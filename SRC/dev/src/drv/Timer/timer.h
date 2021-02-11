#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>
#include <stdint.h>

#include "hardware/irq.h"

#include "pico/stdlib.h"
#include "pico/time.h"

// us oder timer set
void timer_set_us(uint32_t ovf_us);
void timer_main(void);
#endif