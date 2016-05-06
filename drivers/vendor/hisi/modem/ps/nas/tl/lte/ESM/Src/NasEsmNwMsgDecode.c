/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgDecode.c
    Description : EMM发给SM的网侧消息的公共处理
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.杨茜惠 00135146    2008-12-18  Modify  BA8D00752
     3.杨茜惠 00135146    2008-12-24  Modify  BA8D00795
     4.孙兵 49683         2009-01-06  Modify  BA8D00870
     5.杨茜惠 00135146    2009-03-06  Modify  BA8D01127
     6.李洪00150010       2009-08-03  Modify  BJ9D01608
     7.李洪00150010       2009-08-05  Modify  BJ9D01627
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"
#include    "NasLmmPubMOm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGDECODE_C
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
NAS_ESM_MSG_IE_STRU                     g_ActDefltEpsbReq[] = {
{NAS_ESM_MSG_EPS_QOS_IEI,    0x00, NAS_MSG_FORMAT_LV,  1, 2, 14, NAS_ESM_DecodeNwSdfQosValue   },
{NAS_ESM_MSG_APN_IEI,        0x00, NAS_MSG_FORMAT_LV,  1, 2, 101,NAS_ESM_DecodeNwAPNValue      },
{NAS_ESM_MSG_PDN_IEI,        0x00, NAS_MSG_FORMAT_LV,  1, 6, 14, NAS_ESM_DecodeNwPDNValue      },
{NAS_ESM_MSG_TI_IEI,         0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 4 , NAS_ESM_DecodeTransactionId   },
{NAS_ESM_MSG_NQOS_IEI,       0xFF, NAS_MSG_FORMAT_TLV, 2, 14,22, NAS_ESM_DecodeNegotiatedQos   },
{NAS_ESM_MSG_NLS_IEI,        0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeLlcSapi         },
{NAS_ESM_MSG_RADIO_PRIO_IEI, 0xF0, NAS_MSG_FORMAT_TV,  1, 1, 1,  NAS_ESM_DecodeRadioPriority   },
{NAS_ESM_MSG_PFI_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 3,  NAS_ESM_DecodePacketFlowId    },
{NAS_ESM_MSG_APN_AMBR_IEI,   0xFF, NAS_MSG_FORMAT_TLV, 2, 4, 8,  NAS_ESM_DecodeNwApnAmbrValue  },
{NAS_ESM_MSG_ESM_CAU_IEI,    0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,NAS_ESM_DecodeNwPco           }
};
#define  ACT_DEFLT_EPSB_REQ_MSG_IE_NUM  (sizeof(g_ActDefltEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_ActDedictEpsbReq[] = {
{NAS_ESM_MSG_EPS_QOS_IEI,    0x00, NAS_MSG_FORMAT_LV,  1, 2, 14, NAS_ESM_DecodeNwSdfQosValue   },
{NAS_ESM_MSG_TFT_IEI,        0xFF, NAS_MSG_FORMAT_LV,  1, 2, 256,NAS_ESM_DecodeNwTftValue      },
{NAS_ESM_MSG_TI_IEI,         0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 4,  NAS_ESM_DecodeTransactionId   },
{NAS_ESM_MSG_NQOS_IEI,       0xFF, NAS_MSG_FORMAT_TLV, 2,14, 22, NAS_ESM_DecodeNegotiatedQos   },
{NAS_ESM_MSG_NLS_IEI,        0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeLlcSapi         },
{NAS_ESM_MSG_RADIO_PRIO_IEI, 0xF0, NAS_MSG_FORMAT_TV,  1, 1, 1,  NAS_ESM_DecodeRadioPriority   },
{NAS_ESM_MSG_PFI_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 3,  NAS_ESM_DecodePacketFlowId    },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR                  }
};
#define  ACT_DEDICT_EPSB_REQ_MSG_IE_NUM (sizeof(g_ActDedictEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))


NAS_ESM_MSG_IE_STRU                     g_ModEpsbReq[] = {
{NAS_ESM_MSG_EPS_QOS_IEI,    0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 15, NAS_ESM_DecodeNwSdfQosValue   },
{NAS_ESM_MSG_TFT_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 257,NAS_ESM_DecodeNwTftValue      },
{NAS_ESM_MSG_NQOS_IEI,       0xFF, NAS_MSG_FORMAT_TLV, 2,14, 22, NAS_ESM_DecodeNegotiatedQos   },
{NAS_ESM_MSG_NLS_IEI,        0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeLlcSapi         },
{NAS_ESM_MSG_RADIO_PRIO_IEI, 0xF0, NAS_MSG_FORMAT_TV,  1, 1, 1,  NAS_ESM_DecodeRadioPriority   },
{NAS_ESM_MSG_PFI_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 3,  NAS_ESM_DecodePacketFlowId    },
{NAS_ESM_MSG_APN_AMBR_IEI,   0xFF, NAS_MSG_FORMAT_TLV, 2, 4, 8,  NAS_ESM_DecodeNwApnAmbrValue  },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,NAS_ESM_DecodeNwPco           }
};
#define  MOD_EPSB_REQ_MSG_IE_NUM (sizeof(g_ModEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_BearerResAllocRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  BEARER_RES_ALLOC_REJ_MSG_IE_NUM (sizeof(g_BearerResAllocRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_BearerResModRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  BEARER_RES_MOD_REJ_MSG_IE_NUM (sizeof(g_BearerResModRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_DeactEpsbReq[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  DEACT_EPSB_REQ_MSG_IE_NUM  (sizeof(g_DeactEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_PdnConRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  PDN_CON_REJ_MSG_IE_NUM  (sizeof(g_PdnConRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_PdnDisConRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  PDN_DISCON_REJ_MSG_IE_NUM (sizeof(g_PdnDisConRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_EsmStatus[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        }
};
#define  ESM_STATUS_MSG_IE_NUM  (sizeof(g_EsmStatus)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_EsmNotification[] = {
{NAS_ESM_MSG_NI_IEI,         0x00, NAS_MSG_FORMAT_LV,  1, 2, 2,  NAS_ESM_DecodeNotificationIndicator}
};
#define  ESM_NOTIFICATION_MSG_IE_NUM  (sizeof(g_EsmNotification)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_DECODE_TABLE_STRU               g_EsmDecodeTable[] = {
{NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ,  0, ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REQ,
 ACT_DEFLT_EPSB_REQ_MSG_IE_NUM,                      g_ActDefltEpsbReq                      },

{NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ,1, ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REQ,
 ACT_DEDICT_EPSB_REQ_MSG_IE_NUM,                     g_ActDedictEpsbReq                     },

{NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ,        0, ESM_MOD_EPS_BEARER_CNTXT_REQ,
 MOD_EPSB_REQ_MSG_IE_NUM,                            g_ModEpsbReq                           },

{NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_REQ,      0, ESM_DEACT_EPS_BEARER_CNTXT_REQ,
 DEACT_EPSB_REQ_MSG_IE_NUM,                          g_DeactEpsbReq                         },

{NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REJ,                 0, ESM_PDN_CONNECT_REJ,
 PDN_CON_REJ_MSG_IE_NUM,                             g_PdnConRej                            },

{NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REJ,              0, ESM_PDN_DISCONNECT_REJ,
 PDN_DISCON_REJ_MSG_IE_NUM,                          g_PdnDisConRej                         },

{NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REJ,            0, ESM_BEARER_RESOUCE_ALLOC_REJ,
 BEARER_RES_ALLOC_REJ_MSG_IE_NUM,                    g_BearerResAllocRej                    },

{NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REJ,              0, ESM_BEARER_RESOUCE_MOD_REJ,
 BEARER_RES_MOD_REJ_MSG_IE_NUM,                      g_BearerResModRej                      },

{NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ,             0, ESM_INFO_REQ,
 0,                                                  VOS_NULL_PTR                           },

{NAS_ESMCN_MSG_TYPE_ESM_STATUS,                      0, ESM_STUS_MT,
 ESM_STATUS_MSG_IE_NUM,                              g_EsmStatus                            },

{NAS_ESMCN_MSG_TYPE_ESM_NOTIFICATION,                0, ESM_NOTIFICATION_MT,
 ESM_NOTIFICATION_MSG_IE_NUM,                        g_EsmNotification                      }
};

#define g_EsmDecodeTableSize (sizeof(g_EsmDecodeTable)/sizeof(NAS_ESM_DECODE_TABLE_STRU))

NAS_ESM_DECODE_QOSRATE_TABLE_STRU       g_EsmDecodeQosRateTable[] =
{
    {NAS_ESM_QOS_OFFSET_ULMAXRATE,                  NAS_ESM_SdfQosUlMaxRateTran},
    {NAS_ESM_QOS_OFFSET_DLMAXRATE,                  NAS_ESM_SdfQosDlMaxRateTran},
    {NAS_ESM_QOS_OFFSET_ULGMAXRATE,                 NAS_ESM_SdfQosUlGMaxRateTran},
    {NAS_ESM_QOS_OFFSET_DLGMAXRATE,                 NAS_ESM_SdfQosDlGMaxRateTran},
    {NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT,              NAS_ESM_SdfQosUlMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT,              NAS_ESM_SdfQosDlMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT,             NAS_ESM_SdfQosUlGMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT,             NAS_ESM_SdfQosDlGMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT_2,            NAS_ESM_SdfQosUlMaxRateExt2Tran},
    {NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT_2,            NAS_ESM_SdfQosDlMaxRateExt2Tran},
    {NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT_2,           NAS_ESM_SdfQosUlGMaxRateExt2Tran},
    {NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT_2,           NAS_ESM_SdfQosDlGMaxRateExt2Tran}
};
#define g_EsmDecodeQosRateTableSize (sizeof(g_EsmDecodeQosRateTable)/sizeof(NAS_ESM_DECODE_QOSRATE_TABLE_STRU))

