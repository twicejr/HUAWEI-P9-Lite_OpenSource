/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_aif_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:19:57
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_AIF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_AIF_INTERFACE_H__
#define __SOC_DSS_AIF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_AIF
 ****************************************************************************/
/* 寄存器说明：AIF通道0的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_0_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_0_ADDR(base)           ((base) + (0x0000))

/* 寄存器说明：AIF通道1的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_1_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_1_ADDR(base)           ((base) + (0x0020))

/* 寄存器说明：AIF通道2的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_2_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_2_ADDR(base)           ((base) + (0x0040))

/* 寄存器说明：AIF通道3的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_3_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_3_ADDR(base)           ((base) + (0x0060))

/* 寄存器说明：AIF通道4的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_4_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_4_ADDR(base)           ((base) + (0x0080))

/* 寄存器说明：AIF通道5的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_5_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_5_ADDR(base)           ((base) + (0x00a0))

/* 寄存器说明：AIF通道6的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_6_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_6_ADDR(base)           ((base) + (0x00c0))

/* 寄存器说明：AIF通道7的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_7_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_7_ADDR(base)           ((base) + (0x00e0))

/* 寄存器说明：AIF通道8的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_8_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_8_ADDR(base)           ((base) + (0x0100))

/* 寄存器说明：AIF通道9的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_9_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_9_ADDR(base)           ((base) + (0x0120))

/* 寄存器说明：AIF通道10的通道控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CH_CTL_10_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_10_ADDR(base)          ((base) + (0x0140))

/* 寄存器说明：AXI0 Read ID Mask
   位域定义UNION结构:  SOC_DSS_AIF_AXI0_RID_MSK0_UNION */
#define SOC_DSS_AIF_AXI0_RID_MSK0_ADDR(base)          ((base) + (0x0800))

/* 寄存器说明：AXI0 Read ID Mask
   位域定义UNION结构:  SOC_DSS_AIF_AXI0_RID_MSK1_UNION */
#define SOC_DSS_AIF_AXI0_RID_MSK1_ADDR(base)          ((base) + (0x0804))

/* 寄存器说明：AXI0 Read ID Mask
   位域定义UNION结构:  SOC_DSS_AIF_AXI0_WID_MSK_UNION */
#define SOC_DSS_AIF_AXI0_WID_MSK_ADDR(base)           ((base) + (0x0808))

/* 寄存器说明：AXI0 Read QOS remap
   位域定义UNION结构:  SOC_DSS_AIF_AXI0_R_QOS_MAP_UNION */
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_ADDR(base)         ((base) + (0x080c))

/* 寄存器说明：AXI1 Read ID Mask
   位域定义UNION结构:  SOC_DSS_AIF_AXI1_RID_MSK0_UNION */
#define SOC_DSS_AIF_AXI1_RID_MSK0_ADDR(base)          ((base) + (0x0810))

/* 寄存器说明：AXI1 Read ID Mask
   位域定义UNION结构:  SOC_DSS_AIF_AXI1_RID_MSK1_UNION */
#define SOC_DSS_AIF_AXI1_RID_MSK1_ADDR(base)          ((base) + (0x0814))

/* 寄存器说明：AXI1 Read ID Mask
   位域定义UNION结构:  SOC_DSS_AIF_AXI1_WID_MSK_UNION */
#define SOC_DSS_AIF_AXI1_WID_MSK_ADDR(base)           ((base) + (0x0818))

/* 寄存器说明：AXI1 Read QOS remap
   位域定义UNION结构:  SOC_DSS_AIF_AXI1_R_QOS_MAP_UNION */
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_ADDR(base)         ((base) + (0x081c))

/* 寄存器说明：AIF模块时钟选择
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CLK_SEL0_UNION */
#define SOC_DSS_AIF_AIF_CLK_SEL0_ADDR(base)           ((base) + (0x0820))

/* 寄存器说明：AIF模块时钟选择
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CLK_SEL1_UNION */
#define SOC_DSS_AIF_AIF_CLK_SEL1_ADDR(base)           ((base) + (0x0824))

/* 寄存器说明：AIF模块时钟使能
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CLK_EN0_UNION */
#define SOC_DSS_AIF_AIF_CLK_EN0_ADDR(base)            ((base) + (0x0828))

/* 寄存器说明：AIF模块时钟使能
   位域定义UNION结构:  SOC_DSS_AIF_AIF_CLK_EN1_UNION */
