


#include "SsInclude.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*=>A32D07063*/
#if 0
/***********************************************************************
*  MODULE   : Ss_T551Expiry
*  FUNCTION : T551溢出后的处理
*  INPUT    : VOS_UINT8     ucTi        对应的Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_VOID Ss_T551Expiry(
                   VOS_UINT8 ucTi
                   )
{
    ST_SSP_MSG                      stSsMsg;

    SS_WARN_LOG( "\n SS TimerExpiry: T551\r" );
    if( SS_S_CONNECTED == g_SsEntity[ucTi].ucState )
    {                                                                           /* 判断是否存在连接                         */

        stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                   /* 设置CR                                   */
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                            /* 设置消息选择                             */
        Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));    /* 将消息空间清零                           */
        SSA_DealMsgFromSS(&stSsMsg);

        Ss_SndRelCmpl( VOS_NULL_PTR, ucTi, SS_CAUSE_RECOVERY_TIMER_EXPIRY );            /* 发送DR(RELEASE COMPLETE #102)            */
        Ss_SndMmssRelReq( ucTi );                                               /* 向MM发送MMSS_REL_REQ原语，释放MM连接     */
        Ss_EntityClear( ucTi );                                                 /* 释放对应的SS实体                         */
    }
}
#endif
/*<=A32D07063*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVTIMER_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/




VOS_VOID Ss_RcvTimerOut(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT8                           ucSsTi;


    if (TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER == ucTimerId)
    {
        ucSsTi = Ss_GetSsTi(ucTi);

        Ss_SndMmssAbortReq(ucSsTi);
    }


    TAF_SSA_RcvTimerExpired(ucTimerId, ucTi);




    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

