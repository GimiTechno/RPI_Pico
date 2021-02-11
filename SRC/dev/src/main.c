#include "main.h"

static void HW_init( void );
static void binary_info( void );
static void led_blink( void );
static void opn_msg( void );
static void APP_LCD( void );

static void APP_init_0( void );
static void APP_init_1( void );
static void main_1( void );
static void APP_Main_0( void );
static void APP_Main_1( void );

// For SPI(BMP280/BME280)
static uint8_t s_chipid = 0;

// For I2C(LCD1602)
static uint8_t *message[] =
{
        "RP2040 by", "Raspberry Pi",
        "And 2Core of ", "ARM Cortex M0+",
};

static void APP_LCD( void )
{
    for (int m = 0; m < sizeof(message) / sizeof(message[0]); m += MAX_LINES) {
        for (int line = 0; line < MAX_LINES; line++) {
            lcd_set_cursor(line, (MAX_CHARS / 2) - strlen(message[m + line]) / 2);
            lcd_string(message[m + line]);
        }
        sleep_ms(2000);
#ifdef WDT_ENABLE
        WDT_TGL;
#endif
        lcd_clear();
    }
}

static void opn_msg( void )
{
    /* opg msg */
    printf("************************************************************\n");

    // WDT OVF Reseted Reboot Check
    if (watchdog_caused_reboot() == WDT_WAS_OVF) {
        printf("[DEBUG MSG] : Rebooted by WDT. WDT was OVF!!!\n");
    }
    // F/W info
    printf("DEBUG Development REV1.0\n");
#ifdef WDT_ENABLE
    printf("[System Info] : WDT OVF ... %dms\n",WDT_OVF_MS);
#endif
    printf("[System Info] : CPUID REG ... 0x%X\n",REG.CPUID.DWORD);
    printf("************************************************************\n");
}

static void HW_init( void )
{
    binary_info();
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    PWM_Init();

    ADC_Init();
    I2C_Init();
    SPI_Init();
    UART_Init();

    // 1ms Timer Set
    // timer_set_us(TIMER_1MS);

#ifdef WDT_ENABLE
    // WDT Enable. OVF@ WDT_OVF_MS
    watchdog_enable(WDT_OVF_MS, WDT_DEBUG_DISABLE);
#endif
}

static void led_blink( void )
{
    static uint8_t s_val = 0;
    static uint32_t tmp = 0;

    s_val = ~s_val;

    gpio_put(LED_PIN, !s_val);
    tmp += LED_BULINK_TIME_MS;
    // printf("No WDT Tgl ... %dms\n",tmp);
    sleep_ms(LED_BULINK_TIME_MS);
}

static void binary_info( void )
{
    bi_decl(bi_program_description("F/W REV 1.0"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
}

// Core0 App Init
static void APP_init_0( void )
{
    HW_init();
    sleep_ms(SYSTEM_INIT_WAIT_MS);

    // opn_msg();
    // mon_init();
    // i2c_scan();

    // I2C LCD
    // lcd_init();

    ADC_DMA_Start();

#ifdef WDT_ENABLE
    WDT_TGL;
#endif
}

// Core1 App Init
static void APP_init_1( void )
{
    // DACはSPIとバッティングしてる
    // PIO_DAC_Init();

    // BME280(SPI)湿温度気圧センサ
    s_chipid = bme280_init();
}

// Core0 App Main
static void APP_Main_0( void )
{
    // mon_main();

    ds3231_read_reg();
    sleep_ms(900);

    // APP_ADC_Main();
    // APP_LCD();
}

// Core1 App Main
static void APP_Main_1( void )
{
    // led_blink();

    // Timer @ 1ms
    // timer_main();

    // DACはSPIとバッティングしてる
    // PIO_DAC_Main();

    uart_puts(UART_ID, "\nCore1 Main1 Loop\n");

    // BME280(SPI)湿温度気圧センサ
    bme280_main(s_chipid);
    sleep_ms(1000);
}

// Core1 Startup Entry
static void main_1( void )
{
    APP_init_1();

    while(1){
        APP_Main_1();
#ifdef WDT_ENABLE
        WDT_TGL;
#endif
    }
}

// Core0 Startup Entry
int main( void )
{
    APP_init_0();

    // WakeUP Core1
    multicore_launch_core1(main_1);

    while(1){
        APP_Main_0();
#ifdef WDT_ENABLE
        WDT_TGL;
#endif
    }
}