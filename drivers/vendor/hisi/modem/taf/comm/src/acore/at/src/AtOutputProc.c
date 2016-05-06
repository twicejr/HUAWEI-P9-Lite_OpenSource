

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtInputProc.h"
#include "AtDataProc.h"
#include "cpm.h"
#include "AtTafAgentInterface.h"
#include "AtEventReport.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


 /*****************************************************************************
   2 结构定义
 *****************************************************************************/
#ifdef __PS_WIN32_RECUR__
#define PID_AT_STUB               (278)
#endif

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_OUTPUTPROC_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/

const AT_RETURN_TAB_TYPE_STRU gastAtReturnCodeTab[]=
{
    {AT_SUCCESS,                                           {TAF_NULL_PTR,          TAF_NULL_PTR             }  },
    {AT_FAILURE,                                           {TAF_NULL_PTR,          TAF_NULL_PTR             }  },
    {AT_WAIT_SMS_INPUT,                                    {(TAF_UINT8*)"\r\n> ", (TAF_UINT8*)"\r\n> "      }  },
    {AT_WAIT_XML_INPUT,                                    {(TAF_UINT8*)"\r\n> ", (TAF_UINT8*)"\r\n> "      }  },
    {AT_WAIT_ASYNC_RETURN,                                 {TAF_NULL_PTR,          TAF_NULL_PTR             }  },

    {AT_BASIC_CODE_ENUM_BEGAIN,                            {TAF_NULL_PTR,          TAF_NULL_PTR             }  },

    {AT_OK,                                                {(TAF_UINT8*)"0", (TAF_UINT8*)"OK"           }},
    {AT_CONNECT,                                           {(TAF_UINT8*)"1", (TAF_UINT8*)"CONNECT"      }},
    {AT_RING,                                              {(TAF_UINT8*)"2", (TAF_UINT8*)"RING"         }},
    {AT_NO_CARRIER,                                        {(TAF_UINT8*)"3", (TAF_UINT8*)"NO CARRIER"   }},
    {AT_ERROR,                                             {(TAF_UINT8*)"4", (TAF_UINT8*)"ERROR"        }},
    {AT_NO_DIALTONE,                                       {(TAF_UINT8*)"6", (TAF_UINT8*)"NO DIALTONE"  }},
    {AT_BUSY,                                              {(TAF_UINT8*)"7", (TAF_UINT8*)"BUSY"         }},
    {AT_NO_ANSWER,                                         {(TAF_UINT8*)"8", (TAF_UINT8*)"NO ANSWER"    }},
    {AT_BASIC_CODE_ENUM_END,                               {TAF_NULL_PTR,     TAF_NULL_PTR              }  },
    {AT_CME_ERROR_ENUM_BEGAIN,                             {TAF_NULL_PTR,     TAF_NULL_PTR              }  },
    {AT_CME_PHONE_FAILURE,                                 {(TAF_UINT8*)"0" , (TAF_UINT8*)"phone failure"                                  }  },
    {AT_CME_NO_CONNECTION_TO_PHONE,                        {(TAF_UINT8*)"1" , (TAF_UINT8*)"NO CONNECTION TO PHONE"                         }  },
    {AT_CME_PHONE_ADAPTOR_LINK_RESERVED,                   {(TAF_UINT8*)"2" , (TAF_UINT8*)"PHONE ADAPTOR LINK RESERVED"                    }  },
    {AT_CME_OPERATION_NOT_ALLOWED,                         {(TAF_UINT8*)"3" , (TAF_UINT8*)"operation not allowed"                          }  },
    {AT_CME_OPERATION_NOT_SUPPORTED,                       {(TAF_UINT8*)"4" , (TAF_UINT8*)"operation not supported"                        }  },
    {AT_CME_PH_SIM_PIN_REQUIRED,                           {(TAF_UINT8*)"5" , (TAF_UINT8*)"PH SIM PIN REQUIRED"                            }  },
    {AT_CME_PH_FSIM_PIN_REQUIRED,                          {(TAF_UINT8*)"6" , (TAF_UINT8*)"PH-FSIM PIN REQUIRED"                           }  },
    {AT_CME_PH_FSIM_PUK_REQUIRED,                          {(TAF_UINT8*)"7" , (TAF_UINT8*)"PH-FSIM PUK REQUIRED"                           }  },
    {AT_CME_SIM_NOT_INSERTED,                              {(TAF_UINT8*)"10", (TAF_UINT8*)"SIM not inserted"                               }  },
    {AT_CME_SIM_PIN_REQUIRED,                              {(TAF_UINT8*)"11", (TAF_UINT8*)"SIM PIN required"                               }  },
    {AT_CME_SIM_PUK_REQUIRED,                              {(TAF_UINT8*)"12", (TAF_UINT8*)"SIM PUK required"                               }  },
    {AT_CME_SIM_FAILURE,                                   {(TAF_UINT8*)"13", (TAF_UINT8*)"SIM failure"                                    }  },
    {AT_CME_SIM_BUSY,                                      {(TAF_UINT8*)"14", (TAF_UINT8*)"SIM busy"                                       }  },
    {AT_CME_SIM_WRONG,                                     {(TAF_UINT8*)"15", (TAF_UINT8*)"SIM wrong"                                      }  },
    {AT_CME_INCORRECT_PASSWORD,                            {(TAF_UINT8*)"16", (TAF_UINT8*)"incorrect password"                             }  },
    {AT_CME_SIM_PIN2_REQUIRED,                             {(TAF_UINT8*)"17", (TAF_UINT8*)"SIM PIN2 required"                              }  },
    {AT_CME_SIM_PUK2_REQUIRED,                             {(TAF_UINT8*)"18", (TAF_UINT8*)"SIM PUK2 required"                              }  },
    {AT_CME_MEMORY_FULL,                                   {(TAF_UINT8*)"20", (TAF_UINT8*)"memory full"                                    }  },
    {AT_CME_INVALID_INDEX,                                 {(TAF_UINT8*)"21", (TAF_UINT8*)"invalid index"                                  }  },
    {AT_CME_NOT_FOUND,                                     {(TAF_UINT8*)"22", (TAF_UINT8*)"not found"                                      }  },
    {AT_CME_MEMORY_FAILURE,                                {(TAF_UINT8*)"23", (TAF_UINT8*)"memory failure"                                 }  },
    {AT_CME_TEXT_STRING_TOO_LONG,                          {(TAF_UINT8*)"24", (TAF_UINT8*)"text string too long"                           }  },
    {AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING,             {(TAF_UINT8*)"25", (TAF_UINT8*)"INVALID CHARACTERS IN TEXT STRING"              }  },
    {AT_CME_DIAL_STRING_TOO_LONG,                          {(TAF_UINT8*)"26", (TAF_UINT8*)"dial string too long"                           }  },
    {AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING,             {(TAF_UINT8*)"27", (TAF_UINT8*)"invalid characters in dial string"              }  },

    {AT_CME_SPN_FILE_CONTENT_ERROR,                        {(TAF_UINT8*)"65284", (TAF_UINT8*)"SPN FILE CONTENT ERROR"                      }  },
    {AT_CME_SPN_FILE_QUERY_REJECT,                         {(TAF_UINT8*)"65285", (TAF_UINT8*)"READ SPN FILE REJECTED"                      }  },
    {AT_CME_SPN_FILE_NOT_EXISTS,                           {(TAF_UINT8*)"65286", (TAF_UINT8*)"SPN FILE NOT EXIST"                          }  },

    {AT_CME_NO_NETWORK_SERVICE,                            {(TAF_UINT8*)"30",  (TAF_UINT8*)"NO NETWORK SERVICE"                             }  },
    {AT_CME_NETWORK_TIMEOUT,                               {(TAF_UINT8*)"31",  (TAF_UINT8*)"NETWORK TIMEOUT"                                }  },
    {AT_CME_NETWORK_NOT_ALLOWED_EMERGENCY_CALLS_ONLY,      {(TAF_UINT8*)"32",  (TAF_UINT8*)"NETWORK NOT ALLOWED - EMERGENCY CALLS ONLY"     }  },
    {AT_CME_NETWORK_PERSONALIZATION_PIN_REQUIRED,          {(TAF_UINT8*)"40",  (TAF_UINT8*)"NETWORK PERSONALIZATION PIN REQUIRED"           }  },
    {AT_CME_NETWORK_PERSONALIZATION_PUK_REQUIRED,          {(TAF_UINT8*)"41",  (TAF_UINT8*)"NETWORK PERSONALIZATION PUK REQUIRED"           }  },
    {AT_CME_NETWORK_SUBSET_PERSONALIZATION_PIN_REQUIRED,   {(TAF_UINT8*)"42",  (TAF_UINT8*)"NETWORK SUBSET PERSONALIZATION PIN REQUIRED"    }  },
    {AT_CME_NETWORK_SUBSET_PERSONALIZATION_PUK_REQUIRED,   {(TAF_UINT8*)"43",  (TAF_UINT8*)"NETWORK SUBSET PERSONALIZATION PUK REQUIRED"    }  },
    {AT_CME_SERVICE_PROVIDER_PERSONALIZATION_PIN_REQUIRED, {(TAF_UINT8*)"44",  (TAF_UINT8*)"SERVICE PROVIDER PERSONALIZATION PIN REQUIRED"  }  },
    {AT_CME_SERVICE_PROVIDER_PERSONALIZATION_PUK_REQUIRED, {(TAF_UINT8*)"45",  (TAF_UINT8*)"SERVICE PROVIDER PERSONALIZATION PUK REQUIRED"  }  },
    {AT_CME_CORPORATE_PERSONALIZATION_PIN_REQUIRED,        {(TAF_UINT8*)"46",  (TAF_UINT8*)"CORPORATE PERSONALIZATION PIN REQUIRED"         }  },
    {AT_CME_CORPORATE_PERSONALIZATION_PUK_REQUIRED,        {(TAF_UINT8*)"47",  (TAF_UINT8*)"CORPORATE PERSONALIZATION PUK REQUIRED"         }  },
    {AT_CME_HIDDEN_KEY_REQUIRED,                           {(TAF_UINT8*)"48",  (TAF_UINT8*)"hidden key required"                            }  },
    {AT_CME_EAP_METHOD_NOT_SUPPORTED,                      {(TAF_UINT8*)"49",  (TAF_UINT8*)"EAP method not supported"                       }  },
    {AT_CME_INCORRECT_PARAMETERS,                          {(TAF_UINT8*)"50",  (TAF_UINT8*)"Incorrect parameters"                           }  },
    {AT_CME_RX_DIV_NOT_SUPPORTED,                          {(TAF_UINT8*)"0" ,  (TAF_UINT8*)"NOT SUPPORTED"                                  }  },
    {AT_CME_RX_DIV_OTHER_ERR,                              {(TAF_UINT8*)"1" ,  (TAF_UINT8*)"OTHER ERROR"                                    }  },
    {AT_CME_UNKNOWN,                                       {(TAF_UINT8*)"100", (TAF_UINT8*)"UNKNOWN"                                        }  },

    {AT_CME_ILLEGAL_MS,                                    {(TAF_UINT8*)"103", (TAF_UINT8*)"Illegal MS"                                     }  },
    {AT_CME_ILLEGAL_ME,                                    {(TAF_UINT8*)"106", (TAF_UINT8*)"Illegal ME"                                     }  },
    {AT_CME_GPRS_SERVICES_NOT_ALLOWED,                     {(TAF_UINT8*)"107", (TAF_UINT8*)"GPRS services not allowed"                      }  },
    {AT_CME_PLMN_NOT_ALLOWED,                              {(TAF_UINT8*)"111", (TAF_UINT8*)"PLMN not allowed"                               }  },
    {AT_CME_LOCATION_AREA_NOT_ALLOWED,                     {(TAF_UINT8*)"112", (TAF_UINT8*)"Location area not allowed"                      }  },
    {AT_CME_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA,     {(TAF_UINT8*)"113", (TAF_UINT8*)"Roaming not allowed in this location area"      }  },

    {AT_CME_SERVICE_OPTION_NOT_SUPPORTED,                  {(TAF_UINT8*)"132", (TAF_UINT8*)"service option not supported"                   }  },
    {AT_CME_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED,       {(TAF_UINT8*)"133", (TAF_UINT8*)"requested service option not subscribed"        }  },
    {AT_CME_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER,       {(TAF_UINT8*)"134", (TAF_UINT8*)"service option temporarily out of order"        }  },
    {AT_CME_PDP_AUTHENTICATION_FAILURE,                    {(TAF_UINT8*)"149", (TAF_UINT8*)"PDP authentication failure"                     }  },

    {AT_CME_INVALID_MOBILE_CLASS,                          {(TAF_UINT8*)"150" ,(TAF_UINT8*)"invalid mobile class"                           }  },
    {AT_CME_UNSPECIFIED_GPRS_ERROR,                        {(TAF_UINT8*)"148" ,(TAF_UINT8*)"unspecified GPRS error"                         }  },

    {AT_CME_VBS_VGCS_NOT_SUPPORTED_BY_THE_NETWORK,         {(TAF_UINT8*)"151", (TAF_UINT8*)"VBS/VGCS not supported by the network"          }  },
    {AT_CME_NO_SERVICE_SUBSCRIPTION_ON_SIM,                {(TAF_UINT8*)"152", (TAF_UINT8*)"No service subscription on SIM"                 }  },
    {AT_CME_NO_SUBSCRIPTION_FOR_GROUP_ID,                  {(TAF_UINT8*)"153", (TAF_UINT8*)"No subscription for group ID"                   }  },
    {AT_CME_GROUP_ID_NOT_ACTIVATED_ON_SIM,                 {(TAF_UINT8*)"154", (TAF_UINT8*)"Group Id not activated on SIM"                  }  },
    {AT_CME_NO_MATCHING_NOTIFICATION,                      {(TAF_UINT8*)"155", (TAF_UINT8*)"No matching notification"                       }  },
    {AT_CME_VBS_VGCS_CALL_ALREADY_PRESENT,                 {(TAF_UINT8*)"156", (TAF_UINT8*)"VBS/VGCS call already present"                  }  },
    {AT_CME_CONGESTION,                                    {(TAF_UINT8*)"157", (TAF_UINT8*)"Congestion"                                     }  },
    {AT_CME_NETWORK_FAILURE,                               {(TAF_UINT8*)"158", (TAF_UINT8*)"Network failure"                                }  },
    {AT_CME_UPLINK_BUSY,                                   {(TAF_UINT8*)"159", (TAF_UINT8*)"Uplink busy"                                    }  },
    {AT_CME_NO_ACCESS_RIGHTS_FOR_SIM_FILE,                 {(TAF_UINT8*)"160", (TAF_UINT8*)"No access rights for SIM file"                  }  },
    {AT_CME_NO_SUBSCRIPTION_FOR_PRIORITY,                  {(TAF_UINT8*)"161", (TAF_UINT8*)"No subscription for priority"                   }  },
    {AT_CME_OPERATION_NOT_APPLICABLE_OR_NOT_POSSIBLE,      {(TAF_UINT8*)"162", (TAF_UINT8*)"operation not applicable or not possible"       }  },
    {AT_CME_FILE_NOT_EXISTS,                               {(TAF_UINT8*)"163", (TAF_UINT8*)"FILE NOT EXIST"                            }  },

    {AT_CME_1X_RAT_NOT_SUPPORTED,                          {(VOS_UINT8*)"170", (VOS_UINT8*)"1X RAT NOT SUPPORTED"                }  },

    {AT_CME_SERVICE_NOT_PROVISIONED,                       {(VOS_UINT8*)"171", (VOS_UINT8*)"Service not provisioned"       }  },

    /* 3GPP 27007 9.2.3 Also all other values below 256 are reserved */
    {AT_CME_PDP_ACT_LIMIT,                                 {(TAF_UINT8*)"300", (TAF_UINT8*)"PDP ACT LIMIT"                            }  },
    {AT_CME_NET_SEL_MENU_DISABLE,                          {(TAF_UINT8*)"301", (TAF_UINT8*)"NETWORK SELECTION MENU DISABLE"           }  },

    {AT_CME_CS_SERV_EXIST,                                 {(TAF_UINT8*)"302", (TAF_UINT8*)"CS SERVICE EXIST"                         }  },

    {AT_CME_FDN_FAILED,                                    {(TAF_UINT8*)"303", (TAF_UINT8*)"FDN Failed"                              }  },
    {AT_CME_CALL_CONTROL_FAILED,                           {(TAF_UINT8*)"304", (TAF_UINT8*)"Call Control Failed"                           }  },
    {AT_CME_CALL_CONTROL_BEYOND_CAPABILITY,                {(TAF_UINT8*)"305", (TAF_UINT8*)"Call Control beyond Capability"                }  },

    {AT_CME_NO_RF,                                         {(TAF_UINT8*)"306"  ,(TAF_UINT8*)"NO RF"                         }  },

    {AT_CME_IMS_NOT_SUPPORT,                               {(VOS_UINT8*)"306", (VOS_UINT8*)"IMS Not Support"                 }  },
    {AT_CME_IMS_SERVICE_EXIST,                             {(VOS_UINT8*)"307", (VOS_UINT8*)"IMS Service Exist"               }  },
    {AT_CME_IMS_VOICE_DOMAIN_PS_ONLY,                      {(VOS_UINT8*)"308", (VOS_UINT8*)"IMS Voice Domain PS Only"              }  },
    {AT_CME_IMS_STACK_TIMEOUT,                             {(VOS_UINT8*)"309", (VOS_UINT8*)"IMS Stack Time Out"              }  },

    {AT_CME_APN_LEN_ILLEGAL,                               {(VOS_UINT8*)"700", (VOS_UINT8*)"APN length illegal"              }  },
    {AT_CME_APN_SYNTACTICAL_ERROR,                         {(VOS_UINT8*)"701", (VOS_UINT8*)"APN syntactical error"           }  },
    {AT_CME_SET_APN_BEFORE_SET_AUTH,                       {(VOS_UINT8*)"702", (VOS_UINT8*)"set APN before set auth"         }  },
    {AT_CME_AUTH_TYPE_ILLEGAL,                             {(VOS_UINT8*)"703", (VOS_UINT8*)"auth type illegal"               }  },
    {AT_CME_USER_NAME_TOO_LONG,                            {(VOS_UINT8*)"704", (VOS_UINT8*)"user name too long"              }  },
    {AT_CME_USER_PASSWORD_TOO_LONG,                        {(VOS_UINT8*)"705", (VOS_UINT8*)"user password too long"          }  },
    {AT_CME_ACCESS_NUM_TOO_LONG,                           {(VOS_UINT8*)"706", (VOS_UINT8*)"access number too long"          }  },
    {AT_CME_CALL_CID_IN_OPERATION,                         {(VOS_UINT8*)"707", (VOS_UINT8*)"call cid in operation"           }  },
    {AT_CME_BEARER_TYPE_NOT_DEFAULT,                       {(VOS_UINT8*)"708", (VOS_UINT8*)"bearer type not default"         }  },
    {AT_CME_CALL_CID_INVALID,                              {(VOS_UINT8*)"709", (VOS_UINT8*)"call cid invalid"                }  },
    {AT_CME_CALL_CID_ACTIVE,                               {(VOS_UINT8*)"710", (VOS_UINT8*)"call cid active"                 }  },
    {AT_CME_BEARER_TYPE_ILLEGAL,                           {(VOS_UINT8*)"711", (VOS_UINT8*)"bearer type illegal"             }  },
    {AT_CME_MUST_EXIST_DEFAULT_TYPE_CID,                   {(VOS_UINT8*)"712", (VOS_UINT8*)"must exist default type cid"     }  },
    {AT_CME_PDN_TYPE_ILLEGAL,                              {(VOS_UINT8*)"713", (VOS_UINT8*)"PDN type illegal"                }  },
    {AT_CME_IPV4_ADDR_ALLOC_TYPE_ILLEGAL,                  {(VOS_UINT8*)"714", (VOS_UINT8*)"IPV4 address alloc type illegal" }  },
    {AT_CME_LINK_CID_INVALID,                              {(VOS_UINT8*)"715", (VOS_UINT8*)"link cid invalid"                }  },
    {AT_CME_NO_SUCH_ELEMENT,                               {(VOS_UINT8*)"716", (VOS_UINT8*)"no such element"                 }  },
    {AT_CME_MISSING_RESOURCE,                              {(VOS_UINT8*)"717", (VOS_UINT8*)"missing resource"                }  },
    {AT_CME_OPERATION_NOT_ALLOWED_IN_CL_MODE,              {(VOS_UINT8*)"718", (VOS_UINT8*)"operation not allowed in CL mode"                }  },
    {AT_CME_ERROR_ENUM_END,                                {TAF_NULL_PTR,       TAF_NULL_PTR                 }  },

    /*装备AT命令错误码提示*/
    {AT_DEVICE_ERROR_BEGIN,                                {VOS_NULL_PTR   ,VOS_NULL_PTR                                     }  },
    {AT_DEVICE_MODE_ERROR,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"Mode Error"                        }  },
    {AT_FCHAN_BAND_NOT_MATCH,                              {(VOS_UINT8*)"1", (VOS_UINT8*)"Band not match"                    }  },
    {AT_FCHAN_SET_CHANNEL_FAIL,                            {(VOS_UINT8*)"2", (VOS_UINT8*)"Channel number set fail"           }  },
    {AT_FCHAN_BAND_CHANNEL_NOT_MATCH,                      {(VOS_UINT8*)"3", (VOS_UINT8*)"Band and Channel not match"        }  },
    {AT_FCHAN_OTHER_ERR,                                   {(VOS_UINT8*)"4", (VOS_UINT8*)"Other error"                       }  },
    {AT_FDAC_CHANNEL_NOT_SET,                              {(VOS_UINT8*)"0", (VOS_UINT8*)"channel not set"                   }  },
    {AT_FDAC_SET_FAIL,                                     {(VOS_UINT8*)"2", (VOS_UINT8*)"Set DAC fail"                      }  },
    {AT_CHANNEL_NOT_SET,                                   {(VOS_UINT8*)"1", (VOS_UINT8*)"channel not set"                   }  },
    {AT_FTXON_SET_FAIL,                                    {(VOS_UINT8*)"2", (VOS_UINT8*)"Set FTXON fail"                    }  },
    {AT_FTXON_OTHER_ERR,                                   {(VOS_UINT8*)"3", (VOS_UINT8*)"other FTXON Error"                 }  },
    {AT_DATA_UNLOCK_ERROR,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"Data UNLock Error:0"               }  },
    {AT_DPAUPA_ERROR,                                      {(VOS_UINT8*)"1", (VOS_UINT8*)"DPA UPA Error:1"                   }  },
    {AT_SN_LENGTH_ERROR,                                   {(VOS_UINT8*)"0", (VOS_UINT8*)"SN LENGTH Error:1"                 }  },
    {AT_FRXON_OTHER_ERR,                                   {(VOS_UINT8*)"3", (VOS_UINT8*)"other FRXON Error"                 }  },
    {AT_FRXON_SET_FAIL,                                    {(VOS_UINT8*)"2", (VOS_UINT8*)"Set FRXON fail"                    }  },
    {AT_FPA_OTHER_ERR,                                     {(VOS_UINT8*)"3", (VOS_UINT8*)"Other FPA error"                   }  },
    {AT_FLNA_OTHER_ERR,                                    {(VOS_UINT8*)"3", (VOS_UINT8*)"Other LNA error"                   }  },
    {AT_FRSSI_OTHER_ERR,                                   {(VOS_UINT8*)"4", (VOS_UINT8*)"Other FRSSI error"                 }  },
    {AT_FRSSI_RX_NOT_OPEN,                                 {(VOS_UINT8*)"2", (VOS_UINT8*)"RX Not Open"                       }  },
    {AT_SD_CARD_NOT_EXIST,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"SD Card Not Exist"                 }  },
    {AT_SD_CARD_INIT_FAILED,                               {(VOS_UINT8*)"1", (VOS_UINT8*)"SD Card init fail"                 }  },
    {AT_SD_CARD_OPRT_NOT_ALLOWED,                          {(VOS_UINT8*)"2", (VOS_UINT8*)"Sd Oprt not allowed"               }  },
    {AT_SD_CARD_ADDR_ERR,                                  {(VOS_UINT8*)"3", (VOS_UINT8*)"Sd Card Address Error"             }  },
    {AT_SD_CARD_OTHER_ERR,                                 {(VOS_UINT8*)"4", (VOS_UINT8*)"Sd Card Other Error"               }  },
    {AT_DEVICE_OTHER_ERROR,                                {(VOS_UINT8*)"1", (VOS_UINT8*)"1"                                 }  },
    {AT_PHYNUM_LENGTH_ERR,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"Physical Number length error"      }  },
    {AT_PHYNUM_NUMBER_ERR,                                 {(VOS_UINT8*)"1", (VOS_UINT8*)"Physical Number number error"      }  },
    {AT_PHYNUM_TYPE_ERR,                                   {(VOS_UINT8*)"2", (VOS_UINT8*)"Physical Number type error"        }  },
    {AT_SIMLOCK_PLMN_NUM_ERR,                              {(VOS_UINT8*)"2", (VOS_UINT8*)"Simlock Plmn num invalid"          }  },
    {AT_SIMLOCK_PLMN_MNC_LEN_ERR,                          {(VOS_UINT8*)"3", (VOS_UINT8*)"Simlock Plmn MNC len Err"          }  },

    {AT_DEVICE_NOT_SUPPORT,                                {(VOS_UINT8*)"500", (VOS_UINT8*)"Undone",                            }},
    {AT_DEVICE_ERR_UNKNOWN,                                {(VOS_UINT8*)"501", (VOS_UINT8*)"Unknown error",                     }},
    {AT_DEVICE_INVALID_PARAMETERS,                         {(VOS_UINT8*)"502", (VOS_UINT8*)"Invalid parameters",                }},
    {AT_DEVICE_NV_NOT_SUPPORT_ID,                          {(VOS_UINT8*)"520", (VOS_UINT8*)"NVIM Not Exist",                    }},
    {AT_DEVICE_NV_READ_FAILURE,                            {(VOS_UINT8*)"521", (VOS_UINT8*)"Read NVIM Failure",                 }},
    {AT_DEVICE_NV_WRITE_FAIL_OVERLEN,                      {(VOS_UINT8*)"522", (VOS_UINT8*)"Write Error for Length Overflow",   }},
    {AT_DEVICE_NV_WRITE_FAIL_BADFLASH,                     {(VOS_UINT8*)"523", (VOS_UINT8*)"Write Error for Flash Bad Block",   }},
    {AT_DEVICE_NV_WRITE_FAIL_UNKNOWN,                      {(VOS_UINT8*)"524", (VOS_UINT8*)"Write Error for Unknown Reason",    }},
    {AT_DEVICE_VCTCXO_OVER_HIGH,                           {(VOS_UINT8*)"525", (VOS_UINT8*)"Higher Voltage",                    }},
    {AT_DEVICE_UE_MODE_ERR,                                {(VOS_UINT8*)"526", (VOS_UINT8*)"UE Mode Error",                     }},
    {AT_DEVICE_NOT_SET_CHAN,                               {(VOS_UINT8*)"527", (VOS_UINT8*)"Not Set Appointed Channel",         }},
    {AT_DEVICE_OPEN_UL_CHAN_ERROR,                         {(VOS_UINT8*)"528", (VOS_UINT8*)"Open TX Transmitter Failure",       }},
    {AT_DEVICE_OPEN_DL_CHAN_ERROR,                         {(VOS_UINT8*)"529", (VOS_UINT8*)"Open RX Transmitter Failure",       }},
    {AT_DEVICE_OPEN_CHAN_ERROR,                            {(VOS_UINT8*)"530", (VOS_UINT8*)"Open Channel Failure",              }},
    {AT_DEVICE_CLOSE_CHAN_ERROR,                           {(VOS_UINT8*)"531", (VOS_UINT8*)"Close Channel Failure",             }},
    {AT_DEVICE_OPERATION_NOT_SUPPORT,                      {(VOS_UINT8*)"532", (VOS_UINT8*)"Not Support",                       }},
    {AT_DEVICE_INVALID_OP,                                 {(VOS_UINT8*)"533", (VOS_UINT8*)"Invalid Operation",                 }},
    {AT_DEVICE_CHAN_BAND_INVALID,                          {(VOS_UINT8*)"534", (VOS_UINT8*)"Band No Match",                     }},
    {AT_DEVICE_SET_CHAN_INFO_FAILURE,                      {(VOS_UINT8*)"535", (VOS_UINT8*)"Set Channel Information Failure",   }},
    {AT_DEVICE_CHAN_BAND_CHAN_NOT_MAP,                     {(VOS_UINT8*)"536", (VOS_UINT8*)"Band And Channel Not Combined",     }},
    {AT_DEVICE_SET_TX_POWER_FAILURE,                       {(VOS_UINT8*)"537", (VOS_UINT8*)"Set TX Transmitter Power Error",    }},
    {AT_DEVICE_SET_PA_LEVEL_FAILURE,                       {(VOS_UINT8*)"538", (VOS_UINT8*)"Set PA Level Failure",              }},
    {AT_DEVICE_NOT_SET_CURRENT_CHAN,                       {(VOS_UINT8*)"539", (VOS_UINT8*)"Not Set Current Channel",           }},
    {AT_DEVICE_CUR_APC_UNAVAILABLE,                        {(VOS_UINT8*)"540", (VOS_UINT8*)"APC Value Can't Be Read",           }},
    {AT_DEVICE_SET_APC_ERR,                                {(VOS_UINT8*)"541", (VOS_UINT8*)"Write APC Failure",                 }},
    {AT_DEVICE_RD_APC_ERR,                                 {(VOS_UINT8*)"542", (VOS_UINT8*)"Read APC Failure",                  }},
    {AT_DEVICE_SET_LNA_ERR,                                {(VOS_UINT8*)"543", (VOS_UINT8*)"Set AAGC Failure",                  }},
    {AT_DEVICE_NOT_OPEN_DL_CHAN,                           {(VOS_UINT8*)"544", (VOS_UINT8*)"RX Transmitter Not Open",           }},
    {AT_DEVICE_NOT_OPEN_UL_CHAN,                           {(VOS_UINT8*)"545", (VOS_UINT8*)"TX Transmitter Not Open",           }},
    {AT_DEVICE_NO_SIGNAL,                                  {(VOS_UINT8*)"546", (VOS_UINT8*)"No Signal",                         }},
    {AT_DEVICE_PHYNUM_LEN_ERR,                             {(VOS_UINT8*)"547", (VOS_UINT8*)"PHY Number Length Error",           }},
    {AT_DEVICE_PHYNUM_INVALID,                             {(VOS_UINT8*)"548", (VOS_UINT8*)"Invalid PHY Number",                }},
    {AT_DEVICE_PHYNUM_TYPE_ERR,                            {(VOS_UINT8*)"549", (VOS_UINT8*)"Invalid PHY Type",                  }},
    {AT_DEVICE_PLATFORM_INFO_UNAVAILABLE,                  {(VOS_UINT8*)"550", (VOS_UINT8*)"Platform Infomation Can't Be Read", }},
    {AT_DEVICE_DATA_LOCK,                                  {(VOS_UINT8*)"551", (VOS_UINT8*)"Not unlock, write error",           }},
    {AT_DEVICE_PLMN_OVER_20,                               {(VOS_UINT8*)"552", (VOS_UINT8*)"Card Number More than 20",          }},
    {AT_DEVICE_MNC_NUM_INVALID,                            {(VOS_UINT8*)"553", (VOS_UINT8*)"<mnc-digital-num> Enter Error",     }},
    {AT_DEVICE_GET_VER_ERR,                                {(VOS_UINT8*)"554", (VOS_UINT8*)"Read Version Failure",              }},
    {AT_DEVICE_PORTLOCK_ERR,                               {(VOS_UINT8*)"555", (VOS_UINT8*)"Operation Failure",                 }},
    {AT_DEVICE_PWD_ERR,                                    {(VOS_UINT8*)"556", (VOS_UINT8*)"Password Error",                    }},
    {AT_DEVICE_TIMEOUT_ERR,                                {(VOS_UINT8*)"557", (VOS_UINT8*)"Timeout",                           }},
    {AT_DEVICE_NOT_ENOUGH_MEMORY,                          {(VOS_UINT8*)"558", (VOS_UINT8*)"No Memory",                         }},
    {AT_DEVICE_SIMM_LOCK,                                  {(VOS_UINT8*)"559", (VOS_UINT8*)"SIM Lock Active",                   }},
    {AT_DEVICE_CLOSE_UL_CHAN_FAILURE,                      {(VOS_UINT8*)"560", (VOS_UINT8*)"Close TX Transmitter Failure",      }},
    {AT_DEVICE_CLOSE_DL_CHAN_FAILURE,                      {(VOS_UINT8*)"561", (VOS_UINT8*)"Close RX Transmitter Failure",      }},
    {AT_DEVICE_NV_DATA_INVALID,                            {(VOS_UINT8*)"562", (VOS_UINT8*)"NV DATA INVALID",                   }},

    {AT_PERSONALIZATION_ERR_BEGIN,                          {VOS_NULL_PTR     , VOS_NULL_PTR                                     } },
    {AT_PERSONALIZATION_IDENTIFY_FAIL,                      {(VOS_UINT8*)"301", (VOS_UINT8*)"Identify failure",                  } },
    {AT_PERSONALIZATION_SIGNATURE_FAIL,                     {(VOS_UINT8*)"302", (VOS_UINT8*)"Signature verification failed",     } },
    {AT_PERSONALIZATION_DK_INCORRECT,                       {(VOS_UINT8*)"303", (VOS_UINT8*)"Debug port password incorrect",     } },
    {AT_PERSONALIZATION_PH_PHYNUM_LEN_ERROR,                {(VOS_UINT8*)"304", (VOS_UINT8*)"Phone physical number length error",} },
    {AT_PERSONALIZATION_PH_PHYNUM_VALUE_ERROR,              {(VOS_UINT8*)"305", (VOS_UINT8*)"Phone physical number value error", } },
    {AT_PERSONALIZATION_PH_PHYNUM_TYPE_ERROR,               {(VOS_UINT8*)"306", (VOS_UINT8*)"Phone physical number type error",  } },
    {AT_PERSONALIZATION_RSA_ENCRYPT_FAIL,                   {(VOS_UINT8*)"307", (VOS_UINT8*)"RSA encryption failed",             } },
    {AT_PERSONALIZATION_RSA_DECRYPT_FAIL,                   {(VOS_UINT8*)"308", (VOS_UINT8*)"RSA decryption failed",             } },
    {AT_PERSONALIZATION_GET_RAND_NUMBER_FAIL,               {(VOS_UINT8*)"309", (VOS_UINT8*)"Generate random number failed",     } },
    {AT_PERSONALIZATION_WRITE_HUK_FAIL,                     {(VOS_UINT8*)"310", (VOS_UINT8*)"Write HUK failed",                  } },
    {AT_PERSONALIZATION_FLASH_ERROR,                        {(VOS_UINT8*)"311", (VOS_UINT8*)"Flash error",                       } },
    {AT_PERSONALIZATION_OTHER_ERROR,                        {(VOS_UINT8*)"312", (VOS_UINT8*)"Other error",                       } },
    {AT_PERSONALIZATION_ERR_END,                            {VOS_NULL_PTR     , VOS_NULL_PTR                                     } },

    {AT_DEVICE_ERROR_END,                                  {VOS_NULL_PTR,       VOS_NULL_PTR                                     } },

    {AT_CMS_ERROR_ENUM_BEGAIN,                             {TAF_NULL_PTR,       TAF_NULL_PTR                                     } },
    {AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER,                            { (TAF_UINT8*)"1  ", (TAF_UINT8*)"Unassigned (unallocated) number"                             } },
    {AT_CMS_OPERATOR_DETERMINED_BARRING,                              { (TAF_UINT8*)"8  ", (TAF_UINT8*)"Operator determined barring"                                 } },
    {AT_CMS_CALL_BARRED,                                              { (TAF_UINT8*)"10 ", (TAF_UINT8*)"Call barred"                                                 } },
    {AT_CMS_SHORT_MESSAGE_TRANSFER_REJECTED,                          { (TAF_UINT8*)"21 ", (TAF_UINT8*)"Short message transfer rejected"                             } },
    {AT_CMS_DESTINATION_OUT_OF_SERVICE,                               { (TAF_UINT8*)"27 ", (TAF_UINT8*)"Destination out of service"                                  } },
    {AT_CMS_UNIDENTIFIED_SUBSCRIBER,                                  { (TAF_UINT8*)"28 ", (TAF_UINT8*)"Unidentified subscriber"                                     } },
    {AT_CMS_FACILITY_REJECTED,                                        { (TAF_UINT8*)"29 ", (TAF_UINT8*)"Facility rejected"                                           } },
    {AT_CMS_UNKNOWN_SUBSCRIBER,                                       { (TAF_UINT8*)"30 ", (TAF_UINT8*)"Unknown subscriber"                                          } },
    {AT_CMS_NETWORK_OUT_OF_ORDER,                                     { (TAF_UINT8*)"38 ", (TAF_UINT8*)"Network out of order"                                        } },
    {AT_CMS_TEMPORARY_FAILURE,                                        { (TAF_UINT8*)"41 ", (TAF_UINT8*)"Temporary failure"                                           } },
    {AT_CMS_CONGESTION,                                               { (TAF_UINT8*)"42 ", (TAF_UINT8*)"Congestion"                                                  } },
    {AT_CMS_RESOURCES_UNAVAILABLE_UNSPECIFIED,                        { (TAF_UINT8*)"47 ", (TAF_UINT8*)"Resources unavailable, unspecified"                          } },
    {AT_CMS_REQUESTED_FACILITY_NOT_SUBSCRIBED,                        { (TAF_UINT8*)"50 ", (TAF_UINT8*)"Requested facility not subscribed"                           } },
    {AT_CMS_REQUESTED_FACILITY_NOT_IMPLEMENTED,                       { (TAF_UINT8*)"69 ", (TAF_UINT8*)"Requested facility not implemented"                          } },
    {AT_CMS_INVALID_SHORT_MESSAGE_TRANSFER_REFERENCE_VALUE,           { (TAF_UINT8*)"81 ", (TAF_UINT8*)"Invalid short message transfer reference value"              } },
    {AT_CMS_INVALID_MESSAGE_UNSPECIFIED,                              { (TAF_UINT8*)"95 ", (TAF_UINT8*)"Invalid message, unspecified"                                } },
    {AT_CMS_INVALID_MANDATORY_INFORMATION,                            { (TAF_UINT8*)"96 ", (TAF_UINT8*)"Invalid mandatory information"                               } },
    {AT_CMS_MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED,             { (TAF_UINT8*)"97 ", (TAF_UINT8*)"Message type non existent or not implemented"                } },
    {AT_CMS_MESSAGE_NOT_COMPATIBLE_WITH_SHORT_MESSAGE_PROTOCOL_STATE, { (TAF_UINT8*)"98 ", (TAF_UINT8*)"Message not compatible with short message protocol state"    } },
    {AT_CMS_INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED,      { (TAF_UINT8*)"99 ", (TAF_UINT8*)"Information element non existent or not implemented"         } },
    {AT_CMS_PROTOCOL_ERROR_UNSPECIFIED,                               { (TAF_UINT8*)"111", (TAF_UINT8*)"Protocol error, unspecified"                                 } },
    {AT_CMS_INTERWORKING_UNSPECIFIED,                                 { (TAF_UINT8*)"127", (TAF_UINT8*)"Interworking, unspecified"                                   } },

    {AT_CMS_TELEMATIC_INTERWORKING_NOT_SUPPORTED,                     { (TAF_UINT8*)"128", (TAF_UINT8*)"Telematic interworking not supported"                        } },
    {AT_CMS_SHORT_MESSAGE_TYPE_0_NOT_SUPPORTED,                       { (TAF_UINT8*)"129", (TAF_UINT8*)"Short message Type 0 not supported"                          } },
    {AT_CMS_CANNOT_REPLACE_SHORT_MESSAGE,                             { (TAF_UINT8*)"130", (TAF_UINT8*)"Cannot replace short message"                                } },
    {AT_CMS_UNSPECIFIED_TPPID_ERROR,                                  { (TAF_UINT8*)"143", (TAF_UINT8*)"Unspecified TPPID error"                                     } },
    {AT_CMS_DATA_CODING_SCHEME_ALPHABET_NOT_SUPPORTED,                { (TAF_UINT8*)"144", (TAF_UINT8*)"Data coding scheme (alphabet) not supported"                 } },
    {AT_CMS_MESSAGE_CLASS_NOT_SUPPORTED,                              { (TAF_UINT8*)"145", (TAF_UINT8*)"Message class not supported"                                 } },
    {AT_CMS_UNSPECIFIED_TPDCS_ERROR,                                  { (TAF_UINT8*)"159", (TAF_UINT8*)"Unspecified TPDCS error"                                     } },
    {AT_CMS_COMMAND_CANNOT_BE_ACTIONED,                               { (TAF_UINT8*)"160", (TAF_UINT8*)"Command cannot be actioned"                                  } },
    {AT_CMS_COMMAND_UNSUPPORTED,                                      { (TAF_UINT8*)"161", (TAF_UINT8*)"Command unsupported"                                         } },
    {AT_CMS_UNSPECIFIED_TPCOMMAND_ERROR,                              { (TAF_UINT8*)"175", (TAF_UINT8*)"Unspecified TPCommand erro"                                  } },
    {AT_CMS_TPDU_NOT_SUPPORTED,                                       { (TAF_UINT8*)"176", (TAF_UINT8*)"TPDU not supported"                                          } },
    {AT_CMS_SC_BUSY,                                                  { (TAF_UINT8*)"192", (TAF_UINT8*)"SC busy"                                                     } },
    {AT_CMS_NO_SC_SUBSCRIPTION,                                       { (TAF_UINT8*)"193", (TAF_UINT8*)"No SC subscription"                                          } },
    {AT_CMS_SC_SYSTEM_FAILURE,                                        { (TAF_UINT8*)"194", (TAF_UINT8*)"SC system failure"                                           } },
    {AT_CMS_INVALID_SME_ADDRESS,                                      { (TAF_UINT8*)"195", (TAF_UINT8*)"Invalid SME address"                                         } },
    {AT_CMS_DESTINATION_SME_BARRED,                                   { (TAF_UINT8*)"196", (TAF_UINT8*)"Destination SME barred"                                      } },
    {AT_CMS_SM_REJECTEDDUPLICATE_SM,                                  { (TAF_UINT8*)"197", (TAF_UINT8*)"SM RejectedDuplicate SM"                                     } },
    {AT_CMS_TPVPF_NOT_SUPPORTED,                                      { (TAF_UINT8*)"198", (TAF_UINT8*)"TPVPF not supported"                                         } },
    {AT_CMS_TPVP_NOT_SUPPORTED,                                       { (TAF_UINT8*)"199", (TAF_UINT8*)"TPVP not supported"                                          } },
    {AT_CMS_SIM_SMS_STORAGE_FULL,                                     { (TAF_UINT8*)"208", (TAF_UINT8*)"(U)SIM SMS storage full"                                     } },
    {AT_CMS_NO_SMS_STORAGE_CAPABILITY_IN_SIM,                         { (TAF_UINT8*)"209", (TAF_UINT8*)"No SMS storage capability in (U)SIM"                         } },
    {AT_CMS_ERROR_IN_MS,                                              { (TAF_UINT8*)"210", (TAF_UINT8*)"Error in MS"                                                 } },
    {AT_CMS_MEMORY_CAPACITY_EXCEEDED,                                 { (TAF_UINT8*)"211", (TAF_UINT8*)"Memory Capacity Exceeded"                                    } },
    {AT_CMS_SIM_APPLICATION_TOOLKIT_BUSY,                             { (TAF_UINT8*)"212", (TAF_UINT8*)"(U)SIM Application Toolkit Busy"                             } },
    {AT_CMS_SIM_DATA_DOWNLOAD_ERROR,                                  { (TAF_UINT8*)"213", (TAF_UINT8*)"(U)SIM data download error"                                  } },
    {AT_CMS_UNSPECIFIED_ERROR_CAUSE,                                  { (TAF_UINT8*)"255", (TAF_UINT8*)"Unspecified error cause"                                     } },

    {AT_CMS_ME_FAILURE,                                               { (TAF_UINT8*)"300", (TAF_UINT8*)"ME failure"                                                  } },
    {AT_CMS_SMS_SERVICE_OF_ME_RESERVED,                               { (TAF_UINT8*)"301", (TAF_UINT8*)"SMS service of ME reserved"                                  } },
    {AT_CMS_OPERATION_NOT_ALLOWED,                                    { (TAF_UINT8*)"302", (TAF_UINT8*)"operation not allowed"                                       } },
    {AT_CMS_OPERATION_NOT_SUPPORTED,                                  { (TAF_UINT8*)"303", (TAF_UINT8*)"operation not supported"                                     } },
    {AT_CMS_INVALID_PDU_MODE_PARAMETER,                               { (TAF_UINT8*)"304", (TAF_UINT8*)"304"                                                         } },/*"invalid PDU mode parameter"*/
    {AT_CMS_INVALID_TEXT_MODE_PARAMETER,                              { (TAF_UINT8*)"305", (TAF_UINT8*)"305"                                                         } },/*"invalid text mode parameter"*/
    {AT_CMS_U_SIM_NOT_INSERTED,                                       { (TAF_UINT8*)"310", (TAF_UINT8*)"(U)SIM not inserted"                                         } },
    {AT_CMS_U_SIM_PIN_REQUIRED,                                       { (TAF_UINT8*)"311", (TAF_UINT8*)"(U)SIM PIN required"                                         } },
    {AT_CMS_PH_U_SIM_PIN_REQUIRED,                                    { (TAF_UINT8*)"312", (TAF_UINT8*)"PH-(U)SIM PIN required"                                      } },
    {AT_CMS_U_SIM_FAILURE,                                            { (TAF_UINT8*)"313", (TAF_UINT8*)"313"                                                         } },
    {AT_CMS_U_SIM_BUSY,                                               { (TAF_UINT8*)"314", (TAF_UINT8*)"(U)SIM busy"                                                 } },
    {AT_CMS_U_SIM_WRONG,                                              { (TAF_UINT8*)"315", (TAF_UINT8*)"(U)SIM wrong"                                                } },
    {AT_CMS_U_SIM_PUK_REQUIRED,                                       { (TAF_UINT8*)"316", (TAF_UINT8*)"(U)SIM PUK required"                                         } },
    {AT_CMS_U_SIM_PIN2_REQUIRED,                                      { (TAF_UINT8*)"317", (TAF_UINT8*)"(U)SIM PIN2 required"                                        } },
    {AT_CMS_U_SIM_PUK2_REQUIRED,                                      { (TAF_UINT8*)"318", (TAF_UINT8*)"(U)SIM PUK2 required"                                        } },
    {AT_CMS_MEMORY_FAILURE,                                           { (TAF_UINT8*)"320", (TAF_UINT8*)"memory failure"                                              } },
    {AT_CMS_INVALID_MEMORY_INDEX,                                     { (TAF_UINT8*)"321", (TAF_UINT8*)"invalid memory index"                                        } },
    {AT_CMS_MEMORY_FULL,                                              { (TAF_UINT8*)"322", (TAF_UINT8*)"memory full"                                                 } },
    {AT_CMS_SMSC_ADDRESS_UNKNOWN,                                     { (TAF_UINT8*)"330", (TAF_UINT8*)"330"                                                         } },/*"SMSC address unknown"*/
    {AT_CMS_NO_NETWORK_SERVICE,                                       { (TAF_UINT8*)"331", (TAF_UINT8*)"no network service"                                          } },
    {AT_CMS_NETWORK_TIMEOUT,                                          { (TAF_UINT8*)"332", (TAF_UINT8*)"network timeout"                                             } },
    {AT_CMS_NO_CNMA_ACKNOWLEDGEMENT_EXPECTED,                         { (TAF_UINT8*)"340", (TAF_UINT8*)"no +CNMA acknowledgement expected"                           } },
    {AT_CMS_FDN_DEST_ADDR_FAILED,                                     { (TAF_UINT8*)"341", (TAF_UINT8*)"FDN Failed"                                                  } },
    {AT_CMS_FDN_SERVICE_CENTER_ADDR_FAILED,                           { (TAF_UINT8*)"342", (TAF_UINT8*)"Service Centre Address FDN failed"                           } },
    {AT_CMS_MO_SMS_CONTROL_FAILED,                                    { (TAF_UINT8*)"343", (TAF_UINT8*)"MO SMS Control Failed"                                       } },
    {AT_CMS_UNKNOWN_ERROR,                                            { (TAF_UINT8*)"500", (TAF_UINT8*)"500"                                               } },/*"unknown error"*/

    {AT_CMS_ERROR_ENUM_END,                                           {TAF_NULL_PTR   ,TAF_NULL_PTR                          }  },
};

