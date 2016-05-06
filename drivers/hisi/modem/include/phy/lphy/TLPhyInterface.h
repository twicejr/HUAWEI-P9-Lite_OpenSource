/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TlPhyInterface.h
  版 本 号   : 初稿
  作    者   : honghuiyong(164941)
  生成日期   : 2012年12月01日
  最近修改   :
  功能描述   : 定义邮箱，BBP基地址等。针对ARM和TENSILICA访问同一个地方，看到的
            地址不一样进行处理，例如协议栈和DSP都要访问同一邮箱，但其基地址在
            ARM侧和TENSILCA侧看到的并不一样，通过本文件定义为同一的宏，大家使用
            相同的名字即可。

  函数列表   :
  修改历史   :
------------------------------------------------------------------------------
  1.日  期     :    2012年12月1日
    作  者     : 	honghuiyong(164941)
    修改内容   : 	基于v7r1版本创建v7r2的头文件，优化邮箱设计。
------------------------------------------------------------------------------
  2.日  期     :    2015年5月3日
    作  者     : 	honghuiyong(164941)
    修改内容   : 	优化头文件中的分类定义，使得UT/ST以及FPGA支持多种芯片平台。
******************************************************************************/
#ifndef __TL_PHY_INTERFACE_H__
#define __TL_PHY_INTERFACE_H__

/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "product_config.h"

/************************************************************
                               宏定义
************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#if defined(TL_PHY_FPGA_P500)
/*-------------------------------------------------------------------------*
 *                  P500 Base verification platform                        *
 *-------------------------------------------------------------------------*/
    #define LPHY_FPGA                               "FPGAP500"
    #error "Sorry, this code do not support P500 board Anymore!"

#elif defined(TL_PHY_FPGA_P531)
/*-------------------------------------------------------------------------*
 *                  P531 Base verification platform                        *
 *-------------------------------------------------------------------------*/
    #define LPHY_FPGA                               "FPGAP531"
    #error "Sorry, this code do not support P531 board Anymore!"

#elif defined(TL_PHY_FPGA_P532)
/*-------------------------------------------------------------------------*
 *                  P532 Base verification platform                        *
 *-------------------------------------------------------------------------*/

    #define MASTER_TCM_ADDR_OFFSET                  (0x00000000)
    #define SLAVE_TCM_ADDR_OFFSET                   (0x00000000)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)
    #define LPHY_FPGA_P532
    #define LPHY_FPGA                                "FPGAP532"

    #if defined(TL_PHY_HI6950)
    /*-------------------------------------------------------------------------*
     *              [P532 + Hi6950 BBP FPGA] verification platform             *
     *-------------------------------------------------------------------------*/
        #define TLPHY_BBP_BASE_ADDR                 (0x21000000UL)
        #define LPHY_FPGA_V750
        #define LPHY_V750
        #define  LPHY_CHIP_BB_6950CS
        #define LPHY_RFIC_HI6362

    #elif defined(TL_PHY_HI6250)
    /*-------------------------------------------------------------------------*
     *              [P532 + Hi6250 BBP FPGA] verification platform             *
     *-------------------------------------------------------------------------*/
        #define TLPHY_BBP_BASE_ADDR                 (0x21000000UL)  /*待确认*/
        #define LPHY_FPGA_V850
        #define LPHY_V850
        #define LPHY_CHIP_BB_6950CS
        #define LPHY_RFIC_HI6362

    #elif defined(TL_PHY_HI6932)
    /*-------------------------------------------------------------------------*
     *              [P532 + Hi6932 BBP FPGA] verification platform             *
     *-------------------------------------------------------------------------*/
        #define TLPHY_BBP_BASE_ADDR                 (0x21000000UL)  /*待确认*/
        #define LPHY_FPGA_V722
        #define LPHY_V722
        #define LPHY_CHIP_BB_6950CS
        #define LPHY_RFIC_HI6362

    #elif defined(TL_PHY_HI3660)
    /*-------------------------------------------------------------------------*
     *              [P532 + Hi3660 BBP FPGA] verification platform             *
     *-------------------------------------------------------------------------*/
        #define TLPHY_BBP_BASE_ADDR                 (0x21000000UL)  /*待确认*/
        #define LPHY_FPGA_K3V6
        #define LPHY_K3V6
        #define LPHY_CHIP_BB_6950CS
        #define LPHY_RFIC_HI6362

    #else
        error "sorry, this is not a support FPGA + xxxx version!"
    #endif

    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))

