/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmBackOffAlgMain.h
  Description     : NasEsmBackOffAlgMain.c的头文件
  History         :
      1.sunjitan 00193151    2015-01-12  Draft   Enact



******************************************************************************/

#ifndef __NASESMBACKOFFALGMAIN_H__
#define __NASESMBACKOFFALGMAIN_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LNvCommon.h"
#include "LNasNvInterface.h"
#include "AppEsmInterface.h"
#include "NasEsmPublic.h"
//#include "AppNasComm.h"


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

/* 有效值相关宏定义 */

#define NAS_ESM_NO                             0
#define NAS_ESM_YES                            1

#define NAS_BACKOFF_NULL                       0
#define NAS_BACKOFF_NULL_PTR                  (0L)

#define NAS_BACKOFF_SUCC                       0
#define NAS_BACKOFF_FAIL                       1

#define NAS_BACKOFF_NVIM_SUCC                  0
#define NAS_BACKOFF_NVIM_FAIL                  1

#define NAS_BACKOFF_ALG_INVALID                0
#define NAS_BACKOFF_ALG_VALID                  1

#define NAS_BACKOFF_BIT_NO_SILT                0
#define NAS_BACKOFF_BIT_SILT                   1

#define NAS_BACKOFF_APN_ENTITY_MAX_NUM         6

#define NAS_BACKOFF_FX_DIVIDE_MIN_VALUE        2

#define NAS_BACKOFF_FX_MIN_VALUE               4

#define NAS_BACKOFF_FORBID_TIMER_MAX_VALUE    (15*60*1000)
#define NAS_BACKOFF_1HOUR_VALUE               (60*60*1000)

#define NAS_BACKOFF_PDP_CAUSE_NULL             0

#define NAS_BACKOFF_PDP_PERM_CAUSE_DEFAULT_NUM 7
#define NAS_BACKOFF_PDP_TEMP_CAUSE_DEFAULT_NUM 8
/*封装打印LOG的宏*/
#ifdef PS_ITT_PC_TEST
#define NAS_BACKOFF_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
 */
#define NAS_BACKOFF_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
 */
#define NAS_BACKOFF_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
 */
#define NAS_BACKOFF_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
 */
#define NAS_BACKOFF_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
 */
#define NAS_BACKOFF_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
 */
#define NAS_BACKOFF_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
 */
#define NAS_BACKOFF_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
 */
#else
#define NAS_BACKOFF_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_BACKOFF_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_BACKOFF_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_BACKOFF_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_BACKOFF_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_BACKOFF_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_BACKOFF_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_BACKOFF_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#endif



/*****************************************************************************
  3 Enum
*****************************************************************************/


/*****************************************************************************
结构名称    :NAS_BACKOFF_NETRAT_ENUM
使用说明    :Back-off算法支持的接入技术
*****************************************************************************/
enum NAS_BACKOFF_NETRAT_ENUM
{
    NAS_BACKOFF_NETRAT_LTE  = 0x00,     /* LTE */
    NAS_BACKOFF_NETRAT_GU   = 0x01,     /* GU  */

    NAS_BACKOFF_NETRAT_ENUM_BUTT
};
typedef VOS_UINT32  NAS_BACKOFF_NETRAT_ENUM_UINT32;

/*****************************************************************************
结构名称    :NAS_BACKOFF_OPERATE_TYPE_ENUM
使用说明    :Back-off算法实体操作消息类型枚举
*****************************************************************************/
enum NAS_BACKOFF_OPERATE_TYPE_ENUM
{
    NAS_BACKOFF_OPERATE_TYPE_INIT       = 0,     /* 初始化 */
    NAS_BACKOFF_OPERATE_TYPE_JUDGMENT   = 1,     /* 判定 */
    NAS_BACKOFF_OPERATE_TYPE_MAINTAIN   = 2,     /* 维护 */
    NAS_BACKOFF_OPERATE_TYPE_RESET      = 3,     /* 复位 */

    NAS_BACKOFF_OPERATE_TYPE_ENUM_BUTT
};
typedef VOS_UINT32  NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32;

/*****************************************************************************
结构名称    :NAS_BACKOFF_RESET_TYPE_ENUM
使用说明    :Back-off算法实体重置原因枚举
*****************************************************************************/
enum NAS_BACKOFF_RESET_CAUSE_ENUM
{
    NAS_BACKOFF_RESET_CAUSE_SWITCH_OFF    = 0,     /* 关机 */
    NAS_BACKOFF_RESET_CAUSE_PLMN_CHANGE   = 1,     /* PLMN变更 */

