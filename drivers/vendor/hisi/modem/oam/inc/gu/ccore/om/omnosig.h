/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : omnosig.h
  版 本 号   : 初稿
  作    者   : 甘兰47350
  生成日期   : 2011年9月27日

  最近修改   :
  功能描述   : omnosig.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年9月27日
    作    者   : 甘兰47350
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OM_NOSIG_H__
#define __OM_NOSIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "vos.h"
#include "omprivate.h"
#include "cbtrl.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define SHL1(x)                         (x | (1<<16))
#define SHL2(x)                         (x | (2<<16))
#define CBT_INDEXNOEXIT                 (0xFFFF)
#define CBT_CHAN_MAX_SEGMENT_COUNT      (10)
#define CBT_GE_MAX_BAND_SUPPORT         (4)


#define OM_FRAME_NUM_REG_MASKBIT                      (0x7FF)

/* 读取寄存器的延时长度 */
#define OM_EDGE_BLER_TASK_DELAY         (2000)

/* 等待DSP回复的超时长度 */
#define OM_NOSIG_WAIT_TIME_LEN          (5000)

/* 最大帧数*/
#define OM_FRAME_MAX_NUM                (2715648)

/*寄存器高位对应帧数*/
#define OM_HIHG_ADDR_FRAME_NUM                        (1326)

/*下发消息对应所需时间*/
#define OM_DL_MSG_FRAME_NUM                           (50)

/*译码邮箱最大数据长度，数据用32位数表示 */
#define OM_R99_MAILBOX_MAX_PHY_DATA_IND_LEN           ((328)*4)

/*上行传输信道个数*/
#define OM_UL_TRANS_CHANNEL_NUM                       (2)

/*R99 译码邮箱索引*/
#define OM_R99_DECODE_BUF_INDEX_INIT                  (0x0)
#define OM_R99_DECODE_BUF_INDEX_FIRST                 (0x1)
#define OM_R99_DECODE_BUF_INDEX_SECOND                (0x2)

#define OM_OFFSET_OF(s, m) ((VOS_SIZE_T)&(((s *)0)->m))


typedef VOS_UINT32 (* CBT_PFNTRANSMSG)(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum OM_GE_DL_MODE
{
    OM_GE_DL_MODE_GSM,
    OM_GE_DL_MODE_EDGE,
    OM_GE_DL_MODE_BUTT
};

typedef VOS_UINT32 OM_GE_DL_MODE_ENUM_UINT32;

enum OM_R99_MAILBOX_MUTEX_ENUM
{
    OM_R99_MAILBOX_MUTEX_DATA_NOT_EXIST             = 0,        /* 共享变量中无数据，  可写，不可读;*/
    OM_R99_MAILBOX_MUTEX_DATA_EXIST                 = 1,        /* 共享变量中有数据，不可写，  可读;*/
    OM_R99_MAILBOX_MUTEX_BUTT
};

typedef VOS_UINT16 OM_R99_MAILBOX_MUTEX_ENUM_UINT16;


typedef enum
{
    CBT_STATE_INIT     = 0,
    CBT_STATE_LOOPBACK,
    CBT_STATE_TEST,
    CBT_STATE_HANDOVER
}CBT_LIST_MODE_STATE_ENUM;

typedef enum
{
    CBT_ACTION_CALL     = 0,
    CBT_ACTION_HANDOVER,
    CBT_ACTION_PCLHANDOVER,
    CBT_ACTION_RELEASE,
    CBT_ACTION_BUTT
} CBT_ACTION_ENUM;

typedef enum
{
    CBT_TO_DSP = 0,
    DSP_TO_CBT,
    DIRECTION_BUTT
} CBT_DIRECTION_ENUM;

typedef VOS_UINT16 CBT_DIRECTION_ENUM_UINT16;

typedef enum
{
    CBT_CALL_ERROR      = 0xFFFF0001,
    CBT_HANDOVER_ERROR,
    CBT_RELEASE_ERROR,

    CBT_WAITTOTALFRAMES_ERROR,
    CBT_WAITTXFRAMES_ERROR,

    CBT_SETPOWER_ERROR,
    CBT_CHANCOUNT_ERROR
} CBT_LM_ERROR_CODE_ENUM;

typedef enum
{
    CBT_DATA_UMTS = 0,
    CBT_DATA_GSM,
    CBT_DATA_EDGE,
    CBT_DATA_BUTT
} CBT_DATA_DOMAIN_MODE_ENUM;


typedef enum
{
    W_TPC_DISENABLE,
    W_TPC_ENABLE
} CBT_W_TPC_CONTROL_ENUM;

typedef VOS_UINT16 CBT_W_TPC_CONTROL_ENUM_UINT16;
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

/*****************************************************************************
结构名    : CBT_LIST_MODE_MSG_STRU
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulMsgId;
    VOS_UINT16                  usDataLen;
    VOS_UINT16                  usPosition;
} CBT_LIST_MODE_MSG_STRU;

/*****************************************************************************
结构名    : CBT_CONVERT_MSG_STRU
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulMsgId;
    CBT_DIRECTION_ENUM_UINT16   enDirection;
    VOS_UINT16                  usRsv;
    CBT_PFNTRANSMSG             pfnCbtTrans;
} CBT_CONVERT_MSG_STRU;

/*****************************************************************************
结构名    : CBT_GETMSG_CNF_STRU
结构说明  : list mode需要的msgid回复消息格式
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulResult;
    VOS_UINT32  ulCount;
    VOS_UINT8   aucData[4];
} CBT_GETMSG_CNF_STRU;
/*****************************************************************************
结构名    : CBT_GETMSG_CNF_STRU
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulMsgId;        /*消息类型和消息ID*/
    VOS_UINT32      ulMsgLen;       /* 消息的长度 */
    VOS_MSG_HEADER
} CBT_TRANS_MSG_HEAD_STRU;

