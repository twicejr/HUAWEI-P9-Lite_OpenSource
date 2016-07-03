

#ifndef __BFGX_USER_CTRL_H__
#define __BFGX_USER_CTRL_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include "plat_type.h"
#include "hisi_customize_wifi.h"
#include "hisi_ini.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define SNPRINT_LIMIT_TO_KERNEL   (512)

enum PLAT_LOGLEVLE{
	PLAT_LOG_ALERT = 0,
	PLAT_LOG_ERR = 1,
	PLAT_LOG_WARNING = 2,
	PLAT_LOG_INFO = 3,
	PLAT_LOG_DEBUG = 4,
};

enum UART_DUMP_CTRL{
    UART_DUMP_CLOSE =0,
    UART_DUMP_OPEN=1,
};

enum BUG_ON_CTRL{
    BUG_ON_DISABLE = 0,
    BUG_ON_ENABLE  = 1,
};
/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/
extern struct kobject *g_sysfs_hi110x_bfgx;
extern int32 g_plat_loglevel;
extern int32 g_bug_on_enable;

#ifdef PLATFORM_DEBUG_ENABLE
extern int32 g_uart_rx_dump;
#endif

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern int32 bfgx_user_ctrl_init(void);
extern void bfgx_user_ctrl_exit(void);
#endif

