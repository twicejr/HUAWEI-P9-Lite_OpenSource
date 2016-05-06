/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_ov6_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:15
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_OV6.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_OV6_INTERFACE_H__
#define __SOC_DSS_OV6_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_OV6
 ****************************************************************************/
/* 寄存器说明：overlay图像大小
   位域定义UNION结构:  SOC_DSS_OV6_OV_SIZE_UNION */
#define SOC_DSS_OV6_OV_SIZE_ADDR(base)                ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_OV_BG_COLOR_UNION */
#define SOC_DSS_OV6_OV_BG_COLOR_ADDR(base)            ((base) + (0x4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_DST_STARTPOS_UNION */
#define SOC_DSS_OV6_DST_STARTPOS_ADDR(base)           ((base) + (0x8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_DST_ENDPOS_UNION */
#define SOC_DSS_OV6_DST_ENDPOS_ADDR(base)             ((base) + (0xC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_OV_GCFG_UNION */
#define SOC_DSS_OV6_OV_GCFG_ADDR(base)                ((base) + (0x10))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_POS_UNION */
#define SOC_DSS_OV6_LAYER0_POS_ADDR(base)             ((base) + (0x14))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_SIZE_UNION */
#define SOC_DSS_OV6_LAYER0_SIZE_ADDR(base)            ((base) + (0x18))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_ADDR(base)        ((base) + (0x1C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_ADDR(base)        ((base) + (0x20))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_ADDR(base)        ((base) + (0x24))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_ADDR(base)        ((base) + (0x28))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER0_PATTERN_ADDR(base)         ((base) + (0x2C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER0_ALPHA_ADDR(base)           ((base) + (0x30))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_CFG_UNION */
#define SOC_DSS_OV6_LAYER0_CFG_ADDR(base)             ((base) + (0x34))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER0_PSPOS_ADDR(base)           ((base) + (0x38))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER0_PEPOS_ADDR(base)           ((base) + (0x3C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_ADDR(base)      ((base) + (0x40))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x44))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER0_ST_INFO_ADDR(base)         ((base) + (0x48))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER0_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER0_IST_INFO_ADDR(base)        ((base) + (0x4C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_POS_UNION */
#define SOC_DSS_OV6_LAYER1_POS_ADDR(base)             ((base) + (0x50))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_SIZE_UNION */
#define SOC_DSS_OV6_LAYER1_SIZE_ADDR(base)            ((base) + (0x54))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_ADDR(base)        ((base) + (0x58))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_ADDR(base)        ((base) + (0x5C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_ADDR(base)        ((base) + (0x60))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_ADDR(base)        ((base) + (0x64))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER1_PATTERN_ADDR(base)         ((base) + (0x68))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER1_ALPHA_ADDR(base)           ((base) + (0x6C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_CFG_UNION */
#define SOC_DSS_OV6_LAYER1_CFG_ADDR(base)             ((base) + (0x70))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER1_PSPOS_ADDR(base)           ((base) + (0x74))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER1_PEPOS_ADDR(base)           ((base) + (0x78))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_ADDR(base)      ((base) + (0x7C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x80))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER1_ST_INFO_ADDR(base)         ((base) + (0x84))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER1_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER1_IST_INFO_ADDR(base)        ((base) + (0x88))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_POS_UNION */
#define SOC_DSS_OV6_LAYER2_POS_ADDR(base)             ((base) + (0x8C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_SIZE_UNION */
#define SOC_DSS_OV6_LAYER2_SIZE_ADDR(base)            ((base) + (0x90))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_ADDR(base)        ((base) + (0x94))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_ADDR(base)        ((base) + (0x98))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_ADDR(base)        ((base) + (0x9C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_ADDR(base)        ((base) + (0xA0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER2_PATTERN_ADDR(base)         ((base) + (0xA4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER2_ALPHA_ADDR(base)           ((base) + (0xA8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_CFG_UNION */
#define SOC_DSS_OV6_LAYER2_CFG_ADDR(base)             ((base) + (0xAC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER2_PSPOS_ADDR(base)           ((base) + (0xB0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER2_PEPOS_ADDR(base)           ((base) + (0xB4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_ADDR(base)      ((base) + (0xB8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_ADDR(base)   ((base) + (0xBC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER2_ST_INFO_ADDR(base)         ((base) + (0xC0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER2_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER2_IST_INFO_ADDR(base)        ((base) + (0xC4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_POS_UNION */
#define SOC_DSS_OV6_LAYER3_POS_ADDR(base)             ((base) + (0xC8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_SIZE_UNION */
#define SOC_DSS_OV6_LAYER3_SIZE_ADDR(base)            ((base) + (0xCC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_ADDR(base)        ((base) + (0xD0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_ADDR(base)        ((base) + (0xD4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_ADDR(base)        ((base) + (0xD8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_ADDR(base)        ((base) + (0xDC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER3_PATTERN_ADDR(base)         ((base) + (0xE0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER3_ALPHA_ADDR(base)           ((base) + (0xE4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_CFG_UNION */
#define SOC_DSS_OV6_LAYER3_CFG_ADDR(base)             ((base) + (0xE8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER3_PSPOS_ADDR(base)           ((base) + (0xEC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER3_PEPOS_ADDR(base)           ((base) + (0xF0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_ADDR(base)      ((base) + (0xF4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_ADDR(base)   ((base) + (0xF8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER3_ST_INFO_ADDR(base)         ((base) + (0xFC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER3_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER3_IST_INFO_ADDR(base)        ((base) + (0x100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_POS_UNION */
#define SOC_DSS_OV6_LAYER4_POS_ADDR(base)             ((base) + (0x104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_SIZE_UNION */
#define SOC_DSS_OV6_LAYER4_SIZE_ADDR(base)            ((base) + (0x108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_ADDR(base)        ((base) + (0x10C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_ADDR(base)        ((base) + (0x110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_ADDR(base)        ((base) + (0x114))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_ADDR(base)        ((base) + (0x118))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER4_PATTERN_ADDR(base)         ((base) + (0x11C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER4_ALPHA_ADDR(base)           ((base) + (0x120))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_CFG_UNION */
#define SOC_DSS_OV6_LAYER4_CFG_ADDR(base)             ((base) + (0x124))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER4_PSPOS_ADDR(base)           ((base) + (0x128))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER4_PEPOS_ADDR(base)           ((base) + (0x12C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_ADDR(base)      ((base) + (0x130))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x134))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER4_ST_INFO_ADDR(base)         ((base) + (0x138))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER4_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER4_IST_INFO_ADDR(base)        ((base) + (0x13C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_POS_UNION */
#define SOC_DSS_OV6_LAYER5_POS_ADDR(base)             ((base) + (0x140))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_SIZE_UNION */
#define SOC_DSS_OV6_LAYER5_SIZE_ADDR(base)            ((base) + (0x144))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_ADDR(base)        ((base) + (0x148))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_ADDR(base)        ((base) + (0x14C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_ADDR(base)        ((base) + (0x150))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_ADDR(base)        ((base) + (0x154))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER5_PATTERN_ADDR(base)         ((base) + (0x158))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER5_ALPHA_ADDR(base)           ((base) + (0x15C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_CFG_UNION */
#define SOC_DSS_OV6_LAYER5_CFG_ADDR(base)             ((base) + (0x160))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER5_PSPOS_ADDR(base)           ((base) + (0x164))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER5_PEPOS_ADDR(base)           ((base) + (0x168))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_ADDR(base)      ((base) + (0x16C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x170))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER5_ST_INFO_ADDR(base)         ((base) + (0x174))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_LAYER5_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER5_IST_INFO_ADDR(base)        ((base) + (0x178))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_BASE_ST_INFO_UNION */
#define SOC_DSS_OV6_BASE_ST_INFO_ADDR(base)           ((base) + (0x17C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_BASE_IST_INFO_UNION */
#define SOC_DSS_OV6_BASE_IST_INFO_ADDR(base)          ((base) + (0x180))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_GATE_CTRL_UNION */
#define SOC_DSS_OV6_GATE_CTRL_ADDR(base)              ((base) + (0x184))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_OV6_OV_RD_SHADOW_SEL_UNION */
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ADDR(base)       ((base) + (0x188))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_OV6_OV_CLK_SEL_UNION */
#define SOC_DSS_OV6_OV_CLK_SEL_ADDR(base)             ((base) + (0x018C))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_OV6_OV_CLK_EN_UNION */
#define SOC_DSS_OV6_OV_CLK_EN_ADDR(base)              ((base) + (0x0190))

