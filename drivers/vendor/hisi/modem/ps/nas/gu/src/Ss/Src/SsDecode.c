/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsDecode.c
  Description  : SS解码
  Function List:
      1.  Ss_DecodeField         对指定IE进行解码
      2.  Ss_DecodeRegister      REGISTER消息解码
      3.  Ss_DecodeFacility      FACILITY消息解码
      4.  Ss_DecodeRelCmpl       RELEASE COMPLETE消息解码
      5.  Ss_Decode              SS解码主函数
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
#define    THIS_FILE_ID        PS_FILE_ID_SS_DECODE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*lint -save -e958 */
/***********************************************************************
*  MODULE   : Ss_DecodeField
*  FUNCTION : 对指定IE进行解码
*  INPUT    : VOS_UINT8           *pucField;  指定IE解码前数据的地址
*             ST_SSP_IES_FACILITY *pOct;      指定IE解码后数据地的址
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_VOID Ss_DecodeField(
                    VOS_UINT8 *pucField,                                            /* 指定IE解码前数据的地址                   */
                    ST_SSP_IES_FACILITY *pOct                                       /* 指定IE解码后数据的地址                   */
                    )
{
    VOS_UINT8   ucFieldLen;                                                         /* 定义指定IE的长度                         */
    ucFieldLen = *pucField;                                                     /* 获取该IE的长度                           */
    pOct->ulCnt = ucFieldLen;                                                   /* 设置数据长度                             */
    Ss_MemCpy( pOct->Facility, pucField + 1, ucFieldLen );                          /* 设置数据                                 */
}

/***********************************************************************
*  MODULE   : Ss_DecodeRegister
*  FUNCTION : REGISTER消息解码
*  INPUT    : VOS_VOID *pSrc;               解码前数据的地址
*             ST_BEGIN_IND *pMsg;       解码后数据的地址
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/
VOS_VOID Ss_DecodeRegister(
                        VOS_UINT8 *pSrc,                                            /* 解码前数据的地址                         */
                        ST_BEGIN_IND *pMsg                                      /* 解码后数据的地址                         */
                        )
{
    Ss_DecodeField( pSrc + 1, &( pMsg->Facility ));                             /* 调用IE解码函数                           */
    return;                                                          /* 返回解码成功或失败标志                   */
}

/***********************************************************************
*  MODULE   : Ss_DecodeFacility
*  FUNCTION : FACILITY消息解码
*  INPUT    : VOS_VOID *pSrc;                       解码前数据的地址
*             ST_SSP_MSGS_FACILITY_IND *pMsg;   解码后数据的地址
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/
VOS_VOID Ss_DecodeFacility(
                        VOS_UINT8 *pSrc,                                            /* 解码前数据的地址                         */
                        ST_SSP_MSGS_FACILITY_IND *pMsg                          /* 解码后数据的地址                         */
                        )
{
    Ss_DecodeField( pSrc, &( pMsg->Facility ));                                 /* 调用IE解码函数                           */

    return;                                                          /* 返回解码成功或失败标志                   */
}

/***********************************************************************
*  MODULE   : Ss_DecodeRelCmpl
*  FUNCTION : RELEASE COMPLETE消息解码
*  INPUT    : VOS_VOID *pSrc;              解码前数据的地址
*             ST_END_IND *pMsg;        解码后数据的地址
*             VOS_UINT32 ulMsgDataLen;      消息中IE的总长度
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8 ucResult;          解码成功标志
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_UINT8 Ss_DecodeRelCmpl(
                        VOS_UINT8 *pSrc,                                            /* 解码前数据的地址                         */
                        ST_END_IND *pMsg,                                       /* 解码后数据的地址                         */
                        VOS_UINT32 ulMsgDataLen                                      /* 消息中IE的总长度                         */
                        )
{
    VOS_UINT8   ucIEI;                                                              /* 定义指定IE对应的IEI                      */
    VOS_UINT32   ulLenOffset;                                                        /* 定义用于消息中IE的定位的长度偏移         */
    VOS_UINT8   *pucField;                                                          /* 定义指向指定IE的指针                     */
    VOS_UINT8   ucResult;                                                           /* 定义解码成功标志                         */

    ucIEI = 0;                                                                  /* 初始化指定IE对应的IEI                    */
    ulLenOffset = 0;                                                            /* 初始化长度偏移                           */
    pucField = VOS_NULL_PTR;                                                            /* 初始化指定IE的指针                       */
    ucResult = WUEPS_TRUE;                                                      /* 初始化解码成功标志                       */

    for( ; ulLenOffset < ulMsgDataLen ; )
    {                                                                           /* 循环判断各IE是否存在                     */
        pucField = pSrc + ulLenOffset + 1;                                      /* 获取指定IE                               */
        ucIEI = *( pSrc + ulLenOffset );                                        /* 获取指定IEI                              */
        switch( ucIEI )
        {                                                                       /* 按IE的类型分发                           */
        case SS_IEIFACILITY:                                                    /* IE: FACILITY                             */
            pMsg->OP_Facility = 1;                                              /* 设置该IE存在标志                         */
                Ss_DecodeField( pucField, (ST_SSP_IES_FACILITY*)(&(pMsg->Facility)));                        /* 调用IE解码函数                           */
            break;                                                              /* 跳出分支                                 */
        case SS_IEICAUSE:                                                       /* IE: CAUSE                                */
            pMsg->OP_Cause = 1;                                                 /* 设置该IE存在标志                         */
                Ss_DecodeField( pucField, (ST_SSP_IES_FACILITY*)(&(pMsg->Cause)));                           /* 调用IE解码函数                           */
            break;                                                              /* 跳出分支                                 */
        default:                                                                /* 其他IE                                   */
            ucResult = WUEPS_FALSE;                                             /* 设置解码失败标志                         */
            break;                                                              /* 跳出分支                                 */
        }

        if( WUEPS_FALSE == ucResult )
        {                                                                       /* 判断解码是否失败                         */
            break;                                                              /* 跳出循环                                 */
        }
        ulLenOffset += *pucField + 2;                                           /* 更新长度偏移                             */
    }
    return ucResult;                                                            /* 返回解码成功或失败标志                   */
}

