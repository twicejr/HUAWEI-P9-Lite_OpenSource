#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_TIMER_C
/*lint +e767*/

/* 时间节点的哈希链表，用于删除定时器连上的节点时能够快速定位到节点，节点哈希值通过teidc计算得到 */
DHCPC_TIMER_LIST_HEAD_S *g_pstDHCPTimerHashList = NULL;
/* 秒级定时器链表 */
/* DHCPC_TIMER_NODE_S *g_pstDHCPTimerSecondList = NULL; */
DHCPC_TIMER_NODE_S g_pstDHCPTimerSecondList[DHCPC_SECOND_TIMER_LEN] = {0};
/* 小时定时器链表 */
/* DHCPC_TIMER_NODE_S *g_pstDHCPTimerHourList = NULL; */
DHCPC_TIMER_NODE_S g_pstDHCPTimerHourList[DHCPC_HOUR_TIMER_LEN] = {0};

/* 秒级定时器链表处理的当前位置 */
ULONG g_ulDHCPCTimerSecondPos = 0;
/* 小时定时器链表处理的当前位置 */
ULONG g_ulDHCPCTimerHourPos = 0;

/* 小时定时器链表分钟处理次数 */
ULONG g_ulDHCPCTimerHourSecNum = 0;

/* 秒级定时器id */
RELTMR_T g_ulDHCPCSecondTimerId = 0;
/* 小时定时器id */
RELTMR_T g_ulDHCPCHourTimerId = 0;

/* 秒级定时器和小时定时器链表上节点个数 */
ULONG g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_MAX] = {0};

/* 获取秒级链的当前位置 */
ULONG DHCPC_getCurTimerSecondPos()
{
    return g_ulDHCPCTimerSecondPos;
}

/* 使秒级链的当前位置加1 */
ULONG DHCPC_incCurTimerSecondPos()
{
    g_ulDHCPCTimerSecondPos++;
    g_ulDHCPCTimerSecondPos = g_ulDHCPCTimerSecondPos%DHCPC_SECOND_TIMER_LEN;
    return g_ulDHCPCTimerSecondPos;
}

/* 获取小时链的当前位置 */
ULONG DHCPC_getCurTimerHourPos()
{
    return g_ulDHCPCTimerHourPos;
}

/* 使小时链的当前位置加1 */
ULONG DHCPC_incCurTimerHourPos()
{
    g_ulDHCPCTimerHourPos++;
    g_ulDHCPCTimerHourPos = g_ulDHCPCTimerHourPos%DHCPC_HOUR_TIMER_LEN;
    return g_ulDHCPCTimerHourPos;
}

/* 获取小时链的超时次数 */
ULONG DHCPC_getCurTimerHourSec()
{
    return g_ulDHCPCTimerHourSecNum;
}

/* 使小时链的超时次数加1 */
VOID DHCPC_incCurTimerHourSec()
{
    g_ulDHCPCTimerHourSecNum++;
    g_ulDHCPCTimerHourSecNum = g_ulDHCPCTimerHourSecNum%DHCPC_SECONDS_PER_HOUR;
    return;
}



ULONG DHCPC_InitTimerList()
{
    ULONG ulMemSize;

    /* 为时间节点哈希链表表头申请内存并初始化 */
    ulMemSize= sizeof(DHCPC_TIMER_LIST_HEAD_S) * DHCPC_CTRLBLK_HASH_TABLE_SIZE;
    g_pstDHCPTimerHashList = (DHCPC_TIMER_LIST_HEAD_S *)DHCP_Malloc(DHCPC_HANDLE, ulMemSize);
    if (NULL == g_pstDHCPTimerHashList)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(g_pstDHCPTimerHashList, ulMemSize);

    /* 为时间节点秒级链表表头申请内存并初始化 */
    /* ulMemSize= sizeof(DHCPC_TIMER_NODE_S) * DHCPC_SECOND_TIMER_LEN;
    g_pstDHCPTimerSecondList = (DHCPC_TIMER_NODE_S *)DHCP_Malloc(DHCPC_HANDLE, ulMemSize);
    if (NULL == g_pstDHCPTimerSecondList)
    {
        DHCP_Free(DHCPC_HANDLE, g_pstDHCPTimerHashList);
        VOS_Assert(0);
        return VOS_ERR;
    } */
    DHCP_MemZero(g_pstDHCPTimerSecondList, ulMemSize);

    /* 为时间节点小时链表表头申请内存并初始化 */
    /* ulMemSize= sizeof(DHCPC_TIMER_NODE_S) * DHCPC_HOUR_TIMER_LEN;
    g_pstDHCPTimerHourList = (DHCPC_TIMER_NODE_S *)DHCP_Malloc(DHCPC_HANDLE, ulMemSize);
    if (NULL == g_pstDHCPTimerHourList)
    {
        DHCP_Free(DHCPC_HANDLE, g_pstDHCPTimerHashList);
        DHCP_Free(DHCPC_HANDLE, g_pstDHCPTimerSecondList);
        VOS_Assert(0);
        return VOS_ERR;
    } */
    DHCP_MemZero(g_pstDHCPTimerHourList, ulMemSize);

    return VOS_OK;
}

ULONG DHCPC_IsTimNodeExist(UCHAR ucIpType, ULONG ulTeidc)
{
    ULONG ulHashKey = DHCPC_GET_HASHKEY(ulTeidc);
    DHCPC_TIMER_NODE_S *pstCurrNode = NULL;

    pstCurrNode = g_pstDHCPTimerHashList[ulHashKey].pstNextNode;

    while(NULL != pstCurrNode)
    {
        if ((pstCurrNode->ulTeidc == ulTeidc)
            && (pstCurrNode->ucIpType == ucIpType))
        {
            return VOS_OK;
        }

        pstCurrNode = pstCurrNode->pstHashNextNode;
    }

    return VOS_ERR;
}



VOID DHCPC_CreateDhcpcTimerNode(DHCPC_TIMER_NODE_S **ppstDHCPTimerNode)
{
    DHCPC_TIMER_NODE_S *pstDHCPTimerNode = NULL;

    if (NULL == ppstDHCPTimerNode)
    {
        VOS_Assert(0);
        return;
    }

    pstDHCPTimerNode = (DHCPC_TIMER_NODE_S *)DHCP_Malloc(DHCPC_HANDLE, sizeof(DHCPC_TIMER_NODE_S));
    if (NULL == pstDHCPTimerNode)
    {
        VOS_Assert(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_MALLOC_ERR_FOR_TIMER_NODE);
        *ppstDHCPTimerNode = NULL;
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "malloc Timer Node memory failed!");
        return;
    }
    DHCP_MemZero(pstDHCPTimerNode, sizeof(DHCPC_TIMER_NODE_S));

    *ppstDHCPTimerNode = pstDHCPTimerNode;

    return;
}


VOID DHCPC_putTimerNodeToHashList(DHCPC_TIMER_LIST_HEAD_S *pstHashList,
                                    DHCPC_TIMER_NODE_S *pstTimerNode)
{
    ULONG ulHashKey = DHCPC_GET_HASHKEY(pstTimerNode->ulTeidc);

    pstTimerNode->pstHashNextNode = pstHashList[ulHashKey].pstNextNode;

    pstHashList[ulHashKey].pstNextNode = pstTimerNode;

    return;
}


VOID DHCPC_putTimerNodeToTimerList(DHCPC_TIMER_NODE_S *pstTimerList,
                                    DHCPC_TIMER_NODE_S *pstTimerNode, ULONG ulTimerPos)
{
    DHCPC_TIMER_NODE_S *pstHeadNode = &(pstTimerList[ulTimerPos]);

    /* 插到首节点位置 */
    pstTimerNode->pstPrevNode = pstHeadNode;
    pstTimerNode->pstNextNode = pstHeadNode->pstNextNode;

    if (NULL != pstHeadNode->pstNextNode)
    {
        pstHeadNode->pstNextNode->pstPrevNode = pstTimerNode;
    }

    pstHeadNode->pstNextNode = pstTimerNode;

    return;
}