/*速率气泡显示的速率表数组,由于是遵照CONNECT <Rate>的格式，故预留一个空格*/
const TAF_CHAR   *g_PppDialRateDisplay[] =
{
    " 9600",
    " 85600",
    " 107000",
    " 236800",
    " 296000",
    " 384000",
    " 3600000",
    " 7200000",
    " 10200000",
    " 14400000",
    " 1800000",
    " 21600000",
    " 28800000",
    " 43200000",
    " 57600000",
    " 86400000"
};

/*速率气泡显示的速率表数组,NV定制值*/
const VOS_CHAR   *g_ucDialRateDisplayNv[] =
{
    " 53600",
    " 236800",
    " 384000",
    " 1800000",
    " 3600000",
    " 7200000",
};

#if (FEATURE_ON == FEATURE_LTE)
/*速率气泡显示的速率表数组,NV定制值*/
const VOS_CHAR   *g_ucLTEDlRateDisplay[] =
{
    " 10000000",
    " 50000000",
    " 100000000",
    " 150000000",
    " 300000000",
};
#endif



/*****************************************************************************
   3 函数、变量声明
*****************************************************************************/
/* Modified by L60609 for AT Project，2011-10-20,  Begin*/
#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_INT32 Sock_Send(VOS_UINT8 ucPortNo, VOS_UINT8* pucData, VOS_UINT16 uslength);
#endif
/* Modified by L60609 for AT Project，2011-10-20,  Begin*/