NAS_ESM_PF_CONPONET_TYPE_LEN_TABLE_STRU       g_EsmPFComponentTypeLenTable[] =
{
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_ADDR,                   8},
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_ADDR,                  32},
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_LOCAL_ADDR,             8},
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_LOCAL_ADDR,            17},
    {NAS_ESM_TFT_PF_COP_TYPE_PROTOCOL_ID,                 1},
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_LOCAL_PORT,           2},
    {NAS_ESM_TFT_PF_COP_TYPE_LOCAL_PORT_RANGE,            4},
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_REMOTE_PORT,          2},
    {NAS_ESM_TFT_PF_COP_TYPE_REMOTE_PORT_RANGE,           4},
    {NAS_ESM_TFT_PF_COP_TYPE_SPI,                         4},
    {NAS_ESM_TFT_PF_COP_TYPE_TOS,                         2},
    {NAS_ESM_TFT_PF_COP_TYPE_FLOW_LABLE,                  3}
};
#define g_EsmPFComponentTypeLenTableSize (sizeof(g_EsmPFComponentTypeLenTable)/sizeof(NAS_ESM_PF_CONPONET_TYPE_LEN_TABLE_STRU))
/*****************************************************************************
 Global Variable Name   : g_EsmDecodeAddFilterTftTable[]
 Description            : ADD TFT PF的component相关译码表定义
 History                :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
NAS_ESM_DECODE_ADD_FILTER_TFT_TABLE_STRU  g_EsmDecodeAddFilterTftTable[] =
{
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_LOCAL_ADDR    , NAS_ESM_TFT_DecodePfCopTypeIpv4LocalAddr    },
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_LOCAL_ADDR    , NAS_ESM_TFT_DecodePfCopTypeIpv6LocalAddr    },
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_ADDR          , NAS_ESM_TFT_DecodePfCopTypeIpv4Addr         },
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_ADDR          , NAS_ESM_TFT_DecodePfCopTypeIpv6Addr         },
    {NAS_ESM_TFT_PF_COP_TYPE_PROTOCOL_ID        , NAS_ESM_TFT_DecodePfCopTypeProtocolId       },
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_LOCAL_PORT  , NAS_ESM_TFT_DecodePfCopTypeSingleLocalPort  },
    {NAS_ESM_TFT_PF_COP_TYPE_LOCAL_PORT_RANGE   , NAS_ESM_TFT_DecodePfCopTypeLocalPortRange   },
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_REMOTE_PORT , NAS_ESM_TFT_DecodePfCopTypeSingleRemotePort },
    {NAS_ESM_TFT_PF_COP_TYPE_REMOTE_PORT_RANGE  , NAS_ESM_TFT_DecodePfCopTypeRemotePortRange  },
    {NAS_ESM_TFT_PF_COP_TYPE_SPI                , NAS_ESM_TFT_DecodePfCopTypeSpi              },
    {NAS_ESM_TFT_PF_COP_TYPE_TOS                , NAS_ESM_TFT_DecodePfCopTypeTos              },
    {NAS_ESM_TFT_PF_COP_TYPE_FLOW_LABLE         , NAS_ESM_TFT_DecodePfCopTypeFlowLable        }
};

const VOS_UINT32 g_EsmDecodeAddFilterTftTableSize =
              (sizeof(g_EsmDecodeAddFilterTftTable)/sizeof(NAS_ESM_DECODE_ADD_FILTER_TFT_TABLE_STRU));



#if (VOS_OS_VER == VOS_WIN32)
NAS_ESM_OM_CN_MSG_IE_PRINT_STR_STRU  g_EsmDecodeFailIePrintTable[] =
{
    {NAS_ESM_CN_MSG_PDN_IE              , "NAS_ESM_CN_MSG_PDN_IE"},
    {NAS_ESM_CN_MSG_TFT_IE              , "NAS_ESM_CN_MSG_TFT_IE"},
    {NAS_ESM_CN_MSG_EPS_QOS_IE          , "NAS_ESM_CN_MSG_EPS_QOS_IE"},
    {NAS_ESM_CN_MSG_APN_IE              , "NAS_ESM_CN_MSG_APN_IE"},
    {NAS_ESM_CN_MSG_PCO_IE              , "NAS_ESM_CN_MSG_PCO_IE"},
    {NAS_ESM_CN_MSG_ESM_CAUSE_IE        , "NAS_ESM_CN_MSG_ESM_CAUSE_IE"},
    {NAS_ESM_CN_MSG_NQOS_IE             , "NAS_ESM_CN_MSG_NQOS_IE"},
    {NAS_ESM_CN_MSG_TI_IE               , "NAS_ESM_CN_MSG_TI_IE"},
    {NAS_ESM_CN_MSG_NLS_IE              , "NAS_ESM_CN_MSG_NLS_IE"},
    {NAS_ESM_CN_MSG_PFI_IE              , "NAS_ESM_CN_MSG_PFI_IE"},
    {NAS_ESM_CN_MSG_RADIO_PRIO_IE       , "NAS_ESM_CN_MSG_RADIO_PRIO_IE"},
    {NAS_ESM_CN_MSG_APN_AMBR_IE         , "NAS_ESM_CN_MSG_APN_AMBR_IE"},
    {NAS_ESM_CN_MSG_EPSBID_IE           , "NAS_ESM_CN_MSG_EPSBID_IE"},
    {NAS_ESM_CN_MSG_PTI_IE              , "NAS_ESM_CN_MSG_PTI_IE"},
    {NAS_ESM_CN_MSG_LINKED_EPSBID_IE    , "NAS_ESM_CN_MSG_LINKED_EPSBID_IE"},
    {NAS_ESM_CN_MSG_MSG_TYPE_IE         , "NAS_ESM_CN_MSG_MSG_TYPE_IE"},
    {NAS_ESM_CN_MSG_IE_NOIE             , "NAS_ESM_CN_MSG_IE_NOIE"},
    {NAS_ESM_CN_MSG_MANDAN_IE           , "NAS_ESM_CN_MSG_MANDAN_IE"},
    {NAS_ESM_CN_MSG_OPTION_IE           , "NAS_ESM_CN_MSG_OPTION_IE"}
};

const VOS_UINT32 g_EsmDecodeFailIePrintTableSize =
              (sizeof(g_EsmDecodeFailIePrintTable)/sizeof(NAS_ESM_OM_CN_MSG_IE_PRINT_STR_STRU));

NAS_ESM_OM_DECODE_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU  g_EsmDecodeFailCausePrintTable[] =
{
    {ESM_DECODE_CN_MSG_IE_LEN_INVALID                       , "ESM_DECODE_CN_MSG_IE_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IE_TYPE_INVALID                      , "ESM_DECODE_CN_MSG_IE_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_PD_INVALID                           , "ESM_DECODE_CN_MSG_PD_INVALID"},
    {ESM_DECODE_CN_MSG_MSG_TYPE_INVALID                     , "ESM_DECODE_CN_MSG_MSG_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_NOT_PARA_LIST_ID                     , "ESM_DECODE_CN_MSG_NOT_PARA_LIST_ID"},
    {ESM_DECODE_CN_MSG_TAD_TYPE_INVALID                     , "ESM_DECODE_CN_MSG_TAD_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_PF_NUM_INVALID                       , "ESM_DECODE_CN_MSG_PF_NUM_INVALID"},
    {ESM_DECODE_CN_MSG_SAME_PF_ID                           , "ESM_DECODE_CN_MSG_SAME_PF_ID"},
    {ESM_DECODE_CN_MSG_SAME_PF_PRECEDENCE                   , "ESM_DECODE_CN_MSG_SAME_PF_PRECEDENCE"},
    {ESM_DECODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST    , "ESM_DECODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST"},
    {ESM_DECODE_CN_MSG_IP_LEN_INVALID                       , "ESM_DECODE_CN_MSG_IP_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_BCM_TYPE_INVALID                     , "ESM_DECODE_CN_MSG_BCM_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID          , "ESM_DECODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID"},
    {ESM_DECODE_CN_MSG_IP_TYPE_INVALID                      , "ESM_DECODE_CN_MSG_IP_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_QOS_RATE_0                           , "ESM_DECODE_CN_MSG_QOS_RATE_0"},
    {ESM_DECODE_CN_MSG_PF_ITEM_TYPE_INVALID                 , "ESM_DECODE_CN_MSG_PF_ITEM_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID                , "ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID"},
    {ESM_DECODE_CN_MSG_PARA_LIST_ID_INVALID                 , "ESM_DECODE_CN_MSG_PARA_LIST_ID_INVALID"},
    {ESM_DECODE_CN_MSG_IPV4_LEN_INVALID                     , "ESM_DECODE_CN_MSG_IPV4_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPV6_LEN_INVALID                     , "ESM_DECODE_CN_MSG_IPV6_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_BCM_LEN_INVALID                      , "ESM_DECODE_CN_MSG_BCM_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_LEN_INVALID                     , "ESM_DECODE_CN_MSG_IPCP_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID             , "ESM_DECODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID             , "ESM_DECODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_OTHER_LEN_INVALID               , "ESM_DECODE_CN_MSG_IPCP_OTHER_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_LEN_INVALID                          , "ESM_DECODE_CN_MSG_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_ESM_MSG_PD_INVALID                   , "ESM_DECODE_CN_MSG_ESM_MSG_PD_INVALID"},
    {ESM_DECODE_CN_MSG_ESM_MSG_TYPE_INVALID                 , "ESM_DECODE_CN_MSG_ESM_MSG_TYPE_INVALID"}
};

const VOS_UINT32 g_EsmDecodeFailCausePrintTableSize =
              (sizeof(g_EsmDecodeFailCausePrintTable)/sizeof(NAS_ESM_OM_DECODE_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU));
#endif






/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ESM_CheckIeLen
 Description     : 消息长度检查，并返回信元的长度
 Input           :NAS_ESM_MSG_IE_STRU                *pstEsmMsgIe
                 VOS_UINT16                          usIeLen
 Output          : VOS_UINT16                          *pusIeValueLen
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2010-7-7  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CheckIeLen
(
    const NAS_ESM_MSG_IE_STRU          *pstEsmMsgIe,
    VOS_UINT16                          usIeLen,
    VOS_UINT16                         *pusIeValueLen
)
{
    VOS_UINT16                          usFormatLen = NAS_ESM_NULL;
    VOS_UINT16                          usMinLen = pstEsmMsgIe->usMinLen;
    VOS_UINT16                          usMaxLen = pstEsmMsgIe->usMaxLen;

    usFormatLen = pstEsmMsgIe->ucFormatLen;

    /* 对于只有半字Type信元 ,需要加1 */
    if (0xf0 == pstEsmMsgIe->ucMask)
    {
        *pusIeValueLen = 1;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* 对于没有长度指示的信元按照协议规定长度填写*/
    if ((NAS_MSG_FORMAT_TV == pstEsmMsgIe->enType)
     || (NAS_MSG_FORMAT_V == pstEsmMsgIe->enType))
    {
        *pusIeValueLen = usMinLen - usFormatLen;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    *pusIeValueLen = usIeLen;

    /* 对于含有长度指示的信元按照协议规定长度进行检查*/
    if ((usMinLen > (usIeLen + usFormatLen)) || (usMaxLen < (usIeLen + usFormatLen)))
    {
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_DecodeMandatoryIei
 Description     : 必选信元解码
 Input           :NAS_ESM_MSG_IE_STRU                 *pstEsmMsgIe
                  VOS_UINT8                             *pucRcvNwMsg
 Output          :
                  VOS_UINT16                          *pulSum
                  NAS_ESM_NW_MSG_STRU                 *pstNwMsgRecord
 Return          : NAS_ESM_CAUSE_ENUM_UINT8
 History         :
    1.luojian 00107747      2010-7-7  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeMandatoryIei
(
    const NAS_ESM_MSG_IE_STRU           *pstEsmMsgIe,
    VOS_UINT16                          *pulSum,
    const VOS_UINT8                     *pucRcvNwMsg,
    VOS_UINT32                           ulRemainLen,
    NAS_ESM_NW_MSG_STRU                 *pstNwMsgRecord
)
{
    VOS_UINT16                          usIeValueLen = 0;
    NAS_ESM_CAUSE_ENUM_UINT8            enRst;

    /* 必选信元解码是必须的 */
    if (VOS_NULL_PTR == pstEsmMsgIe->pfDecodeFun)
    {
        return NAS_ESM_CAUSE_FEATURE_NOT_SUPPORTED;
    }

    /* 校验信元长度是否合法，并返回IE Value长度 */
    if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckIeLen(pstEsmMsgIe,
                                                    pucRcvNwMsg[*pulSum],
                                                    &usIeValueLen))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_MANDAN_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
        return NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION;
    }

    /* 剩余未译码长度小于要译码的信元长度，返回失败 */
    if ((usIeValueLen + pstEsmMsgIe->ucFormatLen) > ulRemainLen)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_MANDAN_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    if (NAS_MSG_FORMAT_LV == pstEsmMsgIe->enType)
    {
        /* 跳过L */
        *pulSum = *pulSum + 1;
    }

    /* 解码具体信元 */
    enRst = pstEsmMsgIe->pfDecodeFun(usIeValueLen,&pucRcvNwMsg[*pulSum],pstNwMsgRecord);

    if (NAS_ESM_CAUSE_SUCCESS == enRst)
    {
        *pulSum += usIeValueLen;
    }

    return enRst;
}


/*****************************************************************************
 Function Name   : NAS_ESM_DecodeOptinalIei
 Description     : 可选信元解码
 Input           :NAS_ESM_MSG_IE_STRU                 *pstOptionalIe
                VOS_UINT16                          *pulSum
                VOS_UINT8                           *pucOptinalMsg
                NAS_ESM_NW_MSG_STRU                 *pstNwMsgRecord
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.luojian 00107747      2010-7-7  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeOptinalIei
(
    const NAS_ESM_MSG_IE_STRU           *pstEsmMsgIe,
    VOS_UINT16                          *pulSum,
    const VOS_UINT8                     *pucRcvNwMsg,
    VOS_UINT32                           ulRemainLen,
    NAS_ESM_NW_MSG_STRU                 *pstNwMsgRecord
)
{
    VOS_UINT16                          usIeValueLen = 0;
    VOS_UINT16                          usIeLen      = 0;
    NAS_ESM_CAUSE_ENUM_UINT8            enRst;

    if (pstEsmMsgIe->ucIei != (pucRcvNwMsg[*pulSum] & pstEsmMsgIe->ucMask))
    {
        /* 忽略此信元 */
        return NAS_ESM_CAUSE_ERROR;
    }
    else
    {
        /* 普通掩码跳过Type字段 */
        if (0xF0 != pstEsmMsgIe->ucMask)
        {
            *pulSum = *pulSum + 1;
        }
    }

    /* 校验信元长度是否合法，并返回IE Value长度 */
    if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckIeLen(pstEsmMsgIe,
                                                    pucRcvNwMsg[*pulSum],
                                                    &usIeValueLen))
    {
        *pulSum = *pulSum + 1 + usIeValueLen;
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_OPTION_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
         return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    if (NAS_MSG_FORMAT_TLV == pstEsmMsgIe->enType)
    {
        /* 跳过L */
        *pulSum = *pulSum + 1;
    }

    /* 计算整个信元长度(如果有T和L，也包括T和L的长度) */
    if (0xF0 != pstEsmMsgIe->ucMask)
    {
        usIeLen = usIeValueLen + pstEsmMsgIe->ucFormatLen;
    }
    else
    {
        usIeLen = usIeValueLen;
    }

    /* 剩余未译码长度小于要译码的信元长度，返回失败 */
    if (usIeLen > ulRemainLen)
    {
        *pulSum  += usIeValueLen;
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_OPTION_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /* 不需要的可选信元可以直接跳过 */
    if (VOS_NULL_PTR == pstEsmMsgIe->pfDecodeFun)
    {
        *pulSum  += usIeValueLen;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* 解码具体信元 */
    enRst = pstEsmMsgIe->pfDecodeFun(usIeValueLen,&pucRcvNwMsg[*pulSum],pstNwMsgRecord);

    /*if (NAS_ESM_CAUSE_SUCCESS == enRst)
    {
        *pulSum += usIeValueLen;
    }*/
    *pulSum += usIeValueLen;

    return enRst;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNwMsgIe
 Description     : 可选信元解析
 Input           :

    VOS_UINT8                           ucOptinalIeMaxNum
    VOS_UINT32                          ulRemainMsgLen
    VOS_UINT8                           *pucOptinalMsg
    NAS_ESM_MSG_IE_STRU                 *pstOptionalIe

 Output          :
    VOS_UINT32                          *pulDecodeMsgLen
    NAS_ESM_NW_MSG_STRU                 *pstNwMsgRecord
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.luojian 00107747      2010-7-1  Draft Enact
    2.niuxiufan 00181501    2012-7-23 modify 增加网络兼容性,对可选信元解析时忽略顺序
                                             重复信元,只解析第一个

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
NAS_ESM_CAUSE_ENUM_UINT8    NAS_ESM_DecodeNwMsgIei
(
    VOS_UINT8                           ucIeMaxNum,
    VOS_UINT32                          ulRemainMsgLen,
    VOS_UINT32                         *pulDecodeMsgLen,
    const VOS_UINT8                    *pucRcvNwMsg,
    const NAS_ESM_MSG_IE_STRU          *pstEsmMsgIe,
    NAS_ESM_NW_MSG_STRU                *pstNwMsgRecord
)
{
    VOS_UINT16                          ulSum  = NAS_ESM_NULL;
    VOS_UINT8                           ucLoop = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enDecodeRst;

    VOS_UINT32                          ulDecodedIE = NAS_ESM_NULL;    /*记录已经解的信元 */
    VOS_UINT32                          ulDecodingIE = NAS_ESM_BIT_0;  /*记录正在解的信元 */
    VOS_UINT32                          ulTmpPos    = NAS_ESM_BIT_0;
    VOS_UINT16                          usIeValueLen = NAS_ESM_NULL;  /*跳过的信元IEI的长度 */
    VOS_UINT16                          usIeLen      = NAS_ESM_NULL; /*跳过的信元总长度 */

    /* 循环解析必选信元 */
    while ((NAS_ESM_IsMandatoryIei(pstEsmMsgIe[ucLoop].enType)) && (ulRemainMsgLen > ulSum))
    {
        enDecodeRst = NAS_ESM_DecodeMandatoryIei(&pstEsmMsgIe[ucLoop],
                                                 &ulSum,
                                                 pucRcvNwMsg,
                                                 ulRemainMsgLen - ulSum,
                                                 pstNwMsgRecord);

        if (NAS_ESM_CAUSE_SUCCESS != enDecodeRst)
        {
            *pulDecodeMsgLen = ulSum;

            if (NAS_ESM_CAUSE_PROTOCOL_ERROR == enDecodeRst)
            {
                enDecodeRst = NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION;
            }

            return enDecodeRst;
        }

        ucLoop++;
    }

    /* 循环解析可选信元 */
    while (ulRemainMsgLen > ulSum)
    {
        ulDecodingIE = NAS_ESM_BIT_0;
        ulTmpPos    = NAS_ESM_BIT_0;

        for (ucLoop = 0; ucLoop < ucIeMaxNum; ucLoop++)
        {

            /*只要信元已经被解到过,直接跳过信元 */
            if (((ulDecodingIE | ulDecodedIE) == ulDecodedIE)&&
                ((pstEsmMsgIe + ucLoop)->ucIei == (pucRcvNwMsg[ulSum] & (pstEsmMsgIe+ucLoop)->ucMask)))
            {
                /* 校验信元长度是否合法，如果不合法直接返回，停止解码 */
                if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckIeLen(&pstEsmMsgIe[ucLoop],
                                                                pucRcvNwMsg[ulSum + 1],
                                                                &usIeValueLen))
                {
                    *pulDecodeMsgLen = ulSum;
                    return NAS_ESM_SUCCESS;
                }

                /*计算跳过的信元的总长度 */
                usIeLen = (0xF0 != (pstEsmMsgIe+ucLoop)->ucMask)
                                ? (usIeValueLen + (pstEsmMsgIe+ucLoop)->ucFormatLen)
                                : (usIeValueLen);

                /*码流直接平移 */
                ulSum += usIeLen;

                NAS_ESM_LOG1("NAS_ESM_DecodeNwMsgIei  skip repeated IEI: ", (pstEsmMsgIe+ucLoop)->ucIei);
                TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeNwMsgIei_ENUM, 1, (pstEsmMsgIe+ucLoop)->ucIei);
                break;

            }

            /*记录正在解的信元 */
            ulDecodingIE = ulDecodingIE << 1;

            /*解码信元 */
            enDecodeRst = NAS_ESM_DecodeOptinalIei(&pstEsmMsgIe[ucLoop],
                                                   &ulSum,
                                                   pucRcvNwMsg,
                                                   ulRemainMsgLen - ulSum,
                                                   pstNwMsgRecord);


            if (NAS_ESM_CAUSE_SUCCESS != enDecodeRst)
            {
                continue;
            }

            /*记录已经解的信元 */
            ulDecodedIE |=  (ulTmpPos << ucLoop);

            break;
        }
        /*无法识别收到的NAS消息中的信元,也无法知道跳过码流的长度,可选信元解码失败
         不会影响正常功能,所以按照解码成功处理 */
        if (ucLoop >= ucIeMaxNum)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DecodeNwMsgIei :(WARN)Some IEI not specified!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwMsgIei_ENUM, 2);
            *pulDecodeMsgLen = ulSum;
            return NAS_ESM_CAUSE_SUCCESS;
        }
    }
    *pulDecodeMsgLen = ulSum;

    return NAS_ESM_CAUSE_SUCCESS;

}

