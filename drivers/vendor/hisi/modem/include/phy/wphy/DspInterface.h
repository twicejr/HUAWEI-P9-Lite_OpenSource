/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : DspInterface.h
  版 本 号   : 初稿
  作    者   : 李霄 46160
  生成日期   : 2008年7月17日
  最近修改   :
  功能描述   : 协议栈与DSP之间的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2008年7月17日
    作    者   : 李霄 46160
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DSPINTERFACE_H__
#define __DSPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "vos.h"

/******************************************************************************
 2 宏定义
******************************************************************************/
#define CPHY_MOD_ID_WCDMA                    0x00
#define CPHY_MOD_ID_GSMGPRS                  0x01
#define CPHY_MOD_ID_MP3_ENCODE               0x10
#define CPHY_MOD_ID_MP3_DECODE               0x11
#define CPHY_MOD_ID_WMA                      0x12
#define CPHY_MOD_ID_AAC                      0x13
#define CPHY_MOD_ID_AMR_EFR_FR               0x14
#define CPHY_MOD_ID_HR                       0x15
#define CPHY_MOD_ID_EFR                      0x16
#define CPHY_MOD_ID_FR                       0x17
#define CPHY_MOD_ID_VOMATE                   0x18

#define CPHY_INFO_NUM_MAX                    12

#define DSP_REG_ACTUAL_ADDR(base, offset)   (((unsigned long)base)+(offset))

#define BIT_N(num)                          ( 0x01L << ( num ) )

#define SHPA_LDF_BUFFER_SIZE                2048

/* unit is K 16bit */
#define ZSP_ITCM_LEN                        192

/* unit is K 16bit */
#define ZSP_DTCM_LEN                        160


/* the real size of mailbox on physical address */
#define PP_MAILBOX_REAL_SIZE                2048

/* the real size of mailbox on physical address */
#define NPP_MAILBOX_REAL_SIZE               1024

#define ZSP_UP_MAILBOX_MAX_SIZE             4096

/******************************************************************************/
/* NMI类型  */
/******************************************************************************/
#define SOC_SC_NMI_INT_LEVEL                        9           /*ARM唤醒DSP中断位*/
#define DSP_NMI_BIT                                 0           /*发起ZSP NMI中断*/

#define ZSP_NMI_INT_TYPE_DRX                        0x02        /* DRX期间使用 */
#define ZSP_NMI_INT_TYPE_LDF                        0x04        /* 记录LDF文件 */
#define ZSP_NMI_INT_TYPE_HALT                       0x08        /* 唤醒DSP，供飞行模式使用 */
#define ZSP_NMI_INT_TYPE_INIT                       0x10        /* 唤醒DSP进行上电初始化 */
#define ZSP_NMI_INT_TYPE_SLAVE                      0x20        /* 处于从模睡眠下唤醒 */

#define ZSP_NMI_INT_LDF_REG1_VALUE                  0x5A5A5A5A
#define ZSP_NMI_INT_LDF_REG2_VALUE                  0xA5A5A5A5

/* ZSP_SLEEP_TYPE_ADDR高16比特取值范围:ZSP睡眠所处场景 */
#define ZSP_SLEEP_INIT                              0x00010000  /* 初时上电所处模式,由ARM初始化完成 */
#define ZSP_SLEEP_DRX                               0x00020000  /* 因DRX而进入睡眠 */
#define ZSP_SLEEP_FLYMODE                           0x00040000  /* 因飞行模式/搜网低功耗而进入睡眠 */
/* ZSP_SLEEP_TYPE_ADDR低16比特取值范围:ZSP进入睡眠所需的唤醒方式 */
#define ZSP_SLEEP_NORMAL                            0x00000000  /* DRX普通睡眠,需要NMI中断唤醒 */
#define ZSP_SLEEP_RESET                             0x00000001  /* DRX经过下电的睡眠,需要解复位唤醒 */

/*保存在ZSP_IPC_HALT_INT_TYPE地址的内容取值*/
#define ZSP_HALT_BACKUP_REG                         0
#define ZSP_HALT_NO_BACKUP_REG                      1
#define ZSP_HALT_INVALID_REG                        0x77
/******************************************************************************/
/* IPC中断分配表 */
/******************************************************************************/
/* ARM->DSP */
#define GHPA_IMI_INT_MASKBIT                        2           /*NPP*/
#define DSP_USB_START_BIT                           3           /*SD卡读写开始*/
#define DSP_USB_STOP_BIT                            4           /*SD卡读写停止*/
#define DSP_ANTEN_EXIST_BIT                         5           /*无天线*/
#define DSP_ANTEN_NOEXIST_BIT                       6           /*有天线*/
#define SHPA_IMI_INT_BIT_PA_TEMP_BIT                BIT_N(12)   /*下发PA温度*/
#define BBP_MASTER_READY_BIT                        13          /*通知DSP，BBP MASTER允许睡眠*/
#define SHPA_IMI_INT_MASKBIT                        14          /*加载DSP*/
#define SHPA_HALT_IMI_INT_MASKBIT                   15          /*通知DSP进入HALT*/

