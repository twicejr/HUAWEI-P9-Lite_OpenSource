/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SSA_Decode.c
  Author       : ---
  Version      : V200R001
  Date         : 2008-08-16
  Description  : 该C文件给出了TAFM模块中和SSA功能相关的函数的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-16
     Author: ---
     Modification:UE 1.5
  3. Date:2006-04-11
     Author: h44270
     Modification: 问题单号:A32D03053

  2.日    期   : 2006年4月5日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D01738
  4.日    期   : 2006年10月8日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D06583，修改SSA_TimeoutProc函数
  5.Date:2007-01-19
    Author: h44270
    Modification: 问题单号:A32D08448
  6.Date        : 2007-08-29
    Author      : h44270
    Modification: Create SSA_PowerOff for A32D12744
 7. 日    期   : 2010年05月07日
     作    者   : s62952
     修改内容   : 问题单号:A2D18963
************************************************************************/

#include "vos.h"
#include "Ps.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Common.h"
#include "Ssa_Define.h"
#include "Taf_Ssa_EncodeDef.h"
#include "SsDef.h"
#include "Taf_Tafm_Local.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
#include "PsNvId.h"
#include "NVIM_Interface.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
#include "TafSdcLib.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

#include "NasUsimmApi.h"
#include "NasComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_COMMON_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

SSA_TAG_STRU      gSsTagValue;

VOS_UINT8                  *gpucSsEncodeEndLocation;  /*字串结束位置*/
VOS_UINT8                   gucSsCurLen;              /*当前字串的长度*/
VOS_UINT8                   gucSsCurInvokeId;         /*当前所使用的Invoke ID的值*/
VOS_UINT8                  *gpucSsParaEndLocation;    /*当前Ss参数para部分的结束位置*/

/*SSA状态表*/
SSA_STATE_TABLE_STRU        gastSsaStatetable[TAF_MAX_SSA_TI + 1];

ST_SSP_IES_SSPVERSION       gstSsVersion;

VOS_UINT8                   gucCurrentTi;

VOS_UINT32                  gulCurStrMaxLen;                                /*当前字串的最大长度*/

/* USSD的传输模式, 默认值是透传模式 */
VOS_UINT16                  g_usTafSsaUssdTransMode   = AT_USSD_TRAN_MODE;

TAF_SSA_RETRY_CFG_STRU     g_stSsaRetryCfgInfo;

/*****************************************************************************
 函 数 名  : TAF_SSA_GetSsaRetryCfgInfo
 功能描述  : 新增函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : g_stSsaRetryCfgInfo的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SSA_RETRY_CFG_STRU* TAF_SSA_GetSsaRetryCfgInfo(VOS_VOID)
{
    return  &g_stSsaRetryCfgInfo;
}

/*lint -save -e958 */

/*******************************************************************************
Prototype       : SSA_Init()
Description     : 初始化SSA模块的所有全局变量
Input           : 无
Output          : 无
Calls           :
Called          :供TAFM模块调用。
Return          :无
History         : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
  2. 日    期   : 2010年05月07日
     作    者   : s62952
     修改内容   : 问题单号:A2D18963
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  5.日    期   : 2013年5月17日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:NVen_NV_Item_USSD_Apha_To_Ascii读取放到SDC中
  6.日    期   :2013年9月14日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
*******************************************************************************/
VOS_VOID  SSA_Init(VOS_VOID)
{

    VOS_UINT32                          ulIndex;

    /*对所有全局变量初始化*/
    PS_MEM_SET(&gSsTagValue, 0, sizeof(SSA_TAG_STRU));
    PS_MEM_SET(gastSsaStatetable, 0, (TAF_MAX_SSA_TI + 1)*sizeof(SSA_STATE_TABLE_STRU));

    for (ulIndex = 0; ulIndex < (TAF_MAX_SSA_TI + 1); ulIndex++)
    {
        TAF_SSA_InitAllTimers(gastSsaStatetable[ulIndex].astSsaTimerCtx);
    }

    TAF_SSA_ReadSsRetryCfgNvim();

    TAF_SSA_ReadSsRetryCmSrvRejCfgNvim();

    gucCurrentTi     = 0;
    gucSsCurInvokeId = 0;
    PS_MEM_SET(&gstSsVersion, 0, sizeof(ST_SSP_IES_SSPVERSION));



}

/*******************************************************************************
Prototype       : SSA_PowerOff()
Description     : 关闭计时器，初始化SSA模块的所有全局变量
Input           : 无
Output          : 无
Calls           :
Called          :供TAFM模块调用。
Return          :无
History         : ---
  1.Date        : 2007-08-29
    Author      : h44270
    Modification: Create function for A32D12744
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
*******************************************************************************/
VOS_VOID  SSA_PowerOff(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        TAF_SSA_StopAllTimer(i);
    }
    SSA_Init();

/* Modified by z40661 for DMT工程修改, 2013-2-01, begin */
#ifdef DMT
    Ss_TaskInit();
#endif
/* Modified by z40661 for DMT工程修改, 2013-2-01, end */

}

