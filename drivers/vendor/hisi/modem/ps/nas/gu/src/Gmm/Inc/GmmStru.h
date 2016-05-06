/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmExt.h
  Description : WUEPS系统NAS内部GMM功能模块结构体定义
  History     :
      1.  张志勇  2003.12.05  文件作成
      2.  张志勇  2004.10.23  CK,IK的存储结构改为字节流
      3.  l40632  2006.06.08  根据问题单A32D04196修改
  4.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  5.日    期   : 2006年11月20日
    作    者   : s46746
    修改内容   : 创建，根据问题单号：A32D07433
  6.日    期   : 2007年03月20日
    作    者   : x51137
    修改内容   : A32D09192
  7.日    期   : 2007年3月30日
    作    者   : s46746
    修改内容   : 问题单号:A32D09854
  8.日    期   : 2007年06月16日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D11635,gas上报GPRS RESUME FAILURE时,仍然通知
                 RABM 恢复成功,如果存在PDP激活时,发起RAU,如果在这个RAU过程中系
                 统消息指示RAI发生改变就不再发起RAU.
  9.日    期   : 2007年10月16日
    作    者   : l65478
    修改内容   : 问题单号:A32D11957
 10.日    期   : 2007年10月27日
    作    者   : luojian id:107747
    修改内容   : 根据问题单号：A32D13038
 11.日    期   : 2007年12月18日
    作    者   : luojian id:107747
    修改内容   : 根据问题单号：A32D13917
 12.日    期   : 2007年12月21日
    作    者   : l00107747
    修改内容   : 问题单A32D13950,W支持CS&PS,G下不支持PS，切换到W模式后GMM没有发起联合RAU
 13.日    期   : 2008年9月18日
    作    者   : ouyangfei 00132663
    修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
 14.日    期   : 2008年9月23日
    作    者   : o00132663
    修改内容   : 根据问题单号：AT2D05839,清除无用全局变量 ucRlsMsgFlg和状态GMM_REGISTERED_WAIT_FOR_RAU
 25.日    期   : 2009年02月13日
    作    者   : o00132663
    修改内容   : 问题单号:AT2D08906,【TA 认证】【外场用例-HK】smartone UE没有处于attach状态,就发起了业务请求.
 26.日    期   : 2009年5月9日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
 27.日    期   : 2009年7月23日
    作    者   : s46746
    修改内容   : 根据问题单号：AT2D12878，GSM下HPLMN搜索时接收到GPRS寻呼或PDP激活(W下PDP激活相同处理)请求需要能及时响应
 28.日    期   : 2009年10月12日
    作    者   : s46746
    修改内容   : 根据问题单号：AT2D14959，GMM向MMC发送RAU、Attach成功的假流程时，没有携带EPLMN列表
 29.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
 30.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，删除GMM/MM/MMC关于NVIM_EPLMN的冗余定义
*******************************************************************************/
#ifndef _GMMSTRUCTURE_H_
#define _GMMSTRUCTURE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "GmmCasDef.h"
#include "NasMmlCtx.h"
#include "GmmDef.h"
#include "SmGmmInterface.h"

#pragma pack(4)
/******************************************************************************/
/**************************** GMM全局控制信息 *********************************/
/******************************************************************************/

/*****************************************************************************
 枚举名    : NAS_GMM_SPEC_PROC_TYPE_ENUM
 结构说明  : GMM流程定义
*****************************************************************************/
enum NAS_GMM_SPEC_PROC_TYPE_ENUM
{
    GMM_NULL_PROCEDURE                  = 0x00,                                 /* 没有流程                                 */

    GMM_ATTACH_COMBINED                 = 0x10,                                 /* combined attach                          */
    GMM_ATTACH_WHILE_IMSI_ATTACHED      = 0x11,                                 /* GPRS attach while IMSI attached          */
    GMM_ATTACH_NORMAL                   = 0x12,                                 /* normal attach                            */
    GMM_ATTACH_NORMAL_CS_TRANS          = 0x13,                                 /* CS通信中的normal attach(A+I)             */

    GMM_RAU_COMBINED                    = 0x20,                                 /* combined RAU                             */
    GMM_RAU_WITH_IMSI_ATTACH            = 0x21,                                 /* combined RAU with IMSI attach            */
    GMM_RAU_NORMAL                      = 0x22,                                 /* normal RAU                               */
    GMM_RAU_NORMAL_CS_TRANS             = 0x23,                                 /* CS通信中的normal RAU(A+I)                */
    GMM_RAU_NORMAL_CS_UPDATED           = 0x24,

    GMM_DETACH_COMBINED                 = 0x30,                                 /* GPRS/IMSI detach without switching off   */
    GMM_DETACH_NORMAL                   = 0x31,                                 /* GPRS detach without switching off        */
    GMM_DETACH_WITH_IMSI                = 0x32,                                 /* IMSI detach                              */
    GMM_DETACH_COMBINED_POWER_OFF       = 0x33,                                 /* GPRS/IMSI detach with switching off      */
    GMM_DETACH_NORMAL_POWER_OFF         = 0x34,                                 /* GPRS detach with switching off           */
    GMM_DETACH_COMBINED_SIM_REMOVE      = 0x35,                                 /* GPRS/IMSI detach with switching off      */
    GMM_DETACH_NORMAL_SIM_REMOVE        = 0x36,                                 /* GPRS detach with switching off           */
    GMM_DETACH_NORMAL_NETMODE_CHANGE    = 0x37,                                 /* GPRS detach with netmode change          */

    GMM_SERVICE_REQUEST_DATA_IDLE       = 0x40,                                 /* PMM-IDLE下触发的service request(data)    */
    GMM_SERVICE_REQUEST_DATA_CONN       = 0x41,                                 /* PMM-CONNECTED下触发service request(data) */
    GMM_SERVICE_REQUEST_SIGNALLING      = 0x42,                                 /* service request(signalling)              */
    GMM_SERVICE_REQUEST_PAGING_RSP      = 0x43,                                 /* service request(paging response)         */

    GMM_ABORT_CURRENT_SERVICE           = 0x5f,                                 /* abort current service                    */
    NAS_GMM_SPEC_PROC_TYPE_BUTT
};

typedef VOS_UINT8   NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名      : NAS_GMM_LINK_CTRL_STRU
 结构说明    : GMM RRC连接和PS信令连接控制
