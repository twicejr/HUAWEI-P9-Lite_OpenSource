


#ifndef __NASLCSPUBLIC_H__
#define __NASLCSPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "PsCommonDef.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"
#include    "TafLcsInterface.h"
#include    "NasLcsTimerMsgProc.h"
#include    "PsCommonDef.h"
#include    "NasLcsDecode.h"
#include    "LmmLcsInterface.h"

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
  2 Macro
*****************************************************************************/
#define NAS_LCS_NULL                            0
#define NAS_LCS_NULL_PTR                        VOS_NULL_PTR
#define NAS_LCS_MAX_ENTITY_NUM                  (5)
#define NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN        (2)
#define NAS_LCS_MT_LR_ENTITY_INDEX_END          (4)
#define NAS_LCS_MO_LR_TAF_INDEX                 (1)
#define NAS_LCS_MO_LR_LPP_INDEX                 (0)
#define NAS_LCS_SUCC                            (0)
#define NAS_LCS_FAIL                            (1)
#define NAS_LCS_MAX_HANDLE_ID                   (255)
#define NAS_LCS_LEN_VOS_MSG_HEADER              (20)
#define NAS_LCS_MAX_LPP_MSG_LEN                 (235)
#define NAS_LCS_MAX_INVOKE_ID                   (255)
#define NAS_LCS_MAX_UPLINDK_LCS_MSG             (512)
#define NAS_LCS_MIN_SND_MSG_LEN                 (4)
#define NAS_LCS_MIN_MO_TI_VAULE                 (8)
#define NAS_LCS_MAX_MO_TI_VAULE                 (14)
#define NAS_LCS_TI_OFFSET                       (8)
#define NAS_LCS_TAF_MO_LR_TI                    (14)
#define NAS_LCS_LPP_MO_LR_TI                    (13)
#define NAS_LCS_UE_NW_CAP_LEN_INCLUDE_LCS       (5)
#define NAS_LCS_LPP_CAP_INDEX_UE_NW_CAP         (4)
#define NAS_LCS_CLASSMARK2_LEN_INCLUDE_LCS      (3)
#define NAS_LCS_WAIT_NW_RSP_TIMER_DFT_LEN       (180)

#define NAS_LCS_MSG_HIGH_1_BIT                  (0x80)
#define NAS_LCS_MSG_HIGH_2_BIT                  (0xC0)
#define NAS_LCS_MSG_HIGH_3_BIT                  (0xE0)
#define NAS_LCS_MSG_HIGH_4_BIT                  (0xF0)
#define NAS_LCS_MSG_HIGH_5_BIT                  (0xF8)
#define NAS_LCS_MSG_HIGH_6_BIT                  (0xFC)
#define NAS_LCS_MSG_HIGH_7_BIT                  (0xFE)

#define NAS_LCS_MSG_LOW_BIT                     (0x0F)
#define NAS_LCS_MSG_HIGH_BIT                    (0xF0)
#define NAS_LCS_MSG_LOW_5_BIT                   (0x1F)
#define NAS_LCS_MSG_LOW_6_BIT                   (0x3F)
#define NAS_LCS_MSG_LOW_7_BIT                   (0x7F)
#define NAS_LCS_MSG_LOW_8_BIT                   (0xFF)
#define NAS_LCS_MSG_LOW_16_BIT                  (0xFFFF)

#define NAS_LCS_MSG_8_BIT                       (0x80)
#define NAS_LCS_MSG_7_BIT                       (0x40)
#define NAS_LCS_MSG_6_BIT                       (0x20)
#define NAS_LCS_MSG_5_BIT                       (0x10)
#define NAS_LCS_MSG_4_BIT                       (0x08)
#define NAS_LCS_MSG_3_BIT                       (0x04)
#define NAS_LCS_MSG_2_BIT                       (0x02)
#define NAS_LCS_MSG_1_BIT                       (0x01)

