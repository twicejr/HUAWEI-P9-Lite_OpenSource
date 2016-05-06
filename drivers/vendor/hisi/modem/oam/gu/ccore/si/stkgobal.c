/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SimProc.c
Author      : z00100318
Version     : V200R001
Date        : 2008-10-18
Description : 该文件定义了SIM卡事件实现

Description : SIM卡事件的处理和实现
History     :

1.日    期  : 2008年10月28日
  作    者  : H59254
  修改内容  : Create
************************************************************************/
#include "si_stk.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_STK_GOBAL_C
/*lint +e767*/

SI_STK_DATA_INFO_STRU                   gstUsatCmdDecode;

SI_STK_REQ_UINT_STRU                    gstSTKCtrlStru;

HTIMER                                  gstSTKProtectTimer  = VOS_NULL_PTR;

HTIMER                                  gstSTKINDTimer      = VOS_NULL_PTR;

HTIMER                                  gstSTKRefreshCnfTimer = VOS_NULL_PTR;

HTIMER                                  gstSTKSetupCallDurationTimer    = VOS_NULL_PTR;

HTIMER                                  gstSTKDtmfPauseTimer            = VOS_NULL_PTR;

/* 网络测量定时器 */
HTIMER                                  gstSTKNMRTimer                  = VOS_NULL_PTR;

VOS_UINT8                               gucSTKRefreshQua;

VOS_UINT8                               *g_pucSTKSndCodeAddr  = VOS_NULL_PTR;

/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
HTIMER                                  gstSTKGetTATimer = VOS_NULL_PTR;
/* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

USIMM_STK_CFG_STRU                      g_stSTKProfileContent;

SI_STK_TIMER_STRU                       gstSTKTimer[STK_TIMER_MAX_NUM];

SI_STK_EVENT_STATE_STRU                 g_stSTKEventState;

SI_SAT_SetUpMenu_DATA_STRU              gstSetUpMenuData;

SI_STK_IMSICHG_CTRL_STRU                gstSTKIMSIChgCtrl;/* IMSI切换控制变量 */

SI_STK_IMSICHG_MATCH_STRU               gstSTKIMSIMatch; /* NV项读出的IMSI切换匹配码流 */

SI_STK_ENVELOPE_CMD_STRU                gstSTKEnvelopeCmd; /* 缓存Envelope命令 */

VOS_SEM                                 gulSTKApiSmId       = VOS_NULL_LONG; /*互斥操作*/

VOS_UINT16                              gusSTKSMSIndEnable;/* SEND SMS主动命令上报控制 */

MODEM_ID_ENUM_UINT16                    g_enSTKCurCSModem;  /*SVLTE用于记录当前CS服务的Modem*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

SI_STK_CDMANAS_SYSINFO_STRU             g_stStkCdmaSysInfo;

VOS_UINT8                               g_ucIsXsmsInBuffFlag;   /* FALSE: NO IN BUFF
                                                           TRUR : ONE IN BUFF*/
TAF_XSMS_MESSAGE_STRU                  *g_pstStkSendXsmsBuff;

TAF_XSMS_MESSAGE_STRU                  *g_pstStkRcvXsmsBuff;

#endif

SI_STK_NAS_INFO_STRU                    g_stStkSysInfo;

/*重发Event的数据缓冲区，仅用于C+L的电信Event重发机制*/
STK_EVENTDATA_RESEND_STRU               g_astEventResend[2];


/*支持的STK 命令解码列表*/
VOS_UINT8 gucRefresh[]          = {FILE_LIST_TAG,AID_TAG,ALPHA_IDENTIFIER_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG,PLMNWACT_LIST_TAG};

VOS_UINT8 gucPollInterval[]     = {DURATION_TAG};

VOS_UINT8 gucSetUpEventList[]   = {EVENT_LIST_TAG};

