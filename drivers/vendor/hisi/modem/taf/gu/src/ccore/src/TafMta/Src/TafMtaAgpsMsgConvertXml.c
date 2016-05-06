/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaAgpsMsgConvertXml.c
  版 本 号   : 初稿
  作    者   : 罗小烽 L47619
  生成日期   : 2012年7月11日
  最近修改   :
  功能描述   : 提供将接入层发来的消息结构转换成XML树结构的功能
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月11日
    作    者   : 李紫剑 l00198894
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafMtaComm.h"
#include "TafMtaAgps.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_AGPS_MSG_CONVERT_XML_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_AGPS)

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_CreateANodeAndSetLabel
功能描述  : 创建一个节点并设置标签
输入参数  : pstXmlCtx         XML上下文
            *pcNodeLabel      标签
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : L47619/D00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_CreateANodeAndSetLabel(
    XML_COMM_CTX_STRU                  *pstXmlCtx,
    VOS_CHAR                           *pcNodeLabel
)
{
    XML_COMM_NODE_STRU                 *pstNode;
    VOS_UINT32                          ulReturnValue;

    /* 创建子节点 */
    pstNode = XML_COMM_CreateANode(pstXmlCtx);
    if (VOS_NULL_PTR == pstNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_CreateANodeAndSetLabel: WARNING:Create A Node fail!");
        return VOS_NULL_PTR;
    }

    /* 设置标签 */
    ulReturnValue = XML_COMM_SetNodeLabel(pstNode, pcNodeLabel);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_CreateANodeAndSetLabel: WARNING:Set label fail!");
        return VOS_NULL_PTR;
    }

    return pstNode;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddNewUnsignedIntLeafNode
功能描述  : 增加一个无符号整型叶子节点到当前的XML树上
输入参数  : pstXmlCommCtx     XML上下文
            pstParentNode     父节点
            pcLeafNodeLabel   叶子节点标签
            pulLeafNodeValue  叶子节点值
输出参数  : 无
返 回 值  : VOS_ERR      增加叶子节点失败
            VOS_OK       增加叶子节点成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月10日
  作    者  : h44270
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstParentNode,
    VOS_CHAR                           *pcLeafNodeLabel,
    VOS_UINT32                          ulLeafNodeValue
)
{
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 创建节点并设置标签 */
    pstChildNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, pcLeafNodeLabel);
    if (VOS_NULL_PTR == pstChildNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddNewUnsignedIntLeafNode: WARNING: Create Leaf Node fail!");
        return VOS_ERR;
    }

    /* 设置标签值 */
    ulReturnValue = XML_COMM_SetNodeValueUInt(pstChildNode, ulLeafNodeValue, pstXmlCommCtx);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddNewUnsignedIntLeafNode: WARNING: Set node value fail!");
        return VOS_ERR;
    }

    /* 将子结构并挂到当前节点下 */
    ulReturnValue = XML_COMM_AddAChildNode(pstParentNode, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddNewUnsignedIntLeafNode: WARNING: Add child fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddNewSignedIntLeafNode
功能描述  : 增加一个有符号整型叶子节点到当前的XML树上
输入参数  : pstXmlCommCtx     XML上下文
            pstParentNode     父节点
            pcLeafNodeLabel   叶子节点标签
            plLeafNodeValue   叶子节点值
输出参数  : 无
返 回 值  : VOS_ERR      增加叶子节点失败
            VOS_OK       增加叶子节点成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddNewSignedIntLeafNode(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstParentNode,
    VOS_CHAR                           *pcLeafNodeLabel,
    VOS_INT32                           lLeafNodeValue
)
{
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 创建节点并设置标签 */
    pstChildNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, pcLeafNodeLabel);
    if (VOS_NULL_PTR == pstChildNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddNewSignedIntLeafNode: WARNING: Create Leaf Node fail!");
        return VOS_ERR;
    }

    /* 设置标签值 */
    ulReturnValue = XML_COMM_SetNodeValueInt(pstChildNode, lLeafNodeValue, pstXmlCommCtx);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddNewSignedIntLeafNode: WARNING: Set node value fail!");
        return VOS_ERR;
    }

    /* 将子结构并挂到当前节点下 */
    ulReturnValue = XML_COMM_AddAChildNode(pstParentNode, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddNewSignedIntLeafNode: WARNING: Add child fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertAssistData
功能描述  : 将AGPS_ASSIST_DATA_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstAssistData   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAssistData(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ASSIST_DATA_STRU              *pstAssistData
)
{
    XML_COMM_NODE_STRU                 *pstNodeAssistData;
    XML_COMM_NODE_STRU                 *pstNodeGpsAssist;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*  <!ELEMENT assist_data (GPS_assist?,msr_assist_data?,system_info_assist_data?,more_assist_data?,
           ext_container?,rel98_assist_data_ext?,rel5_assist_data_ext?,rel7_assist_data_ext?)>*/

    /* 创建一个节点并设置标签 */
    pstNodeAssistData = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ASSIST_DATA);
    if (VOS_NULL_PTR == pstNodeAssistData)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAssistData: WARNING: Create MTA_AGPS_LABEL_ASSIST_DATA fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    if (VOS_TRUE == pstAssistData->bitOpGpsAssist)
    {
        pstNodeGpsAssist = TAF_MTA_AGPS_ConvertGpsAssist(pstXmlCommCtx, &pstAssistData->stGpsAssist);
    }
    else
    {
        /* 若bitOpGpsAssit为0，则逻辑有误，终止处理，直接退出 */
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAssistData: WARNING: bitOpGpsAssit is 0!");
        return VOS_NULL_PTR;
    }

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeAssistData, pstNodeGpsAssist, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAssistData: WARNING: Add MTA_AGPS_LABEL_GPS_ASSIST fail!");
        return VOS_NULL_PTR;
    }
    return pstNodeAssistData;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddGpsAssistChildNodesPartOne
功能描述  : 将AGPS_GPS_ASSIST_STRU结构体属性转换为树的子节点，
            包括<status_health>、<BTS_clock_drift>、<ref_time>、
            <location_parameters>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeGpsAssist            属性转换后挂载的父节点
            pstGpsAssist                待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddGpsAssistChildNodesPartOne(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeGpsAssist,
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist
)
{
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 转换子结构并挂到当前节点下 */
    /* <status_health> */
    if (VOS_TRUE == pstGpsAssist->bitOpStatusHealth)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeGpsAssist,
                                                             MTA_AGPS_LABEL_STATUS_HEALTH,
                                                             (VOS_UINT32)pstGpsAssist->enStatusHealth))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_STATUS_HEALTH fail!");
            return VOS_ERR;
        }
    }

    /* <BTS_clock_drift> */
    if (VOS_TRUE == pstGpsAssist->bitOpBtsClockDrift)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeGpsAssist,
                                                            MTA_AGPS_LABEL_BTS_CLOCK_DRIFT,
                                                            (VOS_UINT32)pstGpsAssist->usBtsClockDrift))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_BTS_CLOCK_DRIFT fail!");
            return VOS_ERR;
        }
    }

    /* <ref_time> */
    if (VOS_TRUE == pstGpsAssist->bitOpRefTime)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertRefTime(pstXmlCommCtx, &pstGpsAssist->stRefTime);
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartOne: WARNING: Add MTA_AGPS_LABEL_REF_TIME fail!");
            return VOS_ERR;
        }
    }

    /* <location_parameters> */
    if (VOS_TRUE == pstGpsAssist->bitOpLocationPara)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertLocationPara(pstXmlCommCtx, &pstGpsAssist->stLocationPara);
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartOne: WARNING: Add MTA_AGPS_LABEL_LOCATION_PARAMENTERS fail!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddGpsAssistChildNodesPartTwo
功能描述  : 将AGPS_GPS_ASSIST_STRU结构体属性转换为树的子节点
            包括<DGPS_corrections>、<nav_model_elem>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeGpsAssist            属性转换后挂载的父节点
            pstGpsAssist                待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddGpsAssistChildNodesPartTwo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeGpsAssist,
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist
)
{
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_UINT32                          ulLoop;

    /* <DGPS_corrections> */
    if (VOS_TRUE == pstGpsAssist->bitOpDgpsCorrection)
    {
         /* ulDgpsCorrectionNum 大于 1 填写第 0 组数据 */
        if (0 == pstGpsAssist->stDgpsCorrection.ulDgpsCorrectionNum)
        {
            return VOS_ERR;
        }
        else
        {
            pstChildNode = TAF_MTA_AGPS_ConvertUpDgpsCorrection(pstXmlCommCtx,
                                                                &pstGpsAssist->stDgpsCorrection.astUpDgpsCorrection[0]);
            ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
            if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartTwo: WARNING: Add MTA_AGPS_LABEL_DGPS_CORRECTIONS fail!");
                return VOS_ERR;
            }
        }
    }

    /* <nav_model_elem> */
    if (VOS_TRUE == pstGpsAssist->bitOpNavModelElem)
    {
        for (ulLoop = 0; ulLoop < pstGpsAssist->stNavModelElem.ulNavModelElemNum; ulLoop++)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertNavModelElem(pstXmlCommCtx,
                                                            &pstGpsAssist->stNavModelElem.astNavModelElem[ulLoop]);
            ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
            if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartTwo: WARNING: Add MTA_AGPS_LABEL_NAV_MODEL_ELEM fail!");
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddGpsAssistChildNodesPartThree
功能描述  : 将AGPS_GPS_ASSIST_STRU结构体属性转换为树的子节点
            包括<ionospheric_model>、<UTC_model>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeGpsAssist            属性转换后挂载的父节点
            pstGpsAssist                待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddGpsAssistChildNodesPartThree(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeGpsAssist,
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist
)
{
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <ionospheric_model> */
    if (VOS_TRUE == pstGpsAssist->bitOpIonosphericModel)
    {
        /* 判断模式 */
        if (AGPS_IONOSPHERIC_MODEL_TYPE_RRLP == pstGpsAssist->enIonosphericModelChoice)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertRrlpIonosphericModel(pstXmlCommCtx,
                                                                    &pstGpsAssist->u1.stRrlpIonosphericModel);
        }
        else if (AGPS_IONOSPHERIC_MODEL_TYPE_RRC == pstGpsAssist->enIonosphericModelChoice)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertRrcIonosphericModel(pstXmlCommCtx,
                                                                   &pstGpsAssist->u1.stRrcIonosphericModel);
        }
        else
        {
            MTA_WARNING1_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartThree: WARNING: Invalid enIonosphericModelChoice ", pstGpsAssist->enIonosphericModelChoice);
            return VOS_ERR;
        }

        /* 将子结构并挂到当前节点下 */
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartThree: WARNING: Add MTA_AGPS_LABEL_IONOSPHERIC_MODEL fail!");
            return VOS_ERR;
        }
    }

    /* <UTC_model> */
    if (VOS_TRUE == pstGpsAssist->bitOpUtcModel)
    {
        /* 判断模式 */
        if (AGPS_UTC_MODEL_TYPE_RRLP == pstGpsAssist->enUtcModelChoice)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertRrlpUtcModel(pstXmlCommCtx, &pstGpsAssist->u2.stRrlpUtcModel);
        }
        else if (AGPS_UTC_MODEL_TYPE_RRC == pstGpsAssist->enUtcModelChoice)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertRrcUtcModel(pstXmlCommCtx, &pstGpsAssist->u2.stRrcUtcModel);
        }
        else
        {
            MTA_WARNING1_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartThree: WARNING: Invalid enIonosphericModelChoice ", pstGpsAssist->enUtcModelChoice);
            return VOS_ERR;
        }

        /* 将子结构并挂到当前节点下 */
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartThree: WARNING: Add MTA_AGPS_LABEL_UTC_MODEL fail!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddGpsAssistChildNodesPartFour
功能描述  : 将AGPS_GPS_ASSIST_STRU结构体属性转换为树的子节点
            包括<almanac>、<acqu_assist>、<GPS_rt_integrity>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeGpsAssist            属性转换后挂载的父节点
            pstGpsAssist                待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddGpsAssistChildNodesPartFour(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeGpsAssist,
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist
)
{
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <almanac> */
    if (VOS_TRUE == pstGpsAssist->bitOpAlmanac)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertAlmanac(pstXmlCommCtx, &pstGpsAssist->stAlmanac);
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartFour: WARNING Add MTA_AGPS_LABEL_ALMANAC fail!");
            return VOS_ERR;
        }
    }

    /* <acqu_assist> */
    if (VOS_TRUE == pstGpsAssist->bitOpAcquAssist)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertAcquAssist(pstXmlCommCtx, &pstGpsAssist->stAcquAssist);
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartFour: WARNING Add MTA_AGPS_LABEL_ACPU_ASSIST fail!");
            return VOS_ERR;
        }
    }

    /* <GPS_rt_integrity> */
    if (VOS_TRUE == pstGpsAssist->bitOpGpsRealTimeIntegrity)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertGpsRealTimeIntegrity(pstXmlCommCtx,
                                                            &pstGpsAssist->stGpsRealTimeIntegrity);
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeGpsAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_AddGpsAssistChildNodesPartFour: WARNING Add MTA_AGPS_LABEL_GPS_RT_INTEGRITY fail!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertGpsAssist
功能描述  : 将AGPS_GPS_ASSIST_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstGpsAssist    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsAssist(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist
)
{
    XML_COMM_NODE_STRU                 *pstNodeGpsAssist;

    /* <!ELEMENT GPS_assist (status_health?,BTS_clock_drift?,ref_time?,location_parameters?,
         DGPS_corrections?,nav_model_elem*,ionospheric_model?,UTC_model?,almanac?,acqu_assist?,
         GPS_rt_integrity?)> */

    /* 调用XML API提供的接口，创建<assist_data> 节点并设置标签 */
    pstNodeGpsAssist = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_GPS_ASSIST);
    if (VOS_NULL_PTR == pstNodeGpsAssist)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsAssist: WARNING: Create MTA_AGPS_LABEL_GPS_ASSIST fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part1 */
    if (VOS_OK != TAF_MTA_AGPS_AddGpsAssistChildNodesPartOne(pstXmlCommCtx,
                                                             pstNodeGpsAssist,
                                                             pstGpsAssist))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsAssist: WARNING: Add Child Nodes Part1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part2 */
    if (VOS_OK != TAF_MTA_AGPS_AddGpsAssistChildNodesPartTwo(pstXmlCommCtx,
                                                             pstNodeGpsAssist,
                                                             pstGpsAssist))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsAssist: WARNING: Add Child Nodes Part2 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part3 */
    if (VOS_OK != TAF_MTA_AGPS_AddGpsAssistChildNodesPartThree(pstXmlCommCtx,
                                                               pstNodeGpsAssist,
                                                               pstGpsAssist))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsAssist: WARNING: Add Child Nodes Part3 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part4 */
    if (VOS_OK != TAF_MTA_AGPS_AddGpsAssistChildNodesPartFour(pstXmlCommCtx,
                                                              pstNodeGpsAssist,
                                                              pstGpsAssist))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsAssist: WARNING: Add Child Nodes Part4 fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeGpsAssist;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRefTime
功能描述  : 将AGPS_REFERENCE_TIME_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstRefTime    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRefTime(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_REFERENCE_TIME_STRU           *pstRefTime
)
{
    XML_COMM_NODE_STRU                 *pstNodeRefTime;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_UINT32                          ulLoop;

    /* <!ELEMENT ref_time (GPS_time,GSM_time?,GPS_TOW_assist*)> */

    /* 创建一个节点并设置标签 */
    pstNodeRefTime = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_REF_TIME);
    if (VOS_NULL_PTR == pstNodeRefTime)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRefTime: WARNING: Create MTA_AGPS_LABEL_REF_TIME fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertGpsTime(pstXmlCommCtx, &pstRefTime->stGpsTime);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRefTime, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRefTime: WARNING: Add MTA_AGPS_LABEL_GPS_TIME fail!");
        return VOS_NULL_PTR;
    }

    /* <GSM_time?> */
    if (VOS_TRUE == pstRefTime->bitOpGsmTime)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertGsmTime(pstXmlCommCtx, &pstRefTime->stGsmTime);
        /* 为节点增加一个子节点 */
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeRefTime, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRefTime: WARNING: Add MTA_AGPS_LABEL_GSM_TIME fail!");
            return VOS_NULL_PTR;
        }
    }

    /* <GPS_TOW_assist *> */
    if (VOS_TRUE == pstRefTime->bitOpGpsTowAssistList)
    {
        for (ulLoop = 0; ulLoop < pstRefTime->stGpsTowAssistList.ulGpsTowAssistNum; ulLoop++)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertGpsTowAssist(pstXmlCommCtx,
                                                            &pstRefTime->stGpsTowAssistList.astGpsTowAssist[ulLoop]);

            /* 为节点增加一个子节点 */
            ulReturnValue = XML_COMM_AddAChildNode(pstNodeRefTime, pstChildNode, VOS_NULL_PTR);
            if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRefTime: WARNING: Add MTA_AGPS_LABEL_GPS_TOW_ASSIST fail!");
                return VOS_NULL_PTR;
            }
        }
    }
    return pstNodeRefTime;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertGpsTime
功能描述  : 将AGPS_GPS_TIME_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstGpsTime      待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsTime(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GPS_TIME_STRU                 *pstGpsTime
)
{
    XML_COMM_NODE_STRU                 *pstNodeGpsTime;

    /*  <!ELEMENT GPS_time (GPS_TOW_msec,GPS_week)>
                <!ELEMENT GPS_TOW_msec (#PCDATA)>
                <!ELEMENT GPS_week (#PCDATA)> */

    /* 创建一个节点并设置标签 */
    pstNodeGpsTime = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_GPS_TIME);
    if (VOS_NULL_PTR == pstNodeGpsTime)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTime: WARNING: Create MTA_AGPS_LABEL_GPS_TIME fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT GPS_TOW_msec (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeGpsTime,
                                                         MTA_AGPS_LABEL_GPS_TOW_MSEC,
                                                         pstGpsTime->ulGpsTowMsec))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTime: WARNING: Create MTA_AGPS_LABEL_GPS_TOW_MSEC fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /*<!ELEMENT GPS_week (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeGpsTime,
                                                         MTA_AGPS_LABEL_GPS_WEEK,
                                                         (VOS_UINT32)(VOS_UINT32)pstGpsTime->usGpsWeek))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTime: WARNING: Create MTA_AGPS_LABEL_GPS_WEEK fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeGpsTime;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertGsmTime
功能描述  : 将AGPS_GSM_TIME_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstGpsTime      待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGsmTime(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GSM_TIME_STRU                 *pstGsmTime
)
{
    XML_COMM_NODE_STRU                 *pstNodeGsmTime;

    /* <!ELEMENT GSM_time (frame_number,time_slot_number,bit_number,BCCH_carrier?,BSIC?)>
                <!ELEMENT frame_number (#PCDATA)>
                <!ELEMENT time_slot_number (#PCDATA)>
                <!ELEMENT bit_number (#PCDATA)>
                <!ELEMENT BCCH_carrier (#PCDATA)>
                <!ELEMENT BSIC (#PCDATA)> */

    /* 创建一个节点并设置标签 */
    pstNodeGsmTime = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_GSM_TIME);
    if (VOS_NULL_PTR == pstNodeGsmTime)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGsmTime: WARNING: Create MTA_AGPS_LABEL_GSM_TIME fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT frame_number (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeGsmTime,
                                                         MTA_AGPS_LABEL_FRAME_NUMBER,
                                                         pstGsmTime->ulFrameNum))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGsmTime: WARNING: Create MTA_AGPS_LABEL_FRAME_NUMBER fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /*<!ELEMENT time_slot_number (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeGsmTime,
                                                         MTA_AGPS_LABEL_TIME_SLOT_NUMBER,
                                                         (VOS_UINT32)pstGsmTime->ucTimeSlotNum))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGsmTime: WARNING: Create MTA_AGPS_LABEL_TIME_SLOT_NUMBER fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /*<!ELEMENT bit_number (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeGsmTime,
                                                         MTA_AGPS_LABEL_BIT_NUMBER,
                                                         (VOS_UINT32)pstGsmTime->ucBitNum))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGsmTime: WARNING: Create MTA_AGPS_LABEL_BIT_NUMBER fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT BCCH_carrier (#PCDATA)> ? */
    if (VOS_TRUE == pstGsmTime->bitOpBcchCarrier)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeGsmTime,
                                                             MTA_AGPS_LABEL_BCCH_CARRIER,
                                                             (VOS_UINT32)pstGsmTime->usBcchCarrier))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGsmTime: WARNING: Create MTA_AGPS_LABEL_BCCH_CARRIER fail!");
            return VOS_NULL_PTR;
        }
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT BSIC (#PCDATA)> ? */
    if (VOS_TRUE == pstGsmTime->bitOpBsic)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeGsmTime,
                                                             MTA_AGPS_LABEL_BSIC,
                                                             (VOS_UINT32)pstGsmTime->ucBsic))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGsmTime: WARNING: Create MTA_AGPS_LABEL_BSIC fail!");
            return VOS_NULL_PTR;
        }
    }

    return pstNodeGsmTime;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertGpsTowAssist
功能描述  : 将AGPS_GPS_TOW_ASSIST_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx       XML上下文
            pstTowAssist        待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsTowAssist(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_GPS_TOW_ASSIST_STRU           *pstTowAssist
)
{
    XML_COMM_NODE_STRU                 *pstNodeTowAssist;

    /* <!ELEMENT GPS_TOW_assist (sat_id,tlm_word,anti_sp,alert,tlm_res)>
                <!ELEMENT sat_id (#PCDATA)>
                <!ELEMENT tlm_word (#PCDATA)>
                <!ELEMENT anti_sp (#PCDATA)>
                <!ELEMENT alert (#PCDATA)>
                <!ELEMENT tlm_res (#PCDATA)> */

    /* 创建一个节点并设置标签 */
    pstNodeTowAssist = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_GPS_TOW_ASSIST);
    if (VOS_NULL_PTR == pstNodeTowAssist)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTowAssist: WARNING: Create MTA_AGPS_LABEL_GPS_TOW_ASSIST fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT sat_id (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeTowAssist,
                                                         MTA_AGPS_LABEL_SAT_ID,
                                                         (VOS_UINT32)pstTowAssist->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTowAssist: WARNING: Create MTA_AGPS_LABEL_SAT_ID fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT tlm_word (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeTowAssist,
                                                         MTA_AGPS_LABEL_TLM_WORD,
                                                         (VOS_UINT32)pstTowAssist->usTlmWord))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTowAssist: WARNING: Create MTA_AGPS_LABEL_TLM_WORD fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT  anti_sp (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeTowAssist,
                                                         MTA_AGPS_LABEL_ANTI_SP,
                                                         (VOS_UINT32)pstTowAssist->enAntiSp))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTowAssist: WARNING: Create MTA_AGPS_LABEL_TLM_WORD fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alert (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeTowAssist,
                                                         MTA_AGPS_LABEL_ALERT,
                                                         (VOS_UINT32)pstTowAssist->enAlert))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTowAssist: WARNING: Create MTA_AGPS_LABEL_ALERT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT tlm_res (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeTowAssist,
                                                         MTA_AGPS_LABEL_TLM_RES,
                                                         (VOS_UINT32)pstTowAssist->ucTlmRes))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsTowAssist: WARNING: Create MTA_AGPS_LABEL_ALERT fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeTowAssist;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertLocationPara
功能描述  : 将AGPS_LOCATION_PARA_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstLocationPara 待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertLocationPara(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_LOCATION_PARA_STRU            *pstLocationPara
)
{
    XML_COMM_NODE_STRU                 *pstNodeLocationPara;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT location_parameters (time?,direction?,shape_data,velocity_data?)> */

    /* 创建一个节点并设置标签 */
    pstNodeLocationPara = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_LOCATION_PARAMENTERS);
    if (VOS_NULL_PTR == pstNodeLocationPara)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLocationPara: WARNING:Create MTA_AGPS_LABEL_LOCATION_PARAMENTERS fail!");
        return VOS_NULL_PTR;
    }

    if (VOS_TRUE == pstLocationPara->bitOpTime)
    {
        /* 转换子结构并挂到当前节点下 */
        /* time? */
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeLocationPara,
                                                             MTA_AGPS_LABEL_TIME,
                                                             pstLocationPara->ulTime))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLocationPara: WARNING: Create MTA_AGPS_LABEL_TIME fail!");
            return VOS_NULL_PTR;
        }
    }

    if (VOS_TRUE == pstLocationPara->bitOpDirection)
    {
        /* 转换子结构并挂到当前节点下 */
        /* direction? */
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeLocationPara,
                                                             MTA_AGPS_LABEL_DIRECTION,
                                                             (VOS_UINT32)pstLocationPara->ucDirection))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLocationPara: WARNING: Create MTA_AGPS_LABEL_DIRECTION fail!");
            return VOS_NULL_PTR;
        }
    }

    /* 转换子结构并挂到当前节点下 */
    /* shape_data */
    pstChildNode = TAF_MTA_AGPS_ConvertShapeData(pstXmlCommCtx, &pstLocationPara->stShapeData);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeLocationPara, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLocationPara: WARNING: Add MTA_AGPS_LABEL_SHAPE_DATA fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeLocationPara;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertShapeData
功能描述  : 将AGPS_SHAPE_DATA_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstShapeData    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertShapeData(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_SHAPE_DATA_STRU               *pstShapeData
)
{
    XML_COMM_NODE_STRU                 *pstNodeShapeData;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT shape_data (ellipsoid_point|ellipsoid_point_uncert_circle
                             |ellipsoid_point_uncert_ellipse|polygon|ellipsoid_point_alt
                             |ellipsoid_point_alt_uncertellipse|ellips_arc)> */

    /* 创建一个节点并设置标签 */
    pstNodeShapeData = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_SHAPE_DATA);
    if (VOS_NULL_PTR == pstNodeShapeData)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertShapeData: WARNING:Create MTA_AGPS_LABEL_SHAPE_DATA fail!");
        return VOS_NULL_PTR;
    }

    switch (pstShapeData->enEstimatTypeChoice)
    {
        case AGPS_POSITION_ESTIMAT_ELLIP_POINT:
            pstChildNode = TAF_MTA_AGPS_ConvertEllipPoint(pstXmlCommCtx, &pstShapeData->u.stEllipPoint);
            break;
        case AGPS_POSITION_ESTIMAT_ELLIP_POINT_UNCERT_CIRCLE:
            pstChildNode = TAF_MTA_AGPS_ConvertEllipPointUncertCircle(pstXmlCommCtx,
                                                                      &pstShapeData->u.stEllipPointUncertCircle);
            break;
        case AGPS_POSITION_ESTIMAT_ELLIP_POINT_UNCERT_ELLIP:
            pstChildNode = TAF_MTA_AGPS_ConvertEllipPointUncertEllip(pstXmlCommCtx,
                                                                     &pstShapeData->u.stEllipPointUncertEllip);
            break;
        case AGPS_POSITION_ESTIMAT_ELLIP_POINT_ALTI:
            pstChildNode = TAF_MTA_AGPS_ConvertEllipPointAlti(pstXmlCommCtx,
                                                              &pstShapeData->u.stEllipPointAlti);
            break;
        case AGPS_POSITION_ESTIMAT_ELLIP_POINT_ALTI_ELLIP:
            pstChildNode = TAF_MTA_AGPS_ConvertEllipPointAltiEllip(pstXmlCommCtx,
                                                                   &pstShapeData->u.stEllipPointAltiEllip);
            break;
        case AGPS_POSITION_ESTIMAT_ELLIP_ARC:
            pstChildNode = TAF_MTA_AGPS_ConvertEllipArc(pstXmlCommCtx, &pstShapeData->u.stEllipArc);
            break;
        default:
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertShapeData: WARNING: Invalid enEstimatType!");
            return VOS_NULL_PTR;
    }

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeShapeData, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertShapeData: WARNING: Add MTA_AGPS_LABEL_ELLIPSOID_POINT fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeShapeData;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEllipPoint
功能描述  : 将AGPS_ELLIP_POINT_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstShapeData    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPoint(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_STRU              *pstEllipPoint
)
{
    XML_COMM_NODE_STRU                 *pstNodeEllipPoint;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT ellipsoid_point (coordinate)>
                    <!ELEMENT coordinate (latitude,longitude)>
                        <!ELEMENT latitude (north,degrees)>
                            <!ELEMENT north (#PCDATA)>
                            <!ELEMENT degrees (#PCDATA)>
                        <!ELEMENT longitude (#PCDATA)> */

    /* 调用XML API提供的接口，创建<ellipsoid_point> 节点并设置标签 */
    pstNodeEllipPoint = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ELLIPSOID_POINT);
    if (VOS_NULL_PTR == pstNodeEllipPoint)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPoint: WARNING:Create MTA_AGPS_LABEL_ELLIPSOID_POINT fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertCoordinate(pstXmlCommCtx, &pstEllipPoint->stCoordinate);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPoint, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPoint: WARNING: Add MTA_AGPS_LABEL_COORDINATE fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeEllipPoint;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertCoordinate
功能描述  : 将AGPS_COORDINATE_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstCoordinate   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertCoordinate(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_COORDINATE_STRU               *pstCoordinate
)
{
    XML_COMM_NODE_STRU                 *pstNodeCoordinate;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT coordinate (latitude,longitude)>
                        <!ELEMENT latitude (north,degrees)>
                            <!ELEMENT north (#PCDATA)>
                            <!ELEMENT degrees (#PCDATA)>
                        <!ELEMENT longitude (#PCDATA)> */

    /* 调用XML API提供的接口，创建<coordinate> 节点并设置标签 */
    pstNodeCoordinate = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_COORDINATE);
    if (VOS_NULL_PTR == pstNodeCoordinate)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLocationPara: WARNING:Create MTA_AGPS_LABEL_COORDINATE fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertLatitude(pstXmlCommCtx, &pstCoordinate->stLatitude);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeCoordinate, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRefTime: WARNING: Add MTA_AGPS_LABEL_LATITUDE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT longitude (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeCoordinate,
                                                       MTA_AGPS_LABEL_LONGITUDE,
                                                       pstCoordinate->lLongitude))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsAssist: WARNING: Create MTA_AGPS_LABEL_LONGITUDE fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeCoordinate;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertLatitude
功能描述  : 将AGPS_LATITUDE_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstLatitude     待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertLatitude(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_LATITUDE_STRU                 *pstLatitude
)
{
    XML_COMM_NODE_STRU                 *pstNodeLatitude;

     /* <!ELEMENT latitude (north,degrees)>
                            <!ELEMENT north (#PCDATA)>
                            <!ELEMENT degrees (#PCDATA)> */

    /* 调用XML API提供的接口，创建<latitude> 节点并设置标签 */
    pstNodeLatitude = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_LATITUDE);
    if (VOS_NULL_PTR == pstNodeLatitude)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLatitude: WARNING:Create MTA_AGPS_LABEL_LATITUDE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT north (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeLatitude,
                                                         MTA_AGPS_LABEL_NORTH,
                                                         (VOS_UINT32)pstLatitude->enNorth))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLatitude: WARNING: Create MTA_AGPS_LABEL_NORTH fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT degrees (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeLatitude,
                                                         MTA_AGPS_LABEL_DEGREES,
                                                         pstLatitude->ulDegrees))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLatitude: WARNING: Create MTA_AGPS_LABEL_DEGREES fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeLatitude;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEllipPointUncertCircle
功能描述  : 将AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx               XML上下文
            pstEllipPointUncertCircle   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointUncertCircle(
    XML_COMM_CTX_STRU                      *pstXmlCommCtx,
    AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU    *pstEllipPointUncertCircle
)
{
    XML_COMM_NODE_STRU                 *pstNodeEllipPointUncertCircle;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT ellipsoid_point_uncert_circle (coordinate,uncert_circle)>
                    <!ELEMENT uncert_circle (#PCDATA)> */

    /* 调用XML API提供的接口，创建<ellipsoid_point_uncert_circle> 节点并设置标签 */
    pstNodeEllipPointUncertCircle = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                                        MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_CIRCLE);
    if (VOS_NULL_PTR == pstNodeEllipPointUncertCircle)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointUncertCircle: WARNING:Create MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_CIRCLE fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertCoordinate(pstXmlCommCtx, &pstEllipPointUncertCircle->stCoordinate);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPointUncertCircle, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointUncertCircle: WARNING: Add MTA_AGPS_LABEL_COORDINATE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT uncert_circle (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipPointUncertCircle,
                                                         MTA_AGPS_LABEL_UNCERT_CIRCLE,
                                                         (VOS_UINT32)pstEllipPointUncertCircle->ucUncertnCode))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointUncertCircle: WARNING: Create MTA_AGPS_LABEL_UNCERT_CIRCLE fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeEllipPointUncertCircle;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEllipPointUncertEllip
功能描述  : 将AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx               XML上下文
            pstEllipPointUncertCircle   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointUncertEllip(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU *pstEllipPointUncertEllip
)
{
    XML_COMM_NODE_STRU                 *pstNodeEllipPointUncertEllip;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*  <!ELEMENT ellipsoid_point_uncert_ellipse (coordinate,uncert_ellipse)>
                    <!ELEMENT uncert_ellipse (uncert_semi_major,uncert_semi_minor,orient_major,confidence)> */

    /* 调用XML API提供的接口，创建<ellipsoid_point_uncert_ellipse> 节点并设置标签 */
    pstNodeEllipPointUncertEllip = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                                       MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_ELLIPSE);
    if (VOS_NULL_PTR == pstNodeEllipPointUncertEllip)
    {
        MTA_WARNING_LOG("pstNodeEllipPointUncertEllip: WARNING: Create MTA_AGPS_LABEL_ELLIPSOID_POINT_UNCERT_ELLIPSE fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertCoordinate(pstXmlCommCtx, &pstEllipPointUncertEllip->stCoordinate);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPointUncertEllip, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointUncertCircle: WARNING: Add MTA_AGPS_LABEL_COORDINATE fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertUncertEllipse(pstXmlCommCtx, &pstEllipPointUncertEllip->stUncertEllipse);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPointUncertEllip, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("pstNodeEllipPointUncertEllip: WARNING: Create MTA_AGPS_LABEL_UNCERT_ELLIPSE fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeEllipPointUncertEllip;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertUncertEllipse
功能描述  : 将AGPS_UNCERT_ELLIPSE_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx       XML上下文
            pstUncertEllipse    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertUncertEllipse(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UNCERT_ELLIPSE_STRU           *pstUncertEllipse
)
{
    XML_COMM_NODE_STRU                 *pstNodeUncertEllipse;

    /* <!ELEMENT uncert_ellipse (uncert_semi_major,uncert_semi_minor,orient_major,confidence)>
                        <!ELEMENT uncert_semi_major (#PCDATA)>
                        <!ELEMENT uncert_semi_minor (#PCDATA)>
                        <!ELEMENT orient_major (#PCDATA)>
                        <!ELEMENT confidence (#PCDATA)>*/

    /* 调用XML API提供的接口，创建<uncert_ellipse> 节点并设置标签 */
    pstNodeUncertEllipse = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                               MTA_AGPS_LABEL_UNCERT_ELLIPSE);
    if (VOS_NULL_PTR == pstNodeUncertEllipse)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUncertEllipse: WARNING:Create MTA_AGPS_LABEL_UNCERT_ELLIPSE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT uncert_semi_major (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeUncertEllipse,
                                                         MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR,
                                                         (VOS_UINT32)pstUncertEllipse->ucUncertnSemiMajor))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUncertEllipse: WARNING: Create MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT uncert_semi_minor (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeUncertEllipse,
                                                         MTA_AGPS_LABEL_UNCERT_SEMI_MINOR,
                                                         (VOS_UINT32)pstUncertEllipse->ucUncertnSemiMin))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUncertEllipse: WARNING: Create MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT orient_major (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeUncertEllipse,
                                                         MTA_AGPS_LABEL_ORIENT_MAJOR,
                                                         (VOS_UINT32)pstUncertEllipse->ucOrientMajorAxis))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUncertEllipse: WARNING: Create MTA_AGPS_LABEL_ORIENT_MAJOR fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT confidence (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeUncertEllipse,
                                                         MTA_AGPS_LABEL_CONFIDENCE,
                                                         (VOS_UINT32)pstUncertEllipse->ucConfidence))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUncertEllipse: WARNING: Create MTA_AGPS_LABEL_CONFIDENCE fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeUncertEllipse;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEllipPointAlti
功能描述  : 将AGPS_ELLIP_POINT_ALTI_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx       XML上下文
            pstEllipPointAlti   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointAlti(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_ALTI_STRU         *pstEllipPointAlti
)
{
    XML_COMM_NODE_STRU                 *pstNodeEllipPointAlti;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*<!ELEMENT ellipsoid_point_alt (coordinate,altitude)>
                    <!ELEMENT altitude (height_above_surface,height)> */

    /* 调用XML API提供的接口，创建<ellipsoid_point_alt> 节点并设置标签 */
    pstNodeEllipPointAlti = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                                MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT);
    if (VOS_NULL_PTR == pstNodeEllipPointAlti)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAlti: WARNING: Create MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertCoordinate(pstXmlCommCtx, &pstEllipPointAlti->stCoordinate);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPointAlti, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAlti: WARNING: Add MTA_AGPS_LABEL_COORDINATE fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertAltitude(pstXmlCommCtx, &pstEllipPointAlti->stAltitude);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPointAlti, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAlti: WARNING: Create MTA_AGPS_LABEL_ALTITUDE fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeEllipPointAlti;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertAltitude
功能描述  : 将AGPS_ALTITUDE_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstAltitude     待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAltitude(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ALTITUDE_STRU                 *pstAltitude
)
{
    XML_COMM_NODE_STRU                 *pstNodeAltitude;

     /* <!ELEMENT altitude (height_above_surface,height)>
                        <!ELEMENT height_above_surface (#PCDATA)>
                        <!ELEMENT height (#PCDATA)> */

    /* 调用XML API提供的接口，创建<altitude> 节点并设置标签 */
    pstNodeAltitude = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ALTITUDE);
    if (VOS_NULL_PTR == pstNodeAltitude)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLatitude: WARNING:Create MTA_AGPS_LABEL_ALTITUDE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT height_above_surface (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAltitude,
                                                         MTA_AGPS_LABEL_HEIGHT_ABOVE_SURFACE,
                                                         (VOS_UINT32)pstAltitude->enAltiDirect))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLatitude: WARNING: Create MTA_AGPS_LABEL_HEIGHT_ABOVE_SURFACE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT height (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAltitude,
                                                         MTA_AGPS_LABEL_HEIGHT,
                                                         (VOS_UINT32)pstAltitude->usHeight))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertLatitude: WARNING: Create MTA_AGPS_LABEL_HEIGHT fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeAltitude;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEllipPointAltiEllip
功能描述  : 将AGPS_ELLIP_POINT_ALTI_ELLIP_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstEllipPointAltiEllip  待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipPointAltiEllip(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_POINT_ALTI_ELLIP_STRU   *pstEllipPointAltiEllip
)
{
    XML_COMM_NODE_STRU                 *pstNodeEllipPointAltiEllip;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT ellipsoid_point_alt_uncertellipse (coordinate,altitude,uncert_semi_major,uncert_semi_minor,orient_major,confidence,uncert_alt)>
                   <!ELEMENT uncert_alt (#PCDATA)>
     */

    /* 调用XML API提供的接口，创建<ellipsoid_point_alt_uncertellipse>  节点并设置标签 */
    pstNodeEllipPointAltiEllip = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                                     MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT_UNCERTELLIPSE);
    if (VOS_NULL_PTR == pstNodeEllipPointAltiEllip)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Create MTA_AGPS_LABEL_ELLIPSOID_POINT_ALT_UNCERTELLIPSE fail!");
        return VOS_NULL_PTR;
    }

    /* 添加节点 <coordinate> */
    pstChildNode = TAF_MTA_AGPS_ConvertCoordinate(pstXmlCommCtx, &pstEllipPointAltiEllip->stCoordinate);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPointAltiEllip, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Add MTA_AGPS_LABEL_COORDINATE fail!");
        return VOS_NULL_PTR;
    }

    /* 添加节点 <altitude> */
    pstChildNode = TAF_MTA_AGPS_ConvertAltitude(pstXmlCommCtx, &pstEllipPointAltiEllip->stAltitude);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipPointAltiEllip, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Add MTA_AGPS_LABEL_LATITUDE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT uncert_semi_major (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipPointAltiEllip,
                                                         MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR,
                                                         (VOS_UINT32)pstEllipPointAltiEllip->ucUncertnSemiMajor))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Create MTA_AGPS_LABEL_UNCERT_SEMI_MAJOR fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT uncert_semi_minor (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipPointAltiEllip,
                                                         MTA_AGPS_LABEL_UNCERT_SEMI_MINOR,
                                                         (VOS_UINT32)pstEllipPointAltiEllip->ucUncertnSemiMin))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Create MTA_AGPS_LABEL_UNCERT_SEMI_MINOR fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT orient_major (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipPointAltiEllip,
                                                         MTA_AGPS_LABEL_ORIENT_MAJOR,
                                                         (VOS_UINT32)pstEllipPointAltiEllip->ucOrientMajorAxis))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Create MTA_AGPS_LABEL_ORIENT_MAJOR fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT confidence (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipPointAltiEllip,
                                                         MTA_AGPS_LABEL_CONFIDENCE,
                                                         (VOS_UINT32)pstEllipPointAltiEllip->ucConfidence))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Create MTA_AGPS_LABEL_CONFIDENCE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT uncert_alt (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipPointAltiEllip,
                                                         MTA_AGPS_LABEL_UNCERT_ALT,
                                                         (VOS_UINT32)pstEllipPointAltiEllip->ucUncertnAlti))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipPointAltiEllip: WARNING: Create MTA_AGPS_LABEL_UNCERT_ALT fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeEllipPointAltiEllip;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEllipArc
功能描述  : 将AGPS_ELLIP_ARC_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstEllipArc     待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEllipArc(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ELLIP_ARC_STRU                *pstEllipArc
)
{
    XML_COMM_NODE_STRU                 *pstNodeEllipArc;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT ellips_arc (coordinate,inner_rad,uncert_rad,offset_angle,included_angle,confidence)>
                    <!ELEMENT inner_rad (#PCDATA)>
                    <!ELEMENT uncert_rad (#PCDATA)>
                    <!ELEMENT offset_angle (#PCDATA)>
                    <!ELEMENT included_angle (#PCDATA)> */

    /* 调用XML API提供的接口，创建<ellips_arc> 节点并设置标签 */
    pstNodeEllipArc = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ELLIPS_ARC);
    if (VOS_NULL_PTR == pstNodeEllipArc)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipArc: WARNING:Create MTA_AGPS_LABEL_ELLIPS_ARC fail!");
        return VOS_NULL_PTR;
    }

    pstChildNode = TAF_MTA_AGPS_ConvertCoordinate(pstXmlCommCtx, &pstEllipArc->stCoordinate);

    /* 为节点增加一个子节点 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeEllipArc, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipArc: WARNING: Add MTA_AGPS_LABEL_COORDINATE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT inner_rad (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipArc,
                                                         MTA_AGPS_LABEL_INNER_RAD,
                                                         (VOS_UINT32)pstEllipArc->usInnerRad))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipArc: WARNING: Create MTA_AGPS_LABEL_INNER_RAD fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT uncert_rad (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipArc,
                                                         MTA_AGPS_LABEL_UNCERT_RAD,
                                                         (VOS_UINT32)pstEllipArc->ucUncertRad))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipArc: WARNING: Create MTA_AGPS_LABEL_INNER_RAD fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT offset_angle (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipArc,
                                                         MTA_AGPS_LABEL_OFFSET_ANGLE,
                                                         (VOS_UINT32)pstEllipArc->ucOffsetAngle))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipArc: WARNING: Create MTA_AGPS_LABEL_OFFSET_ANGLE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT included_angle (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipArc,
                                                         MTA_AGPS_LABEL_INCLUDED_ANGLE,
                                                         (VOS_UINT32)pstEllipArc->ucIncludedAngle))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipArc: WARNING: Create MTA_AGPS_LABEL_INCLUDED_ANGLE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT confidence (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeEllipArc,
                                                         MTA_AGPS_LABEL_CONFIDENCE,
                                                         (VOS_UINT32)pstEllipArc->ucConfidence))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEllipArc: WARNING: Create MTA_AGPS_LABEL_CONFIDENCE fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeEllipArc;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertUpDgpsCorrection
功能描述  : 将AGPS_UP_DGPS_CORRECTION_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx         XML上下文
            pstUpDgpsCorrection   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertUpDgpsCorrection(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UP_DGPS_CORRECTION_STRU       *pstUpDgpsCorrection
)
{
    XML_COMM_NODE_STRU                 *pstNodeUpDgpsCorrection;

    /* <!ELEMENT DGPS_corrections (sat_id,IODE,UDRE,PRC,RRC,delta_PRC2?,delta_RRC2?)> */

    /* 调用XML API提供的接口，创建<DGPS_corrections> 节点并设置标签 */
    pstNodeUpDgpsCorrection = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_DGPS_CORRECTIONS);
    if (VOS_NULL_PTR == pstNodeUpDgpsCorrection)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_DGPS_CORRECTIONS fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT sat_id (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeUpDgpsCorrection,
                                                         MTA_AGPS_LABEL_SAT_ID,
                                                         (VOS_UINT32)pstUpDgpsCorrection->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_SAT_ID fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT IODE (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeUpDgpsCorrection,
                                                         MTA_AGPS_LABEL_IODE_UPPER_CASE,
                                                         (VOS_UINT32)pstUpDgpsCorrection->ucIode))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_IODE_UPPER_CASE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT UDRE (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeUpDgpsCorrection,
                                                         MTA_AGPS_LABEL_UDRE,
                                                         (VOS_UINT32)pstUpDgpsCorrection->enUdre))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_UDRE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT PRC (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeUpDgpsCorrection,
                                                       MTA_AGPS_LABEL_PRC,
                                                       (VOS_INT32)pstUpDgpsCorrection->sPrc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_PRC fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT RRC (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeUpDgpsCorrection,
                                                       MTA_AGPS_LABEL_RRC,
                                                       (VOS_INT32)pstUpDgpsCorrection->cRrc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_RRC fail!");
        return VOS_NULL_PTR;
    }

    if (VOS_TRUE == pstUpDgpsCorrection->bitOpDeltaPrc2)
    {
        /* 转换子结构并挂到当前节点下 */
        /* <!ELEMENT delta_PRC2 (#PCDATA)> */
        if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                           pstNodeUpDgpsCorrection,
                                                           MTA_AGPS_LABEL_DELTA_PRC2,
                                                           (VOS_INT32)pstUpDgpsCorrection->cDeltaPrc2))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_DELTA_PRC2 fail!");
            return VOS_NULL_PTR;
        }
    }

    if (VOS_TRUE == pstUpDgpsCorrection->bitOpDeltaRrc2)
    {
        /* 转换子结构并挂到当前节点下 */
        /* <!ELEMENT delta_RRC2 (#PCDATA)> */
        if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                           pstNodeUpDgpsCorrection,
                                                           MTA_AGPS_LABEL_DELTA_RRC2,
                                                           (VOS_INT32)pstUpDgpsCorrection->cDeltaRrc2))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertUpDgpsCorrection: WARNING: Create MTA_AGPS_LABEL_DELTA_PRC2 fail!");
            return VOS_NULL_PTR;
        }
    }

    return pstNodeUpDgpsCorrection;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem
功能描述  : 将AGPS_NAV_MODEL_ELEM_STRU结构体中的enSatSta元素转换为树结构
输入参数  : pstXmlCommCtx         XML上下文
            pstNavModelElem       待转换结构体
            pstNodeNavModelElem   父节点
输出参数  : 无
返 回 值  : VOS_OK      转换成功
            VOS_ERR     转换失败
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月13日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_NAV_MODEL_ELEM_STRU           *pstNavModelElem,
    XML_COMM_NODE_STRU                 *pstNodeNavModelElem
)
{
    XML_COMM_NODE_STRU                 *pstSatStatusNode;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 调用XML API提供的接口，创建节点并设置标签 */
    pstSatStatusNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_SAT_STATUS);
    if (VOS_NULL_PTR == pstSatStatusNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem: WARNING: Create MTA_AGPS_LABEL_SAT_STATUS fail!");
        return VOS_ERR;
    }

    /* 增加属性<!ATTLIST sat_status literal (NS_NN-U|ES_NN-U|NS_NN|ES_SN|REVD) #REQUIRED > */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_ERR;
    }

    switch (pstNavModelElem->enSatSta)
    {
        case AGPS_POS_SAT_STA_NS_NN_U:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_NS_NN_U);
            break;
        case AGPS_POS_SAT_STA_ES_SN:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_ES_SN);
            break;
        case AGPS_POS_SAT_STA_ES_NN_U:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_ES_NN_U);
            break;
        case AGPS_POS_SAT_STA_REV:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_REVD);
            break;
        default:
            /* nav_model_elem是#REQUIRED类型的，值异常则退出 */
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem: WARNING: sat_status is abnormal!", pstNavModelElem->enSatSta);
            return VOS_ERR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstSatStatusNode, pstNodeAttribute, VOS_NULL_PTR);
    /* 将子结构并挂到当前节点下 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeNavModelElem, pstSatStatusNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem: WARNING: Add attribute for sat_status fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertNavModelElem
功能描述  : 将AGPS_NAV_MODEL_ELEM_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx         XML上下文
            pstNavModelElem      待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月29日
  作    者  : l00198894/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertNavModelElem(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_NAV_MODEL_ELEM_STRU           *pstNavModelElem
)
{
    XML_COMM_NODE_STRU                 *pstNodeNavModelElem;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT nav_model_elem (sat_id,sat_status,ephem_and_clock?)>
         <!ELEMENT sat_status EMPTY>
         <!ATTLIST sat_status literal (NS_NN-U|ES_NN-U|NS_NN|ES_SN|REVD) #REQUIRED >
         <!ELEMENT ephem_and_clock (l2_code,ura,sv_health,iodc,l2p_flag,esr1,esr2,esr3,esr4,tgd,toc,af2,af1,af0,crs,delta_n,m0,cuc,ecc,cus,power_half,toe,fit_flag,aoda,cic,omega0,cis,i0,crc,omega,omega_dot,idot)>
            <!ELEMENT l2_code (#PCDATA)>
            <!ELEMENT ura (#PCDATA)>
            <!ELEMENT sv_health (#PCDATA)>
            <!ELEMENT iodc (#PCDATA)>
            <!ELEMENT l2p_flag (#PCDATA)>
            <!ELEMENT esr1 (#PCDATA)>
            <!ELEMENT esr2 (#PCDATA)>
            <!ELEMENT esr3 (#PCDATA)>
            <!ELEMENT esr4 (#PCDATA)>
            <!ELEMENT tgd (#PCDATA)>
            <!ELEMENT toc (#PCDATA)>
            <!ELEMENT af2 (#PCDATA)>
            <!ELEMENT af1 (#PCDATA)>
            <!ELEMENT af0 (#PCDATA)>
            <!ELEMENT crs (#PCDATA)>
            <!ELEMENT delta_n (#PCDATA)>
            <!ELEMENT m0 (#PCDATA)>
            <!ELEMENT cuc (#PCDATA)>
            <!ELEMENT ecc (#PCDATA)>
            <!ELEMENT cus (#PCDATA)>
            <!ELEMENT power_half (#PCDATA)>
            <!ELEMENT toe (#PCDATA)>
            <!ELEMENT fit_flag (#PCDATA)>
            <!ELEMENT aoda (#PCDATA)>
            <!ELEMENT cic (#PCDATA)>
            <!ELEMENT omega0 (#PCDATA)>
            <!ELEMENT cis (#PCDATA)>
            <!ELEMENT i0 (#PCDATA)>
            <!ELEMENT crc (#PCDATA)>
            <!ELEMENT omega (#PCDATA)>
            <!ELEMENT omega_dot (#PCDATA)>
            <!ELEMENT idot (#PCDATA)>
    */
    /* 调用XML API提供的接口，创建<nav_model_elem> 节点并设置标签 */
    pstNodeNavModelElem = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_NAV_MODEL_ELEM);
    if (VOS_NULL_PTR == pstNodeNavModelElem)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertNavModelElem: WARNING: Create MTA_AGPS_LABEL_NAV_MODEL_ELEM fail!");
        return VOS_NULL_PTR;
    }

    /* 创建子节点sat_id */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeNavModelElem,
                                                         MTA_AGPS_LABEL_SAT_ID,
                                                         (VOS_UINT32)pstNavModelElem->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertNavModelElem: WARNING: Create MTA_AGPS_LABEL_SAT_ID fail!");
        return VOS_NULL_PTR;
    }

    /* 创建子节点sat_status */
    ulReturnValue = TAF_MTA_AGPS_ConvertSatStatusOfNavModelElem(pstXmlCommCtx, pstNavModelElem, pstNodeNavModelElem);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertNavModelElem: WARNING: Create MTA_AGPS_LABEL_SAT_STATUS fail!");
        return VOS_NULL_PTR;
    }
    /* 转换并挂接子节点<ephem_and_clock> */
    if (VOS_TRUE == pstNavModelElem->bitEphemClock)
    {
        /* 判断模式 */
        if (AGPS_EPHEM_CLOCK_TYPE_RRLP == pstNavModelElem->enChoice)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertRrlpEphemClockParam(pstXmlCommCtx,
                                                                   &pstNavModelElem->u.stRrlpEphemClock);
        }
        else if (AGPS_EPHEM_CLOCK_TYPE_RRC == pstNavModelElem->enChoice)
        {
            pstChildNode = TAF_MTA_AGPS_ConvertRrcEphemClockParam(pstXmlCommCtx,
                                                                  &pstNavModelElem->u.stRrcEphemClock);
        }
        else
        {
            return VOS_NULL_PTR;
        }

        ulReturnValue = XML_COMM_AddAChildNode(pstNodeNavModelElem, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertNavModelElem: WARNING: Add MTA_AGPS_LABEL_NAV_MODEL_ELEM fail!");
            return VOS_NULL_PTR;
        }
    }

    return pstNodeNavModelElem;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne
