/******************************************************************************
  文 件 名   : PsQnode.h
  版 本 号   : 初稿
  作    者   : liukai
  生成日期   : 2013年9月16日
  最近修改   :
  功能描述   : PsQnode功能的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年9月16日
    作    者   : liukai
    修改内容   : 创建文件
******************************************************************************/

#ifndef __PS_QNODE_H__
#define __PS_QNODE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "PsCommonDef.h"
#include "TTFLink.h"
#include "TTFMem.h"


/******************************************************************************
  2 宏定义
******************************************************************************/
/* 使用者自定义参数段大小, 单位: B */
#define  MAX_PARA_OCTET_NUM     (32)

/*
当前考虑1x每20ms最多8块数据，RLP典型地等待时间在560ms，可以初步估计为8*560ms/20ms=224块。
假设1500B的IP包，按照256B分为8段，那么按照一个IP包计算，需要224*8=1792块。
如果后续可以把ehs的结点也整合到这个结构中，那么就可以复用ehs结点的个数和内存。
*/
#define  MAX_PS_QNODE_NUM      (1792)

/* 计算PSQnode个数(MAX_PS_QNODE_NUM)个bit, 占用多少个4byte */
#define  MAX_PS_QNODE_4BYTE_ALIGN_NUM   ((((MAX_PS_QNODE_NUM) + 0x1f) & (~0x1f)) / 32)

/* 检查数据越界的魔术字 */
#define  PS_QNODE_MAGICNUM     (0x1D2D)

#define PS_QNODE_RESET_SWITCH          (g_stNvPsQnodeResetCtrl.enResetEnable)
#define PS_QNODE_RESET_TOTAL_STAT_CNT  (g_stNvPsQnodeResetCtrl.usTotalStat)
#define PS_QNODE_RESET_THRESHOLD       (g_stNvPsQnodeResetCtrl.ucFailPercent)


/******************************************************************************
  3 枚举定义
******************************************************************************/
/* PsQnode调试开关 */
enum PS_QNODE_TRACE_PRINT_SWITCH_ENUM
{
    PS_QNODE_TRACE_PRINT_OFF     = 0,
    PS_QNODE_TRACE_PRINT_ON      = 1,
    PS_QNODE_TRACE_PRINT_BUTT
};

typedef VOS_UINT8 PS_QNODE_TRACE_PRINT_SWITCH_ENUM_UINT8;

/* PsQnode结点的状态 */
enum PS_QNODE_STATE_ENUM
{
    PS_QNODE_FREE_STATE     = 0,
    PS_QNODE_USED_STATE     = 1,
    PS_QNODE_STATE_BUTT
};

typedef VOS_UINT8 PS_QNODE_STATE_ENUM_UINT8;

/* TtfNode的源内存类型 */
enum PS_QNODE_MEM_SOURCE_TYPE_ENUM
{
    PS_QNODE_MEM_SOURCE_CONSECMEM_TYPE     = 0,
    PS_QNODE_MEM_SOURCE_TTFMEM_TYPE        = 1,
    PS_QNODE_MEM_SOURCE_TYPE_BUTT
};

typedef VOS_UINT8 PS_QNODE_MEM_SOURCE_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : PS_QNODE_EVENT_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : PsQnode事件上报ID
*****************************************************************************/
enum PS_QNODE_EVENT_ID_ENUM
{
    ID_PS_QNODE_FOUND_TAMPERED             = 0x0316,   /* _H2ASN_MsgChoice PS_QNODE_TAMPERED_EVENT_STRU */
    ID_PS_QNODE_TYPE_BUTT
};
typedef VOS_UINT16 PS_QNODE_EVENT_ID_ENUM_UINT16;




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

