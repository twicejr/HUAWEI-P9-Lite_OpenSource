/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LRrcPhyInterface.h
  Description     : LRRC和LRTT接口文件
  History         :
     1.lidui 143774       2011-2-14     Draft Enact
     2.lishangfeng  55206 2011-09-11 DTS2011091100356:候补信息维护策略改进，并且能够支持多Band时的维护
******************************************************************************/
#ifndef __LRRCLPHYINTERFACE_H__
#define __LRRCLPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#include "LPSCommon.h"
#endif
#include "TLPhyInterface.h"

/**/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


#ifdef LPS_RTT
#define VOS_MSG_HEADER
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/
/* MBMS begin */
#define LRRC_LPHY_MAX_NUM_OF_MBSFN_AREA                        8
#define LRRC_LPHY_MAX_NUM_OF_MBSFN_ALLOC                       8
#define LRRC_LPHY_MAX_NUM_OF_PMCH_PER_MBSFN                   15
/* MBMS end */
/* 协议栈下发给物理层最大的候补小区数目 */
#define    LRRC_LPHY_MAX_CANDIDATE_CELL_NUM                   32

/* 一次最多建立或者释放的信道个数 */
#define    LRRC_LPHY_MAX_CHANNEL_NUM                          8

/* UE支持的同频或异频小区最大数目 */
#define    LRRC_LPHY_MAX_FREQ_CELL_NUM                        33

#define    LRRC_LPHY_REPORT_MAX_FREQ_CELL_NUM                 18


/* V7R5之前的版本，:
   主模非LTE模时，UE支持的异频的最大数目是4，
   主模为LTE模时，UE支持的异频的最大数目是3 */
/* V7R5以及之后的版本:
   主模非LTE模时，UE支持的异频的最大数目是9，
   主模为LTE模时，UE支持的异频的最大数目是8 */
#define    LRRC_LPHY_MAX_ADDITIONAL_CARRIER_NUM               9

/* UE 配置 SI 消息的最大数目 */
#define LRRC_LPHY_MAX_SI_CONFIG_NUM                           32

/* 协议栈配置的最大N1_PUCCH_AN_PERSISTENT数目 */
#define LRRC_LPHY_MAX_N1_PUCCH_AN_PERSISTENT_NUM              4

/* V7R2支持下行单 CA,
   V7R5支持下行3 CC, 以及上行CA*/
#if ((FEATURE_ON == FEATURE_LTE_R11)&&(!defined(TL_PHY_ASIC_V850)))
#define LRRC_LPHY_MAX_SECONDARY_CARRIER_NUM                   3
#else
#define LRRC_LPHY_MAX_SECONDARY_CARRIER_NUM                   1
#endif


#define LRRC_LPHY_MAX_N3_PUCCH_AN_LIST_NUM                    4
#define LRRC_LPHY_MAX_N3_PUCCH_AN_LIST_P1_NUM                 4
#define LRRC_LPHY_MAX_N1_PUCCH_AN_CS_LIST_NUM                 2
#define LRRC_LPHY_MAX_N1_PUCCH_AN_CS_NUM                      4
#define LRRC_LPHY_MAX_SRS_CFG_AP_DCI_FORMAT4_NUM              3


/* 物理层上报扫频结果的最大频段数 */
#define LRRC_LPHY_MAX_SCAN_FREQ_NUM                           100

/* Maximum number of MBSFN frame allocations with different offset */
#define LRRC_LPHY_MAX_MBSFN_ALLOCATIONS_NUM                   8

/* BSIC的最大列表 */
#define LRRC_LPHY_MAX_BSIC_NUM                                8

/* 地址环BUF最多记录的消息个数 */
#define LRRC_LPHY_MBX_SLAVE_ADDR_QUEUE_BUF_MAX               16

/* 限制地址环最多记录的消息个数 */
#define LRRC_LPHY_MBX_SLAVE_ADDR_QUEUE_MAX   3

/* LCS Begin */
#define LRRC_LPHY_ECID_MAX_NEIGHBOUR_CELL_NUM               32
#define LRRC_LPHY_OTDOA_MAX_NEIGHBOUR_CELL_NUM              (3 * 24)            /*OTDOA测量辅助消息中邻区列表中最大邻区数*/
#define LRRC_LPHY_OTDOA_MAX_FREQ_LAYER_NUM                  4                   /*RSTD测量辅助消息中最大的频率层数*/
#define LRRC_LPHY_OTDOA_MAX_NEIGHBOUR_CELL_NUM_PER_LAYER    24                  /*每个频率层最大邻居小区数*/
#define LRRC_LPHY_OTDOA_MAX_RSTD_FREQ_NUM                   3                   /*最大的RSTD异频测量频率数*/
#define LRRC_LPHY_RF_DCOC_RPT_DATA_SIZE                     12
#define LRRC_LPHY_RF_TXIQ_RPT_DATA_SIZE                     4
#define LRRC_LPHY_QUERY_SELF_ADJUST_PARA_MAX_BAND_NUM       3


/* LCS End */
/* TCXo */
#define LRRC_LPHY_TCX0_RSRP_THRESHOLD                            (-120 * 8)
/* 从模下发邮箱长度，单位:字,2.5Kword */
#define LRRC_LPHY_SLAVE_DOWN_MAILBOX_MSG_LEN ((LPHY_MAILBOX_LHPA_DOWN_SIZE - sizeof(LRRC_LPHY_SLAVE_MAILBOX_HEAD_STRU))/4)

/* 从模上报邮箱长度，单位:字,1.5Kword */
#define LRRC_LPHY_SLAVE_UP_MAILBOX_MSG_LEN  ((LPHY_MAILBOX_LHPA_UP_SIZE - sizeof(LRRC_LPHY_SLAVE_MAILBOX_HEAD_STRU))/4)

#define ERRC_LPHY_MSG_HDR                (0x000008C0)         /* PS_MSG_ID_ERRC_TO_LPHY_BASE begin with 2240 */
#define LPHY_ERRC_MSG_HDR                (0x00000900)         /* PS_MSG_ID_LPHY_TO_ERRC_BASE begin with 2304 */
#define ERMM_LPHY_MSG_HDR                (0x00000940)         /* PS_MSG_ID_ERMM_TO_LPHY_BASE begin with 2368 */
#define LPHY_ERMM_MSG_HDR                (0x00000980)         /* PS_MSG_ID_LPHY_TO_ERMM_BASE begin with 2432 */

/*寻呼下移特性begin*/
#define LRRC_LPHY_MAX_NUM_OF_IMSI_DSP      21
/* sunyanjie begin */
#define LRRC_LPHY_MAX_CELL_NUM            5
/* sunyanjie end */

/*物理层一次请求写入NV最大个数*/
#define LRRC_LPHY_MAX_NV_WRITE_NUM        4

#define LRRC_LPHY_MAX_CELL_REPORT_NUM                         8

#define LRRC_LPHY_MAX_RE_MAP_QCL_NUM                          4

#define LRRC_LPHY_MAX_CSI_RS_NZP_NUM                          3

#define LRRC_LPHY_MAX_CSI_RS_ZP_NUM                           4

#define LRRC_LPHY_MAX_CQI_PROC_EXT_NUM                        3

#define LRRC_LPHY_MAX_CSI_IM_NUM                              3

#define LRRC_LPHY_MAX_CSI_PROC_NUM                            4

#define LRRC_LPHY_MAX_STAG_NUM                                3

#define LRRC_LPHY_MAX_N1_PUCCH_AN_CS_LIST_P1_NUM              4

#define LRRC_LPHY_FREQ_RSSI_MAX_SCAN_NUM                      64

#define LRRC_LPHY_MAX_NUM_OF_BANDS                    (64)



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : LRRC_LPHY_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LRRC -> LPHY 接口消息ID
*****************************************************************************/
enum LRRC_LPHY_MSG_ID_ENUM
{
    /* RRC发给物理层的原语 */
    ID_LRRC_LPHY_CELL_SEARCHING_REQ               = (ERMM_LPHY_MSG_HDR + 0x00), /* _H2ASN_MsgChoice LRRC_LPHY_CELL_SEARCHING_REQ_STRU */
    ID_LRRC_LPHY_CAMPED_MAINCELL_REQ              = (ERRC_LPHY_MSG_HDR + 0x01), /* _H2ASN_MsgChoice LRRC_LPHY_CAMPED_MAINCELL_REQ_STRU */
    ID_LRRC_LPHY_RL_SETUP_REQ                     = (ERRC_LPHY_MSG_HDR + 0x02), /* _H2ASN_MsgChoice LRRC_LPHY_RL_SETUP_REQ_STRU */
    ID_LRRC_LPHY_RL_RELEASE_REQ                   = (ERRC_LPHY_MSG_HDR + 0x03), /* _H2ASN_MsgChoice LRRC_LPHY_RL_RELEASE_REQ_STRU */
    ID_LRRC_LPHY_MEAS_IN_IDLE_REQ                 = (ERMM_LPHY_MSG_HDR + 0x04), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_IN_IDLE_REQ_STRU */
    ID_LRRC_LPHY_MEAS_IN_CONNECTED_REQ            = (ERMM_LPHY_MSG_HDR + 0x05), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_IN_CONNECTED_REQ_STRU */
    ID_LRRC_LPHY_MEAS_GAP_CONFIG_REQ              = (ERMM_LPHY_MSG_HDR + 0x06), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_GAP_CONFIG_REQ_STRU */
    ID_LRRC_LPHY_REL_ALL_REQ                      = (ERRC_LPHY_MSG_HDR + 0x07), /* _H2ASN_MsgChoice LRRC_LPHY_RELALL_REQ_STRU */
    ID_LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_REQ      = (ERRC_LPHY_MSG_HDR + 0x08), /* _H2ASN_MsgChoice LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_REQ_STRU */
    ID_LRRC_LPHY_SRS_CONFIG_REQ                   = (ERRC_LPHY_MSG_HDR + 0x09), /* _H2ASN_MsgChoice LRRC_LPHY_SRS_CONFIG_REQ_STRU */
    ID_LRRC_LPHY_HO_REQ                           = (ERRC_LPHY_MSG_HDR + 0x0a), /* _H2ASN_MsgChoice LRRC_LPHY_HO_REQ_STRU */
    ID_LRRC_LPHY_CQI_CONFIG_REQ                   = (ERRC_LPHY_MSG_HDR + 0x0b), /* _H2ASN_MsgChoice LRRC_LPHY_CQI_CONFIG_REQ_STRU */
    ID_LRRC_LPHY_UPLINK_MAXTXPWR_REQ              = (ERRC_LPHY_MSG_HDR + 0x0c), /* _H2ASN_MsgChoice LRRC_LPHY_UPLINK_MAXTXPWR_REQ_STRU */
    ID_LRRC_LPHY_SYNC_REQ                         = (ERRC_LPHY_MSG_HDR + 0x0d), /* _H2ASN_MsgChoice LRRC_LPHY_SYNC_REQ_STRU */
    ID_LRRC_LPHY_SI_CONFIG_REQ                    = (ERMM_LPHY_MSG_HDR + 0x0e), /* _H2ASN_MsgChoice LRRC_LPHY_SI_CONFIG_REQ_STRU */
    ID_LRRC_LPHY_DRX_GATECLOCK_IND                = (ERRC_LPHY_MSG_HDR + 0x0f), /* _H2ASN_MsgChoice LRRC_LPHY_CONFIG_DRX_GATECLOCK_IND_STRU */
    ID_LRRC_LPHY_TCXO_QUERY_REQ                   = (ERMM_LPHY_MSG_HDR + 0x10), /* _H2ASN_MsgChoice LRRC_LPHY_TCXO_QUERY_REQ_STRU */
    ID_LRRC_LPHY_BAND_SCAN_REQ                    = (ERMM_LPHY_MSG_HDR + 0x11), /* _H2ASN_MsgChoice LRRC_LPHY_BAND_SCAN_REQ_STRU */
    ID_LRRC_LPHY_SET_WORK_MODE_REQ                = (ERRC_LPHY_MSG_HDR + 0x12), /* _H2ASN_MsgChoice LRRC_LPHY_SET_WORK_MODE_REQ_STRU */
    ID_LRRC_LPHY_BSIC_VERIFY_REQ                  = (ERMM_LPHY_MSG_HDR + 0x13), /* _H2ASN_MsgChoice LRRC_LPHY_BSIC_VERIFY_REQ_STRU */
    /* MBMS Begin */
    ID_LRRC_LPHY_MBSFN_MCCH_CFG_REQ               = (ERRC_LPHY_MSG_HDR + 0x14), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_MCCH_CFG_REQ_STRU*/
    ID_LRRC_LPHY_MBSFN_NOTIFY_CFG_REQ             = (ERRC_LPHY_MSG_HDR + 0x15), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_NOTIFY_CFG_REQ_STRU*/
    ID_LRRC_LPHY_MBSFN_PMCH_CFG_REQ               = (ERRC_LPHY_MSG_HDR + 0x16), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_PMCH_CFG_REQ_STRU*/
    ID_LRRC_LPHY_MBSFN_SUBFRAME_CFG_REQ           = (ERRC_LPHY_MSG_HDR + 0x17), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_SUBFRAME_CFG_REQ_STRU*/
    /* MBMS End */

    /* LCS Begin */
    ID_LRRC_LPHY_OTDOA_REQ                        = (ERMM_LPHY_MSG_HDR + 0x18), /* _H2ASN_MsgChoice LRRC_LPHY_OTDOA_REQ_STRU */
    /* LCS End */

    ID_LRRC_LPHY_SWTICH_IND                       = (ERRC_LPHY_MSG_HDR + 0x1a), /* _H2ASN_MsgChoice LRRC_LPHY_SWITCH_IND_STRU */

    /* lishangfeng bg search begin */
    ID_LRRC_LPHY_BG_SEARCH_START_REQ              = (ERMM_LPHY_MSG_HDR + 0x1b), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_START_REQ_STRU */
    ID_LRRC_LPHY_BG_SEARCH_STOP_REQ               = (ERMM_LPHY_MSG_HDR + 0x1c), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_STOP_REQ_STRU */
    ID_LRRC_LPHY_BG_SEARCH_SUSPEND_REQ            = (ERMM_LPHY_MSG_HDR + 0x1d), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_SUSPEND_REQ_STRU */
    ID_LRRC_LPHY_BG_SEARCH_RESUME_REQ             = (ERMM_LPHY_MSG_HDR + 0x1e), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_RESUME_REQ_STRU */

    /* lishangfeng bg search end */

    /* lishangfeng Anr search begin */
    ID_LRRC_LPHY_ANR_START_REQ                    = (ERMM_LPHY_MSG_HDR + 0x1f), /* _H2ASN_MsgChoice LRRC_LPHY_ANR_START_REQ_STRU */
    ID_LRRC_LPHY_ANR_STOP_REQ                     = (ERMM_LPHY_MSG_HDR + 0x20), /* _H2ASN_MsgChoice LRRC_LPHY_ANR_STOP_REQ_STRU */
    /* lishangfeng Anr search end */

    ID_LRRC_LPHY_QUERY_SELF_ADJUST_PARA_REQ      = (ERRC_LPHY_MSG_HDR + 0x21), /* _H2ASN_MsgChoice LRRC_LPHY_QUERY_SELF_ADJUST_PARA_REQ_STRU */

    /*寻呼下移特性begin*/
    ID_LRRC_LPHY_PAGING_INFO_REQ                 = (ERRC_LPHY_MSG_HDR + 0x22), /* _H2ASN_MsgChoice LRRC_LPHY_PAGING_INFO_REQ_STRU */
    /*寻呼下移特性end*/

    ID_LRRC_LPHY_NOTCH_REQ                       = (ERRC_LPHY_MSG_HDR + 0x23), /* _H2ASN_MsgChoice LRRC_LPHY_NOTCH_REQ_STRU */

    ID_LRRC_LPHY_DPDT_CMD_REQ                   = (ERRC_LPHY_MSG_HDR + 0x24),

    ID_LRRC_LPHY_NV_WRITE_RSP                      = (ERRC_LPHY_MSG_HDR + 0x25),

    ID_LRRC_LPHY_STAG_CONFIG_REQ                  = (ERRC_LPHY_MSG_HDR + 0x26), /* _H2ASN_MsgChoice LRRC_LPHY_STAG_CONFIG_REQ_STRU */
    /*begin: hifi sync switch */
    ID_LRRC_LPHY_HIFI_SYNC_SWITCH_IND             = (ERRC_LPHY_MSG_HDR + 0x28),   /* _H2ASN_MsgChoice LRRC_LPHY_HIFI_SYNC_SWITCH_IND_STRU */
    /*end: hifi sync switch */
    ID_LRRC_LPHY_FREQ_RSSI_SCAN_REQ               = (ERMM_LPHY_MSG_HDR + 0x29),   /* _H2ASN_MsgChoice LRRC_LPHY_FREQ_RSSI_SCAN_REQ_STRU */

    ID_LRRC_LPHY_MBMS_ENABLE_REQ                  = (ERRC_LPHY_MSG_HDR + 0x27), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_ENABLE_REQ_STRU */
    ID_LRRC_LPHY_MBMS_DISABLE_REQ                 = (ERRC_LPHY_MSG_HDR + 0x2a), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_DISABLE_REQ_STRU */
    ID_LRRC_LPHY_MBMS_PMCH_ACTIVE_REQ             = (ERRC_LPHY_MSG_HDR + 0x2b), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_PMCH_ACTIVE_REQ_STRU */
    ID_LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_REQ       = (ERRC_LPHY_MSG_HDR + 0x2c), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_REQ_STRU */
    ID_LRRC_LPHY_MBMS_MRS_MEAS_IND                = (ERRC_LPHY_MSG_HDR + 0x2d), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_MRS_MEAS_IND_STRU */
    ID_LRRC_LPHY_MBMS_RCV_ALL_MCCH_IND            = (ERRC_LPHY_MSG_HDR + 0x2e), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_RCV_ALL_MCCH_IND_STRU */
    ID_LRRC_LPHY_CONNECTED_TO_IDLE_REQ            = (ERRC_LPHY_MSG_HDR + 0x2f), /* _H2ASN_MsgChoice LRRC_LPHY_CONNECTED_TO_IDLE_REQ_STRU */

    ID_LRRC_LPHY_RLF_PARA_NOTIFY                  = (ERRC_LPHY_MSG_HDR + 0x30), /* _H2ASN_MsgChoice LRRC_LPHY_RLF_PARA_NOTIFY_STRU */

    /* 物理层发给RRC的原语 */
    ID_LRRC_LPHY_CELL_SEARCHING_IND               = (LPHY_ERMM_MSG_HDR + 0x00), /* _H2ASN_MsgChoice LRRC_LPHY_CELL_SEARCHING_IND_STRU */
    ID_LRRC_LPHY_CAMPED_MAINCELL_CNF              = (LPHY_ERRC_MSG_HDR + 0x01), /* _H2ASN_MsgChoice LRRC_LPHY_CAMPED_MAINCELL_CNF_STRU */
    ID_LRRC_LPHY_RL_SETUP_CNF                     = (LPHY_ERRC_MSG_HDR + 0x02), /* _H2ASN_MsgChoice LRRC_LPHY_RL_SETUP_CNF_STRU */
    ID_LRRC_LPHY_RL_RELEASE_CNF                   = (LPHY_ERRC_MSG_HDR + 0x03), /* _H2ASN_MsgChoice LRRC_LPHY_RL_RELEASE_CNF_STRU */
    ID_LRRC_LPHY_SYNC_IND                         = (LPHY_ERRC_MSG_HDR + 0x04), /* _H2ASN_MsgChoice LRRC_LPHY_SYNC_IND_STRU */
    ID_LRRC_LPHY_MEAS_IN_IDLE_CNF                 = (LPHY_ERMM_MSG_HDR + 0x05), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_IN_IDLE_CNF_STRU */
    ID_LRRC_LPHY_MEAS_IN_IDLE_IND                 = (LPHY_ERMM_MSG_HDR + 0x06), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_IN_IDLE_IND_STRU */
    ID_LRRC_LPHY_MEAS_IN_CONNECTED_CNF            = (LPHY_ERMM_MSG_HDR + 0x07), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_IN_CONNECTED_CNF_STRU */
    ID_LRRC_LPHY_MEAS_IN_CONNECTED_IND            = (LPHY_ERMM_MSG_HDR + 0x08), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_IN_CONNECTED_IND_STRU */
    ID_LRRC_LPHY_REL_ALL_CNF                      = (LPHY_ERRC_MSG_HDR + 0x09), /* _H2ASN_MsgChoice LRRC_LPHY_RELALL_CNF_STRU */
    ID_LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_CNF      = (LPHY_ERRC_MSG_HDR + 0x0a), /* _H2ASN_MsgChoice LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_CNF_STRU */
    ID_LRRC_LPHY_SRS_CONFIG_CNF                   = (LPHY_ERRC_MSG_HDR + 0x0b), /* _H2ASN_MsgChoice LRRC_LPHY_SRS_CONFIG_CNF_STRU */
    ID_LRRC_LPHY_HO_CNF                           = (LPHY_ERRC_MSG_HDR + 0x0c), /* _H2ASN_MsgChoice LRRC_LPHY_HO_CNF_STRU */
    ID_LRRC_LPHY_CQI_CONFIG_CNF                   = (LPHY_ERRC_MSG_HDR + 0x0d), /* _H2ASN_MsgChoice LRRC_LPHY_CQI_CONFIG_CNF_STRU */
    ID_LRRC_LPHY_MEAS_GAP_CONFIG_CNF              = (LPHY_ERMM_MSG_HDR + 0x0e), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_GAP_CONFIG_CNF_STRU */
    ID_LRRC_LPHY_OUT_OF_SYNC_IND                  = (LPHY_ERRC_MSG_HDR + 0x0f), /* _H2ASN_MsgChoice LRRC_LPHY_OUT_OF_SYNC_IND_STRU */
    ID_LRRC_LPHY_SYNC_CNF                         = (LPHY_ERRC_MSG_HDR + 0x10), /* _H2ASN_MsgChoice LRRC_LPHY_SYNC_CNF_STRU */
    ID_LRRC_LPHY_SI_CONFIG_CNF                    = (LPHY_ERMM_MSG_HDR + 0x11), /* _H2ASN_MsgChoice LRRC_LPHY_SI_CONFIG_CNF_STRU */
    ID_LRRC_LPHY_TCXO_QUERY_CNF                   = (LPHY_ERMM_MSG_HDR + 0x12), /* _H2ASN_MsgChoice LRRC_LPHY_TCXO_QUERY_CNF_STRU */
    ID_LRRC_LPHY_BAND_SCAN_IND                    = (LPHY_ERMM_MSG_HDR + 0x13), /* _H2ASN_MsgChoice LRRC_LPHY_BAND_SCAN_IND_STRU */
    ID_LRRC_LPHY_SET_WORK_MODE_CNF                = (LPHY_ERRC_MSG_HDR + 0x14), /* _H2ASN_MsgChoice LRRC_LPHY_SET_WORK_MODE_CNF_STRU */
    ID_LRRC_LPHY_BSIC_VERIFY_CNF                  = (LPHY_ERMM_MSG_HDR + 0x15), /* _H2ASN_MsgChoice LRRC_LPHY_BSIC_VERIFY_CNF_STRU */
    ID_LRRC_LPHY_ERROR_IND                        = (LPHY_ERRC_MSG_HDR + 0x16), /* _H2ASN_MsgChoice LRRC_LPHY_ERROR_IND_STRU */
    /* MBMS Begin */
    ID_LRRC_LPHY_MBSFN_MCCH_CFG_CNF               = (LPHY_ERRC_MSG_HDR + 0x17), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_MCCH_CFG_CNF_STRU*/
    ID_LRRC_LPHY_MBSFN_NOTIFY_CFG_CNF             = (LPHY_ERRC_MSG_HDR + 0x18), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_NOTIFY_CFG_CNF_STRU*/
    ID_LRRC_LPHY_MBSFN_PMCH_CFG_CNF               = (LPHY_ERRC_MSG_HDR + 0x19), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_PMCH_CFG_CNF_STRU*/
    ID_LRRC_LPHY_MBSFN_NOTIFY_IND                 = (LPHY_ERRC_MSG_HDR + 0x1a), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_NOTIFY_IND_STRU*/
    ID_LRRC_LPHY_MBSFN_SUBFRAME_CFG_CNF           = (LPHY_ERRC_MSG_HDR + 0x1b), /* _H2ASN_MsgChoice  LRRC_LPHY_MBSFN_SUBFRAME_CFG_CNF_STRU*/
    /* MBMS End */

    /* LCS Begin */
    ID_LRRC_LPHY_OTDOA_CNF                        = (LPHY_ERMM_MSG_HDR + 0x1c), /* _H2ASN_MsgChoice LRRC_LPHY_OTDOA_CNF_STRU */
    ID_LRRC_LPHY_OTDOA_IND                        = (LPHY_ERMM_MSG_HDR + 0x1d), /* _H2ASN_MsgChoice LRRC_LPHY_OTDOA_IND_STRU */
    ID_LRRC_LPHY_LCS_GAP_REQ                      = (LPHY_ERMM_MSG_HDR + 0x1e), /* _H2ASN_MsgChoice LRRC_LPHY_LCS_GAP_REQ_STRU */
    /* LCS End */

    /* lishangfeng bg search begin */
    ID_LRRC_LPHY_BG_SEARCH_START_CNF              = (LPHY_ERMM_MSG_HDR + 0x1f), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_START_CNF_STRU */
    ID_LRRC_LPHY_BG_SEARCH_STOP_CNF               = (LPHY_ERMM_MSG_HDR + 0x20), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_STOP_CNF_STRU */
    ID_LRRC_LPHY_BG_SEARCH_SUSPEND_CNF            = (LPHY_ERMM_MSG_HDR + 0x21), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_SUSPEND_CNF_STRU */
    ID_LRRC_LPHY_BG_SEARCH_RESUME_CNF             = (LPHY_ERMM_MSG_HDR + 0x22), /* _H2ASN_MsgChoice LRRC_LPHY_BG_SEARCH_RESUME_CNF_STRU */
    /* lishangfeng bg search end */

    /* lishangfeng Anr search begin */
    ID_LRRC_LPHY_ANR_START_CNF                    = (LPHY_ERMM_MSG_HDR + 0x23), /* _H2ASN_MsgChoice LRRC_LPHY_ANR_START_CNF_STRU */
    ID_LRRC_LPHY_ANR_STOP_CNF                     = (LPHY_ERMM_MSG_HDR + 0x24), /* _H2ASN_MsgChoice LRRC_LPHY_ANR_STOP_CNF_STRU */
    /* lishangfeng Anr search end */

    ID_LRRC_LPHY_QUERY_SELF_ADJUST_PARA_CNF       = (LPHY_ERRC_MSG_HDR + 0x25), /* _H2ASN_MsgChoice LRRC_LPHY_QUERY_SELF_ADJUST_PARA_CNF_STRU */

    /* NMR begin */
    ID_LRRC_LPHY_MEAS_INFO_IND                    = (LPHY_ERMM_MSG_HDR + 0x26), /* _H2ASN_MsgChoice LRRC_LPHY_MEAS_INFO_IND_STRU */
    /* NMR end */

    /* sunyanjie begin */
    ID_LRRC_LPHY_ERROR_LOG_IND                    = (LPHY_ERMM_MSG_HDR + 0x27), /* _H2ASN_MsgChoice LRRC_LPHY_ERROR_LOG_INFO_IND_STRU */
    /* sunyanjie end */

    ID_LRRC_LPHY_DPDT_CMD_IND                     = (LPHY_ERRC_MSG_HDR + 0x28),

    ID_LRRC_LPHY_NV_WRITE_IND                     = (LPHY_ERRC_MSG_HDR + 0x29),

    ID_LRRC_LPHY_NORF_INFO_IND                    = (LPHY_ERRC_MSG_HDR + 0x2A),   /* _H2ASN_MsgChoice LRRC_LPHY_NORF_INFO_IND  */

    ID_LRRC_LPHY_STAG_CONFIG_CNF                  = (LPHY_ERRC_MSG_HDR + 0x2b), /* _H2ASN_MsgChoice LRRC_LPHY_STAG_CONFIG_CNF_STRU */
    /*begin: hifi sync switch */
    ID_LRRC_LPHY_VOICE_SYNC_IND                  = (LPHY_ERRC_MSG_HDR + 0x2d),   /* _H2ASN_MsgChoice LRRC_LPHY_VOICE_SYNC_IND_STRU */
    /*end: hifi sync switch */
    ID_LRRC_LPHY_FREQ_RSSI_SCAN_IND              = (LPHY_ERMM_MSG_HDR + 0x2e),    /* _H2ASN_MsgChoice LRRC_LPHY_FREQ_RSSI_SCAN_IND_STRU */
    ID_LRRC_LPHY_MBMS_ENABLE_CNF                  = (LPHY_ERRC_MSG_HDR + 0x2c), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_ENABLE_CNF_STRU */
    ID_LRRC_LPHY_MBMS_DISABLE_CNF                 = (LPHY_ERRC_MSG_HDR + 0x2f), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_DISABLE_CNF_STRU */
    ID_LRRC_LPHY_MBMS_PMCH_ACTIVE_CNF             = (LPHY_ERRC_MSG_HDR + 0x30), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_PMCH_ACTIVE_CNF_STRU */
    ID_LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_CNF       = (LPHY_ERRC_MSG_HDR + 0x31), /* _H2ASN_MsgChoice LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_CNF_STRU */
    ID_LRRC_LPHY_CONNECTED_TO_IDLE_CNF            = (LPHY_ERRC_MSG_HDR + 0x32), /* _H2ASN_MsgChoice LRRC_LPHY_CONNECTED_TO_IDLE_CNF_STRU */
    ID_LRRC_LPHY_BUTT =  (LPHY_ERMM_MSG_HDR + 0x40)                             /*消息结构只能到 0x40*/
};
typedef VOS_UINT32    LRRC_LPHY_MSG_ID_ENUM_UINT32;

/*sunyanjie begin*/
/*****************************************************************************
 枚举名    :
 协议表格  :
 ASN.1描述 :
 枚举说明  : ERROE LOG 上报
*****************************************************************************/
typedef struct
{
    VOS_UINT32                     ulAckCnt;
    VOS_UINT32                     ulNackCnt;
}PUSCH_BLER_STRU;

typedef struct
{
    VOS_UINT16                     ausCWInitTotal[2];
    VOS_UINT16                     ausCWInitError[2];
    VOS_UINT16                     ausCWReTotal[2];
    VOS_UINT16                     ausCWReError[2];
}PDSCH_BLER_STRU;

typedef struct
{
    VOS_UINT32                     ulDlGrantCnt;
    VOS_UINT32                     ulUlGrantCnt;
}PDCCH_BLER_STRU;

typedef struct
{
    VOS_INT16                      sPuschTxPwr;
    VOS_INT16                      sPucchTxPwr;
    VOS_INT16                      sSrsTxPwr;
    VOS_UINT16                     usReserved;
    PUSCH_BLER_STRU                stPuschBlerCnt;
    PDSCH_BLER_STRU                stPdschBlerCnt;
    PDCCH_BLER_STRU                stPdcchBlerCnt;
}TRANS_ERROR_LOG_RPT_STRU;

