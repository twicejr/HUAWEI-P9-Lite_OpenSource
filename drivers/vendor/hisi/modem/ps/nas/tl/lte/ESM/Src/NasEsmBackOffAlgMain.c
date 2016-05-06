/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmBackoffAlgMain.c
  Description     : ESM模块Back-off算法实现
  History         :
     1.sunjitan 00193151      2015-01-12  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmBackOffAlgMain.h"
#include    "NasEmmPubUGlobal.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMBACKOFFALGMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMBACKOFFALGMAIN_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


NAS_BACKOFF_ALGORITHM_ENTITY_STRU  g_stBackOffEntity;


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_BACKOFF_OperateInit
 Description     : 调用Back-off算法的操作接口初始化，此接口只能LNAS使用
 Input           : NAS_BACKOFF_INIT_INFO_STRU           初始化入参
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_OperateInit
(
    NAS_BACKOFF_INIT_INFO_STRU            *pstInitPara
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateInit Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateInit_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)pstInitPara;

    (VOS_VOID)NAS_BACKOFF_MainTaskEntry(NAS_BACKOFF_NETRAT_LTE, NAS_BACKOFF_OPERATE_TYPE_INIT, pstOpPara);

    return;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_OperateJudgment
 Description     : 调用Back-off算法的操作接口判定
 Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32       接入技术
                   NAS_BACKOFF_JUDGMENT_PARA_STRU       判定入参
 Output          : None
 Return          : VOS_UINT32     0表示不允许发起，1表示允许发起。
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_BACKOFF_OperateJudgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateJudgment Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateJudgment_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)pstJudgmentPara;

    /* 不满足DAM条件，并且NV开关也没打开，不使用Back-off算法 */
    if((NAS_ESM_YES != NAS_EMM_IsDamConfitionSatisfied())
        &&(NAS_BACKOFF_ALG_VALID != g_stBackOffEntity.ucBackOffAlgFlag))
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateJudgment Backoff close");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateJudgment_ENUM, ESM_BACKOFF_CLOSE);
        return NAS_BACKOFF_SUCC;
    }

    /* 如果读USIM卡定时器在运行，说明卡未读完，不使用Back-off算法 */
    if(PS_FALSE != NAS_ESM_IsWaitBackOffUsimCnfTimerRunning())
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateJudgment wait Usim Cnf");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateJudgment_ENUM, ESM_WAIT_USIM_CNF);
        return NAS_BACKOFF_SUCC;
    }

    /* 满足DAM条件或NV开关打开 */
    return NAS_BACKOFF_MainTaskEntry(enNetRat, NAS_BACKOFF_OPERATE_TYPE_JUDGMENT, pstOpPara);
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_OperateMaintain
 Description     : 调用Back-off算法的操作接口维护
 Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32       接入技术
                   NAS_BACKOFF_MAINTAIN_PARA_STRU       维护入参
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_OperateMaintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateMaintain Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateMaintain_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)pstMaintainPara;

    /* 不满足DAM条件，并且NV开关也没打开，不使用Back-off算法 */
    if((NAS_ESM_YES != NAS_EMM_IsDamConfitionSatisfied())
        &&(NAS_BACKOFF_ALG_VALID != g_stBackOffEntity.ucBackOffAlgFlag))
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateMaintain Backoff close");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateMaintain_ENUM, ESM_BACKOFF_CLOSE);
        return;
    }

    /* 如果读USIM卡定时器在运行，说明卡未读完，不使用Back-off算法 */
    if(PS_FALSE != NAS_ESM_IsWaitBackOffUsimCnfTimerRunning())
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateMaintain wait Usim Cnf");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateMaintain_ENUM, ESM_WAIT_USIM_CNF);
        return;
    }

    /* 满足DAM条件或NV开关打开 */
    (VOS_VOID)NAS_BACKOFF_MainTaskEntry(enNetRat, NAS_BACKOFF_OPERATE_TYPE_MAINTAIN, pstOpPara);

    return;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_OperateReset
 Description     : 调用Back-off算法的操作接口复位
 Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32       接入技术
                   NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  复位原因
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_OperateReset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateReset Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateReset_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)penResetCause;

    (VOS_VOID)NAS_BACKOFF_MainTaskEntry(enNetRat, NAS_BACKOFF_OPERATE_TYPE_RESET, pstOpPara);

    return;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_GetAlgFlagAddr
 Description     : 获取算法开关标识地址
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT8*   算法开关地址
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT8* NAS_BACKOFF_GetAlgFlagAddr(VOS_VOID)
{
    return &g_stBackOffEntity.ucBackOffAlgFlag;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_GetApnEntityAddr
 Description     : 获取APN实体地址
 Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32       接入技术
                   VOS_UINT32                           APN实体索引
 Output          : None
 Return          : NAS_BACKOFF_APN_ENTITY_STRU*         APN实体地址
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
NAS_BACKOFF_APN_ENTITY_STRU* NAS_BACKOFF_GetApnEntityAddr
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32  enNetRat,
    VOS_UINT32                      ulIndex
)
{
    return &g_stBackOffEntity.stNetRatEntity[enNetRat].stApnEntity[ulIndex];
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_GetCommParaAddr
 Description     : 获取算法公共参数地址
 Input           : VOS_VOID
 Output          : None
 Return          : NAS_BACKOFF_COMM_PARA_STRU*        公共参数地址
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
NAS_BACKOFF_COMM_PARA_STRU* NAS_BACKOFF_GetCommParaAddr(VOS_VOID)
{
    return &g_stBackOffEntity.stCommPara;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_GetPdpPermCauseListAddr
 Description     : 获取算法PDP永久拒绝原因值列表地址
 Input           : VOS_VOID
 Output          : None
 Return          : NAS_BACKOFF_COMM_PARA_STRU*   永久拒绝原因值列表地址
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
NAS_CONFIG_PDP_PERM_CAUSE_STRU* NAS_BACKOFF_GetPdpPermCauseListAddr(VOS_VOID)
{
    return &g_stBackOffEntity.stPdpPermCause;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_GetPdpTempCauseListAddr
 Description     : 获取算法PDP临时拒绝原因值列表地址
 Input           : VOS_VOID
 Output          : None
 Return          : NAS_CONFIG_PDP_TEMP_CAUSE_STRU*   临时拒绝原因值列表地址
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
NAS_CONFIG_PDP_TEMP_CAUSE_STRU* NAS_BACKOFF_GetPdpTempCauseListAddr(VOS_VOID)
{
    return &g_stBackOffEntity.stPdpTempCause;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_SetBackOffState
 Description     : 设置Back-off算法状态
 Input           : NAS_BACKOFF_STATE_ENUM_UINT8  目标状态
                   NAS_BACKOFF_APN_ENTITY_STRU   APN实体
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_SetBackOffState
(
    NAS_BACKOFF_STATE_ENUM_UINT8     enDestState,
    NAS_BACKOFF_APN_ENTITY_STRU     *pstApnEntity
)
{
    pstApnEntity->enState = enDestState;
    return ;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_MainTaskEntry
 Description     : Back-off算法主任务入口
 Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32       接入技术
                   NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32 操作类型
                   NAS_BACKOFF_OPERATE_PARA_STRU        操作提供的入参
 Output          : None
 Return          : VOS_UINT32
                   根据操作类型的不同，执行不同的动作。
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_BACKOFF_MainTaskEntry
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32             enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32       enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU             *pstOpPara
)
{
    VOS_UINT32                          ulRslt  = NAS_BACKOFF_FAIL;
    VOS_UINT8                           ulIndex = 0;

    /* 操作类型可维可测信息输出到HIDS，包括初始化、判定、维护和复位 */
    NAS_BACKOFF_SndOmLogOperateInfo(enNetRat, enOpType, pstOpPara);

    switch(enOpType)
    {
        case NAS_BACKOFF_OPERATE_TYPE_INIT:

            /* 可维可测，输出初始化之前算法公共参数到HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();

            NAS_BACKOFF_Init(&pstOpPara->u.stInitPara);

            /* 可维可测，输出初始化之后算法公共参数到HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            ulRslt = NAS_BACKOFF_SUCC;
            break;

        case NAS_BACKOFF_OPERATE_TYPE_JUDGMENT:

            /* 可维可测，输出判定之前算法公共参数和APN实体列表到HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            NAS_BACKOFF_SndOmLogApnEntityList(enNetRat);
            ulRslt = NAS_BACKOFF_Judgment(enNetRat, &pstOpPara->u.stJudgmentPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_MAINTAIN:

            /* 可维可测，输出维护之前算法公共参数和APN实体列表到HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            NAS_BACKOFF_SndOmLogApnEntityList(enNetRat);

            NAS_BACKOFF_Maintain(enNetRat, &pstOpPara->u.stMaintainPara);

            /* 可维可测，输出维护之后APN实体列表到HIDS */
            NAS_BACKOFF_SndOmLogApnEntityList(enNetRat);
            ulRslt = NAS_BACKOFF_SUCC;
            break;

        case NAS_BACKOFF_OPERATE_TYPE_RESET:

            NAS_BACKOFF_Reset(enNetRat, &pstOpPara->u.enResetCause);

            /* 可维可测，输出复位之后公共参数和所有接入技术的算法实体状态到HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            for(ulIndex = 0; ulIndex < NAS_BACKOFF_NETRAT_ENUM_BUTT; ulIndex++)
            {
                NAS_BACKOFF_SndOmLogApnEntityList(ulIndex);
            }
            ulRslt = NAS_BACKOFF_SUCC;
            break;

        default:

            NAS_ESM_INFO_LOG("NAS_BACKOFF_MainTaskEntry:Operate type ERR!");
            TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_MainTaskEntry_ENUM, LNAS_PARAM_INVALID);
            ulRslt = NAS_BACKOFF_FAIL;
    }

    return ulRslt;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_Init
Description     : Back-off算法根据接入技术类型，执行相应接入技术的初始化。
Input           : NAS_BACKOFF_INIT_INFO_STRU       入参
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_Init
(
    NAS_BACKOFF_INIT_INFO_STRU  *pstInitInfo
)
{
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU   stNvDamPara;
    VOS_UINT8                             *pstBackOffAlgFlag = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_COMM_PARA_STRU            *pstCommPara       = NAS_BACKOFF_NULL_PTR;

    NAS_ESM_MEM_SET_S(  &stNvDamPara,
                        sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU),
                        0,
                        sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU));

    NAS_ESM_MEM_SET_S(  &g_stBackOffEntity,
                        sizeof(NAS_BACKOFF_ALGORITHM_ENTITY_STRU),
                        0,
                        sizeof(NAS_BACKOFF_ALGORITHM_ENTITY_STRU));

    pstBackOffAlgFlag = NAS_BACKOFF_GetAlgFlagAddr();
    pstCommPara       = NAS_BACKOFF_GetCommParaAddr();

    if(NAS_BACKOFF_NVIM_SUCC != NAS_BACKOFF_ReadNvDamBackOffPara(&stNvDamPara))
    {
        /* 读NV失败，设置NV中读取出的数据全为0，其他初始化成默认值，此时只有DAM生效时才能使用算法 */
        NAS_ESM_MEM_SET_S(  &stNvDamPara,
                            sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU),
                            0,
                            sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU));
    }

    /* 输出NV参数到HIDS，用于可维可测 */
    NAS_BACKOFF_SndOmLogNvPara(&stNvDamPara);

    NAS_BACKOFF_InitPdpRejCauseList(&stNvDamPara);

    NAS_BACKOFF_InitCommParaFx(&stNvDamPara, pstInitInfo);

    NAS_BACKOFF_InitCommParaFb(pstCommPara);

    /* 初始化惩罚定时器上下限 */
    NAS_BACKOFF_InitCommParaTimerPara(pstCommPara);

    /* Back-off算法在NV中未打开 */
    if(NAS_BACKOFF_BIT_NO_SILT == stNvDamPara.bitOpBackOffAlg)
    {
        *pstBackOffAlgFlag = NAS_BACKOFF_ALG_INVALID;
    }
    else
    {
        /* 算法打开 */
        *pstBackOffAlgFlag = NAS_BACKOFF_ALG_VALID;
    }

    return;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_Judgment
Description     : Back-off算法根据接入技术类型和APN信息进行判定是否允许发起PDP激活。
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32   接入技术
                  NAS_BACKOFF_JUDGMENT_PARA_STRU   待判定的APN
Output          : None
Return          : VOS_UINT32
                    NAS_BACKOFF_SUCC 允许发起
                    NAS_BACKOFF_FAIL 不允许发起
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_BACKOFF_Judgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
)
{
    NAS_BACKOFF_QUERY_RESULT_STRU  stQueryResult;

    NAS_ESM_MEM_SET_S(  &stQueryResult,
                        sizeof(NAS_BACKOFF_QUERY_RESULT_STRU),
                        0,
                        sizeof(NAS_BACKOFF_QUERY_RESULT_STRU));

    /* 查找发现APN对应的实体不存在，允许发起 */
    if(NAS_BACKOFF_SUCC != NAS_BACKOFF_QueryInfo(enNetRat, pstJudgmentPara, &stQueryResult))
    {
        return NAS_BACKOFF_SUCC;
    }

    /* 实体存在但算法处于未激活态，允许发起 */
    if(NAS_BACKOFF_STATE_INACTIVE == stQueryResult.enState)
    {
        return NAS_BACKOFF_SUCC;
    }

    /* 实体存在算法处于激活态，惩罚定时器未运行，允许发起 */
    if(NAS_BACKOFF_FOBID_TIMER_STATE_STOP == stQueryResult.enTimeStatus)
    {
        return NAS_BACKOFF_SUCC;
    }

    return NAS_BACKOFF_FAIL;

}
/*****************************************************************************
Function Name   : NAS_BACKOFF_Maintain
Description     : Back-off算法根据接入技术、APN和失败原因，
                  执行相应算法实体的维护。
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32       接入技术
                  APP_ESM_APN_INFO_STRU                需维护实体的APN信息
                  VOS_UINT8                            失败原因值
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_Maintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    /* PDP激活结果非法 */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM_BUTT <= pstMaintainPara->enPdpResult)
    {
        return;
    }

    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_SUCC == pstMaintainPara->enPdpResult)
    {
        NAS_BACKOFF_PdpActiveSuccProc(enNetRat, pstMaintainPara);
        return;
    }

    /* 失败原因值不需要维护直接返回，需要维护执行PDP失败的相应处理，仅超时或有效CN REJ原因值时需维护 */
    if((NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP == pstMaintainPara->enPdpResult)
        ||((NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ == pstMaintainPara->enPdpResult)
            &&(NAS_BACKOFF_PDP_REJ_TYPE_OTHER != NAS_BACKOFF_GetPdpCnRejType(pstMaintainPara->ucCnCause))))
    {
        NAS_BACKOFF_PdpActiveFailProc(enNetRat, pstMaintainPara);
    }

    return;
}
/*****************************************************************************
Function Name   : NAS_BACKOFF_Reset
Description     : Back-off算法复位。
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32        接入技术
                  NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32   复位原因
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_Reset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
)
{
    VOS_UINT32                           ulIndex           = 0;
    VOS_UINT32                           ulNetRat          = 0;
    NAS_BACKOFF_COMM_PARA_STRU          *pstCommPara       = NAS_BACKOFF_NULL_PTR;
    VOS_UINT8                           *pstBackOffAlgFlag = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       *pstPdpPermCauseList = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       *pstPdpTempCauseList = NAS_BACKOFF_NULL_PTR;

    /* 复位原因错误 */
    if(NAS_BACKOFF_RESET_CAUSE_ENUM_BUTT <= *penResetCause)
    {
        return;
    }

    /* PLMN改变，清空当前接入技术下的所有APN实体 */
    if(NAS_BACKOFF_RESET_CAUSE_PLMN_CHANGE == *penResetCause)
    {
        for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
        {
            NAS_BACKOFF_ClearApnEntity(enNetRat, ulIndex);
        }
    }
    else
    {
        /* 关机 */
        pstBackOffAlgFlag   = NAS_BACKOFF_GetAlgFlagAddr();
        pstCommPara         = NAS_BACKOFF_GetCommParaAddr();
        pstPdpPermCauseList = NAS_BACKOFF_GetPdpPermCauseListAddr();
        pstPdpTempCauseList = NAS_BACKOFF_GetPdpTempCauseListAddr();

        /* 关闭算法 */
        *pstBackOffAlgFlag  = NAS_BACKOFF_ALG_INVALID;

        /* 清空算法公共参数 */
        NAS_ESM_MEM_SET_S(  pstCommPara,
                            sizeof(NAS_BACKOFF_COMM_PARA_STRU),
                            0,
                            sizeof(NAS_BACKOFF_COMM_PARA_STRU));

        /* 清空拒绝原因值列表 */
        NAS_ESM_MEM_SET_S(  pstPdpPermCauseList,
                            sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU),
                            0,
                            sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU));
        NAS_ESM_MEM_SET_S(  pstPdpTempCauseList,
                            sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU),
                            0,
                            sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU));

        /* 不考虑当前接入技术，循环清空所有接入技术的所有APN实体 */
        for(ulNetRat = NAS_BACKOFF_NETRAT_LTE; ulNetRat < NAS_BACKOFF_NETRAT_ENUM_BUTT; ulNetRat++)
        {
            for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
            {
                NAS_BACKOFF_ClearApnEntity(ulNetRat, ulIndex);
            }
        }
    }

    return;

}
/*****************************************************************************
Function Name   : NAS_BACKOFF_QueryInfo
Description     : Back-off算法查询功能。
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32   接入技术
                  APP_ESM_APN_INFO_STRU*           APN
                  NAS_BACKOFF_QUERY_RESULT_STRU*   查询结果
Output          : None
Return          : VOS_UINT32
                  0 查询成功；1 查询失败
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_BACKOFF_QueryInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    APP_ESM_APN_INFO_STRU              *pstApn,
    NAS_BACKOFF_QUERY_RESULT_STRU      *pstQueryResult
)
{
    VOS_UINT32                          ulIndex      = 0;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
    {
        pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

        /* 当前APN实体有效且APN长度相同，比较APN值 */
        if((NAS_BACKOFF_APN_ENTITY_FLAG_VALID == pstApnEntity->enValidFlag)
            &&(pstApnEntity->stApnInfo.ucApnLen == pstApn->ucApnLen))
        {
            /* APN值相同则找到 */
            if(NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(pstApn, &pstApnEntity->stApnInfo, pstApn->ucApnLen))
            {
                break;
            }
        }
    }

    /* 找到 */
    if(ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM)
    {
        /* 设置查询结果: 索引、算法状态、惩罚定时器状态 */
        pstQueryResult->ulIndex      = ulIndex;
        pstQueryResult->enState      = pstApnEntity->enState;
        pstQueryResult->enTimeStatus = NAS_BACKOFF_GetForbidTimerState(pstApnEntity);

        return NAS_BACKOFF_SUCC;
    }

    /* 未找到 */
    return NAS_BACKOFF_FAIL;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_PdpActiveSuccProc