/*****************************************************************************
 结构名    : PS_QNODE_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Qnode统计结构
*****************************************************************************/
typedef struct
{
    volatile VOS_UINT32                      ulAllocTotalCnt;
    volatile VOS_UINT32                      ulAllocFailCnt;         /* 申请Qnode失败次数 */
    volatile VOS_UINT32                      ulFreeTotalCnt;
    volatile VOS_UINT32                      ulFreeNullPtrCnt;       /* 释放空指针次数 */
    volatile VOS_UINT32                      ulFreePtrBeforeCnt;     /* 重复释放次数 */
    volatile VOS_UINT32                      ulMagicTamperedCnt;     /* 魔术字被篡改次数 */
    volatile VOS_UINT32                      ulFreeInvalidPrtCnt;    /* 释放野指针 */
}PS_QNODE_STATISTICS_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_MGMT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PsQnode管理结构
*****************************************************************************/
typedef struct
{
    volatile VOS_UINT16                     usNodeIdx;     /* 结点使用指示 */
    PS_QNODE_TRACE_PRINT_SWITCH_ENUM_UINT8  enIsTracePrintOn;
    VOS_UINT8                               aucReserve[1];
    PS_QNODE_STATISTICS_STRU                stStat;
    volatile VOS_UINT32                     aulQuickMap[MAX_PS_QNODE_4BYTE_ALIGN_NUM];
}PS_QNODE_MGMT_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_DEBUG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PsQnode调试记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulAllocTick;        /* CPU tick when alloc or free */
    VOS_UINT16                      usAllocFileId;      /* File ID when alloc or free */
    VOS_UINT16                      usAllocLineNum;     /* File Line when alloc or free */
    VOS_UINT16                      usTraceFileId;      /* File ID when traced */
    VOS_UINT16                      usTraceLineNum;     /* File Line when traced */
    VOS_UINT32                      ulTraceTick;        /* CPU tick when traced */
}PS_QNODE_DEBUG_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_CONSECUTIVE_MEM_DSCP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 描述外部线性内存数据存放的结构
*****************************************************************************/
typedef struct _CONSECUTIVE_MEM_STRU
{
    VOS_UINT8                      *pucStartMem;    /* 线性内存起始地址 */
    /*
    MSB           LSB
     7 6 5 4 3 2 1 0
    +-+-+-+-+-+-+-+-
    |              |
    +-+-+-+-+-+-+-+-
    e.g, ucOffset = 2, 表示从MSB开始偏移2bit, 即bit 5开始
    */
    VOS_UINT8                        ucOffset;       /* 在起始字节中从MSB起偏移offset bit */
    VOS_UINT8                        aucReserve[1];
    VOS_UINT16                       usBitLen;       /* 数据长度 */
    struct _CONSECUTIVE_MEM_STRU    *pstNext;
}PS_QNODE_CONSECUTIVE_MEM_DSCP_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_TTF_MEM_DSCP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 描述外部TTF_MEM内存数据存放的结构
*****************************************************************************/
typedef struct _TTF_MEM_DSCP_STRU
{
    TTF_MEM_ST                     *pstMem;       /* TTF_MEM形式的内存 */
    /*
    MSB           LSB
     7 6 5 4 3 2 1 0
    +-+-+-+-+-+-+-+-
    |              |
    +-+-+-+-+-+-+-+-
    e.g, ucOffset = 2, 表示从MSB开始偏移2bit, 即bit 5开始
    */
    VOS_UINT8                       ucOffset;       /* 在起始字节中从MSB起偏移offset bit */
    VOS_UINT8                       aucReserve[1];
    VOS_UINT16                      usBitLen;       /* 数据长度 */
    struct _TTF_MEM_DSCP_STRU      *pstNext;
}PS_QNODE_TTF_MEM_DSCP_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_MEM_SOURCE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 描述内存中挂接的数据源的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulChoice;   /* choice的类别可以继续扩展 */

    #define      PS_QNODE_MEM_SOURCE_CONSECMEM_CHOSEN       0    /* 采用线性内存提供数据 */
    #define      PS_QNODE_MEM_SOURCE_TTFMEM_CHOSEN          1    /* 采用TTF_MEM提供数据 */

    union
    {
        PS_QNODE_CONSECUTIVE_MEM_DSCP_STRU      stSrcConsecMem;
        PS_QNODE_TTF_MEM_DSCP_STRU              stSrcTtfMem;
    }u;
}PS_QNODE_MEM_SOURCE_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PsQnode结构
*****************************************************************************/
typedef  struct
{
    TTF_NODE_ST                         stNode;                         /* 便于队列挂接 */
    PS_QNODE_MEM_SOURCE_STRU            stMemSrc;
    volatile VOS_UINT16                 usMagic;                        /* 紧跟MemSrc, 用于检查是否出现数据越界 */
    volatile VOS_UINT16                 usIndex;                        /* 结点索引号, 唯一 */
    volatile PS_QNODE_STATE_ENUM_UINT8  enState;
    VOS_UINT8                           aucReserve1[3];
    PS_QNODE_DEBUG_STRU                 stDbg;
    VOS_UINT8                           aucPara[MAX_PARA_OCTET_NUM];    /* 外部使用者存放自定义参数的区域 */
}PS_QNODE_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_TAMPERED_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于上报Qnode被篡改事件
*****************************************************************************/
typedef struct
{
    VOS_UINT16      usEventId;
    VOS_UINT16      usReserved;
    VOS_UINT32      ulModuleId;

    VOS_UINT16      usFileId;
    VOS_UINT16      usLineId;
    VOS_UINT32      ulPid;
    VOS_UINT32      ulTick;
    PS_QNODE_STRU   stQnode;    /* 被篡改的Qnode */
}PS_QNODE_TAMPERED_EVENT_STRU;