#define NAS_LCS_MOVEMENT_1_BITS                 (1)
#define NAS_LCS_MOVEMENT_2_BITS                 (2)
#define NAS_LCS_MOVEMENT_3_BITS                 (3)
#define NAS_LCS_MOVEMENT_4_BITS                 (4)
#define NAS_LCS_MOVEMENT_5_BITS                 (5)
#define NAS_LCS_MOVEMENT_6_BITS                 (6)
#define NAS_LCS_MOVEMENT_7_BITS                 (7)
#define NAS_LCS_MOVEMENT_8_BITS                 (8)
#define NAS_LCS_MOVEMENT_16_BITS                (16)
#define NAS_LCS_MOVEMENT_24_BITS                (24)


/*封装打印LOG的宏*/
#ifdef PS_ITT_PC_TEST
#define NAS_LCS_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LCS_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#define NAS_LCS_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_ERR_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LCS_ERR_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#else
#define NAS_LCS_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_LCS_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_LCS_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_LCS_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_LCS_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_LCS_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_LCS_ERR_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_LCS_ERR_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#endif

#if (VOS_OS_VER == VOS_WIN32)

#define NAS_LCS_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LCS_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LCS_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
/*****************************************************************************
Function Name  : NAS_LCS_MEM_CPY_S
Discription    : LCS MEM CPY函数, 用于目标内存大小与需拷贝内存大小不相同时, 目标
                 内存大小必须大于需拷贝长度, 否则返回失败
Input          : pDestBuffer   :目标内存地址
                 ulMaxDest     :目标内存最大拷贝长度
                 pSrcBuffer    :原内存地址
                 Count         :拷贝内存字节数
Return         : EOK           :拷贝成功
                 其他          :拷贝失败
*****************************************************************************/
#define NAS_LCS_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength ) \
        (VOS_VOID)NAS_LCS_SecuMemCpy(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, (__LINE__), (THIS_FILE_ID) )

/*****************************************************************************
Function Name  : NAS_LCS_MEM_SET_S
Discription    : LCS MEM SET函数, 用于目标内存大小与需初始化大小不相同时, 目标
                 内存大小必须大于需初始化长度, 否则返回失败
Input          : pDestBuffer   :目标内存地址
                 ulMaxDest     :目标内存最大长度
                 ucData        :初始化目标值
                 Count         :初始化内存大于
Return         : EOK           :初始化成功
                 其他          :初始化失败
*****************************************************************************/
#define NAS_LCS_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength) \
        (VOS_VOID)TLPS_MEM_SET_S((pDestBuffer), (ulMaxDest), (ucData), (ulLength), (__LINE__), (THIS_FILE_ID))

#define NAS_LCS_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength ) \
        (VOS_VOID)TLPS_MEM_MOVE_S( (pDestBuffer), (ulMaxDest), (pSrcBuffer), (ulLength), (__LINE__), (THIS_FILE_ID))

#endif

#define NAS_LCS_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
    PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define NAS_LCS_MEM_FREE(pAddr) \
            {\
                if(VOS_OK != PS_MEM_FREE_ALL_CHECK((WUEPS_PID_LCS), (pAddr)))\
                {\
                    NAS_LCS_ERR_LOG("NAS_LCS_MEM_FREE  ERR!!");\
                }\
            }

#define NAS_LCS_MEM_ALLOC(ulSize) \
            PS_MEM_ALLOC_All_CHECK((WUEPS_PID_LCS), (ulSize))

#define NAS_LCS_ALLOC_MSG(ulLen)\
            PS_ALLOC_MSG_ALL_CHECK((WUEPS_PID_LCS),(ulLen))


/* 发送消息 */
#define NAS_LCS_SND_MSG(pMsg)\
    {\
        NAS_LCS_PrintLcsSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_LCS_PRINT_BUF());\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((WUEPS_PID_LCS) , (pMsg)))\
            {\
                NAS_LCS_ERR_LOG("NAS_LCS_SND_MSG:Msg Snd Err!");\
            }\
    }

