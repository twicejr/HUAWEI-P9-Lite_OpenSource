/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmInterSysTbl.c
Author          :   w00176964
Version         :
Date            :   2015-11-05
Description     :   CL异系统流程状态机消息处理表文件
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/

/*****************************************************************************
  1. Including header files
*****************************************************************************/
#include "NasFsm.h"
#include "NasComm.h"
#include "NasMsccFsmCLInterSys.h"
#include "MmaMsccInterface.h"
#include "NasMsccFsmCLInterSysTbl.h"
#include "MsccMmcInterface.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "hsd_mscc_pif.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_CL_INTER_SYS_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2. Global Variable.
*****************************************************************************/

NAS_FSM_DESC_STRU                       g_stNasMsccCLInterSysFsmDesc;

/**************************************************************************/
/* 3. List of action tables */
/**************************************************************************/
/* intersys状态机init状态下的消息处理表 */
NAS_ACT_STRU        g_astNasMsccCLInterSysInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_INTERSYS_START_IND,
                      NAS_MSCC_RcvHsdInterSysStartInd_CLInterSys_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_INTERSYS_START_IND,
                      NAS_MSCC_RcvMmcInterSysStartInd_CLInterSys_Init)

};

/* intersys状态机等待MMC的power save状态下的消息处理表 */
NAS_ACT_STRU        g_astNasMsccCLInterSysWaitMmcPowerSaveCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvMmcPowerSaveCnf_CLInterSys_WaitMmcPowerSaveCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
                      NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf)

};

/* intersys状态机等待HSD或MMC的异系统结束指示的消息处理表 */
NAS_ACT_STRU        g_astNasMsccCLInterSysWaitInterSysEndIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_INTERSYS_END_IND,
                      NAS_MSCC_RcvHsdInterSysEndInd_CLInterSys_WaitInterSysEndInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_NAS_MSCC_MSCC_ABORT_FSM_REQ,
                      NAS_MSCC_RcvMsccAbortFsmReq_CLInterSys_WaitInterSysEndInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_INTERSYS_END_IND,
                      NAS_MSCC_RcvMmcInterSysEndInd_CLInterSys_WaitInterSysEndInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND,
                      NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd)

};

/* intersys状态机状态处理表 */
NAS_STA_STRU        g_astNasMsccCLInterSysStaTbl[]   =
{
    NAS_STA_TBL_ITEM( NAS_MSCC_CL_INTERSYS_STA_INIT,
                      g_astNasMsccCLInterSysInitActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_CL_INTERSYS_STA_WAIT_MMC_POWER_SAVE_CNF,
                      g_astNasMsccCLInterSysWaitMmcPowerSaveCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MSCC_CL_INTERSYS_STA_WAIT_INTERSYS_END_IND,
                      g_astNasMsccCLInterSysWaitInterSysEndIndActTbl )

};

/*****************************************************************************
Function Name   :   NAS_MSCC_GetCLInterSysStaTblSize
Description     :   获取CL intersys状态机的状态处理表大小

Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-11-05
        Author  :   w00176964
        Modify content :    Create

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetCLInterSysStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccCLInterSysStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetCLInterSysFsmDescAddr
Description     :   获取CL intersys状态机的状态描述表地址
Input parameters:   VOS_VOID
Outout parameters:  None
Return Value    :   &NAS_FSM_DESC_STRU

Modify History:
    1)  Date    :   2015-11-05
        Author  :   w00176964
        Modify content :    Create

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MSCC_GetCLInterSysFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccCLInterSysFsmDesc);
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

