/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcComm.h
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
  2.日    期   : 2009-12-04
    作    者   : h44270
    修改内容   : 问题单号:AT2D15720,驱动接口清理
******************************************************************************/
#ifndef  VC_COMM_H
#define  VC_COMM_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnComm.h"
#include "VcCodecInterface.h"
#include "VcCallInterface.h"

/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define NV_COPY_DATA_OFFSET                     (80)
#define VC_VOLUME_DEFAULT_VALUE                 (-6)

/*回放用消息ID*/
#define EVT_NAS_VC_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa         /* 为PC工程回放定义的消息 */

#define APP_VC_VOICE_TEST_FLAG_DEFALUT                   (0x0)                  /* 频谱测试模式标志默认值，默认不启动频谱测试模式 */
#define APP_VC_VOICE_TEST_FLAG_ENABLE                    (0x55aa55aa)           /* 0x55aa55aa值频谱测试模式启动 */
#define APP_VC_VOICE_NORMAL_MODE_IN_QUICK_START          (0x34343434)           /* 0x34343434值频谱测试模式不启动 */

#define    APP_VC_QUICK_START_DISABLE    0x00000000
#define    APP_VC_QUICK_START_ENABLE     0x01000101
/*****************************************************************************
  3类型定义
*****************************************************************************/

/* VC定时器ID定义 */
enum APP_VC_TIMER_ID_ENUM
{
    APP_VC_TIMER_START,
    APP_VC_TIMER_STOP,
    APP_VC_TIMER_SET_DEV,
    APP_VC_TIMER_SET_VOLUME,
    APP_VC_TIMER_SET_CODEC,
    APP_VC_TIMER_SET_FOREGROUND,
    APP_VC_TIMER_SET_BACKGROUND,
    APP_VC_TIMER_QRY_GROUND,

    /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
    APP_VC_TIMER_SET_ECALL_CFG,
    /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

    APP_VC_TIMER_BUTT
};
typedef VOS_UINT16  APP_VC_TIMER_ID_ENUM_U16;

enum APP_VC_AUDIO_SAMPLE_RATE_ENUM
{
    APP_VC_SAMPLE_RATE_8K       =0,
    APP_VC_SAMPLE_RATE_11K025,
    APP_VC_SAMPLE_RATE_12K,
    APP_VC_SAMPLE_RATE_16K,
    APP_VC_SAMPLE_RATE_22K05,
    APP_VC_SAMPLE_RATE_24K,
    APP_VC_SAMPLE_RATE_32K,
    APP_VC_SAMPLE_RATE_44K1,
    APP_VC_SAMPLE_RATE_48K,
    APP_VC_SAMPLE_RATE_BUTT
};
typedef VOS_UINT16  APP_VC_AUDIO_SAMPLE_RATE_ENUM_U16;

enum APP_VC_AUDIO_IN_DEV_SELECT_ENUM
{
    APP_VC_AUDIO_IN_HEADSET_OUT_MIC         = 1,
    APP_VC_AUDIO_IN_HEADSET_INTERNAL_MIC    = 2,
    APP_VC_AUDIO_IN_HEADFREE_INTERNAL_MIC   = 4,
    APP_VC_AUDIO_IN_BUTT
};
typedef VOS_UINT16  APP_VC_AUDIO_IN_DEV_SELECT_ENUM_U16;

enum APP_VC_AUDIO_OUT_DEV_SELECT_ENUM
{
    APP_VC_AUDIO_OUT_HEADSET_EARPHONE   = 1,
    APP_VC_AUDIO_OUT_HEADSET_RECEIVER   = 2,
    APP_VC_AUDIO_OUT_HEADFREE_SPEAKER   = 4,
    APP_VC_AUDIO_OUT_BUTT
};
typedef VOS_UINT16  APP_VC_AUDIO_OUT_DEV_SELECT_ENUM_U16;

enum VC_NVIM_WORK_MODE_ENUM
{
    en_NV_Item_HANDSET_W_PARAM_ID           = 0X3000,                           /*W模手持工作参数ID*/
    en_NV_Item_HANDHELD_HANDFREE_W_PARAM_ID = 0X3001,                           /*W模手持免提工作参数ID*/
    en_NV_Item_VECHILE_HANDFREE_W_PARAM_ID  = 0X3002,                           /*W模车载免提工作参数ID*/
    en_NV_Item_HEADSET_W_PARAM_ID           = 0X3003,                           /*W模耳机工作参数ID*/
    en_NV_Item_BT_W_PARAM_ID                = 0X3004,                           /*W模蓝牙工作参数ID*/
    en_NV_Item_HANDSET_G_PARAM_ID           = 0X3005,                           /*G模手持工作参数ID*/
    en_NV_Item_HANDHELD_HANDFREE_G_PARAM_ID = 0X3006,                           /*G模手持免提工作参数ID*/
    en_NV_Item_VECHILE_HANDFREE_G_PARAM_ID  = 0X3007,                           /*G模车载免提工作参数ID*/
    en_NV_Item_HEADSET_G_PARAM_ID           = 0X3008,                           /*G模耳机工作参数ID*/
    en_NV_Item_BT_G_PARAM_ID                = 0X3009,                           /*G模蓝牙工作参数ID*/
    en_NV_Item_PCVOICE_PARAM_ID_W           = 0X300F,                           /*W PC VOICE工作参数ID*/