#define NAS_LCS_ReadNv( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)


#define NAS_LCS_WRITE_TAF_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_TAF;\
                    (pstMsg)->stMsgHeader.ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_LMM_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_MM_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_MM;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_LPP_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_LPP;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_OM_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);


/*定时器时长*/
#define TI_NAS_LCS_LPP_WAIT_NW_RSP_TIMER_LEN        (180*1000)      /* LPP触发的MO-LR，等待网侧响应定时器时长 */
#define TI_NAS_LCS_LPP_WAIT_USER_RSP_TIMER_LEN      (30*1000)       /* 等待用户响应定时器时长 */



#define NAS_LCS_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_LCS_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 结构名称: NAS_LCS_ENTITY_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 实体类型
*****************************************************************************/
enum NAS_LCS_ENTITY_TYPE_ENUM
{
    NAS_LCS_ENTITY_TYPE_MOLR       = 1,            /* 当前为MOLR实体 */
    NAS_LCS_ENTITY_TYPE_MTLR       = 2,            /* 当前为MTLR实体 */

    NAS_LCS_ENTITY_TYPE_BUTT
};
typedef VOS_UINT8  NAS_LCS_ENTITY_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_DOMAIN_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS域类型
*****************************************************************************/
enum NAS_LCS_DOMAIN_TYPE_ENUM
{
    NAS_LCS_DOMAIN_TYPE_EPC_LCS     = 0,
    NAS_LCS_DOMAIN_TYPE_CS_LCS      = 1,

    NAS_LCS_DOMAIN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LCS_DOMAIN_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_CONN_STATE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明:LCS实体连接状态
*****************************************************************************/
enum NAS_LCS_CONN_STATE_ENUM
{
    NAS_LCS_CONN_STATE_IDLE         = 0, /* IDLE */
    NAS_LCS_CONN_STATE_ESTING       = 1, /* ESTING */
    NAS_LCS_CONN_STATE_CONN         = 2, /* CONNECTED */
    NAS_LCS_CONN_STATE_BUTT
};
typedef VOS_UINT8 NAS_LCS_CONN_STATE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_ENTITY_USE_FLAG_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS本地实体记录是否被使用
*****************************************************************************/
enum NAS_LCS_ENTITY_USE_FLAG_ENUM
{
    NAS_LCS_ENTITY_NOT_USED         = 0,                    /* 实体没被使用 */
    NAS_LCS_ENTITY_USED             = 1,                    /* 实体被使用 */
    NAS_LCS_ENTITY_USE_FLAG_BUTT
};
typedef VOS_UINT8 NAS_LCS_ENTITY_USE_FLAG_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_NW_EPC_LCS_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 网侧EPC_LCS能力枚举
*****************************************************************************/
enum NAS_LCS_NW_EPC_LCS_ENUM
{
    NAS_LCS_NW_EPC_LCS_NOT_SUPPORT           = 0,           /* 网侧不支持EPC LCS */
    NAS_LCS_NW_EPC_LCS_SUPPORT               = 1,           /* 网侧支持EPC LCS */

    NAS_LCS_NW_EPC_LCS_BUTT
};
typedef VOS_UINT32 NAS_LCS_NW_EPC_LCS_ENUM_UINT32;

/*****************************************************************************
 结构名称: NAS_LCS_NW_CS_LCS_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: 网侧CS_LCS能力枚举
*****************************************************************************/
enum NAS_LCS_NW_CS_LCS_ENUM
{
    NAS_LCS_NW_CS_LCS_NO_INFORMATION         = 0,           /* 网侧消息中未携带是否支持CS LCS */
    NAS_LCS_NW_CS_LCS_SUPPORT                = 1,           /* 网侧支持CS_LCS */
    NAS_LCS_NW_CS_LCS_NOT_SUPPORT            = 2,           /* 网侧不支持LCS */
    NAS_LCS_NW_CS_LCS_RESERVED               = 3,           /* 保留 */

