

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "Fc.h"
#include "FcInterface.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "TTFComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e534*/
#define    THIS_FILE_ID        PS_FILE_ID_FLOW_CTRL_C


/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
   函数声明
*****************************************************************************/


/*****************************************************************************
   全局变量定义
*****************************************************************************/

/* 流控策略实体 */
FC_POLICY_STRU                          g_astFcPolicy[FC_PRIVATE_POLICY_ID_BUTT];

/* 流控点管理实体 */
FC_POINT_MGR_STRU                       g_stFcPointMgr;


/* 流控配置实体 */
FC_CFG_STRU                             g_stFcCfg;

/* 流控内部策略表 */
FC_PRIVATE_POLICY_ID_ENUM_UINT8         g_aenPrivatePolicyTbl[FC_MODEM_ID_NUM][FC_POLICY_ID_BUTT] =
{
    {
        FC_PRIVATE_POLICY_ID_MEM_MODEM_0,
        FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0,
        FC_PRIVATE_POLICY_ID_CDS_MODEM_0,
        FC_PRIVATE_POLICY_ID_CST_MODEM_0,
        FC_PRIVATE_POLICY_ID_GPRS_MODEM_0,
        FC_PRIVATE_POLICY_ID_TMP_MODEM_0,
        FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0,
        FC_PRIVATE_POLICY_ID_CDMA_MODEM_0
    },
    {
        FC_PRIVATE_POLICY_ID_MEM_MODEM_1,
        FC_PRIVATE_POLICY_ID_CPU_A_MODEM_1,
        FC_PRIVATE_POLICY_ID_CDS_MODEM_1,
        FC_PRIVATE_POLICY_ID_CST_MODEM_1,
        FC_PRIVATE_POLICY_ID_GPRS_MODEM_1,
        FC_PRIVATE_POLICY_ID_TMP_MODEM_1,
        FC_PRIVATE_POLICY_ID_CPU_C_MODEM_1,
        FC_PRIVATE_POLICY_ID_CDMA_MODEM_1,
    }
};

VOS_UINT32                              g_ulFcDebugLevel = (VOS_UINT32)PS_PRINT_WARNING;

/******************************************************************************
   6 函数实现
******************************************************************************/
/*lint -save -e958 */
VOS_VOID     FC_LOG
(
    VOS_UINT32          ulLevel,
    const VOS_CHAR     *pcString
)
{
    #ifdef __FC_RELEASE__
    /*lint -e64*/
    TTF_LOG(UEPS_PID_FLOWCTRL, DIAG_MODE_COMM, ulLevel, pcString);
    /*lint +e64*/
    #else
    if ( g_ulFcDebugLevel >=  ulLevel)
    {
        (VOS_VOID)Print(pcString);
    }
    #endif

    return;
}

VOS_VOID     FC_LOG1
(
    VOS_UINT32            ulLevel,
    const VOS_CHAR       *pcString,
    VOS_INT32             lPara1
)
{
    #ifdef __FC_RELEASE__
    /*lint -e64*/
    TTF_LOG1(UEPS_PID_FLOWCTRL, DIAG_MODE_COMM,
           ulLevel, pcString, lPara1);
    /*lint -e64*/
    #else
    if ( g_ulFcDebugLevel >=  ulLevel)
    {
        Print1(pcString, lPara1);
    }
    #endif

    return;
}

VOS_VOID     FC_LOG2
(
    VOS_UINT32            ulLevel,
    const VOS_CHAR       *pcString,
    VOS_INT32             lPara1,
    VOS_INT32             lPara2
)
{
    #ifdef __FC_RELEASE__
    /*lint -e64*/
    TTF_LOG2(UEPS_PID_FLOWCTRL, DIAG_MODE_COMM,
           ulLevel, pcString, lPara1, lPara2);
    /*lint +e64*/
    #else
    if ( g_ulFcDebugLevel >=  ulLevel)
    {
        Print2(pcString, lPara1, lPara2);
    }
    #endif

    return;
}

VOS_VOID     FC_LOG3
(
    VOS_UINT32              ulLevel,
    const VOS_CHAR         *pcString,
    VOS_INT32               lPara1,
    VOS_INT32               lPara2,
    VOS_INT32               lPara3
)
{
    #ifdef __FC_RELEASE__
    /*lint -e64*/
    TTF_LOG3(UEPS_PID_FLOWCTRL, DIAG_MODE_COMM,
           ulLevel, pcString, lPara1, lPara2, lPara3);
    /*lint +e64*/
    #else
    if ( g_ulFcDebugLevel >=  ulLevel)
    {
        Print3(pcString, lPara1, lPara2, lPara3);
    }
    #endif

    return;
}

VOS_VOID     FC_LOG4
(
    VOS_UINT32          ulLevel,
    const VOS_CHAR     *pcString,
    VOS_INT32           lPara1,
    VOS_INT32           lPara2,
    VOS_INT32           lPara3,
    VOS_INT32           lPara4
)
{
    #ifdef __FC_RELEASE__
    /*lint -e64*/
    TTF_LOG4(UEPS_PID_FLOWCTRL, DIAG_MODE_COMM,
           ulLevel, pcString, lPara1, lPara2, lPara3, lPara4);
    /*lint +e64*/
    #else
    if ( g_ulFcDebugLevel >=  ulLevel)
    {
        Print4(pcString, lPara1, lPara2, lPara3, lPara4);
    }
    #endif

    return;
}

/*****************************************************************************
 函 数 名  : FC_MNTN_TraceEvent
 功能描述  : 输出可维可测
 输入参数  : pMsg  --  可维可测消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_MNTN_TraceEvent(VOS_VOID *pMsg)
{
   DIAG_TraceReport(pMsg);

   return;
}

/*****************************************************************************
 函 数 名  : FC_MNTN_TracePointFcEvent
 功能描述  : 流控执行可维可测
 输入参数  : enMsgName  --  流控或解流控消息
             stFcPoint  --  流控点
             ulResult   --  流控执行情况
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_MNTN_TracePointFcEvent
(
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgName,
    FC_POINT_STRU                      *pstFcPoint,
    VOS_UINT32                          ulIsFuncInvoked,
    VOS_UINT32                          ulResult
)
{
    FC_MNTN_POINT_FC_STRU               stMntnPointFc;
    VOS_UINT_PTR                        PtrAddr;
    VOS_UINT32                          *pulOctet;


    stMntnPointFc.ulSenderCpuId         = VOS_LOCAL_CPUID;
    stMntnPointFc.ulSenderPid           = UEPS_PID_FLOWCTRL;
    stMntnPointFc.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    stMntnPointFc.ulReceiverPid         = UEPS_PID_FLOWCTRL;
    stMntnPointFc.ulLength              = (sizeof(FC_MNTN_POINT_FC_STRU) - VOS_MSG_HEAD_LENGTH);
    stMntnPointFc.enMsgName             = enMsgName;
    stMntnPointFc.ulIsFuncInvoked       = ulIsFuncInvoked;
    stMntnPointFc.ulResult              = ulResult;

    /* fetch FcPoint info */
    stMntnPointFc.stFcPoint.enFcId          = pstFcPoint->enFcId;
    stMntnPointFc.stFcPoint.enModemId       = pstFcPoint->enModemId;
    stMntnPointFc.stFcPoint.aucRsv[0]       = 0x0U;
    stMntnPointFc.stFcPoint.aucRsv[1]       = 0x0U;
    stMntnPointFc.stFcPoint.aucRsv[2]       = 0x0U;
    stMntnPointFc.stFcPoint.aucRsv[3]       = 0x0U;
    stMntnPointFc.stFcPoint.aucRsv[4]       = 0x0U;
    stMntnPointFc.stFcPoint.ulPolicyMask    = pstFcPoint->ulPolicyMask;
    stMntnPointFc.stFcPoint.ulFcMask        =   pstFcPoint->ulFcMask;
    stMntnPointFc.stFcPoint.ulParam1        =   pstFcPoint->ulParam1;
    stMntnPointFc.stFcPoint.ulParam2        =   pstFcPoint->ulParam2;

    PtrAddr                                     = (VOS_UINT_PTR)(pstFcPoint->pSetFunc);
    stMntnPointFc.stFcPoint.aulPointSetAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)pstFcPoint->pSetFunc;
    stMntnPointFc.stFcPoint.aulPointSetAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     = (VOS_UINT_PTR)(pstFcPoint->pClrFunc);
    stMntnPointFc.stFcPoint.aulPointClrAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)pstFcPoint->pClrFunc;
    stMntnPointFc.stFcPoint.aulPointClrAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     = (VOS_UINT_PTR)(pstFcPoint->pRstFunc);
    stMntnPointFc.stFcPoint.aulPointRstAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)pstFcPoint->pRstFunc;
    stMntnPointFc.stFcPoint.aulPointRstAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    FC_MNTN_TraceEvent((VOS_VOID *)&stMntnPointFc);

    return;
}


