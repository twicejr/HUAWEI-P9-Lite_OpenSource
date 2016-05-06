/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

*******************************************************************************
*                              iaddr_int_inc.h
*
*    Module Name :  ADDR
*    Version     :  IPBIRV100R003.IPv6.E001
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define and expose ADDR Component,interface used by shell
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik    Created for including all public definitions in
*                             this file, for IPB IR V1R2 - COMMOM re-arrange
******************************************************************************/

#ifndef _IADDR_INT_INC_H
#define _IADDR_INT_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "ipv6/ircommon/addrmng/iaddr_ir_inc.h"
#include "ipv6/addrmng/include/addr_int_pub.h"
#include "ipv6/ipv6_ppi.h"

/* Component Information */
extern const struct ComponentInfo m_CompADDRInfo;

/*Begin: Changed for VISPV1R7 integration by wan, 2008-05-02*/
/* Interface IDs declaration for ADDR Router Interfaces */
#define IID_IP6_ADDR_INT_INIT             (IID_IPV6_BASE + 86)
#define IID_IP6_ADDR_INT_FUN              (IID_IPV6_BASE + 87)
#define IID_IP6_ADDR_INT_HSB              (IID_IPV6_BASE + 88)
#define IID_IP6_ADDR_INT_TEST             (IID_IPV6_BASE + 89)
#define IID_IP6_ADDR_INT_SSA              (IID_IPV6_BASE + 90)

/* Interface IDs declaration for ADDR ND HOST Interfaces */
#define IID_IP6_ADDR_HOST_INT_INIT   (IID_IPV6_BASE + 91)
#define IID_IP6_ADDR_HOST_INT_FUN    (IID_IPV6_BASE + 92)
#define IID_IP6_ADDR_HOST_INT_TEST   (IID_IPV6_BASE + 93)
#define IID_IP6_ADDR_HOST_INT_SSA     (IID_IPV6_BASE + 94)
/*End of change for VISPV1R7 integration, 2008-05-02*/

/*******************************************************************************
                                ADDR ROUTER LEVEL 3 V-tables
*******************************************************************************/

/* Init Interface Level -3  */
DECLARE_INTERFACE(IIF_IP6_ADDR_INT_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_Init_Com_New)(const IPB_IR_ADDR_COM_ID_INFO_S
        *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfIP6_Addr_Activate_Com)(VOID);
    METHOD_(ULONG, pfIP6_Addr_SetResSpecs)(SPECS_RES_VALUE_S *);
    METHOD_(ULONG, pfIP6_Addr_SetModuleInfo)(IP6_ADDR_MOD_INFO_S *pstMInfo);

     /* Commented by Rajat Phull and moved to CFG table for consistency */
    METHOD_(ULONG, pfIP6_Addr_SH_RegCallbackFunc)(IP6_ADDR_SH_CALLBACK_FUNC_S
        *pstCallbackFunc);

    METHOD_(ULONG, pfIP6_Addr_RegNPCallback)(IPV6_PPI_HOOK_S *pstCallbackFunc);

    METHOD_(ULONG, pfIP6_Addr_SetFunSpecs)(SPECS_FUN_VALUE_S *);
};


DECLARE_INTERFACE(IIF_IP6_ADDR_INT_FUN)
{
    IUNKNOWN_METHODS

    METHOD_(VOID, pfIP6_Addr_Enable) (VOID);
    METHOD_(VOID, pfIP6_Addr_Disable)(VOID);
    METHOD_(ULONG, pfIP6_Addr_GetNumValidUcastAddrOnIF)(VOID *pstIfnet);
    METHOD_(VOID, pfIP6_Addr_Set_RPCSendToIO)(VOID);
};


DECLARE_INTERFACE(IIF_IP6_ADDR_INT_HSB)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_Addr_HA_DataSmoothEvent)(VOID);
    METHOD_(ULONG, pfIP6_Addr_HA_RegCallbackFunc)(IP6_ADDR_HA_CALLBACK_FUNC_S
                                                        *pstHACallBackSet);
    METHOD_(ULONG, pfIP6_Addr_HA_SetBackupData)(UCHAR *pData,
        ULONG ulEventType);
    METHOD_(ULONG, pfIP6_Addr_HA_SendBackupData)(VOID);
    METHOD_(VOID,  pfIP6_Addr_HA_StateChange)(ULONG ulHAState);
    METHOD_(ULONG, pfIP6_Addr_HA_RealtimeBackup)(VOID *pstIf,
        IP6IFADDR_S *pstIp6IfAddr, ULONG ulType);
    METHOD_(VOID, pfIP6_Addr_SyncRefCount)(VOID);
};

