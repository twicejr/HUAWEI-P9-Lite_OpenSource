
#ifndef _TAF_SPM_SND_USIM_H_
#define _TAF_SPM_SND_USIM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"

#include "TafAppSsa.h"
#include "UsimPsInterface.h"
#include "siapppb.h"
#include "MnCallApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

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



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 TAF_SPM_SendPbUssdFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendPbSsFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendUsimUssdEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendUsimSsEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_TransUssdMsgToAsciiStr(
    TAF_SS_PROCESS_USS_REQ_STRU        *pstUssdMsg,
    VOS_UINT8                          *pucAsciiStr,
    VOS_UINT32                         *pulAsciiStrLength
);

VOS_UINT32  TAF_SPM_BuildUssdFdnInfo(
    struct MsgCB                       *pstMsg,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
);

VOS_UINT32  TAF_SPM_BuildSsFdnInfo(
    struct MsgCB                       *pstMsg,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
);

VOS_UINT32 TAF_SPM_GetUssdStringSeptetLength(
    VOS_UINT32                          ulOctetLength,
    VOS_UINT8                           ucLastByte
);

VOS_UINT32 TAF_SPM_BuildUssdStringInfo(
    TAF_SS_DATA_CODING_SCHEME           ucDatacodingScheme,
    TAF_SS_USSD_STRING_STRU            *pstSrcUssd,
    TAF_SS_USSD_STRING_STRU            *pstDstUssd
);

VOS_UINT32 TAF_SPM_SendPbCallFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendUsimCallEnvelopeReq_Call(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  TAF_SPM_SendUsimCallEnvelopeReq(
    MN_CALL_CALLED_NUM_STRU            *pstCalledNumber,
    MN_CALL_CS_DATA_CFG_INFO_STRU      *pstDataCfgInfo,
    VOS_UINT32                          ulSendPara,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32  TAF_SPM_SendUsimEconfEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_SendUsimEconfFdnReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
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

#endif /* end of TafSpmSndUsim.h */

