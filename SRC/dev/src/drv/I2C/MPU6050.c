#include "MPU6050.h"

static void mpu6050_read_raw(int16_t *p_accel, int16_t *p_gyro, int16_t *temp);

static void mpu6050_read_raw(int16_t *p_accel, int16_t *p_gyro, int16_t *temp)
{
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_MPU6050, &val, sizeof(val), TRUE); // TRUE to keep master control of bus
    i2c_read_blocking(I2C_PORT, I2C_ADDR_MPU6050, buffer, sizeof(buffer), FALSE);

    for (int i = 0; i < 3; i++) {
        *p_accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now p_gyro data from reg 0x43 for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_MPU6050, &val, sizeof(val), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_MPU6050, buffer, sizeof(buffer), FALSE);  // FALSE - finished with bus

    for (int i = 0; i < 3; i++) {
        *p_gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }

    // Now temperature from reg 0x41 for 2 bytes
    // The register is auto incrementing on each read
    val = 0x41;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_MPU6050, &val, sizeof(val), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_MPU6050, buffer, 2, FALSE);  // FALSE - finished with bus

    *temp = buffer[0] << 8 | buffer[1];
}

void mpu6050_init( void )
{
    // Two byte reset. First byte register, second byte data
    // There are a load more options to set up the device in different ways that could be added here
    uint8_t buf[2] = {0x6B, 0x00};

    i2c_write_blocking(I2C_PORT, I2C_ADDR_MPU6050, buf, sizeof(buf), FALSE);
}

void mpu6050_read(void)
{
    int16_t acceleration[3], gyro[3], temp;

    mpu6050_read_raw(&acceleration, &gyro, &temp);

    // These are the raw numbers from the chip, so will need tweaking to be really useful.
    // See the datasheet for more information
    printf("Acc. X = %d, Y = %d, Z = %d\n", acceleration[0], acceleration[1], acceleration[2]);
    printf("Gyro. X = %d, Y = %d, Z = %d\n", gyro[0], gyro[1], gyro[2]);
    // Temperature is simple so use the datasheet calculation to get deg C.
    // Note this is chip temperature.
    printf("Temp. = %f\n", (temp / 340.0) + 36.53);

    sleep_ms(100);
}