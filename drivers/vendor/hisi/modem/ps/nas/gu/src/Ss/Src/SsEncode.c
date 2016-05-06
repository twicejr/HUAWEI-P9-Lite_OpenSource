/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsEncode.c
  Description  : SS编码
  Function List:
      1.  Ss_EncodeField               对指定IE进行编码
      2.  Ss_EncodeRegister            REGISTER消息编码
      3.  Ss_EncodeFacility            FACILITY消息编码
      4.  Ss_EncodeRelCmpl             RELEASE COMPLETE消息编码
      5.  Ss_Encode                    SS编码主函数
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
#define    THIS_FILE_ID        PS_FILE_ID_SS_ENCODE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/***********************************************************************
*  MODULE   : Ss_EncodeField
*  FUNCTION : 对指定IE进行编码
*  INPUT    : VOS_UINT8 *pDestTmp;          编码后数据的地址
*             VOS_UINT8 ucIEI;              该IE对应的IEI
*             VOS_UINT32 ulFieldLen;         该IE的编码长度
*             VOS_UINT8 *pSrcTmp;           编码前数据的地址
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          编码后的长度
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_UINT32 Ss_EncodeField(
                     VOS_UINT8 *pDestTmp,                                           /* 编码后数据的地址                         */
                     VOS_UINT8 ucIEI,                                               /* 该IE对应的IEI                            */
                     VOS_UINT32 ulFieldLen,                                          /* 该IE的编码长度                           */
                     VOS_UINT8 *pSrcTmp                                             /* 编码前数据的地址                         */
                     )
{
    VOS_UINT8  ucFldLenTmp;                                                         /* 定义IE的长度记录                         */

    ucFldLenTmp = 0;                                                            /* 初始化IE的长度记录                       */

    if( SS_IEINONE != ucIEI )
    {                                                                           /* 判断IE的类型是否存在                     */
        *( pDestTmp + ucFldLenTmp ) = ucIEI;                                    /* 设置指定IE存在标志                       */
        ucFldLenTmp++;                                                          /* 更新IE的长度记录                         */
    }
    *( pDestTmp + ucFldLenTmp ) = ( VOS_UINT8 )ulFieldLen;                          /* 设置此IE长度                             */
    ucFldLenTmp++;                                                              /* 更新IE的长度记录                         */
    Ss_MemCpy( pDestTmp + ucFldLenTmp, pSrcTmp, ulFieldLen );                   /* 复制此IE的数据                           */

    return( ulFieldLen + ucFldLenTmp );                                         /* 返回编码后的长度                         */
}

/***********************************************************************
*  MODULE   : Ss_EncodeRegister
*  FUNCTION : REGISTER消息编码
*  INPUT    : ST_BEGIN_REQ *pSrc;       编码前数据的地址
*             VOS_UINT8 *pDest;             编码后数据的地址
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          编码后的长度
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_UINT32 Ss_EncodeRegister(
                        ST_BEGIN_REQ *pSrc,                                     /* 编码前数据的地址                         */
                        VOS_UINT8 *pDest                                            /* 编码后数据的地址                         */
                        )
{
    VOS_UINT32   ulCodeLen;                                                          /* 定义编码后的长度                         */
    VOS_UINT8   *pSrcTmp;                                                           /* 定义指定IE的编码前数据的地址             */
    VOS_UINT32   ulFieldLen;                                                         /* 定义指定IE的编码长度                     */

    ulCodeLen = 0;                                                              /* 初始化编码后的长度                       */
    ulFieldLen = 0;                                                             /* 初始化指定IE的编码长度                   */

    ulFieldLen = pSrc->Facility.ulCnt;                                          /* 设置IE Facility的编码长度                */
    pSrcTmp = pSrc->Facility.Facility;                                          /* 设置该IE的编码前数据的地址               */
    ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
        SS_IEIFACILITY, ulFieldLen, pSrcTmp );                                  /* 调用IE编码函数                           */

    if( 1 == pSrc->OP_Sspversion )
    {                                                                           /* 判断IE SS version是否存在                */
        ulFieldLen = pSrc->Sspversion.ulCnt;                                    /* 设置该IE的编码长度                       */
        pSrcTmp = pSrc->Sspversion.Sspversion;                                  /* 设置该IE的编码前数据的地址               */
        ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
            SS_IEISSPVERSION, ulFieldLen, pSrcTmp );                            /* 调用IE编码函数                           */
    }
    return ulCodeLen;                                                           /* 返回编码后的长度                         */
}

