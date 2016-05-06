/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : ExtAppMmcInterface.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-08-17
  Description : 协议栈软件MMC与APP接口头文件
  History     :
  1. Date:2005-08-17
     Author: ---
     Modification:Create
  2. 日    期  : 2006年12月4日
     作    者  : luojian id:60022475
     修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
  3. 日    期  : 2007年5月22
     作    者  : Li Jilin 60827
     修改内容  : A32D11131
  4. 日    期   : 2007年9月29日
     作    者   : luojian id:107747
     修改内容   : 根据问题单号：A32D12980
  5. 日    期   : 2008年3月17日
     作    者   : s46746
     修改内容   : 问题单号:AT2D02570,NAS B005版本新增需求合入
  6. 日    期   : 2009年01月06日
     作    者   : o00132663
     修改内容   : 问题单号:AT2D08132,接口消息TAFMMC_START_REQ中ucRoamCapability项未被初始化。
  7. 日    期   : 2009年03月26日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D10349/AT2D10492,MMC/MMA之间交互的SYSCFG回复消息多了个VOS_HEADER
  8. 日    期   : 2009年07月07日
     作    者   : h44270
     修改内容   : 问题单号：AT2D12792，不能显示EGPRS小区信息
  9. 日    期   : 2009年11月28日
     作    者   : s46746
     修改内容   : 问题单号：AT2D15677,澳大利亚漫游定制合入
 10. 日    期   : 2012年4月18日
     作    者   : l00130025
     修改内容   : DTS2012040200480,删除MMC_REG_STATE_TYPE的重复定义
************************************************************************/

#ifndef _EXT_APP_MMC_INTERFACE_H_
#define _EXT_APP_MMC_INTERFACE_H_


#include "TafMmcInterface.h"
#include "TafTypeDef.h"
#include "NasCommDef.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)
/* ------------------------------API 参数结构---------------------------------*/

#define D_MMC_CN_DOMAIN_CS          0x01
#define D_MMC_CN_DOMAIN_PS          0x02
#define D_MMC_CN_DOMAIN_PS_CS       0x03

/* macro definition: Cause */

#define  D_MMC_CAUSE_NULL                                      0
#define  D_MMC_CAUSE_IMSI_UNKNOWN_IN_HLR                       2
#define  D_MMC_CAUSE_ILLEGAL_MS                                3
#define  D_MMC_CAUSE_IMSI_UNKNOWN_IN_VLR                       4
#define  D_MMC_CAUSE_IMSI_NOT_ACCEPTED                         5
#define  D_MMC_CAUSE_ILLEGAL_ME                                6
#define  D_MMC_CAUSE_GPRS_SERV_NOT_ALLOW                       7
#define  D_MMC_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW     8
#define  D_MMC_CAUSE_MS_ID_NOT_DERIVED                         9
#define  D_MMC_CAUSE_IMPLICIT_DETACHED                         10
#define  D_MMC_CAUSE_PLMN_NOT_ALLOW                            11
#define  D_MMC_CAUSE_LA_NOT_ALLOW                              12
#define  D_MMC_CAUSE_ROAM_NOT_ALLOW                            13
#define  D_MMC_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN               14
#define  D_MMC_CAUSE_NO_SUITABL_CELL                           15
#define  D_MMC_CAUSE_MSC_UNREACHABLE                           16
#define  D_MMC_CAUSE_NETWORK_FAILURE                           17
#define  D_MMC_CAUSE_MAC_FAILURE                               20
#define  D_MMC_CAUSE_SYNCH_FAILURE                             21
#define  D_MMC_CAUSE_PROCEDURE_CONGESTION                      22
#define  D_MMC_CAUSE_GSM_AUT_UNACCEPTABLE                      23
#define  D_MMC_CAUSE_SERV_OPT_NOT_SUPPORT                      32
#define  D_MMC_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE                33
#define  D_MMC_CAUSE_SERV_OPT_OUT_OF_ORDER                     34
#define  D_MMC_CAUSE_CALL_CANNOT_IDENTIFY                      38
#define  D_MMC_CAUSE_NO_PDP_CONTEXT_ACT                        40
#define  D_MMC_CAUSE_RETRY_UPON_ENTRY_CELL_MIN                 48
#define  D_MMC_CAUSE_RETRY_UPON_ENTRY_CELL_MAX                 63
#define  D_MMC_CAUSE_SEMANTICALLY_INCORRECT_MSG                95
#define  D_MMC_CAUSE_INVALID_MANDATORY_INF                     96
#define  D_MMC_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE                97
#define  D_MMC_CAUSE_MSG_TYPE_NOT_COMPATIBLE                   98
#define  D_MMC_CAUSE_IE_NONEXIST_NOTIMPLEMENTED                99
#define  D_MMC_CAUSE_CONDITIONAL_IE_ERROR                      100
#define  D_MMC_CAUSE_MSG_NOT_COMPATIBLE                        101
#define  D_MMC_CAUSE_PROTOCOL_ERROR                            111
#define  D_MMC_CAUSE_OTHER_CAUSE                               249
#define  D_MMC_CAUSE_TIMER_TIMEOUT                             251
#define  D_MMC_CAUSE_RR_CONN_EST_FAIL                          252
#define  D_MMC_CAUSE_RR_CONN_FAIL                              253
#define  D_MMC_CAUSE_ACCESS_BARRED                             254
#define  D_MMC_CAUSE_UNSUITABLE_MODE                           255
#define  D_MMC_CAUSE_NAS_MM_CAUSE_SPECIFIC_PROCEDURE_ONGOING   300

