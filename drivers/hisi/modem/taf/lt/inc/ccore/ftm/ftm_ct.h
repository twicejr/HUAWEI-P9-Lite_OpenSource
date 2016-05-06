/******************************************************************************

                  版权所有 (C), 1998-2010, 华为技术有限公司

*****************************************************************************
  文 件 名   : ftm_ct.h
  版 本 号   : V1.0
  作    者   : 陈文峰/00149739
  生成日期   : 2010-05-14
  功能描述   : TODO: ...

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2010-05-14
    作    者 : 陈文峰/00149739
    修改内容 : 创建文件

******************************************************************************/

/******************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
******************************************************************************/

#ifndef __FTM_CT_H__
#define __FTM_CT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gen_msg.h"
#include "TafAppMma.h"

#define FTM_CT_NORMAL             (0) /* 表明该请求没有堵塞 */
#define FTM_CT_WAIT               (1) /* 表明该请求有等待，持续请求直接返回错误 */

#define FTM_CT_OVER_TIME          3000 /* DSP原语返回超时时间(ms) */

typedef struct
{
    VOS_UINT32 ulReqTimer;

    /* FTM_CT_NORMAL: mean normal; FTM_CT_WAIT: mean WAIT */
    VOS_UINT8 ucSta;
    VOS_UINT8 ucRsv1;
    VOS_UINT8 ucRsv2;
    VOS_UINT8 ucRsv3;
} FTM_CTCMD_CTRL_STRU;

typedef struct
{
    FTM_RD_FCHAN_CNF_STRU stCurFchan;    /* AT查询接口上下行信道设置均需返回，因此全局变量保存CNF结构 */
    FTM_TXON_SWT_ENUM enCurTxon;         /* 发射机打开状态 */
    FTM_RXON_SWT_ENUM enCurRxon;         /* 接收机打开状态 */
    FWAVE_TYPE_ENUM   enCurFwaveType;    /* 非信令波形 */
    VOS_UINT16             usCurFwavePower;   /* 非信令功率 单位0.01db */
    VOS_UINT16             usCurVctcxoVol;    /* VCTCXO电压值 */
#if (FEATURE_LTE_4RX == FEATURE_ON)
    VOS_UINT16             usRssiVal1;
    VOS_UINT16             usRssiVal2;
    VOS_UINT16             usRssiVal3;
    VOS_UINT16             usRssiVal4;
#else
    VOS_INT16              sCurRssiVal;       /* 接收信号测量值 */
#endif
    VOS_UINT8              ucCurLnaLvl;       /* LNA档位 */
    VOS_UINT8              ucNoSigFlg;        /* 非信令模式是否打开 */
    VOS_UINT8              ucTselrfPath;      /* 射频通路编号 */
    VOS_UINT8              ucTselrfGroup;     /* 可选参数，对于第一个参数<path>无法准确说明的时候使用 */
} FTM_CT_MANAGE_INFO_STRU;

