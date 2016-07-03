

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Taf_Aps.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsComFunc.h"
#include "MnApsComm.h"
#include "NasComm.h"
#include "TafSdcCtx.h"
#include "TafSdcLib.h"
#include "MnApsMultiMode.h"


#include "TafApsSndInternalMsg.h"

#include "TafApsProcEpdszid.h"
#include "taf_aps_dhcp_pif.h"
#include "ehsm_aps_pif.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndCds.h"
#include "TafApsSndPpp.h"
#include "TafApsSndEsm.h"


#include "TafApsProcIpFilter.h"
#include "TafApsSndRlp.h"
#include "cnas_cttf_hrpd_pa_pif.h"

#include "ApsCdsInterface.h"

#include "TafApsSndEhsm.h"
#include "TafApsSndDhcp.h"
#include "TafApsSndSm.h"
#include "MnApsMultiMode.h"
#include "TafApsProcNvim.h"
#include "TafApsMain.h"
#include "TafApsSndNd.h"

/*lint -e958*/


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_COMFUNC_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/

TAF_APS_SM_ERR_CODE_MAP_STRU            g_astTafApsSmErrCodeMapTbl[] =
{
    { TAF_PS_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT,          SM_TAF_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT             },
    { TAF_PS_CAUSE_SM_MAX_TIME_OUT,                         SM_TAF_CAUSE_SM_MAX_TIME_OUT                            },
    { TAF_PS_CAUSE_SM_INVALID_NSAPI,                        SM_TAF_CAUSE_SM_INVALID_NSAPI                           },
    { TAF_PS_CAUSE_SM_MODIFY_COLLISION,                     SM_TAF_CAUSE_SM_MODIFY_COLLISION                        },
    { TAF_PS_CAUSE_SM_DUPLICATE,                            SM_TAF_CAUSE_SM_DUPLICATE                               },
    { TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE,                    SM_TAF_CAUSE_SM_RAB_SETUP_FAIL                          },
    { TAF_PS_CAUSE_SM_SGSN_VER_PRE_R99,                     SM_TAF_CAUSE_SM_SGSN_VER_PRE_R99                        },
    { TAF_PS_CAUSE_SM_UNKNOWN,                              SM_TAF_CAUSE_SM_UNKNOWN                                 },

    { TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING,       SM_TAF_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING          },
    { TAF_PS_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT,              SM_TAF_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT                 },
    { TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE,              SM_TAF_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE                 },
    { TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,            SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES               },
    { TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN,             SM_TAF_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN                },
    { TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE,          SM_TAF_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE             },
    { TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL,          SM_TAF_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL             },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW, SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,   SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED      },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED,      SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED         },
    { TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,  SM_TAF_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED     },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER,     SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER        },
    { TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED,                SM_TAF_CAUSE_SM_NW_NSAPI_ALREADY_USED                   },
    { TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION,              SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION                 },
    { TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED,                  SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED                     },
    { TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE,                   SM_TAF_CAUSE_SM_NW_NETWORK_FAILURE                      },
    { TAF_PS_CAUSE_SM_NW_REACTIVATION_REQUESTED,            SM_TAF_CAUSE_SM_NW_REACTIVATION_REQUESTED               },
    { TAF_PS_CAUSE_SM_NW_FEATURE_NOT_SUPPORT,               SM_TAF_CAUSE_SM_NW_FEATURE_NOT_SUPPORT                  },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT,               SM_TAF_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT                  },
    { TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT,              SM_TAF_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT                 },
    { TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT,                SM_TAF_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT                   },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER,     SM_TAF_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER        },
    { TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,   SM_TAF_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER      },
    { TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED, SM_TAF_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    },
    { TAF_PS_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT,  SM_TAF_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT },
    { TAF_PS_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION,    SM_TAF_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION       },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,        SM_TAF_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED           },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,        SM_TAF_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED           },
    { TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,  SM_TAF_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     },
    { TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST,   SM_TAF_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST  },
    { TAF_PS_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED,     SM_TAF_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED        },
    { TAF_PS_CAUSE_SM_NW_INVALID_TI,                        SM_TAF_CAUSE_SM_NW_INVALID_TI                           },
    { TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE,    SM_TAF_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE       },
    { TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO,            SM_TAF_CAUSE_SM_NW_INVALID_MANDATORY_INFO               },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT,             SM_TAF_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT                },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE,           SM_TAF_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE              },
    { TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT,                   SM_TAF_CAUSE_SM_NW_IE_NON_EXISTENT                      },
    { TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR,                SM_TAF_CAUSE_SM_NW_CONDITIONAL_IE_ERR                   },
    { TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,                SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE                   },
    { TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED,          SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED             },
    { TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE,      SM_TAF_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE         },

    { TAF_PS_CAUSE_GMM_GPRS_NOT_SUPPORT,                    SM_TAF_CAUSE_GMM_GPRS_NOT_SUPPORT                       },
    { TAF_PS_CAUSE_GMM_ATTACH_MAX_TIMES,                    SM_TAF_CAUSE_GMM_ATTACH_MAX_TIMES                       },
    { TAF_PS_CAUSE_GMM_FORBID_LA,                           SM_TAF_CAUSE_GMM_FORBID_LA                              },
    { TAF_PS_CAUSE_GMM_AUTHENTICATION_FAIL,                 SM_TAF_CAUSE_GMM_AUTHENTICATION_FAIL                    },
    { TAF_PS_CAUSE_GMM_AUTHENTICATION_FAIL,                 SM_TAF_CAUSE_GMM_AUTHENTICATION_REJ                     },
    { TAF_PS_CAUSE_GMM_PS_DETACH,                           SM_TAF_CAUSE_GMM_PS_DETACH                              },
    { TAF_PS_CAUSE_GMM_RRC_EST_FAIL,                        SM_TAF_CAUSE_GMM_RRC_EST_FAIL                           },
    { TAF_PS_CAUSE_GMM_ACCESS_BARRED,                       SM_TAF_CAUSE_GMM_ACCESS_BARRED                          },
    { TAF_PS_CAUSE_SIM_INVALID,                             SM_TAF_CAUSE_GMM_SIM_PS_DOMAIN_REG_INVALID              },
    { TAF_PS_CAUSE_GMM_T3310_EXPIRED,                       SM_TAF_CAUSE_GMM_T3310_EXPIRED                          },
    { TAF_PS_CAUSE_GMM_T3317_EXPIRED,                       SM_TAF_CAUSE_GMM_T3317_EXPIRED                          },
    { TAF_PS_CAUSE_GMM_TIMER_SIGNALING_PROTECT_EXPIRED,     SM_TAF_CAUSE_GMM_TIMER_SIGNALING_PROTECT_EXPIRED        },
    { TAF_PS_CAUSE_GMM_NULL,                                SM_TAF_CAUSE_GMM_STARTUP                                },
    { TAF_PS_CAUSE_GMM_NULL,                                SM_TAF_CAUSE_GMM_NULL                                   },
    { TAF_PS_CAUSE_GMM_NULL,                                SM_TAF_CAUSE_GMM_RESET                                  },
    { TAF_PS_CAUSE_GMM_NO_PDP_CONTEXT,                      SM_TAF_CAUSE_GMM_RAU_ACCEPT                             },
    { TAF_PS_CAUSE_GMM_NO_PDP_CONTEXT,                      SM_TAF_CAUSE_GMM_SERVICE_ACCEPT                         },
    { TAF_PS_CAUSE_GMM_UNKNOWN,                             SM_TAF_CAUSE_GMM_UNKNOWN                                },

    { TAF_PS_CAUSE_GMM_NW_IMSI_UNKNOWN_IN_HLR,              SM_TAF_CAUSE_GMM_NW_IMSI_UNKNOWN_IN_HLR                 },
    { TAF_PS_CAUSE_GMM_NW_ILLEGAL_MS,                       SM_TAF_CAUSE_GMM_NW_ILLEGAL_MS                          },
    { TAF_PS_CAUSE_GMM_NW_IMSI_NOT_ACCEPTED,                SM_TAF_CAUSE_GMM_NW_IMSI_NOT_ACCEPTED                   },
    { TAF_PS_CAUSE_GMM_NW_ILLEGAL_ME,                       SM_TAF_CAUSE_GMM_NW_ILLEGAL_ME                          },
    { TAF_PS_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW,              SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW                 },
    { TAF_PS_CAUSE_GMM_NW_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW, SM_TAF_CAUSE_GMM_NW_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW },
    { TAF_PS_CAUSE_GMM_NW_MS_ID_NOT_DERIVED,                SM_TAF_CAUSE_GMM_NW_MS_ID_NOT_DERIVED                   },
    { TAF_PS_CAUSE_GMM_NW_IMPLICIT_DETACHED,                SM_TAF_CAUSE_GMM_NW_IMPLICIT_DETACHED                   },
    { TAF_PS_CAUSE_GMM_NW_PLMN_NOT_ALLOW,                   SM_TAF_CAUSE_GMM_NW_PLMN_NOT_ALLOW                      },
    { TAF_PS_CAUSE_GMM_NW_LA_NOT_ALLOW,                     SM_TAF_CAUSE_GMM_NW_LA_NOT_ALLOW                        },
    { TAF_PS_CAUSE_GMM_NW_ROAMING_NOT_ALLOW_IN_LA,          SM_TAF_CAUSE_GMM_NW_ROAMING_NOT_ALLOW_IN_LA             },
    { TAF_PS_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW_IN_PLMN,      SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW_IN_PLMN         },
    { TAF_PS_CAUSE_GMM_NW_NO_SUITABL_CELL,                  SM_TAF_CAUSE_GMM_NW_NO_SUITABL_CELL                     },
    { TAF_PS_CAUSE_GMM_NW_MSC_UNREACHABLE,                  SM_TAF_CAUSE_GMM_NW_MSC_UNREACHABLE                     },
    { TAF_PS_CAUSE_GMM_NW_NETWORK_FAILURE,                  SM_TAF_CAUSE_GMM_NW_NETWORK_FAILURE                     },
    { TAF_PS_CAUSE_GMM_NW_MAC_FAILURE,                      SM_TAF_CAUSE_GMM_NW_MAC_FAILURE                         },
    { TAF_PS_CAUSE_GMM_NW_SYNCH_FAILURE,                    SM_TAF_CAUSE_GMM_NW_SYNCH_FAILURE                       },
    { TAF_PS_CAUSE_GMM_NW_PROCEDURE_CONGESTION,             SM_TAF_CAUSE_GMM_NW_PROCEDURE_CONGESTION                },
    { TAF_PS_CAUSE_GMM_NW_GSM_AUT_UNACCEPTABLE,             SM_TAF_CAUSE_GMM_NW_GSM_AUT_UNACCEPTABLE                },
    { TAF_PS_CAUSE_GMM_NW_NOT_AUTHORIZED_FOR_THIS_CSG,      SM_TAF_CAUSE_GMM_NW_NOT_AUTHORIZED_FOR_THIS_CSG         },
    { TAF_PS_CAUSE_GMM_NW_NO_PDP_CONTEXT_ACT,               SM_TAF_CAUSE_GMM_NW_NO_PDP_CONTEXT_ACT                  },
    { TAF_PS_CAUSE_GMM_NW_RETRY_UPON_ENTRY_CELL,            SM_TAF_CAUSE_GMM_NW_RETRY_UPON_ENTRY_CELL               },
    { TAF_PS_CAUSE_GMM_NW_SEMANTICALLY_INCORRECT_MSG,       SM_TAF_CAUSE_GMM_NW_SEMANTICALLY_INCORRECT_MSG          },
    { TAF_PS_CAUSE_GMM_NW_INVALID_MANDATORY_INF,            SM_TAF_CAUSE_GMM_NW_INVALID_MANDATORY_INF               },
    { TAF_PS_CAUSE_GMM_NW_MSG_NONEXIST_NOTIMPLEMENTE,       SM_TAF_CAUSE_GMM_NW_MSG_NONEXIST_NOTIMPLEMENTE          },
    { TAF_PS_CAUSE_GMM_NW_MSG_TYPE_NOT_COMPATIBLE,          SM_TAF_CAUSE_GMM_NW_MSG_TYPE_NOT_COMPATIBLE             },
    { TAF_PS_CAUSE_GMM_NW_IE_NONEXIST_NOTIMPLEMENTED,       SM_TAF_CAUSE_GMM_NW_IE_NONEXIST_NOTIMPLEMENTED          },
    { TAF_PS_CAUSE_GMM_NW_CONDITIONAL_IE_ERROR,             SM_TAF_CAUSE_GMM_NW_CONDITIONAL_IE_ERROR                },
    { TAF_PS_CAUSE_GMM_NW_MSG_NOT_COMPATIBLE,               SM_TAF_CAUSE_GMM_NW_MSG_NOT_COMPATIBLE                  },
    { TAF_PS_CAUSE_GMM_NW_PROTOCOL_ERROR,                   SM_TAF_CAUSE_GMM_NW_PROTOCOL_ERROR                      }
};