/*****************************************************************************
 Function Name   : NAS_ESM_GetDecodeTableIndex
 Description     : 根据消息类型获取解码表的索引
 Input           :VOS_UINT8 enMsgType
                  VOS_UINT32 *pulIndex
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2010-7-8  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_GetDecodeTableIndex( NAS_ESMCN_MSG_TYPE_ENUM_UINT8 enMsgType, VOS_UINT32 *pulIndex )
{
    VOS_UINT32                     ulLoop = NAS_ESM_NULL;

    for (ulLoop = 0; ulLoop < g_EsmDecodeTableSize; ulLoop++)
    {
        if (enMsgType == g_EsmDecodeTable[ulLoop].enMsgTyep)
        {
            break;
        }
    }

    *pulIndex = ulLoop;

     return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNwMsgValue
 Description     : 解码具体消息
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.luojian 00107747      2010-7-8  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwMsgValue
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulDecodeLen,
    VOS_UINT32                          *pulDecodeTableIndex,
    NAS_ESM_NW_MSG_STRU                 *pstMsgIE
)
{
    VOS_UINT32                          ulIndex = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause      =  NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           =  NAS_ESM_NULL;
    VOS_UINT32                          ulUnDecodeMsgLen = *pulDecodeLen;
    VOS_UINT32                          ulDecodeMsgLen  = NAS_ESM_NULL;
    VOS_UINT8*                          pucTmpMsg       =  pucMsg;
    NAS_ESM_NW_MSG_STRU                *pstTmpMsgIE     =  pstMsgIE;
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enMsgType;

    /* 获取网络消息类型 */
    enMsgType = pucTmpMsg[ulSum];

    /* 根据消息类型得到解码表索引*/
    NAS_ESM_GetDecodeTableIndex(enMsgType,&ulIndex);

    /* 不在解码表中的消息类型直接返回错误 */
    if (ulIndex >= g_EsmDecodeTableSize)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_IE_NOIE,
                                        ESM_DECODE_CN_MSG_ESM_MSG_TYPE_INVALID,
                                        enMsgType);
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwMsgValue_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED;
    }

    *pulDecodeTableIndex = ulIndex;

    /*保存消息类型*/
    pstTmpMsgIE->enEsmCnMsgType = enMsgType;

    /*跳过Message type*/
    ulSum++;
    ulUnDecodeMsgLen--;

    if (g_EsmDecodeTable[ulIndex].ulWithLinkEpsb)
    {
        /*记录Linked EPS bearer identity*/
        pstTmpMsgIE->ucLinkedEpsbId     = pucTmpMsg[ulSum++] & NAS_ESM_MSG_LOW_BIT;
        pstTmpMsgIE->bitOpLinkedEpsbId  = NAS_ESM_OP_TRUE;
        ulUnDecodeMsgLen--;
    }

    /* 没有定义解码表的消息只存在已解码公共信息，此时已经解码结束 */
    if (VOS_NULL_PTR == g_EsmDecodeTable[ulIndex].pstEsmMsgIE)
    {
        *pulDecodeLen = ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* 调用公共解码函数 */
    enEsmCause = NAS_ESM_DecodeNwMsgIei(g_EsmDecodeTable[ulIndex].ucMsgTableSize,
                                       ulUnDecodeMsgLen,
                                       &ulDecodeMsgLen,
                                       pucTmpMsg+ulSum,
                                       g_EsmDecodeTable[ulIndex].pstEsmMsgIE,
                                       pstTmpMsgIE);

    *pulDecodeLen = ulSum + ulDecodeMsgLen;
    return enEsmCause;

}

