/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaPktMgmt.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年1月7日
  最近修改   :
  功能描述   : CmmcaPktMgmt.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月7日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CMMCAPKTMGMT_H__
#define __CMMCAPKTMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CmmcaCtxPkt.h"
#include "CmmcaParseCmd.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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


typedef VOS_UINT32 (*CMMCA_PKT_PS_EVT_FUNC)(VOS_VOID *pEvtInfo);

/*****************************************************************************
 结构名    : CMMCA_PS_EVT_FUNC_TBL_STRU
 结构说明  : APS PS域事件处理函数表结构
 1.日    期   : 2014年01月29日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEvtId;
    CMMCA_PKT_PS_EVT_FUNC               pPsEvtFunc;
}CMMCA_PKT_EVT_FUNC_TBL_STRU;


/*****************************************************************************
 结构名    : CMMCA_PKT_ERR_CODE_MAP_TBL_STRU
 结构说明  : TAF错误码和CMMC错误码映射表
 1.日    期   : 2014年01月29日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8     enErrCode;
}CMMCA_PKT_ERR_CODE_MAP_TBL_STRU;


/*****************************************************************************
 结构名    : CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU
 结构说明  : 保存PDN TAB设置请求的结构
 1.日    期   : 2014年02月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId;
    VOS_UINT8                           ucCurIndex;
    VOS_UINT8                           ucTotalNum;
    CMMCA_PDN_INFO_STRU                 astPdnInfo[CMMCA_SUPPORTED_PDN_NUM_MAX];
}CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU
 结构说明  : ID_CMMCA_RAT_MMC_PDN_TABLE_SETUP_RSP的消息结构
 1.日    期   : 2014年01月10日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_ID_ENUM_UINT8                     enRatId;
    CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM_UINT8        ucResult;
    VOS_UINT8                                       aucReserved[2];
}CMMCA_MMC_SET_PDN_PCO_AUTH_CNF_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID CMMCA_PKT_RcvCmmcSetPdnTabReq(
    VOS_VOID                           *pMsg
);

VOS_VOID CMMCA_PKT_RcvCmmcDefaultBearConnReq(
    VOS_VOID                           *pMsg
);

VOS_VOID CMMCA_PKT_RcvCmmcBearDiscReq(
    VOS_VOID                           *pMsg
);


VOS_VOID CMMCA_PKT_RcvCmmcSetPdnTabReq(
    VOS_VOID                           *pMsg
);

VOS_VOID CMMCA_PKT_RcvCmmcDefaultBearConnReq(
    VOS_VOID                           *pMsg
);

VOS_VOID CMMCA_PKT_RcvCmmcBearDiscReq(
    VOS_VOID                           *pMsg
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtSetPrimPdpContextInfoCnf(
   VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtCallOrigCnf(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtCallEndCnf(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateCnf(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateRej(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateInd(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpModifyInd(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd(
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd(
    VOS_VOID                           *pEvtInfo
);

VOS_VOID CMMCA_PKT_RcvTafPsEvt(
    TAF_PS_EVT_STRU                    *pstEvt
);



VOS_VOID CMMCA_PKT_RcvTiWaitIpv6RaExp(
    REL_TIMER_MSG                      *pstTiMsg
);



VOS_VOID CMMCA_PKT_ProcIpv4ActCnf(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
);

VOS_VOID CMMCA_PKT_ProcIpv6ActCnf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
);

VOS_VOID CMMCA_PKT_ProcIpv4v6ActCnf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
);

VOS_VOID CMMCA_PKT_BuildPrimPdpContextInfo(
    CMMCA_PDN_INFO_STRU               *pstPdnInfo,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU     *pstPdpCtxInfo
);

VOS_VOID CMMCA_PKT_SndSetPdnRsp(
    CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM_UINT8    enRslt
);

VOS_VOID  CMMCA_PKT_SndDefaultBearConnRsp(
    VOS_UINT8                                   ucPdnId,
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8   enRslt,
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode
);


VOS_VOID CMMCA_PKT_SndBearDiscRsp(
    VOS_UINT8                           ucPdnId,
    CMMCA_RAT_MMC_RESULT_ENUM_UINT8     enRslt
);


VOS_VOID CMMCA_PKT_SndBearDiscInd(
    VOS_UINT8                           ucPdnId
);

VOS_UINT32 CMMCA_PKT_ProcSdfPara(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucPdnEntityIndex
);

VOS_VOID CMMCA_PKT_GetDialParaFromSdfPara(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_PS_DIAL_PARA_STRU              *pstDialPara
);

VOS_VOID CMMCA_PKT_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
);

CMMCA_RAT_MMC_PKT_ERRCODE_UINT8 CMMCA_PKT_TransferErrCode(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID CMMCA_PKT_SndSetPdnPcoAuthRsp(
    CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM_UINT8        enRslt
);

VOS_UINT32 CMMCA_PKT_RcvTafSetPdnPcoAuthCnf(
    VOS_VOID                           *pEvtInfo
);

VOS_VOID CMMCA_PKT_RcvCmmcSetPdnPcoAuthReq(
    VOS_VOID                           *pMsg
);


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

#endif /* end of CmmcaPktMgmt.h */