/* structure: ST_MMC_START_REQ */
/*****************************************************************************
 结构名    : TAFMMC_START_REQ_STRU
 结构说明  :开机请求
 1.日    期   : 2011年8月04日
   作    者   : w00167002
   修改内容   : 周君检视，删除不用的开机项
 2.日    期   : 2012年6月14日
   作    者   : l60609
   修改内容   : 增加TAFMMC_PLMN_RAT_PRIO_STRU
*****************************************************************************/
typedef struct
{
    TAFMMC_CARD_STATUS_ENUM_U8          ucCardStatus;
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LENGTH];
    VOS_UINT8                           aucReserve[2];
    TAFMMC_PLMN_RAT_PRIO_STRU           stPlmnRatPrio;
} ST_MMC_START_REQ;

/* structure: ST_MMC_START_CNF的 */
typedef struct
{
    VOS_UINT32 ulResult;
} ST_MMC_START_CNF;


/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-10, begin */
/*****************************************************************************
 结构名    : ST_MMC_AC_INFO_CHANGE_IND_STRU
 结构说明  : MMC向MMA上报小区接入禁止信息的结构体

 修改记录  :
 1.日    期   : 2012年12月08日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucCnDomainId;                                   /* 服务域信息 */
    TAFMMC_CELL_RESTRICTION_TYPE_ENUM_UINT8     enCellAcType;                                   /* 小区受限类型 */
    VOS_UINT8                                   ucRestrictRegister;                             /* 是否限制注册 */
    VOS_UINT8                                   ucRestrictPagingRsp;                            /* 是否限制响应寻呼 */
}ST_MMC_AC_INFO_CHANGE_IND_STRU;
/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-10, end */

/* structure: ST_MMC_MODE_CHANGE_REQ */
typedef struct
{
/* 与类型TAF_PH_MS_CLASS_TYPE定义保持一致 */
#define D_MMC_MODE_NULL              5
#define D_MMC_MODE_A                 2
#define D_MMC_MODE_CG                1
#define D_MMC_MODE_CC                0
    VOS_UINT32                  ulMsMode;
}ST_MMC_MODE_CHANGE_REQ;

