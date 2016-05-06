/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMOm.h
    Description :
    History     :
      1.  qilili00145085  2008-10-30  Draft Enact
      2.  hanlufeng 41410  2009-03-11  BA8D01164 NAS_LMM_LOG 视为对PRINTF的
          适配，放在OSA文件中定义；
      3.  hanlufeng 41410  2009-05-07  BA8D00629 以APP的接口代替OM的接口
      4.  zhengjunyan 00148421  2011-05-28 文件名由 NasMmPubMOm.h修改为
                                        NasLmmPubMOm.h
******************************************************************************/

#ifndef _NASLMMPUBMOM_H
#define _NASLMMPUBMOM_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "OmCommon.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmPubUMain.h"

#include    "NasEmmTauInterface.h"
#include    "NasEmmSerInterface.h"
#include    "LnasFtmInterface.h"
#include    "LnasErrlogInterface.h"

/*#include  "IpDhcpv4Server.h"*/
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define NAS_EMM_AIR_DATA_ARRAY_LEN      4

#define NAS_EMM_TP_CMD_HEADER           0x00000000

#define NAS_EMM_EVEN_IMSI               0x01
#define NAS_EMM_ODD_IMSI                0x09
#define MAS_EMM_IMSI_PAD_LEN            0x02

#define NAS_EMM_LOW_4_BIT               0x0F
#define NAS_EMM_HIGH_4_BIT              0xF0

#define NAS_EMM_MNC_LEN2                2
#define NAS_EMM_MNC_LEN3                3
#define NAS_EMM_NV_READ_FAIL            0

#define NAS_EMM_DHCP_SERVER_BUFFER_LEN  400

/* niuxiufan DT begin */
#define NAS_DT_RPT_CTRL_MAX_ITEM_NUM         10
/* niuxiufan DT end */

#define NAS_SAVE_RECEIVE_MSG_INFO_NUM       16

/*LTE CS*/
#define NAS_LMM_LTE_CS_SERVICE_NOT_SUPPORT    0
#define NAS_LMM_LTE_CS_SERVICE_SUPPORT        1

/* niuxiufan DT begin */
#define NAS_EMM_GetNasDtRptCtrlItem(ulIndex)   (&(gastNasDtRptCtrlTbl[ulIndex]))

/* niuxiufan DT end */
#define LNAS_RING_BUFFER_SIZE        (1024)
/*  大数据:UINT32最大数,计算DELAY的时候可能用到 */
#define NAS_EMM_UINT32_MAX  0xFFFFFFFF

#define MAX_PRINT_CHAR_NUM            (500)

extern VOS_UINT32                  g_NasEmmOmInfoIndFlag;


#define NAS_EMM_GetDrxCycleLenChangeFlag()   (g_ulDrxCycleLenChange)
#define NAS_EMM_SetDrxCycleLenChangeFlag(DrxCycleLenChangeFlag)\
                             ((g_ulDrxCycleLenChange) = (DrxCycleLenChangeFlag))


#define EMM_COMP_OMT_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_OM;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

