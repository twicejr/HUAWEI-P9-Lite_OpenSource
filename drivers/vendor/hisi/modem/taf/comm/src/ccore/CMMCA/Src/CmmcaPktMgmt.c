/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaPktMgmt.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年01月08日
  最近修改   :
  功能描述   : CMMCA模块PACKET DATA SERVICE相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月08日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CmmcaPktMgmt.h"
#include "CmmcaCtx.h"
#include "CmmcaTimerMgmt.h"

#include "CbpaPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_PKT_MGMT_C
/*lint +e767 修改人: l60609; */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
const CMMCA_PKT_ERR_CODE_MAP_TBL_STRU  g_astCmmcaErrCodeMapTbl[] =
{
    { TAF_PS_CAUSE_SUCCESS,                                             CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR                                        },
    { TAF_PS_CAUSE_INVALID_PARAMETER,                                   CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA                                   },
    { TAF_PS_CAUSE_CID_INVALID,                                         CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_CID                                    },
    { TAF_PS_CAUSE_SIM_INVALID,                                         CMMCA_RAT_MMC_PKT_ERRCODE_SIM_INVILID                                    },

    { TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING,                   CMMCA_RAT_MMC_PKT_ERRCODE_NW_OPERATOR_DETERMINED_BARRING,                },
    { TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,                        CMMCA_RAT_MMC_PKT_ERRCODE_NW_INSUFFICIENT_RESOURCES,                     },
    { TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN,                         CMMCA_RAT_MMC_PKT_ERRCODE_NW_MISSING_OR_UKNOWN_APN,                      },
    { TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE,                      CMMCA_RAT_MMC_PKT_ERRCODE_NW_UNKNOWN_PDP_ADDR_OR_TYPE,                   },
    { TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL ,                     CMMCA_RAT_MMC_PKT_ERRCODE_NW_USER_AUTHENTICATION_FAIL ,                  },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW,        CMMCA_RAT_MMC_PKT_ERRCODE_NW_ACTIVATION_REJECTED_BY_GGSN,     },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,               CMMCA_RAT_MMC_PKT_ERRCODE_NW_ACTIVATION_REJECTED_UNSPECIFIED,            },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED,                  CMMCA_RAT_MMC_PKT_ERRCODE_NW_SERVICE_OPTION_NOT_SUPPORTED,               },
    { TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,              CMMCA_RAT_MMC_PKT_ERRCODE_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,           },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER,                 CMMCA_RAT_MMC_PKT_ERRCODE_NW_SERVICE_OPTION_TEMP_OUT_ORDER,              },
    { TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_NSAPI_ALREADY_USED,                         },
    { TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION,                          CMMCA_RAT_MMC_PKT_ERRCODE_NW_REGULAR_DEACTIVATION,                       },
    { TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED,                              CMMCA_RAT_MMC_PKT_ERRCODE_NW_QOS_NOT_ACCEPTED,                           },
    { TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE,                               CMMCA_RAT_MMC_PKT_ERRCODE_NW_NETWORK_FAILURE,                            },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT,                           CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTIC_ERR_IN_TFT,                        },
    { TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT,                          CMMCA_RAT_MMC_PKT_ERRCODE_NW_SYNTACTIC_ERR_IN_TFT,                       },
    { TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_UKNOWN_PDP_CONTEXT,                         },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER,                 CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTIC_ERR_IN_PACKET_FILTER,              },
    { TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,               CMMCA_RAT_MMC_PKT_ERRCODE_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,            },
    { TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,             CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,          },
    { TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED,                  CMMCA_RAT_MMC_PKT_ERRCODE_NW_LAST_PDN_DISCONN_NOT_ALLOWED,               },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,                    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,                 },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,                    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,                 },
    { TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,              CMMCA_RAT_MMC_PKT_ERRCODE_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,           },
    { TAF_PS_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED,                      CMMCA_RAT_MMC_PKT_ERRCODE_NW_INFORMATION_NOT_RECEIVED,                   },
    { TAF_PS_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST,                 CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDN_CONNECTION_DOES_NOT_EXIST,              },
    { TAF_PS_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED,     CMMCA_RAT_MMC_PKT_ERRCODE_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED,  },
    { TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST,           CMMCA_RAT_MMC_PKT_ERRCODE_NW_COLLISION_WITH_NW_INITIATED_REQUEST,        },
    { TAF_PS_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE,                         CMMCA_RAT_MMC_PKT_ERRCODE_NW_UNSUPPORTED_QCI_VALUE,                      },
    { TAF_PS_CAUSE_SM_NW_INVALID_TI,                                    CMMCA_RAT_MMC_PKT_ERRCODE_NW_INVALID_TI,                                 },
    { TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE,                CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTICALLY_INCORRECT_MESSAGE,             },
    { TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO,                        CMMCA_RAT_MMC_PKT_ERRCODE_NW_INVALID_MANDATORY_INFO,                     },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT,                         CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_TYPE_NON_EXISTENT,                      },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE,                       CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_TYPE_NOT_COMPATIBLE,                    },
    { TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT,                               CMMCA_RAT_MMC_PKT_ERRCODE_NW_IE_NON_EXISTENT,                            },
    { TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_CONDITIONAL_IE_ERR,                         },
    { TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_NOT_COMPATIBLE,                         },
    { TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED,                      CMMCA_RAT_MMC_PKT_ERRCODE_NW_PROTOCOL_ERR_UNSPECIFIED,                   },
    { TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE,                  CMMCA_RAT_MMC_PKT_ERRCODE_NW_APN_RESTRICTION_INCOMPATIBLE,               },

    { TAF_PS_CAUSE_GMM_PS_DETACH,                                       CMMCA_RAT_MMC_PKT_ERRCODE_PS_DETACH                                      },
    { TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH,                             CMMCA_RAT_MMC_PKT_ERRCODE_DETACH_NOT_REATTACH                            }

};

/* g_astCmmcaErrCodeMapTbl的Item个数 */
const VOS_UINT32 g_ulCmmcaErrCodeMapTblSize  = sizeof(g_astCmmcaErrCodeMapTbl) / sizeof(g_astCmmcaErrCodeMapTbl[0]);

/* APS消息处理函数 */
const CMMCA_PKT_EVT_FUNC_TBL_STRU       g_astCmmcaPktPsEvtFuncTbl[] =
{
    /* 设置上下文 */
    {ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF,
        CMMCA_PKT_RcvTafPsEvtSetPrimPdpContextInfoCnf},

    /* 鉴权回复 */
    {ID_EVT_TAF_PS_SET_AUTHDATA_INFO_CNF,
        CMMCA_PKT_RcvTafSetPdnPcoAuthCnf},

    /* PS CALL */
    {ID_EVT_TAF_PS_CALL_ORIG_CNF,
        CMMCA_PKT_RcvTafPsEvtCallOrigCnf},
    {ID_EVT_TAF_PS_CALL_END_CNF,
        CMMCA_PKT_RcvTafPsEvtCallEndCnf},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF,
        CMMCA_PKT_RcvTafPsEvtPdpActivateCnf},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ,
        CMMCA_PKT_RcvTafPsEvtPdpActivateRej},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND,
        CMMCA_PKT_RcvTafPsEvtPdpActivateInd},
    {ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND,
        CMMCA_PKT_RcvTafPsEvtPdpModifyInd},
    {ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF,
        CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf},
    {ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND,
        CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd},
    {ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND,
        CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd},
};

