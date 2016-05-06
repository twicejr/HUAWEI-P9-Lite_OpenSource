/******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : TTFMem.h
  Author      : g45205
  Version     : V100R001
  Date        : 2006-11-19
  Description : 该头文件定义了TTF组提供的内存管理
  History     :
  1. Date:2006-11-19
     Author: g45205
     Modification:Create
******************************************************************************/
#ifndef __TTF_MEM_H_
#define __TTF_MEM_H_

/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "TtfMemoryMap.h"
#include "TTFLink.h"
#include "TTFMemInterface.h"
#include "TtfNvInterface.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/******************************************************************************
  2 宏定义
******************************************************************************/
#define TTF_NODE_MEM_DBG                FEATURE_ON

/* TTF常用操作宏定义 */
#define TTF_MEM_GET_HDR_RSV_LEN(pMem)           (VOS_UINT16)((pMem)->pData - (pMem)->pOrigData)

#define TTF_MEM_INIT(pMem, usMemType, usMemLen) \
{                                               \
    TTF_NodeInit(&pMem->stNode);                \
    (pMem)->pNext   = VOS_NULL_PTR;             \
    (pMem)->usType  = (usMemType);              \
    (pMem)->usLen   = (usMemLen);               \
    (pMem)->usUsed  = 0;                        \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
#define TTF_MEM_STATE_INIT(pMem) \
    (pMem)->enMemStateFlag  = TTF_BLK_MEM_STATE_FREE;
#endif

#define TTF_MEM_SET(pMem, usMemType, usMemLen) \
{                                               \
    TTF_NodeInit(&pMem->stNode);                \
    (pMem)->pNext   = VOS_NULL_PTR;             \
    (pMem)->usType  = (usMemType);              \
    (pMem)->usLen   = (usMemLen);               \
    (pMem)->usUsed  = (usMemLen);               \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

#define TTF_MEM_RESET(pMem)                     \
{                                               \
    TTF_LINK_INIT_NODE(&pMem->stNode);          \
    (pMem)->pNext   = VOS_NULL_PTR;             \
    (pMem)->usLen  += TTF_MEM_GET_HDR_RSV_LEN((pMem)); \
    (pMem)->usUsed  = 0;                        \
    (pMem)->pData   = (pMem)->pOrigData;        \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

#define TTF_MEM_CLEAN(pMem)                     \
{                                               \
    TTF_LINK_INIT_NODE(&pMem->stNode);          \
    (pMem)->pNext       = VOS_NULL_PTR;         \
    (pMem)->usLen       = 0;                    \
    (pMem)->usUsed      = 0;                    \
    (pMem)->pOrigData   = VOS_NULL_PTR;         \
    (pMem)->pData       = (pMem)->pOrigData;    \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

/*总长度是指从指针头部到最后的数据?
 */
#define TTF_MEM_REMOVE_FROM_HDR(pMem, usNum)    \
{                                               \
    (pMem)->pData  += (usNum);                  \
    (pMem)->usLen  -= (usNum);                  \
    (pMem)->usUsed -= (usNum);                  \
}

#define TTF_MEM_RESUME_TO_HDR(pMem, usNum)      \
{                                               \
    (pMem)->pData  -= (usNum);                  \
    (pMem)->usLen  += (usNum);                  \
    (pMem)->usUsed += (usNum);                  \
}

#define TTF_MEM_NEXT(pMem)                      ((pMem)->pNext)

#define TTF_MEM_SIZE                            sizeof(TTF_MEM_ST)


#if (FEATURE_ON == FEATURE_DC_MIMO)
#define TTF_BLK_MEM_ALERT_THLD                  (1)
#else
#define TTF_BLK_MEM_ALERT_THLD                  (300)
#endif


#define TTF_MALLOC_STATIC_WITH_FILE_LINE(ulPid,size,ulFileID, ulLine)    \
    V_MemAlloc(ulPid, STATIC_MEM_PT, (size), VOS_TRUE, ulFileID, ulLine)
#define TTF_MALLOC_WITH_FILE_LINE(ulPid,size,ulFileID, ulLine)    \
    V_MemAlloc(ulPid, DYNAMIC_MEM_PT, (size), VOS_TRUE, ulFileID, ulLine)


#define TTF_GET_LEN_INDEX(pstTtfMemPoolInfo, usLen) \
    ((pstTtfMemPoolInfo)->aucLenIndexTable[(usLen)])

#define TTF_MEM_NET_PAD                     (64)
#define TTF_MEM_WIFI_PAD                    (256)
#define TTF_MEM_MAC_HEAD_LEN                (14)

/* 预留给Linux skbuff的share空间，=sizeof(struct skb_shared_info)
Linux版本发生改变时需要重新check该值 */
#define TTF_MEM_SKBUFF_SHARE_INFO_SIZE      (264)

/* G模19块静态内存 */
#ifdef __UT_CENTER__
#define TTF_NODE_MEM_G_STATIC_CNT           (0)
#else
#define TTF_NODE_MEM_G_STATIC_CNT           (19)
#endif

/* 增加DSDS特性RRM模块节点内存 */
#define RRM_NODE_MEM_CNT                    (100)

#define TTF_NODE_MEM_POOL_SIZE              (52)
#define TTF_NODE_MEM_W_CNT                  (4352)
#if (FEATURE_OFF == FEATURE_MULTI_MODEM)
#define TTF_NODE_MEM_POOL_CNT               (TTF_NODE_MEM_G_STATIC_CNT + TTF_NODE_MEM_W_CNT)
#else
#define TTF_NODE_MEM_DSDA_G_STATIC_CNT      (1202)
/* 双发下，增加一个G模。以Class 33计算：下行RLC窗口最大640，上行RLC窗口512，
  保存SDU节点需要512*74*2/1500=50块，故增加640+512+50=1202块（占用内存约60KB）。*/
#define TTF_NODE_MEM_POOL_CNT               (TTF_NODE_MEM_G_STATIC_CNT + TTF_NODE_MEM_W_CNT + TTF_NODE_MEM_DSDA_G_STATIC_CNT)
#endif

#define TTF_NODE_MEM_POOL_BASE_ADDR         (g_stNodeMemSpace)

#define RRM_NODE_MEM_POOL_BASE_ADDR         (g_astRrmNodeMemSpace)

/* C-CPU内存池掩码，对应位设置 */
#define TTF_MEM_MASK_POOL(ucPoolId)         (((VOS_UINT32)1) << (ucPoolId))

/* C-CPU上行IP包数据内存池需要给ADQ预留内存，数量取决于IPF_ULAD0_DESC_SIZE + IPF_ULAD1_DESC_SIZE */
#define TTF_MEM_UL_IP_DATA_POOL_RSV_CNT     (IPF_ULAD0_DESC_SIZE + IPF_ULAD1_DESC_SIZE)

/* 内存申请失败复位打印个数 */
#define TTF_MEM_DEBUG_NUM                   (60)


#define TTF_MEM_RCOV_THRES                  (0x1F)
#define TTF_MEM_RCOV_TIMER_LEN              (10 * 60 * 1000 * 33)   /* 默认10分钟, 单位slice */

#define TTF_MEM_RCOV_DEF_POOL_MSK           (TTF_MEM_MASK_POOL(TTF_MEM_POOL_ID_DL_SHARE) | TTF_MEM_MASK_POOL(TTF_MEM_POOL_ID_DL_PDU))

#define TTF_MEM_RST_RCOV_ENT()              PS_MEM_SET(&g_stTtfMemRcovEnt, 0, sizeof(TTF_MEM_RCOV_ENTITY_STRU))

#define TTF_MEM_SET_RCOV_ENT_POOL_MSK(poolMsk) \
    (g_stTtfMemRcovEnt.ucRcovPoolMsk = (poolMsk))

#define TTF_MEM_CHK_NEED_RCOV_POOL(poolMsk) \
    (poolMsk == (poolMsk & g_stTtfMemRcovEnt.ucRcovPoolMsk))


#define TTF_MEM_SET_RCOV_ENT_THRES(ulPoolId, ulThres) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovThres = (ulThres))

#define TTF_MEM_GET_RCOV_ENT_THRES(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovThres)

#define TTF_MEM_SET_RCOV_ENT_TIMER_LEN(ulPoolId, ulTmLen) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovTimerLen = (ulTmLen))

#define TTF_MEM_GET_RCOV_ENT_TIMER_LEN(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovTimerLen)

#define TTF_MEM_SET_RCOV_ENT_STATE(ulPoolId, state) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulState = (state))

#define TTF_MEM_GET_RCOV_ENT_STATE(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulState)

#define TTF_MEM_SET_RCOV_ENT_TIMESTAMP(ulPoolId, ulTs) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulEnterRcovTs = (ulTs))

#define TTF_MEM_GET_RCOV_ENT_TIMESTAMP(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulEnterRcovTs)

#define TTF_MEM_SET_RCOV_ENT_FAIL_CNT(ulPoolId, ulFailCnt) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulAllocFailCnt = (ulFailCnt))

#define TTF_MEM_RCOV_ENTER_WAIT_RCOV_STATE(ulPoolId) \
{ \
    TTF_MEM_SET_RCOV_ENT_TIMESTAMP(ulPoolId, mdrv_timer_get_normal_timestamp()); \
    TTF_MEM_SET_RCOV_ENT_STATE(ulPoolId, TTF_MEM_STATE_WAIT_RCOV); \
}

#define TTF_MEM_RCOV_EXIT_WAIT_RCOV_STATE(ulPoolId) \
{ \
    TTF_MEM_SET_RCOV_ENT_STATE(ulPoolId, TTF_MEM_STATE_NORMAL); \
    TTF_MEM_SET_RCOV_ENT_TIMESTAMP(ulPoolId, 0); \
}


#define TTF_MEM_RCOV_TIMER_EXPIRED(a, b) \
    (((VOS_INT32)a - (VOS_INT32)b) >= 0)


#define TTF_MEM_RCOV_ALLOC_SUCC(ulPoolId) \
{ \
    if (TTF_MEM_STATE_NORMAL != g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulState) \
    {\
        TTF_MEM_RCOV_EXIT_WAIT_RCOV_STATE(ulPoolId);\
    }\
}

#define TTF_MEM_RCOV_ALLOC_FAIL(ulPoolId, ulFailCnt, ulPid, usFileId, usLine) \
    TTF_MemRcovAllocFail(ulPoolId, ulFailCnt, ulPid, usFileId, usLine)


enum TTF_MEM_RCOV_STATE_ENUM
{
    TTF_MEM_STATE_NORMAL = 0,
    TTF_MEM_STATE_ALLOC_FAIL,
    TTF_MEM_STATE_WAIT_RCOV,
    TTF_MEM_STATE_BUTT
};

typedef struct
{
    VOS_UINT32  ulState;
    VOS_UINT32  ulRcovThres;
    VOS_UINT32  ulRcovTimerLen;
    VOS_UINT32  ulEnterRcovTs;                  /* 进入等待恢复状态的时戳 */
}TTF_MEM_RCOV_POOL_INFO_STRU;

typedef struct
{
    VOS_UINT8     ucRcovPoolMsk;             /* 需要保护的内存池掩码 */
    VOS_UINT8     aucRsv[3];
    TTF_MEM_RCOV_POOL_INFO_STRU astPoolInfo[TTF_MEM_POOL_ID_BUTT];
}TTF_MEM_RCOV_ENTITY_STRU;


/******************************************************************************
  3 枚举定义
******************************************************************************/


/******************************************************************************
  4 全局变量声明
******************************************************************************/

/******************************************************************************
  5 消息头定义
******************************************************************************/


/******************************************************************************
  6 消息定义
******************************************************************************/


/******************************************************************************
  7 STRUCT定义
******************************************************************************/
#pragma pack(4)


/*====================================*/        /* TTF内存管理定义 */
enum TTF_MEM_TYPE_ENUM
{
    TTF_MEM_TYPE_MIN    = 0,
    TTF_MEM_TYPE_DYN    = 0,                /* 动态数据内存 */
    TTF_MEM_TYPE_BLK,                       /* 专用内存的数据块 */
    TTF_MEM_TYPE_EXT,                       /* 外部内存的数据块 */

    TTF_MEM_TYPE_BUTT
};
typedef VOS_UINT16 TTF_MEM_TYPE_ENUM_UINT16;

#define EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG         (1000)
/*****************************************************************************
 枚举名    : TTF_OM_EVENT_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 事件上报ID
*****************************************************************************/
enum TTF_OM_EVENT_ID_ENUM
{
    TTF_EVENT_BLK_MEM_USED_INFO             = 0X0101,   /* _H2ASN_MsgChoice TTF_OM_EVENT_BLK_MEM_USED_INFO_STRU */
    TTF_EVENT_BUTT
};
typedef VOS_UINT16 TTF_OM_EVENT_ID_ENUM_UINT16;

/*****************************************************************************
 结构名    : TTF_MEM_LEAK_INFO_IND_STRU
 结构说明  : 上报内存泄露消息结构,
 1.日    期   : 2011年12月19日
   作    者   : C00173809
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT16                              usMsgName;      /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                               aucRsv[2];
} TTF_MEM_LEAK_INFO_IND_MSG;


enum BLK_MEM_USED_INFO_TRIG_TYPE_ENUM
{
    TRIG_TYPE_ALERT                      = 0x0,
    TRIG_TYPE_ALLOC_FAIL,
    TRIG_TYPE_LEAK,
    TRIG_TYPE_NORMAL,
    TRIG_TYPE_BUTT
};
typedef VOS_INT8 BLK_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : TTF_OM_EVENT_USED_BLK_MEM_INFO_STRU
 协议表格  :
 ASN.1描述 :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulAllocTick;        /* CPU tick when alloc or free */
    VOS_UINT16                                  usAllocFileId;      /* File ID when alloc or free */
    VOS_UINT16                                  usAllocLineNum;     /* File Line when alloc or free */
    VOS_UINT32                                  ulTraceTick;        /* CPU tick when traced */
    VOS_UINT16                                  usTraceFileId;      /* File ID when traced */
    VOS_UINT16                                  usTraceLineNum;     /* File Line when traced */
    VOS_UINT8                                   aucMemData[4];
}BLK_MEM_TRACE_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usEventId;
    VOS_UINT16                                  usReserved;
    VOS_UINT32                                  ulModuleId;

    VOS_UINT8                                   ucPoolId;
    VOS_UINT8                                   ucRes[3];
    BLK_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8      enTrigType;
    VOS_UINT8                                   ucNo;
    VOS_UINT16                                  usRptCnt;
    VOS_UINT32                                  ulTotalUsedCnt;
    BLK_MEM_TRACE_INFO_STRU                     astBlkMemTraceInfo[1];
}TTF_OM_EVENT_BLK_MEM_USED_INFO_STRU;

typedef struct
{
    VOS_UINT32                                  ulAllocTick;        /* CPU tick when alloc */
    VOS_UINT16                                  usAllocFileId;      /* File ID when alloc */
    VOS_UINT16                                  usAllocLineNum;     /* File Line when alloc */
    VOS_UINT32                                  ulTraceTick;        /* CPU tick when traced */
    VOS_UINT16                                  usTraceFileId;      /* File ID when traced */
    VOS_UINT16                                  usTraceLineNum;     /* File Line when traced */
}TTF_BLK_MEM_DEBUG_INFO_STRU;

/*****************************************************************************
 结构名    : TTF_MEM_CLUSTER_STRU
 协议表格  :
 ASN.1描述 :
*****************************************************************************/
typedef struct
{
    /*本级数的TTF_MEM_ST字节个数*/
    VOS_UINT16                          usTotalCnt;
    VOS_UINT16                          usFreeCnt;

    /*本级内存的内容长度*/
    VOS_UINT16                          usLen;

    VOS_UINT8                           aucRsv[2];

    /*记录TTF_MEM_ST可用内存索引表的栈顶元素，其内容为TTF_MEM_ST指针 */
    TTF_MEM_ST                        **apstFreeStack;
}TTF_MEM_CLUSTER_STRU;

/*****************************************************************************
 结构名    : TTF_MEM_POOL_STRU
 协议表格  :
 ASN.1描述 :
*****************************************************************************/
typedef VOS_VOID (*TTF_MEM_EVENT_CALLBACK)(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize);
typedef VOS_VOID (*TTF_MEM_EXT_FREE_CALLBACK)(VOS_VOID *pucAddr);

typedef struct
{
    /* 标识本内存池是否使用 */
    VOS_UINT16                          usUsedFlag;

    /* 本内存池中使用的最大用户字节 */
    VOS_UINT16                          usMaxByteLen;

    /* 指向长度索引表的指针 */
    VOS_UINT8                           aucLenIndexTable[TTF_MEM_BLK_MAX_BYTE_LEN];

    /* 本内存池一共有多少级*/
    VOS_UINT8                           ucClusterCnt;

    VOS_UINT8                           aucsv2[3];

    /* 指向级数索引表的指针 */
    TTF_MEM_CLUSTER_STRU                astClusterTable[TTF_MEM_MAX_CLUSTER_NUM];


    VOS_UINT16                          usTtfMemTotalCnt;       /* 本内存池一共有多少TTF_MEM_ST */
    VOS_UINT16                          usTtfMemUsedCnt;        /* 使用了多少TTF_MEM_ST */
    VOS_UINT32                          ulTtfMemTotalByteSize;  /* 一共有多少字节 */
    VOS_UINT32                          ulTtfMemUsedByteSize;   /* 已使用内存总大小，以字节为单位 */

    VOS_UINT16                          usTtfMemExcThresholdCnt;   /* 申请内存失败超过门限次数 */
    VOS_UINT16                          usTtfMemAllocFailCnt;      /* 最后一次过门限申请内存失败次数 */
    VOS_UINT16                          usTtfMemConAllocFailCnt;   /* 连续申请内存失败次数，用于复位 */
    VOS_UINT8                           aucRsv[2];

    TTF_MEM_ST                        **ppstTtfMem;
    TTF_MEM_ST                         *pstTtfMemStStartAddr;   /* 指向TtfMemST首地址的指针 */
#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
    TTF_BLK_MEM_DEBUG_ST               *pstMemDbInfo;
#endif

    TTF_MEM_EVENT_CALLBACK              pMemAllocEvent;
    TTF_MEM_EVENT_CALLBACK              pMemFreeEvent;
    TTF_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc;        /* 指向外部注册的释放函数*/
}TTF_MEM_POOL_STRU;

/* TTF MEM每级的配置信息*/
typedef struct
{
    VOS_UINT16                          usSize;    /* 本级数的大小 */
    VOS_UINT16                          usCnt;     /* 本级个数 */
}TTF_MEM_CLUSTER_CFG_INFO_STRU;

/* TTF MEM每个内存池的级的信息*/
typedef struct
{
    /* 本池 ID */
    VOS_UINT8                           ucPoolID;

    /* 本内存池有多少级 */
    VOS_UINT8                           ucClusterCnt;

    VOS_UINT8                           aucResv[2];

    /* 每级的具体信息 */
    TTF_MEM_CLUSTER_CFG_INFO_STRU      *pstClusterCfgInfo;
}TTF_MEM_POOL_CFG_INFO_STRU;



/* 流控使用参数 */
typedef struct TTF_MEM_FLOW_CTRL_INFO
{
    VOS_UINT16                          usUsedMemCnt;
    VOS_UINT16                          usRsv;
    VOS_UINT32                          ulTotalUsedByteCnt;
}TTF_MEM_FLOW_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : TTF_INVALID_MEM_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 结构说明  : TTF MEM内存非法类型

1.日    期 : 2011年11月28日
  作    者 : s00164817
  修改内容 : 新建
*****************************************************************************/
enum TTF_INVALID_MEM_TYPE_ENUM
{
    TTF_INVALID_MEM_TYPE_BLKTYPE = 1,               /* 内存类型 */
    TTF_INVALID_MEM_TYPE_POOLID,                    /* 内存池ID非法  */
    TTF_INVALID_MEM_TYPE_CTRLADDR,                  /* 内存地址非法 */
    TTF_INVALID_MEM_TYPE_STUTAS,                    /* 内存状态错误 */

    TTF_INVALID_MEM_TYPE_BUTT
};
typedef unsigned char TTF_INVALID_MEM_TYPE_ENUM_UINT8;

#if(TTF_NODE_MEM_DBG == FEATURE_ON)
enum TTF_NODE_MEM_STATE_ENUM
{
    TTF_NODE_MEM_USED = 0,
    TTF_NODE_MEM_IDLE,
    TTF_NODE_MEM_BUTT
};

typedef VOS_UINT8 TTF_NODE_MEM_STATE_ENUM_UINT8;
#endif

enum TTF_NODE_MEM_POOL_STATE_ENUM
{
    TTF_NODE_MEM_POOL_STATE_IDLE = 0,
    TTF_NODE_MEM_POOL_STATE_ACTIVE,
    TTF_NODE_MEM_POOL_STATE_BUTT
};

typedef VOS_UINT8 TTF_NODE_MEM_POOL_STATE_ENUM_UINT8;

enum TTF_NODE_MEM_TYPE_ENUM
{
    TTF_NODE_MEM_TYPE_NORMAL    = 0,
    TTF_NODE_MEM_TYPE_RRM       = 1,
    TTF_NODE_MEM_TYPE_BUTT
};

typedef VOS_UINT8 TTF_NODE_MEM_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名    : TTF_MEM_FREE_NULL_PTR_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TTF MEM FREE收到空指针信息
*****************************************************************************/
typedef struct TTF_MEM_FREE_NULL_PTR_INFO
{
    VOS_UINT32          ulTtfMemFreeNullPtrCnt;     /* TtfMemFree 收到空指针次数 */
    VOS_UINT16          usTtfMemFreeFileId;         /* TtfMemFree 收到空指针次数文件ID，仅保存最后一次收到空指针文件ID信息 */
    VOS_UINT16          usTtfMemFreeLineNum;        /* TtfMemFree 收到空指针次数文件ID，仅保存最后一次收到空指针行号信息 */
}TTF_MEM_FREE_NULL_PTR_INFO_STRU;

/*****************************************************************************
 结构名    : TTF_MEM_FREE_INVALIED_MEM_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TTF MEM FREE 收到的非法TTF MEM 内存信息
*****************************************************************************/
typedef struct TTF_MEM_FREE_INVALIED_MEM_INFO
{
    VOS_UINT32                          ulInvalidTtfMemCnt;         /* TTF MEM FREE 收到的非法内存个数 */
    VOS_UINT32                          ulInvalidTtfMemAddr;        /* TTF MEM FREE 最后一次收到的非法TTF MEM 内存地址 */
    VOS_UINT16                          usTtfMemFreeFileId;         /* TTF MEM FREE 最后一次收到的非法TTF MEM 内存文件ID信息 */
    VOS_UINT16                          usTtfMemFreeLineNum;        /* TTF MEM FREE 最后一次收到的非法TTF MEM 内存行号信息 */
    TTF_INVALID_MEM_TYPE_ENUM_UINT8     ucInvalidTtfMemType;        /* TTF MEM FREE 最后一次收到的非法TTF MEM 内存 */
    VOS_UINT8                           aucResve[1];                /* 四字节对齐 */
    VOS_UINT16                          usInvalidTtfMemValue;       /* 非法内存值 */
}TTF_MEM_FREE_INVALIED_MEM_INFO_STRU;


/*****************************************************************************
 结构名    : TTF_MEM_FREE_MNTN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存TTF 内存释放可维可测信息
*****************************************************************************/
typedef struct TTF_MEM_FREE_MNTN_INFO
{
    TTF_MEM_FREE_INVALIED_MEM_INFO_STRU astTtfMemFreeInvalidMemInfo;    /* TTF MEM FREE 收到的非法TTF MEM 内存信息 */
    TTF_MEM_FREE_NULL_PTR_INFO_STRU     astTtfMemFreeNullPtrInfo;       /* TTF MEM FREE 收到一级指针为空的信息 */
    TTF_MEM_FREE_NULL_PTR_INFO_STRU     astTtfMemFreeNullPPtrInfo;      /* TTF MEM FREE 收到二级指针为空的信息 */
    VOS_UINT32                          ulTtfMemExtFreeFailCnt;         /* TTF MEM 释放外部内存失败次数 */
}TTF_MEM_FREE_MNTN_INFO_STRU;

typedef struct
{
#if(TTF_NODE_MEM_DBG == FEATURE_ON)
    VOS_UINT16  usPid;
    VOS_UINT16  usFileId;
    VOS_UINT16  usLineNo;
    VOS_UINT8   ucState;
    VOS_UINT8   ucRsv;
#endif
    VOS_UINT8   aucData[TTF_NODE_MEM_POOL_SIZE];
}TTF_NODE_MEM_NODE_STRU;

typedef struct
{
    VOS_UINT8                               ucState;
    VOS_UINT8                               aucRsv[3];
    volatile VOS_UINT16                     usFreeCnt;
    VOS_UINT16                              usTotalCnt;
    VOS_UINT32                              ulTotalSize;
    VOS_VOID                               *pBaseAddr;
    volatile TTF_NODE_MEM_NODE_STRU       **pFreeNode;
}TTF_NODE_MEM_POOL_STRU;

typedef struct
{
    PS_BOOL_ENUM_UINT8                      enStartStat;    /* 是否开始统计 */
    VOS_UINT8                               aucReserved[3];
    VOS_UINT16                              usFailCnt;      /* 节点申请失败统计值 */
    VOS_UINT16                              usTotalStatCnt; /* 节点申请总个数  */
}TTF_NODE_RESET_STATISTIC_INFO_STRU;

typedef struct
{
    VOS_UINT32                              ulPid;          /* 节点申请使用的Pid值 */
    VOS_UINT32                              ulCnt;          /* 该Pid值总共申请的节点总个数 */
}TTF_NODE_USED_PID_INFO_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION定义
******************************************************************************/


/******************************************************************************
  9 OTHERS定义
******************************************************************************/
extern TTF_MEM_POOL_STRU    g_astTtfMemPool[TTF_MEM_POOL_ID_BUTT];
#define TTF_MEM_BLK_IS_ALERT(ulPoolId)    \
                ((g_astTtfMemPool[ulPoolId].usTtfMemTotalCnt - g_astTtfMemPool[ulPoolId].usTtfMemUsedCnt) < TTF_BLK_MEM_ALERT_THLD)

extern VOS_UINT32  TTF_MemBlkIsAlert(VOS_UINT32 ulPoolId);
extern VOS_UINT32  TTF_MemBlkInit(VOS_UINT32 ulPid);
extern VOS_UINT32  TTF_MemGet(VOS_UINT32 ulPid, TTF_MEM_ST *pMemSrc, VOS_UINT16 usOffset,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemBlkGetHeadData( VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, TTF_MEM_ST *pMemSrc,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemGetHeadData( VOS_UINT32 ulPid, TTF_MEM_ST *pMemSrc,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemGetTailData( VOS_UINT32 ulPid, TTF_MEM_ST *pMemSrc,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemLink(VOS_UINT32 ulPid, TTF_MEM_ST **ppMemHead, TTF_MEM_ST *pMemTail);
extern VOS_UINT32  TTF_MemSet(VOS_UINT32 ulPid, TTF_MEM_ST *pMemDest, VOS_UINT16 usOffset,
           VOS_UINT8 *pSrc, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemStick(VOS_UINT32 ulPid, TTF_MEM_ST *pMemHead, TTF_MEM_ST *pMemTail);
extern VOS_UINT32  TTF_MemIsCritical(VOS_VOID);
extern VOS_UINT32 TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_ENUM_UINT32 enPoolId,
            TTF_MEM_EVENT_CALLBACK pMemAllocEvent, TTF_MEM_EVENT_CALLBACK  pMemFreeEvent);
extern TTF_MEM_ST *TTF_MemSingleFree_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST *pMem);
extern TTF_MEM_ST *TTF_MemBlkCopyAllocFromMem_Debug
(
    VOS_UINT16      usFileID,
    VOS_UINT16      usLineNum,
    VOS_UINT32      ulPid,
    VOS_UINT32      ulPoolId,
    TTF_MEM_ST     *pMemSrc,
    VOS_UINT16      usOffset,
    VOS_UINT16      usLen
);

extern VOS_UINT32 TTF_MemBlkCutHeadData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST **ppMemSrc,
    VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT16 TTF_MemBlkCutTailData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST **ppMemSrc,
    VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32 TTF_MemBlkAddHeadData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId,
    TTF_MEM_ST * * ppMemDest, VOS_UINT8 * pSrcData, VOS_UINT16 usAddLen);
extern VOS_UINT32 TTF_MemBlkAddTailData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId,
    TTF_MEM_ST * * ppMemDest, VOS_UINT8 * pSrcData, VOS_UINT16 usAddLen);
extern TTF_MEM_ST *TTF_MemBlkRef_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolID,
    TTF_MEM_ST *pMemRef, VOS_UINT16  usOffset, VOS_UINT16  usLen);
extern TTF_MEM_ST *TTF_MemBlkAllocWithUsed_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT16 usLen);
extern VOS_UINT16 TTF_MemBlkCutTailDataWithLastMem_Debug
(
    VOS_UINT16 usFileID,VOS_UINT16 usLineNum, VOS_UINT32 ulPid,
    TTF_MEM_ST **ppMemSrc, TTF_MEM_ST **ppLastMem, VOS_UINT8 *pDest,
    VOS_UINT16 usLen
);
extern VOS_UINT32 TTF_MemBlkAddTailDataWithLastMem_Debug
(
    VOS_UINT16 usFileID,VOS_UINT16 usLineNum, VOS_UINT32 ulPid,
    VOS_UINT32 ulPoodId,TTF_MEM_ST **ppMemDest, TTF_MEM_ST *pLastMem,
    VOS_UINT8  *pSrcData, VOS_UINT16  usAddLen
);

extern TTF_MEM_ST *TTF_MemBlkAllocPlus_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,
    VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT16 usLen);

