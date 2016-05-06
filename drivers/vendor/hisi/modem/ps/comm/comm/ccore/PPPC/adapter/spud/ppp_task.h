/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ppp_task.h
  版 本 号   : 初稿
  作    者   : luofang
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : ppp_task.c的头文件
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : luofang
    修改内容   : 创建文件

******************************************************************************/

#ifndef _PPP_TASK_H_H_H_
#define _PPP_TASK_H_H_H_


extern VOS_UINT32 PPP_QueueInit(VOS_VOID);
extern VOS_UINT32 PPP_TaskInit(VOS_VOID);
extern VOS_UINT32 PPP_TaskEntry(VOS_VOID);







extern VOID L2TP_AttachQueue(VOS_VOID);
extern VOS_UINT32 PPP_CompInit1(VOS_VOID);
extern VOS_UINT32 PPP_CompInit3(VOS_VOID);
extern VOS_UINT32 PPP_CompInit2(VOS_VOID);
VOS_VOID PPP_SubBoardInit(VOS_VOID);




#ifdef __WIN32_PLATFORM__
#define DVM_WaitForSysCanRun() 1

#endif


#endif /* _PPP_TASK_H_H_H_ */
