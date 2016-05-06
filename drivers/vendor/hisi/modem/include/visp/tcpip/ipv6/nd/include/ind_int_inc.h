/******************************************************************************
*             Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ind_int_inc.h
*
*    Project Code:  IPB IR V1R2
*    Version     :  IPBIRV100R003.IPv6.E001
*    Module Name :  ND
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define and expose ND Component,interface used by shell
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik    Created for including all public definitions in
*                         this file, for IPB IR V1R2 - COMMOM re-arrange
************************************************************************/

#ifndef _IND_INT_INC_H
#define _IND_INT_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "ipv6/ircommon/nd/ind_ir_inc.h"
#include "ipv6/nd/include/nd_int_pub.h"
#include "ipv6/ipv6_ppi.h"

/* Component Information */
extern const struct ComponentInfo m_CompNDInfo;

/*Begin: Changed for VISPV1R7 integration by wan, 2008-05-02*/
#define IID_IP6_ND_INT_INIT               (IID_IPV6_BASE + 68)
#define IID_IP6_ND_INT_FUN               (IID_IPV6_BASE + 69)
#define IID_IP6_ND_INT_TEST              (IID_IPV6_BASE + 70)
#define IID_IP6_ND_INT_SSA                (IID_IPV6_BASE + 71)

#define IID_IP6_ND_HOST_INT_INIT    (IID_IPV6_BASE + 72)
#define IID_IP6_ND_HOST_INT_FUN     (IID_IPV6_BASE + 73)
#define IID_IP6_ND_HOST_INT_SSA     (IID_IPV6_BASE + 74)
#define IID_IP6_ND_HOST_INT_TEST   (IID_IPV6_BASE + 75)
/*End of change for VISPV1R7 integration, 2008-05-02*/

/* ND Init VTable strcture Level - 3 */
DECLARE_INTERFACE (IIF_IP6_ND_INT_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_Init_Com_New) (IPB_IR_ND_COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfIP6_ND_Activate_Com) (VOID);
    METHOD_(ULONG, pfIP6_ND_SetModuleInfo)(IP6_ND_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG, pfIP6_ND_SetResSpecs)(SPECS_RES_VALUE_S  *pstResSpecs);
    METHOD_(ULONG, pfIP6_ND_SH_RegCallbackFunc)(
        IP6_ND_SH_CALLBACK_FUNC_S *pstNDShellCallback);

    /* Commented by Rajat Phull and moved to CFG V-table for consistency */

    METHOD_(ULONG, pfIP6_ND_HA_RegisterCallBack)(
            IP6_ND_SH_HA_CALLBACK_FUNC_S *pstHACallBackSet);

    METHOD_(ULONG, pfIP6_ND_RegNPCallback)(IPV6_PPI_HOOK_S *pstCallbackFunc);

    METHOD_(ULONG, pfIP6_ND_GetResSpecs)(SPECS_RES_VALUE_S  *pstResSpecs);
};

/******************************************************************************/

/**********************
   Testablility VTable
***********************/

/******************************************************************************/

/**********************
   Function VTable
***********************/
/* ND Function VTable Structure - Level 3 */
DECLARE_INTERFACE (IIF_IP6_ND_INT_FUN)
{
    IUNKNOWN_METHODS
    METHOD_(NDINFO_S *, pfIP6_ND_GetNDInfoByIfnet)(const VOID *pvIfnet);
    METHOD_(VOID,pfIP6_ND_DeleteNeighbour)(IN6ADDR_S stIn6Addr,ULONG ulIfIndex);
};

/******************************************************************************/

/*************
   SSA VTable
**************/

DECLARE_INTERFACE (IIF_IP6_ND_INT_SSA)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_ND_RA_TimeOut) (ND_TIMER_S  *pstTimerMsg);
    METHOD_(VOID, pfIP6_ND_DAD_Timeout) (VOID);
    METHOD_(VOID, pfIP6_ND_NB_Timeout) (ND_TIMER_S  *pstTimerMsg);
    METHOD_(VOID, pfIP6_ND_NBCacheCleanup_Timeout)(ND_TIMER_S * pstTimerMsg);
    METHOD_(ULONG, pfIP6_ND_ClearRATimerId)(ULONG ulIfindex);
    /*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    METHOD_(VOID, pfIP6_ND_NA_Timeout) (ND_TIMER_S  *pstTimerMsg);
    /* End of Added by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    /*Added by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测。, 2014/2/22   问题单号:DTS2014021206259  */
    METHOD_(VOID, pfIP6_ND_DADExt_Timeout) (ND_TIMER_S  *pstTimerMsg);
    /* End of Added by guojianjun178934, 2014/2/22   问题单号:DTS2014021206259  */
};


/******************************************************************************/
/*                      ND Host VTable Starts Here                            */
/******************************************************************************/

