

/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmAttDetInclude.h
    Description : EMM的C文件要包含的头文件
    History     :
      1.  leili  132387 2008-10-08 Initial

******************************************************************************/

#ifndef __NASEMMATTDETINCLUDE_H__
#define __NASEMMATTDETINCLUDE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "PsCommonDef.h"
#include    "LRrcLNasInterface.h"

#include    "NasLmmPubMIntraMsg.h"
#include    "NasLmmPubMFsm.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmPubUEntry.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "NasEmmPubUMain.h"
#include    "NasLmmPubMEntry.h"
#include    "NasLmmPubMOm.h"
#include    "NasLmmPublic.h"
#include    "NasLmmPubMTimer.h"
#include    "NasLmmPubMNvim.h"

#include    "AppMmInterface.h"
#include    "EmmEsmInterface.h"
#include    "EmmTcInterface.h"
#include    "NasEmmMrrcPubInterface.h"
#include    "NasEmmcEmmInterface.h"
#include    "NasEmmTauSerInclude.h"

#include    "NasEmmMrrcPubInterface.h"
#include    "NasEmmPlmnInterface.h"

#include    "NasEmmAttach.h"
#include    "NasEmmAttachAppMsgProcess.h"
#include    "NasEmmAttachCnMsgProcess.h"
#include    "NasEmmAttachEsmMsgProcess.h"
/*#include    "NasEmmAttDetMrrcMsgProcess.h"*/ /*l00258641 删除没有用到的头文件*/
#include    "NasEmmDetach.h"
#include    "NasEmmDetachAppMsgProcess.h"
#include    "NasEmmDetachCnMsgProcess.h"
#include    "NasEmmGutiPubInterface.h"
#include    "NasEmmMrrc.h"
#include    "NasCommPrint.h"



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

#define NAS_EMM_AD_BIT_SLCT                                         1
#define NAS_EMM_AD_BIT_NO_SLCT                                      0

#define NAS_EMM_AD_TLV_TAG_1_BYTE                                   1   /* TAG本身占的一个字节 */
#define NAS_EMM_AD_LV_LENGTH_1_BYTE                                 1   /* 长度本身占的一个字节 */

#define NAS_EMM_AD_LEN_CN_MSG_PD_SHT                                1
#define NAS_EMM_AD_LEN_CN_MSG_MT                                    1
#define NAS_EMM_AD_LEN_CN_MSG_AT_NKSI                               1

#define NAS_EMM_AD_LEN_CN_MSG_IMSI                                  (*(NAS_EMM_GLO_AD_GetImsi())+1)
#define NAS_EMM_AD_LEN_CN_MSG_IMEI                                  (*(NAS_EMM_GLO_AD_GetImei())+1)

#define NAS_EMM_AD_LEN_CN_MSG_MSNW_CAPA                             (*(NAS_EMM_GLO_AD_GetMsNetCapa())+1)
#define NAS_EMM_AD_ADDITIONAL_GUTI_IEI                              0x50
#define NAS_EMM_AD_TAI_IEI                                          0x52
#define NAS_EMM_AD_PTMSI_SIGNATURE_IEI                              0x19

#define NAS_EMM_AD_ADDITION_GUTI_IEI                                0x50
#define NAS_EMM_AD_LAI_IEI                                          0x13
#define NAS_EMM_AD_DRX_IEI                                          0x5C
#define NAS_EMM_AD_MS_NET_CAPA_IEI                                  0x31
#define NAS_EMM_AD_MS_CLASSMARK2_IEI                                0x11
#define NAS_EMM_AD_MS_CLASSMARK3_IEI                                0x20
#define NAS_EMM_AD_SUPPORT_CODECS_IEI                               0x40
#define NAS_EMM_AD_VOICE_DOMAIN_AND_USAGE_SETTING_IEI               0x5D

#define NAS_EMM_AD_TMSI_BASED_NRI_CONTAINER_IEI                     0x10

#define NAS_EMM_AD_LEN_TMSI_BASED_NRI_CONTAINER                     2


