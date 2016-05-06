/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcMnccProc.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月31日
  最近修改   : 2008年2月14日
  功能描述   : 接收和处理来自上层的MNCC原语
  函数列表   :
              NAS_CC_ProcMnccAlertReq
              NAS_CC_ProcMnccCallConfReq
              NAS_CC_ProcMnccDiscReq
              NAS_CC_ProcMnccEmergSetupReq
              NAS_CC_ProcMnccFacilityReq
              NAS_CC_ProcMnccHoldReq
              NAS_CC_ProcMnccModifyRej
              NAS_CC_ProcMnccModifyReq
              NAS_CC_ProcMnccModifyRes
              NAS_CC_ProcMnccRejReq
              NAS_CC_ProcMnccRelReq
              NAS_CC_ProcMnccRetrieveReq
              NAS_CC_ProcMnccSetupReq
              NAS_CC_ProcMnccSetupRsp
              NAS_CC_ProcMnccStartDtmfReq
              NAS_CC_ProcMnccStopDtmfReq
              NAS_CC_ProcMnccPrimitive
  修改历史   :
  1.日    期   : 2007年8月31日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年10月25日
    作    者   : s62952
    修改内容   : 问题单号:A32D14142,在通话117时，拨打1，2等DTMF字符时，会中断117通话

  3.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  4.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS1
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "NasCcInclude.h"
#include "NasMmlCtx.h"
#include "MnCall.h"
#include "NasCcCtx.h"
#include "NasCcProcNvim.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_MMNC_PROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 变量定义
*****************************************************************************/
/* 编码缓存，用于存放编码生成的空口消息数据 */
LOCAL NAS_CC_AIR_MSG_BUF_STRU  f_stCcEncodeBuf;

NAS_CC_UUS1_INFO_STRU    f_astUus1MsgBuf[NAS_CC_MAX_UUIE_MSG_NUM];

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccEmergSetupReq
 功能描述  : 处理MNCC_EMERG_SETUP_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 发送Est Req到MM时，增加呼叫模式，表明是语音呼叫还是可视电话

  3.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 增加ALS多线路支持
  4.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  5.日    期   : 2015年8月25日
    作    者   : s00217060
    修改内容   : User_Exp_Improve:新增是否重拨标志
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccEmergSetupReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_EMERGENCY_SETUP,
                            &pstMsg->unParam.stEmerg.stHeader);

    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0_1);

    /* 增加redial入参 */
    NAS_CC_SendMmccEstReq(ucTi, MMCC_EMERGENCY_CALL,MMCC_CALL_MODE_SPEECH,
                          MMCC_NO_CALL_PRIORITY, pstMsg->ucRedialFlg);

    NAS_CC_StartTimer(entityId, TI_NAS_CC_T303, 0);

    /* 编码emergency setup消息并缓存 */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stEmerg,
                     g_stNasCcBufferedSetupMsg.aucBuf,
                     (VOS_UINT8 *)&g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_INFO_LOG("NAS_CC_ProcMnccEmergSetupReq: ChangeCallState to U0_1");

    /* 记录呼叫的一些参数 */
    stBcParams.enItc = pstMsg->unParam.stEmerg.stBC.Octet3.InfoTransCap;
    NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccCallConfReq
 功能描述  : 处理MNCC_CALL_CONF_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccCallConfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    if (NAS_CC_CALL_STATE_U6 == enCurrState)
    {
        /* 填写call confirm消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CALL_CNF, &pstMsg->unParam.stCallCnf.stHeader);

        /* 编码call confirm消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stCallCnf,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccCallConfReq: ChangeCallState to U9");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U9);

        NAS_CC_UpdateCallId(entityId, pstMsg->ucCallId);

        /* 如果BC改变，需要更新已保存的承载能力参数 */
        if (pstMsg->unParam.stCallCnf.stBC1.IsExist)
        {
            stBcParams.enItc = pstMsg->unParam.stCallCnf.stBC1.Octet3.InfoTransCap;
            NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
            if (pstMsg->unParam.stCallCnf.stBC2.IsExist)
            {
                stBcParams.enItc = pstMsg->unParam.stCallCnf.stBC2.Octet3.InfoTransCap;
                NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
            }
        }

        /* 信道已经接入的情况,需要设置当前使用此信道的每一个呼叫实体.
           避免多个呼叫存在时,原来的呼叫被释放后,就断开信道
           CC在呼叫结束的时候,会清除此标志*/
        if (VOS_TRUE == NAS_CC_IsAttachUserConn())
        {
            NAS_CC_SetUserConnEntity(entityId);
        }
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccCallConfReq: bad state.", enCurrState);
    }
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccCcEstCnfReq
 功能描述  : 处理MNCC_CC_EST_CNF_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
             entityId    - 处理该原语的CC实体的ID
             ucTi        - CC实体对应的transaction ID
             enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :  2009-12-25
    作    者   :  z00161729
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccCcEstCnfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U0_4 == enCurrState)
    {
        /* 填写cc establishment cnf消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CC_EST_CNF,
                                &pstMsg->unParam.stCcEstCnf.stHeader);

        /* 编码cc establishment cnf消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stCcEstCnf,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T335, 0);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccCcEstCnfReq: ChangeCallState to U0.5");

        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0_5);

        NAS_CC_UpdateCallId(entityId, pstMsg->ucCallId);

    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccCcEstCnfReq: bad state.", enCurrState);
    }
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccSetupReq
 功能描述  : 处理MNCC_SETUP_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
             entityId    - 处理该原语的CC实体的ID
             ucTi        - CC实体对应的transaction ID
             enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccCcbsSetupReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_SETUP, &pstMsg->unParam.stSetup.stHeader);
    NAS_CC_StartTimer(entityId, TI_NAS_CC_T303, 0);

    /* 此处放在上面的目的是由于NAS_CC_GetMsgUus1Info会使用到更新后的ITC  */
    /* 记录呼叫的承载能力参数 */
    stBcParams.enItc = pstMsg->unParam.stSetup.stBC1.Octet3.InfoTransCap;
    NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
    if (pstMsg->unParam.stSetup.stBC2.IsExist)
    {
        stBcParams.enItc = pstMsg->unParam.stSetup.stBC2.Octet3.InfoTransCap;
        NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
    }

    /* 判断UUS1是否激活 */
    NAS_CC_GetMsgUus1Info(entityId,
                          NAS_CC_MSG_SETUP,
                          &pstMsg->unParam.stSetup.stUserUser);

    /* 编码setup消息并缓存 */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stSetup,
                     g_stNasCcBufferedSetupMsg.aucBuf,
                     (VOS_UINT8 *)&g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_SendMmccDataReq(ucTi, g_stNasCcBufferedSetupMsg.aucBuf,
                           g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_INFO_LOG("NAS_CC_ProcMnccCcbsSetupReq: ChangeCallState to U1");
    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U1);


}

