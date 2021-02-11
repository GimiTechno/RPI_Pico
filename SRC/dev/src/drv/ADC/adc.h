#ifndef __ADC_H__
#define __ADC_H__

// SDK
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

// APP
#include "../../drv/common.h"

// Channel 0 is GPIO26
#define CAPTURE_CHANNEL 0

typedef enum{
    ADC_0CH = 0,
    ADC_1CH,
    ADC_2CH,
    ADC_3CH,
    ADC_4CH_TEMP_SENSOR = 4
} ADC_CH_E;

// ADC GPIO = GPIO26 - GPIO29
#define ADC_GPIO_BASE       26
#define ADC_TEMP_SENSOR     0x04

void ADC_Init(void);
void ADC_DMA_Get(void);
void PIO_DAC_Main(void);
void APP_ADC_Main(void);

#endif /* __ADC_H__ */