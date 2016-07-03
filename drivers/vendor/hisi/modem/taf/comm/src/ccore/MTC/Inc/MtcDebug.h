

#ifndef __MTCDEBUG_H__
#define __MTCDEBUG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "MtcCtx.h"
#include "MtcIntrusion.h"
#include "MtcPsTransfer.h"
#include "MtcRfLcdIntrusion.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 封装可维可测事件消息头 */
#define MTC_DEBUG_CFG_MSG_HDR(pstMsg, SenderPid, ReceiverPid, ulLen)\
                (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                (pstMsg)->ulSenderPid     = SenderPid;\
                (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                (pstMsg)->ulReceiverPid   = ReceiverPid;\
                (pstMsg)->ulLength        = (ulLen);



#define MTC_DEBUG_RF_LCD_ALLOC_MSG_ERR()        g_stMtcDebugInfo.stRfLcdDebugInfo.ulAllocMsgErr++

#define MTC_DEBUG_RF_LCD_SND_MIPICLK_IND_OK()   g_stMtcDebugInfo.stRfLcdDebugInfo.ulSndMipiClkInfoIndOK++

#define MTC_DEBUG_RF_LCD_SND_MIPICLK_IND_ERR()  g_stMtcDebugInfo.stRfLcdDebugInfo.ulSndMipiClkInfoIndErr++

#define MTC_DEBUG_SAVE_AS_RF_USING_INFO_NUM(ASFreq)      g_stRfUsingDebugInfo.ASFreq.ulFreqNum++

#define MTC_DEBUG_SAVE_RF_USING_INFO(ASFreq, info, Value, Num)  g_stRfUsingDebugInfo.ASFreq.astArfcnInfo[Num].info = (Value)

#define MTC_DEBUG_SAVE_RF_USING_CS_PS_INFO(csFlag, psFlag) \
                g_stRfUsingDebugInfo.enCsExistFlag = csFlag;\
                g_stRfUsingDebugInfo.enPsExistFlag = psFlag

#define MTC_DEBUG_COPY_MODEM_MIPICLK(ModemMipiClk)  PS_MEM_CPY(&g_stRfUsingDebugInfo.stModemMipiClk, &(ModemMipiClk), sizeof(MTC_MODEM_MIPI_CLK_PRI_STRU))

#define MTC_DEBUG_MRMA_MAX_MODEM_NUM            (MTC_RCM_MODEM_BUTT)




/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum MTC_DEBUG_BAND_ENUM
{
    MTC_DEBUG_BAND_NONE                   = 0x00,
    MTC_DEBUG_BAND_1,
    MTC_DEBUG_BAND_3,
    MTC_DEBUG_BAND_8,
    MTC_DEBUG_BAND_3_8,
    MTC_DEBUG_BAND_31,
    MTC_DEBUG_BAND_31_8,
    MTC_DEBUG_BAND_32,
    MTC_DEBUG_BAND_32_8,
    MTC_DEBUG_BAND_39,

    MTC_DEBUG_BAND_BUTT
};
typedef VOS_UINT8  MTC_DEBUG_BAND_ENUM_UINT8;


enum MTC_DEBUG_MSG_ID_ENUM
{
    ID_DEBUG_MTC_CTX_INFO                           = 0xF000,                  /* _H2ASN_MsgChoice MTC_CONTEXT_DEBUG_STRU */
    ID_DEBUG_MTC_RF_USING_FREQ_LIST_INFO            = 0xF001,                  /* _H2ASN_MsgChoice MTC_DEBUG_RF_USING_FREQ_LIST_STRU */
    ID_DEBUG_MTC_ALL_MODEM_STATE_INFO               = 0xF002,                  /* _H2ASN_MsgChoice MTC_DEBUG_ALL_MODEM_STATE_INFO */
    ID_DEBUG_MTC_NOTCH_INFO                         = 0xF003,
    ID_DEBUG_MTC_BUTT
};
typedef VOS_UINT32 MTC_DEBUG_MSG_ID_ENUM_UINT32;


enum MTC_DEBUG_CONN_STATE_ENUM
{
    MTC_DEBUG_CONN_NO_EXIST                   = 0x00,                                 /* 不存在连接状态 */
    MTC_DEBUG_CONN_EXIST                      = 0x01,                                 /* 存在连接状态 */

    MTC_DEBUG_CONN_STATE_BUTT
};
typedef VOS_UINT8 MTC_DEBUG_CONN_STATE_ENUM_UINT8;


enum MTC_DEBUG_MODEM_POWER_STATE_ENUM
{
    MTC_DEBUG_MODEM_POWER_OFF                 = 0x00,
    MTC_DEBUG_MODEM_POWER_ON                  = 0x01,

    MTC_DEBUG_MODEM_POWER_STATE_BUTT
};
typedef VOS_UINT8  MTC_DEBUG_MODEM_POWER_STATE_ENUM_UINT8;



enum MTC_DEBUG_USIMM_CARD_SERVIC_ENUM
{
    MTC_DEBUG_USIMM_CARD_SERVIC_ABSENT        =0,                               /* 无卡 */
    MTC_DEBUG_USIMM_CARD_SERVIC_UNAVAILABLE   =1,                               /* 有卡,服务不可用 */
    MTC_DEBUG_USIMM_CARD_SERVIC_SIM_PIN       =2,                               /* SIM卡服务由于PIN码原因不可用 */
    MTC_DEBUG_USIMM_CARD_SERVIC_SIM_PUK       =3,                               /* SIM卡服务由于PUK码原因不可用 */
    MTC_DEBUG_USIMM_CARD_SERVIC_NET_LCOK      =4,                               /* SIM卡服务由于网络锁定原因不可用 */
    MTC_DEBUG_USIMM_CARD_SERVIC_IMSI_LCOK     =5,                               /* SIM卡服务由于IMSI锁定原因不可用 */
    MTC_DEBUG_USIMM_CARD_SERVIC_AVAILABLE     =6,                               /* 服务可用 */

    MTC_DEBUG_USIMM_CARD_SERVIC_BUTT
};
typedef VOS_UINT16      MTC_DEBUG_USIMM_CARD_SERVIC_ENUM_UINT16;





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
    VOS_UINT16                          ausRcvPowerOnNum[MODEM_ID_BUTT];
    VOS_UINT16                          ausRcvPowerOffNum[MODEM_ID_BUTT];
    VOS_UINT16                          ausRcvCsSrvNum[MODEM_ID_BUTT];
    VOS_UINT16                          usSndAction2TDSRrcReqNum;
    VOS_UINT16                          usSndAction2LTERrcReqNum;
    VOS_UINT16                          usSndAction2GASReqNum;
    VOS_UINT16                          usRcvTDSRrcActionCnfNum;
    VOS_UINT16                          usRcvLTERrcActionCnfNum;
    VOS_UINT16                          usRcvGASBandSetCnfNum;
    VOS_UINT16                          usRcvLTEBandSetCnfNum;
    VOS_UINT16                          usRcvTDSBandSetCnfNum;
    VOS_UINT16                          usRcvGASActionCnfNum;
    VOS_UINT16                          usSndGasSetBandReqNum;
    VOS_UINT16                          usSndLteSetBandReqNum;
    VOS_UINT16                          usSndTdsSetBandReqNum;
}MTC_INTRUSION_DEBUG_INFO;


typedef struct
{
    VOS_UINT16                          usRcvTDSAreaLostIndNum;
    VOS_UINT16                          usRcvLTEAreaLostIndNum;
    VOS_UINT16                          usRcvAreaAvaliableIndNum;
    VOS_UINT16                          ausSndPsTransferIndNum[MTC_PS_TRANSFER_CAUSE_BUTT];
    VOS_UINT16                          ausReserved[2];
}MTC_PS_TRANSFER_DEBUG_INFO;


typedef struct
{
    VOS_UINT32                          ulAllocMsgErr;
    VOS_UINT32                          ulSndMipiClkInfoIndOK;
    VOS_UINT32                          ulSndMipiClkInfoIndErr;
}MTC_DEBUG_RF_LCD_INFO_STRU;



typedef struct
{
    MTC_INTRUSION_DEBUG_INFO            stIntrusionDebugInfo;
    MTC_PS_TRANSFER_DEBUG_INFO          stPsTransferDebugInfo;
    MTC_DEBUG_RF_LCD_INFO_STRU          stRfLcdDebugInfo;
}MTC_DEBUG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER
    MTC_DEBUG_MSG_ID_ENUM_UINT32        enMsgType;
    MTC_CONTEXT_STRU                    stMtcCtx;
}MTC_CONTEXT_DEBUG_STRU;


typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usBandId;
    VOS_UINT16                          usFreq;
    VOS_UINT8                           aucRsv[2];
}MTC_DEBUG_ARFCN_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulFreqNum;
    MTC_DEBUG_ARFCN_INFO_STRU           astArfcnInfo[MTC_RF_FREQ_MAX_NUM];
}MTC_DEBUG_RF_FREQ_LIST_STRU;


typedef struct
{
    VOS_UINT32                          ulArfcn;
    VOS_UINT16                          usBandId;
    VOS_UINT16                          usFreq;
}MTC_DEBUG_LTE_ARFCN_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulFreqNum;
    MTC_DEBUG_LTE_ARFCN_INFO_STRU       astArfcnInfo[MTC_RF_FREQ_MAX_NUM];
}MTC_DEBUG_LTE_RF_FREQ_LIST_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enCsExistFlag;                          /* PS_FALSE 表示不存在CS连接 */
    PS_BOOL_ENUM_UINT8                  enPsExistFlag;                          /* PS_FALSE 表示不存在PS连接 */
    VOS_UINT8                           aucRsv[2];
    MTC_DEBUG_RF_FREQ_LIST_STRU         stGsmFreq;
    MTC_DEBUG_RF_FREQ_LIST_STRU         stGsmHoppingFreq;
    MTC_DEBUG_RF_FREQ_LIST_STRU         stWcdmaFreq;
    MTC_DEBUG_LTE_RF_FREQ_LIST_STRU     stLteFreq;
    MTC_DEBUG_RF_FREQ_LIST_STRU         stTdsFreq;
    MTC_MODEM_MIPI_CLK_PRI_STRU         stModemMipiClk;
}MTC_DEBUG_RF_USING_FREQ_LIST_STRU;