/***********************************************************************
*  MODULE   : Ss_EncodeFacility
*  FUNCTION : FACILITY消息编码
*  INPUT    : ST_SSP_MSGS_FACILITY_REQ *pSrc;   编码前数据的地址
*             VOS_UINT8 *pDest;                     编码后数据的地址
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          编码后的长度
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_UINT32 Ss_EncodeFacility(
                        ST_SSP_MSGS_FACILITY_REQ *pSrc,                         /* 编码前数据的地址                         */
                        VOS_UINT8 *pDest                                            /* 编码后数据的地址                         */
                        )
{
    VOS_UINT32   ulCodeLen;                                                          /* 定义编码后的长度                         */
    VOS_UINT8   *pSrcTmp;                                                           /* 定义指定IE的编码前数据的地址             */
    VOS_UINT32   ulFieldLen;                                                         /* 定义指定IE的编码长度                     */

    ulCodeLen = 0;                                                              /* 初始化编码后的长度                       */
    ulFieldLen = 0;                                                             /* 初始化指定IE的编码长度                   */

    ulFieldLen = pSrc->Facility.ulCnt;                                          /* 设置IE Facility的编码长度                */
    pSrcTmp = pSrc->Facility.Facility;                                             /* 设置该IE的编码前数据的地址               */
    ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
        SS_IEINONE, ulFieldLen, pSrcTmp );                                      /* 调用IE编码函数                           */

    return ulCodeLen;                                                           /* 返回编码后的长度                         */
}

/***********************************************************************
*  MODULE   : Ss_EncodeRelCmpl
*  FUNCTION : RELEASE COMPLETE消息编码
*  INPUT    : ST_END_REQ *pSrc;         编码前数据的地址
*             VOS_UINT8 *pDest;             编码后数据的地址
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          编码后的长度
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_UINT32 Ss_EncodeRelCmpl(
                       ST_END_REQ *pSrc,                                        /* 编码前数据的地址                         */
                       VOS_UINT8 *pDest                                             /* 编码后数据的地址                         */
                       )
{
    VOS_UINT32   ulCodeLen;                                                          /* 定义编码后的长度                         */
    VOS_UINT8   *pSrcTmp;                                                           /* 定义指定IE的编码前数据的地址             */
    VOS_UINT32   ulFieldLen;                                                         /* 定义指定IE的编码长度                     */

    ulCodeLen = 0;                                                              /* 初始化编码后的长度                       */
    ulFieldLen = 0;                                                             /* 初始化指定IE的编码长度                   */

    if( 1 == pSrc->OP_Cause )
    {                                                                           /* 判断IE Cause是否存在                     */
        ulFieldLen = pSrc->Cause.ulCnt;                                         /* 设置该IE的编码长度                       */
        pSrcTmp = pSrc->Cause.Cause;                                            /* 设置该IE的编码前数据的地址               */
        ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
            SS_IEICAUSE, ulFieldLen, pSrcTmp );                                 /* 调用IE编码函数                           */
    }
    if( 1 == pSrc->OP_Facility )
    {                                                                           /* 判断IE Facility是否存在                  */
        ulFieldLen = pSrc->Facility.ulCnt;                                      /* 设置该IE的编码长度                       */
        pSrcTmp = pSrc->Facility.Facility;                                      /* 设置该IE的编码前数据的地址               */
        ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
            SS_IEIFACILITY, ulFieldLen, pSrcTmp );                              /* 调用IE编码函数                           */
    }
    return ulCodeLen;                                                           /* 返回编码后的长度                         */
}

