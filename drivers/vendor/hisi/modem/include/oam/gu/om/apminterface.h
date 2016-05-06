

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: APMInterface.h                                                  */
/*                                                                           */
/*    Author: Jiang KaiBo                                                    */
/*            Xu Cheng                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: process data of APM mailbox                                  */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/


#ifndef  _APM_INTERFACE_H
#define  _APM_INTERFACE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "vos.h"
#include "phyoaminterface.h"

/*---------------------------------------------*
 * 常数宏定义                                  *
 *---------------------------------------------*/

/*更新DSP NV相关代码*/
#define SHPA_TMR_LOAD_PHY_INTERVAL          5000

#define DSP_DATA_WRITE_OK                   0x5555AAAA
#define DSP_DATA_READ_OK                    0x5A5A5A5A

/*加载DSP结果*/
#define CPHY_DSP_LOAD_SUCCESS               0
#define CPHY_DSP_LOAD_FAILURE               1
#define CPHY_DSP_LOAD_TIMEOUT               2

/* 等待加载标志位生效 */
#define SHPA_PROTECT_DELAY_COUNT            (30)

/* 防止写DSP越界的保护字 */
#define COMM_EXT_DATA_MEM_PROTECT_BIT_1     0xAAAA
#define COMM_EXT_DATA_MEM_PROTECT_BIT_2     0x5555
#define COMM_EXT_DATA_MEM_PROTECT_BIT_3     0x5A5A
#define COMM_EXT_DATA_MEM_PROTECT_BIT_4     0x5A5A
#define COMM_EXT_DATA_MEM_PROTECT_BIT_5     0xA5A5
#define COMM_EXT_DATA_MEM_PROTECT_BIT_6     0xA5A5
#define COMM_EXT_DATA_MEM_PROTECT_BIT_7     0x5555
#define COMM_EXT_DATA_MEM_PROTECT_BIT_8     0xAAAA

#define SHPA_LDF_DELAY_TIME                 (340)   /* 保存临终遗言时需要延迟的时间 10ms,发送NMI 后马上访问DTCM会ARM挂死 */

#define SHPA_LDF_DELAY_1S_TIME              (34)   /* 保存临终遗言时需要延迟的时间 1ms,发送NMI 后马上访问DTCM会ARM挂死 */

#define SHPA_LDF_LOAD_PHY_DELAY_TIME        (400)   /* 上移DSP时加载DSP需要延时的时间 400ms */

#ifdef  __LDF_FUNCTION__
#define SHPA_Ldf_Check()                    UPHY_MNTN_PhyLdfFileSaving()
#endif

enum DSP_CONFIG_ERROR_EUNM
{
    DSP_NVREAD_NOERROR = 0,
    DSP_BOOTINFO_MEMERR,
    DSP_NVREAD_LENERR,
    DSP_NVREAD_READNVERR,
    DSP_NVREAD_ALLOCMEMERR,
    DSP_NVREAD_TOTALLENERR,
    DSP_LOAD_STATIC_ERROR,
    DSP_GET_COMMON_INFO_ERROR,
    DSP_CONFIG_INFO_TOO_LONG,
    DSP_ACTIVE_TIME_OUT,
    DSP_CONFIG_ERROR_BUTT
};
typedef VOS_UINT32 DSP_CONFIG_ERROR_EUNM_UINT32;

enum APM_CFG_STATE_EUNM
{
    APM_INIT_STATE   = 0,
    APM_SENDED_MSG,
    APM_RECEIVED_MSG,
    APM_CFG_STATE_BUTT
};
typedef VOS_UINT32 APM_CFG_STATE_EUNM_UINT32;

/*****************************************************************************
 枚举名    :DUALMODEM_SCENE_TYPE_ENUM_UINT16
 协议表格  :
 枚举说明  :通信组件CCPU DDR调频通道类型
*****************************************************************************/
enum
{
   DUALMODEM_SCENCE_GSM,
   DUALMODEM_SCENCE_WCDMA,
   DUALMODEM_SCENCE_APS,
   DUALMODEM_SCENCE_TL,
   DUALMODEM_SCENCE_GUDRX,
   DUALMODEM_SCENCE_BUTT,
};
typedef VOS_UINT16 DUALMODEM_SCENE_TYPE_ENUM_UINT16;

