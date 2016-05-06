/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_type.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2005/4/23
Last Modified :
Description   : The common data type defination
Function List :
History       :
1.Date        : 2008/06/28
  Author      : c42025
  Modification: modified definition for HI_S8

2.Date        :   2008/10/31
  Author      :   z44949
  Modification:   Translate the chinese comment
******************************************************************************/
#ifndef __HI_MEM_H__
#define __HI_MEM_H__

#include "hi_type.h"
#include <linux/seq_file.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/io.h>

#include "hi_drv_venc.h"
#include <linux/math64.h>
#include <linux/hisi/hisi_ion.h>
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern HI_U32  g_VencPrintEnable;
extern HI_CHAR g_VencPrintMsg[1024];

typedef enum
{
    VENC_FATAL = 0,
    VENC_ERR,
    VENC_WARN,
    VENC_INFO,
    VENC_DBG,
    VENC_ALW,
}VENC_PRINT_TYPE;

#define HI_FATAL_VENC(fmt,...) HI_PRINT(VENC_FATAL,(char *)__FILE__, (int)__LINE__, (char *)__FUNCTION__, fmt, ##__VA_ARGS__)
#define HI_ERR_VENC(fmt,...)   HI_PRINT(VENC_ERR,(char *)__FILE__, (int)__LINE__, (char *)__FUNCTION__, fmt, ##__VA_ARGS__)
#define HI_WARN_VENC(fmt,...)  HI_PRINT(VENC_WARN,(char *)__FILE__, (int)__LINE__, (char *)__FUNCTION__, fmt,##__VA_ARGS__)
#define HI_INFO_VENC(fmt,...)  HI_PRINT(VENC_INFO,(char *)__FILE__, (int)__LINE__, (char *)__FUNCTION__, fmt,##__VA_ARGS__)
#define HI_DBG_VENC(fmt,...)   HI_PRINT(VENC_DBG,(char *)__FILE__, (int)__LINE__, (char *)__FUNCTION__, fmt,##__VA_ARGS__)

#define ALIGN_UP(val, align) ( (val+((align)-1))&~((align)-1) )

typedef struct
{
	HI_U64 DdrBasePhyAddr;	 /*起始物理地址*/
	HI_U8* pDdrBaseVirAddr;
	HI_U64 Vir2BusOffset;
	HI_U64 DdrOffset;	/*偏移*/
	HI_U32 DdrSize; 	/*分配大小，以字节为单位*/
}DDR_MEM_ALLOC;

typedef struct
{
    HI_VOID *pStartVirAddr;
    HI_U32    u32StartPhyAddr;
    HI_U32    u32Size;
}MEM_BUFFER_S;

typedef struct
{
	HI_U64 VirAddr;
	HI_U64 PhyAddr;
	HI_U32 Length;
}MEM_DESC_S;


/***********************************************************************************
    memory menage relative functions
***********************************************************************************/
#define MAX_ION_MEM_NODE     (200)
#define MAX_MEM_NAME_LEN     (15)

typedef struct
{
    HI_CHAR node_name[MAX_MEM_NAME_LEN];
    HI_CHAR zone_name[MAX_MEM_NAME_LEN];
    HI_U32  phys_addr;
	HI_U32  size;
    struct ion_handle *handle;
}ION_MEM_DESC_S;

extern DDR_MEM_ALLOC DdrMem;

HI_S32 HI_DRV_UserCopy(struct file *file,
           HI_U32 cmd, unsigned long arg,
           long (*func)(struct file *file,
               HI_U32 cmd, unsigned long uarg));

#define PROC_PRINT  seq_printf

#define HI_DRV_PROC_EchoHelper  printk

HI_VOID HI_PRINT(HI_U32 type,char *file, int line , char * function,  HI_CHAR*  msg, ... );

HI_U32 HI_GetTS(HI_VOID);


/**************************************platform.h**************************************************/
HI_S32 DRV_Venc_GetTimeStampMs(HI_U32 *pu32TimeMs);
HI_S32 DRV_MEM_INIT(HI_VOID);
HI_S32 DRV_MEM_EXIT(HI_VOID);

/* MMU内存分配  */
HI_S32 DRV_MMU_MEM_AllocAndMap(const HI_CHAR *bufname, HI_CHAR *zone_name,HI_U32 size, HI_S32 align, MEM_BUFFER_S *psMBuf,HI_U32 mmu_bypass_flag);
HI_VOID DRV_MMU_MEM_UnmapAndRelease(MEM_BUFFER_S *psMBuf,HI_U32 mmu_bypass_flag);
HI_S32 DRV_MMU_GetPhyAddr_KernelVaddr(venc_user_buf * pstFrameBuf);

/**************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */


