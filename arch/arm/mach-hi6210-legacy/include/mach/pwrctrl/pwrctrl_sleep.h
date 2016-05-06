/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_sleep.h
  版 本 号   : 初稿
  作    者   : 刘永富 56193
  生成日期   : 2012年7月25日
  最近修改   :
  功能描述   : pwrctrl_sleep.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月25日
    作    者   : 刘永富 56193
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PWRCTRL_SLEEP_H__
#define __PWRCTRL_SLEEP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PWRCTRL_JMP_INSTRUCTION             (0xea00007e)    /*B pc+0x200*/
#define PWC_STORE_MEM_SIZE                  (0x200)
#define ACPU_GIC_ICDABR_NUM                 (5)
#define ACPU_COMMTX_CORE0                   (132)
#define ACPU_COMMTX_CORE3                   (135)
#define ACPU_GIC_MAX_NUM                    (160)


/*SCU*/
#define ACPU_SCU_BASE               (SOC_ACPU_A7_PRIVATE_BASE_ADDR)
#define ACPU_SCU_BASE_VA            IO_ADDRESS(ACPU_SCU_BASE)

/*L2CC*/
#if defined(CHIP_BB_HI6210)

#else
#define ACPU_L2CC_BASE             (SOC_L2CC_BASE_ADDR)
#define ACPU_L2CC_BASE_VA          IO_ADDRESS(ACPU_L2CC_BASE)
#define ACPU_L2CC_CTRL_VA          (ACPU_L2CC_BASE_VA + 0x100)
#define ACPU_L2CC_AUX_CTRL_VA      (ACPU_L2CC_BASE_VA + 0x104)
#define ACPU_L2CC_DLTNCY_CTRL_VA   (ACPU_L2CC_BASE_VA + 0x10c)
#define ACPU_L2CC_PREFETCH_CTRL_VA (ACPU_L2CC_BASE_VA + 0xf60)
#define ACPU_L2CC_PWR_CTRL_VA      (ACPU_L2CC_BASE_VA + 0xf80)
#endif

/* GIC -- phy addr */
#define ACPU_GIC_ICC_BASE           (SOC_ACPU_A7_PRIVATE_BASE_ADDR + 0x2000)
#define ACPU_GIC_DIST_BASE          (SOC_ACPU_A7_PRIVATE_BASE_ADDR + 0x1000)
#define ACPU_GIC_ICCICR             (ACPU_GIC_ICC_BASE + 0x000)
#define ACPU_GIC_ICCPMR             (ACPU_GIC_ICC_BASE + 0x004)
#define ACPU_GIC_ICCBPR             (ACPU_GIC_ICC_BASE + 0x008)
#define ACPU_GIC_ICCEOIR            (ACPU_GIC_ICC_BASE + 0x010)
#define ACPU_GIC_ICABPR             (ACPU_GIC_ICC_BASE + 0x01C)

#define ACPU_GIC_ICDDCR             (ACPU_GIC_DIST_BASE + 0x000)
#define ACPU_GIC_ICDISR             (ACPU_GIC_DIST_BASE + 0x080)
#define ACPU_GIC_ICDISER            (ACPU_GIC_DIST_BASE + 0x100)
#define ACPU_GIC_ICDICER            (ACPU_GIC_DIST_BASE + 0x180)
#define ACPU_GIC_ICDISPR            (ACPU_GIC_DIST_BASE + 0x200)
#define ACPU_GIC_ICDICPR            (ACPU_GIC_DIST_BASE + 0x280)
#define ACPU_GIC_ICDABR             (ACPU_GIC_DIST_BASE + 0x300)
#define ACPU_GIC_ICDIPR             (ACPU_GIC_DIST_BASE + 0x400)
#define ACPU_GIC_ICDIPTR            (ACPU_GIC_DIST_BASE + 0x800)
#define ACPU_GIC_ICDICFR            (ACPU_GIC_DIST_BASE + 0xC00)
#define ACPU_GIC_ICDSGIR            (ACPU_GIC_DIST_BASE + 0xF00)

#define ACPU_GIC_ICDISER_OFFSET(x)  (ACPU_GIC_ICDISER  + ((x)*0x4))
#define ACPU_GIC_ICDABR_OFFSET(x)   (ACPU_GIC_ICDABR   + ((x)*0x4))
#define ACPU_GIC_ICDISPR_OFFSET(x)  (ACPU_GIC_ICDISPR  + ((x)*0x4))