/*****************************************************************************
   4 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : At_SendData
 Description    :
 Input          : ---
 Output         : ---
 Return Value   : AT_SUCCESS --- 成功
                  AT_FAILURE --- 失败
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期 : 2007-03-27
    作    者 : h59254
    修改内容 : 问题单号:A32D09820(PC-Lint修改)
  3.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project: 直接调用DRV/DMS向端口发送数据
  4.日    期   : 2011年10月19日
    作    者   : S62952
    修改内容   : AT Project: 修改modem口方式接口
  5.日    期   : 2012年02月14日
    作    者   : l00171473
    修改内容   : DTS2012021405602,删掉对AT_APP_SOCK_PORT_NO端口的AT上报
  6.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:新增HSIC AT通道的发送数据逻辑
  7.日    期   : 2012年8月6日
    作    者   : l60609
    修改内容   : MUX：增加mux通道处理
  8.日    期   : 2012年11月29日
    作    者   : l00227485
    修改内容   : DSDA PHASE1, 修改VCOM接口
  9.日    期   : 2013年03月13日
    作    者   : z00214637
    修改内容   : BodySAR项目
 10.日    期   : 2013年05月27日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
 11.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
TAF_UINT32 At_SendData(TAF_UINT8 ucIndex,TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen)
{

    /* Added by L60609 for MUX，2012-08-06,  Begin */
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;
    /* Added by L60609 for MUX，2012-08-06,  End */

    /* Added by L60609 for MUX，2012-08-06,  Begin */
    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);
    /* Added by L60609 for MUX，2012-08-06,  End */

    /* 检查 输入参数，如果失败，返回错误； */
    /* 根据当前用户业务类型，把数据发送到指定的接口 */
    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        return AT_FAILURE;
    }
    if ( (AT_CLIENT_USED != gastAtClientTab[ucIndex].ucUsed)
      || (AT_DATA_BUTT_MODE == gastAtClientTab[ucIndex].DataMode))
    {
        return AT_FAILURE;
    }
    if (ucType != gastAtClientTab[ucIndex].DataMode)
    {
        return AT_FAILURE;
    }


    if (AT_DATA_STOP_STATE == gastAtClientTab[ucIndex].DataState)
    {
        return AT_FAILURE;
    }

    if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
    {
        return AT_FAILURE;
    }
    else
    {
        if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /*向USB COM口发送数据*/
            /* Modified by L60609 for AT Project，2011-10-15,  Begin*/
            #if (VOS_WIN32 == VOS_OS_VER)
            #ifndef __PS_WIN32_RECUR__
            Sock_Send(AT_USB_COM_PORT_NO, pData, usLen);
            #endif
            #else
            DMS_COM_SEND(AT_USB_COM_PORT_NO, pData, usLen);
            AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
            #endif
            /* Modified by L60609 for AT Project，2011-10-15,  End*/
            return AT_SUCCESS;
        }
        /* 向VCOM口发送数据 */
        else if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by L60609 for AT Project，2011-10-18,  Begin*/
            /* Modified by l00227485 for DSDA Phase I，2012-11-28, Begin */
            APP_VCOM_Send(gastAtClientTab[ucIndex].ucPortNo, pData, usLen);
            /* Modified by l00227485 for DSDA Phase I，2012-11-28, End */
            return AT_SUCCESS;
            /* Modified by L60609 for AT Project，2011-10-18,  End*/
        }
        else if (AT_SOCK_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by L60609 for AT Project，2011-10-18,  Begin*/
            if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
            {
                CPM_ComSend(CPM_AT_COMM, pData, VOS_NULL_PTR, usLen);
                return AT_SUCCESS;
            }
            /* Modified by L60609 for AT Project，2011-10-18,  End*/
         }
        else if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
        {

            DMS_COM_SEND(AT_CTR_PORT_NO, pData, usLen );
            AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
            return AT_SUCCESS;
        }
        else if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
        {
            DMS_COM_SEND(AT_PCUI2_PORT_NO, pData, usLen );
            AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
            return AT_SUCCESS;
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        else if (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by S62952 for AT Project，2011-10-18,  Begin*/
            return AT_SendDataToModem(ucIndex, pData, usLen);
            /* Modified by S62952 for AT Project，2011-10-18,  END*/
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
        else if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* NDIS AT口目前实现中暂无数据发送,若从该口发送数据,则3直接返回AT_FAILURE */
            return AT_FAILURE;
        }
        /* Modified by L60609 for MUX，2012-08-13,  Begin */
        else if (VOS_TRUE == ulHsicUserFlg)
        /* Modified by L60609 for MUX，2012-08-13,  End */
        {
/* Added by j00174725 for V3R3 Cut Out Memory，2013-11-07,  Begin */
#if (FEATURE_ON == FEATURE_AT_HSIC)
            return AT_SendDataToHsic(ucIndex, pData, usLen);
#endif
/* Added by j00174725 for V3R3 Cut Out Memory，2013-11-07,  End */
        }
        /* Added by L60609 for MUX，2012-08-06,  Begin */
        else if (VOS_TRUE == ulMuxUserFlg)
        {
            return AT_SendMuxResultData(ucIndex, pData, usLen);
        }
        /* Added by L60609 for MUX，2012-08-06,  End */
        else
        {
            return AT_FAILURE;
        }
        return AT_FAILURE;
    }
}

