
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcCtx.c
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年03月03日
  最近修改   :
  功能描述   : CC CTX文件
  函数列表   :

  修改历史   :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcCtx.h"

#include "NasCcProcNvim.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_CC_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* CC CTX,用于保存CC上下文 */
NAS_CC_CONTEXT_STRU                    g_stNasCcCtx;


/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_CC_GetCcCtx
 功能描述  : 获取当前CC的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前CC的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : s62952
   修改内容   : 新生成函数

*****************************************************************************/
NAS_CC_CONTEXT_STRU*  NAS_CC_GetCcCtx( VOS_VOID )
{
    return &(g_stNasCcCtx);
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetCustomCfgInfo
 功能描述  : 获取CC中保存特性定制特性信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CC中保存特性定制特性信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : s62952
   修改内容   : 新生成函数

*****************************************************************************/
NAS_CC_CUSTOM_CFG_INFO_STRU* NAS_CC_GetCustomCfgInfo( VOS_VOID )
{
    return &(NAS_CC_GetCcCtx()->stMsCfgInfo.stCustomCfg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetProceedingStartT310Flag
 功能描述  : 设置是否启动T310的标志
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月10日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_SetProceedingStartT310Flag(VOS_UINT8 ucFlag)
{
    NAS_CC_GetCustomCfgInfo()->ucProceedingStartT310Flag = ucFlag;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetProceedingStartT310Flag
 功能描述  : 获取启动T310的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月10日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_CC_GetProceedingStartT310Flag(VOS_VOID)
{
    return NAS_CC_GetCustomCfgInfo()->ucProceedingStartT310Flag;
}


/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchHoldState
 功能描述  : 获取CC模块补充业务切换HOLD操作状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_CC_SS_SWITCH_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
NAS_CC_SS_SWITCH_STATE_ENUM_UINT8 NAS_CC_GetSsSwitchHoldState(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.enHoldState;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchRetrieveState
 功能描述  : 获取CC模块补充业务切换RETRIEVE操作状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_CC_SS_SWITCH_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
NAS_CC_SS_SWITCH_STATE_ENUM_UINT8 NAS_CC_GetSsSwitchRetrieveState(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.enRetrieveState;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchHoldEntityID
 功能描述  : 获取CC模块补充业务切换HOLD实体ID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_CC_ENTITY_ID_T
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
NAS_CC_ENTITY_ID_T NAS_CC_GetSsSwitchHoldEntityID(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.ulHoldEntityID;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchRetrieveEntityID
 功能描述  : 获取CC模块补充业务切换RETRIEVE实体ID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_CC_ENTITY_ID_T
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
NAS_CC_ENTITY_ID_T NAS_CC_GetSsSwitchRetrieveEntityID(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.ulRetrieveEntityID;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchHoldCause
 功能描述  : 获取CC模块补充业务切换HOLD原因值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013/7/16
    作    者   : l00198894
    修改内容   :
*****************************************************************************/
NAS_CC_CAUSE_VALUE_ENUM_U32 NAS_CC_GetSsSwitchHoldCause(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.enHoldCause;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchRetrieveCause
 功能描述  : 获取CC模块补充业务切换RETRIEVE原因值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013/7/16
    作    者   : l00198894
    修改内容   :
*****************************************************************************/
NAS_CC_CAUSE_VALUE_ENUM_U32 NAS_CC_GetSsSwitchRetrieveCause(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.enRetrieveCause;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetSsSwitchHoldInfo
 功能描述  : 设置CC模块补充业务切换HOLD信息
 输入参数  : ulEntityID     -- 呼叫实体ID
             enState        -- 补充业务切换状态
             enCause        -- 原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID NAS_CC_SetSsSwitchHoldInfo(
    NAS_CC_ENTITY_ID_T                  ulEntityID,
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enState,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    g_stNasCcCtx.stSsControl.stSwitchInfo.ulHoldEntityID    = ulEntityID;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enHoldState       = enState;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enHoldCause       = enCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetSsSwitchRetrieveInfo
 功能描述  : 设置CC模块补充业务切换RETRIEVE信息
 输入参数  : ulEntityID     -- 呼叫实体ID
             enState        -- 补充业务切换状态
             enCause        -- 原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID NAS_CC_SetSsSwitchRetrieveInfo(
    NAS_CC_ENTITY_ID_T                  ulEntityID,
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enState,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    g_stNasCcCtx.stSsControl.stSwitchInfo.ulRetrieveEntityID  = ulEntityID;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enRetrieveState     = enState;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enRetrieveCause     = enCause;

    return;
}

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */
/*****************************************************************************
 函 数 名  : NAS_CC_SetSsSwitchHoldEntityID
 功能描述  : 设置CC模块补充业务切换HOLD的呼叫实体ID
 输入参数  : ulEntityID     -- 呼叫实体ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID NAS_CC_SetSsSwitchHoldEntityID(NAS_CC_ENTITY_ID_T ulEntityID)
{
    g_stNasCcCtx.stSsControl.stSwitchInfo.ulHoldEntityID    = ulEntityID;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetSsSwitchRetrieveEntityID
 功能描述  : 设置CC模块补充业务切换RETRIEVE的呼叫实体ID
 输入参数  : ulEntityID     -- 呼叫实体ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID NAS_CC_SetSsSwitchRetrieveEntityID(NAS_CC_ENTITY_ID_T ulEntityID)
{
    g_stNasCcCtx.stSsControl.stSwitchInfo.ulRetrieveEntityID  = ulEntityID;

    return;
}
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchOpFacility
 功能描述  : 获取CC模块补充业务切换是否保存了网络下发的FACILITY信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_UINT8 NAS_CC_GetSsSwitchOpFacility(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpFacility;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetSsSwitchOpFacility
 功能描述  : 设置CC模块补充业务切换是否保存了网络下发的FACILITY信息
 输入参数  : ulOpFlg    -- 是否保存了网络下发的FACILITY信息
             pstFacilityMsg -- FACILITY消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID NAS_CC_SetSsSwitchOpFacility(
    VOS_UINT32                          ulOpFlg,
    NAS_CC_MSG_FACILITY_MT_STRU        *pstFacilityMsg
)
{
    if (VOS_FALSE == ulOpFlg)
    {
        PS_MEM_SET(&(g_stNasCcCtx.stSsControl.stSwitchInfo.stFacility),
                   0,
                   sizeof(NAS_CC_MSG_FACILITY_MT_STRU));

        g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpFacility = VOS_FALSE;
    }
    else
    {
        PS_MEM_CPY(&(g_stNasCcCtx.stSsControl.stSwitchInfo.stFacility),
                   pstFacilityMsg,
                   sizeof(g_stNasCcCtx.stSsControl.stSwitchInfo.stFacility));

        g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpFacility = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchFacility
 功能描述  : 获取CC模块补充业务切换保存的网络下发的FACILITY信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_CC_MSG_FACILITY_MT_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
NAS_CC_MSG_FACILITY_MT_STRU* NAS_CC_GetSsSwitchFacility(VOS_VOID)
{
    return &(g_stNasCcCtx.stSsControl.stSwitchInfo.stFacility);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetSsSwitchInvokeId
 功能描述  : 设置CC模块补充业务切换保存的InvokeId
 输入参数  : ucFlg          -- 标志位，用于标示设置还是清除InvokeId
             ucInvokeId     -- 需要保存的InvokeId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID NAS_CC_SetSsSwitchInvokeId(
    VOS_UINT8                           ucFlg,
    VOS_UINT8                           ucInvokeId
)
{
    if (VOS_FALSE == ucFlg)
    {
        g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpInvokeId  = VOS_FALSE;
        g_stNasCcCtx.stSsControl.stSwitchInfo.ucInvokeId    = NAS_CC_INVALID_INVOKE_ID;
    }
    else
    {
        g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpInvokeId  = VOS_TRUE;
        g_stNasCcCtx.stSsControl.stSwitchInfo.ucInvokeId    = ucInvokeId;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchOpInvokeId
 功能描述  : 获取CC模块补充业务切换是否保存了InvokeId
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_UINT8 NAS_CC_GetSsSwitchOpInvokeId(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpInvokeId;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetSsSwitchInvokeId
 功能描述  : 获取CC模块补充业务切换保存的InvokeId
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_UINT8 NAS_CC_GetSsSwitchInvokeId(VOS_VOID)
{
    return g_stNasCcCtx.stSsControl.stSwitchInfo.ucInvokeId;
}

/*****************************************************************************
 函 数 名  : NAS_CC_InitSsSwitchInfo
 功能描述  : 初始化CC模块补充业务切换信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID NAS_CC_InitSsSwitchInfo(VOS_VOID)
{
    PS_MEM_SET(&g_stNasCcCtx.stSsControl.stSwitchInfo, 0, sizeof(NAS_CC_SS_SWITCH_INFO_STRU));

    g_stNasCcCtx.stSsControl.stSwitchInfo.ulHoldEntityID        = NAS_CC_INVALID_ENTITY_ID;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enHoldState           = NAS_CC_SS_SWITCH_IDLE;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enHoldCause           = NAS_CC_CAUSE_NULL;
    g_stNasCcCtx.stSsControl.stSwitchInfo.ulRetrieveEntityID    = NAS_CC_INVALID_ENTITY_ID;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enRetrieveState       = NAS_CC_SS_SWITCH_IDLE;
    g_stNasCcCtx.stSsControl.stSwitchInfo.enRetrieveCause       = 0;
    g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpFacility          = VOS_FALSE;
    g_stNasCcCtx.stSsControl.stSwitchInfo.ucOpInvokeId          = VOS_FALSE;
    g_stNasCcCtx.stSsControl.stSwitchInfo.ucInvokeId            = NAS_CC_INVALID_INVOKE_ID;

    return;
}
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

/*****************************************************************************
 函 数 名  : NAS_CC_GetCachMsgBufferAddr
 功能描述  : 获取当前的缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS CC缓存消息队列
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月22日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
NAS_CC_MSG_QUEUE_STRU* NAS_CC_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(g_stNasCcCtx.stBufferEntryMsgQueue);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SaveCacheMsgInMsgQueue
 功能描述  : 将缓存消息保存的缓存内存池中
 输入参数  : ulEventType:消息ID+PID
             pMsg      :消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : b00269685
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_CC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_CC_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = NAS_CC_GetCachMsgBufferAddr();

    if (pstMsgQueue->ucCacheMsgNum >= NAS_CC_MAX_MSG_QUEUE_NUM)
    {
        NAS_CC_ERR_LOG("NAS_CC_SaveCacheMsgInMsgQueue:No Empty buffer");

        NAS_CC_LogBufferQueueMsg(VOS_TRUE);

        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    NAS_CC_LogBufferQueueMsg(VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SaveCacheMsg
 功能描述  : 保存当前需要处理的缓存
 输入参数  : ulEventType:消息ID+PID
             pMsg      :消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月20日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_CC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if (pstMsgHeader->ulLength >= (NAS_CC_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH))
    {
        NAS_CC_ERR_LOG("NAS_CC_SaveCacheMsg:Len too Long");

        return;
    }

    NAS_CC_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ClearCacheMsg
 功能描述  : 清除第一条指定的缓存消息
 输入参数  : ulEventType:清除需求缓存的消息类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月22日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    NAS_CC_MSG_QUEUE_STRU              *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = NAS_CC_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* 先找到需要被清除的缓存 */
    for (i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        if (ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            cCachePos = (VOS_INT8)i;
        }
    }

    /* 未找到该消息类型直接返回 */
    if (-1 == cCachePos)
    {
        NAS_CC_INFO_LOG("NAS_CC_ClearCacheMsg:invalid msg type");

        return;
    }

    /* 为保证先入先出,需要将后面的消息移到前面 */
    for (i = cCachePos; i < (pstMsgQueue->ucCacheMsgNum - 1); i++)
    {
        /* COPY消息内容 */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(NAS_CC_ENTRY_MSG_STRU));

    }

    /* 将缓存个数减一 */
    pstMsgQueue->ucCacheMsgNum--;

    /* 将当前缓存给打印出来 */
    NAS_CC_LogBufferQueueMsg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ClearSpecEventTypeCacheMsg
 功能描述  : 清除所有指定的缓存消息
 输入参数  : ulEventType:清除需求缓存的消息类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月22日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_CC_ClearSpecEventTypeCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    NAS_CC_MSG_QUEUE_STRU              *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            j;

    pstMsgQueue = NAS_CC_GetCachMsgBufferAddr();

    /* 先找到需要被清除的缓存 */
    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        if (ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            for (j = i; j < (pstMsgQueue->ucCacheMsgNum - 1); j++)
            {
                /* COPY消息内容到前一个 */
                PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[j].stMsgEntry),
                           &(pstMsgQueue->astMsgQueue[j + 1].stMsgEntry),
                           sizeof(NAS_CC_ENTRY_MSG_STRU));

            }

            /* 将缓存个数减一 */
            pstMsgQueue->ucCacheMsgNum--;
        }
    }

    /* 将当前缓存给打印出来 */
    NAS_CC_LogBufferQueueMsg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ClearAllCacheMsg
 功能描述  : 清除所有的缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月22日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_ClearAllCacheMsg(VOS_VOID)
{
    NAS_CC_MSG_QUEUE_STRU              *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                = NAS_CC_GetCachMsgBufferAddr();

    pstMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < NAS_CC_MAX_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   0x00,
                   sizeof(NAS_CC_ENTRY_MSG_STRU));
    }

    NAS_CC_LogBufferQueueMsg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetNextSpecEventTypeCachedMsg
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  : pstEntryMSg:当前优先级最高的缓存消息
 返 回 值  : VOS_OK:获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月22日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_CC_GetNextSpecEventTypeCachedMsg(
    VOS_UINT32                          ulEventType,
    NAS_CC_ENTRY_MSG_STRU              *pstEntryMsg
)
{
    NAS_CC_MSG_QUEUE_STRU              *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue = NAS_CC_GetCachMsgBufferAddr();

    if (0 == pstMsgQueue->ucCacheMsgNum)
    {
        NAS_CC_ERR_LOG("NAS_CC_GetNextSpecEventTypeCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        if (ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            /* 按照先入先出原则,默认取第1个指定消息的缓存内容 */
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(NAS_CC_ENTRY_MSG_STRU));

            /* 消息已经取出则清除当前缓存 */
            NAS_CC_ClearCacheMsg(pstEntryMsg->ulEventType);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_CC_GetErrLogRingBufAddr
 功能描述  : 获取CC层RING BUFFER的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CC层RING BUFFER的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
OM_RING_ID NAS_CC_GetErrLogRingBufAddr(VOS_VOID)
{
    return g_stNasCcCtx.stErrlogInfo.stBuffInfo.pstRingBuffer;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetErrLogRingBufAddr
 功能描述  : 设置CC层RING BUFFER的地址
 输入参数  : RING BUFFER的地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer)
{
    g_stNasCcCtx.stErrlogInfo.stBuffInfo.pstRingBuffer = pRingBuffer;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetErrlogCtrlFlag
 功能描述  : 获取ERRLOG打开和关闭的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG打开和关闭的标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_CC_GetErrlogCtrlFlag(VOS_VOID)
{
    return g_stNasCcCtx.stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetErrlogCtrlFlag
 功能描述  : 设置ERRLOG打开和关闭的标识
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_SetErrlogCtrlFlag(VOS_UINT8 ucFlag)
{
    g_stNasCcCtx.stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetErrlogAlmLevel
 功能描述  : 获取ERRLOG打开和关闭的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG打开和关闭的标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_CC_GetErrlogAlmLevel(VOS_VOID)
{
    return g_stNasCcCtx.stErrlogInfo.stCtrlInfo.usAlmLevel;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetErrlogAlmLevel
 功能描述  : 设置ERRLOG打开和关闭的标识
 输入参数  : usAlmLevel
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel)
{
    g_stNasCcCtx.stErrlogInfo.stCtrlInfo.usAlmLevel = usAlmLevel;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetErrlogOverflowCnt
 功能描述  : 获取Ringbuf溢出的次数
 输入参数  : VOS_UINT32
 输出参数  : 无
 返 回 值  : Ringbuf溢出的次数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_CC_GetErrlogOverflowCnt(VOS_VOID)
{
    return g_stNasCcCtx.stErrlogInfo.stBuffInfo.ulOverflowCnt;
}

/*****************************************************************************
 函 数 名  : NAS_CC_SetErrlogOverflowCnt
 功能描述  : 设置Ringbuf溢出的次数
 输入参数  : Ringbuf溢出的次数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt)
{
    g_stNasCcCtx.stErrlogInfo.stBuffInfo.ulOverflowCnt = ulOverflowCnt;

    return;
}

/*lint -e593 -e830*/

/*****************************************************************************
 函 数 名  : NAS_CC_InitErrLogInfo
 功能描述  : 创建RING BUFFER
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_InitErrLogInfo(VOS_VOID)
{
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRingbuffer;

    /* en_NV_Item_ErrLogCtrlInfo */
    NAS_CC_ReadErrlogCtrlInfoNvim();

    /* 申请cache的动态内存 , 长度加1是因为读和写指针之间在写满时会相差一个字节 */
    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_CC, NAS_CC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
        NAS_CC_SetErrLogRingBufAddr(VOS_NULL_PTR);
        return;
    }

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, NAS_CC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_CC, pbuffer);
    }

    /* 保存ringbuffer指针 */
    NAS_CC_SetErrLogRingBufAddr(pRingbuffer);

    NAS_CC_SetErrlogOverflowCnt(0);

    return;

}
/*lint +e593 +e830*/

/*****************************************************************************
 函 数 名  : NAS_CC_PutErrLogRingBuf
 功能描述  : RING BUFFER写操作
 输入参数  : pbuffer:需要写入的内容
             lbytes :写入内容的长度
 输出参数  : 无
 返 回 值  : 实际写入的大小，如果BUFFER空间不够则返回0
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_CC_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pTafRingBuffer;

    pTafRingBuffer = NAS_CC_GetErrLogRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    /* 如果写入比RING BUFFER还大则不写入 */
    if (ulbytes > TAF_SDC_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pTafRingBuffer);

    ulCount = NAS_CC_GetErrlogOverflowCnt();

    /* 如果剩余空间不足写入的大小，则清空RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        NAS_CC_SetErrlogOverflowCnt(ulCount);

        OM_RingBufferFlush(pTafRingBuffer);
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetErrLogRingBufContent
 功能描述  : RING BUFFER读操作操作
 输入参数  : pbuffer: 读出来存放的空间
             ulbytes: 读取的最大值
 输出参数  : 无
 返 回 值  : 实际读取的大小，如果RINGBUFFER为空，则返回0
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_CC_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_CC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGet(NAS_CC_GetErrLogRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetErrLogRingBufferUseBytes
 功能描述  : RING BUFFER中有多少数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 实际RING BUFFER中数据大小
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_CC_GetErrLogRingBufferUseBytes(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_CC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferNBytes(NAS_CC_GetErrLogRingBufAddr());
}

/*****************************************************************************
 函 数 名  : NAS_CC_CleanErrLogRingBuf
 功能描述  : 清空RINGBUFFER中的数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_CC_CleanErrLogRingBuf(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_CC_GetErrLogRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(NAS_CC_GetErrLogRingBufAddr());

    return;
}


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



