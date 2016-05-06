/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TtfErrlog.h
  版 本 号   : 初稿
  作    者   : t00148005
  生成日期   : 2013年9月23日
  最近修改   :
  功能描述   : TtfErrlog.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年9月23日
    作    者   : t00148005
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TTFERRLOG_H__
#define __TTFERRLOG_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "omnvinterface.h"
#include "omringbuffer.h"
#include "omerrorlog.h"
#include "TTFComm.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 枚举定义
*****************************************************************************/
enum TTF_MODULE_ID_ENUM
{
    MODULE_ID_PDCP = 0,
    MODULE_ID_WRM,
    MODULE_ID_GRM,
    MODULE_ID_LLC,
    MODULE_ID_SN,
    MODULE_ID_DL,
    MODULE_ID_BUTT
};

enum TTF_ERR_LOG_RPT_STATUS_ENUM
{
    TTF_ERR_LOG_RPT_CLOSE = 0,
    TTF_ERR_LOG_RPT_OPEN,
    TTF_ERR_LOG_RPT_BUTT
};

typedef VOS_UINT8 TTF_MODULE_ID_ENUM_UINT8;


enum TTF_ERR_LOG_ALM_ID_ENUM
{
    TTF_ERR_LOG_ALM_ID_WRLC_RESET = 1,
    TTF_ERR_LOG_ALM_ID_WRLC_LI_ERR,
    TTF_ERR_LOG_ALM_ID_WRLC_TFCI_FAIL,
    TTF_ERR_LOG_ALM_ID_TTF_MEM_FAIL,
    TTF_ERR_LOG_ALM_ID_GPRS_TBF_ABNML,
    TTF_ERR_LOG_ALM_ID_GLLC_CRC_ERR,
    TTF_ERR_LOG_ALM_ID_GSM_MDL_ERR,
    TTF_ERR_LOG_ALM_ID_WCDMA_COMM_INFO,
    TTF_ERR_LOG_ALM_ID_GSM_COMM_INFO,

    TTF_ERR_LOG_ALM_ID_BUTT
};

typedef VOS_UINT8 TTF_ERR_LOG_ALM_ID_ENUM_UINT8;

enum TTF_ERR_LOG_ALM_LEV_ENUM
{
    TTF_ERR_LOG_ALM_LEV_CRITICAL = 0,
    TTF_ERR_LOG_ALM_LEV_MAJOR,
    TTF_ERR_LOG_ALM_LEV_MINOR,
    TTF_ERR_LOG_ALM_LEV_WARNING,
    TTF_ERR_LOG_ALM_LEV_BUTT,
};

typedef VOS_UINT8 TTF_ERR_LOG_ALM_LEV_ENUM_UINT8;

enum TTF_MNTN_ERR_LOG_WRLC_RESET_TYPE
{
    TTF_MNTN_ERR_LOG_WRLC_RESET_RCV_ERR_STATUS_REPORT,
    TTF_MNTN_ERR_LOG_WRLC_RESET_RCV_RESET_PDU,
    TTF_MNTN_ERR_LOG_WRLC_RESET_TX_DATA_REACH_MST,
    TTF_MNTN_ERR_LOG_WRLC_RESET_TX_MRW_REACH_MST,
    TTF_MNTN_ERR_LOG_WRLC_RESET_BUTT
};
typedef VOS_UINT8 TTF_MNTN_ERR_LOG_WRLC_RESET_TYPE_ENUM_UINT8;

enum TTF_MNTN_ERR_LOG_LI_ERR_TYPE
{
    TTF_MNTN_ERR_LOG_LI_1ST,                /* judge from Li, the Sdu should be the the 1st Sdu in the Pdu,but actually not */
    TTF_MNTN_ERR_LOG_LI_LAST,               /* judge from Li, the Sdu should be the the last Sdu in the Pdu,but actually not */
    TTF_MNTN_ERR_LOG_LI_HEAD,               /* judge from Li, the Sdu should be the the lst or 2nd Sdu in the Pdu,but actually not */
    TTF_MNTN_ERR_LOG_LI_RSV,                /* use the Li not support */
    TTF_MNTN_ERR_LOG_LI_TOO_SHORT,
    TTF_MNTN_ERR_LOG_LI_TOO_LONG,
    TTF_MNTN_ERR_LOG_LI_OFFSET_ERR,         /* pre Li > this Li */
    TTF_MNTN_ERR_LOG_LI_PADDING,            /* padding LI but not the last LI */
    TTF_MNTN_ERR_LOG_LI_BUTT
};
typedef VOS_UINT8  TTF_MNTN_ERR_LOG_LI_ERR_TYPE_ENUM8;