#define EMM_COMP_APP_MSG_VOS_HEADER(pDestMsg,MsgLenthNoHeader,pSourMsg)\
        {\
            (pDestMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            (pDestMsg)->ulSenderPid     = PS_PID_MM;\
            (pDestMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            (pDestMsg)->ulReceiverPid   = PS_PID_APP;\
            (pDestMsg)->ulLength        = (MsgLenthNoHeader);\
            (pDestMsg)->usOriginalId    = (pSourMsg)->usTerminalId;\
            (pDestMsg)->usTerminalId    = (pSourMsg)->usOriginalId;\
            (pDestMsg)->ulTimeStamp     = (pSourMsg)->ulTimeStamp;\
            (pDestMsg)->ulSN            = (pSourMsg)->ulSN;\
        }

#define EMM_COMP_APP_DT_IND_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = L3_MSP_PID_DT_IND;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }
/* OM融合，所有透传消息CNF和REQ中的usOriginalId和usTerminalId必须对应，不能颠倒 */
#define EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pDestMsg,MsgLenthNoHeader,pSourMsg)\
        {\
            (pDestMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            (pDestMsg)->ulSenderPid     = PS_PID_MM;\
            (pDestMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            (pDestMsg)->ulReceiverPid   = L3_MSP_PID_DT;\
            (pDestMsg)->ulLength        = (MsgLenthNoHeader);\
            (pDestMsg)->usOriginalId    = (pSourMsg)->usOriginalId;\
            (pDestMsg)->usTerminalId    = (pSourMsg)->usTerminalId;\
            (pDestMsg)->ulTimeStamp     = (pSourMsg)->ulTimeStamp;\
            (pDestMsg)->ulSN            = (pSourMsg)->ulSN;\
        }

/*空口消息和关键事件填充APP消息头*/
#define EMM_COMP_OMT_APP_MSG_HEADER(pMsg)\
        {\
            (pMsg)->usOriginalId  = (UE_MODULE_MM_ID);\
            (pMsg)->usTerminalId  = (UE_APP_SUBSYS_ID);\
        }

#define EMM_COMP_MM_APP_KEY_AIR_MSG_HEADER(pMsg)\
        {\
            (pMsg)->usOriginalId        = (UE_MODULE_MM_ID);\
            (pMsg)->usTerminalId        = (UE_APP_SUBSYS_ID);\
        }


#define NAS_EMM_COMP_MM_2_APP_MSGID(pstEmmAppMsg, ID_EMM_APP_MSGID) \
            (pstEmmAppMsg->ulMsgId      = (ID_EMM_APP_MSGID))

#define EMM_TP_CMD_TYPE(enTpMsgType)    (enTpMsgType)


#define EMM_MSG_LENTH_NO_HEADER(EMM_XX_MSG_STRU)\
            (sizeof(EMM_XX_MSG_STRU)    - NAS_EMM_LEN_VOS_MSG_HEADER)


#define NAS_LMM_MEM_CMP(dest, src, count) PS_MEM_CMP((dest), (src), (count))


/*OMA头*/
#define OMA_HEADER        VOS_UINT16    usHeader;\
                          VOS_UINT16    usMsgLen;

#ifndef APP_MSG_HEADER

#define APP_MSG_HEADER    VOS_UINT16    usOriginalId;\
                          VOS_UINT16    usTerminalId;\
                          VOS_UINT32    ulTimeStamp; \
                          VOS_UINT32    ulSN;


#endif

/* 计算TP_GINFO_CNF_MSG的DOPRA申请的消息的部分长度，
该长度不包括u 中具体的全局变量的长度 */
#define NAS_EMM_TP_GINFO_MSG_LENGTH_EXCEPT_IE(pstTpGInfoCnfMsg) \
                ((sizeof(APP_MM_TP_G_INFO_CNF_STRU)\
                 - NAS_EMM_LEN_VOS_MSG_HEADER)\
                 - (sizeof(pstTpGInfoCnfMsg->u)))



#define NAS_EMM_GetFtmInfoManageAddr()      (&(g_astEmmFtmInfoManage))
#define NAS_EMM_GetEmmInfoAddr()            (&(g_astEmmInfo))
#define NAS_EMM_GetFtmInfoActionFlag()      (NAS_EMM_GetFtmInfoManageAddr()->ulFtmActionFlag)
#define NAS_EMM_GetFtmInfoMsgSN()           (NAS_EMM_GetFtmInfoManageAddr()->ulMsgSN)
#define NAS_EMM_GetFtmInfoCnRej()           (NAS_EMM_GetFtmInfoManageAddr()->enEmmCnRejCause)
#define NAS_EMM_SetFtmOmManageFtmActionFlag(Flag)  (NAS_EMM_GetFtmInfoActionFlag() = Flag)

#define NAS_EMM_GetErrlogGloInfoAddr()                  (&stErrlogGloInfo)
#define NAS_EMM_GetErrlogCtrlInfo()                     (&(NAS_EMM_GetErrlogGloInfoAddr()->stCtrlInfo))
#define NAS_EMM_GetErrlogBufferInfo()                   (&(NAS_EMM_GetErrlogGloInfoAddr()->stBuffInfo))
#define NAS_EMM_GetErrlogCtrlInfoCtrlFlag()             (NAS_EMM_GetErrlogCtrlInfo()->ucErrLogCtrlFlag)
#define NAS_EMM_SetErrlogCtrlInfoCtrlFlag(ucFlag)       (NAS_EMM_GetErrlogCtrlInfoCtrlFlag() = ucFlag)
#define NAS_EMM_GetErrlogCtrlInfoALMLevel()             (NAS_EMM_GetErrlogCtrlInfo()->usAlmLevel)
#define NAS_EMM_SetErrlogCtrlInfoALMLevel(usLevel)      (NAS_EMM_GetErrlogCtrlInfoALMLevel() = usLevel)
#define NAS_EMM_GetErrlogBufferInfoRingBuffer()         (NAS_EMM_GetErrlogBufferInfo()->pstRingBuffer)
#define NAS_EMM_GetErrlogBufferInfoOverflowCnt()        (NAS_EMM_GetErrlogBufferInfo()->ulOverflowCnt)
#define NAS_EMM_SetErrlogBufferInfoOverflowCnt(ulCnt)   (NAS_EMM_GetErrlogBufferInfoOverflowCnt() = ulCnt)

#define NAS_EMM_ERRLOG_MAX_NUM              (4)

#define NAS_LMM_COMP_OM_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = MSP_PID_DIAG_APP_AGENT;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }



#define NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(pstHeader, ModemId, AlmId, AlmLevel, ulSlice, ulLength) \
{ \
    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_LMM; \
    (pstHeader)->usModemId         = ModemId; \
    (pstHeader)->usAlmId           = AlmId; \
    (pstHeader)->usAlmLevel        = AlmLevel; \
    (pstHeader)->usAlmType         = EMM_OM_ERRLOG_ALM_TYPE_COMMUNICATION; \
    (pstHeader)->ulAlmLowSlice     = ulSlice; \
    (pstHeader)->ulAlmHighSlice    = 0; \
    (pstHeader)->ulAlmLength       = ulLength; \
}
#define NAS_EMM_GetEmmOmEntityAddr()                (&g_stEmmOmEntity)
#define NAS_EMM_GetOmInterTauFlag()                 (NAS_EMM_GetEmmOmEntityAddr()->ucIsInterTauFlag)
#define NAS_EMM_SetOmInterTauFlag(ucFlag)           {NAS_EMM_GetOmInterTauFlag()=(ucFlag);\
                                                     NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_SetOmInterTauFlag",ucFlag);}

#define NAS_EMM_GetOmMtSerFlag()                    (NAS_EMM_GetEmmOmEntityAddr()->ucIsMtServiceFlag)
#define NAS_EMM_SetOmMtSerFlag(ucFlag)              (NAS_EMM_GetOmMtSerFlag()=(ucFlag))


#define NAS_EMM_GetOmSuccRationTauInfoAddr()        (&NAS_EMM_GetEmmOmEntityAddr()->stTauSuccRatio)
#define NAS_EMM_GetIntraTauSuccRatioInfoAddr()      (&(NAS_EMM_GetOmSuccRationTauInfoAddr()->stIntraTauSuccRatio))
#define NAS_EMM_GetIntraTauTolalTimes()             (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usTolalTimes)
#define NAS_EMM_GetIntraTauSuccTimes()              (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usSuccTimes)
#define NAS_EMM_GetIntraTauBarFailTimes()           (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usBarFailTimes)
#define NAS_EMM_GetIntraTauNoRfFailTimes()          (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usNoRfFailTimes)
#define NAS_EMM_GetIntraTauEstFailTimes()           (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usEstFailTimes)
#define NAS_EMM_GetIntraTauExpFailTimes()           (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usExpFailTimes)
#define NAS_EMM_GetIntraTauRejFailTimes()           (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usRejFailTimes)
#define NAS_EMM_GetIntraTauRelFailTimes()           (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usRelFailTimes)
#define NAS_EMM_GetIntraTauDatReqFailTimes()        (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usDataReqFailTimes)
#define NAS_EMM_GetIntraTauOtherFailTimes()         (NAS_EMM_GetIntraTauSuccRatioInfoAddr()->usOtherFailTimes)

#define NAS_EMM_GetInterTauSuccRatioInfoAddr()      (&(NAS_EMM_GetOmSuccRationTauInfoAddr()->stInterTauSuccRatio))
#define NAS_EMM_GetInterTauTolalTimes()             (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usTolalTimes)
#define NAS_EMM_GetInterTauSuccTimes()              (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usSuccTimes)
#define NAS_EMM_GetInterTauBarFailTimes()           (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usBarFailTimes)
#define NAS_EMM_GetInterTauNoRfFailTimes()          (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usNoRfFailTimes)
#define NAS_EMM_GetInterTauEstFailTimes()           (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usEstFailTimes)
#define NAS_EMM_GetInterTauExpFailTimes()           (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usExpFailTimes)
#define NAS_EMM_GetInterTauRejFailTimes()           (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usRejFailTimes)
#define NAS_EMM_GetInterTauRelFailTimes()           (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usRelFailTimes)
#define NAS_EMM_GetInterTauDatReqFailTimes()        (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usDataReqFailTimes)
#define NAS_EMM_GetInterTauOtherFailTimes()         (NAS_EMM_GetInterTauSuccRatioInfoAddr()->usOtherFailTimes)

#define NAS_EMM_GetOmSuccRationAttInfoAddr()             (&NAS_EMM_GetEmmOmEntityAddr()->stAttachSuccRatio)
#define NAS_EMM_GetOmSuccRationAttTolTimes()             (NAS_EMM_GetOmSuccRationAttInfoAddr()->usTolalTimes)
#define NAS_EMM_GetOmSuccRationAttSuccTimes()            (NAS_EMM_GetOmSuccRationAttInfoAddr()->usSuccTimes)
#define NAS_EMM_GetOmSuccRationAttBarFailTimes()         (NAS_EMM_GetOmSuccRationAttInfoAddr()->usBarFailTimes)
#define NAS_EMM_GetOmSuccRationAttNoRfFailTimes()        (NAS_EMM_GetOmSuccRationAttInfoAddr()->usNoRfFailTimes)
#define NAS_EMM_GetOmSuccRationAttEstFailTimes()         (NAS_EMM_GetOmSuccRationAttInfoAddr()->usEstFailTimes)
#define NAS_EMM_GetOmSuccRationAttExpFailTimes()         (NAS_EMM_GetOmSuccRationAttInfoAddr()->usExpFailTimes)
#define NAS_EMM_GetOmSuccRationAttRejFailTimes()         (NAS_EMM_GetOmSuccRationAttInfoAddr()->usRejFailTimes)
#define NAS_EMM_GetOmSuccRationAttRelFailTimes()         (NAS_EMM_GetOmSuccRationAttInfoAddr()->usRelFailTimes)
#define NAS_EMM_GetOmSuccRationAttEsmFailTimes()         (NAS_EMM_GetOmSuccRationAttInfoAddr()->usEsmFailTimes)
#define NAS_EMM_GetOmSuccRationAttDataReqFailTimes()     (NAS_EMM_GetOmSuccRationAttInfoAddr()->usDataReqFailTimes)
#define NAS_EMM_GetOmSuccRationAttOtherFailTimes()       (NAS_EMM_GetOmSuccRationAttInfoAddr()->usOtherFailTimes)

#define NAS_EMM_GetOmSuccRationSerInfoAddr()     (&NAS_EMM_GetEmmOmEntityAddr()->stServiceSuccRatio)
#define NAS_EMM_GetMtSerSuccRatioInfoAddr()      (&(NAS_EMM_GetOmSuccRationSerInfoAddr()->stMtSerSuccRatio))
#define NAS_EMM_GetMtSerTolalTimes()             (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usTolalTimes)
#define NAS_EMM_GetMtSerSuccTimes()              (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usSuccTimes)
#define NAS_EMM_GetMtSerBarFailTimes()           (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usBarFailTimes)
#define NAS_EMM_GetMtSerNoRfFailTimes()          (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usNoRfFailTimes)
#define NAS_EMM_GetMtSerEstFailTimes()           (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usEstFailTimes)
#define NAS_EMM_GetMtSerExpFailTimes()           (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usExpFailTimes)
#define NAS_EMM_GetMtSerRejFailTimes()           (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usRejFailTimes)
#define NAS_EMM_GetMtSerRelFailTimes()           (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usRelFailTimes)
#define NAS_EMM_GetMtSerDataReqFailTimes()       (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usDataReqFailTimes)
#define NAS_EMM_GetMtSerOtherFailTimes()         (NAS_EMM_GetMtSerSuccRatioInfoAddr()->usOtherFailTimes)

#define NAS_EMM_GetMoSerSuccRatioInfoAddr()      (&(NAS_EMM_GetOmSuccRationSerInfoAddr()->stMoSerSuccRatio))
#define NAS_EMM_GetMoSerTolalTimes()             (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usTolalTimes)
#define NAS_EMM_GetMoSerSuccTimes()              (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usSuccTimes)
#define NAS_EMM_GetMoSerBarFailTimes()           (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usBarFailTimes)
#define NAS_EMM_GetMoSerNoRfFailTimes()          (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usNoRfFailTimes)
#define NAS_EMM_GetMoSerEstFailTimes()           (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usEstFailTimes)
#define NAS_EMM_GetMoSerExpFailTimes()           (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usExpFailTimes)
#define NAS_EMM_GetMoSerRejFailTimes()           (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usRejFailTimes)
#define NAS_EMM_GetMoSerRelFailTimes()           (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usRelFailTimes)
#define NAS_EMM_GetMoSerDataReqFailTimes()       (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usDataReqFailTimes)
#define NAS_EMM_GetMoSerOtherFailTimes()         (NAS_EMM_GetMoSerSuccRatioInfoAddr()->usOtherFailTimes)

#define NAS_EMM_GetOmAttachDelayInfoAddr()          (&NAS_EMM_GetEmmOmEntityAddr()->stAttachDelayInfo)
#define NAS_EMM_GetOmAttachDelayInfoOpEstSucc()     (NAS_EMM_GetOmAttachDelayInfoAddr()->bitOpEstSucc)
#define NAS_EMM_GetOmAttachDelayInfoStartTime()     (NAS_EMM_GetOmAttachDelayInfoAddr()->ulStart)
#define NAS_EMM_GetOmAttachDelayInfoReqSndTime()    (NAS_EMM_GetOmAttachDelayInfoAddr()->ulAttachReqSnd)
#define NAS_EMM_GetOmAttachDelayInfoEstSuccTime()   (NAS_EMM_GetOmAttachDelayInfoAddr()->ulEstSucc)
#define NAS_EMM_GetOmAttachDelayInfoulAcceptTime()  (NAS_EMM_GetOmAttachDelayInfoAddr()->ulAttachAccept)
#define NAS_EMM_GetOmAttachDelayInfoCmpSndTime()    (NAS_EMM_GetOmAttachDelayInfoAddr()->ulAttachCompleteSnd)
#define NAS_EMM_GetOmAttachDelayInfoEndTime()       (NAS_EMM_GetOmAttachDelayInfoAddr()->ulEnd)

#define NAS_EMM_GetOmMoSerDelayInfoAddr()           (&NAS_EMM_GetEmmOmEntityAddr()->stMoServiceDelayInfo)
#define NAS_EMM_GetOmMoSerStartTime()               (NAS_EMM_GetOmMoSerDelayInfoAddr()->ulStart)
#define NAS_EMM_GetOmMoSerReqSndTime()              (NAS_EMM_GetOmMoSerDelayInfoAddr()->ulServiceReqSnd)
#define NAS_EMM_GetOmMoSerEstSuccTime()             (NAS_EMM_GetOmMoSerDelayInfoAddr()->ulEstSucc)
#define NAS_EMM_GetOmMoSerEndTime()                 (NAS_EMM_GetOmMoSerDelayInfoAddr()->ulEnd)

#define NAS_EMM_GetOmMtSerDelayInfoAddr()           (&NAS_EMM_GetEmmOmEntityAddr()->stMtServiceDelayInfo)
#define NAS_EMM_GetOmMtSerStartTime()               (NAS_EMM_GetOmMtSerDelayInfoAddr()->ulStart)
#define NAS_EMM_GetOmMtSerReqSndTime()              (NAS_EMM_GetOmMtSerDelayInfoAddr()->ulServiceReqSnd)
#define NAS_EMM_GetOmMtSerEstSuccTime()             (NAS_EMM_GetOmMtSerDelayInfoAddr()->ulEstSucc)
#define NAS_EMM_GetOmMtSerEndTime()                 (NAS_EMM_GetOmMtSerDelayInfoAddr()->ulEnd)
/* LNAS复位可维可测记录消息条数 */
#define LNAS_EXC_MAX_SAVE_MSG_NUM          50

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

enum    NAS_EMM_OM_MSG_ENUM
{
    /* 定时器使用区间，需保留 */
    ID_NAS_EMM_OM_TIMER_MSG_MIN                     = PS_MSG_ID_EMM_TO_EMM_OM_BASE,
    /* 为定时器预留70个ID */
    ID_NAS_EMM_OM_TIMER_MSG_MAX                     = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x46,  /* 7355 */

    /* 美国需求DAM相关的EMM OM信息 */
    ID_NAS_EMM_OM_DAM_PARA_LOG                      = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x47,  /* _H2ASN_MsgChoice NAS_EMM_OM_DAM_PARA_LOG_STRU */
    /* LMM定制需求公共NV参数OM输出 */
    ID_NAS_EMM_OM_COMM_CONFIG_PARA_LOG              = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x48,  /* _H2ASN_MsgChoice NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU */
    /* LMM输出REJ#19计数           */
    ID_NAS_EMM_OM_REJ19_CNT_LOG                     = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x49,  /* _H2ASN_MsgChoice NAS_EMM_OM_REJ19_CNT_LOG_STRU */
    /* 状态变更可维可测 */
    ID_NAS_LMM_OM_LOG_STATE_CHANGE_INFO             = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x4a,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_STATE_CHANGE_INFO_STRU */
    /* UE NET CAPABILITY NV参数输出 */
    ID_NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY       = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x4b,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU */
    ID_NAS_LMM_OM_LOG_UE_ID_INFO                    = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x4c,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_UE_ID_INFO_STRU */
    ID_NAS_LMM_OM_LOG_EPS_LOC_INFO                  = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x4d,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU */
    ID_NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO          = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x4e,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU */
    ID_NAS_LMM_OM_LOG_FORBIDDEN_INFO                = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x4f,  /* _H2ASN_MsgChoice NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU */
    ID_NAS_LMM_OM_LOG_NW_CAUSE_CHANGE_INFO          = ID_NAS_EMM_OM_TIMER_MSG_MAX  + 0x0a,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU */
    /* TMO需求设置TAU ACTIVE FLAG OM信息 */
    ID_NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG           = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x51,  /* _H2ASN_MsgChoice NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU */
    ID_NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL            = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x52,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU */
    ID_NAS_LMM_OM_LOG_TAU_START_TYPE_INFO           = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x53,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU */
    ID_NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL            = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x54,  /* _H2ASN_MsgChoice NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU */
    ID_NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL            = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x55,  /* _H2ASN_MsgChoice NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL_STRU */
    ID_NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL            = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x56,  /* _H2ASN_MsgChoice NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU */
    ID_NAS_LMM_OM_LOG_SECU_VERIFY_FAIL              = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x57,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU */
    ID_NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO              = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x58,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU */
    /* 雷显调增加的调试信息        */
    ID_NAS_LMM_OM_LOG_SER_START_TYPE_INFO       = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x59,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU */
    ID_NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO     = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x5a,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU */
    ID_NAS_LMM_OM_LOG_STATIC_UE_ID_INFO         = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x5b,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU */
    ID_NAS_LMM_OM_LOG_CONN_STATE_INFO           = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x5c,  /* _H2ASN_MsgChoice NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU */
    ID_NAS_EMM_OM_GRADUAL_FORB_TA_INFO          = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x5D,  /* _H2ASN_MsgChoice NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU */
    ID_NAS_EMM_OM_GRADUAL_FORB_PARA_LOG         = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x5E,  /* _H2ASN_MsgChoice NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU */
    ID_NAS_EMM_OM_DEBUG_INFO_LOG                    = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x5F,  /* _H2ASN_MsgChoice NAS_EMM_DBG_INFO_IND_STRU */
    ID_NAS_EMM_OM_MSG_BUTT                          = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x60,

    /*EMM与MMC接口的API*/
    LNAS_OM_LOG_PUB_INFO_IND                        = PS_MSG_ID_LNAS_TO_OM_BASE,            /*_H2ASN_MsgChoice NAS_LMM_LOG_PUB_INFO_STRU*/
    LNAS_OM_LOG_GU_INFO_IND                         = PS_MSG_ID_LNAS_TO_OM_BASE + 0x01,     /*_H2ASN_MsgChoice NAS_LMM_LOG_GU_INFO_STRU*/
    LNAS_OM_LOG_TIN_INFO_IND                        = PS_MSG_ID_LNAS_TO_OM_BASE + 0x02,     /*_H2ASN_MsgChoice NAS_LMM_LOG_TIN_INFO_STRU*/
    LNAS_OM_LOG_MS_NETWORK_CAPACILITY_INFO_IND      = PS_MSG_ID_LNAS_TO_OM_BASE + 0x03,     /*_H2ASN_MsgChoice NAS_LMM_LOG_MS_NETWORK_CAPACILITY_INFO_STRU*/
    LNAS_OM_LOG_UEIDTMSI_IND                        = PS_MSG_ID_LNAS_TO_OM_BASE + 0x04,     /*_H2ASN_MsgChoice NAS_LMM_LOG_UEIDTMSI_INFO_STRU*/
    LNAS_OM_LOG_CS_SERVICE_FLAG_INFO_IND            = PS_MSG_ID_LNAS_TO_OM_BASE + 0x05,     /*_H2ASN_MsgChoice NAS_LMM_LOG_CS_SERVICE_FLAG_INFO_STRU*/
    LNAS_OM_LOG_ADD_UPDATE_RSLT_INFO_IND            = PS_MSG_ID_LNAS_TO_OM_BASE + 0x06,     /*_H2ASN_MsgChoice NAS_LMM_LOG_ADD_UPDATE_RSLT_INFO_STRU*/
    LNAS_OM_LOG_PS_BEAR_CTX_INFO_IND                = PS_MSG_ID_LNAS_TO_OM_BASE + 0x07,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PS_BEAR_CTX_INFO_STRU*/
    LNAS_OM_LOG_PSBER_EXIST_BEF_ISRACT_INFO_IND     = PS_MSG_ID_LNAS_TO_OM_BASE + 0x08,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PSBER_EXIST_BEF_ISRACT_INFO_STRU*/
    LNAS_OM_LOG_BEAR_ISR_ACT_AFTER_INFO_IND         = PS_MSG_ID_LNAS_TO_OM_BASE + 0x09,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PSBER_EXIST_AFTER_ISRACT_INFO_STRU*/
    LNAS_OM_LOG_EMERGENCY_NUMLIST_INFO_IND          = PS_MSG_ID_LNAS_TO_OM_BASE + 0x0a,     /*_H2ASN_MsgChoice NAS_LMM_LOG_EMERGENCY_NUMLIST_INFO_STRU*/
    LNAS_OM_LOG_PSREG_CONTAINDRX_INFO_IND           = PS_MSG_ID_LNAS_TO_OM_BASE + 0x0b,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PSREG_CONTAINDRX_INFO_STRU*/
    LNAS_OM_LOG_EUTRAN_PS_DRX_LEN_INFO_IND          = PS_MSG_ID_LNAS_TO_OM_BASE + 0x0c,     /*_H2ASN_MsgChoice NAS_LMM_LOG_UE_EUTRAN_PS_DRX_LEN_INFO_STRU*/
    LNAS_OM_LOG_DRX_TIMER_INFO_IND                  = PS_MSG_ID_LNAS_TO_OM_BASE + 0x0d,     /*_H2ASN_MsgChoice NAS_LMM_LOG_NON_DRX_TIMER_INFO_STRU*/
    LNAS_OM_LOG_SPLIT_PG_CYCLE_CODE_INFO_IND        = PS_MSG_ID_LNAS_TO_OM_BASE + 0x0e,     /*_H2ASN_MsgChoice NAS_LMM_LOG_DRX_SPLIT_PG_CYCLE_CODE_INFO_STRU*/
    LNAS_OM_LOG_SPLIT_ON_CCCH_INFO_IND              = PS_MSG_ID_LNAS_TO_OM_BASE + 0x0f,     /*_H2ASN_MsgChoice NAS_LMM_LOG_DRX_SPLIT_ON_CCCH_INFO_STRU*/
    LNAS_OM_LOG_CLASSMARK2_INFO_IND                 = PS_MSG_ID_LNAS_TO_OM_BASE + 0x10,     /*_H2ASN_MsgChoice NAS_LMM_LOG_CLASSMARK2_INFO_STRU*/
    LNAS_OM_LOG_CS_ATTACH_ALLOW_FLG_INFO_IND        = PS_MSG_ID_LNAS_TO_OM_BASE + 0x11,     /*_H2ASN_MsgChoice NAS_LMM_LOG_CS_ATTACH_ALLOW_FLG_INFO_STRU*/
    LNAS_OM_LOG_PS_ATTACH_ALLOW_FLG_INFO_IND        = PS_MSG_ID_LNAS_TO_OM_BASE + 0x12,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PS_ATTACH_ALLOW_FLG_INFO_STRU*/
    LNAS_OM_LOG_MS_MODE_INFO_IND                    = PS_MSG_ID_LNAS_TO_OM_BASE + 0x13,     /*_H2ASN_MsgChoice NAS_LMM_LOG_MS_MODE_INFO_STRU*/
    LNAS_OM_LOG_PLMN_IS_FORBID_INFO_IND             = PS_MSG_ID_LNAS_TO_OM_BASE + 0x14,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PLMNID_IS_FOBID_INFO_STRU*/
    LNAS_OM_LOG_PLMN_EXAXTLY_CMP_INFO_IND           = PS_MSG_ID_LNAS_TO_OM_BASE + 0x15,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PLMN_EXACTLY_COMPARE_INFO_STRU*/
    LNAS_OM_LOG_PS_REG_STATUS_INFO_IND              = PS_MSG_ID_LNAS_TO_OM_BASE + 0x16,     /*_H2ASN_MsgChoice NAS_LMM_LOG_PS_REG_STATUS_INFO_STRU*/
    LNAS_OM_LOG_SIM_TYPE_INFO_IND                   = PS_MSG_ID_LNAS_TO_OM_BASE + 0x17,     /*_H2ASN_MsgChoice NAS_LMM_LOG_SIM_TYPE_INFO_STRU*/
    LNAS_OM_LOG_BSP_KDF_KEY_MAKE_INFO_IND           = PS_MSG_ID_LNAS_TO_OM_BASE + 0x18,     /*_H2ASN_MsgChoice NAS_LMM_LOG_KDF_KEY_INFO_STRU*/
    LNAS_OM_LOG_SDF_PARA_INFO_IND                   = PS_MSG_ID_LNAS_TO_OM_BASE + 0x19,     /*_H2ASN_MsgChoice NAS_OM_LOG_SDF_PARA_INFO_STRU*/
    LNAS_OM_LOG_PDP_MANAGE_INFO_IND                 = PS_MSG_ID_LNAS_TO_OM_BASE + 0x1a,     /*_H2ASN_MsgChoice NAS_OM_LOG_PDP_MANAGER_INFO_STRU*/
    LNAS_OM_LOG_CARD_IMSI_INFO_IND                  = PS_MSG_ID_LNAS_TO_OM_BASE + 0x1b,     /*_H2ASN_MsgChoice NAS_LMM_LOG_CARD_IMSI_INFO_STRU*/
    LNAS_OM_LOG_USIMM_SERVICE_INFO_IND              = PS_MSG_ID_LNAS_TO_OM_BASE + 0x1c,     /*_H2ASN_MsgChoice NAS_LMM_LOG_USIMM_SERVICE_INFO_STRU*/
    LNAS_OM_LOG_USIMM_TEST_MODE_INFO_IND            = PS_MSG_ID_LNAS_TO_OM_BASE + 0x1d,     /*_H2ASN_MsgChoice NAS_LMM_LOG_USIM_TEST_MODE_INFO_STRU*/
    LNAS_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_IND   = PS_MSG_ID_LNAS_TO_OM_BASE + 0x1e,     /*_H2ASN_MsgChoice NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU*/
    LNAS_OM_LOG_LTE_NW_IMS_VOICE_CAP_INFO_IND       = PS_MSG_ID_LNAS_TO_OM_BASE + 0x1f,     /*_H2ASN_MsgChoice NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU*/
    LNAS_OM_LOG_GU_NW_IMS_VOICE_CAP_INFO_IND        = PS_MSG_ID_LNAS_TO_OM_BASE + 0x20,     /*_H2ASN_MsgChoice NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU*/
    LNAS_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_INFO_IND= PS_MSG_ID_LNAS_TO_OM_BASE + 0x21,     /*_H2ASN_MsgChoice NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU */
    LNAS_OM_LOG_MSG_BUTT                            = PS_MSG_ID_LNAS_TO_OM_BASE + 0x1f,

    LNAS_OM_LOG_DSDS_PREPROC_MSG_INFO_IND           = PS_MSG_ID_DSDS_DEBUG_BASE,           /*_H2ASN_MsgChoice NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU*/
    LNAS_OM_LOG_DSDS_SESSION_MSG_INFO_IND           = PS_MSG_ID_DSDS_DEBUG_BASE + 0x01,    /*_H2ASN_MsgChoice NAS_LMM_DSDS_SESSION_MSG_INFO_STRU*/

    LNAS_OM_LOG_DSDS_SESSION_MSG_BUTT               = PS_MSG_ID_DSDS_DEBUG_BASE + 0x1f,

    /* 大数据可维可测消息ID段 */
    ID_NAS_EMM_OM_KPI_BASE                          = TL_KPI_MSG_ID_LTE_NAS_BASE,           /* 7861 */
    ID_NAS_EMM_OM_ATTACH_SUCC_RATIO_INFO            = ID_NAS_EMM_OM_KPI_BASE + 0x00,        /* _H2ASN_MsgChoice NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU */
    ID_NAS_EMM_OM_TAU_SUCC_RATIO_INFO               = ID_NAS_EMM_OM_KPI_BASE + 0x01,        /* _H2ASN_MsgChoice NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU */
    ID_NAS_EMM_OM_SERVICE_SUCC_RATIO_INFO           = ID_NAS_EMM_OM_KPI_BASE + 0x02,        /* _H2ASN_MsgChoice NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU */
    ID_NAS_EMM_OM_ATTACH_DELAY_INFO                 = ID_NAS_EMM_OM_KPI_BASE + 0x03,        /* _H2ASN_MsgChoice NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU */
    ID_NAS_EMM_OM_SERVICE_DELAY_INFO                = ID_NAS_EMM_OM_KPI_BASE + 0x04,        /* _H2ASN_MsgChoice NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU */

    ID_NAS_EMM_OM_KPI_BUTT                          = ID_NAS_EMM_OM_KPI_BASE + 0x3f
};
typedef VOS_UINT32  NAS_EMM_TO_EMM_OM_MSG_ENUM_UINT32;




enum    NAS_EMM_FTM_ACTION_FLAG_ENUM
{
    NAS_EMM_FTM_ACTION_FLAG_CLOSE = 0,
    NAS_EMM_FTM_ACTION_FLAG_OPEN = 1,
    NAS_EMM_FTM_ACTION_FLAG_BUTT
};
typedef VOS_UINT32  NAS_EMM_FTM_ACTION_FLAG_ENUM_UINT32;

enum NAS_EMM_ERRLOG_ACTION_FLAG_ENUM
{
    NAS_EMM_ERRLOG_ACTION_FLAG_CLOSE  = 0,
    NAS_EMM_ERRLOG_ACTION_FLAG_OPEN   = 1,
    NAS_EMM_ERRLOG_ACTION_FLAG_BUTT
};
typedef VOS_UINT32  NAS_EMM_ERRLOG_ACTION_FLAG_ENUM_UINT32;

enum NAS_EMM_ERRLOG_LEVEL_ENUM
{
    NAS_EMM_ERRLOG_LEVEL_CRITICAL   = 1,/*代表紧急*/
    NAS_EMM_ERRLOG_LEVEL_MAJOR      = 2,/*代表重要*/
    NAS_EMM_ERRLOG_LEVEL_MINOR      = 3,/*代表次要*/
    NAS_EMM_ERRLOG_LEVEL_WARING     = 4,/*代表提示，*/
    NAS_EMM_ERRLOG_LEVEL_BUTT
};
typedef VOS_UINT16  NAS_EMM_ERRLOG_LEVEL_ENUM_UINT16;

/* ERROR LOG故障&警告类型*/
enum NAS_EMM_ERRLOG_TYPE_ENUM
{
    NAS_EMM_ERRLOG_TYPE_COMMUNICATION       = 0x00, /* 通信     */
    NAS_EMM_ERRLOG_TYPE_SERVING_QUALITY     = 0x01, /* 业务质量 */
    NAS_EMM_ERRLOG_TYPE_PROCESS_ERROR       = 0x02, /* 处理出错 */
    NAS_EMM_ERRLOG_TYPE_EQUIPMENT_TROUBLE   = 0x03, /* 设备故障 */
    NAS_EMM_ERRLOG_TYPE_ENVIRONMENT_TROUBLE = 0x04, /* 环境故障 */
};
typedef VOS_UINT16 NAS_EMM_ERRLOG_TYPE_ENUM_UINT16;


enum    NAS_EMM_OMT_AIR_MSG_UP_DOWN_ENUM
{
    NAS_EMM_OMT_AIR_MSG_UP              = 0x00,             /* UPWARD */
    NAS_EMM_OMT_AIR_MSG_DOWN            = 0x01,             /* DOWNWARD */

    NAS_EMM_OMT_AIR_MSG_BUTT
};
typedef VOS_UINT8   NAS_LMM_OM_AIR_MSG_UP_DOWN_ENUM_UINT8;

enum    NAS_EMM_OMT_AIR_MSG_ID_ENUM
{
    NAS_EMM_ATTACH_REQ                  = MM_ATTACH_REQ,
    NAS_EMM_ATTACH_ACP                  = MM_ATTACH_ACP,
    NAS_EMM_ATTACH_CMP                  = MM_ATTACH_CMP,
    NAS_EMM_ATTACH_REJ                  = MM_ATTACH_REJ,

    NAS_EMM_DETACH_REQ_MT               = MM_DETACH_REQ_MT,
    NAS_EMM_DETACH_ACP_MT               = MM_DETACH_ACP_MT,
    NAS_EMM_DETACH_REQ_MO               = MM_DETACH_REQ_MO,
    NAS_EMM_DETACH_ACP_MO               = MM_DETACH_ACP_MO,

    NAS_EMM_TAU_REQ                     = MM_TAU_REQ,
    NAS_EMM_TAU_ACP                     = MM_TAU_ACP,
    NAS_EMM_TAU_CMP                     = MM_TAU_CMP,
    NAS_EMM_TAU_REJ                     = MM_TAU_REJ,

    NAS_EMM_SER_REQ                     = MM_SER_REQ,
    NAS_EMM_SER_REJ                     = MM_SER_REJ,
    NAS_EMM_SER_ACP                     = MM_SER_ACP,

    NAS_EMM_GUTI_CMD                    = MM_GUTI_CMD,
    NAS_EMM_GUTI_CMP                    = MM_GUTI_CMP,

    NAS_EMM_IDEN_REQ                    = MM_IDEN_REQ,
    NAS_EMM_IDEN_RSP                    = MM_IDEN_RSP,

    NAS_EMM_AUTH_REQ                    = MM_AUTH_REQ,
    NAS_EMM_AUTH_FAIL                   = MM_AUTH_FAIL,
    NAS_EMM_AUTH_RSP                    = MM_AUTH_RSP,
    NAS_EMM_AUTH_REJ                    = MM_AUTH_REJ,

    NAS_EMM_SECU_CMD                    = MM_SECU_CMD,
    NAS_EMM_SECU_CMP                    = MM_SECU_CMP,
    NAS_EMM_SECU_REJ                    = MM_SECU_REJ,

    NAS_EMM_STATUS                      = MM_EMM_STATUS,
    NAS_EMM_INFO                        = MM_EMM_INFO,

    NAS_EMM_DOWNLINK_NAS_TRANSPORT      = MM_EMM_DOWNLINK_NAS_TRANSPORT,
    NAS_EMM_UPLINK_NAS_TRANSPORT        = MM_EMM_UPLINK_NAS_TRANSPORT,

    NAS_EMM_EXTENDED_SER_REQ            = MM_EXTENDED_SER_REQ,                  /* 2012-02-24 */
    NAS_EMM_CS_SER_NOTIFICATION         = MM_CS_SER_NOTIFICATION,               /* 2012-02-24 */

    NAS_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT = MM_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT,
    NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT   = MM_EMM_UPLINK_GENERIC_NAS_TRANSPORT,
};
typedef VOS_UINT8   NAS_LMM_OM_AIR_MSG_ID_ENUM_UINT8;


enum    PS_EMM_OMT_KEY_EVENT_TYPE_ENUM
{   /* EMM关键事件取值范围100 - 199 */

    EMM_OMT_KE_PLMN_SPEC_SEARCH_START   = MM_KEY_EVENT_PLMN_SPEC_SEARCH_START,
    EMM_OMT_KE_PLMN_LIST_SEARCH_START   = MM_KEY_EVENT_PLMN_LIST_SEARCH_START,
    EMM_OMT_KE_PLMN_SEARCH_SUCC         = MM_KEY_EVENT_PLMN_SEARCH_SUCC,
    EMM_OMT_KE_PLMN_SEARCH_FAIL         = MM_KEY_EVENT_PLMN_SEARCH_SUCC,
    EMM_OMT_KE_START_AUTO_RESEL         = MM_KEY_EVENT_START_AUTO_RESEL,
    EMM_OMT_KE_START_MANUAL_RESEL       = MM_KEY_EVENT_START_MANUAL_RESEL,
    EMM_OMT_KE_PLMN_RESEL_CNF           = MM_KEY_EVENT_PLMN_RESEL_CNF,
    EMM_OMT_KE_COVERAGE_LOST            = MM_KEY_EVENT_COVERAGE_LOST,

    EMM_OMT_KE_ATTACH_REQ               = MM_KEY_EVENT_ATTACH_REQ,
    EMM_OMT_KE_ATTACH_ACP               = MM_KEY_EVENT_ATTACH_ACP,
    EMM_OMT_KE_ATTACH_CMP               = MM_KEY_EVENT_ATTACH_CMP,
    EMM_OMT_KE_ATTACH_REJ               = MM_KEY_EVENT_ATTACH_REJ,

    EMM_OMT_KE_DETACH_REQ_MT            = MM_KEY_EVENT_ATTACH_REJ,
    EMM_OMT_KE_DETACH_ACP_MT            = MM_KEY_EVENT_DETACH_REQ_MT,
    EMM_OMT_KE_DETACH_REQ_MO            = MM_KEY_EVENT_DETACH_REQ_MT,
    EMM_OMT_KE_DETACH_ACP_MO            = MM_KEY_EVENT_DETACH_ACP_MT,

    EMM_OMT_KE_TAU_REQ                  = MM_KEY_EVENT_TAU_REQ,
    EMM_OMT_KE_TAU_ACP                  = MM_KEY_EVENT_TAU_ACP,
    EMM_OMT_KE_TAU_CMP                  = MM_KEY_EVENT_TAU_CMP,
    EMM_OMT_KE_TAU_REJ                  = MM_KEY_EVENT_TAU_REJ,

    EMM_OMT_KE_SER_REQ                  = MM_KEY_EVENT_SER_REQ,
    EMM_OMT_KE_SER_REJ                  = MM_KEY_EVENT_SER_REJ,
    EMM_OMT_KE_SER_ACP                  = MM_KEY_EVENT_SER_ACP,

    EMM_OMT_KE_GUTI_CMD                 = MM_KEY_EVENT_GUTI_CMD,
    EMM_OMT_KE_GUTI_CMP                 = MM_KEY_EVENT_GUTI_CMP,

    EMM_OMT_KE_IDEN_REQ                 = MM_KEY_EVENT_IDEN_REQ,
    EMM_OMT_KE_IDEN_RSP                 = MM_KEY_EVENT_IDEN_RSP,

    EMM_OMT_KE_AUTH_REQ                 = MM_KEY_EVENT_AUTH_REQ,
    EMM_OMT_KE_AUTH_FAIL                = MM_KEY_EVENT_AUTH_FAIL,
    EMM_OMT_KE_AUTH_RSP                 = MM_KEY_EVENT_AUTH_RSP,
    EMM_OMT_KE_AUTH_REJ                 = MM_KEY_EVENT_AUTH_REJ,

    EMM_OMT_KE_SECU_CMD                 = MM_KEY_EVENT_SECU_CMD,
    EMM_OMT_KE_SECU_CMP                 = MM_KEY_EVENT_SECU_CMP,
    EMM_OMT_KE_SECU_REJ                 = MM_KEY_EVENT_SECU_REJ,

    EMM_OMT_KE_EMM_STATUS               = MM_KEY_EVENT_EMM_STATUS,
    EMM_OMT_KE_EMM_INFO                 = MM_KEY_EVENT_EMM_INFO,

    EMM_OMT_KE_EMM_DOWNLINK_NAS_TRANSPORT  = MM_KEY_EVENT_EMM_DOWNLINK_NAS_TRANSPORT,
    EMM_OMT_KE_EMM_UPLINK_NAS_TRANSPORT    = MM_KEY_EVENT_EMM_UPLINK_NAS_TRANSPORT,        /*2011-11-15*/

    EMM_OMT_KE_EXTENDED_SER_REQ         = MM_KEY_EVENT_EXTENDED_SER_REQ,        /*2012-02-24*/
    EMM_OMT_KE_CS_SER_NOTIFICATION      = MM_KEY_EVENT_CS_SER_NOTIFICATION,     /*2012-02-24*/

    EMM_OMT_KE_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT = MM_KEY_EVENT_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT,
    EMM_OMT_KE_EMM_UPLINK_GENERIC_NAS_TRANSPORT   = MM_KEY_EVENT_EMM_UPLINK_GENERIC_NAS_TRANSPORT,

    EMM_OMT_KE_TYPE_BUTT
};
typedef VOS_UINT8   PS_EMM_OMT_KEY_EVENT_TYPE_ENUM_UINT8;

/* OM_EMM_MSG_ID_ENUM_UINT32包括4部分:

-----------------------------------------------------------
  字节高位                                      字节低位
-----------------------------------------------------------
| BYTE1高4位 + 0000 |  BYTE2    |   BYTE3    |    BYTE4   |
-----------------------------------------------------------
0000：协议模块间消息|  源模块号 |  目的模块号| 消息号0-255
-----------------------------------------------------------
0001：L2 LOG        |           |            |
-----------------------------------------------------------
0010：空口消息      |           |            |
-----------------------------------------------------------
0011：普通命令      |           |            | OM_EMM_ORDER_TYPE_ENUM_UINT32
-----------------------------------------------------------
0100：实时监控命令  |           |            | OM_EMM_ORDER_TYPE_ENUM_UINT32
-----------------------------------------------------------
0101：关键事件      |           |            | 保留不用
-----------------------------------------------------------
*/
/*
typedef VOS_UINT32  OMT_EMM_MSG_ID_UINT32;
*/


/* OM和EMM间的维护类命令执行结果类型 */
enum    APP_EMM_MAINTAIN_RST_ENUM
{
    APP_EMM_MAINTAIN_RST_SUCC       = 0x00,
    APP_EMM_MAINTAIN_RST_FAIL,

    APP_EMM_MAINTAIN_RST_BUTT
};
typedef VOS_UINT32  APP_EMM_MAINTAIN_RST_ENUM_UINT32;



/*****************************************************************************
 枚举名    : NAS_EMM_TP_MSG_TYPE_ENUM
 枚举说明  : OM和EMM间的透明类命令类型
*****************************************************************************/

enum    NAS_EMM_TP_MSG_TYPE_ENUM
{
    NAS_EMM_TP_INQ_G_INFO_REQ           = 0x01,

    NAS_EMM_TP_MSG_TYPE_BUTT
};
typedef VOS_UINT32  NAS_EMM_TP_MSG_TYPE_ENUM_UINT32;

enum    APP_EMM_TP_CAUSE_ENUM
{
    APP_EMM_TP_CAUSE_TP_MSG_TYPE_UNKNOWN= 0x01,
    APP_EMM_TP_CAUSE_PARA_RANGE_ERR     = 0x02,
    APP_EMM_TP_CAUSE_BUTT               = 0xFF
};
typedef VOS_UINT32  APP_EMM_TP_CAUSE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : EMM_OM_G_INFO_TYPE_ENUM
 枚举说明  : 查询的信息类型
*****************************************************************************/
enum    EMM_OM_G_INFO_TYPE_ENUM
{
    /*状态类*/
    EMM_OM_G_INFO_EMMUPSTATE           = 0x00000000,   /* */


    /*网络信息类*/
    EMM_OM_G_INFO_EPlMNLIST,
    EMM_OM_G_INFO_TAILIST,


    /*定时器*/
    EMM_OM_G_INFO_T3402,
    EMM_OM_G_INFO_T3412,
    EMM_OM_G_INFO_TAU_T3411,

    /*TAU*/
    EMM_TAU_ATTEMPT_COUNTER,
    EMM_TAU_START_CAUSE,

    /*SER*/
    EMM_SER_START_CAUSE,

    /* DHCPV4 SERVER */
    EMM_DHCPV4_SERVER_DEFT_EPSBID,
    EMM_DHCPV4_SERVER_TMP_STATUS,
    EMM_DHCPV4_SERVER_ALLOC_STATUS,
    EMM_DHCPV4_SERVER_NW_PARA,
    EMM_DHCPV4_SERVER_BUFFER,

    /* IPF */
    EMM_IPF_UL_FILTER_NUM,
    /*身份类*/
    /*安全类*/
    /*其他*/
    /*子模块控制参数: ATTACH, DETACH, TAU, SERIVCE, MMC*/
    /*MML的TIN值信息*/
    EMM_TIN_TYPE,

    /*MML的承载信息*/
    EMM_PS_BEARER_INFO,
    /*L.V.R TAI*/
    EMM_LVR_TAI = 17,

    /*Reg Domain*/
    EMM_REG_DOMAIN = 18,
    EMM_OM_G_INFO_BUTT
};
typedef VOS_UINT32  EMM_OM_G_INFO_TYPE_ENUM_UINT32;

enum    NAS_EMM_DRX_CYCLE_LEN_CHANGE_ENUM
{
    NAS_EMM_DRX_CYCLE_LEN_CHANGED       = 0,
    NAS_EMM_DRX_CYCLE_LEN_NOT_CHANGED   = 1,
    NAS_EMM_DRX_CYCLE_LEN_CHANGE_BUTT
};
typedef VOS_UINT32   NAS_EMM_DRX_CYCLE_LEN_CHANGE_ENUM_UINT32;
enum NAS_LMM_TIN_TYPE_ENUM
{
    NAS_LMM_TIN_P_TMSI                  = 0x00000000,
    NAS_LMM_TIN_GUTI                    ,
    NAS_LMM_TIN_RAT_RELATED_TMSI        ,
    NAS_LMM_TIN_INVALID                 ,

    NAS_LMM_TIN_BUTT
};
typedef VOS_UINT32 NAS_LMM_TIN_TYPE_ENUM_UINT32;
/*****************************************************************************
 枚举名    : NAS_LMM_OM_PCE_TIMES_TYPE_ENUM
 枚举说明  : 计数类型
*****************************************************************************/
enum NAS_LMM_OM_PCE_TIMES_TYPE_ENUM
{
    NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL             = 1, /*总计数*/
    NAS_LMM_OM_PCE_TIMES_TYPE_SUCC              = 2, /*成功数*/
    NAS_LMM_OM_PCE_TIMES_TYPE_BAR               = 3, /*被BAR*/
    NAS_LMM_OM_PCE_TIMES_TYPE_NO_RF             = 4, /*NO RF*/
    NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL          = 5, /*建链失败*/
    NAS_LMM_OM_PCE_TIMES_TYPE_EXP               = 6, /*定时器超时*/
    NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ            = 7, /*CN REJ错误*/
    NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL          = 8, /*收到LRRC释放*/
    NAS_LMM_OM_PCE_TIMES_TYPE_ESM_FAIL          = 9, /*esm fail*/
    NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL     = 10, /*data req失败*/
    NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL       = 11, /*其他*/

    NAS_LMM_OM_PROCEDURE_FAIL_TYPE_BUTT
};
typedef VOS_UINT16 NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : NAS_LMM_OM_TAU_START_TYPE_ENUM
 枚举说明  : TAU发起原因,用于可维可测
*****************************************************************************/
enum NAS_LMM_OM_TAU_START_TYPE_ENUM
{
    NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS                    = 1,   /*注册CS域*/
    NAS_LMM_OM_TAU_START_TYPE_MT_IMSI_DETACH                    = 2,   /*MT IMSI DETACH*/
    NAS_LMM_OM_TAU_START_TYPE_3412_EXP                          = 3,   /*3412超时*/
    NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE               = 4,   /*VOICE DOMAIN变更*/
    NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST                   = 5,   /*不在TAI LIST中*/
    NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED            = 6,   /*承载变更*/
    NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED                      = 7,   /*DRX变更*/
    NAS_LMM_OM_TAU_START_TYPE_NOT_EU1                           = 8,   /*不为EU1*/
    NAS_LMM_OM_TAU_START_TYPE_LOAD_BALANCE                      = 9,   /*负载均衡*/
    NAS_LMM_OM_TAU_START_TYPE_CONN_FAIL                         = 10,   /*CONN FAIL*/
    NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE                  = 11,  /*无线能力变更*/

    /*p）when the UE activates mobility management for IMS voice termination as specified in 3GPP TS 24.008 [13],
            annex P.2, and the TIN indicates "RAT-related TMSI";*/
            /*IMS voice from not available to available,ISR激活，start TAU*/
    NAS_LMM_OM_TAU_START_TYPE_P2                                = 12,

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    NAS_LMM_OM_TAU_START_TYPE_P4                                = 13,
    NAS_LMM_OM_TAU_START_TYPE_3411OR3402                        = 14,    /*3411或3402超时*/
    NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL                      = 15,    /*消息发送失败*/
    NAS_LMM_OM_TAU_START_TYPE_PTMSI                             = 16,    /*TIN值为P-TMSI*/
    NAS_LMM_OM_TAU_START_TYPE_LAU_COMRAU                        = 17,    /*LAU或者联合RAU*/
    NAS_LMM_OM_TAU_START_TYPE_SRVCC                             = 18,    /*SRVCC*/
    NAS_LMM_OM_TAU_START_TYPE_GPRS_READY_OR_PMM_CONNECT         = 19,    /*GPRS连接状态为READY或者W的连接状态为PMM CONNECTED*/
    NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND                    = 20,    /*GSM PS域挂起*/
    /*t)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
                   and the UE has previously performed the MM connection establishment for CS fallback
                   emergency calls (see 3GPP TS 24.008 [13], subclause 4.5.1.5a) without performing a
                   location area updating procedure or combined routing area updating procedure while
                   camping on a location area which is different from the stored location area.
                   In this case, the EPS update type IE shall be set to "combined TA/LA updating with IMSI attach"*/
    NAS_LMM_OM_TAU_START_TYPE_EMC_CSFB                          = 21,

    NAS_LMM_OM_TAU_START_TYPE_EMC_PDN_EST_REQ                   = 22,   /*紧急PDN建立请求*/
    NAS_LMM_OM_TAU_START_TYPE_3346                              = 23,   /*3346超时*/
    NAS_LMM_OM_TAU_START_TYPE_CCO                               = 24,   /*CCO*/

    NAS_LMM_OM_TAU_START_TYPE_INTER_CHANGE                      = 25,   /*异系统,第一次异系统具体原因值失败后，后面再出发TAU都归结为异系统*/
    NAS_LMM_OM_TAU_START_TYPE_LAST_ATTEMPT_TA_NOT_IN_TAI_LIST   = 26,   /* 上次尝试的TA不在TAI LIST里 */
    NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED                 = 27,   /* 发生过3412定时器超时 */
    NAS_LMM_OM_TAU_START_TYPE_MMC_SUSPEND_FAIL                  = 28,   /* MMC回复挂起失败,回退过程中触发的TAU */
    NAS_LMM_OM_TAU_START_TYPE_PLMN_TA_CHANGE                    = 29,   /* PLMN或者TA变更 */
    NAS_LMM_OM_TAU_START_TYPE_PS_PAGING                         = 30,   /* 收到PS PAGING */
    NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST                   = 31,   /* 不在allowde csg list和operater csg list */
    NAS_LMM_OM_TAU_START_TYPE_CSG_ID_CHANGE                     = 32,   /* CSGID改变 */
    NAS_LMM_OM_TAU_START_TYPE_OTHERS                            = 33,   /*OTHERS*/

    NAS_LMM_OM_TAU_START_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32;
enum NAS_LMM_OM_SER_START_TYPE_ENUM
{
    NAS_LMM_OM_SER_START_TYPE_RRC_PAGING                    = 1,
    NAS_LMM_OM_SER_START_TYPE_RABM_REEST                    = 2,
    NAS_LMM_OM_SER_START_TYPE_ESM_DATA_REQ                  = 3,
    NAS_LMM_OM_SER_START_TYPE_UPLINK_PENDING                = 4,
    NAS_LMM_OM_SER_START_TYPE_SMS_EST_REQ                   = 5,
    NAS_LMM_OM_SER_START_TYPE_ESM_DATA_REQ_EMC              = 6,
    NAS_LMM_OM_SER_START_TYPE_RABM_REEST_EMC                = 7,
    NAS_LMM_OM_SER_START_TYPE_LPP_EST_REQ                   = 8,
    NAS_LMM_OM_SER_START_TYPE_SS_EST_REQ                    = 9,

    NAS_LMM_OM_SER_STRT_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_OM_SER_START_TYPE_ENUM_UINT32;
enum NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ENUM
{
    NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ADD       = 0,
    NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_DEL       = 1,
    NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_TIMER_OUT = 2,
    NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ENUM_UINT8;

/*PC REPLAY MODIFY BY LEILI DELETE*/
/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
}NAS_EMM_PROTOCOL_STATE_MAP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
}NAS_EMM_GENERAL_MSG_HEADER_STRU;

typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;    /*_H2ASN_Skip*/
    NAS_LMM_OM_SER_START_TYPE_ENUM_UINT32       enSerStartType;
}NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;   /*_H2ASN_Skip*/

    NAS_LMM_SIM_STAT_ENUM_UINT32        ulSimStat;
    NAS_LMM_SIM_VALIDITY_ENUM_UINT32    enPsSimValidity;
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT8                           aucRsv[3];
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       enPlmnForb;
    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRoam; /* forbidden tracking areas for roaming */
    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRpos; /* forbidden tracking areas for regional provision of service */
    NAS_MM_TA_STRU                      stTa;
}NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU;

typedef struct
{
    VOS_UINT32                          bitOpImei   :1;
    VOS_UINT32                          bitOpImeisv :1;
    VOS_UINT32                          bitOpRsv    :30;
    NAS_OM_IMSI_INFO_STRU               stImsiInfo;
    VOS_UINT8                           aucImei[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           aucImeisv[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved2[2];
    VOS_UINT32                          ulImsiMncLen;
}NAS_LMM_STATIC_UEID_STRU;

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/*_H2ASN_Skip*/
    NAS_LMM_STATIC_UEID_STRU            stMmUeid;
}NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/*_H2ASN_Skip*/
    NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucPreConnState;
    NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucCurConnState;
}NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU;




/*****************************************************************************
 结构名    : APP_MM_TP_G_INFO_REQ_STRU
 结构说明  : MM的透明命令的通用请求结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER

    NAS_EMM_TP_MSG_TYPE_ENUM_UINT32     ulMmTpCmdType;
    VOS_UINT8                           aucTransCmd[4];
}APP_MM_TP_CMD_REQ_STRU;
/*ID_APP_MM_TP_CMD_REQ*/


/*****************************************************************************
 结构名    : APP_MM_TP_CMD_CNF_STRU
 结构说明  : MM的透明命令的通用响应结构，若是查询G_INFO
                  的成功的CNF消息，见APP_MM_TP_G_INFO_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER

    APP_EMM_MAINTAIN_RST_ENUM_UINT32    ulRslt;
    APP_EMM_TP_CAUSE_ENUM_UINT32        ulCause;
}APP_MM_TP_CMD_CNF_STRU;




/*****************************************************************************
 结构名称  : APP_MM_TP_G_INFO_REQ_STRU
 结构说明  : OM查询MM层全局参数时，给MM的请求结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER


    NAS_EMM_TP_MSG_TYPE_ENUM_UINT32     enMmTpCmdType;      /*查询G_INFO命令*/
    EMM_OM_G_INFO_TYPE_ENUM_UINT32      enGInfoType;        /*待查询的数据类型*/
}APP_MM_TP_G_INFO_REQ_STRU;


/*****************************************************************************
 结构名    : APP_MM_TP_G_INFO_CNF_STRU
 结构说明  : 查询MM层全局参数时，给OM响应的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER

    APP_EMM_MAINTAIN_RST_ENUM_UINT32    ulRslt ;            /* 查询是否成功 */
    EMM_OM_G_INFO_TYPE_ENUM_UINT32      enGInfoType;
    union
    {
        NAS_EMM_UPDATE_STATE_ENUM_UINT8 ucEmmUpStat;
        NAS_MM_PLMN_LIST_STRU           stEPlmnList;
        NAS_MM_TA_LIST_STRU             stTaiList;
        NAS_LMM_TIMER_CTRL_STRU          stTimer;
        VOS_UINT32                      ulTauAttemptCounter;
        NAS_EMM_TAU_START_CAUSE_ENUM_UINT8 enTauStartCause;
        NAS_EMM_SER_START_CAUSE_ENUM_UINT8 enSerStartCause;
        VOS_UINT8                       ucDhcpv4ServerDeftEpsbId;
        VOS_UINT8                       ucDhcpv4SeverTmpStatus;
        VOS_UINT8                       ucDhcpv4SeverAllocStatus;
        /*IP_DHCPV4SERVER_NWPARAM_STRU    stDhcpv4ServerNWParam;*/
        VOS_UINT8                       aucDhcpv4ServerBuffer[NAS_EMM_DHCP_SERVER_BUFFER_LEN];
        VOS_UINT32                      ulIpfUlFilterNum;
        NAS_LMM_TIN_TYPE_ENUM_UINT32    ulTinType;
        NAS_MML_PS_BEARER_CONTEXT_STRU  astPsBearerCtx[EMM_ESM_MAX_EPS_BEARER_NUM];
        NAS_MM_NETWORK_ID_STRU          stLvrTai;
        NAS_LMM_REG_DOMAIN_ENUM_UINT32  enRegDomain;
    }u;

}APP_MM_TP_G_INFO_CNF_STRU;



/*原来写在interface.c*/
typedef struct
{
    VOS_UINT32                          ulNasMsgSize;       /* [1,RRC_NAS_MAX_SIZE_NAS_MSG],Byte */
    VOS_UINT8                           aucNasMsg[4];       /* 消息的前四个字节内容              */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}NAS_MSG_STRU;


/* OM动作处理函数的类型定义 */
typedef VOS_VOID    ( * NAS_LMM_OM_ACTION_FUN )( MsgBlock  *  /* 消息指针 */);


/* OM动作表结构 */
typedef struct
{
    APP_MM_MSG_TYPE_ENUM_UINT32         ulMsgId;     /* 消息ID */
    NAS_LMM_OM_ACTION_FUN                pfFun;       /* 设置 或 查询函数 */
}NAS_LMM_OM_ACT_STRU;



typedef NAS_LMM_COMM_ACTION_FUN          NAS_LMM_PRE_PROC_ACTION_FUN;
typedef NAS_LMM_COMM_ACT_STRU            NAS_LMM_PRE_PROC_ACT_STRU;

typedef struct
{
    VOS_UINT8                                   ucRsrv;
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8              enCnMsgType;
    NAS_LMM_OM_AIR_MSG_ID_ENUM_UINT8             enAirMsg;
    PS_EMM_OMT_KEY_EVENT_TYPE_ENUM_UINT8        enKeyEvent;

}NAS_LMM_OM_MSG_ID_CHANGE_STRU;

typedef struct
{
    APP_MM_MSG_TYPE_ENUM_UINT32         ulMsgId;
    VOS_UINT32                          ulOpId;
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
    VOS_UINT32                          ulRslt;

}NAS_LMM_APP_PARA_SET_RESLT_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /*本次操作标识*/
    APP_MM_SET_TYPE_ENUM_UINT32         enSetType;          /*设置类型:0:设置,1:删除*/
}NAS_LMM_APP_PARA_SET_HEAD_STRU;