/* g_astCmmcaPktPsEvtFuncTbl的Item个数 */
const VOS_UINT32 g_ulCmmcaPktPsEvtFuncTblSize  = sizeof(g_astCmmcaPktPsEvtFuncTbl) / sizeof(g_astCmmcaPktPsEvtFuncTbl[0]);


/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvCmmcSetPdnTabReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_PDN_TABLE_SETUP_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_RcvCmmcSetPdnTabReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_SET_PDN_TAB_REQ_STRU  stSetPdnTabReq;
    CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU    stPdnTabBuffItem;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpCtxInfo;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stSetPdnTabReq, 0, sizeof(CMMCA_MMC_RAT_SET_PDN_TAB_REQ_STRU));

    PS_MEM_SET(&stPdnTabBuffItem, 0, sizeof(CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU));

    PS_MEM_SET(&stPdpCtxInfo, 0, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseSetPdnTabReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                     pstDataInd->aucData,
                                     &stSetPdnTabReq);

    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);
        return;
    }

    /* 没有要设置的PDN参数，直接返回SUCC */
    if (0 == stSetPdnTabReq.ulTotalNum)
    {
        /* 直接回RSP(SUCC) */
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_SUCC);

        return;
    }

    ucOpId = CMMCA_OPID_INVILID_VALUE;

    /* 分配OP ID */
    CMMCA_AssignOpid(&ucOpId);

    /* 保存PDN TABLE的参数 */
    stPdnTabBuffItem.enCmdId    = ID_CMMCA_MMC_RAT_PDN_TABLE_SETUP_REQ;
    stPdnTabBuffItem.ucCurIndex = 0;
    stPdnTabBuffItem.ucTotalNum = (VOS_UINT8)stSetPdnTabReq.ulTotalNum;
    PS_MEM_CPY(stPdnTabBuffItem.astPdnInfo,
               stSetPdnTabReq.astPdnInfo,
               sizeof(CMMCA_PDN_INFO_STRU) * stSetPdnTabReq.ulTotalNum);

    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(&stPdnTabBuffItem), sizeof(CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU));
    if (VOS_OK != ulRslt)
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);
        return;
    }

    /* 从table index=0开始设置，构造参数 */
    CMMCA_PKT_BuildPrimPdpContextInfo(&(stSetPdnTabReq.astPdnInfo[0]), &stPdpCtxInfo);

    /* 调用TAF_PS_SetPrimPdpContextInfo发送设置请求 */
    ulRslt = TAF_PS_SetPrimPdpContextInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPdpCtxInfo);

    if (VOS_OK != ulRslt)
    {
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvCmmcDefaultBearConnReq_PreProc
 功能描述  : ID_CMMCA_MMC_RAT_DEFAULTBEARER_REQ消息预处理
 输入参数  : CBPCA_DATA_IND_MSG_STRU                     *pstDataInd
 输出参数  : CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU    *pstDefBearConnReq
             VOS_UINT8                                   *pucPdnEntityIndex
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvCmmcDefaultBearConnReq_PreProc(
    CBPCA_DATA_IND_MSG_STRU                     *pstDataInd,
    CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU    *pstDefBearConnReq,
    VOS_UINT8                                   *pucPdnEntityIndex
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    CMMCA_CONN_STATUS_ENUM_UINT8        enCurConnStatus;

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseDefaultBearConnReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                           pstDataInd->aucData,
                                           pstDefBearConnReq);

    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA);
        return VOS_TRUE;
    }

    ucIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstDefBearConnReq->ucPdnId);

    /* 如果该PDN ID对应的实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucIndex)
    {
        /* 分配一个新的实体 */
        CMMCA_PKT_AssignPdnConnEntity(pstDefBearConnReq->ucPdnId, pucPdnEntityIndex);

        /* 没有分配到实体 */
        if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == *pucPdnEntityIndex)
        {
            /* 直接回RSP(FAIL) */
            CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                            CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                            CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA);
            return VOS_TRUE;
        }
        /* 分配到一个新的实体,预处理结束,发起拨号 */
        else
        {
            /* 保存PDN实体的index */
            CMMCA_PKT_SavePdnConnEntityIndex(pstDefBearConnReq->ucPdnId, *pucPdnEntityIndex);

            CMMCA_PKT_SetUserPdnType(*pucPdnEntityIndex, pstDefBearConnReq->enPdnType);

            CMMCA_PKT_SetPdnRequestType(*pucPdnEntityIndex, pstDefBearConnReq->enRequestType);

            return VOS_FALSE;
        }
    }
    /* 如果该PDN ID对应的实体存在 */
    else
    {
        enCurConnStatus = CMMCA_PKT_GetConnStatus(ucIndex);

        /* 如果当前连接处于CONNED状态，直接回复RSP(SUCC) */
        if (CMMCA_CONN_STATUS_CONNED == enCurConnStatus)
        {
            CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                            CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                            CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR);

            return VOS_TRUE;
        }

        /* 如果当前连接处于CONNING或INTERNAL DISCING状态，忽略本次的REQ */
        if ((CMMCA_CONN_STATUS_CONNING == enCurConnStatus)
         || (CMMCA_CONN_STATUS_INTERNAL_DISCING == enCurConnStatus))
        {
            return VOS_TRUE;
        }

        /* 如果当前连接处于DISCING状态，直接回复RSP(FAIL, Errcode:conn is releasing) */
        if (CMMCA_CONN_STATUS_DISCING == enCurConnStatus)
        {
            CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                            CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                            CMMCA_RAT_MMC_PKT_ERRCODE_CONN_IS_RELEASING);
            return VOS_TRUE;
        }

        *pucPdnEntityIndex = ucIndex;

        /* 发起拨号流程 */
        return VOS_FALSE;
    }

}
/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvCmmcDefaultBearConnReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_DEFAULTBEARER_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_RcvCmmcDefaultBearConnReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU                     *pstDataInd = VOS_NULL_PTR;
    TAF_PS_DIAL_PARA_STRU                        stDialPara;
    CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU     stDefBearConnReq;
    VOS_UINT8                                    ucPdnEntityIndex;
    VOS_UINT32                                   ulRslt;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    ucPdnEntityIndex = CMMCA_PDN_CONN_ENTITY_INDEX_INVALID;

    PS_MEM_SET(&stDefBearConnReq, 0, sizeof(CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU));

    PS_MEM_SET(&stDialPara, 0, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_PKT_RcvCmmcDefaultBearConnReq_PreProc(pstDataInd, &stDefBearConnReq, &ucPdnEntityIndex);

    /* 预处理结束,不满足发起拨号 */
    if (VOS_TRUE == ulRslt)
    {
        return;
    }

    /* 获取SDF参数并保存在对应的实体中 */
    ulRslt = CMMCA_PKT_ProcSdfPara(stDefBearConnReq.ucPdnId, ucPdnEntityIndex);

    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndDefaultBearConnRsp(stDefBearConnReq.ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA);

        /* 清除实体及映射关系 */
        CMMCA_PKT_FreePdnConnEntity(stDefBearConnReq.ucPdnId);

        return;
    }

    /* 将选择的SDF参数转化成拨号参数格式 */
    CMMCA_PKT_GetDialParaFromSdfPara(ucPdnEntityIndex, &stDialPara);

    /* 填充PDN Request Type */
    stDialPara.bitOpReqType     = VOS_TRUE;

    if (CMMCA_PDN_REQUEST_TYPE_INITIAL == stDefBearConnReq.enRequestType)
    {
        stDialPara.enPdpRequestType = TAF_PDP_REQUEST_TYPE_INITIAL;
    }
    else
    {
        stDialPara.enPdpRequestType = TAF_PDP_REQUEST_TYPE_HANDOVER;
    }

    /* 调用API接口TAF_PS_CallOrig请求APS建立承载 */
    if (VOS_OK == TAF_PS_CallOrig(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stDialPara))
    {
        /* 更新到CONNING状态 */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNING);

        /* 保存用户拨号请求的PDN类型 */
        CMMCA_PKT_SetUserPdnType(ucPdnEntityIndex, stDefBearConnReq.enPdnType);

        /* 保存用户拨号请求的PDN请求类型 */
        CMMCA_PKT_SetPdnRequestType(ucPdnEntityIndex, stDefBearConnReq.enRequestType);
    }
    else
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndDefaultBearConnRsp(stDefBearConnReq.ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_UNKNOWN);


        /* 清除实体及映射关系 */
        CMMCA_PKT_FreePdnConnEntity(stDefBearConnReq.ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvCmmcBearDiscReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_BEARER_DISCONNECT_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_RcvCmmcBearDiscReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_BEAR_DISC_REQ_STRU    stDiscReq;
    VOS_UINT32                          ulRslt;
    CMMCA_CONN_STATUS_ENUM_UINT8        enCurConnStatus;
    VOS_UINT8                           ucPdnEntityIndex;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stDiscReq, 0 , sizeof(CMMCA_MMC_RAT_BEAR_DISC_REQ_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseBearDiscReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stDiscReq);

    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_FAIL);
        return;
    }

    /* 目前只支持default承载，dedicated承载，直接返回RSP(FAIL) */
    if (VOS_TRUE != stDiscReq.ucIsDefaultBearer)
    {
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_FAIL);
        return;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(stDiscReq.ucPdnId);

    /* 实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        /* 直接回复RSP(SUCC) */
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_SUCC);

        return;
    }

    enCurConnStatus = CMMCA_PKT_GetConnStatus(ucPdnEntityIndex);

    /* 如果当前连接处于DISCING或INTERNAL DISCING状态，忽略本次的REQ */
    if ((CMMCA_CONN_STATUS_DISCING == enCurConnStatus)
     || (CMMCA_CONN_STATUS_INTERNAL_DISCING == enCurConnStatus))
    {
        return;
    }

    /* 如果当前连接处于CONNING或者CONNED状态，停止等待IPV6参数定时器，发起断开拨号请求 */
    CMMCA_StopTimer(WUEPS_PID_CMMCA, TI_CMMCA_WAIT_IPV6_RA_INFO);

    if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, stDiscReq.ucPdnId))
    {
        /* 更新连接状态为DISCING */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_DISCING);
    }
    else
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_FAIL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtSetPrimPdpContextInfoCnf
 功能描述  : 处理ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtSetPrimPdpContextInfoCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   *pstSetPdpCtxInfoCnf = VOS_NULL_PTR;
    CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU            *pstPdnTabBuffItem  = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU                       *pstCmdBuff  = VOS_NULL_PTR;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU                stPdpCtxInfo;
    VOS_UINT32                                   ulRslt;

    pstSetPdpCtxInfoCnf  = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU*)pEvtInfo;

    PS_MEM_SET(&stPdpCtxInfo, 0, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    pstCmdBuff = CMMCA_GetItemFromCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

    if (VOS_NULL_PTR == pstCmdBuff)
    {
        return VOS_ERR;
    }

    /* 如果设置失败，直接给上层返回设置失败 */
    if (TAF_PS_CAUSE_SUCCESS != pstSetPdpCtxInfoCnf->enCause)
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);

        CMMCA_DelItemInCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

        return VOS_ERR;
    }

    pstPdnTabBuffItem = (CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU *)pstCmdBuff->pucMsgInfo;

    /* 如果设置成功，判断当前PdnId是否为PDN table中最后一个，如果是最后一个PdnId，给上层返回设置成功 */
    if ((pstPdnTabBuffItem->ucTotalNum -1 ) == pstPdnTabBuffItem->ucCurIndex )
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_SUCC);

        CMMCA_DelItemInCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

        return VOS_OK;
    }

    /* 否则，从保存的参数中取出下一个PdnId的信息并调用API接口TAF_PS_SetPrimPdpContextInfo设置，OPID使用保存的 */
    pstPdnTabBuffItem->ucCurIndex++;

    CMMCA_PKT_BuildPrimPdpContextInfo(&(pstPdnTabBuffItem->astPdnInfo[pstPdnTabBuffItem->ucCurIndex]),
                                      &stPdpCtxInfo);

    ulRslt = TAF_PS_SetPrimPdpContextInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, pstSetPdpCtxInfoCnf->stCtrl.ucOpId, &stPdpCtxInfo);

    if (VOS_OK != ulRslt)
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);

        CMMCA_DelItemInCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtCallOrigCnf
 功能描述  : 处理ID_EVT_TAF_PS_CALL_ORIG_CNF消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtCallOrigCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_ORIG_CNF_STRU          *pstCallOrigCnf  = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucErrCode;

    pstCallOrigCnf  = (TAF_PS_CALL_ORIG_CNF_STRU*)pEvtInfo;

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(pstCallOrigCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallOrigCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstCallOrigCnf->ucCid);

    /* 实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallOrigCnf: Not Find Entity!");
        return VOS_ERR;
    }

    /* 不是CONNING状态，则直接退出 */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallOrigCnf: Not CONNING state!");
        return VOS_ERR;
    }

    /* APS返回成功，直接退出，等待激活结果 */
    if (TAF_PS_CAUSE_SUCCESS == pstCallOrigCnf->enCause)
    {
        return VOS_OK;
    }

    /* 将APS的错误码转换成CMMC的错误码 */
    ucErrCode = CMMCA_PKT_TransferErrCode(pstCallOrigCnf->enCause);

    /* 回RSP(FAIL) */
    CMMCA_PKT_SndDefaultBearConnRsp(pstCallOrigCnf->ucCid,
                                    CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                    ucErrCode);

    /* 清除实体及映射关系 */
    CMMCA_PKT_FreePdnConnEntity(pstCallOrigCnf->ucCid);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtCallEndCnf
 功能描述  : 处理ID_EVT_TAF_PS_CALL_END_CNF消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtCallEndCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_END_CNF_STRU           *pstCallEndCnf  = VOS_NULL_PTR;
    CMMCA_CONN_STATUS_ENUM_UINT8        enCurConnStatus;
    VOS_UINT8                           ucPdnEntityIndex;

    pstCallEndCnf  = (TAF_PS_CALL_END_CNF_STRU*)pEvtInfo;

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(pstCallEndCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallEndCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstCallEndCnf->ucCid);

    /* 实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallEndCnf: Not Find Entity!");
        return VOS_ERR;
    }

    enCurConnStatus = CMMCA_PKT_GetConnStatus(ucPdnEntityIndex);

    /* 不是DISCING或INTERNAL DISCING状态，则直接退出 */
    if ((CMMCA_CONN_STATUS_DISCING != enCurConnStatus)
     && (CMMCA_CONN_STATUS_INTERNAL_DISCING != enCurConnStatus))
    {
        return VOS_ERR;
    }

    /* APS返回成功，直接退出，等待去激活结果 */
    if (TAF_PS_CAUSE_SUCCESS == pstCallEndCnf->enCause)
    {
        return VOS_OK;
    }
    else
    {
        /* 目前APS只有pdp id对应实体不存在或者Client Id不一致时回复失败 */
        CMMCA_ERROR1_LOG("CMMCA_PKT_RcvTafPsEvtCallEndCnf: End fail, enCause is ", pstCallEndCnf->enCause);

        return VOS_ERR;
    }
}


