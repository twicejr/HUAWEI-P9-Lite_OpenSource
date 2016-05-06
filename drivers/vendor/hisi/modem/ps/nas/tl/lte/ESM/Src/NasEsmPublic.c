/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmPublic.c
  Description     : 提供SM模块公共操作
  History         :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.孙兵 49683         2009-01-06  Modify BA8D00870
     3.杨茜惠 00135146    2009-03-06  Modify BA8D01127
     4.李洪00150010       2009-08-03  Modify  BJ9D01608
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmPublic.h"
#include    "NasEsmInclude.h"
#include    "NasCommBuffer.h"
#include    "NasCommPrint.h"
#include    "PsMd5.h"
#include    "NasIpInterface.h"
#include    "IpComm.h"
#include    "UsimPsInterface.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMPUBULIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMPUBULIC_C
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

/* 删除PCO flag相关无效代码 y00307272 20151205 DTS2015101700432 */

VOS_UINT32                              g_ulMd5Flag     = NAS_ESM_FUN_MD5_CTRL_ON;
VOS_UINT32                              g_ulDelSdfWithQosFlag = LPS_NV_GET_DEL_SDF_WITH_QOS_BIT;

VOS_UINT8                               g_aucChallengeValue[NAS_ESM_AUTH_CHALLENGE_VALUE_LEN] = {
                                                                0x36,0x50,0x4e,0x20,0x77,0x47,0x19,0x93,
                                                                0xa0,0x24,0x13,0x34,0xb3,0x39,0xe3,0x65};

VOS_UINT8                               g_aucChallegeRspValue[NAS_ESM_AUTH_RESPONSE_VALUE_LEN] = {
                                                                0x57,0x14,0x72,0x31,0x04,0xa3,0x19,0x69,
                                                                0xb5,0x24,0x45,0x87,0x64,0x29,0xc4,0xb6};


NAS_ESM_APP_ERROR_MAPPING_STRU  g_astEsmAppErrorMappingTbl[] =
{
    {APP_SUCCESS                                        ,NAS_ESM_CAUSE_SUCCESS                                    },
    {APP_ERR_SM_NW_PROT_ERR_UNSPECIFIED                 ,NAS_ESM_CAUSE_ERROR                                      },

    {APP_ERR_SM_NW_OPERATOR_DETERMINED_BARRING                  ,NAS_ESM_CAUSE_OPERATOR_DETERMINE_BARRING                 },
    {APP_ERR_SM_NW_INSUFFICIENT_RESOURCES                       ,NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES                     },
    {APP_ERR_SM_NW_MISSING_OR_UKNOWN_APN                        ,NAS_ESM_CAUSE_UNKNOWN_OR_MISSING_APN                     },
    {APP_ERR_SM_NW_UNKNOWN_PDN_TYPE                             ,NAS_ESM_CAUSE_UNKNOWN_PDN_TYPE                           },
    {APP_ERR_SM_NW_USER_AUTH_FAIL                               ,NAS_ESM_CAUSE_USER_AUTH_FAIL                             },
    {APP_ERR_SM_NW_REQ_REJ_BY_SGW_OR_PGW                        ,NAS_ESM_CAUSE_REQ_REJ_BY_SGW_OR_PGW                      },
    {APP_ERR_SM_NW_REQ_REJ_UNSPECITY                            ,NAS_ESM_CAUSE_REQ_REJ_UNSPECITY                          },
    {APP_ERR_SM_NW_SERVICE_OPTION_NOT_SUPPORT                   ,NAS_ESM_CAUSE_SERVICE_OPTION_NOT_SUPPORT                 },
    {APP_ERR_SM_NW_REQ_SERVICE_NOT_SUBSCRIBE                    ,NAS_ESM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED                 },
    {APP_ERR_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER                ,NAS_ESM_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER              },
    {APP_ERR_SM_NW_PTI_ALREADY_IN_USE                           ,NAS_ESM_CAUSE_PTI_ALREADY_IN_USED                        },
    {APP_ERR_SM_NW_REGULAR_DEACT                                ,NAS_ESM_CAUSE_REGULAR_DEACTIVATION                       },
    {APP_ERR_SM_NW_EPS_QOS_NOT_ACCEPT                           ,NAS_ESM_CAUSE_EPS_QOS_NOT_ACCEPT                         },
    {APP_ERR_SM_NW_NET_FAIL                                     ,NAS_ESM_CAUSE_NETWORK_FAILURE                            },
    {APP_ERR_SM_NW_PROT_ERR_UNSPECIFIED                         ,NAS_ESM_CAUSE_FEATURE_NOT_SUPPORTED                      },
    {APP_ERR_SM_NW_SEMANTIC_ERR_IN_TFT                          ,NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT                        },
    {APP_ERR_SM_NW_SYNTACTIC_ERR_IN_TFT                         ,NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT                       },
    {APP_ERR_SM_NW_INVALID_EPS_BERER_IDENTITY                   ,NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY                },
    {APP_ERR_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER                ,NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER              },
    {APP_ERR_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER              ,NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER            },
    {APP_ERR_SM_NW_BEARER_WITHOUT_TFT_ACT                       ,NAS_ESM_CAUSE_BEARER_WITHOUT_TFT_ACT                     },
    {APP_ERR_SM_NW_PTI_MISMATICH                                ,NAS_ESM_CAUSE_PTI_MISMATCH                               },
    {APP_ERR_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED                 ,NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED               },
    {APP_ERR_SM_NW_PDN_TPYE_IPV4_ONLY_ALLOWED                   ,NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED                  },
    {APP_ERR_SM_NW_PDN_TPYE_IPV6_ONLY_ALLOWED                   ,NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED                  },
    {APP_ERR_SM_NW_SINGLE_ADDR_BERERS_ONLY_ALLOWED              ,NAS_ESM_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED            },
    {APP_ERR_SM_NW_ESM_INFO_NOT_RECEIVED                        ,NAS_ESM_CAUSE_ESM_INFORMATION_NOT_RECEIVED               },
    {APP_ERR_SM_NW_PDN_CONN_NOT_EXIST                           ,NAS_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST              },
    {APP_ERR_SM_NW_MULTI_PDN_CONN_FOR_ONE_APN_NOT_ALLOWED       ,NAS_ESM_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED  },
    {APP_ERR_SM_NW_COLLISION_WITH_NW_INTIAL_REQEST              ,NAS_ESM_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST   },
    {APP_ERR_SM_NW_UNSUPPORTED_QCI_VALUE                        ,NAS_ESM_CAUSE_UNSUPPORTED_QCI_VALUE                      },
    {APP_ERR_SM_NW_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN      ,NAS_ESM_CAUSE_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN                      },
    {APP_ERR_SM_NW_INVALID_PTI_VALUE                            ,NAS_ESM_CAUSE_INVALID_PTI_VALUE                          },
    {APP_ERR_SM_NW_SYNCTACTIC_INCORRECT_MSG                     ,NAS_ESM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE             },
    {APP_ERR_SM_NW_INVALID_MANDATORY_INFOR                      ,NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION              },
    {APP_ERR_SM_NW_MSG_TYPE_NON_EXIST                           ,NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED  },
    {APP_ERR_SM_NW_MSG_TYPE_NOT_COMPATIBLE_WITH_PROT            ,NAS_ESM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA  },
    {APP_ERR_SM_NW_INFOR_ELEM_NON_EXIST                         ,NAS_ESM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED  },
    {APP_ERR_SM_NW_CONDITIONAL_IE_ERROR                         ,NAS_ESM_CAUSE_CONDITIONAL_IE_ERROR                       },
    {APP_ERR_SM_NW_MSG_NOT_COMPATIBLE_WITH_PROT                 ,NAS_ESM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA       },
    {APP_ERR_SM_NW_PROT_ERR_UNSPECIFIED                         ,NAS_ESM_CAUSE_PROTOCOL_ERROR                             },

    {APP_ERR_SM_NW_APN_RESTRICTION_INCOMPATIBLE_WITH_ACT_EPS_BEARER , NAS_ESM_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER}

};

NAS_COMM_PRINT_LIST_STRU g_astEsmAppMsgIdArray[] =
{
    {   ID_APP_ESM_SET_TFT_REQ               ,
            "MSG:  ID_APP_ESM_SET_TFT_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_SET_TFT_CNF     ,
            "MSG:  ID_APP_ESM_SET_TFT_CNF                 ",
        NAS_ESM_PrintEsmAppSetResult},
    {   ID_APP_ESM_SET_QOS_REQ               ,
            "MSG:  ID_APP_ESM_SET_QOS_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_SET_QOS_CNF               ,
            "MSG:  ID_APP_ESM_SET_QOS_CNF                           ",
        NAS_ESM_PrintEsmAppSetResult},
    {   ID_APP_ESM_SET_EPS_QOS_REQ             ,
            "MSG:  ID_APP_ESM_SET_EPS_QOS_REQ                         ",
        NAS_ESM_PrintAppEsmSetEpsQosReqMsg},
    {   ID_APP_ESM_SET_EPS_QOS_CNF               ,
            "MSG:  ID_APP_ESM_SET_EPS_QOS_CNF                           ",
        NAS_ESM_PrintEsmAppSetResult},
    {   ID_APP_ESM_SET_APN_REQ     ,
            "MSG:  ID_APP_ESM_SET_APN_REQ                 ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_SET_APN_CNF               ,
            "MSG:  ID_APP_ESM_SET_APN_CNF                           ",
        NAS_ESM_PrintEsmAppSetResult},
    {   ID_APP_ESM_SET_PCO_REQ               ,
            "MSG:  ID_APP_ESM_SET_PCO_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_SET_PCO_CNF             ,
            "MSG:  ID_APP_ESM_SET_PCO_CNF                         ",
        NAS_ESM_PrintEsmAppSetResult},
    {   ID_APP_ESM_SET_PDN_TYPE_REQ               ,
            "MSG:  ID_APP_ESM_SET_PDN_TYPE_REQ                           ",
        NAS_ESM_PrintAppEsmSetPdnTypeReqMsg},
    {   ID_APP_ESM_SET_PDN_TYPE_CNF     ,
            "MSG:  ID_APP_ESM_SET_PDN_TYPE_CNF                 ",
        NAS_ESM_PrintEsmAppSetResult},
    {   ID_APP_ESM_SET_BEARER_TYPE_REQ               ,
            "MSG:  ID_APP_ESM_SET_BEARER_TYPE_REQ                           ",
        NAS_ESM_PrintAppEsmSetBearerTypeReqMsg},
    {   ID_APP_ESM_SET_BEARER_TYPE_CNF               ,
            "MSG:  ID_APP_ESM_SET_BEARER_TYPE_CNF                           ",
        NAS_ESM_PrintEsmAppSetResult},
    {   ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ             ,
            "MSG:  ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ                         ",
        NAS_ESM_PrintAppEsmSetManageTypeReqMsg},
    {   ID_APP_ESM_SET_PDP_MANAGER_TYPE_CNF               ,
            "MSG:  ID_APP_ESM_SET_PDP_MANAGER_TYPE_CNF                           ",
        NAS_ESM_PrintEsmAppSetManageTypeResult},
    {   ID_APP_ESM_SET_GW_AUTH_REQ,
            "MSG:  ID_APP_ESM_SET_GW_AUTH_REQ                           ",
        NAS_ESM_PrintAppEsmSetGwAuthReqMsg},
    {   ID_APP_ESM_SET_GW_AUTH_CNF               ,
        "MSG:  ID_APP_ESM_SET_GW_AUTH_CNF                           ",
        NAS_ESM_PrintEsmAppSetResult},

    {   ID_APP_ESM_SET_CGDCONT_REQ,
            "MSG:  ID_APP_ESM_SET_CGDCONT_REQ                           ",
        NAS_ESM_PrintAppEsmSetCgdontReqMsg},
    {   ID_APP_ESM_SET_CGDCONT_CNF               ,
        "MSG:  ID_APP_ESM_SET_CGDCONT_CNF                           ",
        NAS_ESM_PrintEsmAppCgdontResult},

    {   ID_APP_ESM_IPV6_INFO_NOTIFY               ,
        "MSG:  ID_APP_ESM_IPV6_INFO_NOTIFY                           ",
        NAS_ESM_PrintEsmAppIpv6InfoNotify},
    {   ID_APP_ESM_PROCEDURE_ABORT_NOTIFY     ,
            "MSG:  ID_APP_ESM_PROCEDURE_ABORT_NOTIFY                 ",
        NAS_ESM_PrintEsmAppProcedureAbortNotify},
    {   ID_APP_ESM_INQ_TFT_REQ     ,
            "MSG:  ID_APP_ESM_INQ_TFT_REQ                 ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_TFT_CNF               ,
            "MSG:  ID_APP_ESM_INQ_TFT_CNF                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_QOS_REQ               ,
            "MSG:  ID_APP_ESM_INQ_QOS_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_QOS_CNF             ,
            "MSG:  ID_APP_ESM_INQ_QOS_CNF                         ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_EPS_QOS_REQ               ,
            "MSG:  ID_APP_ESM_INQ_EPS_QOS_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_EPS_QOS_CNF     ,
            "MSG:  ID_APP_ESM_INQ_EPS_QOS_CNF                 ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_APN_REQ               ,
            "MSG:  ID_APP_ESM_INQ_APN_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_APN_CNF               ,
            "MSG:  ID_APP_ESM_INQ_APN_CNF                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_PCO_REQ             ,
            "MSG:  ID_APP_ESM_INQ_PCO_REQ                         ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_PCO_CNF               ,
            "MSG:  ID_APP_ESM_INQ_PCO_CNF                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_PDN_TYPE_REQ     ,
            "MSG:  ID_APP_ESM_INQ_PDN_TYPE_REQ                 ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_PDN_TYPE_CNF               ,
            "MSG:  ID_APP_ESM_INQ_PDN_TYPE_CNF                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_BEARER_TYPE_REQ               ,
            "MSG:  ID_APP_ESM_INQ_BEARER_TYPE_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_BEARER_TYPE_CNF             ,
            "MSG:  ID_APP_ESM_INQ_BEARER_TYPE_CNF                         ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_PDP_MANAGER_TYPE_REQ               ,
        "MSG:  ID_APP_ESM_INQ_PDP_MANAGER_TYPE_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_PDP_MANAGER_TYPE_CNF     ,
        "MSG:  ID_APP_ESM_INQ_PDP_MANAGER_TYPE_CNF                 ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_BEAER_QOS_REQ               ,
        "MSG:  ID_APP_ESM_INQ_BEAER_QOS_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_BEAER_QOS_CNF               ,
        "MSG:  ID_APP_ESM_INQ_BEAER_QOS_CNF                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_BEAER_QOS_IND             ,
        "MSG:  ID_APP_ESM_INQ_BEAER_QOS_IND                         ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ               ,
        "MSG:  ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF     ,
        "MSG:  ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF                 ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ               ,
        "MSG:  ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF               ,
        "MSG:  ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_DYNAMIC_TFT_REQ             ,
        "MSG:  ID_APP_ESM_INQ_DYNAMIC_TFT_REQ                         ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_DYNAMIC_TFT_CNF               ,
            "MSG:  ID_APP_ESM_INQ_DYNAMIC_TFT_CNF                           ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_GW_AUTH_REQ             ,
        "MSG:  ID_APP_ESM_INQ_GW_AUTH_REQ                         ",
        VOS_NULL_PTR},
    {   ID_APP_ESM_INQ_GW_AUTH_CNF               ,
            "MSG:  ID_APP_ESM_INQ_GW_AUTH_CNF                           ",
        VOS_NULL_PTR},
    {   ID_OM_ESM_INFO_REPORT_REQ               ,
            "MSG:  ID_OM_ESM_INFO_REPORT_REQ                           ",
        VOS_NULL_PTR},
    {   ID_OM_ESM_INFO_REPORT_CNF,
        "MSG:  ID_APP_OM_INFO_REPORT_CNF                           ",
        VOS_NULL_PTR},
    #if (FEATURE_PTM == FEATURE_ON)
    {   ID_OM_FTM_CTRL_IND                   ,
            "MSG:  ID_OM_FTM_CTRL_IND                               ",
        VOS_NULL_PTR},
    {   ID_OM_FTM_REPROT_IND                   ,
            "MSG:  ID_OM_FTM_REPROT_IND                             ",
        VOS_NULL_PTR},
    #endif
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astEsmStateTimerArray[] =
{
    {   TI_NAS_ESM_T3482               ,
            "STATE TI:  TI_NAS_ESM_T3482                           "},
    {   TI_NAS_ESM_T3492     ,
            "STATE TI:  TI_NAS_ESM_T3492                 "},
    {   TI_NAS_ESM_T3480               ,
            "STATE TI:  TI_NAS_ESM_T3480                           "},
    {   TI_NAS_ESM_T3481               ,
            "STATE TI:  TI_NAS_ESM_T3481                           "},
    {   TI_NAS_ESM_WAIT_APP_CNF             ,
            "STATE TI:  TI_NAS_ESM_WAIT_APP_CNF                         "},
    {   TI_NAS_ESM_WAIT_PTI_INVALID               ,
            "STATE TI:  TI_NAS_ESM_WAIT_PTI_INVALID                           "},
    {   TI_NAS_ESM_ATTACH_BEARER_REEST               ,
            "STATE TI:  TI_NAS_ESM_ATTACH_BEARER_REEST                           "},
    {   TI_NAS_ESM_REL_NON_EMC_BEARER,
            "STATE TI:  TI_NAS_ESM_REL_NON_EMC_BEARER               "}
};



VOS_UINT32      g_ulEmmEsmOpId = 0;

/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_UINT32  NAS_ESM_AllocEmmEsmOpId( VOS_VOID )
{
    g_ulEmmEsmOpId++;
    if(g_ulEmmEsmOpId == NAS_ESM_EMM_OPID_NOT_VAILID)
    {
        g_ulEmmEsmOpId = 0;
    }

    return g_ulEmmEsmOpId;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name   : NAS_ESM_SendBeginSessionNotify
 Description     : ESM开始申请资源的函数封装
 Input           :
 Output          :
 Return          : VOS_VOID

 History         :
    1.lifuxin  00253982       2014-07-02   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SendBeginSessionNotify(VOS_VOID)
{
    EMM_ESM_BEGIN_SESSION_NOTIFY_STRU     *pstEmmEsmBeginSessionNotity = VOS_NULL_PTR;

    /*lint -e961*/
    NAS_ESM_LOG1("NAS_ESM_SendBeginSessionNotify is entered,BearerSessionFlag:", NAS_ESM_GetBearerSessionStartFlag());
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_SendBeginSessionNotify_ENUM, LNAS_ENTRY, NAS_ESM_GetBearerSessionStartFlag());
    /*lint +e961*/

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*如果射频共享开关关闭，则不进行下面的处理*/
        NAS_ESM_INFO_LOG("NAS_ESM_SendBeginSessionNotify: g_ulDsdsRFSharedFlag=PS_FALSE!!!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SendBeginSessionNotify_ENUM, 1);
        return;
    }

    if(NAS_ESM_YES == NAS_ESM_GetBearerSessionStartFlag())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SendBeginSessionNotify: RF resouce have applied!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SendBeginSessionNotify_ENUM, 2);
        return;
    }

    /*置上start session标识*/
    NAS_ESM_SetBearerSessionStartFlag(NAS_ESM_YES);

    /*分配空间并检验分配是否成功*/
    pstEmmEsmBeginSessionNotity = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_BEGIN_SESSION_NOTIFY_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEmmEsmBeginSessionNotity)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SendBeginSessionNotify:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SendBeginSessionNotify_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    /*lint -e960*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEmmEsmBeginSessionNotity),
                        NAS_ESM_GET_MSG_LENGTH(pstEmmEsmBeginSessionNotity),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEmmEsmBeginSessionNotity));
    /*lint +e960*/

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstEmmEsmBeginSessionNotity, ID_EMM_ESM_BEGIN_SESSION_NOTITY);

    pstEmmEsmBeginSessionNotity->enSessionType = EMM_ESM_SESSION_TYPE_ESM;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEmmEsmBeginSessionNotity);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SendBeginSessionNotify
 Description     : ESM结束申请资源的函数封装
 Input           :
 Output          :
 Return          : VOS_VOID

 History         :
    1.lifuxin  00253982       2014-07-02   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SendEndSessionNotify(VOS_VOID)
{
    EMM_ESM_END_SESSION_NOTIFY_STRU     *pstEmmEsmEndSessionNotity;

    /*lint -e961*/
    NAS_ESM_LOG1("NAS_ESM_SendEndSessionNotify is entered,BearerSessionFlag:", NAS_ESM_GetBearerSessionStartFlag());
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_SendEndSessionNotify_ENUM, LNAS_ENTRY, NAS_ESM_GetBearerSessionStartFlag());
    /*lint +e961*/

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*如果射频共享开关关闭，则不进行下面的处理*/
        NAS_ESM_INFO_LOG("NAS_ESM_SendEndSessionNotify: g_ulDsdsRFSharedFlag=PS_FALSE!!!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SendEndSessionNotify_ENUM, 1);
        return;
    }

    if(NAS_ESM_NO == NAS_ESM_GetBearerSessionStartFlag())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SendEndSessionNotify: RF resouce have release!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SendEndSessionNotify_ENUM, 2);
        return;
    }

    /*清零start session标示*/
    NAS_ESM_SetBearerSessionStartFlag(NAS_ESM_NO);

    /*分配空间并检验分配是否成功*/
    pstEmmEsmEndSessionNotity = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(EMM_ESM_END_SESSION_NOTIFY_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEmmEsmEndSessionNotity)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SendEndSessionNotify:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SendEndSessionNotify_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    /*lint -e960*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEmmEsmEndSessionNotity),
                        NAS_ESM_GET_MSG_LENGTH(pstEmmEsmEndSessionNotity),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEmmEsmEndSessionNotity));
    /*lint +e960*/

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstEmmEsmEndSessionNotity, ID_EMM_ESM_END_SESSION_NOTITY);

    pstEmmEsmEndSessionNotity->enSessionType = EMM_ESM_SESSION_TYPE_ESM;

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstEmmEsmEndSessionNotity);
}
#endif

