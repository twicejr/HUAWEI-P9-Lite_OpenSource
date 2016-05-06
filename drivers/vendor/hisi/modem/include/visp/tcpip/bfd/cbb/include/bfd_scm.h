/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_sh.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD SCM
*  Date Created: 2006-12-04
*        Author: Wangchengyang
*   Description: BFD Shell 函数声明以及宏定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-07   Wangchengyang    Create
*  2009-01-20   wangchengyang    VISP1.7C03 VRF,多个函数声明增加入参
*******************************************************************************/
#ifndef _BFD_SCM_H_
#define _BFD_SCM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
ULONG BFD_Core_SessionCreate(ULONG *pulDstIP, ULONG *pulSrcIP, ULONG ulOutIfIndex, ULONG * pulSessionID, ULONG ulVrfIndex,ULONG ulIpVer,ULONG ulStartId);
*/

/*SGSN需求DTS2010090200956: BFD 多会话和应用共用问题*/
typedef struct tagBFD_CORE_SESSION_CREATE_S { 
    ULONG ulIpVer;
    ULONG ulDstIP[4];
    ULONG ulSrcIP[4];
    ULONG ulOutIfIndex;
    ULONG ulVrfIndex;
    ULONG ulStartId;
    ULONG ulBfdType;
    /* Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05  增加BFD创建的协议类型字段 */   
    ULONG ulBfdProtocol;
    /*Added by zhongyu206043, 增加BFD中的TOS值设置 for S.BFD.1.1, 2012/10/11 */
    UCHAR ucTos;
    UCHAR ucRes[3]; /* 保证字节对齐 */
    ULONG ulRemoteDiscr;
    /* Added by fengjing209023 for S-BFD-MultiSession.CFG.001 置为BFD_ON会生效，其他默认不生效 */
    ULONG ulMultiHopFlag;       /* 如果置上该标记，则在多跳下也是用3784，否则默认4784 */
}BFD_CORE_SESSION_CREATE_S;

ULONG BFD_Core_SessionCreate(BFD_CORE_SESSION_CREATE_S *pstSession, ULONG * pulSessionID);

/*Added by guojianjun178934, BFD问题单同步处理, 2013/11/18   问题单号:DTS2013111409068 */
/*Modified by q62011 for DTS2013101602773 在批量操作的情况下，会出现BFD队列满导致
        满规格的配置失败因此通过优化，减少一个消息,2013/10/17*/
ULONG BFD_Core_SessionCreateByParam(BFD_CORE_SESSION_CREATE_S *pstSession, BFD_SESSION_PARA_S *pSessPara,ULONG * pulSessionID);
/* End of Added by guojianjun178934, 2013/11/18   问题单号:DTS2013111409068 */

ULONG BFD_SessionCreateBySlave(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex, ULONG ulSessionID,ULONG ulIpVer,ULONG ulVrfIndex);

ULONG BFD_Core_SessionDelete(ULONG ulSessionID,ULONG ulVrfIndex);

ULONG BFD_Core_DeleteSingleApp(ULONG ulSessionID, ULONG ulAppID,ULONG ulVrfIndex, ULONG ulIPVertion);

ULONG BFD_Core_SessionParaUpdate(ULONG ulSessionID, BFD_SESSION_PARA_S *pSessPara,ULONG ulVrfIndex, ULONG ulIpVer);

ULONG BFD_Core_SetSingleAppToSession(ULONG ulSessionID, ULONG ulAppID,ULONG ulVrfIndex, ULONG ulIPVertion);

ULONG BFD_Core_SetAppsToSession(ULONG ulSessionID, ULONG ulAppGroup,ULONG ulVrfIndex, ULONG ulIPVertion);

ULONG BFD_Core_SetWtrTime(ULONG ulSeconds);

ULONG BFD_SCM_ProcZeroDiscr (BFD_PACKET_S *pstPkt,BFD_SESS_ENTRY_S *pstSessEntry);

ULONG BFD_SCM_ProcPkt( BFD_SESS_ENTRY_S *pstSessEntry ,  BFD_PACKET_S *pstPkt );

ULONG BFD_SCM_ProcAsyncPkt( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt);

ULONG BFD_SCM_ProcDemandPkt ( BFD_SESS_ENTRY_S *pstSessEntry , BFD_PACKET_S *pstPkt );

ULONG BFD_Core_SessionAdminister(ULONG ulSessionID, BOOL_T bShutdown,ULONG ulVrfIndex);