/* 寄存器说明：Block的图像高度
   位域定义UNION结构:  SOC_DSS_OV6_BLOCK_SIZE_UNION */
#define SOC_DSS_OV6_BLOCK_SIZE_ADDR(base)             ((base) + (0x01A0))

/* 寄存器说明：分块可谓可测寄存
   位域定义UNION结构:  SOC_DSS_OV6_BLOCK_DBG_UNION */
#define SOC_DSS_OV6_BLOCK_DBG_ADDR(base)              ((base) + (0x01A4))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_OV6_REG_DEFAULT_UNION */
#define SOC_DSS_OV6_REG_DEFAULT_ADDR(base)            ((base) + (0x01A8))





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
                     (1/1) reg_OV6
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_OV6_OV_SIZE_UNION
 结构说明  : OV_SIZE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: overlay图像大小
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  img_width  : 15; /* bit[0-14] : overlay最终输出图像宽度-1，以像素为单位 */
        unsigned int  reserved_0 : 1;  /* bit[15]   : 保留 */
        unsigned int  img_height : 15; /* bit[16-30]: overlay最终输出图像高度-1 */
        unsigned int  reserved_1 : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_OV_SIZE_UNION;
#endif
#define SOC_DSS_OV6_OV_SIZE_img_width_START   (0)
#define SOC_DSS_OV6_OV_SIZE_img_width_END     (14)
#define SOC_DSS_OV6_OV_SIZE_img_height_START  (16)
#define SOC_DSS_OV6_OV_SIZE_img_height_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_OV_BG_COLOR_UNION
 结构说明  : OV_BG_COLOR 寄存器结构定义。地址偏移量:0x4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bg_color : 32; /* bit[0-31]: overlay 背景颜色，最底层，格式为argb8888 */
    } reg;
} SOC_DSS_OV6_OV_BG_COLOR_UNION;
#endif
#define SOC_DSS_OV6_OV_BG_COLOR_bg_color_START  (0)
#define SOC_DSS_OV6_OV_BG_COLOR_bg_color_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_DST_STARTPOS_UNION
 结构说明  : DST_STARTPOS 寄存器结构定义。地址偏移量:0x8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blayer_startx : 15; /* bit[0-14] : baselayer 操作矩形区域起始点x坐标 */
        unsigned int  reserved_0    : 1;  /* bit[15]   : 保留 */
        unsigned int  blayer_starty : 15; /* bit[16-30]: baselayer 操作矩形区域起始点y坐标 */
        unsigned int  reserved_1    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_DST_STARTPOS_UNION;
