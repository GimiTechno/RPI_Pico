#include "DS3231.h"

const char *rtc_day_tbl[RTC_DAY+1] = {
                        "NONE",
                        "Sun",    /* Day1 = Sunday */
                        "Mon",    /* Day2 = Monday */
                        "Tue",    /* Day3 = Tuesday */
                        "Wed",    /* Day4 = Wednesday */
                        "Thu",    /* Day5 = Thursday */
                        "Fri",    /* Day6 = Friday */
                        "Sat"     /* Day7 = Saturday */
};

void ds3231_init(RTC_T *rtc_t)
{
    // uint8_t buf[] = {REG_DAY,SUNDAY};
    // i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, buf, sizeof(buf), TRUE);
}

void ds3231_read_reg(void)
{
    uint8_t reg = 0;
    uint8_t val = 0;
    RTC_T rtc_t;

    printf("RTC Info\n");

    // Year
    reg = REG_YEARS;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, &reg, sizeof(reg), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_DS3231, &val, sizeof(val), FALSE);
    rtc_t.year = val;
    // printf("20%X/",val);

    // Month
    reg = REG_MONTH;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, &reg, sizeof(reg), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_DS3231, &val, sizeof(val), FALSE);
    rtc_t.month = val;
    // printf("%X/",val);

    // Date
    reg = REG_DATE;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, &reg, sizeof(reg), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_DS3231, &val, sizeof(val), FALSE);
    rtc_t.date = val;
    // printf("%X ",val);

    // Week
    reg = REG_DAY;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, &reg, sizeof(reg), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_DS3231, &val, sizeof(val), FALSE);
    rtc_t.day = val;
    // printf("%s ",rtc_day_tbl[val]);

    // Hour
    reg = REG_HOURS;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, &reg, sizeof(reg), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_DS3231, &val, sizeof(val), FALSE);
    rtc_t.hour = val;
    // printf("%X:",val);

    // Min
    reg = REG_MINUTES;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, &reg, sizeof(reg), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_DS3231, &val, sizeof(val), FALSE);
    rtc_t.min = val;
    // printf("%X:",val);

    // Sec
    reg = REG_SECONDS;
    i2c_write_blocking(I2C_PORT, I2C_ADDR_DS3231, &reg, sizeof(reg), TRUE);
    i2c_read_blocking(I2C_PORT, I2C_ADDR_DS3231, &val, sizeof(val), FALSE);
    rtc_t.sec = val;
    // printf("%X\n",val);

    /* RTC ... フォーマット(DD/MM/YY DOW HH:MM:SS)　DOW...週 */
    printf("RTC(BCD) ... 20%X/%X/%X %s %X:%X:%X\n",
            rtc_t.year,
            rtc_t.month,
            rtc_t.date,
            rtc_day_tbl[rtc_t.day],
            rtc_t.hour,
            rtc_t.min,
            rtc_t.sec);

    printf("RTC(DEC) ... %d/%d/%d %s %d:%d:%d\n",
            2000 + BCD2DEC(rtc_t.year),
            BCD2DEC(rtc_t.month),
            BCD2DEC(rtc_t.date),
            rtc_day_tbl[rtc_t.day],
            BCD2DEC(rtc_t.hour),
            BCD2DEC(rtc_t.min),
            BCD2DEC(rtc_t.sec));
}