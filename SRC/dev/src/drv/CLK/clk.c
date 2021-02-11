#include "clk.h"

void CLK_Info(uint8_t pll)
{
        uint32_t f_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
        uint32_t f_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
        uint32_t f_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
        uint32_t f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
        uint32_t f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
        uint32_t f_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
        uint32_t f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
        uint32_t f_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);

    // KHz Oder Print
    if(pll != PLL_USE_CLOCK_UP)
    {
        printf("PLL_SYS  = %dkHz\n", f_pll_sys);
        printf("PLL_USB  = %dkHz\n", f_pll_usb);
        printf("ROSC     = %dkHz\n", f_rosc);
        printf("CLK_SYS  = %dkHz\n", f_clk_sys);
        printf("CLK_PERI = %dkHz\n", f_clk_peri);
        printf("CLK_USB  = %dkHz\n", f_clk_usb);
        printf("CLK_ADC  = %dkHz\n", f_clk_adc);
        printf("CLK_RTC  = %dkHz\n", f_clk_rtc);
    }else{     // MHz Oder Print
        printf("PLL_SYS  = %.3fMHz\n", f_pll_sys / 1000.0);
        printf("PLL_USB  = %.3fMHz\n", f_pll_usb / 1000.0);
        printf("ROSC     = %.3fMHz\n", f_rosc / 1000.0);
        printf("CLK_SYS  = %.3fMHz\n", f_clk_sys / 1000.0);
        printf("CLK_PERI = %.3fMHz\n", f_clk_peri / 1000.0);
        printf("CLK_USB  = %.3fMHz\n", f_clk_usb / 1000.0);
        printf("CLK_ADC  = %.3fMHz\n", f_clk_adc / 1000.0);
        printf("CLK_RTC  = %.3fMHz\n", f_clk_rtc / 1000.0);
    }
}

void Clock_Init(void)
{
    // Reconfigure PLL sys back to the default state of 1500 / 6 / 2 = 125MHz
    pll_init(pll_sys, 1, 1500 * MHZ, 6, 2);

    // CLK SYS = PLL SYS (125MHz) / 1 = 125MHz
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
                    125 * MHZ,
                    125 * MHZ);

    stdio_init_all();
}