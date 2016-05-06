/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsCtx.h
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年12月13日
  最近修改   :
  功能描述   : TafApsCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月13日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSCTX_H__
#define __TAFAPSCTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsDsFlowStats.h"
#include "AtMnInterface.h"
#include "SmEsmInterface.h"
#include "MmcApsInterface.h"
#include "Taf_Aps.h"
#include "TafApsApi.h"

#include "NasNvInterface.h"

#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_APS_MAX_MSG_BUFFER_LEN                      (1500)                  /* 缓存的最大长度 */
#define TAF_APS_MAX_MSG_QUEUE_NUM                       (22)                    /* 最大缓存的个数 */

#define TAF_APS_RAB_ID_OFFSET                           (5)                     /* 当前到网络的定义是5到15，因此有一个5的偏移量 */

#define TAF_APS_RAB_ID_MIN                              (5)                     /* RAB ID的取值范围，最小是5 */
#define TAF_APS_RAB_ID_MAX                              (15)                    /* RAB ID的取值范围，最大是15 */

/* 最大RAB承载个数 */
#define TAF_APS_MAX_RAB_NUM                             (15)                    /* RAB ID的取值范围，最大是15 */


#define TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE               (11)                    /* 等待消息结果的队列长度，目前假定为10个 */

#define TAF_APS_INVALID_PDPID                           (0xFF)                  /* 无效的PDP ID */
#define TAF_APS_INVALID_CID                             (0xFF)                  /* 无效的CID */
#define TAF_APS_INVALID_CLIENTID                        (0xFFFE)                /* 无效的CLIENT ID */
#define TAF_APS_INVALID_OPID                            (0xFF)                  /* 无效的OPID ID */

#define TAF_APS_MAX_MSG_QUEUE_SIZE                      (11)                    /* 内部消息队列最大的长度，
                                                                                   当前状态机内部发出，应该最多十个PDP实体，目前使用的长度是12 */
#define TAF_APS_INVALID_INTERNAL_MSG_ID                 (0xFFFF)                /* 消息ID的无效值 */

#define TAF_APS_32BIT_DATA_LEN                          (32)                    /* 32位数据的bit长度 */
#define TAF_APS_DEFAULT_CID                             (0)                     /* 默认承载所使用的CID，CID0 */
#define TAF_APS_OCTET_MOVE_THREE_BITS                   (0x03)                  /* 将一个字节移动3位 */

#define TAF_APS_1_KBYTE_1024_BYTE                       (1024)

/* PDP激活被拒10次之内，不限制用户向网侧发起PDP激活请求 */
#define TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD   (10)

/* PDP激活被拒11-19次之内，按照10s步长递增启动定时器 */
#define TAF_APS_PDP_ACT_LIMIT_STEP_DELAY_COUNT_THRESHOLD (19)
#define TAF_APS_PDP_ACT_LIMIT_STEP_TIME                  (10)

/* PDP激活被拒19次(包括19次)以上，按照90s时长启动定时器 */
#define TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME         (90)

/* PDP暂停激活定时器时长随机数的阈值 */
#define TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_THRESHOLD      (45)

/* 当失败次数是10的整数倍时，PDP暂停激活定时器使用随机时长 */
#define TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_FAILCOUNT      (10)

/* TI_TAF_APS_LIMIT_PDP_ACT定时器不和任何PDP ID邦定，所以定义一个无效值 */
#define TAF_APS_PDP_ACT_LIMIT_PDP_ID                    (0xFF)

#define TAF_APS_DSFLOW_AT_REPORT_PERIOD                 (2)

#define TAF_APS_HRPD_DEFAULT_SR_ID                       (1)

#define TAF_APS_CDMA_EPDSZID_LIST_MAX_LEN                   ( 15 )
#define TAF_APS_CDMA_EPDSZID_DEFAULT_MAX_LEN                ( 4 )
#define TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN                ( 1 )

#define TAF_APS_CDMA_EPDSZID_INVAILD_SID                    (0xFFFF)
#define TAF_APS_CDMA_EPDSZID_INVAILD_NID                    (0)
#define TAF_APS_CDMA_EPDSZID_INVAILD_PZID                   (0xFF)

#define TAF_APS_CDMA_EPDSZID_INVAILD_SEQ_NUM                (0xFF)

#define TAF_APS_CDATA_EPDSZID_HAT_DEFAULT_LEN               ( 30  )             /* UNIT:S */
#define TAF_APS_CDATA_EPDSZID_HT_DEFAULT_LEN                ( 60  )             /* UNIT:S */

#define TAF_APS_MAX_SLICE_VALUE                             (0xFFFFFFFF)

/**
 * Traffic channel is suspended.
 */
#define TAF_APS_CDMA_TC_SUSPENDED                           ( 1 )
/**
 * Traffic channel is resumed.
 */
#define TAF_APS_CDMA_TC_RESUMED                             ( 0 )

#define TAF_APS_CDMA_INVALID_SR_ID                          ( 0 )

#define TAF_APS_CDMA_INVALID_PDN_ID                         ( 0xFF )


#define TAF_APS_NSAPI_INVALID_VALUE                         ( 0 )

#define TAF_APS_GET_MULTI_DFS_SUPPORT_FLG()                 (g_stTafApsCtx.stSwitchDdrRateInfo.ulMultiDfsFlg)

#define TAF_APS_GET_MULTI_DFS_PROFILE_NUM(dfsType)          (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].ulProfileNum)
#define TAF_APS_GET_MULTI_DFS_PROFILE_DL_RATE(dfsType, i)   (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].astProfile[i].ulDlRate)
#define TAF_APS_GET_MULTI_DFS_PROFILE_UL_RATE(dfsType, i)   (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].astProfile[i].ulUlRate)
#define TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(dfsType, i)  (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].astProfile[i].ulDdrBand)

