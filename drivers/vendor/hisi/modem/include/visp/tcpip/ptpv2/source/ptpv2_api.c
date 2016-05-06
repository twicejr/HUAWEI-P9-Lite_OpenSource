/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_api.c
*
*  Project Code:
*   Module Name: PTPV2 api
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

#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_basefun.h"

/*******************************************************************************
*    Func Name: TCPIP_PTP_Init
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2初始化
*  Description: PTPV2初始化，创建定时器、报文、控制消息队列，创建PTP任务，分配端口资源
*        Input: ulPtpClockType: PTP时钟类型，OC或者BC
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Init(ULONG ulPtpClockType)
{
    ULONG ulRet = TCPIP_PTP_OK;

    ulRet = PTPV2_Global_Init(ulPtpClockType);
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EA, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_Init ClockType = %u, return code = %#x.\r\n",
        ulPtpClockType, ulRet, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_UnInit
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2去初始化
*  Description: PTPV2去初始化，写事件给PTP主任务，并等待主任务卸载完成
*        Input: 
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_UnInit()
{
    ULONG ulRet = TCPIP_PTP_OK;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPV2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    g_pfETH_PTPV2_HOOK = NULL; /*停止接收报文*/

    PTPV2_WarningRemoveProc();/*告警解除操作*/

    /*通知PTPV2主任务自动消亡*/
    ulRet = VOS_Ev_Write(g_ulPtpV2TaskId, PTPV2_EVT_TASK_OVER_Q);
    if (TCPIP_PTP_OK != ulRet)
    {
        PTPV2_UnLock();
        goto EXIT_LABEL;
    }

    PTPV2_UnLock();

    /*创建同步信号量，等待PTPV2任务消亡*/
    ulRet = TCPIP_CreateSm(NULL, 0, &g_ulSynsemId);
    if (TCPIP_PTP_OK == ulRet)
    {
        ulRet = TCPIP_SmP_Wait(g_ulSynsemId, 1000);/*等待1秒*/
        if (TCPIP_PTP_OK != ulRet)
        {
            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2A86, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
                   "TCPIP PTPv2 LOG: TCPIP_PTP_UnInit SmP wait error! return code = %#x.\r\n", 
                   ulRet, 0, 0, 0);

            ulRet = TCPIP_PTP_ERR_SMP_TIMEOUT;
        }

        (VOID)TCPIP_DeleteMutex(g_ulSynsemId);
    }

    g_ulSynsemId = 0;

EXIT_LABEL:
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EB, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_UnInit , return code = %#x.\r\n",
         ulRet, 0, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_AddPort
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 创建可用的PTP端口
*  Description: 创建可用的PTP端口
*        Input: ULONG ulIfIndex: 接口索引
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 添加的PTP地址，目前不使用，用于将来扩展
*       Output: USHORT* pusPtpPortNo:返回的PTP端口号
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1.目前仅支持Overmac，基于接口配置不需要指定physical地址
*               2.OC下，返回的端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_AddPort(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr,
                        USHORT* pusPtpPortNo)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_PORT_S*  pstPortTemp = NULL;
    PTPV2_PORT_S*  pstAdd = NULL;
    ULONG ulFreeLockFlag = PTPV2_NO;
    USHORT usPortNo = 0;

    if (NULL == pusPtpPortNo)
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    /*PTPV2没有初始化*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /*不支持的接口类型*/
    ulRet =  PTPV2_CheckIfIndex(ulIfIndex);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*是否已经满规格*/
    ulRet = PTPV2_CheckPortNoUpToMax();
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*先判断树是否存在，不存在则添加*/
    ulRet = PTPV2_GetPortInfoByIntf(ulIfIndex, pstPtpAddr, &pstPortTemp);
    if (TCPIP_PTP_OK == ulRet)
    {
        if (NULL == pstPortTemp || NULL == pstPortTemp->pstSubPortInfo)
        {
            ulRet = TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        }
        else
        {
            *pusPtpPortNo = pstPortTemp->pstSubPortInfo->usPortNo;
            usPortNo = *pusPtpPortNo;
        }

        goto EXIT_LABEL;
    }

    /*添加新的树节点*/
    ulRet = PTPV2_AddPortInfo(ulIfIndex, pstPtpAddr, &pstAdd);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*PTP 端口号参数初始化*/
    (VOID)PTPV2_InitPortInfo(pstAdd);

    *pusPtpPortNo = pstAdd->pstSubPortInfo->usPortNo;
    usPortNo = *pusPtpPortNo;
EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EC, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_AddPort ulIfIndex = %u, usPortNo = %u, return code = %#x.\r\n",
        ulIfIndex, usPortNo, ulRet,  0);

    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_DelPort
* Date Created: 2014-03-21
*       Author: luogaowei & dutianyi
*      Purpose: 删除指定的PTP端口
*  Description: 删除指定的PTP端口
*        Input: USHORT usPtpPortNo:PTP端口号
*               ULONG ulIfIndex:接口索引
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr:PTP地址
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1. BC只需要指定的端口号即可，后两个参数传任意值即可
*               2. OC由于共享的是端口号1，需要指定接口索引(后续也可能需要指定地址)
*               3. pstPtpAddr仅为未来扩展预留，在OC下，同一个接口不同的地址可以配置PTP应用
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-21   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_DelPort(USHORT usPtpPortNo, ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPV2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    if (PTPV2_CLOCK_TYPE_OC == PTPV2_GetClockType())
    {
        ulRet = PTPV2_DelOCPortInfoEntry(usPtpPortNo, ulIfIndex, pstPtpAddr);
    }
    else
    {
        ulRet = PTPV2_DelBCPortInfoEntry(usPtpPortNo);
    }

EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27ED, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_DelPort  usPtpPortNo = %u, return code = %#x.\r\n",
         usPtpPortNo, ulRet,  0, 0);

    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_Start
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 启动PTP的功能
*  Description: 启动PTP的功能，启动指定端口的发送定时器
*        Input: USHORT usPtpPortNo: 创建的PTP端口号
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 地址信息目前不使用，将来扩展
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1.参数pstPtpAddr暂时不使用，用于将来扩展支持层3单播功能
*               2.OC下仅有一个端口，启动后该端口所有的物理口都会发送报文
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Start(USHORT usPtpPortNo, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    PTPV2_PORT_S* pstPortInfo = NULL;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    if (NULL == pstPtpAddr)
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }


    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /* 端口号是否在支持的范围内 */
    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* 判断端口是否有效 */
    ulRet = PTPV2_GetPortInfoByPort(usPtpPortNo, &pstPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* 判断端口是否已经启动 */
    if (PTPV2_YES == pstPortInfo->pstSubPortInfo->ucWorkState)
    {
        goto EXIT_LABEL;
    }

    /*已经存在则启动*/
    (VOID)pstPortInfo->pfPtpStartFunc(pstPortInfo, pstPtpAddr);/*启动PTP*/

EXIT_LABEL:

    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EE, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_Start  usPtpPortNo = %u , return code = %#x.\r\n",
        usPtpPortNo, ulRet, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockIdentity
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 配置PTP时钟ID
*  Description: 配置PTP时钟ID
*        Input: TCPIP_PTP_CLOCK_ID_SZ szClockID:PTP时钟ID
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 参数有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockIdentity(TCPIP_PTP_CLOCK_ID_SZ szClockID)
{
    CHAR  szClockInfo[LEN_64] = {0};
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    
    if (NULL == szClockID)
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_SNPRINTF0(szClockInfo, LEN_64, P8("%02x%02x%02x%02x%02x%02x%02x%02x\r\n",
                       szClockID[0],
                       szClockID[1],
                       szClockID[2],
                       szClockID[3],
                       szClockID[4],
                       szClockID[5],
                       szClockID[6],
                       szClockID[7]));
    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Copy((VOID*)g_pstPtpGlobalInfo->szClockId, sizeof(TCPIP_PTP_CLOCK_ID_SZ),(VOID*)szClockID, sizeof(TCPIP_PTP_CLOCK_ID_SZ));
    PTPV2_UpdateVirtualD0();
    
EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EF, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetClockIdentity  return code = %#x.\r\n",
        ulRet, 0, 0, 0);

    TCPIP_LOG_VARLEN(RUN_LOG_VISP_33D3, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                     "TCPIP PTPV2 LOG: TCPIP_PTP_SetClockIdentity  szClockID = %s \r\n",
                     szClockInfo);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockQuality
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 设置时钟源质量
*  Description: 设置时钟源质量
*        Input: TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality:时钟源质量
*                 pstPtpCfgClockQuality->ucClockClass:时钟类别，默认0
*                 pstPtpCfgClockQuality->ucClockAccuracy: 时钟精度，默认0，范围0x20-0x32
*                 pstPtpCfgClockQuality->usOffsetScaledLogVariance:时钟稳定度，默认0
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 时钟等级/时钟稳定度的有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockQuality(TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    TCPIP_PTP_CLOCK_QA_S  stClockForLog = {0};

    if (NULL == pstPtpCfgClockQuality)/*参数有效性判断*/
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    /*仅对时间精度判断有效性，其他由产品决定*/
    if ((TCPIP_PTP_CLOCK_ACCURACY_25NS > pstPtpCfgClockQuality->ucClockAccuracy) || (TCPIP_PTP_CLOCK_ACCURACY_M10S < pstPtpCfgClockQuality->ucClockAccuracy))
    {
        ulRet = TCPIP_PTP_ERR_CLOCK_ACCURACY;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Copy((VOID*)&stClockForLog, sizeof(TCPIP_PTP_CLOCK_QA_S),(VOID*)pstPtpCfgClockQuality, sizeof(TCPIP_PTP_CLOCK_QA_S));
    (VOID)TCPIP_Mem_Copy((VOID*)&g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa,sizeof(TCPIP_PTP_CLOCK_QA_S),
        (VOID*)pstPtpCfgClockQuality, sizeof(TCPIP_PTP_CLOCK_QA_S));

EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F0, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPV2 LOG: TCPIP_PTP_SetClockQuality, ucClockClass = %u, ucClockAccuracy = %u, \
        usOffsetScaledLogVariance = %u ,return code =%u.\r\n",
        (ULONG)(stClockForLog.ucClockClass),
        (ULONG)(stClockForLog.ucClockAccuracy),
        (ULONG)(stClockForLog.usOffsetScaledLogVariance),
        (ULONG)ulRet);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetUtcProperties
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi
*      Purpose: OC matser下设置UTC
*  Description: OC matser下设置UTC
*        Input: SHORT sCurrentUtcOffset:UTC偏移量
*               BOOL_T bLeap61:Leap61
*               BOOL_T bLeap59:Leap59
*               BOOL_T bCurrentUtcOffsetValid:UTC偏移量有效性
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1.Leap61和Leap59不能同时为真
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetUtcProperties(SHORT sCurrentUtcOffset, BOOL_T bLeap61, BOOL_T bLeap59, 
                                    BOOL_T bCurrentUtcOffsetValid)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    /* leap61,leap59不可能同时为真 */
    if (((BOOL_TRUE == bLeap61) && (BOOL_TRUE == bLeap59))
        || (BOOL_TRUE != bCurrentUtcOffsetValid && BOOL_FALSE != bCurrentUtcOffsetValid))
    {
        ulRet = TCPIP_PTP_ERR_INVALID_PARA;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    /* 赋值当前utc时间偏移 */
    g_pstPtpGlobalInfo->stCfgDefaultDs.sCurrentUtcOffset = sCurrentUtcOffset;

    /* 赋值当前UTC天的最后一分钟是否含61秒的属性 */
    g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap61 = bLeap61;

    /* 赋值当前UTC天的最后一分钟是否含59秒的属性 */
    g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap59 = bLeap59;

    /*  赋值当前时间偏移所否有效 */
    g_pstPtpGlobalInfo->stCfgDefaultDs.bCurrentUtcOffsetValid = bCurrentUtcOffsetValid;

    PTPV2_UpdateVirtualD0();

EXIT_LABEL:

    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F1, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetUtcProperties  sCurrentUtcOffset = %d , bLeap61 = %u, bLeap59 = %u,"
        " bCurrentUtcOffsetValid = %u.\r\n",
        sCurrentUtcOffset, bLeap61, bLeap59, bCurrentUtcOffsetValid);
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F2, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetUtcProperties  return code = %#x.\r\n",
        ulRet, 0, 0 ,0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetPriClassGroup
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: 设置PTP优选源
*  Description: 设置PTP优选源，选中与优选源一致的源进行PPI下发时会携带优选源标记
*        Input: UCHAR ucClass0
*               UCHAR ucClass1
*               UCHAR ucClass2
*               UCHAR ucClass3
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 参数有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetPriClassGroup(UCHAR ucClass0, UCHAR ucClass1, UCHAR ucClass2, UCHAR ucClass3)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass0 = ucClass0;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass1 = ucClass1;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass2 = ucClass2;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass3 = ucClass3;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriClassFlag = PTPV2_YES;/*标记配置了优选源*/

EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F3, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPV2 LOG: TCPIP_PTP_SetPriClassGroup, ucClass0 = %u, ucClass1 = %u, \
        ucClass2 = %u, ucClass3 = %u.\r\n",
        ucClass0, ucClass1, ucClass2, ucClass3);

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F4, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPV2 LOG: TCPIP_PTP_SetPriClassGroup, return code = %#x.\r\n",
        ulRet, 0, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetDomain
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 设置时钟设备的域参数
*  Description: 设置时钟设备的域参数，PTP通信仅在同一个域的时钟间进行
*        Input: UCHAR ucDomainNumber:时钟设备域
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 参数有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetDomain(UCHAR ucDomainNumber)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    if (NULL == g_pstPtpGlobalInfo)/*指针为空，表示数据异常*/
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    g_pstPtpGlobalInfo->stCfgDefaultDs.ucDomainNumber = ucDomainNumber;

EXIT_LABEL:
    if (ulFreeLockFlag == PTPV2_YES)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F7, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetDomain  ucDomainNumber = %u , return code = %#x.\r\n",
        ucDomainNumber, ulRet, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnInterval
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 设置端口的Ann报文消息间隔(指数形式)
*  Description: 设置端口的Ann报文消息间隔(指数形式)
*        Input: USHORT usPtpPortNo:时钟端口号
*               CHAR cLogAnnInterval:时钟端口LogAnnounceInterval值, 默认1，范围0--4
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: OC下端口号只能为1，时间间隔由产品保证有效性
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnInterval(USHORT usPtpPortNo, CHAR cLogAnnInterval)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    PTPV2_PORT_S* pstPortInfo = NULL;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /* 端口号是否在支持的范围内 */
    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* 判断端口是否有效 */
    ulRet = PTPV2_GetPortInfoByPort(usPtpPortNo, &pstPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    /*设置ANNOUNCE消息发送间隔*/
    pstPortInfo->pstSubPortInfo->stPortAnnInfo.clogAnnounceInterval = cLogAnnInterval;

EXIT_LABEL:
    if (ulFreeLockFlag == PTPV2_YES)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F5, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetAnnInterval  usPtpPortNo = %u ,cLogAnnInterval = %d, return code = %#x.\r\n",
        usPtpPortNo, cLogAnnInterval, ulRet,  0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnRcvTimeoutNum
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: 设置announce报文接收超时最大次数
*  Description: 设置announce报文接收超时最大次数，超过该次数后会删除端口上对应的ForeignMaster
*        Input: USHORT usPtpPortNo:PTP端口号
*               UCHAR ucReceiptTimeout:接收超时最大次数，接收超时次数的默认值为3，范围2-10
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: OC下端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnRcvTimeoutNum(USHORT usPtpPortNo, UCHAR ucAnnRcvTimeoutNum)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    PTPV2_PORT_S* pstPortInfo = NULL;

    /*超时范围为2-255*/
    if (TCPPI_PTP_MIN_ANN_RCV_TIMEOUT > ucAnnRcvTimeoutNum)
    {
        ulRet = TCPIP_PTP_ERR_INVALID_PARA;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2没有初始化*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /* 端口号是否在支持的范围内 */
    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* 判断端口是否有效 */
    ulRet = PTPV2_GetPortInfoByPort(usPtpPortNo, &pstPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*数据有效性检查*/
    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    /*设置ANNOUNCE 接收次数*/
    pstPortInfo->pstSubPortInfo->stPortAnnInfo.ucAnnRcvTimeoutNum = ucAnnRcvTimeoutNum;

EXIT_LABEL:
    if (ulFreeLockFlag == PTPV2_YES)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F6, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetAnnRcvTimeoutNum  usPtpPortNo = %u ,ucAnnRcvTimeoutNum = %d, return code = %#x.\r\n",
        usPtpPortNo, ucAnnRcvTimeoutNum, ulRet,  0);
    return ulRet;
}


ULONG TCPIP_PTP_SetPtsf(ULONG ulVrfIndex, TCPIP_PTP_PORT_ADDR_S* pstForeignMasterAddr, ULONG ulPtsfType,ULONG ulPTSFValue)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_FOREIGN_MASTER_S *pstForeignMaster = NULL;
    CHAR  szMacAddr[LEN_32] = {0};
    
    if (NULL == pstForeignMasterAddr)
    {
        ulRet = TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulRet = PTPV2_GetForeignMasterByAddr(pstForeignMasterAddr, &pstForeignMaster);
    if (TCPIP_PTP_OK != ulRet)
    {
        PTPV2_UnLock();
        goto EXIT_LABEL;
    }

    switch ( ulPtsfType ) 
    {
        case TCPIP_PTP_PTSF_SYNC:
        {
            pstForeignMaster->ulPtsfSync = ulPTSFValue;
            break;
        }
        
        default:
        {
            ulRet = TCPIP_PTP_ERR_INVALID_PARA;
            break;
        }
    }
    
    PTPV2_UnLock();

    /*记录日志*/
    if ((TCPIP_PTP_PROTOCAL_IEEE_802 == pstForeignMasterAddr->usNetworkProtocol) && 
        (PTPV2_MACADDRLEN == pstForeignMasterAddr->usAddressLength))
    {
        (VOID)TCPIP_SNPRINTF0(szMacAddr, LEN_32, P6("%02x%02x.%02x%02x.%02x%02x",
                pstForeignMasterAddr->unAddr.ucMacAddr[0],pstForeignMasterAddr->unAddr.ucMacAddr[1],
                pstForeignMasterAddr->unAddr.ucMacAddr[2],pstForeignMasterAddr->unAddr.ucMacAddr[3],
                pstForeignMasterAddr->unAddr.ucMacAddr[4],pstForeignMasterAddr->unAddr.ucMacAddr[5]));
        TCPIP_LOG_VARLEN(RUN_LOG_VISP_0002, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
            "TCPIP PTPv2 LOG: TCPIP_PTP_SetPtsf for OverMac Master Addr: %s\r\n",szMacAddr);
    }
    
EXIT_LABEL:

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_0001, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetPtsf ulVrfIndex = %d ,ulPtsfType = %d, ulPTSFValue = %d, return code = %#x.\r\n",
        ulVrfIndex, ulPtsfType, ulPTSFValue, ulRet);
    return ulRet;

/*    TCPIP_LOG_VARLEN(RUN_LOG_VISP_0001, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                     "TCPIP PTPV2 LOG: TCPIP_PTP_SetClockIdentity  szClockID = %s \r\n",
                     szClockInfo);
*/                     

}

#ifdef __cplusplus
}
#endif