VOID DHCPC_putIntoTimerList(DHCPC_TIMER_NODE_S *pstTimerNode, ULONG ulTimerInterval)
{
    ULONG ulTempSeconds = 0;
    ULONG ulInsTimerPos = 0;
    ULONG ulTempHours = 0;

    /* 放入小时定时器 */
    if (ulTimerInterval >= DHCPC_SECONDS_PER_HOUR)
    {
        /* 需要考虑小时定时器已经过去的时间 */
        ulTempSeconds = (ulTimerInterval + DHCPC_getCurTimerHourSec());
        pstTimerNode->usSecondField = (USHORT)(ulTempSeconds % DHCPC_SECONDS_PER_HOUR);

        ulTempHours = ulTempSeconds / DHCPC_SECONDS_PER_HOUR;
        pstTimerNode->ulCircleNum = ulTempHours / DHCPC_HOUR_TIMER_LEN; /* 租约的月数，0表示不到一个月 */
        pstTimerNode->ucListType = DHCPC_LIST_TYPE_HOUR;
        ulInsTimerPos = DHCPC_GET_HOUR_INSPOS(ulTempHours);
        DHCPC_putTimerNodeToTimerList(g_pstDHCPTimerHourList, pstTimerNode, ulInsTimerPos);
        g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_HOUR]++;

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "put Timer Node into Hour-Timer List "
                        "ulTeidc=%08x, ulTimerInterval=%u, ulSecondField=%u, "
                        "ulCurHourPos=%u, ulInsHourPos=%u!",
                        pstTimerNode->ulTeidc, ulTimerInterval, pstTimerNode->usSecondField,
                        DHCPC_getCurTimerHourPos(), ulInsTimerPos);
        return;
    }

    /* 放入秒级定时器 */
    pstTimerNode->usSecondField = 0;
    pstTimerNode->ucListType = DHCPC_LIST_TYPE_SECOND;
    ulInsTimerPos = DHCPC_GET_SECOND_INSPOS(ulTimerInterval * DHCPC_MILLSECONDS_PER_SECOND / DHCPC_SECOND_TIMER_INTERVAL);
    DHCPC_putTimerNodeToTimerList(g_pstDHCPTimerSecondList, pstTimerNode, ulInsTimerPos);
    g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_SECOND]++;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "put Timer Node into Second-Timer List "
                    "ulTeidc=%08x, ulTimerInterval=%u, ulSecondField=%u, "
                    "ulCurSecPos=%u, ulInsSecPos=%u!",
                    pstTimerNode->ulTeidc, ulTimerInterval, 0,
                    DHCPC_getCurTimerSecondPos(), ulInsTimerPos);

    return;
}


ULONG DHCPC_StartTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent, ULONG ulTimerInterval, DHCPC_TIMER_CALLBACK pCallBackFun)
{
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    /* 合法性校验 */
    if ((0 == ulTeidc) || (0 == ulTimerInterval))
    {
        VOS_Assert(0 != ulTeidc);
        VOS_Assert(0 != ulTimerInterval);
        return VOS_ERR;
    }

    /* 申请内存，创建时间链表节点 */
    DHCPC_CreateDhcpcTimerNode(&pstTimerNode);
    if (NULL == pstTimerNode)
    {
        return VOS_ERR;
    }

    /* 为时间链表节点赋值 */
    pstTimerNode->ulTeidc = ulTeidc;
    pstTimerNode->ucIpType = ucIpType;
    pstTimerNode->ucEvent = ucEvent;
    pstTimerNode->pCallBackFun = pCallBackFun;

    /* 放入哈希链 */
    DHCPC_putTimerNodeToHashList(g_pstDHCPTimerHashList, pstTimerNode);

    /* 放入定时器 */
    DHCPC_putIntoTimerList(pstTimerNode, ulTimerInterval);

    return VOS_OK;
}


ULONG DHCPC_DeleteNodeFromHashList(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent, DHCPC_TIMER_NODE_S **ppstTimerNode)
{
    ULONG ulHashKey = DHCPC_GET_HASHKEY(ulTeidc);
    DHCPC_TIMER_NODE_S *pstPrevNode = NULL;
    DHCPC_TIMER_NODE_S *pstCurrNode = NULL;

    *ppstTimerNode = NULL;

    pstPrevNode = g_pstDHCPTimerHashList[ulHashKey].pstNextNode;
    pstCurrNode = pstPrevNode;

    /* 如果一个节点都没有，必然是查找失败 */
    if (NULL == pstPrevNode)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_NODE_IN_HASH_LIST);
        return VOS_ERR;
    }

    while(NULL != pstCurrNode)
    {
        if ((pstCurrNode->ulTeidc == ulTeidc)
            && (pstCurrNode->ucIpType == ucIpType)
            && (pstCurrNode->ucEvent == ucEvent))
        {
            /* 从哈希链中摘除 */
            /* 是头结点的情况 */
            if (pstPrevNode == pstCurrNode)
            {
                g_pstDHCPTimerHashList[ulHashKey].pstNextNode = pstCurrNode->pstHashNextNode;
            }
            else
            {
                pstPrevNode->pstHashNextNode = pstCurrNode->pstHashNextNode;
            }

            pstCurrNode->pstHashNextNode = NULL;
            *ppstTimerNode = pstCurrNode;
            return VOS_OK;
        }

        /* 改变循环变量 */
        pstPrevNode = pstCurrNode;
        pstCurrNode = pstCurrNode->pstHashNextNode;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NODE_NOT_IN_HASH_LIST);
    return VOS_ERR;
}