*****************************************************************************/
typedef struct
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucCurrentProc;                          /* 当前流程 */
    VOS_UINT8                           ucExistedRrcConn;                       /* 流程是否建立在已存在的RRC连接上 */
    VOS_UINT8                           ucExistedPsSignallingConn;              /* 流程是否建立在已存在的PS信令连接上 */
    VOS_UINT8                           ucSmcOrFirstNasMsgRcvdFlg;              /* 是否从网测收到Security Mode Command或者NAS层消息 */
}NAS_GMM_LINK_CTRL_STRU;



typedef struct
{
    VOS_UINT8                               aucMccDigit[3];                         /* INTEGER(0..9)                            */
    VOS_UINT8                               ucMncCnt;                               /* MNC的个数                                */
    VOS_UINT8                               aucMncDigit[3];                         /* INTEGER(0..9)                            */
}GMM_PLMN_ID_STRU;

typedef struct
{
    VOS_UINT32             ulMcc;
    VOS_UINT32             ulMnc;
}GMM_PLMN_ID_U32_STRU;

typedef struct
{
    GMM_PLMN_ID_STRU                        PlmnId;
    VOS_UINT8                               aucLac[2];                              /* The LAC field consists of 16 bits.       *
                                                                                 * Bit 8 in octet 1 is the most significant *
                                                                                 * bit and bit 1 in octet 2 is the least    *
                                                                                 * significant bit.                         */
}GMM_LAI_STRU;

typedef struct
{
    GMM_LAI_STRU                            Lai;
    VOS_UINT8                               ucRac;                                  /* BIT STRING(SIZE(8))                      */
}GMM_RAI_STRU;


/* 系统信息 */
typedef struct
{
    GMM_RAI_STRU                            Rai;                                    /* RAI                                      */
    VOS_UINT8                               ucNetMod;                               /* 网络模式                                 */
    VOS_UINT8                               ucPsDrxLen;                             /* PS域的DRX length系数                     */
                                                                                /* ucPsDrxLen取值范围0（无效值），6～9 */

#define GMM_NO_FORBIDDEN                    MMC_GMM_NO_FORBIDDEN                  /* 不在任何禁止列表中                       */
#define GMM_FORBIDDEN_PLMN                  MMC_GMM_FORBIDDEN_PLMN                /* 在forbidden PLMN list上                  */
#define GMM_FORBIDDEN_PLMN_FOR_GPRS         MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS       /* 在forbidden PLMN for GPRS list上         */
#define GMM_FORBIDDEN_LA_FOR_ROAM           MMC_GMM_FORBIDDEN_LA_FOR_ROAM         /* 在forbidden LA for roaming上             */
#define GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS   MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS /* 在forbidden LA for regional provision of *
                                                                                 * service上                                */
    VOS_UINT8                               ucForbMask;                             /* 是否在禁止列表中                         */

    VOS_UINT8                               ucSysValidFlg;                          /* 系统信息是否有效标志                     */


#define GMM_NOT_SUPPORT_GPRS                1                                    /* 当前小区不支持GPRS                       */
#define GMM_SUPPORT_GPRS                    0                                    /* 当前小区支持GPRS                         */
    VOS_UINT8                               ucNotSupportGprs;                       /* 当前小区是否支持GPRS标志                 */
    VOS_UINT16                              usGsmCellId;           /* 当前小区ID, only for GSM */
    VOS_UINT8                               ucNtType;              /* 记录系统消息来自于GSM或WCDMA网中 */
    VOS_UINT32                              ulCellId;
    VOS_UINT8                               ucCellChgFlg;
}GMM_SYS_INFO_STRU;

/* PS域的安全信息 */
typedef struct
{
#define GMM_CIPHER_ALGO_UEA0    0
#define GMM_CIPHER_ALGO_UEA1    1
    VOS_UINT8                   ucCiperAlgor;               /*3000接口该数据域无效*/
}GMM_PS_SECURITY_INFO_STRU;


#define  GMM_MAX_SIZE_IMEISV                                        16
#if (FEATURE_ON == FEATURE_LTE)
#define  NAS_GMM_LMM_TOKEN_LEN                                      32
#endif
typedef struct
{
#define    GMM_UEID_INVALID                                   0x00

#define    GMM_UEID_IMSI                                      0x01
#define    GMM_UEID_P_TMSI                                    0x02
#define    GMM_UEID_P_TMSI_SIGNATURE                          0x04
    VOS_UINT8                               ucUeIdMask;                             /* UeId存在标识                             */

    VOS_UINT8       aucImeisv[GMM_MAX_SIZE_IMEISV];                                 /* IMEISV                                   */
}GMM_UEID_STRU;

/* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*此定义移到LMM中*/
#define GMM_NON_DRX_TIMER_MAX           7
/* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */


/* GMM_MSG_HOLD_STRU: ulMsgHoldMsk取值 */
#define                 GMM_MSG_HOLD_FOR_ATTACH    0x00000001
#define                 GMM_MSG_HOLD_FOR_RAU       0x00000002
#define                 GMM_MSG_HOLD_FOR_DETACH    0x00000004
#define                 GMM_MSG_HOLD_FOR_SERVICE   0x00000008
#define                 GMM_MSG_HOLD_FOR_PAGING    0x00000010
#define                 GMM_MSG_HOLD_FOR_SM        0x00000020
#define                 GMM_MSG_HOLD_FOR_POWEROFF  0x00000040
#define                 GMM_MSG_HOLD_FOR_SMS       0x00000080

#define                 GMM_MSG_HOLD_FOR_GSM_SYSINFO       (0x00000100)

/* 此标志用来在如下场景时用来保存系统消息: PS建链过程中发生RA改变，
该场景中如果CS域有业务则PS域做RAU会被不确定的推迟到CS连接释放时才做，
修改此场景中的操作如下:若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放
连接，并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU */
#define                 GMM_MSG_HOLD_FOR_WAS_SYSINFO     (0x00000200)