extern TTF_MEM_ST *TTF_MemBlkCopyAlloc_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,
    VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT8 *pData, VOS_UINT16 usLen);

extern TTF_MEM_ST *TTF_MemBlkCopyAllocPacket_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,
    VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT8 *pData, VOS_UINT16 usLen);

extern TTF_MEM_ST *TTF_MemBlkSingleFree_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, TTF_MEM_ST *pstTtfMem);

extern VOS_VOID TTF_MemFreeData(VOS_UINT32 ulPid, TTF_MEM_ST *pItem);

extern VOS_UINT16 TTF_MemGetLen(VOS_UINT32 ulPid, TTF_MEM_ST *pMem);

extern VOS_UINT32 TTF_MemRegExtFreeCallBack
                    (
                        TTF_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc
                    );

extern VOS_VOID TTF_MemFreeShowMntnInfo( VOS_VOID );

extern VOS_UINT_PTR TTF_GetHdlcMemSection(VOS_VOID);

extern VOS_UINT_PTR TTF_GetCipherMemSection(VOS_VOID);

extern VOS_VOID TTF_NodeMemPoolInit(VOS_VOID);
extern VOS_UINT8 *TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_ENUM_UINT8 enTtfNodeMemType,VOS_UINT32  ulPid, VOS_UINT16  usLen, VOS_UINT16  usFileId, VOS_UINT16  usLineNo);
extern VOS_VOID   TTF_NodeMemFree_Debug(TTF_NODE_MEM_TYPE_ENUM_UINT8 enTtfNodeMemType, VOS_UINT32 ulPid, VOS_UINT8 * pMem, VOS_UINT16 usFileId, VOS_UINT16 usLineNo);
extern VOS_UINT32 TTF_NodeMemLeakCheck(VOS_VOID);