enum TTF_MNTN_ERR_LOG_TFC_ERR_TYPE
{
    TTF_MNTN_ERR_LOG_TFC_ERR_NO_CHOICE,
    TTF_MNTN_ERR_LOG_TFC_ERR_NO_LOCH_LABEL,
    TTF_MNTN_ERR_LOG_TFC_ERR_BUTT
};
typedef VOS_UINT8 TTF_MNTN_ERR_LOG_TFC_ERR_NO_CHOICE_ENUM8;

enum TTF_MNTN_ERR_LOG_MAC_TYPE
{
    TTF_MNTN_ERR_LOG_MAC_R99 = 0,
    TTF_MNTN_ERR_LOG_MAC_UPA,
    TTF_MNTN_ERR_LOG_MAC_DPA,

    TTF_MNTN_ERR_LOG_MAC_TYPE_BUTT
};
typedef VOS_UINT8 TTF_MNTN_ERR_LOG_MAC_TYPE_ENUM8;

enum TTF_MNTN_GSM_CODE_SCHEME_ENUM
{
    TTF_MNTN_GSM_CODE_SCHEME_CS_1                   = 0x0000,
    TTF_MNTN_GSM_CODE_SCHEME_CS_2                   = 0x0001,
    TTF_MNTN_GSM_CODE_SCHEME_CS_3                   = 0x0002,
    TTF_MNTN_GSM_CODE_SCHEME_CS_4                   = 0x0003,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_1                  = 0x1000,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_2                  = 0x1001,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_3                  = 0x1002,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_4                  = 0x1003,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_5                  = 0x1004,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_6                  = 0x1005,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_7                  = 0x1006,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_8                  = 0x1007,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_9                  = 0x1008,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_5_7                = 0x1009,
    TTF_MNTN_GSM_CODE_SCHEME_MCS_6_9                = 0x100a,

    TTF_MNTN_GSM_CODE_SCHEME_BUTT
};
typedef VOS_UINT16 TTF_MNTN_GSM_CODE_SCHEME_ENUM_UINT16;

enum TTF_MNTN_GSM_TBF_MODE_ENUM
{
    TTF_MNTN_GSM_TBF_MODE_GPRS = 0,
    TTF_MNTN_GSM_TBF_MODE_EGPRS,
    TTF_MNTN_GSM_TBF_MODE_NULL
};
typedef VOS_UINT8 TTF_MNTN_GSM_TBF_MODE_ENUM_UINT8;

/*****************************************************************************
  3 宏定义
*****************************************************************************/
/*  提供的SAPI个数，不支持TOM  */
#define LL_SAPI_NUMBER                              (6)
#define LL_INVALID_LLE_INDEX                        (6)
#define LL_MAX_SAPI_VALUE                           (11)

#define TTF_ARRAY_SIZE(x)                           (sizeof(x) / sizeof(x[0]))

#if (FEATURE_PTM == FEATURE_OFF)
#define TTF_MNTN_InitErrLogEnt(ulPid)    (VOS_OK)
#define GTTF_MNTN_ErrlogTbfAbnmlEvt(ulPid, usType)
#define GTTF_MNTN_ErrlogLlCrcErrEvt(ucSapi, pFcsData)
#define GTTF_MNTN_ErrlogMdlErrEvt(ulPid, pstMdlErr)
#define TTF_MNTN_ErrlogTtfMemAllocFail(ulPid, ucPoolId, usFileId,  usLine,  ulAllocFailCnt)
#define WTTF_MNTN_ErrlogRlcResetEvt(ulPid, ucRbId, enResetType)
#define WTTF_MNTN_ErrlogRlcLiErrEvt(ulPid, ucRbId, enLiErrType)
#define WTTF_MNTN_ErrlogTfciFailEvt(ulPid, ucMacState, enType)
#else
#define TTF_ERR_LOG_BUF_SIZE                            (2 * 1024)
#define TTF_ERR_SEM_TIMEOUT_LEN                         (5000)
#define TTF_ERR_LOG_RCD_MEM_CNT                         (20)

