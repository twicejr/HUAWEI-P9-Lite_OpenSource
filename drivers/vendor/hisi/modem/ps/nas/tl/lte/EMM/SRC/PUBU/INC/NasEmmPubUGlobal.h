/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmPubUGlobal.h
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact
      2.  hanlufeng 41410  2009-03-11  BA8D01164 增加对EMM INFO处理的接口
******************************************************************************/

#ifndef _NASEMMPUBUGLOBAL_H
#define _NASEMMPUBUGLOBAL_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPublic.h"
#include    "NasLmmPubMFsm.h"
#include    "NasLmmCore.h"
#include    "NasCommPrint.h"
#include    "Msp_diag_cmd_id.h"
#include    "MmcLmmInterface.h"
#include    "NasMmlCtx.h"
#include    "NasMmlLib.h"
#include    "MmLmmInterface.h"
#include    "OmEmmInterface.h"


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
typedef VOS_UINT32                      NAS_EMM_FFS_UINT32;
typedef VOS_UINT32                      NAS_EMM_FFS;

#define NAS_EMM_OK                      VOS_OK
#define NAS_EMM_NULL_PTR                VOS_NULL_PTR

#define NAS_EMM_MAX_PLMN_NUM            15
#define NAS_EMM_MAX_EQU_PLMN_NUM        15

#define NAS_EMM_PUB_WAIT_MRRC_REL_CNF   10000

#define NAS_EMM_SUCC                    VOS_OK
#define NAS_EMM_FAIL                    VOS_ERR

#define NAS_EMM_GO_INTO_EMM_FSM         0
#define NAS_EMM_NOT_GO_INTO_EMM_FSM     1

#define NAS_EMM_PARA_VALID              1
#define NAS_EMM_PARA_INVALID            0

#define AUTO_START                      1
#define NOT_AUTO_START                  0

#define NAS_EMM_NOT_DELETE_RPLMN        0
#define NAS_EMM_DELETE_RPLMN            1
#define NAS_EMM_TRANSFER_RAT_ALLOW      0
#define NAS_EMM_TRANSFER_RAT_NOT_ALLOW  1
#define NAS_RELEASE_R10                 (0x00000a00 <= NAS_LMM_GetNasRelease())
#define NAS_RELEASE_R11                 (0x00000b00 <= NAS_LMM_GetNasRelease())
#define NAS_RELEASE_CTRL                NAS_RELEASE_R10
#define NAS_EMM_AUTO_ATTACH_ALLOW       VOS_TRUE/*UE可以自动发起ATTACH*/
#define NAS_EMM_AUTO_ATTACH_NOT_ALLOW   VOS_FALSE /*UE响应了APP_DETACH，不允许自动发起ATTACH*/

#define NAS_EMM_BIT_SLCT                1
#define NAS_EMM_BIT_NO_SLCT             0

#define NAS_EMM_STATE_VALID             1
#define NAS_EMM_STATE_INVALID           0

#define NAS_EMM_MOVEMENT_1_BYTE         1
#define NAS_EMM_MOVEMENT_3_BYTE         3
#define NAS_EMM_MOVEMENT_4_BYTE         4
#define NAS_EMM_ZONE_TIME_LEN           7

#define NAS_EMM_MOVEMENT_2_BITS         2
#define NAS_EMM_MOVEMENT_3_BITS         3
#define NAS_EMM_MOVEMENT_4_BITS         4
#define NAS_EMM_MOVEMENT_8_BITS         8
#define NAS_EMM_MOVEMENT_16_BITS        16
#define NAS_EMM_MOVEMENT_24_BITS        24

#define NAS_EMM_OPT_FILE_MASK           0x80

#define NAS_EMM_OPID_TYPE_ATTACH_IND    DIAG_CMD_MM_ATTACH_IND
#define NAS_EMM_OPID_TYPE_DETACH_IND    DIAG_CMD_MM_DETACH_IND


#define EMM_CN_MSG_PDMASK               0x0F

#define EMM_CN_MSG_PD_EMM               0x07                /* 0111   EPS mobility management messages */
#define EMM_CN_MSG_PD_ESM               0x02                /* 0010   EPS session management messages */
#define EMM_CN_MSG_PD_TC                0x0F                /* 1111   Test Control messages */


#define NAS_EMM_PLMNACT_IDEN            3
#define NAS_EMM_PLMNACT_LTE             0x40                /* 0100  0000  */

#define NAS_EMM_VOS_HEADER_LEN          20
#define NAS_EMM_MSG_ID_LEN              4
#define NAS_EMM_4BYTES_LEN              4

#define NAS_EMM_PLAIN_MSG_TYPE_POS      1

#define NAS_EMM_BIT_1                   0x01
#define NAS_EMM_BIT_2                   0x02
#define NAS_EMM_BIT_3                   0x04
#define NAS_EMM_BIT_4                   0x08
#define NAS_EMM_BIT_4_5                 0x18



#define NAS_EMM_STACK_EMPTY             NAS_LMM_STACK_EMPTY
#define NAS_EMM_MSG_BUF_EMPTY           NAS_LMM_MSG_BUF_EMPTY

#define NAS_EMMC_STACK_EMPTY             NAS_LMM_STACK_EMPTY
#define NAS_EMMC_MSG_BUF_EMPTY           NAS_LMM_MSG_BUF_EMPTY

#define NAS_EMM_MSG_BUF_HEAD_INIT       NAS_LMM_MSG_BUF_HEAD_INIT
#define NAS_EMM_MSG_BUF_TAIL_INIT       NAS_LMM_MSG_BUF_TAIL_INIT

#define NAS_EMMC_MSG_BUF_HEAD_INIT       NAS_LMM_MSG_BUF_HEAD_INIT
#define NAS_EMMC_MSG_BUF_TAIL_INIT       NAS_LMM_MSG_BUF_TAIL_INIT

/*DRX Param*/
/*SPLIT PG CYCLE CODE*/
#define NAS_LMM_MAX_SPLIT_PG_CYCLE_CODE  98
#define NAS_LMM_SPLIT_PG_CYCLE_CODE_ONE  1

/*UE SPEC DRX VALUE*/
#define NAS_LMM_UE_SPEC_DRX_VALUE_NUM    5
#define NAS_LMM_UE_NOT_SPEC_DRX_VALUE    0

/*SPLIT on CCCH*/
#define NAS_LMM_SPLIT_ON_CCCH_NOT_SUPPORT    0
#define NAS_LMM_SPLIT_ON_CCCH_SUPPORT        1

/*non-DRX Timer*/
#define NAS_LMM_NO_NONE_DRX_MODE         0
#define NAS_LMM_MAX_NON_DRX_TIMER        7

/* 给MMC发送消息时的OPID */
#define NAS_EMM_OPID_MMC                0

/* 给MM发送消息时的OPID */
#define NAS_EMM_OPID_MM                 0

/* UE的GU能力未发生变化*/
#define NAS_EMM_UE_GU_RADIO_CAP_NOT_CHG    0X00

/* UE的LTE能力未发生变化 */
#define NAS_EMM_UE_LTE_RADIO_CAP_NOT_CHG   0X00

/* UE的HRPD能力未发生变化*/
#define NAS_EMM_UE_HRPD_RADIO_CAP_NOT_CHG  0X00

/*sunbing 49683 2013-10-21 VoLTE begin*/
/* codec相关定义参考GU NAS的实现，对应的宏定义为MN_CALL(替代下面宏的NAS_EMM) */
/*  当前支持的UMTS的codec类型仅存在3种,但协议中还有扩展，因此此处预留扩展的字段 */
#define NAS_EMM_MAX_UMTS_CODEC_TYPE_NUM     (7)

#define NAS_EMM_BC_MAX_SPH_VER_NUM          (6)


#define NAS_EMM_UMTS_CODEC_TYPE_AMR         (5)
#define NAS_EMM_UMTS_CODEC_TYPE_AMR2        (6)
#define NAS_EMM_UMTS_CODEC_TYPE_AMRWB       (10)

#define NAS_EMM_BC_VAL_SPH_VER_FR_1     0
#define NAS_EMM_BC_VAL_SPH_VER_FR_2     2
#define NAS_EMM_BC_VAL_SPH_VER_FR_3     4
#define NAS_EMM_BC_VAL_SPH_VER_HR_1     1
#define NAS_EMM_BC_VAL_SPH_VER_HR_3     5
#define NAS_EMM_BC_VAL_SPH_VER_FR_5     8

/*sunbing 49683 2013-10-21 VoLTE end*/

/*来自MMC/GMM/MM/ESM的消息类型最多为30个*/
#define NAS_EMM_INPUT_DSDS_MSG_NUM      30

/*****************************************************************************
   各种 UE ID 存放的最大字节数目,包括LENTH字节:
   The IMSI shall not exceed 15 digits, ie 7 and a half of bytes;
   the TMSI/P-TMSI is 4 octets long;
   the IMEI is composed of 15 digits;
   the IMEISV is 16 digits;
******************************************************************************/
#define NAS_EMM_MAX_UEID_BUF_SIZE       10                  /* UNIT: BYTE  */
#define NAS_EMM_MS_NET_CAP_MAX_SIZE     9                   /* UNIT: BYTE  */

#define NAS_EMM_MAX_CIPHER_KEY_LEN      16                  /* 加密密钥长度 */
#define NAS_EMM_MAX_INTEGRITY_KEY_LEN   16                  /* 完整性保护密钥长度 */
#define NAS_EMM_MAX_RAB_SETUP_NUM       11                  /* 建立的最大RAB数  */
#define NAS_EMM_MIN_EPS_ID              5                   /* 最小的EPS ID*/
#define EMM_CN_MSG_UE_ID_EVEN           0x00                /* 0000  0000   even number of identity digits */
#define EMM_CN_MSG_UE_ID_ODD            0x08                /* 0000  1000   odd  number of identity digits */


#define NAS_EMM_HIGH_HALF_BYTE_F        0xF0                /* 1111  0000  */
#define NAS_EMM_LOW_HALF_BYTE_F         0x0F                /* 0000  1111  */
#define NAS_EMM_LOW_3_BITS_F            0x07                /* 0000  0111  */
#define NAS_EMM_LOW_2_BITS_F            0x03                /* 0000  0011  */
#define NAS_EMM_FOURTH_BITS_F           0x08                /* 0000  1000  */

#define NAS_EMM_FIFTH_BITS_F            0x10                /* 0001  0000  */

#define NAS_EMM_HIGH_3_BITS_F           0x70                /* 0111  0000  */
#define NAS_EMM_6_BITS_F                0x7E                /* 0111  1110*/
#define NAS_EMM_7_BITS_F                0x7f                /* 0111  1111  */
#define NAS_EMM_HIGHES_BIT              0x80                /* 1000  0000  */
#define NAS_EMM_HITH_2_BITS_F           0xc0                /* 1100  0000  */
#define NAS_EMM_LOW_1_BITS_F            0x01                /* 0000  0001 */
#define NAS_EMM_FIRST_BYTE_F            (0x000000FF)
#define NAS_EMM_SECOND_BYTE_F           (0x0000FF00)
#define NAS_EMM_THIRD_BYTE_F            (0x00FF0000)
#define NAS_EMM_LOW_3_BYTE_F            (0x00FFFFFF)


/*****************************************************************************/
/******************* 原因值的宏定义    ***************************************/
/*****************************************************************************/

#define  NAS_LMM_CAUSE_GPRS_NOT_SUPPORTED                    233
#define  NAS_LMM_CAUSE_T3310_EXPIRED                         234
#define  NAS_LMM_CAUSE_T3317_EXPIRED                         235
#define  NAS_LMM_CAUSE_T3321_EXPIRED                         236
#define  NAS_LMM_CAUSE_T3330_EXPIRED                         237
#define  NAS_LMM_CAUSE_AUTHENTICATION_FAILURE                238
#define  NAS_LMM_CAUSE_COVERAGE_LOST                         239
#define  NAS_LMM_CAUSE_UESR_DETACH                           240


#define  NAS_LMM_CAUSE_OTHER_CAUSE                           249             /* Other cause                              */

#define  NAS_LMM_CAUSE_PAGING_WITH_IMSI                      250             /* Paging with imsi                         */
#define  NAS_LMM_CAUSE_TIMER_TIMEOUT                         251             /* Timer timeout                            */
#define  NAS_LMM_CAUSE_RR_CONN_EST_FAIL                      252             /* RR connection establish failure          */
#define  NAS_LMM_CAUSE_RR_CONN_FAIL                          253             /* RR connection failure                    */
#define  NAS_LMM_CAUSE_ACCESS_BARRED                         254             /* access barred                            */
#define  NAS_LMM_CAUSE_UNSUITABLE_MODE                       255             /* Unsuitable mode                          */
#define  NAS_MAX_PUBLISHMENT_TIMER_LEN                       (12*60*60)      /*4G未开户定制特性下最大的惩罚定时器时长*/
#define  NAS_MAX_EXT_PUBLISHMENT_TIMER_LEN                   (8*60*60)       /*网络携带extCause场景下惩罚定时器的最大时长*/
#define  NAS_PUBLISHMENT_LEN_ONE_HOUR                        (1*60*60)       /*如果用户设置定时器时长为0，则默认设置为1个小时*/
#define  NAS_LMM_WITH_EXT_CAUSE                               1              /*网络带有扩展原因值*/
#define  NAS_LMM_WITHOUT_EXT_CAUSE                            0              /*网络没有带扩展原因值*/
#define  NAS_LMM_HAVE_REG_SUCC_ON_LTE                         1
#define  NAS_LMM_NO_REG_SUCC_ON_LTE                           0

