
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

#define SMS_TPDU_MTI_PS                 (0x24)
#define SMS_TPDU_SCLEN_PS               (0x22)
#define SMS_TPDU_MTI_CS                 (0x28)
#define SMS_TPDU_SCLEN_CS               (0x26)
#define SMT_TP_RD_RETRANS               (0x04)                                                 /* RETRANSFER                               */
#define    SMS_TPDU_SCLEN_LTE_PS        (0x26)
#define    SMS_TPDU_MTI_LTE_PS          (0x28)


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

