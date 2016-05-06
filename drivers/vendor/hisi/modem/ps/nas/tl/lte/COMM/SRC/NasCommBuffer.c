/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasCommBuffer.c
    Description : 缓存区相关处理
    History     :
     1.李洪 00150010        2010-01-28  Draft Enact
     2.李洪 00150010        2010-04-29  Modify

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasCommBuffer.h"
#include    "LPsOm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASCOMMBUFFER_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASCOMMBUFFER_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/* ESM缓存区 */
VOS_UINT8                               g_aucEsmBuff[NAS_COMM_BUFF_ESM_MAX_ITEM_NUM][NAS_COMM_BUFF_ESM_ITEM_MAX_SIZE + NAS_COMM_BUFF_ITEM_RESERVED_LEN];

/* EMM缓存区 */
VOS_UINT8                               g_aucEmmBuff[NAS_COMM_BUFF_EMM_MAX_ITEM_NUM][NAS_COMM_BUFF_EMM_ITEM_MAX_SIZE + NAS_COMM_BUFF_ITEM_RESERVED_LEN];

/* 缓存类型表 */
NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU    g_astNasBuffTypeTable[] =
{
    {NAS_COMM_BUFF_TYPE_ESM,  NAS_COMM_BUFF_ESM_MAX_ITEM_NUM, {0},&g_aucEsmBuff[0][0], NAS_COMM_BUFF_ESM_ITEM_MAX_SIZE},
    {NAS_COMM_BUFF_TYPE_EMM,  NAS_COMM_BUFF_EMM_MAX_ITEM_NUM, {0},&g_aucEmmBuff[0][0],NAS_COMM_BUFF_EMM_ITEM_MAX_SIZE}
};

/* 缓存区控制表 */
NAS_COMM_BUFFER_CTRL_BLOCK_STRU         g_astNasBuffCtrlBlockTable[NAS_COMM_BUFF_NUM];

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e826*/
/*****************************************************************************
 Function Name   : NAS_COMM_CheckBuff
 Description     : 判断用户请求释放的地址是否合法
 Input           : pucBuffItemAddr-----------缓存记录首地址
                   ulMaxBuffItemLen----------缓存记录最大长度
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-22  Modify

*****************************************************************************/
/*lint -e961*/
VOS_UINT32  NAS_COMM_CheckBuff
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
)
{
    NAS_COMM_BUFFER_ITEM_HEAD_STRU     *pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU*)pucBuffItemAddr;
    VOS_UINT32                         *pulNasBuffItemTail = VOS_NULL_PTR;

    /* 判断缓存记录头保护标识是否正确 */
    if (pstNasBuffItemHead->ulProtCrc != NAS_COMM_BUFF_PROT_CRC)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_CheckBuff:WARN:Buffer head protect flag is modified!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_CheckBuff_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_COMM_BUFF_CHECK_FAIL;
    }

    /* 计算缓存记录尾地址 */
    pulNasBuffItemTail = (VOS_UINT32*)( pucBuffItemAddr +
                                        NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN +
                                        ulMaxBuffItemLen);

    /* 判断缓存记录尾保护标识是否正确 */
    if (*pulNasBuffItemTail != NAS_COMM_BUFF_PROT_CRC)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_CheckBuff:WARN:Buffer tail protect flag is modified!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_CheckBuff_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_COMM_BUFF_CHECK_FAIL;
    }

    return NAS_COMM_BUFF_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_COMM_InitBuffItem
 Description     : 初始化缓存记录
 Input           : pucBuffItemAddr-----------缓存记录首地址
                   ulMaxBuffItemLen----------缓存记录最大长度
 Output          :
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-24  Modify

*****************************************************************************/
VOS_VOID  NAS_COMM_InitBuffItem
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
)
{
    NAS_COMM_BUFFER_ITEM_HEAD_STRU     *pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU*)pucBuffItemAddr;
    VOS_UINT32                         *pulNasBuffItemTail = VOS_NULL_PTR;

    /* 标识记录未分配 */
    pstNasBuffItemHead->ucUsedTag = NAS_COMM_BUFF_ITEM_UNUSED;

    /* 赋值缓存记录头保护标识 */
    pstNasBuffItemHead->ulProtCrc = NAS_COMM_BUFF_PROT_CRC;

    /* 计算缓存记录尾地址 */
    pulNasBuffItemTail = (VOS_UINT32*)( pucBuffItemAddr +
                                        NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN +
                                        ulMaxBuffItemLen);

    /* 赋值缓存记录尾保护标识 */
    *pulNasBuffItemTail = NAS_COMM_BUFF_PROT_CRC;
}