#define  NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM                 16             /* 渐进FORB优化,临时FORB列表最大个数 */
#define  NAS_LMM_GRADUAL_FORB_REJ_FIRST                       1
#define  NAS_LMM_GRADUAL_FORB_REJ_SECOND                      2

#define NAS_EMM_UENETCAP_WITHOUT_LCS                          (0xFB)
#define NAS_EMM_UENETCAP_WITHOUT_LPP                          (0xF7)

/* 组合事件类型,低两字节有效: 0x0000_0x源PID_0x消息类型  */
#define EMM_EVENTTYPE_MASK_SPID         0x00FF0000
#define EMM_EVENTTYPE_MASK_MSGID        0x000000FF
typedef VOS_UINT32                      NAS_EMM_EVENTTYPE_UINT32;

typedef struct MsgCB                    NAS_EMM_MSG_STRU;




#define NAS_EMM_PUBU_LOG_INFO(String)           NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String)
#define NAS_EMM_PUBU_LOG_NORM(String)           NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String)
#define NAS_EMM_PUBU_LOG_WARN(String)           NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String)
#define NAS_EMM_PUBU_LOG_ERR(String)            NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String)

#define NAS_EMM_PUBU_LOG1_INFO(String, Para1)   NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String, Para1)
#define NAS_EMM_PUBU_LOG1_NORM(String, Para1)   NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String, Para1)
#define NAS_EMM_PUBU_LOG1_WARN(String, Para1)   NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String, Para1)
#define NAS_EMM_PUBU_LOG1_ERR(String,  Para1)   NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU,  String,  Para1)

#define NAS_EMM_PUBU_LOG2_INFO(String, Para1, Para2)   NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String, Para1, Para2)
#define NAS_EMM_PUBU_LOG2_NORM(String, Para1, Para2)   NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String, Para1, Para2)
#define NAS_EMM_PUBU_LOG2_WARN(String, Para1, Para2)   NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU, String, Para1, Para2)
#define NAS_EMM_PUBU_LOG2_ERR(String,  Para1, Para2)   NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_PUBU,  String,  Para1, Para2)



/* 计算EMM要发给XXX的消息长度, 不包含VOS头(外部消息) */
#define NAS_EMM_GET_MSG_LENGTH_NO_HEADER(XXX_EMM_MSG_STRU) \
                    (sizeof(XXX_EMM_MSG_STRU) - VOS_MSG_HEAD_LENGTH)


/* 打包EMM内部消息头 */
#define NAS_EMM_INTRA_MSG_HEADER(pMsg, ulLen) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_MM;\
            (pMsg)->ulLength            = ulLen;\
        }

/* Set Vos Header */
#define NAS_EMM_SET_RRC_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ERRC;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

#define NAS_EMM_IF_RETURN_RESULT_ERR_PRINT(iRslt,ErrorInformation)\
        {\
            if(VOS_OK!=iRslt)\
            {\
                NAS_LMM_PUBM_LOG1_ERR(ErrorInformation,iRslt);\
            }\
        }

#define EMM_PUBU_COMP_MMC_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = WUEPS_PID_MMC;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
       }

#define EMM_PUBU_COMP_MM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = WUEPS_PID_MM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
       }
/*lihong 2013-7-11 VoLTE begin*/
#define EMM_PUBU_COMP_GMM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = WUEPS_PID_GMM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
       }
/*lihong 2013-7-11 VoLTE end*/

#define EMM_PUBU_COMP_ESM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ESM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
        }

#define EMM_PUBU_COMP_ERABM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_RABM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
       }

/*封装写USIM消息头的宏*/
/*USIM的消息头都被统一封装在了MsgHeader中*/
#define NAS_EMM_USIM_MSG_HEAD(pstMsg, ulMsgID, enApptype, ulSendpara)\
                    (pstMsg)->stMsgHeader.enMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_MM;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.enAppType = (enApptype);\
                    (pstMsg)->stMsgHeader.ulSendPara = (ulSendpara);\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_USIM;
#define NAS_EMM_SET_MTA_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = UEPS_PID_MTA;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }


/*#define NAS_LMM_GetUsimFeature()                NAS_EMM_CheckUsimFeature()*/
/*****************************************************************************
数据:   下述大量对 g_stEmmInfo 封装的宏定义;
功能:   提供 对EMM的数据  NAS_LMM_PUB_INFO_STRU g_stEmmInfo 操作的接口，
        EMM的各子模块要对该数据操作，调用此处提供的接口，而不直接对全局写代码
*****************************************************************************/

/* 获取EMMINFO的地址 */
#define NAS_LMM_GetEmmInfoAddr()                     (&g_stEmmInfo)

/* 获取EMMINFO的各项成员的地址 */
#define NAS_LMM_GetEmmInfoUeidAddr()                 (&((NAS_LMM_GetEmmInfoAddr())->stMmUeId))        /* 获取EMMINFO的UEID地址 */
#define NAS_LMM_GetEmmInfoNetInfoAddr()              (&((NAS_LMM_GetEmmInfoAddr())->stNetInfo))       /* 获取EMMINFO的stNetInfo地址 */
#define NAS_LMM_GetEmmInfoMsNetCapAddr()             (&((NAS_LMM_GetEmmInfoAddr())->stMsNetCap))
#define NAS_LMM_GetEmmInfoMsClassMarkAddr()          (&((NAS_LMM_GetEmmInfoAddr())->stMsClassMark))
#define NAS_LMM_GetEmmInfoSupCodecListAddr()         (&((NAS_LMM_GetEmmInfoAddr())->stSupCodecList))
#define NAS_LMM_GetEmmInfoNasEmmInfoListAddr()       (&((NAS_LMM_GetEmmInfoAddr())->stEmmInfoPara))
/*#define NAS_LMM_GetEmmInfoNasSerTableAddr()          (&((NAS_LMM_GetEmmInfoAddr())->stEmmSrvInfo))*/
#define NAS_LMM_GetEmmInfoUsimStatusAddr()           (&((NAS_LMM_GetEmmInfoAddr())->ulSimStat))
#define NAS_LMM_GetEmmStartInfoAddr()                (&((NAS_LMM_GetEmmInfoAddr())->stEmmStartInfo))
#define NAS_LMM_GetEmmInfoTriggerTauFlagAddr()       (&((NAS_LMM_GetEmmInfoAddr())->stTriggerTauFlag))

#define NAS_LMM_GetEmmInfoSyscfgCtrlAddr()           (&((NAS_LMM_GetEmmInfoAddr())->stSyscfgCtrl))
#define NAS_LMM_SetEmmInfoSyscfgCtrl(SyscfgFlag)      ((NAS_LMM_GetEmmInfoSyscfgCtrlAddr())->enSyscfgFlag = (SyscfgFlag))
#define NAS_LMM_GetEmmInfoSyscfgCtrl()                ((NAS_LMM_GetEmmInfoSyscfgCtrlAddr())->enSyscfgFlag )
#define NAS_LMM_GetEmmInfoMmcAttachReason()                ((NAS_LMM_GetEmmInfoAddr())->enMmcAttachReason )
#define NAS_LMM_SetEmmInfoMmcAttachReason(enMmcAttachReason)                (NAS_LMM_GetEmmInfoMmcAttachReason() = (enMmcAttachReason))

#define NAS_LMM_GetEmmInfoLtePowerOffFlag()            ((NAS_LMM_GetEmmInfoAddr())-> ucLtePowerOffFlag)
#define NAS_LMM_SetEmmInfoLtePowerOffFlag(ucLtePowerOffFlag)  ((NAS_LMM_GetEmmInfoLtePowerOffFlag()) = (ucLtePowerOffFlag))

/* 获取 (NAS_LMM_PUB_INFO_STRU)g_stEmmInfo.
        (NAS_LMM_UEID_STRU)stMmUeId 的各项成员的地址 */
#define NAS_LMM_GetEmmInfoUeidImsiAddr()             (((NAS_LMM_GetEmmInfoUeidAddr())->aucImsi))
#define NAS_LMM_GetEmmInfoUeidImeiAddr()             (((NAS_LMM_GetEmmInfoUeidAddr())->aucImei))
#define NAS_LMM_GetEmmInfoUeidImeisvAddr()           (((NAS_LMM_GetEmmInfoUeidAddr())->aucImeisv))
#define NAS_LMM_GetEmmInfoUeidPtmsiAddr()            (((NAS_LMM_GetEmmInfoUeidAddr())->aucPtmsi))
#define NAS_LMM_GetEmmInfoUeidTmgiAddr()             (&((NAS_LMM_GetEmmInfoUeidAddr())->stTmgiMbms))
#define NAS_LMM_GetEmmInfoUeidGutiAddr()             (&((NAS_LMM_GetEmmInfoUeidAddr())->stGuti))

#define NAS_LMM_GetEmmInfoUeidImsiMncLenAddr()           (&((NAS_LMM_GetEmmInfoUeidAddr())->ulImsiMncLen))


/* 获取(NAS_LMM_PUB_INFO_STRU)g_stEmmInfo.()stNetInfo的各项成员的地址 */
#define NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr()    (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stLastRegNetId))
#define NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()    (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stPresentNetId))
#define NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr()    (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stLastAttmpRegTa))

#define NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr()     ((NAS_LMM_GetEmmInfoNetInfoAddr())->bitOpEPlmnList)

#define NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()     (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stEPlmnList))
#define NAS_LMM_GetEmmInfoNetInfoTaiListAddr()       (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stTaiList))
#define NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr() (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stForbTaForRoam))
#define NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr() (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stForbTaForRpos))
#define NAS_LMM_GetEmmInfoNetInfoForbTaForRej15Addr() (&((NAS_LMM_GetEmmInfoNetInfoAddr())->stForbTaForRej15))
#define NAS_LMM_GetEmmInfoPresentPlmnAddr()          (&(NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->stPlmnId))
#define NAS_LMM_GetEmmInfoPresentTacAddr()           (&(NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->stTac))
#define NAS_LMM_GetEmmInfoLastAttmpRegPlmnAddr()          (&(NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr()->stPlmnId))
#define NAS_LMM_GetEmmInfoLastRegPlmnAddr()          (&(NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr()->stPlmnId))
#define NAS_LMM_GetEmmInfoOpLastRegPlmn()          (NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr()->bitOpPlmnId)

#define NAS_LMM_GetEmmInfoLastRegTacAddr()           (&(NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr()->stTac))
#define NAS_LMM_GetEmmInfoNetInfoLastAttmpRegCsgInfoAddr()    (&(NAS_LMM_GetEmmInfoNetInfoAddr()->stLastAttmpRegCsgInfo))

#define NAS_LMM_GetEmmInfoHplmnAddr()                (&(NAS_LMM_GetEmmInfoNetInfoAddr()->stHplmn))


#define NAS_LMM_GetEmmInfoLastWriteUsimPsLocAddr()     (&(NAS_LMM_GetEmmInfoAddr())->aucLastWriteUsimPsLoc[0])



/* 获取EMMINFO的UE_NET_CAP的地址 */
#define NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr()     (&((NAS_LMM_GetEmmInfoAddr())->stUeNetCap))

#define NAS_LMM_GetEmmInfoRaMod()                    (NAS_LMM_GetEmmInfoAddr()->enRaMod)

#define NAS_LMM_GetEmmInfoCcoFlagAddr()               (&((NAS_LMM_GetEmmInfoAddr())->stCcoFlag))
#define NAS_LMM_GetTempEmmInfoTinType()               (NAS_LMM_GetEmmInfoCcoFlagAddr()->ulTinType)
#define NAS_LMM_SetTempEmmInfoTinType(ulTinType)      (NAS_LMM_GetTempEmmInfoTinType()= ulTinType)
#define NAS_LMM_GetEmmInfoTinChagFlag()              (NAS_LMM_GetEmmInfoCcoFlagAddr()->ulTinChagFlag)
#define NAS_LMM_SetEmmInfoTinChagFlag(ulTinChag)     (NAS_LMM_GetEmmInfoTinChagFlag()= ulTinChag)


/*获取service table表信息*/
/*#define NAS_LMM_GetEmmInfoSrvInfoAddr()              (&((NAS_LMM_GetEmmInfoAddr())->stEmmSrvInfo))*/

#define NAS_LMM_GetSimState()                        ((NAS_LMM_GetEmmInfoAddr())->ulSimStat)

#define NAS_LMM_GetPsSimValidity()                   ((NAS_LMM_GetEmmInfoAddr())->enPsSimValidity)
#define NAS_LMM_SetPsSimValidity(enPsSimValidity)    (NAS_LMM_GetPsSimValidity() = (enPsSimValidity))


#define NAS_LMM_GetNasRelease()                     ((NAS_LMM_GetEmmInfoAddr())->ulNasRelease)
#define NAS_LMM_SetNasRelese(ulNasRelease)          (NAS_LMM_GetNasRelease() = (ulNasRelease))

#define NAS_LMM_GetT3402Src()                       ((NAS_LMM_GetEmmInfoAddr())->enT3402Src)
#define NAS_LMM_SetT3402Src(enT3402Src)                       (NAS_LMM_GetT3402Src() = enT3402Src)


#define NAS_LMM_GetMsgIsIntegrityFlag()                     ((NAS_LMM_GetEmmInfoAddr())->ucIsMsgIntegrityFlag)
#define NAS_LMM_SetMsgIsIntegrityFlag(ucIsMsgIntegrityFlag)          (NAS_LMM_GetMsgIsIntegrityFlag() = (ucIsMsgIntegrityFlag))



