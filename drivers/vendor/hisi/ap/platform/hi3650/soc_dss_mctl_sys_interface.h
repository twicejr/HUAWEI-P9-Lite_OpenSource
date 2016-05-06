/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_mctl_sys_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:11
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_MCTL_SYS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_MCTL_SYS_INTERFACE_H__
#define __SOC_DSS_MCTL_SYS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_MCTL_SYS
 ****************************************************************************/
/* 寄存器说明：安全配置寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_CTL_SECU_CFG_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_ADDR(base)      ((base) + (0x0000))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：安全禁止通路配置
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ADDR(base)    ((base) + (0x0080))

/* 寄存器说明：安全禁止通路配置
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ADDR(base)    ((base) + (0x0084))

/* 寄存器说明：安全禁止通路配置
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ADDR(base)    ((base) + (0x0088))

/* 寄存器说明：安全禁止通路配置
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_UNION */
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_ADDR(base)  ((base) + (0x00A0))

/* 寄存器说明：安全禁止通路配置
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_UNION */
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_ADDR(base)  ((base) + (0x00A4))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_ADDR(base)     ((base) + (0x0100))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_ADDR(base)     ((base) + (0x0104))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_ADDR(base)     ((base) + (0x0108))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_ADDR(base)     ((base) + (0x010C))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_ADDR(base)     ((base) + (0x0110))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_ADDR(base)     ((base) + (0x0114))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_ADDR(base)     ((base) + (0x0118))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_ADDR(base)     ((base) + (0x011C))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_ADDR(base)     ((base) + (0x0120))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_ADDR(base)     ((base) + (0x0124))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ADDR(base)      ((base) + (0x0128))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ADDR(base)      ((base) + (0x012C))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ADDR(base)      ((base) + (0x0130))

/* 寄存器说明：子模块寄存器刷新使能
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ADDR(base)      ((base) + (0x0134))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH0_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_ADDR(base)       ((base) + (0x0160))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH1_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_ADDR(base)       ((base) + (0x0164))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH2_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_ADDR(base)       ((base) + (0x0168))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH3_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_ADDR(base)       ((base) + (0x016C))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH4_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_ADDR(base)       ((base) + (0x0170))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH5_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_ADDR(base)       ((base) + (0x0174))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH6_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_ADDR(base)       ((base) + (0x0178))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH7_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_ADDR(base)       ((base) + (0x017C))

/* 寄存器说明：RCH对应OV0的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH_OV0_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_ADDR(base)       ((base) + (0x0180))

/* 寄存器说明：RCH对应OV1的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH_OV1_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_ADDR(base)       ((base) + (0x0184))

/* 寄存器说明：RCH对应OV2的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH_OV2_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_ADDR(base)       ((base) + (0x0188))

/* 寄存器说明：RCH对应OV3的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH_OV3_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_ADDR(base)       ((base) + (0x018C))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_WCH0_OV_IEN_UNION */
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_ADDR(base)       ((base) + (0x01A0))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_WCH1_OV_IEN_UNION */
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_ADDR(base)       ((base) + (0x01A4))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_WCH_OV2_SEL_UNION */
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_ADDR(base)       ((base) + (0x01A8))

/* 寄存器说明：RCH对应OV的layer选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_WCH_OV3_SEL_UNION */
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_ADDR(base)       ((base) + (0x01AC))

/* 寄存器说明：输出到ENC的wch选择
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_WB_ENC_SEL_UNION */
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_ADDR(base)        ((base) + (0x01B0))

/* 寄存器说明：DSI_MUX选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_DSI_MUX_SEL_UNION */
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_ADDR(base)       ((base) + (0x01B4))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH0_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_ADDR(base)       ((base) + (0x01C0))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH1_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_ADDR(base)       ((base) + (0x01C4))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH2_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_ADDR(base)       ((base) + (0x01C8))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH3_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_ADDR(base)       ((base) + (0x01CC))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH4_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_ADDR(base)       ((base) + (0x01D0))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH5_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_ADDR(base)       ((base) + (0x01D4))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH6_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_ADDR(base)       ((base) + (0x01D8))

/* 寄存器说明：RCH对应Y坐标
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_RCH7_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_ADDR(base)       ((base) + (0x01DC))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_UNION */
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_ADDR(base)      ((base) + (0x01F0))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MCTL_CLK_EN_UNION */
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_ADDR(base)       ((base) + (0x01F4))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD_CLK_SEL_UNION */
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_ADDR(base)       ((base) + (0x01F8))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD_CLK_EN_UNION */
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_ADDR(base)        ((base) + (0x01FC))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD0_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD0_DBG_ADDR(base)          ((base) + (0x0200))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD1_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD1_DBG_ADDR(base)          ((base) + (0x0204))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD2_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD2_DBG_ADDR(base)          ((base) + (0x0208))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD3_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD3_DBG_ADDR(base)          ((base) + (0x020C))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD4_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD4_DBG_ADDR(base)          ((base) + (0x0210))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD5_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD5_DBG_ADDR(base)          ((base) + (0x0214))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD6_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD6_DBG_ADDR(base)          ((base) + (0x0218))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD7_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD7_DBG_ADDR(base)          ((base) + (0x021C))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD8_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD8_DBG_ADDR(base)          ((base) + (0x0220))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD9_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD9_DBG_ADDR(base)          ((base) + (0x0224))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD10_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ADDR(base)         ((base) + (0x0228))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD11_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ADDR(base)         ((base) + (0x022C))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD12_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ADDR(base)         ((base) + (0x0230))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD13_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ADDR(base)         ((base) + (0x0234))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD14_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD14_DBG_ADDR(base)         ((base) + (0x0238))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD15_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD15_DBG_ADDR(base)         ((base) + (0x023C))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD16_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD16_DBG_ADDR(base)         ((base) + (0x0240))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD17_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD17_DBG_ADDR(base)         ((base) + (0x0244))