#define SOC_DSS_AIF_AIF_CLK_EN1_ADDR(base)            ((base) + (0x082c))

/* 寄存器说明：monitor控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_MONITOR_CTRL_UNION */
#define SOC_DSS_AIF_MONITOR_CTRL_ADDR(base)           ((base) + (0x0830))

/* 寄存器说明：monitor计时器初始值
   位域定义UNION结构:  SOC_DSS_AIF_MONITOR_TIMER_INI_UNION */
#define SOC_DSS_AIF_MONITOR_TIMER_INI_ADDR(base)      ((base) + (0x0834))

/* 寄存器说明：debug buffer基地址寄存器
   位域定义UNION结构:  SOC_DSS_AIF_DEBUG_BUF_BASE_UNION */
#define SOC_DSS_AIF_DEBUG_BUF_BASE_ADDR(base)         ((base) + (0x0838))

/* 寄存器说明：debug控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_DEBUG_CTRL_UNION */
#define SOC_DSS_AIF_DEBUG_CTRL_ADDR(base)             ((base) + (0x083C))

/* 寄存器说明：影子寄存器读选择寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_SHADOW_READ_UNION */
#define SOC_DSS_AIF_AIF_SHADOW_READ_ADDR(base)        ((base) + (0x0840))

/* 寄存器说明：AIF通道SRAM控制寄存器
   位域定义UNION结构:  SOC_DSS_AIF_AIF_MEM_CTRL_UNION */
#define SOC_DSS_AIF_AIF_MEM_CTRL_ADDR(base)           ((base) + (0x0844))

/* 寄存器说明：AXI recorder part a
   位域定义UNION结构:  SOC_DSS_AIF_AXI_REC_A_m_UNION */
#define SOC_DSS_AIF_AXI_REC_A_m_ADDR(base, m)         ((base) + (0x0880+0x10*(m)))

/* 寄存器说明：AXI recorder part b
   位域定义UNION结构:  SOC_DSS_AIF_AXI_REC_B_m_UNION */
#define SOC_DSS_AIF_AXI_REC_B_m_ADDR(base, m)         ((base) + (0x0884+0x10*(m)))

/* 寄存器说明：AXI recorder part c
   位域定义UNION结构:  SOC_DSS_AIF_AXI_REC_C_m_UNION */
#define SOC_DSS_AIF_AXI_REC_C_m_ADDR(base, m)         ((base) + (0x0888+0x10*(m)))

/* 寄存器说明：AXI recorder part d
   位域定义UNION结构:  SOC_DSS_AIF_AXI_REC_D_m_UNION */
#define SOC_DSS_AIF_AXI_REC_D_m_ADDR(base, m)         ((base) + (0x088C+0x10*(m)))





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

