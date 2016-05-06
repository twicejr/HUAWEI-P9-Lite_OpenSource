/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : PhyAsDmInterface.h
  版 本 号   : 初稿
  作    者   : 罗青全
  生成日期   : 2010年12月15日
  最近修改   :
  功能描述   : 该头文件是协议栈和物理层之间的接口文件。
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月15日
    作    者   : 罗青全
    修改内容   : 创建文件
  2.日    期   : 2013年06月24日
    作    者   : f48555
    修改内容   : DTS2013061705150，新增原语ID_MPH_FULL_LIST_STOP_REQ和ID_MPH_FULL_LIST_STOP_CNF

******************************************************************************/

#ifndef __PHYGASCOMM_H__
#define __PHYGASCOMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#pragma pack(1)

/********************************* 信道类型**********************************/
#define PHY_CHANNEL_TCH_F                           ( 0x0001 )
#define PHY_CHANNEL_TCH_H                           ( 0x0002 )
#define PHY_CHANNEL_SDCCH_4                         ( 0x0003 )
#define PHY_CHANNEL_SDCCH_8                         ( 0x0004 )
#define PHY_CHANNEL_CCCH                            ( 0x0005 )
#define PHY_CHANNEL_NBCCH                           ( 0x0006 )
#define PHY_CHANNEL_PCH                             ( 0x0007 )
#define PHY_CHANNEL_EPCH                            ( 0x0008 )
#define PHY_CHANNEL_CBCH                            ( 0x0009 )
#define PHY_CHANNEL_EBCCH                           ( 0x000A )


/********************* 结构MPH_RXLEV_CNF_STRU 中相关域取值 ******************/
#define SEARCH_SEND_FREQ_INFO_NUM                   ( 32 )                      /* 频点搜索时，使用原语MPH_RXLEV_CNF_STRU一次上报的最大频点数目 */

/***********************  结构MPH_CELL_SB_IND_STRU中使用的宏 ****************/
#define PHY_GAS_SB_IND_ERRCODE_SUCCESS              ( 0 )
#define PHY_GAS_SB_IND_ERRCODE_SB_FAIL              ( 1 )
#define PHY_GAS_SB_IND_ERRCODE_AFC_FAIL             ( 2 )
#define PHY_GAS_SB_IND_ERRCODE_NO_RF_FAIL           ( 3 )

/***********************  结构MPH_RA_CNF_STRU和MPHP_RA_CNF_ST中使用的宏 ****************/
#define PHY_GAS_RA_CNF_NO_RF_FAIL                   ( 2 )
    

/**************************** 背景搜索相关宏定义 ****************************/

