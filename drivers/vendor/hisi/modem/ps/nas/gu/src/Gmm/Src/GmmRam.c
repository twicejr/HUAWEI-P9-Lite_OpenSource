/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmDetach.c
  Description   : GMM全局变量定义用源文件
  Function List :
    01.  g_GmmGlobalCtrl
    02.  g_GmmTimerMng
    03.  g_GmmAttachCtrl
    04.  g_GmmRauCtrl
    05.  g_GmmDetachCtrl
    06.  g_GmmAuthenCtrl
    07.  g_GmmReqCnfMng
    08.  g_GmmImportFunc
    09.  g_GmmServiceCtrl
  History       :
    1.  张志勇  2003.12.05  新规作成

*******************************************************************************/
#include "GmmInc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

GMM_GLOBAL_CTRL_STRU          g_GmmGlobalCtrl;
GMM_TIMER_STRU                g_GmmTimerMng;
GMM_ATTACH_CTRL_STRU          g_GmmAttachCtrl;
GMM_RAU_CTRL_STRU             g_GmmRauCtrl;
GMM_DOWNLINK_NPDU_STRU        g_GmmDownLinkNpduBake;
GMM_DETACH_CTRL_STRU          g_GmmDetachCtrl;
GMM_AUTHEN_CTRL_STRU          g_GmmAuthenCtrl;
GMM_REQ_CNF_MNG_STRU          g_GmmReqCnfMng;
GMM_IMPORTED_FUNC_LIST_STRU   g_GmmImportFunc;
GMM_SR_CTRL_STRU              g_GmmServiceCtrl;
VOS_BOOL                      g_HaveGotLmmSecInfo;
GMM_SPEC_PROC_CONTEXT_STRU    g_stGmmSpecProcCtxToGetLmmSecInfo;

GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU g_GmmInterRatInfoCtrl;

HTIMER                        g_stGmmProtectRrRelTimer;

VOS_UINT8                       gucLteGutiValid ;

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