/*****************************************************************************
结构名    : CBT_POWER_CTRL_UNION
结构说明  :
*****************************************************************************/
typedef union
{
    VOS_UINT16      usGsmPcl;       /*Gsm配置的PCL等级*/
    VOS_INT16       sWPower10th;    /*Wcdma配置的期望power*/
} CBT_POWER_CTRL_UNION;
/*****************************************************************************
结构名    : CBT_LIST_MODE_SEGMENT_STRU
结构说明  : listmode 一个segment的数据结构
*****************************************************************************/
typedef struct
{
    CBT_W_TPC_CONTROL_ENUM_UINT16   usEnableTpc;    /*W mode enable tpc control  1: enable, 0 disable*/
    VOS_UINT16                      usRsv;
    CBT_POWER_CTRL_UNION            unWgPowerCtrl;
    VOS_UINT16                      usTxFramCnt;

} CBT_LIST_MODE_SEGMENT_STRU;

/*****************************************************************************
结构名    : CBT_LIST_MODE_CHAN_STRU
结构说明  : listmode 一个信道的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulBand;
    VOS_UINT16                  usTxChan;
    VOS_UINT16                  usRxChan;

    VOS_UINT16                  usDurationFrameCnt;
    VOS_UINT16                  usReportFrameCnt;

    VOS_UINT32                  ulSegmentCount;
    CBT_LIST_MODE_SEGMENT_STRU  stSegment[CBT_CHAN_MAX_SEGMENT_COUNT];
} CBT_LIST_MODE_CHAN_STRU;

typedef struct
{
    VOS_UINT16              usEnableReport;  /* 是否使能消息上报,0不上报，1上报 */
    VOS_UINT16              usRcvMsgPrimId;  /* 等待消息ID */
    VOS_UINT16              usSyncStatus;    /* 保存W同步状态 */
    CBT_MODEM_SSID_STRU     stModemSsid;       /* Modem */
    VOS_UINT8               ucReserve;       /* 保留字 */
    CBT_COMPONENT_MODE_STRU stCompMode;        /* 组件ID */
    VOS_UINT16              usRsv2;
    VOS_SEM                 ulNoSigSyncSem;  /* 串行等待消息同步信号量 */
    VOS_UINT32              ulTotalFrameNum; /* 上报的BER总帧数 */
    VOS_UINT32              ulCurFrameNum;   /* 上报的BER当前帧数 */
}OM_NOSIG_CTRL_STRU;