/*UE MODE OF OPERATION*//* h41410 for ue mode begin */
/*#define NAS_LMM_GetEmmInfoGuUeMode()                ((NAS_LMM_GetEmmInfoAddr())->ulGuUeMode)*/
/*#define NAS_LMM_SetEmmInfoGuUeMode(UeMode)          (NAS_LMM_GetEmmInfoGuUeMode() = (UeMode))*/
#define NAS_LMM_SetEmmInfoGuUeMode(UeMode)          ((NAS_LMM_GetEmmInfoAddr())->ulGuUeMode = (UeMode))


/*#define NAS_LMM_GetEmmInfoUeOperationMode()         ((NAS_LMM_GetEmmInfoAddr())->ulLteUeMode)*/
#define NAS_LMM_SetEmmInfoUeOperationMode(UeMode)   (((NAS_LMM_GetEmmInfoAddr())->ulLteUeMode) = (UeMode))
#define NAS_LMM_GetEmmInfoUeCenter()                ((NAS_LMM_GetEmmInfoAddr())->ulUsageSetting)
#define NAS_LMM_SetEmmInfoUeCenter(UeCenter)        (NAS_LMM_GetEmmInfoUeCenter() = UeCenter)

/* h41410 for ue mode end */

/*CS SERVICE*/
#define NAS_LMM_GetEmmInfoCsService()               ((NAS_LMM_GetEmmInfoAddr())->ulCsService)
#define NAS_LMM_SetEmmInfoCsService(CsService)      (((NAS_LMM_GetEmmInfoAddr())->ulCsService) = (CsService))

/*VOICE DOMAIN*/
#define NAS_LMM_GetEmmInfoVoiceDomain()             ((NAS_LMM_GetEmmInfoAddr())->ulVoiceDomain)
#define NAS_LMM_SetEmmInfoVoiceDomain(VoiceDomain)  (((NAS_LMM_GetEmmInfoAddr())->ulVoiceDomain) = (VoiceDomain))

/*EMERGENCY LIST*/
#define NAS_LMM_GetEmmInfoEmergencyListAddr()        (&((NAS_LMM_GetEmmInfoAddr())->stEmergencyNumList))

/* 把注册域获取和设置改成函数 */


#define NAS_LMM_GetEmmInfoLauOrComRauFlag()                     ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enLauOrCombinedRauFlag)
#define NAS_LMM_SetEmmInfoLauOrComRauFlag(LauOrComRauFlag)      (NAS_LMM_GetEmmInfoLauOrComRauFlag() = (LauOrComRauFlag))
#define NAS_LMM_GetEmmInfoSrvccFlag()                     ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enSrvccFlag)
#define NAS_LMM_SetEmmInfoSrvccFlag(enSrvccFlag)      (NAS_LMM_GetEmmInfoSrvccFlag() = (enSrvccFlag))

#define NAS_LMM_GetEmmInfoLaiChangeFlag()                     ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->ucLaiChangeFlag)
#define NAS_LMM_SetEmmInfoLaiChangeFlag(ucLaiChangeFlag)      (NAS_LMM_GetEmmInfoLaiChangeFlag() = (ucLaiChangeFlag))

#define NAS_LMM_GetEmmInfoCsEmcConneExitFlag()                     ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->ucEmcConnExitFlag)
#define NAS_LMM_SetEmmInfoCsEmcConneExitFlag(ucEmcConnExitFlag)      (NAS_LMM_GetEmmInfoCsEmcConneExitFlag() = (ucEmcConnExitFlag))



#define NAS_LMM_GetEmmInfoFirstTauFlag()               ((NAS_LMM_GetEmmInfoAddr())->enFirstTauFlag)
#define NAS_LMM_SetEmmInfoFirstTauFlag(FirstTauFlag)   (((NAS_LMM_GetEmmInfoAddr())->enFirstTauFlag) = (FirstTauFlag))

#define NAS_LMM_GetEmmInfoGConnState()                 ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enGprsMmState)
#define NAS_LMM_SetEmmInfoGConnState(GConnState)       (NAS_LMM_GetEmmInfoGConnState()  = (GConnState))

#define NAS_LMM_GetEmmInfoUConnState()                 ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enPacketMmState)
#define NAS_LMM_SetEmmInfoUConnState(UConnState)       ( NAS_LMM_GetEmmInfoUConnState() = (UConnState))


#define NAS_LMM_GetEmmInfoPsState()                    ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enGprsSuspensionState)
#define NAS_LMM_SetEmmInfoPsState(PsState)             (NAS_LMM_GetEmmInfoPsState() = (PsState))


#define NAS_LMM_GetEmmInfoRejRecordAddr()              (&((NAS_LMM_GetEmmInfoAddr())->stRejRecord))
#define NAS_LMM_GetEmmInfoRejCause2Flag()              ((NAS_LMM_GetEmmInfoRejRecordAddr())->enRejCause2Flag)
#define NAS_LMM_SetEmmInfoRejCause2Flag(enRejCau2Falg) ((NAS_LMM_GetEmmInfoRejCause2Flag()) = enRejCau2Falg)

/*#define NAS_LMM_GetEmmInfoUpdateMmFlag()               ((NAS_LMM_GetEmmInfoAddr())->enUpdateMmFlag)
#define NAS_LMM_SetEmmInfoUpdateMmFlag(enUpdateMmFlag) ((NAS_LMM_GetEmmInfoUpdateMmFlag()) = (enUpdateMmFlag))*/
#define NAS_LMM_GetEmmInfoT3412ExpCtrl()                     ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enEmmT3412ExpCtrl)
#define NAS_LMM_SetEmmInfoT3412ExpCtrl(enEmmT3412ExpCtrl)    ((NAS_LMM_GetEmmInfoT3412ExpCtrl()) = (enEmmT3412ExpCtrl))