    NAS_BACKOFF_RESET_CAUSE_ENUM_BUTT
};
typedef VOS_UINT32  NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32;

/*****************************************************************************
结构名称    :NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM
使用说明    :PDP激活结果
*****************************************************************************/
enum NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM
{
    NAS_BACKOFF_PDP_ACTIVE_RESULT_SUCC       = 0X00,     /* 成功     */
    NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP  = 0X01,     /* 超时     */
    NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ     = 0X02,     /* 网侧拒绝 */

    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8;

/*****************************************************************************
结构名称    :NAS_BACKOFF_APN_ENTITY_FLAG_ENUM
使用说明    :Back-off算法APN实体标识
*****************************************************************************/
enum NAS_BACKOFF_APN_ENTITY_FLAG_ENUM
{
    NAS_BACKOFF_APN_ENTITY_FLAG_INVALID = 0x00,     /* APN实体处于无效态 */
    NAS_BACKOFF_APN_ENTITY_FLAG_VALID   = 0x01,     /* APN实体处于有效态 */

    NAS_BACKOFF_APN_ENTITY_FLAG_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_APN_ENTITY_FLAG_ENUM_UINT8;

/*****************************************************************************
结构名称    :NAS_BACKOFF_STATE_ENUM
使用说明    :Back-off算法状态枚举
*****************************************************************************/
enum NAS_BACKOFF_STATE_ENUM
{
    NAS_BACKOFF_STATE_INACTIVE = 0x00,     /* 算法处于未激活态 */
    NAS_BACKOFF_STATE_ACTIVE   = 0x01,     /* 算法处于激活态 */

    NAS_BACKOFF_STATE_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_STATE_ENUM_UINT8;

/*****************************************************************************
结构名称    :NAS_ESM_BACKOFF_FOBID_TIMER_STATE_ENUM
使用说明    :惩罚定时器状态枚举
*****************************************************************************/
enum NAS_BACKOFF_FOBID_TIMER_STATE_ENUM
{
    NAS_BACKOFF_FOBID_TIMER_STATE_STOP     = 0x00,  /* 惩罚定时器未运行 */
    NAS_BACKOFF_FOBID_TIMER_STATE_RUNNING  = 0x01,  /* 惩罚定时器在运行 */

    NAS_BACKOFF_FOBID_TIMER_STATE_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_FOBID_TIMER_STATE_ENUM_UINT8;

/*****************************************************************************
结构名称    :NAS_BACKOFF_PDP_REJ_TYPE_ENUM
使用说明    :Back-off算法实体PDP激活被网侧拒绝的类型
*****************************************************************************/
enum NAS_BACKOFF_PDP_REJ_TYPE_ENUM
{
    NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ  = 0X00,     /* 永久拒绝 */
    NAS_BACKOFF_PDP_REJ_TYPE_TEMP_REJ  = 0X01,     /* 临时拒绝 */
    NAS_BACKOFF_PDP_REJ_TYPE_OTHER     = 0X02,     /* 其他     */

    NAS_BACKOFF_PDP_REJ_TYPE_ENUM_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_PDP_REJ_TYPE_ENUM8;

/*****************************************************************************
  4 STRUCT
*****************************************************************************/

/*****************************************************************************
结构名称    :NAS_BACKOFF_INIT_INFO_STRU
使用说明    :Back-off算法初始化信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32   bitOpSimFxFlag   :1;  /* SIM卡中参数是否有效                  */
    VOS_UINT32   bitOpRsv         :31; /* 保留                                 */

