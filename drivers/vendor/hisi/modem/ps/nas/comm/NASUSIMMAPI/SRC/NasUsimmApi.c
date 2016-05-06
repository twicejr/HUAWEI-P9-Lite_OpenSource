/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUsimmApi.c
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2013年6月3日
  最近修改   :
  功能描述   : NasUsimmApi.c文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasUsimmApi.h"
#include "NasSndUsimm.h"
#include "NasUsimmApiMntn.h"
#include "NasMmlCtx.h"

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
#include "MM_Share.h"
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_USIMMAPI_C

TAF_USIMM_VSIM_INFO_STRU             g_stNasVsimInfo;

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/


/*****************************************************************************
  5 变量定义
*****************************************************************************/
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-30, begin */
NAS_USIMM_SRVICES_TYPE_STRU g_NasUsimSrviceTypeTab[NAS_USIM_SVR_MAX_SERVICE] =
{
    {NAS_USIM_SVR_NONE,                     UICC_SVR_NONE,                  UICC_SVR_NONE},                 /* 0 */

    {NAS_USIM_SVR_LOCAL_PHONEBOOK,          UICC_SVR_NONE,                  USIM_SVR_LOCAL_PHONEBOOK},      /* 1 */
    {NAS_USIM_SVR_FDN,                      SIM_SVR_FDN,                    USIM_SVR_FDN},
    {NAS_USIM_SVR_EXT2,                     SIM_SVR_EXT2,                   USIM_SVR_EXT2},
    {NAS_USIM_SVR_SDN,                      SIM_SVR_SDN,                    USIM_SVR_SDN},
    {NAS_USIM_SVR_EXT3,                     SIM_SVR_EXT3,                   USIM_SVR_EXT3},
    {NAS_USIM_SVR_BDN,                      SIM_SVR_BDN,                    USIM_SVR_BDN},
    {NAS_USIM_SVR_EXT4,                     SIM_SVR_EXT4,                   USIM_SVR_EXT4},
    {NAS_USIM_SVR_OCI_OCT,                  UICC_SVR_NONE,                  USIM_SVR_OCI_OCT},
    {NAS_USIM_SVR_ICI_ICT,                  UICC_SVR_NONE,                  USIM_SVR_ICI_ICT},

    {NAS_USIM_SVR_SMS,                      SIM_SVR_SMS,                    USIM_SVR_SMS},                  /* 10 */
    {NAS_USIM_SVR_SMSR,                     SIM_SVR_SMS_REPORTS,            USIM_SVR_SMSR},
    {NAS_USIM_SVR_SMSP,                     SIM_SVR_SMS_PARA,               USIM_SVR_SMSP},
    {NAS_USIM_SVR_AOC,                      SIM_SVR_AOC,                    USIM_SVR_AOC},
    {NAS_USIM_SVR_CCP,                      SIM_SVR_CCP,                    USIM_SVR_CCP},
    {NAS_USIM_SVR_CBMI,                     SIM_SVR_CBMID,                  USIM_SVR_CBMI},
    {NAS_USIM_SVR_CBMIR,                    SIM_SVR_CBMIR,                  USIM_SVR_CBMIR},
    {NAS_USIM_SVR_GID1,                     SIM_SVR_GIDL1,                  USIM_SVR_GID1},
    {NAS_USIM_SVR_GID2,                     SIM_SVR_GIDL2,                  USIM_SVR_GID2},
    {NAS_USIM_SVR_SPN,                      SIM_SVR_SERVICE_PRO_NAME,       USIM_SVR_SPN},

    {NAS_USIM_SVR_UPLMN_SEL_WACT,           SIM_SVR_USER_CTRL_PLMN,         USIM_SVR_UPLMN_SEL_WACT},       /* 20 */
    {NAS_USIM_SVR_MSISDN,                   SIM_SVR_MSISDN,                 USIM_SVR_MSISDN},
    {NAS_USIM_SVR_IMAGE,                    SIM_SVR_IMG,                    USIM_SVR_IMAGE},
    {NAS_USIM_SVR_SOLSA,                    SIM_SVR_SOLSA,                  USIM_SVR_SOLSA},
    {NAS_USIM_SVR_ENH_ML_SVC,               SIM_SVR_ENH_ML_SVC,             USIM_SVR_ENH_ML_SVC},
    {NAS_USIM_SVR_AA_EMLPP,                 SIM_SVR_AUTO_ANSWER_FOR_EMLPP,  USIM_SVR_AA_EMLPP},
    {NAS_USIM_SVR_RFU1,                     SIM_SVR_RFU1,                   USIM_SVR_RFU1},
    {NAS_USIM_SVR_GSM_ACCESS_IN_USIM,       UICC_SVR_NONE,                  USIM_SVR_GSM_ACCESS_IN_USIM},
    {NAS_USIM_SVR_DATA_DL_SMSPP,            SIM_SVR_DD_VIA_SMS_PP,          USIM_SVR_DATA_DL_SMSPP},
    {NAS_USIM_SVR_DATA_DL_SMSCB,            SIM_SVR_DD_VIA_SMS_CB,          USIM_SVR_DATA_DL_SMSCB},

    {NAS_USIM_SVR_CALL_CONTROL,             SIM_SVR_CALL_CONTROL,           USIM_SVR_CALL_CONTROL},         /* 30 */
    {NAS_USIM_SVR_MOSMS_CONTROL,            SIM_SVR_MOSMC,                  USIM_SVR_MOSMS_CONTROL},
    {NAS_USIM_SVR_RUN_AT_CMD,               SIM_SVR_RUN_AT_CMD,             USIM_SVR_RUN_AT_CMD},
    {NAS_USIM_SVR_SET_ONE,                  UICC_SVR_NONE,                  USIM_SVR_SET_ONE},
    {NAS_USIM_SVR_EST,                      UICC_SVR_NONE,                  USIM_SVR_EST},
    {NAS_USIM_SVR_ACL,                      UICC_SVR_NONE,                  USIM_SVR_ACL},
    {NAS_USIM_SVR_DEPERSON_KEYS,            SIM_SVR_DPCK,                   USIM_SVR_DEPERSON_KEYS},
    {NAS_USIM_SVR_COOP_NETWK_LIST,          SIM_SVR_CONL,                   USIM_SVR_COOP_NETWK_LIST},
    {NAS_USIM_SVR_GSM_SECURITY_CONTEXT,     UICC_SVR_NONE,                  USIM_SVR_GSM_SECURITY_CONTEXT},
    {NAS_USIM_SVR_CPBCCH,                   SIM_SVR_CPBCCHI,                USIM_SVR_CPBCCH},

    {NAS_USIM_SVR_INV_SCAN,                 SIM_SVR_INV_SCAN,               USIM_SVR_INV_SCAN},             /* 40 */
    {NAS_USIM_SVR_MEXE,                     SIM_SVR_MEXE,                   USIM_SVR_MEXE},
    {NAS_USIM_SVR_OPLMN_SEL_WACT,           SIM_SVR_OPERATOR_CTRL_PLMN,     USIM_SVR_OPLMN_SEL_WACT},
    {NAS_USIM_SVR_HPLMN_WACT,               SIM_SVR_HPLMN,                  USIM_SVR_HPLMN_WACT},
    {NAS_USIM_SVR_EXT5,                     UICC_SVR_NONE,                  USIM_SVR_EXT5},
    {NAS_USIM_SVR_PLMN_NTWRK_NAME,          SIM_SVR_PLMNNN,                 USIM_SVR_PLMN_NTWRK_NAME},
    {NAS_USIM_SVR_OPLMN_LIST,               SIM_SVR_OPLMNL,                 USIM_SVR_OPLMN_LIST},
    {NAS_USIM_SVR_MAILBOX_DIAL,             SIM_SVR_MDN,                    USIM_SVR_MAILBOX_DIAL},
    {NAS_USIM_SVR_MSG_WAIT,                 SIM_SVR_MWIS,                   USIM_SVR_MSG_WAIT},
    {NAS_USIM_SVR_CALL_FWD_IND,             SIM_SVR_CFIS,                   USIM_SVR_CALL_FWD_IND},

    {NAS_USIM_SVR_RFU2,                     SIM_SVR_RFU2,                   USIM_SVR_RFU2},                  /* 50 */
    {NAS_USIM_SVR_SP_DISP_INFO,             SIM_SVR_SPDI,                   USIM_SVR_SP_DISP_INFO},
    {NAS_USIM_SVR_MMS,                      SIM_SVR_MMS,                    USIM_SVR_MMS},
    {NAS_USIM_SVR_EXT8,                     SIM_SVR_EXT8,                   USIM_SVR_EXT8},
    {NAS_USIM_SVR_GPRS_USIM,                UICC_SVR_NONE,                  USIM_SVR_GPRS_USIM},
    {NAS_USIM_SVR_MMS_USR_P,                SIM_SVR_MMS_UCP,                USIM_SVR_MMS_USR_P},
    {NAS_USIM_SVR_NIA,                      SIM_SVR_NID,                    USIM_SVR_NIA},
    {NAS_USIM_SVR_VGCS_GID_LIST,            SIM_SVR_EFVGCS_EFVGCSS,         USIM_SVR_VGCS_GID_LIST},
    {NAS_USIM_SVR_VBS_GID_LIST,             SIM_SVR_FVBS_EFVBSS,            USIM_SVR_VBS_GID_LIST},
    {NAS_USIM_SVR_PSEUDONYM,                UICC_SVR_NONE,                  USIM_SVR_PSEUDONYM},

    {NAS_USIM_SVR_UPLMN_WLAN_ACC,           UICC_SVR_NONE,                  USIM_SVR_UPLMN_WLAN_ACC},       /* 60 */
    {NAS_USIM_SVR_OPLMN_WLAN_ACC,           UICC_SVR_NONE,                  USIM_SVR_OPLMN_WLAN_ACC},
    {NAS_USIM_SVR_USER_CTRL_WSID,           UICC_SVR_NONE,                  USIM_SVR_USER_CTRL_WSID},
    {NAS_USIM_SVR_OPER_CTRL_WSID,           UICC_SVR_NONE,                  USIM_SVR_OPER_CTRL_WSID},
    {NAS_USIM_SVR_VGCS_SECURITY,            UICC_SVR_NONE,                  USIM_SVR_VGCS_SECURITY},
    {NAS_USIM_SVR_VBS_SECURITY,             UICC_SVR_NONE,                  USIM_SVR_VBS_SECURITY},
    {NAS_USIM_SVR_WLAN_REAUTH_ID,           UICC_SVR_NONE,                  USIM_SVR_WLAN_REAUTH_ID},
    {NAS_USIM_SVR_MM_STORAGE,               UICC_SVR_NONE,                  USIM_SVR_MM_STORAGE},
    {NAS_USIM_SVR_GBA,                      UICC_SVR_NONE,                  USIM_SVR_GBA},
    {NAS_USIM_SVR_MBMS_SECURITY,            UICC_SVR_NONE,                  USIM_SVR_MBMS_SECURITY},

    {NAS_USIM_SVR_DATA_DL_USSD,             UICC_SVR_NONE,                  USIM_SVR_DATA_DL_USSD},         /* 70 */
    {NAS_USIM_SVR_EHPLMN,                   UICC_SVR_NONE,                  USIM_SVR_EHPLMN},
    {NAS_USIM_SVR_TP_AFTER_UICC_ACT,        UICC_SVR_NONE,                  USIM_SVR_TP_AFTER_UICC_ACT},
    {NAS_USIM_SVR_EHPLMN_IND,               UICC_SVR_NONE,                  USIM_SVR_EHPLMN_IND},
    {NAS_USIM_SVR_RPLMN_LACT,               UICC_SVR_NONE,                  USIM_SVR_RPLMN_LACT},
    {NAS_USIM_SVR_OMA_BCAST_PROFILE,        UICC_SVR_NONE,                  USIM_SVR_OMA_BCAST_PROFILE},
    {NAS_USIM_SVR_GBAKEY_EM,                UICC_SVR_NONE,                  USIM_SVR_GBAKEY_EM},
    {NAS_USIM_SVR_TERMINAL_APP,             UICC_SVR_NONE,                  USIM_SVR_TERMINAL_APP},
    {NAS_USIM_SVR_SPN_ICON,                 UICC_SVR_NONE,                  USIM_SVR_SPN_ICON},
    {NAS_USIM_SVR_PNN_ICON,                 UICC_SVR_NONE,                  USIM_SVR_PNN_ICON},

    {NAS_USIM_SVR_CONNECT_SIM_IP,           UICC_SVR_NONE,                  USIM_SVR_CONNECT_SIM_IP},       /* 80 */
    {NAS_USIM_SVR_IWLEN_ID_LIST,            UICC_SVR_NONE,                  USIM_SVR_IWLEN_ID_LIST},
    {NAS_USIM_SVR_IWLEN_EHPLMN_IND,         UICC_SVR_NONE,                  USIM_SVR_IWLEN_EHPLMN_IND},
    {NAS_USIM_SVR_IWLEN_HPLMN_IND,          UICC_SVR_NONE,                  USIM_SVR_IWLEN_HPLMN_IND},
    {NAS_USIM_SVR_IWLEN_RPLMN,              UICC_SVR_NONE,                  USIM_SVR_IWLEN_RPLMN},
    {NAS_USIM_SVR_EPS_INFO,                 UICC_SVR_NONE,                  USIM_SVR_EPS_INFO},
    {NAS_USIM_SVR_CSG_COR_IND,              UICC_SVR_NONE,                  USIM_SVR_CSG_COR_IND},
    {NAS_USIM_SVR_CALL_CTRL_EPS,            UICC_SVR_NONE,                  USIM_SVR_CALL_CTRL_EPS},
    {NAS_USIM_SVR_HPLMN_DIR_ACCESS,         UICC_SVR_NONE,                  USIM_SVR_HPLMN_DIR_ACCESS},
    {NAS_USIM_SVR_ECALL_DATA,               UICC_SVR_NONE,                  USIM_SVR_ECALL_DATA},

    {NAS_USIM_SVR_OP_CGS ,                  UICC_SVR_NONE,                  USIM_SVR_OP_CGS},               /* 90 */
    {NAS_USIM_SVR_SM_VOER_IP ,              UICC_SVR_NONE,                  USIM_SVR_SM_VOER_IP},

    {NAS_USIM_SVR_CSG_CTRL ,              UICC_SVR_NONE,                    USIM_SVR_CSG_CTRL},

    {NAS_USIM_SVR_CHV1_DISABLE,             SIM_SVR_CHV1,                   UICC_SVR_NONE},
    {NAS_USIM_SVR_ADN,                      SIM_SVR_ADN,                    UICC_SVR_NONE},
    {NAS_USIM_SVR_PLMN_SELECTOR,            SIM_SVR_PLMN_SELECTOR,          UICC_SVR_NONE},
    {NAS_USIM_SVR_EXT1,                     SIM_SVR_EXT1,                   UICC_SVR_NONE},
    {NAS_USIM_SVR_LND,                      SIM_SVR_LND,                    UICC_SVR_NONE},
    {NAS_USIM_SVR_MENU_SEL,                 SIM_SVR_MENU_SELECTION,         UICC_SVR_NONE},
    {NAS_USIM_SVR_PROACTIVE_SIM,            SIM_SVR_PRO_SIM,                UICC_SVR_NONE},
    {NAS_USIM_SVR_MO_SMS_BY_SIM,            SIM_SVR_MOSMC,                  UICC_SVR_NONE},

    {NAS_USIM_SVR_GPRS ,                    SIM_SVR_GPRS,                   UICC_SVR_NONE},                 /* 100 */
    {NAS_USIM_SVR_USSD ,                    SIM_SVR_USSD,                   UICC_SVR_NONE},
    {NAS_USIM_SVR_EXT_CCP ,                 SIM_SVR_ECCP,                   UICC_SVR_NONE},
};
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-30, end */

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/


