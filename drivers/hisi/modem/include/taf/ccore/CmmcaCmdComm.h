/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaCmdComm.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年1月7日
  最近修改   :
  功能描述   : Cmmca 模块Cmd相关的公共数据结构定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月7日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CMMCACMDCOMM_H__
#define __CMMCACMDCOMM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CMMCA_MMC_RAT_API_BASE                              (0x0400)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名   : CMMCA_MMC_RAT_CMD_ID_ENUM
 枚举说明 : MMC与RAT之间的CMD定义
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_MMC_RAT_CMD_ID_ENUM
{
    ID_CMMCA_MMC_RAT_OTHER_RAT_INFO_IND                     = 0x0018,

    ID_CMMCA_MMC_RAT_POWERUP_REQ                            = CMMCA_MMC_RAT_API_BASE,
    ID_CMMCA_MMC_RAT_POWERDOWN_REQ,
    ID_CMMCA_MMC_RAT_RAT_ONLY_MODE_REQ,
    ID_CMMCA_MMC_RAT_RAT_3GPP_MODE_REQ,
    ID_CMMCA_MMC_RAT_ACQ_REQ,
    ID_CMMCA_MMC_RAT_MCC_SEARCH_REQ,
    ID_CMMCA_MMC_RAT_PS_REG_REQ,
    ID_CMMCA_MMC_RAT_NO_SERVICE_REQ,
    ID_CMMCA_MMC_RAT_CELL_GLOBAL_ID_RSP,
    ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ,
    ID_CMMCA_MMC_RAT_DEFAULT_BEARER_REQ,
    ID_CMMCA_MMC_RAT_DEDICATED_BEARER_REQ,
    ID_CMMCA_MMC_RAT_BEARER_DISCONNECT_REQ,
    ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ,
    ID_CMMCA_MMC_RAT_IRAT_MEAS_IND,
    ID_CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP,
    ID_CMMCA_MMC_RAT_IRAT_SIB8_MEAS_IND,
    ID_CMMCA_MMC_RAT_RAT_MEAS_CMD,
    ID_CMMCA_MMC_RAT_RAT_RESELMEAS_CMD,
    ID_CMMCA_MMC_RAT_STOP_IRAT_RATMEAS_CMD,
    ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ,
    ID_CMMCA_MMC_RAT_CDMA_TXPWR_RSP,

    ID_CMMCA_MMC_RAT_IRAT_RESELMEAS_IND,
    ID_CMMCA_MMC_RAT_IRAT_HANDOVER_RSP,                         /* ignore */
    ID_CMMCA_MMC_RAT_RAT_HANDOVER_PS_REG_REQ,                   /* ignore */
    ID_CMMCA_MMC_RAT_SET_IDLEMODEMOBILITYINFO,

    ID_CMMCA_MMC_RAT_PACKET_STATISTICS_RSP,
    ID_CMMCA_MMC_RAT_PDN_TABLE_SETUP_REQ,
    ID_CMMCA_MMC_RAT_RAT_MODE_REQ,
    ID_CMMCA_MMC_API_SET_PDN_PCO_AUTH_REQ,

    ID_CMMCA_MMC_RAT_CMD_MAX,

    ID_CMMCA_RCM_TAS_CDMA_MEASUREMENT_IND                   = CMMCA_MMC_RAT_API_BASE + 0x60,
    ID_CMMCA_RCM_TAS_CDMA_EVENT_IND,
    ID_CMMCA_MTC_CONN_STATE_INFO_IND,

    ID_CMMCA_RAT_MMC_POWERUP_RSP                            = CMMCA_MMC_RAT_API_BASE + 0x80,
    ID_CMMCA_RAT_MMC_POWERDOWN_RSP,
    ID_CMMCA_RAT_MMC_CMD_REJ_IND,
    ID_CMMCA_RAT_MMC_RAT_ONLY_MODE_RSP,
    ID_CMMCA_RAT_MMC_RAT_3GPP_MODE_RSP,
    ID_CMMCA_RAT_MMC_ACQ_RSP,
    ID_CMMCA_RAT_MMC_MCC_SEARCH_RSP,
    ID_CMMCA_RAT_MMC_PS_REG_RSP,
    ID_CMMCA_RAT_MMC_NO_SERVICE_RSP,
    ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND,
    ID_CMMCA_RAT_MMC_CELL_GLOBAL_ID_REQ,
    ID_CMMCA_RAT_MMC_DATACONNECTION_CMD_RSP,
    ID_CMMCA_RAT_MMC_DEFAULTBEARER_RSP,
    ID_CMMCA_RAT_MMC_DEDICATEDBEARER_IND,
    ID_CMMCA_RAT_MMC_DEDICATEDBEARER_RSP,
    ID_CMMCA_RAT_MMC_BEARER_DISCONNECT_RSP,
    ID_CMMCA_RAT_MMC_BEARER_DISCONNECT_IND,
    ID_CMMCA_RAT_MMC_BEARER_DETACH_RSP,
    ID_CMMCA_RAT_MMC_IRAT_MEAS_CMD,
    ID_CMMCA_RAT_MMC_IRAT_SYSTEM_CHG_REQ,
    ID_CMMCA_RAT_MMC_IRAT_SIB8_MEAS_CMD,
    ID_CMMCA_RAT_MMC_RAT_MEAS_IND,
    ID_CMMCA_RAT_MMC_RAT_RESELMEAS_IND,
    ID_CMMCA_RAT_MMC_STOP_IRAT_MEAS_CMD,
    ID_CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP,
    ID_CMMCA_RAT_MMC_CDMA_TXPWR_REQ,

    ID_CMMCA_RAT_MMC_RAT_HANDOVER_PS_REG_RSP,
    ID_CMMCA_RAT_MMC_IRAT_HANDOVER_REQ,
    ID_CMMCA_RAT_MMC_IRAT_RESELMEAS_CMD,
    ID_CMMCA_RAT_MMC_SET_IDLEMODEMOBILITYINFO,

    ID_CMMCA_RAT_MMC_PACKET_STATISTICS_REQ,
    ID_CMMCA_RAT_MMC_PDN_TABLE_SETUP_RSP,
    ID_CMMCA_RAT_MMC_RAT_MODE_RSP,
    ID_CMMCA_RAT_MMC_SYSTEM_CHG_ABORT_REQ,
    ID_CMMCA_RAT_MMC_SET_PDN_PCO_AUTH_RSP,
    ID_CMMCA_RAT_MMC_LOOKBACK_TEST_REQ                      = CMMCA_MMC_RAT_API_BASE + 0xcc,
    ID_CMMCA_RAT_MMC_CMD_MAX
};