#define TTF_ERR_LOG_ENT_STATE_GET(modemId)                      (g_stTtfMntnErrlogEnt.aulState[modemId])
#define TTF_ERR_LOG_ENT_BUF_GET(modemId)                        (g_stTtfMntnErrlogEnt.pRingMem[modemId])
#define TTF_ERR_LOG_ENT_RINGID_GET(modemId)                     (g_stTtfMntnErrlogEnt.pRingBuffer[modemId].pRingId)
#define TTF_ERR_LOG_ENT_BUFFER_OVER_CNT_GET(modemId)            (g_stTtfMntnErrlogEnt.pRingBuffer[modemId].usBufferOverCounter)
#define TTF_ERR_LOG_ENT_SEM_GET(modemId)                        (g_stTtfMntnErrlogEnt.ulSaveLogSem[modemId])
#define TTF_ERR_LOG_ENT_WCDMA_COMM_INFO_GET(modemId)            (g_stTtfMntnErrlogEnt.pstTtfMntnWcdmaCommInfo[modemId])
#define TTF_ERR_LOG_ENT_GSM_COMM_INFO_GET(modemId)              (g_stTtfMntnErrlogEnt.pstTtfMntnGsmCommInfo[modemId])

#define TTF_ERR_LOG_ENT_STATE_SET(modemId, x)                   (g_stTtfMntnErrlogEnt.aulState[modemId] = (x))
#define TTF_ERR_LOG_ENT_BUF_SET(modemId, x)                     (g_stTtfMntnErrlogEnt.pRingMem[modemId] = (x))
#define TTF_ERR_LOG_ENT_RINGID_SET(modemId, x)                  (g_stTtfMntnErrlogEnt.pRingBuffer[modemId].pRingId = (x))
#define TTF_ERR_LOG_ENT_BUFFER_OVER_CNT_SET(modemId, x)         (g_stTtfMntnErrlogEnt.pRingBuffer[modemId].usBufferOverCounter = (x))
#define TTF_ERR_LOG_ENT_UPDT_BUFFER_OVER_CNT(modemId, x)        (g_stTtfMntnErrlogEnt.pRingBuffer[modemId].usBufferOverCounter += (x))
#define TTF_ERR_LOG_ENT_SEM_SET(modemId, x)                     (g_stTtfMntnErrlogEnt.ulSaveLogSem[modemId] = (x))

#define TTF_ERR_LOG_ENT_UPDT_BUF_RSV_LEN(modemId, x)            (g_stTtfMntnErrlogEnt.ulBufRsvLen[modemId] += (x))
#define TTF_ERR_LOG_ENT_RST_BUF_RSV_LEN(modemId)                (g_stTtfMntnErrlogEnt.ulBufRsvLen[modemId] = (0))
#define TTF_ERR_LOG_ENT_GET_BUF_RSV_LEN(modemId)                (g_stTtfMntnErrlogEnt.ulBufRsvLen[modemId])

#define TTF_ERR_LOG_NEED_RPT_LEV(enModemId, lev) \
        ((OM_APP_STATUS_OPEN == g_stTtfMntnErrlogEnt.stCtrlInfo[enModemId].ucAlmStatus) \
        && (lev <= g_stTtfMntnErrlogEnt.stCtrlInfo[enModemId].ucAlmLevel))

#define TTF_ERR_LOG_ENT_CTRL_STATUS_SET(enModemId, status) \
        (g_stTtfMntnErrlogEnt.stCtrlInfo[enModemId].ucAlmStatus = (status))

#define TTF_ERR_LOG_ENT_CTRL_LEV_SET(enModemId, lev) \
        (g_stTtfMntnErrlogEnt.stCtrlInfo[enModemId].ucAlmLevel = (lev))

#define TTF_ERR_LOG_ENT_CTRL_STATUS_GET(enModemId) \
        (g_stTtfMntnErrlogEnt.stCtrlInfo[enModemId].ucAlmStatus)