#if (FEATURE_ON == FEATURE_LTE)
TAF_APS_ESM_ERR_CODE_MAP_STRU           g_astTafApsEsmErrCodeMapTbl[] =
{
    { TAF_PS_CAUSE_SUCCESS,                                  APP_SUCCESS                                        },
    { TAF_PS_CAUSE_SM_FAILURE,                               APP_FAILURE                                        },
    { TAF_PS_CAUSE_INVALID_PARAMETER,                        APP_ERR_PARA_ERROR                                 },
    { TAF_PS_CAUSE_SM_MAX_TIME_OUT,                          APP_ERR_TIME_OUT                                   },
    { TAF_PS_CAUSE_SM_ERR_UNSPECIFIED_ERROR,                 APP_ERR_UNSPECIFIED_ERROR                          },
    { TAF_PS_CAUSE_SM_ERR_INSUFFICIENT_RESOURCES,            APP_ERR_INSUFFICIENT_RESOURCES                     },
    { TAF_PS_CAUSE_SM_CALL_CID_INVALID,                      APP_ERR_SM_CALL_CID_INVALID                        },
    { TAF_PS_CAUSE_SM_CALL_CID_ACTIVE,                       APP_ERR_SM_CALL_CID_ACTIVE                         },
    { TAF_PS_CAUSE_SM_CALL_CID_NOT_MATCH_BEARER,             APP_ERR_SM_CALL_CID_NOT_MATCH_BEARER               },
    { TAF_PS_CAUSE_SM_BEARER_TYPE_NOT_DEDICATED,             APP_ERR_SM_BEARER_TYPE_NOT_DEDICATED               },
    { TAF_PS_CAUSE_SM_BEARER_INACTIVE,                       APP_ERR_SM_BEARER_INACTIVE                         },
    { TAF_PS_CAUSE_GMM_PS_DETACH,                            APP_ERR_SM_DETACHED                                },
    { TAF_PS_CAUSE_SM_LINK_CID_INVALID,                      APP_ERR_SM_LINK_CID_INVALID                        },
    { TAF_PS_CAUSE_SM_LINK_BEARER_INACTIVE,                  APP_ERR_SM_LINK_BEARER_INACTIVE                    },
    { TAF_PS_CAUSE_SM_APN_LEN_ILLEGAL,                       APP_ERR_SM_APN_LEN_ILLEGAL                         },
    { TAF_PS_CAUSE_SM_APN_SYNTACTICAL_ERROR,                 APP_ERR_SM_APN_SYNTACTICAL_ERROR                   },
    { TAF_PS_CAUSE_SM_AUTH_TYPE_ILLEGAL,                     APP_ERR_SM_AUTH_TYPE_ILLEGAL                       },
    { TAF_PS_CAUSE_SM_USER_NAME_TOO_LONG,                    APP_ERR_SM_USER_NAME_TOO_LONG                      },
    { TAF_PS_CAUSE_SM_USER_PASSWORD_TOO_LONG,                APP_ERR_SM_USER_PASSWORD_TOO_LONG                  },
    { TAF_PS_CAUSE_SM_ACCESS_NUM_TOO_LONG,                   APP_ERR_SM_ACCESS_NUM_TOO_LONG                     },
    { TAF_PS_CAUSE_SM_CALL_CID_IN_OPERATION,                 APP_ERR_SM_CALL_CID_IN_OPERATION                   },
    { TAF_PS_CAUSE_SM_BEARER_TYPE_NOT_DEFAULT,               APP_ERR_SM_BEARER_TYPE_NOT_DEFAULT                 },
    { TAF_PS_CAUSE_SM_BEARER_TYPE_ILLEGAL,                   APP_ERR_SM_BEARER_TYPE_ILLEGAL                     },
    { TAF_PS_CAUSE_SM_MUST_EXIST_DEFAULT_TYPE_CID,           APP_ERR_SM_MUST_EXIST_DEFAULT_TYPE_CID             },
    { TAF_PS_CAUSE_SM_PDN_TYPE_ILLEGAL,                      APP_ERR_SM_PDN_TYPE_ILLEGAL                        },
    { TAF_PS_CAUSE_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL,          APP_ERR_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL            },
    { TAF_PS_CAUSE_SM_SUSPENDED,                             APP_ERR_SM_SUSPENDED                               },
    { TAF_PS_CAUSE_SM_MULTI_EMERGENCY_NOT_ALLOWED,           APP_ERR_SM_MULTI_EMERGENCY_NOT_ALLOWED             },
    { TAF_PS_CAUSE_SM_NON_EMERGENCY_NOT_ALLOWED,             APP_ERR_SM_NON_EMERGENCY_NOT_ALLOWED               },
    { TAF_PS_CAUSE_SM_MODIFY_EMERGENCY_NOT_ALLOWED,          APP_ERR_SM_MODIFY_EMERGENCY_NOT_ALLOWED            },
    { TAF_PS_CAUSE_SM_DEDICATED_FOR_EMERGENCY_NOT_ALLOWED,   APP_ERR_SM_DEDICATED_FOR_EMERGENCY_NOT_ALLOWED     },
    { TAF_PS_CAUSE_SM_BACKOFF_ALG_NOT_ALLOWED,               APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED                 },

    { TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING,        APP_ERR_SM_NW_OPERATOR_DETERMINED_BARRING          },
    { TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,             APP_ERR_SM_NW_INSUFFICIENT_RESOURCES               },
    { TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN,              APP_ERR_SM_NW_MISSING_OR_UKNOWN_APN                },
    { TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE,           APP_ERR_SM_NW_UNKNOWN_PDN_TYPE                     },
    { TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL ,          APP_ERR_SM_NW_USER_AUTH_FAIL                       },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW, APP_ERR_SM_NW_REQ_REJ_BY_SGW_OR_PGW                },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,    APP_ERR_SM_NW_REQ_REJ_UNSPECITY                    },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED,       APP_ERR_SM_NW_SERVICE_OPTION_NOT_SUPPORT           },
    { TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,   APP_ERR_SM_NW_REQ_SERVICE_NOT_SUBSCRIBE            },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER,      APP_ERR_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER        },
    { TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED,                 APP_ERR_SM_NW_PTI_ALREADY_IN_USE                   },
    { TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION,               APP_ERR_SM_NW_REGULAR_DEACT                        },
    { TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED,                   APP_ERR_SM_NW_EPS_QOS_NOT_ACCEPT                   },
    { TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE,                    APP_ERR_SM_NW_NET_FAIL                             },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT,                APP_ERR_SM_NW_SEMANTIC_ERR_IN_TFT                  },
    { TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT,               APP_ERR_SM_NW_SYNTACTIC_ERR_IN_TFT                 },
    { TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT,                 APP_ERR_SM_NW_INVALID_EPS_BERER_IDENTITY           },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER,      APP_ERR_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER        },
    { TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,    APP_ERR_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER      },
    { TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,  APP_ERR_SM_NW_BEARER_WITHOUT_TFT_ACT               },
    { TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED,       APP_ERR_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED         },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,         APP_ERR_SM_NW_PDN_TPYE_IPV4_ONLY_ALLOWED           },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,         APP_ERR_SM_NW_PDN_TPYE_IPV6_ONLY_ALLOWED           },
    { TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,   APP_ERR_SM_NW_SINGLE_ADDR_BERERS_ONLY_ALLOWED      },
    { TAF_PS_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED,           APP_ERR_SM_NW_ESM_INFO_NOT_RECEIVED                },
    { TAF_PS_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST,      APP_ERR_SM_NW_PDN_CONN_NOT_EXIST                   },
    { TAF_PS_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED, APP_ERR_SM_NW_MULTI_PDN_CONN_FOR_ONE_APN_NOT_ALLOWED    },
    { TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST,APP_ERR_SM_NW_COLLISION_WITH_NW_INTIAL_REQEST      },
    { TAF_PS_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE,              APP_ERR_SM_NW_UNSUPPORTED_QCI_VALUE                },
    { TAF_PS_CAUSE_SM_NW_INVALID_TI,                         APP_ERR_SM_NW_INVALID_PTI_VALUE                    },
    { TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE,     APP_ERR_SM_NW_SYNCTACTIC_INCORRECT_MSG             },
    { TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO,             APP_ERR_SM_NW_INVALID_MANDATORY_INFOR              },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT,              APP_ERR_SM_NW_MSG_TYPE_NON_EXIST                   },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE,            APP_ERR_SM_NW_MSG_TYPE_NOT_COMPATIBLE_WITH_PROT    },
    { TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT,                    APP_ERR_SM_NW_INFOR_ELEM_NON_EXIST                 },
    { TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR,                 APP_ERR_SM_NW_CONDITIONAL_IE_ERROR                 },
    { TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,                 APP_ERR_SM_NW_MSG_NOT_COMPATIBLE_WITH_PROT         },
    { TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED,           APP_ERR_SM_NW_PROT_ERR_UNSPECIFIED                 },
    { TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE,       APP_ERR_SM_NW_APN_RESTRICTION_INCOMPATIBLE_WITH_ACT_EPS_BEARER }
};
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_APS_XCC_ERR_CODE_MAP_STRU          g_astTafApsXccErrCodeMapTbl[] =
{
    {TAF_PS_CAUSE_SUCCESS,                                  TAF_XCC_CAUSE_SUCCESS},
    {TAF_PS_CAUSE_XCC_AS_NO_SERVICE,                        TAF_XCC_CAUSE_NO_SERVICE},
    {TAF_PS_CAUSE_XCC_AS_MAX_ACCESS_PROBES,                 TAF_XCC_CAUSE_MAX_ACCESS_PROBES},
    {TAF_PS_CAUSE_XCC_AS_REORDER,                           TAF_XCC_CAUSE_REORDER},
    {TAF_PS_CAUSE_XCC_AS_INTERCEPT,                         TAF_XCC_CAUSE_INTERCEPT},
    {TAF_PS_CAUSE_XCC_AS_ACCESS_DENIED,                     TAF_XCC_CAUSE_ACCESS_DENYIED},
    {TAF_PS_CAUSE_XCC_AS_LOCK,                              TAF_XCC_CAUSE_LOCK},
    {TAF_PS_CAUSE_XCC_AS_ACCT_BLOCK,                        TAF_XCC_CAUSE_ACCT_BLOCK},
    {TAF_PS_CAUSE_XCC_AS_NDSS,                              TAF_XCC_CAUSE_NDSS},
    {TAF_PS_CAUSE_XCC_AS_REDIRECTION,                       TAF_XCC_CAUSE_REDIRECTION},
    {TAF_PS_CAUSE_XCC_AS_ACCESS_IN_PROGRESS,                TAF_XCC_CAUSE_ACCESS_IN_PROGRESS},
    {TAF_PS_CAUSE_XCC_AS_ACCESS_FAIL,                       TAF_XCC_CAUSE_ACCESS_FAIL},
    {TAF_PS_CAUSE_XCC_AS_ABORT,                             TAF_XCC_CAUSE_ABORT},
    {TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_ACH,                TAF_XCC_CAUSE_SIGNAL_FADE_IN_ACH},
    {TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_TCH,                TAF_XCC_CAUSE_SIGNAL_FADE_IN_TCH},
    {TAF_PS_CAUSE_XCC_AS_CHANNEL_ASSIGN_TIMEOUT,            TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT},
    {TAF_PS_CAUSE_XCC_AS_BS_RELEASE,                        TAF_XCC_CAUSE_BS_RELEASE},
    {TAF_PS_CAUSE_XCC_AS_NOT_ACCEPT_BY_BS,                  TAF_XCC_CAUSE_NOT_ACCEPT_BY_BS},
    {TAF_PS_CAUSE_XCC_AS_SO_REJ,                            TAF_XCC_CAUSE_SO_REJ},
    {TAF_PS_CAUSE_XCC_AS_RELEASE_TIME_OUT,                  TAF_XCC_CAUSE_RELEASE_TIME_OUT},
    {TAF_PS_CAUSE_XCC_AS_MS_NORMAL_RELEASE,                 TAF_XCC_CAUSE_MS_NORMAL_RELEASE},
    {TAF_PS_CAUSE_XCC_AS_RETRY_FAIL,                        TAF_XCC_CAUSE_RETRY_FAIL},
    {TAF_PS_CAUSE_XCC_AS_NW_NORMAL_RELEASE,                 TAF_XCC_CAUSE_NW_NORMAL_RELEASE},

    {TAF_PS_CAUSE_XCC_OTHER_SERVICE_IN_TCH,                 TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH},
    {TAF_PS_CAUSE_XCC_CCS_NOT_SUPPORT,                      TAF_XCC_CAUSE_CCS_NOT_SUPPORT},
    {TAF_PS_CAUSE_XCC_CONNECT_ORDER_ACK_FAILURE,            TAF_XCC_CAUSE_CONNECT_ORDER_ACK_FAILURE},

    {TAF_PS_CAUSE_XCC_INCOMING_RSP_TIME_OUT,                TAF_XCC_CAUSE_INCOMING_RSP_TIME_OUT},
    {TAF_PS_CAUSE_XCC_L2_ACK_TIME_OUT,                      TAF_XCC_CAUSE_L2_ACK_TIME_OUT},
    {TAF_PS_CAUSE_XCC_POWER_DOWN_IND,                       TAF_XCC_CAUSE_POWER_DOWN_IND},

    {TAF_PS_CAUSE_XCC_CONNID_NOT_FOUND,                     TAF_XCC_CAUSE_CONNID_NOT_FOUND},
    {TAF_PS_CAUSE_XCC_ACCESS_CNF_TIMEOUT,                   TAF_XCC_CAUSE_ACCESS_CNF_TIMEOUT},
    {TAF_PS_CAUSE_XCC_ACCESS_TCH_TIMEOUT,                   TAF_XCC_CAUSE_ACCESS_TCH_TIMEOUT},
    {TAF_PS_CAUSE_XCC_T53M_TIME_OUT,                        TAF_XCC_CAUSE_T53M_TIME_OUT},
    {TAF_PS_CAUSE_XCC_XCALL_HANGUP,                         TAF_XCC_CAUSE_XCALL_HANGUP},
    {TAF_PS_CAUSE_XCC_CALL_NOT_ALLOWED,                     TAF_XCC_CAUSE_CALL_NOT_ALLOWED},
    {TAF_PS_CAUSE_XCC_ABNORMAL_STATE,                       TAF_XCC_CAUSE_ABNORMAL_STATE},
    {TAF_PS_CAUSE_XCC_ENCODE_FAIL,                          TAF_XCC_CAUSE_ENCODE_FAIL},
    {TAF_PS_CAUSE_XCC_WAIT_L2_ACK_CALL_RELEASE,             TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE},
    {TAF_PS_CAUSE_XCC_CANNOT_FIND_CALL_INSTANCE,            TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE},
    {TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MO_CALL,          TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL},
    {TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MT_CALL,          TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL},
    {TAF_PS_CAUSE_UNKNOWN,                                  TAF_XCC_CAUSE_UNKNOWN},
    {TAF_PS_CAUSE_XCC_CAUSE_L2_ACK_FAIL    ,                TAF_XCC_CAUSE_L2_ACK_FAIL},
    {TAF_PS_CAUSE_XCC_CAUSE_ALLOC_SRID_FAIL,                TAF_XCC_CAUSE_ALLOC_SRID_FAIL},
    {TAF_PS_CAUSE_XCC_CAUSE_NO_RF,                          TAF_XCC_CAUSE_NO_RF},
    {TAF_PS_CAUSE_XCC_CAUSE_PROTOTAL_REV_NOT_SUPPORT,       TAF_XCC_CAUSE_PROTOTAL_REV_NOT_SUPPORT},
    {TAF_PS_CAUSE_XCC_MT_SMS_IN_TCH,                        TAF_XCC_CAUSE_MT_SMS_IN_TCH},
};

TAF_APS_HSM_ERR_CODE_MAP_STRU          g_astTafApsHsmErrCodeMapTbl[] =
{
    {TAF_PS_CAUSE_SUCCESS,                                  HSM_APS_CAUSE_SUCCESS},
    {TAF_PS_CAUSE_HSM_AS_CONN_FAIL,                         HSM_APS_CAUSE_CONN_FAIL},
    {TAF_PS_CAUSE_HSM_AS_MAX_ACCESS_PROBES,                 HSM_APS_CAUSE_MAX_ACCESS_PROBES},
    {TAF_PS_CAUSE_HSM_AS_CONNECTION_DENY,                   HSM_APS_CAUSE_CONN_DENY},
    {TAF_PS_CAUSE_HSM_AS_RTC_RTCACK_FAILURE,                HSM_APS_CAUSE_RTCACK_FAIL},
    {TAF_PS_CAUSE_HSM_AS_SIGNAL_FADE,                       HSM_APS_CAUSE_SIGNAL_FADE},
    {TAF_PS_CAUSE_HSM_AS_SESSION_NOT_EXIST,                 HSM_APS_CAUSE_SESSION_NOT_EXIST},
    {TAF_PS_CAUSE_HSM_AS_CAN_NOT_EST_CONN,                  HSM_APS_CAUSE_CAN_NOT_EST_CONN},
    {TAF_PS_CAUSE_HSM_AS_TIMEOUT,                           HSM_APS_CAUSE_TIMEOUT},
    {TAF_PS_CAUSE_HSM_AS_HRPD_SLAVE,                        HSM_APS_CAUSE_HRPD_SLAVE},
    {TAF_PS_CAUSE_HSM_AS_HANDOFF_FAIL,                      HSM_APS_CAUSE_HANDOFF_FAIL},
    {TAF_PS_CAUSE_HSM_AS_IN_UATI_PROCEDURE,                 HSM_APS_CAUSE_IN_UATI_PROCEDURE},
    {TAF_PS_CAUSE_HSM_AS_IN_SCP_PROCEDURE,                  HSM_APS_CAUSE_IN_SCP_PROCEDURE},

    {TAF_PS_CAUSE_HSM_AS_CONNECTION_EXIST,                  HSM_APS_CAUSE_CONNECTION_EXIST},

    {TAF_PS_CAUSE_HSM_AS_NO_RF,                             HSM_APS_CAUSE_NO_RF},

    {TAF_PS_CAUSE_HSM_AS_REDIRECT,                          HSM_APS_CAUSE_REDIRECT},

    {TAF_PS_CAUSE_HSM_AS_HRPD_HANDOFF_TO_1X,                HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X},

    {TAF_PS_CAUSE_HSM_AS_HRPD_PREFER_CH_NOT_VALID,          HSM_APS_CAUSE_HRPD_PREFER_CH_NOT_VALID},

};

TAF_APS_EHSM_ERR_CODE_MAP_STRU          g_astTafApsEHsmErrCodeMapTbl[] =
{
    {TAF_PS_CAUSE_SUCCESS,                                  EHSM_APS_CAUSE_SUCCESS},
    {TAF_PS_CAUSE_EHSM_NOT_SUPPORT_EHRPD,                   EHSM_APS_CAUSE_NOT_SUPPORT_EHRPD},
    {TAF_PS_CAUSE_EHSM_IN_SUSPEND,                          EHSM_APS_CAUSE_EHRPD_SUSPEND},
    {TAF_PS_CAUSE_EHSM_LAST_PDN,                            EHSM_APS_CAUSE_LAST_PDN},
    {TAF_PS_CAUSE_EHSM_CONN_EST_FAIL,                       EHSM_APS_CAUSE_CONN_EST_FAIL},
    {TAF_PS_CAUSE_EHSM_POWER_OFF,                           EHSM_APS_CAUSE_POWER_OFF},
    {TAF_PS_CAUSE_EHSM_INVALID_PDN_ID,                      EHSM_APS_CAUSE_INVALID_PDN_ID},
    {TAF_PS_CAUSE_EHSM_PPP_DETACH,                          EHSM_APS_CAUSE_PPP_DETACH},
    {TAF_PS_CAUSE_EHSM_TIME_OUT,                            EHSM_APS_CAUSE_TIME_OUT},
    {TAF_PS_CAUSE_EHSM_NW_DISC_IND,                         EHSM_APS_CAUSE_NW_DISC_IND},
    {TAF_PS_CAUSE_EHSM_HSM_CONN_FAIL,                       EHSM_APS_CAUSE_HSM_CONN_FAIL},
    {TAF_PS_CAUSE_EHSM_HSM_MAX_ACCESS_PROBES,               EHSM_APS_CAUSE_HSM_MAX_ACCESS_PROBES},
    {TAF_PS_CAUSE_EHSM_HSM_CONN_DENY,                       EHSM_APS_CAUSE_HSM_CONN_DENY},
    {TAF_PS_CAUSE_EHSM_HSM_RTCACK_RAILURE,                  EHSM_APS_CAUSE_HSM_RTCACK_RAILURE},
    {TAF_PS_CAUSE_EHSM_HSM_SIGNAL_FADE,                     EHSM_APS_CAUSE_HSM_SIGNAL_FADE},
    {TAF_PS_CAUSE_EHSM_HSM_CAN_NOT_EST_CONN,                EHSM_APS_CAUSE_HSM_CAN_NOT_EST_CONN},
    {TAF_PS_CAUSE_EHSM_HSM_TIME_OUT,                        EHSM_APS_CAUSE_HSM_TIMEOUT},
    {TAF_PS_CAUSE_EHSM_HSM_HRPD_SLAVE,                      EHSM_APS_CAUSE_HSM_HRPD_SLAVE},
    {TAF_PS_CAUSE_EHSM_HSM_SESSION_NOT_EXSIT,               EHSM_APS_CAUSE_HSM_SESSION_NOT_EXSIT},
    {TAF_PS_CAUSE_EHSM_HSM_RSLT_IN_UATI_PROCEDURE,          EHSM_APS_CAUSE_HSM_RSLT_IN_UATI_PROCEDURE},
    {TAF_PS_CAUSE_EHSM_HSM_RSLT_IN_SCP_PROCEDURE,           EHSM_APS_CAUSE_HSM_RSLT_IN_SCP_PROCEDURE},
    {TAF_PS_CAUSE_EHSM_HSM_NO_RF,                           EHSM_APS_CAUSE_HSM_NO_RF},
    {TAF_PS_CAUSE_EHSM_HSM_REDIRECT,                        EHSM_APS_CAUSE_HSM_REDIRECT},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_GENERAL_ERROR,             EHSM_APS_CAUSE_PPP_ERROR_GENERAL_ERROR},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_UNAUTHORIZED_APN,          EHSM_APS_CAUSE_PPP_ERROR_UNAUTHORIZED_APN},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_PDN_LIMIT_EXCEEDED,        EHSM_APS_CAUSE_PPP_ERROR_PDN_LIMIT_EXCEEDED},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_NO_PGW_AVAILABLE,          EHSM_APS_CAUSE_PPP_ERROR_NO_PGW_AVAILABLE},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_PGW_UNREACHABLE,           EHSM_APS_CAUSE_PPP_ERROR_PGW_UNREACHABLE},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_PGW_REJECT,                EHSM_APS_CAUSE_PPP_ERROR_PGW_REJECT},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_INSUFFICIENT_PARAMETERS,   EHSM_APS_CAUSE_PPP_ERROR_INSUFFICIENT_PARAMETERS},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_RESOURCE_UNAVAILABLE,      EHSM_APS_CAUSE_PPP_ERROR_RESOURCE_UNAVAILABLE},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_ADMIN_PROHIBITED,          EHSM_APS_CAUSE_PPP_ERROR_ADMIN_PROHIBITED},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_PDNID_ALREADY_IN_USE,      EHSM_APS_CAUSE_PPP_ERROR_PDNID_ALREADY_IN_USE},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_SUBSCRIPTION_LIMITATION,   EHSM_APS_CAUSE_PPP_ERROR_SUBSCRIPTION_LIMITATION},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_PDN_CONNECTION_ALREADY_EXISTS_FOR_THIS_APN,    EHSM_APS_CAUSE_PPP_ERROR_PDN_CONNECTION_ALREADY_EXISTS_FOR_THIS_APN},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_EMERGENCY_SERVICES_NOT_SUPPORTED,              EHSM_APS_CAUSE_PPP_ERROR_EMERGENCY_SERVICES_NOT_SUPPORTED},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_RECONNECT_TO_THIS_APN_NOT_ALLOWED,             EHSM_APS_CAUSE_PPP_ERROR_RECONNECT_TO_THIS_APN_NOT_ALLOWED},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_LCP_EAP_FAILURE,           EHSM_APS_CAUSE_PPP_ERROR_LCP_EAP_FAILURE},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_LCP_OTHER_FAILURE,         EHSM_APS_CAUSE_PPP_ERROR_LCP_OTHER_FAILURE},
    {TAF_PS_CAUSE_EHSM_PPP_ERROR_TIME_OUT,         EHSM_APS_CAUSE_PPP_ERROR_TIMEROUT},
};

TAF_APS_3GPD_FILEID_FLAG_MAP_STRU          g_astTafApsFileIdFlagTbl[] =
{
    {USIMM_CSIM_EFSIPCAP_ID,            TAF_APS_READ_USIMM_CSIM_EFSIPCAP_ID_FLG},
    {USIMM_CSIM_EFSIPUPP_ID,            TAF_APS_READ_USIMM_CSIM_EFSIPUPP_ID_FLG},
    {USIMM_CSIM_EFSIPSP_ID,             TAF_APS_READ_USIMM_CSIM_EFSIPSP_ID_FLG},
    {USIMM_CSIM_EFSIPPAPSS_ID,          TAF_APS_READ_USIMM_CSIM_EFSIPPAPSS_ID_FLG},

    {USIMM_CDMA_EFSIPCAP_ID,            TAF_APS_READ_USIMM_CDMA_EFSIPCAP_ID_FLG},
    {USIMM_CDMA_EFSIPUPP_ID,            TAF_APS_READ_USIMM_CDMA_EFSIPUPP_ID_FLG},
    {USIMM_CDMA_EFSIPSP_ID,             TAF_APS_READ_USIMM_CDMA_EFSIPSP_ID_FLG},
    {USIMM_CDMA_EFSIPPAPSS_ID,          TAF_APS_READ_USIMM_CDMA_EFSIPPAPSS_ID_FLG},
};

#endif


/******************************************************************************
   5 函数实现
******************************************************************************/

VOS_UINT32   TAF_APS_AllocPdpId(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucPdpId
)
{
    VOS_UINT8                           ucAllocPdpId;
    VOS_UINT8                           i;

    ucAllocPdpId = TAF_APS_MAX_PDPID;

    /* 在0~6的范围内查找一个空闲的PDP ID */
    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        /* PDP ID 范围是0-6 */
        if (VOS_FALSE == g_PdpEntity[i].ulUsedFlg)
        {
            /* 有空闲TI */
            ucAllocPdpId = i;
            break;
        }
    }

    if (ucAllocPdpId < TAF_APS_MAX_PDPID)
    {
        /* PDP ID 分配成功 */
        g_PdpEntity[ucAllocPdpId].stClientInfo.aulModuleId[ucCid] = pstCtrl->ulModuleId;
        g_PdpEntity[ucAllocPdpId].stClientInfo.ausClientId[ucCid] = pstCtrl->usClientId;
        g_PdpEntity[ucAllocPdpId].stClientInfo.aucId[ucCid]       = pstCtrl->ucOpId;
        g_PdpEntity[ucAllocPdpId].stClientInfo.ucCid              = ucCid;
        g_PdpEntity[ucAllocPdpId].ulUsedFlg                       = VOS_TRUE;
        g_PdpEntity[ucAllocPdpId].ucPdpId                         = ucAllocPdpId;

        TAF_APS_SetPdpEntBitCidMask(ucAllocPdpId, ucCid);

        /* 无需填充g_TafPsTiTab[ucAllocPdpId].ucUsed域 */
        *pucPdpId = ucAllocPdpId;

        return TAF_APS_ALLOC_PDPID_SUCCESS;
    }
    else
    {
        /* 没有空闲TI */
        return TAF_APS_ALLOC_PDPID_FAIL;
    }
}


VOS_UINT32   TAF_APS_IsPdpIdValid(
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ ucPdpId].ulUsedFlg;
}