/***********************************************

命令执行标志:

1、用于命令间有依赖关系时，判断依赖命令是否完成
2、仅当命令执行成功返回才置相应标志
3、BANDSW之后置为初始状态CT_F_STEPS_DONE_NULL(还有什么时候?)
3、最多支持32个命令执行标志的判断，目前仅使用了9个

TODO:增加判断是否已成功执行某些命令的宏

chenpeng/00173035 2010-12-18

************************************************/
enum FTM_CT_F_CMD_STEPS_FLAG_ENUM
{
	CT_F_STEPS_DONE_NULL      =  0x00000000,  /* 初始状态:当前没有执行任何命令 */
	CT_F_STEPS_DONE_BANDSW    =  0x00000001,  /* 已成功执行命令AT^BANDSW */
	CT_F_STEPS_DONE_FCHANS    =  0x00000002,  /* 已成功执行命令AT^FCHANS */
	CT_F_STEPS_DONE_FSEGMENT  =  0x00000004,  /* 已成功执行命令AT^FSEGMENT */
	CT_F_STEPS_DONE_FPOWS     =  0x00000008,  /* 已成功执行命令AT^FPOWS */
	CT_F_STEPS_DONE_FPAS      =  0x00000010,  /* 已成功执行命令AT^FPAS */
	CT_F_STEPS_DONE_FLNAS     =  0x00000020,  /* 已成功执行命令AT^FLNAS */
	CT_F_STEPS_DONE_FTXWAVE   =  0x00000040,  /* 已成功执行命令AT^FTXWAVE */
	CT_F_STEPS_DONE_FSTART    =  0x00000080,  /* 已成功执行命令AT^FSTART */
	CT_F_STEPS_DONE_FRSSIS_IND=  0x00000100,  /* FSTART 执行后,RSSI已经成功主动上报*/
	CT_F_STEPS_DONE_FCMTMS_IND=  0x00000200,  /* FSTART 执行后,芯片温度值已经成功主动上报*/

    CT_F_STEPS_DONE_FBLK        = 0x00000400, /* 已经成功执行AT^FBLK */
    CT_F_STEPS_DONE_FIPSTART   = 0x00000800,  /* 已经成功执行AT^FIPSTART */
    CT_F_STEPS_DONE_FPAPOWER   = 0x00001000,  /* 已经成功执行AT^FPAPOWER */
    CT_F_STEPS_DONE_FMAXPOWER   = 0x00002000, /* 已经成功执行AT^FMAXPOWER */
    CT_F_STEPS_DONE_FPDMS      = 0X00004000,  /* 已经成功执行AT^fpdms */
	CT_F_STEPS_DONE_FPDPOWS      = 0X00080000,  /* 已经成功执行AT^fpdpows */

	CT_F_STEPS_DONE_BUTT
};
typedef VOS_UINT32    FTM_CT_F_CMD_STEPS_FLAG_ENUM_UINT32;

#define FTM_F_CT_STORE_REQ_TEMP    (0)  /* 请求命令发送后，立刻保存请求内容到静态变量 */
#define FTM_F_CT_STORE_REQ_GLOBAL  (1)  /* 收到响应，即命令发送成功后，将静态变量中的值保存到全局结构 */