typedef struct
{
    VOS_UINT32                     ulValidNum;
    TRANS_ERROR_LOG_RPT_STRU       stTransErrorLog[LRRC_LPHY_MAX_CELL_NUM];
}TRANS_ERROR_LOG_INFO_RPT_STRU;
/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 参数上报数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                     /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                    enMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                                      usOpId;
    VOS_UINT16                                      usReserved;
    TRANS_ERROR_LOG_INFO_RPT_STRU                   stTransErrorLogInfo;
}LRRC_LPHY_ERROR_LOG_INFO_IND_STRU;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CELL_SEARCH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 协议栈指示物理层小区搜索类型
*****************************************************************************/
enum LRRC_LPHY_CELL_SEARCH_TYPE_ENUM
{
    LRRC_LPHY_CELL_SEARCH_FREQ            = 0,                /* 频点信息小区的搜索类型*/
    LRRC_LPHY_CELL_SEARCH_CANDIDATE,                          /* 先验信息(频点+小区ID)小区搜索 */
    LRRC_LPHY_CELL_SEARCH_FREQ_BAND,                          /* 频带搜索 */
    LRRC_LPHY_CELL_SEARCH_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CELL_SEARCH_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SEARCH_CELL_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 小区搜索结果
*****************************************************************************/
enum LRRC_LPHY_SEARCH_CELL_RESULT_ENUM
{
    LRRC_LPHY_SEARCH_CELL_INVALID         = 0,                /* 小区搜索结果无效 */
    LRRC_LPHY_SEARCH_CELL_VALID ,                             /* 小区搜索结果有效 */
    LRRC_LPHY_SEARCH_CELL_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SEARCH_CELL_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_ANTANNA_PORT_ENUM
 协议表格  : MobilityControlInformation->RadioResourceConfigCommon->AntennaInformationCommon
 ASN.1描述 :
 枚举说明  : 天线端口数
*****************************************************************************/
enum LRRC_LPHY_ANTANNA_PORT_ENUM
{
    LRRC_LPHY_ANTANNA_PORT_1              = 0,                /* 天线端口为1 */
    LRRC_LPHY_ANTANNA_PORT_2,                                 /* 天线端口为2 */
    LRRC_LPHY_ANTANNA_PORT_4,                                 /* 天线端口为4 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_ANTANNA_PORT_8,                                 /* 天线端口为8 */
#endif
    LRRC_LPHY_ANTANNA_PORT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CSI_ANTANNA_PORT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CSI天线端口数
*****************************************************************************/
enum LRRC_LPHY_CSI_ANTANNA_PORT_ENUM
{
    LRRC_LPHY_CSI_ANTANNA_PORT_1              = 0,                /* 天线端口为1 */
    LRRC_LPHY_CSI_ANTANNA_PORT_2,                                 /* 天线端口为2 */
    LRRC_LPHY_CSI_ANTANNA_PORT_4,                                 /* 天线端口为4 */
    LRRC_LPHY_CSI_ANTANNA_PORT_8,                                 /* 天线端口为8 */
    LRRC_LPHY_CSI_ANTANNA_PORT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CSI_ANTANNA_PORT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SRS_ANTANNA_PORT_ENUM
 协议表格  : SRS-AntennaPort
 ASN.1描述 :
 枚举说明  : SRS天线端口数
*****************************************************************************/
enum LRRC_LPHY_SRS_ANTANNA_PORT_ENUM
{
    LRRC_LPHY_SRS_ANTANNA_PORT_1              = 0,                /* 天线端口为1 */
    LRRC_LPHY_SRS_ANTANNA_PORT_2,                                 /* 天线端口为2 */
    LRRC_LPHY_SRS_ANTANNA_PORT_4,                                 /* 天线端口为4 */
    LRRC_LPHY_SRS_ANTANNA_PORT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SRS_ANTANNA_PORT_ENUM_UINT16;


/*****************************************************************************
 枚举名    : LRRC_LPHY_BAND_WIDTH_ENUM
 协议表格  : MasterInformationBlock->dl-Bandwidth
 ASN.1描述 :
 枚举说明  : 带宽枚举(包括下行系统带宽、测量带宽)
*****************************************************************************/
enum LRRC_LPHY_BAND_WIDTH_ENUM
{
    LRRC_LPHY_BAND_WIDTH_6RB              = 0,                /* 带宽为6RB */
    LRRC_LPHY_BAND_WIDTH_15RB,                                /* 带宽为15RB */
    LRRC_LPHY_BAND_WIDTH_25RB,                                /* 带宽为25RB */
    LRRC_LPHY_BAND_WIDTH_50RB,                                /* 带宽为50RB */
    LRRC_LPHY_BAND_WIDTH_75RB,                                /* 带宽为75RB */
    LRRC_LPHY_BAND_WIDTH_100RB,                               /* 带宽为100RB */
    LRRC_LPHY_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_BAND_WIDTH_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SUBFRAME_ASSIGNMENT_ENUM
 协议表格  : TDD-Configuration->subframeAssignment
 ASN.1描述 :
 枚举说明  : subframeAssignment
*****************************************************************************/
enum LRRC_LPHY_SUBFRAME_ASSIGNMENT_ENUM
{
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_0       = 0,                /* subframeAssignment-sa0 */
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_1,                          /* subframeAssignment-sa1 */
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_2,                          /* subframeAssignment-sa2 */
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_3,                          /* subframeAssignment-sa3 */
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_4,                          /* subframeAssignment-sa4 */
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_5,                          /* subframeAssignment-sa5 */
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_6,                          /* subframeAssignment-sa6 */
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_SUBFRAME_ASSIGNMENT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_ENUM
 协议表格  : TDD-Configuration->specialSubframePatterns
 ASN.1描述 :
 枚举说明  : specialSubframePatterns
*****************************************************************************/
enum LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_ENUM
{
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_0  = 0,                /* specialSubframePatterns-ssp0 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_1,                     /* specialSubframePatterns-ssp1 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_2,                     /* specialSubframePatterns-ssp2 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_3,                     /* specialSubframePatterns-ssp3 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_4,                     /* specialSubframePatterns-ssp4 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_5,                     /* specialSubframePatterns-ssp5 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_6,                     /* specialSubframePatterns-ssp6 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_7,                     /* specialSubframePatterns-ssp7 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_8,                     /* specialSubframePatterns-ssp8 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_9,                     /* specialSubframePatterns-ssp9 */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理层原语操作结果数据结构
*****************************************************************************/
enum LRRC_LPHY_RESULT_ENUM
{
    LRRC_LPHY_RESULT_SUCC                 = 0,                /* 操作成功 */
    LRRC_LPHY_RESULT_FAIL ,                                   /* 操作失败 */
    LRRC_LPHY_RESULT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CHANNEL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理信道的类型
*****************************************************************************/
enum LRRC_LPHY_CHANNEL_TYPE_ENUM
{
    LRRC_LPHY_CHANNEL_PBCH                = 0,                /* 广播信道 */
    LRRC_LPHY_CHANNEL_PDSCH_BCH,                              /* 解广播的下行共享信道 */
    LRRC_LPHY_CHANNEL_PDSCH_PCH,                              /* 解寻呼的下行共享信道 */
    LRRC_LPHY_CHANNEL_PDSCH_RACH,                             /* 解随机接入响应的下行共享信道*/
    LRRC_LPHY_CHANNEL_PDSCH_DSCH,                             /* 解数据的下行共享信道 */
    LRRC_LPHY_CHANNEL_PUCCH,                                  /* 上行控制信道 */
    LRRC_LPHY_CHANNEL_PUSCH,                                  /* 上行共享信道 */
    LRRC_LPHY_CHANNEL_PRACH,                                  /* 随机接入信道 */
    LRRC_LPHY_CHANNEL_PDSCH_SCELL,                            /* SCELL下行共享信道 */
    LRRC_LPHY_CHANNEL_PUSCH_SCELL,                            /* SCELL上行共享信道 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_CHANNEL_PRACH_SCELL,                            /* SCELL随机接入信道 */
#endif
    LRRC_LPHY_CHANNEL_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : LRRC_LPHY_CQI_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CQI配置的类型
*****************************************************************************/
enum LRRC_LPHY_CQI_TYPE_ENUM
{
    LRRC_LPHY_CQI_PCELL                  = 0,                /* PCELL的CQI配置 */
    LRRC_LPHY_CQI_SCELL,                                     /* SCELL的CQI配置 */
    LRRC_LPHY_CQI_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CQI_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_MBSFN_SF_CFG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MBSFN子帧配置的类型
*****************************************************************************/
enum LRRC_LPHY_MBSFN_SF_CFG_TYPE_ENUM
{
    LRRC_LPHY_MBSFN_SF_CFG_PCELL          = 0,                /* PCELL的MBSFN子帧配置 */
    LRRC_LPHY_MBSFN_SF_CFG_SCELL,                             /* SCELL的MBSFN子帧配置 */
    LRRC_LPHY_MBSFN_SF_CFG_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_MBSFN_SF_CFG_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : LRRC_LPHY_PDSCH_SETUP_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 是否要建立PDSCH物理信道的标志
*****************************************************************************/
enum LRRC_LPHY_PDSCH_SETUP_FLAG_ENUM
{
    LRRC_LPHY_PDSCH_SETUP                = 0,                /* 后续建立PDSCH信道 */
    LRRC_LPHY_PDSCH_NOTSETUP,                            /* 后续不建立PDSCH信道 */
    LRRC_LPHY_PDSCH_BUTT
};
typedef VOS_INT16    LRRC_LPHY_PDSCH_SETUP_FLAG_ENUM_INT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PDSCH_TM_MODE_ENUM
 协议表格  : RadioResourceConfigDedicated->PhysicalConfigDedicated->
             AntennaInformationDedicated->transmissionMode
 ASN.1描述 :
 枚举说明  : PDSCH信道传输模式类型
*****************************************************************************/
enum LRRC_LPHY_PDSCH_TM_MODE_ENUM
{
    LRRC_LPHY_PDSCH_TM1                   = 0,                /* 对应为传输模式1 */
    LRRC_LPHY_PDSCH_TM2,                                      /* 对应为传输模式2 */
    LRRC_LPHY_PDSCH_TM3,                                      /* 对应为传输模式3 */
    LRRC_LPHY_PDSCH_TM4,                                      /* 对应为传输模式4 */
    LRRC_LPHY_PDSCH_TM5,                                      /* 对应为传输模式5 */
    LRRC_LPHY_PDSCH_TM6,                                      /* 对应为传输模式6 */
    LRRC_LPHY_PDSCH_TM7,                                      /* 对应为传输模式7 */
    LRRC_LPHY_PDSCH_TM8,                                      /* 对应为传输模式8 */
    LRRC_LPHY_PDSCH_TM9,                                      /* 对应为传输模式9 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_PDSCH_TM10,                                     /* 对应为传输模式10 */
#endif
    LRRC_LPHY_PDSCH_TM_MODE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PDSCH_TM_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CODE_BOOK_TYPE_ENUM
 协议表格  : RadioResourceConfigDedicated->PhysicalConfigDedicated->
             AntennaInformationDedicated->codebookSubsetRestriction
 ASN.1描述 :
 枚举说明  : codebookSubsetRestriction
*****************************************************************************/
enum LRRC_LPHY_CODE_BOOK_TYPE_ENUM
{
    LRRC_LPHY_CODE_BOOK_TYPE_N2TM3        = 0,                /* n2TxAntenna-tm3 */
    LRRC_LPHY_CODE_BOOK_TYPE_N4TM3,                           /* n4TxAntenna-tm3 */
    LRRC_LPHY_CODE_BOOK_TYPE_N2TM4,                           /* n2TxAntenna-tm4 */
    LRRC_LPHY_CODE_BOOK_TYPE_N4TM4,                           /* n4TxAntenna-tm4 */
    LRRC_LPHY_CODE_BOOK_TYPE_N2TM5,                           /* n2TxAntenna-tm5 */
    LRRC_LPHY_CODE_BOOK_TYPE_N4TM5,                           /* n4TxAntenna-tm5 */
    LRRC_LPHY_CODE_BOOK_TYPE_N2TM6,                           /* n2TxAntenna-tm6 */
    LRRC_LPHY_CODE_BOOK_TYPE_N4TM6,                           /* n4TxAntenna-tm6 */
    LRRC_LPHY_CODE_BOOK_TYPE_N2TM8,                           /* n2TxAntenna-tm8 */
    LRRC_LPHY_CODE_BOOK_TYPE_N4TM8,                           /* n4TxAntenna-tm8 */
    LRRC_LPHY_CODE_BOOK_TYPE_N2TM9,                           /* n2TxAntenna-tm9 */
    LRRC_LPHY_CODE_BOOK_TYPE_N4TM9,                           /* n4TxAntenna-tm9 */
    LRRC_LPHY_CODE_BOOK_TYPE_N8TM9,                           /* n8TxAntenna-tm9 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_CODE_BOOK_TYPE_N2TM10,                          /* n2TxAntenna-tm10 */
    LRRC_LPHY_CODE_BOOK_TYPE_N4TM10,                          /* n4TxAntenna-tm10 */
    LRRC_LPHY_CODE_BOOK_TYPE_N8TM10,                          /* n8TxAntenna-tm10 */
#endif
    LRRC_LPHY_CODE_BOOK_TYPE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CODE_BOOK_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_ANTENNA_SELECT_ENUM
 协议表格  : RadioResourceConfigDedicated->PhysicalConfigDedicated->
             AntennaInformationDedicated->ue-TransmitAntennaSelection
 ASN.1描述 :
 枚举说明  : 传输天线选择
*****************************************************************************/
enum LRRC_LPHY_ANTENNA_SELECT_ENUM
{
    LRRC_LPHY_ANTENNA_SELECT_ENABLE_CLOSEDLOOP      = 0,      /* UE选择传输天线为CLOSELOOP */
    LRRC_LPHY_ANTENNA_SELECT_ENABLE_OPENLOOP,                 /* UE选择传输天线为OPENLOOP */
    LRRC_LPHY_ANTENNA_SELECT_DISABLE,                         /* UE不能选择传输天线 */
    LRRC_LPHY_ANTENNA_SELECT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_ANTENNA_SELECT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PDSCH_PA_ENUM
 协议表格  : PDSCH-Configuration->PDSCH-ConfigDedicated->p-a
 ASN.1描述 :
 枚举说明  : PA数据枚举
*****************************************************************************/
enum LRRC_LPHY_PDSCH_PA_ENUM
{
    LRRC_LPHY_PDSCH_PA_NEGATIVE_6         = 0,                /* PA为-6dB */
    LRRC_LPHY_PDSCH_PA_NEGATIVE_4DOT77,                       /* PA为-4.77dB */
    LRRC_LPHY_PDSCH_PA_NEGATIVE_3,                            /* PA为-3dB */
    LRRC_LPHY_PDSCH_PA_NEGATIVE_1DOT77,                       /* PA为-1.77dB */
    LRRC_LPHY_PDSCH_PA_0,                                     /* PA为0dB */
    LRRC_LPHY_PDSCH_PA_1,                                     /* PA为1dB */
    LRRC_LPHY_PDSCH_PA_2,                                     /* PA为2dB */
    LRRC_LPHY_PDSCH_PA_3,                                     /* PA为3dB */
    LRRC_LPHY_PDSCH_PA_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PDSCH_PA_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PDSCH_PB_ENUM
 协议表格  : PDSCH-Configuration->PDSCH-ConfigCommon->p-b
 ASN.1描述 :
 枚举说明  : PB数据枚举
*****************************************************************************/
enum LRRC_LPHY_PDSCH_PB_ENUM
{
    LRRC_LPHY_PDSCH_PB_0         = 0,                         /* PB为0 */
    LRRC_LPHY_PDSCH_PB_1,                                     /* PA为1 */
    LRRC_LPHY_PDSCH_PB_2,                                     /* PA为2 */
    LRRC_LPHY_PDSCH_PB_3,                                     /* PA为3 */
    LRRC_LPHY_PDSCH_PB_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PDSCH_PB_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PARA_VALID_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 用于指示专用参数是否有效
*****************************************************************************/
enum LRRC_LPHY_PARA_VALID_FLAG_ENUM
{
    LRRC_LPHY_PARA_INVALID                = 0,                /* 参数无效 */
    LRRC_LPHY_PARA_VALID ,                                    /* 参数有效 */
    LRRC_LPHY_PARA_FLG_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DELTA_PUCCH_SHITF_ENUM
 协议表格  : PUCCH-ConfigCommon->deltaPUCCH-Shift
 ASN.1描述 :
 枚举说明  : deltaPUCCH-Shift
*****************************************************************************/
enum LRRC_LPHY_DELTA_PUCCH_SHITF_ENUM
{
    LRRC_LPHY_DELTA_PUCCH_SHITF_1         = 1,                /* deltaPUCCH-Shift为1 */
    LRRC_LPHY_DELTA_PUCCH_SHITF_2 ,                           /* deltaPUCCH-Shift为2 */
    LRRC_LPHY_DELTA_PUCCH_SHITF_3 ,                           /* deltaPUCCH-Shift为3 */
    LRRC_LPHY_DELTA_PUCCH_SHITF_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_DELTA_PUCCH_SHITF_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_REPETITION_FACTOR_ENUM
 协议表格  : PUCCH-ConfigDedicated->ackNackRepetition
 ASN.1描述 :
 枚举说明  : ackNackRepetition
*****************************************************************************/
enum LRRC_LPHY_REPETITION_FACTOR_ENUM
{
    LRRC_LPHY_REPETITION_FACTOR_ENABLE_N2  = 0,                /* ackNackRepetition为N2 */
    LRRC_LPHY_REPETITION_FACTOR_ENABLE_N4 ,                    /* ackNackRepetition为N4 */
    LRRC_LPHY_REPETITION_FACTOR_ENABLE_N6 ,                    /* ackNackRepetition为N6 */
    LRRC_LPHY_REPETITION_FACTOR_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_REPETITION_FACTOR_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_TDD_FEEDBACK_MODE_ENUM
 协议表格  : PUCCH-ConfigDedicated->tddAckNackFeedbackMode
 ASN.1描述 :
 枚举说明  : tddAckNackFeedbackMode
*****************************************************************************/
enum LRRC_LPHY_TDD_FEEDBACK_MODE_ENUM
{
    LRRC_LPHY_TDD_FEEDBACK_MODE_BUNDLING  = 0,                /* tddAckNackFeedbackMode为bundling */
    LRRC_LPHY_TDD_FEEDBACK_MODE_MULTIPLEXING ,                /* tddAckNackFeedbackMode为multiplexing */
    LRRC_LPHY_TDD_FEEDBACK_MODE_INVALID,                      /* tddAckNackFeedbackMode为无效 */
    LRRC_LPHY_TDD_FEEDBACK_MODE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_TDD_FEEDBACK_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DSR_TRANS_MAX_ENUM
 协议表格  : PhysicalConfigDedicated->SchedulingRequest-Configuration->dsr-TransMax
 ASN.1描述 :
 枚举说明  : dsr-TransMax
*****************************************************************************/
enum LRRC_LPHY_DSR_TRANS_MAX_ENUM
{
    LRRC_LPHY_DSR_TRANS_MAX_N4            = 0,                /* deltaPUCCH-Shift为N4 */
    LRRC_LPHY_DSR_TRANS_MAX_N8 ,                              /* deltaPUCCH-Shift为N8 */
    LRRC_LPHY_DSR_TRANS_MAX_N16 ,                             /* deltaPUCCH-Shift为N16 */
    LRRC_LPHY_DSR_TRANS_MAX_N32 ,                             /* deltaPUCCH-Shift为N32 */
    LRRC_LPHY_DSR_TRANS_MAX_N64 ,                             /* deltaPUCCH-Shift为N64 */
    LRRC_LPHY_DSR_TRANS_MAX_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_DSR_TRANS_MAX_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PUSCH_HOPPING_MODE_ENUM
 协议表格  : PUSCH-Configuration->PUSCH-ConfigCommon->n-SB
 ASN.1描述 :
 枚举说明  : PUSCH Hopping模式
*****************************************************************************/
enum LRRC_LPHY_PUSCH_HOPPING_MODE_ENUM
{
    LRRC_LPHY_PUSCH_HOPPING_MODE_INTER_SUBFRAME               = 0, /* interSubFrame */
    LRRC_LPHY_PUSCH_HOPPING_MODE_INTER_INTRA_SUBFRAME,             /* intraAndInterSubFrame */
    LRRC_LPHY_PUSCH_HOPPING_MODE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PUSCH_HOPPING_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PUSCH_HOPPING_MODE_ENUM
 协议表格  : PUSCH-Configuration->PUSCH-ConfigCommon->hoppingMode
 ASN.1描述 :
 枚举说明  : PUSCH N SB
*****************************************************************************/
enum LRRC_LPHY_PUSCH_N_SB_ENUM
{
    LRRC_LPHY_PUSCH_N_SB_1                = 0,                /* N SB为NSB1 */
    LRRC_LPHY_PUSCH_N_SB_2,                                   /* N SB为NSB2 */
    LRRC_LPHY_PUSCH_N_SB_3,                                   /* N SB为NSB3 */
    LRRC_LPHY_PUSCH_N_SB_4,                                   /* N SB为NSB4 */
    LRRC_LPHY_PUSCH_N_SB_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PUSCH_N_SB_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM
 协议表格  : PUSCH-Configuration->PUSCH-ConfigCommon->hoppingMode
 ASN.1描述 :
 枚举说明  : PUSCH N SB
*****************************************************************************/
enum LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM
{
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_NORMAL = 0,                /* Normal */
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_EXTEND,                    /* Extended */
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PARA_ENABLE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 参数使能标识
*****************************************************************************/
enum LRRC_LPHY_PARA_ENABLE_ENUM
{
    LRRC_LPHY_PARA_DISABLE                = 0,                /* 不使能 */
    LRRC_LPHY_PARA_ENABLE,                                    /* 使能 */
    LRRC_LPHY_PARA_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_MAX_HARQ_TX_ENUM
 协议表格  : ul-SCH-Config->maxHARQ-Tx
 ASN.1描述 :
 枚举说明  : maxHARQ-Tx
*****************************************************************************/
enum LRRC_LPHY_MAX_HARQ_TX_ENUM
{
    LRRC_LPHY_N1_MAX_HARQ_TX           = 0,              /* 1 */
    LRRC_LPHY_N2_MAX_HARQ_TX,                            /* 2 */
    LRRC_LPHY_N3_MAX_HARQ_TX,                            /* 3 */
    LRRC_LPHY_N4_MAX_HARQ_TX,                            /* 4 */
    LRRC_LPHY_N5_MAX_HARQ_TX,                            /* 5 */
    LRRC_LPHY_N6_MAX_HARQ_TX,                            /* 6 */
    LRRC_LPHY_N7_MAX_HARQ_TX,                            /* 7 */
    LRRC_LPHY_N8_MAX_HARQ_TX,                            /* 8 */
    LRRC_LPHY_N10_MAX_HARQ_TX,                           /* 10 */
    LRRC_LPHY_N12_MAX_HARQ_TX,                           /* 12 */
    LRRC_LPHY_N16_MAX_HARQ_TX,                           /* 16 */
    LRRC_LPHY_N20_MAX_HARQ_TX,                           /* 20 */
    LRRC_LPHY_N24_MAX_HARQ_TX,                           /* 24 */
    LRRC_LPHY_N28_MAX_HARQ_TX,                           /* 28 */
    LRRC_LPHY_MAX_HARQ_TX_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_MAX_HARQ_TX_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PWR_CTRL_ALPHA_ENUM
 协议表格  : RadioResourceConfigCommonSIB->UplinkPowerControlCommon->alpha
             RadioResourceConfigCommon->UplinkPowerControlCommon->alpha
 ASN.1描述 :
 枚举说明  : alpha
*****************************************************************************/
enum LRRC_LPHY_PWR_CTRL_ALPHA_ENUM
{
    LRRC_LPHY_PWR_CTRL_ALPHA_0            = 0,                /* 0 */
    LRRC_LPHY_PWR_CTRL_ALPHA_0DOT4,                           /* 0.4 */
    LRRC_LPHY_PWR_CTRL_ALPHA_0DOT5,                           /* 0.5 */
    LRRC_LPHY_PWR_CTRL_ALPHA_0DOT6,                           /* 0.6 */
    LRRC_LPHY_PWR_CTRL_ALPHA_0DOT7,                           /* 0.7 */
    LRRC_LPHY_PWR_CTRL_ALPHA_0DOT8,                           /* 0.8 */
    LRRC_LPHY_PWR_CTRL_ALPHA_0DOT9,                           /* 0.9 */
    LRRC_LPHY_PWR_CTRL_ALPHA_1,                               /* 1 */
    LRRC_LPHY_PWR_CTRL_ALPHA_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PWR_CTRL_ALPHA_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DELTAF_FORMAT_ENUM
 协议表格  : RadioResourceConfigCommonSIB->UplinkPowerControlCommon->DeltaFList-PUCCH
             RadioResourceConfigCommon->UplinkPowerControlCommon->DeltaFList-PUCCH
 ASN.1描述 :
 枚举说明  : alpha
*****************************************************************************/
enum LRRC_LPHY_DELTAF_FORMAT_ENUM
{
    LRRC_LPHY_DELTAF_FORMAT_NEGATIVE_2    = 0,                /* -2 */
    LRRC_LPHY_DELTAF_FORMAT_0,                                /* 0 */
    LRRC_LPHY_DELTAF_FORMAT_1,                                /* 1 */
    LRRC_LPHY_DELTAF_FORMAT_2,                                /* 2 */
    LRRC_LPHY_DELTAF_FORMAT_3,                                /* 3 */
    LRRC_LPHY_DELTAF_FORMAT_5,                                /* 5 */
    LRRC_LPHY_DELTAF_FORMAT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_DELTAF_FORMAT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_FILTER_COEFF_ENUM
 协议表格  : PhysicalConfigDedicated->uplinkPowerControlDedicated->filterCoefficient
 ASN.1描述 :
 枚举说明  : FilterCoefficient
*****************************************************************************/
enum LRRC_LPHY_FILTER_COEFF_ENUM
{
    LRRC_LPHY_FC0_FILTER_COEFF          = 0,      /* k = 0 */
    LRRC_LPHY_FC1_FILTER_COEFF,                   /* k = 1 */
    LRRC_LPHY_FC2_FILTER_COEFF,                   /* k = 2 */
    LRRC_LPHY_FC3_FILTER_COEFF,                   /* k = 3 */
    LRRC_LPHY_FC4_FILTER_COEFF,                   /* k = 4 */
    LRRC_LPHY_FC5_FILTER_COEFF,                   /* k = 5 */
    LRRC_LPHY_FC6_FILTER_COEFF,                   /* k = 6 */
    LRRC_LPHY_FC7_FILTER_COEFF,                   /* k = 7 */
    LRRC_LPHY_FC8_FILTER_COEFF,                   /* k = 8 */
    LRRC_LPHY_FC9_FILTER_COEFF,                   /* k = 9 */
    LRRC_LPHY_FC11_FILTER_COEFF,                  /* k = 11 */
    LRRC_LPHY_FC13_FILTER_COEFF,                  /* k = 13 */
    LRRC_LPHY_FC15_FILTER_COEFF,                  /* k = 15 */
    LRRC_LPHY_FC17_FILTER_COEFF,                  /* k = 17 */
    LRRC_LPHY_FC19_FILTER_COEFF,                  /* k = 19 */
    LRRC_LPHY_FILTER_COEFF_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_FILTER_COEFF_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_INDEX_FORMAT_TYPE_ENUM
 协议表格  : PhysicalConfigDedicated->TPC-PDCCH-Configuration->TPC-Index
 ASN.1描述 :
 枚举说明  : TPC-Index
*****************************************************************************/
enum LRRC_LPHY_INDEX_FORMAT_TYPE_ENUM
{
    LRRC_LPHY_INDEX_FORMAT_TYPE_3         = 0,                /* indexOfFormat3 */
    LRRC_LPHY_INDEX_FORMAT_TYPE_3A,                           /* indexOfFormat3A */
    LRRC_LPHY_INDEX_FORMAT_TYPE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_INDEX_FORMAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PERSIST_SCHED_INTERVAL_ENUM
 协议表格  : RadioResourceConfigDedicated->SPS-Configuration
 ASN.1描述 :
 枚举说明  : SPS-Configuration->semiPersistSchedIntervalDL/semiPersistSchedIntervalUL
*****************************************************************************/
enum LRRC_LPHY_PERSIST_SCHED_INTERVAL_ENUM
{
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_10         = 0,          /* 10 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_20,                      /* 20 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_32,                      /* 32 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_40,                      /* 40 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_64,                      /* 64 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_80,                      /* 80 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_128,                     /* 128 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_160,                     /* 160 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_320,                     /* 320 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_640,                     /* 640 */
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PERSIST_SCHED_INTERVAL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_IMPLICIT_REL_AFTER_ENUM
 协议表格  : RadioResourceConfigDedicated->SPS-Configuration->semiPersistSchedIntervalUL
 ASN.1描述 :
 枚举说明  : implicitReleaseAfter
*****************************************************************************/
enum LRRC_LPHY_IMPLICIT_REL_AFTER_ENUM
{
    LRRC_LPHY_IMPLICIT_REL_AFTER_E2       = 0,                /* e2 */
    LRRC_LPHY_IMPLICIT_REL_AFTER_E3,                          /* e3 */
    LRRC_LPHY_IMPLICIT_REL_AFTER_E4,                          /* e4 */
    LRRC_LPHY_IMPLICIT_REL_AFTER_E8,                          /* e8 */
    LRRC_LPHY_IMPLICIT_REL_AFTER_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_IMPLICIT_REL_AFTER_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PHICH_DURATION_ENUM
 协议表格  : PHICH-Configuration->phich-Duration
 ASN.1描述 :
 枚举说明  : phich-Duration
*****************************************************************************/
enum LRRC_LPHY_PHICH_DURATION_ENUM
{
    LRRC_LPHY_PHICH_DURATION_NORMAL       = 0,                  /* Normal */
    LRRC_LPHY_PHICH_DURATION_EXTENDED,                          /* extended */
    LRRC_LPHY_PHICH_DURATION_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PHICH_DURATION_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PHICH_RESOURCE_ENUM
 协议表格  : PHICH-Configuration->phich-Resource
 ASN.1描述 :
 枚举说明  : phich-Resource
*****************************************************************************/
enum LRRC_LPHY_PHICH_RESOURCE_ENUM
{
    LRRC_LPHY_PHICH_RESOURCE_ONE_SIXTH    = 0,                /* 1/6 */
    LRRC_LPHY_PHICH_RESOURCE_HALF,                            /* 1/2 */
    LRRC_LPHY_PHICH_RESOURCE_ONE,                             /* 1 */
    LRRC_LPHY_PHICH_RESOURCE_TWO,                             /* 2 */
    LRRC_LPHY_PHICH_RESOURCE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PHICH_RESOURCE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DRX_PAGE_T_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 寻呼周期
*****************************************************************************/
enum LRRC_LPHY_DRX_PAGE_T_ENUM
{
    LRRC_LPHY_DRX_PAGE_32                 =0,
    LRRC_LPHY_DRX_PAGE_64,
    LRRC_LPHY_DRX_PAGE_128,
    LRRC_LPHY_DRX_PAGE_256,
    LRRC_LPHY_DRX_PAGE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_DRX_PAGE_T_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DRX_PAGE_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 寻呼组
*****************************************************************************/
enum LRRC_LPHY_DRX_PAGE_TYPE_ENUM
{
    LRRC_LPHY_DRX_PAGING_GROUP_0          = 0,                                    /* 0：表示4个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_1,                                                 /* 1：表示2个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_2,                                                 /* 2：表示1个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_3,                                                 /* 3：表示1/2个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_4,                                                 /* 4：表示1/4个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_5,                                                 /* 5：表示1/8个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_6,                                                 /* 6：表示1/16个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_7,                                                 /* 7：表示1/32个DRX周期 */
    LRRC_LPHY_DRX_PAGING_GROUP_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_DRX_PAGE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_MEAS_COMMAND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 测量命令类型
*****************************************************************************/
enum LRRC_LPHY_MEAS_COMMAND_ENUM
{
    LRRC_LPHY_MEAS_COMMAND_REL            = 0,                /* 释放测量 */
    LRRC_LPHY_MEAS_COMMAND_SETUP ,                            /* 建立测量 */
    LRRC_LPHY_MEAS_COMMAND_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_MEAS_COMMAND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_IDLE_MEAS_REPORT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IDLE状态下到的上报类型
*****************************************************************************/
enum LRRC_LPHY_IDLE_MEAS_REPORT_TYPE_ENUM
{
    LRRC_LPHY_IDLE_MEAS_REPORT_SERVE      = 31,               /* IDLE测量主小区上报 */
    LRRC_LPHY_IDLE_MEAS_REPORT_INTRA,                         /* IDLE测量同频邻小区上报 */
    LRRC_LPHY_IDLE_MEAS_REPORT_INTER,                         /* IDLE测量异频邻小区上报 */
    LRRC_LPHY_IDLE_MEAS_REPORT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_IDLE_MEAS_REPORT_TYPE_ENUM_UNIT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CONN_MEAS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : Connected状态下测量命令类型
*****************************************************************************/
enum LRRC_LPHY_CONN_MEAS_TYPE_ENUM
{
    LRRC_LPHY_CONN_MEAS_TYPE_INTRA        = 41,              /* Connected测量同频（包括Primary freq和Secondary freqs）邻小区 */
    LRRC_LPHY_CONN_MEAS_TYPE_INTER,                          /* Connected测量异频（不同于所有Serving freqs的频点）邻小区 */
    LRRC_LPHY_CONN_MEAS_TYPE_IRAT,                           /* Connected测量异系统小区 */
    LRRC_LPHY_CONN_MEAS_TYPE_SECOND_FREQ,                    /* Connected测量辅频小区(配置了SCELL的频点) */
    LRRC_LPHY_CONN_MEAS_TYPE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CONN_MEAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CONN_MEAS_REPORT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 连接状态下测量上报类型
*****************************************************************************/
enum LRRC_LPHY_CONN_MEAS_REPORT_TYPE_ENUM
{
    LRRC_LPHY_CONN_MEAS_REPORT_INTRA     = 51,               /* Connected测量同频邻小区上报 */
    LRRC_LPHY_CONN_MEAS_REPORT_INTER,                        /* Connected测量异频邻小区上报 */
    LRRC_LPHY_CONN_MEAS_REPORT_SECOND_FREQ,                  /* Connected测量Secondary Freqs上所有小区上报（包括SCELL和其他邻区） */
    LRRC_LPHY_CONN_MEAS_REPORT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CONN_MEAS_REPORT_TYPE_ENUM_UNIT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_MEAS_GAP_TYPE_ENUM
 协议表格  : MeasGapConfig->gapActivation->activate->gapPattern
 ASN.1描述 :
 枚举说明  : GAP类型
*****************************************************************************/
enum LRRC_LPHY_MEAS_GAP_TYPE_ENUM
{
    LRRC_LPHY_MEAS_GAP_TYPE_1             = 0,                /* gp1 */
    LRRC_LPHY_MEAS_GAP_TYPE_2,                                /* gp2 */
    LRRC_LPHY_MEAS_GAP_TYPE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_MEAS_GAP_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CQI_MODEA_PERIODIC_ENUM
 协议表格  : PhysicalConfigDedicated->CQI-Reporting->cqi-ReportingModeAperiodic
 ASN.1描述 :
 枚举说明  : cqi-ReportingModeAperiodic
*****************************************************************************/
enum LRRC_LPHY_CQI_MODEA_PERIODIC_ENUM
{
    LRRC_LPHY_CQI_MODEA_PERIODIC_12  = 0,                     /* MODE 1-2 */
    LRRC_LPHY_CQI_MODEA_PERIODIC_20,                          /* MODE 2-0 */
    LRRC_LPHY_CQI_MODEA_PERIODIC_22,                          /* MODE 2-2 */
    LRRC_LPHY_CQI_MODEA_PERIODIC_30,                          /* MODE 3-0 */
    LRRC_LPHY_CQI_MODEA_PERIODIC_31,                          /* MODE 3-1 */
    LRRC_LPHY_CQI_MODEA_PERIODIC_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CQI_MODEA_PERIODIC_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_FORMATE_PERIODIC_ENUM
 协议表格  : PhysicalConfigDedicated->CQI-Reporting->CQI-ReportingPeriodic->cqi-FormatIndicatorPeriodic
 ASN.1描述 :
 枚举说明  : cqi-FormatIndicatorPeriodic
*****************************************************************************/
enum LRRC_LPHY_CQI_FORMATE_IND_TYPE_ENUM
{
    LRRC_LPHY_CQI_FORMATE_IND_TYPE_WIDEBAN  = 0,               /* widebandCQI  */
    LRRC_LPHY_CQI_FORMATE_IND_TYPE_SUBBAND,                    /* subbandCQI */
    LRRC_LPHY_CQI_FORMATE_IND_TYPE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CQI_FORMATE_IND_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SRS_BANDWIDTH_TYPE_ENUM
 协议表格  : SoundingRsUl-ConfigCommon->srsBandwidthConfiguration
 ASN.1描述 :
 枚举说明  : SRS的带宽
*****************************************************************************/
enum LRRC_LPHY_SRS_BANDWIDTH_TYPE_ENUM
{
    LRRC_LPHY_SRS_BANDWIDTH_0             = 0,
    LRRC_LPHY_SRS_BANDWIDTH_1,
    LRRC_LPHY_SRS_BANDWIDTH_2,
    LRRC_LPHY_SRS_BANDWIDTH_3,
    LRRC_LPHY_SRS_BANDWIDTH_4,
    LRRC_LPHY_SRS_BANDWIDTH_5,
    LRRC_LPHY_SRS_BANDWIDTH_6,
    LRRC_LPHY_SRS_BANDWIDTH_7,
    LRRC_LPHY_SRS_BANDWIDTH_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SRS_BANDWIDTH_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SRS_SUBFRAME_TYPE_ENUM
 协议表格  : SoundingRsUl-ConfigCommon->srsSubframeConfiguration
 ASN.1描述 :
 枚举说明  : srsSubframeConfiguration
*****************************************************************************/
enum LRRC_LPHY_SRS_SUBFRAME_TYPE_ENUM
{
    LRRC_LPHY_SRS_SUB_FRAME_0             = 0,
    LRRC_LPHY_SRS_SUB_FRAME_1,
    LRRC_LPHY_SRS_SUB_FRAME_2,
    LRRC_LPHY_SRS_SUB_FRAME_3,
    LRRC_LPHY_SRS_SUB_FRAME_4,
    LRRC_LPHY_SRS_SUB_FRAME_5,
    LRRC_LPHY_SRS_SUB_FRAME_6,
    LRRC_LPHY_SRS_SUB_FRAME_7,
    LRRC_LPHY_SRS_SUB_FRAME_8,
    LRRC_LPHY_SRS_SUB_FRAME_9,
    LRRC_LPHY_SRS_SUB_FRAME_10,
    LRRC_LPHY_SRS_SUB_FRAME_11,
    LRRC_LPHY_SRS_SUB_FRAME_12,
    LRRC_LPHY_SRS_SUB_FRAME_13,
    LRRC_LPHY_SRS_SUB_FRAME_14,
    LRRC_LPHY_SRS_SUB_FRAME_15,
    LRRC_LPHY_SRS_SUB_FRAME_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SRS_SUBFRAME_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SRS_HOPPING_BANDWIDTH_ENUM
 协议表格  : SoundingRsUl-ConfigDedicated->srsHoppingBandwidth
 ASN.1描述 :
 枚举说明  : srsHoppingBandwidth
*****************************************************************************/
enum LRRC_LPHY_SRS_HOPPING_BANDWIDTH_ENUM
{
    LRRC_LPHY_SRS_HOPPING_BANDWIDTH_0          = 0,
    LRRC_LPHY_SRS_HOPPING_BANDWIDTH_1,
    LRRC_LPHY_SRS_HOPPING_BANDWIDTH_2,
    LRRC_LPHY_SRS_HOPPING_BANDWIDTH_3,
    LRRC_LPHY_SRS_HOPPING_BANDWIDTH_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SRS_HOPPING_BANDWIDTH_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CYCLIC_SHIFT_ENUM
 协议表格  : SoundingRsUl-ConfigDedicated->cyclicShift
 ASN.1描述 :
 枚举说明  : cyclicShift
*****************************************************************************/
enum LRRC_LPHY_CYCLIC_SHIFT_ENUM
{
    LRRC_LPHY_CYCLIC_SHIFT_0              = 0,
    LRRC_LPHY_CYCLIC_SHIFT_1,
    LRRC_LPHY_CYCLIC_SHIFT_2,
    LRRC_LPHY_CYCLIC_SHIFT_3,
    LRRC_LPHY_CYCLIC_SHIFT_4,
    LRRC_LPHY_CYCLIC_SHIFT_5,
    LRRC_LPHY_CYCLIC_SHIFT_6,
    LRRC_LPHY_CYCLIC_SHIFT_7,
    LRRC_LPHY_CYCLIC_SHIFT_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CYCLIC_SHIFT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DURATION_TIMER_ENUM
 协议表格  : MAC-MainConfiguration->drx-Configuration->onDurationTimer
 ASN.1描述 :
 枚举说明  : onDurationTimer
*****************************************************************************/
enum LRRC_LPHY_DURATION_TIMER_ENUM
{
    LRRC_LPHY_DURATION_TIMER_1          = 0,
    LRRC_LPHY_DURATION_TIMER_2,
    LRRC_LPHY_DURATION_TIMER_3,
    LRRC_LPHY_DURATION_TIMER_4,
    LRRC_LPHY_DURATION_TIMER_5,
    LRRC_LPHY_DURATION_TIMER_6,
    LRRC_LPHY_DURATION_TIMER_8,
    LRRC_LPHY_DURATION_TIMER_10,
    LRRC_LPHY_DURATION_TIMER_20,
    LRRC_LPHY_DURATION_TIMER_30,
    LRRC_LPHY_DURATION_TIMER_40,
    LRRC_LPHY_DURATION_TIMER_50,
    LRRC_LPHY_DURATION_TIMER_60,
    LRRC_LPHY_DURATION_TIMER_80,
    LRRC_LPHY_DURATION_TIMER_100,
    LRRC_LPHY_DURATION_TIMER_200,
    LRRC_LPHY_DURATION_TIMER_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_DURATION_TIMER_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_INACTIVE_TIMER_ENUM
 协议表格  : MAC-MainConfiguration->drx-Configuration->drx-InactivityTimer
 ASN.1描述 :
 枚举说明  : drx-InactivityTimer
*****************************************************************************/
enum LRRC_LPHY_INACTIVE_TIMER_ENUM
{
    LRRC_LPHY_INACTIVE_TIMER_1            = 0,
    LRRC_LPHY_INACTIVE_TIMER_2,
    LRRC_LPHY_INACTIVE_TIMER_3,
    LRRC_LPHY_INACTIVE_TIMER_4,
    LRRC_LPHY_INACTIVE_TIMER_5,
    LRRC_LPHY_INACTIVE_TIMER_6,
    LRRC_LPHY_INACTIVE_TIMER_8,
    LRRC_LPHY_INACTIVE_TIMER_10,
    LRRC_LPHY_INACTIVE_TIMER_20,
    LRRC_LPHY_INACTIVE_TIMER_30,
    LRRC_LPHY_INACTIVE_TIMER_40,
    LRRC_LPHY_INACTIVE_TIMER_50,
    LRRC_LPHY_INACTIVE_TIMER_60,
    LRRC_LPHY_INACTIVE_TIMER_80,
    LRRC_LPHY_INACTIVE_TIMER_100,
    LRRC_LPHY_INACTIVE_TIMER_200,
    LRRC_LPHY_INACTIVE_TIMER_300,
    LRRC_LPHY_INACTIVE_TIMER_500,
    LRRC_LPHY_INACTIVE_TIMER_750,
    LRRC_LPHY_INACTIVE_TIMER_1280,
    LRRC_LPHY_INACTIVE_TIMER_1920,
    LRRC_LPHY_INACTIVE_TIMER_2560,
    LRRC_LPHY_INACTIVE_TIMER_0,
    LRRC_LPHY_INACTIVE_TIMER_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_INACTIVE_TIMER_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_RETRANS_TIMER_ENUM
 协议表格  : MAC-MainConfiguration->drx-Configuration->drx-RetransmissionTimer
 ASN.1描述 :
 枚举说明  : drx-RetransmissionTimer
*****************************************************************************/
enum LRRC_LPHY_RETRANS_TIMER_ENUM
{
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_RETRANS_TIMER_0             = 0,
    LRRC_LPHY_RETRANS_TIMER_1,
#else
    LRRC_LPHY_RETRANS_TIMER_1             = 0,
#endif
    LRRC_LPHY_RETRANS_TIMER_2,
    LRRC_LPHY_RETRANS_TIMER_4,
    LRRC_LPHY_RETRANS_TIMER_6,
    LRRC_LPHY_RETRANS_TIMER_8,
    LRRC_LPHY_RETRANS_TIMER_16,
    LRRC_LPHY_RETRANS_TIMER_24,
    LRRC_LPHY_RETRANS_TIMER_33,
    LRRC_LPHY_RETRANS_TIMER_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_RETRANS_TIMER_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_LONG_DRX_OFFSET_ENUM
 协议表格  : MAC-MainConfiguration->drx-Configuration->longDRX-CycleStartOffset
 ASN.1描述 :
 枚举说明  : longDRX-CycleStartOffset
*****************************************************************************/
enum LRRC_LPHY_LONG_DRX_OFFSET_ENUM
{
    LRRC_LPHY_LONG_DRX_OFFSET_10    = 0,
    LRRC_LPHY_LONG_DRX_OFFSET_20,
    LRRC_LPHY_LONG_DRX_OFFSET_32,
    LRRC_LPHY_LONG_DRX_OFFSET_40,
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_LONG_DRX_OFFSET_60,
    LRRC_LPHY_LONG_DRX_OFFSET_70,
#endif
    LRRC_LPHY_LONG_DRX_OFFSET_64,
    LRRC_LPHY_LONG_DRX_OFFSET_80,
    LRRC_LPHY_LONG_DRX_OFFSET_128,
    LRRC_LPHY_LONG_DRX_OFFSET_160,
    LRRC_LPHY_LONG_DRX_OFFSET_256,
    LRRC_LPHY_LONG_DRX_OFFSET_320,
    LRRC_LPHY_LONG_DRX_OFFSET_512,
    LRRC_LPHY_LONG_DRX_OFFSET_640,
    LRRC_LPHY_LONG_DRX_OFFSET_1024,
    LRRC_LPHY_LONG_DRX_OFFSET_1280,
    LRRC_LPHY_LONG_DRX_OFFSET_2048,
    LRRC_LPHY_LONG_DRX_OFFSET_2560,
    LRRC_LPHY_LONG_DRX_OFFSET_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_LONG_DRX_OFFSET_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SHORT_DRX_CYCLE_ENUM
 协议表格  : MAC-MainConfiguration->drx-Configuration->shortDRX->shortDRX-Cycle
 ASN.1描述 :
 枚举说明  : shortDRX-Cycle
*****************************************************************************/
enum LRRC_LPHY_SHORT_DRX_CYCLE_ENUM
{
    LRRC_LPHY_SHORT_DRX_CYCLE_2    = 0,
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_SHORT_DRX_CYCLE_4,
#endif
    LRRC_LPHY_SHORT_DRX_CYCLE_5,
    LRRC_LPHY_SHORT_DRX_CYCLE_8,
    LRRC_LPHY_SHORT_DRX_CYCLE_10,
    LRRC_LPHY_SHORT_DRX_CYCLE_16,
    LRRC_LPHY_SHORT_DRX_CYCLE_20,
    LRRC_LPHY_SHORT_DRX_CYCLE_32,
    LRRC_LPHY_SHORT_DRX_CYCLE_40,
    LRRC_LPHY_SHORT_DRX_CYCLE_64,
    LRRC_LPHY_SHORT_DRX_CYCLE_80,
    LRRC_LPHY_SHORT_DRX_CYCLE_128,
    LRRC_LPHY_SHORT_DRX_CYCLE_160,
    LRRC_LPHY_SHORT_DRX_CYCLE_256,
    LRRC_LPHY_SHORT_DRX_CYCLE_320,
    LRRC_LPHY_SHORT_DRX_CYCLE_512,
    LRRC_LPHY_SHORT_DRX_CYCLE_640,
    LRRC_LPHY_SHORT_DRX_CYCLE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SHORT_DRX_CYCLE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DRX_INDICATOR_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DRX功能是否打开
*****************************************************************************/
enum LRRC_LPHY_DRX_INDICATOR_ENUM
{
    LRRC_LPHY_DRX_INDICATOR_INVALID = 0,       /*DRX不使能 */
    LRRC_LPHY_DRX_INDICATOR_VALID,             /* DRX使能*/
    LRRC_LPHY_DRX_INDICATOR_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_DRX_INDICATOR_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_GATECLOCK_INDICATOR_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 时钟门控是否使能
*****************************************************************************/
enum LRRC_LPHY_GATECLOCK_INDICATOR_ENUM
{
    LRRC_LPHY_GATECLOCK_INDICATOR_INVALID = 0,                /*门控钟不使能 */
    LRRC_LPHY_GATECLOCK_INDICATOR_VALID,                    /* 门控钟使能*/
    LRRC_LPHY_GATECLOCK_INDICATOR_BUTT
};
typedef VOS_UINT16  LRRC_LPHY_GATECLOCK_INDICATOR_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SI_WINDOW_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : SI消息的Window
*****************************************************************************/
enum LRRC_LPHY_SI_WINDOW_ENUM
{
    LRRC_LPHY_SI_WINDOW_MS01 = 0,
    LRRC_LPHY_SI_WINDOW_MS02,
    LRRC_LPHY_SI_WINDOW_MS05,
    LRRC_LPHY_SI_WINDOW_MS10,
    LRRC_LPHY_SI_WINDOW_MS15,
    LRRC_LPHY_SI_WINDOW_MS20,
    LRRC_LPHY_SI_WINDOW_MS40
};
typedef VOS_UINT16 LRRC_LPHY_SI_WINDOW_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SI_WINDOW_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : SI消息的Periodicty
*****************************************************************************/
enum LRRC_LPHY_SI_PERIOD_ENUM
{
    LRRC_LPHY_SI_PERIOD_RF008 = 0,
    LRRC_LPHY_SI_PERIOD_RF016,
    LRRC_LPHY_SI_PERIOD_RF032,
    LRRC_LPHY_SI_PERIOD_RF064,
    LRRC_LPHY_SI_PERIOD_RF128,
    LRRC_LPHY_SI_PERIOD_RF256,
    LRRC_LPHY_SI_PERIOD_RF512
};
typedef VOS_UINT16 LRRC_LPHY_SI_PERIOD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : mbsfn radioframe allocation period
*****************************************************************************/
enum LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_ENUM
{
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_N1 = 0,
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_N2,
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_N4,
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_N8,
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_N16,
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_N32,
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_MBSFN_ALLOCATION_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : mbsfn allocation type
*****************************************************************************/
enum LRRC_LPHY_MBSFN_ALLOCATION_TYPE_ENUM
{
    LRRC_LPHY_MBSFN_ALLOCATION_TYPE_ONE = 0,
    LRRC_LPHY_MBSFN_ALLOCATION_TYPE_FOUR
};
typedef VOS_UINT16 LRRC_LPHY_MBSFN_ALLOCATION_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CGI_ACQUISITION_METHOD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CGI acquisition method
             0:不进行CGI获取,即连接态或空闲态进行普通的系统消息接收
             1:表示连接态下利用AUTONOMOUS GAPS获取邻区系统消息
             2:表示连接态下利用空闲DRX周期获取邻区系统消息
*****************************************************************************/
enum LRRC_LPHY_CGI_ACQUISITION_METHOD_ENUM
{
    LRRC_LPHY_CGI_ACQUISITION_METHOD_NONE = 0,
    LRRC_LPHY_CGI_ACQUISITION_METHOD_AUTONOMOUS_GAPS,
    LRRC_LPHY_CGI_ACQUISITION_METHOD_IDLE_PERIODS,
    LRRC_LPHY_CGI_ACQUISITION_METHOD_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_CGI_ACQUISITION_METHOD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_BAND_SCAN_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 扫频类型
*****************************************************************************/
enum LRRC_LPHY_BAND_SCAN_TYPE_ENUM
{
    LRRC_LPHY_BAND_SCAN_TYPE_INIT                  = 0,                         /* 初始扫频 */
    LRRC_LPHY_BAND_SCAN_TYPE_CONT                  = 1,                         /* 后续扫频 */
    LRRC_LPHY_BAND_SCAN_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_BAND_SCAN_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_HO_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 切换类型
*****************************************************************************/
enum LRRC_LPHY_HO_TYPE_ENUM
{
    LRRC_LPHY_HO_TYPE_INTRA_LTE                   = 0,                          /* LTE内切换 */
    LRRC_LPHY_HO_TYPE_IRAT                        = 1,                          /* IRAT->LTE切换 */
    LRRC_LPHY_HO_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_HO_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_WORK_MODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE RTT工作模式
*****************************************************************************/
enum LRRC_LPHY_WORK_MODE_TYPE_ENUM
{
    LRRC_LPHY_WORK_MODE_TYPE_ACTIVE                = 0,                         /* LTE处在工作态 */
    LRRC_LPHY_WORK_MODE_TYPE_INACTIVE              = 1,                         /* LTE处在测量态 */
    LRRC_LPHY_TEST_MODE_TYPE_ACTIVE                = 2,                         /* LTE处在测试态 */
    LRRC_LPHY_TEST_MODE_TYPE_INACTIVE              = 3,                         /* LTE处在停测试态 */
    LRRC_LPHY_WORK_MODE_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_WORK_MODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SET_WORK_MODE_REASON_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 切模原因
*****************************************************************************/
enum LRRC_LPHY_SET_WORK_MODE_REASON_ENUM
{
    LRRC_LPHY_SET_WORK_MODE_REASON_POWEROFF              = 1,                   /* 关机引起 */
    LRRC_LPHY_SET_WORK_MODE_REASON_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_SET_WORK_MODE_REASON_ENUM_UINT16;


/*****************************************************************************
 枚举名    : LRRC_LPHY_RAT_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 系统接入类型
*****************************************************************************/
enum LRRC_LPHY_RAT_TYPE_ENUM
{
    LRRC_LPHY_RAT_TYPE_LTE                    = 0,                              /* LTE */
    LRRC_LPHY_RAT_TYPE_GSM                    = 1,                              /* GSM */
    LRRC_LPHY_RAT_TYPE_WCDMA                  = 2,                              /* WCDMA */
    LRRC_LPHY_RAT_TYPE_TD_SCDMA               = 3,                              /* TD-SCDMA */
    LRRC_LPHY_RAT_TYPE_CDMA                   = 4,                              /* CDMA */