/*****************************************************************************
 Function Name   : NAS_ESM_IsGbrBearer
 Description     : 判断是否是GBR承载
 Input           : ucQci--------QCI
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-1-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsGbrBearer( VOS_UINT8 ucQci )
{
    if ((ucQci >= NAS_ESM_QCI_TYPE_QCI1_GBR) && (ucQci <= NAS_ESM_QCI_TYPE_QCI4_GBR))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetBearCntxtType
 Description     : 获取承载类型
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-31  Draft Enact

*****************************************************************************/
NAS_ESM_BEARER_TYPE_ENUM_UINT8  NAS_ESM_GetBearCntxtType( VOS_UINT32 ulEpsbId )
{
    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetBearCntxtType:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetBearCntxtType_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_BEARER_TYPE_BUTT;
    }

    return (NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)].enBearerCntxtType;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SetBearCntxtType
 Description     : 设置承载类型
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SetBearCntxtType
(
    VOS_UINT32                          ulEpsbId,
    NAS_ESM_BEARER_TYPE_ENUM_UINT8      enDestType
)
{
    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetBearCntxtType:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetBearCntxtType_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    (NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)].enBearerCntxtType = enDestType;
}


/*****************************************************************************
 Function Name   : NAS_ESM_GetBearCntxtState
 Input           : 获取承载状态
 Output          : None
 Return          : NAS_ESM_BEARER_STATE_ENUM_UINT8

 History         :
    1.lihong00150010      2009-8-28  Draft Enact

*****************************************************************************/
NAS_ESM_BEARER_STATE_ENUM_UINT8 NAS_ESM_GetBearCntxtState(VOS_UINT32 ulEpsbId)
{
    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetBearCntxtState:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetBearCntxtState_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_BEARER_STATE_INACTIVE;
    }

    return (NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)].enBearerCntxtState;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SetBearCntxtState
 Input           : 设置承载状态
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-28  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_SetBearCntxtState
(
    VOS_UINT32                          ulEpsbId,
    NAS_ESM_BEARER_STATE_ENUM_UINT8     enDestState
)
{
    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetBearCntxtState:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetBearCntxtState_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    NAS_ESM_LOG1("SM Bearer Context state change----EpsbId : ", ulEpsbId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_SetBearCntxtState_ENUM, 1, ulEpsbId);
    NAS_ESM_PRINT_BEARCNTXTSTA(NAS_ESM_GetBearCntxtState(ulEpsbId));
    NAS_ESM_NORM_LOG("==>>");
    (NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)].enBearerCntxtState = enDestState;
    NAS_ESM_PRINT_BEARCNTXTSTA(enDestState);
    NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
 }

/*****************************************************************************
 Function Name   : NAS_ESM_SetBearCntxtLinkCid
 Description     : 设置承载关联的CID
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-8-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SetBearCntxtLinkCid
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
)
{
    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SetBearCntxtLinkCid:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SetBearCntxtLinkCid_ENUM, LNAS_PARAM_INVALID);
        return ;
    }
    /*lint -e701*/
    (NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)].ulBitCId |= NAS_ESM_BIT_0 << ulCid;
    /*lint +e701*/

    (NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)].bitOpCId = NAS_ESM_OP_TRUE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ClearBearCntxtLinkCid
 Description     : 清除承载关联CID
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-8-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ClearBearCntxtLinkCid
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
)
{
    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ClearBearCntxtLinkCid:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearBearCntxtLinkCid_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    /*lint -e701*/
    ((NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)].ulBitCId &= (~((VOS_UINT32)(NAS_ESM_BIT_0 << ulCid))));
    /*lint +e701*/
}

/*****************************************************************************
 Function Name   : NAS_ESM_UpdateBearCntextLinkCid
 Description     : 更新承载关联CID
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-05-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_UpdateBearCntextLinkCid
(
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg,
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
)
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;

    /* 若此次修改不带TFT信息，或者承载类型为缺省承载，则无需更新承载的关联CID信息 */
    if ((NAS_ESM_OP_TRUE != pstDecodedNwMsg->bitOpTadInfo)
        || (NAS_ESM_BEARER_TYPE_DEDICATED != NAS_ESM_GetBearCntxtType(ulEpsbId)))
    {
        return ;
    }

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);

    /* 当TAD码为ADD_FILTER或REPLACE_FILTER(因为ADD和REPLACE FILTER都有可能添加一个SDF)，
       则将承载与此SDF相关联；当TAD码为DELETE_FILTER，且此SDF下所有packet filter都被删除，
       则将承载与此SDF去除关联 */
    switch(pstDecodedNwMsg->stTadInfo.enTftOpType)
    {
        case NAS_ESM_TFT_OP_TYPE_ADD_FILTER:
        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:
            NAS_ESM_SetBearCntxtLinkCid(ulEpsbId, ulCid);
            break;
        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:
            if (NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
            {
                NAS_ESM_ClearBearCntxtLinkCid(ulEpsbId, ulCid);
            }
            break;
        default:
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetEpsbCntxtInfoAddr
 Description     : 获取承载信息
 Input           : None
 Output          : None
 Return          : NAS_ESM_EPSB_CNTXT_INFO_STRU *

 History         :
    1.lihong00150010      2009-9-1  Draft Enact

*****************************************************************************/
NAS_ESM_EPSB_CNTXT_INFO_STRU * NAS_ESM_GetEpsbCntxtInfoAddr( VOS_UINT32 ulEpsbId )
{
    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEpsbCntxtInfoAddr:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEpsbCntxtInfoAddr_ENUM, LNAS_PARAM_INVALID);
        return &((NAS_ESM_Entity())->astEpsbCntxtInfo[(NAS_ESM_MAX_EPSB_ID - NAS_ESM_MIN_EPSB_ID)]);
    }

    return &((NAS_ESM_Entity())->astEpsbCntxtInfo[(ulEpsbId - NAS_ESM_MIN_EPSB_ID)]);
}


/*****************************************************************************
 Function Name  : NAS_ESM_AssignOpId
 Discription    : 分配SM与EMM交互使用的OpId
 Input          : VOS_UINT32         *pulOpId
 Output         : VOS_UINT32         *pulOpId
 Return         : None
 History:
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AssignOpId(VOS_UINT32         *pulOpId)
{
    VOS_UINT32                         ulOpId = NAS_ESM_NULL;

    /*获取当前最大OpId*/
    ulOpId = NAS_ESM_GetCurMaxOpIdValue();

    /*如果还未到最大值，直接加1*/
    if( ulOpId < NAS_ESM_MAX_OPID_VALUE )
    {
        (*pulOpId) = ulOpId + 1;
    }
    else/*如果已经是最大值，从初值开始分配*/
    {
        (*pulOpId) = NAS_ESM_MIN_OPID_VALUE;
    }

    NAS_ESM_SetCurMaxOpIdValue(*pulOpId);
}

/*****************************************************************************
 Function Name  : NAS_ESM_AssignErabmOpId
 Discription    : 分配SM与ERABM交互使用的OpId
 Input          : VOS_UINT32         *pulOpId
 Output         : VOS_UINT32         *pulOpId
 Return         : None
 History:
      1.wangchen 00209181   2014-07-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AssignErabmSessionId(VOS_UINT8         *pucOpId)
{
    VOS_UINT8                         ucOpId = NAS_ESM_NULL;

    /*获取当前最大OpId*/
    ucOpId = NAS_ESM_GetErabmSessionIdValue();

    /*如果还未到最大值，直接加1*/
    if( ucOpId < NAS_ESM_PTI_MAX_VALUE )
    {
        (*pucOpId) = ucOpId + 1;
    }
    else/*如果已经是最大值，从初值开始分配*/
    {
        (*pucOpId) = NAS_ESM_MIN_OPID_VALUE + 1;
    }
    NAS_ESM_SetErabmSessionIdValue(*pucOpId);
}

/*****************************************************************************
 Function Name  : NAS_ESM_AssignPTI
 Discription    : 分配SM与网侧交互使用的PTI,并保存到承载信息中
 Input          : VOS_UINT32         *pulPti
 Output         : VOS_UINT32         *pulPti
 Return         : None
 History:
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_AssignPTI(VOS_UINT32         *pulPti)
{
    VOS_UINT8                          ucPti = NAS_ESM_NULL;

    /*获取当前最大PTI*/
    ucPti = NAS_ESM_GetCurMaxPTIValue();

    /*如果还未到最大值，直接加1*/
    if( ucPti < NAS_ESM_PTI_MAX_VALUE)
    {
        (*pulPti) = (VOS_UINT32)(ucPti + 1);
    }
    else/*如果已经是最大值，从初值开始分配*/
    {
        (*pulPti) = NAS_ESM_PTI_MIN_VALUE;
    }

    NAS_ESM_SetCurMaxPTIValue((VOS_UINT8)(*pulPti));
}

/*****************************************************************************
 Function Name   : NAS_ESM_AssignGwIpId
 Description     : 分配网关鉴权时携带的Identifier
 Input           : VOS_UINT8   *pucGwAuthId
 Output          : VOS_UINT8   *pucGwAuthId
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-7-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AssignGwIpId( VOS_UINT8   *pucGwAuthId)
{
    VOS_UINT8                          ucGwAuthId = NAS_ESM_NULL;

    /*获取当前最大PTI*/
    ucGwAuthId = NAS_ESM_GetCurMaxGwAuthIdVaule();

    /*如果还未到最大值，直接加1*/
    if( ucGwAuthId < NAS_ESM_GWAUTHID_MAX_VALUE)
    {
        *pucGwAuthId = ucGwAuthId + 1;
    }
    else/*如果已经是最大值，从初值开始分配*/
    {
        *pucGwAuthId = NAS_ESM_GWAUTHID_MIN_VALUE;
    }

    NAS_ESM_SetCurMaxGwAuthIdVaule(*pucGwAuthId);
}

/*****************************************************************************
 Function Name   : NAS_ESM_Random
 Description     : 获取32位的随机数
 Input           : NONE
 Output          : NONE
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010       2010-8-19   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_ESM_Random()
{
    return PS_RAND(NAS_ESM_MAX_UINT32);
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetGwAuthChallegeValue
 Description     : 获取网关CHAP鉴权过程Challenge message中的Challenge值
 Input           : VOS_UINT8 *paucValue
 Output          : VOS_UINT8 *paucValue
 Return          : VOS_VOID

 History         :
    1.leili  00132387       2010-7-15   Draft Enact
    2.lihong 00150010       2010-8-19   Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_GetGwAuthChallengeValue( VOS_UINT8 *pucValue )
{
    VOS_UINT32                          ulRandTmp   = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt       = NAS_ESM_NULL;
    VOS_UINT32                          ulOffSet    = NAS_ESM_NULL;
    VOS_UINT32                          ulLoopTimes = NAS_ESM_NULL;
    VOS_UINT8                           aucChallengeValue[NAS_ESM_AUTH_CHALLENGE_VALUE_LEN] = {NAS_ESM_NULL};

    if (NAS_ESM_GetMd5Flag() == NAS_ESM_FUN_MD5_CTRL_ON)
    {
        ulLoopTimes = (sizeof(aucChallengeValue) / sizeof(ulRandTmp));
        for (ulCnt = NAS_ESM_NULL; ulCnt < ulLoopTimes; ulCnt++)
        {
            ulRandTmp = NAS_ESM_Random();

            aucChallengeValue[ulOffSet++] = (VOS_UINT8)((ulRandTmp & NAS_ESM_FOURTH_BYTE)
                                                            >> NAS_ESM_MOVEMENT_24_BITS);
            aucChallengeValue[ulOffSet++] = (VOS_UINT8)((ulRandTmp & NAS_ESM_THIRD_BYTE)
                                                            >> NAS_ESM_MOVEMENT_16_BITS);
            aucChallengeValue[ulOffSet++] = (VOS_UINT8)((ulRandTmp & NAS_ESM_HIGH_BYTE)
                                                            >> NAS_ESM_MOVEMENT_8_BITS);
            aucChallengeValue[ulOffSet++] = (VOS_UINT8)(ulRandTmp & NAS_ESM_LOW_BYTE);
        }

        NAS_ESM_MEM_CPY_S(  pucValue,
                            NAS_ESM_AUTH_CHALLENGE_VALUE_LEN,
                            aucChallengeValue,
                            NAS_ESM_AUTH_CHALLENGE_VALUE_LEN);
    }
    else
    {
        NAS_ESM_MEM_CPY_S(  pucValue,
                            NAS_ESM_AUTH_CHALLENGE_VALUE_LEN,
                            NAS_ESM_GetChallegeValue(),
                            NAS_ESM_AUTH_CHALLENGE_VALUE_LEN);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetGwAuthRpsValue
 Description     : 获取网关CHAP鉴权过程Response message中的Response值
 Input           : VOS_UINT8 *pucPwd --------CHAP鉴权密码
                   VOS_UINT8 ucId -----------CHAP鉴权标识
                   VOS_UINT8 *pucChlgVal ----CHAP鉴权Chellenge value
 Output          : VOS_UINT8 *pucRspVal -----CHAP鉴权Response value
 Return          : VOS_VOID

 History         :
    1.leili  00132387       2010-7-15   Draft Enact
    2.lihong 00150010       2010-8-19   Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_GetGwAuthRpsValue
(
    const VOS_UINT8                    *pucPwd,
    VOS_UINT8                           ucPwdLen,
    VOS_UINT8                           ucId,
    const VOS_UINT8                    *pucChlgVal,
    VOS_UINT8                          *pucRspVal
)
{
    VOS_CHAR                            acMd5Input[NAS_ESM_MAX_MD5_INPUT_PARA_LEN]   = {NAS_ESM_NULL};
    VOS_UCHAR                           aucRspValue[NAS_ESM_AUTH_RESPONSE_VALUE_LEN] = {NAS_ESM_NULL};
    VOS_UCHAR                           ucLen = NAS_ESM_NULL;

    if (NAS_ESM_GetMd5Flag() == NAS_ESM_FUN_MD5_CTRL_ON)
    {
        /* The Response Value is the one-way hash calculated over a stream of
           octets consisting of the Identifier, followed by (concatenated
           with) the "secret", followed by (concatenated with) the Challenge
           Value. */
        acMd5Input[0] = (VOS_CHAR)ucId;

        NAS_ESM_MEM_CPY_S(  &acMd5Input[1],
                            ucPwdLen,
                            pucPwd,
                            ucPwdLen);

        NAS_ESM_MEM_CPY_S(  &acMd5Input[1 + ucPwdLen],
                            NAS_ESM_AUTH_CHALLENGE_VALUE_LEN,
                            pucChlgVal,
                            NAS_ESM_AUTH_CHALLENGE_VALUE_LEN);

        ucLen = 1 + ucPwdLen + NAS_ESM_AUTH_CHALLENGE_VALUE_LEN;

        /* 调用MD5算法产生challege respose value */
        PS_MD5String(acMd5Input, aucRspValue, ucLen);

        NAS_ESM_MEM_CPY_S(  pucRspVal,
                            NAS_ESM_AUTH_RESPONSE_VALUE_LEN,
                            aucRspValue,
                            NAS_ESM_AUTH_RESPONSE_VALUE_LEN);
    }
    else
    {
        NAS_ESM_MEM_CPY_S(  pucRspVal,
                            NAS_ESM_AUTH_RESPONSE_VALUE_LEN,
                            NAS_ESM_GetChallegeRspValue(),
                            NAS_ESM_AUTH_RESPONSE_VALUE_LEN);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_QueryPfInTft
 Description     : 在TFT信息中查找指定的PF
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-8-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_QueryPfInTft
(
    VOS_UINT8                           ucPacketFilterID,
    const APP_ESM_TFT_INFO_STRU        *pstCntxtTftInfo,
    VOS_UINT32                          ulPfNum,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    const NAS_ESM_CONTEXT_TFT_STRU     *pstTmpTFT       = VOS_NULL_PTR;

    /* 遍历TFT中的所有PF信息，查找指定的PF ID */
    for (ulCnt = NAS_ESM_NULL; ulCnt < ulPfNum; ulCnt++)
    {
        pstTmpTFT = &(pstCntxtTftInfo[ulCnt]);
        if (ucPacketFilterID == pstTmpTFT->ucPacketFilterId)
        {
            *pulIndex = ulCnt;

            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_QueryEpsbCntxtTblByCid
 Discription    : 根据CID查询EpsbCntxtTbl表，得到对应承载号
 Input          : VOS_UINT32          ulCId
                  VOS_UINT32         *pulEpsId
 Output         : VOS_UINT32         *pulEpsId
 Return         : VOS_UINT32(如果没有查到返回SM_FAILURE,否则返回SM_SUCCESS)
 History:
      1.祝义强      2009-02-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryEpsbCntxtTblByCid(VOS_UINT32  ulCId,
                                       VOS_UINT32  *pulEpsbId)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU        *pstEpsbCntxtInfo   = VOS_NULL_PTR;

    /*搜索 StateInfoTbl*/
    for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
    {
        /*根据EpsId取出承载信息*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulCnt);

        /*此承载已经关联CID*/
        if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpCId )
        {
            /*此承载信息中的CID等于指定CID*/
            if( NAS_ESM_OP_TRUE ==((pstEpsbCntxtInfo->ulBitCId >> ulCId )&NAS_ESM_BIT_0))
            {
                /*此时已经关联EPSbID,返回此承载ID*/
                (*pulEpsbId) = ulCnt;
                return NAS_ESM_SUCCESS;
            }
        }
    }

    /*如果没有找到，返回SM_FAILURE*/
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_QueryEpsbCntxtTblByEpsbId
 Discription    : 查找EpsbCntxtTbl表中有没有关联CID，如果有则返回该CID，
 Input          : VOS_UINT32          ulEpsbId
 Output         : VOS_UINT32         *ulCId
 Return         : VOS_UINT32(如果没有查到返回SM_FAILURE,否则返回SM_SUCCESS)
 History:
      1.祝义强      2009-02-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryEpsbCntxtTblByEpsbId(VOS_UINT32  ulEpsbId,
                                       VOS_UINT32  *pulCId)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt            = 0;
    VOS_UINT32                          ulTmpCid         = 0;

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    ulTmpCid = pstEpsbCntxtInfo->ulBitCId;

    /*如果EpsbCntxtTbl表中，没有关联的CID，则返回错误信息*/
    if(NAS_ESM_OP_FALSE == pstEpsbCntxtInfo->bitOpCId)
    {
        return NAS_ESM_FAILURE;
    }

    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if(NAS_ESM_OP_TRUE ==((ulTmpCid >> ulCnt )& NAS_ESM_BIT_0))
        {
            /*暂时先返回关联的值最小的CID*/
            (*pulCId) = ulCnt;
            return NAS_ESM_SUCCESS;
        }
    }

    /*如果没有关联CID，返回SM_FAILURE*/
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_QueryFirstSdfIdByEpsbId
 Description     : 根据承载号,查找第一个满足条件的SDF号
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2009-4-16  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryFirstSdfIdByEpsbId
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                         *pulCid
)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;

    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_QueryFirstSdfIdByEpsbId:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_QueryFirstSdfIdByEpsbId_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_FAILURE;
    }

    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);
        if(ulEpsbId == pstSdfCntxtInfo->ulEpsbId)
        {
            /*暂时先返回关联的值最小的CID*/
            (*pulCid) = ulCnt;
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_QuerySdfIdByEpsbIdAndPfId
 Description     : 根据承载号和PF号，查找SDF号
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2009-4-16  Draft Enact
    2.lihong00150010    2009-7-14   Modify

*****************************************************************************/
VOS_UINT32 NAS_ESM_QuerySdfIdByEpsbIdAndPfId
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                           ucPacketFilterId,
    VOS_UINT32                         *pulCid
)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt2              = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;

    /* 根据承载号和PF号，查找SDF号 */
    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

        /* 判断承载号是否相同 */
        if(ucEpsbId == pstSdfCntxtInfo->ulEpsbId)
        {
            for(ulCnt2 = 0; ulCnt2 < pstSdfCntxtInfo->ulSdfPfNum; ulCnt2++)
            {
                /* 判断PF号是否相同 */
                if(ucPacketFilterId == pstSdfCntxtInfo->astSdfPfInfo[ulCnt2].ucNwPacketFilterId)
                {
                    *pulCid = ulCnt;
                    return NAS_ESM_SUCCESS;
                }
            }
        }
    }

    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_GetQuerySdfIdResult
 Description     : 获取查找SDF号的结果
 Input           : None
 Output          : None
 Return          : NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8

 History         :
    1.lihong 00150010      2009-7-14  Draft Enact

