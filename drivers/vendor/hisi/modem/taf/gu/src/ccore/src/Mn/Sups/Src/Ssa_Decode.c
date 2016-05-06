/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SSA_Decode.c
  Author       : ---
  Version      : V200R001
  Date         : 2008-08-16
  Description  : 该C文件给出了SSA模块解码函数的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-16
     Author: ---
     Modification:Create
  2. Date:2006-03-28
     Author: h44270
     Modification: 问题单号:A32D02754
  3. Date:2006-04-11
     Author: h44270
     Modification: 问题单号:A32D02951
  4.日    期   : 2006年4月4日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D01738
  5.日    期   : 2006年11月14日
    作    者   : DingQing 49431
    修改内容   : 问题单号:A32D07201
  6. Date:2007-01-19
     Author: h44270
     Modification: 问题单号:A32D08448
  7.Date:2007-04-29
    Author: Li Jilin 60827
    Modification: 问题单号:A32D10708
  8.日    期   : 2009年09月05日
    作    者   : h44270
    修改内容   : 问题单号:AT2D05342
  9.日    期   : 2010年02月25日
    作    者   : s62952
    修改内容  : 问题单号:AT2D17545 波兰USSD网络兼容问题
 10.日    期   : 2010年03月01日
    作    者   : h44270
    修改内容  : 问题单号:AT2D17545 波兰USSD网络兼容问题
 11. 日    期   : 2010年05月07日
     作    者   : s62952
     修改内容   : 问题单号:A2D18963
************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Ps.h"

#include "Taf_Common.h"
#include "Taf_Ssa_DecodeDef.h"
#include "TafAppSsa.h"
#include "MnErrorCode.h"
#include "NasComm.h"
#include "TafSdcCtx.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_DECODE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/



/*lint -save -e958 */

/******************************************************************************
 Prototype      : SSA_DecodeComponent
 Description    : 解码component type，进行分类处理
 Input          : *pEvent - 上报给APP的参数
                  *pucSrc   - 接收到的字串
 Output         : 无
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*******************************************************************************/
VOS_UINT32 SSA_DecodeComponent(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 *pucSrc)
{
    VOS_UINT32      ulRslt = SSA_SUCCESS;

    /*根据component type类型，进行相应解码，类型:INVOKE, return result, return error, reject*/
    /*将component type 存入状态表中*/
    /* pEvent->ComponentType = *pucSrc; */
    gastSsaStatetable[gucCurrentTi].uComponenttype = *pucSrc;

    switch (*pucSrc)
    {
        case TAF_SS_COMPONENT_TYPE_INVOKE:
            ulRslt = SSA_DecodeInvoke(pEvent, &pucSrc);
            break;

        case TAF_SS_COMPONENT_TYPE_RTRNRSLT:
            ulRslt = SSA_DecodeRtrnRslt(pEvent, &pucSrc);
            break;

        case TAF_SS_COMPONENT_TYPE_RTRNERR:
            ulRslt = SSA_DecodeRtrnErr(pEvent, &pucSrc);
            break;

        case TAF_SS_COMPONENT_TYPE_REJECT:
            ulRslt = SSA_DecodeReject(pEvent, &pucSrc);
            break;

        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeComponent:WARNING: Component Type Unrecognized");
            return TAF_SS_REJ_UNRECOGNIZED_COMPONENT;
    }

    return ulRslt;
}