#endif
#define SOC_DSS_OV6_DST_STARTPOS_blayer_startx_START  (0)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_startx_END    (14)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_starty_START  (16)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_starty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_DST_ENDPOS_UNION
 结构说明  : DST_ENDPOS 寄存器结构定义。地址偏移量:0xC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blayer_endx : 15; /* bit[0-14] : baselayer 操作矩形区域结束x坐标 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  blayer_endy : 15; /* bit[16-30]: baselayer 操作矩形区域结束y坐标 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_DST_ENDPOS_UNION;
#endif
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endx_START  (0)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endx_END    (14)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endy_START  (16)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_OV_GCFG_UNION
 结构说明  : OV_GCFG 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overlay_enable    : 1;  /* bit[0]    : overlay enable */
        unsigned int  reserved_0        : 7;  /* bit[1-7]  : 保留 */
        unsigned int  reserved_1        : 3;  /* bit[8-10] : 保留 */
        unsigned int  reserved_2        : 3;  /* bit[11-13]: 保留 */
        unsigned int  reserved_3        : 2;  /* bit[14-15]: 保留 */
        unsigned int  blayer_bgcolor_en : 1;  /* bit[16]   : 0: choose src0
                                                             1: only ouput constant color argb8888 format */
        unsigned int  reserved_4        : 3;  /* bit[17-19]: 保留 */
        unsigned int  p3fmt             : 2;  /* bit[20-21]: 00: half line by line
                                                             01: column by column
                                                             10: quincunx */
        unsigned int  reserved_5        : 2;  /* bit[22-23]: 保留 */
        unsigned int  p3fmt_enable      : 1;  /* bit[24]   : 3D format enable  */
        unsigned int  reserved_6        : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_DSS_OV6_OV_GCFG_UNION;
#endif
#define SOC_DSS_OV6_OV_GCFG_overlay_enable_START     (0)
#define SOC_DSS_OV6_OV_GCFG_overlay_enable_END       (0)
#define SOC_DSS_OV6_OV_GCFG_blayer_bgcolor_en_START  (16)
#define SOC_DSS_OV6_OV_GCFG_blayer_bgcolor_en_END    (16)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_START              (20)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_END                (21)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_enable_START       (24)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_enable_END         (24)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_POS_UNION
 结构说明  : LAYER0_POS 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_startx : 15; /* bit[0-14] : layer 0 操作矩形区域起始点x左边 */
        unsigned int  reserved_0    : 1;  /* bit[15]   : 保留 */
        unsigned int  layer0_starty : 15; /* bit[16-30]: layer 0 操作矩形区域起始点y坐标 */
        unsigned int  reserved_1    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_POS_layer0_startx_START  (0)
