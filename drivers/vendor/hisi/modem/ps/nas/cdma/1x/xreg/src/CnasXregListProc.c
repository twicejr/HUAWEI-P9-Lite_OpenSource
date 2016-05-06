/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregListProc.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2014年09月05日
  功能描述   : ZONE_LIST & SIDNID_LIST维护模块
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月05日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregListProc.h"
#include  "CnasMntn.h"
#include  "CnasXregTimer.h"
#include  "CnasXregMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_LIST_PROC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 存放ZONE_LIST & SIDNID_LIST节点的内存数组 */
CNAS_XREG_ZONE_NODE_STRU                g_astCnasXregZoneNode[CNAS_XREG_ZONE_NODE_MAX_NUM];
CNAS_XREG_SIDNID_NODE_STRU              g_astCnasXregSidNidNode[CNAX_XREG_SIDNID_NODE_MAX_NUM];

/* 指向当前ZONE_LIST & SIDNID_LIST的节点 */
CNAS_XREG_ZONE_NODE_STRU               *g_pstCnasXregCurrZoneNode   = VOS_NULL_PTR;
CNAS_XREG_SIDNID_NODE_STRU             *g_pstCnasXregCurrSidNidNode = VOS_NULL_PTR;

/* 维护ZONE_LIST & SIDNID_LIST的链表头 */
CNAS_XREG_LIST_HEADER_STRU              g_astCnasXregListHeader[CNAS_XREG_LIST_BUTT];

/* 存放当前的时间信息 */
CNAS_XREG_TIME_INFO_STRU                g_stCnasXregTimeInfo;

