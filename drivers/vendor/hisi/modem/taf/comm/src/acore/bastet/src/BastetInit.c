
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "BastetInit.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_BST_INIT_C
/*lint +e767*/

RECV_MSG_PROC pRecvMsgProc = NULL;

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID BASTET_CommRegRecvCallBack(RECV_MSG_PROC pFunc)
{
    pRecvMsgProc = pFunc;
}

/*****************************************************************************
 函 数 名  : BASTET_CommPidInit
 功能描述  : BASTET消息处理PID初始化
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日
    作    者   : 彭钰/00188486
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 BASTET_CommPidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : BASTET_CommProcMsg
 功能描述  : BASTET消息处理
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日
    作    者   : 彭钰/00188486
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID BASTET_CommProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    if (NULL != pRecvMsgProc)
    {
        pRecvMsgProc(pMsg);
    }
}

/*****************************************************************************
 函 数 名  : BASTET_CommFidInit
 功能描述  : BASTET处理任务初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日
    作    者   : 彭钰/00188486
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 BASTET_CommFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* 上行PID初始化 */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_BASTET_COMM,
                                         (Init_Fun_Type)BASTET_CommPidInit,
                                         (Msg_Fun_Type)BASTET_CommProcMsg);

            if (VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
            /* 任务优先级 */
            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_BASTET_COMM, VOS_PRIORITY_P4);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
            break;

        case VOS_IP_FARMALLOC:
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

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