/* DSP->ARM */
#define SHPA_IMI_INT_BIT_UPA_STATUS_IND_BIT         BIT_N(1)    /*W UPA要数中断*/
#define GHPA_IMI_INT_BIT_GHPA_NPP_BIT               BIT_N(2)    /*NPP*/
#define SHPA_IMI_INT_BIT_DDR_BEGIN_BIT              BIT_N(3)    /*DSP激活ARM DDR*/
#define SHPA_IMI_INT_BIT_DDR_END_BIT                BIT_N(4)    /*允许ARM睡眠*/
#define SHPA_IMI_INT_BIT_R99_BIT                    BIT_N(5)    /*读取W 信令面邮箱数据*/
#define SHPA_IMI_INT_BIT_PP_HALT_BIT                BIT_N(6)    /*G HALT中断，并且PP邮箱有数据*/
#define SHPA_IMI_INT_BIT_MAC_HALT_BIT               BIT_N(7)	/*数据面邮箱有数据*/
#define SHPA_IMI_INT_BIT_R99_HALT_BIT               BIT_N(8)    /*W HALT中断，并且信令面邮箱有数据*/
#define SHPA_IMI_INT_BIT_RFA_CONNECT_BIT            BIT_N(9)    /*DSP进入连接态*/
#define GHPA_IMI_INT_BIT_FORCE_WAKE_BIT             BIT_N(10)   /*GDSP使用了此bit位*/
#define SHPA_IMI_INT_BIT_RFA_MONITOR_BIT            BIT_N(11)   /*DSP进入IDLE态*/
#define SHPA_IMI_INT_BIT_SHPA_ACTIVE_BIT            BIT_N(12)   /*解复位DSP回复*/
#define SHPA_IMI_INT_BIT_SLEEP_HALT_BIT             BIT_N(13)   /*W HALT中断*/
#define SHPA_IMI_INT_BIT_SHPA_SWAP_BIT              BIT_N(14)   /*加载DSP回复*/
#define GHPA_IMI_INT_BIT_SLEEP_HALT_BIT             BIT_N(15)   /*G HALT中断*/
#define SHPA_IMI_INT_BIT_LOW_POWER_HALT_BIT         BIT_N(16)   /* 从模通知ARM,DSP进入睡眠 */
#define SHPA_IMI_INT_BIT_WAKE_LTE_BIT               BIT_N(17)   /* 从模通知ARM,唤醒LDSP */
#define SHPA_IMI_INT_BIT_WAKE_TD_BIT                BIT_N(18)   /* 从模通知ARM,唤醒TDSP */
#define SHPA_IMI_INT_BIT_DPA_RPT_BIT                BIT_N(19)   /* DPA上报中断给TTF */




/****************************************************************************
 *                   ZSP使用AHB邮箱中的地址的划分                           *
 *                                                                          *
 ****************************************************************************/

/* 说明 1:下图中地址单位为byte
        2:AHB邮箱总的空间大小为32Kbyte

              ----------------------------------- <---------- 0x0000
              | GSM DRX 交互(和PS有接口相关)    |
               ---------------------------------  <---------- 0x0020
              | 临终遗言(和PS有接口相关)        |
              |                                 |
               ---------------------------------  <---------- 0x01B0
              | NV上移、开机信息修改代码,ARM    |
              | 交互地址                        |
               ---------------------------------  <---------- 0x01D0
              |                                 |
              |         AHB信令下发邮箱         |
              |                                 |
               ---------------------------------  <---------- 0x2710
              |                                 |
              |         R99数据面邮箱           |
              |        (和PS有接口相关)         |
              |                                 |
               ---------------------------------  <---------- 0x3AD0
              |                                 |
              |          DRX 流程相关           |
               ---------------------------------  <---------- 0x3BFC
              |                                 |
              |         AHB信令上发邮箱         |
              |                                 |
              |                                 |
               ---------------------------------  <---------- 0x7D70
              |     DSP共享空间档刂上报         |
              |     (WDSP和PS有接口相关)        |
               ---------------------------------  <---------- 0x7E00
              |     (GDSP和PS有接口相关)        |
               ---------------------------------  <---------- 0x7F00
              |   R5译码数据DMA级联地址         |
               ---------------------------------  <---------- 0x7F20
              |   R5控制邮箱(和PS有接口相关)    |
               ---------------------------------  <---------- 0x7F3C
              |   APC表DMA搬移级联地址          |
               ---------------------------------  <---------- 0x7F8C
              |                                 |
              |                                 |
              |   AHB邮箱DMA搬移级联地址        |
              |                                 |
              |                                 |
              ----------------------------------- <---------- 0x8000  */

/*=========================== 临终遗言使用相关地址 ===========================*/
/* NMI INT Type: 0x01 -- wakeup WDSP;0x02 -- wakeup GDSP;0x04 -- LDF function */

 /* NMI中断功能判别寄存器:0x01-唤醒W,0x02-唤醒G,0x04-复位DSP */
