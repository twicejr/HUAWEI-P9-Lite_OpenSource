/*-------------------------------------------------------------------------------
*
*                              ptpv2_bmc.c
*
*  Project Code:
*   Module Name: PTPV2 bmc
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_timer.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/etharp/include/etharp_api.h"

/*D0,Erbest,Ebest比较*/
#define DSA_COMPAR_TYPE_NO_NEED           0   
#define DSA_COMPAR_TYPE_DO_WITH_ERBEST    1
#define DSA_COMPAR_TYPE_DO_WITH_EBEST     2
#define DSA_COMPAR_TYPE_EBEST_WITH_ERBEST 3

/*
选源:
*/
/******************************************************************************
*Func Name   : PTP_Shell_CompareClockClass
*Description : 比较时钟等级
*Input       : pstPtpPort      时钟端口指针
               pstForeMasterA  需比较时钟质量的foreignmaster结构的指针
               pstForeMasterB  需比较时钟质量的foreignmaster结构的指针
*Output      : pstSelectMaster :优先级高的时钟源
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE 2012/2/14    NAME  z00208058  AR-IP-PTP.002
*
*******************************************************************************/
ULONG PTPV2_CompareClockClass(PTPV2_FOREIGN_MASTER_S* pstForeMasterA,
                              PTPV2_FOREIGN_MASTER_S* pstForeMasterB,
                              PTPV2_FOREIGN_MASTER_S** pstSelectMaster)
{
    UCHAR ucClockClassA = 0;
    UCHAR ucClockClassB = 0;
    /*   A B 都在优选组中， 直接比较两者大小
         A 在，B 不在，直接选A
         A 不在，B 在，直接选B
         A 和B 都不在，直接比较两者大小
         总结为三个分支。
    */
    ucClockClassA = pstForeMasterA->stGrandmasterClockQuality.ucClockClass;
    ucClockClassB = pstForeMasterB->stGrandmasterClockQuality.ucClockClass;

    /*配置了优选源*/
    if (PTPV2_YES == g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriClassFlag)
    {
        if (PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassA)
            && !PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassB))
        {
            *pstSelectMaster = pstForeMasterA;
            return TCPIP_PTP_OK;
        }
        else if (!PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassA)
                 && PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassB))
        {
            *pstSelectMaster = pstForeMasterB;
            return TCPIP_PTP_OK;
        }
        else if (PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassA)
                 && PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassB))
        {
            /*若两个Master的class都在优选源中，按照优选源的顺序先后进行选源*/
            if (ucClockClassA != ucClockClassB)
            {
                if(g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass0 == ucClockClassA)        
                {
                    *pstSelectMaster = pstForeMasterA;
                    return TCPIP_PTP_OK;
                }
                else if(g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass0 == ucClockClassB)
                {
                    *pstSelectMaster = pstForeMasterB;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass1 == ucClockClassA)
                {
                    *pstSelectMaster = pstForeMasterA;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass1 == ucClockClassB)
                {
                    *pstSelectMaster = pstForeMasterB;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass2 == ucClockClassA)
                {
                    *pstSelectMaster = pstForeMasterA;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass2 == ucClockClassB)
                {
                    *pstSelectMaster = pstForeMasterB;
                    return TCPIP_PTP_OK;
                }
            }
        }
    }

    /*pstForeMasterA时钟等级 < pstForeMasterB时钟等级*/
    if (ucClockClassA < ucClockClassB)
    {
        *pstSelectMaster = pstForeMasterA;
        return TCPIP_PTP_OK;
    }
    else if (ucClockClassA > ucClockClassB)
    {
        /*pstForeMasterA时钟等级 > pstForeMasterB时钟等级*/
        *pstSelectMaster = pstForeMasterB;
        return TCPIP_PTP_OK;
    }

    return TCPIP_PTP_ERR;/*class相同，无法选择，需要下一个选源参数*/
}

/******************************************************************************
*Func Name   : PTPV2_BMC_DSCA_Part1
*Description : 时钟质量比较函数
*Input       :
*              pstDSMaster  需比较时钟质量的foreignmaster/DataSet结构的指针
*              pstForeMasterB  需比较时钟质量的foreignmaster结构的指针
*              bFlags          true则两个Master比较,false则master和 DS比较
*Output      : ppstSelectMaster: 优先级高的备用时钟源
*              BOOL_T* pbBetter: 选源结果是否为源更优
*              BOOL_T* pbTopoBetter: 选源结果是否为拓扑更优
*Return      : 成功返回TCPIP_PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME               DESCRIPTION
*  选源规则修改为：
* 1、基本原则:优先级1 》class等级》精度 》稳定度 》优先级2 》CLK ID
* 2、当用户打开Clockclass识别功能时:
*     1)、当Clockclass为6、7、13、14时，VISP判断其为参考源可优选，
*        对于两条1588链路，Clockclass优选顺序为：6>13>7>14. 两条1588链路中
*     2)、如果只有一条ClockClass为非6、7、13、14，另外一条为6、7、
*        13、14，则VISP选择6、7、13、14的参考源。
*     3)、如果两条1588链路中，ClockClass都为非6、7、13、14，则VISP返回选源失败；
* 3、当用户没有打开Clockclass识别功能时，按照Class等级大小来比较，越小越优；
*
*******************************************************************************/
ULONG PTPV2_BMC_DSCA_Part1(ULONG ulCompareType, 
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterA,
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterB,
                                PTPV2_FOREIGN_MASTER_S** ppstSelectMaster,
                                BOOL_T* pbBetter, BOOL_T* pbTopoBetter)
{
    LONG lRetResult = -1;
    ULONG ulRet = TCPIP_PTP_OK;

    if (NULL == pstForeMasterA || NULL == pstForeMasterB || NULL == ppstSelectMaster)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;    
    }
    
    /*Step0:比较时钟ID GM Id 是否相同,则执行算法的第二部分*/
    /*CLOCK ID比较*/
    (VOID)VOS_Mem_Cmp((VOID*)pstForeMasterA->szGrandMasterId,
                      (VOID*)pstForeMasterB->szGrandMasterId,
                      TCPIP_PTP_CLOCK_ID_LEN, &lRetResult);
    if (0 == lRetResult)
    {
        ulRet = PTPV2_BMC_DSCA_Part2(ulCompareType, pstForeMasterA, pstForeMasterB, ppstSelectMaster, pbBetter, pbTopoBetter);
        if (TCPIP_PTP_OK != ulRet)/*组网配置错误，则选择第一个*/
        {
            *ppstSelectMaster = pstForeMasterA;
            goto EXIT_LABEL;
        }
        return ulRet;        
    }
    
    /*Step1:比较优先级1*/
    /*pstForeMasterA时钟可接收master列表中的优先级 1<
     pstForeMasterB时钟可接收master列表中的优先级1*/
    if (pstForeMasterA->ucGrandmasterPriority1
        < pstForeMasterB->ucGrandmasterPriority1)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->ucGrandmasterPriority1
             > pstForeMasterB->ucGrandmasterPriority1)
    {
        /*pstForeMasterA时钟可接收master列表中的优先级 >
         pstForeMasterB时钟可接收master列表中的优先级*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step2:比较时钟等级*/
    /*检查MasterA和MasterB是否为优选源等级*/
    lRetResult = PTPV2_CompareClockClass(pstForeMasterA, pstForeMasterB, ppstSelectMaster);
    if (TCPIP_PTP_OK == lRetResult)
    {
        goto EXIT_LABEL;
    }

    /*Step3:比较时钟精度*/
    /*pstForeMasterA时钟精度 < pstForeMasterB时钟精度*/
    if (pstForeMasterA->stGrandmasterClockQuality.ucClockAccuracy
        < pstForeMasterB->stGrandmasterClockQuality.ucClockAccuracy)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->stGrandmasterClockQuality.ucClockAccuracy
             > pstForeMasterB->stGrandmasterClockQuality.ucClockAccuracy)
    {
        /*pstForeMasterA时钟精度  > pstForeMasterB时钟精度*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step4:比较时钟稳定度*/
    /*pstForeMasterA时钟稳定性 < pstForeMasterB时钟稳定性*/
    if (pstForeMasterA->stGrandmasterClockQuality.usOffsetScaledLogVariance
        < pstForeMasterB->stGrandmasterClockQuality.usOffsetScaledLogVariance)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->stGrandmasterClockQuality.usOffsetScaledLogVariance
             > pstForeMasterB->stGrandmasterClockQuality.usOffsetScaledLogVariance)
    {
        /*pstForeMasterA时钟稳定性 > pstForeMasterB时钟稳定性*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step5:比较时钟优先级2*/
    /*pstForeMasterA时钟在可接收master列表中的优先级2<
     pstForeMasterB时钟可接收master列表中的优先级2*/
    if (pstForeMasterA->ucGrandmasterPriority2
        < pstForeMasterB->ucGrandmasterPriority2)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->ucGrandmasterPriority2
             > pstForeMasterB->ucGrandmasterPriority2)
    {
        /*pstForeMasterA时钟可接收master列表中的优先级 >
         pstForeMasterB时钟可接收master列表中的优先级*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step6:比较时钟ID*/
    /*CLOCK ID比较*/
    (VOID)VOS_Mem_Cmp((VOID*)pstForeMasterA->szGrandMasterId,
                      (VOID*)pstForeMasterB->szGrandMasterId,
                      TCPIP_PTP_CLOCK_ID_LEN, &lRetResult);
    if (lRetResult > 0)
    {
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }
    else if (lRetResult < 0)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }   

    /*注:对于clock id相同的情形下的比较，不可能发生,announce报文接收做了限制*/
    *ppstSelectMaster = pstForeMasterA;