/*****************************************************************************
 函 数 名  : FC_MNTN_TracePolicy
 功能描述  : 输出流控策略的可维可测
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MNTN_TracePolicy(FC_MNTN_EVENT_TYPE_ENUM_UINT16 enMsgName, FC_POLICY_STRU *pPolicy )
{
    FC_MNTN_POLICY_STRU                 stFcMntnPolicy;
    VOS_UINT_PTR                        PtrAddr;
    VOS_UINT32                          *pulOctet;

    VOS_MemSet(&stFcMntnPolicy, 0, sizeof(FC_MNTN_POLICY_STRU));

    stFcMntnPolicy.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stFcMntnPolicy.ulSenderPid      = UEPS_PID_FLOWCTRL;
    stFcMntnPolicy.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stFcMntnPolicy.ulReceiverPid    = UEPS_PID_FLOWCTRL;
    stFcMntnPolicy.ulLength         = (sizeof(FC_MNTN_POLICY_STRU) - VOS_MSG_HEAD_LENGTH);
    stFcMntnPolicy.enMsgName        = enMsgName;

    stFcMntnPolicy.stPolicy.enPolicyId      =   pPolicy->enPolicyId;
    stFcMntnPolicy.stPolicy.ucPriCnt        =   pPolicy->ucPriCnt;
    stFcMntnPolicy.stPolicy.aucRsv[0]       =   0x0U;
    stFcMntnPolicy.stPolicy.aucRsv[1]       =   0x0U;
    stFcMntnPolicy.stPolicy.aucRsv[2]       =   0x0U;
    stFcMntnPolicy.stPolicy.enHighestPri    =   pPolicy->enHighestPri;
    stFcMntnPolicy.stPolicy.enDonePri       =   pPolicy->enDonePri;
    stFcMntnPolicy.stPolicy.enToPri         =   pPolicy->enToPri;
    VOS_MemCpy(stFcMntnPolicy.stPolicy.astFcPri, pPolicy->astFcPri, sizeof(pPolicy->astFcPri));

    PtrAddr                                     =   (VOS_UINT_PTR)(pPolicy->pAdjustForUpFunc);
    stFcMntnPolicy.stPolicy.aulPolicyUpAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)(pPolicy->pAdjustForUpFunc);
    stFcMntnPolicy.stPolicy.aulPolicyUpAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     =   (VOS_UINT_PTR)(pPolicy->pAdjustForDownFunc);
    stFcMntnPolicy.stPolicy.aulPolicyDownAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)(pPolicy->pAdjustForDownFunc);
    stFcMntnPolicy.stPolicy.aulPolicyDownAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     =   (VOS_UINT_PTR)(pPolicy->pPostFunc);
    stFcMntnPolicy.stPolicy.aulPolicyPostAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)(pPolicy->pAdjustForDownFunc);
    stFcMntnPolicy.stPolicy.aulPolicyPostAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    FC_MNTN_TraceEvent(&stFcMntnPolicy);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_MNTN_TraceCpuLoad
 功能描述  : 输出当前CPULoad
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月31日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MNTN_TraceCpuLoad(FC_MNTN_EVENT_TYPE_ENUM_UINT16 enMsgName, VOS_UINT32  ulCpuLoad )
{
    FC_MNTN_CPULOAD_STRU                stFcMntnCpuLoad;

    VOS_MemSet(&stFcMntnCpuLoad, 0, sizeof(FC_MNTN_CPULOAD_STRU));

    stFcMntnCpuLoad.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stFcMntnCpuLoad.ulSenderPid     = UEPS_PID_FLOWCTRL;
    stFcMntnCpuLoad.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stFcMntnCpuLoad.ulReceiverPid   = UEPS_PID_FLOWCTRL;
    stFcMntnCpuLoad.ulLength        = (sizeof(FC_MNTN_CPULOAD_STRU) - VOS_MSG_HEAD_LENGTH);
    stFcMntnCpuLoad.enMsgName       = enMsgName;
    stFcMntnCpuLoad.ulCpuLoad       = ulCpuLoad;

    FC_MNTN_TraceEvent(&stFcMntnCpuLoad);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_MNTN_TraceDrvAssemPara
 功能描述  : 输出当前调整组包方案
 输入参数  : FC_DRV_ASSEM_PARA_STRU  pstDrvAssenPara 当前组包参数

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MNTN_TraceDrvAssemPara(FC_DRV_ASSEM_PARA_STRU *pstDrvAssenPara)
{
    FC_MNTN_DRV_ASSEM_PARA_STRU     stFcMntnDrvAssemPara;

    if (VOS_NULL_PTR == pstDrvAssenPara)
    {
        return VOS_ERR;
    }

    VOS_MemSet(&stFcMntnDrvAssemPara, 0, sizeof(FC_MNTN_DRV_ASSEM_PARA_STRU));

    stFcMntnDrvAssemPara.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stFcMntnDrvAssemPara.ulSenderPid     = UEPS_PID_FLOWCTRL;
    stFcMntnDrvAssemPara.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stFcMntnDrvAssemPara.ulReceiverPid   = UEPS_PID_FLOWCTRL;
    stFcMntnDrvAssemPara.ulLength        = (sizeof(FC_MNTN_DRV_ASSEM_PARA_STRU) - VOS_MSG_HEAD_LENGTH);
    stFcMntnDrvAssemPara.enMsgName       = ID_FC_MNTN_DRV_ASSEM_PARA;
    PS_MEM_CPY(&stFcMntnDrvAssemPara.stDrvAssemPara, pstDrvAssenPara, sizeof(FC_DRV_ASSEM_PARA_STRU));

    FC_MNTN_TraceEvent(&stFcMntnDrvAssemPara);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_IsPolicyEnable
 功能描述  : 判断流控内部策略是否使能
 输入参数  : ulPointPolicyMask       --  流控策略掩码
             enModemId               --  该策略对应的Modem ID
 输出参数  : 无
 返 回 值  : 0     --  流控策略未使能
             非0   --  流控策略使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月13日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
/* add by wangrong */
VOS_UINT32 FC_IsPolicyEnable(VOS_UINT32 ulPointPolicyMask, MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                          ulPolicyMask;

    /* 对于Modem1,内部策略在判断使能时，需要右移FC_POLICY_ID_BUTT后再与NV项中使能位比较 */
    if ( MODEM_ID_0 ==  enModemId )
    {
        ulPolicyMask = ulPointPolicyMask;
    }
    else
    {
        ulPolicyMask = (ulPointPolicyMask >> FC_POLICY_ID_BUTT);
    }

    return (ulPolicyMask & g_stFcCfg.ulFcEnbaleMask);
}
/* add by wangrong */

/*****************************************************************************
 函 数 名  : FC_RegPoint
 功能描述  : 请求添加注册流控点,供外部模块调用
 输入参数  : pstFcRegPoint --  流控点参数
 输出参数  :
 返 回 值  : VOS_OK     --  成功
             VOS_ERR    --  失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_RegPoint
(
    FC_REG_POINT_STRU                  *pstFcRegPoint
)
{
    VOS_UINT32                          ulResult;

    /*参数检查*/
    if ( VOS_NULL_PTR == pstFcRegPoint )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_RegPoint, ERROR, pstFcRegPoint is NULL!\n");
        return VOS_ERR;
    }

    /* Add by wangrong */
    if ( MODEM_ID_BUTT <= pstFcRegPoint->enModemId )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_RegPoint, ERROR, enModemId err %d!\n",
            (VOS_INT32)pstFcRegPoint->enModemId);
        return VOS_ERR;
    }
    /* Add by wangrong */

    if ( FC_POLICY_ID_BUTT <= pstFcRegPoint->enPolicyId )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_RegPoint, ERROR, enPolicyId err %d!\n",
            (VOS_INT32)pstFcRegPoint->enPolicyId);
        return VOS_ERR;
    }

    if ( FC_ID_BUTT <= pstFcRegPoint->enFcId )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_RegPoint, ERROR, enFcId err %d\n",
            (VOS_INT32)pstFcRegPoint->enFcId);
        return VOS_ERR;
    }

    if ( (FC_PRI_LOWEST > pstFcRegPoint->enFcPri)
         || (FC_PRI_HIGHEST < pstFcRegPoint->enFcPri) )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_RegPoint, ERROR, Invalid enPri %d\n",
                (VOS_INT32)pstFcRegPoint->enFcPri);
        return VOS_ERR;
    }

    /* 使能检查 */
    if ( FC_POLICY_MASK(pstFcRegPoint->enPolicyId) != (FC_POLICY_MASK(pstFcRegPoint->enPolicyId) & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_RegPoint, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }

    /* 注册内存策略，优先级只能在内存流控约定的范围之内 */
    if (FC_POLICY_ID_MEM == pstFcRegPoint->enPolicyId)
    {
        if ( (FC_PRI_FOR_MEM_LEV_1 > pstFcRegPoint->enFcPri)
             || (FC_PRI_FOR_MEM_LEV_4 < pstFcRegPoint->enFcPri) )
        {
            FC_LOG1(PS_PRINT_ERROR, "FC_RegPoint, ERROR, Invalid enPri for MEM %d\n",
                    (VOS_INT32)pstFcRegPoint->enFcPri);
            return VOS_ERR;
        }
    }

    if (VOS_NULL_PTR == pstFcRegPoint->pSetFunc)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_RegPoint, ERROR, Invalid Fun pSetFunc\n");
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstFcRegPoint->pClrFunc)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_RegPoint, ERROR, Invalid Fun pClrFunc\n");
        return VOS_ERR;
    }

    ulResult = FC_SndRegPointMsg(pstFcRegPoint);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : FC_DeRegPoint
 功能描述  : 请求去注册流控点
 输入参数  : pulFcId       --  流控点ID
 输出参数  : 无
 返 回 值  : VOS_OK     --  成功
             VOS_ERR    --  失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_DeRegPoint
(
    FC_ID_ENUM_UINT8                   enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulResult;
    FC_POINT_STRU                      *pstFcPoint;
    VOS_UINT32                          ulPointPolicyMask;


    if (FC_ID_BUTT <=  enFcId)
    {
         FC_LOG1(PS_PRINT_ERROR, "FC_DeRegPoint, ERROR, Invalid enFcId %d\n",
                (VOS_INT32)enFcId);
         return VOS_ERR;
    }

    /* add by wangrong */
    if ( MODEM_ID_BUTT <= enModemId )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_DeRegPoint, ERROR, enModemId err %d!\n",
            (VOS_INT32)enModemId);
        return VOS_ERR;
    }
    /* add by wangrong */


    /* 通过流控点ID找到流控点结构 */
    pstFcPoint    = FC_POINT_Get(enFcId);
    if (VOS_NULL_PTR == pstFcPoint)
    {
        /* 该流控策略未使能，则返回VOS_OK */
        FC_LOG1(PS_PRINT_WARNING, "FC_DeRegPoint, WARNING, This FCPonit = %d didn't Reg!\n",
                (VOS_INT32)enFcId);
        return VOS_OK;
    }


    /* 流控点删除，需要对相应的流控策略进行处理 */
    ulPointPolicyMask   = pstFcPoint->ulPolicyMask;

    /* add by wangrong */
    if (0 != FC_IsPolicyEnable(ulPointPolicyMask, enModemId))
    {
         ulResult = FC_SndDeRegPointMsg(enFcId,enModemId);

         return ulResult;
    }
    /* add by wangrong */

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : FC_ChangePoint
 功能描述  : 更改流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月8日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_ChangePoint
(
    FC_ID_ENUM_UINT8                   enFcId,
    FC_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_PRI_ENUM_UINT8                  enPri,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulResult;

    if ( FC_ID_BUTT <=  enFcId )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_ChangePoint, ERROR, Invalid enFcId %d\n",
                (VOS_INT32)enFcId);
        return VOS_ERR;
    }


    if ( (FC_PRI_LOWEST > enPri)
         || (FC_PRI_HIGHEST < enPri) )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_ChangePoint, ERROR, Invalid enPri %d\n",
                (VOS_INT32)enPri);
        return VOS_ERR;
    }


    if ( FC_POLICY_ID_BUTT <= enPolicyId )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_ChangePoint, ERROR, enPolicyId err %d!\n",
            (VOS_INT32)enPolicyId);
        return VOS_ERR;
    }

     /* add by wangrong */
    if ( MODEM_ID_BUTT <= enModemId )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_ChangePoint, ERROR, enModemId err %d!\n",
            (VOS_INT32)enModemId);
        return VOS_ERR;
    }
     /* add by wangrong */

    /* 使能检查 */
    if ( FC_POLICY_MASK(enPolicyId) != (FC_POLICY_MASK(enPolicyId) & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_ChangePoint, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }

    ulResult = FC_SndChangePointMsg(enFcId, enPolicyId, enPri, enModemId);

    return ulResult;
}