    NAS_LCS_NW_CS_LCS_BUTT
};
typedef VOS_UINT32 NAS_LCS_NW_CS_LCS_ENUM_UINT32;

/*****************************************************************************
 结构名称: NAS_LCS_START_SOURCE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS发起源枚举
*****************************************************************************/
enum NAS_LCS_START_SOURCE_ENUM
{
    NAS_LCS_START_SOURCE_NW             = 0,
    NAS_LCS_START_SOURCE_LPP            = 1,
    NAS_LCS_START_SOURCE_TAF            = 2,

    NAS_LCS_START_SOURCE_BUTT
};
typedef VOS_UINT8 NAS_LCS_START_SOURCE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_ENTITY_STATE_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS实体状态枚举
*****************************************************************************/
enum NAS_LCS_ENTITY_STATE_ENUM
{
    NAS_LCS_ENTITY_STATE_NULL               = 0,
    NAS_LCS_ENTITY_STATE_WAIT_NW_RSP        = 1,
    NAS_LCS_ENTITY_STATE_WAIT_USER_RSP      = 2,
    NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL    = 3,

    NAS_LCS_ENTITY_STATE_BUTT
};
typedef VOS_UINT8 NAS_LCS_ENTITY_STATE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_CAP_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS实体状态枚举
*****************************************************************************/
enum NAS_LCS_CAP_ENUM
{
    NAS_LCS_CAP_NOT_SUPPORT             = 0,
    NAS_LCS_CAP_SUPPORT                 = 1,

    LMM_LCS_UE_LCS_BUTT
};
typedef VOS_UINT8 NAS_LCS_CAP_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_LCS_TIMER_RUN_STA_ENUM
 协议表格:
 ASN.1 描述:
 结构说明: LCS定时器状态枚举
*****************************************************************************/
enum    NAS_LCS_TIMER_RUN_STA_ENUM
{
    NAS_LCS_TIMER_RUNNING                = 0x00,
    NAS_LCS_TIMER_STOPED,
    NAS_LCS_TIMER_INVALID,