功能描述  : 将AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<l2_code>、<ura>、<sv_health>、<iodc>、<l2p_flag>、<esr1>、
            <esr2>、<esr3>、<esr4>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrlpEphemClockParam  属性转换后挂载的父节点
            pstRrlpEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrlpEphemClockParam,
    AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU   *pstRrlpEphemClockParam
)
{
    /*
    <!ELEMENT l2_code (#PCDATA)>
    <!ELEMENT ura (#PCDATA)>
    <!ELEMENT sv_health (#PCDATA)>
    <!ELEMENT iodc (#PCDATA)>
    <!ELEMENT l2p_flag (#PCDATA)>
    <!ELEMENT esr1 (#PCDATA)>
    <!ELEMENT esr2 (#PCDATA)>
    <!ELEMENT esr3 (#PCDATA)>
    <!ELEMENT esr4 (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT l2_code (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_L2_CODE,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->ucCodeOnL2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_L2_CODE fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT ura (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_URA,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->ucUraIndex))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_URA fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT sv_health (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_SV_HEALTH,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->ucSatHealth))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_SV_HEALTH fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT iodc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_IODC,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->usIodc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_IODC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT l2p_flag (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_L2P_FLAG,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->ucL2PFlag))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_L2P_FLAG fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR1,
                                                         pstRrlpEphemClockParam->ulReserved1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR1 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR2,
                                                         pstRrlpEphemClockParam->ulReserved2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR2 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr3 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR3,
                                                         pstRrlpEphemClockParam->ulReserved3))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR3 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr4 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR4,
                                                         pstRrlpEphemClockParam->usReserved4))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR4 fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo
功能描述  : 将AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<tgd>、<toc>、<af2>、<af1>、<af0>、<crs>、<delta_n>、<m0>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrlpEphemClockParam  属性转换后挂载的父节点
            pstRrlpEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrlpEphemClockParam,
    AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU   *pstRrlpEphemClockParam
)
{
    /*
    <!ELEMENT tgd (#PCDATA)>
    <!ELEMENT toc (#PCDATA)>
    <!ELEMENT af2 (#PCDATA)>
    <!ELEMENT af1 (#PCDATA)>
    <!ELEMENT af0 (#PCDATA)>
    <!ELEMENT crs (#PCDATA)>
    <!ELEMENT delta_n (#PCDATA)>
    <!ELEMENT m0 (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT tgd (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_TGD,
                                                       (VOS_INT32)pstRrlpEphemClockParam->cTGd))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_TGD fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT toc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_TOC,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->usTOc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_TOC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT af2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_AF2,
                                                       (VOS_INT32)pstRrlpEphemClockParam->cAf2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_AF2 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT af1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_AF1,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sAf1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_AF1 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT af0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_AF0,
                                                       pstRrlpEphemClockParam->lAf0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_AF0 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT crs (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_CRS,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sCRs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_CRS fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT delta_n (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_DELTA_N,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sDeltaN))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_DELTA_N fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT m0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_M0,
                                                       pstRrlpEphemClockParam->lM0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_M0 fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree
功能描述  : 将AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<cuc>、<ecc>、<cus>、<power_half>、<toe>、<fit_flag>、<aoda>、
            <cic>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrlpEphemClockParam  属性转换后挂载的父节点
            pstRrlpEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrlpEphemClockParam,
    AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU   *pstRrlpEphemClockParam
)
{
    /*
    <!ELEMENT cuc (#PCDATA)>
    <!ELEMENT ecc (#PCDATA)>
    <!ELEMENT cus (#PCDATA)>
    <!ELEMENT power_half (#PCDATA)>
    <!ELEMENT toe (#PCDATA)>
    <!ELEMENT fit_flag (#PCDATA)>
    <!ELEMENT aoda (#PCDATA)>
    <!ELEMENT cic (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cuc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_CUC,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sCUc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_CUC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT ecc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_ECC,
                                                         pstRrlpEphemClockParam->ulEcc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_ECC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cus (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_CUS,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sCUs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_CUS fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT power_half (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_POWER_HALF,
                                                         pstRrlpEphemClockParam->ulPowerHalf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_POWER_HALF fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT toe (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_TOE,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->usTOe))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_TOE fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT fit_flag (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_FIT_FLAG,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->ucFitFlag))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_FIT_FLAG fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT aoda (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpEphemClockParam,
                                                         MTA_AGPS_LABEL_AODA,
                                                         (VOS_UINT32)pstRrlpEphemClockParam->ucAodo))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_AODA fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cic (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_CIC,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sCIc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_CIC fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour
功能描述  : 将AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<omega0>、<cis>、<i0>、<crc>、<omega>、<omega_dot>、<idot>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrlpEphemClockParam  属性转换后挂载的父节点
            pstRrlpEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrlpEphemClockParam,
    AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU   *pstRrlpEphemClockParam
)
{
    /*
    <!ELEMENT omega0 (#PCDATA)>
    <!ELEMENT cis (#PCDATA)>
    <!ELEMENT i0 (#PCDATA)>
    <!ELEMENT crc (#PCDATA)>
    <!ELEMENT omega (#PCDATA)>
    <!ELEMENT omega_dot (#PCDATA)>
    <!ELEMENT idot (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT omega0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_OMEGA0,
                                                       pstRrlpEphemClockParam->lOmega0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_OMEGA0 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cis (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_CIS,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sCIs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_CIS fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT i0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_I0,
                                                       pstRrlpEphemClockParam->lI0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_I0 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT crc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_CRC,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sCRc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_CRC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT omega (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_OMEGA,
                                                       pstRrlpEphemClockParam->lOmega))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_OMEGA fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT omega_dot (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_OMEGA_DOT,
                                                       pstRrlpEphemClockParam->lOmegaDot))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_OMEGA_DOT fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT idot (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpEphemClockParam,
                                                       MTA_AGPS_LABEL_IDOT,
                                                       (VOS_INT32)pstRrlpEphemClockParam->sIDot))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_IDOT fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrlpEphemClockParam
功能描述  : 将AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx             XML上下文
            pstRrlpEphemClockParam    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpEphemClockParam(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_EPHEM_CLOCK_PARAM_STRU   *pstRrlpEphemClockParam
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrlpEphemClockParam;

     /* <!ELEMENT ephem_and_clock (l2_code,ura,sv_health,iodc,l2p_flag,esr1,esr2,esr3,esr4,tgd,toc,af2,af1,af0,
           crs,delta_n,m0,cuc,ecc,cus,power_half,toe,fit_flag,aoda,cic,omega0,cis,i0,crc,omega,omega_dot,idot)>
                <!ELEMENT l2_code (#PCDATA)>
                <!ELEMENT ura (#PCDATA)>
                <!ELEMENT sv_health (#PCDATA)>
                <!ELEMENT iodc (#PCDATA)>
                <!ELEMENT l2p_flag (#PCDATA)>
                <!ELEMENT esr1 (#PCDATA)>
                <!ELEMENT esr2 (#PCDATA)>
                <!ELEMENT esr3 (#PCDATA)>
                <!ELEMENT esr4 (#PCDATA)>
                <!ELEMENT tgd (#PCDATA)>
                <!ELEMENT toc (#PCDATA)>
                <!ELEMENT af2 (#PCDATA)>
                <!ELEMENT af1 (#PCDATA)>
                <!ELEMENT af0 (#PCDATA)>
                <!ELEMENT crs (#PCDATA)>
                <!ELEMENT delta_n (#PCDATA)>
                <!ELEMENT m0 (#PCDATA)>
                <!ELEMENT cuc (#PCDATA)>
                <!ELEMENT ecc (#PCDATA)>
                <!ELEMENT cus (#PCDATA)>
                <!ELEMENT power_half (#PCDATA)>
                <!ELEMENT toe (#PCDATA)>
                <!ELEMENT fit_flag (#PCDATA)>
                <!ELEMENT aoda (#PCDATA)>
                <!ELEMENT cic (#PCDATA)>
                <!ELEMENT omega0 (#PCDATA)>
                <!ELEMENT cis (#PCDATA)>
                <!ELEMENT i0 (#PCDATA)>
                <!ELEMENT crc (#PCDATA)>
                <!ELEMENT omega (#PCDATA)>
                <!ELEMENT omega_dot (#PCDATA)>
                <!ELEMENT idot (#PCDATA)> */

    /* 调用XML API提供的接口，创建<ephem_and_clock> 节点并设置标签 */
    pstNodeRrlpEphemClockParam = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_EPHEM_AND_CLOCK);
    if (VOS_NULL_PTR == pstNodeRrlpEphemClockParam)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpEphemClockParam: WARNING:Create MTA_AGPS_LABEL_EPHEM_AND_CLOCK fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part1 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartOne(pstXmlCommCtx,
                                                              pstNodeRrlpEphemClockParam,
                                                              pstRrlpEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpEphemClockParam: WARNING: Add Child Nodes Part1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part2 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartTwo(pstXmlCommCtx,
                                                              pstNodeRrlpEphemClockParam,
                                                              pstRrlpEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpEphemClockParam: WARNING: Add Child Nodes Part2 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part3 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartThree(pstXmlCommCtx,
                                                              pstNodeRrlpEphemClockParam,
                                                              pstRrlpEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpEphemClockParam: WARNING: Add Child Nodes Part3 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part4 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrlpEphemClockParamChildNodesPartFour(pstXmlCommCtx,
                                                              pstNodeRrlpEphemClockParam,
                                                              pstRrlpEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpEphemClockParam: WARNING: Add Child Nodes Part4 fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrlpEphemClockParam;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne
功能描述  : 将AGPS_RRC_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<l2_code>、<ura>、<sv_health>、<iodc>、<l2p_flag>、<esr1>、
            <esr2>、<esr3>、<esr4>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrcEphemClockParam   属性转换后挂载的父节点
            pstRrcEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrcEphemClockParam,
    AGPS_RRC_EPHEM_CLOCK_PARAM_STRU    *pstRrcEphemClockParam
)
{
    /*
    <!ELEMENT l2_code (#PCDATA)>
    <!ELEMENT ura (#PCDATA)>
    <!ELEMENT sv_health (#PCDATA)>
    <!ELEMENT iodc (#PCDATA)>
    <!ELEMENT l2p_flag (#PCDATA)>
    <!ELEMENT esr1 (#PCDATA)>
    <!ELEMENT esr2 (#PCDATA)>
    <!ELEMENT esr3 (#PCDATA)>
    <!ELEMENT esr4 (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT l2_code (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_L2_CODE,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucCodeOnL2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_L2_CODE fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT ura (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_URA,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucUraIndex))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_URA fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT sv_health (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_SV_HEALTH,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucSatHealth))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_SV_HEALTH fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT iodc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_IODC,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usIodc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_IODC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT l2p_flag (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_L2P_FLAG,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucL2PFlag))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_L2P_FLAG fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR1,
                                                         pstRrcEphemClockParam->ulReserved1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR1 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR2,
                                                         pstRrcEphemClockParam->ulReserved2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR2 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr3 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR3,
                                                         pstRrcEphemClockParam->ulReserved3))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR3 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT esr4 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_ESR4,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usReserved4))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne: WARNING: Create MTA_AGPS_LABEL_ESR4 fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo
功能描述  : 将AGPS_RRC_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<tgd>、<toc>、<af2>、<af1>、<af0>、<crs>、
            <delta_n>、<m0>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrcEphemClockParam   属性转换后挂载的父节点
            pstRrcEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrcEphemClockParam,
    AGPS_RRC_EPHEM_CLOCK_PARAM_STRU    *pstRrcEphemClockParam
)
{
    /*
    <!ELEMENT tgd (#PCDATA)>
    <!ELEMENT toc (#PCDATA)>
    <!ELEMENT af2 (#PCDATA)>
    <!ELEMENT af1 (#PCDATA)>
    <!ELEMENT af0 (#PCDATA)>
    <!ELEMENT crs (#PCDATA)>
    <!ELEMENT delta_n (#PCDATA)>
    <!ELEMENT m0 (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT tgd (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_TGD,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucTGd))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_TGD fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT toc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_TOC,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usTOc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_TOC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT af2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_AF2,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucAf2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_AF2 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT af1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_AF1,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usAf1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_AF1 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT af0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_AF0,
                                                         pstRrcEphemClockParam->ulAf0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_AF0 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT crs (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_CRS,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usCRs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_CRS fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT delta_n (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_DELTA_N,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usDeltaN))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_DELTA_N fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT m0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_M0,
                                                         pstRrcEphemClockParam->ulM0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo: WARNING: Create MTA_AGPS_LABEL_M0 fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree
功能描述  : 将AGPS_RRC_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<cuc>、<ecc>、<cus>、<power_half>、<toe>、<fit_flag>、
            <aoda>、<cic>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrcEphemClockParam   属性转换后挂载的父节点
            pstRrcEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrcEphemClockParam,
    AGPS_RRC_EPHEM_CLOCK_PARAM_STRU    *pstRrcEphemClockParam
)
{
    /*
    <!ELEMENT cuc (#PCDATA)>
    <!ELEMENT ecc (#PCDATA)>
    <!ELEMENT cus (#PCDATA)>
    <!ELEMENT power_half (#PCDATA)>
    <!ELEMENT toe (#PCDATA)>
    <!ELEMENT fit_flag (#PCDATA)>
    <!ELEMENT aoda (#PCDATA)>
    <!ELEMENT cic (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cuc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_CUC,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usCUc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_CUC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT ecc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_ECC,
                                                         pstRrcEphemClockParam->ulEcc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_ECC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cus (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_CUS,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usCUs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_CUS fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT power_half (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_POWER_HALF,
                                                         pstRrcEphemClockParam->ulPowerHalf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_POWER_HALF fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT toe (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_TOE,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usTOe))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_TOE fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT fit_flag (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_FIT_FLAG,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucFitFlag))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_FIT_FLAG fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT aoda (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_AODA,
                                                         (VOS_UINT32)pstRrcEphemClockParam->ucAodo))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_AODA fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cic (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_CIC,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usCIc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree: WARNING: Create MTA_AGPS_LABEL_CIC fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour
功能描述  : 将AGPS_RRC_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的子节点
            包括<omega0>、<cis>、<i0>、<crc>、<omega>、<omega_dot>、<idot>子节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRrcEphemClockParam   属性转换后挂载的父节点
            pstRrcEphemClockParam      待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRrcEphemClockParam,
    AGPS_RRC_EPHEM_CLOCK_PARAM_STRU    *pstRrcEphemClockParam
)
{
    /*
    <!ELEMENT omega0 (#PCDATA)>
    <!ELEMENT cis (#PCDATA)>
    <!ELEMENT i0 (#PCDATA)>
    <!ELEMENT crc (#PCDATA)>
    <!ELEMENT omega (#PCDATA)>
    <!ELEMENT omega_dot (#PCDATA)>
    <!ELEMENT idot (#PCDATA)>
    */
    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT omega0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_OMEGA0,
                                                         pstRrcEphemClockParam->ulOmega0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_OMEGA0 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT cis (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_CIS,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usCIs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_CIS fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT i0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_I0,
                                                         pstRrcEphemClockParam->ulI0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_I0 fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT crc (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_CRC,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usCRc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_CRC fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT omega (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_OMEGA,
                                                         pstRrcEphemClockParam->ulOmega))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_OMEGA fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT omega_dot (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_OMEGA_DOT,
                                                         pstRrcEphemClockParam->ulOmegaDot))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_OMEGA_DOT fail!");
        return VOS_ERR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT idot (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcEphemClockParam,
                                                         MTA_AGPS_LABEL_IDOT,
                                                         (VOS_UINT32)pstRrcEphemClockParam->usIDot))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour: WARNING: Create MTA_AGPS_LABEL_IDOT fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrcEphemClockParam
功能描述  : 将AGPS_RRC_EPHEM_CLOCK_PARAM_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx            XML上下文
            pstRrcEphemClockParam    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcEphemClockParam(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_EPHEM_CLOCK_PARAM_STRU    *pstRrcEphemClockParam
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrcEphemClockParam;

     /* <!ELEMENT ephem_and_clock (l2_code,ura,sv_health,iodc,l2p_flag,esr1,esr2,esr3,esr4,tgd,toc,af2,af1,af0,
           crs,delta_n,m0,cuc,ecc,cus,power_half,toe,fit_flag,aoda,cic,omega0,cis,i0,crc,omega,omega_dot,idot)>
                <!ELEMENT l2_code (#PCDATA)>
                <!ELEMENT ura (#PCDATA)>
                <!ELEMENT sv_health (#PCDATA)>
                <!ELEMENT iodc (#PCDATA)>
                <!ELEMENT l2p_flag (#PCDATA)>
                <!ELEMENT esr1 (#PCDATA)>
                <!ELEMENT esr2 (#PCDATA)>
                <!ELEMENT esr3 (#PCDATA)>
                <!ELEMENT esr4 (#PCDATA)>
                <!ELEMENT tgd (#PCDATA)>
                <!ELEMENT toc (#PCDATA)>
                <!ELEMENT af2 (#PCDATA)>
                <!ELEMENT af1 (#PCDATA)>
                <!ELEMENT af0 (#PCDATA)>
                <!ELEMENT crs (#PCDATA)>
                <!ELEMENT delta_n (#PCDATA)>
                <!ELEMENT m0 (#PCDATA)>
                <!ELEMENT cuc (#PCDATA)>
                <!ELEMENT ecc (#PCDATA)>
                <!ELEMENT cus (#PCDATA)>
                <!ELEMENT power_half (#PCDATA)>
                <!ELEMENT toe (#PCDATA)>
                <!ELEMENT fit_flag (#PCDATA)>
                <!ELEMENT aoda (#PCDATA)>
                <!ELEMENT cic (#PCDATA)>
                <!ELEMENT omega0 (#PCDATA)>
                <!ELEMENT cis (#PCDATA)>
                <!ELEMENT i0 (#PCDATA)>
                <!ELEMENT crc (#PCDATA)>
                <!ELEMENT omega (#PCDATA)>
                <!ELEMENT omega_dot (#PCDATA)>
                <!ELEMENT idot (#PCDATA)> */

    /* 调用XML API提供的接口，创建<ephem_and_clock> 节点并设置标签 */
    pstNodeRrcEphemClockParam = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_EPHEM_AND_CLOCK);
    if (VOS_NULL_PTR == pstNodeRrcEphemClockParam)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcEphemClockParam: WARNING:Create MTA_AGPS_LABEL_EPHEM_AND_CLOCK fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part1 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartOne(pstXmlCommCtx,
                                                              pstNodeRrcEphemClockParam,
                                                              pstRrcEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcEphemClockParam: WARNING: Add Child Nodes Part1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part2 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartTwo(pstXmlCommCtx,
                                                              pstNodeRrcEphemClockParam,
                                                              pstRrcEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcEphemClockParam: WARNING: Add Child Nodes Part2 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part3 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartThree(pstXmlCommCtx,
                                                              pstNodeRrcEphemClockParam,
                                                              pstRrcEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcEphemClockParam: WARNING: Add Child Nodes Part3 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下Part4 */
    if (VOS_OK != TAF_MTA_AGPS_AddRrcEphemClockParamChildNodesPartFour(pstXmlCommCtx,
                                                              pstNodeRrcEphemClockParam,
                                                              pstRrcEphemClockParam))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcEphemClockParam: WARNING: Add Child Nodes Part4 fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrcEphemClockParam;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrlpIonosphericModel
功能描述  : 将AGPS_RRLP_IONOSPHERIC_MODEL_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx             XML上下文
            pstRrlpIonosphericModel   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpIonosphericModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_IONOSPHERIC_MODEL_STRU   *pstRrlpIonosphericModel
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrlpIonosphericModel;

     /* <!ELEMENT ionospheric_model (alfa0,alfa1,alfa2,alfa3,beta0,beta1,beta2,beta3)>
            <!ELEMENT alfa0 (#PCDATA)>
            <!ELEMENT alfa1 (#PCDATA)>
            <!ELEMENT alfa2 (#PCDATA)>
            <!ELEMENT alfa3 (#PCDATA)>
            <!ELEMENT beta0 (#PCDATA)>
            <!ELEMENT beta1 (#PCDATA)>
            <!ELEMENT beta2 (#PCDATA)>
            <!ELEMENT beta3 (#PCDATA)> */

    /* 调用XML API提供的接口，创建<ionospheric_model>节点并设置标签 */
    pstNodeRrlpIonosphericModel = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_IONOSPHERIC_MODEL);
    if (VOS_NULL_PTR == pstNodeRrlpIonosphericModel)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING:Create MTA_AGPS_LABEL_IONOSPHERIC_MODEL fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_ALFA0,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cAlpha0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_ALFA1,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cAlpha1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_ALFA2,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cAlpha2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA2 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa3 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_ALFA3,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cAlpha3))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA3 fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_BETA0,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cBeta0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_BETA1,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cBeta1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_BETA2,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cBeta2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA2 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta3 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpIonosphericModel,
                                                       MTA_AGPS_LABEL_BETA3,
                                                       (VOS_INT32)pstRrlpIonosphericModel->cBeta3))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA3 fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrlpIonosphericModel;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrcIonosphericModel
功能描述  : 将AGPS_RRC_IONOSPHERIC_MODEL_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx             XML上下文
            pstRrcIonosphericModel    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcIonosphericModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_IONOSPHERIC_MODEL_STRU    *pstRrcIonosphericModel
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrcIonosphericModel;
     /* <!ELEMENT ionospheric_model (alfa0,alfa1,alfa2,alfa3,beta0,beta1,beta2,beta3)>
            <!ELEMENT alfa0 (#PCDATA)>
            <!ELEMENT alfa1 (#PCDATA)>
            <!ELEMENT alfa2 (#PCDATA)>
            <!ELEMENT alfa3 (#PCDATA)>
            <!ELEMENT beta0 (#PCDATA)>
            <!ELEMENT beta1 (#PCDATA)>
            <!ELEMENT beta2 (#PCDATA)>
            <!ELEMENT beta3 (#PCDATA)> */

    /* 调用XML API提供的接口，创建<ionospheric_model> 节点并设置标签 */
    pstNodeRrcIonosphericModel = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_IONOSPHERIC_MODEL);
    if (VOS_NULL_PTR == pstNodeRrcIonosphericModel)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING:Create MTA_AGPS_LABEL_IONOSPHERIC_MODEL fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_ALFA0,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucAlpha0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_ALFA1,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucAlpha1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_ALFA2,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucAlpha2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA2 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT alfa3 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_ALFA3,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucAlpha3))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_ALFA3 fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_BETA0,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucBeta0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_BETA1,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucBeta1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta2 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_BETA2,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucBeta2))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA2 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT beta3 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcIonosphericModel,
                                                         MTA_AGPS_LABEL_BETA3,
                                                         (VOS_UINT32)pstRrcIonosphericModel->ucBeta3))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcIonosphericModel: WARNING: Create MTA_AGPS_LABEL_BETA3 fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrcIonosphericModel;

}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrlpUtcModel
功能描述  : 将AGPS_RRLP_UTC_MODEL_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx         XML上下文
            pstRrlpUtcModel       待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpUtcModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_UTC_MODEL_STRU           *pstRrlpUtcModel
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrlpUtcModel;

     /* <!ELEMENT UTC_model (a1,a0,tot,wnt,dtls,wnlsf,dn,dtlsf)>
            <!ELEMENT a1 (#PCDATA)>
            <!ELEMENT a0 (#PCDATA)>
            <!ELEMENT tot (#PCDATA)>
            <!ELEMENT wnt (#PCDATA)>
            <!ELEMENT dtls (#PCDATA)>
            <!ELEMENT wnlsf (#PCDATA)>
            <!ELEMENT dn (#PCDATA)>
            <!ELEMENT dtlsf (#PCDATA)> */

    /* 调用XML API提供的接口，创建<UTC_model>  节点并设置标签 */
    pstNodeRrlpUtcModel = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_UTC_MODEL);
    if (VOS_NULL_PTR == pstNodeRrlpUtcModel)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING:Create MTA_AGPS_LABEL_UTC_MODEL fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT a1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpUtcModel,
                                                       MTA_AGPS_LABEL_A1,
                                                       pstRrlpUtcModel->lA1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_A1 fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT a0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpUtcModel,
                                                       MTA_AGPS_LABEL_A0,
                                                       pstRrlpUtcModel->lA0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_A0 fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT tot (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpUtcModel,
                                                         MTA_AGPS_LABEL_TOT,
                                                         (VOS_UINT32)pstRrlpUtcModel->ucTOt))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_TOT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT wnt (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpUtcModel,
                                                         MTA_AGPS_LABEL_WNT,
                                                         (VOS_UINT32)pstRrlpUtcModel->ucWnT))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_WNT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT dtls (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpUtcModel,
                                                       MTA_AGPS_LABEL_DTLS,
                                                       (VOS_INT32)pstRrlpUtcModel->cDeltaTLs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_DTLS fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT wnlsf (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpUtcModel,
                                                         MTA_AGPS_LABEL_WNLSF,
                                                         (VOS_UINT32)pstRrlpUtcModel->ucWnLsf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_WNLSF fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT dn (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpUtcModel,
                                                       MTA_AGPS_LABEL_DN,
                                                       (VOS_INT32)pstRrlpUtcModel->cDn))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_DN fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT dtlsf (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpUtcModel,
                                                       MTA_AGPS_LABEL_DTLSF,
                                                       (VOS_INT32)pstRrlpUtcModel->cDeltaTLsf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpUtcModel: WARNING: Create MTA_AGPS_LABEL_DTLSF fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrlpUtcModel;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrcUtcModel
功能描述  : 将AGPS_RRC_UTC_MODEL_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx         XML上下文
            pstRrcUtcModel        待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619/d00212987
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcUtcModel(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_UTC_MODEL_STRU            *pstRrcUtcModel
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrcUtcModel;

     /* <!ELEMENT UTC_model (a1,a0,tot,wnt,dtls,wnlsf,dn,dtlsf)>
            <!ELEMENT a1 (#PCDATA)>
            <!ELEMENT a0 (#PCDATA)>
            <!ELEMENT tot (#PCDATA)>
            <!ELEMENT wnt (#PCDATA)>
            <!ELEMENT dtls (#PCDATA)>
            <!ELEMENT wnlsf (#PCDATA)>
            <!ELEMENT dn (#PCDATA)>
            <!ELEMENT dtlsf (#PCDATA)> */

    /* 调用XML API提供的接口，创建<UTC_model> 节点并设置标签 */
    pstNodeRrcUtcModel = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_UTC_MODEL);
    if (VOS_NULL_PTR == pstNodeRrcUtcModel)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING:Create MTA_AGPS_LABEL_UTC_MODEL fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT a1 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_A1,
                                                         pstRrcUtcModel->ulA1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_A1 fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT a0 (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_A0,
                                                         pstRrcUtcModel->ulA0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_A0 fail!");
        return VOS_NULL_PTR;
    }


    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT tot (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_TOT,
                                                         (VOS_UINT32)pstRrcUtcModel->ucTOt))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_TOT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT wnt (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_WNT,
                                                         (VOS_UINT32)pstRrcUtcModel->ucWnT))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_WNT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT dtls (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_DTLS,
                                                         (VOS_INT32)pstRrcUtcModel->ucDeltaTLs))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_DTLS fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT wnlsf (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_WNLSF,
                                                         (VOS_UINT32)pstRrcUtcModel->ucWnLsf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_WNLSF fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT dn (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_DN,
                                                         (VOS_INT32)pstRrcUtcModel->ucDn))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_DN fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    /* <!ELEMENT dtlsf (#PCDATA)> */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcUtcModel,
                                                         MTA_AGPS_LABEL_DTLSF,
                                                         (VOS_INT32)pstRrcUtcModel->ucDeltaTLsf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcUtcModel: WARNING: Create MTA_AGPS_LABEL_DTLSF fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrcUtcModel;

}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertAlmanac
功能描述  : 将AGPS_ALMANAC_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx         XML上下文
            pstAlmanac            待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAlmanac(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ALMANAC_STRU                  *pstAlmanac
)
{
    XML_COMM_NODE_STRU                 *pstNodeAlmanac;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_UINT32                          ulLoop;

    /*
    <!ELEMENT almanac (wna,alm_elem*)>
             <!ELEMENT wna (#PCDATA)>
             <!ELEMENT alm_elem (data_id?,sat_id,alm_ecc,alm_toa,alm_ksii,alm_omega_dot,alm_sv_health,alm_power_half,alm_omega0,alm_omega,alm_m0,alm_af0,alm_af1)>
                <!ELEMENT data_id (#PCDATA)>
                <!ELEMENT alm_ecc (#PCDATA)>
                <!ELEMENT alm_toa (#PCDATA)>
                <!ELEMENT alm_ksii (#PCDATA)>
                <!ELEMENT alm_omega_dot (#PCDATA)>
                <!ELEMENT alm_sv_health (#PCDATA)>
                <!ELEMENT alm_power_half (#PCDATA)>
                <!ELEMENT alm_omega0 (#PCDATA)>
                <!ELEMENT alm_omega (#PCDATA)>
                <!ELEMENT alm_m0 (#PCDATA)>
                <!ELEMENT alm_af0 (#PCDATA)>
                <!ELEMENT alm_af1 (#PCDATA)>
    */

    /* 创建almanac 节点并设置标签 */
    pstNodeAlmanac = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ALMANAC);
    if (VOS_NULL_PTR == pstNodeAlmanac)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAlmanac: WARNING: Create MTA_AGPS_LABEL_ALMANAC fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<wna>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAlmanac,
                                                         MTA_AGPS_LABEL_WNA,
                                                         (VOS_UINT32)pstAlmanac->ucWnA))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAlmanac: WARNING: Create MTA_AGPS_LABEL_WNA fail!");
        return VOS_NULL_PTR;
    }


    switch (pstAlmanac->stAlmanacSatInfoList.enAlmanacSatInfoChoice)
    {
        case AGPS_ALMANAC_SAT_INFO_TYPE_RRLP:
            /* 转换<alm_elem>子结构并挂到当前节点下 */
            for (ulLoop = 0; ulLoop < pstAlmanac->stAlmanacSatInfoList.ulAlmancSatNum; ulLoop++)
            {
                pstChildNode = TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo(pstXmlCommCtx,
                                                                     &pstAlmanac->stAlmanacSatInfoList.u.astRrlpAlmanacSatInfo[ulLoop]);
                ulReturnValue = XML_COMM_AddAChildNode(pstNodeAlmanac, pstChildNode, VOS_NULL_PTR);
                if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
                {
                    MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertAcquAssist: WARNING: Add alm_elem(RRLP) child fail!", ulLoop);
                    return VOS_NULL_PTR;
                }
            }
            break;
        case AGPS_ALMANAC_SAT_INFO_TYPE_RRC:
            /* 转换<alm_elem>子结构并挂到当前节点下 */
            for (ulLoop = 0; ulLoop < pstAlmanac->stAlmanacSatInfoList.ulAlmancSatNum; ulLoop++)
            {
                pstChildNode = TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo(pstXmlCommCtx,
                                                                     &pstAlmanac->stAlmanacSatInfoList.u.astRrcAlmanacSatInfo[ulLoop]);
                ulReturnValue = XML_COMM_AddAChildNode(pstNodeAlmanac, pstChildNode, VOS_NULL_PTR);
                if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
                {
                    MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertAcquAssist: WARNING: Add alm_elem(RRC) child fail!", ulLoop);
                    return VOS_NULL_PTR;
                }
            }
            break;
        default:
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertAlmanac: WARNING: enAlmanacSatInfoChoice is abnormal!",
                            pstAlmanac->stAlmanacSatInfoList.enAlmanacSatInfoChoice);
            return VOS_NULL_PTR;
    }

    return pstNodeAlmanac;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertDataIdOfRrlpAlmanacSatInfo
