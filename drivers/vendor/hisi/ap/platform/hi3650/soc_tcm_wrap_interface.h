/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_tcm_wrap_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:23:14
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_TCM_WRAP.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_TCM_WRAP_INTERFACE_H__
#define __SOC_TCM_WRAP_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* 寄存器说明：Remap模块控制寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_REMAP_CFG_UNION */
#define SOC_TCM_WRAP_REMAP_CFG_ADDR(base)             ((base) + (0x000))

/* 寄存器说明：Map_table写保护寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_MAP_TABLE_WP_UNION */
#define SOC_TCM_WRAP_MAP_TABLE_WP_ADDR(base)          ((base) + (0x004))

/* 寄存器说明：低功耗控制寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_LP_CTRL_UNION */
#define SOC_TCM_WRAP_LP_CTRL_ADDR(base)               ((base) + (0x008))

/* 寄存器说明：低功耗控制寄存器1
   位域定义UNION结构:  SOC_TCM_WRAP_LP_CTRL_1_UNION */
#define SOC_TCM_WRAP_LP_CTRL_1_ADDR(base)             ((base) + (0x00C))

/* 寄存器说明：ITCM的TLB_ENTY_0寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY0_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY0_ADDR(base)       ((base) + (0x010))

/* 寄存器说明：ITCM的TLB_ENTY_1寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY1_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY1_ADDR(base)       ((base) + (0x014))

/* 寄存器说明：ITCM的TLB_ENTY_2寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY2_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY2_ADDR(base)       ((base) + (0x018))

/* 寄存器说明：ITCM的TLB_ENTY_3寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY3_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY3_ADDR(base)       ((base) + (0x01C))

/* 寄存器说明：ITCM的TLB_ENTY_4寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY4_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY4_ADDR(base)       ((base) + (0x020))

/* 寄存器说明：ITCM的TLB_ENTY_5寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY5_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY5_ADDR(base)       ((base) + (0x024))

/* 寄存器说明：ITCM的TLB_ENTY_6寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY6_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY6_ADDR(base)       ((base) + (0x028))

/* 寄存器说明：ITCM的TLB_ENTY_7寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_TLB_ENTRY7_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY7_ADDR(base)       ((base) + (0x02C))

/* 寄存器说明：D0TCM的TLB_ENTY_0寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_ADDR(base)      ((base) + (0x030))

/* 寄存器说明：D0TCM的TLB_ENTY_1寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_ADDR(base)      ((base) + (0x034))

/* 寄存器说明：D0TCM的TLB_ENTY_2寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_ADDR(base)      ((base) + (0x038))

/* 寄存器说明：D0TCM的TLB_ENTY_3寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_ADDR(base)      ((base) + (0x03C))

/* 寄存器说明：D0TCM的TLB_ENTY_4寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_ADDR(base)      ((base) + (0x040))

/* 寄存器说明：D0TCM的TLB_ENTY_5寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_ADDR(base)      ((base) + (0x044))

/* 寄存器说明：D0TCM的TLB_ENTY_6寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_ADDR(base)      ((base) + (0x048))

/* 寄存器说明：D0TCM的TLB_ENTY_7寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_ADDR(base)      ((base) + (0x04C))

/* 寄存器说明：D1TCM的TLB_ENTY_0寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_ADDR(base)      ((base) + (0x050))

/* 寄存器说明：D1TCM的TLB_ENTY_1寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_ADDR(base)      ((base) + (0x054))

/* 寄存器说明：D1TCM的TLB_ENTY_2寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_ADDR(base)      ((base) + (0x058))

/* 寄存器说明：D1TCM的TLB_ENTY_3寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_ADDR(base)      ((base) + (0x05C))

/* 寄存器说明：D1TCM的TLB_ENTY_4寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_ADDR(base)      ((base) + (0x060))

/* 寄存器说明：D1TCM的TLB_ENTY_5寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_ADDR(base)      ((base) + (0x064))

/* 寄存器说明：D1TCM的TLB_ENTY_6寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_ADDR(base)      ((base) + (0x068))

/* 寄存器说明：D1TCM的TLB_ENTY_7寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_ADDR(base)      ((base) + (0x06C))

/* 寄存器说明：ITCM的命中次数寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_HIT_CNT_UNION */
#define SOC_TCM_WRAP_ITCM_HIT_CNT_ADDR(base)          ((base) + (0x070))

