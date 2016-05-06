/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmcEnt.h
  Description : SMC实体结构定义
  History     :
      1.  张志勇   2004.2.24   新版作成
      2.  h44270  2006.02.07  修改TC1M的计时器超时时间  A32D01938
  3.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  4.Data :2007-08-20
    Author:z40661
    Modify:A32D12705
  5.Date         : 2008-05-07
    Author       : f62575
    Modification : MS在等待接收最后一个CP-ACK时接收到CP-DATA（携带RP-DATA）解释
                   为隐含的接收到前一事务的CP-ACK和新的CP-DATA事件；参考书协议24011 5.3.4, 5.4
                   另，修改TP-MMS数据与释放MM连接无关
  6.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
  7.日    期   : 2010年2月20日
    作    者   : f62575
    修改内容   : AT2D16941，增加短信任意点回放功能
*******************************************************************************/
#ifndef _SMC_ENTITY_H_
#define _SMC_ENTITY_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

#define SMC_MAX_EXPIRE_TIMES    2

#define SMC_TIMER_TC1M_LENGTH           (20000)

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#define SMS_TPDU_MTI_PS                 (0x24)
#define SMS_TPDU_SCLEN_PS               (0x22)
#define SMS_TPDU_MTI_CS                 (0x28)
#define SMS_TPDU_SCLEN_CS               (0x26)
#define SMT_TP_RD_RETRANS               (0x04)                                                 /* RETRANSFER                               */
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */
#define    SMS_TPDU_SCLEN_LTE_PS        (0x26)
#define    SMS_TPDU_MTI_LTE_PS          (0x28)

/*****************************************************************************
 结构名    : NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8
 结构说明  : SMS中缓存的消息类型

1. 日    期   : 2015年1月27日
   作    者   : s00217060
   修改内容   : 新增枚举
*****************************************************************************/
enum NAS_SMS_HOLD_MSG_TYPE_ENUM
{
    NAS_SMS_HOLD_MSG_GU_MT_RP_ACK       = 0, 
    NAS_SMS_HOLD_MSG_LTE_MT_RP_ACK      = 1,
    NAS_SMS_HOLD_MSG_GU_MO_RP_DATA      = 2, 
    NAS_SMS_HOLD_MSG_LTE_MO_RP_DATA     = 3, 

    NAS_SMS_HOLD_MSG_BUTT
};
typedef VOS_UINT8 NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8;


typedef struct{
    VOS_UINT32                          ulMsgLen ;                                                   /* 消息长度                                 */
    VOS_VOID                            *pMsg;                                                       /* 消息首地址                               */
}SMC_SAVE_MSG_STRU ;
typedef struct{
    HTIMER                              TimerId;                                                  /* Timer Id                                 */
    VOS_UINT8                           ucTimerSta;                                               /* 标识Timer是否有效                        */
    VOS_UINT8                           ucExpireTimes;                                            /* Timer超时次数                            */
    VOS_UINT8                           aucReserved1[2];
}SMC_TIMER_MNG_STRU;


typedef struct
{
    struct{
        VOS_UINT8                       ucState;                                                   /* SMC MO实体的状态                         */
        VOS_UINT8                       ucTi;                                                      /* Transaction ID                           */
        VOS_UINT8                       ucPreTi;                                                   /* 前一个TI值                               */
        VOS_UINT8                       ucMr;                                                      /* Message Reference                        */
        VOS_UINT8                       ucCpAckFlg;    /*该参数表明是否需要向网侧回复CP-ACK消息*/                                            /* 是否发送CP-ACK                           */
        NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8                  enHoldSndMsgType;                           /* SMS中缓存的消息类型 */
        VOS_UINT8                       aucReserved1[2];
        SMC_TIMER_MNG_STRU              TimerInfo;                                          /* 该实体对应的TIMER信息                    */
        SMC_SAVE_MSG_STRU               HoldRcvMsg;                                         /* 缓存接收消息的地址                       */
        SMC_SAVE_MSG_STRU               HoldSndMsg;                                         /* 缓存发送消息的地址                       */
    }SmcMo;
    struct{
          VOS_UINT8                     ucState;                                                 /* SMC MO的状态                             */
          VOS_UINT8                     ucTi;                                                    /* Transaction ID                           */
          VOS_UINT8                     ucMr;                                                    /* Message Reference                        */
          NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8                  enHoldSndMsgType;                       /* SMS中缓存的消息类型 */
          SMC_TIMER_MNG_STRU            TimerInfo;                                        /* 该实体对应的TIMER信息                    */
          SMC_SAVE_MSG_STRU             HoldSndMsg;                                       /* 缓存发送消息的地址                       */
    }SmcMt;
}SMC_ENTITY_STRU;

extern SMC_ENTITY_STRU     g_SmcPsEnt;                                          /* sms ps域的实体声明                       */
extern SMC_ENTITY_STRU     g_SmcCsEnt;                                          /* sms cs域的实体声明                       */

extern VOS_UINT8               g_ucPsServiceStatus;                             /* GMM的PS域是否注册标志                    */
extern VOS_UINT8               g_ucCsRegFlg;                                          /* MM的CS域是否注册标志                    */

extern VOS_UINT8               g_ucSmsMR;
extern VOS_UINT8               g_ucCurSendDomain;
extern VOS_UINT8               g_SndDomain;                                   /* 发送域 */

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