/*****************************************************************************
 函 数 名  : FC_POINT_Get
 功能描述  : 根据流控Id来获取流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
FC_POINT_STRU *FC_POINT_Get(FC_ID_ENUM_UINT8 enFcId)
{
    VOS_UINT32                          ulFcIdIdxLoop;


    if ( FC_MAX_POINT_NUM < g_stFcPointMgr.ulPointNum )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_POINT_Get, ERROR, g_stFcPointMgr.ulPointNum overflow!\n");

        return VOS_NULL_PTR;
    }

    for (ulFcIdIdxLoop = 0; ulFcIdIdxLoop < g_stFcPointMgr.ulPointNum; ulFcIdIdxLoop++)
    {
        if (g_stFcPointMgr.astFcPoint[ulFcIdIdxLoop].enFcId == enFcId)
        {
            return (&(g_stFcPointMgr.astFcPoint[ulFcIdIdxLoop]));
        }
    }

    return VOS_NULL_PTR;
}


/*****************************************************************************
 函 数 名  : FC_POINT_Add
 功能描述  : 添加流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POINT_Add
(
    FC_REG_POINT_STRU                  *pstFcRegPoint
)
{
    FC_POINT_STRU                      *pPoint;
    VOS_UINT32                          ulFcPointLoop;
    /* add by wangrong */
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enFcPrivatePolicyId;

    enFcPrivatePolicyId = g_aenPrivatePolicyTbl[pstFcRegPoint->enModemId][pstFcRegPoint->enPolicyId];
    /* add by wangrong */

    if ( FC_MAX_POINT_NUM < g_stFcPointMgr.ulPointNum )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_POINT_Add, WARNING, Reach maximun point number!\n");
        return VOS_ERR;
    }

    for (ulFcPointLoop = 0; ulFcPointLoop < g_stFcPointMgr.ulPointNum; ulFcPointLoop++)
    {
        if (g_stFcPointMgr.astFcPoint[ulFcPointLoop].enFcId == pstFcRegPoint->enFcId)
        {
            /*将该点新的策略加入到原来该点的策略中*/
            pPoint  = &(g_stFcPointMgr.astFcPoint[ulFcPointLoop]);
            pPoint->ulPolicyMask |=  FC_POLICY_MASK(enFcPrivatePolicyId);
            pPoint->enModemId     =  pstFcRegPoint->enModemId;

            /*打印一个提示，表明该点被多个策略添加*/
            FC_LOG1(PS_PRINT_NORMAL, "FC_POINT_Add, NORMAL, The same point has added %d!\n",
                (VOS_INT32)pstFcRegPoint->enFcId);

            return VOS_OK;
        }
    }

    if ( FC_MAX_POINT_NUM == g_stFcPointMgr.ulPointNum )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_POINT_Add, WARNING, g_stFcPointMgr.ulPointNum reaches the MAXNUM!\n");
        return VOS_ERR;
    }

    /*如果没有找到，那么就是一个新点，需要加入到管理结构中*/
    pPoint  = &(g_stFcPointMgr.astFcPoint[g_stFcPointMgr.ulPointNum]);

    pPoint->enFcId          = pstFcRegPoint->enFcId;
    pPoint->ulPolicyMask    = FC_POLICY_MASK(enFcPrivatePolicyId);
    pPoint->ulFcMask        = 0;
    pPoint->ulParam1        = pstFcRegPoint->ulParam1;
    pPoint->ulParam2        = pstFcRegPoint->ulParam2;
    pPoint->pSetFunc        = pstFcRegPoint->pSetFunc;
    pPoint->pClrFunc        = pstFcRegPoint->pClrFunc;
    pPoint->pRstFunc        = pstFcRegPoint->pRstFunc;

    g_stFcPointMgr.ulPointNum++;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POINT_Del
 功能描述  : 从流控点管理模块删除某一个流控点
 输入参数  : enFcId -- 流控ID
 输出参数  : 流控点管理实体
 返 回 值  : 成功VOS_OK，失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POINT_Del(FC_ID_ENUM_UINT8 enFcId )
{
    VOS_UINT32                          ulFcIdIdxLoop;
    VOS_UINT32                          ulFcShiftId;
    FC_POINT_STRU                      *pFcPoint;


    /* 防止全局变量被踩，导致后面数组访问越界 */
    if ( FC_MAX_POINT_NUM < g_stFcPointMgr.ulPointNum)
    {
        FC_LOG(PS_PRINT_WARNING, "FC_POINT_Del, WARNING, g_stFcPointMgr.ulPointNum overflow!\n");

        return VOS_ERR;
    }

    for (ulFcIdIdxLoop = 0; ulFcIdIdxLoop < g_stFcPointMgr.ulPointNum; ulFcIdIdxLoop++)
    {
        if (g_stFcPointMgr.astFcPoint[ulFcIdIdxLoop].enFcId == enFcId)
        {
            for (ulFcShiftId = ulFcIdIdxLoop + 1; ulFcShiftId < g_stFcPointMgr.ulPointNum; ulFcShiftId++)
            {
                pFcPoint    = &(g_stFcPointMgr.astFcPoint[ulFcShiftId]);
                PS_MEM_CPY((pFcPoint - 1), pFcPoint, sizeof(FC_POINT_STRU));
            }

            /* 最后一个需要手动清除 */
            PS_MEM_SET(&(g_stFcPointMgr.astFcPoint[ulFcShiftId-1]), 0, sizeof(FC_POINT_STRU));

            g_stFcPointMgr.ulPointNum--;

            return VOS_OK;
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_PointSetFc
 功能描述  : 请求对应ID的流控点启动流控
 输入参数  : enFcId --  流控点ID
 输出参数  : 无
 返 回 值  : 见FC_PRI_OPER_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
FC_PRI_OPER_ENUM_UINT32 FC_POINT_SetFc
(
    VOS_UINT32                          ulPolicyMask,
    FC_ID_ENUM_UINT8                   enFcId
)
{
    FC_POINT_STRU                      *pFcPoint;
    VOS_UINT32                          ulNeedSet;
    VOS_UINT32                          ulResult ;


    /* 根据流控点,判决是否需要进行流控操作 */
    ulNeedSet   = PS_FALSE;
    ulResult    = VOS_OK;

    pFcPoint    = FC_POINT_Get(enFcId);
    if (VOS_NULL_PTR == pFcPoint)
    {
        return FC_PRI_CHANGE_AND_CONTINUE;
    }

    /*============================*/
    /* 掩码从0到非0，发生翻转，需要执行流控操作，否则说明之前该流控点已经处于流控状态 */
    if (0 == pFcPoint->ulFcMask)
    {
        /* 执行流控函数 */
        ulNeedSet   = VOS_TRUE;
    }

    pFcPoint->ulFcMask  |= ulPolicyMask;

    /* 执行流控 */
    if (PS_FALSE == ulNeedSet)
    {
        FC_MNTN_TracePointFcEvent(ID_FC_MNTN_POINT_SET_FC, pFcPoint, ulNeedSet, ulResult);
        return FC_PRI_CHANGE_AND_CONTINUE;
    }

    if (VOS_NULL_PTR != pFcPoint->pSetFunc)
    {
        ulResult = pFcPoint->pSetFunc(pFcPoint->ulParam1, pFcPoint->ulParam2);
    }

    FC_MNTN_TracePointFcEvent(ID_FC_MNTN_POINT_SET_FC, pFcPoint, ulNeedSet, ulResult);

    return FC_PRI_CHANGE_AND_BREAK;
}


/*****************************************************************************
 函 数 名  : FC_PointClrFc
 功能描述  : 请求对应ID的流控点解除流控
 输入参数  : enFcId --  流控点ID
 输出参数  : 无
 返 回 值  : 见FC_PRI_OPER_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
FC_PRI_OPER_ENUM_UINT32 FC_POINT_ClrFc(VOS_UINT32 ulPolicyMask, FC_ID_ENUM_UINT8 enFcId)
{
    /*  根据ID找到流控点实例，执行实例的流控解除函数 */
    FC_POINT_STRU                      *pFcPoint;
    VOS_UINT32                          ulNeedSet;
    VOS_UINT32                          ulResult;


    /* 根据流控点,判决是否需要进行解除流控操作 */
    ulNeedSet   = PS_FALSE;
    ulResult    = VOS_OK;

    pFcPoint    = FC_POINT_Get(enFcId);
    if (VOS_NULL_PTR == pFcPoint)
    {
        return FC_PRI_CHANGE_AND_CONTINUE;
    }

    /* 并没有因为该种类型导致流控，无须解除流控 */
    if (0 == (pFcPoint->ulFcMask & ulPolicyMask))
    {
        return FC_PRI_CHANGE_AND_CONTINUE;
    }

    pFcPoint->ulFcMask &= ~ulPolicyMask;

    if ( 0 == pFcPoint->ulFcMask )
    {
        /* 只有所有情况都解除了，才能解除流控 */
        ulNeedSet = VOS_TRUE;
    }

    /* 执行解除流控的操作 */
    if (PS_FALSE == ulNeedSet)
    {
        FC_MNTN_TracePointFcEvent(ID_FC_MNTN_POINT_CLR_FC, pFcPoint, ulNeedSet, ulResult);
        return FC_PRI_CHANGE_AND_CONTINUE;
    }

    if (VOS_NULL_PTR != pFcPoint->pClrFunc)
    {
        ulResult = pFcPoint->pClrFunc(pFcPoint->ulParam1, pFcPoint->ulParam2);
    }

    FC_MNTN_TracePointFcEvent(ID_FC_MNTN_POINT_CLR_FC, pFcPoint, ulNeedSet, ulResult);

    return FC_PRI_CHANGE_AND_BREAK;
}


/*****************************************************************************
 函 数 名  : FC_POINT_Reg
 功能描述  : 流控点注册内部处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POINT_Reg
(
    FC_REG_POINT_STRU                  *pstFcRegPoint
)
{
    FC_PRI_ENUM_UINT8                   enPri;
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enFcPrivatePolicyId;

    enFcPrivatePolicyId = g_aenPrivatePolicyTbl[pstFcRegPoint->enModemId][pstFcRegPoint->enPolicyId];

    /* 添加流控点 */
    if ( VOS_OK != FC_POINT_Add(pstFcRegPoint) )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_POINT_Reg, ERROR, FC_POINT_Add error!\n");
        return VOS_ERR;
    }

    /* 如果该流控策略里已经存在该流控ID，直接返回 */
    /* add by wangrong */
    enPri   = FC_POLICY_GetPriWithFcId(enFcPrivatePolicyId, pstFcRegPoint->enFcId);
    /* add by wangrong */

    if (FC_PRI_BUTT != enPri)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_POINT_Reg, ERROR, Policy has same FC Id\n");
        return VOS_ERR;
    }

    /* add by wangrong */
    (VOS_VOID)FC_POLICY_AddPoint(enFcPrivatePolicyId,
        pstFcRegPoint->enFcId,
        pstFcRegPoint->enFcPri);
    /* add by wangrong */

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POINT_DeReg
 功能描述  : 去注册流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POINT_DeReg(FC_ID_ENUM_UINT8 enFcId, MODEM_ID_ENUM_UINT16  enModemId)
{
    FC_POINT_STRU                      *pFcPoint;
    /* add by wangrong */
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId;
    /* add by wangrong */
    VOS_UINT32                          ulPointPolicyMask;

    /* 通过流控点ID找到流控点结构 */
    pFcPoint    = FC_POINT_Get(enFcId);
    if (VOS_NULL_PTR == pFcPoint)
    {
        return VOS_ERR;
    }
    /* 防止另一张卡误调 */
    if ( enModemId != pFcPoint->enModemId )
    {
        return VOS_ERR;
    }

    /* 流控点删除，需要对相应的流控策略进行处理 */
    ulPointPolicyMask   = pFcPoint->ulPolicyMask;

    /* add by wangrong */
    for (enPolicyId = FC_PRIVATE_POLICY_ID_MEM_MODEM_0; enPolicyId < FC_PRIVATE_POLICY_ID_BUTT; enPolicyId++)
    {
        if ( 0 != (FC_POLICY_MASK(enPolicyId) & ulPointPolicyMask) )
        {
            /* 使能检查 */
            if ( 0 != FC_IsPolicyEnable(FC_POLICY_MASK(enPolicyId), enModemId) )
            {
                (VOS_VOID)FC_POLICY_DelPoint(enPolicyId, enFcId);
            }
        }
    }
    /* add by wangrong */

    /* 从流控点池里删除该流控点 */
    (VOS_VOID)FC_POINT_Del(enFcId);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POINT_Change
 功能描述  : 更改POINT属性
 输入参数  : enFcId     -- 流控ID
              enPolicyId --  流控策略ID
              enNewPri   -- 新的优先级
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POINT_Change
(
    FC_ID_ENUM_UINT8                   enFcId,
    FC_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_PRI_ENUM_UINT8                  enNewPri,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    FC_POINT_STRU                      *pFcPoint;
    FC_PRI_ENUM_UINT8                  enOldPri;
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enFcPrivatePolicyId;


    pFcPoint    = FC_POINT_Get(enFcId);
    if (VOS_NULL_PTR == pFcPoint)
    {
        return VOS_ERR;
    }

    enFcPrivatePolicyId = g_aenPrivatePolicyTbl[enModemId][enPolicyId];
    enOldPri            = FC_POLICY_GetPriWithFcId(enFcPrivatePolicyId, enFcId);

    if (FC_PRI_BUTT <= enOldPri)
    {

        FC_LOG3(PS_PRINT_WARNING,
            "FC, FC_POINT_Change, WARNING, oldPri %d err with PolicyId %d, FcId %d\n",
            (VOS_INT32)enOldPri, (VOS_INT32)enFcPrivatePolicyId, (VOS_INT32)enFcId);
        return VOS_ERR;
    }

    if (enNewPri == enOldPri)
    {

        FC_LOG3(PS_PRINT_WARNING,
            "FC, FC_POINT_Change, WARNING, NewPri %d eqaul old with PolicyId %d, FcId %d\n",
            (VOS_INT32)enNewPri, (VOS_INT32)enFcPrivatePolicyId, (VOS_INT32)enFcId);
        return VOS_ERR;
    }

    (VOS_VOID)FC_POLICY_ChangePoint(enFcPrivatePolicyId, enFcId, enOldPri, enNewPri);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POINT_Init
 功能描述  : 流控点模块初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_POINT_Init( VOS_VOID )
{
    VOS_MemSet(&g_stFcPointMgr, 0, sizeof(FC_POINT_MGR_STRU));
}

/*****************************************************************************
 函 数 名  : FC_POLICY_TrimInvalidPri
 功能描述  : 去除该流控策略当前优先级及更低的无效优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_POLICY_TrimInvalidPri( FC_POLICY_STRU *pFcPolicy )
{
    FC_PRI_STRU                        *pstPri;
    FC_PRI_ENUM_UINT8                  enPri;

    /* 如果当前优先级无效，则直接返回，无需降级 */
    if (FC_PRI_NULL == pFcPolicy->enDonePri)
    {
        return;
    }

    /* 找到一个有效的优先级，则跳出循环，不改变当前流控优先级 */
    for (enPri = pFcPolicy->enDonePri; enPri > FC_PRI_NULL; enPri--)
    {
        pstPri   = &(pFcPolicy->astFcPri[enPri]);
        if (VOS_TRUE == pstPri->ucValid)
        {
            break;
        }
    }

    /* 如果当前优先级以及更低的所有优先级均为无效，则将当前优先级直接置为最低优先级 */
    pFcPolicy->enDonePri    = enPri;

    return;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_UpWithOnePri
 功能描述  : 执行一次当前优先级的所有流控点的流控操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
FC_PRI_OPER_ENUM_UINT32 FC_POLICY_UpWithOnePri
(
    FC_POLICY_STRU                     *pFcPolicy,
    FC_PRI_STRU                        *pstPri
)
{
    VOS_UINT32                          ulLoop;

    if (FC_MAX_POINT_NUM < pstPri->ucFcIdCnt)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_POLICY_UpWithOnePri, ERROR, FcIdCnt overflow!\n");

        return FC_PRI_CHANGE_AND_CONTINUE;
    }

    for (ulLoop = 0; ulLoop < pstPri->ucFcIdCnt; ulLoop++)
    {
        (VOS_VOID)FC_POINT_SetFc(FC_POLICY_MASK(pFcPolicy->enPolicyId), pstPri->aenFcId[ulLoop]);
    }

    return FC_PRI_CHANGE_AND_BREAK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_DownForOnePri
 功能描述  : 执行一次当前优先级的所有流控点的解流控操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
FC_PRI_OPER_ENUM_UINT32  FC_POLICY_DownWithOnePri
(
    FC_POLICY_STRU                     *pPolicy,
    FC_PRI_STRU                        *pstPri
)
{
    VOS_UINT32                          ulLoop;

    if (FC_MAX_POINT_NUM < pstPri->ucFcIdCnt)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_POLICY_DownWithOnePri, ERROR, FcIdCnt overflow!\n");

        return FC_PRI_CHANGE_AND_CONTINUE;
    }

    for (ulLoop = 0; ulLoop < pstPri->ucFcIdCnt; ulLoop++)
    {
        (VOS_VOID)FC_POINT_ClrFc(FC_POLICY_MASK(pPolicy->enPolicyId), pstPri->aenFcId[ulLoop]);
    }

    return FC_PRI_CHANGE_AND_BREAK;
}

/*****************************************************************************
 函 数 名  : FC_POLICY_Up
 功能描述  : 流控级别递增一个有效级别
 输入参数  : pPolicy -- 流控策略实体
 输出参数  : pPolicy -- 流控策略级别更改，并执行相应的流控函数
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_POLICY_Up(FC_POLICY_STRU *pPolicy)
{
    FC_PRI_STRU                        *pstPri;
    FC_PRI_ENUM_UINT8                  enPri;

    if (pPolicy->enDonePri >= pPolicy->enHighestPri)
    {
        return VOS_OK;
    }

    while (pPolicy->enDonePri < pPolicy->enHighestPri)
    {
        enPri = (FC_PRI_ENUM_UINT8)(pPolicy->enDonePri + 1);
        pstPri   = &(pPolicy->astFcPri[enPri]);

        /* 当前优先级存在，执行当前流控操作 */
        if (VOS_TRUE == pstPri->ucValid)
        {
            (VOS_VOID)FC_POLICY_UpWithOnePri(pPolicy, pstPri);
            pPolicy->enDonePri++;
            break;
        }

        pPolicy->enDonePri++;
    }

    (VOS_VOID)FC_MNTN_TracePolicy(ID_FC_MNTN_POLICY_UP, pPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_UpToTargetPri
 功能描述  : 流控到指定流控级别
 输入参数  : pFcPolicy   --  流控策略实体指针
              enTargetPri -- 目标流控级别
 输出参数  : None
 返 回 值  : 成功VOS_OK，失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_UpToTargetPri(FC_POLICY_STRU *pFcPolicy, FC_PRI_ENUM_UINT8 enTargetPri )
{
    FC_PRI_STRU                    *pstPri;
    FC_PRI_ENUM_UINT8              enPri;

    if (enTargetPri >= FC_PRI_BUTT)
    {
        return VOS_ERR;
    }

    if (pFcPolicy->enDonePri >= enTargetPri)
    {
        return VOS_OK;
    }

    while (pFcPolicy->enDonePri < enTargetPri)
    {
        enPri   = (FC_PRI_ENUM_UINT8)(pFcPolicy->enDonePri + 1);
        pstPri  = &(pFcPolicy->astFcPri[enPri]);

        /* 当前优先级存在，执行当前流控操作 */
        if (VOS_TRUE == pstPri->ucValid)
        {
            (VOS_VOID)FC_POLICY_UpWithOnePri(pFcPolicy, pstPri);
        }

        pFcPolicy->enDonePri++;
    }

    (VOS_VOID)FC_MNTN_TracePolicy(ID_FC_MNTN_POLICY_UP, pFcPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_Down
 功能描述  : 流控级别递减一个有效级别
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_POLICY_Down(FC_POLICY_STRU *pFcPolicy)
{
    FC_PRI_STRU                        *pstPri;

    if (FC_PRI_NULL == pFcPolicy->enDonePri)
    {
        return VOS_OK;
    }

    while (pFcPolicy->enDonePri > FC_PRI_NULL)
    {
        pstPri   = &(pFcPolicy->astFcPri[pFcPolicy->enDonePri]);

        /* 当前优先级存在，执行当前优先级的解流控操作 */
        if (VOS_TRUE == pstPri->ucValid)
        {
            (VOS_VOID)FC_POLICY_DownWithOnePri(pFcPolicy, pstPri);
            pFcPolicy->enDonePri--;
            break;
        }

        pFcPolicy->enDonePri--;
    }

    /* 去除多余的无效优先级 */
    FC_POLICY_TrimInvalidPri(pFcPolicy);

    (VOS_VOID)FC_MNTN_TracePolicy(ID_FC_MNTN_POLICY_DOWN, pFcPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_DownToTargetPri
 功能描述  : 解除流控到指定流控级别
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_DownToTargetPri(FC_POLICY_STRU *pFcPolicy, FC_PRI_ENUM_UINT8 enTargetPri )
{
    FC_PRI_STRU                        *pstPri;

    if (pFcPolicy->enDonePri <= enTargetPri)
    {
        return VOS_OK;
    }

    while (pFcPolicy->enDonePri > enTargetPri)
    {
        pstPri   = &(pFcPolicy->astFcPri[pFcPolicy->enDonePri]);

        /* 当前优先级存在，执行当前优先级的解流控操作 */
        if (VOS_TRUE == pstPri->ucValid)
        {
            (VOS_VOID)FC_POLICY_DownWithOnePri(pFcPolicy, pstPri);
        }

        pFcPolicy->enDonePri--;
    }

    (VOS_VOID)FC_MNTN_TracePolicy(ID_FC_MNTN_POLICY_DOWN, pFcPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_UpdateHighestPri
 功能描述  : 更新该流控策略的最高优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_POLICY_UpdateHighestPri( FC_POLICY_STRU *pPolicy )
{
    FC_PRI_ENUM_UINT8                  enPri;

    pPolicy->enHighestPri   = FC_PRI_NULL;

    for (enPri = FC_PRI_1; enPri < FC_PRI_BUTT; enPri++)
    {
        if (VOS_TRUE == pPolicy->astFcPri[enPri].ucValid)
        {
            pPolicy->enHighestPri   = enPri;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_AddPointForPri
 功能描述  : 添加流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_AddPointForPri
(
    FC_POLICY_STRU                     *pPolicy,
    FC_ID_ENUM_UINT8                   enFcId,
    FC_PRI_ENUM_UINT8                  enPointPri
)
{
    FC_PRI_STRU                        *pFcPri;
    VOS_UINT32                          ulFcIdxLoop;

    if (FC_PRI_BUTT <= enPointPri)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_POLICY_AddPointForPri, ERROR, enPointPri overflow!\n");

        return VOS_ERR;
    }

    pFcPri  = &(pPolicy->astFcPri[enPointPri]);

    if ( pFcPri->ucFcIdCnt >= FC_MAX_POINT_NUM  )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_POLICY_AddPointForPri, WARNING, added FcId overflow\n",
                (VOS_INT32)enFcId);
        return VOS_ERR;
    }

    /* 如果当前优先级已存在，则添加该流控点 */
    if (VOS_TRUE == pFcPri->ucValid)
    {
        for (ulFcIdxLoop = 0; ulFcIdxLoop < pFcPri->ucFcIdCnt; ulFcIdxLoop++)
        {
            if (enFcId == pFcPri->aenFcId[ulFcIdxLoop])
            {
                /* 已经注册过相同ID，直接返回 */
                FC_LOG1(PS_PRINT_WARNING, "FC_POLICY_AddPointForPri, WARNING, add added FcId %d\n",
                    (VOS_INT32)enFcId);
                return VOS_ERR;
            }
        }

        pFcPri->aenFcId[pFcPri->ucFcIdCnt]  = enFcId;
        pFcPri->ucFcIdCnt++;
    }
    /* 如果当前优先级不存在，则该优先级置为有效 */
    else
    {
        pFcPri->aenFcId[0]  = enFcId;
        pFcPri->ucFcIdCnt   = 1;
        pFcPri->ucValid     = VOS_TRUE;
        pPolicy->ucPriCnt++;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_DelPointForPri
 功能描述  : 删除流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_DelPointForPri
(
    FC_POLICY_STRU                     *pPolicy,
    FC_ID_ENUM_UINT8                   enFcId,
    FC_PRI_ENUM_UINT8                  enPointPri
)
{
    FC_PRI_STRU                        *pFcPri;
    VOS_UINT32                          ulFcIdIdxLoop;
    VOS_UINT32                          ulFcShiftId;

    if (FC_PRI_BUTT <= enPointPri)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_POLICY_DelPointForPri, ERROR, enPointPri overflow!\n");
        return VOS_ERR;
    }

    pFcPri  = &(pPolicy->astFcPri[enPointPri]);

    for (ulFcIdIdxLoop = 0; ulFcIdIdxLoop < pFcPri->ucFcIdCnt; ulFcIdIdxLoop++)
    {
        if (enFcId == pFcPri->aenFcId[ulFcIdIdxLoop])
        {
            /* 删除流控点，进行数组移位 */
            pFcPri->aenFcId[ulFcIdIdxLoop]  = 0;
            for (ulFcShiftId = (ulFcIdIdxLoop + 1); ulFcShiftId < pFcPri->ucFcIdCnt; ulFcShiftId++)
            {
                pFcPri->aenFcId[ulFcShiftId - 1]    = pFcPri->aenFcId[ulFcShiftId];
                pFcPri->aenFcId[ulFcShiftId]        = 0;
            }

            pFcPri->ucFcIdCnt--;

            /* 该优先级删除了所有的流控点，则删除该优先级 */
            if (0 == pFcPri->ucFcIdCnt)
            {
                pFcPri->ucValid     = PS_FALSE;
                pPolicy->ucPriCnt--;
            }

            return VOS_OK;
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_AddPoint
 功能描述  : 流控策略增加流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_AddPoint
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId,
    FC_ID_ENUM_UINT8                   enFcId,
    FC_PRI_ENUM_UINT8                  enPointPri
)
{
    FC_POLICY_STRU                     *pPolicy;

    pPolicy     = FC_POLICY_Get(enPolicyId);

    /* 向流控策略添加流控点 */
    FC_POLICY_AddPointForPri(pPolicy, enFcId, enPointPri);

    /* 更新该流控策略最高优先级 */
    FC_POLICY_UpdateHighestPri(pPolicy);

    /* 调整流控策略，增加流控点，按照流控门限进行重新调整 */
    if (VOS_NULL_PTR != pPolicy->pAdjustForUpFunc)
    {
        (VOS_VOID)pPolicy->pAdjustForUpFunc(enPointPri, enFcId);
    }

    /* 新流控点的流控判决处理 */
    /* 如果注册的流控优先级低于当前优先级，则执行该流控点的流控 */
    if (enPointPri <= pPolicy->enDonePri)
    {
        (VOS_VOID)FC_POINT_SetFc( FC_POLICY_MASK(enPolicyId), enFcId );
    }

    /* 输出可维可测 */
    (VOS_VOID)FC_MNTN_TracePolicy(ID_FC_MNTN_POLICY_ADD_POINT, pPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_GetPriWithFcId
 功能描述  : 通过FcId获得流控优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
FC_PRI_ENUM_UINT8  FC_POLICY_GetPriWithFcId
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId,
    FC_ID_ENUM_UINT8                   enFcId
)
{
    FC_POLICY_STRU                     *pPolicy;
    FC_PRI_STRU                        *pPri;
    FC_PRI_ENUM_UINT8                   enPriLoop;
    VOS_UINT32                          ulFcIdIndexLoop;
    FC_PRI_ENUM_UINT8                   enPointPri;

    pPolicy     = FC_POLICY_Get(enPolicyId);

    for (enPriLoop = FC_PRI_1; enPriLoop < FC_PRI_BUTT; enPriLoop++)
    {
        pPri    = &(pPolicy->astFcPri[enPriLoop]);

        if (FC_MAX_POINT_NUM < pPri->ucFcIdCnt)
        {
            FC_LOG(PS_PRINT_ERROR, "FC_POLICY_GetPriWithFcId, ERROR, ucFcIdCnt overflow!\n");

            continue;
        }

        for (ulFcIdIndexLoop = 0; ulFcIdIndexLoop < pPri->ucFcIdCnt; ulFcIdIndexLoop++)
        {
            if (pPri->aenFcId[ulFcIdIndexLoop] == enFcId)
            {
                /* 从该流控策略里删除该流控点 */
                enPointPri  = enPriLoop;
                return enPointPri;
            }
        }
    }

    return FC_PRI_BUTT;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_DelPoint
 功能描述  : 删除流控策略的流控ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_DelPoint
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId,
    FC_ID_ENUM_UINT8                   enFcId
)
{
    FC_PRI_ENUM_UINT8                  enPointPri;
    FC_POLICY_STRU                     *pPolicy;

    /*================================*//* 对需要删除的流控点进行解除流控处理 */
    (VOS_VOID)FC_POINT_ClrFc(FC_POLICY_MASK(enPolicyId), enFcId);

    /*================================*//* 对相关连的流控策略进行调整 */
    enPointPri  = FC_POLICY_GetPriWithFcId(enPolicyId, enFcId);
    if (FC_PRI_BUTT == enPointPri)
    {
        return VOS_OK;
    }

    pPolicy = FC_POLICY_Get(enPolicyId);
    (VOS_VOID)FC_POLICY_DelPointForPri(pPolicy, enFcId, enPointPri);

    /* 更新该流控策略最高优先级 */
    FC_POLICY_UpdateHighestPri(pPolicy);

    /* 流控策略调整 */
    if (VOS_NULL_PTR != pPolicy->pAdjustForDownFunc)
    {
        (VOS_VOID)pPolicy->pAdjustForDownFunc(enPointPri, enFcId);
    }

    /* 输出可维可测 */
    (VOS_VOID)FC_MNTN_TracePolicy(ID_FC_MNTN_POLICY_DEL_POINT, pPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_ChangePoint
 功能描述  : 更改流控点的优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_ChangePoint
(
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId,
    FC_ID_ENUM_UINT8                   enFcId,
    FC_PRI_ENUM_UINT8                  enPointOldPri,
    FC_PRI_ENUM_UINT8                  enPointNewPri
)
{
    FC_POLICY_STRU                     *pPolicy;

    pPolicy = FC_POLICY_Get(enPolicyId);

    /* 刷新该流控点在流控策略的流控点维护 */
    (VOS_VOID)FC_POLICY_DelPointForPri(pPolicy, enFcId, enPointOldPri);
    FC_POLICY_AddPointForPri(pPolicy, enFcId, enPointNewPri);


    /* 更新该流控策略最高优先级 */
    FC_POLICY_UpdateHighestPri(pPolicy);

    /* 调整流控策略，更改流控点，按照流控门限进行重新调整 */
    if (VOS_NULL_PTR != pPolicy->pAdjustForUpFunc)
    {
        (VOS_VOID)pPolicy->pAdjustForUpFunc(enPointOldPri, enFcId);
    }

    /* 针对优先级的更改进行流控点状态的调整 */
    /* 如果老的优先级低于当前优先级，新的优先级高于当前优先级，则解除该流控点的流控 */
    if ( (enPointOldPri < pPolicy->enDonePri) && (enPointNewPri > pPolicy->enDonePri) )
    {
        (VOS_VOID)FC_POINT_ClrFc(FC_POLICY_MASK(pPolicy->enPolicyId), enFcId);
    }

    /* 如果老的优先级高于当前优先级，新的优先级低于当前优先级，则对该流控点进行流控 */
    if ( (enPointOldPri > pPolicy->enDonePri) && (enPointNewPri < pPolicy->enDonePri) )
    {
        (VOS_VOID)FC_POINT_SetFc(FC_POLICY_MASK(pPolicy->enPolicyId), enFcId);
    }

    /* 输出可维可测 */
    (VOS_VOID)FC_MNTN_TracePolicy(ID_FC_MNTN_POLICY_CHANGE_POINT, pPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_GetPriCnt
 功能描述  : 获取流控策略优先级个数
 输入参数  : pFcPolicy -- 流控策略实体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_GetPriCnt(FC_POLICY_STRU *pFcPolicy)
{
    return (pFcPolicy->ucPriCnt);
}


/*****************************************************************************
 函 数 名  : FC_POLICY_Init
 功能描述  : 流控策略实体初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_POLICY_Init( VOS_VOID )
{
    FC_POLICY_ID_ENUM_UINT8             enPolicyId;

    /*通用流控策略初始化 */
    VOS_MemSet(&g_astFcPolicy[0], 0, sizeof(FC_POLICY_STRU) * FC_PRIVATE_POLICY_ID_BUTT);

    for (enPolicyId = 0; enPolicyId < FC_PRIVATE_POLICY_ID_BUTT; enPolicyId++)
    {
        g_astFcPolicy[enPolicyId].enPolicyId    = (VOS_UINT8)enPolicyId;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CFG_CheckCpuParam
 功能描述  : CPU流控NV参数合法性检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CFG_CheckCpuParam( FC_CFG_CPU_STRU *pstFcCfgCpu )
{
    if ( pstFcCfgCpu->ulCpuOverLoadVal < pstFcCfgCpu->ulCpuUnderLoadVal)
    {
        FC_LOG2(PS_PRINT_WARNING,
            "FC, FC_CFG_CheckCpuParam, WARNING, overLoad %d less than underLoad %d\n",
            (VOS_INT32)pstFcCfgCpu->ulCpuOverLoadVal, (VOS_INT32)pstFcCfgCpu->ulCpuUnderLoadVal);
        return VOS_ERR;
    }

    if ( (pstFcCfgCpu->ulCpuOverLoadVal == 0) || (pstFcCfgCpu->ulCpuOverLoadVal > 100))
    {
        FC_LOG2(PS_PRINT_WARNING,
            "FC, FC_CFG_CheckCpuParam, WARNING, invalid value overLoad %d, underLoad %d\n",
            (VOS_INT32)pstFcCfgCpu->ulCpuOverLoadVal, (VOS_INT32)pstFcCfgCpu->ulCpuUnderLoadVal);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CFG_CheckMemParam
 功能描述  : 内存流控NV参数合法性检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CFG_CheckMemParam( FC_CFG_MEM_STRU *pstFcCfgMem )
{
    VOS_UINT32                          ulThresholdLoop;

    if ( FC_MEM_THRESHOLD_LEV_BUTT < pstFcCfgMem->ulThresholdCnt )
    {
        FC_LOG1(PS_PRINT_WARNING,
                "FC, FC_CFG_CheckMemParam, WARNING, ulThresholdCnt %d\n",
                (VOS_INT32)pstFcCfgMem->ulThresholdCnt);

        return VOS_ERR;
    }

    for ( ulThresholdLoop = 0 ; ulThresholdLoop < pstFcCfgMem->ulThresholdCnt ; ulThresholdLoop++ )
    {
        /* 内存流控设置的是空闲值 */
        if ( pstFcCfgMem->astThreshold[ulThresholdLoop].ulSetThreshold
             > pstFcCfgMem->astThreshold[ulThresholdLoop].ulStopThreshold )
        {
            FC_LOG3(PS_PRINT_WARNING,
                    "FC, FC_CFG_CheckMemParam, WARNING, ulThresholdLoop %d ulSetThreshold %D less than ulStopThreshold %d\n",
                    (VOS_INT32)ulThresholdLoop,
                    (VOS_INT32)pstFcCfgMem->astThreshold[ulThresholdLoop].ulSetThreshold,
                    (VOS_INT32)pstFcCfgMem->astThreshold[ulThresholdLoop].ulStopThreshold);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CFG_CheckUlRateParam
 功能描述  : 上行限制流控NV参数合法性检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CFG_CheckUlRateParam( FC_CFG_UM_UL_RATE_STRU *pstFcCfgUmUlRate )
{
    if ( FC_UL_RATE_MAX_LEV <  pstFcCfgUmUlRate->ucRateCnt)
    {
        FC_LOG1(PS_PRINT_WARNING,
            "FC, FC_CFG_CheckUlRateParam, WARNING, ucRateCnt %d\n",
            pstFcCfgUmUlRate->ucRateCnt);

        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CFG_CheckParam
 功能描述  : NV参数合法性检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CFG_CheckParam( FC_CFG_STRU *pstFcCfg )
{
    /* 设计约束，A核需要判断是否因为速传引起CPU占用率高，第一次CPU占用率
       超标时才启动计算速传速率，所以至少需要2次 */
    if (2 > pstFcCfg->stFcCfgCpuA.ulSmoothTimerLen)
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_CFG_CheckParam, WARNING, CPUA flow ctrl ulSmoothTimerLen is %d!\n",
                                  (VOS_INT32)pstFcCfg->stFcCfgCpuA.ulSmoothTimerLen);
        return VOS_ERR;
    }

    if ( VOS_OK != FC_CFG_CheckCpuParam(&(pstFcCfg->stFcCfgCpuA)) )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_CFG_CheckParam, WARNING, Check CPUA flow ctrl param failed!\n");
        return VOS_ERR;
    }

    if ( VOS_OK != FC_CFG_CheckCpuParam(&(pstFcCfg->stFcCfgCpuC)) )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_CFG_CheckParam, WARNING, Check CPUC flow ctrl param failed!\n");
        return VOS_ERR;
    }

    if ( VOS_OK != FC_CFG_CheckMemParam(&(pstFcCfg->stFcCfgMem)) )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_CFG_CheckParam, WARNING, Check mem flow ctrl param failed!\n");
        return VOS_ERR;
    }

    if ( VOS_OK != FC_CFG_CheckUlRateParam(&(pstFcCfg->stFcCfgUmUlRateForCpu)) )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_CFG_CheckParam, WARNING, Check CPU UL rate param failed!\n");
        return VOS_ERR;
    }

    if ( VOS_OK != FC_CFG_CheckUlRateParam(&(pstFcCfg->stFcCfgUmUlRateForTmp)) )
    {
        FC_LOG(PS_PRINT_WARNING, "FC_CFG_CheckParam, WARNING, Check temperature UL rate param failed!\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CFG_SetDefaultValue
 功能描述  : 设置NV默认值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月12日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CFG_SetDefaultValue( FC_CFG_STRU *pstFcCfg )
{
    FC_LOG(PS_PRINT_WARNING, "FC_CFG_SetDefaultValue, Set Default NV Value.\n");

    VOS_MemSet(pstFcCfg, 0x0, sizeof(FC_CFG_STRU));

    pstFcCfg->ulFcEnbaleMask = 0x7F;

    pstFcCfg->stFcCfgCpuA.ulCpuOverLoadVal      = 95;
    pstFcCfg->stFcCfgCpuA.ulCpuUnderLoadVal     = 70;
    pstFcCfg->stFcCfgCpuA.ulSmoothTimerLen      = 8;
    pstFcCfg->stFcCfgCpuA.ulStopAttemptTimerLen = 100;
    pstFcCfg->stFcCfgCpuA.ulUmUlRateThreshold   = 1048576;
    pstFcCfg->stFcCfgCpuA.ulUmDlRateThreshold   = 10485760;
    pstFcCfg->stFcCfgCpuA.ulRmRateThreshold     = 10485760;

    pstFcCfg->stFcCfgMem.ulThresholdCnt           = 4;
    pstFcCfg->stFcCfgMem.astThreshold[0].ulSetThreshold  = 300;
    pstFcCfg->stFcCfgMem.astThreshold[0].ulStopThreshold = 350;
    pstFcCfg->stFcCfgMem.astThreshold[1].ulSetThreshold  = 250;
    pstFcCfg->stFcCfgMem.astThreshold[1].ulStopThreshold = 300;
    pstFcCfg->stFcCfgMem.astThreshold[2].ulSetThreshold  = 150;
    pstFcCfg->stFcCfgMem.astThreshold[2].ulStopThreshold = 200;
    pstFcCfg->stFcCfgMem.astThreshold[3].ulSetThreshold  = 0;
    pstFcCfg->stFcCfgMem.astThreshold[3].ulStopThreshold = 20;

    pstFcCfg->stFcCfgCst.stThreshold.ulSetThreshold      = 3072;
    pstFcCfg->stFcCfgCst.stThreshold.ulStopThreshold     = 1024;

    pstFcCfg->stFcCfgGprs.stThresholdMemSize.ulSetThreshold  = 30000;
    pstFcCfg->stFcCfgGprs.stThresholdMemSize.ulStopThreshold = 30000;
    pstFcCfg->stFcCfgGprs.stThresholdMemCnt.ulSetThreshold   = 600;
    pstFcCfg->stFcCfgGprs.stThresholdMemCnt.ulStopThreshold  = 600;

    pstFcCfg->stFcCfgCpuC.ulCpuOverLoadVal      = 95;
    pstFcCfg->stFcCfgCpuC.ulCpuUnderLoadVal     = 70;
    pstFcCfg->stFcCfgCpuC.ulSmoothTimerLen      = 8;
    pstFcCfg->stFcCfgCpuC.ulStopAttemptTimerLen = 100;
    pstFcCfg->stFcCfgCpuC.ulUmUlRateThreshold   = 1048576;
    pstFcCfg->stFcCfgCpuC.ulUmDlRateThreshold   = 10485760;
    pstFcCfg->stFcCfgCpuC.ulRmRateThreshold     = 10485760;

    pstFcCfg->stFcCfgUmUlRateForCpu.ucRateCnt   = 4;
    pstFcCfg->stFcCfgUmUlRateForCpu.ausRate[0]  = 5760;
    pstFcCfg->stFcCfgUmUlRateForCpu.ausRate[1]  = 2000;
    pstFcCfg->stFcCfgUmUlRateForCpu.ausRate[2]  = 1000;
    pstFcCfg->stFcCfgUmUlRateForCpu.ausRate[3]  = 384;

    pstFcCfg->stFcCfgUmUlRateForTmp.ucRateCnt   = 3;
    pstFcCfg->stFcCfgUmUlRateForTmp.ausRate[0]  = 2000;
    pstFcCfg->stFcCfgUmUlRateForTmp.ausRate[1]  = 1000;
    pstFcCfg->stFcCfgUmUlRateForTmp.ausRate[2]  = 384;

    pstFcCfg->stFcCfgCdma.stThresholdMemCnt.ulSetThreshold  = 600;
    pstFcCfg->stFcCfgCdma.stThresholdMemCnt.ulStopThreshold = 300;
    pstFcCfg->stFcCfgCdma.stThresholdMemSize.ulSetThreshold = 900000;
    pstFcCfg->stFcCfgCdma.stThresholdMemSize.ulStopThreshold= 121200;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CFG_SetNvValue
 功能描述  : 设置NV默认值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月12日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CFG_SetNvValue( FC_CFG_NV_STRU  *pstFcCfgNv )
{
    FC_CFG_STRU         *pstFcCfg = &g_stFcCfg;

    VOS_MemSet(pstFcCfg, 0x0, sizeof(FC_CFG_STRU));

    pstFcCfg->ulFcEnbaleMask = pstFcCfgNv->ulFcEnbaleMask;

    VOS_MemCpy(&(pstFcCfg->stFcCfgCpuA), &(pstFcCfgNv->stFcCfgCpuA), sizeof(FC_CFG_CPU_STRU));

    pstFcCfg->stFcCfgMem.ulThresholdCnt           = pstFcCfgNv->ulFcCfgMemThresholdCnt;
    VOS_MemCpy(&(pstFcCfg->stFcCfgMem.astThreshold[0]),
               &(pstFcCfgNv->stFcCfgMem[0]),
               sizeof(FC_CFG_MEM_THRESHOLD_STRU) * FC_MEM_THRESHOLD_LEV_BUTT);

    pstFcCfg->stFcCfgCst.stThreshold.ulSetThreshold      = pstFcCfgNv->stFcCfgCst.ulSetThreshold;
    pstFcCfg->stFcCfgCst.stThreshold.ulStopThreshold     = pstFcCfgNv->stFcCfgCst.ulStopThreshold;

    pstFcCfg->stFcCfgGprs.stThresholdMemSize.ulSetThreshold  = pstFcCfgNv->stFcCfgGprsMemSize.ulSetThreshold;
    pstFcCfg->stFcCfgGprs.stThresholdMemSize.ulStopThreshold = pstFcCfgNv->stFcCfgGprsMemSize.ulStopThreshold;
    pstFcCfg->stFcCfgGprs.stThresholdMemCnt.ulSetThreshold   = pstFcCfgNv->stFcCfgGprsMemCnt.ulSetThreshold;
    pstFcCfg->stFcCfgGprs.stThresholdMemCnt.ulStopThreshold  = pstFcCfgNv->stFcCfgGprsMemCnt.ulStopThreshold;

    VOS_MemCpy(&(pstFcCfg->stFcCfgCpuC), &(pstFcCfgNv->stFcCfgCpuC), sizeof(FC_CFG_CPU_STRU));

    VOS_MemCpy(&(pstFcCfg->stFcCfgUmUlRateForCpu), &(pstFcCfgNv->stFcCfgUmUlRateForCpu), sizeof(FC_CFG_UM_UL_RATE_STRU));

    VOS_MemCpy(&(pstFcCfg->stFcCfgUmUlRateForTmp), &(pstFcCfgNv->stFcCfgUmUlRateForTmp), sizeof(FC_CFG_UM_UL_RATE_STRU));

    VOS_MemCpy(&(pstFcCfg->stFcCfgCdma.stThresholdMemCnt), &(pstFcCfgNv->stFcCfgCdmaMemCnt), sizeof(FC_CFG_MEM_THRESHOLD_STRU));

    VOS_MemCpy(&(pstFcCfg->stFcCfgCdma.stThresholdMemSize), &(pstFcCfgNv->stFcCfgCdmaMemSize), sizeof(FC_CFG_MEM_THRESHOLD_STRU));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CFG_Init
 功能描述  : 流控配置初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CFG_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;
    FC_CFG_NV_STRU                      stFcCfgNv;

    VOS_MemSet(&g_stFcCfg, 0, sizeof(FC_CFG_STRU));

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Flow_Ctrl_Config,\
                       &stFcCfgNv, sizeof(FC_CFG_NV_STRU));

    if ( NV_OK != ulResult )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_CFG_Init, WARNING, Fail to read NV, result %d\n",
                (VOS_INT32)ulResult);

        (VOS_VOID)FC_CFG_SetDefaultValue(&g_stFcCfg);

        return VOS_OK;
    }

    /* 将NV配置值转换成内部结构保存 */
    FC_CFG_SetNvValue(&stFcCfgNv);

    ulResult = FC_CFG_CheckParam(&g_stFcCfg);

    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_CommInit, ERROR, Check NV parameter fail!\n");

        /* 当前的NV值有错，设置默认值返回成功 */
        (VOS_VOID)FC_CFG_SetDefaultValue(&g_stFcCfg);

        return VOS_OK;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_SndCpuMsg
 功能描述  : 发送CPU流控消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_SndCpuMsg
(
    FC_MSG_TYPE_ENUM_UINT16 usMsgName,
    VOS_UINT32              ulCpuLoad,
    VOS_UINT32              ulUlRate,
    VOS_UINT32              ulDlRate
)
{
    VOS_UINT32                          ulResult;
    FC_CPULOAD_IND_STRU                *pstMsg;

    pstMsg = (FC_CPULOAD_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                    sizeof(FC_CPULOAD_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        /* 该函数会在中断中被调用，故使用LogPrint */
        LogPrint("FC_SndIntraCpuMsg, ERROR, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = usMsgName;
    pstMsg->ulCpuLoad       = ulCpuLoad;
    pstMsg->ulUlRate        = ulUlRate;
    pstMsg->ulDlRate        = ulDlRate;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        /* 该函数会在中断中被调用，故使用LogPrint */
        LogPrint("FC_SndIntraCpuMsg, ERROR, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_SndRegPointMsg
 功能描述  : 发送注册流控点消息
 输入参数  : pstFcRegPoint -- 流控点结构信息指针
 输出参数  : None
 返 回 值  : 成功VOS_OK，失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_SndRegPointMsg
(
    FC_REG_POINT_STRU                  *pstFcRegPoint
)
{
    VOS_UINT32                          ulResult;
    FC_REG_POINT_IND_STRU              *pstMsg;

    pstMsg = (FC_REG_POINT_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                      sizeof(FC_REG_POINT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndRegPointMsg, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = ID_FC_REG_POINT_IND;

    VOS_MemCpy(&(pstMsg->stFcPoint), pstFcRegPoint, sizeof(FC_REG_POINT_STRU));

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndRegPointMsg, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_SndDeRegPointMsg
 功能描述  : 发送注册流控点消息
 输入参数  : enFcId -- 流控ID
 输出参数  : None
 返 回 值  : 成功VOS_OK，失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_SndDeRegPointMsg
(
    FC_ID_ENUM_UINT8                   enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulResult;
    FC_DEREG_POINT_IND_STRU            *pstMsg;

    pstMsg = (FC_DEREG_POINT_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                      sizeof(FC_DEREG_POINT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndDeRegPointMsg, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = ID_FC_DEREG_POINT_IND;
    pstMsg->enFcId          = enFcId;
    pstMsg->enModemId       = enModemId;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndDeRegPointMsg, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_SndChangePointMsg
 功能描述  : 流控点优先级改变消息
 输入参数  : enFcId     -- 流控ID
              enPolicyId -- 策略ID
              enPri      -- 新的流控优先级
 输出参数  : 消息
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_SndChangePointMsg
(
    FC_ID_ENUM_UINT8                   enFcId,
    FC_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_PRI_ENUM_UINT8                  enPri,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulResult;
    FC_CHANGE_POINT_IND_STRU           *pstMsg;

    pstMsg = (FC_CHANGE_POINT_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                         sizeof(FC_CHANGE_POINT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndChangePointMsg, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = ID_FC_CHANGE_POINT_IND;
    pstMsg->enFcId          = enFcId;
    pstMsg->enPolicyId      = enPolicyId;
    pstMsg->enPri           = enPri;
    pstMsg->enModemId       = enModemId;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndChangePointMsg, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CommInit
 功能描述  : 两核流控模块初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CommInit( VOS_VOID )
{
    VOS_UINT32                          ulResult;

    /* 流控策略初始化 */
    FC_POLICY_Init();

    /* 流控点初始化 */
    FC_POINT_Init();

    /* 流控配置项初始化 */
    ulResult = FC_CFG_Init();

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_CommInit, init Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_SetDebugLev
 功能描述  : 更改流控打印级别
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_SetDebugLev( VOS_UINT32 ulLev )
{
    g_ulFcDebugLevel    = ulLev;

    return g_ulFcDebugLevel;
}


/*****************************************************************************
 函 数 名  : FC_SetFcEnableMask
 功能描述  : 设置流控掩码函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月9日
    作    者   : FC_RecoverUlGradeProcess
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_SetFcEnableMask( VOS_UINT32 ulEnableMask )
{
    g_stFcCfg.ulFcEnbaleMask    = ulEnableMask;

    return (g_stFcCfg.ulFcEnbaleMask);
}


/*****************************************************************************
 函 数 名  : FC_SetThreshold
 功能描述  : 设置门限
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月10日
    作    者   : 高财
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_SetThreshold
(
    VOS_UINT32                          ulPolicyId,
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulSetThreshold,
    VOS_UINT32                          ulStopThreshold
)
{
    switch(ulPolicyId)
    {
        case FC_POLICY_ID_MEM:
            g_stFcCfg.stFcCfgMem.astThreshold[ulParam1].ulSetThreshold  = ulSetThreshold;
            g_stFcCfg.stFcCfgMem.astThreshold[ulParam1].ulStopThreshold = ulStopThreshold;
            break;

        case FC_POLICY_ID_CPU_A:
            g_stFcCfg.stFcCfgCpuA.ulCpuOverLoadVal  = ulSetThreshold;
            g_stFcCfg.stFcCfgCpuA.ulCpuUnderLoadVal = ulStopThreshold;
            break;

        case FC_POLICY_ID_CDS:
            break;

        case FC_POLICY_ID_CST:
            g_stFcCfg.stFcCfgCst.stThreshold.ulSetThreshold     = ulSetThreshold;
            g_stFcCfg.stFcCfgCst.stThreshold.ulStopThreshold    = ulStopThreshold;
            break;

        case FC_POLICY_ID_GPRS:
            if ( 0 == ulParam1) /* R_ITF_FLOW_CTRL_TYPE_MEM_CNT */
            {
                g_stFcCfg.stFcCfgGprs.stThresholdMemCnt.ulSetThreshold      = ulSetThreshold;
                g_stFcCfg.stFcCfgGprs.stThresholdMemCnt.ulStopThreshold     = ulStopThreshold;
            }
            else    /* R_ITF_FLOW_CTRL_TYPE_MEM_SIZE */
            {
                g_stFcCfg.stFcCfgGprs.stThresholdMemSize.ulSetThreshold     = ulSetThreshold;
                g_stFcCfg.stFcCfgGprs.stThresholdMemSize.ulStopThreshold    = ulStopThreshold;
            }
            break;

        case FC_POLICY_ID_TMP:
            break;

        case FC_POLICY_ID_CPU_C:
            g_stFcCfg.stFcCfgCpuC.ulCpuOverLoadVal  = ulSetThreshold;
            g_stFcCfg.stFcCfgCpuC.ulCpuUnderLoadVal = ulStopThreshold;
            break;

        default:
            break;
    }

    return VOS_OK;
} /* FC_SetThreshold */


/*****************************************************************************
 函 数 名  : FC_Help
 功能描述  : 流控当前信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月9日
    作    者   : FC_RecoverUlGradeProcess
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_Help( VOS_VOID )
{
    FC_PRIVATE_POLICY_ID_ENUM_UINT8     enPolicyId;
    FC_PRI_ENUM_UINT8                  enFcPri;
    FC_POLICY_STRU                     *pPolicy;
    FC_PRI_STRU                        *pPri;
    VOS_UINT32                          ulFcIdIndex;
    VOS_UINT32                          ulFcIdLoop;
    FC_POINT_STRU                      *pFcPoint;


    (VOS_VOID)vos_printf("\n================POLICY ID define start================\n");
    (VOS_VOID)vos_printf("0 : FC_POLICY_ID_MEM\n");
    (VOS_VOID)vos_printf("1 : FC_POLICY_ID_CPU_A\n");
    (VOS_VOID)vos_printf("2 : FC_POLICY_ID_CDS\n");
    (VOS_VOID)vos_printf("3 : FC_POLICY_ID_CST\n");
    (VOS_VOID)vos_printf("4 : FC_POLICY_ID_GPRS\n");
    (VOS_VOID)vos_printf("5 : FC_POLICY_ID_TMP\n");
    (VOS_VOID)vos_printf("6 : FC_POLICY_ID_CPU_C\n");
    (VOS_VOID)vos_printf("7 : FC_POLICY_ID_CDMA\n");
    (VOS_VOID)vos_printf("================POLICY ID define end================\n");

    (VOS_VOID)vos_printf("\n================FC ID define start================\n");
    (VOS_VOID)vos_printf("0  : FC_ID_BRIDGE_FORWARD_DISACRD\n");
    (VOS_VOID)vos_printf("1  : FC_ID_USB_ETH\n");
    (VOS_VOID)vos_printf("2  : FC_ID_WIFI_ETH\n");
    (VOS_VOID)vos_printf("3  : FC_ID_NIC_1\n");
    (VOS_VOID)vos_printf("4  : FC_ID_NIC_2\n");
    (VOS_VOID)vos_printf("5  : FC_ID_NIC_3\n");
    (VOS_VOID)vos_printf("6  : FC_ID_NIC_4\n");
    (VOS_VOID)vos_printf("7  : FC_ID_NIC_5\n");
    (VOS_VOID)vos_printf("8  : FC_ID_NIC_6\n");
    (VOS_VOID)vos_printf("9  : FC_ID_NIC_7\n");
    (VOS_VOID)vos_printf("10 : FC_ID_NIC_8\n");
    (VOS_VOID)vos_printf("11 : FC_ID_NIC_9\n");
    (VOS_VOID)vos_printf("12 : FC_ID_NIC_10\n");
    (VOS_VOID)vos_printf("13 : FC_ID_NIC_11\n");
    (VOS_VOID)vos_printf("14 : FC_ID_MODEM\n");
    (VOS_VOID)vos_printf("15 : FC_ID_UL_RATE_1_FOR_CPU\n");
    (VOS_VOID)vos_printf("16 : FC_ID_UL_RATE_2_FOR_CPU\n");
    (VOS_VOID)vos_printf("17 : FC_ID_UL_RATE_3_FOR_CPU\n");
    (VOS_VOID)vos_printf("18 : FC_ID_UL_RATE_4_FOR_CPU\n");
    (VOS_VOID)vos_printf("19 : FC_ID_UL_RATE_5_FOR_CPU\n");
    (VOS_VOID)vos_printf("20 : FC_ID_UL_RATE_6_FOR_CPU\n");
    (VOS_VOID)vos_printf("21 : FC_ID_UL_RATE_7_FOR_CPU\n");
    (VOS_VOID)vos_printf("22 : FC_ID_UL_RATE_8_FOR_CPU\n");
    (VOS_VOID)vos_printf("23 : FC_ID_UL_RATE_9_FOR_CPU\n");
    (VOS_VOID)vos_printf("24 : FC_ID_UL_RATE_10_FOR_CPU\n");
    (VOS_VOID)vos_printf("25 : FC_ID_UL_RATE_11_FOR_CPU\n");
    (VOS_VOID)vos_printf("26 : FC_ID_UL_RATE_1_FOR_TMP\n");
    (VOS_VOID)vos_printf("27 : FC_ID_UL_RATE_2_FOR_TMP\n");
    (VOS_VOID)vos_printf("28 : FC_ID_UL_RATE_3_FOR_TMP\n");
    (VOS_VOID)vos_printf("29 : FC_ID_UL_RATE_4_FOR_TMP\n");
    (VOS_VOID)vos_printf("30 : FC_ID_UL_RATE_5_FOR_TMP\n");
    (VOS_VOID)vos_printf("31 : FC_ID_UL_RATE_6_FOR_TMP\n");
    (VOS_VOID)vos_printf("32 : FC_ID_UL_RATE_7_FOR_TMP\n");
    (VOS_VOID)vos_printf("33 : FC_ID_UL_RATE_8_FOR_TMP\n");
    (VOS_VOID)vos_printf("34 : FC_ID_UL_RATE_9_FOR_TMP\n");
    (VOS_VOID)vos_printf("35 : FC_ID_UL_RATE_10_FOR_TMP\n");
    (VOS_VOID)vos_printf("36 : FC_ID_UL_RATE_11_FOR_TMP\n");
    (VOS_VOID)vos_printf("================FC ID define end================\n");


    (VOS_VOID)vos_printf("\n================FC Debug func start================\n");
    (VOS_VOID)vos_printf("FC SetThreshold Func        : FC_SetThreshold (ulPolicyId, ulParam1, ulSetThreshold, ulStopThreshold)\n");
    (VOS_VOID)vos_printf("FC SetDevLev Func           : FC_SetDebugLev (ulLev)\n");
    (VOS_VOID)vos_printf("FC SetEnableMask Func       : FC_SetFcEnableMask (ulEnableMask)\n");
    (VOS_VOID)vos_printf("================FC Debug func end================\n");


    (VOS_VOID)vos_printf("\n================FC Point information start================\n");
    (VOS_VOID)vos_printf("FC Point information Start\n");
    (VOS_VOID)vos_printf("FC Point Num            : %d\n", g_stFcPointMgr.ulPointNum);

    for (ulFcIdLoop = 0; ulFcIdLoop < g_stFcPointMgr.ulPointNum; ulFcIdLoop++)
    {
        pFcPoint    = &(g_stFcPointMgr.astFcPoint[ulFcIdLoop]);

        (VOS_VOID)vos_printf("FC ID                   : %d\n", pFcPoint->enFcId);
        (VOS_VOID)vos_printf("Modem ID                : %d\n", pFcPoint->enModemId);
        (VOS_VOID)vos_printf("ulPolicyMask        : 0x%x\n", pFcPoint->ulPolicyMask);
        (VOS_VOID)vos_printf("ulFcMask            : 0x%x\n", pFcPoint->ulFcMask);
        (VOS_VOID)vos_printf("ulParam1            : 0x%x\n", pFcPoint->ulParam1);
        (VOS_VOID)vos_printf("ulParam2            : 0x%x\n", pFcPoint->ulParam2);
        (VOS_VOID)vos_printf("pSetFunc            : %p\n", pFcPoint->pSetFunc);
        (VOS_VOID)vos_printf("pClrFunc            : %p\n", pFcPoint->pClrFunc);
    }
    (VOS_VOID)vos_printf("================FC Point information end================\n");



    (VOS_VOID)vos_printf("\n================FC POLICY STATUS Start================\n");
    (VOS_VOID)vos_printf("FC EnableMask           : 0x%x\n", g_stFcCfg.ulFcEnbaleMask);

    for (enPolicyId = FC_PRIVATE_POLICY_ID_MEM_MODEM_0; enPolicyId < FC_PRIVATE_POLICY_ID_BUTT; enPolicyId++)
    {
        pPolicy = FC_POLICY_Get(enPolicyId);

        (VOS_VOID)vos_printf("POLICY ID               : %d\n", enPolicyId);
        (VOS_VOID)vos_printf("PriCnt              : %d\n", pPolicy->ucPriCnt);
        (VOS_VOID)vos_printf("enHighestPri        : %d\n", pPolicy->enHighestPri);
        (VOS_VOID)vos_printf("enDonePri           : %d\n", pPolicy->enDonePri);
        (VOS_VOID)vos_printf("pAdjustForUpFunc    : %p\n", pPolicy->pAdjustForUpFunc);
        (VOS_VOID)vos_printf("pAdjustForDownFunc  : %p\n", pPolicy->pAdjustForDownFunc);
        (VOS_VOID)vos_printf("pPostFunc           : %p\n", pPolicy->pPostFunc);

        for (enFcPri = FC_PRI_1; enFcPri < FC_PRI_BUTT; enFcPri++)
        {
            pPri    = &(pPolicy->astFcPri[enFcPri]);

            if (PS_TRUE == pPri->ucValid)
            {
                (VOS_VOID)vos_printf("FcID of Pri %d       : ", enFcPri);

                for (ulFcIdIndex = 0; ulFcIdIndex < pPri->ucFcIdCnt; ulFcIdIndex++)
                {
                    (VOS_VOID)vos_printf("%d, ", pPri->aenFcId[ulFcIdIndex]);
                }

                (VOS_VOID)vos_printf("\n");
            }
        }
    }

    (VOS_VOID)vos_printf("================FC POLICY STATUS End================\n");

    return VOS_OK;
}
/*lint -restore */
/*lint +e534*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

