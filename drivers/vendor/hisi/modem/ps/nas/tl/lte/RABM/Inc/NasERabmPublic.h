/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasERabmPublic.h
  Description     : NasERabmPublic.h header file
  History         :
     1.  杨茜惠 00135146  2008-08-22   Draft Enact
     2.
******************************************************************************/

#ifndef __NASRABMPUBLIC_H__
#define __NASRABMPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "AppRabmInterface.h"
#include  "EsmRabmInterface.h"
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "NasCommPrint.h"
#include  "NasFileId.h"

#if (VOS_OS_VER != VOS_WIN32)
#include  "LPsOm.h"
#endif


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define NAS_ERABM_SUCCESS                       0             /*RABM模块函数返回成功*/
#define NAS_ERABM_FAILURE                       1             /*RABM模块函数返回失败*/
#define NAS_ERABM_MSGILLOGIC                    2             /*不合逻辑的消息*/
#define NAS_ERABM_PARAILLEGAL                   3             /*入口参数非法*/
#define NAS_ERABM_MSGWRONG                      4             /*消息的内容出错*/
#define NAS_ERABM_WAIT_EPSB_ACTT_LENGTH         2000          /*RB建立等待计时器的时间长度*/
/*单板环境:1S*/
#if (VOS_OS_VER != VOS_WIN32)
#define NAS_ERABM_WAIT_RB_REEST_LENGTH         1000          /*发起RB建立定时器的时间长度*/
#define NAS_ERABM_WAIT_DRB_RESUME_LENGTH       40000          /*DRB挂起最长时间40s, 因底层重建时间是30s*/
#define NAS_ERABM_WAIT_TC_FREE_BUFFER_LENGTH   g_ulERabmBufTimerLength /*缓存环回数据包60s*/
#define NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER_LENGTH   g_ulErabmRfRecoveryTimerLength
/*PC环境:5S*/
#else
#define NAS_ERABM_WAIT_RB_REEST_LENGTH         5000          /*发起RB建立定时器的时间长度*/
#define NAS_ERABM_WAIT_DRB_RESUME_LENGTH       5000          /*DRB挂起最长时间,pc环境 5s*/
#define NAS_ERABM_WAIT_TC_FREE_BUFFER_LENGTH   5000          /*缓存环回数据包60s*/
#define NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER_LENGTH   g_ulErabmRfRecoveryTimerLength
#endif


#define NAS_ERABM_MAX_EPSB_ID                   15            /*最大的承载号*/
#define NAS_ERABM_MIN_EPSB_ID                   5             /*最小的承载号*/
#define NAS_ERABM_MAX_EPSB_NUM                  11            /*最大的承载数量*/
#define NAS_ERABM_ILL_EPSB_ID                   0xFF          /*无效的EPSID*/
#define NAS_ERABM_ILL_RB_ID                     0xFF          /*无效的RBID*/
#define NAS_ERABM_NULL                          0
#define NAS_ERABM_SUCC                          0             /*数据发送成功*/
#define NAS_ERABM_FAIL                          1             /*数据发送失败*/
#define NAS_ERABM_MOVEMENT_4_BITS               4
#define NAS_ERABM_MOVEMENT_5_BITS               5
#define NAS_ERABM_MOVEMENT_6_BITS               6
#define NAS_ERABM_MOVEMENT_7_BITS               7
#define NAS_ERABM_MOVEMENT_8_BITS               8
#define NAS_ERABM_MOVEMENT_12_BITS              12
#define NAS_ERABM_MOVEMENT_16_BITS              16
#define NAS_ERABM_MOVEMENT_24_BITS              24
#define NAS_ERABM_FLOW_LABEL_TYPE_MASK          0x000FFFFF
#define NAS_ERABM_IPDATA_IHL_MASK               0x0F
#define NAS_ERABM_IPDATA_HIGH_16_BIT_MASK       0xFFFF0000
#define NAS_ERABM_IPDATA_LOW_16_BIT_MASK        0x0000FFFF
#define NAS_ERABM_SERVICE_TYPE_HIGH_6_BIT_MASK  0xFC
#define NAS_ERABM_IPDATA_HIGH_4_BIT_MASK        0xF0
#define NAS_ERABM_IPDATA_LOW_4_BIT_MASK         0x0F
#define NAS_ERABM_OP_TRUE                       1             /*标识操作位有效*/
#define NAS_ERABM_OP_FALSE                      0             /*标识操作位无效*/
#define NAS_ERABM_PROCTOCOL_UDP                 (0x11)
#define NAS_ERABM_PROCTOCOL_TCP                 (0x06)
#define NAS_ERABM_ACT_EPSB_NUM_ONE              1