VOS_UINT8 gucUsatSetupCall[]    = {ALPHA_IDENTIFIER_TAG,ADDRESS_TAG,CAP_CFG_PARA_TAG,SUBADDRESS_TAG,DURATION_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatSendSS[]       = {ALPHA_IDENTIFIER_TAG,SS_STRING_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG};

VOS_UINT8 gucUsatSendUSSD[]     = {ALPHA_IDENTIFIER_TAG,USSD_STRING_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG};

VOS_UINT8 gucUsatSendSMS[]      = {ALPHA_IDENTIFIER_TAG,ADDRESS_TAG,SMS_TPDU_TAG,CDMA_SMS_TPDU,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatSendDTMF[]     = {ALPHA_IDENTIFIER_TAG,DTMF_STRING_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatLangBrowser[]  = {BROWSER_IDENTITY_TAG,URL_TAG,BEARER_TAG,TEXT_STRING_TAG,ALPHA_IDENTIFIER_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatPlayTone[]     = {ALPHA_IDENTIFIER_TAG,TONE_TAG,DURATION_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatDispayText[]   = {TEXT_STRING_TAG,ICON_IDENTIFIER_TAG,DURATION_TAG,TEXT_ATTRIBUTE_TAG,IMMEDIATE_RESPONSE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatGetInkey[]     = {TEXT_STRING_TAG,ICON_IDENTIFIER_TAG,DURATION_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatGetInput[]     = {TEXT_STRING_TAG,RESPONSE_LENGTH_TAG,DEFAULT_TEXT_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatSelectItem[]   = {ALPHA_IDENTIFIER_TAG,MS_NEXTACTION_INDICATOR_TAG,ICON_IDENTIFIER_TAG,ITEM_ICONID_LIST_TAG,TEXT_ATTRIBUTE_TAG,ITEM_TEXT_ATTRIBUTE_LIST_TAG,ITEM_IDENTIFIER_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatSetupMenu[]    = {ALPHA_IDENTIFIER_TAG,MS_NEXTACTION_INDICATOR_TAG,ICON_IDENTIFIER_TAG,ITEM_ICONID_LIST_TAG,TEXT_ATTRIBUTE_TAG,ITEM_TEXT_ATTRIBUTE_LIST_TAG};

VOS_UINT8 gucProvideLocalInfo[] = {UTRAN_MEASUREMENT_TAG};

VOS_UINT8 gucTimerManage[]      = {TIMER_IDENTIFIER_TAG,TIMER_VALUE_TAG};

VOS_UINT8 gucUsatIdleText[]     = {TEXT_STRING_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucUsatOpenChannel[]  = {ALPHA_IDENTIFIER_TAG,ICON_IDENTIFIER_TAG,ADDRESS_TAG,SUBADDRESS_TAG,DURATION_TAG,BEARER_DESCRIPTION_TAG,BUFFER_SIZE_TAG,NETWORK_ACCESS_NAME_TAG,TEXT_STRING_TAG,UICC_TERMINAL_TRAN_LEVEL_TAG,TEXT_ATTRIBUTE_TAG,OTHER_ADDR_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucCloseChannel[]     = {ALPHA_IDENTIFIER_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucReceiveData[]      = {ALPHA_IDENTIFIER_TAG,ICON_IDENTIFIER_TAG,TEXT_ATTRIBUTE_TAG,CHANNEL_DATA_LENGTH_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucSendData[]         = {ALPHA_IDENTIFIER_TAG,ICON_IDENTIFIER_TAG,CHANNEL_DATA_TAG,TEXT_ATTRIBUTE_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucSetFrame[]         = {FRAME_LAYOUT_TAG,FRAME_IDENTIFIER_TAG};

VOS_UINT8 gucLNotification[]    = {LANGUAGE_TAG};

/*支持的STK 命令回复编码列表*/
VOS_UINT8 gucSetUpCallRsp[]     = {CALL_CONTROL_REQACTION_TAG, RESULT_TAG,TEXT_STRING_TAG};

VOS_UINT8 gucGetInkey[]         = {TEXT_STRING_TAG};

VOS_UINT8 gucSelectItemRsp[]    = {ITEM_IDENTIFIER_TAG};

VOS_UINT8 gucSetFramesRsp[]     = {FRAMES_INFORMATION_TAG};

VOS_UINT8 guGetFramesRsp[]      = {FRAMES_INFORMATION_TAG};

/*支持的STK Event命令回复编码列表*/
VOS_UINT8 gucMTCallEvent[]      = {TRANSACTION_IDENTIFIER_TAG,ADDRESS_TAG,SUBADDRESS_TAG};

VOS_UINT8 gucCallContEvent[]    = {TRANSACTION_IDENTIFIER_TAG};

VOS_UINT8 gucCallDisContEvent[] = {TRANSACTION_IDENTIFIER_TAG, CAUSE_TAG};

VOS_UINT8 gucLociEvent[]        = {LOCATION_STATUS_TAG, LOCATION_INFORMATION_TAG};

VOS_UINT8 gucCRStatusEvent[]    = {CARD_READER_STATUS_TAG};

VOS_UINT8 gucLSelectEvent[]     = {LANGUAGE_TAG};

VOS_UINT8 gucBrowserTEvent[]    = {BROWSER_TERMINATION_CAUSE_TAG};

VOS_UINT8 gucDataAEvent[]       = {CHANNEL_STATUS_TAG, CHANNEL_DATA_LENGTH_TAG};

VOS_UINT8 gucChannelSEvent[]    = {CHANNEL_STATUS_TAG, BEARER_DESCRIPTION_TAG, OTHER_ADDR_TAG};

VOS_UINT8 gucATCEvent[]         = {ACCESS_TECHNOLOGY_TAG};

VOS_UINT8 gucDPCEvent[]         = {DISPLAY_PARAMETERS_TAG};

VOS_UINT8 gucLCEvent[]          = {SERVICE_RECORD_TAG, REMOTE_ENTITY_ADDRESS_TAG,UICC_TERMINAL_TRAN_LEVEL_TAG,OTHER_ADDR_TAG};

VOS_UINT8 gucNSMCEvent[]        = {NETWORK_SEARCH_MODE_TAG};

VOS_UINT8 gucBSEvent[]          = {BROWSING_STATUS_TAG};

VOS_UINT8 gucFIEvent[]          = {FRAMES_INFORMATION_TAG};

VOS_UINT8 gucNetRejEvent[]      = {LOCATION_INFORMATION_TAG, ROUTING_AREA_INFO_TAG, TRACKING_AREA_ID_TAG,
                                   ACCESS_TECHNOLOGY_TAG, ATTACH_TYPE_TAG, REJETION_CAUSE_CODE_TAG};

/*Envelope 命令下载编码列表*/
VOS_UINT8 gucMenuSelect[]       = {ITEM_IDENTIFIER_TAG,HELP_REQUEST_TAG};

VOS_UINT8 gucCallCtrl[]         = {CAP_CFG_PARA_TAG,SUBADDRESS_TAG,LOCATION_INFORMATION_TAG,CAP_CFG_PARA_TAG,BC_REPEAT_INDICATOR_TAG};

VOS_UINT8 gucMOSMSCtrl[]        = {ADDRESS_TAG,ADDRESS_TAG,LOCATION_INFORMATION_TAG};

VOS_UINT8 gucPPDown[]           = {ADDRESS_TAG, SMS_TPDU_TAG, CDMA_SMS_TPDU };

VOS_UINT8 gucCBDown[]           = {CELL_BROADCAST_PAGE_TAG};

VOS_UINT8 gucMMSTran[]          = {FILE_LIST_TAG,MMS_IDENTIFIER_TAG,MMS_TRANSFER_STATUS_TAG};

VOS_UINT8 gucMMSNotify[]        = {MMS_NOTIFICATION_TAG, LAST_ENVELOPE_TAG};

/*Envelope 命令回复列表 */
VOS_UINT8 gucCallCtrlRsp[]      = {CAP_CFG_PARA_TAG,SUBADDRESS_TAG,ALPHA_IDENTIFIER_TAG,BC_REPEAT_INDICATOR_TAG,CAP_CFG_PARA_TAG};

VOS_UINT8 gucMOSMSCtrlRsp[]     = {ALPHA_IDENTIFIER_TAG};



/*通用处理列表*/

SI_STK_TAGLIST_STRU gastSTKDecodeList[24]={ {SI_STK_REFRESH,                sizeof(gucRefresh),         gucRefresh          },
                                            {SI_STK_POLLINTERVAL,           sizeof(gucPollInterval),    gucPollInterval     },
                                            {SI_STK_SETUPEVENTLIST,         sizeof(gucSetUpEventList),  gucSetUpEventList   },
                                            {SI_STK_SETUPCALL,              sizeof(gucUsatSetupCall),   gucUsatSetupCall    },
                                            {SI_STK_SENDSS,                 sizeof(gucUsatSendSS),      gucUsatSendSS       },
                                            {SI_STK_SENDUSSD,               sizeof(gucUsatSendUSSD),    gucUsatSendUSSD     },
                                            {SI_STK_SENDSMS,                sizeof(gucUsatSendSMS),     gucUsatSendSMS      },
                                            {SI_STK_SENDDTMF,               sizeof(gucUsatSendDTMF),    gucUsatSendDTMF     },
                                            {SI_STK_LAUNCHBROWSER,          sizeof(gucUsatLangBrowser), gucUsatLangBrowser  },
                                            {SI_STK_PLAYTONE,               sizeof(gucUsatPlayTone),    gucUsatPlayTone     },
                                            {SI_STK_DISPLAYTET,             sizeof(gucUsatDispayText),  gucUsatDispayText   },
                                            {SI_STK_GETINKEY,               sizeof(gucUsatGetInkey),    gucUsatGetInkey     },
                                            {SI_STK_GETINPUT,               sizeof(gucUsatGetInput),    gucUsatGetInput     },
                                            {SI_STK_SELECTITEM,             sizeof(gucUsatSelectItem),  gucUsatSelectItem   },
                                            {SI_STK_SETUPMENU,              sizeof(gucUsatSetupMenu),   gucUsatSetupMenu    },
                                            {SI_STK_PROVIDELOCALINFO,       sizeof(gucProvideLocalInfo),gucProvideLocalInfo },
                                            {SI_STK_TIMERMANAGEMENT,        sizeof(gucTimerManage),     gucTimerManage      },
                                            {SI_STK_SETUPIDLETEXT,          sizeof(gucUsatIdleText),    gucUsatIdleText     },
                                            {SI_STK_OPENCHANNEL,            sizeof(gucUsatOpenChannel), gucUsatOpenChannel  },
                                            {SI_STK_CLOSECHANNEL,           sizeof(gucCloseChannel),    gucCloseChannel     },
                                            {SI_STK_RECEIVEDATA,            sizeof(gucReceiveData),     gucReceiveData      },
                                            {SI_STK_SENDDATA,               sizeof(gucSendData),        gucSendData         },
                                            {SI_STK_SETFRAMES,              sizeof(gucSetFrame),        gucSetFrame         },
                                            {SI_STK_LANGUAGENOTIFICATION,   sizeof(gucLNotification),   gucLNotification    }
                                          };

SI_STK_TAGLIST_STRU gastRespCodeList[8]={   {SI_STK_SETUPCALL,       sizeof(gucSetUpCallRsp),    gucSetUpCallRsp },
                                            {SI_STK_SENDSS,          sizeof(gucSetUpCallRsp),    gucSetUpCallRsp },
                                            {SI_STK_SENDUSSD,        sizeof(gucSetUpCallRsp),    gucSetUpCallRsp },
                                            {SI_STK_GETINKEY,        sizeof(gucGetInkey),        gucGetInkey     },
                                            {SI_STK_GETINPUT,        sizeof(gucGetInkey),        gucGetInkey     },
                                            {SI_STK_SELECTITEM,      sizeof(gucSelectItemRsp),   gucSelectItemRsp},
                                            {SI_STK_SETFRAMES,       sizeof(gucSetFramesRsp),    gucSetFramesRsp },
                                            {SI_STK_GETFRAMESSTATUS, sizeof(guGetFramesRsp),     guGetFramesRsp  }
                                         };

SI_STK_TAGLIST_STRU gastEventCodeList[16]={ {SI_STK_EVENT_MT_CALL,              sizeof(gucMTCallEvent),     gucMTCallEvent      },
                                            {SI_STK_EVENT_CALL_CONNECTED,       sizeof(gucCallContEvent),   gucCallContEvent    },
                                            {SI_STK_EVENT_CALL_DISCONNECTED,    sizeof(gucCallDisContEvent),gucCallDisContEvent },
                                            {SI_STK_EVENT_LOCATION_STATUS,      sizeof(gucLociEvent),       gucLociEvent        },
                                            {SI_STK_EVENT_CARDREADER_STATUS,    sizeof(gucCRStatusEvent),   gucCRStatusEvent    },
                                            {SI_STK_EVENT_LANGUAGE_SELECTION,   sizeof(gucLSelectEvent),    gucLSelectEvent     },
                                            {SI_STK_EVENT_BROWSER_TERMINATION,  sizeof(gucBrowserTEvent),   gucBrowserTEvent    },
                                            {SI_STK_EVENT_DATA_AVAILABLE,       sizeof(gucDataAEvent),      gucDataAEvent       },
                                            {SI_STK_EVENT_CHANNEL_STATUS,       sizeof(gucChannelSEvent),   gucChannelSEvent    },
                                            {SI_STK_EVENT_ACCESS_TECHN_CHANGE,  sizeof(gucATCEvent),        gucATCEvent         },
                                            {SI_STK_EVENT_DISPLAY_PARA_CHANGED, sizeof(gucDPCEvent),        gucDPCEvent         },
                                            {SI_STK_EVENT_LOCAL_CONNECTION,     sizeof(gucLCEvent),         gucLCEvent          },
                                            {SI_STK_EVENT_NET_SEARCHMODE_CHANGE,sizeof(gucNSMCEvent),       gucNSMCEvent        },
                                            {SI_STK_EVENT_BROWSING_STATUS,      sizeof(gucBSEvent),         gucBSEvent          },
                                            {SI_STK_EVENT_FRAMES_INFO_CHANGE,   sizeof(gucFIEvent),         gucFIEvent          },
                                            {SI_STK_EVENT_NETWORK_REJECTION,    sizeof(gucNetRejEvent),     gucNetRejEvent      },
                                          };

SI_STK_TAGLIST_STRU gastEnvelopeList[7]= {  {SI_STK_ENVELOPE_PPDOWN,            sizeof(gucPPDown),          gucPPDown           },
                                            {SI_STK_ENVELOPE_CBDOWN,            sizeof(gucCBDown),          gucCBDown           },
                                            {SI_STK_ENVELOPE_MENUSEL,           sizeof(gucMenuSelect),      gucMenuSelect       },
                                            {SI_STK_ENVELOPE_CALLCRTL,          sizeof(gucCallCtrl),        gucCallCtrl         },
                                            {SI_STK_ENVELOPE_SMSCRTL,           sizeof(gucMOSMSCtrl),       gucMOSMSCtrl        },
                                            {SI_STK_ENVELOPE_MMSTRANSTATUS,     sizeof(gucMMSTran),         gucMMSTran          },
                                            {SI_STK_ENVELOPE_MMSNOTIFY,         sizeof(gucMMSNotify),       gucMMSNotify        }
                                         };

SI_STK_TAGLIST_STRU gastEnvelopeDecodeList[2]
                                        = { {SI_STK_ENVELOPE_CALLCRTL,          sizeof(gucCallCtrlRsp),     gucCallCtrlRsp      },
                                            {SI_STK_ENVELOPE_SMSCRTL,           sizeof(gucMOSMSCtrlRsp),    gucMOSMSCtrlRsp     }
                                         };

/* STK 命令在　Profile 中的比特位对应关系 */
SI_STK_CMD_PROFILE_CFG_STRU gastSTKCmdProfileCfg[31] =
                                        {   {SI_STK_REFRESH             ,   23},
                                            {SI_STK_MORETIME            ,   19},
                                            {SI_STK_POLLINTERVAL        ,   21},
                                            {SI_STK_POLLINGOFF          ,   22},
                                            {SI_STK_SETUPEVENTLIST      ,   32},
                                            {SI_STK_SETUPCALL           ,   28},
                                            {SI_STK_SENDSS              ,   26},
                                            {SI_STK_SENDUSSD            ,   27},
                                            {SI_STK_SENDSMS             ,   25},
                                            {SI_STK_SENDDTMF            ,   65},
                                            {SI_STK_LAUNCHBROWSER       ,   70},
                                            {SI_STK_PLAYTONE            ,   20},
                                            {SI_STK_DISPLAYTET          ,   16},
                                            {SI_STK_GETINKEY            ,   17},
                                            {SI_STK_GETINPUT            ,   18},
                                            {SI_STK_SELECTITEM          ,   24},
                                            {SI_STK_SETUPMENU           ,   29},
                                            {SI_STK_SETUPIDLETEXT       ,   60},
                                            {SI_STK_PERFORMCARDAPDU     ,   50},
                                            {SI_STK_POWERONCARD         ,   48},
                                            {SI_STK_POWEROFFCARD        ,   49},
                                            {SI_STK_RUNATCOMMAND        ,   61},
                                            {SI_STK_LANGUAGENOTIFICATION,   69},
                                            {SI_STK_OPENCHANNEL         ,   88},
                                            {SI_STK_CLOSECHANNEL        ,   89},
                                            {SI_STK_RECEIVEDATA         ,   90},
                                            {SI_STK_SENDDATA            ,   91},
                                            {SI_STK_GETCHANNELSTATUS    ,   92},
                                            {SI_STK_SERVICESEARCH       ,   93},
                                            {SI_STK_GETSERVICEINFO      ,   94},
                                            {SI_STK_DECLARESERVICE      ,   95}};

/* STK 事件在　Profile 中的比特位对应关系 */
SI_STK_CMD_PROFILE_CFG_STRU gastSTKEventProfileCfg[15] =
                                        {   {SI_STK_EVENT_MT_CALL              ,    33},
                                            {SI_STK_EVENT_CALL_CONNECTED       ,    34},
                                            {SI_STK_EVENT_CALL_DISCONNECTED    ,    35},
                                            {SI_STK_EVENT_LOCATION_STATUS      ,    36},
                                            {SI_STK_EVENT_ACCESS_TECHN_CHANGE  ,    44},
                                            {SI_STK_EVENT_NET_SEARCHMODE_CHANGE,    47},
                                            {SI_STK_EVENT_NETWORK_REJECTION,        196}};


/*****************************************************************************
 全局变量名    : g_stStkSetupCallCtrl
 全局变量说明  : 当前呼叫状态控制结构
*****************************************************************************/
SI_STK_SETUP_CALL_CTRL_STRU     g_stStkSetupCallCtrl;

/*****************************************************************************
 全局变量名    : g_stLCEnableCfg
 全局变量说明  : L+C共SIM卡功能是否处于使能状态
*****************************************************************************/
TAF_NV_LC_CTRL_PARA_STRU                g_stLCEnableCfg;

/*****************************************************************************
 全局变量名    : g_stCbpEventList
 全局变量说明  : L+C共SIM卡功能保存EVENT LIST
*****************************************************************************/
SI_STK_CBP_SETUP_EVENT_LIST_STRU        g_stCbpEventList;

/*****************************************************************************
 全局变量名    : g_stStkCardInfo
 全局变量说明  : STK模块保存卡信息
*****************************************************************************/
SI_STK_CARDINFO_STRU                    g_stStkCardInfo;

/*****************************************************************************
 全局变量名    : g_stSTKAttRefreshCmd
 全局变量说明  : STK模块保存Refresh命令信息
*****************************************************************************/
VOS_BOOL                                g_bSTKAttResetFlag;


VOS_UINT8                               g_ucCsinCurcRptCfg = VOS_TRUE;

SI_STK_CALLSTATE_STRU                   g_stSTKCallState;

STK_FEATURE_CFG_STRU                    g_stSTKFeatureCnf;

/*****************************************************************************
函 数 名  : STK_CLCfgInit
功能描述  : L+C共SIM卡功能状态初始化
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年12月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_CLCfgInit(VOS_VOID)
{
    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA, &g_stLCEnableCfg, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        g_stLCEnableCfg.ucLCEnableFlg = VOS_FALSE;
        g_stLCEnableCfg.enRatCombined = TAF_NVIM_LC_RAT_COMBINED_GUL;
    }

    /*lint -e534*/
    VOS_MemSet(g_astEventResend, 0, sizeof(g_astEventResend));
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  : STK_ClearPauseCharGobal
功能描述  : SETUP CALL全局变量中呼叫状态机设置
输入参数  : enCallStatus:重置的呼叫状态
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_CallStateMachineSet(SI_STK_CALL_STATUS_ENUM_UINT32 enCallStatus)
{
    STK_NORMAL_LOG1("STK_CallStateMachineSet: enCallStatus set ", (VOS_UINT8)enCallStatus);

    g_stStkSetupCallCtrl.enCallStatus   =   enCallStatus;

    return;
}

/*****************************************************************************
函 数 名  : STK_ClearPauseCharGobal
功能描述  : 清除pause字符相关全局变量
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_ClearPauseCharGobal(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stSTKDtmfData, 0, sizeof(g_stSTKDtmfData));
    /*lint +e534*/

    STK_NORMAL_LOG("STK_ClearPauseCharGobal: Clearn DTMF DATA.");

    return;
}

/*****************************************************************************
函 数 名  : STK_SetCallCleanGobal
功能描述  : SETUP CALL全局变量清除
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_SetCallCleanGobal(VOS_VOID)
{
    STK_ClearPauseCharGobal();

    STK_CallStateMachineSet(SI_STK_CALL_STATUS_WAIT_IDLE);

    g_stStkSetupCallCtrl.ucSetupCallId = VOS_NULL;

	g_stStkSetupCallCtrl.ucRecallTime  = VOS_NULL;

    return;
}

/*****************************************************************************
函 数 名  : STK_InitCallGobal
功能描述  : 初时化与呼叫相关的全局变量的内容
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年9月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_InitCallGobal(VOS_VOID)
{
    VOS_UINT8                           i;

    /* NAS上报的呼叫ID从1到7 */
    for (i = 0; i < (STK_CALL_MAX_NUM); i++)
    {
        g_stStkSetupCallCtrl.astStkCallStatusTable[i].callId    =   i + 1;
        g_stStkSetupCallCtrl.astStkCallStatusTable[i].enStatus  =   SI_STK_CALL_ID_STATUS_IDLE;
    }

    g_stStkSetupCallCtrl.enCallStatus                           =   SI_STK_CALL_STATUS_WAIT_IDLE;

	g_stStkSetupCallCtrl.ucRecallTime							=	VOS_NULL;

    return;
}


/*****************************************************************************
函 数 名  : STK_GetCsSvcStatus
功能描述  : 获取当前CS域服务状态
输入参数  : 无
输出参数  : 无
返 回 值  : CS域服务状态
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 STK_GetCsSvcStatus(VOS_VOID)
{
    if (MODEM_ID_BUTT  == g_enSTKCurCSModem)
    {
        return SI_STK_NO_SERVICE;
    }

    return g_stStkSysInfo.enCsServiceStatus;
}

/*****************************************************************************
函 数 名  : STK_GetSvcStatus
功能描述  : 获取当前服务状态
输入参数  : 无
输出参数  : 无
返 回 值  : 服务状态
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 STK_GetSvcStatus(VOS_VOID)
{
    return g_stStkSysInfo.enServiceStatus;
}

/*****************************************************************************
函 数 名  : STK_UpdateCsSvcStatus
功能描述  : 更新当前CS域服务状态
输入参数  : enCsServiceStatus:CS域服务状态
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_UpdateCsSvcStatus(NAS_STK_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus)
{
    /* 无服务状态处理，无服务时把其它所有的系统信息全部清除 */
    if ((NAS_STK_SERVICE_STATUS_NO_SERVICE == enCsServiceStatus)
     || (NAS_STK_SERVICE_STATUS_DEEP_SLEEP == enCsServiceStatus))
    {
        g_stStkSysInfo.enCsServiceStatus = SI_STK_NO_SERVICE;

        return;
    }
    /* 正常服务 */
    else if (NAS_STK_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
    {
        g_stStkSysInfo.enCsServiceStatus = SI_STK_NORMAL_SERVICE;
    }
    /* 限制服务 */
    else
    {
        g_stStkSysInfo.enCsServiceStatus = SI_STK_LIMITED_SERVICE;
    }

    return;
}

/*****************************************************************************
函 数 名  : STK_UpdateSvcStatus
功能描述  : 更新当前服务状态
输入参数  : enCsServiceStatus:服务状态
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2014年01月15日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_UpdateSvcStatus(NAS_STK_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus)
{
    NAS_STK_SYS_INFO_STRU               stSysInfo;

    /* 无服务状态处理，无服务时把其它所有的系统信息全部清除 */
    if ((NAS_STK_SERVICE_STATUS_NO_SERVICE == enCsServiceStatus)
     || (NAS_STK_SERVICE_STATUS_DEEP_SLEEP == enCsServiceStatus))
    {
        /*lint -e534*/
        VOS_MemSet(&stSysInfo, (VOS_CHAR)0xFF, sizeof(NAS_STK_SYS_INFO_STRU));
        /*lint +e534*/

        g_stStkSysInfo.enServiceStatus = SI_STK_NO_SERVICE;

        STK_INFO_LOG("STK_UpdateSvcStatus: SI_STK_NO_SERVICE, Clear All Info");

        STK_UpdateSysInfo(&stSysInfo);

        return;
    }
    /* 正常服务 */
    else if (NAS_STK_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
    {
        g_stStkSysInfo.enServiceStatus = SI_STK_NORMAL_SERVICE;

        STK_INFO_LOG("STK_UpdateSvcStatus: SI_STK_NORMAL_SERVICE");
    }
    /* 限制服务 */
    else
    {
        g_stStkSysInfo.enServiceStatus = SI_STK_LIMITED_SERVICE;

        STK_INFO_LOG("STK_UpdateSvcStatus: SI_STK_LIMITED_SERVICE");
    }

    return;
}

/*****************************************************************************
函 数 名  : STK_GetSysInfo
功能描述  : 获取当前系统状态
输入参数  : 无
输出参数  : pstSysInfo:CS域系统信息
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_GetSysInfo(SI_STK_SYS_INFO_STRU *pstSysInfo)
{
    pstSysInfo->ulCellId        = g_stStkSysInfo.stSysInfo.ulCellId;
    pstSysInfo->usLac           = g_stStkSysInfo.stSysInfo.usLac;
    pstSysInfo->enSrchMode      = g_stStkSysInfo.stSysInfo.enSrchMode;
    pstSysInfo->enCurRat        = g_stStkSysInfo.stSysInfo.enCurRat;
    pstSysInfo->stCurPlmnId.Mcc = g_stStkSysInfo.stSysInfo.stCurPlmnId.Mcc;
    pstSysInfo->stCurPlmnId.Mnc = g_stStkSysInfo.stSysInfo.stCurPlmnId.Mnc;
    pstSysInfo->enUtranMode     = g_stStkSysInfo.stSysInfo.enUtranMode;

    return;
}

/*****************************************************************************
函 数 名  : STK_UpdateSysInfo
功能描述  : 更新当前系统状态，需要将NAS的服务状态接入技术等设置为STK的定义
输入参数  : pstSysInfo:CS域系统信息
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_UpdateSysInfo(NAS_STK_SYS_INFO_STRU *pstSysInfo)
{
    g_stStkSysInfo.stSysInfo.ulCellId        = pstSysInfo->ulCellId;
    g_stStkSysInfo.stSysInfo.usLac           = pstSysInfo->usLac;
    g_stStkSysInfo.stSysInfo.stCurPlmnId.Mcc = pstSysInfo->stPlmn.Mcc;
    g_stStkSysInfo.stSysInfo.stCurPlmnId.Mnc = pstSysInfo->stPlmn.Mnc;
    g_stStkSysInfo.stSysInfo.enUtranMode     = pstSysInfo->enUtranMode;

    STK_UpdateCurRat(pstSysInfo->enRat);

    return;
}

/*****************************************************************************
函 数 名  : STK_GetCurRat
功能描述  : 获取当前接入技术
输入参数  : 无
输出参数  : 无
返 回 值  : 接入技术
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT8 STK_GetCurRat(VOS_VOID)
{
    return g_stStkSysInfo.stSysInfo.enCurRat;
}

/*****************************************************************************
函 数 名  : STK_UpdateCurRat
功能描述  : 更新当前接入技术
输入参数  : enRat:当前接入技术
输出参数  : 无
返 回 值  : 接入技术
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_UpdateCurRat(TAF_MMA_RAT_TYPE_ENUM_UINT8 enRat)
{
    if (TAF_MMA_RAT_GSM == enRat)
    {
        g_stStkSysInfo.stSysInfo.enCurRat = STK_ACCESS_TECH_GSM;
    }
    else if (TAF_MMA_RAT_WCDMA == enRat)
    {
        g_stStkSysInfo.stSysInfo.enCurRat = STK_ACCESS_TECH_UTRAN;
    }
    else if (TAF_MMA_RAT_LTE == enRat)
    {
        g_stStkSysInfo.stSysInfo.enCurRat = STK_ACCESS_TECH_EUTRAN;
    }
    else
    {
        g_stStkSysInfo.stSysInfo.enCurRat = STK_ACCESS_TECH_BUTT;
    }

    return;
}

/*****************************************************************************
函 数 名  : STK_GetSearchMode
功能描述  : 获取当前搜网模式
输入参数  : 无
输出参数  : 无
返 回 值  : 搜网模式
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT8 STK_GetSearchMode(VOS_VOID)
{
    return g_stStkSysInfo.stSysInfo.enSrchMode;
}

/*****************************************************************************
函 数 名  : STK_UpdateSearchMode
功能描述  : 更新当前搜网模式
输入参数  : 当前搜网模式
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_UpdateSearchMode(VOS_UINT8 ucSearchMode)
{
    g_stStkSysInfo.stSysInfo.enSrchMode = ucSearchMode;

    return;
}

/*****************************************************************************
函 数 名  : STK_ProfileInit
功能描述  : 初始化时PROFILE内容初始化
输入参数  : 无
输出参数  : ppucProfile:Profile内容
            pucProfileLen:Profile长度
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_GetProfileInfo(VOS_UINT8 **ppucProfile, VOS_UINT8 *pucProfileLen)
{
    if (USIMM_PHYCARD_TYPE_UICC == g_stStkCardInfo.enPhyType)
    {
        if (VOS_NULL == g_stSTKProfileContent.stUsimProfile.ucProfileLen)
        {
            STK_ProfileInit(&g_stSTKProfileContent, g_stStkCardInfo.enPhyType);
        }

        *ppucProfile = g_stSTKProfileContent.stUsimProfile.aucProfile;
        *pucProfileLen = g_stSTKProfileContent.stUsimProfile.ucProfileLen;
    }
    else
    {
        if (VOS_NULL == g_stSTKProfileContent.stSimProfile.ucProfileLen)
        {
            STK_ProfileInit(&g_stSTKProfileContent, g_stStkCardInfo.enPhyType);
        }

        *ppucProfile = g_stSTKProfileContent.stSimProfile.aucProfile;
        *pucProfileLen = g_stSTKProfileContent.stSimProfile.ucProfileLen;
    }

    return;
}

/*****************************************************************************
函 数 名  : STK_ProfileInit
功能描述  : 初始化时PROFILE内容初始化
输入参数  : pstSTKProfileContent:Profile全局结构指针
            ucCardType:卡类型
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月11日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_ProfileInit(USIMM_STK_CFG_STRU *pstSTKProfileContent, USIMM_PHYCARD_TYPE_ENUM_UINT32 enPhyType)
{
    VOS_UINT8                           aucUsimProfile[]=STK_USIM_PROFILE_DEFAULT;
    VOS_UINT8                           aucSimProfile[]= {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xC0,
                                                          0xFF,0xFF,0xFF,0xF9,0xFF,0xF7,0xC0,0xFF,0xF0,0xFF};

    if (NV_OK == NV_Read(en_NV_Item_TerminalProfile_Set, pstSTKProfileContent, sizeof(USIMM_STK_CFG_STRU)))
    {
        return;
    }

    pstSTKProfileContent->ucTimer       = STK_POROTECT_TIME_LEN;    /*定时器长度的单位是秒*/
    pstSTKProfileContent->ucFuncEnable  = TAF_TRUE;

    if (USIMM_PHYCARD_TYPE_UICC == enPhyType)
    {
        /*lint -e534*/
        VOS_MemCpy(pstSTKProfileContent->stUsimProfile.aucProfile, aucUsimProfile, sizeof(aucUsimProfile));
        /*lint +e534*/

        pstSTKProfileContent->stUsimProfile.ucProfileLen = sizeof(aucUsimProfile);
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(pstSTKProfileContent->stSimProfile.aucProfile, aucSimProfile, sizeof(aucSimProfile));
        /*lint +e534*/

        pstSTKProfileContent->stSimProfile.ucProfileLen = sizeof(aucSimProfile);
    }

    return;
}

/*****************************************************************************
函 数 名  : STK_ResetGlobalValue
功能描述  : 卡复位需要清除全局变量的内容
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月20日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_ResetGlobalValue(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&gstUsatCmdDecode, 0, sizeof(gstUsatCmdDecode));

    VOS_MemSet(&gstSetUpMenuData, 0, sizeof(gstSetUpMenuData));

    VOS_MemSet(&g_stSTKDtmfData, 0, sizeof(g_stSTKDtmfData));

    VOS_MemSet(&g_stStkSysInfo, (VOS_CHAR)0xFF, sizeof(g_stStkSysInfo));

    VOS_MemSet(&g_stSTKEventState, 0, sizeof(g_stSTKEventState));

    VOS_MemSet(&g_stCbpEventList, 0, sizeof(g_stCbpEventList));

    VOS_MemSet(&g_stSTKCallState, 0, sizeof(g_stSTKCallState));
    /*lint +e534*/

    g_bSTKAttResetFlag = VOS_FALSE;

    g_stStkSysInfo.enServiceStatus = SI_STK_NO_SERVICE;

    g_stStkSysInfo.enCsServiceStatus = SI_STK_NO_SERVICE;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*lint -e534*/
    VOS_MemSet(&g_stStkCdmaSysInfo, 0, sizeof(g_stStkCdmaSysInfo));
    /*lint +e534*/

    g_stStkCdmaSysInfo.enServiceStatus = SI_STK_NO_SERVICE;
#endif

    STK_CLCfgInit();

    STK_InitCallGobal();

    if (VOS_TRUE == USIMM_IsSvlte())
    {
        g_enSTKCurCSModem = MODEM_ID_BUTT;
    }
    else
    {
#if defined (INSTANCE_1)
        g_enSTKCurCSModem = MODEM_ID_1;
#elif defined (INSTANCE_2)
        g_enSTKCurCSModem = MODEM_ID_2;
#else
        g_enSTKCurCSModem = MODEM_ID_0;
#endif  /*end of defined (INSTANCE_1)*/
    }

    return;
}

/*****************************************************************************
函 数 名  : STK_InitGobal
功能描述  : 初时化全局变量的内容
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月20日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID STK_InitGobal(VOS_VOID)
{
    VOS_UINT16                          usDualIMSIFlag = VOS_FALSE;
    VOS_UINT16                          usSmsIndFlag   = VOS_FALSE;
    NVIM_PRIVATE_CMD_STATUS_RPT_STRU    stNvimCmdRptCtrl;

    /*lint -e534*/
    VOS_MemSet(gstSTKTimer, 0, sizeof(gstSTKTimer));

    VOS_MemSet(&gstSTKCtrlStru, 0, sizeof(gstSTKCtrlStru));

    VOS_MemSet(&g_stSTKProfileContent, 0, sizeof(g_stSTKProfileContent));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    g_pstStkSendXsmsBuff = VOS_NULL_PTR;

    g_pstStkRcvXsmsBuff = VOS_NULL_PTR;
#endif
    /*lint +e534*/

    if(VOS_OK != VOS_SmCreate( "STK1",1,VOS_SEMA4_FIFO,&gulSTKApiSmId))/*创建api访问信号量*/
    {
        return;
    }

    if(NV_OK != NV_Read(en_NV_Item_Stk_DualImsi_Ctrl, &gstSTKIMSIMatch, sizeof(SI_STK_IMSICHG_MATCH_STRU)))
    {
        STK_WARNING_LOG("STK_InitGobal: Read en_NV_Item_TerminalProfile_Set Fail");
    }

    gstSTKIMSIMatch.usDualIMSIEnable = VOS_FALSE;

    if ( NV_OK != NV_Read(en_NV_Item_NV_HUAWEI_DOUBLE_IMSI_CFG_I, &usDualIMSIFlag, sizeof(VOS_UINT16)) )
    {
        STK_WARNING_LOG("STK_InitGobal: Read en_NV_Item_NV_HUAWEI_DOUBLE_IMSI_CFG_I Fail");
    }

    /* 前后两个自节均为1，Dual IMSI功能才开启，第一个字节为NV激活标志，第二个为使能位 */
    if ( STK_NV_ENABLED == usDualIMSIFlag )
    {
        gstSTKIMSIMatch.usDualIMSIEnable = VOS_TRUE;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Stk_SmsInd_Ctrl, &usSmsIndFlag, sizeof(VOS_UINT16)) )
    {
        STK_WARNING_LOG("STK_InitGobal: Read en_NV_Item_Stk_SmsInd_Ctrl Fail");
    }

    /* 前后两个自节均为1，SMS上报功能才开启，第一个字节为NV激活标志，第二个为使能位 */
    if ( STK_NV_ENABLED == usSmsIndFlag )
    {
        gusSTKSMSIndEnable = VOS_TRUE;
    }

    if(VOS_FALSE == SI_STK_CheckSupportAP())    /*对接非AP才会申请内存*/
    {
        g_pucSTKSndCodeAddr = (VOS_UINT8 *)VOS_MemAlloc(MAPS_STK_PID, STATIC_MEM_PT, STK_PRINT_MAX_LEN);
    }

    if ( NV_OK != NV_Read(en_NV_Item_PRIVATE_CMD_STATUS_RPT, &stNvimCmdRptCtrl, sizeof(NVIM_PRIVATE_CMD_STATUS_RPT_STRU)) )
    {
        STK_WARNING_LOG("STK_InitGobal: Read en_NV_Item_PRIVATE_CMD_STATUS_RPT Fail");
    }
    else
    {
        if(VOS_TRUE == stNvimCmdRptCtrl.ucStatus)
        {
           g_ucCsinCurcRptCfg = stNvimCmdRptCtrl.ucStatusRptGeneralControl;
        }
    }

    /* NV项读取失败按所有定制都不支持处理 */
    if(VOS_OK != NV_Read(en_NV_Item_STK_Support_Feature_Cfg,
                         (VOS_VOID*)&g_stSTKFeatureCnf, 
                         sizeof(g_stSTKFeatureCnf)))
    {
        /*lint -e534*/
        VOS_MemSet(g_stSTKFeatureCnf.unCfg.aulValue , VOS_FALSE, sizeof(g_stSTKFeatureCnf.unCfg.aulValue));
        /*lint +e534*/
    }

    STK_ResetGlobalValue();

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