    NAS_LCS_TIMER_BUTT
};
typedef VOS_UINT32   NAS_LCS_TIMER_RUN_STA_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名称: NAS_LCS_NW_CAP_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 网侧LCS能力
*****************************************************************************/
typedef struct
{
    NAS_LCS_NW_EPC_LCS_ENUM_UINT32  enNwEpcLcs;
    NAS_LCS_NW_CS_LCS_ENUM_UINT32   enNwCsLcs;
}NAS_LCS_NW_CAP_INFO_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_UE_CAP_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: UE CS LCS能力
*****************************************************************************/
typedef struct
{
    NAS_LCS_CAP_ENUM_UINT8              enPsLcsCap;                     /* 是否支持PS-LCS */
    NAS_LCS_CAP_ENUM_UINT8              enCsLcsCap;                     /* 是否支持CS-LCS */
    VOS_UINT8                           aucRsv[2];
}NAS_LCS_GU_LCS_CAP_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_LTE_LCS_CAP_STRU
 协议表格:
 ASN.1 描述:
 结构说明: UE LTE LCS能力
*****************************************************************************/
typedef struct
{
    NAS_LCS_CAP_ENUM_UINT8              enEpcLcsCap;                    /* 是否支持EPC-LCS */
    NAS_LCS_CAP_ENUM_UINT8              enLppCap;                       /* 是否支持LPP */
    VOS_UINT8                           aucRsv[2];
}NAS_LCS_LTE_LCS_CAP_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_UE_CAP_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: UE LCS能力
*****************************************************************************/
typedef struct
{
    NAS_LCS_GU_LCS_CAP_STRU             stGuLcsCap;
    NAS_LCS_LTE_LCS_CAP_STRU            stLteLcsCap;
}NAS_LCS_UE_CAP_INFO_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_TAF_MSG_RECORD_STRU
 协议表格:
 ASN.1 描述:
 结构说明: TAF消息内容记录
*****************************************************************************/
typedef struct
{
    LCS_MOLR_PARA_STRU                  stMolrPara;                     /* TAF给LCS发送的BeginReq消息内容 */
}NAS_LCS_TAF_MSG_RECORD_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_NW_MSG_RECORD_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口消息内容记录
*****************************************************************************/
typedef struct
{
    LCS_NOTIFICATION_TYPE_ENUM_UINT8    enNotificationType;           /* MT-LR Notification类型 */
    VOS_UINT8                           aucRsv[3];
}NAS_LCS_NW_MSG_RECORD_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_LPP_MSG_RECORD_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LPP消息内容记录机构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLppMsgSize;       /* 长度 */
    VOS_UINT8                           aucLppMsg[NAS_LCS_MAX_LPP_MSG_LEN];
}NAS_LCS_LPP_MSG_RECORD_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_COMM_NV_PARA_STRU
 协议表格:
 ASN.1 描述:
 结构说明: NV设置本地存储结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPeriodicRptTimes :1;               /* 是否设置了周期上报次数 */
    VOS_UINT32                          bitOpSpare            :31;

    VOS_UINT8                           ucMaxRetryTimes;                        /* 最大重新尝试次数 */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT16                          usRetryTimerLen;                        /* 重新尝试定时器时长, 超时后会重新建链 */
    VOS_UINT16                          usPeriodicRptTimes;                     /* MO-LR为周期上报时,设置周期上报次数 */
}NAS_LCS_COMM_NV_PARA_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_STATE_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LCS状态表结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTi;                               /* MO TI为8-14，MT TI为0-6，
                                                                            此TI还不是空口中传输的TI值，需要进行一定转换，
                                                                            为了适配MM */
    VOS_UINT8                           ucHandleId;
    NAS_LCS_ENTITY_USE_FLAG_ENUM_UINT8  enUsedFlag;                         /* 判断该实体是否被使用 */
    NAS_LCS_CONN_STATE_ENUM_UINT8       enConnState;                        /* 当前连接状态 */
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enEntityState;                      /* 实体状态 */
    VOS_UINT8                           ucEstRetryTimes;                    /* 重试建链次数 */
    VOS_UINT8                           ucPeriodRetryTimes;                 /* 周期尝试次数 */
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enCurLcsDomain;                     /* 当前LCS选择的域 */
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource;                      /* 启动LCS源,主要用于区分LPP和TAF触发的MOLR */
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           aucRsv[2];
    NAS_LCS_TIMER_INFO_STRU             stStateTimer;                       /* 状态定时器 */
    NAS_LCS_TIMER_INFO_STRU             stWaitResetTimer;                   /* WAIT RESET定时器 */
    NAS_LCS_NW_MSG_RECORD_STRU          stLcsNwMsgRecord;                   /* 记录网侧发送的空口信息 */
}NAS_LCS_ENTITY_INFO_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_ENCODE_BUFFER_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 编码维护BUFFER
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBufferLen;
    VOS_UINT8                           aucBuffer[NAS_LCS_MAX_UPLINDK_LCS_MSG];
}NAS_LCS_ENCODE_BUFFER_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_PUB_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LCS信息本地维护结构
*****************************************************************************/
typedef struct
{
    NAS_LCS_NW_CAP_INFO_STRU            stNwLcsCap;                             /* 网侧LCS能力 */
    NAS_LCS_COMM_NV_PARA_STRU           stCommNvPara;                           /* LCS NV相关配置都保存到该成员中 */

    /* LCS实体记录,最多记录5条,第一个实体存储LPP触发的MO-LR,第二个实体存储TAF触发的MO-LR,
        第三个到第五个实体存储MT-LR */
    NAS_LCS_ENTITY_INFO_STRU            astLcsEntity[NAS_LCS_MAX_ENTITY_NUM];
    NAS_LCS_TAF_MSG_RECORD_STRU         stTafMsgRecord;                         /* 记录TAF给LCS的消息 */
    NAS_LCS_LPP_MSG_RECORD_STRU         stLppMsgRecord;                         /* 记录LPP给LCS的消息 */

    VOS_UINT8                           ucCurHandleId;
    VOS_UINT8                           ucCurInvokeId;
    VOS_UINT8                           aucRsv[2];

    NAS_LCS_ENCODE_BUFFER_STRU          stEncodeBuffer;
}NAS_LCS_PUB_INFO_STRU;