#define NAS_LMM_GetEmmInfoDrxNetCapChange()                     ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->ulEmmDrxNetCapChange)
#define NAS_LMM_SetEmmInfoDrxNetCapChange(ulEmmDrxNetCapChange) ((NAS_LMM_GetEmmInfoDrxNetCapChange()) = (ulEmmDrxNetCapChange))
#define NAS_LMM_GetEmmInfoTriggerTauRrcRel()                     ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enTriggerTauRrcRel)
#define NAS_LMM_SetEmmInfoTriggerTauRrcRel(enTriggerTauRrcRel)   ((NAS_LMM_GetEmmInfoTriggerTauRrcRel()) = (enTriggerTauRrcRel))
#define NAS_LMM_GetEmmInfoTriggerTauSysChange()                  ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->ulTriggerTauSysChange)
#define NAS_LMM_SetEmmInfoTriggerTauSysChange(enTriggerTauSysChange) ((NAS_LMM_GetEmmInfoTriggerTauSysChange()) = (enTriggerTauSysChange))
/*获取 EPS Bearer Context Stauts*/
#define NAS_EMM_GetEpsContextStatusChange()         ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enStatusChange)
#define NAS_EMM_SetEpsContextStatusChange(StatusChange)\
            (((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->enStatusChange) = (StatusChange))

#define NAS_EMM_GetDsdsTauType()                    ((NAS_LMM_GetEmmInfoAddr())->enDsdsTauType)
#define NAS_EMM_SetDsdsTauType(enDsdsTauType)             (NAS_EMM_GetDsdsTauType() = (enDsdsTauType))

/*leili moidfy for isr end*/

#define NAS_EMM_GetVoiceDomainChange()         ((NAS_LMM_GetEmmInfoTriggerTauFlagAddr())->ulVoiceDomainChange)
#define NAS_EMM_SetVoiceDomainChange(ulVoiceDomainChange) (NAS_EMM_GetVoiceDomainChange() = (ulVoiceDomainChange))


/* UE radio access capbility change flag */
#define NAS_LMM_GetEmmInfoSyscfgCtrlAddr()           (&((NAS_LMM_GetEmmInfoAddr())->stSyscfgCtrl))
#define NAS_LMM_SetEmmInfoSyscfgCtrl(SyscfgFlag)      ((NAS_LMM_GetEmmInfoSyscfgCtrlAddr())->enSyscfgFlag = (SyscfgFlag))
#define NAS_LMM_GetEmmInfoSyscfgCtrl()                ((NAS_LMM_GetEmmInfoSyscfgCtrlAddr())->enSyscfgFlag )
#define  NAS_LMM_GetEmmInfoUeRadioCapChgFlag()    ((NAS_LMM_GetEmmInfoSyscfgCtrlAddr())->enRadioAccCapChgFlag)
#define  NAS_LMM_SetEmmInfoUeRadioCapChgFlag(enRadioAccCap)     (((NAS_LMM_GetEmmInfoSyscfgCtrlAddr())->enRadioAccCapChgFlag) = (enRadioAccCap))
#define  NAS_LMM_GetEmmInfoUtranMode()              ((NAS_LMM_GetEmmInfoAddr()->enUtranMode))
#define  NAS_LMM_SetEmmInfoUtranMode(utranMode)              ((NAS_LMM_GetEmmInfoAddr()->enUtranMode) = (utranMode))

#define NAS_LMM_GetConnectionClientId()      ((NAS_LMM_GetEmmInfoAddr())->enNasConnectionClientId)
#define NAS_LMM_SetConnectionClientId(ConnectionClientId)      ((NAS_LMM_GetConnectionClientId())= (ConnectionClientId))

#define NAS_LMM_GetEmmInfoRegStatus()               ((NAS_LMM_GetEmmInfoAddr())->enRegStatus)
#define NAS_LMM_SetEmmInfoRegStatus(enRegStatus)    (NAS_LMM_GetEmmInfoRegStatus() = (enRegStatus))

#define NAS_LMM_GetEmmInfoIsEmerPndEsting()         ((NAS_LMM_GetEmmInfoAddr())->ulIsEmerPndEsting)
#define NAS_LMM_SetEmmInfoIsEmerPndEsting(ulIsEmerPndEsting)    (NAS_LMM_GetEmmInfoIsEmerPndEsting() = (ulIsEmerPndEsting))

#define NAS_LMM_GetEmmInfoEsmBuffAddr()             ((NAS_LMM_GetEmmInfoAddr())->pucEsmMsg)
#define NAS_EMM_GetEmmInfoT3312State()               ((NAS_LMM_GetEmmInfoAddr())->enT3312State)
#define NAS_EMM_SetEmmInfoT3312State(T3312State)     (NAS_EMM_GetEmmInfoT3312State() = (T3312State))

#define NAS_EMM_GetEmmInfoDamParaAddr()              (&((NAS_LMM_GetEmmInfoAddr())->stDamPara))
#define NAS_EMM_GetEmmInfoDamConfigPlmnParaAddr()    (&((NAS_EMM_GetEmmInfoDamParaAddr())->stDamConfigPlmnPara))
#define NAS_EMM_GetEmmInfoDamParaPlmnListAddr()      (&((NAS_EMM_GetEmmInfoDamConfigPlmnParaAddr())->stDamPlmnList))
#define NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr()  (&((NAS_EMM_GetEmmInfoDamConfigPlmnParaAddr())->stImsiPlmnList))
#define NAS_EMM_GetEmmInfoDamParaCserviceMax()       ((NAS_EMM_GetEmmInfoDamParaAddr())->ulCServiceMax)
#define NAS_EMM_GetEmmInfoDamParaCserviceCnt()       ((NAS_EMM_GetEmmInfoDamParaAddr())->ulCServiceCount)
#define NAS_EMM_GetEmmInfoDamParaT3402Len()          (NAS_EMM_GetEmmInfoDamParaAddr()->ulT3402Len)

#define NAS_EMM_GetEmmInfoRej19AtmptCntFlag()        (NAS_LMM_GetEmmInfoAddr()->ulRej19AtmptCntFlag)


#define NAS_EMM_GetEmmInfoTmoUsimCardFlag()        (NAS_LMM_GetEmmInfoAddr()->ucTmoUsimCardFlag)

/*最新发送的空口消息的类型*/
#define NAS_LMM_GetLastAirMsgType()                  (NAS_LMM_GetEmmInfoAddr()->enLastAirMsgType)

/*DRX Param*/
#define NAS_LMM_GetEmmInfoOpDrx()                    ((NAS_LMM_GetEmmInfoAddr())->bitOpDrx)
#define NAS_LMM_SetEmmInfoOpDrx(OpDrx)               (((NAS_LMM_GetEmmInfoAddr())->bitOpDrx) = (OpDrx))

#define NAS_LMM_GetEmmInfoDrxAddr()                  (&((NAS_LMM_GetEmmInfoAddr())->stDrx))
#define NAS_LMM_GetEmmInfoDrxCycleLen()              ((NAS_LMM_GetEmmInfoDrxAddr())->ucPsDrxLen)

/* del by leili for isr */


/* 获取开机信息 */
#define NAS_EMM_GetTransceiverType()                (NAS_LMM_GetEmmStartInfoAddr()->ulTransceiverType)
#define NAS_EMM_GetLteRatPrio()                     (NAS_LMM_GetEmmStartInfoAddr()->enLteRatPrio)
#define NAS_LMM_GetCurGsmPrio()                     (NAS_LMM_GetEmmStartInfoAddr()->aucCurRatPrioList[NAS_LMM_RAT_TYPE_GSM])
#define NAS_LMM_GetCurWcdmaPrio()                   (NAS_LMM_GetEmmStartInfoAddr()->aucCurRatPrioList[NAS_LMM_RAT_TYPE_WCDMA])
#define NAS_LMM_GetCurLtePrio()                     (NAS_LMM_GetEmmStartInfoAddr()->aucCurRatPrioList[NAS_LMM_RAT_TYPE_LTE])
#define NAS_LMM_GetCurCdma1xPrio()                     (NAS_LMM_GetEmmStartInfoAddr()->aucCurRatPrioList[NAS_LMM_RAT_TYPE_CDMA1X])
#define NAS_LMM_GetCurHrpdPrio()                     (NAS_LMM_GetEmmStartInfoAddr()->aucCurRatPrioList[NAS_LMM_RAT_TYPE_HRPD])
#define NAS_EMM_GetCurButtRatPrioFromList()         (NAS_LMM_GetEmmStartInfoAddr()->aucCurRatPrioList[NAS_LMM_RAT_TYPE_BUTT])


/* LMM PRE RAT PRIO*/
#define NAS_LMM_GetPreGsmPrio()                     (NAS_LMM_GetEmmStartInfoAddr()->aucPreRatPrioList[NAS_LMM_RAT_TYPE_GSM])
#define NAS_LMM_GetPreWcdmaPrio()                   (NAS_LMM_GetEmmStartInfoAddr()->aucPreRatPrioList[NAS_LMM_RAT_TYPE_WCDMA])
#define NAS_LMM_GetPreLtePrio()                     (NAS_LMM_GetEmmStartInfoAddr()->aucPreRatPrioList[NAS_LMM_RAT_TYPE_LTE])
#define NAS_EMM_GetPreButtRatPrioFromList()         (NAS_LMM_GetEmmStartInfoAddr()->aucPreRatPrioList[NAS_LMM_RAT_TYPE_BUTT])

/* 异系统变换信息地址 */
#define NAS_EMM_GetSysChngCtrlAddr()                (&(NAS_LMM_GetEmmInfoAddr()->stSysChngCtrl))
#define NAS_EMM_GetStateBeforeSuspendAddr()         (&(NAS_EMM_GetSysChngCtrlAddr()->stStateBeforeSuspend))
#define NAS_EMM_GetStateBeforeResumeAddr()          (&(NAS_EMM_GetSysChngCtrlAddr()->stStateBeforeResume))
#define NAS_EMM_GetSuspendSecuParaAddr()            (&(NAS_EMM_GetSysChngCtrlAddr()->stHoSecuPara))

/*GU ACT RESULT保存地址*/
#define NAS_EMM_GetGuActRstContextAddr()            (&(NAS_LMM_GetEmmInfoAddr()->stLmmGuActRst))
#define NAS_EMM_GetGuActRstOpReqDomain()            (NAS_EMM_GetGuActRstContextAddr()->bitOpGuReqDomain)
#define NAS_EMM_GetGuActRstOpRstDomain()            (NAS_EMM_GetGuActRstContextAddr()->bitOpGuRstDomain)
#define NAS_EMM_GetGuActRstOpMtDetachType()         (NAS_EMM_GetGuActRstContextAddr()->bitOpGuMtDetachType)
#define NAS_EMM_GetGuActRstOpCnCause()              (NAS_EMM_GetGuActRstContextAddr()->bitOpGuCnCause)
#define NAS_EMM_GetGuActRstOpAtmpCnt()             (NAS_EMM_GetGuActRstContextAddr()->bitOpGuAtmpCnt)
#define NAS_EMM_GetGuActType()                      (NAS_EMM_GetGuActRstContextAddr()->ulGuActionType)
#define NAS_EMM_GetGuActRst()                       (NAS_EMM_GetGuActRstContextAddr()->ulGuActRst)
#define NAS_EMM_GetGuActReqDomain()                 (NAS_EMM_GetGuActRstContextAddr()-> ulGuActReqDomain)
#define NAS_EMM_GetGuActRstDomain()                 (NAS_EMM_GetGuActRstContextAddr()-> ulGuActRstDomain)
#define NAS_EMM_GetGuActMtDetachType()              (NAS_EMM_GetGuActRstContextAddr()-> ulGuMtDetachType)
#define NAS_EMM_GetGuActCnCause()                   (NAS_EMM_GetGuActRstContextAddr()-> ucCnCause)
#define NAS_EMM_GetGuActAttemptCount()              (NAS_EMM_GetGuActRstContextAddr()-> ulAttemptCount)

/* LRRC在SYSCFG CNF消息中通知LMM挂起的类型 */
#define NAS_EMM_GetRrcSysCfgSusType()               (NAS_LMM_GetEmmInfoAddr()->ulRrcSysCfgSusType)

#define NAS_EMM_GetSuspendOri()                     ((NAS_EMM_GetSysChngCtrlAddr()->ulSusOri ))
#define NAS_EMM_GetResumeOri()                      ((NAS_EMM_GetSysChngCtrlAddr()->ulRsmOri ))
#define NAS_EMM_GetSuspendDir()                     ((NAS_EMM_GetSysChngCtrlAddr()->ulSusDir ))
#define NAS_EMM_GetResumeDir()                      ((NAS_EMM_GetSysChngCtrlAddr()->ulRsmDir ))
#define NAS_EMM_GetSuspendType()                    ((NAS_EMM_GetSysChngCtrlAddr()->ulSusType))
#define NAS_EMM_GetResumeType()                     ((NAS_EMM_GetSysChngCtrlAddr()->ulRsmType))
#define NAS_EMM_GetSuspendCause()                   ((NAS_EMM_GetSysChngCtrlAddr()->ulSusCause))
#define NAS_EMM_GetUplayerCount()                   ((NAS_EMM_GetSysChngCtrlAddr()->ulUpLayerCount))
#define NAS_EMM_GetSuspendSecuPara()                ((NAS_EMM_GetSuspendSecuParaAddr()->ucHoSecuPara))

#define NAS_EMM_GetMsBefSuspend()                   ((NAS_EMM_GetStateBeforeSuspendAddr()->enMainState))
#define NAS_EMM_GetSsBefSuspend()                   ((NAS_EMM_GetStateBeforeSuspendAddr()->enSubState))
#define NAS_EMM_GetStaTIdBefSuspend()               ((NAS_EMM_GetStateBeforeSuspendAddr()->enStaTId))
#define NAS_EMM_GetMsBefResume()                    ((NAS_EMM_GetStateBeforeResumeAddr()->enMainState))
#define NAS_EMM_GetSsBefResume()                    ((NAS_EMM_GetStateBeforeResumeAddr()->enSubState))



#define NAS_EMM_SetSuspendOri(ulOri)                (NAS_EMM_GetSuspendOri() = ulOri)
#define NAS_EMM_SetResumeOri(ulOri)                 (NAS_EMM_GetResumeOri()  = ulOri)
#define NAS_EMM_SetSuspendDir(ulSusDir)             (NAS_EMM_GetSuspendDir() = ulSusDir)
#define NAS_EMM_SetResumeDir(ulRsmDir)              (NAS_EMM_GetResumeDir()  = ulRsmDir)
#define NAS_EMM_SetSuspendType(ulSusType)           (NAS_EMM_GetSuspendType() = ulSusType)
#define NAS_EMM_SetResumeType(ulRsmType)            (NAS_EMM_GetResumeType()  = ulRsmType)
#define NAS_EMM_SetSuspendCause(ulSusCause)         (NAS_EMM_GetSuspendCause() = ulSusCause)
#define NAS_EMM_SetUplayerCount(ulUpLayerCount)     (NAS_EMM_GetUplayerCount()  = ulUpLayerCount)
#define NAS_EMM_SetSuspendSecuPara(ucHoSecuPara)    (NAS_EMM_GetSuspendSecuPara()= ucHoSecuPara)
#define NAS_EMM_SetMsBefSuspend(EmmMsSta)           ((NAS_EMM_GetMsBefSuspend()) = (EmmMsSta))
#define NAS_EMM_SetSsBefSuspend(EmmSsSta)           ((NAS_EMM_GetSsBefSuspend()) = (EmmSsSta))





/*标识LTE处于DISABLE态还是ENABLE态*/
#define NAS_EMM_GetLteEnableSta()                   (NAS_LMM_GetEmmInfoAddr()->enLteEnableSta)
#define NAS_EMM_SetLteEnableSta(LteEnableSta)       ((NAS_LMM_GetEmmInfoAddr()->enLteEnableSta)=(LteEnableSta))

/* 获取统计SysInfo消息全局变量地址 */
#define NAS_EMM_GetSysInfCntAddr()       (&g_stMsgSysInfCnt)

/* 自动ATTACH标志*/
#define NAS_EMM_GetAutoAttFlag()               (g_ulAutoAttFlag)
/*#define NAS_EMM_SetAutoAttFlag(ulAutoAttFlag) ((g_ulAutoAttFlag) = (ulAutoAttFlag))*/

/* CS域自动ATTACH标志*/
/*#define NAS_EMM_GetCsAutoAttFlag()                  (g_ulCsAutoAttFlag)*/
/*#define NAS_EMM_SetCsAutoAttFlag(ulCsAutoAttFlag)   ((g_ulCsAutoAttFlag) = (ulCsAutoAttFlag))*/

#define NAS_EMM_GetSuspendRelCause()     (NAS_LMM_GetEmmInfoAddr()->ulSuspendRelCause)  /* 停止挂起流程的原因 */
#define NAS_EMM_SetSuspendRelCause(cause)     (NAS_EMM_GetSuspendRelCause() = cause)    /* 停止挂起流程的原因 */

#define NAS_EMM_GetCsfbProcedureFlag()            (g_ulCsfbProcedureFlag)
#define NAS_EMM_SetCsfbProcedureFlag(flag)        (NAS_EMM_GetCsfbProcedureFlag() = flag)

#define NAS_EMM_GetLteNoSubscribeAddr()                                 (&stLteNoSubscribeConfig)
#define NAS_EMM_GetLteNoSubscribeNvConfigAddr()                         (&(NAS_EMM_GetLteNoSubscribeAddr()->stLteNoSubscribeNvConfig))
#define NAS_EMM_GetLteNoSubscribeNvConfigVplmnSwitch()                  (NAS_EMM_GetLteNoSubscribeNvConfigAddr()->ucLteNoSubscribeVplmnSwitch)
#define NAS_EMM_SetLteNoSubscribeNvConfigVplmnSwitch(switchFlag)        (NAS_EMM_GetLteNoSubscribeNvConfigVplmnSwitch() = switchFlag)
#define NAS_EMM_GetLteNoSubscribeNvConfigHplmnSwitch()                  (NAS_EMM_GetLteNoSubscribeNvConfigAddr()->ucLteNoSubscribeHplmnSwitch)
#define NAS_EMM_SetLteNoSubscribeNvConfigHplmnSwitch(switchFlag)        (NAS_EMM_GetLteNoSubscribeNvConfigHplmnSwitch() = switchFlag)
#define NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerVplmnLen()     (NAS_EMM_GetLteNoSubscribeNvConfigAddr()->ulPublishmentTimerVplmnLen)
#define NAS_EMM_SetLteNoSubscribeNvConfigPublishmentTimerVplmnLen(len)  (NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerVplmnLen() = len)
#define NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerHplmnLen()     (NAS_EMM_GetLteNoSubscribeNvConfigAddr()->ulPublishmentTimerHplmnLen)
#define NAS_EMM_SetLteNoSubscribeNvConfigPublishmentTimerHplmnLen(len)  (NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerHplmnLen() = len)

#define NAS_EMM_GetLteNoSubscribeNvConfigDiscardExtCauseFlag()          (NAS_EMM_GetLteNoSubscribeNvConfigAddr()->ucDiscardExtendedEmmCauseFlag)
#define NAS_EMM_SetLteNoSubscribeNvConfigDiscardExtCauseFlag(flag)      (NAS_EMM_GetLteNoSubscribeNvConfigDiscardExtCauseFlag() = flag)
/*#define NAS_EMM_GetLteNoSubscribeExtCauseFlag()                         (NAS_EMM_GetLteNoSubscribeAddr()->ulExtCauseFlag)
#define NAS_EMM_SetLteNoSubscribeExtCauseFlag(flag)                     (NAS_EMM_GetLteNoSubscribeExtCauseFlag() = flag)*/

#define NAS_EMM_GetLteNoSubscribeLteRegFlag()                         (NAS_EMM_GetLteNoSubscribeAddr()->ucIsLteRegFlag)
#define NAS_EMM_SetLteNoSubscribeLteRegFlag(flag)                     (NAS_EMM_GetLteNoSubscribeLteRegFlag() = flag)
/* Lnas功能开关组 */
#define  LNAS_NV_GET_NAS_FUN_FLAG(ucIndex, ulFlag)        (g_aulNasFunFlg[ucIndex]&(ulFlag))

#define NAS_EMM_GetOmSwitchAddr()                         (&g_stNasOmSwitch)
#define NAS_EMM_GetOmSwitchKeyInfoFlag()                  (NAS_EMM_GetOmSwitchAddr()->ucLnasKeyInfoFlag)
#define NAS_EMM_GetOmSwitchKeyEventFlag()                 (NAS_EMM_GetOmSwitchAddr()->ucLnasKeyEventFlag)
#define NAS_EMM_GetOmSwitchApiFlag()                      (NAS_EMM_GetOmSwitchAddr()->ucLnasApiFlag)
#define NAS_EMM_GetOmSwitchSuccRatioFlag()                (NAS_EMM_GetOmSwitchAddr()->ucLnasSuccRatioFlag)
#define NAS_EMM_GetOmSwitchDelayFlag()                    (NAS_EMM_GetOmSwitchAddr()->ucLnasDelayFlag)
#define NAS_LMM_GetGradualForbTempForbTaListAddr()       (&g_stGradualForbTempForbTaList)
#define NAS_LMM_GetGradualForbTaAddr(ulIndex)            (&g_stGradualForbTempForbTaList.astGradualForbTa[ulIndex])
#define NAS_LMM_GetGradualForbTimerAddr(ulIndex)         (&g_stGradualForbTempForbTaList.astGradualForbTa[ulIndex].stGradualForbTimer)
#define NAS_LMM_GetGradualForbAgingTimerAddr(ulIndex)    (&g_stGradualForbTempForbTaList.astGradualForbTa[ulIndex].stGradualForbAgingTimer)
#define NAS_LMM_GetTauReqSndFailFlag()                   (g_ulEmmTauReqSndFailFlag)
#define NAS_LMM_SetTauReqSndFailFlag(enTauReqSndFailFlag)      (NAS_LMM_GetTauReqSndFailFlag() = (enTauReqSndFailFlag))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 枚举名    : NAS_EMM_INFO_DATA_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS_EMM_PUB_INFO_STRU  g_stEmmInfo 中的各数据项类型
*****************************************************************************/
enum NAS_EMM_INFO_DATA_TYPE_ENUM
{
    /* NAS_LMM_UEID_STRU 类型 */
    NAS_EMM_INFO_UEID_BEGIN             = 0x00000000,
    NAS_EMM_INFO_UEID                               ,
    NAS_EMM_INFO_IMSI                               ,
    NAS_EMM_INFO_IMEI                               ,
    NAS_EMM_INFO_IMEISV                             ,
    NAS_EMM_INFO_TMSI                               ,
    NAS_EMM_INFO_PTMSI                              ,
    NAS_EMM_INFO_TMGI                               ,
    NAS_EMM_INFO_GUTI                               ,
    NAS_EMM_INFO_UEID_END                           ,   /*NAS_LMM_UEID_STRU 类型 的结尾*/


    /* NAS_LMM_NETWORK_INFO_STRU 类型 */
    NAS_EMM_INFO_NETWORK_INFO_BEGIN     = 0x00001000,
    NAS_EMM_INFO_NETWORK_INFO                       ,
    NAS_EMM_INFO_PRESENT_NET_ID                     ,
    NAS_EMM_INFO_LAST_REG_NET_ID                    ,
    NAS_EMM_INFO_EPLMN_LIST                         ,
    NAS_EMM_INFO_TAI_LIST                           ,
    NAS_EMM_INFO_HPLMN                              ,
    NAS_EMM_INFO_EHPLMN_LIST                        ,
    NAS_EMM_INFO_FORB_TA_FOR_ROAM                   ,
    NAS_EMM_INFO_FORB_TA_FOR_RPOS                   ,
    NAS_EMM_INFO_NETWORK_INFO_END                   ,   /*NAS_LMM_NETWORK_INFO_STRU 类型 的结尾*/



    /* NAS_LMM_SECURITY_PARA_STRU 类型 */
    NAS_EMM_INFO_SECURITY_PARA_BEGIN    = 0x00002000,
    NAS_EMM_INFO_SECURITY_PARA                      ,
    NAS_EMM_INFO_NKSI                               ,
    NAS_EMM_INFO_NKSISGSN                           ,
    NAS_EMM_INFO_NSA                                ,
    NAS_EMM_INFO_UE_NET_CAP                         ,
    NAS_EMM_INFO_MS_NET_CAP                         ,
    NAS_EMM_INFO_SECURITY_PARA_END                  ,   /*NAS_LMM_SECURITY_PARA_STRU 类型 的结尾*/


    NAS_EMM_INFO_DRX                                ,
    NAS_EMM_INFO_CLASSMARK                          ,
    NAS_EMM_INFO_CODEC_LIST                         ,


    NAS_EMM_INFO_DATA_TYPE_BUTT
 };
typedef VOS_UINT32   NAS_EMM_INFO_DATA_TYPE_ENUM_UINT32;


/*****************************************************************************
结构名称    :
使用说明    :
*****************************************************************************/
enum NAS_EMM_TIMER_UNIT_ENUM
{
    NAS_EMM_TIMER_UNIT_2SENDS           = 0x00,             /*000:value is incremented in
                                                                  multiples of 2 seconds*/
    NAS_EMM_TIMER_UNIT_1MINUTE          = 0x01,             /*001:value is incremented in
                                                                  multiples of 1 minute*/
    NAS_EMM_TIMER_UNIT_6MINUTES         = 0x02,             /*010:value is incremented in
                                                                  multiples of decihours*/
    NAS_EMM_TIMER_DEACTIVATE            = 0x07,             /*111:value indicated that the
                                                                  timer is deactivated*/

    NAS_EMM_TIMER_UNIT_BUTT
};
typedef VOS_UINT8   NAS_EMM_TIMER_UNIT_ENUM_UINT8;

/*****************************************************************************
结构名称    :控制NAS安全特性的相关参数
使用说明    :
*****************************************************************************/
enum NAS_EMM_SMC_CTRL_UNIT_ENUM
{
    NAS_EMM_SMC_OPEN                    = 0,
    NAS_EMM_SMC_CLOSE                   = 1,
    NAS_EMM_SMC_CTRL_UNIT_BUTT
};
typedef VOS_UINT8   NAS_EMM_SMC_CTRL_UNIT_ENUM_UINT32;

/*****************************************************************************
结构名称    :控制关机时是否发起DETACH 的相关参数
使用说明    :
*****************************************************************************/
/*
enum NAS_EMM_DETACH_WHEN_POWEROFF_CTRL_ENUM
{
    NAS_EMM_DO_NOT_DETACH_WHEN_POWEROFF = 0,
    NAS_EMM_DO_DETACH_WHEN_POWEROFF     = 1,
    NAS_EMM_DETACH_WHEN_POWEROFF_CTRL_BUTT
};
typedef VOS_UINT32  NAS_EMM_DETACH_WHEN_POWEROFF_CTRL_ENUM_UINT32;
*/
/*****************************************************************************
 枚举名    : NAS_NV_ITEM_OP_TYPE_ENUM
 枚举说明  : NV项操作类型
*****************************************************************************/
enum  NAS_NV_ITEM_OP_TYPE_ENUM
{
    NAS_NV_ITEM_DELETE,
    NAS_NV_ITEM_UPDATE,
    NAS_NV_ITEM_OP_TYPE_BUTT
};
typedef VOS_UINT32   NAS_NV_ITEM_OP_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_UE_CAP_CHG_UPDATE_TYPE_ENUM
 枚举说明  : 用于记录无线能力变更类型是否刷新
*****************************************************************************/
enum  NAS_UE_CAP_CHG_UPDATE_TYPE_ENUM
{
    NAS_UE_CAP_CHG_HAVE_UPDATE = 0,
    NAS_UE_CAP_CHG_NO_UPDATE,
    NAS_UE_CAP_CHG_BUTT
};
typedef VOS_UINT32 NAS_UE_CAP_CHG_UPDATE_TYPE_ENUM_UINT32;

typedef VOS_UINT32  MM_SESSION_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_LMM_DSDS_MSG_TYPE_ENUM
 枚举说明  : 用于记录启动或者结束流程保护
*****************************************************************************/
enum  NAS_LMM_DSDS_MSG_TYPE_ENUM
{
    NAS_LMM_DSDS_MSG_TYPE_BEGIN = 0,     /*启动流程保护*/
    NAS_LMM_DSDS_MSG_TYPE_END,           /*结束流程保护*/
    NAS_LMM_DSDS_MSG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32;

enum  NAS_OM_LOG_DSDS_MSG_ENUM
{
    NAS_OM_LOG_DSDS_MSG_PREPROC  =  0x00,
    NAS_OM_LOG_DSDS_MSG_SEND,
    NAS_OM_LOG_DSDS_MSG_BUTT
};
typedef VOS_UINT32 NAS_OM_LOG_DSDS_MSG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM
 枚举说明  : TA更新临时列表结果
*****************************************************************************/
enum NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM
{
    NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST            = 0,
    NAS_EMM_GRADUAL_FORB_ADD_TA_SUCC                      = 1,
    NAS_EMM_GRADUAL_FORB_TA_IN_TEMP_LIST                  = 2,
    NAS_EMM_GRADUAL_FORB_TA_LIST_CHANGED                  = 3,
    NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED              = 4,
    NAS_EMM_GRADUAL_FORB_REUSLT_BUTT
};
typedef VOS_UINT32 NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32;
/*****************************************************************************
 枚举名    : NAS_EMM_GRADUAL_FORBIDDEN_TA_USED_FLAG_ENUM
 枚举说明  : 临时TA列表, 被使用标志
*****************************************************************************/
enum NAS_EMM_GRADUAL_FORBIDDEN_TA_USED_FLAG_ENUM
{
    NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED                 = 0,
    NAS_EMM_GRADUAL_FORBIDDEN_TA_USED                     = 1,
    NAS_EMM_GRADUAL_FORBIDDEN_TA_USED_FLAG_BUTT
};
typedef VOS_UINT8 NAS_EMM_GRADUAL_FORBIDDEN_TA_USED_FLAG_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
结构名称    :内部消息 INTRA_CONN2IDLE_REQ的结构
使用说明    :
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;   /* 消息ID*/
    VOS_UINT32          ulReserved;
}NAS_EMM_INTRA_CONN2IDLE_REQ_STRU;

/*****************************************************************************
结构名称    :内部消息INTRA_DISABLE_LTE_NOTIFY的结构
使用说明    :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;   /* 消息ID*/
    VOS_UINT32          ulReserved;
}NAS_LMM_INTRA_DISABLE_LTE_NOTIFY_STRU;