/*****************************************************************************
结构名    : CBT_LISTMODE_MSG_CONTEXT_REQ_STRU
结构说明  : listmode配置消息内容消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usMode;
    VOS_UINT16                  usRsv;
    VOS_UINT32                  ulMsgCount;
    VOS_UINT8                   aucData[4];
} CBT_LISTMODE_MSG_CONTEXT_REQ_STRU;

/*****************************************************************************
结构名    : CBT_LISTMODE_BEGIN_PROC_STRU
结构说明  : listmode开始测试req消息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usEnableReport;
    VOS_UINT16                  usMode;
    VOS_UINT32                  ulChanCount;
    VOS_UINT8                   aucData[4];
} CBT_LISTMODE_TEST_PROC_STRU;


typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHeader;
    VOS_UINT16                  usPrimId;   /*Indicates current msg type.*/
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;
    VOS_UINT32                  ulFirstErrNum;
    VOS_UINT32                  ulFirstTotalNum;
    VOS_UINT32                  ulSecondErrNum;
    VOS_UINT32                  ulSecondTotalNum;
}CBT_EDGE_BLER_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHeader;
    VOS_UINT16                  usPrimId;    /*Indicates current msg type.*/
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;
    VOS_UINT16                  usModeType;  /*1:GSM 2: EDGE*/
    VOS_UINT16                  usReverse2;  /*Not used now.*/
}CBT_GE_DL_STATUS_REQ_STRU;

typedef struct
{
    VOS_UINT16  usNsMsgType;    /* VOS_FALSE:下发消息, VOS_TRUE:等待CNF或者IND消息 */
    VOS_UINT16  usNsMsgLen;     /* 消息的长度 */
    VOS_UINT16  usRcvMsgPrimId; /* 返回消息的ID值 */
    VOS_UINT16  usReserve;      /* 保留 */
}OM_NOSIG_MSG_HEAD_STRU;


typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHeader;
    VOS_UINT16                  usPrimId;   /*Indicates current msg type.*/
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;
    VOS_UINT16                  usFrameNum;
    VOS_UINT16                  usReserve;
}CBT_WC_BER_DATA_REQ_STRU;

typedef struct
{
    UINT16                      usEnableTpc;
    INT16                       sDedicatePower; /* 单位 0.125 dBm*/
}CBT_C_SET_POWER_STRU;


typedef struct
{
    CBT_MSG_HEAD_STRU       stHeader;
    VOS_UINT16              usPrimId;            /*Indicates current msg type.*/
    VOS_UINT16              usToolId;            /*Not used now.*/
    VOS_UINT32              ulMsgLength;
    VOS_UINT16              usTotalFrameNum;
    VOS_UINT16              usCurFrameNum;
    VOS_UINT32              ulDataLen;           /* 数据长度,单位:字节,在数值上是4的整数倍,范围[0..WTTFPHY_MAX_PHY_DATA_REQ_LEN-1] */
    VOS_UINT8               aucData[OM_BER_DATA_MAX_SIZE]; /* 上行数据块 */
}CBT_W_BER_DATA_IND_STRU;

/*先验小区信息结构*/
typedef struct
{
   VOS_UINT16       usPrimaryScramCode;
   VOS_UINT16       usReferenceTime;
}CANDIDATE_CELL_STRU;

/*频段信息结构体*/
typedef struct
{
    VOS_UINT16      usLowFreq;
    VOS_UINT16      usHighFreq;
}FREQ_BAND_STRU;

/*频点信息结构*/
typedef struct
{
    VOS_UINT16      usFreqBandNo;
    VOS_UINT16      usTxRxFreqSepatation;
    VOS_UINT16      usDLFreqInfo;
    VOS_UINT16      usReserve;
}FREQ_INFO_STRU;

/*频点列表结构*/
typedef struct
{
    VOS_UINT16          usFreqCnt;
    VOS_UINT16          usReserve;
    FREQ_INFO_STRU      astFreqList[20];
    VOS_UINT16          usTxRxFreqSeparation;
    VOS_UINT16          usFreqBandNo;
    VOS_UINT16          usReportCellNumInd;  /*上报小区的个数*/
    VOS_UINT16          usReserve1;
}FREQ_LIST_STRU;


typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT16  usMsgId;
    VOS_UINT16  usOpId;
    VOS_UINT16  usCellSearchType;
    VOS_UINT16  usFreqInfo;
    VOS_INT16   sRSCPThreshold;
    VOS_UINT16  usCandidateCellNumm;

    CANDIDATE_CELL_STRU   astCandidateCell[64]; /*先验小区信息*/
    FREQ_BAND_STRU        stFreqBand;
    FREQ_LIST_STRU        stFreqList;
}CELL_SEARCHING_REQ_STRU;