/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_SetFileReq
 功能描述  : 对USIMM模块的NAS_SndUsimmUpdateFileReq和NAS_SndUsimmUpdateFileReq_Instance进行封装。
             SVLTE模式下调用NAS_SndUsimmUpdateFileReq_Instance；
             非SVLTE模式下调用NAS_SndUsimmUpdateFileReq
 输入参数  : ulSenderPid:发送请求的pId；
             ulSendPara :发送的参数；
             pstSetFileInfo:设置的文件信息；
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 *****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_SetFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_UPDATEFILE_INFO_STRU     *pstSetFileInfo
)
{
    VOS_UINT32                          ulRslt;

    /* 向USIMM发送UpdateFile消息 */
    ulRslt = NAS_SndUsimmUpdateFileReq(ulSenderPid,
                                       ulSendPara,
                                      (NAS_USIMM_UPDATEFILE_DATA_STRU *)pstSetFileInfo);

    /* 调用可维可测 */
    NAS_LogUsimmApiSetFileReq(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, (NAS_USIMM_MNTN_SETFILE_INFO_STRU *)pstSetFileInfo);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_GetFileReq
 功能描述  : 对USIMM模块的USIMM_GetFileReq和USIMM_GetFileReq_Instance进行封装。
             SVLTE模式下调用USIMM_GetFileReq_Instance；
             非SVLTE模式下调用NAS_SndUsimmUpdateFileReq
 输入参数  : ulSenderPid:发送请求的pId；
             ulSendPara :发送的参数；
             pstGetFileInfo:获取的文件信息；
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_GetFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT32                          ulRet;

    /* 向USIMM发送ReadFile消息 */
    ulRet = NAS_SndUsimmReadFileReq(ulSenderPid,
                                    ulSendPara,
                                   (NAS_USIMM_GETFILE_DATA_STRU *)pstGetFileInfo);

    /* 调用可维可测 */
    NAS_LogUsimmApiGetFileReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, (NAS_USIMM_MNTN_GETFILE_INFO_STRU *)pstGetFileInfo);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_AuthReq
 功能描述  : 对USIMM模块的NAS_SndUsimmAuthReq和NAS_SndUsimmAuthReq_Instance进行封装。
             SVLTE模式下调用NAS_SndUsimmAuthReq_Instance；
             非SVLTE模式下调用NAS_SndUsimmAuthReq
 输入参数  : ulSenderPid:发送请求的pId；
             ucChallengeType:鉴权类型
             pucRand:鉴权随机数
             pucAutn:鉴权数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期  : 2013年11月30日
   作    者  : l65478
   修改内容  : DTS2013121919477,连续收到网络的两条鉴权消息,网络把第一条消息的响应作为第二条请求的响应,导致鉴权失败
 3.日    期   : 2013年7月17日
   作    者   : y00245242
   修改内容   : 由于USIM接口修改，重新做适配