Description     : PDP激活成功时的处理
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32   接入技术
                  NAS_BACKOFF_MAINTAIN_PARA_STRU*  APN
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_PdpActiveSuccProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    NAS_BACKOFF_QUERY_RESULT_STRU   stQueryResult;

    NAS_ESM_MEM_SET_S(  &stQueryResult,
                        sizeof(NAS_BACKOFF_QUERY_RESULT_STRU),
                        0,
                        sizeof(NAS_BACKOFF_QUERY_RESULT_STRU));

    /* 查询当前APN相关实体是否存在 */
    if(NAS_BACKOFF_SUCC == NAS_BACKOFF_QueryInfo(enNetRat, &pstMaintainPara->stApnInfo, &stQueryResult))
    {
        /* 存在则清空相应的APN实体 */
        NAS_BACKOFF_ClearApnEntity(enNetRat, stQueryResult.ulIndex);
    }

    return;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_PdpActiveFailProc
Description     : PDP激活失败时的处理
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32   接入技术
                  NAS_BACKOFF_MAINTAIN_PARA_STRU*  维护信息
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_PdpActiveFailProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;
    VOS_UINT32                          ulAllocIndex = 0;
    NAS_BACKOFF_QUERY_RESULT_STRU       stQueryResult;

    NAS_ESM_MEM_SET_S(  &stQueryResult,
                        sizeof(NAS_BACKOFF_QUERY_RESULT_STRU),
                        0 ,
                        sizeof(NAS_BACKOFF_QUERY_RESULT_STRU));

    /* 查找发现APN对应的实体存在 */
    if(NAS_BACKOFF_SUCC == NAS_BACKOFF_QueryInfo(enNetRat, &pstMaintainPara->stApnInfo, &stQueryResult))
    {
        /* 找到APN实体，根据当前实体的算法状态进行相应处理 */
        pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, stQueryResult.ulIndex);

        if(NAS_BACKOFF_STATE_INACTIVE == pstApnEntity->enState)
        {
            NAS_BACKOFF_InactiveProc(enNetRat, stQueryResult.ulIndex, \
                        pstMaintainPara->enPdpResult, pstMaintainPara->ucCnCause);
        }
        else
        {
            NAS_BACKOFF_ActiveProc(enNetRat, stQueryResult.ulIndex, \
                        pstMaintainPara->enPdpResult, pstMaintainPara->ucCnCause);
        }

        return;
    }

    /* APN实体不存在，分配一个实体 */
    if(NAS_BACKOFF_SUCC != NAS_BACKOFF_AllocApnEntity(enNetRat, &ulAllocIndex))
    {
        /* 实体已满，分配失败直接返回 */
        return;
    }

    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulAllocIndex);

    /* 设置APN实体被启用 */
    pstApnEntity->enValidFlag        = NAS_BACKOFF_APN_ENTITY_FLAG_VALID;

    /* 保存APN */
    pstApnEntity->stApnInfo.ucApnLen = pstMaintainPara->stApnInfo.ucApnLen;

    NAS_ESM_MEM_CPY_S(  pstApnEntity->stApnInfo.aucApnName,
                        APP_MAX_APN_LEN,
                        pstMaintainPara->stApnInfo.aucApnName,
                        pstMaintainPara->stApnInfo.ucApnLen);

    /* 进入INACTIVE态 */
    NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_INACTIVE, pstApnEntity);

    /* 执行INACTIVE态的处理 */
    NAS_BACKOFF_InactiveProc(enNetRat, ulAllocIndex, \
                pstMaintainPara->enPdpResult, pstMaintainPara->ucCnCause);

    return;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_InactiveProc
