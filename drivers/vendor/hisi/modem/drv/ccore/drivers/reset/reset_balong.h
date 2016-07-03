

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

struct crg_clkstat_ctrl
{
    unsigned int addr_offset;
    unsigned int hdlc;
    unsigned int upacc;
    unsigned int cicom1;
    unsigned int cicom0;
};

#define  reset_print_err(fmt, ...)    \
	(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __RESET_BALONG_H__ */