    VOS_UINT8    ucSimFxIgnore;        /* Ignore场景连续失败计数USIM中的限定值 */
    VOS_UINT8    ucSimFxPerm;          /* Perm场景连续失败计数USIM中的限定值   */
    VOS_UINT8    ucSimFxTemp;          /* Temp场景连续失败计数USIM中的限定值   */
    VOS_UINT8    ucRsv;
} NAS_BACKOFF_INIT_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_ESM_BACKOFF_OPERATION_TYPE_MSG_STRU
使用说明    :Back-off算法判定消息入参
*****************************************************************************/
typedef APP_ESM_APN_INFO_STRU  NAS_BACKOFF_JUDGMENT_PARA_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_OPERATION_TYPE_MSG_STRU
使用说明    :Back-off算法维护消息入参
*****************************************************************************/
typedef struct
{
    APP_ESM_APN_INFO_STRU                    stApnInfo;      /* APN            */
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult;    /* PDP激活结果    */
    VOS_UINT8                                ucCnCause;      /* 网侧拒绝原因值 */
    VOS_UINT8                                ucRsv[2];       /* 保留           */
} NAS_BACKOFF_MAINTAIN_PARA_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_QUERY_RESULT_STRU
使用说明    :Back-off算法查询结果
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulIndex;     /* 查询到的APN在算法实体中的索引 */
    NAS_BACKOFF_STATE_ENUM_UINT8              enState;     /* 查询到的Back-off算法状态 */
    NAS_BACKOFF_FOBID_TIMER_STATE_ENUM_UINT8  enTimeStatus;/* 查询到的是否有惩罚定时器在运行的结果 */
} NAS_BACKOFF_QUERY_RESULT_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_TIMER_INFO_STRU
使用说明    :Back-off算法惩罚定时器信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ulTminLen; /* 惩罚定时器下限 */
    VOS_UINT32   ulTmaxLen; /* 惩罚定时器上限 */
} NAS_BACKOFF_TIMER_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_BACK_OFF_ALGORITHM_ENTITY_STRU
使用说明    :Back-off算法公共参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucFxIgnore; /* NV或USIM中设置的对应ignore场景的Fx */
    VOS_UINT8   ucFxPerm;   /* NV或USIM中设置的对应perm场景的Fx   */
    VOS_UINT8   ucFxTemp;   /* NV或USIM中设置的对应Temp场景的Fx   */
    VOS_UINT8   ucRsv;

    VOS_UINT8   ucFbIgnore; /* ignore场景的阈值Fb */
    VOS_UINT8   ucFbPerm;   /* perm场景的阈值Fb   */
    VOS_UINT8   ucFbTemp;   /* temp场景的阈值Fb   */
    VOS_UINT8   ucRsv1;

    NAS_BACKOFF_TIMER_INFO_STRU   stFxIgnoreTimerInfo; /* Ignore场景下的定时器信息 */
    NAS_BACKOFF_TIMER_INFO_STRU   stFxPermTimerInfo;   /* Perm场景下的定时器信息   */
    NAS_BACKOFF_TIMER_INFO_STRU   stFxTempTimerInfo;   /* Temp场景下的定时器信息   */
} NAS_BACKOFF_COMM_PARA_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_TIMER_STRU
使用说明    :Back-off算法惩罚定时器
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;      /* vos分配的Timer Id   */
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enPara;      /* Timer类型   */
    VOS_UINT8                           ucRsv[3];    /* 保留   */
} NAS_BACKOFF_TIMER_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_INACTIVE_INFO_STRU
使用说明    :Back-off算法未激活态实体
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulFnIgnore;       /* 非激活态下Ignore场景连续失败计数 */
    VOS_UINT32  ulFnPerm;         /* 非激活态下Perm场景连续失败计数 */
    VOS_UINT32  ulFnTemp;         /* 非激活态下Temp场景连续失败计数 */
} NAS_BACKOFF_INACTIVE_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_ACTIVE_INFO_STRU
使用说明    :Back-off算法激活态实体
*****************************************************************************/
typedef struct
{
    NAS_BACKOFF_TIMER_STRU    stBackoffTimer;  /* 激活态下惩罚定时器信息 */
} NAS_BACKOFF_ACTIVE_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_APN_ENTITY_STRU
使用说明    :Back-off算法APN实体
*****************************************************************************/
typedef struct
{
    APP_ESM_APN_INFO_STRU                   stApnInfo;      /* APN */
    NAS_BACKOFF_APN_ENTITY_FLAG_ENUM_UINT8  enValidFlag;    /* 当前实体是否有效 */
    NAS_BACKOFF_STATE_ENUM_UINT8            enState;        /* Back-off算法状态: 激活还是未激活 */
    VOS_UINT8                               ucRsv[2];       /* 保留 */

    NAS_BACKOFF_INACTIVE_INFO_STRU          stInactiveInfo; /* 算法未激活态下维护的信息 */
    NAS_BACKOFF_ACTIVE_INFO_STRU            stActiveInfo;   /* 算法激活态下维护的信息   */
} NAS_BACKOFF_APN_ENTITY_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_NETRAT_ENTITY_STRU
使用说明    :Back-off算法接入技术实体
*****************************************************************************/
typedef struct
{
    NAS_BACKOFF_APN_ENTITY_STRU   stApnEntity[NAS_BACKOFF_APN_ENTITY_MAX_NUM]; /* APN相关实体 */
} NAS_BACKOFF_NETRAT_ENTITY_STRU;