extern VOS_UINT32 TTF_MemInsertNext(VOS_UINT32 ulPid, TTF_MEM_ST *pMemCurr, TTF_MEM_ST *pMemNext);

extern TTF_MEM_FREE_MNTN_INFO_STRU             g_stTtfMemFreeMntnEntity;

#define TTF_MemBlkAllocPlus(ulPid, ulPoolId, usLen) \
    TTF_MemBlkAllocPlus_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, usLen)


#define TTF_MemSingleFree(ulPid, pMem) \
    TTF_MemSingleFree_Debug(THIS_FILE_ID, __LINE__, ulPid, pMem)

#define TTF_MemBlkCopyAlloc(ulPid, ulPoolId, pData,usLen) \
    TTF_MemBlkCopyAlloc_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pData, usLen)

#define TTF_MemBlkCopyAllocPacket(ulPid, ulPoolId, pData,usLen) \
    TTF_MemBlkCopyAllocPacket_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pData, usLen)

#define TTF_MemBlkCopyAllocFromMem(ulPid, ulPoolId, pMemSrc, usOffset, usLen) \
    TTF_MemBlkCopyAllocFromMem_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pMemSrc, usOffset, usLen)

#define TTF_MemBlkCutHeadData(ulPid, ppMemSrc, pDest, usLen) \
    TTF_MemBlkCutHeadData_Debug(THIS_FILE_ID, __LINE__, ulPid, ppMemSrc, pDest, usLen)

