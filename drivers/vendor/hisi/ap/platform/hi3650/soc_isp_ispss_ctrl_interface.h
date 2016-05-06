/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_ispss_ctrl_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:57
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_ISPSS_CTRL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_ISPSS_CTRL_INTERFACE_H__
#define __SOC_ISP_ISPSS_CTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) ISPSS_CTRL
 ****************************************************************************/
/* 寄存器说明：IP identification number
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_IP_ID_UNION */
#define SOC_ISP_ISPSS_CTRL_IP_ID_ADDR(base)           ((base) + (0x0000))

/* 寄存器说明：IP version number
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_VERSION_ID_UNION */
#define SOC_ISP_ISPSS_CTRL_VERSION_ID_ADDR(base)      ((base) + (0x0004))

/* 寄存器说明：IP revision number
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_REVISION_ID_UNION */
#define SOC_ISP_ISPSS_CTRL_REVISION_ID_ADDR(base)     ((base) + (0x0008))

/* 寄存器说明：SW module clock gating Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_ADDR(base)  ((base) + (0x0010))

/* 寄存器说明：SW module clock gating Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_ADDR(base) ((base) + (0x0014))

/* 寄存器说明：SW module clock gating Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：SW module clock gating Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_ADDR(base) ((base) + (0x001C))

/* 寄存器说明：SW module clock gating Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_ADDR(base) ((base) + (0x0020))

/* 寄存器说明：SW module clock gating Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_ADDR(base) ((base) + (0x0024))

/* 寄存器说明：SW module clock gating Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_ADDR(base) ((base) + (0x0028))

/* 寄存器说明：Memory light_sleep Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_ADDR(base)  ((base) + (0x0040))

/* 寄存器说明：Memory light_sleep Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_ADDR(base)  ((base) + (0x0044))

/* 寄存器说明：Memory light_sleep Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_ADDR(base) ((base) + (0x0048))

/* 寄存器说明：Memory light_sleep Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_ADDR(base) ((base) + (0x004C))

/* 寄存器说明：Memory light_sleep Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_ADDR(base) ((base) + (0x0050))

/* 寄存器说明：Memory light_sleep Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_ADDR(base) ((base) + (0x0054))

/* 寄存器说明：Module Reset Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_ADDR(base) ((base) + (0x0060))

/* 寄存器说明：Module Reset Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_ADDR(base) ((base) + (0x0064))

/* 寄存器说明：Module Reset Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_ADDR(base) ((base) + (0x0068))

/* 寄存器说明：Module Reset Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_ADDR(base) ((base) + (0x006C))

/* 寄存器说明：Module Reset Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_ADDR(base) ((base) + (0x0070))

/* 寄存器说明：Module Reset Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_ADDR(base) ((base) + (0x0074))

/* 寄存器说明：Module Reset Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_ADDR(base) ((base) + (0x0078))

/* 寄存器说明：Pipe configuration control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CONTROL_UNION */
#define SOC_ISP_ISPSS_CTRL_CONTROL_ADDR(base)         ((base) + (0x0090))

/* 寄存器说明：Pipe configuration control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_ADDR(base)    ((base) + (0x0094))

/* 寄存器说明：Pipe configuration control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_ADDR(base)    ((base) + (0x0098))

/* 寄存器说明：CVDR Read Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_UNION */
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_ADDR(base)    ((base) + (0x0100))

/* 寄存器说明：CVDR Write Control
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_UNION */
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_ADDR(base)    ((base) + (0x0104))

/* 寄存器说明：Local Time Stamp low
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_LST_LOW_UNION */
#define SOC_ISP_ISPSS_CTRL_LST_LOW_ADDR(base)         ((base) + (0x0120))

/* 寄存器说明：Local Time Stamp high
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_LST_HIGH_UNION */
#define SOC_ISP_ISPSS_CTRL_LST_HIGH_ADDR(base)        ((base) + (0x0124))

/* 寄存器说明：Select ITAP and OTAP location
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_ADDR(base)    ((base) + (0x0130))

/* 寄存器说明：Select ITAP and OTAP location
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_ADDR(base)    ((base) + (0x0134))

/* 寄存器说明：Crop horizontal offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_ADDR(base)     ((base) + (0x0140))

/* 寄存器说明：Crop vertical offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_ADDR(base)     ((base) + (0x0144))

/* 寄存器说明：Crop horizontal offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_ADDR(base)     ((base) + (0x0148))

/* 寄存器说明：Crop  vertical offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_ADDR(base)     ((base) + (0x014C))

/* 寄存器说明：Generic Output
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_GPO_UNION */
#define SOC_ISP_ISPSS_CTRL_GPO_ADDR(base)             ((base) + (0x0160))

/* 寄存器说明：Generic Output CTRL
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_UNION */
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_ADDR(base)      ((base) + (0x0164))

/* 寄存器说明：Generic Output CTRL
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_UNION */
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_ADDR(base)      ((base) + (0x0168))

/* 寄存器说明：first half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_1_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_1_ADDR(base) ((base) + (0x0170))

/* 寄存器说明：second half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_2_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_2_ADDR(base) ((base) + (0x0174))

/* 寄存器说明：first half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_1_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_1_ADDR(base) ((base) + (0x0178))

/* 寄存器说明：second half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_2_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_2_ADDR(base) ((base) + (0x017C))

/* 寄存器说明：first half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_1_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_1_ADDR(base) ((base) + (0x0180))

/* 寄存器说明：second half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_2_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_2_ADDR(base) ((base) + (0x0184))

/* 寄存器说明：first half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_1_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_1_ADDR(base) ((base) + (0x0188))

/* 寄存器说明：second half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_2_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_2_ADDR(base) ((base) + (0x018C))

/* 寄存器说明：first half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_1_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_1_ADDR(base) ((base) + (0x0190))

/* 寄存器说明：second half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_2_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_2_ADDR(base) ((base) + (0x0194))

/* 寄存器说明：first half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_1_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_1_ADDR(base) ((base) + (0x0198))

/* 寄存器说明：second half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_2_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_2_ADDR(base) ((base) + (0x019C))

/* 寄存器说明：first half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_1_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_1_ADDR(base) ((base) + (0x01A0))

/* 寄存器说明：second half of programmable pattern for GPO configuration in PWM
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_2_UNION */
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_2_ADDR(base) ((base) + (0x01A4))

/* 寄存器说明：clock divider
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PRE_DIV_UNION */
#define SOC_ISP_ISPSS_CTRL_PRE_DIV_ADDR(base)         ((base) + (0x01B0))

/* 寄存器说明：Crop horizontal offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_ADDR(base)     ((base) + (0x01B4))

/* 寄存器说明：Crop vertical offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_ADDR(base)     ((base) + (0x01B8))

/* 寄存器说明：Crop horizontal offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_ADDR(base)     ((base) + (0x01BC))

/* 寄存器说明：Crop vertical offsets
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_UNION */
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_ADDR(base)     ((base) + (0x01C0))

/* 寄存器说明：VPBG control registers (second number:_1 and _2 are used to distinguish pipe 1 and pipe)
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_UNION */
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ADDR(base)     ((base) + (0x01D0))

/* 寄存器说明：VPBG control registers (second number:_1 and _2 are used to distinguish pipe 1 and pipe)
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_UNION */
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ADDR(base)     ((base) + (0x01D4))

/* 寄存器说明：VPBG control registers (second number:_1 and _2 are used to distinguish pipe 1 and pipe)
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_UNION */
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_ADDR(base)     ((base) + (0x01D8))

/* 寄存器说明：debug status for PHY CSI-A
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_UNION */
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ADDR(base)   ((base) + (0x01E0))

/* 寄存器说明：debug status for PHY CSI-A
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_UNION */
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ADDR(base)   ((base) + (0x01E4))

