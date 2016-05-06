/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_sub_ctrl_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:47:15
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_SUB_CTRL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_SUB_CTRL_INTERFACE_H__
#define __SOC_ISP_SUB_CTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) ISP SUB_CTRL
 ****************************************************************************/
/* 寄存器说明：SUBSYS config register.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_SUBSYS_CFG_UNION */
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_ADDR(base)        ((base) + (0x0))

/* 寄存器说明：configure register.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_CORE_CFG_UNION */
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_ADDR(base)      ((base) + (0x4))

/* 寄存器说明：ERROR information register0.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_UNION */
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_ADDR(base)     ((base) + (0x8))

/* 寄存器说明：ERROR information register1.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_UNION */
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_ADDR(base)     ((base) + (0xC))

/* 寄存器说明：ERROR information register2.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_UNION */
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_ADDR(base)     ((base) + (0x10))

/* 寄存器说明：ERROR information register3.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_UNION */
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_ADDR(base)     ((base) + (0x14))

/* 寄存器说明：ERROR clear register.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_UNION */
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_ADDR(base)     ((base) + (0x18))

/* 寄存器说明：readonly register.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_UNION */
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_ADDR(base)     ((base) + (0x1C))

/* 寄存器说明：cfg register group0.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_UNION */
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_ADDR(base)   ((base) + (0x20))

/* 寄存器说明：cfg register group1.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_UNION */
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_ADDR(base)   ((base) + (0x24))

/* 寄存器说明：readonly register vic0.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_vic0_out0_UNION */
#define SOC_ISP_SUB_CTRL_vic0_out0_ADDR(base)         ((base) + (0x28))

/* 寄存器说明：vic0 contgrol reg group0.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_vic0_in0_UNION */
#define SOC_ISP_SUB_CTRL_vic0_in0_ADDR(base)          ((base) + (0x2C))

/* 寄存器说明：vic0 contgrol reg group1.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_vic0_in1_UNION */
#define SOC_ISP_SUB_CTRL_vic0_in1_ADDR(base)          ((base) + (0x30))

/* 寄存器说明：readonly register vic1.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_vic1_out0_UNION */
#define SOC_ISP_SUB_CTRL_vic1_out0_ADDR(base)         ((base) + (0x34))

/* 寄存器说明：vic1 contgrol reg group0.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_vic1_in0_UNION */
#define SOC_ISP_SUB_CTRL_vic1_in0_ADDR(base)          ((base) + (0x38))

/* 寄存器说明：vic1 contgrol reg group1.
   位域定义UNION结构:  SOC_ISP_SUB_CTRL_vic1_in1_UNION */
