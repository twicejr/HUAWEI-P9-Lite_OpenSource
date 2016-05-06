/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ppi.h
*  Project Code: VISPV100R005
*   Module Name: public   
*  Date Created: 2006-04-30
*        Author: x36530
*   Description: NP特性头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-04-30  xiehuaguo(36530)  Creat the first version.
*  2006-6-20   X36317         第二阶段质量改进.
*  2008-04-11  wuhailan       增加NP下发耗时处理相关宏定义
*******************************************************************************/

#ifndef TCPIP_PPI_H
#define TCPIP_PPI_H

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_pub.h"
#include "public/dopra_cbb/include/utlsll.h"




/* NP重复下发相关宏，结构，全局变量等 */
#define PPI_REPEATE_TIME                2000    /* NP重复下发定时器2秒超时一次 */
#define PPI_REPEATE_QUEUE_NUM           1024    /* NP重复下发队列的最大长度 */
#define PPI_REPEATE_MAX_HANDLE          128     /* 每次定时器超时最多处理128个元素 */
#define PPI_REPEATE_MAX_DOWN_TIME       3       /* NP重复下发队列每个元素的最大下发次数 */
#define PPI_REPEATE_DEFAULT_PRIORITY    128     /* NP重复下发队列元素的默认优先级 */
#define PPI_REPEATE_ARG_NUM             5       /* NP重复下发队列元素的参数个数 */


/* NP重复下发机制 */
typedef struct tagPPI_REPEATE
{
    SLL_NODE_S stNode;      /* 全局链表节点 */
    ULONG ulModuleId;       /* 模块ID */
    ULONG ulFailedCount;    /* 累计下发失败次数 */
    ULONG ulPriority;       /* 值越小，优先级越高，默认128 */
    ULONG aulArgs[PPI_REPEATE_ARG_NUM];       /* 回调函数的参数，由各个模块自己解释，下同 */
}PPI_REPEATE_S;

extern SLL_S g_sllPpiRepeate;
extern ULONG g_ulPpiRepeateTimer;
/* NP重复下发相关宏，结构，全局变量等 */



/*NP下发耗时统计处理结构*/
#define PPI_COUNT 5
typedef struct tagPPI_TIME
{
    TCPIP_CPUTICK_S stStartTime[PPI_COUNT];   /*下发记录的开始时间*/
    TCPIP_CPUTICK_S stEndTime[PPI_COUNT];     /*下发记录的结束时间*/
    ULONG           ulOprType[PPI_COUNT];     /*下发的操作类型*/
    ULONG           ulNPUpdateCount;          /*下发次数*/
}PPI_TIME_S;

typedef struct tagNpPppOsicpOption
{
    /* 是否协商 */
    UCHAR neg_Align_NPDU;
    /* 协商参数值 */
    UCHAR ucAlign_NPDU;
    USHORT  usReserved;
}PPI_PPP_OSICP_OPTION_S;

/*NP下发耗前耗时打点*/
extern VOID VOS_GetCpuTick( ULONG *plow,ULONG *phigh );
#define MAKE_NP_STARTDOT(ulMsgType, OprType)\
{\
    if (g_ulNPUpdateSwitch)\
    {\
        ULONG ii = g_stNPPpiTime[ulMsgType].ulNPUpdateCount;\
        ii %= PPI_COUNT;\
        VOS_GetCpuTick( &(g_stNPPpiTime[ulMsgType].stStartTime[ii].ulLowTick),  \
                        &(g_stNPPpiTime[ulMsgType].stStartTime[ii].ulHighTick) );\
        g_stNPPpiTime[ulMsgType].ulOprType[ii] = OprType;\
    }\
}
/*NP下发耗返回后时间打点*/
#define MAKE_NP_ENDDOT(ulMsgType)\
{\
    if (g_ulNPUpdateSwitch)\
    {\
        ULONG ii = g_stNPPpiTime[ulMsgType].ulNPUpdateCount;\
        ii %= PPI_COUNT;\
        VOS_GetCpuTick( &(g_stNPPpiTime[ulMsgType].stEndTime[ii].ulLowTick),  \
                        &(g_stNPPpiTime[ulMsgType].stEndTime[ii].ulHighTick) );\
        g_stNPPpiTime[ulMsgType].ulNPUpdateCount++;\
    }\
}