/*****************************************************************************
 枚举名    : NAS_EMM_RAT_LRRC_TAILIST_STATUS_ENUM
 枚举说明  : 异系统流程中收到LRRC的TAILIST的时候判断是否在被禁列表中
*****************************************************************************/
enum    NAS_EMM_RAT_LRRC_TAILIST_STATUS_ENUM
{
    NAS_EMM_RAT_LRRC_TAILIST_STATUS_ALL_IN_FORB_LIST = 1,
    NAS_EMM_RAT_LRRC_TAILIST_STATUS_PART_IN_FORB_LIST,
    NAS_EMM_RAT_LRRC_TAILIST_STATUS_ALL_NOT_IN_FORB_LIST,
    NAS_EMM_RAT_LRRC_TAILIST_STATUS_BUTT
};
typedef VOS_UINT32  NAS_EMM_RAT_LRRC_TAILIST_STATUS_ENUM_UINT32;
/*****************************************************************************
结构名称    :内部消息INTRA_EIA0_ACT_NOTIFY的结构
使用说明    :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;   /* 消息ID*/
    VOS_UINT32          ulReserved;
}NAS_LMM_INTRA_EIA0_ACT_NOTIFY_STRU;

/*****************************************************************************
结构名称    : NAS_EMM_ESM_MSG_BUFF_STRU
使用说明    : EMM保存ESM消息缓存的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulOpid;
    VOS_UINT32                              ulIsEmcType;
    EMM_ESM_MSG_STRU                        stEsmMsg;
}NAS_EMM_ESM_MSG_BUFF_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_SYSINFO_COUNT_STRU
使用说明    :用于记录等待RRC EstCnf/RelCnf/RelInd 时收到SysInfo次数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulEstCnfCount;
    VOS_UINT32                                 ulRelCnfCount;
    VOS_UINT32                                 ulRegInitRrcRelIndCount;
    VOS_UINT32                                 ulDeregInitRrcRelIndCount;
    VOS_UINT32                                 ulTauInitRrcRelIndCount;
    VOS_UINT32                                 ulServInitRrcRelIndCount;
    VOS_UINT32                                 ulRegImsiDetachRrcRelIndCount;
}NAS_LMM_SYSINFO_COUNT_STRU;


/*sunbing 49683 2013-10-21 VoLTE begin*/
/*******************************************************************************
 结构名    : NAS_EMM_SUPPORT_CODEC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前支持的codec类型,bit位置1表示该codec有效
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          CodecType_GSMFR         :1;
    VOS_UINT16                          CodecType_GSMHR         :1;
    VOS_UINT16                          CodecType_GSMEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMR      :1;
    VOS_UINT16                          CodecType_GSMHRAMR      :1;
    VOS_UINT16                          CodecType_UMTSAMR       :1;
    VOS_UINT16                          CodecType_UMTSAMR2      :1;
    VOS_UINT16                          CodecType_TDMAEFR       :1;
    VOS_UINT16                          CodecType_PDCEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMRWB    :1;
    VOS_UINT16                          CodecType_UMTSAMRWB     :1;
    VOS_UINT16                          CodecType_OHR_AMR       :1;
    VOS_UINT16                          CodecType_OFR_AMR_WB    :1;
    VOS_UINT16                          CodecType_OHR_AMR_WB    :1;
    VOS_UINT16                          BandSpare               :2;
}NAS_EMM_SUPPORT_CODEC_STRU;

/*******************************************************************************
 结构名    :NAS_EMM_SUPPORT_CODEC_UNION
 协议表格  :
 ASN.1描述 :
 结构说明  : 当前支持的codec类型,bit位置1表示该codec有效，参考MN_CALL_SUPPORT_CODEC_UNION
*******************************************************************************/
typedef union
{
    NAS_EMM_SUPPORT_CODEC_STRU          stSupportCodec;
    VOS_UINT16                          usSupportCodec;
}NAS_EMM_SUPPORT_CODEC_UNION;
/*sunbing 49683 2013-10-21 VoLTE end*/

