/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvMm.c
  Description  : 接收MM消息的处理
  Function List:
      1.  Ss_CheckAirMsg               空口消息检查
      2.  Ss_RcvMmssEstCnf             接收MMSS_EST_CNF的处理
      3.  Ss_RcvMmssEstInd             接收MMSS_EST_IND的处理
      4.  Ss_RcvMmssDataInd            接收MMSS_DATA_IND的处理
      5.  Ss_RcvMmssRelInd             接收MMSS_REL_IND的处理
      6.  Ss_RcvMmMsg                  分发MM消息
  History:
      1.  张志勇 2004.03.08   新版作成
*******************************************************************************/

#include "SsInclude.h"
#include "NasOmInterface.h"
#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVMM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_SS_ReportN2MOtaMsg
 功能描述  : 勾取SS空口消息发给OM
 输入参数  : pNasMsg   - SS空口消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SS_ReportN2MOtaMsg(
    SS_MSG_STRU                        *pNasMsg
)
{

    NAS_OTA_MSG_ID_ENUM_UINT16          enNasOtaMsyId;
    VOS_UINT8                           ucMsgType;

    enNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    /* Message Type字段在消息中的所在位置 */
    ucMsgType = pNasMsg->aucSsMsg[1];

    SS_NORM_LOG1("NAS_SS_ReportN2MOtaMsg: [Msgtype] ", pNasMsg->aucSsMsg[1]);

    /* 把NAS下行空口消息ID和上报给OM的消息ID对应，并通过OM进行勾取显示 */
    switch(ucMsgType)
    {
        case SS_MSG_REGISTER:
            enNasOtaMsyId = NAS_OTA_MSG_SS_REGISTER_DOWN;
            break;
        case SS_MSG_FACILITY:
            enNasOtaMsyId = NAS_OTA_MSG_SS_FACILITY_DOWN;
            break;
        case SS_MSG_RELCMPL:
            enNasOtaMsyId = NAS_OTA_MSG_SS_RELCMPL_DOWN;
            break;
        default:
            break;
    }

    if (NAS_OTA_MSG_ID_BUTT == enNasOtaMsyId)
    {
          SS_WARN_LOG1("NAS_SS_ReportN2MOtaMsg: invalid msg type!", enNasOtaMsyId);
          /* 不属于SS模块的空口消息，不在trace中显示 */
          return;
    }

    /*上报空口消息给OM*/
    NAS_SendAirMsgToOM(WUEPS_PID_SS,
                       enNasOtaMsyId,
                       NAS_OTA_DIRECTION_DOWN,
                       pNasMsg->ulSsMsgSize + 4,
                       (VOS_UINT8 *)pNasMsg);

    return;
}

/***********************************************************************
*  MODULE   : Ss_CheckAirMsg
*  FUNCTION : 空口消息检查
*  INPUT    : VOS_VOID      *pMsg       当前处理的消息
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8     ucResult    WUEPS_TRUE:  检查通过
*                                   WUEPS_FALSE: 检查未通过
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_UINT8 Ss_CheckAirMsg(
                     VOS_VOID *pMsg
                     )
{
    VOS_UINT8                   ucResult;                                           /* 定义消息检查是否成功标志                 */
    MMSS_DATA_IND_STRU      *pDataInd;                                          /* 定义指向MMSS_DATA_IND类型的消息          */

    ucResult = WUEPS_TRUE;                                                      /* 初始化为成功                             */
    pDataInd = (MMSS_DATA_IND_STRU*)pMsg;                                       /* 获取MMSS_DATA_IND_STRU消息指针           */
    if( pDataInd->SsMsg.ulSsMsgSize < 2 )
    {                                                                           /* 消息过短                                 */
        ucResult = WUEPS_FALSE;                                                 /* 返回检查失败                             */
    }
    else if(( SS_MSG_REGISTER == pDataInd->SsMsg.aucSsMsg[1] )
        && ( pDataInd->ulTi > SS_MT_ENTITY_NUM ))
    {                                                                           /* REGISTER的TI FLAG为1                     */
        ucResult = WUEPS_FALSE;                                                 /* 返回检查失败                             */
    }
    else
    {
    }
    return ucResult;
}