#define TAF_APS_GET_DFS_PROFILE_NUM()                       (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].ulProfileNum)
#define TAF_APS_GET_DFS_PROFILE_DL_RATE(i)                  (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].astProfile[i].ulDlRate)
#define TAF_APS_GET_DFS_PROFILE_UL_RATE(i)                  (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].astProfile[i].ulUlRate)
#define TAF_APS_GET_DFS_PROFILE_DDR_BAND(i)                 (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].astProfile[i].ulDdrBand)

#define TAF_APS_DFS_REQUEST_SUCC_CNT(i)                     (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulRequestSucCnt  += i)
#define TAF_APS_DFS_REQUEST_FAIL_CNT(i)                     (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulRequestFailCnt  += i)
#define TAF_APS_DFS_UPDATE_SUCC_CNT(i)                      (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulUpdateSucCnt  += i)
#define TAF_APS_DFS_UPDATE_FAIL_CNT(i)                      (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulUpdateFailCnt += i)

#define TAF_APS_GET_DSFLOW_RELEASE_DFS()                    (g_stTafApsCtx.stSwitchDdrRateInfo.ulMinBand)
#define TAF_APS_GET_DSFLOW_MIN_DDR_BAND()                   (g_stTafApsCtx.stSwitchDdrRateInfo.ulMinBand)
#define TAF_APS_GET_DSFLOW_MAX_DDR_BAND()                   (g_stTafApsCtx.stSwitchDdrRateInfo.ulMaxBand)


#define TAF_APS_GET_RAT_TYPE_IN_SUSPEND()                   (g_stTafApsCtx.enCurrSuspendRatType)
#define TAF_APS_SET_RAT_TYPE_IN_SUSPEND(ratType)            (g_stTafApsCtx.enCurrSuspendRatType = (ratType))

#define TAF_APS_SET_CDATA_SUSPEND_STATUS(ucStatus)          (g_stTafApsCtx.stCdataCtx.ucSuspendStatus = (ucStatus))
#define TAF_APS_GET_CDATA_SUSPEND_STATUS()                  (g_stTafApsCtx.stCdataCtx.ucSuspendStatus)


#define TAF_APS_SET_CDATA_MTU(value)                        (g_stTafApsCtx.stCdataCtx.usMtu = (value))
#define TAF_APS_GET_CDATA_MTU()                             (g_stTafApsCtx.stCdataCtx.usMtu)
#define TAF_APS_MIN(x, y)\
        (((x)<(y))?(x):(y))


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define      TAF_APS_MAX_SIP_NAI_NUM                                            (16)
#define      TAF_APS_MAX_SIP_NAI_LENGTH                                         (127)
#define      TAF_APS_MAX_SIPPAPSS_LENGTH                                        (127)
#define      TAF_APS_MAX_SIPPAPSS_NUM                                           (16)
#define      TAF_APS_3GPD_SIP_STATUS_FILE_LENGTH                                (1)
#define      TAF_APS_3GPD_SIP_CAPA_FILE_LENGTH                                  (4)
#define      TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_PAP_ENABLE                     (0x40)
#define      TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP_ENABLE                    (0x80)
#define      TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_PAP_CHAP_ENABLE                (0xC0)
#define      TAF_APS_3GPD_SIP_SS_NAI_INDEX_BIT_LEN                              (4)
#define      TAF_APS_3GPD_SIP_SS_NAI_NUM_BIT_LEN                                (4)
#define      TAF_APS_MIN_SIP_SS_LENGTH                                          (2)
#define      TAF_APS_MIN_SIP_NAI_LENGTH                                         (9)
#define      TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN                                 (5)
#define      TAF_APS_BIT_LEN_8_BITS                                             (8)
#define      TAF_APS_MIN_CDMA_SERVICE_TABLE_LEN_CONTAIN_MIP                     (10)
#define      TAF_APS_MIN_CDMA_SERVICE_TABLE_LEN_CONTAIN_SIP                     (5)
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_APS_FSM_ID_ENUM_UINT32
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2011年12月17日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
enum TAF_APS_FSM_ID_ENUM
{
    /* TAF APS MAIN 状态机，当前处于稳态 */
    TAF_APS_FSM_MAIN                                    = 0X00,

    /* TAF APS MS ACTIVATING状态机，当前在UE发起激活操作过程中 */
    TAF_APS_FSM_MS_ACTIVATING                           = 0X01,

    /* TAF APS NW ACTIVATING状态机，当前在NW发起激活操作过程中 */
    TAF_APS_FSM_NW_ACTIVATING                           = 0X02,

    /* TAF APS MS DEACTIVATING状态机，当前在UE发起去激活操作过程中 */
    TAF_APS_FSM_MS_DEACTIVATING                         = 0X03,

    /* TAF APS MS MODIFYING状态机，当前在UE发起MODIFY操作过程中 */
    TAF_APS_FSM_MS_MODIFYING                            = 0X04,

    /* TAF APS CDATA ESTING状态机，当前在CDMA模式下发起数据服务链接建立过程中 */
    TAF_APS_FSM_CDATA_ESTING                            = 0X05,

    /* TAF APS CDATA DISCING状态机，当前在CDMA模式下数据服务链接挂断过程中 */
    TAF_APS_FSM_CDATA_DISCING                           = 0X06,

    /* TAF APS CDATA HANDOFF状态机，当前在CDMA模式下数据服务链接切换过程中 */
    TAF_APS_FSM_CDATA_HANDOFF                           = 0X07,

    TAF_APS_FSM_BUTT

};
typedef VOS_UINT32 TAF_APS_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_APS_DFS_TYPE_ENUM_UINT32
 结构说明  : 当前的接入技术
 1.日    期   : 2014年05月26日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