#define NAS_ERABM_MAX_SEG_BUFF_ITEM_NUM         (50)
#define NAS_ERABM_IPV4_ADDR_LEN                 (4)
#define NAS_ERABM_IPV6_ADDR_LEN                 (16)
#define NAS_ERABM_IPV6_PREFIX_LEN               (8)
#define NAS_ERABM_PDN_IPV4                      (0x01)              /* 支持IPV4地址*/
#define NAS_ERABM_PDN_IPV6                      (0x02)              /* 支持IPV6地址*/
#define NAS_ERABM_PDN_IPV4_IPV6                 (0x03)              /* 支持IPV4和IPV6地址*/

#define NAS_ERABM_PRINT_LMODESTA(LModeStatus)\
            switch (LModeStatus)\
            {\
                case    NAS_ERABM_L_MODE_STATUS_NORMAL   :\
                    NAS_ERABM_NORM_LOG("RABM L_MODE_NORMAL");\
                    break;\
                case    NAS_ERABM_L_MODE_STATUS_SUSPENDED:\
                    NAS_ERABM_NORM_LOG("RABM L_MODE_SUSPENDED");\
                    break;\
                case    NAS_ERABM_L_MODE_STATUS_BUTT:\
                default   :\
                    NAS_ERABM_NORM_LOG("RABM UKNOWN L MODE STATUS");\
                    break;\
            }


#ifdef PS_ITT_PC_TEST
#define NAS_ERABM_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_ERABM_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#else
#define NAS_ERABM_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_ERABM_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_ERABM_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_ERABM_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_ERABM_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_ERABM_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)

#endif

#define NAS_ERABM_GET_MSG_LENGTH(pMsg)             ((pMsg)->ulLength)
#define NAS_ERABM_GET_RRC_MSG_ENTITY(pMsg)             ((VOS_VOID*)&((pMsg)->enMsgId))
#define NAS_ERABM_GET_MSG_ENTITY(pMsg)             ((VOS_VOID*)&((pMsg)->ulMsgId))