功能描述  : 将AGPS_RRLP_ALMANAC_SAT_INFO_STRU结构体中的ucDataId转换为树结构
输入参数  : pstXmlCommCtx               XML上下文
            pstRrlpAlmanacSatInfo       待转换结构体
            pstNodeRrlpAlmanacSatInfo   父节点
输出参数  : 无
返 回 值  : VOS_ERR      增加data_id节点失败
            VOS_OK       增加data_id节点成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_ConvertDataIdOfRrlpAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_ALMANAC_SAT_INFO_STRU    *pstRrlpAlmanacSatInfo,
    XML_COMM_NODE_STRU                 *pstNodeRrlpAlmanacSatInfo
)
{
    if (VOS_TRUE == pstRrlpAlmanacSatInfo->bitOpDataId)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeRrlpAlmanacSatInfo,
                                                             MTA_AGPS_LABEL_DATA_ID,
                                                             (VOS_UINT32)pstRrlpAlmanacSatInfo->ucDataId))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertDataIdOfRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_DATA_ID fail!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo
功能描述  : 将AGPS_RRLP_ALMANAC_SAT_INFO_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstRrlpAlmanacSatInfo   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_ALMANAC_SAT_INFO_STRU    *pstRrlpAlmanacSatInfo
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrlpAlmanacSatInfo;

    /*
    <!ELEMENT alm_elem (data_id?,sat_id,alm_ecc,alm_toa,alm_ksii,alm_omega_dot,alm_sv_health,alm_power_half,alm_omega0,alm_omega,alm_m0,alm_af0,alm_af1)>
                <!ELEMENT data_id (#PCDATA)>
                <!ELEMENT alm_ecc (#PCDATA)>
                <!ELEMENT alm_toa (#PCDATA)>
                <!ELEMENT alm_ksii (#PCDATA)>
                <!ELEMENT alm_omega_dot (#PCDATA)>
                <!ELEMENT alm_sv_health (#PCDATA)>
                <!ELEMENT alm_power_half (#PCDATA)>
                <!ELEMENT alm_omega0 (#PCDATA)>
                <!ELEMENT alm_omega (#PCDATA)>
                <!ELEMENT alm_m0 (#PCDATA)>
                <!ELEMENT alm_af0 (#PCDATA)>
                <!ELEMENT alm_af1 (#PCDATA)>
    */

    /* 创建alm_elem节点并设置标签 */
    pstNodeRrlpAlmanacSatInfo = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ALM_ELEM);
    if (VOS_NULL_PTR == pstNodeRrlpAlmanacSatInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_ELEM fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<data_id>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_ConvertDataIdOfRrlpAlmanacSatInfo(pstXmlCommCtx,
                                                                 pstRrlpAlmanacSatInfo,
                                                                 pstNodeRrlpAlmanacSatInfo))
    {
        return VOS_NULL_PTR;
    }

    /* 转换<sat_id>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_SAT_ID,
                                                         (VOS_UINT32)pstRrlpAlmanacSatInfo->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_SAT_ID fail!");
        return VOS_NULL_PTR;
    }


    /* 转换<alm_ecc>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_ECC,
                                                         (VOS_UINT32)pstRrlpAlmanacSatInfo->usAlmEcc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_ECC fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_toa>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_TOA,
                                                         (VOS_UINT32)pstRrlpAlmanacSatInfo->ucAlmToa))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_TOA fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_ksii>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpAlmanacSatInfo,
                                                       MTA_AGPS_LABEL_ALM_KSII,
                                                       (VOS_INT32)pstRrlpAlmanacSatInfo->sAlmKsii))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_KSII fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_omega_dot>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpAlmanacSatInfo,
                                                       MTA_AGPS_LABEL_ALM_OMEGA_DOT,
                                                       (VOS_INT32)pstRrlpAlmanacSatInfo->sAlmOmegaDot))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_OMEGA_DOT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_sv_health>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_SV_HEALTH,
                                                         (VOS_UINT32)pstRrlpAlmanacSatInfo->ucAlmSvHealth))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_SV_HEALTH fail!");
        return VOS_NULL_PTR;
    }


    /* 转换<alm_power_half>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrlpAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_POWER_HALF,
                                                         pstRrlpAlmanacSatInfo->ulAlmPowerHalf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_POWER_HALF fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_omega0>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpAlmanacSatInfo,
                                                       MTA_AGPS_LABEL_ALM_OMEGA0,
                                                       pstRrlpAlmanacSatInfo->lAlmOmega0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_OMEGA0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_omega>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpAlmanacSatInfo,
                                                       MTA_AGPS_LABEL_ALM_OMEGA,
                                                       pstRrlpAlmanacSatInfo->lAlmOmega))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_OMEGA fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_m0>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpAlmanacSatInfo,
                                                       MTA_AGPS_LABEL_ALM_M0,
                                                       pstRrlpAlmanacSatInfo->lAlmM0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_M0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_af0>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpAlmanacSatInfo,
                                                       MTA_AGPS_LABEL_ALM_AF0,
                                                       (VOS_INT32)pstRrlpAlmanacSatInfo->sAlmAf0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_AF0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_af1>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeRrlpAlmanacSatInfo,
                                                       MTA_AGPS_LABEL_ALM_AF1,
                                                       (VOS_INT32)pstRrlpAlmanacSatInfo->sAlmAf1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_AF1 fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrlpAlmanacSatInfo;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertDataIdOfRrcAlmanacSatInfo
功能描述  : 将AGPS_RRC_ALMANAC_SAT_INFO_STRU结构体中的ucDataId转换为树结构
输入参数  : pstXmlCommCtx               XML上下文
            pstRrcAlmanacSatInfo       待转换结构体
            pstNodeRrcAlmanacSatInfo   父节点
输出参数  : 无
返 回 值  : VOS_ERR      增加data_id节点失败
            VOS_OK       增加data_id节点成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_ConvertDataIdOfRrcAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_ALMANAC_SAT_INFO_STRU     *pstRrcAlmanacSatInfo,
    XML_COMM_NODE_STRU                 *pstNodeRrcAlmanacSatInfo
)
{
    /* 判断bit位是否为1 */
    if (VOS_TRUE == pstRrcAlmanacSatInfo->bitOpDataId)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeRrcAlmanacSatInfo,
                                                             MTA_AGPS_LABEL_DATA_ID,
                                                             (VOS_UINT32)pstRrcAlmanacSatInfo->ucDataId))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertDataIdOfRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_DATA_ID fail!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo
功能描述  : 将AGPS_RRC_ALMANAC_SAT_INFO_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstRrcAlmanacSatInfo    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_ALMANAC_SAT_INFO_STRU     *pstRrcAlmanacSatInfo
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrcAlmanacSatInfo;

    /*
    <!ELEMENT alm_elem (data_id?,sat_id,alm_ecc,alm_toa,alm_ksii,alm_omega_dot,alm_sv_health,alm_power_half,alm_omega0,alm_omega,alm_m0,alm_af0,alm_af1)>
                <!ELEMENT data_id (#PCDATA)>
                <!ELEMENT alm_ecc (#PCDATA)>
                <!ELEMENT alm_toa (#PCDATA)>
                <!ELEMENT alm_ksii (#PCDATA)>
                <!ELEMENT alm_omega_dot (#PCDATA)>
                <!ELEMENT alm_sv_health (#PCDATA)>
                <!ELEMENT alm_power_half (#PCDATA)>
                <!ELEMENT alm_omega0 (#PCDATA)>
                <!ELEMENT alm_omega (#PCDATA)>
                <!ELEMENT alm_m0 (#PCDATA)>
                <!ELEMENT alm_af0 (#PCDATA)>
                <!ELEMENT alm_af1 (#PCDATA)>
    */

    /* 创建alm_elem节点并设置标签 */
    pstNodeRrcAlmanacSatInfo = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ALM_ELEM);
    if (VOS_NULL_PTR == pstNodeRrcAlmanacSatInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_ELEM fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<data_id>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_ConvertDataIdOfRrcAlmanacSatInfo(pstXmlCommCtx,
                                                                pstRrcAlmanacSatInfo,
                                                                pstNodeRrcAlmanacSatInfo))
    {
        return VOS_NULL_PTR;
    }

    /* 转换<sat_id>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_SAT_ID,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_SAT_ID fail!");
        return VOS_NULL_PTR;
    }


    /* 转换<alm_ecc>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_ECC,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->usAlmEcc))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_ECC fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_toa>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_TOA,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->ucAlmToa))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_TOA fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_ksii>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_KSII,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->usAlmKsii))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_KSII fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_omega_dot>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_OMEGA_DOT,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->usAlmOmegaDot))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_OMEGA_DOT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_sv_health>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_SV_HEALTH,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->ucAlmSvHealth))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_SV_HEALTH fail!");
        return VOS_NULL_PTR;
    }


    /* 转换<alm_power_half>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_POWER_HALF,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->ulAlmPowerHalf))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_POWER_HALF fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_omega0>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_OMEGA0,
                                                         pstRrcAlmanacSatInfo->ulAlmOmega0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_OMEGA0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_omega>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_OMEGA,
                                                         pstRrcAlmanacSatInfo->ulAlmOmega))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_OMEGA fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_m0>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_M0,
                                                         pstRrcAlmanacSatInfo->ulAlmM0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_M0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_af0>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_AF0,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->usAlmAf0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_AF0 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<alm_af1>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeRrcAlmanacSatInfo,
                                                         MTA_AGPS_LABEL_ALM_AF1,
                                                         (VOS_UINT32)pstRrcAlmanacSatInfo->usAlmAf1))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcAlmanacSatInfo: WARNING: Create MTA_AGPS_LABEL_ALM_AF1 fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrcAlmanacSatInfo;

}


/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertAcquAssist
功能描述  : 将AGPS_ACQU_ASSIST_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstAcquAssist           待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAcquAssist(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ACQU_ASSIST_STRU              *pstAcquAssist
)
{
    XML_COMM_NODE_STRU                 *pstNodeAcquAssist;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_UINT32                          ulLoop;

    /*
    <!ELEMENT acqu_assist (tow_msec,sat_info)>
         <!ELEMENT tow_msec (#PCDATA)>
         <!ELEMENT sat_info (sat_id,dopl0,dopl_extra?,code_ph,code_ph_int,GPS_bitno,srch_w,az_el?)>
            <!ELEMENT dopl0 (#PCDATA)>
            <!ELEMENT dopl_extra (dopl1,dopl1_uncert)>
               <!ELEMENT dopl1 (#PCDATA)>
               <!ELEMENT dopl1_uncert EMPTY>
               <!ATTLIST dopl1_uncert literal (hz12-5|hz25|hz50|hz100|hz200) #REQUIRED>
            <!ELEMENT code_ph (#PCDATA)>
            <!ELEMENT code_ph_int (#PCDATA)>
            <!ELEMENT GPS_bitno (#PCDATA)>
            <!ELEMENT srch_w (#PCDATA)>
            <!ELEMENT az_el (az,elev)>
               <!ELEMENT az (#PCDATA)>
               <!ELEMENT elev (#PCDATA)>
    */

    /* 创建acqu_assist 节点并设置标签 */
    pstNodeAcquAssist = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_ACPU_ASSIST);
    if (VOS_NULL_PTR == pstNodeAcquAssist)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquAssist: WARNING:Create MTA_AGPS_LABEL_ACPU_ASSIST fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<tow_msec>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAcquAssist,
                                                         MTA_AGPS_LABEL_TOW_MSEC,
                                                         pstAcquAssist->ulTowMsec))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquAssist: WARNING: Create MTA_AGPS_LABEL_TOW_MSEC fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<sat_info>子结构并挂到当前节点下 */
    /* AGPS_ACQU_SAT_INFO_LIST_STRU结构体中的astSatInfo是数组，而27007 R9中的sat_info是单个的，
       但R11后的XML规范已经升级为多个，故按照多个来填写 */
    for (ulLoop = 0; ulLoop < pstAcquAssist->stSatInfoList.ulSatInfoNum; ulLoop++)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertAcquSatInfo(pstXmlCommCtx,
                                                       &pstAcquAssist->stSatInfoList.astSatInfo[ulLoop]);
        if (VOS_NULL_PTR == pstChildNode)
        {
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertAcquAssist: WARNING: Convert sat_info fail!", ulLoop);
            return VOS_NULL_PTR;
        }

        ulReturnValue = XML_COMM_AddAChildNode(pstNodeAcquAssist, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquAssist: WARNING: Add sat_info child fail!");
            return VOS_NULL_PTR;
        }
    }

    return pstNodeAcquAssist;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertAcquSatInfo
功能描述  : 将AGPS_ACQU_SAT_INFO_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstAcquSatInfo         待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAcquSatInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_ACQU_SAT_INFO_STRU            *pstAcquSatInfo
)
{
    XML_COMM_NODE_STRU                 *pstNodeAcquSatInfo;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
         <!ELEMENT sat_info (sat_id,dopl0,dopl_extra?,code_ph,code_ph_int,GPS_bitno,srch_w,az_el?)>
            <!ELEMENT dopl0 (#PCDATA)>
            <!ELEMENT dopl_extra (dopl1,dopl1_uncert)>
               <!ELEMENT dopl1 (#PCDATA)>
               <!ELEMENT dopl1_uncert EMPTY>
               <!ATTLIST dopl1_uncert literal (hz12-5|hz25|hz50|hz100|hz200) #REQUIRED>
            <!ELEMENT code_ph (#PCDATA)>
            <!ELEMENT code_ph_int (#PCDATA)>
            <!ELEMENT GPS_bitno (#PCDATA)>
            <!ELEMENT srch_w (#PCDATA)>
            <!ELEMENT az_el (az,elev)>
               <!ELEMENT az (#PCDATA)>
               <!ELEMENT elev (#PCDATA)>
    */

    /* 创建sat_info  节点并设置标签 */
    pstNodeAcquSatInfo = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_SAT_INFO);
    if (VOS_NULL_PTR == pstNodeAcquSatInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING:Create MTA_AGPS_LABEL_SAT_INFO fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<sat_id>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAcquSatInfo,
                                                         MTA_AGPS_LABEL_SAT_ID,
                                                         (VOS_UINT32)pstAcquSatInfo->ucSatId))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Create MTA_AGPS_LABEL_SAT_ID fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<dopl0>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewSignedIntLeafNode(pstXmlCommCtx,
                                                       pstNodeAcquSatInfo,
                                                       MTA_AGPS_LABEL_DOPL0,
                                                       (VOS_INT32)pstAcquSatInfo->sDopl0))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Create MTA_AGPS_LABEL_DOPL0 fail!");
        return VOS_NULL_PTR;
    }


    /* 转换<dopl_extra>子结构并挂到当前节点下 */
    if (1 == pstAcquSatInfo->bitOpExtraDopplerInfo)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertExtraDopplerInfo(pstXmlCommCtx,
                                                            &pstAcquSatInfo->stExtraDopplerInfo);

        ulReturnValue = XML_COMM_AddAChildNode(pstNodeAcquSatInfo, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Add dopl_extra child fail!");
            return VOS_NULL_PTR;
        }
    }

    /* 转换<code_ph>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAcquSatInfo,
                                                         MTA_AGPS_LABEL_CODE_PH,
                                                         (VOS_UINT32)pstAcquSatInfo->usCodePhase))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Create MTA_AGPS_LABEL_CODE_PH fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<code_ph_int>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAcquSatInfo,
                                                         MTA_AGPS_LABEL_CODE_PH_INT,
                                                         (VOS_UINT32)pstAcquSatInfo->ucIntCodePhase))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Create MTA_AGPS_LABEL_CODE_PH_INT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<GPS_bitno>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAcquSatInfo,
                                                         MTA_AGPS_LABEL_GPS_BITNO,
                                                         (VOS_UINT32)pstAcquSatInfo->ucGpsBitNum))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Create MTA_AGPS_LABEL_GPS_BITNO fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<srch_w>节点并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAcquSatInfo,
                                                         MTA_AGPS_LABEL_SRCH_W,
                                                         (VOS_UINT32)pstAcquSatInfo->enCodePhaseSearchWin))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Create MTA_AGPS_LABEL_SRCH_W fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<az_el>子结构并挂到当前节点下 */
    if (1 == pstAcquSatInfo->bitOpAzimuthAndEleva)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertAzimuthAndEleva(pstXmlCommCtx,
                                                           &pstAcquSatInfo->stAzimuthAndEleva);

        ulReturnValue = XML_COMM_AddAChildNode(pstNodeAcquSatInfo, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAcquSatInfo: WARNING: Add az_el child fail!");
            return VOS_NULL_PTR;
        }
    }

    return pstNodeAcquSatInfo;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertExtraDopplerInfo
功能描述  : 将AGPS_EXTRA_DOPPLER_INFO_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstExtraDopplerInfo     待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertExtraDopplerInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_EXTRA_DOPPLER_INFO_STRU       *pstExtraDopplerInfo
)
{
    XML_COMM_NODE_STRU                 *pstNodeExtraDopplerInfo;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
    <!ELEMENT dopl_extra (dopl1,dopl1_uncert)>
                   <!ELEMENT dopl1 (#PCDATA)>
                   <!ELEMENT dopl1_uncert EMPTY>
                   <!ATTLIST dopl1_uncert literal (hz12-5|hz25|hz50|hz100|hz200) #REQUIRED>
    */
    /* 创建dopl_extra节点并设置标签 */
    pstNodeExtraDopplerInfo = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_DOPL_EXTRA);
    if (VOS_NULL_PTR == pstNodeExtraDopplerInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING:Create MTA_AGPS_LABEL_DOPL_EXTRA fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<dopl1>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeExtraDopplerInfo,
                                                         MTA_AGPS_LABEL_DOPL1,
                                                         (VOS_UINT32)pstExtraDopplerInfo->ucDoppler1stOrder))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: Create MTA_AGPS_LABEL_DOPL1 fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<dopl1_uncert>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_DOPL1_UNCERT);
    if (VOS_NULL_PTR == pstChildNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: Create MTA_AGPS_LABEL_DOPL1_UNCERT fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST dopl1_uncert literal (hz12-5|hz25|hz50|hz100|hz200) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    /* 设置属性值 */
    switch (pstExtraDopplerInfo->enDopplerUncertn)
    {
        case AGPS_DOPPLER_UNCERTN_HZ125:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_HZ12_5);
            break;
        case AGPS_DOPPLER_UNCERTN_HZ25:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_HZ25);
            break;
        case AGPS_DOPPLER_UNCERTN_HZ50:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_HZ50);
            break;
        case AGPS_DOPPLER_UNCERTN_HZ100:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_HZ100);
            break;
        case AGPS_DOPPLER_UNCERTN_HZ200:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_HZ200);
            break;
        default:
            /* dopl1_uncert的属性是#REQUIRED类型的，其它值都按照异常处理，直接退出 */
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: enDopplerUncertn is abnormal!",
                             pstExtraDopplerInfo->enDopplerUncertn);

            return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: set dopl1_uncert attribute fail!");
        return VOS_NULL_PTR;
    }

    /* 将属性增加至该节点上 */
    ulReturnValue = XML_COMM_AddAnAttribute(pstChildNode, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: Add attribute for dopl1_uncert fail!");
        return VOS_NULL_PTR;
    }

    /* 将该节点增加至父节点上 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeExtraDopplerInfo, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: Add dopl1_uncert child fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeExtraDopplerInfo;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertAzimuthAndEleva
功能描述  : 将AGPS_AZIMUTH_AND_ELEVA_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstAzimuthAndEleva      待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertAzimuthAndEleva(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_AZIMUTH_AND_ELEVA_STRU        *pstAzimuthAndEleva
)
{
    XML_COMM_NODE_STRU                 *pstNodeAzimuthAndEleva;

    /* <!ELEMENT az_el (az,elev)>
               <!ELEMENT az (#PCDATA)>
               <!ELEMENT elev (#PCDATA)>
     */
    /* 创建az_el 节点并设置标签 */
    pstNodeAzimuthAndEleva = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_AZ_EL);
    if (VOS_NULL_PTR == pstNodeAzimuthAndEleva)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertAzimuthAndEleva: WARNING:Create MTA_AGPS_LABEL_AZ_EL fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<az>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAzimuthAndEleva,
                                                         MTA_AGPS_LABEL_AZ,
                                                         (VOS_UINT32)pstAzimuthAndEleva->ucAzimuth))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: Create MTA_AGPS_LABEL_AZ fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<elev>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                         pstNodeAzimuthAndEleva,
                                                         MTA_AGPS_LABEL_ELEV,
                                                         (VOS_UINT32)pstAzimuthAndEleva->ucEleva))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertExtraDopplerInfo: WARNING: Create MTA_AGPS_LABEL_ELEV fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeAzimuthAndEleva;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertGpsRealTimeIntegrity
功能描述  : 将AGPS_BAD_SAT_LIST_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx           XML上下文
            pstBadSatList           待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertGpsRealTimeIntegrity(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_BAD_SAT_LIST_STRU             *pstBadSatList
)
{
    XML_COMM_NODE_STRU                 *pstNodeBadSatList;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* <!ELEMENT GPS_rt_integrity (#PCDATA)> */

    if (0 == pstBadSatList->ulBadSatListBadSatListNum)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsRealTimeIntegrity: WARNING: ulBadSatListBadSatListNum = 0!");
        return VOS_NULL_PTR;
    }

    /* <!ELEMENT GPS_rt_integrity (#PCDATA)> */
    /* 虽然结构体中GPS_rt_integrity是以数组形式体现，但XML码流中则只有一个，故只取数组中的第一个 */
    pstNodeBadSatList = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_GPS_RT_INTEGRITY);
    if (VOS_NULL_PTR == pstNodeBadSatList)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsRealTimeIntegrity: WARNING:Create MTA_AGPS_LABEL_GPS_RT_INTEGRITY fail!");
        return VOS_NULL_PTR;
    }

    /* 设置节点值 */
    ulReturnValue = XML_COMM_SetNodeValueUInt(pstNodeBadSatList,
                                              (VOS_UINT32)pstBadSatList->ausBadSatListBadSatList[0],
                                              pstXmlCommCtx);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertGpsRealTimeIntegrity: WARNING: Set MTA_AGPS_LABEL_GPS_RT_INTEGRITY value fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeBadSatList;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertMeasureReq
功能描述  : 将AGPS_MEASURE_REQ_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstMeasureReq 待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMeasureReq(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_MEASURE_REQ_STRU              *pstMeasureReq
)
{
    XML_COMM_NODE_STRU                 *pstNodeMeasureReq;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    /*
    <!ELEMENT pos_meas (meas_abort|RRLP_meas|RRC_meas)>
        <!ELEMENT meas_abort EMPTY>
        <!ELEMENT RRLP_meas (RRLP_pos_instruct)>
        <!ELEMENT RRC_meas (rep_quant,rep_crit)>
    */
    /* 调用XML API提供的接口，创建<pos_meas> 节点并设置标签 */
    pstNodeMeasureReq = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_POS_MEAS);
    if (VOS_NULL_PTR == pstNodeMeasureReq)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMeasureReq: WARNING:Create MTA_AGPS_LABEL_POS_MEAS fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    switch (pstMeasureReq->enActionTypeChoice)
    {
        case AGPS_POSITION_ACTION_TYPE_ABORT:
            /* 创建一个空节点并设置标签 */
            pstChildNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MEAS_ABORT);
            break;

        case AGPS_POSITION_ACTION_TYPE_RRLP_MEAS:
            pstChildNode = TAF_MTA_AGPS_ConvertRrlpMeasReq(pstXmlCommCtx, &pstMeasureReq->u.stRrlpMeasReq);
            break;

        case AGPS_POSITION_ACTION_TYPE_RRC_MEAS:
            pstChildNode = TAF_MTA_AGPS_ConvertRrcMeasReq(pstXmlCommCtx, &pstMeasureReq->u.stRrcMeasReq);
            break;

        default:
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertMeasureReq: WARNING; enActionType is abnormal!",
                             pstMeasureReq->enActionTypeChoice);
            return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAChildNode(pstNodeMeasureReq, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMeasureReq: WARNING; Add stRrcMeasReq child fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeMeasureReq;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrlpMeasReq
功能描述  : 将AGPS_RRLP_MEAS_REQ_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstRrlpMeasReq 待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpMeasReq(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_MEAS_REQ_STRU            *pstRrlpMeasReq
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrlpMeasReq;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
    <!ELEMENT RRLP_meas (RRLP_pos_instruct)>
          <!ELEMENT RRLP_pos_instruct (RRLP_method_type,RRLP_method,resp_time_seconds,mult_sets)>
             <!ELEMENT RRLP_method_type (ms_assisted|ms_assisted_no_accuracy|ms_based|ms_based_pref|ms_assisted_pref)>
                <!ELEMENT ms_assisted (method_accuracy)>
                   <!ELEMENT method_accuracy (#PCDATA)>
                <!ELEMENT ms_assisted_no_accuracy EMPTY>
                <!ELEMENT ms_based (method_accuracy)>
                <!ELEMENT ms_based_pref (method_accuracy)>
                <!ELEMENT ms_assisted_pref (method_accuracy)>
             <!ELEMENT RRLP_method EMPTY>
             <!ATTLIST RRLP_method literal (gps) #REQUIRED>
             <!ELEMENT resp_time_seconds (#PCDATA)>
             <!ELEMENT mult_sets EMPTY>
             <!ATTLIST mult_sets literal (multiple|one) #REQUIRED>
    */

    /* 调用XML API提供的接口，创建<RRLP_meas> 节点并设置标签 */
    pstNodeRrlpMeasReq = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_RRLP_MEAS);
    if (VOS_NULL_PTR == pstNodeRrlpMeasReq)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMeasReq: WARNING:Create MTA_AGPS_LABEL_RRLP_MEAS fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<RRLP_pos_instruct>子结构并挂到当前节点下 */
    pstChildNode  = TAF_MTA_AGPS_ConvertPositionInstruct(pstXmlCommCtx, &pstRrlpMeasReq->stPosInstruct);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRrlpMeasReq, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMeasReq: WARNING: Add stPosInstruct child fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrlpMeasReq;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct
功能描述  : 构造RRLP_method节点
输入参数  : pstXmlCommCtx           XML上下文
            pstNodePositionInstruct 父节点
输出参数  : 无
返 回 值  : VOS_OK  转换成功
            VOS_ERR 转换失败
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月13日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodePositionInstruct
)
{
    XML_COMM_NODE_STRU                 *pstRrlpMethodNode;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 创建节点，并设置标签 */
    pstRrlpMethodNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_RRLP_METHOD);
    if (VOS_NULL_PTR == pstRrlpMethodNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct: WARNING: Create MTA_AGPS_LABEL_RRLP_METHOD fail!");
        return VOS_ERR;
    }

    /* 创建属性节点 */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_ERR;
    }

    /* 设置属性值 */
    ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_GPS);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct: WARNING: set MTA_AGPS_ATTRIB_VALUE_GPS fail!");
        return VOS_ERR;
    }

    /* 将属性增加至该节点 */
    ulReturnValue = XML_COMM_AddAnAttribute(pstRrlpMethodNode, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct: WARNING: Add MTA_AGPS_ATTRIB_VALUE_GPS fail!");
        return VOS_ERR;
    }

    /* 增加该子节点至父节点上 */
    ulReturnValue = XML_COMM_AddAChildNode(pstNodePositionInstruct, pstRrlpMethodNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct: WARNING: Add RRLP_method child fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct
功能描述  : 构造mult_sets节点
输入参数  : pstXmlCommCtx           XML上下文
            pstNodePositionInstruct 父节点
            enUseMultipleSets       Mult sets的值
输出参数  : 无
返 回 值  : VOS_OK  转换成功
            VOS_ERR 转换失败
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月13日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodePositionInstruct,
    AGPS_MULT_SETS_ENUM_UINT8           enUseMultipleSets
)
{
    XML_COMM_NODE_STRU                 *pstMultSetsNode;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
    <!ELEMENT RRLP_pos_instruct (RRLP_method_type,RRLP_method,resp_time_seconds,mult_sets)>
         <!ELEMENT RRLP_method_type (ms_assisted|ms_assisted_no_accuracy|ms_based|ms_based_pref|ms_assisted_pref)>
            <!ELEMENT ms_assisted (method_accuracy)>
               <!ELEMENT method_accuracy (#PCDATA)>
            <!ELEMENT ms_assisted_no_accuracy EMPTY>
            <!ELEMENT ms_based (method_accuracy)>
            <!ELEMENT ms_based_pref (method_accuracy)>
            <!ELEMENT ms_assisted_pref (method_accuracy)>
         <!ELEMENT RRLP_method EMPTY>
         <!ATTLIST RRLP_method literal (gps) #REQUIRED>
         <!ELEMENT resp_time_seconds (#PCDATA)>
         <!ELEMENT mult_sets EMPTY>
         <!ATTLIST mult_sets literal (multiple|one) #REQUIRED>
    */

    /*创建节< mult_sets > 点并设置标签 */
    pstMultSetsNode  = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MULT_SETS);
    if (VOS_NULL_PTR == pstMultSetsNode)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct: WARNING: Create MTA_AGPS_LABEL_MULT_SETS fail!");
        return VOS_ERR;
    }

    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_ERR;
    }

    switch (enUseMultipleSets)
    {
        case AGPS_MULT_SETS_MULTIPLE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_MULTIPLE);
            if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct: WARNING: set MTA_AGPS_ATTRIB_VALUE_MULTIPLE fail!");
                return VOS_ERR;
            }
            break;
        case AGPS_MULT_SETS_ONE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_ONE);
            if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct: WARNING: set MTA_AGPS_ATTRIB_VALUE_ONE fail!");
                return VOS_ERR;
            }
            break;
        default:
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct: WARNING: enUseMultipleSets is invalid!", enUseMultipleSets);
            return VOS_ERR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstMultSetsNode, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct: WARNING: Add mult_sets attribute fail!");
        return VOS_ERR;
    }

    ulReturnValue = XML_COMM_AddAChildNode(pstNodePositionInstruct, pstMultSetsNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct: WARNING: Add RRLP_method child fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertPositionInstruct
功能描述  : 将AGPS_POSITION_INSTRUCT_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstPositionInstruct 待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertPositionInstruct(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_POSITION_INSTRUCT_STRU        *pstPositionInstruct
)
{
    XML_COMM_NODE_STRU                 *pstNodePositionInstruct;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
        <!ELEMENT RRLP_pos_instruct (RRLP_method_type,RRLP_method,resp_time_seconds,mult_sets)>
                 <!ELEMENT RRLP_method_type (ms_assisted|ms_assisted_no_accuracy|ms_based|ms_based_pref|ms_assisted_pref)>
                    <!ELEMENT ms_assisted (method_accuracy)>
                       <!ELEMENT method_accuracy (#PCDATA)>
                    <!ELEMENT ms_assisted_no_accuracy EMPTY>
                    <!ELEMENT ms_based (method_accuracy)>
                    <!ELEMENT ms_based_pref (method_accuracy)>
                    <!ELEMENT ms_assisted_pref (method_accuracy)>
                 <!ELEMENT RRLP_method EMPTY>
                 <!ATTLIST RRLP_method literal (gps) #REQUIRED>
                 <!ELEMENT resp_time_seconds (#PCDATA)>
                 <!ELEMENT mult_sets EMPTY>
                 <!ATTLIST mult_sets literal (multiple|one) #REQUIRED>
    */

    /* 调用XML API提供的接口，创建<RRLP_pos_instruct> 节点，并设置标签 */
    pstNodePositionInstruct = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_RRLP_POS_INSTRUCT);
    if (VOS_NULL_PTR == pstNodePositionInstruct)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPositionInstruct: WARNING:Create MTA_AGPS_LABEL_RRLP_POS_INSTRUCT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<RRLP_method_type>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertRrlpMethodType(pstXmlCommCtx, &pstPositionInstruct->stRrlpMethodType);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodePositionInstruct, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPositionInstruct: WARNING: Add stRrlpMethodType child fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<RRLP_method>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_ConvertRrlpMethodOfPositionInstruct(pstXmlCommCtx, pstNodePositionInstruct))
    {
        return VOS_NULL_PTR;
    }

    /* 转换<resp_time_seconds>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                        pstNodePositionInstruct,
                                                        MTA_AGPS_LABEL_RESP_TIME_SECONDS,
                                                        (VOS_UINT32)pstPositionInstruct->ucMeasureRspTime))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPositionInstruct: WARNING: Create MTA_AGPS_LABEL_RESP_TIME_SECONDS node fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<mult_sets>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_ConvertMultSetsOfPositionInstruct(pstXmlCommCtx,
                                                                 pstNodePositionInstruct,
                                                                 pstPositionInstruct->enUseMultipleSets))
    {
        return VOS_NULL_PTR;
    }

    return pstNodePositionInstruct;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrlpMethodType
功能描述  : 将AGPS_RRLP_METHOD_TYPE_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstRrlpMethodType 待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrlpMethodType(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRLP_METHOD_TYPE_STRU         *pstRrlpMethodType
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrlpMethodType;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
         <!ELEMENT RRLP_method_type (ms_assisted|ms_assisted_no_accuracy|ms_based|ms_based_pref|ms_assisted_pref)>
            <!ELEMENT ms_assisted (method_accuracy)>
               <!ELEMENT method_accuracy (#PCDATA)>
            <!ELEMENT ms_assisted_no_accuracy EMPTY>
            <!ELEMENT ms_based (method_accuracy)>
            <!ELEMENT ms_based_pref (method_accuracy)>
            <!ELEMENT ms_assisted_pref (method_accuracy)>
    */

    /* 调用XML API提供的接口，创建<d> 节点，并设置标签 */
    pstNodeRrlpMethodType = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_RRLP_METHOD_TYPE);
    if (VOS_NULL_PTR == pstNodeRrlpMethodType)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMethodType: WARNING:Create MTA_AGPS_LABEL_RRLP_METHOD_TYPE fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    switch (pstRrlpMethodType->enRrlpMethodType)
    {
        case AGPS_RRLP_METHOD_TYPE_UE_ASSISTED:
            pstChildNode = TAF_MTA_AGPS_ConvertMsAssisted(pstXmlCommCtx, &pstRrlpMethodType->ucAccuracy);
            break;

        case AGPS_RRLP_METHOD_TYPE_UE_ASSISTED_NO_ACCURACY:
            /* <!ELEMENT ms_assisted_no_accuracy EMPTY> */
            /*创建子节点并设置标签 */
            pstChildNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MS_ASSISTED_NO_ACCURACY);
            break;

        case AGPS_RRLP_METHOD_TYPE_UE_BASED:
            pstChildNode = TAF_MTA_AGPS_ConvertMsBased(pstXmlCommCtx, &pstRrlpMethodType->ucAccuracy);
            break;

        case AGPS_RRLP_METHOD_TYPE_UE_ASSISTED_PREFER:
            pstChildNode = TAF_MTA_AGPS_ConvertMsBasedPref(pstXmlCommCtx, &pstRrlpMethodType->ucAccuracy);
            break;

        case AGPS_RRLP_METHOD_TYPE_UE_BASED_PREFER:
            pstChildNode = TAF_MTA_AGPS_ConvertMsAssistedPref(pstXmlCommCtx, &pstRrlpMethodType->ucAccuracy);
            break;

        default:
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertRrlpMethodType: WARNING: enRrlpMethodType is abnormal!",
                             pstRrlpMethodType->enRrlpMethodType);
            return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRrlpMethodType, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrlpMethodType: WARNING: TAF_MTA_AGPS_ConvertMsAssistedPref fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrlpMethodType;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertMsAssisted
功能描述  : 将pucAccuracy转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pucAccuracy    待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsAssisted(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy
)
{
    XML_COMM_NODE_STRU                 *pstNodeMsAssisted;

    /*
        <!ELEMENT ms_assisted (method_accuracy)>
           <!ELEMENT method_accuracy (#PCDATA)>
    */

    /* 调用XML API提供的接口，创建<ms_assisted> 节点，并设置标签 */
    pstNodeMsAssisted = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MS_ASSISTED);
    if (VOS_NULL_PTR == pstNodeMsAssisted)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsAssisted: WARNING:Create MTA_AGPS_LABEL_MS_ASSISTED fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<method_accuracy>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                        pstNodeMsAssisted,
                                                        MTA_AGPS_LABEL_METHOD_ACCURACY,
                                                        (VOS_UINT32)(*pucAccuracy)))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsAssisted: WARNING: Create MTA_AGPS_LABEL_METHOD_ACCURACY node fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeMsAssisted;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertMsBased
功能描述  : 将pucAccuracy转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pucAccuracy    待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsBased(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy
)
{
    XML_COMM_NODE_STRU                 *pstNodeMsBased;

    /* <!ELEMENT ms_based (method_accuracy)> */

    /* 调用XML API提供的接口，创建<ms_based> 节点，并设置标签 */
    pstNodeMsBased = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MS_BASED);
    if (VOS_NULL_PTR == pstNodeMsBased)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsBased: WARNING:Create MTA_AGPS_LABEL_MS_BASED fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<method_accuracy>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                        pstNodeMsBased,
                                                        MTA_AGPS_LABEL_METHOD_ACCURACY,
                                                        (VOS_UINT32)(*pucAccuracy)))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsBased: WARNING: Create MTA_AGPS_LABEL_METHOD_ACCURACY node fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeMsBased;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertMsBasedPref
功能描述  : 将pucAccuracy转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pucAccuracy    待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsBasedPref(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy
)
{
    XML_COMM_NODE_STRU                 *pstNodeMsBasedPref;

    /* <!ELEMENT ms_based_pref (method_accuracy)> */

    /* 调用XML API提供的接口，创建<ms_based_pref> 节点，并设置标签 */
    pstNodeMsBasedPref = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MS_BASED_PREF);
    if (VOS_NULL_PTR == pstNodeMsBasedPref)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsBasedPref: WARNING:Create MTA_AGPS_LABEL_MS_BASED_PREF fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<method_accuracy>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                        pstNodeMsBasedPref,
                                                        MTA_AGPS_LABEL_METHOD_ACCURACY,
                                                        (VOS_UINT32)(*pucAccuracy)))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsBasedPref: WARNING: Create MTA_AGPS_LABEL_METHOD_ACCURACY node fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeMsBasedPref;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertMsAssistedPref
功能描述  : 将pucAccuracy转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pucAccuracy    待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMsAssistedPref(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    VOS_UINT8                          *pucAccuracy
)
{
    XML_COMM_NODE_STRU                 *pstNodeMsAssistedPref;

    /* <!ELEMENT ms_assisted_pref (method_accuracy)> */

    /* 调用XML API提供的接口，创建<ms_based_pref> 节点，并设置标签 */
    pstNodeMsAssistedPref = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MS_ASSISTED_PREF);
    if (VOS_NULL_PTR == pstNodeMsAssistedPref)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsAssistedPref: WARNING:Create MTA_AGPS_LABEL_MS_ASSISTED_PREF fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<method_accuracy>子结构并挂到当前节点下 */
    if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                        pstNodeMsAssistedPref,
                                                        MTA_AGPS_LABEL_METHOD_ACCURACY,
                                                        (VOS_UINT32)(*pucAccuracy)))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMsAssistedPref: WARNING: Create MTA_AGPS_LABEL_METHOD_ACCURACY node fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeMsAssistedPref;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrcMeasReq
功能描述  : 将AGPS_RRC_MEAS_REQ_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstRrcMeaseReq 待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcMeasReq(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_RRC_MEAS_REQ_STRU             *pstRrcMeaseReq
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrcMeaseReq;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
     <!ELEMENT RRC_meas (rep_quant,rep_crit)>
         <!ELEMENT rep_quant (RRC_method_type,RRC_method,hor_acc?,vert_acc?)>
         <!ATTLIST rep_quant
         gps_timing_of_cell_wanted (true|false) "false"
         addl_assist_data_req      (true|false) #REQUIRED>
            <!ELEMENT RRC_method_type EMPTY>
            <!ATTLIST RRC_method_type literal (ue_assisted|ue_based|ue_based_pref|ue_assisted_pref) #REQUIRED>
            <!ELEMENT RRC_method EMPTY>
            <!ATTLIST RRC_method literal (otdoa|gps|otdoaOrGPS|cellID) #REQUIRED>
            <!ELEMENT hor_acc (#PCDATA)>
            <!ELEMENT vert_acc (#PCDATA)>
         <!ELEMENT rep_crit (no_rep|event_rep_crit|period_rep_crit)>
            <!ELEMENT no_rep EMPTY>
            <!ELEMENT event_rep_crit (event_par*)>
               <!ELEMENT event_par (rep_amount,meas_interval,event_specific_info?) >
               <!ATTLIST event_par report_first_fix (true|false) #REQUIRED>
                  <!ELEMENT rep_amount EMPTY>
                  <!ATTLIST rep_amount literal (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) #REQUIRED>
                  <!ELEMENT meas_interval EMPTY>
                  <!ATTLIST meas_interval literal (e5|e15|e60|e300|e900|e1800|e3600|e7200) #REQUIRED>
                  <!ELEMENT event_specific_info (tr_pos_chg|tr_SFN_SFN_chg|tr_SFN_GPS_TOW)>
                     <!ELEMENT tr_pos_chg EMPTY>
                     <!ATTLIST tr_pos_chg literal (pc10|pc20|pc30|pc40|pc50|pc100|pc200|pc300|pc500|pc1000|pc2000|pc5000|pc10000|pc20000|pc50000|pc100000) #REQUIRED>
                     <!ELEMENT tr_SFN_SFN_chg EMPTY>
                     <!ATTLIST tr_SFN_SFN_chg literal (c0-25|c0-5|c1|c2|c3|c4|c5|c10|c20|c50|c100|c200|c500|c1000|c2000|c5000) #REQUIRED>
                     <!ELEMENT tr_SFN_GPS_TOW EMPTY>
                     <!ATTLIST tr_SFN_GPS_TOW literal (ms1|ms2|ms3|ms5|ms10|ms20|ms50|ms100)  #REQUIRED>
            <!ELEMENT period_rep_crit EMPTY>
            <!ATTLIST period_rep_crit rep_amount (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) "ra-Infinity">
            <!ATTLIST period_rep_crit rep_interval_long (ril0|ril0-25|ril0-5|ril1|ril2|ril3|ril4|ril6|ril8|ril12|ril16|ril20|ril24|ril28|ril32|ril64) #REQUIRED>
     */

    /* 调用XML API提供的接口，创建<RRLP_meas> 节点，并设置标签 */
    pstNodeRrcMeaseReq = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_RRC_MEAS);
    if (VOS_NULL_PTR == pstNodeRrcMeaseReq)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMeasReq: WARNING:Create MTA_AGPS_LABEL_RRC_MEAS fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<rep_quant>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertRepQuant(pstXmlCommCtx, &pstRrcMeaseReq->stRepQuant);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRrcMeaseReq, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMeasReq: WARNING: Add rep_quant child fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<rep_crit>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertRepCrit(pstXmlCommCtx, &pstRrcMeaseReq->stRepCrit);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRrcMeaseReq, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMeasReq: WARNING: Add rep_crit child fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrcMeaseReq;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_AddRepQuantAttribs
功能描述  : 将AGPS_RRC_EPHEM_CLOCK_PARAM_STRU结构体属性转换为树的属性节点
输入参数  : pstXmlCommCtx               XML上下文
            pstNodeRepQuant             属性转换后挂载的父节点
            pstRepQuant                 待转换属性结构体
输出参数  : 无
返 回 值  : VOS_ERR     转换失败
            VOS_OK      转换成功
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : l00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_AGPS_AddRepQuantAttribs(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    XML_COMM_NODE_STRU                 *pstNodeRepQuant,
    AGPS_REP_QUANT_STRU                *pstRepQuant
)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 增加属性<gps_timing_of_cell_wanted (true|false) "false"> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_GPS_TIMING_OF_CELL_WANTED);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRepQuantAttribs: WARNING: Create MTA_AGPS_ATTRIB_GPS_TIMING_OF_CELL_WANTED fail!");
        return VOS_ERR;
    }

    switch (pstRepQuant->enGpsTimOfCellWant)
    {
        case PS_FALSE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_FALSE);
            break;

        case PS_TRUE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_TRUE);
            break;

        default:
            /* 若无效，则赋值为false */
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_FALSE);
            break;
    }
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRepQuantAttribs: WARNING: set MTA_AGPS_ATTRIB_GPS_TIMING_OF_CELL_WANTED value fail!");
        return VOS_ERR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeRepQuant, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRepQuantAttribs: WARNING: Add MTA_AGPS_ATTRIB_GPS_TIMING_OF_CELL_WANTED fail!");
        return VOS_ERR;
    }

    /* 增加属性<addl_assist_data_req      (true|false) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_ADDL_ASSIST_DATA_REQ);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRepQuantAttribs: WARNING: Create MTA_AGPS_ATTRIB_ADDL_ASSIST_DATA_REQ fail!");
        return VOS_ERR;
    }

    switch (pstRepQuant->enAddAssistDataReq)
    {
        case PS_FALSE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_FALSE);
            break;
        case PS_TRUE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_TRUE);
            break;
        default:
            /* 由于该属性为#REQUIRED，值异常则直接退出 */
            return VOS_ERR;
    }
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRepQuantAttribs: WARNING: set MTA_AGPS_ATTRIB_ADDL_ASSIST_DATA_REQ value fail!");
        return VOS_ERR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeRepQuant, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_AddRepQuantAttribs: WARNING: Add MTA_AGPS_ATTRIB_ADDL_ASSIST_DATA_REQ fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRepQuant
功能描述  : 将AGPS_REP_QUANT_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstRepQuant    待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRepQuant(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_REP_QUANT_STRU                *pstRepQuant
)
{
    XML_COMM_NODE_STRU                 *pstNodeRepQuant;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
        <!ELEMENT rep_quant (RRC_method_type,RRC_method,hor_acc?,vert_acc?)>
                 <!ATTLIST rep_quant
                 gps_timing_of_cell_wanted (true|false) "false"
                 addl_assist_data_req      (true|false) #REQUIRED>
                    <!ELEMENT RRC_method_type EMPTY>
                    <!ATTLIST RRC_method_type literal (ue_assisted|ue_based|ue_based_pref|ue_assisted_pref) #REQUIRED>
                    <!ELEMENT RRC_method EMPTY>
                    <!ATTLIST RRC_method literal (otdoa|gps|otdoaOrGPS|cellID) #REQUIRED>
                    <!ELEMENT hor_acc (#PCDATA)>
                    <!ELEMENT vert_acc (#PCDATA)>
    */

    /* 调用XML API提供的接口，创建<rep_quant> 节点，并设置标签 */
    pstNodeRepQuant = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_REP_QUANT);
    if (VOS_NULL_PTR == pstNodeRepQuant)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepQuant: WARNING:Create MTA_AGPS_LABEL_REP_QUANT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<rep_quant>节点的属性值 */
    if (VOS_OK != TAF_MTA_AGPS_AddRepQuantAttribs(pstXmlCommCtx,
                                                  pstNodeRepQuant,
                                                  pstRepQuant))
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepQuant: WARNING: Add Attributes fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<RRC_method_type>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertRrcMethodType(pstXmlCommCtx, &pstRepQuant->enMethodType);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRepQuant, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepQuant: WARNING: Add RRC_method_type child fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<RRC_method>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertRrcMethod(pstXmlCommCtx, &pstRepQuant->enPosMethod);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRepQuant, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepQuant: WARNING: Add RRC_method child fail!");
        return VOS_NULL_PTR;
    }

    /* 挂接<hor_acc>子节点 */
    if (pstRepQuant->bitOpHoriAccur)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeRepQuant,
                                                             MTA_AGPS_LABEL_HOR_ACC,
                                                             (VOS_UINT32)pstRepQuant->ucHoriAccur))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepQuant: WARNING: Create MTA_AGPS_LABEL_HOR_ACC fail!");
            return VOS_NULL_PTR;
        }
    }

    /* 挂接<vert_acc>子节点 */
    if (pstRepQuant->bitOpVerticalAccur)
    {
        if (VOS_OK != TAF_MTA_AGPS_AddNewUnsignedIntLeafNode(pstXmlCommCtx,
                                                             pstNodeRepQuant,
                                                             MTA_AGPS_LABEL_VERT_ACC,
                                                             (VOS_UINT32)pstRepQuant->ucVerticalAccur))
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepQuant: WARNING: Create MTA_AGPS_LABEL_VERT_ACC fail!");
            return VOS_NULL_PTR;
        }
    }

    return pstNodeRepQuant;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrcMethodType
功能描述  : 将penMethodType转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            penMethodType   待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcMethodType(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_POSITION_TYPE_ENUM_UINT8      *penMethodType
)
{
    XML_COMM_NODE_STRU                 *pstRrcMethodType;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
        <!ELEMENT RRC_method_type EMPTY>
        <!ATTLIST RRC_method_type literal (ue_assisted|ue_based|ue_based_pref|ue_assisted_pref) #REQUIRED>
    */

    /* 创建<RRC_method_type>子节点 */
    pstRrcMethodType = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_RRC_METHOD_TYPE);
    if (VOS_NULL_PTR == pstRrcMethodType)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethodType: WARNING: Create MTA_AGPS_LABEL_RRC_METHOD_TYPE fail!");
        return VOS_NULL_PTR;
    }

    /*增加属性<!ATTLIST RRC_method_type literal (ue_assisted|ue_based|ue_based_pref|ue_assisted_pref) #REQUIRED>*/
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethodType: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    switch (*penMethodType)
    {
        case AGPS_UE_POS_METHOD_TYPE_UE_ASSIST:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_UE_ASSISTED);
            break;
        case AGPS_UE_POS_METHOD_TYPE_UE_BASED:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_UE_BASED);
            break;
        case AGPS_UE_POS_METHOD_TYPE_UE_BASED_PREF:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_UE_BASED_PREF);
            break;
        case AGPS_UE_POS_METHOD_TYPE_UE_ASSIST_PREF:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_UE_ASSISTED_PREF);
            break;
        default:
            /* RRC_method_type是#REQUIRED类型的，值异常则退出 */
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertRrcMethodType: WARNING: MethodType is abnormal!", *penMethodType);
            return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethodType: WARNING: set RRC_method_type attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstRrcMethodType, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethodType: WARNING: Add attribute for RRC_method_type fail!");
        return VOS_NULL_PTR;
    }

    return pstRrcMethodType;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRrcMethod
功能描述  : 将penMethodType转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            penMethodType   待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRrcMethod(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_POS_METHOD_ENUM_UINT8         *penPosMethod
)
{
    XML_COMM_NODE_STRU                 *pstNodeRrcMethod;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
        <!ELEMENT RRC_method EMPTY>
        <!ATTLIST RRC_method literal (otdoa|gps|otdoaOrGPS|cellID) #REQUIRED>
    */

    /* 创建<RRC_method> 节点，并设置标签 */
    pstNodeRrcMethod = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_RRC_METHOD);
    if (VOS_NULL_PTR == pstNodeRrcMethod)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethod: WARNING: Create MTA_AGPS_LABEL_RRC_METHOD fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST RRC_method literal (otdoa|gps|otdoaOrGPS|cellID) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethod: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    switch (*penPosMethod)
    {
        case AGPS_POS_METHOD_OTDOA:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_OTDOA);
            break;
        case AGPS_POS_METHOD_GPS:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_GPS);
            break;
        case AGPS_POS_METHOD_OTDOA_OR_GPS:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_OTDOAORGPS);
            break;
        case AGPS_POS_METHOD_CELL_ID:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_CELLID);
            break;
        default:
            /* RRC_method是#REQUIRED类型的，值异常则退出 */
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertRrcMethod: WARNING: MethodType is abnormal!", *penPosMethod);
            return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethod: WARNING: set RRC_method attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeRrcMethod, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRrcMethod: WARNING: Add attribute for RRC_method fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRrcMethod;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRepCrit
功能描述  : 将AGPS_REP_CRIT_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstRepCrit     待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRepCrit(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_REP_CRIT_STRU                 *pstRepCrit
)
{
    XML_COMM_NODE_STRU                 *pstNodeRepCrit;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /*
        <!ELEMENT rep_crit (no_rep|event_rep_crit|period_rep_crit)>
                    <!ELEMENT no_rep EMPTY>
                    <!ELEMENT event_rep_crit (event_par*)>
                       <!ELEMENT event_par (rep_amount,meas_interval,event_specific_info?) >
                       <!ATTLIST event_par report_first_fix (true|false) #REQUIRED>
                          <!ELEMENT rep_amount EMPTY>
                          <!ATTLIST rep_amount literal (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) #REQUIRED>
                          <!ELEMENT meas_interval EMPTY>
                          <!ATTLIST meas_interval literal (e5|e15|e60|e300|e900|e1800|e3600|e7200) #REQUIRED>
                          <!ELEMENT event_specific_info (tr_pos_chg|tr_SFN_SFN_chg|tr_SFN_GPS_TOW)>
                             <!ELEMENT tr_pos_chg EMPTY>
                             <!ATTLIST tr_pos_chg literal (pc10|pc20|pc30|pc40|pc50|pc100|pc200|pc300|pc500|pc1000|pc2000|pc5000|pc10000|pc20000|pc50000|pc100000) #REQUIRED>
                             <!ELEMENT tr_SFN_SFN_chg EMPTY>
                             <!ATTLIST tr_SFN_SFN_chg literal (c0-25|c0-5|c1|c2|c3|c4|c5|c10|c20|c50|c100|c200|c500|c1000|c2000|c5000) #REQUIRED>
                             <!ELEMENT tr_SFN_GPS_TOW EMPTY>
                             <!ATTLIST tr_SFN_GPS_TOW literal (ms1|ms2|ms3|ms5|ms10|ms20|ms50|ms100)  #REQUIRED>
                    <!ELEMENT period_rep_crit EMPTY>
                    <!ATTLIST period_rep_crit rep_amount (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) "ra-Infinity">
                    <!ATTLIST period_rep_crit rep_interval_long (ril0|ril0-25|ril0-5|ril1|ril2|ril3|ril4|ril6|ril8|ril12|ril16|ril20|ril24|ril28|ril32|ril64) #REQUIRED>
    */

    /* 调用XML API提供的接口，创建<rep_crit>节点，并设置标签 */
    pstNodeRepCrit = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_REP_CRIT);
    if (VOS_NULL_PTR == pstNodeRepCrit)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepCrit: WARNING:Create MTA_AGPS_LABEL_REP_CRIT fail!");
        return VOS_NULL_PTR;
    }

    /* 转换子结构并挂到当前节点下 */
    switch (pstRepCrit->enChoice)
    {
        case AGPS_REP_CRIT_TYPE_NO_REP:
            /*创建子节点并设置标签 */
            pstChildNode = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MS_ASSISTED_NO_ACCURACY);
            if (VOS_NULL_PTR == pstChildNode)
            {
                MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepCrit: WARNING: create MTA_AGPS_LABEL_NO_REP fail!");
                return VOS_NULL_PTR;
            }
            break;

        case AGPS_REP_CRIT_TYPE_POS_EVT_REP:
            pstChildNode = TAF_MTA_AGPS_ConvertEventRepCrit(pstXmlCommCtx,
                                                            &pstRepCrit->u.stUePosRptngCrtr);
            break;

        case AGPS_REP_CRIT_TYPE_PERIOD_REP:
            pstChildNode = TAF_MTA_AGPS_ConvertPeriodRepCrit(pstXmlCommCtx,
                                                             &pstRepCrit->u.stPeriodRptngCrtr);
            break;

        default:
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertRepCrit: WARNING; enChoice is abnormal!",
                             pstRepCrit->enChoice);
            return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAChildNode(pstNodeRepCrit, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepCrit: WARNING; Add period_rep_crit child fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRepCrit;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEventRepCrit
功能描述  : 将AGPS_UE_POS_EVT_PARAM_LIST_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx            XML上下文
            pstUePosEvtParamList     待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEventRepCrit(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_EVT_PARAM_LIST_STRU    *pstUePosEvtParamList
)
{
    XML_COMM_NODE_STRU                 *pstNodeUePosEvtParamList;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_UINT32                          ulLoop;

    /*
        <!ELEMENT event_rep_crit (event_par*)>
                       <!ELEMENT event_par (rep_amount,meas_interval,event_specific_info?) >
                       <!ATTLIST event_par report_first_fix (true|false) #REQUIRED>
                          <!ELEMENT rep_amount EMPTY>
                          <!ATTLIST rep_amount literal (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) #REQUIRED>
                          <!ELEMENT meas_interval EMPTY>
                          <!ATTLIST meas_interval literal (e5|e15|e60|e300|e900|e1800|e3600|e7200) #REQUIRED>
                          <!ELEMENT event_specific_info (tr_pos_chg|tr_SFN_SFN_chg|tr_SFN_GPS_TOW)>
                             <!ELEMENT tr_pos_chg EMPTY>
                             <!ATTLIST tr_pos_chg literal (pc10|pc20|pc30|pc40|pc50|pc100|pc200|pc300|pc500|pc1000|pc2000|pc5000|pc10000|pc20000|pc50000|pc100000) #REQUIRED>
                             <!ELEMENT tr_SFN_SFN_chg EMPTY>
                             <!ATTLIST tr_SFN_SFN_chg literal (c0-25|c0-5|c1|c2|c3|c4|c5|c10|c20|c50|c100|c200|c500|c1000|c2000|c5000) #REQUIRED>
                             <!ELEMENT tr_SFN_GPS_TOW EMPTY>
                             <!ATTLIST tr_SFN_GPS_TOW literal (ms1|ms2|ms3|ms5|ms10|ms20|ms50|ms100)  #REQUIRED>
    */

    /* 调用XML API提供的接口，创建<event_rep_crit> 节点并设置标签*/
    pstNodeUePosEvtParamList = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_EVENT_REP_CRIT);
    if (VOS_NULL_PTR == pstNodeUePosEvtParamList)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventRepCrit: WARNING:Create MTA_AGPS_LABEL_EVENT_REP_CRIT fail!");
        return VOS_NULL_PTR;
    }

    /* meas_event 数量应该小于等于 AGPS_MAX_MEAS_EVENT  */
    if (AGPS_MAX_MEAS_EVENT < pstUePosEvtParamList->ulCnt)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventRepCrit: WARNING: MEAS_EVENT count fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<event_par>子结构并挂到当前节点下 */
    for (ulLoop = 0; ulLoop < pstUePosEvtParamList->ulCnt; ulLoop++)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertEventPar(pstXmlCommCtx,
                                                    &pstUePosEvtParamList->astUePosEvtParam[ulLoop]);

        ulReturnValue = XML_COMM_AddAChildNode(pstNodeUePosEvtParamList, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertEventRepCrit: WARNING: Add event_par child fail!", ulLoop);
            return VOS_NULL_PTR;
        }
    }

    return pstNodeUePosEvtParamList;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEventPar
功能描述  : 将AGPS_UE_POS_EVT_PARAM_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx        XML上下文
            pstUePosEvtParam     待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEventPar(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_EVT_PARAM_STRU         *pstUePosEvtParam
)
{
    XML_COMM_NODE_STRU                 *pstNodeUePosEvtParam;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 调用XML API提供的接口，创建<event_par> 节点，并设置标签 */
    pstNodeUePosEvtParam = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_EVENT_PAR);
    if (VOS_NULL_PTR == pstNodeUePosEvtParam)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING:Create MTA_AGPS_LABEL_EVENT_PAR fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST event_par report_first_fix (true|false) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_REPORT_FIRST_FIX);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING: Create MTA_AGPS_ATTRIB_REPORT_FIRST_FIX fail!");
        return VOS_NULL_PTR;
    }

    switch (pstUePosEvtParam->enRptFirstFix)
    {
        case PS_FALSE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_FALSE);
            break;
        case PS_TRUE:
            ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_TRUE);
            break;
        default:
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING: enRptFirstFix is abnormal!",
                             pstUePosEvtParam->enRptFirstFix);
            return VOS_NULL_PTR;
    }
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING: set MTA_AGPS_ATTRIB_VALUE_GPS fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeUePosEvtParam, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING: Add attribute for rep_amount fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<rep_amount>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertRepAmount(pstXmlCommCtx,
                                                 &pstUePosEvtParam->enReportAmount);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeUePosEvtParam, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING: Add rep_amount child fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<meas_interval>子结构并挂到当前节点下 */
    pstChildNode = TAF_MTA_AGPS_ConvertMeasInterval(pstXmlCommCtx,
                                                    &pstUePosEvtParam->enMeasInterval);
    ulReturnValue = XML_COMM_AddAChildNode(pstNodeUePosEvtParam, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING: Add meas_interval child fail!");
        return VOS_NULL_PTR;
    }

    /* 转换<event_specific_info>子结构并挂到当前节点下 */
    if (VOS_TRUE == pstUePosEvtParam->bitOpEvtSpecInfo)
    {
        pstChildNode = TAF_MTA_AGPS_ConvertEventSpecificInfo(pstXmlCommCtx,
                                                             &pstUePosEvtParam->stEvtSpecInfo);
        ulReturnValue = XML_COMM_AddAChildNode(pstNodeUePosEvtParam, pstChildNode, VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
        {
            MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventPar: WARNING: Add event_specific_info child fail!");
            return VOS_NULL_PTR;
        }
    }

    return pstNodeUePosEvtParam;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertRepAmount
功能描述  : 将penReportAmount转换为树结构
输入参数  : pstXmlCommCtx     XML上下文
            penReportAmount   待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertRepAmount(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_RPT_MOUNT_ENUM_UINT8   *penReportAmount
)
{
    XML_COMM_NODE_STRU                 *pstNodeRepAmount;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_CHAR                           *aucRepAmountmap[] = {MTA_AGPS_ATTRIB_VALUE_RA1,
                                                             MTA_AGPS_ATTRIB_VALUE_RA2,
                                                             MTA_AGPS_ATTRIB_VALUE_RA4,
                                                             MTA_AGPS_ATTRIB_VALUE_RA8,
                                                             MTA_AGPS_ATTRIB_VALUE_RA16,
                                                             MTA_AGPS_ATTRIB_VALUE_RA32,
                                                             MTA_AGPS_ATTRIB_VALUE_RA64,
                                                             MTA_AGPS_ATTRIB_VALUE_RA_INFINITY};

    /* 创建<rep_amount> 节点，并设置标签 */
    pstNodeRepAmount = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_REP_AMOUNT);
    if (VOS_NULL_PTR == pstNodeRepAmount)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepAmount: WARNING: Create MTA_AGPS_LABEL_REP_AMOUNT fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST rep_amount literal (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepAmount: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    if (AGPS_UE_POS_RPT_MOUNT_BUTT > *penReportAmount)
    {
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, aucRepAmountmap[*penReportAmount]);
    }
    else
    {
        /* rep_amount的属性是#REQUIRED类型的，值异常则退出 */
        MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertRepAmount: WARNING: penReportAmount is abnormal!",
                         *penReportAmount);
        return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepAmount: WARNING: set rep_amount attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeRepAmount, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertRepAmount: WARNING: Add attribute for rep_amount fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeRepAmount;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertMeasInterval
功能描述  : 将penMeasInterval转换为树结构
输入参数  : pstXmlCommCtx     XML上下文
            penMeasInterval   待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertMeasInterval(
    XML_COMM_CTX_STRU                      *pstXmlCommCtx,
    AGPS_UE_POS_EVT_INTERVAL_ENUM_UINT8    *penMeasInterval
)
{
    XML_COMM_NODE_STRU                 *pstNodeMeasInterval;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_CHAR                           *aucRepAmountmap[] = {MTA_AGPS_ATTRIB_VALUE_E5,
                                                             MTA_AGPS_ATTRIB_VALUE_E15,
                                                             MTA_AGPS_ATTRIB_VALUE_E60,
                                                             MTA_AGPS_ATTRIB_VALUE_E300,
                                                             MTA_AGPS_ATTRIB_VALUE_E900,
                                                             MTA_AGPS_ATTRIB_VALUE_E1800,
                                                             MTA_AGPS_ATTRIB_VALUE_E3600,
                                                             MTA_AGPS_ATTRIB_VALUE_E7200};

    /* 创建<meas_interval> 节点，并设置标签 */
    pstNodeMeasInterval = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_MEAS_INTERVAL);
    if (VOS_NULL_PTR == pstNodeMeasInterval)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMeasInterval: WARNING: Create MTA_AGPS_LABEL_MEAS_INTERVAL fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST meas_interval literal (e5|e15|e60|e300|e900|e1800|e3600|e7200) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMeasInterval: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    if (AGPS_UE_POS_EVT_INTERVAL_BUTT > *penMeasInterval)
    {
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, aucRepAmountmap[*penMeasInterval]);
    }
    else
    {
        /* meas_interval的属性是#REQUIRED类型的，值异常则退出 */
        MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertMeasInterval: WARNING: penMeasInterval is abnormal!",
                         *penMeasInterval);
        return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMeasInterval: WARNING: set meas_interval attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeMeasInterval, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertMeasInterval: WARNING: Add attribute for meas_interval fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeMeasInterval;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertEventSpecificInfo
功能描述  : 将AGPS_UE_POS_EVT_SPEC_INFO_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx        XML上下文
            pstUePosEvtSpecInfo  待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertEventSpecificInfo(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_UE_POS_EVT_SPEC_INFO_STRU     *pstUePosEvtSpecInfo
)
{
    XML_COMM_NODE_STRU                 *pstNodeUePosEvtSpecInfo;
    XML_COMM_NODE_STRU                 *pstChildNode;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;

    /* 创建<event_specific_info> 节点，并设置标签 */
    pstNodeUePosEvtSpecInfo = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx, MTA_AGPS_LABEL_EVENT_SPECIFIC_INFO);
    if (VOS_NULL_PTR == pstNodeUePosEvtSpecInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventSpecificInfo: WARNING: Create MTA_AGPS_LABEL_EVENT_SPECIFIC_INFO fail!");
        return VOS_NULL_PTR;
    }

    switch (pstUePosEvtSpecInfo->enChoice)
    {
        case AGPS_UE_POS_EVT_7A:
            pstChildNode = TAF_MTA_AGPS_ConvertTrPosChg(pstXmlCommCtx, &pstUePosEvtSpecInfo->u.enE7a);
            break;

        case AGPS_UE_POS_EVT_7B:
            pstChildNode = TAF_MTA_AGPS_ConvertTrSfnSfnChg(pstXmlCommCtx, &pstUePosEvtSpecInfo->u.enE7b);
            break;

        case AGPS_UE_POS_EVT_7C:
            pstChildNode = TAF_MTA_AGPS_ConvertTrSfnGpsTow(pstXmlCommCtx, &pstUePosEvtSpecInfo->u.enE7c);
            break;

        default:
            MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertEventSpecificInfo: WARNING: enChoice is abnormal!",
                             pstUePosEvtSpecInfo->enChoice);
            return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAChildNode(pstNodeUePosEvtSpecInfo, pstChildNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertEventSpecificInfo: WARNING: Add enE7a child fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeUePosEvtSpecInfo;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertTrPosChg
功能描述  : 将penE7a转换为树结构
输入参数  : pstXmlCommCtx     XML上下文
            penE7a            待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertTrPosChg(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_THRESHOLD_POSITION_ENUM_UINT8 *penE7a
)
{
    XML_COMM_NODE_STRU                 *pstNodeTrPosChg;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_CHAR                           *aucPosChgmap[] = {MTA_AGPS_ATTRIB_VALUE_PC10,
                                                          MTA_AGPS_ATTRIB_VALUE_PC20,
                                                          MTA_AGPS_ATTRIB_VALUE_PC30,
                                                          MTA_AGPS_ATTRIB_VALUE_PC40,
                                                          MTA_AGPS_ATTRIB_VALUE_PC50,
                                                          MTA_AGPS_ATTRIB_VALUE_PC100,
                                                          MTA_AGPS_ATTRIB_VALUE_PC200,
                                                          MTA_AGPS_ATTRIB_VALUE_PC300,
                                                          MTA_AGPS_ATTRIB_VALUE_PC500,
                                                          MTA_AGPS_ATTRIB_VALUE_PC1000,
                                                          MTA_AGPS_ATTRIB_VALUE_PC2000,
                                                          MTA_AGPS_ATTRIB_VALUE_PC5000,
                                                          MTA_AGPS_ATTRIB_VALUE_PC10000,
                                                          MTA_AGPS_ATTRIB_VALUE_PC20000,
                                                          MTA_AGPS_ATTRIB_VALUE_PC50000,
                                                          MTA_AGPS_ATTRIB_VALUE_PC100000};

    /* 创建<tr_pos_chg> 节点，并设置标签 */
    pstNodeTrPosChg = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                          MTA_AGPS_LABEL_TR_POS_CHG);
    if (VOS_NULL_PTR == pstNodeTrPosChg)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrPosChg: WARNING: Create MTA_AGPS_LABEL_TR_POS_CHG fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST tr_pos_chg literal (pc10|pc20|pc30|pc40|pc50|
       pc100|pc200|pc300|pc500|pc1000|pc2000|pc5000|pc10000|pc20000|pc50000|pc100000) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrPosChg: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    if (AGPS_THRESHOLD_POSITION_BUTT > *penE7a)
    {
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, aucPosChgmap[*penE7a]);
    }
    else
    {
        /* tr_pos_chg的属性是#REQUIRED类型的，值异常则退出 */
        MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertTrPosChg: WARNING: penE7a is abnormal!", *penE7a);
        return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrPosChg: WARNING: set tr_pos_chg attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeTrPosChg, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrPosChg: WARNING: Add attribute for tr_pos_chg fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeTrPosChg;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertTrSfnSfnChg
功能描述  : 将penE7b转换为树结构
输入参数  : pstXmlCommCtx     XML上下文
            penE7b            待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertTrSfnSfnChg(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_THRESHOLD_SFN_SFN_ENUM_UINT8  *penE7b
)
{
    XML_COMM_NODE_STRU                 *pstNodeTrSfnSfnChg;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_CHAR                           *aucSfnSfnChgMap[] = {MTA_AGPS_ATTRIB_VALUE_C0_25,
                                                             MTA_AGPS_ATTRIB_VALUE_C0_5,
                                                             MTA_AGPS_ATTRIB_VALUE_C1,
                                                             MTA_AGPS_ATTRIB_VALUE_C2,
                                                             MTA_AGPS_ATTRIB_VALUE_C3,
                                                             MTA_AGPS_ATTRIB_VALUE_C4,
                                                             MTA_AGPS_ATTRIB_VALUE_C5,
                                                             MTA_AGPS_ATTRIB_VALUE_C10,
                                                             MTA_AGPS_ATTRIB_VALUE_C20,
                                                             MTA_AGPS_ATTRIB_VALUE_C50,
                                                             MTA_AGPS_ATTRIB_VALUE_C100,
                                                             MTA_AGPS_ATTRIB_VALUE_C200,
                                                             MTA_AGPS_ATTRIB_VALUE_C500,
                                                             MTA_AGPS_ATTRIB_VALUE_C1000,
                                                             MTA_AGPS_ATTRIB_VALUE_C2000,
                                                             MTA_AGPS_ATTRIB_VALUE_C5000};

    /* 创建<tr_SFN_SFN_chg> 节点，并设置标签 */
    pstNodeTrSfnSfnChg = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                             MTA_AGPS_LABEL_TR_SFN_SFN_CHG);
    if (VOS_NULL_PTR == pstNodeTrSfnSfnChg)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnSfnChg: WARNING: Create MTA_AGPS_LABEL_TR_SFN_SFN_CHG fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST tr_SFN_SFN_chg literal (c0-25|c0-5|c1|c2|c3|c4|c5|c10|c20|c50|c100|c200|c500|c1000|c2000|c5000) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnSfnChg: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    if (AGPS_THRESHOLD_SFN_SFN_BUTT > *penE7b)
    {
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, aucSfnSfnChgMap[*penE7b]);
    }
    else
    {
        /* tr_SFN_SFN_chg的属性是#REQUIRED类型的，值异常则退出 */
        MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertTrSfnSfnChg: WARNING: penE7b is abnormal!", *penE7b);
        return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnSfnChg: WARNING: set tr_SFN_SFN_chg attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeTrSfnSfnChg, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnSfnChg: WARNING: Add attribute for tr_SFN_SFN_chg fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeTrSfnSfnChg;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertTrSfnGpsTow
功能描述  : 将penE7c转换为树结构
输入参数  : pstXmlCommCtx     XML上下文
            penE7c            待转换数据
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertTrSfnGpsTow(
    XML_COMM_CTX_STRU                      *pstXmlCommCtx,
    AGPS_THRESHOLD_SFN_GPS_TOW_ENUM_UINT8  *penE7c
)
{
    XML_COMM_NODE_STRU                 *pstNodeTrSfnGpsTow;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_CHAR                           *aucTrSfnGpsTowMap[] = {MTA_AGPS_ATTRIB_VALUE_MS1,
                                                               MTA_AGPS_ATTRIB_VALUE_MS2,
                                                               MTA_AGPS_ATTRIB_VALUE_MS3,
                                                               MTA_AGPS_ATTRIB_VALUE_MS5,
                                                               MTA_AGPS_ATTRIB_VALUE_MS10,
                                                               MTA_AGPS_ATTRIB_VALUE_MS20,
                                                               MTA_AGPS_ATTRIB_VALUE_MS50,
                                                               MTA_AGPS_ATTRIB_VALUE_MS100};

    /* 创建<tr_SFN_GPS_TOW> 节点，并设置标签 */
    pstNodeTrSfnGpsTow = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                             MTA_AGPS_LABEL_TR_SFN_GPS_TOW);
    if (VOS_NULL_PTR == pstNodeTrSfnGpsTow)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnGpsTow: WARNING: Create MTA_AGPS_LABEL_TR_SFN_GPS_TOW fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST tr_SFN_GPS_TOW literal (ms1|ms2|ms3|ms5|ms10|ms20|ms50|ms100)  #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_LITERAL);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnGpsTow: WARNING: Create MTA_AGPS_ATTRIB_LITERAL fail!");
        return VOS_NULL_PTR;
    }

    if (AGPS_THRESHOLD_SFN_GPS_TOW_BUTT > *penE7c)
    {
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, aucTrSfnGpsTowMap[*penE7c]);
    }
    else
    {
        /* tr_SFN_GPS_TOW的属性是#REQUIRED类型的，值异常则退出 */
        MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertTrSfnGpsTow: WARNING: penE7c is abnormal!", *penE7c);
        return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnGpsTow: WARNING: set tr_SFN_GPS_TOW attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodeTrSfnGpsTow, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertTrSfnGpsTow: WARNING: Add attribute for tr_SFN_GPS_TOW fail!");
        return VOS_NULL_PTR;
    }

    return pstNodeTrSfnGpsTow;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertPeriodRepCrit
功能描述  : 将AGPS_PERIOD_RPTNG_CRTR_STRU结构体转换为树结构
输入参数  : pstXmlCommCtx        XML上下文
            pstPeriodRptngCrtr   待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年07月07日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertPeriodRepCrit(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx,
    AGPS_PERIOD_RPTNG_CRTR_STRU        *pstPeriodRptngCrtr
)
{
    XML_COMM_NODE_STRU                 *pstNodePeriodRptngCrtr;
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNodeAttribute;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnValue;
    VOS_CHAR                           *aucRepMountMap[]        = {MTA_AGPS_ATTRIB_VALUE_RA1,
                                                                   MTA_AGPS_ATTRIB_VALUE_RA2,
                                                                   MTA_AGPS_ATTRIB_VALUE_RA4,
                                                                   MTA_AGPS_ATTRIB_VALUE_RA8,
                                                                   MTA_AGPS_ATTRIB_VALUE_RA16,
                                                                   MTA_AGPS_ATTRIB_VALUE_RA32,
                                                                   MTA_AGPS_ATTRIB_VALUE_RA64,
                                                                   MTA_AGPS_ATTRIB_VALUE_RA_INFINITY};

    VOS_CHAR                           *aucRepIntervalLongMap[] = {MTA_AGPS_ATTRIB_VALUE_RIL0,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL0_25,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL0_5,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL1,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL2,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL3,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL4,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL6,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL8,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL12,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL16,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL20,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL24,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL28,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL32,
                                                                   MTA_AGPS_ATTRIB_VALUE_RIL64};

    /*
        <!ELEMENT period_rep_crit EMPTY>
                    <!ATTLIST period_rep_crit rep_amount (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) "ra-Infinity">
                    <!ATTLIST period_rep_crit rep_interval_long (ril0|ril0-25|ril0-5|ril1|ril2|ril3|ril4|ril6|ril8|ril12|ril16|ril20|ril24|ril28|ril32|ril64) #REQUIRED>
    */

    /* 创建<period_rep_crit> 节点，并设置标签 */
    pstNodePeriodRptngCrtr = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                                 MTA_AGPS_LABEL_PERIOD_REP_CRIT);
    if (VOS_NULL_PTR == pstNodePeriodRptngCrtr)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: Create MTA_AGPS_LABEL_PERIOD_REP_CRIT fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST period_rep_crit rep_amount (ra1|ra2|ra4|ra8|ra16|ra32|ra64|ra-Infinity) "ra-Infinity"> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_REP_AMOUNT);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: Create MTA_AGPS_ATTRIB_REP_AMOUNT fail!");
        return VOS_NULL_PTR;
    }

    if (AGPS_UE_POS_RPT_MOUNT_BUTT > pstPeriodRptngCrtr->enRptngAmount)
    {
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute,
                                                   aucRepMountMap[pstPeriodRptngCrtr->enRptngAmount]);
    }
    else
    {
        /* rep_amount的默认属性是"ra-Infinity" */
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute, MTA_AGPS_ATTRIB_VALUE_RA_INFINITY);
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: set rep_amount attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodePeriodRptngCrtr, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: Add rep_amount attribute fail!");
        return VOS_NULL_PTR;
    }

    /* 增加属性<!ATTLIST period_rep_crit rep_interval_long (ril0|ril0-25|ril0-5|
       ril1|ril2|ril3|ril4|ril6|ril8|ril12|ril16|ril20|ril24|ril28|ril32|ril64) #REQUIRED> */
    pstNodeAttribute = XML_COMM_CreateAnAttribute(pstXmlCommCtx);
    ulReturnValue = XML_COMM_SetAttributeName(pstNodeAttribute, MTA_AGPS_ATTRIB_REP_INTERVAL_LONG);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: Create MTA_AGPS_ATTRIB_REP_INTERVAL_LONG fail!");
        return VOS_NULL_PTR;
    }

    if (AGPS_UE_POS_PERI_INTERVAL_BUTT > pstPeriodRptngCrtr->enMeasInterval)
    {
        ulReturnValue = XML_COMM_SetAttributeValue(pstNodeAttribute,
                                                   aucRepIntervalLongMap[pstPeriodRptngCrtr->enMeasInterval]);
    }
    else
    {
        /* rep_interval_long的属性是#REQUIRED类型的，值异常则退出 */
        MTA_WARNING1_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: enMeasInterval is abnormal!",
                         pstPeriodRptngCrtr->enMeasInterval);
        return VOS_NULL_PTR;
    }

    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: set rep_interval_long attribute fail!");
        return VOS_NULL_PTR;
    }

    ulReturnValue = XML_COMM_AddAnAttribute(pstNodePeriodRptngCrtr, pstNodeAttribute, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulReturnValue)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPeriodRepCrit: WARNING: Add rep_interval_long attribute fail!");
        return VOS_NULL_PTR;
    }

    return pstNodePeriodRptngCrtr;
}

/*****************************************************************************
函 数 名  : TAF_MTA_AGPS_ConvertPos
功能描述  : 将pos结构体转换为树结构
输入参数  : pstXmlCommCtx   XML上下文
            pstMeasureReq 待转换结构体
输出参数  : 无
返 回 值  : VOS_NULL_PTR    转换失败
            成功返回转换后的树根节点
调用函数  :
被调函数  :

修改历史
1.日    期   : 2012年06月27日
  作    者   : y00213812
  修改内容   : V7R1C50 A-GPS项目新增函数
*****************************************************************************/
XML_COMM_NODE_STRU* TAF_MTA_AGPS_ConvertPos(
    XML_COMM_CTX_STRU                  *pstXmlCommCtx
)
{
    XML_COMM_NODE_STRU                 *pstNodePos;

    /* 调用XML API提供的接口，创建 节点，并设置标签 */
    pstNodePos = TAF_MTA_AGPS_CreateANodeAndSetLabel(pstXmlCommCtx,
                                                     MTA_AGPS_LABEL_POS);
    if (VOS_NULL_PTR == pstNodePos)
    {
        MTA_WARNING_LOG("TAF_MTA_AGPS_ConvertPos: WARNING:Create MTA_AGPS_LABEL_POS fail!");
        return VOS_NULL_PTR;
    }

    return pstNodePos;
}



#endif /* FEATURE_AGPS */

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
       }
    #endif
#endif

