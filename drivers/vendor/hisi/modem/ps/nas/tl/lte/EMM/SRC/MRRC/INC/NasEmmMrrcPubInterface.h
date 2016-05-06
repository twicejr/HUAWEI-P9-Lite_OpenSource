/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmMrrcPubInterface.h
    Description :
    History     :
      1.  zangyalan 57968  2008-09-04  Draft Enact
      2.
******************************************************************************/
#ifndef __NASEMMMRRCPUBINTERFACE_H__
#define __NASEMMMRRCPUBINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "LRrcLNasInterface.h"



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
#define NAS_EMM_MRRC_BIT_SLCT               1
#define NAS_EMM_MRRC_BIT_NO_SLCT            0


#define NAS_EMM_GIM_VOS_MSG_HEADER_LEN       20

#define NAS_EMM_MRRC_DATA_REQ_LEN(CnMsgLen)  (NAS_EMM_MSG_ID_LEN + CnMsgLen + NAS_RRC_EST_CAUSE_LEN +NAS_RRC_EST_MSG_TYPE_LEN)

#define NAS_EMM_MRRC_CONNECT_FAIL_IND_LEN    (NAS_EMM_GIM_VOS_MSG_HEADER_LEN + NAS_EMM_MSG_ID_LEN + sizeof(LRRC_LNAS_EST_RESULT_ENUM_UINT32))

#define NAS_LMM_OPID                          0

#define NAS_EMM_SetNormalServiceRelCause(ucCause)      (g_stEmmMrrcCtrl.ulRelCause = ucCause)
#define NAS_EMM_GetNormalServiceRelCause()             (g_stEmmMrrcCtrl.ulRelCause)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_LMM_BARRED_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : nas在发送释放请求时,指示当前使用的小区是否被bar
*****************************************************************************/
enum NAS_LMM_BARRED_IND_ENUM
{
    NAS_LMM_NOT_BARRED                   = 0,                                    /* 原小区没有被barred */
    NAS_LMM_BARRED                       = 1,                                    /* 原小区被barred */
    NAS_NAS_BARRED_IND_BUTT
};
typedef VOS_UINT32 NAS_LMM_BARRED_IND_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_EMM_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS在进行连接建立请求时发送的消息类型
*****************************************************************************/
enum NAS_EMM_MSG_TYPE_ENUM
{
    NAS_EMM_MSG_ATTACH_REQ               = 0x01,    /*attach message type*/
    NAS_EMM_MSG_ATTACH_CMP               ,
    NAS_EMM_MSG_DETACH_REQ               ,          /*detach message type*/
    NAS_EMM_MSG_DETACH_ACP               ,
    NAS_EMM_MSG_LOAD_BALANCING_TAU       ,          /*load balancing tau message type*/
    NAS_EMM_MSG_NOT_LOAD_BALANCING_TAU   ,
    NAS_EMM_MSG_TAU_CMP                  ,
    NAS_EMM_MSG_SERVICE_REQ              ,          /*service message type*/
    NAS_EMM_MSG_GUTI_CMP                 ,
    NAS_EMM_MSG_IDEN_RSP                 ,
    NAS_EMM_MSG_AUTH_RSP                 ,
    NAS_EMM_MSG_AUTH_FAIL                ,
    NAS_EMM_MSG_SMC_COMPL                ,
    NAS_EMM_MAS_SMC_REJ                  ,
    NAS_EMM_NAS_STATUS                   ,
    NAS_EMM_NAS_UPLINK_NAS_TRANSPORT     ,          /*uplink NAS transport  2011-11-15*/
    NAS_EMM_MSG_EXTENDED_SERVICE_REQ     ,
    NAS_EMM_MSG_ESM                      ,
    NAS_EMM_MSG_TC                       ,
    NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT,       /*uplink generic NAS transport*/
    NAS_EMM_MSG_OTHER                    ,
    NAS_EMM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_EMM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_NORMALSERVICES_REL_CAUSE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 进入REG+NORAML_SERVICE或REG+ATTEMPT_TO_UPDATE_MM状态释放链路原因枚举
*****************************************************************************/
enum NAS_EMM_NORMALSERVICE_REL_CAUSE_ENUM
{
    NAS_EMM_NORMALSERVICE_REL_CAUSE_NULL           = 0,
    NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_2,
    NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_161722,
    NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_18,