/* 寄存器说明：debug status for PHY CSI-A
   位域定义UNION结构:  SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_UNION */
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ADDR(base)   ((base) + (0x01E8))





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
                     (1/1) ISPSS_CTRL
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_IP_ID_UNION
 结构说明  : IP_ID 寄存器结构定义。地址偏移量:0x0000，初值:0x48495350，宽度:32
 寄存器说明: IP identification number
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_id : 32; /* bit[0-31]: IP identification ID */
    } reg;
} SOC_ISP_ISPSS_CTRL_IP_ID_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_IP_ID_ip_id_START  (0)
#define SOC_ISP_ISPSS_CTRL_IP_ID_ip_id_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_VERSION_ID_UNION
 结构说明  : VERSION_ID 寄存器结构定义。地址偏移量:0x0004，初值:0x56313030，宽度:32
 寄存器说明: IP version number
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_version : 32; /* bit[0-31]: IP version ID */
    } reg;
} SOC_ISP_ISPSS_CTRL_VERSION_ID_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_VERSION_ID_ip_version_START  (0)
#define SOC_ISP_ISPSS_CTRL_VERSION_ID_ip_version_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_REVISION_ID_UNION
 结构说明  : REVISION_ID 寄存器结构定义。地址偏移量:0x0008，初值:0x000000A0，宽度:32
 寄存器说明: IP revision number
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_revision : 32; /* bit[0-31]: IP revision ID (to be filled later)
                                                      First version of BUILD 1 is generated in 20140415, so rev_id is 0x140415a1 (planned)
                                                      Second Version of BUILD 2 is generated in 20140530, so rev_id is 0x140530b2 (planned)
                                                      100% Netlist Version is generated in 20141110,so rev_id is 0x141110a1 */
    } reg;
} SOC_ISP_ISPSS_CTRL_REVISION_ID_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_REVISION_ID_ip_revision_START  (0)
#define SOC_ISP_ISPSS_CTRL_REVISION_ID_ip_revision_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_UNION
 结构说明  : MODULE_CGR_TOP 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: SW module clock gating Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cgr_0    : 1;  /* bit[0]    : Functional clock on module PRESCALER is gated when set to 0 */
        unsigned int  cgr_1    : 1;  /* bit[1]    : Functional clock on module SCALER_3 is gated when set to 0 */
        unsigned int  cgr_2    : 1;  /* bit[2]    : Functional clock on module FD is gated when set to 0 */
        unsigned int  cgr_3    : 1;  /* bit[3]    : Functional clock on module JPGENC is gated when set to 0 */
        unsigned int  cgr_4    : 1;  /* bit[4]    : Functional clock on module CVDR_SRAM is gated when set to 0 */
        unsigned int  cgr_5    : 1;  /* bit[5]    : Functional clock on module CVDR_RT is gated when set to 0 */
        unsigned int  cgr_6    : 1;  /* bit[6]    : Functional clock on module STREAM_ROUTER is gated when set to 0 */
        unsigned int  cgr_7    : 1;  /* bit[7]    : Functional clock on module CSI2IF_A is gated when set to 0 */
        unsigned int  cgr_8    : 1;  /* bit[8]    : Functional clock on module CSI2IF_B is gated when set to 0 */
        unsigned int  cgr_9    : 1;  /* bit[9]    : Functional clock on module CSI2IF_C is gated when set to 0 */
        unsigned int  cgr_10   : 1;  /* bit[10]   : Functional clock on module I2C_2 is gated when set to 0 */
        unsigned int  cgr_11   : 1;  /* bit[11]   : Functional clock on module I2C_1 is gated when set to 0 */
        unsigned int  cgr_12   : 1;  /* bit[12]   : Functional clock on module I2C_3 is gated when set to 0 */
        unsigned int  cgr_13   : 1;  /* bit[13]   : Functional clock on module DEBUG is gated when set to 0 */
        unsigned int  reserved : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_7_END       (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_8_START     (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_8_END       (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_9_START     (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_9_END       (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_10_START    (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_10_END      (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_11_START    (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_11_END      (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_12_START    (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_12_END      (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_13_START    (13)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_cgr_13_END      (13)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_UNION
 结构说明  : MODULE_CGR_TOP_P1 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: SW module clock gating Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cgr_0    : 1;  /* bit[0]   : Functional clock on module FBCRAW_(x) is gated when set to 0 */
        unsigned int  cgr_1    : 1;  /* bit[1]   : Functional clock on module FBDRAW_(x) is gated when set to 0 */
        unsigned int  cgr_2    : 1;  /* bit[2]   : Functional clock on module FBCYUV_(x) is gated when set to 0 */
        unsigned int  cgr_3    : 1;  /* bit[3]   : Functional clock on module FBDYUV_(x) is gated when set to 0 */
        unsigned int  cgr_4    : 1;  /* bit[4]   : Functional clock on module SCALER_1_(x) is gated when set to 0 */
        unsigned int  cgr_5    : 1;  /* bit[5]   : Functional clock on module SCALER_2_(x) is gated when set to 0 */
        unsigned int  reserved : 26; /* bit[6-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P1_cgr_5_END       (5)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_UNION
 结构说明  : MODULE_CGR_TOP_P2 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: SW module clock gating Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cgr_0    : 1;  /* bit[0]   : Functional clock on module FBCRAW_(x) is gated when set to 0 */
        unsigned int  cgr_1    : 1;  /* bit[1]   : Functional clock on module FBDRAW_(x) is gated when set to 0 */
        unsigned int  cgr_2    : 1;  /* bit[2]   : Functional clock on module FBCYUV_(x) is gated when set to 0 */
        unsigned int  cgr_3    : 1;  /* bit[3]   : Functional clock on module FBDYUV_(x) is gated when set to 0 */
        unsigned int  cgr_4    : 1;  /* bit[4]   : Functional clock on module SCALER_1_(x) is gated when set to 0 */
        unsigned int  cgr_5    : 1;  /* bit[5]   : Functional clock on module SCALER_2_(x) is gated when set to 0 */
        unsigned int  reserved : 26; /* bit[6-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_TOP_P2_cgr_5_END       (5)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_UNION
 结构说明  : MODULE_CGR_FE_P1 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: SW module clock gating Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cgr0     : 1;  /* bit[0]    : Functional clock on module BLC_(x) is gated when set to 0 */
        unsigned int  cgr_1    : 1;  /* bit[1]    : Functional clock on module DGAMMA_(x) is gated when set to 0 */
        unsigned int  cgr_2    : 1;  /* bit[2]    : Functional clock on module LSC_(x) is gated when set to 0 */
        unsigned int  cgr_3    : 1;  /* bit[3]    : Functional clock on module DPCC_(x) is gated when set to 0 */
        unsigned int  cgr_4    : 1;  /* bit[4]    : Functional clock on module STAT3A_(x) is gated when set to 0 */
        unsigned int  cgr_5    : 1;  /* bit[5]    : Functional clock on module STATDIS_(x) is gated when set to 0 */
        unsigned int  cgr_6    : 1;  /* bit[6]    : Functional clock on module RAWNF_(x) is gated when set to 0 */
        unsigned int  cgr_7    : 1;  /* bit[7]    : Functional clock on module BAS_(x) is gated when set to 0 */
        unsigned int  reserved_0: 1;  /* bit[8]    : reserved */
        unsigned int  reserved_1: 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2: 22; /* bit[10-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr0_START      (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr0_END        (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P1_cgr_7_END       (7)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_UNION
 结构说明  : MODULE_CGR_FE_P2 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: SW module clock gating Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cgr0     : 1;  /* bit[0]    : Functional clock on module BLC_(x) is gated when set to 0 */
        unsigned int  cgr_1    : 1;  /* bit[1]    : Functional clock on module DGAMMA_(x) is gated when set to 0 */
        unsigned int  cgr_2    : 1;  /* bit[2]    : Functional clock on module LSC_(x) is gated when set to 0 */
        unsigned int  cgr_3    : 1;  /* bit[3]    : Functional clock on module DPCC_(x) is gated when set to 0 */
        unsigned int  cgr_4    : 1;  /* bit[4]    : Functional clock on module STAT3A_(x) is gated when set to 0 */
        unsigned int  cgr_5    : 1;  /* bit[5]    : Functional clock on module STATDIS_(x) is gated when set to 0 */
        unsigned int  cgr_6    : 1;  /* bit[6]    : Functional clock on module RAWNF_(x) is gated when set to 0 */
        unsigned int  cgr_7    : 1;  /* bit[7]    : Functional clock on module BAS_(x) is gated when set to 0 */
        unsigned int  reserved_0: 1;  /* bit[8]    : reserved */
        unsigned int  reserved_1: 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2: 22; /* bit[10-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr0_START      (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr0_END        (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_FE_P2_cgr_7_END       (7)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_UNION
 结构说明  : MODULE_CGR_BE_P1 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: SW module clock gating Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cgr_0    : 1;  /* bit[0]    : Functional clock on module AWBGAIN_(x) is gated when set to 0 */
        unsigned int  cgr_1    : 1;  /* bit[1]    : Functional clock on module GCD_(x) is gated when set to 0 */
        unsigned int  cgr_2    : 1;  /* bit[2]    : Functional clock on module UVUP_(x) is gated when set to 0  */
        unsigned int  cgr_3    : 1;  /* bit[3]    : Functional clock on module CC_(x) is gated when set to 0 */
        unsigned int  cgr_4    : 1;  /* bit[4]    : Functional clock on module DRC_(x) is gated when set to 0 */
        unsigned int  cgr_5    : 1;  /* bit[5]    : Functional clock on module GAMMA_(x) is gated when set to 0 */
        unsigned int  cgr_6    : 1;  /* bit[6]    : Functional clock on module YUV2RGB_(x) is gated when set to 0 */
        unsigned int  cgr_7    : 1;  /* bit[7]    : Functional clock on module UVDEC_(x) is gated when set to 0 */
        unsigned int  cgr_8    : 1;  /* bit[8]    : Functional clock on module CE_(x) is gated when set to 0 */
        unsigned int  cgr_9    : 1;  /* bit[9]    : Functional clock on module YUVNF_(x) is gated when set to 0 */
        unsigned int  cgr_10   : 1;  /* bit[10]   : Functional clock on module SHARPEN_(x) is gated when set to 0 */
        unsigned int  cgr_11   : 1;  /* bit[11]   : Functional clock on module TNR_(x) is gated when set to 0 */
        unsigned int  cgr_12   : 1;  /* bit[12]   : Functional clock on module IE_(x) is gated when set to 0 */
        unsigned int  reserved : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_7_END       (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_8_START     (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_8_END       (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_9_START     (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_9_END       (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_10_START    (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_10_END      (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_11_START    (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_11_END      (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_12_START    (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P1_cgr_12_END      (12)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_UNION
 结构说明  : MODULE_CGR_BE_P2 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: SW module clock gating Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cgr_0    : 1;  /* bit[0]    : Functional clock on module AWBGAIN_(x) is gated when set to 0 */
        unsigned int  cgr_1    : 1;  /* bit[1]    : Functional clock on module GCD_(x) is gated when set to 0 */
        unsigned int  cgr_2    : 1;  /* bit[2]    : Functional clock on module UVUP_(x) is gated when set to 0  */
        unsigned int  cgr_3    : 1;  /* bit[3]    : Functional clock on module CC_(x) is gated when set to 0 */
        unsigned int  cgr_4    : 1;  /* bit[4]    : Functional clock on module DRC_(x) is gated when set to 0 */
        unsigned int  cgr_5    : 1;  /* bit[5]    : Functional clock on module GAMMA_(x) is gated when set to 0 */
        unsigned int  cgr_6    : 1;  /* bit[6]    : Functional clock on module YUV2RGB_(x) is gated when set to 0 */
        unsigned int  cgr_7    : 1;  /* bit[7]    : Functional clock on module UVDEC_(x) is gated when set to 0 */
        unsigned int  cgr_8    : 1;  /* bit[8]    : Functional clock on module CE_(x) is gated when set to 0 */
        unsigned int  cgr_9    : 1;  /* bit[9]    : Functional clock on module YUVNF_(x) is gated when set to 0 */
        unsigned int  cgr_10   : 1;  /* bit[10]   : Functional clock on module SHARPEN_(x) is gated when set to 0 */
        unsigned int  cgr_11   : 1;  /* bit[11]   : Functional clock on module TNR_(x) is gated when set to 0 */
        unsigned int  cgr_12   : 1;  /* bit[12]   : Functional clock on module IE_(x) is gated when set to 0 */
        unsigned int  reserved : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_7_END       (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_8_START     (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_8_END       (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_9_START     (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_9_END       (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_10_START    (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_10_END      (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_11_START    (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_11_END      (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_12_START    (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_CGR_BE_P2_cgr_12_END      (12)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_UNION
 结构说明  : MEM_PWR_CLK_P1 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: Memory light_sleep Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  light_sleep_0  : 1;  /* bit[0]    : Put all memories of ISP_FE_(x) except BAS_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_1  : 1;  /* bit[1]    : Put all memories of BAS_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_2  : 1;  /* bit[2]    : Put all memories of ISP_BE_(x) except TNR_(x) in light_sleep when set to 1 */
        unsigned int  light_sleep_3  : 1;  /* bit[3]    : Put all memories of TNR_(x) in light_sleep when set to 1 */
        unsigned int  light_sleep_4  : 1;  /* bit[4]    : Put all memories of SCALER_1_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_5  : 1;  /* bit[5]    : Put all memories of SCALER_2_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_6  : 1;  /* bit[6]    : Put all memories of CDVR_RT_(x) in light_sleep when set to 1 */
        unsigned int  light_sleep_7  : 1;  /* bit[7]    : Put all memories of E_SRAM_(x) (64KB - block A)in light_sleep when set to 1 */
        unsigned int  light_sleep_8  : 1;  /* bit[8]    : Put all memories of STREAM_ROUTER in light_sleep when set to 1 */
        unsigned int  light_sleep_9  : 1;  /* bit[9]    : Put all memories of PRESCALER in light_sleep when set to 1 */
        unsigned int  light_sleep_10 : 1;  /* bit[10]   : Put all memories of SCALER_3 in light_sleep when set to 1 */
        unsigned int  light_sleep_11 : 1;  /* bit[11]   : Put all memories of JPGENC in light_sleep when set to 1 */
        unsigned int  light_sleep_12 : 1;  /* bit[12]   : Put all memories of FD in light_sleep when set to 1 */
        unsigned int  light_sleep_13 : 1;  /* bit[13]   : Put all memories of DEBUG in light_sleep when set to 1 */
        unsigned int  light_sleep_14 : 1;  /* bit[14]   : Put all memories of FBCRAW_(x) and FBDRAW_(x) channels associated to pipe (x) in light_sleep when set to 1 */
        unsigned int  light_sleep_15 : 1;  /* bit[15]   : Put all memories of FBCYUV_(x) and FBDYUV_(x) channels associated to pipe (x) in light_sleep when set to 1 */
        unsigned int  light_sleep_16 : 1;  /* bit[16]   : Put all memories of Frame_merger when set to 1 */
        unsigned int  light_sleep_17 : 1;  /* bit[17]   : Put all memories of E_SRAM_(x) (32KB - block C)in light_sleep when set to 1 */
        unsigned int  light_sleep_18 : 1;  /* bit[18]   : Put all memories of E_SRAM_(x) (32KB - block B)in light_sleep when set to 1 */
        unsigned int  reserved       : 13; /* bit[19-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_0_START   (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_0_END     (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_1_START   (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_1_END     (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_2_START   (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_2_END     (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_3_START   (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_3_END     (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_4_START   (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_4_END     (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_5_START   (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_5_END     (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_6_START   (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_6_END     (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_7_START   (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_7_END     (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_8_START   (8)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_8_END     (8)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_9_START   (9)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_9_END     (9)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_10_START  (10)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_10_END    (10)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_11_START  (11)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_11_END    (11)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_12_START  (12)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_12_END    (12)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_13_START  (13)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_13_END    (13)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_14_START  (14)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_14_END    (14)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_15_START  (15)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_15_END    (15)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_16_START  (16)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_16_END    (16)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_17_START  (17)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_17_END    (17)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_18_START  (18)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P1_light_sleep_18_END    (18)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_UNION
 结构说明  : MEM_PWR_CLK_P2 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: Memory light_sleep Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  light_sleep_0 : 1;  /* bit[0]   : Put all memories of ISP_FE_(x) except BAS_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_1 : 1;  /* bit[1]   : Put all memories of BAS_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_2 : 1;  /* bit[2]   : Put all memories of ISP_BE_(x) except TNR_(x) in light_sleep when set to 1 */
        unsigned int  light_sleep_3 : 1;  /* bit[3]   : Put all memories of TNR_(x) in light_sleep when set to 1 */
        unsigned int  light_sleep_4 : 1;  /* bit[4]   : Put all memories of SCALER_1_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_5 : 1;  /* bit[5]   : Put all memories of SCALER_2_(x)in light_sleep when set to 1 */
        unsigned int  light_sleep_6 : 1;  /* bit[6]   : reserved */
        unsigned int  light_sleep_7 : 1;  /* bit[7]   : Put all memories of FBCRAW_(x) and FBDRAW_(x) channels associated to pipe (x) in light_sleep when set to 1 */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_0_START  (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_0_END    (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_1_START  (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_1_END    (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_2_START  (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_2_END    (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_3_START  (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_3_END    (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_4_START  (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_4_END    (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_5_START  (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_5_END    (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_6_START  (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_6_END    (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_7_START  (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR_CLK_P2_light_sleep_7_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_UNION
 结构说明  : MEM_PWR2_CLK_P1 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: Memory light_sleep Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  deep_sleep_0  : 1;  /* bit[0]    : Put all memories of ISP_FE_(x) except BAS_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_1  : 1;  /* bit[1]    : Put all memories of BAS_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_2  : 1;  /* bit[2]    : Put all memories of ISP_BE_(x) except TNR_(x) in deep_sleep when set to 1 */
        unsigned int  deep_sleep_3  : 1;  /* bit[3]    : Put all memories of TNR_(x) in deep_sleep when set to 1 */
        unsigned int  deep_sleep_4  : 1;  /* bit[4]    : Put all memories of SCALER_1_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_5  : 1;  /* bit[5]    : Put all memories of SCALER_2_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_6  : 1;  /* bit[6]    : Put all memories of CDVR_RT_(x) ) in deep_sleep when set to 1 */
        unsigned int  deep_sleep_7  : 1;  /* bit[7]    : Put all memories of E_SRAM_(x) (64KB - block A)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_8  : 1;  /* bit[8]    : Put all memories of STREAM_ROUTER in deep_sleep when set to 1 */
        unsigned int  deep_sleep_9  : 1;  /* bit[9]    : Put all memories of PRESCALER in deep_sleep when set to 1 */
        unsigned int  deep_sleep_10 : 1;  /* bit[10]   : Put all memories of SCALER_3 in deep_sleep when set to 1 */
        unsigned int  deep_sleep_11 : 1;  /* bit[11]   : Put all memories of JPGENC in deep_sleep when set to 1 */
        unsigned int  deep_sleep_12 : 1;  /* bit[12]   : Put all memories of FD in deep_sleep when set to 1 */
        unsigned int  deep_sleep_13 : 1;  /* bit[13]   : Put all memories of DEBUG in deep_sleep when set to 1 */
        unsigned int  deep_sleep_14 : 1;  /* bit[14]   : Put all memories of FBCRAW_(x) and FBDRAW_(x) channels associated to pipe (x) in deep_sleep when set to 1 */
        unsigned int  deep_sleep_15 : 1;  /* bit[15]   : Put all memories of FBCYUV_(x) and FBDYUV_(x) channels associated to pipe (x) in deep_sleep when set to 1 */
        unsigned int  deep_sleep_16 : 1;  /* bit[16]   : Put all memories of Frame_merger when set to 1 */
        unsigned int  deep_sleep_17 : 1;  /* bit[17]   : Put all memories of E_SRAM_(x) (32KB - block C)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_18 : 1;  /* bit[18]   : Put all memories of E_SRAM_(x) (32KB - block B) in deep_sleep when set to 1 */
        unsigned int  reserved      : 13; /* bit[19-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_0_START   (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_0_END     (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_1_START   (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_1_END     (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_2_START   (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_2_END     (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_3_START   (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_3_END     (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_4_START   (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_4_END     (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_5_START   (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_5_END     (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_6_START   (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_6_END     (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_7_START   (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_7_END     (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_8_START   (8)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_8_END     (8)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_9_START   (9)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_9_END     (9)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_10_START  (10)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_10_END    (10)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_11_START  (11)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_11_END    (11)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_12_START  (12)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_12_END    (12)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_13_START  (13)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_13_END    (13)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_14_START  (14)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_14_END    (14)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_15_START  (15)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_15_END    (15)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_16_START  (16)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_16_END    (16)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_17_START  (17)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_17_END    (17)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_18_START  (18)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P1_deep_sleep_18_END    (18)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_UNION
 结构说明  : MEM_PWR2_CLK_P2 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: Memory light_sleep Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  deep_sleep_0 : 1;  /* bit[0]   : Put all memories of ISP_FE_(x) except BAS_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_1 : 1;  /* bit[1]   : Put all memories of BAS_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_2 : 1;  /* bit[2]   : Put all memories of ISP_BE_(x) except TNR_(x) in deep_sleep when set to 1 */
        unsigned int  deep_sleep_3 : 1;  /* bit[3]   : Put all memories of TNR_(x) in deep_sleep when set to 1 */
        unsigned int  deep_sleep_4 : 1;  /* bit[4]   : Put all memories of SCALER_1_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_5 : 1;  /* bit[5]   : Put all memories of SCALER_2_(x)in deep_sleep when set to 1 */
        unsigned int  deep_sleep_6 : 1;  /* bit[6]   : reserved */
        unsigned int  deep_sleep_7 : 1;  /* bit[7]   : Put all memories of FBCRAW_(x) and FBDRAW_(x) channels associated to pipe (x) in deep_sleep when set to 1 */
        unsigned int  reserved     : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_0_START  (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_0_END    (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_1_START  (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_1_END    (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_2_START  (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_2_END    (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_3_START  (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_3_END    (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_4_START  (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_4_END    (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_5_START  (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_5_END    (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_6_START  (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_6_END    (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_7_START  (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR2_CLK_P2_deep_sleep_7_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_UNION
 结构说明  : MEM_PWR3_CLK_P1 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: Memory light_sleep Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  power_down_0  : 1;  /* bit[0]    : Put all memories of ISP_FE_(x) except BAS_(x)in power_down when set to 1 */
        unsigned int  power_down_1  : 1;  /* bit[1]    : Put all memories of BAS_(x)in power_down when set to 1 */
        unsigned int  power_down_2  : 1;  /* bit[2]    : Put all memories of ISP_BE_(x) except TNR_(x) in power_down when set to 1 */
        unsigned int  power_down_3  : 1;  /* bit[3]    : Put all memories of TNR_(x) in power_down when set to 1 */
        unsigned int  power_down_4  : 1;  /* bit[4]    : Put all memories of SCALER_1_(x)in power_down when set to 1 */
        unsigned int  power_down_5  : 1;  /* bit[5]    : Put all memories of SCALER_2_(x)in power_down when set to 1 */
        unsigned int  power_down_6  : 1;  /* bit[6]    : Put all memories of CDVR_RT_(x) in power_down when set to 1 */
        unsigned int  power_down_7  : 1;  /* bit[7]    : Put all memories of E_SRAM_(x) (64KB -block C)in power_down when set to 1 */
        unsigned int  power_down_8  : 1;  /* bit[8]    : Put all memories of STREAM_ROUTER in power_down when set to 1 */
        unsigned int  power_down_9  : 1;  /* bit[9]    : Put all memories of PRESCALER in power_down when set to 1 */
        unsigned int  power_down_10 : 1;  /* bit[10]   : Put all memories of SCALER_3 in power_down when set to 1 */
        unsigned int  power_down_11 : 1;  /* bit[11]   : Put all memories of JPGENC in power_down when set to 1 */
        unsigned int  power_down_12 : 1;  /* bit[12]   : Put all memories of FD in power_down when set to 1 */
        unsigned int  power_down_13 : 1;  /* bit[13]   : Put all memories of DEBUG in power_down when set to 1 */
        unsigned int  power_down_14 : 1;  /* bit[14]   : Put all memories of FBCRAW_(x) and FBDRAW_(x) channels associated to pipe (x) in power_down when set to 1 */
        unsigned int  power_down_15 : 1;  /* bit[15]   : Put all memories of FBCYUV_(x) and FBDYUV_(x) channels associated to pipe (x) in power_down when set to 1 */
        unsigned int  power_down_16 : 1;  /* bit[16]   : Put all memories of Frame_merger when set to 1 */
        unsigned int  power_down_17 : 1;  /* bit[17]   : Put all memories of E_SRAM_(x) (32KB -block C)in power_down when set to 1 */
        unsigned int  power_down_18 : 1;  /* bit[18]   : Put all memories of E_SRAM_(x) (32KB -block B)in power_down when set to 1 */
        unsigned int  reserved      : 13; /* bit[19-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_0_START   (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_0_END     (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_1_START   (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_1_END     (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_2_START   (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_2_END     (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_3_START   (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_3_END     (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_4_START   (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_4_END     (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_5_START   (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_5_END     (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_6_START   (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_6_END     (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_7_START   (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_7_END     (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_8_START   (8)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_8_END     (8)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_9_START   (9)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_9_END     (9)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_10_START  (10)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_10_END    (10)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_11_START  (11)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_11_END    (11)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_12_START  (12)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_12_END    (12)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_13_START  (13)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_13_END    (13)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_14_START  (14)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_14_END    (14)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_15_START  (15)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_15_END    (15)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_16_START  (16)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_16_END    (16)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_17_START  (17)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_17_END    (17)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_18_START  (18)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P1_power_down_18_END    (18)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_UNION
 结构说明  : MEM_PWR3_CLK_P2 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: Memory light_sleep Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  power_down_0 : 1;  /* bit[0]   : Put all memories of ISP_FE_(x) except BAS_(x)in power_down when set to 1 */
        unsigned int  power_down_1 : 1;  /* bit[1]   : Put all memories of BAS_(x)in power_down when set to 1 */
        unsigned int  power_down_2 : 1;  /* bit[2]   : Put all memories of ISP_BE_(x) except TNR_(x) in power_down when set to 1 */
        unsigned int  power_down_3 : 1;  /* bit[3]   : Put all memories of TNR_(x) in power_down when set to 1 */
        unsigned int  power_down_4 : 1;  /* bit[4]   : Put all memories of SCALER_1_(x)in power_down when set to 1 */
        unsigned int  power_down_5 : 1;  /* bit[5]   : Put all memories of SCALER_2_(x)in power_down when set to 1 */
        unsigned int  power_down_6 : 1;  /* bit[6]   : reserved */
        unsigned int  power_down_7 : 1;  /* bit[7]   : Put all memories of FBCRAW_(x) and FBDRAW_(x) channels associated to pipe (x) in power_down when set to 1 */
        unsigned int  reserved     : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_0_START  (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_0_END    (0)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_1_START  (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_1_END    (1)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_2_START  (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_2_END    (2)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_3_START  (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_3_END    (3)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_4_START  (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_4_END    (4)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_5_START  (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_5_END    (5)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_6_START  (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_6_END    (6)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_7_START  (7)
#define SOC_ISP_ISPSS_CTRL_MEM_PWR3_CLK_P2_power_down_7_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_UNION
 结构说明  : MODULE_RESET_TOP 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: Module Reset Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_0    : 1;  /* bit[0]    : Reset PRESCALER when set to 1 */
        unsigned int  rst_1    : 1;  /* bit[1]    : Reset SCALER_3 when set to 1 */
        unsigned int  rst_2    : 1;  /* bit[2]    : Reset FD when set to 1 */
        unsigned int  rst_3    : 1;  /* bit[3]    : Reset JPGENC when set to 1 */
        unsigned int  rst_4    : 1;  /* bit[4]    : Reset CVDR_SRAM when set to 1 */
        unsigned int  rst_5    : 1;  /* bit[5]    : Reset CVDR_RT when set to 1 */
        unsigned int  rst_6    : 1;  /* bit[6]    : Reset STREAM_ROUTER when set to 1 */
        unsigned int  rst_7    : 1;  /* bit[7]    : Reset CSI2IF_A when set to 1 */
        unsigned int  rst_8    : 1;  /* bit[8]    : Reset CSI2IF_B when set to 1 */
        unsigned int  rst_9    : 1;  /* bit[9]    : Reset CSI2IF_C when set to 1 */
        unsigned int  rst_10   : 1;  /* bit[10]   : Reset I2C_2 when set to 1 */
        unsigned int  rst_11   : 1;  /* bit[11]   : Reset I2C_1 when set to 1 */
        unsigned int  rst_12   : 1;  /* bit[12]   : Reset I2C_3 when set to 1 */
        unsigned int  rst_13   : 1;  /* bit[13]   : Reset full ISP_FE_1 ( all sub_modules) when set to 1 */
        unsigned int  rst_14   : 1;  /* bit[14]   : Reset full ISP_FE_2 ( all sub_modules) when set to 1 */
        unsigned int  rst_15   : 1;  /* bit[15]   : Reset full ISP_BE_1 ( all sub_modules) when set to 1 */
        unsigned int  rst_16   : 1;  /* bit[16]   : Reset full ISP_BE_2 ( all sub_modules) when set to 1 */
        unsigned int  reserved : 15; /* bit[17-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_7_END       (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_8_START     (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_8_END       (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_9_START     (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_9_END       (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_10_START    (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_10_END      (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_11_START    (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_11_END      (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_12_START    (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_12_END      (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_13_START    (13)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_13_END      (13)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_14_START    (14)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_14_END      (14)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_15_START    (15)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_15_END      (15)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_16_START    (16)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_rst_16_END      (16)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_UNION
 结构说明  : MODULE_RESET_TOP_P1 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: Module Reset Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_0    : 1;  /* bit[0]   : Reset FBDRAW_(x) when set to 1 */
        unsigned int  rst_1    : 1;  /* bit[1]   : Reset FBCRAW_(x) when set to 1 */
        unsigned int  rst_2    : 1;  /* bit[2]   : Reset FBDYUV_(x) when set to 1 */
        unsigned int  rst_3    : 1;  /* bit[3]   : Reset FBCYUV_(x) when set to 1 */
        unsigned int  rst_4    : 1;  /* bit[4]   : Reset SCALER_1_(x) when set to 1 */
        unsigned int  rst_5    : 1;  /* bit[5]   : Reset SCALER_2_(x) when set to 1 */
        unsigned int  reserved : 26; /* bit[6-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P1_rst_5_END       (5)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_UNION
 结构说明  : MODULE_RESET_TOP_P2 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: Module Reset Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_0    : 1;  /* bit[0]   : Reset FBDRAW_(x) when set to 1 */
        unsigned int  rst_1    : 1;  /* bit[1]   : Reset FBCRAW_(x) when set to 1 */
        unsigned int  rst_2    : 1;  /* bit[2]   : Reset FBDYUV_(x) when set to 1 */
        unsigned int  rst_3    : 1;  /* bit[3]   : Reset FBCYUV_(x) when set to 1 */
        unsigned int  rst_4    : 1;  /* bit[4]   : Reset SCALER_1_(x) when set to 1 */
        unsigned int  rst_5    : 1;  /* bit[5]   : Reset SCALER_2_(x) when set to 1 */
        unsigned int  reserved : 26; /* bit[6-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_TOP_P2_rst_5_END       (5)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_UNION
 结构说明  : MODULE_RESET_FE_P1 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: Module Reset Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_0    : 1;  /* bit[0]   : Reset BLC_(x) when set to 1 */
        unsigned int  rst_1    : 1;  /* bit[1]   : Reset DGAMMA_(x) when set to 1 */
        unsigned int  rst_2    : 1;  /* bit[2]   : Reset LSC_(x) when set to 1 */
        unsigned int  rst_3    : 1;  /* bit[3]   : Reset DPCC_(x) when set to 1 */
        unsigned int  rst_4    : 1;  /* bit[4]   : Reset STAT3A_(x) when set to 1 */
        unsigned int  rst_5    : 1;  /* bit[5]   : Reset STATDIS_(x) when set to 1 */
        unsigned int  rst_6    : 1;  /* bit[6]   : Reset RAWNF_(x) when set to 1 */
        unsigned int  rst_7    : 1;  /* bit[7]   : Reset BAS_(x) when set to 1 */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P1_rst_7_END       (7)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_UNION
 结构说明  : MODULE_RESET_FE_P2 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: Module Reset Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_0    : 1;  /* bit[0]   : Reset BLC_(x) when set to 1 */
        unsigned int  rst_1    : 1;  /* bit[1]   : Reset DGAMMA_(x) when set to 1 */
        unsigned int  rst_2    : 1;  /* bit[2]   : Reset LSC_(x) when set to 1 */
        unsigned int  rst_3    : 1;  /* bit[3]   : Reset DPCC_(x) when set to 1 */
        unsigned int  rst_4    : 1;  /* bit[4]   : Reset STAT3A_(x) when set to 1 */
        unsigned int  rst_5    : 1;  /* bit[5]   : Reset STATDIS_(x) when set to 1 */
        unsigned int  rst_6    : 1;  /* bit[6]   : Reset RAWNF_(x) when set to 1 */
        unsigned int  rst_7    : 1;  /* bit[7]   : Reset BAS_(x) when set to 1 */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_FE_P2_rst_7_END       (7)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_UNION
 结构说明  : MODULE_RESET_BE_P1 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: Module Reset Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_0    : 1;  /* bit[0]    : Reset AWBGAIN_(x) when set to 1 */
        unsigned int  rst_1    : 1;  /* bit[1]    : Reset GCD_(x) when set to 1 */
        unsigned int  rst_2    : 1;  /* bit[2]    : Reset UVUP_(x) when set to 1  */
        unsigned int  rst_3    : 1;  /* bit[3]    : Reset CC_(x) when set to 1 */
        unsigned int  rst_4    : 1;  /* bit[4]    : Reset DRC_(x) when set to 1 */
        unsigned int  rst_5    : 1;  /* bit[5]    : Reset GAMMA_(x) when set to 1 */
        unsigned int  rst_6    : 1;  /* bit[6]    : Reset YUV2RGB_(x) when set to 1 */
        unsigned int  rst_7    : 1;  /* bit[7]    : Reset UVDEC_(x) when set to 1 */
        unsigned int  rst_8    : 1;  /* bit[8]    : Reset CE_(x) when set to 1 */
        unsigned int  rst_9    : 1;  /* bit[9]    : Reset YUVNF_(x) when set to 1 */
        unsigned int  rst_10   : 1;  /* bit[10]   : Reset SHARPEN_(x) when set to 1 */
        unsigned int  rst_11   : 1;  /* bit[11]   : Reset TNR_(x) when set to 1 */
        unsigned int  rst_12   : 1;  /* bit[12]   : Reset IE when set to 1 */
        unsigned int  reserved : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_7_END       (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_8_START     (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_8_END       (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_9_START     (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_9_END       (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_10_START    (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_10_END      (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_11_START    (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_11_END      (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_12_START    (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P1_rst_12_END      (12)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_UNION
 结构说明  : MODULE_RESET_BE_P2 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: Module Reset Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_0    : 1;  /* bit[0]    : Reset AWBGAIN_(x) when set to 1 */
        unsigned int  rst_1    : 1;  /* bit[1]    : Reset GCD_(x) when set to 1 */
        unsigned int  rst_2    : 1;  /* bit[2]    : Reset UVUP_(x) when set to 1  */
        unsigned int  rst_3    : 1;  /* bit[3]    : Reset CC_(x) when set to 1 */
        unsigned int  rst_4    : 1;  /* bit[4]    : Reset DRC_(x) when set to 1 */
        unsigned int  rst_5    : 1;  /* bit[5]    : Reset GAMMA_(x) when set to 1 */
        unsigned int  rst_6    : 1;  /* bit[6]    : Reset YUV2RGB_(x) when set to 1 */
        unsigned int  rst_7    : 1;  /* bit[7]    : Reset UVDEC_(x) when set to 1 */
        unsigned int  rst_8    : 1;  /* bit[8]    : Reset CE_(x) when set to 1 */
        unsigned int  rst_9    : 1;  /* bit[9]    : Reset YUVNF_(x) when set to 1 */
        unsigned int  rst_10   : 1;  /* bit[10]   : Reset SHARPEN_(x) when set to 1 */
        unsigned int  rst_11   : 1;  /* bit[11]   : Reset TNR_(x) when set to 1 */
        unsigned int  rst_12   : 1;  /* bit[12]   : Reset IE when set to 1 */
        unsigned int  reserved : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_0_START     (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_0_END       (0)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_3_START     (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_3_END       (3)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_4_START     (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_4_END       (4)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_5_START     (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_5_END       (5)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_6_START     (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_6_END       (6)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_7_START     (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_7_END       (7)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_8_START     (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_8_END       (8)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_9_START     (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_9_END       (9)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_10_START    (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_10_END      (10)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_11_START    (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_11_END      (11)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_12_START    (12)
#define SOC_ISP_ISPSS_CTRL_MODULE_RESET_BE_P2_rst_12_END      (12)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CONTROL_UNION
 结构说明  : CONTROL 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: Pipe configuration control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0               : 2;  /* bit[0-1]  : Reserved */
        unsigned int  fd_image_size            : 2;  /* bit[2-3]  : Define the size of the image processed by the FD
                                                                    00 -> QVGA (320x240)
                                                                    01 -> VGA (640x480)
                                                                    10 -> WQVGA (427x240)
                                                                    11 -> WVGA+ (854x480) */
        unsigned int  flash_mode               : 1;  /* bit[4]    : 0: sensor interface works independently from flash control unit 
                                                                    1: one frame is captured when signaled by flash control unit */
        unsigned int  reserved_1               : 1;  /* bit[5]    : Reserved */
        unsigned int  mode_esram               : 3;  /* bit[6-8]  : Static embedded SRAM connectity configuration
                                                                    The 128KB JPeg buffer can be allocated (static) to Jpeg/MPU/Stream router (to support DFS) 
                                                                    000: Full SRAM (128KB) allocated to JPEG only 
                                                                    001: Full SRAM (128KB) allocated to MPU (AXI)
                                                                    010: half SRAM (64KB) allocated to MPU (AXI) and half (64KB) to the second camera requiring extra buffer for DFS support(2 cameras UC)
                                                                    011: half SRAM allocated to second camera (64KB) and the remaining quarters (32KB) to the third camera and MPU (AXI).
                                                                    100: half SRAM allocated to JPGENC and half to the second camera requiring extra buffer for DFS support(2 cameras UC). 
                                                                    Others: reserved */
        unsigned int  disable_axi_data_packing : 1;  /* bit[9]    : This control is enabling the packing of a full burst in the AXI async bridge FIFO before the request is sent to the SOC. It has been added to secure the late AXI fix
                                                                    0: packing is active
                                                                    1: no packing */
        unsigned int  reserved_2               : 2;  /* bit[10-11]: This control is not used. Replaced by a control at the SOC level */
        unsigned int  reserved_3               : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CONTROL_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CONTROL_fd_image_size_START             (2)
#define SOC_ISP_ISPSS_CTRL_CONTROL_fd_image_size_END               (3)
#define SOC_ISP_ISPSS_CTRL_CONTROL_flash_mode_START                (4)
#define SOC_ISP_ISPSS_CTRL_CONTROL_flash_mode_END                  (4)
#define SOC_ISP_ISPSS_CTRL_CONTROL_mode_esram_START                (6)
#define SOC_ISP_ISPSS_CTRL_CONTROL_mode_esram_END                  (8)
#define SOC_ISP_ISPSS_CTRL_CONTROL_disable_axi_data_packing_START  (9)
#define SOC_ISP_ISPSS_CTRL_CONTROL_disable_axi_data_packing_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_UNION
 结构说明  : CONTROL_0_P1 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: Pipe configuration control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_fe_bypass        : 1;  /* bit[0]    : Select if the stream on ISP_BE_(x) (port 1) comes from the ISP_FE_(x) or stream_router.Used to drive the SELECT input of VPM2TO1_32_(x)
                                                                0 -> From ISP_FE_(x)
                                                                1 -> From STREAM_ROUTER  */
        unsigned int  isp_be_scaler_1      : 1;  /* bit[1]    : The scaler_1 can be used from memory to memory when it is not used for the image capture.Used to drive the SELECT input of VPM2TO1_38_(x)
                                                                0 -> The scaler_1 is connected to the ISP_BE_(x)
                                                                1 -> The scaler_1 is connected to the DRAM through the CDVR . */
        unsigned int  isp_be_scaler_2      : 1;  /* bit[2]    : The scaler_2 can be used from memory to memory when it is not used for the image capture. Used to drive the SELECT input of VPM2TO1_39_(x)
                                                                0 -> The scaler_2 is connected to the ISP_BE_(x)
                                                                1 -> The scaler_2 is connected to the DRAM through the CDVR . */
        unsigned int  reserved_0           : 1;  /* bit[3]    : Reserved */
        unsigned int  isp_fbcraw_sel1      : 1;  /* bit[4]    : The FBCRAW may be associated to the STREAM_ROUTER out or the the ISP_FE exclusively. For video use case, the compression is used on the ISP_FE (Vstab) whereas for the Still image capture of large image, RAW Frame is sent to DRAM after STREAM_ROUTER - VPM2TO1_40_(x)
                                                                0 -> Data from Stream_router is sent to FBCRAW
                                                                1 -> Data from ISP_FE is sent to FBCRAW. */
        unsigned int  isp_fbcraw_sel2      : 2;  /* bit[5-6]  : VPM2TO1_42_(x)
                                                                00 -> Data from STREAM_ROUTER is sent to DRAM
                                                                01 -> Data from FBCRAW is sent to DRAM
                                                                10 -> Data from ISP_FE is seent to DRAM
                                                                11 -> reserved ( same as 0b10) */
        unsigned int  isp_fbcraw_sel3      : 1;  /* bit[7]    : VPM2TO1_41_(x)
                                                                0 -> Data from ISP_FE is sent to DRAM
                                                                1 -> Data from FBCRAW is sent to DRAM */
        unsigned int  isp_fbdraw_sel1      : 1;  /* bit[8]    : Allow selection of FBDRAW to be used either on the ISP_FE input or on the ISP_BE input VPM2TO1_46_(x)
                                                                0 -> Data from CVDR(R1.x) is sent to FBDRAW
                                                                1 -> Data from CVDR(R10.x) is sent to FBDRAW */
        unsigned int  isp_fbdraw_sel2      : 1;  /* bit[9]    : Allow selection of FBDRAW to be used either on the ISP_FE input or on the ISP_BE input VPM2TO1_45_(x)
                                                                0 -> Data from CVDR(R10.x) is sent ISP_FE
                                                                1 -> Data from FBDRAW is sent ISP_FE */
        unsigned int  isp_fbdraw_sel3      : 1;  /* bit[10]   : Allow selection of FBDRAW to be used either on the ISP_FE input or on the ISP_BE input VPM2TO1_44_(x)
                                                                0 -> Data from FBDRAW is sent ISP_BE
                                                                1 -> Data from CVDR(R1.x) is sent ISP_BE */
        unsigned int  reserved_1           : 5;  /* bit[11-15]: Reserved for extra explicit VPM control */
        unsigned int  reserved_2           : 1;  /* bit[16]   : reserved( previously disable_pipe) */
        unsigned int  isp_be_1_to_jpgenc   : 1;  /* bit[17]   : Select connection between ISP_BE_1 and SCALER_1_1 to JPGENC 
                                                                0 -> JPGENC (port pipe 1)is connected to SCALER_1_1.Default configuration
                                                                1 -> JPEGENC (port pipe 1) is connected to ISP_BE_1 */
        unsigned int  pipe_1_to_scaler_1_2 : 1;  /* bit[18]   : Select connection to input of SCALER_1_2 between ISP_BE_1 or ISP_BE_2 (VPM_48_1)
                                                                0 -> SCALER_1_2 is connected to ISP_BE_2. Default configuration
                                                                1 -> SCALER_1_2 is connected to ISP_BE_1. */
        unsigned int  pipe_1_to_scaler_2_2 : 1;  /* bit[19]   : Select connection to input of SCALER_2_2 between ISP_BE_1 or ISP_BE_2 (VPM_49_1)
                                                                0 -> SCALER_2_2 is connected to ISP_BE_2. Default configuration
                                                                1 -> SCALER_2_2 is connected to ISP_BE_1.  */
        unsigned int  isp_be_1_to_dram     : 1;  /* bit[20]   : Select connection to DRAM between output of TNR_x and output of ISP_BE_x (VPM_51_1)
                                                                0 -> TNR_1 is connect to FBCYUV (DRAM). Default configuration
                                                                1 -> ISP_BE_1 is connected to FBDYUV (DRAM). */
        unsigned int  reserved_3           : 11; /* bit[21-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fe_bypass_START         (0)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fe_bypass_END           (0)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_scaler_1_START       (1)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_scaler_1_END         (1)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_scaler_2_START       (2)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_scaler_2_END         (2)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbcraw_sel1_START       (4)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbcraw_sel1_END         (4)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbcraw_sel2_START       (5)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbcraw_sel2_END         (6)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbcraw_sel3_START       (7)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbcraw_sel3_END         (7)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbdraw_sel1_START       (8)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbdraw_sel1_END         (8)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbdraw_sel2_START       (9)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbdraw_sel2_END         (9)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbdraw_sel3_START       (10)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_fbdraw_sel3_END         (10)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_1_to_jpgenc_START    (17)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_1_to_jpgenc_END      (17)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_pipe_1_to_scaler_1_2_START  (18)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_pipe_1_to_scaler_1_2_END    (18)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_pipe_1_to_scaler_2_2_START  (19)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_pipe_1_to_scaler_2_2_END    (19)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_1_to_dram_START      (20)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P1_isp_be_1_to_dram_END        (20)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_UNION
 结构说明  : CONTROL_0_P2 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: Pipe configuration control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_fe_bypass      : 1;  /* bit[0]    : Select if the stream on ISP_BE_(x) (port 1) comes from the ISP_FE_(x) or stream_router.Used to drive the SELECT input of VPM2TO1_32_(x)
                                                              0 -> From ISP_FE_(x)
                                                              1 -> From STREAM_ROUTER  */
        unsigned int  isp_be_scaler_1    : 1;  /* bit[1]    : The scaler_1 can be used from memory to memory when it is not used for the image capture.Used to drive the SELECT input of VPM2TO1_38_(x)
                                                              0 -> The scaler_1 is connected to the ISP_BE_(x)
                                                              1 -> The scaler_1 is connected to the DRAM through the CDVR . */
        unsigned int  isp_be_scaler_2    : 1;  /* bit[2]    : The scaler_2 can be used from memory to memory when it is not used for the image capture. Used to drive the SELECT input of VPM2TO1_39_(x)
                                                              0 -> The scaler_2 is connected to the ISP_BE_(x)
                                                              1 -> The scaler_2 is connected to the DRAM through the CDVR . */
        unsigned int  reserved_0         : 1;  /* bit[3]    : Reserved */
        unsigned int  isp_fbcraw_sel1    : 1;  /* bit[4]    : The FBCRAW may be associated to the STREAM_ROUTER out or the the ISP_FE exclusively. For video use case, the compression is used on the ISP_FE (Vstab) whereas for the Still image capture of large image, RAW Frame is sent to DRAM after STREAM_ROUTER - VPM2TO1_40_(x)
                                                              0 -> Data from Stream_router is sent to FBCRAW
                                                              1 -> Data from ISP_FE is sent to FBCRAW.  */
        unsigned int  isp_fbcraw_sel2    : 2;  /* bit[5-6]  : VPM2TO1_42_(x)
                                                              00 -> Data from STREAM_ROUTER is sent to DRAM
                                                              01 -> Data from FBCRAW is sent to DRAM
                                                              10 -> Data from ISP_FE is seent to DRAM
                                                              11 -> reserved ( same as 0b10) */
        unsigned int  isp_fbcraw_sel3    : 1;  /* bit[7]    : VPM2TO1_41_(x)
                                                              0 -> Data from ISP_FE is sent to DRAM
                                                              1 -> Data from FBCRAW is sent to DRAM */
        unsigned int  isp_fbdraw_sel1    : 1;  /* bit[8]    : Allow selection of FBDRAW to be used either on the ISP_FE input or on the ISP_BE input VPM2TO1_46_(x)
                                                              0 -> Data from CVDR(R1.x) is sent to FBDRAW
                                                              1 -> Data from CVDR(R10.x) is sent to FBDRAW */
        unsigned int  isp_fbdraw_sel2    : 1;  /* bit[9]    : Allow selection of FBDRAW to be used either on the ISP_FE input or on the ISP_BE input VPM2TO1_45_(x)
                                                              0 -> Data from CVDR(R10.x) is sent ISP_FE
                                                              1 -> Data from FBDRAW is sent ISP_FE */
        unsigned int  isp_fbdraw_sel3    : 1;  /* bit[10]   : Allow selection of FBDRAW to be used either on the ISP_FE input or on the ISP_BE input VPM2TO1_44_(x)
                                                              0 -> Data from FBDRAW is sent ISP_BE
                                                              1 -> Data from CVDR(R1.x) is sent ISP_BE */
        unsigned int  reserved_1         : 5;  /* bit[11-15]: Reserved for extra explicit VPM control */
        unsigned int  reserved_2         : 1;  /* bit[16]   : reserved(previously pipe_disable) */
        unsigned int  isp_be_2_to_jpgenc : 1;  /* bit[17]   : Select connection between ISP_BE_2 and SCALER_1_2 to JPGENC 
                                                              0 -> JPGENC (port pipe1) is connected to SCALER_1_2.Default configuration
                                                              1 -> JPEGENC (port pipe 1) is connected to ISP_BE_2 */
        unsigned int  reserved_3         : 14; /* bit[18-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fe_bypass_START       (0)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fe_bypass_END         (0)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_be_scaler_1_START     (1)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_be_scaler_1_END       (1)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_be_scaler_2_START     (2)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_be_scaler_2_END       (2)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbcraw_sel1_START     (4)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbcraw_sel1_END       (4)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbcraw_sel2_START     (5)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbcraw_sel2_END       (6)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbcraw_sel3_START     (7)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbcraw_sel3_END       (7)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbdraw_sel1_START     (8)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbdraw_sel1_END       (8)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbdraw_sel2_START     (9)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbdraw_sel2_END       (9)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbdraw_sel3_START     (10)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_fbdraw_sel3_END       (10)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_be_2_to_jpgenc_START  (17)
#define SOC_ISP_ISPSS_CTRL_CONTROL_0_P2_isp_be_2_to_jpgenc_END    (17)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_UNION
 结构说明  : CVDR_RD_CTRL 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: CVDR Read Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r1_1_rt_srt    : 1;  /* bit[0]    : Configure the CVDR connected to the R1.1 (FBDRAW_1_1)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  r1_2_rt_srt    : 1;  /* bit[1]    : Configure the CVDR connected to the R1.2 (FBDRAW_1_2)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  r3_1_rt_srt    : 1;  /* bit[2]    : Configure the CVDR connected to the R3.1 (FBDYUV_1_1)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  r3_2_rt_srt    : 1;  /* bit[3]    : Configure the CVDR connected to the R3.2 (FBDYUV_1_2)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  r4_1_rt_srt    : 1;  /* bit[4]    : Configure the CVDR connected to the R4.1 (JPGENC Y)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  reserved_0     : 1;  /* bit[5]    : reserved */
        unsigned int  r11_1_1_rt_srt : 1;  /* bit[6]    : Configure the CVDR connected to the R11.1 (ITAP_1_1)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  r11_1_2_rt_srt : 1;  /* bit[7]    : Configure the CVDR connected to the R11.2 (ITAP_1_2)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  r11_2_1_rt_srt : 1;  /* bit[8]    : Configure the CVDR connected to the R12.1 (ITAP_2_1)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  r11_2_2_rt_srt : 1;  /* bit[9]    : Configure the CVDR connected to the R12.2 (ITAP_2_2)channel as:
                                                          1 -> Real Time initiator
                                                          0 -> Soft Real Time initiator */
        unsigned int  reserved_1     : 22; /* bit[10-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r1_1_rt_srt_START     (0)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r1_1_rt_srt_END       (0)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r1_2_rt_srt_START     (1)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r1_2_rt_srt_END       (1)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r3_1_rt_srt_START     (2)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r3_1_rt_srt_END       (2)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r3_2_rt_srt_START     (3)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r3_2_rt_srt_END       (3)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r4_1_rt_srt_START     (4)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r4_1_rt_srt_END       (4)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_1_1_rt_srt_START  (6)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_1_1_rt_srt_END    (6)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_1_2_rt_srt_START  (7)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_1_2_rt_srt_END    (7)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_2_1_rt_srt_START  (8)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_2_1_rt_srt_END    (8)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_2_2_rt_srt_START  (9)
#define SOC_ISP_ISPSS_CTRL_CVDR_RD_CTRL_r11_2_2_rt_srt_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_UNION
 结构说明  : CVDR_WR_CTRL 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: CVDR Write Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  w1_1_rt_srt   : 1;  /* bit[0]    : Configure the CVDR connected to the W1.1 (CROP_ISP_FE_1)channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w1_2_rt_srt   : 1;  /* bit[1]    : Configure the CVDR connected to the W1.2 (CROP_ISP_FE_2) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w2_1_rt_srt   : 1;  /* bit[2]    : Configure the CVDR connected to the W2.1 (CROP_ISP_FE_1 or ISP_FE_1/BAS_1)channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w2_2_rt_srt   : 1;  /* bit[3]    : Configure the CVDR connected to the W2.2 (CROP_ISP_FE_2 or ISP_FE_2/BAS_2) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  reserved_0    : 3;  /* bit[4-6]  : Reserved */
        unsigned int  w4_1_1_rt_srt : 1;  /* bit[7]    : Configure the CVDR connected to the W4.1.1 (SCALER_1_1 Y ) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w4_1_2_rt_srt : 1;  /* bit[8]    : Configure the CVDR connected to the W4.1.2 (SCALER_1_1 UV) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w4_2_1_rt_srt : 1;  /* bit[9]    : Configure the CVDR connected to the W4.2.1 (SCALER_1_2 Y) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w4_2_2_rt_srt : 1;  /* bit[10]   : Configure the CVDR connected to the W4.2.2 (SCALER_1_2 UV) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w5_1_1_rt_srt : 1;  /* bit[11]   : Configure the CVDR connected to the W5.1.1 (SCALER_2_1 Y) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w5_1_2_rt_srt : 1;  /* bit[12]   : Configure the CVDR connected to the W5.1.2 (SCALER_2_1 UV)channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w5_2_1_rt_srt : 1;  /* bit[13]   : Configure the CVDR connected to the W5.2.1 (SCALER_2_2 Y) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w5_2_2_rt_srt : 1;  /* bit[14]   : Configure the CVDR connected to the W5.2.2 (SCALER_2_2 UV) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w6_1_rt_srt   : 1;  /* bit[15]   : Configure the CVDR connected to the W6.1 (SCALER_3 Y) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w6_2_rt_srt   : 1;  /* bit[16]   : Configure the CVDR connected to the W6.2 (SCALER_3 UV) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w7_1_rt_srt   : 1;  /* bit[17]   : Configure the CVDR connected to the W7.1 (FBCYUV_1) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w7_2_rt_srt   : 1;  /* bit[18]   : Configure the CVDR connected to the W7.2 (FBCYUV_2) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w8_1_rt_srt   : 1;  /* bit[19]   : Configure the CVDR connected to the W8.1 (JPGENC) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  reserved_1    : 1;  /* bit[20]   : Reserved (Previously used to configure the CVDR connected to the W9.1 (WARP_1)channel a)s:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  reserved_2    : 1;  /* bit[21]   : Reserved (Previously used to configure the CVDR connected to the W9.2 (WARP_2) channel as):
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  reserved_3    : 1;  /* bit[22]   : Reserved */
        unsigned int  w11_1_rt_srt  : 1;  /* bit[23]   : Configure the CVDR connected to the W11.1 (3ASTAT_1) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w11_2_rt_srt  : 1;  /* bit[24]   : Configure the CVDR connected to the W11.2 (3ASTAT_2) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w12_1_rt_srt  : 1;  /* bit[25]   : Configure the CVDR connected to the W12.1 (OTAP_1_1) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w12_2_rt_srt  : 1;  /* bit[26]   : Configure the CVDR connected to the W12.2 (OTAP_1_2) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w13_1_rt_srt  : 1;  /* bit[27]   : Configure the CVDR connected to the W13.1 (OTAP_2_1) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  w13_2_rt_srt  : 1;  /* bit[28]   : Configure the CVDR connected to the W13.2 (OTAP_2_2) channel as:
                                                         1 -> Real Time initiator
                                                         0 -> Soft Real Time initiator */
        unsigned int  reserved_4    : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w1_1_rt_srt_START    (0)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w1_1_rt_srt_END      (0)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w1_2_rt_srt_START    (1)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w1_2_rt_srt_END      (1)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w2_1_rt_srt_START    (2)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w2_1_rt_srt_END      (2)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w2_2_rt_srt_START    (3)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w2_2_rt_srt_END      (3)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_1_1_rt_srt_START  (7)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_1_1_rt_srt_END    (7)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_1_2_rt_srt_START  (8)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_1_2_rt_srt_END    (8)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_2_1_rt_srt_START  (9)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_2_1_rt_srt_END    (9)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_2_2_rt_srt_START  (10)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w4_2_2_rt_srt_END    (10)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_1_1_rt_srt_START  (11)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_1_1_rt_srt_END    (11)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_1_2_rt_srt_START  (12)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_1_2_rt_srt_END    (12)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_2_1_rt_srt_START  (13)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_2_1_rt_srt_END    (13)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_2_2_rt_srt_START  (14)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w5_2_2_rt_srt_END    (14)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w6_1_rt_srt_START    (15)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w6_1_rt_srt_END      (15)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w6_2_rt_srt_START    (16)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w6_2_rt_srt_END      (16)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w7_1_rt_srt_START    (17)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w7_1_rt_srt_END      (17)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w7_2_rt_srt_START    (18)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w7_2_rt_srt_END      (18)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w8_1_rt_srt_START    (19)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w8_1_rt_srt_END      (19)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w11_1_rt_srt_START   (23)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w11_1_rt_srt_END     (23)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w11_2_rt_srt_START   (24)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w11_2_rt_srt_END     (24)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w12_1_rt_srt_START   (25)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w12_1_rt_srt_END     (25)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w12_2_rt_srt_START   (26)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w12_2_rt_srt_END     (26)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w13_1_rt_srt_START   (27)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w13_1_rt_srt_END     (27)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w13_2_rt_srt_START   (28)
#define SOC_ISP_ISPSS_CTRL_CVDR_WR_CTRL_w13_2_rt_srt_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_LST_LOW_UNION
 结构说明  : LST_LOW 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: Local Time Stamp low
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lst_low : 32; /* bit[0-31]: system counter range [31:0] */
    } reg;
} SOC_ISP_ISPSS_CTRL_LST_LOW_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_LST_LOW_lst_low_START  (0)
#define SOC_ISP_ISPSS_CTRL_LST_LOW_lst_low_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_LST_HIGH_UNION
 结构说明  : LST_HIGH 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: Local Time Stamp high
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lst_high : 32; /* bit[0-31]: system counter range [63:32] */
    } reg;
} SOC_ISP_ISPSS_CTRL_LST_HIGH_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_LST_HIGH_lst_high_START  (0)
#define SOC_ISP_ISPSS_CTRL_LST_HIGH_lst_high_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_UNION
 结构说明  : IOTAP_MAP_P1 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: Select ITAP and OTAP location
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pos_out_sel_1 : 4;  /* bit[0-3]  : This field defines to which Video Port the OTAP_1_(x) ( x = 1 for pipe 1) is connected to. When configured to zero no data is sent to the OTAP. Default value is zero. 
                                                          0 -> mux is selecting the Video port from the crop function defining the active frame in DCT but Video port traffic is gated 
                                                          1 -> from ISP_FE_(x) crop function defining the active frame
                                                          2 -> from LSC_(x) out 
                                                          3 -> from RAWNF_(x) out 
                                                          4 -> from CROP_2_(x) out (after VPB) 
                                                          5 -> from GCD_(x) out
                                                          6 -> from RGB2YUV_(x) out
                                                          7 -> from CE_(x) out
                                                          8 -> from SHARPEN_(x) out 
                                                          9 -> from SCALER_1_(x) out (Y for YUV420 after VPB1TO2YUV_2_x or YUV422)
                                                          10 -> reserved
                                                          11 -> from CROP_3 out (SCALER_2) (Y for YUV420 after VPB1TO2YUV_1_x or YUV422) 
                                                          12 -> reserved
                                                          13 ->from SCALER_3 out (Y for YUV420 after VPB1TO2YUV_1 or YUV422)
                                                          14-15 -> Reserved */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved */
        unsigned int  pos_in_sel_1  : 4;  /* bit[8-11] : This field defines to which Video Port the ITAP_1_(x) (x = 1 for pipe 1) is connected to. When value is zero ITAP_1_x is disabled.
                                                          0 -> ITAP is disabled; No ITAP is connected to the pipe. All VPM receiving ITAP are in normal path mode
                                                          1 -> control on VPM_1_x in front of BLC_(x) is set to 1 to select ITAP
                                                          2 -> control on VPM_2_x in front of DPCC_(x) is set to 1 to select ITAP
                                                          3 -> control on VPM_3_x in front of BAS_(x) is set to 1 to select ITAP
                                                          4 -> Reserved
                                                          5 -> control on VPM_5_x in front of AWBGAIN_(x) is set to 1 to select ITAP
                                                          6 -> control on VPM_6_x in front of CC_(x) prior to VPB is set to 1 to select ITAP
                                                          7 -> control on VPM_7_x in front of UVDEC_(x) is set to 1 to select ITAP
                                                          8 -> control on VPM_8_x in front of TNR_(x) is set to 1 to select ITAP
                                                          9 -> control on VPM_9_x in front of IE_(x) is set to 1 to select ITAP
                                                          10-15 -> reserved mapping 
                                                         If both IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_MAP_P1.POS_IN_SEL_2 equal zero, pipe is in standard configuration, no ITAP is connected to the pipe. 
                                                         If one or the other is different from zero at least one ITAP is connected. If IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_P1_MAP.POS_IN_SEL_2 are programmed to the same value ( different from zero) ITAP_1_(x) is connected but not ITAP_2_(x). */
        unsigned int  reserved_1    : 4;  /* bit[12-15]: Reserved */
        unsigned int  pos_out_sel_2 : 4;  /* bit[16-19]: This field defines to which Video Port the OTAP_2_(x) ( x = 1 for pipe 1) is connected to. When configured to zero no data is sent to the OTAP. Default value is zero. 
                                                          0 -> mux is selecting the Video port from the crop function defining the active frame in DCT but Video port traffic is gated 
                                                          1 -> from ISP_FE_(x) crop function defining the active frame
                                                          2 -> from LSC_(x) out 
                                                          3 -> from RAWNF_(x) out
                                                          4 -> from CROP_2_(x) out (after VPB)
                                                          5 -> from GCD_(x) out
                                                          6 -> from RGB2YUV_(x) out
                                                          7 -> from CE_(x) out
                                                          8 -> from SHARPEN_(x) out
                                                          9 -> from SCALER_1_(x) out (Y for YUV420 after VPB1TO2YUV_2_x or YUV422)
                                                          10 -> from SCALER_1_(x) out (UV for YUV420 after VPB1TO2YUV_2_x)
                                                          11 -> from CROP_3 out (SCALER_2) (Y for YUV420 after VPB1TO2YUV_1_x or YUV422) 
                                                          12 -> from CROP_3 (SCALER_2) (UV for YUV420 after VPB1TO2YUV_1_x)
                                                          13 -> reserved
                                                          14 -> from SCALER_3 out (UV for YUV420 after VPB1TO2YUV_1)
                                                          15 -> from Debug_infrastructure */
        unsigned int  reserved_2    : 4;  /* bit[20-23]: Reserved */
        unsigned int  pos_in_sel_2  : 4;  /* bit[24-27]: This field defines to which Video Port the ITAP_2_(x) (x = 1 for pipe 1) is connected to. When value is zero ITAP_2_x is disabled.
                                                          0 -> ITAP is disabled; No ITAP is connected to the pipe. All VPM receiving ITAP are in normal path mode
                                                          1 -> control on VPM_12_x in front of BLC_(x) is set to 1 to select ITAP
                                                          2 -> control on VPM_13_x in front of DPCC_(x) is set to 1 to select ITAP
                                                          3 -> control on VPM_14_x in front of BAS_(x) is set to 1 to select ITAP
                                                          4 -> Reserved 
                                                          5 -> control on VPM_16_x in front of AWBGAIN_(x) is set to 1 to select ITAP
                                                          6 -> control on VPM_17_x in front of CC_(x) prior to VPB is set to 1 to select ITAP 
                                                          7 -> control on VPM_18_x in front of UVDEC_(x) is set to 1 to select ITAP 
                                                          8 -> control on VPM_19_x in front of TNR_(x) is set to 1 to select ITAP
                                                          9 -> control on VPM_20_x in front of IE_(x) is set to 1 to select ITAP
                                                          10-15 -> reserved mapping 
                                                          If both IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_MAP_P1.POS_IN_SEL_2 equal zero, pipe is in standard configuration, no ITAP is connected to the pipe. if one or the other is different from zero at least one ITAP is connected. If IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_P1_MAP.POS_IN_SEL_2 are programmed to the same value ( different from zero) ITAP_1_(x) is connected but not ITAP_2_(x). */
        unsigned int  reserved_3    : 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_out_sel_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_out_sel_1_END    (3)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_in_sel_1_START   (8)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_in_sel_1_END     (11)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_out_sel_2_START  (16)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_out_sel_2_END    (19)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_in_sel_2_START   (24)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P1_pos_in_sel_2_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_UNION
 结构说明  : IOTAP_MAP_P2 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: Select ITAP and OTAP location
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pos_out_sel_1 : 4;  /* bit[0-3]  : This field defines to which Video Port the OTAP_1_(x) ( x = 2 for pipe 2) is connected to. When configured to zero no data is sent to the OTAP. Default value is zero. 
                                                          0 -> mux is selecting the Video port from the crop function defining the active frame in DCT but Video port traffic is gated 
                                                          1 -> from ISP_FE_(x) crop function defining the active frame 
                                                          2 -> from LSC_(x) out 
                                                          3 -> from RAWNF_(x) out
                                                          4 -> from CROP_2_(x) out after VPB
                                                          5 -> from GCD_(x) out
                                                          6 -> from RGB2YUV_(x) out
                                                          7 -> from CE_(x) out
                                                          8 -> from SHARPEN_(x) out 
                                                          9 -> from SCALER_1_(x) out (Y for YUV420 after VPB1TO2YUV_2_x or YUV422)
                                                          10 -> reserved
                                                          11 -> from CROP_3_(x) out (SCALER_2) (Y for YUV420 after VPB1TO2YUV_1_x or YUV422)
                                                          12-15 -> reserved */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved */
        unsigned int  pos_in_sel_1  : 4;  /* bit[8-11] : This field defines to which Video Port the ITAP_1_(x) (x = 2 for pipe 2) is connected to. When value is zero ITAP_1_x is disabled.
                                                          0 -> ITAP is disabled; No ITAP is connected to the pipe. All VPM receiving ITAP are in normal path mode
                                                          1 -> control on VPM_1_x in front of BLC_(x) is set to 1 to select ITAP
                                                          2 -> control on VPM_2_x in front of DPCC_(x) is set to 1 to select ITAP
                                                          3 -> control on VPM_3_x in front of BAS_(x) is set to 1 to select ITAP
                                                          4 -> Reserved
                                                          5 -> control on VPM_5_x in front of AWBGAIN_(x) is set to 1 to select ITAP
                                                          6 -> control on VPM_6_x in front of CC_(x) prior to VPB is set to 1 to select ITAP
                                                          7 -> control on VPM_7_x in front of UVDEC_(x) is set to 1 to select ITAP
                                                          8 -> control on VPM_8_x in front of TNR_(x) is set to 1 to select ITAP
                                                          9 -> control on VPM_9_x in front of IE_(x) is set to 1 to select ITAP
                                                          10-15 -> reserved mapping 
                                                         If both IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_MAP_P1.POS_IN_SEL_2 equal zero, pipe is in standard configuration, no ITAP is connected to the pipe. 
                                                         If one or the other is different from zero at least one ITAP is connected. If IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_P1_MAP.POS_IN_SEL_2 are programmed to the same value ( different from zero) ITAP_1_(x) is connected but not ITAP_2_(x). */
        unsigned int  reserved_1    : 4;  /* bit[12-15]: Reserved */
        unsigned int  pos_out_sel_2 : 4;  /* bit[16-19]: This field defines to which Video Port the OTAP_2_(x) ( x = 2 for pipe 2) is connected to. When configured to zero no data is sent to the OTAP. Default value is zero. 
                                                          0 -> mux is selecting the Video port from the crop function defining the active frame in DCT but Video port traffic is gated 
                                                          1 -> from ISP_FE_(x) crop function defining the active frame
                                                          2 -> from LSC_(x) out 
                                                          3 -> from RAWNF_(x) out
                                                          4 -> from CROP_2_(x) out (after VPB)
                                                          5 -> from GCD_(x) out
                                                          6 -> from RGB2YUV_(x) out
                                                          7 -> from CE_(x) out
                                                          8 -> from SHARPEN_(x) out
                                                          9 -> from SCALER_1_(x) out (Y for YUV420 after VPB1TO2YUV_2_x or YUV422) 
                                                          10 -> from SCALER_1_(x) out (UV for YUV420 after VPB1TO2YUV_2_x)
                                                          11 -> from CROP_3 out (SCALER_2) (Y for YUV420 after VPB1TO2YUV_1_x or YUV422)
                                                          12 -> from CROP_3 (SCALER_2) (UV for YUV420 after VPB1TO2YUV_1_x)
                                                          13-14 -> reserved 
                                                          15 -> from Debug_infrastructure */
        unsigned int  reserved_2    : 4;  /* bit[20-23]: Reserved */
        unsigned int  pos_in_sel_2  : 4;  /* bit[24-27]: This field defines to which Video Port the ITAP_2_(x) (x = 2 for pipe 2) is connected to. When value is zero ITAP_2_x is disabled.
                                                          0 -> ITAP is disabled; No ITAP is connected to the pipe. All VPM receiving ITAP are in normal path mode
                                                          1 -> control on VPM_12_x in front of BLC_(x) is set to 1 to select ITAP
                                                          2 -> control on VPM_13_x in front of DPCC_(x) is set to 1 to select ITAP
                                                          3 -> control on VPM_14_x in front of BAS_(x) prior to VPB is set to 1 to select ITAP
                                                          4 -> Reserved
                                                          5 -> control on VPM_16_x in front of AWBGAIN_(x) is set to 1 to select ITAP
                                                          6 -> control on VPM_17_x in front of CC_(x) is set to 1 to select ITAP
                                                          7 -> control on VPM_18_x in front of UVDEC_(x) is set to 1 to select ITAP
                                                          8 -> control on VPM_19_x in front of TNR_(x) is set to 1 to select ITAP
                                                          9 -> control on VPM_20_x in front of IE_(x) is set to 1 to select ITAP
                                                          10-15 -> reserved mapping 
                                                          If both IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_MAP_P1.POS_IN_SEL_2 equal zero, pipe is in standard configuration, no ITAP is connected to the pipe. if one or the other is different from zero at least one ITAP is connected. If IOTAP_MAP_P1.POS_IN_SEL_1 and IOTAP_P1_MAP.POS_IN_SEL_2 are programmed to the same value ( different from zero) ITAP_1_(x) is connected but not ITAP_2_(x). */
        unsigned int  reserved_3    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_out_sel_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_out_sel_1_END    (3)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_in_sel_1_START   (8)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_in_sel_1_END     (11)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_out_sel_2_START  (16)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_out_sel_2_END    (19)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_in_sel_2_START   (24)
#define SOC_ISP_ISPSS_CTRL_IOTAP_MAP_P2_pos_in_sel_2_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_UNION
 结构说明  : CROP_H_3_P1 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft   : 13; /* bit[0-12] : Indicate position of first pixel on the left for the cropped window, 0 means no left crop.  */
        unsigned int  reserved_0: 3;  /* bit[13-15]: reserved */
        unsigned int  ihright  : 13; /* bit[16-28]: Indicate position of last pixel on the right for the cropped window.  */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_ihleft_START    (0)
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_ihleft_END      (12)
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_ihright_START   (16)
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P1_ihright_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_UNION
 结构说明  : CROP_V_3_P1 寄存器结构定义。地址偏移量:0x0144，初值:0x00000000，宽度:32
 寄存器说明: Crop vertical offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivtop    : 13; /* bit[0-12] : indicates position of first line on the top for the cropped window,, 0 means no top crop */
        unsigned int  reserved_0: 3;  /* bit[13-15]: Reserved */
        unsigned int  ivbottom : 13; /* bit[16-28]: indicates position of last line on the bottom for the cropped window */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_ivtop_START     (0)
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_ivtop_END       (12)
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_ivbottom_START  (16)
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P1_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_UNION
 结构说明  : CROP_H_3_P2 寄存器结构定义。地址偏移量:0x0148，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft   : 13; /* bit[0-12] : Indicate position of first pixel on the left for the cropped window, 0 means no left crop.  */
        unsigned int  reserved_0: 3;  /* bit[13-15]: reserved */
        unsigned int  ihright  : 13; /* bit[16-28]: Indicate position of last pixel on the right for the cropped window.  */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_ihleft_START    (0)
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_ihleft_END      (12)
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_ihright_START   (16)
#define SOC_ISP_ISPSS_CTRL_CROP_H_3_P2_ihright_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_UNION
 结构说明  : CROP_V_3_P2 寄存器结构定义。地址偏移量:0x014C，初值:0x00000000，宽度:32
 寄存器说明: Crop  vertical offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivtop    : 13; /* bit[0-12] : indicates position of first line on the top for the cropped window,, 0 means no top crop */
        unsigned int  reserved_0: 3;  /* bit[13-15]: Reserved */
        unsigned int  ivbottom : 13; /* bit[16-28]: indicates position of last line on the bottom for the cropped window */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_ivtop_START     (0)
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_ivtop_END       (12)
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_ivbottom_START  (16)
#define SOC_ISP_ISPSS_CTRL_CROP_V_3_P2_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_GPO_UNION
 结构说明  : GPO 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: Generic Output
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpo0     : 1;  /* bit[0]    : Reset image sensor ( front side) */
        unsigned int  gpo1     : 1;  /* bit[1]    : Reset image sensor ( back side). Only one reset for 1 or 2 Cameras ( 3D) */
        unsigned int  gpo2     : 1;  /* bit[2]    : generic gpio/Used for Flash strobe. ( only for the main back camera)  */
        unsigned int  gpo3     : 1;  /* bit[3]    : generic gpio/Used for prelight strobe Xenon flash not confirmed yet */
        unsigned int  gpo4     : 1;  /* bit[4]    : generic gpio/PWM */
        unsigned int  gpo5     : 1;  /* bit[5]    : generic gpio/PWM */
        unsigned int  gpo6     : 1;  /* bit[6]    : Strobe uinput from camera ( not used as output) */
        unsigned int  gpo7     : 1;  /* bit[7]    : signal to enable/ power sensor A */
        unsigned int  gpo8     : 1;  /* bit[8]    : signal to enable/ power sensor B */
        unsigned int  gpo9     : 1;  /* bit[9]    : signal to enable/ power sensor C */
        unsigned int  gpo10    : 1;  /* bit[10]   : generic gpio/fsync (for 3D cameras) */
        unsigned int  gpo11    : 1;  /* bit[11]   : generic gpio/PWM */
        unsigned int  gpo12    : 1;  /* bit[12]   : generic gpio/PWM */
        unsigned int  reserved : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_GPO_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_GPO_gpo0_START      (0)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo0_END        (0)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo1_START      (1)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo1_END        (1)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo2_START      (2)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo2_END        (2)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo3_START      (3)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo3_END        (3)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo4_START      (4)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo4_END        (4)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo5_START      (5)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo5_END        (5)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo6_START      (6)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo6_END        (6)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo7_START      (7)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo7_END        (7)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo8_START      (8)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo8_END        (8)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo9_START      (9)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo9_END        (9)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo10_START     (10)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo10_END       (10)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo11_START     (11)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo11_END       (11)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo12_START     (12)
#define SOC_ISP_ISPSS_CTRL_GPO_gpo12_END       (12)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_UNION
 结构说明  : GPO_CTRL_1 寄存器结构定义。地址偏移量:0x0164，初值:0x00000000，宽度:32
 寄存器说明: Generic Output CTRL
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpo2_sel  : 2;  /* bit[0-1]  : GPO2 selection source
                                                     00: GPO
                                                     01: PWM
                                                     10: Flash strobe. ( only for the main back camera)
                                                     11: reserved */
        unsigned int  gpo3_sel  : 2;  /* bit[2-3]  : GPO3 selection source
                                                     00: GPO
                                                     01: PWM
                                                     10: Prelight strobe
                                                     11: reserved */
        unsigned int  gpo4_sel  : 2;  /* bit[4-5]  : GPO4 selection source
                                                     00: GPO
                                                     01: other sources ( PWM or programmable pattern)
                                                     1x: reserved */
        unsigned int  gpo5_sel  : 2;  /* bit[6-7]  : GPO5 selection source
                                                     00: GPO
                                                     01: other sources ( PWM or programmable pattern)
                                                     1x: reserved */
        unsigned int  reserved_0: 2;  /* bit[8-9]  : Reserved */
        unsigned int  gpo10_sel : 2;  /* bit[10-11]: GPO selection source// update by tanhuang to comply with the austin GPIO
                                                     00: GPO10 (may be used for synchronizing camera (ex: 3D) to drive fsync input camera sensor)
                                                     01: PWM
                                                     1x :Reserved */
        unsigned int  gpo11_sel : 2;  /* bit[12-13]: GPO11 selection source
                                                     00: GPO11
                                                     01: PWM
                                                     1x: reserved */
        unsigned int  gpo12_sel : 2;  /* bit[14-15]: GPO12 selection source
                                                     00: GPO12
                                                     01: PWM
                                                     1x: reserved */
        unsigned int  reserved_1: 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo2_sel_START   (0)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo2_sel_END     (1)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo3_sel_START   (2)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo3_sel_END     (3)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo4_sel_START   (4)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo4_sel_END     (5)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo5_sel_START   (6)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo5_sel_END     (7)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo10_sel_START  (10)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo10_sel_END    (11)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo11_sel_START  (12)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo11_sel_END    (13)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo12_sel_START  (14)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_1_gpo12_sel_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_UNION
 结构说明  : GPO_CTRL_2 寄存器结构定义。地址偏移量:0x0168，初值:0x00000000，宽度:32
 寄存器说明: Generic Output CTRL
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode_repeat : 7;  /* bit[0-6]  : Mode repeat
                                                       bit field 6: PWM on GPO12
                                                       bit field 5: PWM on GPO11
                                                       bit field 4: PWM on GPO6
                                                       bit field 3: PWM on GPO5
                                                       bit field 2: PWM on GPO4
                                                       bit field 1: PWM on GPO3
                                                       bit field 0: PWM on GPO2
                                                       0: Single shot pattern on GPO configured in PWM
                                                       1: repeat pattern on GPO configured in PWM */
        unsigned int  reserved_0  : 1;  /* bit[7]    : reserved */
        unsigned int  pwm_mode    : 7;  /* bit[8-14] : PMW configuration per GPO supporting PWM 
                                                       bit field 14: PWM on GPO12
                                                       bit field 13: PWM on GPO11
                                                       bit field 12: PWM on GPO6
                                                       bit field 11: PWM on GPO5
                                                       bit field 10: PWM on GPO4
                                                       bit field 9: PWM on GPO3
                                                       bit field 8: PWM on GPO2
                                                       0: Mode 1 -> programmable / repeatable pattern
                                                       1: Mode 2 -> dual counter for standard PWM */
        unsigned int  reserved_1  : 1;  /* bit[15]   : reserved */
        unsigned int  start       : 7;  /* bit[16-22]: Start for GPO configured in PWM
                                                       bit field 22: PWM on GPO12
                                                       bit field 21: PWM on GPO11
                                                       bit field 20: PWM on GPO6
                                                       bit field 19: PWM on GPO5
                                                       bit field 18: PWM on GPO4
                                                       bit field 17: PWM on GPO3
                                                       bit field 16: PWM on GPO2 */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_mode_repeat_START  (0)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_mode_repeat_END    (6)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_pwm_mode_START     (8)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_pwm_mode_END       (14)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_start_START        (16)
#define SOC_ISP_ISPSS_CTRL_GPO_CTRL_2_start_END          (22)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_1_UNION
 结构说明  : PATTERN_CTRL_1_1 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: first half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo5_seq_pat_1 : 32; /* bit[0-31]: Define sequence pattern seq[31:0] for GPO5 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_1_pwm_gpo5_seq_pat_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_1_pwm_gpo5_seq_pat_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_2_UNION
 结构说明  : PATTERN_CTRL_1_2 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: second half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo5_seq_pat_2 : 32; /* bit[0-31]: Define sequence pattern seq[63:32] for GPO5 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_2_pwm_gpo5_seq_pat_2_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_1_2_pwm_gpo5_seq_pat_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_1_UNION
 结构说明  : PATTERN_CTRL_2_1 寄存器结构定义。地址偏移量:0x0178，初值:0x00000000，宽度:32
 寄存器说明: first half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo4_seq_pat_1 : 32; /* bit[0-31]: Define sequence pattern seq[31:0] for GPO4 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_1_pwm_gpo4_seq_pat_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_1_pwm_gpo4_seq_pat_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_2_UNION
 结构说明  : PATTERN_CTRL_2_2 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: second half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo4_seq_pat_2 : 32; /* bit[0-31]: Define sequence pattern seq[63:32] for GPO4 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_2_pwm_gpo4_seq_pat_2_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_2_2_pwm_gpo4_seq_pat_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_1_UNION
 结构说明  : PATTERN_CTRL_3_1 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: first half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo2_seq_pat_1 : 32; /* bit[0-31]: Define sequence pattern seq[31:0] for GPO2 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_1_pwm_gpo2_seq_pat_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_1_pwm_gpo2_seq_pat_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_2_UNION
 结构说明  : PATTERN_CTRL_3_2 寄存器结构定义。地址偏移量:0x0184，初值:0x00000000，宽度:32
 寄存器说明: second half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo2_seq_pat_2 : 32; /* bit[0-31]: Define sequence pattern seq[63:32] for GPO2 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_2_pwm_gpo2_seq_pat_2_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_3_2_pwm_gpo2_seq_pat_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_1_UNION
 结构说明  : PATTERN_CTRL_4_1 寄存器结构定义。地址偏移量:0x0188，初值:0x00000000，宽度:32
 寄存器说明: first half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo3_seq_pat_1 : 32; /* bit[0-31]: Define sequence pattern seq[31:0] for GPO3 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_1_pwm_gpo3_seq_pat_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_1_pwm_gpo3_seq_pat_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_2_UNION
 结构说明  : PATTERN_CTRL_4_2 寄存器结构定义。地址偏移量:0x018C，初值:0x00000000，宽度:32
 寄存器说明: second half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo3_seq_pat_2 : 32; /* bit[0-31]: Define sequence pattern seq[63:32] for GPO3 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_2_pwm_gpo3_seq_pat_2_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_4_2_pwm_gpo3_seq_pat_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_1_UNION
 结构说明  : PATTERN_CTRL_5_1 寄存器结构定义。地址偏移量:0x0190，初值:0x00000000，宽度:32
 寄存器说明: first half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo6_seq_pat_1 : 32; /* bit[0-31]: Define sequence pattern seq[31:0] for GPO6 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_1_pwm_gpo6_seq_pat_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_1_pwm_gpo6_seq_pat_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_2_UNION
 结构说明  : PATTERN_CTRL_5_2 寄存器结构定义。地址偏移量:0x0194，初值:0x00000000，宽度:32
 寄存器说明: second half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo6_seq_pat_2 : 32; /* bit[0-31]: Define sequence pattern seq[63:32] for GPO6 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_2_pwm_gpo6_seq_pat_2_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_5_2_pwm_gpo6_seq_pat_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_1_UNION
 结构说明  : PATTERN_CTRL_6_1 寄存器结构定义。地址偏移量:0x0198，初值:0x00000000，宽度:32
 寄存器说明: first half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo11_seq_pat_1 : 32; /* bit[0-31]: Define sequence pattern seq[31:0] for GPO11 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_1_pwm_gpo11_seq_pat_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_1_pwm_gpo11_seq_pat_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_2_UNION
 结构说明  : PATTERN_CTRL_6_2 寄存器结构定义。地址偏移量:0x019C，初值:0x00000000，宽度:32
 寄存器说明: second half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo11_seq_pat_2 : 32; /* bit[0-31]: Define sequence pattern seq[63:32] for GPO11 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_2_pwm_gpo11_seq_pat_2_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_6_2_pwm_gpo11_seq_pat_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_1_UNION
 结构说明  : PATTERN_CTRL_7_1 寄存器结构定义。地址偏移量:0x01A0，初值:0x00000000，宽度:32
 寄存器说明: first half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo12_seq_pat_1 : 32; /* bit[0-31]: Define sequence pattern seq[31:0] for GPO12 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_1_pwm_gpo12_seq_pat_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_1_pwm_gpo12_seq_pat_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_2_UNION
 结构说明  : PATTERN_CTRL_7_2 寄存器结构定义。地址偏移量:0x01A4，初值:0x00000000，宽度:32
 寄存器说明: second half of programmable pattern for GPO configuration in PWM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_gpo12_seq_pat_2 : 32; /* bit[0-31]: Define sequence pattern seq[63:32] for GPO12 */
    } reg;
} SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_2_pwm_gpo12_seq_pat_2_START  (0)
#define SOC_ISP_ISPSS_CTRL_PATTERN_CTRL_7_2_pwm_gpo12_seq_pat_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PRE_DIV_UNION
 结构说明  : PRE_DIV 寄存器结构定义。地址偏移量:0x01B0，初值:0x00000000，宽度:32
 寄存器说明: clock divider
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prediv   : 27; /* bit[0-26] : Divid functional clock frquency to control Sequence in Mode 1. Zero means no division, 1 divide by 2,by 3,… */
        unsigned int  reserved : 5;  /* bit[27-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_PRE_DIV_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PRE_DIV_prediv_START    (0)
#define SOC_ISP_ISPSS_CTRL_PRE_DIV_prediv_END      (26)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_UNION
 结构说明  : CROP_H_4_P1 寄存器结构定义。地址偏移量:0x01B4，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft   : 13; /* bit[0-12] : Indicate position of first pixel on the left for the cropped window, 0 means no left crop.  */
        unsigned int  reserved_0: 3;  /* bit[13-15]: reserved */
        unsigned int  ihright  : 13; /* bit[16-28]: Indicate position of last pixel on the right for the cropped window.  */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_ihleft_START    (0)
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_ihleft_END      (12)
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_ihright_START   (16)
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P1_ihright_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_UNION
 结构说明  : CROP_V_4_P1 寄存器结构定义。地址偏移量:0x01B8，初值:0x00000000，宽度:32
 寄存器说明: Crop vertical offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivtop    : 13; /* bit[0-12] : indicates position of first line on the top for the cropped window,, 0 means no top crop */
        unsigned int  reserved_0: 3;  /* bit[13-15]: Reserved */
        unsigned int  ivbottom : 13; /* bit[16-28]: indicates position of last line on the bottom for the cropped window */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_ivtop_START     (0)
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_ivtop_END       (12)
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_ivbottom_START  (16)
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P1_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_UNION
 结构说明  : CROP_H_4_P2 寄存器结构定义。地址偏移量:0x01BC，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft   : 13; /* bit[0-12] : Indicate position of first pixel on the left for the cropped window, 0 means no left crop.  */
        unsigned int  reserved_0: 3;  /* bit[13-15]: reserved */
        unsigned int  ihright  : 13; /* bit[16-28]: Indicate position of last pixel on the right for the cropped window.  */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_ihleft_START    (0)
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_ihleft_END      (12)
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_ihright_START   (16)
#define SOC_ISP_ISPSS_CTRL_CROP_H_4_P2_ihright_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_UNION
 结构说明  : CROP_V_4_P2 寄存器结构定义。地址偏移量:0x01C0，初值:0x00000000，宽度:32
 寄存器说明: Crop vertical offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivtop    : 13; /* bit[0-12] : indicates position of first line on the top for the cropped window,, 0 means no top crop */
        unsigned int  reserved_0: 3;  /* bit[13-15]: Reserved */
        unsigned int  ivbottom : 13; /* bit[16-28]: indicates position of last line on the bottom for the cropped window */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_ivtop_START     (0)
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_ivtop_END       (12)
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_ivbottom_START  (16)
#define SOC_ISP_ISPSS_CTRL_CROP_V_4_P2_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_UNION
 结构说明  : VPBG_CTRL_1 寄存器结构定义。地址偏移量:0x01D0，初值:0xFFFFFF3F，宽度:32
 寄存器说明: VPBG control registers (second number:_1 and _2 are used to distinguish pipe 1 and pipe)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctrl_vpbg_2_1  : 2;  /* bit[0-1]  : out1:framemerge_in1; out2: vpm42_1_in2 */
        unsigned int  ctrl_vpbg_2_2  : 2;  /* bit[2-3]  : out1:framemerge_in2; out2: vpm42_2_in2 */
        unsigned int  ctrl_vpbg_6_1  : 2;  /* bit[4-5]  : out1: BE1; out2: VPB8_1 */
        unsigned int  reserved       : 2;  /* bit[6-7]  :  */
        unsigned int  ctrl_vpbg_8_1  : 2;  /* bit[8-9]  : out1: Scaler_1_1; out2:Scaler_2_1 */
        unsigned int  ctrl_vpbg_8_2  : 2;  /* bit[10-11]: out1: Scaler_1_2; out2:Scaler_2_2 */
        unsigned int  ctrl_vpbg_30_1 : 2;  /* bit[12-13]: out1: vpm45_1_in2; out2:vpm44_1_in1 */
        unsigned int  ctrl_vpbg_30_2 : 2;  /* bit[14-15]: out1: vpm45_2_in2; out2:vpm44_2_in1 */
        unsigned int  ctrl_vpbg_31_1 : 2;  /* bit[16-17]: out1:vpm46_1_in1;out2:vpm44_1_in2 */
        unsigned int  ctrl_vpbg_31_2 : 2;  /* bit[18-19]: out1:vpm46_2_in1;out2:vpm44_2_in2 */
        unsigned int  ctrl_vpbg_32_1 : 2;  /* bit[20-21]: out1:vpm45_1_in1;out2:vpm46_1_in2 */
        unsigned int  ctrl_vpbg_32_2 : 2;  /* bit[22-23]: out1:vpm45_2_in1;out2:vpm46_2_in2 */
        unsigned int  ctrl_vpbg_33_1 : 2;  /* bit[24-25]: out1: vpm42_1_in1; out2:vpm40_1_in1 */
        unsigned int  ctrl_vpbg_33_2 : 2;  /* bit[26-27]: out1: vpm42_2_in1; out2:vpm40_2_in1 */
        unsigned int  ctrl_vpbg_34_1 : 2;  /* bit[28-29]: out1: vpm42_1_in2; out2:vpm41_1_in2 */
        unsigned int  ctrl_vpbg_34_2 : 2;  /* bit[30-31]: Enables to shutdown the output ports when unused - each bit controls the corresponding output port.
                                                          0: output port disabled
                                                          1: output port enabled
                                                          out1: vpm42_2_in2; out2:vpm41_2_in2 */
    } reg;
} SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_2_1_START   (0)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_2_1_END     (1)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_2_2_START   (2)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_2_2_END     (3)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_6_1_START   (4)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_6_1_END     (5)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_8_1_START   (8)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_8_1_END     (9)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_8_2_START   (10)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_8_2_END     (11)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_30_1_START  (12)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_30_1_END    (13)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_30_2_START  (14)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_30_2_END    (15)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_31_1_START  (16)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_31_1_END    (17)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_31_2_START  (18)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_31_2_END    (19)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_32_1_START  (20)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_32_1_END    (21)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_32_2_START  (22)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_32_2_END    (23)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_33_1_START  (24)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_33_1_END    (25)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_33_2_START  (26)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_33_2_END    (27)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_34_1_START  (28)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_34_1_END    (29)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_34_2_START  (30)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_1_ctrl_vpbg_34_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_UNION
 结构说明  : VPBG_CTRL_2 寄存器结构定义。地址偏移量:0x01D4，初值:0xFFFF0F33，宽度:32
 寄存器说明: VPBG control registers (second number:_1 and _2 are used to distinguish pipe 1 and pipe)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctrl_vpbg_35_1 : 2;  /* bit[0-1]  : out1: cvdr;out2:vpm50_1_in1 */
        unsigned int  reserved_0     : 2;  /* bit[2-3]  :  */
        unsigned int  ctrl_vpbg_35_2 : 2;  /* bit[4-5]  : out1: cvdr;out2:vpm50_2_in1 */
        unsigned int  reserved_1     : 2;  /* bit[6-7]  :  */
        unsigned int  ctrl_vpbg_36_1 : 2;  /* bit[8-9]  : unused */
        unsigned int  ctrl_vpbg_36_2 : 2;  /* bit[10-11]: unused */
        unsigned int  reserved_2     : 4;  /* bit[12-15]:  */
        unsigned int  ctrl_vpbg_41_1 : 2;  /* bit[16-17]: out1:vpm50_1_in2;out2:vpm51_1_in2 */
        unsigned int  ctrl_vpbg_41_2 : 2;  /* bit[18-19]: out1:vpm50_1_in2;out2:cvdr */
        unsigned int  ctrl_vpbg_43_1 : 2;  /* bit[20-21]: out1: FE1; out2:VPM32_1_in2 */
        unsigned int  ctrl_vpbg_43_2 : 2;  /* bit[22-23]: out1: FE2; out2:VPM32_2_in2 */
        unsigned int  ctrl_vpbg_7_1  : 2;  /* bit[24-25]: out1: VPM40_1_in2;out2:VPM41_1_in1 */
        unsigned int  ctrl_vpbg_7_2  : 2;  /* bit[26-27]: out1: VPM40_2_in2;out2:VPM41_2_in1 */
        unsigned int  ctrl_vpbg_9_1  : 2;  /* bit[28-29]: out1:prescaler; out2:crop3_1 */
        unsigned int  ctrl_vpbg_9_2  : 2;  /* bit[30-31]: Enables to shutdown the output ports when unused - each bit controls the corresponding output port.
                                                          0: output port disabled
                                                          1: output port enabled
                                                          out1:cvdr; out2:crop3_2 */
    } reg;
} SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_35_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_35_1_END    (1)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_35_2_START  (4)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_35_2_END    (5)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_36_1_START  (8)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_36_1_END    (9)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_36_2_START  (10)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_36_2_END    (11)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_41_1_START  (16)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_41_1_END    (17)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_41_2_START  (18)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_41_2_END    (19)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_43_1_START  (20)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_43_1_END    (21)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_43_2_START  (22)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_43_2_END    (23)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_7_1_START   (24)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_7_1_END     (25)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_7_2_START   (26)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_7_2_END     (27)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_9_1_START   (28)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_9_1_END     (29)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_9_2_START   (30)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_2_ctrl_vpbg_9_2_END     (31)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_UNION
 结构说明  : VPBG_CTRL_3 寄存器结构定义。地址偏移量:0x01D8，初值:0x0000071F，宽度:32
 寄存器说明: VPBG control registers (second number:_1 and _2 are used to distinguish pipe 1 and pipe)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctrl_vpbg_37_1 : 5;  /* bit[0-4]  : Field 0: enable output to scaler 1_1
                                                          Field 1: enable output to scaler 2_1
                                                          Field 2: enable output to crop_4_1 DRAM / JPGENC output
                                                          Field 3: enable output to scaler 1_2
                                                          Field 4: enable output to scaler 2_2 */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  :  */
        unsigned int  ctrl_vpbg_37_2 : 3;  /* bit[8-10] : Field 0: enable output to scaler 1_2
                                                          Field 1: enable output to scaler 2_2
                                                          Field 2: enable output to crop_4_1 DRAM / JPGENC output */
        unsigned int  reserved_1     : 21; /* bit[11-31]: Enables to shutdown the output ports when unused - each bit controls the corresponding output port.
                                                          0: output port disabled
                                                          1: output port enabled */
    } reg;
} SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_ctrl_vpbg_37_1_START  (0)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_ctrl_vpbg_37_1_END    (4)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_ctrl_vpbg_37_2_START  (8)
#define SOC_ISP_ISPSS_CTRL_VPBG_CTRL_3_ctrl_vpbg_37_2_END    (10)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_UNION
 结构说明  : PHY_CSI_A_dbg 寄存器结构定义。地址偏移量:0x01E0，初值:0x00000000，宽度:32
 寄存器说明: debug status for PHY CSI-A
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rxactivehs_0     : 1;  /* bit[0]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 0. */
        unsigned int  rxactivehs_1     : 1;  /* bit[1]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 1. */
        unsigned int  rxactivehs_2     : 1;  /* bit[2]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 2. */
        unsigned int  rxactivehs_3     : 1;  /* bit[3]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 3. */
        unsigned int  rxlpdtesc_0      : 1;  /* bit[4]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_1      : 1;  /* bit[5]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_2      : 1;  /* bit[6]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_3      : 1;  /* bit[7]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  ulpsactivenot_0  : 1;  /* bit[8]    : ctive Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_1  : 1;  /* bit[9]    : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_2  : 1;  /* bit[10]   : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_3  : 1;  /* bit[11]   : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  errsyncesc_0     : 1;  /* bit[12]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_1     : 1;  /* bit[13]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_2     : 1;  /* bit[14]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_3     : 1;  /* bit[15]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  ulpsactivenotclk : 1;  /* bit[16]   : Active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSCLK. TXCLKESC must be supplied to the macro until ULPSACTIVENOTCLK is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted together with RXCLKULPSNOT; at the end of the ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSCLKNOT signal is deasserted. */
        unsigned int  reserved         : 15; /* bit[17-31]:  */
    } reg;
} SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_0_START      (0)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_0_END        (0)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_1_START      (1)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_1_END        (1)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_2_START      (2)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_2_END        (2)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_3_START      (3)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxactivehs_3_END        (3)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_0_START       (4)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_0_END         (4)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_1_START       (5)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_1_END         (5)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_2_START       (6)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_2_END         (6)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_3_START       (7)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_rxlpdtesc_3_END         (7)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_0_START   (8)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_0_END     (8)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_1_START   (9)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_1_END     (9)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_2_START   (10)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_2_END     (10)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_3_START   (11)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenot_3_END     (11)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_0_START      (12)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_0_END        (12)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_1_START      (13)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_1_END        (13)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_2_START      (14)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_2_END        (14)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_3_START      (15)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_errsyncesc_3_END        (15)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenotclk_START  (16)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_A_dbg_ulpsactivenotclk_END    (16)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_UNION
 结构说明  : PHY_CSI_B_dbg 寄存器结构定义。地址偏移量:0x01E4，初值:0x00000000，宽度:32
 寄存器说明: debug status for PHY CSI-A
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rxactivehs_0     : 1;  /* bit[0]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 0. */
        unsigned int  rxactivehs_1     : 1;  /* bit[1]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 1. */
        unsigned int  rxactivehs_2     : 1;  /* bit[2]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 2. */
        unsigned int  rxactivehs_3     : 1;  /* bit[3]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 3. */
        unsigned int  rxlpdtesc_0      : 1;  /* bit[4]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_1      : 1;  /* bit[5]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_2      : 1;  /* bit[6]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_3      : 1;  /* bit[7]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  ulpsactivenot_0  : 1;  /* bit[8]    : ctive Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_1  : 1;  /* bit[9]    : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_2  : 1;  /* bit[10]   : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_3  : 1;  /* bit[11]   : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  errsyncesc_0     : 1;  /* bit[12]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_1     : 1;  /* bit[13]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_2     : 1;  /* bit[14]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_3     : 1;  /* bit[15]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  ulpsactivenotclk : 1;  /* bit[16]   : Active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSCLK. TXCLKESC must be supplied to the macro until ULPSACTIVENOTCLK is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted together with RXCLKULPSNOT; at the end of the ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSCLKNOT signal is deasserted. */
        unsigned int  reserved         : 15; /* bit[17-31]:  */
    } reg;
} SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_0_START      (0)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_0_END        (0)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_1_START      (1)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_1_END        (1)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_2_START      (2)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_2_END        (2)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_3_START      (3)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxactivehs_3_END        (3)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_0_START       (4)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_0_END         (4)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_1_START       (5)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_1_END         (5)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_2_START       (6)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_2_END         (6)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_3_START       (7)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_rxlpdtesc_3_END         (7)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_0_START   (8)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_0_END     (8)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_1_START   (9)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_1_END     (9)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_2_START   (10)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_2_END     (10)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_3_START   (11)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenot_3_END     (11)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_0_START      (12)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_0_END        (12)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_1_START      (13)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_1_END        (13)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_2_START      (14)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_2_END        (14)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_3_START      (15)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_errsyncesc_3_END        (15)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenotclk_START  (16)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_B_dbg_ulpsactivenotclk_END    (16)


/*****************************************************************************
 结构名    : SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_UNION
 结构说明  : PHY_CSI_C_dbg 寄存器结构定义。地址偏移量:0x01E8，初值:0x00000000，宽度:32
 寄存器说明: debug status for PHY CSI-A
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rxactivehs_0     : 1;  /* bit[0]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 0. */
        unsigned int  rxactivehs_1     : 1;  /* bit[1]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 1. */
        unsigned int  rxactivehs_2     : 1;  /* bit[2]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 2. */
        unsigned int  rxactivehs_3     : 1;  /* bit[3]    : High speed interface.High-speed reception active. This signal indicates that the lane module is actively receiving a high-speed data transmission from lane interconnect 3. */
        unsigned int  rxlpdtesc_0      : 1;  /* bit[4]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_1      : 1;  /* bit[5]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_2      : 1;  /* bit[6]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  rxlpdtesc_3      : 1;  /* bit[7]    : Escape Low Power Data Receive Mode. This signal is asserted to indicate that the lane module is now in Low Power Data Receive Mode. While in this mode, received data is driven onto RXDATAESC output bus when RXVALIDESC is active. RXLPDTESC remains asserted until a STOP state is detected on the lane interconnect. */
        unsigned int  ulpsactivenot_0  : 1;  /* bit[8]    : ctive Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_1  : 1;  /* bit[9]    : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_2  : 1;  /* bit[10]   : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  ulpsactivenot_3  : 1;  /* bit[11]   : active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSESC and TXREQUESTESC (or TXULPSCLK) are asserted. TXCLKESC must be supplied to the macro until ULPSACTIVENOT is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXREQUESTESC or TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted; at the end of the
                                                            ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSESC (or
                                                            RXULPSCLKNOT) signal is deasserted. */
        unsigned int  errsyncesc_0     : 1;  /* bit[12]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_1     : 1;  /* bit[13]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_2     : 1;  /* bit[14]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  errsyncesc_3     : 1;  /* bit[15]   : Low Power Data Transmission Synchronization Error. If the number of bits received during low power data transmission mode is not a multiple of eight (8) when the transmission ends, this signal is asserted and remains high until the line returns to Stop state. */
        unsigned int  ulpsactivenotclk : 1;  /* bit[16]   : Active Low. Indicates that the lane is in the Ultra Low Power state. For a Tx lane, this signal is asserted some time after TXULPSCLK. TXCLKESC must be supplied to the macro until ULPSACTIVENOTCLK is asserted.
                                                            In order to leave ULP state, the transmitter first drives TXULPSEXIT high, then waits for ULPSACTIVENOT to become high (inactive). At that point, the macro is active and has started transmitting a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives TXULPSCLK inactive to return the Lane to Stop state.
                                                            For a Rx lane, this signal indicates that the lane is in ULP state. At the beginning of ULP state, ULPSACTIVENOT is asserted together with RXCLKULPSNOT; at the end of the ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the RXULPSCLKNOT signal is deasserted. */
        unsigned int  reserved         : 15; /* bit[17-31]:  */
    } reg;
} SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_UNION;
#endif
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_0_START      (0)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_0_END        (0)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_1_START      (1)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_1_END        (1)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_2_START      (2)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_2_END        (2)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_3_START      (3)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxactivehs_3_END        (3)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_0_START       (4)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_0_END         (4)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_1_START       (5)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_1_END         (5)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_2_START       (6)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_2_END         (6)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_3_START       (7)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_rxlpdtesc_3_END         (7)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_0_START   (8)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_0_END     (8)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_1_START   (9)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_1_END     (9)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_2_START   (10)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_2_END     (10)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_3_START   (11)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenot_3_END     (11)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_0_START      (12)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_0_END        (12)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_1_START      (13)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_1_END        (13)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_2_START      (14)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_2_END        (14)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_3_START      (15)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_errsyncesc_3_END        (15)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenotclk_START  (16)
#define SOC_ISP_ISPSS_CTRL_PHY_CSI_C_dbg_ulpsactivenotclk_END    (16)






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

#endif /* end of soc_isp_ispss_ctrl_interface.h */