*****************************************************************************/
VOS_VOID NAS_USIMMAPI_AuthReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucChallengeType,
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulRet;

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-22, begin */
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    NAS_USIMM_AUTH_DATA_STRU            stAuthData;

    PS_MEM_SET(&stAuthData, 0x00, sizeof(NAS_USIMM_AUTH_DATA_STRU));



    ulRet     = 0;
    enAppType = USIMM_GUTL_APP;


    if (AUTHENTICATION_REQ_GSM_CHALLENGE == ucChallengeType)
    {
        stAuthData.enAuthType = USIMM_2G_AUTH;
        PS_MEM_CPY(stAuthData.unAuthPara.st2GAuth.stRand.aucData,
                   pucRand,
                   NAS_MAX_AUTH_RAND_LEN);
        stAuthData.unAuthPara.st2GAuth.stRand.ucDataLen = NAS_MAX_AUTH_RAND_LEN;
    }
    else
    {
        stAuthData.enAuthType = USIMM_3G_AUTH;
        PS_MEM_CPY(stAuthData.unAuthPara.st3GAuth.stRand.aucData,
                   pucRand,
                   NAS_MAX_AUTH_RAND_LEN);
        stAuthData.unAuthPara.st3GAuth.stRand.ucDataLen = NAS_MAX_AUTH_RAND_LEN;
        /* skip the first byte since the first byte is length in Autn parameter */
        PS_MEM_CPY(stAuthData.unAuthPara.st3GAuth.stAutn.aucData,
                   (pucAutn + 1),
                   NAS_MAX_AUTH_AUTN_LEN);
        stAuthData.unAuthPara.st3GAuth.stAutn.ucDataLen = NAS_MAX_AUTH_AUTN_LEN;
    }

    /* 向USIMM发送鉴权消息 */
    ulRet = NAS_SndUsimmAuthReq(ulSenderPid, enAppType, &stAuthData, ucOpId);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-17, end */

    /* 调用可维可测 */
    NAS_LogUsimmApiAuthReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ucChallengeType, pucRand, pucAutn);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_PinReq
 功能描述  : 对USIMM模块的USIMM_PinReq和USIMM_PinReq_Instance进行封装。
             SVLTE模式下调用USIMM_PinReq_Instance；
             非SVLTE模式下调用USIMM_PinReq
 输入参数  : ulSenderPid:发送请求的pId；
             ucCmdType:操作类型
             ucPINType:PIN类型
             pucOldPIN:PIN码内容
             pucNewPIN:新PIN码内容
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_PinReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPINType,
    VOS_UINT8                          *pucOldPIN,
    VOS_UINT8                          *pucNewPIN
)
{
    VOS_UINT32                          ulRet;
    NAS_LOG_USIMM_PIN_INFO_STRU         stPinInfo;

    PS_MEM_SET(&stPinInfo, 0, sizeof(stPinInfo));

    stPinInfo.enCmdType = ucCmdType;
    stPinInfo.enPINType = ucPINType;

    if (VOS_NULL_PTR != pucOldPIN)
    {
        PS_MEM_CPY(stPinInfo.aucOldPIN, pucOldPIN, sizeof(stPinInfo.aucOldPIN));
    }

    if (VOS_NULL_PTR != pucNewPIN)
    {
        PS_MEM_CPY(stPinInfo.aucNewPIN, pucNewPIN, sizeof(stPinInfo.aucNewPIN));
    }

    /* 向USIMM发送Pin消息 */
    ulRet = NAS_SndUsimmPinReq(ulSenderPid, ucCmdType, ucPINType, pucOldPIN, pucNewPIN);

    /* 调用可维可测 */
    NAS_LogUsimmApiPinReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, &stPinInfo);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_MaxEFRecordNumReq
 功能描述  : 对USIMM模块的USIMM_MaxEFRecordNumReq和USIMM_MaxEFRecordNumReq_Instance进行封装。
             SVLTE模式下调用USIMM_MaxEFRecordNumReq_Instance；
             非SVLTE模式下调用USIMM_MaxEFRecordNumReq
 输入参数  : ulSenderPid:发送请求的pId；
             enAppType  :usimm应用类型
             usEFid     :文件id
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_MaxEFRecordNumReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
)
{
    VOS_UINT32                          ulRet;

    /* 向USIMM发送QueryFile消息 */
    ulRet = NAS_SndUsimmQueryFileReq(ulSenderPid, enAppType, usEFid);

    /* 调用可维可测 */
    NAS_LogUsimmApiMaxEFRecordNumReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, enAppType, usEFid);

    return ulRet;
}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
/*****************************************************************************
 函 数 名  : NAS_CovertUsimSrvTypeToUiccSrvType
 功能描述  : 转换NAS内部的(U)SIM service type到USIM接口UICC service type

 输入参数  : enUsimSrvType －－ NAS内部定义的USIM service type
 输出参数  : enUiccSrvType －－ 返回USIM接口的service type地址
 返 回 值  : VOS_FALSE  无对应的UICC业务类型
             VOS_TRUE   从table表中返回UICC业务类型

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月29日
   作    者   : y00245242
   修改内容   : 创建
 2.日    期   : 2014年2月19日
   作    者   : s00217060
   修改内容   : coverity清理
*****************************************************************************/
VOS_UINT32  NAS_CovertUsimSrvTypeToUiccSrvType(
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 enUsimSrvType,
    UICC_SERVICES_TYPE_ENUM_UINT32     *enUiccSrvType
)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucCardType;

    ulRst = VOS_FALSE;

    /* Added by s00217060 for coverity清理, 2014-02-19, begin */
    ucCardType  = USIMM_CARD_NOCARD;
    /* Added by s00217060 for coverity清理, 2014-02-19, end */

    /* 此处需要调用API获取,因为此时相关全局变量在未开机时还未更新 */
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType);

    if (NAS_USIM_SVR_MAX_SERVICE > enUsimSrvType)
    {
        if (USIMM_CARD_SIM == ucCardType)
        {
            /* Get UICC SRV type from SIM SRV type */
            *enUiccSrvType = g_NasUsimSrviceTypeTab[enUsimSrvType].enSimSrvType;
        }
        else
        {
            /* Get UICC SRV type from USIM SRV type */
            *enUiccSrvType = g_NasUsimSrviceTypeTab[enUsimSrvType].enUsimSrvType;
        }

        if (NAS_USIM_SVR_NONE != *enUiccSrvType)
        {
            ulRst = VOS_TRUE;
        }
    }

    return ulRst;
}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */
/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_IsServiceAvailable
 功能描述  : 对USIMM模块的USIMM_IsServiceAvailable和USIMM_IsServiceAvailable_Instance进行封装。
             SVLTE模式下调用USIMM_IsServiceAvailable_Instance；
             非SVLTE模式下调用USIMM_IsServiceAvailable
 输入参数  : enService:服务ID；
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2013年7月22日
   作    者   : y00245242
   修改内容   : 适配新的USIM接口
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_IsServiceAvailable(
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 enService
)
{
    VOS_UINT32                          ulRst;

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    UICC_SERVICES_TYPE_ENUM_UINT32      enUiccSrvType;

    if (VOS_FALSE == NAS_CovertUsimSrvTypeToUiccSrvType(enService, &enUiccSrvType))
    {
        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRst = USIMM_IsServiceAvailable_Instance(MODEM_ID_0, enUiccSrvType);
        NAS_LogUsimmApiIsServiceAvailable(ulRst,
                                          NAS_USIMM_API_TYPE_WITH_INSTANCE, enUiccSrvType);
        return ulRst;
    }

    /* 单待或DSDA */
    ulRst = USIMM_IsServiceAvailable(enUiccSrvType);

    NAS_LogUsimmApiIsServiceAvailable(ulRst,
                                      NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, enUiccSrvType);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_IsTestCard
 功能描述  : 对USIMM模块的USIMM_IsTestCard和USIMM_IsTestCard_Instance进行封装。
             SVLTE模式下调用USIMM_IsTestCard_Instance；
             非SVLTE模式下调用USIMM_IsTestCard
 输入参数  : ulSenderPid - 发送pid
 输出参数  : 无
 返 回 值  : VOS_TRUE:是；VOS_FALSE:否
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL  NAS_USIMMAPI_IsTestCard(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = USIMM_IsTestCard_Instance(MODEM_ID_0);

        /* 可维可测 */
        NAS_LogUsimmApiIsTestCard(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE);

        return ulRet;
    }

    /* 单待或DSDA */
    ulRet = USIMM_IsTestCard();

    /* 可维可测 */
    NAS_LogUsimmApiIsTestCard(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_GetPinStatus
 功能描述  : 对USIMM模块的USIMM_GetPinStatus和USIMM_GetPinStatus_Instance进行封装。
             SVLTE模式下调用USIMM_GetPinStatus_Instance；
             非SVLTE模式下调用USIMM_GetPinStatus
 输入参数  : ulSenderPid:发送pid
             pucType    :PIN类型
 输出参数  : pucBeEnable:PIN是否开启
             pucBeNeed  :PIN是否需要
             pucNum     :PIN剩余次数
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2013年10月8日
   作    者   : w00242748
   修改内容   : DTS2013090309349 参数作为出参，获取该出参变量后，再赋值给临时
                变量，再进行勾包处理。
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetPinStatus(
    VOS_UINT8                          *pucType,
    VOS_UINT8                          *pucBeEnable,
    VOS_UINT8                          *pucBeNeed,
    VOS_UINT8                          *pucNum
)
{
    VOS_UINT32                          ulRet;
    NAS_PIN_STATUS_STRU                 stPinStatus;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enUsimmApiType;

    if (VOS_NULL_PTR == pucType)
    {
        stPinStatus.ucPinType      = NAS_USIMM_PIN_TYPE_INVALID;
    }
    else
    {
        stPinStatus.ucPinType      = *pucType;
    }

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet          = USIMM_GetPinStatus_Instance(MODEM_ID_0, pucType, pucBeEnable, pucBeNeed, pucNum);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITH_INSTANCE;
    }
    else
    {
        /* 单待或DSDA */
        ulRet          = USIMM_GetPinStatus(pucType, pucBeEnable, pucBeNeed, pucNum);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITHOUT_INSTANCE;
    }

    if (VOS_NULL_PTR == pucBeEnable)
    {
        stPinStatus.ucPinBeEnable  = NAS_USIMM_PIN_ENABLE_FLG_INVALID;
    }
    else
    {
        stPinStatus.ucPinBeEnable  = *pucBeEnable;
    }

    if (VOS_NULL_PTR == pucBeNeed)
    {
        stPinStatus.ucPinBeNeed    = NAS_USIMM_PIN_NEED_FLG_INVALID;
    }
    else
    {
        stPinStatus.ucPinBeNeed    = *pucBeNeed;
    }

    if (VOS_NULL_PTR == pucNum)
    {
        stPinStatus.ucPinRemainNum = NAS_USIMM_PIN_NUM_INVALID;
    }
    else
    {
        stPinStatus.ucPinRemainNum = *pucNum;
    }

    /* 可维可测 */
    NAS_LogUsimmApiGetPinStatus(ulRet, enUsimmApiType, &stPinStatus);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_GetCachedFile
 功能描述  : 对USIMM模块的USIMM_GetCachedFile和USIMM_GetCachedFile_Instance进行封装。
             SVLTE模式下调用USIMM_GetCachedFile_Instance；
             非SVLTE模式下调用USIMM_GetCachedFile
 输入参数  : usFileID   :读取文件的ID
             enAppType  :USIMM卡类型
 输出参数  : pulDataLen :返回文件的内容长度
             ppucData   :返回文件内容的地址
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetCachedFile(
    VOS_UINT32                          ulFileID,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType
)
{
    VOS_UINT32                          ulRet;

    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulPathLength;

    ulRet = 0;
    ulPathLength    = 0;

    if (VOS_OK != USIMM_ChangeDefFileToPath(ulFileID, &pucFilePathStr))
    {
        return USIMM_API_FAILED;
    }

    /* 文件路径长度保护 */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        return USIMM_API_WRONG_PARA;
    }

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = USIMM_GetCachedFile_Instance(MODEM_ID_0, pucFilePathStr, pulDataLen, ppucData, enAppType);

        /* 调用可维可测 */
        NAS_LogUsimmApiGetCachedFile(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, *pulDataLen, ppucData);

        return ulRet;
    }

    /* 单待或DSDA */
    ulRet = USIMM_GetCachedFile(pucFilePathStr, pulDataLen, ppucData, enAppType);

    /* 调用可维可测 */
    NAS_LogUsimmApiGetCachedFile(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, *pulDataLen, ppucData);

    return ulRet;
}


