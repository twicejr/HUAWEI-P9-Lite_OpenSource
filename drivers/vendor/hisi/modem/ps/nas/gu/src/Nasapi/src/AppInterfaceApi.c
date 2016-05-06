/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : AppInterfaceApi.c
  Description  : 提供给APP的接口API函数实体
  Function List:
      1.
  History:
      1.  张志勇   2005.01.04   新规作成
      2.  郜东东   2005.09.20   增加SMS相关的接口函数
      3.  韩鲁峰   2005-04-25   for A32D01738
      4.  丁  庆   2007-09-26   A32D12924
*******************************************************************************/
#include "PsTypeDef.h"
#include "ExtAppCmInterface.h"
#include "NasComm.h"

#include "ExtAppRabmInterface.h"
#include "RabmTafInterface.h"
#include "TTFMem.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_APPINTERFACEAPI_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/***********************************************************************
*  MODULE   : Api_AppRabmDataReq
*  FUNCTION : APP向RABM发送CS域数据
*  INPUT    : ST_APP_RABM_DATA *pRabmDataReq
*  OUTPUT   : void
*  RETURN   : void
*  NOTE     :
*  HISTORY  :
*     1.  L47619   2008-03-06  NAS分组域架构优化(该函数仅支持WCDMA模式CS域上行数据)

  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
************************************************************************/
VOS_VOID Api_AppRabmDataReq( ST_APP_RABM_DATA *pRabmDataReq )
{
    VOS_UINT32  ulDataLen;
    TAFRABM_CS_DATA_REQ_STRU   *pSndCsMsg = VOS_NULL_PTR;                               /* 定义发送到CS域的指针                     */
    VOS_UINT32  ulRet;

    if (D_RABM_CS_DOMAIN != pRabmDataReq->ucDomain)
    {
        PS_NAS_LOG( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR,  "Api_AppRabmDataReq(CS):ucDomain is not D_RABM_CS_DOMAIN!" );
        return;
    }

    ulDataLen = (pRabmDataReq->ulDataLen + 7) / 8;                          /* 将APP传来的bit长度改为字节长度           */
    pSndCsMsg = (TAFRABM_CS_DATA_REQ_STRU *)
                PS_ALLOC_MSG( WUEPS_PID_TAF,
                              (sizeof(TAFRABM_CS_DATA_REQ_STRU)
                                            + ulDataLen) - 4);
    if (VOS_NULL_PTR ==pSndCsMsg)
    {
        PS_NAS_LOG( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR,  "Api_AppRabmDataReq(CS):Alloc msg fail!" );
        return;
    }

    pSndCsMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndCsMsg->MsgHeader.ulSenderPid = WUEPS_PID_TAF;
    pSndCsMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndCsMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;
    pSndCsMsg->MsgHeader.ulMsgName   = TAFRABM_CS_DATA_REQ;

    pSndCsMsg->ulSi = pRabmDataReq->ucRabId;                                /* 保存SI                                   */
    pSndCsMsg->ulDataLen = pRabmDataReq->ulDataLen;                         /* 保存数据长度                             */
    PS_NAS_MEM_CPY(pSndCsMsg->aucData,
                pRabmDataReq->pucData,
                ulDataLen);                                                 /* 获得数据                                 */


    PS_NAS_LOG( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL,   "\n Api_AppRabmDataReq: ucDomain   = D_RABM_CS_DOMAIN\r" );
    PS_NAS_LOG1( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                 "\n Api_AppRabmDataReq: ucRabId    = \r",
                 pRabmDataReq->ucRabId );
    PS_NAS_LOG1( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                 "\n Api_AppRabmDataReq: ulDataLen  = \r",
                 (VOS_INT32)pRabmDataReq->ulDataLen );

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pSndCsMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_TAF, "Api_AppRabmDataReq():WARNING:SEND LMM START REQ FIAL");
    }

}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