#define     MAX_ENH_MEAS_G_CARRIER_NUM              ( 60 )                      /* GAS发送给G物理层进行频点测量的最大频点个数 */
#define     RRC_PHY_MAX_MSG_SIZE                    ( 230 )                     /* RRC通过GAS透传给G物理层的最大消息长度 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    /* RR  ---> L1 */
    ID_MPH_IMMED_ASSIGN_REQ                         =   0x2701,                 /* _H2ASN_MsgChoice  MPH_IMMED_ASSIGN_REQ_STRU */
    ID_MPH_CHANNEL_ASSIGN_REQ                       =   0x2702,                 /* _H2ASN_MsgChoice  MPH_CHANNEL_ASSIGN_REQ_STRU */
    ID_MPH_HO_REQ                                   =   0x2703,                 /* _H2ASN_MsgChoice  MPH_HO_REQ_STRU */
    ID_MPH_ABORT_HO_RA_REQ                          =   0x2704,                 /* _H2ASN_MsgChoice  MPH_ABORT_HO_RA_REQ_STRU */
    ID_MPH_HANDOVER_FAIL_REQ                        =   0x2705,                 /* _H2ASN_MsgChoice  MPH_HANDOVER_FAIL_REQ_STRU */
    ID_MPH_CHANNEL_MODE_MODIFY_REQ                  =   0x2706,                 /* _H2ASN_MsgChoice  MPH_CHANNEL_MODE_MODIFY_REQ_STRU */
    ID_MPH_SET_CIPHERING_REQ                        =   0x2707,                 /* _H2ASN_MsgChoice  MPH_SET_CIPHERING_REQ_STRU */
    ID_MPH_CHANGE_FREQUENCY_REQ                     =   0x2708,                 /* _H2ASN_MsgChoice  MPH_CHANGE_FREQUENCY_REQ_STRU */
    ID_MPH_STOP_DEDICATED_REQ                       =   0x2709,                 /* _H2ASN_MsgChoice  MPH_STOP_DEDICATED_REQ_STRU */
    ID_MPH_CHANGE_DTX_REQ                           =   0x270a,                 /* _H2ASN_MsgChoice  MPH_CHANGE_DTX_REQ_STRU */
    ID_MPH_HANDOVER_COMPLETE                        =   0x270b,                 /* _H2ASN_MsgChoice  MPH_HANDOVER_COMPLETE_STRU */
    ID_MPH_RA_REQ                                   =   0x270c,                 /* _H2ASN_MsgChoice  MPH_RA_REQ_STRU */
    ID_MPH_RA_ABORT_REQ                             =   0x270d,                 /* _H2ASN_MsgChoice  MPH_RA_ABORT_REQ_ST */
    ID_MPH_BHO_NCELL_FB_SB_REQ                      =   0x270e,                 /* _H2ASN_MsgChoice  MPH_BHO_NCELL_FB_SB_REQ_STRU */
    ID_MPH_STOP_BHO_NCELL_FB_SB_REQ                 =   0x270f,                 /* _H2ASN_MsgChoice  MPH_STOP_BHO_NCELL_FB_SB_REQ_STRU */
    ID_MPH_CBCH_READ_REQ                            =   0x27F0,                 /* _H2ASN_MsgChoice  MPH_CBCH_READ_REQ_STRU */
    ID_MPH_STOP_CBCH_READ_REQ                       =   0x27F1,                 /* _H2ASN_MsgChoice  MPH_STOP_CBCH_READ_REQ_STRU */
    ID_MPH_STOP_CBCH_CUR_PAGE_REQ                   =   0x27F2,                 /* _H2ASN_MsgChoice  MPH_STOP_CBCH_CUR_PAGE_REQ_STRU */


    /* L1 --->  RR */
    ID_MPH_IMMED_ASSIGN_CNF                         =   0x7201,                 /* _H2ASN_MsgChoice  MPH_IMMED_ASSIGN_CNF_STRU */
    ID_MPH_CHANNEL_ASSIGN_CNF                       =   0x7202,                 /* _H2ASN_MsgChoice  MPH_CHANNEL_ASSIGN_CNF_STRU */
    ID_MPH_ASYNC_HO_CNF                             =   0x7203,                 /* _H2ASN_MsgChoice  MPH_ASYNC_HO_CNF_STRU */
    ID_MPH_HANDOVER_FINISHED                        =   0x7204,                 /* _H2ASN_MsgChoice  MPH_HANDOVER_FINISHED_STRU */
    ID_MPH_HANDOVER_FAIL_CNF                        =   0x7205,                 /* _H2ASN_MsgChoice  MPH_HANDOVER_FAIL_CNF_STRU */
    ID_MPH_CHANNEL_MODE_MODIFY_CNF                  =   0x7206,                 /* _H2ASN_MsgChoice  MPH_CHANNEL_MODE_MODIFY_CNF_STRU */
    ID_MPH_SET_CIPHERING_CNF                        =   0x7207,                 /* _H2ASN_MsgChoice  MPH_SET_CIPHERING_CNF_STRU */
    ID_MPH_CHANGE_FREQUENCY_CNF                     =   0x7208,                 /* _H2ASN_MsgChoice  MPH_CHANGE_FREQUENCY_CNF_STRU */
    ID_MPH_STOP_DEDICATED_CNF                       =   0x7209,                 /* _H2ASN_MsgChoice  MPH_STOP_DEDICATED_CNF_STRU */
    ID_MPH_CHANGE_DTX_CNF                           =   0x720a,                 /* _H2ASN_MsgChoice  MPH_CHANGE_DTX_CNF_STRU */
    ID_MPH_RA_CNF                                   =   0x720c,                 /* _H2ASN_MsgChoice  MPH_RA_CNF_STRU */
    ID_MPH_BHO_NCELL_FB_SB_CNF                      =   0x720e,                 /* _H2ASN_MsgChoice  MPH_BHO_NCELL_FB_SB_CNF_STRU */
    ID_MPH_STOP_BHO_NCELL_FB_SB_CNF                 =   0x720f,                 /* _H2ASN_MsgChoice  MPH_STOP_BHO_NCELL_FB_SB_CNF_STRU */
    ID_MPH_CBCH_READ_CNF                            =   0x72F0,                 /* _H2ASN_MsgChoice  MPH_CBCH_READ_CNF_STRU */
    ID_MPH_STOP_CBCH_READ_CNF                       =   0x72F1,                 /* _H2ASN_MsgChoice  MPH_STOP_CBCH_READ_CNF_STRU */
    ID_MPH_STOP_CBCH_CUR_PAGE_CNF                   =   0x72F2,                 /* _H2ASN_MsgChoice  MPH_STOP_CBCH_CUR_PAGE_CNF_STRU */
    ID_MPH_CBS_DATA_IND                             =   0x72F3,                 /* _H2ASN_MsgChoice  MPH_CBS_DATA_IND_STRU */

    /* L1 ---> GCOM  */
    ID_MPH_RXLEV_CNF                                =   0x7801,                 /* _H2ASN_MsgChoice  MPH_RXLEV_CNF_STRU */
    ID_MPH_CELL_SB_IND                              =   0x7802,                 /* _H2ASN_MsgChoice  MPH_CELL_SB_IND_STRU */
    ID_MPH_PAGING_MODE_CNF                          =   0x7803,                 /* _H2ASN_MsgChoice  MPH_PAGING_MODE_CNF_STRU */
    ID_MPH_NCELL_SB_IND                             =   0x7804,                 /* _H2ASN_MsgChoice  MPH_NCELL_SB_IND_STRU */
    ID_MPH_NCELL_BCCH_READ_CNF                      =   0x7805,                 /* _H2ASN_MsgChoice  MPH_NCELL_BCCH_READ_CNF_STRU */
    ID_MPH_SCELL_BCCH_READ_CNF                      =   0x7806,                 /* _H2ASN_MsgChoice  MPH_SCELL_BCCH_READ_CNF_STRU */
    ID_MPH_SI_UPDATE_CNF                            =   0x7807,                 /* _H2ASN_MsgChoice  MPH_SI_UPDATE_CNF_STRU */
    ID_MPH_FULL_LIST_CNF                            =   0x7808,                 /* _H2ASN_MsgChoice  MPH_FULL_LIST_CNF_STRU */
    ID_MPH_FULL_LIST_STOP_CNF                       =   0x7809,                 /* _H2ASN_MsgChoice  MPH_FULL_LIST_STOP_CNF_STRU */
    ID_MPH_BA_LIST_CNF                              =   0x780a,                 /* _H2ASN_MsgChoice  MPH_BA_LIST_CNF_STRU */
    ID_MPH_WCDMA_MEAS_CNF                           =   0x780b,                 /* _H2ASN_MsgChoice  MPH_WCDMA_MEAS_CNF_STRU */
    ID_MPH_NCELL_BCCH_READ_FAIL_IND                 =   0x780d,                 /* _H2ASN_MsgChoice  MPH_NCELL_BCCH_READ_FAIL_IND_STRU */
    ID_MPHC_NETWORK_LOST_CNF                        =   0x780e,                 /* _H2ASN_MsgChoice  MPHC_NETWORK_LOST_CNF_STRU */
    ID_MPHP_SERVING_PBCCH_RELEASE_CNF               =   0x780f,                 /* _H2ASN_MsgChoice  MPHP_SERVING_PBCCH_RELEASE_CNF */
    ID_MPHP_SERVING_PBCCH_SETUP_CNF                 =   0x7810,                 /* _H2ASN_MsgChoice  MPHP_SERVING_PBCCH_SETUP_CNF_ST */
    ID_MPHP_UPDATE_PSI_PARAM_CNF                    =   0x7811,                 /* _H2ASN_MsgChoice  MPHP_UPDATE_PSI_PARAM_CNF_ST */
    ID_MPHP_GPRS_CHANNEL_QUALITY_REPORT             =   0x7812,                 /* _H2ASN_MsgChoice  MPHP_GPRS_CHANNEL_QUALITY_REPORT_ST */
    ID_MPH_NC_MEAS_REPORT_IND                       =   0x7813,                 /* _H2ASN_MsgChoice  MPH_NC_MEAS_REPORT_IND_STRU */
    ID_MPHP_EGPRS_CHANNEL_QUALITY_REPORT            =   0x7814,                 /* _H2ASN_MsgChoice  MPHP_EGPRS_CHANNEL_QUALITY_REPORT_ST */
    ID_MPH_UPDATE_RESEL_PARA_CNF                    =   0x7816,                 /* _H2ASN_MsgChoice  MPH_UPDATE_RESEL_PARA_CNF_STRU */
    ID_MPH_UPDATE_PARSE_PAGING_PARA_CNF             =   0x7817,                 /* _H2ASN_MsgChoice  MPH_UPDATE_PARSE_PAGING_PARA_CNF_STRU */
    ID_MPH_CELL_INFO_REPORT_IND                     =   0x7818,                 /* _H2ASN_MsgChoice  MPH_CELL_INFO_REPORT_IND_STRU */
    ID_MPH_CELL_RESELECT_CNF                        =   0x7819,                 /* _H2ASN_MsgChoice  MPH_CELL_RESELECT_CNF_STRU */
    ID_MPH_CS_DEDICATED_MEAS_IND                    =   0x781a,                 /* _H2ASN_MsgChoice  MPH_CS_DEDICATED_MEAS_IND_STRU */

    ID_MPH_STOP_NCELL_BCCH_READ_CNF                 =   0x781b,                 /* _H2ASN_MsgChoice  MPH_STOP_NCELL_BCCH_READ_CNF_STRU */
    ID_MPH_STOP_NCELL_FB_SB_CNF                     =   0x781d,                 /* _H2ASN_MsgChoice  MPH_STOP_NCELL_FB_SB_CNF_STRU */
    ID_MPH_G_ENH_MEAS_CNF                           =   0x781e,                 /* _H2ASN_MsgChoice  MPH_G_ENH_MEAS_CNF_STRU */
    ID_MPH_G_ENH_MEAS_STOP_CNF                      =   0x781f,                 /* _H2ASN_MsgChoice  MPH_G_ENH_MEAS_STOP_CNF_STRU */
    ID_MPH_G_ENH_MEAS_IND                           =   0x7820,                 /* _H2ASN_MsgChoice  MPH_G_ENH_MEAS_IND_STRU */
    ID_MPH_UPDATE_DEDICATED_CTRL_PARA_CNF           =   0x7821,                 /* _H2ASN_MsgChoice  MPH_UPDATE_DEDICATED_CTRL_PARA_CNF_STRU */

    ID_MPH_SET_WORK_MODE_CNF                        =   0x7822,                 /* _H2ASN_MsgChoice  MPH_SET_WORK_MODE_CNF_STRU */
    ID_MPH_LTE_MEAS_CNF                             =   0x7823,                 /* _H2ASN_MsgChoice  MPH_LTE_MEAS_CNF_STRU */
    ID_MPH_STOP_MEAS_CNF                            =   0x7824,                 /* _H2ASN_MsgChoice  MPH_STOP_MEAS_CNF_STRU */

    ID_MPH_TA_INFO_CNF                              =   0x7825,                 /* _H2ASN_MsgChoice  MPH_TA_INFO_CNF_STRU */
    ID_MPH_L_BG_SEARCH_CNF                          =   0x7826,                 /* _H2ASN_MsgChoice  MPH_L_BG_SEARCH_CNF_STRU */

    ID_MPH_TDS_MEAS_CNF                             =   0x7827,                 /* _H2ASN_MsgChoice  MPH_TDS_MEAS_CNF_STRU */

    ID_MPH_MEAS_RLT_RPT_CTRL_CNF                    =   0x7828,                 /* _H2ASN_MsgChoice  MPH_MEAS_RLT_RPT_CTRL_CNF_STRU */

    ID_MPH_RADIO_RESOURCE_IND                       =   0x7829,                 /* _H2ASN_MsgChoice  MPH_RADIO_RESOURCE_IND_STRU */
    ID_MPH_RXLEV_STOP_CNF                           =   0x782a,                 /* _H2ASN_MsgChoice  MPH_RXLEV_STOP_CNF_STRU */

    ID_MPH_W_BG_SEARCH_CNF                          =   0x782b,                 /* _H2ASN_MsgChoice  MPH_W_BG_SEARCH_CNF_STRU */
    ID_MPH_G_SLAVE_MEAS_CNF                         =   0x782c,                 /* _H2ASN_MsgChoice  MPH_G_SLAVE_MEAS_CNF_STRU */
    ID_MPH_G_SLAVE_MEAS_IND                         =   0x782d,                 /* _H2ASN_MsgChoice  MPH_G_SLAVE_MEAS_IND_STRU */
    ID_MPH_G_SLAVE_BSIC_VERIFIED_CNF                =   0x782e,                 /* _H2ASN_MsgChoice  MPH_G_SLAVE_BSIC_VERIFIED_CNF_STRU */
    ID_MPH_G_SLAVE_BSIC_VERIFIED_IND                =   0x782f,                 /* _H2ASN_MsgChoice  MPH_G_SLAVE_BSIC_VERIFIED_IND_STRU */

    ID_MPH_UPDATE_BCCH_READING_CNF                  =   0x7830,                 /* _H2ASN_MsgChoice  MPH_UPDATE_BCCH_READING_CNF_STRU */
    ID_MPH_UPDATE_PAGE_PARA_CNF                     =   0x7831,                 /* _H2ASN_MsgChoice  MPH_UPDATE_PAGE_PARA_CNF_STRU */

    /* 上报AFC的值 */
    ID_MPH_AFC_LOCK_IND                             =   0x7832,                 /* _H2ASN_MsgChoice  MPH_AFC_LOCK_IND_STRU */

    /* 读系统消息失败 */
    ID_MPH_BCCH_READ_FAIL_IND                       =   0x7833,                 /* _H2ASN_MsgChoice  MPH_BCCH_READ_FAIL_IND_STRU */

    ID_MPH_CAMP_SCELL_CNF                           =   0x7834,                 /* _H2ASN_MsgChoice  MPH_CAMP_SCELL_CNF_STRU */
    ID_MPH_START_SEARCH_CELL_CNF                    =   0x7835,                 /* _H2ASN_MsgChoice  MPH_START_SEARCH_CELL_CNF_STRU */
    ID_MPH_UPDATE_SEARCH_CELL_CNF                   =   0x7836,                 /* _H2ASN_MsgChoice  MPH_UPDATE_SEARCH_CELL_CNF_STRU */
    ID_MPH_STOP_SEARCH_CELL_CNF                     =   0x7837,                 /* _H2ASN_MsgChoice  MPH_STOP_SEARCH_CELL_CNF_STRU */

    ID_MPH_START_NCELL_BCCH_LIST_READ_CNF           =   0x7838,                 /* _H2ASN_MsgChoice  MPH_START_NCELL_BCCH_LIST_READ_CNF_STRU */
    ID_MPH_UPDATE_NCELL_BCCH_LIST_READ_CNF          =   0x7839,                 /* _H2ASN_MsgChoice  MPH_UPDATE_NCELL_BCCH_LIST_READ_CNF_STRU */
    ID_MPH_STOP_NCELL_BCCH_LIST_READ_CNF            =   0x783A,                 /* _H2ASN_MsgChoice  MPH_STOP_NCELL_BCCH_LIST_READ_CNF_STRU */
    ID_MPHP_PS_BER_REPORT                           =   0x783B,                 /* _H2ASN_MsgChoice  MPHP_PS_BER_REPORT_STRU */
    /*  GPRS专用 */
    ID_MPHP_SERVING_PBCCH_SETUP_REQ                 =   0x8017,                 /* _H2ASN_MsgChoice  MPHP_SERVING_PBCCH_SETUP_REQ_ST */
    ID_MPHP_SERVING_PBCCH_RELEASE_REQ               =   0x8018,                 /* _H2ASN_MsgChoice  MPHP_SERVING_PBCCH_RELEASE_REQ_ST */
    ID_MPHP_UPDATE_PSI_PARAM_REQ                    =   0x801b,                 /* _H2ASN_MsgChoice  MPHP_UPDATE_PSI_PARAM_REQ_ST */

    /*  GCOM ----> L1 */
    ID_MPHC_NETWORK_LOST_REQ                        =   0x8701,                 /* _H2ASN_MsgChoice  MPHC_NETWORK_LOST_REQ_STRU */
    ID_MPH_RXLEV_REQ                                =   0x8702,                 /* _H2ASN_MsgChoice  MPH_RXLEV_REQ_STRU */
    ID_MPH_START_BCCH_READING                       =   0x8703,                 /* _H2ASN_MsgChoice  MPH_START_BCCH_READING_STRU */
    ID_MPH_STOP_BCCH_READING                        =   0x8704,                 /* _H2ASN_MsgChoice  MPH_STOP_BCCH_READING_STRU */
    ID_MPH_CELL_RESELECT_REQ                        =   0x8705,                 /* _H2ASN_MsgChoice  MPH_CELL_RESELECT_REQ_STRU */
    ID_MPH_PAGING_MODE_REQ                          =   0x8706,                 /* _H2ASN_MsgChoice  MPH_PAGING_MODE_REQ_STRU */
    ID_MPH_BA_LIST                                  =   0x8709,                 /* _H2ASN_MsgChoice  MPH_BA_LIST_STRU */
    ID_MPH_NCELL_FB_SB_READ                         =   0x870a,                 /* _H2ASN_MsgChoice  MPH_NCELL_FB_SB_READ_STRU */
    ID_MPH_STOP_NCELL_BCCH_READ                     =   0x870b,                 /* _H2ASN_MsgChoice  MPH_STOP_NCELL_BCCH_READ_STRU */
    ID_MPH_NCELL_BCCH_READ                          =   0x870c,                 /* _H2ASN_MsgChoice  MPH_NCELL_BCCH_READ_STRU */
    ID_MPH_SCELL_BCCH_READ                          =   0x870d,                 /* _H2ASN_MsgChoice  MPH_SCELL_BCCH_READ_STRU */
    ID_MPH_FULL_LIST_REQ                            =   0x870e,                 /* _H2ASN_MsgChoice  MPH_FULL_LIST_REQ_STRU */
    ID_MPH_SI_UPDATE_REQ                            =   0x8711,                 /* _H2ASN_MsgChoice  MPH_SI_UPDATE_REQ_STRU */
    ID_MPH_WCDMA_MEAS_REQ                           =   0x8714,                 /* _H2ASN_MsgChoice  MPH_WCDMA_MEAS_REQ_STRU */
    ID_MPH_FULL_LIST_STOP_REQ                       =   0x8715,                 /* _H2ASN_MsgChoice  MPH_FULL_LIST_STOP_REQ_STRU */
    ID_MPH_STOP_NCELL_FB_SB_REQ                     =   0x8716,                 /* _H2ASN_MsgChoice  MPH_STOP_NCELL_FB_SB_REQ_STRU */
    ID_MPH_G_ENH_MEAS_REQ                           =   0x8717,                 /* _H2ASN_MsgChoice  MPH_G_ENH_MEAS_REQ_STRU */
    ID_MPH_G_ENH_MEAS_STOP_REQ                      =   0x8718,                 /* _H2ASN_MsgChoice  MPH_G_ENH_MEAS_STOP_REQ_STRU */
    ID_MPH_UPDATE_PARSE_PAGING_PARA_REQ             =   0x8721,                 /* _H2ASN_MsgChoice  MPH_UPDATE_PARSE_PAGING_PARA_REQ_STRU */
    ID_MPH_NC_MEAS_REPORT_REQ                       =   0x8722,                 /* _H2ASN_MsgChoice  MPH_NC_MEAS_REPORT_REQ_STRU */
    ID_MPH_UPDATE_RESEL_PARA_REQ                    =   0x8723,                 /* _H2ASN_MsgChoice  MPH_UPDATE_RESEL_PARA_REQ_STRU */
    ID_MPH_CELL_INFO_REPORT_REQ                     =   0x8724,                 /* _H2ASN_MsgChoice  MPH_CELL_INFO_REPORT_REQ_STRU */

    /* VENUS EMULATION MODE */
    ID_MPH_PHY_MEA_ISR_STUB                         =   0x8725,                 /* _H2ASN_MsgChoice  MPH_PHY_MEA_ISR_STUB_REQ_STRU */
    ID_MPH_PHY_SYN_ISR_STUB                         =   0x8726,                 /* _H2ASN_MsgChoice  MPH_PHY_SYN_ISR_STUB_REQ_STRU */
    ID_MPH_PHY_CSDEC_ISR_STUB                       =   0x8727,                 /* _H2ASN_MsgChoice  MPH_PHY_CSDEC_ISR_STUB_REQ_STRU */
    ID_MPH_PHY_PSDEC_ISR_STUB                       =   0x8728,                 /* _H2ASN_MsgChoice  MPH_PHY_PSDEC_ISR_STUB_REQ_STRU */

    ID_MPH_UPDATE_DEDICATED_CTRL_PARA_REQ           =   0x8729,                 /* _H2ASN_MsgChoice  MPH_UPDATE_DEDICATED_CTRL_PARA_REQ_STRU */

    ID_MPH_SET_WORK_MODE_REQ                        =   0x8730,                 /* _H2ASN_MsgChoice  MPH_SET_WORK_MODE_REQ_STRU */
    ID_MPH_LTE_MEAS_REQ                             =   0x8731,                 /* _H2ASN_MsgChoice  MPH_LTE_MEAS_REQ_STRU */
    ID_MPH_STOP_MEAS_REQ                            =   0x8732,                 /* _H2ASN_MsgChoice  MPH_STOP_MEAS_REQ_STRU */

    ID_MPH_TA_INFO_REQ                              =   0x8733,                 /* _H2ASN_MsgChoice  MPH_TA_INFO_REQ_STRU */
    ID_MPH_L_BG_SEARCH_REQ                          =   0x8734,                 /* _H2ASN_MsgChoice  MPH_L_BG_SEARCH_REQ_STRU */

    ID_MPH_TDS_MEAS_REQ                             =   0x8735,                 /* _H2ASN_MsgChoice  MPH_TDS_MEAS_REQ_STRU */

    ID_MPH_MEAS_RLT_RPT_CTRL_REQ                    =   0x8736,                 /* _H2ASN_MsgChoice  MPH_MEAS_RLT_RPT_CTRL_REQ_STRU */

    ID_MPH_NOTCH_CHANNEL_IND                        =   0x8737,                 /* _H2ASN_MsgChoice  MPH_NOTCH_CHANNEL_IND_STRU */
    ID_MPH_BAND_CFG_IND                             =   0x8738,                 /* _H2ASN_MsgChoice  MPH_BAND_CCFG_IND_STRU */
    ID_MPH_TDS_LTE_RF_CONTROL_IND                   =   0x8739,                 /* _H2ASN_MsgChoice  MPH_TDS_LTE_RF_CONTROL_IND_STRU */

    ID_MPH_RSE_CFG_IND                              =   0x873A,                 /* _H2ASN_MsgChoice  MPH_RSE_CFG_IND_STRU */
    ID_MPH_AS_CONNECTED_STATUS_IND                  =   0x873B,                 /* _H2ASN_MsgChoice  MPH_AS_CONNECTED_STATUS_IND_STRU */
    ID_MPH_RXLEV_STOP_REQ                           =   0x873C,                 /* _H2ASN_MsgChoice  MPH_RXLEV_STOP_REQ_STRU */

    ID_MPH_W_BG_SEARCH_REQ                          =   0x873D,                 /* _H2ASN_MsgChoice  MPH_W_BG_SEARCH_REQ_STRU */
    ID_MPH_G_SLAVE_MEAS_REQ                         =   0x873E,                 /* _H2ASN_MsgChoice  MPH_G_SLAVE_MEAS_REQ_STRU */
    ID_MPH_G_SLAVE_BSIC_VERIFIED_REQ                =   0x873F,                 /* _H2ASN_MsgChoice  MPH_G_SLAVE_BSIC_VERIFIED_REQ_STRU */

    ID_MPH_AS_ACTIVE_DSDS_STATUS_IND                =   0x8740,                 /* _H2ASN_MsgChoice  MPH_AS_ACTIVE_DSDS_STATUS_IND_STRU */

    ID_MPH_UPDATE_BCCH_READING_REQ                  =   0x8741,                 /* _H2ASN_MsgChoice  MPH_UPDATE_BCCH_READING_REQ_STRU */
    ID_MPH_UPDATE_PAGE_PARA_REQ                     =   0x8742,                 /* _H2ASN_MsgChoice  MPH_UPDATE_PAGE_PARA_REQ_STRU */

    /* 开机驻留搜索 */
    ID_MPH_CAMP_SCELL_REQ                           =   0x8743,                 /* _H2ASN_MsgChoice  MPH_CAMP_SCELL_REQ_STRU */
    ID_MPH_START_SEARCH_CELL_REQ                    =   0x8744,                 /* _H2ASN_MsgChoice  MPH_START_SEARCH_CELL_REQ_STRU */
    ID_MPH_UPDATE_SEARCH_CELL_REQ                   =   0x8745,                 /* _H2ASN_MsgChoice  MPH_UPDATE_SEARCH_CELL_REQ_STRU */
    ID_MPH_STOP_SEARCH_CELL_REQ                     =   0x8746,                 /* _H2ASN_MsgChoice  MPH_STOP_SEARCH_CELL_REQ_STRU */

    /* 背景搜索 *//* 邻小区读取系统消息 */
    ID_MPH_START_NCELL_BCCH_LIST_READ_REQ           =   0x8747,                 /* _H2ASN_MsgChoice  MPH_START_NCELL_BCCH_LIST_READ_REQ_STRU */
    ID_MPH_UPDATE_NCELL_BCCH_LIST_READ_REQ          =   0x8748,                 /* _H2ASN_MsgChoice  MPH_UPDATE_NCELL_BCCH_LIST_READ_REQ_STRU */
    ID_MPH_STOP_NCELL_BCCH_LIST_READ_REQ            =   0x8749,                 /* _H2ASN_MsgChoice  MPH_STOP_NCELL_BCCH_LIST_READ_REQ_STRU */

    ID_PHY_GAS_MSG_BUTT
}PHY_GAS_MSG_ID_ENUM;
typedef VOS_UINT16 PHY_GAS_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 消息名称  : MPH_RXLEV_CNF_STRU
 功能描述  : 物理层在小区选择状态收到原语MPH_RXLEV_REQ 测量完所有载频后使用原语
              MPH_RXLEV_CNF上报测量结果。该原语应用于小区选择过程中。
 修改历史  :
  1.日    期    : 2007年09月10日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构TBD