/* Added by l00208543 for V9R1 STK升级, 2013-07-24, begin */
/*****************************************************************************
 函 数 名  : NAS_GetOamReceivePid
 功能描述  : 获取给oam发送的receive pid
 输入参数  : 接收方PID
 输出参数  : 无
 返 回 值  : 经过转换后的接收方PID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : l00208543
    修改内容   : STK升级项目，新增函数

*****************************************************************************/
VOS_UINT32 NAS_GetOamReceivePid(VOS_UINT32 ulRcvPid)
{
    if (VOS_FALSE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        return ulRcvPid;
    }

    switch (ulRcvPid)
    {
        case MAPS_STK_PID:
            return I0_MAPS_STK_PID;

        case WUEPS_PID_USIM:
            return I0_WUEPS_PID_USIM;

        case MAPS_PB_PID:
            return I0_MAPS_PB_PID;

        default:
            return ulRcvPid;
    }
}
/* Added by l00208543 for V9R1 STK升级, 2013-07-24, end */


/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_GetCardIMSI
 功能描述  : 对USIMM模块的USIMM_GetCardIMSI和USIMM_GetCardIMSI_Instance进行封装。
             SVLTE模式下调用USIMM_GetCardIMSI_Instance；
             非SVLTE模式下调用USIMM_GetCardIMSI
 输入参数  : 无
 输出参数  : pucImsi :存储文件的内容
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetCardIMSI(
    VOS_UINT8                          *pucImsi
)
{
    VOS_UINT32                          ulRst;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRst = USIMM_GetCardIMSI_Instance(MODEM_ID_0, pucImsi);
        NAS_LogUsimmApiGetCardIMSI(ulRst, NAS_USIMM_API_TYPE_WITH_INSTANCE, pucImsi);
        return ulRst;
    }

    /* 单待或DSDA */
    ulRst  = USIMM_GetCardIMSI(pucImsi);
    NAS_LogUsimmApiGetCardIMSI(ulRst, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pucImsi);

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_GetCardType
 功能描述  : 对USIMM模块的USIMM_GetCardType和USIMM_GetCardType_Instance进行封装。
             SVLTE模式下调用USIMM_GetCardType_Instance；
             非SVLTE模式下调用USIMM_GetCardType
 输入参数  : 无
 输出参数  : pucCardStatus  :卡类型
             pucCardType    :卡状态
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2013年10月8日
   作    者   : w00242748
   修改内容   : DTS2013090309349 参数作为出参，获取该出参变量后，再赋值给临时
                变量，再进行勾包处理。
 3.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_GetCardType(
    VOS_UINT8                          *pucCardStatus,
    VOS_UINT8                          *pucCardType
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucCardStatus;
    VOS_UINT16                          usCardType = 0X00;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enUsimmApiType;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet          = USIMM_GetCardTypeByAppType_Instance(MODEM_ID_0, pucCardStatus, pucCardType, USIMM_GUTL_APP);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITH_INSTANCE;
    }
    else
    {
        /* 单待或DSDA */
        ulRet          = USIMM_GetCardTypeByAppType(pucCardStatus, pucCardType, USIMM_GUTL_APP);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITHOUT_INSTANCE;
    }

    /* 可维可测时，需要取指针指向区域的内容，当指针为VOS_NULL_PTR时，取内容会出错，所以在此保护 */
    if (VOS_NULL_PTR == pucCardStatus)
    {
        ucCardStatus = USIMM_CARD_SERVIC_BUTT;
    }
    else
    {
        ucCardStatus = *pucCardStatus;
    }

    if (VOS_NULL_PTR == pucCardType)
    {
        usCardType  = NAS_USIMM_CARD_TYPE_INVALID;
    }
    else
    {
        usCardType  = *pucCardType;
    }

    /* 调用可维可测 */
    NAS_LogUsimmApiGetCardType(ulRet, enUsimmApiType, ucCardStatus, usCardType);

    return ulRet;
}