#define PPP_COPY_LCPPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg acfc:%d", pstOptions->neg_accompression)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg magicnumber:%d", pstOptions->neg_magicnumber));\
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg accm:%d", pstOptions->neg_asyncmap)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg mhf:%d", pstOptions->neg_mhf)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg mrru:%d", pstOptions->neg_mrru)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg mru:%d", pstOptions->neg_mru)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg pfc:%d", pstOptions->neg_pcompression)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg prefix elision:%d", pstOptions->neg_prefix)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg ssnhf:%d", pstOptions->neg_ssnhf)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg discr:%d", pstOptions->neg_discr));\
    if (pstOptions->neg_asyncmap) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\naccm:%d", pstOptions->ulAsyncmap)); \
    } \
    if (pstOptions->neg_mhf) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), \
            P2("\r\ncode:%d, class:%d", pstOptions->ucCode, pstOptions->ucClass)); \
    } \
    if (pstOptions->neg_mrru) \
    { \
        UCHAR ucDiscrLen; \
        UCHAR ucIndex; \
        CHAR  szTemp[LEN_64] = {0}; \
        INT32   i32TempLen = 0; \
        \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmrru:%d", pstOptions->usMrru)); \
        \
        if((pstOptions->ucDiscr_len > PPP_CILEN_DISCR) \
            && (pstOptions->ucDiscr_len <= (PPP_CILEN_DISCR + PPI_MP_MP_DISCR_MAX_LENGTH))) \
        { \
            ucDiscrLen = pstOptions->ucDiscr_len - PPP_CILEN_DISCR; \
            \
            for(ucIndex=0; ucIndex < ucDiscrLen; ucIndex++) \
            { \
                i32TempLen += TCPIP_SNPRINTF(szTemp + i32TempLen, (LEN_64 - i32TempLen), P1("%02x", pstOptions->discr_addr[ucIndex])); \
            } \
            \
            iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P3("\r\nDISCRIMINATOR : Class: %u, Len: %u, Discr: %s", \
                                  pstOptions->ucDiscr_class, ucDiscrLen, szTemp)); \
        } \
    } \
    if (pstOptions->neg_mru) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmru:%d", pstOptions->usMru)); \
    } \
    \
    if(pstOptions->neg_magicnumber) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmagicnumber:%#x", pstOptions->ulMagicnumber)); \
    } \
    if (pstOptions->neg_prefix) \
    { \
        ULONG m; \
        ULONG n; \
        PPI_MC_PREFIX_S*pstPrefixEInfo = NULL; \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("\r\nPrefix-E info:")); \
        for (m = 0; m < PPI_MC_PREFIX_MAX_NUM; m++) \
        { \
            pstPrefixEInfo = &pstOptions->astPrefix[m]; \
            if (pstPrefixEInfo->ucPrefixValid) \
            { \
                iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\nCls:%02d, ", pstPrefixEInfo->ucClass)); \
                iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("Field:")); \
                for (n = 0; n < pstPrefixEInfo->usPrefixLength; n++) \
                { \
                    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("%02x", pstPrefixEInfo->aucPrefix[n])); \
                } \
            } \
        } \
    } \
}

#define PPP_COPY_IPCPPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    CHAR cTemp[LEN_32] = {0}; \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg iphc:%d", pstOptions->neg_iphc)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg vj:%d", pstOptions->neg_vj)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nouraddr:%s",  \
        VOS_IpAddrToStr(VOS_NTOHL(pstOptions->ulOurAddr), cTemp))); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nhisaddr:%s", \
        VOS_IpAddrToStr(VOS_NTOHL(pstOptions->ulHisAddr), cTemp))); \
    if (pstOptions->neg_iphc) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ncompress type:%d", pstOptions->ucCompressType)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nrtp compress type:%d", pstOptions->ucRtpCompressType)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax header:%d", pstOptions->usMaxHeader)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax period:%d", pstOptions->usMaxPeriod)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax time:%d", pstOptions->usMaxTime)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nnon-tcp space:%d", pstOptions->usNonTcpSpace)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ntcp space:%d", pstOptions->usTcpSpace)); \
    } \
} \