/*****************************************************************************
 Prototype      : SSA_PackMsgHeader
 Description    : 对COMPONENT中Parameter部分之外的头部进行封装(operationcode, InvokeId,
                  ComponetType)
 Input          : ucOperationcode -- 操作码, ucMsgType -- 消息类型,
                  ucTi -- 使用的Ti值
 Output         : *stFacility -- facility的内容
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_PackMsgHeader(ST_SSP_IES_FACILITY  *pstFacility, TAF_SS_OPERATION ucOperationcode,
                           TAF_SS_MSGTYPE ucMsgType, VOS_UINT8 ucTi, TAF_SS_ERROR usErrCode,
                           TAF_SS_REJECT ucProblemCode/*, TAF_SS_COMPONENTTYPE ucCmpNntType*/)
{
    VOS_UINT8               ucInvokeId;
    TAF_SS_COMPONENTTYPE    ucCmpNntType;

    /*获取INVOKE ID*/
    ucInvokeId = SSA_GetInvokeId(ucTi);

    /*如果是REGISTER类型,为INVOKE类型*/
    if (TAF_SS_MSG_TYPE_REGISTER == ucMsgType)
    {
        gastSsaStatetable[ucTi].ucInvokeId = ucInvokeId;
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_INVOKE;
    }
    /*否则暂时认为是return result类型,后续如果有其他的情况,再置成相应的类型*/
    else
    {
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_RTRNRSLT;
    }

    /*封装operation code*/
    if (VOS_NULL != ucOperationcode)
    {
        SSA_EncodeOperationCode(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucOperationcode);
        /*在密码操作和USSD操作时时，需要设定Sequence Tag*/
        if ((ucOperationcode == TAF_SS_GETPASSWORD) || (ucOperationcode == TAF_SS_USS_REQ))
        {
            SSA_EncodeSequenceTag(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt));
        }
    }
    /*有error code的时候,为retrun error类型,封装error code*/
    else if (VOS_NULL != usErrCode)
    {
        SSA_EncodeErrorCode(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), usErrCode);
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_RTRNERR;
    }
    /*有problem code的时候,为reject类型,封装*/
    else if (VOS_NULL != ucProblemCode)
    {
        SSA_EncodeProblemCode(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucProblemCode);
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_REJECT;
    }
    else
    {
        ;
    }


    /*头部封装INVOKE ID*/
    SSA_EncodeInvokeId(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucInvokeId);

    /*头部封装component type*/
    SSA_EncodeComponentType(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucCmpNntType);

    return SSA_SUCCESS;
}
/*****************************************************************************
 Prototype      : TAF_SSA_WaitNetworkRspTimerExpired
 Description    : SSA模块的超时处理，由定时器消息参数的不同，来区别定时器
 Input          : REL_TIMER_MSG
 Output         : 无
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
  2. 日    期   : 2006年10月8日
     作    者   : luojian id:60022475
     修改内容   : 问题单号:A32D06583，修改SSA_TimeoutProc函数
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  4.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能重命名
*****************************************************************************/
VOS_VOID TAF_SSA_WaitNetworkRspTimerExpired(VOS_UINT8 ucTi)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU      *pstSsEvent;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_TimeoutProc:ERROR: Alloc Mem Fail");
        return;
    }


    /*察看状态表中当前Ti的相关参数,确定Ti的参数是否有误*/
    if (SSA_IDLE == gastSsaStatetable[ucTi].ucState)
    {
        /*打印异常信息*/
        SSA_LOG(WARNING_PRINT, "SSA_TimeoutProc:WARNING: Timer out,but Ti not exist");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /*向网络侧发送Release Complete消息,并告知原因,与UE 1.5的超时
    处理类似, 向APP进行事件上报*/
    PS_MEM_SET(pstSsEvent, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    pstSsEvent->OP_Error = 1;
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, begin */
    pstSsEvent->ClientId = gastSsaStatetable[ucTi].ClientId;
    pstSsEvent->OpId = gastSsaStatetable[ucTi].OpId;

    /* 填写ErrorCode，如果当前有UE主动发起的连接，并且网络超时，ErrorCode需要填成特殊的原因值
        AT上报+CUSD: 5时会用到；其他情况下ErrorCode为TAF_ERR_TIME_OUT */
    if (TAF_SSA_USSD_MO_CONN_STATE == gastSsaStatetable[ucTi].ucUssdFlag)
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        pstSsEvent->ErrorCode = TAF_ERR_USSD_NET_TIMEOUT;
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    }
    else
    {
        pstSsEvent->ErrorCode = TAF_ERR_TIME_OUT;
    }

    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, end */

    TAF_SsEventReport(pstSsEvent);
    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);

    SSA_ReturnError(0, ucTi, TAF_SS_MSG_TYPE_RLCOMPLETE,SS_CAUSE_RECOVERY_TIMER_EXPIRY);
}

/*****************************************************************************
 函 数 名  : TAF_SSA_WaitAppRspTimerExpired
 功能描述  : TI_TAF_SSA_WAIT_APP_RSP_TIMER定时器超时的处理
 输入参数  : ucTi - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月15日
    作    者   : z001617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SSA_WaitAppRspTimerExpired(VOS_UINT8  ucTi)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU      *pstSsEvent;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "TAF_SSA_WaitAppRspTimerExpired:ERROR: Alloc Mem Fail");
        return;
    }


    /*察看状态表中当前Ti的相关参数,确定Ti的参数是否有误*/
    if (SSA_IDLE == gastSsaStatetable[ucTi].ucState)
    {
        /*打印异常信息*/
        SSA_LOG(WARNING_PRINT, "TAF_SSA_WaitAppRspTimerExpired:WARNING: Timer out,but Ti not exist");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /*向网络侧发送Release Complete消息,并告知原因,与UE 1.5的超时
    处理类似, 向APP进行事件上报*/
    PS_MEM_SET(pstSsEvent, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    pstSsEvent->OP_Error = 1;
    pstSsEvent->ClientId = gastSsaStatetable[ucTi].ClientId;
    pstSsEvent->OpId = gastSsaStatetable[ucTi].OpId;

    /* 填写ErrorCode，如果当前有UE主动发起的连接，并且网络超时，ErrorCode需要填成特殊的原因值
        AT上报+CUSD: 5时会用到；其他情况下ErrorCode为TAF_ERR_TIME_OUT */
    if (TAF_SSA_USSD_MT_CONN_STATE == gastSsaStatetable[ucTi].ucUssdFlag)
    {
        pstSsEvent->ErrorCode = TAF_ERR_USSD_USER_TIMEOUT;
    }
    else
    {
        pstSsEvent->ErrorCode = TAF_ERR_TIME_OUT;
    }


    TAF_SsEventReport(pstSsEvent);
    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);

    SSA_ReturnError(0, ucTi, TAF_SS_MSG_TYPE_RLCOMPLETE,SS_CAUSE_RECOVERY_TIMER_EXPIRY);
}



