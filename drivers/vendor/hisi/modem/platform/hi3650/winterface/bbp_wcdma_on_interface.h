/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_wcdma_on_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-10-30 15:02:31
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月30日
    作    者   : p00277817
    修改内容   : 从《K3V5 MODEM寄存器手册_WCDMA_ON.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_WCDMA_ON_INTERFACE_H__
#define __BBP_WCDMA_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_ck_1
 ***======================================================================***/
/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   时钟测量小数部分，即ck_msr_counter除以ck_msr_period的小数部分。
             注意：DSP配置时，将测量结果乘以2048后配置给BBP使用。
   UNION结构:  WBBP_CK_MSR_FRAC_UNION */
#define WBBP_CK_MSR_FRAC_ADDR                         (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C08)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   时钟测量整数部分，即ck_msr_counter除以ck_msr_period的整数部分。
   UNION结构:  WBBP_CK_MSR_INTEGER_UNION */
#define WBBP_CK_MSR_INTEGER_ADDR                      (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C0C)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   产生深睡指示的10ms帧数，即表示在唤醒之前多长时间内，BBP产生深睡指示。单位，10ms。
   UNION结构:  WBBP_DEEP_SLEEP_THRESHOLD_UNION */
#define WBBP_DEEP_SLEEP_THRESHOLD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C2C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上报ARM的深睡指示。1，表示此时距离唤醒时刻的时间小于deep_sleep_threshold配置的时间；0，表示此时距离唤醒时刻的时间大于deep_sleep_threshold配置的时间。
   UNION结构:  WBBP_DEEP_SLEEP_IND_1CARD_UNION */
#define WBBP_DEEP_SLEEP_IND_1CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C30)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBP唤醒方式。1，表示CPU强制唤醒；0，表示BBP根据配置时刻唤醒。
   UNION结构:  WBBP_BBP_WAKEUP_TYPE_2CARD_UNION */
#define WBBP_BBP_WAKEUP_TYPE_2CARD_ADDR               (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C48)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBP睡眠查询标志。1，表示BBP处于睡眠状态；0，表示BBP处于唤醒状态。
   UNION结构:  WBBP_BBP_SLEEP_STATUS_2CARD_UNION */
#define WBBP_BBP_SLEEP_STATUS_2CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C4C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上报ARM的深睡指示。1，表示此时距离唤醒时刻的时间小于deep_sleep_threshold配置的时间；0，表示此时距离唤醒时刻的时间大于deep_sleep_threshold配置的时间。
   UNION结构:  WBBP_DEEP_SLEEP_IND_2CARD_UNION */
#define WBBP_DEEP_SLEEP_IND_2CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C50)

/* 寄存器说明：
 bit[31:28]  睡眠期间系统帧定时计数器slot计数值。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
 bit[27:16]  睡眠期间系统帧定时计数器chip计数值。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
 bit[15:12]  睡眠期间系统帧定时计数器clk计数值。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
 bit[11:0]   睡眠期间SFN。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
   UNION结构:  WBBP_SYS_CNT_SLEEP_2CARD_UNION */
#define WBBP_SYS_CNT_SLEEP_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C54)

/* 寄存器说明：
 bit[31:28]  睡眠期间系统帧定时计数器slot计数值。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
 bit[27:16]  睡眠期间系统帧定时计数器chip计数值。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
 bit[15:12]  睡眠期间系统帧定时计数器clk计数值。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
 bit[11:0]   睡眠期间SFN。
             注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。
   UNION结构:  WBBP_SYS_CNT_SLEEP_1CARD_UNION */
#define WBBP_SYS_CNT_SLEEP_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C64)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBP唤醒方式。1，表示CPU强制唤醒；0，表示BBP根据配置时刻唤醒。
   UNION结构:  WBBP_BBP_WAKEUP_TYPE_1CARD_UNION */
#define WBBP_BBP_WAKEUP_TYPE_1CARD_ADDR               (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C70)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBP睡眠查询标志。1，表示BBP处于睡眠状态；0，表示BBP处于唤醒状态。
   UNION结构:  WBBP_BBP_SLEEP_STATUS_1CARD_UNION */
#define WBBP_BBP_SLEEP_STATUS_1CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C74)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
   UNION结构:  WBBP_ARM_INT02_STA_UNION */
#define WBBP_ARM_INT02_STA_ADDR                       (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C80)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  WBBP_ARM_INT02_EN_UNION */
#define WBBP_ARM_INT02_EN_ADDR                        (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C88)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
   UNION结构:  WBBP_ARM_INT03_STA_UNION */