    en_NV_Item_ID_BUTT                      = 0X3100
};
typedef VOS_UINT16 VC_NVIM_WORK_MODE_ENUM_U16;

enum APP_VC_IOCTL_AUDIO_IN_DEV_ENUM
{
    APP_VC_IN_DEV_HEADSET_EXTERNAL_MIC = 1,
    APP_VC_IN_DEV_HANDSET_INTERNAL_MIC  = 2,
    APP_VC_IN_DEV_HANDFREE_INTERNAL_MIC = 4,

    APP_VC_IN_DEV_BUTT
};
typedef VOS_UINT16 APP_VC_IOCTL_AUDIO_IN_DEV_ENUM_U16;

enum APP_VC_IOCTL_AUDIO_OUT_DEV_ENUM
{
    APP_VC_OUT_DEV_HEADSET_EXTERNAL_MIC = 1,
    APP_VC_OUT_DEV_HANDSET_INTERNAL_MIC  = 2,
    APP_VC_OUT_DEV_HANDFREE_INTERNAL_MIC = 4,

    APP_VC_OUT_DEV_BUTT
};
typedef VOS_UINT16 APP_VC_IOCTL_AUDIO_OUT_DEV_ENUM_U16;



/*****************************************************************************
 结构名    : VC_OM_PCVOICE_TRANS_STATUS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :假消息VC_OM_PCVOICE_TRANS_STATUS_STRU的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                     usPcVoiceChannelOper;  /* 对PC VOICE语音通道进行的操作: 打开、修改、关闭*/
    VOS_UINT16                     usPort;                /* 语音通道端口 */
    VOS_UINT32                     usOmOperResult;        /* OM执行结果 */
} VC_OM_PCVOICE_TRANS_STATUS_STRU;


/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define APP_VC_INVALID_DEV_HANDLE                   -1

#define APP_VC_AUDIO_IOCTL_BASE                     0x30000000
#define APP_VC_IOCTL_AUDIO_PCM_MODE_SET             0x30000000 + 7
#define APP_VC_IOCTL_AUDIO_SAMPLE_RATE_SET          0x30000000 + 1
#define APP_VC_IOCTL_AUDIO_IN_DEV_SELECT            0x30000000 + 11
#define APP_VC_IOCTL_AUDIO_OUT_DEV_SELECT           0x30000000 + 12
#define APP_VC_IOCTL_AUDIO_IN_DEV_UNSELECT          0x30000000 + 14
#define APP_VC_IOCTL_AUDIO_OUT_DEV_UNSELECT         0x30000000 + 13
#define APP_VC_IOCTL_AUDIO_VOICE_OPEN               0x30000000 + 23
#define APP_VC_IOCTL_AUDIO_VOICE_CLOSE              0x30000000 + 24


/* 调试输出 */
#define VC_INFO_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str)
#define VC_NORM_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str)
#define VC_WARN_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str)
#define VC_ERR_LOG(str)       TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str)

#define VC_INFO_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str, x)
#define VC_NORM_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str, x)
#define VC_WARN_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x)
#define VC_ERR_LOG1(str, x)   TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str, x)

#define VC_WARN_LOG2(str, x1, x2)  TAF_LOG2(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x1, x2)

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
extern VOS_UINT32 WuepsVCPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);
extern VOS_VOID   APP_VC_MsgProc(MsgBlock* pMsg);
extern  VCVOICE_WORK_TYPE_ENUM_UINT16 APP_VC_GetWorkType(VOS_VOID);

/*****************************************************************************
 函 数 名  : NAS_VC_SndOutsideContextData
 功能描述  : 把VC外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月30日
    作    者   : 王毛 00166186
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_VC_SndOutsideContextData(VOS_VOID);

/*****************************************************************************
 函 数 名  : APP_VC_SendVCReqToOm
 功能描述  : 将VC的异步请求发送到OM所在任务处理
 输入参数  : ulStatus - 命令类型
 输出参数  : ulPort   - 端口号
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : f00179208
    修改内容   : 新增，AT移植项目:将OM_PcvTransStatus接口改为异步消息发给OM
*****************************************************************************/
VOS_UINT32  APP_VC_SendVcReqToOm(VOS_UINT32 ulStatus, VOS_UINT32 ulPort);

VCVOICE_TYPE_ENUM_UINT16 APP_VC_ConvertCallCodeTypeToVodecType(
    CALL_VC_CODEC_TYPE_ENUM_U8       enCodeType
);


#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 函 数 名  : NAS_VC_RestoreContextData
 功能描述  : 恢复VC全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月1日
    作    者   : 王毛 00166186
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_VC_RestoreContextData(struct MsgCB * pMsg);
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

#endif /* VC_COMM_H */