VOS_UINT8 TAF_APS_GetCidValue(
    VOS_UINT32                          ulBearerActivateFlg,
    VOS_UINT8                          *pucCidList
)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulMaxCid;

    if (VOS_TRUE == ulBearerActivateFlg)
    {
#if (FEATURE_ON == FEATURE_LTE)
        ulMaxCid = APS_PDP_MAX_CID;
#else
        ulMaxCid = TAF_MAX_CID;
#endif
    }
    else
    {
        ulMaxCid = TAF_MAX_CID;
    }

    for (i = 1; i <= ulMaxCid; i++)
    {
        if ( VOS_TRUE == pucCidList[i])
        {
            return i;
        }
    }

    return 0;
}


VOS_UINT32 TAF_APS_CheckCidDefinedCtx(
    VOS_UINT8                           ucCid
)
{

    if (VOS_TRUE == g_TafCidTab[ucCid].ucUsed)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_CheckBearerPdpTypeSuitable(
    VOS_UINT8                           ucDefaultPdpType,
    TAF_PDP_TYPE_ENUM_UINT8             enUserPdpType
)
{
    if (MN_APS_ADDR_IPV4V6 == ucDefaultPdpType)
    {
        return VOS_TRUE;
    }

    if (( (APS_ADDR_STATIC_IPV4 == ucDefaultPdpType)
       || (APS_ADDR_DYNAMIC_IPV4 == ucDefaultPdpType))
      && (TAF_PDP_IPV4 == enUserPdpType))
    {
        return VOS_TRUE;
    }

    if ((MN_APS_ADDR_IPV6 == ucDefaultPdpType)
      && (TAF_PDP_IPV6 == enUserPdpType))
    {
        return VOS_TRUE;
    }

    if (TAF_PDP_IPV4V6 == enUserPdpType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8   TAF_APS_GetPdpIdByNsapi(
    VOS_UINT8                           ucNsapi
)
{
    VOS_UINT8                           ucTmpPdpId;

    for(ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++ )
    {
        if (( ucNsapi == g_PdpEntity[ucTmpPdpId].ucNsapi)
         && ( VOS_TRUE == g_PdpEntity[ucTmpPdpId].ulUsedFlg ))
        {
            return  ucTmpPdpId;
        }
    }
    return TAF_APS_INVALID_PDPID;

}


VOS_UINT8 TAF_APS_GetPdpIdByLlcSapi(
    VOS_UINT8                           ucLlcSapi
)
{
    VOS_UINT8                           ucTmpPdpId;

    for(ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++)
    {
        if ( (VOS_TRUE == g_PdpEntity[ucTmpPdpId].ulUsedFlg)
          && (VOS_TRUE == g_PdpEntity[ucTmpPdpId].PdpGprsParaFlag)
          && (VOS_TRUE == g_PdpEntity[ucTmpPdpId].GprsPara.Op_Sapi)
          && (ucLlcSapi == g_PdpEntity[ucTmpPdpId].GprsPara.ucSapi) )
        {
            return  ucTmpPdpId;
        }
    }

    return TAF_APS_INVALID_PDPID;
}


VOS_VOID TAF_APS_String2Hex(
    VOS_UINT8                          *pucStr,
    VOS_UINT16                          usStrLen,
    VOS_UINT32                         *pulResult
)
{
    VOS_UINT32                          ulCurrChar      = 0;                    /* current Char */
    VOS_UINT32                          ulCurrTotal     = 0;                    /* current total */
    VOS_UINT8                           ucCurrLen       = 0;                    /* current Length */
/*lint -e961*/
    ulCurrChar                          = (VOS_UINT32)(*(pucStr++));

    while (ucCurrLen++ < usStrLen)
    {
        if ( (ulCurrChar  >= '0') && (ulCurrChar  <= '9') )
        {
            ulCurrChar  = ulCurrChar  - '0';
        }
        else if ( (ulCurrChar  >= 'a') && (ulCurrChar  <= 'f') )
        {
            ulCurrChar  = ulCurrChar  - 'a' + 10;
        }
        else if ( (ulCurrChar  >= 'A') && (ulCurrChar  <= 'F') )
        {
            ulCurrChar  = ulCurrChar  - 'A' + 10;
        }
        else
        {
            return;
        }

        if (ulCurrTotal > 0x0FFFFFFF)
        {
            /* 发生反转, 返回失败 */
            return;
        }
        else
        {
            ulCurrTotal = (ulCurrTotal << 4) + ulCurrChar;                      /* accumulate digit */
            ulCurrChar  = (VOS_UINT32)(*(pucStr++));                            /* get next Char */
        }
    }
/*lint +e961*/

    *pulResult          = ulCurrTotal;                                          /* return result, negated if necessary */

    return;
}


VOS_UINT8   TAF_APS_GetPdpIdByCid(
    VOS_UINT8                           ucCid
)
{
    VOS_UINT8                           i;

    if ( ucCid > TAF_MAX_CID )
    {
        return  TAF_APS_INVALID_PDPID;
    }

    for(i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(i, ucCid))
         && (VOS_TRUE == g_PdpEntity[i].ulUsedFlg))
        {
            /*找到了相同的CID,并且该项是正在使用的,则为找到了正确的项*/
            return i;
        }
    }
    return TAF_APS_INVALID_PDPID;
}


VOS_UINT8 TAF_APS_GetPdpIdByEpsbId(VOS_UINT32 ulEpsbId)
{
    VOS_UINT8                           i;

    if (!APS_JUDGE_NSAPI_VALID(ulEpsbId))
    {
        return TAF_APS_INVALID_PDPID;
    }

    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if ( (VOS_TRUE == g_PdpEntity[i].ulUsedFlg)
          && (ulEpsbId == g_PdpEntity[i].ucNsapi) )
        {
            return i;
        }
    }

    return TAF_APS_INVALID_PDPID;
}


VOS_UINT32   TAF_APS_GetPdpEntModuleId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    return g_PdpEntity[ucPdpId].stClientInfo.aulModuleId[ucCid];
}


VOS_UINT16   TAF_APS_GetPdpEntClientId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    return g_PdpEntity[ucPdpId].stClientInfo.ausClientId[ucCid];
}


VOS_UINT8   TAF_APS_GetPdpEntOpId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    return g_PdpEntity[ucPdpId].stClientInfo.aucId[ucCid];
}


VOS_VOID   TAF_APS_SetPdpEntClientInfo(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    PS_MEM_SET(&g_PdpEntity[ucPdpId].stClientInfo, 0, sizeof(TAF_APS_CLIENT_INFO_STRU));

    TAF_APS_SetPdpEntCidValue(ucPdpId, ucCid);
    TAF_APS_SetPdpEntModuleId(ucPdpId, ucCid, ulModuleId);
    TAF_APS_SetPdpEntClientId(ucPdpId, ucCid, usClientId);
    TAF_APS_SetPdpEntOpId(ucPdpId, ucCid, ucOpId);

    return;
}


VOS_VOID   TAF_APS_AddPdpEntClientInfo(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    CONST TAF_CTRL_STRU                *pstCtrl
)
{
    TAF_APS_SetPdpEntBitCidMask(ucPdpId, ucCid);

    TAF_APS_SetPdpEntModuleId(ucPdpId, ucCid, pstCtrl->ulModuleId);
    TAF_APS_SetPdpEntClientId(ucPdpId, ucCid, pstCtrl->usClientId);
    TAF_APS_SetPdpEntOpId(ucPdpId, ucCid, pstCtrl->ucOpId);

    return;
}


VOS_VOID TAF_APS_RmvPdpEntClientInfo (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_APS_BITCID_INFO_STRU           *pstBitCid
)
{
    VOS_UINT8                           i;

    TAF_APS_RmvPdpEntBitCidMask(ucPdpId, ucCid);
    TAF_APS_SetPdpEntModuleId(ucPdpId, ucCid, TAF_APS_INVALID_MODULEID);
    TAF_APS_SetPdpEntClientId(ucPdpId, ucCid, TAF_APS_INVALID_CLIENTID);
    TAF_APS_SetPdpEntOpId(ucPdpId, ucCid, TAF_APS_INVALID_OPID);

    /* 如果去激活的CID为建立该承载时使用的，需要通知ESM新的cid */
    if (ucCid == TAF_APS_GetPdpEntCurrCid(ucPdpId))
    {
        for (i = 0; i < pstBitCid->ulNum; i++)
        {
            if (ucCid != pstBitCid->aucCid[i])
            {
                break;
            }
        }

        TAF_APS_SetPdpEntCidValue(ucPdpId, pstBitCid->aucCid[i]);

#if (FEATURE_ON == FEATURE_LTE)
        /* 通知ESM当前的Cid刷新 */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);
#endif
    }
}


VOS_UINT8  TAF_APS_GetPdpIdByDefaultCid (VOS_VOID)
{
    VOS_UINT8                           i;

    /*TI有效范围是0-6,8-14*/
    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        /* 如果当前的CID相同， */
        if ( ( VOS_TRUE == g_PdpEntity[i].ulUsedFlg )
          && ( VOS_TRUE == g_PdpEntity[i].PdpNsapiFlag )
          && ( TAF_APS_DEFAULT_CID == g_PdpEntity[i].stClientInfo.ucCid ))
        {
            return i;
        }

    }

    TAF_NORMAL_LOG(WUEPS_PID_TAF,"TAF_APS_GetPdpIdByDefaultCid: Can not find PDP ID for CID");

    /* 未找到匹配的，返回无效的PDP ID */
    return TAF_APS_INVALID_PDPID;

}


VOS_VOID TAF_APS_SetPdpEntCidValue (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    g_PdpEntity[ucPdpId].stClientInfo.ucCid = ucCid;
    TAF_APS_SetPdpEntBitCidMask(ucPdpId, ucCid);
}


VOS_VOID TAF_APS_SetPdpEntModuleId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulModuleId
)
{
    if (ucCid <= TAF_MAX_CID)
    {
        g_PdpEntity[ucPdpId].stClientInfo.aulModuleId[ucCid] = ulModuleId;
    }
}

VOS_VOID TAF_APS_SetPdpEntClientId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT16                          usClientId
)
{
    g_PdpEntity[ucPdpId].stClientInfo.ausClientId[ucCid] = usClientId;
}


VOS_VOID TAF_APS_SetPdpEntOpId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucOpId
)
{
    if (ucCid <= TAF_MAX_CID)
    {
        g_PdpEntity[ucPdpId].stClientInfo.aucId[ucCid] = ucOpId;
    }
}


VOS_VOID TAF_APS_SetPdpEntBitCidMask (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulCid;

    ulCid = (VOS_UINT32)0x00000001 << ucCid;
    g_PdpEntity[ucPdpId].stClientInfo.ulBitCidMask |= ulCid;
}



VOS_VOID TAF_APS_SetPdpEntModDialInfo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_PDP_MOD_DIAL_STRU          *pstModDial
)
{
    g_PdpEntity[ucPdpId].stModDial = *pstModDial;
}


VOS_VOID TAF_APS_GetPdpEntModDialInfo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_PDP_MOD_DIAL_STRU          *pstModDial
)
{
     *pstModDial = g_PdpEntity[ucPdpId].stModDial;
}


VOS_VOID TAF_APS_RmvPdpEntBitCidMask (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulCid;

    ulCid = ((VOS_UINT32)0x00000001 << ucCid);
    g_PdpEntity[ucPdpId].stClientInfo.ulBitCidMask &= (~ulCid);
}


VOS_VOID TAF_APS_SetPdpEntDialPdpType(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    g_PdpEntity[ucPdpId].stClientInfo.aenPdpType[ucCid] = enPdpType;
}


VOS_UINT8 TAF_APS_GetPdpEntDialPdpType(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    return g_PdpEntity[ucPdpId].stClientInfo.aenPdpType[ucCid];
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 TAF_APS_CheckImsBearerByCid (
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulCid;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (TAF_APS_STA_ACTIVE == TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            ulCid = (VOS_UINT32)0x00000001 << ucCid;
            if ((0 != (g_PdpEntity[ucPdpId].stClientInfo.ulBitCidMask & ulCid))
             && (PS_PID_IMSA == g_PdpEntity[ucPdpId].stClientInfo.aulModuleId[ucCid]))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_CheckImsBearerByRabId (
    VOS_UINT32                          ulRabId
)
{
    VOS_UINT32                          ulCid;
    VOS_UINT8                           ucBitCidIndex;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (TAF_APS_STA_ACTIVE == TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            if (ulRabId != g_PdpEntity[ucPdpId].ucNsapi)
            {
                continue;
            }

            /* 目前只支持关联IMSA发起的IMS承载的专有承载 */
            for (ucBitCidIndex = 0; ucBitCidIndex <= TAF_MAX_CID; ucBitCidIndex++)
            {
                ulCid = (VOS_UINT32)0x00000001 << ucBitCidIndex;
                if ((0 != (g_PdpEntity[ucPdpId].stClientInfo.ulBitCidMask & ulCid))
                 && (PS_PID_IMSA == g_PdpEntity[ucPdpId].stClientInfo.aulModuleId[ucBitCidIndex]))
                {
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}


VOS_VOID TAF_APS_GetImsBearerCid (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucCid
)
{
    VOS_UINT32                          ulCid;
    VOS_UINT8                           ucBitCidIndex;

    for (ucBitCidIndex = 0; ucBitCidIndex <= TAF_MAX_CID; ucBitCidIndex++)
    {
        ulCid = (VOS_UINT32)0x00000001 << ucBitCidIndex;
        if ((PS_PID_IMSA == g_PdpEntity[ucPdpId].stClientInfo.aulModuleId[ucBitCidIndex])
         && (0 != (g_PdpEntity[ucPdpId].stClientInfo.ulBitCidMask & ulCid)))
        {
            *pucCid = ucBitCidIndex;
            return;
        }
    }
    return;
}
#endif


VOS_UINT32 TAF_APS_IsPdpEntBitCidMaskExit (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulCid;

    ulCid = (VOS_UINT32)0x00000001 << ucCid;
    if (0 != (g_PdpEntity[ucPdpId].stClientInfo.ulBitCidMask & ulCid))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_VOID TAF_APS_GetPdpEntBitCidInfo(
    VOS_UINT8                           ucPdpId,
    TAF_APS_BITCID_INFO_STRU           *pstCid
)
{
    VOS_UINT8                           ucBitCidIndex;

    pstCid->ulNum = 0;

    if (VOS_TRUE == g_PdpEntity[ucPdpId].ulUsedFlg)
    {
        /* 由于是32位的数据长度，因此查找32位中的每一个bit */
        for (ucBitCidIndex = 0; ucBitCidIndex <= TAF_MAX_CID; ucBitCidIndex++)
        {
            /* 查看当前哪个一个BIT上是有值的，就认为这个是当前的CID定义 */
            if (0 != (g_PdpEntity[ucPdpId].stClientInfo.ulBitCidMask & ((VOS_UINT32)0x00000001 << ucBitCidIndex)))
            {
                /* BIT1代表CID 0，BIT32代表CID 31 */
                pstCid->aucCid[pstCid->ulNum] = ucBitCidIndex;
                pstCid->ulNum ++;
            }
        }
    }

}


VOS_VOID TAF_APS_SetPdpEntAttachBearerFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucFlag
)
{
    g_PdpEntity[ucPdpId].ucDefaultBearerFlag = ucFlag;
}


VOS_UINT8 TAF_APS_GetPdpEntAttachBearerFlag (
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].ucDefaultBearerFlag;
}


VOS_UINT32  TAF_APS_GetTiFromPdpId(
    VOS_UINT8                           ucPdpId,
    SM_TAF_TRANS_ID_STRU               *pstTi
)
{
    VOS_UINT8                           i;

    for(i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if ( (ucPdpId == g_PdpEntity[i].ucPdpId)
            &&  (VOS_TRUE == g_PdpEntity[i].ulUsedFlg))
        {
            /*找到了相同的CID,并且该项是正在使用的,则为找到了正确的项*/
            *pstTi = g_PdpEntity[i].stTransId;
            return VOS_OK;
        }

    }
    return VOS_ERR;
}


VOS_UINT32  TAF_APS_GetPdpIdFromTi(
    SM_TAF_TRANS_ID_STRU               *pstTi,
    VOS_UINT8                          *pucPdpId
)
{
    VOS_UINT8                           i;


    for(i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if ( (VOS_TRUE == g_PdpEntity[i].ulUsedFlg)
          && (pstTi->ucTiFlag== g_PdpEntity[i].stTransId.ucTiFlag)
          && (pstTi->ucTiValue== g_PdpEntity[i].stTransId.ucTiValue))

        {
            /*找到了相同的CID,并且该项是正在使用的,则为找到了正确的项*/
            *pucPdpId = g_PdpEntity[i].ucPdpId;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_VOID  TAF_APS_SetPdpEntityTi(
    VOS_UINT8                           ucPdpId,
    SM_TAF_TRANS_ID_STRU               *pstTi
)
{
    g_PdpEntity[ucPdpId].bitOpTransId = VOS_TRUE;

    g_PdpEntity[ucPdpId].stTransId    = *pstTi;
}


VOS_UINT8 TAF_APS_GetCidFromLteBitCid(
    VOS_UINT32                          ulBitCid
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucBitCidIndex;

    /*
        根据当前与L4A的接口，转换成APS内部定义的Cid，由于是32位的数据长度，
        因此查找32位中的每一个bit
    */
    ucCid = TAF_INVALID_CID;
    for (ucBitCidIndex = 0; ucBitCidIndex < TAF_APS_32BIT_DATA_LEN; ucBitCidIndex++)
    {
        /* 查看当前哪个一个BIT上是有值的，就认为这个是当前的CID定义 */
        if (ulBitCid & ((VOS_UINT32)0x00000001 << ucBitCidIndex))
        {
            /* BIT1代表CID 0，BIT32代表CID 31 */
            ucCid = ucBitCidIndex;
            break;
        }
    }

    return ucCid;
 }


VOS_UINT32  TAF_APS_GetActivedCid(VOS_UINT8 * pucActivedCid)
{
    VOS_UINT8                           i;
    TAF_APS_STA_ENUM_UINT32             enState;
    VOS_UINT8                           j;
    TAF_APS_BITCID_INFO_STRU                     stCid;

    if (VOS_NULL_PTR == pucActivedCid)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pucActivedCid, 0x00, TAF_MAX_CID + 1);

    /* PDP ID有效范围是0-6 */
    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        PS_MEM_SET(&stCid, 0x00, sizeof(TAF_APS_BITCID_INFO_STRU));
        /* 如果当前的CID是无效值，则跳过 */
        TAF_APS_GetPdpEntBitCidInfo(i, &stCid);
        if (0 == stCid.ulNum)
        {
            continue;
        }

        /* 查看当前使用的PDP ID所对应实体的状态，如果在激活、modify过程中，
        去激活过程中，此时认为实体是激活的 */
        enState = TAF_APS_GetPdpIdMainFsmState(i);
        if ( (TAF_APS_STA_ACTIVE == enState)
          || (TAF_APS_STA_MS_MODIFYING == enState)
          || (TAF_APS_STA_MS_DEACTIVATING == enState) )
        {
            for (j = 0; j < stCid.ulNum; j++)
            {
                pucActivedCid[stCid.aucCid[j]] = VOS_TRUE;
            }
        }
    }

    return VOS_OK;
}


TAF_APS_USER_CONN_STATUS_ENUM_UINT8 TAF_APS_GetUserConnStatus(VOS_VOID)
{
    VOS_UINT8                           i;
    TAF_APS_STA_ENUM_UINT32             enState;


    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(i))
        {
            continue;
        }

        /* 查看当前使用的PDP ID所对应实体的状态，如果在激活、modify过程中，
        去激活过程中，此时认为实体是激活的 */
        enState = TAF_APS_GetPdpIdMainFsmState(i);
        if ((TAF_APS_STA_ACTIVE == enState)
          || (TAF_APS_STA_MS_MODIFYING == enState)
          || (TAF_APS_STA_MS_DEACTIVATING == enState))
        {
            /* 如果不是默认承载建立的连接，以及是主PDP建立的连接都为存在PDP连接 */
            if ((TAF_APS_DEFAULT_CID != TAF_APS_GetPdpEntCurrCid(i))
              && (APS_PDP_ACT_PRI == TAF_APS_GetPdpEntActType(i)))
            {
                return TAF_APS_USER_CONN_EXIST;
            }
        }

    }

    return TAF_APS_USER_CONN_NOT_EXIST;
}


VOS_UINT32 TAF_APS_Ipv4AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          ulNumLen;
    VOS_UINT32                          ulDotNum;
    VOS_UINT32                          ulValTmp;
    VOS_UINT8                           aucAddr[TAF_IPV4_ADDR_LEN];

    ulStrLen = 0;
    ulNumLen = 0;
    ulDotNum = 0;
    ulValTmp = 0;
    PS_MEM_SET(aucAddr, 0x00 ,TAF_IPV4_ADDR_LEN);

    if ((VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber))
    {
        return VOS_ERR;
    }

    ulStrLen = VOS_StrLen(pcString);

    if (ulStrLen > VOS_StrLen("255.255.255.255"))
    {
        return VOS_ERR;
    }

    for (i = 0; i < ulStrLen; i++)
    {
        if ((pcString[i] >= '0') && (pcString[i] <= '9'))
        {
            ulValTmp = (ulValTmp * 10) + (pcString[i] - '0');

            ulNumLen++;
            continue;
        }
        else if (pcString[i] == '.')
        {
            if ( (0 == ulNumLen) || (ulNumLen > 3) )
            {
                return VOS_ERR;
            }

            if ( ulValTmp > 255 )
            {
                return VOS_ERR;
            }

            aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

            ulValTmp = 0;
            ulNumLen = 0;

            /* 统计'.'的个数 */
            ulDotNum++;

            continue;
        }
        else
        {
            /* 其他值直接返回失败 */
            return VOS_ERR;
        }
    }

    /* 如果不是3个'.'则返回失败 */
    if (3 != ulDotNum)
    {
        return VOS_ERR;
    }

    aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

    PS_MEM_CPY(pucNumber, aucAddr, TAF_IPV4_ADDR_LEN);

    return VOS_OK;
}


VOS_UINT32 TAF_APS_ValidatePdpType(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeReq,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeCnf
)
{
    if ((TAF_PDP_IPV4V6 == enPdpTypeReq)
     && ((TAF_PDP_IPV4V6 == enPdpTypeCnf)
      || (TAF_PDP_IPV4 == enPdpTypeCnf)
      || (TAF_PDP_IPV6 == enPdpTypeCnf)))
    {
        /* 请求的是IPV4V6类型,回复的类型可以为IPV4V6，IPV4，IPV6 */
        return VOS_OK;
    }
    else if((enPdpTypeReq == enPdpTypeCnf )
         && (TAF_PDP_TYPE_BUTT != enPdpTypeCnf))
    {
        /* 请求的PDP类型与回复的PDP类型一致，并且回复的类型不是TAF_PDP_TYPE_BUTT */
        return VOS_OK;
    }
    else
    {
    }

    return VOS_ERR;
}


VOS_UINT32 TAF_APS_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_CHAR                            astringTmp[8];

    PS_MEM_SET(astringTmp, 0x00, 8);

    if ((VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber))
    {
        return VOS_ERR;
    }
    else
    {
        PS_MEM_SET(pcString, 0, TAF_MAX_IPV4_ADDR_STR_LEN);
        /*lint -e586*/
        (VOS_VOID)sprintf(astringTmp, "%d", pucNumber[0]);
        (VOS_VOID)strcat(pcString, astringTmp);

        (VOS_VOID)sprintf(astringTmp, ".%d", pucNumber[1]);
        (VOS_VOID)strcat(pcString, astringTmp);

        (VOS_VOID)sprintf(astringTmp, ".%d", pucNumber[2]);
        (VOS_VOID)strcat(pcString, astringTmp);

        (VOS_VOID)sprintf(astringTmp, ".%d", pucNumber[3]);
        (VOS_VOID)strcat(pcString, astringTmp);
        /*lint +e586*/
    }

    return VOS_OK;
}



VOS_UINT8 TAF_APS_ConverUserDefPdpTypeToApsEntityPdpType (
    TAF_PDP_TYPE_ENUM_UINT8             enUserPdpType,
    VOS_UINT8                           ucDefaultPdpType
)
{
    if (TAF_PDP_IPV4V6 == enUserPdpType)
    {
        return ucDefaultPdpType;
    }

    if (TAF_PDP_IPV4 == enUserPdpType)
    {
        return APS_ADDR_STATIC_IPV4;
    }

    if (TAF_PDP_IPV6 == enUserPdpType)
    {
        return MN_APS_ADDR_IPV6;
    }

    return  APS_ADDR_STATIC_IPV4;
}


TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmcRatType (
    MMC_APS_RAT_TYPE_ENUM_UINT32       enRatType
)
{
    switch (enRatType)
    {
        case MMC_APS_RAT_TYPE_GSM:
            return TAF_APS_RAT_TYPE_GSM;

        case MMC_APS_RAT_TYPE_WCDMA:
            return TAF_APS_RAT_TYPE_WCDMA;

        case MMC_APS_RAT_TYPE_LTE:
            return TAF_APS_RAT_TYPE_LTE;

        default:
            return TAF_APS_RAT_TYPE_NULL;
    }
}


TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmaRatType (
    MMA_TAF_RAT_TYPE_ENUM_UINT32       enRatType
)
{
    switch (enRatType)
    {
        case MMA_TAF_RAT_TYPE_HRPD:
            return TAF_APS_RAT_TYPE_HRPD;

        case MMA_TAF_RAT_TYPE_EHRPD:
            return TAF_APS_RAT_TYPE_EHRPD;

        case MMA_TAF_RAT_TYPE_1X:
            return TAF_APS_RAT_TYPE_1X;

        case MMA_TAF_RAT_TYPE_GSM:
            return TAF_APS_RAT_TYPE_GSM;

        case MMA_TAF_RAT_TYPE_WCDMA:
            return TAF_APS_RAT_TYPE_WCDMA;

        case MMA_TAF_RAT_TYPE_LTE:
            return TAF_APS_RAT_TYPE_LTE;

        default:
            return TAF_APS_RAT_TYPE_NULL;
    }
}


TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmaRatTypeToApsRatType (
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType
)
{
    switch (enRatType)
    {
        case TAF_MMA_RAT_GSM:
            return TAF_APS_RAT_TYPE_GSM;

        case TAF_MMA_RAT_WCDMA:
            return TAF_APS_RAT_TYPE_WCDMA;

        case TAF_MMA_RAT_LTE:
            return TAF_APS_RAT_TYPE_LTE;

        case TAF_MMA_RAT_1X:
            return TAF_APS_RAT_TYPE_1X;

        case TAF_MMA_RAT_HRPD:
            return TAF_APS_RAT_TYPE_HRPD;

        default:
            return TAF_APS_RAT_TYPE_NULL;
    }
}


TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmaClServiceToApsRatType (
    MMA_TAF_RAT_TYPE_ENUM_UINT32       enRatType
)
{
    switch (enRatType)
    {
        case MMA_TAF_CL_STATUS_LTE_NORMAL_SERVICE:
            return TAF_APS_RAT_TYPE_LTE;

        case MMA_TAF_CL_STATUS_HRPD_NORMAL_SERVICE:
            return TAF_APS_RAT_TYPE_HRPD;

        case MMA_TAF_CL_STATUS_EHRPD_NORMAL_SERVICE:
            return TAF_APS_RAT_TYPE_EHRPD;

        default:
            return TAF_APS_GetCurrPdpEntityRatType();
    }
}



VOS_VOID TAF_APS_GetSpecPdpLinkedPdpInfo (
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList,
    VOS_UINT8                           ucNsapi
)
{
    VOS_UINT8                           i;

    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if (VOS_TRUE == g_PdpEntity[i].PdpNsapiFlag)
        {
            if (ucNsapi == g_PdpEntity[i].ucLinkedNsapi)
            {
                pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = i;
                pstPdpIdList->ucPdpNum++;
            }
        }
    }
}


TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapSmCause(
    SM_TAF_CAUSE_ENUM_UINT16            enSmCause
)
{
    TAF_APS_SM_ERR_CODE_MAP_STRU       *pstSmErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSmErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSmErrMapTblPtr = TAF_APS_GET_SM_ERR_CODE_MAP_TBL_PTR();
    ulSmErrMapTblSize = TAF_APS_GET_SM_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSmErrMapTblSize; ulCnt++)
    {
        if (pstSmErrMapTblPtr[ulCnt].enSmCause == enSmCause)
        {
            return pstSmErrMapTblPtr[ulCnt].enPsCuase;
        }
    }

    return TAF_PS_CAUSE_UNKNOWN;
}