#ifdef DMT
/*****************************************************************************
 函 数 名  : At_SndResult_DMTStub
 功能描述  : 将at回复消息发给dmt pid
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID At_SndResult_DMTStub(
    VOS_UINT8                          ucIndex,
    VOS_UINT8                         *pData,
    VOS_UINT16                         usLen
)
{
    AT_MSG_STRU                        *pMsg = TAF_NULL_PTR;
    TAF_UINT32                          ulTmpAddr;
    VOS_UINT32                          ulLength;

    if(VOS_NULL_PTR == pData)
    {
        AT_WARN_LOG("At_SndResult_DMTStub :pData is null ptr!");
        return;
    }

    if(0 == usLen)
    {
        AT_WARN_LOG("At_SndResult_DMTStub ulLength = 0");
        return;
    }

    if(AT_COM_BUFF_LEN < usLen)
    {
        AT_WARN_LOG("At_SndResult_DMTStub ulLength > AT_COM_BUFF_LEN");
        return;
    }

    /* 增加自定义的ITEM，共4个字节 */
    AT_GetAtMsgStruMsgLength(usLen, &ulLength);
    pMsg = (AT_MSG_STRU*)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);
    if ( pMsg == TAF_NULL_PTR )
    {
        AT_ERR_LOG("At_SndResult_DMTStub:ERROR:Alloc Msg");
        return;
    }

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid       = WUEPS_PID_AT;
    pMsg->ulReceiverPid     = DMT_PID_STUB;
    pMsg->ucType            = 0x1;                                                        /*AT_CMD_RSP*/
    pMsg->ucIndex           = ucIndex;
    pMsg->usLen             = usLen;

    pMsg->enMsgId           = AT_GetResultMsgID(ucIndex);

    AT_GetUserTypeFromIndex(ucIndex, &pMsg->ucUserType);
    PS_MEM_SET(pMsg->aucReserved, 0x00, sizeof(pMsg->aucReserved));

    /* 填写新消息内容 */
    ulTmpAddr = (TAF_UINT32)(pMsg->aucValue);
    PS_MEM_CPY((TAF_VOID*)ulTmpAddr, pData, usLen);  /* 内容 */

    /*发送消息到AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_AT, pMsg ) )
    {
        AT_ERR_LOG("At_SndResult_DMTStub:ERROR:VOS_SendMsg");
        return;
    }

    return;

}



#endif

#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 Prototype      : At_SndResult_Stub
 Description    : 将AT命令回复发给AT_STUB PID中
 Input          : pData   --- 数据
                  usLen   --- 长度
 Output         : ---
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-11-11
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_VOID At_SndResult_Stub(TAF_UINT8 ucIndex, TAF_UINT8* pData, TAF_UINT16 usLen)
{
    AT_MSG_STRU                        *pMsg = TAF_NULL_PTR;
    TAF_UINT32                          ulTmpAddr;
    VOS_UINT32                          ulLength;

    if(VOS_NULL_PTR == pData)
    {
        AT_WARN_LOG("At_SndResult_Stub :pData is null ptr!");
        return;
    }

    if(0 == usLen)
    {
        AT_WARN_LOG("At_SndResult_Stub ulLength = 0");
        return;
    }

    if(AT_COM_BUFF_LEN < usLen)
    {
        AT_WARN_LOG("At_SndResult_Stub ulLength > AT_COM_BUFF_LEN");
        return;
    }

    /* 增加自定义的ITEM，共4个字节 */
    AT_GetAtMsgStruMsgLength(usLen, &ulLength);
    pMsg = (AT_MSG_STRU*)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);
    if ( pMsg == TAF_NULL_PTR )
    {
        AT_ERR_LOG("At_SndResult_Stub:ERROR:Alloc Msg");
        return;
    }

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid       = WUEPS_PID_AT;
    pMsg->ulReceiverPid     = PID_AT_STUB;
    pMsg->ucType            = 0x1;                                                        /*AT_CMD_RSP*/
    pMsg->ucIndex           = ucIndex;
    pMsg->usLen             = usLen;

    pMsg->enMsgId           = AT_GetResultMsgID(ucIndex);

    AT_GetUserTypeFromIndex(ucIndex, &pMsg->ucUserType);
    PS_MEM_SET(pMsg->aucReserved, 0x00, sizeof(pMsg->aucReserved));

    /* 填写新消息内容 */
    ulTmpAddr = (TAF_UINT32)(pMsg->aucValue);
    PS_MEM_CPY((TAF_VOID*)ulTmpAddr, pData, usLen);  /* 内容 */

    /*发送消息到AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_AT, pMsg ) )
    {
        AT_ERR_LOG("At_SndResult_Stub:ERROR:VOS_SendMsg");
        return;
    }

    return;

}

#endif

/*****************************************************************************
 函 数 名  : AT_DisplayResultData
 功能描述  : 将Taf返回的AT命令数据分发给相应的端口
 输入参数  : TAF_UINT16  usLen 数据长度
             TAF_UINT8   ucIndex 用户索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月10日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2011年02月24日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011022404828，MODEM口下发AT命令，返回结果不完整

  3.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project: 直接调用DRV_COM_SEND向端口发送数据
  4.日    期   : 2011年10月19日
    作    者   : S62952
    修改内容   : AT Project: 修改modem口方式接口
  5.日    期   : 2011年12月7日
    作    者   : 李军 l00171473
    修改内容   : DTS2011120801675，UART通道校准修改
  6.日    期   : 2012年02月14日
    作    者   : l00171473
    修改内容   : DTS2012021405602,删掉对AT_APP_SOCK_PORT_NO端口的AT上报
  7.日    期   : 2012年02月24日
    作    者   : w00181244
    修改内容   : DTS2012021305344,删掉对PCUI/control/FEATURE_NDIS端口的消息打印
  8.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:新增HSIC AT通道发送AT回复的处理逻辑
  9.日    期   : 2012年8月6日
    作    者   : l60609
    修改内容   : MUX：增加mux通道处理
 10.日    期   : 2012年11月29日
    作    者   : l00227485
    修改内容   : DSDA PHASE1, 修改VCOM接口
 11.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
 12.日    期   : 2013年03月13日
    作    者   : z00214637
    修改内容   : BodySAR项目
 13.日    期   : 2013年05月27日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
 14.日    期   : 2013年9月25日
    作    者   : j00174725
    修改内容   : UART-MODEM: 增加HSUART端口处理
*****************************************************************************/
VOS_VOID  AT_DisplayResultData (
    VOS_UINT8                           ucIndex,
    VOS_UINT16                          usLen
)
{

    /* Added by L60609 for MUX，2012-08-06,  Begin */
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;
    /* Added by L60609 for MUX，2012-08-06,  End */

    /* Added by L60609 for MUX，2012-08-06,  Begin */
    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);
    /* Added by L60609 for MUX，2012-08-06,  End */

    /*如果是数传状态，直接返回*/
    if (AT_DATA_START_STATE == gastAtClientTab[ucIndex].DataState)
    {
        AT_LOG1("At_SendResultData DataState:",gastAtClientTab[ucIndex].DataState);
        return;
    }

    if ((AT_DATA_STOP_STATE == gastAtClientTab[ucIndex].DataState)
        && (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode))
    {
        gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;
    }

    /*选择PCUI口*/
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        /*向USB COM口发送数据*/
        #if (VOS_WIN32 == VOS_OS_VER)
        #ifndef __PS_WIN32_RECUR__
        Sock_Send(AT_USB_COM_PORT_NO, gstAtSendDataBuffer, usLen);
        #endif
        #else
        DMS_COM_SEND(AT_USB_COM_PORT_NO, gstAtSendDataBuffer, usLen);
        #endif
    }

    /*选择control口*/
    else if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {

        DMS_COM_SEND(AT_CTR_PORT_NO, gstAtSendDataBuffer, usLen);
    }
    else if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        DMS_COM_SEND(AT_PCUI2_PORT_NO, gstAtSendDataBuffer, usLen);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /*选择MODEM口*/
    else if (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
    {
        AT_SendDataToModem(ucIndex, gstAtSendDataBuffer, usLen);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    else if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        /* Modified by l00227485 for DSDA Phase I，2012-11-28, Begin */
        APP_VCOM_Send(gastAtClientTab[ucIndex].ucPortNo, gstAtSendDataBuffer, usLen);
        /* Modified by l00227485 for DSDA Phase I，2012-11-28, End */
    }
    else if (AT_SOCK_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
        {
            CPM_ComSend(CPM_AT_COMM, gstAtSendDataBuffer, VOS_NULL_PTR, usLen);
        }
    }
    else if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
    {
        DMS_COM_SEND(AT_NDIS_PORT_NO, gstAtSendDataBuffer, usLen);
    }
    else if(AT_UART_USER == gastAtClientTab[ucIndex].UserType)
    {
        AT_UART_SendDlData(ucIndex, gstAtSendDataBuffer, usLen);
    }
#if (FEATURE_ON == FEATURE_AT_HSUART)
    else if(AT_HSUART_USER == gastAtClientTab[ucIndex].UserType)
    {
        AT_HSUART_SendDlData(ucIndex, gstAtSendDataBuffer, usLen);
    }
#endif
    /* Modified by L60609 for MUX，2012-08-13,  Begin */
    else if(VOS_TRUE == ulHsicUserFlg)
    /* Modified by L60609 for MUX，2012-08-13,  End */
    {
        /* Added by j00174725 for V3R3 Cut Out Memory，2013-11-07,  Begin */
#if (FEATURE_ON == FEATURE_AT_HSIC)
        AT_SendDataToHsic(ucIndex, gstAtSendDataBuffer, usLen);
        AT_MNTN_TraceCmdResult(ucIndex, gstAtSendDataBuffer, usLen);
#endif
        /* Added by j00174725 for V3R3 Cut Out Memory，2013-11-07,  End */
    }
    /* Added by L60609 for MUX，2012-08-06,  Begin */
    else if (VOS_TRUE == ulMuxUserFlg)
    {
        AT_SendMuxResultData(ucIndex, gstAtSendDataBuffer, usLen);
    }
    /* Added by L60609 for MUX，2012-08-06,  End */
    else
    {
        ;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_DisplaySelResultData
 功能描述  : 将Taf返回的AT命令数据分发给相应的端口
 输入参数  : TAF_UINT16  usLen 数据长度
             TAF_UINT8   ucIndex 索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月10日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2011年02月24日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011022404828，MODEM口下发AT命令，返回结果不完整

  3.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project: 直接调用DRV_COM_SEND向AT_USB_COM_PORT_NO发送数据
  4.日    期   : 2011年10月19日
    作    者   : S62952
    修改内容   : AT Project: 修改modem口方式接口
  5.日    期   : 2012年02月14日
    作    者   : l00171473
    修改内容   : DTS2012021405602,删掉对AT_APP_SOCK_PORT_NO端口的AT上报
  6.日    期   : 2012年02月24日
    作    者   : w00181244
    修改内容   : DTS2012021305344,删掉对PCUI/control/FEATURE_NDIS端口的消息打印,修改对ctrl口的上报
  7.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:新增HSIC AT通道处理AT主动上报的逻辑
  8.日    期   : 2012年8月6日
    作    者   : l60609
    修改内容   : MUX：增加mux通道处理
  9.日    期   : 2012年11月29日
    作    者   : l00227485
    修改内容   : DSDA PHASE1, 修改VCOM接口
 10.日    期  : 2013年03月13日
    作    者  : z00214637
    修改内容  : BodySAR项目
 11.日    期   : 2013年05月27日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
 12.日    期   : 2013年9月25日
    作    者   : j00174725
    修改内容   : UART-MODEM: 增加HSUART端口处理
 13.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID AT_DisplaySelResultData(
    VOS_UINT16                          usLen,
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucLoop;
    /* Added by L60609 for MUX，2012-08-06,  Begin */
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;
    /* Added by L60609 for MUX，2012-08-06,  End */

    /* Added by L60609 for MUX，2012-08-06,  Begin */
    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);
    /* Added by L60609 for MUX，2012-08-06,  End */


    if ( (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
      || (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode) )
    {
        if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* 选择PCUI口 */
            if (0 == gucAtPortSel)
            {
                #if (VOS_WIN32 == VOS_OS_VER)
                #ifndef __PS_WIN32_RECUR__
                Sock_Send(AT_USB_COM_PORT_NO, gstAtSendDataBuffer, usLen);
                #endif
                #else
                DMS_COM_SEND(AT_USB_COM_PORT_NO, gstAtSendDataBuffer, usLen);
                #endif
            }
        }
        else if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
        {

             /* 选择control口 */
            if (0 == gucAtPortSel)
            {
                DMS_COM_SEND(AT_CTR_PORT_NO, gstAtSendDataBuffer, usLen);
            }
        }
        else if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
        {
             /* 选择PCUI2口 */
            if (0 == gucAtPortSel)
            {
                DMS_COM_SEND(AT_PCUI2_PORT_NO, gstAtSendDataBuffer, usLen);
            }
        }
        else if (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* 选择modem口 */
            if (1 == gucAtPortSel)
            {
                /* Modified by S62952 for AT Project，2011-10-18,  Begin*/
                AT_SendDataToModem(ucIndex, gstAtSendDataBuffer, usLen);
                /* Modified by S62952 for AT Project，2011-10-18,  END*/
            }
        }
#if (FEATURE_ON == FEATURE_AT_HSUART)
        else if (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType)
        {
            AT_HSUART_SendDlData(ucIndex, gstAtSendDataBuffer,usLen);
        }
#endif
        else if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by L60609 for AT Project，2011-10-18,  Begin*/
            /* Modified by l00227485 for DSDA Phase I，2012-11-28, Begin */
            APP_VCOM_Send(gastAtClientTab[ucIndex].ucPortNo, gstAtSendDataBuffer, usLen);
            /* Modified by l00227485 for DSDA Phase I，2012-11-28, End */
            /* Modified by L60609 for AT Project，2011-10-18,  end*/
        }
        else if (AT_SOCK_USER == gastAtClientTab[ucIndex].UserType)
        {
            if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
            {
            /* Modified by L60609 for AT Project，2011-10-18,  Begin*/
                CPM_ComSend(CPM_AT_COMM, gstAtSendDataBuffer, VOS_NULL_PTR, usLen);
            /* Modified by L60609 for AT Project，2011-10-18,  End*/
            }
        }
        else if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
        {
            #ifndef __PS_WIN32_RECUR__
            DMS_COM_SEND(AT_NDIS_PORT_NO,gstAtSendDataBuffer, (VOS_UINT32)usLen);
            #endif
        }
        /* Modified by L60609 for MUX，2012-08-13,  Begin */
        else if (VOS_TRUE == ulHsicUserFlg)
        /* Modified by L60609 for MUX，2012-08-13,  End */
        {
            /* 判断是否允许从该HSIC AT端口主动上报AT命令 */
            for (ucLoop = 0; ucLoop < AT_HSIC_AT_CHANNEL_MAX; ucLoop++)
            {
/* Added by j00174725 for V3R3 Cut Out Memory，2013-11-07,  Begin */
#if (FEATURE_ON == FEATURE_AT_HSIC)
                if ((g_astAtHsicCtx[ucLoop].ucHsicUser == gastAtClientTab[ucIndex].UserType)
                  && (AT_HSIC_REPORT_ON == g_astAtHsicCtx[ucLoop].enRptType))
                {
                    AT_SendDataToHsic(ucIndex, gstAtSendDataBuffer, usLen);
                    break;
                }
#endif
/* Added by j00174725 for V3R3 Cut Out Memory，2013-11-07,  End */
            }
        }
        /* Added by L60609 for MUX，2012-08-06,  Begin */
        else if (VOS_TRUE == ulMuxUserFlg)
        {
            AT_SendMuxSelResultData(ucIndex, gstAtSendDataBuffer, usLen);
        }
        /* Added by L60609 for MUX，2012-08-06,  End */
        else
        {
            ;
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : At_BufferorSendResultData
 功能描述  : 缓存待发送数据到组合AT命令发送缓存
 输入参数  : VOS_UINT8  ucIndex     用户索引
             VOS_UINT8  *pucData    待发送字符串首指针
             VOS_UINT16 usLength    待发送字符串长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月20日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
  3.日    期   : 2014年01月15日
    作    者   : f62575
    修改内容   : DTS2014011301359，+CPOL命令支持超过37个UPLMN
*****************************************************************************/
VOS_VOID At_BufferorSendResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLength
)
{
    VOS_UINT32                          ulBufferLength;
    VOS_UINT8                          *pBuffer;

    if (0 == usLength)
    {
        return;
    }

    ulBufferLength = gstAtCombineSendData[ucIndex].usBufLen + usLength;

    /* 若缓冲区存储空间不够用则将当前已缓存信息输出 */
    if (ulBufferLength > AT_CMD_OUTPUT_MAX_LEN)
    {
        At_SendResultData(ucIndex,
                          gstAtCombineSendData[ucIndex].aucBuffer,
                          gstAtCombineSendData[ucIndex].usBufLen);
        gstAtCombineSendData[ucIndex].usBufLen = 0;
    }

    /* 缓存待输出的新数据 */
    pBuffer = gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen;
    PS_MEM_CPY(pBuffer, pucData, usLength);
    gstAtCombineSendData[ucIndex].usBufLen += usLength;

    return;
}

/*****************************************************************************
 函 数 名  : AT_SendBroadCastResultData
 功能描述  : 发送广播数据给上层模块
 输入参数  : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID AT_SendBroadCastResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                           ucCount;
    MODEM_ID_ENUM_UINT16                enBroadCastModemId;
    MODEM_ID_ENUM_UINT16                enCurModemId;
    VOS_UINT32                          ulRslt;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    enCurModemId = MODEM_ID_0;

    switch (ucIndex)
    {
        case AT_BROADCAST_CLIENT_INDEX_MODEM_0:
            enBroadCastModemId = MODEM_ID_0;
            break;
        case AT_BROADCAST_CLIENT_INDEX_MODEM_1:
            enBroadCastModemId = MODEM_ID_1;
            break;
        case AT_BROADCAST_CLIENT_INDEX_MODEM_2:
            enBroadCastModemId = MODEM_ID_2;
            break;
        default:
            enBroadCastModemId = MODEM_ID_0;
            break;
    }

    for (ucCount = 0; ucCount < AT_MAX_CLIENT_NUM; ucCount++ )
    {
        pstAtClientCtx = AT_GetClientCtxAddr(ucCount);

        /* 该端口未使用 */
        if (AT_CLIENT_NULL == gastAtClientTab[ucCount].ucUsed)
        {
            continue;
        }

        /* 该端口不允许上报 */
        if (VOS_FALSE == pstAtClientCtx->stClientConfiguration.ucReportFlg)
        {
            continue;
        }

        ulRslt = AT_GetModemIdFromClient(ucCount, &enCurModemId);

        if (VOS_OK != ulRslt)
        {
            continue;
        }

        /* 判断该端口是否属于要广播的Modem */
        if (enBroadCastModemId != enCurModemId)
        {
            continue;
        }

        if (AT_IND_MODE == gastAtClientTab[ucCount].IndMode)
        {
            /*为了保证发送的数据是4字节对齐格式，故做一次拷贝*/
            PS_MEM_CPY(gstAtSendDataBuffer, pData, usLen);
            AT_DisplaySelResultData(usLen, ucCount);
        }
    }

}