*****************************************************************************/
typedef struct
{
     VOS_UINT16                             usFreqInfo;                         /* 其中前4位是频带信息 */
     VOS_UINT16                             usRxlev;                            /* 测量频点的电平，-120+316~ -15+316 */
} RXLEV_MEAS_STRU;



/*****************************************************************************
 消息名称  : MPH_NCELL_FB_SB_READ_STRU
 功能描述  : L1收到该原语后开始读该载频的FB和SB，然后用原语MPH_NCELL_SB_IND报告
             成功或失败，如果成功，就通过该原语提供该邻小区和服务小区的精确时间差。
 修改历史  :
  1.日    期   : 2007年09月10日
    作    者   : fangjian(48555)
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usFreqInfo;
} MPH_NCELL_FB_SB_READ_STRU;


/*****************************************************************************
 消息名称  : MPH_NCELL_SB_IND_STRU
 功能描述  : L1读载频的FB和SB后用原语MPH_NCELL_SB_IND报告成功或失败，如果成功，
             就通过该原语提供该邻小区和服务小区的精确时间差。
 修改历史  :
  1.日    期   : 2007年09月10日
    作    者   : fangjian(48555)
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usFreqInfo;
    VOS_UINT16                              usSBFoundFlag;
    VOS_UINT16                              usBSIC;
    VOS_UINT32                              ulFNOffset;
    VOS_UINT16                              usTimeAlignmt;
    VOS_UINT16                              usErrCode;                          /* 0－Success；1—SB Fail；2—AFC Fail；3—NO RF */
} MPH_NCELL_SB_IND_STRU;

