/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmPlmnInterface.h
  Description     : NasEmmPlmnInterface.h header file
  History         :
     1.lining 00141619       2008-11-13     Draft Enact
     2.leili 00132387        2009-02-20 问题单BA8D00962
     描述:在REG + REG_WAIT_MRRC_REL_CNF状态下增加了收到MrrcRelCnf消息的处理
******************************************************************************/
#ifndef __NASEMMPLMNINTERFACE_H__
#define __NASEMMPLMNINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


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

#define  NAS_EMM_REBOOT_TYPE_ESM_ABNORMAL                              1
#define  NAS_EMM_REBOOT_TYPE_RRC_REPORT_ERR_IND                        2

#define  NAS_EMM_REBOOT_TYPE_SYSCFG_SUSPEND_ECM_FAIL                   3
#define  NAS_EMM_REBOOT_TYPE_SYSCFG_SUSPEND_RRC_FAIL                   4

#define  NAS_EMM_REBOOT_TYPE_RRC_SUSPEND_ECM_FAIL                      5
#define  NAS_EMM_REBOOT_TYPE_RRC_SUSPEND_WAIT_MMC_END_FAIL             6

#define  NAS_EMM_REBOOT_TYPE_MMC_SUSPEND_ECM_FAIL                      7
#define  NAS_EMM_REBOOT_TYPE_MMC_SUSPEND_RRC_FAIL                      8

#define  NAS_EMM_REBOOT_TYPE_RRC_RESUME_ECM_FAIL                       9

#define  NAS_EMM_REBOOT_TYPE_RRC_START_FAIL                            10
#define  NAS_EMM_REBOOT_TYPE_RRC_START_WAIT_RRC_TIMEOUT_FAIL           11





/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
 枚举名: NAS_LMM_MMC_START_RAT_TYPE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:待机类型取值
  ------------------------------------------------------------------------
  bit8    |  bit7  | bit6  | bit5  | bit4     | bit3     |  bit2  | bit1
  ------------------------------------------------------------------------
   RSV    |  RSV  |   RSV  |  RSV  |  LTE_TDD | LTE_FDD  |  UMTS  |  GSM
  ----------------------------------------------------------------------
*****************************************************************************/
enum    NAS_LMM_MMC_INF_START_RAT_TYPE_ENUM
{
    NAS_LMM_MMC_START_RAT_NONE          = 0x00,
    NAS_LMM_MMC_START_RAT_GSM           = 0x01,
    NAS_LMM_MMC_START_RAT_UMTS          = 0x02,
    NAS_LMM_MMC_START_RAT_LTE_FDD       = 0x04,
    NAS_LMM_MMC_START_RAT_LTE_TDD       = 0x08,

    NAS_LMM_MMC_START_RAT_BUTT
};
typedef VOS_UINT8   NAS_LMM_MMC_INF_START_RAT_TYPE_ENUM_UINT8;







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

/* 开机相关流程处理 Function */
extern VOS_UINT32    NAS_EMM_MsNullSsWaitAppStartReqMsgAppStartReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
/*
extern VOS_UINT32    NAS_EMM_MsNullSsWaitingUsimReadyMsgAppStartReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
*/
extern VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgAppStartReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32    NAS_EMM_WhenStopingThenMsgAppStartReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