#define NAS_EMM_AD_LEN_MSG_ID                                       4
#define NAS_EMM_AD_LEN_IE_MSGSIZE_OF_NAS_MSG_STRU                   4
#define NAS_EMM_AD_LEN_CN_MSG_DET_TYPE                              1
#define NAS_EMM_AD_LEN_PLMN_ID                                      3
#define NAS_EMM_AD_LEN_MS_CLASSMARK2                                3
#define NAS_EMM_AD_LEN_MS_CLASSMARK3                                32  /*V的长度，不包含TL*/
#define NAS_EMM_AD_LEN_VOICE_DOMAIN                                 1

#define NAS_EMM_AD_LEN_GUTI                                         0x0B
#define NAS_EMM_AD_ID_GUTI                                          0xF6

#define NAS_EMM_CN_MSG_ATTACH_TYPE_PS       0x01                /* 0000  0001   PS attach   */
#define NAS_EMM_CN_MSG_ATTACH_TYPE_PS_CS    0x02                /* 0000  0011   Combined PS/CS attach   */
#define NAS_EMM_NKSI_NO_KEY                 0x70


#define NAS_EMM_AD_MOVEMENT_0_BIT           0
#define NAS_EMM_AD_MOVEMENT_1_BIT           1
#define NAS_EMM_AD_MOVEMENT_2_BITS           2
#define NAS_EMM_AD_MOVEMENT_3_BITS          3
#define NAS_EMM_AD_MOVEMENT_4_BITS          4
#define NAS_EMM_AD_MOVEMENT_5_BITS          5
#define NAS_EMM_AD_MOVEMENT_6_BITS          6
#define NAS_EMM_AD_MOVEMENT_7_BITS          7
#define NAS_EMM_AD_MOVEMENT_8_BITS          8
#define NAS_EMM_AD_MOVEMENT_16_BITS         16
#define NAS_EMM_AD_MOVEMENT_24_BITS         24
#define NAS_EMM_DEFAULT_CID                 0

#define NAS_EMM_MAX_MT_DETACH_ACC_TX_NUM    1
#define NAS_EMM_HITH_BYTE                   0x80
#define NAS_EMM_HITH2_BYTE                  0xC0

#define NAS_EMM_DAM_ATTACH_REJ19_MAX_CNT    3
/*========================= EMM全局变量的宏简写 =========================*/

#define NAS_EMM_GLO_AD_GetAttCtrlAddr()             (&g_stEmmAttCtrl)
#define NAS_EMM_GLO_AD_GetDetCtrlAddr()             (&g_stEmmDetCtrl)
#define NAS_EMM_GLO_AD_GetInfoCtrlAddr()            (&g_stEmmInfo)

/*NAS_EMM_PUB_INFO*/
#define NAS_EMM_GLO_AD_OP_NetInfo()                 ((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->bitOpNetInfo)
#define NAS_EMM_GLO_AD_OP_SecurityPara()            ((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->bitOpSecurityPara)
#define NAS_EMM_GLO_AD_OP_MsNetCap()                ((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->bitOpMsNetCap)
#define NAS_EMM_GLO_AD_OP_MsClassMark()             ((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->bitOpClassMark)
#define NAS_EMM_GLO_AD_OP_SupCodecList()            ((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->bitOpSupCodecList)

#define NAS_EMM_GLO_AD_GetNwInfoAddr()              (&((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->stNetInfo))
#define NAS_EMM_GLO_AD_GetSecuParaAddr()            (&((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->stSecurityPara))
#define NAS_EMM_GLO_AD_GetUeIdAddr()                (&((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->stMmUeId))
#define NAS_EMM_GLO_AD_GetMsNetCapaAddr()           (&((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->stMsNetCap))
#define NAS_EMM_GLO_AD_GetMsClassMarkAddr()         (&((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->stMsClassMark))
#define NAS_EMM_GLO_AD_GetSupCodecListAddr()        (&((NAS_EMM_GLO_AD_GetInfoCtrlAddr())->stSupCodecList))

/*NAS_EMM_UE_ID信息*/
#define NAS_EMM_GLO_AD_OP_GUTI()                    ((NAS_EMM_GLO_AD_GetUeIdAddr())->bitOpGuti)
#define NAS_EMM_GLO_AD_OP_IMSI()                    ((NAS_EMM_GLO_AD_GetUeIdAddr())->bitOpImsi)
#define NAS_EMM_GLO_AD_OP_TMSI()                    ((NAS_EMM_GLO_AD_GetUeIdAddr())->bitOpTmsi)
#define NAS_EMM_GLO_AD_GetGutiAddr()                (&((NAS_EMM_GLO_AD_GetUeIdAddr())->stGuti))
#define NAS_EMM_GLO_AD_GetImsi()                    ((NAS_EMM_GLO_AD_GetUeIdAddr())->aucImsi)
#define NAS_EMM_GLO_AD_GetImei()                    ((NAS_EMM_GLO_AD_GetUeIdAddr())->aucImei)

