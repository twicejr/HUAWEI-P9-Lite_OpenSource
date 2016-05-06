

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifndef __IND_IR_INC_H__
#define __IND_IR_INC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "common/ipos/ipv6/basic/nd/ind_inc.h"
#include "ipv6/ircommon/nd/nd_ir_pub.h"
#include "ipv6/ircommon/nd/nd_ir_gen.h"

/* Interface IDs declaration */
#define IID_IP6_ND_IR_FUN              201

/* Interface IDs declaration for Host*/
#define IID_IP6_ND_HOST_IR_FUN         301

/******************************************************************************/
/*                      Router VTable Start Here                              */
/******************************************************************************/

/**********************
   Function VTable
***********************/

/* ND Function VTable Structure - Level 2 */
DECLARE_INTERFACE (IIF_IP6_ND_IR_FUN)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_ND_RS_Input) (MBUF_S* pMbuf, LONG lOff,
        LONG lIcmp6Len);
    METHOD_(VOID, pfIP6_ND_RA_Input) (MBUF_S* pMbuf, LONG lOff,
        LONG lIcmp6Len);
    METHOD_(VOID, pfIP6_ND_NS_Input) (MBUF_S* pstMbuf, LONG lOff,
        LONG lIcmp6Len);
    METHOD_(VOID, pfIP6_ND_NA_Input) (MBUF_S* pstMbuf, LONG lOff,
        LONG lIcmp6Len);
    METHOD_(ULONG, pfIP6_ND_IsNextHopRouterHost) (ULONG ulIfIndex,
        const IN6ADDR_S st_Addr);
    METHOD_(ULONG, pfIP6_ND_GetLinkLocalAddr) (ULONG ulIfIndex,
        const IN6ADDR_S  *pstInAddr, IN6ADDR_S  **ppstOutAddr);
    METHOD_(ULONG, pfIP6_ND_GetLinkLayerAddr)(ULONG ulIfIndex,
        const IN6ADDR_S *pstInAddr, UCHAR  **ppucllAddr);
    METHOD_(VOID, pfIP6_ND_AddAddr) (const IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_DelAddr) (const IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_AddPrefix)(ULONG ulIfnetIndex,
        IN6ADDR_S  stPrefixInfo, ULONG ulPrefixLength);
    METHOD_(VOID, pfIP6_ND_DeletePrefix)(ULONG ulIfnetIndex,
        IN6ADDR_S  stPrefixInfo);
    METHOD_(VOID, pfIP6_ND_NDInfoInit) (IP6IFNET_S *pstIP6Ifnet);
    METHOD_(VOID, pfIP6_ND_NDInfoFree) (const IP6IFNET_S *pstIP6Ifnet);
    METHOD_(VOID, pfIP6_ND_DADStart) (IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_DADStop)(const IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(VOID, pfIP6_ND_DADStopAll)(VOID *pstIf);
    METHOD_(ND_NBENTRY_S *,pfIP6_ND_NBEntryLookup)(ULONG ulIndex,
        IN6ADDR_S stIPv6Addr);
    METHOD_(ULONG, pfIP6_ND_GetTimerQueueID)(ULONG *pulTimerQueID);
    METHOD_(ULONG, pfIP6_ND_GetTaskID)(ULONG *pulTaskID);

    /*METHOD_(VOID, pfIP6_ND_AsynEnQue)(ND_TIMER_S    *pstRcvMsg);*/
    METHOD_(VOID, pfIP6_ND_AsynEnQue)(IP6_ND_EVENTMSG_S    *pstRcvMsg);

    METHOD_(VOID, pfIP6_ND_ResetDadAttempts) (ULONG ulIfnetIndex);
    METHOD_(VOID, pfIP6_ND_UpdatePrefixStatus) (const IP6IFNET_S *pstIp6Ifnet,
        const IN6ADDR_S *pstPrefixInfo, ULONG ulStatus);
    METHOD_(ULONG, pfIP6_ND_NBEntry_DelbyPrefix)(ULONG ulIfIndex,
                                    IN6ADDR_S stIn6Addr,
                                    IN6ADDR_S stPrefixMask);
    METHOD_(ULONG, pfIP6_ND_GetSpecialProxy)(IP6_ND_SPECIAL_PROXY_PARA_S *pstSpecProxyPara);
    /*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    METHOD_(ULONG, pfIP6_ND_NAStart) (IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_NAStop)(const IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(VOID, pfIP6_ND_NAStopAll)(VOID *pstIf);
    /* End of Added by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    
    /*Added by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测。, 2014/2/22   问题单号:DTS2014021206259  */
    METHOD_(ULONG, pfIP6_ND_DADExtStart) (IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_DADExtStop)(const IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(VOID, pfIP6_ND_DADExtStopAll)(VOID *pstIf);
    /* End of Added by guojianjun178934, 2014/2/22   问题单号:DTS2014021206259  */
    METHOD_(ULONG, pfIP6_ND_NBEntry_UpdateVrfByIf)(ULONG ulVrfIndex, ULONG ulIfIndex);
};



/******************************************************************************/
/*                      ND Host VTable Starts Here                            */
/******************************************************************************/

/**********************
   Function VTable
***********************/

/* ND Function VTable Structure - Level 2 */
DECLARE_INTERFACE (IIF_IP6_ND_HOST_IR_FUN)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_ND_RA_Input) (MBUF_S* pMbuf, LONG lOff,
        LONG lIcmp6Len);
    METHOD_(VOID, pfIP6_ND_NS_Input) (MBUF_S* pstMbuf, LONG lOff,
        LONG lIcmp6Len);
    METHOD_(VOID, pfIP6_ND_NA_Input) (MBUF_S* pstMbuf, LONG lOff,
        LONG lIcmp6Len);
    METHOD_(ULONG, pfIP6_ND_IsNextHopRouterHost) (ULONG ulIfIndex,
        const IN6ADDR_S st_Addr);
    METHOD_(ULONG, pfIP6_ND_GetLinkLocalAddr) (ULONG ulIfIndex,
        const IN6ADDR_S  *pstInAddr, IN6ADDR_S  **ppstOutAddr);
    METHOD_(ULONG, pfIP6_ND_GetLinkLayerAddr)(ULONG ulIfIndex,
        const IN6ADDR_S *pstInAddr, UCHAR  **ppucllAddr);
    METHOD_(VOID, pfIP6_ND_NDInfoInit) (IP6IFNET_S *pstIP6Ifnet);
    METHOD_(VOID, pfIP6_ND_NDInfoFree) (const IP6IFNET_S *pstIP6Ifnet);
    METHOD_(VOID, pfIP6_ND_DADStart) (IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_DADStop)(const IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(VOID, pfIP6_ND_DADStopAll)(VOID *pstIf);
    METHOD_(ND_NBENTRY_S *,pfIP6_ND_NBEntryLookup)(ULONG ulIndex,
        IN6ADDR_S stIPv6Addr);
    METHOD_(ULONG, pfIP6_ND_GetTimerQueueID)(ULONG *pulTimerQueID);
    METHOD_(ULONG, pfIP6_ND_GetTaskID)(ULONG *pulTaskID);

    /*METHOD_(VOID, pfIP6_ND_AsynEnQue)(ND_TIMER_S    *pstRcvMsg);*/
    METHOD_(VOID, pfIP6_ND_AsynEnQue)(IP6_ND_EVENTMSG_S    *pstRcvMsg);
    METHOD_(VOID, pfIP6_ND_ResetDadAttempts) (ULONG ulIfnetIndex);
    METHOD_(VOID, pfIP6_ND_Redirect_Input)
        (MBUF_S * pstMbuf, LONG lOff, LONG lIcmp6Len);
    METHOD_(ULONG, pfIP6_ND_FindNHAndOGIntf_ForDestAddr)(
        IP6_ND_NHINPUTPARAM_S *pstNHInput,
        IP6_ND_NHOUTPUTPARAM_S *pstNHOut);
    METHOD_(ULONG, pfIP6_ND_NotifyDHCP6CAdaptAddrNotUse)(
        IP6_ND_IADESC_S *pstIADesc, IP6_ND_IN6ADDRWITHTIME_S *pstAddress,
        IP6_ND_NOTUSABLE_REASON_E eNotifyType);
    METHOD_(ULONG, pfIP6_ND_NBEntry_DelbyPrefix)(ULONG ulIfIndex,
                                    IN6ADDR_S stIn6Addr,
                                    IN6ADDR_S stPrefixMask);
    METHOD_(ULONG, pfIP6_ND_GetSpecialProxy)(IP6_ND_SPECIAL_PROXY_PARA_S *pstSpecProxyPara);
    /*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    METHOD_(ULONG, pfIP6_ND_NAStart) (IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_NAStop)(const IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(VOID, pfIP6_ND_NAStopAll)(VOID *pstIf);
    /* End of Added by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    /*Added by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测。, 2014/2/22   问题单号:DTS2014021206259  */
    METHOD_(ULONG, pfIP6_ND_DADExtStart) (IP6IFADDR_S *pstAddr);
    METHOD_(VOID, pfIP6_ND_DADExtStop)(const IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(VOID, pfIP6_ND_DADExtStopAll)(VOID *pstIf);
    /* End of Added by guojianjun178934, 2014/2/22   问题单号:DTS2014021206259  */
    METHOD_(ULONG, pfIP6_ND_NBEntry_UpdateVrfByIf)(ULONG ulVrfIndex, ULONG ulIfIndex);
};



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __IND_IR_INC_H__ */
