#ifndef __WASPHYCOMMINTERFACE_H__
#define __WASPHYCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "product_config.h"
#include "Hi_Config.h"
#include "vos.h"

#pragma pack(4)

#define MULTIBAND_SUPPORT_SWITCH                (1)                /*开关为1表示支持多频段,为0表示不支持*/

#define RRC_PHY_MAX_FREQ_NUM                   (20)   /*频率列表中最大的频率数*/

#define RRC_PHY_MAX_PSCH_FREQ_NUM              (25)    /*下发给WDSP做PSCH的一组频点的最大个数*/

#define RRC_PHY_MAX_SAMPLE_FREQ_NUM_PER_BAND   (25)    /*一个band内采样的最大频点个数*/


#define RRC_PHY_MAX_W_BG_SEARCH_FREQ_NUM        (32)

#define RRC_PHY_MAX_G_BG_SEARCH_FREQ_NUM        (60)

/**************精确接收相关的宏***********************/
#define RRC_PHY_MAX_SEG_POS_INFO_NUM           (10)

#define PHY_RRC_MAX_REPORT_CANDIDATE_CELL_NUM  (32) /*Cell Search 上报时携带的最多小区个数*/


#define RRC_PHY_MAX_CANDIDATE_CELL_NUM         (64)    /*候补小区搜索下发的最多小区个数 */

#define  RRC_PHY_BCCH_DATA_SIZE                 (32)


/*****************************************************************************
 枚举名    : PHYITF_RSLT_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接口中的有效性标识
*****************************************************************************/

enum    PHYITF_RSLT_ENUM
{
    PHYITF_SUCC                         = 0,                                    /* 成功 */
    PHYITF_FAIL                         = 1,                                    /* 失败 */
    PHYITF_DRX_NOT_SUPPORT              = 2,                                    /* DRX太短 */

    PHYITF_RSLT_BUTT
};
typedef VOS_UINT16  PHYITF_RSLT_ENUM_UINT16;

enum PHYITF_BG_RESULT_TYPE_ENUM
{
    PHYITF_BG_SUCC              = 0,
    PHYITF_BG_FAIL              = 1,

    PHYITF_BG_BUTT
};
typedef  VOS_UINT16 PHYITF_BG_RESULT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_ANT_CHANGE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RSSI搜索时天线是否发生切换
*****************************************************************************/

enum    PHYITF_ANT_CHANGE_ENUM
{
    PHYITF_ANT_NOT_CHANGE     = 0,            /* 天线没有发生切换 */
    PHYITF_ANT_CHANGE         = 1,            /* 天线发生切换 */
    PHYITF_ANT_BUTT
};
typedef VOS_UINT32 PHYITF_ANT_CHANGE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : RRC_PHY_MSG_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRC -> PHY 接口消息ID
*****************************************************************************/

enum    RRC_PHY_MSG_ID_ENUM
{
    ID_RRC_PHY_RL_SETUP_REQ                                 = 0x1001,   /* _H2ASN_MsgChoice RRC_PHY_RL_SETUP_REQ_STRU */
    ID_RRC_PHY_RL_MODIFY_REQ                                = 0x1002,   /* _H2ASN_MsgChoice RRC_PHY_RL_MODIFY_REQ_STRU */
    ID_RRC_PHY_RL_RELEASE_REQ                               = 0x1003,   /* _H2ASN_MsgChoice RRC_PHY_RL_RELEASE_REQ_STRU */
    ID_RRC_PHY_POWER_CONTROL_REQ                            = 0x1004,   /* _H2ASN_MsgChoice RRC_PHY_POWER_CONTROL_REQ_STRU */
    ID_RRC_PHY_TRCH_CONFIG_REQ                              = 0x1005,   /* _H2ASN_MsgChoice RRC_PHY_TRCH_CONFIG_REQ_STRU */
    ID_RRC_PHY_TRCH_RELEASE_REQ                             = 0x1006,   /* _H2ASN_MsgChoice RRC_PHY_TRCH_RELEASE_REQ_STRU */

    ID_RRC_PHY_UPLINK_MAXTXPWR_REQ                          = 0x1008,   /* _H2ASN_MsgChoice RRC_PHY_UPLINK_MAXTXPWR_REQ_STRU */
    ID_RRC_PHY_RELALL_PHYCH_REQ                             = 0x1009,   /* _H2ASN_MsgChoice RRC_PHY_RELALL_REQ_STRU */
    ID_RRC_PHY_CAMPED_MAINCELL_REQ                          = 0x100A,   /* _H2ASN_MsgChoice RRC_PHY_CAMPED_MAINCELL_REQ_STRU */

    ID_RRC_PHY_PCCPCH_SETUP_REQ                             = 0x100D,   /* _H2ASN_MsgChoice RRC_PHY_PCCPCH_SETUP_REQ_STRU */
    ID_RRC_PHY_PCCPCH_RELEASE_REQ                           = 0x100E,   /* _H2ASN_MsgChoice RRC_PHY_PCCPCH_RELEASE_REQ_STRU */
    ID_RRC_PHY_CELL_SEARCHING_REQ                           = 0x100F,   /* _H2ASN_MsgChoice RRC_PHY_CELL_SEARCH_REQ_STRU */
    ID_RRC_PHY_MEASUREMENT_IN_IDLE_REQ                      = 0x1010,   /* _H2ASN_MsgChoice RRC_PHY_IDLE_MEASURE_REQ_STRU */
    ID_RRC_PHY_QUALITY_MEASUREMENT_REQ                      = 0x1011,   /* _H2ASN_MsgChoice RRC_PHY_QUALITY_MEASUREMENT_REQ_STRU */
    ID_RRC_PHY_MEASUREMENT_IN_CONNECTED_REQ                 = 0x1012,   /* _H2ASN_MsgChoice RRC_PHYITF_CONNECT_MEASURE_REQ_STRU */
    ID_RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ       = 0x1013,   /* _H2ASN_MsgChoice RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ_STRU */
    ID_RRC_PHY_MACE_CONFIG_REQ                              = 0x1014,   /* _H2ASN_MsgChoice RRC_PHY_MACE_CONFIG_REQ_STRU */