/*网络信息*/

#define NAS_EMM_GLO_AD_OP_PRESNETID()               ((NAS_EMM_GLO_AD_GetNwInfoAddr())->bitOpPresentNetId)
#define NAS_EMM_GLO_AD_OP_TAILIST()                 ((NAS_EMM_GLO_AD_GetNwInfoAddr())->bitOpTaiList)
#define NAS_EMM_GLO_AD_OP_FORBTAFORROAM()           ((NAS_EMM_GLO_AD_GetNwInfoAddr())->bitOpFoibTaForRoam)
#define NAS_EMM_GLO_AD_OP_FORBTAFORRPOS()           ((NAS_EMM_GLO_AD_GetNwInfoAddr())->bitOpFoibTaForRpos)
#define NAS_EMM_GLO_AD_GetPresentNetIdAddr()        (&((NAS_EMM_GLO_AD_GetNwInfoAddr())->stPresentNetId))
#define NAS_EMM_GLO_AD_GetLastRegNetIdAddr()        (&((NAS_EMM_GLO_AD_GetNwInfoAddr())->stLastRegNetId))
#define NAS_EMM_GLO_AD_GetEPlmnListAddr()           (&((NAS_EMM_GLO_AD_GetNwInfoAddr())->stEPlmnList))
#define NAS_EMM_GLO_AD_GetTaiListAddr()             (&((NAS_EMM_GLO_AD_GetNwInfoAddr())->stTaiList))
#define NAS_EMM_GLO_AD_GetForbTaiListForRoamAddr()  (&((NAS_EMM_GLO_AD_GetNwInfoAddr())->stForbTaForRoam))
#define NAS_EMM_GLO_AD_GetForbTaiListForRposAddr()  (&((NAS_EMM_GLO_AD_GetNwInfoAddr())->stForbTaForRpos))

/*当前网络信息*/
#define NAS_EMM_GLO_AD_OP_PRESPLMNID()              ((NAS_EMM_GLO_AD_GetPresentNetIdAddr())->bitOpPlmnId)
#define NAS_EMM_GLO_AD_OP_PRESLAC()                 ((NAS_EMM_GLO_AD_GetPresentNetIdAddr())->bitOpLac)
#define NAS_EMM_GLO_AD_OP_PRESCELLID()              ((NAS_EMM_GLO_AD_GetPresentNetIdAddr())->bitOpCellId)
#define NAS_EMM_GLO_AD_GetPresPlmnIdAddr()          (&((NAS_EMM_GLO_AD_GetPresentNetIdAddr())->stPlmnId))
#define NAS_EMM_GLO_AD_GetPresTacAddr()             (&((NAS_EMM_GLO_AD_GetPresentNetIdAddr())->stTac))
#define NAS_EMM_GLO_AD_GetPresLacAddr()             (&((NAS_EMM_GLO_AD_GetPresentNetIdAddr())->stLac))
#define NAS_EMM_GLO_AD_GetPresCellId()              ((NAS_EMM_GLO_AD_GetPresentNetIdAddr())->ulCellId)

/*上次注册的网络信息*/
#define NAS_EMM_GLO_AD_OP_LASTREGPLMNID()           ((NAS_EMM_GLO_AD_GetLastRegNetIdAddr())->bitOpPlmnId)
#define NAS_EMM_GLO_AD_OP_LASTREGLAC()              ((NAS_EMM_GLO_AD_GetLastRegNetIdAddr())->bitOpLac)
#define NAS_EMM_GLO_AD_OP_LASTREGCELLID()           ((NAS_EMM_GLO_AD_GetLastRegNetIdAddr())->bitOpCellId)
#define NAS_EMM_GLO_AD_GetLastRegPlmnIdAddr()       (&((NAS_EMM_GLO_AD_GetLastRegNetIdAddr())->stPlmnId))
#define NAS_EMM_GLO_AD_GetLastRegTacAddr()          (&((NAS_EMM_GLO_AD_GetLastRegNetIdAddr())->stTac))
#define NAS_EMM_GLO_AD_GetLastRegLacAddr()          (&((NAS_EMM_GLO_AD_GetLastRegNetIdAddr())->stLac))
#define NAS_EMM_GLO_AD_GetLastRegCellIdAddr()       (&((NAS_EMM_GLO_AD_GetLastRegNetIdAddr())->ulCellId))