#define TTF_ERR_LOG_ENT_CTRL_LEV_GET(enModemId) \
        (g_stTtfMntnErrlogEnt.stCtrlInfo[enModemId].ucAlmLevel)

#define TTF_ERR_LOG_RPT_CB_SET(modemId, moduleId, cb)   (apErrLogRptCb[modemId][moduleId] = (cb))
#define TTF_ERR_LOG_RPT_CB_GET(modemId, moduleId)       (apErrLogRptCb[modemId][moduleId])
#define TTF_ERR_LOG_GET_ALM_LEV(AlmId)                  (g_aucTtfErrlogAlmLevTbl[AlmId])


/* 0表示通信故障，TTF整个属于通信模块，只显示通信故障 */
#define TTF_ERR_LOG_ALM_TYPE_COMUNICATION             (0)

#define TTF_ERR_LOG_FILL_HEADER(pstHeader, ModemId, AlmId, AlmLev, ulLen) \
{ \
    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_GUL2; \
    (pstHeader)->usModemId         = (VOS_UINT16)ModemId; \
    (pstHeader)->usAlmId           = AlmId; \
    (pstHeader)->usAlmLevel        = AlmLev; \
    (pstHeader)->usAlmType         = TTF_ERR_LOG_ALM_TYPE_COMUNICATION; \
    (pstHeader)->usAlmLowSlice     = mdrv_timer_get_normal_timestamp(); \
    (pstHeader)->usAlmHighSlice    = 0; \
    (pstHeader)->ulAlmLength       = ulLen; \
}


#define TTF_ERR_LOG_GET_LLC_CRC_ERR_INFO(ucSapi)    &g_stErrlogLlcCrcErrCtx.astLlCrcErrInfo[ucSapi]
#define TTF_ERR_LOG_UPDT_LLC_CRC_ERR_SAPI(ucSapi) \
{\
    g_stErrlogLlcCrcErrCtx.aucCrcErrSapi[g_stErrlogLlcCrcErrCtx.ucCrcErrCnt] = ucSapi; \
    g_stErrlogLlcCrcErrCtx.ucCrcErrCnt++; \
}

#define TTF_ERR_LOG_GET_SAPI_CRC_ERR_CNT()          g_stErrlogLlcCrcErrCtx.ucCrcErrCnt
#define TTF_ERR_LOG_GET_SAPI_BY_INDX(ucIndx)        g_stErrlogLlcCrcErrCtx.aucCrcErrSapi[ucIndx]

#define TTF_ERR_LOG_RST_LLC_CRC_ERR_CTX_INFO()      PS_MEM_SET(&g_stErrlogLlcCrcErrCtx, 0, sizeof(TTF_MNTN_ERR_LOG_GLLC_CRC_ERR_CTX_STRU))

#define TTF_ERR_LOG_LL_IS_DUMMY_BLOCK(data)         (0 == ((data[0]^data[1]) | (data[1]^data[2])))

#define UTRAN_MAX_RB_ID                             (33)
#define UTRAN_MAX_RB_NUM                            (UTRAN_MAX_RB_ID + 1)

#define TTF_ERR_LOG_CB_SHOW(enModemId, ulModuleId) \
    vos_printf("Modem:%d            %s      cb:0x%x \r\n", enModemId, #ulModuleId, apErrLogRptCb[enModemId][ulModuleId])

#define TTF_ERR_LOG_COMM_INFO_CNT                   (8)     /* 这里限定必须是2的n次方 */
#define TTF_ERR_LOG_UL_SCHED_INFO_CNT               (64)    /* 这里限定必须是2的n次方 */

/* mod必须是2的N次方 */
#define TTF_ERR_LOG_COMM_COUNTER_INCR(seq, mod)     ((seq) = (((seq) + 1) & (mod - 1)))

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
typedef struct
{
    OM_RING_ID                   pRingId;

    VOS_UINT16                   usBufferOverCounter;   /* Ring Buffre 溢出计数 */
    VOS_UINT16                   usRsv;
}RING_BUFFER_MANAGEMENT_STRU;

typedef struct
{
    VOS_UINT16              usAllocFileId;
    VOS_UINT16              usAllocLine;
    VOS_UINT16              usTraceFileId;
    VOS_UINT16              usTraceLine;
}TTF_MNTN_ERR_LOG_MEM_ALLOC_INFO_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU  stHeader;
    VOS_UINT8               ucPoolId;
    VOS_UINT8               aucRsv[3];
    VOS_UINT16              usFileId;
    VOS_UINT16              usLine;
    VOS_UINT32              ulAllocFailCnt;
    TTF_MNTN_ERR_LOG_MEM_ALLOC_INFO_STRU astAllocInfo[TTF_ERR_LOG_RCD_MEM_CNT];
}TTF_MNTN_ERR_LOG_MEM_ALLOC_FAIL_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU  stHeader;
    VOS_UINT16              usAbnmlType;
    VOS_UINT8               aucRsv[2];
}TTF_MNTN_ERR_LOG_GRLC_TBF_ABNML_STRU;

