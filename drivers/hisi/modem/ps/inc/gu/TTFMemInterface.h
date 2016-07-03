

#ifndef __TTFMEMINTERFACE_H__
#define __TTFMEMINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "v_typdef.h"
#include "product_config.h"
#include "TtfDrvInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 转定义原有的上行RLC SDU池的数据都从上行DATA池中取 */
#define  TTF_MEM_POOL_ID_UL_RLC_SDU    TTF_MEM_POOL_ID_UL_DATA

/* 转定义原有的上行RLC PDU池的数据都从上行DATA池中取 */
#define  TTF_MEM_POOL_ID_UL_RLC_PDU    TTF_MEM_POOL_ID_UL_DATA

/* 转定义原有的下行DL池的数据都从下行PDU池中取 */
#define  TTF_MEM_POOL_ID_DL            TTF_MEM_POOL_ID_DL_PDU


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名    : TTF_MEM_POOL_ID_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
*****************************************************************************/
enum TTF_MEM_POOL_ID_ENUM
{
    TTF_MEM_POOL_ID_DL_SHARE  = 0,    /* C-CPU 下行跨核共享内存池，目前只能由CDS和CST模块使用 */
    TTF_MEM_POOL_ID_DL_PDU,           /* C-CPU 下行PDU内存池 */
    TTF_MEM_POOL_ID_UL_DATA,          /* C-CPU 上行数据内存池 */
    TTF_MEM_POOL_ID_EXT,              /* A-CPU 跨核内存池 */
    TTF_MEM_POOL_ID_UL_IP_DATA,       /* C-CPU 上行 IP包数据内存池*/

    TTF_MEM_POOL_ID_BUTT
};
typedef VOS_UINT32 TTF_MEM_POOL_ID_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern TTF_MEM_ST *TTF_MemBlkAlloc_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT16 usLen);

extern VOS_VOID TTF_MemFree_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST **ppMem);

extern TTF_MEM_ST * TTF_DataTransformTtfMem_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,VOS_UINT8* pucData,VOS_UINT16 usLen, VOS_VOID*  pstIMMZc);



#define TTF_MemBlkAlloc(ulPid, ulPoolId, usLen) \
    TTF_MemBlkAlloc_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, usLen)



#define TTF_MemFree(ulPid, pMem) \
    TTF_MemFree_Debug(THIS_FILE_ID, __LINE__, ulPid, &(pMem))



extern VOS_VOID TTF_ExtMemFree( void **pstExtMem );

#define TTF_RemoteFreeImmMem(pucAddr)  TTF_ExtMemFree((&pucAddr))



#define TTF_DataTransformTtfMem(pucData, usLen, pstIMM)\
    TTF_DataTransformTtfMem_Debug(THIS_FILE_ID, __LINE__, pucData, usLen, pstIMM)



extern VOS_UINT32 TTF_GetDlIpFreeMemCnt (VOS_VOID);



extern VOS_UINT32 TTF_GetUlIpFreeMemCnt (VOS_VOID);



extern VOS_VOID TTF_MemCcpuCheckPoolLeak( VOS_VOID );



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TTFMemInterface.h */