/*DownLink Info*/
typedef struct
{
    VOS_UINT16   usSecScramCode;      /*第2扰码， 0表示没有*/
    VOS_INT16    sOvsfCodeNum;        /*扩频码*/
    VOS_UINT16   usReserve;
    VOS_UINT16   usScrambCodeChange;  /*扰码改变标示，1-nochange*/
}DOWN_LINK_INFO_STRU;

/*Compress MODE TGPS INFO*/
typedef struct
{
   VOS_UINT16   usTgpsi;
   VOS_UINT16   usTgpStausFlag;
   VOS_INT16    sTgcfn;
   VOS_UINT16   usReserve;
   VOS_INT16    sTgrc;
   VOS_INT16    usTgmp;
   VOS_UINT16   usTgsn;
   VOS_UINT16   usTgL1;
   VOS_UINT16   usTgL2;
   VOS_INT16    sTgd;
   VOS_UINT16   usTGPL1;
   VOS_UINT16   usTGPL2;
   VOS_UINT16   usRpp;
   VOS_UINT16   usITP;
   VOS_UINT16   usDLFrameType;
   VOS_UINT16   usDeltaSIR1;
   VOS_UINT16   usDelatSIRafter1;
   VOS_UINT16   usDeltaSIR2;
   VOS_UINT16   usDelatSIRafter2;
   VOS_UINT16   usNIdentifyabort;
   VOS_UINT16   usTReconfirmabort;
   VOS_UINT16   usReserve1;
   VOS_UINT16   usULMethod;
   VOS_UINT16   usReserve2;
}COMPRESS_MODE_TGPS_INFO_STRU;

/*Compress mode*/
typedef struct
{
    VOS_UINT16   usTGPSCnt;
    VOS_UINT16   usReserve;
    COMPRESS_MODE_TGPS_INFO_STRU stCompressModeTgpsInfo[6];

}COMPRESS_MODE_STRU;

/*RL参数结构*/
typedef struct
{
    VOS_UINT16   usPhyType;            /*物理信道类型 2 dldpch*/
    VOS_INT16    sActiveTime;          /*-1立即下发*/
    VOS_UINT16   usFreqInfo;
    VOS_UINT16   usSlotFormat;         /*时隙格式，仪器默认等于11*/
    VOS_UINT16   usDpchFrameOffset;    /*帧偏移，默认是0*/
    VOS_UINT16   usTdIndicator;
    VOS_UINT16   usDpchChanNum;        /*DPCH格式,1个*/
    VOS_UINT16   usDownLinkScramCode;  /*扰码 9*/
    DOWN_LINK_INFO_STRU  stDownLinkInfo;
    VOS_UINT16   usDpcMode;            /*下行功率控制模式  1-singel*/
    VOS_UINT16   usTpcCombIndex;       /*TPC组合的索引，仪器配置[0,5];*/
    VOS_UINT16   usTimingIndication;   /*硬切换定时指示，4-非硬切换*/
    VOS_INT16    sCfnSfnOffset;

    COMPRESS_MODE_STRU stCompressMode;
    VOS_UINT16   usNeedSyncAInd;
    VOS_UINT16   usPcpichTDIndicator;
    VOS_UINT16   usBlindHhoFlag;
    VOS_UINT16   usFreqBandNo;
    VOS_UINT16   usTxRxFreqSeparation;
    VOS_UINT16   usSecndCpichValidInd;

    VOS_UINT16   usSecondDlScramblCode;
    VOS_UINT16   usOvsfCodeNum;
    VOS_UINT16   usPo2;
    VOS_UINT16   usPo3;
}RL_PARA_STRU;

