/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              soc_baseaddr_inferface.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH
*  Date Created: 2015-08-17
*        Author: guodongfeng
*   Description: soc base addr
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2015-08-17  guodongfeng     Create the first version.
*
*******************************************************************************/

#ifndef __SOC_BASEADDR_INTERFACE_H__
#define __SOC_BASEADDR_INTERFACE_H__



#define SOC_BBP_CDMA_BASE_ADDR          ( 0xe19e0000 )   /* Cbbp */
#define SOC_Modem_DMAC_BASE_ADDR        ( 0xe0204000 )   /* Edma */
#define SOC_IPC_S_BASE_ADDR             ( 0xFDF21000 )   /* Ipc */
#define SOC_SOCP_BASE_ADDR	            ( 0xff030000 )   /* Socp */
#define SOC_AO_SCTRL_BASE_ADDR          ( 0xfff0a534 )   /* 32k SOC_AO_SCTRL_BASE_ADDR */
#define SOC_MODEM_SCTRL_BASE_ADDR       ( 0xe0200000 )   /* sysctrl */
#define SOC_ABB_CFG_BASE_ADDR           ( 0xe1f8c000 )   /* uwAbbCfgAddr */
#define SOC_BBP_COMM_BASE_ADDR          ( 0xe1f80000 )   /* uwBbpcomAddr */
#define SOC_BBP_COMM_ON_BASE_ADDR       ( 0xfff12000 )   /* uwBbpcomOnAddr */
#define SOC_BBP_GLB_ON_BASE_ADDR        ( 0xfff12000 )
#define SOC_BBP_WCDMA_BASE_ADDR         ( 0xe1900000 )
#define SOC_BBP_COMM_2_BASE_ADDR        ( SOC_BBP_COMM_BASE_ADDR )  /* uwBbpcom2Addr */
#define SOC_PMU_SSI_BASE_ADDR            ( 0xFFF34000 )  /* PMU */
#define SOC_PA_POWER_ON_BASE_ADDR        ( 0xe8a17020 )  /* uwPaPowerOnBaseAddr */
#define SOC_BBP_WDG_BASE_ADDR            ( 0x00000000 )  /*hi3650没有watchdog，设为无效值*/

#endif
