


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "TafLog.h"
#include "TafApsSndRabm.h"



#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SNDRABM_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/


VOS_VOID TAF_APS_SndRabmSetTransModeMsg(
    VOS_UINT8                           ucNsapi,
    RABM_TRANS_MODE_ENUM                enTransMode
)
{
    RABM_APS_SET_TRANSMODE_MSG         *pstRabmSetTransModeMsg;

    /* 构造消息 */
    pstRabmSetTransModeMsg = (RABM_APS_SET_TRANSMODE_MSG*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_TAF,
                                        sizeof(RABM_APS_SET_TRANSMODE_MSG));
    if (VOS_NULL_PTR == pstRabmSetTransModeMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndRabmSetTransMode: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstRabmSetTransModeMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABM_APS_SET_TRANSMODE_MSG) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstRabmSetTransModeMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRabmSetTransModeMsg->ulReceiverPid   = WUEPS_PID_RABM;
    pstRabmSetTransModeMsg->usMsgType       = RABM_APS_SET_TRANSMODE_MSG_TYPE;

    /* 填写消息内容 */
    pstRabmSetTransModeMsg->RabmApsSetTransMode.ucNsapi   = ucNsapi;
    pstRabmSetTransModeMsg->RabmApsSetTransMode.TransMode = enTransMode;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstRabmSetTransModeMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "MN_APS_PackEsmPdpOptModify: Send message failed.");
        return;
    }

    return;
}

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif





