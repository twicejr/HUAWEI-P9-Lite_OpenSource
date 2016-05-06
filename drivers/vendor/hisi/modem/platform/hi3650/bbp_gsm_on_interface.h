/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_gsm_on_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-10-30 15:06:49
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月30日
    作    者   : p00277817
    修改内容   : 从《K3V5 MODEM寄存器手册_GSM_ON.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSM_ON_INTERFACE_H__
#define __BBP_GSM_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_gdrx
 ***======================================================================***/
/* 寄存器说明：
 bit[31:28]  保留
 bit[27]     切换到104M中断输出，104M时钟域的脉冲信号，用于指示DRX睡眠结束之后唤醒ARM。
             产生条件：CPU立即唤醒、定时唤醒。
 bit[26]     保留
 bit[25]     GBBP到达定时休眠开始时刻产生的中断信号，一个104MHz脉冲信号。用于指示ARM切换到32KHz时钟。
 bit[24]     唤醒中断输出，32KHz时钟域的脉冲信号，用于DRX睡眠结束之后唤醒ARM。
             产生条件：定时唤醒。
             注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。
 bit[23:0]   保留
   UNION结构:  GBBP_DRX_CPU_INT_STA_UNION */
#define GBBP_DRX_CPU_INT_STA_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27]     时钟切换到104M中断输出屏蔽寄存器
 bit[26]     保留
 bit[25]     ARM指定的定时休眠开始之后发出的定时中断屏蔽寄存器
 bit[24]     唤醒中断屏蔽寄存器，1表示屏蔽，0表示打开屏蔽。
             注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。
 bit[23:0]   保留
   UNION结构:  GBBP_DRX_CPU_INT_MASK_UNION */
#define GBBP_DRX_CPU_INT_MASK_ADDR                    (SOC_BBP_GSM_ON_BASE_ADDR + 0x4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27]     时钟切换到104M中断输出清零寄存器
 bit[26]     保留
 bit[25]     ARM指定的定时休眠开始之后发出的定时中断清零寄存器
 bit[24]     唤醒中断清零寄存器
 bit[23:0]   保留
   UNION结构:  GBBP_DRX_CPU_INT_CLR_UNION */
#define GBBP_DRX_CPU_INT_CLR_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27]     切换到104M中断输出，104M时钟域的脉冲信号，用于指示DRX睡眠结束之后唤醒ARM。
             产生条件：CPU立即唤醒、定时唤醒。
 bit[26]     保留
 bit[25]     GBBP到达定时休眠开始时刻产生的中断信号，一个104MHz脉冲信号。用于指示ARM切换到32KHz时钟。
 bit[24]     唤醒中断输出，32KHz时钟域的脉冲信号，用于DRX睡眠结束之后唤醒ARM。
             产生条件：定时唤醒。
             注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。
 bit[23:0]   保留
   UNION结构:  GBBP_DRX_DSP_INT_STA_UNION */
#define GBBP_DRX_DSP_INT_STA_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x10)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27]     时钟切换到104M中断输出屏蔽寄存器
 bit[26]     保留
 bit[25]     ARM指定的定时休眠开始之后发出的定时中断屏蔽寄存器
 bit[24]     唤醒中断屏蔽寄存器，1表示屏蔽，0表示打开屏蔽。
             注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。
 bit[23:0]   保留
   UNION结构:  GBBP_DRX_DSP_INT_MASK_UNION */
#define GBBP_DRX_DSP_INT_MASK_ADDR                    (SOC_BBP_GSM_ON_BASE_ADDR + 0x14)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27]     时钟切换到104M中断输出清零寄存器
 bit[26]     保留
 bit[25]     ARM指定的定时休眠开始之后发出的定时中断清零寄存器
 bit[24]     唤醒中断清零寄存器
 bit[23:0]   保留
   UNION结构:  GBBP_DRX_DSP_INT_CLR_UNION */
#define GBBP_DRX_DSP_INT_CLR_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x18)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   ARM 104M中断延迟上报间隔时间参数，单位为imi_clk
   UNION结构:  GBBP_ARM_INT_DELAY_REG_PD_UNION */
#define GBBP_ARM_INT_DELAY_REG_PD_ADDR                (SOC_BBP_GSM_ON_BASE_ADDR + 0x1C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   PHY 104M中断延迟上报间隔时间参数，单位为imi_clk
   UNION结构:  GBBP_DSP_INT_DELAY_REG_PD_UNION */