typedef struct
{
	FTM_CT_F_CMD_STEPS_FLAG_ENUM_UINT32 ulCurCmdStepsFlag;	 /*当前已执行步骤标志*/

	FCHAN_MODE_ENUM enCurMode;                               /* BANDSW MODE*/
	VOS_UINT8  ucCurBand;                                         /* BANDSW BAND*/
    VOS_UINT8  ucCurWaveType;                                     /* FTXWAVE:发射波形*/
    VOS_UINT8  ucCurTriggerType;                                  /* FSTART:校准类型 */

    VOS_UINT8  ucPadding1;

	VOS_UINT16 usCurSegmentLen;                                   /* FSEGMENT:10,20毫秒 */
    VOS_UINT16 usCurMeasOffset;                                   /* FSEGMENT:测量偏移百分比，取值范围0~100 */
	VOS_UINT16 usCurMeasLen;                                      /* FSEGMENT:测量长度百分比，取值范围0~100 */

	VOS_UINT16 usCurUlListNum;                                    /* FAHSNS:上行设置的个数，对应ausUlFreqInfo，最多16个 */
    VOS_UINT16 usCurDlListNum;                                    /* FAHSNS:下行设置的个数，对应ausDlFreqInfo，最多16个 */

    VOS_UINT16 usCurTxPowerNum;                                   /* FPOWS:指定在asTxPower的个数 */
    VOS_UINT16 usCurPaLevelNum;                                   /* FPAS */
	VOS_UINT16 usCurAagcNum;                                      /* FLNAS */
    VOS_UINT16 usCmtmsNum; 					     				 /* 温度值数量，取值范围为0～16 */
    VOS_UINT16 usRsv;

    VOS_UINT16 ausCurUlFreqInfo[CT_F_FREQ_LIST_MAX_NUM];          /* FAHSNS:上行频点信息 */
    VOS_UINT16 ausCurDlFreqInfo[CT_F_FREQ_LIST_MAX_NUM];          /* FAHSNS:下行频点信息 */
    VOS_INT16 asCurTxPowerList[CT_F_TXPOW_SET_MAX_NUM];         /* FPOWS:上行发射功率*/
    VOS_UINT8  aucCurPaLevelList[CT_F_PA_SET_MAX_NUM];            /* FPAS */
    VOS_UINT8  aucCurAagcList[CT_F_AAGC_SET_MAX_NUM];             /* FLNAS:AAGC增益值 */

	/* 校准RSSI缓存 */
	VOS_UINT16 ausRxANT1RSSI[CT_F_FREQ_LIST_MAX_NUM][CT_F_TXPOW_SET_MAX_NUM]; /* FRSSIS:下行信道天线1的RSSI的测量值缓存*/
	VOS_UINT16 ausRxANT2RSSI[CT_F_FREQ_LIST_MAX_NUM][CT_F_TXPOW_SET_MAX_NUM]; /* FRSSIS:下行信道天线2的RSSI的测量值缓存*/

    VOS_UINT16 ausCmtms[CT_F_FREQ_LIST_MAX_NUM]; /* 温度值列表，取值范围为0～256，若温度值数量为0则没有温度值列表 */

    VOS_UINT8 padding[2];

    VOS_UINT32 ulBlocking;

	VOS_UINT32 ulChannel;

	VOS_UINT32 ulFpapower_usPaLeverNum;/* ^fpapower */
	VOS_UINT16 usFpapower_list[CT_F_TXPOW_SET_MAX_NUM];
	VOS_UINT32 ulFmaxpower_usPaLevelNum;/* ^fmaxpower */
	VOS_UINT32 ulFmaxpower_usPaReduceGain;/* ^fmaxpower */

	VOS_UINT32 ulFpdmsSw;    /* at^fpdms */

    FTM_SET_FCALIIP2S_REQ_STRU stFCaliIp2sSetReq;
    FTM_RD_FCALIIP2S_CNF_STRU  stFCaliIp2sRdCnf;

    FTM_SET_FGAINSTATES_REQ_STRU stFGainStatesSetReq;

    FTM_SET_FCALIDCOCS_REQ_STRU stFCaliDcocsSetReq;
    FTM_RD_FCALIDCOCS_CNF_STRU  stFCaliDcocsRdCnf;

    FTM_SET_FCALIIP2SMRF_REQ_STRU stFCaliIp2sMrfSetReq;
    FTM_RD_FCALIIP2SMRF_CNF_STRU  stFCaliIp2sMrfRdCnf;

    FTM_SET_FCALIDCOCSMRF_REQ_STRU stFCaliDcocsMrfSetReq;
    FTM_RD_FCALIDCOCSMRF_CNF_STRU  stFCaliDcocsMrfRdCnf;

	FTM_SET_FDBBATTS_REQ_STRU stFDbbAttSetReq;

	FTM_SET_FBBATTS_REQ_STRU  stFBbAttSetReq;

	FTM_SET_FCALITXIQS_REQ_STRU  stFCaliTxiqSetReq;
    FTM_RD_FCALITXIQS_CNF_STRU  stFCaliTxiqRdCnf;
	FTM_SET_F_FCALPDDCS_REQ_STRU stFCalPDDCSSetReq;
	FTM_RD_F_FCALPDDCS_CNF_STRU stFCalPDDCSRdCnf;
	FTM_SET_F_FPDPOWS_REQ_STRU stFpdpowsSetReq;
	FTM_RD_FQPDDCRES_CNF_STRU stFQPDDCRESRdCnf;
} FTM_CT_F_MANAGE_INFO_STRU;

