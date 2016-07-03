
#ifndef __DHCPV6S_COMP_H__
#define __DHCPV6S_COMP_H__

extern PTM_COMPONENT_INFO_S g_stDhcpv6sComInfo;
#define DHCPV6S_SELF_CSI             g_stDhcpv6sComInfo.ullSelfCsi
#define DHCPV6S_SELF_SGID            g_stDhcpv6sComInfo.ullSelfSgId
#define DHCPV6S_SELF_CMPIDX          g_stDhcpv6sComInfo.ulSelfCmpIdx
#define DHCPV6S_SELF_CMPIDX_INSG     g_stDhcpv6sComInfo.ulSelfCmpIdxInSG
#define DHCPV6S_HANDLE               g_stDhcpv6sComInfo.ulHandle

#define DHCPV6S_DEFAULT_MAX_APP_MSG_NUM 4096

extern ULONG ulDhcpv6sPerfInitFinish;
extern ULONG DHCPV6S_OmInitial(VOID);

extern VOS_SIZE_T g_UEtoPGW_ulDHCPV6InformRequestNumAddr;
extern VOS_SIZE_T g_PGWtoUE_ulDHCPV6AckNumAddr;
extern VOS_SIZE_T g_UEtoSGW_ulDHCPV6InformRequestNumAddr;
extern VOS_SIZE_T g_SGWtoUE_ulDHCPV6AckNumAddr;

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/
extern ULONG DHCPV6S_CommInit1( VOID);
extern ULONG DHCPV6S_CommInit3( VOID);


/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/


#endif /* end of __DHCPV6S_COMP_H__ */