/* 消息保留数据结构 */
typedef struct{
    VOS_UINT32                               ulMsgHoldMsk;                           /* 有无消息被缓存的标志，                   *
                                                                                 * 每一个bit代表一种被缓存的流程            */
    VOS_UINT32                               ulMsgAddrForAttach;                     /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForRau;                        /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForDetach;                     /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForService;                    /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForPaging;                     /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForSm;                         /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForPowerOff;                   /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForSMS;                        /* 被缓存的消息的首地址                     */
    VOS_UINT32                               ulMsgAddrForGsmSysinfo;                 /* 被缓存的消息的首地址                     */

    VOS_UINT32                               ulMsgAddrForWasSysinfo;

    VOS_UINT8                                ucHandleRauFlg;                         /* 流程结束后要触发RAU的标志                */
    VOS_UINT8                                ucInitiateLuFlg;                        /* GMM不能进行RAU时，是否要触发MM的LU过程的
                                                                                 * 标志                                     */
    VOS_UINT8                                ucMmT3211ExpiredDelayRauFlag;      /* 缓存收到MM T3211超时消息需要延迟做rau标识*/
    VOS_UINT8                                ucReserved;

}GMM_MSG_HOLD_STRU;


/* UE信息 */
typedef struct
{
    VOS_UINT8                               ucUpdateSta;                            /* 更新状态                                 */

#define  GMM_MAX_SIZE_NET_CAPABILITY        9
    VOS_UINT8                               ucReserved[2];

#define  GMM_NOT_SUPPORT_INFORMATION_MSG    0
#define  GMM_SUPPORT_INFORMATION_MSG        1
    VOS_UINT8                               ucSupportInfoFlg;                       /* 是否支持GMM INFORMATION消息标志          */
    VOS_UINT8                               aucRadioCpb[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];
    VOS_UINT8                               aucTdsRadioCpb[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];/* TD下rac能力信息 */
#if (FEATURE_ON == FEATURE_LTE)


    NAS_MML_PLMN_RAT_PRIO_STRU              stRadioCpbRelatedRatList;          /* 当前RadiocCapability对应的接入技术列表  */

#endif


    GMM_UEID_STRU                           UeId;

    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
    /* PS域的DRX parameter 定义，从GMM移至MML中，这里记录上次Attach或者RAU时Drx参数的携带状态*/
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8              enLatestAttachOrRauContainDrx;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
    VOS_UINT8                                               ucMsRadioCapSupportLteFromRegReq;   /* ATTACH或RAU时携带的MS Radio Access capability IE是否支持LTE,VOS_TRUE:支持LTE,VOS_FALSE:不支持LTE */
    VOS_UINT8                                               ucMsRadioCapSupportLteFromAs;       /* 记录GAS接入层发送的GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND或GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND
                                                                                                  是否支持LTE,VOS_TRUE:支持L；VOS_FALSE:不支持L */
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainFromRegReq;            /* 记录发起ATTACH或RAU时的voice domain */

}GMM_UE_INFO_STRU;

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 结构名    : GMM_MAPPED_INFO_FROM_EPS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 从L模获取的信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUeIdMask;                             /* UeId存在标识                             */
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];           /* BIT STRING(SIZE(32))                     */
    VOS_UINT8                           aucPtmsiSignature[NAS_MML_MAX_PTMSI_SIGNATURE_LEN];
    GMM_RAI_STRU                        Rai;
    VOS_UINT8                           aucNasToken[NAS_GMM_LMM_TOKEN_LEN];
}GMM_MAPPED_INFO_FROM_EPS_STRU;
#endif




/* CS域的相关信息 */
typedef struct
{
    VOS_UINT8                               ucCsTransFlg;                           /* CS域是否通信中标志                       */

}GMM_CS_INFO_STRU;

typedef struct
{
    VOS_UINT8                               ucYear;                                 /* 年                                       */
    VOS_UINT8                               ucMonth;                                /* 月                                       */
    VOS_UINT8                               ucDay;                                  /* 日                                       */
    VOS_UINT8                               ucHour;                                 /* 小时                                     */
    VOS_UINT8                               ucMinute;                               /* 分钟                                     */
    VOS_UINT8                               ucSecond;                               /* 秒                                       */
    VOS_UINT8                               ucTimeZone;                             /* 时区                                     */
}GMM_UNIV_TIME_LOC_TIME_ZONE_STRU;


/* GMM infomation */
typedef struct
{
    VOS_UINT8                               ucFullNameLen;                          /* Full name for network的长度              */
#define     GMM_MAX_SIZE_FULL_NAME_FOR_NETWORK                8
    VOS_UINT8       aucFullNtName[GMM_MAX_SIZE_FULL_NAME_FOR_NETWORK];              /* Full name for network                    */
    VOS_UINT8                               ucShortNameLen;                         /* Short name for network的长度             */
#define     GMM_MAX_SIZE_SHORT_NAME_FOR_NETWORK               4
    VOS_UINT8       aucShortNtName[GMM_MAX_SIZE_SHORT_NAME_FOR_NETWORK];            /* Short name for network                   */
#define     GMM_UNIVERSAL_TIME                 0x01
#define     GMM_LOCAL_TIME_ZONE                0x02
#define     GMM_DAYLIGHT_TIME                  0x04
    VOS_UINT32                               ulInfoMsk;                              /* Information中各个IE有无标志，            *
                                                                                 * 每一个bit代表一个IE                      */

    GMM_UNIV_TIME_LOC_TIME_ZONE_STRU        UnivTime;                               /* Universal time and local time zone       */
    VOS_UINT8                               ucLocTimeZone;                          /* Local time zone                          */
    VOS_UINT8                               ucSavTime;                              /* Network Daylight Saving Time             */
    VOS_UINT8                               ucLsaIdLen;                             /* Length of LSA Identifier contents        */
    VOS_UINT8                               aucLsaId[3];                            /* LSA Identifier                           */
}GMM_INFO_STRU;

/* GMM状态  */
#define     GMM_NULL                                          0x00              /* GMM_NULL状态                             */
#define     GMM_REGISTERED_INITIATED                          0x01              /* GMM-REGISTERED-INITIATED状态             */
#define     GMM_DEREGISTERED_INITIATED                        0x02              /* GMM_DEREGISTERED_INITIATED               */
#define     GMM_ROUTING_AREA_UPDATING_INITIATED               0x03              /* GMM_ROUTING_AREA_UPDATING_INITIATED      */
#define     GMM_SERVICE_REQUEST_INITIATED                     0x04              /* GMM-SERVICE-REQUEST-INITIATED            */

#define     GMM_TC_ACTIVE                                     0x05              /* GMM-TC-ACTIVE(进行TC时的状态)            */
#define     GMM_GPRS_SUSPENSION                               0x06              /* (GSM only)GMM_GPRS_SUSPENSION */

