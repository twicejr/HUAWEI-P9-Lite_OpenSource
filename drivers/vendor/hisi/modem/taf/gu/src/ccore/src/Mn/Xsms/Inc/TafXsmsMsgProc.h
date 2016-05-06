/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsMsgProc.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : TafXsmsMsgProc.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_MSG_PROC_H_
#define _TAF_XSMS_MSG_PROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasNvInterface.h"
#include "cas_1x_control_main_nas_pif.h"
#include "xcc_sms_pif.h"
#include "TafXsmsCtx.h"
#include "TafXsmsInterMsg.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_XSMS_CAS_DATA_IND_MAX_LEN  (255)
#define TAF_XSMS_DBM_SMS_TYPE          (0x03)

#define TAF_XSMS_RESEND_TIMES_MAX          (7)   /* 短信发送过程中重试次数 */
#define TAF_XSMS_RECONNECT_INTERVAL_MAX    (5)   /* 短信发送过程中重新建立连接的间隔，秒为单位 */
#define TAF_XSMS_RESEND_INTERVAL_MAX       (1)   /* 短信发送过程中重新给接入层发数据的间隔，秒为单位 */

/* 设置 CS0005E_Details 成员 */
#define TAF_XSMS_SetCS0005EDetailPara(pstCS0005Detail,usMsgTag,usPRevInUse,usAuthMode)\
    {\
        PS_MEM_SET((pstCS0005Detail),0,sizeof(CS0005E_Details));\
        (pstCS0005Detail)->n_MSG_TAG          = (usMsgTag);\
        (pstCS0005Detail)->n_P_REV_IN_USEs    = (usPRevInUse);\
        (pstCS0005Detail)->n_AUTH_MODE        = (usAuthMode);\
    }

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM
 枚举说明  : 第三编解码函数错误类型
*****************************************************************************/
enum TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM
{
    TAF_XSMS_3RD_PARTY_ERR_DECODE_c_f_csch_mini6                = 0x00,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_SETPRESENT_c_r_csch_mini6_DBM = 0x01,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_c_r_csch_mini6         = 0x02,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_DECODE_c_f_dsch               = 0x03,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_SETPRESENT_c_r_dsch_DBM       = 0x04,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_c_r_dsch               = 0x05,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_BUTT
};

typedef VOS_UINT32 TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM_UINT32;



/*****************************************************************************
 枚举名    : TAF_XSMS_CAS_DATA_REQ_TYPE_ENUM
 枚举说明  : 给接入层的DATA_REQ类型
*****************************************************************************/
enum TAF_XSMS_CAS_DATA_REQ_TYPE_ENUM
{
    TAF_XSMS_CAS_DATA_REQ_TYPE_MO   = 0x5A,
    TAF_XSMS_CAS_DATA_REQ_TYPE_MT   = 0xA5,
    TAF_XSMS_CAS_DATA_REQ_TYPE_BUTT = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_CAS_DATA_REQ_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : TAF_XSMS_SEND_XCC_CALL_ID_ENUM
 枚举说明  : MO/MT短信的call id
*****************************************************************************/
enum TAF_XSMS_SEND_XCC_CALL_ID_ENUM
{
    TAF_XSMS_SEND_XCC_CALL_ID_MO     = 0x55,
    TAF_XSMS_SEND_XCC_CALL_ID_MT     = 0xAA,
    TAF_XSMS_SEND_XCC_CALL_ID_BUTT   = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_SEND_XCC_CALL_ID_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*****************************************************************************
 结构名    : TAF_XSMS_CAS_DATA_IND_MSG_STRU
 结构说明  : 接入层上报的DSCH和CSCH数据转换后在XSMS内部使用的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CAS_1X_CONTROL_MAIN_NAS_PIF_MSG_TYPE_ENUM_UINT16        enMsgId;       /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucLen;
    VOS_UINT8                                               aucMsg[TAF_XSMS_CAS_DATA_IND_MAX_LEN];
}TAF_XSMS_CAS_DATA_IND_MSG_STRU;





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
/* Deleted by wx270776 for OM融合, 2015-7-16, begin */
/* Deleted by wx270776 for OM融合, 2015-7-16, end */

extern VOS_VOID   TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32 enMsgName, VOS_UINT8 *pucMsg, VOS_UINT32 ulMsgLen);

extern VOS_VOID   TAF_XSMS_AtDeleteMsgProc(TAF_XSMS_DELETE_MSG_REQ_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_AtWriteMsgProc(TAF_XSMS_WRITE_MSG_REQ_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_AtMsgProc(MsgBlock* pstMsg);

extern VOS_VOID   TAF_XSMS_TimeOutMsgProc(REL_TIMER_MSG *pstRelTimerMsg);

extern VOS_VOID   TAF_XSMS_XccEndCallCnfChooseStateMachine(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_XccSoIndChooseStateMachine(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_XccMsgProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_1xCasMsgProc(MsgBlock* pstMsg);

extern VOS_UINT32 TAF_XSMS_TransCSCHDataToDbm(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
);

extern VOS_UINT32 TAF_XSMS_TransDbmToCSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschData
);

extern VOS_UINT32 TAF_XSMS_TransDSCHDataToDbm
(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
);

extern VOS_UINT32 TAF_XSMS_TransDbmToDSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU     *pstDschData
);

extern VOS_VOID   TAF_XSMS_CasDschCnfProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasDschDataIndProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasCschCnfProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasCschDataIndProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasAbortProc(MsgBlock *pstMsg);

extern VOS_UINT32 TAF_XSMS_CheckIsSmsDbm(TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm);

extern VOS_VOID   TAF_XSMS_PidMsgProc(MsgBlock* pstMsg);

extern VOS_UINT32 TAF_XSMS_PidInit(enum VOS_INIT_PHASE_DEFINE  ip);
extern VOS_UINT32 TAF_XSMS_EncodeCschOrderMsg
(
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschDataReq
);

extern VOS_UINT32 TAF_XSMS_TransDbmToAucData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    VOS_UINT8                          *paucData
);

extern VOS_VOID TAF_XSMS_TransAucDataToDbm
(
    VOS_UINT8                          *paucData ,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
);

extern VOS_VOID TAF_XSMS_DealXccVoiceMailInd(MsgBlock* pstMsg);
extern VOS_VOID TAF_XSMS_AtApMemFullMsgProc(TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU *pstApMemFullMsg);
extern VOS_VOID TAF_XSMS_StkProc(MsgBlock *pstMsg);
extern VOS_VOID TAF_XSMS_HookSmsContect(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    VOS_UINT32                          ulReqSeq,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
);
extern VOS_VOID TAF_XSMS_HookSmsTlAck(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode
);

VOS_VOID TAF_XSMS_XpdsProc(MsgBlock *pstMsg);
VOS_VOID TAF_XSMS_XcallProc(MsgBlock *pstMsg);


#endif


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