typedef struct
{
    VOS_UINT8               ucSapi;
    VOS_UINT8               aucRsv[3];
    VOS_UINT32              ulLstUpdtTs;
    VOS_UINT32              ulCrcErrCnt;
}TTF_MNTN_GLLC_CRC_ERR_INFO_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU  stHeader;
    TTF_MNTN_GLLC_CRC_ERR_INFO_STRU stLlcCrcErrInfo;
}TTF_MNTN_ERR_LOG_GLLC_CRC_ERR_STRU;

typedef struct
{
    VOS_UINT8               ucSapi;
    VOS_UINT8               ucChanType;
    VOS_UINT8               ucErrCause;
    VOS_UINT8               ucRsv;
}TTF_MNTN_GDL_MDL_ERR_INFO_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU          stHeader;
    TTF_MNTN_GDL_MDL_ERR_INFO_STRU  stDlMdlErrInfo;
}TTF_MNTN_ERR_LOG_GDL_MDL_ERR_STRU;

typedef struct
{
    VOS_UINT8                           aucCrcErrSapi[LL_SAPI_NUMBER];
    VOS_UINT8                           aucRsv1[2];
    TTF_MNTN_ERR_LOG_GLLC_CRC_ERR_STRU  astLlCrcErrInfo[LL_SAPI_NUMBER];
    VOS_UINT8                           ucCrcErrCnt;
    VOS_UINT8                           aucRsv2[3];
}TTF_MNTN_ERR_LOG_GLLC_CRC_ERR_CTX_STRU;


typedef VOS_VOID (*TTF_MNTN_ERR_LOG_RPT_CB)(VOS_VOID);

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;
    TTF_MNTN_ERR_LOG_WRLC_RESET_TYPE_ENUM_UINT8     enResetType;
    VOS_UINT8                                       ucRbId;
    VOS_UINT16                                      usResetCnt;
}TTF_MNTN_ERR_LOG_WRLC_RESET_STRU;

typedef struct
{
    VOS_UINT32                                      ulLstUpdtTs;
    VOS_UINT8                                       ucRbId;
    TTF_MNTN_ERR_LOG_LI_ERR_TYPE_ENUM8              enType;
    VOS_UINT8                                       aucRsv[2];
    VOS_UINT32                                      ulLiErrCnt;
}TTF_MNTN_WRLC_LI_ERR_INFO_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU          stHeader;
    TTF_MNTN_WRLC_LI_ERR_INFO_STRU  stLiErrInfo;
}TTF_MNTN_ERR_LOG_WRLC_LI_ERR_STRU;

typedef struct
{
    TTF_MNTN_ERR_LOG_WRLC_LI_ERR_STRU   astWrlcLiErrInfo[UTRAN_MAX_RB_NUM];
    VOS_UINT8                           aucLiErrRbs[UTRAN_MAX_RB_NUM];
    VOS_UINT8                           ucLiErrRbCnt;
    VOS_UINT8                           aucRsv;
}TTF_MNTN_ERR_LOG_WRLC_LI_ERR_CTX_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    VOS_UINT8                                   ucMacState;
    TTF_MNTN_ERR_LOG_TFC_ERR_NO_CHOICE_ENUM8    enType;
    VOS_UINT8                                   aucRsv[2];
}WTTF_MNTN_TFCI_FAIL_STRU;