#define     GMM_DEREGISTERED_NORMAL_SERVICE                   0x10              /* GMM-DEREGISTERED.NORMAL-SERVICE          */
#define     GMM_DEREGISTERED_LIMITED_SERVICE                  0x11              /* GMM-DEREGISTERED.LIMITED-SERVICE         */
#define     GMM_DEREGISTERED_ATTACH_NEEDED                    0x12              /* GMM-DEREGISTERED.ATTACH-NEEDED           */
#define     GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH             0x13              /* GMM-DEREGISTERED.ATTEMPTING-TO-ATTACH    */
#define     GMM_DEREGISTERED_NO_CELL_AVAILABLE                0x14              /* GMM-DEREGISTERED.NO-CELL-AVAILABLE       */
#define     GMM_DEREGISTERED_PLMN_SEARCH                      0x15              /* GMM-DEREGISTERED.PLMN-SEARCH             */
#define     GMM_DEREGISTERED_NO_IMSI                          0x16              /* GMM-DEREGISTERED.NO-IMSI                 */

#define     GMM_REGISTERED_NORMAL_SERVICE                     0x20              /* GMM-REGISTERED.NORMAL-SERVICE            */
#define     GMM_REGISTERED_LIMITED_SERVICE                    0x21              /* GMM-REGISTERED.LIMITED-SERVICE           */
#define     GMM_REGISTERED_UPDATE_NEEDED                      0x22              /* GMM-REGISTERED.UPDATE-NEEDED             */
#define     GMM_REGISTERED_ATTEMPTING_TO_UPDATE               0x23              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE      */
#define     GMM_REGISTERED_NO_CELL_AVAILABLE                  0x24              /* GMM-REGISTERED.NO-CELL-AVAILABLE         */
#define     GMM_REGISTERED_PLMN_SEARCH                        0x25              /* GMM-REGISTERED.PLMN-SEARCH               */
#define     GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM            0x26              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
#define     GMM_REGISTERED_IMSI_DETACH_INITIATED              0x27              /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */

#define     GMM_SUSPENDED_NORMAL_SERVICE                      0x30              /* GMM-SUSPENDED.NORMAL-SERVICE             */
#define     GMM_SUSPENDED_GPRS_SUSPENSION                     0x31              /* GMM-SUSPENDED.GPRS-SUSPENSION            */
#define     GMM_SUSPENDED_WAIT_FOR_SYSINFO                    0x32              /* GMM-SUSPENDED.WAIT-FOR-SYSINFO           */

typedef VOS_UINT8   GMM_STATE_TYPE_UINT8;

#define     GMM_NET_MODE_I                                    1                 /* 网络模式I                                */
#define     GMM_NET_MODE_II                                   2                 /* 网络模式II                               */
#define     GMM_NET_MODE_III                                  3                 /* 网络模式III                              */
typedef VOS_UINT8   GMM_NET_MODE_TYPE_UINT8;


#define  GMM_REAL_PROCEDURE        MMC_GMM_REAL_PROCEDURE                       /* 真正发起流程                             */
#define  GMM_UNREAL_PROCEDURE      MMC_GMM_UNREAL_PROCEDURE                     /* 没有真正发起流程                         */

typedef struct
{
    VOS_UINT8                           ucSndDetachCnt;
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulEstResult;           /* 关机时信令连接建立结果 */
}GMM_POWER_OFF_CTRL_STRU;

enum GMM_SERVICE_REQ_TYPE_ENUM
{
    GMM_SERVICE_REQ_NONE                  = 0,                /* 表示搜网过程中没有服务请求 */
    GMM_SERVICE_REQ_PAGING                = 1,                /* 表示搜网过程中接收到paging消息 */
    GMM_SERVICE_REQ_PDPACT                = 2,                /* 表示搜网过程中接收到PDP激活请求 */
    GMM_SERVICE_REQ_BUTT
};
typedef VOS_UINT8 GMM_SERVICE_REQ_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名     : GMM_BACKUP_SHARE_STRU
 结构说明   : 对GMM中一些参数进行备份恢复，目前只有CCO流程会用到
 1.日    期  : 2011年6月30日
   作    者  : w00176964
   修改内容  : 新建
 2.日    期   : 2012年03月08日
   作    者   : l00130025
   修改内容   : DTS2012030107623: G->W Est_Rej_Cogest,CCO回退过程，需要保存Eplmn
 3.日    期   : 2013年09月24日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseII 项目:增加SIM卡中的PS安全上下文的备份恢复
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucState;                                /* GMM状态*/
    VOS_UINT8                                   ucNtMod;                                /* 网络模式*/
    VOS_UINT8                                   ucPsSigConnFlg;                         /* PS域信令连接是否存在标志 */
    NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8    enPsIntegrityProtect;                   /* 完整性保护信息 */
    VOS_UINT8                                   ucRauAttmptCnt;                         /* RAU attempt counter                      */
    GMM_GPRS_SRV_STATE                          ucSrvState;                             /* 当前GMM GPRS服务状态 */
    GMM_PS_SECURITY_INFO_STRU                   stPsSecutityInfo;                       /* PS域的security information*/
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, begin */
    NAS_MML_SIM_PS_SECURITY_INFO_STRU           stSimPsSecurity;                        /* SIM卡中的PS域的安全参数 */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */
    GMM_SYS_INFO_STRU                           stSysInfo;                              /* 当前系统消息 */
    GMM_UE_INFO_STRU                            stUeInfo;                               /* UE 信息                                  */

    NAS_MML_EQUPLMN_INFO_STRU                   stBackupEquPlmnInfo;

    NAS_MML_TIN_TYPE_ENUM_UINT8                 enTinType;                              /* TIN类型*/
    VOS_UINT8                                   ucT3311Status;
    VOS_UINT8                                   aucReserved[2];
}GMM_BACKUP_SHARE_STRU;