/****************************************************************************
                     (1/1) reg_AIF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_0_UNION
 结构说明  : AIF_CH_CTL_0 寄存器结构定义。地址偏移量:0x0000，初值:0x0000，宽度:32
 寄存器说明: AIF通道0的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode等于1或者2时，最大连续命令个数 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved    : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode等于1或者2时，限流下阈值。单位是16Bytes。 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_0_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_0_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_0_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_0_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_lth_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_1_UNION
 结构说明  : AIF_CH_CTL_1 寄存器结构定义。地址偏移量:0x0020，初值:0x0000，宽度:32
 寄存器说明: AIF通道1的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : 保留 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved_1  : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: 保留 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_1_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_1_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_1_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_1_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_1_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_1_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_step_END    (22)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_2_UNION
 结构说明  : AIF_CH_CTL_2 寄存器结构定义。地址偏移量:0x0040，初值:0x0000，宽度:32
 寄存器说明: AIF通道2的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode等于1或者2时，最大连续命令个数 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved    : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode等于1或者2时，限流下阈值。单位是16Bytes。 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_2_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_2_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_2_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_2_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_2_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_lth_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_3_UNION
 结构说明  : AIF_CH_CTL_3 寄存器结构定义。地址偏移量:0x0060，初值:0x0000，宽度:32
 寄存器说明: AIF通道3的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode等于1或者2时，最大连续命令个数 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved    : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode等于1或者2时，限流下阈值。单位是16Bytes。 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_3_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_3_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_3_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_3_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_3_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_lth_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_4_UNION
 结构说明  : AIF_CH_CTL_4 寄存器结构定义。地址偏移量:0x0080，初值:0x0000，宽度:32
 寄存器说明: AIF通道4的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode等于1或者2时，最大连续命令个数 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved    : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode等于1或者2时，限流下阈值。单位是16Bytes。 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_4_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_4_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_4_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_4_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_4_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_lth_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_5_UNION
 结构说明  : AIF_CH_CTL_5 寄存器结构定义。地址偏移量:0x00a0，初值:0x0000，宽度:32
 寄存器说明: AIF通道5的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode等于1或者2时，最大连续命令个数 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved    : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode等于1或者2时，限流下阈值。单位是16Bytes。 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_5_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_5_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_5_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_5_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_5_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_lth_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_6_UNION
 结构说明  : AIF_CH_CTL_6 寄存器结构定义。地址偏移量:0x00c0，初值:0x0000，宽度:32
 寄存器说明: AIF通道6的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : 保留 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved_1  : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: 保留 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_6_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_6_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_6_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_6_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_6_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_6_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_6_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_step_END    (22)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_7_UNION
 结构说明  : AIF_CH_CTL_7 寄存器结构定义。地址偏移量:0x00e0，初值:0x0000，宽度:32
 寄存器说明: AIF通道7的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : 保留 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved_1  : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: 保留 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_7_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_7_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_7_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_7_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_7_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_7_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_7_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_step_END    (22)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_8_UNION
 结构说明  : AIF_CH_CTL_8 寄存器结构定义。地址偏移量:0x0100，初值:0x0000，宽度:32
 寄存器说明: AIF通道8的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode等于1或者2时，最大连续命令个数 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved    : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode等于1或者2时，限流下阈值。单位是16Bytes。 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_8_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_8_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_8_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_8_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_8_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_lth_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_9_UNION
 结构说明  : AIF_CH_CTL_9 寄存器结构定义。地址偏移量:0x0120，初值:0x0000，宽度:32
 寄存器说明: AIF通道9的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode等于1或者2时，最大连续命令个数 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved    : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode等于1或者2时，限流下阈值。单位是16Bytes。 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_9_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_9_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_9_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_9_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_9_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_lth_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CH_CTL_10_UNION
 结构说明  : AIF_CH_CTL_10 寄存器结构定义。地址偏移量:0x0140，初值:0x0000，宽度:32
 寄存器说明: AIF通道10的通道控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI端口选择：
                                                       0：选择AXI0；
                                                       1：选择AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : 保留 */
        unsigned int  mid         : 4;  /* bit[4-7]  : 通道的MID。
                                                       0x0~0x9：有效配置值；
                                                       0xA~0xF：禁止配置，会对整个系统造成不可预知的后果； */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : 流量模式。
                                                       0x0：普通模式
                                                       0x1：afbc模式，读通道无效；
                                                       0x2：流控模式
                                                       0x3：无效值； */
        unsigned int  reserved_1  : 1;  /* bit[10]   : 保留 */
        unsigned int  credit_en   : 1;  /* bit[11]   : 流量控制使能。
                                                       0：通道流量控制禁止，max_cont和credit_step配置值无效；
                                                       1：通道流量控制使能，max_cont和credit_step配置值有效； */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod等于0时，命令序列最大长度。
                                                       0x0：命令序列最大长度等于1；
                                                       0x1：命令序列最大长度等于2；
                                                       ……
                                                       0xF：命令序列最大长度等于16；
                                                       credit_mode等于1或者2时，表示限流上限值。
                                                       单位是512Bytes，此时支持0x0-0xE； */
        unsigned int  credit_step : 7;  /* bit[16-22]: 通道流量控制：
                                                       0x0：通道只做命令序列最大长度控制；
                                                       0x1：1/128*通道最大带宽；
                                                       0x2：2/128*通道最大带宽； 
                                                       0x3：3/128*通道最大带宽； 
                                                       0x4：4/128*通道最大带宽；
                                                       0x5：5/128*通道最大带宽；
                                                       0x6：6/128*通道最大带宽；
                                                       0x7：7/128*通道最大带宽；
                                                       0x8：8/128*通道最大带宽；
                                                       …… 
                                                       0xFF：127/128*通道最大带宽； */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: 保留 */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_10_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_10_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_10_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_10_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_10_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_10_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_10_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_step_END    (22)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI0_RID_MSK0_UNION
 结构说明  : AXI0_RID_MSK0 寄存器结构定义。地址偏移量:0x0800，初值:0xFFFFFFFF，宽度:32
 寄存器说明: AXI0 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_rid_msk0 : 32; /* bit[0-31]: AXI0读端口ID_MAP的0~31bit Mask位：为0表示对应的ID不被分配，为1表示对应的ID可分配。 */
    } reg;
} SOC_DSS_AIF_AXI0_RID_MSK0_UNION;
#endif
#define SOC_DSS_AIF_AXI0_RID_MSK0_axi0_rid_msk0_START  (0)
#define SOC_DSS_AIF_AXI0_RID_MSK0_axi0_rid_msk0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI0_RID_MSK1_UNION
 结构说明  : AXI0_RID_MSK1 寄存器结构定义。地址偏移量:0x0804，初值:0x0000FFFF，宽度:32
 寄存器说明: AXI0 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_rid_msk1 : 32; /* bit[0-31]: AXI0读端口ID_MAP的31~63bit Mask位：为0表示对应的ID不被分配，为1表示对应的ID可分配。 */
    } reg;
} SOC_DSS_AIF_AXI0_RID_MSK1_UNION;
#endif
#define SOC_DSS_AIF_AXI0_RID_MSK1_axi0_rid_msk1_START  (0)
#define SOC_DSS_AIF_AXI0_RID_MSK1_axi0_rid_msk1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI0_WID_MSK_UNION
 结构说明  : AXI0_WID_MSK 寄存器结构定义。地址偏移量:0x0808，初值:0x0000FFFF，宽度:32
 寄存器说明: AXI0 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_wid_msk : 32; /* bit[0-31]: AXI0读端口ID_MAP的0~31bit Mask位：为0表示对应的ID不被分配，为1表示对应的ID可分配。 */
    } reg;
} SOC_DSS_AIF_AXI0_WID_MSK_UNION;
#endif
#define SOC_DSS_AIF_AXI0_WID_MSK_axi0_wid_msk_START  (0)
#define SOC_DSS_AIF_AXI0_WID_MSK_axi0_wid_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI0_R_QOS_MAP_UNION
 结构说明  : AXI0_R_QOS_MAP 寄存器结构定义。地址偏移量:0x080c，初值:0xE4E4E4E4，宽度:32
 寄存器说明: AXI0 Read QOS remap
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_rd_qos_map : 8;  /* bit[0-7]  : AXI0读端口QOS重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
        unsigned int  axi0_wr_qos_map : 8;  /* bit[8-15] : AXI0写端口QOS重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
        unsigned int  axi0_rd_prs_map : 8;  /* bit[16-23]: AXI0读端口Mainpress重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
        unsigned int  axi0_wr_prs_map : 8;  /* bit[24-31]: AXI0写端口Mainpress重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
    } reg;
} SOC_DSS_AIF_AXI0_R_QOS_MAP_UNION;
#endif
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_qos_map_START  (0)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_qos_map_END    (7)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_qos_map_START  (8)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_qos_map_END    (15)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_prs_map_START  (16)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_prs_map_END    (23)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_prs_map_START  (24)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_prs_map_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI1_RID_MSK0_UNION
 结构说明  : AXI1_RID_MSK0 寄存器结构定义。地址偏移量:0x0810，初值:0xFFFFFFFF，宽度:32
 寄存器说明: AXI1 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_rid_msk0 : 32; /* bit[0-31]: AXI1读端口ID_MAP的0~31bit Mask位：为0表示对应的ID不被分配，为1表示对应的ID可分配。 */
    } reg;
} SOC_DSS_AIF_AXI1_RID_MSK0_UNION;
#endif
#define SOC_DSS_AIF_AXI1_RID_MSK0_axi1_rid_msk0_START  (0)
#define SOC_DSS_AIF_AXI1_RID_MSK0_axi1_rid_msk0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI1_RID_MSK1_UNION
 结构说明  : AXI1_RID_MSK1 寄存器结构定义。地址偏移量:0x0814，初值:0x0000FFFF，宽度:32
 寄存器说明: AXI1 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_rid_msk1 : 32; /* bit[0-31]: AXI1读端口ID_MAP的31~63bit Mask位：为0表示对应的ID不被分配，为1表示对应的ID可分配。 */
    } reg;
} SOC_DSS_AIF_AXI1_RID_MSK1_UNION;
#endif
#define SOC_DSS_AIF_AXI1_RID_MSK1_axi1_rid_msk1_START  (0)
#define SOC_DSS_AIF_AXI1_RID_MSK1_axi1_rid_msk1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI1_WID_MSK_UNION
 结构说明  : AXI1_WID_MSK 寄存器结构定义。地址偏移量:0x0818，初值:0x0000FFFF，宽度:32
 寄存器说明: AXI1 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_wid_msk : 32; /* bit[0-31]: AXI1写端口ID_MAP的0~31bit Mask位：为0表示对应的ID不被分配，为1表示对应的ID可分配。 */
    } reg;
} SOC_DSS_AIF_AXI1_WID_MSK_UNION;
#endif
#define SOC_DSS_AIF_AXI1_WID_MSK_axi1_wid_msk_START  (0)
#define SOC_DSS_AIF_AXI1_WID_MSK_axi1_wid_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI1_R_QOS_MAP_UNION
 结构说明  : AXI1_R_QOS_MAP 寄存器结构定义。地址偏移量:0x081c，初值:0xE4E4E4E4，宽度:32
 寄存器说明: AXI1 Read QOS remap
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_rd_qos_map : 8;  /* bit[0-7]  : AXI1读端口QOS重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
        unsigned int  axi1_wr_qos_map : 8;  /* bit[8-15] : AXI0写端口QOS重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
        unsigned int  axi1_rd_prs_map : 8;  /* bit[16-23]: AXI0读端口Mainpress重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
        unsigned int  axi1_wr_prs_map : 8;  /* bit[24-31]: AXI0写端口Mainpress重映射表。
                                                           [1:0]：输入为2'b00时的映射值；
                                                           [3:2]：输入为2'b01时的映射值；
                                                           [5:4]：输入为2'b10时的映射值；
                                                           [7:6]: 输入为2'b11时的映射值。 */
    } reg;
} SOC_DSS_AIF_AXI1_R_QOS_MAP_UNION;
#endif
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_qos_map_START  (0)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_qos_map_END    (7)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_qos_map_START  (8)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_qos_map_END    (15)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_prs_map_START  (16)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_prs_map_END    (23)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_prs_map_START  (24)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_prs_map_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CLK_SEL0_UNION
 结构说明  : AIF_CLK_SEL0 寄存器结构定义。地址偏移量:0x0820，初值:0xFFFFFFFF，宽度:32
 寄存器说明: AIF模块时钟选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_sel0 : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                       1：表示强制打开时钟。
                                                       0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟 */
    } reg;
} SOC_DSS_AIF_AIF_CLK_SEL0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_SEL0_aif_clk_sel0_START  (0)
#define SOC_DSS_AIF_AIF_CLK_SEL0_aif_clk_sel0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CLK_SEL1_UNION
 结构说明  : AIF_CLK_SEL1 寄存器结构定义。地址偏移量:0x0824，初值:0xFFFFFFFF，宽度:32
 寄存器说明: AIF模块时钟选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_sel1 : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                       1：表示强制打开时钟。
                                                       0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟 */
    } reg;
} SOC_DSS_AIF_AIF_CLK_SEL1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_SEL1_aif_clk_sel1_START  (0)
#define SOC_DSS_AIF_AIF_CLK_SEL1_aif_clk_sel1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CLK_EN0_UNION
 结构说明  : AIF_CLK_EN0 寄存器结构定义。地址偏移量:0x0828，初值:0xFFFFFFFF，宽度:32
 寄存器说明: AIF模块时钟使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_en0 : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                      1：表示软件时钟使能有效，允许硬件开钟
                                                      0：表示软件时钟使能无效，禁止硬件开钟 */
    } reg;
} SOC_DSS_AIF_AIF_CLK_EN0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_EN0_aif_clk_en0_START  (0)
#define SOC_DSS_AIF_AIF_CLK_EN0_aif_clk_en0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_CLK_EN1_UNION
 结构说明  : AIF_CLK_EN1 寄存器结构定义。地址偏移量:0x082c，初值:0xFFFFFFFF，宽度:32
 寄存器说明: AIF模块时钟使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_en1 : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                      1：表示软件时钟使能有效，允许硬件开钟
                                                      0：表示软件时钟使能无效，禁止硬件开钟 */
    } reg;
} SOC_DSS_AIF_AIF_CLK_EN1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_EN1_aif_clk_en1_START  (0)
#define SOC_DSS_AIF_AIF_CLK_EN1_aif_clk_en1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_MONITOR_CTRL_UNION
 结构说明  : MONITOR_CTRL 寄存器结构定义。地址偏移量:0x0830，初值:0x00000000，宽度:32
 寄存器说明: monitor控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_run      : 1;  /* bit[0]   : monitor使能。
                                                           0：monitor不使能；
                                                           1：monitor使能； */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : 保留。 */
        unsigned int  monitor_streamid : 4;  /* bit[4-7] : monitor对应的streamid */
        unsigned int  reserved_1       : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_AIF_MONITOR_CTRL_UNION;