#define ZSP_NMI_INT_TYPE_REG            DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0020)

/* NMI中断状态判别寄存器1 */
#define ZSP_NMI_INT_LDF_REG1            DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0024)

/* NMI中断状态判别寄存器2 */
#define ZSP_NMI_INT_LDF_REG2            DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0028)

/*0x0: 初始化寄存器, 0x1: 不初始化寄存器*/
#define ZSP_IPC_HALT_INT_TYPE           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x002c)

/* 1)DSP睡眠类型地址定义,取值范围参见ZSP_SLEEP_*的宏定义 */
/* 2)高16bit表示睡眠场景,包括ZSP_SLEEP_INIT,ZSP_SLEEP_DRX,ZSP_SLEEP_FLYMODE;
     低16bit表示ZSP睡眠的方式,包括ZSP_SLEEP_NORMAL,ZSP_SLEEP_RESET */
/* 3)首次上电由OAM初始化成(ZSP_SLEEP_INIT|ZSP_SLEEP_NORMAL) */
#define ZSP_SLEEP_TYPE_ADDR             DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0030)

/*保留*/
#define ZSP_NMI_INT_LDF_REGRSV2         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x005C)



/*============================AHB OM邮箱 保护地址====================*/
#define ZSP_OM_MAIL_BOX_LOCK_ADDR       DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x01C8)


/*=================飞行模式和搜网低功耗状态告知ARM是否已经睡眠================*/
#define ZSP_IPC_HALT_STATUS_ADDR        DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x01CC)


/*============================AHB信令下发邮箱地址:ARM->DSP====================*/

/* ARM下发信息到WDSP 下行邮箱大小 */
#define R99_DL_MAILBOX_REAL_SIZE        (9536)

/* AHB邮箱接口*/
#define R99_ARM2DSP_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x01D0)

#define NPP_UL_MAILBOX_REAL_SIZE        4096
#define NPP_DSP2ARM_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x1400)

#define NPP_DL_MAILBOX_REAL_SIZE        4096
#define NPP_ARM2DSP_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x0400)


/*======================R99数据面地址(WPHY-TTF接口)========================*/

/* R99用户面邮箱基地址,R99用户面邮箱位于AHB RAM上 */
#define ARM_DSP_R99_DATA_BASE_ADDR      DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x2710)


/*=========================== 临终遗言(保存DRX相关信息)=======================*/
#define ZSP_DRX_INFO_BEGIN_ADDR         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x3AD0)
#define ZSP_DRX_INFO_END_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x3BFC)


/*============================AHB信令上报邮箱地址:DSP->ARM====================*/

/* DSP 上报信息到 ARM 上行邮箱大小 */
#define R99_UL_MAILBOX_REAL_SIZE        (16752)

/* AHB邮箱接口*/
#define R99_DSP2ARM_BASE_ADDR           DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x3C00)

#define PP_DL_MAILBOX_REAL_SIZE          4096
#define PP_ARM2DSP_BASE_ADDR             DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x4000)

#define PP_UL_MAILBOX_REAL_SIZE          8192
#define PP_DSP2ARM_BASE_ADDR             DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x5000)

/*===========================DSP内部变量起始地址上报ram========================*/

/* R5用户面控制信息基地址,R5用户面控制信息部分位于AHB邮箱上 */
#define ARM_DSP_R5_R7_SHARE_MEM_HEAD_CTRL_BASE_ADDR         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x7F20)

/* R6用户面控制信息基地址,R6用户面控制信息部分位于ZSP TCM内 */
/* 此地址用于查询R6用户面控制信息基地址, 因为FPGA上UPA PHY-MAC共享地址获取方式改变而引入 */
#define ARM_DSP_R6_SHARE_MEM_CTRL_INQUIRE_ADDR      DSP_REG_ACTUAL_ADDR(ZSP_DTCM_BASE_ADDR, 0x0000)


/* R7用户面控制信息基地址,R5用户面控制信息部分位于AHB邮箱上 */
#define ARM_DSP_R5_R7_SHARE_MEM_DATA_CTRL_BASE_ADDR         DSP_REG_ACTUAL_ADDR(AHB_BASE_ADDR, 0x7F30)


/* AHB邮箱DMA搬移级联地址  */
#define AHB_MAIL_DMA_LLI_PARA_LOW_ADDR          ((PHY_UINT32)0x7F90)

/* AHB邮箱DMA搬移级联地址,G模使用, 0x7000 -  0x7500 为DMA级联地址，每个DMA通道 40*32bit */
#define UCOM_AHB_DMA_LLI_START_ADDR             ((PHY_UINT32)0x2800)

/****************************************************************************
 *                   ZSP ITCM共享缓存的划分                                 *
 *                                                                          *
 ****************************************************************************/


/****************************************************************************
 *                   ZSP DTCM共享缓存的划分                                 *
 *                                                                          *
 ****************************************************************************/


/*===================================APM邮箱==================================*/


#define DSP_SHARE_MEMORY_SINGLE_SPACE       0x2A