#define WBBP_ARM_INT03_STA_ADDR                       (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C90)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  WBBP_ARM_INT03_EN_UNION */
#define WBBP_ARM_INT03_EN_ADDR                        (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C98)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6]      Card2 DRX RST控制，控制IMI时钟域RST。
             复位时，将该bit置1，之后再将该bit复位为0。
 bit[5]      Card2 DRX RST控制，控制32k时钟域RST。
             复位时，将该bit置1，之后再将该bit复位为0。
 bit[4]      Card2 DRX RST控制，控制61M时钟域RST。
             复位时，将该bit置1，之后再将该bit复位为0。
 bit[3]      保留
 bit[2]      Card1 DRX RST控制，控制IMI时钟域RST。
             复位时，将该bit置1，之后再将该bit复位为0。
 bit[1]      Card1 DRX RST控制，控制32k时钟域RST。
             复位时，将该bit置1，之后再将该bit复位为0。
 bit[0]      Card1 DRX RST控制，控制61M时钟域RST。
             复位时，将该bit置1，之后再将该bit复位为0。
   UNION结构:  WBBP_DRX_RST_CON_UNION */
#define WBBP_DRX_RST_CON_ADDR                         (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CC0)

/* 寄存器说明：
 bit[31]     DRX态AFC值指示。
 bit[30:12]  保留
 bit[11:0]   DRX态AFC值。
   UNION结构:  WBBP_DRX_AFC_VALUE_UNION */
#define WBBP_DRX_AFC_VALUE_ADDR                       (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CC4)

/* 寄存器说明：
   详      述：唤醒后时钟切换中断比原来预定的时刻晚了多少32k时钟周期
   UNION结构 ：无 */
#define WBBP_SWITCH_DELAY_CNT_1CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CC8)

/* 寄存器说明：
   详      述：唤醒后时钟切换中断比原来预定的时刻晚了多少32k时钟周期
   UNION结构 ：无 */
#define WBBP_SWITCH_DELAY_CNT_2CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CCC)



/***======================================================================***
                     (2/3) register_define_ck_2
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      进入睡眠模式使能。1，表示BBP立即进入睡眠；0，无效。BBP内部将此信号处理为脉冲信号。
   UNION结构:  WBBP_SLEEP_EN_1CARD_UNION */
#define WBBP_SLEEP_EN_1CARD_ADDR                      (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C00)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      CPU强制唤醒使能。1，表示BBP立即唤醒；0，无效。BBP内部将此信号处理为脉冲信号。
   UNION结构:  WBBP_SWITCH_UP_1CARD_UNION */
#define WBBP_SWITCH_UP_1CARD_ADDR                     (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C04)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      自然唤醒流程中，DSP指示BBP产生时钟切换中断的配置。如果已经达到时钟切换时刻，而DSP没有配置此寄存器，则BBP继续维护32k定时，直到DSP配置此寄存器位置，再产生时钟切换中断
   UNION结构:  WBBP_DSP_READY_IND_1CARD_UNION */
#define WBBP_DSP_READY_IND_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C10)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   从唤醒时刻到时钟切换时刻32.768k时钟个数。
   UNION结构:  WBBP_CK_SWITCH_CNT_1CARD_UNION */
#define WBBP_CK_SWITCH_CNT_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C14)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   唤醒时刻SFN值。
   UNION结构:  WBBP_CK_WAKE_SFN_1CARD_UNION */
#define WBBP_CK_WAKE_SFN_1CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C18)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:16]  唤醒时刻帧内计数值slot计数。
 bit[15:4]   唤醒时刻帧内计数值chip计数。
 bit[3:0]    唤醒时刻帧内计数值clk计数。
   UNION结构:  WBBP_CK_WAKE_CNT_1CARD_UNION */
#define WBBP_CK_WAKE_CNT_1CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C1C)

/* 寄存器说明：
   详      述：自然唤醒流程中，预定时钟切换中断后，最多等待多长时间再产生时钟切换中断
   UNION结构 ：无 */
#define WBBP_SWITCH_DELAY_MAX_1CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C20)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
   UNION结构:  WBBP_ARM_INT02_MASK_1CARD_UNION */
#define WBBP_ARM_INT02_MASK_1CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C84)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构:  WBBP_ARM_INT02_CLR_1CARD_UNION */
#define WBBP_ARM_INT02_CLR_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C8C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
   UNION结构:  WBBP_ARM_INT03_MASK_1CARD_UNION */
#define WBBP_ARM_INT03_MASK_1CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C94)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构:  WBBP_ARM_INT03_CLR_1CARD_UNION */
#define WBBP_ARM_INT03_CLR_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C9C)



/***======================================================================***
                     (3/3) register_define_ck_3
 ***======================================================================***/
/* 寄存器说明：
   详      述：自然唤醒流程中，预定时钟切换中断后，最多等待多长时间再产生时钟切换中断
   UNION结构 ：无 */
#define WBBP_SWITCH_DELAY_MAX_2CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C24)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      进入睡眠模式使能。1，表示BBP立即进入睡眠；0，无效。BBP内部将此信号处理为脉冲信号。
   UNION结构:  WBBP_SLEEP_EN_2CARD_UNION */
#define WBBP_SLEEP_EN_2CARD_ADDR                      (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C34)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      CPU强制唤醒使能。1，表示BBP立即唤醒；0，无效。BBP内部将此信号处理为脉冲信号。
   UNION结构:  WBBP_SWITCH_UP_2CARD_UNION */