/*****************************************************************************
 结构名称: NAS_LCS_NV_PERIODIC_RPT_PARA_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 周期性上报参数设置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPerRptTimesFlag;    /* usPerRptTimes设置是否有效, 0:表示无效, 1:表示有效 */
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usPerRptTimes;        /* 周期性上报上报次数设置 */
}NAS_LCS_NV_PERIODIC_RPT_PARA_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_NV_RETRY_PARA_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 重新尝试相关NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRetryTimerLen;      /* 等待重建定时器时长,单位为秒 */
    VOS_UINT8                           ucCsLcsRetryTimes;    /* Cs Lcs 重新尝试次数 */
    VOS_UINT8                           ucEpcLcsRetryTimes;   /* Epc Lcs 重新尝试次数 */
    VOS_UINT8                           ucRsv;
}NAS_LCS_NV_RETRY_PARA_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_NV_PARA_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LCS NV 参数设置
*****************************************************************************/
typedef struct
{
    NAS_LCS_NV_RETRY_PARA_STRU          stRetryPara;          /* 重新尝试NV配置 */
    NAS_LCS_NV_PERIODIC_RPT_PARA_STRU   stPerRptPara;         /* 周期性上报参数设置 */
}NAS_LCS_NV_PARA_STRU;

/*****************************************************************************
 结构名称: NAS_LCS_ENCODE_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 空口编码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpCause      :1;
    VOS_UINT32                          bitLocNtfRsp    :1;
    VOS_UINT32                          bitOpInvokeId   :1;
    VOS_UINT32                          bitOpSpare      :29;

    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucInvokeId;
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource;
    LCS_MTLRA_OP_ENUM_UINT8             enLocNtfRsp;
    NAS_LCS_OPERATION_TYPE_UINT32       enOperType;
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause;
}NAS_LCS_ENCODE_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_LCS_PUB_INFO_STRU                g_stLcsInfo;
extern NAS_LCS_PUB_INFO_STRU               *pg_stLcsInfo;

#define NAS_LCS_GetLcsInfo()                    (pg_stLcsInfo)
#define NAS_LCS_GetLcsEntity(ulIndex)           (&pg_stLcsInfo->astLcsEntity[ulIndex])
#define NAS_LCS_GetCurHandleId()                (pg_stLcsInfo->ucCurHandleId)
#define NAS_LCS_SetCurHandleId(ucHandleId)      (pg_stLcsInfo->ucCurHandleId = ucHandleId)
#define NAS_LCS_GetCurInvokeId()                (pg_stLcsInfo->ucCurInvokeId)
#define NAS_LCS_SetCurInvokeId(ucInvokeId)      (pg_stLcsInfo->ucCurInvokeId = ucInvokeId)
#define NAS_LCS_GetNwLcsCap()                   (&pg_stLcsInfo->stNwLcsCap)
#define NAS_LCS_GetEncodeBuffer()               (&pg_stLcsInfo->stEncodeBuffer)


/* 获取实体信息 */
#define NAS_LCS_GetEntityState(ulIndex)                     (pg_stLcsInfo->astLcsEntity[ulIndex].enEntityState)
#define NAS_LCS_GetEntityConnState(ulIndex)                 (pg_stLcsInfo->astLcsEntity[ulIndex].enConnState)
#define NAS_LCS_GetEntityLcsDomain(ulIndex)                 (pg_stLcsInfo->astLcsEntity[ulIndex].enCurLcsDomain)
#define NAS_LCS_SetEntityLcsDomain(ulIndex, enLcsDoamin)    (pg_stLcsInfo->astLcsEntity[ulIndex].enCurLcsDomain = (enLcsDoamin))
#define NAS_LCS_GetEntityEstRetryTimers(ulIndex)            (pg_stLcsInfo->astLcsEntity[ulIndex].ucEstRetryTimes)
#define NAS_LCS_AddEntityEstRetryTimers(ulIndex)            (pg_stLcsInfo->astLcsEntity[ulIndex].ucEstRetryTimes++)
#define NAS_LCS_ResetEntityEstRetryTimers(ulIndex)          (pg_stLcsInfo->astLcsEntity[ulIndex].ucEstRetryTimes = 0)
#define NAS_LCS_GetEntityPediodRetryTimers(ulIndex)         (pg_stLcsInfo->astLcsEntity[ulIndex].ucPeriodRetryTimes)
#define NAS_LCS_AddEntityPediodRetryTimers(ulIndex)         (pg_stLcsInfo->astLcsEntity[ulIndex].ucPeriodRetryTimes++)
#define NAS_LCS_ResetEntityPediodRetryTimers(ulIndex)       (pg_stLcsInfo->astLcsEntity[ulIndex].ucPeriodRetryTimes = 0)
#define NAS_LCS_GetEntityTi(ulIndex)                        (pg_stLcsInfo->astLcsEntity[ulIndex].ucTi)
#define NAS_LCS_GetEntityStrartSource(ulIndex)              (pg_stLcsInfo->astLcsEntity[ulIndex].enStartSource)
#define NAS_LCS_SetEntityTi(ulIndex, ucTmpTi)               (pg_stLcsInfo->astLcsEntity[ulIndex].ucTi = (ucTmpTi))
#define NAS_LCS_GetStateTimer(ulIndex)                      (&pg_stLcsInfo->astLcsEntity[ulIndex].stStateTimer)
#define NAS_LCS_GetWaitResetTimer(ulIndex)                  (&pg_stLcsInfo->astLcsEntity[ulIndex].stWaitResetTimer)
#define NAS_LCS_GetEntityHandleId(ulIndex)                  (pg_stLcsInfo->astLcsEntity[ulIndex].ucHandleId)
#define NAS_LCS_SetEntityHandleId(ulIndex, ucHandleId)      (pg_stLcsInfo->astLcsEntity[ulIndex].ucHandleId = (ucHandleId))
#define NAS_LCS_GetEntityNwMsgRecord(ulIndex)               (&pg_stLcsInfo->astLcsEntity[ulIndex].stLcsNwMsgRecord)
#define NAS_LCS_GetEntityNotificationType(ulIndex)          (pg_stLcsInfo->astLcsEntity[ulIndex].stLcsNwMsgRecord.enNotificationType)
#define NAS_LCS_GetEntityInvokeId(ulIndex)                  (pg_stLcsInfo->astLcsEntity[ulIndex].ucInvokeId)
#define NAS_LCS_SetEntityInvokeId(ulIndex,ucCurInvokeId)    (pg_stLcsInfo->astLcsEntity[ulIndex].ucInvokeId = (ucCurInvokeId))