#endif
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_run_START       (0)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_run_END         (0)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_streamid_START  (4)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_streamid_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_MONITOR_TIMER_INI_UNION
 结构说明  : MONITOR_TIMER_INI 寄存器结构定义。地址偏移量:0x0834，初值:0x00000000，宽度:32
 寄存器说明: monitor计时器初始值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_ini : 32; /* bit[0-31]: monitor计时器初始值 */
    } reg;
} SOC_DSS_AIF_MONITOR_TIMER_INI_UNION;
#endif
#define SOC_DSS_AIF_MONITOR_TIMER_INI_monitor_ini_START  (0)
#define SOC_DSS_AIF_MONITOR_TIMER_INI_monitor_ini_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_DEBUG_BUF_BASE_UNION
 结构说明  : DEBUG_BUF_BASE 寄存器结构定义。地址偏移量:0x0838，初值:0x00000000，宽度:32
 寄存器说明: debug buffer基地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved   : 4;  /* bit[0-3] : 保留 */
        unsigned int  debug_base : 28; /* bit[4-31]: debug buffer基地址，16Bytes对齐。 */
    } reg;
} SOC_DSS_AIF_DEBUG_BUF_BASE_UNION;
#endif
#define SOC_DSS_AIF_DEBUG_BUF_BASE_debug_base_START  (4)
#define SOC_DSS_AIF_DEBUG_BUF_BASE_debug_base_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_DEBUG_CTRL_UNION
 结构说明  : DEBUG_CTRL 寄存器结构定义。地址偏移量:0x083C，初值:0x00000000，宽度:32
 寄存器说明: debug控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_en    : 1;  /* bit[0]    : debug DMA使能 */
        unsigned int  reserved    : 15; /* bit[1-15] : 保留 */
        unsigned int  debug_depth : 16; /* bit[16-31]: debug深度-1，深度必须16Bytes对齐。 */
    } reg;
} SOC_DSS_AIF_DEBUG_CTRL_UNION;
#endif
#define SOC_DSS_AIF_DEBUG_CTRL_debug_en_START     (0)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_en_END       (0)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_depth_START  (16)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_depth_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_SHADOW_READ_UNION
 结构说明  : AIF_SHADOW_READ 寄存器结构定义。地址偏移量:0x0840，初值:0x00000000，宽度:32
 寄存器说明: 影子寄存器读选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_rd_shadow : 1;  /* bit[0]   : 1'b0 :读工作寄存器
                                                        1'b1 :读影子寄存器 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_AIF_AIF_SHADOW_READ_UNION;
#endif
#define SOC_DSS_AIF_AIF_SHADOW_READ_aif_rd_shadow_START  (0)
#define SOC_DSS_AIF_AIF_SHADOW_READ_aif_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AIF_MEM_CTRL_UNION
 结构说明  : AIF_MEM_CTRL 寄存器结构定义。地址偏移量:0x0844，初值:0x00000A18，宽度:32
 寄存器说明: AIF通道SRAM控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl : 16; /* bit[0-15] : Two Port类型MEM低功耗软件配置模式下有效：
                                                    [9:7]: KP,默认为3'b011;
                                                    [6:5]: WCT,默认为2'b01;
                                                    [4:3]: RCT,默认为2'b01;;
                                                    [2]: 为1表示进入Shut Down模式
                                                    [1]: 为1表示进入Deep Sleep模式
                                                    [0]: 为1表示进入Sleep模式 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_AIF_AIF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_AIF_AIF_MEM_CTRL_mem_ctrl_START  (0)
#define SOC_DSS_AIF_AIF_MEM_CTRL_mem_ctrl_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI_REC_A_m_UNION
 结构说明  : AXI_REC_A_m 寄存器结构定义。地址偏移量:0x0880+0x10*(m)，初值:0x00000000，宽度:32
 寄存器说明: AXI recorder part a
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  length : 3;  /* bit[0-2] : burst length */
        unsigned int  rw     : 1;  /* bit[3]   : 读写标志。
                                                 0：读；
                                                 1：写 */
        unsigned int  addr   : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_AIF_AXI_REC_A_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_A_m_length_START  (0)