#define PPP_COPY_IP6CPPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    ULONG i = 0;\
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg interfaceid:%d", pstOptions->neg_interfaceid)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg compprotocol:%d", pstOptions->neg_compprotocol)); \
\
    if (pstOptions->neg_interfaceid)\
    {\
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("\r\nmy interface id:0x")); \
        for (i = 0; i < INTERFACE_ID_LEN; i++)\
        {\
            iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("%x", pstOptions->my_interface_id[i])); \
        }\
\
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("\r\nhis interface id:0x")); \
        for (i = 0; i < INTERFACE_ID_LEN; i++)\
        {\
            iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("%x", pstOptions->his_interface_id[i])); \
        }\
    }\
\
    if (pstOptions->neg_compprotocol)\
    {\
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ncomp protocol:%#x", pstOptions->comp_protocol)); \
    }\
}

#define PPP_COPY_PMUXPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg default pid:%d", pstOptions->neg_defaultpid)); \
    if (pstOptions->neg_defaultpid) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ndefault pid:%x", pstOptions->usDefaultPid)); \
    } \
} 

#define PPP_COPY_CONFIG_TO_BUF(pcBuf,  iBufLen, iOffset, pstConfig) \
{ \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nPppInterleave:%d", pstConfig->bPppInterleave)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nPppReorderWindow:%d", pstConfig->bPppReorderWindow)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmp min frag len:%d", pstConfig->usMinFragLen)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nlfi max delay LFI:%d", pstConfig->usMaxDelayLFI)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax delay:%d", pstConfig->usMaxDelay)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax frame len:%d", pstConfig->usMaxFrameLen)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax sub frame len:%d", pstConfig->usMaxSubFrameLen)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax sub frame num:%d", pstConfig->usMaxSubFrameNum)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\niphc nego suboptions :%d", pstConfig->ulNegoSubOptions)); \
}
#define NEXTLINE         5


extern ULONG       g_ulNPUpdateSwitch;   /*NP下发耗时计算开关*/
extern PPI_TIME_S  g_stNPPpiTime[PPI_TYPE_END];/*NP下发耗时统计处理变量*/

/*为了防止引用函数名字过长，用宏定义替换*/
#define g_pfTCPIP_PPI_FIB4_Update   g_stPPIHook.pfTCPIP_PPI_FIB4_Update     
#define g_pfTCPIP_PPI_ARP_Update    g_stPPIHook.pfTCPIP_PPI_ARP_Update      
#define g_pfTCPIP_PPI_IFNET_Update  g_stPPIHook.pfTCPIP_PPI_IFNET_Update   
#define g_pfTCPIP_PPI_PPP_Update    g_stPPIHook.pfTCPIP_PPI_PPP_Update      
#define g_pfTCPIP_PPI_IP4_Output    g_stPPIHook.pfTCPIP_PPI_IP4_Output
/* add by l57500 for trunk np, 06-12-06*/
#define g_pfTCPIP_PPI_TRUNKPORT_Update g_stPPIHook.pfTCPIP_PPI_TRUNKPORT_Update

/*Add by z62474 for 2007-09-10 ,增加OSI对NP的支持*/
#define g_pfTCPIP_PPI_OSI_Output    g_stPPIHook.pfTCPIP_PPI_OSI_Output

/* 3ah ppi update */
#define     g_pfTCPIP_PPI_3AH_Update    g_stPPIHook.pfTCPIP_PPI_3AH_Update

#define     g_pfTCPIP_PPI_1AG_Update    g_stPPIHook.pfTCPIP_PPI_1AG_Update

/*add by z62531 for support igmp*/
#define     g_pfTCPIP_PPI_IGMP_Update    g_stPPIHook.pfTCPIP_PPI_IGMP_Update