/*****************************************************************************
 Prototype      : At_SendResultData
 Description    : 发送Taf反馈AT命令的数据给APP
 Input          : ucIndex --- 用户索引
                  pData   --- 数据
                  usLen   --- 长度
 Output         : ---
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期   : 2007-03-27
    作    者   : h59254
    修改内容   : 问题单号:A32D09820(PC-Lint修改)
  3.日    期   : 2010年3月30日
    作    者   : s62952
    修改内容   : 根据问题单AT2D18046修改
  4.日    期   : 2012年8月23日
    作    者   : z60575
    修改内容   : 合入北京AT代码修改DTS2012081501160
  5.日    期   : 2012年12月08日
    作    者   : f62575
    修改内容   : DTS2012110804140，解决AT模块因组合AT命令处理状态问题导致的概率性无OK问题
  6.日    期   : 2012年12月27日
    作    者   : l60609
    修改内容   : DSDA Phase II

  7.日    期   : 2013年12月28日
    作    者   : j00174725
    修改内容   : HSUART PHASE III

*****************************************************************************/
VOS_VOID At_SendResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    gstAtSendData.usBufLen = 0;

    /* 参数检查 */
    if ((0 == usLen) || (AT_CMD_MAX_LEN <= usLen))
    {
        AT_LOG1("At_SendResultData usLen:",usLen);
        return;
    }

    pData[usLen] = 0;
    AT_INFO_LOG((TAF_CHAR *)pData);
    AT_LOG1("At_SendResultData:",usLen);

