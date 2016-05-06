/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmrEnt.h
  Description : smr实体结构定义
  History     :
      1.  张志勇   2004.2.24   新版作成
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  3.Data :2007-08-20
    Author:z40661
    Modify:A32D12705
  4.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
  5.日    期   : 2010年3月1日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
*******************************************************************************/
#ifndef _SMR_ENTITY_H_
#define _SMR_ENTITY_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

#define SMR_MIN_RP_DATA_LEN             0x05
#define SMR_MIN_RP_ACK_LEN              0x02
#define SMR_MIN_RP_ERROR_LEN            0x04

#define  SMR_MAX_ENT_NUM     1

/* TIMER时长 */
#define SMR_TIMER_TR1M_LENGTH           (45000)

#define SMR_TIMER_TRAM_LENGTH     30000
#define SMR_TIMER_TR2M_LENGTH     15000
#define SMR_TIMER_TRRM_LENGTH     10000


typedef struct{
    HTIMER                              TimerId;                                                  /* Timer Id                                 */
    VOS_UINT8                           ucTimerSta;                                               /* 标识Timer是否有效                        */
    VOS_UINT8                           aucReserved1[3];
}SMR_TIMER_MNG_STRU;

typedef struct
{
    struct{
        VOS_UINT8                       ucState;                                                      /* SMR实体状态                              */
        VOS_UINT8                       ucMr;                                                         /* Message Reference                        */
        VOS_UINT8                       ucMemAvailFlg;                                                /* 标志是否是通知过程                       */
        VOS_UINT8                       ucRetransFlg;                                                 /* 是否重传标志                             */
        SMR_TIMER_MNG_STRU              aTimerInfo[3];                                     /* TIMER信息                                */
    }SmrMo;
    struct{
        VOS_UINT8                       ucState;                                                      /* SMR实体状态                              */
        VOS_UINT8                       ucMr;                                                         /* Message Reference                        */
        VOS_UINT8                       aucReserved1[2];
        SMR_TIMER_MNG_STRU              TimerInfo;                                         /* TIMER信息                                */
        SMR_TIMER_MNG_STRU              RelTimerInfo;                                          /* Release TIMER信息                        */
    } SmrMt;

} SMR_ENTITY_STRU;

extern SMR_ENTITY_STRU     g_SmrEnt;                                            /* smr的实体声明                            */

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

