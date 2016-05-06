/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : LUPZeroCopy.h
  版 本 号   : 初稿
  作    者   : h00133115
  生成日期   : 2008年9月1日
  最近修改   :
  功能描述   : 定义了LTE 用户面使用的内存管理
  函数列表   :
  修改历史   :
  1.日    期   : 2008年9月1日
    作    者   : h00133115
    修改内容   : 创建文件

******************************************************************************/

#ifndef __LUP_ZEROCOPY_H_
#define __LUP_ZEROCOPY_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "TTFLink.h"
/*lint -e40*/
#include "TTFMem.h"
/*lint +e40*/

#define IPPACKET_MIN_LEN                1500
/*#define LUP_DEBUG
 */
/******************************************************************************
  2 宏定义
******************************************************************************/
/*================================*/            /* TTF常用操作宏定义 */
#define LUP_RMEM_INIT(rMem,enMemType,pStart)     \
{                                                \
    (rMem)->sRefCnt = 1;                         \
    (rMem)->enBlkType    = (enMemType);            \
    (rMem)->enL2DataType = LUP_DATA_TYPE_DEFAULT;\
    (rMem)->pucStarAddr  = (pStart);\
}

#define LUP_MEM_INIT(pMem,rMem,ulLen)       \
{                                               \
    (pMem)->pNext   = VOS_NULL_PTR;             \
    (pMem)->rMem    = (rMem);                     \
    (pMem)->usUsed  = (ulLen);                        \
    (pMem)->pData   = (VOS_UINT8 *)((rMem) + 1);\
}

/*总长度是指从指针头部到最后的数据?*/
#define LUP_MEM_REMOVE_FROM_HDR(pMem, usNum)    \
{                                               \
    (pMem)->pData  += (usNum);                  \
    (pMem)->usUsed -= (usNum);                  \
}

#define  LUP_MEM_SIZE                            sizeof(LUP_MEM_ST)
#define  R_MEM_SIZE                              sizeof(R_MEM_ST)

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
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
 结构名    : LUP_USED_BLK_MEM_TYPE
 协议表格 :
 ASN.1描述 :
 结构说明 : 内存块类型
*****************************************************************************/
enum LUP_USED_BLK_MEM_TYPE
{
    LUP_USED_BLK_MEM_TYPE_LUP    = 0    ,   /*V7 L2内部的内存池*/
    LUP_USED_BLK_MEM_TYPE_GUTTF         ,   /*V7版本融合后,GU模TTF内存池*/
    LUP_USED_BLK_MEM_TYPE_DLTB          ,   /*下行TB块*/
    LUP_USED_BLK_MEM_TYPE_BUTT
};
typedef VOS_UINT8   LUP_USED_BLK_MEM_TYPE_EN_UINT8;

/*****************************************************************************
 结构名    : L2_DATA_TYPE
 协议表格 :
 ASN.1描述  :
 结构说明 : 分配该内存块的L2数据类型
*****************************************************************************/
enum LUP_DATA_TYPE
{
    LUP_DATA_TYPE_DEFAULT     = 0x0,      /*默认为0*/
    LUP_DATA_TYPE_PDCP_PDU         ,      /*使用该内存块的是PDCP PDU*/
    LUP_DATA_TYPE_BUTT
};
typedef VOS_UINT8   LUP_DATA_TYPE_EN_UINT8;

/*****************************************************************************
 结构名    : R_MEM_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 在原始内存块的最前面，记录引用计数等信息，
                 与LUP_MEM_ST结构共同实现零拷贝功能
*****************************************************************************/
typedef struct _R_MEM_ST
{
    VOS_INT16                           sRefCnt;            /*引用计数*/
    LUP_USED_BLK_MEM_TYPE_EN_UINT8      enBlkType;          /*内存块类型*/
    LUP_DATA_TYPE_EN_UINT8              enL2DataType;       /*使用该内块的L2数据类型*/
    VOS_UINT8                          *pucStarAddr;        /*原始起始地址预留*/
    VOS_UINT32                          aulRev[2];          /*预留*/
    VOS_UINT32                          aulRev2[2];         /*预留*/
}R_MEM_ST;

/*****************************************************************************
 结构名    : LUP_MEM_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : L2零拷贝内存描述符
*****************************************************************************/
typedef struct _LUP_MEM_ST
{
    struct _LUP_MEM_ST                  *pNext;             /* 该数据的下一段 */
    VOS_UINT32                           usUsed;            /* 数据长度 */
    VOS_UINT8                           *pData;             /* 存放数据的指针，物理上指向结构体的连续内*/
    R_MEM_ST                            *rMem;              /*实际内存的控制结构*/
    VOS_UINT8                            aucResv[24];       /*预留字段*/
} LUP_MEM_ST;

