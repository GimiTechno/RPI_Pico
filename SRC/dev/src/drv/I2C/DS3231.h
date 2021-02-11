#ifndef __DS3231_H__
#define __DS3231_H__

#include "i2c.h"

#define I2C_ADDR_DS3231            0x68
#define I2C_ADDR_DS3231_EEPROM     0x57

#define RTC_DAY                    0x07

#define SUNDAY                     0x01
#define MONDAY                     0x02
#define TUESDAY                    0x03
#define WEDNESDAY                  0x04
#define THURSDAY                   0x05
#define FRIDAY                     0x06
#define SATURDAY                   0x07

// DEC -> BCD
#define DEC2BCD(x) \
        ((x / 10) & 0x0F) << 4 | ((x % 10) & 0x0F)

// BCD -> DEC
#define BCD2DEC(x) \
        ((x >> 4) & 0x0F) * 10 + (x & 0x0F)

typedef struct _RTC_T {
    uint8_t year;   /* 年 */
    uint8_t month;  /* 月 */
    uint8_t date;   /* 日 */
    uint8_t day;    /* 曜日 */
    uint8_t hour;   /* 時 */
    uint8_t min;    /* 分 */
    uint8_t sec;    /* 秒 */
} RTC_T;

/*************************** REG MAP ***************************/
/* フォーマット(DD/MM/YY DOW HH:MM:SS)　DOW...週 */
#define REG_SECONDS                 0x00    /* 秒 */
#define REG_MINUTES                 0x01    /* 分 */
#define REG_HOURS                   0x02    /* 時 */
#define REG_DAY                     0x03    /* 曜日 */
#define REG_DATE                    0x04    /* 日 */
#define REG_MONTH                   0x05    /* 月 */
#define REG_YEARS                   0x06    /* 年 */

#define REG_ALARM1_SEC              0x07    /* アラーム1　秒 */
#define REG_ALARM1_MIN              0x08    /* アラーム1　分 */
#define REG_ALARM1_HOUR             0x09    /* アラーム1　時 */
#define REG_ALARM1_DAY_DATE         0x0A    /* アラーム1　曜日/日 */

#define REG_ALARM2_MIN              0x0B    /* アラーム2　分 */
#define REG_ALARM2_HOUR             0x0C    /* アラーム2　時 */
#define REG_ALARM2_DAY_DATE         0x0D    /* アラーム2　曜日/日 */

#define REG_CONTROL                 0x0E    /* Conrtol Reg */
#define REG_CONTROL_STATUS          0x0F    /* Conrtol Reg/Status */

#define REG_AGING_OFFSET            0x10    /* Aging Offset */
#define REG_MSB_TEMP                0x11    /* MSB of Temp */
#define REG_LSB_TEMP                0x12    /* LSB of Temp */
/**************************************************************/

void ds3231_init(RTC_T *rtc_t);
void ds3231_read_reg(void);

#endif