#elif (defined(TL_PHY_ASIC_HI6930)||defined(TL_PHY_SFT_HI6930))
/*-------------------------------------------------------------------------*
 *                  Hi6930[V7R2] ASIC[/SFT] board configuration            *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)
    #define TLPHY_BBP_BASE_ADDR                     (0x20000000UL)

    #define LPHY_CHIP_BB_6930CS
    #define LPHY_RFIC_HI6361

    #define LPHY_ASIC_B720
    #define LPHY_ASIC                               "V700R200"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))


#elif (defined(TL_PHY_ASIC_K3V3) || defined(TL_PHY_K3V3_SFT))
/*-------------------------------------------------------------------------*
 *                  Kirin920[K3V3] ASIC[/SFT] board configuration          *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)
    #define TLPHY_BBP_BASE_ADDR                     (0xE1000000UL)

    #define LPHY_CHIP_BB_6930CS
    #define LPHY_RFIC_HI6361

    #define LPHY_ASIC_K3V3
    #define LPHY_ASIC                                "K300V300"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))

#elif defined(TL_PHY_ASIC_V711)
/*-------------------------------------------------------------------------*
 *                  Hi6921[V711] ASIC[/SFT] board configuration            *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)
    #define TLPHY_BBP_BASE_ADDR                     (0x20000000UL)

    #define LPHY_CHIP_BB_6930CS
    #define LPHY_RFIC_HI6361
    #define LPHY_ASIC_V711
    #define LPHY_ASIC                                "V700R110"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))

#elif defined(CHIP_BB_HI6210)    //[V810&V820 platform]

/*-------------------------------------------------------------------------*
 *                  Hi6210[Kirin620] ASIC[/SFT] board configuration        *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x00000000)
    #define SLAVE_TCM_ADDR_OFFSET                   (0x00000000)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)
    #define TLPHY_BBP_BASE_ADDR                     (0xFD000000UL)

    #define LPHY_CHIP_BB_6930CS
    #define LPHY_RFIC_HI6361

    #define LPHY_ASIC_V810
    #define LPHY_ASIC                               "V800R200"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))

#elif (defined(TL_PHY_ASIC_HI6950))
/*-------------------------------------------------------------------------*
 *                  Hi6950[Balong750] ASIC[/SFT] board configuration       *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x10000000UL)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL - MASTER_TCM_ADDR_OFFSET)
    #define TLPHY_BBP_BASE_ADDR                     (0x81000000UL)

    #define LPHY_CHIP_BB_6950CS
    #define LPHY_RFIC_HI6362
    #define LPHY_ASIC_V750
    #define LPHY_V750
    #define LPHY_ASIC                                "V700R500"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))

#elif defined(TL_PHY_ASIC_K3V5)
/*-------------------------------------------------------------------------*
 *                  Hi9635[Kirin950] ASIC[/SFT] board configuration        *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)
    #define TLPHY_BBP_BASE_ADDR                     (0xE1000000UL)

    #define LPHY_CHIP_BB_6930CS

    #if defined(PRODUCT_HISILICON_RFIC_VERSION)
        #define LPHY_RFIC_HI6361
    #else
        #define LPHY_RFIC_HI6362_MPW_EC
    #endif


    #if defined(CONFIG_AVOID_RFIC6362_LDO27_LEAK)
        #define TLPHY_RFIC_HI6362_AVOID_LDO27
    #endif

    #if defined(LPHY_RFIC_HI6362_MPW)
        #define         LPHY_RFIC_HI6362               (PHY_ON)
        #define         LPHY_RFIC_HI6362_MPW_DEFECT    (PHY_ON)
    #elif defined(LPHY_RFIC_HI6362_MPW_EC)
        #define         LPHY_RFIC_HI6362               (PHY_ON)
        #define         LPHY_RFIC_HI6362_MPW_EC_DEFECT (PHY_ON)
    #elif defined(LPHY_RFIC_HI6362_PILOT)
        #define         LPHY_RFIC_HI6362               (PHY_ON)
        #define         LPHY_RFIC_HI6362_PILOT_DEFECT  (PHY_ON)

        #endif


    #define LPHY_ASIC_K3V5
    #define LPHY_ASIC                                "K300V500"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))


#elif (defined(TL_PHY_ASIC_V722))
/*-------------------------------------------------------------------------*
 *                  Hixxxx[Balong722] ASIC[/SFT] board configuration       *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x10000000UL)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL - MASTER_TCM_ADDR_OFFSET)
    #define TLPHY_BBP_BASE_ADDR                     (0x81000000UL)

    #define LPHY_CHIP_BB_6950CS
    #define LPHY_RFIC_HI6362
    #define LPHY_ASIC_V722
    #define LPHY_V722
    #define LPHY_ASIC                                 "V700R220"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))

#elif (defined(TL_PHY_ASIC_V850))
/*-------------------------------------------------------------------------*
 *                  Hixxxx[Kirin650] ASIC[/SFT] board configuration        *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x70000000UL)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL - MASTER_TCM_ADDR_OFFSET)
    #define TLPHY_BBP_BASE_ADDR                     (0xE1000000UL)

    #define LPHY_CHIP_BB_6950CS
    #define LPHY_RFIC_HI6362
    #define LPHY_ASIC_V850
    #define LPHY_V850
    #define LPHY_ASIC                                "V800R500"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))

#elif (defined(TL_PHY_ASIC_K3V6))
/*-------------------------------------------------------------------------*
 *                  Hixxxx[Kirin960] ASIC[/SFT] board configuration        *
 *-------------------------------------------------------------------------*/
    #define MASTER_TCM_ADDR_OFFSET                  (0x70000000UL)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL - MASTER_TCM_ADDR_OFFSET)
    #define TLPHY_BBP_BASE_ADDR                     (0x20000000UL)

    #define LPHY_CHIP_BB_6950CS
    #define LPHY_RFIC_HI6362
    #define LPHY_ASIC_K3V6
    #define LPHY_K3V6
    #define LPHY_ASIC                                "K300V600"
    #define PHY_VER_SEG                             __attribute__((section(".lphy.version")))
    #define SYS_DBG_SEG                             __attribute__((section(".sys.dbg.seg")))
