


#ifndef __IADDR_IR_INC_H__
#define __IADDR_IR_INC_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#include "common/ipos/ipv6/basic/addrmng/iaddr_inc.h"
#include "ipv6/ircommon/addrmng/addr_ir_pub.h"
#include "ipv6/ircommon/addrmng/addr_ir_gen.h"

/* Interface IDs declaration for ADDR Router Interfaces */
#define IID_IP6_ADDR_IR_FUN 201

/* Interface IDs declaration for ADDR ND HOST Interfaces */
#define IID_IP6_ADDR_HOST_IR_FUN 301

/*******************************************************************************
                                ADDR ROUTER LEVEL 2 V-tables
*******************************************************************************/

DECLARE_INTERFACE(IIF_IP6_ADDR_IR_FUN)
{
    IUNKNOWN_METHODS

    /* No Ext Use, Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_DADCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Head)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_First_Addr)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Next_Addr)(IP6IFADDR_S *pstIp6IfAddr);

    /* No Ext Use - Nd alone uses */
    METHOD_(ULONG, pfIP6_IsLocalAddr)(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);

    /* Used By ND alone */
    METHOD_(IP6IFADDR_S *, pfIP6_IF_FindSameIpAddr)(IN6ADDR_S stIn6Addr,
        IP6IFNET_S *pIp6IfNet);

    /* Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_PrefixLen2Mask) (IN6ADDR_S *pstMask,
        ULONG ulPrefixLen);

    /* Used by ND */
    METHOD_(ULONG, pfIP6_Addr_CheckDADType)(VOID *pstIf);

    METHOD_(ULONG, pfIP6_Addr_IsValidSpecialProxyAddr)(ULONG ulIfIndex, 
                                                   IN6ADDR_S *pstIP6Addr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_GetExactAddrNoPrefix)(ULONG ulVrfIndex, 
                                                        IN6ADDR_S *pstIn6Addr);
    /* Modified by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测, 2014/2/21   问题单号:DTS2014021206259  */
    /*DAD扩展通知处理*/
    METHOD_(VOID, pfIP6_Addr_DADExtCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);
    /*End of Modified by guojianjun178934, 2014/2/21   问题单号:DTS2014021206259  */

};

/*******************************************************************************
                                ADDR ND HOST LEVEL 2 V-tables
*******************************************************************************/
DECLARE_INTERFACE(IIF_IP6_ADDR_HOST_IR_FUN)
{
    IUNKNOWN_METHODS

    /* No Ext Use, Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_DADCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Head)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_First_Addr)(ULONG ulScopeType,
        IP6IFNET_S *pstIp6If);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_Next_Addr)(IP6IFADDR_S *pstIp6IfAddr);

    /* No Ext Use - Nd alone uses */
    METHOD_(ULONG, pfIP6_IsLocalAddr)(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);

    /* Used By ND alone */
    METHOD_(IP6IFADDR_S *, pfIP6_IF_FindSameIpAddr)(IN6ADDR_S stIn6Addr,
        IP6IFNET_S *pIp6IfNet);

    /* Used by ND alone */
    METHOD_(VOID, pfIP6_Addr_PrefixLen2Mask) (IN6ADDR_S *pstMask,
        ULONG ulPrefixLen);


    /* Used by ND */
    METHOD_(ULONG, pfIP6_Addr_CheckDADType)(VOID *pstIf);

    /* ND uses */
    METHOD_(ULONG, pfIP6_Addr_HandleHostEvents)(IP6_ADDR_HOSTEVENT_S *pstNDHostEvent);
    METHOD_(ULONG, pfIP6_Addr_SetMTU)(ULONG ulIfnetIndex,
                                                ULONG ulIsNoCmd, ULONG ulMtu);

    

    /* ND uses */
    METHOD_(ULONG, pfIP6_Addr_SelectIntfwithValidAddr)(ULONG ulIfIndex,
                                                ULONG *pulAddrState);
    /* UT End : Srinivas D S 03-12-2007 */
    
    METHOD_(ULONG, pfIP6_Addr_IsValidSpecialProxyAddr)(ULONG ulIfIndex, 
                                                   IN6ADDR_S *pstIP6Addr);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_GetExactAddrNoPrefix)(ULONG ulVrfIndex, 
                                                        IN6ADDR_S *pstIn6Addr);
    /* Modified by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测, 2014/2/21   问题单号:DTS2014021206259  */
    /*DAD扩展通知处理*/
    METHOD_(VOID, pfIP6_Addr_DADExtCompleteNotify)(IP6IFADDR_S *pstIp6IfAddr);
    /*End of Modified by guojianjun178934, 2014/2/21   问题单号:DTS2014021206259  */

};


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IADDR_IR_INC_H__ */