/*****************************************************************************
 结构名    : LUP_TB_MEM_CTRL_BLOCK
 协议表格  :
 ASN.1描述 :
 结构说明  : L2 DL TB内存池节点结构
*****************************************************************************/
typedef struct LUP_TB_MEM_CTRL_BLOCK_ST
{
    VOS_UINT32      ulUsedflg;
    VOS_UINT32      ulPid;
    VOS_UINT32      ulFileID;
    VOS_UINT32      ulLineNum;
    R_MEM_ST        stRMem;
} LUP_TB_MEM_CTRL_BLOCK;

/*Balong V7 GU模用户面数据结构,联调中前期L模打桩测试*/
#ifdef GU_TTFMEM_STUB

    /*****************************************************************************
     结构名    : TTF_MEM_ST
     协议表格  :
     ASN.1描述 :
     结构说明  : GU模内存管理结构，镜像桩
    *****************************************************************************/


    /*****************************************************************************
    结构名    : GU_TTFMEM_STUB_POOL
    协议表格  :
    ASN.1描述 :
    结构说明  : V7R1内存池使用Balong，桩代码是在联调中前期
              和内部测试使用
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT32      ulSize;
        VOS_UINT32      ulNum;
        TTF_MEM_ST     *pstTtfMemLink;
    }GU_TTFMEM_STUB_POOL;
/*lint -e507*/
#ifdef TTF_MemFree
#undef TTF_MemFree
#endif
    #define TTF_MemFree(ulPid, pMem) \
        TTF_MemFree_Debug((VOS_UINT16)THIS_FILE_ID, (VOS_UINT16)__LINE__, ulPid, &pMem)

#ifdef TTF_MemBlkAlloc
#undef TTF_MemBlkAlloc
#endif
    #define TTF_MemBlkAlloc(ulPid,ulPoolId,ulLen) \
        TTF_MemBlkAlloc_Debug((VOS_UINT16)THIS_FILE_ID, (VOS_UINT16)__LINE__, ulPid, ulPoolId, ulLen)

#endif
/*lint +e507*/
#define  GUTTFMEM_OFFSETOFRMEM    ((VOS_UINT32)(&(((TTF_MEM_ST*)0)->ulForLte[0])))
#define  LUPMEM_OFFSETOFPDATA   ((VOS_UINT32)(&(((LUP_MEM_ST*)0)->pData)))
#define  LUPMEM_OFFSETOFLEN     ((VOS_UINT32)(&(((LUP_MEM_ST*)0)->usUsed)))
#define  LUPMEM_OFFSETOFNEXT    ((VOS_UINT32)(&(((LUP_MEM_ST*)0)->pNext)))
#define  DLTBMEM_OFFSETOFRMEM    ((VOS_UINT32)(&(((LUP_TB_MEM_CTRL_BLOCK*)0)->stRMem)))

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

/******************************************************************************
  8 UNION定义
******************************************************************************/


/******************************************************************************
  9 OTHERS定义
******************************************************************************/
VOS_UINT32  LUP_MemGet(VOS_UINT32 ulPid, LUP_MEM_ST *pMemSrc, VOS_UINT32 ulOffset,
                             VOS_UINT8 *pDest, VOS_UINT32 ulLen);
VOS_UINT32  LUP_MemGetHeadData(VOS_UINT32 ulPid, LUP_MEM_ST *pMemSrc,
                                         VOS_UINT8 *pDest, VOS_UINT32 ulLen);
VOS_UINT32  LUP_MemGetLen(VOS_UINT32 ulPid, LUP_MEM_ST *pMem);
VOS_UINT32  LUP_MemGetSingleLen(VOS_UINT32 ulPid, const LUP_MEM_ST *pMem);
VOS_UINT32  LUP_MemLink(VOS_UINT32 ulPid, LUP_MEM_ST *const*ppMemHead, LUP_MEM_ST *pMemTail);
LUP_MEM_ST *LUP_MemSingleFree_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, LUP_MEM_ST *pMem);
VOS_VOID    LUP_MemFree_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, LUP_MEM_ST **ppMem);
LUP_MEM_ST *LUP_MemAlloc_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulLen);
LUP_MEM_ST *LUP_MemCopyAlloc_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, const VOS_UINT8 *pData, VOS_UINT32 ulLen);
VOS_UINT32 LUP_MemCutHeadData_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, LUP_MEM_ST **ppMemSrc, VOS_UINT8 *pDest, VOS_UINT32 ulLen);
VOS_UINT32 LUP_MemCutTailData_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, LUP_MEM_ST **ppMemSrc,
                                              VOS_UINT8 *pDest, VOS_UINT32 ulLen);
VOS_UINT32 LUP_MemAddHeadData_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, LUP_MEM_ST **ppMemDest,
                                                 const VOS_UINT8  *pSrcData, VOS_UINT32  ulAddLen);
LUP_MEM_ST * LUP_MemGetNewSlice_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum,
                                                  VOS_UINT32 ulPid, LUP_MEM_ST *pMemSrc,VOS_UINT32 ulOffset,
                                                  VOS_UINT32 ulLen );