/*SECURITY PARA信息*/
#define NAS_EMM_GLO_AD_OP_KSISN()                   ((NAS_EMM_GLO_AD_GetSecuParaAddr())->bitOpKsiSn)
#define NAS_EMM_GLO_AD_OP_NKSI()                    ((NAS_EMM_GLO_AD_GetSecuParaAddr())->bitOpNksi)
#define NAS_EMM_GLO_AD_GetNksiAddr()                (&((NAS_EMM_GLO_AD_GetSecuParaAddr())->stNksi))

/*MS net capability信息*/
#define NAS_EMM_GLO_AD_GetMsNetCapa()               ((NAS_EMM_GLO_AD_GetMsNetCapaAddr())->aucMsNetCap)


/*上次注册的TAC、LAC和PLMN ID信息*/
#define NAS_EMM_GLO_AD_GetLastRegTac()              ((NAS_EMM_GLO_AD_GetLastRegTacAddr())->ucTac)
#define NAS_EMM_GLO_AD_GetLastRegTacCnt()           ((NAS_EMM_GLO_AD_GetLastRegTacAddr())->ucTacCnt)
#define NAS_EMM_GLO_AD_GetLastRegLac()              ((NAS_EMM_GLO_AD_GetLastRegLacAddr())->ucLac)
#define NAS_EMM_GLO_AD_GetLastRegLacCnt()           ((NAS_EMM_GLO_AD_GetLastRegLacAddr())->ucLacCnt)
#define NAS_EMM_GLO_AD_GetLastRegPlmnId()           ((NAS_EMM_GLO_AD_GetLastRegPlmnIdAddr())->aucPlmnId)





/*GUTI信息*/
#define NAS_EMM_GLO_AD_GetGutiHeaderAddr()          (&((NAS_EMM_GLO_AD_GetGutiAddr())->stGutiHead))
#define NAS_EMM_GLO_AD_GetMmeGroupIdAddr()          (&((NAS_EMM_GLO_AD_GetGutiAddr())->stMmeGroupId))
#define NAS_EMM_GLO_AD_GetMmeCodeAddr()             (&((NAS_EMM_GLO_AD_GetGutiAddr())->stMmeCode))
#define NAS_EMM_GLO_AD_GetMTmsiAddr()               (&((NAS_EMM_GLO_AD_GetGutiAddr())->stMTmsi))
#define NAS_EMM_GLO_AD_GetGutiPlmnIdAddr()          (&((NAS_EMM_GLO_AD_GetGutiAddr())->stPlmnId))

#define NAS_EMM_GLO_AD_GetLen()                     ((NAS_EMM_GLO_AD_GetGutiHeaderAddr())->ucLenth)
#define NAS_EMM_GLO_AD_GetOeToi()                   ((NAS_EMM_GLO_AD_GetGutiHeaderAddr())->ucOeToi)
#define NAS_EMM_GLO_AD_GetGutiPlmn()                ((NAS_EMM_GLO_AD_GetGutiPlmnIdAddr())->aucPlmnId)
#define NAS_EMM_GLO_AD_GetMmeGroupId()              ((NAS_EMM_GLO_AD_GetMmeGroupIdAddr())->ucGroupId)
#define NAS_EMM_GLO_AD_GetMMeGroupIdCnt()           ((NAS_EMM_GLO_AD_GetMmeGroupIdAddr())->ucGroupIdCnt)
#define NAS_EMM_GLO_AD_GetMMeCode()                 ((NAS_EMM_GLO_AD_GetMmeCodeAddr())->ucMmeCode)
#define NAS_EMM_GLO_AD_GetMTmsi()                   ((NAS_EMM_GLO_AD_GetMTmsiAddr())->ucMTmsi)
#define NAS_EMM_GLO_AD_GetMTmsiCnt1()               ((NAS_EMM_GLO_AD_GetMTmsiAddr())->ucMTmsiCnt1)
#define NAS_EMM_GLO_AD_GetMTmsiCnt2()               ((NAS_EMM_GLO_AD_GetMTmsiAddr())->ucMTmsiCnt2)
#define NAS_EMM_GLO_AD_GetMTmsiCnt3()               ((NAS_EMM_GLO_AD_GetMTmsiAddr())->ucMTmsiCnt3)


