
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

