/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              idhcp4r.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R 
*  Date Created: 2007-7-11
*        Author: LY(57500)
*   Description: DHCP4R 组件定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-11  LY(57500)     Create the first version.
*
*******************************************************************************/

#ifndef _IDHCP4R_H_
#define _IDHCP4R_H_

#ifdef  __cplusplus
extern "C"{
#endif


typedef struct tagDHCP4RModInfo
{    
    ULONG ulModID; 
    
    ULONG ulCfgMode;            /* Relay使能和配置模式      */
    ULONG ulDHCP4RTaskId;       /* Relay任务ID              */
    ULONG ulDHCP4RSocketQId;    /* Relay异步socket消息ID    */
    ULONG ulDHCP4RCntrlQId;     /* Relay控制命令消息队列ID  */
    ULONG ulDHCP4RPortSwitch;   /* Relay是否对外显示端口开关*/
}DHCP4R_MOD_INFO_S;

DECLARE_INTERFACE (IIF_COMP_DHCP4R_ComIntFUN)
{
    IUNKNOWN_METHODS
    METHOD_(VOID,  pfDHCP4R_SetTaskId)(ULONG ulTask);
    METHOD_(ULONG, pfDHCP4R_Notify_CreateSocket)(VOID);
    METHOD_(ULONG, pfDHCP4R_GetPortSwitch)(VOID);

    /* HA相关 */
    METHOD_(ULONG, pfDHCP4R_HA_BatchBackup)(VOID);
    METHOD_(ULONG, pfDHCP4R_HA_RealTimePack)(ULONG ulMsgType, VOID *pData);
    METHOD_(ULONG, pfDHCP4R_HA_Input)(UCHAR *pucData, ULONG ulDataLen);
    METHOD_(ULONG, pfDHCP4R_HA_Smooth)(VOID);
    METHOD_(ULONG, pfDHCP4R_HA_Clean)(VOID);
};

DECLARE_INTERFACE (IIF_COMP_DHCP4R_ComIntCFG)
{
    IUNKNOWN_METHODS
        
    /* 组件相关 */
    METHOD_(ULONG, pfDHCP4R_Init_Com)(const COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfDHCP4R_Active_Com)(VOID);
    METHOD_(ULONG, pfDHCP4R_SetModuleInfo)(DHCP4R_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG, pfDHCP4R_RegShellApi)(DHCP4R_SHELL_CALLBACK_SET_S* pstShellApi);
    
    /* 配置相关 */
    METHOD_(ULONG, pfDHCP4R_RelayEnable)(ULONG ulIndex, ULONG ulSetYes);
    METHOD_(ULONG, pfDHCP4R_CfgServer)(ULONG ulOperate, ULONG ulIndex, ULONG ulServerIP);
    METHOD_(ULONG, pfDHCP4R_CfgOption82)(ULONG ulOperate, ULONG ulIndex,
                                         ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);
    METHOD_(ULONG, pfDHCP4R_GetCfg)(ULONG ulIndex, DHCP4R_CFG_INFO_S *pstDHCP4RCfg);
    METHOD_(ULONG, pfDHCP4R_SetFwdMode)(ULONG ulFwdMode);
    METHOD_(ULONG, pfDHCP4R_GetFwdMode)(ULONG *pulMode);
    METHOD_(ULONG, pfDHCP4R_GetStatistics)(DHCP4R_STATINFO_S *pstDHCP4RStat);
    METHOD_(VOID,  pfDHCP4R_ClearStatistics)(VOID);
    METHOD_(ULONG, pfDHCP4R_SetMaxHops)(ULONG ulhops);
    METHOD_(ULONG, pfDHCP4R_GetMaxHops)(ULONG *pulhops);
    METHOD_(ULONG, pfDHCP4R_SetTos)(UCHAR ucTos);
    METHOD_(ULONG, pfDHCP4R_GetTos)(UCHAR *pucTos);
    METHOD_(ULONG, pfDHCP4R_SetDebug)(ULONG ulOperate, ULONG ulIndex, ULONG ulDebugLevel);
    METHOD_(ULONG, pfDHCP4R_GetDebug)(ULONG ulIndex, ULONG *pulDebug);

    /* 其他模块使用的接口 */    
    METHOD_(ULONG, pfDHCP4R_Notify_IfDelete)(ULONG ulIfIndex);
    METHOD_(ULONG, pfDHCP4R_Cfg_Judge)(ULONG ulIndex);

    /* Vrf相关 */
    METHOD_(ULONG, pfDHCP4R_Notify_VRFDelete)(ULONG ulVrfIndex);
    METHOD_(ULONG, pfDHCP4R_RelayEnableByVrf)(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG ulEnable);
    METHOD_(ULONG, pfDHCP4R_CfgServerByVrf)(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulServerIP);
    METHOD_(ULONG, pfDHCP4R_CfgOption82ByVrf)(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, 
                                              ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);
    METHOD_(ULONG, pfDHCP4R_GetCfgByVrf)(ULONG ulVrfIndex,ULONG ulIfIndex, DHCP4R_CFG_INFO_S *pstDHCP4RCfg);
    METHOD_(ULONG, pfDHCP4R_SetFwdModeByVrf)(ULONG ulVrfIndex, ULONG ulFwdMode);
    METHOD_(ULONG, pfDHCP4R_GetFwdModeByVrf)(ULONG ulVrfIndex, ULONG *pulFwdMode);
    METHOD_(ULONG, pfDHCP4R_GetStatisticsByVrf)(ULONG ulVrfIndex, DHCP4R_STATINFO_S *pstDHCP4RStat);
    METHOD_(VOID,  pfDHCP4R_ClearStatisticsByVrf)(ULONG ulVrfIndex);
    METHOD_(ULONG, pfDHCP4R_SetMaxHopsByVrf)(ULONG ulVrfIndex, ULONG ulMaxHops);
    METHOD_(ULONG, pfDHCP4R_GetMaxHopsByVrf)(ULONG ulVrfIndex, ULONG *pulMaxHops);
    METHOD_(ULONG, pfDHCP4R_SetTosByVrf)(ULONG ulVrfIndex, UCHAR ucTos);
    METHOD_(ULONG, pfDHCP4R_GetTosByVrf)(ULONG ulVrfIndex, UCHAR *pucTos);
    METHOD_(ULONG, pfDHCP4R_SetDebugByVrf)(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulDebugLevel);
    METHOD_(ULONG, pfDHCP4R_GetDebugByVrf)(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG *pulDbgLevel);
    METHOD_(ULONG, pfDHCP4R_SetOpt82ModeByVrf)(ULONG ulVrfIndex,ULONG ulIfIndex, ULONG ulMode);
    METHOD_(ULONG, pfDHCP4R_GetOpt82ModeByVrf)(ULONG ulVrfIndex,ULONG ulIfIndex, ULONG *pulMode);

    /* HA相关 */
    METHOD_(ULONG, pfTCPIP_HA_SetDHCP4RDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfDHCP4R_HA_GetDHCP4RDbg)(ULONG* pulDbg);
    METHOD_(ULONG, pfDHCP4R_HA_SetDHCP4RVerboseDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfDHCP4R_HA_GetDHCP4RVerboseDbg)(ULONG* pulDbg);
    METHOD_(VOID,  pfDHCP4R_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd); 
};
 

DECLARE_INTERFACE (IIF_COMP_DHCP4R_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagDHCP4R_IntObj
{
    struct IIF_COMP_DHCP4R_ComIntFUN    *pCompIntFUN;
    struct IIF_COMP_DHCP4R_ComIntCFG    *pCompIntCFG;
    struct IIF_COMP_DHCP4R_ComIntSSA    *pCompIntSSA;
}DHCP4R_INT_OBJ_S;

#ifdef  __cplusplus
}
#endif      /* end of __cplusplus    */

#endif      /* end of _IDHCP4R_H_   */