#define GBBP_DSP_INT_DELAY_REG_PD_ADDR                (SOC_BBP_GSM_ON_BASE_ADDR + 0x28)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      bit[2] CPU立即唤醒GDRX使能，逻辑自清零。该信号配置前应先确保GBBP 104M系统时钟已经打开并且稳定。
 bit[1]      bit[1] 0：立即睡眠（默认），1：等到sleep_point时开始
 bit[0]      bit[0] DRX睡眠启动，写1开启，1个104MHz。写0无意义。
   UNION结构:  GBBP_SLEEP_EN_UNION */
#define GBBP_SLEEP_EN_ADDR                            (SOC_BBP_GSM_ON_BASE_ADDR + 0x30)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   bit[10:0] 上报唤醒中断到时钟切换时间内32.768k计数个数。
   UNION结构:  GBBP_WAKE_CNF_UNION */
#define GBBP_WAKE_CNF_ADDR                            (SOC_BBP_GSM_ON_BASE_ADDR + 0x34)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   睡眠到上报唤醒中断这段时间内32.768k计数个数，该配置值必需大于1。
   UNION结构:  GBBP_WAKEUP_LEN_UNION */
#define GBBP_WAKEUP_LEN_ADDR                          (SOC_BBP_GSM_ON_BASE_ADDR + 0x38)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  bit[29:24]睡眠计数96倍部分（指示1个32K有多少个96个104M钟的倍数）。
             注：参数gdrx_msr_timebase、gdrx_msr_integer和gdrx_msr_frac表示了一个32K时钟包含的104M时钟的个数，分别以x、y和z表示这三个参数的取值。
             经过时钟校准测量后可以得到一个32K时钟相当于m.n个104M时钟，m、n分别为整数和小数部分。它们之间有如下关系：m=x*96+y、n=z/2048。
             
 bit[23]     保留
 bit[22:16]  睡眠计数整数部分，少于96的104MHz时钟个数。
             和gdrx_msr_timebase一起表示了睡眠计数的全部整数部分。
             
 bit[15:11]  保留
 bit[10:0]   睡眠计数小数部分，该计数器的进位表示1个104M时钟。
   UNION结构:  GBBP_MSR_CNF_UNION */
#define GBBP_MSR_CNF_ADDR                             (SOC_BBP_GSM_ON_BASE_ADDR + 0x3C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:0]   AMR判断GBBP睡眠时间深度的门限值，当GDRX内部32K计数值大于该门限时，内部连线信号为1，通知ARM。
   UNION结构:  GBBP_CPU_DRX_DEPTH_CFG_UNION */
#define GBBP_CPU_DRX_DEPTH_CFG_ADDR                   (SOC_BBP_GSM_ON_BASE_ADDR + 0x40)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  DRX唤醒切换时加载到GTC的gtc_timebase计数值，测试用
 bit[15:7]   保留
 bit[6:0]    DRX唤醒切换时加载到GTC的FRAC计数值，测试用
   UNION结构:  GBBP_WAKE_GTC_QB_FRAC_RPT_UNION */
#define GBBP_WAKE_GTC_QB_FRAC_RPT_ADDR                (SOC_BBP_GSM_ON_BASE_ADDR + 0x50)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  DRX唤醒切换时加载到GTC的T3计数值，测试用
 bit[23:21]  保留
 bit[20:16]  DRX唤醒切换时加载到GTC的T2计数值，测试用
 bit[15:11]  保留
 bit[10:0]   DRX唤醒切换时加载到GTC的T1计数值，测试用
   UNION结构:  GBBP_WAKE_GTC_T1_T2_T3_RPT_UNION */
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_ADDR               (SOC_BBP_GSM_ON_BASE_ADDR + 0x54)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  DRX唤醒切换时加载到GTC的FN_HIGH计数值，测试用
 bit[15:11]  保留
 bit[10:0]   DRX唤醒切换时加载到GTC的FN_LOW计数值，测试用
   UNION结构:  GBBP_DRX_WAKE_GTC_FN_RPT_UNION */