/*****************************************************************************
 Prototype      : SSA_CheckInvokeId
 Description    : 判断Invoke ID的值是否异常
 Input          : ucTi--Ti的值  ucInvokeId--Invoke Id的值
 Output         : 无
 Return Value   : 无
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_CheckInvokeId(VOS_UINT8 ucTi, VOS_UINT8  ucInvokeId)
{
    VOS_UINT32     i;

    /*如果当前Ti状态表已用,并且和之前的Invoke Id值相同,则返回失败*/
    for (i = 0; i < TAF_MAX_SSA_TI; i++)
    {
        if ((gastSsaStatetable[i].ucState == SSA_USED)
            &&(gastSsaStatetable[i].ucInvokeId == ucInvokeId))
        {
            return  SSA_FAILURE;
        }
    }
    return SSA_SUCCESS;

}


/*****************************************************************************
 Prototype      : SSA_GetInvokeId
 Description    : 获取当前可用的Invoke Id(Invoke Id是一种循环递增的方式,范围在0~255)
 Input          : ucTi--Ti的值
 Output         : 无
 Return Value   : Invoke Id的值
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT8 SSA_GetInvokeId(VOS_UINT8 ucTi)
{
    VOS_UINT32    ulTmp;

    /*查询当前Ti的状态表，如果表中的Ti项已经使用，则返回该项的Invoke ID值，如果
    没有，则挑选一个新的Invoke Id值(循环递增方式)*/
    if (gastSsaStatetable[ucTi].ucState == SSA_USED)
    {
        return gastSsaStatetable[ucTi].ucInvokeId;
    }
    else
    {
        gucSsCurInvokeId += 1;

        for (ulTmp = 0; ulTmp < TAF_MAX_SSA_TI; ulTmp ++)
        {
            if ((gastSsaStatetable[ulTmp].ucState == SSA_USED)
                &&(gastSsaStatetable[ulTmp].ucInvokeId == gucSsCurInvokeId))
            {
                gucSsCurInvokeId += 1;
                ulTmp = 0;
            }
        }

        return gucSsCurInvokeId;
    }
}


/*****************************************************************************
 Prototype      : SSA_GetPassWord
 Description    : 察看当前是否保存有该操作所需的密码
 Input          : *ucTi --  当前操作的Ti
 Output         : 无
 Return Value   : 查找结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_CheckPassWord(VOS_UINT8 ucTi)
{
    /*如果当前Ti状态表可用,并且密码有效*/
    if ((gastSsaStatetable[ucTi].ucState == SSA_USED)
        &&(gastSsaStatetable[ucTi].ucPwdFlag == SSA_PASSWORD_VALID))
    {
        return  SSA_SUCCESS;
    }

    return SSA_FAILURE;
}

/*****************************************************************************
 函 数 名  : SSA_CheckOperationCode
 功能描述  : 判断OperationCode的值是否异常,如果异常,进入异常处理
 输入参数  : VOS_UINT8 ucTi
             VOS_UINT8  ucOperationCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月15日
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2010年8月16日
    作    者   : 王毛/00166186
    修改内容   : DTS2010081702586 德国电信USSD PHASE1 兼容性问题
*****************************************************************************/
VOS_UINT32 SSA_CheckOperationCode(VOS_UINT8 ucTi, VOS_UINT8  ucOperationCode)
{
    switch (ucOperationCode)
    {
        case TAF_SS_REGISTERSS:
        case TAF_SS_ERASESS:
        case TAF_SS_ACTIVATESS:
        case TAF_SS_DEACTIVATESS:
        case TAF_SS_INTERROGATESS:
        case TAF_SS_PROCESS_USS_DATA:
        case TAF_SS_PROCESS_USS_REQ:
        case TAF_SS_USS_REQ:
        case TAF_SS_USS_NOTIFY:
        case TAF_SS_REGISTERPASSWORD:
        case TAF_SS_GETPASSWORD:
        case TAF_SS_ERASECC_ENTRY:
        /*case TAF_SS_FORWARDCHECKSS_INDICATION:*/
            return SSA_SUCCESS;
        default:
            return TAF_ERR_PARA_ERROR;
    }
}

/*****************************************************************************
 Prototype      : SSA_GetIdByTi
 Description    : 根据Ti值来获取ClientId和OpId
 Input          : ucTi    -   分配的Ti
 Output         : *pClientId -   APP/AT客户端标识
                  *pOpId       -   操作标识
 Return Value   : 操作结果
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_GetIdByTi(VOS_UINT16 *pClientId, VOS_UINT8 *pOpId, VOS_UINT8 ucTi)
{

    /*TI有效范围是0-6,8-14*/
    if ((ucTi > TAF_MAX_SSA_TI) || (ucTi == TAF_MIDDLE_SSA_TI))
    {
        return SSA_FAILURE;
    }

    /* 判断g_SsaStatetable[ucTi].ucState是否已经被使用*/
    if ( gastSsaStatetable[ucTi].ucState == SSA_USED)
    {
        *pClientId = gastSsaStatetable[ucTi].ClientId;
        *pOpId = gastSsaStatetable[ucTi].OpId;
        return SSA_SUCCESS;
    }

    return SSA_FAILURE;

}

