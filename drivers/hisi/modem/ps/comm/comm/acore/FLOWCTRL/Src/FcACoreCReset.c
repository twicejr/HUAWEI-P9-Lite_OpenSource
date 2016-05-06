 


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"
#if(FEATURE_ON == FEATURE_ACPU_FC_POINT_REG)

#include "Fc.h"
#include "FcInterface.h"
#include "FcIntraMsg.h"
#include "FcACoreCReset.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_ACORE_CRESET_FLOW_CTRL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
VOS_SEM         g_ulFcACoreCResetDoneSem;    /* FcACore完成回调事务信号量 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : FC_ACORE_CResetSendNotify
 功能描述  : 底软C核复位过程模块通知FcACore进行复位处理或者发送复位成功的通知
 输入参数  : FC_MSG_TYPE_ENUM_UINT16     usMsgName      消息名称
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月22日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_ACORE_CResetSendNotify(FC_MSG_TYPE_ENUM_UINT16     usMsgName)
{
    FC_ACORE_CRESET_IND_STRU    *pstMsg;

    /* 申请消息内存 */
    pstMsg = (FC_ACORE_CRESET_IND_STRU *) VOS_AllocMsg( UEPS_PID_FLOWCTRL_A,
        sizeof(FC_ACORE_CRESET_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    if ( VOS_NULL_PTR == pstMsg )
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetSendNotify, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    /* 填写消息内容 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL_A;
    pstMsg->usMsgName       = usMsgName;

    /* 发送消息 */
    (VOS_VOID)VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : FC_ACORE_CResetCallback
 功能描述  : FcACore需要注册到底软C核复位接口中的回调函数
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT enParam 指示时复位处理前还是复位成功后
             int userdata                       用户自定义数据
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月22日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_INT FC_ACORE_CResetCallback(DRV_RESET_CB_MOMENT_E enParam, VOS_INT userdata)
{
    VOS_UINT32                   ulResult;


    if ( MDRV_RESET_CB_BEFORE == enParam )      /* 复位处理时调用 */
    {
        FC_ACORE_CResetSendNotify(ID_FC_ACORE_CRESET_START_IND);

        ulResult = VOS_SmP(g_ulFcACoreCResetDoneSem, FC_ACORE_CRESET_TIMEOUT_LEN);
        if (VOS_OK != ulResult)
        {
            FC_LOG1(PS_PRINT_ERROR,
                          "FC_ACORE_CRESET_Callback, wait g_ulFcACoreResetDoneSem timeout! ulResult = %d\r\n", (VOS_INT32)ulResult);

            return VOS_ERR;
        }
    }
    else if ( MDRV_RESET_CB_AFTER == enParam )   /* 复位成功后调用 */
    {
        FC_ACORE_CResetSendNotify(ID_FC_ACORE_CRESET_END_IND);
    }
    else
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetCallback, enParam invalid !\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_ACORE_CResetProc
 功能描述  : FcACore收到底软C核复位过程处理模块发来的复位及复位成功的通知后的处理函数
 输入参数  : FC_ACORE_CRESET_MOMENT_ENUM_UINT8 enCResetMoment 指示时复位处理前还是复位成功后
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月22日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_ACORE_CResetProc(FC_ACORE_CRESET_MOMENT_ENUM_UINT8 enCResetMoment)
{
    VOS_UINT32                          ulFcPointLoop;
    FC_POINT_STRU                      *pFcPoint;
    VOS_UINT32                          ulResult;
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;
    FC_ACORE_CRESET_RSP_STRU           *pstMsg;
    VOS_UINT32                          ulRspResult;


    ulRspResult         = 0;

    if ( FC_ACORE_CRESET_BEFORE_RESET == enCResetMoment )
    {
        usMsgName           = ID_FC_ACORE_CRESET_START_RSP;

        /* 复位处理时遍历每个流控点，执行流控点上外部模块注册的reset函数 */
        for ( ulFcPointLoop = 0; ulFcPointLoop < g_stFcPointMgr.ulPointNum; ulFcPointLoop++ )
        {
            pFcPoint    = &g_stFcPointMgr.astFcPoint[ulFcPointLoop];

            if ( pFcPoint->pRstFunc != VOS_NULL_PTR )
            {
                ulResult     = pFcPoint->pRstFunc(pFcPoint->ulParam1, pFcPoint->ulParam2);
                ulRspResult |= ulResult ;
                FC_MNTN_TracePointFcEvent(ID_FC_MNTN_ACORE_CRESET_START_FC, pFcPoint, VOS_TRUE, ulResult);
            }
        }
    }
    else if ( FC_ACORE_CRESET_AFTER_RESET == enCResetMoment )
    {
        usMsgName           = ID_FC_ACORE_CRESET_END_RSP;
    }
    else
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetProc, enCResetMoment invalid !\n");
        return VOS_ERR;
    }

    /* 申请消息内存: */
    pstMsg = (FC_ACORE_CRESET_RSP_STRU *) VOS_AllocMsg( UEPS_PID_FLOWCTRL_A,
        sizeof(FC_ACORE_CRESET_RSP_STRU) - VOS_MSG_HEAD_LENGTH );

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetProc, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    /*填写消息内容:*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL_A;
    pstMsg->usMsgName       = usMsgName;
    pstMsg->ulResult        = ulRspResult;

    /*发送消息:*/
    (VOS_VOID)VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_ACORE_CResetRcvStartRsp
 功能描述  : 收到ID_FC_ACORE_CRESET_START_RSP消息后的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月22日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_ACORE_CResetRcvStartRsp(VOS_VOID)
{
    VOS_SmV(g_ulFcACoreCResetDoneSem);

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