/*****************************************************************************
 枚举名    : NAS_GMM_ATTACH_TYPE_ENUM
 结构说明  : 等待ATTACH结果的类型
 1.日    期   : 2011年6月30日
   作    者   : w00166186
   修改内容   : 新建结构
*****************************************************************************/
enum NAS_GMM_ATTACH_TYPE_ENUM
{
    GMM_WAIT_NULL_ATTACH  = 0,
    GMM_WAIT_PS_ATTACH,
    GMM_WAIT_CS_ATTACH,
    GMM_WAIT_CS_PS_ATTACH,
    GMM_WAIT_ATTACH_BUTT
};
typedef VOS_UINT8 NAS_GMM_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_GMM_DETACH_TYPE_ENUM
 结构说明  : 等待DETACH结果的类型
 1.日    期   : 2011年6月30日
   作    者   : w00166186
   修改内容   : 新建结构
*****************************************************************************/
enum NAS_GMM_DETACH_TYPE_ENUM
{
    GMM_WAIT_NULL_DETACH = 0,
    GMM_WAIT_PS_DETACH,
    GMM_WAIT_CS_DETACH,
    GMM_WAIT_CS_PS_DETACH,
    GMM_WAIT_DETACH_BUTT
};

typedef VOS_UINT32 NAS_GMM_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : GMM_ATTACH_INFO_STRU
 结构说明  : GMM等待ATTACH结果的信息
 1.日    期   : 2011年6月30日
   作    者   : w00166186
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulOpid;                                 /* MMA生成和使用 */
    NAS_GMM_ATTACH_TYPE_ENUM_UINT32     enAttachType;                           /* 等待ATTACH响应消息的类型 */
}NAS_GMM_ATTACH_INFO_STRU;

/*****************************************************************************
 结构名    : GMM_ATTACH_INFO_STRU
 结构说明  : GMM等待DETACH结果的信息
 1.日    期   : 2011年6月30日
   作    者   : w00166186
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulOpid;                                 /* MMA生成和使用 */
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType;                           /* 等待DETACH响应消息的类型                 */
}NAS_GMM_DETACH_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_GMM_NVIM_TIN_INFO_STRU
 结构说明  : en_NV_Item_TIN_INFO NV项结构
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;                              /* TIN类型 */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_MML_MAX_IMSI_LEN];          /* 上次保存的IMSI的内容 */
}NAS_GMM_NVIM_TIN_INFO_STRU;

/*****************************************************************************
 枚举名    : NAS_GMM_LOG_OM_INFO_ENUM
 结构说明  : 可维可测消息id
 1.日    期   : 2012年3月17日
   作    者   : z00161729
   修改内容   : 新建结构
 2.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,新增ps注册携带DRX参数改变
*****************************************************************************/
enum NAS_GMM_LOG_OM_INFO_ENUM
{
    NAS_GMM_LOG_GUTI_INFO_IND       = 0xa00,
    NAS_GMM_LOG_TIN_TYPE_INFO_IND,
    NAS_GMM_LOG_PS_REG_DRX_INFO_IND,
    NAS_GMM_LOG_BUTT
};
typedef VOS_UINT32 NAS_GMM_LOG_OM_INFO_ENUM_UINT32;

/*****************************************************************************
 结构名    : NAS_GMM_LOG_TIN_INFO_STRU
 结构说明  : GMM TIN值更新时通知om勾消息，可维可测使用
  1.日    期   : 2012年3月17日
    作    者   : z00161729
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;                              /* TIN类型 */
    VOS_UINT8                           aucReserve[3];
}NAS_GMM_LOG_TIN_INFO_STRU;


/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*****************************************************************************
 结构名    : NAS_GMM_LOG_PS_REG_DRX_INFO_STRU
 结构说明  : ps注册携带DRX参数值更新时通知om勾消息，可维可测使用
  1.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8    enPsRegContainDrx;            /* 是否携带Drx 参数类型*/
    VOS_UINT8                                     aucReserve[3];
}NAS_GMM_LOG_PS_REG_DRX_INFO_STRU;
/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */

/* ucEventCause使用的宏定义 */
#define GMM_EVENT_CAUSE_INVALID      0xff
typedef struct
{
    GMM_MSG_HOLD_STRU                   MsgHold;                                /* 原语保留结构                             */
    GMM_PLMN_ID_U32_STRU                aEquPlmnIdList[15];                     /* 保存RAU Accept消息中的Equ Plmn信息，假流程中使用 */
    VOS_UINT8                           ucEquPlmnNum;
    GMM_STATE_TYPE_UINT8                ucState;                                /* GMM状态                                  */
    VOS_UINT8                           ucServPreSta;                           /* 保留SERVICE REQ流程发生前的GMM状态       */
    VOS_UINT8                           ucPlmnSrchPreSta;                       /* 搜网前的状态 */
    GMM_NET_MODE_TYPE_UINT8             ucNetMod;                               /* 网络模式                                 */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProc;                             /* 当前进行的specific流程                   */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProcHold;                         /* 保留的specific流程                       */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProcInCsTrans;                    /* CS通信中进行的specific流程               */
    VOS_UINT8                           ucSigConFlg;                            /* 信令连接是否存在标志                     */
    VOS_UINT8                           ucFollowOnFlg;                          /* 信令延长使用标志                         */
    VOS_UINT8                           ucCvrgAreaLostFlg;                      /* 是否出覆盖区的标志                       */
    VOS_UINT8                           ucRealProFlg;                           /* 是否真正发起流程标志                     */
    VOS_UINT8                           ucTcPreSta;                             /* 进行TC之前的状态                         */
    VOS_UINT8                           ucCipherStartFlg;                       /* 加密启动标志                             */
    VOS_UINT8                           ucRelCause;                             /* 最后一次信令连接释放原因                 */
    VOS_UINT8                           ucIntegrityProtStart;                   /* 完整性保护启动标志                       */
    VOS_UINT8                           ucGprsResumeFlg;
    VOS_UINT8                           ucSuspendProc;
    VOS_UINT8                           ucRaiChgRelFlg;                         /* 是否是RAI改变导致主动要求释放连接的标志  */
    VOS_UINT8                           ucLaNotAllowFlg;                        /* 记录PS域流程被拒绝后，原因值是否是#12    */
    VOS_UINT8                           ucTime2Sndout;                          /* 当前是否需要导出全局变量供回放 */
    VOS_UINT8                           ucFopFlg;                               /* 记录空口消息中指示是否Follow On PS信令连接的标志 */
    VOS_UINT8                           ucNeedChgServiceStatus;                 /* 是否需要通知MMC改变MMC的服务状态,VOS_TRUE:需要,VOS_FALSE:不需要 */
    VOS_UINT8                           ucEventCause;                           /* 上报OM事件中使用的原因值，此值无效时，使用函数中自带的原因值 */
    GMM_SERVICE_REQ_TYPE_ENUM_UINT8     enServReq;
    GMM_UE_INFO_STRU                    UeInfo;                                 /* UE 信息                                  */
    GMM_SYS_INFO_STRU                   SysInfo;                                /* 上次驻留的系统信息                                 */
    GMM_SYS_INFO_STRU                   SysInfo_Registered;                     /* 成功注册时所在小区的系统信息                                 */
    GMM_PS_SECURITY_INFO_STRU           PsSecutityInfo;                         /* PS域的security information               */
    GMM_CS_INFO_STRU                    CsInfo;                                 /* CS域的相关信息                           */
    GMM_POWER_OFF_CTRL_STRU             stPowerOffCtrl;
    VOS_UINT32                          ulEstCause;                             /* 记录RRC连接建立原因，用途是Follow On流程网侧指示不延长
                                                                                    PS域信令，连接释放之后重新建立RRC连接填写建立原因 */
    VOS_UINT32                          ulGmmAttachFlg;

    NAS_GMM_LINK_CTRL_STRU              stGmmLinkCtrl;                          /* GMM 连接释放管理 */

    VOS_UINT8                           ucInterRatFlg;                          /* 记录在wait for sysinfo状态下收到Gas的挂起时，向RABM发送gprs suspension，*/
                                                                                /* 带参数为handover.在收到Gas的恢复后向RABM发送gprs resume，带参数为handover*/
    VOS_UINT8                           ucUserPsAttachFlag;                     /* AT 发起ATTACH的标志 ,VOS_TRUE表示AT发起了ATTACH,VOS_FALSE表示没有 */
    VOS_UINT16                          usUplinkDataStatus;                     /* 保存RABM发送的GMMRABM_REESTABLISH_REQ消息中的链路状态信息 */
#if( FEATURE_ON == FEATURE_LTE)
    GMM_MAPPED_INFO_FROM_EPS_STRU       stMappedUeInfoFromEps;                  /* 从LMM获取到的信息                            */
#endif
    GMM_BACKUP_SHARE_STRU               stBackupShare;                            /* GMM备份的一些全局变量，目前只在CCO流程用到 */

    NAS_GMM_ATTACH_INFO_STRU            stAttachInfo;                           /* 等待ATTACH结果的信息 */
    NAS_GMM_DETACH_INFO_STRU            stDetachInfo;                           /* 等待DETACH结果的信息 */

    VOS_UINT8                           ucDetachAcceptedFlg;                    /* 标志记录GMM是否刚发送完DETACH ACCEPTED消息给LL */
    VOS_UINT8                           ucRelConnAfterPdpDeact;
    GMM_SM_CAUSE_ENUM_UINT16            enAttach2DetachCause;
    VOS_UINT8                           ucRcvNetDetachFlg;

    VOS_UINT8                           ucIsNeedStartT3340PdpExist;
    VOS_UINT8                           aucReseve[2];

    /* 记录GMM迁到ATTEMPT TO UPDATE状态且update status迁到2时的RAI信息，在开机或ps、csps detach或发起注册时候，则清除该标记 */
    NAS_MML_RAI_STRU                     stAttemptToUpdateRai;

    NAS_MML_PLMN_WITH_RAT_STRU           stAllocT3302ValuePlmnWithRat;  /* 下发T3302定时器时长的网络信息 */
}GMM_GLOBAL_CTRL_STRU;


enum NAS_GMM_SPEC_PROC_ENUM
{
    NAS_GMM_SPEC_PROC_ATTACH  = 0,
    NAS_GMM_SPEC_PROC_RAU        ,
    NAS_GMM_SPEC_PROC_BUTT
};
typedef VOS_UINT8 NAS_GMM_SPEC_PROC_ENUM_UINT8;

/*  获取lMM的安全上下文是 缓存发起 Attach和Rau，以及 RAU的类型 */
typedef struct
{
    NAS_GMM_SPEC_PROC_ENUM_UINT8        enGmmSpecProc;
    VOS_UINT8                           ucRauType;

}GMM_SPEC_PROC_CONTEXT_STRU;


/******************************************************************************/
/*************************** GMM收发原语的管理 ********************************/
/******************************************************************************/

typedef struct
{
#define     GMM_RRC_RRMM_EST_CNF_FLG                          0x01              /* 接收到异常原因时不清该标志               */

#define     GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG             0x02

    VOS_UINT8                               ucCnfMask;                              /* 等待CNF原语的标记                        */
    /* opid使用原则：先加后用 */
    VOS_UINT8                               ucUsimStaOpid;                          /* AGENT_USIM_STATUS_REQ原语中的Opid        */
    VOS_UINT8                               ucRrmmEstOpid;                          /* RRMM_EST_REQ原语中的Opid                 */

}GMM_REQ_CNF_MNG_STRU;



/******************************************************************************/
/*************************** GMM Timer管理 ************************************/
/******************************************************************************/

typedef struct
{
    /* MASK使用说明：定时器启动时usTimerRunMask被置位，usTimerSusMask被清零；
       定时器挂起时usTimerRunMask不变（仍然置位），usTimerSusMask被置位；
       定时器停止时usTimerRunMask被清零；usTimerSusMask被清零。
       当空口消息中更新定时器时长时usTimerValMask被置位，定时器启动时判断，
       如被置位，则调用OS API更新时长，并将usTimerSusMask清零，然后再启动。*/
    VOS_UINT32                               ulTimerRunMask;                         /* TIMER ID 小于32时，Timer启动标记(有哪些Timer在运行)         */
    VOS_UINT32                               ulTimerRunMaskEx;                       /* TIMER ID 32-64 时，Timer启动标记(有哪些Timer在运行)         */
    
    VOS_UINT32                               ulTimerSusMask;                         /* TIMER ID 小于32时，Timer挂起标记(有哪些Timer被挂起)         */
    VOS_UINT32                               ulTimerSusMaskEx;                       /* TIMER ID 32-64时，Timer挂起标记(有哪些Timer被挂起)         */

    VOS_UINT32                               ulTimerSusTcMask;                       /* TIMER ID 小于32时，Timer在TC中挂起标记(有哪些Timer被挂起)   */
    VOS_UINT32                               ulTimerSusTcMaskEx;                     /* TIMER ID 32-64时，Timer在TC中挂起标记(有哪些Timer被挂起)   */

    VOS_UINT32                               ulTimerValMask;                         /* TIMER ID 小于32时，Timer时长更新标记(有哪些Timer时长被更新) */
    VOS_UINT32                               ulTimerValMaskEx;                       /* TIMER ID 32-64时，Timer时长更新标记(有哪些Timer时长被更新) */

    struct{
        HTIMER                               hTimer;                                /* TimerID                                  */
        VOS_UINT32                           ulTimerVal;                             /* Timer时长(单位：毫秒)                    */
        VOS_UINT32                           ulParam;
        VOS_UINT8                            ucMode;
    }aTimerInf[GMM_TIMER_NUM];
}GMM_TIMER_STRU;