/*****************************************************************************
 函 数 名  : NAS_CC_IsNeedCreateEntity
 功能描述  : 当收到MNCC_SETUP_REQ消息后判断是否需要新建实体
 输入参数  : enPrimName  - MNCC原语名
             ucTi        - transaction ID
             pentityId   - 处理该原语的CC实体的ID
 输出参数  : VOS_TRUE: 需要新建实体
             VOS_FALSE:不需要新建实体
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年2月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL NAS_CC_IsNeedCreateEntity(
    MNCC_PRIM_NAME_ENUM_U16             enPrimName,
    VOS_UINT8                           ucTi,
    NAS_CC_ENTITY_ID_T                  *pentityId
)
{
    VOS_BOOL                            bIsCreateEntity;

    bIsCreateEntity = VOS_TRUE;

    /* CCBS打开时收到Setup消息时不需要创建Entity,其他情况下需要创建 */
    if (enPrimName == MNCC_SETUP_REQ)
    {
        *pentityId = NAS_CC_GetEntityByTi(ucTi);
        if (NAS_CC_INVALID_ENTITY_ID != *pentityId)
        {
            bIsCreateEntity = VOS_FALSE;
        }
    }
    return bIsCreateEntity;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetCallMode
 功能描述  : 获取当前呼叫模式
 输入参数  : pstSetup - 呼叫参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月21日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_GetCallMode(
    NAS_CC_MSG_SETUP_MO_STRU            *pstSetup
)
{
    if ( ( NAS_CC_ITC_SPEECH == pstSetup->stBC1.Octet3.InfoTransCap )
      || ( NAS_CC_ITC_AUXILIARY_SPEECH == pstSetup->stBC1.Octet3.InfoTransCap ))
    {
        return MMCC_CALL_MODE_SPEECH;
    }
    else
    {
        if ( ( NAS_CC_ITC_UDI == pstSetup->stBC1.Octet3.InfoTransCap )
          && ( NAS_CC_IE_EXT  == pstSetup->stBC1.Octet5.Ext )
          && ( NAS_CC_OTHER_RA_H223_H245 == pstSetup->stBC1.Octet5a.OtherRA ))
        {
            return MMCC_CALL_MODE_VIDEO;
        }
    }
    return MMCC_CALL_MODE_OTHER;
}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccSetupReq
 功能描述  : 处理MNCC_SETUP_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年2月23日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  4.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  5.日    期   : 2015年8月25日
    作    者   : s00217060
    修改内容   : User_Exp_Improve:增加是否重拨标志
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccSetupReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;
    VOS_UINT32                          ulCallMode;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();


    if ( (NAS_CC_CALL_STATE_U0_6 == enCurrState)
       &&(NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg))
    {
        NAS_CC_ProcMnccCcbsSetupReq(pstMsg,entityId,ucTi,enCurrState);
        return;
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_SETUP, &pstMsg->unParam.stSetup.stHeader);

    /* 获取当前呼叫模式 */
    ulCallMode = NAS_CC_GetCallMode(&pstMsg->unParam.stSetup);

    /* 此处放在上面的目的是由于NAS_CC_GetMsgUus1Info会使用到更新后的ITC,不能放在后面  */

    /* 记录呼叫的承载能力参数 */
    stBcParams.enItc = pstMsg->unParam.stSetup.stBC1.Octet3.InfoTransCap;
    NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
    if (pstMsg->unParam.stSetup.stBC2.IsExist)
    {
        stBcParams.enItc = pstMsg->unParam.stSetup.stBC2.Octet3.InfoTransCap;
        NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
    }

    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0_1);

    /* 增加redial入参 */
    NAS_CC_SendMmccEstReq(ucTi, MMCC_MO_NORMAL_CALL,ulCallMode,MMCC_NO_CALL_PRIORITY, pstMsg->ucRedialFlg);

    NAS_CC_StartTimer(entityId, TI_NAS_CC_T303, 0);

    /* 判断UUS1是否激活 */
    NAS_CC_GetMsgUus1Info(entityId,
                          NAS_CC_MSG_SETUP,
                          &(pstMsg->unParam.stSetup.stUserUser));

    /* 编码setup消息并缓存 */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stSetup,
                     g_stNasCcBufferedSetupMsg.aucBuf,
                     (VOS_UINT8 *)&g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_INFO_LOG("NAS_CC_ProcMnccSetupReq: ChangeCallState to U0_1");

    /* 信道已经接入的情况,需要设置当前使用此信道的每一个呼叫实体.
       避免多个呼叫存在时,原来的呼叫被释放后,就断开信道
       CC在呼叫结束的时候,会清除此标志*/
    if (VOS_TRUE == NAS_CC_IsAttachUserConn())
    {
        NAS_CC_SetUserConnEntity(entityId);
    }


}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccAlertReq
 功能描述  : 处理MNCC_ALERT_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccAlertReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U9 == enCurrState)
    {
        /* 填写alerting消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_ALERTING, &pstMsg->unParam.stAlert.stHeader);


        /* 判断UUS1是否激活 */
        NAS_CC_GetMsgUus1Info(entityId,
                              NAS_CC_MSG_ALERTING,
                              &(pstMsg->unParam.stAlert.stUserUser));

        /* 编码alerting消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stAlert,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccAlertReq: ChangeCallState to U7");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U7);

        /* 信道已经接入的情况,需要设置当前使用此信道的每一个呼叫实体.
           避免多个呼叫存在时,原来的呼叫被释放后,就断开信道
           CC在呼叫结束的时候,会清除此标志*/
        if (VOS_TRUE == NAS_CC_IsAttachUserConn())
        {
            NAS_CC_SetUserConnEntity(entityId);
        }
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccAlertReq: bad state.", enCurrState);
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccSetupRsp
 功能描述  : 处理MNCC_SETUP_RES原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccSetupRsp(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    if ((NAS_CC_CALL_STATE_U9 == enCurrState)
      ||(NAS_CC_CALL_STATE_U7 == enCurrState))
    {
        /* 填写connect消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CONNECT, &pstMsg->unParam.stConn.stHeader);

        /* 判断UUS1是否激活 */
        NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_CONNECT,&(pstMsg->unParam.stConn.stUserUser));

        /* 编码connect消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stConn,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T313, 0);

        /*
        [5.2.2.9 User connection attachment during a mobile terminating call]
        For speech calls: The mobile station shall attach the user connection
        at latest when sending the connect message.
        */
        NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_CURR, &stBcParams);
        if ( (NAS_CC_ITC_SPEECH == stBcParams.enItc)
          || (NAS_CC_ITC_AUXILIARY_SPEECH == stBcParams.enItc))
        {
            NAS_CC_AttachUserConn(entityId, NAS_CC_ITC_SPEECH);
        }

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccSetupRsp: ChangeCallState to U8");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U8);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccSetupRsp: bad state.", enCurrState);
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccDiscReq
 功能描述  : 处理MNCC_DISC_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年2月23日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccDiscReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if ((NAS_CC_CALL_STATE_U0 == enCurrState)
      ||(NAS_CC_CALL_STATE_U11 == enCurrState)
      ||(NAS_CC_CALL_STATE_U19 == enCurrState))
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccDiscReq: bad state.", enCurrState);
        return;
    }

    NAS_CC_StopAllTimer(entityId);

    switch (enCurrState)
    {
        case NAS_CC_CALL_STATE_U0_1:
            /* MM连接还未建立成功，直接释放MM连接 */
            NAS_CC_SendMmccAbortReq(ucTi);
            NAS_CC_SendMnccMsg(entityId, MNCC_REL_CNF, VOS_NULL_PTR, 0);
            NAS_CC_INFO_LOG1("NAS_CC_ProcMnccDiscReq: ChangeCallState to U0, current state:", enCurrState);
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
            break;

        case NAS_CC_CALL_STATE_U12:
            /* disconnect indication状态，向网络发送release消息 */
            NAS_CC_SendRelease(ucTi, VOS_FALSE, 0, VOS_FALSE, 0);
            NAS_CC_StartTimer(entityId, TI_NAS_CC_T308, NAS_CC_T308_FIRST);
            NAS_CC_INFO_LOG1("NAS_CC_ProcMnccDiscReq: ChangeCallState to U19, current state:", enCurrState);
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U19);
            break;

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        case NAS_CC_CALL_STATE_U0_6:
            if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                /*用户拒绝回呼，发送release complete消息*/
                NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_17);
                NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);
                NAS_CC_SendMnccMsg(entityId, MNCC_REL_CNF, VOS_NULL_PTR, 0);
                NAS_CC_INFO_LOG1("NAS_CC_ProcMnccDiscReq: ChangeCallState to U0, current state:", enCurrState);
                NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
            }

            break;
       /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */

        default:
            /* 断开用户连接(TBD) */

            /* 填写disconnect消息头 */
            NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_DISCONNECT, &pstMsg->unParam.stDisc.stHeader);

            /* 判断UUS1是否激活 */
            NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_DISCONNECT,&(pstMsg->unParam.stDisc.stUserUser));

            /* 编码disconnect消息 */
            NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stDisc,
                             f_stCcEncodeBuf.aucBuf,
                             (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

            /* 发送MMCC_DATA_REQ原语将消息发往网络 */
            NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

            NAS_CC_StartTimer(entityId,
                              TI_NAS_CC_T305,
                              pstMsg->unParam.stDisc.stCause.Octet4.CauseValue);
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U11);
    }