/* GIC -- virtue addr */
#define ACPU_GIC_ICCICR_VA          IO_ADDRESS(ACPU_GIC_ICCICR)
#define ACPU_GIC_ICCPMR_VA          IO_ADDRESS(ACPU_GIC_ICCPMR)
#define ACPU_GIC_ICCBPR_VA          IO_ADDRESS(ACPU_GIC_ICCBPR)
#define ACPU_GIC_ICCEOIR_VA         IO_ADDRESS(ACPU_GIC_ICCEOIR)
#define ACPU_GIC_ICABPR_VA          IO_ADDRESS(ACPU_GIC_ICABPR)

#define ACPU_GIC_ICDDCR_VA          IO_ADDRESS(ACPU_GIC_ICDDCR)
#define ACPU_GIC_ICDISR_VA          IO_ADDRESS(ACPU_GIC_ICDISR)
#define ACPU_GIC_ICDISER_VA         IO_ADDRESS(ACPU_GIC_ICDISER)
#define ACPU_GIC_ICDICER_VA         IO_ADDRESS(ACPU_GIC_ICDICER)
#define ACPU_GIC_ICDISPR_VA         IO_ADDRESS(ACPU_GIC_ICDISPR)
#define ACPU_GIC_ICDICPR_VA         IO_ADDRESS(ACPU_GIC_ICDICPR)
#define ACPU_GIC_ICDABR_VA          IO_ADDRESS(ACPU_GIC_ICDABR)
#define ACPU_GIC_ICDIPR_VA          IO_ADDRESS(ACPU_GIC_ICDIPR)
#define ACPU_GIC_ICDICFR_VA         IO_ADDRESS(ACPU_GIC_ICDICFR)
#define ACPU_GIC_ICDSGIR_VA         IO_ADDRESS(ACPU_GIC_ICDSGIR)
#define ACPU_GIC_ICDIPTR_VA         IO_ADDRESS(ACPU_GIC_ICDIPTR)

#define ACPU_GIC_ICDISER_OFFSET_VA(x)  IO_ADDRESS(ACPU_GIC_ICDISER_OFFSET(x))
#define ACPU_GIC_ICDABR_OFFSET_VA(x)   IO_ADDRESS(ACPU_GIC_ICDABR_OFFSET(x))
#define ACPU_GIC_ICDISPR_OFFSET_VA(x)  IO_ADDRESS(ACPU_GIC_ICDISPR_OFFSET(x))

#if defined (WIN32) || defined (GENERIC_PROJECT)
/* for acore UT */
#define PWRCTRL_GET_GIC_STATUS(i)   (( s32_t )pwrctrl_read_reg32(ACPU_GIC_ICDISPR_OFFSET_VA(i)))
#else
#define PWRCTRL_GET_GIC_STATUS(i)   ((( s32_t )pwrctrl_read_reg32(ACPU_GIC_ICDISPR_OFFSET_VA(i)))  \
                                     & (( s32_t )pwrctrl_read_reg32(ACPU_GIC_ICDISER_OFFSET_VA(i))))
#endif

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


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/
extern u32_t g_aAcpuStoreReg[PWC_STORE_MEM_SIZE];
extern u32_t g_aAcpuHwVoteBaseAddr[];
extern ST_STORE_REG_ADDR_INFO g_aAcpuSocRegTable[];


/*****************************************************************************
  10 函数声明
*****************************************************************************/


extern s32_t pwrctrl_check_irq_pending_status ( void_t );
extern s32_t  pwrctrl_deep_sleep( void_t );
extern s32_t pwrctrl_l2c_disable( void_t );
extern s32_t pwrctrl_l2c_enable( void_t );
extern s32_t pwrctrl_restore_ip_reg( u32_t * addr);
extern s32_t pwrctrl_sleep_initial ( void_t );
extern s32_t pwrctrl_sleep_tele_vote_lock(u32_t teleModeId, u32_t enClientId);
extern s32_t pwrctrl_sleep_tele_vote_unlock( u32_t teleModeId, u32_t enClientId );
extern s32_t pwrctrl_sleep_tele_vote_wake_status(u32_t teleModeId);
extern s32_t pwrctrl_store_ip_reg ( u32_t * addr );
extern void_t pwrctrl_arm_init(void_t);
extern void_t pwrctrl_asm_mem_copy(void_t);
extern void_t pwrctrl_asm_deep_sleep_entry(void_t);
extern void_t pwrctrl_arm_dmb(void_t);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bsp_pwc_sleep.h */
