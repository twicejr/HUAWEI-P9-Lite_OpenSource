/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SsGlobal.h
  Description : Ss全局控制数据结构头文件
  History     :
      1.  张志勇      2004.02.27   新版作成
      2.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/
#ifndef _SS_GLOBAL_H_
#define _SS_GLOBAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
/********************************************************************************/
/******************************SS实体信息 ***************************************/
/********************************************************************************/
typedef struct
{                                               /* SS实体信息                   */
#define SS_S_NULL                0x00           /* S0:Null                      */
#define SS_S_CONNECT_PEND        0x01           /* S1:MM Connection pending     */
#define SS_S_CONNECTED           0x02           /* S2:MM Connection established */
    VOS_UINT8                  ucState;             /* SS实体状态                   */
    VOS_UINT8                  ucCr;                /* 记录TAF消息中的CR            */
} SS_ENTITY_STRU;

/********************************************************************************/
/*****************************消息缓存BUFFER*************************************/
/********************************************************************************/
#define SS_MO_ENTITY_NUM          7             /* 呼叫个数最大值               */

typedef struct {
    VOS_UINT32  ulMsgLen;                            /* 储存消息的长度               */
    VOS_UINT8  *pucMsg;                             /* 指向储存消息的指针           */
} SS_SAVE_MSG_STRU;


/********************************************************************************/
/*****************************动态内存管理信息***********************************/
/********************************************************************************/
#define    SS_MAX_MEM_NUM         10            /* 内存申请最大个数             */

typedef struct
{
    VOS_UINT8       ucMemNum;                       /* 记录开辟的内存块的个数       */
    VOS_UINT32       *pulMemBlk[SS_MAX_MEM_NUM];     /* 指向每个开辟的内存块的地址   */
} SS_MEMORY_MNG_STRU;


/********************************************************************************/
/******************************TIMER管理信息*************************************/
/********************************************************************************/
typedef struct
{
    HTIMER    SsTimerId;                      /* 存储VOS分配的Timer id        */

#define    SS_TIMER_IDLE      0x00              /* 该Timer未启动                */
#define    SS_TIMER_RUN       0x01              /* 该Timer已启动                */
#define    SS_TIMER_EXPIRY    0x02              /* 该Timer已溢出                */
    VOS_UINT8       ucTimerState;                   /* 该Timer的状态                */
} SS_TIMER_MNG_STRU;

/********************************************************************************/
/******************************OM管理信息*************************************/
/********************************************************************************/
/*****************************************************************************
 枚举名    : NAS_SS_OM_MSG_ID_ENUM_U32
 结构说明  : SS发送给OM的可维可测消息
  1.日    期   : 2014年6月30日
    作    者   : w00242748
    修改内容   : SS发送给OM的可维可测消息ID枚举
*****************************************************************************/
enum NAS_SS_OM_MSG_ID_ENUM
{
    /* CC发送给OM的消息 */
    SSOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_SS_LOG_STATE_INFO_STRU */

    SSOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_SS_OM_MSG_ID_ENUM_U32;

/*****************************************************************************
 结构名    : NAS_SS_LOG_STATE_INFO_STRU
 结构说明  : 勾SS的状态的结构

 修改记录  :
 1.日    期   : 2014年06月30日
   作    者   : w00242748
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucSsState;
    VOS_UINT8                           aucRsv3[3];
}NAS_SS_LOG_STATE_INFO_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#endif