#else
    #error "sorry, this is not a supported board version, please include product_config.h"
#endif



/*-------------------------------------------------------------------------*
 *      Difference between [FPGA/ASIC] and pc-based verification platform  *
 *-------------------------------------------------------------------------*/
#if defined(MS_VC6_PLATFORM)
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (LPHY_SIM_LMAC_HARQ_BUFF_BASE_ADDR)
    #define LPHY_SHARE_MEM_BASE_ADDR_FOR_DSP        (LPHY_SIM_SHARE_MEM_BASE_ADDR_FOR_DSP)
    #define LPHY_SHARE_MEM_BASE_ADDR_FOR_SOC        (LPHY_SIM_SHARE_MEM_BASE_ADDR_FOR_DSP)

    #undef  PHY_VER_SEG
    #undef  SYS_DBG_SEG
    #define PHY_VER_SEG
    #define SYS_DBG_SEG
#else
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR                   (TLPHY_BBP_BASE_ADDR + 0x680000UL)
    #define LPHY_SHARE_MEM_BASE_ADDR_FOR_DSP                (LPHY_PUB_DTCM_BASE)
    #define LPHY_SHARE_MEM_BASE_ADDR_FOR_SOC                (LPHY_PUB_DTCM_BASE + MASTER_TCM_ADDR_OFFSET)
