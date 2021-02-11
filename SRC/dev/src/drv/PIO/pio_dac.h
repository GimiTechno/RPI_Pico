#ifndef __PIO_DAC_H__
#define __PIO_DAC_H__

// SDK
#include "pico/stdlib.h"
#include "hardware/pio.h"

// APP
#include "../../drv/common.h"

// ASM
#include "resistor_dac.pio.h"

// ----------------------------------------------------------------------------
// Code for driving the "DAC" output for us to measure

// Core 1 is just going to sit and drive samples out continously. PIO provides
// consistent sample frequency.

#define OUTPUT_FREQ_KHZ 5
#define SAMPLE_WIDTH 5
// This is the green channel on the VGA board
#define DAC_PIN_BASE 6

void PIO_DAC_Init(void);
void PIO_DAC_Main(void);

#endif /* __PIO_DAC_H__ */