#include "pio_dac.h"

static PIO s_pio;
static uint s_sm;
static uint s_offset;

void PIO_DAC_Init(void)
{
    s_pio = pio0;
    s_sm = pio_claim_unused_sm(pio0, true);
    s_offset = pio_add_program(pio0, &resistor_dac_5bit_program);

    resistor_dac_5bit_program_init(pio0, s_sm, s_offset,
        OUTPUT_FREQ_KHZ * 1000 * 2 * (1 << SAMPLE_WIDTH), DAC_PIN_BASE);
}

// Must Core1 Run 
void PIO_DAC_Main(void)
{

    while (true) {
        // Triangle wave
        for (int i = 0; i < (1 << SAMPLE_WIDTH); ++i)
            pio_sm_put_blocking(s_pio, s_sm, i);
        for (int i = 0; i < (1 << SAMPLE_WIDTH); ++i)
            pio_sm_put_blocking(s_pio, s_sm, (1 << SAMPLE_WIDTH) - 1 - i);
    }
}