*****************************************************************************/
NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8  NAS_ESM_GetQuerySdfIdResult
(
     VOS_UINT32                         ulFindNum,
     VOS_UINT32                         ulPacketFilterNum,
     PS_BOOL_ENUM_UINT8                 enIsCidEqual
)
{
    /* 全部找到的情况 */
    if(ulFindNum == ulPacketFilterNum)
    {
        if(PS_TRUE == enIsCidEqual)
        {
            return NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_EQUAL_CID;
        }
        else
        {
            return NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_UNEQUAL_CID;
        }
    }

    /* 全部没找到的情况 */
    if(NAS_ESM_NULL == ulFindNum)
    {
        return NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND;
    }

    /* 部分找到的情况 */
    if(PS_TRUE == enIsCidEqual)
    {
        return NAS_ESM_QUERY_CID_RSLT_PART_FOUND_EQUAL_CID;
    }
    else
    {
        return NAS_ESM_QUERY_CID_RSLT_PART_FOUND_UNEQUAL_CID;
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_QuerySdfId
 Description     : 查找SDF号
 Input           : None
 Output          : None
 Return          : NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8

 History         :
    1.lihong 00150010      2009-7-14  Draft Enact

*****************************************************************************/
NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8  NAS_ESM_QuerySdfId
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    VOS_UINT32                         *pulCid
)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT32                          ulFindNum           = NAS_ESM_NULL;
    VOS_UINT32                          ulCid               = NAS_ESM_ILL_CID;
    VOS_UINT32                          ulLastCid           = NAS_ESM_ILL_CID;
    VOS_UINT8                           ucPacketFilter      = NAS_ESM_NULL;
    PS_BOOL_ENUM_UINT8                  enIsCidEqual        = PS_TRUE;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;

    /* 判断是否为缺省承载*/
    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(pstEsmNwMsgIE->ucEpsbId)))
      ||(NAS_ESM_OP_TRUE != pstEsmNwMsgIE->bitOpTadInfo))
    {
        /* 根据承载号,查找第一个满足条件的SDF号 */
        ulRslt = NAS_ESM_QueryFirstSdfIdByEpsbId(pstEsmNwMsgIE->ucEpsbId, pulCid);
        if(NAS_ESM_SUCCESS == ulRslt)
        {
            return NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_EQUAL_CID;
        }
        else
        {
            return NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND;
        }
    }

    for(ulCnt = 0; ulCnt < pstEsmNwMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        ucPacketFilter = pstEsmNwMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId;

        /* 根据承载号和当前PF号来查找CID */
        ulRslt = NAS_ESM_QuerySdfIdByEpsbIdAndPfId( pstEsmNwMsgIE->ucEpsbId,
                                                    ucPacketFilter,
                                                    &ulCid);

        if(NAS_ESM_SUCCESS == ulRslt)
        {
            ulFindNum++;
            if(NAS_ESM_ILL_CID == ulLastCid)
            {
                /* 保存当前找到的CID */
                ulLastCid = ulCid;
                *pulCid = ulCid;
            }
            else
            {
                /* 如果前后两次找到的CID不同,则设置enIsCidEqual为PS_FALSE */
                if(ulLastCid != ulCid)
                {
                    enIsCidEqual = PS_FALSE;
                }
            }
        }
    }

    return NAS_ESM_GetQuerySdfIdResult( ulFindNum,
                                        pstEsmNwMsgIE->stTadInfo.ucSdfPfNum,
                                        enIsCidEqual);

}
/*****************************************************************************
 Function Name   : NAS_ESM_GetLinkCidByActiveCid
 Description     : 通过专有承载的Cid,找到这个专有承载的关联
                   缺省承载对应的Cid.
 Input           : ulCid -- Cid号
 Output          : None
 Return          : 找到的缺省承载的Cid

 History         :
    1.liuwenyu 00143951      2010-8-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_GetLinkCidByActiveCid
(
    VOS_UINT32                          ulCid
)

{
    VOS_UINT32                          ulEpsbId         = NAS_ESM_NULL;
    VOS_UINT32                          ulLinkCid        = NAS_ESM_ILL_CID;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    /* 找Cid对应的承载的EpsbId */
    if (NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        return NAS_ESM_ILL_CID;
    }

    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(ulEpsbId)))
    {
        return NAS_ESM_ILL_CID;
    }

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* 查找关联承载对应的Cid*/
    if (NAS_ESM_FAILURE == NAS_ESM_QueryEpsbCntxtTblByEpsbId(pstEpsbCntxtInfo->ulLinkedEpsbId,
                                                             &ulLinkCid))
    {
        return NAS_ESM_ILL_CID;
    }

    return ulLinkCid;
}



/*****************************************************************************
 Function Name  : NAS_ESM_GetStateTblIndexByCid
 Discription    : 根据CID，分配一个StateInfoTbl表节点;
 Input          : VOS_UINT32        ulCidRecv
 Output         : VOS_UINT32        *ulStateId
 Return         : VOS_UINT32(如果没有查到返回SM_FAILURE,否则返回SM_SUCCESS)
 History:
      1.祝义强      2009-02-5  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_GetStateTblIndexByCid(VOS_UINT32 ulCidRecv,VOS_UINT32 *ulStateId)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStatTblnfo   = VOS_NULL_PTR;

    /*搜索 StateInfoTbl*/
    for(ulCnt = 0; ulCnt < NAS_ESM_MAX_STATETBL_NUM; ulCnt++)
    {
        pstStatTblnfo = NAS_ESM_GetStateTblAddr(ulCnt);

        /*如果CID已经在STATE表中*/
        if(ulCidRecv == pstStatTblnfo->ulCid)
        {
            return NAS_ESM_FAILURE;
        }
    }

    /*分配到ulStateId*/
    for(ulCnt = 0; ulCnt < NAS_ESM_MAX_STATETBL_NUM; ulCnt++)
    {
        pstStatTblnfo = NAS_ESM_GetStateTblAddr(ulCnt);

        /*如果STATE_INFO_TBL表中对应CID为无效值*/
        if(NAS_ESM_ILL_CID == pstStatTblnfo->ulCid)
        {
            /*ulStateId分配成功*/
            (*ulStateId) = ulCnt;
            pstStatTblnfo->ulCid = ulCidRecv;

            NAS_ESM_NORM_LOG("*********************");
            NAS_ESM_LOG1("GET StateTblIndex : ", *ulStateId);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_GetStateTblIndexByCid_ENUM, 1, *ulStateId);
            NAS_ESM_NORM_LOG("*********************");

            return NAS_ESM_SUCCESS;
        }
    }

    /*如果找不到空闲的ulStateId*/
    return NAS_ESM_FAILURE;

}

/*****************************************************************************
 Function Name  : NAS_ESM_QueryStateTblIndexByCid
 Discription    : 根据CID，查询StateInfoTbl表;
 Input          : VOS_UINT32 ulCidRecv
 Output         : VOS_UINT32         *pulEpsId
 Return         : VOS_UINT32(如果没有查到返回SM_FAILURE,否则返回SM_SUCCESS)

 History:
      1.祝义强      2009-02-5  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryStateTblIndexByCid(VOS_UINT32 ulCidRecv,VOS_UINT32 *ulStateId)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStatTblnfo   = VOS_NULL_PTR;

    /*搜索 StateInfoTbl*/
    for(ulCnt = 0; ulCnt < NAS_ESM_MAX_STATETBL_NUM; ulCnt++)
    {
        pstStatTblnfo = NAS_ESM_GetStateTblAddr(ulCnt);

        /*如果CID已经在STATE_INFO_TBL表中*/
        if(ulCidRecv == pstStatTblnfo->ulCid)
        {
            /*返回StateInfoTbl的索引*/
            (*ulStateId) = ulCnt;
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;

}

/*****************************************************************************
 Function Name  : NAS_ESM_QueryStateTblIndexByPti
 Discription    : 根据ucPti，分配一个StateId;
 Input          : VOS_UINT8         ucPti
 Output         : VOS_UINT32         *pulEpsId
 Return         : VOS_UINT32(如果没有查到返回SM_FAILURE,否则返回SM_SUCCESS)

 History:
      1.祝义强      2009-02-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryStateTblIndexByPti(VOS_UINT8 ucPti,VOS_UINT32 *ulStateId)
{
    VOS_UINT8                           ucCurrPti           = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStatTblnfo       = VOS_NULL_PTR;

    /*搜索 StateInfoTbl*/
    for(ulCnt = 0; ulCnt < NAS_ESM_MAX_STATETBL_NUM; ulCnt++)
    {
        pstStatTblnfo = NAS_ESM_GetStateTblAddr(ulCnt);
        ucCurrPti = pstStatTblnfo->stNwMsgRecord.ucPti;

        /*如果在STATE表中找到对应PTI值*/
        if(ucPti == ucCurrPti)
        {
            /*返回对应State表的索引*/
            (*ulStateId) = ulCnt;
            return NAS_ESM_SUCCESS;
        }
    }

    /*没有对应的节点*/
    return NAS_ESM_FAILURE;

}

/*****************************************************************************
 Function Name  : NAS_ESM_QueryStateTblIndexByEpsbId
 Discription    : 根据承载号EpsbId,查询StateTbl表，返回StateTbl表的索引
 Input          : VOS_UINT32        ulEpsbId
 Output         : VOS_UINT32       *ulStateId
 Return         : VOS_UINT32(如果没有查到返回SM_FAILURE,否则返回SM_SUCCESS)

 History:
      1.祝义强      2009-02-10  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryStateTblIndexByEpsbId(VOS_UINT32 ulEpsbId,VOS_UINT32 *ulStateId)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStatTblnfo   = VOS_NULL_PTR;

    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_QueryStateTblIndexByEpsbId:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_QueryStateTblIndexByEpsbId_ENUM, LNAS_ENTRY);
        return NAS_ESM_FAILURE;
    }

    for(ulCnt = 0; ulCnt < NAS_ESM_MAX_STATETBL_NUM; ulCnt++)
    {
        pstStatTblnfo = NAS_ESM_GetStateTblAddr(ulCnt);

        /*如果在STATE表中有对应EpsbId*/
        if(ulEpsbId == pstStatTblnfo->ulEpsbId)
        {
            /*返回StateTbl索引*/
            (*ulStateId) = ulCnt;

            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_GetBuffItemAddr
 Description     : 获取缓存记录地址
 Input           : ulIndex------------------------定时器索引号
 Output          : None
 Return          : VOS_VOID*

 History         :
    1.lihong00150010      2010-4-23  Draft Enact

*****************************************************************************/
VOS_VOID* NAS_ESM_GetBuffItemAddr
(
    NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8   enEsmBuffType,
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();
    VOS_VOID                           *pBuffItem           = VOS_NULL_PTR;

    if (enEsmBuffType == NAS_ESM_BUFF_ITEM_TYPE_PTI)
    {
        pBuffItem = pstEsmBuffManInfo->paPtiBuffer[ulIndex];
    }
    else
    {
        pBuffItem = pstEsmBuffManInfo->paAttBuffer[ulIndex];
    }

    return pBuffItem;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetPtiBuffItemTimer
 Description     : 获取ESM缓存记录关联定时器
 Input           : ulIndex------------------------定时器索引号
 Output          : None
 Return          : NAS_ESM_TIMER_STRU*

 History         :
    1.lihong00150010      2010-1-29     Draft Enact
    2.lihong00150010      2010-04-23    Modify

*****************************************************************************/
NAS_ESM_TIMER_STRU* NAS_ESM_GetPtiBuffItemTimer
(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_PTI_BUFF_ITEM_STRU         *pstEsmPtiBuffItem = VOS_NULL_PTR;

    /* 获取缓存记录 */
    pstEsmPtiBuffItem = (NAS_ESM_PTI_BUFF_ITEM_STRU*)
                                NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulIndex);
    if (pstEsmPtiBuffItem == VOS_NULL_PTR)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_GetPtiBuffItemTimer:WARN:Get buffer item failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_GetPtiBuffItemTimer_ENUM, LNAS_NULL_PTR);
        return VOS_NULL_PTR;
    }

    return &pstEsmPtiBuffItem->stTimerInfo;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetTimerLen
 Description     : 获取定时器时长
 Input           : enTimerType------------------定时器类型
                   ulIndex----------------------定时器索引号
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-1-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_GetTimerLen
(
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                  ulTimerLen   = NAS_ESM_NULL;

    /*根据定时器不同类型，定时器时长不同*/
    switch( enTimerType )
    {
        case TI_NAS_ESM_T3482:
            ulTimerLen = TI_NAS_ESM_T3482_TIMER_LEN;
            break;
        case TI_NAS_ESM_T3492:
            ulTimerLen = TI_NAS_ESM_T3492_TIMER_LEN;
            break;
        case TI_NAS_ESM_T3480:
            ulTimerLen = TI_NAS_ESM_T3480_TIMER_LEN;
            break;
        case TI_NAS_ESM_T3481:
            ulTimerLen = TI_NAS_ESM_T3481_TIMER_LEN;
            break;
        case TI_NAS_ESM_WAIT_APP_CNF:
            ulTimerLen = TI_NAS_ESM_WAIT_APP_CNF_TIMER_LEN;
            break;
        case TI_NAS_ESM_WAIT_PTI_INVALID:
            ulTimerLen = TI_NAS_ESM_WAIT_PTI_INVALID_TIMER_LEN;
            break;
        case TI_NAS_ESM_ATTACH_BEARER_REEST:
            ulTimerLen = NAS_ESM_GetAttachBearerReestTimerLen();
            break;
        case TI_NAS_ESM_REL_NON_EMC_BEARER:
            ulTimerLen = TI_NAS_ESM_REL_NON_EMC_BEARER_TIMER_LEN;
            break;
        case TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF:
            ulTimerLen = TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF_TIMER_LEN;
            break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC:
            ulTimerLen = (5 * TI_NAS_ESM_T3485_TIMER_LEN);

            break;
        #endif

        default :
            break;
    }

    return ulTimerLen;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetTimer
 Description     : 获取定时器
 Input           : enTimerType------------------定时器类型
                   ulIndex----------------------定时器索引号
 Output          : None
 Return          : NAS_ESM_TIMER_STRU*

 History         :
    1.lihong00150010      2010-1-29  Draft Enact

*****************************************************************************/
NAS_ESM_TIMER_STRU*  NAS_ESM_GetTimer
(
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    NAS_ESM_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;

    /*根据定时器不同类型，获取定时器*/
    switch( enTimerType )
    {
        case TI_NAS_ESM_T3482:
        case TI_NAS_ESM_T3492:
        case TI_NAS_ESM_T3480:
        case TI_NAS_ESM_T3481:
        case TI_NAS_ESM_WAIT_APP_CNF:
            pstTimerInfo = NAS_ESM_GetStateTblTimer(ulIndex);
            break;
        case TI_NAS_ESM_WAIT_PTI_INVALID:
            pstTimerInfo = NAS_ESM_GetPtiBuffItemTimer(ulIndex);
            break;
        case TI_NAS_ESM_ATTACH_BEARER_REEST:
            pstTimerInfo = &(NAS_ESM_Entity()->stAttachBearerReestInfo.stTimerInfo);
            break;
        case TI_NAS_ESM_REL_NON_EMC_BEARER:
            pstTimerInfo = &(NAS_ESM_Entity()->stDeferRelNonEmcTimerInfo);
            break;

        case TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF:
            pstTimerInfo = &(NAS_ESM_Entity()->stBackOffWaitUsimTimerInfo);
            break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC:
            pstTimerInfo = &(NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex)->stTimerInfo);
            break;
        #endif

        default :
            break;
    }

    return pstTimerInfo;
}