/* APM邮箱加载部分，DSP可读ARM不可写 */
#define APM_DSP_READABLE       	            (0x7788)
/* APM邮箱加载部分，DSP不可读ARM可写 */
#define APM_ARM_WRITABLE                    (0x99AA)
/*==================================GDSP原语邮箱==============================*/

/*OM mailbox physical address*/
#define OM_MAILBOX_BASE_ADDR                DSP_REG_ACTUAL_ADDR(ZSP_DTCM_BASE_ADDR, 0x6c30)





/*================================WPHY临终遗言相关地址========================*/

/* 0x1210 ~ 0x121F: total 16 byte */
#define ZSP_G_INT_REG                       DSP_REG_ACTUAL_ADDR(GBBP_BASE_ADDR,0x1210) /*0x20211210
 */

/* 0x0000 ~ 0x003F: total 64 byte */
#define ZSP_W_INT_REG                       DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x0000) /*0x20200000
 */

/* 0x0000 ~ 0x1FFFF: total (128*1024) byte */
#define BBP_ALL_REG                         DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x0000) /*0x20200000
 */

/* 0x1100 ~ 0x112F: total 48 byte */
#define ZSP_W_DRX_REG1                      DSP_REG_ACTUAL_ADDR(WDRX_BBP_BASE_ADDR,0x1100) /*x20221100
 */

/* 0x1170 ~ 0x1177: total 8 byte */
#define ZSP_W_DRX_REG2                      DSP_REG_ACTUAL_ADDR(WDRX_BBP_BASE_ADDR,0x1170) /*0x20221170
 */

/* 0x1160 ~ 0x1163: total 4 byte */
#define ZSP_W_DRX_REG3                      DSP_REG_ACTUAL_ADDR(WDRX_BBP_BASE_ADDR,0x1160) /*0x20221160
 */

/* 0x10A8 ~ 0x10AB: tatal 4 byte */
#define ZSP_W_SYS_CLK_CTRL_REG1             DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x10a8) /*0x202010A8
 */

/* 0x8238 ~ 0x823B: tatal 4 byte */
#define ZSP_W_SYS_CLK_CTRL_REG2             DSP_REG_ACTUAL_ADDR(WBBP_BASE_ADDR,0x8238) /*0x20208238
 */

/* 0x01C0 ~ 0x01D3: total 20 byte */
#define ZSP_DMA_CHANNEL6_STATUS_REG         DSP_REG_ACTUAL_ADDR(DMAC_BASE_ADDR,0x01c0) /*0x203801C0
 */


/*****************************************************************************
 *                                                                           *
 *                 ZSP LDF 临终遗言相关地址和数据长度(Byte)                  *
 *                                                                           *
 *****************************************************************************/

/* SECT 00 -- 数据来源:文件头标志和LDF生成时间;长度:4 Byte + 4 byte */
#define ZSP_LDF_FILE_CREATE_INFO_LEN        ( 8 )

/* SECT 01 -- 数据来源:ld文件APMDOWNMBOX段LOAD信息;长度:80 Byte */
#define ZSP_LDF_APM_LOAD_INFO_ADDR          ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_APM_LOAD_INFO_LEN           ( 80 )

/* SECT 02 -- 数据来源:ld文件COMMON_DEBUG_DATA段;长度:2.5K Byte */
#define ZSP_LDF_COM_DEBUG_DATA_ADDR         ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x3F400 ) )
#define ZSP_LDF_COM_DEBUG_DATA_LEN          ( 2560 )

/* SECT 03 -- 数据来源:ld文件TEST段;长度:0.5K Byte */
#define ZSP_LDF_TEST_DATA_ADDR              ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x3FE00 ) )
#define ZSP_LDF_TEST_DATA_LEN               ( 512 )

/* SECT 04 -- 数据来源:ld文件APMDOWNMBOX段;长度:1K Byte */
#define ZSP_LDF_APM_DOWN_BOX_ADDR           ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_APM_DOWN_BOX_LEN            ( 1024 )

/* SECT 05 -- 数据来源:ld文件OVERLAY_DATA_PHY段;长度:1K Byte */
#define ZSP_LDF_OVERLAY_DATA_ADDR           ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x1F400 ) )
#define ZSP_LDF_OVERLAY_DATA_LEN            ( 1024 )

/* SECT 06 -- 数据来源:BBP所有寄存器;长度:128K Byte */
#define ZSP_LDF_BBP_REG_ADDR                ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_BBP_REG_LEN                 ( 128*1024 )

/* SECT 07 -- 数据来源:BBP G/W模INT中断相关寄存器;长度:16 Byte + 64 Byte */
#define ZSP_LDF_G_INT_REG_ADDR              ( DSP_REG_ACTUAL_ADDR( GBBP_BASE_ADDR, 0x1210 ) )
#define ZSP_LDF_G_INT_REG_LEN               ( 16 )
#define ZSP_LDF_W_INT_REG_ADDR              ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_W_INT_REG_LEN               ( 64 )

