/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcPhyInterface.h
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2009年7月05日
  最近修改   : 2009年7月05日
  功能描述   : VC模块和HPA之间的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2009年7月05日
    作    者   : h44270
    修改内容   : 创建文件
******************************************************************************/
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
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-09, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include "VcImsaInterface.h"
#endif
#include "VcComm.h"

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-09, end */

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

/*****************************************************************************
 结构名    : VC_PHY_TEST_MODE_NOTIFY_STRU
 结构说明  : 通知物理层进入测试模式
 1.日    期   : 2012年3月8日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
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
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-31, begin */
/* Deleted by wx270776 for OM融合, 2015-7-16, begin */
/* Deleted by wx270776 for OM融合, 2015-7-16, end */
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-31, end */

/*****************************************************************************
函 数 名  : APP_VC_SendStartReq
功能描述  : 发送消息ID_VC_CODEC_START_REQ给物理层
输入参数  : pstChanInfo - 信道信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年07月05日
    作    者   : h44270
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32  APP_VC_SendStartReq(
    CALL_VC_CHANNEL_INFO_STRU           *pstChanInfo,
    CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode
);

/*****************************************************************************
函 数 名  : APP_VC_SendStopReq
功能描述  : 发送消息VC_PHY_STOP_REQ给物理层
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年07月05日
    作    者   : h44270
    修改内容   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendStopReq(CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode);

VOS_UINT32  APP_VC_SendSetDeviceReq(
    VC_PHY_DEVICE_MODE_ENUM_U16         enDeviceMode
);

/*****************************************************************************
函 数 名  : APP_VC_SendSetVolumeReq
功能描述  : 发送消息VC_PHY_SET_VOLUME_REQ给物理层
输入参数  : pstChanInfo - 信道信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年07月05日
    作    者   : h44270
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32  APP_VC_SendSetVolumeReq(
    VOS_UINT16                          usVolTarget,
    VOS_INT16                           sVolValue
);

/*****************************************************************************
函 数 名  : APP_VC_SendSetCodecReq
功能描述  : 发送消息VC_PHY_SET_CODEC_REQ给物理层
输入参数  : pstChanInfo - 信道信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年07月05日
    作    者   : h44270
    修改内容   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendSetCodecReq(CALL_VC_CHANNEL_INFO_STRU *pstChanInfo);

/*****************************************************************************
函 数 名  : APP_VC_SendEndCallReq
功能描述  : 发送挂断电话消息给CALL模块
输入参数  : pstChanInfo - 信道信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年07月05日
    作    者   : h44270
    修改内容   : Creat
2.  日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID APP_VC_SendEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32  enCause
);


/*****************************************************************************
函 数 名  : APP_VC_SendPhyTestModeNotify
功能描述  : 发送消息ID_VC_GPHY_TEST_MODE_NOTIFY给DSP测试模式通知
输入参数  : enMode - 接入模式
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2012年03月08日
    作    者   : h44270
    修改内容   : 新建

*****************************************************************************/
VOS_VOID APP_VC_SendPhyTestModeNotify(
    CALL_VC_RADIO_MODE_ENUM_U8              enMode
);


