/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsSndAir.c
  Description  : 发送空口消息的处理
  Function List:
      1.  Ss_SaveRegister           用于缓存REGISTER消息
      2.  Ss_SndRegister            发送REGISTER消息
      3.  Ss_SndFacility            发送FACILITY消息
      4.  Ss_SndRelCmpl             发送RELEASE COMPLETE消息
  History:
      1.  张志勇 2004.03.09   新版作成
*******************************************************************************/

#include "SsInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_SNDAIR_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/***********************************************************************
*  MODULE   : Ss_SaveRegister
*  FUNCTION : 用于缓存REGISTER消息
*  INPUT    : VOS_VOID      *pSspMsg        当前处理的消息
*             VOS_UINT8     ucTi            对应的Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_VOID Ss_SaveRegister(
                     VOS_VOID *pstSsMsg,
                     VOS_UINT8 ucTi
                     )
{
    VOS_UINT32   ulEncLen;                                                           /* 编码后的消息长度                         */
    VOS_VOID    *pucEncDest;                                                        /* 指向编码后的数据                         */

    SS_NORM_LOG1("Ss_SaveRegister entered. ucTi:", ucTi);

    pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
        SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                    /* 申请SS编码空间                           */
    if ( VOS_NULL_PTR == pucEncDest )
    {
        return;
    }
    ulEncLen = Ss_Encode( pstSsMsg, pucEncDest, SS_MSG_REGISTER, ucTi );            /* SS编码                                   */
    g_SsSaveMsg[ucTi-8].ulMsgLen = ulEncLen;                                    /* 缓存消息长度                             */
    g_SsSaveMsg[ucTi-8].pucMsg = (VOS_UINT8 *)pucEncDest;                                    /* 缓存消息                                 */
}

/***********************************************************************
*  MODULE   : Ss_DeleteRegister
*  FUNCTION : 用于释放SaveREGISTER时分配的内存
*  INPUT    : VOS_UINT8     ucTi            对应的Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
 1.日    期   : 2015年9月19日
   作    者   : c00318887
   修改内容   : 新生成函数
************************************************************************/

VOS_VOID Ss_DeleteRegister(
                     VOS_UINT8 ucTi
                     )
{
    SS_NORM_LOG1("Ss_DeleteRegister entered. ucTi:", ucTi);

    g_SsSaveMsg[ucTi-8].ulMsgLen = 0;                                           /* 缓存消息长度清0                          */

    if (VOS_NULL_PTR != g_SsSaveMsg[ucTi-8].pucMsg)
    {
        PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, g_SsSaveMsg[ucTi-8].pucMsg );    /* 释放缓存的REGISTER消息                   */
        g_SsSaveMsg[ucTi-8].pucMsg = VOS_NULL_PTR;
    }
}

/***********************************************************************
*  MODULE   : Ss_SndRegister
*  FUNCTION : 发送REGISTER消息
*  INPUT    : VOS_UINT8     ucTi            对应的Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_VOID Ss_SndRegister(
                    VOS_UINT8 ucTi
                    )
{
    VOS_UINT32   ulEncLen;                                                           /* 编码后的消息长度                         */
    VOS_VOID    *pucEncDest;                                                        /* 指向编码后的数据                         */

    ulEncLen = g_SsSaveMsg[ucTi-8].ulMsgLen;
    pucEncDest = g_SsSaveMsg[ucTi-8].pucMsg;                                    /* 获取缓存的REGISTER消息                   */

    Ss_SndMmssDataReq( ucTi, (VOS_UINT8 *)pucEncDest, ulEncLen );                            /* 发送MMSS_DATA_REQ                        */
    g_SsSaveMsg[ucTi-8].ulMsgLen = 0;                                           /* 缓存消息长度清0                          */
    PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                             /* 释放缓存的REGISTER消息                   */
}

