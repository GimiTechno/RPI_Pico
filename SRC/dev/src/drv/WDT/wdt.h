#ifndef __WDT_H__
#define __WDT_H__

#include <stdio.h>
#include <stdint.h>

#include "hardware/watchdog.h"
#include "pico/stdlib.h"

// WDT
#define WDT_ENABLE             0x01
#define WDT_OVF_MS             8000                 /* WDT OVF(ms) ... MAX 8000ms*/
#define WDT_DEBUG_DISABLE      0x01                 /* Debuging No WDT RUN */
#define WDT_WAS_OVF            0x01                 /* WDT OVF,Because Rebooted*/
#define WDT_TGL                watchdog_update()    /* WDT Toggle */

#endif