/* Deleted by l00208543 for V9R1 STK升级, 2013-7-10, begin */
/* 删掉函数SSA_GetTi()，所有的调用使用TAF_SSA_GetUssdTi()替换 */
/* Deleted by l00208543 for V9R1 STK升级, 2013-7-10, end */

/* Added by l00208543 for V9R1 STK升级, 2013-07-10, begin */
/*****************************************************************************
 函 数 名  : TAF_SSA_GetUssdTi
 功能描述  : 根据ClientId和OpId获取相应的Ti
 输入参数  : 无
 输出参数  : pucTi    -   分配的Ti
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : l00208543
    修改内容   : V9R1 STK升级

*****************************************************************************/
VOS_UINT32 TAF_SSA_GetUssdTi(VOS_UINT8 *pucTi)
{
    VOS_UINT8                           i;

    /* TI有效范围是0-6,8-14 */
    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        /* index=7时跳过 */
        if (i != TAF_MIDDLE_SSA_TI)
        {
            if ( (SSA_USED == gastSsaStatetable[i].ucState)
              && ( (TAF_SSA_USSD_MO_CONN_STATE == gastSsaStatetable[i].ucUssdFlag)
                || (TAF_SSA_USSD_MT_CONN_STATE == gastSsaStatetable[i].ucUssdFlag) ) )
            {
                *pucTi = i;
                return SSA_SUCCESS;
            }
        }
     }

    /* 未找到匹配的 */
    return SSA_FAILURE;

}

/* Added by l00208543 for V9R1 STK升级, 2013-07-10, end */


/*****************************************************************************
 Prototype      : SSA_TiAlloc
 Description    : 根据ClientId和OpId分配Ti
 Input          : ClientId -   APP/AT客户端标识
                  OpId     -   操作标识
 Output         : pucTi    -   分配的Ti
 Return Value   : 操作结果
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
  2.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : V9R1_SVLTE
  3.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报CS域业务状态

*****************************************************************************/
VOS_UINT32 SSA_TiAlloc(VOS_UINT16 ClientId, VOS_UINT8 OpId, VOS_UINT8 *pucTi)
{
    VOS_UINT8     ucAllocTi = TAF_MIDDLE_SSA_TI;
    VOS_UINT32    i = 0;

    for (i = 0; i < TAF_MIDDLE_SSA_TI; i++)
    {
        /*MO时TI范围是0-6*/
        if (SSA_IDLE == gastSsaStatetable[i].ucState)
        {   /*有空闲TI*/
            ucAllocTi = (VOS_UINT8)i;
        }
        /*呼叫发起者是APP时，不允许相同ClientId，OpId同时发起两个操作*/
        else if ((gastSsaStatetable[i].ClientId == ClientId)
                  &&(gastSsaStatetable[i].OpId == OpId))
        {
            return SSA_FAILURE;   /*是否应该告知APP其发起操作的clientid和Opid的值有误*/
        }
        else
        {
            ;
        }
    }

    if (ucAllocTi < TAF_MIDDLE_SSA_TI)
    {
        /*TI分配成功*/
        gastSsaStatetable[ucAllocTi].ClientId = ClientId;
        gastSsaStatetable[ucAllocTi].OpId = OpId;
        gastSsaStatetable[ucAllocTi].ucState = SSA_USED;
        gastSsaStatetable[ucAllocTi].ucPwdFlag = SSA_PASSWORD_INVALID;
        *pucTi = ucAllocTi;

        /* TI分配成功之后，置一下CS域的SS业务是否存在的标志 */
        TAF_SDC_SetCsSsSrvExistFlg(VOS_TRUE);

        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */

        return SSA_SUCCESS;
    }
    else
    {
        /*没有空闲TI*/
        return SSA_FAILURE;
    }
}

/*****************************************************************************
 Prototype      : Taf_SsaTiFree
 Description    : Ssa模块释放Ti
 Input          : ucTi -- 分配的Ti
 Output         :
 Return Value   : 操作结果
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_TiIdle(VOS_VOID)
{
    VOS_UINT32  i;

    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        /*index=7时跳过*/
        if (i != TAF_MIDDLE_SSA_TI)
        {
            /*如果当前的ClientId和OpId与状态表中的CliendId、OpId相同则成功获取Ti,
            如果是由于之前广播上报的Ti,则替换原有的CliendId和OpId*/
            if (gastSsaStatetable[i].ucState == SSA_USED)
            {
                return SSA_USED;
            }
        }
    }

    return   SSA_IDLE;
}