#if (FEATURE_ON == FEATURE_LTE)

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapEsmCause(
    VOS_UINT32                          ulEsmCause
)
{
    TAF_APS_ESM_ERR_CODE_MAP_STRU      *pstEsmErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulEsmErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstEsmErrMapTblPtr = TAF_APS_GET_ESM_ERR_CODE_MAP_TBL_PTR();
    ulEsmErrMapTblSize = TAF_APS_GET_ESM_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulEsmErrMapTblSize; ulCnt++)
    {
        if (pstEsmErrMapTblPtr[ulCnt].ulEsmCause == ulEsmCause)
        {
            return pstEsmErrMapTblPtr[ulCnt].enPsCause;
        }
    }

    return TAF_PS_CAUSE_UNKNOWN;
}

#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapXccCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
)
{
    TAF_APS_XCC_ERR_CODE_MAP_STRU      *pstXccErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulXccErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstXccErrMapTblPtr = TAF_APS_GET_XCC_ERR_CODE_MAP_TBL_PTR();
    ulXccErrMapTblSize = TAF_APS_GET_XCC_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulXccErrMapTblSize; ulCnt++)
    {
        if (pstXccErrMapTblPtr[ulCnt].enXccCause == enXccCause)
        {
            return pstXccErrMapTblPtr[ulCnt].enPsCause;
        }
    }

    return TAF_PS_CAUSE_UNKNOWN;
}


TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapHsmCause(
    HSM_APS_CAUSE_ENUM_UINT32           enHsmCause
)
{
    TAF_APS_HSM_ERR_CODE_MAP_STRU      *pstHsmErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulHsmErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstHsmErrMapTblPtr = TAF_APS_GET_HSM_ERR_CODE_MAP_TBL_PTR();
    ulHsmErrMapTblSize = TAF_APS_GET_HSM_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulHsmErrMapTblSize; ulCnt++)
    {
        if (pstHsmErrMapTblPtr[ulCnt].enHsmCause == enHsmCause)
        {
            return pstHsmErrMapTblPtr[ulCnt].enPsCause;
        }
    }

    return TAF_PS_CAUSE_UNKNOWN;
}


TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapEhsmCause(
    EHSM_APS_CAUSE_ENUM_UINT32          enEhsmCause
)
{
    TAF_APS_EHSM_ERR_CODE_MAP_STRU     *pstEhsmErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulEhsmErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstEhsmErrMapTblPtr = TAF_APS_GET_EHSM_ERR_CODE_MAP_TBL_PTR();
    ulEhsmErrMapTblSize = TAF_APS_GET_EHSM_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulEhsmErrMapTblSize; ulCnt++)
    {
        if (pstEhsmErrMapTblPtr[ulCnt].enEhsmCause == enEhsmCause)
        {
            return pstEhsmErrMapTblPtr[ulCnt].enPsCause;
        }
    }

    return TAF_PS_CAUSE_UNKNOWN;
}


VOS_UINT8   TAF_APS_GetPdpIdByCallId(
    VOS_UINT8                           ucCallId
)
{
    if ( (ucCallId < TAF_MIN_CALLID)
      || (ucCallId > TAF_MAX_CALLID))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_GetPdpIdByCallId Wrong call id:", ucCallId);
        return TAF_APS_INVALID_PDPID;
    }

    if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucCallId - 1))
    {
        return (VOS_UINT8)(ucCallId - 1);
    }

    return TAF_APS_INVALID_PDPID;
}



VOS_UINT32 TAF_APS_Is1xRedialCause(
    TAF_PS_CAUSE_ENUM_UINT32                enCause,
    TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8    enType
)
{
    VOS_UINT8                           ucIsNeedReidal;

    /* 先判断原因值是否满足重拨条件 */
    switch (enCause)
    {
        case TAF_PS_CAUSE_XCC_AS_NO_SERVICE:
        case TAF_PS_CAUSE_XCC_AS_MAX_ACCESS_PROBES:
        case TAF_PS_CAUSE_XCC_AS_REORDER:
        case TAF_PS_CAUSE_XCC_AS_ACCESS_DENIED:
        case TAF_PS_CAUSE_XCC_AS_ACCT_BLOCK:
        case TAF_PS_CAUSE_XCC_AS_NDSS:
        case TAF_PS_CAUSE_XCC_AS_REDIRECTION:
        case TAF_PS_CAUSE_XCC_AS_ACCESS_IN_PROGRESS:
        case TAF_PS_CAUSE_XCC_AS_ACCESS_FAIL:
        case TAF_PS_CAUSE_XCC_AS_ABORT:
        case TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_ACH:
        case TAF_PS_CAUSE_XCC_AS_CHANNEL_ASSIGN_TIMEOUT:
        case TAF_PS_CAUSE_XCC_CCS_NOT_SUPPORT:
        case TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MO_CALL:
        case TAF_PS_CAUSE_XCC_ABORTED_BY_RECEIVED_MT_CALL:
        case TAF_PS_CAUSE_XCC_CAUSE_NO_RF:
        case TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_TCH:
            return VOS_TRUE;

        default:
            ucIsNeedReidal = VOS_FALSE;
            break;
    }

    /* 始呼或者上行数据触发的建链需要增加以下重播原因 */
    if (TAF_APS_CDATA_REDIAL_TYPE_DRS_TRUE == enType)
    {
        switch (enCause)
        {
            case TAF_PS_CAUSE_XCC_AS_MS_NORMAL_RELEASE:
            case TAF_PS_CAUSE_XCC_AS_SO_REJ:
            case TAF_PS_CAUSE_XCC_AS_NW_NORMAL_RELEASE:
                ucIsNeedReidal = VOS_TRUE;
                break;

            default:
                ucIsNeedReidal = VOS_FALSE;
                break;
        }
    }
    return ucIsNeedReidal;
}


VOS_UINT8 TAF_APS_IsHrpdRedialCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    switch(enCause)
    {
        case TAF_PS_CAUSE_HSM_AS_MAX_ACCESS_PROBES:
        case TAF_PS_CAUSE_HSM_AS_CONNECTION_DENY:
        case TAF_PS_CAUSE_HSM_AS_RTC_RTCACK_FAILURE:
        case TAF_PS_CAUSE_HSM_AS_SIGNAL_FADE:
        case TAF_PS_CAUSE_HSM_AS_CONNECTION_EXIST:
        case TAF_PS_CAUSE_HSM_AS_NO_RF:
        case TAF_PS_CAUSE_HSM_AS_CAN_NOT_EST_CONN:
        case TAF_PS_CAUSE_HSM_AS_SESSION_NOT_EXIST:
        case TAF_PS_CAUSE_HSM_AS_HRPD_SLAVE:
        case TAF_PS_CAUSE_HSM_AS_IN_UATI_PROCEDURE:
        case TAF_PS_CAUSE_HSM_AS_IN_SCP_PROCEDURE:
        case TAF_PS_CAUSE_HSM_AS_REDIRECT:
        case TAF_PS_CAUSE_HSM_AS_HRPD_PREFER_CH_NOT_VALID:

            return VOS_TRUE;

        default:

            return VOS_FALSE;
    }
}




VOS_UINT32 TAF_APS_IsNeedSilentRedial(
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatMode
)
{
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8    enType;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();
    enType  = TAF_APS_IsNeedRedialEventType(pstEntryMsg->ulEventType);

    /* 用户去激活不需要重播,1X切换到LTE也不需要重播 */
    if (TAF_APS_CDATA_REDIAL_TYPE_NONE == enType)
    {
        return VOS_FALSE;
    }

    if (TAF_APS_RAT_TYPE_1X == enRatMode)
    {
        /* 如果激活失败原因值不满足重拨条件，返回VOS_FALSE */
        if (VOS_FALSE == TAF_APS_Is1xRedialCause(enCause, enType))
        {
            return VOS_FALSE;
        }
    }
    else if (TAF_APS_RAT_TYPE_HRPD == enRatMode)
    {
        /* 如果激活失败原因值不满足重拨条件，返回VOS_FALSE */
        if (VOS_FALSE == TAF_APS_IsHrpdRedialCause(enCause))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_FALSE;
    }

    /* 获取TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD定时器剩余时长 */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                              ucPdpId,
                              &ulRemainTimeLen);

    /* 若TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD剩余时长大于或等于4s，满足重拨条件 */
    if (ulRemainTimeLen < TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_IsNeedRedial1xSystemAcquire(
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    VOS_INT32                           lRssi
)
{
    /* 根据CDG 143，以下原因值触发重拨时搜网 */
    switch (enCause)
    {
        case TAF_PS_CAUSE_XCC_AS_REORDER:
        case TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_ACH:
        case TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_TCH:
        case TAF_PS_CAUSE_XCC_AS_CHANNEL_ASSIGN_TIMEOUT:
            if (lRssi > -100 )
            {
                return VOS_FALSE;
            }
        case TAF_PS_CAUSE_XCC_AS_MAX_ACCESS_PROBES:
        case TAF_PS_CAUSE_XCC_AS_ACCESS_DENIED:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }

}


VOS_VOID TAF_APS_CdataOrigRedialCount(
    VOS_UINT8                           ucPdpId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucReOrigCount;

    pstPdpEntity  = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucReOrigCount = TAF_APS_GetPdpEntReOrigCount(ucPdpId);

    /* 记录是否是L2失败原因导致的重拨 */
    if (TAF_XCC_FAIL_LAYER_L2 == enFailLayer)
    {
        TAF_APS_SetPdpEntL2ErrReOrigFlag(ucPdpId, VOS_TRUE);

        if (TAF_XCC_FAIL_LAYER_L3 != pstPdpEntity->stCdataInfo.enLastReOrigErr)
        {
            /*原因值相同, 或者第一次重拨失败，则重拨计数累加 */
            if (ucReOrigCount < TAF_APS_MAX_ORIG_REDIAL_COUNT)
            {
            TAF_APS_SetPdpEntReOrigCount(ucPdpId, ucReOrigCount + 1);
            }
        }
        else
        {
            /*原因值不同则重新重1开始计数*/
            TAF_APS_SetPdpEntReOrigCount(ucPdpId, 1);
        }

        pstPdpEntity->stCdataInfo.enLastReOrigErr = TAF_XCC_FAIL_LAYER_L2;

    }
    else
    {
        TAF_APS_SetPdpEntL2ErrReOrigFlag(ucPdpId, VOS_FALSE);

        if (TAF_XCC_FAIL_LAYER_L2 != pstPdpEntity->stCdataInfo.enLastReOrigErr)
        {
            if (ucReOrigCount < TAF_APS_MAX_ORIG_REDIAL_COUNT)
            {
                TAF_APS_SetPdpEntReOrigCount(ucPdpId, ucReOrigCount + 1);
            }
        }
        else
        {
            TAF_APS_SetPdpEntReOrigCount(ucPdpId, 1);
        }

        pstPdpEntity->stCdataInfo.enLastReOrigErr = TAF_XCC_FAIL_LAYER_L3;
    }

    return;
}



VOS_UINT32 TAF_APS_IsNeedRedialHrpdSystemAcquire(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    /* 根据CDG 143，以下原因值触发重拨时搜网 */
    switch (enCause)
    {
        case TAF_PS_CAUSE_HRPD_NO_SERVICE:
     /* 目前以下原因值暂不搜网，靠HSD的自动触发来完成
        case TAF_PS_CAUSE_HSM_AS_MAX_ACCESS_PROBES:
        case TAF_PS_CAUSE_HSM_AS_CONNECTION_DENY:
        case TAF_PS_CAUSE_HSM_AS_RTC_RTCACK_FAILURE:
        case TAF_PS_CAUSE_HSM_AS_SIGNAL_FADE:
     */
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }

}



VOS_UINT8 TAF_APS_IsNeedRedialImmediately(
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    VOS_INT32                           lRssi
)
{
    switch(enCause)
    {
        case TAF_PS_CAUSE_XCC_AS_REORDER:
        case TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_ACH:
        case TAF_PS_CAUSE_XCC_AS_SIGNAL_FADE_IN_TCH:
        case TAF_PS_CAUSE_XCC_AS_CHANNEL_ASSIGN_TIMEOUT:
            if (lRssi <= -100)
            {
                return VOS_TRUE;
            }

        case TAF_PS_CAUSE_HSM_AS_MAX_ACCESS_PROBES:
        case TAF_PS_CAUSE_HSM_AS_CONNECTION_DENY:
        case TAF_PS_CAUSE_HSM_AS_RTC_RTCACK_FAILURE:
        case TAF_PS_CAUSE_HSM_AS_SIGNAL_FADE:
            return VOS_FALSE;

        default:
            /* TAF_PS_CAUSE_XCC_AS_NO_SERVICE */
            /* TAF_PS_CAUSE_XCC_AS_MAX_ACCESS_PROBES */
            /* TAF_PS_CAUSE_XCC_AS_ACCESS_DENIED */
            return VOS_TRUE;
    }
}


TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8 TAF_APS_IsNeedRedialEventType(
    VOS_UINT32            ulEventType
)
{
    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):

        case TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_RECONN_IND):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):

            return TAF_APS_CDATA_REDIAL_TYPE_DRS_TRUE;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):

            return TAF_APS_CDATA_REDIAL_TYPE_DRS_FALSE;

        default:
            break;
    }

    /* 1X切换到LTE也不需要重播 */
    return TAF_APS_CDATA_REDIAL_TYPE_NONE;
}




TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_MapCdataBearStatus(
    VOS_UINT8                           ucPdnId
)
{
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 enTafPsCdataBearStatus;
    VOS_UINT32                          ulState;

    ulState = TAF_APS_GetPdpIdMainFsmState(ucPdnId);
    switch (ulState)
    {
        case TAF_APS_STA_INACTIVE:
            enTafPsCdataBearStatus = TAF_PS_CDATA_BEAR_STATUS_INACTIVE;
            break;

        case TAF_APS_STA_ACTIVE:
            enTafPsCdataBearStatus = TAF_PS_CDATA_BEAR_STATUS_ACTIVE;
            break;

        case TAF_APS_STA_DORMANT:
            if (VOS_TRUE == TAF_APS_IsExistXcallOrXsmsOpreation())
            {
                enTafPsCdataBearStatus = TAF_PS_CDATA_BEAR_STATUS_SUSPEND;
            }
            else
            {
                enTafPsCdataBearStatus = TAF_PS_CDATA_BEAR_STATUS_IDLE;
            }
            break;

        default :
            enTafPsCdataBearStatus = TAF_PS_CDATA_BEAR_STATUS_SUSPEND;
    }

    return enTafPsCdataBearStatus;
}

TAF_APS_CDATA_PS_STATE_ENUM_UINT8 AT_APS_ConvertPsCdataStatusToCsdCdataStatus(
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8                     enPsCdataStatus
)
{
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8                       enCdsCdataBearStatus;

    switch (enPsCdataStatus)
    {
        case TAF_PS_CDATA_BEAR_STATUS_INACTIVE:
            enCdsCdataBearStatus = APS_CDS_CDATA_BEAR_STATUS_INACTIVE;
            break;

        case TAF_PS_CDATA_BEAR_STATUS_ACTIVE:
            enCdsCdataBearStatus = APS_CDS_CDATA_BEAR_STATUS_ACTIVE;
            break;

        case TAF_PS_CDATA_BEAR_STATUS_IDLE:
            enCdsCdataBearStatus = APS_CDS_CDATA_BEAR_STATUS_IDLE;
            break;

        case TAF_PS_CDATA_BEAR_STATUS_SUSPEND:
            enCdsCdataBearStatus = APS_CDS_CDATA_BEAR_STATUS_SUSPEND;
            break;

        default :
            enCdsCdataBearStatus = APS_CDS_CDATA_BEAR_STATUS_SUSPEND;
    }

    return enCdsCdataBearStatus;
}


VOS_UINT8 TAF_APS_MapEhsmPdnTypeToAps(
    EHSM_APS_PDN_TYPE_ENUM_UINT8        enPdnType
)
{
    switch (enPdnType)
    {
        case EHSM_APS_PDN_TYPE_IPV4:
            return APS_ADDR_STATIC_IPV4;

        case EHSM_APS_PDN_TYPE_IPV6:
            return MN_APS_ADDR_IPV6;

        case EHSM_APS_PDN_TYPE_IPV4V6:
            return MN_APS_ADDR_IPV4V6;

        default :
            return APS_ADDR_INVALID;
    }
}

VOS_UINT8 TAF_APS_MapPppPdnTypeToAps(
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8                        enPdnType
)
{
    switch (enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            return APS_ADDR_STATIC_IPV4;

        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            return MN_APS_ADDR_IPV6;

        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            return MN_APS_ADDR_IPV4V6;

        default :
            return APS_ADDR_INVALID;
    }
}

#endif


TAF_PDP_TYPE_ENUM_UINT8 TAF_APS_ConvertPdpType(VOS_UINT8 ucPdpTypeNum)
{
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    /* 转换APS内部PDP类型至TAF外部PDP类型 */
    switch (ucPdpTypeNum)
    {
        case APS_ADDR_STATIC_IPV4:
            enPdpType = TAF_PDP_IPV4;
            break;

        case APS_ADDR_PPP:
            enPdpType = TAF_PDP_PPP;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case MN_APS_ADDR_IPV6:
            enPdpType = TAF_PDP_IPV6;
            break;

        case MN_APS_ADDR_IPV4V6:
            enPdpType = TAF_PDP_IPV4V6;
            break;
#endif

        default:
            enPdpType = TAF_PDP_IPV4;
            break;
    }

    return enPdpType;
}


VOS_UINT32 TAF_APS_GetCtrlHdrFromCmdBufferQueue(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimer,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo   = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    if (VOS_NULL_PTR == pstCtrl)
    {
        return VOS_FALSE;
    }

    /* 从缓冲队列中获取消息 */
    pstMsgInfo = TAF_APS_GetItemFromCmdBufferQueue(enTimer, ulPara);

    if (VOS_NULL_PTR == pstMsgInfo)
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_GetCtrlHdrFromCmdBufferQueue: Get message info failed!");
        return VOS_FALSE;
    }

    ulLength = PS_MIN(pstMsgInfo->ulMsgInfoLen , sizeof(TAF_CTRL_STRU));
    PS_MEM_CPY((VOS_UINT8 *)pstCtrl, (VOS_UINT8 *)pstMsgInfo->pulMsgInfo, ulLength);

    return VOS_TRUE;

}


#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID TAF_APS_PsCallFailErrRecord(TAF_PS_CAUSE_ENUM_UINT32 enCause)
{
    NAS_ERR_LOG_PS_CALL_FAIL_EVENT_STRU                     stPsCallFailEvent;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU                        *pstCurPdpEntityFsmCtx = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PS_CALL_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 不需要记录或没有异常时，不保存异常信息 */
    if ((VOS_FALSE == ulIsLogRecord)
     || (TAF_PS_CAUSE_SUCCESS == enCause)
     || (TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION == enCause))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PS_CALL_FAIL_EVENT_STRU);

    /* 获取当前状态机信息 */
    pstCurPdpEntityFsmCtx = TAF_APS_GetCurrPdpEntityFsmAddr();

    /* 填充PS呼叫失败异常信息 */
    PS_MEM_SET(&stPsCallFailEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stPsCallFailEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_PS_CALL_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stPsCallFailEvent.ulPsCause                      = enCause;
    stPsCallFailEvent.ulPsRegState                   = (VOS_UINT32)TAF_SDC_GetPsServiceStatus();
    stPsCallFailEvent.stApsFsmInfo.stMainFsm.ulFsmId = pstCurPdpEntityFsmCtx->stMainFsm.enFsmId;
    stPsCallFailEvent.stApsFsmInfo.stMainFsm.ulState = pstCurPdpEntityFsmCtx->stMainFsm.ulState;
    stPsCallFailEvent.stApsFsmInfo.stSubFsm.ulFsmId  = pstCurPdpEntityFsmCtx->stSubFsm.enFsmId;
    stPsCallFailEvent.stApsFsmInfo.stSubFsm.ulState  = pstCurPdpEntityFsmCtx->stSubFsm.ulState;
    stPsCallFailEvent.stApsFsmInfo.ucPdpId           = pstCurPdpEntityFsmCtx->ucPdpId;

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stPsCallFailEvent.stPositionInfo);

    /* 获取当前Usim信息 */
    NAS_MMA_OutputUsimInfo(&stPsCallFailEvent.stUsimInfo);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stPsCallFailEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_PsCallFailErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PS_CALL_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stPsCallFailEvent,
                           sizeof(stPsCallFailEvent));
    return;
}
#endif


VOS_VOID   TAF_APS_SetPsCallEvtCtrl(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_CTRL_STRU                      *pstCtrl
)
{
    pstCtrl->ulModuleId     = g_PdpEntity[ucPdpId].stClientInfo.aulModuleId[ucCid];
    pstCtrl->usClientId     = g_PdpEntity[ucPdpId].stClientInfo.ausClientId[ucCid];
    pstCtrl->ucOpId         = g_PdpEntity[ucPdpId].stClientInfo.aucId[ucCid];

}


VOS_INT32 TAF_APS_CompareApn(
    const VOS_UINT8                 aucBearerApn[],
    VOS_UINT8                       ucBearerApnLen,
    const VOS_UINT8                 aucUserApn[],
    VOS_UINT8                       ucUserApnLen
)
{
    VOS_UINT8                       i;
    VOS_UINT8                       ucChar1;
    VOS_UINT8                       ucChar2;

    /* 检查APN长度, 承载的APN会携带MNC和MCC信息 */
    if (ucBearerApnLen < ucUserApnLen)
    {
        return VOS_ERROR;
    }

    /* 逐个字节比较用户和承载的APN */
    for (i = 0; i < ucUserApnLen; i++)
    {
        ucChar1 = UPCASE(aucBearerApn[i]);
        ucChar2 = UPCASE(aucUserApn[i]);

        if (ucChar1 != ucChar2)
        {
            return VOS_ERROR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_MatchCallWithAllBearer(
    CONST TAF_CTRL_STRU                *pstCtrl,
    CONST TAF_APS_MATCH_PARAM_STRU     *pstMatchParam,
    VOS_UINT8                          *pucPdpId
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT8                          *pucPdpEntApnValue = VOS_NULL_PTR;
    VOS_UINT8                          *pucUsrApnValue = VOS_NULL_PTR;
    VOS_UINT8                           aucApn[APS_MAX_LENGTH_OF_APN];
    VOS_UINT8                           ucPdpEntApnLen;
    VOS_UINT8                           ucUsrApnLen;
    VOS_UINT8                           ucPdpId;
    TAF_APS_STA_ENUM_UINT32             enState;

    PS_MEM_SET(aucApn, 0x00, APS_MAX_LENGTH_OF_APN);

    /* 检查承载类型是否匹配 */
    if (VOS_TRUE != pstMatchParam->ucPrimaryPdpFlg)
    {
        return VOS_FALSE;
    }

    /* 用户APN必须携带 */
    if (0 == pstMatchParam->stApn.ucLength)
    {
        return VOS_FALSE;
    }

    /* 拨号参数中的APN转换成网络协议格式 */
    Taf_LenStr2Apn(&pstMatchParam->stApn, aucApn);

    /* 遍历所有实体, 匹配拨号参数 */
    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ( ((TAF_APS_STA_ACTIVE == enState)
           || (TAF_APS_STA_MS_MODIFYING == enState)
           || (TAF_APS_STA_MS_DEACTIVATING == enState))
          && (VOS_TRUE != g_PdpEntity[ucPdpId].PdpNsapiFlag) )
        {
            continue;
        }

        /* 检查承载的IP类型是否匹配 */
        if (VOS_TRUE != TAF_APS_CheckBearerPdpTypeSuitable(
                                    TAF_APS_GetPdpEntPdpAddrType(ucPdpId),
                                    pstMatchParam->enPdpType))
        {
            continue;
        }

        /* 检查紧急承载的类型是否匹配 */
        if (TAF_APS_GetPdpEntEmcFlg(ucPdpId) != pstMatchParam->enEmergencyInd)
        {
            continue;
        }

        /* 提取网络协议格式APN总长度和内容 */
        pucUsrApnValue = &aucApn[1];
        ucUsrApnLen    = aucApn[0];

        /* 检查承载的APN是否匹配 */
        if (VOS_TRUE == TAF_APS_GetPdpEntApnFlag(ucPdpId))
        {
            pucPdpEntApnValue = TAF_APS_GetPdpEntApnValue(ucPdpId);
            ucPdpEntApnLen    = TAF_APS_GetPdpEntApnLen(ucPdpId);

            /* 比较APN内容 */
            if (VOS_OK == TAF_APS_CompareApn(pucPdpEntApnValue,
                                             ucPdpEntApnLen,
                                             pucUsrApnValue,
                                             ucUsrApnLen))
            {
                if ( (PS_PID_IMSA != TAF_APS_GetPdpEntModuleId(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId)))
                  && (PS_PID_IMSA != pstCtrl->ulModuleId) )
                {
                    return VOS_FALSE;
                }

                *pucPdpId = ucPdpId;
                return VOS_TRUE;
            }
        }
    }
#endif

    return VOS_FALSE;
}


VOS_VOID TAF_APS_SetPdpEntAddrType(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (TAF_PDP_IPV4 == enPdpType)
    {
        pstPdpEntity->PdpAddrFlag          = VOS_TRUE;
        pstPdpEntity->PdpAddr.ucPdpTypeNum = APS_ADDR_STATIC_IPV4;
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == enPdpType)
    {
        pstPdpEntity->PdpAddrFlag          = VOS_TRUE;
        pstPdpEntity->PdpAddr.ucPdpTypeNum = MN_APS_ADDR_IPV6;
    }
    else if (TAF_PDP_IPV4V6 == enPdpType)
    {
        pstPdpEntity->PdpAddrFlag          = VOS_TRUE;
        pstPdpEntity->PdpAddr.ucPdpTypeNum = MN_APS_ADDR_IPV4V6;
    }
#endif
    else
    {
        pstPdpEntity->PdpAddrFlag          = VOS_TRUE;
        pstPdpEntity->PdpAddr.ucPdpTypeNum = APS_ADDR_STATIC_IPV4;
    }
}


VOS_UINT32 TAF_APS_IsAnyBearerExist(VOS_VOID)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if ( (VOS_TRUE == pstPdpEntity->ulUsedFlg)
          && (VOS_TRUE == pstPdpEntity->PdpNsapiFlag)
          && (APS_JUDGE_NSAPI_VALID(pstPdpEntity->ucNsapi)) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 TAF_APS_IsAttachBearerExist(VOS_VOID)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (VOS_TRUE == pstPdpEntity->ucDefaultBearerFlag)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_IsPdnCntxtValid(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntxt)
{
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_FALSE;

    if (VOS_NULL_PTR == pstPdnCntxt)
    {
        return ulRslt;
    }

    if (VOS_TRUE == pstPdnCntxt->ulUsedFlg)
    {
        ulRslt = VOS_TRUE;
    }

    return ulRslt;
}


VOS_UINT32 TAF_APS_IsPdnCntxtDefault(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntxt)
{
    if (VOS_FALSE == TAF_APS_IsPdnCntxtValid(pstPdnCntxt))
    {
        return VOS_FALSE;
    }

    return pstPdnCntxt->ucDefaultBearerFlag;
}


VOS_UINT32 TAF_APS_IsAnyOtherNormalPdnActive(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntxt)
{
    TAF_APS_PDN_CONTEXT_STRU           *pstLocalPdnCntx = VOS_NULL_PTR;
    TAF_APS_STA_ENUM_UINT32             enState;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        pstLocalPdnCntx = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* 过滤相同PDN连接上下文 */
        if (pstLocalPdnCntx == pstPdnCntxt)
        {
            continue;
        }

        /* 过滤无效PDN连接上下文 */
        if (VOS_FALSE == TAF_APS_IsPdnCntxtValid(pstLocalPdnCntx))
        {
            continue;
        }

        /* 过滤紧急PDN连接上下文, 先预留 */


        /* 检查PDN连接是否处于激活状态 */
        enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ( ((TAF_APS_STA_ACTIVE == enState) || (TAF_APS_STA_MS_MODIFYING == enState))
          && (APS_PDP_ACT_PRI == pstLocalPdnCntx->ActType) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_UINT32 TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntxt)
{
    TAF_APS_PDN_TEARDOWN_POLICY_STRU   *pstPdnTeardownPolicy = VOS_NULL_PTR;
    VOS_UINT32                          ulTeardown;

    pstPdnTeardownPolicy = TAF_APS_GetPdnTeardownPolicy();
    ulTeardown           = VOS_FALSE;

    /* 专用承载不适用该策略 */
    if (APS_PDP_ACT_PRI != pstPdnCntxt->ActType)
    {
        return VOS_TRUE;
    }

    /* 缺省承载断开策略 */
    if (VOS_TRUE == TAF_APS_IsPdnCntxtDefault(pstPdnCntxt))
    {
        if (VOS_TRUE == pstPdnTeardownPolicy->ucAllowDefPdnTeardownFlg)
        {
            if (VOS_TRUE == TAF_APS_IsAnyOtherNormalPdnActive(pstPdnCntxt))
            {
                ulTeardown = VOS_TRUE;
            }
        }
    }
    else
    {
        /*
         * 非缺省PDN连接, 默认允许断开, 无需判断当前是否有其他PDN连接存在
         * 注: 后续这里可以考虑增加允许断开的定制条件
         */
        ulTeardown = VOS_TRUE;
    }

    return ulTeardown;
}
#endif


VOS_UINT8 TAF_APS_GetAttachAllowFlg(VOS_VOID)
{
    return NAS_MML_GetPsAttachAllowFlg();
}


VOS_UINT8 TAF_APS_IsT3402Running(VOS_VOID)
{
    if (NAS_MML_TIMER_START == NAS_MML_GetT3402Status())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID TAF_APS_GenMatchParamByCidInfo(
    CONST TAF_PDP_TABLE_STRU           *pstPdpTblInfo,
    TAF_APS_MATCH_PARAM_STRU           *pstMatchParam
)
{
    /* 缺省承载标识 */
    pstMatchParam->ucPrimaryPdpFlg = (VOS_TRUE == pstPdpTblInfo->ucPriCidFlag)?
                                     VOS_FALSE : VOS_TRUE;

    /* IP类型 */
    pstMatchParam->enPdpType       = pstPdpTblInfo->CidTab.stPdpAddr.enPdpType;

    /* 承载类型 */
    pstMatchParam->enEmergencyInd  = pstPdpTblInfo->CidTab.enEmergencyInd;

    /* APN信息 */
    PS_MEM_CPY(&pstMatchParam->stApn, &pstPdpTblInfo->CidTab.stApn, sizeof(TAF_PDP_APN_STRU));

    PIH_GetVsimAPN(TAF_MAX_APN_LEN, pstMatchParam->stApn.aucValue, &pstMatchParam->stApn.ucLength);

    return;
}


VOS_VOID TAF_APS_GenMatchParamByDailInfo(
    CONST TAF_PS_DIAL_PARA_STRU        *pstDialParaInfo,
    TAF_APS_MATCH_PARAM_STRU           *pstMatchParam
)
{
    /* Primary PDP标识 */
    pstMatchParam->ucPrimaryPdpFlg    = VOS_TRUE;

    /* IP类型 */
    pstMatchParam->enPdpType          = pstDialParaInfo->enPdpType;

    /* 承载类型 */
    if (VOS_TRUE == pstDialParaInfo->bitOpEmergencyInd)
    {
        pstMatchParam->enEmergencyInd = pstDialParaInfo->enEmergencyInd;
    }
    else
    {
        pstMatchParam->enEmergencyInd = TAF_PDP_NOT_FOR_EMC;
    }

    /* APN信息 */
    if (VOS_TRUE == pstDialParaInfo->bitOpApn)
    {
        pstMatchParam->stApn.ucLength = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstDialParaInfo->aucApn);
        PS_MEM_CPY(pstMatchParam->stApn.aucValue, pstDialParaInfo->aucApn, TAF_MAX_APN_LEN);
        PIH_GetVsimAPN(TAF_MAX_APN_LEN, pstMatchParam->stApn.aucValue, &pstMatchParam->stApn.ucLength);
    }
    else
    {
        pstMatchParam->stApn.ucLength = 0;
    }

    return;
}


VOS_VOID TAF_APS_SetPdpEntCdataPdnId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucPdnId
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.ucPdnId = ucPdnId;
}


VOS_UINT8 TAF_APS_GetPdpEntCdataPdnId(
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.ucPdnId;
}




VOS_VOID TAF_APS_SetPdpEntCdataPsState (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enPsState
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.enPsState = enPsState;
}


TAF_APS_CDATA_PS_STATE_ENUM_UINT8 TAF_APS_GetPdpEntCdataPsState (
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.enPsState;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_APS_SetPdpEntSo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSo
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.enSo = enSo;
}


TAF_APS_CDATA_SO_TYPE_ENUM_UINT16 TAF_APS_GetPdpEntSo (
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.enSo;
}


VOS_VOID TAF_APS_SetPdpEntConRef (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucConRef
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.ucConRef = ucConRef;
}


VOS_VOID TAF_APS_SetPdpEntConnectId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucConnectId
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.ucConnectId = ucConnectId;
}



VOS_VOID TAF_APS_SetPdpEntPppState (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.enPppState = enPppState;
}


TAF_APS_CDATA_PPP_STATE_ENUM_UINT8 TAF_APS_GetPdpEntPppState (
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.enPppState;
}


VOS_VOID TAF_APS_SetCdmaAirLinkStatus(
    VOS_UINT8                                   ucPdpId,
    TAF_APS_CDATA_AIR_LINK_STATUS_ENUM_UINT8    enAirLinkStatus
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.enAirLinkStatus = enAirLinkStatus;

    return;
}

TAF_APS_CDATA_AIR_LINK_STATUS_ENUM_UINT8 TAF_APS_GetCdmaAirLinkStatus(
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.enAirLinkStatus;
}



VOS_VOID TAF_APS_SetDoQuickAcqProtectFlag(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucDoQuickAcqProtect
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.ucDoQuickAcqProtect = ucDoQuickAcqProtect;

    return;
}


VOS_UINT8 TAF_APS_GetDoQuickAcqProtectFlag(
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.ucDoQuickAcqProtect;
}




VOS_UINT8   TAF_APS_GetPdpIdByConRef(
    VOS_UINT8                           ucConRef
)
{
    VOS_UINT8                           i;

    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if ((ucConRef == g_PdpEntity[i].stCdataInfo.ucConRef)
         && (VOS_TRUE == g_PdpEntity[i].ulUsedFlg))
        {
            return g_PdpEntity[i].ucPdpId;
        }
    }
    return TAF_APS_INVALID_PDPID;
}




