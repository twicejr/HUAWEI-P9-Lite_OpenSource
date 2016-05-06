/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasMain.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月27日
  功能描述   : 实现CDMA（包括1x与evdo）模块FID初始化，注册以及各PID的注册
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasMain.h"
#include "CnasXsdMain.h"
#include "CnasXregMain.h"
#include "CnasXccMain.h"
#include "CnasMntn.h"
#include "CnasCcb.h"
#include "CnasPrlApi.h"
#include "CnasHluMain.h"

#include "CnasHsdMain.h"

#include  "CnasHsmMain.h"

#include "CnasEhsmMain.h"

#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_INTERNAL_MSG_CTX_STRU              g_stCnasIntCtxInfo;

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : CNAS_GetIntMsgCtxAddr
 功能描述  : 获取CNAS上下文数据结构首地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_INTERNAL_MSG_CTX_STRU *
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新增获取内部消息缓存队列的指针
*****************************************************************************/
CNAS_INTERNAL_MSG_CTX_STRU *CNAS_GetIntMsgCtxAddr(VOS_VOID)
{
    return &(g_stCnasIntCtxInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_InitIntMsgCtx
 功能描述  : 初始化CNAS内部消息上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新增获取内部消息缓存队列的指针
*****************************************************************************/
VOS_VOID CNAS_InitIntMsgCtx(VOS_VOID)
{
    CNAS_INTERNAL_MSG_CTX_STRU         *pstInternalMsgCtx = VOS_NULL_PTR;

    /* 初始化CNAS内部消息队列 */
    pstInternalMsgCtx                   = CNAS_GetIntMsgCtxAddr();
    CNAS_InitIntMsgBuf(pstInternalMsgCtx);

}

/*****************************************************************************
 函 数 名  : CNAS_InitIntMsgBuf
 功能描述  : 初始化内部消息队列
 输入参数  : CNAS_INTERNAL_MSG_CTX_STRU    *pstInternalMsgCtx
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新增获取内部消息缓存队列的指针
 2.日    期   : 2015年09月06日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_VOID CNAS_InitIntMsgBuf(
    CNAS_INTERNAL_MSG_CTX_STRU         *pstInternalMsgCtx
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    VOS_UINT32                          i;

    for (i = 0; i < CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE; i++)
    {
        pstInternalMsgCtx->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstInternalMsgCtx->ucIntMsgNum = 0;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */
}

/*****************************************************************************
 函 数 名  : CNAS_GetIntMsgSendBuf
 功能描述  : 从内部消息缓存队列中获取内部消息发送缓冲区
 输入参数  : ulMsgID  -- 请求缓存消息的ID
             ulBufLen -- 请求缓存消息长度
 输出参数  : 无
 返 回 值  : CNAS_INTERNAL_MSG_BUF_STRU *
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新增获取内部消息缓存队列的指针
 2.日    期   : 2015年09月06日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_VOID *CNAS_GetIntMsgSendBuf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulBufLen
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    VOS_VOID         *pstSendMsgBuf = VOS_NULL_PTR;

    pstSendMsgBuf = PS_MEM_ALLOC(ulModuleId, ulBufLen);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

    return pstSendMsgBuf;
}

/*****************************************************************************
 函 数 名  : CNAS_SndInternalMsg
 功能描述  : 发送内部消息
 输入参数  : pSndMsg:待发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年09月06日
    作    者   : w00176964
    修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_UINT32  CNAS_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    VOS_UINT8                           ucIntMsgNum;
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_GetIntMsgCtxAddr()->ucIntMsgNum;
    pstIntMsg   = (MSG_HEADER_STRU *)pSndMsg;

    /* 检查内部消息队列，是否有缓存队列已满 */
    if (CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE <= ucIntMsgNum)
    {
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pSndMsg);

        CNAS_ERROR_LOG(pstIntMsg->ulSenderPid, "CNAS_SndInternalMsg: msg queue is full!" );

        return VOS_FALSE;
    }

    /* 保存当前信息 */
    CNAS_GetIntMsgCtxAddr()->pastIntMsg[ucIntMsgNum] = pSndMsg;

    CNAS_GetIntMsgCtxAddr()->ucIntMsgNum = (ucIntMsgNum + 1);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_GetNextInternalMsg
 功能描述  : 获取内部消息队列中的下一条可用的内部消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 内部消息队列的指针
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年09月06日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_UINT8 *CNAS_GetNextInternalMsg(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_GetIntMsgCtxAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* 获取下一个缓存的消息消息 */
        pstIntMsg = CNAS_GetIntMsgCtxAddr()->pastIntMsg[0];

        /* 内部消息数目减少一个 */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* 前移内部消息 */
            NAS_MEM_MOVE_S(&(CNAS_GetIntMsgCtxAddr()->pastIntMsg[0]),
                           CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE * sizeof(VOS_UINT8 *),
                           &(CNAS_GetIntMsgCtxAddr()->pastIntMsg[1]),
                           ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* 对消息队列中尾部的消息清为空指针 */
        CNAS_GetIntMsgCtxAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_GetIntMsgCtxAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */
}

/* Deleted by w00176964 for CNAS内存裁剪, 2015-9-6, begin */

/* Deleted by w00176964 for CNAS内存裁剪, 2015-9-6, end */
/*****************************************************************************
 函 数 名  : CNAS_FindPidMsgProc
 功能描述  : 查找处理消息的PID函数
 输入参数  : ulRcvPid -- 接收消息ID
 输出参数  : 无
 返 回 值  : pCnasPidMsgProc -- 接收消息处理函数入口指针
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年02月4日
   作    者   : w00176964
   修改内容   : CDMA Iteration 8 Modified:增加HSM模块消息处理函数
*****************************************************************************/
pCnasPidMsgProc CNAS_FindPidMsgProc(
    VOS_UINT32                          ulRcvPid
)
{
    pCnasPidMsgProc                     pMsgProc = VOS_NULL_PTR;

    switch (ulRcvPid)
    {
        case UEPS_PID_XSD:
            pMsgProc = CNAS_XSD_MsgProc;
            break;

        case UEPS_PID_XREG:
            pMsgProc = CNAS_XREG_MsgProc;
            break;

        case UEPS_PID_XCC:
            pMsgProc = CNAS_XCC_MsgProc;
            break;

        case UEPS_PID_HLU:
            pMsgProc = CNAS_HLU_DispatchMsg;
            break;

        case UEPS_PID_HSD:
            pMsgProc = CNAS_HSD_MsgProc;
            break;

       case UEPS_PID_HSM:
           pMsgProc = CNAS_HSM_MsgProc;
           break;

        case UEPS_PID_EHSM:
            pMsgProc = CNAS_EHSM_MsgProcEntry;
            break;

        default:
            break;
    }

    return pMsgProc;
}

/*****************************************************************************
 函 数 名  : CNAS_FidMsgProc
 功能描述  : CDMA NAS层消息入口处理函数
 输入参数  : pRcvMsg -- 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE : 消息处理完成
             VOS_FALSE: 消息异常
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  CNAS_FidMsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    pCnasPidMsgProc                     pMsgProc  = VOS_NULL_PTR;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    /* 入口参数检查 */
    if (VOS_NULL_PTR == pRcvMsg)
    {
        /* 打印error信息 */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_FidMsgProc: pRcvMsg pointer is NULL!");
        return VOS_FALSE;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;
    CNAS_MNTN_LogMsgInfo(pstMsgHeader);

    pMsgProc = CNAS_FindPidMsgProc(pRcvMsg->ulReceiverPid);

    if (VOS_NULL_PTR == pMsgProc)
    {
        /* 打印error信息 */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_FidMsgProc: pMsgProc pointer is NULL!");

        return VOS_FALSE;
    }

    pMsgProc(pRcvMsg);

    //处理完消息后记录时间
    CNAS_MNTN_UpdateMsgExitTime();

    /* 获取CNAS内部队列消息 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    pstIntMsg = (MSG_HEADER_STRU *)CNAS_GetNextInternalMsg();
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* 消息勾包 */
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

        /* 获取消息处理函数指针 */
        pMsgProc = CNAS_FindPidMsgProc(pstIntMsg->ulReceiverPid);

        if (VOS_NULL_PTR != pMsgProc)
        {
            /* 处理消息 */
            pMsgProc((struct MsgCB *)pstIntMsg);
        }
        else
        {
            /* 打印error信息 */
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_FidMsgProc: pMsgProc pointer is NULL!");
        }

        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
        /* 释放内部消息 */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* 获取下一条CNAS内部队列消息 */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_GetNextInternalMsg();
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_InitTask
 功能描述  : CNAS模块任务初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : Y00213812
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  CNAS_InitTask(VOS_VOID)
{
    /* 初始化调试信息 */
    CNAS_MNTN_InitCtx();

    /* 初始化定时器 */
    CNAS_InitTimerCtx();

    /* 初始化CNAS内部队列 */
    CNAS_InitIntMsgCtx();

    /* 初始化CCB上下文 */
    CNAS_CCB_InitCcbCtx();

    /* 初始化PRL上下文 */
    CNAS_PRL_InitPrlCtx(VOS_TRUE);
}
#endif

/*****************************************************************************
 函 数 名  : CNAS_FidInit
 功能描述  : CDMA NAS层FID初始化函数
 输入参数  : enInitPhase:初始化阶段
 输出参数  : 无
 返 回 值  : VOS_TRUE : 初始化成功
             VOS_FALSE: 初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月27日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年02月4日
   作    者   : w00176964
   修改内容   : CDMA Iteration 8 Modified:增加HSM模块初始化
*****************************************************************************/
VOS_UINT32 CNAS_FidInit(enum VOS_INIT_PHASE_DEFINE enInitPhase)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32 ulReturnCode;

    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_XSD,
                                               (Init_Fun_Type)CNAS_XSD_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);
            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_XREG,
                                               (Init_Fun_Type)CNAS_XREG_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);
            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_XCC,
                                               (Init_Fun_Type)CNAS_XCC_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_HLU,
                                   (Init_Fun_Type)CNAS_HLU_InitPid,
                                   (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_HSD,
                                               (Init_Fun_Type)CNAS_HSD_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_HSM,
                                               (Init_Fun_Type)CNAS_HSM_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_EHSM,
                                               (Init_Fun_Type)CNAS_EHSM_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterTaskPrio(UEPS_FID_CNAS, CNAS_TASK_PRIO);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
            /* CNAS模块上下文初始化 */
            CNAS_InitTask();

            break;

        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;

    }
#endif

    return VOS_OK;
}
/*lint -restore*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