    LRRC_LPHY_RAT_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_RAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_GERAN_BAND_IND_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : GERAN的频带指示
*****************************************************************************/
enum LRRC_LPHY_GERAN_BAND_IND_ENUM
{
    LRRC_LPHY_GERAN_BAND_IND_DCS1800          = 0,
    LRRC_LPHY_GERAN_BAND_IND_PCS1900,
    LRRC_LPHY_GERAN_BAND_IND_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_GERAN_BAND_IND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE模式类型
*****************************************************************************/
enum LRRC_LPHY_LTE_MODE_TYPE_ENUM
{
    LRRC_LPHY_LTE_MODE_TYPE_FDD                = 0,                             /* LTE FDD 制式 */
    LRRC_LPHY_LTE_MODE_TYPE_TDD                = 1,                             /* LTE TDD 制式 */
    LRRC_LPHY_LTE_MODE_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_WCDMA_STATE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : WCDMA协议状态类型
*****************************************************************************/
enum LRRC_LPHY_WCDMA_STATE_ENUM
{
    LRRC_LPHY_WCDMA_STATE_CELL_PCH            = 0,                              /* CELL PCH */
    LRRC_LPHY_WCDMA_STATE_URA_PCH             = 1,                              /* URA PCH */
    LRRC_LPHY_WCDMA_STATE_CELL_FACH           = 2,                              /* CELL FACH */
    LRRC_LPHY_WCDMA_STATE_CELL_DCH            = 3,                              /* CELL DCH */
    LRRC_LPHY_WCDMA_STATE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_WCDMA_STATE_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_BAND_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE Band指示枚举
**********************************************************/
enum LRRC_LPHY_BAND_IND_ENUM
{
    LRRC_LPHY_BAND_IND_NONE,
    LRRC_LPHY_BAND_IND_1                   = 1 ,
    LRRC_LPHY_BAND_IND_2,
    LRRC_LPHY_BAND_IND_3,
    LRRC_LPHY_BAND_IND_4,
    LRRC_LPHY_BAND_IND_5,
    LRRC_LPHY_BAND_IND_6,
    LRRC_LPHY_BAND_IND_7,
    LRRC_LPHY_BAND_IND_8,
    LRRC_LPHY_BAND_IND_9,
    LRRC_LPHY_BAND_IND_10,
    LRRC_LPHY_BAND_IND_11,
    LRRC_LPHY_BAND_IND_12,
    LRRC_LPHY_BAND_IND_13,
    LRRC_LPHY_BAND_IND_14,
    LRRC_LPHY_BAND_IND_15,
    LRRC_LPHY_BAND_IND_16,
    LRRC_LPHY_BAND_IND_17                = 17,
    LRRC_LPHY_BAND_IND_18,
    LRRC_LPHY_BAND_IND_19,
    LRRC_LPHY_BAND_IND_20,
    LRRC_LPHY_BAND_IND_21,
    LRRC_LPHY_BAND_IND_22,
    LRRC_LPHY_BAND_IND_23,
    LRRC_LPHY_BAND_IND_24,
    LRRC_LPHY_BAND_IND_25,
    LRRC_LPHY_BAND_IND_26,
    LRRC_LPHY_BAND_IND_27,
    LRRC_LPHY_BAND_IND_28,
    LRRC_LPHY_BAND_IND_29,
    LRRC_LPHY_BAND_IND_30,
    LRRC_LPHY_BAND_IND_31,
    LRRC_LPHY_BAND_IND_32,
    LRRC_LPHY_BAND_IND_33                = 33,
    LRRC_LPHY_BAND_IND_34,
    LRRC_LPHY_BAND_IND_35,
    LRRC_LPHY_BAND_IND_36,
    LRRC_LPHY_BAND_IND_37,
    LRRC_LPHY_BAND_IND_38,
    LRRC_LPHY_BAND_IND_39,
    LRRC_LPHY_BAND_IND_40,
    LRRC_LPHY_BAND_IND_41,
    LRRC_LPHY_BAND_IND_42,
    LRRC_LPHY_BAND_IND_43,
    LRRC_LPHY_BAND_IND_64                = 64,

    /* 非标频段begin */
    LRRC_LPHY_BAND_IND_101  = 101,
    LRRC_LPHY_BAND_IND_102  = 102,
    LRRC_LPHY_BAND_IND_103  = 103,
    LRRC_LPHY_BAND_IND_104  = 104,
    LRRC_LPHY_BAND_IND_105  = 105,
    LRRC_LPHY_BAND_IND_106  = 106,
    LRRC_LPHY_BAND_IND_107  = 107,
    LRRC_LPHY_BAND_IND_108  = 108,
    LRRC_LPHY_BAND_IND_109  = 109,
    LRRC_LPHY_BAND_IND_110  = 110,
    LRRC_LPHY_BAND_IND_111  = 111,
    LRRC_LPHY_BAND_IND_112  = 112,
    LRRC_LPHY_BAND_IND_113  = 113,
    LRRC_LPHY_BAND_IND_114  = 114,
    LRRC_LPHY_BAND_IND_115  = 115,
    LRRC_LPHY_BAND_IND_116  = 116,
    /* 非标频段end */

    LRRC_LPHY_BAND_IND_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_BAND_IND_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_ERR_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理层发生错误的类型枚举
**********************************************************/
enum LRRC_LPHY_ERR_TYPE_ENUM
{
    LRRC_LPHY_ERR_TYPE_TIMING_ERR       = 0 ,                                   /* 定时错误 */

