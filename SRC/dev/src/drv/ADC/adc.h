#ifndef __ADC_H__
#define __ADC_H__

#include <stdio.h>

#include "pico/stdlib.h"

// For ADC input:
#include "hardware/adc.h"
#include "hardware/dma.h"

// Channel 0 is GPIO26
#define CAPTURE_CHANNEL 0
#define CAPTURE_DEPTH 1000

#define N_SAMPLES 1000

void ADC_Init(void);
void ADC_DMA_Start(void);
void PIO_DAC_Main(void);
void APP_ADC_Main(void);

#endif /* __ADC_H__ */