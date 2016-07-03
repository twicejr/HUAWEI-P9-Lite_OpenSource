

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcInclude.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_USERCONN_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 类型定义
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTchAvail;                             /* TCH是否可用,VOS_TRUE:可用; VOS_FALSE:不可用 */
    VOS_UINT8                           aucReserve[3];
    VOS_BOOL                            bGsm;                                  /* 是否是GSM, VOS_TRUE: 是; VOS_FALSE:不是 */
    NAS_CC_TCH_TYPE_ENUM_U32            enChannelMode;                          /* 信道模式 */
} NAS_CC_TCH_STATUS_STRU;


/*****************************************************************************
  3 变量定义
*****************************************************************************/
LOCAL NAS_CC_TCH_STATUS_STRU            f_stCcTchStatus;                        /* 当前业务信道状态 */
LOCAL VOS_BOOL                          f_bSpeechConnAttached;                  /* 语音用户面连接是否已建立 */
LOCAL VOS_BOOL                          f_bDataConnAttached;                    /* 数据用户面连接是否已建立 */
LOCAL VOS_BOOL                          f_bCcLocalAlerting;                     /* 是否已产生本地回铃音 */
LOCAL NAS_CC_ENTITY_ID_T                f_connectedEntities[NAS_CC_MAX_ENTITY_NUM]; /* 已建立用户面连接的呼叫实体 */
LOCAL NAS_CC_INFO_TRANSFER_CAP_ENUM_U8  f_enCurrItc;

/*lint -save -e958 */

/*****************************************************************************
  4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_CC_InitUserConn
 功能描述  : 初始化用户连接管理模块，在第一次调用用户连接管理模块的其他函数之前，
             必须先调用该函数进行初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/

VOS_VOID NAS_CC_RealAttachUserConn(
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enItc,
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    NAS_CC_SYNC_IND_STRU                stSyncInd;

    stSyncInd.enAlertInd = NAS_CC_ALERT_IND_BUFF;
    stSyncInd.enRaMode = NAS_CC_RA_MODE_WCDMA;
    if(VOS_TRUE == f_stCcTchStatus.bGsm)
    {
        stSyncInd.enRaMode = NAS_CC_RA_MODE_GSM;
    }
    stSyncInd.ulTchAvail = f_stCcTchStatus.ucTchAvail;
    stSyncInd.enTchType = f_stCcTchStatus.enChannelMode;

    if (enItc == NAS_CC_ITC_SPEECH)
    {
        f_bSpeechConnAttached = VOS_TRUE;
        /* 发送MNCC_SYNC_IND原语 */
        NAS_CC_SendMnccMsg(entityId , MNCC_SYNC_IND, &stSyncInd, sizeof(NAS_CC_SYNC_IND_STRU));
    }
    else
    {
        if (VOS_FALSE == f_bDataConnAttached)
        {
            /* 建立CSD连接，暂不提供 */

            f_bDataConnAttached = VOS_TRUE;
        }
    }
}



LOCAL VOS_VOID NAS_CC_RealDetachUserConn(
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enItc,
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    NAS_CC_SYNC_IND_STRU                stSyncInd;
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;

    PS_MEM_SET(&stSyncInd, 0, sizeof(NAS_CC_SYNC_IND_STRU));
    /* 初始化为信道不存在,其它信息初始化为默认值，MN不使用 */
    stSyncInd.enAlertInd = NAS_CC_ALERT_IND_BUFF;
    stSyncInd.ulTchAvail = VOS_FALSE;
    stSyncInd.enRaMode = NAS_CC_RA_MODE_GSM;

    f_stCcTchStatus.ucTchAvail = VOS_FALSE;

    if (enItc == NAS_CC_ITC_SPEECH)
    {
        if (VOS_TRUE == f_bSpeechConnAttached)
        {
            f_bSpeechConnAttached = VOS_FALSE;

            /* 发送MNCC_SYNC_IND原语 */
            enCallState = NAS_CC_GetCallState(entityId);
            if ((NAS_CC_CALL_STATE_U10 != enCallState)
              &&(NAS_CC_CALL_STATE_U26 != enCallState))
            {
                NAS_CC_SendMnccMsg(entityId , MNCC_SYNC_IND, &stSyncInd, sizeof(NAS_CC_SYNC_IND_STRU));
            }
        }
    }
    else
    {
        if (VOS_TRUE == f_bDataConnAttached)
        {
            /* 释放CSD连接，暂不提供 */

            f_bDataConnAttached = VOS_FALSE;
        }

        f_enCurrItc = NAS_CC_ITC_SPEECH;
    }
}


