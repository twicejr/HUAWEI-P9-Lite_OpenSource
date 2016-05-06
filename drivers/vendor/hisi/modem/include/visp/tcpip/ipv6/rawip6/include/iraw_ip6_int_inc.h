/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              iraw_ip6_inc.h
*
*    Project Code:  VRP5.0
*    Module Name: IP6 RawIp6
*    Create Date:   2003/06/23
*    Author:           Sunil Dutt
*    Description:    To define RawIp6 component interfaces
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2003-06-23  Sunil Dutt    Create
************************************************************************
*/

#ifdef  __cplusplus
extern "C"{
#endif

#include "common/ipos/ipv6/iraw_ip6_inc.h"
#include "ipv6/rawip6/include/raw_ip6_int_pub.h"

extern const struct ComponentInfo m_CompRIP6Info;

/*Begin: Changed for VISPV1R7 integration by wan, 2008-05-02*/
#define IID_IP6_RIP6_INIT            (IID_IPV6_BASE + 42)
#define IID_IP6_RIP6_TEST           (IID_IPV6_BASE + 43)
/*End of change for VISPV1R7 integration, 2008-05-02*/

/* The initialization interface provided by the component. */
DECLARE_INTERFACE (IIF_IP6_RIP6_INIT)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIP6_RIP6_Init_Com) (COM_ID_INFO_S *pComInfo, \
                                            ULONG ulComLen);
    METHOD_(ULONG, pfIP6_RIP6_Activate_Com)();
    METHOD_(ULONG, pfIP6_RIP6_SetModuleInfo) (IP6_RIP6_MOD_INFO_S *pMInfo);
};


/*RIP6 interface object*/
typedef struct tagRIP6_INT_OBJ
{
    IIF_IP6_RIP6_INIT * pstIComInt_RIP6_Init;
    IIF_IP6_RIP6_CFG * pstIComInt_RIP6_Cfg;
    IIF_IP6_RIP6_FUN * pstIComInt_RIP6_Fun;
} RIP6_INT_OBJ_S;




#ifdef  __cplusplus
}
#endif


