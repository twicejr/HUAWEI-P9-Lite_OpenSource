
#ifdef  __cplusplus
extern  "C"{
#endif
#ifndef _I_ATK_FUNC_H_
#define _I_ATK_FUNC_H_


VOID ATK_Sock_TimeCallBack(VOID *pArg);

/*******************************************************************************
*    Func Name: ATK_AddAtkStat
* Date Created: 2014-08-06
*       Author: a00900892
*  Description: Increment count of an attack type in attack statistics for an
*               interface.
*        Input: ulIfIndex: If index of the incoming interface.
*               ulAttackType: Type of IP attack, one of ENUM_ATKSTATTYPE.
*               pstIp£ºPointer to the IP header of the incoming packet.
*       Output: 
*       Return: VOS_OK: If module not initialized, else VOS_ERR.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-06   a00900892               Create
*  2014-08-18   a00900892               Modify (change return type, DTS2014081805831)
*
*******************************************************************************/
ULONG ATK_AddAtkStat(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp);

/*******************************************************************************
*    Func Name: ATK_AddIcmpJumbogramStat
* Date Created: 2014-08-06
*       Author: a00900892
*  Description: Check if the incoming icmp packet length is larger than the
*               configured maximum size. If size is lesser, return success.
*               Else increment Attack count of type ATK_STAT_TYPE_ICMP_LARGE.
*        Input: ulIfIndex: If index of the incoming interface.
*               ulLen: Length of the incoming IP packet(ICMP).
*               pstIp£ºPointer to the IP header of the incoming packet.
*       Output: 
*       Return: VOS_OK:  If packet should not be dropped.
*               VOS_ERR: If packet should be dropped.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-06   a00900892               Create
*
*******************************************************************************/
ULONG ATK_AddIcmpJumbogramStat(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp);


ULONG ATK_DelAllStats();


VOID ATK_IfDelete_Notify(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: ATK_AddAtkStat_PT
* Date Created: 2014-08-06
*       Author: a00900892
*  Description: Increment count of an attack type in attack statistics for an
*               interface.
*        Input: ulIfIndex: If index of the incoming interface.
*               ulAttackType: Type of IP attack, one of ENUM_ATKSTATTYPE.
*               pstIp£ºPointer to the IP header of the incoming packet.
*       Output: 
*       Return: VOS_OK: If module not initialized, else VOS_ERR.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-18   a00900892               Create (for DTS2014081805831)
*
*******************************************************************************/
ULONG ATK_AddAtkStat_PT(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp);

/*******************************************************************************
*    Func Name: ATK_AddIcmpJumbogramStat_PT
* Date Created: 2014-08-06
*       Author: a00900892
*  Description: Check if the incoming icmp packet length is larger than the
*               configured maximum size. If size is lesser, return success.
*               Else increment Attack count of type ATK_STAT_TYPE_ICMP_LARGE.
*        Input: ulIfIndex: If index of the incoming interface.
*               ulLen: Length of the incoming IP packet(ICMP).
*               pstIp£ºPointer to the IP header of the incoming packet.
*       Output: 
*       Return: VOS_OK:  If packet should not be dropped.
*               VOS_ERR: If packet should be dropped.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-18   a00900892               Create (for DTS2014081805831)
*
*******************************************************************************/
ULONG ATK_AddIcmpJumbogramStat_PT(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp);


VOID ATK_IfDelete_Notify_PT(ULONG ulIfIndex);


ULONG ATK_IsSwitchOpen();


#endif  /* I_ATK_FUNC_H_ */
#ifdef  __cplusplus
}
#endif


