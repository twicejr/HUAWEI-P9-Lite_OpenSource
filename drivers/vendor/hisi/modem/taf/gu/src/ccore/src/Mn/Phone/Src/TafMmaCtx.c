
/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaCtx.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年07月10日
  最近修改   :
  功能描述   : TAF MMA CTX文件
  函数列表   :

  修改历史   :
  1.日    期   : 2013年7月10日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "TafMmaCtx.h"
#include "TafMmaFsmMainTbl.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafLog.h"
#include "TafMmaSndInternalMsg.h"
#include "Taf_Tafm_Remote.h"
#include "TafMmaMntn.h"
#include "TafOamInterface.h"
#include "MmaUphyInterface.h"

#include "TafSdcLib.h"

#include "TafMmaFsmImsSwitchTbl.h"

#include "TafMmaFsmSysCfgTbl.h"
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
#include "TafCdmaPlusTranslate.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* MMA CTX,用于保存MMA状态机,描述表 */
TAF_MMA_CONTEXT_STRU                    g_stTafMmaCtx;

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_MMA_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
             pstMsg                 :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013-07-19
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理MMA入口消息的缓冲区地址 */
    pstEntryMsg                 = TAF_MMA_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_FSM_SetCurrState
 功能描述  : 设置当前需要迁移的状态
 输入参数  : ulCurrState:当前迁移的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = TAF_MMA_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的L1和L2状态 */
    TAF_MMA_LogFsmInfo();

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_FSM_GetFsmTopState
 功能描述  : 获取状态机顶层的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的顶层状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_FSM_GetFsmTopState( VOS_VOID )
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* 获取当前状态机 */
    pstCurFsm               = TAF_MMA_GetCurFsmAddr();
    ulState                 = pstCurFsm->ulState;

    return ulState;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetMmaCtxAddr
 功能描述  : 获取当前MMA的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前MMA的CTX地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_CONTEXT_STRU* TAF_MMA_GetMmaCtxAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetRegCtrlAddr
 功能描述  : 获取当前状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_FSM_CTX_STRU* TAF_MMA_GetCurFsmAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetFsmStackAddr
 功能描述  : 获取当前状态机栈地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机栈地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月13日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_FSM_STACK_STRU* TAF_MMA_GetFsmStackAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stFsmStack);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU* TAF_MMA_GetCurFsmDesc(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurrFsmMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_ENTRY_MSG_STRU* TAF_MMA_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurrFsmMsgAddr
 功能描述  : 获取当前状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_FSM_ID_ENUM_UINT32 TAF_MMA_GetCurrFsmId(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.enFsmId);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCachMsgBufferAddr
 功能描述  : 获取当前的缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF MMA缓存消息队列
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_MSG_QUEUE_STRU* TAF_MMA_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stBufferEntryMsgQueue);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_FSM_PushFsm
 功能描述  : 对状态机进行压栈
 输入参数  : *pstFsmStack:状态机栈
             *pstNewFsm:需要压入的状态机
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_FSM_PushFsm(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack,
    TAF_MMA_FSM_CTX_STRU                *pstNewFsm
)
{
    TAF_MMA_FSM_CTX_STRU                *pstCurFsm;

    if ( (VOS_NULL_PTR == pstFsmStack)
      || (VOS_NULL_PTR == pstNewFsm) )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                       "TAF_MMA_FSM_PushFsm,Para null ptr,pstFsmStack,pstNewFsm");

        return;
    }

    if ( pstFsmStack->usStackDepth >= TAF_MMA_MAX_STACK_DEPTH )
    {
        TAF_ERROR_LOG1(WUEPS_PID_MMA,
                       "TAF_MMA_FSM_PushFsm,Fsm Stack Depth Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    pstCurFsm               = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* 将当前状态机所有CTX都需要保存起来 */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(TAF_MMA_FSM_CTX_STRU));

    pstFsmStack->usStackDepth++;


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_FSM_PopFsm
 功能描述  : 对状态机进行出栈
 输入参数  : 无
             无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_FSM_PopFsm( VOS_VOID )
{
    VOS_UINT16                          usPopFsmPos;
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack                     = TAF_MMA_GetFsmStackAddr();
    pstCurFsm                       = TAF_MMA_GetCurFsmAddr();

    /* 栈已空 */
    if ( 0 == (pstFsmStack->usStackDepth) )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_FSM_PopFsm,FSM Stack empty");

        return;
    }

    pstFsmStack->usStackDepth--;
    usPopFsmPos   = pstFsmStack->usStackDepth;

    /* 设置当前状态机 */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[usPopFsmPos]),
              sizeof(TAF_MMA_FSM_CTX_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_LoadSubFsmInfo
 功能描述  : 加载L2状态机的信息
 输入参数  : enFsmId:L2状态机ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_VOID  TAF_MMA_LoadSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm
)
{
    switch ( enFsmId )
    {
        case TAF_MMA_FSM_PHONE_MODE :
            pstCurFsm->ulState                  = TAF_MMA_PHONE_MODE_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetPhoneModeFsmDescAddr();
            break;

#if (FEATURE_IMS == FEATURE_ON)
        case TAF_MMA_FSM_IMS_SWITCH :
            pstCurFsm->ulState                  = TAF_MMA_IMS_SWITCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetImsSwitchFsmDescAddr();
            break;
#endif

        case TAF_MMA_FSM_SYS_CFG :
            pstCurFsm->ulState                  = TAF_MMA_SYS_CFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetSysCfgFsmDescAddr();
            break;


        default:
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LoadSubFsm:Invalid Fsm Id");
            return;
    }


    /*执行初始化sub状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_FSM_InitSubFsm
 功能描述  : MMA启动一个L2或L3的状态机。启动流程的同时启动状态以及保护定时器?
              该函数会进行压栈操作,如果不需要进行协议栈压栈,必须保证退出前流程
 输入参数  : enFsmId:L2状态机ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_FSM_InitSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
)
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;


    pstCurFsm                           = TAF_MMA_GetCurFsmAddr();
    pstFsmStack                         = TAF_MMA_GetFsmStackAddr();

    /*  打印压栈前的main和sub状态 */
    TAF_MMA_LogFsmInfo();

    /* 将当前状态机压栈操作 */
    TAF_MMA_FSM_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId                  = enFsmId;

    /* 加载sub状态机 */
    TAF_MMA_LoadSubFsm(enFsmId, pstCurFsm);

    /*  打印当前的main和sub状态 */
    TAF_MMA_LogFsmInfo();
}


/*****************************************************************************
 函 数 名  : TAF_MMA_FSM_QuitSubFsm
 功能描述  : 结束L2状态机。如果结束流程，状态机弹出状态栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_FSM_QuitSubFsm( VOS_VOID )
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm                           = TAF_MMA_GetCurFsmAddr();

    /* QUIT时清空当前sub状态机的CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    /*  打印压栈前的main和sub状态 */
    TAF_MMA_LogFsmInfo();

    /* 状态机出栈操作 */
    TAF_MMA_FSM_PopFsm();

    /*  打印当前的main和sub状态 */
    TAF_MMA_LogFsmInfo();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetFsmStackDepth
 功能描述  : 获取当前协议栈的栈深度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的深度
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16  TAF_MMA_GetFsmStackDepth( VOS_VOID )
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsExistCacheMsg
 功能描述  : 判断当前消息是否已经缓存
 输入参数  : ulEventType:消息ID
 输出参数  : pulIndex   :缓存的消息索引
 返 回 值  : VOS_TRUE:存在缓存的消息
             VOS_FALSE:不存在缓存的消息
 调用函数  :pulIndex
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月30日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();
   *pulIndex                           = 0;

    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            *pulIndex   = i;
            return VOS_TRUE;
        }
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_IsExistCacheMsg:not match MSG");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedCacheMsg
 功能描述  : 比较缓存消息与当前消息的优先级
 输入参数  : ulEventType:消息类型
             pstMsg     :消息首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息不需要被缓存
             VOS_TRUE:消息需要被缓存
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月30日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsNeedCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                          ulIndex;

    switch (ulEventType)
    {
        /* 当前卡状态指示消息的缓存只需要缓存一条 */
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND):

            if (VOS_TRUE == TAF_MMA_IsExistCacheMsg(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND), &ulIndex))
            {
                return VOS_FALSE;
            }

            break;

        default:
            break;
    }

    /* 默认返回保存该消息 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SaveCacheMsgInMsgQueue
 功能描述  : 将缓存消息保存的缓存内存池中
 输入参数  : ulEventType:消息ID+PID
             pMsg      :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 保存成功
             VOS_FALSE -- 保存失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32 TAF_MMA_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = TAF_MMA_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= TAF_MMA_MAX_MSG_QUEUE_NUM )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:buffer full");

        TAF_MMA_LogBufferQueueMsg(VOS_TRUE);

        return VOS_FALSE;
    }

    /* 比较消息优先级,判断是否需要保存在缓存池中 */
    if (VOS_FALSE == TAF_MMA_IsNeedCacheMsg(ulEventType, pstMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:already exist msg");

        return VOS_FALSE;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    TAF_MMA_LogBufferQueueMsg(VOS_FALSE);

    TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ClearCacheMsg
 功能描述  : 清除指定的缓存消息
 输入参数  : ulEventType:清除需求缓存的消息类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* 先找到需要被清除的缓存 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            cCachePos = (VOS_INT8)i;
        }
    }

    /* 未找到该消息类型直接返回 */
    if ( -1 == cCachePos )
    {
        TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_ClearCacheMsg:invalid msg type", ulEventType);
        return;
    }

    /* 为保证先入先出,需要将后面的消息移到前面 */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY消息内容 */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(TAF_MMA_ENTRY_MSG_STRU));
    }

    /* 将缓存个数减一 */
    pstMsgQueue->ucCacheMsgNum--;

    /* 将当前缓存给打印出来 */
    TAF_MMA_LogBufferQueueMsg(VOS_FALSE);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_InitFsmCtx_PhoneMode
 功能描述  : 初始化手机模式状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  TAF_MMA_InitFsmCtx_PhoneMode(VOS_VOID)
{
    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_NO_ERROR);


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitFsmCtx_SysCfg
 功能描述  : 初始化SYS CFG状态机的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : DTS2015061601845:增加原始SYSCFG触发的操作类型