#ifdef DMT
    At_SndResult_DMTStub(ucIndex, pData, usLen);
#endif

#ifdef __PS_WIN32_RECUR__
    At_SndResult_Stub(ucIndex, pData, usLen);
    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
#else
        /* 通过ucIndex获取端口类型 */
    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
#endif

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_SendBroadCastResultData(ucIndex, pData, usLen);
        AT_MNTN_TraceRPTPORT();
    }
    else
    {
        if (AT_MAX_CLIENT_NUM <= ucIndex)
        {
            AT_LOG1("At_SendResultData ucIndex:",ucIndex);
            return;
        }

        /* 注意遗留问题: 此处需要增加链路类型判断，数传和命令状态数据不能混在一起 */
        if (AT_CLIENT_NULL == gastAtClientTab[ucIndex].ucUsed)
        {
            AT_LOG1("At_SendResultData ucUsed:",gastAtClientTab[ucIndex].ucUsed);
            AT_ParseCmdOver(ucIndex);
            return;
        }

        /*为了保证发送的数据是4字节对齐格式，故做一次拷贝*/
        PS_MEM_CPY(gstAtSendDataBuffer, pData, usLen);
        AT_DisplayResultData(ucIndex, usLen);

        /* 判断是否需要Flash 短信,若需要，则将短信flash出去 */
        if (VOS_FALSE == AT_IsClientBlock())
        {
            AT_FlushSmsIndication();
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : At_JudgeCombineCmdSubSequentProcess
 Description    : 根据命令的返回结果来判断后续命令的处理
                  1.若后续无命令，则直接返回
                  2.若返回结果为错误，但后续还有命令，则终止后续命令的处理，并做相应的
                    清空操作
                  3.若返回结果为正确，且后续还有命令，则继续执行后续命令
 Input          : ucIndex    --- 索引号
                  ReturnCode --- 返回码
 Output         : TAF_UINT32
 Return Value   : ---
 Calls          : ---
 Called By      : At_FormatResultData

 History        : ---
  1.Date        : 2009-05-30
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32  At_JudgeCombineCmdSubSequentProcess(TAF_UINT8 ucIndex, TAF_UINT32 ReturnCode)
{
    /* 判读是否有未处理完成的命令 */
    if (g_stParseContext[ucIndex].stCombineCmdInfo.usTotalNum == 0)
    {
        /* 该分支有如下两种情况:
            1.无待处理命令，属于主动上报
            2.解析组合AT命令(或仅为独立AT命令)失败
         */
        return AT_COM_CMD_SUB_PROC_FINISH;
    }

    /* 判断是否为最后一个AT命令 */
    if ((g_stParseContext[ucIndex].stCombineCmdInfo.usProcNum + 1) == g_stParseContext[ucIndex].stCombineCmdInfo.usTotalNum)
    {
        return AT_COM_CMD_SUB_PROC_FINISH;
    }

    if (AT_SUCCESS == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_CONTINUE;
    }
    else if (AT_FAILURE == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if ((AT_CME_ERROR_ENUM_BEGAIN < ReturnCode) && (ReturnCode < AT_CME_ERROR_ENUM_END))
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if ((AT_CMS_ERROR_ENUM_BEGAIN < ReturnCode) && (ReturnCode < AT_CMS_ERROR_ENUM_END))
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_CMD_NOT_SUPPORT == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_TOO_MANY_PARA == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_TOO_MANY_PARA <= ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_OK == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_CONTINUE;
    }
    else if (AT_CONNECT == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_RING == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_NO_CARRIER == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_ERROR == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_NO_DIALTONE == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_BUSY == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_NO_ANSWER == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else
    {
        return AT_COM_CMD_SUB_PROC_CONTINUE;
    }

}


/*****************************************************************************
 函 数 名  : AT_GetReturnCodeId
 功能描述  : 从gastAtReturnCodeTab中获取错误码对应的index值
 输入参数  : VOS_UINT32                          ulReturnCode
             VOS_UINT32                         *pulIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月24日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_GetReturnCodeId(
    VOS_UINT32                          ulReturnCode,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i;

    for (i = 0; i < sizeof(gastAtReturnCodeTab)/sizeof(gastAtReturnCodeTab[0]); i++)
    {
        if (ulReturnCode == gastAtReturnCodeTab[i].ucIndex)
        {
            *pulIndex = i;
            return VOS_OK;
        }
    }

    AT_ERR_LOG("AT_GetResultDataId, ReturnCode is out of gastAtReturnCodeTab!");
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : AT_FormatAtCmdNotSupportResult
 功能描述  : AT_CMD_NOT_SUPPORT 的结果格式化处理
 输入参数  : enReturnCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月24日
    作    者   : l00171473
    修改内容   : 新生成函数 for V7R1C50_At_Abort, 提取函数降复杂度

*****************************************************************************/
VOS_VOID AT_FormatAtCmdNotSupportResult(
    VOS_UINT8                           ucIndex,
    AT_RRETURN_CODE_ENUM_UINT32         enReturnCode
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;

    pucDataAt = pgucAtSndCodeAddr;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)gaucAtCmdNotSupportStr);
    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCmdNotSupportStr, ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    if ( (AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength) )
    {
        PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                    pucDataAt,
                    usLength);
        gstAtCombineSendData[ucIndex].usBufLen += usLength;
    }

    At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

}

/*****************************************************************************
 函 数 名  : AT_FormatAtTooManyParaResult
 功能描述  : AT_TOO_MANY_PARA 的结果格式化处理
 输入参数  : enReturnCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月24日
    作    者   : l00171473
    修改内容   : 新生成函数 for V7R1C50_At_Abort, 提取函数降复杂度

*****************************************************************************/
VOS_VOID AT_FormatAtTooManyParaResult(
    VOS_UINT8                           ucIndex,
    AT_RRETURN_CODE_ENUM_UINT32         enReturnCode
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;

    pucDataAt = pgucAtSndCodeAddr;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)gaucAtTooManyParaStr);
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)gaucAtTooManyParaStr, ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
    {
        PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                    pucDataAt,
                    usLength);
        gstAtCombineSendData[ucIndex].usBufLen += usLength;
    }

    At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

    return;
}

/*****************************************************************************
 函 数 名  : AT_FormatAtAbortResult
 功能描述  : AT_ABORT 的结果格式化处理
 输入参数  : ucIndex:索引号
              enReturnCode:返回码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月24日
    作    者   : l00171473
    修改内容   : 新生成函数 for V7R1C50_At_Abort, 处理新增错误码

*****************************************************************************/
VOS_VOID AT_FormatAtAbortResult(
    VOS_UINT8                           ucIndex,
    AT_RRETURN_CODE_ENUM_UINT32         enReturnCode
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;

    pucDataAt = pgucAtSndCodeAddr;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 获取打断回复 */
    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    /* 在打断回复后面，加上回车换行 */
    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    /* 把打断回复和回车换行等输出信息保存到全局变量中 */
    if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
    {
        PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                    pucDataAt,
                    usLength);
        gstAtCombineSendData[ucIndex].usBufLen += usLength;
    }

    /* 发送AT命令的数据给APP */
    At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

    return;
}


