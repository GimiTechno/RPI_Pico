cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(develop_project)

pico_sdk_init()

add_executable(dev_20210206
    # Driver
    src/drv/PIO/pio_dac.c
    src/drv/ADC/adc.c
    src/drv/PWM/pwm.c
    src/drv/Timer/timer.c
    src/drv/I2C/i2c.c
    src/drv/I2C/DS3231.c
    src/drv/I2C/LCD1602_I2C.c
    src/drv/SPI/spi.c
    src/drv/SPI/bme280.c
    src/drv/UART/uart.c

    # APP
    src/main.c

    # APP Monitor
    # src/lib/FYSMonitor/mon_main.c
    # src/lib/FYSMonitor/mon_core.c
    )

    # PIO Assembler Create
# pico_generate_pio_header(dev_20210206 src/drv/PIO/resistor_dac.pio)
# pico_generate_pio_header(dev_20210206 ${CMAKE_CURRENT_LIST_DIR}/resistor_dac.pio)

pico_enable_stdio_usb(dev_20210206 1)
pico_enable_stdio_uart(dev_20210206 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(dev_20210206)

target_link_libraries(dev_20210206
        hardware_pio
        hardware_adc
        hardware_dma
        hardware_i2c
        hardware_spi
        hardware_uart
        hardware_pwm
        hardware_rtc
        pico_stdlib
        pico_multicore
        )