    LRRC_LPHY_ERR_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_ERR_TYPE_ENUM_UINT16;

/* MBMS Begin */
/*********************************************************
 枚举名    : LRRC_LPHY_MCCH_REPET_PERIOD_R9_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MCCH重复周期
**********************************************************/
enum LRRC_LPHY_MCCH_REPET_PERIOD_R9_ENUM
{
    LRRC_LPHY_RF32_MCCH_REPET_PERIOD_R9                = 0,
    LRRC_LPHY_RF64_MCCH_REPET_PERIOD_R9                = 1,
    LRRC_LPHY_RF128_MCCH_REPET_PERIOD_R9               = 2,
    LRRC_LPHY_RF256_MCCH_REPET_PERIOD_R9               = 3,
    LRRC_LPHY_MCCH_REPET_PERIOD_R9_BUTT
};
typedef VOS_UINT8 LRRC_LPHY_MCCH_REPET_PERIOD_R9_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_LRRC_LPHY_MCCH_OFFSET_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MCCH offset值(0..10)
**********************************************************/
enum LRRC_LPHY_LRRC_LPHY_MCCH_OFFSET_ENUM
{
    LRRC_LPHY_MCCH_OFFSET_0,
    LRRC_LPHY_MCCH_OFFSET_1,
    LRRC_LPHY_MCCH_OFFSET_2,
    LRRC_LPHY_MCCH_OFFSET_3,
    LRRC_LPHY_MCCH_OFFSET_4,
    LRRC_LPHY_MCCH_OFFSET_5,
    LRRC_LPHY_MCCH_OFFSET_6,
    LRRC_LPHY_MCCH_OFFSET_7,
    LRRC_LPHY_MCCH_OFFSET_8,
    LRRC_LPHY_MCCH_OFFSET_9,
    LRRC_LPHY_MCCH_OFFSET_10,
    LRRC_LPHY_MCCH_OFFSET_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_LRRC_LPHY_MCCH_OFFSET_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_MCCH_MODIFY_PERIOD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MCCH modify周期(0..10)
**********************************************************/
enum LRRC_LPHY_MCCH_MODIFY_PERIOD_ENUM
{
    LRRC_LPHY_MCCH_MODIFY_PERIOD_RF_512,
    LRRC_LPHY_MCCH_MODIFY_PERIOD_RF_1024,
    LRRC_LPHY_MCCH_MODIFY_PERIOD_RF_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_MCCH_MODIFY_PERIOD_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_SIG_MCS_R9_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MCCH Signal MCS调度信息
**********************************************************/
enum LRRC_LPHY_SIG_MCS_R9_ENUM
{
    LRRC_LPHY_N2_SIG_MCS_R9                            = 0,
    LRRC_LPHY_N7_SIG_MCS_R9                            = 1,
    LRRC_LPHY_N13_SIG_MCS_R9                           = 2,
    LRRC_LPHY_N19_SIG_MCS_R9                           = 3,
    LRRC_LPHY_SIG_MCS_R9_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_SIG_MCS_R9_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_NON_MBSF_NREGION_LEN_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :non-MBSFNregionLength
**********************************************************/
enum LRRC_LPHY_NON_MBSF_NREGION_LEN_ENUM
{
    LRRC_LPHY_NON_MBSF_NREGION_LEN_1,
    LRRC_LPHY_NON_MBSF_NREGION_LEN_2,
    LRRC_LPHY_NON_MBSF_NREGION_LEN_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_NON_MBSF_NREGION_LEN_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_NON_MBSF_NREGION_LEN_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :non-MBSFNregionLength
**********************************************************/
enum LRRC_LPHY_CONIG_VALID_FLG_ENUM
{
    LRRC_LPHY_CONIG_FLG_INVALID  = 0,
    LRRC_LPHY_CONIG_FLG_VALID    = 1
};
typedef VOS_UINT8 LRRC_LPHY_CONIG_VALID_FLG_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_NOTIFICATION_OFFSET_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :non-MBSFNregionLength
**********************************************************/
enum LRRC_LPHY_NOTIFICATION_OFFSET_ENUM
{
    LRRC_LPHY_NOTIFICATION_OFFSET_0,
    LRRC_LPHY_NOTIFICATION_OFFSET_1,
    LRRC_LPHY_NOTIFICATION_OFFSET_2,
    LRRC_LPHY_NOTIFICATION_OFFSET_3,
    LRRC_LPHY_NOTIFICATION_OFFSET_4,
    LRRC_LPHY_NOTIFICATION_OFFSET_5,
    LRRC_LPHY_NOTIFICATION_OFFSET_6,
    LRRC_LPHY_NOTIFICATION_OFFSET_7,
    LRRC_LPHY_NOTIFICATION_OFFSET_8,
    LRRC_LPHY_NOTIFICATION_OFFSET_9,
    LRRC_LPHY_NOTIFICATION_OFFSET_10,
    LRRC_LPHY_NOTIFICATION_OFFSET_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_NOTIFICATION_OFFSET_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_NOTIFICATION_OFFSET_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :non-MBSFNregionLength
**********************************************************/
enum LRRC_LPHY_NOTIFICATION_REPET_COEFF_R9_ENUM
{
    LRRC_LPHY_N2_NOTIFICATION_REPET_COEFF_R9           = 0,
    LRRC_LPHY_N4_NOTIFICATION_REPET_COEFF_R9           = 1,
    LRRC_LPHY_NOTIFICATION_REPET_COEFF_R9_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_NOTIFICATION_REPET_COEFF_R9_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_NOTIFICATION_OFFSET_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :non-MBSFNregionLength
**********************************************************/
enum LRRC_LPHY_NOTIFICATION_SF_INDEX_ENUM
{
    LRRC_LPHY_NOTIFICATION_SF_INDEX_1 = 1,
    LRRC_LPHY_NOTIFICATION_SF_INDEX_2,
    LRRC_LPHY_NOTIFICATION_SF_INDEX_3,
    LRRC_LPHY_NOTIFICATION_SF_INDEX_4,
    LRRC_LPHY_NOTIFICATION_SF_INDEX_5,
    LRRC_LPHY_NOTIFICATION_SF_INDEX_6,
    LRRC_LPHY_NOTIFICATION_SF_INDEX_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_NOTIFICATION_SF_INDEX_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_NOTIFICATION_OFFSET_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :non-MBSFNregionLength
**********************************************************/
enum LRRC_LPHY_MCH_SCHDL_PERIOD_R9_ENUM
{
    LRRC_LPHY_RF8_MCH_SCHDL_PERIOD_R9                  = 0,
    LRRC_LPHY_RF16_MCH_SCHDL_PERIOD_R9                 = 1,
    LRRC_LPHY_RF32_MCH_SCHDL_PERIOD_R9                 = 2,
    LRRC_LPHY_RF64_MCH_SCHDL_PERIOD_R9                 = 3,
    LRRC_LPHY_RF128_MCH_SCHDL_PERIOD_R9                = 4,
    LRRC_LPHY_RF256_MCH_SCHDL_PERIOD_R9                = 5,
    LRRC_LPHY_RF512_MCH_SCHDL_PERIOD_R9                = 6,
    LRRC_LPHY_RF1024_MCH_SCHDL_PERIOD_R9               = 7,
    LRRC_LPHY_MCH_SCHDL_PERIOD_R9_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_MCH_SCHDL_PERIOD_R9_ENUM_UINT8;

/*********************************************************
 枚举名    : LRRC_LPHY_COMM_SF_ALLOC_PERIOD_R9_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_COMM_SF_ALLOC_PERIOD_R9_ENUM
{
    LRRC_LPHY_RF4_MBSFN                                      = 0,
    LRRC_LPHY_RF8_MBSFN                                      = 1,
    LRRC_LPHY_RF16_MBSFN                                     = 2,
    LRRC_LPHY_RF32_MBSFN                                     = 3,
    LRRC_LPHY_RF64_MBSFN                                     = 4,
    LRRC_LPHY_RF128_MBSFN                                    = 5,
    LRRC_LPHY_RF256_MBSFN                                    = 6,
    LRRC_LPHY_MBSFN_BUFF
};
typedef VOS_UINT8 LRRC_LPHY_COMM_SF_ALLOC_PERIOD_R9_ENUM_UINT8;


/* LCS Begin */

/*****************************************************************************
 枚举名    : LRRC_LPHY_OTDOA_ENABLE_SIGNAL_ENUM
 协议表格  : 上报给网络侧，是否有足够的gap或释放gap
 ASN.1描述 :
 枚举说明  : LRRC_LPHY_OTDOA_ENABLE_SIGNAL_ENUM
*****************************************************************************/
enum LRRC_LPHY_OTDOA_ENABLE_SIGNAL_ENUM
{
    LRRC_LPHY_OTDOA_ENABLE_STOP,
    LRRC_LPHY_OTDOA_ENABLE_START,
    LRRC_LPHY_OTDOA_ENABLE_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_OTDOA_ENABLE_SIGNAL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_POSITION_OTDOA_MEAS_REQ_ENUM
 协议表格  : 启动或停止指示OTDOA测量
 ASN.1描述 :
 枚举说明  : LRRC_LPHY_POSITION_OTDOA_MEAS_REQ_ENUM
*****************************************************************************/
enum LRRC_LPHY_POSITION_OTDOA_MEAS_REQ_ENUM
{
    LRRC_LPHY_POSITION_OTDOA_MEAS_REL,
    LRRC_LPHY_POSITION_OTDOA_MEAS_SETUP,
    LRRC_LPHY_POSITION_OTDOA_MEAS_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_POSITION_OTDOA_MEAS_REQ_ENUM_UINT16;

/*****************************************************************************
 枚举名    : OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16
*****************************************************************************/
enum LRRC_LPHY_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM
{
    LRRC_LPHY_OTDOA_MEAS_NO_ERROR,
    LRRC_LPHY_OTDOA_TARGET_DEVICE_UNDEFINED,
    LRRC_LPHY_OTDOA_ASSISTANCE_DATA_MISSING,
    LRRC_LPHY_OTDOA_UNABLE_TO_MEASURE_REF_CELL,
    LRRC_LPHY_OTDOA_UNABLE_TO_MEASURE_ANY_NEIGHBOUR_CELL,
    LRRC_LPHY_OTDOA_ATTEMPTED_BUT_UNABLE_TO_MEASURE_SOME_NEIGHBOUR_CELLS,
    LRRC_LPHY_OTDOA_TARGET_DEVICE_ERROR_CAUSES_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_ECID_TARGET_DEVICE_ERROR_CAUSES_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LRRC_LPHY_ECID_TARGET_DEVICE_ERROR_CAUSES_ENUM
*****************************************************************************/
enum LRRC_LPHY_ECID_TARGET_DEVICE_ERROR_CAUSES_ENUM
{
    LRRC_LPHY_ECID_MEAS_NO_ERROR,
    LRRC_LPHY_ECID_TARGET_DEVICE_UNDEFINED,
    LRRC_LPHY_ECID_REQUESTED_MEASUREMENT_NOT_AVAILABLE,
    LRRC_LPHY_ECID_NOT_ALL_REQUESTED_MEASUREMENTS_POSSIBLE,
    LRRC_LPHY_ECID_TARGET_DEVICE_ERROR_CAUSES_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_ECID_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_LTE_CP_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_LTE_CP_TYPE_ENUM
{
    LRRC_LPHY_LTE_CP_TYPE_NORMAL = 0,
    LRRC_LPHY_LTE_CP_TYPE_EXTENDED,
    LRRC_LPHY_LTE_CP_TYPE_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_LTE_CP_TYPE_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_OTDOA_ANT_PORT_CFG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_OTDOA_ANT_PORT_CFG_ENUM
{
    LRRC_LPHY_OTDOA_ANT_PORTS_1_OR_2 = 1,
    LRRC_LPHY_OTDOA_ANT_PORTS_4      = 4,
    LRRC_LPHY_OTDOA_ANT_PORTS_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_OTDOA_ANT_PORT_CFG_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_OTDOA_PRS_CRS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_OTDOA_PRS_CRS_TYPE_ENUM
{
    LRRC_LPHY_OTDOA_PRS_TYPE,
    LRRC_LPHY_OTDOA_CRS_TYPE,
    LRRC_LPHY_OTDOA_PRS_CRS_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_OTDOA_PRS_CRS_TYPE_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_OTDOA_DL_SUBFRAME_NUM_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_OTDOA_DL_SUBFRAME_NUM_ENUM
{
    LRRC_LPHY_OTDOA_DL_SF_1,
    LRRC_LPHY_OTDOA_DL_SF_2,
    LRRC_LPHY_OTDOA_DL_SF_4,
    LRRC_LPHY_OTDOA_DL_SF_6,
    LRRC_LPHY_OTDOA_DL_SF_BUFF
};
typedef VOS_UINT16 LRRC_LPHY_OTDOA_DL_SUBFRAME_NUM_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_OTDOA_DL_SUBFRAME_NUM_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_LTE_BAND_WIDTH_ENUM
{
    LRRC_LPHY_LTE_BAND_WIDTH_1D4M = 0,
    LRRC_LPHY_LTE_BAND_WIDTH_3M,
    LRRC_LPHY_LTE_BAND_WIDTH_5M,
    LRRC_LPHY_LTE_BAND_WIDTH_10M,
    LRRC_LPHY_LTE_BAND_WIDTH_15M,
    LRRC_LPHY_LTE_BAND_WIDTH_20M,
    LRRC_LPHY_LTE_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_LTE_BAND_WIDTH_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_OTDOA_RPRT_INTERVAL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_OTDOA_RPRT_INTERVAL_ENUM
{
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_1 = 0,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_2,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_4,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_8,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_10,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_16,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_20,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_32,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_SECOND_64,
    LRRC_LPHY_OTDOA_RPRT_INTERVAl_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_OTDOA_RPRT_INTERVAL_ENUM_UINT16;


/* LCS End */

/*********************************************************
 枚举名    : LRRC_LPHY_DELTAF_PUCCH_FORMAT3_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_DELTAF_PUCCH_FORMAT3_ENUM
{
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_NEGATIVE_1 = 0,                          /* deltaF-1 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_0,                                       /* deltaF0 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_1,                                       /* deltaF1 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_2,                                       /* deltaF2 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_3,                                       /* deltaF3 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_4,                                       /* deltaF4 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_5,                                       /* deltaF5 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_6,                                       /* deltaF6 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_DELTAF_PUCCH_FORMAT3_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_ENUM
{
    LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_1,                                        /* deltaF1 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_2,                                        /* deltaF2 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_SPARE2,                                   /* spare2 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_SPARE1,                                   /* spare1 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM
{
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_DB_0,                                       /* dB 0 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_DB_NEGATIVE_1,                              /* dB -1 */
#endif
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_DB_NEGATIVE_2,                              /* dB -2 */
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM_UINT16;

/*********************************************************
 枚举名    : LRRC_LPHY_PUCCH_FORMAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LRRC_LPHY_PUCCH_FORMAT_TYPE_ENUM
{
    LRRC_LPHY_PUCCH_FORMAT_TYPE_FORMAT3,                                        /* format3-r10 */
    LRRC_LPHY_PUCCH_FORMAT_TYPE_CHANNEL_SEL,                                    /* channelSelection-r10 */
    LRRC_LPHY_PUCCH_FORMAT_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_PUCCH_FORMAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SUBFRAME_PATTERN_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LPHY_SUBFRAME_PATTERN_TYPE_ENUM
{
    LRRC_LPHY_SUBFRAME_PATTERN_TYPE_FDD,                                        /* subframePatternFDD-r10 */
    LRRC_LPHY_SUBFRAME_PATTERN_TYPE_TDD_1_5,                                    /* subframeConfig1-5-r10 */
    LRRC_LPHY_SUBFRAME_PATTERN_TYPE_TDD_0,                                      /* subframeConfig0-r10 */
    LRRC_LPHY_SUBFRAME_PATTERN_TYPE_TDD_6,                                      /* subframeConfig6-r10 */
    LRRC_LPHY_SUBFRAME_PATTERN_TYPE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SUBFRAME_PATTERN_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PERIODIC_FACTOR_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LPHY_PERIODIC_FACTOR_ENUM
{
    LRRC_LPHY_PERIODIC_FACTOR_N2,                                               /* n2  */
    LRRC_LPHY_PERIODIC_FACTOR_N4,                                               /* n4 */
    LRRC_LPHY_PERIODIC_FACTOR_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PERIODIC_FACTOR_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CQI_REPORT_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LPHY_CQI_REPORT_MODE_ENUM
{
    LRRC_LPHY_CQI_REPORT_MODE_SUBMODE1,                                         /* submode1 */
    LRRC_LPHY_CQI_REPORT_MODE_SUBMODE2,                                         /* submode2 */
    LRRC_LPHY_CQI_REPORT_MODE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_CQI_REPORT_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_TRANSMISSION_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LPHY_TRANSMISSION_MODE_ENUM
{
    LRRC_LPHY_TRANSMISSION_MODE_TM1,
    LRRC_LPHY_TRANSMISSION_MODE_TM2,
    LRRC_LPHY_TRANSMISSION_MODE_SPARE6,
    LRRC_LPHY_TRANSMISSION_MODE_SPARE5,
    LRRC_LPHY_TRANSMISSION_MODE_SPARE4,
    LRRC_LPHY_TRANSMISSION_MODE_SPARE3,
    LRRC_LPHY_TRANSMISSION_MODE_SPARE2,
    LRRC_LPHY_TRANSMISSION_MODE_SPARE1,
    LRRC_LPHY_TRANSMISSION_MODE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_TRANSMISSION_MODE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PATHLOSS_REF_LINK_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LPHY_PATHLOSS_REF_LINK_ENUM
{
    LRRC_LPHY_PATHLOSS_REF_LINK_PCELL,
    LRRC_LPHY_PATHLOSS_REF_LINK_SCELL,
    LRRC_LPHY_PATHLOSS_REF_LINK_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_PATHLOSS_REF_LINK_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_SCHEDUL_CELL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LPHY_SCHEDUL_CELL_TYPE_ENUM
{
    LRRC_LPHY_SCHEDUL_CELL_TYPE_OWN,                                            /* No cross carrier scheduling */
    LRRC_LPHY_SCHEDUL_CELL_TYPE_OTHER,                                          /* Cross carrier scheduling */
    LRRC_LPHY_SCHEDUL_CELL_TYPE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_SCHEDUL_CELL_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_MEAS_CYCLE_SCELL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_LPHY_MEAS_CYCLE_SCELL_ENUM
{
    LRRC_LPHY_MEAS_CYCLE_SF_160,
    LRRC_LPHY_MEAS_CYCLE_SF_256,
    LRRC_LPHY_MEAS_CYCLE_SF_320,
    LRRC_LPHY_MEAS_CYCLE_SF_512,
    LRRC_LPHY_MEAS_CYCLE_SF_640,
    LRRC_LPHY_MEAS_CYCLE_SF_1024,
    LRRC_LPHY_MEAS_CYCLE_SF_1280,
    LRRC_LPHY_MEAS_CYCLE_SPARE1,
    LRRC_LPHY_MEAS_CYCLE_BUTT
};
typedef VOS_UINT16    LRRC_LPHY_MEAS_CYCLE_SCELL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DSDS_RFSHARED_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :DSDS特性新增，RF shared是否使能
*****************************************************************************/
enum LRRC_LPHY_DSDS_RFSHARED_ENUM
{
    LRRC_LPHY_DSDS_RFSHARED_DISABLE           = 0,    /* 不启动 */
    LRRC_LPHY_DSDS_RFSHARED_ENABLE            = 1,    /* 启动 */
    LRRC_LPHY_DSDS_RFSHARED_BUTT
};
typedef VOS_UINT16  LRRC_LPHY_DSDS_RFSHARED_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_NOTCH_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  通知物理层启动NOTCH 通道指示
*****************************************************************************/

enum LRRC_LPHY_NOTCH_STATE_ENUM
{
    LRRC_LPHY_NOTCH_OPEN_FLAG_FALSE          = 0,    /* 不启动 */
    LRRC_LPHY_NOTCH_OPEN_FLAG_TRUE           = 1,    /* 启动 */
    LRRC_LPHY_NOTCH_OPEN_FLAG_BUTT
};
typedef VOS_UINT16  LRRC_LPHY_NOTCH_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DPDT_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 发送DPST命令的功能
*****************************************************************************/

enum LRRC_LPHY_DPDT_CMD_ENUM
{
    LRRC_LPHY_SET_SWITCH           = 0,    /*开关 */
    LRRC_LPHY_SET_VALUE            = 1,    /* 设置值 */
    LRRC_LPHY_DPDT_VALUE_QRY               /*查询*/
};
typedef VOS_UINT16  LRRC_LPHY_DPDT_CMD_ENUM_UINT16;

#if (FEATURE_ON == FEATURE_LTE_R11)
/*****************************************************************************
 枚举名    : LRRC_LPHY_QCL_OPERATION_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/

enum LRRC_LPHY_QCL_OPERATION_ENUM
{
    LRRC_LPHY_QCL_OPERATION_TYPEA           = 0,
    LRRC_LPHY_QCL_OPERATION_TYPEB           = 1
};
typedef VOS_UINT16  LRRC_LPHY_QCL_OPERATION_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_CRS_PORTS_COUNT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/

enum LRRC_LPHY_CRS_PORTS_COUNT_ENUM
{
    LRRC_LPHY_CRS_PORTS_N1,
    LRRC_LPHY_CRS_PORTS_N2,
    LRRC_LPHY_CRS_PORTS_N4,
    LRRC_LPHY_CRS_PORTS_SPARE1,
    LRRC_LPHY_CRS_PORTS_BUTT
};
typedef VOS_UINT16  LRRC_LPHY_CRS_PORTS_COUNT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_PDSCH_START_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/

enum LRRC_LPHY_PDSCH_START_ENUM
{
    LRRC_LPHY_PDSCH_START_RESERVED,
    LRRC_LPHY_PDSCH_START_N1,
    LRRC_LPHY_PDSCH_START_N2,
    LRRC_LPHY_PDSCH_START_N3,
    LRRC_LPHY_PDSCH_START_N4,
    LRRC_LPHY_PDSCH_START_ASSIGNED,
    LRRC_LPHY_PDSCH_START_BUTT
};
typedef VOS_UINT16  LRRC_LPHY_PDSCH_START_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_TRANSMISSION_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/

enum LRRC_LPHY_TRANSMISSION_TYPE_ENUM
{
    LRRC_LPHY_TRANSMISSION_TYPE_LOCALISED                 = 0,                  /*localised*/
    LRRC_LPHY_TRANSMISSION_TYPE_DISTRIBUTED ,                                   /*distributed*/
    LRRC_LPHY_TRANSMISSION_TYPE_BUTT
};
typedef VOS_UINT16  LRRC_LPHY_TRANSMISSION_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_NUMBERPRB_PAIRS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/

enum LRRC_LPHY_NUMBERPRB_PAIRS_ENUM
{
    LRRC_LPHY_NUMBERPRB_PAIRS_N2                 = 0,                           /*N2*/
    LRRC_LPHY_NUMBERPRB_PAIRS_N4 ,                                              /*N4*/
    LRRC_LPHY_NUMBERPRB_PAIRS_N8 ,                                              /*N8*/
    LRRC_LPHY_NUMBERPRB_PAIRS_BUTT
};
typedef VOS_UINT16  LRRC_LPHY_NUMBERPRB_PAIRS_ENUM_UINT16;
#endif

/*****************************************************************************
 枚举名    : LRRC_LPHY_BGSCFG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DSDS特性新增，指示启动背景搜是正常搜网还是真实背景搜
*****************************************************************************/
enum LRRC_LPHY_BGSCFG_TYPE_ENUM
{
    LRRC_LPHY_BGSCFG_TYPE_BGS                    = 0,
    LRRC_LPHY_BGSCFG_TYPE_DSDS                   = 1,
    LRRC_LPHY_BGSCFG_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_BGSCFG_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_LPHY_DSDS_NORF_TYPE_ENUMs
 协议表格  :
 ASN.1描述 :
 枚举说明  : DSDS特性新增，上报NORF的场景
*****************************************************************************/
enum LRRC_LPHY_DSDS_NORF_TYPE_ENUM
{
    LRRC_LPHY_DSDS_NORF_TYPE_OUTOFSYNC             = 0,   /*同失步场景*/
    LRRC_LPHY_DSDS_NORF_TYPE_BUTT
};
typedef VOS_UINT16 LRRC_LPHY_DSDS_NORF_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PS_BAND_ENUM
 枚举说明  : 用于索引不同band的NV列表
*****************************************************************************/
#if defined (TL_PHY_ASIC_K3V5)
enum PS_BAND_ENUM
{
    PS_BAND_7,
    PS_BAND_38,
    PS_BAND_20,
    PS_BAND_40,
    PS_BAND_41,
    PS_BAND_3,
    PS_BAND_1,
    PS_BAND_5,
    PS_BAND_8,
    PS_BAND_39,
    PS_BAND_19,
    PS_BAND_21,
    PS_BAND_2,
    PS_BAND_4,
    PS_BAND_6,
    PS_BAND_9,
    PS_BAND_10,
    PS_BAND_11,
    PS_BAND_12,
    PS_BAND_13,
    PS_BAND_14,
    PS_BAND_17,
    PS_BAND_18,
    PS_BAND_22,
    PS_BAND_23,
    PS_BAND_24,
    PS_BAND_25,
    PS_BAND_26,
    PS_BAND_33,
    PS_BAND_34,
    PS_BAND_35,
    PS_BAND_36,
    PS_BAND_37,
    PS_BAND_42,
    PS_BAND_43,
	PS_BAND_28,
    PS_BAND_128,
    PS_BAND_27,
    PS_BAND_29,
    PS_BAND_30,
    PS_BAND_44,
    PS_BAND_32,
    PS_BAND_103,
    PS_BAND_104,
    PS_BAND_105,
    PS_BAND_106,
    PS_BAND_107,
    PS_BAND_108,
    PS_BAND_109,
    PS_BAND_110,
    PS_BAND_111,
    PS_BAND_112,
    PS_BAND_113,
    PS_BAND_114,
    PS_BAND_115,
    PS_BAND_116,
    PS_BAND_BUTT
};
#else
enum PS_BAND_ENUM
{
    PS_BAND_7,
    PS_BAND_38,
    PS_BAND_20,
    PS_BAND_40,
    PS_BAND_41,
    PS_BAND_3,
    PS_BAND_1,
    PS_BAND_5,
    PS_BAND_8,
    PS_BAND_39,

    PS_BAND_19,
    PS_BAND_21,

    PS_BAND_2,
    PS_BAND_4,
    PS_BAND_6,
    PS_BAND_9,
    PS_BAND_10,
    PS_BAND_11,
    PS_BAND_12,
    PS_BAND_13,
    PS_BAND_14,
    PS_BAND_17,

    PS_BAND_18,
    PS_BAND_22,
    PS_BAND_23,
    PS_BAND_24,
    PS_BAND_25,
    PS_BAND_33,
    PS_BAND_34,
    PS_BAND_35,
    PS_BAND_36,
    PS_BAND_37,

    PS_BAND_42,
    PS_BAND_43,
	PS_BAND_28,
	PS_BAND_26, /* ADDED BY DK */
    /* 非标频段begin */
    //PS_BAND_101,
/*BEGIN DTS2014041603793 c00203521 modify for B28全频段特性*/
    PS_BAND_128,
/*END DTS2014041603793 c00203521 modify for B28全频段特性*/
    PS_BAND_29,
    PS_BAND_32,
    PS_BAND_103,
    PS_BAND_104,
    PS_BAND_105,
    PS_BAND_106,
    PS_BAND_107,
    PS_BAND_108,
    PS_BAND_109,
    PS_BAND_110,
    PS_BAND_111,
    PS_BAND_112,
    PS_BAND_113,
    PS_BAND_114,
    PS_BAND_115,
    PS_BAND_116,
    /* 非标频段end */

    PS_BAND_BUTT
};
#endif
typedef VOS_UINT8 PS_BAND_ENUM_UINT8;


/*****************************************************************************
 结构名    : RRC_PHY_NOTCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC透传MTC NOTCH 启动消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgID;            /*_H2ASN_Skip*/  /* 原语类型*/
    VOS_UINT16                          usOPID;             /* 操作标识 */
    LRRC_LPHY_NOTCH_STATE_ENUM_UINT16   enStartFlag;        /* 启动标识 */
}LRRC_LPHY_NOTCH_REQ_STRU;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : LRRC_LPHY_CANDIDATE_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 先验、候补小区的信息列表数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCellNum;
    VOS_UINT16                          ausCellId[LRRC_LPHY_MAX_CANDIDATE_CELL_NUM];
}LRRC_LPHY_CANDIDATE_CELL_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_FREQ_BAND_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频带信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLowBand;
    VOS_UINT16                          usHighBand;
}LRRC_LPHY_FREQ_BAND_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CELL_SEARCHING_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈指示物理层小区搜索数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                  enMsgId;                      /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                    usOpId;                       /* 操作标识符 */
    VOS_UINT16                                    usFreqInfo;                   /* 频点信息 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                enBandInd;                    /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16           enLteModeType;                /* 指示频点所属的制式类型, FDD或TDD */
    VOS_INT16                                     sRsrpThreshold;               /* 小区搜索过程中要求的RSRP最低门限 */
    LRRC_LPHY_CELL_SEARCH_TYPE_ENUM_UINT16        enCellSearchType;             /* 小区搜索类型 */
    union
    {
        LRRC_LPHY_CANDIDATE_CELL_INFO_LIST_STRU   stBarredCellList;             /* 被bar小区信息 */
        LRRC_LPHY_CANDIDATE_CELL_INFO_LIST_STRU   stCandidateCellList;          /* 先验信息数据结构 */
        LRRC_LPHY_FREQ_BAND_INFO_STRU             stFreqBandInfo;               /* 频段信息 */
    }u;
}LRRC_LPHY_CELL_SEARCHING_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CELL_SEARCHING_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层指示小区搜索结果数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                  enMsgId;                      /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                    usOpId;                       /* 操作标识符 */
    LRRC_LPHY_SEARCH_CELL_RESULT_ENUM_UINT16      enValidInd;                   /* 这个频点上的最强小区是否有效 */
    VOS_UINT16                                    usFreqInfo;                   /* 搜索到的小区的频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                enBandInd;                    /* 频带指示 */
    VOS_UINT16                                    usCellId;                     /* 小区ID */
    VOS_INT16                                     sRsrp;                        /* RSRP测量值 */
    VOS_INT16                                     sRsrq;                        /* RSRQ测量值 */
    VOS_UINT16                                    usNoRfValid;                  /* DSDS特性NoRF指示 */

    VOS_UINT8                                     ucFakeCellInd;                /*假小区指示,上报的假小区时为1 */
    VOS_UINT8                                     ucReserved[3];                /* 保留字段 */

}LRRC_LPHY_CELL_SEARCHING_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BAND_SCAN_RESULT_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 扫频结果数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_BAND_IND_ENUM_UINT16                enBandInd;                    /* 频带指示 */
    VOS_UINT16                                    usBandNum;                    /* 物理层上报的Band数目 */
    LRRC_LPHY_FREQ_BAND_INFO_STRU                 astBandScanResult[LRRC_LPHY_MAX_SCAN_FREQ_NUM];          /* 频段信息 */
}LRRC_LPHY_BAND_SCAN_RESULT_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BAND_SCAN_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈指示物理层扫频数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                  enMsgId;                      /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                    usOpId;                       /* 操作标识符 */
    LRRC_LPHY_BAND_SCAN_TYPE_ENUM_UINT16          enBandScanType;               /* 扫频类型 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                enBandInd;                    /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16           enLteModeType;                /* 指示频点所属的制式类型, FDD或TDD */
    LRRC_LPHY_FREQ_BAND_INFO_STRU                 stFreqBandInfo;               /* 频段信息 */
}LRRC_LPHY_BAND_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BAND_SCAN_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层指示扫频结果数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                  enMsgId;                      /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                    usOpId;                       /* 操作标识符 */
    VOS_UINT16                                    usNoRfValid;                  /* DSDS特性NORF指示 */
    LRRC_LPHY_BAND_SCAN_RESULT_LIST_STRU          stBandScanResult;             /* 扫频结果 */
}LRRC_LPHY_BAND_SCAN_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_FREQ_RSSI_MEAS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈指示物理层扫描指定的各个中心频点1.4M带宽的RSSI的具体频点信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usFreqInfo;                   /* 搜索到的小区的频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                enBandInd;                    /* 频带指示 */
    VOS_INT16                                     sRssi;                        /* RSRP测量值 */
    VOS_UINT16                                    usHighPriFlg;
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16           enLteModeType;
    VOS_UINT16                                    usPssRatio;
}LRRC_LPHY_FREQ_RSSI_MEAS_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_FREQ_RSSI_SCAN_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈指示物理层扫描指定的各个中心频点1.4M带宽的RSSI
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                  enMsgId;                      /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                    usOpId;                       /* 操作标识符 */
    LRRC_LPHY_LTE_BAND_WIDTH_ENUM_UINT16          enScanBandWith;
    VOS_UINT16                                    usNoRfValid;
    VOS_UINT16                                    usRsv;
    VOS_UINT32                                    ulValidNum;
    LRRC_LPHY_FREQ_RSSI_MEAS_INFO_STRU            astMeasInfo[LRRC_LPHY_FREQ_RSSI_MAX_SCAN_NUM];
}LRRC_LPHY_FREQ_RSSI_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_TDD_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDD配置信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SUBFRAME_ASSIGNMENT_ENUM_UINT16               enSa;               /* TDD-Configuration->subframeAssignment */
    LRRC_LPHY_SPECIAL_SUBFRAME_PATTERN_ENUM_UINT16          enSsp;              /* TDD-Configuration->specialSubframePatterns */
}LRRC_LPHY_TDD_CONFIG_INFO_STRU;

/*寻呼下移特性begin*/
/*********************************************************************
* ASN 文本 :S-TMSI
*********************************************************************/
typedef struct
{
    VOS_UINT8                     ucMmec;
    VOS_UINT8                     aucRev[3];
    VOS_UINT32                    ulMTmsi;
}LRRC_LPHY_S_TMSI_STRU;

/*********************************************************************
* ASN 文本 :IMSI
*********************************************************************/
typedef struct
{
    VOS_UINT16                    usCnt;    /*(0, 6..UU_MAX_NUM_OF_IMSI_DSP)*/
    VOS_UINT8                     aucItem[LRRC_LPHY_MAX_NUM_OF_IMSI_DSP];
    VOS_UINT8                     ucRev;
}LRRC_LPHY_IMSI_STRU;

/*********************************************************************
结构名    : PAGING_UE_ID_STRU_DSP
协议表格  :
ASN.1描述 :
结构说明  : UE ID数据结构

*********************************************************************/
typedef struct
{
    VOS_UINT8                       ucSTmsiFlag;
    VOS_UINT8                       ucImsiFlag;
    VOS_UINT8                       aucRev[2];

    LRRC_LPHY_S_TMSI_STRU           stSTmsi;
    LRRC_LPHY_IMSI_STRU             stImsi;

}LRRC_LPHY_PAGING_UE_ID_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_UE_ID_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UE ID数据结构
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32     enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */

    VOS_UINT8                        ucCapAccessRel;
    VOS_UINT8                        aucRev[3];
    LRRC_LPHY_PAGING_UE_ID_STRU      stPagingUeId;

}LRRC_LPHY_PAGING_INFO_REQ_STRU;
/*寻呼下移特性end*/
/*****************************************************************************
 结构名    : LRRC_LPHY_CAMPED_MAINCELL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区驻留数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT16                          usFreqInfo;                             /* 小区的频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteModeType;                          /* 指示频点所属的制式类型, FDD或TDD */
    VOS_UINT16                          usCellId;                               /* 小区ID */
    LRRC_LPHY_BAND_WIDTH_ENUM_UINT16    enDlBandWidth;                          /* 下行带宽,对应空口MasterInformationBlock->dl-Bandwidth字段 */
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16  enAntennaPortsCount;                    /* 传输天线数量,对应空口antennaPortsCount字段 */
    VOS_UINT16                          usReserved;                             /* 保留字段 */
    LRRC_LPHY_TDD_CONFIG_INFO_STRU      stTddConfigInfo;                        /* TDD配置信息,对应空口TDD-Configuration字段  */
}LRRC_LPHY_CAMPED_MAINCELL_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CAMPED_MAINCELL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区驻留数回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    LRRC_LPHY_RESULT_ENUM_UINT16        enResult;                               /* 结果，0表示成功，1表示失败 */
    VOS_UINT16                          usNoRfValid;
    VOS_UINT16                          usRsved;
}LRRC_LPHY_CAMPED_MAINCELL_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_UPLINK_MAXTXPWR_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 最大发射功率配置数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_INT16                           sMaxTxPwr;                              /* 最大发射功率 */
    VOS_UINT16                          usReserved;                             /* 保留字段 */
}LRRC_LPHY_UPLINK_MAXTXPWR_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PBCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PBCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16             enPhyChannelType;            /* 物理信道类型 */
    LRRC_LPHY_CGI_ACQUISITION_METHOD_ENUM_UINT16   enAcqMethod;                 /* 指示CGI获取方式,0表示不进行CGI获取,1表示利用AUTONOMOUS GAP,2表示利用IDLE PERIODS */
}LRRC_LPHY_PBCH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ANTENNA_COMM_INFO_STRU
 协议表格  : MobilityControlInformation->RadioResourceConfigCommon->AntennaInformationCommon
 ASN.1描述 :
 结构说明  : 公共天线相关信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16    enAntennaPortsCount;                  /* 天线口数量 */
    VOS_UINT16                            usReserved;
}LRRC_LPHY_ANTENNA_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ANTENNA_DEDICATED_INFO_STRU
 协议表格  : RadioResourceConfigDedicated->PhysicalConfigDedicated->AntennaInformationDedicated
 ASN.1描述 :
 结构说明  : 专有天线相关信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PDSCH_TM_MODE_ENUM_UINT16   enTransmitMode;                       /* 传输模式 */
    LRRC_LPHY_ANTENNA_SELECT_ENUM_UINT16  enAntennaSelect;                      /* UE传输天线选择，2表示disable,0/1表示enable */
    VOS_UINT16                            usReserved;
    LRRC_LPHY_CODE_BOOK_TYPE_ENUM_UINT16  enCodeBookType;                       /* 指示当前使用的码书的子集受限类型 */
    /* add TM9 n2/n4/n8，n8TM9最大需要109BITS */
    VOS_UINT32                            aulCodebookSubsetRestriction[4];      /* 码书的子集受限,Little-Endian字节序 */
}LRRC_LPHY_ANTENNA_DEDICATED_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_SUBFRAME_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Radio-frames that contain MBSFN subframes occur when equation SFN
 mod radioFrameAllocationPeriod = radioFrameAllocationOffset is satisfied.
 Value n1 for radioframeAllocationPeriod denotes value 1, n2 denotes value 2,
 and so on. When fourFrames is used for subframeAllocation, the equation defines
 the first radio frame referred to in the description below. Values n1 and n2 are
 not applicable when fourFrames is used.

 case LRRC_LPHY_MBSFN_ALLOCATION_TYPE_ONE:
 ulSfnAllocationBitmap:the lower 6 bits are used.
 "1" denotes that the corresponding subframe is allocated for MBSFN.
 The following mapping applies:
 FDD: The first/leftmost bit defines the MBSFN allocation for subframe #1,
      the second bit for #2, third bit for #3 , fourth bit for #6, fifth bit for #7, sixth bit for #8.
 TDD: The first/leftmost bit defines the allocation for subframe #3,
      the second bit for #4, third bit for #7, fourth bit for #8, fifth bit for #9.
      Uplink subframes are not allocated. The last bit is not used.

 case LRRC_LPHY_MBSFN_ALLOCATION_TYPE_FOUR:
 ulSfnAllocationBitmap:the lower 24 bits are used.
 A bit-map indicating MBSFN subframe allocation in four consecutive radio frames,
 "1" denotes that the corresponding subframe is allocated for MBSFN.
 The bitmap is interpreted as follows:
 FDD: Starting from the first radioframe and from the first/leftmost bit in the bitmap,
      the allocation applies to subframes #1, #2, #3 , #6, #7, and #8 in the sequence of the four radio-frames.
 TDD: Starting from the first radioframe and from the first/leftmost bit in the bitmap,
      the allocation applies to subframes #3, #4, #7, #8, and #9 in the sequence of the four radio-frames.
      The last four bits are not used. Uplink subframes are not allocated
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_MBSFN_ALLOCATION_PERIOD_ENUM_UINT16  enRfAllocationPeriod;        /* MBSFN 无线帧分配周期 */
    VOS_UINT16                                     usRfAllocationOffset;        /* MBSFN 无线帧分配偏移 */
    VOS_UINT16                                     usReserved;
    LRRC_LPHY_MBSFN_ALLOCATION_TYPE_ENUM_UINT16    enRfAllocationType;          /* MBSFN 无线帧分配类型 */
    VOS_UINT32                                     ulSfnAllocationBitmap;       /* MBSFN 子帧分配Bitmap,指示对应子帧是否被分配，1:表示该子帧被分配,0:表示未被分配 */
}LRRC_LPHY_MBSFN_SUBFRAME_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_SUBFRAME_CFG_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MBSFN无线帧的子帧预留信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16         enMbsfnCfgEnabled;                /* 用来指示MBSFN配置是否有效 */
    VOS_UINT16                                usCnt;
    LRRC_LPHY_MBSFN_SUBFRAME_CFG_INFO_STRU    stSubframecfg[LRRC_LPHY_MAX_MBSFN_ALLOCATIONS_NUM];
}LRRC_LPHY_MBSFN_SUBFRAME_CFG_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PDSCH_COMM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 公共PDSCH信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PDSCH_PA_ENUM_UINT16          enP_A;                              /* 设置PDSCH传输功率信息,默认值为0 */
    LRRC_LPHY_PDSCH_PB_ENUM_UINT16          enP_B;                              /* PDSCH资源的偏移,默认值为0 */
    VOS_INT16                               sRefSignalPwr;                      /* 参考信号功率 */
    LRRC_LPHY_BAND_WIDTH_ENUM_UINT16        enDlBandWidth;                      /* 下行带宽,对应空口MasterInformationBlock->dl-Bandwidth字段 */
    LRRC_LPHY_PHICH_DURATION_ENUM_UINT16    enPhichDuration;                    /* PHICH-DURATION */
    LRRC_LPHY_PHICH_RESOURCE_ENUM_UINT16    enPhichResOurce;                    /* PHICH-RESOURCE */
    LRRC_LPHY_TDD_CONFIG_INFO_STRU          stTddConfigInfo;                    /* TDD配置信息,对应空口TDD-Configuration字段  */
    LRRC_LPHY_ANTENNA_COMM_INFO_STRU        stAntennaCommInfo;                  /* 公共天线信息 */
}LRRC_LPHY_PDSCH_COMM_INFO_STRU;

#if (FEATURE_ON == FEATURE_LTE_R11)
/*****************************************************************************
 结构名    : LRRC_LPHY_DMRS_CONFIG_STRU
 协议表格  : DMRS-Config-r11
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                               usScramblingId;                    /* scramblingIdentity-r11		INTEGER (0..503) */
    VOS_UINT16                               usScramblingId2;                   /* scramblingIdentity2-r11		INTEGER (0..503) */
}LRRC_LPHY_DMRS_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OPTIONAL_SET_OF_FIELDS_STRU
 协议表格  : optionalSetOfFields-r11
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CRS_PORTS_COUNT_ENUM_UINT16   enCRSPortsCount;                    /* crs-PortsCount-r11 */
    VOS_UINT16                              usCRSFreqShift;                     /* crs-FreqShift-r11 */
    LRRC_LPHY_PDSCH_START_ENUM_UINT16       enPdschStart;                       /* pdsch-Start-r11 */
    VOS_UINT16                              usReserved;