/*封装写SM消息头的宏*/
#define NAS_ERABM_WRITE_ESM_MSG_HEAD(pstMsg, ulEsmMsgID)\
                    (pstMsg)->ulMsgId = (ulEsmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_ESM;

/*封装写EMM消息头的宏*/
#define NAS_ERABM_WRITE_EMM_MSG_HEAD(pstMsg, ulEmmMsgID)\
                    (pstMsg)->ulMsgId   = (ulEmmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;

/*封装写RRC消息头的宏*/
#define NAS_ERABM_WRITE_RRC_MSG_HEAD(pstMsg, ulRrcMsgID)\
                    (pstMsg)->enMsgId   = (ulRrcMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_ERRC;

/*封装写APP消息头的宏*/
#define NAS_ERABM_WRITE_APP_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_APP;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

/*封装APP写RABM消息头的宏*/
#define NAS_ERABM_APP_WRITE_RABM_MSG_HEAD(pstMsg, ulAppMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulAppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_APP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_RABM;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

/*封装写IP消息头的宏*/
#define NAS_ERABM_WRITE_IP_MSG_HEAD(pstMsg, ulIpMsgID)\
                    (pstMsg)->ulMsgId = (ulIpMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_IP;

#define NAS_ERABM_WRITE_TC_MSG_HEAD(pstMsg, ulIpMsgID)\
                    (pstMsg)->ulMsgId = (ulIpMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_TC;

/*封装写SM消息头的宏*/
#define NAS_ERABM_WRITE_CDS_MSG_HEAD(pstMsg, ulEsmMsgID)\
                    (pstMsg)->ulMsgId = (ulEsmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = UEPS_PID_CDS;


/* 内存拷贝宏定义 */


#define NAS_ERABM_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))


#if (VOS_OS_VER == VOS_WIN32)

#define NAS_ERABM_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ERABM_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ERABM_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
#define NAS_ERABM_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength )\
        (VOS_VOID)NAS_ERABM_SecuMemCpy(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, (__LINE__), (THIS_FILE_ID) )

#define NAS_ERABM_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength )   \
        (VOS_VOID)TLPS_MEM_SET_S((pDestBuffer), (ulMaxDest), (ucData), (ulLength), (__LINE__), (THIS_FILE_ID))

#define NAS_ERABM_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_MOVE_S( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#endif

#define NAS_ERABM_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_RABM) , (ulLen))
/* 发送消息 */
#define NAS_ERABM_SND_MSG(pMsg)\
    {\
        NAS_ERABM_PrintRabmSendMsg((const PS_MSG_HEADER_STRU * )pMsg,NAS_COMM_GET_ESM_PRINT_BUF());\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_RABM) , (pMsg)))\
        {\
            NAS_ERABM_ERR_LOG("NAS_ERABM_SND_MSG:Msg Snd Err!");\
        }\
    }

/*内存释放*/
#if (VOS_OS_VER != VOS_WIN32)
#define NAS_ERABM_MEM_FREE(pAddr)\
    {\
        if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_RABM), (pAddr)))\
        {\
            NAS_ERABM_ERR_LOG("NAS_ERABM_MEM_FREE  ERR!!");\
        }\
    }
#else
#define NAS_ERABM_MEM_FREE(pAddr) PS_MEM_FREE_ALL_CHECK((PS_PID_RABM), (pAddr));
#endif

/*内存动态分配*/
#define NAS_ERABM_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_RABM) , (ulSize))
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*承载上下文状态*/
enum NAS_ERABM_EPSB_STATE_ENUM
{
    NAS_ERABM_EPSB_INACTIVE    =       0,               /*去激活状态*/
    NAS_ERABM_EPSB_ACTIVE,                              /*激活状态*/

    NAS_ERABM_EPSB_BUTT
};
typedef VOS_UINT8  NAS_ERABM_EPSB_STATE_ENUM_UINT8;

/*RB的连接状态*/
enum NAS_ERABM_RB_STATE_ENUM
{
    NAS_ERABM_RB_CONNECTED      =      0,               /*RB为连接态*/
    NAS_ERABM_RB_DISCONNECTED,                          /*RB为非连接态*/
    NAS_ERABM_RB_SUSPENDED,                             /*RB为暂停接态*/

    NAS_ERABM_RB_STATE_BUTT
};
typedef VOS_UINT8  NAS_ERABM_RB_STATE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : NAS_ERABM_TIMER_STATE_ENUM
    枚举说明  : 定时器的状态:正在运行,停止
*****************************************************************************/
enum    NAS_ERABM_TIMER_STATE_ENUM
{
    NAS_ERABM_TIMER_STATE_RUNNING                = 0x00,
    NAS_ERABM_TIMER_STATE_STOPED,

    NAS_ERABM_TIMER_STATE_BUTT
};
typedef VOS_UINT32   NAS_ERABM_TIMER_STATE_ENUM_UINT32;

/*标识定时器的名字*/
enum NAS_ERABM_TIMER_NAME_ENUM
{
    NAS_ERABM_WAIT_EPSB_ACT_TIMER        =      0,     /*等待EPS承载激活定时器*/
    NAS_ERABM_WAIT_RB_REEST_TIMER,                     /*等待RB建立定时器*/
    NAS_ERABM_WAIT_RB_RESUME_TIMER,                    /*等待RB恢复定时器*/
    NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER,               /*环回缓存定时器*/
    NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER,              /* RF恢复RB重建定时器 */