/*****************************************************************************
 Prototype      : Ssa_TiFree
 Description    : Ssa模块释放Ti
 Input          : ucTi -- 分配的Ti
 Output         :
 Return Value   : 操作结果
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
  2.Date:2007-01-19
    Author: h44270
    Modification: 问题单号:A32D08448
  3.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : V9R1_SVLTE
  4.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报CS域业务状态
*****************************************************************************/
VOS_VOID SSA_TiFree(VOS_UINT8 ucTi)
{
    if ((ucTi > TAF_MAX_SSA_TI) || (ucTi == TAF_MIDDLE_SSA_TI))
    {
        SSA_LOG1(WARNING_PRINT, "SSA_TiFree:WARNING: Ti Value is Wrong, ucTi:", ucTi);
        return;
    }

    if (VOS_NULL_PTR != gastSsaStatetable[ucTi].pstUssdBuf)
    {
        PS_MEM_FREE(WUEPS_PID_SS, gastSsaStatetable[ucTi].pstUssdBuf);
        gastSsaStatetable[ucTi].pstUssdBuf = VOS_NULL_PTR;
    }

    PS_MEM_SET(&gastSsaStatetable[ucTi], 0, sizeof(SSA_STATE_TABLE_STRU));

    /* 当前Ti释放完了之后，判断一下是否所有的TI都释放了，
        如果所有的TI都释放了，置一下CS域的SS业务不存在的标志 */
    if (SSA_IDLE == SSA_TiIdle())
    {
        TAF_SDC_SetCsSsSrvExistFlg(VOS_FALSE);

        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */
    }

    return ;
}