/* 非信令综测 */
enum FTM_SYN_CMD_STEPS_FLAG_ENUM
{
	CT_S_STEPS_DONE_NULL      =  0x00000000,  /* 初始状态:当前没有执行任何命令 */

	CT_S_STEPS_DONE_SSYNC           =  0x00000001,  /* 已成功执行命令AT^BANDSW */
	CT_S_STEPS_DONE_SSYNC_IND      = 0x00000002,
	CT_S_STEPS_DONE_STXBW           =  0x00000004,  /* 已成功执行命令AT^FCHANS */
	CT_S_STEPS_DONE_STXCHAN         =  0x00000008,  /* 已成功执行命令AT^FSEGMENT */
	CT_S_STEPS_DONE_SSUBFRAME       =  0x00000010,  /* 已成功执行命令AT^FPOWS */
	CT_S_STEPS_DONE_SPARA           =  0x00000020,  /* 已成功执行命令AT^FPAS */
	CT_S_STEPS_DONE_SSEGNUM         =  0x00000040,  /* 已成功执行命令AT^FLNAS */
	CT_S_STEPS_DONE_STXMODUS        =  0x00000080,  /* 已成功执行命令AT^FTXWAVE */
	CT_S_STEPS_DONE_STXRBNUMS       =  0x00000100,  /* 已成功执行命令AT^FSTART */
	CT_S_STEPS_DONE_STXRBPOSS       =  0x00000200,  /* FSTART 执行后,RSSI已经成功主动上报*/
	CT_S_STEPS_DONE_STXPOWS         =  0x00000400,  /* FSTART 执行后,芯片温度值已经成功主动上报*/

    CT_S_STEPS_DONE_STXCHANTYPES   = 0x00000800,  /* 已经成功执行AT^FBLK */
    CT_S_STEPS_DONE_SSEGLEN         = 0x00001000, /* 已经成功执行AT^FIPSTART */
	CT_S_STEPS_DONE_SRXPOW          = 0x00002000, /* 已经成功执行AT^FIPSTART */
	CT_S_STEPS_DONE_SRXSUBFRA      = 0x00004000, /* 已经成功执行AT^FIPSTART */
	CT_S_STEPS_DONE_SRXBLER        = 0x00008000, /* 已经成功执行AT^FIPSTART */
	CT_S_STEPS_DONE_SRXBLER_IND    = 0x00010000,
	CT_S_STEPS_DONE_SSTART         = 0x00020000, /* 已经成功执行AT^FIPSTART */
	CT_S_STEPS_DONE_SSTOP          = 0x00040000, /* 已经成功执行AT^FIPSTART */
	CT_S_STEPS_DONE_SRXSET         = 0x00080000, /* 已经成功执行AT^SRXSET */
	CT_S_STEPS_DONE_TMODE_7_REQ   = 0x00100000,

	CT_S_STEPS_DONE_SSYNC_CNF     = 0x00200000,
	CT_S_STEPS_DONE_SSTART_CNF    = 0x00400000,
	CT_S_STEPS_DONE_STCFGDPCH    = 0x00800000,   /* 已经成功执行 AT^STCFGDPCH  */
	CT_S_STEPS_DONE_FPOW         = 0x01000000,    /* 已经成功执行 AT^FPOW  */
	CT_S_STEPS_DONE_STRXBER_IND   = 0x02000000,    /* TDS 下DSP主动上报BER 执行*/
	CT_S_STEPS_DONE_BUTT
};

typedef VOS_UINT32    FTM_SYN_CMD_STEPS_FLAG_ENUM_UINT32;

#define FTM_SYN_STORE_REQ_TEMP    (0)  /* 请求命令发送后，立刻保存请求内容到静态变量 */
#define FTM_SYN_STORE_REQ_GLOBAL  (1)  /* 收到响应，即命令发送成功后，将静态变量中的值保存到全局结构 */


