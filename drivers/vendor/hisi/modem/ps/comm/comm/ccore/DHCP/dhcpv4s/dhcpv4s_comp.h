
#ifndef __DHCPV4S_COMP_H__
#define __DHCPV4S_COMP_H__

extern PTM_COMPONENT_INFO_S       g_stDhcpv4sComInfo;
#define DHCPS_SELF_CSI            g_stDhcpv4sComInfo.ullSelfCsi
#define DHCPS_SELF_SGID            g_stDhcpv4sComInfo.ullSelfSgId
#define DHCPS_SELF_CMPIDX         g_stDhcpv4sComInfo.ulSelfCmpIdx
#define DHCPS_SELF_CMPIDX_INSG    g_stDhcpv4sComInfo.ulSelfCmpIdxInSG

#ifndef __WIN32_PLATFORM__
#define DHCPS_HANDLE         g_stDhcpv4sComInfo.ulHandle
#else
#define DHCPS_HANDLE         DHCPS_SELF_CSI
#endif

#define DHCPV4S_DEFAULT_MAX_APP_MSG_NUM 4096

extern ULONG ulDhcpv4sPerfInitFinish;
extern ULONG DHCPS_OmInitial(VOID);

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/


typedef enum 
{
    DHCPS_INNER_LEASE_TIMEOUT = 1,
    DHCPS_INNER_STATE_TIMEOUT,
}DHCPS_INNER_MSGCODE_E;


typedef struct tagDHCPS_INNER_MSG_S
{
    ULONG ulMsgCode;
    ULONG ulReserve345;
}DHCPS_INNER_MSG_S;

extern VOS_UINT64 g_ullDhcpv4sUsmCsi;
/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/



/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/
extern ULONG DHCPS_SendRtMsg(VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen );
extern ULONG DHCPS_MallocNode(UCHAR **ppucNode,ULONG ulLength);
extern VOID DHCPS_FreeNode(UCHAR **ppucNode);


#endif /* __DHCPV4S_COMP_H__ */