/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_BdnQuery
 功能描述  : 对USIMM模块的USIMM_BdnQuery和USIMM_BdnQuery_Instance进行封装。
             SVLTE模式下调用USIMM_BdnQuery_Instance；
             非SVLTE模式下调用USIMM_BdnQuery
 输入参数  : 无
 输出参数  : pulState :BDN状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_USIMMAPI_BdnQuery(
    VOS_UINT32                          *pulState
)
{
     /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        USIMM_BdnQuery_Instance(MODEM_ID_0, pulState);

        /* 调用可维可测 */
        if (VOS_NULL_PTR != pulState)
        {
            NAS_LogUsimmApiBdnQuery(*pulState, NAS_USIMM_API_TYPE_WITH_INSTANCE);
        }

        return;
    }

    /* 单待或DSDA */
    USIMM_BdnQuery(pulState);

    /* 调用可维可测 */
    if (VOS_NULL_PTR != pulState)
    {
        NAS_LogUsimmApiBdnQuery(*pulState, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_FdnQuery
 功能描述  : 对USIMM模块的USIMM_FdnQuery和USIMM_FdnQuery_Instance进行封装。
             SVLTE模式下调用USIMM_FdnQuery_Instance；
             非SVLTE模式下调用USIMM_FdnQuery
 输入参数  : 无
 输出参数  : pulState :FDN状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_USIMMAPI_FdnQuery(
    VOS_UINT32                         *pulUsimState,
    VOS_UINT32                         *pulCsimState
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        USIMM_FdnQuery_Instance(MODEM_ID_0, pulUsimState, pulCsimState);

        /* 调用可维可测 */
        if ((VOS_NULL_PTR != pulUsimState)
         && (VOS_NULL_PTR != pulCsimState))
        {
            NAS_LogUsimmApiFdnQuery(*pulUsimState, *pulCsimState, NAS_USIMM_API_TYPE_WITH_INSTANCE);
        }

        return;
    }

    /* 单待或DSDA */
    USIMM_FdnQuery(pulUsimState, pulCsimState);

    /* 调用可维可测 */
    if ((VOS_NULL_PTR != pulUsimState)
     && (VOS_NULL_PTR != pulCsimState))
    {
        NAS_LogUsimmApiFdnQuery(*pulUsimState, *pulCsimState, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_GetPinRemainTime
 功能描述  : 对USIMM模块的USIMM_GetPinRemainTime和USIMM_GetPinRemainTime_Instance进行封装。
             SVLTE模式下调用USIMM_GetPinRemainTime_Instance；
             非SVLTE模式下调用USIMM_GetPinRemainTime
 输入参数  : 无
 输出参数  : pstRemainTime :PIN剩余时间
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetPinRemainTime(
    USIMM_PIN_REMAIN_STRU              *pstRemainTime
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = USIMM_GetPinRemainTime_Instance(MODEM_ID_0, pstRemainTime);

        /* 调用可维可测 */
        NAS_LogUsimmApiGetPinRemainTime(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRemainTime);

        return ulRet;
    }

    /* 单待或DSDA */
    ulRet = USIMM_GetPinRemainTime(pstRemainTime);

    /* 调用可维可测 */
    NAS_LogUsimmApiGetPinRemainTime(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRemainTime);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_RestrictedAccessReq
 功能描述  :
 输入参数  : ulSenderPid:发送请求的pId；
             ulSendPara :发送的参数；
             pstData:；
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月15日
   作    者   : h00313353
   修改内容   : 新生成函数
 *****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_RestrictedAccessReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    USIMM_RACCESS_REQ_STRU             *pstData
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmRestrictedAccessReq(ulSenderPid,
                                             ulSendPara,
                                             pstData);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_RestrictedAccessReq
 功能描述  : 卡复位操作　
 输入参数  : ulSenderPid:发送请求的pId；
             pstCMDDetail :Reset信息
             pstRstInfo:Reset信息；
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月15日
   作    者   : h00313353
   修改内容   : 新生成函数
 *****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_ResetReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_STK_COMMAND_DETAILS_STRU     *pstCMDDetail,
    USIMM_RESET_INFO_STRU              *pstRstInfo
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmRefreshReq(ulSenderPid,
                                    pstCMDDetail,
                                    pstRstInfo);

    return ulRslt;
}


/*****************************************************************************
 函 数 名  : NAS_PIHAPI_RegUsimCardStatusIndMsg
 功能描述  : 对PIH模块的PIH_RegUsimCardStatusIndMsg和PIH_RegUsimCardStatusIndMsg_Instance进行封装。
             SVLTE模式下调用PIHAPI_RegUsimCardStatusIndMsg_Instance；
             非SVLTE模式下调用PIHAPI_RegUsimCardStatusIndMsg
 输入参数  : ulRegPID:注册的PID
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_PIHAPI_RegUsimCardStatusIndMsg(
    VOS_UINT32                          ulRegPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_RegUsimCardStatusIndMsg_Instance(MODEM_ID_0, ulRegPID);

        /* 调用可维可测 */
        NAS_LogPihApiRegUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulRegPID);

        return ulRet;
    }

    /* 单待或DSDA */
    ulRet = PIH_RegUsimCardStatusIndMsg(ulRegPID);


    /* 调用可维可测 */
    NAS_LogPihApiRegUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulRegPID);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_PIHAPI_DeregUsimCardStatusIndMsg
 功能描述  : 对PIH模块的PIH_DeregUsimCardStatusIndMsg和PIH_DeregUsimCardStatusIndMsg_Instance进行封装。
             SVLTE模式下调用PIHAPI_DeregUsimCardStatusIndMsg_Instance；
             非SVLTE模式下调用PIHAPI_DeregUsimCardStatusIndMsg
 输入参数  : ulDeregPID:去注册的PID
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_PIHAPI_DeregUsimCardStatusIndMsg(
    VOS_UINT32                          ulDeregPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_DeregUsimCardStatusIndMsg_Instance(MODEM_ID_0, ulDeregPID);

        /* 调用可维可测 */
        NAS_LogPihApiDeregUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulDeregPID);

        return ulRet;
    }

    /* 单待或DSDA */
    ulRet = PIH_DeregUsimCardStatusIndMsg(ulDeregPID);

    /* 调用可维可测 */
    NAS_LogPihApiDeregUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulDeregPID);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_PIHAPI_RegCardRefreshIndMsg
 功能描述  : 对PIH模块的PIH_RegCardRefreshIndMsg和PIH_RegCardRefreshIndMsg_Instance进行封装。
             SVLTE模式下调用PIHAPI_RegCardRefreshIndMsg_Instance；
             非SVLTE模式下调用PIHAPI_RegCardRefreshIndMsg
 输入参数  : ulRegPID:注册的PID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_PIHAPI_RegCardRefreshIndMsg(
    VOS_UINT32                          ulRegPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_RegCardRefreshIndMsg_Instance(MODEM_ID_0, ulRegPID);

        /* 调用可维可测 */
        NAS_LogPihApiRegCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulRegPID);

        return;
    }

    /* 单待或DSDA */
    ulRet = PIH_RegCardRefreshIndMsg(ulRegPID);

    /* 调用可维可测 */
    NAS_LogPihApiRegCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulRegPID);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_PIHAPI_DeregCardRefreshIndMsg
 功能描述  : 对PIH模块的PIH_DeregCardRefreshIndMsg和PIH_DeregCardRefreshIndMsg_Instance进行封装。
             SVLTE模式下调用PIHAPI_DeregCardRefreshIndMsg_Instance；
             非SVLTE模式下调用PIHAPI_DeregCardRefreshIndMsg
 输入参数  : ulDerecPID:去注册的PID
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_PIHAPI_DeregCardRefreshIndMsg(
    VOS_UINT32                          ulDeregPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_DeregCardRefreshIndMsg_Instance(MODEM_ID_0, ulDeregPID);

        /* 调用可维可测 */
        NAS_LogPihApiDeregCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulDeregPID);

        return ulRet;
    }

    /* 单待或DSDA */
    ulRet = PIH_DeregCardRefreshIndMsg(ulDeregPID);

    /* 调用可维可测 */
    NAS_LogPihApiDeregCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulDeregPID);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_PBAPI_GetEccNumber
 功能描述  : 对PB模块的SI_PB_GetEccNumber和SI_PB_GetEccNumber_Instance进行封装。
             SVLTE模式下调用SI_PB_GetEccNumber_Instance；
             非SVLTE模式下调用SI_PB_GetEccNumber
 输入参数  : 无
 输出参数  : pstEccData:获取ECC值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_PBAPI_GetEccNumber(
    SI_PB_ECC_DATA_STRU                *pstEccData
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = SI_PB_GetEccNumber_Instance(MODEM_ID_0, pstEccData);

        /* 调用可维可测 */
        NAS_LogPbApiGetEccNumber(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, pstEccData);

        return;
    }

    /* 单待或DSDA */
    ulRet = SI_PB_GetEccNumber(pstEccData);

    /* 调用可维可测 */
    NAS_LogPbApiGetEccNumber(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstEccData);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_PBAPI_FdnNumCheck
 功能描述  : 对STK模块的SI_PB_FdnNumCheck和SI_PB_FdnNumCheck_Instance进行封装。
             SVLTE模式下调用SI_PB_FdnNumCheck_Instance；
             非SVLTE模式下调用SI_PB_FdnNumCheck
 输入参数  : ulPid          ：发送FDN号码检查请求的Pid
             ulContextIndex :上下文索引
             ulSendPara     :发送参数
             pstFdnInfo     :FDN信息
 输出参数  : pstEccData:获取ECC值
 返 回 值  : 0:有效 1:无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_PBAPI_FdnNumCheck(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulContextIndex,
    VOS_UINT32                          ulSendPara,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmFdnNumCheckReq(ulPid, ulContextIndex, ulSendPara, pstFdnInfo);

    /* 调用可维可测 */
    NAS_LogPbApiFdnNumCheck(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstFdnInfo);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_STKAPI_EnvelopeRsp_Decode
 功能描述  : 对STK模块的SI_STK_EnvelopeRsp_Decode和SI_STK_EnvelopeRsp_Decode_Instance进行封装。
             SVLTE模式下调用SI_STK_EnvelopeRsp_Decode_Instance；
             非SVLTE模式下调用SI_STK_EnvelopeRsp_Decode
 输入参数  : enDataType: 解码的信封命令数据类型
             ulDataLen : 需要解码的数据长度
             pucData   : 需要解码的数据内容
 输出参数  : pstRspData: 解码后的数据内容
 返 回 值  : 0:有效 1:无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_STKAPI_EnvelopeRsp_Decode(
    SI_STK_ENVELOPE_TYPE_UINT32         enDataType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucCmdData,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    VOS_UINT32                          ulRslt;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRslt = SI_STK_EnvelopeRsp_Decode_Instance(MODEM_ID_0, enDataType, ulDataLen, pucCmdData, pstRspData);

        /* 调用可维可测 */
        NAS_LogStkApiEnvelopRspDecode(ulRslt, NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRspData);

        return ulRslt;
    }

    /* 单待或DSDA */
    ulRslt = SI_STK_EnvelopeRsp_Decode(enDataType, ulDataLen, pucCmdData, pstRspData);

    /* 调用可维可测 */
    NAS_LogStkApiEnvelopRspDecode(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRspData);

    return ulRslt;

}