EXIT_LABEL:
    *pbBetter = BOOL_TRUE;
    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_1588_BMC
* Date Created: 2014-11-08
*       Author: w00217009
*  Description: 选择最佳源,包括两种情况 AR-IP-PTP.002
*               有两种场景:1.选择全系统的最佳源Ebest
*                          2.选择一个具体端口的最佳源Erbest
*        Input: DLL_S *pstDll : foreignmaster链表:
*               BOOL_T bEbest : 本次执行是否为选最佳源Ebest
*                               因Ebest和Erbest操作的链表位置不同
*       Output: PTPV2_FOREIGN_MASTER_S** pstSelectMaster : 返回最佳源
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
ULONG PTPV2_1588_BMC(DLL_S *pstDll, PTPV2_FOREIGN_MASTER_S** pstSelectMaster, BOOL_T bEbest)
{

    PTPV2_FOREIGN_MASTER_S* pstIter = NULL;
    PTPV2_FOREIGN_MASTER_S* pstIterForeMaster = NULL;
    PTPV2_FOREIGN_MASTER_S* pstBmcParent = NULL;
    PTPV2_FOREIGN_MASTER_S* pstTemp = NULL;

    ULONG ulRet = TCPIP_PTP_OK;
    BOOL_T bBetter = BOOL_FALSE;
    BOOL_T bTopoBetter = BOOL_FALSE;

    if (NULL == pstSelectMaster || NULL == pstDll)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    DLL_Scan(pstDll, pstIter, PTPV2_FOREIGN_MASTER_S *)
    {
        /*指针重新指到结构体起始位置,Ebest对应global链表,Erbest对应于port链表*/
        pstIterForeMaster = bEbest ? (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter))
                                    : (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stPortDllNode - (CHAR *)pstIter));

        /*Add by heyijun 00218462 for AR-IP-PTP.001 支持PTSF配置参与选源, 2014-11 
        * 收到的ann报文少于2的foremaster,不参与选源
        */
        if ((NULL == pstIterForeMaster) || (PTPV2_IS_FOREMASTER_GOT_PTSF(pstIterForeMaster)) 
             || (pstIterForeMaster->ulRecvAnnCount < 2))
        {
            continue;
        }

        if (NULL == pstBmcParent)
        {

            pstBmcParent = pstIterForeMaster;
            continue;
        }

        pstTemp = pstBmcParent;
        
        (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_NO_NEED, pstTemp, pstIterForeMaster, &pstBmcParent, &bBetter, &bTopoBetter);
       
    }

    *pstSelectMaster = pstBmcParent;
    return ulRet;
}

ULONG PTPV2_AddForeignMaster(PTPV2_PORT_S* pstPtpPort, TCPIP_PTP_ADDRINFO_S* pstAddrInfo,
                             PTPV2_FOREIGN_MASTER_S** ppstForeMaster)
{
    PTPV2_FOREIGN_MASTER_S* pstAddForeign = NULL;
    /* Modified by wuling201943, 申请内存长度不对, 2014/11/11   问题单号:DTS2014111107372 */
    ULONG ulStructLen = sizeof(PTPV2_FOREIGN_MASTER_S);
    /*End of Modified by wuling201943, 2014/11/11   问题单号:DTS2014111107372 */
    ULONG ulRet = TCPIP_PTP_ERR;

    if (NULL == pstAddrInfo || NULL == ppstForeMaster)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    pstAddForeign = (PTPV2_FOREIGN_MASTER_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_FOREIGN_MASTER, ulStructLen);
    if (NULL == pstAddForeign)
    {
        ulRet = TCPIP_PTP_ERR_MALLOC_FAIL;
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FA, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: PTPV2_AddForeignMaster malloc pstAddForeign failed.\r\n",
                         0, 0, 0, 0);
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Set((CHAR*)pstAddForeign, 0, ulStructLen);

    /*fill */
    (VOID)TCPIP_Mem_Copy((VOID*) & (pstAddForeign->stForeignMasterPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S),
                                            (VOID*) & (pstAddrInfo->stSrcPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S));

    DLL_Add(&g_GlobalForeignMasterList, (DLL_NODE_S*)&(pstAddForeign->stGlobalDllNode));
    DLL_Add(&(pstPtpPort->dllForeignMasterHead), (DLL_NODE_S*)&(pstAddForeign->stPortDllNode));
    pstAddForeign->pstPortInfo = pstPtpPort;
    pstAddForeign->ulRcvIfIndex = pstAddrInfo->ulIfIndex;/*填写入接口索引*/
    pstAddForeign->ulRecvAnnCount++; /*收到第一个ann报文时生成foremaster*/

    *ppstForeMaster = pstAddForeign;
    ulRet = TCPIP_PTP_OK;

EXIT_LABEL:

    return ulRet;
}

