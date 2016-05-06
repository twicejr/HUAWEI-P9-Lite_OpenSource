/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmEhsmMsgProc.c
    Description : 处理EHSM发给ESM的承载处理类消息
    History     :
     1.sunjitan 00193151    2015-06-16   Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmEhsmMsgProc.h"
#include    "NasEsmInclude.h"


/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_NASESMEHSMMSGPROC_C
#define    THIS_NAS_FILE_ID             NAS_FILE_ID_NASESMEHSMMSGPROC_C
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


/*****************************************************************************
  3 Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
NAS_ESM_EHRPD_ENTITY_STRU               g_stEsmEhrpdEntity;


/*****************************************************************************
 Function Name  : NAS_ESM_EhsmMsgDistr
 Description    : ESM模块EHSM消息处理函数
 Input          : VOS_VOID*              EHSM发来的消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmMsgDistr(
    VOS_VOID                           *pRcvMsg
)
{
    EHSM_ESM_MSG_HEADER_STRU           *pEhsmMsg  = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmMsgDistr_ENUM, LNAS_ENTRY);

    pEhsmMsg        = (EHSM_ESM_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息ID，调用相应的消息处理函数*/
    switch (pEhsmMsg->enMsgId)
    {
        case ID_EHSM_ESM_SYNC_PDN_INFO_IND:

            NAS_ESM_EhsmSyncPdnInfoMsgProc(pRcvMsg);

            /* 可维可测，上报HIDS实体状态 */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();
            break;

        case ID_EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY:

            /* 可维可测，上报HIDS实体清除承载之前的记录状态 */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();

            NAS_ESM_EhsmClearAllBearerNotifyMsgProc(pRcvMsg);
            break;

        default:

            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_EhsmMsgDistr:Warning:EHSM->SM,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmMsgDistr_ENUM, ESM_EHSM_MSGID_ERROR);
            break;
    }

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_InitEhrpdEntity
 Description    : ESM模块初始化EHRPD实体的处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_InitEhrpdEntity(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EHRPD_ENTITY_STRU          *pstEhrpdEntity      = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_InitEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_InitEhrpdEntity_ENUM, LNAS_ENTRY);

    pstEhrpdEntity = NAS_ESM_GET_EHRPD_ENTITY_ADDR();

    /* EHRPD实体处于等待恢复状态 */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* EHRPD承载记录总数为0 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()      = 0;

    pstEhrpdEntity->aucRsv[0]                     = 0;
    pstEhrpdEntity->aucRsv[1]                     = 0;

    /* 循环将每个PDN实体初始化 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);
        pstPdnEntity->ucUsedFlag        = PS_FALSE;
        pstPdnEntity->ucAttachPdnFlag   = PS_FALSE;
        pstPdnEntity->ucIsOnReconnFlag  = PS_FALSE;
        pstPdnEntity->ucRsv             = 0;
        pstPdnEntity->ulHandoverEpsbId  = 0;

        NAS_ESM_MEM_SET_S(  &pstPdnEntity->stNwMsgRecord,
                            sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU),
                            0,
                            sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

        NAS_ESM_MEM_SET_S(  &pstPdnEntity->stTimerInfo,
                            sizeof(NAS_ESM_TIMER_STRU),
                            0,
                            sizeof(NAS_ESM_TIMER_STRU));

        NAS_ESM_MEM_SET_S(  &pstPdnEntity->stEhPdnContextInfo,
                            sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU));
    }

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoMsgProc
 Description    : ESM模块收到ID_EHSM_ESM_SYNC_PDN_INFO_IND消息的处理
 Input          : VOS_VOID*             EHSM发来的消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoMsgProc(
    VOS_VOID                           *pRcvMsg
)
{
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg            = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, LNAS_ENTRY);

    pEhsmMsg        = (EHSM_ESM_SYNC_PDN_INFO_IND_STRU*)pRcvMsg;

    /* 状态不为挂起态，说明是异常，丢弃消息 */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* 根据EHSM发来的承载信息同步操作，分别进行处理 */
    switch (pEhsmMsg->enPdnOption)
    {
        case EHSM_ESM_PDN_OPT_CONNECTED:

            NAS_ESM_EhsmSyncPdnInfoConnectedProc(pEhsmMsg);
            break;

        case EHSM_ESM_PDN_OPT_MODIFIED:

            NAS_ESM_EhsmSyncPdnInfoModifiedProc(pEhsmMsg);
            break;

        case EHSM_ESM_PDN_OPT_DISCONNECTED:

            NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(pEhsmMsg);
            break;

        default:

            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc:Warning:EHSM->SM,Receive Abnormal PdnOption!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, ESM_EHSM_MSGID_ERROR);
            break;
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmClearAllBearerNotifyMsgProc
 Description    : ESM模块收到ID_EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY消息的处理
 Input          : VOS_VOID*             EHSM发来的消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmClearAllBearerNotifyMsgProc(
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllBearerNotifyMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmClearAllBearerNotifyMsgProc_ENUM, LNAS_ENTRY);

    /* 状态不为挂起态，说明是异常，丢弃消息 */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllBearerNotifyMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmClearAllBearerNotifyMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* 删除L下的所有承载 */
    NAS_ESM_ClearEsmResource();

    /* 删除所有之前记录的EHRPD承载 */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();

    /* 通知EMM执行本地DETACH */
    NAS_ESM_SndEmmClLocalDetachNotifyMsg();

    /* 通知RABM清除所有承载资源，包括LTE承载和EHRPD承载 */
    NAS_ESM_SndEsmRabmClearClBearerNotifyMsg();

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoConnectedProc
 Description    : ESM收到EHSM发来的承载CONN指示时的处理
 Input          : EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM发来的消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoConnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, LNAS_ENTRY);

    /* 如果是EHRPD下ATTACH的PDN连接，特殊处理 */
    if (PS_TRUE == pEhsmMsg->ulAttachFlag)
    {
        /* 删除L下的所有承载 */
        NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc();

        /* 删除所有之前记录的所有EHRPD承载 */
        NAS_ESM_ClearAllEhrpdPdnInfoProc();

        /* 通知EMM执行本地DETACH */
        NAS_ESM_SndEmmClLocalDetachNotifyMsg();

        /* 通知RABM清除所有承载资源，包括EHRPD和LTE的承载 */
        NAS_ESM_SndEsmRabmClearClBearerNotifyMsg();

        /* 分配一个PDN实体 */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: ATTACH PDN Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* 设置ATTACH FLAG标识 */
        NAS_ESM_SET_EHRPD_PDN_ENTITY_ATTACH_FLAG(ulIndex, PS_TRUE);

        /* 保存EHRPD承载信息 */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    else
    {
        /* 分配一个未启用的PDN信息实体 */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* 保存EHRPD承载信息 */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    /* 使用的PDN实体总数加1 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM() ++;

    /* 向RABM发送ID_ESM_ERABM_ACT_IND, 接入技术类型为EHRPD，不是恢复流程，填写EHRPD承载ID */
    NAS_ESM_SndEsmRabmActIndMsg(ESM_ERABM_INVALID_BEARER_ID, ESM_ERABM_BEARER_RAT_EHRPD, PS_FALSE, pEhsmMsg->ulEpsbId);

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoModifiedProc
 Description    : ESM收到EHSM发来的承载MODIFY指示时的处理
 Input          : EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM发来的消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoModifiedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoModifiedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoModifiedProc_ENUM, LNAS_ENTRY);

    /* 在EHRPD实体中根据EHRPD承载ID查找当前修改的PDN连接是否存在 */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* 按覆盖式处理，修改此PDN连接的信息 */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);

        /* 发送ID_ESM_ERABM_MDF_IND消息 */
        NAS_ESM_SndEsmRabmMdfIndMsg(pEhsmMsg->ulEpsbId, ESM_ERABM_BEARER_RAT_EHRPD);
    }
    else
    {
        /* 不存在，说明出现异常，丢弃此消息，打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoModifiedProc:Warning:not exist this PDN info.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhsmSyncPdnInfoModifiedProc_ENUM, ESM_EHSM_NO_PDN);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoDisconnectedProc
 Description    : ESM收到EHSM发来的承载DISCONN指示时的处理
 Input          : EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM发来的消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoDisconnectedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoDisconnectedProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /* 在EHRPD实体中根据EHRPD承载ID查找当前修改的PDN连接是否存在 */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* 通知RABM，向RABM发送ID_ESM_ERABM_DEACT_IND，只去激活1个EHRPD承载 */
        aulEpsId[0] = pEhsmMsg->ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* 删除此PDN连接的信息 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);
    }
    else
    {
        /* 不存在，说明出现异常，丢弃此消息，打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoDisconnectedProc:Warning:not exist this PDN info.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhsmSyncPdnInfoDisconnectedProc_ENUM, ESM_EHSM_NO_PDN);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc
 Description    : ESM模块清除所有处于激活态的LTE承载，
                  缺省承载不通知APS，专有承载通知APS
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc(VOS_VOID)
{
    VOS_UINT32                          i;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc_ENUM, LNAS_ENTRY);

    /* 根据消息记录通知APP */
    NAS_ESM_ClearStateTable(APP_ERR_SM_DETACHED, PS_FALSE);

    /* 设置EMM的状态为未注册 */
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);

    /* 如果支持双APN，则停止对应定时器，并设置注册承载无效 */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        NAS_ESM_SetAttachBearerId(NAS_ESM_UNASSIGNED_EPSB_ID);
    }

    /* 设置OPID为0 */
    NAS_ESM_SetCurMaxOpIdValue(NAS_ESM_MIN_OPID_VALUE);

    #ifdef PS_ITT_PC_TEST_NAS
    /* NAS ST场景下，由于现有用例在注册时使用了PTI值为2，所以PTI初始化为1，调用PTI分配函数，会从2开始使用 */
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE);
    #else

    /* PTI初始化为0，注册时，调用PTI分配函数，会从1开始使用 */
    /*lint -e778*/
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE-1);
    /*lint +e778*/

    /* CID0在PS融合后比较特殊，在ESM维护的内容与NV的内容会存在不一致, 需将CID0初始化为专有类型 */
    NAS_ESM_ClearCid0StaticInfo();
    #endif

    NAS_ESM_SetCurMaxGwAuthIdVaule(NAS_ESM_GWAUTHID_MIN_VALUE);

    /* 初始化CID 21~31 关联静态信息 */
    NAS_ESM_ClearNwCtrlSdfPara();

    /* 通知APP和APS 激活承载被释放，初始化承载信息 */
    for (i = NAS_ESM_MIN_EPSB_ID; i <= NAS_ESM_MAX_EPSB_ID; i++)
    {
        /* 未激活，直接删掉 */
        if (NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(i))
        {
            /* 初始化承载信息 */
            NAS_ESM_InitEpsbCntxtInfo(i);
            continue;
        }

        /* 激活态且是专有承载，则需要通知APS去激活，缺省承载不能通知 */
        if (NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(i))
        {
            /* L4A重构, GU要求BEARER_INFO_IND在Rel Cnf之前 */
            /* 通知APS 激活承载被释放 */
            NAS_ESM_SndSmEspBearerDeactIndMsg(i);

            /* 通知APP 激活承载被释放，汇聚的所有CID都通知APP释放掉 */
            NAS_ESM_InformAppBearerRel(i);
        }

        /* 初始化承载信息 */
        NAS_ESM_InitEpsbCntxtInfo(i);
    }

    /* 初始化业务流的动态信息 */
    for (i = 0; i < NAS_ESM_MAX_CID_NUM; i++)
    {
        NAS_ESM_MEM_SET_S(  NAS_ESM_GetSdfCntxtInfo(i),
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
    }

    /* 初始化PDN连接的个数 */
    NAS_ESM_SetCurPdnNum(0);

    /* 初始化发送空口消息的结构体 */
    NAS_ESM_ClearEsmSndNwMsgAddr();

    /* 清除ESM缓存区 */
    NAS_ESM_ClearEsmBuff();

    return;

}