/*****************************************************************************
  Function Name  : NAS_ESM_DecodeNwMsg()
  Description    : ESM模块解析空口消息函数
  Input          : VOS_UINT8             *pucMsg,
                   VOS_UINT32         *ulMsgLen,
                   NAS_ESM_NW_MSG_STRU *pstMsgIE
  Output         : VOS_VOID
  Return Value   : VOS_VOID

  History        :
  1.聂州渝00108792  2008-09-16  Draft Enact
  2.lihong00150010   2009-07-24  Modify
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwMsg(VOS_UINT8 *pucMsg,
                                         VOS_UINT32 *pulMsgLen,
                                         NAS_ESM_NW_MSG_STRU *pstMsgIE)
{
    VOS_UINT8                          *pucTmpMsg           = pucMsg;
    VOS_UINT8                           ucTmpBearerId       = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_NULL;
    VOS_UINT32                          ulUnDecodeMsgLength = *pulMsgLen;
    VOS_UINT32                          ulMsgLenTmp         = NAS_ESM_NULL;
    NAS_ESM_NW_MSG_STRU                *pstTmpMsgIE         = pstMsgIE;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwMsg_ENUM, LNAS_ENTRY);

    /*入口参数检查(pucMsg)*/
    if(ulUnDecodeMsgLength < NAS_ESM_MSG_MIN_LEN)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_IE_NOIE,
                                        ESM_DECODE_CN_MSG_LEN_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwMsg_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_MSG_TOO_SHORT;
    }

    /*判断Protocol discriminator*/
    if(NAS_ESM_MSG_PD != (pucTmpMsg[ulSum] & NAS_ESM_MSG_LOW_BIT))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_IE_NOIE,
                                        ESM_DECODE_CN_MSG_ESM_MSG_PD_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwMsg_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /*记录ucEPSBearerID*/
    /*信元检测,取消息第一字节中的5-8位为pulEpsbId
    ，判断是否符合协议，0000-0100为协议保留。*/
    ucTmpBearerId = (pucTmpMsg[ulSum] >> NAS_ESM_MOVEMENT_4_BITS)& NAS_ESM_MSG_LOW_BIT;

    /*保存pulEpsbId*/
    pstTmpMsgIE->ucEpsbId = ucTmpBearerId;


    /*跳过Protocol discriminator和EPS bearer identity*/
    ulSum++;

    /*保存PTI，跳过Procedure transaction identifier单元*/
    pstTmpMsgIE->ucPti = pucTmpMsg[ulSum];

    /*跳过PTI*/
    ulSum++;

    *pulMsgLen = ulSum;
    ulUnDecodeMsgLength -= NAS_ESM_SUM_LEN_OF_PD_EBI_PTI;
    ulMsgLenTmp = ulUnDecodeMsgLength;

    enEsmCause = NAS_ESM_DecodeNwMsgValue(pucMsg + ulSum,&ulMsgLenTmp,&ulIndex,pstTmpMsgIE);

    *pulMsgLen = *pulMsgLen + ulMsgLenTmp;

    if (NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED != enEsmCause)
    {
        NAS_ESM_SndAirMsgReportInd(pucMsg,*pulMsgLen,
                                   NAS_ESM_AIR_MSG_DIR_ENUM_DOWN,
                                   g_EsmDecodeTable[ulIndex].enAirMsgId);
    }

    return enEsmCause;

}
/*****************************************************************************
  Function Name  : NAS_ESM_DecodeNwMsgGetEsmCause()
  Description    : ESM模块解析空口消息函数,返回esm原因值
  Input          : VOS_UINT8             *pucMsg,
                   VOS_UINT32         *ulMsgLen,
  Output         : VOS_VOID
  Return Value   : VOS_UINT8

  History        :
   1.leixiantiao 00258641  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_DecodeNwEsmMsgGetEsmCause(VOS_UINT8 *pucMsg,
                                         VOS_UINT32 ulMsgLen,
                                         VOS_UINT8 *enEsmCause)
{
    VOS_UINT8                          *pucTmpMsg           = pucMsg;
    VOS_UINT8                           ucTmpBearerId       = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulUnDecodeMsgLength = ulMsgLen;
    VOS_UINT32                          ulMsgLenTmp         = NAS_ESM_NULL;
    NAS_ESM_NW_MSG_STRU                *pstTmpMsgIE;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwEsmMsgGetEsmCause is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_ENTRY);

    /*入口参数检查(pucMsg)*/
    if(ulUnDecodeMsgLength < NAS_ESM_MSG_MIN_LEN)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_ESM_CAUSE_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_MSG_INVALID, 1);
        return VOS_ERR;
    }

    /*判断Protocol discriminator*/
    if(NAS_ESM_MSG_PD != (pucTmpMsg[ulSum] & NAS_ESM_MSG_LOW_BIT))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_ESM_CAUSE_IE,
                                        ESM_DECODE_CN_MSG_PD_INVALID,
                                        (pucTmpMsg[ulSum] & NAS_ESM_MSG_LOW_BIT));
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_MSG_INVALID, 2);
        return VOS_ERR;
    }
    pstTmpMsgIE = (VOS_VOID *)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_NW_MSG_STRU));
    if (VOS_NULL_PTR == pstTmpMsgIE)
    {
        NAS_ESM_ERR_LOG(" NAS_ESM_DecodeNwEsmMsgGetEsmCause: MSG ALLOC VOS_NULL_PTR  Null!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_NULL_PTR);
        return VOS_ERR;
    }

    NAS_ESM_MEM_SET_S(pstTmpMsgIE,sizeof(NAS_ESM_NW_MSG_STRU),0,sizeof(NAS_ESM_NW_MSG_STRU));

    if( ulUnDecodeMsgLength > ESM_MAX_MSG_CONTAINER_CNTNTS_LEN )
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_ESM_CAUSE_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_MSG_INVALID, 3);
        ulUnDecodeMsgLength = ESM_MAX_MSG_CONTAINER_CNTNTS_LEN;
    }

    /*记录ucEPSBearerID*/
    /*信元检测,取消息第一字节中的5-8位为pulEpsbId
    ，判断是否符合协议，0000-0100为协议保留。*/
    ucTmpBearerId = (pucTmpMsg[ulSum] >> NAS_ESM_MOVEMENT_4_BITS)& NAS_ESM_MSG_LOW_BIT;

    /*保存pulEpsbId*/
    pstTmpMsgIE->ucEpsbId = ucTmpBearerId;


    /*跳过Protocol discriminator和EPS bearer identity*/
    ulSum++;

    /*保存PTI，跳过Procedure transaction identifier单元*/
    pstTmpMsgIE->ucPti = pucTmpMsg[ulSum];

    /*跳过PTI*/
    ulSum++;

    ulUnDecodeMsgLength -= NAS_ESM_SUM_LEN_OF_PD_EBI_PTI;
    ulMsgLenTmp = ulUnDecodeMsgLength;

    if(NAS_ESM_CAUSE_SUCCESS == NAS_ESM_DecodeNwMsgValue(pucMsg + ulSum,&ulMsgLenTmp,&ulIndex,pstTmpMsgIE))
    {   if(NAS_ESM_OP_TRUE == pstTmpMsgIE->bitOpEsmCause)
        {
            *enEsmCause = pstTmpMsgIE->enEsmCau;
        }
        NAS_ESM_MEM_FREE(pstTmpMsgIE);
        return VOS_OK;
    }
    else
    {
        NAS_ESM_MEM_FREE(pstTmpMsgIE);
        return VOS_ERR;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeTftNoOperation
 Description     : 解析TAD码为No Operation时的packet filter内容
 Input           :VOS_UINT8                     ucPfCnt
                  NAS_ESM_NW_MSG_STRU           *pstMsgIE
                  VOS_UINT8                     *pucMsg
                  VOS_UINT8                     *pucTftLength
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong 00150010      2010-05-25  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTftNoOperation
(
    NAS_ESM_NW_MSG_STRU                *pstMsgIE,
    VOS_UINT8                          *pucMsg
)
{
    VOS_UINT8                           ucCnt       = NAS_ESM_NULL;
    VOS_UINT8                          *pTmp        = pucMsg;
    NAS_ESM_CONTEXT_TFT_STRU           *pstTftInfo  = VOS_NULL_PTR;

    if (pTmp[NAS_ESM_PARAMETER_ID_OFFSET] != NAS_ESM_TFT_PARA_LIST_ID)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PARA_LIST_ID_INVALID,
                                        pTmp[NAS_ESM_PARAMETER_ID_OFFSET]);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeTftNoOperation_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    /*解码NO OPERATION*/
    pstMsgIE->stTadInfo.enTftOpType = NAS_ESM_TFT_OP_TYPE_NO_OP;
    pstMsgIE->stTadInfo.ucSdfPfNum  = pTmp[NAS_ESM_PARAMETER_LEN_OFFSET];

    for (ucCnt = NAS_ESM_NULL; ucCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ucCnt++)
    {
        pstTftInfo = &pstMsgIE->stTadInfo.astSdfPfInfo[ucCnt];
        pstTftInfo->ucNwPacketFilterId = (pTmp[NAS_ESM_PARAMETER_LEN_OFFSET + 1 + ucCnt])
                                        &(NAS_ESM_MSG_LOW_BIT);
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeTftDeleteFilter
 Description     : 解析TAD码为Delete packet filter时的packet filter内容
 Input           :VOS_UINT8                     ucPfCnt
                  NAS_ESM_NW_MSG_STRU           *pstMsgIE
                  VOS_UINT8                     *pucMsg
                  VOS_UINT8                     *pucTftLength
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong 00150010      2010-05-25  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTftDeleteFilter
(
    NAS_ESM_NW_MSG_STRU                *pstMsgIE,
    VOS_UINT8                          *pucMsg
)
{
    VOS_UINT8                           ucCnt       = NAS_ESM_NULL;
    VOS_UINT8                           ucPfNum     = NAS_ESM_NULL;
    VOS_UINT8                          *pTmp        = pucMsg;
    NAS_ESM_CONTEXT_TFT_STRU           *pstTftInfo  = VOS_NULL_PTR;

    /*获取packet filter个数*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    /* OCTET4 Packet filter identifier 1 */
    for (ucCnt = NAS_ESM_NULL; ucCnt < ucPfNum; ucCnt++)
    {
        pstTftInfo = &pstMsgIE->stTadInfo.astSdfPfInfo[ucCnt];
        pstTftInfo->ucNwPacketFilterId = (pTmp[NAS_ESM_PACKET_FILTER_ID_OFFSET + ucCnt])&(NAS_ESM_MSG_LOW_BIT);
    }

    pstMsgIE->stTadInfo.enTftOpType = NAS_ESM_TFT_OP_TYPE_DELETE_FILTER;
    pstMsgIE->stTadInfo.ucSdfPfNum = ucPfNum;

    return NAS_ESM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_DecodeFilterContent
 Description     : 根据TAD码分情况译码TFT
 Input           :VOS_UINT8                     ucPfCnt
                  NAS_ESM_NW_MSG_STRU           *pstMsgIE
                  VOS_UINT8                     *pucMsg
                  VOS_UINT8                     *pucTftLength
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.yangqianhui 00135146      2009-7-15  Draft Enact
    2.chengmin 00285307         2015-3-23  mod for M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeFilterContent
(
    NAS_ESM_NW_MSG_STRU           *pstMsgIE,
    VOS_UINT8                     *pucMsg,
    VOS_UINT8                      ucToDecodePfNum
)
{
    VOS_UINT8                           ucTad       = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause  = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT8                          *pTmp        = pucMsg;

    /*获取TFT操作码*/
    ucTad = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_HIGH_BIT;

    switch(ucTad)
    {
        case NAS_ESM_TFT_ADD_FILTER:
        case NAS_ESM_TFT_CREATE_TFT:
        case NAS_ESM_TFT_REPLACE_FILTER:
            enEsmCause = NAS_ESM_DecodeTftAddFilter(pstMsgIE, pTmp, ucToDecodePfNum);
            break;
        case NAS_ESM_TFT_NO_OPERATION:
            enEsmCause = NAS_ESM_DecodeTftNoOperation(pstMsgIE, pTmp);
            break;
        case NAS_ESM_TFT_DELETE_TFT:
            pstMsgIE->stTadInfo.enTftOpType = NAS_ESM_TFT_OP_TYPE_DELETE_TFT;
            enEsmCause = NAS_ESM_CAUSE_SUCCESS;
            break;
        case NAS_ESM_TFT_DELETE_FILTER:
            enEsmCause = NAS_ESM_DecodeTftDeleteFilter(pstMsgIE, pTmp);
            break;
        default:
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_TAD_TYPE_INVALID,
                                            ucTad);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    return enEsmCause;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeTftAddFilter
 Description     : 解析TAD码为Add packet filter时的packet filter内容
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.yangqianhui 00135146      2009-7-15  Draft Enact
    2.chengmin 00285307         2015-3-23  Mod for M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTftAddFilter
(
    NAS_ESM_NW_MSG_STRU                *pstMsgIE,
    VOS_UINT8                          *pTmp,
    VOS_UINT8                           ucToDecodePfNum
)
{
    VOS_UINT8                     ucPfNum     = NAS_ESM_NULL;
    VOS_UINT8                     ucTad       = NAS_ESM_NULL;
    VOS_UINT8                     ucLoop      = NAS_ESM_NULL;
    VOS_UINT8                     *pucTmp     = VOS_NULL_PTR;
    VOS_UINT8                     ucPfLength  = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU      stTftInfo;
    NAS_ESM_CAUSE_ENUM_UINT8      enEsmCause  = NAS_ESM_CAUSE_SUCCESS;

    if (ucToDecodePfNum < 1)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucToDecodePfNum);
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    /*获取TFT操作码*/
    ucTad = (pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_HIGH_3_BIT)
                                                    >> NAS_ESM_MOVEMENT_5_BITS;

    pucTmp = &(pTmp[NAS_ESM_PACKET_FILTER_ID_OFFSET]);

    /* 译码所有packet filter */
    for ( ucLoop = 0; ucLoop < ucToDecodePfNum; ucLoop++ )
    {
        NAS_ESM_MEM_SET_S(  &stTftInfo,
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                            0,
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU));

        /* 译码当前packet filter */
        enEsmCause = NAS_ESM_DecodeAddOneFilterTFT(&stTftInfo, pucTmp, &ucPfLength);

        if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
        {
            NAS_ESM_MEM_CPY_S(  &pstMsgIE->stTadInfo.astSdfPfInfo[ucPfNum++],
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                                &stTftInfo,
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU));
        }

        /* 将指针指到下一个packet filter的起始位置 */
        pucTmp = pucTmp + ucPfLength + NAS_ESM_PACKET_FILTER_LEN_OFFSET;
    }


    if (ucPfNum < 1)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    /* 保存操作码和packet filter的个数 */
    pstMsgIE->stTadInfo.enTftOpType = ucTad;
    pstMsgIE->stTadInfo.ucSdfPfNum = ucPfNum;

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftLenAddFilter
 Description     : 判断Tad码为Add Packet Filter时，消息的长度是否合法
 Input           : pucMsg      -- 空口消息码流
                   ucTftLength -- TFT结构长度
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.liuwenyu 00143951      2010-5-25  Draft Enact
    2.chengmin00285307       2015-3-23  Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenAddFilter
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength,
    VOS_UINT8                          *pucToDecodePfNum
)
{
    VOS_UINT8                           ucPfNum         = NAS_ESM_NULL;
    VOS_UINT8                           ucLoop          = NAS_ESM_NULL;
    VOS_UINT8                           ucAllPfLength   = NAS_ESM_NULL;
    VOS_UINT8                           ucPrePfLength   = NAS_ESM_NULL;
    VOS_UINT8                          *pTmp            = pucMsg;
    VOS_UINT8                          *pucTemp         = VOS_NULL_PTR;

    *pucToDecodePfNum = 0;

    /*获取packet filter个数*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if(ucPfNum == NAS_ESM_NULL)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenAddFilter_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    /* 判断长度是否合法 */
    if(ucTftLength < (NAS_ESM_TAD_BYTE + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ucTftLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenAddFilter_ENUM, LNAS_MSG_INVALID, 2);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    pucTemp = &(pTmp[NAS_ESM_PACKET_FILTER_LEN_OFFSET]);

    /* 获取所有packet filter所占总字节数 */
    ucPrePfLength = pTmp[NAS_ESM_PACKET_FILTER_LEN_OFFSET];
    ucAllPfLength = ucPrePfLength + (NAS_ESM_TAD_BYTE + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN);
    if (ucAllPfLength <= ucTftLength)
    {
        (*pucToDecodePfNum) ++;
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ucTftLength);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    for ( ucLoop = 1; ucLoop < ucPfNum; ucLoop++ )
    {
        /* 判断长度是否合法 */
        if ((ucAllPfLength + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN) > ucTftLength)
        {
            break;
        }

        /* 累加下一个packet filter的长度 */
        ucAllPfLength = ucAllPfLength +
                        pucTemp[ucPrePfLength + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN]
                        + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN;
        if (ucAllPfLength <= ucTftLength)
        {
           (*pucToDecodePfNum) ++;
        }

        /* 将指针指到下一个packet filter的长度信元的位置 */
        pucTemp = &(pucTemp[ucPrePfLength + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN]);

        /* 保存下一个packet filter的长度信元的值 */
        ucPrePfLength = *pucTemp;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftLenNoOperation
 Description     : 判断Tad码为No Operation 时，消息的长度是否合法
 Input           : pucMsg      -- 空口消息码流
                   ucTftLength -- TFT结构长度
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8


 History         :
    1.liuwenyu 00143951      2010-5-25  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenNoOperation
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength
)
{
    VOS_UINT8                           *pTmp       = pucMsg;
    VOS_UINT8                            ucPfNum    = NAS_ESM_NULL;

    /*获取packet filter个数*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if((pTmp[NAS_ESM_PARAMETER_LEN_OFFSET] != (ucTftLength - (NAS_ESM_PARAMETER_LEN_OFFSET + 1)))
        ||( NAS_ESM_NULL != ucPfNum))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateTftLenNoOperation:NW->SM TFT Length Error!");
        if (NAS_ESM_NULL != ucPfNum)
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                            ucPfNum);
        }
        else
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                            pTmp[NAS_ESM_PARAMETER_LEN_OFFSET]);
        }
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftLenNoOperation_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftLenDeleteTft
 Description     : 判断Tad码为Delete Tft 时，消息的长度是否合法
 Input           : pucMsg      -- 空口消息码流
                   ucTftLength -- TFT结构长度
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8


 History         :
    1.liuwenyu 00143951      2010-5-25  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenDeleteTft
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength
)
{
    VOS_UINT8                            ucPfNum    = NAS_ESM_NULL;
    VOS_UINT8                           *pTmp       = pucMsg;

    (VOS_VOID)ucTftLength;

    /*获取packet filter个数*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if(ucPfNum != NAS_ESM_NULL)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftLenDeleteTft_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftLenDeleteFilter
 Description     : 判断Tad码为Delete Packet Filter 时，消息的长度是否合法
 Input           : pucMsg      -- 空口消息码流
                   ucTftLength -- TFT结构长度
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8


 History         :
    1.liuwenyu 00143951      2010-5-25  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenDeleteFilter
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength
)
{
    VOS_UINT8                            ucPfNum    = NAS_ESM_NULL;
    VOS_UINT8                           *pTmp       = pucMsg;

    /*获取packet filter个数*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if(ucPfNum == NAS_ESM_NULL)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenDeleteFilter_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    if (ucTftLength != (ucPfNum + 1))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ucTftLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenDeleteFilter_ENUM, LNAS_MSG_INVALID, 2);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}


NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLen
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength,
    VOS_UINT8                          *pucToDecodePfNum
)
{
    VOS_UINT8                           ucTad       = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause  = NAS_ESM_CAUSE_SUCCESS;

    /*获取TFT操作码*/
    ucTad = pucMsg[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_HIGH_BIT;

    switch(ucTad)
    {
        case NAS_ESM_TFT_ADD_FILTER:
        case NAS_ESM_TFT_CREATE_TFT:
        case NAS_ESM_TFT_REPLACE_FILTER:
            enEsmCause = NAS_ESM_ValidateTftLenAddFilter(pucMsg, ucTftLength, pucToDecodePfNum);
            break;
        case NAS_ESM_TFT_NO_OPERATION:

            enEsmCause = NAS_ESM_ValidateTftLenNoOperation(pucMsg, ucTftLength);
            break;
        case NAS_ESM_TFT_DELETE_TFT:

            enEsmCause = NAS_ESM_ValidateTftLenDeleteTft(pucMsg, ucTftLength);
            break;
        case NAS_ESM_TFT_DELETE_FILTER:

            enEsmCause = NAS_ESM_ValidateTftLenDeleteFilter(pucMsg, ucTftLength);
            break;
        default:
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_TAD_TYPE_INVALID,
                                            ucTad);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    return enEsmCause;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsExistSamePfIdInTft
 Description     : 判断TFT中是否有相同PF id的两个PF
 Input           : ulPfNum -- packet filter 数目
                   pstTFT  -- packet filter 数组的首地址
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu 00143951      2010-05-26  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsExistSamePfIdInTft
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
            if (pstTFT[ulCnt1].ucNwPacketFilterId == pstTFT[ulCnt2].ucNwPacketFilterId)
            {
                return NAS_ESM_SUCCESS;
            }
        }
    }

    return NAS_ESM_FAILURE;
}
/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftIeAfterDecode
 Description     : TFT译码结束之后，马上对译码后的TFT信元进行合法性检测
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-7  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftIeAfterDecode
(
    const NAS_ESM_NW_MSG_STRU          *pstMsgIE
)
{
    VOS_UINT32                          ulRslt        = NAS_ESM_FAILURE;
    VOS_UINT32                          ulCnt         = NAS_ESM_NULL;
    const NAS_ESM_CONTEXT_TFT_STRU     *pstTmpTftInfo = VOS_NULL_PTR;

    /* 检测TFT信元中的packet filter id是否有重复 */
    ulRslt = NAS_ESM_IsExistSamePfIdInTft(pstMsgIE->stTadInfo.ucSdfPfNum,
                                          pstMsgIE->stTadInfo.astSdfPfInfo);
    if (NAS_ESM_SUCCESS == ulRslt)
    {
        /*返回消息检测失败*/
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_SAME_PF_ID,
                                        pstMsgIE->stTadInfo.ucSdfPfNum);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftIeAfterDecode_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    /* 若TAD码为CREATE_TFT或ADD_FILTER或REPLACE_FILTER，则检测TFT信元中的优先级
       是否有重复 */
    if ((NAS_ESM_TFT_OP_TYPE_CREATE_TFT == pstMsgIE->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_ADD_FILTER == pstMsgIE->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER == pstMsgIE->stTadInfo.enTftOpType))
    {
        /* 检测TFT信元中的precedence 是否有重复 */
        ulRslt = NAS_ESM_IsExistSamePrecedenceInTft(pstMsgIE->stTadInfo.ucSdfPfNum,
                                                    pstMsgIE->stTadInfo.astSdfPfInfo);
        if (NAS_ESM_SUCCESS == ulRslt)
        {
            /*返回消息检测失败*/
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_SAME_PF_PRECEDENCE,
                                            pstMsgIE->stTadInfo.ucSdfPfNum);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftIeAfterDecode_ENUM, LNAS_MSG_INVALID, 2);
            return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
        }
    }

    /* 检查网络同时设置端口号和端口范围的错误 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum ; ulCnt++)
    {
        pstTmpTftInfo = &pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt];

        if(((NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpLocalPortRange)
            && (NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpSingleLocalPort))
         || ((NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpSingleRemotePort)
            && (NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpRemotePortRange)))
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST,
                                            pstMsgIE->stTadInfo.ucSdfPfNum);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftIeAfterDecode_ENUM, LNAS_MSG_INVALID, 3);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNwApnAmbrValue
 Description     : APN-AMBR信元解码
 Input           : VOS_UINT16  usMsgLen
                   VOS_UINT8 *pucMsg
 Output          :
                   NAS_ESM_NW_MSG_STRU   *pstMsgIE

 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2010-7-2  Draft Enact
    2.chengmin00285307      2015-3-19 Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwTftValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause        = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum             = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg         = pucMsg;
    VOS_UINT8                          *pTmp              = VOS_NULL_PTR;
    VOS_UINT8                           ucToDecodePfNum;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwTftValue is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_ENTRY);

    pTmp     = (VOS_UINT8*) &(pucTmpMsg[ulSum]);

    /* 检测TAD码与PF个数的错误情况*/
    enEsmCause = NAS_ESM_ValidateTftLen(pTmp,(VOS_UINT8)usMsgLen,&ucToDecodePfNum);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*返回消息检测失败*/
        NAS_ESM_WARN_LOG( "NAS_ESM_DecodeNwTftValue:NAS_ESM_ValidateTftLen failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_MSG_INVALID);
        return enEsmCause;
    }


    /* 根据TAD码分情况译码TFT */
    enEsmCause = NAS_ESM_DecodeFilterContent(pstMsgIE, pTmp, ucToDecodePfNum);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*返回消息检测失败*/
        NAS_ESM_WARN_LOG( "NAS_ESM_DecodeEsmTft:NAS_ESM_DecodeFilterContent run Err!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_FAIL, 1);
        return enEsmCause;
    }
    enEsmCause = NAS_ESM_ValidateTftIeAfterDecode(pstMsgIE);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*返回消息检测失败*/
        NAS_ESM_WARN_LOG( "NAS_ESM_DecodeEsmTft:NAS_ESM_ValidateTftIeAfterDecode failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_FAIL, 2);
        return enEsmCause;
    }

    pstMsgIE->bitOpTadInfo = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_EpsQosRateDecodeThirdByte
 Description     : 当Qos的0~7位不为0时，将QoS速率从16位格式变为32位格式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-23  Draft Enact
    2.wangchen 00209181     2014-09-02 Modify:R11
*****************************************************************************/
VOS_VOID  NAS_ESM_EpsQosRateDecodeLowByte
(
    VOS_UINT8                           ucLow,
    VOS_UINT32                         *pulRate32
)
{
    if (NAS_ESM_EPS_QOS_NULL_RATE2 == ucLow)
    {
        *pulRate32 = NAS_ESM_NULL;
        return;
    }

    /* 判断ucLow的第8位是否为0 */
    if (NAS_ESM_NULL != (ucLow >> NAS_ESM_MOVEMENT_7_BITS))
    {
        *pulRate32 = ((ucLow - (1 << NAS_ESM_MOVEMENT_7_BITS)) *
                        NAS_ESM_QOS_RATE_GRANULARITY_64KB) + NAS_ESM_QOS_RATE_576KB;
        return;
    }

    /* 判断ucLow的第7位是否为0 */
    if (NAS_ESM_NULL != (ucLow >> NAS_ESM_MOVEMENT_6_BITS))
    {
        *pulRate32 = ((ucLow - (1 << NAS_ESM_MOVEMENT_6_BITS)) *
                        NAS_ESM_QOS_RATE_GRANULARITY_8KB) + NAS_ESM_QOS_RATE_64KB;
        return;
    }

    *pulRate32 = ucLow;
}
/*****************************************************************************
 Function Name   : NAS_ESM_EpsQosRateDecodeThirdByte
 Description     : 当Qos的8~15位不为0时，将QoS速率从16位格式变为32位格式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-23  Draft Enact
    2.wangchen 00209181     2014-09-02 Modify:R11
*****************************************************************************/
VOS_VOID  NAS_ESM_EpsQosRateDecodeHighByte
(
    VOS_UINT8                           ucHigh,
    VOS_UINT32                         *pulRate32
)
{
    /* 和01001010比较 */
    if (ucHigh <= NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB)
    {
        *pulRate32 = (ucHigh * NAS_ESM_QOS_RATE_GRANULARITY_100KB) +
                                                NAS_ESM_QOS_RATE_8600KB;
        return;
    }

    /* 和10111010比较 */
    if (ucHigh <= NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB)
    {
        *pulRate32 = ((ucHigh - NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_1MB) + NAS_ESM_QOS_RATE_16MB;
        return;
    }

    /* 和11111010比较 */
    if (ucHigh <= NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB)
    {
        *pulRate32 = ((ucHigh - NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_2MB) + NAS_ESM_QOS_RATE_128MB;
        return;
    }

    *pulRate32 = NAS_ESM_QOS_RATE_256MB;
}
/*****************************************************************************
 Function Name   : NAS_ESM_EpsQosRateDecodeThirdByte
 Description     : 当Qos的16~23位不为0时，将QoS速率从16位格式变为32位格式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-23  Draft Enact
    2.wangchen 00209181     2014-09-02 Modify:R11
*****************************************************************************/
VOS_VOID  NAS_ESM_EpsQosRateDecodeThirdByte
(
    VOS_UINT8                           ucThird,
    VOS_UINT32                         *pulRate32
)
{
    /* 和0011 1101比较 */
    if (ucThird <= NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB)
    {
        *pulRate32 = (ucThird*NAS_ESM_QOS_RATE_GRANULARITY_4MB) + NAS_ESM_QOS_RATE_256MB;
        return;
    }

    /* 和1010 0001比较 */
    if (ucThird <= NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB)
    {
        *pulRate32 = ((ucThird - NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_10MB) + NAS_ESM_QOS_RATE_500MB;
        return;
    }

    /* 和1111 0110 比较 */
    if (ucThird <= NAS_ESM_QOS_RATE_RANGE_10GB_GRANULARITY_100MB)
    {
        *pulRate32 = ((ucThird - NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_100MB)+ NAS_ESM_QOS_RATE_1500MB;
        return;
    }

    *pulRate32 = NAS_ESM_QOS_RATE_10GB;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EpsQosRateDecodeTo32
 Description     : 将QoS速率从16位格式变为32位格式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-23  Draft Enact
    2.wangchen 00209181     2014-09-02 Modify:R11
*****************************************************************************/
VOS_VOID  NAS_ESM_EpsQosRateDecodeTo32
(
    VOS_UINT32                          ulRate32,
    VOS_UINT32                         *pulRate32
)
{
    VOS_UINT8                           ucThird = NAS_ESM_NULL;
    VOS_UINT8                           ucHigh = NAS_ESM_NULL;
    VOS_UINT8                           ucLow  = NAS_ESM_NULL;

    if (NAS_ESM_NULL == ulRate32)
    {
        *pulRate32 = NAS_ESM_NULL;
        return;
    }

    ucThird = (VOS_UINT8)((ulRate32 & NAS_ESM_THIRD_BYTE) >> NAS_ESM_MOVEMENT_16_BITS);
    ucHigh = (VOS_UINT8)((ulRate32 & NAS_ESM_HIGH_BYTE) >> NAS_ESM_MOVEMENT_8_BITS);
    ucLow = (VOS_UINT8)(ulRate32 & NAS_ESM_LOW_BYTE);

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        /* 判断16~23位是否为0 */
        if (NAS_ESM_NULL == ucThird)
        {
            /* 判断高8位是否为0 */
            if (NAS_ESM_NULL == ucHigh)
            {
                NAS_ESM_EpsQosRateDecodeLowByte(ucLow, pulRate32);
            }
            else
            {
                NAS_ESM_EpsQosRateDecodeHighByte(ucHigh, pulRate32);
            }
        }
        else
        {
            NAS_ESM_EpsQosRateDecodeThirdByte(ucThird, pulRate32);
        }
    }
    else
    {
        if (NAS_ESM_NULL == ucHigh)
        {
            NAS_ESM_EpsQosRateDecodeLowByte(ucLow, pulRate32);
        }
        else
        {
            NAS_ESM_EpsQosRateDecodeHighByte(ucHigh, pulRate32);
        }
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpItem
 Description     : 译码PCO信元中的IP项，如P-CSCF IPV4 ADDRESS，P-CSCF IPV6
                   ADDRESS，DNS SERVER IPV4 ADDRESS,DNS SERVER IPV6 ADDRESS
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpItem
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_IP_ADDR_STRU        *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* 记录并跳过IP项长度 */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == APP_MAX_IPV4_ADDR_LEN)
    {
        pstIpAddr->ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY_S(  pstIpAddr->aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN,
                            &pucMsg[ulSum],
                            APP_MAX_IPV4_ADDR_LEN);
    }
    else if (ucItemLen == APP_MAX_IPV6_ADDR_LEN)
    {
        pstIpAddr->ucIpType = NAS_ESM_PDN_IPV6;

        NAS_ESM_MEM_CPY_S(  pstIpAddr->aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN,
                            &pucMsg[ulSum],
                            APP_MAX_IPV6_ADDR_LEN);
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DecodePcoIpItem:IP address length is illegal");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoIpItem_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv4Item
 Description     : 译码PCO信元中的IP项，如P-CSCF IPV4 ADDRESS，P-CSCF IPV6
                   ADDRESS，DNS SERVER IPV4 ADDRESS,DNS SERVER IPV6 ADDRESS
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv4Item
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_IPV4_ADDR_STRU              *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* 记录并跳过IP项长度 */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == APP_MAX_IPV4_ADDR_LEN)
    {
        NAS_ESM_MEM_CPY_S(  pstIpAddr->aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN,
                            &pucMsg[ulSum],
                            APP_MAX_IPV4_ADDR_LEN);
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPV4_LEN_INVALID,
                                        ucItemLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoIpv4Item_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv6Item
 Description     : 译码PCO信元中的IP项，如P-CSCF IPV6 ADDRESS，DNS SERVER IPV6 ADDRESS
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv6Item
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_IPV6_ADDR_STRU              *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* 记录并跳过IP项长度 */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == APP_MAX_IPV6_ADDR_LEN)
    {
        NAS_ESM_MEM_CPY_S(  pstIpAddr->aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN,
                            &pucMsg[ulSum],
                            APP_MAX_IPV6_ADDR_LEN);
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPV6_LEN_INVALID,
                                        ucItemLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoIpv6Item_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv6Dns
 Description     : 译码PCO信元中的IPV6 DNS SERVER
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.wangchen 00209181     2014-09-26  Draft Enact
    2.chengmin 00285307     2015-04-14  Mod for M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv6Dns
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV6_ADDR_STRU             *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* DNS SERVER存储已满，则跳过此项 */
    if (pstPco->ucIpv6DnsSerNum >= NAS_ESM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum = *pulSum + ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv6Item( &pucTmpMsg[ulSum],
                                            &pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* 如果获取的IPv6 DNS内容为全零，代表网侧无此DNS，则不增加DNS数量 */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum],
                            pstEmptyIpv6Addr,
                            sizeof(NAS_ESM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);

    *pulSum = *pulSum + ulSum;

    return NAS_ESM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv4Dns
 Description     : 译码PCO信元中的IPV4 DNS SERVER
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.wangchen 00209181     2014-09-26  Draft Enact
    2.chengmin 00285307     2014-04-14  Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv4Dns
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV4_ADDR_STRU             *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* DNS SERVER存储已满，则跳过此项 */
    if (pstPco->ucIpv4DnsSerNum >= NAS_ESM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* 如果获取的IPv4 DNS内容为全零，代表网侧无此DNS，则不增加DNS数量 */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum],
                            pstEmptyIpv4Addr,
                            sizeof(NAS_ESM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv4Pcscf
 Description     : 译码PCO信元中的IPV4 P-CSCF
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.wangchen 00209181     2014-09-26  Draft Enact
    2.chengmin 00285307     2015-04-14  Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv4Pcscf
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV4_ADDR_STRU             *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* P-CSCF存储已满，则跳过此项 */
    if (pstPco->ucIpv4PcscfNum >= NAS_ESM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* 如果获取的IPv4 P-CSCF内容为全零，代表网侧无此P-CSCF，则不增加P-CSCF数量 */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum],
                            pstEmptyIpv4Addr,
                            sizeof(NAS_ESM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4PcscfNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return NAS_ESM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv6Pcscf
 Description     : 译码PCO信元中的IPV6 P-CSCF
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.wangchen 00209181     2014-09-26  Draft Enact
    2.chengmin 00285307     2015-04-14  MOd For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv6Pcscf
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV6_ADDR_STRU             *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* P-CSCF存储已满，则跳过此项 */
    if (pstPco->ucIpv6PcscfNum >= NAS_ESM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv6Item(&pucTmpMsg[ulSum], &pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* 如果获取的IPv4 P-CSCF内容为全零，代表网侧无此P-CSCF，则不增加P-CSCF数量 */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum],
                            pstEmptyIpv6Addr,
                            sizeof(NAS_ESM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6PcscfNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return NAS_ESM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv6Pcscf
 Description     : 译码PCO信元中的IPV6 P-CSCF
                   等
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.wangchen 00209181     2014-09-26  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeLocalAddress
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_DecodeLocalAddress enter");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeLocalAddress_ENUM, LNAS_ENTRY);
        NAS_ESM_GetNwLocalIpSupFlag() = NAS_ESM_NW_LOCAL_IP_CAP_SUPPORT;

        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    }
    else
    {
        /* 跳过此项内容 */
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    }

    *pulSum += ulSum;

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoBcm
 Description     : 译码PCO信元中的BCM
 Input           : pucMsg
 Output          : pstPco
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_DecodePcoBcm
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* 记录并跳过IP项长度 */
    ucItemLen = pucMsg[ulSum++];

    /* 协议规定BCM的内容长度为1，若不为1，则忽略此项 */
    if (1 != ucItemLen)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_BCM_LEN_INVALID,
                                        ucItemLen);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodePcoBcm_ENUM, LNAS_MSG_INVALID, 1);
        return ;
    }

    /* 协议规定BCM的合法值为SM_ESM_BCM_MS_ONLY和SM_ESM_BCM_MS_NW */
    if ((SM_ESM_BCM_MS_ONLY!= pucMsg[ulSum]) && (SM_ESM_BCM_MS_NW != pucMsg[ulSum]))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_BCM_TYPE_INVALID,
                                        pucMsg[ulSum]);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodePcoBcm_ENUM, LNAS_MSG_INVALID, 2);
        return ;
    }

    pstPco->enBcm       = pucMsg[ulSum];
    pstPco->bitOpBcm    = NAS_ESM_OP_TRUE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePcoLen
 Description     : 判断IPCP信元长度的合法性
 Input           : pucMsg       -- 空口消息码流
                   ucIpcpLength -- IPCP结构长度
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-09-13  Draft Enact
    2.yangfan 00159566    2011-06-03  Modify
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateIpcpLen
(
    const VOS_UINT8                    *pucMsg
)
{
    VOS_UINT8                           ucTmpLength         = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;
    VOS_UINT8                           ucSum               = NAS_ESM_NULL;

    /* 获取总长度 */
    ucTmpLength |= (VOS_UINT8)((pucTmpMsg[2] << 8));
    ucTmpLength |= pucTmpMsg[3];

    /* 判断是否可以读取长度 */
    if (ucTmpLength < (ucSum + NAS_ESM_IPCP_PACKET_HEAD_LEN))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                        ucTmpLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateIpcpLen_ENUM, LNAS_MSG_INVALID, 1);

        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /* 跳过IPCP的头长度 */
    ucSum += NAS_ESM_IPCP_PACKET_HEAD_LEN;

    /* 统计所有的长度 */
    while (ucTmpLength > ucSum)
    {
        /* 判断是否可以读取长度 */
        if (ucTmpLength < ((ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) - 1))
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                            ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                            ucTmpLength);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateIpcpLen_ENUM, LNAS_MSG_INVALID, 2);

            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }

        /* 判断长度不能为0，避免死循环 */
        if (NAS_ESM_NULL == pucTmpMsg[(ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) - 1])
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                            ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                            pucTmpMsg[(ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) - 1]);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateIpcpLen_ENUM, LNAS_MSG_INVALID, 3);

            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
        ucSum += pucTmpMsg[(ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) -1];
    }

    /* 判断总长度是否相等 */
    if (ucTmpLength != ucSum)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                        ucTmpLength);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsIpcpTypeValid
 Description     : 判断IPCP类型是否合法
 Input           : ucIpcpType       -- IPCP类型
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-09-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsIpcpTypeValid
(
    VOS_UINT8                          ucIpcpType
)
{
    if((ucIpcpType == NAS_ESM_IPCP_OPTIONS_PRI_DNS_ADDR)
       ||(ucIpcpType == NAS_ESM_IPCP_OPTIONS_SEC_DNS_ADDR))
    {
        return NAS_ESM_SUCCESS;
    }

    return NAS_ESM_FAILURE;
}
/*****************************************************************************
 Function Name   : NAS_ESM_CheckIpAddrIsEmpty
 Description     : 检查IP地址是否为空
 Input           :
 Output          : None
 Return          : BOOL

 History         :
    1.niuxiufan 00181501      2012-10-10  Draft Enact

*****************************************************************************/

