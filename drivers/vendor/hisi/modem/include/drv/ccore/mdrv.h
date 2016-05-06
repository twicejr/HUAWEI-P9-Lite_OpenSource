#ifndef __MDRV_CCORE_H__
#define __MDRV_CCORE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "product_config.h"

/*public*/
#include "mdrv_public.h"
#include "mdrv_version.h"

/*soc*/
#include "mdrv_int.h"
#include "mdrv_ipc.h"
#include "mdrv_icc.h"
#include "mdrv_rtc.h"
#include "mdrv_timer.h"
#include "mdrv_edma.h"
#include "mdrv_memory.h"
#include "mdrv_sysctrl.h"
#include "mdrv_sync.h"
#include "mdrv_pm.h"

/*rat related*/
#include "mdrv_bbp.h"
#include "mdrv_cipher.h"
#include "mdrv_crypto.h"
#include "mdrv_dsp.h"
#include "mdrv_ipf.h"

/*device ip*/
#include "mdrv_abb.h"
#include "mdrv_anten.h"
#include "mdrv_efuse.h"
#include "mdrv_gpio.h"
#include "mdrv_hkadc.h"
#include "mdrv_misc.h"
#include "mdrv_pmu.h"
#include "mdrv_sci.h"
#include "mdrv_leds.h"
#include "mdrv_mipi.h"

/*封装*/
#include "mdrv_udi.h"
#include "mdrv_om.h"
#include "mdrv_rfile.h"
#include "mdrv_nvim.h"

#include "mdrv_socp.h"
#include "mdrv_dual_modem.h"
/*solution*/
#include "mdrv_mailbox.h"
#include "mdrv_xmailbox.h"
#include "mdrv_sysboot.h"
#include "mdrv_thermal.h"

/*stub*/
#include "mdrv_wifi.h"
#include "mdrv_stub.h"

#include "drv_mailbox_cfg.h"    /* 多核ICC项目后此头文件删除 */

#include "mdrv_msp_sleep.h"

#ifdef __cplusplus
}
#endif
#endif