/*****************************************************************************
 函 数 名  : At_FormatResultData
 功能描述  : 根据V,+CMEE,对结果进行格式化
 输入参数  : VOS_UINT8                           ucIndex
             VOS_UINT32                          ulReturnCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期 : 2007-03-27
    作    者 : h59254
    修改内容 : 问题单号:A32D09820(PC-Lint修改)
  3.日    期   : 2008年10月30日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D07005,添加对不支持的AT命令的输出处理
  4.日    期   : 2010年09月25日
    作    者   : z00161729
    修改内容  : 问题单号：DTS2010091901225,通过AT口发起VP呼叫成功后，AT口不再可用
  5.日    期   : 2011年7月20日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011063000712 速率显示错误
  6.日    期   : 2011年10月22日
    作    者   : f62575
    修改内容   : AT PROJECT NAS_EventReport -> AT_EventReport
  7.日    期   : 2011年10月27日
    作    者   : f62575
    修改内容   : AT PROJECT gstAtSendData.usBufLen赋值错误
  8.日    期   : 2012年06月27日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目，增加XML文本模式的输入提示
  9.日    期   : 2012年9月19日
    作    者   : l00171473
    修改内容   : for V7R1C50_At_Abort, 增加 AT_ABORT错误码的上报
 10.日    期   : 2012年9月19日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
 11.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容   : UART-MODEM: 增加UART端口PPP拨号支持
 12.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
 13.日    期   : 2015年12月26日
    作    者   : f00179208
    修改内容   : Coverity告警清理
 14.日    期   : 2015年11月17日
    作    者   : zwx247453
    修改内容   : dallas gps参考时钟虚焊检测
*****************************************************************************/
VOS_VOID At_FormatResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulReturnCode
)
{
    VOS_UINT32                          ulTmp;
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pDataAt1;
    VOS_UINT8                          *pDataAt3;
    VOS_UINT32                          ulMdmMscFlg;

    VOS_UINT32                          ulComCmdSubProc;
    /* TAF_UINT32                          ulResult; */
    VOS_UINT32                          ulNvDialRateIndex;
    VOS_UINT8                           ucSubSysMode;
    VOS_UINT8                           aucDialRateTmp[AT_AP_RATE_STRLEN];
    /* Added by L60609 for AT Project，2011-10-24,  Begin*/
    VOS_UINT32                          ulReturnCodeIndex;
    VOS_UINT32                          ulRslt;
    /*AT_ERROR对应的index值*/
    VOS_UINT32                          ulAtErrIndex;
    VOS_UINT32                          ulAtErrRslt;

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_AGENT_SYS_MODE_STRU             stSysMode;
    VOS_UINT32                          ulRet;
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    /*变量初始化*/
    usLength               = gstAtSendData.usBufLen;
    gstAtSendData.usBufLen = 0;

    ulTmp                  = 0;
    pDataAt1               = pgucAtSndCrLfAddr;
    pDataAt3               = pgucAtSndCodeAddr;
    ulMdmMscFlg            = VOS_FALSE;
    ulRslt                 = VOS_ERR;

    ulAtErrIndex           = 0;
    ulReturnCodeIndex      = 0;
    /* Added by L60609 for AT Project，2011-10-24,  End*/

    PS_MEM_SET(aucDialRateTmp, 0, sizeof(aucDialRateTmp));

    ulComCmdSubProc = At_JudgeCombineCmdSubSequentProcess(ucIndex, ulReturnCode);

    if(ulReturnCode > AT_RRETURN_CODE_BUTT)
    {
        At_ResetCombinParseInfo(ucIndex);
        AT_CheckProcBlockCmd();
        return;
    }

    if ( AT_CMD_NOT_SUPPORT == ulReturnCode )
    {
        /* 提取函数降复杂度 */

        AT_FormatAtCmdNotSupportResult(ucIndex, (AT_RRETURN_CODE_ENUM_UINT32)ulReturnCode);

        At_ResetCombinParseInfo(ucIndex);
        AT_CheckProcBlockCmd();
        return;
    }

    if ( AT_TOO_MANY_PARA == ulReturnCode )
    {
        /* 提取函数降复杂度 */

        AT_FormatAtTooManyParaResult(ucIndex, (AT_RRETURN_CODE_ENUM_UINT32)ulReturnCode);

        At_ResetCombinParseInfo(ucIndex);
        AT_CheckProcBlockCmd();
        return;
    }

    if (AT_ABORT == ulReturnCode)
    {
        AT_FormatAtAbortResult(ucIndex, (AT_RRETURN_CODE_ENUM_UINT32)ulReturnCode);

        At_ResetCombinParseInfo(ucIndex);

        AT_CheckProcBlockCmd();
        /* 恢复AT端口的全局变量 */
        return;
    }

    /* Added by L60609 for AT Project，2011-10-24,  Begin*/
    ulRslt = AT_GetReturnCodeId(ulReturnCode, &ulReturnCodeIndex);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("At_FormatResultData: result code index is err!");
        return;
    }
    /* Added by L60609 for AT Project，2011-10-24,  End*/
    if ((AT_WAIT_SMS_INPUT == ulReturnCode)/* 进入SMS输入模式 */
        || (AT_WAIT_XML_INPUT == ulReturnCode))/* 进入XML文本输入模式 */
    {

        ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType]);
        PS_MEM_CPY( pDataAt3 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0], ulTmp );
        usLength += (TAF_UINT16)ulTmp;

        if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
        {
            PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                        pDataAt3,
                        usLength);
            gstAtCombineSendData[ucIndex].usBufLen += usLength;
        }

        At_SendResultData(ucIndex,pDataAt3,usLength);

        /* 清除gstAtCombineSendData的内容 */
        PS_MEM_SET(&gstAtCombineSendData[ucIndex], 0, sizeof(AT_SEND_DATA_BUFFER_STRU));

        return;
    }
    else if((AT_CME_ERROR_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_CME_ERROR_ENUM_END) )
    {
        switch (gucAtCmeeType)
        {
        case AT_CMEE_ONLY_ERROR:
            /* Added by L60609 for AT Project，2011-10-24,  Begin*/
            ulAtErrRslt = AT_GetReturnCodeId(AT_ERROR, &ulAtErrIndex);

            if(VOS_OK != ulAtErrRslt)
            {
                AT_ERR_LOG("At_FormatResultData: AT ERROR index is err!");
                return;
            }
            /* Added by L60609 for AT Project，2011-10-24,  End*/
            ulTmp = VOS_StrLen( (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType] );
            PS_MEM_CPY( pDataAt3 + usLength , (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType] , ulTmp );
            usLength += (TAF_UINT16)ulTmp;
            break;

        case AT_CMEE_ERROR_CODE:
            PS_MEM_CPY( pDataAt3 + usLength , (TAF_CHAR *)gaucAtCmeErrorStr, 12 );
            usLength += 12;

            ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0]);
            PS_MEM_CPY( pDataAt3 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0], ulTmp );
            usLength += (TAF_UINT16)ulTmp;
            break;

        default:
            PS_MEM_CPY( pDataAt3 + usLength , (TAF_CHAR *)gaucAtCmeErrorStr, 12 );
            usLength += 12;

            ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1]);
            PS_MEM_CPY( pDataAt3 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1], ulTmp );
            usLength += (TAF_UINT16)ulTmp;
            break;
        }
    }
    else if((AT_DEVICE_ERROR_BEGIN < ulReturnCode) && (ulReturnCode < AT_DEVICE_ERROR_END) )
    {
        PS_MEM_CPY( pDataAt3 + usLength , (TAF_CHAR *)gaucAtCmeErrorStr, 12 );
        usLength += 12;

        ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0]);
        PS_MEM_CPY( pDataAt3 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0], ulTmp );
        usLength += (TAF_UINT16)ulTmp;
    }
    else if((AT_CMS_ERROR_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_CMS_ERROR_ENUM_END) )
    {
        switch(gucAtCmeeType)
        {
            case AT_CMEE_ONLY_ERROR:
                /* Added by L60609 for AT Project，2011-10-24,  Begin*/
                ulAtErrRslt = AT_GetReturnCodeId(AT_ERROR, &ulAtErrIndex);

                if(VOS_OK != ulAtErrRslt)
                {
                    AT_ERR_LOG("At_FormatResultData: AT ERROR index is err!");
                    return;
                }
                /* Added by L60609 for AT Project，2011-10-24,  End*/

                ulTmp = VOS_StrLen( (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType] );
                PS_MEM_CPY( pDataAt3 + usLength , (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType] , ulTmp );
                usLength += (TAF_UINT16)ulTmp;
                break;

            case AT_CMEE_ERROR_CODE:

                PS_MEM_CPY( pDataAt3 + usLength , (TAF_CHAR *)gaucAtCmsErrorStr, 12 );
                usLength += 12;

                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0]);
                PS_MEM_CPY( pDataAt3 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0], ulTmp );
                usLength += (TAF_UINT16)ulTmp;
                break;

            default:
                PS_MEM_CPY( pDataAt3 + usLength , (TAF_CHAR *)gaucAtCmsErrorStr, 12 );
                usLength += 12;

                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1]);
                PS_MEM_CPY( pDataAt3 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1], ulTmp );
                usLength += (TAF_UINT16)ulTmp;
                break;
        }
    }
    else
    {

    }

    if (AT_V_ENTIRE_TYPE == gucAtVType)
    {
        if (0 != usLength)
        {
            PS_MEM_CPY(pDataAt1,(TAF_CHAR *)gaucAtCrLf,2);/*Text前面加\r\n*/

            PS_MEM_CPY(pDataAt3 + usLength,(TAF_CHAR *)gaucAtCrLf,2);/*Text后面加\r\n*/
            usLength += 2;
            usLength += 2;
        }

        if ((AT_COM_CMD_SUB_PROC_FINISH == ulComCmdSubProc)
            || (AT_COM_CMD_SUB_PROC_ABORT == ulComCmdSubProc))
        {
            if((AT_BASIC_CODE_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_BASIC_CODE_ENUM_END))
            {
                PS_MEM_CPY((TAF_CHAR *)(pDataAt1 + usLength),(TAF_CHAR *)gaucAtCrLf,2);/*Code前面加\r\n*/
                usLength += 2;

                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType]);
                PS_MEM_CPY(pDataAt1 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType], ulTmp);/*Code*/
                usLength += (TAF_UINT16)ulTmp;

                /*如果是PPP拨号且gucAtXType大于0，则CONNECT返回码需要附上速率信息，格式依照:CONNECT <Rate>*/
                if (AT_CONNECT == ulReturnCode)
                {
                    if ((AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
                        && ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
                              || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode) ) )
                    {
                        /* 设置管脚信号标志 */
                        ulMdmMscFlg = VOS_TRUE;

                        /* 若gucAtXType大于0，在CONNECT后附上速率信息 */
                        if (gucAtXType > 0)
                        {

                            PPP_RATE_DISPLAY_ENUM_UINT32 enRateDisplay;

                            /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
                            PS_MEM_SET(&stSysMode, 0, sizeof(stSysMode));

                            /* 从C核获取ucRatType和ucSysSubMode */
                            ulRet = TAF_AGENT_GetSysMode(ucIndex, &stSysMode);
                            if (VOS_OK != ulRet)
                            {
                                ucSubSysMode = TAF_SYS_SUBMODE_BUTT;
                            }
                            else
                            {
                                ucSubSysMode = stSysMode.enSysSubMode;
                            }

                            switch (ucSubSysMode)
                            {
                                case TAF_SYS_SUBMODE_GSM:
                                    ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGsmConnectRate;
                                break;
                                case TAF_SYS_SUBMODE_GPRS:
                                    ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGprsConnectRate;

                                break;
                                case TAF_SYS_SUBMODE_EDGE:
                                    ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucEdgeConnectRate;
                                break;
                                case TAF_SYS_SUBMODE_WCDMA:
                                    ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucWcdmaConnectRate;
                                break;
                                case TAF_SYS_SUBMODE_HSDPA:
                                case TAF_SYS_SUBMODE_HSDPA_HSUPA:
                                    ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucDpaConnectRate;
                                break;
                                default:
                                    ulNvDialRateIndex = 0;
                                break;
                            }

                            if ((0 == ulNvDialRateIndex) || (ulNvDialRateIndex > 6))
                            {
                                if ( (TAF_PH_INFO_WCDMA_RAT == stSysMode.enRatType)
                                  || (TAF_PH_INFO_TD_SCDMA_RAT == stSysMode.enRatType) )
                                {
                                    enRateDisplay = AT_GetRateDisplayIndexForWcdma(&g_stAtDlRateCategory);
                                    ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
                                    VOS_MemCpy(aucDialRateTmp, g_PppDialRateDisplay[enRateDisplay], ulTmp);
                                }
                            #if (FEATURE_ON == FEATURE_LTE)
                                else if (TAF_PH_INFO_LTE_RAT == stSysMode.enRatType)
                                {
                                    enRateDisplay = AT_GetRateDisplayIndexForLTE(&g_stAtDlRateCategory);
                                    ulTmp = VOS_StrLen((TAF_CHAR *)g_ucLTEDlRateDisplay[enRateDisplay]);
                                    VOS_MemCpy(aucDialRateTmp, g_ucLTEDlRateDisplay[enRateDisplay], ulTmp);
                                }
                            #endif
                                else
                                {
                                    enRateDisplay = AT_GetRateDisplayIndexForGsm(&stSysMode);
                                    ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
                                    VOS_MemCpy(aucDialRateTmp, g_PppDialRateDisplay[enRateDisplay], ulTmp);
                                }
                            }
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
                            else
                            {
                                ulTmp = VOS_StrLen((TAF_CHAR *)g_ucDialRateDisplayNv[ulNvDialRateIndex - 1]);
                                VOS_MemCpy(aucDialRateTmp, g_ucDialRateDisplayNv[ulNvDialRateIndex - 1], ulTmp);
                            }

                            /*在CONNECT后附上速率信息*/
                            PS_MEM_CPY(pDataAt1 + usLength, aucDialRateTmp, ulTmp);
                            usLength += (TAF_UINT16)ulTmp;
                        }
                    }
                    else if ((AT_CSD_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
                          && (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType))
                    {
                        /* 设置管脚信号标志 */
                        ulMdmMscFlg = VOS_TRUE;
                    }
                    else
                    {

                    }
                }
                if ( AT_NO_CARRIER == ulReturnCode )
                {
                    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
                      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
                    {
                        ulMdmMscFlg = VOS_TRUE;
                    }
                }

                PS_MEM_CPY(pDataAt1 + usLength,(TAF_CHAR *)gaucAtCrLf,2);/*Code后面加\r\n*/
                usLength += 2;

            }

            /* 拷贝<text>和结果码 */
            if ((0 != usLength)
                && ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength)))
            {
                PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                            pDataAt1,
                            usLength);
                gstAtCombineSendData[ucIndex].usBufLen += usLength;
            }

            At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

            if (VOS_TRUE == ulMdmMscFlg)
            {
                AT_ProcFormatResultMsc(ucIndex, ulReturnCode);
            }

            At_ResetCombinParseInfo(ucIndex);
            AT_CheckProcBlockCmd();
        }
        else
        {
            if ((0 != usLength)
                && ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength)))
            {
                PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                            pDataAt1,
                            usLength);
                gstAtCombineSendData[ucIndex].usBufLen += usLength;
            }

            AT_ParseCmdOver(ucIndex);
        }
    }
    else
    {
        if ((AT_COM_CMD_SUB_PROC_FINISH == ulComCmdSubProc)
            || (AT_COM_CMD_SUB_PROC_ABORT == ulComCmdSubProc))
        {
            if((AT_BASIC_CODE_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_BASIC_CODE_ENUM_END) )
            {
                if (0 != usLength)
                {
                   PS_MEM_CPY(pDataAt3 + usLength,(TAF_CHAR *)gaucAtCrLf,2);
                   usLength += 2;
                }
                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType]);
                PS_MEM_CPY(pDataAt3 + usLength, (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType], ulTmp);/*Code*/
                usLength += (TAF_UINT16)ulTmp;

                PS_MEM_CPY(pDataAt3 + usLength,&ucAtS3,1);/*Code后面加\r*/
                usLength += 1;
            }
            else
            {
                if ( 0 != usLength )
                {
                    if (AT_CMEE_ONLY_ERROR == gucAtCmeeType)
                    {
                        PS_MEM_CPY(pDataAt3 + usLength,&ucAtS3,1);
                        usLength += 1;
                    }
                    else
                    {
                        PS_MEM_CPY(pDataAt3 + usLength,(TAF_CHAR *)gaucAtCrLf,2);
                        usLength += 2;
                    }
                }
            }

            if ((0 != usLength)
                && ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength)))
            {
                PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                            pDataAt3,
                            usLength);
                gstAtCombineSendData[ucIndex].usBufLen += usLength;
            }

            At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

            At_ResetCombinParseInfo(ucIndex);
            AT_CheckProcBlockCmd();
        }
        else
        {
            if (0 != usLength)
            {
                PS_MEM_CPY(pDataAt3 + usLength,(TAF_CHAR *)gaucAtCrLf,2);
                usLength += 2;

                if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
                {
                    PS_MEM_CPY((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                                pDataAt3,
                                usLength);
                    gstAtCombineSendData[ucIndex].usBufLen += usLength;
                }
            }

            AT_ParseCmdOver(ucIndex);
        }
    }

}

/*****************************************************************************
 函 数 名  : AT_GetDlRateDisplayIndex
 功能描述  : 获取WCDMA模式缺省协议版本下行能力等级在速率显示表中的索引
 输入参数  : ucWasCategory - UE能力等级
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月14日
    作    者   : w00181244
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_GetDlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        }

     return enDlRateDisplayIndex;
}

/*****************************************************************************
 函 数 名  : AT_GetR7DlRateDisplayIndex
 功能描述  : 获取WCDMA模式R7协议版本下行能力等级在速率显示表中的索引
 输入参数  : ucWasCategory - UE能力等级
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月14日
    作    者   : w00181244
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_GetR7DlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        case AT_RATE_WCDMA_CATEGORY_14:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_14;
            break;

        case AT_RATE_WCDMA_CATEGORY_18:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

    }

    return enDlRateDisplayIndex;
}

/*****************************************************************************
 函 数 名  : AT_GetR8DlRateDisplayIndex
 功能描述  : 获取WCDMA模式R8协议版本下行能力等级在速率显示表中的索引
 输入参数  : ucWasCategory - UE能力等级
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月14日
    作    者   : w00181244
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_GetR8DlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        case AT_RATE_WCDMA_CATEGORY_14:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_14;
            break;

        case AT_RATE_WCDMA_CATEGORY_18:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

        case AT_RATE_WCDMA_CATEGORY_24:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_24;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_24;
            break;

        }

     return enDlRateDisplayIndex;
}

/*****************************************************************************
 函 数 名  : AT_GetR9DlRateDisplayIndex
 功能描述  : 获取WCDMA模式R9协议版本下行能力等级在速率显示表中的索引
 输入参数  : ucWasCategory - UE能力等级
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月14日
    作    者   : w00181244
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_GetR9DlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        case AT_RATE_WCDMA_CATEGORY_14:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_14;
            break;

        case AT_RATE_WCDMA_CATEGORY_18:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

        case AT_RATE_WCDMA_CATEGORY_24:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_24;
            break;

        case AT_RATE_WCDMA_CATEGORY_26:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_26;
            break;

        case AT_RATE_WCDMA_CATEGORY_28:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_28;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_28;
            break;

        }

     return enDlRateDisplayIndex;
}

/*****************************************************************************
 函 数 名  : AT_GetRateDisplayIndexForLTE
 功能描述  : 获取LTE模式下行能力等级在速率显示表中的索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月10日
    作    者   : w00182550
    修改内容   : 新生成函数

*****************************************************************************/
#if(FEATURE_ON == FEATURE_LTE)
VOS_UINT32 AT_GetRateDisplayIndexForLTE(
    AT_DOWNLINK_RATE_CATEGORY_STRU     *pstDlRateCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enRateIndex;

    enRateIndex = pstDlRateCategory->ucLteUeCategory;

    return enRateIndex;
}
#endif

/*****************************************************************************
 函 数 名  : AT_GetRateDisplayIndexForGsm
 功能描述  : 获取GSM模式下行能力等级在速率显示表中的索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年7月25日
    作    者   : z60575
    修改内容   : DTS2012072409126，GPRS下支持Class33时上报速率不正确
  3.日    期   : 2013年4月2日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 AT_GetRateDisplayIndexForGsm(
    TAF_AGENT_SYS_MODE_STRU            *pstSysMode
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enRateIndex;

    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    if ( TAF_SYS_SUBMODE_EDGE == pstSysMode->enSysSubMode )
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        if ( VOS_TRUE == g_stAtDlRateCategory.ucGasMultislotClass33Flg )
        {
            enRateIndex = PPP_RATE_DISPLAY_EDGE_CALSS33;
        }
        else
        {
            enRateIndex = PPP_RATE_DISPLAY_EDGE;
        }
    }
    else
    {
    	if ( VOS_TRUE == g_stAtDlRateCategory.ucGasMultislotClass33Flg )
        {
            enRateIndex = PPP_RATE_DISPLAY_GPRS_CALSS33;
        }
        else
        {
            enRateIndex = PPP_RATE_DISPLAY_GPRS;
        }
    }

    return enRateIndex;
}

/*****************************************************************************
 函 数 名  : AT_GetRateDisplayIndexForWcdma
 功能描述  : 获取WCDMA模式下行能力等级在速率显示表中的索引
 输入参数  : pstDlRateCategory - UE下行能力
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月14日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月13日
    作    者   : l00171473
    修改内容   : DTS2011092204540，MODEM拨号时速率显示不正确

*****************************************************************************/
VOS_UINT32 AT_GetRateDisplayIndexForWcdma(
    AT_DOWNLINK_RATE_CATEGORY_STRU     *pstDlRateCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enRateIndex;

    switch (pstDlRateCategory->cWasRelIndicator)
    {
        case PS_PTL_VER_R99:
        case PS_PTL_VER_R3:
        case PS_PTL_VER_R4:
            enRateIndex = PPP_RATE_DISPLAY_R99;
            break;

        case PS_PTL_VER_R5:
        case PS_PTL_VER_R6:
            enRateIndex = AT_GetDlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        case PS_PTL_VER_R7:
            enRateIndex = AT_GetR7DlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        case PS_PTL_VER_R8:
            enRateIndex = AT_GetR8DlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        case PS_PTL_VER_R9:
            enRateIndex = AT_GetR9DlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        default:
            enRateIndex = AT_GetDlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;
    }

    return enRateIndex;
}