#define WBBP_SWITCH_UP_2CARD_ADDR                     (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C38)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   从唤醒时刻到时钟切换时刻32.768k时钟个数。
   UNION结构:  WBBP_CK_SWITCH_CNT_2CARD_UNION */
#define WBBP_CK_SWITCH_CNT_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C3C)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   唤醒时刻SFN值。
   UNION结构:  WBBP_CK_WAKE_SFN_2CARD_UNION */
#define WBBP_CK_WAKE_SFN_2CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C40)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:16]  唤醒时刻帧内计数值slot计数。
 bit[15:4]   唤醒时刻帧内计数值chip计数。
 bit[3:0]    唤醒时刻帧内计数值clk计数。
   UNION结构:  WBBP_CK_WAKE_CNT_2CARD_UNION */
#define WBBP_CK_WAKE_CNT_2CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C44)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      自然唤醒流程中，DSP指示BBP产生时钟切换中断的配置。如果已经达到时钟切换时刻，而DSP没有配置此寄存器，则BBP继续维护32k定时，直到DSP配置此寄存器位置，再产生时钟切换中断
   UNION结构:  WBBP_DSP_READY_IND_2CARD_UNION */
#define WBBP_DSP_READY_IND_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C68)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
 bit[0]      保留
   UNION结构:  WBBP_ARM_INT02_MASK_2CARD_UNION */
#define WBBP_ARM_INT02_MASK_2CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CA0)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
 bit[0]      保留
   UNION结构:  WBBP_ARM_INT02_CLR_2CARD_UNION */
#define WBBP_ARM_INT02_CLR_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CA4)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:2]    中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
 bit[1:0]    保留
   UNION结构:  WBBP_ARM_INT03_MASK_2CARD_UNION */
#define WBBP_ARM_INT03_MASK_2CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CA8)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:2]    中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
 bit[1:0]    保留
   UNION结构:  WBBP_ARM_INT03_CLR_2CARD_UNION */
#define WBBP_ARM_INT03_CLR_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CAC)





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

/***======================================================================***
                     (1/3) register_define_ck_1
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_CK_MSR_FRAC_UNION
 结构说明  : CK_MSR_FRAC 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_frac_reg;
    struct
    {
        unsigned long  ck_msr_frac : 11; /* bit[0-10] : 时钟测量小数部分，即ck_msr_counter除以ck_msr_period的小数部分。
                                                        注意：DSP配置时，将测量结果乘以2048后配置给BBP使用。 */
        unsigned long  reserved    : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_CK_MSR_FRAC_UNION;
#define WBBP_CK_MSR_FRAC_ck_msr_frac_START  (0)
#define WBBP_CK_MSR_FRAC_ck_msr_frac_END    (10)


/*****************************************************************************
 结构名    : WBBP_CK_MSR_INTEGER_UNION
 结构说明  : CK_MSR_INTEGER 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_integer_reg;
    struct
    {
        unsigned long  ck_msr_integer : 11; /* bit[0-10] : 时钟测量整数部分，即ck_msr_counter除以ck_msr_period的整数部分。 */
        unsigned long  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_CK_MSR_INTEGER_UNION;
#define WBBP_CK_MSR_INTEGER_ck_msr_integer_START  (0)
#define WBBP_CK_MSR_INTEGER_ck_msr_integer_END    (10)


/*****************************************************************************
 结构名    : WBBP_DEEP_SLEEP_THRESHOLD_UNION
 结构说明  : DEEP_SLEEP_THRESHOLD 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_threshold_reg;
    struct
    {
        unsigned long  deep_sleep_threshold : 12; /* bit[0-11] : 产生深睡指示的10ms帧数，即表示在唤醒之前多长时间内，BBP产生深睡指示。单位，10ms。 */
        unsigned long  reserved             : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_DEEP_SLEEP_THRESHOLD_UNION;
#define WBBP_DEEP_SLEEP_THRESHOLD_deep_sleep_threshold_START  (0)
#define WBBP_DEEP_SLEEP_THRESHOLD_deep_sleep_threshold_END    (11)


