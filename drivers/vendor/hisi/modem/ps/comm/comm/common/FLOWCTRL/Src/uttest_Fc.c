
#include "Fc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

    extern FC_POINT_MGR_STRU                       g_stFcPointMgr;
    extern VOS_UINT32                              g_ulFcDebugLevel;

    unsigned long *g_ulFcPointMgr;

/*****************************************************************************
 函 数 名  : stub_FC_POINT_Init
 功能描述  : 函数FC_POINT_Init的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月17日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Init( VOS_VOID )
{
	FC_POINT_MGR_STRU stFcPointMgr = {0};
	int ret = 1;

	FC_POINT_Init();

    //g_ulFcPointMgr = (unsigned long *)&g_stFcPointMgr;

	ret = memcmp(&g_stFcPointMgr, &stFcPointMgr, sizeof(FC_POINT_MGR_STRU));

    return ret;
}

void stub_FC_POINT_MemSet(void)
{
    FC_POINT_MGR_STRU stFcPointMgr = {0};

    memcpy(&g_stFcPointMgr, &stFcPointMgr, sizeof(FC_POINT_MGR_STRU));
}

void stub_FC_POLICY_Init_MemSet(void)
{
    FC_POLICY_STRU  stFcPolicy[FC_PRIVATE_POLICY_ID_BUTT] = {0};

    memcpy(&g_astFcPolicy, &stFcPolicy, sizeof(FC_POLICY_STRU)*FC_PRIVATE_POLICY_ID_BUTT);
}

/*****************************************************************************
 函 数 名  : stub_FC_LOG
 功能描述  : 函数FC_LOG的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_LOG
(
    unsigned int    ulLevel,
    char           *pcString
)
{
    FC_LOG(ulLevel,pcString);

    if(g_ulFcDebugLevel>=ulLevel)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_LOG1
 功能描述  : 函数FC_LOG1的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_LOG1
(
    unsigned int    ulLevel,
    char           *pcString,
    int             lPara1
)
{
    FC_LOG1(ulLevel,pcString,lPara1);

    if(g_ulFcDebugLevel>=ulLevel)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_LOG2
 功能描述  : 函数FC_LOG2的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_LOG2
(
    unsigned int    ulLevel,
    char           *pcString,
    int             lPara1,
    int             lPara2
)
{
    FC_LOG2(ulLevel,pcString,lPara1,lPara2);

    if(g_ulFcDebugLevel>=ulLevel)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_LOG3
 功能描述  : 函数FC_LOG3的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_LOG3
(
    unsigned int    ulLevel,
    char           *pcString,
    int             lPara1,
    int             lPara2,
    int             lPara3
)
{
    FC_LOG3(ulLevel,pcString,lPara1,lPara2,lPara3);

    if(g_ulFcDebugLevel>=ulLevel)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_LOG4
 功能描述  : 函数FC_LOG4的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_LOG4
(
    unsigned int    ulLevel,
    char           *pcString,
    int             lPara1,
    int             lPara2,
    int             lPara3,
    int             lPara4
)
{
    FC_LOG4(ulLevel,pcString,lPara1,lPara2,lPara3,lPara4);

    if(g_ulFcDebugLevel>=ulLevel)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_MNTN_TracePointFcEvent
 功能描述  : 函数FC_MNTN_TracePointFcEvent的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_MNTN_TracePointFcEvent(void)
{
    FC_MNTN_EVENT_TYPE_ENUM_UINT16      enMsgName;
    FC_POINT_STRU                       stFcPoint;
    VOS_UINT32                          ulIsFuncInvoked;
    VOS_UINT32                          ulResult;
    FC_MNTN_POINT_FC_STRU               stMntnPointFc1;
    FC_MNTN_POINT_FC_STRU               stMntnPointFc2;
    VOS_UINT_PTR                        PtrAddr;
    VOS_UINT32                          *pulOctet;

    /* 被测函数入参赋值 */
    enMsgName = ID_FC_MNTN_POLICY_UP;

    stFcPoint.enFcId = FC_ID_NIC_1;
    stFcPoint.enModemId = MODEM_ID_1;
    stFcPoint.ulPolicyMask = 127;
    stFcPoint.ulFcMask = 2;
    stFcPoint.ulParam1 = 0;
    stFcPoint.ulParam2 = 0;
    stFcPoint.pSetFunc = 0x1000;
    stFcPoint.pClrFunc = 0x2000;
    stFcPoint.pRstFunc = 0x3000;

    ulIsFuncInvoked = 0;
    ulResult        = 1;

    /* 调用被测函数 */
    FC_MNTN_TracePointFcEvent(enMsgName,&stFcPoint,ulIsFuncInvoked,ulResult);

    /* 使用被测函数的赋值方式模拟对FC_MNTN_TraceEvent的入参赋值 */
    memset(&stMntnPointFc1, 0, sizeof(FC_MNTN_POINT_FC_STRU));

    stMntnPointFc1.ulSenderCpuId         = VOS_LOCAL_CPUID;
    stMntnPointFc1.ulSenderPid           = UEPS_PID_FLOWCTRL;
    stMntnPointFc1.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    stMntnPointFc1.ulReceiverPid         = UEPS_PID_FLOWCTRL;
    stMntnPointFc1.ulLength              = (sizeof(FC_MNTN_POINT_FC_STRU) - VOS_MSG_HEAD_LENGTH);
    stMntnPointFc1.enMsgName             = enMsgName;
    stMntnPointFc1.ulIsFuncInvoked       = ulIsFuncInvoked;
    stMntnPointFc1.ulResult              = ulResult;

    /* fetch FcPoint info */
    stMntnPointFc1.stFcPoint.enFcId          = stFcPoint.enFcId;
    stMntnPointFc1.stFcPoint.enModemId       = stFcPoint.enModemId;
    stMntnPointFc1.stFcPoint.ulPolicyMask    = stFcPoint.ulPolicyMask;
    stMntnPointFc1.stFcPoint.ulFcMask        =   stFcPoint.ulFcMask;
    stMntnPointFc1.stFcPoint.ulParam1        =   stFcPoint.ulParam1;
    stMntnPointFc1.stFcPoint.ulParam2        =   stFcPoint.ulParam2;

    PtrAddr                                     = (VOS_UINT_PTR)(stFcPoint.pSetFunc);
    stMntnPointFc1.stFcPoint.aulPointSetAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)stFcPoint.pSetFunc;
    stMntnPointFc1.stFcPoint.aulPointSetAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     = (VOS_UINT_PTR)(stFcPoint.pClrFunc);
    stMntnPointFc1.stFcPoint.aulPointClrAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)stFcPoint.pClrFunc;
    stMntnPointFc1.stFcPoint.aulPointClrAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     = (VOS_UINT_PTR)(stFcPoint.pRstFunc);
    stMntnPointFc1.stFcPoint.aulPointRstAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)stFcPoint.pRstFunc;
    stMntnPointFc1.stFcPoint.aulPointRstAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    /* 对FC_MNTN_TraceEvent的入参直接赋值 */
    memset(&stMntnPointFc2, 0, sizeof(FC_MNTN_POINT_FC_STRU));

    stMntnPointFc2.ulSenderCpuId         = VOS_LOCAL_CPUID;
    stMntnPointFc2.ulSenderPid           = UEPS_PID_FLOWCTRL;
    stMntnPointFc2.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    stMntnPointFc2.ulReceiverPid         = UEPS_PID_FLOWCTRL;
    stMntnPointFc2.ulLength              = (sizeof(FC_MNTN_POINT_FC_STRU) - VOS_MSG_HEAD_LENGTH);
    stMntnPointFc2.enMsgName             = ID_FC_MNTN_POLICY_UP;
    stMntnPointFc2.ulIsFuncInvoked       = 0;
    stMntnPointFc2.ulResult              = 1;

    /* fetch FcPoint info */
    stMntnPointFc2.stFcPoint.enFcId          = FC_ID_NIC_1;
    stMntnPointFc2.stFcPoint.enModemId       = MODEM_ID_1;
    stMntnPointFc2.stFcPoint.ulPolicyMask    = 127;
    stMntnPointFc2.stFcPoint.ulFcMask        = 2;
    stMntnPointFc2.stFcPoint.ulParam1        = 0;
    stMntnPointFc2.stFcPoint.ulParam2        = 0;


    stMntnPointFc2.stFcPoint.aulPointSetAddr[0]  = 0x1000;   /* Low */
    stMntnPointFc2.stFcPoint.aulPointSetAddr[1]  = 0;    /* High */

    stMntnPointFc2.stFcPoint.aulPointClrAddr[0]  = 0x2000;   /* Low */
    stMntnPointFc2.stFcPoint.aulPointClrAddr[1]  = 0;    /* High */

    stMntnPointFc2.stFcPoint.aulPointRstAddr[0]  = 0x3000;   /* Low */
    stMntnPointFc2.stFcPoint.aulPointRstAddr[1]  = 0;    /* High */

    /* 比较FC_MNTN_TraceEvent的入参 */
    if (memcmp(&stMntnPointFc2,&stMntnPointFc1,sizeof(FC_MNTN_POINT_FC_STRU)))
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_MNTN_TracePolicy
 功能描述  : 函数FC_MNTN_TracePolicy的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_MNTN_TracePolicy(void)
{
    FC_MNTN_EVENT_TYPE_ENUM_UINT16 enMsgName;
    FC_POLICY_STRU stPolicy;
    FC_MNTN_POLICY_STRU                 stFcMntnPolicy1;
    FC_MNTN_POLICY_STRU                 stFcMntnPolicy2;
    VOS_UINT_PTR                        PtrAddr;
    VOS_UINT32                          *pulOctet;
    FC_PRI_STRU                         astFcPri[FC_PRI_BUTT];

    /* 被测函数入参赋值 */
    memset(&astFcPri[0], 0xcd, (sizeof(FC_PRI_STRU)*FC_PRI_BUTT));

    enMsgName = ID_FC_MNTN_CPU_A_CPULOAD;

    stPolicy.enPolicyId = FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0;
    stPolicy.ucPriCnt   = 1;
    stPolicy.enHighestPri = FC_PRI_5;
    stPolicy.enDonePri    = FC_PRI_4;
    stPolicy.enToPri      = FC_PRI_5;
    memcpy(&(stPolicy.astFcPri[0]),&astFcPri[0], (sizeof(FC_PRI_STRU)*FC_PRI_BUTT));
    stPolicy.pAdjustForUpFunc = 0x1000;
    stPolicy.pAdjustForDownFunc = 0x2000;
    stPolicy.pPostFunc = 0x3000;

    /* 调用被测函数 */
    (VOS_VOID)FC_MNTN_TracePolicy(enMsgName, &stPolicy);

    /* 使用被测函数的赋值方式模拟对FC_MNTN_TraceEvent的入参赋值 */
    memset(&stFcMntnPolicy1, 0, sizeof(FC_MNTN_POLICY_STRU));

    stFcMntnPolicy1.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stFcMntnPolicy1.ulSenderPid      = UEPS_PID_FLOWCTRL;
    stFcMntnPolicy1.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stFcMntnPolicy1.ulReceiverPid    = UEPS_PID_FLOWCTRL;
    stFcMntnPolicy1.ulLength         = (sizeof(FC_MNTN_POLICY_STRU) - VOS_MSG_HEAD_LENGTH);
    stFcMntnPolicy1.enMsgName        = enMsgName;

    stFcMntnPolicy1.stPolicy.enPolicyId      =   stPolicy.enPolicyId;
    stFcMntnPolicy1.stPolicy.ucPriCnt        =   stPolicy.ucPriCnt;
    stFcMntnPolicy1.stPolicy.aucRsv[0]       =   0x0U;
    stFcMntnPolicy1.stPolicy.aucRsv[1]       =   0x0U;
    stFcMntnPolicy1.stPolicy.enHighestPri    =   stPolicy.enHighestPri;
    stFcMntnPolicy1.stPolicy.enDonePri       =   stPolicy.enDonePri;
    stFcMntnPolicy1.stPolicy.enToPri         =   stPolicy.enToPri;
    memcpy(stFcMntnPolicy1.stPolicy.astFcPri, stPolicy.astFcPri, sizeof(stPolicy.astFcPri));

    PtrAddr                                     =   (VOS_UINT_PTR)(stPolicy.pAdjustForUpFunc);
    stFcMntnPolicy1.stPolicy.aulPolicyUpAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)(stPolicy.pAdjustForUpFunc);
    stFcMntnPolicy1.stPolicy.aulPolicyUpAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     =   (VOS_UINT_PTR)(stPolicy.pAdjustForDownFunc);
    stFcMntnPolicy1.stPolicy.aulPolicyDownAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)(stPolicy.pAdjustForDownFunc);
    stFcMntnPolicy1.stPolicy.aulPolicyDownAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    PtrAddr                                     =   (VOS_UINT_PTR)(stPolicy.pPostFunc);
    stFcMntnPolicy1.stPolicy.aulPolicyPostAddr[0]  = (VOS_UINT32)(PtrAddr & (~0U));   /* Low */
    pulOctet                                    = (VOS_UINT32 *)(stPolicy.pAdjustForDownFunc);
    stFcMntnPolicy1.stPolicy.aulPolicyPostAddr[1]  = (VOS_UINT32)(VOS_UINT_PTR)(pulOctet + 1);    /* High */

    /* 对FC_MNTN_TraceEvent的入参实际赋值 */
    memset(&stFcMntnPolicy2, 0, sizeof(FC_MNTN_POLICY_STRU));

    stFcMntnPolicy2.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stFcMntnPolicy2.ulSenderPid      = UEPS_PID_FLOWCTRL;
    stFcMntnPolicy2.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stFcMntnPolicy2.ulReceiverPid    = UEPS_PID_FLOWCTRL;
    stFcMntnPolicy2.ulLength         = (sizeof(FC_MNTN_POLICY_STRU) - VOS_MSG_HEAD_LENGTH);
    stFcMntnPolicy2.enMsgName        = ID_FC_MNTN_CPU_A_CPULOAD;

    stFcMntnPolicy2.stPolicy.enPolicyId      =   FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0;
    stFcMntnPolicy2.stPolicy.ucPriCnt        =   1;
    stFcMntnPolicy2.stPolicy.enHighestPri    =   FC_PRI_5;
    stFcMntnPolicy2.stPolicy.enDonePri       =   FC_PRI_4;
    stFcMntnPolicy2.stPolicy.enToPri         =   FC_PRI_5;
    memcpy(stFcMntnPolicy2.stPolicy.astFcPri, stPolicy.astFcPri, sizeof(stPolicy.astFcPri));

    stFcMntnPolicy2.stPolicy.aulPolicyUpAddr[0]  = 0x1000;   /* Low */
    stFcMntnPolicy2.stPolicy.aulPolicyUpAddr[1]  = 0;    /* High */

    stFcMntnPolicy2.stPolicy.aulPolicyDownAddr[0]  = 0x2000;   /* Low */
    stFcMntnPolicy2.stPolicy.aulPolicyDownAddr[1]  = 0;    /* High */

    stFcMntnPolicy2.stPolicy.aulPolicyPostAddr[0]  = 0x3000;   /* Low */
    stFcMntnPolicy2.stPolicy.aulPolicyPostAddr[1]  = 0;    /* High */

    /* 比较FC_MNTN_TraceEvent的入参 */
    if (memcmp(&stFcMntnPolicy2,&stFcMntnPolicy1,sizeof(FC_MNTN_POLICY_STRU)))
    {
        return 1;
    }

    return 0;

}