/***********************************************************************
*  MODULE   : Ss_RcvMmssEstCnf
*  FUNCTION : 接收MMSS_EST_CNF的处理
*  INPUT    : VOS_VOID      *pMsg   当前处理的消息
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇   04-03-08  新版作成
*     2.  张志勇   05-01-08  新增对缓存的REGISTER消息的处理
      3.日    期   :2013年9月10日
        作    者   :z00161729
        修改内容  :DTS2013082903019:支持ss重发功能
      4.日    期   : 2014年6月24日
        作    者   : w00167002
        修改内容   : DSDS III项目
************************************************************************/

VOS_VOID Ss_RcvMmssEstCnf(
                      VOS_VOID *pMsg
                      )
{
    MMSS_EST_CNF_STRU   *pEstCnf;                                               /* 定义指向MMSS_EST_CNF消息的指针           */
    VOS_UINT8                  ucTi;                                                /* 用于获取TI                               */
    ST_SSP_MSG           stSsMsg;

    pEstCnf = (MMSS_EST_CNF_STRU *)pMsg;                                        /* 获取指向MMSS_EST_CNF消息的指针           */
    ucTi = ( VOS_UINT8 )( pEstCnf->ulTi );                                          /* 取得TI                                   */

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI不应为“111”                            */
        if( SS_S_CONNECT_PEND == g_SsEntity[ucTi].ucState )
        {                                                                       /* 判断是否是建立中                         */
            if( MMSS_EST_SUCCESS == pEstCnf->ulResult )
            {                                                                   /* 判断建立是否成功                         */
                Ss_SndRegister( ucTi );                                         /* 发送DR(REGISTER)原语                     */

                NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

                stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;

                if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
                {
                    stSsMsg.ucCr -= 120;                                        /*Cr范围为128-134时，需要转换成TI:8-14*/
                }

                stSsMsg.SspmsgCore.ucChoice = SSA_SS_CS_CONN_IND;

                PS_MEM_SET(&(stSsMsg.SspmsgCore.u.stCsConnInd), 0, sizeof(SSA_SS_CS_CONN_IND_STRU));
                stSsMsg.SspmsgCore.u.stCsConnInd.enConnState = SSA_SS_CS_CONN_STATE_PRESENT;
                SSA_DealMsgFromSS(&stSsMsg);

                SS_NORM_LOG(
                    "\n SS state: SS_S_CONNECT_PEND ==> SS_S_CONNECTED \r" );
            }

            /* mm不会回复est cnf结果为失败，该场景mm统一通过mmss rel ind消息回复 */
        }
    }
}

