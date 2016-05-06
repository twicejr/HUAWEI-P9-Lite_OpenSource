/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_OS_Memory.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月30日
  最近修改   :
  功能描述   : 实现内存处理相关函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月30日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_OS_Memory.h"
#include "BST_OS_Thread.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_OS_MEMORY_C
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/
#define BST_MEM_CTRL_BLOCK_NUMBER       (2)
#define BST_BUF_CTRL_BLOCK_NUMBER       (2)

/*每种类型内存允许注册的回调函数最大个数*/
#define BST_MEM_STATUS_CALLBACK_MAX_NUMBER         (3)

#define BST_MEM_LOW_LEVEL_THRESHOLD     (12)
#define BST_MEM_HIGH_LEVEL_THRESHOLD    ( BST_DYNAMIC_SIZE2_MAX_NUM - 12 )
#define BST_PBUF_LOW_LEVEL_THRESHOLD    (12)
#define BST_PBUF_HIGH_LEVEL_THRESHOLD   ( BST_PBUF_SIZE2_MAX_NUM - 12 )

#define BST_DYNAMIC_MEM_SIZE1           (128)
#define BST_DYNAMIC_MEM_SIZE2           (1500)

#define BST_DYNAMIC_SIZE1_MAX_NUM       (1024)
#define BST_DYNAMIC_SIZE2_MAX_NUM       (64)


#define BST_PBUF_SIZE1                  (128)
#define BST_PBUF_SIZE2                  (BST_IP_MTU_SIZE)

#define BST_PBUF_SIZE1_MAX_NUM          (512)
#define BST_PBUF_SIZE2_MAX_NUM          (220)


#define BST_NOT_USED                    (0x00)
#define BST_USED                        (0x01)
#define BST_MEMORY_CRC                  (0x55AA55AAUL)
#define BST_MEM_HEAD_BLOCK_SIZE         ( sizeof(BST_MEM_HEAD_BLOCK) )

/* be used the head and tail of memory to protect overflow */
#define BST_MEMORY_PROTECT_SIZE                               1024

/* the number of words which on the head of the user's space */
#define BST_MEMORY_RESERVED_WORD_HEAD                          2

/* the number of words which on the tail of the user's space */
#define BST_MEMORY_RESERVED_WORD_TAIL                          1

/* the number of bytes which on the user's space */
#define BST_MEMORY_RESERVED_BYTES \
    ((sizeof(BST_UINT_PTR) * BST_MEMORY_RESERVED_WORD_HEAD) \
    + (sizeof(BST_UINT_PTR) * BST_MEMORY_RESERVED_WORD_TAIL))

/* the begin address of user's space */
BST_UINT_PTR             g_ulBstSpaceStart;

/* the end address of user's space */
BST_UINT_PTR             g_ulBstSpaceEnd;

/* the begin address of user's space */
BST_UINT_PTR             g_ulBstSpaceAndProtectionStart;

/* the end address of user's space */
BST_UINT_PTR             g_ulBstSpaceAndProtectionEnd;

/* 自旋锁，用来作Memory的临界资源保护 */
BST_OS_SPINLOCK_T        g_stBstMemSpinLock;

/*****************************************************************************
  3 函数声明
*****************************************************************************/
BST_VOID BST_OS_MemStatusReport( BST_MEM_TYPE_ENUM_UINT8 enType );

/******************************************************************************
   4 私有定义
******************************************************************************/
typedef struct
{
    BST_UINT32                          ulSize;
    BST_UINT32                          ulNumber;
}BST_MEM_BLOCK_INFO;


typedef struct BST_MEM_HEAD_BLOCK
{
    BST_UINT_PTR                        ulMemCtrlAddress;  /* the address of  BST_MEM_CTRL_BLOCK */
    BST_UINT_PTR                        ulMemAddress;      /* the address of User's */
    BST_UINT32                          ulMemUsedFlag;     /* whether be used or not */
    struct BST_MEM_HEAD_BLOCK          *pstNext;           /*  next block whether allocated or not */
} BST_MEM_HEAD_BLOCK;

typedef struct
{
    BST_INT32                           lBlockLength;       /* block size */
    BST_INT32                           lTotalBlockNumber;  /* block number */
    BST_UINT_PTR                        ulBuffer;           /*start address of block */
    BST_UINT_PTR                        ulBufferEnd;        /*end address of block*/
    BST_INT32                           lIdleBlockNumber;   /* the number of free block*/
    BST_MEM_HEAD_BLOCK                 *pstBlocks;          /*list of free block*/
    BST_MEM_TYPE_ENUM_UINT8             enType;             /*mem type pbuf or dynamic*/
    BST_UINT8                           aucReversed[3];
} BST_MEM_CTRL_BLOCK;