#define SOC_DSS_OV6_LAYER0_POS_layer0_startx_END    (14)
#define SOC_DSS_OV6_LAYER0_POS_layer0_starty_START  (16)
#define SOC_DSS_OV6_LAYER0_POS_layer0_starty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_SIZE_UNION
 结构说明  : LAYER0_SIZE 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_endx : 15; /* bit[0-14] : layer 0 操作矩形区域结束x杰作 */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  layer0_endy : 15; /* bit[16-30]: layer 0 操作矩形区域结束y坐标 */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endx_START  (0)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endx_END    (14)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endy_START  (16)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_SRCLOKEY_UNION
 结构说明  : LAYER0_SRCLOKEY 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_src_locolorkey : 24; /* bit[0-23] : layer 0 source low color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_layer0_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_layer0_src_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_SRCHIKEY_UNION
 结构说明  : LAYER0_SRCHIKEY 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_src_hicolorkey : 24; /* bit[0-23] : layer 0 source high color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_layer0_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_layer0_src_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_DSTLOKEY_UNION
 结构说明  : LAYER0_DSTLOKEY 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_dst_locolorkey : 24; /* bit[0-23] : layer 0 destination low color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_layer0_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_layer0_dst_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_DSTHIKEY_UNION
 结构说明  : LAYER0_DSTHIKEY 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_dst_hicolorkey : 24; /* bit[0-23] : layer 0 destination high color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_layer0_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_layer0_dst_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_PATTERN_UNION
 结构说明  : LAYER0_PATTERN 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_pattern : 32; /* bit[0-31]: layer 0 色彩常值，argb8888格式 */
    } reg;
} SOC_DSS_OV6_LAYER0_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PATTERN_layer0_pattern_START  (0)
#define SOC_DSS_OV6_LAYER0_PATTERN_layer0_pattern_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_ALPHA_UNION
 结构说明  : LAYER0_ALPHA 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_dst_global_alpha : 8;  /* bit[0-7]  : layer 0 destination 全局alpha */
        unsigned int  layer0_fix_mode         : 1;  /* bit[8]    : layer 0 destination pixel alpha 选择
                                                                   0:destination pixel alpha
                                                                   1: source pixel alpha  */
        unsigned int  layer0_dst_pmode        : 1;  /* bit[9]    : layer 0 destination pixel alpha处理记为pmode_alpha
                                                                   0:pixel alpha
                                                                   1:1-pixel alpha */
        unsigned int  layer0_alpha_offdst     : 2;  /* bit[10-11]:  */
        unsigned int  layer0_dst_gmode        : 2;  /* bit[12-13]: layer 0 destination pmode_alpha处理记为gmode_alpha
                                                                   00: pmode_alpha
                                                                   01: pmode_alpha*dst_global_alpha
                                                                   10: dst_global_alpha */
        unsigned int  layer0_dst_amode        : 2;  /* bit[14-15]: layer 0 destination gmode_alpha处理记为amode_alpha
                                                                   00: 0
                                                                   01: 1
                                                                   10: 1-gmode_alpha
                                                                   11: gmode_alpha */
        unsigned int  layer0_src_global_alpha : 8;  /* bit[16-23]: layer 0 source 全局alpha */
        unsigned int  layer0_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer0_src_pmode        : 1;  /* bit[25]   : layer 0 source pixel alpha处理记为pmode_alpha
                                                                   0：pixel alpha
                                                                   1：1-pixel alpha */
        unsigned int  layer0_src_lmode        : 1;  /* bit[26]   : 0: src_global_alpha
                                                                   1: dst pixel alpha */
        unsigned int  layer0_alpha_offsrc     : 1;  /* bit[27]   :  */
        unsigned int  layer0_src_gmode        : 2;  /* bit[28-29]: layer 0 source pmode_alpha处理记为gmode_alpha
                                                                   00: pmode_alpha
                                                                   01: pmode_alpha*src_global_alpha
                                                                   10: src_global_alpha */
        unsigned int  layer0_src_amode        : 2;  /* bit[30-31]: layer 0 source gmode_alpha处理记为amode_alpha
                                                                   00: 0
                                                                   01: 1
                                                                   10: 1-gmode_alpha
                                                                   11: gmode_alpha */
    } reg;
} SOC_DSS_OV6_LAYER0_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offdst_START      (10)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offdst_END        (11)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offsrc_START      (27)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offsrc_END        (27)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_amode_END           (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_CFG_UNION
 结构说明  : LAYER0_CFG 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_enable     : 1;  /* bit[0]    : 0: layer 0 disable
                                                             1: layer 0 enable
                                                             当disable时，当前层的输出来自于当前层的输入 */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  layer0_trop_en    : 1;  /* bit[4]    : 0: transparent function disable
                                                             1: transparent function enable */
        unsigned int  layer0_rop_en     : 1;  /* bit[5]    : 0: alphablend function enable
                                                             1: rop function enable */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  layer0_src_cfg    : 1;  /* bit[8]    : 0: select source from layer0_src_sel
                                                             1: select source from layer0_pattern */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : 保留 */
        unsigned int  reserved_3        : 3;  /* bit[12-14]: 保留 */
        unsigned int  reserved_4        : 1;  /* bit[15]   : 保留 */
        unsigned int  layer0_auto_nosrc : 1;  /* bit[16]   : 0:此层固定需要 
                                                             1:自动判断是否需要此层的source, 此层layer的need信号不再拉高 */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: 保留 */
        unsigned int  layer0_trop_code  : 4;  /* bit[20-23]: [3:0] transparent code */
        unsigned int  layer0_rop_code   : 8;  /* bit[24-31]: [7:0] rop code */
    } reg;
} SOC_DSS_OV6_LAYER0_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_CFG_layer0_enable_START      (0)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_enable_END        (0)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_code_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_PSPOS_UNION
 结构说明  : LAYER0_PSPOS 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : 保留 */
        unsigned int  layer0_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstarty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_PEPOS_UNION
 结构说明  : LAYER0_PEPOS 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : 保留 */
        unsigned int  layer0_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendx_START  (0)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendx_END    (14)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendy_START  (16)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_INFO_ALPHA_UNION
 结构说明  : LAYER0_INFO_ALPHA 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer0_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer0_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer0_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : 保留 */
        unsigned int  layer0_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer0_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER0_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_info_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_UNION
 结构说明  : LAYER0_INFO_SRCCOLOR 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : 保留 */
        unsigned int  layer0_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_ST_INFO_UNION
 结构说明  : LAYER0_ST_INFO 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_stall_info : 32; /* bit[0-31]: 下一帧dss_clear 更新成istall_info值 */
    } reg;
} SOC_DSS_OV6_LAYER0_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_ST_INFO_layer0_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER0_ST_INFO_layer0_stall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER0_IST_INFO_UNION
 结构说明  : LAYER0_IST_INFO 寄存器结构定义。地址偏移量:0x4C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_istall_info : 32; /* bit[0-31]: 当stall_info_en有效，计数一帧期间(ov_dneed=1&&src_drdy=0)周期数。
                                                             在dss_clear有效时清零 */
    } reg;
} SOC_DSS_OV6_LAYER0_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_IST_INFO_layer0_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER0_IST_INFO_layer0_istall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_POS_UNION
 结构说明  : LAYER1_POS 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : 保留 */
        unsigned int  layer1_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_POS_layer1_startx_START  (0)
#define SOC_DSS_OV6_LAYER1_POS_layer1_startx_END    (14)
#define SOC_DSS_OV6_LAYER1_POS_layer1_starty_START  (16)
#define SOC_DSS_OV6_LAYER1_POS_layer1_starty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_SIZE_UNION
 结构说明  : LAYER1_SIZE 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  layer1_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endx_START  (0)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endx_END    (14)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endy_START  (16)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_SRCLOKEY_UNION
 结构说明  : LAYER1_SRCLOKEY 寄存器结构定义。地址偏移量:0x58，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_layer1_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_layer1_src_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_SRCHIKEY_UNION
 结构说明  : LAYER1_SRCHIKEY 寄存器结构定义。地址偏移量:0x5C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_layer1_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_layer1_src_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_DSTLOKEY_UNION
 结构说明  : LAYER1_DSTLOKEY 寄存器结构定义。地址偏移量:0x60，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_layer1_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_layer1_dst_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_DSTHIKEY_UNION
 结构说明  : LAYER1_DSTHIKEY 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_layer1_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_layer1_dst_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_PATTERN_UNION
 结构说明  : LAYER1_PATTERN 寄存器结构定义。地址偏移量:0x68，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PATTERN_layer1_pattern_START  (0)