    NAS_NAS_ERABM_TIMER_NAME_BUTT
};
typedef VOS_UINT8  NAS_ERABM_TIMER_NAME_ENUM_UINT8;
enum NAS_ERABM_OM_LOG_MSG_ENUM
{
    NAS_ERABM_OM_LOG_TIMER_MIN                  = PS_MSG_ID_ERABM_TO_ERABM_OM_BASE,
    NAS_ERABM_OM_LOG_TIMER_MAX                  = PS_MSG_ID_ERABM_TO_ERABM_OM_BASE + NAS_NAS_ERABM_TIMER_NAME_BUTT,
    ID_NAS_ERABM_OM_LOG_IPF_FILTER_INFO         = NAS_ERABM_OM_LOG_TIMER_MAX + 0x1,
    ID_NAS_ERABM_OM_LOG_CDS_FILTER_INFO         = NAS_ERABM_OM_LOG_TIMER_MAX + 0x2
};
typedef VOS_UINT32 NAS_ERABM_OM_LOG_MSG_ENUM_UINT32;


/*设定RABM等待EPS承载激活的标识*/
enum NAS_ERABM_WAIT_EPSB_ACT_ENUM
{
    NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG = 0,              /*RABM没有等待EPSB激活消息*/
    NAS_ERABM_WAIT_EPSB_ACT_MSG,                      /*RABM等待EPSB激活消息*/

    NAS_ERABM_WAIT_EPSB_ACT_BUTT
};
typedef VOS_UINT8 NAS_ERABM_WAIT_EPSB_ACT_ENUM_UINT8;

/* L模状态 */
enum NAS_ERABM_L_MODE_STATUS_ENUM
{
    NAS_ERABM_L_MODE_STATUS_NORMAL        = 0,                /*正常态*/
    NAS_ERABM_L_MODE_STATUS_SUSPENDED     = 1,                /*挂起态*/

    NAS_ERABM_L_MODE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_ERABM_L_MODE_STATUS_ENUM_UINT8;


/*设定用于记录给SERVICE流程状态，等RB建立后，给EMM发送停止SERVICE REQ的标识*/
enum NAS_ERABM_SERVICE_STATE_ENUM
{
    NAS_ERABM_SERVICE_STATE_TERMIN = 0,              /*SERVICE流程结束*/
    NAS_ERABM_SERVICE_STATE_INIT,                    /*SERVICE流程启动*/

    NAS_ERABM_SERVICE_STATE_BUTT
};
typedef VOS_UINT32 NAS_ERABM_SERVICE_STATE_ENUM_UINT32;

/* RABM工作模式 */
enum NAS_ERABM_MODE_TYPE_ENUM
{
    NAS_ERABM_MODE_TYPE_NORMAL           =      0,        /*正常模式*/
    NAS_ERABM_MODE_TYPE_LB               =      1,        /*环回模式*/

    NAS_ERABM_MODE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_ERABM_MODE_TYPE_ENUM_UINT32;


/*****************************************************************************
    枚举名    : NAS_TIMER_RUN_STA_ENUM
    枚举说明  : 定时器的状态:正在运行,停止
*****************************************************************************/
enum    NAS_ERABM_TIMER_RUN_STA_ENUM
{
    NAS_ERABM_TIMER_RUNNING                = 0x00,
    NAS_ERABM_TIMER_STOPED,
    NAS_ERABM_TIMER_INVALID,