VOS_UINT8 NAS_ESM_CheckIpv4AddrIsEmpty(const NAS_ESM_IPV4_ADDR_STRU *pstIpAddr)
{
    if ( (0 == pstIpAddr->aucIpV4Addr[0])
        && (0 == pstIpAddr->aucIpV4Addr[1])
        && (0 == pstIpAddr->aucIpV4Addr[2])
        && (0 == pstIpAddr->aucIpV4Addr[3]))
    {
        return PS_TRUE;
    }

    return PS_FALSE;

}
/*****************************************************************************
 Function Name   : NAS_ESM_OptimizeDnsServer
 Description     : 重新组合DNS
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-10-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_OptimizeDnsServer
(
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
)
{
    VOS_UINT8          ucPriDnsNoExist = PS_TRUE;
    VOS_UINT8          ucSecDnsNoExist = PS_TRUE;

    ucPriDnsNoExist = NAS_ESM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[0]));
    ucSecDnsNoExist = NAS_ESM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[1]));

    if ((PS_TRUE == ucPriDnsNoExist) && (PS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;

        NAS_ESM_MEM_CPY_S(  (VOS_VOID*)&(pstPco->astIpv4DnsServer[0]),
                            sizeof(NAS_ESM_IPV4_ADDR_STRU),
                            (VOS_VOID*)&(pstPco->astIpv4DnsServer[1]),
                            sizeof(NAS_ESM_IPV4_ADDR_STRU));

        return;
    }

    if ((PS_FALSE == ucPriDnsNoExist) && (PS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;
        return;
    }

    if ((PS_TRUE == ucPriDnsNoExist) && (PS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 0;
        return;
    }

    if ((PS_FALSE == ucPriDnsNoExist) && (PS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 2;
        return;
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeIpcpOptionContent
 Description     : 解码IPCP Option内容
 Input           :
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.niuxiufan 00181501      2012-10-10  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeIpcpOptionContent
(
    const VOS_UINT8                     *pucMsg,
    VOS_UINT32                          *pulSum,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco

)
{
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;
    NAS_ESM_CAUSE_ENUM_UINT8            enRslt;
    VOS_UINT32                          ulOptionLen = NAS_ESM_NULL;
    VOS_UINT32                          ulTempSum = *pulSum;


    NAS_ESM_INFO_LOG1("NAS_ESM_DecodeIpcpOptionContent:configure-type:", pucMsg[*pulSum]);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_ENTRY, pucMsg[*pulSum]);

    /* 检查当前的可选项总长度正确 */
    enRslt = NAS_ESM_ValidateIpcpLen(pucMsg + ulTempSum);
    if (NAS_ESM_CAUSE_SUCCESS != enRslt)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_DecodeIpcpOptionContent:Lenth is illegal!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_MSG_INVALID, 1);

        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }


    /*计算该IPCP option长度 */
    ulOptionLen |= (VOS_UINT8)((pucTmpMsg[ulTempSum + 2] << 8));
    ulOptionLen |= pucTmpMsg[ulTempSum + 3];


    /* 跳过头部结构 */
    ulTempSum += NAS_ESM_IPCP_PACKET_HEAD_LEN;

    while (ulTempSum < (*pulSum + ulOptionLen))
    {
        switch (pucTmpMsg[ulTempSum])
        {
            /* 译码主DNS Server信息 */
            case NAS_ESM_IPCP_OPTIONS_PRI_DNS_ADDR:

                /*跳过type字节*/
                ulTempSum++;

                /* 判断长度是否合法 */
                if (NAS_ESM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                                    ESM_DECODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID,
                                                    pucTmpMsg[ulTempSum]);
                    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_MSG_INVALID, 2);
                    *pulSum = ulTempSum;
                    return NAS_ESM_CAUSE_PROTOCOL_ERROR;
                }

                /*跳过length字节*/
                ulTempSum++;

                NAS_ESM_MEM_CPY_S(  (VOS_VOID*)pstPco->astIpv4DnsServer[0].aucIpV4Addr,
                                    APP_MAX_IPV4_ADDR_LEN,
                                    (VOS_VOID*)&pucTmpMsg[ulTempSum],
                                    APP_MAX_IPV4_ADDR_LEN);

                /* 跳过IP地址 */
                ulTempSum += APP_MAX_IPV4_ADDR_LEN;

                break;


            case NAS_ESM_IPCP_OPTIONS_SEC_DNS_ADDR:

                /*跳过type字节*/
                ulTempSum++;

                /* 判断长度是否合法 */
                if (NAS_ESM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                                    ESM_DECODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID,
                                                    pucTmpMsg[ulTempSum]);
                    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_MSG_INVALID, 3);
                    *pulSum = ulTempSum;
                    return NAS_ESM_CAUSE_PROTOCOL_ERROR;
                }

                /*跳过length字节*/
                ulTempSum++;

                NAS_ESM_MEM_CPY_S(  (VOS_VOID*)pstPco->astIpv4DnsServer[1].aucIpV4Addr,
                                    APP_MAX_IPV4_ADDR_LEN,
                                    (VOS_VOID*)&pucTmpMsg[ulTempSum],
                                    APP_MAX_IPV4_ADDR_LEN);

                /* 跳过IP地址 */
                ulTempSum += APP_MAX_IPV4_ADDR_LEN;

                break;

            default:
                /* 判断长度不能为0，避免死循环 */
                if (NAS_ESM_NULL == pucTmpMsg[ulTempSum + 1])
                {
                    *pulSum = ulTempSum;
                    NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                                    ESM_DECODE_CN_MSG_IPCP_OTHER_LEN_INVALID,
                                                    pucTmpMsg[ulTempSum + 1]);
                    return NAS_ESM_CAUSE_PROTOCOL_ERROR;
                }

                /* 跳过信元长度 */
                ulTempSum += pucTmpMsg[ulTempSum + 1];

                break;
        }
    }
    *pulSum = ulTempSum;
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeIpcpContent
 Description     : 译码IPCP的码流