/*****************************************************************************
 函 数 名  : LCS_RcvMmlcsMsg
 功能描述  : 处理MM发送给LCS的消息
 输入参数  : VOS_UINT8         ucTi
             VOS_VOID         *pAirMsg  --空口消息数据首地址
 输出参数  : 无
 返 回 值  : VOS_OK  消息处理成功
             VOS_ERR 非LCS消息，未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : l00198894
    修改内容   : DTS2012121903140: LCS功能不支持，回复RELEASE COMPLETE

*****************************************************************************/
VOS_UINT32 LCS_RcvMmlcsMsg(
    VOS_UINT8                           ucTi,
    VOS_VOID                           *pAirMsg
)
{
    VOS_UINT8                          *pucRcvMsg;
    ST_SSP_IES_CAUSE                    stCause;
    VOS_UINT8                          *pucDestMsg;
    VOS_UINT8                           ucMsgTi;
    VOS_UINT32                          ulCodeLen;          /* 编码后长度 */

    pucRcvMsg       = (VOS_UINT8 *)pAirMsg;
    ulCodeLen       = 0;
    ucMsgTi         = GET_MSG_TI(ucTi);
    PS_MEM_SET(&stCause, 0, sizeof(stCause));

    /* 判断如果非LCS消息，返回VOS_ERR */
    if (LCS_MM_IE_PD_LOCATION_SRVC != (pucRcvMsg[0] & 0x0f))
    {
        return VOS_ERR;
    }

    /* 非REGISTER消息，不作处理，直接返回VOS_OK */
    if (LCS_MSG_REGISTER != pucRcvMsg[1])
    {
        return VOS_OK;
    }

    /* 根据运营商要求，当UE不支持LCS功能时，需要回复RELCOMP(#69) */
    /* 填写Cause域 */
    stCause.ulCnt       = 2;

    /* 填写coding standard */
    stCause.Cause[0]    = LCS_CAUSE_CODING_STANDARD_GSM;

    /* 填写原因值(#69) */
    stCause.Cause[1]    = LCS_CAUSE_FACILITY_NOT_IMPLEMENTED;

    /* 申请RELCOMPLETE消息内存空间 */
    pucDestMsg = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_SS, SS_MAX_MSG_LEN);
    if ( VOS_NULL_PTR == pucDestMsg)
    {
        return VOS_ERR;
    }
    PS_MEM_SET(pucDestMsg, 0, SS_MAX_MSG_LEN);

    /* 设置PD及TI字节 */
    *(pucDestMsg + ulCodeLen) = (VOS_UINT8)(NAS_PD_LS | ( ucMsgTi << 4 ));

    /* 更新编码后的长度 */
    ulCodeLen++;

    /* 设置消息类型 */
    *(pucDestMsg + ulCodeLen) = LCS_MSG_RELCMPL;

    /* 更新编码后的长度 */
    ulCodeLen++;

    /* 设置指定IE存在标志 */
    *(pucDestMsg + ulCodeLen) = LCS_IEICAUSE;

    /* 更新编码后的长度 */
    ulCodeLen++;

    /* 填写CAUSE长度 */
    *(pucDestMsg + ulCodeLen) = (VOS_UINT8)stCause.ulCnt;

    /* 更新编码后的长度 */
    ulCodeLen++;

    /* 填写CAUSE值 */
    PS_MEM_CPY(pucDestMsg + ulCodeLen, stCause.Cause, stCause.ulCnt);

    /* 更新编码后的长度 */
    ulCodeLen += stCause.ulCnt;

    /* 发送MMSS_DATA_REQ */
    Ss_SndMmssDataReq(ucTi, pucDestMsg, ulCodeLen);

    /* 释放该消息 */
    PS_MEM_FREE(WUEPS_PID_SS, pucDestMsg);

    return VOS_OK;
}

/***********************************************************************
*  MODULE   : Ss_RcvMmssEstInd
*  FUNCTION : 接收MMSS_EST_IND的处理
*  INPUT    : VOS_VOID      *pMsg   当前处理的消息
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成

      2.日    期   : 2012年12月19日
        作    者   : l00198894
        修改内容   : DTS2012121903140: LCS功能不支持，回复RELEASE COMPLETE
        
      3.日    期   : 2012年12月29日
        作    者   : l00198894
        修改内容   : DTS2012122702627: 增加SS空口消息可维可测
      4.日    期   : 2013年8月29日
        作    者   : f62575
        修改内容   : VSIM FEATURE
      5.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容   :DTS2013082903019:支持ss重发功能
      6.日    期   : 2014年6月24日
        作    者   : w00167002
        修改内容   : DSDS III项目
************************************************************************/

