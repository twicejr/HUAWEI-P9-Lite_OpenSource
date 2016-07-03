
#ifndef __SOC_INTERRUPTS_M3_H__
#define __SOC_INTERRUPTS_M3_H__
#if 0
#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
                  * interrupts level m3 only *
***************************************************************************/
/* todo */
#define  M3_IPCM_INT0_2                 6  /* IPCM给M3的核间通信，对应IPCM中断0[2] */
#define  M3_IPCM_INT1_2                 7  /* IPCM给M3的核间通信，对应IPCM中断1[2] */
#define  M3_IPC_M2C_INT0                8  /* M3 唤醒MODEM */
#define  M3_IPC_M2C_INT1                9  /* M3 唤醒MODEM */

#define  M3_WDT_INT                     21  /* WatchDog模块输出中断 */


#define  M3_UART2_INT                   62  /* 串口2中断 */

#define  M3_SOCP_INT0                   188 /* SOCP Core0中断*/
#define  M3_SOCP_INT1                   189 /* SOCP Core1中断 */
#define M3_TIMER00_INT                20 
#define M3_TIMER01_INT                21 
#define M3_TIMER10_INT                22
#define M3_TIMER11_INT                23
#define M3_TIMER20_INT                24
#define M3_TIMER21_INT                25
#define M3_TIMER30_INT                26
#define M3_TIMER31_INT                27
#define M3_TIMER40_INT                28 
#define M3_TIMER41_INT                29 
#define M3_TIMER50_INT                30
#define M3_TIMER51_INT                31
#define M3_TIMER60_INT                32
#define M3_TIMER61_INT                33
#define M3_TIMER70_INT                34
#define M3_TIMER71_INT                35

#define M3_LTE_ARM_WAKEUP_INT         191
#define M3_TDS_DRX_ARM_WAKEUP_INT     192
#define M3_G1_INT_BBP_TO_CPU_32K      195
#define M3_G2_INT_BBP_TO_CPU_32K      198
#define M3_W_ARM_INT_02               200
#define M3_IPF_INT0                   204
#define M3_IPF_INT1                   205

/* for setting wake_src in acore/ccore */
#define M3_DRX_TIMER_INT M3_TIMER30_INT

#ifdef __cplusplus
}
#endif
#endif
#endif /* __SOC_INTERRUPTS_M3_H__ */