/*****************************************************************************
 Prototype      : SSA_GetRepEvtFromOpCode
 Description    : 从OperationCode获得相对应得上报事件
 Input          : ucTi -- 分配的Ti
 Output         :
 Return Value   : 操作结果
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : 2005-12-13
    Author      : ---
    Modification: UE 1.5d function
  2. Date:2007-01-19
     Author: h44270
     Modification: 问题单号:A32D08448
*****************************************************************************/
VOS_UINT8 SSA_GetRepEvtFromOpCode(VOS_UINT8  ucOprationCode)
{
    switch (ucOprationCode)
    {
        case TAF_SS_REGISTERSS:
            return TAF_SS_EVT_REGISTERSS_CNF;

        case TAF_SS_ERASESS:
            return TAF_SS_EVT_ERASESS_CNF;

        case TAF_SS_ACTIVATESS:
            return TAF_SS_EVT_ACTIVATESS_CNF;

        case TAF_SS_DEACTIVATESS:
            return TAF_SS_EVT_DEACTIVATESS_CNF;

        case TAF_SS_INTERROGATESS:
            return TAF_SS_EVT_INTERROGATESS_CNF;

        case TAF_SS_PROCESS_USS_DATA:
            return TAF_SS_EVT_PROCESS_USS_REQ_CNF;

        case TAF_SS_PROCESS_USS_REQ:
            return TAF_SS_EVT_PROCESS_USS_REQ_CNF;

        case TAF_SS_USS_REQ:
            return TAF_SS_EVT_USS_REQ_IND;

        case TAF_SS_USS_NOTIFY:
            return TAF_SS_EVT_USS_NOTIFY_IND;

        case TAF_SS_REGISTERPASSWORD:
            return TAF_SS_EVT_REG_PASSWORD_CNF;

        case TAF_SS_GETPASSWORD:
            return TAF_SS_EVT_GET_PASSWORD_IND;

        case TAF_SS_ERASECC_ENTRY:
            return TAF_SS_EVT_ERASE_CC_ENTRY_CNF;

        /* case TAF_SS_FORWARDCHECKSS_INDICATION: */
        /* return TAF_SS_EVT_FORWARDCHECKSS_INDICATION; */

        default:
            return TAF_SS_EVT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : SSA_GetUssdMode
 功能描述  : 返回USSD透传模式设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月31日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  SSA_GetUssdTransMode(VOS_VOID)
{
    /* 若g_usTafSsaUssdTransMode非法，则返回AT_USSD_TRAN_MODE */
    if ((AT_USSD_NON_TRAN_MODE != g_usTafSsaUssdTransMode)
     && (AT_USSD_TRAN_MODE != g_usTafSsaUssdTransMode))
    {
        SSA_LOG(WARNING_PRINT, "SSA_GetUssdTransMode: usUssdTransMode is Abnormal!");

        return AT_USSD_TRAN_MODE;
    }

    /* g_usTafSsaUssdTransMode值合法 */
    return g_usTafSsaUssdTransMode;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, Begin */
/*****************************************************************************
 函 数 名  : TAF_SSA_UpdateUssdRptStatus
 功能描述  : 更新UUSD的主动上报状态
 输入参数  : usMsgType:消息类型 pMsg:AT下发的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新生成函数

*****************************************************************************/
VOS_VOID  TAF_SSA_UpdateUssdRptStatus(
    TAF_SS_PROCESS_USS_REQ_STRU        *pstSsReqMsg
)
{
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
    VOS_UINT32                               ulRptCmdStatus;

    ulRptCmdStatus  = VOS_TRUE;

    /* 更新CUSD对应的SDC全局变量 */
    if (TAF_SS_CUSD_TYPE_ENABLE == pstSsReqMsg->enCusdType)
    {
        ulRptCmdStatus = VOS_TRUE;
    }
    else
    {
        ulRptCmdStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, ulRptCmdStatus);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_IsUssdStateIdle
 功能描述  : 判断USSD是否处于IDLE态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:处于IDLE态；VOS_FALSE:不处于IDLE态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SSA_IsUssdStateIdle(VOS_VOID)
{
    VOS_UINT32  i;

    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        /*index=7时跳过*/
        if (i != TAF_MIDDLE_SSA_TI)
        {
            /*如果当前的ClientId和OpId与状态表中的CliendId、OpId相同则成功获取Ti,
            如果是由于之前广播上报的Ti,则替换原有的CliendId和OpId*/
            if ( (TAF_SSA_USSD_MO_CONN_STATE == gastSsaStatetable[i].ucUssdFlag)
              || (TAF_SSA_USSD_MT_CONN_STATE == gastSsaStatetable[i].ucUssdFlag) )
            {
                return VOS_FALSE;
            }
        }
    }

    return   VOS_TRUE;
}
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, End */

/*****************************************************************************
 函 数 名  : TAF_SSA_GetSsRetrySupportFlg
 功能描述  : 获取是否支持ss重发功能标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 支持ss重发功能
             VOS_FALSE - 不支持ss重发功能
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SSA_GetSsRetrySupportFlg(VOS_VOID)
{
    return g_stSsaRetryCfgInfo.ucIsSsRetrySupportFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_SetSsRetrySupportFlg
 功能描述  : 设置是否支持ss重发功能标识
 输入参数  : ucIsSsRetrySupportFlg - 是否支持ss重发功能
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_SetSsRetrySupportFlg(VOS_UINT8 ucIsSsRetrySupportFlg)
{
    g_stSsaRetryCfgInfo.ucIsSsRetrySupportFlg = ucIsSsRetrySupportFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_GetSsRetryIntervalTimerLen
 功能描述  : 获取ss重发间隔定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SSA_GetSsRetryIntervalTimerLen(VOS_VOID)
{
    return g_stSsaRetryCfgInfo.ulSsRetryInterval;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_SetSsRetryIntervalTimerLen
 功能描述  : 设置ss重发间隔定时器的时长
 输入参数  : ulSsRetryInterval - 定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_SetSsRetryIntervalTimerLen(VOS_UINT32 ulSsRetryInterval)
{
    g_stSsaRetryCfgInfo.ulSsRetryInterval = ulSsRetryInterval;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_GetSsRetryPeriodTimerLen
 功能描述  : 获取ss重发最大时长定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SSA_GetSsRetryPeriodTimerLen(VOS_VOID)
{
    return g_stSsaRetryCfgInfo.ulSsRetryPeriod;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_SetSsRetryPeriodTimerLen
 功能描述  : 设置ss重发尝试最大时间定时器的时长
 输入参数  : ulSsRetryPeriod - 定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_SetSsRetryPeriodTimerLen(VOS_UINT32 ulSsRetryPeriod)
{
    g_stSsaRetryCfgInfo.ulSsRetryPeriod = ulSsRetryPeriod;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_ReadSsRetryCfgNvim
 功能描述  : 获取NVIM中的en_NV_Item_SS_Retry_CFG的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月10日
    作    者   : z00161729
    修改内容   : 支持ss重发新增nv项
*****************************************************************************/
VOS_VOID  TAF_SSA_ReadSsRetryCfgNvim( VOS_VOID )
{
    TAF_SSA_NVIM_RETRY_CFG_STRU         stSsaRetryCfg;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    /* GCF测试,ss重发功能需要关闭 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

        return;
    }

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_SS_Retry_CFG, &ulLength);

    PS_MEM_SET(&stSsaRetryCfg, 0x0, sizeof(TAF_SSA_NVIM_RETRY_CFG_STRU));

    if (ulLength > sizeof(TAF_SSA_NVIM_RETRY_CFG_STRU))
    {
        MN_WARN_LOG("TAF_SS_ReadSsaRetryCfgNvim():WARNING: en_NV_Item_SS_Retry_CFG length Error");

        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

        return;
    }

    /* 如果NV读取失败，则设置为不开启 */
    if (NV_OK != NV_Read(en_NV_Item_SS_Retry_CFG,
                         &stSsaRetryCfg, ulLength))
    {
        MN_WARN_LOG("TAF_SS_ReadSsaRetryCfgNvim():WARNING: en_NV_Item_SS_Retry_CFG Error");
        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

        return;
    }

    if (VOS_TRUE == stSsaRetryCfg.ucIsSsRetrySupportFlg)
    {
        TAF_SSA_SetSsRetrySupportFlg(VOS_TRUE);

        /* nv中存的时长为秒，需要转换为毫秒 */
        TAF_SSA_SetSsRetryPeriodTimerLen(TAF_SSA_ONE_THOUSAND_MILLISECOND * stSsaRetryCfg.ulSsRetryPeriod);
        TAF_SSA_SetSsRetryIntervalTimerLen(TAF_SSA_ONE_THOUSAND_MILLISECOND * stSsaRetryCfg.ulSsRetryInterval);
    }
    else
    {
        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_ReadSsRetryCmSrvRejCfgNvim
 功能描述  : 获取NVIM中的en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00355355
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SSA_ReadSsRetryCmSrvRejCfgNvim( VOS_VOID )
{
    TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU      stSsRetryCmSrvRejCfg;
    VOS_UINT32                                  ulLength;

    ulLength = 0;

    /* GCF测试,ss重发功能需要关闭 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = 0;
        return;
    }

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG, &ulLength);

    PS_MEM_SET(&stSsRetryCmSrvRejCfg, 0x0, sizeof(TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU));

    if (ulLength > sizeof(TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU))
    {
        MN_WARN_LOG("TAF_SSA_ReadSsRetryCmSrvRejCfgNvim():WARNING: en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG length Error");

        g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = 0;
        return;
    }

    /* 如果NV读取失败，则设置为不开启 */
    if (NV_OK != NV_Read(en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG,
                         &stSsRetryCmSrvRejCfg, ulLength))
    {
        MN_WARN_LOG("TAF_SSA_ReadSsRetryCmSrvRejCfgNvim():WARNING: en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG Error");
        g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = 0;
        return;
    }

    if (stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum > TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM)
    {
        stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum = TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM;
    }

    g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum;
    PS_MEM_CPY(g_stSsaRetryCfgInfo.aucSsRetryCmSrvRejCause,
               stSsRetryCmSrvRejCfg.aucSsRetryCmSrvRejCause,
               stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum);
    return;
}


/*****************************************************************************
 函 数 名  : TAF_SSA_ClearBufferedMsg
 功能描述  : 清空缓存的消息
 输入参数  : ucTi - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_ClearBufferedMsg(VOS_UINT8 ucTi)
{
    PS_MEM_SET(&gastSsaStatetable[ucTi].stSsaBufferedMsg, 0x0, sizeof(TAF_SSA_MSG_BUFF_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_GetBufferedMsg
 功能描述  : 获取对应ti缓存的消息
 输入参数  : ucTi - transaction id
 输出参数  : 无
 返 回 值  : 获取对应ti缓存的消息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SSA_MSG_BUFF_STRU*  TAF_SSA_GetBufferedMsg( VOS_UINT8 ucTi )
{
    return &(gastSsaStatetable[ucTi].stSsaBufferedMsg);
}

/*****************************************************************************
 函 数 名  : TAF_SSA_GetTimerRemainLen
 功能描述  : 获取定时器剩余的时间
 输入参数  : enTimerId - 定时器id
             ucTi      - transaction id
 输出参数  : 无
 返 回 值  : 定时器剩余时长,单位:毫秒
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月10日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SSA_GetTimerRemainLen(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    VOS_UINT32                          ulTick;
    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    ulTick         = 0;

    /*TI有效范围是0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_GetTimerRemainLen: Ti invalid!");
        return ulTick;
    }

    pstSsaTimerCtx = gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_SSA_TIMER_STATUS_RUNING  == pstSsaTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstSsaTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if (i >= TAF_SSA_MAX_TIMER_NUM)
    {
        /* 不存在说明此定时器已超时或停止 */
        ulTick = 0;
        return ulTick;
    }

    /* 句柄为空时，说明此定时器已超时或停止 */
    if (VOS_NULL_PTR != pstSsaTimerCtx[i].hTimer)
    {
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstSsaTimerCtx[i].hTimer), &ulTick))
        {
            ulTick = 0;
        }
    }

    /* tick值乘以10转换为毫秒 */
    return ulTick * TAF_SSA_TIMER_TICK;
}