/* 寄存器说明：ITCM的miss次数寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_MISS_CNT_UNION */
#define SOC_TCM_WRAP_ITCM_MISS_CNT_ADDR(base)         ((base) + (0x074))

/* 寄存器说明：D0TCM的命中次数寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_HIT_CNT_UNION */
#define SOC_TCM_WRAP_D0TCM_HIT_CNT_ADDR(base)         ((base) + (0x078))

/* 寄存器说明：D0TCM的miss次数寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_MISS_CNT_UNION */
#define SOC_TCM_WRAP_D0TCM_MISS_CNT_ADDR(base)        ((base) + (0x07C))

/* 寄存器说明：D1TCM的命中次数寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_HIT_CNT_UNION */
#define SOC_TCM_WRAP_D1TCM_HIT_CNT_ADDR(base)         ((base) + (0x080))

/* 寄存器说明：D1TCM的miss次数寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_MISS_CNT_UNION */
#define SOC_TCM_WRAP_D1TCM_MISS_CNT_ADDR(base)        ((base) + (0x084))

/* 寄存器说明：TCM ADDRESS边界检查功能使能寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_UNION */
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_ADDR(base) ((base) + (0x098))

/* 寄存器说明：ITCM错误类型寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_TCM_ERR_TYPE_UNION */
#define SOC_TCM_WRAP_TCM_ERR_TYPE_ADDR(base)          ((base) + (0x09C))

/* 寄存器说明：BANK选择寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_BANK_SEL_UNION */
#define SOC_TCM_WRAP_BANK_SEL_ADDR(base)              ((base) + (0x0A0))

/* 寄存器说明：ITCM错误地址寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_ERR_ADDR_UNION */
#define SOC_TCM_WRAP_ITCM_ERR_ADDR_ADDR(base)         ((base) + (0x0A8))

/* 寄存器说明：D0TCM错误地址寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_ERR_ADDR_UNION */
#define SOC_TCM_WRAP_D0TCM_ERR_ADDR_ADDR(base)        ((base) + (0x0AC))

/* 寄存器说明：D1TCM错误地址寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_ERR_ADDR_UNION */
#define SOC_TCM_WRAP_D1TCM_ERR_ADDR_ADDR(base)        ((base) + (0x0B0))

/* 寄存器说明：ITCM错误计数器寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_ITCM_ERR_CNT_UNION */
#define SOC_TCM_WRAP_ITCM_ERR_CNT_ADDR(base)          ((base) + (0x0B4))

/* 寄存器说明：D0TCM错误计数器寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D0TCM_ERR_CNT_UNION */
#define SOC_TCM_WRAP_D0TCM_ERR_CNT_ADDR(base)         ((base) + (0x0B8))

/* 寄存器说明：D1TCM错误计数器寄存器
   位域定义UNION结构:  SOC_TCM_WRAP_D1TCM_ERR_CNT_UNION */