typedef struct
{
    BST_MEM_STATUS_CALLBACK_FUNC        pfCallBack;        /*注册的回调函数*/
    BST_UINT16                          usLastReportValue; /*上次上报的值*/
    BST_UINT8                           aucReversed[2];    /*保留字段*/
} BST_MEM_STATUE_CALLBACK_INFO;

/******************************************************************************
   5 全局变量定义
******************************************************************************/
BST_MEM_BLOCK_INFO g_BstMemBlockInfo[BST_MEM_CTRL_BLOCK_NUMBER]={
                                                                    {BST_DYNAMIC_MEM_SIZE1,BST_DYNAMIC_SIZE1_MAX_NUM},
                                                                    {BST_DYNAMIC_MEM_SIZE2,BST_DYNAMIC_SIZE2_MAX_NUM},    
                                                                };

BST_MEM_BLOCK_INFO g_BstBufBlockInfo[BST_BUF_CTRL_BLOCK_NUMBER]={
                                                                    {BST_PBUF_SIZE1, BST_PBUF_SIZE1_MAX_NUM},
                                                                    {BST_PBUF_SIZE2, BST_PBUF_SIZE2_MAX_NUM},
                                                                };

/* memory control blocks */
BST_MEM_CTRL_BLOCK                      g_BstMemCtrlBlk[BST_MEM_CTRL_BLOCK_NUMBER];

/* buf blocks */
BST_MEM_CTRL_BLOCK                      g_BstBufCtrlBlk[BST_BUF_CTRL_BLOCK_NUMBER];


BST_CHAR                                g_acBstMemBuf[900*1024];


/* the start address of mem pool */
BST_UINT_PTR g_ulBstMemPoolIntervalAddress[BST_MEM_TYPE_BUTT+1];

/*记录内存状态回调函数注册结果*/
BST_MEM_STATUE_CALLBACK_INFO            g_acBstMemCallBackInfo[BST_MEM_TYPE_BUTT][BST_MEM_STATUS_CALLBACK_MAX_NUMBER];

/******************************************************************************
   6 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : BST_OS_StaticMemCtrlBlkInit
 功能描述  : 静态内存处理初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_OS_StaticMemCtrlBlkInit( BST_MEM_CTRL_BLOCK *BST_MemCtrlBlock,
                      BST_INT32 lBlockLength, BST_INT32 lTotalBlockNumber,
                      BST_UINT_PTR *ulCtrlAddress, BST_UINT_PTR *ulSpaceAddress )
{
    BST_UINT32                          ulLength;
    BST_INT32                           i;
    BST_MEM_HEAD_BLOCK                 *Block;
    BST_UINT_PTR                        ulTemp;
    BST_UINT_PTR                       *pulTemp;

    if( ( BST_NULL_PTR == BST_MemCtrlBlock )
        ||( BST_NULL_PTR == ulCtrlAddress )
        ||( BST_NULL_PTR == ulSpaceAddress ) )
    {
        return;
    }

    BST_MemCtrlBlock->lBlockLength      = lBlockLength;
    BST_MemCtrlBlock->lTotalBlockNumber = lTotalBlockNumber;
    BST_MemCtrlBlock->lIdleBlockNumber  = lTotalBlockNumber;

    ulLength = (BST_UINT32)(BST_MEMORY_RESERVED_BYTES + lBlockLength);

    BST_MemCtrlBlock->ulBuffer = *ulSpaceAddress;
    BST_MemCtrlBlock->ulBufferEnd = *ulSpaceAddress
        + ulLength * lTotalBlockNumber;

    BST_MemCtrlBlock->pstBlocks = (BST_MEM_HEAD_BLOCK *)(*ulCtrlAddress);

    Block = BST_MemCtrlBlock->pstBlocks;

    ulTemp = BST_MemCtrlBlock->ulBuffer;

    for( i=1; i<lTotalBlockNumber; i++)
    {
        Block->ulMemCtrlAddress = (BST_UINT_PTR)BST_MemCtrlBlock;
        Block->ulMemAddress = ulTemp;
        Block->ulMemUsedFlag = BST_NOT_USED;
        Block->pstNext = Block + 1;

        /* add protection on head */
        pulTemp = (BST_UINT_PTR*)ulTemp;
        *pulTemp = (BST_UINT_PTR)Block;
        pulTemp++;
        *pulTemp = BST_MEMORY_CRC;

        /* offset next */
        Block++;
        ulTemp += ulLength;

        /* add protection on tail */
        pulTemp = (BST_UINT_PTR *)ulTemp;
        pulTemp--;
        *pulTemp = BST_MEMORY_CRC;
    }
    Block->ulMemCtrlAddress = (BST_UINT_PTR)BST_MemCtrlBlock;
    Block->ulMemAddress = ulTemp;
    Block->ulMemUsedFlag = BST_NOT_USED;
    Block->pstNext = BST_NULL_PTR;
     /* add protection on head */
    pulTemp = (BST_UINT_PTR *)ulTemp;
    *pulTemp = (BST_UINT_PTR)Block;
    pulTemp++;
    *pulTemp = BST_MEMORY_CRC;

    /* offset next */
    Block++;
    ulTemp += ulLength;

    /* add protection on tail */
    pulTemp = (BST_UINT_PTR *)ulTemp;
    pulTemp--;
    *pulTemp = BST_MEMORY_CRC;

    *ulCtrlAddress = (BST_UINT_PTR)Block;
    *ulSpaceAddress = ulTemp;
}


 /*****************************************************************************
  函 数 名  : BST_OS_StaticMemInit
  功能描述  : 静态内存处理初始化
  输入参数  : 无
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :
  修改历史  :
     1.日    期   : 2015年05月27日
       作    者   : z00128442
       修改内容   : 新生成函数
 *****************************************************************************/