    ID_RRC_PHY_FREQ_MEASURE_REQ                             = 0x1015,   /* _H2ASN_MsgChoice RRC_PHY_FREQ_MEASURE_REQ_STRU */
    ID_RRC_PHY_BG_SEARCH_STOP_REQ                           = 0x1017,   /* _H2ASN_MsgChoice RRC_PHY_BG_SEARCH_STOP_REQ_STRU */
    ID_RRC_PHY_BG_SEARCH_SUSPEND_REQ                        = 0x1018,   /* _H2ASN_MsgChoice RRC_PHY_BG_SEARCH_SUSPEND_REQ_STRU */
    ID_RRC_PHY_BG_SEARCH_RESUME_REQ                         = 0x1019,   /* _H2ASN_MsgChoice RRC_PHY_BG_SEARCH_RESUME_REQ_STRU */
    ID_RRC_PHY_SYSINFO_POS_NOTIFY_REQ                       = 0x101A,   /* _H2ASN_MsgChoice RRC_PHY_SYSINFO_POS_NOTIFY_REQ_STRU */
    ID_RRC_PHY_BSIC_VERIFIED_REQ                            = 0x1020,   /* _H2ASN_MsgChoice RRC_PHY_BSIC_VERIFIED_REQ_STRU */
    ID_RRC_PHY_POSITION_MEASUREMENT_REQ                     = 0x1021,   /* _H2ASN_MsgChoice RRC_PHY_POSITION_MEASUREMENT_REQ_STRU */
    ID_RRC_PHY_MACE_RELEASE_REQ                             = 0x1022,   /* _H2ASN_MsgChoice RRC_PHY_MACE_RELEASE_REQ_STRU */
    ID_RRC_PHY_MAC_E_I_RESET_REQ                            = 0x1023,   /* _H2ASN_MsgChoice RRC_PHY_MAC_E_I_RESET_REQ_STRU */
    ID_RRC_PHY_MACHS_RESET_REQ                              = 0x1024,   /* _H2ASN_MsgChoice RRC_PHY_MACHS_RESET_REQ_STRU*/
    ID_RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ                = 0x1025,   /* _H2ASN_MsgChoice RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ_STRU */
    ID_RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ                = 0x1026,   /* _H2ASN_MsgChoice RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ_STRU */

    ID_RRC_PHY_CBS_CONFIG_REQ                               = 0x1027,   /* _H2ASN_MsgChoice RRC_PHY_CBS_CONFIG_REQ_STRU */
    ID_RRC_PHY_CPC_CONFIG_REQ                               = 0X1028,   /* _H2ASN_MsgChoice RRC_PHY_CPC_CONFIG_REQ_STRU*/
    ID_RRC_PHY_CPC_DISABLE_REQ                              = 0X1029,   /* _H2ASN_MsgChoice RRC_PHY_CPC_DISABLE_REQ_STRU*/
    ID_RRC_PHY_SCND_RL_SETUP_REQ                            = 0x102A,   /* _H2ASN_MsgChoice RRC_PHY_SCND_RL_SETUP_REQ_STRU */
    ID_RRC_PHY_SCND_RL_MODIFY_REQ                           = 0x102B,   /* _H2ASN_MsgChoice RRC_PHY_SCND_RL_MODIFY_REQ_STRU */
    ID_RRC_PHY_SCND_RL_REL_REQ                              = 0x102C,   /* _H2ASN_MsgChoice RRC_PHY_SCND_RL_REL_REQ_STRU */
    ID_RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ                    = 0x102D,   /* _H2ASN_MsgChoice RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ_STRU */

    /* ADD UL_E_L2 */
    ID_RRC_PHY_MACI_CONFIG_REQ                              = 0x102E,   /* _H2ASN_MsgChoice RRC_PHY_MACI_CONFIG_REQ_STRU */
    ID_RRC_PHY_MACI_RELEASE_REQ                             = 0x102F,   /* _H2ASN_MsgChoice RRC_PHY_MACI_RELEASE_REQ_STRU */
    /* END UL_E_L2 */
    ID_RRC_PHY_SET_WORK_MODE_REQ                            = 0x1032,    /* _H2ASN_MsgChoice RRC_PHY_SET_WORK_MODE_REQ_STRU */
    ID_RRC_PHY_SET_RAT_PRI_REQ                              = 0x1033,    /* _H2ASN_MsgChoice RRC_PHY_SET_RAT_PRI_REQ_STRU */

    /* 周期接收SIB7新增接口------ start */
    ID_RRC_PHY_PRACH_INIT_TX_POWER_IND                      = 0x1034,   /* _H2ASN_MsgChoice RRC_PHY_PRACH_INIT_TX_POWER_IND_STRU */
    /* 周期接收SIB7新增接口------ end */

