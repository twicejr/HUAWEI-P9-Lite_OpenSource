/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvAir.c
  Description  : 接收空口消息的处理
  Function List:
      1.  Ss_RcvRegister            收到网侧来的REGISTER消息的处理
      2.  Ss_RcvFacility            收到网侧来的FACILITY消息的处理
      3.  Ss_RcvRelCmpl             收到网侧来的RELEASE COMPLETE消息的处理
      4.  Ss_RcvUnknownAirMsg       收到网侧来的不可识别的空口消息的处理
  History:
      1.  张志勇 2004.03.08   新版作成
      2.  丁  庆 2006.11.07   问题单A32D07063
      3.  丁  庆 2006.12.26   问题单A32D07990
      4.  丁  庆 2007.08.07   问题单A32D12052
*******************************************************************************/

#include "SsInclude.h"
#include "Taf_Tafm_Local.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVAIR_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/***********************************************************************
*  MODULE   : Ss_RcvRegister
*  FUNCTION : 收到网侧来的REGISTER消息的处理
*  INPUT    : VOS_VOID      *pMsg       接收到空口消息的指针
*             VOS_UINT32     ulMsgLen    消息的长度
*             VOS_UINT8     ucTi        对应的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
*     2.  丁  庆 06-12-26  问题单A32D07990

  3.日    期   : 2014年6月24日
    作    者   : w00167002
    修改内容   : DSDS III项目
************************************************************************/