ULONG PTPV2_GetForeignMasterByAddr(TCPIP_PTP_PORT_ADDR_S* pstAddrInfo,
                                   PTPV2_FOREIGN_MASTER_S** ppstForeMaster)
{
    PTPV2_FOREIGN_MASTER_S* pstIter = NULL;
    PTPV2_FOREIGN_MASTER_S* pstIterForeMaster = NULL;
    LONG lCmp = -1L;
    ULONG ulRet = TCPIP_PTP_ERR;

    if (NULL == pstAddrInfo || NULL == ppstForeMaster)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    DLL_Scan(&g_GlobalForeignMasterList, pstIter, PTPV2_FOREIGN_MASTER_S *)
    {
        /*指针重新指到结构体起始位置*/
        pstIterForeMaster = (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter));

        /*原判断存在问题*/
        if ((TCPIP_PTP_PROTOCAL_IEEE_802 == pstAddrInfo->usNetworkProtocol) && 
                (PTPV2_MACADDRLEN == pstAddrInfo->usAddressLength))
        {
            (VOID)VOS_Mem_Cmp((VOID *)pstAddrInfo->unAddr.ucMacAddr, 
                              (VOID *)pstIterForeMaster->stForeignMasterPortAddr.unAddr.ucMacAddr,
                               PTPV2_MACADDRLEN, &lCmp);
            if (0 == lCmp)
            {
                *ppstForeMaster = pstIterForeMaster;
                ulRet = TCPIP_PTP_OK;
                break;
            }
        }
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_DelForeignMaster
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:  删除备用master
*        Input: PTPV2_FOREIGN_MASTER_S* pstDelForeMaster:
*       Output:
*       Return:
*      Caution:
*              三次时机:1、 announce接收超时，应当删除备用master
*                       2、 删除端口
*                       3、 卸载PTP模块
*             删除备用master: a. 删除定时器 b. 从全局链表中删除 c.从端口链表中删除
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_DelForeignMaster(PTPV2_FOREIGN_MASTER_S* pstDelForeMaster)
{
    PTPV2_PORT_S* pstPortInfo = NULL;

    VOS_DBGASSERT(NULL != pstDelForeMaster);

    pstPortInfo = pstDelForeMaster->pstPortInfo;

    VOS_DBGASSERT(NULL != pstPortInfo);

    /*Foremaster Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
    {
        TCPIP_InfoOutput("\r\ndel foremaster:");

        PTPV2_ForeMasterPrint(pstDelForeMaster);
    }

    if (g_pstBmcEbest == pstDelForeMaster)/*当前删除的==选中的时钟源*/
    {
        (VOID)PTPV2_BMC_PPI_SlaveRole(pstDelForeMaster, TCPIP_PTP_PPI_DEL, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);
        g_pstBmcEbest = NULL;        
    }

    /*删除备用时钟源: 接收定时器 &  从全局链表删除 & 从端口链表中删除*/
    (VOID)PTPV2_DeleteLogicTimer(pstDelForeMaster->ulAnnRcvTimerId);
    DLL_Delete(&g_GlobalForeignMasterList, (DLL_NODE_S*)&pstDelForeMaster->stGlobalDllNode);
    DLL_Delete(&(pstPortInfo->dllForeignMasterHead), (DLL_NODE_S*)&pstDelForeMaster->stPortDllNode);
    (VOID)TCPIP_Free(pstDelForeMaster);
    return TCPIP_PTP_OK;
}

ULONG PTPV2_DelForeignMaster_ByAddrr(TCPIP_PTP_PORT_ADDR_S* pstAddrInfo)
{
    PTPV2_FOREIGN_MASTER_S* pstIter = NULL;
    PTPV2_FOREIGN_MASTER_S* pstIterForeMaster = NULL;
    LONG lCmp = -1;
    ULONG ulRet = TCPIP_PTP_ERR;
    PTPV2_PORT_S* pstPortInfo = NULL;

    DLL_Scan(&g_GlobalForeignMasterList, pstIter, PTPV2_FOREIGN_MASTER_S *)
    {
        /*指针重新指到结构体起始位置*/
        pstIterForeMaster = (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter));

        (VOID)VOS_Mem_Cmp(pstAddrInfo, &(pstIterForeMaster->stForeignMasterPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S), &lCmp);
        if (0 == lCmp)
        {
            pstPortInfo = pstIterForeMaster->pstPortInfo;

            /*Foremaster Debug信息*/
            if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
            {
                TCPIP_InfoOutput("\r\ndel foremaster:");

                PTPV2_ForeMasterPrint(pstIterForeMaster);
            }

            DLL_Delete(&g_GlobalForeignMasterList, (DLL_NODE_S*)&pstIterForeMaster->stGlobalDllNode);
            DLL_Delete(&(pstPortInfo->dllForeignMasterHead), (DLL_NODE_S*)&pstIterForeMaster->stPortDllNode);
            (VOID)TCPIP_Free(pstIterForeMaster);

            ulRet = TCPIP_PTP_OK;
            break;
        }
    }

    return ulRet;
}

