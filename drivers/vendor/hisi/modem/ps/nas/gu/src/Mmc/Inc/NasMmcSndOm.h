/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndOm.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 定义MMC发送给OM的消息处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_SND_OM_H
#define _NAS_MMC_SND_OM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasOmInterface.h"
#include  "NasOmTrans.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "NasMmcCtx.h"
#include  "NasMmlLib.h"
#include  "NasMmSublayerDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_MMC_OUTSIDE_CONTEXT_TYPE_ENUM
 结构说明  : MMC发送给OM的回放的上下文消息的类型
  1.日    期   : 2011年8月22日
    作    者   : l00130025
    修改内容   : MMC发送给OM的回放的上下文消息的类型
*****************************************************************************/

enum NAS_MMC_OUTSIDE_CONTEXT_TYPE_ENUM
{
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_RUNNING_CONTEXT,                               /* 输出MMC的运行上下文 */
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_FSM_STACK,                                     /* 输出MMC的状态机栈数组*/
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_FSM_BUTT
};
typedef VOS_UINT32 NAS_MMC_OUTSIDE_CONTEXT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MMC_OM_MSG_ID_ENUM_U32
 结构说明  : MMC发送给OM的可维可测消息
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : MMC发送给OM的可维可测消息ID枚举
*****************************************************************************/
enum NAS_MMC_OM_MSG_ID_ENUM
{
    /* MMC发送给OM的消息 */
    MMCOM_LOG_FSM_INFO_IND                          = 0x1000,      /*_H2ASN_MsgChoice  NAS_MMC_LOG_FSM_INFO_STRU */
    MMCOM_LOG_GUTI_INFO_IND                         = 0x1001,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_GUTI_INFO_STRU */
    MMCOM_LOG_BUFFER_MSG_INFO_IND                   = 0x1002,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_BUffER_MSG_INFO_STRU */
    MMCOM_LOG_PLMN_SELECTION_LIST                   = 0x1003,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU */
    MMCOM_LOG_INTER_MSG_INFO_IND                    = 0x1004,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_INTER_MSG_INFO_STRU */
    MMCOM_LOG_DRX_TIMER_STATUS_IND                  = 0x1005,
    MMCOM_LOG_DPLMN_LIST                            = 0x1006,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_DPLMN_LIST_STRU */
    MMCOM_LOG_NPLMN_LIST                            = 0x1007,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_NPLMN_LIST_STRU */
    MMCOM_LOG_AS_PLMN_SELECTION_LIST                = 0x1008,

    MMCOM_LOG_DPLMN_NPLMN_CFG                       = 0x1009,  /*_H2ASN_MsgChoice  NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU */

    MMCOM_LOG_RPLMN_RELATED_INFO                    = 0x100A,
    MMCOM_LOG_FORBIDDEN_PLMN_RELATED_INFO           = 0x100B,
    MMCOM_LOG_RPLMN_CFG_INFO                        = 0x100C,

    MMCOM_LOG_SEARCH_TYPE_STRATEGY_RELATED_INFO         = 0x100D,

    MMCOM_LOG_FSM_PLMN_SELECTION_CTX_RELATED_INFO   = 0x1020,
    MMCOM_LOG_FSM_L1_MAIN_CTX_RELATED_INFO          = 0x1021,

    MMCOM_LOG_PLMN_REG_REJ_INFO                     = 0x1022,
    MMCOM_LOG_CURR_PLMN_RELATED_INFO                = 0x1023,

    MMCOM_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO   = 0x1024,

    MMCOM_LOG_MMC_TIMER_STATUS                      = 0x2000 ,  /*_H2ASN_MsgChoice  NAS_MMC_TIMER_INFO_STRU */

    MMCOM_LOG_MMC_PLATFORM_RAT_CAP                  = 0x3000 ,  /*_H2ASN_MsgChoice  NAS_MMC_TIMER_INFO_STRU */

    /* 以下消息只导出开机时读取NV项，或者USIM API获取的全局变量。用于从开机开始的回放 */
    MMCOM_FIXED_PART_CONTEXT                        = 0xaabb , /*_H2ASN_MsgChoice  NAS_MMC_FIXED_CONTEXT_MSG_STRU */
    MMCOM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY     = 0xaaaa ,     /*_H2ASN_MsgChoice  NAS_MMC_SDT_MSG_STRU */
    MMCOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_MMC_OM_MSG_ID_ENUM_U32;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulTopState;
}NAS_MMC_LOG_FSM_INFO_STRU;

