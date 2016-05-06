/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafDrvAgentMsgProc.h
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年10月4日
  最近修改   :
  功能描述   : DRVAGENTMsgProc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DRVAGENTMSGPROC_H__
#define __DRVAGENTMSGPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "TafDrvAgent.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AT_AUTHVER_ONE                  (1)                                     /* SIMLock manager版本号*/
                                                                                /*1表示1.0,版本采用早期的版本进行密码获取*/
#define AT_AUTHVER_TWO                  (2)                                     /* SIMLock manager版本号*/
                                                                                /*2表示2.0版本,采取本次优化之后的版本获取密码*/
#define AT_AUTHVER_THREE                (3)                                     /* SIMLock manager版本号*/
                                                                               /*3表示2.1版本,采取本次优化之后的版本获取密码*/
#define EF_IMSI_ID                      (0x6F07)                                /* EFIMSI */



/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern VOS_UINT8                        g_ucGcfInd;


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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 DRVAGENT_RcvDrvAgentMsidQryReq(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentGcfInd(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentGasMntnCmd(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentVertimeQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentAppdmverReq(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentYjcxSet(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentYjcxQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentHardwareQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentFullHardwareQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentSetNvRestore(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentQryNvRestoreRst(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentNvRestoreManuDefault(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentDloadInfoReq(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentFlashInfoQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentAuthorityVerQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentAuthorityIdQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentAuthVerQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentGodloadSet(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentPfverQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentSdloadSet(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentSdRebootReq(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentAuthorityVerReq(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentDloadVerQryReq(VOS_VOID *pMsg);

/* Added by 傅映君/f62575 for E5宏开关打开后编译问题, 2011/11/15, begin */
VOS_UINT32 DRVAGENT_RcvDrvAgentCpuloadQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentMfreelocksizeQry(VOS_VOID *pMsg);
/* Added by 傅映君/f62575 for E5宏开关打开后编译问题, 2011/11/15, end */


VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceGpioplSet(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceGpioplQry(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceDatalockSet(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceTbatvoltQry(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceTmodeSet(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceVersionQry(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceSecuBootQry(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceFchanSet(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceSfeatureQry(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentDeviceProdtypeQry(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentAdcSet(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentSetRxdiv(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentSetSimlock(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentQryRxdiv(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_CheckRxdivOrRxpriParaIfSupported(
    VOS_UINT16                         *pusSetBands,
    VOS_UINT16                          usBands,
    VOS_UINT32                          ulSetLowBands,
    VOS_UINT32                          ulSetHighBands
);
VOS_UINT32 DRVAGENT_CovertUserSetRxDivOrRxPriParaToMsInternal(
    VOS_UINT32                          ulSetDivLowBands,
    VOS_UINT32                          ulSetDivHighBands,
    VOS_UINT16                         *pusSetDivBands
);


VOS_UINT32 DRVAGENT_RcvDrvAgentImsiChgQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentInfoRbuSet(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentCpnnQry(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentCpnnTest(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentNvBackupSet(VOS_VOID *pMsg);


VOS_UINT32 DRVAGENT_RcvDrvAgentMemInfoQry(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentTseLrfSet(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentHkAdcGet(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentTbatQry(VOS_VOID *pMsg);
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
VOS_UINT32 DRVAGENT_RcvAtSpwordSet(VOS_VOID *pMsg);
#endif
VOS_UINT32 DRVAGENT_RcvDrvAgentSetSecuBoot(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentSetSimlockNv(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentSetStandby(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentNvBackupStatReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentNandBadBlockReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentNandDevInfoReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentChipTempReq(VOS_VOID *pMsg);
VOS_VOID DRVAGENT_RcvDrvAgentAntStateInd(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentSARReductionSet(VOS_VOID *pMsg);
/*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/
#if ( FEATURE_ON == FEATURE_LTE )
VOS_UINT32 DRVAGENT_RcvDrvAgentInfoRrsSet(VOS_VOID *pMsg);
#endif
/*DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合*/

VOS_UINT32 DRVAGENT_RcvDrvAgentSetMaxLockTms(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentSetApSimSt(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentHukSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentFacAuthPubkeySetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentIdentifyStartSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentIdentifyEndSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentSimlockDataWriteSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentPhoneSimlockInfoQryReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentSimlockDataReadQryReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentPhonePhynumSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentPhonePhynumQryReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentPortctrlTmpSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentPortAttribSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentPortAttribQryReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentOpwordSetReq(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_RcvDrvAgentSwverSetReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentCcpuMemQryReq(VOS_VOID *pMsg);

VOS_UINT32 DRVAGENT_GetSimLockRemainUnlockTimes(TAF_CUSTOM_CARDLOCK_STATUS_STRU *pstCardLockStatus);

#if (FEATURE_ON == FEATURE_VSIM)
VOS_UINT32 DRVAGENT_RcvDrvAgentHvpdhSetReq(VOS_VOID *pMsg);
#endif

/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
VOS_UINT32 DRVAGENT_RcvDrvAgentNvManufactureExtSet(VOS_VOID *pMsg);
/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */

VOS_UINT32 DRVAGENT_RcvDrvAgentSetAntSwitchReq(VOS_VOID *pMsg);
VOS_UINT32 DRVAGENT_RcvDrvAgentQryAntSwitchReq(VOS_VOID *pMsg);

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

#endif /* end of TafDrvAgentMsgProc.h */
