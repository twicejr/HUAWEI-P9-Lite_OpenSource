/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvTaf.c
  Description  : 接收TAF消息的处理
  Function List:
      1.  Ss_CheckTafId                  判断TAF ID是否是ACMP指定的TAF ID
      2.  Ss_RcvMnssBeginReq             SS收到MNSS_BEGIN_REQ的处理
      3.  Ss_RcvMnssFacilityReq          SS收到MNSS_FACILITY_REQ的处理
      4.  Ss_RcvMnssEndReq               SS收到MNSS_END_REQ的处理
      5.  Ss_RcvTafMsg                   分发TAF消息
  History:
      1.  张志勇 2004.03.08   新版作成
      2.  丁  庆 2006.11.07   问题单A32D07063
      3.  丁  庆 2006.11.23   问题单A32D07452
*******************************************************************************/

#include "SsInclude.h"
#include "SsExt.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVTAF_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/***********************************************************************
*  MODULE   : Ss_RcvMnssBeginReq
*  FUNCTION : SS收到MNSS_BEGIN_REQ的处理
*  INPUT    : ST_SSP_MSG        *pSspMsg    当前处理的消息
*             VOS_UINT8             ucTafId     消息中的TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
  2.日    期   : 2014年6月24日
    作    者   : w00167002
    修改内容   : DSDS III项目
************************************************************************/

VOS_VOID Ss_RcvMnssBeginReq(
    ST_SSP_MSG                         *pSspMsg
)
{
    VOS_UINT8   ucTi;                                                               /* 定义TI                                   */
    VOS_UINT8   ucCr;                                                               /* 定义CR                                   */

   ucCr = pSspMsg->ucCr;                                                       /* 获取CR                                   */
    if( ucCr <= SS_MO_CR_NUM )
    {
        if( SS_NONE_TI != ( ucTi = Ss_EntityBuildTi( ucCr )))
        {                                                                       /* 选择空闲TI                               */
            Ss_EntityCreat( ucTi, ucCr );                              /* 建立SS实体                               */
            Ss_SaveRegister( pSspMsg, ucTi );                                   /* 缓存REGISTER消息                         */

            /* DSDS需要先资源申请再发est req建链请求 */
            NAS_SS_ChangeSsState(ucTi, SS_S_CONNECT_PEND);

            Ss_SndMmssEstReq( ucTi, pSspMsg->ucRedialFlg);                                           /* 发送MMSS_EST_REQ原语                     */

            SS_NORM_LOG("\n SS state: SS_S_NULL ==> SS_S_CONNECT_PEND \r" );
        }
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvMnssFacilityReq
*  FUNCTION : SS收到MNSS_FACILITY_REQ的处理
*  INPUT    : ST_SSP_MSG        *pSspMsg    当前处理的消息
*             VOS_UINT8             ucTafId     消息中的TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_VOID Ss_RcvMnssFacilityReq( ST_SSP_MSG *pSspMsg )
{
    VOS_UINT8   ucTi;                                                               /* 定义TI                                   */

    if( SS_NONE_TI != ( ucTi = Ss_EntitySelectTi( pSspMsg->ucCr )))
    {                                                                           /* 根据CR和TAF ID找TI                       */
        Ss_SndFacility( pSspMsg, ucTi );                                        /* 发送DR(FACILITY)原语                     */
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvMnssEndReq
*  FUNCTION : SS收到MNSS_FACILITY_REQ的处理
*  INPUT    : ST_SSP_MSG        *pSspMsg    当前处理的消息
*             VOS_UINT8             ucTafId     消息中的TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
*     2.  丁  庆 06-11-23  问题单A32D07452

      3.日    期   : 2014年5月26日
        作    者   : z00234330
        修改内容   : dts2014050800110,app发送cancel cusd时,如果mm连接没有建立,需要给上层发送abort通知
************************************************************************/
VOS_VOID Ss_RcvMnssEndReq( ST_SSP_MSG *pSspMsg )
{
    VOS_UINT8   i;
    VOS_UINT8   ucTi = SS_NONE_TI;                                                            /* 定义TI                                   */

    for( i = 0 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {
        if( pSspMsg->ucCr == g_SsEntity[i].ucCr )
        {
            ucTi = i;
            break;
        }
    }

    if( SS_NONE_TI != ucTi)
    {
        if (SS_S_CONNECTED == g_SsEntity[ucTi].ucState)
        {
            Ss_SndRelCmpl( pSspMsg, ucTi, 0 );                                  /* 发送DR(RELCMPL)原语                      */
        }

        if ( ( VOS_TRUE == pSspMsg->SspmsgCore.u.EndReq.OP_SspTaCause )
          && ( EN_STC_NORMAL == pSspMsg->SspmsgCore.u.EndReq.enSspTaCause )
          && (SS_S_CONNECT_PEND == g_SsEntity[ucTi].ucState))
        {
            Ss_SndMmssAbortReq(ucTi);
        }
        else
        {
            Ss_SndMmssRelReq( ucTi );                                               /* 释放对应的MM连接                         */
        }
        Ss_EntityClear( ucTi );                                                 /* 释放对应的Ss实体                         */
    }
}


/*****************************************************************************
 函 数 名  : Ss_RcvMnssSsStatusNty
 功能描述  : 新生成函数
 输入参数  : ST_SSP_MSG                         *pSspMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ss_RcvMnssSsStatusNty(
    ST_SSP_MSG                         *pSspMsg
)
{
    Ss_SndMmssSsStatusNty(pSspMsg->SspmsgCore.u.stSsStatusNty.enSsStatus);
    return;
}

/***********************************************************************
*  MODULE   : Ss_RcvTafMsg
*  FUNCTION : 分发TAF消息
*  INPUT    : VOS_VOID      *pMsg   当前处理的消息
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_VOID Ss_RcvSsaMsg(
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                      *pstSsMsg;                                   /* CCP消息结构                              */

    pstSsMsg = (ST_SSP_MSG*)pMsg;                               /* 获取ASN解码后SSP消息                     */

    switch( pstSsMsg->SspmsgCore.ucChoice )
        {                                                                       /* 根据消息名分发                           */
        case MNSS_BEGIN_REQ:                                                    /* MNSS_BEGIN_REQ                           */
            Ss_RcvMnssBeginReq( pstSsMsg);                             /* 调用 MNSS_BEGIN_REQ 消息处理             */
            break;
        case MNSS_FACILITY_REQ:                                                 /* MNSS_FACILITY_REQ                        */
            Ss_RcvMnssFacilityReq( pstSsMsg );                          /* 调用 MNSS_FACILITY_REQ 消息处理          */
            break;
        case MNSS_END_REQ:                                                      /* MNSS_END_REQ                             */
            Ss_RcvMnssEndReq( pstSsMsg );                               /* 调用 MNSS_END_REQ 消息处理               */
            break;

        case MNSS_SS_STATUS_NTY:                                                      /* MNSS_SS_STATUS_NTY                             */
            Ss_RcvMnssSsStatusNty( pstSsMsg );                               /* 调用 MNSS_SS_STATUS_NTY 消息处理               */
            break;

        default:                                                                /* 其他TAF消息                              */
            SS_WARN_LOG( "\n [Error]APP->SS MsgType Error!\r" );
            break;
        }

}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