#if (FEATURE_ON == FEATURE_LTE)
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_LMM_GUTI_STRU                   stGutiMsg;
}NAS_MMC_LOG_GUTI_INFO_STRU;
#endif



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulFullFlg;
    NAS_MMC_MSG_QUEUE_STRU              stMsgQueue;
}NAS_MMC_LOG_BUffER_MSG_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_LOG_INTER_MSG_INFO_STRU
 结构说明  : 内部消息队列满的通知
 1.日    期   : 2012年4月12日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucFullFlg;
    VOS_UINT8                           ucMsgLenValidFlg;
    VOS_UINT8                           aucReserve[2];
}NAS_MMC_LOG_INTER_MSG_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_LOG_DPLMNLIST_STRU
 结构说明  : DPLMN NPLMN list
 1.日    期   : 2014年11月11日
   作    者   : b00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT16                                              usDplmnListNum;
    VOS_UINT8                                               aucReserve[2];
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                   astDPlmnList[NAS_MMC_MAX_CFG_DPLMN_NUM];
}NAS_MMC_LOG_DPLMN_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_LOG_NPLMN_LIST_STRU
 结构说明  : DPLMN NPLMN list
 1.日    期   : 2014年11月11日
   作    者   : b00269685
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT16                                              usNplmnListNum;
    VOS_UINT8                                               aucReserve[2];
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                   astNPlmnList[NAS_MMC_MAX_CFG_NPLMN_NUM];
}NAS_MMC_LOG_NPLMN_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_LOG_NPLMN_LIST_STRU
 结构说明  : MMCOM_LOG_DPLMN_NPLMN_CFG对应的结构体
  1.日    期   : 2015年12月15日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头    */ /*_H2ASN_Skip*/
    VOS_UINT8                                               aucVersionId[NAS_MCC_INFO_VERSION_LEN];
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT8                                               ucEHplmnNum;
    NAS_MML_PLMN_ID_STRU                                    astEHplmnList[NAS_MMC_MAX_CFG_HPLMN_NUM];
}NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_FIXED_CONTEXT_MSG_STRU
 结构说明  : PC回放工程，所有MMC和MML相关的固定全局变量通过以下消息结构发送
 1.日    期   : 2011年7月20日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2011年8月20日
   作    者   : l00130025
   修改内容   : 回放消息修改
 3.日    期   : 2011年11月30日
   作    者   : z00161729
   修改内容   : 实现pc回放压缩功能修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucImeisv[NAS_MML_MAX_IMEISV_LEN];          /* IMEISV */
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;                            /* MMC当前搜网模式,自动模式或手动模式*/
    NAS_MML_MS_NETWORK_CAPACILITY_STRU                      stMsNetworkCapability;                  /* MS network capability*/
    VOS_UINT8                                               ucPsAutoAttachFlg;                          /* PS自动Attach标志en_NV_Item_Autoattach */
    NAS_MML_EQUPLMN_INFO_STRU                               stEquPlmnInfo;                              /* EQUPLMN信息 */
    NAS_MML_RPLMN_CFG_INFO_STRU                             stRplmnCfg;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                         stBGSrchCfg;
    VOS_UINT32                                              ulQuickStartFlag;
} NAS_MMC_FIXED_CONTEXT_MSG_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_LOG_PLMN_SELECTION_LIST_STRU
 结构说明  : 输出到SDT的搜网列表结构体
 1.日    期   : 2011年7月29日
   作    者   : s46746
   修改内容   : 新增
*****************************************************************************/
typedef struct{
    VOS_UINT32                          ulMcc;             /* 此网络的MCC    */
    VOS_UINT32                          ulMnc;             /* 此网络的MNC    */
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;        /* 网络类型       */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;         /* 网络的接入技术 */
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus;       /* 网络的存在状态 */
    NAS_MMC_NET_QUALITY_ENUM_UINT8      enQuality;         /* 网络的信号质量 */
}NAS_MMC_LOG_PLMN_SELECTION_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU
 结构说明  : 输出到SDT的搜网列表消息结构体
 1.日    期   : 2011年7月29日
   作    者   : s46746
   修改内容   : 新增
*****************************************************************************/
typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                                              ulPlmnNum;
    NAS_MMC_LOG_PLMN_SELECTION_LIST_STRU                    astPlmnSelectionList[NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST];/* 网络列表 */
}NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU
 结构说明  : 输出到SDT的接入层上报的搜网列表消息结构体
 1.日    期   : 2011年8月9日
   作    者   : z00161729
   修改内容   : 新增