/*****************************************************************************
 Function Name   : NAS_ESM_PrintTimeStartInfo
 Description     : 打印定时器启动信息
 Input           : enTimerType------------------定时器类型
                   ulIndex----------------------定时器索引号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_PrintTimeStartInfo
(
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    /*根据定时器不同类型，打印相应信息*/
    switch( enTimerType )
    {
        case TI_NAS_ESM_T3482:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_T3482", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 1, ulIndex);
            break;
        case TI_NAS_ESM_T3492:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_T3492", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 2, ulIndex);
            break;
        case TI_NAS_ESM_T3480:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_T3480", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 3, ulIndex);
            break;
        case TI_NAS_ESM_T3481:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_T3481", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 4, ulIndex);
            break;
        case TI_NAS_ESM_WAIT_APP_CNF:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_WAIT_APP_CNF", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 5, ulIndex);
            break;
        case TI_NAS_ESM_WAIT_PTI_INVALID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_WAIT_PTI_INVALID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 6, ulIndex);
            break;
        case TI_NAS_ESM_ATTACH_BEARER_REEST:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_ATTACH_BEARER_REEST", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 7, ulIndex);
            break;
        case TI_NAS_ESM_REL_NON_EMC_BEARER:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStart(ulIndex): TI_NAS_ESM_REL_NON_EMC_BEARER", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 8, ulIndex);
            break;
        case TI_NAS_ESM_BACKOFF_IGNORE_FORBID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_BACKOFF_IGNORE_FORBID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 9, ulIndex);
            break;
        case TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 10, ulIndex);
            break;
        case TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStartInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStartInfo_ENUM, 11, ulIndex);
            break;

        default :
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_PrintTimeStopInfo
 Description     : 打印定时器关闭信息
 Input           : enTimerType------------------定时器类型
                   ulIndex----------------------定时器索引号
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_PrintTimeStopInfo
(
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    /*根据定时器不同类型，打印相应信息*/
    switch(enTimerType)
    {
        case TI_NAS_ESM_T3482:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_T3482", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 1, ulIndex);
            break;
        case TI_NAS_ESM_T3492:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_T3492", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 2, ulIndex);
            break;
        case TI_NAS_ESM_T3480:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_T3480", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 3, ulIndex);
            break;
        case TI_NAS_ESM_T3481:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_T3481", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 4, ulIndex);
            break;
        case TI_NAS_ESM_WAIT_APP_CNF:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_WAIT_APP_CNF", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 5, ulIndex);
            break;
        case TI_NAS_ESM_WAIT_PTI_INVALID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_WAIT_PTI_INVALID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 6, ulIndex);
            break;
        case TI_NAS_ESM_ATTACH_BEARER_REEST:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_ATTACH_BEARER_REEST", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 7, ulIndex);
            break;
        case TI_NAS_ESM_REL_NON_EMC_BEARER:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_REL_NON_EMC_BEARER", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 8, ulIndex);
            break;
        case TI_NAS_ESM_BACKOFF_IGNORE_FORBID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_BACKOFF_IGNORE_FORBID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 9, ulIndex);
            break;
        case TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 10, ulIndex);
            break;
        case TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 11, ulIndex);
            break;
        case TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF:
            NAS_ESM_LOG1("NAS_ESM_PrintTimeStopInfo:NORM:SM TimerStop(ulIndex): TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF", ulIndex);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintTimeStopInfo_ENUM, 12, ulIndex);
        default :
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsTimerNameValid
 Description     : 判断定时器名是否合法
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-1-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    switch(enTimerType)
    {
        case TI_NAS_ESM_T3482:
        case TI_NAS_ESM_T3492:
        case TI_NAS_ESM_T3480:
        case TI_NAS_ESM_T3481:
        case TI_NAS_ESM_WAIT_APP_CNF:
        {
            if (ulIndex < NAS_ESM_MAX_STATETBL_NUM)
            {
                return PS_TRUE;
            }

            break;
        }
        case TI_NAS_ESM_WAIT_PTI_INVALID:
        {
            if (ulIndex < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM)
            {
                return PS_TRUE;
            }

            break;
        }
        case TI_NAS_ESM_ATTACH_BEARER_REEST:
        {
            return PS_TRUE;
        }
        case TI_NAS_ESM_REL_NON_EMC_BEARER:
        {
            return PS_TRUE;
        }

        case TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF:
        case TI_NAS_ESM_BACKOFF_IGNORE_FORBID:
        case TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID:
        case TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID:
        {
            return PS_TRUE;
        }

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC:

            return PS_TRUE;
        #endif

        default:
            break;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_TimerStart
 Discription    : 启动某一承载的某种类型的定时器
 Input          : VOS_UINT32  ulIndex
                  NAS_ESM_TIMER_PARA_ENUM_UINT8   enTimerType
 Output         : VOS_VOID
 Return         : None
 History:
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong 00150010    2010-01-29  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_TimerStart
(
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                  ulTimerLen   = NAS_ESM_NULL;
    NAS_ESM_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;

    /*对ulIndex合法性判断*/
    if (PS_FALSE == NAS_ESM_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_TimerStart: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_TimerStart_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = NAS_ESM_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_TimerStart:ERROR: Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_TimerStart_ENUM, LNAS_FAIL);
        return;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_TimerStart:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_TimerStart_ENUM, ESM_CALL_API_FAIL, 1);
            return;
        }

        /*打印异常信息*/
        NAS_ESM_LOG2("(TimerType) Timer not close!",pstTimerInfo->enPara, ulIndex);
        TLPS_PRINT2LAYER_INFO2(NAS_ESM_TimerStart_ENUM, 1, pstTimerInfo->enPara, ulIndex);
    }

    /*根据定时器不同类型，定时器信息不同*/
    ulTimerLen = NAS_ESM_GetTimerLen(enTimerType);
    if (ulTimerLen == NAS_ESM_NULL)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_TimerStart:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_TimerStart_ENUM, LNAS_ERROR);
        return;
    }

    /*设定定时器NAME,enTimerType设定定时器Para，打开失败则报警返回*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTimer),PS_PID_ESM,\
                                ulTimerLen,ulIndex,\
                                (VOS_UINT32)enTimerType,VOS_RELTIMER_NOLOOP))
    {
          /*打印异常信息*/
          NAS_ESM_WARN_LOG("NAS_ESM_TimerStart:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_WARNING1(NAS_ESM_TimerStart_ENUM, ESM_CALL_API_FAIL, 2);
          return;
    }

    /*更新定时器开启信息和定时器类别*/
    pstTimerInfo->enPara     = enTimerType;


    /*钩出当前的定时器信息 */
    NAS_ESM_SndOmEsmTimerStatus(NAS_ESM_TIMER_RUNNING, enTimerType, ulTimerLen);


    /* 打印定时器启动信息 */
    NAS_ESM_PrintTimeStartInfo(ulIndex, enTimerType);
}

/*****************************************************************************
 Function Name  : NAS_ESM_TimerStop
 Discription    : 停止某一承载定时器
 Input          : VOS_UINT32  ulEpsbId
 Output         : VOS_VOID
 Return         : None
 History:
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong 00150010    2010-01-29  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_TimerStop
(
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    NAS_ESM_TIMER_STRU        *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                 ulTimerRemainLen;

    /*对ulIndex合法性判断*/
    if (PS_FALSE == NAS_ESM_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_TimerStop: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_TimerStop_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = NAS_ESM_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_TimerStop:ERROR:Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_TimerStop_ENUM, LNAS_FAIL);
        return;
    }

    /*定时器处于打开状态，则关闭，否则，忽略*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /* 获取当前定时器的剩余时间 */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerInfo->hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_TimerStop:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_TimerStop_ENUM, ESM_CALL_API_FAIL);
            return;
        }

        /*更新定时器超时次数*/
        pstTimerInfo->ucExpireTimes = 0;


        /*钩出当前的定时器信息 */
        NAS_ESM_SndOmEsmTimerStatus(NAS_ESM_TIMER_STOPED, enTimerType, ulTimerRemainLen);

        /* 打印定时器关闭信息 */
        NAS_ESM_PrintTimeStopInfo(ulIndex, enTimerType);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetTimerMaxExpTimes
 Description     : 获取指定定时器允许的最大超时次数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421  2011-2-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_GetTimerMaxExpNum(
                                        NAS_ESM_TIMER_PARA_ENUM_UINT8 enTimerType )
{
    VOS_UINT32                          ulTimerMaxExpNum = 0;

    switch( enTimerType )
    {
        case TI_NAS_ESM_T3482:
             ulTimerMaxExpNum = TI_NAS_ESM_T3482_TIMER_MAX_EXP_NUM;
             break;

        case TI_NAS_ESM_T3492:
             ulTimerMaxExpNum = TI_NAS_ESM_T3492_TIMER_MAX_EXP_NUM;
             break;

        case TI_NAS_ESM_T3480:
             ulTimerMaxExpNum = TI_NAS_ESM_T3480_TIMER_MAX_EXP_NUM;
             break;

        case TI_NAS_ESM_T3481:
             ulTimerMaxExpNum = TI_NAS_ESM_T3481_TIMER_MAX_EXP_NUM;
             break;

        default :
            NAS_ESM_WARN_LOG("NAS_ESM_GetTimerMaxExpNum:enTimerType Invalid.");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_GetTimerMaxExpNum_ENUM, LNAS_PARAM_INVALID);
            break;
    }

    return ulTimerMaxExpNum;
}


/*****************************************************************************
 Function Name   : NAS_ESM_QueryOverduePtiBuffItem
 Description     : 查找过期的PTI缓存记录
 Input           : ucPti----------------------PTI
                   ucEpsbId-------------------承载号
 Output          : pulIndex-------------------缓存记录索引号
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-2-2      Draft Enact
    2.lihong00150010      2010-04-23    Modify

*****************************************************************************/
VOS_UINT32  NAS_ESM_QueryOverduePtiBuffItem
(
    VOS_UINT8                           ucPti,
    VOS_UINT8                           ucEpsbId,
    VOS_UINT32                         *pulIndex
)
{
    NAS_ESM_PTI_BUFF_ITEM_STRU         *pstPtiBuffItem  = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM; ulCnt++)
    {
        /* 获取缓存记录 */
        pstPtiBuffItem = (NAS_ESM_PTI_BUFF_ITEM_STRU*)
                                NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulCnt);

        if (pstPtiBuffItem == VOS_NULL_PTR)
        {
            continue;
        }

        /* 由于网侧不能对同一承载同时进行两种操作，因此假设收到的网侧消息携带的
           承载号为ucEpsbId，PTI为ucPti，则PTI缓存记录中承载号与ucEpsbId相同，且
           PTI小于ucPti，即可以认为此PTI缓存记录为过期无效的PTI缓存记录*/
        if ((pstPtiBuffItem->ucPti < ucPti)
            && (pstPtiBuffItem->ucEpsbId == ucEpsbId))
        {
            /* 找到相应的PTI缓存记录，返回索引号 */
            *pulIndex = ulCnt;

            break;
        }
    }

    if (ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM)
    {
        return NAS_ESM_SUCCESS;
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SavePtiBuffItem
 Description     : 缓存PTI和回复消息
 Input           : ucPti----------------------PTI
                   ucEpsbId-------------------承载号
                   ulLength-------------------回复消息长度
                   pucSendMsg-----------------回复消息首地址
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-1-29     Draft Enact
    2.lihong00150010      2010-04-23    Modify

*****************************************************************************/
VOS_UINT32  NAS_ESM_SavePtiBuffItem
(
    VOS_UINT8                           ucPti,
    VOS_UINT8                           ucEpsbId,
    VOS_UINT32                          ulLength,
    const VOS_UINT8                    *pucSendMsg
)
{
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();
    NAS_ESM_PTI_BUFF_ITEM_STRU         *pstEsmPtiBuffItem   = VOS_NULL_PTR;
    VOS_UINT32                          ulBuffItemLen       = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_SavePtiBuffItem is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SavePtiBuffItem_ENUM, LNAS_ENTRY);

    /* 清除过期的缓存记录 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryOverduePtiBuffItem(ucPti, ucEpsbId, &ulIndex))
    {
        NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulIndex);
    }

    /* 判断是否已到达系统能够存储缓存记录的极限 */
    if (pstEsmBuffManInfo->ucPtiBuffItemNum >= NAS_ESM_MAX_PTI_BUFF_ITEM_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SavePtiBuffItem:WARN:PTI Buffer is full!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SavePtiBuffItem_ENUM, LNAS_FAIL, 1);
        return NAS_ESM_FAILURE;
    }

    /* 计算缓存记录长度 */
    ulBuffItemLen = (sizeof(NAS_ESM_PTI_BUFF_ITEM_STRU) - 4) + ulLength;

    /* 获取缓存记录空间 */
    pstEsmPtiBuffItem = (NAS_ESM_PTI_BUFF_ITEM_STRU *)NAS_COMM_AllocBuffItem(NAS_COMM_BUFF_TYPE_ESM,
                                                                             ulBuffItemLen);
    if (VOS_NULL_PTR == pstEsmPtiBuffItem)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SavePtiBuffItem:WARN:NAS_COMM_AllocBuffItem is failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SavePtiBuffItem_ENUM, LNAS_FAIL, 2);
        return NAS_ESM_FAILURE;
    }

    /* 查找用于存储缓存记录首地址的指针 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM; ulCnt++)
    {
        if (pstEsmBuffManInfo->paPtiBuffer[ulCnt] == VOS_NULL_PTR)
        {
            break;
        }
    }

    if (ulCnt >= NAS_ESM_MAX_PTI_BUFF_ITEM_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SavePtiBuffItem:Get the valuable which stores buffer item addr failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_SavePtiBuffItem_ENUM, LNAS_FAIL, 3);
        return NAS_ESM_FAILURE;
    }

    /* 记录存储缓存记录的首地址 */
    pstEsmBuffManInfo->paPtiBuffer[ulCnt] = (VOS_VOID *)pstEsmPtiBuffItem;

    /* 缓存PTI,EPSBID,OPID信息 */
    pstEsmPtiBuffItem->ucPti = ucPti;
    pstEsmPtiBuffItem->ucEpsbId = ucEpsbId;
    pstEsmPtiBuffItem->ulOpId = NAS_ESM_ILLEGAL_OPID;

    /* 缓存回复消息 */
    pstEsmPtiBuffItem->stEsmMsg.ulEsmMsgSize = ulLength;
    if (ulLength != NAS_ESM_NULL)
    {
        NAS_ESM_MEM_CPY_S(  pstEsmPtiBuffItem->stEsmMsg.aucEsmMsg,
                            ulLength,
                            pucSendMsg,
                            ulLength);
    }

    /* 启动定时器TI_NAS_ESM_WAIT_PTI_INVALID */
    NAS_ESM_TimerStart(ulCnt, TI_NAS_ESM_WAIT_PTI_INVALID);

    /* 增加缓存记录个数 */
    pstEsmBuffManInfo->ucPtiBuffItemNum++;

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_QueryPtiBuffItemByEpsbId
 Description     : 通过承载号查找ESM缓存记录
 Input           : ucEpsbId-------------------承载号
 Output          : pulIndex-------------------缓存记录索引号
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-2-2      Draft Enact
    2.lihong00150010      2010-04-23    Modify

*****************************************************************************/
VOS_UINT32  NAS_ESM_QueryPtiBuffItemByEpsbId
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT32                         *pulIndex
)
{
    NAS_ESM_PTI_BUFF_ITEM_STRU         *pstPtiBuffItem  = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM; ulCnt++)
    {
        /* 获取缓存记录 */
        pstPtiBuffItem = (NAS_ESM_PTI_BUFF_ITEM_STRU*)
                                NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulCnt);

        if (pstPtiBuffItem == VOS_NULL_PTR)
        {
            continue;
        }

        if (ucEpsbId == pstPtiBuffItem->ucEpsbId)
        {
            /* 找到相应的PTI缓存记录，返回索引号 */
            *pulIndex = ulCnt;

            break;
        }
    }

    if (ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM)
    {
        return NAS_ESM_SUCCESS;
    }

    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_QueryPtiBuffItemByPti
 Description     : 通过PTI查找ESM缓存记录
 Input           : ucPti----------------------PTI
 Output          : pulIndex-------------------缓存记录索引号
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-2-2      Draft Enact
    2.lihong00150010      2010-04-23    Modify

*****************************************************************************/
VOS_UINT32  NAS_ESM_QueryPtiBuffItemByPti
(
    VOS_UINT8                           ucPti,
    VOS_UINT32                         *pulIndex
)
{
    NAS_ESM_PTI_BUFF_ITEM_STRU         *pstPtiBuffItem      = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM; ulCnt++)
    {
        /* 获取缓存记录 */
        pstPtiBuffItem = (NAS_ESM_PTI_BUFF_ITEM_STRU*)
                                NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulCnt);

        if (pstPtiBuffItem == VOS_NULL_PTR)
        {
            continue;
        }

        if (ucPti == pstPtiBuffItem->ucPti)
        {
            /* 找到相应的PTI缓存记录，返回索引号 */
            *pulIndex = ulCnt;

            break;
        }
    }

    if (ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM)
    {
        return NAS_ESM_SUCCESS;
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ClearEsmBuff
 Description     : 清楚ESM缓存
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ClearEsmBuff( VOS_VOID )
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();

    /* 释放ATTACHING类型的缓存记录 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM; ulCnt++)
    {
        if (pstEsmBuffManInfo->paAttBuffer[ulCnt] != VOS_NULL_PTR)
        {
            NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulCnt);
        }
    }

    /* 释放PTI类型的缓存记录 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_PTI_BUFF_ITEM_NUM; ulCnt++)
    {
        if (pstEsmBuffManInfo->paPtiBuffer[ulCnt] != VOS_NULL_PTR)
        {
            NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulCnt);
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ClearEsmBuffItem
 Description     : 清楚ESM缓存记录
 Input           : ulIndex-------------------缓存记录索引号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-2  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ClearEsmBuffItem
(
    NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8   enEsmBuffType,
    VOS_UINT32                          ulIndex
)
{
    VOS_VOID                           *pEsmBuffItemAddr    = VOS_NULL_PTR;
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();
    VOS_VOID                          **ppBuffItem          = VOS_NULL_PTR;
    VOS_UINT8                          *pucBuffItemNum      = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_ClearEsmBuffItem is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearEsmBuffItem_ENUM, LNAS_ENTRY);

    /* 获取缓存记录 */
    if (enEsmBuffType == NAS_ESM_BUFF_ITEM_TYPE_PTI)
    {
        pEsmBuffItemAddr = NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulIndex);

        /* 停止定时器TI_NAS_ESM_WAIT_PTI_INVALID */
        NAS_ESM_TimerStop(ulIndex, TI_NAS_ESM_WAIT_PTI_INVALID);

        ppBuffItem      = &pstEsmBuffManInfo->paPtiBuffer[ulIndex];
        pucBuffItemNum  = &pstEsmBuffManInfo->ucPtiBuffItemNum;
    }
    else
    {
        pEsmBuffItemAddr = NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_ATTACHING, ulIndex);

        ppBuffItem      = &pstEsmBuffManInfo->paAttBuffer[ulIndex];
        pucBuffItemNum  = &pstEsmBuffManInfo->ucAttBuffItemNum;
    }

    if (pEsmBuffItemAddr == VOS_NULL_PTR)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ClearEsmBuffItem:WARN:Get buffer item failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ClearEsmBuffItem_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /* 清除缓存记录 */
    (VOS_VOID)NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_ESM, pEsmBuffItemAddr);

    *ppBuffItem = VOS_NULL_PTR;

    /* 将缓存记录数减1 */
    *pucBuffItemNum = *pucBuffItemNum - 1;
}

/*****************************************************************************
 Function Name  : NAS_ESM_ClearEsmBearerResource
 Discription    : 释放某一承载相关资源
 Input          : VOS_UINT32  ulEpsbId
 Output         : VOS_VOID
 Return         : None
 History:
      1.丁丽 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ClearEsmBearerResource( VOS_UINT32  ulEpsbId )
{
    VOS_UINT32                          ulTmpBitCid         = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo         = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;

    /*打印信息*/
    NAS_ESM_LOG1("NAS_ESM_ClearEsmBearerResource:NORM:EpsbId = ",ulEpsbId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ClearEsmBearerResource_ENUM, LNAS_ENTRY, ulEpsbId);

    /* 若不是有效承载号，则返回未激活态 */
    if ((NAS_ESM_MIN_EPSB_ID > ulEpsbId)
        || (NAS_ESM_MAX_EPSB_ID < ulEpsbId))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ClearEsmBearerResource:Unsigned or Reserved Eps Bearer ID!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearEsmBearerResource_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /* 清除缓存记录中与此承载相关的记录 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryPtiBuffItemByEpsbId((VOS_UINT8)ulEpsbId,
                                                             &ulIndex))
    {
        NAS_ESM_ClearEsmBuffItem(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulIndex);
    }
    /*释放与承载相关的动态表资源 */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId, &ulStateTblIndex))
    {
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
    }

    /*获取承载信息地址*/
    pstEpsbInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*根据CID，释放相应的SDF信息*/
    if(NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpCId)
    {
        ulTmpBitCid = pstEpsbInfo->ulBitCId;

        for( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
        {
            /*遍历已取出的CID记录*/
            if(NAS_ESM_OP_TRUE ==((ulTmpBitCid >> ulCnt)&NAS_ESM_OP_TRUE))
            {
                /* 清空SDF上下文 */
                pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);
                NAS_ESM_MEM_SET_S(  pstSdfCntxtInfo,
                                    sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                                    0,
                                    sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

                /* 如果CID在21~31之间，则删除静态信息 */
                if ((ulCnt >= NAS_ESM_MIN_NW_CONTROL_CID)
                   && (ulCnt <= NAS_ESM_MAX_CID))
                {
                    NAS_ESM_ClearSdfPara(ulCnt);
                }
            }
        }
    }

    /*如果支持双APN，并且被去激活的承载是注册承载，则清除注册承载记录*/
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        if ((ulEpsbId == NAS_ESM_GetAttachBearerId()) &&
            (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbInfo->enBearerCntxtType)))
        {
            NAS_ESM_SetAttachBearerId(NAS_ESM_UNASSIGNED_EPSB_ID);
        }
    }

    /*初始化相关信息*/
    NAS_ESM_InitEpsbCntxtInfo((VOS_UINT32)ulEpsbId);
}

