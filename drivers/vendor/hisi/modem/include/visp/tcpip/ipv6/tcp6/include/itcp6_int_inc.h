/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : itcp6_com_inc.h
  Version       : IPBIR V1R3
  Author        : Sandeep71635
  Created       : 2007/12/10
  Last Modified :
  Description   : The inc file for interfaces between core and shell of TCP6
  Function List :
  History       :
  1.Date        : 2007/12/10
    Author      : Sandeep71635
    Modification: Created file

******************************************************************************/
#ifndef _IP6_TCP6_H
#define _IP6_TCP6_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "common/ipos/ipv6/itcp6_inc.h"
#include "ipv6/tcp6/include/tcp6_int_pub.h"

/* Component Information */
extern struct ComponentInfo m_CompTCP6Info;

/*Begin: Changed for VISPV1R7 integration by wan, 2008-05-02*/
#define IID_IP6_TCP6_INIT            (IID_IPV6_BASE + 22)
#define IID_IP6_TCP6_TEST           (IID_IPV6_BASE + 23)
/*End of change for VISPV1R7 integration, 2008-05-02*/

DECLARE_INTERFACE (IIF_IP6_TCP6_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfTCP6_Init_Com) (COM_ID_INFO_S *pComInfo,
        ULONG ulComLen);
    METHOD_(ULONG, pfTCP6_Activate_Com)();
    METHOD_(VOID, pfTCP6_Set_Module_Info)(TCP6_MOD_INFO_S *pTCP6SetModuleInfo);
    METHOD_(ULONG,  pfTCP6_RegisterAll)
        (IP6_TCP6_SH_CALLBACUP_SET_S *pfTCP6CallBack);
};

typedef struct tagTCP6_INT_OBJ_S
{
    IIF_IP6_TCP6_INIT * pstIComInt_TCP6_Init;
    IIF_IP6_TCP6_CFG * pstIComInt_TCP6_Cfg;
    IIF_IP6_TCP6_FUN * pstIComInt_TCP6_Fun;
} TCP6_INT_OBJ_S;

#ifdef  __cplusplus
}
#endif

#endif  /* _IP6_TCP6_H */