VOS_VOID TAF_APS_SetPdpEntL2ErrReOrigFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucIsL2ErrReOrig
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.ucIsL2ErrReOrig = ucIsL2ErrReOrig;
}


VOS_VOID TAF_APS_SetPdpEntReOrigCount (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucReOrigCount
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.ucReOrigCount = ucReOrigCount;
}


VOS_UINT8 TAF_APS_GetPdpEntReOrigCount (
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.ucReOrigCount;
}




VOS_VOID TAF_APS_PdpEntityEnterDormant(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulIsNeedStartTimer
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode;
    VOS_UINT32                          ulCurrRatType;

    /* Main Fsm State enter TAF_APS_STA_DORMANT */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_DORMANT);

    ulCurrRatType          = TAF_APS_GetCurrPdpEntityRatType();

    /*获取当前建立数据服务的模式*/
    enCurrCdataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if ((VOS_TRUE == TAF_APS_GetHysEnableFlg())
    && (TAF_APS_RAT_TYPE_1X   == enCurrCdataServiceMode))
    {
        /* Proc HaT/HT when enter Dormant */
        TAF_APS_ProcEpdszidEnterDormant();
    }

    if ((TAF_APS_RAT_TYPE_HRPD == ulCurrRatType)
     && (TAF_APS_RAT_TYPE_1X   == enCurrCdataServiceMode))
    {
        /* 发送内部1X到HRPD切换请求消息 */
        TAF_APS_SndInter1XToHrpdHandOffReq(ucPdpId);

        return;
    }

    if ((TAF_APS_RAT_TYPE_LTE  == ulCurrRatType)
     && (TAF_APS_RAT_TYPE_1X   == enCurrCdataServiceMode))
    {
        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEnd1xServiceInDormantInd(ucPdpId);

        return;
    }

    if (VOS_TRUE == ulIsNeedStartTimer)
    {
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            /* if Dormant Timer Len > 0，Start Dormant Timer */
            if (TAF_APS_GetSocmDormantTiLen() > 0)
            {
                if (TAF_APS_GetUserCfgDormTiVal() > TAF_APS_GetSocmDormantTiLen())
                {
                    TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetUserCfgDormTiVal(), ucPdpId);
                }
                else
                {
                    TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetSocmDormantTiLen(), ucPdpId);
                }
            }
        }
    }
    return;
}



VOS_VOID TAF_APS_SetPdpEntSrId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucSrId
)
{
    g_PdpEntity[ucPdpId].stCdataInfo.ucSrId= ucSrId;
}


VOS_UINT8 TAF_APS_GetPdpEntSrId (
    VOS_UINT8                           ucPdpId
)
{
    return g_PdpEntity[ucPdpId].stCdataInfo.ucSrId;
}





VOS_VOID TAF_APS_UpdataCdataIpv4Addr(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf
)
{
    /* 更新IP地址 */
    PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpAddr,
               pstPppActCnf->aucIpv4Addr,
               TAF_APS_PPP_IPV4_ADDR_LEN);

    if (VOS_TRUE == pstPppActCnf->stIpv4Dns.bitOpIpv4PrimDNS)
    {
        pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
        pstPdpEntity->PdpDns.OP_PriDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->PdpDns.aucPriDns,
                   pstPppActCnf->stIpv4Dns.aucIpv4PrimDNS,
                   TAF_APS_PPP_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstPppActCnf->stIpv4Dns.bitOpIpv4SecDNS)
    {
        pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
        pstPdpEntity->PdpDns.OP_SecDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->PdpDns.aucSecDns,
                   pstPppActCnf->stIpv4Dns.aucIpv4SecDNS,
                   TAF_APS_PPP_IPV4_ADDR_LEN);
    }
}


VOS_VOID TAF_APS_UpdataCdataIpv6Addr(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf
)
{
    /* 更新IP地址 */
    PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpV6Addr,
               pstPppActCnf->aucIpv6Addr,
               TAF_APS_PPP_IPV6_ADDR_LEN);

}
/*
TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_GetPreRatModeFromSysServiceInd(
    MMA_TAF_1X_SERVICE_STATUS_IND_STRU    *pstMmaServiceStatusInd
)
{
    if (0 == pstMmaServiceStatusInd->ulNum)
    {
        return TAF_APS_RAT_TYPE_NULL;
    }
    else if (1 == pstMmaServiceStatusInd->ulNum)

    return ;
}*/


TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_APS_Get1XServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetCsServiceStatus();
}


TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_APS_GetHrpdServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetPsServiceStatus();
}



VOS_VOID TAF_APS_UpdateCdataEhsmPdnInfo (
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    EHSM_APS_PDN_ADDR_STRU             *pstPdnAddr,
    EHSM_APS_APN_STRU                  *pstApn,
    EHSM_APS_DNS_IPV4_STRU             *pstIpv4Dns
)
{
    /* 更新APN */
    pstPdpEntity->PdpApnFlag      = VOS_TRUE;
    pstPdpEntity->PdpApn.ucLength = (VOS_UINT8)(pstApn->ulLength);
    PS_MEM_CPY(pstPdpEntity->PdpApn.aucValue,
               pstApn->aucApn,
               EHSM_APS_APN_MAX_LEN);

    /* 更新PdnAdrr */
    pstPdpEntity->PdpAddrFlag     = VOS_TRUE;
    if (EHSM_APS_PDN_TYPE_IPV4    == pstPdnAddr->enPdnType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpAddr,
                   pstPdnAddr->aucIpv4Addr,
                   EHSM_APS_IPV4_ADDR_LEN);

        pstPdpEntity->PdpAddr.ucPdpTypeNum  = APS_ADDR_STATIC_IPV4;

    }

    if (VOS_TRUE == pstIpv4Dns->bitOpIpv4PrimDNS)
    {
        pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
        pstPdpEntity->PdpDns.OP_PriDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->PdpDns.aucPriDns,
                   pstIpv4Dns->aucIpv4PrimDNS,
                   EHSM_APS_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstIpv4Dns->bitOpIpv4SecDNS)
    {
        pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
        pstPdpEntity->PdpDns.OP_SecDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->PdpDns.aucSecDns,
                   pstIpv4Dns->aucIpv4SecDNS,
                   EHSM_APS_IPV4_ADDR_LEN);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (EHSM_APS_PDN_TYPE_IPV6    == pstPdnAddr->enPdnType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpV6Addr,
                   pstPdnAddr->aucIpv6Addr,
                   EHSM_APS_IPV6_ADDR_LEN);

        pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV6;

    }

    if (EHSM_APS_PDN_TYPE_IPV4V6  == pstPdnAddr->enPdnType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpAddr,
                   pstPdnAddr->aucIpv4Addr,
                   EHSM_APS_IPV4_ADDR_LEN);

        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpV6Addr,
                   pstPdnAddr->aucIpv6Addr,
                   EHSM_APS_IPV6_ADDR_LEN);

        pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV4V6;

    }

#endif

}


VOS_VOID TAF_APS_UpdateCdataIpv4Dns(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    DHCP_APS_DNS_IPV4_CNF_STRU         *pstDhcpDnsIpv4Cnf
)
{

    if (VOS_TRUE == pstDhcpDnsIpv4Cnf->stIpv4Dns.bitOpIpv4PrimDNS)
    {
        pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
        pstPdpEntity->PdpDns.OP_PriDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->PdpDns.aucPriDns,
                   pstDhcpDnsIpv4Cnf->stIpv4Dns.aucIpv4PrimDNS,
                   TAF_APS_DHCP_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstDhcpDnsIpv4Cnf->stIpv4Dns.bitOpIpv4SecDNS)
    {
        pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
        pstPdpEntity->PdpDns.OP_SecDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->PdpDns.aucSecDns,
                   pstDhcpDnsIpv4Cnf->stIpv4Dns.aucIpv4SecDNS,
                   TAF_APS_DHCP_IPV4_ADDR_LEN);
    }
}


VOS_VOID TAF_APS_UpdateCdataIpv6Dns(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns
)
{
    if (VOS_TRUE == pstPdpIpv6Dns->bitOpPriDns)
    {
        pstPdpEntity->stPdpIpV6Dns.bitOpPriDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->stPdpIpV6Dns.aucPriDns,
                   pstPdpIpv6Dns->aucPriDns,
                   TAF_IPV6_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpIpv6Dns->bitOpSecDns)
    {
        pstPdpEntity->stPdpIpV6Dns.bitOpSecDns  = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->stPdpIpV6Dns.aucSecDns,
                   pstPdpIpv6Dns->aucSecDns,
                   TAF_IPV6_ADDR_LEN);
    }
}


VOS_VOID TAF_APS_SndExternalModulePsRatTypeNtf(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 通知PPPC当前的PS服务所在的模式 */
    if ((TAF_APS_RAT_TYPE_1X   == enCurrCdataServiceMode)
     || (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode))
    {
        TAF_APS_SndPppModeChangeNotify(ucPdpId);
    }
    /* 通知CDS当前建立的数据服务模式 */
    TAF_APS_SndCdsModeChangeInd(enCurrCdataServiceMode);

    /* 通知MMA当前建立的数据服务模式 */
    TAF_SndMmaPsRatTypeNotify(enCurrCdataServiceMode);

    /* 通知EHSM当前建立的数据服务模式 */
    TAF_APS_SndEhsmPsRatTypeNtf(enCurrCdataServiceMode);
}


VOS_UINT8   TAF_APS_GetPdpIdByPndId(
    VOS_UINT8                           ucPdnId
)
{
    VOS_UINT8                           ucTmpPdpId;

    for(ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++ )
    {
        if (( ucPdnId == g_PdpEntity[ucTmpPdpId].stCdataInfo.ucPdnId)
         && ( VOS_TRUE == g_PdpEntity[ucTmpPdpId].ulUsedFlg ))
        {
            return  ucTmpPdpId;
        }
    }
    return TAF_APS_INVALID_PDPID;
}


TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataEhrpdSvcSta(
    VOS_UINT8                           ucPdpId
)
{
    EHSM_APS_PDN_STATUS_ENUM_UINT32     enEhsmStatus;

    VOS_UINT8                           ucPdnId;

    ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    enEhsmStatus  = CNAS_EHSM_GetCdataServiceStatus(ucPdnId);

    TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_GetCdataEhrpdSvcSta: Ehrpd state", enEhsmStatus);

    if (EHSM_APS_PDN_STATUS_INACTIVE == enEhsmStatus)
    {
        return TAF_PS_CDATA_BEAR_STATUS_INACTIVE;
    }
    else if (EHSM_APS_PDN_STATUS_ACTIVE == enEhsmStatus)
    {
        return TAF_PS_CDATA_BEAR_STATUS_ACTIVE;
    }
    else if (EHSM_APS_PDN_STATUS_DORMANT == enEhsmStatus)
    {
        return TAF_PS_CDATA_BEAR_STATUS_IDLE;
    }
    else
    {
        return TAF_PS_CDATA_BEAR_STATUS_SUSPEND;
    }
}



VOS_VOID TAF_APS_RcvSequenceProcessDhcpNdclient(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_CTRL_STRU                       stCtrl;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;

    PS_MEM_SET(&stCtrl, 0x00, sizeof(TAF_CTRL_STRU));

    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    enRatType    = TAF_APS_GetCurrPdpEntityRatType();

    /* 1X 和 HRPD ，在只需协商DNS_ipv6 */
    if (((TAF_APS_RAT_TYPE_1X == enRatType) || (TAF_APS_RAT_TYPE_HRPD == enRatType))
       && (VOS_TRUE == pstPdpEntity->ucRcvDhcpDnsFlgIpv6))
    {
        /* 给用户上报ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
        /* 协商结束 */
        pstPdpEntity->ucNeedGetDnsFlg = VOS_FALSE;

        if (VOS_TRUE == pstPdpEntity->ucRcvNdClientNtyFlg)
        {
            /* 填写APP控制头 */
            TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

            /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
            TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                            pstPdpEntity->stClientInfo.ucCid,
                                            pstPdpEntity->ucNsapi,
                                            (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);

        }

        return;

    }

    /* IPV6类型 ehrpd   */
    if (MN_APS_ADDR_IPV6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
    {

        /* 协商结束 */
        pstPdpEntity->ucNeedGetDnsFlg = VOS_FALSE;

        if (TAF_APS_DEFAULT_CID != ucCid)
        {
            /* 给用户上报ACTIVATE_CNF事件 */
            TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
        }

        if (VOS_TRUE == pstPdpEntity->ucRcvNdClientNtyFlg)
        {
            /* 填写APP控制头 */
            TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

            /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
            TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                            pstPdpEntity->stClientInfo.ucCid,
                                            pstPdpEntity->ucNsapi,
                                            (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);

        }

        return;
    }

    /* 同时协商ipv4 ipv6 dns 的协商， ehrpd  */
    if ((VOS_TRUE == pstPdpEntity->ucRcvDhcpDnsFlgIpv4)
     && (VOS_TRUE == pstPdpEntity->ucRcvDhcpDnsFlgIpv6))
    {

        if (TAF_APS_DEFAULT_CID != ucCid)
        {
            /* 给用户上报ACTIVATE_CNF事件 */
            TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
        }

        /* 协商结束 */
        pstPdpEntity->ucNeedGetDnsFlg = VOS_FALSE;

        if (VOS_TRUE == pstPdpEntity->ucRcvNdClientNtyFlg)
        {
            /* 填写APP控制头 */
            TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

            /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
            TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                            pstPdpEntity->stClientInfo.ucCid,
                                            pstPdpEntity->ucNsapi,
                                            (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
            /* 如果已经上报清标志位 */
            pstPdpEntity->ucRcvNdClientNtyFlg = VOS_FALSE;
            pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_FALSE;
            pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_FALSE;

        }

        return;
    }

    /* IPVv4v6类型,只做v6的dns协商 ehrpd   */
    if (((VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns) || (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns))
     && (MN_APS_ADDR_IPV4V6 == pstPdpEntity->PdpAddr.ucPdpTypeNum))
    {

        /* 协商结束 */
        pstPdpEntity->ucNeedGetDnsFlg = VOS_FALSE;

        if (TAF_APS_DEFAULT_CID != ucCid)
        {
            /* 给用户上报ACTIVATE_CNF事件 */
            TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
        }

        if (VOS_TRUE == pstPdpEntity->ucRcvNdClientNtyFlg)
        {
            /* 填写APP控制头 */
            TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

            /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
            TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                            pstPdpEntity->stClientInfo.ucCid,
                                            pstPdpEntity->ucNsapi,
                                            (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);

        }

        return;
    }
}


VOS_VOID TAF_APS_ProcCdataDhcpNegotiateFail(
    VOS_UINT8                                     ucPdpId,
    TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8      enEndReason
)
{
    VOS_UINT8                           ucCid;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    ucCid        = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (TAF_APS_DEFAULT_CID == ucCid)
    {
        /* 本地去激活 */
        TAF_APS_LocalReleaseProc(ucPdpId);
    }
    else
    {
        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息 */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       enEndReason,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    /* 如果任何一个消息回复失败，清除所有标志位 */
    pstPdpEntity->ucRcvNdClientNtyFlg = VOS_FALSE;
    pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_FALSE;
    pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_FALSE;

}



VOS_VOID TAF_APS_ProcModifyReq_LteHandoverToEhrpdScene(
    VOS_UINT8                                               ucPdpId,
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd
)
{
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity;

    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 更新PDN_ID */
    pstPdpEntity->stCdataInfo.ucPdnId = pstLteHandoverInd->ucPdnId;

    /* 更新APN */
    pstPdpEntity->PdpApnFlag      = VOS_TRUE;
    pstPdpEntity->PdpApn.ucLength = (VOS_UINT8)(pstLteHandoverInd->stApn.ulLength);
    PS_MEM_CPY(pstPdpEntity->PdpApn.aucValue,
               pstLteHandoverInd->stApn.aucApn,
               EHSM_APS_APN_MAX_LEN);

    /* 更新PdnAdrr */
    pstPdpEntity->PdpAddrFlag     = VOS_TRUE;
    if (EHSM_APS_PDN_TYPE_IPV4    == pstLteHandoverInd->stPdnAddr.enPdnType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpAddr,
                   pstLteHandoverInd->stPdnAddr.aucIpv4Addr,
                   EHSM_APS_IPV4_ADDR_LEN);

        pstPdpEntity->PdpAddr.ucPdpTypeNum  = APS_ADDR_STATIC_IPV4;

    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (EHSM_APS_PDN_TYPE_IPV6    == pstLteHandoverInd->stPdnAddr.enPdnType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpV6Addr,
                   pstLteHandoverInd->stPdnAddr.aucIpv6Addr,
                   EHSM_APS_IPV6_ADDR_LEN);

        pstPdpEntity->PdpAddr.ucPdpTypeNum = MN_APS_ADDR_IPV6;

    }

    if (EHSM_APS_PDN_TYPE_IPV4V6  == pstLteHandoverInd->stPdnAddr.enPdnType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpAddr,
                   pstLteHandoverInd->stPdnAddr.aucIpv4Addr,
                   EHSM_APS_IPV4_ADDR_LEN);

        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpV6Addr,
                   pstLteHandoverInd->stPdnAddr.aucIpv6Addr,
                   EHSM_APS_IPV6_ADDR_LEN);

        pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV4V6;
    }
#endif

    return;
}



VOS_VOID TAF_APS_ProcPdnInfoChg_LteHandoverToEhrpdScene(
    VOS_UINT8                                               ucPdpId,
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd,
    VOS_UINT32                                             *pulIsNeedDeactPdn
)
{
    VOS_INT32                           lCmpIpv4AddrRst;
    VOS_INT32                           lCmpIpv6AddrRst;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdnType;

    /* 初始化, 获取消息内容 */
    lCmpIpv4AddrRst = 0;
    lCmpIpv6AddrRst = 0;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucPdnType       = TAF_APS_MapEhsmPdnTypeToAps(pstLteHandoverInd->stPdnAddr.enPdnType);

    if (APS_ADDR_INVALID == ucPdnType)
    {
        return;
    }

    if (pstPdpEntity->PdpAddr.ucPdpTypeNum != ucPdnType)
    {
        *pulIsNeedDeactPdn = VOS_TRUE;

        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;

        return;
    }

    switch (pstLteHandoverInd->stPdnAddr.enPdnType)
    {
        case EHSM_APS_PDN_TYPE_IPV4:
            lCmpIpv4AddrRst                     = PS_MEM_CMP(pstLteHandoverInd->stPdnAddr.aucIpv4Addr,
                                                             pstPdpEntity->PdpAddr.aucIpAddr,
                                                             TAF_IPV4_ADDR_LEN);
            break;

        case EHSM_APS_PDN_TYPE_IPV6:
            lCmpIpv6AddrRst                     = PS_MEM_CMP(pstLteHandoverInd->stPdnAddr.aucIpv6Addr,
                                                             pstPdpEntity->PdpAddr.aucIpV6Addr,
                                                             TAF_IPV6_PREFIX_LEN);


            break;

        case EHSM_APS_PDN_TYPE_IPV4V6:
            lCmpIpv4AddrRst                     = PS_MEM_CMP(pstLteHandoverInd->stPdnAddr.aucIpv4Addr,
                                                             pstPdpEntity->PdpAddr.aucIpAddr,
                                                             TAF_IPV4_ADDR_LEN);

            lCmpIpv6AddrRst                     = PS_MEM_CMP(pstLteHandoverInd->stPdnAddr.aucIpv6Addr,
                                                             pstPdpEntity->PdpAddr.aucIpV6Addr,
                                                             TAF_IPV6_PREFIX_LEN);

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ProcPdnInfoChg_LteHandoverTOEhrpdScene:Wrong Msg Entry");
            break;
    }

    /* 给EHSM发送去激活消息 */
    if ((0 != lCmpIpv4AddrRst)
     || (0 != lCmpIpv6AddrRst))
    {
        *pulIsNeedDeactPdn = VOS_TRUE;

        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;
    }
    return;
}