extern VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStartCnfMsgMmcStartCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStartCnfMsgTimerExp(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32    NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcStartCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32    NAS_EMM_MsNullSsWaitRrcStartCnfMsgTimerExp(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

/*extern VOS_UINT32  NAS_EMM_MsNullSsWaitRrcStartCnfMsgRrcErrInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );*/
extern VOS_VOID  NAS_EMM_ProcRrcStopRslt( VOS_VOID );
extern VOS_UINT32  NAS_EMM_MsNullSsWaitSwitchOffProcMsgRrcRelInd(VOS_VOID);

extern VOS_UINT32  NAS_EMM_MsNullSsAnyStateMsgRrcErrInd(
                     VOS_UINT32                              ulMsgId,
                     VOS_VOID                                *pMsg );


/* 关机相关流程处理 Function */
extern VOS_UINT32    NAS_EMM_MsNullSsAnyReadUsimStateMsgAppStopReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32    NAS_EMM_MsNotNullNotRegMsgAppStopReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStopCnfMsgMmcStopCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                         *pMsg );
extern VOS_UINT32    NAS_EMM_MsNullSsWaitMmcStopCnfMsgTimerExp(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                         *pMsg );
extern VOS_UINT32    NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcStopCnf(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

/*extern VOS_UINT32  NAS_EMM_MsNullSsWaitRrcStopCnfMsgRrcErrInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );*/

extern VOS_UINT32    NAS_EMM_MsNullSsWaitRrcStopCnfMsgTimerExp(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

/* 关机相关流程处理 Function */
extern VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgMmcPlmnInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32    NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcPlmnInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsg
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraMrrcRelInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsg
);
extern VOS_UINT32    NAS_EMM_MsDeregSsNoImsiMsgMmcPlmnInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg);
extern VOS_UINT32  NAS_EMM_MsRegSsNormalServiceMsgMrrcRelInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

extern VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgMmcCoverageLostInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32 NAS_EMM_MsRegSsRegAttemptUpdateMmMsgMmcCoverageLostInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsg
);
extern VOS_UINT32    NAS_EMM_MsDeregSsAttemptToAttachMsgMmcSysInfoInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );
extern VOS_UINT32   NAS_EMM_MsDeregSsNormalSrvMsgMmcSysInfoInd(
                                    VOS_UINT32              ulMsgId,
                                    VOS_VOID               *pMsg );
extern VOS_UINT32 NAS_EMM_MsDeregSsLimitSrvMsgMmcSysInfoInd(
                                    VOS_UINT32              ulMsgId,
                                    VOS_VOID               *pMsg );
extern VOS_UINT32 NAS_EMM_MsDeregSsPlmnSearchMsgMmcSysInfoInd(
                                            VOS_UINT32              ulMsgId,
                                            VOS_VOID               *pMsg );
extern VOS_UINT32 NAS_EMM_MsDeregSsNoCellAvailMsgMmcSysInfoInd(
                                            VOS_UINT32              ulMsgId,
                                            VOS_VOID               *pMsg );

extern VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgRrcErrInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

extern VOS_UINT32    NAS_EMM_MsNullSsWaitSwitchOffMsgRrcRelInd(
                        VOS_UINT32                              ulMsgId,
                        VOS_VOID                                *pMsg );

extern VOS_UINT32     NAS_EMM_MsNullSsWaitSwitchOffMsgRrcErrInd(
                        VOS_UINT32                              ulMsgId,
                        VOS_VOID                                *pMsg );

extern VOS_UINT32    NAS_EMM_MsNotNullSsAnyStateMsgRrcPagingInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

extern VOS_UINT32    NAS_EMM_MsTauInitSsTauWaitCnTauCnfMsgRrcPagingInd(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsg
);
extern VOS_UINT32    NAS_EMM_MsSerInitSsSerWaitCnSerCnfMsgRrcPagingInd(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsg
);

extern VOS_VOID    NAS_EMM_ProcLocalStop( VOS_VOID );
/*extern VOS_UINT32  NAS_EMM_MsNullSsWaitRrcStartCnfProcMsgTimerExp(VOS_UINT32 ulErrCause);*/
#if (VOS_OS_VER != VOS_WIN32)
#define NAS_EMM_SendMmcErrInd(ulErrTpye)  (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( ulErrTpye, (__LINE__), (THIS_FILE_ID) )
#else
extern VOS_VOID NAS_EMM_SendMmcErrInd(VOS_UINT32 ulErrTpye);
#endif



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

#endif /* end of NasEmmPlmnInterface.h */