ULONG DHCPC_CutTimerNodeFromTimerList(DHCPC_TIMER_NODE_S *pstTimerNode)
{
    if (NULL == pstTimerNode)
    {
        VOS_ASSERT(0);
        return VOS_ERR;
    }

    /* 不能是头结点，如果是头结点，则发生异常 */
    if (NULL == pstTimerNode->pstPrevNode)
    {
        VOS_Assert(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FIND_NODE_CANNOT_BE_HEAD);
        return VOS_ERR;
    }

    pstTimerNode->pstPrevNode->pstNextNode = pstTimerNode->pstNextNode;

    if (NULL != pstTimerNode->pstNextNode)
    {
        pstTimerNode->pstNextNode->pstPrevNode = pstTimerNode->pstPrevNode;
    }

    g_ulDHCPCTimerListNodeNum[pstTimerNode->ucListType]--;

    pstTimerNode->pstPrevNode = NULL;
    pstTimerNode->pstNextNode = NULL;

#if 0
    DHCP_Free(DHCPC_HANDLE, pstTimerNode);
#endif

    return VOS_OK;
}


ULONG DHCPC_StopTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent)
{
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    /* 合法性校验 */
    if (0 == ulTeidc)
    {
        VOS_Assert(0 != ulTeidc);
        return VOS_ERR;
    }

    /* 查找时间节点，并从时间节点哈希链中删除 */
    (VOID)DHCPC_DeleteNodeFromHashList(ucIpType, ulTeidc, ucEvent, &pstTimerNode);
    if (NULL == pstTimerNode)
    {
        return VOS_ERR;
    }

    /* 从时间槽中摘除，达到删除定时器目的 */
    (VOID)DHCPC_CutTimerNodeFromTimerList(pstTimerNode);

    pstTimerNode = NULL;

    return VOS_OK;
}


VOID DHCPC_HourListTimerOut(VOID *pvArg)
{
    ULONG ulCurIndex = 0;
    ULONG ulInsTimerPos = 0;
    DHCPC_TIMER_NODE_S *pstTempNode = NULL;
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    DHCPC_incCurTimerHourSec();

    if (0 < DHCPC_getCurTimerHourSec())
    {
        return;
    }

    /* 将小时节点链表当前索引加1，并获取值 */
    ulCurIndex = DHCPC_incCurTimerHourPos();

    pstTimerNode = g_pstDHCPTimerHourList[ulCurIndex].pstNextNode;

    while (NULL != pstTimerNode)
    {
        /* 上一个节点不能为空 */
        if (NULL == pstTimerNode->pstPrevNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SECONDNODE_CANNOT_BE_HEAD);
            break;
        }

        /* 上一个节点的下一个节点必须是本节点 */
        if (pstTimerNode != pstTimerNode->pstPrevNode->pstNextNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SECONDLIST_LINK_ERROR);
            break;
        }

        /* 保存下一节点 */
        pstTempNode = pstTimerNode->pstNextNode;

        /* 已经超期的情况 */
        if (0 == pstTimerNode->ulCircleNum)
        {
            /* 先从小时链表中摘除 */
            pstTimerNode->pstPrevNode->pstNextNode = pstTimerNode->pstNextNode;
            if (NULL != pstTimerNode->pstNextNode)
            {
                pstTimerNode->pstNextNode->pstPrevNode = pstTimerNode->pstPrevNode;
            }
            /* 将节点从小时链表转移到秒级链表 */
            ulInsTimerPos = DHCPC_GET_SECOND_INSPOS(pstTimerNode->usSecondField * DHCPC_MILLSECONDS_PER_SECOND / DHCPC_SECOND_TIMER_INTERVAL);
            pstTimerNode->usSecondField = 0;   /* 转入秒级链表后，该值需要清零 */
            pstTimerNode->ucListType = DHCPC_LIST_TYPE_SECOND;
            DHCPC_putTimerNodeToTimerList(g_pstDHCPTimerSecondList, pstTimerNode, ulInsTimerPos);
            g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_HOUR]--;
            g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_SECOND]++;
            pstTimerNode = pstTempNode;
            continue;
        }

        /* 租约时长超过31天的情况，月份减1 */
        pstTimerNode->ulCircleNum--;

        pstTimerNode = pstTempNode;
    }

    return;
}