enum TAF_APS_DFS_TYPE_ENUM
{
    TAF_APS_DFS_TYPE_BASE               = 0x00,                                 /*当前未在任何网络上驻留*/
    TAF_APS_DFS_TYPE_GSM                = 0x01,                                 /* GSM下DFS */
    TAF_APS_DFS_TYPE_WCDMA              = 0x02,                                 /* WCDMA下DFS */
    TAF_APS_DFS_TYPE_LTE                = 0x03,                                 /* LTE下DFS */
    TAF_APS_DFS_TYPE_TD_WCDMA           = 0x04,                                 /* TD-WCDMA下DFS */
    TAF_APS_DFS_TYPE_CDMA               = 0x05,                                 /* CDMA下DFS */
    TAF_APS_DFS_TYPE_BUTT                                                       /* 无效的接入技术 */
};
typedef VOS_UINT32 TAF_APS_DFS_TYPE_ENUM_UINT32;



/** ****************************************************************************
 * Name        : TAF_APS_CDATA_QOS_MODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_QOS_MODE_ENUM
{
    TAF_APS_CDATA_QOS_MODE_ONE          = 0x00,/* _H2ASN_MsgChoice TAF_APS_CDATA_1X_QOS_ASSURED_PARA_STRU */
    TAF_APS_CDATA_QOS_MODE_TWO          = 0x01,/* _H2ASN_MsgChoice TAF_APS_CDATA_1X_QOS_NON_ASSURED_PARA_STRU */
    TAF_APS_CDATA_QOS_MODE_BUTT         = 0x02
};
typedef VOS_UINT8 TAF_APS_CDATA_QOS_MODE_ENUM_UINT8;



/** ****************************************************************************
 * Name        : TAF_APS_CDATA_EPDSZID_CHG_REORIG_TYPE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM
{
    TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG                         = 0x00,     /* Don't start re-orig */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_ENTER_DORMANT              = 0x01,     /* Start re-Orig before gone to dormant */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_TC_RELEASE           = 0x02,     /* after Traffic channel release, Start re-Orig */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_DORMANT_TI_EXPIRED   = 0x03,     /* Dormant Ti expired, Start re-orig */

    TAF_APS_CDATA_EPDSZID_CHG_REORIG_BUTT
};
typedef VOS_UINT8 TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM
{
    TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID,
    TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID,
    TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID,

    TAF_APS_EPDSZID_TYPE_BUTT
};
typedef VOS_UINT8 TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_ENUM
 * Description : Simple IPAuthentication Algorithm supported by the mobile station.
 *******************************************************************************/
enum TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_ENUM
{
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_NULL,
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP,
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_PAP,
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP_TO_PAP_FALLBACK,

    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_BUTT = 0xff
};
typedef VOS_UINT8 TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_ENUM_UINT8;

#endif
/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern VOS_UINT32                              g_ulApsTestStub;


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_SIMPLE_IP_CAPA_STRU
 * Description : Simple IPCapability Parameters Block
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucMaxNaiNum;
    VOS_UINT8                                               ucMaxNaiLength;
    VOS_UINT8                                               ucMaxSsLength;
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_ENUM_UINT8          ucAuthAlgorithm;

}TAF_APS_3GPD_SIMPLE_IP_CAPA_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_SINGLE_SIP_USER_PROFILE_STRU
 * Description : 单个用户名结构体
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNaiIndex;           /* username index */
    VOS_UINT8                                               ucNaiLength;          /* user name length */
    VOS_UINT8                                               aucNaiStr[TAF_APS_MAX_SIP_NAI_LENGTH + 1];
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_ENUM_UINT8          ucAuthAlgorithm;
    VOS_UINT8                                               aucReserved[2];

}TAF_APS_3GPD_SINGLE_SIP_USER_PROFILE_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_SIP_USER_PROFILE_STRU
 * Description : username profile
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNaiNum;           /* USERNAME 个数 */
    TAF_APS_3GPD_SINGLE_SIP_USER_PROFILE_STRU               stSipUserProfile[TAF_APS_MAX_SIP_NAI_NUM];
    VOS_UINT8                                               aucReserved[3];
}TAF_APS_3GPD_SIP_USER_PROFILE_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_SINGLE_SIP_PAP_SS_STRU
 * Description : 单个密码结构体
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNaiEntryIndex;      /* ss 对应的username index */
    VOS_UINT8                                               ucPapSsLength;          /* ss length */
    VOS_UINT8                                               aucPapSsStr[TAF_APS_MAX_SIPPAPSS_LENGTH + 1];
    VOS_UINT8                                               aucReserved[3];

}TAF_APS_3GPD_SINGLE_SIP_PAP_SS_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_SIP_PAP_SS_STRU
 * Description : SIP PPP SS stru
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPapSsNum;           /* pap ss 个数 */
    TAF_APS_3GPD_SINGLE_SIP_PAP_SS_STRU                     stSipPapSs[TAF_APS_MAX_SIPPAPSS_NUM];
    VOS_UINT8                                               aucReserved[3];
}TAF_APS_3GPD_SIP_PAP_SS_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_OPERATION_CTX_STRU
 * Description : PPP鉴权 卡文件中的用户名和密码
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucTafAps3GdpCurrActSipNaiIndex;
    VOS_UINT8                                               aucReserved[3];
    TAF_APS_3GPD_SIMPLE_IP_CAPA_STRU                        st3GpdSipCapa;
    TAF_APS_3GPD_SIP_USER_PROFILE_STRU                      st3GpdSipUserProfile;
    TAF_APS_3GPD_SIP_PAP_SS_STRU                            st3GpdSipPapSs;
}TAF_APS_3GPD_OPERATION_INFO_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_3GPD_SIP_INFO_STRU
 * Description : PPP鉴权 卡文件中的用户名和密码
 *******************************************************************************/
 typedef struct
{
    VOS_UINT8                                               ucNaiLength;          /* user name length */
    VOS_UINT8                                               ucPapSsLength;          /* ss length */
    TAF_PDP_AUTH_TYPE_ENUM_UINT8                            enPppAuthType;
    VOS_UINT8                                               ucReserved;
    VOS_UINT8                                               aucNaiStr[TAF_APS_MAX_SIP_NAI_LENGTH + 1];
    VOS_UINT8                                               aucPapSsStr[TAF_APS_MAX_SIPPAPSS_LENGTH + 1];
}TAF_APS_3GPD_SIP_INFO_STRU;

#endif

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_EPDSZID_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;        /* System Identifier */
    VOS_UINT16                          usNid;        /* Network Identifier */
    VOS_UINT8                           ucPzid;       /* Packet Zone Identifier */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulBeginSlice; /* Record Begin SliceTimer */
}TAF_APS_CDATA_EPDSZID_STRU;

/*******************************************************************************
 * Name        : TAF_APS_CDATA_EPDSZID_CTX_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucEpdszidHysEnableFlg;      /* Enable:VOS_TRUE(default) Disable:VOS_FALSE */
    VOS_UINT8                                               ucEpdszidHai;               /* default: VOS_FALSE */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8       enReOrigScene;              /* default: 0 */
    VOS_UINT8                                               ucEpdszidMaxListLen;        /* List len allowed by BS: default: 0 */
    VOS_UINT8                                               ucEpdszidCurrListLen;
    TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8                 enEpdszidType;              /*Pzid, Pzid-sid-nid, Pzid-sid */
    VOS_UINT8                                               ucHatTimerLen;
    VOS_UINT8                                               ucHtTimerLen;
    TAF_APS_CDATA_EPDSZID_STRU                              stCurrEpdszid;
    TAF_APS_CDATA_EPDSZID_STRU                              astEpdszidList[TAF_APS_CDMA_EPDSZID_LIST_MAX_LEN];
}TAF_APS_CDATA_EPDSZID_CTX_STRU;

/*******************************************************************************
 * Name        : TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;        /* System Identifier */
    VOS_UINT16                          usNid;        /* Network Identifier */
    VOS_UINT8                           ucPzid;       /* Packet Zone Identifier */
    VOS_UINT8                           ucReserved[3];
}TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_CTX_STRU
 *
 * Description : New add, Belong to TAF_APS_CONTEXT_STRU.
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSocmDormTiVal; /* Default value: 0 */
    VOS_UINT32                          ulUserCfgDormTival;

    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enCdataDialMode;

    VOS_UINT32                          ulPppDeactTimerLen;

    VOS_UINT8                           ucSuspendStatus;

    VOS_UINT8                           ucEhrpdAutoAttachFlag;

    VOS_UINT8                           ucPktCdataInactivityTmrLen;    /* 1XDO Packet Data Inactivity Timer Len  */

    VOS_UINT8                           ucRsvd;

    VOS_UINT16                          usMtu;
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSoInitType;

    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastOirgOnRatType;

    TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU stHrpdEpdszidInfo;

    TAF_APS_CDATA_EPDSZID_CTX_STRU      stEpdszidCtx;
}TAF_APS_CDATA_CTX_STRU;

typedef SM_ESM_EPS_BEARER_INFO_IND_STRU TAF_APS_EPS_BEARER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : TAF_APS_DSFLOW_STATS_STRU
 结构说明  : 流量统计信息上下文结构
1.日    期   : 2011年12月14日
  作    者   : 欧阳飞 00132663
  修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRabActiveFlag;                        /*标识该RAB是否激活*/
    VOS_UINT8                           aucReserve[3];                          /*保留位*/

    VOS_UINT32                          ulStartLinkTime;                        /*当前连接开始时间*/
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;                      /*当前连接流量信息，即最后一次PDP连接的流量信息 */
    TAF_DSFLOW_INFO_STRU                stTotalFlowInfo;                        /*累积流量信息，该RAB历史所有连接累加的流量信息 */
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

}TAF_APS_DSFLOW_STATS_STRU;

/*****************************************************************************
 结构名    : TAF_APS_DFS_DEBUG_INFO_STRU
 结构说明  : DDR频率投票调频调试信息
1.日    期   : 2013年12月09日
  作    者   : 范晶 00179208
  修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRequestSucCnt;
    VOS_UINT32                          ulRequestFailCnt;
    VOS_UINT32                          ulUpdateSucCnt;                         /* 投票成功次数 */
    VOS_UINT32                          ulUpdateFailCnt;                        /* 投票失败次数 */
}TAF_APS_DFS_DEBUG_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_APS_SWITCH_DDR_RATE_INFO_STRU
 结构说明  : DDR频率投票结构
1.日    期   : 2013年12月09日
  作    者   : 范晶 00179208
  修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    VOS_INT32                           iDfsReqId;                              /* DDR调频投票请求ID */
    VOS_UINT32                          ulReqValue;                             /* DDR调频投票请求值 */
    VOS_UINT32                          ulSetMaxFlag;                           /* 设置最大频率的标识 */

    VOS_UINT32                          ulMultiDfsFlg;
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU  astDfsConfig[TAF_NVIM_DIFF_DFS_NUM];
    TAF_APS_DFS_DEBUG_INFO_STRU         stDfsDebugInfo;

    VOS_UINT32                          ulMinBand;                              /* 最小DDR频率 */
    VOS_UINT32                          ulMaxBand;                              /* 最大DDR频率 */
}TAF_APS_SWITCH_DDR_RATE_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_APS_DSFLOW_STATS_CTX_STRU
 结构说明  : 流量信息上下文结构
1.日    期   : 2011年12月14日
  作    者   : 欧阳飞 00132663
  修改内容   : 新建
2.日    期   : 2012年11月09日
  作    者   : l00198894
  修改内容   : Probe路测工具对接项目增加OM流量上报标志位、周期