*****************************************************************************/
VOS_VOID  TAF_MMA_InitFsmCtx_SysCfg(VOS_VOID)
{
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;

    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    PS_MEM_SET(pstSysCfgCtx, 0 , sizeof(TAF_MMA_FSM_SYS_CFG_CTX_STRU));

    pstSysCfgCtx->usOperType   = 0;
    pstSysCfgCtx->ucAttachOpId = 0xFF;

    pstSysCfgCtx->usOrigOperType = 0;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitCurrFsmCtx
 功能描述  : 初始化当前状态机上下文
 输入参数  : 无
 输出参数  : pstCurrFsmCtx:当前状态机上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_InitCurrFsmCtx(
    TAF_MMA_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   TAF_MMA_FSM_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   TAF_MMA_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   TAF_MMA_MAIN_STA_IDLE;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               TAF_MMA_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitFsmStackCtx
 功能描述  : 初始化状态机栈上下文
 输入参数  : 无
 输出参数  : pstFsmStack:状态机栈信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_InitFsmStackCtx(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < TAF_MMA_MAX_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = TAF_MMA_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = TAF_MMA_MAIN_STA_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitInternalBuffer
 功能描述  : 清除内部缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_InitInternalBuffer(
    TAF_MMA_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(TAF_MMA_CACH_MSG_INFO_STRU)*TAF_MMA_MAX_MSG_QUEUE_NUM);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitInternalMsgQueue
 功能描述  : 初始化MMA_CTX中内部消息队列
 输入参数  : pstInternalMsgQueue:内部消息队列
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月19日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_InitInternalMsgQueue(
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MMA的内部消息队列 */
)
{
    VOS_UINT32                          i;

    pstInternalMsgQueue->ucHeader   = 0;
    pstInternalMsgQueue->ucTail     = 0;

    for ( i = 0 ; i < TAF_MMA_MAX_MSG_QUEUE_SIZE; i++ )
    {
        pstInternalMsgQueue->astMmaMsgQueue[i].usMsgID    = TAF_MMA_INVALID_INTERNAL_MSG_ID;
        PS_MEM_SET(pstInternalMsgQueue->astMmaMsgQueue[i].aucBuf,
                   0x00,
                   TAF_MMA_MAX_MSG_BUFFER_LEN);
    }

}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitMaintainInfo
 功能描述  : 初始化MMA_CTX中可维可测信息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月4日
   作    者   : s00217060
   修改内容   : 新生成函数

 2.日    期   : 2014年12月3日
   作    者   : w00167002
   修改内容   : 打印导致开机慢，默认不开启打印
*****************************************************************************/
VOS_VOID  TAF_MMA_InitMaintainInfo(
    TAF_MMA_MAINTAIN_CTX_STRU          *pstMaintainInfo
)
{
    pstMaintainInfo->ucMmaLogInfoFlag   = VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitExternalModuleInitStatus
 功能描述  : 初始化卡和物理层初始化状态
 输入参数  : 初始化状态指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年3月20日
   作    者   : y00176023
   修改内容   : 新生成函数
 2.日    期   : 2014年6月4日
   作    者   : w00167002
   修改内容   : DTS2014060403551:临时修改
 3.日    期   : 2014年7月22日
   作    者   : s00217060
   修改内容   : DTS2014072200696:Phy初始化
 4.日    期   : 2015年1月28日
   作    者   : s00217060
   修改内容   : DTS2015012808702修改，无条件等PHY初始化，否则可能会在搜网时，底层还未初始化完成，引起复位

*****************************************************************************/
VOS_VOID TAF_MMA_InitExternalModuleInitStatus(
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU      *pstInitStatusctx
)
{
    PS_MEM_SET(pstInitStatusctx, 0, sizeof(TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU));

    /* 无条件等待物理层初始化，不和DSDS宏绑定在一起 */
    pstInitStatusctx->enPhyInitStatus      = MMA_UPHY_INIT_STATUS_BUTT;

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPhoneModeCtrl
 功能描述  : 获取当前phone mode 控制上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : phone mode控制上下文
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013-07-12
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
TAF_MMA_PHONE_MODE_CTRL_CTX_STRU *TAF_MMA_GetPhoneModeCtrl(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stPhoneModeCtrl);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCacheNum
 功能描述  : 获取当前存在的缓存个数
 输入参数  : 无
 输出参数  : 当前存在的缓存个数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_GetCacheNum( VOS_VOID )
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCachedMsgPrio
 功能描述  : 获取缓存消息的优先级类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 缓存消息的优先级类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月22日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年9月8日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   TAF_MMA_GetCachedMsgPrio(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio;

    switch (pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ):
        case TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ):
        /* Modified by w00167002 for L-C互操作项目, 2014-2-14, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ):
        /* Modified by w00167002 for L-C互操作项目, 2014-2-14, end */

            enPrio = TAF_MMA_MSG_CACHE_PRIO_HIGH;
            break;

        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND):

            enPrio = TAF_MMA_MSG_CACHE_PRIO_MIDDLE;
            break;

        /* Modified by w00167002 for L-C互操作项目, 2014-2-14, begin */

        /* 查询预处理先返回了  */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        /* Modified by w00167002 for L-C互操作项目, 2014-2-14, end */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):

        /* Modified by w00167002 for L-C互操作项目, 2014-2-17, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
        /* Modified by w00167002 for L-C互操作项目, 2014-2-17, end */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ):

#if (FEATURE_ON == FEATURE_CSG)
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ):
#endif
        default:

            enPrio = TAF_MMA_MSG_CACHE_PRIO_LOW;
            break;
    }

    return enPrio;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetNextPrioCachedMsg
 功能描述  : 获取下条优先级的缓存消息
 输入参数  : 无
 输出参数  : pstEntryMSg:当前优先级的缓存消息
 返 回 值  : VOS_TRUE:获取成功
             VOS_FALSE:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_MMA_GetNextPrioCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        if (enPrio == TAF_MMA_GetCachedMsgPrio(&pstMsgQueue->astMsgQueue[i].stMsgEntry))
        {
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            /* 消息已经取出则清除当前缓存 */
            TAF_MMA_ClearCacheMsg(pstEntryMsg->ulEventType);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetNextCachedMsg
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  : pstEntryMSg:当前优先级最高的缓存消息
 返 回 值  : VOS_TRUE:获取成功
             VOS_FALSE:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月12日
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_MMA_GetNextCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    if (0 == pstMsgQueue->ucCacheMsgNum )
    {
        TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_HIGH))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_MIDDLE))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_LOW))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SetFsmStackPopFlg
 功能描述  : 设置状态机栈pop标志
 输入参数  : ucStackPopFlg:栈pop标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetFsmStackPopFlg
 功能描述  : 获取状态机栈pop标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  TAF_MMA_GetFsmStackPopFlg( VOS_VOID )
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetAutoInitPsFlg
 功能描述  : 更新上电自动初始化协议栈标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_SetAutoInitPsFlg(
    VOS_UINT32                          ulAutoInitPsFlg
)
{
    TAF_MMA_GetPhoneModeCtrl()->ulAutoInitPsFlg = ulAutoInitPsFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetAutoInitPsFlg
 功能描述  : 获取上电自动初始化协议栈标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_GetAutoInitPsFlg(VOS_VOID)
{
    return (TAF_MMA_GetPhoneModeCtrl()->ulAutoInitPsFlg);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetAutoSwitchOnFlg
 功能描述  : 更新上电自动开机标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_SetAutoSwitchOnFlg(
    VOS_UINT32                          ulAutoSwitchOnFlg
)
{
    TAF_MMA_GetPhoneModeCtrl()->ulAutoSwitchOnFlg = ulAutoSwitchOnFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetAutoSwitchOnFlg
 功能描述  : 获取上电自动开机标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_GetAutoSwitchOnFlg(VOS_VOID)
{
    return (TAF_MMA_GetPhoneModeCtrl()->ulAutoSwitchOnFlg);
}


/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_SetCurPhoneErrorCode_PhoneMode
 功能描述  : 设置当前开关机过程中的错误码
 输入参数  : usErrorCode--开关机的错误码
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月19日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_SetCurPhoneErrorCode_PhoneMode(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    /* 如果当前状态机不是PHONE MODE, 异常打印 */
    if (TAF_MMA_FSM_PHONE_MODE != TAF_MMA_GetCurrFsmId())
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SetCurPhoneErrorCode_PhoneMode,ERROR:FsmId Error");
        return;
    }

    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stPhoneModeCtx.enPhoneError = enErrorCode;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurPhoneErrorCode_PhoneMode
 功能描述  : 获取当前的开关机过程中的错误码
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月19日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
TAF_ERROR_CODE_ENUM_UINT32  TAF_MMA_GetCurPhoneErrorCode_PhoneMode(VOS_VOID)
{
    /* 如果当前状态机不是PHONE MODE, 异常打印 */
    if (TAF_MMA_FSM_PHONE_MODE != TAF_MMA_GetCurrFsmId())
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetCurPhoneErrorCode_PhoneMode,ERROR:FsmId Error");
    }
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stPhoneModeCtx.enPhoneError);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetTimerCtxAddr
 功能描述  : 获取MMA CTX模块中定时器的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MMA CTX模块中定时器的上下文指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_MMA_TIMER_CTX_STRU*  TAF_MMA_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->astMmaTimerCtx;
}

/* Added by b00269685 for L-C互操作项目, 2014-2-14, begin */

/*****************************************************************************
 函 数 名  : TAF_MMA_GetOperCtxAddr
 功能描述  : 获取MMA CTX模块中L-C互操作上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MMA CTX模块中L-C互操作上下文
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月14日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
TAF_MMA_OPER_CTX_STRU*  TAF_MMA_GetOperCtxAddr( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->astMmaOperCtx;
}


/* Added by b00269685 for L-C互操作项目, 2014-2-14, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_GetMmaLogInfoFlag
 功能描述  : 获取MMA CTX模块中可维可测信息是否打印标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MMA CTX模块中可维可测信息是否打印标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月4日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  TAF_MMA_GetMmaLogInfoFlag( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->stMaintainInfo.ucMmaLogInfoFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetMmaLogInfoFlag
 功能描述  : 设置MMA CTX模块中可维可测信息是否打印标志
 输入参数  : MMA CTX模块中可维可测信息是否打印标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月4日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_SetMmaLogInfoFlag(
    VOS_UINT8                           ucMmaLogInfoFlag
)
{
    TAF_MMA_GetMmaCtxAddr()->stMaintainInfo.ucMmaLogInfoFlag = ucMmaLogInfoFlag;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_SetNetworkCapabilityInfo
 功能描述  : 根据系统模式更新对应网络能力信息

 输入参数  : enSysMode －－ 系统模式

 输出参数  : 无
 返 回 值  : 返回网络能力信息参数

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月31日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年10月10日
   作    者   : w00176964
   修改内容   : VOLTE_PhaseII:修改函数名
*****************************************************************************/
VOS_VOID TAF_MMA_SetNetworkCapabilityInfo(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstNwCapInfo
)
{
    if (TAF_SDC_SYS_MODE_LTE == enSysMode)
    {
        TAF_SDC_SetLteNwCapInfo(pstNwCapInfo);
    }
    else
    {
        TAF_SDC_SetGuNwCapInfo(pstNwCapInfo);
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetPhyInitStatus
 功能描述  : 设置物理层初始化完成标志

 输入参数  : enFlag －－ 物理层初始化完成标志
                       MMA_UPHY_INIT_STATUS_SUCCESS
                       MMA_UPHY_INIT_STATUS_FAIL
                       MMA_UPHY_INIT_STATUS_BUTT

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年3月19日
   作    者   : y00176023
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SetPhyInitStatus(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enFlag
)
{
    TAF_MMA_GetMmaCtxAddr()->stMmaExternalModuleInitStatusCtx.enPhyInitStatus = enFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPhyInitStatus
 功能描述  : 获取物理层初始化完成标志

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 上报物理层初始化完成标志
                       MMA_UPHY_INIT_STATUS_SUCCESS
                       MMA_UPHY_INIT_STATUS_FAIL
                       MMA_UPHY_INIT_STATUS_BUTT
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年3月19日
   作    者   : y00176023
   修改内容   : 新生成函数
*****************************************************************************/
MMA_UPHY_INIT_STATUS_ENUM_UINT16 TAF_MMA_GetPhyInitStatus( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->stMmaExternalModuleInitStatusCtx.enPhyInitStatus;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_IsExternalModuleInitCompeleted
 功能描述  : 获取扩展模块时初始化完成标志

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 上报扩展模块初始化完成标志 1为TRUE 0为FALSE

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月02日
   作    者   : y00176023
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 TAF_MMA_IsExternalModuleInitCompeleted( VOS_VOID )
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enUsimstatus;
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enUphyInitStatus;

    enUsimstatus     = TAF_SDC_GetSimStatus();
    enUphyInitStatus = TAF_MMA_GetPhyInitStatus();

    if((TAF_SDC_USIM_STATUS_BUTT     == enUsimstatus)
    || (MMA_UPHY_INIT_STATUS_BUTT    == enUphyInitStatus))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/* Added by b00269685 for L-C互操作项目, 2014-2-13, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_IsOperTypeUsed
 功能描述  : 如果g_stTafMmaCtx.astMmaOperCtx里oper type类型结构正在被使用，
             回复成功和index
 输入参数  : enOperType

 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : b00269685
    修改内容   : L-C互操作项目
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsOperTypeUsed(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  enOperType是否正在被使用  */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        if ( (enOperType == pstMmaOperCtx[ulIndex].enOperType)
          && (VOS_TRUE   == pstMmaOperCtx[ulIndex].ucUsedFlag) )
        {
            /* 将当前OPER_CTX信息LOG出来 */
            TAF_MMA_LogOperCtxInfo();

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetSpecOperTypeIndex
 功能描述  : 如果g_stTafMmaCtx.astMmaOperCtx里oper type类型结构正在被使用，
             回复成功和index
 输入参数  : enOperType

 输出参数  : pucCtxIndex
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : b00269685
    修改内容   : L-C互操作项目
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetSpecOperTypeIndex(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                          *pucCtxIndex
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  enOperType是否正在被使用  */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        if ( (enOperType == pstMmaOperCtx[ulIndex].enOperType)
          && (VOS_TRUE   == pstMmaOperCtx[ulIndex].ucUsedFlag) )
        {
            *pucCtxIndex = (VOS_UINT8)ulIndex;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetUnusedOperCtxIndex
 功能描述  : 取得未被使用的CTX的索引
 输入参数  : 无

 输出参数  : pucCtxIndex
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : b00269685
    修改内容   : L-C互操作项目
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetUnusedOperCtxIndex(
    VOS_UINT8                          *pucCtxIndex
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  是否有空余的Ctx   */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        /* 找到了空余的CTX */
        if (VOS_FALSE == pstMmaOperCtx[ulIndex].ucUsedFlag)
        {
            *pucCtxIndex = (VOS_UINT8)ulIndex;

            return VOS_TRUE;
        }

    }

    /* 将当前OPER_CTX信息LOG出来 */
    TAF_MMA_LogOperCtxInfo();

    /* 没有找到空余的CTX */
    return VOS_FALSE;

}
/* Added by b00269685 for L-C互操作项目, 2014-2-13, end */

/* Added by b00269685 for L-C互操作项目, 2014-2-13, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SetOperCtx
 功能描述  : 设置相应的g_stTafMmaCtx.astMmaOperCtx
 输入参数  : stCtrl
             enOperType
             pucCtxIndex

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : b00269685
    修改内容   : L-C互操作项目
*****************************************************************************/
VOS_VOID TAF_MMA_SetOperCtx(
    TAF_MMA_CTRL_STRU                   stCtrl,
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                           ucCtxIndex
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstMmaOperCtx[ucCtxIndex].stCtrl.ucOpId     = stCtrl.ucOpId;
    pstMmaOperCtx[ucCtxIndex].stCtrl.usClientId = stCtrl.usClientId;
    pstMmaOperCtx[ucCtxIndex].stCtrl.ulModuleId = stCtrl.ulModuleId;
    pstMmaOperCtx[ucCtxIndex].enOperType        = enOperType;
    pstMmaOperCtx[ucCtxIndex].ucUsedFlag        = VOS_TRUE;

    /* 将当前OPER_CTX信息LOG出来 */
    TAF_MMA_LogOperCtxInfo();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ClearOperCtx
 功能描述  : 设置相应的g_stTafMmaCtx.astMmaOperCtx
 输入参数  : stCtrl
             enOperType
             pucCtxIndex

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : b00269685
    修改内容   : L-C互操作项目
*****************************************************************************/
VOS_VOID TAF_MMA_ClearOperCtx(
    VOS_UINT8                           ucCtxIndex
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    PS_MEM_SET(&(pstMmaOperCtx[ucCtxIndex]), 0, sizeof(TAF_MMA_OPER_CTX_STRU));

    pstMmaOperCtx[ucCtxIndex].ucUsedFlag = VOS_FALSE;
    pstMmaOperCtx[ucCtxIndex].enOperType = TAF_MMA_OPER_BUTT;

    /* 将当前OPER_CTX信息LOG出来 */
    TAF_MMA_LogOperCtxInfo();

    return;
}
/* Added by b00269685 for L-C互操作项目, 2014-2-13, end */


/*****************************************************************************
 函 数 名  : TAF_MMA_GetCFreqLockSetPara
 功能描述  : 获取FREQLOCK信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新增函数
*****************************************************************************/
TAF_MMA_CFREQ_LOCK_SET_PARA_STRU* TAF_MMA_GetCFreqLockSetPara(VOS_VOID)
{
    return &g_stTafMmaCtx.stCFreqLockValue;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitCFreqLockPara
 功能描述  : 初始化FREQLOCK信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MMA_InitCFreqLockPara(VOS_VOID)
{
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara;

    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();

    PS_MEM_SET(pstTafMmaCFreqLockPara, 0x0, sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

    return;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_SetSysCfgOperType_SysCfg
 功能描述  : SYS CFG状态机中设置SYS CFG的操作类型
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.usOperType = usOperType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SaveSysCfgOrigOperType_SysCfg
 功能描述  : 保存SYS CFG状态机中SYS CFG的原始操作类型
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SaveSysCfgOrigOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.usOrigOperType = usOperType;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetSysCfgOrigOperType_SysCfg
 功能描述  : 获取SYS CFG状态机中SYS CFG的原始操作类型
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetSysCfgOrigOperType_SysCfg(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.usOrigOperType);
}



/*****************************************************************************
 函 数 名  : TAF_MMA_SetSysCfgPara_SysCfg
 功能描述  : SYS CFG状态机中保存消息带的参数
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetSysCfgPara_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    PS_MEM_CPY(&(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgPara),
                pstSysCfgPara,
                sizeof(TAF_MMA_SYS_CFG_PARA_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetSysCfgPara_SysCfg
 功能描述  : 获取SYS CFG状态机中保存的配置参数
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SYS_CFG_PARA_STRU *TAF_MMA_GetSysCfgPara_SysCfg(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgPara);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetAttachOpId_SysCfg
 功能描述  : SYS CFG状态机中保存attach请求的opid
 输入参数  : VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetAttachOpId_SysCfg(
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.ucAttachOpId = ucOpId;

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MMA_GetUserSetLteBandAddr
 功能描述  : 获取用户设置的LTE频段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_USER_SET_PREF_BAND64 -- LTE band地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUserSetLteBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stUserSetBand.stUserSetLteBand);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetUeSupportLteBandAddr
 功能描述  : 获取UE支持的LTE频段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_USER_SET_PREF_BAND64 -- 返回UE的LTE频段
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUeSupportLteBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stUeBandCap.stUeSupportLteBand);
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_GetRatPrioListAddr
 功能描述  : 获取上次用户通过syscfg设置成功的接入技术和优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_MMA_RAT_ORDER_STRU -- 用户RAT优先列表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_MMA_RAT_ORDER_STRU *TAF_MMA_GetRatPrioListAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stRatPrioList);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetLastSyscfgSetAddr
 功能描述  : 获取上次用户通过syscfg设置成功的参数值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU -- 返回上次的系统配置参数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *TAF_MMA_GetLastSyscfgSetAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetSyscfgUserSetBandAddr
 功能描述  : 获取上次用户通过syscfg设置成功的频段内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_MMA_SYSCFG_USER_SET_BAND_STRU -- 返回上次的用户的频段设置
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_MMA_SYSCFG_USER_SET_BAND_STRU *TAF_MMA_GetSyscfgUserSetBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stUserSetBand);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetSyscfgUserSetRoamValue
 功能描述  : 获取上次用户通过syscfg设置漫游值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_MMA_ROAM_MODE_ENUM_UINT8 -- 返回上次的用户的漫游设置
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_MMA_ROAM_MODE_ENUM_UINT8 TAF_MMA_GetSyscfgUserSetRoamValue(VOS_VOID)
{
    return (g_stTafMmaCtx.stLastSyscfgSet.enRoam);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetUeSupportBandAddr
 功能描述  : 获取UE支持的频段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_MMA_UE_BAND_CAPA_ST -- 返回UE支持的频段能力
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_MMA_UE_BAND_CAPA_ST *TAF_MMA_GetUeSupportBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stUeBandCap);
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetAttachOpId
 功能描述  : 获取attach操作的op id
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetAttachOpId(VOS_VOID)
{
    TAF_MMA_CONTEXT_STRU               *pstMmaCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucOpId;

    pstMmaCtx = TAF_MMA_GetMmaCtxAddr();

    ucOpId = pstMmaCtx->stAttachInfo.ucAttachOpId;

    pstMmaCtx->stAttachInfo.ucAttachOpId++;

    pstMmaCtx->stAttachInfo.ucAttachOpId %= 0xFF;

    return ucOpId;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : TAF_MMA_GetCsgListAbortType
 功能描述  : 获取CSG LIST Abort类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CSG LIST Abort类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8 TAF_MMA_GetCsgListAbortType(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCsgListInfo.enCsgListAbortProc);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetCsgListAbortType
 功能描述  : 设置CSG LIST Abort类型
 输入参数  : enCsgListAbortType - CSG LIST Abort类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID TAF_MMA_SetCsgListAbortType(
    TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8                 enCsgListAbortType
)
{
    TAF_MMA_GetMmaCtxAddr()->stCsgListInfo.enCsgListAbortProc = enCsgListAbortType;
    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetCsgListCtxAddr
 功能描述  : 获取CSG LIST上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取CSG LIST上下文
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
TAF_MMA_CSG_LIST_CTX_STRU* TAF_MMA_GetCsgListCtxAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCsgListInfo);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitCsgListCtx
 功能描述  : 初始化CSG List上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID TAF_MMA_InitCsgListCtx(VOS_VOID)
{
    TAF_MMA_CSG_LIST_CTX_STRU          *pstCsgListCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstCsgListCtx = TAF_MMA_GetCsgListCtxAddr();

    PS_MEM_SET(pstCsgListCtx, 0x0, sizeof(pstCsgListCtx));

    pstCsgListCtx->enCsgListAbortProc = TAF_MMA_PLMN_LIST_ABORT_BUTT;

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_CSG_ID_LIST_NUM; ulIndex++)
    {
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mcc = TAF_SDC_INVALID_MCC;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mnc = TAF_SDC_INVALID_MNC;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].ulCsgId      = TAF_SDC_INVALID_CSG_ID_VALUE;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_GetGeoCtxAddr
 功能描述  : 获取获取国家码信息上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_GET_GEO_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_GET_GEO_CTX_STRU* TAF_MMA_GetGeoCtxAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stGetGeoInfo);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitGetGeoCtx
 功能描述  : 初始化获取国家码信息上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitGetGeoCtx(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx = TAF_MMA_GetGeoCtxAddr();

    PS_MEM_SET(pstGetGeoCtx, 0x0, sizeof(TAF_MMA_GET_GEO_CTX_STRU));

    pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag        = VOS_FALSE;
    pstGetGeoCtx->stGetGeoNvCfg.ucCcpuResetFlag        = VOS_FALSE;
    pstGetGeoCtx->stGetGeoNvCfg.aucReserved[0]         = 0;
    pstGetGeoCtx->stGetGeoNvCfg.aucReserved[1]         = 10;
    pstGetGeoCtx->stGetGeoNvCfg.ulGetGeoTimerLen       = TAF_MMA_GET_GEO_TIMER_DEFAULT_LEN;
    pstGetGeoCtx->stGetGeoNvCfg.ulGeoEffectiveTimeLen  = TAF_MMA_GEO_EFFECTIVE_TIME_DEFAULT_LEN;

    pstGetGeoCtx->ulGetGeoTickTime       = VOS_GetTick() / PRE_SECOND_TO_TICK;
    pstGetGeoCtx->stGeoPlmnId.ulMcc      = TAF_SDC_INVALID_MCC;
    pstGetGeoCtx->stGeoPlmnId.ulMnc      = TAF_SDC_INVALID_MNC;

    pstGetGeoCtx->ulGetGeoCdmaTickTime   = VOS_GetTick() / PRE_SECOND_TO_TICK;
    pstGetGeoCtx->stGeoCdmaLocInfo.ulMcc = TAF_SDC_INVALID_MCC;
    pstGetGeoCtx->stGeoCdmaLocInfo.lSid  = MMA_INVALID_SID;
    pstGetGeoCtx->stGeoCdmaLocInfo.lNid  = MMA_INVALID_NID;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetGeoCtxAddr
 功能描述  : 获取获取国家码信息上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_GET_GEO_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SET_DPLMN_CTX_STRU* TAF_MMA_GetSetDplmnCtxAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stSetDplmnCtx);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitSetDplmnCtx
 功能描述  : 初始化设置Dplmn的上下文信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月02日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitSetDplmnCtx(VOS_VOID)
{

    TAF_MMA_SET_DPLMN_CTX_STRU           *pstSetDplmnCtx = VOS_NULL_PTR;

    pstSetDplmnCtx = TAF_MMA_GetSetDplmnCtxAddr();

    PS_MEM_SET(pstSetDplmnCtx, 0x00, sizeof(TAF_MMA_SET_DPLMN_CTX_STRU));

    pstSetDplmnCtx->enApPresetDplmnScene = TAF_MMA_AP_PRESET_DPLMN_SCENE_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetDplmnUpdateScene
 功能描述  : 设置更新Dplmn的场景信息
 输入参数  : TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8                enApPresetDplmnScene
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月2日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetDplmnUpdateScene(
    TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8                enApPresetDplmnScene
)
{
    TAF_MMA_SET_DPLMN_CTX_STRU           *pstSetDplmnCtx = VOS_NULL_PTR;

    pstSetDplmnCtx = TAF_MMA_GetSetDplmnCtxAddr();

    pstSetDplmnCtx->enApPresetDplmnScene = enApPresetDplmnScene;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetDplmnUpdateScene
 功能描述  : 获取当前更新Dplmn的场景信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enApPresetDplmnScene 当前更新DPlmn的场景
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月2日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8 TAF_MMA_GetDplmnUpdateScene(VOS_VOID)
{
    TAF_MMA_SET_DPLMN_CTX_STRU           *pstSetDplmnCtx = VOS_NULL_PTR;

    pstSetDplmnCtx = TAF_MMA_GetSetDplmnCtxAddr();

    return pstSetDplmnCtx->enApPresetDplmnScene;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_InitGetHplmnInfo
 功能描述  : 初始化获取国家码信息上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitGetHplmnInfo(VOS_VOID)
{
    TAF_MMA_GET_HPLMN_STRU             *pstGetHplmnInfo = VOS_NULL_PTR;

    pstGetHplmnInfo = TAF_MMA_GetHplmnInfo();

    PS_MEM_SET(pstGetHplmnInfo, 0x0, sizeof(TAF_MMA_GET_HPLMN_STRU));

    pstGetHplmnInfo->ucHplmnMncLen          = 0;
    pstGetHplmnInfo->enWaitSimFileCnfFlg    = TAF_MMA_READ_USIM_FILE_FLG_NULL;
    pstGetHplmnInfo->ulEHplmnNum            = 0;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetHplmnInfo
 功能描述  : 获取hplmn信息
 输出参数  : 无
 返 回 值  : TAF_MMA_GET_HPLMN_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月16日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
TAF_MMA_GET_HPLMN_STRU *TAF_MMA_GetHplmnInfo(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stGetHplmnInfo);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitSdcIccId
 功能描述  : 初始化卡的IccId
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitSdcIccId( VOS_VOID )
{
    TAF_SDC_ICCID_INFO_STRU             *pstIccIdInfo   = VOS_NULL_PTR;

    pstIccIdInfo        = TAF_SDC_GetIccIdInfo();

    PS_MEM_SET(pstIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));

    pstIccIdInfo->ucLen = TAF_SDC_ICC_ID_MAX_NUM + 1;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsValidIccId
 功能描述  : 判断当前是否为有效
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsValidIccId( VOS_VOID )
{
    TAF_SDC_ICCID_INFO_STRU              stNullIccIdInfo;

    PS_MEM_SET(&stNullIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));
    stNullIccIdInfo.ucLen   = TAF_SDC_ICC_ID_MAX_NUM + 1;

    if (0 == PS_MEM_CMP(TAF_SDC_GetIccIdInfo(), &stNullIccIdInfo, sizeof(TAF_SDC_ICCID_INFO_STRU)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCfgGetGeoFlag
 功能描述  : 获取搜网优化优化2.0标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  TAF_MMA_GetCfgGetGeoFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCfgGetGeoFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetGeoTimerLen
 功能描述  : 获取地理位置定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetGeoTimerLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ulGetGeoTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetCcpuResetFlag
 功能描述  : 设置C核单独复位的标志
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetCcpuResetFlag(VOS_UINT8 ucCcpuResetFlag)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCcpuResetFlag = ucCcpuResetFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCcpuResetFlag
 功能描述  : 获取C核单独复位的标志
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetCcpuResetFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCcpuResetFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetGeoEffectiveTimeLen
 功能描述  : 获取国家码有效时长
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetGeoEffectiveTimeLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ulGeoEffectiveTimeLen;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsGeoValid
 功能描述  : 判断国家码是否有效
 输出参数  : 无
 返 回 值  : VOS_FALSE:无效
             VOS_TRUE:有效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsGeoValid(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCurrTickTime;
    VOS_UINT32                          ulGeoEffectiveTimeLen;
    VOS_UINT32                          ulIsPlmnIdValid;

    ulCurrTickTime          = VOS_GetTick() / PRE_SECOND_TO_TICK;
    ulGeoEffectiveTimeLen   = TAF_MMA_GetGeoEffectiveTimeLen();
    pstGetGeoCtx            = TAF_MMA_GetGeoCtxAddr();
    ulIsPlmnIdValid         = TAF_SDC_IsPlmnIdValid(&pstGetGeoCtx->stGeoPlmnId);

    /* get geo NV关闭时也认为无效 */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return VOS_FALSE;
    }

    /* 地理信息的PLMN无效或者超过有效时长，则认为国家码是无效的 */
    if ((VOS_FALSE == ulIsPlmnIdValid)
     || ((ulCurrTickTime - pstGetGeoCtx->ulGetGeoTickTime) > ulGeoEffectiveTimeLen))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedGetGeoNoSimStart
 功能描述  : 是否需要发起获取国家码的无卡开机
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : f00179208
    修改内容   : 新生成函数
  1.日    期   : 2015年12月28日
    作    者   : l00324781
    修改内容   : CL_MUTIMODE_OPTIMIZE修改，增加X模初搜
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedGetGeoNoSimStart(VOS_VOID)
{
    VOS_UINT8                           ucCfgGetGeoFlag;
    VOS_UINT8                           ucCcpuResetFlag;

    ucCfgGetGeoFlag  = TAF_MMA_GetCfgGetGeoFlag();
    ucCcpuResetFlag  = TAF_MMA_GetCcpuResetFlag();
#if (FEATURE_ON == FEATURE_LTE)
    /* 如果平台不支持L，则直接返回不支持 */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        if ((VOS_TRUE  == ucCfgGetGeoFlag)
         && (VOS_TRUE  != ucCcpuResetFlag))
        {
            return VOS_TRUE;
        }
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsPlatformSupport1x())
    {
        if ((VOS_TRUE  == ucCfgGetGeoFlag)
         && (VOS_TRUE  != ucCcpuResetFlag))
        {
            return VOS_TRUE;
        }
    }
#endif

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SetTestRoamFlag
 功能描述  : 设置测试标志
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月19日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetTestRoamFlag(VOS_UINT8 ucFlag)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[0] = ucFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetTestRoamFlag
 功能描述  : 获取测试标志
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月19日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetTestRoamFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[0];
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetWaitExtTimerLen
 功能描述  : 设置等待外部模块的定时器时长
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月19日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetWaitExtTimerLen(VOS_UINT8 ucLen)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[1] = ucLen;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetWaitExtTimerLen
 功能描述  : 获取等待外部模块的定时器时长
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月19日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetWaitExtTimerLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[1];
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetSrvAcqRatListAddr
 功能描述  : 获取业务触发搜网的网络模式列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月16日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SRV_ACQ_RAT_LIST_STRU* TAF_MMA_GetSrvAcqRatListAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stDsdsInfo.stSrvAcqRatList);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateSrvAcqRatList
 功能描述  : 更新业务触发搜网的网络模式列表
 输入参数  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月16日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSrvAcqRatList(
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
)
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatListAddr = VOS_NULL_PTR;

    pstSrvAcqRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    PS_MEM_CPY(pstSrvAcqRatListAddr, pstSrvAcqRatList, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ClearSrvAcqRatList
 功能描述  : 清除业务触发搜网的网络模式列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月18日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ClearSrvAcqRatList(VOS_VOID)
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatListAddr = VOS_NULL_PTR;

    pstSrvAcqRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    PS_MEM_SET(pstSrvAcqRatListAddr, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SetDelayReportServiceStatusFlg
 功能描述  : 设置当前是否启用了短暂掉网延时上报功能
 输入参数  : ucDelayReportServiceStatusFlg - 短暂掉网延时上报功能是否打开
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
 2.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 修改结构体
*****************************************************************************/
VOS_VOID TAF_MMA_SetDelayReportServiceStatusFlg(
    VOS_UINT8 ucDelayReportServiceStatusFlg
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ucEnable= ucDelayReportServiceStatusFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetDelayReportServiceStatusFlg
 功能描述  : 获取当前是否启用了短暂掉网延时上报功能
 输入参数  :
 输出参数  : 无
 返 回 值  : 短暂掉网延时上报功能是否开启的FLAG
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
 2.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 修改结构体
*****************************************************************************/
VOS_UINT8 TAF_MMA_GetDelayReportServiceStatusFlg(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ucEnable);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetDelayReportServiceStatusTimerLen
 功能描述  : 设置当前启用了短暂掉网延时上报功能的时长
 输入参数  : ulTimerLen -  时长，单位秒
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
 2.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 修改结构体
*****************************************************************************/
VOS_VOID TAF_MMA_SetDelayReportServiceStatusTimerLen(
    VOS_UINT32 ulTimerLen
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ulRptSrvStaDelayTimerValue = ulTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetDelayReportServiceStatusCfgTimerLen
 功能描述  : 获取当前启用了短暂掉网延时上报功能的时长
 输入参数  :
 输出参数  : 无
 返 回 值     :  时长，单位秒
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
 2.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : CDMA Iteration 18 修改结构体
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetDelayReportServiceStatusCfgTimerLen(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ulRptSrvStaDelayTimerValue);
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetCLNoServiceDelayRptInfo
 功能描述  : 获取CL模式延迟上报无服务信息
 输出参数  : 无
 返 回 值  : TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月7日
    作    者   : h00313353
    修改内容   : DTS2016010508602
*****************************************************************************/
TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU *TAF_MMA_GetCLNoServiceDelayRptInfo(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stCLNoServiceDelayRptInfo);
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MMA_SetCLDelayReptSrvStatusFlg
 功能描述  : 设置C模延迟上报使能标识
 输入参数  : ucCLDelayReptSrvStatusFlg - 设置C模延迟上报使能标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : C模服务状态优化项目新增
*****************************************************************************/
VOS_VOID TAF_MMA_SetCLDelayReptSrvStatusFlg(
    VOS_UINT8 ucCLDelayReptSrvStatusFlg
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ucClDelayRptEnable = ucCLDelayReptSrvStatusFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCLDelayReptSrvStatusFlg
 功能描述  : 获取C模延迟上报使能标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 使能标识，VOS_TRUE为开启,VOS_FALSE为关闭
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : C模服务状态优化项目新增
*****************************************************************************/
VOS_UINT8 TAF_MMA_GetCLDelayReptSrvStatusFlg(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ucClDelayRptEnable);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetCLDelayReptSrvStatusTimerLen
 功能描述  : 设置C模延迟上报定时器长度
 输入参数  : ulTimerLen - 需要设置的时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : C模服务状态优化项目新增
*****************************************************************************/
VOS_VOID TAF_MMA_SetCLDelayReptSrvStatusTimerLen(
    VOS_UINT32 ulTimerLen
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ulClRptSrvStaDelayTimerValue = ulTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCLDelayReptSrvStatusTimerLen
 功能描述  : 获取C模延迟上报定时器长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 延迟上报定时器时长，单位毫秒
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月30日
   作    者   : j00354216
   修改内容   : C模服务状态优化项目新增
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetCLDelayReptSrvStatusTimerLen(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ulClRptSrvStaDelayTimerValue);
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MMA_IsGeoCdmaLocValid
 功能描述  : 判断cdma的位置信息是否有效
 输出参数  : 无
 返 回 值  : VOS_FALSE:无效
             VOS_TRUE:有效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsGeoCdmaLocValid(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCurrTickTime;
    VOS_UINT32                          ulGeoEffectiveTimeLen;

    ulCurrTickTime          = VOS_GetTick() / PRE_SECOND_TO_TICK;
    ulGeoEffectiveTimeLen   = TAF_MMA_GetGeoEffectiveTimeLen();
    pstGetGeoCtx            = TAF_MMA_GetGeoCtxAddr();

    /* get geo NV关闭时也认为无效 */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return VOS_FALSE;
    }

    /* 如果Mcc是无效值，则认为整个Cdma的位置信息无效 */
    /* 从时间戳间隔判断，位置信息是否失效 */
    if ((TAF_SDC_INVALID_MCC == pstGetGeoCtx->stGeoCdmaLocInfo.ulMcc)
     || ((ulCurrTickTime - pstGetGeoCtx->ulGetGeoCdmaTickTime) > ulGeoEffectiveTimeLen))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateGeoCdmaLocInfo
 功能描述  : 更新GetGeo中1X的位置信息
 输入参数  : VOS_INT32     lSid   1x的位置信息
             VOS_INT32     lNid   1x的位置信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateGeoCdmaLocInfo(
    VOS_INT32                   lSid,
    VOS_INT32                   lNid
)
{
    TAF_MMA_GET_GEO_CTX_STRU            *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx        = TAF_MMA_GetGeoCtxAddr();

    /* get geo NV项关闭时不需要更新 */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return;
    }

    pstGetGeoCtx->stGeoCdmaLocInfo.lSid  = lSid;
    pstGetGeoCtx->stGeoCdmaLocInfo.lNid  = lNid;
    /* 使用Sid从g_astTafCountryList表中查找Mcc，如果查找不到，返回无效值，全F */
    pstGetGeoCtx->stGeoCdmaLocInfo.ulMcc = TAF_QueryMccWithSid(lSid);

    pstGetGeoCtx->ulGetGeoCdmaTickTime   = VOS_GetTick() / PRE_SECOND_TO_TICK;

    return;
}

#endif
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