Description     : Back-off算法未激活态下的处理。
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32      接入技术
                  VOS_UINT32                          APN实体索引
                  NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8 失败原因
                  VOS_UINT8                           网侧原因值
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_InactiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
)
{
    NAS_BACKOFF_PDP_REJ_TYPE_ENUM8      enPdpRejType = NAS_BACKOFF_PDP_REJ_TYPE_ENUM_BUTT;
    NAS_BACKOFF_COMM_PARA_STRU         *pstCommPara  = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    pstCommPara  = NAS_BACKOFF_GetCommParaAddr();
    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    /* 如果失败原因为超时，对FnIgnore进行加1，然后判断是否满足进入ACTIVE态 */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP == enPdpResult)
    {
        pstApnEntity->stInactiveInfo.ulFnIgnore++;

        /* 计数达到FbIgnore，直接进入ACTIVE态，启动惩罚定时器 */
        if(pstApnEntity->stInactiveInfo.ulFnIgnore >= pstCommPara->ucFbIgnore)
        {
            /* 设置状态为ACTIVE，执行ACTIVE处理 */
            NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_ACTIVE, pstApnEntity);
            NAS_BACKOFF_ActiveProc(enNetRat, ulIndex,\
                        NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP, NAS_BACKOFF_PDP_CAUSE_NULL);
        }

        return;
    }

    enPdpRejType = NAS_BACKOFF_GetPdpCnRejType(ucCnCause);

    /* 根据是PERM REJ还是TEMP REJ对计数进行处理，OTHER REJ不会走到这里，由调用者保证 */
    if(NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ == enPdpRejType)
    {
        pstApnEntity->stInactiveInfo.ulFnPerm++;
    }
    else
    {
        pstApnEntity->stInactiveInfo.ulFnTemp++;
    }

    /* 检查计数，若达到FbPerm或FbTemp，直接进入ACTIVE态，启动惩罚定时器 */
    if((pstApnEntity->stInactiveInfo.ulFnPerm >= pstCommPara->ucFbPerm)
        ||(pstApnEntity->stInactiveInfo.ulFnTemp >= pstCommPara->ucFbTemp))
    {
        /* 设置状态为ACTIVE，执行ACTIVE处理 */
        NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_ACTIVE, pstApnEntity);
        NAS_BACKOFF_ActiveProc(enNetRat, ulIndex,\
                    NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ, ucCnCause);
    }

    return;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_ActiveProc