/* l2if ppi  */
#define     g_pfTCPIP_PPI_VLAN_Update    g_stPPIHook.pfTCPIP_PPI_VLAN_Update
#define     g_pfTCPIP_PPI_PORT_Update    g_stPPIHook.pfTCPIP_PPI_PORT_Update
#define     g_pfTCPIP_PPI_MAC_Update     g_stPPIHook.pfTCPIP_PPI_MAC_Update
#define     g_pfTCPIP_PPI_QINQ_Update    g_stPPIHook.pfTCPIP_PPI_QINQ_Update

/* vrrp ppi */
#define     g_pfTCPIP_PPI_VRRP_Update    g_stPPIHook.pfTCPIP_PPI_VRRP_Update

/* multicase mac */
#define     g_pfTCPIP_PPI_CTRL_Update     g_stPPIHook.pfTCPIP_PPI_CTRL_Update

#define g_pfTCPIP_PPI_MAP_Update g_stPPIHook.pfTCPIP_PPI_MAP_Update
#define g_pfTCPIP_PPI_FIB6_Update g_stPPIHook.pfTCPIP_PPI_FIB6_Update
/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05   */
#define     g_pfTCPIP_PPI_VRF_Update    g_stPPIHook.pfTCPIP_PPI_VRF_Update
/* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

#define g_pfTCPIP_PPI_TRUNKBIND_Update    g_stPPIHook.pfTCPIP_PPI_TRUNKBIND_Update     
#define g_pfTCPIP_PPI_AM4_Update          g_stPPIHook.pfTCPIP_PPI_AM4_Update      

#define g_pfTCPIP_PPI_MPLSFW_Output  g_stPPIHook.pfTCPIP_PPI_MPLSFW_Output

#define g_pfTCPIP_PPI_IP6_Output   g_stPPIHook.pfTCPIP_PPI_IP6_Output 

#define g_pfTCPIP_PPI_PPPOE_Update g_stPPIHook.pfTCPIP_PPI_PPPOE_Update

/* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
#define g_pfTCPIP_PPI_TRUNK_LACP_Update g_stPPIHook.pfTCPIP_PPI_TRUNK_LACP_Update
    /* Chandra */
#define g_pfTCPIP_PPI_POLICYRT_Update g_stPPIHook.pfTCPIP_PPI_POLICYRT_Update

/*Added by apurba for VRF6*/
#define     g_pfTCPIP_PPI_VRF6_Update    g_stPPIHook.pfTCPIP_PPI_VRF6_Update

/*******************************全局变量声明***************************************/
extern TCPIP_PPI_HOOK_S   g_stPPIHook; /*PPI接口钩子函数集*/

/* Add by heyijun 00218462 for DTS2012092900232 维测需求开发, 2012-9 */
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl       *g_pstPp4Am4Vtbl;
/* End of Add by heyijun 00218462 for DTS2012092900232 维测需求开发, 2012-9 */


/*******************************函数声明***************************************/
VOID TCPIP_PPI_LogRt6Msg(ULONG ulRet, ULONG ulOprType, PPI_RTMSG6_S *pstRtEntry);
VOID TCPIP_PPI_LogRtMsg(ULONG ulRet, ULONG ulOprType, PPI_RTMSG4_S *pstRtEntry);
VOID TCPIP_PPI_LogArpMsg(ULONG ulRet, ULONG ulOprType, PPI_ARP_S *pstArpMsg);
VOID TCPIP_PPI_LogIfMsg(ULONG ulRet, IFNET_S *pstIf, ULONG ulOprType, VOID *pData);
VOID TCPIP_PPI_LogPppMsg(ULONG ulRet, IFNET_S *pstIf, ULONG ulOprType, VOID *pData);
VOID TCPIP_PPI_LogMapMsg(ULONG ulRet, ULONG ulOprType, PPI_MAP_S  *pstMapInfo);

VOID TCPIP_PPI_LogOutpkt();
VOID TCPIP_PPI_LogIp6Outpkt();
/*Add by z62474 for 2007-09-10 ,增加OSI对NP的支持*/
VOID TCPIP_PPI_OSI_LogOutpkt();


/* add by l57500,06-12-06,support for trunk np */
VOID TRUNKPORT_PPI_Download_State(IFNET_S *pstPortIf, ULONG ulCmd, VOID* pstTrunkIf);