/* 基本信息 */
typedef struct
{
    VOS_UINT16                                  usMacPduDataBufHeadIdx;
    VOS_UINT16                                  usMacPduDataBufTailIdx;
    VOS_UINT32                                  ulUpaSchedSize;     /* bit */
    VOS_UINT32                                  ulBO;               /* bit */

    VOS_UINT32                                  ulSlice;
}WTTF_UL_SCHED_INFO_STRU;

typedef struct
{
    TTF_MNTN_ERR_LOG_MAC_TYPE_ENUM8             enMacType;
    VOS_UINT8                                   ucTti;
    VOS_UINT8                                   ucUlDchId;
    VOS_UINT8                                   aucRsv[1];

    VOS_UINT16                                  usRlcSize;
    VOS_UINT16                                  usTbCnt;

    VOS_UINT32                                  ulSlice;
}WTTF_MAC_UL_INFO_STRU;

typedef struct
{
    TTF_MNTN_ERR_LOG_MAC_TYPE_ENUM8             enMacType;
    VOS_UINT8                                   ucTti;
    VOS_UINT8                                   ucDlDchId;
    VOS_UINT8                                   aucRsv[1];

    VOS_UINT16                                  usRlcSize;
    VOS_UINT16                                  usTbCnt;

    VOS_UINT32                                  ulSlice;
}WTTF_MAC_DL_INFO_STRU;

typedef struct
{
    TTF_MNTN_GSM_CODE_SCHEME_ENUM_UINT16        enCodeScheme;
    TTF_MNTN_GSM_TBF_MODE_ENUM_UINT8            enTbfMode;
    VOS_UINT8                                   ucTsMask;

    VOS_UINT32                                  ulSlice;
}GTTF_UL_INFO_STRU;

typedef struct
{
    TTF_MNTN_GSM_CODE_SCHEME_ENUM_UINT16        enCodeScheme;
    TTF_MNTN_GSM_TBF_MODE_ENUM_UINT8            enTbfMode;
    VOS_UINT8                                   ucTsMask;

    VOS_UINT32                                  ulSlice;
}GTTF_DL_INFO_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;

    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   ucLochLabel;
    VOS_UINT8                                   ucUpaTti;
    VOS_UINT8                                   ucWMacUlIndex;

    VOS_UINT8                                   ucWUlSchedIndex;
    VOS_UINT8                                   ucWMacDlIndex;
    VOS_UINT16                                  usRingBufferOverCounter;    /* Ring Buffre 溢出计数 */

    WTTF_MAC_UL_INFO_STRU                       astWttfMacUlInfo[TTF_ERR_LOG_COMM_INFO_CNT];
    WTTF_UL_SCHED_INFO_STRU                     astWttfUlSchedInfo[TTF_ERR_LOG_UL_SCHED_INFO_CNT];

    WTTF_MAC_DL_INFO_STRU                       astWttfMacDlInfo[TTF_ERR_LOG_COMM_INFO_CNT];
}TTF_MNTN_WCDMA_COMM_INFO_STRU;

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;

    VOS_UINT8                                   ucGUlIndex;
    VOS_UINT8                                   ucGDlIndex;
    VOS_UINT16                                  usRingBufferOverCounter;    /* Ring Buffre 溢出计数 */

    GTTF_UL_INFO_STRU                           astGttfUlInfo[TTF_ERR_LOG_COMM_INFO_CNT];
    GTTF_DL_INFO_STRU                           astGttfDlInfo[TTF_ERR_LOG_COMM_INFO_CNT];
}TTF_MNTN_GSM_COMM_INFO_STRU;

typedef struct
{
    VOS_UINT32                              aulState[MODEM_ID_BUTT];
    NV_ID_ERR_LOG_CTRL_INFO_STRU            stCtrlInfo[MODEM_ID_BUTT];
    RING_BUFFER_MANAGEMENT_STRU             pRingBuffer[MODEM_ID_BUTT];
    VOS_UINT32                              ulBufRsvLen[MODEM_ID_BUTT];
    VOS_SEM                                 ulSaveLogSem[MODEM_ID_BUTT];
    VOS_UINT8                              *pRingMem[MODEM_ID_BUTT];
    TTF_MNTN_WCDMA_COMM_INFO_STRU          *pstTtfMntnWcdmaCommInfo[MODEM_ID_BUTT];
    TTF_MNTN_GSM_COMM_INFO_STRU            *pstTtfMntnGsmCommInfo[MODEM_ID_BUTT];
}TTF_MNTN_ERR_LOG_ENT_STRU;