/* 获取TAF发来的信息 */
#define NAS_LCS_GetTafMolrRecord()              (&pg_stLcsInfo->stTafMsgRecord.stMolrPara)
#define NAS_LCS_GetMolrMode()                   (pg_stLcsInfo->stTafMsgRecord.stMolrPara.enRepMode)

/* 获取LPP发来的信息 */
#define NAS_LCS_GetLppMolrRecord()              (&pg_stLcsInfo->stLppMsgRecord)


/* 获取NV相关信息 */
#define NAS_LCS_GetCommNvPara()                 (&pg_stLcsInfo->stCommNvPara)
#define NAS_LCS_GetNvMaxRetryTimes()            (pg_stLcsInfo->stCommNvPara.ucMaxRetryTimes)
#define NAS_LCS_GetNvMaxPeriodicRptTimes()      (pg_stLcsInfo->stCommNvPara.usPeriodicRptTimes)







/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern NAS_LCS_DOMAIN_TYPE_ENUM_UINT8 NAS_LCS_SelectMolrDomain( VOS_VOID );
extern VOS_VOID NAS_LCS_StartTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
);
extern VOS_VOID NAS_LCS_StopTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
);
extern VOS_UINT32 NAS_LCS_QueryMolrEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_LCS_IsLteSupportCsLcs( VOS_VOID );
extern VOS_VOID NAS_LCS_ClearResource ( VOS_VOID );
extern VOS_VOID NAS_LCS_SetEntityState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enEntityState
);
extern VOS_VOID NAS_LCS_SetEntityConnState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enConnState
);
extern VOS_UINT32 NAS_LCS_IsMoLr
(
    VOS_UINT32                          ulIndex
);
extern VOS_UINT32 NAS_LCS_CreateLcsEntity
(
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32  NAS_LCS_GetLcsEntityNum( VOS_VOID );
extern VOS_VOID NAS_LCS_ClearLcsEntityAndNotify
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
);
extern VOS_VOID  NAS_LCS_ProcMolrConnAbnormal
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause
);
extern VOS_VOID NAS_LCS_ClearSingleLcsEntity
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
);
extern VOS_UINT32 NAS_LCS_QueryMtLrEntity
(
    VOS_UINT8                           ucHandleId,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID  NAS_LCS_ReadLcsNvCommonConfig( VOS_VOID);
extern VOS_VOID  NAS_LCS_ProcAirMsg
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
);
extern VOS_UINT32 NAS_LCS_QueryLcsEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
);
extern NAS_LCS_TIMER_RUN_STA_ENUM_UINT32  NAS_LCS_IsTimerRunning
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
);
extern TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmEstCnfCauseMap(const LMM_LCS_EST_RESULT_ENUM_UINT32 enCause);
extern TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmDataCnfCauseMap(const LMM_LCS_SEND_RSLT_ENUM_UINT32 enCause);
extern TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmRelCauseMap(const LMM_LCS_REL_CAUSE_ENUM_UINT32 enCause);
extern VOS_UINT8 NAS_LCS_CreateMoTi
(
    VOS_UINT32                          ulIndex
);
extern VOS_UINT8 NAS_LCS_CreateInvokeId( VOS_VOID );
extern VOS_VOID  NAS_LCS_ProcPeriodMolrOnceAbnormalEnd
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
);
extern VOS_VOID  NAS_LCS_TryToChangeDomain
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause
);
extern VOS_VOID  NAS_LCS_SndTafBeginInd
(
    const NAS_LCS_LOC_NOTFICATION_STRU *pstLocNotication,
    VOS_UINT8                           ucHandleId
);
extern VOS_VOID NAS_LCS_SndRegister
(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_LCS_SndFacility
(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_LCS_SndReleaseComplte
(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_LCS_SndMtlrFailReleaseComplte
(
    VOS_UINT8                           ucDlAirTi,
    VOS_UINT8                           ucInvokeId,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType,
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause
);
extern VOS_VOID NAS_LCS_SndMtlrRspReleaseComplte
(
    VOS_UINT32                          ulIndex,
    LCS_MTLRA_OP_ENUM_UINT8             enLocNtfRsp
);

extern VOS_INT32 NAS_LCS_SecuMemCpy
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

#endif











































