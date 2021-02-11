#ifndef __SPI_H__
#define __SPI_H__

// SDK
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

// APP
#include "../../drv/common.h"

#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

#define SPI_PORT spi0

#define TEST_SIZE 1024

void SPI_Init(void);

#endif /* __SPI_H__ */