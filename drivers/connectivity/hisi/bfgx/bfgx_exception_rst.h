

#ifndef __BFGX_EXCEPTION_RST_H__
#define __BFGX_EXCEPTION_RST_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include "plat_exception_rst.h"

/*****************************************************************************
  2 Define macro
*****************************************************************************/
/*plat cfg cmd */
#define PLAT_CFG_IOC_MAGIC                     'z'
#define PLAT_DFR_CFG_CMD                       _IOW(PLAT_CFG_IOC_MAGIC, PLAT_DFR_CFG, int)
#define PLAT_BEATTIMER_TIMEOUT_RESET_CFG_CMD   _IOW(PLAT_CFG_IOC_MAGIC, PLAT_BEATTIMER_TIMEOUT_RESET_CFG, int)

#define PLAT_EXCEPTION_ENABLE                  (1)
#define PLAT_EXCEPTION_DISABLE                 (0)

#define DUMP_BCPU_MEM_BUFF_LEN                 (256*4)
#define DUMP_BCPU_REG_BUFF_LEN                 (256*4)
#define WAKEUP_RETRY_TIMES                     (3)
#define WLAN_OPEN_BEFORE_DUMP                  (1)
#define WLAN_CLOSE_BEFROE_DUMP                 (0)
/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
typedef struct DUMP_MEM_RES
{
    uint8 *file_name;
    uint32 start_addr;
    uint32 align_type;
    uint32 men_len;
}exception_bcpu_dump_msg;
enum dump_msg_align_type
{
    ALIGN_1_BYTE    = 0,
    ALIGN_2_BYTE    = 1,
    ALIGN_4_BYTE    = 2,
};
/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 全局变量定义
*****************************************************************************/
enum PLAT_CFG
{
    PLAT_DFR_CFG                           = 0,
    PLAT_BEATTIMER_TIMEOUT_RESET_CFG       = 1,

    PLAT_CFG_BUFF,
};

enum BFGX_DUMP_TYPE
{
    BFGX_PUB_REG                           = 0,
    BFGX_PRIV_REG                          = 1,
    BFGX_MEM                               = 2,

    SDIO_BFGX_MEM_DUMP_BOTTOM,
};

/*****************************************************************************
  6 EXTERN FUNCTION
*****************************************************************************/
extern void plat_dfr_cfg_set(uint64 arg);
extern void plat_beatTimer_timeOut_reset_cfg_set(uint64 arg);

#endif