#define TTF_MemBlkCutTailData(ulPid, ppMemSrc, pDest, usLen) \
    TTF_MemBlkCutTailData_Debug(THIS_FILE_ID, __LINE__, ulPid, ppMemSrc, pDest, usLen)

#define TTF_MemBlkCutTailDataWithLastMem(ulPid, ppMemSrc, ppLastMem, pDest, usLen) \
    TTF_MemBlkCutTailDataWithLastMem_Debug(THIS_FILE_ID, __LINE__, ulPid, ppMemSrc, ppLastMem, pDest, usLen)

#define TTF_MemBlkAddHeadData(ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen) \
    TTF_MemBlkAddHeadData_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen)

#define TTF_MemBlkAddTailData(ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen) \
    TTF_MemBlkAddTailData_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen)

#define TTF_MemBLkAddTailDataWithLastMem(ulPid, ulPoolId, ppMemDest, pLastMem, pSrcData, usAddLen)\
    TTF_MemBlkAddTailDataWithLastMem_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, ppMemDest, pLastMem, pSrcData, usAddLen)

#define TTF_MemBlkRef(ulPid, ulPoolId, pMemRef, usOffset, usLen) \
    TTF_MemBlkRef_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pMemRef, usOffset, usLen)

#define TTF_MemBlkAllocWithUsed(ulPid, ulPoolId, usLen) \
    TTF_MemBlkAllocWithUsed_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, usLen)