#define SOC_DSS_AIF_AXI_REC_A_m_length_END    (2)
#define SOC_DSS_AIF_AXI_REC_A_m_rw_START      (3)
#define SOC_DSS_AIF_AXI_REC_A_m_rw_END        (3)
#define SOC_DSS_AIF_AXI_REC_A_m_addr_START    (4)
#define SOC_DSS_AIF_AXI_REC_A_m_addr_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI_REC_B_m_UNION
 结构说明  : AXI_REC_B_m 寄存器结构定义。地址偏移量:0x0884+0x10*(m)，初值:0x00000000，宽度:32
 寄存器说明: AXI recorder part b
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id          : 16; /* bit[0-15] : 命令id */
        unsigned int  prs         : 2;  /* bit[16-17]: 通道mainpress信号 */
        unsigned int  qos         : 2;  /* bit[18-19]: 命令qos信号 */
        unsigned int  user        : 4;  /* bit[20-23]: 通道最大user信号 */
        unsigned int  prot        : 3;  /* bit[24-26]: 通道最大prot信号 */
        unsigned int  reserved    : 1;  /* bit[27]   : 保留 */
        unsigned int  response    : 2;  /* bit[28-29]: 命令返回response */
        unsigned int  rec_axi_sel : 1;  /* bit[30]   : axi选择。
                                                       0：axi0；
                                                       1：axi1 */
        unsigned int  recd_vld    : 1;  /* bit[31]   : 记录有效标志 */
    } reg;
} SOC_DSS_AIF_AXI_REC_B_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_B_m_id_START           (0)
#define SOC_DSS_AIF_AXI_REC_B_m_id_END             (15)
#define SOC_DSS_AIF_AXI_REC_B_m_prs_START          (16)
#define SOC_DSS_AIF_AXI_REC_B_m_prs_END            (17)
#define SOC_DSS_AIF_AXI_REC_B_m_qos_START          (18)
#define SOC_DSS_AIF_AXI_REC_B_m_qos_END            (19)
#define SOC_DSS_AIF_AXI_REC_B_m_user_START         (20)
#define SOC_DSS_AIF_AXI_REC_B_m_user_END           (23)
#define SOC_DSS_AIF_AXI_REC_B_m_prot_START         (24)
#define SOC_DSS_AIF_AXI_REC_B_m_prot_END           (26)
#define SOC_DSS_AIF_AXI_REC_B_m_response_START     (28)
#define SOC_DSS_AIF_AXI_REC_B_m_response_END       (29)
#define SOC_DSS_AIF_AXI_REC_B_m_rec_axi_sel_START  (30)
#define SOC_DSS_AIF_AXI_REC_B_m_rec_axi_sel_END    (30)
#define SOC_DSS_AIF_AXI_REC_B_m_recd_vld_START     (31)
#define SOC_DSS_AIF_AXI_REC_B_m_recd_vld_END       (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI_REC_C_m_UNION
 结构说明  : AXI_REC_C_m 寄存器结构定义。地址偏移量:0x0888+0x10*(m)，初值:0x00000000，宽度:32
 寄存器说明: AXI recorder part c
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_rec_begin : 32; /* bit[0-31]: 命令起始时间戳 */
    } reg;
} SOC_DSS_AIF_AXI_REC_C_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_C_m_axi_rec_begin_START  (0)
#define SOC_DSS_AIF_AXI_REC_C_m_axi_rec_begin_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_AIF_AXI_REC_D_m_UNION
 结构说明  : AXI_REC_D_m 寄存器结构定义。地址偏移量:0x088C+0x10*(m)，初值:0x00000000，宽度:32
 寄存器说明: AXI recorder part d
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_rec_end : 32; /* bit[0-31]: 命令结束时间戳 */
    } reg;
} SOC_DSS_AIF_AXI_REC_D_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_D_m_axi_rec_end_START  (0)
#define SOC_DSS_AIF_AXI_REC_D_m_axi_rec_end_END    (31)






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

#endif /* end of soc_dss_aif_interface.h */
