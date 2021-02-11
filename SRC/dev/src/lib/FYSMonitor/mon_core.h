/**
 * @file （ファイル名） : mon_core.h
 * @brief （概要） : 汎用モニタプログラム コア
 * @author （作成者） : F.Y
 * @date （作成日） : 2021/02/05
 * @details （詳細な説明） :
*/
#ifndef __MON_CORE_H__
#define __MON_CORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// H/W Select
#define  __RPI_PICO__   0x01
// #define  __ARDUINO__    0x01
// #define  __STM32__      0x01

// Monitor DEBUG
// #define CMD_DEBUG   0x01

#ifdef __RPI_PICO__
void watchdog_enable(uint32_t delay_ms, bool pause_on_debug);
extern  void timer_set_us(uint32_t ovf_us);
#endif

#define CMD_MAX         8
#define CMD_CMP_OK      0x00
#define CMD_CMP_NG      0xFF
#define CMD_MAX_LEN     64

#define ONLY_ENTER      0x0A

typedef enum {
    CMD_NONE = 0x00,
    CMD_RX,
    CMD_RST = 0xFF
}CMD_E;

typedef struct {
    uint8_t *cmd;
    uint8_t *cmd_ars;
    void (*p_func)(void);
} CMD_TBL_T;

typedef struct {
    uint8_t *p_cmdbuf_top;
    uint8_t *p_cmdbuf;
    uint8_t len;
} CMD_T;

CMD_E mon_getstr(CMD_T* p_cmd_t);
void mon_analyze(CMD_T* p_cmd_t);

#endif /* __MON_CORE_H__ */