typedef struct
{
	FTM_SYN_CMD_STEPS_FLAG_ENUM_UINT32 ulCurCmdStepsFlag;	 /*当前已执行步骤标志*/

	FTM_RD_SSYNC_CNF_STRU     stSsyncRdCnf;
	FTM_RD_STXBW_CNF_STRU     stStxbwRdCnf;
	FTM_RD_STXCHAN_CNF_STRU   stStxchanRdCnf;
	FTM_RD_SSUBFRAME_CNF_STRU stSsubframeRdCnf;
    FTM_RD_SPARA_CNF_TOTAL_STRU stSparaRdCnf;
	FTM_RD_SSEGNUM_CNF_STRU   stSsegnumRdCnf;
	FTM_RD_STXMODUS_CNF_STRU  stStxmodusRdCnf;
	FTM_RD_STXRBNUMS_CNF_STRU stStxrbnumsRdCnf;
	FTM_RD_STXRBPOSS_CNF_STRU stStxrbpossRdCnf;
	FTM_RD_STXPOWS_CNF_STRU   stStxpowsRdCnf;
	FTM_RD_STXCHANTYPES_CNF_STRU stStxchantypesRdCnf;
	FTM_RD_SSEGLEN_CNF_STRU   stSseglenRdCnf;
	FTM_RD_SRXSET_CNF_STRU   stSrxsetRdCnf;
	FTM_RD_SRXPOW_CNF_STRU    stSrxpowRdCnf;
	FTM_RD_SRXSUBFRA_CNF_STRU stSrxsubfraRdCnf;
	FTM_RD_SRXBLER_CNF_STRU   stSrxblerRdCnf;
      FTM_SET_SPARA_REQ_STRU    stFtmSparaInfo;    /* BT save at^spara*/
	FTM_RD_STRXBER_CNF_STRU   stStrxBerRdCnf;          /*BT tds综测BER结果 */
	FTM_RD_SSTART_CNF_STRU    stSstartRdCnf;

}FTM_SYN_INFO_STRU;

typedef struct
{
    FTM_RESET_CALLBACK_PFN pfnResetSymFunc;

    /* 普通校准默认值及运行时数据保持*/
    FTM_CT_MANAGE_INFO_STRU stFtmCtInfo;

	/* 快速校准默认值及运行时数据保持*/
	FTM_CT_F_MANAGE_INFO_STRU stFtmFastCtInfo;

	FTM_SYN_INFO_STRU stFtmSynInfo;

    /* 系统模式 */
    SYM_TMODE_ENUM symMode;

    FTM_RD_LTCOMMCMD_CNF_STRU stRdLtCommCmdCnf;


} FTM_MAIN_INFO_STRU;

typedef struct
{
    VOS_UINT16 usDlLowFreq; /* 本频段下行起始频率, LTE 100Khz为单位, TDS 200Khz为单位 */
    VOS_UINT16 usDlLowChan; /* 本频段下行起始频点 */
    VOS_UINT16 usDlHigChan; /* 本频段下行结束频点 */
    VOS_UINT16 usUlLowFreq; /* 本频段上行起始频率, LTE 100Khz为单位, TDS 200Khz为单位 */
    VOS_UINT16 usUlLowChan; /* 本频段上行起始频点 */
    VOS_UINT16 usUlHigChan; /* 本频段上行结束频点 */
    VOS_UINT8  ucBandMode;  /* 本频段模式 */
    VOS_UINT8  ucBandSWID;  /* 本频段BandSwitch ID */
}FTM_BAND_INFO_STRU;

extern FTM_MAIN_INFO_STRU * ftm_GetMainInfo(VOS_VOID);

/* 获取非信令打开模式 */
extern VOS_UINT8 ftm_GetNoneSig(VOS_VOID);
extern VOS_VOID ftm_SetNoneSig(VOS_UINT8 ucNoneSigNal);