#if (FEATURE_ON == FEATURE_AT_HSUART)
/*****************************************************************************
 函 数 名  : AT_IsSmsRingingTe
 功能描述  : 是否正在输出短信RI波形
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_IsSmsRingingTe(VOS_VOID)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;

    pstRiStateInfo = AT_GetUartRiStateInfo();

    if ( (VOS_TRUE == pstRiStateInfo->ulRunFlg)
      && (AT_UART_RI_TYPE_SMS == pstRiStateInfo->enType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_SmsRingOn
 功能描述  : 输出SMS RI信号高电平
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SmsRingOn(VOS_VOID)
{
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    pstRiCfgInfo   = AT_GetUartRiCfgInfo();
    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucIndex        = AT_CLIENT_TAB_HSUART_INDEX;

    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    /* RI信号设为高电平 */
    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    /* 启动RI信号电平保持定时器 */
    AT_StartRelTimer(&(pstRiStateInfo->hSmsRiTmrHdl),
                     pstRiCfgInfo->ulSmsRiOnInterval,
                     ulTmrName,
                     ulTmrParam,
                     VOS_RELTIMER_NOLOOP);

    pstRiStateInfo->enSmsRiTmrStatus = AT_TIMER_STATUS_RUNNING;

    return;
}

/*****************************************************************************
 函 数 名  : AT_SmsRingOff
 功能描述  : 输出SMS RI信号低电平
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SmsRingOff(VOS_VOID)
{
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    pstRiCfgInfo   = AT_GetUartRiCfgInfo();
    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucIndex        = AT_CLIENT_TAB_HSUART_INDEX;

    AT_SET_SMS_RI_TMR_NAME(ulTmrName);
    AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex);

    if (0 == pstRiCfgInfo->ulSmsRiOffInterval)
    {
        AT_SmsStopRingTe();
    }
    else
    {
        /* RI信号设为低电平 */
        AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

        /* 启动RI信号电平保持定时器 */
        AT_StartRelTimer(&(pstRiStateInfo->hSmsRiTmrHdl),
                         pstRiCfgInfo->ulSmsRiOffInterval,
                         ulTmrName,
                         ulTmrParam,
                         VOS_RELTIMER_NOLOOP);

        pstRiStateInfo->enSmsRiTmrStatus = AT_TIMER_STATUS_RUNNING;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_SmsStartRingTe
 功能描述  : 开始短信RING TE
 输入参数  : ulNewSmsFlg - 用于区分是否增加短信通知波形计数的标识
                           (1) 收到协议栈的短信上报, 该标识为TRUE
                           (2) 恢复被来电打断的波形输出, 该标识为FALSE
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SmsStartRingTe(VOS_UINT32 ulNewSmsFlg)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;

    pstRiStateInfo = AT_GetUartRiStateInfo();

    /* 检查增加短信通知波形计数的标识 */
    if (VOS_TRUE == ulNewSmsFlg)
    {
        pstRiStateInfo->ulSmsRiOutputCount++;
    }

    /* 检查是否正在输出波形 */
    if (VOS_TRUE == pstRiStateInfo->ulRunFlg)
    {
        return;
    }

    /* 输出RI信号高电平波形 */
    AT_SmsRingOn();

    /* 记录RI信号状态 */
    pstRiStateInfo->ulRunFlg = VOS_TRUE;
    pstRiStateInfo->enType   = AT_UART_RI_TYPE_SMS;

    return;
}

/*****************************************************************************
 函 数 名  : AT_SmsStopRingTe
 功能描述  : 停止短信RING TE
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SmsStopRingTe(VOS_VOID)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT8                           ucIndex;

    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucIndex        = AT_CLIENT_TAB_HSUART_INDEX;

    AT_SET_SMS_RI_TMR_NAME(ulTmrName);

    /* RI信号设为低电平 */
    if (AT_IO_LEVEL_HIGH == AT_GetIoLevel(ucIndex, IO_CTRL_RI))
    {
        AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);
    }

    /* 如果电平保持定时器已经停止, 说明短信通知波形已经完整输出 */
    if (AT_TIMER_STATUS_RUNNING == pstRiStateInfo->enSmsRiTmrStatus)
    {
        /* 停止RI信号电平保持定时器 */
        AT_StopRelTimer(ulTmrName, &(pstRiStateInfo->hSmsRiTmrHdl));
        pstRiStateInfo->enSmsRiTmrStatus = AT_TIMER_STATUS_STOP;
    }
    else
    {
        /* 更新短信通知计数 */
        if (pstRiStateInfo->ulSmsRiOutputCount > 0)
        {
            pstRiStateInfo->ulSmsRiOutputCount--;
        }
    }

    /* 清除RI信号状态 */
    pstRiStateInfo->ulRunFlg = VOS_FALSE;
    pstRiStateInfo->enType   = AT_UART_RI_TYPE_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvTiSmsRiExpired
 功能描述  : SMS RI信号保持定时器超时处理
 输入参数  : pstTmrMsg - 定时器超时消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_RcvTiSmsRiExpired(REL_TIMER_MSG *pstTmrMsg)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucIndex        = AT_GET_SMS_RI_CLIENTID_FROM_TMR_PARAM(pstTmrMsg->ulPara);

    /* 短信通知波形输出已停止 */
    if (VOS_TRUE != AT_IsSmsRingingTe())
    {
        return;
    }

    /* 更新定时器状态 */
    pstRiStateInfo->enSmsRiTmrStatus = AT_TIMER_STATUS_STOP;

    /* RI信号电平控制 */
    if (AT_IO_LEVEL_HIGH == AT_GetIoLevel(ucIndex, IO_CTRL_RI))
    {
        AT_SmsRingOff();
    }
    else
    {
        AT_SmsStopRingTe();
    }

    /* SMS RI配置低电平持续时间为0时, 需要重新开始RING TE */
    if ( (VOS_TRUE != AT_IsSmsRingingTe())
      && (0 != pstRiStateInfo->ulSmsRiOutputCount) )
    {
        AT_SmsStartRingTe(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_IsVoiceRingingTe
 功能描述  : 是否正在输出语音RI波形
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_IsVoiceRingingTe(VOS_VOID)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;

    pstRiStateInfo = AT_GetUartRiStateInfo();

    if ( (VOS_TRUE == pstRiStateInfo->ulRunFlg)
      && (AT_UART_RI_TYPE_VOICE == pstRiStateInfo->enType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_VoiceGetRingingCallId
 功能描述  : 获取当前呼叫RI的CALLID
 输入参数  : ucCallId - CALLID [1,7]
 输出参数  : 无
 返 回 值  : AT_UART_RI_STATUS_STOP    - RI停止
             AT_UART_RI_STATUS_RINGING - RI进行中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
AT_UART_RI_STATUS_ENUM_UINT8 AT_GetRiStatusByCallId(VOS_UINT8 ucCallId)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;

    pstRiStateInfo = AT_GetUartRiStateInfo();

    /* 检查CALLID有效性 */
    if (ucCallId > MN_CALL_MAX_NUM)
    {
        return AT_UART_RI_STATUS_STOP;
    }

    return pstRiStateInfo->aenVoiceRiStatus[ucCallId];
}

/*****************************************************************************
 函 数 名  : AT_VoiceRingOn
 功能描述  : 输出VOICE RI信号高电平
 返 回 值  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_VoiceRingOn(VOS_UINT8 ucCallId)
{
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    pstRiCfgInfo   = AT_GetUartRiCfgInfo();
    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucIndex        = AT_CLIENT_TAB_HSUART_INDEX;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    /* RI信号设为高电平 */
    AT_CtrlRI(ucIndex, AT_IO_LEVEL_HIGH);

    /* 启动RI信号电平保持定时器 */
    AT_StartRelTimer(&(pstRiStateInfo->hVoiceRiTmrHdl),
                     pstRiCfgInfo->ulVoiceRiOnInterval,
                     ulTmrName,
                     ulTmrParam,
                     VOS_RELTIMER_NOLOOP);

    pstRiStateInfo->enVoiceRiTmrStatus = AT_TIMER_STATUS_RUNNING;

    return;
}

/*****************************************************************************
 函 数 名  : AT_VoiceRingOff
 功能描述  : 输出VOICE RI信号低电平
 返 回 值  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_VoiceRingOff(VOS_UINT8 ucCallId)
{
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT32                          ulTmrParam;
    VOS_UINT8                           ucIndex;

    pstRiCfgInfo   = AT_GetUartRiCfgInfo();
    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucIndex        = AT_CLIENT_TAB_HSUART_INDEX;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);
    AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId);

    /* RI信号设为低电平 */
    AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);

    /* 启动RI信号电平保持定时器 */
    AT_StartRelTimer(&(pstRiStateInfo->hVoiceRiTmrHdl),
                     pstRiCfgInfo->ulVoiceRiOffInterval,
                     ulTmrName,
                     ulTmrParam,
                     VOS_RELTIMER_NOLOOP);

    pstRiStateInfo->enVoiceRiTmrStatus = AT_TIMER_STATUS_RUNNING;

    return;
}

/*****************************************************************************
 函 数 名  : AT_VoiceStartRingTe
 功能描述  : 开始语音RING TE
 输入参数  : ucCallId - 呼叫ID [1,7]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_VoiceStartRingTe(VOS_UINT8 ucCallId)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;

    pstRiStateInfo = AT_GetUartRiStateInfo();

    /* 检查CALLID有效性 */
    if (ucCallId > MN_CALL_MAX_NUM)
    {
        return;
    }

    /* 检查当前是否正在输出来电通知波形 */
    if (VOS_TRUE == AT_IsVoiceRingingTe())
    {
        return;
    }

    /* 检查当前是否正在短信通知波形 */
    if (VOS_TRUE == AT_IsSmsRingingTe())
    {
        /* 打断短信通知波形输出 */
        AT_SmsStopRingTe();
    }

    /* 输出RI信号高电平波形 */
    AT_VoiceRingOn(ucCallId);

    /* 记录RI信号状态 */
    pstRiStateInfo->ulRunFlg                   = VOS_TRUE;
    pstRiStateInfo->enType                     = AT_UART_RI_TYPE_VOICE;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_RINGING;

    return;
}

/*****************************************************************************
 函 数 名  : AT_VoiceStopRingTe
 功能描述  : 停止语音RING TE
 输入参数  : ucCallId - 呼叫ID [1,7]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_VoiceStopRingTe(VOS_UINT8 ucCallId)
{
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulTmrName;
    VOS_UINT8                           ucIndex;

    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucIndex        = AT_CLIENT_TAB_HSUART_INDEX;

    AT_SET_VOICE_RI_TMR_NAME(ulTmrName);

    /* 检查CALLID有效性 */
    if (ucCallId > MN_CALL_MAX_NUM)
    {
        return;
    }

    /* 检查当前是否正在输出来电通知波形 */
    if (VOS_TRUE != AT_IsVoiceRingingTe())
    {
        return;
    }

    /* 检查CALLID对应的RI状态 */
    if (AT_UART_RI_STATUS_RINGING != AT_GetRiStatusByCallId(ucCallId))
    {
        return;
    }

    /* RI信号设为低电平 */
    if (AT_IO_LEVEL_HIGH == AT_GetIoLevel(ucIndex, IO_CTRL_RI))
    {
        AT_CtrlRI(ucIndex, AT_IO_LEVEL_LOW);
    }

    /* 停止RI信号电平保持定时器 */
    if (AT_TIMER_STATUS_RUNNING == pstRiStateInfo->enVoiceRiTmrStatus)
    {
        AT_StopRelTimer(ulTmrName, &(pstRiStateInfo->hVoiceRiTmrHdl));
        pstRiStateInfo->enVoiceRiTmrStatus     = AT_TIMER_STATUS_STOP;
    }

    /* 清除RI信号状态 */
    pstRiStateInfo->ulRunFlg                   = VOS_FALSE;
    pstRiStateInfo->enType                     = AT_UART_RI_TYPE_BUTT;
    pstRiStateInfo->aenVoiceRiStatus[ucCallId] = AT_UART_RI_STATUS_STOP;
    pstRiStateInfo->ulVoiceRiCycleCount        = 0;

    /* 恢复输出短信通知波形 */
    if (pstRiStateInfo->ulSmsRiOutputCount > 0)
    {
        AT_SmsStartRingTe(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvTiVoiceRiExpired
 功能描述  : VOICE RI信号保持定时器超时处理
 输入参数  : pstTmrMsg - 定时器超时消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_RcvTiVoiceRiExpired(REL_TIMER_MSG *pstTmrMsg)
{
    AT_UART_RI_CFG_STRU                *pstRiCfgInfo   = VOS_NULL_PTR;
    AT_UART_RI_STATE_INFO_STRU         *pstRiStateInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucIndex;

    pstRiCfgInfo   = AT_GetUartRiCfgInfo();
    pstRiStateInfo = AT_GetUartRiStateInfo();
    ucCallId       = AT_GET_VOICE_RI_CALLID_FROM_TMR_PARAM(pstTmrMsg->ulPara);
    ucIndex        = AT_GET_VOICE_RI_CLIENTID_FROM_TMR_PARAM(pstTmrMsg->ulPara);

    /* 检查语音RI是否已经停止 */
    if (VOS_TRUE != AT_IsVoiceRingingTe())
    {
        return;
    }

    /* 检查CALLID对应的RI状态 */
    if (AT_UART_RI_STATUS_RINGING != AT_GetRiStatusByCallId(ucCallId))
    {
        return;
    }

    /* 更新定时器状态 */
    pstRiStateInfo->enVoiceRiTmrStatus = AT_TIMER_STATUS_STOP;

    /* RI信号电平控制 */
    if (AT_IO_LEVEL_HIGH == AT_GetIoLevel(ucIndex, IO_CTRL_RI))
    {
        AT_VoiceRingOff(ucCallId);
    }
    else
    {
        /* 波形输出计数达到配置值, 停止RING TE, 否则继续 */
        if ((++pstRiStateInfo->ulVoiceRiCycleCount) >= pstRiCfgInfo->ucVoiceRiCycleTimes)
        {
            AT_VoiceStopRingTe(ucCallId);
        }
        else
        {
            AT_VoiceRingOn(ucCallId);
        }
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_ProcFormatResultMsc
 功能描述  :
 输入参数  : ulReturnCode 标识是连接还是断开连接
             ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID AT_ProcFormatResultMsc(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulReturnCode
)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    AT_DCE_MSC_STRU                     stMscStru;

    VOS_MemSet(&stMscStru, 0x00, sizeof(AT_DCE_MSC_STRU));

    pstUartCtx      = AT_GetUartCtxAddr();

    if (AT_CONNECT == ulReturnCode)
    {
        if (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
        {
            /* 判断&S并处理DSR管脚  */
            if (AT_UART_DSR_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDsrMode)
            {
                AT_CtrlDSR(ucIndex, AT_IO_LEVEL_HIGH);
            }

            /* 判断&C并处理DCD管脚  */
            if (AT_UART_DCD_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDcdMode)
            {
                AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);
            }
        }
        else
        {
            /* 拉高DCD信号 */
            AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);
        }
    }
    else
    {
        if (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
        {
           /* 判断&S并处理DSR管脚  */
            if (AT_UART_DSR_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDsrMode)
            {
                AT_CtrlDSR(ucIndex, AT_IO_LEVEL_LOW);
            }

            /* 判断&C并处理DCD管脚  */
            if (AT_UART_DCD_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDcdMode)
            {
                AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
            }
        }
        else
        {
            /* 拉低DCD信号 */
            AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        }
    }

}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

