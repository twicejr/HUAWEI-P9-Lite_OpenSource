/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmBase.c
  Author       : zhuli 00100318
  Version      : V100R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---全局变量定义模块实现
  Function List:
  History      :
 ************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
#include "UsimmApi.h"
#include "usimmapdu.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        PS_FILE_ID_USIMM_GLOBAL_C

/*当前的快速开机状态*/
VOS_UINT32                          gulUSIMMOpenSpeed     = 0;

/*当前卡的基本信息*/
USIMM_BASE_INFO_ST                  gstUSIMMBaseInfo;

/* 卡应用信息 */
USIMM_COMM_CARD_APP_INFO_STRU       g_astUSIMMCardAppInfo[USIMM_CHANNEL_NUMBER_MAX];

/* 维护卡中PIN1码信息 */
USIMM_APP_PIN_INFO_STRU             g_astUSIMMAppPIN1Info[USIMM_KEY_REF_PIN_BUTT];

/* 测试卡类型 */
USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 g_enTestCardType;

/* 标记USIM是否支持IMS */
VOS_UINT32                          gulUsimSupportIMS = VOS_FALSE;

USIMM_ISIMUSIM_EFTBL_STRU           g_astUSIMMIsimUsimEFTBL[USIMM_ISIMEFTOUSIMEF_TBL_SIZE] ={
                                               {USIMM_ISIM_EFAD_ID,       USIMM_USIM_EFAD_ID        },
                                               {USIMM_ISIM_EFGBAP_ID,     USIMM_USIM_EFGBAP_ID      },
                                               {USIMM_ISIM_EFGBANL_ID,    USIMM_USIM_EFGBANL_ID     },
                                               {USIMM_ISIM_EFNAFKCA_ID,   USIMM_USIM_EFNAFKCA_ID    },
                                               {USIMM_ISIM_EFUICCIARI_ID, USIMM_USIM_EFUICCIARI_ID  }};

/*底软相关的基本信息*/
USIMM_DRV_INFO_ST                   gstUSIMMDrvInfo;

/*AID信息*/
USIMM_AID_INFO_STRU                 g_astUSIMMInitAIDInfo[USIMM_CARDAPP_BUTT];

/*当前的APDU命令的内容*/
USIMM_APDU_ST                       gstUSIMMAPDU = {0};

/*当前链路层的状态*/
USIMMDL_CONTROL_ST                  gstUSIMMDLControl;

/*文件缓存定义*/
USIMM_POOL_ST                       gstUSIMMPOOL;

/*保存Log信息的控制变量*/
USIMM_LOG_DATA_STRU                 g_stUSIMMLogData;

VOS_UINT32                          g_ulUSIMMExcLogLenBK;

USIMM_LOG_DATA_STRU                 g_stUSIMMExcLogData;

/* 保存逻辑通道上GetResponse信息 */
USIMM_CHANNEL_RESPONSE_STRU         g_astUSIMMChGetRsp[USIMM_CHANNEL_NUMBER_MAX];

USIMM_CARD_INIT_INFO_LOG_STRU       g_stUSIMMInitInfo;

/* 指示支持T=1还是T=0 */
USIMM_DL_T_MODE_ENUM_UINT32         g_enUSIMMTMode = USIMM_DL_T_MODE_T0;

/* T=1相关参数备份，用于卡复位场景后恢复相关的T=1上下文 */
USIMM_DL_T1_PARA_STRU               g_stUSIMMT1Para;

/* 指示是否发送了IFS REQ */
VOS_BOOL                            g_bSendIFSReqFlag = VOS_FALSE;

#if(FEATURE_ON == FEATURE_PTM)
USIMM_MNTN_STATE_ERROR_EVENT_STRU   g_stCardErrorLog;

NV_ID_ERR_LOG_CTRL_INFO_STRU        g_stErrLogCtrlInfo;
#endif

USIMM_STORE_ESN_MEID_STATUS_STRU    g_stStoreEsnMeidStatus;

#if (FEATURE_VSIM == FEATURE_ON)
VOS_UINT8                          *g_pucUSIMMVsimData = VOS_NULL_PTR;
#endif

/*****************************************************************************
 全局变量名    : g_ulUsimmFeatureCfg
 全局变量说明  : USIMM模块定制特性全局控制变量
 1.日    期   : 2012年06月19日
   作    者   : H59254
   修改内容   : 新建
*****************************************************************************/
USIMM_FEATURE_CFG_STRU              g_stUsimmFeatureCfg;

VOS_UINT32                          g_ulATTSpecErrSWCnt;    /* ATT特殊处理的SW计数 */

/*初始化第一步时候读取的不受PIN保护的文件ID*/
VOS_UINT16 gausInitFileOne[USIMM_INITFIRST_FILENUM]   = {USIMM_ICCID_ID,USIMM_PL_ID};

/* 如果有新增加的OP文件读取，需要在下面的表里增加对应的服务。如果不确定或者在6F38找不到对应的服务的就写USIM_SVR_NONE */
/*SIM卡需要初始化读取缓存的Optional文件ID*/
USIMM_OPFILE_LIST_STRU gastSimInitOFile[USIMM_INITSIM_OFILENUM] = {\
    {USIMM_GSM_EFCSP_ID,        (VOS_UINT32)UICC_SVR_NONE},
    {USIMM_GSM_EFKCGPRS_ID,     (VOS_UINT32)SIM_SVR_GPRS},
    {USIMM_GSM_EFLOCIGPRS_ID,   (VOS_UINT32)SIM_SVR_GPRS},
    {USIMM_GSM_EFPLMNWACT_ID,   (VOS_UINT32)SIM_SVR_USER_CTRL_PLMN},
    {USIMM_GSM_EFOPLMNWACT_ID,  (VOS_UINT32)SIM_SVR_OPERATOR_CTRL_PLMN},
    {USIMM_GSM_EFHPLMNACT_ID,   (VOS_UINT32)SIM_SVR_HPLMN},
    {USIMM_GSM_EFCBMI_ID,       (VOS_UINT32)SIM_SVR_CBMID},
    {USIMM_GSM_EFCBMID_ID,      (VOS_UINT32)SIM_SVR_DD_VIA_SMS_CB},
    {USIMM_GSM_EFCBMIR_ID,      (VOS_UINT32)SIM_SVR_CBMIR},
    {USIMM_GSM_EFSPN_ID,        (VOS_UINT32)SIM_SVR_SERVICE_PRO_NAME},
    {USIMM_GSM_EFGID1_ID,       (VOS_UINT32)SIM_SVR_GIDL1},
    {USIMM_GSM_EFPLMNSEL_ID,    (VOS_UINT32)SIM_SVR_PLMN_SELECTOR}};

/*USIM卡需要初始化读取缓存的Optional文件ID*/
USIMM_OPFILE_LIST_STRU gastUsimInitOFile[USIMM_INITUSIM_OFILENUM] = {\
    {USIMM_USIM_EFPLMNWACT_ID,  (VOS_UINT32)USIM_SVR_UPLMN_SEL_WACT},
    {USIMM_USIM_EFOPLMNWACT_ID, (VOS_UINT32)USIM_SVR_OPLMN_SEL_WACT},
    {USIMM_USIM_EFHPLMNwACT_ID, (VOS_UINT32)USIM_SVR_HPLMN_WACT},
    {USIMM_USIM_EFSPN_ID,       (VOS_UINT32)USIM_SVR_SPN},
    {USIMM_USIM_EFGID1_ID,      (VOS_UINT32)USIM_SVR_GID1},
    {USIMM_USIM_EFEHPLMN_ID,    (VOS_UINT32)USIM_SVR_EHPLMN},
    {USIMM_USIM_EFMUK_ID,       (VOS_UINT32)USIM_SVR_EHPLMN_IND},
    {USIMM_USIM_EFLRPLMNSI_ID,  (VOS_UINT32)USIM_SVR_RPLMN_LACT},
    {USIMM_USIM_EFEST_ID,       (VOS_UINT32)UICC_SVR_NONE},
    {USIMM_USIM_EFCBMI_ID,      (VOS_UINT32)USIM_SVR_CBMI},
    {USIMM_USIM_EFCBMID_ID,     (VOS_UINT32)USIM_SVR_DATA_DL_SMSCB},
    {USIMM_USIM_EFCBMIR_ID,     (VOS_UINT32)USIM_SVR_CBMIR},
    {USIMM_USIM_EFKC_ID,        (VOS_UINT32)USIM_SVR_GSM_ACCESS_IN_USIM},
    {USIMM_USIM_EFKCGPRS_ID,    (VOS_UINT32)USIM_SVR_GSM_ACCESS_IN_USIM}};

/* ATT USIM卡需要初始化的文件列表 */
USIMM_DEF_FILEID_ENUM_UINT32 g_aulAttUsimInitFile[USIMM_USIM_ATT_INITFILE_NUM]={USIMM_ATTUSIM_EFACTINGHPLMN_ID,
                                                              USIMM_ATTUSIM_EFRATMODE_ID};

/* ATT SIM卡需要初始化的文件列表 */
USIMM_DEF_FILEID_ENUM_UINT32 g_aulAttSimInitFile [USIMM_SIM_ATT_INITFILE_NUM]={USIMM_ATTGSM_EFACTINGHPLMN_ID};

/*SIM INS字节检查*/
/* 0x90, 0x00 */
VOS_UINT8 g_aucSim9000Ins[] = { CMD_INS_STATUS,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_READ_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_SLEEP,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_GET_RESPONSE,
                                CMD_INS_END};

/* 0x91, 0xFF */
VOS_UINT8 g_aucSim91XXIns[] = { CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_GET_RESPONSE,
                                CMD_INS_END};

/* 0x93, 0x00 */
VOS_UINT8 g_aucSim9300Ins[] = { CMD_INS_ENVELOPE,
                                CMD_INS_END};

/* 0x9E, 0xFF */
VOS_UINT8 g_aucSim9EXXIns[] = { CMD_INS_ENVELOPE,
                                CMD_INS_END};

/* 0x9F, 0xFF */
VOS_UINT8 g_aucSim9FFFIns[] = { CMD_INS_SELECT,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_END};

/* 0x92, 0x40 */
VOS_UINT8 g_aucSim9240Ins[] = { CMD_INS_SELECT,
                                CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_GET_RESPONSE,
                                CMD_INS_END};

/* 0x92, 0xFF */
VOS_UINT8 g_aucSim92FFIns[] = { CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_END};

/* 0x94, 0x00 */
VOS_UINT8 g_aucSim9400Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_END};

/* 0x94, 0x02 */
VOS_UINT8 g_aucSim9402Ins[] = { CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_END};

/* 0x94, 0x04 */
VOS_UINT8 g_aucSim9404Ins[] = { CMD_INS_SELECT,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_END};

/* 0x94, 0x08 */
VOS_UINT8 g_aucSim9408Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

