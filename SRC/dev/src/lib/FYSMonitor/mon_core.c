/**
 * @file （ファイル名） : mon_core.c
 * @brief （概要） : 汎用モニタプログラム コア
 * @author （作成者） : F.Y
 * @date （作成日） : 2021/02/05
 * @details （詳細な説明） :
*/
#include "mon_core.h"

#ifdef __RPI_PICO__
#include "pico/stdlib.h"
#include "hardware/watchdog.h"
#include "hardware/resets.h"
#endif

static void mon_help(void);
static void mon_debuginfo(void);
static void mon_memdump(void);
static void mon_reboot(void);
static void mon_ramentimer(void);

volatile const CMD_TBL_T cmd_tbl[CMD_MAX] = {
    {"?","HELP",&mon_help},
    {"!","INFO",&mon_debuginfo},
    {"$M","MEM",&mon_memdump},
    {"$R","SRST",&mon_reboot},
    {"$T","TIME",&mon_ramentimer},
};

/**
 * @fn void FYSMonitor(void)
 * @brief コマンド取得
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
CMD_E mon_getstr(CMD_T* p_cmd_t)
{
    uint8_t tmp = CMD_NONE;
    uint8_t val;

    val = (uint8_t)getchar();
    // local echo
    printf("%s",&val);
    // printf("(0x%x)",val);

    // Etner key Only ... RST This Func
    if ((val == ONLY_ENTER) && (p_cmd_t->len == 0))
    {
        tmp = CMD_RST;
    }else{
        if((val == '\r') || (val == '\n') || (val == '\0')){
            // CMD Get End
            tmp = CMD_RX;
            // cmd echo
            // printf("%s",(uint8_t *)(p_cmd_t->p_cmdbuf_top));
        } else if((val >= 'a') || (val <= 'z') &&
            (val >= 'A') || (val <= 'Z'))
        {
            *(p_cmd_t->p_cmdbuf) = val;
            p_cmd_t->p_cmdbuf++;
            p_cmd_t->len++;
        } else { 
            /* NOP */
        }
    } 
    return tmp;
}

/**
 * @fn void mon_analyze(uint8_t* p_cmdbuf)
 * @brief コマンド解析
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
void mon_analyze(CMD_T* p_cmd_t)
{
    uint32_t tmp1;
    uint32_t tmp2;
    uint32_t i;

    // Command Serch
    for(i = 0;i < CMD_MAX;i++)
    {

        tmp1 = strcmp(p_cmd_t->p_cmdbuf_top,cmd_tbl[i].cmd);
#ifdef CMD_DEBUGuuuu
        printf("COMPAR CMD = %s, CMD = %s\n",
                p_cmd_t->p_cmdbuf_top,
                cmd_tbl[i].cmd);
#endif
        tmp2 = strcmp(p_cmd_t->p_cmdbuf_top,cmd_tbl[i].cmd_ars);
#ifdef CMD_DEBUG
        printf("COMPAR CMD = %s, CMD = %s\n",
                p_cmd_t->p_cmdbuf_top,
                cmd_tbl[i].cmd_ars);
#endif

        // CMD Match
        if((tmp1 == CMD_CMP_OK) || (tmp2 == CMD_CMP_OK))
        {
            cmd_tbl[i].p_func();
            break;
        }
    }

    // init
    p_cmd_t->len = 0;
    p_cmd_t->p_cmdbuf = p_cmd_t->p_cmdbuf_top;
    memset(p_cmd_t->p_cmdbuf_top,0x00,CMD_MAX_LEN);

#ifdef CMD_DEBUG
    if(i >= CMD_MAX)
    {
        printf("UNKNOWN COMMAND\n");
    }
#endif

    printf("\n");
    printf(">");
}

/**
 * @fn void mon_help(void)
 * @brief コマンド一覧
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
static void mon_help(void)
{
    printf("***********************************************\n");
    printf("|        MONITOR COMMAND HELP FUNCTION        |\n");
    printf("***********************************************\n");
    printf("|    CMD     |       COMMAND INFOMATION       |\n");
    printf("***********************************************\n");

    printf("|   %s,%s   |   MONITOR HELP COMMAND         |\n",cmd_tbl[0].cmd,cmd_tbl[0].cmd_ars);
    printf("|   %s,%s   |   MONITOR DEBUG MODE COMMAND   |\n",cmd_tbl[1].cmd,cmd_tbl[1].cmd_ars);
    printf("|   %s,%s   |   MEMORY DUMP(FLASH) COMMAND   |\n",cmd_tbl[2].cmd,cmd_tbl[2].cmd_ars);
    printf("|   %s,%s   |   SYSTEM REBOOT COMMAND        |\n",cmd_tbl[3].cmd,cmd_tbl[3].cmd_ars);
    printf("|   %s,%s   |   START RAMEN TIMER(3MIN)      |\n",cmd_tbl[4].cmd,cmd_tbl[4].cmd_ars);

    printf("***********************************************\n");
}

/**
 * @fn void mon_debuginfo(void)
 * @brief DEBUG Mode
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
static void mon_debuginfo(void)
{
    printf("MONITOR DEBUG MODE\n");
}

/**
 * @fn void mon_memdump(void)
 * @brief DEBUG Mode
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
static void mon_memdump(void)
{
    printf("MONITOR MEMORY DUMPER\n");
}

/**
 * @fn void mon_ramentimer(void)
 * @brief DEBUG Mode
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
static void mon_ramentimer(void)
{
    printf("RAMEN TIMER START(3 Min)!!!!!!\n");
#ifdef __RPI_PICO__
    Timer_Set_us(180 * 1000000);
#endif
}

/**
 * @fn void mon_reboot(void)
 * @brief System S/W Reset
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
static void mon_reboot(void)
{
    printf("SYSTEM REBOOTING...\n");

#ifdef __RPI_PICO__
    watchdog_enable(0x01, 0x01);
    while(1);
#endif
}