/*****************************************************************************
 Function Name   : NAS_ESM_RelStateTblResource
 Description     : 根据状态表index释放状态表资源
 Input           : VOS_UINT32  ulStateTblIndex
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-11  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RelStateTblResource(VOS_UINT32  ulStateTblIndex )
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG1("NAS_ESM_RelStateTblResource", ulStateTblIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_RelStateTblResource_ENUM, LNAS_ENTRY, ulStateTblIndex);

    /*如果ulStateTblIndex无效*/
    if(ulStateTblIndex >= NAS_ESM_MAX_STATETBL_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RelStateTblResource:WARN: StateTblIndex illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RelStateTblResource_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*停止定时器*/
    NAS_ESM_TimerStop(ulStateTblIndex, pstStateAddr->stTimerInfo.enPara);

    /* 若存在缓存消息，则先释放缓存消息空间 */
    if (pstStateAddr->pstDecodedNwMsg != VOS_NULL_PTR)
    {
        NAS_ESM_MEM_FREE(pstStateAddr->pstDecodedNwMsg);
    }

    /* 如果紧急承载建立被取消，则通知EMM清除相关ESM流程用到的资源，
       FIXME: 此函数有可能在紧急PDN连接还未下发到EMM之前就被呼叫到，
              如编码失败，因此会导致多发一次notify
    */
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg(pstStateAddr->ulCid, PS_TRUE);
    }

    /*清空所有内容*/
    NAS_ESM_MEM_SET_S(  pstStateAddr,
                        sizeof(NAS_ESM_STATE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_STATE_INFO_STRU));

    /*置初始值*/
    pstStateAddr->bitOpNwMsgRecord      = NAS_ESM_OP_FALSE;
    pstStateAddr->bitOpAppMsgRecord     = NAS_ESM_OP_FALSE;
    pstStateAddr->ulCid                 = NAS_ESM_ILL_CID;
    pstStateAddr->ulEpsbId              = NAS_ESM_UNASSIGNED_EPSB_ID;
    pstStateAddr->ulLinkedEpsbId        = NAS_ESM_UNASSIGNED_EPSB_ID;
    pstStateAddr->enBearerCntxtState    = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enProcTransTState     = NAS_ESM_BEARER_PROC_TRANS_STATE_INACTIVE;
    pstStateAddr->pstDecodedNwMsg       = VOS_NULL_PTR;
    pstStateAddr->ucIsWaitForUserAnswer = PS_FALSE;
    pstStateAddr->enPdnReqType          = NAS_ESM_PDN_REQ_TYPE_INITIAL;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_STATUS_NULL;

    /*通过遍历动态表以及本条承载状态，这里判断如果动态表中至少存在一个是sending和succ状态，
      那么不发送end session， 假设既没有sending状态以及succ状态的承载，不外乎有两种情况，
      1、当前承载都是FAIL的。 2、当前承载FAIL和NULL兼而有之，对于这两种情况，表明当前没有承载
      正在使用射频资源。
    */
    NAS_ESM_INFO_LOG1("NAS_ESM_RelStateTblResource: isRunning:", NAS_ESM_IsExistAllFailStateTable());
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_RelStateTblResource_ENUM, 1, NAS_ESM_IsExistAllFailStateTable());
    if( ESM_BEARER_STATUS_BESIDE_RUNING == NAS_ESM_IsExistAllFailStateTable())
    {
        NAS_ESM_SendEndSessionNotify();
    }
    #endif
}

/*****************************************************************************
 Function Name   : NAS_ESM_QueryNWPacketFilterID
 Description     : 根据App设置的packetfilterID，查找网络侧分配的packetfilterID
 Input           : ucPacketFilterID   -- APP设置的packetfilterID
                   ulCID              -- 要查找的CID
 Output          : ucNWPacketFilterID -- 网络分配的packetfilterID
 Return          : NAS_ESM_SUCCESS    -- 找到了对应的网络packetfilterID
                   NAS_ESM_FAILURE    -- 没找到了对应的网络packetfilterID
 History         :
    1.liuwenyu00143951      2009-10-23  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryNWPacketFilterID
(
    VOS_UINT8                           ucPacketFilterID,
    VOS_UINT32                          ulCID,
    VOS_UINT8                          *ucNWPacketFilterID
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU           *pstTmpTFTInfo   = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;

    /* when app set tft, packetfilter id is checked. */
    /* so here,no need to do input check, */

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCID);

    /* search mapped network packetfilter */
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        pstTmpTFTInfo = &pstSdfCntxtInfo->astSdfPfInfo[ulCnt];

        if (ucPacketFilterID == pstTmpTFTInfo->ucPacketFilterId)
        {
            *ucNWPacketFilterID = pstTmpTFTInfo->ucNwPacketFilterId;
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}



/*****************************************************************************
 Function Name   : NAS_ESM_IsTftInfoValid
 Description     : TFT信息的合法性检查
 Input           : None
 Output          : None
 Return          : NAS_ESM_FAILURE -- 信息不合法
                   NAS_ESM_SUCCESS -- 信息合法
 History         :
    1.liuwenyu 00143951      2010-8-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsTftInfoValid
(
    const APP_ESM_TFT_INFO_STRU               *pstAppTftInfo
)
{
    /* 检验TFT方向是否合法 */
    if (pstAppTftInfo->enDirection >= APP_ESM_TRANSFER_DIRECTION_BUTT)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsTftInfoValid:Invalid TFT Direction!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsTftInfoValid_ENUM, LNAS_PARAM_INVALID,1);
        return NAS_ESM_FAILURE;
    }

    /* PFid 的有效性检查*/
    if ((pstAppTftInfo->ucPacketFilterId == NAS_ESM_NULL)
      ||(pstAppTftInfo->ucPacketFilterId > NAS_ESM_MAX_SDF_PF_NUM))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsTftInfoValid:Invalid PacketFilter ID!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsTftInfoValid_ENUM, LNAS_PARAM_INVALID, 2);
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstAppTftInfo->bitOpRemotePortRange)
     && ((pstAppTftInfo->usRmtPortHighLimit < pstAppTftInfo->usRmtPortLowLimit)
        ||(NAS_ESM_OP_TRUE == pstAppTftInfo->bitOpSingleRemotePort)))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsTftInfoValid:Remote port error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsTftInfoValid_ENUM, LNAS_PARAM_INVALID, 3);
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstAppTftInfo->bitOpLocalPortRange)
     && ((pstAppTftInfo->usLcPortHighLimit < pstAppTftInfo->usLcPortLowLimit)
        ||(NAS_ESM_OP_TRUE == pstAppTftInfo->bitOpSingleLocalPort)))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsTftInfoValid:Locate port error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsTftInfoValid_ENUM, LNAS_PARAM_INVALID, 4);
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstAppTftInfo->bitOpFlowLabelType)
     && (pstAppTftInfo->ulFlowLabelType > NAS_ESM_MAX_FLOW_LABEL_TYPE))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsTftInfoValid:Flow Label Type error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsTftInfoValid_ENUM, LNAS_PARAM_INVALID, 5);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsSdfQosValid
 Description     : SDF Qos信息的合法性检查
 Input           : pstSdfQosInfo -- SDF Qos信息的结构指针
 Output          : None
 Return          : NAS_ESM_FAILURE -- 信息不合法
                   NAS_ESM_SUCCESS -- 信息合法

 History         :
    1.liuwenyu 00143951      2010-9-1  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsSdfQosValid
(
    const APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo
)
{
     /* 检测QCI的合法性 */
     if ((pstSdfQosInfo->ucQCI < NAS_ESM_QCI_TYPE_QCI1_GBR)
         || (pstSdfQosInfo->ucQCI > NAS_ESM_QCI_TYPE_QCI9_NONGBR))
     {
         NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_EPS_QOS_IE,
                                         ESM_ENCODE_CN_MSG_QCI_INVALID,
                                         pstSdfQosInfo->ucQCI);
         TLPS_PRINT2LAYER_WARNING(NAS_ESM_IsSdfQosValid_ENUM, LNAS_PARAM_INVALID);
         return NAS_ESM_FAILURE;
     }

     if (PS_TRUE == NAS_ESM_IsGbrBearer(pstSdfQosInfo->ucQCI))
     {
         if ((pstSdfQosInfo->ulDLGMaxRate > pstSdfQosInfo->ulDLMaxRate)
          || (pstSdfQosInfo->ulULGMaxRate > pstSdfQosInfo->ulULMaxRate))
          {
             NAS_ESM_WARN_LOG("NAS_ESM_IsSdfQosValid:APP->SM ,MBR < GBR!");
             NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_EPS_QOS_IE,
                                             ESM_ENCODE_CN_MSG_MAXRATE_INVALID,
                                             pstSdfQosInfo->ulDLGMaxRate);
             TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsSdfQosValid_ENUM, LNAS_FAIL, 1);
             return NAS_ESM_FAILURE;
          }

         if ((NAS_ESM_EPS_QOS_NULL_RATE == pstSdfQosInfo->ulULMaxRate)
          && (NAS_ESM_EPS_QOS_NULL_RATE == pstSdfQosInfo->ulDLMaxRate))
         {
             NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_EPS_QOS_IE,
                                             ESM_ENCODE_CN_MSG_MAXRATE_INVALID,
                                             pstSdfQosInfo->ulULMaxRate);
             TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsSdfQosValid_ENUM, LNAS_FAIL, 2);
             return NAS_ESM_FAILURE;
         }
     }

     return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsGwAuthInfoValid
 Description     : 网关鉴权信息的合法性检查
 Input           : pstGwAuthInfo -- 网关鉴权信息的结构指针
 Output          : None
 Return          : NAS_ESM_FAILURE -- 信息不合法
                   NAS_ESM_SUCCESS -- 信息合法

 History         :
    1.liuwenyu 00143951      2010-9-1  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsGwAuthInfoValid
(
    const APP_ESM_GW_AUTH_INFO_STRU           *pstGwAuthInfo
)
{
    if (pstGwAuthInfo->ucUserNameLen > APP_ESM_MAX_USER_NAME_LEN)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsGwAuthInfoValid:APP->ESM ,User name len is invalid!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsGwAuthInfoValid_ENUM, LNAS_PARAM_INVALID, 1);
        return APP_ERR_SM_USER_NAME_TOO_LONG;
    }

    if (pstGwAuthInfo->ucPwdLen > APP_ESM_MAX_PASSWORD_LEN)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsGwAuthInfoValid:APP->ESM ,Password len is invalid!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsGwAuthInfoValid_ENUM, LNAS_PARAM_INVALID, 2);
        return APP_ERR_SM_USER_PASSWORD_TOO_LONG;
    }

    if (pstGwAuthInfo->ucAccNumLen > APP_ESM_MAX_ACCESS_NUM_LEN)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsGwAuthInfoValid:APP->ESM ,Access Num len is invalid!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsGwAuthInfoValid_ENUM, LNAS_PARAM_INVALID, 3);
        return APP_ERR_SM_ACCESS_NUM_TOO_LONG;
    }

    if (pstGwAuthInfo->enGwAuthType >= APP_ESM_AUTH_TYPE_BUTT)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsGwAuthInfoValid:APP->ESM ,Auth Type error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsGwAuthInfoValid_ENUM, LNAS_PARAM_INVALID, 4);
        return APP_ERR_SM_AUTH_TYPE_ILLEGAL;
    }

    return APP_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_IsSdfParaOtherInfoValid
 Description     : SDF 静态信息中，pdn类型，IP地址分配方式
                   承载类型的合法性检查
 Input           : pstSdfPara      -- SDF静态信息结构的指针
 Output          : None
 Return          : NAS_ESM_FAILURE -- 静态信息不合法
                   NAS_ESM_SUCCESS -- 静态信息合法
 History         :
    1.liuwenyu 00143951      2010-9-1  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsSdfParaOtherInfoValid
(
    const NAS_ESM_SDF_PARA_STRU           *pstSdfPara
)
{
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
    {
        if ((pstSdfPara->enPdnType >= APP_ESM_PDN_TYPE_BUTT)
          ||(pstSdfPara->enPdnType == NAS_ESM_NULL))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_IsSdfParaOtherInfoValid:Pdn type error!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsSdfParaOtherInfoValid_ENUM, LNAS_PARAM_INVALID, 1);
            return NAS_ESM_FAILURE;
        }
    }

    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitIpv4AddrAllocType)
     && (pstSdfPara->enIpv4AddrAllocType >= APP_ESM_IPV4_ADDR_ALLOC_TYPE_BUTT))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsSdfParaOtherInfoValid:IP address allocacte type error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsSdfParaOtherInfoValid_ENUM, LNAS_PARAM_INVALID, 2);
        return NAS_ESM_FAILURE;
    }

    if (pstSdfPara->enBearerCntxtType >= NAS_ESM_BEARER_TYPE_BUTT)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsSdfParaOtherInfoValid:bearer type error!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_IsSdfParaOtherInfoValid_ENUM, LNAS_PARAM_INVALID, 3);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsSdfParaValid
 Description     : 判断SDF的静态信息是否合法
 Input           : pstSdfPara      -- SDF静态信息结构的指针
 Output          : None
 Return          : NAS_ESM_FAILURE -- 静态信息不合法
                   NAS_ESM_SUCCESS -- 静态信息合法
 History         :
    1.liuwenyu 00143951      2010-9-1  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsSdfParaValid
(
    const NAS_ESM_SDF_PARA_STRU           *pstSdfPara
)
{
    VOS_UINT32                          ulCnt     = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_APN_STRU            stApnInfo = {NAS_ESM_NULL};

    /* 对TFT的检查*/
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstSdfPara->ulPfNum; ulCnt++)
    {
        if (NAS_ESM_FAILURE == NAS_ESM_IsTftInfoValid(&pstSdfPara->astCntxtTftInfo[ulCnt]))
        {
            return NAS_ESM_FAILURE;
        }
    }

    /* 对SDF Qos的检查 */
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpSdfQos)
    {
       if (NAS_ESM_FAILURE == NAS_ESM_IsSdfQosValid(&pstSdfPara->stSdfQosInfo))
       {
            return NAS_ESM_FAILURE;
       }
    }

    /* 对网关鉴权信息的检查 */
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpGwAuthInfo)
    {
        if (APP_SUCCESS != NAS_ESM_IsGwAuthInfoValid(&pstSdfPara->stGwAuthInfo))
        {
            return NAS_ESM_FAILURE;
        }
    }

    /* 对Apn信息的检查*/
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
    {

        if (NAS_ESM_FAILURE == NAS_ESM_ApnTransformaton(&stApnInfo,
                                                        &pstSdfPara->stApnInfo))
        {
            return NAS_ESM_FAILURE;
        }

    }

    if (NAS_ESM_FAILURE == NAS_ESM_IsSdfParaOtherInfoValid(pstSdfPara))
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}




/*****************************************************************************
 Function Name   : NAS_ESM_GetAppErrorByEsmCause
 Description     : 根据ESM原因值，获得对应的App错误码
 Input           : enEsmCause -- ESM原因值
 Output          : None
 Return          : App错误码

 History         :
    1.liuwenyu00143951      2009-09-22  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_GetAppErrorByEsmCause
(
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
)
{
    VOS_UINT32          ulArrayLength = NAS_ESM_GetEsmAppErrorMapArrayLen();
    VOS_UINT32          ulCnt         = VOS_NULL;
    NAS_ESM_APP_ERROR_MAPPING_STRU   *pstAppErrorEle = NAS_ESM_GetEsmAppErrorMapTbl();

    for (ulCnt = 0; ulCnt < ulArrayLength; ulCnt++ )
    {
        if (pstAppErrorEle[ulCnt].enEsmCause == enEsmCause)
        {
            return pstAppErrorEle[ulCnt].ulAppErrorCode;
        }
    }

    return APP_ERR_SM_NW_PROT_ERR_UNSPECIFIED;
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetBearerLinkedCidNum
 Description     : 获取承载对应的激活的Cid的个数
 Input           : ulEpsbId -- 承载号
 Output          : None
 Return          : 承载对应的激活的Cid个数
 History         :
    1.liuwenyu 00143951      2010-3-8  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_GetBearerLinkedCidNum
(
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulCnt       = NAS_ESM_NULL;
    VOS_UINT32                          ulActCidNum = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo = VOS_NULL_PTR;

    pstEpsbInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* 统计承载对应的激活的Cid数目*/
    for (ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if (NAS_ESM_OP_TRUE == ((pstEpsbInfo->ulBitCId >> ulCnt) & NAS_ESM_BIT_0))
        {
            ulActCidNum++;
        }
    }

    return ulActCidNum;
}



VOS_INT32  NAS_ESM_PrintAppEsmSetBearerTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_SET_BEARER_TYPE_REQ_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_BEARER_TYPE_REQ_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enSetType = %d \r\n",
                       pstRcvMsg->enSetType,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enBearCidType = %d \r\n",
                       pstRcvMsg->enBearCidType,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpLinkdCid)
    {
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " ulLinkdCid = %d \r\n",
                           pstRcvMsg->ulLinkdCid,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }


    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_SET_BEARER_TYPE_REQ_STRU****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}




VOS_INT32  NAS_ESM_PrintAppEsmSetManageTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                                    ilOutPutLen = 0;
    VOS_UINT16                                   usTotalLen  = usOffset;
    APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enSetType = %d \r\n",
                       pstRcvMsg->enSetType,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enAnsMode = %d \r\n",
                       pstRcvMsg->enAnsMode,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    if (APP_ESM_ANSWER_MODE_AUTO == pstRcvMsg->enAnsMode)
    {
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " enAnsType = %d \r\n",
                           pstRcvMsg->enAnsType,
                           &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }


    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32  NAS_ESM_PrintAppEsmSetPdnTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_SET_PDN_TYPE_REQ_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_PDN_TYPE_REQ_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enSetType = %d \r\n",
                       pstRcvMsg->enSetType,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enPdnType = %d \r\n",
                       pstRcvMsg->enPdnType,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpIpv4AddrAllocType)
    {
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " enIpv4AddrAllocType = %d \r\n",
                           pstRcvMsg->enIpv4AddrAllocType,
                           &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }


    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_SET_PDN_TYPE_REQ_STRU****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32  NAS_ESM_PrintAppEsmSetEpsQosReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_SET_EPS_QOS_REQ_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_EPS_QOS_REQ_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enSetType = %d \r\n",
                       pstRcvMsg->enSetType,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " stSdfQosInfo.ucQCI = %d \r\n",
                       pstRcvMsg->stSdfQosInfo.ucQCI,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " stSdfQosInfo.ulULMaxRate = %d \r\n",
                       pstRcvMsg->stSdfQosInfo.ulULMaxRate,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " stSdfQosInfo.ulDLMaxRate = %d \r\n",
                       pstRcvMsg->stSdfQosInfo.ulDLMaxRate,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " stSdfQosInfo.ulULGMaxRate = %d \r\n",
                       pstRcvMsg->stSdfQosInfo.ulULGMaxRate,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " stSdfQosInfo.ulDLGMaxRate = %d \r\n",
                       pstRcvMsg->stSdfQosInfo.ulDLGMaxRate,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_SET_EPS_QOS_REQ_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  NAS_ESM_PrintAppEsmSetGwAuthReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_SET_GW_AUTH_REQ_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_GW_AUTH_REQ_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enGwAuthType = %d \r\n",
                       pstRcvMsg->stGwAuthInfo.enGwAuthType,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "stGwAuthInfo.ucAccNumLen = %d \r\n",
                       pstRcvMsg->stGwAuthInfo.ucAccNumLen,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->stGwAuthInfo.ucAccNumLen; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " auAccessNum[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->stGwAuthInfo.auAccessNum[ulLoop],
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "stGwAuthInfo.ucUserNameLen = %d \r\n",
                       pstRcvMsg->stGwAuthInfo.ucUserNameLen,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->stGwAuthInfo.ucUserNameLen; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " aucUserName[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->stGwAuthInfo.aucUserName[ulLoop],
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "stGwAuthInfo.ucPwdLen = %d \r\n",
                       pstRcvMsg->stGwAuthInfo.ucPwdLen,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    for (ulLoop = 0; ulLoop < pstRcvMsg->stGwAuthInfo.ucPwdLen; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " aucPwd[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->stGwAuthInfo.aucPwd[ulLoop],
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_SET_GW_AUTH_REQ_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  NAS_ESM_PrintAppEsmSetCgdontReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_SET_CGDCONT_REQ_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_CGDCONT_REQ_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpApn)
    {
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " aucApnName = %d \r\n",
                           (VOS_UINT32)pstRcvMsg->stApnInfo.aucApnName,
                           &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " ucApnLen = %d \r\n",
                           pstRcvMsg->stApnInfo.ucApnLen,
                           &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpBearType)
    {
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " enBearCidType = %d \r\n",
                           pstRcvMsg->enBearCidType,
                           &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

    }

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPdnType)
    {
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " enBearCidType = %d \r\n",
                           pstRcvMsg->enPdnType,
                           &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

    }

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpIpv4AddrAllocType)
    {
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " enIpv4AddrAllocType = %d \r\n",
                           pstRcvMsg->enIpv4AddrAllocType,
                           &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

    }

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enGwAuthType = %d \r\n",
                       pstRcvMsg->enSetType,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_SET_CGDCONT_REQ_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}