Description     : Back-off算法激活态下的处理。
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32   接入技术
                  VOS_UINT32                       APN实体索引
                  NAS_BACKOFF_PDP_FAIL_CAUSE_ENUM8 失败原因
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_ActiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
)
{
    /* 如果失败原因为超时，启动Ignore惩罚定时器 */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP == enPdpResult)
    {
        NAS_BACKOFF_ForbidTimerStart(enNetRat, ulIndex, TI_NAS_ESM_BACKOFF_IGNORE_FORBID);
        return;
    }

    /* CN拒绝，一定是PERM REJ或TEMP REJ，启动相应定时器，其他REJ不会进入此函数，由调用者保证 */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ == enPdpResult)
    {
        if(NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ == NAS_BACKOFF_GetPdpCnRejType(ucCnCause))
        {
            NAS_BACKOFF_ForbidTimerStart(enNetRat, ulIndex, TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID);
        }
        else
        {
            NAS_BACKOFF_ForbidTimerStart(enNetRat, ulIndex, TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID);
        }
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_ReadNvDamParaPdpCauseList
 Description     : 读取AT&T定制需求参数NV项
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_BACKOFF_ReadNvDamBackOffPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU  *pstNvDamPara
)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = NAS_BACKOFF_NVIM_FAIL;

    /* 读NV */
    ulDataLen = sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU);
    ulRslt = LPs_NvimItem_Read(EN_NV_ID_BACKOFF_ALG_CONFIG,
                              (VOS_VOID *)pstNvDamPara,
                              ulDataLen);

    if(NAS_BACKOFF_NVIM_SUCC == ulRslt)
    {
        return NAS_BACKOFF_NVIM_SUCC;
    }

    NAS_ESM_INFO_LOG("NAS_BACKOFF_ReadNvDamBackOffPara: read NV Fail.");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_ReadNvDamBackOffPara_ENUM, LNAS_FAIL);
    return NAS_BACKOFF_NVIM_FAIL;

}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_InitPdpRejCauseList
 Description     : 初始化Back-off算法的PDP拒绝原因值列表
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_InitPdpRejCauseList
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU    *pstNvDamPara
)
{
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       *pstPdpPermCauseList = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       *pstPdpTempCauseList = NAS_BACKOFF_NULL_PTR;

    pstPdpPermCauseList = NAS_BACKOFF_GetPdpPermCauseListAddr();
    pstPdpTempCauseList = NAS_BACKOFF_GetPdpTempCauseListAddr();

    pstPdpPermCauseList->ucCauseNum = pstNvDamPara->stPdpPermCause.ucCauseNum;
    pstPdpTempCauseList->ucCauseNum = pstNvDamPara->stPdpTempCause.ucCauseNum;

    /* 如果存在原因值，初始化，如果原因值数目为0，则初始化成默认值 */
    if(0 != pstPdpPermCauseList->ucCauseNum)
    {
        NAS_ESM_MEM_CPY_S(  pstPdpPermCauseList->aucCause,
                            NAS_MM_MAX_PDP_REJ_CAUSE_NUM,
                            pstNvDamPara->stPdpPermCause.aucCause,
                            pstPdpPermCauseList->ucCauseNum*sizeof(VOS_UINT8));
    }
    else
    {
        /* 永久拒绝原因值, 默认值7个 #8#27#28#29#30#32#33 */
        pstPdpPermCauseList->ucCauseNum  = NAS_BACKOFF_PDP_PERM_CAUSE_DEFAULT_NUM;
        pstPdpPermCauseList->aucCause[0] = 0X08;
        pstPdpPermCauseList->aucCause[1] = 0X1B;
        pstPdpPermCauseList->aucCause[2] = 0X1C;
        pstPdpPermCauseList->aucCause[3] = 0X1D;
        pstPdpPermCauseList->aucCause[4] = 0X1E;
        pstPdpPermCauseList->aucCause[5] = 0X20;
        pstPdpPermCauseList->aucCause[6] = 0X21;
    }

    if(0 != pstPdpTempCauseList->ucCauseNum)
    {
        NAS_ESM_MEM_CPY_S(  pstPdpTempCauseList->aucCause,
                            NAS_MM_MAX_PDP_REJ_CAUSE_NUM,
                            pstNvDamPara->stPdpTempCause.aucCause,
                            pstPdpTempCauseList->ucCauseNum*sizeof(VOS_UINT8));
    }
    else
    {
        /* 临时拒绝原因值，默认值8个 #25#26#31#34#35#38#102#111 */
        pstPdpTempCauseList->ucCauseNum  = NAS_BACKOFF_PDP_TEMP_CAUSE_DEFAULT_NUM;
        pstPdpTempCauseList->aucCause[0] = 0X19;
        pstPdpTempCauseList->aucCause[1] = 0X1A;
        pstPdpTempCauseList->aucCause[2] = 0X1F;
        pstPdpTempCauseList->aucCause[3] = 0X22;
        pstPdpTempCauseList->aucCause[4] = 0X23;
        pstPdpTempCauseList->aucCause[5] = 0X26;
        pstPdpTempCauseList->aucCause[6] = 0X66;
        pstPdpTempCauseList->aucCause[7] = 0X6F;
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_InitCommParaFx
 Description     : 初始化Back-off算法的公共参数Fx
 Input           : None
 Output          : None
 Return          : VOS_UINT8     初始化公共参数Fx的结果
                   0  成功；  1 失败
 History         :
    1.    sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_InitCommParaFx
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU  *pstNvDamPara,
    NAS_BACKOFF_INIT_INFO_STRU            *pstInitInfo
)
{
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara       = NAS_BACKOFF_NULL_PTR;

    pstCommPara       = NAS_BACKOFF_GetCommParaAddr();

    /* 卡中参数有效 */
    if(NAS_BACKOFF_BIT_SILT == pstInitInfo->bitOpSimFxFlag)
    {
        pstCommPara->ucFxIgnore = pstInitInfo->ucSimFxIgnore;
        pstCommPara->ucFxPerm   = pstInitInfo->ucSimFxPerm;
        pstCommPara->ucFxTemp   = pstInitInfo->ucSimFxTemp;
    }
    else if(NAS_BACKOFF_BIT_SILT == pstNvDamPara->bitOpBackOffFx)
    {
        /* 卡中参数无效或读卡失败，NV中参数有效，使用NV中参数 */
        pstCommPara->ucFxIgnore = pstNvDamPara->stBackOffFx.ucFxIgnore;
        pstCommPara->ucFxPerm   = pstNvDamPara->stBackOffFx.ucFxPerm;
        pstCommPara->ucFxTemp   = pstNvDamPara->stBackOffFx.ucFxTemp;
    }
    else
    {
        /* 两种参数均无效，设置默认值 */
        pstCommPara->ucFxIgnore = NAS_ESM_BACKOFF_IGNORE_FX_DEFAULT_VALUE;
        pstCommPara->ucFxPerm   = NAS_ESM_BACKOFF_PERM_FX_DEFAULT_VALUE;
        pstCommPara->ucFxTemp   = NAS_ESM_BACKOFF_TEMP_FX_DEFAULT_VALUE;
    }

    /* 检查修正参数 */
    NAS_BACKOFF_CheckFx(pstCommPara);

    return;

}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_InitCommParaFb
 Description     : 初始化Back-off算法的公共参数Fb
 Input           : None
 Output          : None
 Return          : VOS_UINT8     初始化公共参数结果
 History         :
    1.    sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_InitCommParaFb
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
)
{
    pstCommPara->ucFbIgnore = NAS_BACKOFF_SelectFb(pstCommPara->ucFxIgnore);
    pstCommPara->ucFbPerm   = NAS_BACKOFF_SelectFb(pstCommPara->ucFxPerm);
    pstCommPara->ucFbTemp   = NAS_BACKOFF_SelectFb(pstCommPara->ucFxTemp);
    return;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_InitCommParaTimerPara
 Description     : 初始化Back-off算法的公共参数定时器上下限
 Input           : NAS_BACKOFF_COMM_PARA_STRU       公共参数
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_InitCommParaTimerPara
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
)
{
    /* 计算Ignore场景的定时器上下限 */
    NAS_BACKOFF_CalcTimerLenMinAndMax(pstCommPara->ucFxIgnore,
                     pstCommPara->ucFbIgnore, &pstCommPara->stFxIgnoreTimerInfo);

    /* 计算Perm场景的定时器上下限 */
    NAS_BACKOFF_CalcTimerLenMinAndMax(pstCommPara->ucFxPerm,
                     pstCommPara->ucFbPerm, &pstCommPara->stFxPermTimerInfo);

    /* 计算Temp场景的定时器上下限 */
    NAS_BACKOFF_CalcTimerLenMinAndMax(pstCommPara->ucFxTemp,
                     pstCommPara->ucFbTemp, &pstCommPara->stFxTempTimerInfo);

    return;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_CheckFx
 Description     : 检查Back-off算法Fx参数是否合法
 Input           : NAS_BACKOFF_COMM_PARA_STRU   公共参数
 Output          : None
 Return          : VOS_UINT8
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_CheckFx
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
)
{
    /* 启用Back-off算法，不能有Fx小于4，否则无法实现每15分钟
    至少可发起1次的条件，数值异常则修正为默认值 */
    if(NAS_BACKOFF_FX_MIN_VALUE > pstCommPara->ucFxIgnore)
    {
        pstCommPara->ucFxIgnore = NAS_ESM_BACKOFF_IGNORE_FX_DEFAULT_VALUE;
    }

    if(NAS_BACKOFF_FX_MIN_VALUE > pstCommPara->ucFxPerm)
    {
        pstCommPara->ucFxPerm = NAS_ESM_BACKOFF_PERM_FX_DEFAULT_VALUE;
    }

    if(NAS_BACKOFF_FX_MIN_VALUE > pstCommPara->ucFxTemp)
    {
        pstCommPara->ucFxTemp = NAS_ESM_BACKOFF_TEMP_FX_DEFAULT_VALUE;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_BACKOFF_SelectFb
 Description     : 选取Fb
                   ---------------------------
                   - Fx所处范围区间 - Fb取值 -
                   - [5,6]          - 1      -
                   - [7,10]         - 2      -
                   - [11,15]        - 4      -
                   - [16,20]        - 6      -
                   - [21,29]        - 8      -
                   - [30,255]       - Fx/3   -
                   ---------------------------
 Input           : VOS_UINT8   公共参数Fx
 Output          : None
 Return          : VOS_UINT8   Fb
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_BACKOFF_SelectFb(VOS_UINT8 ucFx)
{
    /* Fx值落在不同区间，选择不同的Fb */
    if(NAS_BACKOFF_FX_MIN_VALUE == ucFx)
    {
        return 0;
    }

    if((5 <= ucFx)&&(6 >= ucFx))
    {
        return 1;
    }

    if((7 <= ucFx)&&(10 >= ucFx))
    {
        return 2;
    }

    if((11 <= ucFx)&&(15 >= ucFx))
    {
        return 4;
    }

    if((16 <= ucFx)&&(20 >= ucFx))
    {
        return 6;
    }

    if((21 <= ucFx)&&(29 >= ucFx))
    {
        return 8;
    }

    /* 大于等于30时，选择3分之一作为Fb */
    if(30 <= ucFx)
    {
        return ucFx/3;/* [false alarm]:代码保证了符号的正确性 */
    }
    return 0;

}


/*****************************************************************************
 Function Name   : NAS_BACKOFF_CalcTimerLenMinAndMax
 Description     : 计算Back-off算法惩罚定时器上下限，单位: 毫秒
 Input           : VOS_UINT8                        ucFx
                   VOS_UINT8                        ucFb
 Output          : NAS_BACKOFF_TIMER_INFO_STRU   定时器上下限
 Return          : VOS_UINT8
 History         :
    1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_CalcTimerLenMinAndMax
(
    VOS_UINT8                           ucFx,
    VOS_UINT8                           ucFb,
    NAS_BACKOFF_TIMER_INFO_STRU        *pstTimerInfo
)
{
    VOS_UINT32                          ulFa;
    VOS_UINT32                          ulFm;

    /* ACTIVE态1小时内可以最多发起的次数Fa */
    ulFa = ucFx - ucFb;

    /* Tmin = min{15min , 60min/Fa}，如不能整除，误差在1ms，可以忽略 */
    pstTimerInfo->ulTminLen = \
        (NAS_BACKOFF_1HOUR_VALUE / ulFa) < NAS_BACKOFF_FORBID_TIMER_MAX_VALUE ? \
                       (NAS_BACKOFF_1HOUR_VALUE / ulFa) : NAS_BACKOFF_FORBID_TIMER_MAX_VALUE;

    /* 每15分钟可发起的最大次数 Fm = max{0.05*Fx , 1} */
    ulFm = (ucFx / 20) > 1 ? (ucFx / 20) : 1;

    /* Tmax = 15min/Fm，如不能整除，误差在1ms，可以忽略*/
    pstTimerInfo->ulTmaxLen = (NAS_BACKOFF_FORBID_TIMER_MAX_VALUE / ulFm);

    return;
}


/*****************************************************************************
Function Name   : NAS_BACKOFF_AllocNewApnEntity
Description     : 获取新的APN实体位置
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32   接入技术
                  VOS_UINT32*                          分配成功返回的索引值
Output          : None
Return          : VOS_UINT32
                  0 分配成功；1 分配失败
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_BACKOFF_AllocApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulIndex      = 0;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
    {
        pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

        if(NAS_BACKOFF_APN_ENTITY_FLAG_VALID != pstApnEntity->enValidFlag)
        {
            /* 找到未启用的APN实体，清空内容，将索引返回 */
            NAS_ESM_MEM_SET_S(  pstApnEntity ,
                                sizeof(NAS_BACKOFF_APN_ENTITY_STRU),
                                0 ,
                                sizeof(NAS_BACKOFF_APN_ENTITY_STRU));
            *pulIndex = ulIndex;
            return NAS_BACKOFF_SUCC;
        }
    }

    return NAS_BACKOFF_FAIL;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_GetPdpCnRejType
