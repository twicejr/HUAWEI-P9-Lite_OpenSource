
#ifndef  VC_PHY_INTERFACE_H
#define  VC_PHY_INTERFACE_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "VcCallInterface.h"
#include "AppVcApi.h"
#include "VcCodecInterface.h"
#include "NasNvInterface.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "VcImsaInterface.h"
#endif
#include "VcComm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/
enum VC_GPHY_MSG_ID_ENUM
{
    /* VC->GDSP */
    ID_VC_GPHY_TEST_MODE_NOTIFY         = 0xE705,

    /* GDSP->VC */

    ID_VC_GPHY_MSG_BUTT
};
typedef VOS_UINT16 VC_GPHY_MSG_ID_ENUM_U16;

typedef struct
{
    VOS_INT16                           sTxVol[20];                             /* 发送音量，dB值, -80~12 */
    VOS_INT16                           sRxVol[20];                             /* 接收音量，dB值, -80~12 */
    VOS_UINT16                          usSlopeEnable;                          /* 预加重滤波使能 */
    VOS_INT16                           asSlopeCoeff[15];                       /* 预加重滤波系数 */
    VOS_UINT16                          usTxHpfEnable;                          /* 上行高通滤波使能 */
    VOS_INT16                           asTxHpfCoeff[8];                        /* 上行高通滤波系数 */
    VOS_UINT16                          usRxHpfEnable;                          /* 下行高通滤波使能 */
    VOS_INT16                           asRxHpfCoeff[8];                        /* 下行高通滤波系数 */
    VOS_INT16                           sDevTxGain;                             /* 设备输出增益（Codec发送增益） */
    VOS_INT16                           sDevRxGain;                             /* 设备输入增益（Codec接收增益） */
    VOS_INT16                           sSideGain;                              /* 侧音增益 */
    VOS_UINT16                          usTxCompEnable;                         /* 上行补偿使能 */
    VOS_INT16                           asTxCompCoeff[31];                      /* 上行补偿滤波系数 */
    VOS_UINT16                          usRxCompEnable;                         /* 下行补偿使能 */
    VOS_INT16                           asRxCompCoeff[31];                      /* 下行补偿滤波系数 */
    VOS_UINT16                          usEcEnable;                             /* 回声抑制使能：0 禁止；1 使能 */
    VOS_INT16                           asEcParam[20];                          /* EC参数 */
    VOS_UINT16                          usNsEnable;                             /* 噪声抑制使能：0 禁止；1 使能 */
    VOS_INT16                           asNsParam[10];                          /* NS参数 */
    VOS_UINT16                          usAgcEnable;                            /* 自动增益控制使能：0 禁止；1 使能 */
    VOS_INT16                           asAgcParam[6];                          /* AGC参数 */
}VC_DEVICE_PARA_NV_STRU;


typedef struct
{
    VC_PHY_DEVICE_MODE_ENUM_U16         enDeviceMode;                           /* 语音设备：0 手持；1 手持免提；2 车载免提；3 耳机；4 蓝牙 */
    VOS_INT16                           sTxVol;                                 /* 发送音量，dB值, -80~12 */
    VOS_INT16                           sRxVol;                                 /* 接收音量，dB值, -80~12 */
    VOS_UINT16                          usSlopeEnable;                          /* 预加重滤波使能 */
    VOS_INT16                           asSlopeCoeff[15];                       /* 预加重滤波系数 */
    VOS_UINT16                          usTxHpfEnable;                          /* 上行高通滤波使能 */
    VOS_INT16                           asTxHpfCoeff[8];                        /* 上行高通滤波系数 */
    VOS_UINT16                          usRxHpfEnable;                          /* 下行高通滤波使能 */
    VOS_INT16                           asRxHpfCoeff[8];                        /* 下行高通滤波系数 */
    VOS_INT16                           sDevTxGain;                             /* 设备输出增益（Codec发送增益） */
    VOS_INT16                           sDevRxGain;                             /* 设备输入增益（Codec接收增益） */
    VOS_INT16                           sSideGain;                              /* 侧音增益 */
    VOS_UINT16                          usTxCompEnable;                         /* 上行补偿使能 */
    VOS_INT16                           asTxCompCoeff[31];                      /* 上行补偿滤波系数 */
    VOS_UINT16                          usRxCompEnable;                         /* 下行补偿使能 */
    VOS_INT16                           asRxCompCoeff[31];                      /* 下行补偿滤波系数 */
    VOS_UINT16                          usEcEnable;                             /* 回声抑制使能：0 禁止；1 使能 */
    VOS_INT16                           asEcParam[20];                          /* EC参数 */
    VOS_UINT16                          usNsEnable;                             /* 噪声抑制使能：0 禁止；1 使能 */
    VOS_INT16                           asNsParam[10];                          /* NS参数 */
    VOS_UINT16                          usAgcEnable;                            /* 自动增益控制使能：0 禁止；1 使能 */
    VOS_INT16                           asAgcParam[6];                          /* AGC参数 */
    VOS_UINT16                          usReserve2;                             /* 保留 */
}VC_DEVICE_PARA_STRU;

/*****************************************************************************
 结构名    : VC_PHY_SET_DEVICE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止语音处理参数结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* 原语类型 */
    VOS_UINT16                          usReserve;                              /* 保留 */
    VC_DEVICE_PARA_STRU                 stDevPara;                              /* 保留 */
}VC_PHY_SET_DEVICE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* 原语类型 */
    VOS_UINT8                           aucReserved[2];
}VC_PHY_TEST_MODE_NOTIFY_STRU;

/*****************************************************************************
  4 宏定义
*****************************************************************************/





/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/


VOS_UINT32  APP_VC_SendStartReq(
    CALL_VC_CHANNEL_INFO_STRU           *pstChanInfo,
    CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode
);


VOS_VOID APP_VC_SendStopReq(CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode);

VOS_UINT32  APP_VC_SendSetDeviceReq(
    VC_PHY_DEVICE_MODE_ENUM_U16         enDeviceMode
);


VOS_UINT32  APP_VC_SendSetVolumeReq(
    VOS_UINT16                          usVolTarget,
    VOS_INT16                           sVolValue
);


VOS_VOID APP_VC_SendSetCodecReq(CALL_VC_CHANNEL_INFO_STRU *pstChanInfo);


VOS_VOID APP_VC_SendEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32  enCause
);



VOS_VOID APP_VC_SendPhyTestModeNotify(
    CALL_VC_RADIO_MODE_ENUM_U8              enMode
);



VOS_UINT32 APP_VC_SendSetForeGroundReq(VOS_VOID);


VOS_UINT32 APP_VC_SendSetBackGroundReq(VOS_VOID);


VOS_UINT32 APP_VC_SendGroundQry(VOS_VOID);


VOS_VOID APP_VC_SendSetForeGroundCnf(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);


VOS_VOID APP_VC_SendSetBackGroundCnf(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);


VOS_VOID APP_VC_SendGroundRsp(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_GROUND_ENUM_UINT16          enState ,
    VOS_UINT8                           ucQryRslt
);


VOS_UINT32 APP_VC_SendSetModemLoopReq(VCVOICE_LOOP_ENUM_UINT16 enVoiceLoop);


#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID APP_VC_SendImsaExceptionNtf(
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32                     enCause
);
#endif

VOS_VOID  APP_VC_LogEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause
);



VOS_VOID APP_VC_SendAtSetCnf(
    VOS_UINT16                          usMsgName,
    MN_CLIENT_ID_T                      usClientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);


VOS_VOID APP_VC_SendQryMsdCnf(
    MN_CLIENT_ID_T                      usClientId
);


VOS_VOID APP_VC_SendQryEcallCfgCnf(
    MN_CLIENT_ID_T                      usClientId
);



VOS_UINT32  APP_VC_SendEcallCfgReq(
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16   enMode,
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16 enVocConfig
);


VOS_VOID APP_VC_SendEcallTransStatusInd(
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8      enEcallTransStatus,
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  enEcallTransFailCause
);



VOS_VOID APP_VC_SendMsdReq(VOS_VOID);

VOS_UINT32 APP_VC_SendDtmfInd(
    VOICEVC_DTMF_IND_STRU              *pstDtmfInd
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32  APP_VC_SendSoCtrlOrderInd(
    VCVOICE_TYPE_ENUM_UINT16        enCodecType,
    VOS_UINT8                       ucORDQ
);

VOS_UINT32  APP_VC_SendSoCtrlMsgInd(
    VCVOICE_TYPE_ENUM_UINT16        enCodecType,
    SO_CTRL_MSG_CODEC_STRU         *pstCodec
);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* VC_PHY_INTERFACE_H */