typedef struct
{
    APP_EMM_MAIN_STATE_ENUM_UINT16       enMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16        enSubState;

    NAS_EMM_PLMN_ID_STRU                 stPlmnId;
    NAS_EMM_GUTI_STRU                    stGuti;
    /* 单位ms，参考函数 NAS_LMM_ModifyPtlTimer()的处理 */
    VOS_UINT32                           ulTimerLen3412;
    NAS_EMM_TAC_STRU                      stTac;

    NAS_EMM_CN_CAUSE_ENUM_UINT8          enEmmCnRejCause;
    VOS_UINT8                            aucRsv[3];

}EMM_DATABASE_INFO_STRU;

typedef struct
{
    /* 打开或者关闭工程模式上报功能 0:close 1:open*/
    VOS_UINT32                          ulFtmActionFlag;
    /* EMM给OM发送的每个工程模式消息都有此编号，上电为0，然后依次加 1 */
    VOS_UINT32                          ulMsgSN;
    /* EMM工程模式管理结构临时存储CnCause，用于与本地数据库进行比对 */
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enEmmCnRejCause;
    VOS_UINT8                           aucRsv[3];

}EMM_FTM_INFO_MANAGE_STRU;

/*****************************************************************************
 结构名    : LNAS_ERRLOG_CTRL_INFO_STRU
 结构说明  : LNAS_ERRLOG_CTRL_INFO_STRU信息
 1.日    期   : 2014年12月24日
   作    者   : lifuxin 00253982
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucErrLogCtrlFlag;                       /* ERRLOG打开标识 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usAlmLevel;                             /* 故障告警级别 */
} LNAS_ERRLOG_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : LNAS_ERRLOG_BUFF_INFO_STRU
 结构说明  : LNAS_ERRLOG_BUFF_INFO_STRU信息
 1.日    期   : 2014年12月24日
   作    者   : lifuxin 00253982
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_RING_ID                          pstRingBuffer;                          /* LNAS层的共享缓存 */
    VOS_UINT32                          ulOverflowCnt;                          /* Ringbuf溢出的次数 */
}LNAS_ERRLOG_BUFF_INFO_STRU;