LUP_MEM_ST * LUP_MemRef_Debug (VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid, const LUP_MEM_ST *pMemSrc );
VOS_UINT32 LUP_MemGetIdleBlockNum(VOS_UINT32 ulIndex);

VOS_UINT32 LUP_MemMonitorIdleBlock(VOS_UINT32 ulIndex, VOS_UINT32 ulUnderStand);
extern TTF_MEM_ST * TTF_MemBlkAlloc_Debug( VOS_UINT16 ulFileId,VOS_UINT16 ulLineNum,VOS_UINT32 ulPid,
                                                    VOS_UINT32 ulPoolId,VOS_UINT16 ulSize );
extern VOS_VOID TTF_MemFree_Debug( VOS_UINT16 ulFileId,VOS_UINT16 ulLineNum,VOS_UINT32 ulPid,TTF_MEM_ST **pstMem );


LUP_MEM_ST *LUP_MemAllocUnCacheMem_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum,
                                                        VOS_UINT32 ulPid, VOS_UINT32 ulLen);
LUP_MEM_ST *LUP_MemAllocCacheMem_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum,VOS_UINT32 ulPid, VOS_UINT32 ulLen);
LUP_MEM_ST * LUP_MemAllocForIpf( TTF_MEM_ST *pstTTFMem );

LUP_MEM_ST *LUP_MemAllocDlTbMem_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum,
                                                   VOS_UINT32 ulPid, VOS_UINT32 ulLen);
LUP_MEM_ST *LUP_MemAllocLMDlTbMem_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum,
                                                      VOS_UINT32 ulPid, VOS_UINT32 ulLen);

LUP_MEM_ST *LUP_MemAllocLSDlTbMem_Debug(VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum,
                                                   VOS_UINT32 ulPid, VOS_UINT32 ulLen);
#define LUP_MemFree(ulPid, pMem) \
    LUP_MemFree_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, &pMem)

#define LUP_MemSingleFree(ulPid, pMem) \
    LUP_MemSingleFree_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, pMem)

#define LUP_MemAllocDlTbMem(ulPid,ulLen) \
    LUP_MemAllocDlTbMem_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, ulLen)

#define LUP_MemAllocLMDlTbMem(ulPid,ulLen) \
    LUP_MemAllocLMDlTbMem_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, ulLen)

#define LUP_MemAllocLSDlTbMem(ulPid,ulLen) \
    LUP_MemAllocLMDlTbMem_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, ulLen)

#define LUP_MemAlloc(ulPid, ulLen) \
    LUP_MemAllocCacheMem_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, ulLen)

#define LUP_MemAllocUnCacheMem(ulPid, ulLen) \
    LUP_MemAllocUnCacheMem_Debug((VOS_UINT32)__FILE__,  __LINE__,ulPid,ulLen);

#define LUP_MemAllocCacheMem(ulPid, ulLen) \
    LUP_MemAllocCacheMem_Debug((VOS_UINT32)__FILE__,  __LINE__,ulPid,ulLen);

#define LUP_MemCopyAlloc(ulPid, pData, ulLen) \
    LUP_MemCopyAlloc_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, pData, ulLen)

#define LUP_MemCutHeadData(ulPid, ppMemSrc, pDest, ulLen) \
    LUP_MemCutHeadData_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, ppMemSrc, pDest, ulLen)

#define LUP_MemAddHeadData(ulPid, ppMemDest, pSrcData, ulAddLen) \
    LUP_MemAddHeadData_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, ppMemDest, pSrcData, ulAddLen)

#define LUP_MemGetNewSlice(ulPid, pMemSrc,ulOffset,ulLen) \
    LUP_MemGetNewSlice_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, pMemSrc,ulOffset,ulLen)

#define LUP_MemRef(ulPid, pMemRef) \
    LUP_MemRef_Debug((VOS_UINT32)__FILE__, __LINE__, ulPid, pMemRef)

extern VOS_UINT32 LUP_DlTbMemThreshold(VOS_UINT32 ulThreshold);
extern VOS_UINT32 LUP_DlTbMemIdleCnt(VOS_VOID);

extern VOS_UINT32  LUP_ZeroCopyInit( VOS_VOID );
extern VOS_UINT32 LUP_DlTbMemPoolInit(VOS_VOID);
extern LUP_TB_MEM_CTRL_BLOCK* LUP_DlTbMemPoolAlloc(VOS_UINT32 ulSize, VOS_UINT32 ulFileID, VOS_UINT32 ulLineNo);

extern VOS_VOID LUP_MemGetLinkInfo(const LUP_MEM_ST *pMem, VOS_UINT32 *pulLinkValid, VOS_UINT32 *pulFirstLen);

extern VOS_UINT32 LUP_MemGetDataPriority(const LUP_MEM_ST * pMem );

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* LUPZeroCopy.h */