    ID_RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ                    = 0x1035,   /* _H2ASN_MsgChoice RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ_STRU */
    ID_RRC_PHY_CS_PS_IND                                    = 0x1036,   /* _H2ASN_MsgChoice RRC_PHY_CS_PS_IND_STRU */
    ID_RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND                 = 0x1037,   /* _H2ASN_MsgChoice RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND_STRU */
    ID_RRC_PHY_SLAVE_MEASURE_REQ                            = 0x1038,   /* _H2ASN_MsgChoice RRC_PHY_SLAVE_MEASURE_REQ_STRU */
    ID_RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND                    = 0x1039,   /* _H2ASN_MsgChoice RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND_STRU */
    ID_RRC_PHY_RTT_TEST_CFG_REQ                             = 0xE001,   /* _H2ASN_MsgChoice RRC_PHY_RTT_TEST_REG_CFG_REQ_STRU */

    ID_PHY_RRC_MEASUREMENT_IN_CONNECTED_CNF                 = 0x0001,   /* _H2ASN_MsgChoice PHY_RRC_CONNECT_MEASURE_CNF_STRU */
    ID_PHY_RRC_MEASUREMENT_IN_CONNECTED_IND                 = 0x0002,   /* _H2ASN_MsgChoice PHY_RRC_CONNECT_MEASURE_IND_STRU */
    ID_PHY_RRC_BSIC_VERIFIED_CNF                            = 0x0003,   /* _H2ASN_MsgChoice PHY_RRC_BSIC_VERIFIED_CNF_STRU */
    ID_PHY_RRC_RL_SETUP_CNF                                 = 0x3201,   /* _H2ASN_MsgChoice PHY_RRC_RL_SETUP_CNF_STRU */
    ID_PHY_RRC_RL_MODIFY_CNF                                = 0x3202,   /* _H2ASN_MsgChoice PHY_RRC_RL_MODIFY_CNF_STRU */
    ID_PHY_RRC_RL_RELEASE_CNF                               = 0x3203,   /* _H2ASN_MsgChoice PHY_RRC_RL_RELEASE_CNF_STRU */
    ID_PHY_RRC_ACTIVATE_IND                                 = 0x3204,   /* _H2ASN_MsgChoice PHY_RRC_ACTIVATE_IND_STRU */
    ID_PHY_RRC_POWER_CONTROL_CNF                            = 0x3205,   /* _H2ASN_MsgChoice PHY_RRC_POWER_CONTROL_CNF_STRU */
    ID_PHY_RRC_TRCH_CONFIG_CNF                              = 0x3206,   /* _H2ASN_MsgChoice PHY_RRC_TRCH_CONFIG_CNF_STRU */
    ID_PHY_RRC_TRCH_RELEASE_CNF                             = 0x3207,   /* _H2ASN_MsgChoice PHY_RRC_TRCH_RELEASE_CNF_STRU */
    ID_PHY_RRC_ERROR_IND                                    = 0x3208,   /* _H2ASN_MsgChoice PHY_RRC_ERROR_IND_STRU */
    ID_PHY_RRC_SYNC_IND                                     = 0x3209,   /* _H2ASN_MsgChoice PHY_RRC_SYNC_IND_STRU */
    ID_PHY_RRC_OUT_OF_SYNC_IND                              = 0x320A,   /* _H2ASN_MsgChoice PHY_RRC_OUT_OF_SYNC_IND_STRU */
    ID_PHY_RRC_RL_FAIL_IND                                  = 0x320B,   /* _H2ASN_MsgChoice PHY_RRC_RL_FAIL_IND_STRU */
    ID_PHY_RRC_RELALL_PHYCH_CNF                             = 0x320C,   /* _H2ASN_MsgChoice PHY_RRC_RELALL_CNF_STRU */
    ID_PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND              = 0x320D,   /* _H2ASN_MsgChoice PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU */
    ID_PHY_RRC_CAMPED_MAINCELL_CNF                          = 0x320E,   /* _H2ASN_MsgChoice PHY_RRC_CAMPED_MAINCELL_CNF_STRU */

    ID_PHY_RRC_MACE_CONFIG_CNF                              = 0x320F,   /* _H2ASN_MsgChoice PHY_RRC_MACE_CONFIG_CNF_STRU */

/*V3 R7_7C1 Start */
    ID_PHY_RRC_MAC_ACTIVATE_IND                             = 0x3210,   /* _H2ASN_MsgChoice PHY_RRC_MAC_ACTIVATE_IND_STRU */
/* V3 R7_7C1 End */

    ID_PHY_RRC_MACE_RELEASE_CNF                             = 0x3211,   /* _H2ASN_MsgChoice PHY_RRC_MACE_RELEASE_CNF_STRU */
    ID_PHY_RRC_MAC_E_I_RESET_CNF                            = 0x3212,   /* _H2ASN_MsgChoice PHY_RRC_MAC_E_I_RESET_CNF_STRU */
    ID_PHY_RRC_UPLINK_MAXTXPWR_CNF                          = 0x3213,   /* _H2ASN_MsgChoice PHY_RRC_UPLINK_MAXTXPWR_CNF_STRU */
    ID_PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND                 = 0x3214,   /* _H2ASN_MsgChoice PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND_STRU */
    ID_PHY_RRC_MACHS_RESET_CNF                              = 0x3215,   /* _H2ASN_MsgChoice PHY_RRC_MACHS_RESET_CNF_STRU*/
    ID_PHY_RRC_RELALL_PHYCH_ACTIVATE_IND                    = 0x3216,   /* _H2ASN_MsgChoice PHY_RRC_RELALL_PHYCH_ACTIVATE_IND_STRU*/
    ID_PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF                = 0x3217,   /* _H2ASN_MsgChoice PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF_STRU */
    ID_PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF                = 0x3218,   /* _H2ASN_MsgChoice PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF_STRU */
    ID_PHY_RRC_CBS_CONFIG_CNF                               = 0x3219,   /* _H2ASN_MsgChoice PHY_RRC_CBS_CONFIG_CNF_STRU */
    ID_PHY_RRC_CPC_CONFIG_CNF                               = 0x321A,   /* _H2ASN_MsgChoice PHY_RRC_CPC_CONFIG_CNF_STRU */
    ID_PHY_RRC_CPC_DISABLE_CNF                              = 0x321B,   /* _H2ASN_MsgChoice PHY_RRC_CPC_DISABLE_CNF_STRU */
    ID_PHY_RRC_SCND_RL_SETUP_CNF                            = 0x321C,   /* _H2ASN_MsgChoice PHY_RRC_SCND_RL_SETUP_CNF_STRU */
    ID_PHY_RRC_SCND_RL_MODIFY_CNF                           = 0x321D,   /* _H2ASN_MsgChoice PHY_RRC_SCND_RL_MODIFY_CNF_STRU */
    ID_PHY_RRC_SCND_RL_REL_CNF                              = 0x321E,   /* _H2ASN_MsgChoice PHY_RRC_SCND_RL_REL_CNF_STRU */
    ID_PHY_RRC_SET_WORK_MODE_CNF                            = 0x321F,   /* _H2ASN_MsgChoice PHY_RRC_SET_WORK_MODE_CNF_STRU */
    ID_PHY_RRC_SET_RAT_PRI_CNF                              = 0x3220,   /* _H2ASN_MsgChoice PHY_RRC_SET_RAT_PRI_CNF_STRU */