/*****************************************************************************
 结构名    : LNAS_ERRLOG_GLO_INFO_STRU
 结构说明  : LNAS_ERRLOG_GLO_INFO_STRU信息
 1.日    期   : 2014年12月24日
   作    者   : lifuxin 00253982
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    LNAS_ERRLOG_CTRL_INFO_STRU       stCtrlInfo;
    LNAS_ERRLOG_BUFF_INFO_STRU       stBuffInfo;
 }LNAS_ERRLOG_GLO_INFO_STRU;

/*****************************************************************************
结构名    : LNAS_ERRLOG_ALM_LEVEL_STRU
结构说明  : LNAS_ERRLOG_ALM_LEVEL_STRU信息
1.日    期   : 2014年12月29日
作    者   : lifuxin 00253982
修改内容   : 新建
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16       enAlmID;        /* 异常模块ID */
    VOS_UINT16                              usLogLevel;     /* 上报log等级 */
}LNAS_ERRLOG_ALM_LEVEL_STRU;

/*****************************************************************************
结构名    : NAS_LMM_CN_CAUSE_TRANS_STRU
结构说明  : NAS_LMM_CN_CAUSE_TRANS_STRU信息
1.日    期   : 2014年12月29日
作    者   : lifuxin 00253982
修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MM_CN_CAUSE_ENUM_UINT8            ulCauseId;    /*cause ID*/
    EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16    ulErrorlogID; /*error id*/
}NAS_LMM_CN_CAUSE_TRANS_STRU;