3.日    期   : 2013年4月8日
  作    者   : s00217060
  修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDsFlowSave2NvFlg;                     /* 标识是否需要保存历史流量信息到NV中 */
    VOS_UINT8                           ucDsFlowSavePeriod;                     /* 流量写NV的周期 */

    VOS_UINT8                           ucDsFlowOMReportFlg;                    /* 标识是否进行OM流量上报 */
    VOS_UINT8                           ucDsFlowATRptPeriod;                    /* AT端口流量上报的周期单位s */
    VOS_UINT8                           ucDsFlowOMRptPeriod;                    /* OM流量上报的周期单位s */
    VOS_UINT8                           ucDsFlowATRptTmrExpCnt;                 /* AT端口流量上报时机，用于控制上报周期 */
    VOS_UINT8                           ucDsFlowOMRptTmrExpCnt;                 /* OM流量上报时机，用于控制上报周期 */
    VOS_UINT8                           aucReserved[1];


    VOS_UINT32                          ulFluxThresRptFlg;                      /* AP流量上报开启标记 */
    VOS_UINT32                          ulFluxThresKByte;                       /* AP流量上报门限, 单位KByte */
    VOS_UINT32                          ulFluxThresHigh;                        /* AP流量上报门限高四个字节, 单位Byte */
    VOS_UINT32                          ulFluxThresLow;                         /* AP流量上报门限低四个字节, 单位Byte */
    VOS_UINT32                          ulTotalFluxHigh;                        /* AP流量累计上报高四个字节, 单位Byte */
    VOS_UINT32                          ulTotalFluxLow;                         /* AP流量累计上报低四个字节, 单位Byte */

    TAF_APS_DSFLOW_STATS_STRU           astApsDsFlowStats[TAF_APS_MAX_RAB_NUM]; /* 保留以RABID为单位的流量数据 */

}TAF_APS_DSFLOW_STATS_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_APS_BUF_WAIT_L4A_CNF_MSG_INFO_STRU
 结构说明  : 缓存命令的信息结构
 1.日    期   : 2011年12月17日
   作    者   : h44270
   修改内容   : 新建
 2.日    期   : 2013年12月17日
   作    者   : Y00213812
   修改内容   : 修改成员类型
*****************************************************************************/
typedef struct
{
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId;
    VOS_UINT32                         *pulMsgInfo;
    VOS_UINT32                          ulMsgInfoLen;
    VOS_UINT32                          ulPara;
}TAF_APS_CMD_BUFFER_STRU;

/*****************************************************************************
 结构名    : TAF_APS_ENTRY_MSG_STRU
 结构说明  : 需要保存的入口消息
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新增，APS缓存消息，后续处理缓存时使用
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[TAF_APS_MAX_MSG_BUFFER_LEN];
} TAF_APS_ENTRY_MSG_STRU;

/*****************************************************************************
 结构名    : TAF_APS_CACHE_MSG_INFO_STRU
 结构说明  : 缓存的消息内容
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_APS_ENTRY_MSG_STRU              stMsgEntry;                             /* 缓存的具体内容 */
}TAF_APS_CACHE_MSG_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_APS_CACH_MSG_INFO_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ucCurrIndex;                            /* 记录当前处理缓存的index */
    VOS_UINT8                           ucCacheMsgNum;                          /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_APS_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_APS_MAX_MSG_QUEUE_NUM]; /* APS的消息队列数组，存储的是带通用消息头的消息 */
}TAF_APS_MSG_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_APS_PS_CALL_ANSWER_MSG_STRU
 结构说明  : 缓存呼叫应答消息
 1.日    期   : 2011年12月27日
   作    者   : s62952
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* TAF APS消息类型*/
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType;
    VOS_UINT8                           ucPdpid;
    VOS_UINT8                           ucReserved;
} TAF_APS_PS_CALL_ANSWER_MSG_STRU;


/*****************************************************************************
 结构名    : TAF_APS_FSM_NW_ACTIVATING_CTX_STRU
 结构说明  : 存放网络激活状态机的上下文信息
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_APS_PS_CALL_ANSWER_MSG_STRU     stAnswerMsg;

} TAF_APS_FSM_NW_ACTIVATING_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_APS_FSM_EXTRA_CTX_UNION
 结构说明  : 状态机状态描述结构,状态机上下文信息
 1.日    期   : 2012年1月11日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef union
{
    TAF_APS_FSM_NW_ACTIVATING_CTX_STRU  stNwActivatingCtx;

}TAF_APS_FSM_EXTRA_CTX_UNION;

/*****************************************************************************
 结构名    : TAF_APS_SUB_FSM_CTX_STRU
 结构说明  : 子状态机状态描述结构
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId;

    /* 当前状态 */
    VOS_UINT32                          ulState;                            /*  */

    /* 子状态机入口消息MSGID和内容  */
    TAF_APS_ENTRY_MSG_STRU              stEntryMsg;

    /* 状态机数据 */
    TAF_APS_FSM_EXTRA_CTX_UNION         unFsmCtx;
}TAF_APS_SUB_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_APS_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId;

    /* 当前状态 */
    VOS_UINT32                          ulState;                            /*  */
}TAF_APS_MAIN_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : PDP实体对应的状态机上下文
 结构说明  : 状态机状态描述结构
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_APS_MAIN_FSM_CTX_STRU           stMainFsm;                              /* 主状态机 */
    TAF_APS_SUB_FSM_CTX_STRU            stSubFsm;                               /* 子状态机 */

    /**************************************************************************
                        TAF APS 当前的网络状态和PS域的卡状态，各个状态机实体里面独立维护
    **************************************************************************/
    VOS_UINT8                           ucPdpId;                                /* 当前状态机所对应的PDP ID */
    VOS_UINT8                           ucCallActiveFlg;
    VOS_UINT8                           aucReserve[2];
}TAF_APS_PDP_ENTITY_FSM_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_APS_INTERNAL_MSG_BUF_STRU
 结构说明  : 内部消息队列的结构
 1.日    期   : 2011年12月27日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* 消息ID */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           aucBuf[TAF_APS_MAX_MSG_BUFFER_LEN];     /* 消息内容 */
}TAF_APS_INTERNAL_MSG_BUF_STRU;