/* CLASSMARK信息 */
#define NAS_EMM_GLO_AD_OP_CLASSMARK1()              ((NAS_EMM_GLO_AD_GetMsClassMarkAddr())->bitOpClassMark1)
#define NAS_EMM_GLO_AD_OP_CLASSMARK2()              ((NAS_EMM_GLO_AD_GetMsClassMarkAddr())->bitOpClassMark2)
#define NAS_EMM_GLO_AD_OP_CLASSMARK3()              ((NAS_EMM_GLO_AD_GetMsClassMarkAddr())->bitOpClassMark3)

#define NAS_EMM_GLO_AD_GetCLASSMARK1Addr()          (&((NAS_EMM_GLO_AD_GetMsClassMarkAddr())->stClassMark1))
#define NAS_EMM_GLO_AD_GetCLASSMARK2Addr()          (&((NAS_EMM_GLO_AD_GetMsClassMarkAddr())->stClassMark2))
#define NAS_EMM_GLO_AD_GetCLASSMARK3Addr()          (&((NAS_EMM_GLO_AD_GetMsClassMarkAddr())->stClassMark3))

/* SUPPORT CODEC LIST */

#define NAS_EMM_GLO_AD_OP_LAI_IS_VALID()            ((NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_LASTREGPLMNID()) && \
                                                    (NAS_EMM_AD_BIT_SLCT == NAS_EMM_GLO_AD_OP_LASTREGLAC()))


#define NAS_EMM_GLO_AD_GetAttAtmpCnt()              ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttAtmpCnt)

#define NAS_EMM_GLO_AD_GetAttRej19AtmpCnt()         ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttRej19AtmpCnt)



#define NAS_EMM_GLO_AD_GetAttCau()                  ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttCause)
#define NAS_EMM_GLO_AD_GetAttRejCau()               ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttRejCause)
#define NAS_EMM_GLO_AD_GetAttRejEsmCau()               ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttRejEsmCause)
#define NAS_EMM_GLO_AD_OP_GetAttRejEmmExtCau()       ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ulBitOpAttExtCause)
#define NAS_EMM_GLO_AD_GetAttRejEmmExtCau()          ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttRejExtendedEmmCause)
#define NAS_EMM_GLO_AD_GetEsmMsgAddr()               (&((NAS_EMM_GLO_AD_GetAttCtrlAddr())->stEsmMsg))
#define NAS_EMM_GLO_AD_GetEsmMsgContentAddr()        ((NAS_EMM_GLO_AD_GetEsmMsgAddr())->aucMsg)
#define NAS_EMM_GLO_AD_OP_ESM_MSG()                  ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucBitOpStSmMsg)
#define NAS_EMM_GLO_AD_GetAttRslt()                  ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttRslt)
#define NAS_EMM_GLO_AD_SetAttRslt(AttRslt)          (((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucAttRslt) = (AttRslt) )
#define NAS_EMM_GLO_AD_GetAttClRegStatus()               ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->enClAttRegStatus)
#define NAS_EMM_GLO_AD_SetAttClRegStatus(AttRegStatus)  (((NAS_EMM_GLO_AD_GetAttCtrlAddr())->enClAttRegStatus) = (AttRegStatus))
#define NAS_EMM_GLO_AD_OP_GetEmmCau()               ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ulBitOpEmmCau )
#define NAS_EMM_GLO_AD_GetEmmCau()                  ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucEMMCause)

#define NAS_EMM_GLO_AD_OP_GetLai()                  ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ulBitOpLai)
#define NAS_EMM_GLO_AD_GetLaiAddr()                 (&((NAS_EMM_GLO_AD_GetAttCtrlAddr())->stLai))

#define NAS_EMM_GLO_AD_OP_GetMsId()                 ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ulBitOpMsId)
#define NAS_EMM_GLO_AD_GetMsIdAddr()                (&((NAS_EMM_GLO_AD_GetAttCtrlAddr())->stMsId))