    NAS_EMM_NORMALSERVICE_REL_CAUSE_BUTT,
};
typedef VOS_UINT32 NAS_EMM_NORMALSERVICE_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*MRRC模块和其他模块的原语接口******************************/
/* The Struct from other EMM module to MRRC for sending UL user data */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /* 消息Id */
    LRRC_LNAS_EST_CAUSE_ENUM_UINT32     enEstCaue;      /*请求建链的原因*/
    LRRC_LNAS_CALL_TYPE_ENUM_UINT32      enCallType;     /*call type*/
    LRRC_LMM_DATA_CNF_ENUM_UINT32       enDataCnf;      /*是否需要确认发送*/
    VOS_UINT32                          ulEsmMmOpId;
    VOS_UINT32                          ulEmmLppOrSsOpId;   /*Emm跟Lpp或者Ss之间的OpId维护*/
    VOS_UINT32                          ulLppSsFlag;        /* 0:表示LPP；1表示SS */
    NAS_EMM_MSG_TYPE_ENUM_UINT32        enEmmMsgType;   /*建立连接时的消息类型*/
    LRRC_LNAS_MSG_STRU                    stNasMsg;       /* 区分是什么nas消息 */

}NAS_EMM_MRRC_DATA_REQ_STRU;

/* emm内部模块请求建立rrc连接失败后，mrrc给emm内部发起模块的回复 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;   /* 消息结构 */
    LRRC_LNAS_EST_RESULT_ENUM_UINT32      enEstResult; /*连接建立结果*/
}NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU;

/*The Struct from other EMM module to MRRC for release RRC CONN*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;   /* 消息结构 */
    NAS_LMM_BARRED_IND_ENUM_UINT32       enBarInd;
}NAS_EMM_MRRC_REL_REQ_STRU;

/*The Struct from MRRC to other EMM module for release RRC CONN CNF*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;        /* 消息结构 */
    VOS_UINT32          ulReserved;
}NAS_EMM_MRRC_REL_IND_STRU;

/*****************************************************************************
 结构名    : NAS_EMM_MRRC_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS_EMM_MRRC_CTRL_STRU数据结构
*****************************************************************************/
typedef struct
{
   NAS_EMM_NORMALSERVICE_REL_CAUSE_ENUM_UINT32     ulRelCause;
}NAS_EMM_MRRC_CTRL_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_EMM_MRRC_CTRL_STRU                  g_stEmmMrrcCtrl;

/*****************************************************************************
  8 Function Extern
*****************************************************************************/
/*MRRC模块和PUBLIC模块的函数接口*****************************/
/*在非RRC_CONN_INIT主状态的任何状态，收到MRRC_DATA_REQ消息 */
extern VOS_UINT32 NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq(VOS_UINT32 ulMsgId, VOS_VOID *pMsgStru);
extern VOS_VOID  NAS_EMM_SndUplinkNasMsg
(
    VOS_VOID *pMsgStru
);

/*把RRC连接状态设为连接态*/
extern VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstSignal( VOS_VOID );
extern VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);


/*把RRC连接状态设为建立过程中*/
extern VOS_VOID  NAS_EMM_ChangeRrcConnStateToEsting( VOS_VOID );
extern VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstData( VOS_VOID );
/*MRRC模块初始化函数*/
extern VOS_VOID NAS_EMM_MrrcInit(VOS_VOID);
extern VOS_VOID NAS_EMM_FreeMrrcDyn( VOS_VOID );
extern VOS_UINT32  NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg);

extern VOS_VOID    NAS_EMM_RelReq(NAS_LMM_BARRED_IND_ENUM_UINT32 enBarStatus);
extern VOS_VOID    NAS_EMM_WaitNetworkRelInd(VOS_VOID);

extern VOS_VOID    NAS_EMM_MrrcChangeRrcStatusToIdle(VOS_VOID);
extern VOS_UINT32  NAS_EMM_PreProcMsgRabmDrbSetupInd( MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_ProcDeregMmcRelReq(VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcDetachMmcRelReq(VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReq(VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReqWhileTauInit(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReqWhileSerInit(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReqWhileImsiDetach(VOS_VOID);

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

#endif /* end of 发送模块+接收模块+Interface.h */