#define GBBP_DRX_WAKE_GTC_FN_RPT_ADDR                 (SOC_BBP_GSM_ON_BASE_ADDR + 0x58)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20]     DRX模块中断屏蔽PHY配置值上报，DRX模块的中断屏蔽即是0xD1214寄存器bit24配置值，测试用
 bit[19:17]  保留
 bit[16]     DRX模块中断屏蔽ARM配置值上报，DRX模块的中断屏蔽即是0xd1204寄存器bit24配置值，测试用
 bit[15:5]   保留
 bit[4]      DRX模块中断状态上报PHY
             中断状态上报即是0x01200寄存器bit24上报值；，测试用
             
 bit[3:1]    保留
 bit[0]      DRX模块中断状态上报ARM
             中断状态上报即是0x01200寄存器bit24上报值； 测试用
             
   UNION结构:  GBBP_GDRX_INT_MASK_STATE_RPT_UNION */
#define GBBP_GDRX_INT_MASK_STATE_RPT_ADDR             (SOC_BBP_GSM_ON_BASE_ADDR + 0x5C)

/* 寄存器说明：
 bit[31]     GBBP模块输出的testpin选择信号，该信号为1时，选择非掉电区的GDRX的testpin，否则选择掉电区输出的test_pin
 bit[30:4]   保留
 bit[3:0]    GDRX模块测试引脚选择信号
   UNION结构:  GBBP_DRX_TEST_PIN_SEL_UNION */
