/*-----------------------------------------------------------------------
*                              ipmtu_com_inc.h
*
*    Project Code:  IPB IR V1R2
*    Module Name :  ADDR
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define and expose pmtu Component,interface used by shell
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik    Created for including all public definitions in
*                             this file, for IPB IR V1R2 - COMMOM re-arrange
************************************************************************/

#ifndef _IP6_IPMTU_COM_INC_H
#define _IP6_IPMTU_COM_INC_H

#ifdef  __cplusplus
extern "C"{
#endif
#include "ipv6/ircommon/pathmtu/ipmtu_ir_inc.h"
#include "ipv6/pathmtu/include/pmtu_int_pub.h"
#include "ipv6/ipv6_ppi.h"

/* Component Information */
extern const struct ComponentInfo m_CompPMTUInfo;

/*Begin: Changed for VISPV1R7 integration by wan, 2008-05-02*/
#define IID_IP6_PMTU_INT_INIT               (IID_IPV6_BASE + 53)
#define IID_IP6_PMTU_INT_SSA                (IID_IPV6_BASE + 54)
#define IID_IP6_PMTU_INT_HSB                (IID_IPV6_BASE + 55)
#define IID_IP6_PMTU_INT_TEST               (IID_IPV6_BASE + 56)
/*End of change for VISPV1R7 integration, 2008-05-02*/


/*Declaration of INT INIT interface*/
DECLARE_INTERFACE(IIF_IP6_PMTU_INT_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_PMTU_Init_Com_NEW)
        (IPB_IR_PMTU_COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfIP6_PMTU_Activate_Com)(VOID);
    METHOD_(ULONG, pfIP6_PMTU_SetModuleInfo)(PMTU_MOD_INFO_S *pMInfo);
    METHOD_(ULONG, pfIP6_PMTU_RegDebugCallBack)
        (PMTU_SHELL_DEBUG_CALLBACK_SET_S *pstCallBackSet);
    METHOD_(ULONG, pfIP6_PMTU_RegTimeoutCallBack)
        (PMTU_SHELL_TIMEOUT_CALLBACUP_SET_S  *pstCallBackSet);
    METHOD_(ULONG, pfIP6_PMTU_HA_RegisterCallBack)
        (PMTU_SHELL_HA_BACUP_SET_S*);
    METHOD_(ULONG, pfIP6_PMTU_RegShellCallbackFunc)
        (IP6_PMTU_SH_CALLBACK_FUNC_S*);
    METHOD_(ULONG, pfIP6_PMTU_RegNPCallback)(IPV6_PPI_HOOK_S *pstCallbackFunc);
};

/*Declaration of INT SSA interface*/
DECLARE_INTERFACE(IIF_IP6_PMTU_INT_SSA)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_PMTU_HotInsertProc)(ULONG ulSlot);
    METHOD_(VOID, pfIP6_PMTU_EV_OnReceivedEvent_Cachetimeout)(VOID);
    METHOD_(VOID, pfIP6_PMTU_EV_OnReceivedEvent_Agetimeout)(VOID);
    METHOD_(ULONG, pfIP6_PMTU_EV_OnReceivedEvent_IPC)(UCHAR *pData);
    METHOD_(ULONG, pfIP6_PMTU_TooBigHandler)(TOO_BIG_INFO_S *);
};

/*Declaration of INT HSB interface*/
DECLARE_INTERFACE(IIF_IP6_PMTU_INT_HSB)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_PMTU_HA_SetBackupData)
        (UCHAR *pData, ULONG ulEventType);
    METHOD_(VOID, pfIP6_PMTU_HA_DataSmoothOutside)(VOID);
    METHOD_(VOID, pfIP6_PMTU_HA_DataSmoothInside)(VOID);
    METHOD_(VOID, pfIP6_PMTU_HA_StateChange)(ULONG);
    METHOD_(ULONG, pfIP6_PMTU_HA_SendBackupData)(VOID);

};

typedef struct tagPMTU_INT_OBJ_S
{
    IIF_IP6_PMTU_INIT     * pstPMTU_INIT;
    IIF_IP6_PMTU_INT_INIT * pstPMTU_INT_INIT;
    IIF_IP6_PMTU_CFG      * pstPMTU_CFG;
    IIF_IP6_PMTU_INT_SSA  * pstPMTU_INT_SSA;
    IIF_IP6_PMTU_FUN      * pstPMTU_FUN;
    IIF_IP6_PMTU_IR_FUN   * pstPMTU_IR_FUN;
    IIF_IP6_PMTU_INT_HSB  * pstPMTU_INT_HSB;
} PMTU_INT_OBJ_S;


#ifdef  __cplusplus
}
#endif

#endif

