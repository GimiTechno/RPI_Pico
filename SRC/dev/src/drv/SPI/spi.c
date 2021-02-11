#include "spi.h"

void SPI_Init(void)
{
/********************** For BME280 **********************/
//    GPIO 16 (pin 21) MISO/spi0_rx-> SDO/SDO on bme280 board
//    GPIO 17 (pin 22) Chip select -> CSB/!CS on bme280 board
//    GPIO 18 (pin 24) SCK/spi0_sclk -> SCL/SCK on bme280 board
//    GPIO 19 (pin 25) MOSI/spi0_tx -> SDA/SDI on bme280 board
//    3.3v (pin 3;6) -> VCC on bme280 board
//    GND (pin 38)  -> GND on bme280 board

    // SPI0 at 0.5MHz.
    spi_init(SPI_PORT, 500 * 1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
/*******************************************************/
}