#endif

    #define LPHY_LMAC_TIMER_LOCK_ADDR                       (TLPHY_BBP_BASE_ADDR + 0x70E094UL)
    #define LPHY_LMAC_FRAME_ADDR                            (TLPHY_BBP_BASE_ADDR + 0x70E014UL)
    #define LPHY_LMAC_SUB_FRAME_ADDR                        (TLPHY_BBP_BASE_ADDR + 0x70E018UL)
    #define LPHY_LMAC_HARQ_BUFF_ADDR_BY_HARQID(ucHarqId)    (LPHY_LMAC_HARQ_BUFF_BASE_ADDR + (ucHarqId*0x4000))

/*邮箱基地址定义*/
#if (defined(TENSILICA_PLATFORM) || defined(MS_VC6_PLATFORM))    /*DSP access mailbox base address*/
    #define LPHY_MAILBOX_BASE_ADDR                          (LPHY_SHARE_MEM_BASE_ADDR_FOR_DSP)
#else
    #define LPHY_MAILBOX_BASE_ADDR                          (LPHY_SHARE_MEM_BASE_ADDR_FOR_SOC)
#endif


/************************************************************
                             数据结构定义
************************************************************/



/*****************************************************************************
 ENUM NAME: LPHY_WORKING_MODE_ENUM defined for LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR
 INTENTION: TLPHY SYSTEM WORKING MODE DEFINE
*****************************************************************************/
typedef enum __LPHY_WORKING_MODE_ENUM__
{
    LPHY_WORKING_MODE_RTT = 0,
    LPHY_WORKING_MODE_SINGLE_MODE  = 1,
    LPHY_WORKING_MODE_MULTI_MODE   = 2,
    LPHY_WORKING_MODE_DUO_SIM_MODE = 3,
}LPHY_WORKING_MODE_ENUM;

/*****************************************************************************
 ENUM NAME: LPHY_RTT_LPC_MODE_ENUM defined for power-saving control mode
 INTENTION: TLDSP POWER SAVING MODE
*****************************************************************************/
typedef enum __LPHY_RTT_LPC_MODE_ENUM__
{
    POWER_SAVING_NULL,
    POWER_SAVING_SNOOZE,
    POWER_SAVING_DEEP_SLEEP
}LPHY_RTT_LPC_MODE_ENUM;

typedef unsigned short LPHY_RTT_LPC_MODE_ENUM_UINT16;
/*****************************************************************************
 STRU NAME: MULTIMODE_BB_STARTUP_MODE_IND_STRU defined for LPHY_MAILBOX_MULTIMODE_STARTUP_MODE_ADDR
 INTENTION: Multimode startup indicator
*****************************************************************************/
typedef struct __MULTIMODE_BB_STARTUP_MODE_IND_STRU__
{
    unsigned int bLteStartInd    :4;    //0:Inactive,1:Active
    unsigned int bTdsStartInd    :4;    //0:Inactive,1:Active
    unsigned int bReserved       :24;
}MULTIMODE_BB_STARTUP_MODE_IND_STRU;

/*****************************************************************************
 STRU NAME: TLPHY_DDR_ADDR_INFO_STRU defined TLPHY_DDR_ADDR_INFO
 INTENTION: ps pre-powerup initialized ddr segment base address list for dsp
*****************************************************************************/
typedef struct __OUTER_MEM_IND_STRU__
{
    unsigned long ulBase;
    unsigned long ulSize;
}OUTER_MEM_IND_STRU;