typedef struct
{
    MTC_DEBUG_CONN_STATE_ENUM_UINT8         enIsCsSrvConnExist;
    MTC_DEBUG_CONN_STATE_ENUM_UINT8         enIsPsSrvConnExist;
    MTC_DEBUG_MODEM_POWER_STATE_ENUM_UINT8  enPowerState;
    VOS_UINT8                               aucReserved1[1];
    MTC_DEBUG_USIMM_CARD_SERVIC_ENUM_UINT16 enUsimmState;
    VOS_UINT8                               ucCsConnInfo;
    VOS_UINT8                               ucPsConnInfo;
    MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16       enModemRatCfg;                      /* Modem配置的接入能力 */
    VOS_UINT8                               aucRsv[2];
    VOS_UINT32                              ulCsSessionValue;
    VOS_UINT32                              ulPsSessionValue;
}MTC_DEBUG_MODEM_STATE_INFO_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_DEBUG_MODEM_STATE_INFO_STRU     stModemStateInfo[MTC_DEBUG_MRMA_MAX_MODEM_NUM];
}MTC_DEBUG_ALL_MODEM_STATE_INFO;


typedef struct
{
    VOS_UINT8                           ucBufBandInfoFlag;
    VOS_UINT8                           aucRcv[3];
    VOS_UINT32                          ulSndPid;
    RRC_MTC_MS_BAND_INFO_STRU           stModemBandInfo;
}MTC_DEBUG_MODEM_BUF_BAND_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucBufNcellBandFlag;
    VOS_UINT8                           aucRcv[3];
    VOS_UINT32                          ulSndPid;
    RRC_MTC_TDS_NCELL_INFO_STRU         stTdsNcellFreqInfo;                     /* TDS频点列表信息 */
    RRC_MTC_LTE_NCELL_INFO_STRU         stLteNcellFreqInfo;                     /* LTE频点列表信息 */
}MTC_DEBUG_MODEM_BUF_NCELL_BAND_INFO_STRU;