/*****************************************************************************
 消息名称  : MPH_NCELL_BCCH_READ_CNF_STRU
 功能描述  : 对原语 MPH_NCELL_BCCH_READ 的回复
 修改历史  :
  1.日    期   : 2007年09月10日
    作    者   : fangjian(48555)
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usERRCode;
} MPH_NCELL_BCCH_READ_CNF_STRU;


/*****************************************************************************
 消息名称  : MPH_NCELL_BCCH_READ_FAIL_IND_STRU
 功能描述  : 通过该原语向协议栈报告读取邻区系统消息失败
 修改历史  :
  1.日    期   : 2007年10月12日
    作    者   : fangjian(48555)
    修改内容   : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usERRCode;
    VOS_UINT16                              usFreqInfo;
    VOS_UINT16                              usTC;
    VOS_UINT32                              ulFN;
} MPH_NCELL_BCCH_READ_FAIL_IND_STRU;


/*****************************************************************************
 消息名称  : MPH_STOP_NCELL_BCCH_READ_STRU
 功能描述  : 物理层收到原语MPH_STOP_NCELL_BCCH_READ停止读邻区BCCH过程。
 修改历史  :
  1.日    期    : 2007年10月26日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRsv;                              /* 保留位 */
} MPH_STOP_NCELL_BCCH_READ_STRU;