typedef struct __TLPHY_OUTER_MEM_INFO_STRU__
{
    OUTER_MEM_IND_STRU stPhyImagBuff;      //Image buffer
    OUTER_MEM_IND_STRU stSdrDataBuff;      //Sdr buff for csu & emu
    OUTER_MEM_IND_STRU stLcsDataBuff;      //Otdoa carculate buffer
    OUTER_MEM_IND_STRU stLBandNvBuff;      //Lte Band related buffer

    OUTER_MEM_IND_STRU stSRamLpcBuff;      //SRam Low power contol buffer
    OUTER_MEM_IND_STRU stSRamMbxProtect;   //mbx protect flag
    OUTER_MEM_IND_STRU stSRamMntnInfo;     //mbx overflow flag
    OUTER_MEM_IND_STRU stHkADCInfoBuff;    //Get temperature info

    OUTER_MEM_IND_STRU stTimeStampLog;     //timestamp log buffer
    OUTER_MEM_IND_STRU stAfcTraceInfo;     //afc trace information

    OUTER_MEM_IND_STRU stHifiMbxULHead;
    OUTER_MEM_IND_STRU stHifiMbxULBody;
    OUTER_MEM_IND_STRU stHifiMbxDLHead;
    OUTER_MEM_IND_STRU stHifiMbxDLBody;

    OUTER_MEM_IND_STRU stDsdsConfigInfo;    //dsds configure descriptor
    OUTER_MEM_IND_STRU stRsvdBuffInfo;      //reserved ddr buffer descriptor
}TLPHY_OUTER_MEM_INFO_STRU;



/************************************************************
                               宏定义
************************************************************/


/*****************************************************************************
 MARC NAME: MAILBOX DEFINE
 INTENTION: MAILBOX defined List
*****************************************************************************/
#if (defined(LPHY_ASIC_K3V5) || defined(LPHY_CHIP_BB_6950CS))

    #define LPHY_MAILBOX_SHARE_MEM_SIZE                 (0x00000400UL)  /*1k字节，TBD*/
    #define LPHY_MAILBOX_DEBUG_SEG_SIZE                 (0x00000C00UL)  /*3k字节，TBD*/
    #define LPHY_MAILBOX_HDLC_BUF_SIZE                  (0x00002400UL)  /*9K字节, TBD*/
    #define LPHY_MAILBOX_LHPA_UP_SIZE                   (0x00002800UL)  /*10K字节，PS上行邮箱大小*/
    #define LPHY_MAILBOX_LHPA_DOWN_SIZE                 (0x00002800UL)  /*10k字节，PS下行邮箱大小*/
    #define LPHY_MAILBOX_OM_UP_SIZE                     (0x00000400UL)  /*1k字节，OM下行邮箱大小*/
    #define LPHY_MAILBOX_OM_DOWN_SIZE                   (0x00000800UL)  /*2k字节，OM下行邮箱大小*/
    #define LPHY_MAILBOX_LMAC_UP_SIZE                   (0x00000400UL)  /*1k字节，MAC专用邮箱大小*/
    #define LPHY_MAILBOX_LMAC_DOWN_SIZE                 (0x00000400UL)  /*1k字节，MAC专用邮箱大小*/
    #define LPHY_MAILBOX_DLTB_QUEUE_SIZE                (0x00000400UL)  /*1k字节，MACPHY下行TB QUEUE处理大小*/
    #define LPHY_MAILBOX_LPP_DOWN_SIZE                  (0x00000A00UL)  /*2.5字节，LPP 定位辅助信息邮箱大小*/
    #define LPHY_MAILBOX_TOA_SIZE                       (0x00000600UL)  /*1.5k字节，TOA邮箱大小*/

    #define LTPHY_NV_COMM_CFG_SIZE                      (0x00000800UL)  /*02k字节，LT PHY 公共NV 大小*/
    #define LPHY_NV_CFG_SIZE                            (0x00002800UL)  /*10k字节，LTE NV项配置区大小 s00181739 ADD*/
    #define TPHY_NV_CFG_SIZE                            (0x00001c00UL)  /*07k字节，TDS NV项配置区大小*/
    #define BAND_NV_DDR_IDX_SIZE                        (0x00000800UL)  /*02k字节，TDS NV项配置区大小*/

    #define LPHY_MAILBOX_TDS_BANKA_MEM_SIZE             (0x00008000UL)  /*32K字节, 用于  pliot版本lcs计算使用*/
    #define LPHY_MAILBOX_CSU_BANKA_MEM_SIZE             (0x00000000UL)
    #define LPHY_MAILBOX_LCS_BANKA_MEM_SIZE             (0x00000000UL)

    #define LPHY_MAILBOX_RSV_BANKA_MEM_SIZE             (0x00008000UL)  /*0K rsvd segment 1*/
    #define LPHY_TOTAL_RSVD_MEM_SIZE                    (128*1024)      /*128K*/