/* structure: ST_MMC_ATTACH_REQ */
#define D_MMC_ATTACH_TYPE_GPRS        1
#define D_MMC_ATTACH_TYPE_IMSI        2
#define D_MMC_ATTACH_TYPE_GPRS_IMSI   3

typedef struct
{
    VOS_UINT32                  ulOpID;

    VOS_UINT32                  ulAttachType;
}ST_MMC_ATTACH_REQ;

/* structure: ST_MMC_ATTACH_CNF */
typedef struct
{
    VOS_UINT32                   ulMcc;
    VOS_UINT32                   ulMnc;
} ST_MMC_PLMN_ID;

typedef struct
{
    VOS_UINT32                  ulOpID;
    VOS_UINT32                  ulCnDomainId;
    VOS_UINT32                  ulServiceStatus;
    ST_MMC_PLMN_ID              PlmnId;
}ST_MMC_ATTACH_CNF;


typedef VOS_UINT8 MMC_CUR_NETWORK;
#define MMC_MS_INVALID   3    /**/
#define MMC_MS_LTE       2
#define MMC_MS_WCDMA     1    /**/
#define MMC_MS_GSM       0    /**/

/*小区信息*/
#define APPMMC_CELL_MAX_NUM    8
typedef struct
{
    VOS_UINT8    ucCellNum;
    VOS_UINT8    aucReserve[3];
    VOS_UINT32   aulCellId[APPMMC_CELL_MAX_NUM]; /*<==A32D11131*/
}MMC_CELL_INFO_ST;

/* structure: ST_MMC_SERVICE_STATUS_IND */
typedef struct
{
    VOS_UINT32                  ulCnDomainId;
    VOS_UINT32                  ulServiceStatus;
    ST_MMC_PLMN_ID         PlmnId;
    /*用于指示以下数据位是否存在*/
    VOS_UINT32             ulSysforIndFlg;
#define  D_MMC_SYS_INFO_NULL_FLG                            0x0
#define  D_MMC_SYS_INFO_MM_REG_STA_FLG                      0x1
#define  D_MMC_SYS_INFO_GMM_REG_STA_FLG                     0x2
#define  D_MMC_SYS_INFO_NETWORK_TYPE_FLG                    0x4
#define  D_MMC_SYS_INFO_LAC_FLG                             0x8
#define  D_MMC_SYS_INFO_CELL_ID_FLG                         0x10
#define  D_MMC_SYS_INFO_RAC_FLG                             0x20
#define  D_MMC_SYS_INFO_WHOLE_FLG                           0xffffffff
    /*增加当前注册状态与位置信息，小区信息*/

    /*注册状态，需求由AT命令提出，直接从MMC的全局数据中获得*/


    TAFMMC_REG_STATE_TYPE  MmRegState;
    /*GMM注册状态*/
    TAFMMC_REG_STATE_TYPE  GmmRegState;


    /*获取当前网络类型*/
    MMC_CUR_NETWORK        CurNetWork;
    VOS_UINT8              ucReserve;
    /*位置码信息*/
    VOS_UINT16             usLac;
    /*RAC*/
    VOS_UINT8              ucRac;
    VOS_UINT8              ucSysSubMode;        /*驻留网络的系统子模式，取值与RRC_NAS_SYS_SUBMODE_ENUM相同 */
    /*小区信息*/
    MMC_CELL_INFO_ST       stCellId;
}ST_MMC_SERVICE_STATUS_IND;

/* structure: ST_MMC_DETACH_REQ */
typedef struct
{
    VOS_UINT32               ulOpID;

#define D_MMC_PS_DETACH              1
#define D_MMC_CS_DETACH              2
#define D_MMC_PS_CS_DETACH           3
    VOS_UINT32               ulDetachCause ;
}ST_MMC_DETACH_REQ;

/* structure: ST_MMC_DETACH_CNF */
typedef struct
{
    VOS_UINT32                  ulOpID;
    VOS_UINT32                  ulCnDomainId;
    VOS_UINT32                  ulServiceStatus;
}ST_MMC_DETACH_CNF;

