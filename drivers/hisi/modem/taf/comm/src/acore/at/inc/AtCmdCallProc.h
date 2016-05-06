

#ifndef __ATCMDCALLPROC_H__
#define __ATCMDCALLPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "AtMnInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define AT_CALL_D_GI_PARA_LEN                          (2)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT32 AT_SetCecallPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryCecallPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetEclstartPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestEclstartPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetEclstopPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetEclcfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryEclcfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetEclmsdPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryEclmsdPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestEclmsdPara(VOS_UINT8 ucIndex);
#endif
/* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, end   */

VOS_UINT32 At_RcvVcMsgDtmfDecoderIndProc(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_RcvTafCallSndFlashRslt(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);


extern VOS_UINT32 AT_RcvTafCallSndBurstDTMFCnf(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);

extern VOS_UINT32 AT_RcvTafCallSndBurstDTMFRslt(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);

extern VOS_UINT32 At_TestCBurstDTMFPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetCBurstDTMFPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_SetCfshPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_CheckCfshNumber(
    VOS_UINT8                          *pucAtPara,
    VOS_UINT16                          usLen
);

extern VOS_UINT32 AT_RcvTafCallCalledNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallCallingNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallDispInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallExtDispInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallConnNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallRedirNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallSignalInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallLineCtrlInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);

extern VOS_UINT32 AT_RcvTafCallCCWACInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);

extern VOS_UINT32 At_TestCContinuousDTMFPara(
    VOS_UINT8                           ucIndex
);
extern VOS_UINT32 AT_SetCContinuousDTMFPara(
    VOS_UINT8                           ucIndex
);
extern VOS_UINT32 AT_CheckCContDtmfKeyPara(VOS_VOID);
extern VOS_UINT32 AT_RcvTafCallSndContinuousDTMFCnf(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallSndContinuousDTMFRslt(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallRcvContinuousDtmfInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);
extern VOS_UINT32 AT_RcvTafCallRcvBurstDtmfInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
);

VOS_VOID AT_RcvTafCallCclprCnf(MN_AT_IND_EVT_STRU *pstData);

VOS_UINT32 AT_TestCclprPara( VOS_UINT8 ucIndex );

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

#endif /* end of AtCmdCallProc.h */