    /* ADD UL_E_L2 */
    ID_PHY_RRC_MACI_CONFIG_CNF                              = 0x3221,   /* _H2ASN_MsgChoice PHY_RRC_MACI_CONFIG_CNF_STRU */
    ID_PHY_RRC_MACI_RELEASE_CNF                             = 0x3222,   /* _H2ASN_MsgChoice PHY_RRC_MACI_RELEASE_CNF_STRU */
    /* END UL_E_L2 */
    ID_PHY_RRC_DISABLE_ULDCCH_IND                           = 0x3223,   /* _H2ASN_MsgChoice PHY_RRC_DISABLE_ULDCCH_IND_STRU */
    ID_PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF                    = 0x3224,   /* _H2ASN_MsgChoice PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF_STRU */
    ID_PHY_RRC_CELL_SEARCH_IND                              = 0x3301,   /* _H2ASN_MsgChoice PHY_RRC_CELL_SEARCH_IND_STRU */
    ID_PHY_RRC_MEASUREMENT_IN_IDLE_CNF                      = 0x3302,   /* _H2ASN_MsgChoice PHY_RRC_IDLE_MEASURE_CNF_STRU */
    ID_PHY_RRC_MEASUREMENT_IN_IDLE_IND                      = 0x3303,   /* _H2ASN_MsgChoice PHY_RRC_IDLE_MEASURE_IND_STRU */
    ID_PHY_RRC_BG_SEARCH_STOP_CNF                           = 0x3306,   /* _H2ASN_MsgChoice PHY_RRC_BG_SEARCH_STOP_CNF_STRU */
    ID_PHY_RRC_BG_SEARCH_SUSPEND_CNF                        = 0x3307,   /* _H2ASN_MsgChoice PHY_RRC_BG_SEARCH_SUSPEND_CNF_STRU */
    ID_PHY_RRC_BG_SEARCH_RESUME_CNF                         = 0x3308,   /* _H2ASN_MsgChoice PHY_RRC_BG_SEARCH_RESUME_CNF_STRU */
    ID_PHY_RRC_FREQ_MEASURE_IND                             = 0x3309,   /* _H2ASN_MsgChoice PHY_RRC_FREQ_MEASURE_IND_STRU */
    ID_PHY_RRC_PCCPCH_SETUP_CNF                             = 0x3401,   /* _H2ASN_MsgChoice PHY_RRC_PCCPCH_SETUP_CNF_STRU */
    ID_PHY_RRC_PCCPCH_RELEASE_CNF                           = 0x3402,   /* _H2ASN_MsgChoice PHY_RRC_PCCPCH_RELEASE_CNF_STRU */
    ID_PHY_RRC_BCCHDATA_IND                                 = 0x3403,   /* _H2ASN_MsgChoice PHY_RRC_BCCH_DATA_ADD_SFN_IND_STRU */
    ID_PHY_RRC_SYSINFO_POS_NOTIFY_CNF                       = 0x3404,   /* _H2ASN_MsgChoice PHY_RRC_SYSINFO_POS_NOTIFY_CNF_STRU */
    ID_PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF       = 0x3501,   /* _H2ASN_MsgChoice PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF_STRU */
    ID_PHY_RRC_QUALITY_MEASUREMENT_CNF                      = 0x3502,   /* _H2ASN_MsgChoice PHY_RRC_QUALITY_MEASUREMENT_CNF_STRU */
    ID_PHY_RRC_QUALITY_MEASUREMENT_IND                      = 0x3503,   /* _H2ASN_MsgChoice PHY_RRC_QUALITY_MEASUREMENT_IND_STRU */
    ID_PHY_RRC_POSITION_MEASUREMENT_CNF                     = 0x3504,   /* _H2ASN_MsgChoice PHY_RRC_POSITION_MEASUREMENT_CNF_STRU*/
    ID_PHY_RRC_POSITION_MEASUREMENT_IND                     = 0x3505,   /* _H2ASN_MsgChoice PHY_RRC_POSITION_MEASUREMENT_IND_STRU*/
    ID_PHY_RRC_UE_INTERNAL_MEASUREMENT_IND                  = 0x3506,   /* _H2ASN_MsgChoice PHY_RRC_UE_INTERNAL_MEASUREMENT_IND_STRU */
    ID_PHY_RRC_BCCH_FAIL_IND                                = 0x3507,   /* _H2ASN_MsgChoice PHY_RRC_BCCH_FAIL_IND_STRU */
    ID_PHY_RRC_WCDMA_CELL_TIMING_IND                        = 0x3509,   /* _H2ASN_MsgChoice PHY_RRC_WCDMA_CELL_TIMING_IND_STRU */
    ID_PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF                    = 0x350A,   /* _H2ASN_MsgChoice PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF_STRU */
    ID_PHY_RRC_WCDMA_TIMING_ERROR_IND                       = 0x350B,   /* _H2ASN_MsgChoice PHY_RRC_WCDMA_TIMING_ERROR_IND_STRU */
    ID_PHY_RRC_SLAVE_MEASURE_CNF                            = 0x350C,   /* _H2ASN_MsgChoice PHY_RRC_SLAVE_MEASURE_CNF_STRU */
    ID_PHY_RRC_SLAVE_MEASURE_IND                            = 0x350D,   /* _H2ASN_MsgChoice PHY_RRC_SLAVE_MEASURE_IND_STRU */
    ID_PHY_RRC_AFC_LOCK_INFO_IND                            = 0x350E,   /* _H2ASN_MsgChoice PHY_RRC_AFC_LOCK_IND_STRU */
    ID_PHY_RRC_RADIO_RESOURCE_IND                           = 0x350F,   /* _H2ASN_MsgChoice PHY_RRC_RADIO_RESOURCE_IND_STRU */
    ID_PHY_RRC_RTT_TEST_REG_IND                             = 0xF001,   /* _H2ASN_MsgChoice PHY_RRC_RTT_TEST_REG_IND_STRU */
    ID_RRC_PHY_MSG_BUTT

};
typedef VOS_UINT16 RRC_PHY_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_TX_DIVER_IND_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 发分集指示类型
*****************************************************************************/