/*****************************************************************************
 结构名    : WBBP_DEEP_SLEEP_IND_1CARD_UNION
 结构说明  : DEEP_SLEEP_IND_1CARD 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_1card_reg;
    struct
    {
        unsigned long  deep_sleep_ind_1card : 1;  /* bit[0]   : 上报ARM的深睡指示。1，表示此时距离唤醒时刻的时间小于deep_sleep_threshold配置的时间；0，表示此时距离唤醒时刻的时间大于deep_sleep_threshold配置的时间。 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DEEP_SLEEP_IND_1CARD_UNION;
#define WBBP_DEEP_SLEEP_IND_1CARD_deep_sleep_ind_1card_START  (0)
#define WBBP_DEEP_SLEEP_IND_1CARD_deep_sleep_ind_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_BBP_WAKEUP_TYPE_2CARD_UNION
 结构说明  : BBP_WAKEUP_TYPE_2CARD 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_wakeup_type_2card_reg;
    struct
    {
        unsigned long  bbp_wakeup_type_2card : 1;  /* bit[0]   : BBP唤醒方式。1，表示CPU强制唤醒；0，表示BBP根据配置时刻唤醒。 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_BBP_WAKEUP_TYPE_2CARD_UNION;
#define WBBP_BBP_WAKEUP_TYPE_2CARD_bbp_wakeup_type_2card_START  (0)
#define WBBP_BBP_WAKEUP_TYPE_2CARD_bbp_wakeup_type_2card_END    (0)


/*****************************************************************************
 结构名    : WBBP_BBP_SLEEP_STATUS_2CARD_UNION
 结构说明  : BBP_SLEEP_STATUS_2CARD 寄存器结构定义。地址偏移量:0x4C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_sleep_status_2card_reg;
    struct
    {
        unsigned long  bbp_sleep_status_2card : 1;  /* bit[0]   : BBP睡眠查询标志。1，表示BBP处于睡眠状态；0，表示BBP处于唤醒状态。 */
        unsigned long  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_BBP_SLEEP_STATUS_2CARD_UNION;
#define WBBP_BBP_SLEEP_STATUS_2CARD_bbp_sleep_status_2card_START  (0)
#define WBBP_BBP_SLEEP_STATUS_2CARD_bbp_sleep_status_2card_END    (0)


/*****************************************************************************
 结构名    : WBBP_DEEP_SLEEP_IND_2CARD_UNION
 结构说明  : DEEP_SLEEP_IND_2CARD 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_2card_reg;
    struct
    {
        unsigned long  deep_sleep_ind_2card : 1;  /* bit[0]   : 上报ARM的深睡指示。1，表示此时距离唤醒时刻的时间小于deep_sleep_threshold配置的时间；0，表示此时距离唤醒时刻的时间大于deep_sleep_threshold配置的时间。 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DEEP_SLEEP_IND_2CARD_UNION;
#define WBBP_DEEP_SLEEP_IND_2CARD_deep_sleep_ind_2card_START  (0)
#define WBBP_DEEP_SLEEP_IND_2CARD_deep_sleep_ind_2card_END    (0)


/*****************************************************************************
 结构名    : WBBP_SYS_CNT_SLEEP_2CARD_UNION
 结构说明  : SYS_CNT_SLEEP_2CARD 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_sleep_2card_reg;
    struct
    {
        unsigned long  wake_sfn_2card      : 12; /* bit[0-11] : 睡眠期间SFN。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
        unsigned long  wake_cnt_2card_clk  : 4;  /* bit[12-15]: 睡眠期间系统帧定时计数器clk计数值。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
        unsigned long  wake_cnt_2card_chip : 12; /* bit[16-27]: 睡眠期间系统帧定时计数器chip计数值。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
        unsigned long  wake_cnt_2card_slot : 4;  /* bit[28-31]: 睡眠期间系统帧定时计数器slot计数值。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
    } reg;
} WBBP_SYS_CNT_SLEEP_2CARD_UNION;
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_sfn_2card_START       (0)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_sfn_2card_END         (11)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_clk_START   (12)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_clk_END     (15)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_chip_START  (16)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_chip_END    (27)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_slot_START  (28)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_slot_END    (31)


/*****************************************************************************
 结构名    : WBBP_SYS_CNT_SLEEP_1CARD_UNION
 结构说明  : SYS_CNT_SLEEP_1CARD 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_sleep_1card_reg;
    struct
    {
        unsigned long  wake_sfn_1card      : 12; /* bit[0-11] : 睡眠期间SFN。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
        unsigned long  wake_cnt_1card_clk  : 4;  /* bit[12-15]: 睡眠期间系统帧定时计数器clk计数值。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
        unsigned long  wake_cnt_1card_chip : 12; /* bit[16-27]: 睡眠期间系统帧定时计数器chip计数值。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
        unsigned long  wake_cnt_1card_slot : 4;  /* bit[28-31]: 睡眠期间系统帧定时计数器slot计数值。
                                                                注意：软件在查询时，需连续读取两次，如果两次的值相同，则表示获取的结果正确。 */
    } reg;
} WBBP_SYS_CNT_SLEEP_1CARD_UNION;
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_sfn_1card_START       (0)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_sfn_1card_END         (11)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_clk_START   (12)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_clk_END     (15)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_chip_START  (16)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_chip_END    (27)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_slot_START  (28)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_slot_END    (31)