#define SOC_TCM_WRAP_D1TCM_ERR_CNT_ADDR(base)         ((base) + (0x0BC))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_TCM_WRAP_REMAP_CFG_UNION
 结构说明  : REMAP_CFG 寄存器结构定义。地址偏移量:0x000，初值:0x00000001，宽度:32
 寄存器说明: Remap模块控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass            : 1;  /* bit[0-0]  : Remap功能是否Bypass
                                                             0：使能Remap功能 
                                                             1：不使能Remap功能 */
        unsigned int  invalid           : 1;  /* bit[1-1]  : 对Micro TLB中的entry进行invalid操作 */
        unsigned int  itcm_cnt_clr      : 1;  /* bit[2-2]  : 写1清除统计ITCM读写操作的命中和miss计数器，写0无效； */
        unsigned int  d0tcm_cnt_clr     : 1;  /* bit[3-3]  : 写1清除统计D0TCM读写操作的命中和miss计数器，写0无效； */
        unsigned int  d1tcm_cnt_clr     : 1;  /* bit[4-4]  : 写1清除统计D1TCM读写操作的命中和miss计数器，写0无效； */
        unsigned int  itcm_err_cnt_clr  : 1;  /* bit[5-5]  : 写1清除统计ITCM错误计数器和错误地址，写0无效； */
        unsigned int  d0tcm_err_cnt_clr : 1;  /* bit[6-6]  : 写1清除统计D0TCM错误计数器和错误地址，写0无效； */
        unsigned int  d1tcm_err_cnt_clr : 1;  /* bit[7-7]  : 写1清除统计D1TCM错误计数器和错误地址，写0无效； */
        unsigned int  itcm_err_clr      : 1;  /* bit[8-8]  : 写1清除ITCM ERR状态，写0无效； */
        unsigned int  d0tcm_err_clr     : 1;  /* bit[9-9]  : 写1清除D0TCM ERR状态，写0无效； */
        unsigned int  d1tcm_err_clr     : 1;  /* bit[10-10]: 写1清除D1TCM ERR状态，写0无效； */
        unsigned int  reserved          : 21; /* bit[11-31]: reserved */
    } reg;
} SOC_TCM_WRAP_REMAP_CFG_UNION;
#endif
#define SOC_TCM_WRAP_REMAP_CFG_bypass_START             (0)
#define SOC_TCM_WRAP_REMAP_CFG_bypass_END               (0)
#define SOC_TCM_WRAP_REMAP_CFG_invalid_START            (1)
#define SOC_TCM_WRAP_REMAP_CFG_invalid_END              (1)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_cnt_clr_START       (2)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_cnt_clr_END         (2)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_cnt_clr_START      (3)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_cnt_clr_END        (3)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_cnt_clr_START      (4)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_cnt_clr_END        (4)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_cnt_clr_START   (5)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_cnt_clr_END     (5)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_cnt_clr_START  (6)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_cnt_clr_END    (6)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_cnt_clr_START  (7)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_cnt_clr_END    (7)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_clr_START       (8)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_clr_END         (8)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_clr_START      (9)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_clr_END        (9)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_clr_START      (10)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_clr_END        (10)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_MAP_TABLE_WP_UNION
 结构说明  : MAP_TABLE_WP 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: Map_table写保护寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mt_wp : 32; /* bit[0-31]: 只有寄存器内容为0x6864_3650时，才能对Map Table进行配置，否则只能对Map Table进行读操作。 */
    } reg;
} SOC_TCM_WRAP_MAP_TABLE_WP_UNION;
#endif
#define SOC_TCM_WRAP_MAP_TABLE_WP_mt_wp_START  (0)
#define SOC_TCM_WRAP_MAP_TABLE_WP_mt_wp_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_LP_CTRL_UNION
 结构说明  : LP_CTRL 寄存器结构定义。地址偏移量:0x008，初值:0x00F000F0，宽度:32
 寄存器说明: 低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auto_gate_en    : 1;  /* bit[0-0]  : 时钟自动门控功能
                                                           0：不使能
                                                           1：使能 */
        unsigned int  reserved_0      : 3;  /* bit[1-3]  : reserved */
        unsigned int  auto_gate_cnt   : 8;  /* bit[4-11] : TCM时钟自动门控功能的防抖周期数，即配置值的周期内没有操作，TCM自动门控生效；配置值不能小于3；，建议配置成0x3 */
        unsigned int  reserved_1      : 4;  /* bit[12-15]: reserved */
        unsigned int  auto_mem_lp_en  : 1;  /* bit[16-16]: Memory自动进入Deepsleep功能
                                                           0：不使能
                                                           1：使能 */
        unsigned int  reserved_2      : 3;  /* bit[17-19]: reserved */
        unsigned int  auto_mem_lp_cnt : 8;  /* bit[20-27]: Memory自动进入Deepsleep的没有操作的周期数，建议配置成0x7 */
        unsigned int  reserved_3      : 4;  /* bit[28-31]: reserved */
    } reg;
} SOC_TCM_WRAP_LP_CTRL_UNION;
#endif
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_en_START     (0)
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_en_END       (0)
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_cnt_START    (4)
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_cnt_END      (11)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_en_START   (16)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_en_END     (16)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_cnt_START  (20)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_cnt_END    (27)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_LP_CTRL_1_UNION
 结构说明  : LP_CTRL_1 寄存器结构定义。地址偏移量:0x00C，初值:0x00000001，宽度:32
 寄存器说明: 低功耗控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcm128_gate_en_soft : 1;  /* bit[0-0] : 128Mhz时钟软门控
                                                              0：不使能
                                                              1：使能 */
        unsigned int  reserved            : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_TCM_WRAP_LP_CTRL_1_UNION;