/* 寄存器说明：module可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD18_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD18_DBG_ADDR(base)         ((base) + (0x0248))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD0_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_ADDR(base)       ((base) + (0x0250))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD1_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_ADDR(base)       ((base) + (0x0254))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD2_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_ADDR(base)       ((base) + (0x0258))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD3_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_ADDR(base)       ((base) + (0x025C))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD4_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_ADDR(base)       ((base) + (0x0260))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD5_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_ADDR(base)       ((base) + (0x0264))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD6_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_ADDR(base)       ((base) + (0x0268))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD7_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_ADDR(base)       ((base) + (0x026C))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD8_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_ADDR(base)       ((base) + (0x0270))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD9_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_ADDR(base)       ((base) + (0x0274))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD10_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ADDR(base)      ((base) + (0x0278))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD11_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ADDR(base)      ((base) + (0x027C))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD12_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ADDR(base)      ((base) + (0x0280))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD13_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_ADDR(base)      ((base) + (0x0284))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD14_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ADDR(base)      ((base) + (0x0288))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD15_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_ADDR(base)      ((base) + (0x028C))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD16_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_ADDR(base)      ((base) + (0x0290))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD17_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_ADDR(base)      ((base) + (0x0294))

/* 寄存器说明：module状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_MOD18_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_ADDR(base)      ((base) + (0x0298))

/* 寄存器说明：SW可谓可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW_DBG_UNION */
#define SOC_DSS_MCTL_SYS_SW_DBG_ADDR(base)            ((base) + (0x02B0))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS0_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_ADDR(base)       ((base) + (0x02B4))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS1_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_ADDR(base)       ((base) + (0x02B8))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS2_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_ADDR(base)       ((base) + (0x02BC))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS3_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_ADDR(base)       ((base) + (0x02C0))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS4_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_ADDR(base)       ((base) + (0x02C4))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS5_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_ADDR(base)       ((base) + (0x02C8))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS6_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_ADDR(base)       ((base) + (0x02D0))