/* 0x98, 0x02 */
VOS_UINT8 g_aucSim9802Ins[] = { CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

/* 0x98, 0x04 */
VOS_UINT8 g_aucSim9804Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

/* 0x98, 0x08 */
VOS_UINT8 g_aucSim9808Ins[] = { CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

/* 0x98, 0x10 */
VOS_UINT8 g_aucSim9810Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_END};

/* 0x98, 0x40 */
VOS_UINT8 g_aucSim9840Ins[] = { CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

/* 0x98, 0x50 */
VOS_UINT8 g_aucSim9850Ins[] = { CMD_INS_INCREASE,
                                CMD_INS_END};
/* 0x67, 0x00    0x67, 0xFF    0x6B, 0xFF    0x6E, 0xFF    0x6F, 0x00    0x6F, 0xFF */
VOS_UINT8 g_aucSimSwAnyIns[] = {CMD_INS_ANY};

/*USIM INS字节检查*/
/*0x90,0x00  0x61,0xFF  0x91,0xFF  0x62,0xFF  0x63,0xFF  0x64,0x00  0x67,0x00  0x67,0xFF  0x68,0x00  0x68,0x81  0x68,0x82  0x6A,0x81  0x6A,0x86  0x6B,0x00  0x6C,0xFF  0x6E,0x00  0x6F,0x00  0x6F,0xFF*/
VOS_UINT8 g_aucUsimSwAnyIns[] = {CMD_INS_ANY};

    /* 0x93, 0x00 */
VOS_UINT8 g_aucUsim9300Ins[] = {CMD_INS_ENVELOPE,
                                CMD_INS_END};

    /* 0x98, 0x50 */
VOS_UINT8 g_aucUsim9850Ins[] = {CMD_INS_INCREASE,
                                CMD_INS_END};

    /* 0x98, 0x62 */
VOS_UINT8 g_aucUsim9862Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

    /* 0x62, 0x00 */
VOS_UINT8 g_aucUsim6200Ins[] = {CMD_INS_SELECT,
                                CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_GET_CHALLENGE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_TERMINAL_CAPABILITY,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x62, 0x81 */
VOS_UINT8 g_aucUsim6281Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_END};

    /* 0x62, 0x82 */
VOS_UINT8 g_aucUsim6282Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_END};

    /* 0x62, 0x83 */
VOS_UINT8 g_aucUsim6283Ins[] = {CMD_INS_SELECT,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_END};

    /* 0x62, 0x85 */
VOS_UINT8 g_aucUsim9285Ins[] = {CMD_INS_SELECT,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_END};

    /* 0x62, 0xF1 */
VOS_UINT8 g_aucUsim62F1Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x62, 0xF2 */
VOS_UINT8 g_aucUsim62F2Ins[] = {CMD_INS_RETRIEVE_DATA,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x62, 0xF3 */
VOS_UINT8 g_aucUsim62F3Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

    /* 0x63, 0xC0 */
VOS_UINT8 g_aucUsim63CxIns[] = {CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

    /* 0x63,0xF1 */
VOS_UINT8 g_aucUsim63F1Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x63, 0xF2 */
VOS_UINT8 g_aucUsim63F2Ins[] = {CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x65, 0x00 */
VOS_UINT8 g_aucUsim6500Ins[] = {CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_END};

    /* 0x65, 0x81 */
VOS_UINT8 g_aucUsim6581Ins[] = {CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_END};

    /* 0x69, 0x00 */
VOS_UINT8 g_aucUsim6900Ins[] = {CMD_INS_SELECT,
                                CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_GET_CHALLENGE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x69, 0x81 */
VOS_UINT8 g_aucUsim6981Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x82 */
VOS_UINT8 g_aucUsim6982Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x83 */
VOS_UINT8 g_aucUsim6983Ins[] = {CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

    /* 0x69, 0x84 */
VOS_UINT8 g_aucUsim6984Ins[] ={CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x85 */
VOS_UINT8 g_aucUsim6985Ins[] = {CMD_INS_SELECT,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x69, 0x86 */
VOS_UINT8 g_aucUsim6986Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x89 */
VOS_UINT8 g_aucUsim6989Ins[] = {CMD_INS_SELECT,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_GET_CHALLENGE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_TERMINAL_CAPABILITY,
                                CMD_INS_END};

    /* 0x6A, 0x80 */
VOS_UINT8 g_aucUsim6A80Ins[] = {CMD_INS_SEARCH_RECORD,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_TERMINAL_CAPABILITY,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x6A, 0x82 */
VOS_UINT8 g_aucUsim6A82Ins[] = {CMD_INS_SELECT,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x6A, 0x83 */
VOS_UINT8 g_aucUsim6A83Ins[] = {CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_END};

    /* 0x6A, 0x84 */
VOS_UINT8 g_aucUsim6A84Ins[] = {CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x6A, 0x87 */
VOS_UINT8 g_aucUsim6A87Ins[] = {CMD_INS_SELECT,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_END};

/* 0x6A, 0x88 */
VOS_UINT8 g_aucUsim6A88Ins[] = {CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_END};

    /* 0x98, 0x63 */
VOS_UINT8 g_aucUsim9863Ins[] = {CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

/*Sim SW字节检查*/
USIMM_SWCHECK_ST gausSimSWCheck[USIMM_SIMSW_MAXNUMBER] =
                            {
                                {0x90, 0x00, USIMM_SW_OK,              },
                                {0x91, 0xFF, USIMM_SW_OK_WITH_SAT,     },
                                {0x93, 0x00, USIMM_SW_CARD_BUSY,       },
                                {0x9E, 0xFF, USIMM_SW_WARNING,         },
                                {0x9F, 0xFF, USIMM_SW_OK_WITH_RESOPNSE,},
                                {0x92, 0x40, USIMM_SW_MEMORY_ERROR,    },
                                {0x92, 0xFF, USIMM_SW_OK,              },
                                {0x94, 0x00, USIMM_SW_NOFILE_SELECT,   },
                                {0x94, 0x02, USIMM_SW_OUTOF_RANGE,     },
                                {0x94, 0x04, USIMM_SW_NOFILE_FOUND,    },
                                {0x94, 0x08, USIMM_SW_FILETYPE_ERROR,  },
                                {0x98, 0x02, USIMM_SW_SECURITY_ERROR,  },
                                {0x98, 0x04, USIMM_SW_SECURITY_ERROR,  },
                                {0x98, 0x08, USIMM_SW_PINSTATUS_ERROR, },
                                {0x98, 0x10, USIMM_SW_FILESTATUS_ERROR,},
                                {0x98, 0x40, USIMM_SW_PIN_BLOCK,       },
                                {0x98, 0x50, USIMM_SW_INCREACE_ERROR,  },
                                {0x67, 0x00, USIMM_SW_CMD_ERROR,       },
                                {0x67, 0xFF, USIMM_SW_P3_ERROR,        },
                                {0x6B, 0xFF, USIMM_SW_CMD_ERROR,       },
                                {0x6E, 0xFF, USIMM_SW_CLA_ERROR,       },
                                {0x6F, 0x00, USIMM_SW_TECH_ERROR,      },
                                {0x6F, 0xFF, USIMM_SW_OTHER_ERROR      },
                                {0x98, 0x34, USIMM_SW_CDMA_AUTN_ERROR  },
                            };

/*Usim SW字节检查*/
USIMM_SWCHECK_ST gausUsimSWCheck[USIMM_USIMSW_MAXNUMBER] =
                            {
                                {0x90, 0x00, USIMM_SW_OK,                },
                                {0x61, 0xFF, USIMM_SW_OK_WITH_RESOPNSE,  },
                                {0x91, 0xFF, USIMM_SW_OK_WITH_SAT,       },
                                {0x93, 0x00, USIMM_SW_CARD_BUSY,         },
                                {0x98, 0x50, USIMM_SW_INCREACE_ERROR,    },
                                {0x98, 0x62, USIMM_SW_AUTN_ERROR ,       },
                                {0x62, 0xFF, USIMM_SW_WARNING,           },
                                {0x63, 0xC0, USIMM_SW_OK,                },
                                {0x63, 0xFF, USIMM_SW_WARNING,           },
                                {0x64, 0x00, USIMM_SW_MEMORY_ERROR,      },
                                {0x65, 0x00, USIMM_SW_MEMORY_ERROR,      },
                                {0x65, 0x81, USIMM_SW_MEMORY_ERROR,      },
                                {0x67, 0x00, USIMM_SW_CMD_ERROR,         },
                                {0x67, 0xFF, USIMM_SW_P3_ERROR,          },
                                {0x68, 0x00, USIMM_SW_CLA_ERROR,         },
                                {0x68, 0x81, USIMM_SW_CHANNEL_NOSUPPORT, },
                                {0x68, 0x82, USIMM_SW_SECURITY_ERROR,    },
                                {0x69, 0x00, USIMM_SW_OTHER_ERROR,       },
                                {0x69, 0x81, USIMM_SW_FILETYPE_ERROR,    },
                                {0x69, 0x82, USIMM_SW_SECURITY_ERROR,    },
                                {0x69, 0x83, USIMM_SW_PIN_BLOCK,         },
                                {0x69, 0x84, USIMM_SW_PINNUMBER_ERROR,   },
                                {0x69, 0x85, USIMM_SW_FILESTATUS_ERROR,  },
                                {0x69, 0x86, USIMM_SW_NOFILE_SELECT,     },
                                {0x69, 0x89, USIMM_SW_COMMAND_ERROR,     },
                                {0x6A, 0x80, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x81, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x82, USIMM_SW_NOFILE_FOUND,      },
                                {0x6A, 0x83, USIMM_SW_NORECORD_FOUND,    },
                                {0x6A, 0x84, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x86, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x87, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x88, USIMM_SW_CMD_ERROR,         },
                                {0x6B, 0x00, USIMM_SW_CMD_ERROR,         },
                                {0x6C, 0xFF, USIMM_SW_P3_ERROR,          },
                                {0x6E, 0x00, USIMM_SW_CLA_ERROR,         },
                                {0x6F, 0x00, USIMM_SW_TECH_ERROR,        },
                                {0x6F, 0xFF, USIMM_SW_OTHER_ERROR        },
                                {0x98, 0x63, USIMM_SW_EXPIRED_ERROR      },
                                {0x98, 0x34, USIMM_SW_CDMA_AUTN_ERROR    },
                            };

/* ISIM服务状态位对应到USIM UST上的索引 */

/*lint -e656*/
const VOS_UINT8 g_aucServIsimToUsim[] =
/*lint +e656*/
                            {
                                0,                  /* ISIM_SVR_PCSCF_ADDR */
                                USIM_SVR_GBA,       /* ISIM_SVR_GBA */
                                0,                  /* ISIM_SVR_HTTP_DIGEST */
                                USIM_SVR_GBAKEY_EM, /* ISIM_SVR_LOCAL_GBA */
                                0,                  /* ISIM_SVR_IMS_PCSCF */
                                USIM_SVR_SMS,       /* ISIM_SVR_SMS */
                                USIM_SVR_SMSR,      /* ISIM_SVR_SMSR */
                                0,                  /* ISIM_SVR_SOI */
                                USIM_SVR_CTRL_IMS,  /* ISIM_SVR_COMM_CTRL */
                                USIM_SVR_ACCESS_IMS /* ISIM_SVR_UICC_IMS */
                            };

USIMM_FILEID_PATHSTR_TABLE_STRU g_stUSIMMFilePathTable[USIMM_DEF_FILEID_BUTT] =
{
    {USIMM_UNLIMIT_AUTO,         USIMM_MF_STR               },            /*USIMM_MF_ID               */
    {USIMM_UNLIMIT_AUTO,         USIMM_DIR_STR              },            /*USIMM_DIR_ID              */
    {USIMM_UNLIMIT_AUTO,         USIMM_ICCID_STR            },            /*USIMM_ICCID_ID            */
    {USIMM_UNLIMIT_AUTO,         USIMM_PL_STR               },            /*USIMM_PL_ID               */
    {USIMM_UNLIMIT_AUTO,         USIMM_ARR_STR              },            /*USIMM_ARR_ID              */
    {USIMM_GUTL_APP,             USIMM_USIM_STR             },            /*USIMM_USIM_ID             */
    {USIMM_GUTL_APP,             USIMM_USIM_EFLI_STR        },            /*USIMM_USIM_EFLI_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFARR_STR       },            /*USIMM_USIM_EFARR_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFIMSI_STR      },            /*USIMM_USIM_EFIMSI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFKEYS_STR      },            /*USIMM_USIM_EFKEYS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFKEYSPS_STR    },            /*USIMM_USIM_EFKEYSPS_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFDCK_STR       },            /*USIMM_USIM_EFDCK_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHPPLMN_STR    },            /*USIMM_USIM_EFHPPLMN_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCNL_STR       },            /*USIMM_USIM_EFCNL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACMMAX_STR    },            /*USIMM_USIM_EFACMMAX_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUST_STR       },            /*USIMM_USIM_EFUST_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACM_STR       },            /*USIMM_USIM_EFACM_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFFDN_STR       },            /*USIMM_USIM_EFFDN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMS_STR       },            /*USIMM_USIM_EFSMS_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGID1_STR      },            /*USIMM_USIM_EFGID1_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGID2_STR      },            /*USIMM_USIM_EFGID2_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMSISDN_STR    },            /*USIMM_USIM_EFMSISDN_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPUCT_STR      },            /*USIMM_USIM_EFPUCT_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMSP_STR      },            /*USIMM_USIM_EFSMSP_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMSS_STR      },            /*USIMM_USIM_EFSMSS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCBMI_STR      },            /*USIMM_USIM_EFCBMI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSPN_STR       },            /*USIMM_USIM_EFSPN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMSR_STR      },            /*USIMM_USIM_EFSMSR_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCBMID_STR     },            /*USIMM_USIM_EFCBMID_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSDN_STR       },            /*USIMM_USIM_EFSDN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT2_STR      },            /*USIMM_USIM_EFEXT2_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT3_STR      },            /*USIMM_USIM_EFEXT3_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFBDN_STR       },            /*USIMM_USIM_EFBDN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT5_STR      },            /*USIMM_USIM_EFEXT5_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCCP2_STR      },            /*USIMM_USIM_EFCCP2_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCBMIR_STR     },            /*USIMM_USIM_EFCBMIR_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT4_STR      },            /*USIMM_USIM_EFEXT4_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEST_STR       },            /*USIMM_USIM_EFEST_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACL_STR       },            /*USIMM_USIM_EFACL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCMI_STR       },            /*USIMM_USIM_EFCMI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSTART_HFN_STR },            /*USIMM_USIM_EFSTART_HFN_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFTHRESHOL_STR  },            /*USIMM_USIM_EFTHRESHOL_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPLMNWACT_STR  },            /*USIMM_USIM_EFPLMNWACT_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOPLMNWACT_STR },            /*USIMM_USIM_EFOPLMNWACT_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHPLMNwACT_STR },            /*USIMM_USIM_EFHPLMNwACT_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPSLOCI_STR    },            /*USIMM_USIM_EFPSLOCI_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACC_STR       },            /*USIMM_USIM_EFACC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFFPLMN_STR     },            /*USIMM_USIM_EFFPLMN_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFLOCI_STR      },            /*USIMM_USIM_EFLOCI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFICI_STR       },            /*USIMM_USIM_EFICI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCI_STR       },            /*USIMM_USIM_EFOCI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFICT_STR       },            /*USIMM_USIM_EFICT_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCT_STR       },            /*USIMM_USIM_EFOCT_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFAD_STR        },            /*USIMM_USIM_EFAD_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVGCS_STR      },            /*USIMM_USIM_EFVGCS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVGCSS_STR     },            /*USIMM_USIM_EFVGCSS_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVBS_STR       },            /*USIMM_USIM_EFVBS_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVBSS_STR      },            /*USIMM_USIM_EFVBSS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEMLPP_STR     },            /*USIMM_USIM_EFEMLPP_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFAAEM_STR      },            /*USIMM_USIM_EFAAEM_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFECC_STR       },            /*USIMM_USIM_EFECC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHIDDENKEY_STR },            /*USIMM_USIM_EFHIDDENKEY_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNETPAR_STR    },            /*USIMM_USIM_EFNETPAR_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPNN_STR       },            /*USIMM_USIM_EFPNN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOPL_STR       },            /*USIMM_USIM_EFOPL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMBDN_STR      },            /*USIMM_USIM_EFMBDN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT6_STR      },            /*USIMM_USIM_EFEXT6_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMBI_STR       },            /*USIMM_USIM_EFMBI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMWIS_STR      },            /*USIMM_USIM_EFMWIS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCFIS_STR      },            /*USIMM_USIM_EFCFIS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT7_STR      },            /*USIMM_USIM_EFEXT7_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSPDI_STR      },            /*USIMM_USIM_EFSPDI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSN_STR      },            /*USIMM_USIM_EFMMSN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT8_STR      },            /*USIMM_USIM_EFEXT8_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSICP_STR    },            /*USIMM_USIM_EFMMSICP_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSUP_STR     },            /*USIMM_USIM_EFMMSUP_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSUCP_STR    },            /*USIMM_USIM_EFMMSUCP_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNIA_STR       },            /*USIMM_USIM_EFNIA_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVGCSCA_STR    },            /*USIMM_USIM_EFVGCSCA_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVBSCA_STR     },            /*USIMM_USIM_EFVBSCA_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGBAP_STR      },            /*USIMM_USIM_EFGBAP_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMSK_STR       },            /*USIMM_USIM_EFMSK_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMUK_STR       },            /*USIMM_USIM_EFMUK_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEHPLMN_STR    },            /*USIMM_USIM_EFEHPLMN_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGBANL_STR     },            /*USIMM_USIM_EFGBANL_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEHPLMNPI_STR  },            /*USIMM_USIM_EFEHPLMNPI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFLRPLMNSI_STR  },            /*USIMM_USIM_EFLRPLMNSI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNAFKCA_STR    },            /*USIMM_USIM_EFNAFKCA_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSPNI_STR      },            /*USIMM_USIM_EFSPNI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPNNI_STR      },            /*USIMM_USIM_EFPNNI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNCPIP_STR     },            /*USIMM_USIM_EFNCPIP_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEPSLOCI_STR   },            /*USIMM_USIM_EFEPSLOCI_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEPSNSC_STR    },            /*USIMM_USIM_EFEPSNSC_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUFC_STR       },            /*USIMM_USIM_EFUFC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUICCIARI_STR  },            /*USIMM_USIM_EFUICCIARI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNASCONFIG_STR },            /*USIMM_USIM_EFNASCONFIG_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPWS_STR       },            /*USIMM_USIM_EFPWS_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_DFPHONEBOOK_STR },            /*USIMM_USIM_DFPHONEBOOK_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPSC_STR       },            /*USIMM_USIM_EFPSC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCC_STR        },            /*USIMM_USIM_EFCC_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPUID_STR      },            /*USIMM_USIM_EFPUID_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPBR_STR       },            /*USIMM_USIM_EFPBR_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_DFGSM_ACCESS_STR},            /*USIMM_USIM_DFGSM_ACCESS_ID*/
    {USIMM_GUTL_APP,             USIMM_USIM_EFKC_STR        },            /*USIMM_USIM_EFKC_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFKCGPRS_STR    },            /*USIMM_USIM_EFKCGPRS_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCPBCCH_STR    },            /*USIMM_USIM_EFCPBCCH_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFINVSCAN_STR   },            /*USIMM_USIM_EFINVSCAN_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_DFMEXE_STR      },            /*USIMM_USIM_DFMEXE_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMexE_ST_STR   },            /*USIMM_USIM_EFMexE_ST_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_EFORPK_STR      },            /*USIMM_USIM_EFORPK_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFARPK_STR      },            /*USIMM_USIM_EFARPK_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFTPRK_STR      },            /*USIMM_USIM_EFTPRK_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_DFSOLSA_STR     },            /*USIMM_USIM_DFSOLSA_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSAI_STR       },            /*USIMM_USIM_EFSAI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSLL_STR       },            /*USIMM_USIM_EFSLL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_DFWLAN_STR      },            /*USIMM_USIM_DFWLAN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPSEUDO_STR    },            /*USIMM_USIM_EFPSEUDO_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUPLMNWLAN_STR },            /*USIMM_USIM_EFUPLMNWLAN_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EF0PLMNWLAN_STR },            /*USIMM_USIM_EF0PLMNWLAN_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUWSIDL_STR    },            /*USIMM_USIM_EFUWSIDL_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOWSIDL_STR    },            /*USIMM_USIM_EFOWSIDL_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWRI_STR       },            /*USIMM_USIM_EFWRI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHWSIDL_STR    },            /*USIMM_USIM_EFHWSIDL_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWEHPLMNPI_STR },            /*USIMM_USIM_EFWEHPLMNPI_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWHPI_STR      },            /*USIMM_USIM_EFWHPI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWLRPLMN_STR   },            /*USIMM_USIM_EFWLRPLMN_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHPLMNDAI_STR  },            /*USIMM_USIM_EFHPLMNDAI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_DFHNB_STR       },            /*USIMM_USIM_DFHNB_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACSGL_STR     },            /*USIMM_USIM_EFACSGL_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCSGT_STR      },            /*USIMM_USIM_EFCSGT_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHNBN_STR      },            /*USIMM_USIM_EFHNBN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCSGL_STR     },            /*USIMM_USIM_EFOCSGL_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCSGT_STR     },            /*USIMM_USIM_EFOCSGT_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOHNBN_STR     },            /*USIMM_USIM_EFOHNBN_ID     */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_STR             },            /*USIMM_TELE_ID             */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFADN_STR       },            /*USIMM_TELE_EFADN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFFDN_STR       },            /*USIMM_TELE_EFFDN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMS_STR       },            /*USIMM_TELE_EFSMS_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFCCP_STR       },            /*USIMM_TELE_EFCCP_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMSISDN_STR    },            /*USIMM_TELE_EFMSISDN_ID    */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMSP_STR      },            /*USIMM_TELE_EFSMSP_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMSS_STR      },            /*USIMM_TELE_EFSMSS_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFLND_STR       },            /*USIMM_TELE_EFLND_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMSR_STR      },            /*USIMM_TELE_EFSMSR_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSDN_STR       },            /*USIMM_TELE_EFSDN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT1_STR      },            /*USIMM_TELE_EFEXT1_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT2_STR      },            /*USIMM_TELE_EFEXT2_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT3_STR      },            /*USIMM_TELE_EFEXT3_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFBDN_STR       },            /*USIMM_TELE_EFBDN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT4_STR      },            /*USIMM_TELE_EFEXT4_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFECCP_STR      },            /*USIMM_TELE_EFECCP_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFRMA_STR       },            /*USIMM_TELE_EFRMA_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSUME_STR      },            /*USIMM_TELE_EFSUME_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFICE_DN_STR    },            /*USIMM_TELE_EFICE_DN_ID    */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFICE_FF_STR    },            /*USIMM_TELE_EFICE_FF_ID    */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFPSISMSC_STR   },            /*USIMM_TELE_EFPSISMSC_ID   */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_STR      },            /*USIMM_TELE_DFGRAP_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_EFIMG_STR},            /*USIMM_TELE_DFGRAP_EFIMG_ID*/
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_EFICEGRAPH_STR},       /*USIMM_TELE_DFGRAP_EFICEGRA*/
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_EFLAUNCHSCWS_STR},     /*USIMM_TELE_DFGRAP_EFLUNCH */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_STR        },            /*USIMM_TELE_DFPB_ID        */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFPSC_STR  },            /*USIMM_TELE_DFPB_EFPSC_ID  */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFCC_STR   },            /*USIMM_TELE_DFPB_EFCC_ID   */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFPUID_STR },            /*USIMM_TELE_DFPB_EFPUID_ID */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFPBR_STR  },            /*USIMM_TELE_DFPB_EFPBR_ID  */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMM_STR        },            /*USIMM_TELE_DFMM_ID        */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMM_EFMML_STR  },            /*USIMM_TELE_DFMM_EFMML_ID  */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMUM_EFMMDF_STR},            /*USIMM_TELE_DFMUM_EFMMDF_ID*/
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMSS_STR       },            /*USIMM_TELE_DFMSS_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMLPL_STR      },            /*USIMM_TELE_EFMLPL_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMSPL_STR      },            /*USIMM_TELE_EFMSPL_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMMSSMODE_STR  },            /*USIMM_TELE_EFMMSSMODE_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_STR             },            /*USIMM_CSIM_ID             */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCOUNT_STR     },            /*USIMM_CSIM_EFCOUNT_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFIMSIM_STR     },            /*USIMM_CSIM_EFIMSIM_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFIMSIT_STR     },            /*USIMM_CSIM_EFIMSIT_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFTMSI_STR      },            /*USIMM_CSIM_EFTMSI_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAH_STR        },            /*USIMM_CSIM_EFAH_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAOP_STR       },            /*USIMM_CSIM_EFAOP_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFALOC_STR      },            /*USIMM_CSIM_EFALOC_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCDMAHOME_STR  },            /*USIMM_CSIM_EFCDMAHOME_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFZNREGI_STR    },            /*USIMM_CSIM_EFZNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSNREGI_STR    },            /*USIMM_CSIM_EFSNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFDISTREGI_STR  },            /*USIMM_CSIM_EFDISTREGI_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFACCOLC_STR    },            /*USIMM_CSIM_EFACCOLC_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFTERM_STR      },            /*USIMM_CSIM_EFTERM_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSSCI_STR      },            /*USIMM_CSIM_EFSSCI_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFACP_STR       },            /*USIMM_CSIM_EFACP_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPRL_STR       },            /*USIMM_CSIM_EFPRL_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFRUIMID_STR    },            /*USIMM_CSIM_EFRUIMID_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCSIMST_STR    },            /*USIMM_CSIM_EFCSIMST_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPC_STR       },            /*USIMM_CSIM_EFSPC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFOTAPASPC_STR  },            /*USIMM_CSIM_EFOTAPASPC_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFNAMLOCK_STR   },            /*USIMM_CSIM_EFNAMLOCK_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFOTA_STR       },            /*USIMM_CSIM_EFOTA_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSP_STR        },            /*USIMM_CSIM_EFSP_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFESNMEID_STR   },            /*USIMM_CSIM_EFESNMEID_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFLI_STR        },            /*USIMM_CSIM_EFLI_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFFDN_STR       },            /*USIMM_CSIM_EFFDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMS_STR       },            /*USIMM_CSIM_EFSMS_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMSP_STR      },            /*USIMM_CSIM_EFSMSP_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMSS_STR      },            /*USIMM_CSIM_EFSMSS_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSSFC_STR      },            /*USIMM_CSIM_EFSSFC_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPN_STR       },            /*USIMM_CSIM_EFSPN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFUSGIND_STR    },            /*USIMM_CSIM_EFUSGIND_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAD_STR        },            /*USIMM_CSIM_EFAD_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMDN_STR       },            /*USIMM_CSIM_EFMDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMAXPRL_STR    },            /*USIMM_CSIM_EFMAXPRL_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPCS_STR      },            /*USIMM_CSIM_EFSPCS_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFECC_STR       },            /*USIMM_CSIM_EFECC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFME3GPDOPC_STR },            /*USIMM_CSIM_EFME3GPDOPC_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EF3GPDOPM_STR   },            /*USIMM_CSIM_EF3GPDOPM_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPCAP_STR    },            /*USIMM_CSIM_EFSIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPCAP_STR    },            /*USIMM_CSIM_EFMIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPUPP_STR    },            /*USIMM_CSIM_EFSIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPUPP_STR    },            /*USIMM_CSIM_EFMIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPSP_STR     },            /*USIMM_CSIM_EFSIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPSP_STR     },            /*USIMM_CSIM_EFMIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPPAPSS_STR  },            /*USIMM_CSIM_EFSIPPAPSS_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPUZL_STR      },            /*USIMM_CSIM_EFPUZL_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMAXPUZL_STR   },            /*USIMM_CSIM_EFMAXPUZL_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMECRP_STR     },            /*USIMM_CSIM_EFMECRP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHRPDCAP_STR   },            /*USIMM_CSIM_EFHRPDCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHRPDUPP_STR   },            /*USIMM_CSIM_EFHRPDUPP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCSSPR_STR     },            /*USIMM_CSIM_EFCSSPR_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFATC_STR       },            /*USIMM_CSIM_EFATC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEPRL_STR      },            /*USIMM_CSIM_EFEPRL_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSCFG_STR  },            /*USIMM_CSIM_EFBCSMSCFG_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSPREF_STR },            /*USIMM_CSIM_EFBCSMSPREF_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSTABLE_STR},            /*USIMM_CSIM_EFBCSMSTABLE_ID*/
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSP_STR    },            /*USIMM_CSIM_EFBCSMSP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBAKPARA_STR   },            /*USIMM_CSIM_EFBAKPARA_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFUPBAKPARA_STR },            /*USIMM_CSIM_EFUPBAKPARA_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSN_STR      },            /*USIMM_CSIM_EFMMSN_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT8_STR      },            /*USIMM_CSIM_EFEXT8_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSICP_STR    },            /*USIMM_CSIM_EFMMSICP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSUP_STR     },            /*USIMM_CSIM_EFMMSUP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSUCP_STR    },            /*USIMM_CSIM_EFMMSUCP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAUTHCAP_STR   },            /*USIMM_CSIM_EFAUTHCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EF3GCIK_STR     },            /*USIMM_CSIM_EF3GCIK_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFDCK_STR       },            /*USIMM_CSIM_EFDCK_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFGID1_STR      },            /*USIMM_CSIM_EFGID1_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFGID2_STR      },            /*USIMM_CSIM_EFGID2_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCDMACNL_STR   },            /*USIMM_CSIM_EFCDMACNL_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHOMETAG_STR   },            /*USIMM_CSIM_EFHOMETAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFGROUPTAG_STR  },            /*USIMM_CSIM_EFGROUPTAG_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPECTAG_STR   },            /*USIMM_CSIM_EFSPECTAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCALLPROMPT_STR},            /*USIMM_CSIM_EFCALLPROMPT_ID*/
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSFEUIMID_STR  },            /*USIMM_CSIM_EFSFEUIMID_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEST_STR       },            /*USIMM_CSIM_EFEST_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHIDDENKEY_STR },            /*USIMM_CSIM_EFHIDDENKEY_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFLCSVER_STR    },            /*USIMM_CSIM_EFLCSVER_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFLCSCP_STR     },            /*USIMM_CSIM_EFLCSCP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSDN_STR       },            /*USIMM_CSIM_EFSDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT2_STR      },            /*USIMM_CSIM_EFEXT2_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT3_STR      },            /*USIMM_CSIM_EFEXT3_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFICI_STR       },            /*USIMM_CSIM_EFICI_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFOCI_STR       },            /*USIMM_CSIM_EFOCI_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT5_STR      },            /*USIMM_CSIM_EFEXT5_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCCP2_STR      },            /*USIMM_CSIM_EFCCP2_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAPPLAB_STR    },            /*USIMM_CSIM_EFAPPLAB_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMODEL_STR     },            /*USIMM_CSIM_EFMODEL_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFRC_STR        },            /*USIMM_CSIM_EFRC_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMSCAP_STR    },            /*USIMM_CSIM_EFSMSCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPFLAGS_STR  },            /*USIMM_CSIM_EFMIPFLAGS_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EF3GPDUPPEXT_STR},            /*USIMM_CSIM_EF3GPDUPPEXT_ID*/
    {USIMM_CDMA_APP,             USIMM_CSIM_EFIPV6CAP_STR   },            /*USIMM_CSIM_EFIPV6CAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFTCPCFG_STR    },            /*USIMM_CSIM_EFTCPCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFDGC_STR       },            /*USIMM_CSIM_EFDGC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFWAPBWCP_STR   },            /*USIMM_CSIM_EFWAPBWCP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFWAPBWBM_STR   },            /*USIMM_CSIM_EFWAPBWBM_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSCFG_STR    },            /*USIMM_CSIM_EFMMSCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFJDL_STR       },            /*USIMM_CSIM_EFJDL_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_DFPHONEBOOK_STR },            /*USIMM_CSIM_DFPHONEBOOK_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPSC_STR       },            /*USIMM_CSIM_EFPSC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCC_STR        },            /*USIMM_CSIM_EFCC_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPUID_STR      },            /*USIMM_CSIM_EFPUID_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPBR_STR       },            /*USIMM_CSIM_EFPBR_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_STR              },            /*USIMM_GSM_ID              */
    {USIMM_GUTL_APP,             USIMM_GSM_EFLP_STR         },            /*USIMM_GSM_EFLP_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFIMSI_STR       },            /*USIMM_GSM_EFIMSI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFKC_STR         },            /*USIMM_GSM_EFKC_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFDCK_STR        },            /*USIMM_GSM_EFDCK_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPLMNSEL_STR    },            /*USIMM_GSM_EFPLMNSEL_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_EFHPLMN_STR      },            /*USIMM_GSM_EFHPLMN_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCNL_STR        },            /*USIMM_GSM_EFCNL_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFACMMAX_STR     },            /*USIMM_GSM_EFACMMAX_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSST_STR        },            /*USIMM_GSM_EFSST_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFACM_STR        },            /*USIMM_GSM_EFACM_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFGID1_STR       },            /*USIMM_GSM_EFGID1_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFGID2_STR       },            /*USIMM_GSM_EFGID2_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPUCT_STR       },            /*USIMM_GSM_EFPUCT_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCBMI_STR       },            /*USIMM_GSM_EFCBMI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSPN_STR        },            /*USIMM_GSM_EFSPN_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCBMID_STR      },            /*USIMM_GSM_EFCBMID_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFBCCH_STR       },            /*USIMM_GSM_EFBCCH_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFACC_STR        },            /*USIMM_GSM_EFACC_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFFPLMN_STR      },            /*USIMM_GSM_EFFPLMN_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFLOCI_STR       },            /*USIMM_GSM_EFLOCI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFAD_STR         },            /*USIMM_GSM_EFAD_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPHASE_STR      },            /*USIMM_GSM_EFPHASE_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVGCS_STR       },            /*USIMM_GSM_EFVGCS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVGCSS_STR      },            /*USIMM_GSM_EFVGCSS_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVBS_STR        },            /*USIMM_GSM_EFVBS_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVBSS_STR       },            /*USIMM_GSM_EFVBSS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEMLPP_STR      },            /*USIMM_GSM_EFEMLPP_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFAAEM_STR       },            /*USIMM_GSM_EFAAEM_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFECC_STR        },            /*USIMM_GSM_EFECC_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCBMIR_STR      },            /*USIMM_GSM_EFCBMIR_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFNIA_STR        },            /*USIMM_GSM_EFNIA_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFKCGPRS_STR     },            /*USIMM_GSM_EFKCGPRS_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFLOCIGPRS_STR   },            /*USIMM_GSM_EFLOCIGPRS_ID   */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSUME_STR       },            /*USIMM_GSM_EFSUME_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCMI_STR        },            /*USIMM_GSM_EFCMI_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPLMNWACT_STR   },            /*USIMM_GSM_EFPLMNWACT_ID   */
    {USIMM_GUTL_APP,             USIMM_GSM_EFOPLMNWACT_STR  },            /*USIMM_GSM_EFOPLMNWACT_ID  */
    {USIMM_GUTL_APP,             USIMM_GSM_EFHPLMNACT_STR   },            /*USIMM_GSM_EFHPLMNACT_ID   */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCPBCCH_STR     },            /*USIMM_GSM_EFCPBCCH_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFINVSCAN_STR    },            /*USIMM_GSM_EFINVSCAN_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPNN_STR        },            /*USIMM_GSM_EFPNN_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFOPL_STR        },            /*USIMM_GSM_EFOPL_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMBDN_STR       },            /*USIMM_GSM_EFMBDN_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEXT6_STR       },            /*USIMM_GSM_EFEXT6_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMBI_STR        },            /*USIMM_GSM_EFMBI_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMWIS_STR       },            /*USIMM_GSM_EFMWIS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCFIS_STR       },            /*USIMM_GSM_EFCFIS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEXT7_STR       },            /*USIMM_GSM_EFEXT7_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSPDI_STR       },            /*USIMM_GSM_EFSPDI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSN_STR       },            /*USIMM_GSM_EFMMSN_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEXT8_STR       },            /*USIMM_GSM_EFEXT8_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSICP_STR     },            /*USIMM_GSM_EFMMSICP_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSUP_STR      },            /*USIMM_GSM_EFMMSUP_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSUCP_STR     },            /*USIMM_GSM_EFMMSUCP_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVMW_STR        },            /*USIMM_GSM_EFVMW_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSVCSTBL_STR    },            /*USIMM_GSM_EFSVCSTBL_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCFF_STR        },            /*USIMM_GSM_EFCFF_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFONS_STR        },            /*USIMM_GSM_EFONS_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCSP_STR        },            /*USIMM_GSM_EFCSP_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCPHSI_STR      },            /*USIMM_GSM_EFCPHSI_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMN_STR         },            /*USIMM_GSM_EFMN_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFONSS_STR       },            /*USIMM_GSM_EFONSS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFINFONUM_STR    },            /*USIMM_GSM_EFINFONUM_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_DFSOLSA_STR      },            /*USIMM_GSM_DFSOLSA_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_DFSOLSA_EFSAI_STR},            /*USIMM_GSM_DFSOLSA_EFSAI_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFSOLSA_EFSLL_STR},            /*USIMM_GSM_DFSOLSA_EFSLL_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_STR       },            /*USIMM_GSM_DFMEXE_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFST_STR  },            /*USIMM_GSM_DFMEXE_EFST_ID  */
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFORPK_STR},            /*USIMM_GSM_DFMEXE_EFORPK_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFARPK_STR},            /*USIMM_GSM_DFMEXE_EFARPK_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFTPRPK_STR},           /*USIMM_GSM_DFMEXE_EFTPRPK_I*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_STR           },            /*USIMM_ATTGSM_ID           */
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFTERMINALTBL_STR},         /*USIMM_ATTGSM_EFTERMINALTBL*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFACTINGHPLMN_STR},         /*USIMM_ATTGSM_EFACTINGHPLMN*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMENABLE_STR},           /*USIMM_ATTGSM_EFPRMENABLE_I*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMPARA_STR },            /*USIMM_ATTGSM_EFPRMPARA_ID */
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMOMCLR_STR},            /*USIMM_ATTGSM_EFPRMOMCLR_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMOMC_STR  },            /*USIMM_ATTGSM_EFPRMOMC_ID  */
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMVERINFO_STR},          /*USIMM_ATTGSM_EFPRMVERINFO_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_STR          },            /*USIMM_ATTUSIM_ID          */
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFTERMINALTBL_STR},        /*USIMM_ATTUSIM_EFTERMINALTBL_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFACTINGHPLMN_STR},        /*USIMM_ATTUSIM_EFACTINGHPLM_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFRATMODE_STR},            /*USIMM_ATTUSIM_EFRATMODE_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMENABLE_STR},          /*USIMM_ATTUSIM_EFPRMENABLE_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMPARA_STR},            /*USIMM_ATTUSIM_EFPRMPARA_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMOMCLR_STR},           /*USIMM_ATTUSIM_EFPRMOMCLR_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMOMC_STR },            /*USIMM_ATTUSIM_EFPRMOMC_ID */
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMVERINFO_STR},         /*USIMM_ATTUSIM_EFPRMVERINFO_ID*/
    {USIMM_CDMA_APP,             USIMM_CDMA_STR             },            /*USIMM_CDMA_ID             */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCOUNT_STR     },            /*USIMM_CDMA_EFCOUNT_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMSIM_STR     },            /*USIMM_CDMA_EFIMSIM_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMSIT_STR     },            /*USIMM_CDMA_EFIMSIT_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFTMSI_STR      },            /*USIMM_CDMA_EFTMSI_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAH_STR        },            /*USIMM_CDMA_EFAH_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAOP_STR       },            /*USIMM_CDMA_EFAOP_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFALOC_STR      },            /*USIMM_CDMA_EFALOC_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCDMAHOME_STR  },            /*USIMM_CDMA_EFCDMAHOME_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFZNREGI_STR    },            /*USIMM_CDMA_EFZNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSNREGI_STR    },            /*USIMM_CDMA_EFSNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDISTREGI_STR  },            /*USIMM_CDMA_EFDISTREGI_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFACCOLC_STR    },            /*USIMM_CDMA_EFACCOLC_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFTERM_STR      },            /*USIMM_CDMA_EFTERM_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSSCI_STR      },            /*USIMM_CDMA_EFSSCI_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFACP_STR       },            /*USIMM_CDMA_EFACP_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFPRL_STR       },            /*USIMM_CDMA_EFPRL_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFRUIMID_STR    },            /*USIMM_CDMA_EFRUIMID_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCST_STR       },            /*USIMM_CDMA_EFCST_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPC_STR       },            /*USIMM_CDMA_EFSPC_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFOTAPASPC_STR  },            /*USIMM_CDMA_EFOTAPASPC_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFNAMLOCK_STR   },            /*USIMM_CDMA_EFNAMLOCK_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFOTA_STR       },            /*USIMM_CDMA_EFOTA_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSP_STR        },            /*USIMM_CDMA_EFSP_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFESNMEIDME_STR },            /*USIMM_CDMA_EFESNMEIDME_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFREVISION_STR  },            /*USIMM_CDMA_EFREVISION_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFRUIMPL_STR    },            /*USIMM_CDMA_EFRUIMPL_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMS_STR       },            /*USIMM_CDMA_EFSMS_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMSP_STR      },            /*USIMM_CDMA_EFSMSP_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMSS_STR      },            /*USIMM_CDMA_EFSMSS_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSSFC_STR      },            /*USIMM_CDMA_EFSSFC_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPN_STR       },            /*USIMM_CDMA_EFSPN_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFUSGIND_STR    },            /*USIMM_CDMA_EFUSGIND_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAD_STR        },            /*USIMM_CDMA_EFAD_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMDN_STR       },            /*USIMM_CDMA_EFMDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMAXPRL_STR    },            /*USIMM_CDMA_EFMAXPRL_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPCS_STR      },            /*USIMM_CDMA_EFSPCS_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFECC_STR       },            /*USIMM_CDMA_EFECC_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFME3GPDOPC_STR },            /*USIMM_CDMA_EFME3GPDOPC_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EF3GPDOPM_STR   },            /*USIMM_CDMA_EF3GPDOPM_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPCAP_STR    },            /*USIMM_CDMA_EFSIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPCAP_STR    },            /*USIMM_CDMA_EFMIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPUPP_STR    },            /*USIMM_CDMA_EFSIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPUPP_STR    },            /*USIMM_CDMA_EFMIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPSP_STR     },            /*USIMM_CDMA_EFSIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPSP_STR     },            /*USIMM_CDMA_EFMIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPPAPSS_STR  },            /*USIMM_CDMA_EFSIPPAPSS_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFPUZL_STR      },            /*USIMM_CDMA_EFPUZL_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMAXPUZL_STR   },            /*USIMM_CDMA_EFMAXPUZL_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMECRP_STR     },            /*USIMM_CDMA_EFMECRP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFHRPDCAP_STR   },            /*USIMM_CDMA_EFHRPDCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFHRPDUPP_STR   },            /*USIMM_CDMA_EFHRPDUPP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCSSPR_STR     },            /*USIMM_CDMA_EFCSSPR_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFACT_STR       },            /*USIMM_CDMA_EFACT_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFEPRL_STR      },            /*USIMM_CDMA_EFEPRL_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSOFG_STR  },            /*USIMM_CDMA_EFBCSMSOFG_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSPREF_STR },            /*USIMM_CDMA_EFBCSMSPREF_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSTBL_STR  },            /*USIMM_CDMA_EFBCSMSTBL_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSP_STR    },            /*USIMM_CDMA_EFBCSMSP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMPI_STR      },            /*USIMM_CDMA_EFIMPI_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDOMAIN_STR    },            /*USIMM_CDMA_EFDOMAIN_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMPU_STR      },            /*USIMM_CDMA_EFIMPU_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFPCSCF_STR     },            /*USIMM_CDMA_EFPCSCF_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBAKPARA_STR   },            /*USIMM_CDMA_EFBAKPARA_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFUPBAKPARA_STR },            /*USIMM_CDMA_EFUPBAKPARA_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSN_STR      },            /*USIMM_CDMA_EFMMSN_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFEXT8_STR      },            /*USIMM_CDMA_EFEXT8_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSICP_STR    },            /*USIMM_CDMA_EFMMSICP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSUP_STR     },            /*USIMM_CDMA_EFMMSUP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSUCP_STR    },            /*USIMM_CDMA_EFMMSUCP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAUTHCAP_STR   },            /*USIMM_CDMA_EFAUTHCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EF3GCIK_STR     },            /*USIMM_CDMA_EF3GCIK_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDCK_STR       },            /*USIMM_CDMA_EFDCK_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFGID1_STR      },            /*USIMM_CDMA_EFGID1_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFGID2_STR      },            /*USIMM_CDMA_EFGID2_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCDMACNL_STR   },            /*USIMM_CDMA_EFCDMACNL_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFHOMETAG_STR   },            /*USIMM_CDMA_EFHOMETAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFGROUPTAG_STR  },            /*USIMM_CDMA_EFGROUPTAG_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPECTAG_STR   },            /*USIMM_CDMA_EFSPECTAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCALLPROM_STR  },            /*USIMM_CDMA_EFCALLPROM_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSFEUIMID_STR  },            /*USIMM_CDMA_EFSFEUIMID_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMSCAP_STR    },            /*USIMM_CDMA_EFSMSCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIPV6CAP_STR   },            /*USIMM_CDMA_EFIPV6CAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPFLAG_STR   },            /*USIMM_CDMA_EFMIPFLAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFTCPCFG_STR    },            /*USIMM_CDMA_EFTCPCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDGC_STR       },            /*USIMM_CDMA_EFDGC_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFWAPBRCP_STR   },            /*USIMM_CDMA_EFWAPBRCP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFWAPBRBM_STR   },            /*USIMM_CDMA_EFWAPBRBM_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EF3GPDUPPEX_STR },            /*USIMM_CDMA_EF3GPDUPPEX_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSCFG_STR    },            /*USIMM_CDMA_EFMMSCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFJDL_STR       },            /*USIMM_CDMA_EFJDL_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMODEL_STR     },            /*USIMM_CDMA_EFMODEL_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFRC_STR        },            /*USIMM_CDMA_EFRC_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAPPLAB_STR    },            /*USIMM_CDMA_EFAPPLAB_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_STR             },            /*USIMM_ISIM_ID           */
    {USIMM_IMS_APP,              USIMM_ISIM_EFIST_STR       },            /*USIMM_ISIM_EFIST_ID     */
    {USIMM_IMS_APP,              USIMM_ISIM_EFIMPI_STR      },            /*USIMM_ISIM_EFIMPI_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFDOMAIN_STR    },            /*USIMM_ISIM_EFDOMAIN_ID  */
    {USIMM_IMS_APP,              USIMM_ISIM_EFIMPU_STR      },            /*USIMM_ISIM_EFIMPU_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFAD_STR        },            /*USIMM_ISIM_EFAD_ID      */
    {USIMM_IMS_APP,              USIMM_ISIM_EFARR_STR       },            /*USIMM_ISIM_EFARR_ID     */
    {USIMM_IMS_APP,              USIMM_ISIM_EFPCSCF_STR     },            /*USIMM_ISIM_EFPCSCF_ID   */
    {USIMM_IMS_APP,              USIMM_ISIM_EFGBAP_STR      },            /*USIMM_ISIM_EFGBAP_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFGBANL_STR     },            /*USIMM_ISIM_EFGBANL_ID   */
    {USIMM_IMS_APP,              USIMM_ISIM_EFNAFKCA_STR    },            /*USIMM_ISIM_EFNAFKCA_ID  */
    {USIMM_IMS_APP,              USIMM_ISIM_EFUICCIARI_STR  },            /*USIMM_ISIM_EFUICCIARI_ID*/
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMS_STR       },            /*USIMM_ISIM_EFSMS_ID     */
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMSS_STR      },            /*USIMM_ISIM_EFSMSS_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMSR_STR      },            /*USIMM_ISIM_EFSMSR_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMSP_STR      },            /*USIMM_ISIM_EFSMSP_ID    */
 };