enum    PHYITF_TX_DIVER_IND_ENUM
{
    PHYITF_TX_DIVER_NO_DIVER                 = 0,       /* 没有发分集 */
    PHYITF_TX_DIVER_STTD                     = 1,       /* STTD */
    PHYITF_TX_DIVER_CLOSELOOP_TIM_ADJ_SLOT1  = 2,       /* TX Diversity Mode = closed loop mode1, Closed loop timing adjustment mode = 1 */
    PHYITF_TX_DIVER_CLOSELOOP_TIM_ADJ_SLOT2  = 3,       /* TX Diversity Mode = closed loop mode1, Closed loop timing adjustment mode = 2 */
    PHYITF_TX_DIVER_UNKNOWN                  = 0xFF,    /*RRC 不知道发分集的模式*/

    PHYITF_TX_DIVER_BUTT

};
typedef VOS_UINT16 PHYITF_TX_DIVER_IND_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 通知DSP 对频点进行排序的方式
*****************************************************************************/

enum    PHYITF_FREQ_SEARCH_TYPE_ENUM
{
    PHYITF_FREQ_SEARCH_TYPE_RSSI               = 0,            /*通知DSP按照RSSI值来对频点进行搜索*/
    PHYITF_FREQ_SEARCH_TYPE_PSCH               = 1,            /*通知DSP按照PSCH值来对频点进行搜索*/
    PHYITF_FREQ_SEARCH_TYPE_FFT                = 2,            /*通知DSP按照FFT算法来对频点进行搜索*/
    PHYITF_FREQ_SEARCH_TYPE_HISTORY_CAND_RSSI  = 3,            /*通知DSP按照HISTORY_CAND频点场景RSSI来对频点进行搜索*/
    PHYITF_FREQ_SEARCH_TYPE_HISTORY_CAND_PSCH  = 4,            /*通知DSP按照HISTORY_CAND频点场景PSCH来对频点进行搜索*/
    PHYITF_FREQ_SEARCH_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_CELL_SEARCH_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : CSEL 使用的小区Search类型
*****************************************************************************/

enum    PHYITF_CELL_SEARCH_TYPE_ENUM
{
    PHYITF_CELL_SEARCH_NO_CAND_CELL     = 0,            /*无先验小区搜索*/
    PHYITF_CELL_SEARCH_WITH_CAND_CELL   = 1,            /*有先验的候选小区搜索*/
    PHYITF_CELL_SEARCH_FREQ_BAND        = 2,            /*频段搜索,指明要搜索的频段，PHY自己在频段内选择频点搜索*/
    PHYITF_CELL_SEARCH_FREQ_LIST        = 3,            /*离散频点列表搜索,指明要搜索的离散频点,PHY自己按照列表内的频点搜索*/

    PHYITF_CELL_SEARCH_TPPE_BUTT

};
typedef VOS_UINT16 PHYITF_CELL_SEARCH_TYPE_ENUM_UINT16;

/* 接口中的BOOL值定义 */
/*****************************************************************************
 枚举名    : PHYITF_BOOL_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接口中的有效性标识
*****************************************************************************/

enum    PHYITF_BOOL_ENUM
{
    PHYITF_INVALID                      = 0,    /*用于对接口中的valid标志置位，若有效则使用1*/
    PHYITF_VALID                        = 1,    /*用于对接口中的valid标志置位，若无效则使用0*/

    PHYITF_BUTT

};
typedef VOS_UINT16  PHYITF_BOOL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHYITF_PCCPCH_PURPOSE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 建立广播信道的目的
*****************************************************************************/

enum    PHYITF_PCCPCH_PURPOSE_ENUM
{
    PHYITF_PCCPCH_PURPOSE_RCV_SIB7      = 0,                                    /* 解SIB7 */
    PHYITF_PCCPCH_PURPOSE_OTHER         = 1,                                    /* 其他原因 */

