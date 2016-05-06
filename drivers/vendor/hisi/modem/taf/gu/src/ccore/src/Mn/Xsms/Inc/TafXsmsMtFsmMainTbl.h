/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsMtFsmMainTbl.h
  版 本 号   : 初稿
  作    者   : l00208516
  生成日期   : 2014年10月31日
  功能描述   : TafXsmsMtFsmMainTbl.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_MT_FSM_MAIN_TBL_H_
#define _TAF_XSMS_MT_FSM_MAIN_TBL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

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
/* MT状态机状态全局变量 */
extern TAF_FSM_DESC_STRU                g_stTafXsmsMtFsmDesc;

/* Xsms MT状态机状态处理表 */
extern TAF_STA_STRU                     g_astTafXsmsMtStaTbl[];

/* XSMS Mo_IDLE下的事件处理表 */
extern TAF_ACT_STRU                     g_astTafXsmsMtIdleActTbl[];

/* XSMS MT_WAITING_XCC_CALL_CONN的事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitXccConnActTbl[];

/* XSMS MT_WAITING_XCC_CNF的事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitXccAnsCallCnfActTbl[];

/* XSMS MT_WAITING_XCC_SO_IND的事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitXccSoIndActTbl[];

/* XSMS MT_WAITING_DSDH_DATA_IND状态下事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingDSCHDataIndActTbl[];

/* XSMS MT_WAITING_WRITE_UIM_CNF状态下事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingWriteUimCnfActTbl[];

/* XSMS MT_WAITING_READ_UIM_CNF状态下事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingReadUimCnfActTbl[];

/* XSMS MT_WAITING_AS_CNF状态下事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingAsCnfActTbl[];

/* XSMS MT_WAITING_END_CALL_CNF状态下事件处理表 */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingXccDisconnectActTbl[];





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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32 TAF_XSMS_GetMtFsmTblNum(VOS_VOID);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