#endif
#define SOC_TCM_WRAP_LP_CTRL_1_tcm128_gate_en_soft_START  (0)
#define SOC_TCM_WRAP_LP_CTRL_1_tcm128_gate_en_soft_END    (0)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY0_UNION
 结构说明  : ITCM_TLB_ENTRY0 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry0 : 20; /* bit[0-19] : ITCM tlb_entry0的值 */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY0_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY0_itcm_tlb_entry0_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY0_itcm_tlb_entry0_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY1_UNION
 结构说明  : ITCM_TLB_ENTRY1 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry1 : 20; /* bit[0-19] : ` */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY1_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY1_itcm_tlb_entry1_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY1_itcm_tlb_entry1_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY2_UNION
 结构说明  : ITCM_TLB_ENTRY2 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_2寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry2 : 20; /* bit[0-19] : ITCM tlb_entry2的值 */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY2_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY2_itcm_tlb_entry2_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY2_itcm_tlb_entry2_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY3_UNION
 结构说明  : ITCM_TLB_ENTRY3 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_3寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry3 : 20; /* bit[0-19] : ITCM tlb_entry3的值 */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY3_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY3_itcm_tlb_entry3_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY3_itcm_tlb_entry3_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY4_UNION
 结构说明  : ITCM_TLB_ENTRY4 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_4寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry4 : 20; /* bit[0-19] : ITCM tlb_entry4的值 */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY4_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY4_itcm_tlb_entry4_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY4_itcm_tlb_entry4_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY5_UNION
 结构说明  : ITCM_TLB_ENTRY5 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_5寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry5 : 20; /* bit[0-19] : ITCM tlb_entry5的值 */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY5_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY5_itcm_tlb_entry5_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY5_itcm_tlb_entry5_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY6_UNION
 结构说明  : ITCM_TLB_ENTRY6 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_6寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry6 : 20; /* bit[0-19] : ITCM tlb_entry6的值 */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY6_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY6_itcm_tlb_entry6_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY6_itcm_tlb_entry6_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_TLB_ENTRY7_UNION
 结构说明  : ITCM_TLB_ENTRY7 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: ITCM的TLB_ENTY_7寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry7 : 20; /* bit[0-19] : ITCM tlb_entry7的值 */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY7_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY7_itcm_tlb_entry7_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY7_itcm_tlb_entry7_END    (19)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_UNION
 结构说明  : D0TCM_TLB_ENTRY0 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry0 : 19; /* bit[0-18] : d0tcm tlb_entry0的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_d0tcm_tlb_entry0_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_d0tcm_tlb_entry0_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_UNION
 结构说明  : D0TCM_TLB_ENTRY1 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry1 : 19; /* bit[0-18] : d0tcm tlb_entry1的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_d0tcm_tlb_entry1_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_d0tcm_tlb_entry1_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_UNION
 结构说明  : D0TCM_TLB_ENTRY2 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_2寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry2 : 19; /* bit[0-18] : d0tcm tlb_entry2的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_d0tcm_tlb_entry2_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_d0tcm_tlb_entry2_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_UNION
 结构说明  : D0TCM_TLB_ENTRY3 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_3寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry3 : 19; /* bit[0-18] : d0tcm tlb_entry3的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_d0tcm_tlb_entry3_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_d0tcm_tlb_entry3_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_UNION
 结构说明  : D0TCM_TLB_ENTRY4 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_4寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry4 : 19; /* bit[0-18] : d0tcm tlb_entry4的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_d0tcm_tlb_entry4_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_d0tcm_tlb_entry4_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_UNION
 结构说明  : D0TCM_TLB_ENTRY5 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_5寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry5 : 19; /* bit[0-18] : d0tcm tlb_entry5的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_d0tcm_tlb_entry5_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_d0tcm_tlb_entry5_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_UNION
 结构说明  : D0TCM_TLB_ENTRY6 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_6寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry6 : 19; /* bit[0-18] : d0tcm tlb_entry6的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_d0tcm_tlb_entry6_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_d0tcm_tlb_entry6_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_UNION
 结构说明  : D0TCM_TLB_ENTRY7 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的TLB_ENTY_7寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry7 : 19; /* bit[0-18] : d0tcm tlb_entry7的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_d0tcm_tlb_entry7_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_d0tcm_tlb_entry7_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_UNION
 结构说明  : D1TCM_TLB_ENTRY0 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry0 : 19; /* bit[0-18] : d1tcm tlb_entry0的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_d1tcm_tlb_entry0_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_d1tcm_tlb_entry0_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_UNION
 结构说明  : D1TCM_TLB_ENTRY1 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry1 : 19; /* bit[0-18] : d1tcm tlb_entry1的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_d1tcm_tlb_entry1_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_d1tcm_tlb_entry1_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_UNION
 结构说明  : D1TCM_TLB_ENTRY2 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_2寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry2 : 19; /* bit[0-18] : d1tcm tlb_entry2的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_d1tcm_tlb_entry2_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_d1tcm_tlb_entry2_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_UNION
 结构说明  : D1TCM_TLB_ENTRY3 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_3寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry3 : 19; /* bit[0-18] : d1tcm tlb_entry3的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_d1tcm_tlb_entry3_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_d1tcm_tlb_entry3_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_UNION
 结构说明  : D1TCM_TLB_ENTRY4 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_4寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry4 : 19; /* bit[0-18] : d1tcm tlb_entry4的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_d1tcm_tlb_entry4_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_d1tcm_tlb_entry4_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_UNION
 结构说明  : D1TCM_TLB_ENTRY5 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_5寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry5 : 19; /* bit[0-18] : d1tcm tlb_entry5的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_d1tcm_tlb_entry5_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_d1tcm_tlb_entry5_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_UNION
 结构说明  : D1TCM_TLB_ENTRY6 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_6寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry6 : 19; /* bit[0-18] : d1tcm tlb_entry6的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_d1tcm_tlb_entry6_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_d1tcm_tlb_entry6_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_UNION
 结构说明  : D1TCM_TLB_ENTRY7 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的TLB_ENTY_7寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry7 : 19; /* bit[0-18] : d1tcm tlb_entry7的值 */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_d1tcm_tlb_entry7_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_d1tcm_tlb_entry7_END    (18)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_HIT_CNT_UNION
 结构说明  : ITCM_HIT_CNT 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: ITCM的命中次数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_hit_cnt : 32; /* bit[0-31]: ITCM的命中次数 */
    } reg;
} SOC_TCM_WRAP_ITCM_HIT_CNT_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_HIT_CNT_itcm_hit_cnt_START  (0)
#define SOC_TCM_WRAP_ITCM_HIT_CNT_itcm_hit_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_MISS_CNT_UNION
 结构说明  : ITCM_MISS_CNT 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: ITCM的miss次数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_miss_cnt : 32; /* bit[0-31]: ITCM的miss次数 */
    } reg;
} SOC_TCM_WRAP_ITCM_MISS_CNT_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_MISS_CNT_itcm_miss_cnt_START  (0)
#define SOC_TCM_WRAP_ITCM_MISS_CNT_itcm_miss_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_HIT_CNT_UNION
 结构说明  : D0TCM_HIT_CNT 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的命中次数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_hit_cnt : 32; /* bit[0-31]: D0TCM的命中次数 */
    } reg;
} SOC_TCM_WRAP_D0TCM_HIT_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_HIT_CNT_d0tcm_hit_cnt_START  (0)
#define SOC_TCM_WRAP_D0TCM_HIT_CNT_d0tcm_hit_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_MISS_CNT_UNION
 结构说明  : D0TCM_MISS_CNT 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: D0TCM的miss次数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_miss_cnt : 32; /* bit[0-31]: D0TCM的miss次数 */
    } reg;
} SOC_TCM_WRAP_D0TCM_MISS_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_MISS_CNT_d0tcm_miss_cnt_START  (0)
#define SOC_TCM_WRAP_D0TCM_MISS_CNT_d0tcm_miss_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_HIT_CNT_UNION
 结构说明  : D1TCM_HIT_CNT 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的命中次数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_hit_cnt : 32; /* bit[0-31]: D1TCM的命中次数 */
    } reg;
} SOC_TCM_WRAP_D1TCM_HIT_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_HIT_CNT_d1tcm_hit_cnt_START  (0)
#define SOC_TCM_WRAP_D1TCM_HIT_CNT_d1tcm_hit_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_MISS_CNT_UNION
 结构说明  : D1TCM_MISS_CNT 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: D1TCM的miss次数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_miss_cnt : 32; /* bit[0-31]: D1TCM的miss次数 */
    } reg;
} SOC_TCM_WRAP_D1TCM_MISS_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_MISS_CNT_d1tcm_miss_cnt_START  (0)
#define SOC_TCM_WRAP_D1TCM_MISS_CNT_d1tcm_miss_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_UNION
 结构说明  : TCMADDR_BOUNDARY_CHECK_BYPASS 寄存器结构定义。地址偏移量:0x098，初值:0x00000003，宽度:32
 寄存器说明: TCM ADDRESS边界检查功能使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcmaddr_boundary_check_bypass : 1;  /* bit[0-0] : tcmaddr边界检查功能
                                                                        1'b0:不bypass，使能容量检查
                                                                        1'b1:bypass检查功能 */
        unsigned int  bank_collision_check_bypass   : 1;  /* bit[1-1] : bank冲突检查功能
                                                                        1'b0:使能bank冲突检查
                                                                        1'b1:bypass检查功能 */
        unsigned int  reserved                      : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_UNION;
