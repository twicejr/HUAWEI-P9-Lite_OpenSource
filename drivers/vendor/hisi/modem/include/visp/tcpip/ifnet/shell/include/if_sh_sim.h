/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                        IF_SH_SIM.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _IF_SH_SIM_H_
#define _IF_SH_SIM_H_

#ifdef  __cplusplus
extern "C"{
#endif
#include"tcpip/ifnet/include/ifnet_api.h"


#define  LINE_IFNET_CREATE          0
#define  LINE_IFNET_ENABLE          1
#define  LINE_IFNET_DISABLE         2
#define  LINE_IFNET_DELETE          3

extern IF_MOD_INFO_S    gstIFModInfo;      /* IFNET模块信息 */

extern struct IIF_IFS_IntFunVtbl  gstIfUPIntFun;      /*上层模拟接口*/
extern struct IIF_IFS_IntFunVtbl  gstIfLinkIntFun;    /*链路层模拟接口*/
extern struct IIF_IFS_IntFunVtbl  gstIfConsoleLinkIntFun;  /* Console类链路层模拟接口 (无IP层) */
extern struct IIF_IFS_IntFunVtbl  gstIfLoopUpIntFun;        /* Loop类上层模拟接口 (无链路层)*/
extern struct IIF_IFS_IntFunVtbl  gstIfNullUpIntFun;        /* Null类上层模拟接口 */
extern struct IIF_IFS_IntFunVtbl  g_stIfVIUpIntFun;         /* VI类上层模拟接口 */
extern struct IIF_IFS_IntFunVtbl  g_stIfUIUpIntFun;         /* UI类上层模拟接口 (无链路层) */
extern struct IIF_IFS_IntFunVtbl  g_stIfTunnelUpIntFun;     /* Tunnel类上层模拟接口 (无链路层) */


/* NULL, Template, Mp, dailer 类( 逻辑接口的物理层控制 )模拟接口 */
/*extern struct IIF_IFS_IntFunVtbl  gstIfLogicDevIntFun;*/     

extern struct IIF_IFS_IntFunVtbl  gstIfLoopBackUpIntFun; /* LoopBack类上层模拟接口 (无链路层)*/

extern struct IIF_IFS_IntFunVtbl  gstIfVTPhyIntFun;       /* VISP.III. VT类虚拟底层模拟接口 */
extern struct IIF_IFS_IntFunVtbl  gstIfDialerPhyIntFun;  /* VISP.III. Dialer类虚拟底层模拟接口 */
extern struct IIF_IFS_IntFunVtbl  gstIfMpGroupPhyIntFun; /* VISP.III. Mp-group类虚拟底层模拟接口 */
extern struct IIF_IFS_IntFunVtbl  gstIfVTChanPhyIntFun;  /* VISP.III. VA类虚拟底层模拟接口 */
extern struct IIF_IFS_IntFunVtbl  gstIfDialerVAPhyIntFun;
extern struct IIF_IFS_IntFunVtbl  gstIfTrunkPhyIntFun;   /* VISPV1R6 Trunk接口虚拟底层模拟接口 */
extern struct IIF_IFS_IntFunVtbl g_stIfVlanifPhyIntFun;  /* VLANIF类虚拟底层模拟接口 */


ULONG IF_Sim_Init();
ULONG IF_Sim_IPInit(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_IPFreeBlock(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_LineInit(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

ULONG IF_Sim_LineFreeBlock(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_LoopIPInit(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_LoopBackIPInit(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_NullIPInit(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_VIIPInit(IFNET_S * pIf, ULONG ulPosition, ULONG * pulRet);
ULONG IF_Sim_UIIPInit(IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);


ULONG IF_Sim_LogicIfIPFreeBlock(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_Logic_PhyInit(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_Logic_PhyFreeBlock(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

ULONG IF_Sim_BackHoleInit(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_BackHoleCmdBuild(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_BackHoleHideCommand(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
ULONG IF_Sim_BackHoleFreeBlock(IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

ULONG NULL_IOCtl(IFNET_S *pIf, ULONG ulCmd, CHAR *pData);
ULONG NULL_Output(MBUF_S* pMBuf);
ULONG LO_IOCtl(IFNET_S *pIf, ULONG ulCmd, CHAR *pData);
ULONG LO_Output(MBUF_S* pMBuf);

ULONG IF_VT_Output(MBUF_S * pMbuf);
ULONG IF_Logic_PhyInit(IFNET_S* pIf) ;
ULONG IF_Logic_SetPhyType(IFNET_S* pIf,ULONG ulPhyType);
ULONG IF_Logic_PhyIOCtl(UINTPTR ulPhyLink,ULONG ulCmd,CHAR * pData);
ULONG IF_Sim_VTPhyInit(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Sim_DialerPhyInit(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Sim_MpGroupPhyInit(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Sim_DialerVAPhyInit(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Sim_VTChanPhyInit(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Sim_TrunkPhyInit(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Sim_TrunkFreeBlock(IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);
ULONG IF_DeleteTrunkIf(IFNET_S* pIf);

ULONG VI_IOCtl(IFNET_S * pIf, ULONG ulCmd, CHAR * pData);
ULONG VI_Output(MBUF_S * pstMBuf);

ULONG UI_LinkDownIOCtl(IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);
ULONG UI_LinkIoCtl(IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);
ULONG UI_Output(MBUF_S* pstMBuf);
ENQUEUE_PF UI_LinkInput(IFNET_S *pstIf, MBUF_S* pstMBuf);

ULONG IF_Sim_VlanifPhyInit(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Sim_VlanifFreeBlock(IFNET_S* pIf, ULONG ulPosition, ULONG *pulRet);
ULONG IF_Tunnel_Output(MBUF_S* pstMBuf);
ULONG IF_Tunnel_IOCtl(IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);
ULONG IF_Sim_TunnelIPInit(IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);
ULONG IF_Tunnel_LinkIoCtl(IFNET_S* pIf, ULONG ulCmdIndex, CHAR *pData);

#ifdef  __cplusplus
}
#endif

#endif  /* _IF_SH_SIM_H_ */