VOID DHCPC_DealBusAndDelFromTimerList(DHCPC_TIMER_NODE_S *pstTimerNode)
{
    ULONG ulTeidc = pstTimerNode->ulTeidc;
    UCHAR ucIpType = pstTimerNode->ucIpType;
    UCHAR ucEvent = pstTimerNode->ucEvent;
    DHCPC_TIMER_CALLBACK pCallBackFun = pstTimerNode->pCallBackFun;

    /* 从链表中删除该节点 */
    (VOID)DHCPC_CutTimerNodeFromTimerList(pstTimerNode);

    /* 执行回调函数，进行业务处理 */
    (VOID)pCallBackFun(ucIpType, ulTeidc, ucEvent);

    return;
}


ULONG DHCPC_DeleteNodeFromHashListByNode(DHCPC_TIMER_NODE_S *pstTimerNode, DHCPC_TIMER_NODE_S **ppstTimerNode)
{
    DHCPC_TIMER_NODE_S *pstPrevNode = NULL;
    DHCPC_TIMER_NODE_S *pstCurrNode = NULL;

    ULONG ulHashKey = DHCPC_GET_HASHKEY(pstTimerNode->ulTeidc);

    *ppstTimerNode = NULL;

    pstPrevNode = g_pstDHCPTimerHashList[ulHashKey].pstNextNode;
    pstCurrNode = pstPrevNode;

    /* 如果一个节点都没有，必然是查找失败 */
    if (NULL == pstPrevNode)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_NODE_IN_HASH_LIST);
        return VOS_ERR;
    }

    while(NULL != pstCurrNode)
    {
        if (pstCurrNode == pstTimerNode)
        {
            /* 从哈希链中摘除 */
            /* 是头结点的情况 */
            if (pstPrevNode == pstCurrNode)
            {
                g_pstDHCPTimerHashList[ulHashKey].pstNextNode = pstCurrNode->pstHashNextNode;
            }
            else
            {
                pstPrevNode->pstHashNextNode = pstCurrNode->pstHashNextNode;
            }

            pstCurrNode->pstHashNextNode = NULL;
            *ppstTimerNode = pstCurrNode;
            return VOS_OK;
        }

        /* 改变循环变量 */
        pstPrevNode = pstCurrNode;
        pstCurrNode = pstCurrNode->pstHashNextNode;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NODE_NOT_IN_HASH_LIST);
    return VOS_ERR;
}


VOID DHCPC_ProcSecondListTimerOut()
{
    ULONG ulCurIndex = 0;
    DHCPC_TIMER_NODE_S *pstTempNode = NULL;
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;
    DHCPC_TIMER_NODE_S *pstHashNode = NULL;

    /* 将秒级节点链表当前索引加1，并获取值 */
    ulCurIndex = DHCPC_incCurTimerSecondPos();

    pstTimerNode = g_pstDHCPTimerSecondList[ulCurIndex].pstNextNode;

    while (NULL != pstTimerNode)
    {
        /* 上一个节点不能为空 */
        if (NULL == pstTimerNode->pstPrevNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_HOURNODE_CANNOT_BE_HEAD);
            break;
        }

        /* 上一个节点的下一个节点必须是本节点 */
        if (pstTimerNode != pstTimerNode->pstPrevNode->pstNextNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_HOURLIST_LINK_ERROR);
            break;
        }

        /* 秒级定时器的时间不为0时，说明处理上有点问题，计数记录 */
        if (0 != pstTimerNode->usSecondField)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SECOND_FIELD_VALUE_ERROR);
        }

        /* 保存下一节点 */
        pstTempNode = pstTimerNode->pstNextNode;

        pstHashNode = NULL;
        /* 从哈希节链表删除 */
        (VOID)DHCPC_DeleteNodeFromHashListByNode(pstTimerNode, &pstHashNode);
        if (NULL == pstHashNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMER_UP_FIND_HASH_ERROR);
        }

        /* 进行业务处理 */
        DHCPC_DealBusAndDelFromTimerList(pstTimerNode);
        pstTimerNode = pstTempNode;
    }

    return;
}


VOID DHCPC_SecondListTimerOut(VOID *pvArg)
{

    /* 处理秒级链表 */
    DHCPC_ProcSecondListTimerOut();

    return;
}