/*****************************************************************************
 函 数 名  : NAS_STKAPI_EnvelopeRspDataFree
 功能描述  : 对STK模块的SI_STK_EnvelopeRspDataFree和SI_STK_EnvelopeRspDataFree_Instance进行封装。
             SVLTE模式下调用SI_STK_EnvelopeRspDataFree_Instance；
             非SVLTE模式下调用SI_STK_EnvelopeRspDataFree
 输入参数  : pstData   : 连接控制响应数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_STKAPI_EnvelopeRspDataFree(
    SI_STK_ENVELOPE_RSP_STRU           *pstData
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        SI_STK_EnvelopeRspDataFree_Instance(MODEM_ID_0, pstData);

        /* 调用可维可测 */
        NAS_LogStkApiEnvelopRspDataFree(NAS_USIMM_API_TYPE_WITH_INSTANCE, pstData);

        return;
    }

    /* 单待或DSDA */
    SI_STK_EnvelopeRspDataFree(pstData);

    /* 调用可维可测 */
    NAS_LogStkApiEnvelopRspDataFree(NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstData);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_STKAPI_EnvelopeDownload
 功能描述  : 对STK模块的SI_STK_EnvelopeDownload和SI_STK_EnvelopeDownload_Instance进行封装。
             SVLTE模式下调用SI_STK_EnvelopeDownload_Instance；
             非SVLTE模式下调用SI_STK_EnvelopeDownload
 输入参数  : ulSenderPid    : 发送者的PID
             usClientId     : 发送参数
             pstENStru      : Envelope数据
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2013年6月26日
   作    者   : f62575
   修改内容   : V9R1 STK升级
 3.日    期   : 2015年2月12日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 NAS_STKAPI_EnvelopeDownload(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulClientId,
    SI_STK_ENVELOPE_STRU               *pstENStru
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = 0;


    /* 向USIMM发送ReadFile消息 */
    ulRslt =  NAS_SndUsimmEnvelopeDownloadReq(ulSenderPid, ulClientId, pstENStru);

    /* 调用可维可测 */
    NAS_LogStkApiEnvelopDownload( ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulClientId, pstENStru);

    return ulRslt;
}

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*
    NAS_STKAPI_MtCallEvent