/*****************************************************************************
 结构名    : TAF_APS_INTERNAL_MSG_QUEUE_STRU
 结构说明  : 保存APS内部消息的链表
 1.日    期   : 2011年12月27日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* TAF APS内部消息队列 */
    TAF_APS_INTERNAL_MSG_BUF_STRU       astApsMsgQueue[TAF_APS_MAX_MSG_QUEUE_SIZE];

    /* 发送消息临时缓存buff,申请局部变量时直接使用该空间,为了避免发送内部消息时
    占用较大的栈空间 */
    TAF_APS_INTERNAL_MSG_BUF_STRU       stSendMsgBuf;

    /*内部消息缓冲队列的索引尾指针*/
    VOS_UINT8                           ucTail;

    /*内部消息缓冲队列的索引头指针*/
    VOS_UINT8                           ucHeader;

    VOS_UINT16                          usReserved;
} TAF_APS_INTERNAL_MSG_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_APS_PDP_ACT_LIMIT_INFO_STRU
 结构说明  : AT&T定制 PDP激活受限NV项打开关闭标志，以及PDP激活失败次数
 1.日    期   : 2012年6月14日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdpActLimitFlg;                       /* 保存NV项打开关闭标志 */
    VOS_UINT8                           ucPdpActFailCount;                      /* 记录PDP激活失败次数 */
    VOS_UINT8                           aucReserved[2];                         /* 保留 四字节对齐 */
}TAF_APS_PDP_ACT_LIMIT_INFO_STRU;

/*****************************************************************************
 结构名称  : TAF_APS_PDN_TEARDOWN_POLICY_STRU
 结构说明  : PDN连接断开策略
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucAllowDefPdnTeardownFlg;
    VOS_UINT8                               aucReserved[3];
} TAF_APS_PDN_TEARDOWN_POLICY_STRU;

/*****************************************************************************
 结构名    : TAF_APS_CONTEXT_STRU
 结构说明  : TAF APS 模块运行上下文
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 新建

  2.日    期   : 2012年6月15日
    作    者   : m00217266
    修改内容   : 添加TAF_APS_Data_PDP_ACT_LIMIT_STRU变量(AT&T定制 PDP激活受限)

  3.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: 添加呼叫建立保护定时器时长数组

  4.日    期   : 2014年11月1日
    作    者   : A00165503
    修改内容   : DTS2014122908593: 增加PDN连接断开策略
*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        存储L模的默认承载
    **************************************************************************/
    TAF_APS_CDATA_CTX_STRU                  stCdataCtx;                         /* 存放CDMA数据业务维护的Dormant Timer以及EPDSZID信息 */

    /**************************************************************************
                        TAF APS状态机状态
    **************************************************************************/
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU         astPdpEntityFsmCtx[TAF_APS_MAX_PDPID];   /* 当前最多11个PDP上下文，因此有11个独立的状态机 */
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU        *pstCurrPdpEntityFsmCtx;                    /* 当前所使用的实体状态机 */

    TAF_APS_TIMER_CTX_STRU                  astApsTimerCtx[TAF_APS_MAX_TIMER_NUM];  /* APS当前正在运行的定时器资源 */
    TAF_APS_DSFLOW_STATS_CTX_STRU           stApsDsFlowCtx;                         /* APS流量统计上下文 */

    /**************************************************************************
                        TAF APS缓存消息队列
    **************************************************************************/
    TAF_APS_MSG_QUEUE_STRU                  stBufferEntryMsgQueue;              /* APS的缓存消息队列 */

    /**************************************************************************
                        TAF APS缓存命令队列
    **************************************************************************/
    TAF_APS_CMD_BUFFER_STRU                 astCmdBufferQueue[TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE]; /* 等待L4A设置查询结果的队列 */

    /**************************************************************************
                        APS 内部消息缓存队列
    **************************************************************************/
    TAF_APS_INTERNAL_MSG_QUEUE_STRU         stInternalMsgQueue;                     /* MM子层的内部消息队列 */

    TAF_APS_PDP_ACT_LIMIT_INFO_STRU         stPdpActLimitInfo;

    TAF_APS_SWITCH_DDR_RATE_INFO_STRU       stSwitchDdrRateInfo;                    /* DDR投票信息 */

    VOS_UINT32                              aulCallRemainTmrLen[TAF_MAX_CID + 1];   /* 记录激活剩余时长，保护上报次数 */

    TAF_APS_RAT_TYPE_ENUM_UINT32            enCurrSuspendRatType;                      /* 记录激活过程中挂起时的接入技术模式 */

    TAF_APS_RAT_TYPE_ENUM_UINT32            enCurrRatType;                          /* 记录当前的接入技术模式 */
    VOS_UINT32                              ulPsSimRegStatus;                       /* PS域SIM卡状态信息,VOS_TRUE:卡有效,VOS_FALSE:卡无效 */
    TAF_APS_RAT_TYPE_ENUM_UINT32            enDataServiceMode;                      /* 记录当前数据服务模式 */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                              ulExist1XService;                       /* 记录是否存在1X的数据服务 */
    VOS_UINT32                              ulClDelaySearch;                       /* CL模式下记录是否完成DO和LTE的搜网 */

    VOS_UINT32                              ulReadSim3GpdFileFlg;                   /* 记录每个3gpd ext 卡文件的读取状态 */
    VOS_UINT32                              ulIsAlreadyRead3GpdFile;                /* 标志3gpd卡文件是否已经读完 */
    VOS_UINT32                              ulPppAuthInfFromCardFlag;               /* 1x hrpd PPP鉴权过程中是否使用卡下发的用户名密码 1:取用卡中数据  0:用ap测数据*/
    TAF_APS_3GPD_OPERATION_INFO_STRU        st3GpdOpInfo;
    VOS_UINT32                              ulIsHrpdDisabled;