ULONG PTPV2_Update_ForeignMasterPara(PTPV2_PORT_S* pstPtpPort, PTPV2_FOREIGN_MASTER_S* pstForeMaster,
                                     PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_ADDRINFO_S* pstAddrInfo)
{
    pstForeMaster->cLogMAnnInterval = pstAnnMsg->stMsgHeader.cLogMessageInterval;
    /*ANN接收超时计数清零*/
    pstForeMaster->ulAnnRcvTimerCount = 0;
    VOS_CopyVar(pstForeMaster->stGrandmasterClockQuality, pstAnnMsg->stGrandmasterClockQuality);
    pstForeMaster->stGrandmasterClockQuality.usOffsetScaledLogVariance = 
        VOS_NTOHS(pstAnnMsg->stGrandmasterClockQuality.usOffsetScaledLogVariance);
    pstForeMaster->ucGrandmasterPriority1 = pstAnnMsg->ucGrandmasterPriority1;
    pstForeMaster->ucGrandmasterPriority2 = pstAnnMsg->ucGrandmasterPriority2;
    pstForeMaster->ucFlagField[0] = pstAnnMsg->stMsgHeader.ucflagField[0];
    pstForeMaster->ucFlagField[1] = pstAnnMsg->stMsgHeader.ucflagField[1];
    pstForeMaster->ucTimeSource = pstAnnMsg->ucTimeSource;
    pstForeMaster->usStepsRemoved = VOS_NTOHS(pstAnnMsg->usStepsRemoved);

    (VOID)TCPIP_Mem_Copy((VOID*)(pstForeMaster->szGrandMasterId), TCPIP_PTP_CLOCK_ID_LEN,(VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN);
    (VOID)TCPIP_Mem_Copy((VOID*)(&(pstForeMaster->stForeignMasterPortAddr)), sizeof(TCPIP_PTP_PORT_ADDR_S),(VOID*)(&(pstAddrInfo->stSrcPortAddr)),
                       sizeof(TCPIP_PTP_PORT_ADDR_S));
    (VOID)TCPIP_Mem_Copy((VOID*)(&(pstForeMaster->szForeignMasterPortId)),sizeof(TCPIP_PTP_PORT_ID_S), (VOID*)(&(pstAnnMsg->stMsgHeader.stSourcePortIdentity)),
                       sizeof(TCPIP_PTP_PORT_ID_S));
    pstForeMaster->szForeignMasterPortId.usPortNumber = VOS_NTOHS(pstAnnMsg->stMsgHeader.stSourcePortIdentity.usPortNumber);

    pstForeMaster->sCurrentUtcOffset = VOS_NTOHS(pstAnnMsg->sCurrentUtcOffset);

    /*更新announce报文的序列号*/
    pstForeMaster->usRcvAnnSequenceId = VOS_NTOHS(pstAnnMsg->stMsgHeader.usSequenceId);

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_BMCPreProcess
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:  BMC 选源的预处理
*        Input: PTPV2_PORT_S* pstPortInfo:
*               PTPV2_ANNOUNCE_MSG_S* pstAnnMsg:
*               TCPIP_PTP_ADDRINFO_S* pstAddrInfo:
*       Output:
*       Return:
*      Caution:
1、查询foregin master是否存在，存在则更新参数(不允许一个master从多个物理口接收
   port id如果变化则丢弃报文，直到超时删除foreign matser
2、不存在,则创建一个新的foreign master
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_BMCPreProcess(PTPV2_PORT_S* pstPortInfo, PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_ADDRINFO_S* pstAddrInfo)
{
    PTPV2_FOREIGN_MASTER_S* pstFind = NULL;
    PTPV2_FOREIGN_MASTER_S* pstAddForeign = NULL;
    ULONG ulRet = TCPIP_PTP_ERR;
    ULONG ulMaxCfgMasterNum = 0;
    ULONG ulCurrentMasterNum = 0;
    ULONG ulPeriod = 0;
    LONG lRet = 0;

    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo
        || NULL == pstAnnMsg || NULL == pstAddrInfo)
    {
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }

    /*根据port id 查找 foreign master是否已经存在*/
    ulRet = PTPV2_GetForeignMasterByPortId(&(pstAnnMsg->stMsgHeader), &pstFind);
    if (TCPIP_PTP_OK == ulRet)
    {
        /*不支持同一个matser的报文从本端多个物理口接收*/
        if (pstAddrInfo->ulIfIndex != pstFind->ulRcvIfIndex)
        {
            /*不支持这种组网*/
            /*报文统计*/
            g_stGlobalPtpV2PktStat.ulRcvErrorIfPackets ++;

            return TCPIP_PTP_ERR_INVALID_RCVINDEX;
        }

        /*clock id和port no变化，则丢弃报文，直到接收超时，删除备用源*/
        (VOID)VOS_Mem_Cmp((void*)(&(pstFind->szForeignMasterPortId)),
                          (void*)(pstAnnMsg->stMsgHeader.stSourcePortIdentity.szClockId), sizeof(TCPIP_PTP_CLOCK_ID_SZ), &lRet);
        if (0 != lRet)
        {
            return TCPIP_PTP_ERR_PORTID;
        }

        /*计数翻转则置为2(避免影响参与选源),否则增长1*/
        if (0xFFFFFFFF == pstFind->ulRecvAnnCount)
        {
            pstFind->ulRecvAnnCount = 2;
        }
        else
        {
            pstFind->ulRecvAnnCount++;
        }

        /*更新 master的地址、时钟参数*/
        (VOID)PTPV2_Update_ForeignMasterPara(pstPortInfo, pstFind, pstAnnMsg, pstAddrInfo);
        return ulRet;
    }

    (VOID)PTPV2_GetGlobalInfo(PTPV2_CMD_MASTER_NUM_LIMIT, &ulMaxCfgMasterNum);
    (VOID)PTPV2_GetGlobalInfo(PTPV2_CMD_CURRENT_MASTER_NUMS, &ulCurrentMasterNum);

    /*Modified by dutianyi for DTS2014060505599, 2014/6/7, ForeMaster数量等于最大值时就不能继续新增*/
    if (ulCurrentMasterNum >= ulMaxCfgMasterNum)/*达到最大配置值*/
    /*End of modifying by dutianyi for DTS2014060505599, 2014/6/7, ForeMaster数量等于最大值时就不能继续新增*/
    {
        /*后续考虑替换最差的那个时钟源*/
        return TCPIP_PTP_ERR_MASTER_UP_MAX;
    }

    /*没有找到则新增*/
    ulRet = PTPV2_AddForeignMaster(pstPortInfo, pstAddrInfo, &pstAddForeign);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    /*更新*/
    (VOID)PTPV2_Update_ForeignMasterPara(pstPortInfo, pstAddForeign, pstAnnMsg, pstAddrInfo);/*更新master参数*/

    /*创建接收定时器*/
    PTPV2_CAL_LOG_TO_MILL(pstAddForeign->cLogMAnnInterval, ulPeriod);
    if (0 == ulPeriod)
    {
        ulPeriod = 2000;
    }

    ulRet = PTPV2_CreateLogicTimer(ulPeriod, PTPV2_AnnRcvTimerOut, pstAddForeign, &pstAddForeign->ulAnnRcvTimerId);
    if (TCPIP_PTP_OK != ulRet)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FB, TCPIP_LOG_LEVEL_WARNING, LOG_TYPE_RUN,
                         "TCPIP PTP LOG:Create Accept Master Detect Timer Failed, Period:%u\r\n", ulPeriod, 0, 0, 0);
    }

    /*Foremaster Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
    {
        TCPIP_InfoOutput("\r\nadd foremaster:");

        PTPV2_ForeMasterPrint(pstAddForeign);
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_BMCProcess
* Date Created: 2014-03-24
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: PTPV2_FOREIGN_MASTER_S** pstSelectMaster:
*       Output:
*       Return:
*      Caution:
*       选源时机:1 收到announce报文  2 announce接收超时  3 删除端口
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-24   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_BMCProcess(PTPV2_FOREIGN_MASTER_S** ppstSelectMaster)
{
    ULONG ulBmcPolicy = 0;
    ULONG ulRet = TCPIP_PTP_ERR;
    ulRet = PTPV2_GetGlobalInfo(PTPV2_CMD_BMC_POLICY, &ulBmcPolicy);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    switch (ulBmcPolicy)
    {
        case TCPIP_PTP_BMC_POLICY_1588:
            (VOID)PTPV2_1588_BMC(&g_GlobalForeignMasterList, ppstSelectMaster, BOOL_TRUE);
            break;
        default:
            break;
    }

    return ulRet;

}

/*******************************************************************************
*    Func Name: PTPV2_BMCNotify
* Date Created: 2014-11-26
*       Author: w00217009
*  Description: 选源变更处理
*               1.第一次选中源,属于Ebest变更,需重新走决策流程,下发passive和slave
*               2.未选中源,属于Ebest变更,需重新走决策流程,下发passive和slave
*               3.切源,属于Ebest变更,需重新走决策流程,下发passive和slave
*               4.不切源,考虑update源即可
*        Input: PTPV2_FOREIGN_MASTER_S* pstSelectMaster: 当前选中的源
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
ULONG PTPV2_BMCNotify(PTPV2_FOREIGN_MASTER_S* pstSelectMaster)
{
    ULONG ulChangeField = TCPIP_PTP_PARA_CHANGE_FIELD_NONE;

    if (PTPV2_NO == PTPV2_HaveParent())
    {
        /*1.1 当前没有时钟源  & 本次也没有选中，则什么都不处理
          1.2 当前没有时钟源  & 本地选中了，则ADD
        */
        if (NULL != pstSelectMaster)
        {
            g_pstBmcEbest = pstSelectMaster;

            /* 将选中源的信息存储至ParentDs */
            PTPV2_UpdateParentDS(g_pstBmcEbest, NULL);

            /*Ebest变更,需要重新决策流程,决策端口的状态和角色,保证后面的下发信息正确*/
            (VOID)PTPV2_BMC_SDAProcess();

            /*通知所有passive端口的状态*/
            PTPV2_BMC_PPI_PassiveRoleForAll();

            /*通知slave端口的状态*/
            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_ADD, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);

            /*第一次选到时钟源，则设置标记，此标记仅设置一次*/
            if (PTPV2_NO == g_ucPtpGotTimeSourceFlag)
            {
                g_ucPtpGotTimeSourceFlag = PTPV2_YES;
            }

            /*告警解除操作*/
            PTPV2_WarningRemoveProc();
        }
    }
    else /*当前已经有时钟源*/
    {
        /*2.1 当前有时钟源 & 本次没有选中 ，则删除上一次的时钟源
          2.2 当前有时钟源 & 本次选中 ==  当前的,不处理
          2.3 当前有时钟源 & 本次选中 != 当前的，先DEL ，再ADD
        */
        if (NULL == pstSelectMaster)
        {
            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_DEL, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);
            g_pstBmcEbest = NULL;

            /*Ebest丢失,属于源变更,需重走BMC流程,否则角色和状态可能不准*/
            (VOID)PTPV2_BMC_SDAProcess();
            
            /*通知所有passive端口的状态*/
            PTPV2_BMC_PPI_PassiveRoleForAll();
            
            /*启动告警定时器*/
            (VOID)PTPV2_CreateWarningTimer();
        }
        else if (g_pstBmcEbest != pstSelectMaster)
        {
            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_DEL, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);

            g_pstBmcEbest = pstSelectMaster;

            /* 将选中源的信息存储至ParentDs */
            PTPV2_UpdateParentDS(g_pstBmcEbest, NULL);

            /*切源,需要重新决策流程,决策端口的状态和角色,保证后面的下发信息正确*/
            (VOID)PTPV2_BMC_SDAProcess();

             /*通知所有passive端口的状态*/
            PTPV2_BMC_PPI_PassiveRoleForAll();

            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_ADD, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);

            /*告警解除操作*/
            PTPV2_WarningRemoveProc();
        }
        /*新选中的源与原有的源相同*/
        else
        {
            /*将新选中源的信息更新至ParentDs */
            PTPV2_UpdateParentDS(g_pstBmcEbest, &ulChangeField);

            /*源信息变更,端口的状态和角色可能要变,需走决策流程*/
            (VOID)PTPV2_BMC_SDAProcess();

             /*通知所有passive端口的状态*/
            PTPV2_BMC_PPI_PassiveRoleForAll();

            /*源参数发生了变化*/
            if (TCPIP_PTP_PARA_CHANGE_FIELD_NONE != ulChangeField)
            {
                 (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_UPDATE, ulChangeField);
            }
        }
    }

    return TCPIP_PTP_OK;
}