BST_UINT32 BST_OS_StaticMemInit( BST_VOID )
{
    BST_INT32                           i;
    BST_UINT32                          lTotalSize = 0;
    BST_UINT32                          lTotalCtrlSize = 0;
    BST_VOID                           *pCtrlStart;
    BST_UINT_PTR                        ulSpaceStart;
    BST_UINT_PTR                        ulSpaceEnd;
    BST_UINT_PTR                        ulCtrlStart;
    BST_INT32                           ulIndex;
    /* calculate mem's size */
    for ( i=0; i<BST_MEM_CTRL_BLOCK_NUMBER; i++ )
    {
        if ( 0x00000003 & g_BstMemBlockInfo[i].ulSize )/* 4 byte Aligned */
        {
            BST_DBG_LOG2("BST_OS_StaticMemInit MemBlockInfo[%d].size(%d) not aligned.\r\n",
                i, g_BstMemBlockInfo[i].ulSize );

            return BST_MEM_ERROR;
        }

        lTotalSize += ( g_BstMemBlockInfo[i].ulSize + BST_MEMORY_RESERVED_BYTES
            + BST_MEM_HEAD_BLOCK_SIZE )
            * g_BstMemBlockInfo[i].ulNumber;
        lTotalCtrlSize += BST_MEM_HEAD_BLOCK_SIZE * g_BstMemBlockInfo[i].ulNumber;
    }
    
    /* calculate buf's size */
    for ( i=0; i<BST_BUF_CTRL_BLOCK_NUMBER; i++ )
    {
        if ( 0x00000003 & g_BstBufBlockInfo[i].ulSize )/* 4 byte Aligned */
        {
            BST_DBG_LOG2("BST_OS_StaticMemInit bufMemBlockInfo[%d].size(%d) not aligned.\r\n",
                    i, g_BstBufBlockInfo[i].ulSize );

            return BST_MEM_ERROR;
        }

        lTotalSize += ( g_BstBufBlockInfo[i].ulSize + BST_MEMORY_RESERVED_BYTES
            + BST_MEM_HEAD_BLOCK_SIZE )
            * g_BstBufBlockInfo[i].ulNumber;
        lTotalCtrlSize += BST_MEM_HEAD_BLOCK_SIZE * g_BstBufBlockInfo[i].ulNumber;
    }

    /* add protected space */
    lTotalSize += 2 * BST_MEMORY_PROTECT_SIZE;
    lTotalCtrlSize += BST_MEMORY_PROTECT_SIZE;

    if ( lTotalSize > sizeof(g_acBstMemBuf) )
    {
        BST_DBG_LOG2("mem init failed, lTotalSize:%d > available:%d",lTotalSize,sizeof(g_acBstMemBuf));
        return BST_MEM_ERROR;
    }

    pCtrlStart = (BST_VOID *)g_acBstMemBuf;

    ulCtrlStart = (BST_UINT_PTR)pCtrlStart;

    ulSpaceStart = ulCtrlStart + lTotalCtrlSize;
    g_ulBstSpaceStart = ulSpaceStart;

    ulSpaceEnd = ulCtrlStart + lTotalSize - BST_MEMORY_PROTECT_SIZE ;
    g_ulBstSpaceEnd = ulSpaceEnd;

    g_ulBstSpaceAndProtectionStart = g_ulBstSpaceStart - BST_MEMORY_PROTECT_SIZE;

    g_ulBstSpaceAndProtectionEnd = g_ulBstSpaceEnd + BST_MEMORY_PROTECT_SIZE;

    /* the start address of msg pool */
    g_ulBstMemPoolIntervalAddress[0] = g_ulBstSpaceStart;

    for ( i=0; i<BST_MEM_CTRL_BLOCK_NUMBER; i++ )
    {
       BST_OS_StaticMemCtrlBlkInit( &g_BstMemCtrlBlk[i],  ( BST_INT32 )g_BstMemBlockInfo[i].ulSize,
            ( BST_INT32 )g_BstMemBlockInfo[i].ulNumber, &ulCtrlStart, &ulSpaceStart);
       g_BstMemCtrlBlk[i].enType        = BST_MEM_TYPE_DYNAMIC;
    }

    /* the start address of mem pool */
    g_ulBstMemPoolIntervalAddress[1] = ulSpaceStart;

    for ( i=0; i<BST_BUF_CTRL_BLOCK_NUMBER; i++ )
    {
        BST_OS_StaticMemCtrlBlkInit( &g_BstBufCtrlBlk[i], (BST_INT32)g_BstBufBlockInfo[i].ulSize,
            (BST_INT32)g_BstBufBlockInfo[i].ulNumber, &ulCtrlStart, &ulSpaceStart);
        g_BstBufCtrlBlk[i].enType        = BST_MEM_TYPE_PBUF;
    }

    /* the start address of app mem pool */
    g_ulBstMemPoolIntervalAddress[2] = ulSpaceStart;

    /* 初始化内存状态状态注册回调函数*/
    for ( i=0; i<BST_MEM_TYPE_BUTT; i++ )
    {
        for(ulIndex=0; ulIndex < BST_MEM_STATUS_CALLBACK_MAX_NUMBER; ulIndex++)
        {
            g_acBstMemCallBackInfo[i][ulIndex].pfCallBack = BST_NULL_PTR;
            g_acBstMemCallBackInfo[i][ulIndex].usLastReportValue = BST_MEM_HIGH_LEVEL;
        }
    }
    BST_OS_InitSpinLock(&g_stBstMemSpinLock);

    return BST_MEM_OK;
}

