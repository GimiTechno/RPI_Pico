#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "i2c.h"

#define I2C_ADDR_MPU6050     0x68  

void mpu6050_init( void );
void mpu6050_read(void);

#endif  /* __MPU6050_H__ */