DECLARE_INTERFACE (IIF_IP6_ADDR_INT_SSA)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_Addr_HandleDADMsg)(IP6_ADDR_DADSTATE_S *pstRecData);
    METHOD_(VOID, pfIP6_Addr_HandleRPCMsg)(IP6RPC_REQUEST_S *pstRecvInfo,
        IP6_GETINTERFACEID_REPLY_S  **ppstOutReplyMsg, ULONG *pulSendDataLen);
};


/*******************************************************************************
                                ADDR ND HOST LEVEL 3 V-tables
*******************************************************************************/


/* Init Interface Level -3  */
DECLARE_INTERFACE(IIF_IP6_ADDR_HOST_INT_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_Init_Com_New)(const IPB_IR_ADDR_COM_ID_INFO_S
        *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfIP6_Addr_Activate_Com)(VOID);
    METHOD_(ULONG, pfIP6_Addr_SetResSpecs)(SPECS_RES_VALUE_S *);
    METHOD_(ULONG, pfIP6_Addr_SetModuleInfo)(IP6_ADDR_MOD_INFO_S *pstMInfo);

    /* Commented by Rajat Phull and moved to CFG table for consistency */
    METHOD_(ULONG, pfIP6_Addr_SH_RegCallbackFunc)(IP6_ADDR_SH_CALLBACK_FUNC_S
        *pstCallbackFunc);
    METHOD_(ULONG, pfIP6_Addr_Timer_RegCallbackFunc)
            (IP6_ADDR_TIMER_CALLBACK_FUNC_S *pstCallbackFunc);
    
    METHOD_(ULONG, pfIP6_Addr_RegNPCallback)(
                                IPV6_PPI_HOOK_S *pstCallbackFunc);

    METHOD_(ULONG, pfIP6_Addr_SetFunSpecs)(SPECS_FUN_VALUE_S *);
};


DECLARE_INTERFACE(IIF_IP6_ADDR_HOST_INT_FUN)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIP6_Addr_GetNumValidUcastAddrOnIF)(VOID *pstIfnet);

    /* Not Used */ /* TBD - can be moved to SSA */
    METHOD_(VOID, pfIP6_Addr_Set_RPCSendToIO)(VOID);
};

DECLARE_INTERFACE(IIF_IP6_ADDR_HOST_INT_SSA)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_HandleTimeOutEvents)
                        (IP6_ADDR_TIMER_CTRL_MSG *pstTimerCtrlMsg);
};

/* Holds V-table Objects */
/* WARNING-> The numbers of structure elements shall be moderate i.e <= 5 */
/* The Above HCC Warning is obvious - Will not be addressed */
typedef struct tagAddrINT_OBJ_S
{
    IIF_IP6_ADDR_INIT *pAddrINIT;
    IIF_IP6_ADDR_CFG  *pAddrCFG;
    IIF_IP6_ADDR_FUN  *pAddrFUN;

    IIF_IP6_ADDR_IR_FUN *pAddrIRFUN;

    IIF_IP6_ADDR_INT_INIT *pAddrINTINIT;
    IIF_IP6_ADDR_INT_FUN  *pAddrINTFUN;
    IIF_IP6_ADDR_INT_HSB  *pAddrINTHSB;
    IIF_IP6_ADDR_INT_SSA  *pAddrINTSSA;

    IIF_IP6_ADDR_HOST_INIT *pAddrHostINIT;
    IIF_IP6_ADDR_HOST_CFG  *pAddrHostCFG;
    IIF_IP6_ADDR_HOST_FUN  *pAddrHostFUN;

    IIF_IP6_ADDR_HOST_IR_FUN *pAddrHostIRFUN;

    IIF_IP6_ADDR_HOST_INT_INIT *pAddrHostINTINIT;
    IIF_IP6_ADDR_HOST_INT_FUN  *pAddrHostINTFUN;
    IIF_IP6_ADDR_HOST_INT_SSA  *pAddrHostINTSSA;

}ADDR_INT_OBJ_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _IADDR_INT_INC_H */