    LRRC_LPHY_MBSFN_SUBFRAME_CFG_LIST_STRU  stMbsfnCfgInfo;                     /* mbsfn-SubframeConfigList-r11 --Need ON */
}LRRC_LPHY_OPTIONAL_SET_OF_FIELDS_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RE_MAP_QCL_CONFIG_STRU
 协议表格  : PDSCH-RE-MappingQCL-Config-r11
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPdschReMapQclConfigId;            /* pdsch-RE-MappingQCL-ConfigId-r11 INTEGER (1..maxRE-MapQCL-r11) */
    VOS_UINT16                              usCsiRSConfigZPId;                  /* csi-RS-ConfigZPId-r11 INTEGER (1..maxCSI-RS-ZP-r11) */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16       enCsiRSConfigNZPIdEnabled;          /* qcl-CSI-RS-ConfigNZPId-r11参数有效标识 */
    VOS_UINT16                              usCsiRSConfigNZPId;                 /* qcl-CSI-RS-ConfigNZPId-r11 --Need OR INTEGER (1..maxCSI-RS-NZP-r11) */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16   enOptionalSetOfFieldsFlag;          /* optionalSetOfFields-r11参数有效标识 */
    VOS_UINT16                              usReserved;

    LRRC_LPHY_OPTIONAL_SET_OF_FIELDS_STRU   stOptionalSetOfFields;              /* optionalSetOfFields-r11 --Need OP */
}LRRC_LPHY_RE_MAP_QCL_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RE_MAP_QCL_CONFIG_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPdschReMapQclConfigNum;           /* pdsch-RE-MappingQCL-ConfigId-r11个数  (1..maxRE-MapQCL-r11) */
    VOS_UINT16                              usReserved;
    LRRC_LPHY_RE_MAP_QCL_CONFIG_STRU        astPdschReMapQclConfig[LRRC_LPHY_MAX_RE_MAP_QCL_NUM];
}LRRC_LPHY_RE_MAP_QCL_CONFIG_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_PDSCH_DEDICATED_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 专有PDSCH信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16       enDMRSConfigEnabled;                /* stDMRSConfigPdsch参数有效标识 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16       enQclOperationEnabled;              /* qcl-Opration参数有效标识 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16       enReMapQclConfigEnabled;            /* PDSCH-RE-MappingQCL-Config-r11参数有效标识 */

    LRRC_LPHY_QCL_OPERATION_ENUM_UINT16     enQclOperation;                     /* qcl-Opration */
    LRRC_LPHY_DMRS_CONFIG_STRU              stDMRSConfigPdsch;                  /* dmrs-ConfigPDSCH-r11 */
    LRRC_LPHY_RE_MAP_QCL_CONFIG_LIST_STRU   stReMapQclConfig;                   /* PDSCH-RE-MappingQCL-Config-r11 */
}LRRC_LPHY_PDSCH_DEDICATED_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_QCL_CRS_INFO_STRU
 协议表格  : qcl-CRS-Info-r11
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usQclScramblingId;                  /* qcl-ScramblingIdentity-r11 (0..503) */
    LRRC_LPHY_CRS_PORTS_COUNT_ENUM_UINT16   enCRSPortsCount;                    /* crs-PortsCount-r11 */

    LRRC_LPHY_MBSFN_SUBFRAME_CFG_LIST_STRU  stMbsfnCfgInfo;                     /* mbsfn-SubframeConfigList-r11 --Need ON */
}LRRC_LPHY_QCL_CRS_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_RS_CONFIG_NZP_INFO_STRU
 协议表格  : CSI-RS-ConfigNZP-r11
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCsiRSConfigNZPId;         /* csi-RS-ConfigNZPId-r11 INTEGER (1..maxCSI-RS-NZP-r11) */
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16              enAntennaPortsCountR11;     /* antennaPortsCount-r11 */
    VOS_UINT16                                      usResourceConfig;           /* resourceConfig-r11 (0..31)*/
    VOS_UINT16                                      usSubframeConfig;           /* subframeConfig-r11 (0..154) */
    VOS_UINT16                                      usScramblingId;             /* scramblingIdentity-r11 (0..503) */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enQclCRSInfoFlag;           /* stQclCRSInfo参数有效标识 */

    LRRC_LPHY_QCL_CRS_INFO_STRU                     stQclCRSInfo;               /* qcl-CRS-Info-r11 -- Need ON */
}LRRC_LPHY_CSI_RS_CONFIG_NZP_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_RS_CONFIG_NZP_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCsiRSConfigNZPNum;                /* CSI-RS-ConfigNZP-r11个数 */
    VOS_UINT16                              usReserved;
    LRRC_LPHY_CSI_RS_CONFIG_NZP_INFO_STRU   astCsiRSConfigNZP[LRRC_LPHY_MAX_CSI_RS_NZP_NUM];
}LRRC_LPHY_CSI_RS_CONFIG_NZP_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_RS_CONFIG_ZP_INFO_STRU
 协议表格  : CSI-RS-ConfigZP-r11
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCsiRSConfigZPId;                  /* csi-RS-ConfigZPId-r11 INTEGER (1..maxCSI-RS-ZP-r11) */
    VOS_UINT16                              usResourceConfigList;               /* resourceConfigList-r11 BIT STRING (SIZE (16))*/
    VOS_UINT16                              usSubframeConfig;                   /* subframeConfig-r11 (0..154) */
    VOS_UINT16                              usReserved;
}LRRC_LPHY_CSI_RS_CONFIG_ZP_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_RS_CONFIG_ZP_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCsiRSConfigZPNum;                 /* CSI-RS-ConfigZP-r11个数 */
    VOS_UINT16                              usReserved;
    LRRC_LPHY_CSI_RS_CONFIG_ZP_INFO_STRU    astCsiRSConfigZP[LRRC_LPHY_MAX_CSI_RS_ZP_NUM];
}LRRC_LPHY_CSI_RS_CONFIG_ZP_INFO_LIST_STRU;
#endif

/*****************************************************************************
 结构名    : LRRC_LPHY_PDSCH_BCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 解广播的PDSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16             enPhyChannelType;            /* 物理信道类型 */
    LRRC_LPHY_CGI_ACQUISITION_METHOD_ENUM_UINT16   enAcqMethod;                 /*指示CGI获取方式，0表示不进行CGA获取，1表示利用AUTONOMOUS,2表示利用IDLE PERIODS*/
    LRRC_LPHY_PDSCH_COMM_INFO_STRU                 stPdschCommInfo;             /* PDSCH公共信息 */
}LRRC_LPHY_PDSCH_BCH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_IDLE_DRX_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE状态下DRX参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_DRX_PAGE_T_ENUM_UINT16      enPaging_DRX_T;                       /* 寻呼周期 */
    LRRC_LPHY_DRX_PAGE_TYPE_ENUM_UINT16   enPaging_Group_Count;                 /* 寻呼组个数 */
    VOS_UINT16                            usUeId;                               /* UE ID */
    VOS_UINT16                            usReserved;
}LRRC_LPHY_IDLE_DRX_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PDSCH_PCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 解寻呼的PDSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16    enPhyChannelType;                     /* 物理信道类型 */
    VOS_UINT16                            usReserved;
    LRRC_LPHY_PDSCH_COMM_INFO_STRU        stPdschCommInfo;                      /* PDSCH公共信息 */
    LRRC_LPHY_IDLE_DRX_INFO_STRU          stIdleDrxInfo;                        /* IDLE态下的DRX参数 */
}LRRC_LPHY_PDSCH_PCH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PDSCH_RACH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 解随机接入响应的PDSCH物理信道参数数据结构
*****************************************************************************/
typedef LRRC_LPHY_PDSCH_BCH_PARA_STRU LRRC_LPHY_PDSCH_RACH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_N1_PUCCH_AN_PERSISTENT_LIST_STRU
 协议表格  : SPS-Configuration->SPS-ConfigurationDL->setup->n1-PUCCH-AN-PersistentList
 ASN.1描述 :
 结构说明  : N1_PUCCH_AN_PERSISTENT列表
*****************************************************************************/
typedef struct
{
    VOS_UINT16               usReserved;
    VOS_UINT16               usCnt;                                             /*(1..4)*/
    VOS_UINT16               ausItem[LRRC_LPHY_MAX_N1_PUCCH_AN_PERSISTENT_NUM]; /* n1Pucch-AN-Persistent:INTEGER (0..2047) */
}LRRC_LPHY_N1_PUCCH_AN_PERSISTENT_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SPS_CONFIG_DL_STRU
 协议表格  : RadioResourceConfigDedicated->SPS-Configuration->SPS-ConfigurationDL
 ASN.1描述 :
 结构说明  : SPS-ConfigurationDL
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_ENUM_UINT16    enDlPersistSchedInterval;   /* semiPersistSchedIntervalDL */
    VOS_UINT16                                      usNumOfSpsProcess;          /* numberOfConfSPS-Processes */
    LRRC_LPHY_N1_PUCCH_AN_PERSISTENT_LIST_STRU      stN1Pucch_An_PersistentList;/* n1-PUCCH-AN-PersistentList */
    LRRC_LPHY_N1_PUCCH_AN_PERSISTENT_LIST_STRU      stN1Pucch_An_PersistentListP1;/* n1PUCCH-AN-PersistentListP1-r10 */
}LRRC_LPHY_SPS_CONFIG_DL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_SUBFRAME_PATTERN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MEAS_SUBFRAME_PATTERN_STRU数据结构
             aulSFCfgBitStr[0]: bit0表示最低位，
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SUBFRAME_PATTERN_TYPE_ENUM_UINT16   enSFPatternType;
    VOS_UINT16                                    usReserved;
    VOS_UINT32                                    aulSFCfgBitStr[3];
}LRRC_LPHY_MEAS_SUBFRAME_PATTERN_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_RS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CSI_RS_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CSI_ANTANNA_PORT_ENUM_UINT16        enAntennaPortsCount;          /* antennaPortsCount-r10 */
    VOS_UINT16                                    usResourceConfig;             /* resourceConfig-r10 */
    VOS_UINT16                                    usSubFrameConfig;             /* subframeConfig-r10 */
    VOS_INT16                                     sPC;                          /* p-C-r10 */
}LRRC_LPHY_CSI_RS_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ZERO_TX_POWER_CSI_RS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ZERO_TX_POWER_CSI_RS_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usZeroTxPowerResCfgList;      /* zeroTxPowerResourceConfigList-r10 */
    VOS_UINT16                                    usZeroTxPowerSfCfg;           /* zeroTxPowerSubframeConfig-r10 */
}LRRC_LPHY_ZERO_TX_POWER_CSI_RS_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_RS_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CSI_RS_CONFIG_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCsiRSValidFlg;              /* stCsiRS是否有效 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enZeroTxPowerCsiRSValidFlg;   /* stZeroTxPowerCsiRS是否有效 */
    LRRC_LPHY_CSI_RS_STRU                         stCsiRS;                      /* csi-RS-r10 */
    LRRC_LPHY_ZERO_TX_POWER_CSI_RS_STRU           stZeroTxPowerCsiRS;           /* zeroTxPowerCSI-RS-r10 */

#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCsiRSCfgNZPInfoListFlg;     /* stCsiRSCfgNZPInfoList是否有效 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCsiRSCfgZPInfoListFlg;      /* stCsiRSCfgZPInfoList是否有效 */
    LRRC_LPHY_CSI_RS_CONFIG_NZP_INFO_LIST_STRU    stCsiRSCfgNZPInfoList;        /* csi-RS-ConfigNZPToAddModList-r11 */
    LRRC_LPHY_CSI_RS_CONFIG_ZP_INFO_LIST_STRU     stCsiRSCfgZPInfoList;         /* csi-RS-ConfigZPToAddModList-r11 */
#endif
}LRRC_LPHY_CSI_RS_CONFIG_STRU;

#if (FEATURE_ON == FEATURE_LTE_R11)
/*****************************************************************************
 结构名    : LRRC_LPHY_CRS_ASSIST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CRS_ASSIST_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usPhyCellId;                  /* physCellId-r11 */
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16            enAntennaPortsCountR11;       /* antennaPortsCount-r11 */
    LRRC_LPHY_MBSFN_SUBFRAME_CFG_LIST_STRU        stMBSFNSfCfgList;             /* mbsfn-SubframeConfigList-r11 */
}LRRC_LPHY_CRS_ASSIST_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CRS_ASSIST_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CRS_ASSIST_INFO_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                               usCellReportNum;                   /* 小区个数 (1..maxCellReport) */
    VOS_UINT16                               usResered;
    LRRC_LPHY_CRS_ASSIST_INFO_STRU           astCRSAssistInfo[LRRC_LPHY_MAX_CELL_REPORT_NUM]; /* CRS-AssistanceInfo-r11 */
}LRRC_LPHY_CRS_ASSIST_INFO_LIST_STRU;

/*****************************************************************************
 结构名    :LRRC_LPHY_RESOURCEBLOCK_ASSIGNMENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_NUMBERPRB_PAIRS_ENUM_UINT16       enNumberPRBPairs;               /*numberPRB-Pairs-r11*/
    VOS_UINT16                                  usReserved;
    VOS_UINT16                                  usBitCnt;                       /* 4..38 有效bit位*/
    VOS_UINT16                                  ausResBlockAssignment[3];       /*resourceBlockAssignment-r11*/
}LRRC_LPHY_RESOURCEBLOCK_ASSIGNMENT_STRU;

/*****************************************************************************
 结构名    :LRRC_LPHY_EPDCCH_SET_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usSetConfigId;                  /*SetConfigId-r11*/
    LRRC_LPHY_TRANSMISSION_TYPE_ENUM_UINT16     enTransmissionType;             /*transmissionType-r11*/
    LRRC_LPHY_RESOURCEBLOCK_ASSIGNMENT_STRU     stResBlockAssignment;           /*resourceBlockAssignment-r11*/
    VOS_UINT16                                  usDmrsScramblingSequenceInt;    /*dmrs-ScramblingSequenceInt-r11 INTEGER (0..503)*/
    VOS_UINT16                                  usPucchResStartOffset;          /*pucch-ResourceStartOffset-r11 INTEGER (0..2047)*/
    VOS_UINT16                                  usReMappingQCLConfigId;         /*可选项 re-MappingQCL-ConfigId-r11 0xFFFF标识无效 */
    VOS_UINT16                                  usReserved;                     /*可选项 保留 对齐*/
}LRRC_LPHY_EPDCCH_SET_CFG_STRU;

/*****************************************************************************
 结构名    :LRRC_LPHY_EPDCCH_SET_CFG_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEpdcchSetCfgNum;                  /*指示SetConfigList数目*/
    VOS_UINT16                              usReserved;                         /*可选项 保留 对齐*/

    LRRC_LPHY_EPDCCH_SET_CFG_STRU           astEpdcchSetCfgList[LRRC_LPHY_MAX_RE_MAP_QCL_NUM];     /*可选项EPDCCH-SetConfigToAddModList*/
}LRRC_LPHY_EPDCCH_SET_CFG_LIST_STRU;

/*****************************************************************************
 结构名    :LRRC_LPHY_EPDCCH_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16       enSfPatternCfgEnabled;              /*SfPatternCfg参数有效标识 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16   enEpdcchSetCfgListFlag;             /*指示stEpdcchSetCfgList是否有效*/
    VOS_UINT16                              usStartSymbol;                      /*可选项 startSymbol-r11 INTEGER (1..4) 0xFFFF指示无效值 */
    VOS_UINT16                              usReserved;

    LRRC_LPHY_MEAS_SUBFRAME_PATTERN_STRU    stSfPatternCfg;                     /*可选项 subframePatternConfig-r11*/
    LRRC_LPHY_EPDCCH_SET_CFG_LIST_STRU      stEpdcchSetCfgList;                 /*可选项EPDCCH-SetConfigToAddModList*/
}LRRC_LPHY_EPDCCH_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_DELTATXD_OFFSETLIST_PUCCH_R11_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM_UINT16 enDeltaTxDOffsetPucchFormat1bCS; /* deltaTxD-OffsetPUCCH-Format1bCS-r11 */
    VOS_UINT16                                  usReserved;
}LRRC_LPHY_DELTATXD_OFFSETLIST_PUCCH_R11_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_N_PUCCH_PARAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usNPucchId;                 /* nPUCCH-Identity-r11 */
    VOS_UINT16                                      usN1PucchAN;                /* n1PUCCH-AN-r11 */
}LRRC_LPHY_N_PUCCH_PARAM_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_DMRS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usNPucchId;                 /* nPUCCH-Identity-r11 INTEGER (0..509) */
    VOS_UINT16                                      usNDmrsCshId;               /* nDMRS-CSH-Identity-r11 INTEGER (0..509) */
}LRRC_LPHY_PUSCH_DMRS_STRU;
#endif


/*****************************************************************************
 结构名    : LRRC_LPHY_PDSCH_DSCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 解数据的PDSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16    enPhyChannelType;                     /* 物理信道类型 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSemiPersistSchedCRntiValidFlg;      /* 指示semiPersistSchedC-RNTI是否有效 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enSpsConfigDlEnabled;                 /* stSpsConfigDl有效标识 */
    VOS_UINT16                            usSemiPersistSchedCRnti;              /* semiPersistSchedC-RNTI */
    LRRC_LPHY_PDSCH_COMM_INFO_STRU        stPdschCommInfo;                      /* PDSCH公共信息 */
    LRRC_LPHY_ANTENNA_DEDICATED_INFO_STRU stAntennaDedicatedInfo;               /* 专用天线信息 */
    LRRC_LPHY_SPS_CONFIG_DL_STRU          stSpsConfigDl;                        /* SPS-ConfigurationDL */
    LRRC_LPHY_CSI_RS_CONFIG_STRU          stCsiRSConfig;                        /* csi-RS-Config-r10 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enCifPresence;                        /* cif-Presence-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enMeasSfPatternPCellValidFlg;
    LRRC_LPHY_MEAS_SUBFRAME_PATTERN_STRU  stMeasSfPatternPCell;                 /* measSubframePatternPCell */
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                            usReserved;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enCRSAssistInfoListEnabled;           /* stCRSAssistInfoList参数有效标识 */
    LRRC_LPHY_CRS_ASSIST_INFO_LIST_STRU   stCRSAssistInfoList;                  /* CRS-AssistanceInfoList-r11 */
    LRRC_LPHY_EPDCCH_CONFIG_STRU          stEPdcchConfig;                       /* EPDCCH-Config-r11 */
    LRRC_LPHY_PDSCH_DEDICATED_INFO_STRU   stPdschDedicatedInfo;                 /* pdsch-ConfigDedicated-v1130 */
#endif

}LRRC_LPHY_PDSCH_DSCH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUCCH_COMM_INFO_STRU
 协议表格  : RadioResourceConfigCommonSIB->PUCCH-ConfigCommon或
             RadioResourceConfigCommon->PUCCH-ConfigCommon
 ASN.1描述 :
 结构说明  : 公共PUCCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_DELTA_PUCCH_SHITF_ENUM_UINT16       enDeltaShift;                 /* PUCCH-ConfigCommon->deltaPUCCH-Shift */
    VOS_UINT16                                    usNrb_Cqi;                    /* PUCCH-ConfigCommon->nRB-CQI */
    VOS_UINT16                                    usNcs_An;                     /* PUCCH-ConfigCommon->nCS-AN */
    VOS_UINT16                                    usN1Pucch_An;                 /* PUCCH-ConfigCommon->n1PUCCH-AN */
}LRRC_LPHY_PUCCH_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ACK_NACK_REPET_STRU
 协议表格  : PUCCH-ConfigDedicated->ackNackRepetition
 ASN.1描述 :
 结构说明  : ACK NACK Repetitiond的数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_REPETITION_FACTOR_ENUM_UINT16       enAckNackRepetitionFactor;  /* PUCCH-ConfigDedicated->ackNackRepetition->repetitionFactor */
    VOS_UINT16                                    usN1PucchAnRep;               /* PUCCH-ConfigDedicated->ackNackRepetition->n1PUCCH-AN-Rep*/
}LRRC_LPHY_ACK_NACK_REPET_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUCCH_FORMAT3_STRU
 协议表格  : PUCCH-ConfigDedicated-v1020->format3-r10
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usN3PucchAnListCnt;         /* 指示ausN3PucchAnList实际使用个数 */
    VOS_UINT16                                      usN3PucchAnListP1Cnt;       /* 指示ausN3PucchAnListP1实际使用个数 */
    VOS_UINT16                                      ausN3PucchAnList[LRRC_LPHY_MAX_N3_PUCCH_AN_LIST_NUM];        /* n3PUCCH-AN-List-r10 */
    VOS_UINT16                                      ausN3PucchAnListP1[LRRC_LPHY_MAX_N3_PUCCH_AN_LIST_P1_NUM];        /* n3PUCCH-AN-ListP1-r10 */
}LRRC_LPHY_PUCCH_FORMAT3_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_N1_PUCCH_AN_CS_STRU
 协议表格  : PUCCH-ConfigDedicated-v1020->channelSelection-r10
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usN1PucchAnCsCnt;         /* 指示ausN3PucchAnList实际使用个数 */
    VOS_UINT16                                      ausN1PucchAnCs[LRRC_LPHY_MAX_N1_PUCCH_AN_CS_NUM];        /* n3PUCCH-AN-List-r10 */
    VOS_UINT16                                      usReserved;
}LRRC_LPHY_N1_PUCCH_AN_CS_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUCCH_CHANNEL_SEL_STRU
 协议表格  : PUCCH-ConfigDedicated-v1020->channelSelection-r10
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usN1PucchAnCsListCnt;       /* 指示ausN3PucchAnList实际使用个数 */
    VOS_UINT16                                      usReserved;
    LRRC_LPHY_N1_PUCCH_AN_CS_STRU                   astN1PucchAnCsList[LRRC_LPHY_MAX_N1_PUCCH_AN_CS_LIST_NUM];        /* n1PUCCH-AN-CS-List-r10 */
}LRRC_LPHY_PUCCH_CHANNEL_SEL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUCCH_DEDICATED_INFO_STRU
 协议表格  : PhysicalConfigDedicated->PUCCH-ConfigDedicated
 ASN.1描述 :
 结构说明  : 专用PUCCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enAckNackRepetitionEnabled; /* AckNackRepetition参数有效标识 */
    LRRC_LPHY_TDD_FEEDBACK_MODE_ENUM_UINT16         enTddAckNackFeedbackMode;   /* PUCCH-ConfigDedicated->tddAckNackFeedbackMode */
    LRRC_LPHY_ACK_NACK_REPET_STRU                   stAckNackRepetition;        /* PhysicalConfigDedicated->PUCCH-ConfigDedicated */
    VOS_UINT16                                      usReserved;
    LRRC_LPHY_PUCCH_FORMAT_TYPE_ENUM_UINT16         enPucchFormatType;          /* 如果没有PUCCH FORMAT参数，此处类型填BUTT */
    union
    {
        LRRC_LPHY_PUCCH_FORMAT3_STRU                stPucchFormat3;
        LRRC_LPHY_PUCCH_CHANNEL_SEL_STRU            stPucchChannelSel;
    }u;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enTwoAntennaPortActPucchFormat1a1b; /* twoAntennaPortActivatedPUCCH-Format1a1b-r10 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enSimulPucchPusch;          /* simultaneousPUCCH-PUSCH-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enN1PucchAnRepP1ValidFlg;   /* usN1PucchAnRepP1有效标识 */
    VOS_UINT16                                      usN1PucchAnRepP1;           /* n1PUCCH-AN-RepP1-r10 INTEGER (0..2047)*/
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enN1PucchAnCSEnabled;       /* stN1PucchAnCSListP1 有效标识 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enNPucchParamEnabled;       /* stNPucchParam 有效标识 */
    LRRC_LPHY_N1_PUCCH_AN_CS_STRU                   stN1PucchAnCSListP1;        /* n1PUCCH-AN-CS-ListP1-r11 --Need ON */
    LRRC_LPHY_N_PUCCH_PARAM_STRU                    stNPucchParam;              /* nPUCCH-Param-r11 --Need ON */
#endif
}LRRC_LPHY_PUCCH_DEDICATED_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SR_CONFIG_INFO_STRU
 协议表格  : PhysicalConfigDedicated->SchedulingRequest-Configuration
 ASN.1描述 :
 结构说明  : 调度请求配置信息参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usSrPucchResIdx;              /* SchedulingRequest-Configuration->sr-PUCCH-ResourceIndex */
    VOS_UINT16                                    usSrConfigIdx;                /* SchedulingRequest-Configuration->sr-ConfigurationIndex */
    LRRC_LPHY_DSR_TRANS_MAX_ENUM_UINT16           enDsrTransMax;                /* SchedulingRequest-Configuration->dsr-TransMax */
    /* v7r2 interface begin */
    VOS_UINT16                                    usReserved;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enSrPucchResourceIndexP1ValidFlg;   /* usSrPucchResourceIndexP1有效标识 */
    VOS_UINT16                                    usSrPucchResourceIndexP1;     /* sr-PUCCH-ResourceIndexP1-r10*/
    /* v7r2 interface end */
}LRRC_LPHY_SR_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUCCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PUCCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16              enPhyChannelType;             /* 物理信道类型 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDedicatedInfoValidFlag;     /* 专用PUCCH信道参数有效标识 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enSrConfigInfoValidFlag;      /* SR调度配置参数有效标识 */
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM_UINT16      enUlCPLen;                    /* 上行CP长度 */
    LRRC_LPHY_PUCCH_COMM_INFO_STRU                  stPucchCommInfo;              /* 公共PUCCH信道参数 */
    LRRC_LPHY_PUCCH_DEDICATED_INFO_STRU             stDedicatedInfo;              /* 专用PUCCH信道参数 */
    LRRC_LPHY_SR_CONFIG_INFO_STRU                   stSrConfigInfo;               /* SchedulingRequest-Configuration参数 */
}LRRC_LPHY_PUCCH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_BASIC_CONFIG_STRU
 协议表格  : PUSCH-Configuration->PUSCH-ConfigCommon->pusch-ConfigBasic
 ASN.1描述 :
 结构说明  : PUSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PUSCH_N_SB_ENUM_UINT16              enNSb;                        /* n-SB */
    LRRC_LPHY_PUSCH_HOPPING_MODE_ENUM_UINT16      enHoppingMode;                /* hoppingMode */
    VOS_UINT16                                    usHoppingOffset;              /* pusch-HoppingOffset */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enEnable64Qam;                /* enable64Qam,1:enable，0:disable */
}LRRC_LPHY_PUSCH_BASIC_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_UL_REF_SIGNAL_STRU
 协议表格  : PUSCH-Configuration->PUSCH-ConfigCommon->UL-ReferenceSignalsPUSCH
 ASN.1描述 :
 结构说明  : PUSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16   usGroupHoppingEnabled;                  /* groupHoppingEnabled */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16   usSequenceHoppingEnabled;               /* sequenceHoppingEnabled */
    VOS_UINT16                          usGroupAssignmentPUSCH;                 /* groupAssignmentPUSCH */
    VOS_UINT16                          usCyclicShift;                          /* cyclicShift */
}LRRC_LPHY_PUSCH_UL_REF_SIGNAL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_BETA_OFFSET_MC_STRU
 协议表格  : PUSCH-Configuration->PUSCH-ConfigDedicated
 ASN.1描述 :
 结构说明  : 专有PUSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                            usOffsetAckIdxMc;                     /* betaOffset-ACK-Index-MC-r10 */
    VOS_UINT16                            usOffsetRiIdxMc;                      /* betaOffset-RI-Index-MC-r10 */
    VOS_UINT16                            usOffsetCqiIdxMc;                     /* betaOffset-CQI-Index-MC-r10 */
    VOS_UINT16                            usReserved;
}LRRC_LPHY_PUSCH_BETA_OFFSET_MC_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_COMM_INFO_STRU
 协议表格  : PUSCH-Configuration->PUSCH-ConfigCommon
 ASN.1描述 :
 结构说明  : 公共PUSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                            usMaxHarqMsg3Tx;                      /* maxHARQ-Msg3Tx */
    VOS_UINT16                            usReserved;
    LRRC_LPHY_PUSCH_BASIC_CONFIG_STRU     stPuschBasicConfig;                   /* PUSCH基本配置信息 */
    LRRC_LPHY_PUSCH_UL_REF_SIGNAL_STRU    stPuschUlRefSignal;                   /* 上行参考信号PUSCH参数 */
}LRRC_LPHY_PUSCH_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_DEDICATED_INFO_STRU
 协议表格  : PUSCH-Configuration->PUSCH-ConfigDedicated
 ASN.1描述 :
 结构说明  : 专有PUSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                            usOffsetAckIdx;     /* deltaOffset-ACK-Index */
    VOS_UINT16                            usOffsetRiIdx;      /* deltaOffset-RI-Index */
    VOS_UINT16                            usOffsetCqiIdx;     /* deltaOffset-CQI-Index */
    LRRC_LPHY_MAX_HARQ_TX_ENUM_UINT16     enUlMaxHarqTxNum;   /* maxHARQ-Tx */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enTtiBundlingFlg;   /* ttiBundling */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enPuschBetaOffsetMcValidFlg;
    LRRC_LPHY_PUSCH_BETA_OFFSET_MC_STRU   stPuschBetaOffsetMc;                  /* betaOffsetMC-r10 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enGroupHopDisabled;                   /* groupHoppingDisabled-r10 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enDmrsWithOccActivated;               /* dmrs-WithOCC-Activated-r10 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                            usReserved;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enPuschDMRSEnabled;                   /* stPuschDMRS是否有效 */
    LRRC_LPHY_PUSCH_DMRS_STRU             stPuschDMRS;                          /* pusch-DMRS-r11 */
#endif
}LRRC_LPHY_PUSCH_DEDICATED_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUCCH_DELTAF_LIST_STRU
 协议表格  : RadioResourceConfigCommonSIB->UplinkPowerControlCommon->deltaFList-PUCCH
              RadioResourceConfigCommon->UplinkPowerControlCommon->deltaFList-PUCCH
 ASN.1描述 :
 结构说明：专有PUSCH物理层信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_DELTAF_FORMAT_ENUM_UINT16   enFormat1;          /* deltaF-PUCCH-Format1 */
    LRRC_LPHY_DELTAF_FORMAT_ENUM_UINT16   enFormat1b;         /* deltaF-PUCCH-Format1b */
    LRRC_LPHY_DELTAF_FORMAT_ENUM_UINT16   enFormat2;          /* deltaF-PUCCH-Format2 */
    LRRC_LPHY_DELTAF_FORMAT_ENUM_UINT16   enFormat2a;         /* deltaF-PUCCH-Format2a */
    LRRC_LPHY_DELTAF_FORMAT_ENUM_UINT16   enFormat2b;         /* deltaF-PUCCH-Format2b */
    VOS_UINT16                            usReserved;
}LRRC_LPHY_PUCCH_DELTAF_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_POWER_CTRL_COMM_INFO_SCELL_STRU
 协议表格  : RadioResourceConfigCommon->UplinkPowerControlCommonSCell-r10
 ASN.1描述 :
 结构说明  : 公共PUSCH物理信道功率控制参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                             sPuschP0Nominal;                        /* p0-NominalPUSCH */
    LRRC_LPHY_PWR_CTRL_ALPHA_ENUM_UINT16  enAlpha;                                /* α*/
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enDeltaPreambleMsg3Enabled;           /* sDeltaPreambleMsg3s 是否存在 */
    VOS_INT16                             sDeltaPreambleMsg3;                   /* deltaPreambleMsg3-r11  */
#endif

}LRRC_LPHY_POWER_CTRL_COMM_INFO_SCELL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_DELTATXD_OFFSETLIST_PUCCH_STRU
 协议表格  : PhysicalConfigDedicated->UplinkPowerControlDedicated->DeltaTxD-OffsetListPUCCH-r10
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM_UINT16 enDeltaTxDOffsetPucchFormat1;    /* deltaTxD-OffsetPUCCH-Format1-r10 */
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM_UINT16 enDeltaTxDOffsetPucchFormat1a1b; /* deltaTxD-OffsetPUCCH-Format1a1b-r10 */
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM_UINT16 enDeltaTxDOffsetPucchFormat22a2b;/* deltaTxD-OffsetPUCCH-Format22a2b-r10 */
    LRRC_LPHY_DELTATXD_OFFSET_PUCCH_ENUM_UINT16 enDeltaTxDOffsetPucchFormat3;    /* deltaTxD-OffsetPUCCH-Format3-r10 */
}LRRC_LPHY_DELTATXD_OFFSETLIST_PUCCH_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_POWER_CTRL_COMM_INFO_STRU
 协议表格  : RadioResourceConfigCommonSIB->UplinkPowerControlCommon
              RadioResourceConfigCommon->UplinkPowerControlCommon
 ASN.1描述 :
 结构说明  : 公共PUSCH物理信道功率控制参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                             sPuschP0Nominal;                        /* p0-NominalPUSCH */
    LRRC_LPHY_PWR_CTRL_ALPHA_ENUM_UINT16  enAlpha;                                /* α*/
    VOS_INT16                             sPucchP0Nominal;                        /* p0-NominalPUCCH */
    VOS_INT16                             sDeltaPreambleMsg3;                     /* deltaPreambleMsg3 */
    LRRC_LPHY_PUCCH_DELTAF_LIST_STRU      stPucchDeltaFlist;                      /* deltaFList-PUCCH */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDeltaFPucchFormat3ValidFlg;   /* enDeltaFPucchFormat3是否有效标识 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT3_ENUM_UINT16      enDeltaFPucchFormat3;           /* deltaF-PUCCH-Format3-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDeltaFPucchFormat1bCsValidFlg;/* enDeltaFPucchFormat1bCs是否有效标识 */
    LRRC_LPHY_DELTAF_PUCCH_FORMAT1BCS_ENUM_UINT16   enDeltaFPucchFormat1bCs;        /* deltaF-PUCCH-Format1bCS-r10 */
}LRRC_LPHY_POWER_CTRL_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_POWER_CTRL_DEDICATED_INFO_STRU
 协议表格  : PhysicalConfigDedicated->UplinkPowerControlDedicated
 ASN.1描述 :
 结构说明  : 专有PUSCH物理信道功率控制参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                             sPuschP0Ue;                                     /* p0-UePUSCH */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enDeltaMcsEnabled;                              /* deltaMCS-Enabled */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enAccumlatEnabled;                              /* accumulationEnabled */
    VOS_INT16                             sPucchP0Ue;                                     /* p0-uePUCCH */
    VOS_UINT16                            usPsrsOffset;                                   /* pSRS-Offset */
    LRRC_LPHY_FILTER_COEFF_ENUM_UINT16    enFilterCoeff;                                  /* FilterCoefficient */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enPSrsOffsetApValidFlg;               /* pSRS-OffsetAp-r10  是否有效标识 */
    VOS_UINT16                                      usPSrsOffsetAp;                       /* pSRS-OffsetAp-r10 INTEGER (0..15)*/
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDeltaTxDOffsetListPucchValidFlg;    /* DeltaTxD-OffsetListPUCCH-r10 是否有效标识  */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDeltaTxDOffsetListPucchR11ValidFlg; /* DeltaTxD-OffsetListPUCCH-r11 是否有效标识  */
#else
    VOS_UINT16                                      usReserved;
#endif
    LRRC_LPHY_DELTATXD_OFFSETLIST_PUCCH_STRU        stDeltaTxDOffsetListPucch;
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_DELTATXD_OFFSETLIST_PUCCH_R11_STRU    stDeltaTxDOffsetListPucchR11;         /* DeltaTxD-OffsetListPUCCH-v1130 */
#endif
}LRRC_LPHY_POWER_CTRL_DEDICATED_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_TPC_PDCCH_CONFIG_STRU
 协议表格  : PhysicalConfigDedicated->TPC-PDCCH-Configuration
 ASN.1描述 :
 结构说明  : TPC-PDCCH-Configuration
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usTpc_Rnti;                   /* tpc-RNTI */
    LRRC_LPHY_INDEX_FORMAT_TYPE_ENUM_UINT16       enTpcFormatType;              /* tpc-Index->choice */
    VOS_UINT16                                    usTpcIdx;                     /* tpc-Index->indexOfFormat3/indexOfFormat3A */
    VOS_UINT16                                    usReserved;
}LRRC_LPHY_TPC_PDCCH_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_P0_PERSISTENT_STRU
 协议表格  : RadioResourceConfigDedicated->SPS-Configuration->SPS-ConfigurationUL
 ASN.1描述 :
 结构说明  : p0-Persistent
*****************************************************************************/
typedef struct
{
    VOS_INT16                            sP0NominalPuschPersistent;             /* p0-NominalPUSCH-Persistent */
    VOS_INT16                            sP0UePuschPersistent;                  /* p0-UePUSCH-Persistent */
}LRRC_LPHY_P0_PERSISTENT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SPS_CONFIG_UL_STRU
 协议表格  : RadioResourceConfigDedicated->SPS-Configuration->SPS-ConfigurationUL
 ASN.1描述 :
 结构说明  : SPS-ConfigurationUL
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PERSIST_SCHED_INTERVAL_ENUM_UINT16    enUlPersistSchedInterval;     /* semiPersistSchedIntervalUL */
    LRRC_LPHY_IMPLICIT_REL_AFTER_ENUM_UINT16        enImplicitRelAfter;           /* implicitReleaseAfter */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enTwoIntervalsCfgValidFlg;    /* twoIntervalsConfig */
    VOS_UINT16                                      usReserved;
    LRRC_LPHY_P0_PERSISTENT_STRU                    stP0Persistent;               /* p0-Persistent */
}LRRC_LPHY_SPS_CONFIG_UL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ANTENNA_INFO_UL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ANTENNA_INFO_UL_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enTransmissionModeULValidFlg; /* transmissionModeUL-r10是否有效 */
    LRRC_LPHY_TRANSMISSION_MODE_ENUM_UINT16       enTransmissionModeUL;         /* transmissionModeUL-r10 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             en4AntennaPortActivated;      /* fourAntennaPortActivated-r10 1: setup, Activated only if transmissionModeUL is set to tm2*/
    VOS_UINT16                                    usReserved;
}LRRC_LPHY_ANTENNA_INFO_UL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PUSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16              enPhyChannelType;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDedicatedPuschInfoValidFlag;/* 专用PUSCH信道参数有效标识 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDedicatedPwrCtrlValidFlag;  /* 专用Pwr Ctrl参数有效标识 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enPucchTpcConfigEnabled;      /* TPC PUCCH参数有效标识 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enPuschTpcConfigEnabled;      /* TPC PUSCH参数有效标识 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enSpsConfigUlEnabled;         /* SPS-ConfigurationUL有效标识 */
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM_UINT16      enUlCPLen;                    /* 上行CP长度 */
    VOS_UINT16                                      usUlFreqInfo;                 /* 上行频率, 对应空口SystemInformationBlockType2->ul-EARFCN, 缺省时根据36.101进行计算 */
    LRRC_LPHY_BAND_WIDTH_ENUM_UINT16                enUlBandWidth;                /* 上行带宽,对应空口SystemInformationBlockType2->ul-Bandwidth，缺省时填写下行带宽 */
    VOS_UINT16                                      usAdditionalSpecEmission;     /* 对应空口SystemInformationBlockType2->additionalSpectrumEmission, 保留字段 */
    LRRC_LPHY_PUSCH_COMM_INFO_STRU                  stPuschCommInfo;              /* 公共PUSCH配置参数 */
    LRRC_LPHY_PUSCH_DEDICATED_INFO_STRU             stPuschDedicatedInfo;         /* 专有PUSCH配置参数 */
    LRRC_LPHY_POWER_CTRL_COMM_INFO_STRU             stPwrCtrlCommInfo;            /* 公共功率控制信息 */
    LRRC_LPHY_POWER_CTRL_DEDICATED_INFO_STRU        stPwrCtrlDedicatedInfo;       /* 专有功率控制信息 */
    LRRC_LPHY_TPC_PDCCH_CONFIG_STRU                 stPucchTpcConfig;             /* tpc-PDCCH-ConfigPUCCH */
    LRRC_LPHY_TPC_PDCCH_CONFIG_STRU                 stPuschTpcConfig;             /* tpc-PDCCH-ConfigPUSCH */
    LRRC_LPHY_SPS_CONFIG_UL_STRU                    stSpsConfigUl;                /* SPS-Configuration->SPS-ConfigurationUL */
    LRRC_LPHY_ANTENNA_INFO_UL_STRU                  stAntennaInfoUL;              /* antennaInfoUL-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enAdditSpecEmissionPCellFlg;  /* usAdditSpecEmissionPCell是否有效标示 */
    VOS_UINT16                                      usAdditSpecEmissionPCell;     /* additionalSpectrumEmissionPCell */
}LRRC_LPHY_PUSCH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PRACH_CONFIG_STRU
 协议表格  : RadioResourceConfigCommonSIB->PRACH-ConfigurationSIB
              RadioResourceConfigCommon->PRACH-Configuration
 ASN.1描述 :
 结构说明  : PRACH物理信道配置参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usRootSequenceIndex;          /* PRACH-Configuration->rootSequenceIndex */
    VOS_UINT16                                    usConfigIndex;                /* PRACH-Configuration->prach-ConfigurationIndex */
    VOS_UINT16                                    usHighSpeedFlg;               /* PRACH-Configuration->highSpeedFlag */
    VOS_UINT16                                    usZeroCorrelationZoneConfig;  /* zeroCorrelationZoneConfig */
    VOS_UINT16                                    usFrequencyOffset;            /* prach-FrequencyOffset */
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM_UINT16    enUlCPLen;                    /* 上行CP长度 */
}LRRC_LPHY_PRACH_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PRACH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16    enPhyChannelType;
    VOS_UINT16                            usReserved;
    LRRC_LPHY_PRACH_CONFIG_STRU           stPrachInfo;
}LRRC_LPHY_PRACH_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RL_SETUP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层信道建立请求数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT16                          usFreqInfo;                             /* 小区的频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteModeType;                          /* 指示频点所属的制式类型, FDD或TDD */
    VOS_UINT16                          usCellId;                               /* 小区ID */
    VOS_UINT16                          usReserved;                             /* 保留字段 */
    VOS_UINT16                          usPhyChannelNum;                        /* 指示本次建立的信道数量 */
    VOS_UINT16                          usParaSize;                             /* 指示本次建立的信道参数的总长度 */
    VOS_UINT8                           aucPhyChannelPara[4];                   /* 物理信道配置参数 */
}LRRC_LPHY_RL_SETUP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RL_SETUP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层信道建立回复结果数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16    enPhyChannelType;
    LRRC_LPHY_RESULT_ENUM_UINT16          enRlConfigResult;
}LRRC_LPHY_RL_CONFIG_RESULT;

/*****************************************************************************
 结构名    : LRRC_LPHY_RL_SETUP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层信道建立回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT16                          usFreqInfo;                             /* 小区的频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    VOS_UINT16                          usCellId;                               /* 小区ID */
    VOS_UINT16                          usReserved;                             /* 保留字段 */
    VOS_UINT16                          usPhyChannelNum;
    LRRC_LPHY_RL_CONFIG_RESULT          astRlSetupRslt[LRRC_LPHY_MAX_CHANNEL_NUM];
}LRRC_LPHY_RL_SETUP_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RL_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层信道建立请求数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16    enPhyChannelType;
    LRRC_LPHY_PDSCH_SETUP_FLAG_ENUM_INT16 enPdschSetupFlag;
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                            usSCellIdx;                           /* SCELL索引, 0标识PCELL */
    VOS_UINT16                            usReserved;
#endif
}LRRC_LPHY_RL_RELEASE_CHANNAL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RL_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层信道释放数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32            enMsgId;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usOpId;
    VOS_UINT16                              usFreqInfo;
    LRRC_LPHY_BAND_IND_ENUM_UINT16          enBandInd;                          /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16     enLteModeType;                      /* 指示频点所属的制式类型, FDD或TDD */
    VOS_UINT16                              usCellId;
    VOS_UINT16                              usPhyChannelNum;
    LRRC_LPHY_RL_RELEASE_CHANNAL_INFO_STRU  astChannelInfo[LRRC_LPHY_MAX_CHANNEL_NUM];
}LRRC_LPHY_RL_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RL_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层信道释放回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usFreqInfo;
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    VOS_UINT16                          usCellId;
    VOS_UINT16                          usReserved;                             /* 保留字段 */
    VOS_UINT16                          usPhyChannelNum;
    LRRC_LPHY_RL_CONFIG_RESULT          astRlReleaseRslt[LRRC_LPHY_MAX_CHANNEL_NUM];
}LRRC_LPHY_RL_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SYNC_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 启动物理层同步请求数据结构,目前只是保留原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usEnableFlg;                            /* 0：表示停止同步指示上报
                                                                                   1：表示启动同步指示上报
                                                                                   2：表示启动失步指示上报 */
}LRRC_LPHY_SYNC_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SYNC_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 启动物理层同步请求回复数据结构,目前只是保留原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usRsd;
}LRRC_LPHY_SYNC_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SYNC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报同步数据结构,目前只是保留原语
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                                /*_H2ASN_Skip*/
}LRRC_LPHY_SYNC_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OUT_OF_SYNC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层上报失步请求回复数据结构,目前只是保留原语
*****************************************************************************/
typedef LRRC_LPHY_SYNC_IND_STRU LRRC_LPHY_OUT_OF_SYNC_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_SF_PATTERN_CFG_NEIGH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MEAS_SF_PATTERN_CFG_NEIGH_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_MEAS_SUBFRAME_PATTERN_STRU  stMeasSfPattern;
    /* CEll ID位图,每一Bit对应一个CellId, 若某bit为1，表示配置该小区
      ulMeasSfCellBmp[0]的 bit0 : 表示CellId为  0 的小区
      ulMeasSfCellBmp[0]的 bit31: 表示CellId为 31 的小区
      ulMeasSfCellBmp[1]的 bit0 : 表示CellId为 32 的小区
      ......
      ......
      */
    VOS_UINT32                            aulMeasSfCellBmp[16];
}LRRC_LPHY_MEAS_SF_PATTERN_CFG_NEIGH_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SCELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_SCELL_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    /* SCELL stru including SCellIndex and phyCellId
    and measCycleSCell and bit-indicator if SCELL is configured */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16   enSCellInfoValidFlg;                /* 指示下面内容是否有效 */
    VOS_UINT16                              usSCellIdx;                         /* 范围1~7 */
    VOS_UINT16                              usSCellId;                          /* SCELL的物理小区ID*/
    LRRC_LPHY_MEAS_CYCLE_SCELL_ENUM_UINT16  enMeasCycleSCell;                   /* MeasCycleSCell-r10 */
}LRRC_LPHY_SCELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SINGLE_FREQ_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单个频点小区信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteModeType;                          /* 指示频点所属的制式类型, FDD或TDD */
    /*neighCellConfig:
      Provides information related to MBSFN and TDD UL/DL configuration of neighbour cells of this frequency
      00: Not all neighbour cells have the same MBSFN subframe allocation as serving cell
      10: The MBSFN subframe allocations of all neighbour cells are identical to or subsets of that in the serving cell
      01: No MBSFN subframes are present in all neighbour cells
      11: Different UL/DL allocation in neighbouring cells for TDD compared to the serving cell
      For TDD, 00, 10 and 01 are only used for same UL/DL allocation in neighbouring cells compared to the serving cell.*/
    VOS_UINT16                          usNeighCellConfigBitmap;                /* 最低两位有效 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16   enPresenceAntennaPort1;
    VOS_UINT16                          usDetectedCellMeasInd;
    LRRC_LPHY_BAND_WIDTH_ENUM_UINT16    enMeasBandWidth;
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                          usPriorSel;                             /* 同频重选优先级，IDLE态有效 ，CONNECT态保留*/
#else
    VOS_UINT16                          usReserved;                             /* 保留字段 */
#endif
    VOS_UINT16                          usCellNum;
    VOS_UINT16                          ausCellIdList[LRRC_LPHY_MAX_FREQ_CELL_NUM]; /* 若测量对象中没有配置测量小区，但是重配置中有SCELL, 需要将SCELL放入此列表。*/