#endif

#if (FEATURE_ON == FEATURE_LTE)
    TAF_APS_PDN_TEARDOWN_POLICY_STRU        stPdnTeardownPolicy;
#endif

}TAF_APS_CONTEXT_STRU;

extern TAF_APS_CONTEXT_STRU             g_stTafApsCtx;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

TAF_APS_PDP_ENTITY_FSM_CTX_STRU* TAF_APS_GetPdpEntityFsm(
    VOS_UINT32                          ulMainFsmState,
    TAF_APS_FSM_ID_ENUM_UINT32          enSubFsmId,
    VOS_UINT32                          ulSubFsmState
);

VOS_VOID  TAF_APS_InitDsFlowCtx(
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsTimerCtx
);

TAF_APS_DSFLOW_STATS_CTX_STRU*  TAF_APS_GetDsFlowCtxAddr( VOS_VOID );

TAF_APS_TIMER_CTX_STRU*  TAF_APS_GetTimerCtxAddr( VOS_VOID );




TAF_APS_MSG_QUEUE_STRU* TAF_APS_GetCachMsgBufferAddr(VOS_VOID);


VOS_UINT8  TAF_APS_GetCacheNum( VOS_VOID );

VOS_VOID  TAF_APS_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_UINT32  TAF_APS_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID  TAF_APS_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_UINT32  TAF_APS_GetNextCachedMsg(
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg
);

VOS_VOID  TAF_APS_SetCurrPdpEntityMainFsmState(
    VOS_UINT32                          ulState
);


VOS_VOID  TAF_APS_SetCurrPdpEntitySubFsmState(
    VOS_UINT32                          ulState
);


VOS_VOID  TAF_APS_DelWaitInfoInL4aMsgRsltQueue(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType
);

VOS_UINT32  TAF_APS_SetPdpIdMainFsmState(
    VOS_UINT8                          ucPdpId,
    VOS_UINT32                         ulState
);

VOS_UINT32  TAF_APS_GetPdpIdMainFsmState(
    VOS_UINT8                          ucPdpId
);

VOS_UINT32  TAF_APS_CheckPdpServiceActivated(
    VOS_UINT8                          ucPdpId
);

VOS_UINT32  TAF_APS_SetPdpIdSubFsmState(
    VOS_UINT8                          ucPdpId,
    VOS_UINT32                         ulState
);

VOS_UINT32  TAF_APS_GetPdpIdSubFsmState(
    VOS_UINT8                          ucPdpId
);

VOS_VOID  TAF_APS_SaveWaitInfoInWaitL4aMsgRsltQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId,
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    VOS_UINT8                           ucOpId
);

TAF_APS_PDP_ENTITY_FSM_CTX_STRU* TAF_APS_GetCurrPdpEntityFsmAddr(VOS_VOID);


VOS_VOID  TAF_APS_InitCmdBufferQueue(
    TAF_APS_CMD_BUFFER_STRU            *pstCmdBufferQueue
);

TAF_APS_CMD_BUFFER_STRU  *TAF_APS_GetCmdBufferQueueAddr( VOS_VOID );

VOS_VOID  TAF_APS_DelItemInCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);

VOS_VOID  TAF_APS_SaveItemInCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                         *pulMsgInfo,
    VOS_UINT32                          ulMsgInfoLen,
    VOS_UINT32                          ulPara
);

TAF_APS_CMD_BUFFER_STRU  *TAF_APS_GetItemFromCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);


