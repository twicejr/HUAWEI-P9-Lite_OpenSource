/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmAppMsgParaProc.h
    Description :
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.祝义强 00138739    2008-09-11
     3.杨茜惠 00135146    2008-12-19  Modify  BA8D00752
******************************************************************************/

#ifndef _NASESMAPPMSGPARAPROC_H
#define _NASESMAPPMSGPARAPROC_H



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasEsmPublic.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_ESM_DEFAULT_BEARER_TYPE_SDF_NUM_ONE             (1)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_ESM_SERVICE_REMOTE_PORT_ENUM
{
    NAS_ESM_SERVICE_REMOTE_FTP                  = 21,
    NAS_ESM_SERVICE_REMOTE_TELNET               = 23,
    NAS_ESM_SERVICE_REMOTE_HTTP                 = 80,
    NAS_ESM_SERVICE_REMOTE_BUTT
};

typedef VOS_UINT16 NAS_ESM_SERVICE_REMOTE_PORT_ENUM_UINT16;

enum NAS_ESM_PROTOCOL_ID_ENUM
{
    NAS_ESM_PROTOCOL_ID_TCP                     = 6,
    NAS_ESM_PROTOCOL_ID_UDP                     = 17,
    NAS_ESM_PROTOCOL_ID_BUTT
};

typedef VOS_UINT16 NAS_ESM_PROTOCOL_ID_ENUM_UINT16;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    APP_ESM_MSG_TYPE_ENUM_UINT32        ulMsgId;
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulSetRslt;
}NAS_ESM_APP_PARA_SET_RESLT_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /*本次操作标识*/
    VOS_UINT32                          ulCid;              /*上下文序列号:0~31       */
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;          /*设置类型:0:设置,1:删除*/
}NAS_ESM_APP_PARA_SET_HEAD_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID NAS_ESM_AppParaSetCnf( const NAS_ESM_APP_PARA_SET_RESLT_STRU *pstParaInfo);

extern VOS_VOID NAS_ESM_BearerCntxtParaInit( VOS_VOID );

extern VOS_VOID NAS_ESM_BearerManageInfoInit( NAS_ESM_PDP_MANAGE_INFO_STRU *pstBearerManInfo );

extern VOS_VOID NAS_ESM_AppParaSetMsgProc(VOS_VOID *pRcvMsg);
extern VOS_VOID NAS_ESM_AppParaQueryMsgProc(VOS_VOID *pRcvMsg);


extern VOS_VOID NAS_ESM_AppParaSetTft( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaSetSdfQos( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaSetApn( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaSetPco( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaSetPdnType( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaSetPdnReqType( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaSetBearType( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaSetPdpManagType( VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ESM_AppParaSetGwAuthInfo( VOS_VOID *pRcvMsg  );

extern VOS_UINT32 NAS_ESM_AppCgdcontOrNdisConnSetBearType
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_CID_TYPE_ENUM_UINT32        enBearCidType,
    VOS_UINT32                          bitOpLinkdCid,
    VOS_UINT32                          ulLinkdCid
);
extern VOS_UINT32 NAS_ESM_AppCgdconntOrNDISconnSetPdnType
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          bitOpIpv4AddrAllocType,
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32 enIpv4AddrAllocType

);
extern VOS_UINT32 NAS_ESM_AppCgdcontOrNdisConnSetApn
(
    VOS_UINT32                                  ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32                enSetType,
    APP_ESM_APN_INFO_STRU                       stApnInfo
);
extern VOS_UINT32 NAS_ESM_AppNdisConnSetGwAuthInfo( VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ESM_AppSetCgdcont( VOS_VOID *pRcvMsg  );

extern VOS_VOID NAS_ESM_AppParaQueryTft( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaQueryQos( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaQuerySdfQos( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaQueryApn( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaQueryPdnType( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaQueryPdnReqType( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_AppParaQueryBearQos(VOS_VOID *pRcvMsg);
extern VOS_VOID  NAS_ESM_SndEsmAppBearerQosIndMsg(VOS_UINT32 ulEpsbId);
extern VOS_VOID NAS_ESM_AppSetCnfParaInfo( NAS_ESM_APP_PARA_SET_RESLT_STRU*  pstParaInfo,
                                          const NAS_ESM_APP_PARA_SET_HEAD_STRU* pstRcvInfo);

extern VOS_VOID NAS_ESM_AppQueryDynamicPdpMsgProc
(
        const VOS_VOID   *pRcvMsg
);

extern VOS_VOID NAS_ESM_AppQueryDynamicEpsQosMsgProc
(
        const VOS_VOID   *pRcvMsg
);

extern VOS_VOID NAS_ESM_AppQueryDynamicTftMsgProc
(
        const VOS_VOID   *pRcvMsg
);

extern VOS_VOID  NAS_ESM_AppParaQueryGwAuthInfo( VOS_VOID *pRcvMsg  );
extern VOS_VOID  NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo( VOS_VOID *pstRsvMsg ,VOS_VOID *pstCntxtInfo);
extern VOS_VOID NAS_ESM_AppIpv6InfoNotifyMsgProc(VOS_VOID* pRcvMsg);

VOS_UINT32  NAS_ESM_IsPrefixInfoExist(VOS_UINT8 ucEpsId);
VOS_UINT32  NAS_ESM_MatchPrefixInfo
(
    const VOS_UINT8  *pucLocalPrefix,
    const VOS_UINT8  *pucPrefix
);

extern VOS_UINT32  NAS_ESM_CheckAppSdfQosOperation
(
    const APP_ESM_SET_EPS_QOS_REQ_STRU       *pAppSdfQosMsg
);
extern VOS_UINT32  NAS_ESM_CheckAppSdfQosOperation
(
    const APP_ESM_SET_EPS_QOS_REQ_STRU       *pAppSdfQosMsg
);
extern VOS_UINT32  NAS_ESM_CheckAppPcoOperation
(
    const APP_ESM_SET_PCO_REQ_STRU           *pAppPcoMsg
);

/* niuxiufan DT begin */
extern VOS_VOID NAS_ESM_AppQueryActPdpInfoMsgProc
(
        const VOS_VOID   *pRcvMsg
);

extern VOS_VOID NAS_ESM_GetActPdpInfo
(
        NAS_OM_ACT_PDP_INFO_STRU   *pActPdpInfo
);

/* niuxiufan DT end */

extern VOS_UINT32  NAS_ESM_CheckAppGwAuthInfoOperation
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_GW_AUTH_INFO_STRU           *pstGwAuthInfo
);

extern VOS_VOID  NAS_ESM_InitLocalIpsupportInfo(VOS_VOID);
extern VOS_UINT32 NAS_ESM_SaveAppNdisConnInfo(VOS_VOID *pRcvMsg);

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

#endif /* end of NasEsmAppMsgPreProc.h*/
