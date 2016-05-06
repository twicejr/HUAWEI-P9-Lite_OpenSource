/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_common.c
*
*  Project Code:
*   Module Name: PTPV2 var
*  Date Created: 2014-03-03
*        Author: luoagwoei
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03    luoagwoei               Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/ptpv2/include/ptpv2_ann.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_timer.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/etharp/include/etharp_api.h"

extern ULONG IF_PhyIoCtrl(IFNET_S *pstIf, ULONG ulCmd, CHAR *pszData);

/*******************************************************************************
*    Func Name: PTPV2_Lock
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: PTPV2加锁
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_Lock(VOID)
{
    TCPIP_BEGIN_PT(g_ulSemForTightMods);
    return;
}

/*******************************************************************************
*    Func Name: PTPV2_UnLock
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: PTPV2解锁
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_UnLock(VOID)
{
    TCPIP_END_PT(g_ulSemForTightMods);
    return;
}

/*******************************************************************************
*    Func Name: PTPV2_GetClockType
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 获取时钟类型
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_GetClockType()
{
    return g_ulPtpV2ClockType;
}

/*******************************************************************************
*    Func Name: PTPV2_GetInitFlag
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 获取P2PV2初始化状态
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_GetInitFlag()
{
    return g_ulPtpV2InitFlag;
}

/*************************************************************************
*    Func Name: PTPV2_PktCircularSpaceCmp
* Date Created: 
*       Author: 
*  Description: 比较两数是否相等，以及偏差是否超过定义的半空间大小
*        Input: USHORT a, 数值a
*               USHORT b，数值b
*               USHORT usHalfSpace, 半空间大小
*       Output:
*       Return: 0: a与b相等
*               1: a到b的距离大于序号环(由小到大的方向，如图中里环所示)空间的一半
*               -1:a到b的距离小于序号环(由小到大的方向，如图中里环所示)空间的一半
*
*                          a
*               .-n--0--1--2--3
*               |   -->-->    |
*               .  |      |   4 b
*               |   <--<--    |
*               .-.--.--.--.--5
*
*      Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   
*
*************************************************************************/
LONG PTPV2_PktCircularSpaceCmp (USHORT a, USHORT b, USHORT usHalfSpace)
{
    if (a == b)
    {
        return 0;
    }
    else if (a > b)
    {
        if ((a-b) <= usHalfSpace)
        {
            return 1;
        }
        else
        {
            return (-1);
        }
    }
    else
    {
        if ((b-a) > usHalfSpace)
        {
            return 1;
        }
        else
        {
            return (-1);
        }
    }
}

/*******************************************************************************
*    Func Name: PTPV2_Port_Tree_Compare
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: Port节点比较函数
*        Input: void* a:
*               void* b:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
LONG PTPV2_Port_Tree_Compare(void* a, void* b)
{
    LONG result = 0;

    PTPV2_PORT_S* pSrc = (PTPV2_PORT_S*)a;
    PTPV2_PORT_S* pDst = (PTPV2_PORT_S*)b;
    if (pSrc->ulIfIndex > pDst->ulIfIndex)
    {
        result = 1;
        goto EXIT_LABEL;
    }
    else if (pSrc->ulIfIndex < pDst->ulIfIndex)
    {
        result = -1;
        goto EXIT_LABEL;
    }

    if (pSrc->stPtpPortAddr.unAddr.ulIpv4 > pDst->stPtpPortAddr.unAddr.ulIpv4)
    {
        result = 1;
        goto EXIT_LABEL;
    }
    else if (pSrc->stPtpPortAddr.unAddr.ulIpv4 < pDst->stPtpPortAddr.unAddr.ulIpv4)
    {
        result = -1;
        goto EXIT_LABEL;
    }

EXIT_LABEL:
    return result;
}

/*******************************************************************************
*    Func Name: PTPV2_Slave_Tree_Compare
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 
*        Input: void* a:
*               void* b:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
LONG PTPV2_Slave_Tree_Compare(void* a, void* b)
{
    return 0;
}

/*******************************************************************************
*    Func Name: PTPV2_GetGlobalInfo
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 获取PTPV2全局信息
*        Input: ULONG ulCmd:
*               ULONG* pData:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_GetGlobalInfo(ULONG ulCmd, ULONG* pData)
{
    if (NULL == pData)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    switch (ulCmd)
    {

        case PTPV2_CMD_BMC_POLICY:
            *pData  = (ULONG)g_pstPtpGlobalInfo->ucBMCPolicy;
            break;
        case PTPV2_CMD_MASTER_NUM_LIMIT:/*用户配置的master 最大个数*/
            *pData = g_pstPtpGlobalInfo->ulMaxMasterNum;
            break;
        case PTPV2_CMD_CURRENT_MASTER_NUMS: /*当前系统的master个数*/
            *pData = (ULONG)g_GlobalForeignMasterList.u4_Count;
            break;
        case PTPV2_CMD_PORT_FSM_MODE: /*当前的FSM 模式*/
            *pData = (ULONG)g_pstPtpGlobalInfo->stCfgDefaultDs.usClockFsmMode;
            break;
        default:
            break;
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_CheckIfIndex
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ulIfIndex:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CheckIfIndex(ULONG ulIfIndex)
{
    IFNET_S*   pIf = NULL;
    ULONG ulPtpV2ClockType = 0;

    /* 根据接口索引找到接口指针 */
    pIf = IF_GetIfByIndex(ulIfIndex);
    if (NULL == pIf)
    {
        return TCPIP_PTP_ERR_INTF_NOT_EXIST;
    }

    /*仅支持TRUNK/Ethernet以及子接口
    注意:对于L3 单播，将来需要支持LoopBack接口*/
    if (PORT_ETHERNET == pIf->if_ulPortType
        || PORT_GE == pIf->if_ulPortType
        || PORT_ETH_TRUNK == pIf->if_ulPortType)
    {

        return TCPIP_PTP_OK ;
    }

    ulPtpV2ClockType = PTPV2_GetClockType();

    /*BC仅支持L2IF， 不支持L3IF*/
    if ((!IF_IS_L2ETH(pIf)) && (PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType))
    {
        return TCPIP_PTP_ERR_NON_L2IF;
    }

    return TCPIP_PTP_ERR_INTF_TYPE;
}

