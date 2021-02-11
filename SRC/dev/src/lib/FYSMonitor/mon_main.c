#include "mon_main.h"

CMD_T g_cmd_t;
static uint8_t cmd_buf[CMD_MAX_LEN];

/**
 * @fn static void mon_init(void)
 * @brief モニタプログラム　初期化
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
void mon_init(void)
{
    g_cmd_t.len = 0;
    memset(&cmd_buf,0x00,sizeof(cmd_buf));
    g_cmd_t.p_cmdbuf_top = (uint8_t*)&cmd_buf;
    g_cmd_t.p_cmdbuf = (uint8_t*)&cmd_buf;

    printf("***************************************\n");
    printf("FSYMONITOR (FSY MONITOR PROGRAM) REV1.0\n");
#ifdef __DEBUG_MON__
    printf("\n");
    printf("[DEBUG] : cmd_tbl[0].cmd = %s\n",cmd_tbl[0].cmd);
    printf("[DEBUG] : cmd_tbl[0].cmd_ars = %s\n",cmd_tbl[0].cmd_ars);
    printf("\n");
#endif
    printf("***************************************\n");
    printf("\n");

    printf(">");

}

/**
 * @fn void mon_main(void)
 * @brief モニタプログラム　メイン
 * @param[in] None
 * @param[out] None
 * @return None
 * @details 
*/
void mon_main(void)
{
    uint8_t  tmp;

    tmp = mon_getstr(&g_cmd_t);

    if(tmp == CMD_RST)
    {
        printf("\n");
        printf(">");
    }

    if((tmp == CMD_RX) && (g_cmd_t.len != 0))
    {
#ifdef CMD_DEBUG
        printf("[DEBUG] : buf = %s,len = %d, strlen = %d\n",
                (uint8_t *)(g_cmd_t.p_cmdbuf_top),
                g_cmd_t.len,strlen(g_cmd_t.p_cmdbuf_top));
#endif
        mon_analyze(&g_cmd_t);
    }
}