*****************************************************************************/
typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSrchedPlmn;
}NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU;

/*****************************************************************************
 结构名称:  NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU
 结构说明:  MMC->MMC,PLMN REG REJ INFO 消息
  1.日    期   : 2015年10月20日
    作    者   : c00318887
    修改内容   :  新增结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */
    NAS_MMC_PLMN_REG_REJ_CTX_STRU       stPlmnRegRejInfo;   /* PLMN 注册被拒信息 */
} NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU;

/*****************************************************************************
 结构名称:  NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU
 结构说明:  MMC->MMC,PLMN REG REJ INFO 消息
  1.日    期   : 2015年10月20日
    作    者   : c00318887
    修改内容   :  新增结构

*****************************************************************************/
typedef struct
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;                               /* PlMN标识 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;                           /* 当前的网络接入技术 */
    VOS_UINT8                           aucReserve[3];

    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService;                        /* 当前CS域的服务状态 */
    NAS_MMC_SERVICE_ENUM_UINT8          enPsCurrService;                        /* 当前PS域的服务状态 */
    NAS_MML_REG_STATUS_ENUM_UINT8       enCsRegStatus;                          /* CS域的注册结果 */
    NAS_MML_REG_STATUS_ENUM_UINT8       enPsRegStatus;                          /* PS域的注册结果 */

} NAS_MMC_LOG_PLMN_RELATED_INFO_STRU;

/*****************************************************************************
 结构名称:  NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU
 结构说明:  MMC->MMC,PLMN REG REJ INFO 消息
  1.日    期   : 2015年10月20日
    作    者   : c00318887
    修改内容   :  新增结构

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */
    NAS_MMC_LOG_PLMN_RELATED_INFO_STRU  stPlmnRelatedInfo;   /* PLMN 注册被拒信息 */
} NAS_MMC_LOG_CURR_PLMN_RELATED_INFO_STRU;



/*****************************************************************************
 结构名    : NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU
 结构说明  : 输出RPLMN相关的可维可测信息结构体
 1.日    期   : 2015年1月5日
   作    者   : w00167002
   修改内容   : 新增
*****************************************************************************/
typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MML_PLMN_ID_STRU                                    stGetLteRplmn;      /* 获取当前LTE的RPLMN */
    NAS_MML_PLMN_ID_STRU                                    stGetGuRplmn;       /* 获取当前GU的RPLMN */
    NAS_MML_RPLMN_CFG_INFO_STRU                             stRplmnCfg;         /* RPLMN的定制特性 */
    NAS_MML_LAI_STRU                                        stLastSuccLai;      /* CS域最后一次注册成功的LAI信息或注册失败后需要删除LAI，则该值为无效值 */
    NAS_MML_RAI_STRU                                        stLastSuccRai;      /* PS域最后一次注册成功的RAI信息或注册失败后需要删除RAI，则该值为无效值 */
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8                enPsUpdateStatus;   /* status of routing update */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;   /* status of location update */
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;           /* 手机模式 */
    VOS_UINT8                                               ucReserved;
}NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_LOG_RPLMN_CFG_INFO_STRU
 结构说明  : 输出RPLMN平配置的可维可测信息结构体
 1.日    期   : 2015年1月5日
   作    者   : w00167002
   修改内容   : 新增
*****************************************************************************/
typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MML_RPLMN_CFG_INFO_STRU                             stRplmnCfg;         /* RPLMN的定制特性 */
}NAS_MMC_LOG_RPLMN_CFG_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU
 结构说明  : 输出FORB PLMN相关的可维可测信息结构体
 1.日    期   : 2015年1月5日
   作    者   : w00167002
   修改内容   : 新增
*****************************************************************************/
typedef struct{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        stSimForbidenInfo;  /* SIM卡中的禁止网络信息 */
    NAS_MML_ROAM_CFG_INFO_STRU                              stRoamCfg;          /* ROAM的定制特性 */
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU                         stPlmnLockCfg;      /* 锁网定制需求,黑名单或白名单 */
    NAS_MML_LTE_INTERNATION_ROAM_CFG_STRU                   stLteRoamCfg;       /* LTE国际漫游定制特性 */
    NAS_MML_RAT_FORBIDDEN_STATUS_STRU                       stRatFirbiddenStatusCfg;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;/* 去使能LTE能力标记 */
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;
    VOS_UINT32                                              ulDisableLteRoamFlg;/* 禁止LTE漫游导致的disable LTE标记 */
}NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU;