/***************
   INIT VTable
***************/

/* ND Host Init VTable strcture Level - 3*/
DECLARE_INTERFACE (IIF_IP6_ND_HOST_INT_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_Init_Com_New) (IPB_IR_ND_COM_ID_INFO_S *pstComInfo,
        ULONG ulComLen);
    METHOD_(ULONG, pfIP6_ND_Activate_Com) (VOID);
    METHOD_(ULONG, pfIP6_ND_SetModuleInfo)(IP6_ND_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG,pfIP6_ND_SetResSpecs)(SPECS_RES_VALUE_S  *pstResSpecs);
    METHOD_(ULONG,  pfIP6_ND_SH_RegCallbackFunc)
        (IP6_ND_SH_CALLBACK_FUNC_S * pstNDShellCallback);

    /* Commented by Rajat Phull and moved to CFG V-table for consistency */

    METHOD_(ULONG, pfIP6_ND_TWL_RegCallbackFunc)
        (IP6_ND_SH_TWLCALLBACK_FUNC_S *pstTWLCallBackFunc);

    METHOD_(ULONG, pfIP6_ND_RegNPCallback)(IPV6_PPI_HOOK_S *pstCallbackFunc);

    METHOD_(ULONG, pfIP6_ND_GetResSpecs)(SPECS_RES_VALUE_S  *pstResSpecs);
};

/******************************************************************************/

/******************************************************************************/

/**********************
   Function VTable
***********************/

/* ND Host Function VTable Structure - Level 3 */
DECLARE_INTERFACE (IIF_IP6_ND_HOST_INT_FUN)
{
    IUNKNOWN_METHODS
    METHOD_(NDINFO_S *, pfIP6_ND_GetNDInfoByIfnet)(const VOID *pvIfnet);
    METHOD_(VOID, pfIP6_ND_DeleteNeighbour)(IN6ADDR_S stIn6Addr,
        ULONG ulIfIndex);
};

/******************************************************************************/

/*************
   SSA VTable
**************/

/* ND Host SSA VTable Structure Level - 3 */
DECLARE_INTERFACE (IIF_IP6_ND_HOST_INT_SSA)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_ND_DAD_Timeout) (VOID);
    METHOD_(VOID, pfIP6_ND_NB_Timeout) (ND_TIMER_S  *pstTimerMsg);
    METHOD_(VOID, pfIP6_ND_NBCacheCleanup_Timeout)(ND_TIMER_S *pstTimerMsg);
    METHOD_(ULONG, pfIP6_ND_CtrlMsgNotify)(UINTPTR *pulCtrMsg);
    METHOD_(ULONG, pfIP6_ND_HostTimeoutHandler)(IP6_ND_HOST_TMRMSG_S *pstTmrMsg);
    /*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    METHOD_(VOID, pfIP6_ND_NA_Timeout) (ND_TIMER_S  *pstTimerMsg);
    /* End of Added by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    /*Added by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测。, 2014/2/22   问题单号:DTS2014021206259  */
    METHOD_(VOID, pfIP6_ND_DADExt_Timeout) (ND_TIMER_S  *pstTimerMsg);
    /* End of Added by guojianjun178934, 2014/2/22   问题单号:DTS2014021206259  */
};

/******************************************************************************/

/*----------------------------------------------*
 * Data Structure                             *
 *----------------------------------------------*/

/* Structure contains VTable Objects */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagND_INT_OBJ_S
{
    IIF_IP6_ND_INIT             *pNDINIT;
    IIF_IP6_ND_CFG              *pNDCFG;
    IIF_IP6_ND_FUN              *pNDFUN;

    IIF_IP6_ND_IR_FUN           *pNDIRFUN;

    IIF_IP6_ND_INT_INIT       *pNDCOMPINIT;
    IIF_IP6_ND_INT_FUN        *pNDCOMPFUN;
    IIF_IP6_ND_INT_SSA        *pNDCOMPSSA;

    IIF_IP6_ND_HOST_INIT      *pND_Host_INIT;
    IIF_IP6_ND_HOST_CFG       *pND_Host_CFG;
    IIF_IP6_ND_HOST_FUN       *pND_Host_FUN;
    IIF_IP6_ND_HOST_DHCP6ADAPT *pND_Host_DHCP6CAdapt;

    IIF_IP6_ND_HOST_IR_FUN     *pND_Host_IRFUN;

    IIF_IP6_ND_HOST_INT_INIT  *pND_Host_COMPINIT;
    IIF_IP6_ND_HOST_INT_FUN   *pND_Host_COMPFUN;
    IIF_IP6_ND_HOST_INT_SSA   *pND_Host_COMPSSA;

    IIF_IP6_ND_COMMON         *PNDCOMMON;
}ND_INT_OBJ_S;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /*_IND_INT_INC_H */