/*****************************************************************************
 消息名称  : MPH_STOP_NCELL_BCCH_READ_CNF
 功能描述  : 该原语是物理层对原语MPH_STOP_NCELL_BCCH_READ的回复，
             WPHY在任何情况下收到后都需要回复。
 修改历史  :
  1.日    期    : 2010年12月14日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRsv;                              /* 保留位 */
} MPH_STOP_NCELL_BCCH_READ_CNF_STRU;


/*****************************************************************************
 消息名称  : MPH_G_ENH_MEAS_REQ_STRU
 功能描述  : 该原语用于处于驻留在GSM模式或者是WCDMA模式时请求物理层进行G的背景搜
             索测量，G物理层通过MPH_G_ENH_MEAS_IND上报测量结果
 修改历史  :
  1.日    期    : 2009年08月20日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usFreqNum;                          /* 频率列表中频点的数目*/
    VOS_UINT16                              astFreqInfo[MAX_ENH_MEAS_G_CARRIER_NUM];/* 其中前4位是频带信息 */
} MPH_G_ENH_MEAS_REQ_STRU;


/*****************************************************************************
 消息名称  : MPH_G_ENH_MEAS_CNF_STRU
 功能描述  : MPH_G_ENH_MEAS_REQ的确认原语，目前在W背景搜G的场景下，默认回复成功。
 修改历史  :
  1.日    期    : 2009年08月20日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usResult;                           /* 0:成功，1：失败 */
} MPH_G_ENH_MEAS_CNF_STRU;