/*****************************************************************************
 函 数 名  : BST_OS_StaticMemCtrlBlkMalloc
 功能描述  : 静态内存分配
 输入参数  : BST_MemCtrlBlock  需要申请的内存对应的控制块
 输出参数  :
 返 回 值  :  ulMemAddress 返回对应的地址
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID* BST_OS_StaticMemCtrlBlkMalloc( BST_MEM_CTRL_BLOCK *BST_MemCtrlBlock)
{
    BST_ULONG             ulLockLevel;
    BST_MEM_HEAD_BLOCK   *Block;
    BST_UINT_PTR         *pulTemp;
    BST_UINT_PTR          ulBlockAddr;
    BST_UINT32            ulCrcTag;

    if ( BST_NULL_PTR == BST_MemCtrlBlock )
    {
        return((BST_VOID*)BST_NULL_PTR);
    }

    ulLockLevel = BST_OS_SpinLock(&g_stBstMemSpinLock);

    if( 0 >= BST_MemCtrlBlock->lIdleBlockNumber )
    {
        BST_OS_SpinUnLock(&g_stBstMemSpinLock, ulLockLevel);

        return((BST_VOID*)BST_NULL_PTR);
    }
    else
    {
        BST_MemCtrlBlock->lIdleBlockNumber--;
        Block = BST_MemCtrlBlock->pstBlocks;
        Block->ulMemUsedFlag = BST_USED;
        BST_MemCtrlBlock->pstBlocks = Block->pstNext;
    }

    BST_OS_SpinUnLock(&g_stBstMemSpinLock, ulLockLevel);


    /* check memory */
    pulTemp = (BST_UINT_PTR*)(Block->ulMemAddress);

    ulBlockAddr = *pulTemp++;
    ulCrcTag = *pulTemp;

    if ( ((BST_UINT_PTR)Block != ulBlockAddr) || (BST_MEMORY_CRC != ulCrcTag) )
    {
        return((BST_VOID*)BST_NULL_PTR);
    }

    return (BST_VOID *)Block->ulMemAddress;
}