IPCP
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Code      |  Identifier   |            Length             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Options ...
+-+-+-+-+

IP:
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |           IP-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         IP-Address (cont)       |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Primary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    Primary-NBNS-Address (cont)  |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

NBNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Secondary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   Secondary-NBNS-Address (cont) |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-7-15  Draft Enact
    2.yangfan00159566   2011-6-2   Modify

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeIpcpContent
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enRslt              = NAS_ESM_CAUSE_ERROR;
    VOS_UINT8                           ucTmpLength         = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;

    /* 获取length项 */
    ucTmpLength = pucTmpMsg[ulSum++];



    /* 判断总长度是否合法 */
    if (ucTmpLength < NAS_ESM_IPCP_PACKET_HEAD_LEN)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                        ucTmpLength);
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeIpcpContent_ENUM, LNAS_MSG_INVALID);

        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    while (ucTmpLength > (ulSum -1))
    {
        enRslt = NAS_ESM_DecodeIpcpOptionContent(pucTmpMsg, &ulSum, pstPco);
        if (NAS_ESM_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePcoLen
 Description     : 判断PCO信元长度的合法性
 Input           : pucMsg      -- 空口消息码流
                   ucPcoLength -- PCO结构长度
 Output          : usDecodeLen -- 要解码的长度
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-09-13  Draft Enact
    2.chengmin00285307    2015-03-19  Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidatePcoLen
(
    const VOS_UINT8                    *pucMsg,
    VOS_UINT8                           ucPcoLength,
    VOS_UINT16                         *pusDecodeLen
)
{
    VOS_UINT8                           ucAllPcoLength  = NAS_ESM_NULL;
    VOS_UINT8                           ucPrePcoLength  = NAS_ESM_NULL;
    const VOS_UINT8                    *pTmp            = pucMsg;
    const VOS_UINT8                    *pucTemp         = VOS_NULL_PTR;

    /* 如果PCO长度为0，则返回失败 */
    if (NAS_ESM_NULL == ucPcoLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePcoLen:Pco length is 0!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidatePcoLen_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /* 如果PCO信元只包含配置协议项，则返回成功 */
    if (NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL == ucPcoLength)
    {
        *pusDecodeLen = NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* 判断长度是否合法 */
    if(ucPcoLength < (NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL + NAS_ESM_SUM_LEN_OF_ID_LEN))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePcoLen:Pco length is between (1,4)!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidatePcoLen_ENUM, LNAS_MSG_INVALID, 2);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pucTemp = &(pTmp[NAS_ESM_PCO_ITEM_LEN_OFFSET]);

    /* 获取所有packet filter所占总字节数 */
    ucPrePcoLength = pTmp[NAS_ESM_PCO_ITEM_LEN_OFFSET];
    ucAllPcoLength = ucPrePcoLength + (NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL
                                                    + NAS_ESM_SUM_LEN_OF_ID_LEN);
    /*到此处可认为可解析的长度为1，即仅包含CONFIGURATION PROTOCOL*/
    *pusDecodeLen = NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;

    while (ucPcoLength >= ucAllPcoLength)
    {
         *pusDecodeLen = ucAllPcoLength;
         /* 判断长度是否合法 */
         if ((ucAllPcoLength + NAS_ESM_SUM_LEN_OF_ID_LEN) > ucPcoLength)
         {
             break;
         }

         /* 累加下一项的长度 */
         ucAllPcoLength =   ucAllPcoLength +
                            pucTemp[ucPrePcoLength + NAS_ESM_SUM_LEN_OF_ID_LEN]
                            + NAS_ESM_SUM_LEN_OF_ID_LEN;

         /* 将指针指到下一项的长度信元的位置 */
         pucTemp = &(pucTemp[ucPrePcoLength + NAS_ESM_SUM_LEN_OF_ID_LEN]);

         /* 保存下一项的长度信元的值 */
         ucPrePcoLength = *pucTemp;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoContent
 Description     : 译码PCO内容
 Input           : pucMsg---------------------空口消息码流
                   pstMsgIE-------------------译码后的空口消息
 Output          : pulIndex-------------------此函数译码的消息长度指针
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-13  Draft Enact
    2.niuxiufan 00181501  2012-4-23  Modify DTS2012042104730
    3.chengmin00285307    2015-3-19  Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoContent
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco              = &pstMsgIE->stPcoInfo;
    VOS_UINT16                          usPcoItemId         = NAS_ESM_NULL;
    NAS_ESM_IPV6_ADDR_STRU              stEmptyIpv6Addr;
    NAS_ESM_IPV4_ADDR_STRU              stEmptyIpv4Addr;

    NAS_ESM_MEM_SET_S(  &stEmptyIpv6Addr,
                        sizeof(NAS_ESM_IPV6_ADDR_STRU),
                        0,
                        sizeof(NAS_ESM_IPV6_ADDR_STRU));
    NAS_ESM_MEM_SET_S(  &stEmptyIpv4Addr,
                        sizeof(NAS_ESM_IPV4_ADDR_STRU),
                        0,
                        sizeof(NAS_ESM_IPV4_ADDR_STRU));

    /* 判断PCO携带的协议是否正确 */
    if (NAS_ESM_PCO_CONFIG_PROTOCOL != (pucTmpMsg[ulSum++] & NAS_ESM_HIGH_5_BIT_MASK))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID,
                                        (pucTmpMsg[ulSum-1] & NAS_ESM_HIGH_5_BIT_MASK));
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoContent_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    NAS_ESM_MEM_SET_S(  &stEmptyIpv6Addr,
                        sizeof(NAS_ESM_IPV6_ADDR_STRU),
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_IPV6_ADDR_STRU));
    NAS_ESM_MEM_SET_S(  &stEmptyIpv4Addr,
                        sizeof(NAS_ESM_IPV4_ADDR_STRU),
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_IPV4_ADDR_STRU));

    /* 逐一译码PCO所携带的各项内容 */
    while (usMsgLen > ulSum)
    {
        usPcoItemId = ((VOS_UINT16)pucTmpMsg[ulSum++] << NAS_ESM_MOVEMENT_8_BITS);
        usPcoItemId = usPcoItemId | (pucTmpMsg[ulSum++]);

        switch (usPcoItemId)
        {
            case NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV6:
                enEsmCause= NAS_ESM_DecodePcoIpv6Dns(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum,
                                                    &stEmptyIpv6Addr);

                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;
            case NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV4:

                enEsmCause = NAS_ESM_DecodePcoIpv4Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;
            case NAS_ESM_PCO_ITEM_TYPE_BCM:
                NAS_ESM_DecodePcoBcm(&pucTmpMsg[ulSum], pstPco);
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;

            case NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV4:

                enEsmCause = NAS_ESM_DecodePcoIpv4Dns(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;

            case NAS_ESM_PCO_ITEM_TYPE_IPCP:
                /*LV格式译码*/
                (VOS_VOID)NAS_ESM_DecodeIpcpContent(&pucTmpMsg[ulSum],pstPco);
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;

            case NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV6:

                enEsmCause = NAS_ESM_DecodePcoIpv6Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv6Addr);
                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;
            case NAS_ESM_PCO_ITEM_TYPE_IM_CN_SIGNAL_FLAG:
                pstPco->bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
                pstPco->enImsCnSignalFlag = APP_ESM_PDP_FOR_IMS_CN_SIG_ONLY;
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;
            case NAS_ESM_PCO_ITEM_TYPE_LOCAL_ADDRESS:
                (VOS_VOID)NAS_ESM_DecodeLocalAddress(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum);
                break;
            default:

                /* 跳过此项内容 */
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;
        }
    }
    /*重新调整DNS */
    NAS_ESM_OptimizeDnsServer(pstPco);


    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name  : NAS_ESM_DecodeNwPco()
 Description    : SM模块解析PCO信息
 Input          :

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.聂州渝00108792  2008-09-16  Draft Enact
      2.lihong00150010  2009-11-23  Modify
      3.chengmin00285307 2015-3-19  Mod For M Project
*****************************************************************************/
/*lint -e415 -e416 -e661 -e662*/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwPco
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT16                          usDecodeLen;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwPco is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwPco_ENUM, LNAS_ENTRY);

    enEsmCause = NAS_ESM_ValidatePcoLen(pucMsg,(VOS_UINT8)usMsgLen,&usDecodeLen);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*返回消息检测失败*/
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        usMsgLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwPco_ENUM, LNAS_FAIL);
        return enEsmCause;
    }

    enEsmCause = NAS_ESM_DecodePcoContent(usDecodeLen, pucMsg, pstMsgIE);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        return enEsmCause;
    }

    pstMsgIE->bitOpPco = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}/*lint +e415 +e416 +e661 +e662*/

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNwPDNValue
 Description     : PDN地址解码
 Input           :VOS_UINT16             usMsgLen
                VOS_UINT8             *pucMsg
                NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2010-7-7  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwPDNValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_IP_ADDR_STRU       *pstPDNInfo       = &pstMsgIE->stPdnAddrInfo;

    (VOS_VOID)usMsgLen;



    /*内存空间初始化*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)pstPDNInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /*保存PDN地址内型*/
    pstPDNInfo->ucIpType = pucTmpMsg[ulSum++];

    switch(pstPDNInfo->ucIpType)
    {
        /*如果是IPV4内型地址，则保存，IPV4地址有4个字节*/
        case NAS_ESM_PDN_IPV4:
            NAS_ESM_MEM_CPY_S(  pstPDNInfo->aucIpV4Addr,
                                APP_MAX_IPV4_ADDR_LEN,
                                &pucTmpMsg[ulSum],
                                APP_MAX_IPV4_ADDR_LEN);
            break;

        /*如果是IPV6内型地址，则保存，IPV4地址有16个字节,保留*/
        case NAS_ESM_PDN_IPV6:
            /*存放IPV6格式的地址*/
            NAS_ESM_MEM_CPY_S(  pstPDNInfo->aucIpV6Addr + NAS_ESM_IPV6_IF_OFFSET,
                                NAS_ESM_IPV6_IF_LEN,
                                &pucTmpMsg[ulSum],
                                NAS_ESM_IPV6_IF_LEN);
            break;

        /*如果支持IPV4和IPV6地址，按位保存，保留*/
        case NAS_ESM_PDN_IPV4_IPV6:
            /*依次存放IPV4和IPV6地址*/
            NAS_ESM_MEM_CPY_S(  pstPDNInfo->aucIpV6Addr + NAS_ESM_IPV6_IF_OFFSET,
                                NAS_ESM_IPV6_IF_LEN,
                                &pucTmpMsg[ulSum],
                                NAS_ESM_IPV6_IF_LEN);
            NAS_ESM_MEM_CPY_S(  pstPDNInfo->aucIpV4Addr,
                                APP_MAX_IPV4_ADDR_LEN,
                                &pucTmpMsg[ulSum+NAS_ESM_IPV6_IF_LEN],
                                APP_MAX_IPV4_ADDR_LEN);

            break;
        default:
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PDN_IE,
                                            ESM_DECODE_CN_MSG_IP_TYPE_INVALID,
                                            pstPDNInfo->ucIpType);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwPDNValue_ENUM, LNAS_PARAM_INVALID);
            NAS_ESM_MEM_SET_S(  (VOS_VOID*)pstPDNInfo,
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                0,
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pstMsgIE->bitOpPdnAddr  = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNwAPNValue
 Description     : APN Value解码
 Input           :VOS_UINT16             usMsgLen
                VOS_UINT8             *pucMsg
                NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2010-7-7  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwAPNValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulRslt           = NAS_ESM_CAUSE_SUCCESS;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_APN_STRU            stTmpAPNInfo;

    NAS_ESM_MEM_SET_S(  &stTmpAPNInfo,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU));

    /*记录APN的长度,跳过APN的长度*/
    stTmpAPNInfo.ucApnLen = (VOS_UINT8)((usMsgLen)&0xFF);

    NAS_ESM_MEM_CPY_S(  stTmpAPNInfo.aucApnName,
                        stTmpAPNInfo.ucApnLen,
                        &pucTmpMsg[0],
                        stTmpAPNInfo.ucApnLen);

    /* 译码APN */
    ulRslt = NAS_ESM_ApnReverseTransformation(&pstMsgIE->stApnInfo, &stTmpAPNInfo);

    if(NAS_ESM_SUCCESS != ulRslt)
    {
        /*打印异常信息*/
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pstMsgIE->bitOpApn = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}
VOS_VOID NAS_ESM_SdfQosUlMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULMaxRateTmp   = NAS_ESM_NULL;

    ulULMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulULMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULMaxRate);
}
VOS_VOID NAS_ESM_SdfQosDlMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLMaxRateTmp   = NAS_ESM_NULL;

    ulDLMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulDLMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLMaxRate);
}
VOS_VOID NAS_ESM_SdfQosUlGMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULGMaxRateTmp   = NAS_ESM_NULL;

    ulULGMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulULGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULGMaxRate);
}
VOS_VOID NAS_ESM_SdfQosDlGMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLGMaxRateTmp   = NAS_ESM_NULL;

    ulDLGMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulDLGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLGMaxRate);
}
VOS_VOID NAS_ESM_SdfQosUlMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULMaxRateTmp   = NAS_ESM_NULL;

    ulULMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULMaxRate);
    }
}

VOS_VOID NAS_ESM_SdfQosDlMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLMaxRateTmp   = NAS_ESM_NULL;

    ulDLMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;

    if (NAS_ESM_NULL != ulDLMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosUlGMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULGMaxRateTmp   = NAS_ESM_NULL;

    ulULGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULGMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosDlGMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLGMaxRateTmp   = NAS_ESM_NULL;

    ulDLGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulDLGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLGMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosUlMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULMaxRateTmp   = NAS_ESM_NULL;

    ulULMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULMaxRate);
    }
}