Description     : 获取PDP拒绝类型
Input           : NAS_BACKOFF_PDP_CAUSE_ENUM_UINT8   PDP拒绝原因值
Output          : None
Return          : VOS_UINT8   PDP拒绝类型
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_BACKOFF_GetPdpCnRejType(VOS_UINT8  ucCnCause)
{
    VOS_UINT32                          ulIndex = 0;
    NAS_CONFIG_PDP_PERM_CAUSE_STRU     *pstPdpPermCauseList = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU     *pstPdpTempCauseList = NAS_BACKOFF_NULL_PTR;

    pstPdpPermCauseList = NAS_BACKOFF_GetPdpPermCauseListAddr();
    pstPdpTempCauseList = NAS_BACKOFF_GetPdpTempCauseListAddr();

    /* 查找是否在Perm原因值列表中 */
    for(ulIndex = 0; ulIndex < pstPdpPermCauseList->ucCauseNum; ulIndex++)
    {
        if(ucCnCause == pstPdpPermCauseList->aucCause[ulIndex])
        {
            return NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ;
        }
    }

    /* 查找是否在Temp原因值列表中 */
    for(ulIndex = 0; ulIndex < pstPdpTempCauseList->ucCauseNum; ulIndex++)
    {
        if(ucCnCause == pstPdpTempCauseList->aucCause[ulIndex])
        {
            return NAS_BACKOFF_PDP_REJ_TYPE_TEMP_REJ;
        }
    }

    /* 全都未找到，是其他原因值 */
    return NAS_BACKOFF_PDP_REJ_TYPE_OTHER;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_ClearApnEntity
Description     : 清除APN实体信息
Input           : VOS_UINT32   APN实体索引
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_ClearApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex
)
{
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_TIMER_STRU         *pstTimer     = NAS_BACKOFF_NULL_PTR;

    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    pstTimer = &pstApnEntity->stActiveInfo.stBackoffTimer;

    /* 删除保存的APN */
    NAS_ESM_MEM_SET_S(  &pstApnEntity->stApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU),
                        0,
                        sizeof(APP_ESM_APN_INFO_STRU));

    /* 实体设置为无效 */
    pstApnEntity->enValidFlag = NAS_BACKOFF_APN_ENTITY_FLAG_INVALID;

    /* 当前APN实体对应的算法状态设置为未激活 */
    NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_INACTIVE, pstApnEntity);

    /* 清空未激活态相关信息 */
    NAS_ESM_MEM_SET_S(  &pstApnEntity->stInactiveInfo,
                        sizeof(NAS_BACKOFF_INACTIVE_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_INACTIVE_INFO_STRU));

    /* 停止惩罚定时器 */
    NAS_BACKOFF_ForbidTimerStop(enNetRat, ulIndex, pstTimer->enPara);

    return;
}