    /* v7r2 interface begin */
    VOS_UINT16                               usReserved1;                       /* 保留字段 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16    enMeasSfPatternNeighValidFlg;
    LRRC_LPHY_MEAS_SF_PATTERN_CFG_NEIGH_STRU stMeasSfPatternNeigh;              /* MeasSubframePatternConfigNeigh-r10 */
    /* v7r2 interface end */
}LRRC_LPHY_SINGLE_FREQ_CELL_INFO_STRU;
typedef LRRC_LPHY_SINGLE_FREQ_CELL_INFO_STRU LRRC_LPHY_INTRA_FREQ_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SECOND_SINGLE_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单个SCELL频点小区信息数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SINGLE_FREQ_CELL_INFO_STRU     stSingleFreqInfo;
    LRRC_LPHY_SCELL_INFO_STRU                stSCellInfo;                       /* SCELL信息 */
}LRRC_LPHY_SECOND_SINGLE_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_INTER_FREQ_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异频小区信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usInterFreqNum;                         /* 总频点数目 */
    VOS_UINT16                          usHighPriorFreqNum;                     /* 高优先级频点数目 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                          usHighestPrior;                         /* 所有频点中优先级最高的优先级，IDLE态有效，CONNECT态无效*/
    VOS_UINT16                          usReserved;
#endif
    /* 数组前usHighPriorFreqNum个用来存放高优先级频点信息，usInterFreqNum-usHighPriorFreqNum为等优先级和低优先级频点信息 */
    LRRC_LPHY_SINGLE_FREQ_CELL_INFO_STRU  astInterCellList[LRRC_LPHY_MAX_ADDITIONAL_CARRIER_NUM];
}LRRC_LPHY_INTER_FREQ_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_IRAT_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异系统频点信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcnNum;                             /* 总频点数目 */
    VOS_UINT16                          usHighPriorArfcnNum;                    /* 高优先级频点数目，usArfcnNum-usHighPriorArfcnNum为低优先级频点数目 */
    VOS_UINT16                          usMgsmNum;                              /* GSM载波分组数，连接态有效，IDLE态该字段保留 */
    LRRC_LPHY_RAT_TYPE_ENUM_UINT16      enMeasRatType;
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                          usHighestPrior;                         /* 所有频点中优先级最高的优先级，IDLE态有效，CONNECT态无效*/
    VOS_UINT16                          usReserved;
#endif
}LRRC_LPHY_IRAT_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SECOND_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 辅频小区信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usSecondFreqNum;                    /* 总频点数目 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT8                               ucAllowInterruptions;               /* allowInterruptions: Value TRUE indicates that the UE is allowed to cause interruptions
                                                                                   to serving cells when performing measurements of deactivated SCell carriers for measCycleSCell
                                                                                   of less than 640ms, as specified in TS 36.133 [16]. E-UTRAN enables this field only when an SCell
                                                                                   is configured.*/
    VOS_UINT8                               ucReserved;
#else
    VOS_UINT16                              usReserved;
#endif
    LRRC_LPHY_SECOND_SINGLE_FREQ_INFO_STRU  astFreqList[LRRC_LPHY_MAX_SECONDARY_CARRIER_NUM];
}LRRC_LPHY_SECOND_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_IRAT_IDLE_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE异系统数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_IRAT_FREQ_INFO_STRU         stIratGsmFreqInfo;
    LRRC_LPHY_IRAT_FREQ_INFO_STRU         stIratUtraFreqInfo;
    LRRC_LPHY_IRAT_FREQ_INFO_STRU         stIratCdmaFreqInfo;    /* CDMA异系统测量信息 */
}LRRC_LPHY_IRAT_IDLE_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_IRAT_CONN_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CONN异系统数据结构
*****************************************************************************/
typedef LRRC_LPHY_IRAT_IDLE_FREQ_INFO_STRU  LRRC_LPHY_IRAT_CONN_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 测量类型
*****************************************************************************/
enum LRRC_LPHY_MEAS_TYPE_ENUM
{
    LRRC_LPHY_MEAS_TYPE_CONTINUOUS            = 0,                              /* 连续测量 */
    LRRC_LPHY_MEAS_TYPE_SINGLE                = 1,                              /* 单次测量，物理层上报完测量IND，自己进行测量释放 */

    LRRC_LPHY_MEAS_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LPHY_MEAS_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_IN_IDLE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE测量数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_MEAS_COMMAND_ENUM_UINT16    enCommand;                            /* 测量命令 */
    LRRC_LPHY_RAT_TYPE_ENUM_UINT16        enRatType;                            /* 指示当前主模类型 */
    LRRC_LPHY_MEAS_TYPE_ENUM_UINT8        enMeasType;                           /* 测量类型：0：连续测量；1：单次测量 */
    VOS_UINT8                             ucRsvd;
    LRRC_LPHY_INTRA_FREQ_CELL_INFO_STRU   stIntraFreqCell;                      /* 频内测量信息 */
    LRRC_LPHY_INTER_FREQ_CELL_INFO_STRU   stInterFreqCell;                      /* LTE内异频测量或GU->LTE测量时,通过该列表配置测量信息 */
    LRRC_LPHY_IRAT_IDLE_FREQ_INFO_STRU    stIratFreqInfo;                       /* LTE->GU测量时，异系统测量信息 */
}LRRC_LPHY_MEAS_IN_IDLE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_IN_IDLE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE下测量回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
}LRRC_LPHY_MEAS_IN_IDLE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellId;
    VOS_INT16                           sRsrp;                                  /* RSRP测量值 */
    VOS_INT16                           sRsrq;                                  /* RSRQ测量值 */
    VOS_INT16                           sRssi;                                  /* RSSI测量值 */
}LRRC_LPHY_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_IDLE_SERV_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE态服务小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                             /* 服务小区频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    LRRC_LPHY_CELL_MEAS_RESULT_STRU     stMeasRslt;
}LRRC_LPHY_IDLE_SERV_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SINGLE_FREQ_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单个频点小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    VOS_UINT16                          usTotalCellNum;
    VOS_UINT16                          usDetectedCellNum;

    VOS_UINT16                         usUeRxTxTimeDiffValidFlag;
    VOS_UINT16                         usUeRxTxTimeDiff;                        /* 0-4095 */
    VOS_UINT16                         usSfn;                                   /* 0-1023 测量RxTx时的SFN值*/
    VOS_UINT16                         usReserved;

    LRRC_LPHY_CELL_MEAS_RESULT_STRU     astCellMeasResult[LRRC_LPHY_REPORT_MAX_FREQ_CELL_NUM];/* SCELL放在第一个的位置 */
}LRRC_LPHY_SINGLE_FREQ_MEAS_RESULT_STRU;
typedef LRRC_LPHY_SINGLE_FREQ_MEAS_RESULT_STRU LRRC_LPHY_INTRA_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_INTER_FREQ_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 异频小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usInterFreqNum;
    VOS_UINT16                                    usReserved;
    LRRC_LPHY_SINGLE_FREQ_MEAS_RESULT_STRU        astInterFreqResultList[LRRC_LPHY_MAX_ADDITIONAL_CARRIER_NUM];
}LRRC_LPHY_INTER_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SECOND_FREQ_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Secondary freqs 小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usSecondFreqNum;
    VOS_UINT16                                    usReserved;
    LRRC_LPHY_SINGLE_FREQ_MEAS_RESULT_STRU        astSecondFreqResultList[LRRC_LPHY_MAX_SECONDARY_CARRIER_NUM];
}LRRC_LPHY_SECOND_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_IN_IDLE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IDLE测量结果上报数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                    enMsgId;                    /*_H2ASN_Skip*/
    VOS_UINT16                                      usOpId;
    LRRC_LPHY_IDLE_MEAS_REPORT_TYPE_ENUM_UNIT16     enReportType;
    union
    {
        LRRC_LPHY_IDLE_SERV_CELL_MEAS_RESULT_STRU   stServingCellResult;
        LRRC_LPHY_INTRA_FREQ_MEAS_RESULT_STRU       stIntraFreqResult;
        LRRC_LPHY_INTER_FREQ_MEAS_RESULT_STRU       stInterFreqResult;
    }u;

    VOS_UINT16                                      usNoRfValid;               /*DSDS特性增加 ，NORF指示*/
    VOS_UINT16                                      usRsved;
}LRRC_LPHY_MEAS_IN_IDLE_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_IN_CONNECTED_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CONNECTED测量数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_MEAS_COMMAND_ENUM_UINT16    enCommand;
    LRRC_LPHY_RAT_TYPE_ENUM_UINT16        enRatType;                            /* 指示当前主模类型 */
    LRRC_LPHY_WCDMA_STATE_ENUM_UINT16     enWrrcState;                          /* WCDMA->LTE测量时,指示当前WRRC的协议状态,CELL_PCH和URA_PCH状态LTE RTT需要按照IDLE态方式进行测量,其他则按照连接态方式 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT8                             enMeasGapFlg;                         /* 指示异频测量是否需要Gap */
    LRRC_LPHY_MEAS_TYPE_ENUM_UINT8        enMeasType;                           /* 测量类型：0：连续测量；1：单次测量 */
#else
    VOS_UINT8                             ucReserved;
    LRRC_LPHY_MEAS_TYPE_ENUM_UINT8        enMeasType;                           /* 测量类型：0：连续测量；1：单次测量 */
#endif
    LRRC_LPHY_CONN_MEAS_TYPE_ENUM_UINT16  enMeasureType;
    union
    {
        LRRC_LPHY_INTRA_FREQ_CELL_INFO_STRU    stIntraFreqCell;
        LRRC_LPHY_INTER_FREQ_CELL_INFO_STRU    stInterFreqCell;                 /* LTE内异频测量或GU->LTE测量时,通过该列表配置测量信息 */
        LRRC_LPHY_IRAT_CONN_FREQ_INFO_STRU     stIratFreqInfo;                  /* LTE->GU测量时，异系统测量信息 */
        LRRC_LPHY_SECOND_FREQ_INFO_STRU        stSecondFreqInfo;
    }u;
}LRRC_LPHY_MEAS_IN_CONNECTED_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_IN_CONNECTED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CONNECTED下测量回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
}LRRC_LPHY_MEAS_IN_CONNECTED_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_IN_CONNECTED_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CONNECTED测量结果上报数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                      enMsgId;                  /*_H2ASN_Skip*/
    VOS_UINT16                                        usOpId;
    LRRC_LPHY_CONN_MEAS_REPORT_TYPE_ENUM_UNIT16       enReportType;
    union
    {
        LRRC_LPHY_INTRA_FREQ_MEAS_RESULT_STRU         stIntraFreqResult;
        LRRC_LPHY_INTER_FREQ_MEAS_RESULT_STRU         stInterFreqResult;
        LRRC_LPHY_SECOND_FREQ_MEAS_RESULT_STRU        stSecondFreqResult;
    }u;
}LRRC_LPHY_MEAS_IN_CONNECTED_IND_STRU;
/*****************************************************************************
 结构名    : LRRC_LPHY_TX_PWR_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TXPOWER数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT16     sPuschPwr;
    VOS_INT16     sPucchPwr;
    VOS_INT16     sSrsPwr;
    VOS_INT16     sPrachPwr;
}LRRC_LPHY_TX_PWR_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MCS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MCS数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16     usUlMcs;
    VOS_UINT16     usDlMcs[2];
    VOS_UINT8      aucRes[2];
}LRRC_LPHY_MCS_INFO_STRU;

/*NMR begin*/
/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CQIs数据结构
*****************************************************************************/
typedef struct
{   VOS_UINT16                                      ausCQI[2];
    VOS_UINT16                                      usRI;
    VOS_UINT8                                       aucRes[2];
} LRRC_LPHY_CQI_INFO_STRU;
/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 参数上报数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                     /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                    enMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                                      usOpId;
    VOS_UINT16                                      usTa;
    VOS_INT32                                       lSINR;
    LRRC_LPHY_CQI_INFO_STRU                         stCQI;
    LRRC_LPHY_TX_PWR_INFO_STRU                      stTxPwrInfo;
    LRRC_LPHY_MCS_INFO_STRU                         stMcsInfo;
}LRRC_LPHY_MEAS_INFO_IND_STRU;
/*NMR end*/

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_GAP_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MEAS GAP配置信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enMeasGapEnabled;                     /* 0:表示deactivate,1:表示activate，同时后面参数有效 */
    LRRC_LPHY_MEAS_GAP_TYPE_ENUM_UINT16   enMeasGapType;                        /* 0:表示gp1,1:表示gp2*/
    VOS_UINT16                            usMeasGapOffset;                      /* 相对应enMeasGapType类型的gapOffset */
    VOS_UINT16                            usMeasPeriod;                         /* 测量周期 */
    VOS_UINT16                            usMinIntraCellNum;                    /* 同频小区数,按照36.133计算 */
}LRRC_LPHY_MEAS_GAP_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MEAS_GAP_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MEAS GAP配置回复信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
}LRRC_LPHY_MEAS_GAP_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RELALL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 指示删除所有物理层信道信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    VOS_UINT16                            usReserved;
}LRRC_LPHY_RELALL_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RELALL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 删除物理层信道回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
}LRRC_LPHY_RELALL_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_CONFIG_INDEX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usCqiPmiConfigIdx2;           /* cqi-pmi-ConfigIndex2-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enRiConfigIdx2ValidFlg;       /* ri-ConfigIndex2-r10是否有效标示 */
    VOS_UINT16                                    usRiConfigIdx2;               /* ri-ConfigIndex2-r10 */
    VOS_UINT16                                    usReserved;
}LRRC_LPHY_CSI_CONFIG_INDEX_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_SUBBAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_SUBBAND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usCqiSubBand_k;               /* k */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enPeriodicFactorValidFlg;
    LRRC_LPHY_PERIODIC_FACTOR_ENUM_UINT16         enPeriodicFactor;             /* periodicityFactor-r10 */
    VOS_UINT16                                    usReserved;
}LRRC_LPHY_CQI_SUBBAND_STRU;

#if (FEATURE_ON == FEATURE_LTE_R11)
/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usCqiRptPeriodProcExtId;      /* cqi-ReportPeriodicProcExtId-r11 INTEGER (1..maxCQI-ProcExt-r11) */
    VOS_UINT16                                    usCqiPmiConfigIndex;          /* cqi-pmi-ConfigIndex-r11			INTEGER (0..1023) */
    LRRC_LPHY_CQI_FORMATE_IND_TYPE_ENUM_UINT16    enCqiFormatIndPeriodic;       /* cqi-FormatIndicatorPeriodic-r11 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiWideBandCsiRptModeValidFlg;        /* enCqiWideBandCsiRptMode是否有效 */
    LRRC_LPHY_CQI_REPORT_MODE_ENUM_UINT16         enCqiWideBandCsiRptMode;                /* widebandCQI-r11 */
    VOS_UINT16                                    usRiConfigIndex;              /* ri-ConfigIndex-r11 --Need OR	INTEGER (0..1023) 0xFFFF无效值 */
    VOS_UINT16                                    usReserved;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCsiConfigIdxValidFlg;       /* csi-ConfigIndex-r11 是否有效 */
    LRRC_LPHY_CSI_CONFIG_INDEX_STRU               stCsiConfigIdx;               /* csi-ConfigIndex-r11 --Need ON */
    LRRC_LPHY_CQI_SUBBAND_STRU                    stCqiSubBand;                 /* subbandCQI-r11 */
}LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCqiProcExtNum;                   /* 小区个数 (1..maxCQI-ProcExt-r11) */
    VOS_UINT16                                      usResered;
    LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_STRU     astCqiProcExtInfo[LRRC_LPHY_MAX_CQI_PROC_EXT_NUM]; /* CQI-ReportPeriodicProcExt-r11 */
}LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_IM_CONFIG_STRU
 协议表格  : CSI-IM-Config-r11
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CSI_IM_CONFIG_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCsiIMCfgId;               /* csi-IM-ConfigId-r11 */
    VOS_UINT16                                      usResourcecfg;              /* resourceConfig-r11 (0..31) */
    VOS_UINT16                                      usSfCfg;                    /* subframeConfig-r11 (0..154) */
    VOS_UINT16                                      usResered;
}LRRC_LPHY_CSI_IM_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_IM_CONFIG_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CSI_IM_CONFIG_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCsiIMCfgNum;              /* 小区个数 (1..maxCSI-IM-r11) */
    VOS_UINT16                                      usResered;
    LRRC_LPHY_CSI_IM_CONFIG_STRU                    astCsiIMCfg[LRRC_LPHY_MAX_CSI_IM_NUM]; /* CSI-IM-Config-r11 */
}LRRC_LPHY_CSI_IM_CONFIG_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_P_C_AND_CBSR_STRU
 协议表格  : p-C-AndCBSR-r11
 ASN.1描述 :
 结构说明  : LRRC_LPHY_P_C_AND_CBSR_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                                       sPC;                        /* p-C-r11 INTEGER (-8..15) */
    LRRC_LPHY_CODE_BOOK_TYPE_ENUM_UINT16            enCodeBookType;             /* 指示当前使用的码书的子集受限类型 */
    /* 36.213 Table 7.2-1b TM10 n2/n4/n8最大需要109BITS */
    VOS_UINT32                                      aulCodebookSubsetRestriction[4]; /* 码书的子集受限,Little-Endian字节序 */
}LRRC_LPHY_P_C_AND_CBSR_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_P_C_AND_CBSR_LIST_STRU
 协议表格  : p-C-AndCBSRList-r11
 ASN.1描述 :
 结构说明  : LRRC_LPHY_P_C_AND_CBSR_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPCAndCBSRNum;             /* 个数 (1..2) */
    VOS_UINT16                                      usResered;
    LRRC_LPHY_P_C_AND_CBSR_STRU                     astPCAndCBSR[2];            /* P-C-AndCBSR-r11 */
}LRRC_LPHY_P_C_AND_CBSR_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_REPORT_BOTH_PROC_STRU
 协议表格  : CQI-ReportBothProc-r11
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_REPORT_BOTH_PROC_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enRiRefCSIProcIdEnabled;    /* usRiRefCSIProcId 是否使能 */
    VOS_UINT16                                      usRiRefCSIProcId;           /* ri-Ref-CSI-ProcessId-r11 --Need OR */
    VOS_UINT16                                      usResered;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enPmiRIReportEnabled;       /* pmi-RI-Report-r11 --Need OR */
}LRRC_LPHY_CQI_REPORT_BOTH_PROC_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_REPORT_APERIODIC_PROC_R11_STRU
 协议表格  : CQI-ReportAperiodicProc-r11
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_REPORT_APERIODIC_PROC_R11_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CQI_MODEA_PERIODIC_ENUM_UINT16        enCqiRptModeAperiodic;      /* cqi-ReportModeAperiodic-r11 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enTrigger01Enabled;         /* trigger01-r11 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enTrigger10Enabled;         /* trigger10-r11 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16               enTrigger11Enabled;         /* trigger11-r11 */
}LRRC_LPHY_CQI_REPORT_APERIODIC_PROC_R11_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_PROCESS_STRU
 协议表格  : CSI-Process-r11
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CSI_PROCESS_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCsiProcId;                /* csi-ProcessId-r11 */
    VOS_UINT16                                      usCsiRSCfgNZPId;            /* csi-RS-ConfigNZPId-r11 */
    VOS_UINT16                                      usCsiIMCfgId;               /* csi-IM-ConfigId-r11 */

    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enCqiRptPeriodProcIdValidFlg;/* usCqiRptPeriodProcId 是否有效 */
    VOS_UINT16                                      usCqiRptPeriodProcId;       /* cqi-ReportPeriodicProcId-r11 --Need OR */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enCqiRptBothProcValidFlg;   /* stCqiRptBothProc 是否有效 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enCqiRptAperiodProcR11ValidFlg;/* stCqiRptAperiodProcR11 是否有效 */
    VOS_UINT16                                      usResered;

    LRRC_LPHY_CQI_REPORT_BOTH_PROC_STRU             stCqiRptBothProc;           /* cqi-ReportBothProc-r11 --Need OR */
    LRRC_LPHY_CQI_REPORT_APERIODIC_PROC_R11_STRU    stCqiRptAperiodProcR11;     /* cqi-ReportAperiodicProc-r11 --Need OR */
    LRRC_LPHY_P_C_AND_CBSR_LIST_STRU                stPCAndCBSRList;            /* p-C-AndCBSRList-r11 */
}LRRC_LPHY_CSI_PROCESS_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CSI_PROCESS_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CSI_PROCESS_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCsiProcNum;               /* 小区个数 (1..maxCSI-Proc-r11) */
    VOS_UINT16                                      usResered;
    LRRC_LPHY_CSI_PROCESS_STRU                      astCsiProc[LRRC_LPHY_MAX_CSI_PROC_NUM]; /* CSI-Process-r11 */
}LRRC_LPHY_CSI_PROCESS_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_REPORT_BOTH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_REPORT_BOTH_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enCsiIMCfgListFlg;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enCsiProcListFlg;

    LRRC_LPHY_CSI_IM_CONFIG_LIST_STRU     stCsiIMCfgList;                       /* csi-IM-ConfigToAddModList-r11 */
    LRRC_LPHY_CSI_PROCESS_LIST_STRU       stCsiProcList;                        /* csi-ProcessToAddModList-r11 */
}LRRC_LPHY_CQI_REPORT_BOTH_STRU;
#endif