typedef struct
{
    MTC_DEBUG_MODEM_BUF_BAND_INFO_STRU          stBufBandInfo;
    MTC_DEBUG_MODEM_BUF_NCELL_BAND_INFO_STRU    stBufNCellFreqInfo;
}MTC_DEBUG_MODEM_BUF_INFO_STRU;


typedef struct
{
    RRC_MTC_MS_BAND_INFO_STRU           stModemBandInfo;
    RRC_MTC_MS_BAND_INFO_STRU           stModemNcellBandInfo;
    MTC_DEBUG_MODEM_BUF_INFO_STRU       stModemBufInfo;
}MTC_DEBUG_MODEM_NOTCH_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_DEBUG_MODEM_NOTCH_INFO_STRU     stModemNotchInfo[MODEM_ID_BUTT];                    /* 默认三个modem */
}MTC_DEBUG_ALL_MODEM_NOTCH_INFO_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    MTC_DEBUG_MSG_ID_ENUM_UINT32        enMsgId;                                /*_H2ASN_MsgChoice_Export MTC_DEBUG_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MTC_DEBUG_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MTC_DEBUG_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MTC_DEBUG_MSG_DATA                  stMsgData;
}MtcDebug_MSG;

/*****************************************************************************
  9 全局变量声明
*****************************************************************************/
extern MTC_DEBUG_INFO_STRU                     g_stMtcDebugInfo;
extern MTC_DEBUG_RF_USING_FREQ_LIST_STRU       g_stRfUsingDebugInfo;
/*****************************************************************************
  10 UNION定义
*****************************************************************************/

/*****************************************************************************
  11 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  12 函数声明
*****************************************************************************/
VOS_VOID MTC_InitDebugCtx(VOS_VOID);

MTC_INTRUSION_DEBUG_INFO* MTC_GetIntrusionDebugCtxAddr(VOS_VOID);

MTC_PS_TRANSFER_DEBUG_INFO* MTC_GetPsTransferDebugCtxAddr(VOS_VOID);

VOS_VOID MTC_DEBUG_IntrusionRcvSetBandCnf(VOS_UINT32 ulPid);

VOS_VOID MTC_DEBUG_IntrusionSendActionReq(VOS_UINT32 ulPid);

VOS_VOID MTC_DEBUG_IntrusionRcvActionCnf(VOS_UINT32 ulPid);

VOS_VOID MTC_DEBUG_RcvPowerStateInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState
);

VOS_VOID MTC_DEBUG_IntrusionSendSetBandReq(VOS_UINT32 ulPid);

VOS_VOID MTC_DEBUG_RcvCsSrvInfoInd(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_DEBUG_RcvRrcAreaLostInd(
    VOS_UINT32                          ulSenderPid
);

VOS_VOID MTC_DEBUG_SndPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
);

VOS_VOID MTC_DEBUG_RcvRrcAreaAvaliableInd(VOS_VOID);

MTC_DEBUG_RF_LCD_INFO_STRU* MTC_DEBUG_GetRfLcdDebugAddr(VOS_VOID);

VOS_VOID MTC_DEBUG_TraceCtxInfo(VOS_VOID);
VOS_VOID MTC_DEBUG_InitRfUsingFreqListInfo(VOS_VOID);
VOS_VOID MTC_DEBUG_TraceRfUsingFreqListInfo(VOS_VOID);

VOS_VOID MTC_DEBUG_TraceAllModemConnStateInfo(VOS_VOID);

VOS_VOID MTC_DEBUG_TraceNotchInfo(VOS_VOID);


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

#endif /* end of MtcDebug.h */