/***********************************************************************
*  MODULE   : Ss_SndFacility
*  FUNCTION : 发送FACILITY消息
*  INPUT    : VOS_VOID      *pSspMsg        当前处理的消息
*             VOS_UINT8     ucTi            Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_VOID Ss_SndFacility(
                    VOS_VOID *pSspMsg,
                    VOS_UINT8 ucTi
                    )
{
    VOS_UINT32   ulEncLen;                                                           /* 编码后的消息长度                         */
    VOS_VOID    *pucEncDest;                                                        /* 指向编码后的数据                         */
    VOS_UINT8   *pucSsMsg;

    pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
        SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                    /* 申请SS编码空间                           */
    if ( VOS_NULL_PTR == pucEncDest )
    {
        return;
    }
    ulEncLen = Ss_Encode( pSspMsg, pucEncDest, SS_MSG_FACILITY, ucTi );         /* SS编码                                   */
    pucSsMsg = (VOS_UINT8 *)pucEncDest;
    Ss_SndMmssDataReq( ucTi, pucSsMsg, ulEncLen );                            /* 发送MMSS_DATA_REQ                        */
    PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                             /* 释放该消息                               */
}

/***********************************************************************
*  MODULE   : Ss_SndRelCmpl
*  FUNCTION : 发送RELEASE COMPLETE消息
*  INPUT    : VOS_VOID      *pSspMsg        当前处理的消息。若为NULL，
*                                       则自己作一个RELEASE COMPLETE消息
*             VOS_UINT8     ucTi            对应的Ti
*             VOS_UINT8     ucCause         原因
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇   04-03-09  新版作成
*     2.  张志勇   05-03-16  修改CAUSE的填写
      3.日    期   : 2012年12月19日
        作    者   : l00198894
        修改内容   : DTS2012121904363: 解决BVT测试中SS发送RELCOMPL编码失败
************************************************************************/
VOS_VOID Ss_SndRelCmpl(
                   VOS_VOID *pSspMsg,
                   VOS_UINT8 ucTi,
                   VOS_UINT8 ucCause
                   )
{
    VOS_UINT32   ulEncLen;                                                           /* 编码后的消息长度                         */
    VOS_VOID    *pucEncDest;                                                        /* 指向编码后的数据                         */
    VOS_UINT8   *pucSsMsg;
    ST_SSP_MSG    stSsMsg;

    PS_MEM_SET(&stSsMsg, 0, sizeof(stSsMsg));

    if( VOS_NULL_PTR == pSspMsg )
    {                                                                           /* 需要自己制作一个RELEASE COMPLETE消息     */
        stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_REQ;

        stSsMsg.SspmsgCore.u.EndReq.OP_Cause = 1;                                                  /* 设置存在Cause域                          */

        /* 设置Cause数据长度                        */
        stSsMsg.SspmsgCore.u.EndReq.Cause.ulCnt = 2;                                             /* 设置Cause数据长度                        */

        stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[0] = 0xe0;                                 /* 填写coding standard                      */
        stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[1] = ucCause;                              /* 设置Cause数据                            */

        pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
            SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                /* 申请SS编码空间                           */
        if ( VOS_NULL_PTR == pucEncDest)
        {
            return;
        }

        PS_MEM_SET(pucEncDest, 0, SS_MAX_MSG_LEN);

        ulEncLen = Ss_Encode( &stSsMsg, pucEncDest, SS_MSG_RELCMPL, ucTi );         /* SS编码                                   */
        pucSsMsg = (VOS_UINT8 *)pucEncDest;

        Ss_SndMmssDataReq( ucTi, pucSsMsg, ulEncLen );                        /* 发送MMSS_DATA_REQ                        */
        PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                         /* 释放该消息                               */

    }
    else
    {
        pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
            SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                /* 申请SS编码空间                           */
        if ( VOS_NULL_PTR == pucEncDest)
        {
            return;
        }

        PS_MEM_SET(pucEncDest, 0, SS_MAX_MSG_LEN);

        ulEncLen = Ss_Encode( pSspMsg, pucEncDest, SS_MSG_RELCMPL, ucTi );      /* SS编码                                   */
        pucSsMsg = (VOS_UINT8 *)pucEncDest;
        Ss_SndMmssDataReq( ucTi, pucSsMsg, ulEncLen );                        /* 发送MMSS_DATA_REQ                        */
        PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                         /* 释放该消息                               */
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