/******************************************************************************
*Func Name   : PTPV2_ForeMasterPrint
*Description : ForeMaster信息打印接口
*Input       : PTPV2_FOREIGN_MASTER_S *pstForeMaster
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-05-14           dutianyi       Create
*  2014-11-07           heyijun        Add PtsfSync to display
*******************************************************************************/
VOID PTPV2_ForeMasterPrint(PTPV2_FOREIGN_MASTER_S *pstForeMaster)
{
    CHAR szBuf[LEN_512] = {0};      /* 缓冲区长度512个字节，存放报文信息 */
    INT32 i32Offset = 0;

    if (NULL == pstForeMaster)
    {
        return;
    }

    (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, 
                             P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                             "PortNo", pstForeMaster->pstPortInfo->pstSubPortInfo->usPortNo,
                             "ForeMasterPortNo", pstForeMaster->szForeignMasterPortId.usPortNumber,
                             "GrandmasterPriority1", pstForeMaster->ucGrandmasterPriority1,
                             "GrandmasterPriority2", pstForeMaster->ucGrandmasterPriority2));

    TCPIP_InfoOutput(szBuf);

    (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, 
                            P9("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x",
                            "Foreign Master Clock Id",
                            pstForeMaster->szForeignMasterPortId.szClockId[0],
                            pstForeMaster->szForeignMasterPortId.szClockId[1],
                            pstForeMaster->szForeignMasterPortId.szClockId[2],
                            pstForeMaster->szForeignMasterPortId.szClockId[3],
                            pstForeMaster->szForeignMasterPortId.szClockId[4],
                            pstForeMaster->szForeignMasterPortId.szClockId[5],
                            pstForeMaster->szForeignMasterPortId.szClockId[6],
                            pstForeMaster->szForeignMasterPortId.szClockId[7]));

    TCPIP_InfoOutput(szBuf);

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, 
                             P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %d",
                             "FlagField0", pstForeMaster->ucFlagField[0],
                             "FlagField1", pstForeMaster->ucFlagField[1],
                             "TimeSource", pstForeMaster->ucTimeSource,
                             "LogMAnnInterval", pstForeMaster->cLogMAnnInterval));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                             P8("\r\n %30s : %d \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                             "CurrentUtcOffset", pstForeMaster->sCurrentUtcOffset,
                             "ClockAccuracy", pstForeMaster->stGrandmasterClockQuality.ucClockAccuracy,
                             "ClockClass", pstForeMaster->stGrandmasterClockQuality.ucClockClass,
                             "OffsetScaledLogVariance", pstForeMaster->stGrandmasterClockQuality.usOffsetScaledLogVariance));

    TCPIP_InfoOutput(szBuf);

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, 
                            P9("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x",
                            "Grand Master Clock Id",
                            pstForeMaster->szGrandMasterId[0],
                            pstForeMaster->szGrandMasterId[1],
                            pstForeMaster->szGrandMasterId[2],
                            pstForeMaster->szGrandMasterId[3],
                            pstForeMaster->szGrandMasterId[4],
                            pstForeMaster->szGrandMasterId[5],
                            pstForeMaster->szGrandMasterId[6],
                            pstForeMaster->szGrandMasterId[7]));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                             P14("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n",
                             "RcvIfIndex", pstForeMaster->ulRcvIfIndex,
                             "AnnRcvTimerId", pstForeMaster->ulAnnRcvTimerId,
                             "AnnRcvTimerCount", pstForeMaster->ulAnnRcvTimerCount,
                             "RcvAnnSequenceId", pstForeMaster->usRcvAnnSequenceId,
                             "StepsRemoved", pstForeMaster->usStepsRemoved,
                             "PtsfSync", pstForeMaster->ulPtsfSync,
                             "RecvAnnCount",pstForeMaster->ulRecvAnnCount));

    TCPIP_InfoOutput(szBuf);

    return;
}


/*******************************************************************************
*    Func Name: PTPV2_BMC_SDAProcess
* Date Created: 2014-11-01
*       Author: z00208058
*  Description: AR-IP-PTP.002 源变化,走BMC状态决策流程
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-01   z00208058               Create
*
*******************************************************************************/
VOID PTPV2_BMC_SDAProcess(VOID)
{
    ULONG ulIter = 0;
    PTPV2_PORT_S *pstPtpPortInfo = NULL;
    PTPV2_FOREIGN_MASTER_S *pstErbest = NULL;
    UCHAR ucSelectPortFsmState = 0;
    UCHAR ucPortRole = 0;
    
    /*1.遍历所有的PTP 端口
      2.针对每个端口r首先选出Erbest
      3.然后根据<D0,Erbest,Ebest>选出每个端口的状态角色
    */
    for(ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
    {
        pstPtpPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);

        /*PTP端口信息不存在则返回失败*/
        if (NULL == pstPtpPortInfo || NULL == pstPtpPortInfo->pstSubPortInfo
            || (PTPV2_NO == pstPtpPortInfo->pstSubPortInfo->ucWorkState))
        {
            continue;
        }

        (VOID)PTPV2_1588_BMC(&(pstPtpPortInfo->dllForeignMasterHead), &pstErbest, BOOL_FALSE);/*选出Erbest*/
        /*选出端口r的状态*/
        ucSelectPortFsmState = PTPV2_BMC_SDAForPort(pstPtpPortInfo, g_pstVirtualD0, pstErbest, g_pstBmcEbest);

        /*更新本端口的状态等信息*/
        PTPV2_Set_FsmState(pstPtpPortInfo->pstSubPortInfo,ucSelectPortFsmState);

        /*设置端口的角色信息*/
        ucPortRole = PTPV2_GetPortRoleByFsmState(ucSelectPortFsmState);
        PTPV2_Set_PortRole(pstPtpPortInfo->pstSubPortInfo, ucPortRole);        
    }

}