/***********************************************************************
*  MODULE   : Ss_Encode
*  FUNCTION : SS编码主函数
*  INPUT    : VOS_VOID *pSrc;           编码前数据的地址
*             VOS_VOID *pDest;          编码后数据的地址
*             VOS_UINT8 ucMsgType;      消息类型
*             VOS_UINT8 ucTi;           空口消息中的Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;      编码后的长度
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
************************************************************************/

VOS_UINT32 Ss_Encode(
                VOS_VOID *pSrc,                                                     /* 编码前数据的地址                         */
                VOS_VOID *pDest,                                                    /* 编码后数据的地址                         */
                VOS_UINT8 ucMsgType,                                                /* 消息类型                                 */
                VOS_UINT8 ucTi                                                      /* 空口消息中的Ti                           */
                )
{
    VOS_UINT32   ulCodeLen;                                                     /* 定义编码后的长度                         */
    ST_SSP_MSG  *pstSsMsg;                                                      /* 用于指示编码所用的结构                   */
    VOS_UINT8    ucMsgTi;

    ulCodeLen = 0;                                                              /* 初始化编码后的长度                       */

    pstSsMsg = ( ST_SSP_MSG *)pSrc;                                             /* 获取编码所用的结构                       */

    ucMsgTi = GET_MSG_TI(ucTi);

    *(( VOS_UINT8 *)pDest + ulCodeLen ) =
        ( VOS_UINT8 )( NAS_PD_SS | ( ucMsgTi << 4 ));     /* 设置PD及TI字节                           */

    ulCodeLen++;                                                                /* 更新编码后的长度                         */

    switch( ucMsgType )
    {                                                                           /* 按消息类型分发                           */
    case SS_MSG_REGISTER:                                                       /* IE: REGISTER                             */
        *(( VOS_UINT8 *)pDest + ulCodeLen ) = SS_MSG_REGISTER;                      /* 设置消息类型                             */
        ulCodeLen++;                                                            /* 更新编码后的长度                         */
            ulCodeLen += Ss_EncodeRegister( &(pstSsMsg->SspmsgCore.u.BeginReq),
            ( VOS_UINT8 *)pDest +ulCodeLen );                                       /* 调用REGISTER消息编码函数                 */
        break;                                                                  /* 跳出分支                                 */
    case SS_MSG_FACILITY:                                                       /* IE: FACILITY                             */
        *(( VOS_UINT8 *)pDest + ulCodeLen ) = SS_MSG_FACILITY;                      /* 设置消息类型                             */
        ulCodeLen++;                                                            /* 更新编码后的长度                         */
            ulCodeLen += Ss_EncodeFacility( &(pstSsMsg->SspmsgCore.u.FacilityReq),
            ( VOS_UINT8 *)pDest +ulCodeLen );                                       /* 调用FACILITY消息编码函数                 */
        break;                                                                  /* 跳出分支                                 */
    case SS_MSG_RELCMPL:                                                        /* IE: RELCMPL                              */
        *(( VOS_UINT8 *)pDest + ulCodeLen ) = SS_MSG_RELCMPL;                       /* 设置消息类型                             */
        ulCodeLen++;                                                            /* 更新编码后的长度                         */
            ulCodeLen += Ss_EncodeRelCmpl( &(pstSsMsg->SspmsgCore.u.EndReq),
            ( VOS_UINT8 *)pDest +ulCodeLen );                                       /* 调用REL CMPL消息编码函数                 */
        break;                                                                  /* 跳出分支                                 */
    default:                                                                    /* 其他IE                                   */
        SS_WARN_LOG( "\n [Error]Ss_Encode MsgType Error! \r" );
        break;                                                                  /* 跳出分支                                 */
    }
    return ulCodeLen;                                                           /* 返回编码后的长度                         */
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

