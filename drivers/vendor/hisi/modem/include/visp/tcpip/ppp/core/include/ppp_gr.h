/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppp_gr.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PPP GR
*  Date Created: 2008-08-15
*        Author: zhangchunyu
*   Description: PPP模块保活恢复模块头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-15  zhangchunyu        Create

*******************************************************************************/

#ifndef _PPP_GR_H_
#define _PPP_GR_H_

#ifdef  __cplusplus
extern "C"{
#endif
#include "tcpip/public/tcpip_gr.h"

enum enumPppGRERR
{
    GR_SUCCESS,                                            /* 0 恢复成功 */ 
    GR_FAIL,                                               /* 1 失败 */
    GR_ERR_NOT_PPP_COM,                                    /* 2 没有注册PPP组件 */
    GR_ERR_NULL_POINT,                                     /* 3 指针为空 */
    GR_ERR_NORMOL_REBOOT,                                  /* 4 正常启动方式，或以完成平滑处理 */
    GR_ERR_WRITE_QUE,                                      /* 5 写队列失败 */
    GR_ERR_OPEN_IFENTRY,                                   /* 6 打开IFNET 链表失败 */
    GR_ERR_GETNP_LCP,                                      /* 7 从NP获取LCP信息失败 */
    GR_ERR_GETNP_IPCP,                                     /* 8 从NP获取IPCP信息失败 */
    GR_ERR_MEM_MALLOC,                                     /* 9 分配内存失败 */
    GR_ERR_MP_CONF_NP,                                     /* 10 配置和NP得到的信息不一致 */
    GR_ERR_CHECK_NP_LCP,                                   /* 11 从NP获取LCP信息错误 */
    GR_ERR_CHECK_NP_IPCP,                                  /* 12 从NP获取IPCP信息错误 */
    GR_ERR_NULL_CB,                                        /* 13 控制块为空, 内部控制块,为了PC-Lint告警 */
    GR_ERR_LCP_NOT_OPEN,                                   /* 14 IPCP恢复, LCP不是OPEN状态 */
    GR_ERR_LCP_NULL_CB,                                    /* 15 IPCP恢复, LCP控制块为NULL */
    GR_ERR_IPCP_MP_LOW,                                    /* 16 MP恢复IPCP恢复前为OPEN,恢复后下限阈值不能满足 */
    GR_ERR_IP_ALLF,                                        /* 17 接口地址为全1 */
    GR_ERR_CHECK_LCP_MRU,                                  /* 18 MRU不合法 */
    GR_ERR_CHECK_LCP_MRRU,                                 /* 19 MRRU不合法 */
    GR_ERR_CHECK_LCP_NEGMP,                                /* 20 一端协商MP,另一端不协商MP */
    GR_ERR_CHECK_GOTNP_NOMHF,                              /* 21 不识别本端MHF协商的code值 */
    GR_ERR_CHECK_GOTNP_MHF_LCLASS,                         /* 22 本端MHF协商的 Length class非法*/
    GR_ERR_CHECK_GOTNP_MHF_SCLASS,                         /* 23 本端MHF协商的 Short class非法*/
    GR_ERR_CHECK_HISNP_NOMHF,                              /* 24 不识别对端MHF协商的code值 */
    GR_ERR_CHECK_HISNP_MHF_LCLASS,                         /* 25 对端MHF协商的 Length class非法*/
    GR_ERR_CHECK_HISNP_MHF_SCLASS,                         /* 26 对端MHF协商的 Short class非法*/
    GR_ERR_CHECK_LCP_DISCRCLASS,                           /* 27 Discr class非法 */
    GR_ERR_CHECK_LCP_MHFSSNHF,                             /* 28 MHF和SSNHF冲突 */
    GR_ERR_CHECK_LCP_MAGICNUM,                             /* 29 本端和对端魔术字相同 */
    GR_ERR_CHECK_LCP_DISCRLEN,                             /* 30 Discr Len非法*/
    GR_ERR_CHECK_IPCP_NOT_ADDR,                            /* 31 主机地址和底层获取的地址不相同 */
    GR_ERR_CHECK_IPCP_ADDR,                                /* 32 本端和对端的协商到的彼此地址不一致 */
    GR_ERR_MP_ED_NULL,                                     /* 33 子接口恢复时, MP接口终端描述符是0*/
    GR_ERR_ED_MISMATCH,                                    /* 34 PPP接口LCP恢复Got Opetion终端描述符和MP接口的终端描述符不一致*/
    GR_ERR_NOT_REGISTERPPI,                                /* 35 没有注册PPP NP下发获取钩子函数 */
    GR_ERR_GETNP_OSICP,                                    /* 36 从NP获取OSICP信息失败 */
    GR_ERR_OSICP_DISABLE,                                  /* 37 接口已去使能OSICP */
    GR_ERR_CHECK_NP_OSICP,                                 /* 38 从NP获取OSICP信息错误 */

    GR_ERR_MAX,                                            /*  恢复返回最大值 */    
};

/* 启动模式 */
#define PPP_NORMAL_REBOOT        MODE_NORMAL
#define PPP_KEEPALIVE_REBOOT     MODE_KEEPALIVE

#define PPP_GET_PPI_LCPOPTION    1
#define PPP_GET_PPI_IPCPOPTION   2
#define PPP_GET_PPI_OSICPOPTION  3

#define PPP_GR_SMOOTH_LCPOPTION     1
#define PPP_GR_SMOOTH_IPCPOPTION    2
#define PPP_GR_SMOOTH_OSICPOPTION   3

#define PPP_GR_DEBUG_ON    1
#define PPP_GR_DEBUG_OFF   0

#define PPP_RESTORE_SUCCESS 0
#define PPP_RESTORE_FAIL    1


/* PTN产品没有设置前缀省略,所以暂不恢复前缀省略 */
#define PPP_RESTORE_LCPOPTION_FROM_PPI(pstLcpOption, pstPpiInfo)\
{\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_NUM >= MC_PREFIXE_MAX_NUM);\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_LEN >= MC_PREFIXE_MAX_STR);\
    (pstLcpOption)->neg_discr = (pstPpiInfo)->neg_discr;\
    (pstLcpOption)->neg_magicnumber = (pstPpiInfo)->neg_magicnumber;\
    (pstLcpOption)->neg_prefixE = (pstPpiInfo)->neg_prefix;\
    (pstLcpOption)->neg_mhf = (pstPpiInfo)->neg_mhf;\
    (pstLcpOption)->neg_ssnhf = (pstPpiInfo)->neg_ssnhf;\
    (pstLcpOption)->neg_mrru = (pstPpiInfo)->neg_mrru;\
    (pstLcpOption)->neg_mru = (pstPpiInfo)->neg_mru;\
    (pstLcpOption)->neg_asyncmap = (pstPpiInfo)->neg_asyncmap;\
    (pstLcpOption)->neg_accompression = (pstPpiInfo)->neg_accompression;\
    (pstLcpOption)->neg_pcompression = (pstPpiInfo)->neg_pcompression;\
    (pstLcpOption)->mru = (pstPpiInfo)->usMru;\
    (pstLcpOption)->mrru = (pstPpiInfo)->usMrru;\
    (pstLcpOption)->asyncmap = (pstPpiInfo)->ulAsyncmap;\
    (pstLcpOption)->ucMhfCode = (pstPpiInfo)->ucCode;\
    (pstLcpOption)->ucMhfClass = (pstPpiInfo)->ucClass;\
    if(pstPpiInfo->neg_mrru)\
    {\
        (pstLcpOption)->discr_len = (pstPpiInfo)->ucDiscr_len;\
        (pstLcpOption)->discr_class = (pstPpiInfo)->ucDiscr_class;\
        (VOID)TCPIP_Mem_Copy((pstLcpOption)->discr_addr, PPP_MP_DISCR_MAX_LENGTH, \
               (pstPpiInfo)->discr_addr, PPP_MP_DISCR_MAX_LENGTH);\
    }\
    (pstLcpOption)->magicnumber = (pstPpiInfo)->ulMagicnumber;\
}