typedef struct
{
    VOS_UINT16   usPhyType;            /*物理信道类型 2 dldpch*/
    VOS_INT16    sActiveTime;
    VOS_UINT16   usFreqInfo;
    VOS_UINT16   usSlotFormat;         /*时隙格式，仪器默认等于11*/
    VOS_UINT16   usDpchFrameOffset;
    VOS_UINT16   usTdIndicator;
    VOS_UINT16   usDpchChanNum;
    VOS_UINT16   usDownLinkScramCode;  /*扰码 9*/
    DOWN_LINK_INFO_STRU  stDownLinkInfo;
    VOS_UINT16   usDpcMode;            /*下行功率控制模式  1-singel*/
    VOS_UINT16   usTpcCombIndex;       /*TPC组合的索引，仪器配置[0,5];*/
    VOS_UINT16   usTimingIndication;   /*硬切换定时指示，4-非硬切换*/
    VOS_INT16    sCfnSfnOffset;

    COMPRESS_MODE_STRU stCompressMode;
    /*V3R2与V3R1不同(usNeedSyncAInd)*/
    VOS_UINT16   usRsv;
    VOS_UINT16   usNeedSync;
    VOS_UINT16   usPostVerification;

    VOS_UINT16   usPcpichTDIndicator;
    VOS_UINT16   usBlindHhoFlag;
    VOS_UINT16   usFreqBandNo;
    VOS_UINT16   usTxRxFreqSeparation;
    VOS_UINT16   usSecndCpichValidInd;

    VOS_UINT16   usSecondDlScramblCode;
    VOS_UINT16   usOvsfCodeNum;
    VOS_UINT16   usPo2;
    VOS_UINT16   usPo3;

    VOS_UINT16   usSuncDetect;
    VOS_UINT16   usT312;
    VOS_UINT16   usN312;
    VOS_UINT16   usT313;
    VOS_UINT16   usN313;
    VOS_UINT16   usN315;
    VOS_UINT16   usDisableUlDcchTimer;
    VOS_UINT16   usResumeUlDcchTimer;
}CBT_V3R2_RL_PARA1_STRU;

typedef struct
{
    VOS_UINT16   usPhyType;            /*物理信道类型 2 dldpch*/

    VOS_INT16    sActivateTime;
    VOS_UINT16   usFreqInfo;
    VOS_UINT16   usScramCodeType;
    VOS_UINT32   ulScramCodeNum;

    VOS_INT16    sDpchInitialTxPower;
    VOS_UINT16   usPcPreamble;
    VOS_UINT16   usPowerControlAlgorithm;
    VOS_UINT16   usTpcStepSize;
    VOS_INT16    sUlDpchPowerOffset;
    VOS_UINT16   usBlindHhoFlag;

    VOS_UINT16   usDpchNum;
    VOS_UINT16   usSlotFormat;
    VOS_UINT16   usFreqBandNo;
    VOS_UINT16   usTxRxFreqSeparation;
}CBT_V3R2_RL_PARA2_STRU;

/*发起建立DL dpch REQ*/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT16              usPrimId;
    VOS_UINT16              usOpId;
    VOS_UINT16              usPhyChannelNum;    /*物理信道个数*/
    VOS_UINT16              usParaSize;         /*消息长度*/
    CBT_V3R2_RL_PARA1_STRU  stRlPara1;
    CBT_V3R2_RL_PARA2_STRU  stRlPara2;
}RL_SETUP_DL_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT16  usPrimId;
    VOS_UINT16  usFreqBand;
    VOS_UINT16  usFreqNum;
    VOS_UINT16  usFreqInfo[67];
}EVT_MPH_RXLEV_REQ_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 CBT_WCellSearchFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_WCampedMainCellFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_WRlSetUpDldpchFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);

VOS_UINT32 CBT_GeRxLevReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeStartBcchReadingFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeStopBcchReadingFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeImmedAssignReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeChannelAssignReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeStopDedicatedReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);

VOS_UINT32 CBT_GeSiUpdateReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeDlSetupReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);
VOS_UINT32 CBT_GeUlSetupReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen);


VOS_UINT32 CBT_GetListModeMsgID(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_ListModeMsgContext(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_ListModeTestProc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_CSyncStatusProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 CBT_CFrameErrorRate(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 CBT_CSetPower(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId);
#endif

VOS_VOID   CBT_FramesStatistics(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID   CBT_CLoopTestProc(VOS_VOID);

#endif

VOS_UINT32 OM_BtTransProc(CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_WSyncStatusProc(CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_EdgeBlerProc (CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_GeDlStatusProc (CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_UINT32 OM_BerConfigProc(CBT_UNIFORM_MSG_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
VOS_VOID   OM_LoopTestProc(VOS_VOID);


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

#endif /* end of omnosig.h */