/******************************************************************************/
/*************************** ATTACH 部分的数据结构 ****************************/
/******************************************************************************/

typedef struct
{
    VOS_UINT8                              ucAttachAttmptCnt;                       /* ATTACH attempt counter                   */
    VOS_UINT8                              ucT3310outCnt;                           /* T3310溢出次数n                           */
    VOS_UINT8                              ucRetryFlg;                              /* 进入新的小区是否进行attach               */
    VOS_UINT8                              ucSmCnfFlg;                              /* attach结束后,是否使用CNF原语上报给SM     */

    VOS_UINT8                              ucPagingWithImsiFlg;                     /* ATTACH的触发原因是否是收到网侧的IMSI寻呼 */
    VOS_UINT8                              ucRetryAttachForRelCtrlFlg;              /* Attach流程被异常释放，需要在收到系统消息后重新发起 */
    VOS_UINT8                              ucReserve;

}GMM_ATTACH_CTRL_STRU;


/******************************************************************************/
/*************************** RAU 部分的数据结构 *******************************/
/******************************************************************************/
/* 用于备份上行的NPDU信息，在GSM下，在连续两次收到网络的RAU ACCEPT消息时使用 */
#define                 GMM_MAX_SIZE_N_PDU                    17
typedef struct
{
    VOS_UINT8                              ucNpduCnt;                               /* N-PDU Numbers的个数                      */
    VOS_UINT8                              aucNpduNum[GMM_MAX_SIZE_N_PDU];          /* N-PDU Numbers                            */
}GMM_DOWNLINK_NPDU_STRU;

typedef struct
{
    VOS_UINT8                           ucRauAttmptCnt;                          /* RAU attempt counter                      */
    VOS_UINT8                           ucT3330outCnt;                           /* T3330溢出次数n                           */
    VOS_UINT8                           ucCsSpringRauFlg;                        /* MmcCmServiceRejectInd #4 触发RAU的标志   */

    VOS_UINT8                           ucRetryFlg;                              /* 进入新的小区是否进行RAU                  */
    VOS_UINT8                           ucT3312ExpiredFlg;                       /* 出服务区时T3312溢出标志                  */
    VOS_UINT8                           ucPeriodicRauFlg;                        /* 当前RAU是否是周期RAU标志                 */
    VOS_UINT8                           ucNpduCnt;                               /* N-PDU Numbers的个数                      */

    VOS_UINT8                           aucNpduNum[GMM_MAX_SIZE_N_PDU];          /* N-PDU Numbers                            */
    VOS_BOOL                            bNpduPresentInRauAccFlg;
    VOS_UINT8                           ucRetryRauForRelCtrlFlg;                 /* 当RAU流程被异常释放后，是否需要重新发起标志 */
    VOS_UINT8                           ucT3311ExpiredFlg;
    VOS_UINT8                           aucReserve[2];
}GMM_RAU_CTRL_STRU;


/******************************************************************************/
/*************************** DETACH 部分的数据结构 ****************************/
/******************************************************************************/

typedef struct
{
    VOS_UINT8                           ucT3321OutCnt;                          /* T3321溢出次数n                           */
    VOS_UINT8                           ucRetryDetachForRelCtrlFlg;             /* Detach流程被异常释放，需要在收到系统消息后重新发起 */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucDetachProc;                           /* 发起Detach的流程名 */

    VOS_UINT8                           ucSysCfgDetachFlg;

}GMM_DETACH_CTRL_STRU;

/******************************************************************************/
/*************************** Authentication 部分的数据结构 ********************/
/******************************************************************************/
#define GMM_AUTHEN_REJ_CAUSE_INVALID     0
#define GMM_AUTHEN_REJ_CAUSE_MAC_FAIL    1
#define GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL   2
#define GMM_AUTHEN_REJ_CAUSE_GSM_FAIL    3

typedef struct
{
    VOS_UINT8                              ucAuthenAttmptCnt;                       /* Authentication attempt counter           */
    VOS_UINT8                              ucRandStoredFlg;                         /* RAND是否被存储的标志                     */
    VOS_UINT8                              ucResStoredFlg;                          /* 易失性内存存储标志                       */
                                                                                /* 1:易失性内存不为空                       *
                                                                                 *   RAND和RES为易失性内存中的值            *
                                                                                 * 0:易失性内存为空,RAND为上一次的RAND的值  */
#define                 GMM_MAX_SIZE_RAND                     16
    VOS_UINT8                              aucRand[GMM_MAX_SIZE_RAND];              /* ARAND                                    */
#define                 GMM_MAX_SIZE_RES                      4
    VOS_UINT8                              aucRes[GMM_MAX_SIZE_RES];                /* RES                                      */

    VOS_UINT8                              ucResExtLen;                             /* RES(EXTERN)的长度，为0时aucResExt无意义  */
#define                 GMM_MAX_SIZE_RES_EXT                  12
    VOS_UINT8                              aucResExt[GMM_MAX_SIZE_RES_EXT];         /* RES(EXTERN)                              */


    VOS_UINT8                              ucImeisvFlg;                             /* RESPONSE消息中是否要带IMEISV             */
    VOS_UINT8                              ucAcRefNum;                              /* A&C reference number                     */
    VOS_UINT8                              ucCksnSav;                               /* 暂存消息中的CKSN                         */

    VOS_UINT8                              aucRandSav[GMM_MAX_SIZE_RAND];           /* 暂存消息中的RAND                         */
    VOS_UINT8                              ucAutnLen;                               /* AUTN长度 */
#define                 GMM_MAX_SIZE_AUTN                     17
    VOS_UINT8                          aucAutn[GMM_MAX_SIZE_AUTN];              /* AUTN内容 */
#define  GMM_UMTS_AUTHEN_SUPPORTED     1
#define  GMM_UMTS_AUTHEN_UNSUPPORTED   0
    VOS_UINT8                              ucUmtsAuthFlg;                           /* UMTS authentication supported flag       */

    VOS_UINT8                              ucLastFailCause;
    VOS_UINT8                              reserve;

    VOS_UINT32                             ulNasMsgSize;                        /* 保存当前收到的网络鉴权消息 */
    VOS_UINT8                              aucNasMsg[255];
    VOS_UINT8                              ucOpId;

}GMM_AUTHEN_CTRL_STRU;


