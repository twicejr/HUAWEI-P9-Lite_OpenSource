/******************************************************************************/
/* Copyright (c) ,1988-2001,Huawei Tech. Co.,Ltd                              */
/* File name     :Taf_Tafm_Db.c                                               */
/* Author        :zzy                                                         */
/* Description   :TAF通信参数管理模块                                         */
/* Others        :                                                            */
/* Function List :                                                            */
/* History       :                                                            */
/*               :2005-04-13 初稿                                             */
/*               :2005-12-13 添加CS查询参数     修改人:d49431                 */
/*               :2006-02-23 问题单:A32D02143   修改人:L47619                 */
/*               :2006-02-23 问题单:A32D02147   修改人:L47619                 */
/*               :2006-03-13 问题单:A32D02480   修改人:H41410                 */
/*               :2006-03-13 问题单:A32D02493   修改人:L47619                 */
/*               :2006-03-13 问题单:A32D02764   修改人:D49431                 */

#include "Taf_Common.h"
#include "TafClientApi.h"
#include "Taf_Aps.h"
#include "MmaAppLocal.h"
#include "MnComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_TAFM_DB_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*lint -save -e958 */

/**********************************************************/
/*         本端被TAF调用的通信参数管理事件上报接口API     */
/**********************************************************/

VOS_VOID  Taf_ParaSetResult (VOS_UINT16            ClientId,
                         VOS_UINT8                   OpId,
                         TAF_PARA_SET_RESULT      Result,
                         TAF_PARA_TYPE      QueryType,
                         VOS_VOID                     *pPara )
{

    MN_SETPARA_SendMsg(ClientId, OpId, Result, QueryType, pPara);

    return;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