VOS_VOID Ss_RcvMmssEstInd(
                      VOS_VOID *pMsg
                      )
{
    MMSS_EST_IND_STRU      *pEstInd;                                            /* 定义指向MMSS_EST_IND消息的指针           */
    VOS_UINT8                  *pAirMsg;                                            /* 定义指向空口消息的指针                   */
    VOS_UINT32                  ulMsgSize;                                           /* 定义空口消息长度                         */
    VOS_UINT8                  ucTi;                                                /* 用于获取TI                               */
    VOS_UINT8                  ucCr;                                                /* 用于获取CR                               */

    ST_SSP_MSG                          stSsMsg;

    pEstInd = ( MMSS_EST_IND_STRU *)pMsg;                                       /* 获取MMSS_EST_IND消息指针                 */
    pAirMsg = pEstInd->SsMsg.aucSsMsg;                                          /* 取得空口消息                             */
    ulMsgSize = pEstInd->SsMsg.ulSsMsgSize;                                     /* 取得空口消息得长度                       */
    ucTi = ( VOS_UINT8 )( pEstInd->ulTi );                                          /* 取得TI                                   */

    if (VOS_OK == LCS_RcvMmlcsMsg(ucTi, pAirMsg))
    {
        Ss_SndMmssRelReq(ucTi);                                                 /* 向MM发送MMSS_REL_REQ原语，释放MM连接     */
        return;
    }

    /* VSIM的MODEM且NAS的VSIM特性开关打开，则拒绝网络发起的SS业务 */
    if (VOS_TRUE == NAS_VSIM_IsRequireVsimCtrl())
    {
        Ss_SndMmssRelReq(ucTi);                                                 
        return;
    }

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI不应为“111” */
        if( WUEPS_TRUE == Ss_CheckAirMsg( pMsg ))
        {                                                                       /* 通过了空口消息检查                       */
            /* 通过OM勾取SS空口消息 */
            NAS_SS_ReportN2MOtaMsg(&pEstInd->SsMsg);

            switch( pAirMsg[1] )
            {                                                                   /* 按空口消息类型分发                       */
            case SS_MSG_REGISTER:                                               /* REGISTER                                 */
                if( SS_NONE_CR != ( ucCr = Ss_EntityBuildCr( ucTi )))
                {                                                               /* 新建一个CR                               */
                        Ss_EntityCreat( ucTi, ucCr);                                    /* 建立TI对应的SS实体                       */
                    Ss_RcvRegister( pAirMsg, ulMsgSize, ucTi );                 /* 调用对REGISTER消息的处理                 */
                }


                NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

                stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;

                if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
                {
                    stSsMsg.ucCr -= 120;                                        /*Cr范围为128-134时，需要转换成TI:8-14*/
                }

                stSsMsg.SspmsgCore.ucChoice = SSA_SS_CS_CONN_IND;

                PS_MEM_SET(&(stSsMsg.SspmsgCore.u.stCsConnInd), 0, sizeof(SSA_SS_CS_CONN_IND_STRU));
                stSsMsg.SspmsgCore.u.stCsConnInd.enConnState = SSA_SS_CS_CONN_STATE_PRESENT;
                SSA_DealMsgFromSS(&stSsMsg);

                break;
            default:                                                            /* 其他空口消息                             */
                Ss_RcvUnknownAirMsg( ucTi );                                    /* 调用对不可识别的空口消息的处理           */
                break;
            }
        }
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvMmssDataInd
*  FUNCTION : 接收MMSS_DATA_IND的处理
*  INPUT    : VOS_VOID      *pMsg   当前处理的消息
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成

      2.日    期   : 2012年12月19日
        作    者   : l00198894
        修改内容   : DTS2012121903140: LCS功能不支持，回复RELEASE COMPLETE
        
      3.日    期   : 2012年12月29日
        作    者   : l00198894
        修改内容   : DTS2012122702627: 增加SS空口消息可维可测
      4.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容  :DTS2013082903019:支持ss重发功能
      5.日    期   : 2014年6月24日
        作    者   : w00167002
        修改内容   : DSDS III项目
************************************************************************/

VOS_VOID Ss_RcvMmssDataInd(
                       VOS_VOID *pMsg
                       )
{
    MMSS_DATA_IND_STRU      *pDataInd;                                          /* 定义指向MMSS_DATA_IND消息的指针          */
    VOS_UINT8                  *pAirMsg;                                            /* 定义指向空口消息的指针                   */
    VOS_UINT32                  ulMsgSize;                                           /* 定义空口消息长度                         */
    VOS_UINT8                  ucTi;                                                /* 用于获取TI                               */

    ST_SSP_MSG                          stSsMsg;

    pDataInd = ( MMSS_DATA_IND_STRU *)pMsg;                                     /* 获取MMSS_DATA_IND消息指针                */
    pAirMsg = pDataInd->SsMsg.aucSsMsg;                                         /* 取得空口消息                             */
    ulMsgSize = pDataInd->SsMsg.ulSsMsgSize;                                    /* 取得空口消息得长度                       */
    ucTi = ( VOS_UINT8 )( pDataInd->ulTi );                                         /* 取得TI                                   */

    if (VOS_OK == LCS_RcvMmlcsMsg(ucTi, pAirMsg))
    {
        return;
    }

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI不应为“111” */
        if( WUEPS_TRUE == Ss_CheckAirMsg( pMsg ))
        {                                                                       /* 通过了空口消息检查                       */
            /* 通过OM勾取SS空口消息 */
            NAS_SS_ReportN2MOtaMsg(&pDataInd->SsMsg);


            NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

            stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;

            if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsMsg.ucCr -= 120;                                        /*Cr范围为128-134时，需要转换成TI:8-14*/
            }

            stSsMsg.SspmsgCore.ucChoice = SSA_SS_CS_CONN_IND;

            PS_MEM_SET(&(stSsMsg.SspmsgCore.u.stCsConnInd), 0, sizeof(SSA_SS_CS_CONN_IND_STRU));
            stSsMsg.SspmsgCore.u.stCsConnInd.enConnState = SSA_SS_CS_CONN_STATE_PRESENT;
            SSA_DealMsgFromSS(&stSsMsg);

            switch(pAirMsg[1])
            {                                                                   /* 按空口消息类型分发                       */
            case SS_MSG_FACILITY:                                               /* FACILITY                                 */
                Ss_RcvFacility( pAirMsg, ulMsgSize, ucTi );                     /* 调用对FACILITY消息的处理                 */
                break;
            case SS_MSG_RELCMPL:                                                /* RELCMPL                                  */
                Ss_RcvRelCmpl( pAirMsg, ulMsgSize, ucTi );                      /* 调用对RELCMPL消息的处理                  */
                break;
            case SS_MSG_REGISTER:                                               /* REGISTER，将其丢弃                       */
                break;
            default:                                                            /* 其他空口消息                             */
                Ss_RcvUnknownAirMsg( ucTi );                                    /* 调用对不可识别的空口消息的处理           */
                break;
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_SS_ConvertMmssRelCauseToSsassCause
 功能描述  : 将NAS_MMSS_REL_CAUSE_ENUM_UINT32转换为SSA_SS_REL_CAUSE_ENUM_UINT32中对应原因值
 输入参数  : enMmssRelCause - mmss之间rel cause值
 输出参数  : penSsCause     - ssass之间cause值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :2013年9月23日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  2.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID TAF_SS_ConvertMmssRelCauseToSsassCause(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmssRelCause,
    SSA_SS_REL_CAUSE_ENUM_UINT32       *penSsCause
)
{
    /* 目前mmss rel cause 与ss ssa rel cause偏移量相同，直接赋值
       后续mmss rel cause新增原因值需要同时在ss ssa rel cause增加 */
       
    *penSsCause = enMmssRelCause;

    return;
}


/***********************************************************************
*  MODULE   : Ss_RcvMmssRelInd
*  FUNCTION : 接收MMSS_REL_IND的处理
*  INPUT    : VOS_VOID      *pMsg   当前处理的消息
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
      2.日    期   :2013年9月14日
        作    者   :z00161729
        修改内容  :DTS2013082903019:支持ss重发功能
      3.日    期   : 2014年6月24日
        作    者   : z00161729
        修改内容   : DSDS III新增
      4.日    期   : 2014年9月23日
        作    者   : b00269685
        修改内容   : DTS2014092207910修改
************************************************************************/

VOS_VOID Ss_RcvMmssRelInd(
                      VOS_VOID *pMsg
                      )
{
    MMSS_REL_IND_STRU       *pRelInd;                                           /* 定义指向MMSS_REL_IND消息的指针           */
    VOS_UINT8                   ucTi;                                               /* 用于获取TI                               */
    ST_SSP_MSG               stSsMsg;

    SSA_SS_REL_CAUSE_ENUM_UINT32        enSsCause;

    pRelInd = ( MMSS_REL_IND_STRU *)pMsg;                                       /* 获取MMSS_REL_IND消息指针                 */
    ucTi = ( VOS_UINT8 )( pRelInd->ulTi );                                          /* 取得TI                                   */

    TAF_SS_ConvertMmssRelCauseToSsassCause(pRelInd->enMmssRelCause, &enSsCause);

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI不应为“111” */
        if ( SS_S_CONNECTED == g_SsEntity[ucTi].ucState )
        {                                                                       /* 判断是否存在连接                         */
            stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                   /* 设置CR                                   */
            if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsMsg.ucCr -= 120;                                            /*Cr范围为128-134时，需要转换成TI:8-14*/
            }
            stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                            /* 设置消息选择                             */

            Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));    /* 将消息空间清零                           */

            Ss_EntityClear( ucTi );
            SSA_DealMsgFromSS(&stSsMsg);
/* 释放对应的Ss实体                         */
        }
        else if (SS_S_CONNECT_PEND == g_SsEntity[ucTi].ucState)
        {
            stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                   /* 设置CR                                   */
            if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsMsg.ucCr -= 120;                                            /*Cr范围为128-134时，需要转换成TI:8-14*/
            }
            stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                            /* 设置消息选择                             */

            Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));    /* 将消息空间清零                           */

            stSsMsg.SspmsgCore.u.EndInd.OP_Cause = 1;
            stSsMsg.SspmsgCore.u.EndInd.Cause.ulCnt = 2;

            stSsMsg.SspmsgCore.u.EndInd.Cause.Cause[0] = 0x60;
            stSsMsg.SspmsgCore.u.EndInd.Cause.Cause[1] = SS_CAUSE_NORMAL_UNSPECIFIED;
            stSsMsg.SspmsgCore.u.EndInd.enSsaSsRelCause = enSsCause;

            SSA_DealMsgFromSS(&stSsMsg);
            Ss_EntityClear( ucTi );

            Ss_DeleteRegister(ucTi);
        }
        else
        {

        }
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvMmMsg
*  FUNCTION : 分发MM消息
*  INPUT    : VOS_VOID      *pMsg   当前处理的消息
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_VOID Ss_RcvMmMsg(
                 VOS_VOID *pMsg
                 )
{
    MSG_HEADER_STRU*        pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU *)pMsg;                                       /* 得到消息头                               */

    switch( pMsgHeader->ulMsgName )
    {                                                                           /* 对消息类型进行分发                       */
    case MMSS_EST_CNF:                                                          /* MMSS_EST_CNF                             */
        Ss_RcvMmssEstCnf(pMsg);                                                 /* 调用 MMSS_EST_CNF 消息处理函数           */
        break;
    case MMSS_EST_IND:                                                          /* MMSS_EST_IND                             */
        Ss_RcvMmssEstInd(pMsg);                                                 /* 调用 MMSS_EST_IND 消息处理函数           */
        break;
    case MMSS_DATA_IND:                                                         /* MMSS_DATA_IND                            */
        Ss_RcvMmssDataInd(pMsg);                                                /* 调用 MMSS_DATA_IND 消息处理函数          */
        break;
    case MMSS_REL_IND:                                                          /* MMSS_REL_IND                             */
        Ss_RcvMmssRelInd(pMsg);                                                 /* 调用 MMSS_REL_IND 消息处理函数           */
        break;
    default:                                                                    /* 其他MM消息                               */
        SS_WARN_LOG( "\n [Error]MM->SS MsgName Error! \r" );
        break;
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