ULONG BFD_Core_GetSessionInfo(ULONG ulSessionID, BFD_SESSION_INFO_S *pSess, ULONG ulVrfIndex);

ULONG BFD6_Core_GetSessionInfo(ULONG ulSessionID, BFD6_SESSION_INFO_S *pSess, ULONG ulVrfIndex);

ULONG BFD_Core_GetNextSessionID(ULONG ulSessionID,ULONG ulVrfIndex, ULONG ulIpVersion);

ULONG BFD_Core_SetDebugSwitch(ULONG ulSessionID, ULONG ulDebug,ULONG ulVrfIndex);

ULONG BFD_Core_GetDebugSwitch(ULONG ulSessionID, ULONG *pulDebug,ULONG ulVrfIndex);

ULONG BFD_Core_DemandQueryByApp(ULONG ulSessionID,ULONG ulVrfIndex);

ULONG BFD_Core_SessionCountClr(UCHAR ucSpecSessFlag,ULONG ulLocalDiscr,ULONG ulVrfIndex, ULONG ulIpVersion);

ULONG BFD_Core_Hook_Register(BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc);

ULONG BFD_Core_Hook_UnRegister(BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc);

ULONG BFD_Core_GetSessionIdByName(UCHAR *pszSessName,ULONG *pulSessionId,ULONG ulVrfIndex);

ULONG BFD_Core_GetNameBySessionId(ULONG ulSessionId,UCHAR *pszSessName,ULONG ulLength,ULONG ulVrfIndex);

ULONG BFD_Core_AddSessionName(ULONG ulSessionID,UCHAR *pszSessName,ULONG ulVrfIndex);

ULONG BFD_Core_AddSessionDesc(ULONG ulSessionID,UCHAR *pszSessDesc,ULONG ulVrfIndex);

ULONG BFD_Core_GetSessionConfig(ULONG ulSessionId,BFD_SESSION_CONFIG_INFO_S *pstSessConfig,ULONG ulVrfIndex);

ULONG BFD_Core_GetSessionAllInfo(ULONG ulSessionId,BFD_SESSION_ALL_INFO_S *pstSessInfo,ULONG ulVrfIndex);

ULONG BFD_Core_GetSessionCount(ULONG ulSessionId,BFD_SESSION_COUNT_S *pstCount,ULONG ulVrfIndex);

ULONG BFD_Core_GetSessionBriefInfo(ULONG ulSessionId,BFD_SESSION_BRIEF_INFO_S *pstBriefInfo,ULONG ulVrfIndex);

ULONG BFD_Core_GetNextSessionByFilter(UINTPTR ulEntryWaitList,ULONG *pulVrfIndex,ULONG *pulSessionId);

ULONG BFD_Core_VrfHook_Register(BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc);

ULONG BFD_Core_VrfHook_UnRegister(BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc);

VOID BFD_Core_ShowSessionCountByVrf(ULONG ulVrfIndex, ULONG ulIpVersion);
VOID BFD_Core_ShowSessionInfoByVrf(ULONG ulVrfIndex, ULONG ulIpVersion);
extern ULONG BFD_GetVrfNameByIndex(CHAR *pszVrfName,ULONG ulVrfIndex);

ULONG BFD6_Core_GetSessionConfig(ULONG ulSessionId,BFD6_SESSION_CONFIG_INFO_S *pstSessConfig,ULONG ulVrfIndex);

ULONG BFD6_Core_GetSessionAllInfo(ULONG ulSessionId,BFD6_SESSION_ALL_INFO_S *pstSessInfo,ULONG ulVrfIndex);

ULONG BFD6_Core_GetNextSessionByFilter(UINTPTR ulEntryWaitList,ULONG *pulVrfIndex,ULONG *pulSessionId);

ULONG BFD_Core_RecvPktWithInfo(BFD_CONTROL_PACKET_S *pBfdPkt,ULONG ulPaketLen,BFD_PKTINFO_S *pstPktInfo);

ULONG BFD6_RecvPacket(CHAR *pBFD6Packet, ULONG ulPktLenth, BFD_PKTINFO_S *pstRcvPktInfo);

ULONG BFD6_Core_Hook_Register(BFD6_NOTIFY_HOOK_FUNC pBfd6NotifyHookFunc);

ULONG BFD6_Core_Hook_UnRegister(BFD6_NOTIFY_HOOK_FUNC pBfd6NotifyHookFunc);

ULONG BFD_Core_SetFirstNegoTimes(ULONG ulTimes);