VOS_VOID TAF_APS_SetCurrPdpEntityFsmAddr(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_SaveCurrSubFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID  TAF_APS_InitMainFsmCtx(
    TAF_APS_MAIN_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  TAF_APS_InitSubFsmCtx(
    TAF_APS_SUB_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  TAF_APS_InitInternalBuffer(
    TAF_APS_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
);

VOS_VOID TAF_APS_QuitCurrSubFsm( VOS_VOID );

VOS_VOID TAF_APS_InitSubFsm(
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
);
VOS_VOID  TAF_APS_SetCurrFsmEntityPdpId(
    VOS_UINT8                           ucPdpId
);

VOS_UINT8  TAF_APS_GetCurrFsmEntityPdpId(VOS_VOID);

VOS_VOID  TAF_APS_SetCurrPdpEntitySimRegStatus(
    VOS_UINT32                          ulPsSimRegStatus
);

VOS_UINT32  TAF_APS_GetCurrPdpEntitySimRegStatus( VOS_VOID );

VOS_VOID  TAF_APS_SetCurrPdpEntityRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32                enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32  TAF_APS_GetCurrPdpEntityRatType( VOS_VOID );

TAF_APS_PDP_ENTITY_FSM_CTX_STRU*  TAF_APS_GetApsEntityFsmCtxAddr(
    VOS_UINT8                           ucPdpId
);





VOS_VOID  TAF_APS_SetCurrPdpEntityDataServiceMode(
    TAF_APS_RAT_TYPE_ENUM_UINT32                enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_GetCurrPdpEntityDataServiceMode(VOS_VOID);

TAF_APS_ENTRY_MSG_STRU* TAF_APS_GetCurrSubFsmMsgAddr(VOS_VOID);

TAF_APS_INTERNAL_MSG_BUF_STRU* TAF_APS_GetNextInternalMsg( VOS_VOID );
VOS_UINT32  TAF_APS_SndInternalMsg(
    VOS_VOID                           *pSndMsg
);
TAF_APS_INTERNAL_MSG_BUF_STRU *TAF_APS_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
);
VOS_VOID  TAF_APS_InitInternalMsgQueue(
    TAF_APS_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MM子层的内部消息队列 */
);
TAF_APS_CONTEXT_STRU*  TAF_APS_GetApsCtxAddr( VOS_VOID );

VOS_VOID  TAF_APS_SaveCachePsCallAnswerMsg(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    VOS_UINT8                           ucPdpid
);



TAF_APS_PDP_ACT_LIMIT_INFO_STRU* TAF_APS_GetPdpActLimitInfoAddr(VOS_VOID);
VOS_VOID TAF_APS_InitPdpActLimitInfo(VOS_VOID);



VOS_VOID TAF_APS_InitSwitchDdrInfo(VOS_VOID);
TAF_APS_SWITCH_DDR_RATE_INFO_STRU*  TAF_APS_GetSwitchDdrRateInfoAddr(VOS_VOID);

VOS_VOID TAF_APS_InitCallRemainTmrLen(VOS_VOID);
VOS_VOID TAF_APS_SetCallRemainTmrLen(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulTmrLen
);
VOS_UINT32 TAF_APS_GetCallRemainTmrLen(VOS_UINT8 ucCid);

VOS_VOID  TAF_APS_SetApsDmtTestStub(
    VOS_UINT32                          ulEnable
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_InitPdnTeardownPolicy(VOS_VOID);
TAF_APS_PDN_TEARDOWN_POLICY_STRU* TAF_APS_GetPdnTeardownPolicy(VOS_VOID);
VOS_UINT8 TAF_APS_GetAllowDefPdnTeardownFlg(VOS_VOID);
VOS_VOID TAF_APS_SetAllowDefPdnTeardownFlg(VOS_UINT8 ucAllowFlg);
#endif



TAF_APS_CID_IMS_CFG_TBL_STRU* TAF_APS_GetCidImsCfgTable(VOS_VOID);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_APS_IsEnterCdataEsting(VOS_VOID);
VOS_UINT32 TAF_APS_IsEnterCdataDiscing(VOS_VOID);

VOS_UINT32 TAF_APS_GetSocmDormantTiLen(VOS_VOID);

VOS_VOID TAF_APS_SetSocmDormantTiLen(
    VOS_UINT32                          ulDormantTiLen
);
VOS_VOID TAF_APS_InitCdataCtx( VOS_VOID );


VOS_VOID TAF_APS_SetCdataPppDeactTimerLen(
    VOS_UINT8                           ucPppDeactTiLen
);

VOS_UINT32 TAF_APS_GetCdataPppDeactTimerLen(VOS_VOID);

VOS_UINT8 TAF_APS_GetEhrpdAutoAttachFlag(VOS_VOID);

VOS_VOID TAF_APS_SetEhrpdAutoAttachFlag(
    VOS_UINT8                           ucAutoAttachFlag
);

VOS_VOID TAF_APS_SetPktCdataInactivityTimerLen(
    VOS_UINT8                           ucTimeLen
);

VOS_UINT8 TAF_APS_GetPktCdataInactivityTimerLen(VOS_VOID);


#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_APS_SetFsmCtxCdataDialMode(
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enDialMode
);

TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32 TAF_APS_GetFsmCtxCdataDialMode( VOS_VOID );




VOS_VOID  TAF_APS_Set1XPsServiceStatus(
    VOS_UINT32                          ulExist
);

VOS_UINT32  TAF_APS_Get1XPsServiceStatus(VOS_VOID);

VOS_VOID TAF_APS_FillEhsmSdfParaApnInfo(
    APS_EHSM_SDF_PARA_INFO_STRU         *pstSdfParaInfo,
    TAF_PDP_TABLE_STRU                  *pstTafCidInfo
);

VOS_VOID TAF_APS_FillEhsmSdfParaAuthInfo(
    APS_EHSM_SDF_PARA_INFO_STRU        *pstSdfParaInfo,
    VOS_UINT8                           ucCid
);



VOS_UINT32  TAF_APS_GetClDelaySearch(VOS_VOID);

VOS_VOID  TAF_APS_SetClDelaySearch(
    VOS_UINT32                          ulClDelaySearch
);


VOS_UINT32  TAF_APS_GetIsHrpdDisabledFlag(VOS_VOID);

VOS_VOID  TAF_APS_SetIsHrpdDisabledFlag(
    VOS_UINT32                           ulIsHrpdDisabled
);


VOS_VOID TAF_APS_SetFsmCtxCdataLastDialOnRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastOirgOnRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_GetFsmCtxCdataLastDialOnRatType(VOS_VOID);


VOS_UINT32 TAF_APS_GetUserCfgDormTiVal(VOS_VOID);

VOS_VOID TAF_APS_SetUserCfgDormTiVal(
    VOS_UINT32                          ulUserCfgDormTival
);

VOS_VOID TAF_APS_SetFsmCtxCdataSoInitType(
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSoInitType
);

TAF_APS_CDATA_SO_TYPE_ENUM_UINT16 TAF_APS_GetFsmCtxCdataSoInitType (VOS_VOID);

VOS_VOID TAF_APS_Init3GpdOpInfo(VOS_VOID);
TAF_APS_3GPD_OPERATION_INFO_STRU* TAF_APS_Get3GpdOpInfoAddr( VOS_VOID );
VOS_UINT32 TAF_APS_GetRead3GpdFileDoneFlag( VOS_VOID  );
VOS_VOID TAF_APS_SetRead3GpdFileDoneFlag(
    VOS_UINT32                          ulRead3GpdFileFlag
);
VOS_UINT32 TAF_APS_GetPppAuthInfoGetFromCardFlag( VOS_VOID );
VOS_VOID TAF_APS_SetPppAuthInfoGetFromCardFlag(
    VOS_UINT32                          ulIsPppAuthGetFromCard
);

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

#endif /* end of TafApsCtx.h */
