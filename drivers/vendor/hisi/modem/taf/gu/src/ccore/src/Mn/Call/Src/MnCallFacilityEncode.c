/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallFacilityDecode.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月20日
  最近修改   : 2007年9月20日
  功能描述   : 实现CS呼叫相关的API接口函数
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Taf_Ssa_DecodeDef.h"
#include "MnCallFacilityDecode.h"
#include "MnCallFacilityEncode.h"
#include "MnComm.h"
#include "MnCall.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/


/*****************************************************************************
  4 宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_FACILITY_ENCODE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
/*****************************************************************************
  5 变量定义
*****************************************************************************/
MN_CALL_SS_ID_TABLE_STRU    g_stCallInvokeIdTable[MN_CALL_MAX_INVOKE_NUM];

/*lint -save -e958 */

/*****************************************************************************
  6 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_CALL_SsCdArgEncode
 功能描述  : 编码呼叫偏转参数
 输入参数  : pArg - 要编码的呼叫偏转参数
 输出参数  : pDest - 编码的目的缓存
 返 回 值  : 编码后参数的长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsCdArgEncode(
    const MN_CALL_SS_CD_ARG_STRU        *pstArg,
    VOS_UINT8                           *pucDest
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulArgLen = 0;

    if ((0 == pstArg->ucNumberLen) ||
        (pstArg->ucNumberLen > MN_CALL_SS_CD_NUM_LEN) ||
        (pstArg->ucSubAddrLen > MN_CALL_SS_CD_SUB_ADDR_LEN))
    {
        MN_WARN_LOG("MN_CALL_SsCdArgEncode:Bad parameter for call deflecting");
        return 0;
    }

    /*lint -e961*/
    /* 编码callDeflectionArg结构 */
    pucDest[ulArgLen++] = 0x30;          /* tag of SEQUENCE */
    pucDest[ulArgLen++] = 0;             /* length, 最后填写 */

    /* 编码deflectedToNumber */
    pucDest[ulArgLen++] = 0x80;
    pucDest[ulArgLen++] = pstArg->ucNumberLen;
    for (i=0; i<pstArg->ucNumberLen; i++)
    {
        pucDest[ulArgLen++] = pstArg->aucNumber[i];
    }

    /* 编码deflectedToSubaddress */
    if (pstArg->ucSubAddrLen > 0)
    {
        pucDest[ulArgLen++] = 0x81;
        pucDest[ulArgLen++] = pstArg->ucSubAddrLen;
        for (i=0; i<pstArg->ucSubAddrLen; i++)
        {
            pucDest[ulArgLen++] = pstArg->aucSubAddr[i];
        }
    }
    /*lint +e961*/

    pucDest[1] = (VOS_UINT8)(ulArgLen - 2);

    return ulArgLen;
}

#if 0
/*****************************************************************************
 函 数 名  : MN_CALL_SsRegCcEntryArgEncode
 功能描述  : 编码accessRegisterCCEntry(注册CCBS)参数
 输入参数  : 无
 输出参数  : pDest - 编码的目的缓存
 返 回 值  : 编码后参数的长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年1月12日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsRegCcEntryArgEncode(
    VOS_UINT8                           *pucDest
)
{
    VOS_UINT32                          ulArgLen = 0;

    pucDest[ulArgLen++] = 0x30;          /* tag of SEQUENCE */
    pucDest[ulArgLen++] = 0;             /* 无内容 */

    return ulArgLen;
}
#endif

/*****************************************************************************
 Prototype      : MN_CALL_SsCugInfoArgEncode
 Description    : 编码Cug-info参数
 Input          : pDest - 编码的目的缓存
                  pArg - 要编码的CUG参数
 Output         :
 Return Value   : 编码后参数的长度
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2006-02-28
    Author      : D49431
    Modification: Created function

  2.Date        : 2006-04-14
    Author      : D49431
    Modification: 根据问题单A32D02961修改

  3.Date        : 2006-12-11
    Author      : D49431
    Modification: 根据问题单A32D07850修改
  4.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsCugInfoArgEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_CUG_CFG_STRU          *pstArg
)
{
    VOS_UINT32                          ulArgLen = 0;
    VOS_UINT8                           *pucSeqLen;

    /*lint -e961*/
    /*添加SEQUENCE的Tag*/
    pucDest[ulArgLen++] = 0x30;                /*cug-info tag*/
    pucSeqLen = &pucDest[ulArgLen++];
    *pucSeqLen = 0;

    /* 目前只支持Index 0~9 */
    if (VOS_TRUE == pstArg->bIndexPresent)
    {
        if (pstArg->ulIndex <= 9)
        {
            /*编码cug-index参数*/
            pucDest[ulArgLen++] = 0x80;            /*tag*/
            pucDest[ulArgLen++] = 1;               /*length*/
            pucDest[ulArgLen++] = (VOS_UINT8)pstArg->ulIndex;

            *pucSeqLen += 3;
        }
    }

    if (VOS_TRUE == pstArg->bSuppressOA)
    {
        /*编码suppressOA参数*/
        pucDest[ulArgLen++] = 0x82;            /*tag*/
        pucDest[ulArgLen++] = 0;               /*VOS_NULL_PTR*/

        *pucSeqLen += 2;
    }

    if (VOS_TRUE == pstArg->bSuppressPrefer)
    {
        /*编码suppressPrefCUG参数*/
        pucDest[ulArgLen++] = 0x81;            /*tag*/
        pucDest[ulArgLen++] = 0;               /*VOS_NULL_PTR*/

        *pucSeqLen += 2;
    }

    /*lint +e961*/
    return ulArgLen;
}