/* 快速校准命令处理函数声明 */
extern FTM_SYN_INFO_STRU *ftm_GetSynMainInfo(VOS_VOID);

extern FTM_CT_F_MANAGE_INFO_STRU* ftm_GetFastCTMainInfo(VOS_VOID);
extern VOS_VOID ftm_SetDefault(VOS_VOID);


/**********************************************************************************/

extern VOS_VOID ftm_MainInfoInit(VOS_VOID);
extern VOS_VOID ftm_MainFunTableInit(VOS_VOID);

#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
#if 0
#endif
extern VOS_VOID hl101_29writeReqtoDhiBuffer(VOS_VOID *pReq);
#endif

/******************************************************************************/
/* A核装备消息处理函数原型 */
typedef VOS_UINT32 (*PFN_AT_FTM_EQUIP_MSG_PROC)(VOS_VOID*);

/* DSP原语消息处理函数原型 */
typedef VOS_UINT32 (*PFN_AT_FTM_DSP_MSP_PROC)(VOS_VOID*);

/* A核装备消息超时处理函数原型 */
typedef VOS_UINT32 (*PFN_AT_FTM_TIMEOUT_PROC)(VOS_VOID);

/* MSP 消息处理函数原型*/
typedef VOS_UINT32 (*PFN_AT_FTM_PS_MSP_PROC)(VOS_VOID*);

/* PS 返回MSP 消息处理表项 */
typedef struct
{
    VOS_UINT32 ulMsgId;
    PFN_AT_FTM_PS_MSP_PROC pfnPsMsgProc;
}FTM_PS_MSG_FUNTBL_STRU;
/* A核装备消息处理表项 */
typedef struct
{
    VOS_UINT32 ulMsgId;
    PFN_AT_FTM_EQUIP_MSG_PROC pfnEquipMsgProc;
    PFN_AT_FTM_TIMEOUT_PROC   pfnTimeoutProc;
}FTM_EQUIP_MSG_FUNTBL_STRU;

/* DSP原语消息处理表项 */
typedef struct
{
    VOS_UINT32 ulMsgId;
    PFN_AT_FTM_DSP_MSP_PROC pfnDspMsgProc;
}FTM_DSP_MSG_FUNTBL_STRU;

extern FTM_CTCMD_CTRL_STRU g_ct_cmd_ctrl;

extern VOS_VOID MMA_PhModeSet(VOS_UINT16 ClientId, VOS_UINT8 OpId, TAF_PH_OP_MODE_STRU *pstPhMode);

/*FTM模块通用函数 */
extern VOS_UINT32 ftm_comm_starttimer(VOS_UINT32* pulTimer, VOS_UINT32 reqId);
extern VOS_UINT32 ftm_comm_stoptimer(VOS_UINT32* pulTimer);
extern VOS_UINT32 ftm_comm_send(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

/* FTM模块邮箱适配  */
extern VOS_UINT32 ftm_mailbox_init(VOS_VOID);
extern VOS_VOID ftm_mailbox_taskproc(VOS_UINT32 ulPara0,
                              VOS_UINT32 ulPara1,
                              VOS_UINT32 ulPara2,
                              VOS_UINT32 ulPara3);
extern VOS_UINT32 ftm_mailbox_ltect_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_ltebt_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_tdsct_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_tdsbt_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_ct_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_bt_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen);

/* LTE协议处理函数 */
extern VOS_UINT32 at_ftm_getBandID(FCHAN_MODE_ENUM emMode, VOS_UINT8 ucBandSwitchID, VOS_UINT8 * pucBandID);
extern VOS_UINT16 at_ftm_get_dlchan(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan);
extern VOS_UINT16 at_ftm_get_ulchan(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan);
extern VOS_UINT16 at_ftm_get_freq(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan);

/* AT^TMODE */
extern VOS_UINT32 at_ftm_tmode_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_tmode_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_tmode_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_tmode_dspcnf(VOS_VOID * pParam);