/*****************************************************************************
 结构名    : NAS_MMC_LOG_OOS_PLMN_SEARCH_STRATEGY_RELATED_INFO_STRU
 结构说明  : 输出History/PrefBand/FullBand选网状态机上下文相关的可维可测信息结构体
 1.日    期   : 2015年10月10日
   作    者   : h00281185
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU              stSearchTypeStrategyInfo;
    NAS_MMC_GET_GEO_INFO_STRU                               stGetGeoInfo;
}NAS_MMC_LOG_OOS_PLMN_SEARCH_STRATEGY_RELATED_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU
 结构说明  : 输出选网状态机上下文相关的可维可测信息结构体
 1.日    期   : 2015年6月5日
   作    者   : w00167002
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                           stMsgHeader;                      /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                 ucAbortFlg;                       /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    VOS_UINT8                                 ucRelRequestFlg;                  /* 是否主动请求连接是否,VOS_TRUE:是主动请求, VOS_FALSE:被动等待释放 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8           ucInterSysSuspendRat;             /* 记录异系统状态机发起时的接入技术，如等注册结果时从G切换到W */
    VOS_UINT8                                 ucSrvTrigPlmnSearchFlag;          /* 是否存在业务触发搜网标识，VOS_TRUE:存在；VOS_FALSE:不存在*/
    NAS_MMC_PLMN_SELECTION_REG_RSLT_INFO_STRU stRegRlstInfo;                    /* 保存选网状态机中注册结果信息 */
    NAS_MMC_RAT_SEARCH_INFO_STRU              astSearchRatInfo[NAS_MML_MAX_RAT_NUM];  /* 保存不同接入技术的搜索信息 */
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU  stForbRoamLaInfo;
    NAS_MML_PLMN_ID_STRU                      stForbGprsPlmn;                   /* "forbidden PLMNs for GPRS service"  */
    NAS_MML_PLMN_ID_STRU                      stCsPsMode1ReCampLtePlmn;         /* 保存当前L网络的PLMNID */
    NAS_MML_PLMN_WITH_RAT_STRU                stCurrSearchingPlmn;              /* 当前正在尝试的网络及其接入技术,用于at+cops=0 9074 nv项开启打断时判断当前正在搜索的网络是否为hplmn */
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32      enCurrSearchingType;              /* 用于区别指定搜，history搜 */
    VOS_UINT8                                 ucExistRplmnOrHplmnFlag;          /* 接入层上报的searched plmn info是否存在rplmn和hplmn标识 */
    VOS_UINT8                                 aucReserve[3];
}NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU
 结构说明  : 输出L1 MAIN状态机上下文相关的可维可测信息结构体
 1.日    期   : 2015年6月5日
   作    者   : w00167002
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                           stMsgHeader;                      /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MMC_L1_MAIN_REG_RSLT_INFO_STRU        stRegRsltInfo;                    /* 保存搜网状态机注册结果信息 */
    VOS_UINT32                                ulCurTimerCount;                  /* 当前Available Timer启动次数 */
    VOS_UINT32                                ulCurHighRatHplmnTimerCount;      /* 当前high prio rat hplmn Timer启动次数 */
    VOS_UINT32                                ulCurNcellSearchTimerCount;       /* 当前ncell快速搜网启动次数 */
    VOS_UINT32                                ulCurHistorySearchTimerCount;     /* 当前history搜网启动次数 */
    VOS_UINT32                                ulCurPrefBandSearchTimerCount;    /* 当前PrefBand搜网启动次数 */
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8   enAvailableTimerType;
    VOS_UINT8                                 aucReserved[3];
}NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU
 结构说明  : 禁止LA有效时长列表相关的可维可测信息结构体
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU    stForbLaWithValidPeriodCfg;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU             stForbLaWithValidPeriod;
}NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_TIMER_INFO_STRU
 结构说明  : log出MMC定时器运行情况
 1.日    期   : 2011年7月20日
   作    者   : zhoujun 40661
   修改内容   : 新建

 2.日    期   : 2011年10月24日
   作    者   : w00167002
   修改内容   : 增加定时器的时长LOG
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucReserve;
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId;


    VOS_UINT32                          ulTimerRemainLen;/* 定时器的时长 */
}NAS_MMC_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_GET_CACHE_FILE_STRU
 结构说明  : 调用USIMM_GetCachedFile接口，勾消息

 修改记录  :
 1.日    期   : 2012年06月30日
   作    者   : l60609
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */
    VOS_UINT32                          ulFileLen;                              /* 文件长度 */
    VOS_UINT8                           aucFileContent[4];                      /* 文件内容 */
}NAS_MMC_GET_CACHE_FILE_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_DRX_TIMER_STAUTS_STRU
 结构说明  : 调用OM的接口

 修改记录  :
 1.日    期   : 2012年11月9日
   作    者   : z40661
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */
    VOS_UINT8                           ucDrxTimerStatus;                       /*  DRX定时器的状态 */
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_DRX_TIMER_STAUTS_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_PLATFORM_RAT_CAP_STRU
 结构说明  : 调用OM的接口

 修改记录  :
 1.日    期   : 2012年12月29日
   作    者   : s00217060
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */
    NAS_MML_PLATFORM_RAT_CAP_STRU       stPlatformRatCap;                       /*  平台接入能力 */
}NAS_MMC_PLATFORM_RAT_CAP_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  NAS_MMC_LogMmcFsmInfo( VOS_VOID );