VOID TCPIP_PPI_LogIGMPMsg(ULONG ulRet, ULONG ulOprType, PPI_IGMPConfigInfo_S *pstIGMPInfo);
/* 3ah ppi log */
VOID TCPIP_PPI_3AH_LogMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOperType, VOID *pOam3ahMsg);

VOID TCPIP_PPI_1AG_LogMsg(ULONG ulRet,ULONG ulIfIndex,ULONG ulOperType,VOID *pEoam1agMsg);

VOID TCPIP_PPI_L2IFVLAN_LogMsg(ULONG ulRet, USHORT usViD, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_L2IFPORT_LogMsg(ULONG ulRet, ULONG ulIndex, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_L2IFMAC_LogMsg(ULONG ulRet, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_L2IFQINQ_LogMsg(ULONG ulRet, ULONG ulIndex, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_VRRP_InfoMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOprType, VOID *pData);
VOID TCPIP_PPI_LogCtrlMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOprType, VOID *pstMMacInfo);
ULONG PPI_MultiMac_Update(ULONG ulIfIndex, ULONG ulOptType, UCHAR *pszMacAddr, UCHAR *pszMacMask);

extern NPDOWNLOAD_FAILED_PROCESS g_pfNpDownLoadFailProcHook;
ULONG PpiRepeate_Init(VOID);
ULONG PpiRepeate_InQueue(ULONG ulModuleId, ULONG ulPriority, ULONG aulArgs[]);
VOID PpiRepeate_Timer(VOID* pArg);
VOID PpiRepeate_WarningOutput(PPI_REPEATE_S *pNode);
/*******************************************************************************
*    Func Name: TCPIP_PPI_LogVRFMsg
* Date Created: 2009-02-04
*       Author: Wangchengyang
*  Description: VRF PPI的日志记录函数
*        Input: ULONG ulRet:PPI下发返回值
*               pstVrfPpiInfo:下发信息(详见VRF_PPI_S)
*               ulOprType:见enum tagVRF_PPI_MSGTYPE_E
*
*       Output: 
*       Return: 无           
*
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-02-04      wangchengyang    Create
*******************************************************************************/
extern VOID TCPIP_PPI_LogVRFMsg(ULONG ulRet, VRF_PPI_S *pstVrfPpiInfo, ULONG ulOprType);

extern VOID TCPIP_PPI_LogVRF6Msg(ULONG ulRet, VRF6_PPI_S *pstVrfPpiInfo, ULONG ulOprType);


extern VOID TCPIP_PPI_LogPolicyRtMsg(ULONG ulRet, PPI_POLICYRT_S *pstPolicyRtPpiInfo, ULONG ulOprType);

extern VOID TCPIP_PPI_TRUNKBIND_LogMsg(ULONG ulRet, ULONG ulOperType, PPI_TRUNK_BIND_S *pstTrunkBind);
/*Added by z00208058/w00207740, TRUNK LACP下移需求开发, 2012/5/2 */
extern VOID TCPIP_PPI_TRUNKUpdate_LogMsg(ULONG ulRet, ULONG ulOperType, PPI_TRUNK_LACP_S *pstTrunkPPI);
extern VOID TCPIP_PPI_AM4_LogMsg(ULONG ulRet, ULONG ulOperType, PPI_IPADDR_INFO_S *pstIpAddrInfo);

extern VOID TCPIP_PPI_VPN_LogOutputPkt();
extern VOID TCPIP_PPI_VPN_LogInputPkt();
extern VOID TCPIP_PPI_VPN_LogErrorPkt();
/* Add by heyijun 00218462 for DTS2012092900232 维测需求开发, 2012-9 */
extern VOID TCPIP_PPI_LogIFOutPkt(ULONG ulOutIndexIf, BOOL_T bIsPpiProcessed, BOOL_T bIsBcast, BOOL_T bIsMcast);

/* End of Add by heyijun 00218462 for DTS2012092900232 维测需求开发, 2012-9 */

/*Added by w00207740, NSR TRUNK,下发日志记录, 2013/7/2 */
extern VOID TCPIP_PPI_NsrTrunk_LogMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOperType, UCHAR *pucData);

#ifdef  __cplusplus
}
#endif

#endif

