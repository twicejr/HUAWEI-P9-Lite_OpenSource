/*************************************************************************
*   版权所有(C) 2008-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  reset_balong.h
*
*   作    者 :  y00184236
*
*   描    述 :  modem单独复位内部C核头文件
*
*   修改记录 :  2014年02月15日  v1.00  y00184236  创建
*************************************************************************/

#ifndef __RESET_BALONG_H__
#define __RESET_BALONG_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <bsp_ipc.h>
#include <bsp_om.h>

struct ccore_reset_ctrl
{
	u32 state;
    u32 stamp_ccpu_addr;
    u32 stamp_m3_reset_addr;
    u32 stamp_m3_unreset_addr;
    u32 fiq_cnt;
	u32 fiq_out;
	IPC_INT_LEV_E ipc_recv_irq_wakeup;
	IPC_INT_LEV_E ipc_send_irq_in_idle;
	IPC_INT_LEV_E ipc_send_irq_reboot_ok;
};

#define  reset_print_err(fmt, ...)    \
	(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __RESET_BALONG_H__ */