/* h41410 CHANGE for ue mode */
/* 改到 NAS_LMM_PUB_INFO_STRU 中定义
#define NAS_EMM_GLO_AD_GetUsgSetting()              ((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucUsageSetting)
#define NAS_EMM_GLO_AD_SetUsgSetting(ucUgSet)       (((NAS_EMM_GLO_AD_GetAttCtrlAddr())->ucUsageSetting) = (ucUgSet))
*/
#define NAS_EMM_GLO_AD_GetUsgSetting()              (NAS_LMM_GetEmmInfoUeCenter())
#define NAS_EMM_GLO_AD_SetUsgSetting(ulUgSet)       (NAS_EMM_GLO_AD_GetUsgSetting() = (ulUgSet))
/* h41410 CHANGE for ue mode */



#define NAS_EMM_GLO_AD_GetDetAtmpCnt()              ((NAS_EMM_GLO_AD_GetDetCtrlAddr())->ucDetachAtmpCnt)
#define NAS_EMM_GLO_AD_GetDetMode()                 ((NAS_EMM_GLO_AD_GetDetCtrlAddr())->ucDetachMode)
#define NAS_EMM_GLO_AD_GetDetTypeMo()               ((NAS_EMM_GLO_AD_GetDetCtrlAddr())->ulDetachTypeMo)
#define NAS_EMM_GLO_AD_GetMtDetachAccTxCnt()        ((NAS_EMM_GLO_AD_GetDetCtrlAddr())->ucMtDetachAccTxCnt)
#define NAS_EMM_GLO_AD_GetUsimPullOutFlag()         ((NAS_EMM_GLO_AD_GetDetCtrlAddr())->ucUsimPollOutFlag)

#define NAS_EMM_GLO_AD_GetAttGutiAddr()             (&((NAS_EMM_GLO_AD_GetAttCtrlAddr())->stGuti))

#define NAS_EMM_GLO_AD_OP_GetDetEmmCau()               ((NAS_EMM_GLO_AD_GetDetCtrlAddr())->ulBitOpEmmCau )
#define NAS_EMM_GLO_AD_GetDetEmmCau()                  ((NAS_EMM_GLO_AD_GetDetCtrlAddr())->ucEmmCause)



#define NAS_EMM_AD_CUR_MAIN_STAT              NAS_LMM_GetEmmCurFsmMS()
#define NAS_EMM_AD_CUR_SUB_STAT               NAS_LMM_GetEmmCurFsmSS()


#define NAS_EMM_COMP_AD_APP_PS_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_APP;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }

#define NAS_EMM_COMP_AD_ESM_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ESM;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

#define NAS_EMM_STK_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = MAPS_STK_PID;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

#define NAS_EMM_COMP_AD_TC_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_TC;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }


#define NAS_EMM_COMP_AD_INTRA_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_MM;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

#define NAS_EMM_COMP_AD_MMC_PS_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = WUEPS_PID_MMC;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }
/* Added by w00209181 for 搜网优化 2015-05-30 */
#define NAS_EMM_COMP_AD_CSS_PS_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_CSS;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

/* Added by w00209181 for 搜网优化 2015-05-30 */

/*#define NAS_EMM_PrintMsgOut((NAS_LMM_INTRA_MSG_STRU *)pMsg);
 */


#define NAS_EMM_AD_SEND_INTRA_MSG(pMsg) \
        {\
            if(NAS_EMM_OK !=  NAS_LMM_SendIntraMsg((pMsg)))\
            {\
                NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_SEND_MSG  ERR!!");\
            }\
        }

#define NAS_EMM_COMP_AD_IMSA_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_IMSA;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

/* 计算组合状态,低两字节有效: 0x0000_0x主_0x子 */ /*HLF  2*/
#define NAS_EMM_AD_PUB_COMP_EMMSTATE(ucMainStat, ucSubStat)\
        ((((VOS_UINT32)(ucMainStat)) << NAS_EMM_AD_MOVEMENT_16_BITS) | (ucSubStat))



#define NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS,EMM_SS) \
        (\
            NAS_EMM_AD_PUB_COMP_EMMSTATE(EMM_MS,EMM_SS) != \
            NAS_EMM_AD_PUB_COMP_EMMSTATE(NAS_EMM_AD_CUR_MAIN_STAT, NAS_EMM_AD_CUR_SUB_STAT)\
        )



/* 内存拷贝宏定义 */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/



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

#endif



























