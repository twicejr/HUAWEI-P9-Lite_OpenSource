

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "GuNasLogFilter.h"
#include "MnMsgApi.h"

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "MsgImsaInterface.h"
#include "Nasrrcinterface.h"
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "AtInternalMsg.h"
#include "AtParse.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_GU_NAS_LOG_FILTER_C

#define    AT_CMD_LEN_7             (7)
#define    AT_CMD_LEN_8             (8)
#define    AT_CMD_LEN_13            (13)
#define    AT_SMS_MODE              (1)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
typedef VOS_UINT32 (*pGuNasSmsMsgFilterProcFunc)(
    PS_MSG_HEADER_STRU      *pstMsg
);

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
extern VOS_UINT32 GUNAS_GetSmsFilterFlg( VOS_VOID );
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT8 AT_GetSmsFilterEnableFlg(
    VOS_UINT8                           ucIndex
);
#endif

/*******************************************************************************
 结构名    : NAS_MNTN_SMS_MSG_FILTER_PROC_TBL_FUNC
 结构说明  : 短信过滤消息处理函数结构体
 1.日    期   : 2015年09月25日
   作    者   : h00313353
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulSenderPid;
    VOS_UINT32                                  ulReceiverPid;
    pGuNasSmsMsgFilterProcFunc                  pFuncSmsFilterProc;
} GUNAS_SMS_MSG_FILTER_PROC_TBL_FUNC;

GUNAS_SMS_MSG_FILTER_PROC_TBL_FUNC              g_astGuNasSmsMsgFilterProcFuncTbl[] =
{
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    {WUEPS_PID_AT,          WUEPS_PID_AT,       GUNAS_SMS_FilterAtToAtMsg},
#endif

    {WUEPS_PID_TAF,         WUEPS_PID_AT,       GUNAS_SMS_FilterTafToAtMsg},
    {WUEPS_PID_AT,          WUEPS_PID_TAF,      GUNAS_SMS_FilterAtToTafMsg},

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    {PS_PID_IMSA,           WUEPS_PID_TAF,      GUNAS_SMS_FilterImsaToTafMsg},
    {WUEPS_PID_WRR,         WUEPS_PID_GMM,      GUNAS_SMS_FilterWrrToGmmMmMsg},
    {WUEPS_PID_WRR,         WUEPS_PID_MM,       GUNAS_SMS_FilterWrrToGmmMmMsg},
    {UEPS_PID_GAS,          WUEPS_PID_MM,       GUNAS_SMS_FilterGasToMmMsg},
#endif
};

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
VOS_CHAR*                                       g_apcATFileterTable[]=
{
        /* USIM相关 */
        "AT+CPIN"           ,
        "\r\n+CPIN:"        ,
        "AT+CLCK"           ,
        "\r\n+CLCK:"        ,
        "AT+CPWD"           ,
        "\r\n+CPWD:"        ,
        "AT^CPIN"           ,
        "\r\n^CPIN:"        ,
        "AT^CPIN2"          ,
        "\r\n^CPIN2:"       ,
        "AT+CPBW"           ,
        "\r\n+CPBW:"        ,
        "AT+CRSM"           ,
        "\r\n+CRSM:"        ,
        "AT+CSIM"           ,
        "\r\n+CSIM:"        ,
        "AT+CCHO"           ,
        "\r\n+CCHO:"        ,
        "AT+CCHC"           ,
        "AT+CNUM"           ,
        "\r\n+CNUM:"        ,
        "AT+CGLA"           ,
        "\r\n+CGLA:"        ,
        "AT+CRLA"           ,
        "\r\n+CRLA:"        ,
        "AT+CIMI"           ,
        "\r\n+CIMI:"        ,
        "AT^CSIN"           ,
        "\r\n^CSIN:"        ,
        "AT^CSTR"           ,
        "\r\n^CSTR:"        ,
        "AT^CSEN"           ,
        "\r\n^CSEN:"        ,
        "\r\n^CCIN:"        ,
        "AT^CISA"           ,
        "\r\n^CISA:"        ,
        "AT^CARDATR"        ,
        "\r\n^CARDATR:"     ,
        "AT^UICCAUTH"       ,
        "\r\n^UICCAUTH:"    ,
        "AT^URSM"           ,
        "\r\n^URSM:"        ,
        "AT^ICCID"          ,
        "\r\n^ICCID:"       ,

        /* 短信相关 */
        "AT+CMGS"           ,
        "AT+CMGW"           ,
        "AT+CMGC"           ,
        "\r\n+CMT:"         ,
        "\r\n+CMGR:"        ,
        "\r\n^RSTRIGGER:"   ,
        "\r\n+CMGS:"        ,
        "\r\n+CDS:"         ,
};
#endif


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterImsaToTafMsg
 功能描述  : 过滤Imsa到Taf短信层间消息的函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterImsaToTafMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    if ((ID_IMSA_MSG_DATA_IND   == pstMsg->ulMsgName)
     || (ID_IMSA_MSG_REPORT_IND == pstMsg->ulMsgName))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterWrrToGmmMmMsg
 功能描述  : 过滤Wrr到GMM或MM短信层间消息的函数
 输入参数  : pstMsg    -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterWrrToGmmMmMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    VOS_UINT8                           ucPd;

    ucPd                                = 0;

    if (RRMM_DATA_IND   != pstMsg->ulMsgName)
    {
        return VOS_FALSE;
    }

    if (VOS_OK != NAS_MM_GetL3RcvMsgPd((RRMM_DATA_IND_STRU *)pstMsg, &ucPd))
    {
        return VOS_FALSE;
    }

    if (NAS_SMS_PD == ucPd)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterGasToMmMsg
 功能描述  : 过滤Gas短信到MM的消息层间消息的函数
 输入参数  : pstMsg -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterGasToMmMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    VOS_UINT8                           ucPd;

    ucPd                                = 0;

    if (RRMM_DATA_IND   != pstMsg->ulMsgName)
    {
        return VOS_FALSE;
    }

    if (VOS_OK != NAS_MM_GetL3RcvMsgPd((RRMM_DATA_IND_STRU *)pstMsg, &ucPd))
    {
        return VOS_FALSE;
    }

    if (NAS_SMS_PD == ucPd)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
