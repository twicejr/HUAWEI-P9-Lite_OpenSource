

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