/******************************************************************************/
/*************************** SR 部分的数据结构 ********************************/
/******************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSmsFlg;                               /* 是否是SMS触发的SR流程标志                */
    VOS_UINT8                           ucSmFlg;                                /* 是否是SM触发的SR流程标志                */
    VOS_UINT8                           ucRejCauseVaildFlg;
    VOS_UINT8                           ucRejCause;

    VOS_UINT8                           ucRetrySrForRelCtrlFlg;                 /* 链路释放后，是否需要重新发起Service Quest 流程*/
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucServiceRequestProc;
    VOS_UINT8                           aucReserve[2];
}GMM_SR_CTRL_STRU;


/*******************************************************************************
 结构名    : GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存inter rat hand over info内容，及相关控制状态。
*******************************************************************************/
typedef struct
{
    /* 是否需要等待WRR回复InterRatInfoCnf消息后，才回复网络Attach Complete消息,
       VOS_TRUE:需要,VOS_FALSE:不需要 */
    VOS_UINT8                           ucAttachCmpWaitInterRatCnfMsg;
    /* 是否需要等待WRR回复InterRatInfoCnf消息后，才回复网络RAU Complete消息,
       VOS_TRUE:需要,VOS_FALSE:不需要 */
    VOS_UINT8                           ucRauCmpWaitInterRatCnfMsg;

    /* CNF消息是否已收到。*/
    VOS_UINT8                           ucInterRatCnfMsgRcvdFlg;

    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           aucData[RRC_NAS_INTER_RAT_HANDOVER_INFO_LEN];

    VOS_UINT8                           ucEutranInterRatInfoRequestedFlag;
    VOS_UINT8                           ucReserve[1];
}GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU;

/******************************************************************************/
/*************************** 消息解析用数据结构 *******************************/
/******************************************************************************/
#define NAS_GMM_ENCODE_IE_MAX_NUM       (17)           /* GMM解析attach和rau结果时记录解析IE的最大个数 */

typedef struct
{
    VOS_UINT32                             ulOptionalIeMask;                        /* 可选IE的MASK                             */

    VOS_UINT8                              aucIeOffset[NAS_GMM_ENCODE_IE_MAX_NUM];                        /* IE的偏移量的存储空间                     */
    VOS_UINT8                              aucReserved[3];
}GMM_MSG_RESOLVE_STRU;

/* ucRauCause */
#define GMM_RAU_FOR_NORMAL                  0
#define GMM_RAU_FOR_INTERSYSTEM             1
#define GMM_RAU_FOR_WAITSERVICE             2

/* ucT3312State */
#define GMM_T3312_NOT_TIMEOUT               0
#define GMM_T3312_TIMEOUT                   1
/* ucPowerOff */
#define GMM_POWER_OFF_NOT_RCV               0
#define GMM_POWER_OFF_RCV                   1
typedef struct
{
    VOS_UINT32          ulTimerRunMask;                 /* 记录切换之前定时器状态 */
    VOS_UINT32          ulTimerRunMaskEx;                 /* 记录切换之前定时器状态 */
    VOS_UINT32          ulTimerValue[GMM_TIMER_NUM];
    VOS_UINT8           ucPreState;                     /* 记录切换之前GMM状态 */
    VOS_UINT8           ucPreSrvState;                  /* 记录切换之前GMM服务状态 */
    VOS_UINT8           ucPreRat;                       /* 记录切换时的网络接入模式 */
    VOS_UINT8           ucRauCause;                     /* 记录RAU原因  */
    VOS_UINT8           ucSuspendCause;                 /* 记录挂起原因,取值见RRMM_SUSPEND_IND */
    VOS_UINT8           ucT3312State;                   /* 记录在挂起过程中T3312是否超时       */
    VOS_UINT8           ucNetModeChange;                /* 记录异系统改变时网络模式改变的类型 */
    VOS_UINT8           ucPowerOff;                     /* 记录是否接收POWER OFF请求          */

    VOS_UINT8           ucGetLteSecContext;             /* 记录异系统是否已经从Lte获取了安全上下文,VOS_TRUE,已获取,VOS_FALSE未获取 */
}GMM_SUSPEND_CTRL_STRU;

/*******************************************************************************
 结构名    : GMM_CALL_SUPPORT_CODEC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前支持的codec类型,bit位置1表示该codec有效
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          CodecType_GSMFR         :1;
    VOS_UINT16                          CodecType_GSMHR         :1;
    VOS_UINT16                          CodecType_GSMEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMR      :1;
    VOS_UINT16                          CodecType_GSMHRAMR      :1;
    VOS_UINT16                          CodecType_UMTSAMR       :1;
    VOS_UINT16                          CodecType_UMTSAMR2      :1;
    VOS_UINT16                          CodecType_TDMAEFR       :1;
    VOS_UINT16                          CodecType_PDCEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMRWB    :1;
    VOS_UINT16                          CodecType_UMTSAMRWB     :1;
    VOS_UINT16                          CodecType_OHR_AMR       :1;
    VOS_UINT16                          CodecType_OFR_AMR_WB    :1;
    VOS_UINT16                          CodecType_OHR_AMR_WB    :1;
    VOS_UINT16                          BandSpare               :2;
}GMM_CALL_SUPPORT_CODEC_STRU;

/*******************************************************************************
 结构名    :MN_CALL_SUPPORT_CODEC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前支持的codec类型,bit位置1表示该codec有效
*******************************************************************************/
typedef union
{
    GMM_CALL_SUPPORT_CODEC_STRU         stSupportCodec;
    VOS_UINT16                          usSupportCodec;
}GMM_CALL_SUPPORT_CODEC_UNION;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif /* _GMMSTRUCTURE_H_ */