/*****************************************************************************
 结构名    : WBBP_BBP_WAKEUP_TYPE_1CARD_UNION
 结构说明  : BBP_WAKEUP_TYPE_1CARD 寄存器结构定义。地址偏移量:0x70，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_wakeup_type_1card_reg;
    struct
    {
        unsigned long  bbp_wakeup_type_1card : 1;  /* bit[0]   : BBP唤醒方式。1，表示CPU强制唤醒；0，表示BBP根据配置时刻唤醒。 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_BBP_WAKEUP_TYPE_1CARD_UNION;
#define WBBP_BBP_WAKEUP_TYPE_1CARD_bbp_wakeup_type_1card_START  (0)
#define WBBP_BBP_WAKEUP_TYPE_1CARD_bbp_wakeup_type_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_BBP_SLEEP_STATUS_1CARD_UNION
 结构说明  : BBP_SLEEP_STATUS_1CARD 寄存器结构定义。地址偏移量:0x74，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_sleep_status_1card_reg;
    struct
    {
        unsigned long  bbp_sleep_status_1card : 1;  /* bit[0]   : BBP睡眠查询标志。1，表示BBP处于睡眠状态；0，表示BBP处于唤醒状态。 */
        unsigned long  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_BBP_SLEEP_STATUS_1CARD_UNION;
#define WBBP_BBP_SLEEP_STATUS_1CARD_bbp_sleep_status_1card_START  (0)
#define WBBP_BBP_SLEEP_STATUS_1CARD_bbp_sleep_status_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_ARM_INT02_STA_UNION
 结构说明  : ARM_INT02_STA 寄存器结构定义。地址偏移量:0x80，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_sta_reg;
    struct
    {
        unsigned long  arm_int02_sta : 2;  /* bit[0-1] : 中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。 */
        unsigned long  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_ARM_INT02_STA_UNION;
#define WBBP_ARM_INT02_STA_arm_int02_sta_START  (0)
#define WBBP_ARM_INT02_STA_arm_int02_sta_END    (1)


/*****************************************************************************
 结构名    : WBBP_ARM_INT02_EN_UNION
 结构说明  : ARM_INT02_EN 寄存器结构定义。地址偏移量:0x88，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_en_reg;
    struct
    {
        unsigned long  arm_int02_en : 1;  /* bit[0]   : 中断使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ARM_INT02_EN_UNION;
#define WBBP_ARM_INT02_EN_arm_int02_en_START  (0)
#define WBBP_ARM_INT02_EN_arm_int02_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_ARM_INT03_STA_UNION
 结构说明  : ARM_INT03_STA 寄存器结构定义。地址偏移量:0x90，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_sta_reg;
    struct
    {
        unsigned long  arm_int03_sta : 4;  /* bit[0-3] : 中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。 */
        unsigned long  reserved      : 28; /* bit[4-31]: 保留 */
    } reg;
} WBBP_ARM_INT03_STA_UNION;
#define WBBP_ARM_INT03_STA_arm_int03_sta_START  (0)
#define WBBP_ARM_INT03_STA_arm_int03_sta_END    (3)


/*****************************************************************************
 结构名    : WBBP_ARM_INT03_EN_UNION
 结构说明  : ARM_INT03_EN 寄存器结构定义。地址偏移量:0x98，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_en_reg;
    struct
    {
        unsigned long  arm_int03_en : 1;  /* bit[0]   : 中断使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ARM_INT03_EN_UNION;
#define WBBP_ARM_INT03_EN_arm_int03_en_START  (0)
#define WBBP_ARM_INT03_EN_arm_int03_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_DRX_RST_CON_UNION
 结构说明  : DRX_RST_CON 寄存器结构定义。地址偏移量:0xC0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_rst_con_reg;
    struct
    {
        unsigned long  drx_rst_control_1card_sys : 1;  /* bit[0]   : Card1 DRX RST控制，控制61M时钟域RST。
                                                                     复位时，将该bit置1，之后再将该bit复位为0。 */
        unsigned long  drx_rst_control_1card_32k : 1;  /* bit[1]   : Card1 DRX RST控制，控制32k时钟域RST。
                                                                     复位时，将该bit置1，之后再将该bit复位为0。 */
        unsigned long  drx_rst_control_1card_imi : 1;  /* bit[2]   : Card1 DRX RST控制，控制IMI时钟域RST。
                                                                     复位时，将该bit置1，之后再将该bit复位为0。 */
        unsigned long  reserved_0                : 1;  /* bit[3]   : 保留 */
        unsigned long  drx_rst_control_2card_sys : 1;  /* bit[4]   : Card2 DRX RST控制，控制61M时钟域RST。
                                                                     复位时，将该bit置1，之后再将该bit复位为0。 */
        unsigned long  drx_rst_control_2card_32k : 1;  /* bit[5]   : Card2 DRX RST控制，控制32k时钟域RST。
                                                                     复位时，将该bit置1，之后再将该bit复位为0。 */
        unsigned long  drx_rst_control_2card_imi : 1;  /* bit[6]   : Card2 DRX RST控制，控制IMI时钟域RST。
                                                                     复位时，将该bit置1，之后再将该bit复位为0。 */
        unsigned long  reserved_1                : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_DRX_RST_CON_UNION;