typedef struct
{
    VOS_UINT32                      ulDspNVConfigAddr;          /*从DSP获取的当前DSP NV的配置段地址*/
    VOS_UINT32                      ulDspNvTotalLen;            /*需要配置给DSP的NV项的长度*/
    VOS_UINT16                      *pusNVData;                 /*保存NV数据的内存空间*/
    DSP_CONFIG_ERROR_EUNM_UINT32    enErrorCode;                /*当前配置DSP错误原因值*/
    APM_CFG_STATE_EUNM_UINT32       enActiveState;
    APM_CFG_STATE_EUNM_UINT32       enLoadState;
    VOS_UINT32                      ulActiveResult;
    VOS_UINT32                      ulLoadResult;
    VOS_UINT32                      ulActiveSmPResult;          /*等待Active信号量的结果*/
    VOS_UINT32                      ulLoadSmPResult;            /*等待Load信号量的结果*/
    VOS_UINT32                      ulGetNvLenErrId;            /*获取NV长度错误的NV ID号*/
    VOS_UINT32                      ulGetNvErrId;               /*获取NV数据错误的NV ID号*/
    /*相关操作的时间戳记录*/
    VOS_UINT32                      ulGetNvLenSlice;            /*读取NV数据的时间戳*/
    VOS_UINT32                      ulRecNVReqSlice;            /*收到DSP NV请求时间戳*/
    VOS_UINT32                      ulConfigNVSlice;            /*配置dSP NV的时间*/
    VOS_UINT32                      ulDSPActiveSlice;           /*Active DSP的时间戳*/
    VOS_UINT32                      ulDSPActCnfSlice;           /*收到Active回复的时间戳*/
    VOS_UINT32                      ulDSPLoadSlice;             /*Load DSP的时间戳*/
    VOS_UINT32                      ulDSPLoadCnfSlice;          /*收到Load回复的时间戳*/
}DSP_CONFIG_CTRL_STRU;

/*发给OM的透明消息*/
typedef struct
{
    VOS_MSG_HEADER                       /* 该消息头填充TOOL_ID和PS的PID,保证消息能转发给相应的PS模块 */
    VOS_UINT16      usTransPrimId;       /* 固定填写0x5001*/
    VOS_UINT16      usReserve;
    VOS_UINT8       ucFuncType;          /*数据查询04,空口消息上报:02*/
    VOS_UINT8       ucReserve;
    VOS_UINT16      usAppLength;         /*下一个字节到包尾的长度*/
    VOS_UINT32      ulSn;                /* 上报消息的序列号 */
    VOS_UINT32      ulTimeStamp;         /*消息的时间戳，填当前的SOC Tick值*/
    VOS_UINT16      usPrimId;            /* 原语ID*/
    VOS_UINT16      usToolsId;           /* 工具ID */
    VOS_UINT8       aucData[4];
}PS_APM_OM_TRANS_IND_STRU;

typedef struct
{
    VOS_UINT16 *pusArray;
    VOS_UINT32 ulNum;
}APM_RF_NV_INFO_STRU;

typedef struct
{
    VOS_UINT32 ulDSPPowerDownState;
    VOS_UINT32 ulReserved[7];
}LDF_EXT_INFO_STRU;

/*---------------------------------------------*
 * 函数声明                                    *
 *---------------------------------------------*/

extern VOS_SEM g_aulShpaLoadPhySemaphor[MODEM_ID_BUTT];

extern VOS_SEM g_aulShpaActivePhySemaphor[MODEM_ID_BUTT];

extern VOS_UINT32 g_aulShpaCurSysId[MODEM_ID_BUTT];

extern DSP_CONFIG_CTRL_STRU g_astDspConfigCtrl[MODEM_ID_BUTT];

extern VOS_UINT16 SHPA_LoadPhy( PHY_OAM_SET_WORK_MODE_REQ_STRU  stSetWorkMode );

extern VOS_UINT32 APM_PIDInit( enum VOS_INIT_PHASE_DEFINE ip );

extern VOS_VOID SHPA_ActivateHw(VOS_VOID);

extern VOS_VOID SHPA_DeactivateHw(VOS_VOID);

extern VOS_UINT32 SHPA_ActiveDSP(VOS_RATMODE_ENUM_UINT32 enRatMode, MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_UINT32 SHPA_ReadWTxPower( VOS_VOID);

extern VOS_UINT32 GHPA_GetRealFN(MODEM_ID_ENUM_UINT16 enModemID);

/*****************************************************************************
 函 数 名  : DualModem_DDRQosUpdate
 功能描述  : CCPU通信组件DDR调频接口
 输入参数  : MODEM_ID_ENUM_UINT16 enModem                       当前Modem Id
             DUALMODEM_SCENE_TYPE_ENUM_UINT16   enSceneType     投票通道类型
             VOS_UINT32 ulValue                                 DDR实际投票频率
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月11日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT32 DualModem_DDRQosUpdate(MODEM_ID_ENUM_UINT16 enModem, DUALMODEM_SCENE_TYPE_ENUM_UINT16 enSceneType,  VOS_UINT32 ulValue);

#ifdef  __LDF_FUNCTION__
VOS_UINT32 SHPA_Ldf_Hifi_Saving(VOS_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _APM_INTERFACE_H */