/*****************************************************************************
 消息名称  : MPH_G_ENH_MEAS_STOP_REQ_STRU
 功能描述  : 该原语用于请求物理层停止G模的频点测量，状态转换时物理层清除相关背景搜索任务，
             GAS不针对此种情况发送停止背景搜索原语。
 修改历史  :
  1.日    期    : 2009年08月20日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRsv;
} MPH_G_ENH_MEAS_STOP_REQ_STRU;


/*****************************************************************************
 消息名称  : MPH_G_ENH_MEAS_STOP_CNF_STRU
 功能描述  : MPH_G_ENH_MEAS_STOP_REQ的确认原语。
 修改历史  :
  1.日    期    : 2009年08月20日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRsv;
} MPH_G_ENH_MEAS_STOP_CNF_STRU;


/*****************************************************************************
 消息名称  :  MPH_G_ENH_MEAS_IND_STRU
 功能描述  :  物理层进行GAS频点的背景搜索测量的结果上报，GDSP每次最多上报32个
 修改历史  :
  1.日    期    : 2009年10月23日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
  2.日    期    : 2014年02月12日
    作    者    : y00142674
    修改内容    : 扫频结果上报最大个数由10调整为32

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usFreqNum;                          /* 结果列表中的数目 */
    RXLEV_MEAS_STRU                         astRxlevResult[SEARCH_SEND_FREQ_INFO_NUM];
} MPH_G_ENH_MEAS_IND_STRU;