/*****************************************************************************
 函 数 名  : GUNAS_SMS_ATCmdFilter
 功能描述  : 过滤At到At的USIM层间消息函数
 输入参数  : pucATData     -- 消息中的数据
             usLen         -- 数据长度
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月31日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 GUNAS_SMS_ATCmdFilter(
    VOS_UINT8                          *pucATData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucTempData = VOS_NULL_PTR;

    pucTempData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);
    if (VOS_NULL_PTR == pucTempData)
    {
        return VOS_FALSE;
    }

    (VOS_VOID)PS_MEM_CPY(pucTempData, pucATData, usLen);

    (VOS_VOID)At_UpString(pucTempData, usLen);

    for (i = 0; i < (sizeof(g_apcATFileterTable)/sizeof(g_apcATFileterTable[0])); i++)
    {
        if (VOS_OK == PS_MEM_CMP((VOS_UINT8 *)g_apcATFileterTable[i], pucTempData, VOS_StrLen(g_apcATFileterTable[i])))
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucTempData);
            return VOS_TRUE;
        }
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucTempData);
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterAtToAtMsg
 功能描述  : 过滤At到At短信层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterAtToAtMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    VOS_UINT8                          *pucTmpAdr = VOS_NULL_PTR;
    VOS_UINT16                          usLen;

    usLen  = 0;

    switch (pstMsg->ulMsgName)
    {
        case ID_AT_MNTN_INPUT_MSC:
        case ID_AT_MNTN_OUTPUT_MSC:
        case ID_AT_MNTN_START_FLOW_CTRL:
        case ID_AT_MNTN_STOP_FLOW_CTRL:
        case ID_AT_MNTN_REG_FC_POINT:
        case ID_AT_MNTN_DEREG_FC_POINT:
        case ID_AT_MNTN_PC_REPLAY_MSG:
        case ID_AT_MNTN_PC_REPLAY_CLIENT_TAB:
        case ID_AT_MNTN_RPT_PORT:
        case ID_AT_COMM_CCPU_RESET_START:
        case ID_AT_COMM_CCPU_RESET_END:
        case ID_AT_COMM_HIFI_RESET_START:
        case ID_AT_COMM_HIFI_RESET_END:
        case ID_AT_NCM_CONN_STATUS_CMD:
        case ID_AT_WATER_LOW_CMD:
        case ID_AT_SWITCH_CMD_MODE:
            return VOS_FALSE;

        default:
        {
            if (AT_SMS_MODE == g_stParseContext[((AT_MSG_STRU *)pstMsg)->ucIndex].ucMode)
            {
                /* 短信模式直接进行过滤 */
                return VOS_TRUE;
            }

            pucTmpAdr                   = (VOS_UINT8 *)((VOS_UINT8 *)pstMsg
                                                        + sizeof(AT_MSG_STRU)
                                                        - sizeof(((AT_MSG_STRU *)pstMsg)->aucValue));

            usLen                       = ((AT_MSG_STRU *)pstMsg)->usLen;

            if (VOS_TRUE == GUNAS_SMS_ATCmdFilter(pucTmpAdr, usLen))
            {
                return VOS_TRUE;
            }

            return VOS_FALSE;
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterAtToTafMsg
 功能描述  : 过滤At到Taf短信层间消息的函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterAtToTafMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    switch (pstMsg->ulMsgName)
    {
        case MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT:
        case MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM:
        case MN_MSG_MSGTYPE_WRITE:
        case MN_MSG_MSGTYPE_READ:
        case MN_MSG_MSGTYPE_LIST:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterTafToAtMsg
 功能描述  : 过滤Taf到At短信层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterTafToAtMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    VOS_UINT32                          ulEventType;

    ulEventType = 0;

    if (MN_CALLBACK_MSG   != pstMsg->ulMsgName)
    {
        return VOS_FALSE;
    }

    PS_MEM_CPY(&ulEventType, ((MN_AT_IND_EVT_STRU *)pstMsg)->aucContent, sizeof(VOS_UINT32));

    switch ((MN_MSG_EVENT_ENUM_U32)ulEventType)
    {
        case MN_MSG_EVT_SUBMIT_RPT:
        case MN_MSG_EVT_MSG_SENT:
        case MN_MSG_EVT_DELIVER:
        case MN_MSG_EVT_READ:
        case MN_MSG_EVT_LIST:
        case MN_MSG_EVT_WRITE:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterLayerMsg
 功能描述  : 过滤短信层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterLayerMsg(
    const VOS_VOID                     *pstMsg
)
{
    PS_MSG_HEADER_STRU                 *pstTempMsg = VOS_NULL_PTR;
    pGuNasSmsMsgFilterProcFunc          pfunSmsFilter;
    VOS_UINT32                          i;

    pstTempMsg      = (PS_MSG_HEADER_STRU *)pstMsg;
    pfunSmsFilter   = VOS_NULL_PTR;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    if (VOS_FALSE == AT_GetSmsFilterEnableFlg(0))
    {
        return VOS_FALSE;
    }
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    if (VOS_FALSE == GUNAS_GetSmsFilterFlg())
    {
        return VOS_FALSE;
    }

    /* SMS消息过滤 */
    if ((WUEPS_PID_SMS == pstTempMsg->ulSenderPid)
     || (WUEPS_PID_SMS == pstTempMsg->ulReceiverPid))
    {
        return VOS_TRUE;
    }
#endif

    for (i = 0; i < (sizeof(g_astGuNasSmsMsgFilterProcFuncTbl)/sizeof(GUNAS_SMS_MSG_FILTER_PROC_TBL_FUNC)); i++)
    {
        if ((pstTempMsg->ulSenderPid    == g_astGuNasSmsMsgFilterProcFuncTbl[i].ulSenderPid)
         && (pstTempMsg->ulReceiverPid  == g_astGuNasSmsMsgFilterProcFuncTbl[i].ulReceiverPid))
        {
            pfunSmsFilter = g_astGuNasSmsMsgFilterProcFuncTbl[i].pFuncSmsFilterProc;
            break;
        }
    }

    if (VOS_NULL_PTR != pfunSmsFilter)
    {
        return pfunSmsFilter(pstTempMsg);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : GUNAS_OM_LayerMsgFilter
 功能描述  : GUNAS用于过滤层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_OM_LayerMsgFilter(
    const VOS_VOID                     *pstMsg
)
{
    /* 短信层间消息过滤 */
    if (VOS_TRUE == GUNAS_SMS_FilterLayerMsg(pstMsg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