VOS_VOID NAS_CC_InitUserConn(VOS_VOID)
{
    VOS_UINT32                          i;

    f_stCcTchStatus.ucTchAvail = VOS_FALSE;
    f_stCcTchStatus.enChannelMode = NAS_CC_TCH_TYPE_BUFF;
    f_bSpeechConnAttached = VOS_FALSE;
    f_bDataConnAttached = VOS_FALSE;
    f_bCcLocalAlerting = VOS_FALSE;
    f_enCurrItc = NAS_CC_ITC_SPEECH;

    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        f_connectedEntities[i] = NAS_CC_INVALID_ENTITY_ID;
    }
}



VOS_VOID NAS_CC_AttachUserConn(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enItc
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMinUnusedIdx = NAS_CC_MAX_ENTITY_NUM;

    /* 寻找一个空闲的位置，记录该呼叫实体建立用户面连接的情况 */
    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if ((NAS_CC_MAX_ENTITY_NUM == ulMinUnusedIdx)
         && (NAS_CC_INVALID_ENTITY_ID == f_connectedEntities[i]))
        {
            ulMinUnusedIdx = i;
        }

        if (f_connectedEntities[i] == entityId)
        {
            /* 该实体已经建立了用户面连接，直接返回 */
            return;
        }
    }
    if(ulMinUnusedIdx >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_CC_NORM_LOG("NAS_CC_AttachUserConn: NO FREE ENTITY.");
        return;
    }
    f_connectedEntities[ulMinUnusedIdx] = entityId;

    f_enCurrItc = enItc;

    if (NAS_CC_IsTchAvailable(enItc) == VOS_TRUE)
    {
        NAS_CC_RealAttachUserConn(enItc, entityId);
        return;
    }
    else
    {
        NAS_CC_NORM_LOG("NAS_CC_AttachUserConn: No available TCH.");
        return;
    }
}



VOS_VOID NAS_CC_DetachUserConn(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulNumEntities = 0;
    VOS_BOOL                            bAttached = VOS_FALSE;


    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (f_connectedEntities[i] == entityId)
        {
            bAttached = VOS_TRUE;
            f_connectedEntities[i] = NAS_CC_INVALID_ENTITY_ID;
        }

        if (f_connectedEntities[i] != NAS_CC_INVALID_ENTITY_ID)
        {
            ulNumEntities++;
        }
    }

    if (VOS_FALSE == bAttached)
    {
        /* 该实体尚未建立连接，直接返回 */
        NAS_CC_WARN_LOG("NAS_CC_DetachUserConn: NAS_CC_DetachUserConn return.");
        if (0 == ulNumEntities)
        {
            NAS_CC_InitUserConn();
        }
        return;
    }

    if (0 == ulNumEntities)
    {
        /* 这是最后一个detach的实体，释放实际的用户面连接 */
        NAS_CC_RealDetachUserConn(f_enCurrItc, entityId);
    }
}


VOS_UINT32 NAS_CC_SetTchStatus(
    const MMCC_SYNC_IND_STRU                  *pstInSyncInd,
    NAS_CC_ENTITY_ID_T                         entityId
)
{
    MMCC_SYNC_REASON_ENUM_U32  enReason =
        pstInSyncInd->enSyncReason;

    /* for cs data, ignore the message */
    if(NAS_CC_ITC_SPEECH != f_enCurrItc)
    {
        NAS_CC_WARN_LOG("NAS_CC_SetTchStatus: TCH sync for data.");
        return VOS_ERR;
    }

    if (MMCC_WCDMA_RAB_ESTABLISHED == enReason)
    {
        NAS_CC_StopRabProtectTimer();
    }

    switch (enReason)
    {
        case MMCC_GSM_CHANNEL_MODE_MODIFIED:
        case MMCC_GSM_GSM_HANDOVER:
        case MMCC_WCDMA_GSM_HANDOVER:
        case MMCC_GSM_RES_ASSIGNED:
            f_stCcTchStatus.ucTchAvail = VOS_TRUE;
            f_stCcTchStatus.bGsm = VOS_TRUE;
            NAS_CC_StopRabProtectTimer();
            break;

        case MMCC_WCDMA_RAB_RECONFIGURED:
        case MMCC_GSM_WCDMA_INTER_HANDOVER:
        case MMCC_WCDMA_RAB_ESTABLISHED:
            f_stCcTchStatus.ucTchAvail = VOS_TRUE;
            f_stCcTchStatus.bGsm = VOS_FALSE;
        break;

        /* 当前未发生变化,不进行任何处理,直接返回 */
        case MMCC_WCDMA_NO_CHANGE:
            if ((MMCC_CHAN_MOD_BUTT != pstInSyncInd->enChannelMode)
             && (VOS_FALSE == f_stCcTchStatus.ucTchAvail))
            {
                f_stCcTchStatus.ucTchAvail  = VOS_TRUE;
                f_stCcTchStatus.bGsm        = VOS_FALSE;

                break;
            }
            else
            {
                return VOS_OK;
            }

        case MMCC_WCDMA_RAB_RELEASED:
            f_stCcTchStatus.ucTchAvail = VOS_FALSE;
            NAS_CC_StartRabProtectTimer();
            break;

        default:
            NAS_CC_ERR_LOG1("NAS_CC_SetTchStatus: Unknown reason.", (VOS_INT32)enReason);
            return VOS_ERR;
    }

    f_stCcTchStatus.enChannelMode = pstInSyncInd->enChannelMode;

    if(VOS_TRUE == f_stCcTchStatus.ucTchAvail)
    {
        NAS_CC_RealAttachUserConn(f_enCurrItc, entityId);
    }
    else
    {
        NAS_CC_RealDetachUserConn(f_enCurrItc,  entityId);
    }

    return VOS_OK;
}