#define TTF_NODE_MEM_ALLOC(ulPid, size)     \
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_NORMAL, ulPid, size, THIS_FILE_ID, __LINE__)

#define TTF_NODE_MEM_FREE(ulPid, pMem)     \
    TTF_NodeMemFree_Debug(TTF_NODE_MEM_TYPE_NORMAL, ulPid, (VOS_UINT8 *)pMem, THIS_FILE_ID, __LINE__)

#define TTF_NODE_MEM_ALLOC_WITH_FILE_LINE(ulPid, size, ulFileID, ulLine)\
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_NORMAL, ulPid, size, ulFileID, ulLine)

/* RRM模块NODE内存申请 */
#define RRM_NODE_MEM_ALLOC(ulPid, size)     \
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_RRM, ulPid, size, THIS_FILE_ID, __LINE__)

/* RRM模块NODE内存释放 */
#define RRM_NODE_MEM_FREE(ulPid, pMem)     \
    TTF_NodeMemFree_Debug(TTF_NODE_MEM_TYPE_RRM, ulPid, (VOS_UINT8 *)pMem, THIS_FILE_ID, __LINE__)

/* RRM模块NODE内存申请 */
#define RRM_NODE_MEM_ALLOC_WITH_FILE_LINE(ulPid, size, ulFileID, ulLine)\
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_RRM, ulPid, size, ulFileID, ulLine)