#define WBBP_DRX_RST_CON_drx_rst_control_1card_sys_START  (0)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_sys_END    (0)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_32k_START  (1)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_32k_END    (1)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_imi_START  (2)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_imi_END    (2)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_sys_START  (4)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_sys_END    (4)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_32k_START  (5)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_32k_END    (5)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_imi_START  (6)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_imi_END    (6)


/*****************************************************************************
 结构名    : WBBP_DRX_AFC_VALUE_UNION
 结构说明  : DRX_AFC_VALUE 寄存器结构定义。地址偏移量:0xC4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_afc_value_reg;
    struct
    {
        unsigned long  cpu_wdrx_afc_value : 12; /* bit[0-11] : DRX态AFC值。 */
        unsigned long  reserved           : 19; /* bit[12-30]: 保留 */
        unsigned long  cpu_wdrx_afc_ind   : 1;  /* bit[31]   : DRX态AFC值指示。 */
    } reg;
} WBBP_DRX_AFC_VALUE_UNION;
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_value_START  (0)
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_value_END    (11)
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_ind_START    (31)
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_ind_END      (31)


/***======================================================================***
                     (2/3) register_define_ck_2
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_SLEEP_EN_1CARD_UNION
 结构说明  : SLEEP_EN_1CARD 寄存器结构定义。地址偏移量:0x00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_en_1card_reg;
    struct
    {
        unsigned long  sleep_en_1card : 1;  /* bit[0]   : 进入睡眠模式使能。1，表示BBP立即进入睡眠；0，无效。BBP内部将此信号处理为脉冲信号。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_SLEEP_EN_1CARD_UNION;
#define WBBP_SLEEP_EN_1CARD_sleep_en_1card_START  (0)
#define WBBP_SLEEP_EN_1CARD_sleep_en_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_SWITCH_UP_1CARD_UNION
 结构说明  : SWITCH_UP_1CARD 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_1card_reg;
    struct
    {
        unsigned long  switch_up_1card : 1;  /* bit[0]   : CPU强制唤醒使能。1，表示BBP立即唤醒；0，无效。BBP内部将此信号处理为脉冲信号。 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_SWITCH_UP_1CARD_UNION;
#define WBBP_SWITCH_UP_1CARD_switch_up_1card_START  (0)
#define WBBP_SWITCH_UP_1CARD_switch_up_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_READY_IND_1CARD_UNION
 结构说明  : DSP_READY_IND_1CARD 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_1card_reg;
    struct
    {
        unsigned long  dsp_ready_ind_1card : 1;  /* bit[0]   : 自然唤醒流程中，DSP指示BBP产生时钟切换中断的配置。如果已经达到时钟切换时刻，而DSP没有配置此寄存器，则BBP继续维护32k定时，直到DSP配置此寄存器位置，再产生时钟切换中断 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_READY_IND_1CARD_UNION;
#define WBBP_DSP_READY_IND_1CARD_dsp_ready_ind_1card_START  (0)
#define WBBP_DSP_READY_IND_1CARD_dsp_ready_ind_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_CK_SWITCH_CNT_1CARD_UNION
 结构说明  : CK_SWITCH_CNT_1CARD 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_1card_reg;
    struct
    {
        unsigned long  ck_switch_cnt_1card : 12; /* bit[0-11] : 从唤醒时刻到时钟切换时刻32.768k时钟个数。 */
        unsigned long  reserved            : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_CK_SWITCH_CNT_1CARD_UNION;
#define WBBP_CK_SWITCH_CNT_1CARD_ck_switch_cnt_1card_START  (0)
#define WBBP_CK_SWITCH_CNT_1CARD_ck_switch_cnt_1card_END    (11)


/*****************************************************************************
 结构名    : WBBP_CK_WAKE_SFN_1CARD_UNION
 结构说明  : CK_WAKE_SFN_1CARD 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_sfn_1card_reg;
    struct
    {
        unsigned long  ck_wake_sfn_1card : 12; /* bit[0-11] : 唤醒时刻SFN值。 */
        unsigned long  reserved          : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_CK_WAKE_SFN_1CARD_UNION;
#define WBBP_CK_WAKE_SFN_1CARD_ck_wake_sfn_1card_START  (0)
#define WBBP_CK_WAKE_SFN_1CARD_ck_wake_sfn_1card_END    (11)


/*****************************************************************************
 结构名    : WBBP_CK_WAKE_CNT_1CARD_UNION
 结构说明  : CK_WAKE_CNT_1CARD 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_cnt_1card_reg;
    struct
    {
        unsigned long  ck_wake_cnt_1card_clk  : 4;  /* bit[0-3]  : 唤醒时刻帧内计数值clk计数。 */
        unsigned long  ck_wake_cnt_1card_chip : 12; /* bit[4-15] : 唤醒时刻帧内计数值chip计数。 */
        unsigned long  ck_wake_cnt_1card_slot : 4;  /* bit[16-19]: 唤醒时刻帧内计数值slot计数。 */
        unsigned long  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_CK_WAKE_CNT_1CARD_UNION;
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_clk_START   (0)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_clk_END     (3)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_chip_START  (4)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_chip_END    (15)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_slot_START  (16)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_slot_END    (19)