*/
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */


/* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, begin */
/* Deleted by l00208543 for V9R1 STK升级, 2013-7-13, end */

/*****************************************************************************
 函 数 名  : NAS_USIMMAPI_DeactiveCardReq
 功能描述  : 对USIMM_DeactiveCardReq进行封装,不区分svlte
 输入参数  : ulSenderPid - 发送pid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月4日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_DeactiveCardReq(VOS_UINT32 ulSenderPid)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmDeactiveCardReq(ulSenderPid);

    /* 调用可维可测 */
    NAS_LogUsimmApiDeactiveCardReq(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_STKAPI_CCResultInd
 功能描述  : 对SI_STK_CCResultInd和SI_STK_CCResultInd_Instance进行封装
 输入参数  : pstRspData - 指向CALL CONTROL的解码后码流
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_STKAPI_CCResultInd(
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        SI_STK_CCResultInd_Instance(MODEM_ID_0, pstRspData);

        /* 调用可维可测 */
        NAS_LogSTKApiCCResultInd(NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRspData);

        return;
    }

    /* 单待或DSDA */
    SI_STK_CCResultInd(pstRspData);

    /* 调用可维可测 */
    NAS_LogSTKApiCCResultInd(NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRspData);
}

/*****************************************************************************
 函 数 名  : NAS_STKAPI_SMSCtrlResultInd
 功能描述  : 对SI_STK_SMSCtrlResultInd和SI_STK_SMSCtrlResultInd_Instance进行封装
 输入参数  : pstRspData - 指向SMS CONTROL的解码后码流
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_STKAPI_SMSCtrlResultInd(
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        SI_STK_SMSCtrlResultInd_Instance(MODEM_ID_0, pstRspData);

        /* 调用可维可测 */
        NAS_LogSTKApiSMSCtrlResultInd(NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRspData);

        return;
    }

    /* 单待或DSDA */
    SI_STK_SMSCtrlResultInd(pstRspData);

    /* 调用可维可测 */
    NAS_LogSTKApiSMSCtrlResultInd(NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRspData);
}