/*****************************************************************************
Function Name   : NAS_BACKOFF_ForbidTimerLenCalc
Description     : Back-off算法激活态下惩罚定时器长度计算
Input           : NAS_BACKOFF_TIMER_INFO_STRU  定时器信息
Output          : None
Return          : VOS_UINT32                   随机得到的定时器长度
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_BACKOFF_TimerLenRandom
(
    NAS_BACKOFF_TIMER_INFO_STRU       *pstTimerInfo
)
{
    VOS_UINT32                          ulTimerRandSize = 0;
    VOS_UINT32                          ulTimerLen      = 0;

    /* 计算出可随机的定时器时长偏移量范围 */
    ulTimerRandSize = pstTimerInfo->ulTmaxLen - pstTimerInfo->ulTminLen;

    /* 随机一个偏移量，加上定时器最小值即为定时器时长 */
    ulTimerLen = VOS_Rand(ulTimerRandSize) + pstTimerInfo->ulTminLen;

    return ulTimerLen;
}

/*****************************************************************************
Function Name   : NAS_BACKOFF_ForbidTimerLenCalc
Description     : Back-off算法激活态下惩罚定时器长度计算
Input           : NAS_TIMER_PARA_ENUM_UINT8   定时器类型
Output          : None
Return          : VOS_UINT32                  定时器长度
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_BACKOFF_ForbidTimerLenCalc
(
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                      ulTimerLen  = 0;
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara = NAS_BACKOFF_NULL_PTR;

    pstCommPara = NAS_BACKOFF_GetCommParaAddr();

    switch(enTimerType)
    {
        case TI_NAS_ESM_BACKOFF_IGNORE_FORBID:

            ulTimerLen = NAS_BACKOFF_TimerLenRandom(&pstCommPara->stFxIgnoreTimerInfo);
            break;

        case TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID:

            ulTimerLen = NAS_BACKOFF_TimerLenRandom(&pstCommPara->stFxPermTimerInfo);
            break;

        case TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID:

            ulTimerLen = NAS_BACKOFF_TimerLenRandom(&pstCommPara->stFxTempTimerInfo);
            break;

        default:
            break;
    }

    return ulTimerLen;

}

/*****************************************************************************
 Function Name  : NAS_BACKOff_ForbidTimerStart
 Discription    : 启动Back-off算法惩罚定时器
 Input          : NAS_BACKOFF_NETRAT_ENUM_UINT32  接入技术
                  VOS_UINT32                      APN实体索引
                  NAS_TIMER_PARA_ENUM_UINT8       定时器类型
 Output         : VOS_VOID
 Return         : None
 History:
      1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_ForbidTimerStart
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                      ulTimerLen   = NAS_BACKOFF_NULL;
    NAS_BACKOFF_TIMER_STRU         *pstTimerInfo = NAS_BACKOFF_NULL_PTR;
    VOS_UINT32                      ulTimerName  = 0;
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    /* 找到APN实体 */
    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    /*根据APN实体,获取相关联的定时器*/
    pstTimerInfo = &pstApnEntity->stActiveInfo.stBackoffTimer;

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_BACKOff_ForbidTimerStart:WARN: stop rel timer error!");
            TLPS_PRINT2LAYER_WARNING1(NAS_BACKOFF_ForbidTimerStart_ENUM, ESM_CALL_API_FAIL, 1);
            return;
        }
    }

    /*根据定时器不同类型，惩罚定时器长度不同*/
    ulTimerLen = NAS_BACKOFF_ForbidTimerLenCalc(enTimerType);
    if (ulTimerLen == NAS_BACKOFF_NULL)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_BACKOff_ForbidTimerStart:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_ForbidTimerStart_ENUM, 1);
        return;
    }

    /* 计算出定时器的NAME，因有多个接入技术，因此将索引值进行偏移处理，
    即: 对于GU的APN实体，对应的定时器ulIndex会增加偏移量NAS_BACKOFF_APN_ENTITY_MAX_NUM */
    ulTimerName = (NAS_BACKOFF_APN_ENTITY_MAX_NUM * enNetRat) + ulIndex;

    /* 设定定时器NAME和PARA */
    if (VOS_OK != PS_START_REL_TIMER(&(pstTimerInfo->hTimer),PS_PID_ESM,\
                                ulTimerLen,ulTimerName, (VOS_UINT32)enTimerType, VOS_RELTIMER_NOLOOP))
    {
          /*打印异常信息*/
          NAS_ESM_WARN_LOG("NAS_BACKOff_ForbidTimerStart:WARN: start timer error!");
          TLPS_PRINT2LAYER_WARNING1(NAS_BACKOFF_ForbidTimerStart_ENUM, ESM_CALL_API_FAIL, 2);
          return;
    }

    /*更新定时器开启信息和定时器类别*/
    pstTimerInfo->enPara = enTimerType;

    /*钩出当前的定时器信息 */
    NAS_ESM_SndOmEsmTimerStatus(NAS_ESM_TIMER_RUNNING, enTimerType, ulTimerLen);

    /* 打印定时器启动信息 */
    NAS_ESM_PrintTimeStartInfo(ulIndex, enTimerType);

    return;
}

