/*******************************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-------------------------------------------------------------------------------
*                              raw_ip6_sh_cfg.h
*
*    Project Code: VRP5.0
*    Module Name:  IP6 Raw IP6
*    Create Date:  2006/06/20
*         Author:  Arvind Saproo
*     Description: Shell cfg implementation header file for Raw IP6 module
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*
*
*
********************************************************************************
*/

#ifndef _RAW_IP6_SH_CFG_H_
#define _RAW_IP6_SH_CFG_H_

#ifdef    __cplusplus
extern    "C"{
#endif


#define TBL_RAWIP6_SHOW_COM_VERSION              0x1

#define CMO_RAWIP6_SHOW_COM_VERSION      \
                  CFG_CMO_DEF( MID_RIP6, TBL_RAWIP6_SHOW_COM_VERSION, 1)
#define CMO_RAWIP6_SHOW_COM_TEST_VERSION \
                  CFG_CMO_DEF( MID_RIP6, TBL_RAWIP6_SHOW_COM_VERSION, 2)

/* Added by Anand - V1R7 Workspace Integration */
#define RAWIP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* Enum container for UDP6 command elements */
enum enum_UDP6
{
    RAWIP6_CMDELEMENT_SHOWCOM,
    RAWIP6_CMDELEMENT_SHOWCOMVER,
    RAWIP6_CMDELEMENT_SHOWCOMTESTVER,
    RAWIP6_CMDELEMENT_SHOWCOMVERRAWIP6,
    RAWIP6_CMDELEMENT_SHOWCOMTESTVERRAWIP6

};


extern struct IIF_IP6_RIP6_INITVtbl          * g_pstRIP6ComInitTable;
extern struct IIF_IP6_RIP6_CFGVtbl          * g_pstRIP6ComCfgTable;
extern struct IIF_IP6_RIP6_FUNVtbl          * g_pstRIP6ComFunTable;

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