/*****************************************************************************
 函 数 名  : BST_OS_StaticMemCtrlBlkFree
 功能描述  : 释放指定内存块的地址
 输入参数  : BST_MemCtrlBlock  --需要释放的控制块地址
                           Block                      --需要释放的block地址
 输出参数  : BST_MEM_ERROR  free地址
 返 回 值  : BST_MEM_OK  代表释放完成，其他代码异常
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_UINT32 BST_OS_StaticMemCtrlBlkFree( BST_MEM_CTRL_BLOCK *BST_MemCtrlBlock,
                               BST_MEM_HEAD_BLOCK *Block )
{
    BST_UINT32           ulLockLevel;

    if (( BST_NULL_PTR == BST_MemCtrlBlock )
        ||( BST_NULL_PTR == Block ))
    {
        return BST_MEM_ERROR;
    }

    ulLockLevel = BST_OS_SpinLock(&g_stBstMemSpinLock);

    if ( BST_NOT_USED == Block->ulMemUsedFlag )
    {
        BST_OS_SpinUnLock(&g_stBstMemSpinLock, ulLockLevel);

        BST_RLS_LOG("# Free Msg again.");

        return BST_MEM_ERROR;
    }

    Block->ulMemUsedFlag = BST_NOT_USED;
    Block->pstNext = BST_MemCtrlBlock->pstBlocks;
    BST_MemCtrlBlock->pstBlocks = Block;

    BST_MemCtrlBlock->lIdleBlockNumber++;

    BST_OS_MemStatusReport( BST_MemCtrlBlock->enType );

    BST_OS_SpinUnLock(&g_stBstMemSpinLock, ulLockLevel);

    return BST_MEM_OK;
}


/*****************************************************************************
 函 数 名  : BST_OS_StaticMemCheck
 功能描述  : 对传入要释放的地址的内存进行合法性检查
                           并返回释放的内存的地址段
 输入参数  : *pAddr --需要检查的内存地址
 输出参数  :pulBlock  --需要释放内存地址对应的block地址
                          pulCtrl  --需要释放内存地址对应的控制块地址
 返 回 值  : BST_UINT32  BST_MEM_OK--代表地址合法，其他为非法地址
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_UINT32 BST_OS_StaticMemCheck( BST_VOID *pAddr, BST_UINT_PTR *pulBlock,
                         BST_UINT_PTR *pulCtrl)
{
    BST_UINT_PTR                       *pulTemp;
    BST_UINT_PTR                        ulHeadValue;
    BST_UINT_PTR                        ulTailValue;
    BST_UINT_PTR                        ulBlockAddress;
    BST_MEM_HEAD_BLOCK                 *pstHeadBlock;
    BST_MEM_CTRL_BLOCK                 *pstMemCtrl;
    BST_UINT_PTR                        ulTempAddress;
    BST_UINT_PTR                        ulUserAddress;

    if (( BST_NULL_PTR == pAddr )
        ||( BST_NULL_PTR == pulBlock )
        ||( BST_NULL_PTR == pulCtrl ))
    {
        return BST_MEM_ERROR;
    }

    ulTempAddress = (BST_UINT_PTR)pAddr;

    if ( ulTempAddress < g_ulBstSpaceAndProtectionStart
        || ulTempAddress > g_ulBstSpaceAndProtectionEnd )
    {
        BST_RLS_LOG("# BST MEM adder is error");
        return(BST_MEM_ERROR);
    }

    if ( ulTempAddress <= g_ulBstSpaceStart
        || ulTempAddress >= g_ulBstSpaceEnd )
    {

        BST_RLS_LOG("# BST MEM ADDR OVERFLOW");
        return(BST_MEM_ERROR);
    }

    pulTemp = (BST_UINT_PTR *)pAddr;

    pulTemp -= BST_MEMORY_RESERVED_WORD_HEAD;

    ulUserAddress = (BST_UINT_PTR)pulTemp;

    ulBlockAddress = *pulTemp;
    pulTemp++;
    ulHeadValue = *pulTemp;
    pulTemp++;

    if ( BST_MEMORY_CRC != ulHeadValue )
    {
        BST_RLS_LOG("# BST MEM HEAD FAIL:");

        return(BST_MEM_ERROR);
    }

    pstHeadBlock = (BST_MEM_HEAD_BLOCK *)ulBlockAddress;
    if ( pstHeadBlock->ulMemAddress != ulUserAddress)
    {
        BST_RLS_LOG("# BST MEM LINK FAIL: ");

        return(BST_MEM_ERROR);
    }

    *pulBlock = ulBlockAddress;

    ulTempAddress = pstHeadBlock->ulMemCtrlAddress;
    pstMemCtrl = (BST_MEM_CTRL_BLOCK *)ulTempAddress;

    *pulCtrl = ulTempAddress;

    pulTemp = (BST_UINT_PTR *)( (BST_UINT_PTR)pulTemp + pstMemCtrl->lBlockLength );

    ulTailValue = *pulTemp;

    if ( BST_MEMORY_CRC != ulTailValue )
    {

        BST_RLS_LOG("# BST MEM TAIL FAIL:");

        return(BST_MEM_ERROR);
    }

    return BST_MEM_OK;
}

/*****************************************************************************
 函 数 名  : BST_OS_StaticMemAlloc
 功能描述  : BST内部静态内存申请
 输入参数  : enType --需要查询的内存块类型
                           ulSize  --  需要查询的内存块大小
 输出参数  : 无
 返 回 值  : 返回申请内存的首地址，BST_NULL_PTR代表申请失败
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID * BST_OS_StaticMemAlloc(BST_MEM_TYPE_ENUM_UINT8 enType, BST_UINT32 ulSize )
{
    BST_INT32                  i;
    BST_UINT_PTR         *pulSpace;
    BST_MEM_BLOCK_INFO   *pstMemInfo;
    BST_MEM_CTRL_BLOCK   *pstMemCtrl;
    BST_INT32             lCycle;

    if( 0 == ulSize )
    {
        BST_RLS_LOG("# BST_OS_StaticMemAlloc size is 0");

        return BST_NULL_PTR;
    }

    if(BST_MEM_TYPE_DYNAMIC == enType)
    {
        pstMemInfo = g_BstMemBlockInfo;
        lCycle = BST_MEM_CTRL_BLOCK_NUMBER;
        pstMemCtrl = g_BstMemCtrlBlk;
    }
    else if(BST_MEM_TYPE_PBUF == enType)
    {
        pstMemInfo = g_BstBufBlockInfo;
        lCycle = BST_BUF_CTRL_BLOCK_NUMBER;
        pstMemCtrl = g_BstBufCtrlBlk;
    }
    else
    {
        
        BST_RLS_LOG1("# V_MemAlloc wrong type:%d", enType);
        return BST_NULL_PTR;      
    }

    for ( i=0; i<lCycle; i++ )
    {
        if(ulSize <= pstMemInfo[i].ulSize )
        {
            pulSpace = (BST_UINT_PTR *)BST_OS_StaticMemCtrlBlkMalloc(&(pstMemCtrl[i]));
            if( BST_NULL_PTR != pulSpace )
            {
                /*如果当前申请的内存块是最大size的内存块，需要检查内存是否达到低内存上报的门限*/
                if( i== ( lCycle - 1 ))
                {
                    BST_OS_MemStatusReport( enType );
                }
                /* offset space which be reserved of OSA */
                pulSpace += BST_MEMORY_RESERVED_WORD_HEAD;
                BST_DBG_LOG1("BST_MemAlloc" ,pulSpace);

                return (BST_VOID *)pulSpace;
            }
        }
    }

    BST_RLS_LOG1("# alloce memory fail size %d.", (BST_INT32)ulSize);


    return BST_NULL_PTR;
}