VOS_INT32  NAS_ESM_PrintEsmAppIpv6InfoNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLoop2;
    APP_ESM_IPV6_INFO_NOTIFY_STRU      *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_IPV6_INFO_NOTIFY_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ucEpsbId = %d \r\n",
                       pstRcvMsg->ucEpsbId,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ucIpv6PrefixNum = %d \r\n",
                       pstRcvMsg->ucIpv6PrefixNum,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ucIpv6PrefixNum; ulLoop++)
    {
         NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ucPrefixLen = %d \r\n",
                       pstRcvMsg->astIpv6PrefixArray[ulLoop].ucPrefixLen,
                      &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        for (ulLoop2 = 0; ulLoop2 < pstRcvMsg->astIpv6PrefixArray[ulLoop].ucPrefixLen; ulLoop2++)
        {
            NAS_COMM_nsprintf_2(pcBuff,
                               usTotalLen,
                               " aucPrefix[%d] = %d \r\n",
                               ulLoop2,
                               pstRcvMsg->astIpv6PrefixArray[ulLoop].aucPrefix[ulLoop2],
                              &ilOutPutLen);

            usTotalLen += (VOS_UINT16)ilOutPutLen;
        }
    }

    return (usTotalLen - usOffset) ;
}


VOS_INT32  NAS_ESM_PrintEsmAppProcedureAbortNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU      *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                      &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  NAS_ESM_PrintEsmAppSetResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_PARA_SET_CNF_STRU          *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_PARA_SET_CNF_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "ulSetRslt = %d \r\n",
                       pstRcvMsg->ulSetRslt,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_PARA_SET_CNF_STRU****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  NAS_ESM_PrintEsmAppCgdontResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    APP_ESM_SET_CGDCONT_CNF_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_CGDCONT_CNF_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulCid = %d \r\n",
                       pstRcvMsg->ulCid,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "ulSetRslt = %d \r\n",
                       pstRcvMsg->ulRslt,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_PARA_SET_CNF_STRU****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}





VOS_INT32  NAS_ESM_PrintEsmAppSetManageTypeResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                               ilOutPutLen = 0;
    VOS_UINT16                              usTotalLen  = usOffset;
    APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU  *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                        usTotalLen,
                        " ulSetRslt = %d \r\n",
                        pstRcvMsg->ulSetRslt,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  NAS_ESM_PrintEsmAppMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)

{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulEsmAppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulEsmAppMsgNum = sizeof(g_astEsmAppMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulEsmAppMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astEsmAppMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulEsmAppMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astEsmAppMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astEsmAppMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astEsmAppMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ESM_LOG1("NAS_ESM_PrintEsmAppMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEsmAppMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}

VOS_INT32  NAS_ESM_PrintEsmTimer
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    VOS_UINT32                           ulTimerType
)

{
    VOS_UINT32                          ulEsmTimerNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulEsmTimerNum = sizeof(g_astEsmStateTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* 打印对应的消息 */
    if ( ulTimerType < ulEsmTimerNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astEsmStateTimerArray[ulTimerType].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ESM_LOG1("NAS_ESM_PrintEsmTimer, Invalid enMsgId: ",ulTimerType);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEsmTimer_ENUM, LNAS_MSG_INVALID, ulTimerType);
    }

    return (usTotalLen - usOffset);

}


VOS_VOID NAS_ESM_PrintEsmRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "NAS ESM Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PrintEsmRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PrintEsmRevMsg_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulSenderPid )
    {
        case PS_PID_RABM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEsmRabmMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);

            break;

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "MM-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmEsmMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg);

            break;

        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "APP(OM)-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ESM_PrintEsmAppMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg);
            break;
        #if (FEATURE_PTM == FEATURE_ON)
        case MSP_PID_DIAG_APP_AGENT  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "APP(MSP_PID_DIAG_APP_AGENT)-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ESM_PrintEsmAppMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg);
            break;
        #endif
        case WUEPS_PID_TAF:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "SM-->ESM\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintSmEsmMsg(pcBuff,
                                                usTotalLen,
                                                pstMsg);
            break;
        case VOS_PID_TIMER  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TIMER-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ESM_PrintEsmTimer(pcBuff,
                                            usTotalLen,
                                            ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulPara);
            break;

        /*case MSP_PID_DIAG_APP_AGENT:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "om-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;
            break;*/

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case UEPS_PID_EHSM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "EHSM-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEhsmEsmMsg(
                                             pcBuff,
                                             usTotalLen,
                                             pstMsg);
            break;
        #endif


        default:
            NAS_ESM_LOG2("NAS_PrintRevSmMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulSenderPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ESM_PrintEsmRevMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ESM_LOG2("NAS_ESM_PrintEsmRevMsg, print return zero length.SenderPid, MsgId: ",
                      pstMsg->ulSenderPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ESM_PrintEsmRevMsg_ENUM, 1, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}


VOS_VOID NAS_ESM_PrintEsmSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "NAS ESM Send Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PrintEsmSendMsg, Print send msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PrintEsmSendMsg_ENUM, LNAS_MSG_INVALID);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_RABM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "ESM-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEsmRabmMsg(
                                             pcBuff,
                                             usTotalLen,
                                             pstMsg);
            break;

        case PS_PID_MM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "ESM-->MM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmEsmMsg(
                                            pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "ESM-->APP(OM)\t",
                            &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ESM_PrintEsmAppMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg);
            break;
        #if (FEATURE_PTM == FEATURE_ON)
        case MSP_PID_DIAG_APP_AGENT  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "ESM-->APP(MSP_PID_DIAG_APP_AGENT)\t",
                            &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ESM_PrintEsmAppMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg);
            break;
        #endif
        case WUEPS_PID_TAF:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "ESM-->SM\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintSmEsmMsg(pcBuff,
                                                usTotalLen,
                                                pstMsg);
            break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case UEPS_PID_EHSM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "ESM-->EHSM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEhsmEsmMsg(
                                             pcBuff,
                                             usTotalLen,
                                             pstMsg);
            break;
        #endif
        default:
            NAS_ESM_LOG2("NAS_ESM_PrintEsmSendMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulReceiverPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ESM_PrintEsmSendMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ESM_LOG2("NAS_ESM_PrintEsmSendMsg, print return zero length. ReceiverPid, MsgId: ",
                              pstMsg->ulReceiverPid,
                              pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ESM_PrintEsmSendMsg_ENUM, 1, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff,usTotalLen);

    return ;

}

/*****************************************************************************
 Function Name   : NAS_ESM_PrintEpsQos
 Description     : 打印承载Qos
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-04-15   Draft Enact

*****************************************************************************/

VOS_VOID NAS_ESM_PrintEpsQos( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    if(NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpEpsQos )
    {
        NAS_ESM_LOG1("ucQCI = ",pstEpsbInfo->stEpsQoSInfo.stQosInfo.ucQCI);
        NAS_ESM_LOG1("ucNwQCI = ",pstEpsbInfo->stEpsQoSInfo.ucNwQCI);
        NAS_ESM_LOG1("ulULMaxRate = ",pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulULMaxRate);
        NAS_ESM_LOG1("ulDLMaxRate = ",pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulDLMaxRate);
        NAS_ESM_LOG1("ulULGMaxRate = ",pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulULGMaxRate);
        NAS_ESM_LOG1("ulDLGMaxRate = ",pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulDLGMaxRate);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsQos_ENUM, 1, pstEpsbInfo->stEpsQoSInfo.stQosInfo.ucQCI);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsQos_ENUM, 2, pstEpsbInfo->stEpsQoSInfo.ucNwQCI);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsQos_ENUM, 3, pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulULMaxRate);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsQos_ENUM, 4, pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulDLMaxRate);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsQos_ENUM, 5, pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulULGMaxRate);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsQos_ENUM, 6, pstEpsbInfo->stEpsQoSInfo.stQosInfo.ulDLGMaxRate);
    }

}


/*****************************************************************************
 Function Name   : NAS_ESM_PrintEpsLinkedSdfId
 Description     : 打印承载包含的SDF号
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-04-15   Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_PrintEpsLinkedSdfId( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    VOS_UINT32                          ulBitCId    = NAS_ESM_NULL;
    VOS_UINT8                           ucLoop      = NAS_ESM_NULL;
    PS_BOOL_ENUM_UINT8                  enIsFirSdf  = PS_TRUE;

    if(NAS_ESM_OP_TRUE != pstEpsbInfo->bitOpCId )
    {
         NAS_ESM_INFO_LOG(" no SDF\r\n");
         TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsLinkedSdfId_ENUM, ESM_SDF_ERROR);
         return ;
    }

    ulBitCId = pstEpsbInfo->ulBitCId;

    NAS_ESM_INFO_LOG("Eps Bearer Linked CID:");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsLinkedSdfId_ENUM, ESM_CID_IS);

    for (ucLoop = NAS_ESM_MIN_CID; ucLoop <= NAS_ESM_MAX_CID; ucLoop++)
    {
        if (NAS_ESM_OP_TRUE != ((ulBitCId >> ucLoop) & NAS_ESM_BIT_0))
        {
            continue;
        }

        if (PS_TRUE == enIsFirSdf)
        {
            NAS_ESM_LOG1("",ucLoop);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsLinkedSdfId_ENUM, 1, ucLoop);
            enIsFirSdf = PS_FALSE;
        }
        else
        {
            NAS_ESM_LOG1(",",ucLoop);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsLinkedSdfId_ENUM, 2, ucLoop);
        }
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_PrintEpsPdn
 Description     : 打印承载信息中的PDN信息
 Input           : pstEpsbInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2010-01-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_PrintEpsPdn( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbInfo->enBearerCntxtType))
        && (NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpPdnAddr))
    {
        if ( (APP_ESM_PDN_TYPE_IPV4 == pstEpsbInfo->stPdnAddrInfo.ucIpType)
             || (APP_ESM_PDN_TYPE_IPV4_IPV6 == pstEpsbInfo->stPdnAddrInfo.ucIpType))
        {
            NAS_ESM_INFO_LOG("ucIpType = APP_ESM_PDN_TYPE_IPV4");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsPdn_ENUM, 4);
            NAS_ESM_LOG1("aucIpV4Addr[0] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[0]);

            NAS_ESM_LOG1("aucIpV4Addr[1] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[1]);
            NAS_ESM_LOG1("aucIpV4Addr[2] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[2]);
            NAS_ESM_LOG1("aucIpV4Addr[3] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[3]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 4, pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[0]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 4, pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[1]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 4, pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[2]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 4, pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[3]);
        }

        if ( (APP_ESM_PDN_TYPE_IPV6 == pstEpsbInfo->stPdnAddrInfo.ucIpType)
             || (APP_ESM_PDN_TYPE_IPV4_IPV6 == pstEpsbInfo->stPdnAddrInfo.ucIpType))
        {
            NAS_ESM_INFO_LOG("ucIpType = APP_ESM_PDN_TYPE_IPV6");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsPdn_ENUM, 6);
            NAS_ESM_LOG1("aucIpV6Addr[0] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[0]);

            NAS_ESM_LOG1("aucIpV6Addr[1] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[1]);
            NAS_ESM_LOG1("aucIpV6Addr[2] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[2]);
            NAS_ESM_LOG1("aucIpV6Addr[3] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[3]);

            NAS_ESM_LOG1("aucIpV6Addr[4] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[4]);
            NAS_ESM_LOG1("aucIpV6Addr[5] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[5]);
            NAS_ESM_LOG1("aucIpV6Addr[6] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[6]);

            NAS_ESM_LOG1("aucIpV6Addr[7] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[7]);
            NAS_ESM_LOG1("aucIpV6Addr[8] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[8]);
            NAS_ESM_LOG1("aucIpV6Addr[9] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[9]);

            NAS_ESM_LOG1("aucIpV6Addr[10] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[10]);
            NAS_ESM_LOG1("aucIpV6Addr[11] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[11]);
            NAS_ESM_LOG1("aucIpV6Addr[12] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[12]);

            NAS_ESM_LOG1("aucIpV6Addr[13] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[13]);
            NAS_ESM_LOG1("aucIpV6Addr[14] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[14]);
            NAS_ESM_LOG1("aucIpV6Addr[15] = ",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[15]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[0]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[1]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[2]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[3]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[4]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[5]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[6]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[7]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[8]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[9]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[10]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[11]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[12]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[13]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[14]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsPdn_ENUM, 6, pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[15]);
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_PrintEpsApnAmbr
 Description     : 打印承载信息中的APN-AMBR信息
 Input           : pstEpsbInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2010-01-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_PrintEpsApnAmbr( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbInfo->enBearerCntxtType))
        && (NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpApnAmbr))
    {
        NAS_ESM_INFO_LOG("APN-AMBR Info :\r\n");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsApnAmbr_ENUM, LNAS_ENTRY);
        NAS_ESM_LOG1("DLApnAmbr = ",pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbr);
        NAS_ESM_LOG1("DLApnAmbrExt = ",pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbrExt);
        NAS_ESM_LOG1("DLApnAmbrExt2 = ",pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbrExt2);
        NAS_ESM_LOG1("ULApnAmbr = ",pstEpsbInfo->stApnAmbrInfo.ucULApnAmbr);
        NAS_ESM_LOG1("ULApnAmbrExt = ",pstEpsbInfo->stApnAmbrInfo.ucULApnAmbrExt);
        NAS_ESM_LOG1("ULApnAmbrExt2 = ",pstEpsbInfo->stApnAmbrInfo.ucULApnAmbrExt2);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsApnAmbr_ENUM, 1, pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbr);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsApnAmbr_ENUM, 2, pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbrExt);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsApnAmbr_ENUM, 3, pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbrExt2);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsApnAmbr_ENUM, 4, pstEpsbInfo->stApnAmbrInfo.ucULApnAmbr);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsApnAmbr_ENUM, 5, pstEpsbInfo->stApnAmbrInfo.ucULApnAmbrExt);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsApnAmbr_ENUM, 6, pstEpsbInfo->stApnAmbrInfo.ucULApnAmbrExt2);
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_PrintEpsbInfo
 Description     : 打印某条承载的信息
 Input           : VOS_UINT32 ulEpsbId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-04-15   Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_PrintEpsbInfo(VOS_UINT32 ulEpsbId)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo         = VOS_NULL_PTR;

    if ((ulEpsbId < NAS_ESM_MIN_EPSB_ID) || (ulEpsbId > NAS_ESM_MAX_EPSB_ID))
    {
        NAS_ESM_INFO_LOG("输入的EPSBID值错误－EPSBID取值范围为5..15 \r\n");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsbInfo_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    pstEpsbInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    NAS_ESM_INFO_LOG("****************Begin:EPS Bearer Information****************");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsbInfo_ENUM, LNAS_ENTRY);

    NAS_ESM_LOG1("ulEpsbId = ",pstEpsbInfo->ulEpsbId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsbInfo_ENUM, 1, pstEpsbInfo->ulEpsbId);

    NAS_ESM_LOG1("enBearerCntxtType = ",pstEpsbInfo->enBearerCntxtType);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsbInfo_ENUM, 2, pstEpsbInfo->enBearerCntxtType);

    if ((pstEpsbInfo->ulLinkedEpsbId >= NAS_ESM_MIN_EPSB_ID)
     || (pstEpsbInfo->ulLinkedEpsbId <= NAS_ESM_MAX_EPSB_ID) )
    {
        NAS_ESM_LOG1("ulLinkedEpsbId = ",pstEpsbInfo->ulLinkedEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PrintEpsbInfo_ENUM, 3, pstEpsbInfo->ulLinkedEpsbId);
    }

    /* 打印承载QOS */
    NAS_ESM_PrintEpsQos(pstEpsbInfo);

    /* 打印承载包含的SDF ID */
    NAS_ESM_PrintEpsLinkedSdfId(pstEpsbInfo);

    /* 打印PDN信息 */
    NAS_ESM_PrintEpsPdn(pstEpsbInfo);

    /* 打印APN-AMBR信息 */
    NAS_ESM_PrintEpsApnAmbr(pstEpsbInfo);
    NAS_ESM_INFO_LOG("****************End:EPS Bearer Information****************");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PrintEpsbInfo_ENUM, LNAS_LEAVE);

}

