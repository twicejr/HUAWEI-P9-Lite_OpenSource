/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmRcvRabm.c
  Description  : 接收RABM消息的处理
  Function List:
                1.  SM_RcvRabmDeActReq
  History:
      1.   张志勇      2003.12.08   新规作成
      2.   L47619      2006.08.30   根据问题单修改:A32D05864
*******************************************************************************/
#include "SmInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SM_RCVRABM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


VOS_VOID SM_RcvRabmDeActReq(
    RABMSM_DEACTIVATE_REQ_STRU         *pMsgIe                                  /* 接收到的消息                             */
)
{
    VOS_UINT8                          *pMsg;
    SM_NW_MSG_STRU                     *pSmMsg;
    VOS_UINT8                           ucCntxtIndex;

    ucCntxtIndex = (VOS_UINT8)pMsgIe->ulNsapi - SM_NSAPI_OFFSET;                /* 获取实体的索引                           */
    if( SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* 状态为激活                               */
        if(0 != g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength)
        {                                                                       /* Qos不为空                                */
            pMsg =  (VOS_UINT8 *)SM_Malloc(sizeof(SM_NW_MSG_STRU));             /* 申请内存                                 */
            if ( VOS_NULL_PTR == pMsg )
            {
                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                        "SM_RcvRabmDeActReq:ERROR:Alloc msg fail!" );
                return;
            }

            SM_MemSet(pMsg, 0, sizeof(SM_NW_MSG_STRU));
            pSmMsg = (SM_NW_MSG_STRU *)pMsg;

            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[5] = 0;        /* 修改内部的Qos maxrate uplink修改为0      */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[6] = 0;        /* 修改内部的Qos maxrate downlink修改为0    */
            pSmMsg->Qos.ucLen = (VOS_UINT8)
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength;         /* 填写QoS长度                              */
            pSmMsg->Qos.pValue = (VOS_UINT8 *)SM_Malloc(pSmMsg->Qos.ucLen);                      /* 申请存储QoS内存                          */
            if ( VOS_NULL_PTR == pSmMsg->Qos.pValue )
            {
                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                        "SM_RcvRabmDeActReq:ERROR:Alloc pSmMsg->Qos.pValue fail!" );
                return;
            }
            PS_MEM_CPY(pSmMsg->Qos.pValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength); /* 存储QoS                                  */

            pSmMsg->ucRadioPri = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri;
            SM_SndTafSmPdpModifyInd( pSmMsg,ucCntxtIndex);                      /* 通知TAF修改Qos                           */
            SM_Free( pSmMsg->Qos.pValue );                                      /* 释放内存                                 */
            SM_Free( pSmMsg );                                                  /* 释放内存                                 */
        }
    }
    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