/*****************************************************************************
 Function Name  : NAS_BACKOff_ForbidTimerStop
 Discription    : 停止Backoff算法惩罚定时器
 Input          : NAS_BACKOFF_NETRAT_ENUM_UINT32  接入技术
                  VOS_UINT32                      APN实体索引
                  NAS_TIMER_PARA_ENUM_UINT8       定时器类型
 Output         : VOS_VOID
 Return         : None
 History:
      1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_BACKOFF_ForbidTimerStop
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    NAS_BACKOFF_TIMER_STRU             *pstTimerInfo     = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity     = NAS_BACKOFF_NULL_PTR;
    VOS_UINT32                          ulTimerRemainLen = 0;

    /* 找到APN实体 */
    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    /*根据APN实体,获取相关联的定时器*/
    pstTimerInfo = &pstApnEntity->stActiveInfo.stBackoffTimer;

    /*定时器处于打开状态，则关闭，否则，忽略*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /* 获取当前定时器的剩余时间 */
        if (VOS_OK != VOS_GetRelTmRemainTime(&pstTimerInfo->hTimer, &ulTimerRemainLen))
        {
            ulTimerRemainLen = 0;
        }

        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&pstTimerInfo->hTimer))
        {
            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_BACKOFF_ForbidTimerStop:WARN: stop rel timer error!");
            TLPS_PRINT2LAYER_WARNING(NAS_BACKOFF_ForbidTimerStop_ENUM, ESM_CALL_API_FAIL);
            return;
        }

        /*钩出当前的定时器信息 */
        NAS_ESM_SndOmEsmTimerStatus(NAS_ESM_TIMER_STOPED, enTimerType, ulTimerRemainLen);

        /* 打印定时器关闭信息 */
        NAS_ESM_PrintTimeStopInfo(ulIndex, enTimerType);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_BACKOFF_GetForbidTimerState
