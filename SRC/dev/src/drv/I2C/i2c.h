#ifndef __I2C_H__
#define __I2C_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#define I2C_PORT            i2c0            /* I2C Port = I2C0 */
#if 0
#define I2C_CLOCK           (100 * 1000)    /* I2C 100KHz */
#else
#define I2C_CLOCK           (400 * 1000)    /* I2C 400KHz */
#endif
#define I2C_SDA             0x04            /* SDA(GPIO4) */
#define I2C_SCL             0x05            /* SCL(GPIO5) */

void I2C_Init(void);
void i2c_scan(void);

#endif /* __I2C_H__ */