/*****************************************************************************
 Function Name   : NAS_COMM_ClearBuffItem
 Description     : 清除缓存记录
 Input           : pucBuffItemAddr-----------缓存记录首地址
                   ulMaxBuffItemLen----------缓存记录最大长度
 Output          :
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-4-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_COMM_ClearBuffItem
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
)
{
    NAS_COMM_BUFFER_ITEM_HEAD_STRU     *pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU *)pucBuffItemAddr;

    /* 标识记录未分配 */
    pstNasBuffItemHead->ucUsedTag = NAS_COMM_BUFF_ITEM_UNUSED;

    /* 清除缓存记录内容 */
    /*lint -e960*/
    NAS_COMM_MEM_SET_S( (pucBuffItemAddr + NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN),
                        ulMaxBuffItemLen,
                        NAS_COMM_NULL,
                        ulMaxBuffItemLen);
    /*lint +e960*/
}


/*****************************************************************************
 Function Name   : NAS_COMM_QueryBuffTypeTableItem
 Description     : 查找缓存类型表记录
 Input           : enNasBuffType----------------NAS缓存类型
                   pulIndex---------------------缓存类型表记录索引号指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-4-21  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_COMM_QueryBuffTypeTableItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTable      = NAS_GetBufferTypeTable();

    /* 查找与输入参数pstBuff相同的记录 */
    for (ulCnt = NAS_COMM_NULL; ulCnt < NAS_COMM_BUFF_NUM; ulCnt++)
    {
        /*lint -e960*/
        if (enNasBuffType == pstBufferTypeTable[ulCnt].enNasBufferType)
        {
            break;
        }
        /*lint +e960*/
    }

    if (ulCnt < NAS_COMM_BUFF_NUM)
    {
        *pulIndex = ulCnt;
        return NAS_COMM_BUFF_SUCCESS;
    }

    return NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL;
}

/*****************************************************************************
 Function Name   : NAS_COMM_InitBuff
 Description     : 初始化缓存区
 Input           : enNasBuffType----------------NAS缓存类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-22  Modify

*****************************************************************************/
VOS_VOID  NAS_COMM_InitBuff
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8            enNasBuffType
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT8                               ucMaxBuffItemNum        = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;

    /* 判断缓存类型是否合法 */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_InitBuff:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_InitBuff_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* 获取缓存类型表记录 */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ucMaxBuffItemNum        = pstBufferTypeTableItem->ucMaxBuffItemNum;
    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* 获取缓存控制块 */
    pstBuffCtrlBlock    = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* 清除缓存区控制块 */
    /*lint -e960*/
    NAS_COMM_MEM_SET_S(   pstBuffCtrlBlock,
                        sizeof(NAS_COMM_BUFFER_CTRL_BLOCK_STRU),
                        NAS_COMM_NULL,
                        sizeof(NAS_COMM_BUFFER_CTRL_BLOCK_STRU));

    /* 清除缓存区空间 */
    NAS_COMM_MEM_SET_S(   pstBufferTypeTableItem->pucBuff,
                        ucMaxBuffItemNum * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN),
                        NAS_COMM_NULL,
                        ucMaxBuffItemNum * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));
    /*lint +e960*/
    /* 赋值已用记录个数为0 */
    pstBuffCtrlBlock->ucUsedNum     = NAS_COMM_NULL;

    /* 赋值最大存储记录个数 */
    pstBuffCtrlBlock->ucMaxNum      = ucMaxBuffItemNum;

    /* 赋值存储记录最大长度 */
    pstBuffCtrlBlock->ulMaxItemLen  = ulMaxBuffItemLen;

    /* 将缓存去标记为已初始化 */
    pstBuffCtrlBlock->enState = NAS_COMM_BUFF_STATE_INITED;

    for (ulCnt = NAS_COMM_NULL; ulCnt < pstBuffCtrlBlock->ucMaxNum; ulCnt++)
    {
        /* 计算当前缓存记录首地址 */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        /* 初始化缓存记录 */
        NAS_COMM_InitBuffItem(pucBuffItemAddr, ulMaxBuffItemLen);
    }
}