/*******************************************************************************
*    Func Name: PTPV2_UpdateVirtualD0
* Date Created: 2014-11-08
*       Author: w00217009
*  Description: AR-IP-PTP.002 更新虚拟D0的Master信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
VOID PTPV2_UpdateVirtualD0()
{    
     if (NULL == g_pstVirtualD0)
     {
         return;
     }
    
    (VOID)TCPIP_Mem_Copy((VOID*)(g_pstVirtualD0->szGrandMasterId), sizeof(TCPIP_PTP_CLOCK_ID_SZ),
                         (VOID*)(g_pstPtpGlobalInfo->szClockId), sizeof(TCPIP_PTP_CLOCK_ID_SZ));

    (VOID)TCPIP_Mem_Copy((VOID*)&(g_pstVirtualD0->szForeignMasterPortId), sizeof(TCPIP_PTP_PORT_ID_S),
                         (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));

    g_pstVirtualD0->sCurrentUtcOffset = g_pstPtpGlobalInfo->stCfgDefaultDs.sCurrentUtcOffset;
    
    return;
}


/*******************************************************************************
*    Func Name: PTPV2_CreateVirtualD0
* Date Created: 2014-11-08
*       Author: w00217009
*  Description: AR-IP-PTP.002 创建虚拟D0的Master信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
PTPV2_FOREIGN_MASTER_S *PTPV2_CreateVirtualD0()
{    
    PTPV2_FOREIGN_MASTER_S *pstVirtualD0 = NULL;
    pstVirtualD0 =  (PTPV2_FOREIGN_MASTER_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_FOREIGN_MASTER, sizeof(PTPV2_FOREIGN_MASTER_S));
    if (NULL == pstVirtualD0)
    { 
       goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Set((CHAR *)pstVirtualD0, 0, sizeof(PTPV2_FOREIGN_MASTER_S));
    pstVirtualD0->pstPortInfo = (PTPV2_PORT_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_PORTINFO, sizeof(PTPV2_PORT_S));
    if (NULL == pstVirtualD0->pstPortInfo)
    {
        (VOID)TCPIP_Free(pstVirtualD0);
        pstVirtualD0 = NULL;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Set((CHAR *)pstVirtualD0->pstPortInfo, 0, sizeof(PTPV2_PORT_S));
    pstVirtualD0->pstPortInfo->pstSubPortInfo = (PTPV2_PORT_SUB_INFO_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_SUBPORTINFO, sizeof(PTPV2_PORT_SUB_INFO_S));
    if (NULL == pstVirtualD0->pstPortInfo->pstSubPortInfo)
    {
        (VOID)TCPIP_Free(pstVirtualD0->pstPortInfo);
        (VOID)TCPIP_Free(pstVirtualD0);
        pstVirtualD0 = NULL;
        goto EXIT_LABEL;
    }
    
    (VOID)TCPIP_Mem_Set((CHAR *)pstVirtualD0->pstPortInfo->pstSubPortInfo, 0, sizeof(PTPV2_PORT_SUB_INFO_S));    
        
    pstVirtualD0->ucGrandmasterPriority1 = 0x80;    
    pstVirtualD0->ucGrandmasterPriority2 = 0x80;    
    pstVirtualD0->usStepsRemoved = 0;
    pstVirtualD0->pstPortInfo->pstSubPortInfo->usPortNo = 0;

    /*D0的时钟质量固定,为最差值*/
    pstVirtualD0->stGrandmasterClockQuality.ucClockClass = 0xF8;
    pstVirtualD0->stGrandmasterClockQuality.ucClockAccuracy = 0xFE;
    pstVirtualD0->stGrandmasterClockQuality.usOffsetScaledLogVariance = 0xFFFF;

EXIT_LABEL:
    if (NULL == pstVirtualD0)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_02CA, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
             "TCPIP PTPV2 LOG: PTPV2_CreateVirtualD0 malloc failed.\r\n", 0, 0, 0, 0);
    }

    return pstVirtualD0;
}

/*******************************************************************************
*    Func Name: PTPV2_FreeVirtualD0
* Date Created: 2014-11-08
*       Author: w00217009
*  Description: AR-IP-PTP.002 释放虚拟D0的Master信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
VOID PTPV2_FreeVirtualD0()
{
    if (NULL == g_pstVirtualD0)
    {
        return;
    }

    (VOID)TCPIP_Free(g_pstVirtualD0->pstPortInfo->pstSubPortInfo);
    (VOID)TCPIP_Free(g_pstVirtualD0->pstPortInfo);
    (VOID)TCPIP_Free(g_pstVirtualD0);
    g_pstVirtualD0 = NULL;

    return ;
}

/*******************************************************************************
*    Func Name: PTPV2_BMCStateDecisionProcessOnPort
* Date Created: 2014-11-01
*       Author: z00208058
*  Description: AR-IP-PTP.002 决策出端口上的最佳源
*        Input: TCPIP_PTP_DEFAULT_DS_S *pstCfgDefaultDs:
*               PTPV2_PORT_S *pstPtpPortInfo:
*       Output: 
*       Return: PORT FSM ENUM
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-01   z00208058               Create
*
*******************************************************************************/
UCHAR PTPV2_BMC_SDAForPort(PTPV2_PORT_S* pstPortInfo,
                                          PTPV2_FOREIGN_MASTER_S *pstVirutalD0,
                                          PTPV2_FOREIGN_MASTER_S *pstErbest, 
                                          PTPV2_FOREIGN_MASTER_S *pstEbest)
{

    /*状态决策算法说明:
    <Do,Erbest,Ebest>作为输入条件，选择端口r的角色

    1.DO的class在1-127


    */
    BOOL_T bBetter = BOOL_FALSE;
    BOOL_T bTopoBetter = BOOL_FALSE;
    PTPV2_FOREIGN_MASTER_S *pstBmcResult = NULL;
    
    /*pstErbest/pstEbest可能为NULL
      pstPortInfo/pstVirutalD0 不可能为NULL 
    */
    if (NULL == pstPortInfo || NULL == pstVirutalD0)
    {
        return PTPV2_PORT_FSM_LISTENING;
    }   

    /*端口为listening &&  no master*/
    if ((PTPV2_PORT_FSM_LISTENING == pstPortInfo->pstSubPortInfo->ucPtpPortFsmState)
        &&(0 == pstPortInfo->dllForeignMasterHead.u4_Count))
    {
        return PTPV2_PORT_FSM_LISTENING;
    }    
    
    if ((pstVirutalD0->stGrandmasterClockQuality.ucClockClass >= 1)
        &&(pstVirutalD0->stGrandmasterClockQuality.ucClockClass <= 127))
    {
        (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_DO_WITH_ERBEST, pstVirutalD0, pstErbest, &pstBmcResult, &bBetter, &bTopoBetter);
        if (NULL == pstErbest || pstBmcResult == pstVirutalD0)/*选出来是 D0更优*/
        {
            return PTPV2_PORT_FSM_MASTER;
        }
        
        return PTPV2_PORT_FSM_PASSIVE;
    }

    /*D0 class 不在1-127之间，则..... D0  Ebest*/
    pstBmcResult = NULL;
    bBetter = BOOL_FALSE;
    bTopoBetter = BOOL_FALSE;
    (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_DO_WITH_EBEST, pstVirutalD0, pstEbest, &pstBmcResult, &bBetter, &bTopoBetter);
    if (NULL == pstEbest || pstBmcResult == pstVirutalD0)
    {
        return PTPV2_PORT_FSM_MASTER;
    }

    if (pstErbest == pstEbest)
    {
        return PTPV2_PORT_FSM_SLAVE;
    }

    /*比较Ebest和Erbest,set to passive state only if Ebest better by topology.
     *Ebest must is not null, Erbest maybe is null ,if Erbest is null, this port as master state
    */
    pstBmcResult = NULL;
    bBetter = BOOL_FALSE;
    bTopoBetter = BOOL_FALSE;
    (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_EBEST_WITH_ERBEST, pstEbest, pstErbest, &pstBmcResult, &bBetter, &bTopoBetter);
    /*拓扑更优，且返回是是Ebest，则是passive*/
    if ((BOOL_TRUE == bTopoBetter) && (pstBmcResult == pstEbest))
    {
        return PTPV2_PORT_FSM_PASSIVE;
    }

    return PTPV2_PORT_FSM_MASTER;
}