/*******************************************************************************
 结构名    : LNAS_ERR_LOG_ALM_REPORT_TYPE_STRU
 结构说明  : Alm ID与主动上报类型对应的结构体
 1.日    期   : 2015年08月05日
   作    者   : w00209181
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16           enAlmID;            /* 异常模块ID */
    EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16  enReportType;       /* 上报log等级 */
}LNAS_ERR_LOG_ALM_REPORT_TYPE_STRU;



/*****************************************************************************
 结构名    : NAS_LMM_RECIVE_MSG_STRU
 结构说明  : LMM 入口消息的信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   ulTimeStamp;  /* 时间戳 */
    VOS_UINT32                   ulSendPid;    /* 发送任务Pid */
    VOS_UINT32                   ulMsgName;    /* 发送消息ID */
}NAS_LMM_RECIVE_MSG_STRU;


/*****************************************************************************
 结构名    : NAS_LMM_SAVE_RECIVE_MSG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 发生故障时，模块收到的最新消息
  ulNextIndex保存下一个收到消息索引，例如ulNextIndex = 1，则astReciveMsgInfo[0]
 是最新的收到的消息ID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulNextIndex;
    NAS_LMM_RECIVE_MSG_STRU            astReciveMsgInfo[NAS_SAVE_RECEIVE_MSG_INFO_NUM];
} NAS_LMM_MSG_SAVE_INFO_STRU;



/*MM模块需上报路测的信息，后续上报新内容也需在此添加*/
typedef struct
{
    NAS_MM_GUTI_STRU                         stGuti;           /*GUTI信息 */
    NAS_OM_IMSI_INFO_STRU                    stImsi;           /*IMSI信息 */
    NAS_OM_EMM_STATE_STRU                    stEmmState;        /*EMM状态信息 */
}APP_MM_DT_STRU;
/*****************************************************************************
 结构名    : NAS_EMM_DBG_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EMM可维可测，勾出当前状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;
    VOS_UINT32                           ulFileName;
    VOS_UINT32                           ulLineNo;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enEmmMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enEmmSubState;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enSecuMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSecuSubState;
    VOS_UINT16                           ucPara1;
    VOS_UINT16                           ucPara2;
    VOS_UINT16                           ucPara3;
    VOS_UINT16                           ucPara4;
}NAS_EMM_DBG_INFO_IND_STRU;

/*****************************************************************************
 结构名    : LNAS_EXC_LOG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 复位时保存的NAS信息
*****************************************************************************/
typedef struct
{
    NAS_LMM_FSM_STATE_STRU              astCurFsm[NAS_LMM_PARALLEL_FSM_BUTT];   /* 状态机*//*主状态 */
    NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucRrcConnState; /* 当前RRC连接是否存在 */
    VOS_UINT8                           aucRsv[3];
    NAS_LMM_CUR_LTE_STATE_ENUM_UINT32   ulCurLteState; /* 主从摸*/
}LNAS_EXC_LOG_STRU;
/*****************************************************************************
结构名称    :OM消息ID_NAS_EMM_OM_DAM_PARA_LOG的结构
使用说明    :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;     /*_H2ASN_Skip*/

    VOS_UINT32                          ulCServiceMax;   /* 有效范围1-60，默认值5 */
    VOS_UINT32                          ulCService;      /* CService计数 */
    NAS_MM_PLMN_ID_STRU                 stCampPlmnId;    /* 当前驻留的PLMN */
    NAS_DAM_IMSI_PLMN_LIST              stImsiPlmnList;  /* DAM特性生效的IMSI PLMN列表 */
    NAS_MM_DAM_PLMN_LIST_STRU           stDamPlmnList;   /* DAM特性生效的PLMN列表 */
} NAS_EMM_OM_DAM_PARA_LOG_STRU;

