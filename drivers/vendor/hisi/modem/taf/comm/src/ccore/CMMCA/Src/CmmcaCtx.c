/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaCtx.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年01月08日
  最近修改   :
  功能描述   : CMMCA模块的上下文维护
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月08日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CmmcaCtx.h"
#include "CmmcaRegMgmt.h"
#include "CmmcaMntn.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_CTX_C
/*lint +e767 修改人: l60609; */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CMMCA_CTX_STRU                          g_stCmmcaCtx;


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CMMCA_REG_GetCtxAddr
 功能描述  : 获取REG上下文地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CMMCA_REG_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : S00261364
    修改内容   : 新生成函数

*****************************************************************************/
CMMCA_REG_CTX_STRU* CMMCA_REG_GetCtxAddr(VOS_VOID)
{
    return &g_stCmmcaCtx.stRegCtx;
}


/*****************************************************************************
 函 数 名  : CMMCA_REG_InitCtx
 功能描述  : 初始化REG相关的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : S00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_InitCtx(VOS_VOID)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx = VOS_NULL_PTR;

    /* 初始化全局变量g_stCmmcaCtx.stRegCtx */
    pstRegCtx = CMMCA_REG_GetCtxAddr();

    PS_MEM_SET(pstRegCtx, 0, sizeof(CMMCA_REG_CTX_STRU));

    /* 初始化漫游特性是否开启NV值 */
    CMMCA_REG_ReadRoamCfgInfoNvim();

    return;
}