/* AT^TSELRF */
extern VOS_UINT32 at_ftm_tselrf_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_tselrf_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_tselrf_dspcnf(VOS_VOID * pParam);

/* AT^FCHAN */
extern VOS_UINT32 at_ftm_fchan_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fchan_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fchan_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fchan_dspcnf(VOS_VOID * pParam);

/* AT^FLNA */
extern VOS_UINT32 at_ftm_flna_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_flna_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_flna_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_flna_dspcnf(VOS_VOID * pParam);

/* AT^FWAVE */
extern VOS_UINT32 at_ftm_fwave_set(VOS_VOID * pParamq);
extern VOS_UINT32 at_ftm_fwave_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fwave_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fwave_dspcnf(VOS_VOID * pParam);

/* AT^FTXON */
extern VOS_UINT32 at_ftm_ftxon_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ftxon_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ftxon_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ftxon_dspcnf(VOS_VOID * pParam);

/* AT^FRXON */
extern VOS_UINT32 at_ftm_frxon_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frxon_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_frxon_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frxon_dspcnf(VOS_VOID * pParam);

/* AT^FRSSI */
extern VOS_UINT32 at_ftm_frssi_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frssi_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_frssi_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frssi_dspind(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frssi_readcnf(VOS_UINT32 ulErrCode);

extern SYM_TMODE_ENUM* ftm_GetTmodeMainInfo(VOS_VOID);


extern VOS_UINT32 atFTMSendVosMsg(VOS_UINT32 TaskId, IN VOS_VOID* pData, VOS_UINT32 uLen);


extern VOS_UINT32 at_ftm_ltcommcmd_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ltcommcmd_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ltcommcmd_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ltcommcmd_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ltcommcmd_dspind(VOS_VOID * pParam);

extern VOS_UINT32 at_ftm_fpllstatus_read(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_fpllstatus_readcnf(VOS_UINT16 txStatus, VOS_UINT16 rxStatus,VOS_UINT32 ulErrCode);
extern VOS_UINT32 at_ftm_fpllstatus_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpllstatus_timeout(VOS_VOID);

extern VOS_UINT32 at_ftm_ftxon_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_tmode_store(VOS_UINT8 ucStoreType, SYM_SET_TMODE_REQ_STRU* pstReq);
extern VOS_VOID at_ftm_frxon_store(VOS_UINT8 ucStoreType, FTM_SET_RXON_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_frxon_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_frssi_store(VOS_INT16 sRssiVal);
extern VOS_VOID at_ftm_fwave_store(VOS_UINT8 ucStoreType, FTM_SET_FWAVE_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_fwave_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_flna_store(VOS_UINT8 ucStoreType, FTM_SET_AAGC_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_flna_setcnf(VOS_UINT32 ulErrCode);
extern VOS_UINT32 at_ftm_fchan_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_ftxon_store(VOS_UINT8 ucStoreType, FTM_SET_TXON_REQ_STRU* pstReq);


extern VOS_UINT32 ftm_MsgProcInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID ftm_MsgProc(MsgBlock *pMsgBlock);
extern VOS_UINT32 ftm_RttMsgProc(OS_MSG_STRU* pMsg);
extern VOS_UINT32 ftm_TimeoutMsgProc(OS_MSG_STRU* pMsg);
extern VOS_UINT32 ftm_CmdMsgProc(OS_MSG_STRU* pMsg);
extern VOS_UINT32 at_ftm_fipstart_timeout(VOS_VOID);
extern VOS_VOID ftm_mailbox_ltect_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_VOID ftm_mailbox_ltebt_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_VOID ftm_mailbox_tdsct_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_VOID ftm_mailbox_tdsbt_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_UINT32 ftm_mailbox_msgproc(MAILBOX_SERVICE_TYPE_E enMbxType);


#ifdef __cplusplus
}
#endif

#endif /* __FTM_CT_H__ */