/* SECT 08 -- 等同SECT 02 */
/* SECT 09 -- 等同SECT 03 */
/* SECT 10 -- 等同SECT 04 */
/* SECT 11 -- 等同SECT 05 */
/* SECT 12 -- 等同SECT 06 */

/* SECT 13 -- 数据来源:WBBP DRX相关;长度:256 Byte + 4 Byte + 4 Byte */
#define ZSP_LDF_W_DRX_REG_ADDR              ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x21100 ) )
#define ZSP_LDF_W_DRX_REG_LEN               ( 256 )
#define ZSP_LDF_W_SYS_CLK_REG1_ADDR         ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x10A8 ) )
#define ZSP_LDF_W_SYS_CLK_REG1_LEN          ( 4 )
#define ZSP_LDF_W_SYS_CLK_REG2_ADDR         ( DSP_REG_ACTUAL_ADDR( WBBP_BASE_ADDR, 0x8238 ) )
#define ZSP_LDF_W_SYS_CLK_REG2_LEN          ( 4 )

/* SECT 14 -- 数据来源:ld文件ITCM段;长度:512K Byte */
#define ZSP_LDF_ITCM_DATA_ADDR              ( DSP_REG_ACTUAL_ADDR( ZSP_ITCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_ITCM_DATA_LEN               ( 512*1024 )

/* SECT 15 -- 数据来源:ld文件DTCM段;长度:272K Byte */
#define ZSP_LDF_DTCM_DATA_ADDR              ( DSP_REG_ACTUAL_ADDR( ZSP_DTCM_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_DTCM_DATA_LEN               ( 272*1024 )

/* SECT 16 -- 数据来源:DL AHB邮箱数据;长度:0x00002510 Byte,实际获取:10240 Byte */
#define ZSP_LDF_DL_AHB_DATA_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x1d8 ) )
#define ZSP_LDF_DL_AHB_DATA_LEN             ( 10240 )

/* SECT 17 -- 数据来源:DL AHB邮箱数据;长度:0x00004148 Byte,实际获取:18432 Byte */
#define ZSP_LDF_UL_AHB_DATA_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x3c00 ) )
#define ZSP_LDF_UL_AHB_DATA_LEN             ( 18432 )

/* SECT 18 -- 数据来源:DL/UL AHB邮箱头;长度:40 Byte + 40 Byte */
#define ZSP_LDF_DL_AHB_HEAD_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x1d8 ) )
#define ZSP_LDF_DL_AHB_HEAD_LEN             ( 40 )
#define ZSP_LDF_UL_AHB_HEAD_ADDR            ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x3c00 ) )
#define ZSP_LDF_UL_AHB_HEAD_LEN             ( 40 )

/* SECT 19 -- 数据来源:Dma6和ABB数据;长度:20 Byte + 124 Byte */
#define ZSP_LDF_DMA_CHANNEL6_ADDR           ( DSP_REG_ACTUAL_ADDR( DMAC_BASE_ADDR, 0x1C0 ) )
#define ZSP_LDF_DMA_CHANNEL6_LEN            ( 20 )
#define ZSP_LDF_ABB_REG_LEN                 ( 31*4 )

/* SECT 20 -- 数据来源:DRX相关所有寄存器;长度:284 Byte */
#define ZSP_LDF_DRX_DATA_ADDR               ( ZSP_DRX_INFO_BEGIN_ADDR )
#define ZSP_LDF_DRX_DATA_LEN                ( ZSP_DRX_INFO_END_ADDR - ZSP_DRX_INFO_BEGIN_ADDR )

/* SECT 21 -- 数据来源:AHB地址0~0x1d8保存的相关信息;长度:472 Byte */
#define ZSP_LDF_AHB_DATA_ADDR               ( DSP_REG_ACTUAL_ADDR( AHB_BASE_ADDR, 0x00 ) )
#define ZSP_LDF_AHB_DATA_LEN                ( 0x01D8 )

/* SECT 22 -- 数据来源:ARM保存相关的DRX信息;长度:** Byte */
/* SECT 23 -- 数据来源:文件尾标志和LDF生成时间;长度:4 Byte + 4 byte */



