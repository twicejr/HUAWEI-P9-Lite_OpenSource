/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmStru.h
  Description : SM数据结构头文件
  History     :
      1.  张志勇      2003.12.04   新版作成
      2.  张志勇   2005.01.08   移植修改
      3.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/
#ifndef _SM_STRU_INTERFACE_H_
#define _SM_STRU_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
#define SM_MAX_EXPIRE_TIMES     5

#define SM_T3380_LENGTH         30000

#define SM_T3381_LENGTH         8000
#define SM_T3390_LENGTH         8000
#define SM_T0001_LENGTH         80000
#define SM_T0002_LENGTH         30000
#define SM_T0003_LENGTH         8000

/* TIMER TYPE DEFINE */
#define SM_REGISTER_TIMER_ID    0xff
#define SM_TIMER_TYPE_T3380     0                                               /* T3380                                    */
#define SM_TIMER_TYPE_T3381     1                                               /* T3381                                    */
#define SM_TIMER_TYPE_T3390     2                                               /* T3390                                    */
#define SM_TIMER_TYPE_T0001     3                                               /* Register保护定时器                       */
#define SM_TIMER_TYPE_T0002     4                                               /* network发起的PDPcontext active保护定时器 */
#define SM_TIMER_TYPE_T0003     5                                               /* network发起的PDPcontext modify保护定时器 */

/*ucRegisterFlg */
#define SM_PS_NOTREGISTER       0                                               /* GMM的PS域没有注册                        */
#define SM_PS_REGISTERING       1                                               /* GMM的PS域正在注册                        */
#define SM_PS_REGISTERED        2                                               /* GMM的PS域已经注册                        */

/* state */
#define SM_PDP_INACTIVE             0
#define SM_PDP_ACTIVE_PENDING       1
#define SM_PDP_INACTIVE_PENDING     2
#define SM_PDP_MODIFY_PENDING       3
#define SM_PDP_ACTIVE               4
#define SM_PDP_NW_MODIFY            6

/* Ti Flg */
#define SM_TI_NET_ORG                   (0)
#define SM_TI_MS_ORG                    (1)

#if (FEATURE_ON == FEATURE_IPV6)
#define SM_MAX_IP_ADDR_LEN              (22)                                              /*空口消息，ip地址的长度 */
#else
#define SM_MAX_IP_ADDR_LEN              (18)
#endif

#define NAS_SM_MAX_QOS_LEN              (16)
#define NAS_SM_MAX_APN_LEN              (100)

/*****************************************************************************
 结构名  : NAS_SM_GMM_ERR_CODE_MAP_STRU
 结构说明: SM错误码与GMM错误码映射结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    SM_TAF_CAUSE_ENUM_UINT16            enSmCuase;
    GMM_SM_CAUSE_ENUM_UINT16            enGmmCause;

} NAS_SM_GMM_ERR_CODE_MAP_STRU;

/*****************************************************************************
 结构名  : SM_QOS_STRU
 结构说明: SM实体保存的QOS结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改成员
*****************************************************************************/
typedef struct{
    VOS_UINT32                          ulQosLength;                            /* Qos的数据大小 */
    VOS_UINT8                           aucQosValue[NAS_SM_MAX_QOS_LEN];        /* Qos数据首地址 */
} SM_QOS_STRU;


typedef struct{
    HTIMER        TimerId;                                                    /* vos分配的Timer Id                        */
    VOS_UINT8           ucExpireTimes;                                              /* Timer超时次数                            */
    VOS_UINT8           ucTimerType;                                                /* Timer类型                                */
#define SM_TIMER_STA_ON     1
#define SM_TIMER_STA_OFF    0
    VOS_UINT8           ucTimerStaFlg;
}SM_TIMER_MNG_STRU;

/*****************************************************************************
 结构名  : SM_PDP_APN_STRU
 结构说明: SM实体保存的APN结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改成员
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulApnLength;                        /* APN的数据大小   */
    VOS_UINT8                               aucApnValue[NAS_SM_MAX_APN_LEN];    /* APN的数据首地址 */
} SM_PDP_APN_STRU;

typedef struct{
    VOS_UINT32       ulAddrLength;                                              /* ADDR的数据大小 */
    VOS_UINT8        aucAddrValue[SM_MAX_IP_ADDR_LEN];                                             /* ADDR的数据首地址*/
} SM_PDP_ADDR_STRU;

