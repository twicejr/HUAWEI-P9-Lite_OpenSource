
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndRabm.c　
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : 发送给RABM的消息发送函数
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : S62952
    修改内容   : 创建文件

******************************************************************************/

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

/*****************************************************************************
 函 数 名  : TAF_APS_SndRabmSetTransModeMsg
 功能描述  : 发送RABM_APS_SET_TRANSMODE_MSG_TYPE消息至RABM
 输入参数  : ucNsapi                    - NSAPI
             enTransMode                - 传输模式(ABM/ADM)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月27日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
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