/*****************************************************************************
 函 数 名  : stub_FC_MNTN_TraceCpuLoad
 功能描述  : 函数FC_MNTN_TraceCpuLoad的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_MNTN_TraceCpuLoad(void)
{
    FC_MNTN_EVENT_TYPE_ENUM_UINT16 enMsgName;
    VOS_UINT32  ulCpuLoad;
    VOS_UINT32  ulRslt;


    enMsgName = ID_FC_MNTN_CPU_A_CPULOAD;
    ulCpuLoad = 50;

    ulRslt = FC_MNTN_TraceCpuLoad(enMsgName, ulCpuLoad);

    if(0 == ulRslt)
    {
        return 0;
    }

    return -1;

}

/*****************************************************************************
 函 数 名  : stub_FC_MNTN_TraceDrvAssemPara
 功能描述  : 函数FC_MNTN_TraceDrvAssemPara的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_MNTN_TraceDrvAssemPara(void)
{
    FC_DRV_ASSEM_PARA_STRU stDrvAssenPara;
    VOS_UINT32  ulRslt;

    memset(&stDrvAssenPara, 1, sizeof(FC_DRV_ASSEM_PARA_STRU));

    ulRslt = FC_MNTN_TraceDrvAssemPara(&stDrvAssenPara);

    if(0 == ulRslt)
    {
        return 0;
    }

    return -1;

}

/*****************************************************************************
 函 数 名  : stub_FC_MNTN_TraceDrvAssemPara
 功能描述  : 函数FC_MNTN_TraceDrvAssemPara的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_IsPolicyEnable(int ulPointPolicyMask, short enModemId)
{
    int ret = 0;

    g_stFcCfg.ulFcEnbaleMask = 0x7F;

    ret = FC_IsPolicyEnable(ulPointPolicyMask, enModemId);

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_IsPolicyEnable_end
 功能描述  : 函数FC_MNTN_TraceDrvAssemPara的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
void stub_FC_IsPolicyEnable_end(void)
{
    int ret = 0;

    g_stFcCfg.ulFcEnbaleMask = 0;

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_RegPoint
 功能描述  : 函数FC_FC_RegPoint的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int stub_FC_RegPoint(void *pstFcRegPoint)
{
    int ret = 0;

    ret = FC_RegPoint((FC_REG_POINT_STRU  *)pstFcRegPoint);

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_SetFcEnableMsk
 功能描述  : 打桩设置g_stFcCfg.ulFcEnbaleMask的函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SetFcEnableMsk(int mask)
{
    g_stFcCfg.ulFcEnbaleMask = mask;
}

/*****************************************************************************
 函 数 名  : stub_FC_RegPoint
 功能描述  : 函数FC_FC_RegPoint的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_DeRegPoint(char FcId,short ModemId)
{
    int ret = 0;
    FC_REG_POINT_STRU                  stFcRegPoint;

    stFcRegPoint.enModemId = 0;
    stFcRegPoint.enPolicyId = 3;
    stFcRegPoint.enFcId = 1;
    stFcRegPoint.enFcPri = 1;
    stFcRegPoint.pSetFunc = 0x1000;
    stFcRegPoint.pClrFunc = 0x2000;
    stFcRegPoint.pRstFunc = 0x3000;

    FC_POINT_Add(&stFcRegPoint);

    ret = FC_DeRegPoint(FcId, ModemId);

    if(1 == ret)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_RegPoint
 功能描述  : 函数FC_FC_RegPoint的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_ChangePoint(char FcId,char PolicyId,char Pri,short ModemId)
{
    int ret = 0;

    ret = FC_ChangePoint(FcId,PolicyId,Pri,ModemId);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_Get
 功能描述  : 函数FC_POINT_Get的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Get_MaxPointNum(char FcId)
{
    int ret = 0;
    FC_POINT_STRU *pRslt;

    g_stFcPointMgr.ulPointNum = FC_MAX_POINT_NUM;

    pRslt = FC_POINT_Get(FcId);

    if (VOS_NULL_PTR == pRslt)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_Get
 功能描述  : 函数FC_POINT_Get的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Get_Succ(char FcId)
{
    int ret = 0;
    FC_POINT_STRU *pRslt;

    g_stFcPointMgr.ulPointNum = 2;
    g_stFcPointMgr.astFcPoint[0].enFcId = 0;
    g_stFcPointMgr.astFcPoint[0].enFcId = 3;

    pRslt = FC_POINT_Get(FcId);

    if (VOS_NULL_PTR == pRslt)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_Get
 功能描述  : 函数FC_POINT_Get的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Get_Fail(char FcId)
{
    int ret = 0;
    FC_POINT_STRU *pRslt;

    g_stFcPointMgr.ulPointNum = 2;
    g_stFcPointMgr.astFcPoint[0].enFcId = 0;
    g_stFcPointMgr.astFcPoint[0].enFcId = 5;

    pRslt = FC_POINT_Get(FcId);

    if (VOS_NULL_PTR == pRslt)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_Add
 功能描述  : 函数FC_POINT_Add的A核UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Add(void)
{
    int ret = 0;
    FC_REG_POINT_STRU                  stFcRegPoint;

    stFcRegPoint.enModemId = 0;
    stFcRegPoint.enPolicyId = 1;
    stFcRegPoint.enFcId = 3;
    stFcRegPoint.enFcPri = 5;
    stFcRegPoint.pSetFunc = 0x1000;
    stFcRegPoint.pClrFunc = 0x2000;
    stFcRegPoint.pRstFunc = 0x3000;


    ret = FC_POINT_Add(&stFcRegPoint);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_SetPointNum
 功能描述  : 设置g_stFcPointMgr中pointNum个数的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
void  stub_FC_POINT_SetPointNum(int Num)
{
    g_stFcPointMgr.ulPointNum = Num;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_SetPointNum
 功能描述  : 设置g_stFcPointMgr中pointNum个数的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
void  stub_FC_POINT_Add_SetPointInfo(char FcId)
{
    g_stFcPointMgr.ulPointNum = 2;
    g_stFcPointMgr.astFcPoint[0].enFcId = 0;
    g_stFcPointMgr.astFcPoint[1].enFcId = FcId;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_Del
 功能描述  : FC_POINT_Del的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Del(char FcId)
{
    int ret = 0;

    ret = FC_POINT_Del(FcId);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_SetFc
 功能描述  : FC_POINT_SetFc的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_SetFc(unsigned int PolicyMask, char FcId)
{
    int ret = 0;

    ret = FC_POINT_SetFc(PolicyMask, FcId);

    return ret;
}

VOS_UINT32 SetFlowCtrlTmp(VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    return 0;
}
VOS_UINT32 ClearFlowCtrlTmp(VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    return 0;
}
VOS_UINT32 ResetFlowCtrlTmp(VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    return 0;
}
VOS_UINT32 FC_POLICY_ADJUST_FOR_UP_FUNC_TEMP(FC_PRI_ENUM_UINT8 enPointPri, FC_ID_ENUM_UINT8 enFcId)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_SetFc_SetPoint
 功能描述  : FC_POINT_SetFc的设置流控点UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
void stub_FC_POINT_SetFc_SetPoint(unsigned int PolicyMask, char FcId, int FcMask, short ModemId,void *pSetFunc, void *pClrFunc)
{
    g_stFcPointMgr.ulPointNum = 1;

    g_stFcPointMgr.astFcPoint[0].enFcId = FcId;
    g_stFcPointMgr.astFcPoint[0].enModemId = ModemId;
    g_stFcPointMgr.astFcPoint[0].ulPolicyMask = PolicyMask;
    g_stFcPointMgr.astFcPoint[0].ulFcMask = FcMask;
    g_stFcPointMgr.astFcPoint[0].ulParam1 = 0;
    g_stFcPointMgr.astFcPoint[0].ulParam2 = 0;

    if (NULL == pSetFunc)
    {
        g_stFcPointMgr.astFcPoint[0].pSetFunc = NULL;
    }
    else
    {
        g_stFcPointMgr.astFcPoint[0].pSetFunc = SetFlowCtrlTmp;
    }

    if (NULL == pClrFunc)
    {
        g_stFcPointMgr.astFcPoint[0].pClrFunc = NULL;
    }
    else
    {
        g_stFcPointMgr.astFcPoint[0].pClrFunc = ClearFlowCtrlTmp;
    }


    g_stFcPointMgr.astFcPoint[0].pRstFunc = ResetFlowCtrlTmp;

}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_ClrFc
 功能描述  : FC_POINT_ClrFc的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_ClrFc(unsigned int PolicyMask, char FcId)
{
    int ret = 0;

    ret = FC_POINT_ClrFc(PolicyMask, FcId);

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_Reg
 功能描述  : FC_POINT_Reg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Reg(void)
{
    int ret = 0;
    FC_REG_POINT_STRU                  stFcRegPoint;

    stFcRegPoint.enModemId = 0;
    stFcRegPoint.enPolicyId = 1;
    stFcRegPoint.enFcId = 3;
    stFcRegPoint.enFcPri = 5;
    stFcRegPoint.pSetFunc = 0x1000;
    stFcRegPoint.pClrFunc = 0x2000;
    stFcRegPoint.pRstFunc = 0x3000;

    ret = FC_POINT_Reg(&stFcRegPoint);
    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_DeReg
 功能描述  : FC_POINT_DeReg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_DeReg(char FcId, short ModemId)
{
    int ret = 0;

    ret = FC_POINT_DeReg(FcId, ModemId);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_DeReg
 功能描述  : FC_POINT_DeReg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int  stub_FC_POINT_Change(char FcId, char PolicyId, char NewPri, short ModemId)
{
    int ret = 0;

    ret = FC_POINT_Change(FcId, PolicyId, NewPri, ModemId);
    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POINT_DeReg
 功能描述  : FC_POINT_DeReg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_TrimInvalidPri(char DonePri)
{
    FC_POLICY_STRU  FcPolicy;
    FcPolicy.enDonePri = DonePri;

    FcPolicy.astFcPri[DonePri].ucValid = VOS_FALSE;
    if (DonePri > FC_PRI_1)
    {
        FcPolicy.astFcPri[DonePri--].ucValid = VOS_TRUE;
    }

    FC_POLICY_TrimInvalidPri(&FcPolicy);

    if (FcPolicy.enDonePri == DonePri)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_UpWithOnePri
 功能描述  : FC_POLICY_UpWithOnePri的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_UpWithOnePri(char FcIdCnt)
{
    int ret = 0;

    FC_POLICY_STRU                     FcPolicy;
    FC_PRI_STRU                        stPri;

    stPri.ucFcIdCnt = FcIdCnt;

    ret = FC_POLICY_UpWithOnePri(&FcPolicy, &stPri);

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_DownWithOnePri
 功能描述  : FC_POLICY_DownWithOnePri的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_DownWithOnePri(char FcIdCnt)
{
    int ret = 0;

    FC_POLICY_STRU                     FcPolicy;
    FC_PRI_STRU                        stPri;

    stPri.ucFcIdCnt = FcIdCnt;

    ret = FC_POLICY_DownWithOnePri(&FcPolicy, &stPri);

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_Up
 功能描述  : FC_POLICY_Up的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_Up(char DonePri, char HighestPri, char Valid )
{
    int ret = 0;
    FC_POLICY_STRU stPolicy;
    char pri;

    stPolicy.enDonePri = DonePri;
    stPolicy.enHighestPri = HighestPri;

    if (HighestPri <= DonePri)
    {
        return 0;
    }

    pri = DonePri;
    while(pri < HighestPri)
    {
        stPolicy.astFcPri[pri].ucValid = PS_FALSE;
        pri++;
    }

    if (PS_TRUE == Valid)
    {
        stPolicy.astFcPri[DonePri + 1].ucValid = PS_TRUE;
    }

    ret = FC_POLICY_Up(&stPolicy);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_UpToTargetPri
 功能描述  : FC_POLICY_UpToTargetPri的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_UpToTargetPri(char DonePri, char TargetPri, char Valid )
{
    int ret = 0;
    FC_POLICY_STRU stPolicy;
    char pri;

    stPolicy.enDonePri = DonePri;

    if (TargetPri <= DonePri)
    {
        return 0;
    }

    pri = DonePri;
    while(pri < TargetPri)
    {
        stPolicy.astFcPri[pri].ucValid = PS_FALSE;
        pri++;
    }

    if (PS_TRUE == Valid)
    {
        stPolicy.astFcPri[DonePri + 1].ucValid = PS_TRUE;
    }

    ret = FC_POLICY_UpToTargetPri(&stPolicy, TargetPri);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_Down
 功能描述  : FC_POLICY_Down的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_Down(char DonePri, char Valid )
{
    int ret = 0;
    char Pri;

    FC_POLICY_STRU stFcPolicy;

    stFcPolicy.enDonePri = DonePri;

    Pri = DonePri;
    while(Pri > FC_PRI_NULL)
    {
        stFcPolicy.astFcPri[Pri].ucValid = VOS_FALSE;

        Pri--;
    }

    if (Valid == PS_TRUE)
    {
        stFcPolicy.astFcPri[DonePri].ucValid = PS_TRUE;
    }

    ret = FC_POLICY_Down(&stFcPolicy);

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_DownToTargetPri
 功能描述  : FC_POLICY_DownToTargetPri的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_DownToTargetPri(char DonePri, char TargetPri, char Valid )
{
    int ret = 0;
    FC_POLICY_STRU stPolicy;
    char pri;

    stPolicy.enDonePri = DonePri;

    if (TargetPri >= DonePri)
    {
        return 0;
    }

    pri = DonePri;
    while(pri > TargetPri)
    {
        stPolicy.astFcPri[pri].ucValid = PS_FALSE;
        pri--;
    }

    if (PS_TRUE == Valid)
    {
        stPolicy.astFcPri[DonePri].ucValid = PS_TRUE;
    }

    ret = FC_POLICY_DownToTargetPri(&stPolicy, TargetPri);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_UpdateHighestPri
 功能描述  : FC_POLICY_UpdateHighestPri的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_UpdateHighestPri(char Valid )
{
    int ret = 0;
    char Pri;

    FC_POLICY_STRU stPolicy;

    memset(&stPolicy, 0, sizeof(FC_POLICY_STRU));

    stPolicy.enHighestPri = FC_PRI_NULL;

    for (Pri = FC_PRI_1; Pri < FC_PRI_BUTT; Pri++)
    {
        stPolicy.astFcPri[Pri].ucValid   = VOS_FALSE;

        if (VOS_TRUE == Valid)
        {
            stPolicy.astFcPri[Pri].ucValid   = Valid;
        }
    }

    FC_POLICY_UpdateHighestPri(&stPolicy);

    if (FC_PRI_NULL != stPolicy.enHighestPri)
    {
        ret = 1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_AddPointForPri
 功能描述  : FC_POLICY_AddPointForPri的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_AddPointForPri(char Valid, char Cnt, char PointPri, char FcId)
{
    int ret = 1;
    FC_POLICY_STRU stPolicy = {0};

	if (FC_PRI_BUTT > PointPri)
	{
		stPolicy.astFcPri[PointPri].ucFcIdCnt = Cnt;
		stPolicy.astFcPri[PointPri].ucValid = Valid;

		stPolicy.astFcPri[PointPri].aenFcId[2] = 3;
	}

    ret = FC_POLICY_AddPointForPri(&stPolicy, FcId, PointPri);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_AddPointForPri
 功能描述  : FC_POLICY_AddPointForPri的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_DelPointForPri(char Cnt, char PointPri, char FcId)
{
    int ret = 1;
    FC_POLICY_STRU stPolicy = {0};

	if (FC_PRI_BUTT > PointPri)
	{
		stPolicy.astFcPri[PointPri].ucFcIdCnt = Cnt;

		stPolicy.astFcPri[PointPri].aenFcId[0] = 3;
	}

    ret = FC_POLICY_DelPointForPri(&stPolicy, FcId, PointPri);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_AddPoint
 功能描述  : FC_POLICY_AddPoint的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_AddPoint(void *pAdjustForUpFunc, char PointPri, char DonePri)
{
    char PolicyId = 3;
    char FcId = 3;
    int ret = 0;

    g_astFcPolicy[PolicyId].pAdjustForUpFunc = (FC_POLICY_ADJUST_FOR_UP_FUNC *)pAdjustForUpFunc;
    g_astFcPolicy[PolicyId].enDonePri = DonePri;

    ret = FC_POLICY_AddPoint(PolicyId, FcId, PointPri);

    if (1 == ret)
    {
        ret = -1;
    }

    stub_FC_POLICY_Init_MemSet();

    FC_POLICY_Init();

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_GetPriWithFcId
 功能描述  : FC_POLICY_GetPriWithFcId的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_GetPriWithFcId(char FcId, char TestcaseNum)
{
    char PolicyId = 3;
    int ret = FC_PRI_BUTT;
    char PriLoop;
    char FcIdIndexLoop;

    if (1 == TestcaseNum)
    {
        for (PriLoop = FC_PRI_1; PriLoop < FC_PRI_BUTT; PriLoop++)
        {
            g_astFcPolicy[PolicyId].astFcPri[PriLoop].ucFcIdCnt = (FC_MAX_POINT_NUM + 1);
        }
    }
    else if (2 == TestcaseNum)
    {
        for (PriLoop = FC_PRI_1; PriLoop < FC_PRI_BUTT; PriLoop++)
        {
            g_astFcPolicy[PolicyId].astFcPri[PriLoop].ucFcIdCnt = 5;

            for (FcIdIndexLoop = 0; FcIdIndexLoop < g_astFcPolicy[PolicyId].astFcPri[PriLoop].ucFcIdCnt; FcIdIndexLoop++)
            {
                g_astFcPolicy[PolicyId].astFcPri[PriLoop].aenFcId[FcIdIndexLoop] == (FcId+1);
            }
        }

    }
    else if (3 == TestcaseNum)
    {
        for (PriLoop = FC_PRI_1; PriLoop < FC_PRI_BUTT; PriLoop++)
        {
            g_astFcPolicy[PolicyId].astFcPri[PriLoop].ucFcIdCnt = (FC_MAX_POINT_NUM + 1);

            for (FcIdIndexLoop = 0; FcIdIndexLoop < g_astFcPolicy[PolicyId].astFcPri[PriLoop].ucFcIdCnt; FcIdIndexLoop++)
            {
                g_astFcPolicy[PolicyId].astFcPri[PriLoop].aenFcId[FcIdIndexLoop] == (FcId+1);
            }
        }

        g_astFcPolicy[PolicyId].astFcPri[2].ucFcIdCnt = 3;

        g_astFcPolicy[PolicyId].astFcPri[2].aenFcId[1] = FcId;

    }
    else
    {

    }

    ret = FC_POLICY_GetPriWithFcId(PolicyId, FcId);

    if (FC_PRI_BUTT == ret)
    {
        ret = 0;
    }
    else
    {
        ret = 1;
    }

    stub_FC_POLICY_Init_MemSet();

    FC_POLICY_Init();

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_DelPoint
 功能描述  : FC_POLICY_DelPoint的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_DelPoint(void *pAdjustForUpFunc)
{
    char PolicyId = 3;
    char FcId = 3;
    int ret = 0;

    g_astFcPolicy[PolicyId].pAdjustForDownFunc = (FC_POLICY_ADJUST_FOR_DOWN_FUNC *)pAdjustForUpFunc;

    ret = FC_POLICY_DelPoint(PolicyId, FcId);

    if (1 == ret)
    {
        ret = -1;
    }

    stub_FC_POLICY_Init_MemSet();

    FC_POLICY_Init();

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_ChangePoint
 功能描述  : FC_POLICY_ChangePoint的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_ChangePoint(void *pAdjustForUpFunc, char DonePri, char NewPri, char OldPri)
{
    char PolicyId = 3;
    char FcId = 3;
    int ret = 0;

    g_astFcPolicy[PolicyId].pAdjustForUpFunc = (FC_POLICY_ADJUST_FOR_UP_FUNC *)pAdjustForUpFunc;
    g_astFcPolicy[PolicyId].enDonePri = DonePri;

    ret = FC_POLICY_ChangePoint(PolicyId,FcId,OldPri,NewPri);

    if (1 == ret)
    {
        ret = -1;
    }

    stub_FC_POLICY_Init_MemSet();

    FC_POLICY_Init();

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_GetPriCnt
 功能描述  : FC_POLICY_GetPriCnt的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_GetPriCnt(int Cnt)
{
    FC_POLICY_STRU stFcPolicy;
    int ret = -1;

    stFcPolicy.ucPriCnt = Cnt;

    ret = FC_POLICY_GetPriCnt(&stFcPolicy);

    if (Cnt == ret)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : stub_FC_POLICY_Init
 功能描述  : FC_POLICY_Init的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_POLICY_Init(void)
{
    int ret = -1;

    FC_POLICY_STRU    astFcPolicy[FC_PRIVATE_POLICY_ID_BUTT] = {0};

    FC_POLICY_ID_ENUM_UINT8             enPolicyId;

    for (enPolicyId = 0; enPolicyId < FC_PRIVATE_POLICY_ID_BUTT; enPolicyId++)
    {
        astFcPolicy[enPolicyId].enPolicyId    = (VOS_UINT8)enPolicyId;
    }

    stub_FC_POLICY_Init_MemSet();
    FC_POLICY_Init();

    ret = memcmp(&astFcPolicy[0], &g_astFcPolicy[0], sizeof(FC_POLICY_STRU)*FC_PRIVATE_POLICY_ID_BUTT);

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_CFG_CheckCpuParam
 功能描述  : FC_CFG_CheckCpuParam的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CFG_CheckCpuParam(int CpuOverLoadVal, int CpuUnderLoadVal)
{
    int ret = 0;

    FC_CFG_CPU_STRU stFcCfgCpu;

    stFcCfgCpu.ulCpuOverLoadVal  = CpuOverLoadVal;
    stFcCfgCpu.ulCpuUnderLoadVal = CpuUnderLoadVal;

    ret = FC_CFG_CheckCpuParam(&stFcCfgCpu);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_CFG_CheckMemParam
 功能描述  : FC_CFG_CheckMemParam的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CFG_CheckMemParam(int ThresholdCnt, int SetThreshold, int StopThreshold)
{
    int ret = 1;
    int ThresholdLoop;

    FC_CFG_MEM_STRU stFcCfgMem;

    stFcCfgMem.ulThresholdCnt = ThresholdCnt;

	if ( FC_MEM_THRESHOLD_LEV_BUTT > ThresholdCnt )
	{
		for ( ThresholdLoop = 0 ; ThresholdLoop < stFcCfgMem.ulThresholdCnt ; ThresholdLoop++ )
		{
			stFcCfgMem.astThreshold[ThresholdLoop].ulSetThreshold = 10;
			stFcCfgMem.astThreshold[ThresholdLoop].ulStopThreshold = 20;
		}

		stFcCfgMem.astThreshold[1].ulSetThreshold = SetThreshold;
		stFcCfgMem.astThreshold[1].ulStopThreshold = StopThreshold;
	}


    ret = FC_CFG_CheckMemParam(&stFcCfgMem);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_CFG_CheckUlRateParam
 功能描述  : FC_CFG_CheckUlRateParam的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CFG_CheckUlRateParam(char Cnt)
{
    FC_CFG_UM_UL_RATE_STRU stFcCfgUmUlRate;
    int ret = 1;

    stFcCfgUmUlRate.ucRateCnt = Cnt;

    ret = FC_CFG_CheckUlRateParam(&stFcCfgUmUlRate);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_CFG_CheckParam
 功能描述  : FC_CFG_CheckParam的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CFG_CheckParam(int TimerLen)
{
    FC_CFG_STRU stFcCfg;
    int ret = 0;

    stFcCfg.stFcCfgCpuA.ulSmoothTimerLen = TimerLen;

    ret = FC_CFG_CheckParam(&stFcCfg);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_CFG_SetDefaultValue
 功能描述  : FC_CFG_SetDefaultValue的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CFG_SetDefaultValue(void)
{
    FC_CFG_STRU  stFcCfg;
    int ret = 0;

    ret = FC_CFG_SetDefaultValue(&stFcCfg);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_CFG_SetNvValue
 功能描述  : FC_CFG_SetNvValue的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CFG_SetNvValue(void)
{
    FC_CFG_NV_STRU  stFcCfgNvInit = {0};
    FC_CFG_NV_STRU  stFcCfgNv = {0};
    int ret = 1;

    FC_CFG_CPU_STRU stFcCfgCpuA;
    FC_CFG_CPU_STRU stFcCfgCpuC;
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgMem[FC_MEM_THRESHOLD_LEV_BUTT];
    unsigned long FcCfgMemThresholdCnt = 9;
    FC_CFG_UM_UL_RATE_STRU stFcCfgUmUlRateForCpu;
    FC_CFG_UM_UL_RATE_STRU stFcCfgUmUlRateForTmp;


    memcpy(&stFcCfgNv.stFcCfgCpuA, &stFcCfgCpuA, sizeof(FC_CFG_CPU_STRU));
    memcpy(&stFcCfgNv.stFcCfgMem[0], &stFcCfgMem[0], sizeof(FC_CFG_MEM_THRESHOLD_STRU) * FC_MEM_THRESHOLD_LEV_BUTT);
    memcpy(&stFcCfgNv.stFcCfgCpuC, &stFcCfgCpuC, sizeof(FC_CFG_CPU_STRU));
    memcpy(&stFcCfgNv.stFcCfgUmUlRateForCpu, &stFcCfgUmUlRateForCpu, sizeof(FC_CFG_UM_UL_RATE_STRU));
    memcpy(&stFcCfgNv.stFcCfgUmUlRateForTmp, &stFcCfgUmUlRateForTmp, sizeof(FC_CFG_UM_UL_RATE_STRU));



    memcpy(&g_stFcCfg, &stFcCfgNvInit, sizeof(FC_CFG_STRU));

    ret = FC_CFG_SetNvValue(&stFcCfgNv);

    //ret = memcmp(&g_stFcCfg, &stFcCfgNv, sizeof(FC_CFG_STRU));

    memcpy(&g_stFcCfg, &stFcCfgNvInit, sizeof(FC_CFG_STRU));

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_CFG_Init
 功能描述  : FC_CFG_Init的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CFG_Init(void)
{
    int ret = 1;

    FC_CFG_STRU stFcCfg = {0};

    memcpy(&g_stFcCfg, &stFcCfg, sizeof(FC_CFG_STRU));

    ret = FC_CFG_Init();

    if (1 == ret)
    {
        ret = -1;
    }

    memcpy(&g_stFcCfg, &stFcCfg, sizeof(FC_CFG_STRU));

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_SndCpuMsg
 功能描述  : FC_SndCpuMsg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SndCpuMsg(void)
{
    int ret = 0;

    FC_MSG_TYPE_ENUM_UINT16 usMsgName = ID_FC_REG_POINT_IND;
    VOS_UINT32              ulCpuLoad = 20;
    VOS_UINT32              ulUlRate = 300;
    VOS_UINT32              ulDlRate = 500;

    ret = FC_SndCpuMsg(usMsgName, ulCpuLoad, ulUlRate, ulDlRate);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_SndRegPointMsg
 功能描述  : FC_SndRegPointMsg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SndRegPointMsg(void)
{
    int ret = 0;

    FC_REG_POINT_STRU   stFcRegPoint;

    ret = FC_SndRegPointMsg(&stFcRegPoint);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_SndDeRegPointMsg
 功能描述  : FC_SndDeRegPointMsg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SndDeRegPointMsg(void)
{
    int ret = 0;

    FC_ID_ENUM_UINT8        enFcId = 3;
    MODEM_ID_ENUM_UINT16    enModemId = 0;

    ret = FC_SndDeRegPointMsg(enFcId, enModemId);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_SndChangePointMsg
 功能描述  : FC_SndChangePointMsg的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SndChangePointMsg(void)
{
    int ret = 0;

    FC_ID_ENUM_UINT8            enFcId = 3;
    FC_POLICY_ID_ENUM_UINT8     enPolicyId = 5;
    FC_PRI_ENUM_UINT8           enPri = 3;
    MODEM_ID_ENUM_UINT16        enModemId = 0;

    ret = FC_SndChangePointMsg(enFcId, enPolicyId, enPri, enModemId);

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_CommInit
 功能描述  : FC_CommInit的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_CommInit(void)
{
    int ret = 0;

    ret = FC_CommInit();

    if (1 == ret)
    {
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_CommInit
 功能描述  : FC_CommInit的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SetDebugLev(unsigned int ulLev)
{
    int ret = 0;

    ret = FC_SetDebugLev(ulLev);

    if (ulLev == ret)
    {
        ret = 1;
    }

    FC_SetDebugLev(0);

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_SetFcEnableMask
 功能描述  : FC_SetFcEnableMask的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SetFcEnableMask(unsigned int ulEnableMask)
{
    int ret = 0;

    ret = FC_SetFcEnableMask(ulEnableMask);

    if (ulEnableMask == ret)
    {
        ret = 1;
    }

    FC_SetFcEnableMask(0);

    return ret;
}

/*****************************************************************************
 函 数 名  : stub_FC_SetThreshold
 功能描述  : FC_SetThreshold的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_SetThreshold(int PolicyId,int Param1)
{
    int ret = 0;
    int SetThreshold = 100;
    int StopThreshold = 200;
    FC_CFG_STRU  stFcCfg = {0};

    memcpy(&g_stFcCfg, &stFcCfg, sizeof(FC_CFG_STRU));

    FC_SetThreshold(PolicyId,Param1,SetThreshold,StopThreshold);

    switch (PolicyId)
    {
        case FC_POLICY_ID_MEM:
            if ((g_stFcCfg.stFcCfgMem.astThreshold[Param1].ulSetThreshold  == SetThreshold) && (g_stFcCfg.stFcCfgMem.astThreshold[Param1].ulStopThreshold == StopThreshold))
            {
                ret = 1;
            }
            break;
        case FC_POLICY_ID_CPU_A:
            if ((g_stFcCfg.stFcCfgCpuA.ulCpuOverLoadVal  == SetThreshold) && (g_stFcCfg.stFcCfgCpuA.ulCpuUnderLoadVal == StopThreshold))
            {
                ret = 1;
            }
            break;
        case FC_POLICY_ID_CDS:
            ret = 1;
            break;
        case FC_POLICY_ID_CST:
            if ((g_stFcCfg.stFcCfgCst.stThreshold.ulSetThreshold == SetThreshold) && (g_stFcCfg.stFcCfgCst.stThreshold.ulStopThreshold == StopThreshold))
            {
                ret = 1;
            }
            break;
        case FC_POLICY_ID_GPRS:
            if ( 0 == Param1)
            {
                if ((g_stFcCfg.stFcCfgGprs.stThresholdMemCnt.ulSetThreshold == SetThreshold) && (g_stFcCfg.stFcCfgGprs.stThresholdMemCnt.ulStopThreshold == StopThreshold))
                {
                    ret = 1;
                }
            }
            else
            {
                if ((g_stFcCfg.stFcCfgGprs.stThresholdMemSize.ulSetThreshold == SetThreshold) && (g_stFcCfg.stFcCfgGprs.stThresholdMemSize.ulStopThreshold == StopThreshold))
                {
                    ret = 1;
                }
            }
            break;
        case FC_POLICY_ID_TMP:
            ret = 1;
            break;
        case FC_POLICY_ID_CPU_C:
            if ((g_stFcCfg.stFcCfgCpuC.ulCpuOverLoadVal == SetThreshold) && (g_stFcCfg.stFcCfgCpuC.ulCpuUnderLoadVal == StopThreshold))
            {
                ret = 1;
            }
            break;

        default:
            break;
    }

    memcpy(&g_stFcCfg, &stFcCfg, sizeof(FC_CFG_STRU));

    return ret;

}

/*****************************************************************************
 函 数 名  : stub_FC_Help
 功能描述  : FC_Help的UT桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : w68271
    修改内容   : 新生成函数

*****************************************************************************/
int stub_FC_Help(int PointNum, int Valid, int FcIdCnt)
{
    int FcIdLoop;
    int FcPri;
    int PolicyId;
    FC_POINT_STRU                      *pFcPoint;
    FC_POLICY_STRU                     *pPolicy;
    FC_PRI_STRU                        *pPri;
    int ret = -1;

    stub_FC_POINT_MemSet();
    stub_FC_POLICY_Init_MemSet();

    g_stFcPointMgr.ulPointNum = PointNum;

    for (FcIdLoop = 0; FcIdLoop < g_stFcPointMgr.ulPointNum; FcIdLoop++)
    {
        pFcPoint    = &(g_stFcPointMgr.astFcPoint[FcIdLoop]);

        pFcPoint->pSetFunc = 0x1000;
        pFcPoint->pClrFunc = 0x2000;

    }

    for (PolicyId = FC_PRIVATE_POLICY_ID_MEM_MODEM_0; PolicyId < FC_PRIVATE_POLICY_ID_BUTT; PolicyId++)
    {
        pPolicy = FC_POLICY_Get(PolicyId);

        pPolicy->pAdjustForUpFunc = 0x1000;
        pPolicy->pAdjustForDownFunc = 0x2000;
        pPolicy->pPostFunc = 0x3000;

        for (FcPri = FC_PRI_1; FcPri < FC_PRI_BUTT; FcPri++)
        {
            pPri    = &(pPolicy->astFcPri[FcPri]);

            pPri->ucValid = Valid;

            pPri->ucFcIdCnt = FcIdCnt;
        }
    }

    ret = FC_Help();

    stub_FC_POINT_MemSet();
    stub_FC_POLICY_Init_MemSet();

    return ret;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif