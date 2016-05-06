/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : iudp6_com_inc.h
  Version       : Initial Draft
  Author        : Sandeep71635
  Created       : 2007/12/9
  Last Modified :
  Description   : iudp6_com_inc.h header file
  Function List :
  History       :
  1.Date        : 2007/12/9
    Author      : Sandeep71635
    Modification: Created file

******************************************************************************/
#ifndef __IUDP6_COM_INC_H__
#define __IUDP6_COM_INC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "common/ipos/ipv6/iudp6_inc.h"
#include "ipv6/udp6/include/udp6_int_pub.h"

/* Component Information */
extern const struct ComponentInfo m_CompUDP6Info;

/*Begin: Changed for VISPV1R7 integration by wan, 2008-05-02*/
#define IID_IP6_UDP6_INIT            (IID_IPV6_BASE + 32)
#define IID_IP6_UDP6_TEST           (IID_IPV6_BASE + 33)
/*End of change for VISPV1R7 integration, 2008-05-02*/

DECLARE_INTERFACE (IIF_IP6_UDP6_INIT)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIP6_UDP6_Init_Com)(const COM_ID_INFO_S *pComInfo,
        ULONG ulComLen);
    METHOD_(ULONG, pfIP6_UDP6_Activate_Com)();
    METHOD_(ULONG, pfIP6_UDP6_SetModuleInfo)(IP6_UDP6_MOD_INFO_S *pMInfo);
    METHOD_(ULONG,  pfIP6_UDP6_RegisterAll)(
        IP6_UDP6_SH_CALLBACUP_SET_S * pfUDP6CallBack);

};

typedef struct tagUDP6_INT_OBJ_S
{
    IIF_IP6_UDP6_INIT * pstIComInt_UDP6_Init;
    IIF_IP6_UDP6_CFG * pstIComInt_UDP6_Cfg;
    IIF_IP6_UDP6_FUN * pstIComInt_UDP6_Fun;
} UDP6_INT_OBJ_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __IUDP6_COM_INC_H__ */