/*******************************************************************************
 结构名    :NAS_LMM_SESSION_TYPE_MAP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC/MM/GMM模块发送的session type与LMM维护的session type映射
*******************************************************************************/
typedef struct
{
      VOS_UINT32                           ulSenderPid;
      MM_SESSION_TYPE_ENUM_UINT32  enInputSessionType;
      MM_SESSION_TYPE_ENUM_UINT32  enOutputSessionType;
}NAS_LMM_SESSION_TYPE_MAP_STRU;

/*******************************************************************************
 结构名    :NAS_LMM_DSDS_SESSION_MSG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 记录发送业务通知消息的相关信息
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU              stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32 enMsgType;/*标示当前消息是开始或结束*/
    MM_SESSION_TYPE_ENUM_UINT32       enOutputSessionType;  /*输出的SESSION TYPE*/
    VOS_UINT32                        ulBeginMsgTotal;      /*对应session type发送begin消息个数*/
    VOS_UINT32                        ulEndMsgTotal;        /*对应session type发送end消息个数*/
}NAS_LMM_DSDS_SESSION_MSG_INFO_STRU;

/*******************************************************************************
 结构名    :NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 记录透传过来的业务消息
             ulInputType参数值和g_astDsdsCvtSessionTypeTbl索引值对应，
             如 0:表示来自MMC模块的MMC_LMM_SESSION_TYPE_CS_MO_NORMAL_CALL消息
                1:表示来自MMC模块的MMC_LMM_SESSION_TYPE_CS_MO_EMERGENCY_CALL消息
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU              stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32 enMsgType;/*标示当前消息是开始或结束*/
    VOS_UINT32                   ulInputType;   /*透传消息ID*/
    VOS_UINT32                   ulBeginMsgTotal;      /*对应session type发送begin消息个数*/
    VOS_UINT32                   ulEndMsgTotal;        /*对应session type发送end消息个数*/
}NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU;

/*******************************************************************************
 结构名    :NAS_LMM_DSDS_MSG_COUNT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 统计DSDS消息个数
*******************************************************************************/
typedef struct
{
      VOS_UINT32                           ulBeginMsgCnt;
      VOS_UINT32                           ulEndMsgCnt;
}NAS_LMM_DSDS_MSG_COUNT_STRU;

/*******************************************************************************
 结构名    :EMM_ESM_DATA_CNF_MAP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :MAP LRRC data cnf原因值到ESM
*******************************************************************************/
typedef struct
{
      LRRC_LMM_SEND_RSLT_ENUM_UINT32        enSendRslt;
      EMM_ESM_SEND_RSLT_ENUM_UINT32         enEmmEsmDataCnfRst;
}EMM_ESM_DATA_CNF_MAP_STRU;

typedef VOS_VOID ( * NAS_LMM_REJ_CAUSE_PROC_FUN )
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enRejCauseVal
);

typedef struct
{
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enRejCauseVal; /* 拒绝原因值 */
    NAS_LMM_REJ_CAUSE_PROC_FUN          pfRejCauseProcFun; /* 拒绝原因值的处理函数 */
}NAS_LMM_REJ_CAUSE_PROC_STRU;



/*****************************************************************************
结构名称    :MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU
使用说明    :4G未开户问题带给MMC的PLMN列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    MMC_LMM_PLMN_ID_STRU                astPlmnId[MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM];
}MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU;

/*****************************************************************************
结构名称    :LNAS_LMM_LTE_NO_SUBSCRIBE_CONFIG_STRU
使用说明    :4G未开户问题带给MMC的PLMN列表
*****************************************************************************/
typedef struct
{
    LNAS_LMM_NV_LTE_NO_SUBSCRIBE_CONFIG_STRU    stLteNoSubscribeNvConfig;
    VOS_UINT32                                  ulExtCauseFlag;
    VOS_UINT8                                   ucIsLteRegFlag;     /*ucIsLteRegFlag标识用于识别UE是否在LTE上面注册成功过，
                                                                    设置的时机是， TAU， ATTACH SUCC, 开机读NV，读USIM*/
    VOS_UINT8                                   aucRsv[3];
}LNAS_LMM_LTE_NO_SUBSCRIBE_CONFIG_STRU;


/*****************************************************************************
结构名称    :LNAS_NV_OM_SWITCH_STRU
使用说明    :可维可测上报控制开关，0为关闭,1为打开
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLnasKeyInfoFlag;
    VOS_UINT8                           ucLnasKeyEventFlag;
    VOS_UINT8                           ucLnasApiFlag;
    VOS_UINT8                           ucLnasSuccRatioFlag;
    VOS_UINT8                           ucLnasDelayFlag;
    VOS_UINT8                           ucRsv[3];
}LNAS_NV_OM_SWITCH_STRU;
/*****************************************************************************
结构名称    :NAS_LMM_GRADUAL_FORB_TA
使用说明    :渐进被禁维护TA信息
*****************************************************************************/
typedef struct
{
    NAS_MM_TA_STRU                                    stTa;                 /* TA列表 */
    NAS_LMM_TIMER_CTRL_STRU                           stGradualForbTimer;    /* 渐进被禁定时器信息维护列表 */
    NAS_LMM_TIMER_CTRL_STRU                           stGradualForbAgingTimer;/* 老化定时器信息维护列表 */
    VOS_UINT32                                        ulTimerPara;          /* 用于区分定时器超时属于哪个TA */
    VOS_UINT8                                         uc15RejTimes;         /* TA被#15拒过的次数 */
    NAS_EMM_GRADUAL_FORBIDDEN_TA_USED_FLAG_ENUM_UINT8 enUsedFlag;           /* 该存储位置是否被使用 */
    VOS_UINT8                                         aucRsv[2];
}NAS_LMM_GRADUAL_FORB_TA;
/*****************************************************************************
结构名称    :NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST
使用说明    :渐进被禁维护临时被禁列表,最大存储16条TA信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulTaNum;                                                    /* 列表中TA个数 */
    NAS_LMM_GRADUAL_FORB_TA                     astGradualForbTa[NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM];       /* TA信息 */
}NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST;

/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_EMM_PUB_INFO_STRU                   g_stEmmInfo;
extern  VOS_UINT32                              g_ulSmcControl;
extern  VOS_UINT32                              g_ulUeSecuCapMatch;


extern  NAS_LMM_SYSINFO_COUNT_STRU               g_stMsgSysInfCnt;
extern  VOS_UINT32                              g_ulAutoAttFlag;
extern  VOS_UINT32                              g_ulCsAutoAttFlag;

extern OM_EMM_STATE_INFO_STRU                   g_stEmmOmInfo;

extern NAS_LMM_SESSION_TYPE_MAP_STRU g_astDsdsCvtSessionTypeTbl[];
extern VOS_UINT32 g_astDsdsCvtSessionTypeTblLen;
extern NAS_LMM_DSDS_MSG_COUNT_STRU g_astDsdsNotifyMsgNum[LRRC_LNAS_SESSION_TYPE_BUTT];
extern NAS_LMM_DSDS_MSG_COUNT_STRU  g_astDsdsInputNotifyMsgNum[NAS_EMM_INPUT_DSDS_MSG_NUM];
extern NAS_LMM_REJ_CAUSE_PROC_STRU  gstEmmAttRejCauseProcTbl[];
extern VOS_UINT32        gstEmmAttRejCauseProcTblLen;
extern VOS_UINT32  g_ulCsfbProcedureFlag;

extern LNAS_LMM_LTE_NO_SUBSCRIBE_CONFIG_STRU    stLteNoSubscribeConfig;
extern LNAS_NV_OM_SWITCH_STRU g_stNasOmSwitch;
extern VOS_UINT32  g_aulNasFunFlg[8];
/* 渐进被禁优化控制 */
extern VOS_UINT8                               g_ucLmmGradualForbFlag;
extern NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  g_stGradualForbTempForbTaList;
extern VOS_UINT32                              g_ulGradualForbTimerFirstLen;
extern VOS_UINT32                              g_ulGradualForbTimerSecondLen;
extern VOS_UINT32                              g_ulGradualForbAgingTimerLen;
extern VOS_UINT32                              g_ulGradualForbTaTimerPara;
extern VOS_UINT32                              g_ulEmmT3402length ;


extern VOS_UINT32        g_ulEsrRej39OptimizeCtr;

extern VOS_UINT32                       g_ulNasAustraliaFlag;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern  VOS_VOID    NAS_EMM_FsmInit(            VOS_VOID );
extern  VOS_VOID    NAS_EMM_PubmInfoUeIdInit(   VOS_VOID );
extern  VOS_VOID    NAS_EMM_PubmInfoNetInfoInit(VOS_VOID );

