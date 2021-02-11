#ifndef __CLK_H__
#define __CLK_H__

// SDK
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"

// APP
#include "../../drv/common.h"

#define PLL_NOTUSE          0x00
#define PLL_USE_CLOCK_UP    0x01

void CLK_Info(uint8_t pll);
void Clock_Init(void);

#endif /* __CLK_H__ */