VOS_VOID Ss_RcvRegister(
                    VOS_VOID *pMsg,
                    VOS_UINT32 ulMsgLen,
                    VOS_UINT8 ucTi
                    )
{
    ST_SSP_MSG          stSsmsg;                                                    /* SS解码生成的消息                         */

    switch( g_SsEntity[ucTi].ucState )
    {                                                                           /* 根据实体状态分别进行处理                 */
    case SS_S_NULL:                                                             /* S0                                       */
        Ss_MemSet( &stSsmsg, 0, sizeof( ST_SSP_MSG ));    /* 将消息空间清零                           */
        if( WUEPS_TRUE == Ss_Decode( pMsg, &(stSsmsg.SspmsgCore), ulMsgLen ))
        {                                                                       /* 解码成功                                 */
            stSsmsg.ucCr = g_SsEntity[ucTi].ucCr;                               /* 设置CR                                   */
            if (stSsmsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsmsg.ucCr -= 120;                                            /*Cr范围为128-134时，需要转换成TI:8-14*/
            }

            NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

            SS_NORM_LOG("\n SS state: SS_S_NULL ==> SS_S_CONNECTED \r" );

            SSA_DealMsgFromSS(&stSsmsg);
        }
    break;

    case SS_S_CONNECT_PEND:                                                     /* S1                                       */
    case SS_S_CONNECTED:                                                        /* S2                                       */
        break;

    default:                                                                    /* 其他状态                                 */
        SS_WARN_LOG( "\n [Error]SsEntity State Error! \r" );
        break;
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvFacility
*  FUNCTION : 收到网侧来的FACILITY消息的处理
*  INPUT    : VOS_VOID      *pMsg       接收到空口消息的指针
*             VOS_UINT32     ulMsgLen    消息的长度
*             VOS_UINT8     ucTi        对应的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_VOID Ss_RcvFacility(
                    VOS_VOID *pMsg,
                    VOS_UINT32 ulMsgLen,
                    VOS_UINT8 ucTi
                    )
{
    ST_SSP_MSG      stSsmsg;                                                        /* SS解码生成的消息                         */


    switch( g_SsEntity[ucTi].ucState )
    {                                                                           /* 根据实体状态分别进行处理                 */
    case SS_S_CONNECTED:                                                        /* S2                                       */
        Ss_MemSet( &stSsmsg, 0, sizeof( ST_SSP_MSG ));    /* 将消息空间清零                           */
        if( WUEPS_TRUE == Ss_Decode( pMsg, &(stSsmsg.SspmsgCore), ulMsgLen ))
        {                                                                       /* 解码成功                                 */
            stSsmsg.ucCr = g_SsEntity[ucTi].ucCr;                               /* 设置CR                                   */
            if (stSsmsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsmsg.ucCr -= 120;                                            /*Cr范围为128-134时，需要转换成TI:8-14*/
            }
            SSA_DealMsgFromSS(&stSsmsg);
        }
        break;

    default:                                                                    /* 其他状态                                 */
        SS_WARN_LOG( "\n [Error]SsEntity State Error! \r" );
        break;
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvRelCmpl
*  FUNCTION : 收到网侧来的RELEASE COMPLETE消息的处理
*  INPUT    : VOS_VOID      *pMsg       接收到空口消息的指针
*             VOS_UINT32     ulMsgLen    消息的长度
*             VOS_UINT8     ucTi        对应的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
*     2.  丁  庆 07-08-07  问题单A32D12052
      3.日    期   : 2014年6月24日
         作    者   : z00161729
         修改内容   : DSDS III新增
      4.日    期   : 2014年9月23日
        作    者   : b00269685
        修改内容   : 先clear，否则需要重发的话会TI不可用

************************************************************************/

VOS_VOID Ss_RcvRelCmpl(
                   VOS_VOID *pMsg,
                   VOS_UINT32 ulMsgLen,
                   VOS_UINT8 ucTi
                   )
{
    ST_SSP_MSG      stSsmsg;                                                         /* SS解码生成的消息                         */


    switch( g_SsEntity[ucTi].ucState )
    {                                                                           /* 根据实体状态分别进行处理                 */
    case SS_S_CONNECTED:                                                        /* S2                                       */
        Ss_MemSet( &stSsmsg, 0, sizeof( ST_SSP_MSG ));    /* 将消息空间清零                           */
        if( WUEPS_TRUE == Ss_Decode( pMsg, &(stSsmsg.SspmsgCore), ulMsgLen ))
        {                                                                       /* 解码成功                                 */
            stSsmsg.ucCr = g_SsEntity[ucTi].ucCr;                               /* 设置CR                                   */
            if (stSsmsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsmsg.ucCr -= 120;                                            /*Cr范围为128-134时，需要转换成TI:8-14*/
            }
            Ss_SndMmssRelReq( ucTi );                                           /* 向MM发送MMSS_REL_REQ原语，释放MM连接     */

            Ss_EntityClear( ucTi );
            SSA_DealMsgFromSS(&stSsmsg);
        }
        break;
    default:                                                                    /* 其他状态                                 */
        SS_WARN_LOG( "\n [Error]SsEntity State Error! \r" );
        break;
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvUnknownAirMsg
*  FUNCTION : 收到网侧来的不可识别的空口消息的处理
*  INPUT    : VOS_UINT8     ucTi        对应的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_VOID Ss_RcvUnknownAirMsg(
                         VOS_UINT8 ucTi
                         )
{
    ST_SSP_MSG      stSsMsg;

    Ss_MemSet( &stSsMsg, 0, sizeof( ST_SSP_MSG ));    /* 将消息空间清零                           */

    if( SS_S_NULL != g_SsEntity[ucTi].ucState )
    {
        stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                       /* 设置CR                                   */
        if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
        {
            stSsMsg.ucCr -= 120;                                            /*Cr范围为128-134时，需要转换成TI:8-14*/
        }
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                                /* 设置消息选择                             */
        Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));       /* 将消息空间清零                           */
        SSA_DealMsgFromSS(&stSsMsg);
    }

    Ss_SndRelCmpl( VOS_NULL_PTR, ucTi, SS_CAUSE_MSG_TYPE_ERR_OR_NOT_IMPLEMENT );        /* 发送DR(RELEASE COMPLETE #97)             */
    Ss_SndMmssRelReq( ucTi );                                                   /* 向MM发送MMSS_REL_REQ原语，释放MM连接     */
    Ss_EntityClear( ucTi );                                                     /* 释放对应的SS实体                         */
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

