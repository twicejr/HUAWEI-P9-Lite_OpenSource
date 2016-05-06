

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "AppVcApi.h"
#include "vos.h"
#include "PsCommonDef.h"
#include "ATCmdProc.h"

#ifdef  __cplusplus
  #if  __cplusplus
      extern "C"{
  #endif
#endif



/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_VC_API_C
/*lint +e767 +e960*/

/*****************************************************************************
   2 函数实现
*****************************************************************************/

/*****************************************************************************
函 数 名  : VCI_SetVoiceVolume
功能描述  : 设置输出音量
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK
调用函数  : SI_InitGlobeVariable
被调函数  :
修订记录  :
1.  日    期   : 2009年07月05日
    作    者   : h44270
    修改内容   : Creat
2.  日    期   : 2011年11月07日
    作    者   : f00179208
    修改内容   : AT Project, 修改虚拟WUEPS_PID_VC为WUEPS_PID_AT
3.  日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32  APP_VC_SetVoiceVolume(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT8                           ucVoiceVolume
)
{
    /*构造消息发送消息给VC模块*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 申请消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetVoiceVolume: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_SET_VOLUME;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = ucVoiceVolume;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetVoiceVolume: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : APP_VC_SetVoiceMode
功能描述  : 设置语音模式
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK
调用函数  : SI_InitGlobeVariable
被调函数  :
修订记录  :
  1.日    期   : 2009年07月05日
    作    者   : h44270
    修改内容   : Creat
  2.日    期   : 2011年11月07日
    作    者   : f00179208
    修改内容   : AT Project, 修改虚拟WUEPS_PID_VC为WUEPS_PID_AT
  3.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
  4.日    期   : 2013年9月30日
    作    者   : Y00213812
    修改内容   : DTS2013092802198: ^VMSET & ^CVOICE发送到指定的模块
  5.日    期   : 2015年5月28日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32  APP_VC_SetVoiceMode(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT8                           ucVoiceMode
)
{
    /*构造消息发送消息给VC模块*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 申请消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetVoiceMode: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_SET_MODE;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = ucVoiceMode;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetVoiceMode: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : APP_VC_SetVoicePort
功能描述  : 设置语音端口
输入参数  : APP_VC_VOICE_PORT_ENUM_U8   ucVoicePort - 设置的语音端口
输出参数  : 无
返 回 值  : 当前的语音端口
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年04月16日
    作    者   : o00132663
    修改内容   : Creat
2.  日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目
3.  日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 APP_VC_SetVoicePort(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort
)
{
    /*构造消息发送消息给VC模块*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;


    /* 申请消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetVoicePort: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_SET_PORT;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = ucVoicePort;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoiceMode: SEND MSG FAIL.");
        return VOS_ERR;
    }
    return VOS_OK;

}

/*****************************************************************************
函 数 名  : APP_VC_GetVoiceMode
功能描述  : 获取当前的语音模式
输入参数  : 无
输出参数  : 无
返 回 值  : TAF_SUCCESS
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2011年10月05日
    作    者   : f00179208
    修改内容   : Creat
2.  日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目, 发送异步消息到C核获取语音模式
3.  日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 APP_VC_GetVoiceMode(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    /*构造消息发送消息给VC模块*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 申请消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_GetVoiceMode: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_QRY_MODE;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = 0;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoiceMode: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : APP_VC_GetVoicePort
功能描述  : 获取当前的语音端口
输入参数  :     MN_CLIENT_ID_T              ClientId
                MN_OPERATION_ID_T           OpId

输出参数  : 无
返 回 值  : VOS_UINT32 - VOS_OK
                         VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年04月16日
    作    者   : o00132663
    修改内容   : Creat
2.  日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目
3.  日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 APP_VC_GetVoicePort(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    /*构造消息发送消息给VC模块*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 申请消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_GetVoicePort: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* 组装消息 */
    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_QRY_PORT;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = 0;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoicePort: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : APP_VC_AppVcVoiceMode2VcPhyVoiceMode
功能描述  : 应用与VC模块语音模式定义转换为VC模块与物理层语音模式接口定义
输入参数  : APP_VC_VOICE_MODE_ENUM_U16  usVoiceMode - 应用与VC接口语音模式定义
输出参数  : 无
返 回 值  : VC_PHY_DEVICE_MODE_ENUM_U16 - VC与物理层语音模式定义
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2021年04月17日
    作    者   : o00132663
    修改内容   : Creat
2.  日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目, 将该函数从C核移植到A核
*****************************************************************************/
VC_PHY_DEVICE_MODE_ENUM_U16  APP_VC_AppVcVoiceMode2VcPhyVoiceMode(
    APP_VC_VOICE_MODE_ENUM_U16          usVoiceMode
)
{
    switch(usVoiceMode)
    {
        case APP_VC_VOICE_MODE_PCVOICE:
            return VC_PHY_DEVICE_MODE_PCVOICE;

        case APP_VC_VOICE_MODE_EARPHONE:
            return VC_PHY_DEVICE_MODE_EARPHONE;

        case APP_VC_VOICE_MODE_HANDSET:
            return VC_PHY_DEVICE_MODE_HANDSET;

        case APP_VC_VOICE_MODE_HANDS_FREE:
            return VC_PHY_DEVICE_MODE_HANDS_FREE;

        default:
            AT_WARN_LOG1("APP_VC_AppVcVoiceMode2VcPhyVoiceMode: wrong usVoiceMode ", usVoiceMode);
            return VC_PHY_DEVICE_MODE_BUTT;
    }

}

/*****************************************************************************
函 数 名  : APP_VC_VcPhyVoiceMode2AppVcVoiceMode
功能描述  : VC模块与物理层语音模式接口定义转换为应用与VC模块语音模式定义
输入参数  : VC_PHY_DEVICE_MODE_ENUM_U16  usVoiceMode - VC与物理层语音模式定义
输出参数  : 无
返 回 值  : APP_VC_VOICE_MODE_ENUM_U16 - 应用与VC接口语音模式定义
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2021年04月17日
    作    者   : o00132663
    修改内容   : Creat
2.  日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目, 将该函数从C核移植到A核
*****************************************************************************/
APP_VC_VOICE_MODE_ENUM_U16  APP_VC_VcPhyVoiceMode2AppVcVoiceMode(
    VC_PHY_DEVICE_MODE_ENUM_U16         usVoiceMode
)
{
    switch(usVoiceMode)
    {
        case VC_PHY_DEVICE_MODE_PCVOICE:
            return APP_VC_VOICE_MODE_PCVOICE;

        case VC_PHY_DEVICE_MODE_EARPHONE:
            return APP_VC_VOICE_MODE_EARPHONE;

        case VC_PHY_DEVICE_MODE_HANDSET:
            return APP_VC_VOICE_MODE_HANDSET;

        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            return APP_VC_VOICE_MODE_HANDS_FREE;

        default:
            AT_WARN_LOG1("APP_VC_VcPhyVoiceMode2AppVcVoiceMode: wrong usVoiceMode ", usVoiceMode);
            return APP_VC_VOICE_MODE_BUTT;
    }

}

/*****************************************************************************
 函 数 名  : APP_VC_GetVoiceVolume
 功能描述  : 获取输出音量
 输入参数  : MN_CLIENT_ID_T                      ClientId
             MN_OPERATION_ID_T                   OpId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月10日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32  APP_VC_GetVoiceVolume(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    /*构造消息发送消息给VC模块*/
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 申请消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                  sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_GetVoiceVolume: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    pstMsg->clientId                    = ClientId;
    pstMsg->opId                        = OpId;
    pstMsg->enMsgName                   = APP_VC_MSG_REQ_QRY_VOLUME;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverPid               = AT_GetDestPid(ClientId, I0_WUEPS_PID_VC);
    pstMsg->aucContent[0]               = 0;
    pstMsg->aucContent[1]               = 0;
    pstMsg->aucContent[2]               = 0;
    pstMsg->aucContent[3]               = 0;

    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_GetVoiceVolume: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetMuteStatus
 功能描述  : 获取静音状态
 输入参数  : usClientId   - 客户端ID
             ucOpId       - 操作码ID
             enMuteStatus - 静音状态
 输出参数  : 无
 返 回 值  : VOS_OK       - 成功
             VOS_ERR      - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 APP_VC_SetMuteStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    APP_VC_MUTE_STATUS_ENUM_UINT8       enMuteStatus
)
{
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 构造消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_AT,
                                        sizeof(APP_VC_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = AT_GetDestPid(usClientId, I0_WUEPS_PID_VC);
    pstMsg->enMsgName       = APP_VC_MSG_SET_MUTE_STATUS_REQ;

    /* 填写消息内容 */
    pstMsg->clientId        = usClientId;
    pstMsg->opId            = ucOpId;
    pstMsg->aucContent[0]   = enMuteStatus;

    /* 发送消息 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VC_SetMuteStatus
 功能描述  : 设置静音状态
 输入参数  : usClientId   - 客户端ID
             ucOpId       - 操作码ID
             enMuteStatus - 静音状态
 输出参数  : 无
 返 回 值  : VOS_OK       - 成功
             VOS_ERR      - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 APP_VC_GetMuteStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 构造消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_AT,
                                        sizeof(APP_VC_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = AT_GetDestPid(usClientId, I0_WUEPS_PID_VC);
    pstMsg->enMsgName       = APP_VC_MSG_GET_MUTE_STATUS_REQ;

    /* 填写消息内容 */
    pstMsg->clientId        = usClientId;
    pstMsg->opId            = ucOpId;

    /* 发送消息 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetMuteStatus: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VC_SetModemLoop
 功能描述  : 设置进入或退出语音换回
 输入参数  : usClientId   - 客户端ID
             ucOpId       - 操作码ID
             ucModemLoop  - 进入或退出语音环回状态
 输出参数  : 无
 返 回 值  : VOS_OK       - 成功
             VOS_ERR      - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 APP_VC_SetModemLoop(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucModemLoop
)
{
    VOS_UINT32                          ulRslt;
    APP_VC_REQ_MSG_STRU                *pstMsg;

    /* 构造消息 */
    pstMsg = (APP_VC_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_AT,
                                        sizeof(APP_VC_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("APP_VC_SetModemLoop: ALLOC MSG FAIL.");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(APP_VC_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = AT_GetDestPid(usClientId, I0_WUEPS_PID_VC);
    pstMsg->enMsgName       = APP_VC_MSG_SET_MODEMLOOP_REQ;

    /* 填写消息内容 */
    pstMsg->clientId        = usClientId;
    pstMsg->opId            = ucOpId;
    pstMsg->aucContent[0]   = ucModemLoop;

    /* 发送消息 */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMsg);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("APP_VC_SetModemLoop: SEND MSG FAIL.");
        return VOS_ERR;
    }

    return VOS_OK;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