VOS_VOID TAF_APS_LocalReleaseProc(
    VOS_UINT8                           ucPdpId
)
{
    /* 如果当前的PPP状态是激活的 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        TAF_APS_SndEhsmLocDetachNotify();
    }

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

}


VOS_VOID TAF_APS_AddCauseForCdataDoalStackDailNotSuport(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActCnfEvt,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enServiceMode;

    enServiceMode   = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if ((TAF_APS_RAT_TYPE_1X == enServiceMode)
     || (TAF_APS_RAT_TYPE_HRPD == enServiceMode)
     || (TAF_APS_RAT_TYPE_EHRPD == enServiceMode))
    {

        if (TAF_PDP_IPV4V6 == TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid))
        {
            if (TAF_PDP_IPV4  == pstPdpActCnfEvt->stPdpAddr.enPdpType)
            {
                pstPdpActCnfEvt->bitOpCause = VOS_TRUE;
                pstPdpActCnfEvt->enCause    = TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED;
            }

            if (TAF_PDP_IPV6 == pstPdpActCnfEvt->stPdpAddr.enPdpType)
            {
                pstPdpActCnfEvt->bitOpCause = VOS_TRUE;
                pstPdpActCnfEvt->enCause    = TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED;
            }
        }
    }

    return;
}


VOS_UINT8 TAF_APS_IsExistXcallOrXsmsOpreation(VOS_VOID)
{

    VOS_UINT8                           ucCsCallExistFlg;
    VOS_UINT8                           ucIsXsmsCallExistFlg;

    ucCsCallExistFlg     = TAF_SDC_GetCsCallExistFlg();
    ucIsXsmsCallExistFlg = TAF_SDC_GetXsmsCallExistFlg();

    TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_IsExistXcallOrXsmsOpreation : ucCsCallExistFlg", ucCsCallExistFlg);
    TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_IsExistXcallOrXsmsOpreation : ucIsXsmsCallExistFlg", ucIsXsmsCallExistFlg);

    if ((VOS_TRUE == ucIsXsmsCallExistFlg)
     || (VOS_TRUE == ucCsCallExistFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 TAF_APS_IsCdataLocalReleaseCause(
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    if ((TAF_PS_CAUSE_XCC_AS_SO_REJ == enCause)
     || (TAF_PS_CAUSE_RAT_TYPE_CHANGE == enCause)
     || (TAF_PS_CAUSE_XCC_CAUSE_PROTOTAL_REV_NOT_SUPPORT == enCause))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_RATMODE_ENUM_UINT32 TAF_APS_MapRatType2VosRatMode(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
)
{
    switch (enRatType)
    {
        case TAF_APS_RAT_TYPE_1X:
            return VOS_RATMODE_1X;
        case TAF_APS_RAT_TYPE_HRPD:
            return VOS_RATMODE_HRPD;
        case TAF_APS_RAT_TYPE_EHRPD:
            return VOS_RATMODE_HRPD;
        default:
            return VOS_RATMODE_BUTT;
    }

}



VOS_UINT32 TAF_APS_IsAllowCdataEsting(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
)
{
    VOS_UINT8                           ucCsCallExistFlg;
    VOS_UINT8                           ucXsmsCallExistFlg;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ucServiceState;

    ucCsCallExistFlg   = TAF_SDC_GetCsCallExistFlg();
    ucXsmsCallExistFlg = TAF_SDC_GetXsmsCallExistFlg();

    if (TAF_APS_RAT_TYPE_1X == enRatType)
    {
        /* 如果不支持并发业务，需要判断当前是否有短信或者语音呼叫实体存在 */
        if (VOS_TRUE != TAF_SDC_Get1xConcurrentSupportedFlag())
        {
            if (VOS_TRUE == TAF_APS_GET_CDATA_SUSPEND_STATUS())
            {
                return VOS_FALSE;
            }

            if ((VOS_TRUE == ucCsCallExistFlg)
             || (VOS_TRUE == ucXsmsCallExistFlg))
            {
                return VOS_FALSE;
            }
        }

        if (VOS_TRUE == TAF_APS_GetPppAuthInfoGetFromCardFlag())
        {
            if (VOS_TRUE  != TAF_APS_GetRead3GpdFileDoneFlag())
            {
                return VOS_FALSE;
            }
        }


        if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_APS_Get1XServiceStatus())
        {
            return VOS_TRUE;
        }
    }
    else
    {
        ucServiceState = TAF_APS_GetHrpdServiceStatus();
        if ((VOS_FALSE                             == TAF_APS_GetIsHrpdDisabledFlag())
         && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ucServiceState))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID TAF_APS_SetPdpEntCdataEstFailCause(
    VOS_UINT8                           ucPdnId,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
)
{
    VOS_UINT8                           ucCsCallExistFlg;
    VOS_UINT8                           ucXsmsCallExistFlg;

    ucCsCallExistFlg   = TAF_SDC_GetCsCallExistFlg();
    ucXsmsCallExistFlg = TAF_SDC_GetXsmsCallExistFlg();

    if (TAF_APS_RAT_TYPE_1X == enRatType)
    {
        /* 如果不支持并发业务，需要判断当前是否有短信或者语音呼叫实体存在 */
        if (VOS_TRUE != TAF_SDC_Get1xConcurrentSupportedFlag())
        {
            if (VOS_TRUE == TAF_APS_GET_CDATA_SUSPEND_STATUS())
            {
                g_PdpEntity[ucPdnId].enCause = TAF_PS_CAUSE_XCC_CCS_NOT_SUPPORT;
            }

            if ((VOS_TRUE == ucCsCallExistFlg)
             || (VOS_TRUE == ucXsmsCallExistFlg))
            {
                g_PdpEntity[ucPdnId].enCause = TAF_PS_CAUSE_XCC_CCS_NOT_SUPPORT;
            }
        }

        if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_APS_Get1XServiceStatus())
        {
            g_PdpEntity[ucPdnId].enCause = TAF_PS_CAUSE_1X_NO_SERVICE;
        }
    }
    else
    {
        if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_APS_GetHrpdServiceStatus())
        {
            g_PdpEntity[ucPdnId].enCause = TAF_PS_CAUSE_HRPD_NO_SERVICE;
        }
    }

    return;
}


VOS_UINT8 TAF_APS_GetDrsValueByScene(
    VOS_UINT32                          ulEventType
)
{
    switch (ulEventType)
    {
        /* DRS=0 的场景 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
            break;

        default:
            /* 除此之外的场景DRS=1 */
            return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 TAF_APS_IsRedialCallFromDormantState(
    VOS_UINT8                           ucPdnId
)
{
    if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdnId))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32  TAF_APS_IsNeedNotifyCdsModeChange(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataSerMode
)
{
    /*
        3）CL模式下，MMC上报NULL给APS，APS根据当前数据业务所在的模式决定是否通知CDS
            1.LTE下，APS通知CDS接入技术为NULL，APS内部的处理与GUL保持一致；
            2.DO下，APS通知CDS接入技术为NULL，只在预处理处理本消息；
            3.1X下，APS忽略该消息，不通知CDS；
        4）CL模式下，MMC上报LTE给APS，APS根据当前数据业务所在的模式决定如何处理
            1.LTE下，APS通知CDS接入技术为LTE，APS内部的处理与GUL保持一致；
            2.DO下，APS忽略该消息，继续等待MMA的系统消息通知，然后再通知CDS；
            3.1X下，APS忽略该消息，继续等待MMA的系统消息通知，DORMANT态直接通知CDS，
              ACTIVE状态不通知，等去激活完成后无条件通知CDS当前的接入技术；
    */

    VOS_UINT32                          ulIsNeed;

    ulIsNeed                            = VOS_FALSE;

    if (TAF_APS_RAT_TYPE_LTE == enDataSerMode)
    {
        ulIsNeed = VOS_TRUE;
    }
    else if ((TAF_APS_RAT_TYPE_HRPD == enDataSerMode)
     || (TAF_APS_RAT_TYPE_EHRPD == enDataSerMode))
    {
        if (TAF_APS_RAT_TYPE_NULL == enRatType)
        {
            ulIsNeed = VOS_TRUE;
        }
    }
    else
    {
        ulIsNeed = VOS_FALSE;
    }

    return ulIsNeed;
}


VOS_UINT32 TAF_APS_IsHybridMode(VOS_VOID)
{
    VOS_UINT32                          ulIsSupportDvdo;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;

    ulIsSupportDvdo = TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_EVDO);
    enRatType       = TAF_APS_GetCurrPdpEntityRatType();

    if (VOS_TRUE == TAF_SDC_Is1xOnlyMode())
    {
        return VOS_FALSE;
    }

    if ((VOS_TRUE != ulIsSupportDvdo)
     &&(TAF_APS_RAT_TYPE_1X == enRatType))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataBearStatusCommFun(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_TIMER_STATUS_ENUM_U8                            enTimerStatus;
    TAF_APS_RAT_TYPE_ENUM_UINT32                            enCurrPsRatType;

    enCurrPsRatType = TAF_APS_GetCurrPdpEntityDataServiceMode();

    /* 如果当前不是3gpp2的数据业务，直接返回INACTIVE */
    if ((TAF_APS_RAT_TYPE_EHRPD != enCurrPsRatType)
      &&(TAF_APS_RAT_TYPE_1X    != enCurrPsRatType)
      &&(TAF_APS_RAT_TYPE_HRPD  != enCurrPsRatType))
    {
        TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_GetCdataBearStatusCommFun : Wrong RAT type", enCurrPsRatType);

        return TAF_PS_CDATA_BEAR_STATUS_SUSPEND;
    }

    if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
    {
        /* 如果当前Dormant timer正在运行，或者PS业务被挂起(TCH通道被其它业务占用)
           则当前状态为SUSPEND状态，不可以数传，目前不支持辅助业务(SO=66)，以后支持辅助业务时，
           再区分是否存在辅助业务 */

        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* 语音或者短信在重拨时，为了语音业务优先，不可以触发建链 */
        if ((TAF_APS_CDMA_TC_SUSPENDED == TAF_APS_GET_CDATA_SUSPEND_STATUS())
         || (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus))
        {
            TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_GetCdataBearStatusCommFun : Dorm Timer Sta", enTimerStatus);

            return TAF_PS_CDATA_BEAR_STATUS_SUSPEND;
        }

        /* EHRPD的状态 */
        if (TAF_APS_RAT_TYPE_EHRPD  == enCurrPsRatType)
        {
            return TAF_APS_GetCdataEhrpdSvcSta(ucPdpId);
        }

        /* 1x或HRPD的承载状态 */
        return TAF_APS_MapCdataBearStatus(ucPdpId);

    }

    return TAF_PS_CDATA_BEAR_STATUS_INACTIVE;
}

TAF_APS_PPP_AUTH_TYPE_ENUM_UINT8 TAF_APS_MapApsAuthTypeToPpp(
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enTafPdpAuthType
)
{
    switch (enTafPdpAuthType)
    {
        case TAF_PDP_AUTH_TYPE_NONE:
            return TAF_APS_PPP_AUTH_TYPE_NONE;

        case TAF_PDP_AUTH_TYPE_PAP:
            return TAF_APS_PPP_AUTH_TYPE_PAP;

        case TAF_PDP_AUTH_TYPE_CHAP:
            return TAF_APS_PPP_AUTH_TYPE_CHAP;

        case TAF_PDP_AUTH_TYPE_PAP_OR_CHAP:
            return TAF_APS_PPP_AUTH_TYPE_PAP_OR_CHAP;

        default :
            return TAF_APS_PPP_AUTH_TYPE_BUTT;
    }
}


TAF_PDP_AUTH_TYPE_ENUM_UINT8 TAF_APS_Map3GpdAuthTypeToPpp(
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_ENUM_UINT8        en3GpdAuthType
)
{
    switch (en3GpdAuthType)
    {
        case TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_NULL:
            return TAF_PDP_AUTH_TYPE_NONE;

        case TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_PAP:
            return TAF_PDP_AUTH_TYPE_PAP;

        case TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP:
            return TAF_PDP_AUTH_TYPE_CHAP;

        case TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP_TO_PAP_FALLBACK:
            return TAF_PDP_AUTH_TYPE_PAP_OR_CHAP;

        default :
            return TAF_PDP_AUTH_TYPE_BUTT;
    }
}


EHSM_APS_AUTH_TYPE_ENUM_UINT8 TAF_APS_MapApsAuthTypeToEhsm(
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enTafPdpAuthType
)
{
    switch (enTafPdpAuthType)
    {
        case TAF_PDP_AUTH_TYPE_NONE:
            return EHSM_APS_AUTH_TYPE_NONE;

        case TAF_PDP_AUTH_TYPE_PAP:
            return EHSM_APS_AUTH_TYPE_PAP;

        case TAF_PDP_AUTH_TYPE_CHAP:
            return EHSM_APS_AUTH_TYPE_CHAP;

        case TAF_PDP_AUTH_TYPE_PAP_OR_CHAP:
            return EHSM_APS_AUTH_TYPE_PAP_OR_CHAP;

        default :
            return EHSM_APS_AUTH_TYPE_BUTT;
    }
}

VOS_VOID TAF_APS_Read3GpdSipCapaFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
)
{
    /*****************************************************************
            Field               |      Length
            MAX_NUM_NAI         |        4
            MAX_NAI_LENGTH      |        8
            MAX_SS_LENGTH       |        5
            AUTH_ALGORITHM      |        8
            RESERVED            |        7
     ******************************************************************/
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucAuthAlgorithm;

    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();

    /* Read file fail */
    if ((VOS_OK != pUsimTafMsg->stCmdResult.ulResult)
     || (TAF_APS_3GPD_SIP_CAPA_FILE_LENGTH != pUsimTafMsg->usEfLen))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipCapaFileCnf: Read 3GPD sip capability file FAIL");
        return;
    }

    pst3GpdOpInfoAddr->st3GpdSipCapa.ucMaxNaiNum     = ((pUsimTafMsg->aucEf[0]) & 0xF0) >> 4;
    pst3GpdOpInfoAddr->st3GpdSipCapa.ucMaxNaiLength  = (((pUsimTafMsg->aucEf[0]) & 0x0F) << 4) | (((pUsimTafMsg->aucEf[1]) & 0xF0) >> 4);
    pst3GpdOpInfoAddr->st3GpdSipCapa.ucMaxSsLength   = ((((pUsimTafMsg->aucEf[1]) & 0x0F) << 1) | (((pUsimTafMsg->aucEf[2]) & 0x80) >> 7)) & 0x1F;
    ucAuthAlgorithm                                  = (((pUsimTafMsg->aucEf[2]) & 0x7F) << 1) | (((pUsimTafMsg->aucEf[3]) & 0x80) >> 7);
    switch (ucAuthAlgorithm)
    {
        case TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_PAP_ENABLE:
            pst3GpdOpInfoAddr->st3GpdSipCapa.ucAuthAlgorithm = TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_PAP;
            break;

        case TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP_ENABLE:
            pst3GpdOpInfoAddr->st3GpdSipCapa.ucAuthAlgorithm = TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP;
            break;

        case TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_PAP_CHAP_ENABLE:
            pst3GpdOpInfoAddr->st3GpdSipCapa.ucAuthAlgorithm = TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_CHAP_TO_PAP_FALLBACK;
            break;

        default :
            /* 全0 表示PAP or CHAP 都不支持 */
            pst3GpdOpInfoAddr->st3GpdSipCapa.ucAuthAlgorithm = TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_BUTT;
    }

    return;
}

VOS_VOID TAF_APS_Read3GpdSipUppFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
)
{
    /*****************************************************************
        first byte is the whole length of content

            Field               |      Length
            NUM_NAI             |        4

            NAI_ENTRY_INDEX     |        4
            NAI_LENGTH          |        8
            NAI                 |        8 * NAI_LENGTH
            AUTH_ALGORITHM      |        4

            RESERVED            |        0 to 7 (as needed)
     *****************************************************************
            None                            |        0000
            PPP CHAP                        |        0001
            PPP PAP                         |        0010
            PPP CHAP to PAP fallback        |        0011
            RESERVED                        |        0100 ~ 1111
     ******************************************************************/
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucNaiNum;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                          *pucSrc;
    VOS_UINT8                           ucUppLength;


    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();
    ucIndex             = 0;

    /* Read file fail */
    if ((VOS_OK != pUsimTafMsg->stCmdResult.ulResult)
     || (0 == pUsimTafMsg->usEfLen))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipUppFileCnf: Read 3GPD sip user profile  FAIL");
        return;
    }
    ucUppLength = pUsimTafMsg->aucEf[0];
    if (0 == ucUppLength)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipUppFileCnf:  3GPD sip user profile str len is zero");
        return;
    }

    /* nai 个数 */
    ucNaiNum = (pUsimTafMsg->aucEf[1] & 0xF0) >> 4;
    if ((0 == ucNaiNum) || (pst3GpdOpInfoAddr->st3GpdSipCapa.ucMaxNaiNum < ucNaiNum))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipUppFileCnf:  3GPD sip user profile NUM VALUE illegal");
        return;
    }
    pst3GpdOpInfoAddr->st3GpdSipUserProfile.ucNaiNum = ucNaiNum;

    /* 解析nai */
    pucSrc = &pUsimTafMsg->aucEf[1];
    while (ucNaiNum)
    {
        ucNaiNum--;

        /* nai index */
        ucIndex = *pucSrc & 0x0F;
        pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiIndex = ucIndex;
        pucSrc++;

        /* nai length */
        pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiLength = *pucSrc;
        if (pst3GpdOpInfoAddr->st3GpdSipCapa.ucMaxNaiLength < *pucSrc)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipUppFileCnf:  3GPD sip user profile nai length illegal");
            PS_MEM_SET(&pst3GpdOpInfoAddr->st3GpdSipUserProfile, 0, sizeof(TAF_APS_3GPD_SIP_USER_PROFILE_STRU));
            return;
        }
        pucSrc++;

        /* nai str */
        PS_MEM_CPY( pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].aucNaiStr,
                    pucSrc,
                    pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiLength);
        pucSrc += pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiLength;

        /* nai AUTH_ALGORITHM */
        pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucAuthAlgorithm = (*pucSrc & 0xF0) >> 4;
    }

    return;
}

VOS_VOID TAF_APS_Read3GpdSipStatusFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
)
{
    /*****************************************************************
            Field               |      Length
            ACT_NAI_ENTRY_INDEX |        4

            RESERVED            |        4

     ******************************************************************/
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;

    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();

    /* Read file fail */
    if ((VOS_OK != pUsimTafMsg->stCmdResult.ulResult)
     || (0 == pUsimTafMsg->usEfLen))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipStatusFileCnf: Read 3GPD SIP STATUS FILE FAIL");
        return;
    }

    if (TAF_APS_3GPD_SIP_STATUS_FILE_LENGTH != pUsimTafMsg->usEfLen)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_APS_Read3GpdSipStatusFileCnf(): Parse Content Failed! usEfLen is 0");
        return;
    }

    pst3GpdOpInfoAddr->ucTafAps3GdpCurrActSipNaiIndex = (pUsimTafMsg->aucEf[0] & 0xF0) >> 4;

    return;
}