/*****************************************************************************
结构名称    :NAS_BACK_OFF_ALGORITHM_ENTITY_STRU
使用说明    :Back-off算法实体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucBackOffAlgFlag;  /* 算法NV功能开关；0 关闭；1 开启 */
    VOS_UINT8                       ucRsv[3];          /* 保留 */

    NAS_BACKOFF_COMM_PARA_STRU      stCommPara;        /* 算法公共参数 */
    NAS_CONFIG_PDP_PERM_CAUSE_STRU  stPdpPermCause;    /* 永久拒绝原因值列表 */
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU  stPdpTempCause;    /* 临时拒绝原因值列表 */
    NAS_BACKOFF_NETRAT_ENTITY_STRU  stNetRatEntity[NAS_BACKOFF_NETRAT_ENUM_BUTT]; /* 接入技术相关实体 */
} NAS_BACKOFF_ALGORITHM_ENTITY_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_OPERATE_TYPE_MSG_STRU
使用说明    :Back-off算法操作消息入参
*****************************************************************************/
typedef struct
{
    union
    {
        NAS_BACKOFF_INIT_INFO_STRU           stInitPara;       /* 初始化操作入参 */
        NAS_BACKOFF_JUDGMENT_PARA_STRU       stJudgmentPara;   /* 判定操作入参   */
        NAS_BACKOFF_MAINTAIN_PARA_STRU       stMaintainPara;   /* 维护操作入参   */
        NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  enResetCause;     /* 重置操作入参   */
    }u;
} NAS_BACKOFF_OPERATE_PARA_STRU;
/*****************************************************************************
  5 Massage Declare
*****************************************************************************/


/*****************************************************************************
结构名称    :NAS_BACKOFF_LOG_OPERATE_INFO_STRU
使用说明    :Back-off算法操作的LOG信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_OPERATE_PARA_STRU        stOperatePara;
} NAS_BACKOFF_LOG_OPERATE_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_LOG_NV_INFO_STRU
使用说明    :Back-off算法NV读出参数的LOG信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;         /*_H2ASN_Skip*/
    NAS_CONFIG_BACKOFF_FX_PARA_STRU      stBackOffFx;         /* Fx参数                                */
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       stPdpPermCause;      /* 永久拒绝原因值列表                    */
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       stPdpTempCause;      /* 临时拒绝原因值列表                    */
    NAS_MM_DAM_PLMN_LIST_STRU            stDamPlmnList;       /* DAM特性生效的PLMN列表                 */
} NAS_BACKOFF_LOG_NV_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_LOG_COMM_INFO_STRU
使用说明    :Back-off算法读出当前实体状态LOG信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/

    NAS_BACKOFF_COMM_PARA_STRU           stCommPara;      /* 算法公共参数 */
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       stPdpPermCause;  /* 永久拒绝原因值列表 */
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       stPdpTempCause;  /* 临时拒绝原因值列表 */

} NAS_BACKOFF_LOG_COMM_INFO_STRU;

/*****************************************************************************
结构名称    :NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU
使用说明    :Back-off算法读出某接入技术下的当前实体信息列表
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;        /* 接入技术                */
    NAS_BACKOFF_NETRAT_ENTITY_STRU       stNetRatEntity;  /* 接入技术下的APN实体列表 */

} NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU;
/*****************************************************************************
结构名称    :NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU
使用说明    :Back-off算法Init操作的LOG信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_INIT_INFO_STRU           stInitInfo;
} NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU;
/*****************************************************************************
结构名称    :NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU
使用说明    :Back-off算法Judgment操作的LOG信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_JUDGMENT_PARA_STRU       stJudgmentPara;
} NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU;
/*****************************************************************************
结构名称    :NAS_BACKOFF_Maintain_OPERATE_INFO_STRU
使用说明    :Back-off算法Maintain操作的LOG信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_MAINTAIN_PARA_STRU       stMaintainPara;
} NAS_BACKOFF_Maintain_OPERATE_INFO_STRU;
/*****************************************************************************
结构名称    :NAS_BACKOFF_RESET_OPERATE_INFO_STRU
使用说明    :Back-off算法Reset操作的LOG信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  enResetCause;
} NAS_BACKOFF_RESET_OPERATE_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_BACKOFF_ALGORITHM_ENTITY_STRU  g_stBackOffEntity;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/* 外部仅能调用此接口函数 */
VOS_VOID NAS_BACKOFF_OperateInit
(
    NAS_BACKOFF_INIT_INFO_STRU            *pstInitPara
);
VOS_UINT32 NAS_BACKOFF_OperateJudgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
);
VOS_VOID NAS_BACKOFF_OperateMaintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_OperateReset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
);