/******************************************************************************
 Prototype      : SSA_DecodeInvoke
 Description    : 解码component type中的Invoke类型
 Input          : *pEvent - 上报给APP的参数
                  **ppucSrc   - 接收到的字串
 Output         : 无
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理

*******************************************************************************/
VOS_UINT32 SSA_DecodeInvoke(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       ucOperationCode;
    /* VOS_UINT8      *pucEndLocation; */
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8       ucTmpLen;

    /* 跳过tag字节 */
    (*ppucSrc)++;

    /*获取component长度, TLV格式，同时指针移位至V，确定结束位置*/
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    ulRslt = SSA_DecodeLength(ppucSrc, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Length Value Error");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    gpucSsParaEndLocation = *ppucSrc + ucTmpLen;

    /*检查INVOKE ID*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        #if 0
        /*检查INVOKE ID的合理性，相应处理,如果有重复的，报错，否则记录下来*/
        if (SSA_SUCCESS != SSA_CheckInvokeId(gucCurrentTi, *(*ppucSrc + 2)))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Invoke Id Wrong");
            return TAF_SS_REJ_DUPLICATE_INVOKE_ID;
        }
        #endif

        gastSsaStatetable[gucCurrentTi].ucInvokeId = *(*ppucSrc + 2);
        gucSsCurInvokeId = *(*ppucSrc + 2);

        *ppucSrc = *ppucSrc + 3;

    }
    else
    {
        /*缺少Invoke Id,返回信息给网络侧*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_INVALID_MANDATORY_IE;
    }

    /*查看是否有LINKED_ID*/
    if (LINKED_ID_TAG == **ppucSrc)
    {
        /*对LINKED_ID_TAG做相应的处理*/
        gastSsaStatetable[gucCurrentTi].ucLinkId = *(*ppucSrc + 2);
        *ppucSrc = *ppucSrc + 3;

    }

    /*查看操作码*/
   ucOperationCode = *(*ppucSrc + 2);
    if (OPERATION_CODE_TAG == **ppucSrc)
    {
        /*如果当前operation code值正确*/
        if (SSA_SUCCESS == SSA_CheckOperationCode(gucCurrentTi, ucOperationCode))
        {
            /*记录operationcode,并转换成相应的上报事件*/
            if (TAF_SS_MSG_TYPE_REGISTER == gastSsaStatetable[gucCurrentTi].ucMsgType)
            {
                gastSsaStatetable[gucCurrentTi].ucOperationCode = ucOperationCode;
            }
            pEvent->SsEvent = SSA_GetRepEvtFromOpCode(ucOperationCode);
            if (TAF_SS_EVT_ERROR == pEvent->SsEvent)
            {
                /*如果返回值为SSA_FAILURE，说明操作码有误，返回*/
                return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
            }

            *ppucSrc = *ppucSrc + 3;
        }
        else
        {
            /*操作类型有误,返回信息给网络侧*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Operation Unrecognized");
            return  TAF_SS_REJ_UNRECOGNIZED_OPERATION;
        }
    }
    else
    {
        /*缺少operation code，返回信息给网络侧*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Operation Id not exist");
        return TAF_SS_REJ_INVALID_MANDATORY_IE;
    }

    /*根据操作码，如果有component参数，做相应的解码处理*/
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        switch(ucOperationCode)
        {
            case TAF_SS_USS_REQ:
                /*对当前状态进行判断,是否可以进行USSD操作(是否出于通话状态,是否有其他的补充业务
                操作)*/
                if ((SSA_IDLE == SSA_TiIdle())||(gastSsaStatetable[gucCurrentTi].ucMsgType == TAF_SS_MSG_TYPE_FACILITY))
                {
                    ulRslt = SSA_DecodeUntructuredSSInd(pEvent, ppucSrc);
                }
                else
                {
                    SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: USS_REQ Busy");
                    return TAF_ERR_SS_USSD_BUSY;
                }
                break;
            case TAF_SS_USS_NOTIFY:
                /*对当前状态进行判断,是否可以进行USSD操作*/
                if ((SSA_IDLE == SSA_TiIdle())||(gastSsaStatetable[gucCurrentTi].ucMsgType == TAF_SS_MSG_TYPE_FACILITY))
                {
                    ulRslt = SSA_DecodeUntructuredSSNotifyInd(pEvent, ppucSrc);
                }
                else
                {
                    SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: USS_NOTIFY Busy");
                    return TAF_ERR_SS_USSD_BUSY;
                }
                break;
            case TAF_SS_GETPASSWORD:
                ulRslt = SSA_DecodeGetPwdInd(pEvent, ppucSrc);
                break;
            #if 0
            case TAF_SS_FORWARDCHECKSS_INDICATION:
                /*无内容,不做处理，记录上报的信息*/
                break;
            #endif
            default:
                SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Wrong Operation Code");
                return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
    }

   /* if ((*pucSrc != pucEndLocation)&&(SSA_SUCCESS == ulRslt)) */
   /* { */
   /*     SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke: BADLY_STRUCTURED_COMPONENT"); */
   /*     return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT; */
   /* } */
    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeRtrnRslt
 功能描述  : 解码SS的网测回复
 输入参数  : TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent
             VOS_UINT8 **ppucSrc
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月15日
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2010年7月31日
    作    者   : 王毛/00166186
    修改内容   : DTS2010081702586 德国电信USSD PHASE1 兼容性问题
  3.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 SSA_DecodeRtrnRslt(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       ucOperationCode;
    /* VOS_UINT8      *pucEndLocation; */
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8       ucTmpLen;

    /* 跳过tag字节 */
    (*ppucSrc)++;

    /*获取component长度, TLV格式，同时指针移位至V，确定结束位置*/
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    ulRslt = SSA_DecodeLength(ppucSrc, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Length Value Error");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    gpucSsParaEndLocation = *ppucSrc + ucTmpLen;

    /*检查参数INVOKE ID*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        /*更新Invoke Id的值*/
        if ((gucSsCurInvokeId < 255)&&(gucSsCurInvokeId <*(*ppucSrc + 2)))
        {
           gucSsCurInvokeId = *(*ppucSrc + 2);
           gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else if ((gucSsCurInvokeId == 255) && (0 == *(*ppucSrc + 2)))
        {
            gucSsCurInvokeId = 0;
            gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else
        {
            ;
        }

        *ppucSrc = *ppucSrc + 3;
    }
    else
    {
        if (gastSsaStatetable[gucCurrentTi].ucMsgType != TAF_SS_MSG_TYPE_RLCOMPLETE)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Invoke Id not exist");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
        }
    }

    /*判断是否有参数Sequence Tag,目前处理是跳过*/
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        if ((TAG_SS_OF_SEQUENCE == **ppucSrc)||(TAG_SS_OF_SET == **ppucSrc))
        {

            /* 跳过tag字节 */
            (*ppucSrc)++;

            /*获取component长度, TLV格式，同时指针移位至V，确定结束位置*/
            /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
            ulRslt = SSA_DecodeLength(ppucSrc, &ucTmpLen);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Length Value Error");
            }
            /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
        }
    }

    /*判断是否有参数operation code,有的话做记录,没有跳过(可选项)*/
    ucOperationCode = *(*ppucSrc + 2);
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        if (OPERATION_CODE_TAG == **ppucSrc)
        {
            /*如果当前operation code值正确,记录operationcode,转换成相应的上报事件,偏移*/
            if (SSA_SUCCESS == SSA_CheckOperationCode(gucCurrentTi, ucOperationCode))
            {
                gastSsaStatetable[gucCurrentTi].ucOperationCode = ucOperationCode;
                pEvent->SsEvent = SSA_GetRepEvtFromOpCode(ucOperationCode);
                #if 0
                if (TAF_SS_EVT_ERROR == pEvent->SsEvent)
                {
                    /*如果返回值为SSA_FAILURE，说明操作码有误，返回*/
                    return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
                }
                #endif

                *ppucSrc = *ppucSrc + 3;
            }
            else
            {
                /*操作类型有误,输出打印信息,返回*/
                SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Operation Unrecognized");
                return  TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
            }
        }
    }
    else
    {
        pEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
        pEvent->OpId = gastSsaStatetable[gucCurrentTi].OpId;
        pEvent->ClientId = gastSsaStatetable[gucCurrentTi].ClientId;
        return SSA_SUCCESS;
    }

    /*根据operation code,如果有component参数，做相应的操作的解码*/
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        pEvent->OP_UnParsePara = 1;
        pEvent->UnParsePara.ucCnt = (VOS_UINT8)(gpucSsParaEndLocation - *ppucSrc);
        PS_MEM_CPY(pEvent->UnParsePara.aucUnParsePara, *ppucSrc, pEvent->UnParsePara.ucCnt);
        switch(ucOperationCode)
        {
            case TAF_SS_REGISTERSS:
                ulRslt = SSA_DecodeRegisterSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_ERASESS:
                ulRslt = SSA_DecodeEraseSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_ACTIVATESS:
                ulRslt = SSA_DecodeActivateSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_DEACTIVATESS:
                ulRslt = SSA_DecodeDeactivateSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_INTERROGATESS:
                ulRslt = SSA_DecodeInterrogateSsCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_PROCESS_USS_REQ:
                ulRslt = SSA_DecodeProcessUnstructuredSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_REGISTERPASSWORD:
                ulRslt = SSA_DecodeRegPwdCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_ERASECC_ENTRY:
                ulRslt = SSA_DecodeEraseCCEntryCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_PROCESS_USS_DATA:
                ulRslt = SSA_DecodeProcessUSSDataCnf(pEvent, ppucSrc);
                break;
            default:
                SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Wrong Operation Code");
                return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
        }
    }

/*    if (*ppucSrc != gpucSsParaEndLocation) */
/*    { */
/*        SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: BADLY_STRUCTURED_COMPONENT"); */
/*        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT; */
/*    } */

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeRtrnErr
 Description    : 解码component type中的Return Error类型
 Input          : *pEvent - 上报给APP的参数
                  *ppucSrc   - 接收到的字串
 Output         : 无
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function

  2.日    期   : 2013年01月18日
    作    者   : l00198894
    修改内容   : DTS2013011803106: 增加SS业务错误码
****************************************************************************/
VOS_UINT32 SSA_DecodeRtrnErr(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT16       usErrCode;

    *ppucSrc = *ppucSrc + 2;

    /*检查参数INVOKE Id是否合理*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        /*更新Invoke Id的值*/
        if ((gucSsCurInvokeId < 255)&&(gucSsCurInvokeId <*(*ppucSrc + 2)))
        {
           gucSsCurInvokeId = *(*ppucSrc + 2);
           gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else if ((gucSsCurInvokeId == 255) && (0 == *(*ppucSrc + 2)))
        {
            gucSsCurInvokeId = 0;
            gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else
        {
            ;
        }
        *ppucSrc = *ppucSrc + 3;

    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnErr:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_RETURN_ERROR_MISTYPED_PARAMETER;
    }

    /*检查参数error code是否存在,存在的话进行记录,当前的错误码均已经加上了偏移量*/
    usErrCode = *(*ppucSrc + 2) + TAF_SS_ERRCODE_OFFSET;
    if (ERROR_CODE_TAG == **ppucSrc)
    {
        /*记录error code及对应操作的上报事件*/
        pEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
        pEvent->OP_Error = SSA_FIELD_EXIST;
        pEvent->ErrorCode = usErrCode;
        *ppucSrc = *ppucSrc + 3;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnErr:WARNING: Error Code not exist");
        return TAF_SS_REJ_RETURN_ERROR_MISTYPED_PARAMETER;
    }

    /* 解码SS Status，并填入Event */
    if (OCTETSTRING_TAG == **ppucSrc)
    {
        pEvent->OP_SsStatus = SSA_FIELD_EXIST;

        /* 偏移到TAG后面 */
        (*ppucSrc)++;

        /* 偏移到Length后面 */
        (*ppucSrc)++;

        pEvent->SsStatus    = **ppucSrc;
    }

    return SSA_SUCCESS;

}

/****************************************************************************
 Prototype      : SSA_DecodeReject
 Description    : 解码component type中的Reject类型
 Input          : *pEvent - 上报给APP的参数
                  *ppucSrc   - 接收到的字串
 Output         : 无
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.Date:2007-01-19
    Author: h44270
    Modification: 问题单号:A32D08448
  3.日    期   : 2014年5月30日
    作    者   : j00174725
    修改内容   : TQE
****************************************************************************/
VOS_UINT32 SSA_DecodeReject(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8         ucTmpLen;
    VOS_UINT8         ucProblemCode;
    VOS_UINT8         ucProblemTag;
    /* VOS_UINT8      *pucEndLocation; */

    /* pucEndLocation = *ppucSrc + *(*ppucSrc + 1); */
    *ppucSrc = *ppucSrc + 2;

    /*检查参数INVOKE ID是否合理*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        /*更新Invoke Id的值*/
        if ((gucSsCurInvokeId < 255)&&(gucSsCurInvokeId <*(*ppucSrc + 2)))
        {
           gucSsCurInvokeId = *(*ppucSrc + 2);
           gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else if ((gucSsCurInvokeId == 255) && (0 == *(*ppucSrc + 2)))
        {
            gucSsCurInvokeId = 0;
            gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else
        {
            ;
        }

        *ppucSrc = *ppucSrc + 3;
    }
    else if (SSA_NULL_TAG == **ppucSrc)
    {
        /*此时Invoke Id不存在*/
        *ppucSrc = *ppucSrc + 2;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeReject:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_MISTYPED_COMPONENT;
    }

    /*检查参数problem code*/
    if ((GENERAL_PROBLEM_TAG == **ppucSrc)||(INVOKE_PROBLEM_TAG == **ppucSrc)
        ||(RETURN_RESULT_PROBLEM_TAG == **ppucSrc)||(RETURN_ERROR_PROBLEM_TAG == **ppucSrc))
    {
        /*记录problem code,目前当作操作失败,统一上报*/
        pEvent->SsEvent = TAF_SS_EVT_PROBLEM;
        pEvent->OP_ProblemCode = SSA_FIELD_EXIST;

        ucProblemTag = **ppucSrc;
        (*ppucSrc)++;

        if (VOS_OK != SSA_DecodeLength(ppucSrc, &ucTmpLen))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeReject:WARNING: SSA_DecodeLength fail");
        }

        ucProblemCode = **ppucSrc;
        pEvent->ProblemCode = ucProblemCode;

        (*ppucSrc)++;

        if (INVOKE_PROBLEM_TAG == ucProblemTag)
        {
            return ucProblemCode|0x20;
        }

    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeReject:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_MISTYPED_COMPONENT;
    }

    return SSA_SUCCESS;
}



/*****************************************************************************
 Prototype      : SSA_DecodeRegisterSSCnf
 Description    : 解码网络侧回复的RegisterSS的相应（Return result）
 Input          : **ppucSrc--输入的字串
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeRegisterSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8  **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8      *pucEndLocation;

    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对标签值进行判断,根据24。080的描述，值只可能时0，1，3*/
    /*对相应的参数进行解码，具体参数参看24.080 Annex A, RegisterSS操作的参数*/
    switch (gSsTagValue.iNumber)
    {
        /*参数:forwardingInfo，进行解码*/
        case 0:
            ulRslt = SSA_DecodeForwardingInfo(&(para->FwdInfo), ppucSrc, IMPLICIT_MODE);
            para->OP_FwdInfo = 1;
            break;

        /*参数:callBarringInfo，进行解码*/
        case 1:
            ulRslt = SSA_DecodeCallBarringInfo(&(para->CallBarInfo), ppucSrc, IMPLICIT_MODE);
            para->OP_CallBarInfo = 1;
            break;

        /*参数:ss-Data, 进行解码*/
        case 3:
            ulRslt = SSA_DecodeSSData(&(para->SsData), ppucSrc, IMPLICIT_MODE);
            para->OP_SsData = 1;
            break;
        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: TagNumber is Error");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeEraseSSCnf
 Description    : 解码网络侧回复的EraseSS的响应（Return result）
 Input          : **ppucSrc--输入的字串   ulLen-- 子串的字串
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeEraseSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8   **ppucSrc)
{
    VOS_UINT32       ulRslt;

    /*EraseSS操作的参数类型与RegiserSS的参数类型一样*/
    ulRslt = SSA_DecodeRegisterSSCnf(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseSSCnf:WARNING: DeCode EraseSS fail");
    }


    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeActivateSSCnf
 Description    : 解码网络侧回复的AtcivateSS的响应（Return result）
 Input          : **ppucSrc--输入的字串   ulLen-- 子串的字串
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeActivateSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8   **ppucSrc)
{
    VOS_UINT32       ulRslt;

    /*ActivateSS操作的参数类型与RegiserSS的参数类型一样*/
    ulRslt = SSA_DecodeRegisterSSCnf(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeActivateSSCnf:WARNING: DeCode ActivateSS fail");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeDeactivateSSCnf
 Description    : 解码网络侧回复的DeatcivateSS的响应（Return result）
 Input          : **ppucSrc--输入的字串   ulLen-- 子串的字串
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeDeactivateSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8  **ppucSrc)
{
    VOS_UINT32       ulRslt;

    /*DeactivateSS操作的参数类型与RegiserSS的参数类型一样*/
    ulRslt = SSA_DecodeRegisterSSCnf(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeDeactivateSSCnf:WARNING: DeCode DeactivateSS fail");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeInterrogateSsCnf
 Description    : 解码网络侧回复的InterrogateSS的相应（Return result）
 Input          : **ppucSrc--输入的字串   ulLen--字串的长度
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeInterrogateSsCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8      *pucEndLocation;


    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对标签值进行判断,根据24。080的描述，值只可能时0,2,3, 4*/
    /*对相应的参数进行解码，具体参数参看24.080 Annex A, InterrogateSS操作的参数*/
    switch (gSsTagValue.iNumber)
    {
        /*参数:ss-Status，进行解码*/
        case 0:
            ulRslt = SSA_DecodeSsStatus(&(para->SsStatus), ppucSrc, IMPLICIT_MODE);
            para->OP_SsStatus = 1;
            break;

        /*参数:basicServiceGroupList，进行解码*/
        case 2:
            ulRslt = SSA_DecodeBasicServiceGroupList(&(para->BsServGroupList), ppucSrc, IMPLICIT_MODE);
            para->OP_BsServGroupList = 1;
            break;

        /*参数:forwardingFeatureList, 进行解码*/
        case 3:
            ulRslt = SSA_DecodeForwardingFeatureList(&(para->FwdFeaturelist), ppucSrc, IMPLICIT_MODE);
            para->OP_FwdFeaturelist = 1;
            break;

        /*参数:genericServiceInfo, 进行解码*/
        case 4:
            ulRslt = SSA_DecodeGenericServiceInfo(&(para->GenericServiceInfo), ppucSrc, IMPLICIT_MODE);
            para->OP_GenericServiceInfo = 1;
            break;
        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: TagNumber is Error");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;

}

/*****************************************************************************
 Prototype      : SSA_DecodeRegPwdCnf
 Description    : 解码网络侧回复的RegisterPassword的相应（Return result）
 Input          : **ppucSrc--输入的字串   ulLen--字串的长度
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeRegPwdCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8       ucTmp;
    VOS_UINT8      *pucEndLocation;

    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*判断是否时NumericString类型，是的话进行解码*/
    if (NUMERICSTRING_TAG == gSsTagValue.iNumber)
    {
        gulCurStrMaxLen = 4;
        ulRslt = SSA_DecodeNumericString(para->aucPassWord, &ucTmp, ppucSrc, IMPLICIT_MODE);
        para->OP_PassWord = 1;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: TagNumber is Error");
        return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeGetPwdInd
 Description    : 解码网络侧发来的的GetPassword的操作（Invoke）
 Input          : **ppucSrc--输入的字串   ulLen--字串的长度
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeGetPwdInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8      *pucEndLocation;


    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGetPwdInd:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGetPwdInd:WARNING: Length Value Error");
        return ulRslt;
    }

    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*判断是否是Enumerated类型，是的话进行解码*/
    if (ENUMERATED_TAG == gSsTagValue.iNumber)
    {
        ulRslt = SSA_DecodeGuidanceInfo(&(para->GuidanceInfo), ppucSrc, IMPLICIT_MODE);
        para->OP_GuidanceInfo = 1;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGetPwdInd:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeProcessUntructuredSSCnf
 Description    : 解码网络侧发来的的ProcessUntructuredSS的操作（Return result）
 Input          : **ppucSrc--输入的字串   ulLen--字串的长度
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2010年03月01日
    作    者   : h44270
    修改内容  : 问题单号:AT2D17075 波兰USSD网络兼容问题
*****************************************************************************/
VOS_UINT32  SSA_DecodeProcessUnstructuredSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8      *pucEndLocation;


    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: Length Value Error");
        return ulRslt;
    }

    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对ussd-DataCodingScheme进行解码, 解码失败则返回*/
    ulRslt = SSA_DecodeUssdDataCodingScheme(&(para->DataCodingScheme), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdDataCodingScheme Failure");
        return ulRslt;
    }
    para->OP_DataCodingScheme = 1;

    /*对ussd-String进行解码,解码失败则返回*/
    ulRslt = SSA_DecodeUssdString(&(para->UssdString), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdString Failure");
        return ulRslt;
    }

    /*在某些编码方案下,需要进行再解码,变成8bit编码方式*/
    if(AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
    {

       /*判断编码方案是否支持,支持的编码方案为0x0f和01xx xxxx的编码(bit3和bit2为0的7bit编码不支持)*/
        if ((para->DataCodingScheme == TAF_SS_8bit)
         || ((para->DataCodingScheme != TAF_SS_UCS2)
         && (0x00 != (para->DataCodingScheme>> 4))
         && (para->DataCodingScheme != TAF_SS_7BIT_DATA_CODING)))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: UNKNOWNALPHABET");
            return TAF_ERR_SS_UNKNOWN_ALPHABET;
        }

        if ((0x00 == (para->DataCodingScheme>> 4))
            ||(TAF_SS_7BIT_DATA_CODING == para->DataCodingScheme))
        {
            ulRslt = SSA_DecodeUssdMessage(&(para->UssdString), para->DataCodingScheme);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdMessage decode Failure");
                return ulRslt;
            }
            else
            {
                para->DataCodingScheme = TAF_SS_8bit;
            }
        }

    }
    para->OP_UssdString = 1;

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeUntructuredSSInd
 Description    : 解码网络侧发来的的UntructuredSS的操作（Invoke）
 Input          : **ppucSrc--输入的字串   ulLen--字串的长度
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2010年02月25日
    作    者   : s62952
    修改内容  : 问题单号:AT2D170545 波兰USSD网络兼容问题
  3.日    期   : 2013年03月26日
    作    者   : f62575
    修改内容  : 问题单号DTS2013040400068 解决法电网络过来的USSD消息不能上报的问题。
*****************************************************************************/
VOS_UINT32  SSA_DecodeUntructuredSSInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32       ulRslt = SSA_SUCCESS;
    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;

    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对ussd-DataCodingScheme进行解码,解码失败则返回*/
    ulRslt = SSA_DecodeUssdDataCodingScheme(&(para->DataCodingScheme), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeUssdDataCodingScheme deocde Failure");
        return ulRslt;
    }
    para->OP_DataCodingScheme = 1;

    /*对ussd-String进行解码,解码失败则返回*/
    ulRslt = SSA_DecodeUssdString(&(para->UssdString), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeUssdString decode Failure");
        return ulRslt;
    }

    /*在某些编码方案下,需要进行再解码,变成8bit编码方式*/
    if(AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
    {

       /*判断编码方案是否支持,支持的编码方案为0x0f和01xx xxxx的编码(bit3和bit2为0的7bit编码不支持)*/
        if ((para->DataCodingScheme == TAF_SS_8bit)
         || ((para->DataCodingScheme != TAF_SS_UCS2)
         && (0x00 != (para->DataCodingScheme>> 4))
         && (para->DataCodingScheme != TAF_SS_7BIT_DATA_CODING)))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: UNKNOWNALPHABET");
            return TAF_ERR_SS_UNKNOWN_ALPHABET;
        }

        if ((0x00 == (para->DataCodingScheme>> 4))
          ||(TAF_SS_7BIT_DATA_CODING == para->DataCodingScheme))
        {
            ulRslt = SSA_DecodeUssdMessage(&(para->UssdString), para->DataCodingScheme);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdMessage decode Failure");
                return ulRslt;
            }
            else
            {
                para->DataCodingScheme = TAF_SS_8bit;
            }
        }

    }
    para->OP_UssdString = 1;

    /*判断有没有alertingPattern这个参数,没有的话,跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*解码TLV中的T和L*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber) && (UNIVERSAL_TAG_TYPE == gSsTagValue.ucClass) && (*ppucSrc < pucEndLocation))
        {
            /*解码alertingpattern参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeAlertingPattern(&(para->AlertingPattern), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeAlertingPattern Failure");
                return ulRslt;
            }
            para->OP_AlertingPattern = 1;
        }
        else
        {
            /*不存在alertingpattern项*/
            *ppucSrc = pucCurLocation;
            para->OP_AlertingPattern = 0;
        }
    }
    else
    {
        /*不存在alertingpattern参数项*/
        para->OP_AlertingPattern = 0;
    }

    /* Modified by f62575 for DTS2013040400068 解决法电网络过来的USSD消息不能上报的问题 2013-03-26, begin   */
#if 0
    /*判断有没有msisdn这个参数，如果有的话进行解码，没有的话，返回*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*解码TLV中的T和L*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Length Value Error");
            return ulRslt;
        }

        /*确认是否存在msisdn参数项*/
        if ((0 == gSsTagValue.iNumber) && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass) && (*ppucSrc < pucEndLocation))
        {
            /*解码Msisdn参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeMsisdn(para->aucMsisdn, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeMsisdn Failure");
                return ulRslt;
            }
            para->OP_Msisdn = 1;
        }
        else
        {
            /*最后一个参数，标签值不可能为其他参数，如果不符，则认为出错*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Unknow Parameter");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
    }
    else
    {
        /*不存在alertingpattern参数项*/
        para->OP_Msisdn= 0;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }
#endif
    /* Modified by f62575 for DTS2013040400068 解决法电网络过来的USSD消息不能上报的问题 2013-03-26, end   */

    return  ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeUntructuredSSNotifyInd
 Description    : 解码网络侧发来的的UntructuredSSNotify的操作（Invoke）
 Input          : **ppucSrc--输入的字串   ulLen--字串的长度
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeUntructuredSSNotifyInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *para, VOS_UINT8 **ppucSrc)
{
  VOS_UINT32       ulRslt;

    /*unstructuredSS-Notify操作的参数类型与unstructuredSS-Request的参数类型一样*/
    ulRslt = SSA_DecodeUntructuredSSInd(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSNotifyInd:WARNING: DeCode UntructuredSSNotify fail");
    }


    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeEraseCCEntryCnf
 Description    : 解码网络侧发来的的EraseCCEntry的操作（Return Result）
 Input          : **ppucSrc--输入的字串   ulLen--字串的长度
 Output         : *para--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeEraseCCEntryCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对ss-Code进行解码*/
    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Length Value Error");
        return ulRslt;
    }

    /*判断标签值的正确性*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        /*解码ss-Code参数项,如果解码失败,则返回*/
        ulRslt = SSA_DecodeSsCode(&(para->SsCode), ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: SSA_DecodeSsCode decode Failure");
            return ulRslt;
        }
        para->OP_SsCode = 1;
    }
    else
    {
        /*标签值不是ss-Code的标签值,失败返回*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*判断是否有ss-Status, 有的话解码,没有跳过*/
    if (*ppucSrc < pucEndLocation)
    {
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Length Value Error");
            return ulRslt;
        }
        if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
        {
            /*解码ss-Status参数项,如果解码失败,则返回*/
            /*判断标签值的正确性*/
            ulRslt = SSA_DecodeSsStatus(&(para->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: SSA_DecodeSsCode decode Failure");
                return ulRslt;
            }
            para->OP_SsStatus = 1;
            /*对返回值进行判断如果出错，返回*/
        }
        else
        {
            /*最后一个参数，标签值不可能为其他参数，如果不符，则认为出错*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Unknow Parameter");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
    }
    else
    {
        /*没有Ss-Status参数项*/
        para->OP_SsStatus = 0;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt ;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeProcessUSSDataCnf
 功能描述  : 解码phase1的网络回复消息
 输入参数  : VOS_UINT8 **ppucSrc
 输出参数  : TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月5日
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2010年8月16日
    作    者   : 王毛/00166186
    修改内容   : DTS2010081702586 德国电信USSD PHASE1 兼容性问题


*****************************************************************************/
VOS_UINT32  SSA_DecodeProcessUSSDataCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt;

    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*如果是IA5String类型,进行相应的解码*/
    if (IA5STRING_TAG== gSsTagValue.iNumber)
    {
        gulCurStrMaxLen = 200;
        ulRslt = SSA_DecodeIA5String(para->UssdString.aucUssdStr,
                                    (VOS_UINT8*)&para->UssdString.usCnt, ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: SSA_DecodeUssdString Failure");
            return ulRslt;
        }
        para->OP_USSData = 1;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: Unknow Parameter");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    para->OP_DataCodingScheme = 1;
    para->DataCodingScheme    = TAF_SS_8bit;

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeSsCode
 Description    : 解码参数ss-Code,ASN.1的描述参见24.080的Annex A
 Input          : **ppucSrc--输入的字串 ,ucTagMode -- 标签模式
 Output         : *ucSscode -- 解码后的Sscode的值
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeSsCode(TAF_SS_CODE *ucSscode, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* 解码，返回解码函数的操作结果 */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(ucSscode, &ucStrLen, ppucSrc, ucTagmode);
}

/*****************************************************************************
 Prototype      : SSA_DecodeBasicServiceCode
 Description    : 解码参数basic service Code,ASN.1的描述参见24.080的Annex A
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *ucBsCode -- 解码后的UINT8类型的服务码
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeBasicServiceCode(TAF_BASIC_SERVICE_CODE *ucBsCode, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* 解码，返回解码函数的操作结果 */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(ucBsCode, &ucStrLen, ppucSrc, ucTagmode);
}


/*****************************************************************************
 Prototype      : SSA_DecodeSsStatus
 Description    : 解码参数ss-Status,ASN.1的描述参见24.080的Annex A
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeSsStatus(TAF_SS_STATUS *ucSsStatus, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* 解码，返回解码函数的操作结果 */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(ucSsStatus, &ucStrLen, ppucSrc, ucTagmode);
}

/*****************************************************************************
 Prototype      : SSA_DecodeMsisdn
 Description    : 解码参数Msisdn,ASN.1的描述参见24.080的Annex A
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeMsisdn(VOS_UINT8 *pucDest, VOS_UINT8  **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;

    /* 解码，返回解码函数的操作结果,并在字串的结尾处加上'\0'*/
    gulCurStrMaxLen = 20;
    ulRslt = SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeMsisdn:WARNING: Decode Msisdn Error!");
        return ulRslt;
    }

    pucDest[ucStrLen]='\0';

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeAlertingPattern
 Description    : 解码参数alertingPattern,ASN.1的描述参见24.080的Annex A
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeAlertingPattern(VOS_UINT8 *pucDest, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* 解码，返回解码函数的操作结果 */
    gulCurStrMaxLen = 1;
    return  SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagmode);
}