#else

    #define LPHY_MAILBOX_SHARE_MEM_SIZE                 (0x00000400UL)  /*1k字节，TBD*/
    #define LPHY_MAILBOX_DEBUG_SEG_SIZE                 (0x00000000UL)  /*3k字节，TBD*/
    #define LPHY_MAILBOX_HDLC_BUF_SIZE                  (0x00002000UL)  /*8K字节, TBD*/
    #define LPHY_MAILBOX_LHPA_UP_SIZE                   (0x00002000UL)  /*8K字节，PS上行邮箱大小*/
    #define LPHY_MAILBOX_LHPA_DOWN_SIZE                 (0x00002000UL)  /*8k字节，PS下行邮箱大小*/
    #define LPHY_MAILBOX_OM_UP_SIZE                     (0x00000000UL)  /*0k字节，OM下行邮箱大小*/
    #define LPHY_MAILBOX_OM_DOWN_SIZE                   (0x00000800UL)  /*2k字节，OM下行邮箱大小*/
    #define LPHY_MAILBOX_LMAC_UP_SIZE                   (0x00000400UL)  /*1k字节，MAC专用邮箱大小*/
    #define LPHY_MAILBOX_LMAC_DOWN_SIZE                 (0x00000400UL)  /*1k字节，MAC专用邮箱大小*/
    #define LPHY_MAILBOX_DLTB_QUEUE_SIZE                (0x00000400UL)  /*1k字节，MACPHY下行TB QUEUE处理大小*/
    #define LPHY_MAILBOX_LPP_DOWN_SIZE                  (0x00000A00UL)  /*2.5字节，LPP 定位辅助信息邮箱大小*/
    #define LPHY_MAILBOX_TOA_SIZE                       (0x00000600UL)  /*1.5k字节，TOA邮箱大小*/

    #define LTPHY_NV_COMM_CFG_SIZE                      (0x00000400UL)  /*1k字节，LT PHY 公共NV 大小*/
    #define LPHY_NV_CFG_SIZE                            (0x00002400UL)  /*9k字节，LTE NV项配置区大小 s00181739 ADD*/
    #define TPHY_NV_CFG_SIZE                            (0x00002000UL)  /*8k字节，TDS NV项配置区大小*/
    #define BAND_NV_DDR_IDX_SIZE                        (0x00000000UL)  /*00k字节，TDS NV项配置区大小*/

    #define LPHY_MAILBOX_TDS_BANKA_MEM_SIZE             (0x00008000UL)  /*32K字节, 用于  pliot版本lcs计算使用*/
    #define LPHY_MAILBOX_CSU_BANKA_MEM_SIZE             (0x00003000UL)
    #define LPHY_MAILBOX_LCS_BANKA_MEM_SIZE             (0x00000000UL)
    #define LPHY_MAILBOX_RSV_BANKA_MEM_SIZE             (0x00000000UL)  /*0K rsvd segment   1*/

    #define LPHY_TOTAL_RSVD_MEM_SIZE                    (96*1024)       /*96K*/

#endif
/*****************************************************************************
 MARC NAME: TOTAL MAILBOX SIZE
 INTENTION: TOTAL MAILBOX SIZE
*****************************************************************************/
/*邮箱总大小*/
#define LPHY_TOTAL_USED_MEM_SIZE    (   \
      LPHY_MAILBOX_SHARE_MEM_SIZE       \
    + LPHY_MAILBOX_DEBUG_SEG_SIZE       \
    + LPHY_MAILBOX_HDLC_BUF_SIZE        \
    + LPHY_MAILBOX_LHPA_UP_SIZE         \
    + LPHY_MAILBOX_LHPA_DOWN_SIZE       \
    + LPHY_MAILBOX_OM_UP_SIZE           \
    + LPHY_MAILBOX_OM_DOWN_SIZE         \
    + LPHY_MAILBOX_LMAC_UP_SIZE         \
    + LPHY_MAILBOX_LMAC_DOWN_SIZE       \
    + LPHY_MAILBOX_DLTB_QUEUE_SIZE      \
    + LPHY_MAILBOX_LPP_DOWN_SIZE        \
    + LPHY_MAILBOX_TOA_SIZE             \
    + LTPHY_NV_COMM_CFG_SIZE            \
    + LPHY_NV_CFG_SIZE                  \
    + TPHY_NV_CFG_SIZE                  \
    + BAND_NV_DDR_IDX_SIZE              \
    + LPHY_MAILBOX_TDS_BANKA_MEM_SIZE   \
    + LPHY_MAILBOX_CSU_BANKA_MEM_SIZE   \
    + LPHY_MAILBOX_LCS_BANKA_MEM_SIZE   \
    + LPHY_MAILBOX_RSV_BANKA_MEM_SIZE)

