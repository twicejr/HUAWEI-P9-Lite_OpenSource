/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : CcRabmIf.h
  Description : CC与RABM接口头文件
  History     :
      1.  张志勇 2003.12.03   新版作成
      2.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/

#ifndef _CC_RABM_INTERFACE_H_
#define _CC_RABM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
#define RABMCC_SYNC_IND                       0                                 /* 消息类型定义                              */

/* 原语RABMCC_SYNC_IND RABM-->CC */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
#define    RABMCC_RAB_ACTIVE      0
#define    RABMCC_RAB_INACTIVE    1
    VOS_UINT32                  ulResult ;                                           /* 0：SI可以使用；1：SI不可以使用             */
    VOS_UINT32                  ulSi;                                                /* 已经建立或释放rab的si                     */
} RABMCC_SYNC_IND_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