#define GBBP_DRX_TEST_PIN_SEL_ADDR                    (SOC_BBP_GSM_ON_BASE_ADDR + 0x60)





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
                     (1/1) register_define_gdrx
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_DRX_CPU_INT_STA_UNION
 结构说明  : DRX_CPU_INT_STA 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_cpu_int_sta_reg;
    struct
    {
        unsigned long  reserved_0          : 24; /* bit[0-23] : 保留 */
        unsigned long  drx_int_state_cpu24 : 1;  /* bit[24]   : 唤醒中断输出，32KHz时钟域的脉冲信号，用于DRX睡眠结束之后唤醒ARM。
                                                                产生条件：定时唤醒。
                                                                注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。 */
        unsigned long  drx_int_state_cpu25 : 1;  /* bit[25]   : GBBP到达定时休眠开始时刻产生的中断信号，一个104MHz脉冲信号。用于指示ARM切换到32KHz时钟。 */
        unsigned long  reserved_1          : 1;  /* bit[26]   : 保留 */
        unsigned long  drx_int_state_cpu27 : 1;  /* bit[27]   : 切换到104M中断输出，104M时钟域的脉冲信号，用于指示DRX睡眠结束之后唤醒ARM。
                                                                产生条件：CPU立即唤醒、定时唤醒。 */
        unsigned long  reserved_2          : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_DRX_CPU_INT_STA_UNION;
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu24_START  (24)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu24_END    (24)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu25_START  (25)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu25_END    (25)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu27_START  (27)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu27_END    (27)


/*****************************************************************************
 结构名    : GBBP_DRX_CPU_INT_MASK_UNION
 结构说明  : DRX_CPU_INT_MASK 寄存器结构定义。地址偏移量:0x0004，初值:0x0B000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_cpu_int_mask_reg;
    struct
    {
        unsigned long  reserved_0         : 24; /* bit[0-23] : 保留 */
        unsigned long  cpu_drx_int_mask24 : 1;  /* bit[24]   : 唤醒中断屏蔽寄存器，1表示屏蔽，0表示打开屏蔽。
                                                               注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。 */
        unsigned long  cpu_drx_int_mask25 : 1;  /* bit[25]   : ARM指定的定时休眠开始之后发出的定时中断屏蔽寄存器 */
        unsigned long  reserved_1         : 1;  /* bit[26]   : 保留 */
        unsigned long  cpu_drx_int_mask27 : 1;  /* bit[27]   : 时钟切换到104M中断输出屏蔽寄存器 */
        unsigned long  reserved_2         : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_DRX_CPU_INT_MASK_UNION;
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask24_START  (24)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask24_END    (24)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask25_START  (25)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask25_END    (25)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask27_START  (27)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask27_END    (27)


/*****************************************************************************
 结构名    : GBBP_DRX_CPU_INT_CLR_UNION
 结构说明  : DRX_CPU_INT_CLR 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_cpu_int_clr_reg;
    struct
    {
        unsigned long  reserved_0        : 24; /* bit[0-23] : 保留 */
        unsigned long  cpu_drx_int_clr24 : 1;  /* bit[24]   : 唤醒中断清零寄存器 */
        unsigned long  cpu_drx_int_clr25 : 1;  /* bit[25]   : ARM指定的定时休眠开始之后发出的定时中断清零寄存器 */
        unsigned long  reserved_1        : 1;  /* bit[26]   : 保留 */
        unsigned long  cpu_drx_int_clr27 : 1;  /* bit[27]   : 时钟切换到104M中断输出清零寄存器 */
        unsigned long  reserved_2        : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_DRX_CPU_INT_CLR_UNION;
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr24_START  (24)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr24_END    (24)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr25_START  (25)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr25_END    (25)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr27_START  (27)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr27_END    (27)


/*****************************************************************************
 结构名    : GBBP_DRX_DSP_INT_STA_UNION
 结构说明  : DRX_DSP_INT_STA 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_dsp_int_sta_reg;
    struct
    {
        unsigned long  reserved_0          : 24; /* bit[0-23] : 保留 */
        unsigned long  drx_int_state_dsp24 : 1;  /* bit[24]   : 唤醒中断输出，32KHz时钟域的脉冲信号，用于DRX睡眠结束之后唤醒ARM。
                                                                产生条件：定时唤醒。
                                                                注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。 */
        unsigned long  drx_int_state_dsp25 : 1;  /* bit[25]   : GBBP到达定时休眠开始时刻产生的中断信号，一个104MHz脉冲信号。用于指示ARM切换到32KHz时钟。 */
        unsigned long  reserved_1          : 1;  /* bit[26]   : 保留 */
        unsigned long  drx_int_state_dsp27 : 1;  /* bit[27]   : 切换到104M中断输出，104M时钟域的脉冲信号，用于指示DRX睡眠结束之后唤醒ARM。
                                                                产生条件：CPU立即唤醒、定时唤醒。 */
        unsigned long  reserved_2          : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_DRX_DSP_INT_STA_UNION;
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp24_START  (24)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp24_END    (24)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp25_START  (25)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp25_END    (25)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp27_START  (27)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp27_END    (27)


/*****************************************************************************
 结构名    : GBBP_DRX_DSP_INT_MASK_UNION
 结构说明  : DRX_DSP_INT_MASK 寄存器结构定义。地址偏移量:0x0014，初值:0x0B000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_dsp_int_mask_reg;
    struct
    {
        unsigned long  reserved_0         : 24; /* bit[0-23] : 保留 */
        unsigned long  dsp_drx_int_mask24 : 1;  /* bit[24]   : 唤醒中断屏蔽寄存器，1表示屏蔽，0表示打开屏蔽。
                                                               注：CPU立即唤醒时需要软件屏蔽唤醒中断位，否则有可能收到无用的唤醒中断。 */
        unsigned long  dsp_drx_int_mask25 : 1;  /* bit[25]   : ARM指定的定时休眠开始之后发出的定时中断屏蔽寄存器 */
        unsigned long  reserved_1         : 1;  /* bit[26]   : 保留 */
        unsigned long  dsp_drx_int_mask27 : 1;  /* bit[27]   : 时钟切换到104M中断输出屏蔽寄存器 */
        unsigned long  reserved_2         : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_DRX_DSP_INT_MASK_UNION;
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask24_START  (24)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask24_END    (24)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask25_START  (25)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask25_END    (25)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask27_START  (27)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask27_END    (27)


/*****************************************************************************
 结构名    : GBBP_DRX_DSP_INT_CLR_UNION
 结构说明  : DRX_DSP_INT_CLR 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_dsp_int_clr_reg;
    struct
    {
        unsigned long  reserved_0        : 24; /* bit[0-23] : 保留 */
        unsigned long  dsp_drx_int_clr24 : 1;  /* bit[24]   : 唤醒中断清零寄存器 */
        unsigned long  dsp_drx_int_clr25 : 1;  /* bit[25]   : ARM指定的定时休眠开始之后发出的定时中断清零寄存器 */
        unsigned long  reserved_1        : 1;  /* bit[26]   : 保留 */
        unsigned long  dsp_drx_int_clr27 : 1;  /* bit[27]   : 时钟切换到104M中断输出清零寄存器 */
        unsigned long  reserved_2        : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_DRX_DSP_INT_CLR_UNION;
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr24_START  (24)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr24_END    (24)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr25_START  (25)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr25_END    (25)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr27_START  (27)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr27_END    (27)


/*****************************************************************************
 结构名    : GBBP_ARM_INT_DELAY_REG_PD_UNION
 结构说明  : ARM_INT_DELAY_REG_PD 寄存器结构定义。地址偏移量:0x001C，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int_delay_reg_pd_reg;
    struct
    {
        unsigned long  cpu_int_dly_clk : 16; /* bit[0-15] : ARM 104M中断延迟上报间隔时间参数，单位为imi_clk */
        unsigned long  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} GBBP_ARM_INT_DELAY_REG_PD_UNION;
#define GBBP_ARM_INT_DELAY_REG_PD_cpu_int_dly_clk_START  (0)
#define GBBP_ARM_INT_DELAY_REG_PD_cpu_int_dly_clk_END    (15)


/*****************************************************************************
 结构名    : GBBP_DSP_INT_DELAY_REG_PD_UNION
 结构说明  : DSP_INT_DELAY_REG_PD 寄存器结构定义。地址偏移量:0x0028，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_int_delay_reg_pd_reg;
    struct
    {
        unsigned long  dsp_int_dly_clk : 16; /* bit[0-15] : PHY 104M中断延迟上报间隔时间参数，单位为imi_clk */
        unsigned long  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} GBBP_DSP_INT_DELAY_REG_PD_UNION;
#define GBBP_DSP_INT_DELAY_REG_PD_dsp_int_dly_clk_START  (0)
#define GBBP_DSP_INT_DELAY_REG_PD_dsp_int_dly_clk_END    (15)


/*****************************************************************************
 结构名    : GBBP_SLEEP_EN_UNION
 结构说明  : SLEEP_EN 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_en_reg;
    struct
    {
        unsigned long  gdrx_sleep_en    : 1;  /* bit[0]   : bit[0] DRX睡眠启动，写1开启，1个104MHz。写0无意义。 */
        unsigned long  gdrx_sleep_mode  : 1;  /* bit[1]   : bit[1] 0：立即睡眠（默认），1：等到sleep_point时开始 */
        unsigned long  gdrx_wake_up_imi : 1;  /* bit[2]   : bit[2] CPU立即唤醒GDRX使能，逻辑自清零。该信号配置前应先确保GBBP 104M系统时钟已经打开并且稳定。 */
        unsigned long  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} GBBP_SLEEP_EN_UNION;
#define GBBP_SLEEP_EN_gdrx_sleep_en_START     (0)
#define GBBP_SLEEP_EN_gdrx_sleep_en_END       (0)
#define GBBP_SLEEP_EN_gdrx_sleep_mode_START   (1)
#define GBBP_SLEEP_EN_gdrx_sleep_mode_END     (1)
#define GBBP_SLEEP_EN_gdrx_wake_up_imi_START  (2)
#define GBBP_SLEEP_EN_gdrx_wake_up_imi_END    (2)


/*****************************************************************************
 结构名    : GBBP_WAKE_CNF_UNION
 结构说明  : WAKE_CNF 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wake_cnf_reg;
    struct
    {
        unsigned long  gdrx_switch_len : 11; /* bit[0-10] : bit[10:0] 上报唤醒中断到时钟切换时间内32.768k计数个数。 */
        unsigned long  reserved        : 21; /* bit[11-31]: 保留 */
    } reg;
} GBBP_WAKE_CNF_UNION;
#define GBBP_WAKE_CNF_gdrx_switch_len_START  (0)
#define GBBP_WAKE_CNF_gdrx_switch_len_END    (10)


/*****************************************************************************
 结构名    : GBBP_WAKEUP_LEN_UNION
 结构说明  : WAKEUP_LEN 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_len_reg;
    struct
    {
        unsigned long  gdrx_wakeup_len : 26; /* bit[0-25] : 睡眠到上报唤醒中断这段时间内32.768k计数个数，该配置值必需大于1。 */
        unsigned long  reserved        : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_WAKEUP_LEN_UNION;
#define GBBP_WAKEUP_LEN_gdrx_wakeup_len_START  (0)
#define GBBP_WAKEUP_LEN_gdrx_wakeup_len_END    (25)