/*****************************************************************************
结构名称    :OM消息ID_NAS_EMM_OM_COMM_CONFIG_PARA_LOG的结构
使用说明    :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;     /*_H2ASN_Skip*/
    LNAS_LMM_NV_COMM_CONFIG_PARA_STRU   stNvCommPara;
} NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU;

/*****************************************************************************
结构名称    :OM消息ID_NAS_EMM_OM_REJ19_CNT_LOG的结构
使用说明    :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;         /*_H2ASN_Skip*/
    VOS_UINT32                          ulRej19AtmptCnt;     /* 当前被拒19所到达的尝试计数     */
    VOS_UINT32                          ulRej19AtmptCntFlag;/* 被拒19NV中设置的尝试次数限定值 */
} NAS_EMM_OM_REJ19_CNT_LOG_STRU;



/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_STATE_CHANGE_INFO_STRU
 结构说明  : 状态转换可维可测
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_FSM_STATE_STRU               stCurState;
    NAS_LMM_FSM_STATE_STRU               stDestState;
}NAS_LMM_OM_LOG_STATE_CHANGE_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_UE_ID_INFO_STRU
 结构说明  : 卡和NV中的IMSI信息上报
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_UEID_STRU                    stMmUeId;
}NAS_LMM_OM_LOG_UE_ID_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU
 结构说明  : 的PSLOC信息上报
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    VOS_UINT32                           bitOpGuti     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                           bitOpTai      :1;
    VOS_UINT32                           bitOpUpState  :1;
    VOS_UINT32                           bitOpRsv      :29;
    NAS_MM_GUTI_STRU                     stGuti;
    NAS_MM_TA_STRU                       stLastRegTai;
    NAS_MM_UPDATE_STATE_ENUM_UINT32      enUpdateState;
}NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_NV_COMM_INFO_STRU
 结构说明  : 重要能力(UeCenter/NasRelease/Config_NWCasue/UMTSCodecType/MedCodecType)信息上报
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    LNAS_LMM_UE_CENTER_ENUM_UINT32       enUeCenter;
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32     ulVoiceDomain;
    VOS_UINT32                           ulNasRelease;
    LNAS_LMM_CONFIG_NWCAUSE_STRU         stConfCause;
    NAS_LMM_CODEC_LIST_STRU              stSupCodecList;
    NAS_MM_UE_NET_CAP_STRU               stUeNetCap;
    LRRC_NAS_AC_CLASS_STRU               stRrcNasAc;
}NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU
 结构说明  : 产品线定制网络原因值转化原因值
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;     /*_H2ASN_Skip*/
    VOS_UINT8                           ucCnCause;
    VOS_UINT8                           ucModifiedCnCause;
    VOS_UINT8                           aucRsv1[2];
    VOS_UINT32                          ucIsHplmn;
    VOS_UINT8                           ucHplmnPsRejChangeTo17Flg;
    VOS_UINT8                           ucVplmnPsRejChangeTo17Flg;
    VOS_UINT8                           aucRsv2[2];
    LNAS_LMM_CONFIG_NWCAUSE_STRU        stConfCause;
}NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU;


/*****************************************************************************
结构名称    :OM消息NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU的结构
使用说明    :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulTmoActiveFlagStatus; /* 当前TMO的active flag标识状态，0无效，1有效 */
} NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU;

typedef VOS_UINT32 ( * NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_FUN )(VOS_VOID);
typedef struct
{
    NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16         enCounterType; /* Attach计数类型 */
    NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_FUN      pfAddAttachCounterProcFun; /* Attach本地计数处理函数 */
}NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_STRU;

typedef VOS_UINT32 ( * NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_FUN )(VOS_VOID);
typedef struct
{
    NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16      enCounterType; /* TAU计数类型 */
    NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_FUN      pfAddTauCounterProcFun; /* TAU本地计数处理函数 */
}NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU;