/*****************************************************************************
 Prototype      : SSA_DecodeBasicService
 Description    : 解码参数basicService,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeBasicService(TAF_SS_BASIC_SERVICE_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicService:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicService:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*确定服务类型*/
    pDest->BsType = (VOS_UINT8)gSsTagValue.iNumber;
    switch (gSsTagValue.iNumber)
    {
        /*确定service code*/
        case TAF_SS_BEARER_SERVICE:
        case TAF_SS_TELE_SERVICE:
            ulRslt = SSA_DecodeBasicServiceCode(&(pDest->BsServiceCode), ppucSrc, IMPLICIT_MODE);
            break;
        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicService:WARNING: TagNumber is Error");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardedToNumber
 Description    : 解码参数forwardedToNumber,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardedToNumber(TAF_SS_NUMTYPE *pucNumType, VOS_UINT8 *pucFwdToNum,VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];

    /* 解码，返回解码函数的操作结果,并在字串的结尾处加上'\0'*/
    gulCurStrMaxLen = 20;

    PS_MEM_SET(aucDest, 0, sizeof(aucDest));

    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardedToNumber:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
        return ulRslt;
    }

    *pucNumType = aucDest[0];
    SSA_BcdNumToAsciiNum(pucFwdToNum, aucDest + 1, ucStrLen-1, *pucNumType);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardedToSubaddress
 Description    : 解码参数forwardedToSubaddress,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardedToSubaddress(TAF_SS_SUBADDRTYPE *pucSubAddrType, VOS_UINT8 *pucSubAddr,VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];

    /* 解码，返回解码函数的操作结果,并在字串的结尾处加上'\0'*/
    gulCurStrMaxLen = 21;

    PS_MEM_SET(aucDest, 0, sizeof(aucDest));

    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardedToSubaddress:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
        return ulRslt;
    }
    *pucSubAddrType = aucDest[0];

    PS_MEM_CPY(pucSubAddr, aucDest + 1, ucStrLen-1);

    *(pucSubAddr + ucStrLen) = '\0';

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardingInfo
 Description    : 解码参数ForwardingInfo,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardingInfo(TAF_SS_FORWARDINGINFO_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8      *pucEndLocation;
    VOS_UINT8      *pucCurLocation;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*子串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*判断是否有ss-Code参数项*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有ss-Code参数项的Tag值:OCTETSTRING_TAG*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber)&&(*ppucSrc < pucEndLocation))
        {
            /*解码ss-Code参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeSsCode(&(pDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: SSA_DecodeSsCode Decode Failure");
                return ulRslt;
            }
            pDest->OP_SsCode = 1;
        }
        else
        {
            *ppucSrc = pucCurLocation;
            pDest->OP_SsCode = 0;
        }
    }
    else
    {
        /*无任何参数,失败返回，forwardingFeatureList为必有选项*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Para Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    /*确认当前有forwardingFeatureList,否则返回错误信息*/
    if (*ppucSrc < pucEndLocation)
    {
        /*对forwardingFeatureList的T、L项进行解码*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有forwardingFeatureList参数项,解码失败则返回*/
        if ( (SEQUENCE_TAG == gSsTagValue.iNumber) && (*ppucSrc < pucEndLocation) )
        {
            ulRslt = SSA_DecodeForwardingFeatureList(&(pDest->FwdFeaTurelist), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: SSA_DecodeForwardingFeatureList Decode Failure");
                return ulRslt;
            }
        }
        else
        {
            /*标签值不正确,失败返回*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: forwardingFeatureList Error");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }
    }
    else
    {
        /*无forwardingFeatureList项,失败返回*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: forwardingFeatureList Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardingFeatureList
 Description    : 解码参数ForwardingFeatureList,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardingFeatureList(TAF_SS_FWDFEATURELIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8      *pucEndLocation;
    VOS_UINT32      ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*采用循环解码的方式，解码结构体类型的数组*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*判断是否产生数组越界*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_FW_FEATURES)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: ForwardingFeature Num too large\r");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*如果ForwardingFeature解码失败，返回*/
        ulRslt = SSA_DecodeForwardingFeature(&(pDest->astFwdFtr[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: SSA_DecodeForwardingFeatureList Decode Failure");
            return ulRslt;
         }

        pDest->ucCnt += 1;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardingOptions
 Description    : 解码参数forwardingOptions,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardingOptions(VOS_UINT8 *pucDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8     ucStrLen;

    /* 解码，返回解码函数的操作结果 */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagMode);
}


/*****************************************************************************
 Prototype      : SSA_DecodeLongForwardedToNumber
 Description    : 解码参数longForwardedToNumber,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
VOS_UINT32 SSA_DecodeLongForwardedToNumber(TAF_SS_NUMTYPE *pucLongFwdNumType, VOS_UINT8 *pucLongFwdToNum,VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8     ucStrLen;
    VOS_UINT32    ulRslt;
    VOS_UINT8     aucDest[21];

    /*解码，同时在最后一个字符后面加上字符串结束符'\0'*/
    gulCurStrMaxLen = 20;

    PS_MEM_SET(aucDest, 0, sizeof(aucDest));

    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeLongForwardedToNumber:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
        return ulRslt;
    }

    *pucLongFwdNumType = aucDest[0];

    SSA_BcdNumToAsciiNum(pucLongFwdToNum, aucDest + 1, ucStrLen-1, *pucLongFwdNumType);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeCallBarringInfo
 Description    : 解码参数callBarringInfo,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCallBarringInfo(TAF_SS_CALLBRARINGINFO_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;


    /*判断是否有ss-Code参数项,有的话解码,没有跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有ss-Code参数项的Tag值:OCTETSTRING_TAG*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber)&&(*ppucSrc < pucEndLocation))
        {
            /*解码ss-Code参数项，解码失败则返回*/
            ulRslt = SSA_DecodeSsCode(&(pDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeature:WARNING: SSA_DecodeNoReplyConditionTime Decode Failure");
                return ulRslt;
            }
            pDest->OP_SsCode = 1;
        }
        else
        {
            *ppucSrc = pucCurLocation;
            pDest->OP_SsCode = 0;
        }
    }
    else
    {
        /*无任何参数,失败返回， callBarringFeatureList为必有选项*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Para Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    if (*ppucSrc < pucEndLocation)
    {
        /*对callBarringFeatureList的T、L项进行解码*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有callBarringFeatureList参数项,有的话解码,没有跳过*/
        if (SEQUENCE_TAG == gSsTagValue.iNumber)
        {
            ulRslt = SSA_DecodeCallBarringFeatureList(&(pDest->CallBarFtrList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: SSA_DecodeCallBarringFeatureList Decode Failure");
                return ulRslt;
            }
        }
        else
        {
            /*标签值不正确,失败返回*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: callBarringFeatureList Error");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }
    }
    else
    {
        /*无callBarringFeatureList项,失败返回*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: callBarringFeatureList Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeCallBarringFeatureList
 Description    : 解码参数CallBarringFeatureList,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCallBarringFeatureList(TAF_SS_CALLBARFEATURELIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*采用循环解码的方式，解码结构体类型的数组*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*判断是否产生数组越界*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_CallBarring_FEATURES)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: callBarringFeature Num too large");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*CallBarringFeature解码，解码失败则返回*/
        ulRslt = SSA_DecodeCallBarringFeature(&(pDest->astCallBarFtr[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: SSA_DecodeCallBarringFeature Decode Failure");
            return ulRslt;
         }

        pDest->ucCnt += 1;

        #if 0
        while ((**ppucSrc == 0) && (*(*ppucSrc + 1) == 0) && (*ppucSrc < pucEndLocation))
        {
            *ppucSrc = *ppucSrc + 2;
        }
        #endif
    }

    return ulRslt;
}


/*lint -e438 -e830*/

/*****************************************************************************
 Prototype      : SSA_DecodeCallBarringFeature
 Description    : 解码参数callBarringFeature,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCallBarringFeature(TAF_SS_CALLBARRINGFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{

    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*判断是否有参数项basicService,有的话解码,没有跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有basicService参数项的Tag值:0x82或者0x83*/
        if (((2 == gSsTagValue.iNumber)||(3 == gSsTagValue.iNumber))&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*解码basicService参数项,解码失败则返回*/
            ulRslt = SSA_DecodeBasicService(&(pDest->BsService), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: SSA_DecodeBasicService Decode Failure");
                return ulRslt;
            }
            pDest->OP_BsService= 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc = pucCurLocation;
            pDest->OP_BsService= 0;
        }
    }
    else
    {
        /*表明没有basicService参数项*/
        pDest->OP_BsService= 0;
    }

    /*判断是否有参数项ss-Status,有的话解码,没有跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有ss-Status参数项的Tag值:0x84*/
        if ((4 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*解码ss-Status参数项，解码失败则返回*/
            ulRslt = SSA_DecodeSsStatus(&(pDest->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: SSA_DecodeSsStatus Decode Failure");
                return ulRslt;
            }
            pDest->OP_SsStatus= 1;
        }
        else
        {
            /*最后一个参数，标签值不可能为其他参数，如果不符，则认为出错*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: SSA_DecodeSsStatus Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*表明没有ss-Status参数项*/
        pDest->OP_SsStatus= 0;
    }

    return ulRslt;
}
/*lint +e438 +e830*/

/*****************************************************************************
 Prototype      : SSA_DecodeBasicServiceGroupList
 Description    : 解码参数basicServiceGroupList,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeBasicServiceGroupList(TAF_SS_BS_SERV_GROUPLIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE  ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSSData:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSSData:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*长度指示置0*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*判断是否产生数组越界*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_BASIC_SERVICES)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicServiceGroupList:WARNING: basicServiceGroup Num too large");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*解码basicService参数项,解码失败则返回*/
        ulRslt = SSA_DecodeBasicService(&(pDest->astBsService[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicServiceGroupList:WARNING: SSA_DecodeCallBarringFeature Decode Failure");
            return ulRslt;
        }

        /*长度计数加1*/
        pDest->ucCnt += 1;
    }

    return ulRslt;
}
/*****************************************************************************
 Prototype      : SSA_DecodeCcbsFeatureList
 Description    : 解码参数ccbs-FeatureList,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
*****************************************************************************/
VOS_UINT32 SSA_DecodeCcbsFeatureList(TAF_SS_CCBS_FEATURELIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*获取字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*采用循环解码的方式，解码结构体类型的数组*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*判断是否产生数组越界*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_CCBS_FEATURE)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: CcbsFeature Num too large");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*解码CcbsFeatur,解码失败则退出*/
        ulRslt = SSA_DecodeCcbsFeature(&(pDest->astCcBsFeature[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: SSA_DecodeCcbsFeature Decode Failure");
            return ulRslt;
        }

        pDest->ucCnt += 1;

        #if 0
        while ((**ppucSrc == 0) && (*(*ppucSrc + 1) == 0) && (*ppucSrc < pucEndLocation))
        {
            *ppucSrc = *ppucSrc + 2;
        }
        #endif
    }

    return ulRslt;

}

/*lint -e438 -e830*/

/*****************************************************************************
 Prototype      : SSA_DecodeCcbsFeature
 Description    : 解码参数ccbs-Feature,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pCcBsFeature--解码后的数据结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCcbsFeature(TAF_SS_CCBS_FEATURE_STRU *pCcBsFeature, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{

    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;
    VOS_INT32          iTmp;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*判断是否有参数项ccbs-Index,有的话解码,没有跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有ccbs-Index参数项的Tag值:0x80*/
        if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*解码ccbs-Index参数项*/
            ulRslt = SSA_DecodeCcbsIndex(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeCcbsIndex Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->CcbsIndex = (VOS_UINT8)iTmp;
            pCcBsFeature->OP_CcbsIndex= 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc = pucCurLocation;
            pCcBsFeature->OP_CcbsIndex= 0;
        }
    }
    else
    {
            /*表明没有ccbs-Index参数项*/
            pCcBsFeature->OP_CcbsIndex= 0;
    }

    /*判断是否有参数项b-subscriberNumber,有的话解码,没有跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有b-subscriberNumber参数项的Tag值:0x81*/
        if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*解码b-subscriberNumber参数项*/
            ulRslt = SSA_DecodeBSubscriberNum(&(pCcBsFeature->NumType), pCcBsFeature->aucBSubscriberNum, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBSubscriberNum Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->OP_BSubscriberNum = 1;
            pCcBsFeature->OP_NumType = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc = pucCurLocation;
            pCcBsFeature->OP_BSubscriberNum = 0;
            pCcBsFeature->OP_NumType = 0;
        }
    }
    else
    {
        /*表明没有b-subscriberNumber参数项*/
        pCcBsFeature->OP_BSubscriberNum = 0;
        pCcBsFeature->OP_NumType = 0;
    }

    /*判断是否有参数项b-subscriberSubaddress,有的话解码,没有跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有b-subscriberSubaddress参数项的Tag值:0x82*/
        if ((2 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*解码b-subscriberSubaddress参数项*/
            ulRslt = SSA_DecodeBSubscriberSubAddress(&(pCcBsFeature->SubAddrType), pCcBsFeature->aucBSubscriberSubAddr, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBSubscriberSubAddress Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->OP_BSubscriberSubAddr = 1;
            pCcBsFeature->OP_SubAddrType = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc = pucCurLocation;
            pCcBsFeature->OP_BSubscriberSubAddr = 0;
            pCcBsFeature->OP_SubAddrType = 0;
        }
    }
    else
    {
        /*表明没有b-subscriberSubaddress参数项*/
        pCcBsFeature->OP_BSubscriberSubAddr = 0;
        pCcBsFeature->OP_SubAddrType = 0;
    }

    /*判断是否有参数项basicServiceGroup,有的话解码,没有跳过*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有basicServiceGroup参数项的Tag值:0x83*/
        if ((3 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*解码basicServiceGroup参数项*/
            ulRslt = SSA_DecodeBasicServiceGroupList(&(pCcBsFeature->BsServGroupList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBasicService Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->OP_BsService= 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBasicService Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*表明没有basicServiceGroup参数项*/
        pCcBsFeature->OP_BsService= 0;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
		SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value not equal with actual length");

        return VOS_ERR;
    }
    return SSA_SUCCESS;
}
/*lint +e438 +e830*/


/*****************************************************************************
 Prototype      : SSA_DecodeBSubscriberNum
 Description    : 解码参数b-subscriberNumber,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pucNumType--解码后号码类型, *pucBSubscriberNum -- 解码后号码
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 SSA_DecodeBSubscriberNum(TAF_SS_NUMTYPE *pucNumType, VOS_UINT8 *pucBSubscriberNum, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];


    ucStrLen = 0;
    PS_MEM_SET(aucDest, 0x00, sizeof(aucDest));


    /* 解码，返回解码函数的操作结果,并在字串的结尾处加上'\0'*/
    gulCurStrMaxLen = 20;
    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);

    *pucNumType = aucDest[0];

    SSA_BcdNumToAsciiNum(pucBSubscriberNum, aucDest + 1, ucStrLen-1, *pucNumType);

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeBSubscriberSubAddress
 Description    : 解码参数b-subscriberSubaddress,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pucSubAddrType--解码后地址类型, pucBSubscriberSubAddr--子地址
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 SSA_DecodeBSubscriberSubAddress(TAF_SS_SUBADDRTYPE *pucSubAddrType, VOS_UINT8 *pucBSubscriberSubAddr, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];


    ucStrLen = 0;
    PS_MEM_SET(aucDest, 0x00, sizeof(aucDest));


    /* 解码，返回解码函数的操作结果,并在字串的结尾处加上'\0'*/
    gulCurStrMaxLen = 21;
    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);

    *pucSubAddrType = aucDest[0];

    PS_MEM_CPY(pucBSubscriberSubAddr, aucDest + 1, ucStrLen-1);

    *(pucBSubscriberSubAddr + ucStrLen) = '\0';

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeUssdDataCodeScheme
 Description    : 解码参数ussd-DataCodingScheme,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pCodingScheme--解码后的编码方案
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeUssdDataCodingScheme(TAF_SS_DATA_CODING_SCHEME *pCodingScheme, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    /* VOS_UINT8       *pucEndLocation; */
    VOS_UINT8        ucStrLen;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /* pucEndLocation = *ppucSrc + gucSsCurLen; */

    /*如果标签值相符，对参数ussd-DataCodingScheme进行解码*/
    if ( OCTETSTRING_TAG == gSsTagValue.iNumber)
    {
        /*参数项ussd-DataCodingScheme解码,失败则返回*/
        gulCurStrMaxLen = 1;
        ulRslt = SSA_DecodeString(pCodingScheme, &ucStrLen, ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: SSA_DecodeString Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeUssdString
 Description    : 解码参数ussd-String,参见24.080的Annex A的ASN.1的描述
 Input          : **ppucSrc--输入的字串, ucTagMode -- 标签模式
 Output         : *pUssdStr--解码后的USSD字串
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeUssdString(TAF_SS_USSD_STRING_STRU *pUssdStr, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32       ulRslt;
    /* VOS_UINT8        ucStrLen; */
    /* VOS_UINT8       *pucEndLocation; */

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /* pucEndLocation = *ppucSrc + gucSsCurLen; */

    /*如果标签值相符，对参数ussd-String进行解码*/
    if ( OCTETSTRING_TAG == gSsTagValue.iNumber)
    {
        gulCurStrMaxLen = 160;
        ulRslt = SSA_DecodeString(pUssdStr->aucUssdStr, (VOS_UINT8*)&(pUssdStr->usCnt), ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: SSA_DecodeString Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return SSA_SUCCESS;

}

/*******************************************************************************
  Function      :SSA_BcdNumToAsciiNum
  Description   :将BCD编码转换成Ascii码
  Input         :*pucBcdNum --- 输入的BCD编码的字串
				  ucBcdNumLen --- BCD编码字串的长度
  Return        : SSA_SUCCESS --- 成功
  				  SSA_ERROR---失败
  Output        :*pucAsciiNum --- Ascii码字符串
  Invoke        : --
  Invoked By    : --
  History       : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
********************************************************************************/
VOS_VOID SSA_BcdNumToAsciiNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucBcdNum,
                              VOS_UINT8 ucBcdNumLen, VOS_UINT8 ucNumType)
{
    VOS_UINT32      ulTmp;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    if (SSA_NUM_TYPE_INT_E164 == ucNumType) /*<==A32D10708*/
    {
        *pucAsciiNum = '+';
        pucAsciiNum++;
    }

    for (ulTmp = 0; ulTmp < ucBcdNumLen; ulTmp++)
    {
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + ulTmp)) & 0x0f);             /*low four bits*/
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + ulTmp)) >> 4) & 0x0f);   /*high four bits*/
        if(ucFirstNumber <= 9)
        {
            *pucAsciiNum = ucFirstNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucFirstNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucFirstNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucFirstNumber + 0x55;
            pucAsciiNum++;
        }

        /* the following proceed the second number */
        if(0xf == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucSecondNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucSecondNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucSecondNumber + 0x55;
            pucAsciiNum++;
        }
    }
    *pucAsciiNum = '\0';
}

/* l65478 begin */
/*****************************************************************************
*  Prototype       : SSA_Get7bits
*  Description     : 对7bit编码的段进行解码并转换为字节
*  Input           : pucEncodedMsg --- 指向待解码的7bit字符串的指针
*                    ulBitAddress  --- 以7为增量的bit串的长度值
*  Output          : pucChar       --- 指向解码后生成的字节的指针
*  Return Value    : SMT_FALSE     --- 失败
*                    SMT_TRUE      --- 成功
*  Calls           :
*  Called By       : Smt_DecodeMessage
*  History         :
*  1. Date         : 2005-10-30
*     Author       : 郜东东
*     Modification : Created function
*****************************************************************************/
VOS_VOID SSA_Get7bits( VOS_UINT8 *pucChar,
                   VOS_UINT8 const *pucEncodedMsg,
                   VOS_UINT32 ulBitAddress )
{
    VOS_UINT32   ulAddress;      /*存放字节地址*/
    VOS_UINT32   ulOffset;       /*存放位偏移*/

    /*计算出字节地址和位偏移*/
    ulAddress = ulBitAddress / 8;
    ulOffset  = ulBitAddress % 8;

    /*将编码过的字符的两部分，分别从相邻的两个字节读出来*/
    /*读出第一部分的内容*/
    *pucChar = ( pucEncodedMsg[ulAddress] >> ulOffset ) & 0x7F;
    /*如果位偏移小于2，则没有第二部分的内容，直接返回*/
    if ( ulOffset < 2 )
    {
        return;
    }
    /*继续读出第二部分的内容*/
    /*lint -e701*/
    *pucChar |= ( ( pucEncodedMsg[ulAddress + 1] << ( 8 - ulOffset ) ) & 0x7F );
    /*lint +e701*/
}



/*****************************************************************************
 函 数 名  : SSA_Decode7bit
 功能描述  : 7bit转8bit编码
 输入参数  : TAF_SS_USSD_STRING_STRU   *para
             VOS_UINT8  ucCodingScheme
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月20日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity

*****************************************************************************/
VOS_VOID SSA_Decode7bit (TAF_SS_USSD_STRING_STRU   *para, VOS_UINT8  ucCodingScheme)
{
    VOS_UINT8      aucTmp[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32     ulLoop;
    VOS_UINT32     ulBitAddress;
    VOS_UINT8      ucDecodeLen;

    ulLoop        = 0;
    ulBitAddress  = 0;


    /*判断是否是7bit编码,根据产品线需求，只支持0000 XXXX的7bit编码，
     其他方式的7bit编码直接丢弃，并返回error */

    if (0 == para->usCnt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_Decode7bit:WARNING: string size 0");
        return;
    }

    if ((0x00 == (ucCodingScheme >> 4 ))
        || (TAF_SS_7BIT_DATA_CODING == ucCodingScheme))
    {
        PS_MEM_SET(aucTmp, 0, TAF_SS_MAX_UNPARSE_PARA_LEN);

        /*长度超过182则字符超长*/
        if (para->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            SSA_LOG(WARNING_PRINT, "SSA_Decode7bit:WARNING: string too long");
            return;
        }

        /*计算7bit字符数*/
        ucDecodeLen = (VOS_UINT8)((para->usCnt * 8) / 7);
        if (0 == ((para->usCnt * 8) % 7))
        {
            /*当字节数为8(n-1)时,确认最后一个字节的高7位是不是为0001101,
            是的话,认为是回车,不是字符*/
            if (0x0d == (para->aucUssdStr[para->usCnt-1]>>1))
            {
                ucDecodeLen--;
            }
        }

        /*循环结构,转换成7bit解码方式*/
        for ( ulLoop = 0; ulLoop < ucDecodeLen; ulLoop++ )
        {
            SSA_Get7bits(&aucTmp[ulLoop], para->aucUssdStr, ulBitAddress);

            /*下一个字符的地址*/
            ulBitAddress += 7;
        }

        /*赋值,并拷贝解码后的字符串*/
        para->usCnt = ucDecodeLen;
        PS_MEM_CPY(para->aucUssdStr, aucTmp, para->usCnt);
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_Decode7bit:WARNING: CodingScheme is not suport");
        return;
    }
    return;
}

/*******************************************************************************
  Function      :SSA_DecodeUssdMessage
  Description   :USSD字串内容进行7bit解码
  Input         :*para --- 输入的USSD字符串的指针
				  ucCodingScheme --- 编码方案
  Return        : SSA_SUCCESS --- 成功
  				  SSA_ERROR---失败
  Output        :*para --- 指向解码转换后的USSD字符串的指针
  Invoke        : SSA_Get7bits
  Invoked By    : SSA_DecodeDeliverInd
  History       : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2. 日    期   : 2010年05月07日
     作    者   : s62952
     修改内容   : 问题单号:A2D18963
  3. 日    期   : 2013年05月17日
     作    者   : w00176964
     修改内容   : SS FDN&Call Control项目:USSD的转换表放到SDC中
  4. 日    期   : 2013年07月222日
     作    者   : j00177245
     修改内容   : 清理Coverity
********************************************************************************/
VOS_UINT32 SSA_DecodeUssdMessage (TAF_SS_USSD_STRING_STRU   *para, VOS_UINT8  ucCodingScheme)
{
    VOS_UINT8      aucTmp[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32     ulLoop;
    VOS_UINT32     ulBitAddress;
    VOS_UINT8      ucDecodeLen;
    VOS_UINT8      aucAscii_String[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32     n;
    VOS_UINT8      *pucCurTransTbl= VOS_NULL_PTR;

    ulLoop        = 0;
    ulBitAddress  = 0;
    n             = 0;

    PS_MEM_SET(aucAscii_String, 0, TAF_SS_MAX_UNPARSE_PARA_LEN);

    if (0 == para->usCnt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdMessage:WARNING: string usCnt 0");
        return SSA_FAILURE;
    }

    /*判断是否是7bit编码,根据产品线需求，只支持0000 XXXX的7bit编码，
     其他方式的7bit编码直接丢弃，并返回error
    */
    if ((0x00 == (ucCodingScheme >> 4 ))
        || (TAF_SS_7BIT_DATA_CODING == ucCodingScheme))
    {
        PS_MEM_SET(aucTmp, 0, TAF_SS_MAX_UNPARSE_PARA_LEN);

        /*长度超过182则字符超长*/
        if (para->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdMessage:WARNING: string too long");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }

        /*计算7bit字符数*/
        ucDecodeLen = (VOS_UINT8)((para->usCnt * 8) / 7);
        if (0 == ((para->usCnt * 8) % 7))
        {
            /*当字节数为8(n-1)时,确认最后一个字节的高7位是不是为0001101,
            是的话,认为是回车,不是字符*/
            if (0x0d == (para->aucUssdStr[para->usCnt-1]>>1))
            {
                ucDecodeLen--;
            }
        }

        /*循环结构,转换成7bit解码方式*/
        for ( ulLoop = 0; ulLoop < ucDecodeLen; ulLoop++ )
        {
            SSA_Get7bits(&aucTmp[ulLoop], para->aucUssdStr, ulBitAddress);

            /*下一个字符的地址*/
            ulBitAddress += 7;
        }

        /*now convert from default alphabet coding into ascii coding*/
        pucCurTransTbl = TAF_SDC_GetCurr7BitToAsciiTableAddr();
        for( n = 0; n < ucDecodeLen; n++ )
        {
            aucAscii_String[n] = pucCurTransTbl[aucTmp[n]];
        }

        /*赋值,并拷贝解码后的字符串*/
        para->usCnt = ucDecodeLen;
        PS_MEM_CPY(para->aucUssdStr, aucAscii_String, para->usCnt);

    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdMessage:WARNING: CodingScheme is not suport");
        return SSA_FAILURE;
    }
    return SSA_SUCCESS;
}


/*****************************************************************************
 Prototype      : SSA_DecodeInt
 Description    : 对BER整型数值进行解码
 Input          : **ppucSrc--编码前的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的值
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeInt(VOS_INT32 *piDest, VOS_INT32 iMaxNum, VOS_UINT8 **ppucSrc, TAG_MODE usTagMode)
{
    VOS_UINT8    ucTmpValue;
    VOS_INT8     cTempLen;
    VOS_INT8     cTmpBuffer[sizeof(VOS_INT32)];
    /*VOS_UINT8    ucFillChar1 = 0; ucFillChar2 = 0xff;*/
    VOS_INT32      Tmpsize,i;

    PS_MEM_SET(cTmpBuffer, 0, sizeof(VOS_INT32));
    /*如果是explicit模式*/
    if (EXPLICIT_MODE  == usTagMode)
    {
        ucTmpValue = (VOS_UINT8)(**ppucSrc & 0x1f);
        if (ucTmpValue != INTEGER_TAG)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: Tag Number Error");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
        *ppucSrc = *ppucSrc + 2;  /*后移2个字节,获取值*/
    }


    /*获取整型的长度*/
    cTempLen = (VOS_INT8)(*(*ppucSrc - 1));
    if ((cTempLen > 4) || (cTempLen <= 0)||(cTempLen > (VOS_INT32)sizeof(VOS_INT32)))
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: Int length Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*判断是否是0，是的话，赋值返回*/
    if ((*(*ppucSrc-1) == 1)&&(**ppucSrc == 0))
    {
        *piDest = 0;
        *ppucSrc = *ppucSrc + 1;
        return SSA_SUCCESS;
    }

    /*第一个字节和第二个字节的最高位不能同时为0或1*/
    if (((**ppucSrc == 0) && ((*(*ppucSrc+1)&0x80) == 0)) ||
         ((**ppucSrc == 0xff) && ((*(*ppucSrc+1)&0x80) == 0x80)) )
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: para value Error");
        return TAF_ERR_SS_UNEXPECTED_DATA_VALUE;
    }

    /*记录最高比特所在的字节的值*/
    ucTmpValue = **ppucSrc;

    /*进行赋值*/
    *piDest = 0;
    for (i = 0 ; i < cTempLen ; i++)
    {
        /* cTmpBuffer[(cTemLen - i) - 1] = (char)**ppucSrc ; */
        /* *ppucSrc = *ppucSrc + 1 ; */
        *piDest = (VOS_INT32)(((VOS_UINT32)*piDest << 8) + **ppucSrc);
        *ppucSrc = *ppucSrc + 1;
    }

    /*负数填充ff*/
    Tmpsize = (VOS_INT8)sizeof(VOS_INT32);
    /*lint -e961*/
    if ((ucTmpValue & 0x80) && (Tmpsize != cTempLen))
    /*lint +e961*/
    {
        *piDest =(VOS_INT32)((0xffffffff << ((Tmpsize - cTempLen)*8)) | *piDest);
    }

    /*超过设定的最大值,则报错返回*/
    if (*piDest > iMaxNum)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: Value too large");
        return TAF_ERR_SS_UNEXPECTED_DATA_VALUE;
    }

    return SSA_SUCCESS;
}



/*****************************************************************************
 Prototype      : SSA_DecodeString
 Description    : 将Octet String类型的字串解码成普通的字符串
 Input          : **ppucSrc--解码前的字串
 Output         : *pucDest--解码后的字串   *pDestLen--解码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeString(VOS_UINT8 *pucDest, VOS_UINT8 *pucDestLen, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    /* VOS_UINT8            ucCurLen; */
    VOS_UINT32           ulRslt;
    /* SSA_TAG_STRU         stTagStru; */

    /*如果是explicit模式*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，有误的话return*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeString:WARNING: Tag Value Error");
            return ulRslt;
        }

        /*对长度进行解码，失败则返回*/
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeString:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*如果是长度确定型的类型*/
    /* if (gucSsCurLen != INDEFINITE_LEN) 长度确定型*/
    /*{ */
    /*对返回的长度进行检查*/
    if ((gucSsCurLen == 0)||(gucSsCurLen > gulCurStrMaxLen))
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeString:WARNING: Length Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*根据解码出来的字符串长度来进行内存拷贝*/
    PS_MEM_CPY(pucDest, *ppucSrc, gucSsCurLen);

    *pucDestLen = gucSsCurLen;

    *ppucSrc = *ppucSrc + gucSsCurLen;

    return SSA_SUCCESS ;
   /* } */

    #if 0
    /*如果是非确定长度类型,有两个全0字节加在了编码后的Value字段后面*/
    *pucDestLen = 0;
    while ((**ppucSrc != 0) && (*(*ppucSrc + 1) != 0))
    {
        /*跳过Tag部分*/
        SSA_DecodeTag(ppucSrc, stTagStru);

        /*对长度进行解码,获取当前长度*/
        ulRslt = SSA_DecodeLength(ppucSrc, &ucCurLen);
        /*检查返回的参数, 有误的话return*/

        /*获取到当前的字串总长*/
        *pucDestLen = *pucDestLen + ucCurLen;

        /*根据解码出来的字符串长度来进行内存拷贝*/
        VOS_MemCpy(pucDest + *pucDestLen, *ppucSrc, ucCurLen);

        /*源字串的指针移位*/
        *ppucSrc = *ppucSrc + ucCurLen;
    }
    #endif
}


/*****************************************************************************
 Prototype      : SSA_DecodeEnum
 Description    : BER编码的枚举值转换成VOS_UINT8型
 Input          : **ppucSrc--解码前的字串, ucTagMode -- 标签模式
 Output         : *pucDest--解码后的值
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeEnum( VOS_UINT8 *pucDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucTagNum;

    /*如果是explicit模式*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        /*获取Tag的值*/
        ucTagNum = (VOS_UINT8)(**ppucSrc & 0x1f);

        /*对标签值进行判断*/
        if (ucTagNum != ENUMERATED_TAG)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEnum:WARNING: Enum Tag Num Wrong");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }

        /*指向TLV中V所指向的地址*/
        *ppucSrc = *ppucSrc + 2;
    }

    /*判断TLV中L的值*/
    if (*(*ppucSrc - 1) != 1)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEnum:WARNING: Enum Tag Num Wrong");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*进行赋值，并偏移指针*/
    *pucDest = **ppucSrc;
    *ppucSrc = *ppucSrc + 1;

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_DecodeLength
 Description    : 根据BER编码的长度分类更新消息中的长度字段；
                  第一级分类: 定长和不定长
                  第二级分类: 不定长的分为长格式和短格式
 Input          : **ppucSrc--解码前的字串
 Output         : *pucLen--解码后的长度
 Return Value   : Tag的组成
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeLength(VOS_UINT8 **ppucSrc, VOS_UINT8 *pucLen)
{
    VOS_UINT8    ucTmpLen;

    *pucLen = 0;
    ucTmpLen = **ppucSrc;

    *ppucSrc = *ppucSrc + 1;

    /* 如果是短格式模式，明确长度，计算长度 */
    if (ucTmpLen < 128)
    {
        *pucLen = ucTmpLen;
        return SSA_SUCCESS;
    }

    switch (ucTmpLen)
    {
        case 128:   /*不定长度的计算处理*/
            /*由于在SS的para的总长都是可知的，所以不应该出现直接传送内容而并不清楚整个数据的长度*/
            /* SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: Length 128 Wrong"); */
            if (SSA_SUCCESS != SSA_DecodeIndefLen(*ppucSrc, pucLen))
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: Indefine Len Error");
                return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
            }
            break;
        case 129:   /*长格式，多字节，*/
            *pucLen = **ppucSrc;
            *ppucSrc = *ppucSrc + 1;
            break;
        default:
            /*
            大于129的情况，由于长度不会超过一个字节，在使用多字节表示时，不会超过一个字节
            若更长，则出错处理
            */
            SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: length too long");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return SSA_SUCCESS;

}

/*****************************************************************************
 Prototype      : SSA_DecodeIndefLen
 Description    : 获取可变长度字段的实际长度；
 Input          : **ppucSrc--解码前的字串
                  *pucLen--解码前的字串长度
 Output         : *pucLen--解码后的长度
 Return Value   : 更新长度操作结果；
                    SSA_SUCCESS 成功；其他，失败
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年11月02日
    作    者   : f62575
    修改内容   : DTS2012091700478，SS命令网络回复消息带不定长度IE，消息无法解析
*****************************************************************************/
VOS_UINT32 SSA_DecodeIndefLen(VOS_UINT8 *pucSrc, VOS_UINT8 *pucLen)
{
    VOS_UINT8                           ucCheckLength;
    VOS_UINT8                           aucEndFlag[] = {0,0};
    VOS_UINT8                           ucEndFlagLength;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           ucLengthBytes;
    VOS_UINT32                          ulRet;

    /* 获取LEN的实际长度； */
    /* 更新可变长度字段为实际长度，待检查的总长度变更为可变长度到实际长度的结束位置；*/
    /* 直到待检查长度与TLV字段的L一致结束 */
    ucCheckLength   = SSA_MAX_COMPONENT_LENGTH;
    ucEndFlagLength = sizeof(aucEndFlag);
    ulLoop          = 0;

    while (ulLoop < SSA_MAX_COMPONENT_LENGTH)
    {
        if (0 == PS_MEM_CMP(pucSrc, aucEndFlag, ucEndFlagLength))
        {
            *pucLen = (VOS_UINT8)ulLoop;
            return SSA_SUCCESS;
        }

        /* TAG */
        pucSrc++;
        ulLoop++;

        /* LENGTH */
        ucLength    = *pucSrc;
        pucSrc++;
        ulLoop++;

        /* 不定长方式:Length所在八位组固定编码为0x80，Value编码结束后以两个0x00结尾。*/
        if (SSA_FALSE_LENGTH_FLAG == ucLength)
        {
            ucLength = ucCheckLength - (VOS_UINT8)ulLoop;
            ulRet = SSA_DecodeIndefLen(pucSrc, &ucLength);
            if (SSA_SUCCESS != ulRet)
            {
                return ulRet;
            }

            pucSrc  += ucLength;
            ulLoop  += ucLength;
        }
        else
        {
            if (SSA_FALSE_LENGTH_FLAG == (ucLength & SSA_FALSE_LENGTH_FLAG))
            {
                /* 定长方式长格式: 第一个八位组的低七位指明整个L所占用的八位组个数，后续八位组表示V的长度 */
                /* SS仅支持长度为1字节的长度 */
                ucLengthBytes = ucLength & SSA_LONG_LENGTH_FORMAT_MASK;
                if (ucLengthBytes > sizeof(VOS_UINT8))
                {
                    SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: length too long");
                    return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
                }

                /* LENGTH */
                ucLength    = *pucSrc;
                pucSrc++;
                ulLoop++;

                pucSrc  += ucLength;
                ulLoop  += ucLength;
            }
            else
            {
                /* 定长方式短格式 */
                pucSrc  += ucLength;
                ulLoop  += ucLength;
            }
        }

    }

    return SSA_FAILURE;
}

/*****************************************************************************
 Prototype      : SSA_DecodeTag
 Description    : 对BER编码的Tag的值进行解码
 Input          : **ppucSrc -- 解码前的字串
 Output         : *pstTagStru -- 标签的结构
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeTag(VOS_UINT8 **ppucSrc , SSA_TAG_STRU *pstTagStru)
{
    VOS_UINT8       ucCounter = 0;
    VOS_UINT8       ucTmp;

    ucTmp = **ppucSrc;

    /*获取标签类型和结构*/
    pstTagStru->ucClass = (VOS_UINT8)(ucTmp >> 6);
    pstTagStru->ucStructed = (VOS_UINT8)(((ucTmp & 0x20) == PRIMITIVE_TAG) ? PRIMITIVE_TAG : CONSTRUCTED_TAG);

    /*获取标签值*/
    ucTmp = (VOS_UINT8)(ucTmp & 0x1f);
    if (ucTmp != 0x1f)          /*单字节格式*/
    {
        pstTagStru->iNumber = ucTmp;
        *ppucSrc = *ppucSrc + 1;
        return SSA_SUCCESS;
    }

    /*多字节格式时,获取标签值,最高位为1时,表示有后续字节*/
    /*把后续字节的第一个字节到最后一个字节的第7位到第一位连起来就是标签的值*/
    pstTagStru->iNumber = 0;
    do
    {
        /*最多的循环次数和int型的长度相关*/
        if (ucCounter > sizeof(pstTagStru->iNumber))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeTag:WARNING: Tag Num wrong");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
        ucCounter ++;
        *ppucSrc = *ppucSrc + 1;
        ucTmp = **ppucSrc;
        pstTagStru->iNumber = (VOS_INT32)(((VOS_UINT32)pstTagStru->iNumber << 7) + (ucTmp & 0x7f));
    }while(ucTmp >= 128);

    *ppucSrc = *ppucSrc + 1;

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_DecodeSsNull
 Description    : 将参数项NULL解码,类型定义参见24.080,附录
 Input          : **ppucSrc--解码前的字串, ucTagMode -- 标签模式
 Output         : --
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeSsNull(VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8    ucTmp;

    /*如果是显式模式，则解码tag*/
    if (ucTagMode == EXPLICIT_MODE)
    {
        ucTmp = (**ppucSrc & 0x1F) ;
        if (ucTmp != NULL_TAG)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSsNull:WARNING: Null Tag Value Err");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER ;
        }

        gucSsCurLen = *(*ppucSrc + 1);
        *ppucSrc = *ppucSrc + 2 ;
    }

    /*NULL模式下，长度必然是0*/
    if (gucSsCurLen != 0)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeSsNull:WARNING: Null Type Length Value Err");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return SSA_SUCCESS;
}