/*****************************************************************************
 函 数 名  : BST_OS_StaticMemFree
 功能描述  : BST 内存申请的内存释放函数
 输入参数  : ppAddr  需要释放的内存地址的地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_UINT32 BST_OS_StaticMemFree(BST_VOID **ppAddr)
{
    BST_UINT_PTR                        ulBlockAdd;
    BST_UINT_PTR                        ulCtrlkAdd;
    
    BST_DBG_LOG1("BST_OS_StaticMemFree",*ppAddr);

    if( BST_NULL_PTR == ppAddr )
    {
        return BST_MEM_ERROR;
    }

    if ( BST_MEM_OK != BST_OS_StaticMemCheck( *ppAddr, &ulBlockAdd, &ulCtrlkAdd) )
    {
        BST_RLS_LOG("BST_MemFree error");
        return BST_MEM_ERROR;
    }

    return BST_OS_StaticMemCtrlBlkFree( (BST_MEM_CTRL_BLOCK *)ulCtrlkAdd,
            (BST_MEM_HEAD_BLOCK *)ulBlockAdd );
}


/*****************************************************************************
 函 数 名  : BST_OS_StaticMemGetIdleBlockNum
 功能描述  : 获取当前指定类型和大小的内存块剩余数
 输入参数  : enType --需要查询的内存块类型
                           ulSize  --  需要查询的内存块大小
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_INT32 BST_OS_StaticMemGetIdleBlockNum( BST_MEM_TYPE_ENUM_UINT8 enType, BST_UINT32 ulSize)
{
    BST_INT32                           i;
    BST_MEM_BLOCK_INFO                 *pstMemInfo;
    BST_MEM_CTRL_BLOCK                 *pstMemCtrl;
    BST_INT32                           lCycle;
    
    if(BST_MEM_TYPE_DYNAMIC == enType)
    {
        pstMemInfo = g_BstMemBlockInfo;
        lCycle = BST_MEM_CTRL_BLOCK_NUMBER;
        pstMemCtrl = g_BstMemCtrlBlk;
    }
    else if(BST_MEM_TYPE_PBUF == enType)
    {
        pstMemInfo = g_BstBufBlockInfo;
        lCycle = BST_BUF_CTRL_BLOCK_NUMBER;
        pstMemCtrl = g_BstBufCtrlBlk;
    }
    else
    {
        
        BST_RLS_LOG1("# BST_MemGetFreeBlockNum wrong type:%d", enType);
        return 0;      
    }

    for ( i=0; i<lCycle; i++ )
    {
        if(ulSize <= pstMemInfo[i].ulSize )
        {
            return pstMemCtrl[i].lIdleBlockNumber;
        }
    }

    return 0;
}



/*****************************************************************************
 函 数 名  : BST_OS_RegisgerMemStatus
 功能描述  : 提供外部注册指定类型的内存空间状态的回调函数
 输入参数  : enType --需要查询的内存块类型
            pfCallBack  --注册的回调函数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年08月05日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_OS_RegisgerMemStatus( BST_MEM_TYPE_ENUM_UINT8 enType, BST_MEM_STATUS_CALLBACK_FUNC pfCallBack )
{
    BST_UINT32                          ulIndex;

    if( BST_NULL_PTR == pfCallBack )
    {
        return BST_ERR_INVALID_PTR;
    }

    if( enType >= BST_MEM_TYPE_BUTT)
    {
        return BST_ERR_NOT_SUPPORT;
    }

    for(ulIndex=0; ulIndex < BST_MEM_STATUS_CALLBACK_MAX_NUMBER; ulIndex++)
    {
        if( BST_NULL_PTR == g_acBstMemCallBackInfo[enType][ulIndex].pfCallBack )
        {
            g_acBstMemCallBackInfo[enType][ulIndex].pfCallBack        = pfCallBack;
            g_acBstMemCallBackInfo[enType][ulIndex].usLastReportValue = BST_MEM_HIGH_LEVEL;
            return BST_NO_ERROR_MSG;
        }
    }

    BST_DBG_LOG("BST_OS_RegisgerMemStatus client max number");
    return BST_ERR_NOT_SUPPORT;
}

/*****************************************************************************
 函 数 名  : BST_OS_MemStatusReport
 功能描述  : 检查内存状态，是否达到内存不足或者充足的门限
 输入参数  : enType --需要查询的内存块类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年08月05日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_OS_MemStatusReport( BST_MEM_TYPE_ENUM_UINT8 enType )
{
    BST_UINT32                          ulIndex;
    BST_UINT16                          usReportValue;

    /*判断当前的内存块类型最大size块的个数是否达到上限或者下限*/
    if( enType == BST_MEM_TYPE_DYNAMIC )
    {
        if( g_BstMemCtrlBlk[BST_MEM_CTRL_BLOCK_NUMBER-1].lIdleBlockNumber >= BST_MEM_HIGH_LEVEL_THRESHOLD )
        {
            usReportValue                   = BST_MEM_HIGH_LEVEL;
        }
        else if( g_BstMemCtrlBlk[BST_MEM_CTRL_BLOCK_NUMBER-1].lIdleBlockNumber <= BST_MEM_LOW_LEVEL_THRESHOLD )
        {
            usReportValue                   = BST_MEM_LOW_LEVEL;
        }
        else
        {
            return;
        }
    }
    else if( enType == BST_MEM_TYPE_PBUF )
    {
        if( g_BstBufCtrlBlk[BST_BUF_CTRL_BLOCK_NUMBER-1].lIdleBlockNumber >= BST_PBUF_HIGH_LEVEL_THRESHOLD )
        {
            usReportValue                   = BST_MEM_HIGH_LEVEL;
        }
        else if( g_BstBufCtrlBlk[BST_BUF_CTRL_BLOCK_NUMBER-1].lIdleBlockNumber <= BST_PBUF_LOW_LEVEL_THRESHOLD )
        {
            usReportValue                   = BST_MEM_LOW_LEVEL;
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }

    /*判断上次上报的值和本次上报的值，如果不一致，通知各回调函数*/
    for(ulIndex=0; ulIndex < BST_MEM_STATUS_CALLBACK_MAX_NUMBER; ulIndex++)
    {
        if( BST_NULL_PTR != g_acBstMemCallBackInfo[enType][ulIndex].pfCallBack )
        {
            if( usReportValue != g_acBstMemCallBackInfo[enType][ulIndex].usLastReportValue )
            {
                g_acBstMemCallBackInfo[enType][ulIndex].pfCallBack(usReportValue);
                g_acBstMemCallBackInfo[enType][ulIndex].usLastReportValue = usReportValue;
            }
        }
    }
    return ;
}
/*****************************************************************************
 函 数 名  : BST_OS_PalMemInit
 功能描述  : 内存处理初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_OS_MemInit( BST_VOID )
{
    BST_OS_PalMemInit();
    BST_OS_StaticMemInit();
}

/*****************************************************************************
 函 数 名  : BST_OS_Memset
 功能描述  : 写内存
 输入参数  : BST_VOID *pData            地址
             BST_INT32 lValue           值
             BST_OS_MEMSIZE_T ulSize    空间
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -sem(BST_OS_PalMemset,custodial(1))*/
BST_VOID BST_OS_Memset(
    BST_VOID           *pData,
    BST_INT32           lValue,
    BST_OS_MEMSIZE_T    ulSize )
{
    BST_OS_PalMemset( pData, lValue, ulSize );
}

