/*************************************************************************
*   版权所有(C) 1987-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  IPC_BALONG.h
*************************************************************************/

#ifndef _IPC_BALONG_H_
#define _IPC_BALONG_H_
#include <bsp_ipc.h>
#include <soc_interrupts_m3.h>
#ifdef __cplusplus
extern "C" {
#endif

#define BSP_IPC_CPU_RAW_INT(i)		(0x400 + (i * 0x10))
#define BSP_IPC_CPU_INT_MASK(i)		(0x404 + (i * 0x10))
#define BSP_IPC_CPU_INT_STAT(i)		(0x408 + (i * 0x10))
#define BSP_IPC_CPU_INT_CLR(i)		(0x40C + (i * 0x10))

#define BSP_IPC_SEM_RAW_INT(i)		(0x600 + (i * 0x10))
#define BSP_IPC_SEM_INT_MASK(i)		(0x604 + (i * 0x10))
#define BSP_IPC_SEM_INT_STAT(i)		(0x608 + (i * 0x10))
#define BSP_IPC_SEM_INT_CLR(i)		(0x60C + (i * 0x10))

#define BSP_IPC_HS_CTRL(i,j)		(0x800 + (i * 0x100) + (j * 0x8 ))
#define BSP_IPC_HS_STAT(i,j)		(0x804 + (i * 0x100) + (j * 0x8 ))

#ifndef NULL
#define NULL (void*)0
#endif
#define MCPU_IPC_INT M3_IPCM_INT0_2
#define BAK_REG_NUM 10

#ifdef IPC_DEBUG_FEATURE
struct ipc_debug_s
{
	u32  u32RecvIntCore;										/*当前发送中断目标核ID*/
	u32  u32IntHandleTimes[INTSRC_NUM];							/*记录某号中断接收次数*/
	u32  u32IntSendTimes[IPC_CORE_BUTTOM][INTSRC_NUM]; 			/*记录往每个核发送每个中断的次数*/	
};
#endif

struct ipc_control{
    u32    core_num;									/* 记录IPC模块工作所在的核ID*/
    u32    ipc_base;									/*ipc基址*/
    struct ipc_entry ipc_int_table[INTSRC_NUM];			/*记录每一个中断源注册的回调函数*/
    u32    ipc_store_reg_table[BAK_REG_NUM];			/*V7R2 五个核，每个核有两个寄存器需要保存，包括快速中断掩码寄存器（IPC_CPU_INT_MASK）和信号量释放中断掩码寄存器（IPC_SEM_INT_MASK），共计16个*/
	unsigned long last_int_cb_addr;  /* 最后一个被回调的中断函数的地址 */
};

#ifdef __cplusplus
}
#endif

#endif /* end #define _IPC_BALONG_H_*/

