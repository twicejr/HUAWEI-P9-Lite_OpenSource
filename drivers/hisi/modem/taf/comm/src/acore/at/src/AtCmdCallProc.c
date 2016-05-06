

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtCmdCallProc.h"

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
#include "AtSndMsg.h"
#include "ATCmdProc.h"
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -save -e960 */
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_CALL_PROC_C
/*lint -restore */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : AT_SetCecallPara
 功能描述  : 发起ECALL会话 ，+CECALL=<type_of_eCall>
             <type_of_eCall>:    0 test call
                                 1 reconfiguration call eCall
                                 2 manually initiated eCall
                                 3 automatically initated eCall
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCecallPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    MN_CALL_ORIG_PARAM_STRU             stCecallPara;

    /* 参数必须为1。
       参数个数为1时，参数长度不可能为0，
       即"AT+CECALL="情况下，gucAtParaIndex为0 */
    if (1 != gucAtParaIndex)
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stCecallPara, 0x0, sizeof(stCecallPara));

    switch (gastAtParaList[0].ulParaValue)
    {
        case 0:
            stCecallPara.enCallType = MN_CALL_TYPE_TEST;
            break;
        case 1:
            stCecallPara.enCallType = MN_CALL_TYPE_RECFGURATION;
            break;
        case 2:
            stCecallPara.enCallType = MN_CALL_TYPE_MIEC;
            break;
        case 3:
            stCecallPara.enCallType = MN_CALL_TYPE_AIEC;
            break;
        default:
            return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   MN_CALL_APP_ORIG_REQ,
                                   &stCecallPara,
                                   sizeof(stCecallPara),
                                   I0_WUEPS_PID_TAF);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CECALL_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetEclstartPara
 功能描述  : ^ECLSTART发起ECALL会话(^ECLSTART=<activation_type>,<type_of_call>[,<dial_num>])
             <activation_type>:   0 用户发起ECALL会话
                                  1 自动发起ECALL会话
             <type_of_call>:      0 发起测试会话 (发起VOICE call)
                                  1 发起紧急呼叫 (发起EMERGENCY call)
             <dial_num>:          发起测试呼叫时，应该要带电话号码，如果没带号码，则从SIM卡的EEfdn或EFsdn中获取；
                                  发起紧急呼叫时，不将号码发送到网络侧，号码参数没有实际意义，可以提供，也可以不提供。
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetEclstartPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    MN_CALL_ORIG_PARAM_STRU             stCecallPara;
    MN_CALL_CALLED_NUM_STRU             stDialNumber;

    /*  判断1: 必选参数的长度不能为0 */
    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_ERROR;
    }

    /* 判断2: 参数个数不对, 判断1已保证参数个数>=2 */
    if (gucAtParaIndex > 3)
    {
        return AT_ERROR;
    }

    /* 判断3:  AT^ECLSTART=1,1, 这种情况是错的 */
    if ((3 == gucAtParaIndex)
     && (0 == gastAtParaList[2].usParaLen))
    {
        return AT_ERROR;
    }

    /* 初始化 */
    PS_MEM_SET(&stDialNumber, 0x0, sizeof(stDialNumber));

    /* 带拨号号码 */
    if (gastAtParaList[2].usParaLen > 0)
    {
        /* 号码的最大长度不能超过18 */
        if (gastAtParaList[2].usParaLen > ECALL_MAX_DIAL_NUM_LEN)
        {
            return AT_ERROR;
        }

        /* 检查并转换电话号码 */
        if (VOS_OK !=  AT_FillCalledNumPara(gastAtParaList[2].aucPara,
                                            gastAtParaList[2].usParaLen,
                                            &stDialNumber))
        {
            AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
            return AT_ERROR;
        }
    }

    /* 初始化 */
    PS_MEM_SET(&stCecallPara, 0x0, sizeof(stCecallPara));

    /* 发紧急呼叫时，<activation_type>参数有效，非紧急呼叫时,<activation_type>参数没有作用 --产品线:t00192572 */
    /* ^ECLSTART=x,0  发起测试call */
    if (0 == gastAtParaList[1].ulParaValue)
    {
        stCecallPara.enCallType = MN_CALL_TYPE_TEST;

        /* 只有测试呼叫才下发电话号码，紧急呼叫不下发电话号码 */
        PS_MEM_CPY(&stCecallPara.stDialNumber, &stDialNumber, sizeof(stDialNumber));
    }
    else
    {
        /* ^ECLSTART=0,1  用户发起紧急call */
        if (0 == gastAtParaList[0].ulParaValue)
        {
            stCecallPara.enCallType = MN_CALL_TYPE_MIEC;
        }
        /* ^ECLSTART=1,1  自动发起紧急call */
        else
        {
            stCecallPara.enCallType = MN_CALL_TYPE_AIEC;
        }
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   MN_CALL_APP_ORIG_REQ,
                                   &stCecallPara,
                                   sizeof(stCecallPara),
                                   I0_WUEPS_PID_TAF);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLSTART_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetEclstopPara
 功能描述  : ^ECLSTOP断开当前ECALL会话
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetEclstopPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    MN_CALL_SUPS_PARAM_STRU             stEclstopPara;

    /* 不带参数的设置命令 */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 初始化 */
    PS_MEM_SET(&stEclstopPara, 0x0, sizeof(stEclstopPara));

    stEclstopPara.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ECALL;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   MN_CALL_APP_SUPS_CMD_REQ,
                                   &stEclstopPara,
                                   sizeof(stEclstopPara),
                                   I0_WUEPS_PID_TAF);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLSTOP_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetEclcfgPara
 功能描述  : ^ECLCFG用于配置单板获取MSD数据的模式，配置是否禁止语音功能。
             ^ECLCFG=<mode>[,<voc_config>]
             <mode>:        表示单板获取MSD数据的模式，目前只支持透传模式
             <voc_config>:  0  在MSD传输过程中同步传输语音信号，默认值。
                            1  在MSD传输过程中禁止语音信号的传输，避免语音信号的传输干扰MSD数据的传输。

 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetEclcfgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    APP_VC_MSG_SET_ECALL_CFG_REQ_STRU   stEclcfgSetPara;

    /* 判断一: 必选参数的长度不能为0 */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    /* 判断二: 参数个数不对, 判断一已经保证参数个数>=1 */
    if (gucAtParaIndex > 2)
    {
        return AT_ERROR;
    }

    /* 判断3:  AT^ECLCFG=0, 这种情况是错的 */
    if ((2 == gucAtParaIndex)
     && (0 == gastAtParaList[1].usParaLen))
    {
        return AT_ERROR;
    }

    stEclcfgSetPara.enMode = (APP_VC_ECALL_MSD_MODE_ENUM_UINT16)gastAtParaList[0].ulParaValue;

    if (0 == gastAtParaList[1].usParaLen)
    {
        stEclcfgSetPara.enVocConfig = APP_VC_ECALL_VOC_CONFIG_NOT_ABANDON;
    }
    else
    {
        stEclcfgSetPara.enVocConfig = (APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16)gastAtParaList[1].ulParaValue;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   APP_VC_MSG_SET_ECALL_CFG_REQ,
                                   &stEclcfgSetPara,
                                   sizeof(stEclcfgSetPara),
                                   I0_WUEPS_PID_VC);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLCFG_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_SetEclmsdPara
 功能描述  : ^ECLMSD用于下发当前ECALL会话需要传输的MSD信息
             ^ECLMSD=<ecall_msd>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetEclmsdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    APP_VC_MSG_SET_MSD_REQ_STRU         stEclmsdPara;

    /* 参数必须为1。
       参数个数为1时，参数长度不可能为0，
       即"AT+CELMSD="情况下，gucAtParaIndex为0 */
    if (1 != gucAtParaIndex)
    {
        return AT_ERROR;
    }

    /* 参数长度不对
       十六进制文本字符串，采用十六进制数据编码方式，字符串长度为280个字节，表示的是MSD协议要求的140个字节原始数据
    */
    if (((APP_VC_MSD_DATA_LEN * 2) != gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    if (AT_FAILURE == At_AsciiString2HexSimple(stEclmsdPara.aucMsdData,
                                               gastAtParaList[0].aucPara,
                                               APP_VC_MSD_DATA_LEN * 2))
    {
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   APP_VC_MSG_SET_MSD_REQ,
                                   &stEclmsdPara,
                                   sizeof(stEclmsdPara),
                                   I0_WUEPS_PID_VC);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLMSD_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_QryCecallPara
 功能描述  : 查询ECALL的类型
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_WAIT_ASYNC_RETURN/AT_ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryCecallPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   MN_CALL_QRY_ECALL_INFO_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_TAF);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CECALL_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_QryEclcfgPara
 功能描述  : 查询单板获取MSD数据的模式，配置是否禁止语音功能。
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_WAIT_ASYNC_RETURN/AT_ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryEclcfgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   APP_VC_MSG_QRY_ECALL_CFG_REQ,
                                   VOS_NULL,
                                   0,
                                   I0_WUEPS_PID_VC);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLCFG_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_QryEclmsdPara
 功能描述  : 查询当前的msd信息
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_WAIT_ASYNC_RETURN/AT_ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryEclmsdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   APP_VC_MSG_QRY_MSD_REQ,
                                   VOS_NULL,
                                   0,
                                   I0_WUEPS_PID_VC);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECLMSD_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_TestEclstartPara
 功能描述  : ECLSTART测试命令处理函数
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_TestEclstartPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1),(0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestEclmsdPara
 功能描述  : ECLMSD测试命令处理函数
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_TestEclmsdPara(VOS_UINT8 ucIndex)
{
    /* ^eclmsd不支持测试命令，
        该函数可以在eclmsd测试命令时返回ERROR，而不是"(MSD)" */
    return AT_ERROR;
}

#endif
/* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, end */

/*****************************************************************************
函 数 名  : At_RcvVcMsgDtmfDecoderIndProc
功能描述  : AT收到VC DTMF上报消息的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : VOS_UINT32
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2014年5月9日
    作    者   : g00261581
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 At_RcvVcMsgDtmfDecoderIndProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_DTMF_DECODER_IND_STRU       *pstDtmfInd;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            aucOutput[2];

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgDtmfDecoderIndProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstDtmfInd = (APP_VC_DTMF_DECODER_IND_STRU *)pstData->aucContent;
    aucOutput[0] = pstDtmfInd->ucDtmfCode;
    aucOutput[1] = '\0';

    /* 输出查询结果 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^DDTMF: %s%s",
                                                    gaucAtCrLf,
                                                    aucOutput,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_CheckCfshNumber
 功能描述  : CFSH命令携带的number合法性检查，合法的字符仅包括：'0' - '9', '*', '#', '+'。
             '+'只能出现在号码的最前面，号码的最大长度不能超过32（不包括"+"）
 输入参数  : pucAtPara   --- <number>
             usLen       ---  号码长度
 输出参数  : 无
 返 回 值  : VOS_OK      参数合法
             VOS_ERR     参数非法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月8日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 AT_CheckCfshNumber(
    VOS_UINT8                          *pucAtPara,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16      ucLoop;

    /* 号码长度有效性判断:+号开头的国际号码，最大长度不能大于33；否则不能大于32 */
    if ('+' == pucAtPara[0])
    {
        if (usLen > (TAF_CALL_MAX_FLASH_DIGIT_LEN + 1))
        {
            return VOS_ERR;
        }

        pucAtPara++;
        usLen--;
    }
    else
    {
        if (usLen > TAF_CALL_MAX_FLASH_DIGIT_LEN)
        {
            return VOS_ERR;
        }
    }

    /* 号码字符有效性判断(不包含国际号码的首字符'+') */
    for (ucLoop = 0; ucLoop < usLen; ucLoop++)
    {
        if (  ((pucAtPara[ucLoop] >= '0') && (pucAtPara[ucLoop] <= '9'))
            || (pucAtPara[ucLoop] == '*')
            || (pucAtPara[ucLoop] == '#'))
        {
            continue;
        }
        else
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SetCfshPara
 功能描述  : AT^CFSH=<number> 的设置函数

             <CR><LF>OK<CR><LF>
             有MS相关错误时：
             <CR><LF>+CME ERROR: <err><CR><LF>

             本命令实现FLASH功能， 首先对命令参数进行合法性检查，包含：号码及长度。约束：合法的字符包括ASCII码数字，号码长度范围：0~32。
             然后发送FLASH命令

             当没有处于通话状态时, 需上报一个错误。
             当有呼叫等待的时候，发送不带电话号码的FLASH命令接听第三方呼叫。
             当通话时，发送带电话号码的FLASH命令进行对第三方的呼叫。
             其他情况报错。
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月7日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

*****************************************************************************/
VOS_UINT32 AT_SetCfshPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    TAF_CALL_FLASH_PARA_STRU            stFlashPara;

    /* 参数过多 */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 若携带了参数<number>，检查其有效性 */
    if (1 == gucAtParaIndex)
    {
        if (VOS_OK != AT_CheckCfshNumber(gastAtParaList[0].aucPara,
                                         gastAtParaList[0].usParaLen))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        /* 这种AT命令AT^CFSH= 返回参数错误 */
        if(AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    PS_MEM_SET(&stFlashPara, 0, sizeof(TAF_CALL_FLASH_PARA_STRU));

    stFlashPara.ucDigitNum = (VOS_UINT8)gastAtParaList[0].usParaLen;
    PS_MEM_CPY(stFlashPara.aucDigit, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    /* 发送TAF_CALL_APP_SEND_FLASH_REQ消息 */
    ulRst = TAF_XCALL_SendFlashReq(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   &stFlashPara);
    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFSH_SET;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallSndFlashRslt
 功能描述  : 处理TAF_CALL_EVT_SEND_FLASH_RSLT事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_VOID AT_RcvTafCallSndFlashRslt(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    VOS_UINT8                           ucIndex;
    TAF_CALL_EVT_SEND_FLASH_RSLT_STRU  *pstSndFlashRslt;

    /* 根据ClientID获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallSndFlashRslt: Get Index Fail!");
        return;
    }

    /* AT模块在等待^CFSH命令的操作结果事件上报 */
    if (AT_CMD_CFSH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvTafCallSndFlashRslt: Error Option!");
        return;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 根据临时响应的错误码打印命令的结果 */
    pstSndFlashRslt = (TAF_CALL_EVT_SEND_FLASH_RSLT_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));
    if (VOS_OK == pstSndFlashRslt->ucResult)
    {
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : At_TestCBurstDTMFPara
 功能描述  : CBurstDTMF测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_TestCBurstDTMFPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^CBURSTDTMF: (1,2),(0-9,*,#),(95,150,200,250,300,350),(60,100,150,200)");
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_SetCBurstDTMFPara
 功能描述  : DTMF指令处理
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCBurstDTMFPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    TAF_CALL_BURST_DTMF_PARA_STRU       stBurstDtmfPara;
    VOS_UINT16                          ucLoop;

    /*参数有效性检查*/
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((gucAtParaIndex != 4)
        ||(0 == gastAtParaList[0].usParaLen)
        ||(0 == gastAtParaList[1].usParaLen)
        ||(0 == gastAtParaList[2].usParaLen)
        ||(0 == gastAtParaList[3].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* DTMF Key长度有效性判断 */
    if (gastAtParaList[1].usParaLen > TAF_CALL_MAX_BURST_DTMF_NUM)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* DTMF Key有效性判断 */
    for (ucLoop = 0; ucLoop < gastAtParaList[1].usParaLen; ucLoop++)
    {
        if (  ((gastAtParaList[1].aucPara[ucLoop] >= '0') && (gastAtParaList[1].aucPara[ucLoop] <= '9'))
            || (gastAtParaList[1].aucPara[ucLoop] == '*')
            || (gastAtParaList[1].aucPara[ucLoop] == '#'))
        {
            continue;
        }
        else
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    PS_MEM_SET(&stBurstDtmfPara, 0, sizeof(stBurstDtmfPara));

    stBurstDtmfPara.ucCallId     = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stBurstDtmfPara.ucDigitNum   = (VOS_UINT8)gastAtParaList[1].usParaLen;
    PS_MEM_CPY(stBurstDtmfPara.aucDigit, gastAtParaList[1].aucPara, stBurstDtmfPara.ucDigitNum);
    stBurstDtmfPara.ulOnLength   = gastAtParaList[2].ulParaValue;
    stBurstDtmfPara.ulOffLength  = gastAtParaList[3].ulParaValue;

    /* 发送TAF_CALL_APP_SEND_BURST_DTMF_REQ消息 */
    ulRst = TAF_XCALL_SendBurstDtmf(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                   &stBurstDtmfPara);
    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CBURSTDTMF_SET;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
/*****************************************************************************
 函 数 名  : AT_RcvTafCallSndBurstDTMFCnf
 功能描述  : 处理TAF_CALL_EVT_SEND_BURST_DTMF_CNF事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafCallSndBurstDTMFCnf(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU                  *pstBurstDtmfCnf;

    /* 根据ClientID获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallSndBurstDTMFCnf: Get Index Fail!");
        return VOS_ERR;
    }

    /* AT模块在等待^CBURSTDTMF命令命令的操作结果事件上报 */
    if ( AT_CMD_CBURSTDTMF_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvTafCallSndBurstDTMFCnf: Error Option!");
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 根据临时响应的错误码打印命令的结果 */
    pstBurstDtmfCnf = (TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));
    if (TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS != pstBurstDtmfCnf->enResult)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallSndBurstDTMFRslt
 功能描述  : 处理TAF_CALL_EVT_SEND_BURST_DTMF_RSLT事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafCallSndBurstDTMFRslt(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvTafCallCalledNumInfoInd
 功能描述  : 处理TAF_CALL_EVT_CALLED_NUM_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CCALLEDNUM: <number_type>,<number_plan>,<number><CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallCalledNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_CALLED_NUM_INFO_IND_STRU                  *pstCalledNum;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               aucDigit[TAF_CALL_MAX_CALLED_NUMBER_CHARI_OCTET_NUM + 1];

    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallCalledNumInfoInd: Get Index Fail!");
        return VOS_ERR;
    }


    /* 初始化 */
    pstCalledNum = (TAF_CALL_EVT_CALLED_NUM_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));
    PS_MEM_CPY(aucDigit, pstCalledNum->aucDigit, pstCalledNum->ucDigitNum);

    /* 在pstCalledNum->aucDigit的最后一位加'\0',防止因pstCalledNum->aucDigit无结束符，导致AT多上报 */
    aucDigit[pstCalledNum->ucDigitNum] = '\0';

    /* 输出查询结果 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s%d,%d,%s%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CCALLEDNUM].pucText,
                                                    pstCalledNum->enNumType,
                                                    pstCalledNum->enNumPlan,
                                                    aucDigit,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallCallingNumInfoInd
 功能描述  : 处理TAF_CALL_EVT_CALLING_NUM_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CCALLINGNUM: <number_type>,<number_plan>,<pi>,<si>,<number><CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallCallingNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU                 *pstCallingNum;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               aucDigit[TAF_CALL_MAX_CALLING_NUMBER_CHARI_OCTET_NUM + 1];

    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallCallingNumInfoInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstCallingNum = (TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));

    PS_MEM_CPY(aucDigit, pstCallingNum->aucDigit, pstCallingNum->ucDigitNum);

    /* 在pstCallingNum->aucDigit的最后一位加'\0',防止因pstCallingNum->aucDigit无结束符，导致AT多上报 */
    aucDigit[pstCallingNum->ucDigitNum] = '\0';

    /* 输出查询结果 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s%d,%d,%d,%d,%s%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CCALLINGNUM].pucText,
                                                    pstCallingNum->enNumType,
                                                    pstCallingNum->enNumPlan,
                                                    pstCallingNum->ucPi,
                                                    pstCallingNum->ucSi,
                                                    aucDigit,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallDispInfoInd
 功能描述  : 处理TAF_CALL_EVT_DISPLAY_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CDISP: <string>[,<ext_display>,<display_type>,<display_tag>]<CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallDispInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_DISPLAY_INFO_IND_STRU  *pstDisplayInfo;
    VOS_UINT8                            ucIndex;
    VOS_UINT8                            aucDigit[TAF_CALL_MAX_DISPALY_CHARI_OCTET_NUM + 1];

    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallDispInfoInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstDisplayInfo = (TAF_CALL_EVT_DISPLAY_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));
    PS_MEM_CPY(aucDigit, pstDisplayInfo->aucDigit, pstDisplayInfo->ucDigitNum);

    /* 在pstDisplayInfo->aucDigit的最后一位加'\0',防止因pstDisplayInfo->aucDigit无结束符，导致AT多上报 */
    aucDigit[pstDisplayInfo->ucDigitNum] = '\0';

    /* 输出查询结果 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s%s,,,%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CDISP].pucText,
                                                    aucDigit,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallExtDispInfoInd
 功能描述  : 处理TAF_CALL_EVT_EXT_DISPLAY_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CDISP: <string>[,<ext_display>,<display_type>,<display_tag>]<CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallExtDispInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU                 *pstExtDispInfo;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulLoop;
    VOS_UINT32                                              ulDigitNum;
    VOS_UINT8                                               aucDigit[TAF_CALL_MAX_EXTENDED_DISPALY_CHARI_OCTET_NUM + 1];

    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallExtDispInfoInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstExtDispInfo = (TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    for (ulLoop = 0; ulLoop < pstExtDispInfo->ucInfoRecsDataNum; ulLoop++)
    {
        /* 在pstExtDispInfo->aucInfoRecsData[ulLoop].aucDigit的最后一位加'\0',
            防止因pstExtDispInfo->aucInfoRecsData[ulLoop].aucDigit无结束符，导致AT多上报 */
        ulDigitNum = pstExtDispInfo->aucInfoRecsData[ulLoop].ucDigitNum;
        PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));
        PS_MEM_CPY(aucDigit, pstExtDispInfo->aucInfoRecsData[ulLoop].aucDigit, ulDigitNum);
        aucDigit[ulDigitNum] = '\0';

        /* 输出查询结果 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s%s%s,%d,%d,%d%s",
                                                        gaucAtCrLf,
                                                        gastAtStringTab[AT_STRING_CDISP].pucText,
                                                        aucDigit,
                                                        pstExtDispInfo->ucExtDispInd,
                                                        pstExtDispInfo->ucDisplayType,
                                                        pstExtDispInfo->aucInfoRecsData[ulLoop].ucDispalyTag,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }



    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallConnNumInfoInd
 功能描述  : 处理TAF_CALL_EVT_CONN_NUM_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CCONNNUM: <number_type>,<number_plan>,<pi>,<si>,<number><CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallConnNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU *pstConnNumInfo;
    VOS_UINT8                            ucIndex;
    VOS_UINT8                            aucDigit[TAF_CALL_MAX_CONNECTED_NUMBER_CHARI_OCTET_NUM + 1];


    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallConnNumInfoInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstConnNumInfo = (TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));
    PS_MEM_CPY(aucDigit, pstConnNumInfo->aucDigit, pstConnNumInfo->ucDigitNum);

    /* 在pstConnNumInfo->aucDigit的最后一位加'\0',防止因pstConnNumInfo->aucDigit无结束符，导致AT多上报 */
    aucDigit[pstConnNumInfo->ucDigitNum] = '\0';

    /* 输出查询结果 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s%d,%d,%d,%d,%s%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CCONNNUM].pucText,
                                                    pstConnNumInfo->enNumType,
                                                    pstConnNumInfo->enNumPlan,
                                                    pstConnNumInfo->ucPi,
                                                    pstConnNumInfo->ucSi,
                                                    aucDigit,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallRedirNumInfoInd
 功能描述  : 处理TAF_CALL_EVT_REDIR_NUM_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CREDIRNUM: <number_type>,<number_plan>,<number>[,<pi>,<si>[,<redir_reason>]]<CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallRedirNumInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU                   *pstRedirNumInfo;
    VOS_UINT8                                               ucIndex;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               aucDigit[TAF_CALL_MAX_REDIRECTING_NUMBER_CHARI_OCTET_NUM + 1];

    usLength        = 0;


    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallRedirNumInfoInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstRedirNumInfo = (TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));
    PS_MEM_CPY(aucDigit, pstRedirNumInfo->aucDigitNum, pstRedirNumInfo->ucDigitNum);

    /* 在pstRedirNumInfo->aucDigitNum的最后一位加'\0',防止因pstRedirNumInfo->aucDigitNum无结束符，导致AT多上报 */
    aucDigit[pstRedirNumInfo->ucDigitNum] = '\0';

    /* 输出查询结果，根据EXTENSIONBIT1，EXTENSIONBIT2输出可选项 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_CREDIRNUM].pucText,
                                       pstRedirNumInfo->enNumType,
                                       pstRedirNumInfo->enNumPlan,
                                       aucDigit);

    if (VOS_TRUE == pstRedirNumInfo->bitOpPi)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstRedirNumInfo->ucPi);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",");
    }

    if (VOS_TRUE == pstRedirNumInfo->bitOpSi)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstRedirNumInfo->ucSi);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",");
    }

    if (VOS_TRUE == pstRedirNumInfo->bitOpRedirReason)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstRedirNumInfo->ucRedirReason);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",");
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallSignalInfoInd
 功能描述  : 处理TAF_CALL_EVT_SIGNAL_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CSIGTONE: <signal_type>,<alert_pitch>,<signal><CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallSignalInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_SIGNAL_INFO_IND_STRU   *pstsignalInfo;
    VOS_UINT8                            ucIndex;

    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallSignalInfoInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstsignalInfo = (TAF_CALL_EVT_SIGNAL_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    /* 输出查询结果 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s%d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CSIGTONE].pucText,
                                                    pstsignalInfo->ucSignalType,
                                                    pstsignalInfo->ucAlertPitch,
                                                    pstsignalInfo->ucSignal,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallLineCtrlInfoInd
 功能描述  : 处理TAF_CALL_EVT_LINE_CTRL_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CLCTR: <polarity_include>[,<toggle>][,<reverse_polarity>],<power_denial><CR><LF>
*****************************************************************************/
VOS_UINT32 AT_RcvTafCallLineCtrlInfoInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU                   *pstLineCtrlInfo;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               ucIndex;

    usLength = 0;

    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallLineCtrlInfoInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstLineCtrlInfo = (TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    /* 输出查询结果 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s%s%d",
                                    gaucAtCrLf,
                                    gastAtStringTab[AT_STRING_CLCTR].pucText,
                                    pstLineCtrlInfo->ucPolarityIncluded);

    if (VOS_TRUE == pstLineCtrlInfo->ucToggleModePresent)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstLineCtrlInfo->ucToggleMode);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",");
    }

    if (VOS_TRUE == pstLineCtrlInfo->ucReversePolarityPresent)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstLineCtrlInfo->ucReversePolarity);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",");
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d%s",
                                       pstLineCtrlInfo->ucPowerDenialTime,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallCCWACInd
 功能描述  : 处理TAF_CALL_EVT_CCWAC_INFO_IND事件
 输入参数  : MN_AT_IND_EVT_STRU                 *pEvtInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : y00307564
    修改内容   : 1X SS Project新生成函数

<CR><LF>^CCWAC: <digits>,<pi>,<si>,<number_type>,<number_plan>,<isPresent>[,<signalType>,
                <alertPitch>,<signal>]<CR><LF>

  2.日    期   : 2015年1月17日
    作    者   : y00307564
    修改内容   : 新增PI, SI字段

*****************************************************************************/
VOS_UINT32 AT_RcvTafCallCCWACInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_CCWAC_INFO_IND_STRU   *pstCCWAC;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucDigit[TAF_CALL_MAX_CALLING_NUMBER_CHARI_OCTET_NUM + 1];

    usLength = 0;

    /* 根据clientId获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallCCWACInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstCCWAC = (TAF_CALL_EVT_CCWAC_INFO_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));
    PS_MEM_CPY(aucDigit, pstCCWAC->aucDigit, pstCCWAC->ucDigitNum);

    /* 在pstCCWAC->aucDigit的最后一位加'\0',防止因pstCCWAC->aucDigit无结束符，导致AT多上报 */
    aucDigit[pstCCWAC->ucDigitNum] = '\0';

    /* 输出查询结果 */
    if (VOS_TRUE == pstCCWAC->ucSignalIsPresent)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%s%s%s,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                            gaucAtCrLf,
                                            gastAtStringTab[AT_STRING_CCWAC].pucText,
                                            aucDigit,
                                            pstCCWAC->ucPi,
                                            pstCCWAC->ucSi,
                                            pstCCWAC->enNumType,
                                            pstCCWAC->enNumPlan,
                                            pstCCWAC->ucSignalIsPresent,
                                            pstCCWAC->ucSignalType,
                                            pstCCWAC->ucAlertPitch,
                                            pstCCWAC->ucSignal,
                                            gaucAtCrLf);

    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%s%s%s,%d,%d,%d,%d,%d,,,%s",
                                            gaucAtCrLf,
                                            gastAtStringTab[AT_STRING_CCWAC].pucText,
                                            aucDigit,
                                            pstCCWAC->ucPi,
                                            pstCCWAC->ucSi,
                                            pstCCWAC->enNumType,
                                            pstCCWAC->enNumPlan,
                                            pstCCWAC->ucSignalIsPresent,
                                            gaucAtCrLf);
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


VOS_UINT32 At_TestCContinuousDTMFPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^CCONTDTMF: (1,2),(0,1),(0-9,*,#)");
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_SetCContinuousDTMFPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;
    TAF_CALL_CONT_DTMF_PARA_STRU        stContDtmfPara;

    /* Check the validity of parameter */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_WARN_LOG("AT_SetCContinuousDTMFPara: Non set command!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*  Check the validity of <Call_ID> and <Switch> */
    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen))
    {
        AT_WARN_LOG("AT_SetCContinuousDTMFPara: Invalid <Call_ID> or <Switch>!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* If the <Switch> is Start and the number of parameter isn't equal to 3.
       Or if the <Switch> is Stop and the number of parameter isn't equal to 2，both invalid */
    if (((TAF_CALL_CONT_DTMF_STOP == gastAtParaList[1].ulParaValue)
      && (AT_CCONTDTMF_PARA_NUM_MIN != gucAtParaIndex))
     || ((TAF_CALL_CONT_DTMF_START == gastAtParaList[1].ulParaValue)
      && (AT_CCONTDTMF_PARA_NUM_MAX != gucAtParaIndex)))
    {
        AT_WARN_LOG("AT_SetCContinuousDTMFPara: The number of parameters mismatch!");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* If the <Switch> is Start,the <Dtmf_Key> should be setted and check its validity */
    if (TAF_CALL_CONT_DTMF_START == gastAtParaList[1].ulParaValue)
    {
        if (VOS_ERR == AT_CheckCContDtmfKeyPara())
        {
            AT_WARN_LOG("AT_SetCContinuousDTMFPara: Invalid <Dtmf_Key>!");
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    PS_MEM_SET(&stContDtmfPara, 0, sizeof(stContDtmfPara));
    stContDtmfPara.ucCallId     = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stContDtmfPara.enSwitch     = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stContDtmfPara.ucDigit      = (VOS_UINT8)gastAtParaList[2].aucPara[0];

    /* Send TAF_CALL_APP_SEND_CONT_DTMF_REQ Message */
    ulRst = TAF_XCALL_SendContinuousDtmf(gastAtClientTab[ucIndex].usClientId,
                                         gastAtClientTab[ucIndex].opId,
                                        &stContDtmfPara);
    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCONTDTMF_SET;

        /* Return hang-up state */
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}


VOS_UINT32 AT_CheckCContDtmfKeyPara(VOS_VOID)
{
    if (1 != gastAtParaList[2].usParaLen)
    {
        return VOS_ERR;
    }

    if ((('0' <= gastAtParaList[2].aucPara[0]) && ('9' >= gastAtParaList[2].aucPara[0]))
      || ('*' == gastAtParaList[2].aucPara[0])
      || ('#' == gastAtParaList[2].aucPara[0]))
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}


VOS_UINT32 AT_RcvTafCallSndContinuousDTMFCnf(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU                   *pstContDtmfCnf = VOS_NULL_PTR;

    /* According to ClientID to get the index */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallSndContinuousDTMFCnf: Get Index Fail!");
        return VOS_ERR;
    }

    /* AT module is waiting for report the result of ^CCONTDTMF command */
    if (AT_CMD_CCONTDTMF_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvTafCallSndContinuousDTMFCnf: Error Option!");
        return VOS_ERR;
    }

    /* Use AT_STOP_TIMER_CMD_READY to recover the AT command state to READY state */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* According to the error code of temporary respond, printf the result of command */
    pstContDtmfCnf = (TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));
    if (TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS != pstContDtmfCnf->enResult)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvTafCallSndContinuousDTMFRslt(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    return VOS_OK;
}


VOS_UINT32 AT_RcvTafCallRcvContinuousDtmfInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU                    *pstRcvContDtmf = VOS_NULL_PTR;
    VOS_UINT8                                               aucDigit[2];
    VOS_UINT8                                               ucIndex;

    /* According to ClientID to get the index */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallRcvContinuousDtmfInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* initialization */
    pstRcvContDtmf = (TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    /*  Initialize aucDigit[0] with pstRcvContDtmf->ucDigit and  aucDigit[1] = '\0'
        Because At_sprintf does not allow to print pstRcvContDtmf->ucDigit with %c
        Hence, need to convert digit into string and print as string */
    aucDigit[0] = pstRcvContDtmf->ucDigit;
    aucDigit[1] = '\0';

    /* Output the inquire result */
    if (TAF_CALL_CONT_DTMF_START == pstRcvContDtmf->enSwitch)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^CCONTDTMF: %d,%d,\"%s\"%s",
                                                        gaucAtCrLf,
                                                        pstRcvContDtmf->ucCallId,
                                                        pstRcvContDtmf->enSwitch,
                                                        aucDigit,
                                                        gaucAtCrLf);
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^CCONTDTMF: %d,%d%s",
                                                        gaucAtCrLf,
                                                        pstRcvContDtmf->ucCallId,
                                                        pstRcvContDtmf->enSwitch,
                                                        gaucAtCrLf);
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvTafCallRcvBurstDtmfInd(
    MN_AT_IND_EVT_STRU                 *pEvtInfo
)
{
    TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU                   *pstRcvBurstDtmf = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               aucDigit[TAF_CALL_MAX_BURST_DTMF_NUM + 1];

    /* According to ClientID to get the index */
    if(AT_FAILURE == At_ClientIdToUserId(pEvtInfo->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallRcvBurstDtmfInd: Get Index Fail!");
        return VOS_ERR;
    }

    /* initialization */
    pstRcvBurstDtmf = (TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU *)(pEvtInfo->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));
    PS_MEM_CPY(aucDigit, pstRcvBurstDtmf->aucDigit, pstRcvBurstDtmf->ucDigitNum);

    /* Add the '\0' to the last byte of pstRcvBurstDtmf->aucDigit */
    aucDigit[pstRcvBurstDtmf->ucDigitNum] = '\0';

    /* Output the inquire result */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CBURSTDTMF: %d,\"%s\",%d,%d%s",
                                                    gaucAtCrLf,
                                                    pstRcvBurstDtmf->ucCallId,
                                                    aucDigit,
                                                    pstRcvBurstDtmf->ulOnLength,
                                                    pstRcvBurstDtmf->ulOffLength,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafCallCclprCnf
 功能描述  : AT收到TAF_CALL_EVT_CCLPR_SET_CNF事件处理函数
 输入参数  : MN_AT_IND_EVT_STRU *pstData
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月10日
    作    者   : f00279542
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID AT_RcvTafCallCclprCnf(MN_AT_IND_EVT_STRU *pstData)
{
    TAF_CALL_EVT_CCLPR_GET_CNF_STRU    *pstCClprGetCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    ucIndex = 0;

    /* 通过ClientId获取ucIndex */
    if(AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallCclprCnf: WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* 如果为广播类型，则返回AT_ERROR */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafCallCclprCnf: WARNING:AT_BROADCAST_INDEX!");
        return;
    }

    /* 判断当前操作类型是否为AT_CMD_CCLPR_GET */
    if (AT_CMD_CCLPR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvTafCallCclprCnf: WARNING:Not AT_CMD_CCLPR_GET!");
        return;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstCClprGetCnf = (TAF_CALL_EVT_CCLPR_GET_CNF_STRU *)(pstData->aucContent
                                              + sizeof(MN_CALL_EVENT_ENUM_U32));
    /* 判断查询操作是否成功 */
    if (TAF_ERR_NO_ERROR != pstCClprGetCnf->ulRet)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return;
    }

    usLength = 0;

    if (TAF_CALL_PRESENTATION_BUTT != pstCClprGetCnf->enPI)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: %d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pstCClprGetCnf->enPI);

    }
    /* 打印结果 */
    gstAtSendData.usBufLen  = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return;

}

/*****************************************************************************
 函 数 名  : AT_TestCclprPara
 功能描述  : 设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月10日
    作    者   : f00279542
    修改内容   : 新增

*****************************************************************************/
VOS_UINT32 AT_TestCclprPara( VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-2)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_SetCclprPara
 功能描述  : ^CCLPR=<call_id>设置命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月10日
    作    者   : f00279542
    修改内容   : 新增

*****************************************************************************/
VOS_UINT32 AT_SetCclprPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数检查 */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 发送跨核消息TAF_CALL_APP_SND_CCLPR_REQ到C核,  */
    ulResult = TAF_XCALL_SendCclpr(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                  (MN_CALL_ID_T)gastAtParaList[0].ulParaValue);
    if (VOS_OK != ulResult)
    {
        AT_WARN_LOG("AT_SetCclprPara: TAF_XCALL_SendCclpr fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCLPR_SET;

    return AT_WAIT_ASYNC_RETURN;

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