/*
还需考虑的:
In the "mobile terminating call confirmed" state or the "call received" state,
if the user of a mobile station is User Determined User Busy then a DISCONNECT
message shall be sent with cause #17 "user busy". In the "mobile terminating call
confirmed" state, if the user of a mobile station wishes to reject the call then
a DISCONNECT message shall be sent with cause #21 "call rejected".
*/
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccRelReq
 功能描述  : 处理MNCC_REL_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccRelReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U12 == enCurrState)
    {
        NAS_CC_StopAllTimer(entityId);

        /* 填写release消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE, &pstMsg->unParam.stRel.stHeader);

        /* 判断UUS1是否激活 */
        NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE,&(pstMsg->unParam.stRel.stUserUser));

        /* 编码release消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stRel,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T308, NAS_CC_T308_FIRST);
        NAS_CC_INFO_LOG("NAS_CC_ProcMnccRelReq ChangeCallState to U19");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U19);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRelReq: bad state.", enCurrState);
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccRejReq
 功能描述  : 处理MNCC_REJ_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccRejReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U6 == enCurrState)
    {
        NAS_CC_StopAllTimer(entityId);

        /* 填写release complete消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE_COMPLETE, &pstMsg->unParam.stRelComp.stHeader);

        /* 判断UUS1是否激活 */
        NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE_COMPLETE,&(pstMsg->unParam.stRelComp.stUserUser));

        /* 编码release complete消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stRelComp,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccRelReq ChangeCallState to U0");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRejReq: bad state.", enCurrState);
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccFacilityReq
 功能描述  : 处理MNCC_FACILITY_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
             entityId    - 处理该原语的CC实体的ID
             ucTi        - CC实体对应的transaction ID
             enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
  4.日    期   : 2014年5月31日
    作    者   : z00161729
    修改内容   : DTS2014060402388:一路active呼叫，一路hold的mpty呼叫，at+chld=1过程中丢网所有呼叫都被释放后call状态异常挂死，hold mpty呼叫无法恢复
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccFacilityReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{

    NAS_SS_OPERATION_ENUM_U8            enOperation;
    NAS_CC_FACILITY_INFO_STRU           stFacInfo;
    VOS_UINT32                          ulResult;


    enOperation = NAS_SS_OPERATION_BUTT;

    (VOS_VOID)NAS_CC_GetFacilityInfo(pstMsg->unParam.stFac.stFacility.aucFacility, &stFacInfo);

    /* 取得facility中的ss operation code */
    if (stFacInfo.bOpCodePresent)
    {
        enOperation = stFacInfo.enOpCode;
    }
    else
    {
        if (VOS_ERR == NAS_CC_RestoreSsOperation(entityId,
                                      stFacInfo.ucInvokeID,
                                      &enOperation))
        {
            NAS_CC_ERR_LOG("NAS_CC_ProcMnccFacilityReq: Unknown invoke ID.");
        }
    }

    /*
    对于MPTY操作，需要检查操作是否允许，然后改变受影响的实体状态，并启动定时器
    */
    switch (enOperation)
    {
    case NAS_SS_OPERATION_BUILD_MPTY:
    case NAS_SS_OPERATION_HOLD_MPTY:
    case NAS_SS_OPERATION_RETRIEVE_MPTY:
    case NAS_SS_OPERATION_SPLIT_MPTY:
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
        if (NAS_SS_OPERATION_HOLD_MPTY == enOperation)
        {
            ulResult = NAS_CC_CheckSsSwitchHoldAllowed();
        }
        else if (NAS_SS_OPERATION_RETRIEVE_MPTY == enOperation)
        {
            ulResult = NAS_CC_CheckSsSwitchRetrieveAllowed();
        }
        else
        {
            ulResult = VOS_OK;
        }

        if ( (NAS_CC_CheckMptyOperation(entityId, enOperation) == VOS_OK)
          && (VOS_OK == ulResult) )
        {
            NAS_CC_HandleMptyEvent(entityId, NAS_CC_MPTY_EVT_INVOKE, enOperation);

            NAS_CC_SetSsSwitchInvokeId(VOS_TRUE, stFacInfo.ucInvokeID);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_MPTY, stFacInfo.ucInvokeID);
            NAS_CC_StoreSsOperation(entityId, stFacInfo.ucInvokeID, enOperation);
        }
        else
        {
            NAS_CC_SendMnccMsg(entityId,
                               MNCC_FACILITY_LOCAL_REJ,
                               &stFacInfo.ucInvokeID,
                               sizeof(stFacInfo.ucInvokeID));
            return;
        }
        /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */
        break;

    case NAS_SS_OPERATION_EXPLICIT_CT:
    /* 此处目前没有进行CC状态的检查，以后需要补充 */
        NAS_CC_StartTimer(entityId, TI_NAS_CC_ECT, stFacInfo.ucInvokeID);
        NAS_CC_StoreSsOperation(entityId, stFacInfo.ucInvokeID, enOperation);
        break;
    default:
        break;
    }

    /* 填写facility消息头 */
    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_FACILITY, &pstMsg->unParam.stFac.stHeader);

    /* 编码facility消息 */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stFac,
                     f_stCcEncodeBuf.aucBuf,
                     (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

    /* 发送MMCC_DATA_REQ原语将消息发往网络 */
    NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccHoldReq
 功能描述  : 处理MNCC_HOLD_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
  3.日    期   : 2015年08月17日
    作    者   : f00179208
    修改内容   : DTS2015080300502:在电话挂断过程中，保持该路电话，需要明确该场景下的原因值
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccHoldReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState = NAS_CC_GetHoldAuxState(entityId);
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCause;
    VOS_UINT32                          ulResult;

    if ((NAS_CC_CALL_STATE_U10 == enCurrState)
     || (NAS_CC_CALL_STATE_U26 == enCurrState))
    {
        ulResult = NAS_CC_CheckSsSwitchHoldAllowed();

        if ( (NAS_CC_HOLD_AUX_S_IDLE == enHoldState)
          && (VOS_OK == ulResult) )
        {
            NAS_AIR_MSG_HDR_STRU  stHeader;

            /* 填写hold消息头 */
            NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_HOLD, &stHeader);

            /* 编码hold消息 */
            NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stHeader,
                             f_stCcEncodeBuf.aucBuf,
                             (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

            /* 发送MMCC_DATA_REQ原语将消息发往网络 */
            NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_HOLD, 0);

            NAS_CC_INFO_LOG("NAS_CC_ProcMnccHoldReq ChangeHoldAuxState to HOLD_REQ");
            NAS_CC_ChangeHoldAuxState(entityId, NAS_CC_HOLD_AUX_S_HOLD_REQ);

            NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_WAIT_CNF, NAS_CC_CAUSE_NULL);

            return;
        }
        else
        {
            NAS_CC_ERR_LOG1("NAS_CC_ProcMnccHoldReq: bad hold state.", enHoldState);
        }
    }

    NAS_CC_ERR_LOG1("NAS_CC_ProcMnccHoldReq: bad state.", enCurrState);

    /* 在断开过程中收到HOLD请求，则使用一个特定原因值，MNCALL在处理HOLD REJ时，
       如果是该原因值，则不更新错误原因值 */
    if ((NAS_CC_CALL_STATE_U11 == enCurrState)
     || (NAS_CC_CALL_STATE_U12 == enCurrState))
    {
        enCause = NAS_CC_CAUSE_CC_INTER_ERR_HOLD_REJ_IN_DISC_STATE;
    }
    else
    {
        enCause = NAS_CC_CAUSE_111;
    }

    NAS_CC_SendMnccMsg(entityId,
                       MNCC_HOLD_REJ,
                       &enCause,
                       sizeof(enCause));

    return;
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccRetrieveReq
 功能描述  : 处理MNCC_RETRIEVE_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccRetrieveReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState = NAS_CC_GetHoldAuxState(entityId);
    NAS_AIR_MSG_HDR_STRU                stHeader;
    VOS_UINT32                          ulResult;
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCause;

    if ((NAS_CC_CALL_STATE_U10 == enCurrState)
     || (NAS_CC_CALL_STATE_U26 == enCurrState))
    {
        ulResult = NAS_CC_CheckSsSwitchRetrieveAllowed();

        if ( (NAS_CC_HOLD_AUX_S_CALL_HELD == enHoldState)
          && (VOS_OK == ulResult) )
        {
            /* 填写retrieve消息头 */
            NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RETRIEVE, &stHeader);

            /* 编码retrieve消息 */
            NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stHeader,
                             f_stCcEncodeBuf.aucBuf,
                             (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

            /* 发送MMCC_DATA_REQ原语将消息发往网络 */
            NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_HOLD, 0);

            NAS_CC_INFO_LOG("NAS_CC_ProcMnccRetrieveReq ChangeHoldAuxState to RETRIEVE_REQ");
            NAS_CC_ChangeHoldAuxState(entityId, NAS_CC_HOLD_AUX_S_RETRIEVE_REQ);

            NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_WAIT_CNF, NAS_CC_CAUSE_NULL);

            return;
        }
        else
        {
            NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRetrieveReq: bad hold state.", enHoldState);
        }
    }
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

    /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
    NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRetrieveReq: bad state.", enCurrState);
    enCause = NAS_CC_CAUSE_111;
    NAS_CC_SendMnccMsg(entityId,
                       MNCC_RETRIEVE_REJ,
                       &enCause,
                       sizeof(enCause));
    /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

    return;

}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccStartDtmfReq
 功能描述  : 处理MNCC_START_DTMF_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年2月18日
    作    者   : z00161729
    修改内容   : DTS2013021803962:start dtmf rej后如果收到stop dtmf请求无需跟网络交互直接回复stop dtmf
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccStartDtmfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_CAUSE_VALUE_ENUM_U32          cause;
    NAS_CC_DTMF_STATE_ENUM              enDtmfState = NAS_CC_GetDtmfState(entityId);

    /* 是否有DTMF过程正在进行 */
    if ((enDtmfState != NAS_CC_DTMF_S_IDLE)
     && (enDtmfState != NAS_CC_DTMF_S_START_REJ))
    {
        /* 缓存DTMF请求 */
        NAS_CC_QueueDtmfReq(entityId,
                            NAS_CC_DTMF_START_REQ,
                            pstMsg->unParam.stStartDtmf.stKeypadFacility.KeypadInfo);
        return;
    }

    /*
    3GPP 24.008 5.5.7 DTMF protocol control procedure

    The mobile station shall be capable of transmitting DTMF messages if and
    only if the mobile station has the user connection for speech attached and
    an appropriate channel is available.
    */
    if (NAS_CC_IsTchAvailable(NAS_CC_ITC_SPEECH))
    {
        /* 填写start dtmf消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_START_DTMF, &pstMsg->unParam.stStartDtmf.stHeader);

        /* 编码start dtmf消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stStartDtmf,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T336, 0);
        NAS_CC_INFO_LOG("NAS_CC_ProcMnccStartDtmfReq ChangeDtmfState to START_REQ");
        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_START_REQ);
    }
    else
    {
        /* 发送MNCC_START_DTMF_REJ原语 */
        cause = NAS_CC_CAUSE_111;
        NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &cause, sizeof(cause));
        NAS_CC_ERR_LOG("NAS_CC_ProcMnccStartDtmfReq: No appropriate channel.");

    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccStopDtmfReq
 功能描述  : 处理MNCC_STOP_DTMF_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年2月18日
    作    者   : z00161729
    修改内容   : DTS2013021803962:start dtmf rej后如果收到stop dtmf请求无需跟网络交互直接回复stop dtmf cnf
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccStopDtmfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_CAUSE_VALUE_ENUM_U32          cause;
    NAS_CC_DTMF_STATE_ENUM              enDtmfState = NAS_CC_GetDtmfState(entityId);

    if (NAS_CC_DTMF_S_START_REJ == enDtmfState)
    {
        NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
        return;
    }

    /* 是否有DTMF过程正在进行 */
    if (enDtmfState != NAS_CC_DTMF_S_START_REQ)
    {
        if (enDtmfState != NAS_CC_DTMF_S_IDLE)
        {
            /* 缓存DTMF请求 */
            NAS_CC_QueueDtmfReq(entityId,
                                NAS_CC_DTMF_STOP_REQ,
                                0);
            return;
        }

        if (NAS_CC_IsTchAvailable(NAS_CC_ITC_SPEECH))
        {
            NAS_CC_SendStopDtmf(ucTi);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_T337, 0);
            NAS_CC_INFO_LOG("NAS_CC_ProcMnccStopDtmfReq ChangeDtmfState to STOP_REQ");
            NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_STOP_REQ);
        }
        else
        {
            cause = NAS_CC_CAUSE_111;
            NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, &cause, sizeof(cause));
            NAS_CC_ERR_LOG("NAS_CC_ProcMnccStopDtmfReq: No appropriate channel.");
        }
    }
    else
    {
       /* 缓存DTMF请求 */
        NAS_CC_QueueDtmfReq(entityId,
                            NAS_CC_DTMF_STOP_REQ,
                            0);
        return;
    }

}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccModifyReq
 功能描述  : 处理MNCC_MODIFY_REQ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccModifyReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U10 == enCurrState)
    {
        /* 填写modify消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_MODIFY, &pstMsg->unParam.stModify.stHeader);

        /* 编码modify消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stModify,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T323, 0);
        NAS_CC_INFO_LOG("NAS_CC_ProcMnccModifyReq ChangeCallState to U26");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U26);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccModifyReq: bad state.", enCurrState);
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccModifyRes
 功能描述  : 处理MNCC_MODIFY_RES原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccModifyRes(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U27 == enCurrState)
    {
        /* 填写modify complete消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_MODIFY_COMPLETE, &pstMsg->unParam.stModifyRes.stHeader);

        /* 编码modify complete消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stModifyRes,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccModifyRes ChangeCallState to U10");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U10);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccModifyRes: bad state.", enCurrState);
    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccModifyRej
 功能描述  : 处理MNCC_MODIFY_REJ原语
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
              entityId    - 处理该原语的CC实体的ID
              ucTi        - CC实体对应的transaction ID
              enCurrState - CC实体当前的呼叫状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccModifyRej(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U27 == enCurrState)
    {
        /* 填写modify reject消息头 */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_MODIFY_REJ, &pstMsg->unParam.stModifyRej.stHeader);

        /* 编码modify reject消息 */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stModifyRej,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* 发送MMCC_DATA_REQ原语将消息发往网络 */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccModifyRej ChangeCallState to U10");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U10);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccModifyRej: bad state.", enCurrState);
    }
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetEntityId
 功能描述  : 处理MNCC原语时获取CC实体ID和TI
 输入参数  : pstMsg      - 来自上层的MNCC原语消息
 输出参数  : pulEntityId - CC实体标识
             pucTi       - TI值
 返 回 值  : VOS_OK -  成功,创建CC实体失败
             VOS_ERR - 失败,创建CC实体失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月29日
    作    者   : z00161729
    修改内容   : 降NAS_CC_ProcMnccPrimitive圈复杂度新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  3.日    期   : 2013年04月08日
    作    者   : Y00213812
    修改内容   : DTS2013040702274, 解决网络未分配TI时，主动挂断错误的问题
  4.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*****************************************************************************/