#define SOC_DSS_OV6_LAYER1_PATTERN_layer1_pattern_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_ALPHA_UNION
 结构说明  : LAYER1_ALPHA 寄存器结构定义。地址偏移量:0x6C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer1_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer1_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer1_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer1_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer1_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer1_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer1_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer1_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer1_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer1_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer1_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer1_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_src_START           (27)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_src_END             (27)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_amode_END           (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_CFG_UNION
 结构说明  : LAYER1_CFG 寄存器结构定义。地址偏移量:0x70，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  layer1_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer1_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  layer1_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : 保留 */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : 保留 */
        unsigned int  layer1_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: 保留 */
        unsigned int  layer1_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer1_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_CFG_layer1_enable_START      (0)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_enable_END        (0)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_code_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_PSPOS_UNION
 结构说明  : LAYER1_PSPOS 寄存器结构定义。地址偏移量:0x74，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : 保留 */
        unsigned int  layer1_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstarty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_PEPOS_UNION
 结构说明  : LAYER1_PEPOS 寄存器结构定义。地址偏移量:0x78，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : 保留 */
        unsigned int  layer1_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendx_START  (0)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendx_END    (14)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendy_START  (16)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_INFO_ALPHA_UNION
 结构说明  : LAYER1_INFO_ALPHA 寄存器结构定义。地址偏移量:0x7C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer1_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer1_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer1_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : 保留 */
        unsigned int  layer1_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer1_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER1_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_info_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_UNION
 结构说明  : LAYER1_INFO_SRCCOLOR 寄存器结构定义。地址偏移量:0x80，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : 保留 */
        unsigned int  layer1_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_ST_INFO_UNION
 结构说明  : LAYER1_ST_INFO 寄存器结构定义。地址偏移量:0x84，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_stall_info : 32; /* bit[0-31]: 下一帧dss_clear 更新成istall_info值 */
    } reg;
} SOC_DSS_OV6_LAYER1_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_ST_INFO_layer1_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER1_ST_INFO_layer1_stall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER1_IST_INFO_UNION
 结构说明  : LAYER1_IST_INFO 寄存器结构定义。地址偏移量:0x88，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_istall_info : 32; /* bit[0-31]: 当stall_info_en有效，计数一帧期间(ov_dneed=1&&src_drdy=0)周期数。
                                                             在dss_clear有效时清零 */
    } reg;
} SOC_DSS_OV6_LAYER1_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_IST_INFO_layer1_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER1_IST_INFO_layer1_istall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_POS_UNION
 结构说明  : LAYER2_POS 寄存器结构定义。地址偏移量:0x8C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : 保留 */
        unsigned int  layer2_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_POS_layer2_startx_START  (0)
#define SOC_DSS_OV6_LAYER2_POS_layer2_startx_END    (14)
#define SOC_DSS_OV6_LAYER2_POS_layer2_starty_START  (16)
#define SOC_DSS_OV6_LAYER2_POS_layer2_starty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_SIZE_UNION
 结构说明  : LAYER2_SIZE 寄存器结构定义。地址偏移量:0x90，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  layer2_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endx_START  (0)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endx_END    (14)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endy_START  (16)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_SRCLOKEY_UNION
 结构说明  : LAYER2_SRCLOKEY 寄存器结构定义。地址偏移量:0x94，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_layer2_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_layer2_src_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_SRCHIKEY_UNION
 结构说明  : LAYER2_SRCHIKEY 寄存器结构定义。地址偏移量:0x98，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_layer2_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_layer2_src_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_DSTLOKEY_UNION
 结构说明  : LAYER2_DSTLOKEY 寄存器结构定义。地址偏移量:0x9C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_layer2_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_layer2_dst_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_DSTHIKEY_UNION
 结构说明  : LAYER2_DSTHIKEY 寄存器结构定义。地址偏移量:0xA0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_layer2_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_layer2_dst_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_PATTERN_UNION
 结构说明  : LAYER2_PATTERN 寄存器结构定义。地址偏移量:0xA4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PATTERN_layer2_pattern_START  (0)
#define SOC_DSS_OV6_LAYER2_PATTERN_layer2_pattern_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_ALPHA_UNION
 结构说明  : LAYER2_ALPHA 寄存器结构定义。地址偏移量:0xA8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer2_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer2_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer2_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer2_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer2_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer2_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer2_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer2_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer2_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer2_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer2_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer2_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_src_START           (27)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_src_END             (27)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_amode_END           (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_CFG_UNION
 结构说明  : LAYER2_CFG 寄存器结构定义。地址偏移量:0xAC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  layer2_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer2_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  layer2_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : 保留 */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : 保留 */
        unsigned int  layer2_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: 保留 */
        unsigned int  layer2_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer2_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_CFG_layer2_enable_START      (0)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_enable_END        (0)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_code_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_PSPOS_UNION
 结构说明  : LAYER2_PSPOS 寄存器结构定义。地址偏移量:0xB0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : 保留 */
        unsigned int  layer2_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstarty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_PEPOS_UNION
 结构说明  : LAYER2_PEPOS 寄存器结构定义。地址偏移量:0xB4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : 保留 */
        unsigned int  layer2_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendx_START  (0)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendx_END    (14)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendy_START  (16)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_INFO_ALPHA_UNION
 结构说明  : LAYER2_INFO_ALPHA 寄存器结构定义。地址偏移量:0xB8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer2_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer2_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer2_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : 保留 */
        unsigned int  layer2_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer2_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER2_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_info_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_UNION
 结构说明  : LAYER2_INFO_SRCCOLOR 寄存器结构定义。地址偏移量:0xBC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : 保留 */
        unsigned int  layer2_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_ST_INFO_UNION
 结构说明  : LAYER2_ST_INFO 寄存器结构定义。地址偏移量:0xC0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_stall_info : 32; /* bit[0-31]: 下一帧dss_clear 更新成istall_info值 */
    } reg;
} SOC_DSS_OV6_LAYER2_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_ST_INFO_layer2_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER2_ST_INFO_layer2_stall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER2_IST_INFO_UNION
 结构说明  : LAYER2_IST_INFO 寄存器结构定义。地址偏移量:0xC4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_istall_info : 32; /* bit[0-31]: 当stall_info_en有效，计数一帧期间(ov_dneed=1&&src_drdy=0)周期数。
                                                             在dss_clear有效时清零 */
    } reg;
} SOC_DSS_OV6_LAYER2_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_IST_INFO_layer2_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER2_IST_INFO_layer2_istall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_POS_UNION
 结构说明  : LAYER3_POS 寄存器结构定义。地址偏移量:0xC8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : 保留 */
        unsigned int  layer3_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_POS_layer3_startx_START  (0)
