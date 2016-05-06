/************************************************************************
 *                                                                      *
 *                             VOS_MEM.H                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/1                                       *
 *  Author:             Zhu Yingming                                    *
 *  Modify Date:                                                        *
 *  Document:  《VRP3.0-VOS内存管理详细设计说明书》                     *
 *             《VRP3.0-VOS内存管理概要设计说明书》                     *
 *  Function: VOS memory managment.                                     *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2000 - 2002 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 ************************************************************************/


#ifndef _VOS_MEM_H_
#define _VOS_MEM_H_

#ifdef TCPIP_DOPRA_V2    /*如用户需要使用Doprav2,则VISP与Dopra版本保持强依赖关系,需要包含Dopra头文件*/
#include "v_memory.h"
#else /* 和旧版本保持一致 */
#include "vrp_mem.h"   
#endif


#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifdef  __cplusplus
extern "C" {
#endif



#ifndef HIWORD
#define HIWORD(x)                      (x>>16)
#endif

#ifndef LOWORD
#define LOWORD(x)                      (x&0x0000FFFF)
#endif



/* added by guoxiaojun for the "guodiao" version of VRP3.0 */
#if ((VRP_PRODUCT_8040 == VRP_YES)  &&  (VRP_OS_VXWORKS == VRP_YES))
typedef struct tagMibMemInfo{
  ULONG ulBufSize;           /* 8040的buffer的大小     */
  ULONG ulTotalCounts;       /* 本类型内存的总共块数   */
  ULONG ulInUseCounts;       /* 正在使用的内存块数     */
  ULONG ulFreeCounts;        /* 目前空闲的内存块数     */
  ULONG ulDropCounts;        /* 申请失败的内存块数     */
  ULONG ulFreeError2;        /* 边界未对齐释放错误     */
  ULONG ulFreeError3;        /* 内存重复释放错误       */
  ULONG ulCollectCounts;     /* 内存收集记数           */
}VOS_MIBMEMINFO_S;

VOID VOS_Mem_GetMIBInfo(VOS_MIBMEMINFO_S stMibMemInfo[]);
#endif
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern ULONG TCPIP_Free(VOID* pBuf);
#ifdef  __cplusplus
}
#endif

#endif