/*****************************************************************************
函 数 名  : APP_VC_SendSetForeGroundReq
功能描述  : VC 下发 CODEC 设置前向模式设置请求
输入参数  : pstMsg - 待发送消息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2012年12月28日
    作    者   : 张鹏/00214637
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 APP_VC_SendSetForeGroundReq(VOS_VOID);

/*****************************************************************************
函 数 名  : APP_VC_SendSetBackGroundReq
功能描述  : VC 下发 CODEC 设置后向模式设置请求
输入参数  : pstMsg - 待发送消息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2012年12月28日
    作    者   : 张鹏/00214637
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 APP_VC_SendSetBackGroundReq(VOS_VOID);

/*****************************************************************************
函 数 名  : APP_VC_SendGroundQry
功能描述  : VC 下发 CODEC 查询前向模式设置请求
输入参数  : pstMsg - 待发送消息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2012年12月28日
    作    者   : 张鹏/00214637
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 APP_VC_SendGroundQry(VOS_VOID);

/*****************************************************************************
函 数 名  : APP_VC_SendSetForeGroundCnf
功能描述  : VC 发送 AT 前向模式设置回复消息
输入参数  : clientId--AT Client ID,enExeRslt--设置请求操作结果
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2012年12月28日
    作    者   : 张鹏/00214637
    修改内容   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendSetForeGroundCnf(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);

/*****************************************************************************
函 数 名  : APP_VC_SendSetBackGroundCnf
功能描述  : VC 发送 AT 后向模式设置回复消息
输入参数  : clientId--AT Client ID,enExeRslt--设置请求操作结果
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2012年12月28日
    作    者   : 张鹏/00214637
    修改内容   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendSetBackGroundCnf(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);

/*****************************************************************************
函 数 名  : APP_VC_SendGroundRsp
功能描述  : VC 发送 AT 查询前向模式回复消息
输入参数  : clientId--AT Client ID,enState--查询状态，ucQryRslt--查询操作结果
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2012年12月28日
    作    者   : 张鹏/00214637
    修改内容   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendGroundRsp(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_GROUND_ENUM_UINT16          enState ,
    VOS_UINT8                           ucQryRslt
);

/*****************************************************************************
 函 数 名  : APP_VC_SendSetModemLoopReq
 功能描述  : VC发送Codec设置语音环回模式的消息
 输入参数  : VCVOICE_LOOP_ENUM_UINT16 enVoiceLoop
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 APP_VC_SendSetModemLoopReq(VCVOICE_LOOP_ENUM_UINT16 enVoiceLoop);


/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-18, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID APP_VC_SendImsaExceptionNtf(
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32                     enCause
);
#endif

VOS_VOID  APP_VC_LogEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause
);

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-18, end */

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
/*****************************************************************************
函 数 名  : APP_VC_SendAtSetCnf
功能描述  : VC回复AT设置消息
输入参数  : usMsgName -- 消息名称
            clientId--AT Client ID
            enExeRslt--设置操作结果
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修订记录  :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SendAtSetCnf(
    VOS_UINT16                          usMsgName,
    MN_CLIENT_ID_T                      usClientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);

/*****************************************************************************
函 数 名  : APP_VC_SendQryMsdCnf
功能描述  : VC回复AT MSD 查询结果
输入参数  : clientId--AT Client ID
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :
修订记录  :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SendQryMsdCnf(
    MN_CLIENT_ID_T                      usClientId
);

/*****************************************************************************
函 数 名  : APP_VC_SendQryEcallCfgCnf
功能描述  : VC回复AT eCall配置查询结果
输入参数  : clientId--AT Client ID
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :
修订记录  :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SendQryEcallCfgCnf(
    MN_CLIENT_ID_T                      usClientId
);


/*****************************************************************************
函 数 名  : APP_VC_SendEcallCfgReq
功能描述  : 发送消息ID_VC_VOICE_SET_ECALLCFG_REQ给MED
输入参数  :
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_UINT32  APP_VC_SendEcallCfgReq(
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16   enMode,
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16 enVocConfig
);

/*****************************************************************************
函 数 名  : APP_VC_SendEcallTransStatusInd
功能描述  : 发送消息VC_CALL_ECALL_TRANS_STATUS_NTF给Call模块
输入参数  : enEcallTransStatus  --传送状态
            enEcallTransFailCause -- 失败原因
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SendEcallTransStatusInd(
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8      enEcallTransStatus,
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  enEcallTransFailCause
);


/*****************************************************************************
函 数 名  : APP_VC_SendMsdReq
功能描述  : 发送MSD数据给MED模块
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :
修订记录  :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SendMsdReq(VOS_VOID);
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

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