VOS_VOID NAS_ESM_SdfQosDlMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLMaxRateTmp   = NAS_ESM_NULL;

    ulDLMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;

    if (NAS_ESM_NULL != ulDLMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosUlGMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULGMaxRateTmp   = NAS_ESM_NULL;

    ulULGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULGMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosDlGMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLGMaxRateTmp   = NAS_ESM_NULL;

    ulDLGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulDLGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLGMaxRate);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeIpv4LocalAddr
 Description     : 译码TFT PF COMPONENT的IPV4 LOCAL地址
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv4LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    NAS_ESM_DecodeIpv4LocalAddr(pstTFTInfo, pucTFTMsg, pucCnt);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeIpv6LocalAddr
 Description     : 译码TFT PF COMPONENT的IPV6 LOCAL地址
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv6LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    NAS_ESM_DecodeIpv6LocalAddr(pstTFTInfo, pucTFTMsg, pucCnt);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeIpv4Addr
 Description     : 译码TFT PF COMPONENT的IPV4地址
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv4Addr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpRmtIpv4AddrAndMask = NAS_ESM_OP_TRUE;
    pstTFTInfo->aucRmtIpv4Address[0]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Address[1]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Address[2]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Address[3]    = pucTFTMsg[(*pucCnt)++];

    pstTFTInfo->aucRmtIpv4Mask[0]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Mask[1]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Mask[2]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Mask[3]       = pucTFTMsg[(*pucCnt)++];
    return;

}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeIpv6Addr
 Description     : 译码TFT PF COMPONENT的IPV6地址
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv6Addr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpRmtIpv6AddrAndMask = NAS_ESM_OP_TRUE;
    pstTFTInfo->aucRmtIpv6Address[0]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[1]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[2]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[3]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[4]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[5]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[6]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[7]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[8]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[9]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[10]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[11]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[12]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[13]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[14]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[15]   = pucTFTMsg[(*pucCnt)++];

    pstTFTInfo->aucRmtIpv6Mask[0]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[1]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[2]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[3]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[4]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[5]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[6]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[7]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[8]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[9]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[10]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[11]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[12]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[13]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[14]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[15]      = pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeProtocolId
 Description     : 译码TFT PF COMPONENT的ProtocolId
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeProtocolId
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpProtocolId = NAS_ESM_OP_TRUE;
    pstTFTInfo->ucProtocolId    = pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeSingleLocalPort
 Description     : 译码TFT PF COMPONENT的SingleLocalPort
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSingleLocalPort
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpSingleLocalPort = NAS_ESM_OP_TRUE;
    pstTFTInfo->usSingleLcPort       = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usSingleLcPort      |= pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeLocalPortRange
 Description     : 译码TFT PF COMPONENT的LocalPortRange
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeLocalPortRange
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpLocalPortRange = NAS_ESM_OP_TRUE;
    pstTFTInfo->usLcPortLowLimit    = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usLcPortLowLimit   |= pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->usLcPortHighLimit   = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usLcPortHighLimit  |= pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeSingleRemotePort
 Description     : 译码TFT PF COMPONENT的SingleRemotePort
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSingleRemotePort
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpSingleRemotePort = NAS_ESM_OP_TRUE;
    pstTFTInfo->usSingleRmtPort       = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usSingleRmtPort      |= pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeRemotePortRange
 Description     : 译码TFT PF COMPONENT的RemotePortRange
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeRemotePortRange
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpRemotePortRange  = NAS_ESM_OP_TRUE;
    pstTFTInfo->usRmtPortLowLimit     = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usRmtPortLowLimit    |= pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->usRmtPortHighLimit    = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usRmtPortHighLimit   |= pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeSpi
 Description     : 译码TFT PF COMPONENT的Spi
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSpi
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpSecuParaIndex = NAS_ESM_OP_TRUE;

    /*lint -e701*/
    pstTFTInfo->ulSecuParaIndex    = (VOS_UINT32)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_24_BITS);
    /*lint +e701*/

    pstTFTInfo->ulSecuParaIndex   |= (pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_16_BITS);
    pstTFTInfo->ulSecuParaIndex   |= (pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->ulSecuParaIndex   |=  pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeTos
 Description     : 译码TFT PF COMPONENT的Tos
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeTos
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpTypeOfService  = NAS_ESM_OP_TRUE;
    pstTFTInfo->ucTypeOfService     = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->ucTypeOfServiceMask = pucTFTMsg[(*pucCnt)++];

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TFT_DecodePfCopTypeFlowLable
 Description     : 译码TFT PF COMPONENT的FlowLable
 Input           : NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
                   const VOS_UINT8                    *pucTFTMsg,
                   VOS_UINT8                           ucCnt
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeFlowLable
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpFlowLabelType = NAS_ESM_OP_TRUE;
    pstTFTInfo->ulFlowLabelType    = (VOS_UINT32)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_16_BITS);
    pstTFTInfo->ulFlowLabelType   |= (pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->ulFlowLabelType   |= pucTFTMsg[(*pucCnt)++];

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SdfQosRateTran
 Description     : SDF QoS速率转换
 Input           : pucTmpMsg
                &ulIndex
                &usULMaxRateTmp
                &usDLMaxRateTmp
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00135146      2009-9-30  Draft Enact
    2.wangchen 00209181 2014-09-02 Modify:R11
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_SdfQosRateTran
(
    VOS_UINT8                           ucTmpLength,
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt            = NAS_ESM_NULL;
    NAS_ESM_DECODE_QOSRATE_FUN          pDecodeRateActFun;

    ulSum = ucTmpLength - 1;

    for (ucCnt = 0; ucCnt < g_EsmDecodeQosRateTableSize; ucCnt++ )
    {
        if (ucTmpLength == g_EsmDecodeQosRateTable[ucCnt].enQosRate)
        {
            pDecodeRateActFun = g_EsmDecodeQosRateTable[ucCnt].pfDecodeFun;

            /* 有处理函数 */
            if (VOS_NULL_PTR != pDecodeRateActFun)
            {
                (pDecodeRateActFun)(&pucTmpMsg[ulSum],pstTmpSdfQosInfo,pulIndex);
            }
            return NAS_ESM_CAUSE_SUCCESS;
        }
    }

    NAS_ESM_WARN_LOG("NAS_ESM_SdfQosRateTran:WARNING:Illegal Qos Offset!");
    TLPS_PRINT2LAYER_WARNING(NAS_ESM_SdfQosRateTran_ENUM, LNAS_MSG_INVALID);
    return NAS_ESM_CAUSE_PROTOCOL_ERROR;

}

VOS_VOID NAS_ESM_MapNwQciToStandardQci
(
    NAS_ESM_CONTEXT_LTE_QOS_STRU               *pstQosInfo,
    VOS_UINT8                                   ucQosLength
)
{
    if ((pstQosInfo->ucNwQCI >= NAS_ESM_QCI_TYPE_QCI1_GBR)
     && (pstQosInfo->ucNwQCI <= NAS_ESM_QCI_TYPE_QCI9_NONGBR))
    {
        /* 如果QCI在1~9之间那么网络的QCI就是标准的QCI */
        pstQosInfo->stQosInfo.ucQCI = pstQosInfo->ucNwQCI;
    }
    else if (NAS_ESM_QOS_LEN_ONLY_QCI == ucQosLength)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_MapNwQciToStandardQci:network QCI is NO_GBR QCI.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_MapNwQciToStandardQci_ENUM, 1);

        /* 如果Qos的长度 等于3，那么网络QCI是NO_GBR的QOS */
        pstQosInfo->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI6_NONGBR;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_MapNwQciToStandardQci:network QCI is GBR QCI.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_MapNwQciToStandardQci_ENUM, 2);
        pstQosInfo->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI2_GBR;
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckNwSdfQosLen
 Description     : 验证QOS 长度的合法性
 Input           : VOS_UINT32 ulMsgLen
 Output          : VOS_UINT32 *ulDecodeLen
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.chengmin00285307 2015-3-25 Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_CheckNwSdfQosLen
(
    VOS_UINT16                           usMsgLen,
    VOS_UINT16                          *ulDecodeLen
)
{
    /* 是测试卡，需要严格检查长度*/
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        if ((usMsgLen != NAS_ESM_QOS_LEN_ONLY_QCI)
            && (usMsgLen != NAS_ESM_QOS_LEN_NO_EXT)
            && (usMsgLen != NAS_ESM_QOS_LEN_ALL_QOS)
            && (usMsgLen != NAS_ESM_QOS_LEN_ALL_WITH_EXT2))
        {
            /*返回消息检测失败*/
            NAS_ESM_WARN_LOG( "NAS_ESM_CheckNwSdfQosLen:QOS length is not 1,5,9,13.");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckNwSdfQosLen_ENUM, LNAS_PARAM_INVALID);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
        *ulDecodeLen = usMsgLen;
    }
    else
    {
        if (usMsgLen >= NAS_ESM_QOS_LEN_ALL_WITH_EXT2)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_ALL_WITH_EXT2;
        }
        else if (usMsgLen >= NAS_ESM_QOS_LEN_ALL_QOS)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_ALL_QOS;
        }
        else if (usMsgLen >= NAS_ESM_QOS_LEN_NO_EXT)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_NO_EXT;
        }
        else if (usMsgLen >= NAS_ESM_QOS_LEN_ONLY_QCI)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_ONLY_QCI;
        }
        else/*长度小于1*/
        {
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }
    return NAS_ESM_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNwSdfQosValue
 Description     : SdfQos解码
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2010-7-7  Draft Enact
    2.yangqianhui 00135146  2010-07-08  Story Key:V200R002C01-429 作为UE，在不能接受网络携带的QCI时自动分配的QCI只能内部使用，和网络交互仍然使用网络的QCI
    3.chengmin00285307 2015-3-19 Mod For M Project
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwSdfQosValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt            = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo = VOS_NULL_PTR;
    VOS_UINT16                           ucLoop;

    if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckNwSdfQosLen(usMsgLen, &ucLoop))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_EPS_QOS_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        usMsgLen);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pstTmpSdfQosInfo = &pstMsgIE->stSdfQosInfo;

    pstTmpSdfQosInfo->ucNwQCI = pucTmpMsg[ulSum++];

    NAS_ESM_MapNwQciToStandardQci(pstTmpSdfQosInfo,(VOS_UINT8)ucLoop);

    pucTmpMsg = pucTmpMsg + ulSum;

    ulSum = 0;

    /* 当GBR QOS 包含ULMaxRate和DLMaxRate时*/
    /* 则它们不能同时为0，否则返回错误*/
    if(ucLoop > 2)
    {
        if (NAS_ESM_QOS_IS_NULL_RATE(pucTmpMsg[ulSum])
         && NAS_ESM_QOS_IS_NULL_RATE(pucTmpMsg[ulSum+1])
         && (PS_TRUE == NAS_ESM_IsGbrBearer(pstTmpSdfQosInfo->stQosInfo.ucQCI)))
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_EPS_QOS_IE,
                                            ESM_DECODE_CN_MSG_QOS_RATE_0,
                                            pstTmpSdfQosInfo->stQosInfo.ucQCI);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwSdfQosValue_ENUM, LNAS_PARAM_INVALID);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }

    for(ucCnt = 1; ucCnt < ucLoop; ucCnt++)
    {
        (VOS_VOID)NAS_ESM_SdfQosRateTran(ucCnt,pucTmpMsg,pstTmpSdfQosInfo,&ulSum);
    }

    pstMsgIE->bitOpEpsQos = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;

}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckNwApnAmbr
 Description     : 验证APN AMBR的合法性
 Input           : VOS_UINT32 ulMsgLen
 Output          : VOS_UINT32 *ulDecodeLen
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.y00135146      2009-10-12  Draft Enact
    2.chengmin00285307 2015-3-19 Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_CheckNwApnAmbr
