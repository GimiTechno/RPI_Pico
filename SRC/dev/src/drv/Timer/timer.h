#ifndef __TIMER_H__
#define __TIMER_H__

// SDK
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "pico/time.h"

// APP
#include "../../drv/common.h"

typedef  struct _TIMER_T {
        
} _TIMER_T;

// us Oder OneShot Timer Set
void Timer_Set_us(uint32_t ovf_us);
void APP_Timer_Main(void);
#endif