/*****************************************************************************
                            ZSP LDF临终遗言TABLE定义

 SECT 00 -- 来源:文件头标志和LDF生成时间;       ADDR:----------     LEN:8 Byte

 SECT 01 -- 来源:ld文件APMDOWNMBOX段LOAD信息;   ADDR:0x20000000     LEN:80 Byte
 SECT 02 -- 来源:ld文件OMMON_DEBUG_DATA段;      ADDR:0x2013F400     LEN:2.5K Byte
 SECT 03 -- 来源:ld文件TEST段;                  ADDR:0x2013FE00     LEN:0.5K Byte
 SECT 04 -- 来源:ld文件APMDOWNMBOX段;           ADDR:0x20100000     LEN:1K Byte
 SECT 05 -- 来源:ld文件VERLAY_DATA_PHY段;       ADDR:0x2011F400     LEN:1K Byte
 SECT 06 -- 来源:BBP所有寄存器;                 ADDR:0x20200000     LEN:128K Byte
 SECT 07 -- 来源:BBP G模INT中断寄存器;          ADDR:0x20211210     LEN:16 Byte
            来源:BBP W模INT中断寄存器;          ADDR:0x20200000     LEN:64 Byte
 SECT 08 -- 来源:ld文件OMMON_DEBUG_DATA段;      ADDR:0x2013F400     LEN:2.5K Byte
 SECT 09 -- 来源:ld文件TEST段;                  ADDR:0x2013FE00     LEN:0.5K Byte
 SECT 10 -- 来源:ld文件APMDOWNMBOX段;           ADDR:0x20100000     LEN:1K Byte
 SECT 11 -- 来源:ld文件VERLAY_DATA_PHY段;       ADDR:0x2011F400     LEN:1K Byte
 SECT 12 -- 来源:BBP所有寄存器;                 ADDR:0x20200000     LEN:128K Byte
 SECT 13 -- 来源:WBBP DRX相关;                  ADDR:0x20221100     LEN:256 Bytes
            来源:W_SYS_CLK1                     ADDR:0x202010A8     LEN:4 Byte
            来源:W_SYS_CLK2                     ADDR:0x20208238     LEN:4 Byte
 SECT 14 -- 来源:ld文件中ITCM段;                ADDR:0x20000000     LEN:512K Byte
 SECT 15 -- 来源:ld文件中DTCM段;                ADDR:0x20100000     LEN:272K Byte
 SECT 16 -- 来源:DL AHB邮箱;                    ADDR:0x203001D8     LEN:10K Byte
 SECT 17 -- 来源:UL AHB邮箱;                    ADDR:0x20303C00     LEN:18K Byte
 SECT 18 -- 来源:DL AHB邮箱头;                  ADDR:0x203001D8     LEN:40 Byte
            来源:DL AHB邮箱头;                  ADDR:0x20303C00     LEN:40 Byte
 SECT 19 -- 来源:Dma6寄存器;                    ADDR:0x203801C0     LEN:20 Byte
 SECT 20 -- 来源:DRX相关寄存器;                 ADDR:0x20303AD0     LEN:300 Byte
 SECT 21 -- 来源:AHB 0~0x1d8信息;               ADDR:0x20300000     LEN:472 Byte

 SECT 22 -- 来源:ARM保存DRX信息;                ADDR:----------     LEN:** Byte
 SECT 23 -- 来源:LDF生成时间和文件尾标志;       ADDR:----------     LEN:8 Byte

 *****************************************************************************/
#define ZSP_LDF_DUMP_DATA_INFO_TABLE    \
ZSP_LDF_DUMP_DATA_INFO_STRU     g_astZspLdfDumpDataTable[] =  \
{   \
    {   ZSP_LDF_APM_LOAD_INFO_ADDR,     ZSP_LDF_APM_LOAD_INFO_LEN   },   \
    {   ZSP_LDF_COM_DEBUG_DATA_ADDR,    ZSP_LDF_COM_DEBUG_DATA_LEN  },   \
    {   ZSP_LDF_TEST_DATA_ADDR,         ZSP_LDF_TEST_DATA_LEN       },   \
    {   ZSP_LDF_APM_DOWN_BOX_ADDR,      ZSP_LDF_APM_DOWN_BOX_LEN    },   \
    {   ZSP_LDF_OVERLAY_DATA_ADDR,      ZSP_LDF_OVERLAY_DATA_LEN    },   \
    {   ZSP_LDF_BBP_REG_ADDR,           ZSP_LDF_BBP_REG_LEN         },   \
    {   ZSP_LDF_G_INT_REG_ADDR,         ZSP_LDF_G_INT_REG_LEN       },   \
    {   ZSP_LDF_W_INT_REG_ADDR,         ZSP_LDF_W_INT_REG_LEN       },   \
    {   ZSP_LDF_COM_DEBUG_DATA_ADDR,    ZSP_LDF_COM_DEBUG_DATA_LEN  },   \
    {   ZSP_LDF_TEST_DATA_ADDR,         ZSP_LDF_TEST_DATA_LEN       },   \
    {   ZSP_LDF_APM_DOWN_BOX_ADDR,      ZSP_LDF_APM_DOWN_BOX_LEN    },   \
    {   ZSP_LDF_OVERLAY_DATA_ADDR,      ZSP_LDF_OVERLAY_DATA_LEN    },   \
    {   ZSP_LDF_BBP_REG_ADDR,           ZSP_LDF_BBP_REG_LEN         },   \
    {   ZSP_LDF_W_DRX_REG_ADDR,         ZSP_LDF_W_DRX_REG_LEN       },   \
    {   ZSP_LDF_W_SYS_CLK_REG1_ADDR,    ZSP_LDF_W_SYS_CLK_REG1_LEN  },   \
    {   ZSP_LDF_W_SYS_CLK_REG2_ADDR,    ZSP_LDF_W_SYS_CLK_REG2_LEN  },   \
    {   ZSP_LDF_ITCM_DATA_ADDR,         ZSP_LDF_ITCM_DATA_LEN       },   \
    {   ZSP_LDF_DTCM_DATA_ADDR,         ZSP_LDF_DTCM_DATA_LEN       },   \
    {   ZSP_LDF_DL_AHB_DATA_ADDR,       ZSP_LDF_DL_AHB_DATA_LEN     },   \
    {   ZSP_LDF_UL_AHB_DATA_ADDR,       ZSP_LDF_UL_AHB_DATA_LEN     },   \
    {   ZSP_LDF_DL_AHB_HEAD_ADDR,       ZSP_LDF_DL_AHB_HEAD_LEN     },   \
    {   ZSP_LDF_UL_AHB_HEAD_ADDR,       ZSP_LDF_UL_AHB_HEAD_LEN     },   \
    {   ZSP_LDF_DMA_CHANNEL6_ADDR,      ZSP_LDF_DMA_CHANNEL6_LEN    },   \
    {   ZSP_LDF_DRX_DATA_ADDR,          ZSP_LDF_DRX_DATA_LEN        },   \
    {   ZSP_LDF_AHB_DATA_ADDR,          ZSP_LDF_AHB_DATA_LEN        }    \
}