/*******************************************************************************
*    Func Name: PTPV2_BMC_DSCA_Part2
* Date Created: 2014-11-08
*       Author: w00217009
*  Description: 数据集比较算法的第二部分
*        Input: PTPV2_FOREIGN_MASTER_S* pstForeMasterA
*               PTPV2_FOREIGN_MASTER_S* pstForeMasterB
*       Output: PTPV2_FOREIGN_MASTER_S** ppstSelectMaster  从Input中选择的更佳源
*               BOOL_T* pbBetter: 选源结果是否为源更优
*               BOOL_T* pbTopoBetter: 选源结果是否为拓扑更优
*       Return: TCPIP_PTP_OK: 选到更好的源
*               TCPIP_PTP_ERR_POINTER_NULL:入参错误
*               TCPIP_PTP_ERR_BMC_ERRNO1: foremaster与本端的时钟id一样
*               TCPIP_PTP_ERR_BMC_ERRNO2: foremaster与本端的portnum一样
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
ULONG PTPV2_BMC_DSCA_Part2(ULONG ulCompareType, 
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterA,
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterB,
                                PTPV2_FOREIGN_MASTER_S** ppstSelectMaster,
                                BOOL_T* pbBetter, BOOL_T* pbTopoBetter)
{
    LONG                   lRet = 0;
    TCPIP_PTP_PORT_ID_S    stReceiverIdA;
    TCPIP_PTP_PORT_ID_S    stReceiverIdB;

    if (NULL == pstForeMasterA || NULL == pstForeMasterB || NULL == ppstSelectMaster)        
    {
        return TCPIP_PTP_ERR_POINTER_NULL;    
    }

    (VOID)TCPIP_Mem_Set((VOID*)&stReceiverIdA, 0, sizeof(TCPIP_PTP_PORT_ID_S));
    (VOID)TCPIP_Mem_Set((VOID*)&stReceiverIdB, 0, sizeof(TCPIP_PTP_PORT_ID_S));

    /*Step8:比较stepsRemoved,A与B的差距大于1,DataSet则stepsRemoved为0,如下为源更优*/
    if (pstForeMasterA->usStepsRemoved + 1 < pstForeMasterB->usStepsRemoved)
    {
        *ppstSelectMaster = pstForeMasterA;
        *pbBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }
    else if (pstForeMasterA->usStepsRemoved > pstForeMasterB->usStepsRemoved + 1)
    {       
        *ppstSelectMaster = pstForeMasterB;
        *pbBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }

    /*Step9:比较stepsRemoved,A与B的差距小于等于1,先确定A/B的receiver*/
    switch (ulCompareType)
    {
        case DSA_COMPAR_TYPE_DO_WITH_ERBEST:
        case DSA_COMPAR_TYPE_DO_WITH_EBEST:
            /*D0的receiver取本地clockid,portnum=0*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdA,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));
            stReceiverIdA.usPortNumber = 0;
            
            /*Erbest/Ebest的receiver都来自Ebest*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdB,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)&(g_pstBmcEbest->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S));
            break;
        case DSA_COMPAR_TYPE_EBEST_WITH_ERBEST:
            /*Erbest/Ebest的receiver都来自Ebest*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdA,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)&(g_pstBmcEbest->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S));
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdB,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)&(g_pstBmcEbest->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S));
            break;
         default:
            /*默认情况填本端clockid,portnum = 0*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdA,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdB,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));
            break;         
        
    }

   if (pstForeMasterA->usStepsRemoved < pstForeMasterB->usStepsRemoved)
    {
          
        (VOID)VOS_Mem_Cmp((void *)&stReceiverIdB, (void *)&(pstForeMasterB->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S), &lRet); 
        if (lRet < 0)/*stReceiverIdB < SenderB*/
        {
            *ppstSelectMaster = pstForeMasterA;
            *pbBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        else if (lRet > 0) /*stReceiverIdB > SenderB*/
        {
            *ppstSelectMaster = pstForeMasterA;
            *pbTopoBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        return TCPIP_PTP_ERR_BMC_ERRNO1;
    }
    else if (pstForeMasterA->usStepsRemoved > pstForeMasterB->usStepsRemoved)
    {
        (VOID)VOS_Mem_Cmp((void *)&stReceiverIdA, (void *)&(pstForeMasterA->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S), &lRet); 
        if (lRet < 0)  /*stReceiverIdA < senderA*/
        {
            *ppstSelectMaster = pstForeMasterB;
            *pbBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        else if (lRet > 0) /*stReceiverIdA > senderA*/
        {
            *ppstSelectMaster = pstForeMasterB;
            *pbTopoBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        return TCPIP_PTP_ERR_BMC_ERRNO1;
    }

    /*Step10:比较portId*/
    (VOID)VOS_Mem_Cmp((void *)&(pstForeMasterA->szForeignMasterPortId), (void *)&(pstForeMasterB->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S), &lRet);
    if (lRet < 0)
    {
        *ppstSelectMaster = pstForeMasterA;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }
    else if (lRet > 0)
    {       
        *ppstSelectMaster = pstForeMasterB;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }

    /*Step11:比较A与B所对应的PTP端口号，在当前实现中始终相同*/
    if (stReceiverIdA.usPortNumber > stReceiverIdB.usPortNumber)
    {
        *ppstSelectMaster = pstForeMasterB;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }
    else if (stReceiverIdA.usPortNumber < stReceiverIdB.usPortNumber)
    {
        *ppstSelectMaster = pstForeMasterA;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }

    return TCPIP_PTP_ERR_BMC_ERRNO2;
}

/*******************************************************************************
*    Func Name: PTPV2_BMC_PPI_SlaveRole
* Date Created: 2014-11-26
*       Author: w00217009
*  Description: 下发Slave角色
*                1.如果源变化，则重新下发PPI 更新
*                2.如果源不变，但参数变化，则下发参数变化命令字
*                3.其他，则不处理
*        Input: PTPV2_FOREIGN_MASTER_S* pstSelectMaster: 下发slave对应的Ebest
*               ULONG ulCmd:下发的命令字
*               ULONG ulChangeField: 参数变化标志
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
ULONG PTPV2_BMC_PPI_SlaveRole(PTPV2_FOREIGN_MASTER_S* pstSelectMaster,  ULONG ulCmd, ULONG ulChangeField)
{
    TCPIP_PTP_SLAVE_PPI_S  stPpiData;
    PTPV2_PORT_S* pstPortInfo = NULL;
    ULONG ulPtpV2ClockType = 0;
    ULONG ulRet = TCPIP_PTP_OK;

    if (NULL == g_pfPtpV2PpiHookFunc)
    {
        return TCPIP_PTP_ERR_HOOK_UNREG;
    }

    /*下发删除 则启动告警定时器*/
    if ((TCPIP_PTP_PPI_DEL == ulCmd))
    {
        /*启动告警定时器*/
        (VOID)PTPV2_CreateWarningTimer();
    }
    
    ulPtpV2ClockType = PTPV2_GetClockType();

    VOS_DBGASSERT(PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType);

    if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
    {
        return TCPIP_PTP_ERR_NOT_SUPPORT_IN_OC;
    }

    pstPortInfo = pstSelectMaster->pstPortInfo;
    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo)
    {
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }

    /*选出源Ebest,对应端口为Slave角色才下发Slave,并记录下发标记*/
    if(TCPIP_PTP_PPI_ADD == ulCmd)
    {
        if (TCPIP_PTP_PORT_ROLE_SLAVE != pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            return TCPIP_PTP_ERR;
        }
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag |= PTPV2_PPI_SLAVE_FLAG;
    }
    else if(TCPIP_PTP_PPI_DEL == ulCmd)
    {   /*删除源Ebest,对应端口有下发过Slave,则下发删除Slave,后续会重新选源,并设置状态和角色*/
        PTPV2_Set_FsmState(pstPortInfo->pstSubPortInfo, PTPV2_PORT_FSM_LISTENING);
        PTPV2_Set_PortRole(pstPortInfo->pstSubPortInfo, TCPIP_PTP_PORT_ROLE_MASTER);
        if (0 == (PTPV2_PPI_SLAVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag))
        {
            return TCPIP_PTP_ERR;
        }
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag &= ~PTPV2_PPI_SLAVE_FLAG;
    }

    (VOID)TCPIP_Mem_Set((CHAR*)&stPpiData, 0, sizeof(TCPIP_PTP_SLAVE_PPI_S));

    /*构造下发给产品的信息*/
    stPpiData.ulIfIndex =  pstSelectMaster->ulRcvIfIndex;
    (VOID)TCPIP_Mem_Copy((VOID*)&(stPpiData.stLocalAddr),sizeof(TCPIP_PTP_PORT_ADDR_S),
            (VOID*)&(pstPortInfo->stPtpPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S));
    stPpiData.usLocalPortNo = pstPortInfo->pstSubPortInfo->usPortNo;
    stPpiData.bTwoStep = g_pstPtpGlobalInfo->stCfgDefaultDs.bTwoStepFlag;
    (VOID)TCPIP_Mem_Copy((VOID*)&(stPpiData.stParentDS), sizeof(TCPIP_PTP_PARENT_DS_S),
            (VOID*)&(g_pstPtpGlobalInfo->stParentDs), sizeof(TCPIP_PTP_PARENT_DS_S));

    /*参数变化标志*/
    stPpiData.ulChangeField = ulChangeField;

    ulRet = g_pfPtpV2PpiHookFunc(TCPIP_PTP_PORT_ROLE_SLAVE , ulCmd, &stPpiData);
    (VOID)PTPV2_PPI_LogMsg(ulRet, pstPortInfo->pstSubPortInfo->usPortNo, ulCmd, &stPpiData);

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_PPI_PassiveRole
* Date Created: 2014-11-08
*       Author: w00217009
*  Description: 下发passive角色
*        Input: ULONG ulCmd:下发的命令字
*               PTPV2_PORT_S* pstPortInfo:需要下发passive信息的端口
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/
VOID PTPV2_PPI_PassiveRole(ULONG ulCmd, PTPV2_PORT_S* pstPortInfo)
{
    ULONG ulRet = 0;
    ULONG ulCanPPI = VRP_NO;
    UCHAR ucLocalMac[PTPV2_MACADDRLEN] = {0};
    TCPIP_PTP_PASSIVE_PPI_S stPpiPassiveData;

    if (NULL == g_pfPtpV2PpiHookFunc)
    {
        return;
    }

    (VOID)TCPIP_Mem_Set((VOID*)&stPpiPassiveData, 0, sizeof(TCPIP_PTP_PASSIVE_PPI_S));
    (VOID)TCPIP_GetEtharpMac(pstPortInfo->ulIfIndex, ucLocalMac);
    
    (VOID)TCPIP_Mem_Copy((VOID*)stPpiPassiveData.stLocalAddr.unAddr.ucMacAddr, 8,(VOID*)ucLocalMac, PTPV2_MACADDRLEN);
    stPpiPassiveData.ulIfIndex = pstPortInfo->ulIfIndex;
    stPpiPassiveData.usLocalPortNo = pstPortInfo->pstSubPortInfo->usPortNo;

    if (TCPIP_PTP_PPI_ADD == ulCmd)
    {   
        ulCanPPI = PTPV2_YES;
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag |= PTPV2_PPI_PASSIVE_FLAG;
    }
    else if (TCPIP_PTP_PPI_DEL == ulCmd)
    {   /*Del passive:1.del port*/
        ulCanPPI = PTPV2_YES;
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag &= ~PTPV2_PPI_PASSIVE_FLAG;
    }
    

    if (VRP_YES == ulCanPPI)
    {
        ulRet = g_pfPtpV2PpiHookFunc(TCPIP_PTP_PORT_ROLE_PASSIVE, ulCmd, (VOID *)&stPpiPassiveData);
        PTPV2_PPI_LogMsg(ulRet, pstPortInfo->pstSubPortInfo->usPortNo, ulCmd, &stPpiPassiveData);
    }

    return;
}

/*******************************************************************************
*    Func Name: PTPV2_BMC_PPI_PassiveRoleForAll
* Date Created: 2014-11-08
*       Author: w00217009
*  Description: 遍历所有端口,判断是否下发passive角色
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   w00217009               Create
*
*******************************************************************************/    
VOID PTPV2_BMC_PPI_PassiveRoleForAll()
{
    ULONG ulIter = 0;
    PTPV2_PORT_S *pstPortInfo = NULL;

    for(ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
    {
        pstPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);

        if (NULL == pstPortInfo)
        {
            continue;
        }
        if (TCPIP_PTP_PORT_ROLE_SLAVE == pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            /*1.passive->slave : ppi del passive
             *2.master->slave  : do nothing
             *3.slave->slave   : do nothing
            */
            if (PTPV2_PPI_PASSIVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag)
            {
               PTPV2_PPI_PassiveRole(TCPIP_PTP_PPI_DEL, pstPortInfo);
            }
        }
        else if (TCPIP_PTP_PORT_ROLE_MASTER== pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            /*1.passive->master: ppi del passive
             *2.slave->master  : do nothing
             *3.master->master : do noting
            */
            if (PTPV2_PPI_PASSIVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag)
            {
                PTPV2_PPI_PassiveRole(TCPIP_PTP_PPI_DEL, pstPortInfo);
            }
        }
        else if (TCPIP_PTP_PORT_ROLE_PASSIVE == pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            /*1.slave->passive  : ppi add passive
             *2.master->passive : ppi add passive
             *3.passive->passive: do nothing
            */
            if (0 == (PTPV2_PPI_PASSIVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag))
            {
                PTPV2_PPI_PassiveRole(TCPIP_PTP_PPI_ADD, pstPortInfo);
            }
        }
    }
    
    return;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
