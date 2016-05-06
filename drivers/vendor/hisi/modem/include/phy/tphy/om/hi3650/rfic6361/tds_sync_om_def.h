/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_sync_om_def.h
  版 本 号   : 初稿
  作    者   : mah
  生成日期   : 2012年11月12日
  最近修改   :
  功能描述   : TDS CQI模块OM定义头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月12日
    作    者   : mah
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TDS_SYNC_OM_DEF_H__
#define __TDS_SYNC_OM_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "om_base_def.h"

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define TPHY_REQ_SYNC_OM_REP_SWITCH    OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_REQ, 0x0)
#define TPHY_REQ_SYNC_ALGTH_PARA       OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_REQ, 0x1)
#define TPHY_REQ_SYNC_STUB             OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_REQ, 0x2)

#define TPHY_IND_SYNC_STAT             OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_IND, 0x0)

/*----------------------------------------------*
 * 结构定义                                                    *
 *----------------------------------------------*/
 /*TDS SIR计算算法可配参数结构定义*/
typedef struct TDS_SYNC_ALG_PARA
{
     UINT16 usSyncThr0;
     UINT16 usSyncThr1;     
}TDS_SYNC_ALG_PARA_STRU;

typedef struct TDS_SYNC_STUB
{
     UINT16 usSyncStubSwitch;
     UINT16 usSyncStat;     /*0 -同步，1-失步*/
}TDS_SYNC_STUB_STRU;

typedef struct TDS_OM_STAT_IND_REQ
{
    UINT16 usSyncStatOmSwitch;
    UINT16 usRsvd;
    
}TDS_OM_STAT_IND_REQ_STRU;

typedef struct TDS_SYNC_OM_STAT
{
    UINT16 usSyncStatOmSwitch;
    UINT16 usCurSbfn;
    UINT16 usDpchCrc;           /*当前DPCH CRC结果，0正确，1错误*/   
    UINT16 usSbInd;             /*当前译码SB判决结果，0不是，1是*/   
    UINT16 usDschCrc;           /*当前DSCH CRC结果，0正确，1错误*/
    UINT16 usSyncFrmCnt;        //同失步配置开始时记录的系统子帧号
    UINT16 usOutSyncCnt;        //失步次数1
    UINT16 usCdSBCnt;           //SB 次数1
    UINT16 usCrcCorrectCnt;     //CRC 正确次数1
    UINT16 usDchSyncCtrlFlag;   //同步流程控制全局变量，功能等价于重邮代码中DchCtrlFlag
    UINT16 usCurDpchValidFlag;  /*当前子帧是否调度了DPCH*/
    UINT16 usCurSmothDpchSnr;
    UINT16 usNextDpchSnr;
    UINT16 usPrevDpchSnr;    
    UINT16 usSyncJudgeFlag;     /*当前子帧同失步判决结果*/
    UINT16 usTtiIndFlag;        /*当前TTI 边界指示判决结果*/
    UINT16 usHSDSCHSchled;      /*当前子帧HSDSCH是否调度指示，1调度，0不调度*/   
    UINT16 usCdSbfn;
    UINT16 usSnrTh0;
    UINT16 usSnrTh1;
}TDS_SYNC_OM_STAT_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

