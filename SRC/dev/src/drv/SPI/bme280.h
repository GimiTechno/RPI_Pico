#ifndef __BME280_H__
#define __BME280_H__

#include "spi.h"

//    GPIO 16 (pin 21) MISO/spi0_rx-> SDO/SDO on bme280 board
//    GPIO 17 (pin 22) Chip select -> CSB/!CS on bme280 board
//    GPIO 18 (pin 24) SCK/spi0_sclk -> SCL/SCK on bme280 board
//    GPIO 19 (pin 25) MOSI/spi0_tx -> SDA/SDI on bme280 board
//    3.3v (pin 3;6) -> VCC on bme280 board
//    GND (pin 38)  -> GND on bme280 board

// 
#define CHIP_ID_BMP280      0x58
#define CHIP_ID_BME280      0x60

#define READ_BIT 0x80

uint8_t bme280_init(void);
void bme280_main(uint8_t chipid);

#endif /* __BME280_H__ */