/*****************************************************************************
 Function Name   : NAS_COMM_AllocBuffItem
 Description     : 分配新的缓存记录
 Input           : enNasBuffType------------NAS缓存类型
                   ulAllocLen---------------请求分配空间大小
 Return          : VOS_VOID*

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-22  Modify

*****************************************************************************/
VOS_VOID*  NAS_COMM_AllocBuffItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    VOS_UINT32                          ulAllocLen
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT8                               ucMaxBuffItemNum        = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_ITEM_HEAD_STRU         *pstNasBuffItemHead      = VOS_NULL_PTR;

    /* 判断缓存类型是否合法 */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL1);
        return VOS_NULL_PTR;
    }

    /* 获取缓存类型表记录 */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ucMaxBuffItemNum        = pstBufferTypeTableItem->ucMaxBuffItemNum;
    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* 获取缓存控制块 */
    pstBuffCtrlBlock    = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* 判断缓存区是否已初始化 */
    if (pstBuffCtrlBlock->enState != NAS_COMM_BUFF_STATE_INITED)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:The buffer is not initialized!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL2);
        return VOS_NULL_PTR;
    }

    /* 判断用户请求的空间大小是否超出了缓存记录的最大长度 */
    if (ulAllocLen > ulMaxBuffItemLen)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:The request of alloc space is too big!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL3);
        return VOS_NULL_PTR;
    }

    /* 判断缓存区是否已满 */
    if (pstBuffCtrlBlock->ucUsedNum >= ucMaxBuffItemNum)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:Insufficent resources!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL4);
        return VOS_NULL_PTR;
    }

    /* 检索尚未使用的缓存空间，分配给用户 */
    for (ulCnt = NAS_COMM_NULL; ulCnt < ucMaxBuffItemNum; ulCnt++)
    {
        /* 计算缓存记录首地址 */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU *)pucBuffItemAddr;
        if (NAS_COMM_BUFF_ITEM_UNUSED == pstNasBuffItemHead->ucUsedTag)
        {
            /* 已分配记录数加1 */
            pstBuffCtrlBlock->ucUsedNum++;

            /* 标识记录已分配 */
            pstNasBuffItemHead->ucUsedTag = NAS_COMM_BUFF_ITEM_USED;

            return (VOS_VOID*)(pucBuffItemAddr + NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN);
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_COMM_FreeBuffItem
 Description     : 释放缓存记录
 Input           : enNasBuffType----------------NAS缓存类型
                   pBufferItemAddr--------------缓存记录地址
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-04-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_COMM_FreeBuffItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    const VOS_VOID                     *pBufferItemStorageAddr
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT8                               ucMaxBuffItemNum        = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_ITEM_HEAD_STRU         *pstNasBuffItemHead      = VOS_NULL_PTR;

    /* 判断缓存类型是否合法 */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    /* 判断用户请求释放的地址是否为空 */
    if (pBufferItemStorageAddr == VOS_NULL_PTR)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:Input para pBufferItemStorageAddr is null!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    /* 获取缓存类型表记录 */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ucMaxBuffItemNum        = pstBufferTypeTableItem->ucMaxBuffItemNum;
    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* 获取缓存控制块 */
    pstBuffCtrlBlock    = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* 判断缓存区是否已初始化 */
    if (pstBuffCtrlBlock->enState != NAS_COMM_BUFF_STATE_INITED)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:The buffer is not initialized!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL3);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    /* 获取缓存记录首地址 */
    pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU *)
                         ((VOS_UINT8 *)pBufferItemStorageAddr - NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN);

    /* 判断用户请求释放的地址是否合法 */
    if (NAS_COMM_BUFF_SUCCESS != NAS_COMM_CheckBuff((VOS_UINT8*)pstNasBuffItemHead, ulMaxBuffItemLen))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:NAS_COMM_CheckBuff failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL4);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    for (ulCnt = NAS_COMM_NULL; ulCnt < ucMaxBuffItemNum; ulCnt++)
    {
        /* 计算当前缓存记录首地址 */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        /* 判断当前缓存记录是否为用户请求释放的缓存记录 */
        /*lint -e960*/
        if ((VOS_UINT8*)pstNasBuffItemHead == pucBuffItemAddr)
        {
            break;
        }
        /*lint +e960*/
    }

    if (ulCnt >= ucMaxBuffItemNum)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN: The input pointer address is not in buffer list!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL5);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    if ((pstNasBuffItemHead->ucUsedTag == NAS_COMM_BUFF_ITEM_USED))
    {
        /* 已分配记录数减1 */
        pstBuffCtrlBlock->ucUsedNum--;

        /* 初始化缓存记录 */
        NAS_COMM_ClearBuffItem((VOS_UINT8 *)pstNasBuffItemHead, ulMaxBuffItemLen);
    }

    return NAS_COMM_BUFF_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_COMM_ClearBuff
 Description     : 清空缓存区
 Input           : enNasBuffType----------------NAS缓存类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-4-24  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_COMM_ClearBuff
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;

    /* 判断缓存类型是否合法 */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_ClearBuff:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_ClearBuff_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* 获取缓存类型表记录 */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* 获取缓存控制块 */
    pstBuffCtrlBlock        = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* 赋值已用记录个数为0 */
    pstBuffCtrlBlock->ucUsedNum = NAS_COMM_NULL;

    for (ulCnt = NAS_COMM_NULL; ulCnt < pstBuffCtrlBlock->ucMaxNum; ulCnt++)
    {
        /* 计算当前缓存记录首地址 */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        /* 清除缓存记录 */
        NAS_COMM_ClearBuffItem(pucBuffItemAddr, ulMaxBuffItemLen);
    }
}
/*lint +e826*/
/*lint +e961*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasCommBuffer.c */