typedef VOS_UINT32 ( * NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_FUN )(VOS_VOID);
typedef struct
{
    NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16      enCounterType; /* TAU计数类型 */
    NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_FUN      pfAddSerCounterProcFun; /* TAU本地计数处理函数 */
}NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_OM_SUCC_RATIO_INTRA_TAU_STRU的结构
使用说明    :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTolalTimes;
    VOS_UINT16                          usSuccTimes;

    /* 以下为失败情况 */
    VOS_UINT16                          usBarFailTimes;
    VOS_UINT16                          usNoRfFailTimes;
    VOS_UINT16                          usEstFailTimes;
    VOS_UINT16                          usExpFailTimes;
    VOS_UINT16                          usRejFailTimes;
    VOS_UINT16                          usRelFailTimes;
    /*包括TAU REQ和TAU COMPLETE，以及公共消息发送失败导致的TAU*/
    VOS_UINT16                          usDataReqFailTimes;
    VOS_UINT16                          usOtherFailTimes;
}NAS_LMM_OM_SUCC_RATIO_INTRA_TAU_STRU;
/*****************************************************************************
结构名称    :NAS_LMM_OM_SUCC_RATIO_TAU_STRU的结构
使用说明    :TAU成功率大数据本地存储结构
*****************************************************************************/
typedef struct
{
    NAS_LMM_OM_SUCC_RATIO_INTRA_TAU_STRU   stIntraTauSuccRatio;
    NAS_LMM_OM_SUCC_RATIO_INTRA_TAU_STRU   stInterTauSuccRatio;

    /* TAU的当次信息，脚本可以通过从LMM_MMC_TAU_IND消息中获得 */
}NAS_LMM_OM_SUCC_RATIO_TAU_STRU;
/*****************************************************************************
结构名称    :NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU的结构
使用说明    :Attach大数据本地存储结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTolalTimes;
    VOS_UINT16                          usSuccTimes;

    /* 以下为失败情况 */
    VOS_UINT16                          usBarFailTimes;
    VOS_UINT16                          usNoRfFailTimes;
    VOS_UINT16                          usEstFailTimes;
    VOS_UINT16                          usExpFailTimes;
    VOS_UINT16                          usRejFailTimes;
    VOS_UINT16                          usRelFailTimes;
    VOS_UINT16                          usEsmFailTimes;
    /*包括ATTACH REQ和ATTACH COMPLETE,以及公共消息发送失败导致的ATTACH*/
    VOS_UINT16                          usDataReqFailTimes;
    VOS_UINT16                          usOtherFailTimes;
    VOS_UINT16                          usRsv;

    /* ATTACH的当次信息，脚本可以通过从LMM_MMC_ATTACH_IND消息中获得 */
}NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU;
/*****************************************************************************
结构名称    :NAS_LMM_OM_SUCC_RATIO_MO_SER_STRU的结构
使用说明    :Service大数据本地存储结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTolalTimes;
    VOS_UINT16                          usSuccTimes;

    /* 以下为失败情况 */
    VOS_UINT16                          usBarFailTimes;
    VOS_UINT16                          usNoRfFailTimes;
    VOS_UINT16                          usEstFailTimes;
    VOS_UINT16                          usExpFailTimes;
    VOS_UINT16                          usRejFailTimes;
    VOS_UINT16                          usRelFailTimes;
    /*包括SERVICE REQ，以及公共消息发送失败导致的SERVICE*/
    VOS_UINT16                          usDataReqFailTimes;
    VOS_UINT16                          usOtherFailTimes;
}NAS_LMM_OM_SUCC_RATIO_MO_SER_STRU;
/*****************************************************************************
结构名称    :NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU的结构
使用说明    :Service大数据本地存储结构
*****************************************************************************/
typedef struct
{
    NAS_LMM_OM_SUCC_RATIO_MO_SER_STRU   stMoSerSuccRatio;
    NAS_LMM_OM_SUCC_RATIO_MO_SER_STRU   stMtSerSuccRatio;

    /* TAU的当次信息，脚本可以通过从LMM_MMC_TAU_IND消息中获得 */
}NAS_LMM_OM_SUCC_RATIO_SER_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_OM_ATTACH_DELAY_INFO_STRU
 结构说明  : NAS_LMM_OM_ATTACH_DELAY_INFO_STRU信息
 1.日    期   : 2015年05月28日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpEstSucc  :1;
    VOS_UINT32                          bitOpRsv      :31;

    VOS_UINT32                          ulStart;
    VOS_UINT32                          ulAttachReqSnd;
    VOS_UINT32                          ulEstSucc;
    VOS_UINT32                          ulAttachAccept;
    VOS_UINT32                          ulAttachCompleteSnd;
    VOS_UINT32                          ulEnd;
}NAS_LMM_OM_ATTACH_DELAY_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU
 结构说明  : NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU信息
 1.日    期   : 2015年05月28日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStart;
    VOS_UINT32                          ulServiceReqSnd;
    VOS_UINT32                          ulEstSucc;
    VOS_UINT32                          ulEnd;
}NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU;

typedef NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU  NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU;
/*****************************************************************************
结构名称    :NAS_LMM_OM_ENTITY_STRU的结构
使用说明    :可维可测EMM实体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsInterTauFlag;
    VOS_UINT8                           ucIsMtServiceFlag;
    VOS_UINT8                           aucRsv[2];

    NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU  stAttachSuccRatio;
    NAS_LMM_OM_SUCC_RATIO_TAU_STRU      stTauSuccRatio;
    NAS_LMM_OM_SUCC_RATIO_SER_STRU      stServiceSuccRatio;

    NAS_LMM_OM_ATTACH_DELAY_INFO_STRU   stAttachDelayInfo;
    NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU  stMoServiceDelayInfo;
    NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU   stMtServiceDelayInfo;
}NAS_LMM_OM_ENTITY_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU
 结构说明  : NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU信息
 1.日    期   : 2015年05月28日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TL_KPI_HDR_STRU                         stTlKpiHdr;
    NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU      stNasLmmOmAttSuccRatioInfo;
}NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU
 结构说明  : NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU信息
 1.日    期   : 2015年05月28日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TL_KPI_HDR_STRU                         stTlKpiHdr;
    NAS_LMM_OM_SUCC_RATIO_TAU_STRU          stNasLmmOmTauSuccRatioInfo;
}NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU
 结构说明  : NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU信息
 1.日    期   : 2015年05月28日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TL_KPI_HDR_STRU                         stTlKpiHdr;
    NAS_LMM_OM_SUCC_RATIO_SER_STRU          stNasLmmOmSerSuccRatioInfo;
}NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU
 结构说明  : NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU信息
 1.日    期   : 2015年05月28日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TL_KPI_DELAY_HDR_STRU               stTlKpiDelayHdr;
    VOS_UINT32                          bitOpEstSucc  :1;
    VOS_UINT32                          bitOpRsv      :31;
    VOS_UINT32                          ulAttachReqSnd;
    VOS_UINT32                          ulEstSucc;
    VOS_UINT32                          ulAttachAccept;
    VOS_UINT32                          ulAttachCompleteSnd;
}NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_MO_SER_DELAY_INFO_MSG_STRU
 结构说明  : NAS_LMM_OM_MO_SER_DELAY_INFO_MSG_STRU信息
 1.日    期   : 2015年05月28日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TL_KPI_DELAY_HDR_STRU                   stTlKpiDelayHdr;
    VOS_UINT32                              ulIsMtServiceFlag;
    VOS_UINT32                              ulServiceReqSnd;
    VOS_UINT32                              ulEstSucc;
}NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU;

/*****************************************************************************
 结构名    : LNAS_EXC_MSG_ELEMENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS消息可维可测保存结构,用于分析复位问题
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimeStamp;            /* 时间戳*/
    VOS_UINT32                          ulCompPid;              /* ulSendPid | ulRcvPid */
    VOS_UINT32                          ulMsgId;                /* 消息ID */
    VOS_UINT32                          ulPrivate;              /* 用来保存一些重要消息的关键参数*/
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enCurrMainState;        /* 当前主状态 */
    NAS_LMM_SUB_STATE_ENUM_UINT16       enCurrSubState;         /* 当前子状态 */
}LNAS_EXC_MSG_ELEMENT_STRU;
/*****************************************************************************
 结构名    : LNAS_EXC_MSG_MNTN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LMM收到的消息队列(50条),用于分析复位问题
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNextIndex;
    LNAS_EXC_MSG_ELEMENT_STRU           astMsgList[LNAS_EXC_MAX_SAVE_MSG_NUM];
}LNAS_EXC_MSG_MNTN_STRU;
/*****************************************************************************
 结构名    : LNAS_EXC_PRE_STATE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存转状态之前的EMM状态,用于复位分析
*****************************************************************************/
typedef struct
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enPreMainState;        /* 前主状态 */
    NAS_LMM_SUB_STATE_ENUM_UINT16       enPreSubState;         /* 前子状态 */
    VOS_UINT32                          ulTimeStamp;           /* 时间戳*/
}LNAS_EXC_PRE_STATE_STRU;
/*****************************************************************************
 结构名    : LNAS_EXC_LOG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存LMM 复位可维可测信息
*****************************************************************************/
typedef struct
{
    LNAS_EXC_MSG_MNTN_STRU              stLNasMsgList;
    LNAS_EXC_PRE_STATE_STRU             stLNasPreState;
}LNAS_EXC_LOG_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU
 结构说明  : 可维可测， Ims Voice 移动性管理是否打开标志上报
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;     /*_H2ASN_Skip*/
    VOS_UINT8                           ucImsVoiceMMEnable;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU
 结构说明  : 可维可测， 网络对IMS Voice 支持信息上报
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;     /*_H2ASN_Skip*/
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoCap;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU
 结构说明  : 可维可测， reject #17的定制的标识上报
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;     /*_H2ASN_Skip*/
    VOS_UINT8                           ucRoamingRejectNoRetryFlg;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU
 结构说明  : TAU发起原因
 1.日    期   : 2015年07月25日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32   enTauStartType;
}NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU
 结构说明  : REG DOMAIN设置可维可测
 1.日    期   : 2015年07月25日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Gradual Forb优化NV配置及实际控制参数可维可测
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;         /*_H2ASN_Skip*/
    VOS_UINT8                                ucGradualForbFlag;
    VOS_UINT8                                aucRsv[3];
    VOS_UINT32                               ulGradualForbTimerFirstLen;
    VOS_UINT32                               ulGradualForbTimerSecondLen;
    VOS_UINT32                               ulGradualForbTimerAgingLen;
    LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU  stNvGradualForbPara;
}NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU;
/*****************************************************************************
 结构名    : NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Gradual Forb TA及TA LIST可维可测
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stMsgHeader;         /*_H2ASN_Skip*/
    NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ENUM_UINT8   enOperationType;
    VOS_UINT8                                           aucRsv[3];
    NAS_MM_TA_STRU                                      stOperaTa;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST              stGradualForbTaList;
}NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Reg Domain可维可测
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stMsgHeader;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32                      enRegDomainCur;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32                      enRegDomainDst;
    VOS_UINT8                                           ucPsAttachAllowFlg;
    VOS_UINT8                                           ucCsAttachAllowFlg;
    VOS_UINT8                                           ucCsRejCause2Flag;
    VOS_UINT8                                           ucCsRej18Cause18Flg;
    NAS_MM_PLMN_LIST_STRU                               stRej18PlmnList;
}NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_EMM_IMSI_REFRESH_STATUS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EMM可维可测，勾出当前状态
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;
    VOS_UINT8                            ucImsiRefreshStatusFlag;
    VOS_UINT8                            aucRsv[3];
}NAS_EMM_IMSI_REFRESH_STATUS_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_EMM_DRX_CYCLE_LEN_CHANGE_ENUM_UINT32    g_ulDrxCycleLenChange;
extern NAS_LMM_OM_MSG_ID_CHANGE_STRU g_stMmOmMsgIdStru[];
extern VOS_UINT32 g_ulSzieof_g_stMmOmMsgIdStru;
extern APP_MM_DT_REPORT_CTRL_STRU  gastNasDtRptCtrlTbl[NAS_DT_RPT_CTRL_MAX_ITEM_NUM];

extern APP_MS_CLASSMARK_STRU        g_aucMsClassMark;

extern EMM_FTM_INFO_MANAGE_STRU              g_astEmmFtmInfoManage;
extern EMM_DATABASE_INFO_STRU                g_astEmmInfo;

extern LNAS_ERRLOG_GLO_INFO_STRU  stErrlogGloInfo;
extern NAS_LMM_OM_ENTITY_STRU g_stEmmOmEntity;
extern  NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_STRU g_stEmmAddAttachCounterProcTbl[];
extern  VOS_UINT32        g_stEmmAddAttachCounterProcTblLen;
extern NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU g_stEmmAddTauCounterProcTbl[];
extern VOS_UINT32        g_stEmmAddTauCounterProcTblLen;
extern NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_STRU  g_stEmmAddSerCounterProcTbl[];
extern VOS_UINT32  g_stEmmAddSerCounterProcTblLen;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmFindFun( VOS_UINT32          ulMsgId);
extern VOS_UINT32 NAS_LMM_DtCompareGuti(VOS_VOID);
extern VOS_UINT32 NAS_LMM_DtCompareImsi(VOS_VOID);
extern VOS_UINT32 NAS_LMM_DtCompareEmmState(VOS_VOID);
extern VOS_VOID NAS_LMM_DtJudgeifNeedRpt(VOS_VOID);
extern VOS_VOID  NAS_LMM_ReadImsaNvImsCapability( VOS_UINT8 *pucSmsOverIms, VOS_UINT8 *pucSrvcc);

/*
extern  VOS_VOID    NAS_LMM_MtTpSetOptUeNetCap ( MsgBlock    *pMsg);
extern  VOS_VOID    NAS_LMM_MtTpSetOptMsNetCap(  MsgBlock    *pMsg);
*/
extern  VOS_VOID  NAS_LMM_SetAppParaValue
(
    NAS_LMM_APP_PARA_SET_RESLT_STRU      *pstParaInfo,
    const NAS_LMM_APP_PARA_SET_HEAD_STRU       *pstAppMsg
);
extern  VOS_UINT32  NAS_LMM_OmMaintain(          MsgBlock    *pMsg);
extern VOS_VOID     NAS_LMM_PubmDaInqRegStat( MsgBlock    *pMsg );
extern VOS_UINT32 NAS_EMM_OmInfoIndMsgProc(MsgBlock    *pMsg );

