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
/*    1.日    期 : 2006-12-07
        作    者 : 韩鲁峰
        修改内容 : A32D07824 增加CGEQNEG的处理
      2.日    期 : 2007年9月26日
        作    者 : luojian id:107747
        修改内容 : 问题单号：A32D12931,查询API接口增加错误码上报
      3.日    期   : 2008年08月25日
        作    者   : f62575
        修改内容   : 问题单号：AT2D05096, AT查选命令，TAF下发到其它模块时，长度填写不正确
******************************************************************************/
#include "Taf_Common.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
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
/**********************************************************
 Function:       Taf_ParaSetResult
 Description:    TAF向APP发送通信参数设置结果
 Calls:          TAFM module
 Data Accessed:
 Data Updated:
 Input:          ClientId - 客户端标识
                 OpId - 操作标识
                 Result - 参数设置结果
 Output:
 Return:
 Others:
    1.2006-02-23 l47619     Modify 问题单:A32D02143
    2.日    期   : 2011年10月19日
      作    者   : f00179208
      修改内容   : AT移植项目,CallBack的清理
**********************************************************/
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