typedef struct
{
    VOS_UINT8                           ucTi;               /* Transaction ID                           */
    VOS_UINT8                           ucCr;               /* Call Reference                           */
    VOS_UINT8                           ucTiFlg;            /* TI标志，0：网侧形成；1：MS形成           */
    VOS_UINT8                           ucState;            /* PDP CONTEXT的状态                        */
    VOS_UINT8                           ucRabId;            /* RAB ID                                   */

    VOS_UINT8                           ucAddrIndex;        /* 该实体在PDP ADDRESS列表中的位置          */

    VOS_UINT8                           ucRadioPri;         /* Radio Priority                           */
    SM_TIMER_MNG_STRU                   TimerInfo;          /* 该实体对应的实体信息                     */
    SM_QOS_STRU                         QoS;                /* 本实体对应的QoS                          */
    VOS_UINT32                          ulHoldLen;          /* 缓存消息大小                             */
    VOS_VOID                           *pHoldSndMsg;        /* 缓存消息的地址                           */
} NAS_SM_PDP_CONTEXT_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucNsapiCnt;                             /* 使用此APN、PDP ADDR信息的NSAPI个数       */
    VOS_UINT8                           aucNsapi[SM_MAX_NSAPI_NUM];             /* NSAPI的列表                              */
    SM_PDP_APN_STRU                     PdpApn;                                 /* APN VALUE                                */
    SM_PDP_ADDR_STRU                    PdpAddrInfo;                            /* PDP地址信息                              */
} NAS_SM_PDP_ADDR_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucRegisterFlg;      /* GMM的PS域是否注册标志                    */
    VOS_UINT8                           ucRegTimerSta;      /* 注册Timer state                          */
    HTIMER                              ulRegTimerID;       /* 注册Timer ID                             */

    struct{
        VOS_VOID                       *pHoldRcvMsg;        /* GMM未注册时，缓存接收的TAF消息           */
    }aHoldMsg[SM_MAX_NSAPI_NUM];

    NAS_SM_PDP_CONTEXT_INFO_STRU        aPdpCntxtList [SM_MAX_NSAPI_NUM];
    VOS_UINT32                          ulSessionBeginFlg;  /* Begin Session标识                        */
}SM_ENTITY_STRU;


typedef struct
{
    VOS_UINT16                          usPdpAddrFlg;       /* PDP address and apn的有效标志            */
    NAS_SM_PDP_ADDR_INFO_STRU           aPdpAddrlist[SM_MAX_NSAPI_NUM];
}SM_PDP_ADDR_AND_APN_STRU;

typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  *pOcts;
}SM_OCT_VARY_STRU;

typedef struct{
    VOS_UINT8    ucLen;                                                             /* IE的长度                                 */
    VOS_UINT8    *pValue;                                                           /* IE的首地址                               */
}SM_MSG_IE_COMMON_STRU;

typedef struct
{
    VOS_UINT8                           ucTiFlg;
    VOS_UINT8                           ucTi;               /* Transaction identifier         */
    VOS_UINT8                           ucRadioPri;         /* Radio priority                 */
    VOS_UINT8                           SmCause;            /* SM Cause                       */
    VOS_UINT8                           ucTdi;              /* Tear down indicator            */
    SM_MSG_IE_COMMON_STRU               PdpAddr;            /* Packet data protocol address   */
    SM_MSG_IE_COMMON_STRU               Apn;                /* Access point name              */
    SM_MSG_IE_COMMON_STRU               Qos;                /* Negotiated QoS                 */
    SM_MSG_IE_COMMON_STRU               ProCnfgOpt;         /* Protocol configuration options */
    SM_MSG_IE_COMMON_STRU               Pfi;                /* Packet Flow Identifier         */
#if (FEATURE_ON == FEATURE_IPV6)
    SM_MSG_IE_COMMON_STRU               stSmCauseTwo;       /* SM cause 2                     */
#endif
}SM_NW_MSG_STRU;

#define EVT_NAS_SM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* 为PC工程回放定义的消息 */

/*****************************************************************************
 Structure      : NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC回放工程，存储所有SM相关的全局变量
 Message origin :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                    pc_g_ucTiExt;                                               /* 记录ti是否有扩展位                       */
    VOS_UINT8                    pc_g_TiMapToNsapi[256];                                     /* TI和NSAPI的映射关系                      */
    VOS_UINT8                    pc_g_CrMapToNsapi[256];                                     /* CR和NSAPI的映射关系                      */
    VOS_UINT8                    pc_g_aucSapi[SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET][2];
    SM_ENTITY_STRU               pc_g_SmEntity;                                              /* sm实体定义                               */
    SM_PDP_ADDR_AND_APN_STRU     pc_g_SmPdpAddrApn;                                          /* 保存pdp address和apn                     */
} NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC回放工程，所有SM相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                           usMsgID;
    VOS_UINT16                           usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_SM_SDT_MSG_ST;


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