/* structure: ST_MMC_DETACH_IND */
typedef struct
{

    VOS_UINT32                  ulCnDomainId;

    VOS_UINT32                  ulServiceStatus;
}ST_MMC_DETACH_IND;

/* structure: ST_MMC_PLMN_LIST_REQ */
typedef struct
{
    VOS_UINT32                  PlaceHold;
} ST_MMC_PLMN_LIST_REQ;

/* structure: ST_MMC_PLMN_LIST_IND */
/*#define D_MMC_MAX_PLMN_CNT    10*/
#define D_MMC_MAX_PLMN_CNT    37
typedef struct
{
    VOS_UINT32                     ulCnt;
    ST_MMC_PLMN_ID            aPlmnList[D_MMC_MAX_PLMN_CNT];
    VOS_UINT8                     aucPlmnStatus[D_MMC_MAX_PLMN_CNT];
    VOS_UINT8                     aucRaMode[D_MMC_MAX_PLMN_CNT];
} ST_MMC_PLMN_LIST_IND;


/* structure: ST_MMC_PLMN_LIST_REJ */
typedef struct
{
    VOS_UINT32 PlaceHold;
} ST_MMC_PLMN_LIST_REJ;

/* structure: ST_MMC_PLMN_LIST_ABORT_REQ */
typedef struct
{
    VOS_UINT32 PlaceHold;
} ST_MMC_PLMN_LIST_ABORT_REQ;

/* structure: ST_MMC_PLMN_USER_SEL_REQ */
typedef struct
{

#define     D_MMC_PLMN_USER_SEL            0x01
#define     D_MMC_PLMN_USER_RESEL          0x02
    VOS_UINT32                   ulMode;
    ST_MMC_PLMN_ID          PlmnId;
#define         D_MMC_PLMN_SEL_MODE_PARA_INVALID    0
#define         D_MMC_PLMN_SEL_MODE_PARA_VALID      1
    VOS_UINT32                   ulPlmnSelModeValid;
#define         D_MMC_PLMN_SEL_MODE_AUTO       0
#define         D_MMC_PLMN_SEL_MODE_MANUAL     1
    VOS_UINT32                   ulPlmnSelMode;
#define         D_MMC_ACCESS_MODE_WCDMA        1
#define         D_MMC_ACCESS_MODE_GSM          0
    VOS_UINT8               ucAccessMode;
} ST_MMC_PLMN_USER_SEL_REQ;

/* structure: ST_MMC_COVERAGE_AREA_IND */
typedef struct
{
#define     D_MMC_COVERAGE_AREA_LOST       0
#define     D_MMC_COVERAGE_AREA_ENTER      1
    VOS_UINT32                  ulCoverageChgMode;
    ST_MMC_PLMN_ID         PlmnId;

    VOS_UINT32                  ulCsSvcSta;
    VOS_UINT32                  ulPsSvcSta;
    VOS_UINT32                  ulTimMaxFlg;
} ST_MMC_COVERAGE_AREA_IND;

/* structure: ST_MMC_POWER_OFF_REQ */
typedef struct
{
    VOS_UINT32 PlaceHold;
    VOS_UINT32 ulCause;
} ST_MMC_POWER_OFF_REQ;

/* structure: ST_MMC_POWER_OFF_CNF */
typedef struct
{
    VOS_UINT32 PlaceHold;
} ST_MMC_POWER_OFF_CNF;