extern  VOS_VOID    NAS_EMM_ReadNvUeNetCap(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ReadNvUeOperationMode(VOS_VOID );

extern  VOS_VOID    NAS_EMM_ReadNvVoiceDomain(VOS_VOID );
extern  VOS_VOID    NAS_EMM_ReadNvNasRelease(VOS_VOID );

extern VOS_VOID  NAS_EMM_ReadNvConfigNwCause(VOS_VOID );

extern  VOS_VOID    NAS_EMM_PubmInfoDrxInit(VOS_VOID);
extern  VOS_UINT32  NAS_EMM_IsGuContainPsRegDrx(VOS_VOID);
extern  VOS_VOID    NAS_EMM_UpdateLteContainDrxFlag( VOS_VOID );
/*extern  VOS_VOID    NAS_EMM_ReadNvDrx(    VOS_VOID );*/
/*extern  VOS_UINT32  NAS_EMM_WriteNvDrx( VOS_VOID );*/
extern  VOS_VOID    NAS_EMM_ReadNvClassMark( VOS_VOID );
extern  VOS_VOID    NAS_EMM_PubmInfoSupCodecListInit( VOS_VOID );
extern  VOS_VOID    NAS_EMM_PubmInfoBearerContextInit(VOS_VOID);
extern  VOS_VOID    NAS_EMM_FsmReg( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_FsmErr(    VOS_UINT32           ulMsgId,
                                                VOS_VOID             *pMsg );
extern  VOS_VOID    NAS_EMM_FSM_PushState(VOS_VOID);
extern  VOS_VOID    NAS_EMM_FSM_PopState(VOS_VOID);

extern  VOS_VOID NAS_LMM_ReadNvimImei(VOS_VOID);

extern  VOS_VOID NAS_EMM_PubUReadNvimClassMark (VOS_VOID);

extern  VOS_VOID NAS_LMM_EmmStateInit( VOS_VOID );
extern  VOS_VOID NAS_LMM_GetImeisvFromImei(VOS_VOID);
extern  VOS_VOID    NAS_EMM_PubmInfoNetCapInit( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_TimerValTransfer
        (
            NAS_EMM_TIMER_UNIT_ENUM_UINT8        ucUnit,
            VOS_UINT8                           ucTimerVal
        );

/*extern  VOS_VOID  NAS_LMM_ReadSimServiceTable(VOS_VOID );*/
extern  VOS_VOID  NAS_LMM_ReadNvEpsSecContext(VOS_VOID);
extern  VOS_VOID  NAS_LMM_ReadSimEpsSecContext( VOS_VOID );

extern  VOS_VOID  NAS_LMM_ReadSimPsLoc( VOS_VOID );

extern VOS_VOID  NAS_LMM_ReadSimMncLen(VOS_VOID);

extern  VOS_VOID  NAS_LMM_ReadNvPsLoc(VOS_VOID);
extern  VOS_VOID  NAS_LMM_UpdateNvImsi(const VOS_UINT8  *pucImsi );
extern VOS_VOID   NAS_EMM_CommProcConn2Ilde( VOS_VOID );
extern  VOS_VOID NAS_LMM_CountSysInfo( VOS_UINT16 usSubState );
extern VOS_VOID  NAS_LMM_WriteNvPsLoc
(
    NAS_NV_ITEM_OP_TYPE_ENUM_UINT32     enOpType
);
extern VOS_VOID  NAS_LMM_WriteSimPsLoc( VOS_VOID );
extern VOS_VOID  NAS_LMM_WriteNvEpsSecurityContext(NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType);
extern VOS_VOID  NAS_LMM_WriteSimEpsSecurityContext(NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType );
extern VOS_VOID  NAS_LMM_WriteEpsSecuContext( NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType );
extern VOS_VOID  NAS_LMM_WritePsLoc
(
    NAS_NV_ITEM_OP_TYPE_ENUM_UINT32     enOpType
);
/*extern VOS_VOID  NAS_LMM_WriteGuUeMode(VOS_VOID);*/
extern VOS_VOID  NAS_EMM_WriteNvMmInfo(VOS_VOID);
extern VOS_VOID  NAS_LMM_EmmInfoInit( VOS_VOID );
extern VOS_VOID  NAS_EMM_NoUsimInit( VOS_VOID );
extern VOS_VOID  NAS_EMM_InitSimState( VOS_VOID );
extern VOS_VOID  NAS_EMM_SaveAppMsgPara( VOS_UINT32 ulMsgId, VOS_UINT32 ulOpId);
extern VOS_VOID  NAS_EMM_ClearAppMsgPara( VOS_VOID );
extern VOS_UINT32  NAS_EMM_CheckAppMsgPara( VOS_UINT32 ulMsgId );
extern VOS_UINT32  NAS_EMM_GetAppMsgOpId( VOS_VOID );
extern VOS_UINT32  NAS_LMM_CheckPlmnAct( VOS_UINT8 const * pucPlmn);
extern VOS_VOID    NAS_LMM_ReadNvimHplmn (VOS_VOID);
extern VOS_VOID    NAS_EMM_ClearGuti(VOS_VOID);
extern VOS_VOID    NAS_EMM_ClearLVRTai( VOS_VOID );

extern VOS_VOID  NAS_EMM_SetLVRTacInvalid( VOS_VOID );

extern VOS_VOID    NAS_EMM_ClearTaiList( VOS_VOID );
extern VOS_VOID    NAS_EMM_ClearRegInfo( VOS_UINT32 ulDeleteRplmn );
extern VOS_VOID    NAS_EMM_ReadNvimNoImsi( VOS_VOID );
/*extern VOS_VOID    NAS_EMM_SetEmmSerTab( VOS_UINT32 ulSerTabBit );*/
extern VOS_VOID    NAS_EMM_LocalDetachProc( VOS_VOID );
extern VOS_VOID    NAS_EMM_SetLVRTai(const NAS_MM_NETWORK_ID_STRU *pstNetId);
extern VOS_VOID  NAS_EMM_SetGuti
(
    const NAS_EMM_GUTI_STRU *pstGuti
);

extern VOS_UINT32  NAS_EMM_UpdatePresentPlmnInfo(VOS_VOID);

extern VOS_VOID  NAS_EMM_SetEmergencyList
(
    VOS_UINT32                             ulOpEmerList,
    const NAS_LMM_EMERGENCY_NUM_LIST_STRU *pstEmerNumList
);


extern VOS_VOID NAS_EMM_ClearEmergencyList( VOS_VOID );
extern VOS_UINT32 NAS_EMM_IsMccChanged( VOS_VOID );


extern VOS_VOID  NAS_EMM_SetEpsNetFeature
(
    VOS_UINT32                          ulOpNetFeature,
    VOS_UINT8                           ucNetFeature
);

extern VOS_VOID  NAS_EMM_SetAddUpdateRslt
(
    VOS_UINT32                                  ulOpAddUpdateRslt,
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt
);
extern NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  NAS_EMM_GetAddUpdateRslt
(
   VOS_VOID
);
extern VOS_UINT32  NAS_EMM_GetLVRTaiOpBit(VOS_VOID  );
/*extern VOS_UINT32  NAS_EMM_GetLaiOpBit( VOS_VOID);
extern VOS_VOID    NAS_EMM_SetLai(const NAS_EMM_LA_STRU *pstLai);
extern VOS_VOID     NAS_EMM_GetLai(NAS_EMM_LA_STRU *pstLai);*/
extern VOS_UINT32  NAS_EMM_TransferUeSpecDrxCycleLen( VOS_VOID );
extern VOS_VOID    NAS_EMM_SendUeSpecDrxCycleLenToRrc( VOS_VOID );
extern VOS_VOID    NAS_EMM_SendInfoChangeReqMsg( CONST LRRC_LNAS_INFO_STRU *pstNasInfo );
extern VOS_VOID    NAS_EMM_PUBU_ClearResource(VOS_VOID);
extern VOS_VOID    NAS_EMM_PUBU_SuspendClearResource(VOS_VOID);
extern VOS_VOID    NAS_EMM_FSM_PopAllState(VOS_VOID);
extern VOS_UINT32  NAS_EMM_CheckSimGutiValid( const VOS_UINT8 *pucSimRecord,
                                                          const VOS_UINT32 ulIndex,
                                                          const VOS_UINT32 ulLen );

extern VOS_VOID NAS_EMM_AddForbTa
(
    const NAS_MM_TA_STRU               *pstTa,
    NAS_MM_TA_LIST_STRU                *pstTaList
);
extern VOS_VOID NAS_EMM_GetCurrentTa( NAS_MM_TA_STRU *pstTa );
extern VOS_VOID NAS_EMM_SetUsimState( NAS_LMM_SIM_STAT_ENUM_UINT32 ulUsimStatus );
extern VOS_VOID NAS_EMM_SendIntraConn2IdleReq(VOS_VOID);
extern VOS_VOID NAS_LMM_IfEmmHasBeenPushedThenPop( VOS_VOID );
extern VOS_VOID NAS_LMM_EstingOrReleasingProcessTimerHandle(VOS_VOID);
extern VOS_VOID    NAS_EMM_SendMmcStatusInd(
                                MMC_LMM_STATUS_TYPE_ENUM_UINT32 ulMmcLmmStaType,
                                MMC_LMM_CONN_STATE_ENUM_UINT32  ulConnState );

extern VOS_VOID NAS_EMM_SendMmcEmmInfoInd(const NAS_EMM_INFO_STRU *pLmmEmmInfo);

extern VOS_VOID    NAS_EMM_PUBU_FSMTranState(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  usMs,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   usSs,
                                    NAS_EMM_STATE_TI_ENUM_UINT16    usTi);


extern VOS_UINT32  NAS_EMM_CheckSupportGUMode( VOS_VOID);
extern VOS_UINT32  NAS_EMM_CheckMutiModeSupport(VOS_VOID  );
extern VOS_UINT32  NAS_EMM_CheckPtmsiAndRaiValidity( VOS_VOID );
extern VOS_VOID  NAS_EMM_GetPtmsiAndRai
(
    NAS_GUMM_PTMSI_STRU     *pstPtmsi,
    MMC_LMM_RAI_STRU        *pstRai
);
extern VOS_VOID  NAS_EMM_DeriveMappedGuti
(
    NAS_LMM_GUTI_STRU                   *pstMappedGuti
);
extern VOS_UINT32  NAS_EMM_GetTinType(VOS_VOID );
/*del by leili for isr */
extern VOS_VOID NAS_EMM_SendMmcUsimStatusCnf( VOS_VOID );
extern VOS_UINT32 NAS_EMM_IsCsPsUeMode( VOS_VOID );
extern VOS_VOID NAS_LMM_SetGuUeMode( NAS_LMM_GU_UE_MODE_ENUM_UINT32 ulGuUeMode);
extern VOS_VOID  NAS_LMM_LteModeChange
(
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeCur,
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeNew
);
extern NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   NAS_LMM_ComputeLteUeMode
(
    NAS_MML_MS_MODE_ENUM_UINT8      ulGuUeMode,
    NAS_EMM_USAGE_SETTING_UINT32        ulUeCenter
);
extern VOS_UINT32  NAS_EMM_lteRatIsExist(VOS_VOID);
extern NAS_LMM_GU_UE_MODE_ENUM_UINT32  NAS_LMM_GetEmmInfoGuUeMode(VOS_VOID);
extern NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32  NAS_LMM_GetEmmInfoUeOperationMode(VOS_VOID);
extern VOS_VOID NAS_EMM_SendMmCombinedStartNotifyReq
(
    MM_LMM_COMBINED_TYPE_ENUM_UINT32    enCombinedType
);
extern VOS_VOID NAS_EMM_SetTauTypeNoProcedure( VOS_VOID );


extern VOS_VOID    NAS_EMM_SendMmcInfoChangeNotify( VOS_VOID );


extern VOS_UINT32  NAS_EMM_RecordUeRadioAccCapChg(VOS_UINT8 ucRadioAccCapChgInd );
extern VOS_UINT32 NAS_LMM_SetEmmInfoUeRadioCapChg(
           NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32   enCurrentUeCapChg,
           NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32   enLastUeCapChg);
extern VOS_VOID  NAS_EMM_ClearUeRadioAccCapChgFlag(VOS_VOID);
extern VOS_VOID  NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc(VOS_VOID);

extern NAS_MML_EMERGENCY_NUM_LIST_STRU*  NAS_EMM_GetEmergencyListFromMml( VOS_VOID );


extern VOS_VOID NAS_EMM_CheckTimerRunningCommonProc
(
    VOS_UINT32                          ulCheckRslt,
    NAS_LMM_STATE_TI_ENUM_UINT16        enStateTimerId
);
extern VOS_UINT32 NAS_EMM_ComCheckEnterNrlSerOrUptMm( VOS_VOID );
extern VOS_VOID NAS_MML_SetUeNetWorkCapability
(
    NAS_MML_UE_NETWORK_CAPABILITY_STRU *pstUeNetworkCapbility
);

extern VOS_VOID NAS_EMM_ClearResumeInfo( VOS_VOID );

extern VOS_VOID NAS_LMM_ClearEmmInfoMmcAttachReason( VOS_VOID );


extern VOS_VOID  NAS_EMM_SendTimerStateNotify
(
    NAS_LMM_PTL_TI_ENUM_UINT16      ulTimerId,
    LMM_MMC_TIMER_STATE_ENUM_UINT32  ulTimerInfo
);
extern VOS_VOID  NAS_EMM_SetTinType(MMC_LMM_TIN_TYPE_ENUM_UINT32 ulTinType);
extern VOS_VOID  NAS_EMM_UpdateBearISRFlag(NAS_MML_PS_BEARER_CONTEXT_STRU  *pstBearerCtx);

extern NAS_MML_EMERGENCY_NUM_LIST_STRU*  NAS_EMM_GetEmergencyListFromMml( VOS_VOID );

extern VOS_UINT32  NAS_LMM_IsLastAttemptRegTaInTaiList(VOS_VOID);

extern VOS_UINT8  NAS_EMM_IsCampOnDamPlmn(VOS_VOID);
extern VOS_UINT8  NAS_EMM_IsDamUsimCard(VOS_VOID);

extern VOS_UINT8  NAS_EMM_IsTmoUsimCard(VOS_VOID);

extern VOS_UINT8  NAS_EMM_IsDamConfitionSatisfied(VOS_VOID);
extern VOS_VOID  NAS_EMM_SendMMCT3402LenNotify(VOS_UINT32 ulT3402Len);
extern VOS_UINT8  NAS_EMM_GetImsiHplmn
(
    VOS_UINT8             *pucImsi,
    NAS_MM_PLMN_ID_STRU   *pstHplmn
);
extern VOS_VOID  NAS_LMM_ReadRej19AtmptCntFlag(VOS_UINT8 ucRej19AtmptCntFlag);

extern VOS_VOID  NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag
(
    NAS_TMO_IMSI_HPLMN_LIST *pstTmoImsiHplmnList
);

extern VOS_VOID  NAS_LMM_ReadNvLmmCommConfigPara(VOS_VOID );

extern VOS_VOID NAS_EMM_SaveLastAttemptRegTa(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsT3411orT3402Running
(
    NAS_LMM_PTL_TI_ENUM_UINT16  *pPtlTimerId
);

extern VOS_UINT32  NAS_LMM_IsRrcConnectStatusIdle(VOS_VOID);
extern VOS_VOID  NAS_EMM_DisableLteCommonProc( VOS_VOID );

extern VOS_UINT32 NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded( VOS_VOID );
extern VOS_VOID NAS_EMM_RecogAndProcSmsOnlyCsfbNotPrefDisable( VOS_VOID );




extern VOS_VOID  NAS_EMM_SendIntraEia0ActNotify( VOS_VOID );
extern VOS_VOID  NAS_EMM_ClearEmcEsmMsg( VOS_VOID );
extern VOS_VOID  NAS_EMM_SndEmcEsmMsg( VOS_VOID );
extern VOS_VOID  NAS_EMM_SaveEmcEsmMsg
(
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_IsDeregState( VOS_VOID );
extern VOS_VOID  NAS_EMM_SendUsimStatusToRrc( LRRC_LNAS_SIM_STATUS_ENUM_UINT32  enSimStatus);
/* s00193151 begin for 自适应网络拒绝原因值 */
extern VOS_VOID NAS_LMM_AdaptRegRejCau(VOS_UINT8 *pucCause);
/* s00193151 end for 自适应网络拒绝原因值 */
extern MMC_LMM_RESULT_ID_ENUM_UINT32 NAS_EMM_GetGulPubInfo
(
    MMC_LMM_INFO_TYPE_ENUM_UINT32    ulInfoType,
    MMC_LMM_PUB_INFO_STRU           *pPubInfo
);
extern MMC_LMM_RESULT_ID_ENUM_UINT32 NAS_EMM_GetGuInfo
(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_GUMM_INFO_STRU *            pstGuInfo
);
extern VOS_VOID NAS_EMM_GetMsNetworkCapability
(
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  *pstMsNetworkCapbility
);
extern VOS_UINT8* NAS_EMM_GetUeIdTmsi(VOS_VOID);
extern NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8  NAS_EMM_GetLteCsServiceCfg(  VOS_VOID  );
extern NAS_MML_PS_BEARER_CONTEXT_STRU* NAS_EMM_GetPsBearerCtx(VOS_VOID);
extern VOS_UINT8  NAS_EMM_GetUeEutranPsDrxLen(VOS_VOID);
extern VOS_UINT8  NAS_EMM_GetNonDrxTimer(  VOS_VOID  );
extern VOS_UINT8  NAS_EMM_GetSplitPgCycleCode(  VOS_VOID  );
extern VOS_UINT8  NAS_EMM_GetSplitOnCcch(  VOS_VOID  );
extern VOS_VOID NAS_EMM_FillIEClassMark2(VOS_UINT8  *pClassMark2);
extern VOS_UINT8  NAS_EMM_GetCsAttachAllowFlg(  VOS_VOID  );
extern VOS_UINT8  NAS_EMM_GetPsAttachAllowFlg(  VOS_VOID  );
extern NAS_MML_MS_MODE_ENUM_UINT8  NAS_EMM_GetMsMode(  VOS_VOID  );
extern MMC_LMM_PLMN_CTRL_ENUM_UINT32  NAS_EMM_PlmnIdIsForbid(MMC_LMM_PLMN_ID_STRU *pstPlmn );
extern NAS_MML_REG_STATUS_ENUM_UINT8  NAS_EMM_GetPsRegStatus( VOS_VOID);
extern NAS_MML_REG_STATUS_ENUM_UINT8  NAS_EMM_GetSimType( VOS_VOID);
extern VOS_UINT32  NAS_EMM_GetCardIMSI
(
    VOS_UINT8      *pucImsi
);

extern VOS_UINT8  NAS_EMM_GetImsiHplmn
(
    VOS_UINT8             *pucImsi,
    NAS_MM_PLMN_ID_STRU   *pstHplmn
);

extern VOS_UINT32  NAS_EMM_IsServiceAvailable
(
    UICC_SERVICES_TYPE_ENUM_UINT32  enService
);



extern VOS_VOID NAS_LMM_LogPubInfo
(
    MMC_LMM_INFO_TYPE_ENUM_UINT32    ulInfoType,
    const MMC_LMM_PUB_INFO_STRU      *pPubInfo,
    MMC_LMM_RESULT_ID_ENUM_UINT32    ulRslt
);
extern VOS_VOID NAS_LMM_LogGuInfo
(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    const NAS_GUMM_INFO_STRU             *pstGuInfo,
    MMC_LMM_RESULT_ID_ENUM_UINT32        ulRslt
);
extern VOS_VOID NAS_LMM_LogTinInfo
(
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType,
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid
);

extern VOS_VOID NAS_LMM_LogMsNetworkCapabilityInfo
(
    const NAS_MML_MS_NETWORK_CAPACILITY_STRU  *pstMsNetworkCapbility
);
extern VOS_VOID NAS_LMM_LogUeIdTmsiInfo
(
    const VOS_UINT8                          *pucTmsi
);
extern VOS_VOID NAS_LMM_LogCsServiceCfgInfo
(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8   ulCsService
);
extern VOS_VOID NAS_LMM_LogAdditionUpdateRsltInfo
(
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32   enAddUpdateRslt
);
extern VOS_VOID NAS_LMM_LogPsBearerCtxInfo
(
    const NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx
);
extern VOS_VOID NAS_LMM_LogIsBearIsrActBeforeInfo
(
    VOS_UINT32      ulRslt
);
extern VOS_VOID NAS_LMM_LogEmergencyNumListInfo
(
   const NAS_MML_EMERGENCY_NUM_LIST_STRU                    *pstMmlEmerNumList,
   VOS_UINT32                                               ulSenderPid,
   VOS_UINT32                                               ulReceiverPid
);
extern VOS_VOID NAS_LMM_LogPsRegContainDrxInfo
(
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8    enPsRegisterContainDrx
);
extern VOS_VOID NAS_LMM_LogIsBearIsrActAfterInfo
(
     VOS_UINT32                          ulExistFlag
);
extern VOS_VOID NAS_LMM_LogUeEutranPsDrxLenInfo
(
    VOS_UINT8                           ucEutranDrxLen
);
extern VOS_VOID NAS_LMM_LogNonDrxTimerInfo
(
    VOS_UINT8                           ucNonDrxTimer
);
extern VOS_VOID NAS_LMM_LogDrxSplitPgCycleCodeInfo
(
    VOS_UINT8                           ucSplitPgCycleCode
);
extern VOS_VOID NAS_LMM_LogDrxSplitOnCcch
(
    VOS_UINT8                           ucSplitCcch
);
extern VOS_VOID NAS_LMM_LogClassMark2Info
(
    const VOS_UINT8  *pClassMark2
);
extern VOS_VOID NAS_LMM_LogCsAttachAllowFlgInfo
(
    VOS_UINT8                           ucCsAttachAllow
);
extern VOS_VOID NAS_LMM_LogPsAttachAllowFlgInfo
(
    VOS_UINT8                           ucCsAttachAllow
);
extern VOS_VOID NAS_LMM_LogMsMode
(
    VOS_UINT8                          ucMsMode
);
extern VOS_VOID NAS_LMM_LogPlmnIsForbid
(
    const MMC_LMM_PLMN_ID_STRU                *pstPlmn,
    VOS_UINT32                          ulRslt
);
extern VOS_VOID NAS_LMM_LogPlmnexactlyCmpFlag
(
    VOS_UINT8                          ucRslt
);
extern VOS_VOID NAS_LMM_LogPsRegStatus
(
    VOS_UINT8                          ucPsRegStatus
);
extern VOS_VOID NAS_LMM_LogSimType
(
    VOS_UINT8                          ucSimType
);
extern VOS_VOID NAS_LMM_LogCardIMSIInfo
(
    const VOS_UINT8 *pucImsi,
    VOS_UINT32      ulRslt
);
extern VOS_VOID NAS_LMM_LogUsimTestModeInfo
(
    VOS_UINT32                          ulRslt
);
extern VOS_UINT32  NAS_EMM_IsAnnexP2ConditionSatisfied(VOS_VOID);
extern VOS_UINT32  NAS_EMM_IsAnnexP4ConditionSatisfied(VOS_VOID);
extern VOS_UINT32  NAS_EMM_IsEnterRegLimitService( VOS_VOID );
extern VOS_VOID NAS_EMM_TranStateRegNormalServiceOrRegLimitService(VOS_VOID);
extern VOS_UINT32  NAS_LMM_IsRegisteredInHplmn(VOS_VOID);

extern VOS_VOID NAS_LMM_LogUsimServiceInfo
(
   VOS_UINT32     enServiceType,
   VOS_UINT32     ulRslt
);
extern VOS_VOID NAS_LMM_SndOmDsdsPreProcMsgInfo
(
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32                 enMsgType,
    VOS_UINT32                                        ulIndex
);
extern VOS_VOID NAS_LMM_SndOmDsdsSessionMsgInfo
(
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32                 enMsgType,
    MM_SESSION_TYPE_ENUM_UINT32                  enSessionType
);
extern  VOS_VOID  NAS_LMM_SendRrcDsdsBeginNotify(LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  ucSessionType);
extern  VOS_VOID  NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  ucSessionType);

extern VOS_VOID NAS_EMM_HandleHplmnRejCauseChange(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT8                           ucConfigCauseNvim
);
extern VOS_VOID NAS_EMM_HandleVplmnRejCauseChange(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT8                           ucConfigCauseNvim
);
extern VOS_VOID NAS_EMM_ResetRejCauseChangedCounter(VOS_VOID);

extern VOS_UINT32 NAS_EMM_IsNeedIgnoreHplmnAuthRej(VOS_VOID);
extern VOS_VOID NAS_EMM_ResetHplmnAuthRejCout(VOS_VOID);

extern VOS_UINT32 NAS_EMM_IsNeedAddForbTa
(
    VOS_VOID
);
extern VOS_UINT32 NAS_EMM_IsCountryChanged(VOS_VOID);

extern VOS_VOID  NAS_LMM_ReadNvDamParaCServiceAndPlmnList(VOS_VOID );
extern VOS_VOID NAS_EMM_SndOmLogUeImportantCapabilityInfo(VOS_VOID);
extern VOS_VOID NAS_EMM_SndOmLogUeIdInfo(VOS_VOID);
extern VOS_VOID NAS_EMM_SndOmLogEpsLocInfo(VOS_VOID);
extern VOS_VOID NAS_EMM_SndOmLogEpsSecContextInfo(VOS_VOID);
extern VOS_VOID NAS_EMM_SndOmLogConfigNwCauseInfo
(
    VOS_UINT8                           ucCnCause,
    VOS_UINT8                           ucModifiedCnCause,
    VOS_UINT32                          ucIsHplmn
);

extern VOS_UINT32  NAS_LMM_LteNoSubscribeIsRegisteredInHplmn(NAS_EMM_PLMN_ID_STRU  *pstPlmn);

extern VOS_VOID  NAS_LMM_ReadNvLmmSwitchPara(VOS_VOID );

extern VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType);

extern VOS_VOID  NAS_EMM_SndEsmClearAllClBearerNotify(VOS_VOID);
extern VOS_VOID  NAS_LMM_SetVoiceDomain(MMC_LMM_VOICE_DOMAIN_ENUM_UINT32     enVoiceDomain );
extern VOS_UINT8  NAS_LMM_GetImsVoiceMMEnableFlg( VOS_VOID );
extern VOS_VOID  NAS_LMM_SndOmLogImsVoiceMMEnableFlgInfo( VOS_VOID );
extern NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8  NAS_LMM_GetLteNwImsVoiceSupportFlag( VOS_VOID );
extern VOS_VOID  NAS_LMM_SndOmLogLteNwImsVoiceSupportFlagInfo( VOS_VOID );
extern NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8  NAS_LMM_GetGUNwImsVoiceSupportFlg( VOS_VOID );
extern VOS_VOID  NAS_LMM_SndOmLogGUNwImsVoiceSupportFlagInfo( VOS_VOID );
extern VOS_UINT8  NAS_LMM_GetRoamingRejectNoRetryFlg( VOS_UINT8 ucCause );
extern VOS_VOID  NAS_LMM_SndOmLogRoamingRejectNoRetryFlgInfo( VOS_UINT8 ucCause );

extern VOS_UINT32 NAS_LMM_GetGradualForbTaTimerPara(VOS_VOID);
extern VOS_UINT32 NAS_LMM_IsGradualForbidenOptimizationOpened(VOS_VOID);
extern VOS_VOID NAS_LMM_DelTaFromTempForbList(VOS_UINT32 ulIndex);
extern VOS_VOID NAS_LMM_AddNewTaWithTempTaListNotFull(NAS_MM_TA_STRU   *pstTa);
extern VOS_VOID NAS_LMM_AddNewTaInGradualForbTempTaList(NAS_MM_TA_STRU   *pstTa);
extern VOS_VOID NAS_LMM_FillTempTaInRrcNasForbTaList(LRRC_LNAS_FORB_TA_LIST_STRU *pstRrcNasForbTaList);
extern VOS_VOID NAS_LMM_FillUserSpecRrcNasForbTaListWithTempTa
(
    const NAS_MM_PLMN_ID_STRU  *pstPlmnId,
    NAS_MM_TA_LIST_STRU        *pstRrcTaList
);
extern VOS_UINT32 NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(VOS_UINT32 ulTimerLen);
extern VOS_VOID NAS_LMM_GradualForbParaInit(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU stNvGradualForbPara);
extern VOS_VOID NAS_LMM_GradualForbTaListInit(VOS_VOID);
extern VOS_VOID NAS_LMM_StopAllGradualForbiddenTimer(VOS_VOID);
extern VOS_VOID NAS_LMM_ClearAllGradualForbTaList(VOS_VOID);
extern NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 NAS_LMM_AddTaInGradualForbTempTaList(NAS_MM_TA_STRU   *pstTa);
extern NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 NAS_LMM_UpdateGradualForbTempTaList(VOS_VOID);
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchGradualForbTaList(const NAS_MM_TA_STRU  *pstTa, VOS_UINT32 *pulIndex);
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TimerParaMatchGradualForbTaList(VOS_UINT32 ulOpid, VOS_UINT32 *pulIndex);
extern VOS_VOID NAS_LMM_GetGradualForbTaWithIndex(VOS_UINT32 ulIndex, NAS_MM_TA_STRU *pstTa);
extern VOS_VOID  NAS_LMM_AddTaInForbListWithTauRejCauseVal15(VOS_UINT32 ulIsWithExtCase,
                                                                        VOS_UINT32 *pulIsNeedExecLteNotAllow);
extern VOS_VOID  NAS_LMM_AddTaInForbListWithAttRejCauseVal15(VOS_UINT32 ulIsWithExtCase,
                                                                         VOS_UINT32 *pulIsNeedExecLteNotAllow);
extern VOS_VOID NAS_LMM_DelCurrTaFromGradualForbTaList(NAS_MM_TA_STRU   *pstCurrTa);
extern VOS_VOID NAS_LMM_UpdateGradualForbListWithTauRejCause13(NAS_MM_TA_STRU   *pstCurrTa);
extern VOS_UINT32 NAS_LMM_ExistTaInTempTaListWithForbTimerRunning(VOS_VOID);
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchTempTaListWithForbTimerRunning
(
    const NAS_MMC_TA_STRU                    *pstTa
);

extern NAS_LMM_REG_DOMAIN_ENUM_UINT32 NAS_LMM_GetEmmInfoRegDomain(VOS_VOID);
extern VOS_VOID NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_ENUM_UINT32 enRegDomainDst);

extern VOS_UINT8  NAS_LMM_IsMsgContainsSMS(VOS_UINT32 ulMsgSize, VOS_UINT8 *pstMsg);
extern VOS_UINT32  NAS_EMM_IsNotIdle(VOS_VOID);

extern VOS_UINT32     g_ulEmmTauReqSndFailFlag;


extern VOS_UINT32  NAS_EMM_IsEhrpdOr1XRatExist(VOS_VOID);

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

#endif /* end of MapsTemplate.h*/