/*****************************************************************************
 Function Name  : NAS_ESM_ClearAllEhrpdPdnInfoProc
 Description    : ESM模块清除所有EHRPD承载记录的处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ClearAllEhrpdPdnInfoProc(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllEhrpdPdnInfoProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllEhrpdPdnInfoProc_ENUM, LNAS_ENTRY);

    /* 遍历PDN实体列表 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            if (NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ ==  \
                                        NAS_ESM_GET_EHRPD_ENTITY_STATE())
            {
                /* 向APS上报承载恢复失败 */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);
            }

            /* 删除EHRPD承载记录 */
            NAS_ESM_DeleteEhrpdPdnEntityInfo(i);
        }
    }

    /* 设置EHRPD实体进入等待恢复状态 */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* 使用的实体总数强制清0 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()      = 0;

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_AllocPdnIndexInEhrpdEntity
 Description    : 在EHRPD实体中分配一个未使用的索引位置
 Input          :
 Output         : VOS_UINT32*           传出分配到的索引值
 Return Value   : VOS_UINT32            分配结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_AllocPdnIndexInEhrpdEntity(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* 如果PDN实体使用数为最大，直接返回分配失败 */
    if (NAS_ESM_EHRPD_PDN_MAX_NUM == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        /* 未找到，返回失败 */
        NAS_ESM_INFO_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity: Entity total num is Max.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, ESM_EHSM_PDN_REACH_MAXNUM);
        return  NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到未使用的位置，返回成功，传出索引值 */
        if (PS_TRUE != pstPdnEntity->ucUsedFlag)
        {
            pstPdnEntity->ucUsedFlag    = PS_TRUE;
            *pulIndex                   = i;

            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，返回失败 */
    NAS_ESM_WARN_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity: Alloc failed.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_SaveEhrpdPdnInfo
 Description    : 在EHRPD实体中保存EHRPD承载信息
 Input          : VOS_UINT32                                存入的索引位置
                  EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM发来的消息
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SaveEhrpdPdnInfo(
    VOS_UINT32                          ulIndex,
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo1;
    APP_ESM_APN_INFO_STRU               stTmpApnInfo2;

    NAS_ESM_INFO_LOG("NAS_ESM_SaveEhrpdPdnInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveEhrpdPdnInfo_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(  &stTmpApnInfo1,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU));
    NAS_ESM_MEM_SET_S(  &stTmpApnInfo2,
                        sizeof(APP_ESM_APN_INFO_STRU),
                        0,
                        sizeof(APP_ESM_APN_INFO_STRU));

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 保存CID */
    pstPdnEntity->stEhPdnContextInfo.ulBitCid               = pEhsmMsg->ulBitCid;

    /* 保存EHRPD下的承载ID */
    pstPdnEntity->stEhPdnContextInfo.ulEpsbId               = pEhsmMsg->ulEpsbId;

    /* 保存EHRPD下的PDN地址 */
    NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stPdnAddr,
                        sizeof(EHSM_ESM_PDN_ADDR_STRU),
                        &pEhsmMsg->stPdnAddr,
                        sizeof(EHSM_ESM_PDN_ADDR_STRU));

    /* 保存APN */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApn)
    {
        /* 临时保存APN，用于APN格式转换 */
        stTmpApnInfo1.ucApnLen          = pEhsmMsg->stApn.ucApnLen;
        NAS_ESM_MEM_CPY_S(  stTmpApnInfo1.aucApnName,
                            NAS_ESM_MAX_APN_NUM,
                            pEhsmMsg->stApn.aucApn,
                            pEhsmMsg->stApn.ucApnLen);

        /* 将APN格式从未译码转为译码 */
        if(NAS_ESM_SUCCESS != NAS_ESM_ApnReverseTransformation(&stTmpApnInfo2, &stTmpApnInfo1))
        {
            NAS_ESM_ERR_LOG("NAS_ESM_SaveEhrpdPdnInfo:apn format is illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_SaveEhrpdPdnInfo_ENUM, ESM_EHSM_APN_FORMAT_ILL);
            pstPdnEntity->stEhPdnContextInfo.bitOpApn       = NAS_ESM_OP_FALSE;
        }
        else
        {
            pstPdnEntity->stEhPdnContextInfo.bitOpApn       = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stApn,
                                sizeof(APP_ESM_APN_INFO_STRU),
                                &stTmpApnInfo2,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }
    }

    /* 保存APN AMBR */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApnAmbr)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpApnAmbr       = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stApnAmbr,
                            sizeof(EHSM_ESM_APN_AMBR_STRU),
                            &pEhsmMsg->stApnAmbr,
                            sizeof(EHSM_ESM_APN_AMBR_STRU));
    }

    /* 保存PCO IPV4 */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpPcoIpv4Item)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpPcoIpv4Item   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stPcoIpv4Item,
                            sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU),
                            &pEhsmMsg->stPcoIpv4Item,
                            sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU));
    }

    /* 保存PCO IPV6 */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpPcoIpv6Item)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpPcoIpv6Item   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stPcoIpv6Item,
                            sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU),
                            &pEhsmMsg->stPcoIpv6Item,
                            sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU));
    }

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_DeleteEhrpdPdnEntityInfo
 Description    : ESM模块清除某EHRPD承载实体信息记录的处理
 Input          : VOS_UINT32            实体索引
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_DeleteEhrpdPdnEntityInfo(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG1("NAS_ESM_DeleteEhrpdPdnEntityInfo:delete entity index = ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DeleteEhrpdPdnEntityInfo_ENUM, LNAS_ENTRY, ulIndex);

    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 设置PDN实体为未使用 */
    pstPdnEntity->ucUsedFlag            = PS_FALSE;

    /* 清除实体相关标识 */
    pstPdnEntity->ucAttachPdnFlag       = PS_FALSE;
    pstPdnEntity->ucIsOnReconnFlag      = PS_FALSE;
    pstPdnEntity->ucRsv                 = 0;

    /* 清零L下恢复的承载ID */
    pstPdnEntity->ulHandoverEpsbId      = 0;

    /* 停止等待PDN恢复成功定时器 */
    NAS_ESM_TimerStop(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);

    /* 清除空口消息记录 */
    NAS_ESM_MEM_SET_S(  &pstPdnEntity->stNwMsgRecord,
                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU),
                        0,
                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

    /* 清除承载上下文信息 */
    NAS_ESM_MEM_SET_S(  &pstPdnEntity->stEhPdnContextInfo,
                        sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU));

    /* EHRPD承载记录总数减一 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM() --;

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId
 Description    : 根据EHRPD的承载ID信息在EHRPD实体中获取相应的PDN实体索引
 Input          : VOS_UINT32            EHRPD承载ID信息
 Output         : VOS_UINT32*           获取到的索引值地址
 Return Value   : VOS_UINT32            获取结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, LNAS_ENTRY);

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* 在实体列表中逐一查找，找到正在使用的，且承载ID相同，返回成功，传出索引值 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulEpsbId == pstPdnEntity->stEhPdnContextInfo.ulEpsbId))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，返回失败 */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId: Not find same EpsbId.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, ESM_EHSM_NOT_FIND_SAME_EPSBID);
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedCid
 Description    : 根据CID在EHRPD实体中获取相应的PDN实体索引
 Input          : VOS_UINT32            CID信息
 Output         : VOS_UINT32*           获取到的索引值地址
 Return Value   : VOS_UINT32            获取结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(
    VOS_UINT32                          ulCid,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulBitCid;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedCid is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, LNAS_ENTRY);

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedCid: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* 转换成ulBitCid */
    ulBitCid        = ((VOS_UINT32)NAS_ESM_BIT_0 << ulCid);

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到正在使用的，且CID相同，返回成功，传出索引值 */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulBitCid == pstPdnEntity->stEhPdnContextInfo.ulBitCid))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，返回失败 */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same CID.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, ESM_EHSM_NOT_FIND_SAME_CID);
    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedApn
 Description    : 根据APN信息在EHRPD实体中获取相应的PDN实体索引
 Input          : APP_ESM_APN_INFO_STRU*          APN信息
 Output         : VOS_UINT32*                     获取到的索引值地址
 Return Value   : VOS_UINT32                      获取结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(
    const APP_ESM_APN_INFO_STRU        *pstApn,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, LNAS_ENTRY);

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* APN长度为0或超99，直接返回获取失败 */
    if ((0 == pstApn->ucApnLen)
      ||(APP_MAX_APN_LEN < pstApn->ucApnLen))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: APN len is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_APN_LEN_0);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到正在使用的，且APN相同，返回成功，传出索引值 */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn))
        {
            if ((pstApn->ucApnLen == pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen)
              &&(NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(pstApn->aucApnName,                   \
                                        pstPdnEntity->stEhPdnContextInfo.stApn.aucApnName,\
                                        pstApn->ucApnLen)))
            {
                *pulIndex               = i;
                return NAS_ESM_SUCCESS;
            }
        }
    }

    /* 未找到，返回失败 */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same APN.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_NOT_FIND_SAME_APN);
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId
 Description    : 根据OPID在EHRPD实体中查找对应的PDN实体索引
 Input          : VOS_UINT32            OPID值
 Output         : VOS_UINT32*           获取到的索引值地址
 Return Value   : VOS_UINT32            获取结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(
    VOS_UINT32                          ulOpId,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, LNAS_ENTRY);

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到正在使用的，且OPID相同，返回成功，传出索引值 */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulOpId == pstPdnEntity->stNwMsgRecord.ulNwMsgOpId))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，返回失败 */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same OPID.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, ESM_EHSM_NOT_FIND_SAME_OPID);
    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name  : NAS_ESM_GetAttachPdnInEhrpdEntity
 Description    : 在EHRPD实体中查找注册PDN
 Input          : None
 Output         : VOS_UINT32*           传出对应的PDN实体索引
 Return Value   : VOS_UINT32            获取结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetAttachPdnInEhrpdEntity(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* 在EHRPD PDN实体中进行循环查找 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 找到被标记为注册PDN的实体 */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(PS_TRUE == pstPdnEntity->ucAttachPdnFlag))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，说明可能被去激活掉了，直接用下一个PDN作为ATTACH PDN */
    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity: NO attachflag PDN, get next reconnect PDN.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, ESM_EHSM_NO_PDN_GET_NEXT_PND);
    if (NAS_ESM_SUCCESS ==  NAS_ESM_GetNextReconnectEhrpdPdn(pulIndex))
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(*pulIndex);
        pstPdnEntity->ucAttachPdnFlag   = PS_TRUE;
    }

    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name  : NAS_ESM_GetAttachCidInEhrpdEntity
 Description    : 在EHRPD实体中查找注册PDN对应的CID
 Input          : None
 Output         : VOS_UINT32*           传出注册用的CID
 Return Value   : VOS_UINT32            获取结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetAttachCidInEhrpdEntity(
    VOS_UINT32                         *pulCid
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulBitCid;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachCidInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachCidInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* 找到被标记为注册PDN的实体 */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
    {
        return NAS_ESM_FAILURE;
    }

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    ulBitCid        = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /* CID转换 */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* 无效CID，返回失败 */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    *pulCid         = ulCid;

    return NAS_ESM_SUCCESS;

}