typedef struct
{
    VOS_UINT32                                  ulPid;
    VOS_UINT32                                  ulModuleId;
}TTF_MNTN_ERR_LOG_PID_MODULE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern VOS_UINT8                        g_aucTtfErrlogAlmLevTbl[TTF_ERR_LOG_ALM_ID_BUTT];
extern TTF_MNTN_ERR_LOG_ENT_STRU        g_stTtfMntnErrlogEnt;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 TTF_MNTN_InitErrLogEnt(VOS_UINT32 ulPid);
extern VOS_VOID   TTF_MNTN_ErrlogCbReg(VOS_UINT32 ulPid, TTF_MNTN_ERR_LOG_RPT_CB pErrlogCb);
extern VOS_VOID   TTF_MNTN_ErrlogCbRun(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID   TTF_MNTN_ErrlogBufPut(VOS_UINT32 ulPid,  VOS_CHAR *pBuffer, VOS_UINT32 ulBytes);
extern VOS_UINT32 TTF_MNTN_ErrLogRcvCtrlInd(MsgBlock *pstMsg, void *p);
extern VOS_UINT32 TTF_MNTN_ErrLogRcvRptReq(MsgBlock *pstMsg, void *p);
extern VOS_VOID   TTF_MNTN_ErrlogBufGet(VOS_UINT32 ulPid, MODEM_ID_ENUM_UINT16  enModemId, VOS_CHAR *pBuffer, VOS_UINT32 ulBytes);
extern VOS_VOID   GTTF_MNTN_ErrlogLlCrcErrEvt(VOS_UINT8 ucSapi, VOS_UINT8 *pData);
extern VOS_VOID   GTTF_MNTN_ErrlogMdlErrEvt(VOS_UINT32 ulPid, VOS_VOID *pMdlErr);
extern VOS_VOID   TTF_MNTN_ErrlogTtfMemAllocFail(VOS_UINT32 ulPid, VOS_UINT8 ucPoolId,
        VOS_UINT16 usFileId, VOS_UINT16 usLine, VOS_UINT32 ulAllocFailCnt);
extern VOS_VOID   GTTF_MNTN_ErrlogTbfAbnmlEvt(VOS_UINT32 ulPid, VOS_UINT16 usType);
extern VOS_VOID WTTF_MNTN_ErrlogRlcResetEvt(VOS_UINT32 ulPid, VOS_UINT8 ucRbId,
        TTF_MNTN_ERR_LOG_WRLC_RESET_TYPE_ENUM_UINT8 enResetType);
extern VOS_VOID WTTF_MNTN_ErrlogRlcLiErrEvt(VOS_UINT32 ulPid, VOS_UINT8 ucRbId,
    TTF_MNTN_ERR_LOG_LI_ERR_TYPE_ENUM8 enLiErrType);
extern VOS_VOID  WTTF_MNTN_ErrlogTfciFailEvt(VOS_UINT32 ulPid, VOS_UINT8 ucMacState,
        TTF_MNTN_ERR_LOG_TFC_ERR_NO_CHOICE_ENUM8 enType);
extern GTTF_UL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForGUL(VOS_UINT32 ulPid);
extern GTTF_DL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForGDL(VOS_UINT32 ulPid);
extern WTTF_MAC_UL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUL(VOS_UINT32 ulPid);
extern WTTF_MAC_DL_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForWDL(VOS_UINT32 ulPid);
extern WTTF_UL_SCHED_INFO_STRU * TTF_MNTN_ErrlogGetCommInfoBuffAddrForWUlSched(VOS_UINT32 ulPid);
extern TTF_MNTN_WCDMA_COMM_INFO_STRU * TTF_MNTN_ErrlogGetWcdmaCommInfo(VOS_UINT32 ulPid);
extern TTF_MNTN_GSM_COMM_INFO_STRU * TTF_MNTN_ErrlogGetGsmCommInfo(VOS_UINT32 ulPid);
#endif

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

#endif /* end of TtfErrlog.h */