Description     : 获取惩罚定时器运行状态
Input           : NAS_BACKOFF_APN_ENTITY_STRU   APN实体
Output          : None
Return          : VOS_UINT8   惩罚定时器运行状态
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_BACKOFF_GetForbidTimerState
(
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity
)
{
    if((NAS_BACKOFF_STATE_ACTIVE == pstApnEntity->enState)
        &&(VOS_NULL_PTR != pstApnEntity->stActiveInfo.stBackoffTimer.hTimer))
    {
        return NAS_BACKOFF_FOBID_TIMER_STATE_RUNNING;
    }
    else
    {
        return NAS_BACKOFF_FOBID_TIMER_STATE_STOP;
    }
}
/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogInitInfo
Description     : Back-off算法的Init操作可维可测信息
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32         接入技术
                  NAS_BACKOFF_OPERATE_PARA_STRU          操作参数
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogInitInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogInitInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogInitInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_INIT;

    NAS_ESM_MEM_CPY_S(  &pstMsg->stInitInfo,
                        sizeof(NAS_BACKOFF_INIT_INFO_STRU),
                        &pstOpPara->u.stInitPara,
                        sizeof(NAS_BACKOFF_INIT_INFO_STRU));

    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}
/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogJudgmentInfo
Description     : Back-off算法的Judgment操作可维可测信息
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32         接入技术
                  NAS_BACKOFF_OPERATE_PARA_STRU          操作参数
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogJudgmentInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogJudgmentInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogJudgmentInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_JUDGMENT;

    NAS_ESM_MEM_CPY_S(  &pstMsg->stJudgmentPara,
                        sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU),
                        &pstOpPara->u.stJudgmentPara,
                        sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));

    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}
/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogMaintainInfo
Description     : Back-off算法的Mainttain操作可维可测信息
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32         接入技术
                  NAS_BACKOFF_OPERATE_PARA_STRU          操作参数
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogMaintainInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_Maintain_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_Maintain_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_Maintain_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogMaintainInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogMaintainInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_BACKOFF_Maintain_OPERATE_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_Maintain_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_Maintain_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_MAINTAIN;

    NAS_ESM_MEM_CPY_S(  &pstMsg->stMaintainPara,
                        sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU),
                        &pstOpPara->u.stMaintainPara,
                        sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU));

    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}
/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogResetInfo
Description     : Back-off算法的Reset操作可维可测信息
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32         接入技术
                  NAS_BACKOFF_OPERATE_PARA_STRU          操作参数
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogResetInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_RESET_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_RESET_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_RESET_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogResetInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogResetInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_BACKOFF_RESET_OPERATE_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_RESET_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_RESET_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_RESET;

    NAS_ESM_MEM_CPY_S(  &pstMsg->enResetCause,
                        sizeof(NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32),
                        &pstOpPara->u.enResetCause,
                        sizeof(NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32));

    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}

/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogOperateInfo
Description     : Back-off算法的操作可维可测信息
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32         接入技术
                  NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32   操作类型
                  NAS_BACKOFF_OPERATE_PARA_STRU          操作参数
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogOperateInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32   enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{


    /* 根据不同的操作填充不同的消息ID和消息体 */
    switch(enOpType)
    {
        case NAS_BACKOFF_OPERATE_TYPE_INIT:

            NAS_BACKOFF_SndOmLogInitInfo(enNetRat,pstOpPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_JUDGMENT:

            NAS_BACKOFF_SndOmLogJudgmentInfo(enNetRat,pstOpPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_MAINTAIN:

            NAS_BACKOFF_SndOmLogMaintainInfo(enNetRat,pstOpPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_RESET:

            NAS_BACKOFF_SndOmLogResetInfo(enNetRat,pstOpPara);
            break;

        default:

            NAS_ESM_INFO_LOG("NAS_BACKOFF_SndOmLogOperatePara:Operate type ERR!");
            TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_SndOmLogResetInfo_ENUM, LNAS_PARAM_INVALID);
            break;
    }
    return;
}

/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogNvPara
Description     : Back-off算法的可维可测信息，输出读到的NV参数
Input           : PS_NV_DAM_CONFIG_PARA_STRU       NV参数
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogNvPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU         *pstNvDamPara
)
{
    NAS_BACKOFF_LOG_NV_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_NV_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_NV_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogNvPara: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogNvPara_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_BACKOFF_LOG_NV_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_LOG_NV_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_NV_INFO_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = NAS_ESM_OM_LOG_BACKOFF_NV_PARA;

    NAS_ESM_MEM_CPY_S(  &pstMsg->stBackOffFx,
                        sizeof(NAS_CONFIG_BACKOFF_FX_PARA_STRU),
                        &pstNvDamPara->stBackOffFx,
                        sizeof(NAS_CONFIG_BACKOFF_FX_PARA_STRU));
    NAS_ESM_MEM_CPY_S(  &pstMsg->stPdpPermCause,
                        sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU),
                        &pstNvDamPara->stPdpPermCause,
                        sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU));
    NAS_ESM_MEM_CPY_S(  &pstMsg->stPdpTempCause,
                        sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU),
                        &pstNvDamPara->stPdpTempCause,
                        sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;
}

/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogCommInfo
Description     : Back-off算法的可维可测信息，输出当前公共参数
Input           : VOS_VOID
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogCommInfo(VOS_VOID)
{
    NAS_BACKOFF_LOG_COMM_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_COMM_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_COMM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogCommInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogCommInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_BACKOFF_LOG_COMM_INFO_STRU),
                        0,
                        sizeof(NAS_BACKOFF_LOG_COMM_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_COMM_INFO_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = NAS_ESM_OM_LOG_BACKOFF_COMM_INFO;

    NAS_ESM_MEM_CPY_S(  &pstMsg->stCommPara,
                        sizeof(NAS_BACKOFF_COMM_PARA_STRU),
                        &g_stBackOffEntity.stCommPara,
                        sizeof(NAS_BACKOFF_COMM_PARA_STRU));
    NAS_ESM_MEM_CPY_S(  &pstMsg->stPdpPermCause,
                        sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU),
                        &g_stBackOffEntity.stPdpPermCause,
                        sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU));
    NAS_ESM_MEM_CPY_S(  &pstMsg->stPdpTempCause,
                        sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU),
                        &g_stBackOffEntity.stPdpTempCause,
                        sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;

}

/*****************************************************************************
Function Name   : NAS_BACKOFF_SndOmLogEntityState
Description     : Back-off算法的可维可测信息，输出对应接入技术的实体列表
Input           : NAS_BACKOFF_NETRAT_ENUM_UINT32    需输出列表的接入技术类型
Output          : None
Return          : VOS_VOID
History         :
   1.sunjitan 00193151      2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_BACKOFF_SndOmLogApnEntityList(NAS_BACKOFF_NETRAT_ENUM_UINT32 enNetRat)
{
    NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogApnEntityList: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogApnEntityList_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU),
                        0,
                        sizeof(NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = NAS_ESM_OM_LOG_BACKOFF_APN_ENTITY_LIST;

    pstMsg->enNetRat                    = enNetRat;

    NAS_ESM_MEM_CPY_S(  &pstMsg->stNetRatEntity,
                        sizeof(NAS_BACKOFF_NETRAT_ENTITY_STRU),
                        &g_stBackOffEntity.stNetRatEntity[enNetRat],
                        sizeof(NAS_BACKOFF_NETRAT_ENTITY_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