extern VOS_UINT32  NAS_LMM_CompareEmmInfo( VOS_VOID );

extern VOS_VOID     NAS_LMM_PubmDaInqLteCs(   MsgBlock    *pMsg  );
extern VOS_VOID     NAS_LMM_PubmDaInqUeMode(   MsgBlock    *pMsg  );
extern  VOS_VOID    NAS_LMM_SendOmtKeyEvent(     PS_EMM_OMT_KEY_EVENT_TYPE_ENUM_UINT8  ucEmmOmtKeyEvent  );
extern  VOS_VOID    NAS_LMM_SendOmtAirMsg(       NAS_LMM_OM_AIR_MSG_UP_DOWN_ENUM_UINT8  ucDir,
                                                NAS_LMM_OM_AIR_MSG_ID_ENUM_UINT8       ucAirMsgId,
                                                NAS_MSG_STRU                          *pstNasMsg);
extern  VOS_VOID    NAS_LMM_FindAirMsgId(        VOS_UINT8 ucCnMsgType,
                                                VOS_UINT8 *ucAirMsg,
                                                VOS_UINT8 *ucKeyEvent);
/*extern  VOS_VOID    NAS_LMM_PubmDaSendSetCnf(
                                            VOS_UINT32                             ulRslt,
                                             const NAS_LMM_APP_PARA_STRU           *pAppPara);*/
VOS_VOID    NAS_LMM_PubmDaSendSetCnf( const NAS_LMM_APP_PARA_SET_RESLT_STRU *pstAppRslt);
extern  VOS_VOID NAS_EMM_SendIntraTauReq
(
    APP_MM_MSG_TYPE_ENUM_UINT32         ulOmMmMsgType,
    NAS_LMM_INTRA_TAU_TYPE_ENUM_UINT32  enIntraTauType
);

extern VOS_VOID    NAS_LMM_PubmGetAreaInfo
       (
           APP_GUTI_STRU                       *pstGuti,
           APP_TA_LIST_STRU                    *pstTaiList,
           APP_TA_STRU                         *pstLastTa
       );
extern VOS_VOID    NAS_LMM_PubmGetEmmInfo
       (
           APP_EMM_INFO_STRU                   *pstEmmInfoCnf
       );
extern VOS_VOID    NAS_LMM_PubmGetEmmState
       (
           APP_EMM_MAIN_STATE_ENUM_UINT16      *pulProtoclMainState,
           APP_EMM_SUB_STATE_ENUM_UINT16       *pulProtoclSubState,
           NAS_LMM_MAIN_STATE_ENUM_UINT16      enMainState,
           NAS_LMM_SUB_STATE_ENUM_UINT16       enSubState

       );
extern VOS_VOID    NAS_LMM_PubmGetEmmUpdateState
       (
           APP_EMM_UPDATE_STATE_ENUM_UINT32    *pulEmmUpState
       );
extern VOS_VOID    NAS_LMM_PubmIndEmmInfo(VOS_VOID);
extern VOS_UINT32  NAS_LMM_CheckAppDrxParam( CONST APP_DRX_STRU *pstAppDrxParam );
extern VOS_UINT32  NAS_LMM_IsDrxSplitOnCcchValid( VOS_UINT8 ucSplitOnCcch );
extern VOS_UINT32  NAS_LMM_IsDrxNonDrxTimerValid( VOS_UINT8 ucNonDrxTimer );
extern VOS_UINT32  NAS_LMM_IsDrxPgCycleCodeValid( VOS_UINT8 ucSplitPgCode );
extern VOS_UINT32  NAS_LMM_IsUeDrxCycleValid( VOS_UINT8 ucPsDrxLen );

/*PC REPLAY MODIFY BY LEILI DELETE*/
extern VOS_VOID     NAS_LMM_OmInfoIndProc(VOS_VOID);
extern VOS_VOID     NAS_LMM_FtmInfoInit(VOS_VOID);
extern VOS_UINT32   NAS_LMM_RevOmFtmCtrlMsg(MsgBlock   *pMsgStru);
extern VOS_UINT32   NAS_LMM_CompareEmmDatabaseInfo(VOS_VOID);
extern VOS_VOID     NAS_LMM_UpdateEmmDatabaseInfo(VOS_VOID);
extern VOS_VOID     NAS_LMM_SendOmFtmMsg(VOS_VOID);

/* niuxiufan DT begin */
extern VOS_VOID  NAS_LMM_PubmDaInqGuti(MsgBlock *pMsg);
extern VOS_VOID  NAS_LMM_PubmDaInqImsi(MsgBlock *pMsg);
extern VOS_VOID  NAS_LMM_PubmDaInqEmmState(MsgBlock *pMsg);
extern VOS_VOID  NAS_LMM_PubmIndGuti(VOS_VOID);
extern VOS_VOID  NAS_LMM_PubmIndImsi(VOS_VOID);
extern VOS_VOID  NAS_LMM_PubmIndEmmState(VOS_VOID);
/* niuxiufan DT end */

extern VOS_VOID NAS_LMM_DtJudgeifNeedRpt(VOS_VOID);
extern VOS_UINT32 NAS_LMM_DtCompareGuti(VOS_VOID);
extern VOS_UINT32 NAS_LMM_DtCompareImsi(VOS_VOID);
extern VOS_UINT32 NAS_LMM_DtCompareEmmState(VOS_VOID);
extern VOS_VOID NAS_LMM_DtJudgeifNeedRpt(VOS_VOID);
extern NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmCommFindFun
(
    const NAS_LMM_OM_ACT_STRU           *aucActMap,
    VOS_UINT32                          ulMapElementNum,
    VOS_UINT32                          ulMsgId
);
extern VOS_VOID  NAS_LMM_ReadImsaNvImsCapability( VOS_UINT8 *pucSmsOverIms, VOS_UINT8 *pucSrvcc);


extern VOS_UINT32 NAS_LMM_RevOmErrlogCtrlMsg(MsgBlock   *pMsgStru);


extern VOS_UINT32 NAS_EMM_GetErrLogRingBufUseBytes(VOS_VOID);
extern VOS_UINT32 NAS_EMM_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_VOID NAS_EMM_CleanErrLogRingBuf(VOS_VOID);
extern VOS_UINT16 NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId);
extern VOS_VOID NAS_EMM_SndAcpuOmErrLogReportCnf(
 VOS_CHAR                           *pbuffer,
 VOS_UINT32                          ulBufUseLen
);
extern VOS_UINT32   NAS_LMM_RevOmReadErrlogReq(MsgBlock   *pMsgStru);
extern VOS_UINT32 NAS_EMM_IsErrLogNeedRecord(VOS_UINT16 usLevel);
extern EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16  NAS_LMM_CnCauseProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucCnCause);
extern VOS_UINT32 NAS_EMM_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_VOID NAS_EMM_PrintErrlogHeader(LNAS_OM_ERR_LOG_HEADER_STRU *pstHeader);
extern VOS_VOID NAS_EMM_AttachErrRecord(
         VOS_VOID*                         pstAttachFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType);
extern VOS_VOID NAS_EMM_TAUErrRecord(
         VOS_VOID*                         pstTAUFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType);
extern   VOS_VOID NAS_LMM_RevNvCtrl(VOS_VOID);
extern VOS_UINT32 NAS_LMM_ExportEmmInfoExcLog(VOS_UINT32* pulExcLogAddr, VOS_UINT32 *pulLeftSpace);
extern VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType);
extern VOS_VOID NAS_EMM_AuthCnFailErrRecord(
        EMM_OM_ERRLOG_AUTH_FAIL_ENUM_UINT16       enErrAuthFail);

extern VOS_VOID  NAS_LMM_SndOmDamPara(VOS_VOID);
extern VOS_VOID  NAS_LMM_SndOmCommConfigPara
(
    LNAS_LMM_NV_COMM_CONFIG_PARA_STRU   *pstNvCommPara
);
extern VOS_VOID  NAS_LMM_SndOmRej19Cnt(VOS_VOID);


VOS_VOID  NAS_LMM_SndOmSetTmoActiveFlag(VOS_UINT32 ulTmoActiveFlagStatus);
extern VOS_UINT32 NAS_LMM_AddAttachTotalCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachSuccCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachBarFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachNoRfFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachEstFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachExpFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachRejFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachRelFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachEsmFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachDataReqFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddAttachOtherFailCounter(VOS_VOID);
extern VOS_VOID NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16  enCounterType);
extern VOS_VOID NAS_LMM_SaveAttachStartTimeStamp(VOS_VOID);
extern VOS_VOID NAS_LMM_SaveAttachReqSndTimeStamp(VOS_VOID);
extern VOS_VOID NAS_LMM_SaveAttachEstSuccTimeStamp(VOS_VOID);
extern VOS_VOID NAS_LMM_SaveAttachAcpTimeStamp(VOS_VOID);
extern VOS_VOID NAS_LMM_SaveAttachCmpSndTimeStamp(VOS_VOID);
extern VOS_VOID NAS_LMM_SaveAttachEndTimeStamp(VOS_VOID);
extern VOS_UINT32 NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauTotalCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauSuccCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauBarFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauNoRfFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauEstFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauExpFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauRejFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauRelFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauDataReqFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddTauOtherFailCounter(VOS_VOID);
extern VOS_VOID NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16   enCounterType);
extern VOS_UINT32 NAS_LMM_AddSerTotalCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerSuccCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerBarFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerNoRfFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerOtherEstFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerExpFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerRejFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerRelFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerDataReqFailCounter(VOS_VOID);
extern VOS_UINT32 NAS_LMM_AddSerOtherFailCounter(VOS_VOID);
extern VOS_VOID NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16   enCounterType);
extern VOS_VOID NAS_LMM_UpdateSerEstFailCounter(LRRC_LNAS_EST_RESULT_ENUM_UINT32   enEstResult);
extern VOS_VOID NAS_EMM_SaveSerReqSndTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMtSerStartTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMtSerReqSndTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMtSerEstSuccTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMtSerEndTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMoSerStartTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMoSerReqSndTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMoSerEstSuccTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveMoSerEndTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveSerEstSuccTimeStamp(VOS_VOID);
extern VOS_VOID NAS_EMM_SaveSerEndTimeStamp(VOS_VOID);
extern VOS_UINT32 NAS_LMM_CalcDelayLen(VOS_UINT32 ulTimeStampBegin, VOS_UINT32 ulTimeStampEnd);
extern VOS_VOID  NAS_LMM_SndOmAttSuccRatioInfo(VOS_VOID);
extern VOS_VOID  NAS_LMM_SndOmTauSuccRatioInfo(VOS_VOID);
extern VOS_VOID  NAS_LMM_SndOmSerSuccRatioInfo(VOS_VOID);
extern VOS_VOID  NAS_LMM_SndOmAttachDelayInfo(VOS_VOID);
extern VOS_VOID  NAS_LMM_SndOmServiceDelayInfo(VOS_UINT32 ulIsMtService);
extern VOS_VOID NAS_EMM_SaveRecvMsgList(VOS_VOID *pMsg);
extern VOS_VOID NAS_EMM_SavePreEmmState(VOS_VOID);
extern VOS_UINT32 NAS_EMM_ExportMsgInfoExcLog(VOS_UINT8* pulExcLogAddr, VOS_UINT32 *pulLeftSize);
extern VOS_VOID NAS_LMM_SndOmTauStartTypeInfo(NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType);
extern VOS_VOID  NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_ENUM_UINT32 enSerStartType);
extern VOS_VOID  NAS_LMM_SndOmAnyCellJudgingInfo
(
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType,
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulPlmnCtrl,
    const   NAS_MM_TA_STRU             *pstTa
);

extern VOS_VOID  NAS_LMM_SndOmStaticUeIdInfo(VOS_VOID);
extern VOS_VOID  NAS_LMM_SndOmConnstateInfo(NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucConnstate);


extern VOS_VOID NAS_EMM_SndOmGradualForbParaLog(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU  stNvGradualForbPara);
extern VOS_VOID NAS_EMM_SndOmGradualForbTaInfo(NAS_MM_TA_STRU *pstOperaTa,
                                                        NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ENUM_UINT8 enOperaType);

extern VOS_VOID NAS_LMM_SndOmRegDomainInfo(NAS_LMM_REG_DOMAIN_ENUM_UINT32  enRegDomainCur,
                                                        NAS_LMM_REG_DOMAIN_ENUM_UINT32   enRegDomainDst);
extern VOS_VOID  NAS_LMM_SndOmImsiRefreshStatus(VOS_UINT8   ucImsiRefreshStatusFlag);

extern VOS_VOID  NAS_EMM_TAU_StartTauForInterRat
(
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8 ucTauStartCause,
    NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 ulTauStartType
);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMOm.h*/