#define SOC_DSS_OV6_LAYER3_POS_layer3_startx_END    (14)
#define SOC_DSS_OV6_LAYER3_POS_layer3_starty_START  (16)
#define SOC_DSS_OV6_LAYER3_POS_layer3_starty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_SIZE_UNION
 结构说明  : LAYER3_SIZE 寄存器结构定义。地址偏移量:0xCC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  layer3_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endx_START  (0)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endx_END    (14)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endy_START  (16)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_SRCLOKEY_UNION
 结构说明  : LAYER3_SRCLOKEY 寄存器结构定义。地址偏移量:0xD0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_layer3_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_layer3_src_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_SRCHIKEY_UNION
 结构说明  : LAYER3_SRCHIKEY 寄存器结构定义。地址偏移量:0xD4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_layer3_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_layer3_src_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_DSTLOKEY_UNION
 结构说明  : LAYER3_DSTLOKEY 寄存器结构定义。地址偏移量:0xD8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_layer3_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_layer3_dst_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_DSTHIKEY_UNION
 结构说明  : LAYER3_DSTHIKEY 寄存器结构定义。地址偏移量:0xDC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_layer3_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_layer3_dst_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_PATTERN_UNION
 结构说明  : LAYER3_PATTERN 寄存器结构定义。地址偏移量:0xE0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PATTERN_layer3_pattern_START  (0)
#define SOC_DSS_OV6_LAYER3_PATTERN_layer3_pattern_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_ALPHA_UNION
 结构说明  : LAYER3_ALPHA 寄存器结构定义。地址偏移量:0xE4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer3_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer3_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer3_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer3_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer3_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer3_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer3_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer3_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer3_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer3_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer3_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer3_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_src_START           (27)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_src_END             (27)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_amode_END           (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_CFG_UNION
 结构说明  : LAYER3_CFG 寄存器结构定义。地址偏移量:0xE8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  layer3_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer3_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  layer3_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : 保留 */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : 保留 */
        unsigned int  layer3_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: 保留 */
        unsigned int  layer3_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer3_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_CFG_layer3_enable_START      (0)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_enable_END        (0)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_code_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_PSPOS_UNION
 结构说明  : LAYER3_PSPOS 寄存器结构定义。地址偏移量:0xEC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : 保留 */
        unsigned int  layer3_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstarty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_PEPOS_UNION
 结构说明  : LAYER3_PEPOS 寄存器结构定义。地址偏移量:0xF0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : 保留 */
        unsigned int  layer3_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendx_START  (0)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendx_END    (14)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendy_START  (16)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_INFO_ALPHA_UNION
 结构说明  : LAYER3_INFO_ALPHA 寄存器结构定义。地址偏移量:0xF4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer3_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer3_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer3_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : 保留 */
        unsigned int  layer3_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer3_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER3_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_info_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_UNION
 结构说明  : LAYER3_INFO_SRCCOLOR 寄存器结构定义。地址偏移量:0xF8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : 保留 */
        unsigned int  layer3_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_ST_INFO_UNION
 结构说明  : LAYER3_ST_INFO 寄存器结构定义。地址偏移量:0xFC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_stall_info : 32; /* bit[0-31]: 下一帧dss_clear 更新成istall_info值 */
    } reg;
} SOC_DSS_OV6_LAYER3_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_ST_INFO_layer3_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER3_ST_INFO_layer3_stall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER3_IST_INFO_UNION
 结构说明  : LAYER3_IST_INFO 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_istall_info : 32; /* bit[0-31]: 当stall_info_en有效，计数一帧期间(ov_dneed=1&&src_drdy=0)周期数。
                                                             在dss_clear有效时清零 */
    } reg;
} SOC_DSS_OV6_LAYER3_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_IST_INFO_layer3_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER3_IST_INFO_layer3_istall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_POS_UNION
 结构说明  : LAYER4_POS 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : 保留 */
        unsigned int  layer4_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_POS_layer4_startx_START  (0)
#define SOC_DSS_OV6_LAYER4_POS_layer4_startx_END    (14)
#define SOC_DSS_OV6_LAYER4_POS_layer4_starty_START  (16)
#define SOC_DSS_OV6_LAYER4_POS_layer4_starty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_SIZE_UNION
 结构说明  : LAYER4_SIZE 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  layer4_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endx_START  (0)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endx_END    (14)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endy_START  (16)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_SRCLOKEY_UNION
 结构说明  : LAYER4_SRCLOKEY 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_layer4_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_layer4_src_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_SRCHIKEY_UNION
 结构说明  : LAYER4_SRCHIKEY 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_layer4_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_layer4_src_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_DSTLOKEY_UNION
 结构说明  : LAYER4_DSTLOKEY 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_layer4_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_layer4_dst_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_DSTHIKEY_UNION
 结构说明  : LAYER4_DSTHIKEY 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_layer4_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_layer4_dst_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_PATTERN_UNION
 结构说明  : LAYER4_PATTERN 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PATTERN_layer4_pattern_START  (0)