/* 以下函数仅能在Back-off算法内部使用 */
VOS_UINT8* NAS_BACKOFF_GetAlgFlagAddr(VOS_VOID);
NAS_BACKOFF_APN_ENTITY_STRU* NAS_BACKOFF_GetApnEntityAddr
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32  enNetRat,
    VOS_UINT32                      ulIndex
);
NAS_BACKOFF_COMM_PARA_STRU* NAS_BACKOFF_GetCommParaAddr(VOS_VOID);
NAS_CONFIG_PDP_PERM_CAUSE_STRU* NAS_BACKOFF_GetPdpPermCauseListAddr(VOS_VOID);
NAS_CONFIG_PDP_TEMP_CAUSE_STRU* NAS_BACKOFF_GetPdpTempCauseListAddr(VOS_VOID);
VOS_VOID NAS_BACKOFF_SetBackOffState
(
    NAS_BACKOFF_STATE_ENUM_UINT8     enDestState,
    NAS_BACKOFF_APN_ENTITY_STRU     *pstApnEntity
);
VOS_UINT32 NAS_BACKOFF_MainTaskEntry
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32             enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32       enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU             *pstOpPara
);
VOS_VOID NAS_BACKOFF_Init
(
    NAS_BACKOFF_INIT_INFO_STRU  *pstInitInfo
);
VOS_UINT32 NAS_BACKOFF_Judgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
);
VOS_VOID NAS_BACKOFF_Maintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_Reset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
);
VOS_UINT32 NAS_BACKOFF_QueryInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    APP_ESM_APN_INFO_STRU              *pstApn,
    NAS_BACKOFF_QUERY_RESULT_STRU      *pstQueryResult
);
VOS_VOID NAS_BACKOFF_PdpActiveSuccProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_PdpActiveFailProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_InactiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
);
VOS_VOID NAS_BACKOFF_ActiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
);
VOS_UINT32  NAS_BACKOFF_ReadNvDamBackOffPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU        *pstNvDamPara
);
VOS_VOID  NAS_BACKOFF_InitPdpRejCauseList
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU           *pstNvDamPara
);
VOS_VOID  NAS_BACKOFF_InitCommParaFx
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU *pstNvDamPara,
    NAS_BACKOFF_INIT_INFO_STRU           *pstInitInfo
);
VOS_VOID NAS_BACKOFF_InitCommParaFb
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
);
VOS_VOID NAS_BACKOFF_InitCommParaTimerPara
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
);
VOS_VOID NAS_BACKOFF_CheckFx
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
);
VOS_UINT8 NAS_BACKOFF_SelectFb(VOS_UINT8 ucFx);
VOS_VOID NAS_BACKOFF_CalcTimerLenMinAndMax
(
    VOS_UINT8                           ucFx,
    VOS_UINT8                           ucFb,
    NAS_BACKOFF_TIMER_INFO_STRU        *pstTimerInfo
);
VOS_UINT32 NAS_BACKOFF_AllocApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                         *pulIndex
);
VOS_UINT8 NAS_BACKOFF_GetPdpCnRejType(VOS_UINT8  ucCnCause);
VOS_VOID NAS_BACKOFF_ClearApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex
);
VOS_UINT32 NAS_BACKOFF_TimerLenRandom
(
    NAS_BACKOFF_TIMER_INFO_STRU       *pstTimerInfo
);
VOS_UINT32 NAS_BACKOFF_ForbidTimerLenCalc
(
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
);
VOS_VOID NAS_BACKOFF_ForbidTimerStart
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
);
VOS_VOID NAS_BACKOFF_ForbidTimerStop
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
);
VOS_UINT8 NAS_BACKOFF_GetForbidTimerState
(
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity
);
VOS_VOID  NAS_BACKOFF_SndOmLogOperateInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32   enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogNvPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU         *pstNvDamPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogCommInfo(VOS_VOID);
VOS_VOID  NAS_BACKOFF_SndOmLogApnEntityList(NAS_BACKOFF_NETRAT_ENUM_UINT32 enNetRat);
VOS_VOID  NAS_BACKOFF_SndOmLog(NAS_BACKOFF_NETRAT_ENUM_UINT32 enNetRat);
VOS_VOID  NAS_BACKOFF_SndOmLogInitInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogJudgmentInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogMaintainInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogResetInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
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

#endif /* end of NasEsmPublic.h */