/*****************************************************************************
函 数 名  :USIMM_CCB_SetTestCardType
功能描述  :设置测试卡类型
输入参数  :USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetTestCardType(USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 enTestCardType)
{
    g_enTestCardType = enTestCardType;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetTestCardType
功能描述  :获取测试卡类型
输入参数  :无
输出参数  :无
返 回 值  :USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 USIMM_CCB_GetTestCardType(VOS_VOID)
{
    return g_enTestCardType;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetCardType
功能描述  :设置卡类型
输入参数  :USIMM_PHYCARD_TYPE_ENUM_UINT32
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_ENUM_UINT32 enCardType)
{
    VOS_UINT32                          i;

    /* 确保在无卡模式下应用状态也变更 */
    if (USIMM_PHYCARD_TYPE_NOCARD == enCardType)
    {
        /*lint -e534*/
        VOS_MemSet(g_astUSIMMCardAppInfo, 0, sizeof(g_astUSIMMCardAppInfo));
        /*lint +e534*/

        for (i = 0; i < USIMM_CHANNEL_NUMBER_MAX; i++)
        {
            g_astUSIMMCardAppInfo[i].enAppType     = USIMM_UNLIMIT_APP_BUTT;
        }

        gstUSIMMBaseInfo.enStateChange = USIMM_CARD_STATE_CHANGED;
    }

    gstUSIMMBaseInfo.enCardType = enCardType;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetCardType
功能描述  :获取当前的卡类型
输入参数  :无
输出参数  :无
返 回 值  :USIMM_PHYCARD_TYPE_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_PHYCARD_TYPE_ENUM_UINT32 USIMM_CCB_GetCardType(VOS_VOID)
{
    return gstUSIMMBaseInfo.enCardType;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetCardVersion
功能描述  :设置卡类型
输入参数  :USIMM_PHYCARD_TYPE_ENUM_UINT32
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetCardVersion(USIMM_PHYCARD_TYPE_ENUM_UINT32 enCardVersion)
{
    gstUSIMMBaseInfo.enCardVersion = enCardVersion;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetCardType
功能描述  :获取当前的卡类型
输入参数  :无
输出参数  :无
返 回 值  :USIMM_PHYCARD_TYPE_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_PHYCARD_TYPE_ENUM_UINT32 USIMM_CCB_GetCardVersion(VOS_VOID)
{
    return gstUSIMMBaseInfo.enCardVersion;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetMainAppType
功能描述  :设置主应用类型
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetMainAppType(USIMM_CARDAPP_ENUM_UINT32 enMainAppType)
{
    gstUSIMMBaseInfo.enMainAppType = enMainAppType;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetMainAppType
功能描述  :返回主应用类型
输入参数  :无
输出参数  :无
返 回 值  :USIMM_CARDAPP_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_CARDAPP_ENUM_UINT32 USIMM_CCB_GetMainAppType(VOS_VOID)
{
    if (USIMM_PHYCARD_TYPE_NOCARD == USIMM_CCB_GetCardType())
    {
        return USIMM_CARDAPP_BUTT;
    }

    return gstUSIMMBaseInfo.enMainAppType;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetAppService
功能描述  :设置卡服务类型
输入参数  :USIMM_CARDAPP_ENUM_UINT32
           USIMM_CARD_SERVIC_ENUM_UINT32
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetAppService(USIMM_CARDAPP_ENUM_UINT32 enAppType, USIMM_CARD_SERVIC_ENUM_UINT32 enAppService)
{
    VOS_UINT8                           ucChannelNo;

    if ((USIMM_UNLIMIT_APP_BUTT <= enAppType)
     || (USIMM_CARD_SERVIC_BUTT <= enAppService))
    {
        return;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_SetAppService:USIMM_CCB_GetAppChNO Error");

        return;
    }

    g_astUSIMMCardAppInfo[ucChannelNo].enAppService = enAppService;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAppService
功能描述  :获取卡服务类型
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_CARD_SERVIC_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_CARD_SERVIC_ENUM_UINT32 USIMM_CCB_GetAppService(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;

    if (USIMM_UNLIMIT_APP_BUTT <= enAppType)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetAppService:Input Error");

        return USIMM_CARD_SERVIC_ABSENT;
    }

    enCardType = USIMM_CCB_GetCardType();
    if (USIMM_PHYCARD_TYPE_NOCARD == enCardType)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetAppService: Card Type Error");

        return USIMM_CARD_SERVIC_ABSENT;
    }

    /* 假如为模拟ISIM则返回USIM卡的结果 */
    if ((VOS_TRUE == USIMM_CCB_GetUsimSimulateIsimStatus())
     && (USIMM_IMS_APP == enAppType))
    {
        enAppType = USIMM_GUTL_APP;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetAppService:USIMM_CCB_GetAppChNO Error");

        return USIMM_CARD_SERVIC_ABSENT;
    }

    return g_astUSIMMCardAppInfo[ucChannelNo].enAppService;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetAppStateChange
功能描述  :设置卡状态改变
输入参数  :USIMM_CARDAPP_ENUM_UINT32
           USIMM_CARD_STATE_CHANGE_ENUM_UINT32
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetAppStateChange(USIMM_CARDAPP_ENUM_UINT32 enAppType, USIMM_CARD_STATE_CHANGE_ENUM_UINT32 enStateChange)
{
    if ((USIMM_CARDAPP_BUTT           <= enAppType)
     || (USIMM_CARD_STATE_CHANGE_BUTT <= enStateChange))
    {
        return;
    }

    gstUSIMMBaseInfo.enStateChange = enStateChange;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAppStateChange
功能描述  :获取卡改变状态
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_CARD_STATE_CHANGE_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_CARD_STATE_CHANGE_ENUM_UINT32 USIMM_CCB_GetAppStateChange(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        return USIMM_CARD_STATE_NOCHANGE;
    }

    return gstUSIMMBaseInfo.enStateChange;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetCurFileInfo
功能描述  :获得应用的当前文件信息
输入参数  :enAppType
输出参数  :无
返 回 值  :USIMM_CURFILEINFO_ST*

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_CURFILEINFO_ST* USIMM_CCB_GetCurFileInfo(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    if (USIMM_UNLIMIT_APP_BUTT <= enAppType)
    {
        return VOS_NULL_PTR;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetCurFileInfo: USIMM_CCB_GetAppChNO Error");

        return VOS_NULL_PTR;
    }

    return &g_astUSIMMCardAppInfo[ucChannelNo].stCurFileInfo;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetCurEFInfo
功能描述  :获得应用的当前EF文件信息
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_EFFCP_ST*

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_EFFCP_ST* USIMM_CCB_GetCurEFInfo(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    if (USIMM_UNLIMIT_APP_BUTT <= enAppType)
    {
        return VOS_NULL_PTR;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetCurEFInfo: USIMM_CCB_GetAppChNO Error");

        return VOS_NULL_PTR;
    }

    return &g_astUSIMMCardAppInfo[ucChannelNo].stCurFileInfo.stEFInfo;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetCurDFInfo
功能描述  :获得应用的当前DF文件信息
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_DFFCP_ST*

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_DFFCP_ST* USIMM_CCB_GetCurDFInfo(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    if (USIMM_UNLIMIT_APP_BUTT <= enAppType)
    {
        return VOS_NULL_PTR;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetCurDFInfo: USIMM_CCB_GetAppChNO Error");

        return VOS_NULL_PTR;
    }

    return &g_astUSIMMCardAppInfo[ucChannelNo].stCurFileInfo.stDFInfo;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAdfInfo
功能描述  :获得应用的ADF信息
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_UICC_ADF_INFO_STRU*

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_UICC_ADF_INFO_STRU* USIMM_CCB_GetAdfInfoByCH(VOS_UINT8 ucChannelNo)
{
    if (USIMM_CHANNEL_NUMBER_MAX <= ucChannelNo)
    {
        return VOS_NULL_PTR;
    }

    if (USIMM_UNLIMIT_APP_BUTT == g_astUSIMMCardAppInfo[ucChannelNo].enAppType)
    {
        return VOS_NULL_PTR;
    }

    return &g_astUSIMMCardAppInfo[ucChannelNo].stAdfInfo;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAppInfoByCH
功能描述  :通过CHANNLE号获得应用信息
输入参数  :ucCHNum
输出参数  :无
返 回 值  :USIMM_COMM_CARD_APP_INFO_STRU *

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_COMM_CARD_APP_INFO_STRU* USIMM_CCB_GetAppInfoByCH(VOS_UINT8 ucChannelNo)
{
    if (USIMM_CHANNEL_NUMBER_MAX <= ucChannelNo)
    {
        return VOS_NULL_PTR;
    }

    return &g_astUSIMMCardAppInfo[ucChannelNo];
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAppTypeByCH
功能描述  :通过CHANNLE号获得应用类型
输入参数  :ucCHNum
输出参数  :无
返 回 值  :USIMM_CARDAPP_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_CARDAPP_ENUM_UINT32 USIMM_CCB_GetAppTypeByCH(VOS_UINT8 ucCHNum)
{
    if (ucCHNum >= USIMM_CHANNEL_NUMBER_MAX)
    {
        return USIMM_UNLIMIT_APP_BUTT;
    }

    return g_astUSIMMCardAppInfo[ucCHNum].enAppType;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetPINInfo
功能描述  :获取全局PIN信息
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_COMM_PIN_INFO_STRU*
修订记录  :

1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_COMM_PIN_INFO_STRU* USIMM_CCB_GetPINInfo(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT32                  ulIndex;

    /* 参数判断 */
    if (enAppType >= USIMM_UNLIMIT_APP_BUTT)
    {
        return VOS_NULL_PTR;
    }

    ulIndex = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ulIndex)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetPINInfo: USIMM_CCB_GetAppChNO Error");

        return VOS_NULL_PTR;
    }

    return &g_astUSIMMCardAppInfo[ulIndex].stPinInfo;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetPIN1InfoByRef
功能描述  :获取全局PIN1信息
输入参数  :USIMM_COMM_PIN_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_APP_PIN_INFO_STRU*
修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_APP_PIN_INFO_STRU* USIMM_CCB_GetPIN1InfoByRef(USIMM_COMM_PIN_ENUM_UINT32 enPinType)
{
    /* 参数判断 */
    if (enPinType >= USIMM_KEY_REF_PIN_BUTT)
    {
        enPinType = USIMM_UNIVERSIAL_PIN;
    }

    return &g_astUSIMMAppPIN1Info[enPinType];
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetPIN1InfoByApp
功能描述  :获取全局PIN信息
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_APP_PIN_INFO_STRU*
修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_APP_PIN_INFO_STRU* USIMM_CCB_GetPIN1InfoByApp(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    /* 参数判断 */
    if (enAppType >= USIMM_UNLIMIT_APP_BUTT)
    {
        return VOS_NULL_PTR;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetPIN1InfoByApp: USIMM_CCB_GetAppChNO Error");

        return VOS_NULL_PTR;
    }

    return USIMM_CCB_GetPIN1InfoByRef(g_astUSIMMCardAppInfo[ucChannelNo].stPinInfo.enPinKeyRef);
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetPIN2InfoByApp
功能描述  :获取全局PIN2信息
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_APP_PIN_INFO_STRU*
修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_APP_PIN_INFO_STRU* USIMM_CCB_GetPIN2InfoByApp(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    /* 参数判断 */
    if (enAppType >= USIMM_UNLIMIT_APP_BUTT)
    {
        return VOS_NULL_PTR;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetPIN2InfoByApp: USIMM_CCB_GetAppChNO Error");

        return VOS_NULL_PTR;
    }

    return &g_astUSIMMCardAppInfo[ucChannelNo].stPinInfo.stPin2Info;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetAppFDN
功能描述  :设置应用的FDN状态
输入参数  :USIMM_CARDAPP_ENUM_UINT32
           USIMM_FDNSTATUS_ENUM_UINT32
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetAppFDN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus
)
{
    VOS_UINT8                           ucChannelNo;

    if ((USIMM_CARDAPP_BUTT <= enAppType)
     || (USIMM_FDNSTATUS_BUTT <= enFDNStatus))
    {
        return;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_SetAppFDN: USIMM_CCB_GetAppChNO Error");

        return ;
    }

    g_astUSIMMCardAppInfo[ucChannelNo].enFDNStatus = enFDNStatus;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAppFDN
功能描述  :获得应用的FDN状态
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_FDNSTATUS_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_FDNSTATUS_ENUM_UINT32 USIMM_CCB_GetAppFDN(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        return USIMM_FDNSTATUS_OFF;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetAppFDN: USIMM_CCB_GetAppChNO Error");

        return USIMM_FDNSTATUS_OFF;
    }

    return g_astUSIMMCardAppInfo[ucChannelNo].enFDNStatus;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetAppBDN
功能描述  :设置应用的BDN状态
输入参数  :USIMM_CARDAPP_ENUM_UINT32
           USIMM_BDNSTATUS_ENUM_UINT32
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetAppBDN(USIMM_CARDAPP_ENUM_UINT32 enAppType,
                                        USIMM_BDNSTATUS_ENUM_UINT32 enBDNStatus)
{
    VOS_UINT8                           ucChannelNo;

    if ((USIMM_CARDAPP_BUTT <= enAppType)
     || (USIMM_FDNSTATUS_BUTT <= enBDNStatus))
    {
        return;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_SetAppBDN: USIMM_CCB_GetAppChNO Error");

        return ;
    }

    g_astUSIMMCardAppInfo[ucChannelNo].enBDNStatus = enBDNStatus;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAppBDN
功能描述  :获得应用的BDN状态
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_BDNSTATUS_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_BDNSTATUS_ENUM_UINT32 USIMM_CCB_GetAppBDN(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        return USIMM_BDNSTATUS_OFF;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetAppBDN: USIMM_CCB_GetAppChNO Error");

        return USIMM_BDNSTATUS_OFF;
    }

    return g_astUSIMMCardAppInfo[ucChannelNo].enBDNStatus;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetAppChNO
功能描述  :赋值应用通道号
输入参数  :USIMM_CARDAPP_ENUM_UINT32
           VOS_UINT32
输出参数  :无
返 回 值  :VOS_VOID

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetAppChNO(VOS_UINT8 ucChannelNo, USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    if ((USIMM_UNLIMIT_APP_BUTT < enAppType)
        ||(USIMM_CHANNEL_NUMBER_MAX <= ucChannelNo))
    {
        return;
    }

    g_astUSIMMCardAppInfo[ucChannelNo].enAppType = enAppType;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAppChNO
功能描述  :获得应用的通道号
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :VOS_UINT8

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_UINT8 USIMM_CCB_GetAppChNO(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           i;

    if (USIMM_UNLIMIT_AUTO == enAppType)
    {
        return 0;
    }

    for(i=0; i< (VOS_UINT8)(ARRAYSIZE(g_astUSIMMCardAppInfo)); i++)
    {
        if (g_astUSIMMCardAppInfo[i].enAppType == enAppType)
        {
            return i;
        }
    }

    return VOS_NULL_BYTE;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetSimPhase
功能描述  :赋值sim卡phase
输入参数  :USIMM_CARDAPP_ENUM_UINT32
           VOS_UINT32
输出参数  :无
返 回 值  :USIMM_BDNSTATUS_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetSimPhase(USIMM_CARDAPP_ENUM_UINT32   enAppType,
                                            USIMM_SIM_PHASE_ENUM_UINT32 enSimPhase)
{
    VOS_UINT8                           ucChannelNo;

    if ((USIMM_CARDAPP_BUTT <= enAppType)
     || (USIMM_SIM_PHASE_BUTT <= enSimPhase))
    {
        return;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetAppSession: USIMM_CCB_GetAppChNO Error");

        return ;
    }

    g_astUSIMMCardAppInfo[ucChannelNo].enSimPhase = enSimPhase;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetSimPhase
功能描述  :获得sim卡phase
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :VOS_UINT32

修订记录  :
1. 日    期   : 2015年3月6日
   作    者   : g00256031
   修改内容   : 新增

*****************************************************************************/
USIMM_SIM_PHASE_ENUM_UINT32 USIMM_CCB_GetSimPhase(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT8                           ucChannelNo;

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        return USIMM_SIM_PHASE_ONE;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CCB_GetAppSession: USIMM_CCB_GetAppChNO Error");

        return USIMM_SIM_PHASE_ONE;
    }

    return g_astUSIMMCardAppInfo[ucChannelNo].enSimPhase;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAIDByApp
功能描述  :
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_AID_INFO_STRU*

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/
USIMM_AID_INFO_STRU* USIMM_CCB_GetAIDByApp(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    if (enAppType >= USIMM_CARDAPP_BUTT)
    {
        return VOS_NULL_PTR;
    }

    if (  (VOS_NULL == g_astUSIMMInitAIDInfo[enAppType].ulAIDLen)
        ||(USIMM_AID_LEN_MAX < g_astUSIMMInitAIDInfo[enAppType].ulAIDLen))
    {
        return VOS_NULL_PTR;
    }

    return &g_astUSIMMInitAIDInfo[enAppType];
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetAIDByApp
功能描述  :
输入参数  :USIMM_CARDAPP_ENUM_UINT32
输出参数  :无
返 回 值  :USIMM_AID_INFO_STRU*

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetAIDByApp(USIMM_CARDAPP_ENUM_UINT32   enAppType,
                                            VOS_UINT32                  ulDataLen,
                                            VOS_UINT8                   *pucAID)
{
    if (enAppType >= USIMM_CARDAPP_BUTT)
    {
        return ;
    }

    if (VOS_NULL == g_astUSIMMInitAIDInfo[enAppType].ulAIDLen)
    {
        g_astUSIMMInitAIDInfo[enAppType].ulAIDLen = ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(g_astUSIMMInitAIDInfo[enAppType].aucAID, pucAID, ulDataLen);
        /*lint +e534*/
    }

    return ;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetAIDFcp
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/

VOS_VOID USIMM_CCB_SetAIDFcp(VOS_UINT8 ucChannelNo, VOS_UINT32 ulFcpLen, VOS_UINT8 *pucFcp)
{
    if (ucChannelNo >= USIMM_CHANNEL_NUMBER_MAX)
    {
        return;
    }

    g_astUSIMMChGetRsp[ucChannelNo].ulAIDFcpLen = ulFcpLen;

    /*lint -e534*/
    VOS_MemCpy(g_astUSIMMChGetRsp[ucChannelNo].aucAIDFcp, pucFcp, ulFcpLen);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAIDFcp
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/

VOS_VOID USIMM_CCB_GetAIDFcp(VOS_UINT8 ucChannelNo, VOS_UINT32 *pulFcpLen, VOS_UINT8 **ppucFcp)
{
    if (ucChannelNo >= USIMM_CHANNEL_NUMBER_MAX)
    {
        *pulFcpLen = VOS_NULL;

        return;
    }

    *pulFcpLen = g_astUSIMMChGetRsp[ucChannelNo].ulAIDFcpLen;

    *ppucFcp = g_astUSIMMChGetRsp[ucChannelNo].aucAIDFcp;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAIDFcp
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/

VOS_VOID USIMM_CCB_ClearAIDFcp(VOS_UINT8 ucChannelNo)
{
    if (ucChannelNo >= USIMM_CHANNEL_NUMBER_MAX)
    {
        return;
    }

    g_astUSIMMChGetRsp[ucChannelNo].ulAIDFcpLen = 0;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAIDFcp
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/

VOS_VOID USIMM_CCB_SetResponse(VOS_UINT8 ucChannelNo, VOS_UINT32 ulRspLen, VOS_UINT8 *pucRsp)
{
    if (ucChannelNo >= USIMM_CHANNEL_NUMBER_MAX)
    {
        return;
    }

    g_astUSIMMChGetRsp[ucChannelNo].ulRspLen = ulRspLen;

    /*lint -e534*/
    VOS_MemCpy(g_astUSIMMChGetRsp[ucChannelNo].aucRspContent, pucRsp, ulRspLen);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAIDFcp
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/

VOS_VOID USIMM_CCB_GetResponse(VOS_UINT8 ucChannelNo, VOS_UINT32 *pulRspLen, VOS_UINT8 **ppucRsp)
{
    if (ucChannelNo >= USIMM_CHANNEL_NUMBER_MAX)
    {
        *pulRspLen = VOS_NULL;

        return;
    }

    *pulRspLen = g_astUSIMMChGetRsp[ucChannelNo].ulRspLen;

    *ppucRsp = g_astUSIMMChGetRsp[ucChannelNo].aucRspContent;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetAIDFcp
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增

*****************************************************************************/

VOS_VOID USIMM_CCB_ClearResponse(VOS_UINT8 ucChannelNo)
{
    if (ucChannelNo >= USIMM_CHANNEL_NUMBER_MAX)
    {
        return;
    }

    g_astUSIMMChGetRsp[ucChannelNo].ulRspLen = VOS_NULL;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetUsimSimulateIsimStatus
功能描述  :返回USIM是否支持模拟ISIM的状态
输入参数  :无
输出参数  :无
返 回 值  :状态

修订记录  :
1. 日    期   : 2015年4月8日
   作    者   : H00300778
   修改内容   : 新增

*****************************************************************************/
VOS_UINT32 USIMM_CCB_GetUsimSimulateIsimStatus(VOS_VOID)
{
    return gulUsimSupportIMS;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetUsimSimulateIsimStatus
功能描述  :设置USIM是否支持模拟ISIM的状态
输入参数  :ulStatus:状态
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年4月8日
   作    者   : H00300778
   修改内容   : 新增

*****************************************************************************/
VOS_VOID USIMM_CCB_SetUsimSimulateIsimStatus(VOS_UINT32 ulStatus)
{
    gulUsimSupportIMS = ulStatus;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_IsCardExist
功能描述  :返回当前是否有卡(快速开机模式也算是有卡)
输入参数  :ulStatus:状态
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年4月8日
   作    者   : H00300778
   修改内容   : 新增

*****************************************************************************/
VOS_UINT32 USIMM_CCB_IsCardExist(VOS_VOID)
{
    if (USIMM_PHYCARD_TYPE_NOCARD == USIMM_CCB_GetCardType())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/*****************************************************************************
函 数 名  :USIMM_CCB_GetFilePoolTotalGlobal
功能描述  :返回文件池全局变量
输入参数  :无
输出参数  :文件池的总全局变量
返 回 值  :无

修订记录  :
1. 日    期   : 2015年4月8日
   作    者   : C00299064
   修改内容   : 新增

*****************************************************************************/
USIMM_POOL_ST* USIMM_CCB_GetFilePoolTotalGlobal(VOS_VOID)
{
    return &gstUSIMMPOOL;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetFilePoolTotalGlobal
功能描述  :返回文件池单个记录
输入参数  :无
输出参数  :返回文件池单个记录
返 回 值  :无

修订记录  :
1. 日    期   : 2015年4月8日
   作    者   : C00299064
   修改内容   : 新增

*****************************************************************************/
USIMM_POOL_ONERECORD_ST* USIMM_CCB_GetPoolFileByIndex(VOS_UINT32 ulFileIndex)
{
    if (USIMM_POOL_MAX_NUM <= ulFileIndex)
    {
        USIMM_ERROR_LOG("USIMM_CCB_GetPoolFileByIndex: index is err");
        return VOS_NULL_PTR;
    }

    return &gstUSIMMPOOL.astpoolRecord[ulFileIndex];
}

/*****************************************************************************
函 数 名  :USIMM_CCB_GetUsimOpenSpeed
功能描述  :返回快速开机模式状态
输入参数  :无
输出参数  :无
返 回 值  :快速开机模式状态:USIMM_OPENSPEEDDISABLE/USIMM_OPENSPEEDENABLE

修订记录  :
1. 日    期   : 2015年4月8日
   作    者   : H00300778
   修改内容   : 新增
*****************************************************************************/
VOS_UINT32 USIMM_CCB_GetUsimOpenSpeed(VOS_VOID)
{
    return gulUSIMMOpenSpeed;
}

/*****************************************************************************
函 数 名  :USIMM_CCB_SetUsimOpenSpeed
功能描述  :设置快速开机模式状态
输入参数  :ulStatus:快速开机模式状态:USIMM_OPENSPEEDDISABLE/USIMM_OPENSPEEDENABLE
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年4月8日
   作    者   : H00300778
   修改内容   : 新增
*****************************************************************************/
VOS_VOID USIMM_CCB_SetUsimOpenSpeed(VOS_UINT32 ulStatus)
{
    gulUSIMMOpenSpeed = ulStatus;

    return;
}

/*****************************************************************************
函 数 名  : USIMM_T1InitGlobalVar
功能描述  : T=1相关全局变量的初始化
输入参数  : VOS_VOID
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2013年10月22日
   作    者   : L00256032
   修改内容   : V9R1 T=1项目新增
*****************************************************************************/
VOS_VOID USIMM_T1InitGlobalVar(VOS_VOID)
{
    /* BWT倍数初始化为1 */
    g_stUsimmT1CtrlCtx.ulBWTTimes = USIMM_T1_DEFAULT_WTX;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitPoolGlobal
功能描述  :初始化文件池的相关变量和状态　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_InitPoolGlobal(VOS_VOID)
{
    VOS_UINT32                          i;
    USIMM_POOL_ST                      *pstPool;

    pstPool                     =  USIMM_CCB_GetFilePoolTotalGlobal();

    pstPool->enPoolStatus       = USIMM_POOL_INITIALED;   /*更改全局变量内容*/

    pstPool->ucPoolFileCount    = 0x00;            /*更改已存文件个数*/

    /*lint -e534*/
    VOS_MemSet(pstPool->astpoolRecord, 0, sizeof(gstUSIMMPOOL.astpoolRecord));/*清空单元内容*/
    /*lint +e534*/

    /* 初始化APPTYPE */
    for (i = 0; i < USIMM_POOL_MAX_NUM; i++)
    {
        pstPool->astpoolRecord[i].enAppType = USIMM_UNLIMIT_APP_BUTT;
    }

    return;
}

/********************************************************************
函 数 名  :USIMM_COMM_InitGlobalVar
功能描述  :初始化相关公共全局变量的内容
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年3月12日
   作    者   : g00256031
   修改内容   : Creat
********************************************************************/
VOS_VOID USIMM_SetGlobalVarDefValue(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stUSIMMInitInfo,      0, sizeof(g_stUSIMMInitInfo));

    VOS_MemSet(&gstUSIMMAPDU,           0, sizeof(gstUSIMMAPDU));

    VOS_MemSet(&gstUSIMMBaseInfo,       0, sizeof(gstUSIMMBaseInfo));

    VOS_MemSet(&gstUSIMMDLControl,      0, sizeof(gstUSIMMDLControl));

    VOS_MemSet(&gstUSIMMDrvInfo,        0, sizeof(gstUSIMMDrvInfo));

    VOS_MemSet(g_astUSIMMChGetRsp,      0, sizeof(g_astUSIMMChGetRsp));

    VOS_MemSet(g_astUSIMMAppPIN1Info,   0, sizeof(g_astUSIMMAppPIN1Info));

#if (FEATURE_VSIM == FEATURE_ON)
    VOS_MemSet(&g_stUSIMMVSimAuthInfo,  0, sizeof(g_stUSIMMVSimAuthInfo));
#endif

    VOS_MemSet(g_astUSIMMAppPIN1Info,   0, sizeof(g_astUSIMMAppPIN1Info));

    VOS_MemSet(g_astUSIMMInitAIDInfo,   0, sizeof(g_astUSIMMInitAIDInfo));

    VOS_MemSet(&g_stT1StatisticInfo,    0, sizeof(g_stT1StatisticInfo));

    VOS_MemSet(&g_stUSIMMT1Para,        0, sizeof(g_stUSIMMT1Para));

    /*T1 Global Init*/
    VOS_MemSet(&g_stUsimmT1CtrlCtx,     0, sizeof(g_stUsimmT1CtrlCtx));

    VOS_MemSet(&g_stT1SendDataInfo,     0, sizeof(g_stT1SendDataInfo));

    VOS_MemSet(&g_stT1RcvDataInfo,      0, sizeof(g_stT1RcvDataInfo));
    /*lint +e534*/

    g_enUSIMMTMode          = USIMM_DL_T_MODE_T0;

    g_ulATTSpecErrSWCnt     = 0;

#if(FEATURE_ON == FEATURE_PTM)
    /*lint -e534*/
    VOS_MemSet(&g_stCardErrorLog, 0, sizeof(g_stCardErrorLog));
    /*lint +e534*/
#endif

    USIMM_COMM_ClearAppInfoGlobal();

    USIMM_InitPoolGlobal();

    USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

    USIMM_CCB_SetCardVersion(USIMM_PHYCARD_TYPE_NOCARD);

    USIMM_COMM_InitCommFuncTble();

    USIMM_COMM_ClearInitCtrlGlobal();

    USIMM_COMM_ResetInitListStatus();

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ClearGlobalVar
功能描述  :清空全局变量的内容，仅在任务初始化调用
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2013年6月19日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ClearGlobalVar(VOS_VOID)
{
    USIMM_SetGlobalVarDefValue();

    USIMM_InitConfigGlobal();

    USIMM_CCB_SetTestCardType(USIMM_TEST_TYPE_NONE);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ResetGlobalVar
功能描述  :再次清空全局变量的内容，
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2013年6月19日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ResetGlobalVar(VOS_VOID)
{
    USIMM_PoolDelAll();         /*避免内存泄露，先释放相关内存*/

    USIMM_SetGlobalVarDefValue();

    USIMM_CCB_SetUsimSimulateIsimStatus(VOS_FALSE);

    USIMM_COMM_ClearAppInfoGlobal();

    USIMM_T1InitGlobalVar();

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ResetGlobalVarWithCard
功能描述  :重设定相关全局变量的内容,并且会设置卡状态上报标记
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ResetGlobalVarWithCard(VOS_VOID)
{
    USIMM_ResetGlobalVar();

    USIMM_CCB_SetAppStateChange(USIMM_GUTL_APP, USIMM_CARD_STATE_CHANGED);

    USIMM_CCB_SetAppStateChange(USIMM_IMS_APP, USIMM_CARD_STATE_CHANGED);

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    USIMM_CCB_SetAppStateChange(USIMM_CDMA_APP, USIMM_CARD_STATE_CHANGED);
#endif

    return;
}

/*****************************************************************************
函 数 名  :USIMM_AttGlobalInit
功能描述  :初始化ATT相关全局变量的内容　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2012年6月18日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_InitConfigGlobal(VOS_VOID)
{
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU   stUSIMMOpenSpeed;

    /* 读取NV判断快速开机状态 */
    if (NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag, &stUSIMMOpenSpeed, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)))
    {
        USIMM_CCB_SetUsimOpenSpeed(USIMM_OPENSPEEDDISABLE);
    }
    else
    {
        USIMM_CCB_SetUsimOpenSpeed(stUSIMMOpenSpeed.ulQuickStartSta);
    }

    /* NV项读取失败按所有定制都不支持处理 */
    if(VOS_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config,
                         (VOS_VOID*)&g_stUsimmFeatureCfg, sizeof(g_stUsimmFeatureCfg)))
    {
        /*lint -e534*/
        VOS_MemSet(g_stUsimmFeatureCfg.unCfg.aulValue , VOS_FALSE, sizeof(g_stUsimmFeatureCfg.unCfg.aulValue));
        /*lint +e534*/
    }

#if(FEATURE_ON == FEATURE_PTM)
    if (VOS_OK != NV_Read(en_NV_Item_ErrLogCtrlInfo, &g_stErrLogCtrlInfo, sizeof(g_stErrLogCtrlInfo)))
    {
        /* Error Log上报控制NV项,如读失败还原初始化nv项 */
        /*lint -e534*/
        VOS_MemSet(&g_stErrLogCtrlInfo, 0, sizeof(g_stErrLogCtrlInfo));
        /*lint +e534*/
    }
#endif

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitOpneSpeed
功能描述  :初始化快速开机需要的全局变量的内容，并上报卡状态　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitOpenSpeed(VOS_VOID)
{
    USIMM_COMM_PIN_INFO_STRU           *pstCommPinInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;

    USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_ICC);
    USIMM_CCB_SetCardVersion(USIMM_PHYCARD_TYPE_ICC);
    USIMM_CCB_SetCardVersion(USIMM_PHYCARD_TYPE_NOCARD);
    USIMM_CCB_SetTestCardType(USIMM_TEST_TYPE_ROM_SIM);

    USIMM_CCB_SetAppChNO(0, USIMM_GUTL_APP);
    USIMM_CCB_SetAppService(USIMM_GUTL_APP, USIMM_CARD_SERVIC_AVAILABLE);

    /* 初始化当前的PIN基本内容 */
    pstCommPinInfo = USIMM_CCB_GetPINInfo(USIMM_GUTL_APP);

    pstCommPinInfo->enCurPINType  = USIMM_PIN2;

    /* 初始化PIN信息 */
    pstCommPinInfo->enPinKeyRef   = USIMM_KEY_REF_PIN_01;

    pstPin1Info = USIMM_CCB_GetPIN1InfoByRef(USIMM_KEY_REF_PIN_01);

    pstPin1Info->ucPINRefNum     = USIMM_KEY_REF_PIN_01;

    /* 初始化默认次数 */
    pstPin1Info->ucPinRemainTime = 3;

    pstCommPinInfo->stPin2Info.ucPinRemainTime = 3;

    pstPin1Info->ucPukRemainTime = 10;

    pstCommPinInfo->stPin2Info.ucPukRemainTime = 10;

    USIMM_OpenSpeedFileInit();

    USIMM_CardStatusInd(MAPS_PIH_PID);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SetTimeOutFlag
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SetTimeOutFlag(
    VOS_BOOL                            bFlag)
{
    gstUSIMMBaseInfo.bTimeOut = bFlag;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_GetTimeOutFlag
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_BOOL USIMM_GetTimeOutFlag(VOS_VOID)
{
    return gstUSIMMBaseInfo.bTimeOut;
}

/*****************************************************************************
函 数 名  :USIMM_GetDLErrorInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
USIMMDL_ERROR_ENUM_UINT32 USIMM_GetT0DLErrorInfo(VOS_VOID)
{
    return gstUSIMMDLControl.enDLError;
}

#else
#include "UsimmApi.h"
#include "usimmbase.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        PS_FILE_ID_USIMM_GLOBAL_C

/*当前的快速开机状态*/
VOS_UINT32                          gulUSIMMOpenSpeed     = 0;

/*当前卡的基本信息*/
USIMM_BASE_INFO_ST                  gstUSIMMBaseInfo;

/* ISIM卡信息 */
USIMM_CARD_APP_INFO_ST              gastUSIMMCardAppInfo[USIMM_UICC_BUTT];

/* 标记USIM是否支持IMS */
VOS_UINT32                          gulUsimSupportIMS;

USIMM_ISIM_USIM_CONVERSION_ST       gastIsimUsimEFConTBL[USIMM_ISIMEFTOUSIMEF_TBL_SIZE] ={
                                               {EFISIMAD,       USIMM_USIM_EFAD_ID},
                                               {EFISIMGBABP,    USIMM_USIM_EFGBAP_ID},
                                               {EFISIMGBANL,    USIMM_USIM_EFGBANL_ID},
                                               {EFISIMNAFKCA,   USIMM_USIM_EFNAFKCA_ID},
                                               {EFISIMUICCIARI, USIMM_USIM_EFUICCIARI_ID}};

USIMM_ISIM_USIM_CONVERSION_ST       gastIsimToUsimEFTBL[USIMM_ISIMEFTOUSIMEF_TBL_SIZE] =
                                               {{EFISIMAD,      EFAD},
                                               {EFISIMGBABP,    EFGBABP},
                                               {EFISIMGBANL,    EFGBANL},
                                               {EFISIMNAFKCA,   EFNAFKCA},
                                               {EFISIMUICCIARI, EFUICCIARI}};

/*底软相关的基本信息*/
USIMM_DRV_INFO_ST                   gstUSIMMDrvInfo;

/*当前访问的文件信息，如果需要支持逻辑通道则定义为数组即可*/
USIMM_CURFILEINFO_ST                gstUSIMMCurFileInfo;

/*当前ADF信息*/
USIMM_ADF_INFO_STRU                 gstUSIMMADFInfo;

/*AID信息*/
USIMM_AID_INFO_STRU                 g_astAidInfo[USIMM_AID_TYPE_BUTT];

/*当前的APDU命令的内容*/
USIMM_APDU_ST                       gstUSIMMAPDU = {0};

/*当前链路层的状态*/
USIMMDL_CONTROL_ST                  gstUSIMMDLControl;

/*文件缓存定义*/
USIMM_POOL_ST                       gstUSIMMPOOL;

/*保存Log信息的控制变量*/
USIMM_LOG_DATA_STRU                 g_stUSIMMLogData;

VOS_UINT32                          g_ulUSIMMExcLogLenBK;

USIMM_LOG_DATA_STRU                 g_stUSIMMExcLogData;

/* 保存逻辑通道信息 */
USIMM_CHANNEL_INFO_STRU             g_astUSIMMChCtrl[USIMM_CHANNEL_NUM_MAX];

/* 保存逻辑通道上GetResponse信息 */
USIMM_CHANNEL_GET_RSP_STRU          g_astUSIMMChGetRsp[USIMM_CHANNEL_NUM_MAX];

/* 保存逻辑通道上AID FCP信息 */
USIMM_CHANNEL_AIDFCPINFO_STRU       g_astUSIMMChAIDFCP[USIMM_CHANNEL_NUM_MAX];

USIMM_CARD_INIT_INFO_LOG_STRU       g_stUSIMMInitInfo;

/* 指示支持T=1还是T=0 */
USIMM_DL_T_MODE_ENUM_UINT32         g_enUSIMMTMode = USIMM_DL_T_MODE_T0;

/* T=1相关参数备份，用于卡复位场景后恢复相关的T=1上下文 */
USIMM_DL_T1_PARA_STRU               g_stUSIMMT1Para;

/* 指示是否发送了IFS REQ */
VOS_BOOL                            g_bSendIFSReqFlag = VOS_FALSE;

#if(FEATURE_ON == FEATURE_PTM)
USIMM_MNTN_STATE_ERROR_EVENT_STRU   g_stCardErrorLog;

NV_ID_ERR_LOG_CTRL_INFO_STRU        g_stErrLogCtrlInfo;
#endif

USIMM_CARD_VERSIONTYPE_STRU         g_stUSIMMCardVersionType;

#if (FEATURE_VSIM == FEATURE_ON)
VOS_UINT8                           *g_pucUSIMMVsimData = VOS_NULL_PTR;
#endif

VOS_UINT32                          g_ulCsimSessionId = VOS_NULL_DWORD;

VOS_BOOL                            g_bCacheEFIccidData = VOS_FALSE;
VOS_UINT8                           g_aucEFIccidData[USIMM_EFICCID_LEN] = {0};

/*****************************************************************************
 全局变量名    : g_ulUsimmFeatureCfg
 全局变量说明  : USIMM模块定制特性全局控制变量
 1.日    期   : 2012年06月19日
   作    者   : H59254
   修改内容   : 新建
*****************************************************************************/
USIMM_FEATURE_CFG_STRU              g_stUsimmFeatureCfg;

VOS_UINT32                          g_ulATTSpecErrSWCnt;    /* ATT特殊处理的SW计数 */

/*初始化第一步时候读取的不受PIN保护的文件ID*/
VOS_UINT16 gausInitFileOne[USIMM_INITFIRST_FILENUM]   = {0x2FE2,0x2F05};

/*SIM卡需要初始化读取缓存的Mandatory文件ID*/
VOS_UINT16 gausSimInitMFile[USIMM_INITSIM_MFILENUM]   = {0x6F07,0x6FAD,0x6F78,0x6F31,0x6F7E,0x6F20,0x6F74,0x6F7B};

/*USIM卡需要初始化读取缓存的Mandatory文件ID*/
VOS_UINT16 gausUsimInitMFile[USIMM_INITUSIM_MFILENUM] = {0x6F07,0x6FC4,0x6FAD,0x6F31,0x6F7E,0x6F78,0x6F73,0x6F08,0x6F09,0x6F7B,0x6F5B,0x6F5C};

/* 如果有新增加的OP文件读取，需要在下面的表里增加对应的服务。如果不确定或者在6F38找不到对应的服务的就写USIM_SVR_NONE */
/*SIM卡需要初始化读取缓存的Optional文件ID*/
USIMM_OPFILE_LIST_STRU gastSimInitOFile[USIMM_INITSIM_OFILENUM] = {{0x6F15, (VOS_UINT16)UICC_SVR_NONE},
                                                                   {0x6F52, (VOS_UINT16)SIM_SVR_GPRS},
                                                                   {0x6F53, (VOS_UINT16)SIM_SVR_GPRS},
                                                                   {0x6F60, (VOS_UINT16)SIM_SVR_USER_CTRL_PLMN},
                                                                   {0x6F61, (VOS_UINT16)SIM_SVR_OPERATOR_CTRL_PLMN},
                                                                   {0x6F62, (VOS_UINT16)SIM_SVR_HPLMN},
                                                                   {0x6F45, (VOS_UINT16)SIM_SVR_CBMID},
                                                                   {0x6F48, (VOS_UINT16)SIM_SVR_DD_VIA_SMS_CB},
                                                                   {0x6F50, (VOS_UINT16)SIM_SVR_CBMIR},
                                                                   {0x6F46, (VOS_UINT16)SIM_SVR_SERVICE_PRO_NAME},
                                                                   {0x6F3E, (VOS_UINT16)SIM_SVR_GIDL1},
                                                                   {0x6F30, (VOS_UINT16)SIM_SVR_PLMN_SELECTOR}};
/*USIM卡需要初始化读取缓存的Optional文件ID*/
USIMM_OPFILE_LIST_STRU gastUsimInitOFile[USIMM_INITUSIM_OFILENUM] = {{0x6F15, (VOS_UINT16)UICC_SVR_NONE},
                                                                     {0x6F60, (VOS_UINT16)USIM_SVR_UPLMN_SEL_WACT},
                                                                     {0x6F61, (VOS_UINT16)USIM_SVR_OPLMN_SEL_WACT},
                                                                     {0x6F62, (VOS_UINT16)USIM_SVR_HPLMN_WACT},
                                                                     {0x6F46, (VOS_UINT16)USIM_SVR_SPN},
                                                                     {0x6F3E, (VOS_UINT16)USIM_SVR_GID1},
                                                                     {0x6FD9, (VOS_UINT16)USIM_SVR_EHPLMN},
                                                                     {0x6FDB, (VOS_UINT16)USIM_SVR_EHPLMN_IND},
                                                                     {0x6FDC, (VOS_UINT16)USIM_SVR_RPLMN_LACT},
                                                                     {0x6F56, (VOS_UINT16)UICC_SVR_NONE},
                                                                     {0x6F45, (VOS_UINT16)USIM_SVR_CBMI},
                                                                     {0x6F48, (VOS_UINT16)USIM_SVR_DATA_DL_SMSCB},
                                                                     {0x6F50, (VOS_UINT16)USIM_SVR_CBMIR},
                                                                     {0x4F20, (VOS_UINT16)USIM_SVR_GSM_ACCESS_IN_USIM},
                                                                     {0x4F52, (VOS_UINT16)USIM_SVR_GSM_ACCESS_IN_USIM}};
/* ATT USIM卡需要初始化的文件列表 */
VOS_UINT16 g_ausAttUsimInitFile[USIMM_USIM_ATT_INITFILE_NUM]={EFACTINGHPLMN, EFRATMODE};

/* ATT SIM卡需要初始化的文件列表 */
VOS_UINT16 g_ausAttSimInitFile [USIMM_SIM_ATT_INITFILE_NUM]={EFACTINGHPLMN};

VOS_UINT16 gausSimDFTELFile[15] = {0x6F3A,0x6F3B,0x6F3C,0x6F3D,0x6F40,0x6F42,0x6F43,0x6F44,0x6F47,0x6F49,0x6F4A,0x6F4B,0x6F4C,0x6F4D,0x6F4E};

VOS_UINT16 gausSimDFGSMFile[46] = {0x6F05,0x6F07,0x6F11,0x6F12,0x6F13,0x6F14,0x6F15,0x6F16,0x6F17,0x6F18,0x6F19,0x6F20,0x6F30,0x6F31,0x6F37,0x6F38,0x6F39,0x6F3E,0x6F3F,0x6F41,0x6F45,0x6F46,0x6F48,0x6F74,0x6F78,0x6F7B,0x6F7E,0x6FAD,0x6FAE,0x6FB1,0x6FB2,0x6FB3,0x6FB4,0x6FB5,0x6FB6,0x6FB7,0x6F50,0x6F51,0x6F52,0x6F53,0x6F54,0x6F60,0x6F61,0x6F62,0x6F63,0x6F64};

VOS_UINT16 gausUsimDFGSMFile[39] = {0x6F05,0x6F07,0x6F20,0x6F30,0x6F31,0x6F37,0x6F38,0x6F39,0x6F3E,0x6F3F,0x6F41,0x6F45,0x6F46,0x6F48,0x6F74,0x6F78,0x6F7B,0x6F7E,0x6FAD,0x6FAE,0x6FB1,0x6FB2,0x6FB3,0x6FB4,0x6FB5,0x6FB6,0x6FB7,0x6F50,0x6F51,0x6F52,0x6F53,0x6F54,0x6F60,0x6F61,0x6F62,0x6F63,0x6F64,0x6FC5,0x6FC6};

VOS_UINT16 gausUsimDFTELFile[17] = {0x6F06,0x6F3A,0x6F3B,0x6F3C,0x6F40,0x6F42,0x6F43,0x6F44,0x6F47,0x6F49,0x6F4A,0x6F4B,0x6F4C,0x6F4D,0x6F4E,0x6F4F,0x6F54};

VOS_UINT16 gausUsimADFFile[88] = {0x6F05,0x6F06,0x6F07,0x6F08,0x6F09,0x6F15,0x6F2C,0x6F31,0x6F32,0x6F37,0x6F38,0x6F39,0x6F3B,0x6F3C,0x6F3E,0x6F3F,0x6F40,0x6F41,0x6F42,0x6F43,0x6F45,0x6F46,0x6F47,0x6F48,0x6F49,0x6F4B,0x6F4C,0x6F4D,0x6F4E,0x6F50,0x6F55,0x6F56,0x6F57,0x6F58,0x6F5B,0x6F5C,0x6F60,0x6F61,0x6F62,0x6FD9,
                            0x6F73,0x6F78,0x6F7B,0x6F7E,0x6F80,0x6F81,0x6F82,0x6F83,0x6FAD,0x6FB5,0x6FB6,0x6FB7,0x6FC3,0x6FC4,0x6FC5,0x6FC6,0x6FC7,0x6FC8,0x6FC9,0x6FCA,0x6FCB,0x6FCC,0x6FCD,0x6FCE,0x6FCF,0x6FD0,0x6FD1,0x6FD2,0x6FD3,0x6F4F,0x6FB1,0x6FB2,0x6FB3,0x6FB4,0x6FD4,0x6FD5,0x6FD6,0x6FD7,0x6FD8,0x6FDA,
                            0x6FDB,0x6FDC,0x6FDD,0x6FDE,0x6FDF,0x6FE2,0x6FE3,0x6FE4};


VOS_UINT16 gausSimDFGRAPHFile[1] = {0x4F20};

VOS_UINT16 gausSimDFSoLSAFile[2] = {0x4F30,0x4F31};

VOS_UINT16 gausSimDFMExEFile[4] = {0x4F40,0x4F41,0x4F42,0x4F43};

VOS_UINT16 gausUsimDFMMFile[2] = {0x4F47,0x4F48};

VOS_UINT16 gausUsimDFGSMAFile[4] = {0x4F20,0x4F52,0x4F63,0x4F64};

VOS_UINT16 gausUsimDFWLANFile[6] = {0x4F41,0x4F42,0x4F43,0x4F44,0x4F45,0x4F46};

USIMM_CARD_FILEMAP_ST   g_stUSIMMCardFileMap[10];

/*SIM卡的DF和子DF关系*/
USIMM_FILE_CONTENT_ST g_stSimDFGSMContent[USIMM_SIMDFGSMGDF_MAX] =
       {{DFMExE,     ARRAYSIZE(gausSimDFMExEFile),   gausSimDFMExEFile},
        {DFSoLSA,    ARRAYSIZE(gausSimDFSoLSAFile),  gausSimDFSoLSAFile}};

USIMM_FILE_CONTENT_ST g_stSimDFTELContent[USIMM_SIMDFTELGDF_MAX] =
       {{DFGRAPHICS, ARRAYSIZE(gausSimDFGRAPHFile),  gausSimDFGRAPHFile}};

USIMM_DF_CONTENT_ST g_stSimDFContent[USIMM_SIMDFCONTENT_MAX] =
       {{{DFGSM,      ARRAYSIZE(gausSimDFGSMFile),    gausSimDFGSMFile},   USIMM_SIMDFGSMGDF_MAX,  g_stSimDFGSMContent},
        {{DFTELCOM,   ARRAYSIZE(gausSimDFTELFile),    gausSimDFTELFile},   USIMM_SIMDFTELGDF_MAX,  g_stSimDFTELContent}};

/*Usim卡的DF和子DF的关系*/
USIMM_FILE_CONTENT_ST g_astUsimADFContent[USIMM_USIMADFGDF_MAX] =
       {{DFGSMACCESS,ARRAYSIZE(gausUsimDFGSMAFile),  gausUsimDFGSMAFile},
        {DFMExE,     ARRAYSIZE(gausSimDFMExEFile),   gausSimDFMExEFile},
        {DFWLAN,     ARRAYSIZE(gausUsimDFWLANFile),  gausUsimDFWLANFile},
        {DFSoLSA,    ARRAYSIZE(gausSimDFSoLSAFile),  gausSimDFSoLSAFile}};

USIMM_FILE_CONTENT_ST g_astUsimDFTELContent[USIMM_USIMADFTELGDF_MAX] =
       {{DFUGRAPHICS,ARRAYSIZE(gausSimDFGRAPHFile),  gausSimDFGRAPHFile},
        {DFMULTIMEDIA,ARRAYSIZE(gausUsimDFMMFile),   gausUsimDFMMFile}};

USIMM_DF_CONTENT_ST g_stUsimDFContent[USIMM_USIMDFCONTENT_MAX] =
       {{{ADF,        ARRAYSIZE(gausUsimADFFile),     gausUsimADFFile},    USIMM_USIMADFGDF_MAX,   g_astUsimADFContent},
        {{DFTELCOM,   ARRAYSIZE(gausUsimDFTELFile),   gausUsimDFTELFile},  USIMM_USIMADFTELGDF_MAX,g_astUsimDFTELContent},
        {{DFGSM,      ARRAYSIZE(gausUsimDFGSMFile),   gausUsimDFGSMFile},  0,                      0}};

/*SIM INS字节检查*/
/* 0x90, 0x00 */
VOS_UINT8 g_aucSim9000Ins[] = { CMD_INS_STATUS,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_READ_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_SLEEP,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_GET_RESPONSE,
                                CMD_INS_END};

/* 0x91, 0xFF */
VOS_UINT8 g_aucSim91XXIns[] = { CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_GET_RESPONSE,
                                CMD_INS_END};

/* 0x93, 0x00 */
VOS_UINT8 g_aucSim9300Ins[] = { CMD_INS_ENVELOPE,
                                CMD_INS_END};

/* 0x9E, 0xFF */
VOS_UINT8 g_aucSim9EXXIns[] = { CMD_INS_ENVELOPE,
                                CMD_INS_END};

/* 0x9F, 0xFF */
VOS_UINT8 g_aucSim9FFFIns[] = { CMD_INS_SELECT,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_END};

/* 0x92, 0x40 */
VOS_UINT8 g_aucSim9240Ins[] = { CMD_INS_SELECT,
                                CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_GET_RESPONSE,
                                CMD_INS_END};

/* 0x92, 0xFF */
VOS_UINT8 g_aucSim92FFIns[] = { CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_END};

/* 0x94, 0x00 */
VOS_UINT8 g_aucSim9400Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_END};

/* 0x94, 0x02 */
VOS_UINT8 g_aucSim9402Ins[] = { CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_END};

/* 0x94, 0x04 */
VOS_UINT8 g_aucSim9404Ins[] = { CMD_INS_SELECT,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_END};

/* 0x94, 0x08 */
VOS_UINT8 g_aucSim9408Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

/* 0x98, 0x02 */
VOS_UINT8 g_aucSim9802Ins[] = { CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

/* 0x98, 0x04 */
VOS_UINT8 g_aucSim9804Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

/* 0x98, 0x08 */
VOS_UINT8 g_aucSim9808Ins[] = { CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

/* 0x98, 0x10 */
VOS_UINT8 g_aucSim9810Ins[] = { CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_END};

/* 0x98, 0x40 */
VOS_UINT8 g_aucSim9840Ins[] = { CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

/* 0x98, 0x50 */
VOS_UINT8 g_aucSim9850Ins[] = { CMD_INS_INCREASE,
                                CMD_INS_END};
/* 0x67, 0x00    0x67, 0xFF    0x6B, 0xFF    0x6E, 0xFF    0x6F, 0x00    0x6F, 0xFF */
VOS_UINT8 g_aucSimSwAnyIns[] = {CMD_INS_ANY};

/*USIM INS字节检查*/
/*0x90,0x00  0x61,0xFF  0x91,0xFF  0x62,0xFF  0x63,0xFF  0x64,0x00  0x67,0x00  0x67,0xFF  0x68,0x00  0x68,0x81  0x68,0x82  0x6A,0x81  0x6A,0x86  0x6B,0x00  0x6C,0xFF  0x6E,0x00  0x6F,0x00  0x6F,0xFF*/
VOS_UINT8 g_aucUsimSwAnyIns[] = {CMD_INS_ANY};

    /* 0x93, 0x00 */
VOS_UINT8 g_aucUsim9300Ins[] = {CMD_INS_ENVELOPE,
                                CMD_INS_END};

    /* 0x98, 0x50 */
VOS_UINT8 g_aucUsim9850Ins[] = {CMD_INS_INCREASE,
                                CMD_INS_END};

    /* 0x98, 0x62 */
VOS_UINT8 g_aucUsim9862Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

    /* 0x62, 0x00 */
VOS_UINT8 g_aucUsim6200Ins[] = {CMD_INS_SELECT,
                                CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_GET_CHALLENGE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_TERMINAL_CAPABILITY,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x62, 0x81 */
VOS_UINT8 g_aucUsim6281Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_END};

    /* 0x62, 0x82 */
VOS_UINT8 g_aucUsim6282Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_END};

    /* 0x62, 0x83 */
VOS_UINT8 g_aucUsim6283Ins[] = {CMD_INS_SELECT,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_END};

    /* 0x62, 0x85 */
VOS_UINT8 g_aucUsim9285Ins[] = {CMD_INS_SELECT,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_END};

    /* 0x62, 0xF1 */
VOS_UINT8 g_aucUsim62F1Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x62, 0xF2 */
VOS_UINT8 g_aucUsim62F2Ins[] = {CMD_INS_RETRIEVE_DATA,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x62, 0xF3 */
VOS_UINT8 g_aucUsim62F3Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_END};

    /* 0x63, 0xC0 */
VOS_UINT8 g_aucUsim63CxIns[] = {CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

    /* 0x63,0xF1 */
VOS_UINT8 g_aucUsim63F1Ins[] = {CMD_INS_AUTHENTICATE,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x63, 0xF2 */
VOS_UINT8 g_aucUsim63F2Ins[] = {CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x65, 0x00 */
VOS_UINT8 g_aucUsim6500Ins[] = {CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_END};

    /* 0x65, 0x81 */
VOS_UINT8 g_aucUsim6581Ins[] = {CMD_INS_UPDATE_BINARY,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_END};

    /* 0x69, 0x00 */
VOS_UINT8 g_aucUsim6900Ins[] = {CMD_INS_SELECT,
                                CMD_INS_STATUS,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_GET_CHALLENGE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x69, 0x81 */
VOS_UINT8 g_aucUsim6981Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x82 */
VOS_UINT8 g_aucUsim6982Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x83 */
VOS_UINT8 g_aucUsim6983Ins[] = {CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_END};

    /* 0x69, 0x84 */
VOS_UINT8 g_aucUsim6984Ins[] ={CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x85 */
VOS_UINT8 g_aucUsim6985Ins[] = {CMD_INS_SELECT,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x69, 0x86 */
VOS_UINT8 g_aucUsim6986Ins[] = {CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x69, 0x89 */
VOS_UINT8 g_aucUsim6989Ins[] = {CMD_INS_SELECT,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_GET_CHALLENGE,
                                CMD_INS_TERMINAL_PROFILE,
                                CMD_INS_ENVELOPE,
                                CMD_INS_FETCH,
                                CMD_INS_TERMINAL_RESPONSE,
                                CMD_INS_MANAGE_CHANNEL,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_TERMINAL_CAPABILITY,
                                CMD_INS_END};

    /* 0x6A, 0x80 */
VOS_UINT8 g_aucUsim6A80Ins[] = {CMD_INS_SEARCH_RECORD,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_TERMINAL_CAPABILITY,
                                CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

    /* 0x6A, 0x82 */
VOS_UINT8 g_aucUsim6A82Ins[] = {CMD_INS_SELECT,
                                CMD_INS_READ_BINARY,
                                CMD_INS_UPDATE_BINARY,
                                CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_INCREASE,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x6A, 0x83 */
VOS_UINT8 g_aucUsim6A83Ins[] = {CMD_INS_READ_RECORD,
                                CMD_INS_UPDATE_RECORD,
                                CMD_INS_SEARCH_RECORD,
                                CMD_INS_END};

    /* 0x6A, 0x84 */
VOS_UINT8 g_aucUsim6A84Ins[] = {CMD_INS_SET_DATA,
                                CMD_INS_END};

    /* 0x6A, 0x87 */
VOS_UINT8 g_aucUsim6A87Ins[] = {CMD_INS_SELECT,
                                CMD_INS_DEACTIVATE_FILE,
                                CMD_INS_ACTIVATE_FILE,
                                CMD_INS_END};

/* 0x6A, 0x88 */
VOS_UINT8 g_aucUsim6A88Ins[] = {CMD_INS_VERIFY,
                                CMD_INS_CHANGE_PIN,
                                CMD_INS_DISABLE_PIN,
                                CMD_INS_ENABLE_PIN,
                                CMD_INS_UNBLOCK_PIN,
                                CMD_INS_AUTHENTICATE,
                                CMD_INS_RETRIEVE_DATA,
                                CMD_INS_END};

    /* 0x98, 0x63 */
VOS_UINT8 g_aucUsim9863Ins[] = {CMD_INS_MANAGE_SECURE_CHANNEL,
                                CMD_INS_TRANSACT_DATA,
                                CMD_INS_END};

/*Sim SW字节检查*/
USIMM_SWCHECK_ST gausSimSWCheck[USIMM_SIMSW_MAXNUMBER] =
                            {
                                {0x90, 0x00, USIMM_SW_OK,              },
                                {0x91, 0xFF, USIMM_SW_OK_WITH_SAT,     },
                                {0x93, 0x00, USIMM_SW_CARD_BUSY,       },
                                {0x9E, 0xFF, USIMM_SW_WARNING,         },
                                {0x9F, 0xFF, USIMM_SW_OK_WITH_RESOPNSE,},
                                {0x92, 0x40, USIMM_SW_MEMORY_ERROR,    },
                                {0x92, 0xFF, USIMM_SW_OK,              },
                                {0x94, 0x00, USIMM_SW_NOFILE_SELECT,   },
                                {0x94, 0x02, USIMM_SW_OUTOF_RANGE,     },
                                {0x94, 0x04, USIMM_SW_NOFILE_FOUND,    },
                                {0x94, 0x08, USIMM_SW_FILETYPE_ERROR,  },
                                {0x98, 0x02, USIMM_SW_SECURITY_ERROR,  },
                                {0x98, 0x04, USIMM_SW_SECURITY_ERROR,  },
                                {0x98, 0x08, USIMM_SW_PINSTATUS_ERROR, },
                                {0x98, 0x10, USIMM_SW_FILESTATUS_ERROR,},
                                {0x98, 0x40, USIMM_SW_PIN_BLOCK,       },
                                {0x98, 0x50, USIMM_SW_INCREACE_ERROR,  },
                                {0x67, 0x00, USIMM_SW_CMD_ERROR,       },
                                {0x67, 0xFF, USIMM_SW_P3_ERROR,        },
                                {0x6B, 0xFF, USIMM_SW_CMD_ERROR,       },
                                {0x6E, 0xFF, USIMM_SW_CLA_ERROR,       },
                                {0x6F, 0x00, USIMM_SW_TECH_ERROR,      },
                                {0x6F, 0xFF, USIMM_SW_OTHER_ERROR      },
                                {0x98, 0x34, USIMM_SW_CDMA_AUTN_ERROR  },
                            };

/*Usim SW字节检查*/
USIMM_SWCHECK_ST gausUsimSWCheck[USIMM_USIMSW_MAXNUMBER] =
                            {
                                {0x90, 0x00, USIMM_SW_OK,                },
                                {0x61, 0xFF, USIMM_SW_OK_WITH_RESOPNSE,  },
                                {0x91, 0xFF, USIMM_SW_OK_WITH_SAT,       },
                                {0x93, 0x00, USIMM_SW_CARD_BUSY,         },
                                {0x98, 0x50, USIMM_SW_INCREACE_ERROR,    },
                                {0x98, 0x62, USIMM_SW_AUTN_ERROR ,       },
                                {0x62, 0xFF, USIMM_SW_WARNING,           },
                                {0x63, 0xC0, USIMM_SW_CMD_REMAINTIME,    },
                                {0x63, 0xFF, USIMM_SW_WARNING,           },
                                {0x64, 0x00, USIMM_SW_MEMORY_ERROR,      },
                                {0x65, 0x00, USIMM_SW_MEMORY_ERROR,      },
                                {0x65, 0x81, USIMM_SW_MEMORY_ERROR,      },
                                {0x67, 0x00, USIMM_SW_CMD_ERROR,         },
                                {0x67, 0xFF, USIMM_SW_P3_ERROR,          },
                                {0x68, 0x00, USIMM_SW_CLA_ERROR,         },
                                {0x68, 0x81, USIMM_SW_CHANNEL_NOSUPPORT, },
                                {0x68, 0x82, USIMM_SW_SECURITY_ERROR,    },
                                {0x69, 0x00, USIMM_SW_OTHER_ERROR,       },
                                {0x69, 0x81, USIMM_SW_FILETYPE_ERROR,    },
                                {0x69, 0x82, USIMM_SW_SECURITY_ERROR,    },
                                {0x69, 0x83, USIMM_SW_PIN_BLOCK,         },
                                {0x69, 0x84, USIMM_SW_PINNUMBER_ERROR,   },
                                {0x69, 0x85, USIMM_SW_FILESTATUS_ERROR,  },
                                {0x69, 0x86, USIMM_SW_NOFILE_SELECT,     },
                                {0x69, 0x89, USIMM_SW_COMMAND_ERROR,     },
                                {0x6A, 0x80, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x81, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x82, USIMM_SW_NOFILE_FOUND,      },
                                {0x6A, 0x83, USIMM_SW_NORECORD_FOUND,    },
                                {0x6A, 0x84, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x86, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x87, USIMM_SW_CMD_ERROR,         },
                                {0x6A, 0x88, USIMM_SW_CMD_ERROR,         },
                                {0x6B, 0x00, USIMM_SW_CMD_ERROR,         },
                                {0x6C, 0xFF, USIMM_SW_P3_ERROR,          },
                                {0x6E, 0x00, USIMM_SW_CLA_ERROR,         },
                                {0x6F, 0x00, USIMM_SW_TECH_ERROR,        },
                                {0x6F, 0xFF, USIMM_SW_OTHER_ERROR        },
                                {0x98, 0x63, USIMM_SW_EXPIRED_ERROR      },
                                {0x98, 0x34, USIMM_SW_CDMA_AUTN_ERROR    },
                            };

/* ISIM服务状态位对应到USIM UST上的索引 */

/*lint -e656*/
const VOS_UINT8 g_aucServIsimToUsim[] =
/*lint +e656*/
                            {
                                0,                  /* ISIM_SVR_PCSCF_ADDR */
                                USIM_SVR_GBA,       /* ISIM_SVR_GBA */
                                0,                  /* ISIM_SVR_HTTP_DIGEST */
                                USIM_SVR_GBAKEY_EM, /* ISIM_SVR_LOCAL_GBA */
                                0,                  /* ISIM_SVR_IMS_PCSCF */
                                USIM_SVR_SMS,       /* ISIM_SVR_SMS */
                                USIM_SVR_SMSR,      /* ISIM_SVR_SMSR */
                                0,                  /* ISIM_SVR_SOI */
                                USIM_SVR_CTRL_IMS,  /* ISIM_SVR_COMM_CTRL */
                                USIM_SVR_ACCESS_IMS /* ISIM_SVR_UICC_IMS */
                            };


/*Usim 卡初始化过程函数列表*/
USIMM_CARD_INIT_FUNC g_aUsimInitCardProcFuncTbl[USIMM_INIT_USIM_CARD_NUM]=
{
    {VOS_NULL_PTR                   },
    {USIMM_InitUsimGlobal           },
    {USIMM_InsertNoNeedPinFileToPool},
    {USIMM_UsimProfileDownload      },
    {USIMM_Select3GApp              },
    {USIMM_SelectUiccADF            },
    {USIMM_InitCardPINInfo          },
    {USIMM_AdjudgeCardState         },
    {USIMM_InitUsimEccFile          },
    {USIMM_InsertLPFileToPool       },
    {USIMM_InitUsimCardFileMap      },
    {USIMM_OpenChannelForCSIM       }
};

/*Sim 卡初始化过程函数列表*/
USIMM_CARD_INIT_FUNC g_aSimInitCardProcFuncTbl[USIMM_INIT_SIM_CARD_NUM]=
{
    {VOS_NULL_PTR                   },
    {USIMM_InitSimGlobal            },
    {USIMM_Select2GApp              },
    {USIMM_InsertNoNeedPinFileToPool},
    {USIMM_InitCardPINInfo          },
    {USIMM_AdjudgeCardState         },
    {USIMM_InitSimEccFile           },
    {USIMM_InsertLPFileToPool       },
    {USIMM_InitSimCardFileMap       }
};

/*初始化卡的过程函数入口控制*/
USIMM_CARD_INIT_TBL_ST g_aCardInitTbl[USIMM_CARD_INIT_TBL_SIZE]=
{
    {g_aUsimInitCardProcFuncTbl, USIMM_INIT_USIM_CARD_NUM},
    {g_aSimInitCardProcFuncTbl,  USIMM_INIT_SIM_CARD_NUM}
};

USIMM_FILEID_PATHSTR_TABLE_STRU g_stUSIMMFilePathTable[USIMM_DEF_FILEID_BUTT] =
{
    {USIMM_UNLIMIT_AUTO,         USIMM_MF_STR               },            /*USIMM_MF_ID               */
    {USIMM_UNLIMIT_AUTO,         USIMM_DIR_STR              },            /*USIMM_DIR_ID              */
    {USIMM_UNLIMIT_AUTO,         USIMM_ICCID_STR            },            /*USIMM_ICCID_ID            */
    {USIMM_UNLIMIT_AUTO,         USIMM_PL_STR               },            /*USIMM_PL_ID               */
    {USIMM_UNLIMIT_AUTO,         USIMM_ARR_STR              },            /*USIMM_ARR_ID              */
    {USIMM_GUTL_APP,             USIMM_USIM_STR             },            /*USIMM_USIM_ID             */
    {USIMM_GUTL_APP,             USIMM_USIM_EFLI_STR        },            /*USIMM_USIM_EFLI_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFARR_STR       },            /*USIMM_USIM_EFARR_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFIMSI_STR      },            /*USIMM_USIM_EFIMSI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFKEYS_STR      },            /*USIMM_USIM_EFKEYS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFKEYSPS_STR    },            /*USIMM_USIM_EFKEYSPS_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFDCK_STR       },            /*USIMM_USIM_EFDCK_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHPPLMN_STR    },            /*USIMM_USIM_EFHPPLMN_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCNL_STR       },            /*USIMM_USIM_EFCNL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACMMAX_STR    },            /*USIMM_USIM_EFACMMAX_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUST_STR       },            /*USIMM_USIM_EFUST_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACM_STR       },            /*USIMM_USIM_EFACM_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFFDN_STR       },            /*USIMM_USIM_EFFDN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMS_STR       },            /*USIMM_USIM_EFSMS_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGID1_STR      },            /*USIMM_USIM_EFGID1_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGID2_STR      },            /*USIMM_USIM_EFGID2_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMSISDN_STR    },            /*USIMM_USIM_EFMSISDN_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPUCT_STR      },            /*USIMM_USIM_EFPUCT_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMSP_STR      },            /*USIMM_USIM_EFSMSP_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMSS_STR      },            /*USIMM_USIM_EFSMSS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCBMI_STR      },            /*USIMM_USIM_EFCBMI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSPN_STR       },            /*USIMM_USIM_EFSPN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSMSR_STR      },            /*USIMM_USIM_EFSMSR_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCBMID_STR     },            /*USIMM_USIM_EFCBMID_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSDN_STR       },            /*USIMM_USIM_EFSDN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT2_STR      },            /*USIMM_USIM_EFEXT2_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT3_STR      },            /*USIMM_USIM_EFEXT3_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFBDN_STR       },            /*USIMM_USIM_EFBDN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT5_STR      },            /*USIMM_USIM_EFEXT5_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCCP2_STR      },            /*USIMM_USIM_EFCCP2_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCBMIR_STR     },            /*USIMM_USIM_EFCBMIR_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT4_STR      },            /*USIMM_USIM_EFEXT4_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEST_STR       },            /*USIMM_USIM_EFEST_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACL_STR       },            /*USIMM_USIM_EFACL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCMI_STR       },            /*USIMM_USIM_EFCMI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSTART_HFN_STR },            /*USIMM_USIM_EFSTART_HFN_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFTHRESHOL_STR  },            /*USIMM_USIM_EFTHRESHOL_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPLMNWACT_STR  },            /*USIMM_USIM_EFPLMNWACT_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOPLMNWACT_STR },            /*USIMM_USIM_EFOPLMNWACT_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHPLMNwACT_STR },            /*USIMM_USIM_EFHPLMNwACT_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPSLOCI_STR    },            /*USIMM_USIM_EFPSLOCI_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACC_STR       },            /*USIMM_USIM_EFACC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFFPLMN_STR     },            /*USIMM_USIM_EFFPLMN_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFLOCI_STR      },            /*USIMM_USIM_EFLOCI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFICI_STR       },            /*USIMM_USIM_EFICI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCI_STR       },            /*USIMM_USIM_EFOCI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFICT_STR       },            /*USIMM_USIM_EFICT_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCT_STR       },            /*USIMM_USIM_EFOCT_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFAD_STR        },            /*USIMM_USIM_EFAD_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVGCS_STR      },            /*USIMM_USIM_EFVGCS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVGCSS_STR     },            /*USIMM_USIM_EFVGCSS_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVBS_STR       },            /*USIMM_USIM_EFVBS_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVBSS_STR      },            /*USIMM_USIM_EFVBSS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEMLPP_STR     },            /*USIMM_USIM_EFEMLPP_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFAAEM_STR      },            /*USIMM_USIM_EFAAEM_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFECC_STR       },            /*USIMM_USIM_EFECC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHIDDENKEY_STR },            /*USIMM_USIM_EFHIDDENKEY_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNETPAR_STR    },            /*USIMM_USIM_EFNETPAR_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPNN_STR       },            /*USIMM_USIM_EFPNN_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOPL_STR       },            /*USIMM_USIM_EFOPL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMBDN_STR      },            /*USIMM_USIM_EFMBDN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT6_STR      },            /*USIMM_USIM_EFEXT6_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMBI_STR       },            /*USIMM_USIM_EFMBI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMWIS_STR      },            /*USIMM_USIM_EFMWIS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCFIS_STR      },            /*USIMM_USIM_EFCFIS_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT7_STR      },            /*USIMM_USIM_EFEXT7_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSPDI_STR      },            /*USIMM_USIM_EFSPDI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSN_STR      },            /*USIMM_USIM_EFMMSN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEXT8_STR      },            /*USIMM_USIM_EFEXT8_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSICP_STR    },            /*USIMM_USIM_EFMMSICP_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSUP_STR     },            /*USIMM_USIM_EFMMSUP_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMMSUCP_STR    },            /*USIMM_USIM_EFMMSUCP_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNIA_STR       },            /*USIMM_USIM_EFNIA_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVGCSCA_STR    },            /*USIMM_USIM_EFVGCSCA_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFVBSCA_STR     },            /*USIMM_USIM_EFVBSCA_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGBAP_STR      },            /*USIMM_USIM_EFGBAP_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMSK_STR       },            /*USIMM_USIM_EFMSK_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMUK_STR       },            /*USIMM_USIM_EFMUK_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEHPLMN_STR    },            /*USIMM_USIM_EFEHPLMN_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFGBANL_STR     },            /*USIMM_USIM_EFGBANL_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEHPLMNPI_STR  },            /*USIMM_USIM_EFEHPLMNPI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFLRPLMNSI_STR  },            /*USIMM_USIM_EFLRPLMNSI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNAFKCA_STR    },            /*USIMM_USIM_EFNAFKCA_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSPNI_STR      },            /*USIMM_USIM_EFSPNI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPNNI_STR      },            /*USIMM_USIM_EFPNNI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNCPIP_STR     },            /*USIMM_USIM_EFNCPIP_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEPSLOCI_STR   },            /*USIMM_USIM_EFEPSLOCI_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_EFEPSNSC_STR    },            /*USIMM_USIM_EFEPSNSC_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUFC_STR       },            /*USIMM_USIM_EFUFC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUICCIARI_STR  },            /*USIMM_USIM_EFUICCIARI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_EFNASCONFIG_STR },            /*USIMM_USIM_EFNASCONFIG_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPWS_STR       },            /*USIMM_USIM_EFPWS_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_DFPHONEBOOK_STR },            /*USIMM_USIM_DFPHONEBOOK_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPSC_STR       },            /*USIMM_USIM_EFPSC_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCC_STR        },            /*USIMM_USIM_EFCC_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPUID_STR      },            /*USIMM_USIM_EFPUID_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPBR_STR       },            /*USIMM_USIM_EFPBR_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_DFGSM_ACCESS_STR},            /*USIMM_USIM_DFGSM_ACCESS_ID*/
    {USIMM_GUTL_APP,             USIMM_USIM_EFKC_STR        },            /*USIMM_USIM_EFKC_ID        */
    {USIMM_GUTL_APP,             USIMM_USIM_EFKCGPRS_STR    },            /*USIMM_USIM_EFKCGPRS_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCPBCCH_STR    },            /*USIMM_USIM_EFCPBCCH_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFINVSCAN_STR   },            /*USIMM_USIM_EFINVSCAN_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_DFMEXE_STR      },            /*USIMM_USIM_DFMEXE_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFMexE_ST_STR   },            /*USIMM_USIM_EFMexE_ST_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_EFORPK_STR      },            /*USIMM_USIM_EFORPK_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFARPK_STR      },            /*USIMM_USIM_EFARPK_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFTPRK_STR      },            /*USIMM_USIM_EFTPRK_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_DFSOLSA_STR     },            /*USIMM_USIM_DFSOLSA_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSAI_STR       },            /*USIMM_USIM_EFSAI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFSLL_STR       },            /*USIMM_USIM_EFSLL_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_DFWLAN_STR      },            /*USIMM_USIM_DFWLAN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFPSEUDO_STR    },            /*USIMM_USIM_EFPSEUDO_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUPLMNWLAN_STR },            /*USIMM_USIM_EFUPLMNWLAN_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EF0PLMNWLAN_STR },            /*USIMM_USIM_EF0PLMNWLAN_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFUWSIDL_STR    },            /*USIMM_USIM_EFUWSIDL_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOWSIDL_STR    },            /*USIMM_USIM_EFOWSIDL_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWRI_STR       },            /*USIMM_USIM_EFWRI_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHWSIDL_STR    },            /*USIMM_USIM_EFHWSIDL_ID    */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWEHPLMNPI_STR },            /*USIMM_USIM_EFWEHPLMNPI_ID */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWHPI_STR      },            /*USIMM_USIM_EFWHPI_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFWLRPLMN_STR   },            /*USIMM_USIM_EFWLRPLMN_ID   */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHPLMNDAI_STR  },            /*USIMM_USIM_EFHPLMNDAI_ID  */
    {USIMM_GUTL_APP,             USIMM_USIM_DFHNB_STR       },            /*USIMM_USIM_DFHNB_ID       */
    {USIMM_GUTL_APP,             USIMM_USIM_EFACSGL_STR     },            /*USIMM_USIM_EFACSGL_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFCSGT_STR      },            /*USIMM_USIM_EFCSGT_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFHNBN_STR      },            /*USIMM_USIM_EFHNBN_ID      */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCSGL_STR     },            /*USIMM_USIM_EFOCSGL_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOCSGT_STR     },            /*USIMM_USIM_EFOCSGT_ID     */
    {USIMM_GUTL_APP,             USIMM_USIM_EFOHNBN_STR     },            /*USIMM_USIM_EFOHNBN_ID     */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_STR             },            /*USIMM_TELE_ID             */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFADN_STR       },            /*USIMM_TELE_EFADN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFFDN_STR       },            /*USIMM_TELE_EFFDN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMS_STR       },            /*USIMM_TELE_EFSMS_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFCCP_STR       },            /*USIMM_TELE_EFCCP_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMSISDN_STR    },            /*USIMM_TELE_EFMSISDN_ID    */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMSP_STR      },            /*USIMM_TELE_EFSMSP_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMSS_STR      },            /*USIMM_TELE_EFSMSS_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFLND_STR       },            /*USIMM_TELE_EFLND_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSMSR_STR      },            /*USIMM_TELE_EFSMSR_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSDN_STR       },            /*USIMM_TELE_EFSDN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT1_STR      },            /*USIMM_TELE_EFEXT1_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT2_STR      },            /*USIMM_TELE_EFEXT2_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT3_STR      },            /*USIMM_TELE_EFEXT3_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFBDN_STR       },            /*USIMM_TELE_EFBDN_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFEXT4_STR      },            /*USIMM_TELE_EFEXT4_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFECCP_STR      },            /*USIMM_TELE_EFECCP_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFRMA_STR       },            /*USIMM_TELE_EFRMA_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFSUME_STR      },            /*USIMM_TELE_EFSUME_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFICE_DN_STR    },            /*USIMM_TELE_EFICE_DN_ID    */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFICE_FF_STR    },            /*USIMM_TELE_EFICE_FF_ID    */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFPSISMSC_STR   },            /*USIMM_TELE_EFPSISMSC_ID   */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_STR      },            /*USIMM_TELE_DFGRAP_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_EFIMG_STR},            /*USIMM_TELE_DFGRAP_EFIMG_ID*/
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_EFICEGRAPH_STR},       /*USIMM_TELE_DFGRAP_EFICEGRA*/
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFGRAP_EFLAUNCHSCWS_STR},     /*USIMM_TELE_DFGRAP_EFLUNCH */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_STR        },            /*USIMM_TELE_DFPB_ID        */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFPSC_STR  },            /*USIMM_TELE_DFPB_EFPSC_ID  */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFCC_STR   },            /*USIMM_TELE_DFPB_EFCC_ID   */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFPUID_STR },            /*USIMM_TELE_DFPB_EFPUID_ID */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFPB_EFPBR_STR  },            /*USIMM_TELE_DFPB_EFPBR_ID  */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMM_STR        },            /*USIMM_TELE_DFMM_ID        */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMM_EFMML_STR  },            /*USIMM_TELE_DFMM_EFMML_ID  */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMUM_EFMMDF_STR},            /*USIMM_TELE_DFMUM_EFMMDF_ID*/
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_DFMSS_STR       },            /*USIMM_TELE_DFMSS_ID       */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMLPL_STR      },            /*USIMM_TELE_EFMLPL_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMSPL_STR      },            /*USIMM_TELE_EFMSPL_ID      */
    {USIMM_UNLIMIT_AUTO,         USIMM_TELE_EFMMSSMODE_STR  },            /*USIMM_TELE_EFMMSSMODE_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_STR             },            /*USIMM_CSIM_ID             */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCOUNT_STR     },            /*USIMM_CSIM_EFCOUNT_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFIMSIM_STR     },            /*USIMM_CSIM_EFIMSIM_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFIMSIT_STR     },            /*USIMM_CSIM_EFIMSIT_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFTMSI_STR      },            /*USIMM_CSIM_EFTMSI_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAH_STR        },            /*USIMM_CSIM_EFAH_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAOP_STR       },            /*USIMM_CSIM_EFAOP_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFALOC_STR      },            /*USIMM_CSIM_EFALOC_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCDMAHOME_STR  },            /*USIMM_CSIM_EFCDMAHOME_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFZNREGI_STR    },            /*USIMM_CSIM_EFZNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSNREGI_STR    },            /*USIMM_CSIM_EFSNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFDISTREGI_STR  },            /*USIMM_CSIM_EFDISTREGI_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFACCOLC_STR    },            /*USIMM_CSIM_EFACCOLC_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFTERM_STR      },            /*USIMM_CSIM_EFTERM_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSSCI_STR      },            /*USIMM_CSIM_EFSSCI_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFACP_STR       },            /*USIMM_CSIM_EFACP_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPRL_STR       },            /*USIMM_CSIM_EFPRL_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFRUIMID_STR    },            /*USIMM_CSIM_EFRUIMID_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCSIMST_STR    },            /*USIMM_CSIM_EFCSIMST_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPC_STR       },            /*USIMM_CSIM_EFSPC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFOTAPASPC_STR  },            /*USIMM_CSIM_EFOTAPASPC_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFNAMLOCK_STR   },            /*USIMM_CSIM_EFNAMLOCK_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFOTA_STR       },            /*USIMM_CSIM_EFOTA_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSP_STR        },            /*USIMM_CSIM_EFSP_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFESNMEID_STR   },            /*USIMM_CSIM_EFESNMEID_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFLI_STR        },            /*USIMM_CSIM_EFLI_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFFDN_STR       },            /*USIMM_CSIM_EFFDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMS_STR       },            /*USIMM_CSIM_EFSMS_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMSP_STR      },            /*USIMM_CSIM_EFSMSP_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMSS_STR      },            /*USIMM_CSIM_EFSMSS_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSSFC_STR      },            /*USIMM_CSIM_EFSSFC_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPN_STR       },            /*USIMM_CSIM_EFSPN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFUSGIND_STR    },            /*USIMM_CSIM_EFUSGIND_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAD_STR        },            /*USIMM_CSIM_EFAD_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMDN_STR       },            /*USIMM_CSIM_EFMDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMAXPRL_STR    },            /*USIMM_CSIM_EFMAXPRL_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPCS_STR      },            /*USIMM_CSIM_EFSPCS_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFECC_STR       },            /*USIMM_CSIM_EFECC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFME3GPDOPC_STR },            /*USIMM_CSIM_EFME3GPDOPC_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EF3GPDOPM_STR   },            /*USIMM_CSIM_EF3GPDOPM_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPCAP_STR    },            /*USIMM_CSIM_EFSIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPCAP_STR    },            /*USIMM_CSIM_EFMIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPUPP_STR    },            /*USIMM_CSIM_EFSIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPUPP_STR    },            /*USIMM_CSIM_EFMIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPSP_STR     },            /*USIMM_CSIM_EFSIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPSP_STR     },            /*USIMM_CSIM_EFMIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSIPPAPSS_STR  },            /*USIMM_CSIM_EFSIPPAPSS_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPUZL_STR      },            /*USIMM_CSIM_EFPUZL_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMAXPUZL_STR   },            /*USIMM_CSIM_EFMAXPUZL_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMECRP_STR     },            /*USIMM_CSIM_EFMECRP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHRPDCAP_STR   },            /*USIMM_CSIM_EFHRPDCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHRPDUPP_STR   },            /*USIMM_CSIM_EFHRPDUPP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCSSPR_STR     },            /*USIMM_CSIM_EFCSSPR_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFATC_STR       },            /*USIMM_CSIM_EFATC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEPRL_STR      },            /*USIMM_CSIM_EFEPRL_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSCFG_STR  },            /*USIMM_CSIM_EFBCSMSCFG_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSPREF_STR },            /*USIMM_CSIM_EFBCSMSPREF_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSTABLE_STR},            /*USIMM_CSIM_EFBCSMSTABLE_ID*/
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBCSMSP_STR    },            /*USIMM_CSIM_EFBCSMSP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFBAKPARA_STR   },            /*USIMM_CSIM_EFBAKPARA_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFUPBAKPARA_STR },            /*USIMM_CSIM_EFUPBAKPARA_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSN_STR      },            /*USIMM_CSIM_EFMMSN_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT8_STR      },            /*USIMM_CSIM_EFEXT8_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSICP_STR    },            /*USIMM_CSIM_EFMMSICP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSUP_STR     },            /*USIMM_CSIM_EFMMSUP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSUCP_STR    },            /*USIMM_CSIM_EFMMSUCP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAUTHCAP_STR   },            /*USIMM_CSIM_EFAUTHCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EF3GCIK_STR     },            /*USIMM_CSIM_EF3GCIK_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFDCK_STR       },            /*USIMM_CSIM_EFDCK_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFGID1_STR      },            /*USIMM_CSIM_EFGID1_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFGID2_STR      },            /*USIMM_CSIM_EFGID2_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCDMACNL_STR   },            /*USIMM_CSIM_EFCDMACNL_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHOMETAG_STR   },            /*USIMM_CSIM_EFHOMETAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFGROUPTAG_STR  },            /*USIMM_CSIM_EFGROUPTAG_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSPECTAG_STR   },            /*USIMM_CSIM_EFSPECTAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCALLPROMPT_STR},            /*USIMM_CSIM_EFCALLPROMPT_ID*/
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSFEUIMID_STR  },            /*USIMM_CSIM_EFSFEUIMID_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEST_STR       },            /*USIMM_CSIM_EFEST_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFHIDDENKEY_STR },            /*USIMM_CSIM_EFHIDDENKEY_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFLCSVER_STR    },            /*USIMM_CSIM_EFLCSVER_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFLCSCP_STR     },            /*USIMM_CSIM_EFLCSCP_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSDN_STR       },            /*USIMM_CSIM_EFSDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT2_STR      },            /*USIMM_CSIM_EFEXT2_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT3_STR      },            /*USIMM_CSIM_EFEXT3_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFICI_STR       },            /*USIMM_CSIM_EFICI_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFOCI_STR       },            /*USIMM_CSIM_EFOCI_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFEXT5_STR      },            /*USIMM_CSIM_EFEXT5_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCCP2_STR      },            /*USIMM_CSIM_EFCCP2_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFAPPLAB_STR    },            /*USIMM_CSIM_EFAPPLAB_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMODEL_STR     },            /*USIMM_CSIM_EFMODEL_ID     */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFRC_STR        },            /*USIMM_CSIM_EFRC_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFSMSCAP_STR    },            /*USIMM_CSIM_EFSMSCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMIPFLAGS_STR  },            /*USIMM_CSIM_EFMIPFLAGS_ID  */
    {USIMM_CDMA_APP,             USIMM_CSIM_EF3GPDUPPEXT_STR},            /*USIMM_CSIM_EF3GPDUPPEXT_ID*/
    {USIMM_CDMA_APP,             USIMM_CSIM_EFIPV6CAP_STR   },            /*USIMM_CSIM_EFIPV6CAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFTCPCFG_STR    },            /*USIMM_CSIM_EFTCPCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFDGC_STR       },            /*USIMM_CSIM_EFDGC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFWAPBWCP_STR   },            /*USIMM_CSIM_EFWAPBWCP_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFWAPBWBM_STR   },            /*USIMM_CSIM_EFWAPBWBM_ID   */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFMMSCFG_STR    },            /*USIMM_CSIM_EFMMSCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFJDL_STR       },            /*USIMM_CSIM_EFJDL_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_DFPHONEBOOK_STR },            /*USIMM_CSIM_DFPHONEBOOK_ID */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPSC_STR       },            /*USIMM_CSIM_EFPSC_ID       */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFCC_STR        },            /*USIMM_CSIM_EFCC_ID        */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPUID_STR      },            /*USIMM_CSIM_EFPUID_ID      */
    {USIMM_CDMA_APP,             USIMM_CSIM_EFPBR_STR       },            /*USIMM_CSIM_EFPBR_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_STR              },            /*USIMM_GSM_ID              */
    {USIMM_GUTL_APP,             USIMM_GSM_EFLP_STR         },            /*USIMM_GSM_EFLP_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFIMSI_STR       },            /*USIMM_GSM_EFIMSI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFKC_STR         },            /*USIMM_GSM_EFKC_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFDCK_STR        },            /*USIMM_GSM_EFDCK_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPLMNSEL_STR    },            /*USIMM_GSM_EFPLMNSEL_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_EFHPLMN_STR      },            /*USIMM_GSM_EFHPLMN_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCNL_STR        },            /*USIMM_GSM_EFCNL_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFACMMAX_STR     },            /*USIMM_GSM_EFACMMAX_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSST_STR        },            /*USIMM_GSM_EFSST_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFACM_STR        },            /*USIMM_GSM_EFACM_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFGID1_STR       },            /*USIMM_GSM_EFGID1_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFGID2_STR       },            /*USIMM_GSM_EFGID2_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPUCT_STR       },            /*USIMM_GSM_EFPUCT_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCBMI_STR       },            /*USIMM_GSM_EFCBMI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSPN_STR        },            /*USIMM_GSM_EFSPN_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCBMID_STR      },            /*USIMM_GSM_EFCBMID_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFBCCH_STR       },            /*USIMM_GSM_EFBCCH_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFACC_STR        },            /*USIMM_GSM_EFACC_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFFPLMN_STR      },            /*USIMM_GSM_EFFPLMN_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFLOCI_STR       },            /*USIMM_GSM_EFLOCI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFAD_STR         },            /*USIMM_GSM_EFAD_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPHASE_STR      },            /*USIMM_GSM_EFPHASE_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVGCS_STR       },            /*USIMM_GSM_EFVGCS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVGCSS_STR      },            /*USIMM_GSM_EFVGCSS_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVBS_STR        },            /*USIMM_GSM_EFVBS_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVBSS_STR       },            /*USIMM_GSM_EFVBSS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEMLPP_STR      },            /*USIMM_GSM_EFEMLPP_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFAAEM_STR       },            /*USIMM_GSM_EFAAEM_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFECC_STR        },            /*USIMM_GSM_EFECC_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCBMIR_STR      },            /*USIMM_GSM_EFCBMIR_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFNIA_STR        },            /*USIMM_GSM_EFNIA_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFKCGPRS_STR     },            /*USIMM_GSM_EFKCGPRS_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFLOCIGPRS_STR   },            /*USIMM_GSM_EFLOCIGPRS_ID   */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSUME_STR       },            /*USIMM_GSM_EFSUME_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCMI_STR        },            /*USIMM_GSM_EFCMI_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPLMNWACT_STR   },            /*USIMM_GSM_EFPLMNWACT_ID   */
    {USIMM_GUTL_APP,             USIMM_GSM_EFOPLMNWACT_STR  },            /*USIMM_GSM_EFOPLMNWACT_ID  */
    {USIMM_GUTL_APP,             USIMM_GSM_EFHPLMNACT_STR   },            /*USIMM_GSM_EFHPLMNACT_ID   */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCPBCCH_STR     },            /*USIMM_GSM_EFCPBCCH_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFINVSCAN_STR    },            /*USIMM_GSM_EFINVSCAN_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_EFPNN_STR        },            /*USIMM_GSM_EFPNN_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFOPL_STR        },            /*USIMM_GSM_EFOPL_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMBDN_STR       },            /*USIMM_GSM_EFMBDN_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEXT6_STR       },            /*USIMM_GSM_EFEXT6_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMBI_STR        },            /*USIMM_GSM_EFMBI_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMWIS_STR       },            /*USIMM_GSM_EFMWIS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCFIS_STR       },            /*USIMM_GSM_EFCFIS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEXT7_STR       },            /*USIMM_GSM_EFEXT7_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSPDI_STR       },            /*USIMM_GSM_EFSPDI_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSN_STR       },            /*USIMM_GSM_EFMMSN_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFEXT8_STR       },            /*USIMM_GSM_EFEXT8_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSICP_STR     },            /*USIMM_GSM_EFMMSICP_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSUP_STR      },            /*USIMM_GSM_EFMMSUP_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMMSUCP_STR     },            /*USIMM_GSM_EFMMSUCP_ID     */
    {USIMM_GUTL_APP,             USIMM_GSM_EFVMW_STR        },            /*USIMM_GSM_EFVMW_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFSVCSTBL_STR    },            /*USIMM_GSM_EFSVCSTBL_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCFF_STR        },            /*USIMM_GSM_EFCFF_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFONS_STR        },            /*USIMM_GSM_EFONS_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCSP_STR        },            /*USIMM_GSM_EFCSP_ID        */
    {USIMM_GUTL_APP,             USIMM_GSM_EFCPHSI_STR      },            /*USIMM_GSM_EFCPHSI_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_EFMN_STR         },            /*USIMM_GSM_EFMN_ID         */
    {USIMM_GUTL_APP,             USIMM_GSM_EFONSS_STR       },            /*USIMM_GSM_EFONSS_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_EFINFONUM_STR    },            /*USIMM_GSM_EFINFONUM_ID    */
    {USIMM_GUTL_APP,             USIMM_GSM_DFSOLSA_STR      },            /*USIMM_GSM_DFSOLSA_ID      */
    {USIMM_GUTL_APP,             USIMM_GSM_DFSOLSA_EFSAI_STR},            /*USIMM_GSM_DFSOLSA_EFSAI_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFSOLSA_EFSLL_STR},            /*USIMM_GSM_DFSOLSA_EFSLL_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_STR       },            /*USIMM_GSM_DFMEXE_ID       */
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFST_STR  },            /*USIMM_GSM_DFMEXE_EFST_ID  */
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFORPK_STR},            /*USIMM_GSM_DFMEXE_EFORPK_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFARPK_STR},            /*USIMM_GSM_DFMEXE_EFARPK_ID*/
    {USIMM_GUTL_APP,             USIMM_GSM_DFMEXE_EFTPRPK_STR},           /*USIMM_GSM_DFMEXE_EFTPRPK_I*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_STR           },            /*USIMM_ATTGSM_ID           */
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFTERMINALTBL_STR},         /*USIMM_ATTGSM_EFTERMINALTBL*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFACTINGHPLMN_STR},         /*USIMM_ATTGSM_EFACTINGHPLMN*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMENABLE_STR},           /*USIMM_ATTGSM_EFPRMENABLE_I*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMPARA_STR },            /*USIMM_ATTGSM_EFPRMPARA_ID */
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMOMCLR_STR},            /*USIMM_ATTGSM_EFPRMOMCLR_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMOMC_STR  },            /*USIMM_ATTGSM_EFPRMOMC_ID  */
    {USIMM_GUTL_APP,             USIMM_ATTGSM_EFPRMVERINFO_STR},          /*USIMM_ATTGSM_EFPRMVERINFO_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_STR          },            /*USIMM_ATTUSIM_ID          */
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFTERMINALTBL_STR},        /*USIMM_ATTUSIM_EFTERMINALTBL_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFACTINGHPLMN_STR},        /*USIMM_ATTUSIM_EFACTINGHPLM_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFRATMODE_STR},            /*USIMM_ATTUSIM_EFRATMODE_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMENABLE_STR},          /*USIMM_ATTUSIM_EFPRMENABLE_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMPARA_STR},            /*USIMM_ATTUSIM_EFPRMPARA_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMOMCLR_STR},           /*USIMM_ATTUSIM_EFPRMOMCLR_ID*/
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMOMC_STR },            /*USIMM_ATTUSIM_EFPRMOMC_ID */
    {USIMM_GUTL_APP,             USIMM_ATTUSIM_EFPRMVERINFO_STR},         /*USIMM_ATTUSIM_EFPRMVERINFO_ID*/
    {USIMM_CDMA_APP,             USIMM_CDMA_STR             },            /*USIMM_CDMA_ID             */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCOUNT_STR     },            /*USIMM_CDMA_EFCOUNT_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMSIM_STR     },            /*USIMM_CDMA_EFIMSIM_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMSIT_STR     },            /*USIMM_CDMA_EFIMSIT_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFTMSI_STR      },            /*USIMM_CDMA_EFTMSI_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAH_STR        },            /*USIMM_CDMA_EFAH_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAOP_STR       },            /*USIMM_CDMA_EFAOP_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFALOC_STR      },            /*USIMM_CDMA_EFALOC_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCDMAHOME_STR  },            /*USIMM_CDMA_EFCDMAHOME_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFZNREGI_STR    },            /*USIMM_CDMA_EFZNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSNREGI_STR    },            /*USIMM_CDMA_EFSNREGI_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDISTREGI_STR  },            /*USIMM_CDMA_EFDISTREGI_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFACCOLC_STR    },            /*USIMM_CDMA_EFACCOLC_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFTERM_STR      },            /*USIMM_CDMA_EFTERM_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSSCI_STR      },            /*USIMM_CDMA_EFSSCI_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFACP_STR       },            /*USIMM_CDMA_EFACP_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFPRL_STR       },            /*USIMM_CDMA_EFPRL_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFRUIMID_STR    },            /*USIMM_CDMA_EFRUIMID_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCST_STR       },            /*USIMM_CDMA_EFCST_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPC_STR       },            /*USIMM_CDMA_EFSPC_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFOTAPASPC_STR  },            /*USIMM_CDMA_EFOTAPASPC_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFNAMLOCK_STR   },            /*USIMM_CDMA_EFNAMLOCK_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFOTA_STR       },            /*USIMM_CDMA_EFOTA_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSP_STR        },            /*USIMM_CDMA_EFSP_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFESNMEIDME_STR },            /*USIMM_CDMA_EFESNMEIDME_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFREVISION_STR  },            /*USIMM_CDMA_EFREVISION_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFRUIMPL_STR    },            /*USIMM_CDMA_EFRUIMPL_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMS_STR       },            /*USIMM_CDMA_EFSMS_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMSP_STR      },            /*USIMM_CDMA_EFSMSP_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMSS_STR      },            /*USIMM_CDMA_EFSMSS_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSSFC_STR      },            /*USIMM_CDMA_EFSSFC_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPN_STR       },            /*USIMM_CDMA_EFSPN_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFUSGIND_STR    },            /*USIMM_CDMA_EFUSGIND_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAD_STR        },            /*USIMM_CDMA_EFAD_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMDN_STR       },            /*USIMM_CDMA_EFMDN_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMAXPRL_STR    },            /*USIMM_CDMA_EFMAXPRL_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPCS_STR      },            /*USIMM_CDMA_EFSPCS_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFECC_STR       },            /*USIMM_CDMA_EFECC_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFME3GPDOPC_STR },            /*USIMM_CDMA_EFME3GPDOPC_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EF3GPDOPM_STR   },            /*USIMM_CDMA_EF3GPDOPM_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPCAP_STR    },            /*USIMM_CDMA_EFSIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPCAP_STR    },            /*USIMM_CDMA_EFMIPCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPUPP_STR    },            /*USIMM_CDMA_EFSIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPUPP_STR    },            /*USIMM_CDMA_EFMIPUPP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPSP_STR     },            /*USIMM_CDMA_EFSIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPSP_STR     },            /*USIMM_CDMA_EFMIPSP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSIPPAPSS_STR  },            /*USIMM_CDMA_EFSIPPAPSS_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFPUZL_STR      },            /*USIMM_CDMA_EFPUZL_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMAXPUZL_STR   },            /*USIMM_CDMA_EFMAXPUZL_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMECRP_STR     },            /*USIMM_CDMA_EFMECRP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFHRPDCAP_STR   },            /*USIMM_CDMA_EFHRPDCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFHRPDUPP_STR   },            /*USIMM_CDMA_EFHRPDUPP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCSSPR_STR     },            /*USIMM_CDMA_EFCSSPR_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFACT_STR       },            /*USIMM_CDMA_EFACT_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFEPRL_STR      },            /*USIMM_CDMA_EFEPRL_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSOFG_STR  },            /*USIMM_CDMA_EFBCSMSOFG_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSPREF_STR },            /*USIMM_CDMA_EFBCSMSPREF_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSTBL_STR  },            /*USIMM_CDMA_EFBCSMSTBL_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBCSMSP_STR    },            /*USIMM_CDMA_EFBCSMSP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMPI_STR      },            /*USIMM_CDMA_EFIMPI_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDOMAIN_STR    },            /*USIMM_CDMA_EFDOMAIN_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIMPU_STR      },            /*USIMM_CDMA_EFIMPU_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFPCSCF_STR     },            /*USIMM_CDMA_EFPCSCF_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFBAKPARA_STR   },            /*USIMM_CDMA_EFBAKPARA_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFUPBAKPARA_STR },            /*USIMM_CDMA_EFUPBAKPARA_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSN_STR      },            /*USIMM_CDMA_EFMMSN_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFEXT8_STR      },            /*USIMM_CDMA_EFEXT8_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSICP_STR    },            /*USIMM_CDMA_EFMMSICP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSUP_STR     },            /*USIMM_CDMA_EFMMSUP_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSUCP_STR    },            /*USIMM_CDMA_EFMMSUCP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAUTHCAP_STR   },            /*USIMM_CDMA_EFAUTHCAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EF3GCIK_STR     },            /*USIMM_CDMA_EF3GCIK_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDCK_STR       },            /*USIMM_CDMA_EFDCK_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFGID1_STR      },            /*USIMM_CDMA_EFGID1_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFGID2_STR      },            /*USIMM_CDMA_EFGID2_ID      */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCDMACNL_STR   },            /*USIMM_CDMA_EFCDMACNL_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFHOMETAG_STR   },            /*USIMM_CDMA_EFHOMETAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFGROUPTAG_STR  },            /*USIMM_CDMA_EFGROUPTAG_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSPECTAG_STR   },            /*USIMM_CDMA_EFSPECTAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFCALLPROM_STR  },            /*USIMM_CDMA_EFCALLPROM_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSFEUIMID_STR  },            /*USIMM_CDMA_EFSFEUIMID_ID  */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFSMSCAP_STR    },            /*USIMM_CDMA_EFSMSCAP_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFIPV6CAP_STR   },            /*USIMM_CDMA_EFIPV6CAP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMIPFLAG_STR   },            /*USIMM_CDMA_EFMIPFLAG_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFTCPCFG_STR    },            /*USIMM_CDMA_EFTCPCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFDGC_STR       },            /*USIMM_CDMA_EFDGC_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFWAPBRCP_STR   },            /*USIMM_CDMA_EFWAPBRCP_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFWAPBRBM_STR   },            /*USIMM_CDMA_EFWAPBRBM_ID   */
    {USIMM_CDMA_APP,             USIMM_CDMA_EF3GPDUPPEX_STR },            /*USIMM_CDMA_EF3GPDUPPEX_ID */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMMSCFG_STR    },            /*USIMM_CDMA_EFMMSCFG_ID    */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFJDL_STR       },            /*USIMM_CDMA_EFJDL_ID       */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFMODEL_STR     },            /*USIMM_CDMA_EFMODEL_ID     */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFRC_STR        },            /*USIMM_CDMA_EFRC_ID        */
    {USIMM_CDMA_APP,             USIMM_CDMA_EFAPPLAB_STR    },            /*USIMM_CDMA_EFAPPLAB_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFIST_STR       },            /*USIMM_ISIM_EFIST_ID     */
    {USIMM_IMS_APP,              USIMM_ISIM_EFIMPI_STR      },            /*USIMM_ISIM_EFIMPI_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFDOMAIN_STR    },            /*USIMM_ISIM_EFDOMAIN_ID  */
    {USIMM_IMS_APP,              USIMM_ISIM_EFIMPU_STR      },            /*USIMM_ISIM_EFIMPU_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFAD_STR        },            /*USIMM_ISIM_EFAD_ID      */
    {USIMM_IMS_APP,              USIMM_ISIM_EFARR_STR       },            /*USIMM_ISIM_EFARR_ID     */
    {USIMM_IMS_APP,              USIMM_ISIM_EFPCSCF_STR     },            /*USIMM_ISIM_EFPCSCF_ID   */
    {USIMM_IMS_APP,              USIMM_ISIM_EFGBAP_STR      },            /*USIMM_ISIM_EFGBAP_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFGBANL_STR     },            /*USIMM_ISIM_EFGBANL_ID   */
    {USIMM_IMS_APP,              USIMM_ISIM_EFNAFKCA_STR    },            /*USIMM_ISIM_EFNAFKCA_ID  */
    {USIMM_IMS_APP,              USIMM_ISIM_EFUICCIARI_STR  },            /*USIMM_ISIM_EFUICCIARI_ID*/
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMS_STR       },            /*USIMM_ISIM_EFSMS_ID     */
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMSS_STR      },            /*USIMM_ISIM_EFSMSS_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMSR_STR      },            /*USIMM_ISIM_EFSMSR_ID    */
    {USIMM_IMS_APP,              USIMM_ISIM_EFSMSP_STR      },            /*USIMM_ISIM_EFSMSP_ID    */
 };

/*****************************************************************************
函 数 名  : USIMM_T1InitGlobalVar
功能描述  : T=1相关全局变量的初始化
输入参数  : VOS_VOID
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2013年10月22日
   作    者   : L00256032
   修改内容   : V9R1 T=1项目新增
*****************************************************************************/
VOS_VOID  USIMM_T1InitGlobalVar(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stUsimmT1CtrlCtx, 0, sizeof(g_stUsimmT1CtrlCtx));

    VOS_MemSet(&g_stT1SendDataInfo, 0, sizeof(g_stT1SendDataInfo));

    VOS_MemSet(&g_stT1RcvDataInfo, 0, sizeof(g_stT1RcvDataInfo));
    /*lint +e534*/

    /* BWT倍数初始化为1 */
    g_stUsimmT1CtrlCtx.ulBWTTimes = USIMM_T1_DEFAULT_WTX;

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