    PHYITF_PCCPCH_PURPOSE_BUTT

};
typedef VOS_UINT16  PHYITF_PCCPCH_PURPOSE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_PCCPCH_FAIL_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : BCCH FAIL 失败原因类型
*****************************************************************************/

enum    PHYITF_PCCPCH_FAIL_TYPE_ENUM
{
    PHYITF_PCCPCH_FAIL_CRC_ERROR              = 0,                                    /* 广播数据错误 */
    PHYITF_PCCPCH_FAIL_PRIMITIVE_ERROR        = 1,                                    /* 广播原语异常 */

    PHYITF_PCCPCH_FAIL_TYPE_BUTT

};
typedef VOS_UINT16  PHYITF_PCCPCH_FAIL_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHYITF_CAMPED_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 驻留类型枚举
*****************************************************************************/
enum    PHYITF_CAMPED_TYPE_ENUM
{
    PHYITF_CAMPED_TYPE_COMMON                       = 0,
    PHYITF_CAMPED_TYPE_L2W_HO                       = 1,
    PHYITF_CAMPED_TYPE_G2W_HO                       = 2,
    PHYITF_CAMPED_TYPE_BUTT
};
typedef VOS_UINT16  PHYITF_CAMPED_TYPE_ENUM_UINT16;

/*****************************************************************************
 结构名    : PHYITF_FREQ_MEASURE_BAND_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频段信息，指明这个频段的
             最低频率,最高频率，收发频差和频段号
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              usLowFreq;                          /* 频段的最低频点 */
    VOS_UINT16                              usHighFreq;                         /* 频段的最高频点 */
    VOS_UINT16                              usFreqBandNo;                       /* 频段号 */
    VOS_UINT16                              usTxRxFreqSeparation;               /* 收发频差 */
}PHYITF_FREQ_MEASURE_BAND_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usFreqBandNo;           /*频段号,取值:1,2,3,4,5,6，8*/
    VOS_UINT16                                  usTxRxFreqSeparation;   /*频差*/
    VOS_UINT16                                  usDLFreqInfo;
    VOS_UINT16                                  usReserve1;
}PHYITF_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : PHYITF_FREQ_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 做细扫时需要携带的频点列表
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usFreqNum;              /* 当原因值为PSCH时，需要携带频点个数 */
    VOS_UINT16                                  usReserve1;             /*当原因值为PSCH时，需要携带频点列表 */
    PHYITF_FREQ_INFO_STRU                       astFreqList[RRC_PHY_MAX_PSCH_FREQ_NUM];/* 频率列表中具体的频点信息*/
}PHYITF_FREQ_LIST_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_FREQ_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频点测量请求消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* 操作标识 */
    PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16         enSearchType;           /* 指示DSP是通过RSSI,PSCH还是FFT对频点进行排序 */
    VOS_UINT16                                  usStepLength;           /* 通知DSP采样取频点的步长，如果原因值是FFT,则步长为5M,则携带频点个数为25个;如果原因值为rssi,则步长为3M，则携带频点个数为15个*/
    PHYITF_FREQ_MEASURE_BAND_INFO_STRU          stFreqBandInfo;         /* 当原因值为RSSI或者FFT时，需要携带band信息以及采样步长 */
    PHYITF_FREQ_LIST_STRU                       stFreqList;             /* 当原因值为PSCH,HISTORY_CAND_RSSI,HISTORY_CAND_PSCH时，需要携带需要做细扫的频点 */
}RRC_PHY_FREQ_MEASURE_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP上报的频点信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usFreq;
    VOS_UINT16                                          usFreqQuality;          /* 频点的RSSI值或者PSCH值，由于RSSI是负的，DSP上报的RSSI值是偏移65535得到的 */
    VOS_UINT16                                          usFreqBandNo;           /*频段号,取值:1,2,3,4,5,6，8*/
    VOS_UINT16                                          usReserve1;
} PHY_RRC_FREQ_INFO_STRU;



/*****************************************************************************
 结构名    : PHY_RRC_RANKED_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP上报的排好序的频点列表
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usFreqNum;              /* 频率数目 */
    VOS_UINT16                                          usReserve1;
    PHY_RRC_FREQ_INFO_STRU                              astFreqInfo[RRC_PHY_MAX_SAMPLE_FREQ_NUM_PER_BAND];
} PHY_RRC_MEAS_FREQ_INFO_STRU;



/*****************************************************************************
 结构名    : PHY_RRC_FREQ_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频点测量指示消息数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* 操作标识 */
    PHYITF_ANT_CHANGE_ENUM_UINT32               enAntChgFlg;            /* 天线是否发生了切换，RSSI搜索时有效 */
    PHYITF_RSLT_ENUM_UINT16                     enResult;               /* 有PI的小区搜索流程中DSP才赋值，默认填PHYITF_SUCC */
    PHYITF_FREQ_SEARCH_TYPE_ENUM_UINT16         enSearchType;           /* 指示DSP是通过RSSI,PSCH还是FFT对频点进行排序 */
    PHY_RRC_MEAS_FREQ_INFO_STRU                 stMeasFreqInfo;
}PHY_RRC_FREQ_MEASURE_IND_STRU;




/**************************小区搜索相关的配置**************************************************/
/*****************************************************************************
 结构名    : PHYITF_CELL_SEARCH_CANDIDATE_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区搜索中候补小区信息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;    /* 先验小区主扰码 */
    VOS_UINT16                          usReferenceTime;       /* 先验小区的时间信息 */

}PHYITF_CELL_SEARCH_CANDIDATE_CELL_INFO_STRU;