/*****************************************************************************
 结构名    : ST_MMC_PLMN_LIST_ABORT_CNF
 结构说明  : MMC向MMA回复TAFMMC_PLMN_LIST_ABORT_CNF消息的结构体
 修改人    : W00176964
 修改日期  : 2011-09-06
 修改原因  : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    VOS_UINT32              ulCnt;                                              /* MMC搜索到的PLMN个数                      */
    TAFMMC_PLMN_ID_STRU     aPlmnList[TAFMMC_MAX_PLMN_CNT];                     /* MMC搜索到的PLMN列表                      */
    VOS_UINT8               aucPlmnStatus[TAFMMC_MAX_PLMN_CNT];
    VOS_UINT8               aucRaMode[TAFMMC_MAX_PLMN_CNT];
}ST_MMC_PLMN_LIST_ABORT_CNF;

/*struct ST_MMC_PLMN_SPECIALIZE_CNF*/
#define MMC_PLMN_SPECIALIZE_SUCCESS     0
#define MMC_PLMN_SPECIALIZE_FAIL        1
#define MMC_PLMN_RESEL_REJ              2
#define MMC_PLMN_RESEL_ACCEPT           3
typedef struct
{
    VOS_UINT32  ulResult;
}MMC_PLMN_SEL_CNF_ST;



#define TAFMMC_SET_WAS_BAND_CNF_SUCCESS   MMC_SET_WAS_BAND_CNF_SUCCESS
#define TAFMMC_SET_WAS_BAND_CNF_FAIL      MMC_SET_WAS_BAND_CNF_FAIL
#define TAFMMC_SET_GAS_BAND_CNF_SUCCESS   MMC_SET_GAS_BAND_CNF_SUCCESS
#define TAFMMC_SET_GAS_BAND_CNF_FAIL      MMC_SET_GAS_BAND_CNF_FAIL

#define    D_MMC_START_REQ               0
#define    D_MMC_START_CNF               1
#define    D_MMC_MODE_CHANGE_REQ         2
#define    D_MMC_ATTACH_REQ              3
#define    D_MMC_ATTACH_CNF              4
#define    D_MMC_SERVICE_STATUS_IND      5
#define    D_MMC_DETACH_REQ              6
#define    D_MMC_DETACH_CNF              7
#define    D_MMC_DETACH_IND              8
#define    D_MMC_PLMN_LIST_REQ           9
#define    D_MMC_PLMN_LIST_IND           10
#define    D_MMC_PLMN_LIST_REJ           11
#define    D_MMC_PLMN_LIST_ABORT_REQ     12
#define    D_MMC_PLMN_USER_SEL_REQ       13
#define    D_MMC_COVERAGE_AREA_IND       14
#define    D_MMC_POWER_OFF_REQ           15
#define    D_MMC_POWER_OFF_CNF           16

/*增加两个MMC事件*/
/*服务状态改变,小区更新,位置区更新*/
#define    D_MMC_SYSTEM_INFO_IND         17
#define    D_MMC_RSSI_IND                18
#define    D_MMC_PLMN_SPECIAL_REQ        19
#define    D_MMC_PLMN_SEL_CNF            20
#define    D_MMC_SET_BAND_CNF            21
#define    D_MMC_USIM_STATUS_IND         22
#define    D_MMC_DATATRAN_ATTRI_IND      23
#define    D_MMC_SYS_CFG_SET_REQ         24
#define    D_MMC_SYS_CFG_SET_CNF         25
#define    D_MMC_MM_INFO_IND             26

#define    D_MMC_CBS_NO_NETWORK_IND      (27)
#define    D_MMC_CBS_CURR_NET_MODE_IND   (28)
#define    D_MMC_PLMN_SEARCH_REQ         (29)
#define    D_MMC_PLMN_SELECTION_RLST_IND (30)

#define    D_MMC_PLMN_LIST_ABORT_CNF     (31)


#define    D_MMC_SPEC_PLMN_SEARCH_ABORT_REQ  (32)
#define    D_MMC_SYS_CFG_SET_ABORT_REQ       (33)
#define    D_MMC_SPEC_PLMN_SEARCH_ABORT_CNF  (34)
#define    D_MMC_SYS_CFG_SET_ABORT_CNF       (35)