VOS_UINT32  NAS_CC_GetEntityId(
    MNCC_REQ_PRIM_MSG_STRU             *pstMsg,
    NAS_CC_ENTITY_ID_T                 *pulEntityId,
    VOS_UINT8                          *pucTi
)
{
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState;
    VOS_BOOL                            bIsCreateEntity;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    /* 对于SETUP和EMERGENCY SETUP请求，需要先建立CC实体 */
    if ((pstMsg->enPrimName != MNCC_SETUP_REQ)
     && (pstMsg->enPrimName != MNCC_EMERG_SETUP_REQ))
    {
        if (MNCC_DISC_REQ == pstMsg->enPrimName)
        {
            *pulEntityId = NAS_CC_GetEntityByCallId(pstMsg->ucCallId);
            *pucTi       = NAS_CC_GetEntityTi(*pulEntityId);
        }
        else
        {
            *pucTi = pstMsg->ucTi;
            *pulEntityId = NAS_CC_GetEntityByTi(*pucTi);
        }
    }
    else
    {
        if ( MNCC_SETUP_REQ == pstMsg->enPrimName )
        {
            enCallType = NAS_CC_CALL_TYPE_MO_NORMAL_CALL;
        }
        else
        {
            enCallType = NAS_CC_CALL_TYPE_EMERGENCY_CALL;
        }

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            bIsCreateEntity = VOS_TRUE;
            *pucTi          = pstMsg->ucTi;
            bIsCreateEntity = NAS_CC_IsNeedCreateEntity(pstMsg->enPrimName, *pucTi, pulEntityId);
            enCurrState     = NAS_CC_CALL_STATE_U0;
            if (VOS_TRUE != bIsCreateEntity)
            {
                enCurrState = NAS_CC_GetCallState(*pulEntityId);
            }

            /* 取得当前呼叫状态, 只有在U0.6状态才不需要createEntity */
            if (NAS_CC_CALL_STATE_U0_6 != enCurrState)
            {
                bIsCreateEntity = VOS_TRUE;
            }

            if (VOS_TRUE == bIsCreateEntity)
            {
                if (NAS_CC_CreateEntity(enCallType, pstMsg->ucCallId, NAS_CC_INVALID_TI_VALUE,
                                        pulEntityId) != VOS_OK)
                {
                    NAS_CC_ERR_LOG("NAS_CC_GetEntityId: Fail to create entity.");
                    return VOS_ERR;
                }

                *pucTi = NAS_CC_GetEntityTi(*pulEntityId);
            }
        }
        else
        {
            if (NAS_CC_CreateEntity(enCallType, pstMsg->ucCallId, NAS_CC_INVALID_TI_VALUE,
                                    pulEntityId) != VOS_OK)
            {
                NAS_CC_ERR_LOG("NAS_CC_GetEntityId: Fail to create entity.");
                return VOS_ERR;
            }

            *pucTi = NAS_CC_GetEntityTi(*pulEntityId);
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    }

    return VOS_OK;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccSrvccCallInfoNtf
 功能描述  : 处理CALL模块的SRVCC同步过来的呼叫信息的通知消息
 输入参数  : pstSrvccCallInfoNtf---SRVCC同步过来的呼叫信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :  2013-9-25
    作    者   :  w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年5月28日
    作    者   : z00234330
    修改内容   : covertity修改
  3.日    期   : 2014年12月23日
    作    者   : b00269685
    修改内容   : ultra flash新增缓存机制

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccSrvccCallInfoNtf(
    MNCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstSrvccCallInfoNtf
)
{
    VOS_UINT8                           aucTi[MNCC_MAX_ENTITY_NUM];
    VOS_UINT8                           ucTiNum;

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    PS_MEM_SET(aucTi, 0x00, sizeof(aucTi));
    /* modified by z00234330 for coverity修改 2014-05-28 begin */

    /* 如果SRVCC带过来的CALL NUM为0也需要通知MM模块 */
    /* 构造CC实体信息 */
    NAS_CC_CreateCcEntityWithCallEntityInfo((VOS_VOID*)pstSrvccCallInfoNtf);

    /* 构造通知MM模块的TI数组信息 */
    NAS_CC_GetEntityTiInfo(&ucTiNum, aucTi);

    /* 通知MM模块MMCC_SRVCC_CALL_INFO_NOTIFY消息 */
    NAS_CC_SendMmccSrvccCallInfoNtf(ucTiNum, aucTi);


    return;
}
#endif

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */

/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccCallStatusNtf
 功能描述  : 处理MNCC_CALL_STATUS_NTY
 输入参数  : MNCC_CALL_STATUS_NTY_STRU           enCallStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_ProcMnccCallStatusNtf(
    MNCC_CALL_STATUS_NTY_STRU          *pstCallStatusNty
)
{
    /* 通知MM模块MMCC_CALL_STATUS_NTY消息 */
    NAS_CC_SendMmccCallStatusNty(pstCallStatusNty->enCallStatus);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_CC_ProcMnccPrimitive
 功能描述  : 处理MNCC原语。该函数将MNCC原语分发到各自的处理函数去处理。
 输入参数  : pMsg - 来自上层的MNCC原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年2月23日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  4.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  5.日    期   : 2013年03月13日
    作    者   : z00214637
    修改内容   : Delete M2
  6.日    期   : 2013年09月25日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseII 项目:增加CALL模块的SRVCC状态通知消息的处理
*****************************************************************************/
VOS_VOID  NAS_CC_ProcMnccPrimitive(VOS_VOID *pMsg)
{
    NAS_CC_ENTITY_ID_T                  ulEntityId;
    VOS_UINT8                           ucTi;
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState;
    MNCC_REQ_PRIM_MSG_STRU             *pstMsg;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    pstMsg = (MNCC_REQ_PRIM_MSG_STRU *)pMsg;

    /*获取CC实体ID*/
    if (VOS_OK != NAS_CC_GetEntityId(pstMsg, &ulEntityId, &ucTi))
    {
        return;
    }

    /* 取得当前呼叫状态 */
    enCurrState = NAS_CC_GetCallState(ulEntityId);
    if ( NAS_CC_CALL_STATE_BUTT == enCurrState )
    {
        NAS_CC_ERR_LOG("NAS_CC_GetCallState: NAS_CC_CALL_STATE_BUTT.");
    }

    NAS_CC_INFO_LOG4("NAS_CC_ProcMnccPrimitive: enPrimName, entityId, ucTi, enCurrState",
                      pstMsg->enPrimName, (VOS_INT32)ulEntityId, ucTi, enCurrState);

    /* 将MNCC原语分发到各处理函数 */
    switch (pstMsg->enPrimName)
    {
        case MNCC_SETUP_REQ:
/*PC回放导出全局变量使用*/
#ifndef __PS_WIN32_RECUR__
            NAS_CC_SndOutsideContextData();
#endif
            NAS_CC_ProcMnccSetupReq(pstMsg, ulEntityId, ucTi, enCurrState);

            break;

        case MNCC_EMERG_SETUP_REQ:
/*PC回放导出全局变量使用*/
#ifndef __PS_WIN32_RECUR__
            NAS_CC_SndOutsideContextData();
#endif
            NAS_CC_ProcMnccEmergSetupReq(pstMsg, ulEntityId, ucTi, enCurrState);

            break;

        case MNCC_SETUP_RES:
            NAS_CC_ProcMnccSetupRsp(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_CALL_CONF_REQ:
            NAS_CC_ProcMnccCallConfReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_ALERT_REQ:
            NAS_CC_ProcMnccAlertReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_DISC_REQ:
            NAS_CC_ProcMnccDiscReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_REL_REQ:
            NAS_CC_ProcMnccRelReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_REJ_REQ:
            NAS_CC_ProcMnccRejReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_FACILITY_REQ:
            NAS_CC_ProcMnccFacilityReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_HOLD_REQ:
            NAS_CC_ProcMnccHoldReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_RETRIEVE_REQ:
            NAS_CC_ProcMnccRetrieveReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_START_DTMF_REQ:
            NAS_CC_ProcMnccStartDtmfReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_STOP_DTMF_REQ:
            NAS_CC_ProcMnccStopDtmfReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_MODIFY_REQ:
            NAS_CC_ProcMnccModifyReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_MODIFY_RES:
            NAS_CC_ProcMnccModifyRes(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_MODIFY_REJ_REQ:
            NAS_CC_ProcMnccModifyRej(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        case MNCC_EST_CNF_REQ:
             if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
             {
                 NAS_CC_ProcMnccCcEstCnfReq(pstMsg, ulEntityId, ucTi, enCurrState);
             }
             break;
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
        case MNCC_SRVCC_CALL_INFO_NOTIFY:
            NAS_CC_ProcMnccSrvccCallInfoNtf((MNCC_SRVCC_CALL_INFO_NOTIFY_STRU *)(&pstMsg->unParam.stSrvccCallInfoNtf));
            break;
#endif
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */

        case MNCC_CALL_STATUS_NTY:
            NAS_CC_ProcMnccCallStatusNtf((MNCC_CALL_STATUS_NTY_STRU *)(&pstMsg->unParam.stCallStatusNtf));
            break;

        default:
            NAS_CC_ERR_LOG1("NAS_CC_ProcMnccPrimitive: Unknown MNCC primitive.",
                        pstMsg->enPrimName);
            break;

    }
}


/*****************************************************************************
 函 数 名  : NAS_CC_ActUus1Info
 功能描述  : 激活UUS1相关信息保存的UUS1信息
 输入参数  : enMsgType   :需激活的消息类型
             pstUuieInfo :激活UUIE的信息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_ActUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
)
{
    VOS_UINT32                          i;

    /* 寻找 缓存中保留的该消息的UUIE信息 */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( enMsgType == f_astUus1MsgBuf[i].enMsgType)
        {
            break;
        }
    }

    /* 如果缓存中已经存在该消息,则直接用UUIE进行替换 */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        PS_MEM_CPY(&(f_astUus1MsgBuf[i].stUuieInfo),
                   pstUuieInfo,
                   sizeof(f_astUus1MsgBuf[i].stUuieInfo));

        return VOS_OK;
    }

    /* 如果缓存中不存在该消息,则查找一个空闲位置存入该消息 */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( VOS_FALSE == f_astUus1MsgBuf[i].stUuieInfo.IsExist )
        {
            break;
        }
    }

    /* 找到空闲位置直接替换 */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        f_astUus1MsgBuf[i].enMsgType = enMsgType;
        PS_MEM_CPY(&(f_astUus1MsgBuf[i].stUuieInfo),
                           pstUuieInfo,
                           sizeof(f_astUus1MsgBuf[i].stUuieInfo));

        return VOS_OK;
    }

    /* 未找到空闲位置,返回出错,实际上不可能走到此处 */
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : NAS_CC_DeactUus1Info
 功能描述  : 去激活UUS1信息
 输入参数  : enMsgType   :需激活的消息类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_DeactUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType
)
{
    VOS_UINT32                          i;

    /* 寻找 缓存中保留的该消息的UUIE信息 */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( enMsgType == f_astUus1MsgBuf[i].enMsgType)
        {
            break;
        }
    }

    /* 如果缓存中已经存在该消息,则直接设置该值不存在返回成功 */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        f_astUus1MsgBuf[i].stUuieInfo.IsExist = VOS_FALSE;
    }

    /* 如果缓存中不存在该消息,则直接返回成功*/
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_CC_GetMsgUus1Info
 功能描述  : 判断该条消息是否激活UUS1信息
 输入参数  : entityId       :处理该原语的CC实体的ID
             enMsgType      :   消息类型
 输出参数  : pstUuieInfo    :   该消息的UUIE内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID  NAS_CC_GetMsgUus1Info(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrMode;
    VOS_UINT32                          i;
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    PS_MEM_SET(pstUuieInfo,0x00,sizeof(NAS_CC_IE_USER_USER_STRU));

    /* 不支持G模下UUS1的隐式激活 */
    enCurrMode = NAS_MML_GetCurrNetRatType();
    if ( NAS_MML_NET_RAT_TYPE_GSM == enCurrMode )
    {
        return;
    }

    /*  获取当前电话类型,语音或数据 */
    NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_CURR, &stBcParams);

    if ( ( NAS_CC_ITC_SPEECH != stBcParams.enItc )
      && ( NAS_CC_ITC_AUXILIARY_SPEECH != stBcParams.enItc ))
    {
        return;
    }

    /* 查找列表中该消息是否激活 */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( ( enMsgType == f_astUus1MsgBuf[i].enMsgType)
          && (VOS_TRUE == f_astUus1MsgBuf[i].stUuieInfo.IsExist))
        {
            break;
        }
    }

    /* 如果该消息已经激活获取UUIE信息 */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        PS_MEM_CPY(pstUuieInfo,
                   &(f_astUus1MsgBuf[i].stUuieInfo),
                   sizeof(f_astUus1MsgBuf[i].stUuieInfo));
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_CC_GetAllUus1Info
 功能描述  : 获取所有激活UUS1信息
 输入参数  : 无
 输出参数  : pulActNum      :已激活UUS1个数
             pstUus1Info    :已激活UUS1相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_GetAllUus1Info(
    VOS_UINT32                          *pulActNum,
    NAS_CC_UUS1_INFO_STRU               *pstUus1Info
)
{
    VOS_UINT32                          i;

    *pulActNum = 0;
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( VOS_TRUE == f_astUus1MsgBuf[i].stUuieInfo.IsExist )
        {
            (*pulActNum)++;
            pstUus1Info->enMsgType = f_astUus1MsgBuf[i].enMsgType;
            PS_MEM_CPY(&(pstUus1Info->stUuieInfo),
                       &(f_astUus1MsgBuf[i].stUuieInfo),
                       sizeof(f_astUus1MsgBuf[i].stUuieInfo));
            pstUus1Info++;
        }
    }

    return;
}


/* Modified by z40661 for DMT工程修改, 2013-2-01, begin */
/*****************************************************************************
 函 数 名  : NAS_CC_InitUus1Info
 功能描述  : 初始化UUS1信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月16日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_InitUus1Info( VOS_VOID )
{
    VOS_UINT32                          i;

    PS_MEM_SET(f_astUus1MsgBuf, 0x00, sizeof(f_astUus1MsgBuf));

    /* 清空UUIE信息 */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        f_astUus1MsgBuf[i].stUuieInfo.IsExist = VOS_FALSE;
    }

    /* 如果缓存中不存在该消息,则直接返回成功*/
    return;
}
/* Modified by z40661 for DMT工程修改, 2013-2-01, end */

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