/*****************************************************************************
 结构名    : PHYITF_CELL_SEARCH_FREQ_BAND_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区搜索频段信息，指明这个频段的
             最低频率和最高频率
 *****************************************************************************/
typedef struct
{
    VOS_UINT16  usLowFreq;       /* 频段的最低频点 */
    VOS_UINT16  usHighFreq;      /* 频段的最高频点 */

}PHYITF_CELL_SEARCH_FREQ_BAND_INFO_STRU;


typedef struct
{
    VOS_UINT16                              usFreqCnt;                       /* 频率列表中频点的数目,为0则表示没有 */
    VOS_UINT16                              usReserve1;
    PHYITF_FREQ_INFO_STRU                   astFreqList[RRC_PHY_MAX_FREQ_NUM];/* 频率列表中具体的频点信息*/

}PHYITF_FREQ_INFO_LIST_STRU;


/*****************************************************************************
 结构名    : RRC_PHY_CELL_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区搜索请求消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* 操作标识 */
    PHYITF_CELL_SEARCH_TYPE_ENUM_UINT16         enCellSearchType;       /*枚举值，取自PHYITF_SEARCH_FLAG_ENUM*/  /* 初始小区搜索类型 */
    VOS_UINT16                                  usFreqInfo;             /* 初始小区搜索的频点,当enCellSearchType = PHYITF_CELL_SEARCH_NO_CAND_CELL或PHYITF_CELL_SEARCH_WITH_CAND_CELL时有效*/
    VOS_INT16                                   sRSCPThreshold;         /* 小区搜索过程中要求的RSCP最低门限 */
    VOS_UINT16                                  usCandidateCellNum;     /* 先验小区的数目,当enCellSearchType = PHYITF_CELL_SEARCH_WITH_CAND_CELL时有效*/
    PHYITF_CELL_SEARCH_CANDIDATE_CELL_INFO_STRU astCandidateCellInfo[RRC_PHY_MAX_CANDIDATE_CELL_NUM];
    PHYITF_CELL_SEARCH_FREQ_BAND_INFO_STRU      stFreqBand;             /*当enCellSearchType = PHYITF_CELL_SEARCH_FREQ_BAND时有效*/
    PHYITF_FREQ_INFO_LIST_STRU                  stFreqList;             /*当enCellSearchType = PHYITF_CELL_SEARCH_FREQ_LIST时有效*/
    VOS_UINT16                                  usTxRxFreqSeparation;   /*为实际频率值Freq乘5的结果*/
    VOS_UINT16                                  usFreqBandNo;           /*频段号,取值:1,2,3,4,5,6*/
    VOS_UINT16                                  usReportCellNumInd;    /*上报小区数目指示,1:只上报一个小区测量结果则可.2:要上报多个小区测量结果*/
    PHYITF_BOOL_ENUM_UINT16                     enHoFlg;                /* 切换目的的小区搜索指示 */
    PHYITF_BOOL_ENUM_UINT16                     enCsDetectFlg;          /* 指定小区搜索时，是否搜索检测小区 */
    VOS_UINT16                                  usDetectCellNum;        /* 搜索检测小区的个数 */
}RRC_PHY_CELL_SEARCH_REQ_STRU;



/*****************************************************************************
 结构名    : PHY_RRC_EACH_CELL_SEARCH_RESULT
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区搜索过程中每个小区的搜索结果数据结构

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;         /*小区主扰码*/
    VOS_INT16                           sCpichRscp;                 /* CPICH RSCP测量值 */
    VOS_INT16                           sCpichEcN0;                 /* CPICH EcN0测量值 */
    VOS_INT16                           sUtraCarrierRSSI;           /* UtraCarrierRSSI测量值 */

}PHY_RRC_EACH_CELL_SEARCH_RESULT;


/*****************************************************************************
 结构名    : PHY_RRC_CELL_SEARCH_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区搜索指示消息数据结构

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                              usOPID;                 /* 操作标识 */
    VOS_UINT16                              usFreqInfo;             /* 初始小区的频点 */
    VOS_UINT16                              usSerchedCellNum;       /*当在该频点一个小区都搜不到，则usSerchedCellNum = 0*/
    PHY_RRC_EACH_CELL_SEARCH_RESULT         astCellSerchResult[PHY_RRC_MAX_REPORT_CANDIDATE_CELL_NUM]; /* 小区的主扰码 */
    PHYITF_RSLT_ENUM_UINT16                 enResult;               /* 小区搜索结果，有PI的小区搜索流程中DSP才赋值，默认填PHYITF_SUCC */
    VOS_UINT16                              ausReserve1[1];
}PHY_RRC_CELL_SEARCH_IND_STRU;



/*****************************************************************************
 结构名    : RRC_PHY_PCCPCH_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PCCPCH 信道释放请求消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    PHYITF_BOOL_ENUM_UINT16             enBgSearchFlg;          /* 是否背景搜标志，如果是DSP需要做精确接收，
                                                                    PHYITF_VALID 表示需要做精确解广播，
                                                                    PHYITF_INVALID，表示不需要精确解广播 */
    VOS_UINT16                          usReserve1;
}RRC_PHY_PCCPCH_RELEASE_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_PCCPCH_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PCCPCH 信道释放证实消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

}PHY_RRC_PCCPCH_RELEASE_CNF_STRU;