ULONG BFD_Core_GetIpVerBySessionId(ULONG ulSessionId,ULONG ulVrfIndex,ULONG *pulIpVer);

VOID BFD_Core_SetRelationFlage(BOOL_T bFlag);
ULONG BFD_Core_SetSessionTosByVrf(ULONG ulSessionID, ULONG ulVrfIndex, UCHAR ucTos);


VOID BFD_NotifyTimerOut(ULONG ulVrfBfdIndex,ULONG ulTimerId);
ULONG BFD_Core_SetNotifyTime(ULONG ulTimes);
ULONG BFD_Core_SetNotifyTimeFlag( ULONG ulFlag);
ULONG BFD_Core_SetDontSendAdminDownPktFlag(ULONG ulSessionID, ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_Core_GetSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: get BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: BFD_STATISTIC_S *pstStat
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_Core_GetSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId, BFD_STATISTIC_S * pstStat);

/*******************************************************************************
*    Func Name: BFD_Core_ClrSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: show BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_Core_ClrSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId);

/*******************************************************************************
*    Func Name: BFD_Core_GetBfdVersion
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: get BFD ip version
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: ULONG *pulVersion: BFD_OVER_IPV4/BFD_OVER_IPV6
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_Core_GetBfdSessionVersion(ULONG ulVrfIndex, ULONG ulSessionId, ULONG *pulVersion);

/*******************************************************************************
*    Func Name: BFD_Core_CheckCapability
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: check bfd capability
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_Core_CheckCapability(ULONG ulVrfIndex, ULONG ulSessionId);

/*Added by guojianjun178934, S-IP-C20-001-BFD6.001 BFD6和OSPFv3联动，要做刷新动作, 2014/8/13   问题单号:DOPRA-15  */
/*******************************************************************************
*    Func Name: BFD4_Core_CheckSession
* Date Created: 2014-08-13
*       Author: guojianjun178934
*  Description: BFD4会话有效性检查
*        Input: ULONG ulVrfIndex:
*               ULONG ulSessionId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-13   guojianjun178934        Create
*
*******************************************************************************/
ULONG BFD4_Core_CheckSession(ULONG ulVrfIndex, ULONG ulSessionId);

/*******************************************************************************
*    Func Name: BFD6_Core_CheckSession
* Date Created: 2014-08-13
*       Author: guojianjun178934
*  Description: BFD6会话有效性检查
*        Input: ULONG ulVrfIndex:
*               ULONG ulSessionId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-13   guojianjun178934        Create
*
*******************************************************************************/
ULONG BFD6_Core_CheckSession(ULONG ulVrfIndex, ULONG ulSessionId);

/*******************************************************************************
*    Func Name: BFD_Core_CheckSession
* Date Created: 2014-08-13
*       Author: guojianjun178934
*  Description: BFD会话有效性检查(BFD4/BFD6)
*        Input: ULONG ulVrfIndex:
*               ULONG ulSessionId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-13   guojianjun178934        Create
*
*******************************************************************************/
ULONG BFD_Core_CheckSession(ULONG ulVrfIndex, ULONG ulSessionId);
/* End of Added by guojianjun178934, 2014/8/13   问题单号:DOPRA-15  */