VOS_VOID TAF_APS_Read3GpdSipPapSsFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
)
{
    /*****************************************************************
        first byte is the whole length of content

            Field               |      Length
            NUM_NAI             |        4

            NAI_ENTRY_INDEX     |        4
            SS_LENGTH           |        5
            SS                  |        8 * SS_LENGTH

            RESERVED            |        0 to 7 (as needed)
     ******************************************************************/

    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucNaiNum;
    VOS_UINT8                           ucSsContentLength;
    VOS_UINT8                           ucSingleSsContentBitLen;
    VOS_UINT8                          *pucSrcAddr;
    VOS_UINT8                          *pucTempAddr;
    VOS_UINT8                           ucOffsetPos;
    VOS_UINT8                           ucPapSsIndex;

    pst3GpdOpInfoAddr       = TAF_APS_Get3GpdOpInfoAddr();
    ucSingleSsContentBitLen = 0;
    ucSsContentLength       = 0;

    /* Read file fail */
    if ((VOS_OK != pUsimTafMsg->stCmdResult.ulResult)
     || (0 == pUsimTafMsg->usEfLen))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipPapSsFileCnf: Read 3GPD SIP PPP SS FILE FAIL");
        return;
    }

    pucSrcAddr = PS_MEM_ALLOC(WUEPS_PID_TAF, (pUsimTafMsg->usEfLen + 1));

    if (VOS_NULL_PTR == pucSrcAddr)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipPapSsFileCnf: alloc memory  FAIL");
        return;
    }

    PS_MEM_CPY(pucSrcAddr, pUsimTafMsg->aucEf, pUsimTafMsg->usEfLen + 1);

    ucSsContentLength = pucSrcAddr[0];

    if (0 == ucSsContentLength)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipPapSsFileCnf: 3GPD SIP PPP SS content length is zero");
        PS_MEM_FREE(WUEPS_PID_TAF, pucSrcAddr);
        return;
    }

    /* nai 个数 */
    ucNaiNum = (pucSrcAddr[1] & 0xF0) >> 4;
    if (0 == ucNaiNum)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipPapSsFileCnf:  3GPD sip user profile NUM VALUE illegal");
        PS_MEM_FREE(WUEPS_PID_TAF, pucSrcAddr);
        return;
    }
    pst3GpdOpInfoAddr->st3GpdSipPapSs.ucPapSsNum = ucNaiNum;


    /* 解析pap ss 码流 */
    pucTempAddr     = &(pucSrcAddr[1]);
    ucOffsetPos     = TAF_APS_BIT_LEN_8_BITS - TAF_APS_3GPD_SIP_SS_NAI_NUM_BIT_LEN;
    ucPapSsIndex    = 0;
    while (ucNaiNum)
    {
        if (VOS_TRUE != TAF_APS_Parse3GpdSingleSipSsContent(pucTempAddr,
                                                            ucOffsetPos,
                                                            ucPapSsIndex,
                                                            &ucSingleSsContentBitLen))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Read3GpdSipPapSsFileCnf: Parse 3GPD SIP PPP SS FILE FAIL");
            PS_MEM_SET(&(pst3GpdOpInfoAddr->st3GpdSipPapSs), 0, sizeof(TAF_APS_3GPD_SIP_PAP_SS_STRU));
            PS_MEM_FREE(WUEPS_PID_TAF, pucSrcAddr);
            return;
        }

        ucNaiNum--;

        pucTempAddr += (ucOffsetPos + ucSingleSsContentBitLen)/TAF_APS_BIT_LEN_8_BITS;
        ucOffsetPos = (ucOffsetPos + ucSingleSsContentBitLen)%TAF_APS_BIT_LEN_8_BITS;
        ucPapSsIndex++;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pucSrcAddr);
    return;
}

VOS_UINT8 TAF_APS_Parse3GpdSingleSipSsContent(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucPapSsIndex,
    VOS_UINT8                          *pucSingleSsContentBitLen
)
{
    /*****************************************************************
            NAI_ENTRY_INDEX     |        4
            SS_LENGTH           |        5
            SS                  |        8 * SS_LENGTH
     ******************************************************************/
    VOS_UINT8                          *pucBuffOffset = VOS_NULL_PTR;
    VOS_UINT8                           ucRemainBitLen;
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucSsLen;
    VOS_UINT8                           ucPapNaiIndexHigh;
    VOS_UINT8                           ucPapNaiIndexLow;
    VOS_UINT8                           ucTempOffset;
    VOS_UINT8                          *pucSsStrPos;

    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();
    pucBuffOffset       = pucSrcAddr;
    ucRemainBitLen      = (VOS_UINT8)(TAF_APS_BIT_LEN_8_BITS - ucOffsetPos);
    ucSsLen             = 0;
    ucPapNaiIndexHigh   = 0;
    ucPapNaiIndexLow    = 0;
    ucTempOffset        = 0;

    /* 如果第一个字节剩余bit长度大于4，则直接在该字节中进行取值 */
    /* 如果第一个字节剩余bit长度等于4，则直接在该字节中进行取值 */
    /* 如果第一个字节剩余bit长度小于于4,则还需要从下一个字节中进行取值*/
    if (TAF_APS_3GPD_SIP_SS_NAI_INDEX_BIT_LEN < ucRemainBitLen)
    {
        /* ss index */
        pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucPapSsIndex].ucNaiEntryIndex = (VOS_UINT8)(((VOS_UINT8)((VOS_UINT32)*pucBuffOffset << ucOffsetPos) & 0xf0) >> 4);

        /* ss length */
        /***********************************************************************************************************
         offsetpos is b7,so nai index is b6~b3, ss length is b2~b1 of the first byte and b8~b6 of the second byte

            b8 b7  |     b6 b5 b4 b3        | b2 b1     b8 b7 b6 | b5 b4 b3 b2 b1

            offset     NAI_ENTRY_INDEX          SS_LENGTH
         ************************************************************************************************************/

        ucTempOffset = ucOffsetPos + TAF_APS_3GPD_SIP_SS_NAI_INDEX_BIT_LEN;
        if (VOS_TRUE != TAF_APS_ParseSipPapSsLen(pucBuffOffset,
                                                 ucTempOffset,
                                                 &ucSsLen,
                                                 ucPapSsIndex))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Parse3GpdSipSsContent: 3GPD SIP PPP SS length is illegal");
            return VOS_FALSE;
        }

        /* ss str */
        pucSsStrPos = pucBuffOffset + (TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN + ucTempOffset)/TAF_APS_BIT_LEN_8_BITS;
        TAF_APS_ParseSipPapSsStr(pucSsStrPos,
                                (1 + ucOffsetPos),
                                 ucSsLen,
                                 ucPapSsIndex);

    }
    else if (TAF_APS_3GPD_SIP_SS_NAI_INDEX_BIT_LEN == ucRemainBitLen)
    {
        /* ss index */
        pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucPapSsIndex].ucNaiEntryIndex = *pucBuffOffset & 0x0f;
        pucBuffOffset++;

        /* ss length */
        /***********************************************************************************************************
         offsetpos is b7,so nai index is b6~b3, ss length is b2~b1 of the first byte and b8~b6 of the second byte

            b8 b7 b6 b5  |      b4 b3 b2 b1       |  b8 b7 b6 b5 b4 |  b3 b2 b1

            offset            NAI_ENTRY_INDEX          SS_LENGTH
         ************************************************************************************************************/
        if (VOS_TRUE != TAF_APS_ParseSipPapSsLen(pucBuffOffset,
                                                 0,
                                                 &ucSsLen,
                                                 ucPapSsIndex))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Parse3GpdSipSsContent: 3GPD SIP PPP SS length is illegal");
            return VOS_FALSE;
        }

        /* ss str */
        pucSsStrPos = pucBuffOffset;
        TAF_APS_ParseSipPapSsStr(pucSsStrPos,
                                 TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN,
                                 ucSsLen,
                                 ucPapSsIndex);

    }
    else
    {
        /***********************************************************************************************************
         offsetpos is b7,so nai index is b6~b3, ss length is b2~b1 of the first byte and b8~b6 of the second byte

            b8 b7 b6 b5  b4 b3  |   b2 b1 b8 b7     |  b6 b5 b4 b3 b2 |  b1

            offset                NAI_ENTRY_INDEX        SS_LENGTH
         ************************************************************************************************************/
        /* ss index */
        ucPapNaiIndexHigh = (VOS_UINT8)((VOS_UINT8)((VOS_UINT32)*pucBuffOffset << ucOffsetPos) & 0xf0);
        ucPapNaiIndexLow  = (VOS_UINT8)(*(pucBuffOffset + 1)) >> (TAF_APS_BIT_LEN_8_BITS - ucOffsetPos);
        pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucPapSsIndex].ucNaiEntryIndex = ((ucPapNaiIndexHigh | ucPapNaiIndexLow) & 0xf0) >> 4;
        pucBuffOffset++;

        /* ss length */
        ucTempOffset = TAF_APS_3GPD_SIP_SS_NAI_INDEX_BIT_LEN - (TAF_APS_BIT_LEN_8_BITS - ucOffsetPos);
        if (VOS_TRUE != TAF_APS_ParseSipPapSsLen(pucBuffOffset,
                                                 ucTempOffset,
                                                 &ucSsLen,
                                                 ucPapSsIndex))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Parse3GpdSipSsContent: 3GPD SIP PPP SS length is illegal");
            return VOS_FALSE;
        }

        /* ss str */
        ucTempOffset += TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN;
        if (TAF_APS_BIT_LEN_8_BITS == ucTempOffset)
        {
            ucTempOffset = 0;
            pucSsStrPos  = pucBuffOffset++;
        }
        else
        {
            pucSsStrPos = pucBuffOffset + ucTempOffset/TAF_APS_BIT_LEN_8_BITS;
        }

        TAF_APS_ParseSipPapSsStr(pucSsStrPos,
                                 ucTempOffset,
                                 ucSsLen,
                                 ucPapSsIndex);

    }

    *pucSingleSsContentBitLen = (VOS_UINT8)(TAF_APS_BIT_LEN_8_BITS*ucSsLen + TAF_APS_3GPD_SIP_SS_NAI_INDEX_BIT_LEN + TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN);

    return VOS_TRUE;
}

VOS_UINT8 TAF_APS_ParseSipPapSsLen(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                          *pucSslen,
    VOS_UINT8                           ucPapSsIndex
)
{
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucSsLen;
    VOS_UINT8                           ucSsLenHigh;
    VOS_UINT8                           ucSsLenLow;
    VOS_UINT8                           ucRemainBitLen;

    ucRemainBitLen      = (VOS_UINT8)(TAF_APS_BIT_LEN_8_BITS - ucOffsetPos);
    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();
    ucSsLen             = 0;
    ucSsLenHigh         = 0;
    ucSsLenLow          = 0;

    /* 如果第一个字节剩余bit长度大于TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN，则直接在该字节中进行取值 */
    /* 如果第一个字节剩余bit长度等于TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN，则直接在该字节中进行取值 */
    /* 如果第一个字节剩余bit长度小于TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN,则还需要从下一个字节中进行取值*/
    if (TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN <= ucRemainBitLen)
    {
        /***********************************************************************************************************
         offsetpos is b7,so nai index is b6~b3, ss length is b2~b1 of the first byte and b8~b6 of the second byte

                    b8 b7    |       b6 b5 b4 b3 b2 b1

                  offset             SS_LENGTH
         ************************************************************************************************************/


        ucSsLen = (VOS_UINT8)(((VOS_UINT8)((VOS_UINT32)*pucSrcAddr << ucOffsetPos) & 0xf8) >> (TAF_APS_BIT_LEN_8_BITS - TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN));
    }
    else
    {
        /***********************************************************************************************************
         offsetpos is b7,so nai index is b6~b3, ss length is b2~b1 of the first byte and b8~b6 of the second byte

            b8 b7  b6 b5 b4 b3  | b2 b1     b8 b7 b6 | b5 b4 b3 b2 b1

                  offset             SS_LENGTH
         ************************************************************************************************************/
        ucSsLenHigh = (VOS_UINT8)((VOS_UINT8)((VOS_UINT32)*pucSrcAddr << ucOffsetPos) & 0xf0);
        ucSsLenLow  = (((VOS_UINT8)(*(pucSrcAddr + 1)) & 0xf0)) >> (TAF_APS_BIT_LEN_8_BITS - ucOffsetPos);

        ucSsLen = ((ucSsLenHigh | ucSsLenLow) & 0xf8) >> (TAF_APS_BIT_LEN_8_BITS - TAF_APS_3GPD_SIP_SS_LENGTH_BIT_LEN);
    }

    if (pst3GpdOpInfoAddr->st3GpdSipCapa.ucMaxSsLength < ucSsLen)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Parse3GpdSipSsContent: 3GPD SIP PPP SS length is illegal");
        return VOS_FALSE;
    }

    *pucSslen  = ucSsLen;
    pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucPapSsIndex].ucPapSsLength = ucSsLen;

    return VOS_TRUE;
}


VOS_VOID TAF_APS_ParseSipPapSsStr(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucSsLen,
    VOS_UINT8                           ucPapSsIndex
)
{
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucSsLenIndex;
    VOS_UINT8                          *pucBuffOffset = VOS_NULL_PTR;
    VOS_UINT8                           ucSsHigh;
    VOS_UINT8                           ucSsLow;

    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();
    pucBuffOffset       = pucSrcAddr;

    for (ucSsLenIndex = 0; ucSsLenIndex < ucSsLen; ucSsLenIndex++)
    {
        ucSsHigh = (VOS_UINT8)((VOS_UINT8)((VOS_UINT32)*pucBuffOffset << ucOffsetPos) & 0xff);
        ucSsLow  = (VOS_UINT8)(*(pucBuffOffset + 1)) >> (TAF_APS_BIT_LEN_8_BITS - ucOffsetPos);

        pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucPapSsIndex].aucPapSsStr[ucSsLenIndex] = (ucSsHigh | ucSsLow);
        pucBuffOffset++;
    }
    return;
}

VOS_UINT32 TAF_APS_Get3GpdPppSipNaiInfoFromCard(
    TAF_APS_3GPD_SIP_INFO_STRU         *pst3GpdSipInfo
)
{
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucNaiIndex;
    VOS_UINT8                           ucIndex;

    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();

    ucNaiIndex = pst3GpdOpInfoAddr->ucTafAps3GdpCurrActSipNaiIndex;

    /* 卡中用户名信息为空 */
    if ((0 == pst3GpdOpInfoAddr->st3GpdSipUserProfile.ucNaiNum)
      ||(ucNaiIndex >= pst3GpdOpInfoAddr->st3GpdSipUserProfile.ucNaiNum))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Get3GpdPppSipNaiInfo() USER INFO IS EMPTY! ");
        return VOS_FALSE;
    }

    for (ucIndex = 0; ucIndex < pst3GpdOpInfoAddr->st3GpdSipUserProfile.ucNaiNum; ucIndex++)
    {
        if ((ucNaiIndex == pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiIndex)
         && (0 != pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiLength))
        {
            pst3GpdSipInfo->ucNaiLength = pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiLength;
            if ((TAF_APS_MAX_SIP_NAI_LENGTH < pst3GpdSipInfo->ucNaiLength)
              ||(TAF_APS_MIN_SIP_NAI_LENGTH > pst3GpdSipInfo->ucNaiLength))
            {
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Get3GpdPppSipNaiInfo() USER INFO IS invalid! ");
                return VOS_FALSE;
            }
            pst3GpdSipInfo->enPppAuthType  = TAF_APS_Map3GpdAuthTypeToPpp(pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucAuthAlgorithm);
            PS_MEM_CPY( pst3GpdSipInfo->aucNaiStr,
                        pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].aucNaiStr,
                        pst3GpdOpInfoAddr->st3GpdSipUserProfile.stSipUserProfile[ucIndex].ucNaiLength);
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_Get3GpdPppSipPapSsInfoFromCard(
    TAF_APS_3GPD_SIP_INFO_STRU         *pst3GpdSipInfo
)
{
    TAF_APS_3GPD_OPERATION_INFO_STRU   *pst3GpdOpInfoAddr;
    VOS_UINT8                           ucNaiIndex;
    VOS_UINT8                           ucIndex;

    pst3GpdOpInfoAddr   = TAF_APS_Get3GpdOpInfoAddr();

    ucNaiIndex = pst3GpdOpInfoAddr->ucTafAps3GdpCurrActSipNaiIndex;

    /* 卡中密码信息为空 */
    if ((0 == pst3GpdOpInfoAddr->st3GpdSipPapSs.ucPapSsNum)
      ||(ucNaiIndex >= pst3GpdOpInfoAddr->st3GpdSipPapSs.ucPapSsNum))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Get3GpdPppSipPapSsInfo() PAP Ss info IS EMPTY! ");
        return VOS_FALSE;
    }

    for (ucIndex = 0; ucIndex < pst3GpdOpInfoAddr->st3GpdSipPapSs.ucPapSsNum; ucIndex++)
    {
        if ((ucNaiIndex == pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucIndex].ucNaiEntryIndex)
         && (0 != pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucIndex].ucPapSsLength))
        {
            pst3GpdSipInfo->ucPapSsLength = pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucIndex].ucPapSsLength;
            if (TAF_APS_MAX_SIPPAPSS_LENGTH < pst3GpdSipInfo->ucNaiLength)
            {
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_Get3GpdPppSipPapSsInfoFromCard() pswd INFO IS invalid! ");
                return VOS_FALSE;
            }
            PS_MEM_CPY( pst3GpdSipInfo->aucPapSsStr,
                        pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucIndex].aucPapSsStr,
                        pst3GpdOpInfoAddr->st3GpdSipPapSs.stSipPapSs[ucIndex].ucPapSsLength);
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}


TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32 TAF_APS_Map3GpdFileIdAndFlag(
    USIMM_DEF_FILEID_ENUM_UINT32          usEfId
)
{
    TAF_APS_3GPD_FILEID_FLAG_MAP_STRU  *pst3GpdFileIdFlagMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulGpdFileIdFlagMapTblSize;
    VOS_UINT32                          ulCnt;

    pst3GpdFileIdFlagMapTblPtr = TAF_APS_3GPD_FILEID_FLAG_MAP_TBL_PTR();
    ulGpdFileIdFlagMapTblSize = TAF_APS_3GPD_FILEID_FLAG_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulGpdFileIdFlagMapTblSize; ulCnt++)
    {
        if (pst3GpdFileIdFlagMapTblPtr[ulCnt].usEfId == usEfId)
        {
            return pst3GpdFileIdFlagMapTblPtr[ulCnt].enSimFileCnfFlg;
        }
    }

    return TAF_APS_READ_USIM_FILE_CNF_BUTT;
}



VOS_UINT32 TAF_APS_IsSyscfgCdmaModeChange(
    TAF_MMA_RAT_ORDER_STRU             *pstOldRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstNewRatOrder
)
{
    VOS_UINT32                          ulOldExistCmode;
    VOS_UINT32                          ulNewExistCmode;

    if (0 == PS_MEM_CMP(pstNewRatOrder, pstOldRatOrder, sizeof(TAF_MMA_RAT_ORDER_STRU)))
    {
        return VOS_FALSE;
    }

    /* 获取原有模式列表中是否存在C模 */
    ulOldExistCmode  = TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_1X, pstOldRatOrder);
    ulOldExistCmode |= TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_HRPD, pstOldRatOrder);

    /* 获取新的模式列表中是否存在C模 */
    ulNewExistCmode  = TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_1X, pstNewRatOrder);
    ulNewExistCmode |= TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_HRPD, pstNewRatOrder);

    /* 判断是否有GUL<->CL模式的切换 */
    if (ulOldExistCmode == ulNewExistCmode)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID TAF_APS_LocalReleaseAll(VOS_VOID)
{
    VOS_UINT8                   ucPdpId;
    TAF_APS_STA_ENUM_UINT32     enState;
    APS_PDP_CONTEXT_ENTITY_ST  *pstPdpEntity = VOS_NULL_PTR;

    for ( ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++ )
    {
        enState      = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (TAF_APS_STA_INACTIVE != enState)
        {
            if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
              && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
            {
                (VOS_VOID)Aps_SmMsgModSnDeActInd(ucPdpId);
            }

            /* 通知SM本地去激活 */
            TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);

            /* 通知ESM本地去激活 */
            MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);

            /* 通知EHSM本地去激活 */
            TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

            /* 通知PPPC本地去激活 */
            if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
            {
                TAF_APS_SndPppDeactInd(ucPdpId);
            }

            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SYSCFG_MODE_CHANGE);

            /* 通知DHCP去激活 */
            TAF_APS_SndDhcpDeactInd(ucPdpId);

       }
    }

    TAF_APS_SaveDsFlowInfoToNv();

    TAF_APS_ReleaseDfs();

#if (FEATURE_ON == FEATURE_IPV6)
    TAF_APS_SndNdRelInd();
#endif

    /* 停止所有定时器*/
    TAF_APS_StopAllTimer();

    /*调用初始化函数:*/
    Aps_PdpEntityInit();

    /* APS CTX模块初始化 */
    TAF_APS_InitCtx();

    /* 本地释放, 不会走正常的状态机流程, 需要主动通知一下STK当前的PS域呼叫状态 */
    TAF_APS_SndStkPsCallEvent();

    return;
}


#endif


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