/*****************************************************************************
 结构名    : GBBP_MSR_CNF_UNION
 结构说明  : MSR_CNF 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      msr_cnf_reg;
    struct
    {
        unsigned long  gdrx_msr_frac     : 11; /* bit[0-10] : 睡眠计数小数部分，该计数器的进位表示1个104M时钟。 */
        unsigned long  reserved_0        : 5;  /* bit[11-15]: 保留 */
        unsigned long  gdrx_msr_integer  : 7;  /* bit[16-22]: 睡眠计数整数部分，少于96的104MHz时钟个数。
                                                              和gdrx_msr_timebase一起表示了睡眠计数的全部整数部分。 */
        unsigned long  reserved_1        : 1;  /* bit[23]   : 保留 */
        unsigned long  gdrx_msr_timebase : 6;  /* bit[24-29]: bit[29:24]睡眠计数96倍部分（指示1个32K有多少个96个104M钟的倍数）。
                                                              注：参数gdrx_msr_timebase、gdrx_msr_integer和gdrx_msr_frac表示了一个32K时钟包含的104M时钟的个数，分别以x、y和z表示这三个参数的取值。
                                                              经过时钟校准测量后可以得到一个32K时钟相当于m.n个104M时钟，m、n分别为整数和小数部分。它们之间有如下关系：m=x*96+y、n=z/2048。 */
        unsigned long  reserved_2        : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_MSR_CNF_UNION;