typedef VOS_UINT16 CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名   :CMMCA_MMC_RAT_ID_ENUM
 枚举说明 :RAT ID
 1.日    期   : 2014年01月27日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_MMC_RAT_ID_ENUM
{
    CMMCA_MMC_RAT_ID_NULL,
    CMMCA_MMC_RAT_ID_CDMA2K1X           = 2,                                    /* 1X */
    CMMCA_MMC_RAT_ID_GERAN,                                                     /* GSM */
    CMMCA_MMC_RAT_ID_CDMA2KHRPD,                                                /* DO */
    CMMCA_MMC_RAT_ID_UTRAN,                                                     /* 3GPP */
    CMMCA_MMC_RAT_ID_CDMA2KAI,                                                  /* 1X&DO, for matching type MMSS_SYS_CDMA2000_AI */
    CMMCA_MMC_RAT_ID_EUTRAN             = 9,                                    /* LTE */
    CMMCA_MMC_RAT_ID_3GPPAI,                                                    /* GSM&UMTS&LTE, for matching type MMSS_SYS_3GPP_AI */
    CMMCA_MMC_RAT_ID_BUTT
};
typedef VOS_UINT8 CMMCA_MMC_RAT_ID_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : CMMCA_MMC_RAT_CMD_DATA_STRU
 结构说明  : CMMCA收发的码流格式
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId;
    VOS_UINT8                           aucParamBlk[1];
}CMMCA_MMC_RAT_CMD_DATA_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CmmcaCmdComm.h */