/*******************************************************************************
*    Func Name: PTPV2_CheckPortNoUpToMax
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CheckPortNoUpToMax()
{
    ULONG ulPtpV2ClockType = 0;

    ulPtpV2ClockType = PTPV2_GetClockType();
    if ((PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType && g_pstPortManageInfo->ulCrtPortCount >= PTPV2_MAX_PORTNO)
        ||(PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType && g_pstPortManageInfo->ulCrtPortCount >= g_pstPtpGlobalInfo->usSndPortMaxNum))
    {
        return TCPIP_PTP_ERR_PROTNO_FULL;
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_CheckPortValidation
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG usPtpPortNo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CheckPortValidation(ULONG usPtpPortNo)
{
    ULONG ulPtpV2ClockType;
    ulPtpV2ClockType = PTPV2_GetClockType();

    if ((PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType && usPtpPortNo != PTPV2_MIN_PORTNO)
        ||(PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType && (usPtpPortNo < PTPV2_MIN_PORTNO || usPtpPortNo > PTPV2_MAX_PORTNO)))
    {
        return TCPIP_PTP_ERR_INVALID_PARA;
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_GetPortInfoByPort
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: 根据PTP端口号获取端口数据
*        Input: ULONG usPtpPortNo:
*               PTPV2_PORT_S **ppstPortInfo:
*       Output:
*       Return:
*      Caution: 对于OC来说，只获取第一个的端口数据
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GetPortInfoByPort(ULONG usPtpPortNo, PTPV2_PORT_S **ppstPortInfo)
{
    ULONG ulHandle = NULL;
    ULONG ulIter = 0;
    ULONG ulPtpV2ClockType = 0;

    ulPtpV2ClockType = PTPV2_GetClockType();

    if (PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType)
    {
        ulHandle = g_pstPortManageInfo->ulPortInfoHandle[usPtpPortNo];

        /*PTP端口信息不存在则返回失败*/
        if (0 == ulHandle)
        {
            return TCPIP_PTP_ERR_PROTINFO_NOT_EXIST;
        }

        *ppstPortInfo = (PTPV2_PORT_S *)ulHandle;
    }
    /*Added by wuling for DTS2014101506342  2014-10-27 OC下启动端口需要寻找最小可用的PTP端口索引号*/
    else
    {
        if (g_pstPortManageInfo->ulCrtPortCount > 0)
        {
            /*获取可用的索引*/
            for (ulIter = PTPV2_MIN_PORTNO; ulIter < PTPV2_MAX_PORTNO + 1; ulIter++)
            {
                ulHandle = g_pstPortManageInfo->ulPortInfoHandle[ulIter];
                if (ulHandle != 0)
                {
                    *ppstPortInfo = (PTPV2_PORT_S *)ulHandle;
                    return TCPIP_PTP_OK;
                }
            }

            /*找不到可用的PTP端口,系统异常*/
            return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        }
        else
        {
            /*当前没有配置任何接口索引,无法Start PTP端口*/
            return TCPIP_PTP_ERR_PROTINFO_NOT_EXIST;
        }
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_GetPortInfoByIntf
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: 根据接口索引和地址信息获取端口数据
*        Input: ULONG ulIfIndex: 接口索引
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 地址 :用于将来扩展
*
*       Output: PTPV2_PORT_S** ppstFindPortInfo: 返回的端口数据
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GetPortInfoByIntf(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr, PTPV2_PORT_S** ppstFindPortInfo)
{
    PTPV2_PORT_S  stPort;
    PTPV2_PORT_S* pstIter = NULL;

    (VOID)pstPtpAddr;
    VOS_DBGASSERT(NULL != ppstFindPortInfo);

    (VOID)TCPIP_Mem_Set((CHAR*)&stPort, 0, sizeof(PTPV2_PORT_S));

    stPort.ulIfIndex = ulIfIndex;

    pstIter = (PTPV2_PORT_S*)PTPV2_find(g_PtpV2Tree, &stPort, g_PtpV2TreeInfo);
    if (NULL == pstIter)
    {
        return TCPIP_PTP_ERR;
    }

    *ppstFindPortInfo = pstIter;
    return TCPIP_PTP_OK;

}

/*******************************************************************************
*    Func Name: PTPV2_DelOCPortInfo
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 删除OC端口信息
*        Input: PTPV2_PORT_S  *pstDelPortInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_DelOCPortInfo(PTPV2_PORT_S  *pstDelPortInfo)
{
    PTPV2_LOGIC_TIMER_S *pstLogicTimer = NULL;
    PTPV2_PORT_S *pstTimerPortInfo = NULL;
    ULONG ulIter = 0;

    if (NULL == pstDelPortInfo)
    {
        return TCPIP_PTP_ERR_PROTINFO_NOT_EXIST;
    }

    /*OC端口下绑定的地址即将全被删除时,删除发送定时器,端口状态回到非Start状态*/
    if (1 == g_pstPortManageInfo->ulCrtPortCount)
    {
        g_pstOCPortSubInfo->ucWorkState = PTPV2_NO;

        /*从多播组中删除*/
        if (TCPIP_PTP_CLOCK_IEEE8023_MODE == pstDelPortInfo->pstSubPortInfo->ucCastMode)
        {
            IFNET_S *pstIfnet = NULL;
            UCHAR aucMacMask[MACADDRLEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

            pstIfnet = IF_GetIfByIndex(pstDelPortInfo->ulIfIndex);
            if (NULL != pstIfnet)
            {
                (VOID)IF_PhyIoCtrl(pstIfnet, (ULONG)PHY_LEAVEMULTI, (CHAR *)g_szMacPTPV2_E2E);
                (VOID)PPI_MultiMac_Update(pstDelPortInfo->ulIfIndex, PPI_MULTICMAC_DEL, (UCHAR*)g_szMacPTPV2_E2E, (UCHAR*)aucMacMask);
            }
        }

        /*master 要删除发送定时器，目前不支持slave*/
        if (TCPIP_PTP_PORT_ROLE_MASTER == pstDelPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            (VOID)PTPV2_DeleteLogicTimer(pstDelPortInfo->pstSubPortInfo->ulAnnSndTimerId);
        }
    }
    /*删除指定接口索引绑定的PTP控制块后,还有绑定其他接口索引的PTP控制块*/
    else
    {
        pstLogicTimer = (PTPV2_LOGIC_TIMER_S *)pstDelPortInfo->pstSubPortInfo->ulAnnSndTimerId;
        if (pstLogicTimer != NULL)
        {
            pstTimerPortInfo = (PTPV2_PORT_S *)pstLogicTimer->pArg;
            if (NULL == pstTimerPortInfo)
            {
                return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
            }

            /*发送定时器绑定在即将删除的PTP控制块上,重新将发送定时器绑定在第一个可用的PTP控制块上*/
            if (pstTimerPortInfo == pstDelPortInfo)
            {
                /*获取可用的索引*/
                for (ulIter = PTPV2_MIN_PORTNO; ulIter < PTPV2_MAX_PORTNO + 1; ulIter++)
                {
                    pstTimerPortInfo = (PTPV2_PORT_S *)g_pstPortManageInfo->ulPortInfoHandle[ulIter];
                    if ((pstTimerPortInfo != NULL) && (pstTimerPortInfo != pstDelPortInfo))
                    {
                        pstLogicTimer->pArg = (VOID *)pstTimerPortInfo;
                        break;
                    }
                }
            }
        }
    }

    /* 从树中移除端口控制块*/
    PTPV2_avl_delete(g_PtpV2Tree, pstDelPortInfo->stPtpPortNode);

    g_pstPortManageInfo->ulPortInfoHandle[pstDelPortInfo->ulPtpPortAllocIndex] = 0;

    if (g_pstPortManageInfo->ulCrtPortCount > 0)
    {
       g_pstPortManageInfo->ulCrtPortCount--;
       g_pstPtpGlobalInfo->stCfgDefaultDs.ulNumberPorts =  g_pstPortManageInfo->ulCrtPortCount;
    }

    /* 释放端口控制块*/
    (VOID)TCPIP_Free(pstDelPortInfo);

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_DelAllOCPortInfo
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 删除所有OC端口信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_DelAllOCPortInfo()
{
    ULONG ulIter = 0;
    PTPV2_PORT_S *pstDelPortInfo = NULL;

    for(ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
    {
         pstDelPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);
         if (NULL == pstDelPortInfo)
         {
             continue;
         }

         (VOID)PTPV2_DelOCPortInfo(pstDelPortInfo);
    }

    (VOID)TCPIP_Free(g_pstOCPortSubInfo);
    g_pstOCPortSubInfo = NULL;
    return;
}

/*******************************************************************************
*    Func Name: PTPV2_DelBCPortInfo
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 删除BC端口信息
*        Input: PTPV2_PORT_S *pstDelPortInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_DelBCPortInfo(PTPV2_PORT_S *pstDelPortInfo)
{
    PTPV2_FOREIGN_MASTER_S *pstIterMaster = NULL;

    if (NULL == pstDelPortInfo || NULL == pstDelPortInfo->pstSubPortInfo)
    {
        return TCPIP_PTP_ERR;
    }

    /*删除相关定时器*/
    if (0 != pstDelPortInfo->pstSubPortInfo->ulAnnSndTimerId)
    {
        (VOID)PTPV2_DeleteLogicTimer(pstDelPortInfo->pstSubPortInfo->ulAnnSndTimerId);
    }

    /*删除BC 1.当前是master ,do nothing
     *       2.当前是slave  ,do nothing
     *       3.当前是passive,ppi del passive
    */
    if ((TCPIP_PTP_PORT_ROLE_PASSIVE == pstDelPortInfo->pstSubPortInfo->ucPtpPortRole)
        && (PTPV2_PPI_PASSIVE_FLAG & pstDelPortInfo->pstSubPortInfo->ucPpiRoleFlag))
    {
        PTPV2_PPI_PassiveRole(TCPIP_PTP_PPI_DEL,pstDelPortInfo);
    }

    /*删除ForeignMaster*/
    while (NULL != (pstIterMaster = (PTPV2_FOREIGN_MASTER_S *)DLL_First(&pstDelPortInfo->dllForeignMasterHead)))
    {
        (VOID)PTPV2_DelForeignMaster(pstIterMaster);
    }

    /* 从树中移除端口控制块*/
    PTPV2_avl_delete(g_PtpV2Tree, pstDelPortInfo->stPtpPortNode);

    if (TCPIP_PTP_CLOCK_IEEE8023_MODE == pstDelPortInfo->pstSubPortInfo->ucCastMode)/*从多播组中删除*/
    {
        IFNET_S *pstIfnet = NULL;
        UCHAR aucMacMask[MACADDRLEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        pstIfnet = IF_GetIfByIndex(pstDelPortInfo->ulIfIndex);
        if (NULL != pstIfnet)
        {
            (VOID)IF_PhyIoCtrl(pstIfnet, (ULONG)PHY_LEAVEMULTI, (CHAR *)g_szMacPTPV2_E2E);
            (VOID)PPI_MultiMac_Update(pstDelPortInfo->ulIfIndex, PPI_MULTICMAC_DEL, (UCHAR*)g_szMacPTPV2_E2E, (UCHAR*)aucMacMask);
        }
    }

    g_pstPortManageInfo->ulPortInfoHandle[pstDelPortInfo->ulPtpPortAllocIndex] = 0;
    if (g_pstPortManageInfo->ulCrtPortCount > 0)
    {
       g_pstPortManageInfo->ulCrtPortCount--;
       g_pstPtpGlobalInfo->stCfgDefaultDs.ulNumberPorts =  g_pstPortManageInfo->ulCrtPortCount;
    }
    
    /*3 释放端口控制块*/
    (VOID)TCPIP_Free(pstDelPortInfo->pstSubPortInfo);
    (VOID)TCPIP_Free(pstDelPortInfo);

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_DelAllBCPortInfo
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 删除所有BC端口信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_DelAllBCPortInfo()
{
    ULONG ulIter = 0;
    PTPV2_PORT_S *pstDelPortInfo = NULL;

    for (ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
    {
         pstDelPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);
         if (NULL == pstDelPortInfo)
         {
             continue;
         }

         (VOID)PTPV2_DelBCPortInfo(pstDelPortInfo);
    }

    return;
}

/*******************************************************************************
*    Func Name: PTPV2_AddPortInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ulIfIndex:
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 地址不使用，用于将来L3 单播扩展
*               PTPV2_PORT_S** ppstAddPortInfo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_AddPortInfo(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr, PTPV2_PORT_S** ppstAddPortInfo)
{
    PTPV2_PORT_S* pstNewPortInfo = NULL;
    ULONG ulPtpV2ClockType = 0;

    (VOID)pstPtpAddr;
    VOS_DBGASSERT(NULL != ppstAddPortInfo);

    /*1 申请端口控制块*/
    pstNewPortInfo = (PTPV2_PORT_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_PORTINFO,  sizeof(PTPV2_PORT_S));
    if (NULL == pstNewPortInfo)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FC, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
            "TCPIP PTPV2 LOG: PTPV2_AddPortInfo malloc pstNewPortInfo failed.\r\n",
                         0, 0, 0, 0);
        return TCPIP_PTP_ERR_MALLOC_FAIL;
    }

    (VOID)TCPIP_Mem_Set((CHAR*)pstNewPortInfo, 0, sizeof(PTPV2_PORT_S));
    DLL_Init(&pstNewPortInfo->dllForeignMasterHead);/*初始化ptp端口的备用时钟源链表*/

    pstNewPortInfo->ulIfIndex = ulIfIndex;

    /*2 将端口控制块加入树*/
    PTPV2_init_avl_node(pstNewPortInfo->stPtpPortNode);
    (VOID)PTPV2_avl_insert(g_PtpV2Tree, pstNewPortInfo->stPtpPortNode, g_PtpV2TreeInfo);

    ulPtpV2ClockType = PTPV2_GetClockType();

    /*3 申请端口子控制块*/
    if (PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType)
    {
        pstNewPortInfo->pstSubPortInfo = (PTPV2_PORT_SUB_INFO_S *)TCPIP_Malloc(PTPV2_MID | SID_PTP_SUBPORTINFO,  sizeof(PTPV2_PORT_SUB_INFO_S));
        if (NULL == pstNewPortInfo->pstSubPortInfo)
        {
            PTPV2_avl_delete(g_PtpV2Tree, pstNewPortInfo->stPtpPortNode);
            (VOID)TCPIP_Free(pstNewPortInfo);
            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FD, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
               "TCPIP PTPV2 LOG: PTPV2_AddPortInfo malloc pstSubPortInfo failed.\r\n",
               0, 0, 0, 0);
            return TCPIP_PTP_ERR_MALLOC_FAIL;
        }

        (VOID)TCPIP_Mem_Set((CHAR *)(pstNewPortInfo->pstSubPortInfo), 0, sizeof(PTPV2_PORT_SUB_INFO_S));
    }
    else if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
    {
        pstNewPortInfo->pstSubPortInfo = g_pstOCPortSubInfo;
        VOS_DBGASSERT(NULL != pstNewPortInfo->pstSubPortInfo);
    }

    *ppstAddPortInfo = pstNewPortInfo;

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_DelOCPortInfoEntry
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 删除OC端口实例
*        Input: USHORT usPtpPortNo:
*               ULONG ulIfIndex:
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_DelOCPortInfoEntry(USHORT usPtpPortNo, ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr)
{
    PTPV2_PORT_S  *pstDelPortInfo = NULL;
    ULONG ulRet = TCPIP_PTP_OK;

    (VOID)usPtpPortNo;
    ulRet = PTPV2_GetPortInfoByIntf(ulIfIndex, pstPtpAddr, &pstDelPortInfo);
    if (TCPIP_PTP_OK != ulRet || NULL == pstDelPortInfo)
    {
        return TCPIP_PTP_ERR_PROTINFO_NOT_EXIST;
    }

    (VOID)PTPV2_DelOCPortInfo(pstDelPortInfo);

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_DelBCPortInfoEntry
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 删除BC端口实例
*        Input: USHORT usPtpPortNo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_DelBCPortInfoEntry(USHORT usPtpPortNo)
{
    PTPV2_FOREIGN_MASTER_S *pstSelectMaster = NULL;
    PTPV2_PORT_S *pstDelPortInfo = NULL;

    pstDelPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[usPtpPortNo]);
    if (NULL == pstDelPortInfo)
    {
        return TCPIP_PTP_ERR_PROTINFO_NOT_EXIST;
    }

    (VOID)PTPV2_DelBCPortInfo(pstDelPortInfo);

    /*删除端口后需要重新选一次时钟源*/
    (VOID)PTPV2_BMCProcess(&pstSelectMaster);
    (VOID)PTPV2_BMCNotify(pstSelectMaster);/*选源后处理，更新参数,删除master 会进行PPI 下发处理*/

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_InitPortSubInfo
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: PTPV2_PORT_SUB_INFO_S *pstPortSubInfo:
*               ULONG ulFsmMode:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_InitPortSubInfo(PTPV2_PORT_SUB_INFO_S *pstPortSubInfo, ULONG ulFsmMode)
{
    if (NULL == pstPortSubInfo)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }
    
    pstPortSubInfo->usPortNo = PTPV2_MIN_PORTNO;
    pstPortSubInfo->stPortAnnInfo.usSndAnnSequenceId = 0;/*announce序列号*/
    pstPortSubInfo->stPortAnnInfo.clogAnnounceInterval = 1; /*Announce消息的发送间隔, 默认1  -3--3*/
    pstPortSubInfo->stPortAnnInfo.ucAnnRcvTimeoutNum = 3;/*Announce消息的接收超时 默认3    2--10*/
    pstPortSubInfo->ucDelayMechanism = TCPIP_PTP_DELAY_MACHENISM_E2E;/*E2E P2P  none*/
    pstPortSubInfo->ucCastMode  = TCPIP_PTP_CLOCK_IEEE8023_MODE;/*单播、多播模式，目前仅支持L2组播*/
    pstPortSubInfo->ulAnnSndTimerId = 0; /*端口的定时器集合:发送定时器*/
    PTPV2_Set_FsmState(pstPortSubInfo, PTPV2_PORT_FSM_INITIALIZING);/*Add Port过程中置端口状态机状态为listening,AR-IP-PTP.002*/
    PTPV2_Set_PortRole(pstPortSubInfo, TCPIP_PTP_PORT_ROLE_UNDEFINED);/*Add Port过程中置端口角色为undefined,AR-IP-PTP.002*/

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_InitPortInfo
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: PTPV2_PORT_S* pstPortInfo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_InitPortInfo(PTPV2_PORT_S* pstPortInfo)
{
    ULONG ulIter = 0;
    ULONG ulFsmMode = 0;
    ULONG ulCrtPos = 0;
    ULONG ulPtpV2ClockType = 0;
    /*slave树节点 暂时没有，填0*/

    /*初始化PTP 端口的地址树，用于后续OC地址扩展*/
    (VOID)TCPIP_Mem_Set((CHAR*)&pstPortInfo->stSlavetreeRoot, 0, sizeof(AVL3_TREE_S));
    
    (VOID)PTPV2_GetGlobalInfo(PTPV2_CMD_PORT_FSM_MODE, &ulFsmMode);

    ulPtpV2ClockType = PTPV2_GetClockType();

    if (PTPV2_CLOCK_TYPE_BC== ulPtpV2ClockType)
    {
        /*BC下进行端口级参数初始化*/
        (VOID)PTPV2_InitPortSubInfo(pstPortInfo->pstSubPortInfo, ulFsmMode);
    }

    /*获取可用的索引*/
    for (ulIter = PTPV2_MIN_PORTNO; ulIter < PTPV2_MAX_PORTNO + 1; ulIter++)
    {
        if (0 == g_pstPortManageInfo->ulPortInfoHandle[ulIter])
        {
            ulCrtPos = ulIter;
            break;
        }
    }

    if (0 == ulCrtPos)/*没有可用的分配索引,应当是数据错误，因为初始化前已经判定了*/
    {
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }

    pstPortInfo->ulPtpPortAllocIndex = ulCrtPos;/*BC中端口号和分配索引相同*/

    if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
    {
        pstPortInfo->pstSubPortInfo->usPortNo = PTPV2_MIN_PORTNO; /*OC只有一个端口号*/
    }
    else
    {
        pstPortInfo->pstSubPortInfo->usPortNo =  ulCrtPos;  /*BC借用索引号作为端口号*/
    }

    g_pstPortManageInfo->ulPortInfoHandle[ulCrtPos] = (ULONG)pstPortInfo;
    g_pstPortManageInfo->ulCrtPortCount++; 
    g_pstPtpGlobalInfo->stCfgDefaultDs.ulNumberPorts =  g_pstPortManageInfo->ulCrtPortCount;

    if (PTPV2_FSM_MODE_OC_MASTER == ulFsmMode)
    {
        pstPortInfo->pfPtpStartFunc = PTPV2_OcStart;
        pstPortInfo->pfPtpStopFunc = PTPV2_Stop;
        pstPortInfo->pfPtpBuildAnnPktFunc = PTPV2_OC_MasterBuildAnnPkt;
        pstPortInfo->pfPtpSndAnnPktFunc = PTPV2_OverMacSndAnnPkt;
    }
    else if (PTPV2_FSM_MODE_BC == ulFsmMode)
    {
        pstPortInfo->pfPtpStartFunc = PTPV2_BcStart;
        pstPortInfo->pfPtpStopFunc = PTPV2_Stop;
        pstPortInfo->pfPtpBuildAnnPktFunc = PTPV2_BC_MasterBuildAnnPkt;
        pstPortInfo->pfPtpSndAnnPktFunc = PTPV2_OverMacSndAnnPkt;
    }
    else
    {
        pstPortInfo->pfPtpStartFunc = NULL;
        pstPortInfo->pfPtpStopFunc = NULL;
        pstPortInfo->pfPtpBuildAnnPktFunc = NULL;
        pstPortInfo->pfPtpSndAnnPktFunc = NULL;
    }

    /*接口可以使用1588 ，需要加入多播组中*/
    if (TCPIP_PTP_CLOCK_IEEE8023_MODE == pstPortInfo->pstSubPortInfo->ucCastMode)/*加入多播组*/
    {
        IFNET_S *pstIfnet = NULL;
        UCHAR aucMacMask[MACADDRLEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

        pstIfnet = IF_GetIfByIndex(pstPortInfo->ulIfIndex);
        if (NULL != pstIfnet)
        {
            (VOID)IF_PhyIoCtrl(pstIfnet, (ULONG)PHY_JOINMULTI, (CHAR *)g_szMacPTPV2_E2E);
            (VOID)PPI_MultiMac_Update(pstPortInfo->ulIfIndex, PPI_MULTICMAC_ADD, (UCHAR*)g_szMacPTPV2_E2E, (UCHAR*)aucMacMask);
        }
    }

    return TCPIP_PTP_OK;
}


/*******************************************************************************
*    Func Name: PTPV2_GetForeignMasterByPortId
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description: 根据报文的port id 查找foreign master
*        Input: PTPV2_MSGHEADER_S* pstMsgHeader:
*               PTPV2_FOREIGN_MASTER_S** ppstForeMaster:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GetForeignMasterByPortId(PTPV2_MSGHEADER_S* pstMsgHeader,
                           PTPV2_FOREIGN_MASTER_S** ppstForeMaster)
{
    PTPV2_FOREIGN_MASTER_S* pstIter = NULL;
    PTPV2_FOREIGN_MASTER_S* pstIterForeMaster = NULL;
    LONG lCmp = -1L;
    ULONG ulRet = TCPIP_PTP_ERR;

    if (NULL == pstMsgHeader || NULL == ppstForeMaster)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    DLL_Scan(&g_GlobalForeignMasterList, pstIter, PTPV2_FOREIGN_MASTER_S*)
    {
        /*指针重新指到结构体起始位置*/
        pstIterForeMaster = (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter));
        
        (VOID)VOS_Mem_Cmp((VOID *)(pstMsgHeader->stSourcePortIdentity.szClockId), (VOID *)(pstIterForeMaster->szForeignMasterPortId.szClockId), 
                          TCPIP_PTP_CLOCK_ID_LEN, &lCmp);
        if (0 == lCmp && (VOS_NTOHS(pstMsgHeader->stSourcePortIdentity.usPortNumber) == pstIterForeMaster->szForeignMasterPortId.usPortNumber))
        {
            *ppstForeMaster = pstIterForeMaster;
            ulRet = TCPIP_PTP_OK;
            break;
        }
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_UpdateParentDS
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 更新parent DS
*        Input: PTPV2_FOREIGN_MASTER_S *pstSelectMaster:
*               ULONG *pulChangeField:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_UpdateParentDS(PTPV2_FOREIGN_MASTER_S *pstSelectMaster, ULONG *pulChangeField)
{
    TCPIP_PTP_PARENT_DS_S *pstParentDS = &(g_pstPtpGlobalInfo->stParentDs);
    /*当前选中源的参数*/
    BOOL_T      bCurUtcOffsetValid = FALSE;
    SHORT       sCurUtcOffset = 0;
    BOOL_T      bCurLeap59 = FALSE;
    BOOL_T      bCurLeap61 = FALSE;
    UCHAR       ucCurBestClassFlag = PTPV2_NOT_PRI_CLASS;
    ULONG       ulCurClockClass = 0;

    /*获取当前源中的UTC参数*/
    sCurUtcOffset = pstSelectMaster->sCurrentUtcOffset;
    bCurUtcOffsetValid = (pstSelectMaster->ucFlagField[1] >> 2) & 0x01;
    bCurLeap59 = (pstSelectMaster->ucFlagField[1] >> 1) & 0x01;
    bCurLeap61 = (pstSelectMaster->ucFlagField[1]) & 0x01;
    ulCurClockClass = pstSelectMaster->stGrandmasterClockQuality.ucClockClass;

    /*当前是否是优选源*/
    if (PTPV2_IS_PRI_CLOCK_SOURCE(pstSelectMaster->stGrandmasterClockQuality.ucClockClass))
    {
        ucCurBestClassFlag = PTPV2_PRI_CLASS;
    }
    else
    {
        ucCurBestClassFlag = PTPV2_NOT_PRI_CLASS;
    }

    /*获取变化参数的标志*/
    if (NULL != pulChangeField)
    {
        /*若源的UTC参数发生变化，或优选源状态发生变化，则下发PPI*/
        if ((sCurUtcOffset != g_pstPtpGlobalInfo->stParentDs.sCurrentUtcOffset)
            || (bCurLeap59 != g_pstPtpGlobalInfo->stParentDs.bLeap59)
            || (bCurLeap61 != g_pstPtpGlobalInfo->stParentDs.bLeap61)
            || (bCurUtcOffsetValid != g_pstPtpGlobalInfo->stParentDs.bCurrentUtcOffsetValid))
        {
            *pulChangeField |= TCPIP_PTP_PARA_CHANGE_FIELD_UTC;

        }
        
        if (ucCurBestClassFlag != g_pstPtpGlobalInfo->stParentDs.ucBestClassFlag
            || ulCurClockClass != g_pstPtpGlobalInfo->stParentDs.stParentClockQA.ucClockClass)
        {
            *pulChangeField |= TCPIP_PTP_PARA_CHANGE_FIELD_BMC;
        }
    }

    /*更新ParentDS*/
    pstParentDS->sCurrentUtcOffset = sCurUtcOffset;
    pstParentDS->bCurrentUtcOffsetValid = bCurUtcOffsetValid;
    pstParentDS->bLeap59 = bCurLeap59;
    pstParentDS->bLeap61 = bCurLeap61;
    pstParentDS->ucBestClassFlag = ucCurBestClassFlag;
    pstParentDS->stParentClockQA.ucClockClass = ulCurClockClass;

    (VOID)TCPIP_Mem_Copy((VOID*)(pstParentDS->szGrandMasterId),TCPIP_PTP_CLOCK_ID_LEN,
        (VOID*)(pstSelectMaster->szGrandMasterId), TCPIP_PTP_CLOCK_ID_LEN);

    (VOID)TCPIP_Mem_Copy((VOID*)&(pstParentDS->stParentPortId), sizeof(TCPIP_PTP_PORT_ID_S),
        (VOID*)&(pstSelectMaster->szForeignMasterPortId), sizeof(TCPIP_PTP_PORT_ID_S));

    (VOID)TCPIP_Mem_Copy((VOID*)&(pstParentDS->stParentAddr),sizeof(TCPIP_PTP_PORT_ADDR_S),
        (VOID*)&(pstSelectMaster->stForeignMasterPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S));

    pstParentDS->stParentClockQA.ucClockAccuracy = pstSelectMaster->stGrandmasterClockQuality.ucClockAccuracy;
    pstParentDS->stParentClockQA.usOffsetScaledLogVariance = pstSelectMaster->stGrandmasterClockQuality.usOffsetScaledLogVariance;

    pstParentDS->ucGrandmasterPriority1 = pstSelectMaster->ucGrandmasterPriority1;
    pstParentDS->ucGrandmasterPriority2 = pstSelectMaster->ucGrandmasterPriority2;

    /* 时钟源 :从上一级时钟获取*/
    pstParentDS->ucTimeSource = pstSelectMaster->ucTimeSource;
    pstParentDS->cLogMAnnInterval = pstSelectMaster->cLogMAnnInterval;
    pstParentDS->usStepsRemoved = pstSelectMaster->usStepsRemoved;

    pstParentDS->bTimeTraceable = (pstSelectMaster->ucFlagField[1] >> 4) & 0x01;
    pstParentDS->bFrequencyTraceable = (pstSelectMaster->ucFlagField[1] >> 5) & 0x01;
    pstParentDS->bPtpTimescale = (pstSelectMaster->ucFlagField[1] >> 3) & 0x01;

    return;
}

/*******************************************************************************
*    Func Name: PTPV2_PPI_LogMsg
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: PPI下发日志记录
*        Input: ULONG ulRet:
*               USHORT usPtpPortNumber:
*               ULONG ulPtpPpiCmd:
*               VOID *pstPpiInfo:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_PPI_LogMsg(ULONG ulRet, USHORT usPtpPortNumber, ULONG ulPtpPpiCmd, VOID *pstPpiInfo)
{
    TCPIP_PTP_SLAVE_PPI_S *pstPpiData = (TCPIP_PTP_SLAVE_PPI_S *)pstPpiInfo;
    INT32 i32Offset = 0;

    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_PPI)
    {
        CHAR szBuf[LEN_512] = {0};

        i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P5("\r\n---------------PPI Info----------------"
                               "\nPPI CMD: %u\nTwoStep: %u\nChangeField: %u\nIfIndex: %u\nLocalPortNo: %u", 
                               ulPtpPpiCmd,
                               pstPpiData->bTwoStep, pstPpiData->ulChangeField, 
                               pstPpiData->ulIfIndex, pstPpiData->usLocalPortNo));
        i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P9("\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x",
                                "GrandMaster Clock Identity",
                                pstPpiData->stParentDS.szGrandMasterId[0],
                                pstPpiData->stParentDS.szGrandMasterId[1],
                                pstPpiData->stParentDS.szGrandMasterId[2],
                                pstPpiData->stParentDS.szGrandMasterId[3],
                                pstPpiData->stParentDS.szGrandMasterId[4],
                                pstPpiData->stParentDS.szGrandMasterId[5],
                                pstPpiData->stParentDS.szGrandMasterId[6],
                                pstPpiData->stParentDS.szGrandMasterId[7]));
        (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P11("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x \r\n %30s : %u",
                                "Parent Clock Identity",
                                pstPpiData->stParentDS.stParentPortId.szClockId[0],
                                pstPpiData->stParentDS.stParentPortId.szClockId[1],
                                pstPpiData->stParentDS.stParentPortId.szClockId[2],
                                pstPpiData->stParentDS.stParentPortId.szClockId[3],
                                pstPpiData->stParentDS.stParentPortId.szClockId[4],
                                pstPpiData->stParentDS.stParentPortId.szClockId[5],
                                pstPpiData->stParentDS.stParentPortId.szClockId[6],
                                pstPpiData->stParentDS.stParentPortId.szClockId[7],
                                "Parent PortNumber",
                                pstPpiData->stParentDS.stParentPortId.usPortNumber));

        TCPIP_InfoOutput(szBuf);

        i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512,P6("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                    "Parent ClockClass", pstPpiData->stParentDS.stParentClockQA.ucClockClass,
                    "Parent ClockAccuracy", pstPpiData->stParentDS.stParentClockQA.ucClockAccuracy,
                    "Parent OffsetScaledLogVariance", pstPpiData->stParentDS.stParentClockQA.usOffsetScaledLogVariance));
        i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P4("\r\n %30s : %d \r\n %30s : %u", 
                    "GrandmasterPriority1", pstPpiData->stParentDS.ucGrandmasterPriority1,
                    "GrandmasterPriority2", pstPpiData->stParentDS.ucGrandmasterPriority2));
        (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P8("\r\n %30s : %d \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                    "Parent CurrentUtcOffset", pstPpiData->stParentDS.sCurrentUtcOffset,
                    "Parent CurrentUtcOffsetValid", pstPpiData->stParentDS.bCurrentUtcOffsetValid,
                    "Parent Leap59", pstPpiData->stParentDS.bLeap59,
                    "Parent Leap61", pstPpiData->stParentDS.bLeap61));

        TCPIP_InfoOutput(szBuf);

        i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                    "TimeTraceable", pstPpiData->stParentDS.bTimeTraceable,
                    "FrequencyTraceable", pstPpiData->stParentDS.bFrequencyTraceable,
                    "TimeScale", pstPpiData->stParentDS.bTimeScale,
                    "PtpTimescale", pstPpiData->stParentDS.bPtpTimescale));
        (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P6("\r\n %30s : %u \r\n %30s : %d \r\n %30s : %d", 
                    "TimeSource", pstPpiData->stParentDS.ucTimeSource,
                    "LogMAnnInterval", pstPpiData->stParentDS.cLogMAnnInterval,
                    "BestClassFlag", pstPpiData->stParentDS.ucBestClassFlag));
        
        TCPIP_InfoOutput(szBuf);
    }
    return;
}

/*******************************************************************************
*    Func Name: PTPV2_WarningRemoveProc
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 告警解除操作
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_WarningRemoveProc()
{
    /*如果上报了告警，需要告警消除*/
    if (NULL != g_pfPtpV2WarnOutput
        && g_pstPtpGlobalInfo->usWarningRecord & TCPIP_PTP_WARN_BMC_FAIL_FLAG)
    {
        /*上报告警解除*/
        TCPIP_PTP_WARN_PARAM_S  stPtpWarnPara = {0};

        stPtpWarnPara.ucWarnType = TCPIP_PTP_WARN_BMC_FAIL;
        stPtpWarnPara.ucWarnState = TCPIP_PTP_WARNING_END;

        (VOID)g_pfPtpV2WarnOutput(&stPtpWarnPara);
        g_pstPtpGlobalInfo->usWarningRecord &= ~TCPIP_PTP_WARN_BMC_FAIL_FLAG;
    }

    /*删除告警定时器，防止误报*/
    (VOID)PTPV2_DeleteWarningTimer();

    return;
}

/*******************************************************************************
*    Func Name: PTPV2_HaveParent
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 判断是否存在FOREIGN_MASTER
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
ULONG PTPV2_HaveParent()
{
    /* Modified by wuling201943, 消除fortify告警, 2014/9/9   问题单号:DTS2014090901965 */
    return (ULONG)(g_pstBmcEbest ? PTPV2_YES: PTPV2_NO);
    /*End of Modified by wuling201943, 2014/9/9   问题单号:DTS2014090901965 */
}

/*******************************************************************************
*    Func Name: PTPV2_GetPortRoleByFsmState
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 根据状态机状态获取端口角色
*        Input: UCHAR ucPortFsmState:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
UCHAR PTPV2_GetPortRoleByFsmState(UCHAR ucPortFsmState)
{
    UCHAR ucPortRole = TCPIP_PTP_PORT_ROLE_UNDEFINED;
    switch (ucPortFsmState)
    {
        case PTPV2_PORT_FSM_LISTENING:
            ucPortRole = TCPIP_PTP_PORT_ROLE_MASTER;
            break;
            
        case PTPV2_PORT_FSM_MASTER:
            ucPortRole = TCPIP_PTP_PORT_ROLE_MASTER;
            break;
        case PTPV2_PORT_FSM_SLAVE:
            ucPortRole = TCPIP_PTP_PORT_ROLE_SLAVE;
            break;

        case PTPV2_PORT_FSM_PASSIVE:
            ucPortRole = TCPIP_PTP_PORT_ROLE_PASSIVE;
            break;

        default:
            break;        
    }
    return ucPortRole;
}
 
/*******************************************************************************
*    Func Name: PTPV2_Set_FsmState
* Date Created: 2014-12-22
*       Author: guojianjun178934
*  Description: 设置端口状态机状态
*        Input: PTPV2_PORT_SUB_INFO_S *pstSubPortInfo:
*               UCHAR ucPtpPortFsmState:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_Set_FsmState(PTPV2_PORT_SUB_INFO_S *pstSubPortInfo, UCHAR ucPtpPortFsmState) 
{    
    if (pstSubPortInfo->ucPtpPortFsmState == ucPtpPortFsmState)
    {
        return;
    }
    /*状态机Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
    {
        CHAR szInfo[LEN_64] = {0};
        (VOID)TCPIP_SNPRINTF0(szInfo, LEN_64, P3("\r\n PTPV2 FSM: PortNum(%u), CurState(%u) ,NextState(%u). \r\n", 
                                    pstSubPortInfo->usPortNo, pstSubPortInfo->ucPtpPortFsmState, ucPtpPortFsmState));
        TCPIP_InfoOutput(szInfo);
    }
    
    pstSubPortInfo->ucPtpPortFsmState = ucPtpPortFsmState;
    return;
}

/*******************************************************************************
*    Func Name: PTPV2_Set_PortRole
* Date Created: 2014-12-16
*       Author: guojianjun178934
*  Description: 设置端口角色
*        Input: PTPV2_PORT_SUB_INFO_S *pstSubPortInfo:
*               UCHAR ucPtpPortRole:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-16   guojianjun178934        Create
*
*******************************************************************************/
VOID PTPV2_Set_PortRole(PTPV2_PORT_SUB_INFO_S *pstSubPortInfo, UCHAR ucPtpPortRole)
{
    if (pstSubPortInfo->ucPtpPortRole == ucPtpPortRole)
    {
        return;
    }
    /*角色Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
    {
        CHAR szInfo[LEN_64] = {0};
        (VOID)TCPIP_SNPRINTF0(szInfo, LEN_64, P3("\r\n PTPV2 Role: PortNum(%u), CurRole(%u) ,NextRole(%u). \r\n", 
                                    pstSubPortInfo->usPortNo, pstSubPortInfo->ucPtpPortRole, ucPtpPortRole));
        TCPIP_InfoOutput(szInfo);
    }
    
    pstSubPortInfo->ucPtpPortRole = ucPtpPortRole;
    return;
}
#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