/*****************************************************************************
 MARC NAME: Reserved shared memory size check & protection
 INTENTION: Reserved shared memory size check & protection
*****************************************************************************/
#if (LPHY_TOTAL_USED_MEM_SIZE > LPHY_TOTAL_RSVD_MEM_SIZE)
	#error "sorry, reserved memory exhausted!"
#endif

/*****************************************************************************
 MARC NAME: detail mailbox segment base address
 INTENTION: detail mailbox segment base address
*****************************************************************************/
#define LPHY_MAILBOX_VERSION_ADDR                   (LPHY_MAILBOX_BASE_ADDR + 0x0200)   /*DSP版本查询地址*/
#define LPHY_MAILBOX_LOAD_MEMORY_ADDR               (LPHY_MAILBOX_BASE_ADDR + 0x020C)   /*开机初始化握手地址*/
#define LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR         (LPHY_MAILBOX_BASE_ADDR + 0x0210)   /*LTE PHY WorkModeInd*/
#define LPHY_MAILBOX_LPHY_CTU_REG_BASE_ADDR         (LPHY_MAILBOX_BASE_ADDR + 0x0214)   /*LTE 编译模式*/
#define LPHY_MAILBOX_LPHY_DSP_NV_PARA_SIZE_ADDR     (LPHY_MAILBOX_BASE_ADDR + 0x0218)   /*LTE PHY DSP 编译时 NV Para_Size*/
#define LPHY_MAILBOX_LPHY_ARM_NV_PARA_SIZE_ADDR     (LPHY_MAILBOX_BASE_ADDR + 0x021C)   /*LTE PHY ARM下发的  NV Para_Size*/
#define LPHY_MAILBOX_MULTIMODE_STARTUP_MODE_ADDR    (LPHY_MAILBOX_BASE_ADDR + 0x0220)   /*多模基带启动模式指示*/
#define LPHY_MAILBOX_IMAG_SIZE_INFO_ADDR            (LPHY_MAILBOX_BASE_ADDR + 0x0230)   /*多模基带启动模式指示*/
#define LPHY_MAILBOX_OUTER_MEM_INFO_ADDR            (LPHY_MAILBOX_BASE_ADDR + 0x0240)   /*TL PHY 在DDR地址，包括IMAGE SDR LCS BANDNV。64B*/