/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtPdpActivateCnf
 功能描述  : 处理ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf = VOS_NULL_PTR;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnEntityIndex;

    /* 初始化 */
    pstPdpActivateCnf                   = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU*)pEvtInfo;

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpActivateCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpActivateCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    /* 目前只支持缺省承载，如果是专有承载，不处理 */
    if (VOS_TRUE == pstPdpActivateCnf->bitOpLinkdRabId)
    {
        return VOS_ERR;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpActivateCnf->ucCid);

    /* 实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* 当前不在CONNING状态，则直接退出 */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        return VOS_ERR;
    }

    /* 保存PDP信息 */
    pstPdnConnEntity                    = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    CMMCA_PKT_SavePdpInfo(&(pstPdnConnEntity->stPdpInfo), pstPdpActivateCnf);

    /* 根据PDP类型分别处理*/
    switch (pstPdpActivateCnf->stPdpAddr.enPdpType)
    {
        case TAF_PDP_IPV4:
            CMMCA_PKT_ProcIpv4ActCnf(ucPdnEntityIndex, pstPdpActivateCnf);
            break;

        case TAF_PDP_IPV6:
            CMMCA_PKT_ProcIpv6ActCnf(pstPdpActivateCnf);
            break;

        case TAF_PDP_IPV4V6:
            CMMCA_PKT_ProcIpv4v6ActCnf(pstPdpActivateCnf);
            break;

        default:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtPdpActivateRej
 功能描述  : 处理ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateRej(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstPdpActivateRej = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucErrCode;

    /* 初始化 */
    pstPdpActivateRej  = (TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU*)pEvtInfo;

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpActivateRej->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpActivateRej: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex   = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpActivateRej->ucCid);

    /* 实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* 当前不在CONNING状态，则直接退出 */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        return VOS_ERR;
    }

    /* 将APS的错误码转换成CMMC的错误码，IPV4V6需要特殊处理 */
    if ((CMMCA_IP_TYPE_IPV4V6 == CMMCA_PKT_GetUserPdnType(ucPdnEntityIndex))
      && (CMMCA_IP_TYPE_IPV4V6 != pstPdpActivateRej->enPdpType)
      && (VOS_TRUE == pstPdpActivateRej->bitOpCauseEx)
      && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstPdpActivateRej->enCauseEx))
    {
        ucErrCode = CMMCA_PKT_TransferErrCode(pstPdpActivateRej->enCauseEx);
    }
    else
    {
        ucErrCode = CMMCA_PKT_TransferErrCode(pstPdpActivateRej->enCause);
    }

    /* 给上层回复RSP(FAIL, ERR CODE) */
    CMMCA_PKT_SndDefaultBearConnRsp(pstPdpActivateRej->ucCid,
                                    CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                    ucErrCode);

    /* 清除实体及映射关系 */
    CMMCA_PKT_FreePdnConnEntity(pstPdpActivateRej->ucCid);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtPdpActivateInd
 功能描述  : 处理ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateInd(
    VOS_VOID                           *pEvtInfo
)
{
    /* reserved */
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtPdpModifyInd
 功能描述  : 处理ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpModifyInd(
    VOS_VOID                           *pEvtInfo
)
{
    /* reserved */
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf
 功能描述  : 处理ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU    *pstPdpDeactivateCnf = VOS_NULL_PTR;
    CMMCA_CONN_STATUS_ENUM_UINT8            enCurConnStatus;
    VOS_UINT8                               ucPdnEntityIndex;

    /* 初始化 */
    pstPdpDeactivateCnf = (TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU*)pEvtInfo;

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpDeactivateCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex    = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpDeactivateCnf->ucCid);

    /* 实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* 当前不在DISCING或者INTERNAL DISCING状态，则直接退出 */
    enCurConnStatus                     = CMMCA_PKT_GetConnStatus(ucPdnEntityIndex);

    if ((CMMCA_CONN_STATUS_DISCING != enCurConnStatus)
     && (CMMCA_CONN_STATUS_INTERNAL_DISCING != enCurConnStatus))
    {
        return VOS_ERR;
    }

    /* 如果是内部去激活，说明是RA超时导致的，需要回激活的RSP而不是去激活的RSP */
    if (CMMCA_CONN_STATUS_DISCING == enCurConnStatus)
    {
        CMMCA_PKT_SndBearDiscRsp(pstPdpDeactivateCnf->ucCid, CMMCA_RAT_MMC_RESULT_SUCC);
    }
    else
    {
        CMMCA_PKT_SndDefaultBearConnRsp(pstPdpDeactivateCnf->ucCid,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP);
    }

    /* 清除实体及映射关系 */
    CMMCA_PKT_FreePdnConnEntity(pstPdpDeactivateCnf->ucCid);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd
 功能描述  : 处理ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU    *pstPdpDeactivateInd = VOS_NULL_PTR;
    VOS_UINT8                               ucPdnEntityIndex;

    /* 初始化 */
    pstPdpDeactivateInd = (TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU*)pEvtInfo;

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpDeactivateInd->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex    = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpDeactivateInd->ucCid);

    /* 实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* 上报承载去激活指示 */
    CMMCA_PKT_SndBearDiscInd(pstPdpDeactivateInd->ucCid);

    /* 清除实体及映射关系 */
    CMMCA_PKT_FreePdnConnEntity(pstPdpDeactivateInd->ucCid);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd
 功能描述  : 处理ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_IPV6_INFO_IND_STRU          *pstPsIpv6InfoInd = VOS_NULL_PTR;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnEntityAddr = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                           ucPdnEntityIndex;

    /* 初始化 */
    pstPsIpv6InfoInd     = (TAF_PS_IPV6_INFO_IND_STRU*)pEvtInfo;

    PS_MEM_SET(aucIpv6LanAddr, 0, CMMCA_IPV6_ADDR_LEN);

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(pstPsIpv6InfoInd->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    /* 如果没有携带前缀信息，则直接退出 */
    if (0 == pstPsIpv6InfoInd->stIpv6RaInfo.ulPrefixNum)
    {
        return VOS_ERR;
    }

    ucPdnEntityIndex     = CMMCA_PKT_FindPdnConnEntityIndex(pstPsIpv6InfoInd->ucCid);

    /* 找不到PDN对应的实体 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    pstPdnEntityAddr = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    /* 如果当前连接处于CONN状态，仅更新上下文 */
    if (CMMCA_CONN_STATUS_CONNED == CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        /* 保存IPV6 RA INFO*/
        CMMCA_PKT_SaveIpv6RaInfo(&(pstPdnEntityAddr->stPdpInfo), pstPsIpv6InfoInd);
    }

    /* 如果当前连接处于CONNING状态，更新上下文，并通知上层承载激活成功 */
    if (CMMCA_CONN_STATUS_CONNING == CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        /* 停止保护定时器 */
        CMMCA_StopTimer(WUEPS_PID_CMMCA, TI_CMMCA_WAIT_IPV6_RA_INFO);

        /* 保存IPV6 RA INFO*/
        CMMCA_PKT_SaveIpv6RaInfo(&(pstPdnEntityAddr->stPdpInfo), pstPsIpv6InfoInd);

        /* 生成IPV6全局地址 */
        CMMCA_PKT_GenIpv6LanAddrWithRadomIID(pstPsIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstPsIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr);

        /* 更新IPv6全局地址 */
        PS_MEM_CPY(pstPdnEntityAddr->stPdpInfo.stPdpAddr.aucIpV6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* 更新状态为CONN */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNED);

        /* 通知上层承载激活成功 */
        CMMCA_PKT_SndDefaultBearConnRsp(pstPsIpv6InfoInd->ucCid,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafPsEvt
 功能描述  : 处理PS域的事件
 输入参数  : TAF_PS_EVT_STRU                    *pstEvt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_RcvTafPsEvt(
    TAF_PS_EVT_STRU                    *pstEvt
)
{
    CMMCA_PKT_PS_EVT_FUNC               pPsEvtFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRslt;

    /* 查表g_astCmmcaPktPsEvtFuncTbl */
    for (ulIndex = 0; ulIndex < g_ulCmmcaPktPsEvtFuncTblSize; ulIndex++)
    {
        if (pstEvt->ulEvtId == g_astCmmcaPktPsEvtFuncTbl[ulIndex].ulEvtId)
        {
            pPsEvtFunc = g_astCmmcaPktPsEvtFuncTbl[ulIndex].pPsEvtFunc;

            break;
        }
    }

    if (VOS_NULL_PTR == pPsEvtFunc)
    {
        CMMCA_ERROR_LOG("CMMCA_PKT_RcvTafPsEvt: Not find msg proc func");
        return;
    }
    else
    {
        ulRslt = pPsEvtFunc(pstEvt->aucContent);

        if (VOS_OK != ulRslt)
        {
            CMMCA_ERROR_LOG("CMMCA_PKT_RcvTafPsEvt: msg proc func fail");
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTiWaitIpv6RaExp
 功能描述  : 处理TI_CMMCA_WAIT_IPV6_RA_INFO定时器超时消息
 输入参数  : REL_TIMER_MSG                      *pstTiMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_RcvTiWaitIpv6RaExp(
    REL_TIMER_MSG                      *pstTiMsg
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucPdnEntityIndex;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    ucPdnId = (VOS_UINT8)pstTiMsg->ulPara;

    /* Pdn Id有效性检查 */
    if (!CMMCA_IS_VALID_PDN_ID(ucPdnId))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTiWaitIpv6RaExp: Pdn Id is Invalid!");
        return;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    /* 对应的实体不存在 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return;
    }

    /* 当前不在CONNING状态，则直接退出 */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        return;
    }

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    if (VOS_TRUE != pstPdnConnEntity->stPdpInfo.bitOpPdpAddr)
    {
        return;
    }

    /* 如果是IPV6 ONLY, 需要将对应的承载去激活，然后给上层上报RSP(FAIL, ERRCODE(CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP)) */
    if (CMMCA_IP_TYPE_IPV6 == pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType)
    {
        if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, ucPdnId))
        {
            /* 更新连接状态为INTERNAL DISCING */
            CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_INTERNAL_DISCING);
        }
        else
        {
            CMMCA_ERROR_LOG("CMMCA_PKT_RcvTiWaitIpv6RaExp: End call fail");
        }
    }

    /* 如果是IPV4V6, 给上层上报RSP(SUCC, ERRCODE(CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP)) */
    if (CMMCA_IP_TYPE_IPV4V6 == pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType)
    {
        /* 回RSP成功，带原因值等RA超时 */
        CMMCA_PKT_SndDefaultBearConnRsp(ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP);

        /* 更新连接状态为CONN */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNED);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_ProcIpv4ActCnf
 功能描述  : 处理IPV4激活成功消息
 输入参数  : VOS_UINT8                           ucPdnEntityIndex
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_ProcIpv4ActCnf(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
)
{
    /* 更新连接状态为CONN */
    CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNED);

    /* 给上层回复RSP(SUCC) */
    CMMCA_PKT_SndDefaultBearConnRsp(pstPdpActivateCnf->ucCid,
                                    CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                    CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_ProcIpv6ActCnf
 功能描述  : 处理IPV6激活成功消息
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_ProcIpv6ActCnf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
)
{
    /* 启动获取RA的保护定时器，获取到RA后更新连接状态并给上层回复RSP */
    CMMCA_StartTimer(WUEPS_PID_CMMCA,
                     TI_CMMCA_WAIT_IPV6_RA_INFO,
                     TI_CMMCA_WAIT_IPV6_RA_INFO_LEN,
                     pstPdpActivateCnf->ucCid);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_ProcIpv4v6ActCnf
 功能描述  : 处理IPV4V6激活成功消息
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_ProcIpv4v6ActCnf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
)
{
    /* 启动获取RA的保护定时器，获取到RA后更新连接状态并给上层回复RSP */
    CMMCA_StartTimer(WUEPS_PID_CMMCA,
                     TI_CMMCA_WAIT_IPV6_RA_INFO,
                     TI_CMMCA_WAIT_IPV6_RA_INFO_LEN,
                     pstPdpActivateCnf->ucCid);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_BuildPrimPdpContextInfo
 功能描述  : 构造设置主PDP上下文的参数
 输入参数  : CMMCA_PDN_INFO_STRU               *pstPdnInfo
 输出参数  : TAF_PDP_PRIM_CONTEXT_EXT_STRU     *pstPdpCtxInfo
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月8日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_BuildPrimPdpContextInfo(
    CMMCA_PDN_INFO_STRU               *pstPdnInfo,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU     *pstPdpCtxInfo
)
{
    /* 填充CID */
    pstPdpCtxInfo->ucCid     = pstPdnInfo->ucPdnId;

    /* 如果参数只有PDNid，PDN TYPE和APN都为空，按删除处理 */
    if ((0 == pstPdnInfo->ucApnLen)
     && (0 == pstPdnInfo->enPdnType))
    {
        pstPdpCtxInfo->ucDefined = VOS_FALSE;
    }
    else
    {
        pstPdpCtxInfo->ucDefined = VOS_TRUE;

        /* PDN TYPE */
        if (CMMCA_IS_VALID_PDN_TYPE(pstPdnInfo->enPdnType))
        {
            pstPdpCtxInfo->bitOpPdpType = VOS_TRUE;
            pstPdpCtxInfo->enPdpType    = pstPdnInfo->enPdnType;
        }

        /* APN */
        if (0 != pstPdnInfo->ucApnLen)
        {
            pstPdpCtxInfo->bitOpApn = VOS_TRUE;
            PS_MEM_CPY(pstPdpCtxInfo->aucApn, pstPdnInfo->aucApn, pstPdnInfo->ucApnLen);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_FillDefaultBearConnSuccPara
 功能描述  : 填充承载激活成功参数
 输入参数  : VOS_UINT8                                   ucPdnEntityIndex
             CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode
 输出参数  : CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU   *pstDefaultBearConnCnf
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_FillDefaultBearConnSuccPara(
    VOS_UINT8                                   ucPdnEntityIndex,
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode,
    CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU   *pstDefaultBearConnCnf
)
{
    VOS_UINT8                           ucRabId;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    ucRabId = pstPdnConnEntity->stPdpInfo.ucRabId;

    /* Bear Id */
    pstDefaultBearConnCnf->ucBearerId   = 0xF0 | ucRabId;

    /* Addr */
    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.bitOpPdpAddr)
    {
        pstDefaultBearConnCnf->enPdnType    = pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType;

        PS_MEM_CPY(pstDefaultBearConnCnf->aucIpv4Addr,
                   pstPdnConnEntity->stPdpInfo.stPdpAddr.aucIpV4Addr,
                   CMMCA_IPV4_ADDR_LEN);

        PS_MEM_CPY(pstDefaultBearConnCnf->aucIpv6Addr,
                   pstPdnConnEntity->stPdpInfo.stPdpAddr.aucIpV6Addr,
                   CMMCA_IPV6_ADDR_LEN);

        /* IPV4V6，RA超时时需要特殊处理*/
        if (CMMCA_IP_TYPE_IPV4V6 == pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType)
        {
            if (CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP == enErrCode)
            {
                pstDefaultBearConnCnf->enPdnType = CMMCA_IP_TYPE_IPV4;

                PS_MEM_SET(pstDefaultBearConnCnf->aucIpv6Addr, 0, CMMCA_IPV6_ADDR_LEN);
            }
        }
    }

    /* IPV4 DNS */
    pstDefaultBearConnCnf->ucDns4Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.bitOpPriDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns4Addr[pstDefaultBearConnCnf->ucDns4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.aucPriDns,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns4Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.bitOpSecDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns4Addr[pstDefaultBearConnCnf->ucDns4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.aucSecDns,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns4Num++;
    }

    /* IPV4 PCSCF*/
    pstDefaultBearConnCnf->ucPcscf4Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf4Addr[pstDefaultBearConnCnf->ucPcscf4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv4Pcscf.aucPrimPcscfAddr,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf4Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Pcscf.bitOpSecPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf4Addr[pstDefaultBearConnCnf->ucPcscf4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.aucSecPcscfAddr,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf4Num++;
    }

    /* Gate Way */
    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpGateWay.bitOpGateWayAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucRouteAddr,
                   pstPdnConnEntity->stPdpInfo.stPdpGateWay.aucGateWayAddr,
                   CMMCA_IPV4_ADDR_LEN);
    }

    /* IPV6 DNS */
    pstDefaultBearConnCnf->ucDns6Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.bitOpPriDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns6Addr[pstDefaultBearConnCnf->ucDns6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.aucPriDns,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns6Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.bitOpSecDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns6Addr[pstDefaultBearConnCnf->ucDns6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.aucSecDns,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns6Num++;
    }

    /* IPV6 PCSCF*/
    pstDefaultBearConnCnf->ucPcscf6Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf6Addr[pstDefaultBearConnCnf->ucPcscf6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.aucPrimPcscfAddr,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf6Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.bitOpSecPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf6Addr[pstDefaultBearConnCnf->ucPcscf6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.aucSecPcscfAddr,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf6Num++;
    }


    /* Interface Id */
    PS_MEM_CPY(pstDefaultBearConnCnf->aucIp6InterfaceId,
               pstPdnConnEntity->stPdpInfo.aucPdpIpv6IfId,
               CMMCA_IPV6_INTERFACE_ID_BYTE_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_BuildDefaultBearConnRsp
 功能描述  : 构造CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU
 输入参数  : VOS_UINT8                                   ucPdnId
             CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8   enRslt
             CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode
             CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU   *pstDefaultBearConnCnf
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_BuildDefaultBearConnRsp(
    VOS_UINT8                                   ucPdnId,
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8   enRslt,
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode,
    CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU   *pstDefaultBearConnCnf
)
{
    VOS_UINT8                           ucPdnEntityIndex;

    pstDefaultBearConnCnf->ucPdnId             = ucPdnId;

    /* BearId为0xf0 | RabId，初始化为0xf0 */
    pstDefaultBearConnCnf->ucBearerId          = 0xf0;
    pstDefaultBearConnCnf->enRslt              = enRslt;
    pstDefaultBearConnCnf->enErrCode           = enErrCode;
    pstDefaultBearConnCnf->enSelBearerCtrlMode = CMMCA_PDN_SEL_BEARER_CTRL_MODE_NW_AND_UE;

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return;
    }

    /* 成功需要打包其它参数*/
    if (CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC == enRslt)
    {
        CMMCA_PKT_FillDefaultBearConnSuccPara(ucPdnEntityIndex, enErrCode, pstDefaultBearConnCnf);
    }
    else
    {
        /* 如果PDN id对应的实体分配了IP地址，使用上下文保存的PDN TYPE，否则使用上层设置下来的 */
        if (VOS_TRUE == CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.bitOpPdpAddr)
        {
            pstDefaultBearConnCnf->enPdnType = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.stPdpAddr.enIpType;
        }
        else
        {
            pstDefaultBearConnCnf->enPdnType = CMMCA_PKT_GetUserPdnType(ucPdnEntityIndex);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_SndSetPdnRsp
 功能描述  : 发送默认承载激活请求结果ID_CMMCA_RAT_MMC_PDN_TABLE_SETUP_RSP
 输入参数  : CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM_UINT8    enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_SndSetPdnRsp(
    CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM_UINT8    enRslt
)
{
    CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU  stSetPdnTabCnf;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_SET_PDN_TAB_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    PS_MEM_SET(&stSetPdnTabCnf, 0, sizeof(CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU));

    stSetPdnTabCnf.enRslt = enRslt;

    /* 调用CMMCA_PackSetPdnTabRsp，打包PDN设置回复消息 */
    ulRslt = CMMCA_PackSetPdnTabRsp(&stSetPdnTabCnf, CMMCA_CMD_SET_PDN_TAB_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发送至cbpca */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_SET_PDN_TAB_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_SndDefaultBearConnRsp
 功能描述  : 发送默认承载激活请求结果ID_CMMCA_RAT_MMC_DEFAULTBEARER_RSP
 输入参数  : VOS_UINT8                                   ucPdnId
             CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8   enRslt
             CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CMMCA_PKT_SndDefaultBearConnRsp(
    VOS_UINT8                                   ucPdnId,
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8   enRslt,
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode
)
{
    CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU    stDefaultBearConnCnf;
    VOS_UINT8                                  *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                                  ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_DEFAULT_BEAR_CONN_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    PS_MEM_SET(&stDefaultBearConnCnf, 0, sizeof(CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU));

    /* 调用CMMCA_PKT_BuildDefaultBearConnRsp构造激活请求回复的参数 */
    CMMCA_PKT_BuildDefaultBearConnRsp(ucPdnId, enRslt, enErrCode, &stDefaultBearConnCnf);

    /* 调用CMMCA_PackDefaultBearConnRsp，打包默认承载激活回复消息 */
    ulRslt = CMMCA_PackDefaultBearConnRsp(&stDefaultBearConnCnf, CMMCA_CMD_DEFAULT_BEAR_CONN_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发送至cbpca */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_DEFAULT_BEAR_CONN_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_SndBearDiscRsp
 功能描述  : 发送承载断开请求结果ID_CMMCA_RAT_MMC_BEARER_DISCONNECT_RSP
 输入参数  : VOS_UINT8                           ucPdnId,
             CMMCA_RAT_MMC_RESULT_ENUM_UINT8     enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_SndBearDiscRsp(
    VOS_UINT8                           ucPdnId,
    CMMCA_RAT_MMC_RESULT_ENUM_UINT8     enRslt
)
{
    /* 构造 CMMCA_RAT_MMC_BEAR_DISC_CNF_STRU */
    CMMCA_RAT_MMC_BEAR_DISC_CNF_STRU    stBearDiscCnf;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    stBearDiscCnf.ucPdnId    = ucPdnId;
    stBearDiscCnf.enRslt     = enRslt;
    stBearDiscCnf.ucBearerId = 0xf0;

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    /* 如果该Pdn Id实体已分配 */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID != ucPdnEntityIndex)
    {
        ucRabId = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.ucRabId;
        stBearDiscCnf.ucBearerId = 0xf0 | ucRabId;
    }

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_BEAR_DISC_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    /* 调用CMMCA_PackBearDiscRsp函数打包发送消息 */
    ulRslt = CMMCA_PackBearDiscRsp(&stBearDiscCnf, CMMCA_CMD_BEAR_DISC_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_BEAR_DISC_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_SndBearDiscInd
 功能描述  : 发送承载断开指示ID_CMMCA_RAT_MMC_BEARER_DISCONNECT_IND
 输入参数  : VOS_UINT8                           ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_SndBearDiscInd(
    VOS_UINT8                           ucPdnId
)
{
    CMMCA_RAT_MMC_BEAR_DISC_IND_STRU    stBearDiscInd;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return;
    }

    ucRabId = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.ucRabId;

    /* 构造CMMCA_RAT_MMC_BEAR_DISC_IND_STRU */
    stBearDiscInd.ucPdnId    = ucPdnId;
    stBearDiscInd.ucBearerId = 0xf0 | ucRabId;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_BEAR_DISC_IND_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    /* 调用CMMCA_PackBearDiscInd函数打包发送消息 */
    ulRslt = CMMCA_PackBearDiscInd(&stBearDiscInd, CMMCA_CMD_BEAR_DISC_IND_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_BEAR_DISC_IND_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_FindSelSdfPara
 功能描述  : 查找PdnId对应的SDF参数
 输入参数  : VOS_UINT8                           ucPdnId
             VOS_UINT32                          ulSdfNum
             TAF_SDF_PARA_STRU                  *pstSdfPara
 输出参数  : VOS_UINT32                         *pulIndex
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_FindSelSdfPara(
    VOS_UINT8                           ucPdnId,
    VOS_UINT32                          ulSdfNum,
    TAF_SDF_PARA_STRU                  *pstSdfPara,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i;

    if (0 == ulSdfNum)
    {
        return VOS_ERR;
    }

    for (i = 0; i < ulSdfNum; i++)
    {
        if (ucPdnId != pstSdfPara[i].ucCid)
        {
            continue;
        }

        /* PDN TYPE */
        if (VOS_TRUE != pstSdfPara[i].bitOpPdnType)
        {
            continue;
        }

        if ((pstSdfPara[i].enPdnType < TAF_PDP_IPV4)
         || (pstSdfPara[i].enPdnType > TAF_PDP_IPV4V6))
        {
            continue;
        }

        /* APN */
        if (VOS_TRUE != pstSdfPara[i].bitOpApn)
        {
            continue;
        }

        *pulIndex = i;

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_SaveSelSdfPara
 功能描述  : 保存PdnId对应的SDF参数
 输入参数  : VOS_UINT8                           ucPdnEntityIndex
             TAF_SDF_PARA_STRU                  *pstSdfPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_SaveSelSdfPara(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_SDF_PARA_STRU                  *pstSdfPara
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    PS_MEM_SET(&(pstPdnConnEntity->stSelSdfPara), 0x0, sizeof(CMMCA_SEL_SDF_PARA_STRU));

    /* Cid */
    pstPdnConnEntity->stSelSdfPara.ucCid                    = pstSdfPara->ucCid;

    /* Linked Cid */
    pstPdnConnEntity->stSelSdfPara.bitOpLinkdCid            = pstSdfPara->bitOpLinkdCid;
    pstPdnConnEntity->stSelSdfPara.ucLinkdCid               = pstSdfPara->ucLinkdCid;

    /* Pdn Type */
    pstPdnConnEntity->stSelSdfPara.bitOpPdnType             = pstSdfPara->bitOpPdnType;
    pstPdnConnEntity->stSelSdfPara.enPdnType                = pstSdfPara->enPdnType;

    /* Apn */
    pstPdnConnEntity->stSelSdfPara.bitOpApn = pstSdfPara->bitOpApn;
    PS_MEM_CPY(&(pstPdnConnEntity->stSelSdfPara.stApnInfo),
               &pstSdfPara->stApnInfo,
               sizeof(TAF_PDP_APN_STRU));

    /* Auth */
    pstPdnConnEntity->stSelSdfPara.bitOpGwAuthInfo = pstSdfPara->bitOpGwAuthInfo;
    PS_MEM_CPY(&(pstPdnConnEntity->stSelSdfPara.stGwAuthInfo),
               &pstSdfPara->stGwAuthInfo,
               sizeof(TAF_GW_AUTH_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_ProcSdfPara
 功能描述  : SDF参数处理
 输入参数  : VOS_UINT8                           ucPdnId
             VOS_UINT8                           ucPdnEntityIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_ProcSdfPara(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucPdnEntityIndex
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulSelSdfIndex;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo = VOS_NULL_PTR;

    pstSdfQueryInfo = (TAF_SDF_PARA_QUERY_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstSdfQueryInfo, 0x0, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    /* 调用API接口TAF_PS_GetCidSdfParaInfo获取所有NV项中的SDF配置信息 */
    ulRslt = TAF_PS_GetCidSdfParaInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstSdfQueryInfo);

        return VOS_ERR;
    }

    /* 从获取的列表中选择对应的SDF参数 */
    ulSelSdfIndex = 0;

    ulRslt = CMMCA_PKT_FindSelSdfPara(ucPdnId,
                                      pstSdfQueryInfo->ulSdfNum,
                                      pstSdfQueryInfo->astSdfPara,
                                      &ulSelSdfIndex);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstSdfQueryInfo);

        return VOS_ERR;
    }

    /* 存储选择的SDF参数 */
    CMMCA_PKT_SaveSelSdfPara(ucPdnEntityIndex, &(pstSdfQueryInfo->astSdfPara[ulSelSdfIndex]));

    PS_MEM_FREE(WUEPS_PID_CMMCA, pstSdfQueryInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_GetDialParaFromSdfPara
 功能描述  : 从SDF参数中获取拨号请求的参数
 输入参数  : VOS_UINT8                           ucPdnEntityIndex,
             TAF_PS_DIAL_PARA_STRU              *pstDialPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_GetDialParaFromSdfPara(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_PS_DIAL_PARA_STRU              *pstDialPara
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    PS_MEM_SET(pstDialPara, 0, sizeof(TAF_PS_DIAL_PARA_STRU));

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    pstDialPara->ucCid                  = pstPdnConnEntity->stSelSdfPara.ucCid;
    pstDialPara->enPdpType              = pstPdnConnEntity->stSelSdfPara.enPdnType;

    /* 赋值APN信息 */
    if (VOS_TRUE == pstPdnConnEntity->stSelSdfPara.bitOpApn)
    {
        pstDialPara->bitOpApn = VOS_TRUE;

        /* 拨号APN参数没有长度字段，是因为是字符串格式，已在结尾加上'\0' */
        PS_MEM_CPY(pstDialPara->aucApn,
                   pstPdnConnEntity->stSelSdfPara.stApnInfo.aucValue,
                   pstPdnConnEntity->stSelSdfPara.stApnInfo.ucLength);
    }

    /* 赋值鉴权参数 */
    if (VOS_TRUE == pstPdnConnEntity->stSelSdfPara.bitOpGwAuthInfo)
    {
        pstDialPara->bitOpAuthType      = VOS_TRUE;
        pstDialPara->enAuthType         = pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.enAuthType;

        if (0 != pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucUserNameLen)
        {
            pstDialPara->bitOpUserName  = VOS_TRUE;

            /* 拨号用户名参数没有长度字段，是因为是字符串格式，已在结尾加上'\0' */
            PS_MEM_CPY(pstDialPara->aucUserName,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.aucUserName,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucUserNameLen);
        }

        if (0 != pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucPwdLen)
        {
            pstDialPara->bitOpPassWord  = VOS_TRUE;

            /* 拨号密码参数没有长度字段，是因为是字符串格式，已在结尾加上'\0' */
            PS_MEM_CPY(pstDialPara->aucPassWord,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.aucPwd,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucPwdLen);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_GenIpv6LanAddrWithRadomIID
 功能描述  : 获取IPv6动态全局地址
 输入参数  : VOS_UINT8                          *pucPrefix
             VOS_UINT32                          ulPrefixByteLen
             VOS_UINT8                          *pucIpv6LanAddr
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
)
{
    VOS_UINT32                         *paulAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulTick;

    paulAddr = (VOS_UINT32 *)pucIpv6LanAddr;

    if (ulPrefixByteLen > CMMCA_IPV6_PREFIX_BYTE_LEN)
    {
        CMMCA_ERROR_LOG("CMMCA_PKT_GenIpv6LanAddrWithRadomIID: Prefix Len > 8");
        return;
    }

    /* 拷贝IPv6地址前缀 */
    PS_MEM_CPY(pucIpv6LanAddr, pucPrefix, ulPrefixByteLen);

    ulTick = VOS_GetTick();

    /* 在进行PC测试时，不使用随机值 */
#if (VOS_WIN32 == VOS_OS_VER)
    paulAddr[2] = 0xFFFFFFFF;

    paulAddr[3] = 0xFFFFFFFF;

#else
    VOS_SetSeed(ulTick);
    paulAddr[2] = VOS_Rand(0xFFFFFFFF);

    VOS_SetSeed(ulTick + 10);
    paulAddr[3] = VOS_Rand(0xFFFFFFFF);

#endif

    *(VOS_UINT8 *)(&paulAddr[2]) &= ~0x02;

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_TransferErrCode
 功能描述  : 将TAF的错误码转换为CMMC的错误码
 输入参数  : TAF_PS_CAUSE_ENUM_UINT32            enCause
 输出参数  : 无
 返 回 值  : CMMCA_RAT_MMC_PKT_ERRCODE_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月29日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CMMCA_RAT_MMC_PKT_ERRCODE_UINT8 CMMCA_PKT_TransferErrCode(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < g_ulCmmcaErrCodeMapTblSize; ulIndex++)
    {
        if (enCause == g_astCmmcaErrCodeMapTbl[ulIndex].enCause)
        {
            return g_astCmmcaErrCodeMapTbl[ulIndex].enErrCode;
        }
    }

    return CMMCA_RAT_MMC_PKT_ERRCODE_UNKNOWN;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_SndSetPdnPcoAuthRsp
 功能描述  : 发送PDN鉴权结果
 输入参数  : CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM_UINT8    enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月27日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_PKT_SndSetPdnPcoAuthRsp(
    CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM_UINT8        enRslt
)
{
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_SET_PND_PCO_AUTH_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    /* 调用CMMCA_PackSetPdnTabRsp，打包PDN设置回复消息 */
    ulRslt = CMMCA_PackSetPdnPcoAuthRsp(enRslt, CMMCA_CMD_SET_PND_PCO_AUTH_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发送至cbpca */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_SET_PND_PCO_AUTH_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvTafSetPdnPcoAuthCnf
 功能描述  : 处理ID_EVT_TAF_PS_SET_AUTHDATA_INFO_CNF消息
 输入参数  : VOS_VOID                           *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月26日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_PKT_RcvTafSetPdnPcoAuthCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_SET_AUTHDATA_INFO_CNF_STRU  *pstSetPdnPcoAuthCnf = VOS_NULL_PTR;

    pstSetPdnPcoAuthCnf  = (TAF_PS_SET_AUTHDATA_INFO_CNF_STRU*)pEvtInfo;

    if (TAF_PS_CAUSE_SUCCESS == pstSetPdnPcoAuthCnf->enCause)
    {
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_SUCC);
    }
    else
    {
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_FAIL);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_RcvCmmcSetPdnPcoAuthReq
 功能描述  : 处理ID_CMMCA_MMC_API_SET_PDN_PCO_AUTH_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CMMCA_PKT_RcvCmmcSetPdnPcoAuthReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd      = VOS_NULL_PTR;
    TAF_AUTHDATA_EXT_STRU                   stAuthdataExt;
    VOS_UINT32                              ulRslt;
    VOS_UINT8                               ucOpid;

    /* 初始化 */
    PS_MEM_SET(&stAuthdataExt, 0x0, sizeof(TAF_AUTHDATA_EXT_STRU));

    /* 参考VIA接口文档，解析消息 */
    pstDataInd      = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* 做参数检查和转换 */
    ulRslt = CMMCA_ParseSetPdnPcoAuthReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                         pstDataInd->aucData,
                                         &stAuthdataExt);
    if (VOS_ERR == ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_FAIL);
        return;
    }

    /* 申请OPID */
    ucOpid = 0x0;
    CMMCA_AssignOpid(&ucOpid);

    /* 调用APS的函数处理消息 */
    ulRslt = TAF_PS_SetAuthDataInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpid, &stAuthdataExt);
    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_FAIL);
        return;
    }

    return;
}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