/*****************************************************************************
 Function Name  : NAS_ESM_GetNextReconnectEhrpdPdn
 Description    : 在EHRPD实体中查找下一个可以恢复的EHRPD PDN
 Input          : None
 Output         : VOS_UINT32*           下一个EHRPD实体索引
 Return Value   : VOS_UINT32            获取结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetNextReconnectEhrpdPdn(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;

    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到正在使用的 */
        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* 如果检查结果为不允许发起，跳过选择下一个 */
            if (NAS_ESM_SUCCESS != NAS_ESM_CheckAllowedPdnEntityToReconnect(pstPdnEntity))
            {
                /* 向APS上报承载恢复失败 */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

                /* 在EHRPD实体中找到此EHRPD承载ID，通知ERABM释放此承载 */
                pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);
                aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
                NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

                /* 删除这条EHRPD承载信息记录 */
                NAS_ESM_DeleteEhrpdPdnEntityInfo(i);

                continue;
            }

            *pulIndex                   = i;

            /* 可维可测，上报HIDS实体状态 */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();
            return NAS_ESM_SUCCESS;
        }
    }

    NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn: Get next PDN failed.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, ESM_EHSM_NO_NEXT_PDN);
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_PerformEhrpdPdnReconnect
 Description    : 执行EHRPD PDN恢复流程
 Input          : None
 Output         : VOS_UINT32           EHRPD实体索引
 Return Value   : VOS_UINT32           0 执行成功； 1 执行失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_PerformEhrpdPdnReconnect(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT32                          ulPti;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulBitCid;
    VOS_UINT32                          ulStateTblIndex;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_PerformEhrpdPdnReconnect is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, LNAS_ENTRY);

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    ulBitCid        = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /* L模为挂起态，停止EHRPD承载恢复流程 */
    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return NAS_ESM_FAILURE;
    }

    /* CID转换 */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* 无效CID，返回失败 */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* 分配动态表ID */
    if (NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCid, &ulStateTblIndex))
    {
        /* 打印异常消息，状态表满或者该CID已经在表中 */
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_TABLE_FULL_OR_CID_ALREADY_IN);
        return NAS_ESM_FAILURE;
    }

    /* 将EHRPD承载记录中的APN信息写入对应CID的SDF表项 */
    pstSdfPara                          = NAS_ESM_GetSdfParaAddr(ulCid);
    NAS_ESM_SetEhrpdPdnInfoToSdf(pstSdfPara, pstPdnEntity);

    /* 设置动态表中参数承载状态和类别 */
    pstStateAddr                        = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->enBearerCntxtState    = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEFAULT;
    pstStateAddr->enPdnReqType          = NAS_ESM_PDN_REQ_TYPE_HANDOVER;

    /* 分配PTI，并存入承载信息中 */
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr->stNwMsgRecord.ucPti   = (VOS_UINT8)ulPti;

    /* 填充NAS_ESM_ENCODE_INFO_STRU */
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau            = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid                  = pstStateAddr->ulCid;
    stEncodeInfo.ucPti                  = (VOS_UINT8)ulPti;
    stEncodeInfo.enPdnReqType           = pstStateAddr->enPdnReqType;

    /* 组装PDN_Connect_Req消息 */
    if (NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo,             \
                                        pstStateAddr->stNwMsgRecord.aucMsgBuff, \
                                        &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_ENCODE_PND_CONN_REQ_FAIL);

        /* 编码失败，释放动态表资源 */
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return NAS_ESM_FAILURE;
    }

    /* 分配OPID，记录空口消息类型 */
    pstStateAddr->bitOpNwMsgRecord                = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ulOpId            = NAS_ESM_AllocEmmEsmOpId();
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType    = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /* 设置是否为紧急PDN连接请求 */
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq     = PS_FALSE;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf              = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /* 调用函数，ESM->EMM发送消息:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ) */
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,                         \
                                                  pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,\
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,                      \
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  NAS_ESM_AIR_MSG_DIR_ENUM_UP,              \
                                                  ESM_PDN_CONNECT_REQ);

    /* 启动T3482定时器 */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_T3482);

    /* 状态转换 */
    NAS_ESM_SetProcTransState(ulStateTblIndex, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

    /* 此EHRPD的PDN实体进入承载恢复过程中 */
    pstPdnEntity->ucIsOnReconnFlag = PS_TRUE;

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_SetEhrpdPdnInfoToSdf
 Description    : 将EHRPD的PDN实体中的信息设置到SDF中
 Input          : NAS_ESM_SDF_PARA_STRU*          SDF指针
                  NAS_ESM_EHRPD_PDN_ENTITY_STRU*  PDN实体指针
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSdf(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    /* 取出实体中的APN，设置到SDF中 */
    if (NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        pstSdfPara->bitOpApn            = NAS_ESM_OP_TRUE;

        pstSdfPara->stApnInfo.ucApnLen  = pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen;

        NAS_ESM_MEM_CPY_S(  pstSdfPara->stApnInfo.aucApnName,
                            APP_MAX_APN_LEN,
                            pstPdnEntity->stEhPdnContextInfo.stApn.aucApnName,
                            pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen);
    }

    /* 取出实体中的PDN类型，设置到SDF中 */
    if ((EHSM_ESM_PDN_TYPE_IPV4 <= pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType)
      &&(EHSM_ESM_PDN_TYPE_IPV4V6 >= pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType))
    {
        pstSdfPara->bitOpPdnType         = NAS_ESM_OP_TRUE;
        pstSdfPara->enPdnType            = pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg
 Description     : 赋值EHRPD承载信息到PDN同步消息中
 Input           : NAS_ESM_EPSB_CNTXT_INFO_STRU*            ESM承载信息指针
                   ESM_EHSM_SYNC_PDN_INFO_IND_STRU*         ESM与EHSM接口中的承载信息指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd
)
{
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo;

    NAS_ESM_MEM_SET_S(  &stTmpApnInfo,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU));

    NAS_ESM_INFO_LOG("NAS_ESM_SetEhrpdPdnInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg_ENUM, LNAS_ENTRY);

    /* 赋值关联CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /* 赋值承载ID */
    pstPdnInfoInd->ulEpsbId             = pstEpsbCntxtInfo->ulEpsbId;

    /* 将译码的APN信息转成未译码的APN信息 */
    if(APP_SUCCESS != NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                        &pstEpsbCntxtInfo->stApnInfo))
    {
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_FALSE;
    }
    else
    {
        /* 赋值APN */
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_TRUE;
        pstPdnInfoInd->stApn.ucApnLen   = stTmpApnInfo.ucApnLen;

        NAS_ESM_MEM_CPY_S(  pstPdnInfoInd->stApn.aucApn,
                            EHSM_ESM_MAX_APN_LEN,
                            stTmpApnInfo.aucApnName,
                            stTmpApnInfo.ucApnLen);
    }

    /* 赋值PDN ADDRESS */
    NAS_ESM_MEM_CPY_S(  &pstPdnInfoInd->stPdnAddr,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                        &pstEpsbCntxtInfo->stPdnAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /* 赋值APN-AMBR，暂时先不填 */

    /* 赋值PCO，暂时先不填 */

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_ConvertBitCidToCid
 Description    : 在只有一个CID的情况下ulBitCid到Cid的转换
 Input          : VOS_UINT32            ulBitCid
 Output         : None
 Return Value   : VOS_UINT32            获取CID结果

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_ConvertBitCidToCid(
    VOS_UINT32                          ulBitCid
)
{
    VOS_UINT8                           i;

    NAS_ESM_INFO_LOG1("NAS_ESM_ConvertBitCidToCid: ulBitCid = ", ulBitCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ConvertBitCidToCid_ENUM, LNAS_ENTRY, ulBitCid);

    /* 循环移位找到CID，目前不存在承载汇聚，因此只能有1个CID */
    for (i = 0; i <= NAS_ESM_MAX_CID; i++)
    {
        /* 右移几位之后的结果为1，CID就是几，找到后返回成功 */
        if (NAS_ESM_OP_TRUE == ((ulBitCid >> i) & 0x00000001))
        {
            return i;
        }
    }

    return NAS_ESM_ILL_CID;
}

/*****************************************************************************
 Function Name  : NAS_ESM_IsBackOffAllowedToReconn
 Description    : BACK OFF算法是否允许发起承载恢复空口流程判定
 Input          : NAS_ESM_EHRPD_PDN_ENTITY_STRU*  PDN实体指针
 Output         : None
 Return Value   : VOS_UINT32            判定结果: 0成功；1失败

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_IsBackOffAllowedToReconn(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    NAS_ESM_MEM_SET_S(  &stJudgmentPara,
                        sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU),
                        0,
                        sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));

    /* 缺省承载且有APN，Back-off算法判定，如果不允许发起，直接给APP回失败 */
    if(NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        NAS_ESM_MEM_CPY_S(  &stJudgmentPara,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &pstPdnEntity->stEhPdnContextInfo.stApn,
                            sizeof(APP_ESM_APN_INFO_STRU));
    }
    else
    {
        /* 无APN直接允许发起 */
        return NAS_ESM_SUCCESS;
    }

    if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_IsBackOffAllowedToReconn: Back-off not allowed send PDN req.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_IsBackOffAllowedToReconn_ENUM, ESM_EHSM_BACKOFF_NOT_ALLOW_PDN_REQ);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_CheckAllowedPdnEntityToReconnect
 Description    : 检查是否允许当前PDN实体发起承载恢复流程
 Input          : NAS_ESM_EHRPD_PDN_ENTITY_STRU*  PDN实体指针
 Output         : None
 Return Value   : VOS_UINT32            检查结果: 0允许发起；1不允许发起

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_CheckAllowedPdnEntityToReconnect(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    VOS_UINT32                          ulCid;

    NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, LNAS_ENTRY);

    /* Back-off算法判定，如果不允许发起，返回失败 */
    if (NAS_ESM_SUCCESS != NAS_ESM_IsBackOffAllowedToReconn(pstPdnEntity))
    {
        return NAS_ESM_FAILURE;
    }

    /* 在拒绝原因值#66列表中，且当前驻留PLMN是#66列表的PLMN，返回失败*/
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #66 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_66_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    ulCid = NAS_ESM_ConvertBitCidToCid(pstPdnEntity->stEhPdnContextInfo.ulBitCid);

    /* CID无效，返回失败 */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* 错误PDN类型，返回失败 */
    if ((EHSM_ESM_PDN_TYPE_IPV4 > pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType)
      ||(EHSM_ESM_PDN_TYPE_IPV4V6 < pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect:PDN type err.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_PDN_TYPE_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* 如果当前使用的APN在#50拒绝列表中，返回失败 */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType, \
                                        pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #50 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_50_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    /* 如果当前使用的APN在#51拒绝列表中，返回失败 */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas51Rej(pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType,  \
                                        pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #51 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_51_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdPdnConnectHandOverSuccProc
 Description    : EHRPD承载恢复成功的处理
 Input          : VOS_UINT32            PDN实体索引
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverSuccProc(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulEhrpdBearerId;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverSuccProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverSuccProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 取出在LTE下恢复后网侧分配的承载ID，取出原EHRPD下分配的承载ID */
    ulEpsbId        = pstPdnEntity->ulHandoverEpsbId;
    ulEhrpdBearerId = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;

    /* 向RABM发送ID_ESM_ERABM_ACT_IND, 填写LTE下恢复后网侧分配的承载ID，接入技术类型为LTE，是恢复流程，填写原EHRPD承载ID */
    NAS_ESM_SndEsmRabmActIndMsg(ulEpsbId, ESM_ERABM_BEARER_RAT_LTE, PS_TRUE, ulEhrpdBearerId);

    /* 向APS上报注册承载恢复成功 */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_SUCC);

    /* 删除这条EHRPD承载信息记录 */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* 寻找下一条EHRPD承载执行恢复流程 */
    NAS_ESM_PerformNextEhrpdPdnReconnectProc();

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdPdnConnectHandOverFailProc
 Description    : EHRPD承载恢复失败的处理
 Input          : VOS_UINT32            PDN实体索引
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverFailProc(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverFailProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /* 向APS上报承载恢复失败 */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

    /* 在EHRPD实体中找到此EHRPD承载ID，通知ERABM释放此承载 */
    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
    aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

    /* 删除这条EHRPD承载信息记录 */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* 寻找下一条EHRPD承载执行恢复流程 */
    NAS_ESM_PerformNextEhrpdPdnReconnectProc();

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc
 Description    : EHRPD实体对EMM发送DATA REQ消息成功的处理
 Input          : VOS_UINT32            OPID
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc(
    VOS_UINT32                          ulOpId
)
{
    VOS_UINT32                          ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc_ENUM, LNAS_ENTRY);

    /* 根据OPID查找对应的PDN实体索引 */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(ulOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 找到PDN实体，如果是激活缺省承载ACP发送成功，执行恢复成功的处理 */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        NAS_ESM_EhrpdPdnConnectHandOverSuccProc(ulIndex);
    }
    else
    {
        /* 只是PDN REQ发送成功，无动作 */
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdEntityProcEmmSendDataReqFail
 Description    : EHRPD实体对EMM发送DATA REQ消息失败的处理
 Input          : const EMM_ESM_DATA_CNF_STRU*
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqFail(
    const EMM_ESM_DATA_CNF_STRU        *pEmmEsmDataCnfMsg
)
{
    VOS_UINT32                          ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_DSDS)
    VOS_UINT32                          i;
    VOS_UINT32                          ulEpsIdNum = 0;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));
    #endif

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqFail is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdEntityProcEmmSendDataReqFail_ENUM, LNAS_ENTRY);

    /* 如果是因NO RF发送的失败，则剩余未恢复的EHRPD承载都不再恢复了 */
    #if (FEATURE_ON == FEATURE_DSDS)
    if (EMM_ESM_SEND_RSLT_NORF == pEmmEsmDataCnfMsg->enDataCnfRst)
    {
        for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
        {
            /* 在EHRPD实体中找到所有未恢复的EHRPD承载ID */
            pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

            if (PS_TRUE == pstPdnEntity->ucUsedFlag)
            {
                aulEpsId[ulEpsIdNum] = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
                ulEpsIdNum++;
            }
        }

        /* 通知ERABM释放所有未恢复的EHRPD承载 */
        NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsIdNum, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* 清除所有EHRPD的PDN记录 */
        NAS_ESM_ClearAllEhrpdPdnInfoProc();
        return;
    }
    #endif

    /* 根据OPID查找对应的PDN实体索引 */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(pEmmEsmDataCnfMsg->ulEsmEmmOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqFail: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqFail_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                        = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 找到PDN实体，如果是激活缺省承载ACP发送失败，按发送失败进行特殊的处理 */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        pstPdnEntity->stNwMsgRecord.ucSendFailTimes ++;

        /* 第一次发送失败时启动等待恢复承载成功定时器，防止网侧不再发送缺省承载激活请求导致挂死
        此定时器在删除此承载记录时停止，如果超时，删除此承载进行下一条EHRPD承载恢复流程 */
        if (NAS_ESM_FIRST_FAIL_TIME == pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_TimerStart(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);
        }

        /* 失败次数达最大，认为承载恢复失败 */
        if (NAS_ESM_EHRPD_ALLOW_MAX_SND_FAIL_TIMES <= pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_EhrpdPdnConnectHandOverFailProc(ulIndex);
            return;
        }

    }
    else
    {
        /* 只是PDN REQ发送失败，无动作，等待T3482定时器超时重发 */
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_PerformNextEhrpdPdnReconnectProc
 Description    : 执行下一条EHRPD PDN的恢复流程
 Input          : None
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_PerformNextEhrpdPdnReconnectProc(VOS_VOID)
{
    VOS_UINT32                          ulIndex      = 0;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_PerformNextEhrpdPdnReconnectProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PerformNextEhrpdPdnReconnectProc_ENUM, LNAS_ENTRY);

    /* 如果PDN实体数为0，说明恢复承载流程结束，设置EHRPD实体为等待恢复态 */
    if (0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_PerformNextEhrpdPdnReconnectProc: PDN entity is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_PerformNextEhrpdPdnReconnectProc_ENUM, ESM_EHSM_NO_PDN);
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

        #if (FEATURE_ON == FEATURE_DSDS)
        NAS_ESM_SendEndSessionNotify();
        #endif

        return;
    }

    /* 取下一条承载 */
    while (NAS_ESM_SUCCESS == NAS_ESM_GetNextReconnectEhrpdPdn(&ulIndex))
    {
        /* 获取成功，执行下一条承载恢复处理，如果执行成功，返回 */
        if (NAS_ESM_SUCCESS == NAS_ESM_PerformEhrpdPdnReconnect(ulIndex))
        {
            return;
        }

        /* 执行失败 */

        /* 向APS上报承载恢复失败 */
        NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

        /* 在EHRPD实体中找到此EHRPD承载ID，通知ERABM释放此承载 */
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
        aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* 删除这条EHRPD承载信息记录 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);
    }

    /* 获取下一个失败 */
    #if (FEATURE_ON == FEATURE_DSDS)
    NAS_ESM_SendEndSessionNotify();
    #endif

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc
 Description    : 等待恢复的EHRPD承载收到APS的PDP释放请求的处理
 Input          : const APP_ESM_PDP_RELEASE_REQ_STRU*  APS的释放消息
                  VOS_UINT32                           待释放的PDN实体索引
 Output         : None
 Return Value   : VOS_UINT32

 History        :
      1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc(
    const APP_ESM_PDP_RELEASE_REQ_STRU *pstAppEsmPdpRelReqMsg,
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    VOS_UINT32                          ulStateTblIndex = 0;

    NAS_ESM_INFO_LOG("NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32),
                                        0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /*封装结构体pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET_S(&stEsmAppCnfMsg, sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                                        0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    stEsmAppCnfMsg.bitOpEpsbId          = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId             = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId            = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid             = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId                = pstAppEsmPdpRelReqMsg->ulCid;
    stEsmAppCnfMsg.ulOpId               = pstAppEsmPdpRelReqMsg->ulOpId;
    stEsmAppCnfMsg.usOriginalId         = pstAppEsmPdpRelReqMsg->usOriginalId;
    stEsmAppCnfMsg.usTerminalId         = pstAppEsmPdpRelReqMsg->usTerminalId;
    stEsmAppCnfMsg.bitOpErrorCode       = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.ulRst                = NAS_ESM_FAILURE;

    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 如果只有1个EHRPD PDN实体，且当前LTE不是已注册状态，说明这是唯一的承载 */
    if ((1 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
      &&(NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus()))
    {
        /* 直接给APS回复失败，后面强行恢复，LTE下不允许没有承载 */
        NAS_ESM_WARN_LOG("NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc:WARNING1:The Last PDN CONNECT can not be disconnect!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc_ENUM, LNAS_FUNCTION_LABEL1);

        /* 向APP返回承载释放失败，原因值为:NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED */
        stEsmAppCnfMsg.ulRst          = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED);
        stEsmAppCnfMsg.bitOpEpsbId    = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId       = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* 要释放的不是最后一条承载 */

    /* 如果当前PDN实体还未进入恢复流程，直接删除记录即可 */
    if (PS_FALSE == pstPdnEntity->ucIsOnReconnFlag)
    {
        /* 通知RABM，向RABM发送ID_ESM_ERABM_DEACT_IND，只去激活1个EHRPD承载 */
        aulEpsId[0] = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* 删除此PDN实体记录 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

        /* 向APS上报PDP释放成功 */
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* 当前PDN实体已经进入恢复流程 */

    /* 如果当前要释放的是handover ATTACH过程中的那条PDN，由于已经起ATTACH空口流程，无法停止，向APS返回失败 */
    if (PS_TRUE == pstPdnEntity->ucAttachPdnFlag)
    {
        /* 直接给APS回复失败，后面强行恢复，LTE下不允许没有承载 */
        NAS_ESM_WARN_LOG("NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc:WARNING2:The Last PDN CONNECT can not be disconnect!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc_ENUM, LNAS_FUNCTION_LABEL2);

        /* 向APP返回承载释放失败，原因值为:NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED */
        stEsmAppCnfMsg.ulRst          = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED);
        stEsmAppCnfMsg.bitOpEpsbId    = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId       = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* 当前要释放的不是handover ATTACH的那条PDN，且还未收到网侧回复承载激活请求，直接释放动态表删除记录 */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC != pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        /* 找到使用的动态表，一定找的到 */
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pstAppEsmPdpRelReqMsg->ulCid, &ulStateTblIndex))
        {
            /* 释放状态表资源，后续再收到网侧承载激活请求自然直接回REJ */
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
        }

        /* 通知RABM，向RABM发送ID_ESM_ERABM_DEACT_IND，只去激活1个EHRPD承载 */
        aulEpsId[0] = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* 删除此PDN实体记录 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

        /* 向APS上报PDP释放成功 */
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);

        /* 寻找下一条EHRPD承载启动恢复流程 */
        NAS_ESM_PerformNextEhrpdPdnReconnectProc();
    }

    /* 承载已经被激活，只是还未收到发送激活承载ACP的EMM的DATA CNF消息 */

    /* 此时相应的承载在ESM上下文中已经属于激活态的承载，此处不做处理，
    复用原ESM收到APS释放的处理，发起空口的DISCONN流程 */

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc
 Description    : EHRPD承载恢复成功收到APS的PDP释放请求的处理
 Input          : const APP_ESM_PDP_RELEASE_REQ_STRU*  APS的释放消息
                  VOS_UINT32                           待释放的PDN实体索引
 Output         : None
 Return Value   : VOS_UINT32

 History        :
      1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc(
    const APP_ESM_PDP_RELEASE_REQ_STRU *pstAppEsmPdpRelReqMsg,
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 当前要释放的是handover ATTACH的那条PDN，但ATTACH CMP还未发送成功，
    此时只有一条承载，原流程自然会回失败，不用处理 */
    if ((PS_TRUE == pstPdnEntity->ucAttachPdnFlag)
      &&(NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus()))
    {
        return;
    }

    /* 不是ATTACH的PDN，原流程会自然执行承载去激活流程，
    此处只需要通知ERABM释放EHRPD承载资源，启动下一条EHRPD承载恢复流程 */

    /* 通知ERABM释放此EHRPD承载 */
    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
    aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

    /* 删除此EHRPD的PDN实体 */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* 寻找下一条EHRPD承载执行恢复流程 */
    NAS_ESM_PerformNextEhrpdPdnReconnectProc();
    return;
}

/*lint -specific(-e433)*/
/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmSyncPdnInfoIndMsg
 Description     : 向EHSM发送承载激活同步消息
 Input           : VOS_UINT32           承载号
                   VOS_UINT32           AttachPdn标识
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
    2.sunjitan 00193151    2016-01-14   Mofify for CL多模互操作二阶段
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_CONNECTED;

    /* 如果是第一条PDN连接，则需要在通知EHSM承载信息时设置Attach flag为true */
    if (1 == NAS_ESM_GetCurPdnNum())
    {
        pstPdnInfoInd->ulAttachFlag = VOS_TRUE;
    }
    else
    {
        pstPdnInfoInd->ulAttachFlag = VOS_FALSE;
    }

    /* 赋值承载信息 */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmSyncPdnInfoModIndMsg
 Description     : 向EHSM发送承载修改同步消息
 Input           : VOS_UINT32           承载号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstPdnInfoInd   = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(      \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoModIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoModIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_MODIFIED;
    pstPdnInfoInd->ulAttachFlag         = PS_FALSE;

    /* 赋值承载信息 */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg
 Description     : 向EHSM发送承载去激活同步消息
 Input           : VOS_UINT32           承载号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_DISCONNECTED;
    pstPdnInfoInd->ulEpsbId             = ulEpsbId;

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* 赋值关联CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* 赋值关联CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmClearAllBearerNotifyMsg
 Description     : 向EHSM发送清除所有承载指示
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmClearAllBearerNotifyMsg(VOS_VOID)
{
    ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU        *pstClearNtfMsg = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstClearNtfMsg = (ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG( \
                                                  sizeof(ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstClearNtfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmClearAllBearerNotifyMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmClearAllBearerNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstClearNtfMsg),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstClearNtfMsg),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstClearNtfMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstClearNtfMsg, ID_ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstClearNtfMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndApsEhrpdPdnReconnSuccMsg
 Description     : 向APS发送EHRPD承载恢复成功消息
 Input           : VOS_UINT32           PDN实体索引值
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* 获取对应PDN实体地址 */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 恢复成功，向SM发送承载modify ind，接口消息复用 */
    NAS_ESM_SndSmEspBearerMdfIndMsg(pstPdnEntity->ulHandoverEpsbId);

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SndApsEhrpdPdnReconnFailMsg
 Description     : 向APS发送EHRPD承载恢复失败消息
 Input           : VOS_UINT32           PDN实体索引值
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnFailMsg(
    VOS_UINT32                          ulIndex
)
{
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstEpsBearInfoInd = (SM_ESM_EPS_BEARER_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(    \
                                        sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstEpsBearInfoInd)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndApsEhrpdPdnReconnFailMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndApsEhrpdPdnReconnFailMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return;
    }

    /* 获取对应PDN实体地址 */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd),
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    /* 去激活，只填承载ID和Cid即可 */
    pstEpsBearInfoInd->enPdpOption      = SM_ESM_PDP_OPT_DEACTIVATE;
    pstEpsBearInfoInd->ulEpsbId         = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    pstEpsBearInfoInd->ulBitCid         = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /*填写消息头*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SndApsEhrpdPdnReconnectResultMsg
 Description     : 向EHSM发送承载去激活同步消息
 Input           : VOS_UINT32                               EHRPD承载记录索引
                   NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8  恢复结果
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(
    VOS_UINT32                                    ulIndex,
    NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8       enResult
)
{

    if (NAS_ESM_PDN_RECONNECT_RESULT_SUCC == enResult)
    {
        /* 恢复成功，向APS发送承载modify ind   */
        NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(ulIndex);
    }
    else
    {
        /* 恢复失败，向APS发送承载deactive ind */
        NAS_ESM_SndApsEhrpdPdnReconnFailMsg(ulIndex);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEmmClLocalDetachNotifyMsg
 Description     : 向EMM发送local DETACH指示
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEmmClLocalDetachNotifyMsg(VOS_VOID)
{
    EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU          *pstDetachMsg        = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstDetachMsg    = (EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG(  \
                                                  sizeof(EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstDetachMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEmmClLocalDetachNotifyMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEmmClLocalDetachNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(NAS_ESM_GET_MSG_ENTITY(pstDetachMsg),
                      NAS_ESM_GET_MSG_LENGTH(pstDetachMsg),
                      0,
                      NAS_ESM_GET_MSG_LENGTH(pstDetachMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstDetachMsg, ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstDetachMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndOmEhrpdUsedPdnEntityNum
 Description     : 可维可测，向OM发送正在使用的PDN实体数量
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityNum(VOS_VOID)
{
    NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU         *pstEntityOmMsg      = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstEntityOmMsg  = (NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU*)NAS_ESM_MEM_ALLOC( \
                                                  sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU));

    if (VOS_NULL_PTR == pstEntityOmMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmEhrpdUsedPdnEntityNum:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndOmEhrpdUsedPdnEntityNum_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstEntityOmMsg,
                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU),
                        0,
                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU));

    pstEntityOmMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstEntityOmMsg->stMsgHeader.ulSenderPid         = PS_PID_ESM;
    pstEntityOmMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstEntityOmMsg->stMsgHeader.ulReceiverPid       = PS_PID_ESM;
    pstEntityOmMsg->stMsgHeader.ulLength            = sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU) - 20;

    pstEntityOmMsg->stMsgHeader.ulMsgName           = NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_NUM;

    /* 填充EHRPD实体当前状态 */
    pstEntityOmMsg->ulEhrpdPdnTotalNum              = NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM();

    /* 消息上报HIDS */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstEntityOmMsg);
    NAS_ESM_MEM_FREE(pstEntityOmMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo
 Description     : 可维可测，向OM发送正在使用的PDN实体状态
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU   *pstEntityOmMsg      = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    /* 先上报一下正在使用的PDN实体数量 */
    NAS_ESM_SndOmEhrpdUsedPdnEntityNum();

    /* 逐条上报正在使用的PDN实体信息 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* 分配空间并检验分配是否成功 */
            pstEntityOmMsg = (NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU*)NAS_ESM_MEM_ALLOC(\
                                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU));

            if (VOS_NULL_PTR == pstEntityOmMsg)
            {
                /*打印异常信息*/
                NAS_ESM_ERR_LOG("NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo:Alloc Msg fail!");
                TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
                return;
            }

            NAS_ESM_MEM_SET_S(  pstEntityOmMsg,
                                sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU),
                                0,
                                sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU));

            pstEntityOmMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
            pstEntityOmMsg->stMsgHeader.ulSenderPid         = PS_PID_ESM;
            pstEntityOmMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
            pstEntityOmMsg->stMsgHeader.ulReceiverPid       = PS_PID_ESM;
            pstEntityOmMsg->stMsgHeader.ulLength            = sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU) - 20;

            pstEntityOmMsg->stMsgHeader.ulMsgName           = NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_INFO;

            /* 填充EHRPD实体当前状态 */
            pstEntityOmMsg->enEntityState                   = NAS_ESM_GET_EHRPD_ENTITY_STATE();

            /* 本次发消息输出的PDN实体索引号 */
            pstEntityOmMsg->ucEntityIndex                   = (VOS_UINT8)i;
            NAS_ESM_MEM_CPY_S(  &pstEntityOmMsg->stEhPdnEntityInfo,
                                sizeof(NAS_ESM_EHRPD_PDN_ENTITY_STRU),
                                pstPdnEntity,
                                sizeof(NAS_ESM_EHRPD_PDN_ENTITY_STRU));

            /* 消息上报HIDS */
            (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstEntityOmMsg);
            NAS_ESM_MEM_FREE(pstEntityOmMsg);
        }
    }

    return;
}


/*lint -specific(+e433)*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

