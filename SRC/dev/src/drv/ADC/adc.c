#include "adc.h"

static void ADC_DMA_Init(void);
static void ADC_DMA_Restart(void);

// DMA CH
static uint8_t s_dma_ch = 0;
dma_channel_config g_cfg;

// ADC Channel(4CH = Inter Temp Sensor)
static uint8_t s_adc_ch = ADC_0CH;
// static uint8_t s_adc_ch = ADC_4CH_TEMP_SENSOR;

// ADC Capter Buf(DMA Use)
#define CAPTURE_DEPTH 8
uint32_t capture_buf[CAPTURE_DEPTH];

static void ADC_DMA_Init(void)
{
    // Set up the DMA to start transferring data as soon as it appears in FIFO
    s_dma_ch = dma_claim_unused_channel(TRUE);
    dma_channel_config cfg = dma_channel_get_default_config(s_dma_ch);

    // Reading from constant address, writing to incrementing byte addresses
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_32);
    channel_config_set_read_increment(&cfg, FALSE);
    channel_config_set_write_increment(&cfg, TRUE);

    // Pace transfers based on availability of ADC samples
    channel_config_set_dreq(&cfg, DREQ_ADC);

    dma_channel_configure(s_dma_ch, &cfg,
        capture_buf,    // dst
        &adc_hw->fifo,  // src
        CAPTURE_DEPTH,  // transfer count
        TRUE            // start immediately
    );
}

static void ADC_DMA_Restart(void)
{
    // Reading from constant address, writing to incrementing byte addresses
    channel_config_set_transfer_data_size(&g_cfg, DMA_SIZE_32);
    channel_config_set_read_increment(&g_cfg, FALSE);
    channel_config_set_write_increment(&g_cfg, TRUE);

    // Pace transfers based on availability of ADC samples
    channel_config_set_dreq(&g_cfg, DREQ_ADC);

    dma_channel_configure(s_dma_ch, &g_cfg,
        capture_buf,    // dst
        &adc_hw->fifo,  // src
        CAPTURE_DEPTH,  // transfer count
        TRUE            // start immediately
    );
}

void ADC_DMA_Get(void)
{
    // Restart
    ADC_DMA_Restart();

    // printf("Starting capture\n");
    adc_run(TRUE);

    // Once DMA finishes, stop any new conversions from starting, and clean up
    // the FIFO in case the ADC was still mid-conversion.
    dma_channel_wait_for_finish_blocking(s_dma_ch);
    // printf("Capture finished\n");
    adc_run(FALSE);
    adc_fifo_drain();
}

void ADC_Init(void)
{
    // Init GPIO for analogue use: hi-Z, no pulls, disable digital input buffer.
    adc_gpio_init(ADC_GPIO_BASE + s_adc_ch);

    adc_init();
    adc_set_temp_sensor_enabled(TRUE);

    adc_select_input(s_adc_ch);

    adc_fifo_setup(
        TRUE,    // Write each completed conversion to the sample FIFO
        TRUE,    // Enable DMA data request (DREQ)
        1,       // DREQ (and IRQ) asserted when at least 1 sample present
        FALSE,   // We won't see the ERR bit because of 8 bit reads; disable.
        TRUE     // Shift each sample to 8 bits when pushing to FIFO
    );

    // Divisor of 0 -> full speed. Free-running capture with the divider is
    // equivalent to pressing the ADC_CS_START_ONCE button once per `div + 1`
    // cycles (div not necessarily an integer). Each conversion takes 96
    // cycles, so in general you want a divider of 0 (hold down the button
    // continuously) or > 95 (take samples less frequently than 96 cycle
    // intervals). This is all timed by the 48 MHz ADC clock.
    adc_set_clkdiv(0);

    ADC_DMA_Init();
}

void APP_ADC_Main(void)
{
    uint8_t i;

    ADC_DMA_Get();

    // Print samples to stdout so you can display them in pyplot, excel, matlab
    for ( i = 0; i < CAPTURE_DEPTH; ++i)
    {
        if(s_adc_ch != ADC_TEMP_SENSOR)
        {
            printf("%-3d, ", capture_buf[i]);
            if (i % 10 == 9)
                printf("\n");
        }else{
            printf("Temp = %dC\n", capture_buf[i]);
        }
    }
}