#define GBBP_MSR_CNF_gdrx_msr_frac_START      (0)
#define GBBP_MSR_CNF_gdrx_msr_frac_END        (10)
#define GBBP_MSR_CNF_gdrx_msr_integer_START   (16)
#define GBBP_MSR_CNF_gdrx_msr_integer_END     (22)
#define GBBP_MSR_CNF_gdrx_msr_timebase_START  (24)
#define GBBP_MSR_CNF_gdrx_msr_timebase_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_DRX_DEPTH_CFG_UNION
 结构说明  : CPU_DRX_DEPTH_CFG 寄存器结构定义。地址偏移量:0x0040，初值:0x00000200，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_drx_depth_cfg_reg;
    struct
    {
        unsigned long  cpu_drx_depth : 27; /* bit[0-26] : AMR判断GBBP睡眠时间深度的门限值，当GDRX内部32K计数值大于该门限时，内部连线信号为1，通知ARM。 */
        unsigned long  reserved      : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_CPU_DRX_DEPTH_CFG_UNION;
#define GBBP_CPU_DRX_DEPTH_CFG_cpu_drx_depth_START  (0)
#define GBBP_CPU_DRX_DEPTH_CFG_cpu_drx_depth_END    (26)


/*****************************************************************************
 结构名    : GBBP_WAKE_GTC_QB_FRAC_RPT_UNION
 结构说明  : WAKE_GTC_QB_FRAC_RPT 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wake_gtc_qb_frac_rpt_reg;
    struct
    {
        unsigned long  gdrx_gtc_wake_frac : 7;  /* bit[0-6]  : DRX唤醒切换时加载到GTC的FRAC计数值，测试用 */
        unsigned long  reserved_0         : 9;  /* bit[7-15] : 保留 */
        unsigned long  gdrx_gtc_wake_chip : 13; /* bit[16-28]: DRX唤醒切换时加载到GTC的gtc_timebase计数值，测试用 */
        unsigned long  reserved_1         : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_WAKE_GTC_QB_FRAC_RPT_UNION;
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_frac_START  (0)
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_frac_END    (6)
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_chip_START  (16)
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_chip_END    (28)


/*****************************************************************************
 结构名    : GBBP_WAKE_GTC_T1_T2_T3_RPT_UNION
 结构说明  : WAKE_GTC_T1_T2_T3_RPT 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wake_gtc_t1_t2_t3_rpt_reg;
    struct
    {
        unsigned long  gdrx_gtc_t1_cnt : 11; /* bit[0-10] : DRX唤醒切换时加载到GTC的T1计数值，测试用 */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: 保留 */
        unsigned long  gdrx_gtc_t2_cnt : 5;  /* bit[16-20]: DRX唤醒切换时加载到GTC的T2计数值，测试用 */
        unsigned long  reserved_1      : 3;  /* bit[21-23]: 保留 */
        unsigned long  gdrx_gtc_t3_cnt : 6;  /* bit[24-29]: DRX唤醒切换时加载到GTC的T3计数值，测试用 */
        unsigned long  reserved_2      : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_WAKE_GTC_T1_T2_T3_RPT_UNION;
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t1_cnt_START  (0)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t1_cnt_END    (10)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t2_cnt_START  (16)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t2_cnt_END    (20)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t3_cnt_START  (24)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t3_cnt_END    (29)


/*****************************************************************************
 结构名    : GBBP_DRX_WAKE_GTC_FN_RPT_UNION
 结构说明  : DRX_WAKE_GTC_FN_RPT 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_wake_gtc_fn_rpt_reg;
    struct
    {
        unsigned long  gdrx_gtc_fn_low  : 11; /* bit[0-10] : DRX唤醒切换时加载到GTC的FN_LOW计数值，测试用 */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: 保留 */
        unsigned long  gdrx_gtc_fn_high : 11; /* bit[16-26]: DRX唤醒切换时加载到GTC的FN_HIGH计数值，测试用 */
        unsigned long  reserved_1       : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_DRX_WAKE_GTC_FN_RPT_UNION;
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_low_START   (0)
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_low_END     (10)
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_high_START  (16)
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_high_END    (26)


/*****************************************************************************
 结构名    : GBBP_GDRX_INT_MASK_STATE_RPT_UNION
 结构说明  : GDRX_INT_MASK_STATE_RPT 寄存器结构定义。地址偏移量:0x005C，初值:0x00110000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gdrx_int_mask_state_rpt_reg;
    struct
    {
        unsigned long  drx_int_state_cpu    : 1;  /* bit[0]    : DRX模块中断状态上报ARM
                                                                 中断状态上报即是0x01200寄存器bit24上报值； 测试用 */
        unsigned long  reserved_0           : 3;  /* bit[1-3]  : 保留 */
        unsigned long  drx_int_state_dsp    : 1;  /* bit[4]    : DRX模块中断状态上报PHY
                                                                 中断状态上报即是0x01200寄存器bit24上报值；，测试用 */
        unsigned long  reserved_1           : 11; /* bit[5-15] : 保留 */
        unsigned long  cpu_drx_int_mask_32k : 1;  /* bit[16]   : DRX模块中断屏蔽ARM配置值上报，DRX模块的中断屏蔽即是0xd1204寄存器bit24配置值，测试用 */
        unsigned long  reserved_2           : 3;  /* bit[17-19]: 保留 */
        unsigned long  dsp_drx_int_mask_32k : 1;  /* bit[20]   : DRX模块中断屏蔽PHY配置值上报，DRX模块的中断屏蔽即是0xD1214寄存器bit24配置值，测试用 */
        unsigned long  reserved_3           : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_GDRX_INT_MASK_STATE_RPT_UNION;
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_cpu_START     (0)
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_cpu_END       (0)
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_dsp_START     (4)
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_dsp_END       (4)
#define GBBP_GDRX_INT_MASK_STATE_RPT_cpu_drx_int_mask_32k_START  (16)
#define GBBP_GDRX_INT_MASK_STATE_RPT_cpu_drx_int_mask_32k_END    (16)
#define GBBP_GDRX_INT_MASK_STATE_RPT_dsp_drx_int_mask_32k_START  (20)
#define GBBP_GDRX_INT_MASK_STATE_RPT_dsp_drx_int_mask_32k_END    (20)


/*****************************************************************************
 结构名    : GBBP_DRX_TEST_PIN_SEL_UNION
 结构说明  : DRX_TEST_PIN_SEL 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_test_pin_sel_reg;
    struct
    {
        unsigned long  gdrx_test_pin_sel      : 4;  /* bit[0-3] : GDRX模块测试引脚选择信号 */
        unsigned long  reserved               : 27; /* bit[4-30]: 保留 */
        unsigned long  gdrx_test_pin_sel_flag : 1;  /* bit[31]  : GBBP模块输出的testpin选择信号，该信号为1时，选择非掉电区的GDRX的testpin，否则选择掉电区输出的test_pin */
    } reg;
} GBBP_DRX_TEST_PIN_SEL_UNION;
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_START       (0)
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_END         (3)
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_flag_START  (31)
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_flag_END    (31)




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

#endif /* end of bbp_gsm_on_interface.h */
