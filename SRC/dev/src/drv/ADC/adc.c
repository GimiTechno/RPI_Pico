#include "adc.h"

// This example uses the DMA to capture many samples from the ADC.
// - We are putting the ADC in free-running capture mode at 0.5 Msps
// - A DMA channel will be attached to the ADC sample FIFO
// - Configure the ADC to right-shift samples to 8 bits of significance, so we
//   can DMA into a byte buffer
// This could be extended to use the ADC's round robin feature to sample two
// channels concurrently at 0.25 Msps each.
//
// It would be nice to have some analog samples to measure! This example also
// drives waves out through a 5-bit resistor DAC, as found on the reference
// VGA board. If you have that board, you can take an M-F jumper wire from
// GPIO 26 to the Green pin on the VGA connector (top row, next-but-rightmost
// hole). Or you can ignore that part of the code and connect your own signal
// to the ADC input.

uint8_t capture_buf[CAPTURE_DEPTH];

static void ADC_DMA_Init(void);
uint s_dma_chan = 0;

static void ADC_DMA_Init(void)
{
    // Set up the DMA to start transferring data as soon as it appears in FIFO
    s_dma_chan = dma_claim_unused_channel(true);
    dma_channel_config cfg = dma_channel_get_default_config(s_dma_chan);

    // Reading from constant address, writing to incrementing byte addresses
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);

    // Pace transfers based on availability of ADC samples
    channel_config_set_dreq(&cfg, DREQ_ADC);

    dma_channel_configure(s_dma_chan, &cfg,
        capture_buf,    // dst
        &adc_hw->fifo,  // src
        CAPTURE_DEPTH,  // transfer count
        true            // start immediately
    );
}

void ADC_DMA_Start(void)
{
    // printf("Starting capture\n");
    adc_run(true);

    // Once DMA finishes, stop any new conversions from starting, and clean up
    // the FIFO in case the ADC was still mid-conversion.
    dma_channel_wait_for_finish_blocking(s_dma_chan);
    // printf("Capture finished\n");
    adc_run(false);
    adc_fifo_drain();
}

void ADC_Init(void)
{
    // Init GPIO for analogue use: hi-Z, no pulls, disable digital input buffer.
    adc_gpio_init(26 + CAPTURE_CHANNEL);

    adc_init();
    adc_select_input(CAPTURE_CHANNEL);
    adc_fifo_setup(
        true,    // Write each completed conversion to the sample FIFO
        true,    // Enable DMA data request (DREQ)
        1,       // DREQ (and IRQ) asserted when at least 1 sample present
        false,   // We won't see the ERR bit because of 8 bit reads; disable.
        true     // Shift each sample to 8 bits when pushing to FIFO
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
    // Print samples to stdout so you can display them in pyplot, excel, matlab
    for (int i = 0; i < CAPTURE_DEPTH; ++i)
    {
        printf("%-3d, ", capture_buf[i]);
        if (i % 10 == 9)
            printf("\n");
    }
}