/*****************************************************************************
 函 数 名  : BST_OS_Memcmp
 功能描述  : mem比较
 输入参数  : BST_VOID *pData1         内存1
             BST_VOID *pData2         内存2
             BST_OS_MEMSIZE_T ulSize  空间大小
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_INT8 BST_OS_Memcmp(
    const BST_VOID     *pData1,
    const BST_VOID     *pData2,
    BST_OS_MEMSIZE_T    ulSize )
{
    return( ( BST_INT8 )BST_OS_PalMemcmp( pData1, pData2, ulSize ) );
}

/*****************************************************************************
 函 数 名  : BST_OS_Memcpy
 功能描述  : mem复制
 输入参数  : BST_VOID *pDst           内存1
             BST_VOID *pSrc           内存2
             BST_OS_MEMSIZE_T ulSize  空间大小
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -sem(BST_OS_PalMemcpy,custodial(1))*/
BST_VOID BST_OS_Memcpy(
    BST_VOID           *pDst,
    const BST_VOID     *pSrc,
    BST_OS_MEMSIZE_T    ulSize )
{
    BST_OS_PalMemcpy( pDst, pSrc, ulSize );
}

/*****************************************************************************
 函 数 名  : BST_OS_Memmove
 功能描述  : 内存搬移
 输入参数  : BST_VOID *pDst           目的地址
             BST_VOID *pSrc           源地址
             BST_OS_MEMSIZE_T ulSize  空间大小
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID    BST_OS_Memmove (
    BST_VOID           *pDst,
    BST_VOID           *pSrc,
    BST_OS_MEMSIZE_T    ulSize )
{
    BST_OS_PalMemmove( pDst, pSrc, ulSize );
}

/*****************************************************************************
 函 数 名  : BST_OS_MALLOC
 功能描述  : UT专用申请内存函数
 输入参数  : BST_INT32 ulSize        空间大小
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月26日
      作    者   : w00178404
      修改内容   : 新生成函数
*****************************************************************************/
#if (BST_VER_TYPE == BST_UT_VER )
BST_VOID    *BST_OS_MALLOC( BST_INT32 ulSize )
{
    return( malloc(ulSize) );
}
#endif