/*****************************************************************************
 结构名    : PS_QNODE_RESET_STATISTIC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于统计Qnode申请失败次数，判断是否进行复位
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enStartStat;    /* 是否开始统计 */
    VOS_UINT8                               aucReserved[3];
    VOS_UINT16                              usFailCnt;      /* 节点申请失败统计值 */
    VOS_UINT16                              usTotalStatCnt; /* 节点申请总个数统计值  */
}PS_QNODE_RESET_STATISTIC_INFO_STRU;



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION定义
******************************************************************************/


/******************************************************************************
  4 全局变量声明
******************************************************************************/
extern PS_QNODE_STRU    g_astQnode[MAX_PS_QNODE_NUM];


/******************************************************************************
  9 OTHERS定义
******************************************************************************/
PS_QNODE_STRU* PS_Qnode_GetNode
                            (VOS_UINT16 usFileId,
                            VOS_UINT16 usLineId,
                            VOS_UINT32 ulPid);

PS_RSLT_CODE_ENUM_UINT32 PS_Qnode_FreeNode
                              (VOS_UINT16       usFileId,
                               VOS_UINT16      usLineId,
                               VOS_UINT32      ulOpPid,
                               PS_QNODE_STRU  *pstQnode);

PS_RSLT_CODE_ENUM_UINT32 PS_Qnode_FillMemInfo
                    (VOS_UINT16   usFileId,
                    VOS_UINT16                     usLineId,
                    VOS_UINT32                     ulPid,
                    PS_QNODE_STRU                 *pstQnode,
                    PS_QNODE_MEM_SOURCE_STRU      *pstMemSrc,
                    VOS_UINT8                      ucParaOctetCnt,
                    VOS_UINT8                      aucPara[]);

VOS_VOID PS_Qnode_ResetCtrlInitNvPara(VOS_VOID);

VOS_VOID PS_Qnode_ResetStatInfoInit(VOS_VOID);

VOS_VOID PS_Qnode_ResetGetFailProc
(
    VOS_UINT16                          usFileId,
    VOS_UINT16                          usLineId,
    VOS_UINT32                          ulPid
);



#define PS_GET_QNODE(ulPid) \
    PS_Qnode_GetNode(THIS_FILE_ID, __LINE__, (ulPid))

#define PS_FREE_QNODE(ulPid, pstQnode) \
    PS_Qnode_FreeNode(THIS_FILE_ID, __LINE__, (ulPid), (pstQnode))

#define PS_FILL_QNODE(ulPid, pstQnode, pstMemSrc, ucParaOctetCnt, aucPara) \
    PS_Qnode_FillMemInfo(THIS_FILE_ID, __LINE__, (ulPid), (pstQnode), \
        (pstMemSrc), (ucParaOctetCnt), (aucPara))

extern VOS_VOID PS_Qnode_Init(VOS_VOID);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* PsQnode.h */