    NAS_ERABM_TIMER_BUTT
};
typedef VOS_UINT32   NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

typedef struct
{
    HTIMER                               stHTimer;            /* vos分配的Timer Id*/
    NAS_ERABM_TIMER_NAME_ENUM_UINT8       enName;              /* 定时器名*/
    VOS_UINT8                            ucExpireTimes;       /* Timer超时次数  */
    VOS_UINT8                            aucReserve1[2];      /* 四字节对齐，保留*/
}NAS_ERABM_START_TIMER_STRU; /*定时器使用的数据结构*/

typedef struct
{
    VOS_UINT32                          ulEpsbId;            /*对应EPS承载ID*/
    VOS_UINT32                          ulRbId;              /*对应RBID*/
    NAS_ERABM_EPSB_STATE_ENUM_UINT8      enContextState;      /*EPSB上下文的状态*/
    NAS_ERABM_RB_STATE_ENUM_UINT8        enRbState;           /*RB的连接状态*/
    VOS_UINT8                           aucReserve1[2];      /* 四字节对齐，保留*/
    VOS_UINT32                          ulTftPfNum;
    ESM_ERABM_TFT_PF_STRU                astTftPfInfo[ESM_ERABM_MAX_PF_NUM_IN_BEARER];
    APP_ESM_IP_ADDR_STRU                stPdnAddr;
    ESM_ERABM_BEARER_TYPE_ENUM_UINT32   enBearerCntxtType;  /* 上下文对应承载的类型 */
    VOS_UINT32                          ulLinkedEpsbId;     /*与此承载关联的EPS承载ID*/
    VOS_UINT8                           ucQCI;              /* 承载的QCI */
    VOS_UINT8                           ucRev[3];
}NAS_ERABM_INFO_STRU;    /*承载数据结构*/

typedef struct
{
    VOS_UINT32                           ulRbId;              /*对应RBID*/
    VOS_UINT32                           ulEpsbId;            /*对应EPS承载ID*/
}NAS_ERABM_RB_SETUP_REQ_STRU;    /*等待EPSB激活消息数据结构*/


typedef struct
{
    NAS_ERABM_WAIT_EPSB_ACT_ENUM_UINT8    enWaitEpsbActSign;   /*设定一个等待EPS承载激活的标识*/
    NAS_ERABM_L_MODE_STATUS_ENUM_UINT8    enLModeStatus;      /* L模状态 */
    VOS_UINT8                            aucReserve1[2];      /* 四字节对齐，保留*/
    VOS_UINT32                           ulRbNum;             /*RRC请求建立RB的个数*/
    VOS_UINT32                           ulOnlyActiveAndNoUlTftEpsbId; /*唯一激活且没有上行TFT的承载号，同时该变量也
                                                                       标志是否只有一条承载激活且没有上行TFT*/
    NAS_ERABM_START_TIMER_STRU            astTimerInfo[NAS_NAS_ERABM_TIMER_NAME_BUTT];       /*定时器使用信息*/
    NAS_ERABM_INFO_STRU                   astRabmInfo[NAS_ERABM_MAX_EPSB_NUM];
    NAS_ERABM_RB_SETUP_REQ_STRU           astRabmRbSetup[NAS_ERABM_MAX_EPSB_NUM];
    APP_ERABM_DATA_TRANS_INFO_STRU        stAppRabmDataInfo;
    NAS_ERABM_MODE_TYPE_ENUM_UINT32       enMode;                /* 0:环回模式，1:正常模式 */
}NAS_ERABM_ENTITY_STRU;/*RABM实体数据结构*/


/*****************************************************************************
 Function Name   : NAS_ERABM_EHRPD_ENTITY_STRU
 Description     : EHRPD承载管理实体，用于1XCL互操作管理EHRPD同步过来的承载信息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
typedef struct
{
    /* EHRPD实体信息 */
    NAS_ERABM_INFO_STRU                 astEhrpdBearerInfo[NAS_ERABM_MAX_EPSB_NUM];

    /* 数据包统计，统计C->L变换时每条承载上缓存的数据包个数 */
    VOS_UINT32                          aulStorePktNum[NAS_ERABM_MAX_EPSB_NUM];
}NAS_ERABM_EHRPD_ENTITY_STRU;


/*****************************************************************************
 结构名    : NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4分片包信息记录缓存结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIdentifier;
    VOS_UINT8                           aucSrcIpV4Addr[NAS_ERABM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucDesIpV4Addr[NAS_ERABM_IPV4_ADDR_LEN];
    VOS_UINT8                           ucBearerId;
    VOS_UINT8                           aucReserved[3];
}NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU;

/*****************************************************************************
 结构名    : NAS_ERABM_IPV4_SEGMENT_BUFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4分片包信息缓存结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                           ulItemNum;
    NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU    astErabmSegBuff[NAS_ERABM_MAX_SEG_BUFF_ITEM_NUM];
}NAS_ERABM_IPV4_SEGMENT_BUFF_STRU;


/*****************************************************************************
 结构名    : NAS_ERABM_TIMER_INFO_STRU
 结构说明  : log出ERABM定时器运行情况
 1.日    期   : 2012年12月03日
   作    者   : n00181501
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32      enTimerStatus;   /* 定时器状态*/