/*****************************************************************************
 结构名    : WBBP_ARM_INT02_MASK_1CARD_UNION
 结构说明  : ARM_INT02_MASK_1CARD 寄存器结构定义。地址偏移量:0x84，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_mask_1card_reg;
    struct
    {
        unsigned long  arm_int02_mask_1card : 1;  /* bit[0]   : 中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ARM_INT02_MASK_1CARD_UNION;
#define WBBP_ARM_INT02_MASK_1CARD_arm_int02_mask_1card_START  (0)
#define WBBP_ARM_INT02_MASK_1CARD_arm_int02_mask_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_ARM_INT02_CLR_1CARD_UNION
 结构说明  : ARM_INT02_CLR_1CARD 寄存器结构定义。地址偏移量:0x8C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_clr_1card_reg;
    struct
    {
        unsigned long  arm_int02_clr_1card : 1;  /* bit[0]   : 中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ARM_INT02_CLR_1CARD_UNION;
#define WBBP_ARM_INT02_CLR_1CARD_arm_int02_clr_1card_START  (0)
#define WBBP_ARM_INT02_CLR_1CARD_arm_int02_clr_1card_END    (0)


/*****************************************************************************
 结构名    : WBBP_ARM_INT03_MASK_1CARD_UNION
 结构说明  : ARM_INT03_MASK_1CARD 寄存器结构定义。地址偏移量:0x94，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_mask_1card_reg;
    struct
    {
        unsigned long  arm_int03_mask_1card : 2;  /* bit[0-1] : 中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。 */
        unsigned long  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_ARM_INT03_MASK_1CARD_UNION;
#define WBBP_ARM_INT03_MASK_1CARD_arm_int03_mask_1card_START  (0)
#define WBBP_ARM_INT03_MASK_1CARD_arm_int03_mask_1card_END    (1)


/*****************************************************************************
 结构名    : WBBP_ARM_INT03_CLR_1CARD_UNION
 结构说明  : ARM_INT03_CLR_1CARD 寄存器结构定义。地址偏移量:0x9C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_clr_1card_reg;
    struct
    {
        unsigned long  arm_int03_clr_1card : 2;  /* bit[0-1] : 中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_ARM_INT03_CLR_1CARD_UNION;
#define WBBP_ARM_INT03_CLR_1CARD_arm_int03_clr_1card_START  (0)
#define WBBP_ARM_INT03_CLR_1CARD_arm_int03_clr_1card_END    (1)


/***======================================================================***
                     (3/3) register_define_ck_3
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_SLEEP_EN_2CARD_UNION
 结构说明  : SLEEP_EN_2CARD 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_en_2card_reg;
    struct
    {
        unsigned long  sleep_en_2card : 1;  /* bit[0]   : 进入睡眠模式使能。1，表示BBP立即进入睡眠；0，无效。BBP内部将此信号处理为脉冲信号。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_SLEEP_EN_2CARD_UNION;
#define WBBP_SLEEP_EN_2CARD_sleep_en_2card_START  (0)
#define WBBP_SLEEP_EN_2CARD_sleep_en_2card_END    (0)


/*****************************************************************************
 结构名    : WBBP_SWITCH_UP_2CARD_UNION
 结构说明  : SWITCH_UP_2CARD 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_2card_reg;
    struct
    {
        unsigned long  switch_up_2card : 1;  /* bit[0]   : CPU强制唤醒使能。1，表示BBP立即唤醒；0，无效。BBP内部将此信号处理为脉冲信号。 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_SWITCH_UP_2CARD_UNION;
#define WBBP_SWITCH_UP_2CARD_switch_up_2card_START  (0)
#define WBBP_SWITCH_UP_2CARD_switch_up_2card_END    (0)


/*****************************************************************************
 结构名    : WBBP_CK_SWITCH_CNT_2CARD_UNION
 结构说明  : CK_SWITCH_CNT_2CARD 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_2card_reg;
    struct
    {
        unsigned long  ck_switch_cnt_2card : 12; /* bit[0-11] : 从唤醒时刻到时钟切换时刻32.768k时钟个数。 */
        unsigned long  reserved            : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_CK_SWITCH_CNT_2CARD_UNION;
#define WBBP_CK_SWITCH_CNT_2CARD_ck_switch_cnt_2card_START  (0)
#define WBBP_CK_SWITCH_CNT_2CARD_ck_switch_cnt_2card_END    (11)


/*****************************************************************************
 结构名    : WBBP_CK_WAKE_SFN_2CARD_UNION
 结构说明  : CK_WAKE_SFN_2CARD 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_sfn_2card_reg;
    struct
    {
        unsigned long  ck_wake_sfn_2card : 12; /* bit[0-11] : 唤醒时刻SFN值。 */
        unsigned long  reserved          : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_CK_WAKE_SFN_2CARD_UNION;
#define WBBP_CK_WAKE_SFN_2CARD_ck_wake_sfn_2card_START  (0)
#define WBBP_CK_WAKE_SFN_2CARD_ck_wake_sfn_2card_END    (11)