/*******************************************************************************
*    Func Name: BFD_Core_GetNextSessionByFilterEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 根据指定的过滤条件获取关键数据
*        Input: pFilter: 过滤器
*                 pCurEntry: 起始的关键数据
*       Output: 下一个符合条件的关键数据
*       Return: 成功返回       关键数据指针
*               失败返回       NULL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_Core_GetNextSessionByFilterEx(UINTPTR ulEntryWaitList,ULONG *pulVrfIndex,ULONG *pulSessionId);
/*******************************************************************************
*    Func Name: BFD_Core_GetSessionConfigEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 根据指定的会话索引获取会话配置信息
*        Input: pulSessionId: 会话索引
*               ulVrfIndex:  VRF索引
*       Output: pstSessConfig: 配置信息
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE    
*                              BFD_ERR_HA_IS_SMOOTHING    
*                              BFD_ERR_NULL_POINTER    
*                              BFD_ERR_SESSION_ID    
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_Core_GetSessionConfigEx(ULONG ulSessionId,BFD_SESSION_CONFIG_INFO_EX_S *pstSessConfig,ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: BFD_Core_GetSessionCountEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 根据指定的会话索引获取会话统计信息
*        Input: ulSessionId: 会话索引
*               ulVrfIndex:  VRF索引
*       Output: pstCount: 会话统计信息
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE    
*                              BFD_ERR_HA_IS_SMOOTHING    
*                              BFD_ERR_NULL_POINTER    
*                              BFD_ERR_SESSION_ID    
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_Core_GetSessionCountEx(ULONG ulSessionId,BFD_SESSION_COUNT_EX_S *pstCount,ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: BFD_Core_GetSessionAllInfoEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 根据指定的会话索引获取会话信息
*        Input: ulSessionId: 会话索引
*               ulVrfIndex:  VRF索引
*       Output: pstSessInfo: 会话信息
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE    
*                              BFD_ERR_HA_IS_SMOOTHING    
*                              BFD_ERR_NULL_POINTER    
*                              BFD_ERR_SESSION_ID    
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_Core_GetSessionAllInfoEx(ULONG ulSessionId, BFD_SESSION_ALL_INFO_EX_S *pstSessInfo, ULONG ulVrfIndex);


/*******************************************************************************
*    Func Name: BFD_GetSessEntry
* Date Created: 2014-09-03
*       Author: caiqizheng183667
*  Description: 获取会话信息
*        Input: ULONG ulSessID: 会话ID
*               ULONG ulVrfIndex:Vrf索引
*       Output: 
*       Return: BFD_SESS_ENTRY_S *
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-03   caiqizheng183667         Creat
*******************************************************************************/
extern BFD_SESS_ENTRY_S *BFD_GetSessEntry(ULONG ulSessID, ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SesssionCountByVrf
* Date Created: 2014-12-13
*       Author: caiqizheng183667
*  Description: 增加/减少对应VRF索引下的BFD会话个数
*        Input: ULONG ulType:  VRP_NO表示减少; VRP_YES表示增加
*               BFD_SESS_ENTRY_S *pstBFDSessEntry
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13  caiqizheng183667         Creat
*******************************************************************************/
extern VOID BFD_SesssionCountByVrf(ULONG ulType, BFD_SESS_ENTRY_S *pstBFDSessEntry);

/*******************************************************************************
*    Func Name: BFD_AddSessionToTree
* Date Created: 2014-12-13
*       Author: caiqizheng183667
*  Description: 增加BFD会话结点到树上
*        Input: BFD_SESS_ENTRY_S *pstBFDSessEntry
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13  caiqizheng183667         Creat
*******************************************************************************/
extern VOID BFD_AddSessionToTree(BFD_SESS_ENTRY_S *pstBFDSessEntry);

/*******************************************************************************
*    Func Name: BFD_DelSessionFromTree
* Date Created: 2014-12-13
*       Author: caiqizheng183667
*  Description: 从树上删除BFD会话结点
*        Input: BFD_SESS_ENTRY_S *pstBFDSessEntry
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13  caiqizheng183667         Creat
*******************************************************************************/
extern VOID BFD_DelSessionFromTree(BFD_SESS_ENTRY_S *pstBFDSessEntry);

/*******************************************************************************
*    Func Name: BFD_FreeSessionResource
* Date Created: 2014-12-13
*       Author: caiqizheng183667
*  Description: 释放BFD会话资源
*        Input: BFD_SESS_ENTRY_S *pstBFDSessEntry
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13  caiqizheng183667         Creat
*******************************************************************************/
extern VOID BFD_FreeSessionResource(BFD_SESS_ENTRY_S *pstBFDSessEntry);

/*******************************************************************************
*    Func Name: BFD_RemoveSessionByVrfIndex
* Date Created: 2014-12-13
*       Author: caiqizheng183667
*  Description: 删除指定VRF下所有的BFD会话
*        Input: ULONG ulVrfIndex
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13  caiqizheng183667         Creat
*******************************************************************************/
extern VOID BFD_RemoveSessionByVrfIndex(ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_RemoveAllSession
* Date Created: 2014-12-13
*       Author: caiqizheng183667
*  Description: 删除所有的BFD会话
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13  caiqizheng183667         Creat
*******************************************************************************/
extern VOID BFD_RemoveAllSession();

/*******************************************************************************
*    Func Name: BFD_SessionTreeCompare
* Date Created: 2014-12-13
*       Author: caiqizheng183667
*  Description: 比较BFD会话sessionid的大小
*        Input: VOID* a
*               VOID* b
*       Output: 
*       Return: LONG
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13  caiqizheng183667         Creat
*******************************************************************************/
extern LONG BFD_SessionTreeCompare(VOID* a, VOID* b);

#ifdef __cplusplus
}
#endif

#endif

