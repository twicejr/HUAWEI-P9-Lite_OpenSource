#ifndef C_IPF_BALONG_TEST_H
#define C_IPF_BALONG_TEST_H

#include <string.h>
#include <osl_thread.h>
#include <osl_cache.h>
#include "osal.h"
#include "osl_malloc.h"
#include "osl_sem.h"
#include "securec.h"
#include <bsp_ipf.h>
#include <bsp_hardtimer.h>
#include "ipf_balong.h"

#define T_DL_VALUE		0x5a
#define T_UL_VALUE		0x5b

typedef struct tagStreamIPv4Header
{
    unsigned int TOL:16;
    unsigned int TOS:8;
    unsigned int HeaderLen:4;
    unsigned int Vers:4; 
    unsigned int offset:13;
    unsigned int MF:1;
    unsigned int DF:1;
    unsigned int ReservFlag:1;
    unsigned int ID:16;
    unsigned int Checksum:16;
    unsigned int Prot:8;
    unsigned int TTL:8;    
    unsigned int SourceAddr;
    unsigned int DestAddr;
}StreamIPv4Header;

typedef struct tagStreamUDP
{
    unsigned int DstPort:16;
    unsigned int SrcPort:16;
    unsigned int Checksum:16;
    unsigned int Length:16;    
}StreamUDP;


//-psam test file needs ttf struct
#define TTF_OFFSET_OF_T(s, m) ((unsigned int)&(((s *)0)->m))
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct _TTF_NODE_ST
{
    struct _TTF_NODE_ST    *pNext;
    struct _TTF_NODE_ST    *pPrev;
} TTF_NODE_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*本内存属于哪一个内存池 */
    unsigned char                   ucClusterId;    /*本内存是属于哪一个级别*/
    unsigned char                   ucReserve[2];
    struct _TTF_MEM_ST             *pNext;          /* 该数据的下一段 */
    unsigned short                  usType;         /* 内存类型，DYN、BLK、EXT类型 */
    unsigned short                  usLen;          /* 申请数据的总长度，但不一定全部被使用 */
    unsigned short                  usUsed;         /* 已经使用的数据长度   */
    unsigned short                  usApp;          /* 使用者可以使用的区域 */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* 记录数据的原始指针 */
    unsigned char                  *pData;          /* 存放数据的指针，物理上指向结构体的连续内存 */
    void                           *pExtBuffAddr;   /* 保存extern类型的内存地址用于释放 */
    unsigned long                   ulForCds[1];    /*预留给CDS使用，GU模不用初始化*/

#if( FEATURE_LTE == FEATURE_ON )
    unsigned long                   ulForLte[6];    /*预留给LTE使用，GU模不用初始化*/
#endif
} TTF_MEM_ST;
//+psam test file needs ttf struct


void ipf_set_ccore_reset_flag(unsigned int flag);


#endif