/*****************************************************************************
 函 数 名  : TAF_SSA_GetTimerStatus
 功能描述  : 查询指定的ssa定时器的状态
 输入参数  : enTimerId  - 需要查询的定时器ID
             ucTi       - transation id
 输出参数  : 无
 返 回 值  : 定时器状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月10日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SSA_TIMER_STATUS_ENUM_UINT8  TAF_SSA_GetTimerStatus(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /*TI有效范围是0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_GetTimerStatus: Ti invalid!");
        return TAF_SSA_TIMER_STATUS_STOP;
    }

    pstSsaTimerCtx = gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_SSA_TIMER_STATUS_RUNING  == pstSsaTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstSsaTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_SSA_MAX_TIMER_NUM)
    {
        return TAF_SSA_TIMER_STATUS_STOP;
    }

    return TAF_SSA_TIMER_STATUS_RUNING;

}


/*****************************************************************************
 函 数 名  : TAF_SSA_StartTimer
 功能描述  : 启动指定的SSA定时器
 输入参数  : enTimerId - 需要启动的定时器ID
             ulLen     - 定时器时长
             ucTi      - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月10日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_SSA_StartTimer(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucTi
)
{
    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;
    NAS_TIMER_OPERATION_STRU            stTimer;

    /*TI有效范围是0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StopTimer: Ti invalid!");
        return VOS_FALSE;
    }

    pstSsaTimerCtx   =  gastSsaStatetable[ucTi].astSsaTimerCtx;

    if (0 == ulLen)
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StartTimer: timer len is zero!");
        return VOS_FALSE;
    }

    /* 如果该定时器已经启动则直接返回 */
    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_SSA_TIMER_STATUS_RUNING == pstSsaTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstSsaTimerCtx[i].enTimerId))
        {
            SSA_LOG1(WARNING_PRINT, "TAF_SSA_StartTimer:timer is running", enTimerId);
            return VOS_FALSE;
        }
    }

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_SSA_TIMER_STATUS_STOP == pstSsaTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if ( i >= TAF_SSA_MAX_TIMER_NUM)
    {
        SSA_LOG1(WARNING_PRINT, "TAF_SSA_StartTimer:too many timer", enTimerId);

        return VOS_FALSE;
    }

    if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulPrecision = NAS_GetTimerPrecision(WUEPS_PID_SS, enTimerId);

    ulRet = VOS_StartRelTimer(&(pstSsaTimerCtx[i].hTimer),
                              WUEPS_PID_SS,
                              ulLen,
                              enTimerId,
                              ucTi,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);

    if ( VOS_OK != ulRet)
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StartTimer: start timer failed!");

        return VOS_FALSE;
    }

    pstSsaTimerCtx[i].enTimerId     = enTimerId;
    pstSsaTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_RUNING;


    /* 定时器状态勾包出来 */
    stTimer.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulSenderPid      = WUEPS_PID_SS;
    stTimer.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulReceiverPid    = VOS_PID_TIMER;
    stTimer.MsgHeader.ulLength         = sizeof(NAS_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;
    stTimer.MsgHeader.ulMsgName        = enTimerId;
    stTimer.ulTimeAction               = NAS_TIMER_OPERATION_START;
    stTimer.ulTimeLen                  = ulLen;

    DIAG_TraceReport(&stTimer);

    NAS_TIMER_EventReport(stTimer.MsgHeader.ulMsgName, WUEPS_PID_SS, NAS_OM_EVENT_TIMER_OPERATION_START);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_StopTimer
 功能描述  : 停止指定的SSA定时器
 输入参数  : enTimerId - 需要停止的定时器ID
             ucTi      - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月10日
    作    者   : z001617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SSA_StopTimer(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    TAF_SSA_TIMER_CXT_STRU             *pstSsTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /*TI有效范围是0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StopTimer: Ti invalid!");
        return;
    }

    pstSsTimerCtx = gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( (TAF_SSA_TIMER_STATUS_RUNING  == pstSsTimerCtx[i].enTimerStatus )
          && (enTimerId                    == pstSsTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_SSA_MAX_TIMER_NUM)
    {
        SSA_LOG1(WARNING_PRINT, "TAF_SSA_StopTimer:too many timer", enTimerId);
        return;
    }

    /* 停止VOS定时器: 当定时器的指针已经为空的时候, 说明其已经停止或者超时 */
    if (VOS_NULL_PTR != pstSsTimerCtx[i].hTimer)
    {
        (VOS_VOID)NAS_StopRelTimer(WUEPS_PID_SS, enTimerId, &pstSsTimerCtx[i].hTimer);
    }

    pstSsTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstSsTimerCtx[i].enTimerId     = TI_TAF_SSA_TIMER_BUTT;
    pstSsTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_STOP;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_StopAllTimer
 功能描述  : 停止对应ti SSA的所有定时器
 输入参数  : ucTi - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月10日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SSA_StopAllTimer(VOS_UINT8 ucTi)
{

    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /*TI有效范围是0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StopTimer: Ti invalid!");
        return;
    }

    pstSsaTimerCtx =  gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_SSA_TIMER_STATUS_RUNING  == pstSsaTimerCtx[i].enTimerStatus )
        {
            TAF_SSA_StopTimer(pstSsaTimerCtx[i].enTimerId, ucTi);

            pstSsaTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstSsaTimerCtx[i].enTimerId     = TI_TAF_SSA_TIMER_BUTT;
            pstSsaTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_STOP;
        }
    }
}


/*****************************************************************************
 函 数 名  : TAF_SSA_RetryPeriodTimerExpired
 功能描述  : TI_TAF_SSA_RETRY_PERIOD_TIMER定时器超时处理
 输入参数  : ucTi - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月12日
    作    者   : z001617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SSA_RetryPeriodTimerExpired(VOS_UINT8 ucTi)
{
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_RetryIntervalTimerExpired
 功能描述  : TI_TAF_SSA_RETRY_INTERVAL_TIMER定时器超时处理
 输入参数  : ucTi - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月12日
    作    者   : z001617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SSA_RetryIntervalTimerExpired(VOS_UINT8 ucTi)
{
    TAF_SSA_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg  = TAF_SSA_GetBufferedMsg(ucTi);


    if (TAF_SSA_STATE_CONN_PENDING != gastSsaStatetable[ucTi].enSsaState)
    {
        SSA_LOG(INFO_PRINT, "TAF_SSA_RetryIntervalTimerExpired: ssa state is invalid.");
        TAF_SSA_ClearBufferedMsg(ucTi);
        TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi);
        return;
    }

    /* 取缓存消息 */
    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedBeginReqMsg)
    {
        Taf_SSA_ProcBufferedBeginReqMsg(&pstBufferdMsg->stBufferedBeginReqMsg);
        return;
    }

    SSA_LOG(INFO_PRINT, "TAF_SSA_RetryIntervalTimerExpired: buffered begin req msg is null!");
    TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi);

    return;

}


