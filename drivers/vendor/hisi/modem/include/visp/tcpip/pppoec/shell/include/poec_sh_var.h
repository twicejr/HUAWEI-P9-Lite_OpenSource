/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_sh_var.h 
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11  
 *        Author: liuhui
 *   Description: PPPoE Client模块Shell部分全局变量的引用说明
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE            NAME                DESCRIPTION
 *  2003-01-11      liuhui              Created file
 *  2005-09-15      t45114              Modify
 *  2006-03-30      liai                Adjust for D00660
 *  2006/04/21      liai                Adjust for D00865
 *  2006-05-13      l48923              Delete useless code
 *  
 ************************************************************************/

#ifndef  _POEC_SH_VAR_H_
#define  _POEC_SH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/*全局PPPoE Client Discovery阶段定时器ID，供所有Session 的padi和padr报文使用*/
extern ULONG  g_ulPPPoEClientDisTimerID;

/*全局IDLE Timer超时定时器ID */
extern ULONG  g_ulPPPoEClientIdleTimerID;

/*全局PPPoE Client模块Session字符串*/
extern CHAR *g_PPPoESessionInfo[2];

/*全局PPPoE Client模块Session 状态字符串*/
extern CHAR *g_SessionState[]; 

extern CHAR g_cPppoeClientDebugBuf[];

extern CHAR *Inf_PPPOE_Client_En[];   /* 英文帮助信息 */

extern struct ComponentInfo m_PPPOE_CLIENT_CompInfo;  /* PPPOE组件信息 */

extern struct IIF_PPPOE_CLIENT_ComIntCFGVtbl   * g_pstPPPOEClientComCfgTable; /* PPPOE配置管理虚函数表 */
extern struct IIF_PPPOE_CLIENT_ComIntFUNVtbl   * g_pstPPPOEClientComFunTable; /* PPPOE功能函数虚表 */
extern struct IIF_PPPOE_CLIENT_ComIntSSAVtbl   * g_pstPPPOEClientComSsaTable; /* PPPOE系统支持虚函数表 */

extern APP_INIT_INFO_S g_stPPPoEClientAppInfo; 

#if __cplusplus
}
#endif

#endif