(
    VOS_UINT16                           ulMsgLen,
    VOS_UINT16                          *ulDecodeLen
)
{
    /* 是测试卡，需要严格检查长度*/
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        /*判断APN AMBR长度是否符合协议*/
        if ((ulMsgLen != NAS_ESM_APN_AMBR_LEN_NO_EXT)
         && (ulMsgLen != NAS_ESM_APN_AMBR_LEN_EXT1)
         && (ulMsgLen != NAS_ESM_APN_AMBR_LEN_EXT2))
        {
            /*返回消息检测失败*/
            NAS_ESM_WARN_LOG( "NAS_ESM_CheckNwApnAmbr:APN AMBR decode Err!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckNwApnAmbr_ENUM, LNAS_PARAM_INVALID, 1);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
        *ulDecodeLen = ulMsgLen;
    }
    else
    {
        if (ulMsgLen >= NAS_ESM_APN_AMBR_LEN_EXT2)
        {
            *ulDecodeLen = NAS_ESM_APN_AMBR_LEN_EXT2;
        }
        else if (ulMsgLen >= NAS_ESM_APN_AMBR_LEN_EXT1)
        {
            *ulDecodeLen = NAS_ESM_APN_AMBR_LEN_EXT1;
        }
        else if (ulMsgLen >= NAS_ESM_APN_AMBR_LEN_NO_EXT)
        {
            *ulDecodeLen = NAS_ESM_APN_AMBR_LEN_NO_EXT;
        }
        else
        {
            /*返回消息检测失败*/
            NAS_ESM_WARN_LOG( "NAS_ESM_CheckNwApnAmbr:APN AMBR decode Err!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckNwApnAmbr_ENUM, LNAS_PARAM_INVALID, 2);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNwApnAmbrValue
 Description     : APN-AMBR信元解码
 Input           : VOS_UINT16  usMsgLen
                   VOS_UINT8 *pucMsg
 Output          :
                   NAS_ESM_NW_MSG_STRU   *pstMsgIE

 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2010-7-2  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwApnAmbrValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum  = NAS_ESM_NULL;
    VOS_UINT16                          usLoop;
    NAS_ESM_CAUSE_ENUM_UINT8            enRslt              = NAS_ESM_CAUSE_SUCCESS;
    NAS_ESM_CONTEXT_APN_AMBR_STRU      *pstApnAmbrInfo      = &pstMsgIE->stApnAmbrInfo;
    VOS_UINT16                          ulToDecodeLen;

    enRslt = NAS_ESM_CheckNwApnAmbr(usMsgLen,&ulToDecodeLen);

    if ( NAS_ESM_CAUSE_SUCCESS != enRslt )
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_AMBR_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        usMsgLen);
        return enRslt;
    }

    for(usLoop = 0; usLoop < ulToDecodeLen; usLoop++)
    {
        switch(usLoop)
        {
            case NAS_ESM_APN_AMBR_OFFSET_DLRATE:
                pstApnAmbrInfo->ucDLApnAmbr = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_ULRATE:
                pstApnAmbrInfo->ucULApnAmbr = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_DLEXT1:
                pstApnAmbrInfo->bitOpDLApnAmbrExt = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucDLApnAmbrExt = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_ULEXT1:
                pstApnAmbrInfo->bitOpULApnAmbrExt = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucULApnAmbrExt = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_DLEXT2:
                pstApnAmbrInfo->bitOpDLApnAmbrExt2 = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucDLApnAmbrExt2 = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_ULEXT2:
                pstApnAmbrInfo->bitOpULApnAmbrExt2 = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucULApnAmbrExt2 = pucMsg[ulSum++];
                break;

            default:
                NAS_ESM_WARN_LOG("NAS_ESM_DecodeNwApnAmbrValue:WARNING:Illegal APN-AMBR Offset!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwApnAmbrValue_ENUM, LNAS_MSG_INVALID);
                return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }

    pstMsgIE->bitOpApnAmbr = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeEsmCause
 Description     : ESM CAUSE信元解码
 Input           :VOS_UINT16  usMsgLen
                  VOS_UINT8 *pucMsg

 Output          : NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2010-7-2  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeEsmCause
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpEsmCause = NAS_ESM_OP_TRUE;
    pstMsgIE->enEsmCau      = pucMsg[0];

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_GetFtmInfoEsmCause() = pstMsgIE->enEsmCau;
    #endif

    return NAS_ESM_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_DecodeAddOneFilterTFTCheckItemLen()
 Description    : SM模块解析ADD FILTER TFT信息各子项时检查长度
 Input          :NAS_ESM_CONTEXT_TFT_STRU   *pstTFTInfo,
                 NAS_ESM_MSG_IE_COMMON_STRU *pstTFTAddr

 Output         : VOS_VOID
 Return Value   : NAS_ESM_CAUSE_ENUM_UINT8

 History        :
      1.chengmin 00285307 2015-03-19 Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeAddOneFilterTFTCheckItemLen
(
    VOS_UINT8                     ucItemId,
    VOS_UINT8                     usMsgLen
)
{
    VOS_UINT16                usLoop;
    VOS_UINT8                 ucLen = NAS_ESM_NULL;

    if (usMsgLen < 1)
    {
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }


    for (usLoop=0; usLoop<g_EsmPFComponentTypeLenTableSize; ++usLoop)
    {
        if (ucItemId == g_EsmPFComponentTypeLenTable[usLoop].ucType)
        {
            ucLen = g_EsmPFComponentTypeLenTable[usLoop].ucLen;
            break;
        }
    }

    if (ucLen == NAS_ESM_NULL || ucLen+1 > usMsgLen)
    {
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}



/*****************************************************************************
 Function Name  : NAS_ESM_DecodeIpv4LocalAddr()
 Description    : 解析IPV4类型的LOCAL IP地址
 Input          :NAS_ESM_CONTEXT_TFT_STRU   *pstTFTInfo,
                 NAS_ESM_MSG_IE_COMMON_STRU *pstTFTAddr

 Output         : VOS_VOID
 Return Value   : NAS_ESM_CAUSE_ENUM_UINT8

 History        :
      1.wangchen 00209181   2014-09-28 Draft Enact
      2.wangchen 00209181   2015-06-23 Modify:R11
*****************************************************************************/
VOS_VOID NAS_ESM_DecodeIpv4LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo,
    const VOS_UINT8                     *pTmp,
    VOS_UINT8                           *pucIndex
)
{
    VOS_UINT8                          ucCnt = *pucIndex;

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
            NAS_ESM_WARN_LOG("NAS_ESM_DecodeIpv4LocalAddr- DECODE!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeIpv4LocalAddr_ENUM, LNAS_ENTRY);
            pstTFTInfo->bitOpLocalIpv4AddrAndMask = NAS_ESM_OP_TRUE;
            pstTFTInfo->aucLocalIpv4Addr[0] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Addr[1] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Addr[2] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Addr[3] = pTmp[ucCnt++ ];

            pstTFTInfo->aucLocalIpv4Mask[0] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Mask[1] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Mask[2] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Mask[3] = pTmp[ucCnt++ ];

        *pucIndex = ucCnt;


    }
    else
    {
        pstTFTInfo->bitOpLocalIpv4AddrAndMask = NAS_ESM_OP_FALSE;
        /* 如果不是该R11版本，但是携带了该信元，则直接跳过 */
        ucCnt = ucCnt + 8;
        *pucIndex = ucCnt;
    }
    return;
}
/*****************************************************************************
 Function Name  : NAS_ESM_DecodeIpv6LocalAddr()
 Description    : 解析IPV4类型的LOCAL IP地址
 Input          :NAS_ESM_CONTEXT_TFT_STRU   *pstTFTInfo,
                 NAS_ESM_MSG_IE_COMMON_STRU *pstTFTAddr

 Output         : VOS_VOID
 Return Value   : NAS_ESM_CAUSE_ENUM_UINT8

 History        :
      1.wangchen 00209181   2014-09-28 Draft Enact
      2.wangchen 00209181   2015-06-23 Modify:R11
*****************************************************************************/
VOS_VOID NAS_ESM_DecodeIpv6LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo,
    const VOS_UINT8                     *pTmp,
    VOS_UINT8                           *pucIndex
)
{
    VOS_UINT8                          ucCnt = *pucIndex;
    VOS_UINT8                          ucIndex;

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DecodeIpv6LocalAddr DECODE!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeIpv6LocalAddr_ENUM, LNAS_ENTRY);
            pstTFTInfo->bitOpLocalIpv6AddrAndMask = NAS_ESM_OP_TRUE;
            for (ucIndex = 0; ucIndex < NAS_ESM_IP_ADDR_LEN_IPV6; ucIndex++)
            {
                pstTFTInfo->aucLocalIpv6Addr[ucIndex] = pTmp[ucCnt];
                ucCnt++;
            }
            pstTFTInfo->ucLocalIpv6Prefix = pTmp[ucCnt++];

        *pucIndex = ucCnt;

    }
    else
    {
        pstTFTInfo->bitOpLocalIpv6AddrAndMask = NAS_ESM_OP_FALSE;
         /* 如果不是该R11版本，但是携带了该信元，则直接跳过 */
        ucCnt = ucCnt + 17;
        *pucIndex = ucCnt;
    }
    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_DecodeAddOneFilterTFT()
 Description    : SM模块解析ADD FILTER TFT信息并保存函数
 Input          :NAS_ESM_CONTEXT_TFT_STRU   *pstTFTInfo,
                 NAS_ESM_MSG_IE_COMMON_STRU *pstTFTAddr

 Output         : VOS_VOID
 Return Value   : NAS_ESM_CAUSE_ENUM_UINT8

 History        :
      1.杨茜惠   00135146  2009-02-12  Draft Enact
      2.chengmin 00285307  2015-03-19  Mod for M Project
      3.sunjitan 00193151  2015-04-25  Modify for R11
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeAddOneFilterTFT
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucLength
)
{
    VOS_UINT8                           ucCnt       = NAS_ESM_NULL;
    VOS_UINT8                           ucTmp       = NAS_ESM_NULL;
    VOS_UINT8                           ucLength    = NAS_ESM_NULL;
    const VOS_UINT8                    *pTmp        = pucTFTMsg;

    VOS_UINT32                          ulIndex     = 0;
    NAS_ESM_TFT_PF_COP_TYPE_ENUM_ENUM8  enTftPfCopType = NAS_ESM_TFT_PF_COP_TYPE_BUTT;

    /*判断消息内容的合法性，如果不合法，则退出;
      pTmp[3]    = filter1中的所有4个components的长度和
                 = TFT码流数组的字节数- TFT码流前边4个域的字节数*/
    /* 判断TFT是否是uplink only */
    ucTmp = (pTmp[ucCnt] >> NAS_ESM_MOVEMENT_4_BITS) & NAS_ESM_LOW_2_BIT_MASK;

    /* OCTET4 Packet filter identifier 1 */
    pstTFTInfo->ucNwPacketFilterId = (pTmp[ucCnt])&(NAS_ESM_MSG_LOW_BIT);

    /* 获取PF的方向 */
    pstTFTInfo->enDirection      = ucTmp;

    /* 如果是R11版本，需要修正PF的方向
       24301 CR1937R4(Rel-11): 6.4.2.3
       The UE shall treat any packet filter without explicit direction as being bi-directional. */
    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        /* 判断是否未指定方向，前面的&操作只取了低2位，保证值不会大于0x03 */
        if(APP_ESM_TRANSFER_DIRECTION_PRE_REL7_TFT_FILTER == ucTmp)
        {
            pstTFTInfo->enDirection = APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK;
        }
    }

    /* OCTET5 ,Packet filter evaluation precedence 1 */
    ucCnt = ucCnt + 1;
    pstTFTInfo->ucPrecedence = pTmp[ucCnt++];

    /* 取出Length of Pactket fileter contents1*/
    ucLength = pTmp[ucCnt++];


    while(ucLength > (ucCnt - NAS_ESM_PACKET_FILTER_LEN_OFFSET))
    {
        /*如果取出的长度不够解析就直接返回，否则就有可能踩后面的内存*/
        if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_DecodeAddOneFilterTFTCheckItemLen(pTmp[ucCnt],
                                                                               ucLength-(ucCnt - NAS_ESM_PACKET_FILTER_LEN_OFFSET)))
        {
            *pucLength = ucLength;
            return NAS_ESM_CAUSE_SUCCESS;
        }

        /* 获取当前TftPfCopType */
        enTftPfCopType = pTmp[ucCnt++];

        /* 扫描译码表，找到对应项就调用译码 */
        for(ulIndex = 0; ulIndex < g_EsmDecodeAddFilterTftTableSize; ulIndex++)
        {
            if(enTftPfCopType == g_EsmDecodeAddFilterTftTable[ulIndex].enTftPfCopType)
            {
                g_EsmDecodeAddFilterTftTable[ulIndex].pfDecodeFun(pstTFTInfo, pTmp, &ucCnt);
                break;
            }
        }

        /* 未找到相应TftPfCopType，前面的码流还有效，后面的不要了，否则继续译码 */
        if(ulIndex >= g_EsmDecodeAddFilterTftTableSize)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DecodeAddOneFilterTFT:WARNING:NW->SM Invalid mandatory information1!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeAddOneFilterTFT_ENUM, LNAS_MSG_INVALID);
            break;
        }
    }

    /* 传出的长度还是要以网络侧发的为准，后续译码其他信元还是要跳过 */
    *pucLength = ucLength;
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeLlcSapi
 Description     : LLC SAPI解码 (合法性由GU模的SM来做)
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-26  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeLlcSapi
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    /*
    8   7   6   5   4   3   2   1
    LLC SAPI IEI
    0   0   0   0   LLC SAPI value
    */

    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpLlcSapi  = NAS_ESM_OP_TRUE;
    pstMsgIE->ucLlcSapi     = (pucMsg[0] & NAS_ESM_MSG_LOW_BIT);
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePacketFlowId
 Description     : Packet Flow Identifier解码 (合法性由GU模的SM来做)
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-26  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodePacketFlowId
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    /*
    8   7   6   5   4   3   2   1
    Packet Flow Identifier IEI
    Length of Packet Flow Identifier IE
    0   Packet Flow Identifier value
    */

    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpPacketFlowId = NAS_ESM_OP_TRUE;
    pstMsgIE->ucPacketFlowId    = (pucMsg[0] & 0x7f);
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeRadioPriority
 Description     : Radio Priority解码
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-27  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeRadioPriority
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    /*
    8       7       6       5       4       3       2       1
    Radio priority IEI              0       Radio priority level value
    */

    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpRadioPriority    = NAS_ESM_OP_TRUE;
    pstMsgIE->ucRadioPriority       = (pucMsg[0] & 0x07);

    /* 如果不是位于【1,4】,则认为是4 */
    if ((NAS_ESM_RADIO_PRIORITY_LEVEL1 > pstMsgIE->ucRadioPriority)
        || (NAS_ESM_RADIO_PRIORITY_LEVEL4 < pstMsgIE->ucRadioPriority))
    {
        pstMsgIE->ucRadioPriority = NAS_ESM_RADIO_PRIORITY_LEVEL4;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeTransactionId
 Description     : Transaction identifier解码
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-27  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTransactionId
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT8                           ucTiValue = NAS_ESM_NULL;

    /*
    8       7       6       5       4       3       2       1
    Linked TI IEI
    Length of Linked TI IE
    TI flag TI value                0       0       0       0
    1       TI value
    */

    /* 协议规定第一字节中的TI VALUE若小于7，则TI值以第一字节中的TI VALUE为准；
       若第一字节中的TI VALUE为7，则必须存在第二字节，TI值以第二字节中的TI值
       为准，忽略第一字节中的TI值 */

    /* 获取第一字节中的TI VALUE */
    ucTiValue = (pucMsg[0] & 0x70) >> NAS_ESM_MOVEMENT_4_BITS;

    /* 如果第一字节中的TI VALUE为7，但不存在第二字节，则认为此信元有误，
       忽略此信元 */
    if (7 == ucTiValue)
    {
        if (1 == usMsgLen)
        {
            /*返回消息检测失败*/
            NAS_ESM_WARN_LOG( "NAS_ESM_DecodeTransactionId:len error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeTransactionId_ENUM, LNAS_MSG_INVALID);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }

        /* TI值设为第二字节中的TI VALUE */
        pstMsgIE->stTransId.ucTiValue = (pucMsg[1] & 0x7f);
    }
    else
    {
        /* TI值设为第一字节中的TI VALUE */
        pstMsgIE->stTransId.ucTiValue  = ucTiValue;
    }

    pstMsgIE->stTransId.ucTiFlag    = (pucMsg[0] & 0x80) >> NAS_ESM_MOVEMENT_7_BITS;
    pstMsgIE->bitOpTransId          = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNegotiatedQos
 Description     : Negotiated Qos解码(代码取自GU模)
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-27  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNegotiatedQos
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_QOS_STRU           *pstTmpPdpQosInfo = VOS_NULL_PTR;

    pstTmpPdpQosInfo = &pstMsgIE->stCntxtQosInfo;

    pstTmpPdpQosInfo->ucDelayClass  = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_DELAY_CLASS) >> NAS_ESM_MOVEMENT_3_BITS;
    pstTmpPdpQosInfo->ucReliabClass = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_RELIABILITY_CLASS);

    pstTmpPdpQosInfo->ucPeakThrough          = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_PEAK_THROUGHPUT) >> NAS_ESM_MOVEMENT_4_BITS;
    pstTmpPdpQosInfo->ucPrecedenceClass      = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_PRECEDENCE_CLASS);

    pstTmpPdpQosInfo->ucMeanThrough          = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_MEAN_THROUGHPUT);

    if (usMsgLen > 3)
    {
        pstTmpPdpQosInfo->ucTrafficClass     = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_TRAFFIC_CLASS)>>5;
        pstTmpPdpQosInfo->ucDeliverOrder     = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_DELIVERY_ORDER)>>3;
        pstTmpPdpQosInfo->ucDeliverOfErrSdu  = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_DELIVERY_ERRORNEOUS_SDU);
    }

    if (usMsgLen > 4)
    {
        pstTmpPdpQosInfo->ucMaximSduSize     = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 5)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForUp  = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 6)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForDown = pucTmpMsg[ulSum++];;
    }

    if (usMsgLen > 7)
    {
        pstTmpPdpQosInfo->ucResidualBer      = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_RESIDUAL_BER) >> NAS_ESM_MOVEMENT_4_BITS;
        pstTmpPdpQosInfo->ucSduErrRatio      = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_SDU_ERROR_RATIO);
    }

    if (usMsgLen > 8)
    {
        pstTmpPdpQosInfo->ucTransDelay           = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_TRANSFER_DELAY) >> NAS_ESM_MOVEMENT_2_BITS;
        pstTmpPdpQosInfo->ucTraffHandlPrior      = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_TRAFFIC_HANDLING_PRIORITY);
    }

    if (usMsgLen > 9)
    {
        pstTmpPdpQosInfo->ucGuarantBitRateForUp  = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 10)
    {
       pstTmpPdpQosInfo->ucGuarantBitRateForDown = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 11)
    {
        pstTmpPdpQosInfo->ucSrcStatisticsDescriptor = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_SSD);

        /* Signalling-Indication 的值只取该字节的第5位 */
        pstTmpPdpQosInfo->ucSignallingIndication    = ((pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_SIGNALLING_INDICATION) >> NAS_ESM_MOVEMENT_4_BITS);
    }

    if (usMsgLen > 12)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForDownExt    = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 13)
    {
        pstTmpPdpQosInfo->ucGuarantBitRateForDownExt = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 14)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForUpExt     = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 15)
    {
        pstTmpPdpQosInfo->ucGuarantBitRateForUpExt = pucTmpMsg[ulSum++];
    }

    if(NAS_RELEASE_R11)
    {
        if (usMsgLen > 16)
        {
            pstTmpPdpQosInfo->ucMaxBitRateForDownExt_2 = pucTmpMsg[ulSum++];
            pstTmpPdpQosInfo->ucGuarantBitRateForDownExt_2 = pucTmpMsg[ulSum++];
        }

        if(usMsgLen > 18)
        {
            pstTmpPdpQosInfo->ucMaxBitRateForUpExt_2 = pucTmpMsg[ulSum++];
            pstTmpPdpQosInfo->ucGuarantBitRateForUpExt_2 = pucTmpMsg[ulSum++];
        }
    }

    pstMsgIE->bitOpNegQos = NAS_ESM_OP_TRUE;
    return NAS_ESM_CAUSE_SUCCESS;
}
/*lint +e961*/
/*lint +e960*/

NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNotificationIndicator
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    NAS_ESM_NOTIFICATION_IND_STRU   *pstNotificationInd = VOS_NULL_PTR;
    (VOS_VOID)usMsgLen;

    pstMsgIE->bitOpNotificationInd = NAS_ESM_OP_TRUE;
    pstNotificationInd = &pstMsgIE->stNotificationInd;

    pstNotificationInd->ucValue = pucMsg[0];

    return  NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndOmLogCnMsgDecodeFail
 Description     : ESM空口信元解析失败，可维可测上报
 Input           : enIeType 信元类型
                   enCause  失败原因
                   ulValue  失败值
 Output          : None
 Return          : None

 History         :
    1.chengmin 00285307      2015-6-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmLogCnMsgDecodeFail
(
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_ESM_DECODE_CN_MSG_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
)
{
    NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU      *pstMsg                         = VOS_NULL_PTR;
#if (VOS_OS_VER == VOS_WIN32)
    VOS_CHAR                                     acPrintStr[MAX_PRINT_CHAR_NUM] = {0};
    VOS_CHAR                                     acValue[MAX_PRINT_CHAR_NUM]    = {0};
#endif

    pstMsg = (NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmLogCnMsgDecodeFail: mem alloc fail!.");
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU),
                        0,
                        sizeof(NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL;
    pstMsg->enIeType                    = enIeType;
    pstMsg->enCause                     = enCause;
    pstMsg->ulValue                     = ulValue;

#if (VOS_OS_VER == VOS_WIN32)
    VOS_StrCpy(acPrintStr, "CN MSG Decode Fail, Fail IE:");
    VOS_StrCat(acPrintStr, g_EsmDecodeFailIePrintTable[enIeType-1].aucPrintStr);
    VOS_StrCat(acPrintStr, ", Fail Cause:");
    VOS_StrCat(acPrintStr, g_EsmDecodeFailCausePrintTable[enCause-1].aucPrintStr);
    VOS_sprintf(acValue, ", Value:%d", ulValue);
    VOS_StrCat(acPrintStr, acValue);
    NAS_ESM_ERR_LOG(acPrintStr);
#endif

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;
}





#ifdef __cplusplus
    #if __cplusplus
                                                }
    #endif
#endif

