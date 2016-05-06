/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcMain.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年8月13日
  最近修改   :
  功能描述   : MtcMain.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月13日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MTCMAIN_H__
#define __MTCMAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

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
 结构名    : MTC_MSG_PROC_FUNC
 结构说明  : 消息处理函数指针

  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   :  V9R1 干扰控制项目
*****************************************************************************/
typedef VOS_VOID (*MTC_MSG_PROC_FUNC)(VOS_VOID* pMsg);

/*****************************************************************************
 结构名    : MTC_PROC_MSG_STRU
 结构说明  : MTC模块消息处理函数的结构

  1.日    期  : 2013年08月13日
    作    者  : j00174725
    修改内容  :  V9R1 干扰控制项目
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgType;                              /* MTC接收消息ID */
    MTC_MSG_PROC_FUNC                   pProcMsgFunc;
}MTC_MSG_PROC_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 MTC_SearchMsgProcTab(
    VOS_UINT32                          ulMsgCnt,
    VOS_VOID                           *pstMsg,
    const MTC_MSG_PROC_STRU            *pstMsgProcTab
);

VOS_VOID MTC_RcvModem0MmaMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem1MmaMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem0TafMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem1TafMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem1GasMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem0TdsMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem0LteMsg(struct MsgCB *pstMsg);

/* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, begin */
VOS_VOID MTC_RcvModem0GasMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem0WasMsg(struct MsgCB *pstMsg);
/* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, end */

#if (3 == MULTI_MODEM_NUMBER)
VOS_VOID MTC_RcvModem2MmaMsg(struct MsgCB *pstMsg);
VOS_VOID MTC_RcvModem2TafMsg(struct MsgCB *pstMsg);
VOS_VOID MTC_RcvModem2GasMsg(struct MsgCB *pstMsg);
#endif

VOS_VOID MTC_RcvCbpcaMsg(struct MsgCB *pstMsg);

VOS_VOID MTC_RcvModem0TcMsg(
    struct MsgCB                       *pstMsg
);
VOS_VOID MTC_RcvModem1TcMsg(
    struct MsgCB                       *pstMsg
);
VOS_VOID MTC_RcvModem0ETcMsg(
    struct MsgCB                       *pstMsg
);

VOS_VOID MTC_ProcMsg(MsgBlock* pMsg);



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

#endif /* end of MtcMain.h */