/*****************************************************************************
 Function Name   : NAS_ESM_GetAllEpsBearerInPdn
 Description     : 获取某PDN下的所有承载号
 Input           : ucEpsbId---------------------承载号
 Output          : pucEpsBearNum----------------承载数
                   pucEspbId--------------------承载号数组首地址
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-05-27   Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_GetAllEpsBearerInPdn
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                          *pucEpsBearNum,
    VOS_UINT8                          *pucEspbId
)
{
    VOS_UINT8                           ucCnt               = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    *pucEpsBearNum = NAS_ESM_NULL;

    if (PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(ucEpsbId)))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_GetAllEpsBearerInPdn:Input para ucEpsbId is not default bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_GetAllEpsBearerInPdn_ENUM, LNAS_PARAM_INVALID);

        return NAS_ESM_FAILURE;
    }

    pucEspbId[*pucEpsBearNum] = ucEpsbId;
    (*pucEpsBearNum)++;

    /*循环承载信息，查找与此承载关联的专有承载*/
    for( ucCnt = NAS_ESM_MIN_EPSB_ID; ucCnt <= NAS_ESM_MAX_EPSB_ID; ucCnt++ )
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucCnt);

        /*某一承载的Linked EPSB ID为当前承载ID*/
        if( (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType)
            && (NAS_ESM_BEARER_STATE_ACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)\
            && (pstEpsbCntxtInfo->ulLinkedEpsbId == ucEpsbId) )
        {
            pucEspbId[*pucEpsBearNum] = ucCnt;
            (*pucEpsBearNum)++;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsExistSamePrecedenceInTft
 Description     : 判断TFT中是否有相同precedence 的两个PF
 Input           : ulPfNum -- packet filter 数目
                   pstTFT  -- packet filter 数组的首地址
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu 00143951      2010-05-26  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsExistSamePrecedenceInTft
(
    VOS_UINT32                          ulPfNum,
    const NAS_ESM_CONTEXT_TFT_STRU     *pstTFT
)
{
    VOS_UINT32                          ulCnt1 = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt2 = NAS_ESM_NULL;

    for (ulCnt1 = NAS_ESM_NULL;ulCnt1 < ulPfNum;ulCnt1++)
    {
        for (ulCnt2 = ulCnt1 + 1 ;ulCnt2 < ulPfNum;ulCnt2++)
        {
            if (pstTFT[ulCnt1].ucPrecedence == pstTFT[ulCnt2].ucPrecedence)
            {
                return NAS_ESM_SUCCESS;
            }
        }
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DHCPGetIPv4Mask
 Description     : 根据IP地址计算子网掩码
 Input           : pucIpv4Addr --- IP地址
 Output          : pucIpv4Mask --- 子网掩码
 Return          : VOS_VOID

 History         :
    1.sunli 00180715        2011-04-18  Modify

*****************************************************************************/
VOS_VOID NAS_ESM_DHCPGetIPv4Mask
(
    const VOS_UINT8                    *pucIpv4Addr,
    VOS_UINT8                          *pucIpv4Mask
)
{
    /*lint -e961*/
    VOS_UINT32                          ulMask = 0xfffffffe;
    /*lint +e961*/
    VOS_UINT32                          ulIpTemp = 0;
    VOS_UINT32                          ulFirstBit;


    /*lint -e701*/
    IP_GetUint32Data(ulIpTemp, pucIpv4Addr);
    ulFirstBit = ulIpTemp & 0x00000001;
    /*lint +e701*/


    while (0x0 != ulIpTemp)
    {
        ulMask = ulMask << 1;
        ulIpTemp = ulIpTemp >> 1;

        if (ulFirstBit != (ulIpTemp & 0x00000001))
        {
            break;
        }
    }

    IP_SetUint32Data(pucIpv4Mask, ulMask);
}

/*****************************************************************************
 Function Name   : NAS_ESM_DHCPGetIPv4GateWay
 Description     : 根据IP地址和子网掩码计算网关
 Input           : pucIpv4Addr    --- IP地址
                   pucIpv4Mask    --- 子网掩码
 Output          : pucIpv4GateWay --- 网关
 Return          : VOS_VOID

 History         :
    1.sunli 00180715        2011-04-18  Modify

*****************************************************************************/
VOS_VOID NAS_ESM_DHCPGetIPv4GateWay
(
    const VOS_UINT8                    *pucIpv4Addr,
    const VOS_UINT8                    *pucIpv4Mask,
    VOS_UINT8                          *pucIpv4GateWay
)
{
    VOS_UINT32                          ulMaskTemp = 0;
    VOS_UINT32                          ulIpTemp = 0;
    VOS_UINT32                          ulGateWay = 0;

    /*lint -e701*/
    IP_GetUint32Data(ulIpTemp, pucIpv4Addr);
    IP_GetUint32Data(ulMaskTemp, pucIpv4Mask);
    /*lint +e701*/

    ulGateWay = (ulIpTemp & ulMaskTemp) + 1;

    while (ulGateWay == ulIpTemp)
    {
        ulGateWay++;
    }

    IP_SetUint32Data(pucIpv4GateWay, ulGateWay);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ClearSdfPara
 Description     : 根据Cid清除Sdf参数
 Input           : Cid
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangfan 00159566      2011-6-29  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ClearSdfPara(VOS_UINT32  ulCid)
{
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara       = VOS_NULL_PTR;

    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    NAS_ESM_MEM_SET_S(pstSdfPara, sizeof(NAS_ESM_SDF_PARA_STRU), 0, sizeof(NAS_ESM_SDF_PARA_STRU));

    pstSdfPara->ulCId = ulCid;

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ClearNwCtrlSdfPara
 Description     : 清除网侧主动建立专有承载的静态信息 CID 20~31
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangfan 00159566      2011-6-27  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ClearNwCtrlSdfPara(VOS_VOID)
{
    VOS_UINT32                          ulCnt            = NAS_ESM_NULL;

    /*打印信息*/
    NAS_ESM_INFO_LOG("NAS_ESM_ClearNwCtrlSdfPara: Clear Nw Control Cid Parameters!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearNwCtrlSdfPara_ENUM, LNAS_ENTRY);

    /* 遍历CID 21~31,清除所有静态信息 */
    for (ulCnt = NAS_ESM_MIN_NW_CONTROL_CID; ulCnt < NAS_ESM_MAX_CID_NUM; ulCnt++)
    {
        NAS_ESM_ClearSdfPara(ulCnt);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_Ipv4TransformPcoStru
 Description     : 转变PCO结构格式，用于适配上报APP中PCO结构和本地存储PCO结构的不同
 Input           : pstContPco  -- 本地存储的PCO结构指针
 Output          : pstTransPco-----转换格式后的PCO结构指针
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-03-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_Ipv4TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    pstTransPco->bitOpBcm = pstContPco->bitOpBcm;
    pstTransPco->enBcm = pstContPco->enBcm;

    /* 转化NBNS结构 */
    pstTransPco->ucNbnsNum = pstContPco->ucIpv4NbnsNum;
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstContPco->ucIpv4NbnsNum; ulCnt++)
    {
        pstTransPco->astNbns[ulCnt].ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astNbns[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv4Nbns[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN);
    }

    /* 转化DNS结构 */
    pstTransPco->ucDnsSerNum = pstContPco->ucIpv4DnsSerNum;
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstContPco->ucIpv4DnsSerNum; ulCnt++)
    {
        pstTransPco->astDnsServer[ulCnt].ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astDnsServer[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv4DnsServer[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN);
    }

    /* 转化PCSCF结构 */
    pstTransPco->ucPcscfNum = pstContPco->ucIpv4PcscfNum;
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstContPco->ucIpv4PcscfNum; ulCnt++)
    {
        pstTransPco->astPcscf[ulCnt].ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astPcscf[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv4Pcscf[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_Ipv6TransformPcoStru
 Description     : 转变PCO结构格式，用于适配上报APP中PCO结构和本地存储PCO结构的不同
 Input           : pstContPco  -- 本地存储的PCO结构指针
 Output          : pstTransPco-----转换格式后的PCO结构指针
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-03-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_Ipv6TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    pstTransPco->bitOpBcm = pstContPco->bitOpBcm;
    pstTransPco->enBcm = pstContPco->enBcm;

    /* 转化NBNS结构 */
    pstTransPco->ucNbnsNum = 0;


    /* 转化DNS结构 */
    pstTransPco->ucDnsSerNum = pstContPco->ucIpv6DnsSerNum;
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstContPco->ucIpv6DnsSerNum; ulCnt++)
    {
        pstTransPco->astDnsServer[ulCnt].ucIpType = NAS_ESM_PDN_IPV6;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astDnsServer[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv6DnsServer[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN);
    }

    /* 转化PCSCF结构 */
    pstTransPco->ucPcscfNum = pstContPco->ucIpv6PcscfNum;
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstContPco->ucIpv6PcscfNum; ulCnt++)
    {
        pstTransPco->astPcscf[ulCnt].ucIpType = NAS_ESM_PDN_IPV6;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astPcscf[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv6Pcscf[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_Ipv4v6TransformPcoStru
 Description     : 转变PCO结构格式，用于适配上报APP中PCO结构和本地存储PCO结构的不同
 Input           : pstContPco  -- 本地存储的PCO结构指针
 Output          : pstTransPco-----转换格式后的PCO结构指针
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-03-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_Ipv4v6TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    pstTransPco->bitOpBcm = pstContPco->bitOpBcm;
    pstTransPco->enBcm = pstContPco->enBcm;


    /* 转化NBNS结构 */
    pstTransPco->ucNbnsNum = pstContPco->ucIpv4NbnsNum;
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstContPco->ucIpv4NbnsNum; ulCnt++)
    {
        pstTransPco->astNbns[ulCnt].ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astNbns[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv4Nbns[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN);
    }

    /* 转化DNS结构 */
    for (ulCnt = 0; ulCnt < pstContPco->ucIpv4DnsSerNum; ulCnt++)
    {
        pstTransPco->astDnsServer[ulCnt].ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astDnsServer[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv4DnsServer[ulCnt].aucIpV4Addr[0]),
                            APP_MAX_IPV4_ADDR_LEN);
    }

    for (ulCnt = 0; ulCnt < pstContPco->ucIpv6DnsSerNum; ulCnt++)
    {
        if (NAS_ESM_PDN_IPV4 == pstTransPco->astDnsServer[ulCnt].ucIpType)
        {
            pstTransPco->astDnsServer[ulCnt].ucIpType = NAS_ESM_PDN_IPV4_IPV6;
        }
        else
        {
            pstTransPco->astDnsServer[ulCnt].ucIpType = NAS_ESM_PDN_IPV6;
        }

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astDnsServer[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv6DnsServer[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN);
    }
    pstTransPco->ucDnsSerNum = ((pstContPco->ucIpv4DnsSerNum < pstContPco->ucIpv6DnsSerNum)
                                 ? pstContPco->ucIpv6DnsSerNum :  pstContPco->ucIpv4DnsSerNum);

    /* 转化PCSCF结构 */
    for (ulCnt = 0; ulCnt < pstContPco->ucIpv4PcscfNum; ulCnt++)
    {
        if(NAS_ESM_MAX_PCSCF_NUM == ulCnt)
        {
            break;
        }
        pstTransPco->astPcscf[ulCnt].ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY_S(  pstTransPco->astPcscf[ulCnt].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstContPco->astIpv4Pcscf[ulCnt].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
    }

    for (ulCnt = 0; ulCnt < pstContPco->ucIpv6PcscfNum; ulCnt++)
    {
        if (NAS_ESM_PDN_IPV4 == pstTransPco->astPcscf[ulCnt].ucIpType)
        {
            pstTransPco->astPcscf[ulCnt].ucIpType = NAS_ESM_PDN_IPV4_IPV6;
        }
        else
        {
            pstTransPco->astPcscf[ulCnt].ucIpType = NAS_ESM_PDN_IPV6;
        }

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstTransPco->astPcscf[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN,
                            (VOS_VOID*)&(pstContPco->astIpv6Pcscf[ulCnt].aucIpV6Addr[0]),
                            APP_MAX_IPV6_ADDR_LEN);
    }
    pstTransPco->ucPcscfNum = ((pstContPco->ucIpv4PcscfNum < pstContPco->ucIpv6PcscfNum)
                                 ? pstContPco->ucIpv6PcscfNum :  pstContPco->ucIpv4PcscfNum);
}


/*****************************************************************************
 Function Name   : NAS_ESM_TransformPcoStru
 Description     : 转变PCO结构格式，用于适配上报APP中PCO结构和本地存储PCO结构的不同
 Input           : ucIpType -- PDN类型
                   pstContPco  -- 本地存储的PCO结构指针
 Output          : pstTransPco-----转换格式后的PCO结构指针
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-03-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_TransformPcoStru
(
    VOS_UINT8                           ucIpType,
    const NAS_ESM_CONTEXT_PCO_STRU           *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
)
{
    if (NAS_ESM_PDN_IPV4 == ucIpType)
    {
        NAS_ESM_Ipv4TransformPcoStru(pstContPco, pstTransPco);
    }
    else if (NAS_ESM_PDN_IPV6 == ucIpType)
    {
        NAS_ESM_Ipv6TransformPcoStru(pstContPco, pstTransPco);

    }
    else
    {
        NAS_ESM_Ipv4v6TransformPcoStru(pstContPco, pstTransPco);
    }
}
/*****************************************************************************
 Function Name   : NAS_ESM_ClearCid0StaticInfo
 Description     : 用于在清空资源时,重新初始化CID0的内容
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501   2012-3-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ClearCid0StaticInfo(VOS_VOID)
{
    NAS_ESM_SDF_PARA_STRU          *pstBearCntxtPara  = VOS_NULL_PTR;

    /* CID0在PS融合后比较特殊，在ESM维护的内容与NV的内容会存在不一致, 需将CID0初始化为专有类型 */
    pstBearCntxtPara = NAS_ESM_GetSdfParaAddr(NAS_ESM_NULL);

    NAS_ESM_MEM_SET_S(  pstBearCntxtPara,
                        sizeof(NAS_ESM_SDF_PARA_STRU),
                        0,
                        sizeof(NAS_ESM_SDF_PARA_STRU));

    pstBearCntxtPara->bitOpLinkdCId         = NAS_ESM_OP_TRUE;
    pstBearCntxtPara->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEDICATED;
    pstBearCntxtPara->ulLinkdCId            = 20;
}

/*****************************************************************************
 Function Name   : NAS_ESM_HasExistedEmergencyPdn
 Description     : 判断当前已经建立的EPS承载中是否有紧急PDN连接
 Input           : None
 Output          : None
 Return          : PS_TRUE    存在紧急PDN连接
                   PS_FALSE   不存在紧急PDN连接
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_HasExistedEmergencyPdn(VOS_VOID)
{
    VOS_UINT32 ulEpsId = 0;
    NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsCtxInfo = VOS_NULL_PTR;

    for (ulEpsId = NAS_ESM_MIN_EPSB_ID; ulEpsId <= NAS_ESM_MAX_EPSB_ID; ulEpsId++)
    {
        pstEpsCtxInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsId);

        if ((NAS_ESM_OP_TRUE == pstEpsCtxInfo->bitOpCId) &&
            (NAS_ESM_BEARER_STATE_ACTIVE == pstEpsCtxInfo->enBearerCntxtState) &&
            (NAS_ESM_BEARER_TYPE_EMERGENCY == pstEpsCtxInfo->enBearerCntxtType))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_HasEstingEmergencyPdn
 Description     : 判断当前是否存在正在建立的紧急PDN连接
 Input           : None
 Output          : None
 Return          : PS_TRUE    存在正在建立的紧急PDN连接
                   PS_FALSE   不存在正在建立的紧急PDN连接
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_HasEstingEmergencyPdn(VOS_VOID)
{
    VOS_UINT32 i = 0;
    NAS_ESM_STATE_INFO_STRU *pstStatTblInfo = VOS_NULL_PTR;

    for(i = 0; i < NAS_ESM_MAX_STATETBL_NUM; i++)
    {
        pstStatTblInfo = NAS_ESM_GetStateTblAddr(i);
        if ((NAS_ESM_ILL_CID != pstStatTblInfo->ulCid) &&
            (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStatTblInfo->enBearerCntxtType))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_HasEmergencyPdn
 Description     : 判断当前是否存在紧急PDN连接
 Input           : None
 Output          : None
 Return          : PS_TRUE    存在紧急PDN连接
                   PS_FALSE   不存在紧急PDN连接
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_HasEmergencyPdn(VOS_VOID)
{
    if (NAS_ESM_HasExistedEmergencyPdn() || NAS_ESM_HasEstingEmergencyPdn())
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_IsEmmEmcAttachedOrAttaching
 Description     : 判断当前EMM已经处于紧急注册状态或正在进行紧急注册，                        ü鼸SM内部信息来等效判断，
                   包含以下两种情况:
                      1. 只有一个正在建立的PDN连接请求，且为紧急类型，此时EMM正在进行紧急注册
                      2. 只有一个已经建立的PDN连接请求，且为紧急类型，此时EMM已经处于紧急注册
 Input           : None
 Output          : None
 Return          : PS_TRUE    EMM已经处于紧急注册状态或正在进行紧急注册
                   PS_FALSE   EMM既不处于紧急注册状态也没有正在进行紧急注册
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsEmmEmcAttachedOrAttaching(VOS_VOID)
{
    if (((0 == NAS_ESM_GetCurPdnNum()) && (PS_TRUE == NAS_ESM_HasEstingEmergencyPdn())) ||
        ((1 == NAS_ESM_GetCurPdnNum()) && (PS_TRUE == NAS_ESM_HasExistedEmergencyPdn())))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsDefaultEpsBearerType
 Description     : 判断承载类型是否是默认承载，这里的默认承载是协议原本意义上的默认承载类型
                   (通过ACTIVATE DEFAULT EPS BEARER CONTEXT REQUEST激活)，因此包括紧急类型承载
 Input           : Type  承载类型
 Output          : None
 Return          : PS_TRUE    该承载是默认承载
                   PS_FALSE   该承载不是默认承载
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsDefaultEpsBearerType(VOS_UINT32 Type)
{
    if ((NAS_ESM_BEARER_TYPE_DEFAULT == Type) || (NAS_ESM_BEARER_TYPE_EMERGENCY == Type))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_QueryStateTblIndexForEmc
 Description     : 在动态表中搜索紧急PDN建立消息
 Input           : None
 Output          : pulStateIndex  如果有紧急记录，通过此参数保存将该动态表索引值
 Return          : NAS_ESM_SUCCESS  搜索成功
                   NAS_ESM_FAILURE  搜索不成功
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryStateTblIndexForEmc(VOS_UINT32 *pulStateIndex)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStatTblnfo       = VOS_NULL_PTR;

    /*搜索 StateInfoTbl*/
    for(ulCnt = 0; ulCnt < NAS_ESM_MAX_STATETBL_NUM; ulCnt++)
    {
        pstStatTblnfo = NAS_ESM_GetStateTblAddr(ulCnt);
        if (PS_TRUE == pstStatTblnfo->stNwMsgRecord.ucIsEmcPdnReq)
        {
            *pulStateIndex = ulCnt;
            return NAS_ESM_SUCCESS;
        }
    }

    /*没有对应的节点*/
    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_DeactAllNonEmcPdn
 Description     : 释放当前所有非紧急PDN连接
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.liuhua    00212067       2012-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_DeactAllNonEmcPdn(VOS_VOID)
{
    VOS_UINT32 ulCid = 0;
    VOS_UINT32 ulEpsId = 0;
    VOS_UINT32 ulStateTblIndex = 0;
    NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsCtxInfo = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU      *pstStateTblInfo = VOS_NULL_PTR;
    APP_ESM_PDP_RELEASE_REQ_STRU  stAppPdpRelReq = {0};

    NAS_ESM_INFO_LOG("NAS_ESM_DeactAllNonEmcPdn: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DeactAllNonEmcPdn_ENUM, LNAS_ENTRY);

    /*清除动态表，紧急相关除外*/
    NAS_ESM_ClearStateTable(APP_ERR_SM_DETACHED, PS_TRUE);

    /*对所有非紧急PDN连接发起PDN DISCONNECT REQUEST*/
    for (ulCid = 0; ulCid < NAS_ESM_MAX_CID_NUM; ulCid++)
    {
        if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid, &ulEpsId))
        {
            pstEpsCtxInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsId);

            /*只有激活且是默认类型的承载才进行释放*/
            if ((pstEpsCtxInfo->enBearerCntxtState == NAS_ESM_BEARER_STATE_ACTIVE) &&
                (pstEpsCtxInfo->enBearerCntxtType == NAS_ESM_BEARER_TYPE_DEFAULT))
            {
                if (NAS_ESM_SUCCESS == NAS_ESM_GetStateTblIndexByCid(ulCid, &ulStateTblIndex))
                {
                    /*设置APP消息记录的标识位*/
                    pstStateTblInfo = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

                    /*设置承载状态和类别、关联承载信息*/
                    pstStateTblInfo->ulEpsbId           = ulEpsId;
                    pstStateTblInfo->enBearerCntxtState = NAS_ESM_GetBearCntxtState(ulEpsId);
                    pstStateTblInfo->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(ulEpsId);
                    pstStateTblInfo->ulLinkedEpsbId     = pstEpsCtxInfo->ulLinkedEpsbId;

                    /*准备CID*/
                    stAppPdpRelReq.ulCid = ulCid;
                    /*lint -e961*/
                    NAS_ESM_INFO_LOG2("NAS_ESM_DeactAllNonEmcPdn:", ulCid, ulEpsId);
                    TLPS_PRINT2LAYER_INFO2(NAS_ESM_DeactAllNonEmcPdn_ENUM, 1, ulCid, ulEpsId);
                    /*lint +e961*/
                    /*发起PDN DISCONNECT REQUEST空口消息*/
                    NAS_ESM_DefltAttMsgAppSdfRelReq((VOS_VOID*)&stAppPdpRelReq);
                }
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_ESM_SndOmEsmTimerStatus
 功能描述  : 发送消息给OM模块，ESM定时器运行完成
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月6日
   作    者   : niuxiufan 00181501
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_ESM_SndOmEsmTimerStatus(
    NAS_ESM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus,
    NAS_ESM_TIMER_PARA_ENUM_UINT8           enTimerId,
    VOS_UINT32                              ulTimerRemainLen
)
{
    NAS_ESM_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_ESM_TIMER_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmEsmTimerStatus: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndOmEsmTimerStatus_ENUM, LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ESM_TIMER_INFO_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId + PS_MSG_ID_ESM_TO_ESM_OM_BASE;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->enTimerId                   = enTimerId;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_ESM_MEM_FREE(pstMsg);

}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_GetSdfPara
 Description     : 获取APP的SDF PARA
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
/*lint -e426*/
/*lint -e830*/
/*lint -e429*/
VOS_UINT32  NAS_ESM_GetSdfPara
(
    VOS_UINT32                         *pulSdfNum,
    APP_ESM_SDF_PARA_STRU              *pstSdfPara
)
{
    VOS_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = APP_GetSdfPara (pulSdfNum, pstSdfPara);

    NAS_LMM_LogSdfPara (pulSdfNum, pstSdfPara ,ulRslt);

    #else
    ulRslt = Stub_APP_GetSdfPara(pulSdfNum, pstSdfPara);
    #endif
    return ulRslt;
}
/*lint +e429*/
/*lint +e830*/
/*lint +e426*/

/*****************************************************************************
 Function Name   : NAS_ESM_GetSdfPara
 Description     : 获取APP的PDP MANAGE INFO
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_GetPdpManageInfo
(
    APP_ESM_PDP_MANAGE_INFO_STRU  *pstPdpManageInfo
)
{
    VOS_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = APP_GetPdpManageInfo (pstPdpManageInfo);

    NAS_LMM_LogPdpManageInfo(pstPdpManageInfo,ulRslt);
    #else
    ulRslt = Stub_APP_GetPdpManageInfo(pstPdpManageInfo);
    #endif
    return ulRslt;
}
/*****************************************************************************
 Function Name   : NAS_ESM_IsCurrentApnExitRej50InfoAndSamePdnType
 Description     : 判断当前被拒绝的PDN是否在被拒列表中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-04  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsCurrentApnAvailable
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOPApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
)
{
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(enPdnType,ulBitOPApnInfo,pstApnInfo))
    {
        return NAS_ESM_FAILURE;
    }

    /* 如果选取的NV参数，APN被#51拒绝，则选取下一套 */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas51Rej(enPdnType,ulBitOPApnInfo,pstApnInfo))
    {
        return NAS_ESM_FAILURE;
    }

    /* 如果选取的NV参数，APN被#66拒绝，则选取下一套 */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(ulBitOPApnInfo,pstApnInfo))
    {
        return NAS_ESM_FAILURE;
    }
    return NAS_ESM_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_IsCurrentApnExitRej50InfoAndSamePdnType
 Description     : 判断当前被拒绝的PDN是否在被拒列表中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-04  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsCurrentApnHas50Rej
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
)
{
    ESM_EMM_PLMN_ID_STRU                stCurrentCampInfo;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRejInfo = VOS_NULL_PTR;

    NAS_ESM_MEM_SET_S(  &stCurrentCampInfo,
                        sizeof(ESM_EMM_PLMN_ID_STRU),
                        0,
                        sizeof(ESM_EMM_PLMN_ID_STRU));

    pstPdnRejInfo = pg_stNasEsmEntity->pstPdnRej50Info;

    NAS_EMM_GetCurrentCampInfo(&stCurrentCampInfo);

    /* 如果被禁列表不为空，则遍历链表，查看该APN和PLMN是否已经在列表中存在 */
    while (pstPdnRejInfo)
    {
        if ((NAS_ESM_OP_TRUE == ulBitOpApnInfo)
            &&(NAS_ESM_OP_TRUE == pstPdnRejInfo->bitOpApnInfo))
        {
            /* 先判断APN长度是否相同 */
            if (pstApnInfo->ucApnLen == pstPdnRejInfo->stApnInfo.ucApnLen)
            {
                /* 判断该长度的APN是否相同 */
                if (((NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(pstApnInfo->aucApnName,pstPdnRejInfo->stApnInfo.aucApnName,pstApnInfo->ucApnLen))) &&
                    (enPdnType == pstPdnRejInfo->enPdnType))
                {
                    /* 判断当前驻留的PLMN是否在EPLMN列表中 */
                    if (NAS_ESM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchPlmnList((NAS_MM_PLMN_ID_STRU*)&stCurrentCampInfo, &(pstPdnRejInfo->stEPlmnList)))
                    {
                        return VOS_TRUE;
                    }
                }
            }
        }
        else if ((NAS_ESM_OP_FALSE == ulBitOpApnInfo)
                &&(NAS_ESM_OP_FALSE == pstPdnRejInfo->bitOpApnInfo))
        {
            if ((enPdnType == pstPdnRejInfo->enPdnType)
                && (NAS_ESM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchPlmnList((NAS_MM_PLMN_ID_STRU*)&stCurrentCampInfo, &(pstPdnRejInfo->stEPlmnList))))
            {
                return VOS_TRUE;
            }
        }
        else
        {
            NAS_ESM_INFO_LOG("NAS_ESM_IsCurrentApnHas50Rej: Apn Info is differ");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_IsCurrentApnHas50Rej_ENUM, 1);
        }

        pstPdnRejInfo = pstPdnRejInfo->pstNext;

    }
    return VOS_FALSE;
}
/*****************************************************************************
 Function Name   : NAS_ESM_IsCurrentApnExitRej50InfoAndSamePdnType
 Description     : 判断当前被拒绝的PDN是否在被拒列表中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-04  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsCurrentApnHas51Rej
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
)
{
    ESM_EMM_PLMN_ID_STRU                stCurrentCampInfo;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRejInfo = VOS_NULL_PTR;

    NAS_ESM_MEM_SET_S(&stCurrentCampInfo, sizeof(ESM_EMM_PLMN_ID_STRU), 0, sizeof(ESM_EMM_PLMN_ID_STRU));

    pstPdnRejInfo = pg_stNasEsmEntity->pstPdnRej51Info;

    NAS_EMM_GetCurrentCampInfo(&stCurrentCampInfo);

    /* 如果被禁列表不为空，则遍历链表，查看该APN和PLMN是否已经在列表中存在 */
    while (pstPdnRejInfo)
    {
        if ((NAS_ESM_OP_TRUE == ulBitOpApnInfo)
            && (NAS_ESM_OP_TRUE == pstPdnRejInfo->bitOpApnInfo))
        {
            /* 先判断APN长度是否相同 */
            if (pstApnInfo->ucApnLen == pstPdnRejInfo->stApnInfo.ucApnLen)
            {
            NAS_ESM_INFO_LOG1("NAS_ESM_IsCurrentApnHas51Rej: Apn Info is =  ",pstPdnRejInfo->enPdnType);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_IsCurrentApnHas51Rej_ENUM, 1, pstPdnRejInfo->enPdnType);
                /* 判断该长度的APN是否相同 */
                if (((NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(pstApnInfo->aucApnName,pstPdnRejInfo->stApnInfo.aucApnName,pstApnInfo->ucApnLen))) &&
                    (enPdnType == pstPdnRejInfo->enPdnType))
                {
                     NAS_ESM_INFO_LOG1("NAS_ESM_IsCurrentApnHas51Rej: Apn Info is =  ",pstPdnRejInfo->enPdnType);
                     TLPS_PRINT2LAYER_INFO1(NAS_ESM_IsCurrentApnHas51Rej_ENUM, 2, pstPdnRejInfo->enPdnType);
                    /* 判断当前驻留的PLMN是否在EPLMN列表中 */
                    if (NAS_ESM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchPlmnList((NAS_MM_PLMN_ID_STRU*)&stCurrentCampInfo, &(pstPdnRejInfo->stEPlmnList)))
                    {
                        return VOS_TRUE;
                    }
                }
            }
        }
        else if ((NAS_ESM_OP_FALSE == ulBitOpApnInfo)
                && (NAS_ESM_OP_FALSE == pstPdnRejInfo->bitOpApnInfo))
        {
            if ((enPdnType == pstPdnRejInfo->enPdnType)
                && (NAS_ESM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchPlmnList((NAS_MM_PLMN_ID_STRU*)&stCurrentCampInfo, &(pstPdnRejInfo->stEPlmnList))))
            {
                return VOS_TRUE;
            }
        }
        else
        {
            NAS_ESM_INFO_LOG("NAS_ESM_IsCurrentApnHas51Rej: Apn Info is differ");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_IsCurrentApnHas51Rej_ENUM, 3);
        }

        pstPdnRejInfo = pstPdnRejInfo->pstNext;

    }
    return VOS_FALSE;
}
/*****************************************************************************
 Function Name   : NAS_ESM_IsCurrentApnExitRej50InfoAndSamePdnType
 Description     : 判断当前被拒绝的PDN是否在被拒列表中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-04  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsCurrentApnHas66Rej
(
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
)
{
    ESM_EMM_PLMN_ID_STRU                stCurrentCampInfo;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRejInfo    = VOS_NULL_PTR;

    NAS_ESM_MEM_SET_S(&stCurrentCampInfo, sizeof(ESM_EMM_PLMN_ID_STRU), 0, sizeof(ESM_EMM_PLMN_ID_STRU));

    pstPdnRejInfo = pg_stNasEsmEntity->pstPdnRej66Info;

    NAS_EMM_GetCurrentCampInfo(&stCurrentCampInfo);

    /* 如果被禁列表不为空，则遍历链表，查看该APN和PLMN是否已经在列表中存在 */
    while (pstPdnRejInfo)
    {
        if ((NAS_ESM_OP_TRUE == ulBitOpApnInfo)
            && (NAS_ESM_OP_TRUE == pstPdnRejInfo->bitOpApnInfo))
        {
            /* 先判断APN长度是否相同 */
            if (pstApnInfo->ucApnLen == pstPdnRejInfo->stApnInfo.ucApnLen)
            {
                /* 判断该长度的APN是否相同 */
                if ((NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(pstApnInfo->aucApnName,pstPdnRejInfo->stApnInfo.aucApnName,pstApnInfo->ucApnLen)))
                {
                    /* 判断当前驻留的PLMN是否在EPLMN列表中 */
                    if (NAS_ESM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchPlmnList((NAS_MM_PLMN_ID_STRU*)&stCurrentCampInfo, &(pstPdnRejInfo->stEPlmnList)))
                    {
                        return VOS_TRUE;
                    }
                }
            }
        }
        else if ((NAS_ESM_OP_FALSE == ulBitOpApnInfo)
                && (NAS_ESM_OP_FALSE == pstPdnRejInfo->bitOpApnInfo))
        {
            /* 判断当前驻留的PLMN是否在EPLMN列表中 */
            if (NAS_ESM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchPlmnList((NAS_MM_PLMN_ID_STRU*)&stCurrentCampInfo, &(pstPdnRejInfo->stEPlmnList)))
            {
                return VOS_TRUE;
            }

        }
        else
        {
            NAS_ESM_INFO_LOG("NAS_ESM_IsCurrentApnHas66Rej: Apn Info is differ");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_IsCurrentApnHas66Rej_ENUM, 1);
        }

        pstPdnRejInfo = pstPdnRejInfo->pstNext;

    }
    return VOS_FALSE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ReadUsimRpmPdpPara
 Description     : 读USIM卡中RPM参数的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT8                   读取结果
 History         :
    1.sunjitan 00193151    2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_ReadUsimBackOffRpmPdpPara(VOS_VOID)
{
    VOS_CHAR                         *cPathStr;
    VOS_UINT8                        ucRecordNum;
    USIMM_FILEPATH_INFO_STRU         stGetFilePath = {0};

    /*利用USIM提供的接口，将FILE ID转换为文件路径*/
    /*检测转换是否成功*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(USIMM_ATTUSIM_EFPRMPARA_ID, &cPathStr))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ReadUsimBackOffRpmPdpPara: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ReadUsimBackOffRpmPdpPara_ENUM, ESM_CALL_API_FAIL);
        return NAS_ESM_FAILURE;
    }
    stGetFilePath.ulPathLen = VOS_StrLen(cPathStr);

    NAS_ESM_MEM_CPY_S(  stGetFilePath.acPath,
                        sizeof(stGetFilePath.acPath),
                        cPathStr,
                        stGetFilePath.ulPathLen);

    /*读取必选文件*/
    ucRecordNum  = 1;
    return NAS_ESM_SndUsimReadFileReq(USIMM_GUTL_APP, \
                            ucRecordNum, \
                            0, \
                            &stGetFilePath);

}
/*****************************************************************************
 Function Name  : NAS_ESM_SndUsimReadFileReq()
 Description    : 给USIM发送读取文件请求
 Input          : ulAppType         应用类型
                  ucRecordNum
                  ulOpId
                  stGetFilePath     文件路径
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641  2015-02-10   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
)
{
    USIMM_READFILE_REQ_STRU     *pstUsimReadFileReq;

    /*分配空间并检验分配是否成功*/
    pstUsimReadFileReq = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(USIMM_READFILE_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstUsimReadFileReq)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("IMSA_SndUsimReadFileReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndUsimReadFileReq_ENUM, ESM_CALL_API_FAIL);
        return NAS_ESM_FAILURE;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  pstUsimReadFileReq,
                        sizeof(USIMM_READFILE_REQ_STRU),
                        0,
                        sizeof(USIMM_READFILE_REQ_STRU));

    /*填写消息头*/
    /*消息结构体中的SendPara用来存储OpId*/
    NAS_ESM_WRITE_USIM_MSG_HEAD(pstUsimReadFileReq, USIMM_READFILE_REQ, ulAppType, ulOpId);

    /*填写消息内容*/
    pstUsimReadFileReq->ucRecordNum = ucRecordNum;
    pstUsimReadFileReq->bNeedReadCache = VOS_TRUE;

    NAS_ESM_MEM_CPY_S(  &(pstUsimReadFileReq->stFilePath),
                        sizeof(USIMM_FILEPATH_INFO_STRU),
                        pstGetFilePath,
                        sizeof(USIMM_FILEPATH_INFO_STRU));

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pstUsimReadFileReq);
    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_DecodeUsimBackOffPara
 Description    : 读USIM中的BackOff算法参数的译码
 Input          : VOS_UINT16           参数长度
 Output         : VOS_UINT8            参数流
 Return Value   : VOS_UINT32           译码结果

 History        :
      1.sunjitan 00193151    2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_DecodeUsimBackOffPara
(
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucContent,
    NAS_BACKOFF_INIT_INFO_STRU         *pstInitPara
)
{
    /* 卡文件长度过短，取不到有效Fx值 */
    if(2 >= usLen)
    {
        pstInitPara->bitOpSimFxFlag = NAS_ESM_OP_FALSE;
        return;
    }

    /* 至少有一个参数有效 */
    pstInitPara->bitOpSimFxFlag = NAS_ESM_OP_TRUE;
    pstInitPara->ucSimFxIgnore  = NAS_ESM_BACKOFF_IGNORE_FX_DEFAULT_VALUE;
    pstInitPara->ucSimFxPerm    = NAS_ESM_BACKOFF_PERM_FX_DEFAULT_VALUE;
    pstInitPara->ucSimFxTemp    = NAS_ESM_BACKOFF_TEMP_FX_DEFAULT_VALUE;

    /* 只有3个字节 */
    if(3 >= usLen)
    {
        pstInitPara->ucSimFxIgnore = pucContent[2];
        return;
    }

    /* 只有4个字节 */
    if(4 >= usLen)
    {
        pstInitPara->ucSimFxIgnore = pucContent[2];
        pstInitPara->ucSimFxPerm   = pucContent[3];
        return;
    }

    pstInitPara->ucSimFxIgnore = pucContent[2];
    pstInitPara->ucSimFxPerm   = pucContent[3];
    pstInitPara->ucSimFxTemp   = pucContent[4];

    return;
}
/*****************************************************************************
 Function Name  : NAS_ESM_ProcReadIsimFileResult()
 Description    : ESM读卡文件，USIM回复消息处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641    2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ProcReadIsimFileResult(VOS_VOID *pRcvMsg)
{
    NAS_BACKOFF_INIT_INFO_STRU           stInitPara;
    USIMM_READFILE_CNF_STRU             *pstUsimCnf;
    USIMM_DEF_FILEID_ENUM_UINT32         enDefFileID;
    VOS_UINT32                           ulresult;

    pstUsimCnf = (USIMM_READFILE_CNF_STRU *)pRcvMsg;
    /* 调用USIM提供的接口，将文件路径转换为FileID */
    ulresult = USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstUsimCnf->stFilePath.ulPathLen, pstUsimCnf->stFilePath.acPath, &enDefFileID);
    if(VOS_OK != ulresult)
    {
        /* 如果转换失败，表示没有对应的FileID */
        NAS_ESM_WARN_LOG("NAS_ESM_ProcReadIsimFileResult: USIMM_ChangePathToDefFileID err");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcReadIsimFileResult_ENUM, ESM_CALL_API_FAIL);
        return;
    }
    switch(enDefFileID)
    {
        case USIMM_ATTUSIM_EFPRMPARA_ID:

            NAS_ESM_MEM_SET_S(  &stInitPara,
                                sizeof(NAS_BACKOFF_INIT_INFO_STRU),
                                0,
                                sizeof(NAS_BACKOFF_INIT_INFO_STRU));

            pstUsimCnf          = (USIMM_READFILE_CNF_STRU*)pRcvMsg;
            NAS_ESM_TimerStop(0, TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF);

            /* 读卡成功，译码参数后初始化BackOff算法 */
            if (NAS_ESM_SUCCESS == pstUsimCnf->stCmdResult.ulResult)
            {
                NAS_ESM_DecodeUsimBackOffPara(pstUsimCnf->usEfLen, pstUsimCnf->aucEf, &stInitPara);
            }
            else
            {
            /* 读卡失败 */
                stInitPara.bitOpSimFxFlag = NAS_ESM_OP_FALSE;
            }

            NAS_BACKOFF_OperateInit(&stInitPara);
            break;
        default:
            break;
    }
    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_UsimMsgDistr()
 Description    : SM模块USIM消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-01-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_UsimMsgDistr(VOS_VOID *pRcvMsg)
{
    PS_MSG_HEADER_STRU                  *pHeader = VOS_NULL_PTR;
    pHeader = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pHeader->ulMsgName)
    {
        case USIMM_READFILE_CNF:
            NAS_ESM_ProcReadIsimFileResult(pRcvMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_IsWaitBackOffUsimCnfTimerRunning
 Description    : 判断等待读USIM卡定时器是否在运行
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-01-15  Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_ESM_IsWaitBackOffUsimCnfTimerRunning(VOS_VOID)
{
    NAS_ESM_TIMER_STRU                 *pstTimerInfo = VOS_NULL_PTR;

    pstTimerInfo = NAS_ESM_GetTimer(0, TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF);

    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}



/*****************************************************************************
 Function Name  : NAS_ESM_QueryPdnDisconnNumInStateTbl
 Description    : 查询动态表中正在去激活的PDN连接数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.sunjitan 00193151    2015-03-15  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_QueryPdnDisconnNumInStateTbl(VOS_VOID)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    VOS_UINT32                          ulStateTblIndex  = 0;
    VOS_UINT32                          ulPdnDisconnNum  = 0;

    /* 查询一下动态表中，因上层触发的去激活缺省承载的PDN连接数 */
    for(ulStateTblIndex = 0; ulStateTblIndex < NAS_ESM_MAX_STATETBL_NUM; ulStateTblIndex++)
    {
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        if((NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
            &&(ID_APP_ESM_PDP_RELEASE_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
            &&(NAS_ESM_BEARER_TYPE_DEFAULT == pstStateAddr->enBearerCntxtType))
        {
            ulPdnDisconnNum++;
        }
    }

    NAS_ESM_LOG1("NAS_ESM_QueryPdnDisconnNumInStateTbl: ulPdnDisconnNum = ",ulPdnDisconnNum);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_QueryPdnDisconnNumInStateTbl_ENUM, 1, ulPdnDisconnNum);

    return ulPdnDisconnNum;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SecuMemCpy
 Description     : 安全memcpy
 Input           : VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc,
                   VOS_UINT32  ulLength, VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID
 Output          : None
 Return          : VOS_INT32

 History         :
    1.z00297373    2015-12-28  Draft Enact
*****************************************************************************/
VOS_INT32 NAS_ESM_SecuMemCpy
(
    VOS_VOID            * pDst,
    VOS_UINT32          ulMaxBuffer,
    const VOS_VOID      * pSrc,
    VOS_UINT32          ulLength,
    VOS_UINT32          ulLineNO,
    VOS_UINT32          ulFileID
)
{
    /*如果源地址和目的地址重叠，需改用TLPS_MEM_MOVE_S，否则安全拷贝失败 */
    if(((pSrc > pDst) && ((VOS_UINT8 *)pSrc <= ((VOS_UINT8 *)pDst + ulMaxBuffer)))
        ||((pDst> pSrc) && ((VOS_UINT8 *)pDst <= ((VOS_UINT8 *)pSrc + ulLength)))
        || (pSrc == pDst))
    {
        return TLPS_MEM_MOVE_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
    else
    {
        return TLPS_MEM_CPY_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmPublic.c */