/*****************************************************************************
 结构名    : WBBP_CK_WAKE_CNT_2CARD_UNION
 结构说明  : CK_WAKE_CNT_2CARD 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_cnt_2card_reg;
    struct
    {
        unsigned long  ck_wake_cnt_2card_clk  : 4;  /* bit[0-3]  : 唤醒时刻帧内计数值clk计数。 */
        unsigned long  ck_wake_cnt_2card_chip : 12; /* bit[4-15] : 唤醒时刻帧内计数值chip计数。 */
        unsigned long  ck_wake_cnt_2card_slot : 4;  /* bit[16-19]: 唤醒时刻帧内计数值slot计数。 */
        unsigned long  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_CK_WAKE_CNT_2CARD_UNION;
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_clk_START   (0)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_clk_END     (3)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_chip_START  (4)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_chip_END    (15)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_slot_START  (16)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_slot_END    (19)


/*****************************************************************************
 结构名    : WBBP_DSP_READY_IND_2CARD_UNION
 结构说明  : DSP_READY_IND_2CARD 寄存器结构定义。地址偏移量:0x68，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_2card_reg;
    struct
    {
        unsigned long  dsp_ready_ind_2card : 1;  /* bit[0]   : 自然唤醒流程中，DSP指示BBP产生时钟切换中断的配置。如果已经达到时钟切换时刻，而DSP没有配置此寄存器，则BBP继续维护32k定时，直到DSP配置此寄存器位置，再产生时钟切换中断 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_READY_IND_2CARD_UNION;
#define WBBP_DSP_READY_IND_2CARD_dsp_ready_ind_2card_START  (0)
#define WBBP_DSP_READY_IND_2CARD_dsp_ready_ind_2card_END    (0)


/*****************************************************************************
 结构名    : WBBP_ARM_INT02_MASK_2CARD_UNION
 结构说明  : ARM_INT02_MASK_2CARD 寄存器结构定义。地址偏移量:0xA0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_mask_2card_reg;
    struct
    {
        unsigned long  reserved_0           : 1;  /* bit[0]   : 保留 */
        unsigned long  arm_int02_mask_2card : 1;  /* bit[1]   : 中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。 */
        unsigned long  reserved_1           : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_ARM_INT02_MASK_2CARD_UNION;
#define WBBP_ARM_INT02_MASK_2CARD_arm_int02_mask_2card_START  (1)
#define WBBP_ARM_INT02_MASK_2CARD_arm_int02_mask_2card_END    (1)


/*****************************************************************************
 结构名    : WBBP_ARM_INT02_CLR_2CARD_UNION
 结构说明  : ARM_INT02_CLR_2CARD 寄存器结构定义。地址偏移量:0xA4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_clr_2card_reg;
    struct
    {
        unsigned long  reserved_0          : 1;  /* bit[0]   : 保留 */
        unsigned long  arm_int02_clr_2card : 1;  /* bit[1]   : 中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved_1          : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_ARM_INT02_CLR_2CARD_UNION;
#define WBBP_ARM_INT02_CLR_2CARD_arm_int02_clr_2card_START  (1)
#define WBBP_ARM_INT02_CLR_2CARD_arm_int02_clr_2card_END    (1)


/*****************************************************************************
 结构名    : WBBP_ARM_INT03_MASK_2CARD_UNION
 结构说明  : ARM_INT03_MASK_2CARD 寄存器结构定义。地址偏移量:0xA8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_mask_2card_reg;
    struct
    {
        unsigned long  reserved_0           : 2;  /* bit[0-1] : 保留 */
        unsigned long  arm_int03_mask_2card : 2;  /* bit[2-3] : 中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。 */
        unsigned long  reserved_1           : 28; /* bit[4-31]: 保留 */
    } reg;
} WBBP_ARM_INT03_MASK_2CARD_UNION;
#define WBBP_ARM_INT03_MASK_2CARD_arm_int03_mask_2card_START  (2)
#define WBBP_ARM_INT03_MASK_2CARD_arm_int03_mask_2card_END    (3)


/*****************************************************************************
 结构名    : WBBP_ARM_INT03_CLR_2CARD_UNION
 结构说明  : ARM_INT03_CLR_2CARD 寄存器结构定义。地址偏移量:0xAC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_clr_2card_reg;
    struct
    {
        unsigned long  reserved_0          : 2;  /* bit[0-1] : 保留 */
        unsigned long  arm_int03_clr_2card : 2;  /* bit[2-3] : 中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved_1          : 28; /* bit[4-31]: 保留 */
    } reg;
} WBBP_ARM_INT03_CLR_2CARD_UNION;
#define WBBP_ARM_INT03_CLR_2CARD_arm_int03_clr_2card_START  (2)
#define WBBP_ARM_INT03_CLR_2CARD_arm_int03_clr_2card_END    (3)




/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bbp_wcdma_on_interface.h */