#if (FEATURE_LTE == FEATURE_ON)
VOS_VOID  NAS_MMC_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
);
#endif

VOS_VOID  NAS_MMC_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID NAS_MMC_SndOutsideFixedContextData( VOS_VOID );


VOS_VOID NAS_MMC_SndPcRepalyCtxInfo(
    NAS_MMC_OUTSIDE_CONTEXT_TYPE_ENUM_UINT32                ulContextType
);

VOS_VOID NAS_MMC_SndOutsideContextData( VOS_VOID );

/* Modified by wx270776 for OM融合, 2015-7-10, begin */
VOS_VOID NAS_MMC_SndOmOtaCnf(
    VOS_UINT32                          ulErrCode,
    OM_NAS_OTA_REQ_STRUCT              *pstOtaReq
);
/* Modified by wx270776 for OM融合, 2015-7-10, end */

VOS_VOID NAS_MMC_SndOmInquireCnfMsg(
    ID_NAS_OM_INQUIRE_STRU             *pstOmInquireMsg
);

VOS_VOID  NAS_MMC_ConvertPlmnIdToOmDispalyFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    PLMN_ID_STRUCT                     *pstOmPlmnIdFormat
);

VOS_VOID NAS_MMC_SndOmPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
);

VOS_VOID NAS_MMC_LogPlmnRegRejInfo(VOS_VOID);
VOS_VOID NAS_MMC_LogCurrPlmnRelatedInfo(VOS_VOID);

VOS_VOID NAS_MMC_LogRplmnRelatedInfo(VOS_VOID);
VOS_VOID NAS_MMC_LogForbiddenPlmnRelatedInfo(VOS_VOID);
VOS_VOID NAS_MMC_LogRplmnCfgInfo(VOS_VOID);

VOS_VOID NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(
    NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU *pstFsmPlmnSelectionCtx
);
VOS_VOID NAS_MMC_LogFsmL1MainCtxRelatedInfo(
    NAS_MMC_FSM_L1_MAIN_CTX_STRU       *pstFsmL1MainCtx
);
VOS_VOID NAS_MMC_LogOosPlmnSearchStrategyRelatedInfo(VOS_VOID);

VOS_VOID NAS_MMC_LogForbLaWithValidPeriodListInfo(VOS_VOID);

VOS_VOID  NAS_MMC_SndOmMmcTimerStatus(
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus,
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulTimerRemainLen
);

VOS_VOID NAS_MMC_SndOmEquPlmn(VOS_VOID);

VOS_VOID  NAS_MMC_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
);


VOS_VOID NAS_MMC_SndOmInternalMsgQueueDetailInfo(
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pInternalMsgQueue
);

VOS_VOID  NAS_MMC_SndOmGetCacheFile(
    VOS_UINT32                          ulFileId,
    VOS_UINT32                          ulFileLen,
    VOS_UINT8                          *pucFileContent
);


VOS_VOID  NAS_MMC_SndDrxTimerInfo( VOS_UINT8 ucDrxTimerStatus );

VOS_VOID  NAS_MMC_SndOmPlatformRatCap( VOS_VOID );

NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32 NAS_MMC_GetPlmnHUOType(NAS_MML_PLMN_ID_STRU *pstPlmn);


#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID  NAS_MMC_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
 );
VOS_VOID  NAS_MMC_SndAcpuOmFtmRptInd(
    VOS_UINT8                           *pucTmsi,
    VOS_UINT32                           ulLen
);
VOS_VOID NAS_MMC_SndAcpuOmCurTmsi(VOS_VOID);
VOS_VOID NAS_MMC_SndAcpuOmCurPtmsi(VOS_VOID);
#endif


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