/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_REPORT_PERIODIC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_REPORT_PERIODIC_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usCqiPucchResIdx;             /* cqi-PUCCH-ResourceIndex */
    VOS_UINT16                                    usCqiPmiConfigIdx;            /* cqi-pmi-ConfigIndex */
    VOS_UINT16                                    usRiConfigIdx;                /* ri-ConfigIndex */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enAnAndCqiValidFlg;           /* simultaneousAckNackAndCQI */
    LRRC_LPHY_CQI_FORMATE_IND_TYPE_ENUM_UINT16    enCqiFormatIndPeriodic;       /* cqi-FormatIndicatorPeriodic */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiPucchResIdxP1ValidFlg;   /* usCqiPucchResIdxP1_r10是否有效 */
    VOS_UINT16                                    usCqiPucchResIdxP1;           /* cqi-PUCCH-ResourceIndexP1-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCsiConfigIdxValidFlg;       /* csi-ConfigIndex-r10 */
    LRRC_LPHY_CSI_CONFIG_INDEX_STRU               stCsiConfigIdx;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiWideBandCsiRptModeValidFlg;        /* enCqiWideBandCsiRptMode是否有效 */
    LRRC_LPHY_CQI_REPORT_MODE_ENUM_UINT16         enCqiWideBandCsiRptMode;                /* widebandCQI-r10:csi-ReportMode-r10 */
    LRRC_LPHY_CQI_SUBBAND_STRU                    stCqiSubBand;                 /* subbandCQI-r10 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16                   enSimultAckNackAndCqiFormat3Enabled; /* simultaneousAckNackAndCQI-Format3-r11 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16               enCqiRptPeriodProcExtListFlg; /* stCqiRptPeriodProcExtList有效标识 */
    LRRC_LPHY_CQI_REPORT_PERIODIC_PROC_EXT_LIST_STRU    stCqiRptPeriodProcExtList;
#endif
}LRRC_LPHY_CQI_REPORT_PERIODIC_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_REPORT_APERIODIC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_REPORT_APERIODIC_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CQI_MODEA_PERIODIC_ENUM_UINT16      enCqiRptModeAType;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCsiAperiodicTrigValidFlg; /* aperiodicCSI-Trigger-r10是否有效 */
    VOS_UINT16                                    ausTrigger[2];
}LRRC_LPHY_CQI_REPORT_APERIODIC_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_RPT_CONFIG_PCELL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_RPT_CONFIG_PCELL_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CQI_TYPE_ENUM_UINT16                enCqiType;                    /* CQI类型 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiRptModeAperiodicValidFlg;/* stCqiRptAperiodic是否有效 */
    VOS_INT16                                     sNomPdschRsEpreOffset;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enCqiRptPeriodicEnabled;      /* 0:表示stCqiRptPeriodicInfo无效 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiMaskValidFlg;            /* 0:表示该参数无效，1:表示该参数有效 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enPmiRiReportValidFlg;        /* 0:表示该参数无效，1:表示该参数有效 */
    LRRC_LPHY_CQI_REPORT_PERIODIC_INFO_STRU       stCqiRptPeriodicInfo;
    LRRC_LPHY_CQI_REPORT_APERIODIC_STRU           stCqiRptAperiodic;            /* CQI-ReportAperiodic-r10 */
    VOS_UINT16                                    usReserved;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCsiSFPatCfgValidFlg;        /* astCsiMeasSFSet是否有效 */
    LRRC_LPHY_MEAS_SUBFRAME_PATTERN_STRU          astCsiMeasSFSet[2];
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_CQI_REPORT_BOTH_STRU                stCqiRptBoth;                 /* CQI-ReportBoth-r11 */
#endif
}LRRC_LPHY_CQI_RPT_CONFIG_PCELL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_RPT_CONFIG_SCELL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_RPT_CONFIG_SCELL_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CQI_TYPE_ENUM_UINT16                enCqiType;                    /* CQI类型 */
    VOS_UINT16                                    usSCellIdx;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiRptModeAperiodicValidFlg;/* enCqiRptModeAType是否有效 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiRptPeriodicValidFlg;     /* stCqiRptPeriodicInfoSCell是否有效 */
    LRRC_LPHY_CQI_REPORT_APERIODIC_STRU           stCqiRptAperiodic;            /* CQI-ReportAperiodic-r10 */
    LRRC_LPHY_CQI_REPORT_PERIODIC_INFO_STRU       stCqiRptPeriodicInfo;         /* cqi-ReportPeriodicSCell-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enCqiMaskValidFlg;            /* 0:表示该参数无效，1:表示该参数有效 */
    VOS_INT16                                     sNomPdschRsEpreOffset;        /* nomPDSCH-RS-EPRE-Offset-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enPmiRiReportValidFlg;        /* 0:表示该参数无效，1:表示该参数有效 */
    VOS_UINT16                                    usReserved;
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_CQI_REPORT_BOTH_STRU                stCqiRptBoth;                 /* CQI-ReportBoth-r11 */
#endif
}LRRC_LPHY_CQI_RPT_CONFIG_SCELL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CQI配置请求数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT16                          usReserved;                             /* 保留字段 */
    VOS_UINT16                          usCqiCfgNum;                            /* 指示本次建立的CQI配置数量 */
    VOS_UINT16                          usParaSize;                             /* 指示本次建立的CQI配置参数的总长度 */
    VOS_UINT8                           aucCqiCfgPara[4];                       /* CQI配置参数 */
}LRRC_LPHY_CQI_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CQI_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CQI_CONFIG_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
}LRRC_LPHY_CQI_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SRS_COMM_INFO_STRU
 协议表格  : RadioResourceConfigCommonSIB->SoundingRsUl-ConfigCommon
             RadioResourceConfigCommon->SoundingRsUl-ConfigCommon
 ASN.1描述 :
 结构说明  : 配置公共SRS数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SRS_BANDWIDTH_TYPE_ENUM_UINT16        enSrsBandWidth;               /* srsBandwidthConfiguration */
    LRRC_LPHY_SRS_SUBFRAME_TYPE_ENUM_UINT16         enSrsSubFrame;                /* srsSubframeConfiguration */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enAnSrsTransValidFlg;         /* ackNackSrsSimultaneousTransmission */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enSrsMaxUpPtsValidFlg;        /* srsMaxUpPts */
}LRRC_LPHY_SRS_COMM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SRS_DEDICATED_INFO_STRU
 协议表格  : PhysicalConfigDedicated->SoundingRsUl-ConfigDedicated
 ASN.1描述 :
 结构说明  : 配置专有SRS数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SRS_BANDWIDTH_TYPE_ENUM_UINT16        enSrsBandWidth;               /* srsBandwidth */
    LRRC_LPHY_SRS_HOPPING_BANDWIDTH_ENUM_UINT16     enSrsHoppingBandWidth;        /* srsHoppingBandwidth */
    VOS_UINT16                                      usFreqDomainPos;              /* frequencyDomainPosition */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enDurationValidFlg;           /* duration */
    VOS_UINT16                                      usSrsConfigIdx;               /* srs-ConfigurationIndex */
    VOS_UINT16                                      usTransComb;                  /* transmissionComb */
    LRRC_LPHY_CYCLIC_SHIFT_ENUM_UINT16              enCyclicShift;                /* cyclicShift */
    VOS_UINT16                                      usReserved;
}LRRC_LPHY_SRS_DEDICATED_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SRS_CONFIG_AP_STRU
 协议表格  : SRS-ConfigAp-r10
 ASN.1描述 :
 结构说明  : 配置专有SRS数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SRS_ANTANNA_PORT_ENUM_UINT16          enSrsAntennaPortAp;         /* srs-AntennaPortAp-r10 */
    LRRC_LPHY_SRS_BANDWIDTH_TYPE_ENUM_UINT16        enSrsBandWidthAp;           /* srs-BandwidthAp-r10 */
    VOS_UINT16                                      usFreqDomainPositionAp;     /* freqDomainPositionAp-r10 */
    VOS_UINT16                                      usTransCombAp;              /* transmissionCombAp-r10 */
    LRRC_LPHY_CYCLIC_SHIFT_ENUM_UINT16              enCyclicShiftAp;            /* cyclicShiftAp-r10 */
    VOS_UINT16                                      usReserved;
}LRRC_LPHY_SRS_CONFIG_AP_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SRS_DEDICATED_INFO_STRU
 协议表格  : PhysicalConfigDedicated->SoundingRS-UL-ConfigDedicatedAperiodic-r10
 ASN.1描述 :
 结构说明  : 配置专有非周期SRS数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usSrsCfgIndexAp;         /* srs-ConfigIndexAp-r10 */
    VOS_UINT16                                      usSrsCfgApDciFormat4Cnt; /* astSrsConfigApDciFormat4个数 */
    LRRC_LPHY_SRS_CONFIG_AP_STRU                    astSrsCfgApDciFormat4[LRRC_LPHY_MAX_SRS_CFG_AP_DCI_FORMAT4_NUM];
    VOS_UINT16                                      usReserved;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enSrsCfgApDciFormat0And1ValidFlg; /* stSrsConfigApDciFormat0和stSrsConfigApDciFormat1a2b2c是否有效 */
    LRRC_LPHY_SRS_CONFIG_AP_STRU                    stSrsCfgApDciFormat0;
    LRRC_LPHY_SRS_CONFIG_AP_STRU                    stSrsCfgApDciFormat1a2b2c;
}LRRC_LPHY_SRS_DEDI_APERIOD_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_SRS_CONFIG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置SRS数据结构.PCELL和SCELL结构相同，通过usSCellIdx区分。
*****************************************************************************/
typedef struct
{
    VOS_UINT16                            usSCellIdx;                           /* 0表示PCELL */
    VOS_UINT16                            usReserved1;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsCommInfoValidFlg;                /* 公共SRS参数是否有效 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsDedicatedInfoValidFlg;           /* 专有SRS参数是否有效 */
    LRRC_LPHY_SRS_COMM_INFO_STRU          stSrsCommInfo;
    LRRC_LPHY_SRS_DEDICATED_INFO_STRU     stSrsDedicatedInfo;
    VOS_UINT16                            usReserved2;                          /* 保留字段 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsAntennaPortValidFlg;             /* R10专有SRS参数enSrsAntennaPort是否有效 */
    LRRC_LPHY_SRS_ANTANNA_PORT_ENUM_UINT16    enSrsAntennaPort;                 /* SRS天线口数量 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16 enSrsDedicatedAperiodicInfoValidFlg;  /* R10 非周期专有SRS参数是否有效 */
    LRRC_LPHY_SRS_DEDI_APERIOD_INFO_STRU  stSrsDedicatedAperiodicInfo;          /* R10 非周期专有SRS参数 */
}LRRC_LPHY_SRS_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SRS_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SRS配置请求数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT16                          usReserved;                             /* 保留字段 */
    VOS_UINT16                          usSrsCfgNum;                            /* 指示本次建立的SRS配置数量 */
    VOS_UINT16                          usParaSize;                             /* 指示本次建立的SRS配置参数的总长度 */
    VOS_UINT8                           aucSrsCfgPara[4];                       /* SRS配置参数 */
}LRRC_LPHY_SRS_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_SRS_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 配置SRS回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
}LRRC_LPHY_SRS_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_HO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 切换请求数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usFreqInfo;
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteModeType;                          /* 指示频点所属的制式类型, FDD或TDD */
    VOS_UINT16                          usCellId;
    LRRC_LPHY_HO_TYPE_ENUM_UINT16       enHoType;
    VOS_UINT16                          usPhyChannelNum;
    VOS_UINT16                          usParaSize;
    VOS_UINT8                           aucPhyChannelPara[4];
}LRRC_LPHY_HO_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_HO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 切换回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16        enResult;
    VOS_UINT16                          usNoRfValid;                            /*DSDS特性增加 ，NORF指示*/
    VOS_UINT16                          usRsved;
}LRRC_LPHY_HO_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_DRX_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DRX参数配置数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_DURATION_TIMER_ENUM_UINT16  enDurationTimer;                        /* onDurationTimer */
    LRRC_LPHY_INACTIVE_TIMER_ENUM_UINT16  enInactiveTimer;                        /* drx-InactivityTimer */
    LRRC_LPHY_RETRANS_TIMER_ENUM_UINT16   enReTransTimer;                         /* drx-RetransmissionTimer */
    LRRC_LPHY_LONG_DRX_OFFSET_ENUM_UINT16 enLongDrxOffsetType;                    /* longDRX-CycleStartOffset类型 */
    VOS_UINT16                            usLongDrxStartOffse;                    /* longDRX-CycleStartOffset */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enShortDrxEnabled;                      /* 0:表示shortDRX无效 */
    LRRC_LPHY_SHORT_DRX_CYCLE_ENUM_UINT16 enShortDrxCycle;                        /* shortDRX->shortDRX-Cycle */
    VOS_UINT16                            usShortDrxCycleTimer;                   /* shortDRX->drxShortCycleTimer,0表示该值无效 */
}LRRC_LPHY_CONNECTED_DRX_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CONNECTED态下DRX参数配置数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16     enConnDrxEnabled;                     /* 指示CONNECTED态下DRX是否有效 */
    LRRC_LPHY_CONNECTED_DRX_INFO_STRU     stConnDrxInfo;
}LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DRX参数配置回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
}LRRC_LPHY_DRX_CONFIG_IN_CONNECTED_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SI_CONFIG_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SI消息的配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                        usSiOrder;
    LRRC_LPHY_SI_PERIOD_ENUM_UINT16   enSiPeriod;
} LRRC_LPHY_SI_CONFIG_ITEM_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SI_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_LPHY_MSG_ID_ENUM_UINT32      enMsgId;
    VOS_UINT16                        usOpId;
    LRRC_LPHY_SI_WINDOW_ENUM_UINT16   enSiWindow;
    VOS_UINT16                        usSiNum;
    VOS_UINT8                         aucReserved[2];
    LRRC_LPHY_SI_CONFIG_ITEM_STRU     astSiConfigItem[LRRC_LPHY_MAX_SI_CONFIG_NUM];
} LRRC_LPHY_SI_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SI_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_LPHY_MSG_ID_ENUM_UINT32      enMsgId;
    VOS_UINT16                        usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16      enResult;
} LRRC_LPHY_SI_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CONFIG_DRX_GATECLOCK_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CONFIG_DRX_GATECLOCK_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32      enMsgId;                                  /*_H2ASN_Skip*/
    VOS_UINT16                        usOpId;
    VOS_UINT16                        usRsvd;

    LRRC_LPHY_DRX_INDICATOR_ENUM_UINT16                 enDrxIndicator;
    LRRC_LPHY_GATECLOCK_INDICATOR_ENUM_UINT16           enGateClockIndicator;
} LRRC_LPHY_CONFIG_DRX_GATECLOCK_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_TCXO_QUERY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_TCXO_QUERY_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32      enMsgId;                                  /*_H2ASN_Skip*/
    VOS_UINT16                        usOpId;
    VOS_UINT16                        usRsvd;
}LRRC_LPHY_TCXO_QUERY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_TCXO_QUERY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_TCXO_QUERY_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32    enMsgId;                                    /*_H2ASN_Skip*/
    VOS_UINT16                      usOpId;
    VOS_UINT16                      usFlg;                                      /* 0：有效；其余无效，无效时usDynamicTcxo值无意义 */
    VOS_UINT16                      usDynamicTcxo;
    VOS_UINT16                      usRsvd;
}LRRC_LPHY_TCXO_QUERY_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SET_WORK_MODE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_SET_WORK_MODE_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32              enMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    LRRC_LPHY_WORK_MODE_TYPE_ENUM_UINT16      enWorkModeType;                   /* 指示LTE工作模式，0:处于工作态，1:处于测量态 */
    LRRC_LPHY_SET_WORK_MODE_REASON_ENUM_UINT16  enSetWorkModeReason;            /*切模原因*/
    LRRC_LPHY_DSDS_RFSHARED_ENUM_UINT16       enDsdsRfShardFlg;
}LRRC_LPHY_SET_WORK_MODE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SET_WORK_MODE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_SET_WORK_MODE_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32              enMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16              enWorkModeCfgRslt;
}LRRC_LPHY_SET_WORK_MODE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BSIC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BSIC_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                usArfcn;
    LRRC_LPHY_GERAN_BAND_IND_ENUM_UINT16      enBandInd;
}LRRC_LPHY_BSIC_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BSIC_VERIFY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BSIC_VERIFY_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32              enMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    VOS_UINT16                                usBsicNum;
    LRRC_LPHY_BSIC_INFO_STRU                  astBsicList[LRRC_LPHY_MAX_BSIC_NUM];
}LRRC_LPHY_BSIC_VERIFY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BSIC_VERIFY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BSIC_VERIFY_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32              enMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16              enBsicCfgRslt;
}LRRC_LPHY_BSIC_VERIFY_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ERROR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ERROR_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32              enMsgId;                          /*_H2ASN_Skip*/
    LRRC_LPHY_ERR_TYPE_ENUM_UINT16            enErrType;
    VOS_UINT16                                usReserved;
}LRRC_LPHY_ERROR_IND_STRU;

/* LCS Begin */
/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_INTER_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_INTER_FREQ_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                usFreqInfo;                       /* 频率 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16            enBandInd;                        /* 频带指示 */
    VOS_UINT16                                usMeasPrsOffset;                  /* 0-39 */
    VOS_UINT8                                 aucReserved[2];
}LRRC_LPHY_OTDOA_INTER_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_LCS_GAP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_LCS_GAP_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32              enMsgId;                          /*_H2ASN_Skip*/
    LRRC_LPHY_OTDOA_ENABLE_SIGNAL_ENUM_UINT16 enInterRSTDMeasInd;
    VOS_UINT16                                usRSTDFreqNum;
    LRRC_LPHY_OTDOA_INTER_FREQ_INFO_STRU      astRSTDInterFreqInfoList[LRRC_LPHY_OTDOA_MAX_RSTD_FREQ_NUM];
}LRRC_LPHY_LCS_GAP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_PRS_MUTING_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_PRS_MUTING_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usValidBitNum;
    VOS_UINT16                                              usMutingBitInfo;
}LRRC_LPHY_OTDOA_PRS_MUTING_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_PRS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_PRS_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_LTE_BAND_WIDTH_ENUM_UINT16                    enPRSBandwidth;
    VOS_UINT16                                              usPRSCfgIndex;
    LRRC_LPHY_OTDOA_DL_SUBFRAME_NUM_ENUM_UINT16             enDLSubframeNum;
    VOS_UINT8                                               aucReservered[2];
    LRRC_LPHY_OTDOA_PRS_MUTING_INFO_STRU                    stPRSMutingInfo;
}LRRC_LPHY_OTDOA_PRS_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_PRS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_PRS_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPhysCellId;
    VOS_UINT16                                              usFreqInfoRef;      /* 频率 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                          enBandInd;          /* 频带指示 */
    LRRC_LPHY_OTDOA_ANT_PORT_CFG_ENUM_UINT16                enAntPortCfg;
    LRRC_LPHY_LTE_CP_TYPE_ENUM_UINT16                       enCpLength;
    LRRC_LPHY_OTDOA_PRS_CRS_TYPE_ENUM_UINT16                enPRSCRSIndication;

    LRRC_LPHY_OTDOA_PRS_INFO_STRU                           stPRSInfo;
}LRRC_LPHY_OTDOA_REF_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPhysCellId;
    VOS_UINT16                                              usFreqInfoNeighbour;/* 频率 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                          enBandInd;          /* 频带指示 */
    LRRC_LPHY_OTDOA_ANT_PORT_CFG_ENUM_UINT16                enAntPortCfg;
    LRRC_LPHY_LTE_CP_TYPE_ENUM_UINT16                       enCpLength;
    LRRC_LPHY_OTDOA_PRS_CRS_TYPE_ENUM_UINT16                enPRSCRSIndication;
    LRRC_LPHY_OTDOA_PRS_INFO_STRU                           stPRSInfo;
    VOS_UINT8                                               ucSlotNumberOffsetFlg; /* 指示usSlotNumberOffset是否存在，0:不存在，1:存在 */
    VOS_UINT8                                               ucPRSSubframeOffsetFlg;/* 指示usPRSSubframeOffset是否存在，0:不存在，1:存在 */
    VOS_UINT8                                               aucReservered[2];
    VOS_UINT16                                              usSlotNumberOffset;
    VOS_UINT16                                              usPRSSubframeOffset;
    VOS_UINT16                                              usExpectedRSTD;
    VOS_UINT16                                              usExpectedRSTDUncertainty;
}LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usNeighbourCellNum;
    VOS_UINT8                                               aucReservered[2];
    LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU           astNeighbourCellInfoList[LRRC_LPHY_OTDOA_MAX_NEIGHBOUR_CELL_NUM_PER_LAYER];
}LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usFreqLayersNum;
    VOS_UINT8                                               aucReservered[2];
    LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU                astNeighbourCellLayersInfoList[LRRC_LPHY_OTDOA_MAX_FREQ_LAYER_NUM - 1];
}LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_LAYERS_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRefCellInfoFlg;
    VOS_UINT8                                               ucNeighbourCellLayersInfoFlg;
    VOS_UINT8                                               aucReserved[2];

    LRRC_LPHY_OTDOA_REF_CELL_INFO_STRU                      stRefCellInfo;
    LRRC_LPHY_OTDOA_NEIGHBOUR_CELL_LAYERS_INFO_STRU         stNeighbourCellLayersInfo;
}LRRC_LPHY_OTDOA_ASSISTANCE_DATA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_LCS_MBX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_LCS_MBX_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usActiveFlag;
    VOS_UINT16                                              usProtectWord;
    LRRC_LPHY_OTDOA_ASSISTANCE_DATA_STRU                    stOtdoaAssistanceData;
}LRRC_LPHY_LCS_MBX_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                            enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_LPHY_POSITION_OTDOA_MEAS_REQ_ENUM_UINT16           enRSTDMeasReqType;
    LRRC_LPHY_OTDOA_RPRT_INTERVAL_ENUM_UINT16               enOtdoaRprtInterval;/* 当enRSTDMeasReqType指示为OTDOA测量启动时有效 */
    VOS_UINT8                                               aucReserved[2];
}LRRC_LPHY_OTDOA_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : OTDOA回复数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16        enResult;
}LRRC_LPHY_OTDOA_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_MEAS_QUALITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_MEAS_QUALITY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usErrorResolution;
    VOS_UINT16                                              usErrorValue;
    VOS_UINT16                                              usErrorNumSamples;
    VOS_UINT8                                               aucReservered[2];
}LRRC_LPHY_OTDOA_MEAS_QUALITY_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_LIST_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPhyCellIdNeighbour;/* 0-503 */
    VOS_UINT16                                              usFreqInfoNeighbour;/* 频率 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                          enBandInd;          /* 频带指示 */
    VOS_UINT16                                              usRSTDResult;       /* 0-12711 */

    LRRC_LPHY_OTDOA_MEAS_QUALITY_STRU                       stRSTDQuality;
}LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usNeighbourCellNum;
    VOS_UINT8                                               aucReservered[2];
    LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_LIST_STRU                astNeighbourCellMeasList[LRRC_LPHY_OTDOA_MAX_NEIGHBOUR_CELL_NUM];
}LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_SIGNAL_MEAS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_SIGNAL_MEAS_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSFN;
    VOS_UINT16                                              usPhyCellIdRef;
    VOS_UINT16                                              usFreqInfoRef;
    LRRC_LPHY_BAND_IND_ENUM_UINT16                          enBandInd;          /* 频带指示 */

    LRRC_LPHY_OTDOA_MEAS_QUALITY_STRU                       stRefQuality;
    LRRC_LPHY_OTDOA_NEIGHBOUR_MEAS_STRU                     stNeighbourCellMeasurement;
}LRRC_LPHY_OTDOA_SIGNAL_MEAS_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_PROVIDE_LOCATION_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_PROVIDE_LOCATION_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16  enError;
    VOS_UINT8                                               aucReservered[2];
    LRRC_LPHY_OTDOA_SIGNAL_MEAS_INFO_STRU                   stSignalMeasInfo;
}LRRC_LPHY_OTDOA_PROVIDE_LOCATION_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_OTDOA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_OTDOA_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                            enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReservered[2];
    LRRC_LPHY_OTDOA_PROVIDE_LOCATION_INFO_STRU              stOtdoaMeasInfo;
}LRRC_LPHY_OTDOA_IND_STRU;


/* LCS End */
/*****************************************************************************
 结构名    : LRRC_LPHY_MSG_DATA
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MSG_DATA数据结构,以下为RRC专用，DSP不使用
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgID;        /*_H2ASN_MsgChoice_Export LRRC_LPHY_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                             aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LPHY_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}LRRC_LPHY_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : LrrcLphyInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : LrrcLphyInterface_MSG数据结构,以下为RRC专用，DSP不使用
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_LPHY_MSG_DATA                    stMsgData;
}LrrcLphyInterface_MSG;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBX_SLAVE_ADDR_QUEUE_ELEMENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBX_SLAVE_ADDR_QUEUE_ELEMENT_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32              *pulMsgAddr;                                        /*消息起始地址*/
    VOS_UINT32              ulMsgLen;                                           /*消息长度，单位双字*/
}LRRC_LPHY_MBX_SLAVE_ADDR_QUEUE_ELEMENT_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SLAVE_MAILBOX_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_SLAVE_MAILBOX_HEAD_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usProtectWord;                  /* 邮箱保护字 */
    VOS_UINT16                                  usFatalErrorInd;                /* 0:表示该字段无效, 1:关键信息丢失, 2:非关键信息丢失 */
    LRRC_LPHY_MBX_SLAVE_ADDR_QUEUE_ELEMENT_STRU stMsgAddrQue[LRRC_LPHY_MBX_SLAVE_ADDR_QUEUE_BUF_MAX];
} LRRC_LPHY_SLAVE_MAILBOX_HEAD_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SLAVE_DOWN_MAILBOX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_SLAVE_DOWN_MAILBOX_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SLAVE_MAILBOX_HEAD_STRU       stMailBoxHead;                      /* 邮箱头*/
    VOS_UINT32                              aulMessage[LRRC_LPHY_SLAVE_DOWN_MAILBOX_MSG_LEN];/* 消息帧,用于存储原语*/
} LRRC_LPHY_SLAVE_DOWN_MAILBOX_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_SLAVE_UP_MAILBOX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_SLAVE_UP_MAILBOX_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_SLAVE_MAILBOX_HEAD_STRU       stMailBoxHead;                      /* 邮箱头*/
    VOS_UINT32                              aulMessage[LRRC_LPHY_SLAVE_UP_MAILBOX_MSG_LEN];/* 消息帧,用于存储原语*/
} LRRC_LPHY_SLAVE_UP_MAILBOX_STRU;

/* MBMS Begin */
/*****************************************************************************
 结构名    : LRRC_LPHY_MCCH_CONFIG_R9_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MCCH_CONFIG_R9_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_MCCH_REPET_PERIOD_R9_ENUM_UINT8           enMcchRptPeriod;            /*rf32,rf64,rf128,rf256*/
    LRRC_LPHY_LRRC_LPHY_MCCH_OFFSET_ENUM_UINT8          enMcchOffset;               /*0..10*/
    LRRC_LPHY_MCCH_MODIFY_PERIOD_ENUM_UINT8             enMcchModPeriod;            /*rf512,rf1024*/
    VOS_UINT8                                           ucSfAlloc;                  /* rrc按照空口的格式进行配置 */
    LRRC_LPHY_SIG_MCS_R9_ENUM_UINT8                     enSignalMcs;                /*n2,n7,n13,n19*/
    VOS_UINT8                                           aucReservered[3];
}LRRC_LPHY_MCCH_CONFIG_R9_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_AREA_INFO_R9_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_AREA_INFO_R9_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                           ucAreaId;
    LRRC_LPHY_NON_MBSF_NREGION_LEN_ENUM_UINT8           enNonMbsfnRegionLen;
    VOS_UINT8                                           ucNotiIndicator;
    VOS_UINT8                                           ucReservered;
    LRRC_LPHY_MCCH_CONFIG_R9_STRU                       stMcchCfgPara;
}LRRC_LPHY_MBSFN_AREA_INFO_R9_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_AREA_INFO_LIST_R9_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_AREA_INFO_LIST_R9_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usValidAreaNum;
    VOS_UINT8                                           aucReservered[2];
    LRRC_LPHY_MBSFN_AREA_INFO_R9_STRU                   astMcchAreaInfo[LRRC_LPHY_MAX_NUM_OF_MBSFN_AREA];
}LRRC_LPHY_MBSFN_AREA_INFO_LIST_R9_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_MCCH_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_MCCH_CFG_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
    LRRC_LPHY_MBSFN_AREA_INFO_LIST_R9_STRU              stMbsfnAreaInfoList;
}LRRC_LPHY_MBSFN_MCCH_CFG_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_MCCH_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_MCCH_CFG_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBSFN_MCCH_CFG_CNF_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_MCCH_NOTIFICATION_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MCCH_NOTIFICATION_CFG_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_NOTIFICATION_REPET_COEFF_R9_ENUM_UINT8     enNotificationRptCoeff;
    LRRC_LPHY_NOTIFICATION_OFFSET_ENUM_UINT8             enNotificationOffset;
    LRRC_LPHY_NOTIFICATION_SF_INDEX_ENUM_UINT8           enNotificationSfINdex;
    VOS_UINT8                                            ucReservered;
}LRRC_LPHY_MCCH_NOTIFICATION_CFG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_NOTIFY_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_NOTIFY_CFG_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_CONIG_VALID_FLG_ENUM_UINT8                enMRNTIValidFlg;        /* 指示notify是否需要启动的标志 */
    LRRC_LPHY_MCCH_MODIFY_PERIOD_ENUM_UINT8             enMinNotificationRptPeriod; /* 由rrc找最小的mcchmodify周期 */
    LRRC_LPHY_MCCH_NOTIFICATION_CFG_STRU                stMcchNotificationCfg;
}LRRC_LPHY_MBSFN_NOTIFY_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_NOTIFY_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_NOTIFY_CFG_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBSFN_NOTIFY_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PMCH_CONFIG_R9_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_PMCH_CONFIG_R9_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CONIG_VALID_FLG_ENUM_UINT8                enPmchValidFlg;
    LRRC_LPHY_MCH_SCHDL_PERIOD_R9_ENUM_UINT8            enMchSchedPeriod;
    VOS_UINT16                                          usSfAllocEnd;           /*0..1535*/
    VOS_UINT16                                          usDataMcs;              /*0..28*/
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT8                                           ucPmchIndex;            /*0-LRRC_LPHY_MAX_NUM_OF_PMCH_PER_MBSFN-1*/
    VOS_UINT8                                           aucReservered[1];