    NAS_ERABM_TIMER_NAME_ENUM_UINT8          enTimerId;       /* 定时器ID*/
    VOS_UINT8                                usRsv[3];
    VOS_UINT32                               ulTimerRemainLen;/* 定时器的时长 */
}NAS_ERABM_TIMER_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern NAS_ERABM_EHRPD_ENTITY_STRU      g_stNasERabmEhrpdEntity;   /*RABM的EHRPD承载管理实体声明*/

#define NAS_ERABM_GetEhrpdBearerIdInfoAddr(ulEhrpdBearerId)   (&g_stNasERabmEhrpdEntity.astEhrpdBearerInfo[ulEhrpdBearerId - NAS_ERABM_MIN_EPSB_ID])
#define NAS_ERABM_GetEhrpdBearerStorePktNum(ulEhrpdBearerId)  (g_stNasERabmEhrpdEntity.aulStorePktNum[ulEhrpdBearerId - NAS_ERABM_MIN_EPSB_ID])
#define NAS_ERABM_GetEhrpdPdnAddr(ulEhrpdBearerId)            (&((NAS_ERABM_GetEhrpdBearerIdInfoAddr(ulEhrpdBearerId))->stPdnAddr))
#define NAS_ERABM_GetEhrpdBearerStateInfo(ulEhrpdBearerId)    ((NAS_ERABM_GetEhrpdBearerIdInfoAddr(ulEhrpdBearerId))->enContextState)
#endif

/*RABM实体信息*/
extern NAS_ERABM_ENTITY_STRU                        g_stNasERabmEntity;
extern NAS_ERABM_ENTITY_STRU                       *pg_stNasERabmEntity;
#define NAS_ERABM_Entity()                         (pg_stNasERabmEntity)

/*得到定时器的信息*/
#define NAS_ERABM_GetRbTimer(ucTimeIndex)          (((ucTimeIndex) < NAS_NAS_ERABM_TIMER_NAME_BUTT)?(&(NAS_ERABM_Entity()->astTimerInfo[ucTimeIndex])): VOS_NULL_PTR)

/*把RB建立请求信息保存在RB建立临时表*/
#define NAS_ERABM_SetRbSetupRbIdInfo(ulRbNum,ulRId)      ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulRbId = (ulRId))
#define NAS_ERABM_SetRbSetupEpsbIdInfo(ulRbNum,ulEpsId)    ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulEpsbId = (ulEpsId))

/*得到RB建立临时表信息*/
#define NAS_ERABM_GetRbSetupRbIdInfo(ulRbNum)      ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulRbId)
#define NAS_ERABM_GetRbSetupEpsbIdInfo(ulRbNum)    ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulEpsbId)
#define NAS_ERABM_GetRbNumInfo()                   ((NAS_ERABM_Entity()->ulRbNum))

/*记录请求建立的RB数目*/
#define NAS_ERABM_SetRbNumInfo(ulRbSetupReqNum)                   ((NAS_ERABM_Entity()->ulRbNum) = (ulRbSetupReqNum))

/*唯一激活且没有TFT的承载号*/
#define NAS_ERABM_GetOnlyActiveAndNoUlTftEpsbId()      ((NAS_ERABM_Entity()->ulOnlyActiveAndNoUlTftEpsbId))
#define NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(ulEpsbId)      ((NAS_ERABM_Entity()->ulOnlyActiveAndNoUlTftEpsbId) = (ulEpsbId) )

#define NAS_ERABM_SetEpsbBearerType(ulEpsbIdCnt, enBearerCntxtType1)      (((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enBearerCntxtType) = (enBearerCntxtType1))
#define NAS_ERABM_SetEpsbLinkedEpsbId(ulEpsbIdCnt, ulLinkedEpsbId1)       (((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulLinkedEpsbId) = (ulLinkedEpsbId1))
#define NAS_ERABM_SetEpsbQCI(ulEpsbIdCnt, ucNwQCI)       (((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ucQCI) = (ucNwQCI))