#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
#define TTF_MEM_DBG(pMem, usFileID, usLineNum) \
{ \
    if (TTF_BLK_MEM_DEBUG_SWITCH_ON) \
    { \
        if (VOS_NULL_PTR != pMem->pstDbgInfo) \
        { \
            pMem->pstDbgInfo->enMemStateFlag    = TTF_BLK_MEM_STATE_ALLOC; \
            pMem->pstDbgInfo->usAllocFileId     = usFileID; \
            pMem->pstDbgInfo->usAllocLineNum    = usLineNum; \
            pMem->pstDbgInfo->ulAllocTick       = mdrv_timer_get_normal_timestamp(); \
            pMem->pstDbgInfo->usTraceFileId     = usFileID; \
            pMem->pstDbgInfo->usTraceLineNum    = usLineNum; \
        } \
        else \
        { \
            TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_ERROR, "Blk Mem debug info is null! \n"); \
        } \
    }\
}

#define TTF_BLK_MEM_DEBUG_SWITCH_ON \
    (1 == g_ulTtfBlkMemCheck)

#define TTF_MEM_TRACE(pMem) \
    TTF_MemSetBlkFlag(pMem, THIS_FILE_ID, __LINE__)

#define TTF_MEM_RCOV_MEM(ulPoolId, ulPid, usFileId, usLine) \
    TTF_MemRcovMem(ulPoolId, ulPid, usFileId, usLine)

