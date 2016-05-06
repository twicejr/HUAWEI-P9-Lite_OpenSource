/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvTimer.c
  Description  : 接收Timer溢出消息的处理
  Function List:
      1.  Ss_T551Expiry         T551溢出后的处理
      2.  Ss_RcvTimerOut        进行TIMER溢出的分发处理（该函数由CC调用）
  History:
      1.  张志勇 2004.03.09   新版作成
      2.  日    期   : 2006年10月8日
          作    者   : luojian id:60022475
          修改内容   : 问题单号:A32D06583，修改Ss_RcvTimerOut函数
      3.  丁  庆 2006.11.07   问题单A32D07063
*******************************************************************************/


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


/***********************************************************************
*  MODULE   : Ss_RcvTimerOut
*  FUNCTION : 进行TIMER溢出的分发处理（该函数由CC调用）
*  INPUT    : VOS_UINT8     ucTi        对应的Ti
*             VOS_UINT8     ucTimerId   定时器id
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
      2.  日    期   : 2006年10月8日
          作    者   : luojian id:60022475
          修改内容   : 问题单号:A32D06583，修改Ss_RcvTimerOut函数
      3.日    期   : 2012年02月24日
        作    者   : 傅映君/f62575
        修改内容   : C50_IPC Project 新增等待USIM的FDN检查结果超时处理
      4.日    期   : 2013年04月08日
        作    者   : l65478
        修改内容   : DTS2013032201710:功耗下不去
      5.日    期   : 2013年05月17日
        作    者   : w00176964
        修改内容   : SS FDN&Call Control项目:FDN检查删除
      6.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容   :DTS2013082903019:支持ss重发功能
      7.日    期   : 2014年5月22日
        作    者   : z00161729
        修改内容   : DTS2014050601476:L打电话重定向到g过程中电话挂断，mm缓存cc abort，
                     g查询csfb状态是存在，lau结束后没有启动自主FR流程到L
************************************************************************/

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