#else
    VOS_UINT8                                           aucReservered[2];
#endif
}LRRC_LPHY_PMCH_CONFIG_R9_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PMCH_INFO_LIST_R9_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_PMCH_INFO_LIST_R9_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usPmchNum;
    VOS_UINT8                                           aucReservered[2];
    LRRC_LPHY_PMCH_CONFIG_R9_STRU                       astPmchInfo[LRRC_LPHY_MAX_NUM_OF_PMCH_PER_MBSFN];
}LRRC_LPHY_PMCH_INFO_LIST_R9_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_AREA_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_AREA_CFG_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                           ucAreaId;
    LRRC_LPHY_COMM_SF_ALLOC_PERIOD_R9_ENUM_UINT8        enComSfAllocPeriod;
    LRRC_LPHY_NON_MBSF_NREGION_LEN_ENUM_UINT8           enNonMbsfnRegionLen;
    LRRC_LPHY_SIG_MCS_R9_ENUM_UINT8                     enSignalMcs;
    LRRC_LPHY_MBSFN_SUBFRAME_CFG_LIST_STRU              stMbsfnCfgInfo;
    LRRC_LPHY_PMCH_INFO_LIST_R9_STRU                    stPmchInfoList;
}LRRC_LPHY_MBSFN_AREA_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_PMCH_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_PMCH_CFG_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT16                                          usAreaNum;              /* 如果个数为0则为释放请求 */
    LRRC_LPHY_MBSFN_AREA_CFG_INFO_STRU                  astMbsfnAreaInfo[LRRC_LPHY_MAX_NUM_OF_MBSFN_AREA];
}LRRC_LPHY_MBSFN_PMCH_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_PMCH_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_PMCH_CFG_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBSFN_PMCH_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_PMCH_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_PMCH_CFG_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT16                                          usCurrentSfn;
    VOS_UINT8                                           ucMcchChgInd;
    VOS_UINT8                                           ucReservered[3];
}LRRC_LPHY_MBSFN_NOTIFY_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_SUBFRAME_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_SUBFRAME_CFG_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usSCellIdx;                   /* 0表示PCELL */
    VOS_UINT16                                    usReserved;
    LRRC_LPHY_MBSFN_SUBFRAME_CFG_LIST_STRU        stMbsfnSFCfgList;             /* MBSFN子帧配置信息 */
}LRRC_LPHY_MBSFN_SUBFRAME_CFG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_SUBFRAME_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明：LRRC_LPHY_MBSFN_SUBFRAME_CFG_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];

    VOS_UINT16                                          usMbsfnSfCfgNum;        /* 指示本次MBSFN子帧配置数量 */
    VOS_UINT16                                          usParaSize;             /* 指示本次MBSFN子帧配置参数的总长度 */
    VOS_UINT8                                           aucMbsfnSfCfgPara[4];   /* MBSFN子帧配置参数 */

}LRRC_LPHY_MBSFN_SUBFRAME_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBSFN_SUBFRAME_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBSFN_SUBFRAME_CFG_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                              /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBSFN_SUBFRAME_CFG_CNF_STRU;

enum LRRC_LPHY_SWITCH_IND_TYPE_ENUM
{
    LRRC_LPHY_ANTEN_SWITCH_MSG_TYPE       = 0,
    LRRC_LPHY_SAR_REDUCTION_PRI_MSG_TYPE
};
typedef VOS_UINT16 LRRC_LPHY_SWITCH_IND_TYPE_ENUM_UNIT16;

/*****************************************************************************
 结构名    : LRRC_LPHY_SWITCH_IND_STRU
 协议表格  : rrc和Phy之间的接口 ,天线状态.ucSARSwitch: 0表示无线，1表示有线
 ASN.1描述 :
 结构说明  : LRRC_LPHY_SWITCH_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    LRRC_LPHY_SWITCH_IND_TYPE_ENUM_UNIT16               ulMsgType;
    VOS_UINT16                                          usSarReductionPri;      /*功率回退等级*/
    VOS_UINT8                                           ucAntenSwitch;          /*天线状态*/
    VOS_UINT8                                           ucRev[3];
}LRRC_LPHY_SWITCH_IND_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_START_REQ_STRU
 协议表格  :
 ASN.1描述 : 在背景搜索开始时下发该原语，dsp给rrc回复cnf后，rrc再进行bg搜索
 结构说明  : LRRC_LPHY_BG_SEARCH_START_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RAT_TYPE_ENUM_UINT16                      enStartBGSearchRat;     /* L主模时，此处填写BG搜哪个模式；L从模时，此处固定填写为L模 */
    LRRC_LPHY_BGSCFG_TYPE_ENUM_UINT16                   enBsgCfgType;            /*DSDS新增*/
    VOS_UINT16                                          usRsv;
}LRRC_LPHY_BG_SEARCH_START_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_START_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BG_SEARCH_START_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_BG_SEARCH_START_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_STOP_REQ_STRU
 协议表格  : 在背景搜索或者是背景搜索挂起时，dsp收到该请求后需要停止背景搜索
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BG_SEARCH_STOP_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_BG_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BG_SEARCH_STOP_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_BG_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_SUSPEND_REQ_STRU
 协议表格  : 在背景搜索时，rrc使用该原语挂起dsp bg搜索请求，
             rrc可以在BG频点搜索、频段搜索、扫频期间下发该原语，下发该请求后，DSP需要挂起
             频段搜索、扫频的上下文信息，用于dsp恢复背景搜索信息
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BG_SEARCH_SUSPEND_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_BG_SEARCH_SUSPEND_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_SUSPEND_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BG_SEARCH_SUSPEND_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_BG_SEARCH_SUSPEND_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_RESUME_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BG_SEARCH_RESUME_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_BG_SEARCH_RESUME_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_BG_SEARCH_RESUME_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_BG_SEARCH_RESUME_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_BG_SEARCH_RESUME_CNF_STRU;





/*****************************************************************************
 结构名    : LRRC_LPHY_ANR_START_REQ_STRU
 协议表格  :
 ASN.1描述 : DSP启动anr处理
 结构说明  : LRRC_LPHY_ANR_START_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RAT_TYPE_ENUM_UINT16                      enStartAnrRat;
    LRRC_LPHY_CGI_ACQUISITION_METHOD_ENUM_UINT16        enAcqMethod;            /* 指示CGI获取方式,0表示不进行CGI获取,1表示利用AUTONOMOUS GAP,2表示利用IDLE PERIODS */
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_ANR_START_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ANR_START_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ANR_START_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_ANR_START_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ANR_STOP_REQ_STRU
 协议表格  : 在anr时，dsp收到该请求后需要停止anr处理
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ANR_STOP_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_ANR_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ANR_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ANR_STOP_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_ANR_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RF_IIP2_DATA_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_RF_IIP2_DATA_PARA_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usIIP2IQWord;/*IQ校准码字*/
    VOS_INT16                                           sCorIMD2;/*IQ校准码字对应的IMD2校准结果*/
}LRRC_LPHY_RF_IIP2_DATA_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RF_IIP2_CAL_BAND_SPEC_VAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_RF_IIP2_CAL_BAND_SPEC_VAL_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_RF_IIP2_DATA_PARA_STRU                    stRfIIP2CalVar;
    VOS_UINT32                                          ulSuccFlag;
}LRRC_LPHY_RF_IIP2_CAL_BAND_SPEC_VAL_STRU;
/*****************************************************************************
 结构名    : LRRC_LPHY_RF_IIP2_CAL_BAND_SPEC_VAL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_RF_IIP2_CAL_BAND_SPEC_VAL_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usBand;
    VOS_UINT8                                           aucReserve[2];
    VOS_UINT32                                          aulDcocCal[LRRC_LPHY_RF_DCOC_RPT_DATA_SIZE];/*静态DCOC校准值，分别对应12个档位，每个数据分别包括主副通道的I、Q*/
    VOS_UINT32                                          aulTXIQCal[LRRC_LPHY_RF_TXIQ_RPT_DATA_SIZE];/*TXIQ校准，包括A、P、I、Q*/
    LRRC_LPHY_RF_IIP2_CAL_BAND_SPEC_VAL_STRU            stRfIIP2CalVar;
}LRRC_LPHY_RF_HI6360_INIT_CALDATA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ADJUST_PARA_QUERY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ADJUST_PARA_QUERY_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_QUERY_SELF_ADJUST_PARA_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_ADJUST_PARA_QUERY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_ADJUST_PARA_QUERY_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT16                                          usBandNum;
    LRRC_LPHY_RF_HI6360_INIT_CALDATA_STRU               stRfCalData[LRRC_LPHY_QUERY_SELF_ADJUST_PARA_MAX_BAND_NUM];
}LRRC_LPHY_QUERY_SELF_ADJUST_PARA_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CROSS_CARR_SCHEDUL_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CROSS_CARR_SCHEDUL_CFG_STRU数据结构
*****************************************************************************/
typedef struct
{
    /* 调度小区类型。当类型为own时，enCifPresenceFlg有效，
       当类型为other时，usSchedulCellIdx、usPdschStart有效 */
    LRRC_LPHY_SCHEDUL_CELL_TYPE_ENUM_UINT16       enSchedulCellType;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enCifPresence;                /* cif-Presence-r10 */
    VOS_UINT16                                    usSchedulCellIdx;             /* schedulingCellId-r10  */
    VOS_UINT16                                    usPdschStart;                 /* pdsch-Start-r10 */
}LRRC_LPHY_CROSS_CARR_SCHEDUL_CFG_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_DEDICATED_SCELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_PUSCH_DEDICATED_SCELL_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enGroupHopDisabled;           /* groupHoppingDisabled-r10是否有效 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enDmrsWithOCCActivated;       /* dmrs-WithOCC-Activated-r10是否有效 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                                    usReserved;
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enPuschDMRSEnabled;           /* stPuschDMRS是否有效 */
    LRRC_LPHY_PUSCH_DMRS_STRU                     stPuschDMRS;                  /* pusch-DMRS-r11 */
#endif
}LRRC_LPHY_PUSCH_DEDICATED_SCELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_POWER_CTRL_DEDICATED_INFO_SCELL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                     sPuschP0Ue;                   /* p0-UE-PUSCH-r10	 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enDeltaMcsEnabled;            /* deltaMCS-Enabled-r10 */
    LRRC_LPHY_PARA_ENABLE_ENUM_UINT16             enAccumlatEnabled;            /* accumulationEnabled-r10 */
    VOS_UINT16                                    usPsrsOffset;                 /* pSRS-Offset-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enPsrsOffsetApValidFlg;       /* usPsrsOffsetAp是否有效 */
    VOS_UINT16                                    usPsrsOffsetAp;               /* pSRS-OffsetAp-r10 */
    LRRC_LPHY_FILTER_COEFF_ENUM_UINT16            enFilterCoeff;                /* FilterCoefficient-r10 */
    LRRC_LPHY_PATHLOSS_REF_LINK_ENUM_UINT16       enPathLossRefLink;            /* athlossReferenceLinking-r10 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    VOS_UINT16                                    usResverd;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enDeltaTxDOffsetListPucchR11ValidFlg; /* DeltaTxD-OffsetListPUCCH-r11 是否有效标识  */
    LRRC_LPHY_DELTATXD_OFFSETLIST_PUCCH_R11_STRU  stDeltaTxDOffsetListPucchR11;        /* DeltaTxD-OffsetListPUCCH-v1130 */
#endif
}LRRC_LPHY_POWER_CTRL_DEDICATED_INFO_SCELL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PUSCH_SCELL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PUSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16              enPhyChannelType;
    VOS_UINT16                                      usScellIdx;
    VOS_UINT16                                      usUlFreqInfo;               /* 上行频率, 对应空口ul-FreqInfo-r10->ul-CarrierFreq-r10, 缺省时根据36.101进行计算 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                  enBandInd;                  /* 频带指示 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16             enLteModeType;              /* 指示频点所属的制式类型, FDD或TDD */
    VOS_UINT16                                      usPhyCellId;
    VOS_UINT16                                      usStagId;                   /* stag-Id-r11 */
#else
    VOS_UINT16                                      usReserved;
#endif
    LRRC_LPHY_BAND_WIDTH_ENUM_UINT16                enUlBandWidth;              /* 上行带宽,对应空口ul-FreqInfo-r10->ul-Bandwidth-r10，缺省时填写下行带宽 */
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM_UINT16      enUlCPLen;                  /* 上行CP长度 */
    VOS_INT16                                       sMaxTxPwr;                  /* 最大发射功率 p-Max-r10 */
    LRRC_LPHY_PUSCH_COMM_INFO_STRU                  stPuschCommInfo;            /* 公共PUSCH配置参数 */
    LRRC_LPHY_POWER_CTRL_COMM_INFO_SCELL_STRU       stPwrCtrlCommInfo;          /* 公共功率控制信息 */
    LRRC_LPHY_ANTENNA_INFO_UL_STRU                  stAntennaInfoUL;            /* antennaInfoUL-r10 */
    LRRC_LPHY_PUSCH_DEDICATED_SCELL_INFO_STRU       stPuschCfgDedicateSCell;    /* pusch-ConfigDedicatedSCell-r10 */
    VOS_UINT16                                      usReserved1;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enUlPowerCtlDedicSCellValidFlg;  /* stUlPowerCtlDedicSCell是否有效 */
    LRRC_LPHY_POWER_CTRL_DEDICATED_INFO_SCELL_STRU  stUlPowerCtlDedicSCell;          /* uplinkPowerControlDedicatedSCell-r10 */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16           enAdditSpecEmissionSCellValidFlg;
    VOS_UINT16                                      usAdditSpecEmissionSCell;   /* additionalSpectrumEmissionSCell-r10 */
}LRRC_LPHY_PUSCH_SCELL_PARA_STRU;

#if (FEATURE_ON == FEATURE_LTE_R11)
/*****************************************************************************
 结构名    : LRRC_LPHY_PRACH_CONFIG_SCELL_INFO_R11_STRU
 协议表格  : RadioResourceConfigCommonSCell-r10->prach-ConfigSCell-r11
 ASN.1描述 :
 结构说明  : PRACH物理信道配置参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usReserved;
    VOS_UINT16                                    usHighSpeedFlg;               /* PRACH-Configuration->highSpeedFlag */
    VOS_UINT16                                    usZeroCorrelationZoneConfig;  /* zeroCorrelationZoneConfig */
    VOS_UINT16                                    usFrequencyOffset;            /* prach-FrequencyOffset */
}LRRC_LPHY_PRACH_CONFIG_SCELL_INFO_R11_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PRACH_CONFIG_STRU
 协议表格  :  RadioResourceConfigCommonSCell-r10->prach-ConfigSCell-r11
 ASN.1描述 :
 结构说明  : PRACH物理信道配置参数数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usRootSequenceIndex;          /* PRACH-Configuration->rootSequenceIndex */
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enPrachCfgSCellInfoR11ValidFlg;
    LRRC_LPHY_PRACH_CONFIG_SCELL_INFO_R11_STRU    stPrachCfgSCellInfoR11;
}LRRC_LPHY_PRACH_CONFIG_SCELL_R11_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PRACH_CONFIG_STRU
 协议表格  : PRACH-ConfigSCell-r10
             prach-ConfigSCell-r11
 ASN.1描述 :
 结构说明  : PRACH物理信道配置参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enPrachSCellCfgR11ValidFlg;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16         enConfigIndexValidFlg;
    LRRC_LPHY_UL_CYCLIC_PREFIX_LEN_ENUM_UINT16    enUlCPLen;                    /* 上行CP长度 */
    VOS_UINT16                                    usConfigIndex;                /* PRACH-Config->prach-ConfigInfo->prach-ConfigIndex or prach-ConfigIndex-r10 */
    LRRC_LPHY_PRACH_CONFIG_SCELL_R11_STRU         stPrachSCellCfgR11;           /* PRACH-Config中除了prach-ConfigIndex之外参数*/
}LRRC_LPHY_PRACH_CONFIG_SCELL_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_PRACH_SCELL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PRACH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16              enPhyChannelType;
    VOS_UINT16                                      usScellIdx;
    VOS_UINT16                                      usUlFreqInfo;               /* 上行频率, 对应空口ul-FreqInfo-r10->ul-CarrierFreq-r10, 缺省时根据36.101进行计算 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16                  enBandInd;                  /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16             enLteModeType;              /* 指示频点所属的制式类型, FDD或TDD */
    VOS_UINT16                                      usPhyCellId;
    LRRC_LPHY_PRACH_CONFIG_SCELL_STRU               stPrachInfo;
}LRRC_LPHY_PRACH_SCELL_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_STAG_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_STAG_CONFIG_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT16                                          usStagIdNum;            /*数组ausStagId的有效个数，代表当前实际存在的stag id数目.0:代表当前实际存在的stag id数目为0，即释放所有存在的stag id*/
    VOS_UINT16                                          ausStagId[LRRC_LPHY_MAX_STAG_NUM];
    VOS_UINT16                                          usReserved;
}LRRC_LPHY_STAG_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_STAG_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_STAG_CONFIG_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_STAG_CONFIG_CNF_STRU;
#endif

/*****************************************************************************
 结构名    : LRRC_LPHY_PDSCH_SCELL_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 解数据的PDSCH物理信道参数数据结构
*****************************************************************************/
typedef struct
{
    LRRC_LPHY_CHANNEL_TYPE_ENUM_UINT16      enPhyChannelType;
    VOS_UINT16                              usSCellIdx;                         /* SCELL索引 */
    VOS_UINT16                              usDlFreqInfo;                       /* SCELL下行频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16          enBandInd;                          /* 频带指示 */
    VOS_UINT16                              usPhyCellId;
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16     enLteModeType;                      /* 指示频点所属的制式类型, FDD或TDD */
#else
    VOS_UINT16                              usReserved1;
#endif
    LRRC_LPHY_PDSCH_COMM_INFO_STRU          stPdschCommInfoSCell;               /* SCELL的PDSCH公共信息 */
    LRRC_LPHY_ANTENNA_DEDICATED_INFO_STRU   stAntennaDedicatedInfo;             /* 专用天线信息 */
    VOS_UINT16                              usReserved2;
    LRRC_LPHY_PARA_VALID_FLAG_ENUM_UINT16   enCrossCarrSchedulCfgValidFlg;      /* stCrossCarrSchedulCfg是否有效 */
    LRRC_LPHY_CROSS_CARR_SCHEDUL_CFG_STRU   stCrossCarrSchedulCfg;              /* crossCarrierSchedulingConfig-r10 */
    LRRC_LPHY_CSI_RS_CONFIG_STRU            stCsiRSConfig;                      /* csi-RS-Config-r10 */
#if (FEATURE_ON == FEATURE_LTE_R11)
    LRRC_LPHY_EPDCCH_CONFIG_STRU            stEPdcchConfig;                     /* EPDCCH-Config-r11 */
    LRRC_LPHY_PDSCH_DEDICATED_INFO_STRU     stPdschDedicatedSCell;              /* pdsch-ConfigDedicated-v1130 */
#endif
}LRRC_LPHY_PDSCH_SCELL_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_DPDT_CMD_REQ_STRUs
 协议表格  :
 ASN.1描述 :
 结构说明：
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_DPDT_CMD_ENUM_UINT16                      enCmdIndex;           /*判断指令*/
    VOS_UINT8                                           ucSwitchFlag;      /*0关 1开*/
    VOS_UINT8                                           ucRev[3];
    VOS_UINT32                                          ulDpdtValue;
}LRRC_LPHY_DPDT_CMD_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_DPDT_CMD_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           ucRev[2];
    VOS_UINT32                                          ulDpdtValue;
}LRRC_LPHY_DPDT_CMD_IND_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_NV_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要存储的NV结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usNvId;
    VOS_UINT16        usNvItemLength;    /* 请求写入NV数据长度*/
    VOS_UINT32        ulNvItemAddress;        /* 待写入NV TCM地址*/
} LRRC_LPHY_NV_ITEM_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_NV_WRITE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP请求RRC存储NV消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_LPHY_MSG_ID_ENUM_UINT32       enMsgId;
    VOS_UINT16                         usOpId;
    VOS_UINT16                         usNvItemNum;
    LRRC_LPHY_NV_ITEM_STRU             astNvItems[LRRC_LPHY_MAX_NV_WRITE_NUM];
} LRRC_LPHY_NV_WRITE_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_NV_WRITE_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC完成NV存储后回复DSP消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_LPHY_MSG_ID_ENUM_UINT32          enMsgId;
    VOS_UINT16                            usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16          enResult;
} LRRC_LPHY_NV_WRITE_RSP_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_NORF_INFO_IND
 协议表格  :
 ASN.1描述 :
 结构说明  : DSDS特性打开情况下，RTT向RRC上报NORF指示，并指示上报NORF时的场景
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_DSDS_NORF_TYPE_ENUM_UINT16                enNorfScene;
    VOS_UINT32                                          ulRsv;
}LRRC_LPHY_NORF_INFO_IND;

#if (FEATURE_ON == FEATURE_LTE_R11)
/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_ENABLE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_ENABLE_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_MBMS_ENABLE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_ENABLE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_ENABLE_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBMS_ENABLE_CNF_STRU;


/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_DISABLE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_DISABLE_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_MBMS_DISABLE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_DISABLE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_DISABLE_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBMS_DISABLE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_PMCH_ACTIVE_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_PMCH_ACTIVE_CFG_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                           ucAreaId;
    VOS_UINT8                                           ucPmchNum;              /*1-LRRC_LPHY_MAX_NUM_OF_PMCH_PER_MBSFN*/
    VOS_UINT8                                           aucPmchIndex[LRRC_LPHY_MAX_NUM_OF_PMCH_PER_MBSFN];/*0-LRRC_LPHY_MAX_NUM_OF_PMCH_PER_MBSFN-1*/
    VOS_UINT8                                           aucReservered[3];
}LRRC_LPHY_MBMS_PMCH_ACTIVE_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_PMCH_ACTIVE_REQ_STRU
 协议表格  :
 ASN.1描述 : 全覆盖配置
 结构说明  : LRRC_LPHY_MBMS_PMCH_ACTIVE_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT16                                          usAreaNum;              /*1 ~ LRRC_LPHY_MAX_NUM_OF_MBSFN_AREA*/
    LRRC_LPHY_MBMS_PMCH_ACTIVE_CFG_INFO_STRU            astMbmsPmchActiveInfo[LRRC_LPHY_MAX_NUM_OF_MBSFN_AREA];
}LRRC_LPHY_MBMS_PMCH_ACTIVE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_PMCH_ACTIVE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_PMCH_ACTIVE_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBMS_PMCH_ACTIVE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_INFO_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_UINT8                                           aucReservered[2];
}LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_MBMS_ALL_PMCH_INACTIVE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_MBMS_MRS_MEAS_IND
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_MBMS_MRS_MEAS_IND数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    VOS_INT16                                           sRsrp;                  /* RSRP测量值 */
    VOS_INT32                                           lSINR;                  /* 范围:(-10,40db),1X精度 */
}LRRC_LPHY_MBMS_MRS_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RCV_ALL_MCCH_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC指示PHY收到了所有的MCCH消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT8                           aucResv[2];
}LRRC_LPHY_MBMS_RCV_ALL_MCCH_IND_STRU;
#endif

/*****************************************************************************
 结构名    : LRRC_LPHY_CONNECTED_IDLE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区从连接态到空闲态直接驻留数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT16                          usFreqInfo;                             /* 小区的频点 */
    LRRC_LPHY_BAND_IND_ENUM_UINT16      enBandInd;                              /* 频带指示 */
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteModeType;                          /* 指示频点所属的制式类型, FDD或TDD */
    VOS_UINT16                          usCellId;                               /* 小区ID */
    LRRC_LPHY_BAND_WIDTH_ENUM_UINT16    enDlBandWidth;                          /* 下行带宽,对应空口MasterInformationBlock->dl-Bandwidth字段 */
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16  enAntennaPortsCount;                    /* 传输天线数量,对应空口antennaPortsCount字段 */
    VOS_UINT16                          usReserved;                             /* 保留字段 */
    LRRC_LPHY_TDD_CONFIG_INFO_STRU      stTddConfigInfo;                        /* TDD配置信息,对应空口TDD-Configuration字段  */
}LRRC_LPHY_CONNECTED_TO_IDLE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CONNECTED_TO_IDLE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_LPHY_CONNECTED_TO_IDLE_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                                          usOpId;
    LRRC_LPHY_RESULT_ENUM_UINT16                        enResult;
}LRRC_LPHY_CONNECTED_TO_IDLE_CNF_STRU;


/*begin: hifi sync switch */
/*****************************************************************************
 结构名    : LRRC_LPHY_HIFI_SYNC_SWITCH_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知LDSP HIFI同步开关指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT8                                           ucHifiSyncEnabled;      /* 0: 关闭; 1: 打开; */
    VOS_UINT8                                           ucPowerState;           /* Modem1 开关机状态，0 : 表示关闭 1: 表示打开  */
    VOS_UINT8                                           aucReserved[2];
}LRRC_LPHY_HIFI_SYNC_SWITCH_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_VOICE_SYNC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VoLTE语音业务启动后，LPHY发送该消息LHPA，LHPA转发给CODEC进行时序同步
            |------------------|-------------------|-----OnDuration-----|
            |                  |<--uhwSendOffset-->|
            |<---uhwWakeUpOffset------------------>|
            |                  |                   |
            |                  |                   |
            HIFI唤醒时刻       HIFI发送语音包时刻  CDRX OnDuration起始时刻
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;                                 /* 操作标识符 */
    VOS_UINT16                          usForceSyncFlag;                        /*强制同步标识*/

    VOS_UINT32                          ulOnDurationSlice;                      /* LPHY给出的LTE CDRX OnDuration起始时刻*/
    VOS_UINT16                          usWakeUpOffset;                         /* 以uwOnDurationSlice为基点，HIFI唤醒提前量*/
    VOS_UINT16                          usSendOffset;                           /* 以uwOnDurationSlice为基点，HIFI发送语音包前量 */
}LRRC_LPHY_VOICE_SYNC_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RLF_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLF参数结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGcfTestModeInd;                       /*0:普通模式,1:GCF测试模式 */
    VOS_UINT32                          ulN310;                                 /*取值范围[1,2,3,4,6,8,10,20]*/
    VOS_UINT32                          ulT310;                                 /*单位ms,枚举见36.331  6.3.2*/
    VOS_UINT32                          ulN311;                                 /*取值范围[1,2,3,4,5,6,8,10]*/
    VOS_UINT32                          ulT311;                                 /*单位ms,枚举见36.331  6.3.2*/
}LRRC_LPHY_RLF_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_RLF_PARA_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLF参数通知结构,LPHY根据不同的网络配置,用来区分不同的同失步门限
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_LPHY_MSG_ID_ENUM_UINT32                        enMsgId;                /*_H2ASN_Skip*/

    LRRC_LPHY_RLF_PARA_STRU                             stRlfPara;
}LRRC_LPHY_RLF_PARA_NOTIFY_STRU;


/*****************************************************************************
 结构名    : LTE_RRC_EXTBANDINFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Band28全频段特性新增NV
             ucflag:1表示扩展BAND功能打开；0表示关闭
             ucBandnum:表示有几个BAND需要用到扩展BAND号
             aucRsv[]:预留
             aucBandInd[]:需要扩展BAND号的BAND列表
*****************************************************************************/
typedef struct
{
    VOS_UINT8          ucflag;
    VOS_UINT8          ucBandnum;
    VOS_UINT8          aucRsv[2];
    VOS_UINT8          aucBandInd[8];
}LTE_RRC_EXTBANDINFO_STRU;

/*****************************************************************************
 结构名    : RRC_UE_CAP_SUPP_EUTRA_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UE EUTRA能力中RF->Band参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEutraBand;
    VOS_UINT8                           enHalfDuplex;
    VOS_UINT8                           aucReserved[2];
} LRRC_LPHY_UE_CAP_SUPP_EUTRA_BAND_STRU;

/*****************************************************************************
 结构名    : RRC_UE_CAP_RF_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UE EUTRA能力中RF参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                 aucReserved[2];
    VOS_UINT16                                usCnt;
    LRRC_LPHY_UE_CAP_SUPP_EUTRA_BAND_STRU     astSuppEutraBandList[LRRC_LPHY_MAX_NUM_OF_BANDS];
} LRRC_LPHY_UE_CAP_RF_PARA_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_INIT_RECFG_INFO_STRUs
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP加载过程中重配天线选择等参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucUeCapUl;
    VOS_UINT8                            ucUeCapDl;
    VOS_UINT8                            ucAntSelect;
    VOS_UINT8                            ucNvLteDefaultBandIdx;
    VOS_UINT32                           ulGcfConnDrxStubFlag;
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16  enLteMode;
    VOS_UINT8                            aucReserved[2];
    LTE_RRC_EXTBANDINFO_STRU             stExtBandInfo;
    LRRC_LPHY_UE_CAP_RF_PARA_STRU        stRfCap;
} LRRC_LPHY_INIT_RECFG_INFO_STRU;


typedef LRRC_LPHY_FREQ_RSSI_SCAN_REQ_STRU LRRC_LPHY_FREQ_RSSI_SCAN_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LPHY_CHR_SRVING_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前服务小区信息:包括GCI、Tac、PlmnId
*****************************************************************************/
typedef struct
{
    VOS_UINT32               ulSrvCellIdentity;         /*Sib1中的Gci*/
    VOS_UINT16               usSrvCellTrackAreaCode;    /*Sib1中的Tac*/
    VOS_UINT16               usReserved;
    VOS_UINT32               ulMcc;
    VOS_UINT32               ulMnc;
}LRRC_LPHY_CHR_SRVING_CELL_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
 Function Name   : LPHY_NosignalNvReload
 Description     : 非信令模式用于不下电重新加载NV，以用于NV及时生效
 Input           : None
 Output          : None
 Return          : None

 History         :

*****************************************************************************/
extern VOS_UINT32  LPHY_EquipNvReload(LRRC_LPHY_UE_CAP_RF_PARA_STRU *pstRfCap,
                                              LTE_RRC_EXTBANDINFO_STRU   *pstExtBandInfo);

/*****************************************************************************
 Function Name   : LPHY_InitNvLoad
 Description     : 初始化ddr中配置信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
*****************************************************************************/
extern VOS_UINT32  LPHY_InitNvLoad(LRRC_LPHY_UE_CAP_RF_PARA_STRU *pstRfCap,
                                        LTE_RRC_EXTBANDINFO_STRU   *pstExtBandInfo);

/*****************************************************************************
 Function Name   : LPHY_InitDspAddr
 Description     : 初始化阶段设置PHY用到的地址
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
****************************************/
extern VOS_UINT32  LPHY_InitDspAddr( void );


/*****************************************************************************
 Function Name   : LPHY_CfgRF6360Info
 Description     : 初始化过程中加载PHY公共NV
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Guojiyu      2010-5-17  Draft Enact

*****************************************************************************/
extern VOS_UINT32 LPHY_CfgRF6360Info( void );

/*****************************************************************************
 Function Name   : LHPA_GetReCfgInfo
 Description     : LPHY通过该函数获取如下信息的重
                   1. UE能力等级
                   2. 是否存在128非标频段的增加
                   3. 天线选择
                   4. GCF桩
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Lishangfeng      2011-10-13  Draft Enact

*****************************************************************************/
extern void LHPA_GetReCfgInfo(LRRC_LPHY_INIT_RECFG_INFO_STRU *pstReCfginfo);

/*****************************************************************************
 Function Name   : LHPA_GetBandCount
 Description     : 获取某个Band是否需要做非标拆分
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.Lishangfeng      2011-10-13  Draft Enact

*****************************************************************************/
extern VOS_UINT16 LHPA_GetBandCount( VOS_UINT8 ucBand );



/*****************************************************************************
 Function Name   : LPHY_GetBtFtmBandCandFreqInfo
 Description     : 信令BT方式下，PS通过该函数获取产线先验频点NV ID
 Input           : VOS_UINT8 ucBand
 Output          : None
 Return          : 0:SUCC
                   1:FAIL
 History         :
     1.Wang Yangcai 49178       2010-12-27  Draft Enact

*****************************************************************************/
extern VOS_UINT32 LPHY_GetBtFtmBandCandFreqInfo(VOS_UINT32 *pstNVId,VOS_UINT8 ucBand);

/*****************************************************************************
 Function Name   :LRRC_LPHY_GetSrvingCellSibInfo
 Description     :获取当前服务小区的Cgi\Plmn\Tac信息
 Input           :
 Output          : pstScellInfo:当前服务小区sib1中的相关信息
 Return          : 1 获取信息成功;0 获取信息失败
 History         :
    1.w00272217     2015-07-27  Draft Enact
*****************************************************************************/
extern VOS_UINT8 LRRC_LPHY_GetSrvingCellSibInfo(LRRC_LPHY_CHR_SRVING_CELL_INFO_STRU *pstScellInfo);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LRrcLPhyInterface.h */