/*****************************************************************************
 Prototype      : MN_CALL_SsInvokeArgEncode
 Description    : 编码Invoke参数
 Input          : ucOpCode - 操作码
                  punArg   - 要编码的CUG参数
 Output         : pucDest  - 编码结果的目的缓存
 Return Value   : 编码结果
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-02-26
    Author      : D49431
    Modification: Created function
  2.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsInvokeArgEncode(
    VOS_UINT8                            ucOpCode,
    const MN_CALL_SS_COMPONENT_ARG_UNION *punArg,
    VOS_UINT8                            *pucDest
)
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if (punArg == VOS_NULL_PTR)
    {
        return 0;
    }

    switch(ucOpCode)
    {
    case MN_CALL_SS_CUG_OPERATION:
        return MN_CALL_SsCugInfoArgEncode(pucDest, &punArg->cugInfoArg);

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    case MN_CALL_SS_CD_OPERATION:
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCallDeflectionSupportFlg )
        {
            return MN_CALL_SsCdArgEncode(&punArg->stCdArg, pucDest);
        }
        else
        {
            return 0;
        }

    case MN_CALL_SS_REG_CC_ENTRY_OPERATION:
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg )
        {
            return 0;
        }
        else
        {
            return 0;
        }

   /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    default:
        return 0;
    }

}


/*****************************************************************************
 Prototype      : MN_CALL_SsComponentEncode()
 Description    : Component消息编码
 Input          : punComponent - 需要编码的component的内容
 Output         : pucDest      - 编码后的缓存指针
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsComponentEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
)
{
    VOS_UINT32                          ulComponentLen = 0;
    /*lint -e961*/
    switch(punComponent->ucCompType)
    {
    case MN_CALL_SS_INVOKE_TYPE_TAG:
        pucDest[ulComponentLen++] = MN_CALL_SS_INVOKE_TYPE_TAG;
        pucDest[ulComponentLen++] = 0;
        pucDest[ulComponentLen++] = MN_CALL_SS_INVOKE_ID_TAG;
        pucDest[ulComponentLen++] = 1;
        pucDest[ulComponentLen++] = punComponent->invokeComp.ucInvokeId;
        if (punComponent->invokeComp.bitOpLinkId)
        {
            pucDest[ulComponentLen++] = MN_CALL_SS_LINKED_ID_TAG;
            pucDest[ulComponentLen++] = 1;
            pucDest[ulComponentLen++] = punComponent->invokeComp.ucLinkId;
        }
        pucDest[ulComponentLen++] = MN_CALL_SS_OPERATION_CODE_TAG;
        pucDest[ulComponentLen++] = 1;
        pucDest[ulComponentLen++] = punComponent->invokeComp.ucOperateCode;
        ulComponentLen +=
            MN_CALL_SsInvokeArgEncode(punComponent->invokeComp.ucOperateCode,
                                   &punComponent->invokeComp.unArg,
                                   &pucDest[ulComponentLen]);

        pucDest[1] = (VOS_UINT8)(ulComponentLen - 2);
        break;

    case MN_CALL_SS_RETURN_RESULT_TYPE_TAG:
        break;

    case MN_CALL_SS_RETURN_ERROR_TYPE_TAG:
        break;

    case MN_CALL_SS_REJECT_TYPE_TAG:
        break;

    default:
        break;
    }
    /*lint +e961*/
    return ulComponentLen;
}



/*****************************************************************************
 Prototype      : MN_CALL_FacilityEncode()
 Description    : Facility消息编码
 Input          : punComponent - 需要编码的component的内容
                : ucTi         - Ti值
 Output         : pucDest      - 编码后的缓存指针
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
  2.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
*****************************************************************************/
VOS_UINT32 MN_CALL_FacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
)
{
    return MN_CALL_SsComponentEncode(&pucDest[0], punComponent);
}

/*****************************************************************************
 Prototype      : MN_CALL_SimpleFacilityEncode()
 Description    : Facility消息编码
 Input          : punComponent - 需要编码的component的内容

 Output         : pucDest      - 编码后的缓存指针
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
  2.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
*****************************************************************************/
VOS_VOID MN_CALL_SimpleFacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
)
{
    pucDest[0] = (VOS_UINT8)MN_CALL_SsComponentEncode(&pucDest[1], punComponent);
}

/*****************************************************************************
 Prototype      : MN_CALL_InvokeId_Free()
 Description    : 分配InvokeId
 Input          : ucInvokeId: 要释放的ucInvokeId
 Output         :
 Return Value   : SPEECH_SUCCESS  释放成功
                : SPEECH_ERROR    释放失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_VOID MN_CALL_InvokeId_Free( VOS_UINT8 ucInvokeId )
{
    g_stCallInvokeIdTable[ucInvokeId].bUsed      = VOS_FALSE;
    g_stCallInvokeIdTable[ucInvokeId].ucCallId   = MN_CALL_INVALID_TI;
    g_stCallInvokeIdTable[ucInvokeId].ucInvokeId = MN_CALL_MAX_INVOKE_NUM;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