/*****************************************************************************
 函 数 名  : SSA_DecodeTL
 功能描述  : 解析参数的TAG和LENGTH
 输入参数  : VOS_UINT8          **ppucSrc    -待解码的字串
 输出参数  : SSA_TAG_STRU       *pstTagStru  -存放解码出的标签值
             VOS_UINT8          *pucLen      -存放解码出的长度值
 返 回 值  : VOS_UINT32                      -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月8日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeTL(
    VOS_UINT8                           **ppucSrc,
    SSA_TAG_STRU                        *pstTagStru,
    VOS_UINT8                           *pucLen
)
{
    VOS_UINT32                          ulRslt;

    /* 对标签进行解码，解码TLV中的T和L,确定结束位置 */
    ulRslt = SSA_DecodeTag(ppucSrc, pstTagStru);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeTL:WARNING: Tag Value Wrong");
        return ulRslt;
    }

    ulRslt = SSA_DecodeLength(ppucSrc, pucLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeTL:WARNING: Length Value Error");
        return ulRslt;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeSSDataSsCode
 功能描述  : 解码SSData中的参数SSCode
 输入参数  : VOS_UINT8          **ppucSrc            -待解码的字串
             VOS_UINT8          *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8          *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_SSDATA_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                              -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月8日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeSSDataSsCode(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                              ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有ss-Code参数项的Tag值:OCTETSTRING_TAG*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation)
           )
        {
            /*解码ss-Code参数项,解码失败则返回*/
            ulRslt = SSA_DecodeSsCode(&(pstDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataSsCode:WARNING: SSA_DecodeSsCode Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsCode    = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc              = pucCurLocation;
            pstDest->OP_SsCode    = 0;
        }
    }
    else
    {
        /*表明没有参数项ss-Code*/
        pstDest->OP_SsCode    = 0;
        ulRslt                = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeSSDataSsStatus
 功能描述  : 解码SSData中的参数SsStatus
 输入参数  : VOS_UINT8          **ppucSrc            -待解码的字串
             VOS_UINT8          *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8          *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_SSDATA_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                              -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeSSDataSsStatus(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有ss-Status参数项的Tag值:OCTETSTRING_TAG*/
        if ((4 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码SsStatus参数项*/
            ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataSsStatus:WARNING: SSA_DecodeSsStatus Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsStatus        = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_SsStatus        = 0;
        }
    }
    else
    {
        /*表明没有参数项ss-status*/
        pstDest->OP_SsStatus     = 0;
        ulRslt                   = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeSSDataSsSubScriptionOp
 功能描述  : 对SSData的参数ss-SubscriptionOption解码
 输入参数  : VOS_UINT8          **ppucSrc            -待解码的字串
             VOS_UINT8          *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8          *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_SSDATA_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                              -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeSSDataSsSubScriptionOp(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有ss-SubscriptionOption参数项的Tag值:OCTETSTRING_TAG*/
        if (((2 == gSsTagValue.iNumber) || (1 == gSsTagValue.iNumber))
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ss-SubscriptionOption参数项*/
            pstDest->SsSubScriptionOp.SubScriptionOptionChoice = (VOS_UINT8)gSsTagValue.iNumber;
            ulRslt = SSA_DecodeEnum(&(pstDest->SsSubScriptionOp.SubScriptionOptionValue), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataSsSubScriptionOp:WARNING: ss-SubscriptionOption Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsSubscriptionOp    = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                        = pucCurLocation;
            pstDest->OP_SsSubscriptionOp    = 0;
        }
    }
    else
    {
        /*表明没有参数项ss-SubscriptionOption*/
        pstDest->OP_SsSubscriptionOp    = 0;
        ulRslt                          = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeSSDataBasicServiceGroupList
 功能描述  : 对SSData的参数basicServiceGroupList解码
 输入参数  : VOS_UINT8          **ppucSrc            -待解码的字串
             VOS_UINT8          *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8          *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_SSDATA_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                              -解码的结果

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeSSDataBasicServiceGroupList(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有basicServiceGroupList参数项的Tag值:SEQUENCE_TAG*/
        if ((SEQUENCE_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码basicServiceGroupList参数项*/
            ulRslt = SSA_DecodeBasicServiceGroupList(&(pstDest->BsServGroupList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataBasicServiceGroupList:WARNING: SSA_DecodeBasicServiceGroupList Decode Failure");
                return ulRslt;
            }
            pstDest->OP_BsServGroupList     = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                        = pucCurLocation;
            pstDest->OP_BsServGroupList     = 0;
        }
    }
    else
    {
        /*表明没有参数项basicServiceGroupList*/
        pstDest->OP_BsServGroupList     = 0;
        ulRslt                          = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeSSDataDefaultPriority
 功能描述  : 对SSData的参数defaultPriority解码
 输入参数  : VOS_UINT8          **ppucSrc            -待解码的字串
             VOS_UINT8          *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8          *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_SSDATA_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                              -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeSSDataDefaultPriority(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

         /*判断是否有defaultPriority 参数项的Tag值:INTEGER_TAG*/
        if ((INTEGER_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation))
        {

            /*解码defaultPriority参数项*/
            ulRslt = SSA_DecodeDefaultPriority(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataDefaultPriority:WARNING: SSA_DecodeBasicServiceGroupList Decode Failure");
                return ulRslt;
            }
            pstDest->DefaultPrio        = (VOS_UINT8)iTmp;
            pstDest->OP_DefaultPrio     = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_DefaultPrio     = 0;
        }
    }
    else
    {
        /*表明没有参数项defaultPriority*/
         pstDest->OP_DefaultPrio    = 0;
         ulRslt                     = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeSSDataNbrUser
 功能描述  : 对SSData的参数nbrUser解码
 输入参数  : VOS_UINT8          **ppucSrc            -待解码的字串
             VOS_UINT8          *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8          *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_SSDATA_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                              -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeSSDataNbrUser(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

         /*判断是否有nbrUser参数项的Tag值:INTEGER_TAG*/
        if ((5 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码nbrUser参数项*/
            ulRslt = SSA_DecodeNbrUser(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataNbrUser:WARNING: SSA_DecodeNbrUser Decode Failure");
                return ulRslt;
            }
            pstDest->NbrUser            = (VOS_UINT8)iTmp;
            pstDest->OP_NbrUser         = 1;
        }
        else
        {
            /*最后一个参数，标签值不可能为其他参数，如果不符，则认为出错*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataNbrUser:WARNING: SSA_DecodeNbrUser Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*表明没有参数项nbrUser*/
        pstDest->OP_NbrUser     = 0;
        ulRslt                  = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeFwdFeatureBasicService
 功能描述  : 对ForwardingFeature的参数basicService解码
 输入参数  : VOS_UINT8              **ppucSrc            -待解码的字串
             VOS_UINT8              *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8              *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_FWDFEATURE_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                  -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeFwdFeatureBasicService(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有basicService参数项的Tag值:0x82, 0x83*/
        if (((2 == gSsTagValue.iNumber)||(3 == gSsTagValue.iNumber))
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码basicService参数项,解码失败则返回*/
            ulRslt = SSA_DecodeBasicService(&(pstDest->BsService), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureBasicService:WARNING: SSA_DecodeBasicService Decode Failure");
                return ulRslt;
            }
            pstDest->OP_BsService         = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                      = pucCurLocation;
            pstDest->OP_BsService         = 0;
        }
    }
    else
    {
        /*表明没有basicService参数项*/
        pstDest->OP_BsService         = 0;
        ulRslt                        = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeFwdFeatureSsStatus
 功能描述  : 对ForwardingFeature的参数ss-Status解码
 输入参数  : VOS_UINT8              **ppucSrc            -待解码的字串
             VOS_UINT8              *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8              *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_FWDFEATURE_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                  -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeFwdFeatureSsStatus(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有ss-Status参数项的Tag值:0x84*/
        if ((4 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ss-Status参数项,解码失败则返回*/
            ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureSsStatus:WARNING: SSA_DecodeSsStatus Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsStatus        = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_SsStatus        = 0;
        }
    }
    else
    {
        /*表明没有参数项ss-status*/
        pstDest->OP_SsStatus        = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeFwdFeatureForwardedToNumber
 功能描述  : 对ForwardingFeature的参数forwardedToNumber解码
 输入参数  : VOS_UINT8              **ppucSrc            -待解码的字串
             VOS_UINT8              *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8              *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_FWDFEATURE_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                  -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeFwdFeatureForwardedToNumber(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有forwardedToNumber参数项的Tag值:0x85*/
        if ((5 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码forwardedToNumber参数项，解码失败则返回*/
            ulRslt = SSA_DecodeForwardedToNumber(&(pstDest->NumType), pstDest->aucFwdToNum, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureForwardedToNumber:WARNING: SSA_DecodeForwardedToNumber Decode Failure");
                return ulRslt;
            }
            pstDest->OP_NumType         = 1;
            pstDest->OP_FwdToNum        = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_NumType         = 0;
            pstDest->OP_FwdToNum        = 0;
        }
    }
    else
    {
        /*表明没有forwardedToNumber参数项*/
        pstDest->OP_NumType         = 0;
        pstDest->OP_FwdToNum        = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeFwdFeatureForwardedToSubaddress
 功能描述  : 对ForwardingFeature的参数forwardedToSubaddress解码
 输入参数  : VOS_UINT8              **ppucSrc            -待解码的字串
             VOS_UINT8              *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8              *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_FWDFEATURE_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                  -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeFwdFeatureForwardedToSubaddress(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有forwardedToSubaddress参数项的Tag值:0x88*/
        if ((8 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码forwardedToSubaddress参数项,解码失败则返回*/
            ulRslt = SSA_DecodeForwardedToSubaddress(&(pstDest->SubAddrType), pstDest->aucFwdToSubAddr, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureForwardedToSubaddress:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SubAddrType       = 1;
            pstDest->OP_FwdToSubAddr      = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                      = pucCurLocation;
            pstDest->OP_SubAddrType       = 0;
            pstDest->OP_FwdToSubAddr      = 0;
        }
    }
    else
    {
        /*表明没有forwardedToSubaddress参数项*/
        pstDest->OP_SubAddrType       = 0;
        pstDest->OP_FwdToSubAddr      = 0;
        ulRslt = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeFwdFeatureForwardingOptions
 功能描述  : 对ForwardingFeature的参数forwardingOptions解码
 输入参数  : VOS_UINT8              **ppucSrc            -待解码的字串
             VOS_UINT8              *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8              *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_FWDFEATURE_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                  -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeFwdFeatureForwardingOptions(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有forwardingOptions参数项的Tag值:0x86*/
        if ((6 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码forwardingOptions参数项,解码失败则返回*/
            ulRslt = SSA_DecodeForwardingOptions(&(pstDest->FwdOption), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeature:WARNING: SSA_DecodeForwardingOptions Decode Failure");
                return ulRslt;
            }
            pstDest->OP_FwdOption       = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_FwdOption       = 0;
        }
    }
    else
    {
        /*表明没有forwardingOptions参数项*/
        pstDest->OP_FwdOption       = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeFwdFeatureNoReplyConditionTime
 功能描述  : 对ForwardingFeature的参数noReplyConditionTime解码
 输入参数  : VOS_UINT8              **ppucSrc            -待解码的字串
             VOS_UINT8              *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8              *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_FWDFEATURE_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                  -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeFwdFeatureNoReplyConditionTime(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

       /*判断是否有noReplyConditionTime参数项的Tag值:0x87*/
        if ((7 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码noReplyConditionTime参数项，失败则返回*/
            ulRslt = SSA_DecodeNoReplyConditionTime(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureNoReplyConditionTime:WARNING: SSA_DecodeNoReplyConditionTime Decode Failure");
                return ulRslt;
            }
            pstDest->NoRepCondTime      = (VOS_UINT8)iTmp;
            pstDest->OP_NoRepCondTime   = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_NoRepCondTime   = 0;
        }
    }
    else
    {
        /*表明没有noReplyConditionTime参数项*/
        pstDest->OP_NoRepCondTime   = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeFwdFeatureLongForwardedToNumber
 功能描述  : 对ForwardingFeature的参数longForwardedToNumber解码
 输入参数  : VOS_UINT8              **ppucSrc            -待解码的字串
             VOS_UINT8              *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8              *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_FWDFEATURE_STRU *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                  -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeFwdFeatureLongForwardedToNumber(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

         /*判断是否有longForwardedToNumber参数项的Tag值:0x89*/
        if ((9 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码longForwardedToNumber参数项,解码失败则返回*/
            ulRslt = SSA_DecodeLongForwardedToNumber(&(pstDest->LongFwdNumType), pstDest->aucLongFwdToNum, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureLongForwardedToNumber:WARNING: SSA_DecodeNoReplyConditionTime Decode Failure");
                return ulRslt;
            }
            pstDest->OP_LongFwdNumType  = 1;
            pstDest->OP_LongFwdToNum    = 1;
        }
        else
        {
            /*最后一个参数，标签值不可能为其他参数，如果不符，则认为出错*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureLongForwardedToNumber:WARNING: NoReplyConditionTime Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*表明没有longForwardedToNumber参数项*/
        pstDest->OP_LongFwdNumType  = 0;
        pstDest->OP_LongFwdToNum    = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericCliRestrictionOption
 功能描述  : 对GenericServiceInfo的参数cliRestrictionOption解码
 输入参数  : VOS_UINT8                      **ppucSrc            -待解码的字串
             VOS_UINT8                      *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8                      *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU  *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                          -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericCliRestrictionOption(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有cliRestrictionOption参数项的Tag值:ENUMERATED_TAG*/
        if ((ENUMERATED_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码cliRestrictionOption参数项,解码失败在则返回*/
            ulRslt = SSA_DecodeCliRestrictionOption(&(pstDest->CliRestrictionOp), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericServiceInfo:WARNING: SSA_DecodeCliRestrictionOption Decode Failure");
                return ulRslt;
            }
            pstDest->OP_CliStrictOp     = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_CliStrictOp     = 0;
        }
    }
    else
    {
        /*表明没有cliRestrictionOption参数项*/
        pstDest->OP_CliStrictOp     = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericMaxEntitledPriority
 功能描述  : 对GenericServiceInfo的参数maximumEntitledPriority解码
 输入参数  : VOS_UINT8                      **ppucSrc            -待解码的字串
             VOS_UINT8                      *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8                      *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU  *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                          -解码的结果

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericMaxEntitledPriority(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有maximumEntitledPriority参数项的Tag值:80*/
        if ((0 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码maximumEntitledPriority参数项*/
            ulRslt = SSA_DecodeMaxEntitledPriority(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericMaxEntitledPriority:WARNING: SSA_DecodeMaxEntitledPriority Decode Failure");
                return ulRslt;
            }
            pstDest->MaxEntitledPrio    = (VOS_UINT8)iTmp;
            pstDest->OP_MaxEntiledPrio  = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_MaxEntiledPrio  = 0;
        }

    }
    else
    {
        /*表明没有maximumEntitledPriority参数项*/
        pstDest->OP_MaxEntiledPrio  = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericDefaultPriority
 功能描述  : 对GenericServiceInfo的参数maximumEntitledPriority解码
 输入参数  : VOS_UINT8                      **ppucSrc            -待解码的字串
             VOS_UINT8                      *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8                      *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU  *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                          -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericDefaultPriority(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有defaultPriority参数项的Tag值:81*/
        if ((1 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码defaultPriority参数项,解码失败则退出*/
            ulRslt = SSA_DecodeDefaultPriority(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericDefaultPriority:WARNING: SSA_DecodeDefaultPriority Decode Failure");
                return ulRslt;
            }
            pstDest->DefaultPrio        = (VOS_UINT8)iTmp;
            pstDest->OP_DefaultPrio     = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_DefaultPrio     = 0;
        }
    }
    else
    {
        /*表明没有defaultPriority参数项*/
        pstDest->OP_DefaultPrio     = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericCcbsFeatureList
 功能描述  : 对GenericServiceInfo的参数ccbs-FeatureList解码
 输入参数  : VOS_UINT8                      **ppucSrc            -待解码的字串
             VOS_UINT8                      *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8                      *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU  *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                          -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericCcbsFeatureList(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有ccbs-FeatureList参数项的Tag值:0x82*/
        if ((2 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ccbs-FeatureList参数项,解码失败则退出*/
            ulRslt = SSA_DecodeCcbsFeatureList(&(pstDest->CcbsFeatureList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericCcbsFeatureList:WARNING: SSA_DecodeCcbsFeatureList Decode Failure");
                return ulRslt;
            }
            pstDest->OP_CcbsFeatureList = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc = pucCurLocation;
            pstDest->OP_CcbsFeatureList = 0;
        }
    }
    else
    {
        /*表明没有ccbs-FeatureList参数项*/
        pstDest->OP_CcbsFeatureList = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericNbrSB
 功能描述  : 对GenericServiceInfo的参数nbrSB解码
 输入参数  : VOS_UINT8                      **ppucSrc            -待解码的字串
             VOS_UINT8                      *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8                      *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU  *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                          -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericNbrSB(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有nbrSB参数项的Tag值:0x83*/
        if ((3 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码nbrSB参数项,解码失败则退出*/
            ulRslt = SSA_DecodeNbrSB(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrSB:WARNING: SSA_DecodeNbrSB Decode Failure");
                return ulRslt;
            }
            pstDest->NbrSb              = (VOS_UINT8)iTmp;
            pstDest->OP_NbrSb           = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_NbrSb           = 0;
        }
    }
    else
    {
        /*表明没有nbrSB参数项*/
        pstDest->OP_NbrSb           = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericNbrUser
 功能描述  : 对GenericServiceInfo的参数nbrUser解码
 输入参数  : VOS_UINT8                      **ppucSrc            -待解码的字串
             VOS_UINT8                      *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8                      *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU  *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                          -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericNbrUser(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有nbrUser参数项的Tag值:0x84*/
        if ((4 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码nbrUser参数项,解码失败则退出*/
            ulRslt = SSA_DecodeNbrUser(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrUser:WARNING: SSA_DecodeNbrUser Decode Failure");
                return ulRslt;
            }
            pDest->NbrUser              = (VOS_UINT8)iTmp;
            pDest->OP_NbrUser           = 1;
        }
        else
        {
            /*如果没有，则置回解码前位置，相关参数项的位域置0*/
            *ppucSrc                    = pucCurLocation;
            pDest->OP_NbrUser           = 0;
        }

    }
    else
    {
        /*表明没有nbrUser参数项*/
        pDest->OP_NbrUser           = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericNbrSN
 功能描述  : 对GenericServiceInfo的参数nbrSN解码
 输入参数  : VOS_UINT8                      **ppucSrc            -待解码的字串
             VOS_UINT8                      *pucCurLocation      -待解码字串的当前位置
             VOS_UINT8                      *pucEndLocation      -待解码字串的结束位置
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU  *pstDest             -存放解码出的参数值
 返 回 值  : VOS_UINT32                                          -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericNbrSN(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断是否有nbrSN参数项的Tag值:0x85*/
        if ((5 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码nbrUser参数项,解码失败则退出*/
            ulRslt = SSA_DecodeNbrSN(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrSN:WARNING: SSA_DecodeNbrSN Decode Failure");
                return ulRslt;
            }
            pDest->NbrSn                = (VOS_UINT8)iTmp;
            pDest->OP_NbrSn             = 1;
        }
        else
        {
            /*最后一个参数，标签值不可能为其他参数，如果不符，则认为出错*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrSN:WARNING: nbrSN Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }

    }
    else
    {
        /*表明没有nbrSN参数项*/
        pDest->OP_NbrSn             = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeSSData
 功能描述  : 解码SS空口消息facility中TAF_SS_SSDATA_STRU的参数
 输入参数  : VOS_UINT8                  **ppucSrc       -待解码的字串起始地址
             TAG_MODE                   ucTagMode       -解码的模式
 输出参数  : TAF_SS_SSDATA_STRU         *pstDest        -存放解码出的SSData数据
 返 回 值  : VOS_UINT32                                 -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月15日
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 降圈复杂度

*****************************************************************************/
VOS_UINT32 SSA_DecodeSSData(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;
    VOS_UINT32                          ulRslt;

    /*如果TAG_MODE为EXPLICIT模式*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数SsCode*/
    ulRslt = SSA_DecodeSSDataSsCode(pstDest,
                                    ppucSrc,
                                    pucCurLocation,
                                    pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数SsStatus*/
    ulRslt = SSA_DecodeSSDataSsStatus(pstDest,
                                      ppucSrc,
                                      pucCurLocation,
                                      pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数SsSubScriptionOp*/
    ulRslt = SSA_DecodeSSDataSsSubScriptionOp(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数basicServiceGroupList*/
    ulRslt = SSA_DecodeSSDataBasicServiceGroupList(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数defaultPriority*/
    ulRslt = SSA_DecodeSSDataDefaultPriority(pstDest,
                                             ppucSrc,
                                             pucCurLocation,
                                             pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }


    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数nbrUser*/
    ulRslt = SSA_DecodeSSDataNbrUser(pstDest,
                                     ppucSrc,
                                     pucCurLocation,
                                     pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeForwardingFeature
 功能描述  : 解码SS空口消息facility中TAF_SS_FWDFEATURE_STRU类型的参数
 输入参数  : VOS_UINT8                      **ppucSrc       -待解码的字串起始地址
             TAG_MODE                       ucTagMode       -解码的模式
 输出参数  : TAF_SS_FWDFEATURE_STRU         *pstDest        -存放解码出的SSData数据
 返 回 值  : VOS_UINT32                                     -解码的结果

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月15日
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2006年03月28日
    作    者   : h44270
    修改内容   : 问题单A32D02754修改
  3.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 降圈复杂度

*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardingFeature(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;
    VOS_UINT32                          ulRslt;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数SsCode*/
    ulRslt = SSA_DecodeFwdFeatureBasicService(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数SsStatus*/
    ulRslt = SSA_DecodeFwdFeatureSsStatus(pstDest,
                                          ppucSrc,
                                          pucCurLocation,
                                          pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数forwardedToNumber*/
    ulRslt = SSA_DecodeFwdFeatureForwardedToNumber(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数forwardedToSubaddress*/
    ulRslt = SSA_DecodeFwdFeatureForwardedToSubaddress(pstDest,
                                                       ppucSrc,
                                                       pucCurLocation,
                                                       pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数forwardingOptions*/
    ulRslt = SSA_DecodeFwdFeatureForwardingOptions(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数noReplyConditionTime*/
    ulRslt = SSA_DecodeFwdFeatureNoReplyConditionTime(pstDest,
                                                      ppucSrc,
                                                      pucCurLocation,
                                                      pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数longForwardedToNumber*/
    ulRslt = SSA_DecodeFwdFeatureLongForwardedToNumber(pstDest,
                                                       ppucSrc,
                                                       pucCurLocation,
                                                       pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : SSA_DecodeGenericServiceInfo
 功能描述  : 解码SS空口消息facility中TAF_SS_GENERIC_SERV_INFO_STRU类型的参数
 输入参数  : VOS_UINT8                              **ppucSrc       -待解码的字串起始地址
             TAG_MODE                               ucTagMode       -解码的模式
 输出参数  : TAF_SS_GENERIC_SERV_INFO_STRU          *pstDest        -存放解码出的SSData数据
 返 回 值  : VOS_UINT32                                             -解码的结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月15日
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2010年7月10日
    作    者   : 王毛/00166186
    修改内容   : 降圈复杂度

*****************************************************************************/
VOS_UINT32 SSA_DecodeGenericServiceInfo(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;
    VOS_UINT32                          ulRslt;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTL(ppucSrc,&gSsTagValue,&gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }
    }

    /*确定字串结束位置*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对ss-Status进行解码,解码失败则返回*/
    ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericServiceInfo:WARNING: SSA_DecodeSsStatus Decode Failure");
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数cliRestrictionOption*/
    ulRslt = SSA_DecodeGenericCliRestrictionOption(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数maximumEntitledPriority*/
    ulRslt = SSA_DecodeGenericMaxEntitledPriority(pstDest,
                                                  ppucSrc,
                                                  pucCurLocation,
                                                  pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数defaultPriority*/
    ulRslt = SSA_DecodeGenericDefaultPriority(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数ccbs-FeatureList*/
    ulRslt = SSA_DecodeGenericCcbsFeatureList(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数nbrSB*/
    ulRslt = SSA_DecodeGenericNbrSB(pstDest,
                                    ppucSrc,
                                    pucCurLocation,
                                    pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数nbrUser*/
    ulRslt = SSA_DecodeGenericNbrUser(pstDest,
                                      ppucSrc,
                                      pucCurLocation,
                                      pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数nbrSN*/
    ulRslt = SSA_DecodeGenericNbrSN(pstDest,
                                    ppucSrc,
                                    pucCurLocation,
                                    pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}



/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted SSA_GetDcsMsgCoding */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