/*记录EPS承载激活表信息*/
#define NAS_ERABM_SetEpsbTftPfNum(ulEpsbIdCnt,ulEpsbTftPfNum)   ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulTftPfNum = (ulEpsbTftPfNum))
#define NAS_ERABM_SetEpsbIdInfo(ulEpsbIdCnt,ulEpsId)       ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulEpsbId = (ulEpsId))
#define NAS_ERABM_SetEpsbRbIdInfo(ulEpsbIdCnt,ulRId)     ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulRbId = (ulRId))
#define NAS_ERABM_SetEpsbStateInfo(ulEpsbIdCnt,enCntxtState)    ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enContextState = (enCntxtState))
#define NAS_ERABM_SetRbStateInfo(ulEpsbIdCnt,enRState)      ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enRbState = (enRState))
#define NAS_ERABM_GetEpsbBearerType(ulEpsbIdCnt)         ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enBearerCntxtType)
#define NAS_ERABM_GetEpsbLinkedEpsbId(ulEpsbIdCnt)       ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulLinkedEpsbId)
#define NAS_ERABM_GetEpsbQCI(ulEpsbIdCnt)            ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ucQCI)

/*得到EPS承载激活表信息*/
#define NAS_ERABM_GetEpsbTftPfNum(ulEpsbIdCnt)   ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulTftPfNum)
#define NAS_ERABM_GetEpsbIdInfo(ulEpsbIdCnt)       ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulEpsbId)
#define NAS_ERABM_GetEpsbRbIdInfo(ulEpsbIdCnt)     ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulRbId)
#define NAS_ERABM_GetEpsbStateInfo(ulEpsbIdCnt)    ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enContextState)
#define NAS_ERABM_GetRbStateInfo(ulEpsbIdCnt)      ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enRbState)
#define NAS_ERABM_GetEpsbTftAddr(ulEpsbIdCnt,ulTftPfCnt)   (&((NAS_ERABM_Entity())->astRabmInfo[(ulEpsbIdCnt)-NAS_ERABM_MIN_EPSB_ID].astTftPfInfo[(ulTftPfCnt)]))
#define NAS_ERABM_GetEpsbPdnAddr(ulEpsbIdCnt)      (&(NAS_ERABM_Entity()->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].stPdnAddr))


/*等待EPS承载激活标识的相关操作*/
#define NAS_ERABM_GetWaitEpsbActSign()             ((NAS_ERABM_Entity())->enWaitEpsbActSign)
#define NAS_ERABM_SetWaitEpsBActSign(ucWaitEpsbActMsgStatus)\
                                                  ((NAS_ERABM_Entity())->enWaitEpsbActSign = (ucWaitEpsbActMsgStatus))


/* RABM模式的相关操作 */
#define NAS_ERABM_GetMode()               ((NAS_ERABM_Entity())->enMode)
#define NAS_ERABM_SetMode(enModeType)\
                                                  ((NAS_ERABM_Entity())->enMode = (enModeType))

/*设置RABM灌包相关信息*/
#define   NAS_ERABM_StAppDataBitIpv4(bOpIpv4)\
                   ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv4 = bOpIpv4)

#define   NAS_ERABM_StAppDataBitIpv6(bOpIpv6)\
                   ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv6 = bOpIpv6)

#define   NAS_ERABM_SetAppDataRmtPortIpv4(RmtPortIpv4)\
     ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv4SingleRmtPort = RmtPortIpv4)

#define   NAS_ERABM_SetAppDataRmtPortIpv6(RmtPortIpv6)\
     ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv6SingleRmtPort = RmtPortIpv6)

#define   NAS_ERABM_SetAppDataOperateType(SetOpType)\
               ((NAS_ERABM_Entity()->stAppRabmDataInfo).enSetOpType = SetOpType)