/* 目前没有用到压缩，所以不恢复压缩 */
#define PPP_RESTORE_IPCPOPTION_FROM_PPI(pstIpcpOption,pstPpiInfo)\
{\
     (pstIpcpOption)->neg_vj  = (pstPpiInfo)->neg_vj;\
     (pstIpcpOption)->neg_iphc = (pstPpiInfo)->neg_iphc;\
     (pstIpcpOption)->ouraddr = VOS_NTOHL((pstPpiInfo)->ulOurAddr);\
     (pstIpcpOption)->hisaddr = VOS_NTOHL((pstPpiInfo)->ulHisAddr);\
}

#define PPP_GET_NPINFO_FROM_PPI(pstIf, pstOption, ulPpiMsgType, optionType, ulPpiRet)\
{\
    (VOID)TCPIP_Mem_Set(pstOption, 0, sizeof(optionType));\
    ulPpiRet = g_pfTCPIP_PPI_PPP_Update(pstIf->if_ulIfIndex, ulPpiMsgType, pstOption);\
    TCPIP_PPI_LogPppMsg(ulPpiRet, pstIf, ulPpiMsgType, pstOption);\
}

#define PPP_RESTORE_OSICPOPTION_FROM_PPI(pstOsicpOption,pstPpiInfo)\
{\
     (pstOsicpOption)->neg_Align_NPDU  = (pstPpiInfo)->neg_Align_NPDU;\
     (pstOsicpOption)->ucAlign_NPDU = (pstPpiInfo)->ucAlign_NPDU;\
}

