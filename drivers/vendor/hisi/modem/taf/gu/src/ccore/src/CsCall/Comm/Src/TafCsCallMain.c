/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCsCallMain.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年09月03日
  功能描述   : TAF CS CALL模块初始化，入口函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafCsCallMain.h"
#include "TafXCallMain.h"
#include "MnCall.h"
#include "TafSdcLib.h"
#include "TafCsCallCtx.h"
#include "MnCallTimer.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_MAIN_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : TAF_CSCALL_Init
 功能描述  : CS CALL模块初始化
 输入参数  : TAF_CSCALL_INIT_TYPE_ENUM_UINT8     enInitCtxType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_Init(
    TAF_CSCALL_INIT_TYPE_ENUM_UINT8     enInitCtxType
)
{
    /* 初始化上下文 */
    TAF_CSCALL_InitCtx();
}

/*****************************************************************************
 函 数 名  : TAF_CSCALL_IsNeedXcallProcAppReqMsg
 功能描述  : 是否是XCALL需要处理的消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_CSCALL_IsNeedXcallProcAppReqMsg(struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    switch ( pstMsgHeader->ulMsgName )
    {
        case MN_CALL_APP_SET_UUSINFO_REQ:
        case MN_CALL_APP_QRY_UUSINFO_REQ:
        case MN_CALL_APP_SET_ALS_REQ:
        case MN_CALL_APP_QRY_ALS_REQ:
        case MN_CALL_APP_CLPR_GET_REQ:
        case MN_CALL_APP_SET_CSSN_REQ:
        case MN_CALL_QRY_ECALL_INFO_REQ:
        case MN_CALL_APP_END_REQ:
        case MN_CALL_APP_ANSWER_REQ:
        case MN_CALL_APP_START_DTMF_REQ:
        case MN_CALL_APP_STOP_DTMF_REQ:
        case MN_CALL_APP_GET_CDUR_REQ:
        /* 紧急呼号码定制AT^NVM命令进入XCALL独立处理 */
            return VOS_FALSE;

        default:
            return VOS_TRUE;

    }
}

/*****************************************************************************
 函 数 名  : TAF_CSCALL_ProcAppReqMsg
 功能描述  : CS CALL模块处理来自应用层的请求消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcAppReqMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulRslt;

    /* CL互操作模式 */
    ulRslt = TAF_CSCALL_IsNeedXcallProcAppReqMsg(pstMsg);
    if ((VOS_TRUE == TAF_SDC_IsConfigCLMode())
       &&(VOS_TRUE == ulRslt))
    {
        TAF_XCALL_ProcAppReqMsg(pstMsg);

        return;
    }
#endif


    MN_CALL_ProcAppReqMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CSCALL_ProcVcMsg
 功能描述  : CS CALL模块处理来自VC的消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcVcMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_XCALL_ProcVcMsg(pstMsg);

        return;
    }
#endif

    MN_CALL_ProcVCMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CSCALL_ProcMmaMsg
 功能描述  : CS CALL模块处理来自MMA的消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcMmaMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcMmaMsg(pstMsg);
#endif

    TAF_CALL_ProcMmaMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CSCALL_ProcTimerOutMsg
 功能描述  : CS CALL模块处理来自timer的消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcTimerOutMsg(
    REL_TIMER_MSG                       *pTmrMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcTimerOutMsg(pTmrMsg);
#endif

    /* 调用CCA的定时器消息处理函数 */
    MN_CALL_ProcTimeoutMsg(pTmrMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_CSCALL_ProcUsimMsg
 功能描述  : CS CALL模块处理来自usim的消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcUsimMsg(
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcUsimMsg(pstMsg);
#endif

    /* 调用CCA的USIM消息处理函数 */
    MN_CALL_DispatchUsimMsg(pstMsg);

    return;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_CSCALL_ProcXsmsMsg
 功能描述  : CS CALL模块处理来自XSMS的消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcXsmsMsg(
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcXsmsMsg(pstMsg);
#endif
}



/*****************************************************************************
 函 数 名  : TAF_CSCALL_ProcCttfMsg
 功能描述  : CS CALL模块处理来自CTTF的消息
 输入参数  : struct MsgCB* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcCttfMsg(
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    TAF_XCALL_ProcCttfMsg(pstMsg);
#endif
#endif
}
#endif

/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