/* 寄存器说明：SW0状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW0_STATUS7_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_ADDR(base)       ((base) + (0x02D4))

/* 寄存器说明：SW1状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_SYS_SW1_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_SW1_STATUS_ADDR(base)        ((base) + (0x02D8))





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
                     (1/1) reg_MCTL_SYS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_CTL_SECU_CFG_UNION
 结构说明  : CTL_SECU_CFG 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 安全配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 4;  /* bit[0-3] : 保留 */
        unsigned int  pay_secu : 1;  /* bit[4]   : 1'b1:
                                                    OV0 top layer 寄存器安全配置使能，
                                                    vig0 channel 所有寄存器安全配置使能，
                                                   1'b0 : normal
                                                   复位值：1'b0 */
        unsigned int  reserved_1: 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_CFG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_pay_secu_START  (4)
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_pay_secu_END    (4)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_UNION
 结构说明  : PAY_SECU_FLUSH_EN 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pay_secu_flush_en : 1;  /* bit[0]   : 安全支付寄存器刷新使能
                                                            复位值：0x0 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_pay_secu_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_pay_secu_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_UNION
 结构说明  : CTL_SECU_GATE0 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 安全禁止通路配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_rch0_secu_gate : 6;  /* bit[0-5]  : 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_0         : 2;  /* bit[6-7]  : 保留 */
        unsigned int  ctl_rch1_secu_gate : 6;  /* bit[8-13] : 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: 保留 */
        unsigned int  ctl_rch2_secu_gate : 6;  /* bit[16-21]: 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_2         : 2;  /* bit[22-23]: 保留 */
        unsigned int  ctl_rch3_secu_gate : 6;  /* bit[24-29]: 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_3         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch0_secu_gate_START  (0)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch0_secu_gate_END    (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch1_secu_gate_START  (8)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch1_secu_gate_END    (13)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch2_secu_gate_START  (16)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch2_secu_gate_END    (21)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch3_secu_gate_START  (24)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch3_secu_gate_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_UNION
 结构说明  : CTL_SECU_GATE1 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 安全禁止通路配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_rch4_secu_gate : 6;  /* bit[0-5]  : 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_0         : 2;  /* bit[6-7]  : 保留 */
        unsigned int  ctl_rch5_secu_gate : 6;  /* bit[8-13] : 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: 保留 */
        unsigned int  ctl_rch6_secu_gate : 6;  /* bit[16-21]: 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_2         : 2;  /* bit[22-23]: 保留 */
        unsigned int  ctl_rch7_secu_gate : 6;  /* bit[24-29]: 选择RCH禁止配置的目地端
                                                              [5]: 1'b1 禁止RCH配置到WCH1，1'b0无效
                                                              [4]: 1'b1 禁止RCH配置到WCH0，1'b0无效
                                                              [3]: 1'b1 禁止RCH配置到OV3，1'b0无效
                                                              [2]: 1'b1 禁止RCH配置到OV2，1'b0无效
                                                              [1]: 1'b1 禁止RCH配置到OV1，1'b0无效
                                                              [0]: 1'b1 禁止RCH配置到OV0，1'b0无效 */
        unsigned int  reserved_3         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch4_secu_gate_START  (0)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch4_secu_gate_END    (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch5_secu_gate_START  (8)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch5_secu_gate_END    (13)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch6_secu_gate_START  (16)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch6_secu_gate_END    (21)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch7_secu_gate_START  (24)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch7_secu_gate_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_UNION
 结构说明  : CTL_SECU_GATE2 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 安全禁止通路配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 4;  /* bit[0-3] : 保留 */
        unsigned int  ctl_ov2_secu_gate : 2;  /* bit[4-5] : 选择OV禁止配置的目地端
                                                            [1]: 1'b1 禁止OV2配置到WCH1，1'b0无效
                                                            [0]: 1'b1 禁止OV2配置到WCH0，1'b0无效 */
        unsigned int  ctl_ov3_secu_gate : 2;  /* bit[6-7] : 选择OV禁止配置的目地端
                                                            [1]: 1'b1 禁止OV3配置到WCH1，1'b0无效
                                                            [0]: 1'b1 禁止OV3配置到WCH0，1'b0无效 */
        unsigned int  reserved_1        : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov2_secu_gate_START  (4)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov2_secu_gate_END    (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov3_secu_gate_START  (6)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov3_secu_gate_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_UNION
 结构说明  : DSI0_SECU_CFG_EN 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: 安全禁止通路配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi0_secu_cfg_en : 1;  /* bit[0]   : 仅可以由安全OS配置
                                                           1：安全
                                                           0：无效
                                                           DSI0 地址6c，70为安全OS配置 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_dsi0_secu_cfg_en_START  (0)
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_dsi0_secu_cfg_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_UNION
 结构说明  : DSI1_SECU_CFG_EN 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
 寄存器说明: 安全禁止通路配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi1_secu_cfg_en : 1;  /* bit[0]   : 仅可以由安全OS配置
                                                           1：安全
                                                           0：无效
                                                           DSI0 地址6c，70为安全OS配置 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_dsi1_secu_cfg_en_START  (0)
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_dsi1_secu_cfg_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_UNION
 结构说明  : RCH0_FLUSH_EN 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_flush_en : 1;  /* bit[0]   : rch0寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_rch0_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_rch0_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_UNION
 结构说明  : RCH1_FLUSH_EN 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_flush_en : 1;  /* bit[0]   : rch1寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_rch1_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_rch1_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_UNION
 结构说明  : RCH2_FLUSH_EN 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_flush_en : 1;  /* bit[0]   : rch2寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_rch2_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_rch2_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_UNION
 结构说明  : RCH3_FLUSH_EN 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_flush_en : 1;  /* bit[0]   : rch3寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_rch3_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_rch3_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_UNION
 结构说明  : RCH4_FLUSH_EN 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_flush_en : 1;  /* bit[0]   : rch4寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_rch4_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_rch4_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_UNION
 结构说明  : RCH5_FLUSH_EN 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_flush_en : 1;  /* bit[0]   : rch5寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_rch5_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_rch5_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_UNION
 结构说明  : RCH6_FLUSH_EN 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_flush_en : 1;  /* bit[0]   : rch6寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_rch6_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_rch6_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_UNION
 结构说明  : RCH7_FLUSH_EN 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_flush_en : 1;  /* bit[0]   : rch7寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_rch7_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_rch7_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_UNION
 结构说明  : WCH0_FLUSH_EN 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_flush_en : 1;  /* bit[0]   : wch0寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_wch0_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_wch0_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_UNION
 结构说明  : WCH1_FLUSH_EN 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_flush_en : 1;  /* bit[0]   : wch1寄存器刷新使能
                                                        复位值：0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_wch1_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_wch1_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_UNION
 结构说明  : OV0_FLUSH_EN 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov0_flush_en   : 1;  /* bit[0]   : ov0寄存器刷新使能
                                                         复位值：0x0 */
        unsigned int  scf_flush_en   : 1;  /* bit[1]   : scf寄存器刷新使能
                                                         复位值：0x0 */
        unsigned int  dbuf0_flush_en : 1;  /* bit[2]   : dbuf0寄存器刷新使能
                                                         复位值：0x0 */
        unsigned int  itf0_flush_en  : 1;  /* bit[3]   : dpp_itf0寄存器刷新使能
                                                         复位值：0x0 */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ov0_flush_en_START    (0)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ov0_flush_en_END      (0)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_scf_flush_en_START    (1)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_scf_flush_en_END      (1)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_dbuf0_flush_en_START  (2)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_dbuf0_flush_en_END    (2)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_itf0_flush_en_START   (3)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_itf0_flush_en_END     (3)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_UNION
 结构说明  : OV1_FLUSH_EN 寄存器结构定义。地址偏移量:0x012C，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov1_flush_en   : 1;  /* bit[0]   : ov1寄存器刷新使能
                                                         复位值：0x0 */
        unsigned int  reserved_0     : 1;  /* bit[1]   : 保留 */
        unsigned int  dbuf1_flush_en : 1;  /* bit[2]   : dbuf1寄存器刷新使能
                                                         复位值：0x0 */
        unsigned int  itf1_flush_en  : 1;  /* bit[3]   : itf1寄存器刷新使能
                                                         复位值：0x0 */
        unsigned int  reserved_1     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ov1_flush_en_START    (0)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ov1_flush_en_END      (0)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_dbuf1_flush_en_START  (2)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_dbuf1_flush_en_END    (2)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_itf1_flush_en_START   (3)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_itf1_flush_en_END     (3)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_UNION
 结构说明  : OV2_FLUSH_EN 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov2_flush_en : 1;  /* bit[0]   : ov2寄存器刷新使能
                                                       复位值：0x0 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ov2_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ov2_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_UNION
 结构说明  : OV3_FLUSH_EN 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: 子模块寄存器刷新使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov3_flush_en : 1;  /* bit[0]   : ov3寄存器刷新使能
                                                       复位值：0x0 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ov3_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ov3_flush_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH0_OV_OEN_UNION
 结构说明  : RCH0_OV_OEN 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_ov_oen : 12; /* bit[0-11] : rch0通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_rch0_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_rch0_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH1_OV_OEN_UNION
 结构说明  : RCH1_OV_OEN 寄存器结构定义。地址偏移量:0x0164，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_ov_oen : 12; /* bit[0-11] : rch1通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_rch1_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_rch1_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH2_OV_OEN_UNION
 结构说明  : RCH2_OV_OEN 寄存器结构定义。地址偏移量:0x0168，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_ov_oen : 12; /* bit[0-11] : rch2通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_rch2_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_rch2_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH3_OV_OEN_UNION
 结构说明  : RCH3_OV_OEN 寄存器结构定义。地址偏移量:0x016C，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_ov_oen : 12; /* bit[0-11] : rch3通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_rch3_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_rch3_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH4_OV_OEN_UNION
 结构说明  : RCH4_OV_OEN 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_ov_oen : 12; /* bit[0-11] : rch4通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_rch4_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_rch4_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH5_OV_OEN_UNION
 结构说明  : RCH5_OV_OEN 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_ov_oen : 12; /* bit[0-11] : rch5通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_rch5_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_rch5_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH6_OV_OEN_UNION
 结构说明  : RCH6_OV_OEN 寄存器结构定义。地址偏移量:0x0178，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_ov_oen : 12; /* bit[0-11] : rch6通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_rch6_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_rch6_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH7_OV_OEN_UNION
 结构说明  : RCH7_OV_OEN 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_ov_oen : 12; /* bit[0-11] : rch7通路输出选择
                                                       [7:0]：reserved
                                                       [8]：1'b1: OV0
                                                       [9]：1'b1: OV1
                                                       [10]：1'b1: OV2
                                                       [11]：1'b1: OV3
                                                       复位值：0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_rch7_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_rch7_ov_oen_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH_OV0_SEL_UNION
 结构说明  : RCH_OV0_SEL 寄存器结构定义。地址偏移量:0x0180，初值:0x0FFFFFFF，宽度:32
 寄存器说明: RCH对应OV0的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov0_sel : 28; /* bit[0-27] : ov0 layer输入选择
                                                       [27:24] layer5
                                                       [23:20] layer4
                                                       [19:16] layer3
                                                       [15:12] layer2
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layerv
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       复位值：0xFFFFFFF */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV0_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_rch_ov0_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_rch_ov0_sel_END    (27)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH_OV1_SEL_UNION
 结构说明  : RCH_OV1_SEL 寄存器结构定义。地址偏移量:0x0184，初值:0x00000FFF，宽度:32
 寄存器说明: RCH对应OV1的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov1_sel : 12; /* bit[0-11] : ov1 layer输入选择
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layerv
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       复位值：0xFFF */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV1_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_rch_ov1_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_rch_ov1_sel_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH_OV2_SEL_UNION
 结构说明  : RCH_OV2_SEL 寄存器结构定义。地址偏移量:0x0188，初值:0x0FFFFFFF，宽度:32
 寄存器说明: RCH对应OV2的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov2_sel : 28; /* bit[0-27] : ov2 layer输入选择
                                                       [27:24] layer5
                                                       [23:20] layer4
                                                       [19:16] layer3
                                                       [15:12] layer2
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layerv
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       复位值：0xFFFFFFF */
        unsigned int  reserved    : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV2_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_rch_ov2_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_rch_ov2_sel_END    (27)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH_OV3_SEL_UNION
 结构说明  : RCH_OV3_SEL 寄存器结构定义。地址偏移量:0x018C，初值:0x00000FFF，宽度:32
 寄存器说明: RCH对应OV3的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov3_sel : 12; /* bit[0-11] : ov3 layer输入选择
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layer
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       复位值：0xFFF */
        unsigned int  reserved    : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV3_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_rch_ov3_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_rch_ov3_sel_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_WCH0_OV_IEN_UNION
 结构说明  : WCH0_OV_IEN 寄存器结构定义。地址偏移量:0x01A0，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_ov_ien : 2;  /* bit[0-1] : wch0通路输入选择
                                                      2'b01: OV2
                                                      2'b10: OV3
                                                      2'b00,2'b11:reserved
                                                      复位值：0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_WCH0_OV_IEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_wch0_ov_ien_START  (0)
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_wch0_ov_ien_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_WCH1_OV_IEN_UNION
 结构说明  : WCH1_OV_IEN 寄存器结构定义。地址偏移量:0x01A4，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_ov_ien : 2;  /* bit[0-1] : wch1通路输入选择
                                                      2'b01: OV2
                                                      2'b10: OV3
                                                      2'b00,2'b11:reserved
                                                      复位值：0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_WCH1_OV_IEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_wch1_ov_ien_START  (0)
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_wch1_ov_ien_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_WCH_OV2_SEL_UNION
 结构说明  : WCH_OV2_SEL 寄存器结构定义。地址偏移量:0x01A8，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch_ov2_sel : 2;  /* bit[0-1] : OV2通路输入选择
                                                      2'b01: 选择wch0
                                                      2'b10: 选择wch1
                                                      2'b11: 选择wch0,wch1
                                                      2‘b00：reserved
                                                      复位值：0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_WCH_OV2_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_wch_ov2_sel_START  (0)
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_wch_ov2_sel_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_WCH_OV3_SEL_UNION
 结构说明  : WCH_OV3_SEL 寄存器结构定义。地址偏移量:0x01AC，初值:0x00000000，宽度:32
 寄存器说明: RCH对应OV的layer选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch_ov3_sel : 2;  /* bit[0-1] : OV3通路输入选择
                                                      2'b01: 选择wch0
                                                      2'b10: 选择wch1
                                                      2'b11: 选择wch0,wch1
                                                      2‘b00：reserved
                                                      复位值：0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_WCH_OV3_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_wch_ov3_sel_START  (0)
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_wch_ov3_sel_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_WB_ENC_SEL_UNION
 结构说明  : WB_ENC_SEL 寄存器结构定义。地址偏移量:0x01B0，初值:0x00000000，宽度:32
 寄存器说明: 输出到ENC的wch选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wb_enc_sel : 2;  /* bit[0-1] : 选择输出给enc的回写通路
                                                     2'b01:选择wch0作为输出给encoder的回写通路
                                                     2'b10:选择wch1作为输出给encoder的回写通路
                                                     2'b11,2'b00: 无输出给encoder的回写通路
                                                     复位值2'b00 */
        unsigned int  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_WB_ENC_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_wb_enc_sel_START  (0)
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_wb_enc_sel_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_DSI_MUX_SEL_UNION
 结构说明  : DSI_MUX_SEL 寄存器结构定义。地址偏移量:0x01B4，初值:0x00000000，宽度:32
 寄存器说明: DSI_MUX选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_mux_sel : 1;  /* bit[0]   : DSI_MUX控制选择寄存器
                                                      1'b0 : 选择LDI0 DPI1 从DSI1输出
                                                      1'b1 : 选择LDI1 DPI0 从DSI1输出 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_DSI_MUX_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_dsi_mux_sel_START  (0)
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_dsi_mux_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH0_STARTY_UNION
 结构说明  : RCH0_STARTY 寄存器结构定义。地址偏移量:0x01C0，初值:0x00080000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch0_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH1_STARTY_UNION
 结构说明  : RCH1_STARTY 寄存器结构定义。地址偏移量:0x01C4，初值:0x00000000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch1_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH2_STARTY_UNION
 结构说明  : RCH2_STARTY 寄存器结构定义。地址偏移量:0x01C8，初值:0x000C0000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch2_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH3_STARTY_UNION
 结构说明  : RCH3_STARTY 寄存器结构定义。地址偏移量:0x01CC，初值:0x00090000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch3_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH4_STARTY_UNION
 结构说明  : RCH4_STARTY 寄存器结构定义。地址偏移量:0x01D0，初值:0x000A0000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch4_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH5_STARTY_UNION
 结构说明  : RCH5_STARTY 寄存器结构定义。地址偏移量:0x01D4，初值:0x00090000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch5_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH6_STARTY_UNION
 结构说明  : RCH6_STARTY 寄存器结构定义。地址偏移量:0x01D8，初值:0x00000000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch6_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_RCH7_STARTY_UNION
 结构说明  : RCH7_STARTY 寄存器结构定义。地址偏移量:0x01DC，初值:0x00000000，宽度:32
 寄存器说明: RCH对应Y坐标
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_starty : 15; /* bit[0-14] : RCH对应的图层起始y坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  rch7_thld   : 15; /* bit[16-30]: 预先启动的阈值 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_thld_END      (30)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_UNION
 结构说明  : MCTL_CLK_SEL 寄存器结构定义。地址偏移量:0x01F0，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mctl_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                       1：表示强制打开时钟。
                                                       0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                       [7:0]：用于ctl_mutex0~7；
                                                       [30:8]：reserved
                                                       [31]：用于apb； */
    } reg;
} SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_mctl_clk_sel_START  (0)
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_mctl_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MCTL_CLK_EN_UNION
 结构说明  : MCTL_CLK_EN 寄存器结构定义。地址偏移量:0x01F4，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mctl_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                      1：表示软件时钟使能有效，允许硬件开钟
                                                      0：表示软件时钟使能无效，禁止硬件开钟
                                                      [7:0]：用于mctl_mutex0~7；
                                                      [31:8]：reserved */
    } reg;
} SOC_DSS_MCTL_SYS_MCTL_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_mctl_clk_en_START  (0)
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_mctl_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD_CLK_SEL_UNION
 结构说明  : MOD_CLK_SEL 寄存器结构定义。地址偏移量:0x01F8，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mod_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                      1：表示强制打开时钟。
                                                      0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                      [7:0] rch0~7
                                                      [9:8] wch0~1
                                                      [13:10] ov0~3
                                                      [14] scf
                                                      [16:15] dbuf0~1
                                                      [18:17] itf0~1
                                                      [31:19] reserved */
    } reg;
} SOC_DSS_MCTL_SYS_MOD_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_mod_clk_sel_START  (0)
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_mod_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD_CLK_EN_UNION
 结构说明  : MOD_CLK_EN 寄存器结构定义。地址偏移量:0x01FC，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mod_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                     1：表示软件时钟使能有效，允许硬件开钟
                                                     0：表示软件时钟使能无效，禁止硬件开钟
                                                     [7:0] rch0~7
                                                     [9:8] wch0~1
                                                     [13:10] ov0~3
                                                     [14] scf
                                                     [16:15] dbuf0~1
                                                     [18:17] itf0~1
                                                     [31:19] reserved */
    } reg;
} SOC_DSS_MCTL_SYS_MOD_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_mod_clk_en_START  (0)
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_mod_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD0_DBG_UNION
 结构说明  : MOD0_DBG 寄存器结构定义。地址偏移量:0x0200，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD0_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD0_DBG_rch0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD0_DBG_rch0_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD1_DBG_UNION
 结构说明  : MOD1_DBG 寄存器结构定义。地址偏移量:0x0204，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD1_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD1_DBG_rch1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD1_DBG_rch1_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD2_DBG_UNION
 结构说明  : MOD2_DBG 寄存器结构定义。地址偏移量:0x0208，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD2_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD2_DBG_rch2_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD2_DBG_rch2_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD3_DBG_UNION
 结构说明  : MOD3_DBG 寄存器结构定义。地址偏移量:0x020C，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD3_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD3_DBG_rch3_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD3_DBG_rch3_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD4_DBG_UNION
 结构说明  : MOD4_DBG 寄存器结构定义。地址偏移量:0x0210，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD4_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD4_DBG_rch4_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD4_DBG_rch4_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD5_DBG_UNION
 结构说明  : MOD5_DBG 寄存器结构定义。地址偏移量:0x0214，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD5_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD5_DBG_rch5_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD5_DBG_rch5_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD6_DBG_UNION
 结构说明  : MOD6_DBG 寄存器结构定义。地址偏移量:0x0218，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD6_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD6_DBG_rch6_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD6_DBG_rch6_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD7_DBG_UNION
 结构说明  : MOD7_DBG 寄存器结构定义。地址偏移量:0x021C，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD7_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD7_DBG_rch7_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD7_DBG_rch7_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD8_DBG_UNION
 结构说明  : MOD8_DBG 寄存器结构定义。地址偏移量:0x0220，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD8_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD8_DBG_wch0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD8_DBG_wch0_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD9_DBG_UNION
 结构说明  : MOD9_DBG 寄存器结构定义。地址偏移量:0x0224，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD9_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD9_DBG_wch1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD9_DBG_wch1_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD10_DBG_UNION
 结构说明  : MOD10_DBG 寄存器结构定义。地址偏移量:0x0228，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov0_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD10_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ov0_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ov0_dbg_END     (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD11_DBG_UNION
 结构说明  : MOD11_DBG 寄存器结构定义。地址偏移量:0x022C，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov1_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD11_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ov1_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ov1_dbg_END     (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD12_DBG_UNION
 结构说明  : MOD12_DBG 寄存器结构定义。地址偏移量:0x0230，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov2_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD12_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ov2_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ov2_dbg_END     (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD13_DBG_UNION
 结构说明  : MOD13_DBG 寄存器结构定义。地址偏移量:0x0234，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov3_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD13_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ov3_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ov3_dbg_END     (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD14_DBG_UNION
 结构说明  : MOD14_DBG 寄存器结构定义。地址偏移量:0x0238，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD14_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD14_DBG_scf_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD14_DBG_scf_dbg_END     (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD15_DBG_UNION
 结构说明  : MOD15_DBG 寄存器结构定义。地址偏移量:0x023C，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf0_dbg : 24; /* bit[0-23] : [23:22] 
                                                     2'b11 软件配置，按mod 发起clear
                                                     2'b10 软件配置，按mod撤销clear
                                                     2'b0* 硬件自动按ctl发clear
                                                     [21:20] 
                                                     2'b11 软件配置，强制恢复idle态
                                                     2'b10 软件配置，撤销强制恢复idle态
                                                     2'b0* 硬件判断是否idle态
                                                     [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                     [17:16] mod end信号延时配置
                                                     [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                     [7] 屏蔽starty
                                                     [6：5] reserved
                                                     [4]no flush_en press:
                                                     1'b1:module flush_en不支持根据ov ycnt自动反压
                                                     1'b0:module flush_en支持根据ov ycnt自动反压
                                                     [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                     [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                     [1] no start
                                                     1'b1:仅产生reload，无start产生
                                                     配置后立刻生效
                                                     [0] bypass starty */
        unsigned int  reserved  : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD15_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD15_DBG_dbuf0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD15_DBG_dbuf0_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD16_DBG_UNION
 结构说明  : MOD16_DBG 寄存器结构定义。地址偏移量:0x0240，初值:0x00020000，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf1_dbg : 24; /* bit[0-23] : [23:22] 
                                                     2'b11 软件配置，按mod 发起clear
                                                     2'b10 软件配置，按mod撤销clear
                                                     2'b0* 硬件自动按ctl发clear
                                                     [21:20] 
                                                     2'b11 软件配置，强制恢复idle态
                                                     2'b10 软件配置，撤销强制恢复idle态
                                                     2'b0* 硬件判断是否idle态
                                                     [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                     [17:16] mod end信号延时配置
                                                     [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                     [7] 屏蔽starty
                                                     [6：5] reserved
                                                     [4]no flush_en press:
                                                     1'b1:module flush_en不支持根据ov ycnt自动反压
                                                     1'b0:module flush_en支持根据ov ycnt自动反压
                                                     [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                     [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                     [1] no start
                                                     1'b1:仅产生reload，无start产生
                                                     配置后立刻生效
                                                     [0] bypass starty */
        unsigned int  reserved  : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD16_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD16_DBG_dbuf1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD16_DBG_dbuf1_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD17_DBG_UNION
 结构说明  : MOD17_DBG 寄存器结构定义。地址偏移量:0x0244，初值:0x00020F00，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf0_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD17_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD17_DBG_itf0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD17_DBG_itf0_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD18_DBG_UNION
 结构说明  : MOD18_DBG 寄存器结构定义。地址偏移量:0x0248，初值:0x00020F00，宽度:32
 寄存器说明: module可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf1_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 软件配置，按mod 发起clear
                                                    2'b10 软件配置，按mod撤销clear
                                                    2'b0* 硬件自动按ctl发clear
                                                    [21:20] 
                                                    2'b11 软件配置，强制恢复idle态
                                                    2'b10 软件配置，撤销强制恢复idle态
                                                    2'b0* 硬件判断是否idle态
                                                    [19] 1'b1 清除当前已经配置的flush_en（cpu模式不要配置，cmdlist模式需要配置）
                                                    [17:16] mod end信号延时配置
                                                    [15:8]ctl_st_idly 控制模块进入start状态，需要延迟的时间
                                                    [7] 屏蔽starty
                                                    [6：5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en不支持根据ov ycnt自动反压
                                                    1'b0:module flush_en支持根据ov ycnt自动反压
                                                    [3] 清除记录的用来dbg的reload状态，配合mod_status工作
                                                    [2] 清除记录的用来dbgstart状态，配合mod_status工作
                                                    [1] no start
                                                    1'b1:仅产生reload，无start产生
                                                    配置后立刻生效
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD18_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD18_DBG_itf1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD18_DBG_itf1_dbg_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD0_STATUS_UNION
 结构说明  : MOD0_STATUS 寄存器结构定义。地址偏移量:0x0250，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD0_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_rch0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_rch0_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD1_STATUS_UNION
 结构说明  : MOD1_STATUS 寄存器结构定义。地址偏移量:0x0254，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD1_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_rch1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_rch1_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD2_STATUS_UNION
 结构说明  : MOD2_STATUS 寄存器结构定义。地址偏移量:0x0258，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD2_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_rch2_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_rch2_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD3_STATUS_UNION
 结构说明  : MOD3_STATUS 寄存器结构定义。地址偏移量:0x025C，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD3_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_rch3_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_rch3_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD4_STATUS_UNION
 结构说明  : MOD4_STATUS 寄存器结构定义。地址偏移量:0x0260，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD4_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_rch4_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_rch4_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD5_STATUS_UNION
 结构说明  : MOD5_STATUS 寄存器结构定义。地址偏移量:0x0264，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD5_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_rch5_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_rch5_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD6_STATUS_UNION
 结构说明  : MOD6_STATUS 寄存器结构定义。地址偏移量:0x0268，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD6_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_rch6_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_rch6_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD7_STATUS_UNION
 结构说明  : MOD7_STATUS 寄存器结构定义。地址偏移量:0x026C，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD7_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_rch7_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_rch7_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD8_STATUS_UNION
 结构说明  : MOD8_STATUS 寄存器结构定义。地址偏移量:0x0270，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD8_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_wch0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_wch0_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD9_STATUS_UNION
 结构说明  : MOD9_STATUS 寄存器结构定义。地址偏移量:0x0274，初值:0x00000016，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD9_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_wch1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_wch1_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD10_STATUS_UNION
 结构说明  : MOD10_STATUS 寄存器结构定义。地址偏移量:0x0278，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov1_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD10_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ov1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ov1_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD11_STATUS_UNION
 结构说明  : MOD11_STATUS 寄存器结构定义。地址偏移量:0x027C，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov2_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD11_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ov2_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ov2_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD12_STATUS_UNION
 结构说明  : MOD12_STATUS 寄存器结构定义。地址偏移量:0x0280，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov3_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD12_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ov3_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ov3_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD13_STATUS_UNION
 结构说明  : MOD13_STATUS 寄存器结构定义。地址偏移量:0x0284，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD13_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_scf_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_scf_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD14_STATUS_UNION
 结构说明  : MOD14_STATUS 寄存器结构定义。地址偏移量:0x0288，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov0_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD14_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ov0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ov0_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD15_STATUS_UNION
 结构说明  : MOD15_STATUS 寄存器结构定义。地址偏移量:0x028C，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf0_status : 6;  /* bit[0-5] : [0] reload status
                                                       [1] flush status
                                                       [2] activey
                                                       [3] start status
                                                       [4] idle
                                                       [5] clear ack */
        unsigned int  reserved     : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD15_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_dbuf0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_dbuf0_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD16_STATUS_UNION
 结构说明  : MOD16_STATUS 寄存器结构定义。地址偏移量:0x0290，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf1_status : 6;  /* bit[0-5] : [0] reload status
                                                       [1] flush status
                                                       [2] activey
                                                       [3] start status
                                                       [4] idle
                                                       [5] clear ack */
        unsigned int  reserved     : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD16_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_dbuf1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_dbuf1_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD17_STATUS_UNION
 结构说明  : MOD17_STATUS 寄存器结构定义。地址偏移量:0x0294，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf0_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD17_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_itf0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_itf0_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_MOD18_STATUS_UNION
 结构说明  : MOD18_STATUS 寄存器结构定义。地址偏移量:0x0298，初值:0x00000036，宽度:32
 寄存器说明: module状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf1_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_MOD18_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_itf1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_itf1_status_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW_DBG_UNION
 结构说明  : SW_DBG 寄存器结构定义。地址偏移量:0x02B0，初值:0x00000000，宽度:32
 寄存器说明: SW可谓可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_dbg   : 16; /* bit[0-15] : [0]:apb_secu_en使能，为1表示安全配置，为0表示非安全配置
                                                    [15:1]:reserved； */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_SW_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW_DBG_sw_dbg_START    (0)
#define SOC_DSS_MCTL_SYS_SW_DBG_sw_dbg_END      (15)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS0_UNION
 结构说明  : SW0_STATUS0 寄存器结构定义。地址偏移量:0x02B4，初值:0x00000000，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status0 : 32; /* bit[0-31]: sw0端口rch output enable状态
                                                      [7] rch7_oen
                                                      [6] rch6_oen
                                                      [5] rch5_oen
                                                      [4] rch4_oen
                                                      [3] rch3_oen
                                                      [2] rch2_oen
                                                      [1] rch1_oen
                                                      [0] rch0_oen */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS0_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_sw0_status0_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_sw0_status0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS1_UNION
 结构说明  : SW0_STATUS1 寄存器结构定义。地址偏移量:0x02B8，初值:0x0FFFFFFF，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status1 : 32; /* bit[0-31]: sw0端口overlay select状态
                                                      [27:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS1_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_sw0_status1_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_sw0_status1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS2_UNION
 结构说明  : SW0_STATUS2 寄存器结构定义。地址偏移量:0x02BC，初值:0x00000FFF，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status2 : 32; /* bit[0-31]: sw0端口overlay select状态
                                                      [11:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS2_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_sw0_status2_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_sw0_status2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS3_UNION
 结构说明  : SW0_STATUS3 寄存器结构定义。地址偏移量:0x02C0，初值:0x0FFFFFFF，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status3 : 32; /* bit[0-31]: sw0端口overlay select状态
                                                      [27:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS3_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_sw0_status3_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_sw0_status3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS4_UNION
 结构说明  : SW0_STATUS4 寄存器结构定义。地址偏移量:0x02C4，初值:0x00000FFF，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status4 : 32; /* bit[0-31]: sw0端口overlay select状态
                                                      [11:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS4_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_sw0_status4_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_sw0_status4_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS5_UNION
 结构说明  : SW0_STATUS5 寄存器结构定义。地址偏移量:0x02C8，初值:0x0007C000，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status5 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS5_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_sw0_status5_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_sw0_status5_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS6_UNION
 结构说明  : SW0_STATUS6 寄存器结构定义。地址偏移量:0x02D0，初值:0x00000000，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status6 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS6_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_sw0_status6_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_sw0_status6_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW0_STATUS7_UNION
 结构说明  : SW0_STATUS7 寄存器结构定义。地址偏移量:0x02D4，初值:0x00000000，宽度:32
 寄存器说明: SW0状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status7 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS7_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_sw0_status7_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_sw0_status7_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_SYS_SW1_STATUS_UNION
 结构说明  : SW1_STATUS 寄存器结构定义。地址偏移量:0x02D8，初值:0x00000000，宽度:32
 寄存器说明: SW1状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw1_status : 8;  /* bit[0-7] : [7:6] wch0_ien
                                                     [5:4] wch1_ien
                                                     [3:2] ov2_wch选择状态
                                                     [1:0] ov3_wch选择状态 */
        unsigned int  reserved   : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_SYS_SW1_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW1_STATUS_sw1_status_START  (0)
#define SOC_DSS_MCTL_SYS_SW1_STATUS_sw1_status_END    (7)






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

#endif /* end of soc_dss_mctl_sys_interface.h */
