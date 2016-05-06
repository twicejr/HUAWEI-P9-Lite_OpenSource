
#if (NAT_WVISP == 1)

#include "security/wvisp_adapter/include/intf_adp.h"

#elif (NAT_RPU == 1)

#include "security/rpu_adapter/include/intf_adp.h"

#else

#ifndef _INTF_ADP_H_
#define _INTF_ADP_H_

#ifdef  __cplusplus
extern  "C"{
#endif
typedef VOID * INTF_HANDLE;

/*******************************************************************************
*    Func Name: IPSAFE_ADP_SetNATRuleHandle
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Set nat rule handle to interface
*  Description: Set nat rule handle to interface
*        Input: INTF_HANDLE intfHandle: Interface handle, product interpret interface handle<Product write value>
*               VOID * pstNatRuleHandle: Nat rule pointer<Not null pointer>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: For one interface, set nat rule handle only one time and this memory free by nat moudle. 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/

UINT32 IPSAFE_ADP_SetNATRuleHandle(INTF_HANDLE intfHandle, VOID * pstNatRuleHandle);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_GetNATRuleHandle
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Get nat rule handle address
*  Description: Get nat rule handle address
*        Input: INTF_HANDLE intfHandle: Interface handle, product interpret interface handle<Product write value>
*               VOID **pstNatRuleHandle: Get nat rule pointer address<Not null pointer>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_GetNATRuleHandle(INTF_HANDLE intfHandle, VOID **pstNatRuleHandle);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_SetASPFRuleHandle
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Set aspf rule handle to interface
*  Description: Set aspf rule handle to interface
*        Input: INTF_HANDLE intfHandle: Interface handle, product interpret interface handle<Product write value>
*               VOID * pstNatRuleHandle: Aspf rule pointer<Not null pointer>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: For one interface, set aspf rule handle only one time and this memory free by nat moudle. 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_SetASPFRuleHandle(INTF_HANDLE intfHandle, VOID * pstAspfRuleHandle);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_GetASPFRuleHandle
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Get aspf rule handle address
*  Description: Get aspf rule handle address
*        Input: INTF_HANDLE intfHandle: Interface handle, product interpret interface handle<Product write value>
*               VOID **pstNatRuleHandle: Get aspf rule pointer address<Not null pointer>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_GetASPFRuleHandle(INTF_HANDLE intfHandle, VOID **pstAspfRuleHandle);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_GetMaxIpNum
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Get configing max global ip number
*  Description: Get configing max global ip number 
*        Input: VOID
*       Output: 
*       Return: 
*      Caution: 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/

UINT32 IPSAFE_ADP_GetMaxIpNum(VOID);

#ifdef  __cplusplus
}
#endif

#endif

#endif