/*****************************************************************************
 函 数 名  : NAS_VSIM_SetVsimCtrlFlg
 功能描述  : 设置NAS的虚拟卡控制配置
 输入参数  : ucVsimCtrlFlg - NAS的虚拟卡控制功能标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年8月29日
   作    者   : f62575
   修改内容   : VSIM FEATURE

*****************************************************************************/
VOS_VOID NAS_VSIM_SetVsimCtrlFlg(
    VOS_UINT8                           ucVsimCtrlFlg
)
{
    g_stNasVsimInfo.ucVsimCtrlFlg = ucVsimCtrlFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_VSIM_ReadNvimVsimCfg
 功能描述  : 读取en_Item_NAS_VSIM_CTRL_FEATURE到内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年8月29日
   作    者   : f62575
   修改内容   : VSIM FEATURE
*****************************************************************************/
VOS_VOID NAS_VSIM_ReadNvimVsimCfg(VOS_VOID)
{
    TAF_NVIM_VSIM_CFG_STRU              stVsimCfg;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    PS_MEM_SET(&stVsimCfg, 0, sizeof(stVsimCfg));

    (VOS_VOID)NV_GetLength(en_Item_NAS_VSIM_CTRL_FEATURE, &ulLength);

    ulRet = NV_Read(en_Item_NAS_VSIM_CTRL_FEATURE, &stVsimCfg, ulLength);
    /* NV项读取失败，按不支持VSIM特性处理 */
    if ((NV_OK != ulRet)
     || (VOS_TRUE != stVsimCfg.ucVsimCtrlFlg))
    {
        NAS_VSIM_SetVsimCtrlFlg(VOS_FALSE);
        return;
    }

    NAS_VSIM_SetVsimCtrlFlg(stVsimCfg.ucVsimCtrlFlg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_VSIM_InitVsimCfgInfo
 功能描述  : VSIM特性初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : f62575
    修改内容   : VSIM FEATURE

*****************************************************************************/
VOS_VOID NAS_VSIM_InitVsimCfgInfo(VOS_VOID)
{
    NAS_VSIM_ReadNvimVsimCfg();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_VSIM_GetVsimCtrlFlg
 功能描述  : 获取NAS的虚拟卡特性配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  要求NAS进行VSIM控制；
             VOS_FALSE 不要求NAS进行VSIM控制
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : f62575
    修改内容   : VSIM FEATURE

*****************************************************************************/
VOS_UINT8 NAS_VSIM_GetVsimCtrlFlg(VOS_VOID)
{
    return g_stNasVsimInfo.ucVsimCtrlFlg;
}

/*****************************************************************************
 函 数 名  : NAS_VSIM_IsRequireVsimCtrl
 功能描述  : 获取VSIM控制流程启用标志，
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  启用VSIM控制流程
             VOS_FALSE 不启用VSIM控制流程
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : f62575
    修改内容   : VSIM FEATURE

*****************************************************************************/
VOS_UINT32 NAS_VSIM_IsRequireVsimCtrl(VOS_VOID)
{

    VOS_UINT32                          ulVsimModem;
    VOS_UINT8                           ucVsimCtrlFlg;

    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulVsimModem     = USIMM_VsimIsActive_Instance(MODEM_ID_0);
    }
    else
    {
        ulVsimModem     = USIMM_VsimIsActive();
    }

    ucVsimCtrlFlg       = NAS_VSIM_GetVsimCtrlFlg();

    /* 此处需要钩包输出ulVsimModem和ucVsimCtrlFlg数据 */
    NAS_LogVsimIsRequireVsimCtrl(ulVsimModem, ucVsimCtrlFlg);

    /* MODEM是VSIM的MODEM且NAS的VSIM特性开启则启用VSIM控制流程 */
    if ((VOS_TRUE == ulVsimModem)
     && (VOS_TRUE == ucVsimCtrlFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-23, begin */
/*****************************************************************************
 函 数 名  : NAS_PBAPI_QryECallNumber
 功能描述  : 对STK模块的SI_PB_QryECallNumber和SI_PB_QryECallNumber_Instance进行封装。
             SVLTE模式下调用SI_PB_QryECallNumber_Instance；
             非SVLTE模式下调用SI_PB_QryECallNumber
 输入参数  : ulPid          ：发送查询ecall号码请求的Pid
             enPbType       : 电话本类型
             ucListLen      : 指定的文件索引记录长度
             pucList        : 指定的文件索引记录数组
 输出参数  : 无
 返 回 值  : 0:有效 1:无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月23日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_PBAPI_QryECallNumber(
    VOS_UINT32                          ulPid,
    SI_PB_STORAGE_ENUM_UINT32           enPbType,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
)
{
    VOS_UINT32                          ulRslt;

    /* 单待或DSDA */
    ulRslt = NAS_SndUsimmEcallNumberQry(ulPid, enPbType, ucListLen, pucList);

    /* 调用可维可测 */
    NAS_LogPbApiQryEcallNumber(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, enPbType, ucListLen, pucList);

    return;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-23, end */

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

/*****************************************************************************
 函 数 名  : NAS_PBAPI_GetXeccNumber
 功能描述  : 对PB模块的SI_PB_GetXeccNumber和SI_PB_GetXeccNumber_Instance进行封装。
             SVLTE模式下调用SI_PB_GetEccNumber_Instance；
             非SVLTE模式下调用SI_PB_GetEccNumber
 输入参数  : 无
 输出参数  : pstEccData:获取ECC值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月28日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_PBAPI_GetXeccNumber(
    SI_PB_ECC_DATA_STRU                *pstEccData
)
{
    VOS_UINT32                          ulRet;

    /* 单待或DSDA */
    ulRet = SI_PB_GetXeccNumber(pstEccData);

    /* 调用可维可测 */
    NAS_LogPbApiGetXeccNumber(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstEccData);

    return;
}

#endif


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