/*****************************************************************************
 函 数 名  : TAF_SSA_RcvTimerExpired
 功能描述  : SSA定时器超时
 输入参数  : enTimerId - 超时的定时器ID
             ucTi      - transaction id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月12日
    作    者   : z001617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SSA_RcvTimerExpired(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    /*TI有效范围是0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_RcvTimerExpired: Ti invalid!");
        return;
    }

    TAF_SSA_StopTimer(enTimerId, ucTi);

    switch (enTimerId)
    {
        case TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER:
            TAF_SSA_WaitNetworkRspTimerExpired(ucTi);
            break;

        case TI_TAF_SSA_WAIT_APP_RSP_TIMER:
            TAF_SSA_WaitAppRspTimerExpired(ucTi);
            break;

        case TI_TAF_SSA_RETRY_PERIOD_TIMER:
            /*lint -e522*/
            TAF_SSA_RetryPeriodTimerExpired(ucTi);
            /*lint +e522*/
            break;

        case TI_TAF_SSA_RETRY_INTERVAL_TIMER:
            TAF_SSA_RetryIntervalTimerExpired(ucTi);
            break;

        default:
            SSA_LOG(WARNING_PRINT, "TAF_SSA_RcvTimerExpired: timer id is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_InitAllTimers
 功能描述  : 初始化ssa定时器
 输入参数  : pstSsaTimerCtx - 定时器信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月15日
    作    者   : z001617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SSA_InitAllTimers(
    TAF_SSA_TIMER_CXT_STRU              *pstSsaTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        pstSsaTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstSsaTimerCtx[i].enTimerId     = TI_TAF_SSA_TIMER_BUTT;
        pstSsaTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_STOP;
    }
}

/*****************************************************************************
 函 数 名  : TAF_SSA_IsTiValid
 功能描述  : 判断ti是否合法
 输入参数  : ucTi - Transaction id
 输出参数  : 无
 返 回 值  : VOS_TRUE:ti合法
             VOS_FALSE: ti非法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月15日
    作    者   : z001617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SSA_IsTiValid(
    VOS_UINT8                           ucTi
)
{
    /*TI有效范围是0-6,8-14*/
    if ((ucTi > TAF_MAX_SSA_TI)
     || (TAF_MIDDLE_SSA_TI == ucTi))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