#define ZSP_LDF_DUMP_SECT_HALT_NO       ( 8 )


/* 获取LDF数据表的首地址 */

/* 获取LDF数据表长度 */


/*****************************************************************************
 *                           ZSP LDF临终遗言定义END                          *
 *****************************************************************************/










/****************************************************************************
 *                  WCDMA协议栈与WPHY之间共享内存接口地址描述(DDR)          *
 *                                                                          *
 ****************************************************************************/

/* HSDPA ARM与DSP间SRAM接口起始地址,FPGA平台提供的接口SRAM的地址暂时分配为0x63f00000~0x64000000，共1M空间
   协议栈与DSP使用的为0x63f00000开始的32KB空间 */

/* HSDA+ ARM与DSP间SDRAM接口起始地址,共5472*12=65,664(Byte)空间 */



#define DSP_DYMAIC_SEG_SIZE                         ( 63 )                      /* DSP动态段大小 */

#define PHY_OM_SAR_MASK_ANTSTATE                    (0x1)
#define PHY_OM_SAR_MASK_REDUCTION                   (0x2)


/******************************************************************************
  3 结构定义
******************************************************************************/

/*****************************************************************************
 结构名    : ZSP_LDF_DUMP_DATA_INFO_STRU
 结构说明  : ZSP LDF数据保存信息的首地址和数据长度结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulDataAddr;                                     /* 数据的首地址 */
    VOS_UINT32                  ulDataLen;                                      /* 数据的长度 */
}ZSP_LDF_DUMP_DATA_INFO_STRU;


typedef struct
{
    VOS_UINT16                  uhwRxVer;
    VOS_UINT16                  uhwTxVer;
    VOS_UINT16                  uhwRxEcVer;
    VOS_UINT16                  uhwTxEcVer;
    VOS_UINT16                  uhwverlogmsg;
    VOS_UINT16                  uhwResever;

} CPHY_RF_VER_INFO_STRU;

