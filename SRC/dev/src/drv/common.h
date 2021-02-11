#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "pico/stdlib.h"

#define __ISR

struct st_io {                       /* struct IO    */
    union {                          /* CPUID         */
        uint32_t DWORD;              /*  4Byte Access */
        uint32_t WORD;               /*  Word Access */
        uint32_t BYTE;               /*  Byte Access */
          struct {                   /*  Bit  Access */
                 uint8_t B31:1; /*    Bit 32     */
                 uint8_t B30:1; /*    Bit 31     */
                 uint8_t B29:1; /*    Bit 30     */
                 uint8_t B28:1; /*    Bit 29     */
                 uint8_t B27:1; /*    Bit 28     */
                 uint8_t B26:1; /*    Bit 27     */
                 uint8_t B25:1; /*    Bit 26     */
                 uint8_t B24:1; /*    Bit 25     */
                 uint8_t B23:1; /*    Bit 24     */
                 uint8_t B22:1; /*    Bit 23     */
                 uint8_t B21:1; /*    Bit 22     */
                 uint8_t B20:1; /*    Bit 21     */
                 uint8_t B19:1; /*    Bit 20     */
                 uint8_t B18:1; /*    Bit 19     */
                 uint8_t B17:1; /*    Bit 18     */
                 uint8_t B16:1; /*    Bit 17     */
                 uint8_t B15:1; /*    Bit 16     */
                 uint8_t B14:1; /*    Bit 15     */
                 uint8_t B13:1; /*    Bit 14     */
                 uint8_t B12:1; /*    Bit 13     */
                 uint8_t B11:1; /*    Bit 12     */
                 uint8_t B10:1; /*    Bit 11     */
                 uint8_t B9:1;  /*    Bit 10     */
                 uint8_t B8:1;  /*    Bit 9     */
                 uint8_t B7:1;  /*    Bit 8     */
                 uint8_t B6:1;  /*    Bit 7     */
                 uint8_t B5:1;  /*    Bit 6     */
                 uint8_t B4:1;  /*    Bit 5     */
                 uint8_t B3:1;  /*    Bit 4     */
                 uint8_t B2:1;  /*    Bit 3     */
                 uint8_t B1:1;  /*    Bit 2     */
                 uint8_t B0:1;  /*    Bit 1     */
          } BIT;                     /*              */
    } CPUID;                          /*              */


    uint32_t M0PLUS;                  /*         */
};             

#define REG_BASE_ADDR           0xE0000000
#define REG                     (*(volatile struct st_io *) (REG_BASE_ADDR + 0xED00))

#endif /* __COMMON_H__ */