extern VOS_UINT32   g_ulTtfBlkMemCheck;
extern VOS_VOID     TTF_ShowUsedBlkMemInfo(VOS_VOID);
extern VOS_VOID     TTF_MemSetBlkFlag(TTF_MEM_ST *pstMem, VOS_UINT16 usFileID, VOS_UINT16 usLineNum);

#else

#define TTF_MEM_TRACE(pMem)
#define TTF_MEM_DBG(pMem, usFileID, usLineNum)
#define TTF_MEM_RCOV_MEM(ulPoolId, ulPid, usFileId, usLine) \
     mdrv_om_system_error(TTF_MEM_ALLOC_FAIL_SYSTEM_ERROR, usFileId, usLine, VOS_NULL_PTR, 0)

#endif


#if (FEATURE_PTM == FEATURE_ON)

#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
#define TTF_ERR_LOG_RCD_DBG(pstMemAllocInfo, pstMem, usMemRptCnt) \
{ \
    if ((VOS_NULL_PTR != pstMem->pstDbgInfo) && (TTF_BLK_MEM_STATE_FREE != pstMem->pstDbgInfo->enMemStateFlag)) \
    { \
        pstMemAllocInfo->usAllocFileId  = pstMem->pstDbgInfo->usAllocFileId; \
        pstMemAllocInfo->usAllocLine    = pstMem->pstDbgInfo->usAllocLineNum; \
        pstMemAllocInfo->usTraceFileId  = pstMem->pstDbgInfo->usTraceFileId; \
        pstMemAllocInfo->usTraceLine    = pstMem->pstDbgInfo->usTraceLineNum; \
        usMemRptCnt++;\
    } \
}
#else
#define TTF_ERR_LOG_RCD_DBG(pstMemAllocInfo, pstMem, usMemRptCnt) \
{ \
    PS_MEM_SET(pstMemAllocInfo, 0, sizeof(TTF_MNTN_ERR_LOG_MEM_ALLOC_INFO_STRU));\
    usMemRptCnt++; \
}
#endif
extern VOS_VOID TTF_MNTN_ErrlogTtfMemAllocFail(VOS_UINT32 ulPid, VOS_UINT8 ucPoolId, VOS_UINT16 usFileId, VOS_UINT16 usLine, VOS_UINT32 ulAllocFailCnt);

#endif


#if((FEATURE_LTE == FEATURE_OFF) && (FEATURE_WIFI == FEATURE_ON))
#define TTF_MEM_RSV_PAD_LEN(usDataLen, usLen) \
{\
    usDataLen   = DRV_WifiCalDataLen(usLen + TTF_MEM_MAC_HEADER_RSV_LEN); \
    usLen       = ( TTF_MEM_SKB_HEAD_PAD_LEN + usDataLen+ TTF_MEM_SKB_TAIL_PAD_LEN); \
}
#else
#define TTF_MEM_RSV_PAD_LEN(usDataLen, usLen) \
{ \
    usLen      += TTF_MEM_MAC_HEADER_RSV_LEN; \
    usDataLen   = (VOS_UINT16)TTF_GET_32BYTE_ALIGN_VALUE(usLen); \
    usLen       = ( TTF_MEM_SKB_HEAD_PAD_LEN + usDataLen+ TTF_MEM_SKB_TAIL_PAD_LEN); \
}
#endif

extern VOS_UINT32 TTF_DynamicMemFree(VOS_UINT32 ulPid);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TTFMem.h */