/*获取RABM灌包相关信息*/
#define   NAS_ERABM_GetAppDataInfoAddr()         (&(NAS_ERABM_Entity()->stAppRabmDataInfo))
#define   NAS_ERABM_GetAppDataBitIpv4()          ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv4)
#define   NAS_ERABM_GetAppDataBitIpv6()          ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv6)
#define   NAS_ERABM_GetAppDataRmtPortIpv4()      ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv4SingleRmtPort)
#define   NAS_ERABM_GetAppDataRmtPortIpv6()      ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv6SingleRmtPort)
#define   NAS_ERABM_GetAppDataOperateType()      ((NAS_ERABM_Entity()->stAppRabmDataInfo).enSetOpType)
#define   NAS_ERABM_GetAppDataRemoteIpv4Addr()   ((NAS_ERABM_Entity()->stAppRabmDataInfo).aucRmtIpv4Address)
#define   NAS_ERABM_GetAppDataRemoteIpv6Addr()   ((NAS_ERABM_Entity()->stAppRabmDataInfo).aucRmtIpv6Address)

/*extern NAS_ERABM_SEGMENT_DATA_INFO_ARRAY_STRU    g_stERabmSegDataInfo;
#define NAS_ERABM_GetSegDataInfoArrayAddr()      (&g_stERabmSegDataInfo)
#define NAS_ERABM_GetSegDataInfoAddr(ulIndex)    (&((NAS_ERABM_GetSegDataInfoArrayAddr())->astRabmSegDataInfo[ulIndex]))
#define NAS_ERABM_GetSegDataInfoNum()            ((NAS_ERABM_GetSegDataInfoArrayAddr())->ulSegDataInfoNum)
#define NAS_ERABM_AddSelfSegDataInfoNum()        ((NAS_ERABM_GetSegDataInfoArrayAddr())->ulSegDataInfoNum++)*/

extern NAS_ERABM_IPV4_SEGMENT_BUFF_STRU          g_stErabmIpv4SegBuff;
#define NAS_ERABM_GetIpv4SegBuffAddr()           (&g_stErabmIpv4SegBuff)
#define NAS_ERABM_GetIpv4SegBuffItemAddr(ulIndex) (&((NAS_ERABM_GetIpv4SegBuffAddr())->astErabmSegBuff[ulIndex]))
#define NAS_ERABM_GetIpv4SegBuffItemNum()        ((NAS_ERABM_GetIpv4SegBuffAddr())->ulItemNum)
#define NAS_ERABM_AddSelfIpv4SegBuffItemNum()    ((NAS_ERABM_GetIpv4SegBuffAddr())->ulItemNum++)


/*上行数据阻塞标志*/
extern EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32    g_enERabmUlDataPending;

#define   NAS_ERABM_GetUpDataPending()               (g_enERabmUlDataPending)
#define   NAS_ERABM_SetUpDataPending(UpDataPending)  ((g_enERabmUlDataPending) = (UpDataPending))

#define NAS_ERABM_GetLModeStatus()\
                  ((NAS_ERABM_Entity())->enLModeStatus)

#define NAS_ERABM_SetLModeStatus(ucLModeStatus)\
            {\
                 NAS_ERABM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
                 NAS_ERABM_NORM_LOG("RABM L Mode Status change----");\
                 NAS_ERABM_PRINT_LMODESTA(NAS_ERABM_GetLModeStatus());\
                 NAS_ERABM_NORM_LOG("==>>");\
                 (NAS_ERABM_Entity())->enLModeStatus = (ucLModeStatus);\
                 NAS_ERABM_PRINT_LMODESTA(ucLModeStatus);\
                 NAS_ERABM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
            }
extern NAS_ERABM_SERVICE_STATE_ENUM_UINT32 g_enERabmSrState;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID NAS_ERABM_SndOmErabmTimerStatus
(
    NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32 enTimerStatus,
    NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerId,
    VOS_UINT32 ulTimerRemainLen
);
extern VOS_VOID NAS_LMM_LogIsDataPending
(
    VOS_UINT32  ulRslt
);

extern VOS_INT32 NAS_ERABM_SecuMemCpy
(
    VOS_VOID        * pDst,
    VOS_UINT32      ulMaxBuffer,
    const VOS_VOID  * pSrc,
    VOS_UINT32      ulLength,
    VOS_UINT32      ulLineNO,
    VOS_UINT32      ulFileID
);


/*****************************************************************************
  9 OTHERS
*****************************************************************************/








#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasERabmPublic.h */

