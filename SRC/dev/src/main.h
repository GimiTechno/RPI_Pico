#ifndef __MAIN_H__
#define __MAIN_H__

/*************** lib Include ***************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
/*******************************************/

/*************** SDK Include ***************/
#include "hardware/gpio.h"

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"
/*******************************************/

/*************** DRV Include ***************/
// Common
#include "drv/common.h"
// WDT
#include "drv/WDT/wdt.h"
// Timer
#include "drv/Timer/timer.h"
// PWM
#include "drv/PWM/pwm.h"
// ADC
#include "drv/ADC/adc.h"
// PIO DAC
#include "drv/PIO/pio_dac.h"
// I2C
#include "drv/I2C/i2c.h"
#include "drv/I2C/DS3231.h"
#include "drv/I2C/LCD1602_I2C.h"
// SPI
#include "drv/SPI/spi.h"
#include "drv/SPI/bme280.h"
// UART
#include "drv/UART/uart.h"
/*******************************************/

/*************** APP Include ***************/
// FSYMonitor(Monitor Program)
#include "lib/FYSMonitor/mon_main.h"
/*******************************************/

// Sys
#define SYSTEM_INIT_WAIT_MS    500                  /* System H/W Init Wait Time ms) */
#define TIMER_1MS              1000                 /* 1ms Timer */

// LED
#define LED_PIN                25                   /* Built In LED Pin */
#define LED_BULINK_TIME_MS     500                 /* LED Bulink Time(ms) */

#endif /* __MAIN_H__ */