#define    D_MMC_APS_SERVICE_STATE_IND    (36)
#define    D_MMC_UMTS_CIPHER_INFO_IND     (37)
#define    D_MMC_GPRS_CIPHER_INFO_IND     (38)


#define    D_MMC_OM_MAINTAIN_INFO_IND     (39)



#define    D_MMC_PLMN_USER_SEL_REJ     (40)

/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-10, begin */
#define    D_MMC_AC_INFO_CHANGE_IND                (41)
/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-10, end */

/* MMC MSG CORE */
typedef struct {
    VOS_UINT8      ucChoice;
    VOS_UINT8      aucReserve[3];

    union  {
        ST_MMC_START_REQ                 StartReq;
        ST_MMC_START_CNF                 StartCnf;
        ST_MMC_MODE_CHANGE_REQ           ModeChangeReq;
        ST_MMC_ATTACH_REQ                AttachReq;
        ST_MMC_ATTACH_CNF                AttachCnf;
        ST_MMC_SERVICE_STATUS_IND        ServiceStatusInd;
        ST_MMC_DETACH_REQ                DetachReq;
        ST_MMC_DETACH_CNF                DetachCnf;
        ST_MMC_DETACH_IND                DetachInd;
        ST_MMC_PLMN_LIST_REQ             PlmnListReq;
        ST_MMC_PLMN_LIST_IND             PlmnListInd;
        ST_MMC_PLMN_LIST_REJ             PlmnListRej;
        ST_MMC_PLMN_LIST_ABORT_REQ       PlmnListAbortReq;
        ST_MMC_PLMN_USER_SEL_REQ         PlmnUserSelReq;
        ST_MMC_COVERAGE_AREA_IND         CoverageAreaInd;
        ST_MMC_POWER_OFF_REQ             PowerOffReq;
        ST_MMC_POWER_OFF_CNF             PowerOffCnf;
        ST_MMC_PLMN_LIST_ABORT_CNF       stPlmnListAbortCnf;
        /*增加对应的结构体*/
        MMC_RSSI_IND_ST                  RssiValue;
        ST_MMC_PLMN_USER_SEL_REQ         stSelPlmnSrhReq;
        MMC_PLMN_SEL_CNF_ST              stSelPlmnSrhCnf;
        VOS_UINT8                        ucDataTranAttri;
        TAFMMC_SYS_CFG_SET_REQ_STRU      stSysCfgReq;
        TAFMMC_SYS_CFG_SET_RESULT_ENUM_UINT32 ulSysCfgRslt;
        NAS_MM_INFO_IND_STRU             stMmInfo;
        TAFMMC_PLMN_SELECTION_RESULT_ENUM_UINT32 enPlmnSelectionRslt;
        TAFMMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU stSpecPlmnSearchAbortReq;
        TAFMMC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU stSpecPlmnSearchAbortCnf;


        MMC_UMTS_CIPHER_INFO_IND_STRU    stWCipherInfoInd;
        MMC_GPRS_CIPHER_INFO_IND_STRU    stGCipherInfoInd;

        TAFMMC_OM_MAINTAIN_INFO_IND_STRU    stOmMaintainInfoInd;

        TAFMMC_SPEC_PLMN_SEARCH_REJ_STRU    stSpecPlmnSearchRej;

        /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        TAFMMC_AC_INFO_CHANGE_IND_STRU      stAcInfoChangeInd;
        /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    } u;
} ST_MMC_MSG;

/*_H2ASN_Include wuepsosa_msg.h*/

typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                  /* 消息头                                   */
    ST_MMC_MSG                      stMmcMsg;
}APP_MMC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    APP_MMC_MSG_DATA                MsgData;
}AppMmcInterface_MSG;
/* ------------------------------API 外部声明---------------------------------*/

extern VOS_VOID Api_AppMmcMsgReq(ST_MMC_MSG  *p);
extern VOS_VOID Api_AppMmcMsgInd(ST_MMC_MSG  *p);


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