/***********************************************************************
*  MODULE   : Ss_Decode
*  FUNCTION : SS解码主函数
*  INPUT    : VOS_VOID *pSrc;           解码前数据的地址
*             VOS_VOID *pDest;          解码后数据的地址
*             VOS_UINT32 ulMsgLen;       消息长度
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8 ucResult;       解码成功标志
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_UINT8 Ss_Decode(
                VOS_VOID *pSrc,                                                     /* 解码前数据的地址                         */
                VOS_VOID *pDest,                                                    /* 解码后数据的地址                         */
                VOS_UINT32 ulMsgLen                                                  /* 消息长度                                 */
                )
{
    VOS_UINT8   ucMsgType;                                                          /* 定义消息类型                             */
    VOS_UINT8   ucResult;                                                           /* 定义解码成功标志                         */

    ucResult = WUEPS_TRUE;                                                      /* 初始化解码成功标志                       */

    ucMsgType = (( VOS_UINT8 *)pSrc)[1];                                            /* 获取消息类型                             */
    switch( ucMsgType )
    {                                                                           /* 按消息类型分发                           */
    case SS_MSG_REGISTER:
            (( ST_SSP_MSG_CORE *)pDest )->ucChoice = D_SMC_BEGIN_IND;           /* 设置消息类型                             */
            Ss_DecodeRegister(( VOS_UINT8 *)pSrc + 2,
                              (ST_BEGIN_IND *)(&((( ST_SSP_MSG_CORE *)pDest )->u.BeginInd)));             /* 调用REGISTER消息解码函数                 */
        break;                                                                  /* 跳出分支                                 */
    case SS_MSG_FACILITY:
            Ss_DecodeFacility(( VOS_UINT8 *)pSrc + 2,
                              (ST_SSP_MSGS_FACILITY_IND *)(&((( ST_SSP_MSG_CORE *)pDest )->u.BeginInd)));            /* 调用FACILITY消息解码函数                 */
            (( ST_SSP_MSG_CORE *)pDest )->ucChoice = D_SMC_FACILITY_IND;        /* 设置消息类型                             */
        break;                                                                  /* 跳出分支                                 */
    case SS_MSG_RELCMPL:
        ucResult = Ss_DecodeRelCmpl(( VOS_UINT8 *)pSrc + 2,
                                        (ST_END_IND *)(&((( ST_SSP_MSG_CORE *)pDest )->u.BeginInd)),
                                        ulMsgLen - 2 );                                 /* 调用REL CMPL消息解码函数                 */
        if( WUEPS_TRUE == ucResult )
        {                                                                       /* 判断解码是否成功                         */
            (( ST_SSP_MSG_CORE *)pDest )->ucChoice = D_SMC_END_IND;             /* 设置消息类型                             */
        }
        break;                                                                  /* 跳出分支                                 */
    default:
        ucResult = WUEPS_FALSE;                                                 /* 设置解码失败标志                         */
        break;                                                                  /* 跳出分支                                 */
    }

    return ucResult;                                                            /* 返回解码成功或失败标志                   */
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