/*****************************************************************************
 函 数 名  : CMMCA_REG_ReadRoamCfgInfoNvim
 功能描述  : 获取漫游NV相关的特性值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月5日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_ReadRoamCfgInfoNvim(VOS_VOID)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx = VOS_NULL_PTR;
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulLength;

    pstRegCtx                       = CMMCA_REG_GetCtxAddr();
    enModemId                       = MODEM_ID_0;
    ulLength                        = 0;
    stRoamFeature.ucRoamFeatureFlg  = NV_ITEM_ACTIVE;
    stRoamFeature.ucRoamCapability  = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulLength);
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_Roam_Capa,
                         &stRoamFeature, ulLength))
    {
        return;
    }

    if ((NV_ITEM_ACTIVE     != stRoamFeature.ucRoamFeatureFlg)
     && (NV_ITEM_DEACTIVE   != stRoamFeature.ucRoamFeatureFlg))
    {
        return;
    }

    if ( NV_ITEM_DEACTIVE == stRoamFeature.ucRoamFeatureFlg )
    {
        pstRegCtx->stUserCfgInfo.ucIsRoamActive = VOS_FALSE;
    }
    else
    {
        pstRegCtx->stUserCfgInfo.ucIsRoamActive = VOS_TRUE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CMMCA_GetTiCtx
 功能描述  : 获取timer ctx地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CMMCA_TIMER_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月23日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CMMCA_TIMER_CTX_STRU* CMMCA_GetTiCtx(VOS_VOID)
{
    return CMMCA_GetCtxAddr()->astCmmcaTimer;
}

/*****************************************************************************
 函 数 名  : CMMCA_InitTiCtx
 功能描述  : 初始化定时器相关的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_InitTiCtx(VOS_VOID)
{
    CMMCA_TIMER_CTX_STRU               *pstTiCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstTiCtx = CMMCA_GetTiCtx();

    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        pstTiCtx[i].hTimer        = VOS_NULL_PTR;
        pstTiCtx[i].enTimerId     = TI_CMMCA_TIMER_BUTT;
        pstTiCtx[i].enTimerStatus = CMMCA_TIMER_STATUS_STOP;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_InitCtx
 功能描述  : CMMCA模块上下文初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_InitCtx(VOS_VOID)
{
    /* 初始化Cur Op Id */
    CMMCA_SetCurMaxOpid(0);

    /* 设置Modem的状态为INACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);

    /* 初始化消息缓存队列 */
    CMMCA_InitCmdBufferQueue(CMMCA_GetCmdBufferQueueAddr());

    /* 初始化和PACKET DATA相关的上下文 */
    CMMCA_PKT_InitCtx();

    /* Added by s00261364 for L-C互操作项目, 2014-2-13, begin */
    /* 初始化和注册相关的上下文 */
    CMMCA_REG_InitCtx();
    /* Added by s00261364 for L-C互操作项目, 2014-2-13, end */

    /* 初始化定时器相关的上下文 */
    CMMCA_InitTiCtx();

    /* 可维可测初始化 */
    CMMCA_DEBUG_InitCtx();

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_AssignOpid
 功能描述  : 分配OPID，1-255
 输入参数  : VOS_UINT8                          *pucOpid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_AssignOpid(
    VOS_UINT8                          *pucOpid
)
{
    VOS_UINT8                           ucOpid;

    /*获取当前最大OPID*/
    ucOpid = CMMCA_GetCurMaxOpid();

    /*如果还未到最大值，直接加1*/
    if( ucOpid < CMMCA_OPID_MAX_VALUE)
    {
        *pucOpid = ucOpid + 1;
    }
    /*如果已经是最大值，从初值开始分配*/
    else
    {
        (*pucOpid) = CMMCA_OPID_MIN_VALUE;
    }

    CMMCA_SetCurMaxOpid(*pucOpid);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_GetCmdBufferQueueAddr
 功能描述  : 获取CMMCA消息队列的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CMMCA_CMD_BUFFER_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CMMCA_CMD_BUFFER_STRU* CMMCA_GetCmdBufferQueueAddr(VOS_VOID)
{
    return CMMCA_GetCtxAddr()->astCmdBufferQueue;
}

/*****************************************************************************
 函 数 名  : CMMCA_InitCmdBufferQueue
 功能描述  : 初始化CMMC消息队列
 输入参数  : CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_InitCmdBufferQueue(
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue
)
{
    VOS_UINT32                          i;

    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        pstCmdBufferQueue[i].ucOpId         = CMMCA_OPID_INVILID_VALUE;
        pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
        pstCmdBufferQueue[i].ulMsgInfoLen   = 0;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_DelItemInCmdBufferQueue
 功能描述  : 从队列中删除相对应的等待消息
 输入参数  : VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_DelItemInCmdBufferQueue(
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          i;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;

    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();

    for ( i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (ucOpId == pstCmdBufferQueue[i].ucOpId)
        {
            /* 如果有缓存的消息，释放消息内存 */
            if (VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
            {
                PS_MEM_FREE(WUEPS_PID_CMMCA, pstCmdBufferQueue[i].pucMsgInfo);
            }

            /* 初始化 */
            pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
            pstCmdBufferQueue[i].ucOpId         = CMMCA_OPID_INVILID_VALUE;
            pstCmdBufferQueue[i].ulMsgInfoLen   = 0;

            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_SaveItemInCmdBufferQueue
 功能描述  : 将相关信息存入到等待的缓存队列中, 等待处理的结果。约定pucMsgInfo的前两个字节为CMD ID
 输入参数  : VOS_UINT8                           ucOpId
             VOS_UINT8                          *pucMsgInfo
             VOS_UINT32                          ulMsgInfoLen
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CMMCA_SaveItemInCmdBufferQueue(
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *pucMsgInfo,
    VOS_UINT32                          ulMsgInfoLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucMsgBuf = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;

    /* 如果消息指针为空，直接返回 */
    if (VOS_NULL_PTR == pucMsgInfo)
    {
        return VOS_ERR;
    }

    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();

    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if (CMMCA_OPID_INVILID_VALUE == pstCmdBufferQueue[i].ucOpId)
        {
            break;
        }
    }

    /* 判定当前的循环队列是否已经满了，如果满了则直接返回，进行异常打印 */
    if (i >= CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE)
    {
        /* 缓存队列已满 */
        CMMCA_WARNING1_LOG("CMMCA_SaveItemInCmdBufferQueue, Buffer Full, Op Id :", ucOpId);

        CMMCA_LogBuffFullInd();

        return VOS_ERR;
    }

    /* 在队列增加相应的信息，分配内存，进行信息赋值 */
    pucMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, ulMsgInfoLen);
    if (VOS_NULL_PTR == pucMsgBuf)
    {
        return VOS_ERR;
    }

    /* 赋值 */
    PS_MEM_CPY((VOS_UINT8 *)pucMsgBuf, pucMsgInfo, ulMsgInfoLen);
    pstCmdBufferQueue[i].pucMsgInfo     = pucMsgBuf;
    pstCmdBufferQueue[i].ucOpId         = ucOpId;
    pstCmdBufferQueue[i].ulMsgInfoLen   = ulMsgInfoLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_GetItemFromCmdBufferQueue
 功能描述  : 从等待的缓存队列中获取相关信息
 输入参数  : VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : CMMCA_CMD_BUFFER_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CMMCA_CMD_BUFFER_STRU* CMMCA_GetItemFromCmdBufferQueue(
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          i;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue;

    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();

    /* 遍历队列, 获取enTimerId指定的消息节点 */
    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if (ucOpId == pstCmdBufferQueue[i].ucOpId)
        {
            break;
        }
    }

    /* 判定当前的循环队列是否已经满了，如果满了则直接返回，进行异常打印 */
    if (i >= CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE)
    {
        /* 未找到 */
        CMMCA_WARNING1_LOG("CMMCA_GetItemFromCmdBufferQueue, Msg Not Found, ucOpId Id :", ucOpId);

        return VOS_NULL_PTR;
    }

    /* 将缓存的消息指针返回 */
    return &pstCmdBufferQueue[i];
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