/*****************************************************************************
 消息名称  : MPH_FULL_LIST_STOP_REQ_STRU
 功能描述  : 该原语用于请求物理层停止G模的FULL LIST频点测量，状态转换时物理层清除
             相关背景搜索任务，但也需要响应该条原语。
 修改历史  :
  1.日    期    : 2013年06月24日
    作    者    : fangjian(48555)
    修改内容    : 问题单DTS2013061705150新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRsv;
} MPH_FULL_LIST_STOP_REQ_STRU;

/*****************************************************************************
 消息名称  : MPH_FULL_LIST_STOP_CNF_STRU
 功能描述  : MPH_FULL_LIST_STOP_REQ的确认原语。
 修改历史  :
  1.日    期    : 2013年06月24日
    作    者    : fangjian(48555)
    修改内容    : 问题单DTS2013061705150新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRsv;
} MPH_FULL_LIST_STOP_CNF_STRU;

/*****************************************************************************
 消息名称  : MPH_STOP_NCELL_FB_SB_REQ_STRU
 功能描述  : 该原语主要用于驻留在W模时GAS同步定时器超时时请求停止WPHY停止目标小区搜索。
 修改历史  :
  1.日    期    : 2010年10月14日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usFreqInfo;                         /* 小区频点，包含频段MARK */
} MPH_STOP_NCELL_FB_SB_REQ_STRU;


/*****************************************************************************
 消息名称  : MPH_STOP_NCELL_FB_SB_CNF_STRU
 功能描述  : 该原语是对MPH_STOP_NCELL_FB_SB_REQ的回复，WPHY在任何情况下收到后都需要回复。
 修改历史  :
  1.日    期    : 2010年10月14日
    作    者    : fangjian(48555)
    修改内容    : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRsved;                            /* 填充字段 */
} MPH_STOP_NCELL_FB_SB_CNF_STRU;




/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __PHYGASCOMM_H__ */

