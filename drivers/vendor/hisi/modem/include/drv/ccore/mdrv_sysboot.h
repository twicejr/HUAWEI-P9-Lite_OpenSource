#ifndef __MDRV_CCORE_SYSBOOT_H__
#define __MDRV_CCORE_SYSBOOT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_sysboot_commmon.h>

typedef enum DRV_SHUTDOWN_REASON_tag_s
{
	DRV_SHUTDOWN_POWER_KEY,             /* 长按 Power 键关机          */
	DRV_SHUTDOWN_BATTERY_ERROR,         /* 电池异常                   */
	DRV_SHUTDOWN_LOW_BATTERY,           /* 电池电量低                 */
	DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* 过温保护关机               */
	DRV_SHUTDOWN_CHARGE_REMOVE,         /* 关机充电模式下，拔除充电器 */
	DRV_SHUTDOWN_UPDATE,                /* 关机并进入升级模式         */
	DRV_SHUTDOWN_RESET,                 /* 系统软复位                 */
	DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_E;


typedef enum
{
	DRV_START_MODE_CHARGING = 0, /* 充电开机模式, ps 等业务不启动  */
	DRV_START_MODE_NORMAL ,     /* 正常开机模式，所有业务启动     */
	DRV_START_MODE_UPDATE,      /* 升级模式 */
	DRV_START_MODE_BUILT
}DRV_START_MODE_E;


int mdrv_loadas ( DRV_RAT_MODE_ENUM rat_mode );

#define DRV_NOT_START_UMTS (0x55aa5a5a)

DRV_START_MODE_E mdrv_sysboot_get_bootmode(void);

void mdrv_sysboot_poweroff(void);

void mdrv_sysboot_shutdown(DRV_SHUTDOWN_REASON_E eReason);

int mdrv_sysboot_stampadd(const char * phaseName, unsigned int param);

int  mdrv_sysboot_ok(void);

unsigned int mdrv_sysboot_check_startps(void);

#ifdef __cplusplus
}
#endif
#endif