VOS_BOOL NAS_CC_IsTchAvailable(
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enItc
)
{
    if (VOS_FALSE == f_stCcTchStatus.ucTchAvail)
    {
        return VOS_FALSE;
    }

    if (NAS_CC_ITC_SPEECH == enItc)
    {
        if (VOS_TRUE == f_stCcTchStatus.bGsm)
        {
            if ((f_stCcTchStatus.enChannelMode >= NAS_CC_TCH_TYPE_FR)
             && (f_stCcTchStatus.enChannelMode <= NAS_CC_TCH_TYPE_AMRWB))
            {
                return VOS_TRUE;
            }
            else
            {
                return VOS_FALSE;
            }

        }
        else
        {
            return VOS_TRUE;
        }
    }
    else
    {
        return VOS_TRUE;
    }
}



VOS_VOID NAS_CC_GenarateLocalAlertInd(VOS_VOID)
{
    if (VOS_FALSE == f_bCcLocalAlerting)
    {
        NAS_CC_ProcLocalAlert(NAS_CC_ALERT_START);
        f_bCcLocalAlerting = VOS_TRUE;
    }
}



VOS_VOID NAS_CC_StopLocalAlertInd(VOS_VOID)
{
    if (VOS_TRUE == f_bCcLocalAlerting)
    {
        NAS_CC_ProcLocalAlert(NAS_CC_ALERT_STOP);
        f_bCcLocalAlerting = VOS_FALSE;
    }
}


VOS_VOID NAS_CC_ProcLocalAlert(
    NAS_CC_ALERT_IND_ENUM_U32           enAlertInd
)
{
    NAS_CC_SYNC_IND_STRU                stSyncInd;

    PS_MEM_SET(&stSyncInd, 0, sizeof(NAS_CC_SYNC_IND_STRU));
    stSyncInd.enAlertInd = enAlertInd;
    stSyncInd.ulTchAvail = f_stCcTchStatus.ucTchAvail;

    stSyncInd.enRaMode = NAS_CC_RA_MODE_WCDMA;
    if(VOS_TRUE == f_stCcTchStatus.bGsm)
    {
        stSyncInd.enRaMode = NAS_CC_RA_MODE_GSM;
    }

    stSyncInd.enTchType = f_stCcTchStatus.enChannelMode;
    NAS_CC_SendMnccMsg(NAS_CC_MAX_ENTITY_NUM , MNCC_SYNC_IND, &stSyncInd, sizeof(NAS_CC_SYNC_IND_STRU));
}


VOS_VOID NAS_CC_SetTchAvailValue(
    VOS_BOOL                            bTchAvail
)
{
    f_stCcTchStatus.ucTchAvail = (VOS_UINT8)bTchAvail;
}


NAS_CC_INFO_TRANSFER_CAP_ENUM_U8 NAS_CC_GetCurrItc(
)
{
    return f_enCurrItc;
}


VOS_BOOL NAS_CC_IsGsmNet(VOS_VOID)
{
    return f_stCcTchStatus.bGsm;
}




VOS_UINT32  NAS_CC_IsAttachUserConn( VOS_VOID )
{
    if ( VOS_TRUE == f_bSpeechConnAttached )
    {
        return VOS_TRUE;
    }

    if ( VOS_TRUE == f_bDataConnAttached )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID  NAS_CC_SetUserConnEntity(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMinUnusedIdx = NAS_CC_MAX_ENTITY_NUM;

    /* 寻找一个空闲的位置，记录该呼叫实体建立用户面连接的情况 */
    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if ((NAS_CC_MAX_ENTITY_NUM == ulMinUnusedIdx)
         && (NAS_CC_INVALID_ENTITY_ID == f_connectedEntities[i]))
        {
            ulMinUnusedIdx = i;
        }

        if (f_connectedEntities[i] == entityId)
        {
            /* 该实体已经建立了用户面连接，直接返回 */
            return;
        }
    }
    if(ulMinUnusedIdx >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_CC_NORM_LOG("NAS_CC_AttachUserConn: NO FREE ENTITY.");
        return;
    }
    f_connectedEntities[ulMinUnusedIdx] = entityId;
}

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