#define SOC_ISP_SUB_CTRL_vic1_in1_ADDR(base)          ((base) + (0x3C))





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
                     (1/1) ISP SUB_CTRL
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_SUBSYS_CFG_UNION
 结构说明  : SUBSYS_CFG 寄存器结构定义。地址偏移量:0x0，初值:0x0000FFFF，宽度:32
 寄存器说明: SUBSYS config register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_wdt_apm_clken     : 1;  /* bit[0]    : isp subsys watchdog clock enable */
        unsigned int  isp_ipc_apm_clken     : 1;  /* bit[1]    : isp subsys IPC clock enable */
        unsigned int  isp_tim_apm_clken     : 1;  /* bit[2]    : isp subsys timer clock enable (apm clock) */
        unsigned int  sub_ctrl_reg0_7to3b   : 5;  /* bit[3-7]  : [3] isp subsys timer clock enable (sys clock)
                                                                 [7:4] reserved */
        unsigned int  sub_ctrl_reg0_15to8b  : 8;  /* bit[8-15] : reserved for eco */
        unsigned int  sub_ctrl_reg0_23to16b : 8;  /* bit[16-23]: reserved for eco */
        unsigned int  sub_ctrl_reg0_31to24b : 8;  /* bit[24-31]: reserved for eco */
    } reg;
} SOC_ISP_SUB_CTRL_SUBSYS_CFG_UNION;
#endif
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_wdt_apm_clken_START      (0)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_wdt_apm_clken_END        (0)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_ipc_apm_clken_START      (1)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_ipc_apm_clken_END        (1)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_tim_apm_clken_START      (2)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_tim_apm_clken_END        (2)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_7to3b_START    (3)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_7to3b_END      (7)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_15to8b_START   (8)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_15to8b_END     (15)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_23to16b_START  (16)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_23to16b_END    (23)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_31to24b_START  (24)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_31to24b_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_CORE_CFG_UNION
 结构说明  : ISP_CORE_CFG 寄存器结构定义。地址偏移量:0x4，初值:0x000000FF，宽度:32
 寄存器说明: configure register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sub_ctrl_reg1_7to0b   : 8;  /* bit[0-7]  : reserved for eco */
        unsigned int  sub_ctrl_reg1_15to8b  : 8;  /* bit[8-15] : [15:10] reserved;
                                                                 [9]: timer soft reset, set 1 to reset core, then set 0 to clear reset state.
                                                                 [8]: isp core soft reset, set 1 to reset core, then set 0 to clear reset state. */
        unsigned int  sub_ctrl_reg1_23to16b : 8;  /* bit[16-23]: reserved for eco */
        unsigned int  sub_ctrl_reg1_31to24b : 8;  /* bit[24-31]: reserved for eco */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_CORE_CFG_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_7to0b_START    (0)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_7to0b_END      (7)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_15to8b_START   (8)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_15to8b_END     (15)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_23to16b_START  (16)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_23to16b_END    (23)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_31to24b_START  (24)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_31to24b_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_UNION
 结构说明  : ISP_AXI_BUS_0 寄存器结构定义。地址偏移量:0x8，初值:0x00000000，宽度:32
 寄存器说明: ERROR information register0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m1_waddr_err : 32; /* bit[0-31]: error isp_axi master1 write address[33:2] */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_isp_axi_m1_waddr_err_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_isp_axi_m1_waddr_err_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_UNION
 结构说明  : ISP_AXI_BUS_1 寄存器结构定义。地址偏移量:0xC，初值:0x00000000，宽度:32
 寄存器说明: ERROR information register1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m1_raddr_err : 32; /* bit[0-31]: error isp_axi master1 read address[33:2] */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_isp_axi_m1_raddr_err_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_isp_axi_m1_raddr_err_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_UNION
 结构说明  : ISP_AXI_BUS_2 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: ERROR information register2.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m2_waddr_err : 32; /* bit[0-31]: error isp_axi master2 write address[33:2] */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_isp_axi_m2_waddr_err_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_isp_axi_m2_waddr_err_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_UNION
 结构说明  : ISP_AXI_BUS_3 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: ERROR information register3.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m2_raddr_err : 32; /* bit[0-31]: error isp_axi master2 read address[33:2] */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_isp_axi_m2_raddr_err_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_isp_axi_m2_raddr_err_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_UNION
 结构说明  : ISP_AXI_BUS_4 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: ERROR clear register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_mst_err_srst_req_apm : 1;  /* bit[0]   : clear ISP_AXI_BUS master error information (apm clock domain) */
        unsigned int  reserved_0                   : 7;  /* bit[1-7] : reserved */
        unsigned int  reserved_1                   : 1;  /* bit[8]   : reserved */
        unsigned int  reserved_2                   : 23; /* bit[9-31]: reserved */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_isp_axi_mst_err_srst_req_apm_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_isp_axi_mst_err_srst_req_apm_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_UNION
 结构说明  : ISP_AXI_BUS_5 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: readonly register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sub_ctrl_ro_reg : 32; /* bit[0-31]: sub_ctrl_ro_reg[1:0]:isp_axi_m1_waddr_err[1:0];
                                                          sub_ctrl_ro_reg[3:2]:isp_axi_m1_raddr_err[1:0];
                                                          sub_ctrl_ro_reg[5:4]:isp_axi_m2_waddr_err[1:0];
                                                          sub_ctrl_ro_reg[7:6]:isp_axi_m2_raddr_err[1:0];
                                                          sub_ctrl_ro_reg[11:8]:isp_axi_mst_err[3:0]({m2_rd_err,m2_wr_err,m1_rd_err,m1_wr_err}); */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_sub_ctrl_ro_reg_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_sub_ctrl_ro_reg_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_UNION
 结构说明  : ISP_core_ctrl_0 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: cfg register group0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  subctrl_to_core_grp0 : 32; /* bit[0-31]: [1:0]: overf_prot used for isp bus module;
                                                                00:disable overtime protect function;
                                                                01:start overtime protection after 512cycles;
                                                                10:start overtime protection after 1024cycles;
                                                                11:start overtime protection after 2048cycles;
                                                               [2]: dw_axi_rs_gatedclock_en in bus, not used.
                                                               [3]: dw_axi_gs_gatedclock_en used for gs dynamic clock control inisp bus module;//should be always set to be 1'b0;
                                                               [4]: gatedclock_en used for isp bus module; //not used by bus module now;
                                                               [31:5]reserved */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_subctrl_to_core_grp0_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_subctrl_to_core_grp0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_UNION
 结构说明  : ISP_core_ctrl_1 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: cfg register group1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  subctrl_to_core_grp1 : 32; /* bit[0-31]: reserved */
    } reg;
} SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_subctrl_to_core_grp1_START  (0)
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_subctrl_to_core_grp1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_vic0_out0_UNION
 结构说明  : vic0_out0 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: readonly register vic0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic0_out_irq_mask : 32; /* bit[0-31]: vic0 output irq status; */
    } reg;
} SOC_ISP_SUB_CTRL_vic0_out0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic0_out0_vic0_out_irq_mask_START  (0)
#define SOC_ISP_SUB_CTRL_vic0_out0_vic0_out_irq_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_vic0_in0_UNION
 结构说明  : vic0_in0 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: vic0 contgrol reg group0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic0_in_irq_level_mask : 32; /* bit[0-31]: vic0 irq mask bit,"1" will mask the input irq; */
    } reg;
} SOC_ISP_SUB_CTRL_vic0_in0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic0_in0_vic0_in_irq_level_mask_START  (0)
#define SOC_ISP_SUB_CTRL_vic0_in0_vic0_in_irq_level_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_vic0_in1_UNION
 结构说明  : vic0_in1 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: vic0 contgrol reg group1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic0_in_irq_level_force : 32; /* bit[0-31]: vic0 irq force bit, "1" will force an irq generation; */
    } reg;
} SOC_ISP_SUB_CTRL_vic0_in1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic0_in1_vic0_in_irq_level_force_START  (0)
#define SOC_ISP_SUB_CTRL_vic0_in1_vic0_in_irq_level_force_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_vic1_out0_UNION
 结构说明  : vic1_out0 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: readonly register vic1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic1_out_irq_mask : 32; /* bit[0-31]: vic1 output irq status; */
    } reg;
} SOC_ISP_SUB_CTRL_vic1_out0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic1_out0_vic1_out_irq_mask_START  (0)
#define SOC_ISP_SUB_CTRL_vic1_out0_vic1_out_irq_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_vic1_in0_UNION
 结构说明  : vic1_in0 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: vic1 contgrol reg group0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic1_in_irq_level_mask : 32; /* bit[0-31]: vic1 irq mask bit,"1" will mask the input irq; */
    } reg;
} SOC_ISP_SUB_CTRL_vic1_in0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic1_in0_vic1_in_irq_level_mask_START  (0)
#define SOC_ISP_SUB_CTRL_vic1_in0_vic1_in_irq_level_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SUB_CTRL_vic1_in1_UNION
 结构说明  : vic1_in1 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: vic1 contgrol reg group1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic1_in_irq_level_force : 32; /* bit[0-31]: vic1 irq force bit, "1" will force an irq generation; */
    } reg;
} SOC_ISP_SUB_CTRL_vic1_in1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic1_in1_vic1_in_irq_level_force_START  (0)
#define SOC_ISP_SUB_CTRL_vic1_in1_vic1_in_irq_level_force_END    (31)






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

#endif /* end of soc_isp_sub_ctrl_interface.h */