#define SOC_DSS_OV6_LAYER4_PATTERN_layer4_pattern_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_ALPHA_UNION
 结构说明  : LAYER4_ALPHA 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer4_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer4_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer4_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer4_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer4_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer4_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer4_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer4_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer4_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer4_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer4_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer4_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_src_START           (27)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_src_END             (27)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_amode_END           (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_CFG_UNION
 结构说明  : LAYER4_CFG 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  layer4_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer4_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  layer4_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : 保留 */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : 保留 */
        unsigned int  layer4_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: 保留 */
        unsigned int  layer4_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer4_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_CFG_layer4_enable_START      (0)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_enable_END        (0)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_code_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_PSPOS_UNION
 结构说明  : LAYER4_PSPOS 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : 保留 */
        unsigned int  layer4_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstarty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_PEPOS_UNION
 结构说明  : LAYER4_PEPOS 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : 保留 */
        unsigned int  layer4_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendx_START  (0)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendx_END    (14)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendy_START  (16)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_INFO_ALPHA_UNION
 结构说明  : LAYER4_INFO_ALPHA 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer4_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer4_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer4_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : 保留 */
        unsigned int  layer4_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer4_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER4_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_info_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_UNION
 结构说明  : LAYER4_INFO_SRCCOLOR 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : 保留 */
        unsigned int  layer4_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_ST_INFO_UNION
 结构说明  : LAYER4_ST_INFO 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_stall_info : 32; /* bit[0-31]: 下一帧dss_clear 更新成istall_info值 */
    } reg;
} SOC_DSS_OV6_LAYER4_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_ST_INFO_layer4_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER4_ST_INFO_layer4_stall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER4_IST_INFO_UNION
 结构说明  : LAYER4_IST_INFO 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_istall_info : 32; /* bit[0-31]: 当stall_info_en有效，计数一帧期间(ov_dneed=1&&src_drdy=0)周期数。
                                                             在dss_clear有效时清零 */
    } reg;
} SOC_DSS_OV6_LAYER4_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_IST_INFO_layer4_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER4_IST_INFO_layer4_istall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_POS_UNION
 结构说明  : LAYER5_POS 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : 保留 */
        unsigned int  layer5_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_POS_layer5_startx_START  (0)
#define SOC_DSS_OV6_LAYER5_POS_layer5_startx_END    (14)
#define SOC_DSS_OV6_LAYER5_POS_layer5_starty_START  (16)
#define SOC_DSS_OV6_LAYER5_POS_layer5_starty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_SIZE_UNION
 结构说明  : LAYER5_SIZE 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : 保留 */
        unsigned int  layer5_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endx_START  (0)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endx_END    (14)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endy_START  (16)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_SRCLOKEY_UNION
 结构说明  : LAYER5_SRCLOKEY 寄存器结构定义。地址偏移量:0x148，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_layer5_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_layer5_src_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_SRCHIKEY_UNION
 结构说明  : LAYER5_SRCHIKEY 寄存器结构定义。地址偏移量:0x14C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_layer5_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_layer5_src_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_DSTLOKEY_UNION
 结构说明  : LAYER5_DSTLOKEY 寄存器结构定义。地址偏移量:0x150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_layer5_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_layer5_dst_locolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_DSTHIKEY_UNION
 结构说明  : LAYER5_DSTHIKEY 寄存器结构定义。地址偏移量:0x154，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_layer5_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_layer5_dst_hicolorkey_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_PATTERN_UNION
 结构说明  : LAYER5_PATTERN 寄存器结构定义。地址偏移量:0x158，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PATTERN_layer5_pattern_START  (0)
