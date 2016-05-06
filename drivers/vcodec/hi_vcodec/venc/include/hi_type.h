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
#ifndef __HI_TYPE_H__
#define __HI_TYPE_H__
#include <linux/fs.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * The common data type, will be used in the whole project.*
 *----------------------------------------------*/
//#define VENC_SIMULATE//没有逻辑，模拟运行
//#define TEST_TIME
//#define SLICE_INT_EN  //slice级中断 
//#define RE_ENCODE_EN  // 使能重编功能 ,重编和输出低延迟不能同时打开 
//#define SPLIT_SPS_PPS //SPS PPS单独打包 发出 
//#define SHUTDOWN_REGULATOR_EN  //使能帧间上下电

#define IRQ_EN  //使能中断模式
//#define MD5_WC_EN  //使能MD5计算
#define HARDWARE_SPLIT_SPS_PPS_EN //硬件将SPS PPS单独打包，发出 
#define OUTPUT_LOWDELAY_EN //输出低延迟使能
#define SAO_LOWPOWER_EN  // SAO低功耗使能



typedef unsigned char           HI_U8;
typedef unsigned char           HI_UCHAR;
typedef unsigned short          HI_U16;
typedef unsigned int            HI_U32;

typedef signed char             HI_S8;
typedef short                   HI_S16;
typedef int                     HI_S32;

#ifndef _M_IX86
typedef unsigned long long      HI_U64;
typedef long long               HI_S64;
#else
typedef __int64                   HI_U64;
typedef __int64                   HI_S64;
#endif

typedef char                    HI_CHAR;
typedef char*                   HI_PCHAR;

typedef float                   HI_FLOAT;
typedef double                  HI_DOUBLE;
typedef void                    HI_VOID;

typedef unsigned long           HI_SIZE_T;
typedef unsigned long           HI_LENGTH_T;

typedef HI_U64 HI_HANDLE;

typedef int HI_LD_Event_ID_E;


/*----------------------------------------------*
 * const defination                             *
 *----------------------------------------------*/
typedef enum {
    HI_FALSE    = 0,
    HI_TRUE     = 1,
} HI_BOOL;

#ifndef NULL
#define NULL             0L
#endif
#define HI_NULL          0L
#define HI_NULL_PTR      0L

#define HI_SUCCESS       0
#define HI_FAILURE       (-1)


typedef struct HI_MMZ_BUS
{
    HI_U8  bufname[24]; //buffer名字
	HI_U64 kernel_viraddr;//buffer 内核地址
	HI_U64 user_viraddr; //buffer虚拟地址
	HI_U64 phyaddr;   //buffer物理地址

    HI_U32 bufsize;  //buffersize
    HI_U32 bufid;    //需要分配的bufferID
    HI_U32 portDir;  //端口类型
}HI_MMZ_BUF_S;


typedef enum  hiMOD_ID_E{
    HI_ID_VENC = 0,
    EVENT_VENC_FRM_IN,
    EVENT_VENC_FRM_OUT,
    HI_ERR_VENC_CHN_NOT_EXIST,
    HI_ERR_VENC_CHN_NO_ATTACH,
    HI_ERR_VENC_INVALID_PARA,
    HI_ERR_VENC_CREATE_ERR,
    HI_ERR_VENC_NOT_SUPPORT,
    HI_ERR_VENC_CHN_INVALID_STAT,
    HI_ERR_VENC_BUF_EMPTY,
    HI_ERR_VENC_CHN_RELEASE_ERR,
    HI_ERR_VENC_NULL_PTR,
    HI_ID_BUTT,
    HI_ID_VI,
    HI_ID_VO,
    HI_ID_DISP,
    //GFP_KERNEL,
    HI_LOG_LEVEL_INFO,
    HI_ID_VSYNC,
    HI_ERR_VENC_INVALID_CHNID,
    //EIO,
}HI_MOD_ID_E;

typedef struct MMZ_BUFFER_S
{
	HI_U64 u32StartVirAddr;
	HI_U64 u32StartPhyAddr;
	HI_U32 u32Size;
}MMZ_BUFFER_S;

typedef struct HI_LD_Event_S
{
    HI_S32 evt_id;
    HI_S32 frame;
    HI_HANDLE handle;
    HI_U32 time;
}HI_LD_Event_S;

typedef struct DRV_PROC_ITEM_S{
    void* data;
    int * read;
    int * write;
}DRV_PROC_ITEM_S;


typedef struct HI_RECT_S{
    HI_S32 s32Height;
    HI_S32 s32Width;
    HI_S32 s32X;
    HI_S32 s32Y;
}HI_RECT_S;

#define VERSION_STRING "1234"

//#define spinlock_t int
#define HI_INVALID_HANDLE (0xffffffff)

#define IOC_TYPE_VENC  'V' // 魔数 0-255

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */


