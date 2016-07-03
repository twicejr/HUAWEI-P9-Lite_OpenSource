

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __PWRCTRL_COMMON_H__
#define __PWRCTRL_COMMON_H__

#if 0
#include <soc_baseaddr_interface.h>
#if defined(CHIP_BB_HI6210)

#else
#include <soc_sctrl_interface.h>
#endif
#include <soc_timer_interface.h>
#endif
#include <linux/hisi/pm/pwrctrl_multi_memcfg.h>
#include <linux/hisi/pm/pwrctrl_multi_def.h>
#include <linux/hisi/pm/pwrctrl_multi_dfs.h>
#include <linux/hisi/pm/pwrctrl_multi_sleep.h>
#include <linux/hisi/pm/pwrctrl_multi_mca.h>

#if 0
#include <mntn/excDrv.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#if 0
#define PWC_REG_UART_PHY            (SOC_UART0_BASE_ADDR)
#endif
#define PWRCTRL_SLICE_UNIT_CONV     (1000)           /*s -> us*/
#if 0
#define PWC_MCU_SLICE_TIMER_ID      (PWC_SLICE_TIMER_ID)


#define PWRCTRL_ACPU_PD_SIZE        0x200
#define PWRCTRL_ACPU_HOTPLUG_SIZE   0x200
#define PWRCTRL_INIT_FLAG           0x12345678

/*A 核异常信息区分配*/
#define EXCH_ACPU_CORE_PWC_ADDR     (PWRCTRL_EXC_ACPU_ADDR - EXCH_BASE_ADDR + EXCH_DDR_BASE_ADDR)  /*phy addr*/
#define EXCH_ACPU_CORE_PWC_ADDR_V   (PWRCTRL_EXC_ACPU_ADDR)  /*virtue addr*/
#define EXCH_ACPU_CORE_PWC_SIZE     (PWRCTRL_EXC_ACPU_SIZE)
#define EXCH_ACPU_CORE_HOTPLUG_ADDR (EXCH_ACPU_CORE_PWC_ADDR_V + PWRCTRL_ACPU_PD_SIZE)



#define EXCH_ACPU_CORE_INFO_OFFSET      (sizeof(PWRCTRL_ACPU_EXC_PD_STRU))





#ifdef WIN32    /*for pc ut/st*/
#define IO_ADDRESS(x)               (0xffff0000)
#endif
#endif
/*log output*/
/***********************************************************************
#ifdef WIN32

#define PWC_TRACE(enLogLevel, fmt, arg0, arg1, arg2, arg3, arg4, arg5)     \
    printf("["#enLogLevel"]"fmt"\n", arg0, arg1, arg2, arg3, arg4, arg5)

#else
#define PWC_TRACE(enLogLevel, fmt, arg0, arg1, arg2, arg3, arg4, arg5)     \
    printk(fmt, arg0, arg1, arg2, arg3, arg4, arg5)
#endif
***********************************************************************/

/*log output*/
#ifdef WIN32
#define PWC_TRACE(enLogLevel, fmt,...)     \
    printf("["#enLogLevel"]"fmt"\n",__VA_ARGS__)

#else
#define PWC_TRACE(enLogLevel, fmt, args...)     \
    printk(fmt, ## args)
#endif


#if 0
#define PWC_LOG_MEM(info, addr, size) \
    pwrctrl_log_mem(info, addr, size)

#ifdef _PWRCTRL_DEB_VERSION_
#define PWRCTRL_DEBUG_TRACE(data) \
{\
    if( 0 == g_ulPwrctrlDebugTrace)\
    {\
        *(volatile u8_t *)(UART_CCPU_BASE) = data;\
    }\
    if( 1 == g_ulPwrctrlDebugTrace)\
    {\
         PWC_TRACE(PWC_LOG_MAX, "%c",data);\
    }\
}
#else
#define PWRCTRL_DEBUG_TRACE(data)
#endif

extern unsigned int g_ulpwrctrl_print_switch;

/*根据EM_PWC_SWITCH模块划分*/

#define PRINT_PWC_DBG(mod, fmt, args...)  \
do { \
    if (0 != (g_ulpwrctrl_print_switch&(1<<mod))) \
    { \
        printk(fmt, ## args) ; \
    } \
} while (0)
#endif
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
#if 0
typedef struct PWRCTRL_ACPU_EXC_PD_STRU_S
{
    u32_t  SlpCnt;         //+0X0
    u32_t  WkCnt;          //+0X4
    u32_t  rev[2];         //+0X8

    u32_t  SlpMgrSTm;
    u32_t  SlpSTm;
    u32_t  WkSTm;
    u32_t  WkMgrSTm;

    u32_t  SlpIpcCnt;
    u32_t  SlpIpcSTm;
    u32_t  WfiRetCnt;
    u32_t  WfiRetSTm;

    u32_t  mcPdCnt;     //主core(master core)记录:对从core的上下电状态
    u32_t  mcPuCnt;
    u32_t  mcPdSTm;
    u32_t  mcPuSTm;

    u32_t  mcWfiFailCnt;
    u32_t  mcWfiFailSTm;
    u32_t  rev2[2];
}PWRCTRL_ACPU_EXC_PD_STRU;

typedef struct PWRCTRL_ACPU_EXC_LOG_STRU_S
{
    PWRCTRL_ACPU_EXC_PD_STRU  core0;
    PWRCTRL_ACPU_EXC_PD_STRU  core1;
    PWRCTRL_ACPU_EXC_PD_STRU  core2;
    PWRCTRL_ACPU_EXC_PD_STRU  core3;

}PWRCTRL_ACPU_EXC_LOG_STRU;
#endif
/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/
#if 0
extern PWRCTRL_ACPU_EXC_LOG_STRU * g_stAcpuPwcExcLog;
extern u32_t   g_ulPwcDebugTrace;
extern u32_t g_pwc_init_flag;
#endif

extern s8_t g_pwcAcpuWakeFlagIcc;
extern s8_t g_pwcAcpuWakeFlagRfile;
extern PWC_ACPU_LOG_STRU * g_pPwcAcpuLog;
/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern s32_t pwrctrl_clr_bits (unsigned long ulRegAddr, u32_t ulMask);
extern u32_t  pwrctrl_get_slice_time( void_t );
extern u32_t pwrctrl_is_bit_set (unsigned long addr,  u32_t offset);
extern s32_t pwrctrl_mem_cpy ( void_t * dest, void_t * src, u32_t size );
extern u32_t pwrctrl_read_reg32 (unsigned long ulRegAddr );
extern s32_t pwrctrl_timer_delay (u32_t time);
extern s32_t pwrctrl_write_reg32(unsigned long ulRegAddr, u32_t ulRegVal);
extern s32_t pwrctrl_set_bits (unsigned long ulRegAddr, u32_t ulMask);
extern void_t pwrctrl_write_reg32_mask (unsigned long ulRegAddr, u32_t ulRegVal, u32_t ulMask);
extern u32_t pwrctrl_read_reg32_mask(unsigned long ulRegAddr, u32_t ulMask);
extern bool_t pwrctrl_is_bits_set(unsigned long ulRegAddr, u32_t ulMask);
extern bool_t pwrctrl_is_bits_clr(unsigned long ulRegAddr, u32_t ulMask);
extern s32_t pwrctrl_ccpu_debug_info_show( void_t );
extern s32_t pwrctrl_mcu_debug_info_show( void_t );









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bsp_pwc_common.h */