/*****************************************************************************
 结构名    : RRC_PHY_PCCPCH_SETUP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PCCPCH 信道建立请求消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */
    VOS_UINT16                          usFreqInfo;             /* 频率信息 */

    VOS_UINT16                          usFreqBandNo;                           /* 频段号:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* 收发频差*/

    VOS_UINT16                          usPriScramCode;         /* 小区的主扰码 */

    /*Pccpch的分集方式: 0：不采用分集方式；1：采用STTD分集方式,
     0xFF:第一次建立Pccpch，RRC不知道Pccpch是否采用了分集方式,由物理层自己来判断.
     为了兼容6511版本,此值只能使用0,1.
     对于6720版本，此值可以使用0,1,0xFF*/
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enTDIndicator;
    PHYITF_BOOL_ENUM_UINT16             enBgSearchFlg;          /* 是否背景搜标志，如果是DSP需要做精确接收，
                                                                    PHYITF_VALID 表示需要做精确解广播，
                                                                    PHYITF_INVALID，表示不需要精确解广播 */
    PHYITF_PCCPCH_PURPOSE_ENUM_UINT16   enPccpchPurpose;        /* 本次解广播是不是只解SIB7消息 */
    VOS_UINT16                          usReserve1;

}RRC_PHY_PCCPCH_SETUP_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_PCCPCH_SETUP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PCCPCH 信道建立证实消息数据结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* 操作标识 */

}PHY_RRC_PCCPCH_SETUP_CNF_STRU;


typedef struct
{
    VOS_UINT16                      usPos;
    VOS_UINT16                      usRepeat;
} SYSINFO_POS_REPEAT_STRU;

/* CPHY_SYSINFO_POS_NOTIFY_REQ原语参数结构 */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16  enMsgID;                                        /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                  usOpID;
    PHYITF_BOOL_ENUM_UINT16     enRcvAllFlg;                                    /* 是否全解广播的标记 */
    VOS_UINT16                  ausReserve1[2];
    VOS_UINT16                  usSegNum;
    SYSINFO_POS_REPEAT_STRU     astSegList[RRC_PHY_MAX_SEG_POS_INFO_NUM];                                  /*接收位置数组*/
} RRC_PHY_SYSINFO_POS_NOTIFY_REQ_STRU;

/* CPHY_SYSINFO_POS_NOTIFY_CNF原语参数结构 */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                      enMsgID;                    /* 原语类型 *//*_H2ASN_Skip*/
    VOS_UINT16                                      usOPID;
    PHYITF_RSLT_ENUM_UINT16                         enResult;                   /* 成功还是失败的标志 */
    VOS_UINT16                                      usReserve1[1];
} PHY_RRC_SYSINFO_POS_NOTIFY_CNF_STRU;


/*****************************************************************************
 结构名    : PHY_RRC_BCCH_FAIL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于精确解广播过程中，WDSP给WAS上报无法进行精确解广播。
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* 原语类型 *//*_H2ASN_Skip*/
    PHYITF_PCCPCH_FAIL_TYPE_ENUM_UINT16 enFailType;         /* 广播失败原因 */
} PHY_RRC_BCCH_FAIL_IND_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_BG_SEARCH_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W背景搜W的时候，WAS通知WPHY停止背景搜
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                        enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                        usOPID;                 /* 操作标识 */
}RRC_PHY_BG_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_BG_SEARCH_SUSPEND_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W背景搜W的时候，WAS通知WPHY暂停背景搜
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                        enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                        usOPID;                 /* 操作标识 */
}RRC_PHY_BG_SEARCH_SUSPEND_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_BG_SEARCH_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY对RRC_PHY_BG_SEARCH_STOP_REQ消息的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOPID;                 /* 操作标识 */
    PHYITF_BG_RESULT_TYPE_ENUM_UINT16        usResult;               /* 搜索结果 */
    VOS_UINT16                               usReserve1;
}PHY_RRC_BG_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_BG_SEARCH_SUSPEND_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY对RRC_PHY_BG_SEARCH_SUSPEND_REQ消息的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOPID;                 /* 操作标识 */
    PHYITF_BG_RESULT_TYPE_ENUM_UINT16        usResult;               /* 搜索结果 */
    VOS_UINT16                               usReserve1;
}PHY_RRC_BG_SEARCH_SUSPEND_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PHY_BG_SEARCH_RESUME_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W背景搜W的时候，WAS通知WPHY解挂背景搜
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                        enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                        usOPID;                 /* 操作标识 */
}RRC_PHY_BG_SEARCH_RESUME_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RRC_BG_SEARCH_RESUME_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WPHY对RRC_PHY_BG_SEARCH_RESUME_REQ消息的响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOPID;                 /* 操作标识 */
    PHYITF_BG_RESULT_TYPE_ENUM_UINT16        usResult;               /* 搜索结果 */
    VOS_UINT16                               usReserve1;
}PHY_RRC_BG_SEARCH_RESUME_CNF_STRU;

/****************PCCPCH 来的BCCH上的数据**********************************/
/*****************************************************************************
 结构名    : PHY_RRC_BCCH_DATA_ADD_SFN_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : BCCH DATA 指示消息数据结构
             从PCCPCH 来的系统消息使用此
             消息传输

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* 原语类型 *//*_H2ASN_Skip*/
    VOS_INT16                           sCRCFlg;            /* CRC结果 */
    VOS_UINT16                          usServSfn;          /* 主小区的sfn值*/
    VOS_UINT16                          usReserve;
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucBcchData[RRC_PHY_BCCH_DATA_SIZE]; /* 一个TB的BCCH数据 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausBcchData[RRC_PHY_BCCH_DATA_SIZE/2]; /* _H2ASN_Skip  一个TB的BCCH数据 */
#endif

} PHY_RRC_BCCH_DATA_ADD_SFN_IND_STRU;


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

#endif /* end of RrcPhyInterface.h */