#define SOC_DSS_OV6_LAYER5_PATTERN_layer5_pattern_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_ALPHA_UNION
 结构说明  : LAYER5_ALPHA 寄存器结构定义。地址偏移量:0x15C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer5_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer5_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer5_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer5_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer5_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer5_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer5_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer5_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer5_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer5_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer5_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer5_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_src_START           (27)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_src_END             (27)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_amode_END           (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_CFG_UNION
 结构说明  : LAYER5_CFG 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  layer5_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer5_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : 保留 */
        unsigned int  layer5_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : 保留 */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : 保留 */
        unsigned int  layer5_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: 保留 */
        unsigned int  layer5_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer5_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_CFG_layer5_enable_START      (0)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_enable_END        (0)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_code_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_PSPOS_UNION
 结构说明  : LAYER5_PSPOS 寄存器结构定义。地址偏移量:0x164，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : 保留 */
        unsigned int  layer5_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstarty_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_PEPOS_UNION
 结构说明  : LAYER5_PEPOS 寄存器结构定义。地址偏移量:0x168，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : 保留 */
        unsigned int  layer5_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendx_START  (0)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendx_END    (14)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendy_START  (16)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendy_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_INFO_ALPHA_UNION
 结构说明  : LAYER5_INFO_ALPHA 寄存器结构定义。地址偏移量:0x16C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer5_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer5_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer5_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : 保留 */
        unsigned int  layer5_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer5_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_OV6_LAYER5_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_info_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_UNION
 结构说明  : LAYER5_INFO_SRCCOLOR 寄存器结构定义。地址偏移量:0x170，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : 保留 */
        unsigned int  layer5_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_ST_INFO_UNION
 结构说明  : LAYER5_ST_INFO 寄存器结构定义。地址偏移量:0x174，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_stall_info : 32; /* bit[0-31]: 下一帧dss_clear 更新成istall_info值 */
    } reg;
} SOC_DSS_OV6_LAYER5_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_ST_INFO_layer5_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER5_ST_INFO_layer5_stall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_LAYER5_IST_INFO_UNION
 结构说明  : LAYER5_IST_INFO 寄存器结构定义。地址偏移量:0x178，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_istall_info : 32; /* bit[0-31]: 当stall_info_en有效，计数一帧期间(ov_dneed=1&&src_drdy=0)周期数。
                                                             在dss_clear有效时清零 */
    } reg;
} SOC_DSS_OV6_LAYER5_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_IST_INFO_layer5_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER5_IST_INFO_layer5_istall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_BASE_ST_INFO_UNION
 结构说明  : BASE_ST_INFO 寄存器结构定义。地址偏移量:0x17C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bs_stall_info : 32; /* bit[0-31]: 下一帧dss_clear 更新成istall_info值 */
    } reg;
} SOC_DSS_OV6_BASE_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_BASE_ST_INFO_bs_stall_info_START  (0)
#define SOC_DSS_OV6_BASE_ST_INFO_bs_stall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_BASE_IST_INFO_UNION
 结构说明  : BASE_IST_INFO 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bs_istall_info : 32; /* bit[0-31]: 当stall_info_en有效，计数一帧期间(ov_dneed=1&&src_drdy=0)周期数。
                                                         在dss_clear有效时清零 */
    } reg;
} SOC_DSS_OV6_BASE_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_BASE_IST_INFO_bs_istall_info_START  (0)
#define SOC_DSS_OV6_BASE_IST_INFO_bs_istall_info_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_GATE_CTRL_UNION
 结构说明  : GATE_CTRL 寄存器结构定义。地址偏移量:0x184，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_core_gt    : 2;  /* bit[0-1] : [1]：1'b1 表示，子模块的工作时钟由软件门控 1'b0 表示，子模块的工作时钟由硬件自动控制 [0]：1'b0 表示，工作时钟运行 1'b1 表示，工作时钟关闭 */
        unsigned int  reserved_0    : 2;  /* bit[2-3] : 保留 */
        unsigned int  stall_info_en : 1;  /* bit[4]   : 1:使能ov计数dneed拉高，drdy未拉高的cycle数istall_info. */
        unsigned int  reserved_1    : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_DSS_OV6_GATE_CTRL_UNION;
#endif
#define SOC_DSS_OV6_GATE_CTRL_ov_core_gt_START     (0)
#define SOC_DSS_OV6_GATE_CTRL_ov_core_gt_END       (1)
#define SOC_DSS_OV6_GATE_CTRL_stall_info_en_START  (4)
#define SOC_DSS_OV6_GATE_CTRL_stall_info_en_END    (4)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_OV_RD_SHADOW_SEL_UNION
 结构说明  : OV_RD_SHADOW_SEL 寄存器结构定义。地址偏移量:0x188，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_rd_shadow_sel : 1;  /* bit[0]   : 1:读影子寄存器
                                                           0：读工作寄存器 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_OV6_OV_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ov_rd_shadow_sel_START  (0)
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ov_rd_shadow_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_OV_CLK_SEL_UNION
 结构说明  : OV_CLK_SEL 寄存器结构定义。地址偏移量:0x018C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                     1：表示强制打开时钟。
                                                     0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                     bit31：用于abp和reg模块
                                                     其余位保留 */
    } reg;
} SOC_DSS_OV6_OV_CLK_SEL_UNION;
#endif
#define SOC_DSS_OV6_OV_CLK_SEL_ov_clk_sel_START  (0)
#define SOC_DSS_OV6_OV_CLK_SEL_ov_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_OV_CLK_EN_UNION
 结构说明  : OV_CLK_EN 寄存器结构定义。地址偏移量:0x0190，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                    1：表示软件时钟使能有效，允许硬件开钟
                                                    0：表示软件时钟使能无效，禁止硬件开钟
                                                    保留 */
    } reg;
} SOC_DSS_OV6_OV_CLK_EN_UNION;
#endif
#define SOC_DSS_OV6_OV_CLK_EN_ov_clk_en_START  (0)
#define SOC_DSS_OV6_OV_CLK_EN_ov_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_BLOCK_SIZE_UNION
 结构说明  : BLOCK_SIZE 寄存器结构定义。地址偏移量:0x01A0，初值:0x7FFF0000，宽度:32
 寄存器说明: Block的图像高度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 16; /* bit[0-15] : 保留 */
        unsigned int  block_height : 15; /* bit[16-30]: overlay 分块图像的下边沿相对于画布上沿的坐标值，该坐标从零开始计 */
        unsigned int  reserved_1   : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DSS_OV6_BLOCK_SIZE_UNION;
#endif
#define SOC_DSS_OV6_BLOCK_SIZE_block_height_START  (16)
#define SOC_DSS_OV6_BLOCK_SIZE_block_height_END    (30)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_BLOCK_DBG_UNION
 结构说明  : BLOCK_DBG 寄存器结构定义。地址偏移量:0x01A4，初值:0x00000000，宽度:32
 寄存器说明: 分块可谓可测寄存
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  block_dbg : 32; /* bit[0-31]: bit[0] block_disable
                                                    1'b1 ：不支持分块
                                                    1'b0 ： 支持分块 */
    } reg;
} SOC_DSS_OV6_BLOCK_DBG_UNION;
#endif
#define SOC_DSS_OV6_BLOCK_DBG_block_dbg_START  (0)
#define SOC_DSS_OV6_BLOCK_DBG_block_dbg_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_OV6_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x01A8，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   :  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_OV6_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_OV6_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_OV6_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_ov6_interface.h */