extern ULONG g_ulPPPRebootMode; 

VOID PPP_GR_DealMsg(UINTPTR aulMsg[4]);
ULONG PPP_GR_Smooth(VOID);
ULONG PPP_GR_Restore(VOID);

ULONG PPP_GR_RestoreByCase(IFNET_S *pstIf, PPPINFO_S *pstPppInfo, ULONG ulCaseType);
ULONG PPP_GR_SmoothByCase(IFNET_S *pstIf, ULONG ulCaseType);
ULONG PPP_LCPSmooth(IFNET_S *pstIfnet);
ULONG PPP_IPCPSmooth(IFNET_S *pstIfnet);
struct tagNpPppOsicpOption;
ULONG PPP_OSICPRestore(IFNET_S *pstIfnet, struct tagNpPppOsicpOption *pstNPGotOsicpOption,
    struct tagNpPppOsicpOption *pstNPHisOsicpOption);
ULONG PPP_OSICPSmooth(IFNET_S *pstIfnet);
ULONG PPP_LCPRestore(IFNET_S *pstIfnet, 
                     struct tagNpPppLcpOption *pstNPGotLcpInfo, 
                     struct tagNpPppLcpOption *pstNPHisLcpInfo);
ULONG PPP_IPCPRestore(IFNET_S *pstIfnet, 
                      struct tagNpPppIpcpOption *pstNPGotIpcpOption,
                      struct tagNpPppIpcpOption *pstNPHisIpcpOption);
ULONG PPP_CBRestore(PPPINFO_S *pstPPPInfo, ULONG ulPhyStauts);
ULONG PPP_CheckPpiPara(IFNET_S * pstIfNet, VOID * pstPpiGotInfo, VOID * pstPpiHisInfo,ULONG ulPppType);
ULONG PPP_GetNPInfo(IFNET_S *pstIf, ULONG ulCmd, VOID *pstPPIGotOption, VOID *pstPPIHisOption);
ULONG PPP_GR_GetMPDisc(IFNET_S *pstIfnet, UCHAR *pucDiscr_addr);
ULONG GR_SetDebug(ULONG ulDebugSwitch);
ULONG GR_GetDebug(ULONG *pulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_PPP_GR_SetDebug
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: 设置PPP GR调试开关
*        Input: ULONG ulDebugSwitch: 1: 打开 0: 关闭 其他: 无效
*       Output: 
*       Return: GR_SUCCESS: 成功, GR_FAIL: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_PPP_GR_SetDebug(ULONG ulDebugSwitch);


/*******************************************************************************
*    Func Name: TCPIP_PPP_GR_GetDebug
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: 获取PPP GR调试开关
*        Input: ULONG *pulDebugSwitch: 输出参数, 调试开关值
*       Output: pulDebugSwitch调试开关
*       Return: GR_SUCCESS: 成功, GR_FAIL: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_PPP_GR_GetDebug(ULONG *pulDebugSwitch);



#ifdef  __cplusplus
}
#endif
#endif