typedef struct
{
    VOS_UINT16                  uhwReslutinfo;             /*DSP初始化结果*/
    VOS_UINT16                  ulResever1;

} CPHY_BOOT_RESULT_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulProtect1;
    VOS_UINT32                  ulArmWriteSlice1;
    VOS_UINT32                  ulDspReadSlice1;
    VOS_UINT32                  ulDspMakeVersion;
    VOS_UINT32                  ulDspMakeDate;
    VOS_UINT32                  ulDspMakeTime;
    VOS_UINT32                  ulResever1[2];

    VOS_UINT32                  ulProtect2;
    VOS_UINT32                  ulArmReadSlice2;
    VOS_UINT32                  ulDspWriteSlice2;
    VOS_UINT32                  ulResever2[7];

    VOS_UINT32                  ulProtect3;
    VOS_UINT32                  ulArmWriteSlice3;
    VOS_UINT32                  ulDspReadSlice3;
    VOS_UINT32                  ulResever3[5];

    VOS_UINT32                  ulProtect4;
    VOS_UINT32                  ulArmWriteSlice4;
    VOS_UINT32                  ulDspReadSlice4;
    VOS_UINT32                  ulResever4[5];

    VOS_UINT32                  ulProtect5;
    CPHY_RF_VER_INFO_STRU       stDspVersionInfo;
    VOS_UINT32                  ulArmWriteSlice5;
    VOS_UINT32                  ulDspReadSlice5;
    VOS_UINT32                  ulResever5[5];

    VOS_UINT32                  ulProtect6;
    VOS_UINT32                  ulWphyVerAddr;
    VOS_UINT32                  ulResever6[2];
    VOS_UINT32                  ulHsupaShareCtrlAddr;
    VOS_UINT32                  ulDspModeRptAddr;
    VOS_UINT32                  ulHsupaRptAddr;
    VOS_UINT32                  ulHsupaTtiAddr;
    VOS_UINT32                  ulWReserveRptAddr2;
    VOS_UINT32                  ulWReserveRptAddr3;
    VOS_UINT32                  ulWReserveRptAddr4;
    VOS_UINT32                  ulCpcDrxRptAddr;

    VOS_UINT32                  ulGMsgRptAddr;
    VOS_UINT32                  ulGMsgRptLenAddr;
    VOS_UINT32                  ulGComRptAddr;
    VOS_UINT32                  ulGComRptLenAddr;
    VOS_UINT32                  ulGPsRptAddr;
    VOS_UINT32                  ulGPsRptLenAddr;
    VOS_UINT32                  ulGCsRptAddr;
    VOS_UINT32                  ulGCsRptLenAddr;
    VOS_UINT32                  ulGMailRptAddr;
    VOS_UINT32                  ulGMailptLenAddr;
    VOS_UINT32                  ulGCchRptAddr;
    VOS_UINT32                  ulGCchRptLenAddr;
    VOS_UINT32                  ulGNcellRptAddr;
    VOS_UINT32                  ulGNcellRptLenAddr;
    VOS_UINT32                  ulGDrxRptAddr;
    VOS_UINT32                  ulGDrxRptLenAddr;
    VOS_UINT32                  ulGPwcRptAddr;
    VOS_UINT32                  ulGPwcRptLenAddr;
    VOS_UINT32                  ulGCalRptAddr;
    VOS_UINT32                  ulGCalRptLenAddr;
    VOS_UINT32                  ulGMeasRptAddr;
    VOS_UINT32                  ulGMeasRptLenAddr;
    VOS_UINT32                  ulGDrvRptAddr;
    VOS_UINT32                  ulGDrvRptLenAddr;
    VOS_UINT32                  ulRfFrontEndRptAddr;        /* 前端可维可测，每帧打印 */
    VOS_UINT32                  ulRfFrontEndRptLenAddr;     /* 前端可维可测长度 */
}CPHY_IPC_INFO_STRU;


/*****************************************************************************
 结构名    : CPHY_BOOT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP上电时OAM需要往DSP的.dsp_oam_common_data段写如下结构的数据，起始地址由DRV解析ZSP bin件后传给OAM
*****************************************************************************/
typedef struct CPHY_BOOT_INFO_STRU
{
    VOS_UINT32                          ulProtect1;             /*保护字1*/
    VOS_UINT32                          ulValidFlag1;           /*OAM 在完成数据的填写后置有效标记*/
    VOS_UINT32                          ulArmWriteSlice;
    VOS_UINT32                          ulDspReadyFlag;
    VOS_UINT32                          ulDspReadSlice;
    VOS_UINT32                          ulUmtsBandBitMap;        /* 频段有效位图 */
    VOS_UINT32                          ulValidFlag2;            /*保护字2*/
    VOS_UINT32                          ulCQIAddr;               /*NV CQI地址*/
    VOS_UINT32                          ulAPTAddr;               /* APT表首地址 */
    VOS_UINT32                          ulETAddr;                /* ET地址*/
    VOS_UINT32                          ulValidFlag3;            /*保护字3*/
    VOS_UINT32                          aulApmModuleAddrInfo[DSP_DYMAIC_SEG_SIZE];
    VOS_UINT32                          ulValidFlag4;            /*保护字4*/
    VOS_UINT16                          ausPhyOmNvTable[8];      /* 存储NV table，OAM从本起始地址开始写NV项*/
}CPHY_BOOT_INFO_STRU;




/* 和层二的交互邮箱的长度*/
#define COM_GPRS_DATA_LEN               (0xc00-2)
typedef struct /*和层二的交互邮箱的结构定义*/
{
    VOS_UINT16      uhwAhbWrIndex;                           /* AHB邮箱写指针偏移地址 */
    VOS_UINT16      uhwAhbRdIndex;                           /* AHB邮箱读指针偏移地址 */
    VOS_UINT16      uhwMutex;                                /* 和GRM修改接口,增加的互斥标志 */
    VOS_UINT16      uhwRsv;                                  /* 和GRM修改接口,保留 */
    VOS_UINT16      auhwDataBuf[COM_GPRS_DATA_LEN];          /* 指向AHB邮箱首块缓存的指针*/
}GPRS_DATA_BUF;
/******************************************************************************
  4 枚举定义
******************************************************************************/


/******************************************************************************
  5 全局变量声明
******************************************************************************/


/******************************************************************************
  6 消息头定义
******************************************************************************/


/******************************************************************************
  7 消息定义
******************************************************************************/


/******************************************************************************
  8 结构定义
******************************************************************************/
extern VOS_UINT32 APM_OamClearSdtLinkStatus( VOS_VOID );
extern VOS_VOID UCOM_SetTemparatureAddr( VOS_UINT32 uwTempratureAddr );
extern VOS_UINT32 UCOM_GetDspShareMemAddr(VOS_VOID);
extern VOS_UINT32 UPHY_MNTN_PhyLdfFileSaving( VOS_VOID );


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DSPINTERFACE_H__ */