#endif
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_tcmaddr_boundary_check_bypass_START  (0)
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_tcmaddr_boundary_check_bypass_END    (0)
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_bank_collision_check_bypass_START    (1)
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_bank_collision_check_bypass_END      (1)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_TCM_ERR_TYPE_UNION
 结构说明  : TCM_ERR_TYPE 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: ITCM错误类型寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_page_err          : 1;  /* bit[0-0]  : ITCM缺页错误
                                                                  1'b0:无错
                                                                  1'b1:有错 */
        unsigned int  itcmaddr_out_320k_err  : 1;  /* bit[1-1]  : ITCM访问超过320K空间错误
                                                                  1'b0:无错
                                                                  1'b1:有错 */
        unsigned int  reserved_0             : 2;  /* bit[2-3]  : reserved */
        unsigned int  d0tcm_page_err         : 1;  /* bit[4-4]  : D0TCM缺页错误
                                                                  1'b0:无错
                                                                  1'b1:有错 */
        unsigned int  d0tcmaddr_out_320k_err : 1;  /* bit[5-5]  : D0TCM访问超过320K空间错误
                                                                  1'b0:无错
                                                                  1'b1:有错 */
        unsigned int  reserved_1             : 2;  /* bit[6-7]  : reserved */
        unsigned int  d1tcm_page_err         : 1;  /* bit[8-8]  : D1TCM缺页错误
                                                                  1'b0:无错
                                                                  1'b1:有错 */
        unsigned int  d1tcmaddr_out_320k_err : 1;  /* bit[9-9]  : D1TCM访问超过320K空间错误
                                                                  1'b0:无错
                                                                  1'b1:有错 */
        unsigned int  reserved_2             : 2;  /* bit[10-11]: reserved */
        unsigned int  itcm_err_bank0         : 1;  /* bit[12-12]: ITCM是否访问了分配给DTCM的bank0
                                                                  1'b1:访问了分配给DTCM的bank0
                                                                  1'b0:未访问 */
        unsigned int  itcm_err_bank1         : 1;  /* bit[13-13]: ITCM是否访问了分配给DTCM的bank1
                                                                  1'b1:访问了分配给DTCM的bank1
                                                                  1'b0:未访问 */
        unsigned int  itcm_err_bank2         : 1;  /* bit[14-14]: ITCM是否访问了分配给DTCM的bank2
                                                                  1'b1:访问了分配给DTCM的bank2
                                                                  1'b0:未访问 */
        unsigned int  itcm_err_bank3         : 1;  /* bit[15-15]: ITCM是否访问了分配给DTCM的bank3
                                                                  1'b1:访问了分配给DTCM的bank3
                                                                  1'b0:未访问 */
        unsigned int  itcm_err_bank4         : 1;  /* bit[16-16]: ITCM是否访问了分配给DTCM的bank4
                                                                  1'b1:访问了分配给DTCM的bank4
                                                                  1'b0:未访问 */
        unsigned int  d0tcm_err_bank0        : 1;  /* bit[17-17]: D0TCM是否访问了分配给ITCM的bank0
                                                                  1'b1:访问了分配给ITCM的bank0
                                                                  1'b0:未访问 */
        unsigned int  d0tcm_err_bank1        : 1;  /* bit[18-18]: D0TCM是否访问了分配给ITCM的bank1
                                                                  1'b1:访问了分配给ITCM的bank1
                                                                  1'b0:未访问 */
        unsigned int  d0tcm_err_bank2        : 1;  /* bit[19-19]: D0TCM是否访问了分配给ITCM的bank2
                                                                  1'b1:访问了分配给ITCM的bank2
                                                                  1'b0:未访问 */
        unsigned int  d0tcm_err_bank3        : 1;  /* bit[20-20]: D0TCM是否访问了分配给ITCM的bank3
                                                                  1'b1:访问了分配给ITCM的bank3
                                                                  1'b0:未访问 */
        unsigned int  d0tcm_err_bank4        : 1;  /* bit[21-21]: D0TCM是否访问了分配给ITCM的bank4
                                                                  1'b1:访问了分配给ITCM的bank4
                                                                  1'b0:未访问 */
        unsigned int  d1tcm_err_bank0        : 1;  /* bit[22-22]: D1TCM是否访问了分配给ITCM的bank0
                                                                  1'b1:访问了分配给ITCM的bank0
                                                                  1'b0:未访问 */
        unsigned int  d1tcm_err_bank1        : 1;  /* bit[23-23]: D1TCM是否访问了分配给ITCM的bank1
                                                                  1'b1:访问了分配给ITCM的bank1
                                                                  1'b0:未访问 */
        unsigned int  d1tcm_err_bank2        : 1;  /* bit[24-24]: D1TCM是否访问了分配给ITCM的bank2
                                                                  1'b1:访问了分配给ITCM的bank2
                                                                  1'b0:未访问 */
        unsigned int  d1tcm_err_bank3        : 1;  /* bit[25-25]: D1TCM是否访问了分配给ITCM的bank3
                                                                  1'b1:访问了分配给ITCM的bank3
                                                                  1'b0:未访问 */
        unsigned int  d1tcm_err_bank4        : 1;  /* bit[26-26]: D1TCM是否访问了分配给ITCM的bank4
                                                                  1'b1:访问了分配给ITCM的bank4
                                                                  1'b0:未访问 */
        unsigned int  reserved_3             : 5;  /* bit[27-31]: reserved */
    } reg;
} SOC_TCM_WRAP_TCM_ERR_TYPE_UNION;
#endif
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_page_err_START           (0)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_page_err_END             (0)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcmaddr_out_320k_err_START   (1)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcmaddr_out_320k_err_END     (1)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_page_err_START          (4)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_page_err_END            (4)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcmaddr_out_320k_err_START  (5)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcmaddr_out_320k_err_END    (5)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_page_err_START          (8)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_page_err_END            (8)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcmaddr_out_320k_err_START  (9)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcmaddr_out_320k_err_END    (9)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank0_START          (12)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank0_END            (12)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank1_START          (13)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank1_END            (13)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank2_START          (14)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank2_END            (14)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank3_START          (15)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank3_END            (15)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank4_START          (16)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank4_END            (16)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank0_START         (17)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank0_END           (17)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank1_START         (18)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank1_END           (18)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank2_START         (19)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank2_END           (19)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank3_START         (20)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank3_END           (20)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank4_START         (21)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank4_END           (21)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank0_START         (22)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank0_END           (22)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank1_START         (23)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank1_END           (23)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank2_START         (24)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank2_END           (24)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank3_START         (25)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank3_END           (25)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank4_START         (26)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank4_END           (26)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_BANK_SEL_UNION
 结构说明  : BANK_SEL 寄存器结构定义。地址偏移量:0x0A0，初值:0x0000001C，宽度:32
 寄存器说明: BANK选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bank0_sel : 1;  /* bit[0-0] : bank0分配给ITCM还是DTCM
                                                    1'b0:分配给ITCM
                                                    1'b1:分配给DTCM */
        unsigned int  bank1_sel : 1;  /* bit[1-1] : bank1分配给ITCM还是DTCM
                                                    1'b0:分配给ITCM
                                                    1'b1:分配给DTCM */
        unsigned int  bank2_sel : 1;  /* bit[2-2] : bank2分配给ITCM还是DTCM
                                                    1'b0:分配给ITCM
                                                    1'b1:分配给DTCM */
        unsigned int  bank3_sel : 1;  /* bit[3-3] : bank3分配给ITCM还是DTCM
                                                    1'b0:分配给ITCM
                                                    1'b1:分配给DTCM */
        unsigned int  bank4_sel : 1;  /* bit[4-4] : bank4分配给ITCM还是DTCM
                                                    1'b0:分配给ITCM
                                                    1'b1:分配给DTCM */
        unsigned int  reserved  : 27; /* bit[5-31]: reserved */
    } reg;
} SOC_TCM_WRAP_BANK_SEL_UNION;
#endif
#define SOC_TCM_WRAP_BANK_SEL_bank0_sel_START  (0)
#define SOC_TCM_WRAP_BANK_SEL_bank0_sel_END    (0)
#define SOC_TCM_WRAP_BANK_SEL_bank1_sel_START  (1)
#define SOC_TCM_WRAP_BANK_SEL_bank1_sel_END    (1)
#define SOC_TCM_WRAP_BANK_SEL_bank2_sel_START  (2)
#define SOC_TCM_WRAP_BANK_SEL_bank2_sel_END    (2)
#define SOC_TCM_WRAP_BANK_SEL_bank3_sel_START  (3)
#define SOC_TCM_WRAP_BANK_SEL_bank3_sel_END    (3)
#define SOC_TCM_WRAP_BANK_SEL_bank4_sel_START  (4)
#define SOC_TCM_WRAP_BANK_SEL_bank4_sel_END    (4)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_ERR_ADDR_UNION
 结构说明  : ITCM_ERR_ADDR 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: ITCM错误地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_err_addr : 23; /* bit[0-22] : ITCM错误操作的地址 */
        unsigned int  reserved      : 9;  /* bit[23-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_ERR_ADDR_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_ERR_ADDR_itcm_err_addr_START  (0)
#define SOC_TCM_WRAP_ITCM_ERR_ADDR_itcm_err_addr_END    (22)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_ERR_ADDR_UNION
 结构说明  : D0TCM_ERR_ADDR 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: D0TCM错误地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_err_addr : 22; /* bit[0-21] : D0TCM错误操作的地址 */
        unsigned int  reserved       : 10; /* bit[22-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_ERR_ADDR_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_ERR_ADDR_d0tcm_err_addr_START  (0)
#define SOC_TCM_WRAP_D0TCM_ERR_ADDR_d0tcm_err_addr_END    (21)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_ERR_ADDR_UNION
 结构说明  : D1TCM_ERR_ADDR 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: D1TCM错误地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_err_addr : 22; /* bit[0-21] : D1TCM错误操作的地址 */
        unsigned int  reserved       : 10; /* bit[22-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_ERR_ADDR_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_ERR_ADDR_d1tcm_err_addr_START  (0)
#define SOC_TCM_WRAP_D1TCM_ERR_ADDR_d1tcm_err_addr_END    (21)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_ITCM_ERR_CNT_UNION
 结构说明  : ITCM_ERR_CNT 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: ITCM错误计数器寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_err_cnt : 32; /* bit[0-31]: ITCM ERR的数量 */
    } reg;
} SOC_TCM_WRAP_ITCM_ERR_CNT_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_ERR_CNT_itcm_err_cnt_START  (0)
#define SOC_TCM_WRAP_ITCM_ERR_CNT_itcm_err_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D0TCM_ERR_CNT_UNION
 结构说明  : D0TCM_ERR_CNT 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: D0TCM错误计数器寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_err_cnt : 32; /* bit[0-31]: D0TCM ERR的数量 */
    } reg;
} SOC_TCM_WRAP_D0TCM_ERR_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_ERR_CNT_d0tcm_err_cnt_START  (0)
#define SOC_TCM_WRAP_D0TCM_ERR_CNT_d0tcm_err_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_TCM_WRAP_D1TCM_ERR_CNT_UNION
 结构说明  : D1TCM_ERR_CNT 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: D1TCM错误计数器寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_err_cnt : 32; /* bit[0-31]: D1TCM ERR的数量 */
    } reg;
} SOC_TCM_WRAP_D1TCM_ERR_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_ERR_CNT_d1tcm_err_cnt_START  (0)
#define SOC_TCM_WRAP_D1TCM_ERR_CNT_d1tcm_err_cnt_END    (31)






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

#endif /* end of soc_tcm_wrap_interface.h */