/* ZONE_TIMER索引表，参考协议: Table 3.7.2.3.2.1-1. */
VOS_UINT16                              g_ausCnasXregZoneTimerMap[] = {60, 120, 300, 600,
                                                                       1200, 1800, 2700, 3600};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetNodeCount
 功能描述  : 获取当前列表节点数目
 输入参数  : enListId -- 列表索引
 输出参数  : 无
 返 回 值  : VOS_UINT8 -- 节点数目
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XREG_GetNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId)
{
    return (VOS_UINT8)g_astCnasXregListHeader[enListId].ulNodeCount;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SetNodeCount
 功能描述  : 设置指定列表的节点数目
 输入参数  : enListId   -- 列表索引
             ulNodeCount-- 节点数目
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_SetNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId, VOS_UINT32 ulNodeCount)
{
    g_astCnasXregListHeader[enListId].ulNodeCount = ulNodeCount;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_IncNodeCount
 功能描述  : 指定列表的节点数目加一操作
 输入参数  : enListId   -- 列表索引
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_IncNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId)
{
    g_astCnasXregListHeader[enListId].ulNodeCount++;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_DecNodeCount
 功能描述  : 指定列表的节点数目减一操作
 输入参数  : enListId   -- 列表索引
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_DecNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId)
{
    g_astCnasXregListHeader[enListId].ulNodeCount--;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetListHeader
 功能描述  : 返回指定列表的头节点
 输入参数  : enListId   -- 列表索引
 输出参数  : 无
 返 回 值  : HI_LIST_S*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
HI_LIST_S* CNAS_XREG_GetListHeader(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId)
{
    return &(g_astCnasXregListHeader[enListId].stListHeader);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_AllocListNode
 功能描述  : 从指定列表中分配节点
 输入参数  : enListId   -- 列表索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
HI_LIST_S* CNAS_XREG_AllocListNode(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId)
{
    HI_LIST_S                           *pstIndexNode;

    if (0 == CNAS_XREG_GetNodeCount(enListId))
    {
        return VOS_NULL_PTR;
    }

    pstIndexNode = CNAS_XREG_GetListHeader(enListId)->next;

    msp_list_del(pstIndexNode);

    CNAS_XREG_DecNodeCount(enListId);

    return pstIndexNode;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RelCurrZoneNode
 功能描述  : 释放当前ZONE列表节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_RelCurrZoneNode(VOS_VOID)
{
    msp_list_add_tail(&(g_pstCnasXregCurrZoneNode->stListNode), CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_FREE_LIST_ID));

    CNAS_XREG_IncNodeCount(CNAS_XREG_ZONE_FREE_LIST_ID);

    g_pstCnasXregCurrZoneNode = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RelZoneListNode
 功能描述  : 释放ZONE列表中的指定节点
 输入参数  : pstZoneNode -- 需要删除的节点
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_RelZoneListNode(HI_LIST_S *pstZoneNode)
{
    msp_list_del(pstZoneNode);

    CNAS_XREG_DecNodeCount(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_add_tail(pstZoneNode, CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_FREE_LIST_ID));

    CNAS_XREG_IncNodeCount(CNAS_XREG_ZONE_FREE_LIST_ID);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RelCurrSidNidNode
 功能描述  : 释放当前SIDNID列表节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_RelCurrSidNidNode(VOS_VOID)
{
    msp_list_add_tail(&(g_pstCnasXregCurrSidNidNode->stListNode), CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_FREE_LIST_ID));

    CNAS_XREG_IncNodeCount(CNAS_XREG_SIDNID_FREE_LIST_ID);

    g_pstCnasXregCurrSidNidNode = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RelSidNidListNode
 功能描述  : 释放SIDNID列表中的指定节点
 输入参数  : pstSidNidNode -- 需要删除的节点
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_RelSidNidListNode(HI_LIST_S *pstSidNidNode)
{
    msp_list_del(pstSidNidNode);

    CNAS_XREG_DecNodeCount(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_add_tail(pstSidNidNode, CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_FREE_LIST_ID));

    CNAS_XREG_IncNodeCount(CNAS_XREG_SIDNID_FREE_LIST_ID);
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_InitList
 功能描述  : 初始化ZONE注册使用的链表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_InitList(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    HI_LIST_S                          *pstListHeader;

    /* 初始化链表头 */
    for (ucIndex = 0; ucIndex < CNAS_XREG_LIST_BUTT; ucIndex++)
    {
        CNAS_XREG_SetNodeCount(ucIndex, 0);

        pstListHeader = CNAS_XREG_GetListHeader(ucIndex);

        /*lint -e717*/
        HI_INIT_LIST_HEAD(pstListHeader);
        /*lint +e717*/
    }

    /* 初始化ZoneList */
    PS_MEM_SET(g_astCnasXregZoneNode, 0, sizeof(g_astCnasXregZoneNode));

    for (ucIndex = 0; ucIndex < CNAS_XREG_ZONE_NODE_MAX_NUM; ucIndex++)
    {
        msp_list_add_tail(&g_astCnasXregZoneNode[ucIndex].stListNode,
                            CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_FREE_LIST_ID));
    }

    CNAS_XREG_SetNodeCount(CNAS_XREG_ZONE_FREE_LIST_ID, CNAS_XREG_ZONE_NODE_MAX_NUM);

    /* 初始化SidNidList */
    PS_MEM_SET(g_astCnasXregSidNidNode, 0, sizeof(g_astCnasXregSidNidNode));

    for (ucIndex = 0; ucIndex < CNAX_XREG_SIDNID_NODE_MAX_NUM; ucIndex++)
    {
        msp_list_add_tail(&g_astCnasXregSidNidNode[ucIndex].stListNode,
                            CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_FREE_LIST_ID));
    }

    CNAS_XREG_SetNodeCount(CNAS_XREG_SIDNID_FREE_LIST_ID, CNAX_XREG_SIDNID_NODE_MAX_NUM);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ClearList
 功能描述  : 清空LIST所有的节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_ClearList(VOS_VOID)
{
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    HI_LIST_S                          *pstListHeader;

    /* 清空ZONE_LIST中所有项 */
    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        CNAS_XREG_RelZoneListNode(pstIndexNode);
    }

    if (VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
    {
        CNAS_XREG_RelCurrZoneNode();
    }

    /* 清空SIDNID_LIST中所有项 */
    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        CNAS_XREG_RelSidNidListNode(pstIndexNode);
    }

    if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
    {
        CNAS_XREG_RelCurrSidNidNode();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RestoreList
 功能描述  : 恢复LIST当前节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_RestoreList(VOS_VOID)
{
    PS_MEM_SET(&g_stCnasXregTimeInfo, 0, sizeof(g_stCnasXregTimeInfo));

    CNAS_XREG_ClearList();

    /* 假如NV项中存在ZONE单元则赋值到当前ZONE中 */
    ;

    /* 假如NV项中存在ZONE单元则赋值到当前ZONE中 */
    ;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SaveList
 功能描述  : 保存LIST的当前节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_SaveList(VOS_VOID)
{
    /* 假如NV项中存在ZONE单元则赋值到当前ZONE中 */
    ;


    /* 假如NV项中存在ZONE单元则赋值到当前ZONE中 */
    ;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_AddZoneNode
 功能描述  : 增加ZONE列表中节点
 输入参数  : pstZoneNode -- 节点
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_AddZoneNode(CNAS_XREG_ZONE_NODE_STRU *pstZoneNode)
{
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_ZONE_NODE_STRU           *pstIndexZoneNode;

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexZoneNode = msp_list_entry(pstIndexNode, CNAS_XREG_ZONE_NODE_STRU, stListNode);

        /* 找到链表中插入位置 */
        if (pstIndexZoneNode->ulSecNum > pstZoneNode->ulSecNum)
        {
            break;
        }
    }

    __list_add_msp(&(pstZoneNode->stListNode), pstIndexNode->prev, pstIndexNode);

    CNAS_XREG_IncNodeCount(CNAS_XREG_ZONE_USED_LIST_ID);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_AddCurrZoneNode
 功能描述  : 将当前的ZONE节点添加到队列中
 输入参数  : usSid       -- 系统ID
             usNid       -- 网络ID
             usRegZone   -- 区域标示
             ucZoneTimer -- 区域定时器长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_AddCurrZoneNode(VOS_UINT16 usSid, VOS_UINT16 usNid,
                                        VOS_UINT16 usRegZone, VOS_UINT8 ucZoneTimer)
{
    if (VOS_NULL_PTR == g_pstCnasXregCurrZoneNode)
    {
        return;
    }

    /* 参数检测 */
    if (ucZoneTimer >= (sizeof(g_ausCnasXregZoneTimerMap)/sizeof(VOS_UINT16)))
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_AddCurrZoneNode: ucZoneTimer is not correct.", ucZoneTimer);

        return;
    }

    if ((usSid != g_pstCnasXregCurrZoneNode->usSid)
        || ((usNid != g_pstCnasXregCurrZoneNode->usNid)
            && (usNid != CNAS_XREG_HOME_NID))
        || (usRegZone != g_pstCnasXregCurrZoneNode->usRegZone))
    {
        g_pstCnasXregCurrZoneNode->ulSecNum = g_stCnasXregTimeInfo.ulSecNum + g_ausCnasXregZoneTimerMap[ucZoneTimer];

        CNAS_XREG_AddZoneNode(g_pstCnasXregCurrZoneNode);

        g_pstCnasXregCurrZoneNode = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_AddSidNidNode
 功能描述  : 增加SIDNID列表中节点
 输入参数  : pstSidNidNode -- 节点
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_AddSidNidNode(CNAS_XREG_SIDNID_NODE_STRU *pstSidNidNode)
{
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_SIDNID_NODE_STRU         *pstIndexSidNidNode;

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        /* 找到链表中插入位置 */
        if (pstIndexSidNidNode->ulSecNum > pstSidNidNode->ulSecNum)
        {
            break;
        }
    }

    __list_add_msp(&(pstSidNidNode->stListNode), pstIndexNode->prev, pstIndexNode);

    CNAS_XREG_IncNodeCount(CNAS_XREG_SIDNID_USED_LIST_ID);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_AddCurrSidNidNode
 功能描述  : 将当前的SIDNID节点添加到队列中
 输入参数  : usSid       -- 系统ID
             usNid       -- 网络ID
             ucZoneTimer -- 区域定时器长度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_AddCurrSidNidNode(VOS_UINT16 usSid, VOS_UINT16 usNid,
                                                    VOS_UINT8 ucZoneTimer)
{
    if (VOS_NULL_PTR == g_pstCnasXregCurrSidNidNode)
    {
        return;
    }

    /* 参数检测 */
    if (ucZoneTimer >= (sizeof(g_ausCnasXregZoneTimerMap)/sizeof(VOS_UINT16)))
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_AddCurrSidNidNode: ucZoneTimer is not correct.", ucZoneTimer);

        return;
    }

    if ((usSid != g_pstCnasXregCurrSidNidNode->usSid)
        || ((usNid != g_pstCnasXregCurrSidNidNode->usNid)
            && (usNid != CNAS_XREG_HOME_NID)))
    {
        g_pstCnasXregCurrSidNidNode->ulSecNum = g_stCnasXregTimeInfo.ulSecNum + g_ausCnasXregZoneTimerMap[ucZoneTimer];

        CNAS_XREG_AddSidNidNode(g_pstCnasXregCurrSidNidNode);

        g_pstCnasXregCurrSidNidNode = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RefreshLists
 功能描述  : 更新当前列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_RefreshLists(VOS_VOID)
{
    VOS_UINT32                          ulCurrSlice;
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_ZONE_NODE_STRU           *pstIndexZoneNode;
    CNAS_XREG_SIDNID_NODE_STRU         *pstIndexSidNidNode;

    /* 将当前的SIDNIDLIST和ZONELIST可维可测输出 */
    CNAS_XREG_ZoneListMntn();
    CNAS_XREG_SidNidListMntn();
    CNAS_XREG_SndOmRegListReportInd();

    ulCurrSlice = CNAS_XREG_GetSlice();

    /* 记录当前上电后的时间，单位为秒 */
    g_stCnasXregTimeInfo.ulSecNum   += (ulCurrSlice - g_stCnasXregTimeInfo.ulPreSlice)/VOS_GetSliceUnit();

    g_stCnasXregTimeInfo.ulPreSlice = ulCurrSlice;

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexZoneNode = msp_list_entry(pstIndexNode, CNAS_XREG_ZONE_NODE_STRU, stListNode);

        /* 判断当前节点是否已经超时 */
        if (pstIndexZoneNode->ulSecNum <= g_stCnasXregTimeInfo.ulSecNum)
        {
            CNAS_XREG_RelZoneListNode(pstIndexNode);
        }
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        /* 判断当前节点是否已经超时 */
        if (pstIndexSidNidNode->ulSecNum <= g_stCnasXregTimeInfo.ulSecNum)
        {
            CNAS_XREG_RelSidNidListNode(pstIndexNode);
        }
    }

    /* 启动LIST保护定时器，确保1小时内LIST有刷新 */
    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_ZONELIST_PT, TI_CNAS_XREG_TIMER_ZONELIST_PT_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_TotalZones
 功能描述  : 设置ZONE列表中的最大节点个数
 输入参数  : ucRegZoneNum -- 最大节点个数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_TotalZones(VOS_UINT8 ucRegZoneNum)
{
    /*
    1、If TOTAL_ZONESs is equal to zero, the mobile station shall delete all entries.
    2、If TOTAL_ZONESs is not equal to zero, the mobile station shall delete those entries
       having active zone list entry timers, starting with the oldest entry, as determined by
       the timer values, and continuing in order of decreasing age until no more than TOTAL_ZONESs entries remain.
    */

    VOS_UINT8                           ucDelNum = 0;
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;

    /* 计算需要删除的个数 */
    if (ucRegZoneNum <= CNAS_XREG_GetNodeCount(CNAS_XREG_ZONE_USED_LIST_ID))
    {
        ucDelNum = CNAS_XREG_GetNodeCount(CNAS_XREG_ZONE_USED_LIST_ID) - ucRegZoneNum;

        if (VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
        {
            ucDelNum++;
        }
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    /* 将多余的ZONELIST删除 */
    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        if (0 == ucDelNum)
        {
            break;
        }

        CNAS_XREG_RelZoneListNode(pstIndexNode);

        ucDelNum--;
    }

    /* 假如还剩余一个，则把当前的ZONE删除 */
    if (1 == ucDelNum)
    {
        CNAS_XREG_RelCurrZoneNode();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_DelNodesByBandBlkSys
 功能描述  : 根据BandClass和BlockSystem删除节点
 输入参数  : pstSysInfo -- 系统消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_DelNodesByBandBlkSys(XSD_XREG_SYS_INFO_STRU *pstSysInfo)
{
    VOS_UINT16                          usBandClass;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_ZONE_NODE_STRU           *pstIndexZoneNode;
    CNAS_XREG_SIDNID_NODE_STRU         *pstIndexSidNidNode;

    usBandClass = pstSysInfo->usBandClass;
    enBlkSys    = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);

    /* ZONE_LIST */
    if ((VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
        && ((usBandClass != g_pstCnasXregCurrZoneNode->usBandClass)
            || (enBlkSys != g_pstCnasXregCurrZoneNode->enBlkSys)))
    {
        CNAS_XREG_RelCurrZoneNode();
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexZoneNode = msp_list_entry(pstIndexNode, CNAS_XREG_ZONE_NODE_STRU, stListNode);

        if ((pstIndexZoneNode->usBandClass != usBandClass)
            ||(pstIndexZoneNode->enBlkSys != enBlkSys))
        {
            CNAS_XREG_RelZoneListNode(pstIndexNode);
        }
    }

    /* SIDNID_LIST */
    if ((VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
        && ((usBandClass != g_pstCnasXregCurrSidNidNode->usBandClass)
            || (enBlkSys != g_pstCnasXregCurrSidNidNode->enBlkSys)))
    {
        CNAS_XREG_RelCurrSidNidNode();
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        if ((pstIndexSidNidNode->usBandClass != usBandClass)
            ||(pstIndexSidNidNode->enBlkSys != enBlkSys))
        {
            CNAS_XREG_RelSidNidListNode(pstIndexNode);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_FindZoneNode
 功能描述  : 在ZONE列表中查找相应节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_XREG_ZONE_NODE_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
CNAS_XREG_ZONE_NODE_STRU *CNAS_XREG_FindZoneNode(VOS_UINT16 usSid, VOS_UINT16 usNid, VOS_UINT16 usRegZone)
{
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_ZONE_NODE_STRU           *pstIndexZoneNode;

    if (VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
    {
        if ((usSid == g_pstCnasXregCurrZoneNode->usSid)
            && ((CNAS_XREG_HOME_NID == usNid)
                || (usNid == g_pstCnasXregCurrZoneNode->usNid))
            && (usRegZone == g_pstCnasXregCurrZoneNode->usRegZone))
        {
            return g_pstCnasXregCurrZoneNode;
        }
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexZoneNode = msp_list_entry(pstIndexNode, CNAS_XREG_ZONE_NODE_STRU, stListNode);

        if ((usSid == pstIndexZoneNode->usSid)
            && ((CNAS_XREG_HOME_NID == usNid)
                || (usNid == pstIndexZoneNode->usNid))
            && (usRegZone == pstIndexZoneNode->usRegZone))
        {
            return pstIndexZoneNode;
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_FindSidNidNode
 功能描述  : 在SIDNID列表中查找相应节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
CNAS_XREG_SIDNID_NODE_STRU *CNAS_XREG_FindSidNidNode(VOS_UINT16 usSid, VOS_UINT16 usNid)
{
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_SIDNID_NODE_STRU         *pstIndexSidNidNode;

    if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
    {
        if ((usSid == g_pstCnasXregCurrSidNidNode->usSid)
            && ((CNAS_XREG_HOME_NID == usNid)
                || (usNid == g_pstCnasXregCurrSidNidNode->usNid)))
        {
            return g_pstCnasXregCurrSidNidNode;
        }
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        if ((usSid == pstIndexSidNidNode->usSid)
            && ((CNAS_XREG_HOME_NID == usNid)
                || (usNid == pstIndexSidNidNode->usNid)))
        {
            return pstIndexSidNidNode;
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_UpdateZoneList
 功能描述  : 更新ZONE列表
 输入参数  : pstSysInfo -- 系统消息
             usSid      -- 系统ID
             usNid      -- 网络ID
             usRegZone  -- 区域标示
             ucZoneTimer-- ZONE定时器时长
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_UpdateZoneList(XSD_XREG_SYS_INFO_STRU *pstSysInfo, VOS_UINT16 usSid, VOS_UINT16 usNid,
                                    VOS_UINT16 usRegZone, VOS_UINT8 ucZoneTimer)
{
    CNAS_XREG_ZONE_NODE_STRU           *pstZoneNode;
    HI_LIST_S                          *pstIndexNode;

    /* 参数检测 */
    if (ucZoneTimer >= (sizeof(g_ausCnasXregZoneTimerMap)/sizeof(VOS_UINT16)))
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_UpdateZoneList: ucZoneTimer is not correct.", ucZoneTimer);

        return;
    }

    pstZoneNode = CNAS_XREG_FindZoneNode(usSid, usNid, usRegZone);

    /* 假如没找到对应的ZONE_LIST */
    if (VOS_NULL_PTR == pstZoneNode)
    {
        if (VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
        {
            g_pstCnasXregCurrZoneNode->ulSecNum = g_stCnasXregTimeInfo.ulSecNum + g_ausCnasXregZoneTimerMap[ucZoneTimer];

            CNAS_XREG_AddZoneNode(g_pstCnasXregCurrZoneNode);
        }

        pstIndexNode = CNAS_XREG_AllocListNode(CNAS_XREG_ZONE_FREE_LIST_ID);

        if (VOS_NULL_PTR == pstIndexNode)
        {
            /* 假如无剩余节点，则从删除最老节点 */
            pstIndexNode = CNAS_XREG_AllocListNode(CNAS_XREG_ZONE_USED_LIST_ID);
        }

        g_pstCnasXregCurrZoneNode = msp_list_entry(pstIndexNode, CNAS_XREG_ZONE_NODE_STRU, stListNode);

        g_pstCnasXregCurrZoneNode->ulSecNum     = 0;
        g_pstCnasXregCurrZoneNode->usSid = usSid;
        g_pstCnasXregCurrZoneNode->usNid = usNid;
        g_pstCnasXregCurrZoneNode->usRegZone    = usRegZone;
        g_pstCnasXregCurrZoneNode->usBandClass  = pstSysInfo->usBandClass;
        g_pstCnasXregCurrZoneNode->enBlkSys     = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);;

        return;
    }

    /* 找到对应的ZONE_LIST，并且和当前的ZONE_LIST不同 */
    if (pstZoneNode != g_pstCnasXregCurrZoneNode)
    {
        /* 删除原有节点 */
        msp_list_del(&(pstZoneNode->stListNode));

        CNAS_XREG_DecNodeCount(CNAS_XREG_ZONE_USED_LIST_ID);

        /* 将当前ZONE加入到ZONE_LIST中 */
        if (VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
        {
            g_pstCnasXregCurrZoneNode->ulSecNum = g_stCnasXregTimeInfo.ulSecNum + g_ausCnasXregZoneTimerMap[ucZoneTimer];

            CNAS_XREG_AddZoneNode(g_pstCnasXregCurrZoneNode);
        }

        g_pstCnasXregCurrZoneNode = pstZoneNode;

        g_pstCnasXregCurrZoneNode->ulSecNum     = 0;
        g_pstCnasXregCurrZoneNode->usSid = usSid;
        g_pstCnasXregCurrZoneNode->usNid = usNid;
        g_pstCnasXregCurrZoneNode->usRegZone    = usRegZone;
        g_pstCnasXregCurrZoneNode->usBandClass  = pstSysInfo->usBandClass;
        g_pstCnasXregCurrZoneNode->enBlkSys     = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_UpdateSidNidList
 功能描述  : 更新SIDNID列表
 输入参数  : pstSysInfo -- 系统消息
             usSid      -- 系统ID
             usNid      -- 网络ID
             ucZoneTimer-- ZONE定时器时长
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_UpdateSidNidList(XSD_XREG_SYS_INFO_STRU *pstSysInfo, VOS_UINT16 usSid,
                                                VOS_UINT16 usNid, VOS_UINT8 ucZoneTimer)
{
    CNAS_XREG_SIDNID_NODE_STRU         *pstSidNidNode;
    HI_LIST_S                          *pstIndexNode;

    /* 参数检测 */
    if (ucZoneTimer >= (sizeof(g_ausCnasXregZoneTimerMap)/sizeof(VOS_UINT16)))
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_UpdateSidNidList: ucZoneTimer is not correct.", ucZoneTimer);

        return;
    }

    pstSidNidNode = CNAS_XREG_FindSidNidNode(usSid, usNid);

    /* 假如没找到对应的SIDNID_LIST */
    if (VOS_NULL_PTR == pstSidNidNode)
    {
        if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
        {
            g_pstCnasXregCurrSidNidNode->ulSecNum = g_stCnasXregTimeInfo.ulSecNum + g_ausCnasXregZoneTimerMap[ucZoneTimer];

            CNAS_XREG_AddSidNidNode(g_pstCnasXregCurrSidNidNode);
        }

        pstIndexNode = CNAS_XREG_AllocListNode(CNAS_XREG_SIDNID_FREE_LIST_ID);

        if (VOS_NULL_PTR == pstIndexNode)
        {
            /* 假如无剩余节点，则从删除最老节点 */
            pstIndexNode = CNAS_XREG_AllocListNode(CNAS_XREG_SIDNID_USED_LIST_ID);
        }

        g_pstCnasXregCurrSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        g_pstCnasXregCurrSidNidNode->ulSecNum     = 0;
        g_pstCnasXregCurrSidNidNode->usSid = usSid;
        g_pstCnasXregCurrSidNidNode->usNid = usNid;
        g_pstCnasXregCurrSidNidNode->usBandClass = pstSysInfo->usBandClass;
        g_pstCnasXregCurrSidNidNode->enBlkSys    = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);;

        return;
    }

    /* 找到对应的SIDNID_LIST，并且和当前的SIDNID_LIST不同 */
    if (pstSidNidNode != g_pstCnasXregCurrSidNidNode)
    {
        /* 删除原有节点 */
        msp_list_del(&(pstSidNidNode->stListNode));

        CNAS_XREG_DecNodeCount(CNAS_XREG_SIDNID_USED_LIST_ID);

        /* 将当前ZONE加入到ZONE_LIST中 */
        if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
        {
            g_pstCnasXregCurrSidNidNode->ulSecNum = g_stCnasXregTimeInfo.ulSecNum + g_ausCnasXregZoneTimerMap[ucZoneTimer];

            CNAS_XREG_AddSidNidNode(g_pstCnasXregCurrSidNidNode);
        }

        g_pstCnasXregCurrSidNidNode = pstSidNidNode;

        g_pstCnasXregCurrSidNidNode->ulSecNum     = 0;
        g_pstCnasXregCurrSidNidNode->usSid = usSid;
        g_pstCnasXregCurrSidNidNode->usNid = usNid;
        g_pstCnasXregCurrSidNidNode->usBandClass    = pstSysInfo->usBandClass;
        g_pstCnasXregCurrSidNidNode->enBlkSys       = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_DelMultSids
 功能描述  : 删除SIDNID列表中不同SID的节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_DelMultSids(VOS_VOID)
{
    /*
    Whenever MULT_SIDSs is equal to '0' and SID_NID_LIST contains entries with different
    SIDs, the mobile station shall delete the excess entries according to the following rules:
      If the SID/NID entry timer for any entry is disabled, the mobile station shall delete
       all entries not having the same SID as the entry whose timer is disabled;
      Otherwise, the mobile station shall delete all entries not having the same SID as the
       newest entry in SID_NID_LIST, as determined by the timer values.
    */
    VOS_UINT16                          usSid;
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_SIDNID_NODE_STRU         *pstSidNidNode;

    if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
    {
        usSid = g_pstCnasXregCurrSidNidNode->usSid;
    }
    else
    {
        if (0 == CNAS_XREG_GetNodeCount(CNAS_XREG_SIDNID_USED_LIST_ID))
        {
            return;
        }

        /* 取最新节点的SID作为比较值 */
        pstIndexNode  = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID)->prev;
        pstSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        usSid         = pstSidNidNode->usSid;
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    /* 查找SIDNID_LIST，并将不同SID节点删除 */
    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        if (usSid != pstSidNidNode->usSid)
        {
            CNAS_XREG_RelSidNidListNode(pstIndexNode);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_DelMultNids
 功能描述  : 确保SIDNID列表中的相同SID项只保留最新节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_DelMultNids(VOS_VOID)
{
/*
    Whenever MULT_NIDSs is equal to '0' and SID_NID_LIST contains more than one entry for
    any SID, the mobile station shall delete the excess entries for each SID according to the
    following rules:
    If the SID/NID entry timer for any entry is disabled, the mobile station shall delete
    all entries for that SID except the entry whose timer is disabled;
    For all other SIDs, the mobile station shall delete all entries for each SID except the
    newest entry, as determined by the timer values.
*/
    VOS_UINT16                          usSid;
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    HI_LIST_S                          *pstTailNode;
    CNAS_XREG_SIDNID_NODE_STRU         *pstSidNidNode;

    if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
    {
        usSid = g_pstCnasXregCurrSidNidNode->usSid;

        pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

        /* 查找SIDNID_LIST，并将相同SID节点删除 */
        msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
        {
            pstSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

            if (usSid == pstSidNidNode->usSid)
            {
                CNAS_XREG_RelSidNidListNode(pstIndexNode);
            }
        }
    }

    /* 指向最尾的节点 */
    pstTailNode = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID)->prev;

    while (pstTailNode != CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID))
    {
        pstSidNidNode = msp_list_entry(pstTailNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);
        usSid         = pstSidNidNode->usSid;

        pstIndexNode = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID)->next;
        pstTempNode  = pstIndexNode->next;

        for (; pstIndexNode != pstTailNode; pstIndexNode = pstTempNode, pstTempNode = pstIndexNode->next)
        {
            pstSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

            if (usSid == pstSidNidNode->usSid)
            {
                CNAS_XREG_RelSidNidListNode(pstIndexNode);
            }
        }

        /* 完成一轮遍历后需要向前进一步 */
        pstTailNode = pstTailNode->prev;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SidNidListIsEmpty
 功能描述  : 判断SID_NID_LIST是否为空
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XREG_SidNidListIsEmpty(VOS_VOID)
{
    if (VOS_NULL_PTR == g_pstCnasXregCurrSidNidNode)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetSlice
 功能描述  : 为DMT测试封装Slice接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetSlice(VOS_VOID)
{
    return VOS_GetSlice();
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SidNidListMntn
 功能描述  : SidNidList可维可测
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_SidNidListMntn(VOS_VOID)
{
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_SIDNID_NODE_STRU         *pstIndexSidNidNode;
    CNAS_XREG_SIDNID_LIST_MNTN_STRU    *pstSidNidListMntnMsg;
    VOS_UINT32                          ulIndex = 0;

    pstSidNidListMntnMsg = (CNAS_XREG_SIDNID_LIST_MNTN_STRU*)VOS_AllocMsg(UEPS_PID_XREG,
                                                                          sizeof(CNAS_XREG_SIDNID_LIST_MNTN_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSidNidListMntnMsg)
    {
        return;
    }

    pstSidNidListMntnMsg->ulReceiverPid   = UEPS_PID_XREG;
    pstSidNidListMntnMsg->enMsgId         = CNAS_XREG_MNTN_SIDNID_LIST;

    /* 存放时间信息 */
    PS_MEM_CPY(&(pstSidNidListMntnMsg->stTimeInfo),
               &g_stCnasXregTimeInfo,
               sizeof(CNAS_XREG_TIME_INFO_STRU));

    PS_MEM_SET(pstSidNidListMntnMsg->astSidNidNode,
               0,
               sizeof(pstSidNidListMntnMsg->astSidNidNode));

    if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
    {
        PS_MEM_CPY(&(pstSidNidListMntnMsg->astSidNidNode[ulIndex]),
                   g_pstCnasXregCurrSidNidNode,
                   sizeof(CNAS_XREG_SIDNID_NODE_STRU));
        ulIndex++;
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        PS_MEM_CPY(&(pstSidNidListMntnMsg->astSidNidNode[ulIndex]),
                   pstIndexSidNidNode,
                   sizeof(CNAS_XREG_SIDNID_NODE_STRU));
    }

    DIAG_TraceReport((VOS_VOID *)(pstSidNidListMntnMsg));

    VOS_FreeMsg(UEPS_PID_XREG, pstSidNidListMntnMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ZoneListMntn
 功能描述  : ZoneList可维可测
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : ganlan
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XREG_ZoneListMntn(VOS_VOID)
{
    HI_LIST_S                          *pstListHeader;
    HI_LIST_S                          *pstIndexNode;
    HI_LIST_S                          *pstTempNode;
    CNAS_XREG_ZONE_NODE_STRU           *pstIndexZoneNode;
    CNAS_XREG_ZONE_LIST_MNTN_STRU      *pstZoneListMntnMsg;
    VOS_UINT32                          ulIndex = 0;

    pstZoneListMntnMsg = (CNAS_XREG_ZONE_LIST_MNTN_STRU*)VOS_AllocMsg(UEPS_PID_XREG,
                                                                      sizeof(CNAS_XREG_ZONE_LIST_MNTN_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstZoneListMntnMsg)
    {
        return;
    }

    pstZoneListMntnMsg->ulReceiverPid   = UEPS_PID_XREG;
    pstZoneListMntnMsg->enMsgId         = CNAS_XREG_MNTN_ZONE_LIST;

    pstZoneListMntnMsg->ulCurSlice = VOS_GetSlice();
    PS_MEM_SET(pstZoneListMntnMsg->astZoneNode, 0, sizeof(pstZoneListMntnMsg->astZoneNode));

    if (VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
    {
        PS_MEM_CPY(&(pstZoneListMntnMsg->astZoneNode[ulIndex]),
                   g_pstCnasXregCurrZoneNode,
                   sizeof(CNAS_XREG_ZONE_NODE_STRU));
        ulIndex++;
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexZoneNode = msp_list_entry(pstIndexNode, CNAS_XREG_ZONE_NODE_STRU, stListNode);

        PS_MEM_CPY(&(pstZoneListMntnMsg->astZoneNode[ulIndex]),
                   pstIndexZoneNode,
                   sizeof(CNAS_XREG_ZONE_NODE_STRU));
        ulIndex++;
    }

    DIAG_TraceReport((VOS_VOID *)(pstZoneListMntnMsg));

    VOS_FreeMsg(UEPS_PID_XREG, pstZoneListMntnMsg);

    return;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