#define LPHY_MAILBOX_SEGMENT_OFFSET                 (LPHY_MAILBOX_SHARE_MEM_SIZE        + LPHY_MAILBOX_DEBUG_SEG_SIZE)
#define LPHY_MAILBOX_HDLC_BUF_BASE_ADDR             (LPHY_MAILBOX_BASE_ADDR             + LPHY_MAILBOX_SEGMENT_OFFSET)
#define LPHY_MAILBOX_LHPA_UP_BASE_ADDR              (LPHY_MAILBOX_HDLC_BUF_BASE_ADDR    + LPHY_MAILBOX_HDLC_BUF_SIZE)
#define LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR            (LPHY_MAILBOX_LHPA_UP_BASE_ADDR     + LPHY_MAILBOX_LHPA_UP_SIZE)
#define LPHY_MAILBOX_OM_UP_BASE_ADDR                (LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR   + LPHY_MAILBOX_LHPA_DOWN_SIZE)
#define LPHY_MAILBOX_OM_DOWN_BASE_ADDR              (LPHY_MAILBOX_OM_UP_BASE_ADDR       + LPHY_MAILBOX_OM_UP_SIZE)
#define LPHY_MAILBOX_LMAC_UP_BASE_ADDR              (LPHY_MAILBOX_OM_DOWN_BASE_ADDR     + LPHY_MAILBOX_OM_DOWN_SIZE)
#define LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR            (LPHY_MAILBOX_LMAC_UP_BASE_ADDR     + LPHY_MAILBOX_LMAC_UP_SIZE)
#define LPHY_MAILBOX_DL_TB_QUEUE_BASE_ADDR          (LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR   + LPHY_MAILBOX_LMAC_DOWN_SIZE)
#define LPHY_MAILBOX_LPP_DOWN_BASE_ADDR             (LPHY_MAILBOX_DL_TB_QUEUE_BASE_ADDR + LPHY_MAILBOX_DLTB_QUEUE_SIZE)
#define LPHY_MAILBOX_TOA_BASE_ADDR                  (LPHY_MAILBOX_LPP_DOWN_BASE_ADDR    + LPHY_MAILBOX_LPP_DOWN_SIZE)

#define LPHY_MAILBOX_NV_CFG_BASE_ADDR               (LPHY_MAILBOX_TOA_BASE_ADDR         + LPHY_MAILBOX_TOA_SIZE)
#define TPHY_MAILBOX_NV_CFG_BASE_ADDR               (LPHY_MAILBOX_NV_CFG_BASE_ADDR      + LPHY_NV_CFG_SIZE)
#define COMM_MAILBOX_NV_CFG_BASE_ADDR               (TPHY_MAILBOX_NV_CFG_BASE_ADDR      + TPHY_NV_CFG_SIZE)
#define BAND_MAILBOX_NV_IDX_BASE_ADDR               (COMM_MAILBOX_NV_CFG_BASE_ADDR      + LTPHY_NV_COMM_CFG_SIZE)

#define LPHY_MAILBOX_TDS_BANKA_BASE_ADDR            (BAND_MAILBOX_NV_IDX_BASE_ADDR      + BAND_NV_DDR_IDX_SIZE)
#define LPHY_MAILBOX_CSU_BANKA_BASE_ADDR            (LPHY_MAILBOX_TDS_BANKA_BASE_ADDR   + LPHY_MAILBOX_TDS_BANKA_MEM_SIZE)
#define LPHY_MAILBOX_LCS_BANKA_BASE_ADDR            (LPHY_MAILBOX_CSU_BANKA_BASE_ADDR   + LPHY_MAILBOX_CSU_BANKA_MEM_SIZE)
#define LPHY_MAILBOX_RSV_BANKA_BASE_ADDR            (LPHY_MAILBOX_LCS_BANKA_BASE_ADDR   + LPHY_MAILBOX_LCS_BANKA_MEM_SIZE)
#define LPHY_MAILBOX_LPHY_NV_BASE_ADDR              (LPHY_MAILBOX_TOA_BASE_ADDR)  //TBD_Onetrack

/*	----------------------------------------------------------------------------------
 * redefine the marco to keep the compatible with old code.
-------------------------------------------------------------------------------------*/
#define TPHY_RSVD_32K_BUFFER_BASE_ADDR              (LPHY_MAILBOX_TDS_BANKA_BASE_ADDR)
#define LTPHY_MAILBOX_NV_COMM_CFG_BASE_ADDR         (COMM_MAILBOX_NV_CFG_BASE_ADDR)
#define TLPHY_DDR_ADDR_INFO                         (LPHY_MAILBOX_OUTER_MEM_INFO_ADDR)

#define LPHY_MAILBOX_DDR_NV_ADDR                    (BAND_MAILBOX_NV_IDX_BASE_ADDR)

#define LPHY_MAILBOX_SLAVE_AWAKE_ADDR               (0)  //Reseved for CPHY

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* __MEM_MAP_BASE_H__ */
