/******************************************************************************

版权所有 (C), 2001-2012, 华为技术有限公司

******************************************************************************
文 件 名      : XmlComm.c
版 本 号      : 初稿
作    者      : 李紫剑 00198894
生成日期      : 2012年6月16日
最近修改      :
功能描述      : 该头文件为XML相关操作c文件, 目前仅提供给MEA模块使用
函数列表      :
修改历史      :
1.日    期    : 2012年6月16日
  作    者    : 李紫剑 00198894
  修改内容    : 创建文件

******************************************************************************/

/*****************************************************************************
1 头文件包含
*****************************************************************************/

#include "Taf_Common.h"
#include "XmlComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*lint -e958*/

#if (FEATURE_ON == FEATRUE_XML_PARSER)

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_XML_COMM_C

/*****************************************************************************
2 全局变量定义
*****************************************************************************/
typedef VOS_UINT32 (*XML_COMM_ANALYSE_FUNC)(XML_COMM_CTX_INNER_STRU *pstXmlCtxInner);

/*****************************************************************************
3 函数定义
*****************************************************************************/

/*****************************************************************************
函 数 名  : XML_COMM_GetChildCount
功能描述  : 取得某节点子节点数量
输入参数  : pstNode 节点
输出参数  : 无
返 回 值  : VOS_ERROR 表示节点不存在, 其它值表示子节点数目
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_INT32 XML_COMM_GetChildCount(XML_COMM_NODE_STRU *pstNode)
{
    XML_COMM_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetChildCount: pstNode is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    lCounter = 0;

    /* 从长子链表头开始, 遍历所有子节点 */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        lCounter++;
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return lCounter;
}

/*****************************************************************************
函 数 名  : XML_COMM_GetChildNodeByIndex
功能描述  : 按照索引取得某节点子节点,索引从0开始
输入参数  : pstNode     节点
            iChildIndex 索引值,范围从0开始
输出参数  : 无
返 回 值  : 子节点指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* XML_COMM_GetChildNodeByIndex(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lChildIndex)
{
    XML_COMM_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetChildNodeByIndex: pstNode is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    lCounter = 0;

    /* 从长子链表头开始,遍历所有子节点 */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        if (lCounter == lChildIndex)
        {
            return pstTmpNode;
        }
        lCounter++;
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
函 数 名  : XML_COMM_GetChildNodeByLabel
功能描述  : 按照标签名字取得某节点子节点
输入参数  : pstNode 节点
            pcLabel 标签名字
输出参数  : 无
返 回 值  : 子节点指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* XML_COMM_GetChildNodeByLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabel)
{
    XML_COMM_NODE_STRU                 *pstTmpNode;
    VOS_UINT32                          ulLabelLength;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcLabel))
    {
        XML_WARNING_LOG("XML_COMM_GetChildNodeByLabel: pstNode or pcLabel is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* 从长子链表头开始,遍历所有子节点 */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        ulLabelLength   = pstTmpNode->ulLabelLength;
        if (VOS_StrLen(pcLabel) == ulLabelLength)
        {
            if (0 == PS_MEM_CMP(pstTmpNode->pcNodeLabel, pcLabel, ulLabelLength))
            {
                return pstTmpNode;
            }
        }
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
函 数 名  : XML_COMM_CheckLabelName
功能描述  : 检查节点标签名是否与目标值相同
输入参数  : pstNode     节点指针
            pcLabelName 节点标签名目标值, 带字符串结尾
输出参数  : 无
返 回 值  : VOS_TRUE    与目标值匹配
            VOS_FALSE   与目标值不匹配, 或其他异常
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 XML_COMM_CheckLabelName(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabelName)
{
    VOS_UINT32                          ulLabelLength;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcLabelName))
    {
        XML_WARNING_LOG("XML_COMM_CheckLabelName: pstNode or pcLabelName is VOS_NULL_PTR!");
        return VOS_FALSE;
    }

    /* 分别对比标签名长度及标签名的值 */
    ulLabelLength = VOS_StrLen(pcLabelName);
    if (ulLabelLength == pstNode->ulLabelLength)
    {
        if (0 == PS_MEM_CMP(pstNode->pcNodeLabel, pcLabelName, ulLabelLength))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : XML_COMM_GetAttributeCount
功能描述  : 取得某节点属性数量
输入参数  : pstNode 节点指针
输出参数  : 无
返 回 值  : 该节点属性数量, VOS_ERROR表示非法节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_INT32 XML_COMM_GetAttributeCount(XML_COMM_NODE_STRU *pstNode)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetAttributeCount: pstNode is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    lCounter = 0;

    /* 从长子链表头开始,遍历所有子节点 */
    pstTmpAttribute = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttribute)
    {
        lCounter++;
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return lCounter;
}

/*****************************************************************************
函 数 名  : XML_COMM_GetAttributeByIndex
功能描述  : 按照索引取得某节点属性值,索引从0开始
输入参数  : pstNode 节点指针
输出参数  : 无
返 回 值  : 属性指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetAttributeByIndex(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lAttribIndex)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_GetAttributeByIndex: pstNode is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    lCounter = 0;

    /* 从链表头开始,遍历所有子节点 */
    pstTmpAttribute = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttribute)
    {
        if (lCounter == lAttribIndex)
        {
            return pstTmpAttribute;
        }
        lCounter++;
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
函 数 名  : XML_COMM_GetAttributeByAttributeName
功能描述  : 按照属性名取得某节点属性
输入参数  : pstNode 节点指针
输出参数  : 无
返 回 值  : 属性指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetAttributeByAttributeName(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribName)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;
    VOS_UINT32                          ulNameLength;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcAttribName))
    {
        XML_WARNING_LOG("XML_COMM_GetAttributeByAttributeName: pstNode or pcAttribName is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* 从链表头开始,遍历所有属性 */
    pstTmpAttrib = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttrib)
    {
        ulNameLength = pstTmpAttrib->ulNameLength;
        if (VOS_StrLen(pcAttribName) == ulNameLength)
        {
            if (0 == PS_MEM_CMP(pstTmpAttrib->pcAttribName, pcAttribName, ulNameLength))
            {
                return pstTmpAttrib;
            }
        }
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    XML_WARNING_LOG("XML_COMM_GetAttributeByAttributeName: Can't find the Attribute!");
    return VOS_NULL_PTR;
}

/*****************************************************************************
函 数 名  : XML_COMM_GetLastAttribute
功能描述  : 内部函数, 获取节点最后一个属性
输入参数  : pstNode 节点指针
输出参数  : 无
返 回 值  : 属性指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_GetLastAttribute(
    XML_COMM_NODE_STRU                 *pstNode)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;

    pstTmpAttribute = pstNode->pstFirstAttrib;

    /* 节点无属性则直接返回空指针 */
    if (VOS_NULL_PTR == pstTmpAttribute)
    {
        return VOS_NULL_PTR;
    }

    /* 从链表头开始, 遍历所有子节点, 直到最后一个属性 */
    while (VOS_NULL_PTR != pstTmpAttribute->pstNexBrother)
    {
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return pstTmpAttribute;
}

/*****************************************************************************
函 数 名  : XML_COMM_BreakAnAttribute
功能描述  : 检查属性值是否与目标值相同
输入参数  : pstAttribute        属性指针
            pcAttributeValue    属性值目标值, 带字符串结尾
输出参数  : 无
返 回 值  : VOS_TRUE    与目标值匹配
            VOS_FALSE   与目标值不匹配, 或其他异常
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 XML_COMM_CheckAttributeValue(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttributeValue)
{
    VOS_UINT32                          ulValueLength;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstAttribute) || (VOS_NULL_PTR == pcAttributeValue))
    {
        XML_WARNING_LOG("XML_COMM_CheckAttributeValue: pstAttribute or pcAttributeValue is VOS_NULL_PTR!");
        return VOS_FALSE;
    }

    /* 分别对比属性值长度及属性值内容 */
    ulValueLength = VOS_StrLen(pcAttributeValue);
    if (ulValueLength == pstAttribute->ulValueLength)
    {
        if (0 == PS_MEM_CMP(pstAttribute->pcAttribValue, pcAttributeValue, ulValueLength))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : XML_COMM_BreakAnAttribute
功能描述  : 从节点上拆下一个属性
输入参数  : pstNode     指定要释放的属性在哪个节点上
            pstProperty 指定要释放的属性指针
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BreakAnAttribute(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstAttribute))
    {
        XML_WARNING_LOG("XML_COMM_BreakAnAttribute: pstNode or pstAttribute is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 遍历链表查找,定位到要拆掉的属性 */
    pstTmpAttrib = pstNode->pstFirstAttrib;
    while ((VOS_NULL_PTR != pstTmpAttrib) && (pstAttribute != pstTmpAttrib))
    {
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    /* 没找到指定的属性,失败返回 */
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FAILED_ATTRIB_NOT_FOUND;
    }

    /* 如果要拆卸的是节点第一个属性，则更换节点首属性指针 */
    if (pstTmpAttrib == pstNode->pstFirstAttrib)
    {
        pstNode->pstFirstAttrib = pstTmpAttrib->pstNexBrother;
    }

    /* 更新前后兄弟节点的指向 */
    if (VOS_NULL_PTR != pstTmpAttrib->pstPreBrother)
    {
        pstTmpAttrib->pstPreBrother->pstNexBrother = pstTmpAttrib->pstNexBrother;
    }
    if (VOS_NULL_PTR != pstTmpAttrib->pstNexBrother)
    {
        pstTmpAttrib->pstNexBrother->pstPreBrother = pstTmpAttrib->pstPreBrother;
    }

    /* 与原来的链断绝关系 */
    pstTmpAttrib->pstPreBrother = VOS_NULL_PTR;
    pstTmpAttrib->pstNexBrother = VOS_NULL_PTR;

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_BreakANode
功能描述  : 拆下一个树枝
输入参数  : pstNode 指定要处理的节点
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BreakANode(XML_COMM_NODE_STRU *pstNode)
{
    XML_COMM_NODE_STRU                 *pstFatherNode;
    XML_COMM_NODE_STRU                 *pstTmpNode;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("XML_COMM_BreakANode: pstNode is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 取得父节点 */
    pstFatherNode = pstNode->pstFather;

    /* 根节点不予拆除 */
    if (VOS_NULL_PTR == pstFatherNode)
    {
        return XML_COMM_RESULT_FAILED_CANT_UNLOAD_ROOT_NODE;
    }

    /* 遍历子节点链表查找，确认指定的父子关系 */
    pstTmpNode = pstFatherNode->pstFirstChild;
    while ((VOS_NULL_PTR != pstTmpNode) && (pstTmpNode != pstNode))
    {
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    /* 没有找到 */
    if (VOS_NULL_PTR == pstTmpNode)
    {
        return XML_COMM_RESULT_FAILED_NODE_NOT_FOUND;
    }

    /* 如果是父节点长子，则更换父节点长子 */
    if (pstNode == pstFatherNode->pstFirstChild)
    {
        pstFatherNode->pstFirstChild = pstNode->pstNexBrother;
    }

    /* 脱离父子关系 */
    pstNode->pstFather = VOS_NULL_PTR;

    /* 脱离兄弟链表 */
    if (VOS_NULL_PTR != pstNode->pstPreBrother)
    {
        pstNode->pstPreBrother->pstNexBrother = pstNode->pstNexBrother;
    }
    if (VOS_NULL_PTR != pstNode->pstNexBrother)
    {
        pstNode->pstNexBrother->pstPreBrother = pstNode->pstPreBrother;
    }
    pstNode->pstPreBrother = VOS_NULL_PTR;
    pstNode->pstNexBrother = VOS_NULL_PTR;

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_InitMemory
功能描述  : 内部函数, 初始化上下文中的内存
输入参数  : pstXmlCtx     XML API上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_InitMemory(XML_COMM_CTX_STRU *pstXmlCtx)
{
    /* 上下文中内存地址为空, 则分配内存并初始化 */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
    {
        pstXmlCtx->ulXMLBuffSize    = XML_COMM_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffer     = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, pstXmlCtx->ulXMLBuffSize);
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;

        /* 申请内存失败 */
        if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
        {
            XML_ERROR_LOG("XML_COMM_InitMemory: Malloc Failure!");
            return XML_COMM_RESULT_FALIED_MALLOC;
        }
    }
    /* 上下文已分配内存空间, 则只需初始化 */
    else
    {
        pstXmlCtx->ulXMLBuffSize    = XML_COMM_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;
    }

    PS_MEM_SET(pstXmlCtx->pucXMLBuffer, 0x00, pstXmlCtx->ulXMLBuffSize);

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_Malloc
功能描述  : 内部函数, 从内存中分配一片内存
输入参数  : pstXmlCommCtx   XML上下文
            ulSize          申请内存大小
输出参数  : 无
返 回 值  : VOS_VOID类型指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID* XML_COMM_Malloc(
    XML_COMM_CTX_STRU                  *pstXmlCtx,
    VOS_UINT32                          ulSize)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;
    VOS_INT32                           iRemainMemSize;
    VOS_VOID                           *pReturn;

    pReturn     = VOS_NULL_PTR;
    ulReturnVal = XML_COMM_RESULT_SUCCEED;

    /* 判断上下文中的当前内存指针是否可用, 不可用则调用初始化内存函数 */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffCur)
    {
        ulReturnVal = XML_COMM_InitMemory(pstXmlCtx);
    }

    if (XML_COMM_RESULT_SUCCEED == ulReturnVal)
    {
        /* 判断上下文中内存是否够用 */
        iRemainMemSize = (pstXmlCtx->pucXMLBuffer
                       + pstXmlCtx->ulXMLBuffSize)
                       - pstXmlCtx->pucXMLBuffCur;
        if ((VOS_INT32)ulSize > iRemainMemSize)
        {
            pReturn = VOS_NULL_PTR;
        }
        else
        {
            pReturn = (VOS_VOID*)pstXmlCtx->pucXMLBuffCur;
            pstXmlCtx->pucXMLBuffCur += ulSize;
        }
    }

    return pReturn;
}

/*****************************************************************************
函 数 名  : XML_COMM_CreateAnAttribute
功能描述  : 在内存中创建一个属性并初始化
输入参数  : pstXmlCtx   XML API上下文
输出参数  : 无
返 回 值  : 新XML_COMM_NODE_ATTRIBUTE_STRU结构的指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_ATTRIBUTE_STRU* XML_COMM_CreateAnAttribute(XML_COMM_CTX_STRU *pstXmlCtx)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute;
    VOS_UINT32                          ulAttribStruSize;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("XML_COMM_CreateAnAttribute: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstAttribute        = VOS_NULL_PTR;
    ulAttribStruSize    = sizeof(XML_COMM_NODE_ATTRIBUTE_STRU);

    /* 调用XML模块内存分配函数，申请一块节点内存 */
    pstAttribute = (XML_COMM_NODE_ATTRIBUTE_STRU*)XML_COMM_Malloc(pstXmlCtx, ulAttribStruSize);

    return pstAttribute;
}

/*****************************************************************************
函 数 名  : XML_COMM_SetAttributeName
功能描述  : 设置属性的属性名
输入参数  : pstAttribute        属性指针
            pcAttributeName     属性名, 带字符串结尾
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetAttributeName(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttribName)
{
    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstAttribute) || (VOS_NULL_PTR == pcAttribName))
    {
        XML_WARNING_LOG("XML_COMM_SetAttributeName: pstAttribute or pcAttribName is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 对属性结构进行赋值 */
    pstAttribute->pcAttribName = pcAttribName;
    pstAttribute->ulNameLength = VOS_StrLen(pcAttribName);

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_SetAttributeValue
功能描述  : 设置属性的属性值
输入参数  : pstAttribute        属性指针
            pcAttributeValue    属性值, 带字符串结尾
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetAttributeValue(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                           *pcAttribValue)
{
    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstAttribute) || (VOS_NULL_PTR == pcAttribValue))
    {
        XML_WARNING_LOG("XML_COMM_SetAttributeValue: pstAttribute or pcAttribValue is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 对属性结构进行赋值 */
    pstAttribute->pcAttribValue = pcAttribValue;
    pstAttribute->ulValueLength = VOS_StrLen(pcAttribValue);

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_CreateANode
功能描述  : 在内存中创建一个节点并初始化
输入参数  : pstXmlCtx   XML API上下文
输出参数  : 无
返 回 值  : 新XML_COMM_NODE结构的指针
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* XML_COMM_CreateANode(XML_COMM_CTX_STRU *pstXmlCtx)
{
    XML_COMM_NODE_STRU                 *pstNode;
    VOS_UINT32                          ulNodeStruSize;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("XML_COMM_CreateANode: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstNode         = VOS_NULL_PTR;
    ulNodeStruSize  = sizeof(XML_COMM_NODE_STRU);

    /* 调用XML模块内存分配函数，申请一块节点内存 */
    pstNode = (XML_COMM_NODE_STRU*)XML_COMM_Malloc(pstXmlCtx, ulNodeStruSize);

    return pstNode;
}

/*****************************************************************************
函 数 名  : XML_COMM_SetNodeLabel
功能描述  : 设置节点的标签名
输入参数  : pstNode     节点指针
            pcNodeLabel 标签名, 带字符串结尾
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcNodeLabel)
{
    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcNodeLabel))
    {
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 对节点结构进行赋值 */
    pstNode->pcNodeLabel        = pcNodeLabel;
    pstNode->pcNodeLabelEnd     = pcNodeLabel;
    pstNode->ulLabelLength      = VOS_StrLen(pcNodeLabel);
    pstNode->ulLabelEndLength   = VOS_StrLen(pcNodeLabel);

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_SetNodeValueStr
功能描述  : 设置节点的值, 字符串类型
输入参数  : pstNode     节点指针
            pcNodeValue 节点值, 带字符串结尾, 要求全局或静态变量
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueStr(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcNodeValue)
{
    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcNodeValue))
    {
        XML_WARNING_LOG("XML_COMM_SetNodeValueStr: pstNode or pcNodeValue is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 对节点结构进行赋值 */
    pstNode->pcNodeValue    = pcNodeValue;
    pstNode->ulValueLength  = VOS_StrLen(pcNodeValue);

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_SetNodeValueInt
功能描述  : 设置节点的值, 整数类型
输入参数  : pstNode     节点指针
            lNodeValue  节点值, 整数类型
            pstXmlCtx   XML API上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueInt(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_INT32                           lNodeValue,
    XML_COMM_CTX_STRU                  *pstXmlCtx)
{
    VOS_CHAR                            acTmpStr[XML_COMM_MAX_NUM_LEN + 1];

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("XML_COMM_SetNodeValueInt: pstNode or pstXmlCtx is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    PS_MEM_SET(acTmpStr, 0x00, XML_COMM_MAX_NUM_LEN + 1);

    /* 对节点结构进行赋值 */
    /* 将整型值转换为字符串并获取长度 */
    pstNode->ulValueLength  = (VOS_UINT32)VOS_sprintf(acTmpStr, "%d", lNodeValue);

    /* 申请值内存，并赋值 */
    pstNode->pcNodeValue    = (VOS_CHAR*)XML_COMM_Malloc(pstXmlCtx, pstNode->ulValueLength);
    if (VOS_NULL_PTR == pstNode->pcNodeValue)
    {
        XML_ERROR_LOG("XML_COMM_SetNodeValueInt: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MALLOC;
    }

    PS_MEM_CPY(pstNode->pcNodeValue, acTmpStr, pstNode->ulValueLength);

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_SetNodeValueUInt
功能描述  : 设置节点的值, 整数类型
输入参数  : pstNode     节点指针
            ulNodeValue 节点值, 整数类型
            pstXmlCtx   XML API上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_SetNodeValueUInt(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_UINT32                          ulNodeValue,
    XML_COMM_CTX_STRU                  *pstXmlCtx)
{
    VOS_CHAR                            acTmpStr[XML_COMM_MAX_NUM_LEN];

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("XML_COMM_SetNodeValueUInt: pstNode or pstXmlCtx is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    PS_MEM_SET(acTmpStr, 0x00, XML_COMM_MAX_NUM_LEN);

    /* 对节点结构进行赋值 */
    /* 将整型值转换为字符串并获取长度 */
    pstNode->ulValueLength  = (VOS_UINT32)VOS_sprintf(acTmpStr, "%u", ulNodeValue);

    /* 申请值内存，并赋值 */
    pstNode->pcNodeValue    = (VOS_CHAR*)XML_COMM_Malloc(pstXmlCtx, pstNode->ulValueLength);
    if (VOS_NULL_PTR == pstNode->pcNodeValue)
    {
        XML_ERROR_LOG("XML_COMM_SetNodeValueUInt: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MALLOC;
    }

    PS_MEM_CPY(pstNode->pcNodeValue, acTmpStr, pstNode->ulValueLength);

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_AddAChildNode
功能描述  : 为一个节点增加子节点，把一个节点或一棵树，
            挂到另一个树的某个节点下，放到第三个参数指定的节点之前
输入参数  : pstFather       指定为该节点增加子节点
            pstChild        子节点指针
            pstYoungBrother 增加的子节点添加到该子节点之前
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_AddAChildNode(
    XML_COMM_NODE_STRU                 *pstFather,
    XML_COMM_NODE_STRU                 *pstChild,
    XML_COMM_NODE_STRU                 *pstYoungBrother)
{
    XML_COMM_NODE_STRU                 *pstTmpChild;
    XML_COMM_NODE_STRU                 *pstLastChild;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstFather) || (VOS_NULL_PTR == pstChild))
    {
        XML_WARNING_LOG("XML_COMM_AddAChildNode: pstFather or pstChild is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 设定父亲 */
    pstChild->pstFather = pstFather;

    /* 设定孩子 */
    /* 如果该节点还没有孩子，则把插入的节点作为首节点 */
    if (VOS_NULL_PTR == pstFather->pstFirstChild)
    {
        pstFather->pstFirstChild    = pstChild;

        /* 重置添加的这个孩子的链表关系 */
        pstChild->pstPreBrother     = VOS_NULL_PTR;
        pstChild->pstNexBrother     = VOS_NULL_PTR;

        return XML_COMM_RESULT_SUCCEED;
    }

    /* 用临时变量pstTmpChild遍历子节点链表, 直到找到参数指定的子节点的弟弟 */
    pstTmpChild     = pstFather->pstFirstChild; /* 从长子开始 */
    pstLastChild    = VOS_NULL_PTR;
    while (VOS_NULL_PTR != pstTmpChild)
    {
        pstLastChild = pstTmpChild;
        if (pstTmpChild == pstYoungBrother)
        {
            break;
        }
        pstTmpChild = pstTmpChild->pstNexBrother;
    }

    /* 没有找到指定的弟弟（插入点） */
    if (VOS_NULL_PTR == pstTmpChild )
    {
        if ( (VOS_NULL_PTR != pstYoungBrother)
          || (VOS_NULL_PTR == pstLastChild) )
        {
            return XML_COMM_RESULT_FAILED_NODE_NOT_FOUND;
        }
        else
        {
            pstLastChild->pstNexBrother = pstChild;
            pstChild->pstPreBrother     = pstLastChild;
            pstChild->pstNexBrother     = VOS_NULL_PTR;
            return XML_COMM_RESULT_SUCCEED;
        }
    }

    if (pstFather->pstFirstChild == pstTmpChild)
    {
        /* 弟弟为原长子 */
        pstFather->pstFirstChild    = pstChild;
        pstChild ->pstPreBrother    = VOS_NULL_PTR;
        pstChild ->pstNexBrother    = pstTmpChild;
        pstTmpChild->pstPreBrother  = pstChild;
    }
    else
    {
        pstChild ->pstPreBrother    = pstTmpChild->pstPreBrother;
        pstChild ->pstNexBrother    = pstTmpChild;
        pstTmpChild->pstPreBrother  = pstChild;
        pstChild->pstPreBrother->pstNexBrother = pstChild;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_AddAProperty
功能描述  : 为一个节点增加属性
输入参数  : pstNode         指定为该节点增加属性
            pstProperty     属性指针
            pstYoungBrother 增加的属性添加到该属性之前
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_AddAnAttribute(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstYoungBrother)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstAttribute))
    {
        XML_WARNING_LOG("XML_COMM_AddAnAttribute: pstNode or pstAttribute is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 如果该节点还没有属性，或首个属性即为pstYoungBrother，则把插入的属性当做首个属性 */
    if ( (VOS_NULL_PTR == pstNode->pstFirstAttrib)
      || (pstYoungBrother == pstNode->pstFirstAttrib) )
    {
        /* 重置添加的这个属性的链表关系 */
        pstAttribute->pstPreBrother         = VOS_NULL_PTR;
        pstAttribute->pstNexBrother         = pstNode->pstFirstAttrib;
        if (VOS_NULL_PTR != pstYoungBrother)
        {
            pstYoungBrother->pstPreBrother  = pstAttribute;
        }

        pstNode->pstFirstAttrib             = pstAttribute;

        return XML_COMM_RESULT_SUCCEED;
    }

    /* 用临时变量pstAttribute遍历属性链表,直到找到参数指定的属性的前一个 */
    pstTmpAttrib = pstNode->pstFirstAttrib; /* 从第一个属性开始 */
    while ( (VOS_NULL_PTR != pstTmpAttrib)
         && (pstTmpAttrib->pstNexBrother != pstYoungBrother) )
    {
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    /* 没有找到指定的插入点 */
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FAILED_ATTRIB_NOT_FOUND;
    }

    /* 把pstAttribute插入pstTmpAttrib和pstYoungBrother之间 */
    pstTmpAttrib->pstNexBrother     = pstAttribute;
    pstAttribute->pstPreBrother     = pstTmpAttrib;
    pstAttribute->pstNexBrother     = pstYoungBrother;
    if (VOS_NULL_PTR != pstYoungBrother)
    {
        pstYoungBrother->pstPreBrother = pstAttribute;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_IsSeparator
功能描述  : 用于检查字符是否为XML文档中的分隔符
输入参数  : cCharacter  传入待检查的字符
输出参数  : 无
返 回 值  : VOS_TRUE    该字符为分隔符
            VOS_FALSE   该字符不为分隔符
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 XML_COMM_IsSeparator(VOS_CHAR cCharacter)
{
    if ( ('\r' == cCharacter)       /* 分隔符包括回车   */
      || ('\n' == cCharacter)       /* 分隔符包括换行   */
      || ('\t' == cCharacter)       /* 分隔符包括制表符 */
      || (' '  == cCharacter) )     /* 分隔符包括空格   */
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : XML_COMM_IsLetter
功能描述  : 内部函数，用于检查字符是否为英文字母
输入参数  : cCharacter  传入待检查的字符
输出参数  : 无
返 回 值  : VOS_TRUE    该字符为字母
            VOS_FALSE   该字符不为字母
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 XML_COMM_IsLetter(VOS_CHAR cCharacter)
{
    /* 判断字符是否在a~z之间 */
    if ( ('a' <= cCharacter)
      && ('z' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* 判断字符是否在A~Z之间 */
    else if ( ('A' <= cCharacter)
           && ('Z' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    else
    {
        if ('_' == cCharacter)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : XML_COMM_IsKeySymbol
功能描述  : 内部函数, 检查字符是否为关键符号
输入参数  : cCharacter  传入待检查的字符
输出参数  : 无
返 回 值  : VOS_TRUE    该字符为标点符号
            VOS_FALSE   该字符不为标点符号
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 XML_COMM_IsKeySymbol(VOS_CHAR cCharacter)
{
    /* XML标准约束的关键符号包括": . - _" */
    if ( (':' == cCharacter)
      || ('.' == cCharacter)
      || ('-' == cCharacter)
      || ('_' == cCharacter) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : XML_COMM_IsPunctuation
功能描述  : 内部函数，用于检查字符是否为标点符号
输入参数  : cCharacter  传入待检查的字符
输出参数  : 无
返 回 值  : VOS_TRUE    该字符为标点符号
            VOS_FALSE   该字符不为标点符号
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 XML_COMM_IsPunctuation(VOS_CHAR cCharacter)
{
    /* 根据ASCII码表, 首先判断是否为以下标点符号
       (空格) ! " # $ % & ' ( ) * + , - . / */
    if ( (' ' <= cCharacter)
      && ('/' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* 判断是否为以下标点符号 : ; < = > @ */
    else if ( (':' <= cCharacter)
           && ('@' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* 判断是否为以下标点符号 [ \ ] ^ _ ` */
    else if ( ('[' <= cCharacter)
           && ('`' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* 判断是否为以下标点符号 { | } ~ */
    else if ( ('{' <= cCharacter)
           && ('~' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    else
    {
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlOriginal
功能描述  : 内部函数，状态机处理函数，初始状态的处理函数
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlOriginal(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 遇到<则更改状态 */
    if ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ENTER_LABEL;
    }
    /* 当前节点指针为空, 认为没有进入节点, 忽略该字符 */
    else if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode)
    {
        /* 此时如果没有根节点，且字符不能忽略需要返回异常 */
        if ( (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
          && (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode) )
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlOriginal: Unexpect charactor out of Root!");
            return XML_COMM_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
        }
    }
    /* 当前节点的值不为空, 则认为该节点无子节点, 当前字符属于节点值 */
    else if (VOS_NULL_PTR != pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue)
    {
        /* 当前节点的值长度+1 */
        pstXmlCtxInner->pstXMLCurrentNode->ulValueLength++;
    }
    else
    {
    }

    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlEnterLabel
功能描述  : 内部函数，状态机处理函数，进入Label后的处理
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlEnterLabel(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 遇到首行版本信息 */
    if ('?' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_DECLARATION;
    }
    /* 遇到注释 */
    else if ('!' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_COMMENT;
    }
    /* 遇到尾节点标签 */
    else if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_SINGLE_ENDS_LABEL;
    }
    /* 进入一个新节点 */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_NODE_LABEL_START;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlDeclaration
功能描述  : 内部函数，状态机处理函数，XML声明处理函数
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlDeclaration(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 将指针移到"<?"后 */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* 目前无解析版本信息的需求，暂不作处理, 直到遇到"?>"结束 */
    while ('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        /*lint -e961*/
        if ( ('?' == *(pstXmlCtxInner->pcXMLStrCurChar++))
          && ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return XML_COMM_RESULT_SUCCEED;
        }
        /*lint +e961*/
    }

    XML_WARNING_LOG("XML_COMM_ProcXmlDeclaration: The declaration has no end!");
    return XML_COMM_RESULT_FALIED_DECLARATION_NO_END;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlComment
功能描述  : 内部函数，状态机处理函数，注释的处理函数
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlComment(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 将指针移到"<!"后 */
    pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint -e961*/
    /* 不支持DOCTYPE, 注释必须以"<!--"开头, 否则语法错误 */
    if ( ('-' == *(pstXmlCtxInner->pcXMLStrCurChar++))
      && ('-' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
    {
        pstXmlCtxInner->pcXMLStrCurChar++;

        /* 直到遇到结束符"-->"前, 忽略所有的字符 */
        while (0 != *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            if ( ('-' == *(pstXmlCtxInner->pcXMLStrCurChar++))
              && ('-' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
            {
                pstXmlCtxInner->pcXMLStrCurChar++;
                if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar++))
                {
                    pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
                    return XML_COMM_RESULT_SUCCEED;
                }
                else
                {
                    XML_WARNING_LOG("XML_COMM_ProcXmlComment: The comment has syntax error!");
                    return XML_COMM_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
                }
            }
        }

        XML_WARNING_LOG("XML_COMM_ProcXmlComment: The comment has no end!");
        return XML_COMM_RESULT_FALIED_COMMENT_NO_END;
    }
    /*lint +e961*/
    XML_WARNING_LOG("XML_COMM_ProcXmlComment: The comment has syntax error!");
    return XML_COMM_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlSingleEndLabel
功能描述  : 内部函数，状态机处理函数，进入独立的结尾标签的处理
输入参数  : pstXmlCtxXML    上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlSingleEndLabel(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 将指针移到"</"后 */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* 标签名首字母不能为数字或标点符号 */
    /* 不支持双字节编码字符, 不支持命名空间, 点属性操作符等 */
    if (VOS_TRUE != XML_COMM_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlSingleEndLabel: Illegal label name!");
        return XML_COMM_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* 给节点右标签名赋值 */
    /*lint -e961*/
    pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd = pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint +e961*/
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == XML_COMM_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == XML_COMM_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength++;
    }

    /* 比较右标签名是否和左标签名一样 */
    if (pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength == pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength)
    {
        if (0 != PS_MEM_CMP(pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabel,
                            pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd,
                            pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength))
        {
            return XML_COMM_RESULT_FALIED_LABEL_NAMES_NOT_SAME;
        }
    }
    else
    {
        return XML_COMM_RESULT_FALIED_BAD_END_LABEL;
    }

    /* 右标签名与标签结束符之间仅允许分隔符 */
    /* 一直到遇见>结束整个结尾标签 */
    while (0 != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode->pstFather)
            {
                /* 根节点的结尾标签, 表明根节点解析结束了 */
                pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_AFTER_ROOT_NODE;
                pstXmlCtxInner->pcXMLStrCurChar++;
                return XML_COMM_RESULT_SUCCEED_ALL_ENDS;
            }
            break;
        }
        else if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlSingleEndLabel: Illegal label!");
            return XML_COMM_RESULT_FALIED_BAD_END_LABEL;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
        }
    }

    /* 空节点处理 */
    if (0 == pstXmlCtxInner->pstXMLCurrentNode->ulValueLength)
    {
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = VOS_NULL_PTR;
    }

    /* 当前节点退到父节点 */
    pstXmlCtxInner->pstXMLCurrentNode   = pstXmlCtxInner->pstXMLCurrentNode->pstFather;
    pstXmlCtxInner->enXMLAnalyseStatus  = XML_COMM_PARSE_ORIGINAL;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlLabelStart
功能描述  : 内部函数，状态机处理函数，节点标签名的处理
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
2.日    期   : 2012年12月11日
  作    者   : l00167671
  修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlLabelStart(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_STRU                 *pstNewNode;
    XML_COMM_RESULT_ENUM_UINT32         enXmlRslt;

    /* 标签名首字母不能为数字或标点符号 */
    /* 不支持双字节编码字符, 不支持命名空间, 点属性操作符等 */
    if (VOS_TRUE != XML_COMM_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlLabelStart: Illegal label name!");
        return XML_COMM_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* 创建一个新节点 */
    pstNewNode  = XML_COMM_CreateANode(pstXmlCtxInner->pstXMLCtx);
    if (VOS_NULL_PTR == pstNewNode)
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlLabelStart: Create Node Error!");
        return XML_COMM_RESULT_FALIED_CREATE_NODE_ERROR;
    }

    /* 根节点为空, 意味着当前节点即根节点 */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode)
    {
        pstXmlCtxInner->pstXMLRootNode = pstNewNode;
    }

    /* 并加入到当前节点的子节点链表末端，并将当前节点指针指向这个新节点 */
    if (VOS_NULL_PTR != pstXmlCtxInner->pstXMLCurrentNode)
    {
        enXmlRslt = XML_COMM_AddAChildNode(pstXmlCtxInner->pstXMLCurrentNode,
                               pstNewNode,
                               VOS_NULL_PTR);
        if (XML_COMM_RESULT_SUCCEED != enXmlRslt)
        {
            XML_WARNING_LOG("XML_COMM_AddAChildNode: Error!");
        }
        /* 如果包含子节点, 则清空节点值 */
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue      = VOS_NULL_PTR;
        pstXmlCtxInner->pstXMLCurrentNode->ulValueLength    = 0;
    }
    pstXmlCtxInner->pstXMLCurrentNode = pstNewNode;
    /*lint -e961*/
    /* 给节点Label赋值 */
    pstNewNode->pcNodeLabel = pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint +e961*/
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == XML_COMM_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == XML_COMM_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstNewNode->ulLabelLength++;
    }

    /* 遇到/或者>或者分隔符说明Node的名字结束了 */
    /* 遇到/结束并收尾整个节点, 下个字节一定是> */
    if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_LABEL_END_MUST_RIGHT;
    }
    /* 遇到>左标签结束 */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = pstXmlCtxInner->pcXMLStrCurChar + 1;
    }
    /* 标签名字结束, 进入属性解析状态 */
    else if (VOS_TRUE == XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_START;
    }
    else
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlLabelStart: Illegal label name!");
        return XML_COMM_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* 把这个字节放进当前节点值的缓冲区内 */
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength++;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlEndMustBeRight
功能描述  : 内部函数，状态机处理函数，进入Label/等待>
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlEndMustBeRight(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /*lint -e961*/
    /* 必须是>，否则为错误格式 */
    if ('>' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlEndMustBeRight: Illegal end label!");
        return XML_COMM_RESULT_FALIED_BAD_END_LABEL;
    }
    /*lint +e961*/
    /* 如果是根节点的结尾标签, 表明解析可以结束了 */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode->pstFather)
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_AFTER_ROOT_NODE;
        return XML_COMM_RESULT_SUCCEED_ALL_ENDS;
    }

    /* 当前节点退到父节点 */
    pstXmlCtxInner->pstXMLCurrentNode   = pstXmlCtxInner->pstXMLCurrentNode->pstFather;
    /* 变更状态 */
    pstXmlCtxInner->enXMLAnalyseStatus  = XML_COMM_PARSE_ORIGINAL;

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlAttribStart
功能描述  : 内部函数，状态机处理函数，进入属性的解析
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribStart(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 忽略Lable中的分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* 遇到尾节点标签 */
    if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_LABEL_END_MUST_RIGHT;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* 左标签结束, 回到初始状态 */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ORIGINAL;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* 进入标签名解析 */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_NAME_START;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlAttribNameStart
功能描述  : 内部函数，状态机处理函数，开始属性名字的解析
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribNameStart(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstNewAttrib;

    /* 属性名首字母不能为数字或标点符号, 不支持双字节编码字符 */
    if (VOS_TRUE != XML_COMM_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameStart: Illegal attribute name!");
        return XML_COMM_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    /* 创建一个新节点, 并加入到当前节点的属性链表末端 */
    pstNewAttrib = XML_COMM_CreateAnAttribute(pstXmlCtxInner->pstXMLCtx);
    if (XML_COMM_RESULT_SUCCEED != XML_COMM_AddAnAttribute(pstXmlCtxInner->pstXMLCurrentNode,
                                                           pstNewAttrib,
                                                           VOS_NULL_PTR))
    {
        return XML_COMM_RESULT_FALIED_CREATE_ATTRIB_ERROR;
    }
    /*lint -e961*/
    /* 给属性名赋值 */
    pstNewAttrib->pcAttribName = pstXmlCtxInner->pcXMLStrCurChar++;
    /*lint +e961*/
    pstNewAttrib->ulNameLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == XML_COMM_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == XML_COMM_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstNewAttrib->ulNameLength++;
    }

    /* 遇到=或者分隔符说明属性名结束了 */
    if ('=' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_NAME_END;
    }
    else if (VOS_TRUE == XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_NAME_END;
    }
    else
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameStart: Illegal attribute name!");
        return XML_COMM_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlAttribNameEnd
功能描述  : 内部函数，状态机处理函数，属性名字的解析完成处理
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribNameEnd(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 属性名结束后, 允许存在多个分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /*lint -e961*/
    /* 去掉分隔附后, 一定是'=' */
    if ('=' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameEnd: Lake of equal sign!");
        return XML_COMM_RESULT_FALIED_EXPECT_EQUAL_SIGN;
    }
    /*lint +e961*/
    /* 等号与属性值之间允许多个分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* 去掉分隔附后, 一定是单引号或双引号 */
    if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_VALUE_SINGLE;
    }
    else if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_VALUE_DOUBLE;
    }
    else
    {
        XML_WARNING_LOG("XML_COMM_ProcXmlAttribNameEnd: Lake of quotation mark!");
        return XML_COMM_RESULT_FALIED_NO_QUOTATION_MARK;
    }

    pstXmlCtxInner->pcXMLStrCurChar++;
    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlAttribValueSingle
功能描述  : 内部函数，状态机处理函数，以单引号结束的属性值
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
4.日    期   : 2012年12月11日
  作    者   : l00167671
  修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribValueSingle(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* 给当前节点最后一个属性的属性值中 */
    pstTmpAttrib = XML_COMM_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* 等待单引号 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* 属性值结束, 返回开始解析属性的状态 */
            pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return XML_COMM_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueSingle: Unexpect Char!");
            return XML_COMM_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueSingle: Lake of end quotation mark!");
    return XML_COMM_RESULT_FALIED_NO_QUOTATION_MARK;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlAttribValueDouble
功能描述  : 内部函数，状态机处理函数，以双引号结束的属性值
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAttribValueDouble(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* 给当前节点最后一个属性的属性值中 */
    pstTmpAttrib = XML_COMM_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return XML_COMM_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* 等待双引号 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* 属性值结束, 返回开始解析属性的状态 */
            pstXmlCtxInner->enXMLAnalyseStatus = XML_COMM_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return XML_COMM_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueDouble: Unexpect Char!");
            return XML_COMM_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("XML_COMM_ProcXmlAttribValueDouble: Lake of end quotation mark!");
    return XML_COMM_RESULT_FALIED_NO_QUOTATION_MARK;
}

/*****************************************************************************
函 数 名  : XML_COMM_ProcXmlAfterRootNode
功能描述  : 内部函数，状态机处理函数，根节点结束后的处理
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ProcXmlAfterRootNode(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 直到码流末尾都仅允许出现分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != XML_COMM_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("XML_COMM_ProcXmlAfterRootNode: Unexpect charactor out of Root!");
            return XML_COMM_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    return XML_COMM_RESULT_SUCCEED_ALL_ENDS;
}

/*****************************************************************************
函 数 名  : XML_COMM_Analyse
功能描述  : 内部函数，主状态机
输入参数  : pstXmlCtxInner    内部上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_Analyse(
    XML_COMM_CTX_INNER_STRU            *pstXmlCtxInner)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;
    XML_COMM_ANALYSE_FUNC               afucXmlAnalyseFucs[] =
    {
        XML_COMM_ProcXmlOriginal,
        XML_COMM_ProcXmlEnterLabel,
        XML_COMM_ProcXmlDeclaration,
        XML_COMM_ProcXmlComment,
        XML_COMM_ProcXmlLabelStart,
        XML_COMM_ProcXmlSingleEndLabel,
        XML_COMM_ProcXmlEndMustBeRight,
        XML_COMM_ProcXmlAttribStart,
        XML_COMM_ProcXmlAttribNameStart,
        XML_COMM_ProcXmlAttribNameEnd,
        XML_COMM_ProcXmlAttribValueSingle,
        XML_COMM_ProcXmlAttribValueDouble,
        XML_COMM_ProcXmlAfterRootNode
    };

    /* 判断解析状态的合法性 */
    if (pstXmlCtxInner->enXMLAnalyseStatus >= XML_COMM_PARSE_BUTT)
    {
        XML_WARNING_LOG("XML_COMM_Analyse: Invalid Analyse Status!");
        return XML_COMM_RESULT_FALIED_ANALYSE_STATUS_ERROR;
    }

    /* 通过索引调用状态机处理函数 */
    ulReturnVal = afucXmlAnalyseFucs[pstXmlCtxInner->enXMLAnalyseStatus](pstXmlCtxInner);

    return ulReturnVal;
}

/*****************************************************************************
函 数 名  : XML_COMM_InitXMLCtx
功能描述  : 初始化XML API上下文
输入参数  : pcXmlStr    XML格式码流
输出参数  : 无
返 回 值  : XML_COMM_RESULT_SUCCEED成功, 其它失败码参见枚举定义
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_InitXMLCtx(XML_COMM_CTX_STRU *pstXmlCtx)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("XML_COMM_InitXMLCtx: pstXmlCtx is VOS_NULL_PTR!");
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 初始化内存空间 */
    PS_MEM_SET(pstXmlCtx, 0x00, sizeof(XML_COMM_CTX_STRU));
    ulReturnVal = XML_COMM_InitMemory(pstXmlCtx);

    return ulReturnVal;
}

/*****************************************************************************
函 数 名  : XML_COMM_BuildXMLTree
功能描述  : XML码流解析总入口函数, 根据XML格式码流建立一棵XML树
输入参数  : pcXmlStr    XML格式码流
            pstXmlCtx   XML API上下文
输出参数  : 无
返 回 值  : XML树的根节点
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_NODE_STRU* XML_COMM_BuildXMLTree(
    VOS_CHAR                           *pcXmlStr,
    XML_COMM_CTX_STRU                  *pstXmlCtx)
{
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;
    XML_COMM_CTX_INNER_STRU             stXmlCtxInner;
    VOS_UINT32                          ulStrLen;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pcXmlStr) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("XML_COMM_BuildXMLTree: pcXmlStr or pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* 对解析的XML码流的长度进行约束 */
    ulStrLen = VOS_StrLen(pcXmlStr);
    if ( (0 == ulStrLen)
      || (ulStrLen > XML_COMM_MAX_STR_LEN) )
    {
        XML_WARNING_LOG("XML_COMM_BuildXMLTree: pcXmlStr Length Error!");
        return VOS_NULL_PTR;
    }

    /* 初始化内存管理 */
    ulReturnVal = XML_COMM_InitMemory(pstXmlCtx);
    if (XML_COMM_RESULT_SUCCEED != ulReturnVal)
    {
        return VOS_NULL_PTR;
    }

    stXmlCtxInner.pstXMLCtx             = pstXmlCtx;
    stXmlCtxInner.pstXMLRootNode        = VOS_NULL_PTR;
    stXmlCtxInner.pstXMLCurrentNode     = VOS_NULL_PTR;
    stXmlCtxInner.pcXMLStrCurChar       = pcXmlStr;
    stXmlCtxInner.enXMLAnalyseStatus    = XML_COMM_PARSE_ORIGINAL;

    /* 遍历XML格式码流，解析为XML树结构 */
    while ('\0' != *(stXmlCtxInner.pcXMLStrCurChar))
    {
        ulReturnVal = XML_COMM_Analyse(&stXmlCtxInner);

        /* 处理失败直接中断循环返回 */
        if ( (XML_COMM_RESULT_SUCCEED != ulReturnVal)
          && (XML_COMM_RESULT_SUCCEED_ALL_ENDS != ulReturnVal) )
        {
            break;
        }
    }

    /* 解析正常完成，返回XML树结构根节点 */
    if (XML_COMM_RESULT_SUCCEED_ALL_ENDS == ulReturnVal)
    {
        return stXmlCtxInner.pstXMLRootNode;
    }

    /* 解析异常, 释放上下文中分配的内存, 返回空指针 */
    XML_WARNING1_LOG("XML_COMM_BuildXMLTree: Xml Analyse Failure, Error Code: ", ulReturnVal);
    (VOS_VOID)XML_COMM_ClearXMLCtx(pstXmlCtx);
    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : XML_COMM_StackPushNode
 功能描述  : 将XML的一个节点压栈
 输入参数  : pstTraverseStack   用于存放节点的栈的指针
 输出参数  : pstStackNode       待压入栈的节点
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID XML_COMM_StackPushNode(
    XML_COMM_TRAVERSE_STACK_STRU       *pstTraverseStack,
    XML_COMM_TRAVERSE_STACK_NODE_STRU  *pstStackNode)
{
    /*lint -e961*/
    if (XML_COMM_MAX_STACK_DEPTH > pstTraverseStack->ulStackDepth)
    {
        pstTraverseStack->astStackNode[pstTraverseStack->ulStackDepth++] = *pstStackNode;
    }
    /*lint +e961*/
    return;
}

/*****************************************************************************
 函 数 名  : XML_COMM_StackPopNode
 功能描述  : 将栈中的节点弹出
 输入参数  : pstTraverseStack   用于存放节点的栈的指针
 输出参数  : pstStackNode       栈顶的节点
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID XML_COMM_StackPopNode(
    XML_COMM_TRAVERSE_STACK_STRU       *pstTraverseStack,
    XML_COMM_TRAVERSE_STACK_NODE_STRU  *pstStackNode)
{
    /*lint -e961*/
    if (0 < pstTraverseStack->ulStackDepth)
    {
        *pstStackNode = pstTraverseStack->astStackNode[--pstTraverseStack->ulStackDepth];
    }
    /*lint +e961*/
    return;
}

/*****************************************************************************
函 数 名  : XML_COMM_PrintIndentation
功能描述  : 内部函数, 打印缩进
输入参数  : pcXmlStr        用于存放码流的指针
            plLenRemain     当前可以存放的码流的最大长度
            ulLevel         树结构层级
            enFormatting    输出格式，紧凑或换行缩进
输出参数  : plLenRemain     当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月9日
  作    者   : l00198894
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintIndentation(
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    VOS_UINT32                          ulLevel,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLen;

    /* 根据格式判断是否需要缩进 */
    if (XML_FORMATTING_INDENTED == enFormatting)
    {
        /* 判断内存空间是否充足 */
        ulLen = ulLevel * XML_COMM_INDENTATION_SPACE_NUM;
        if (ulLen >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintIndentation: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        /* 根据层数输出缩进 */
        for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
        {
            *((*ppcXmlStr)++) = ' ';
        }
        /*lint +e961*/
        (*pulLenRemain) -= ulLen;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_PrintAttribs
功能描述  : 内部函数, 打印属性
输入参数  : pstAttribute    属性链表首节点
            pcXmlStr        用于存放码流的指针
            plLenRemain     当前可以存放的码流的最大长度
输出参数  : plLenRemain     当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月9日
  作    者   : l00198894
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintAttribs(
    XML_COMM_NODE_ATTRIBUTE_STRU       *pstAttribute,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain)
{
    VOS_UINT32                          ulLen;

    /* 循环打印属性链表 */
    while (VOS_NULL_PTR != pstAttribute)
    {
        /* 判断内存空间是否充足 */
        ulLen = XML_COMM_ATTRIB_PUNCTUATION_LEN
              + pstAttribute->ulNameLength
              + pstAttribute->ulValueLength;
        if (ulLen >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintAttribs: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        /* 填写属性间的空格 */
        *((*ppcXmlStr)++) = ' ';

        /* 填写属性名 */
        PS_MEM_CPY((*ppcXmlStr), pstAttribute->pcAttribName, pstAttribute->ulNameLength);
        (*ppcXmlStr) += pstAttribute->ulNameLength;

        /* 填写=" (暂不考虑单引号的情况) */
        *((*ppcXmlStr)++) = '=';
        *((*ppcXmlStr)++) = '\"';

        /* 填写属性值 */
        PS_MEM_CPY((*ppcXmlStr), pstAttribute->pcAttribValue, pstAttribute->ulValueLength);
        (*ppcXmlStr) += pstAttribute->ulValueLength;

        /* 填写" (暂不考虑单引号的情况) */
        *((*ppcXmlStr)++) = '\"';
        /*lint +e961*/
        (*pulLenRemain) -= ulLen;
        pstAttribute = pstAttribute->pstNexBrother;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_PrintCRLF
功能描述  : 内部函数, 打印回车换行
输入参数  : pcXmlStr        用于存放码流的指针
            plLenRemain     当前可以存放的码流的最大长度
            enFormatting    输出格式，紧凑或换行缩进
输出参数  : plLenRemain     当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月9日
  作    者   : l00198894
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintCRLF(
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    if (XML_FORMATTING_INDENTED == enFormatting)
    {
        if (XML_COMM_CRLF_LEN >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintCRLF: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        /* 填写回车换行符 */
        *((*ppcXmlStr)++) = '\r';
        *((*ppcXmlStr)++) = '\n';
        /*lint +e961*/
        (*pulLenRemain)  -= XML_COMM_CRLF_LEN;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_PrintStartLabelEnd
功能描述  : 内部函数, 打印左标签结束符
输入参数  : pstNode         节点指针
            pcXmlStr        用于存放码流的指针
            plLenRemain     当前可以存放的码流的最大长度
            enFormatting    输出格式，紧凑或换行缩进
输出参数  : plLenRemain     当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月9日
  作    者   : l00198894
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintStartLabelEnd(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulHasValue;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* 判断该节点是否有Value */
    ulHasValue  = VOS_TRUE;
    if ( (VOS_NULL_PTR == pstNode->pcNodeValue)
      || (0 == pstNode->ulValueLength) )
    {
        ulHasValue  = VOS_FALSE;
    }

    /* 有子节点或有Value则左标签以">"结束, 否则以"/>"结束 */
    if ((VOS_NULL_PTR != pstNode->pstFirstChild) || (VOS_TRUE == ulHasValue))
    {
        if (XML_COMM_LABEL_END_LEN >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintStartLabelEnd: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }
        /*lint -e961*/
        *((*ppcXmlStr)++) = '>';
        /*lint +e961*/
        (*pulLenRemain)   -= XML_COMM_LABEL_END_LEN;
    }
    else
    {
        if (XML_COMM_SINGLE_LABLE_END_LEN >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintStartLabelEnd: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }

        /*lint -e961*/
        *((*ppcXmlStr)++) = '/';
        *((*ppcXmlStr)++) = '>';
        /*lint +e961*/
        (*pulLenRemain)   -= XML_COMM_SINGLE_LABLE_END_LEN;
    }

    /* 节点结束, 填写回车换行 */
    if (VOS_FALSE == ulHasValue)
    {
        ulResult = XML_COMM_PrintCRLF(ppcXmlStr, pulLenRemain, enFormatting);
        if (XML_COMM_RESULT_SUCCEED != ulResult)
        {
            return ulResult;
        }
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_PrintStartLabelAndAttribs
功能描述  : 内部函数, 打印左标签结束符
输入参数  : pstNode         节点指针
            pcXmlStr        用于存放码流的指针
            plLenRemain     当前可以存放的码流的最大长度
            ulLevel         树结构层级
            enFormatting    输出格式，紧凑或换行缩进
输出参数  : plLenRemain     当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月9日
  作    者   : l00198894
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintStartLabelAndAttribs(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    VOS_UINT32                          ulLevel,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulLen;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* 输出缩进 */
    ulResult = XML_COMM_PrintIndentation(ppcXmlStr, pulLenRemain, ulLevel, enFormatting);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    /* 计算左标签的长度, 并判断内存是否够用 */
    ulLen = XML_COMM_LABEL_START_LEN + pstNode->ulLabelLength;
    if (ulLen >= *pulLenRemain)
    {
        XML_WARNING_LOG("XML_COMM_PrintStartLabelAndAttribs: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
    }

    /*lint -e961*/
    /* 写前标签 */
    *((*ppcXmlStr)++) = '<';
    /*lint +e961*/

    /* 填写标签名 */
    PS_MEM_CPY((*ppcXmlStr), pstNode->pcNodeLabel, pstNode->ulLabelLength);
    (*ppcXmlStr)      += pstNode->ulLabelLength;
    (*pulLenRemain)   -= ulLen;

    /* 遍历属性链表 */
    ulResult = XML_COMM_PrintAttribs(pstNode->pstFirstAttrib, ppcXmlStr, pulLenRemain);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    /* 写后标签 */
    ulResult = XML_COMM_PrintStartLabelEnd(pstNode,
                                           ppcXmlStr,
                                           pulLenRemain,
                                           enFormatting);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_PrintEndLabel
功能描述  : 内部函数, 打印右标签
输入参数  : pstNode         节点指针
            pcXmlStr        用于存放码流的指针
            plLenRemain     当前可以存放的码流的最大长度
输出参数  : plLenRemain     当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月9日
  作    者   : l00198894
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintEndLabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain)
{
    VOS_UINT32                          ulLen;

    /* 计算右标签的长度, 并判断内存是否够用 */
    ulLen = XML_COMM_END_LABEL_START_LEN + pstNode->ulLabelLength + XML_COMM_LABEL_END_LEN;
    if (ulLen >= *pulLenRemain)
    {
        XML_WARNING_LOG("XML_COMM_PrintEndLabel: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
    }
    /*lint -e961*/
    /* 填写右标签起始符"</" */
    *((*ppcXmlStr)++) = '<';
    *((*ppcXmlStr)++) = '/';

    /* 填写标签名 */
    PS_MEM_CPY((*ppcXmlStr), pstNode->pcNodeLabel, pstNode->ulLabelLength);
    (*ppcXmlStr)      += pstNode->ulLabelLength;

    /* 填写右标签结束符">" */
    *((*ppcXmlStr)++) = '>';
    (*pulLenRemain)   -= ulLen;
    /*lint +e961*/
    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_PrintValueAndELabel
功能描述  : 内部函数, 打印节点值及右标签
输入参数  : pstNode         节点指针
            pcXmlStr        用于存放码流的指针
            plLenRemain     当前可以存放的码流的最大长度
            ulLevel         树结构层级
            enFormatting    输出格式，紧凑或换行缩进
输出参数  : plLenRemain     当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月9日
  作    者   : l00198894
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_PrintValueAndELabel(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    VOS_UINT32                          ulLevel,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    VOS_UINT32                          ulHasValue;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* 判断该节点是否有Value */
    ulHasValue  = VOS_TRUE;
    if ( (VOS_NULL_PTR == pstNode->pcNodeValue)
      || (0 == pstNode->ulValueLength) )
    {
        ulHasValue  = VOS_FALSE;
    }

    /* 如果节点既无子节点也无节点值, 则直接返回 */
    if ((VOS_NULL_PTR == pstNode->pstFirstChild) && (VOS_FALSE == ulHasValue))
    {
        return XML_COMM_RESULT_SUCCEED;
    }

    /* 如果该节点有值则先输出节点值, 否则输出缩进 */
    if (VOS_TRUE == ulHasValue)
    {
        /* 计算节点值的长度, 并判断内存是否够用 */
        if (pstNode->ulValueLength >= *pulLenRemain)
        {
            XML_WARNING_LOG("XML_COMM_PrintValueAndELabel: Memory not enough!");
            return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
        }

        /* 填写节点值 */
        PS_MEM_CPY((*ppcXmlStr), pstNode->pcNodeValue, pstNode->ulValueLength);
        (*ppcXmlStr)      += pstNode->ulValueLength;
        (*pulLenRemain)   -= pstNode->ulValueLength;
    }
    else
    {
        /* 输出缩进 */
        ulResult = XML_COMM_PrintIndentation(ppcXmlStr, pulLenRemain, ulLevel, enFormatting);
        if (XML_COMM_RESULT_SUCCEED != ulResult)
        {
            return ulResult;
        }
    }

    /* 输出右标签 */
    ulResult = XML_COMM_PrintEndLabel(pstNode, ppcXmlStr, pulLenRemain);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    /* 节点结束, 填写回车换行 */
    ulResult = XML_COMM_PrintCRLF(ppcXmlStr, pulLenRemain, enFormatting);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        return ulResult;
    }

    return XML_COMM_RESULT_SUCCEED;
}

/*****************************************************************************
函 数 名  : XML_COMM_GenerateXMLStr
功能描述  : 内部函数, 根据XML当前的树结构，生成XML码流
输入参数  : pstXMLRootNode: XML树的根节点
            pcXmlStr:       用于存放码流的指针
            plLenRemain:    当前可以存放的码流的最大长度
            enFormatting    输出格式，紧凑或换行缩进
输出参数  : plLenRemain:    当前可以存放的码流的最大长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年7月6日
  作    者   : h44270
  修改内容   : 新生成函数
*****************************************************************************/
LOCAL XML_COMM_RESULT_ENUM_UINT32 XML_COMM_GenerateXMLStr(
    XML_COMM_NODE_STRU                 *pstXMLRootNode,
    VOS_CHAR                          **ppcXmlStr,
    VOS_UINT32                         *pulLenRemain,
    XML_COMM_FORMATTING_ENUM_UINT8      enFormatting)
{
    XML_COMM_TRAVERSE_STACK_STRU       *pstTraverseStack;
    XML_COMM_NODE_STRU                 *pstTmpNode;
    XML_COMM_NODE_STRU                  stXmlRootNode;
    XML_COMM_TRAVERSE_STACK_NODE_STRU   stTmpStackNode;
    XML_COMM_RESULT_ENUM_UINT32         ulResult;

    /* 初始化栈空间 */
    pstTraverseStack = (XML_COMM_TRAVERSE_STACK_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                   sizeof(XML_COMM_TRAVERSE_STACK_STRU));
    if (VOS_NULL_PTR == pstTraverseStack)
    {
        XML_ERROR_LOG("XML_COMM_GenerateXMLStr: Malloc Failure!");
        return XML_COMM_RESULT_FALIED_MALLOC;
    }
    PS_MEM_SET(pstTraverseStack, 0, sizeof(XML_COMM_TRAVERSE_STACK_STRU));

    /* 初始化参数 */
    PS_MEM_SET(&stXmlRootNode, 0, sizeof(XML_COMM_NODE_STRU));
    ulResult = XML_COMM_AddAChildNode(&stXmlRootNode, pstXMLRootNode, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != ulResult)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
        return ulResult;
    }
    pstTmpNode = VOS_NULL_PTR;

    /* 记录当前的节点 */
    stTmpStackNode.pstXmlNode = &stXmlRootNode;
    stTmpStackNode.ulVisited  = VOS_FALSE;
    XML_COMM_StackPushNode(pstTraverseStack, &stTmpStackNode);

    /* 深度为0时，退出循环 */
    do
    {
        /* 存在孩子节点 并且还没被访问过 */
        pstTmpNode = stTmpStackNode.pstXmlNode->pstFirstChild;
        while ( (VOS_NULL_PTR != pstTmpNode)
             && (VOS_FALSE == stTmpStackNode.ulVisited) )
        {
            /* 输出左标签，标签名，属性 */
            ulResult = XML_COMM_PrintStartLabelAndAttribs(pstTmpNode,
                                                          ppcXmlStr,
                                                          pulLenRemain,
                                                          pstTraverseStack->ulStackDepth - 1,
                                                          enFormatting);
            if (XML_COMM_RESULT_SUCCEED != ulResult)
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
                return ulResult;
            }

            /* 节点设置成已经被访问 */
            stTmpStackNode.pstXmlNode    = pstTmpNode;
            stTmpStackNode.ulVisited     = VOS_TRUE;

            /* 如果有子节点，则压栈 */
            if (VOS_NULL_PTR != pstTmpNode->pstFirstChild)
            {
                XML_COMM_StackPushNode(pstTraverseStack, &stTmpStackNode);
                stTmpStackNode.ulVisited = VOS_FALSE;
                pstTmpNode               = pstTmpNode->pstFirstChild;
            }
        }

        /* stTmpStackNode的节点打印Value, 右标签值 */
        ulResult = XML_COMM_PrintValueAndELabel(stTmpStackNode.pstXmlNode,
                                                ppcXmlStr,
                                                pulLenRemain,
                                                pstTraverseStack->ulStackDepth - 1,
                                                enFormatting);
        if (XML_COMM_RESULT_SUCCEED != ulResult)
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
            return ulResult;
        }

        /*存在兄弟节点*/
        pstTmpNode = stTmpStackNode.pstXmlNode->pstNexBrother;
        while (VOS_NULL_PTR != pstTmpNode)
        {
            /* 输出左标签，标签名，属性值 */
            ulResult = XML_COMM_PrintStartLabelAndAttribs(pstTmpNode,
                                                          ppcXmlStr,
                                                          pulLenRemain,
                                                          pstTraverseStack->ulStackDepth - 1,
                                                          enFormatting);
            if (XML_COMM_RESULT_SUCCEED != ulResult)
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
                return ulResult;
            }

            /* 兄弟节点存在孩子节点 */
            if  (VOS_NULL_PTR != pstTmpNode->pstFirstChild)
            {
                /*兄弟节点压栈*/
                stTmpStackNode.pstXmlNode = pstTmpNode;
                stTmpStackNode.ulVisited  = VOS_TRUE;
                XML_COMM_StackPushNode(pstTraverseStack, &stTmpStackNode);
                stTmpStackNode.ulVisited  = VOS_FALSE;
                break;
            }
            else
            {
                /*打印Value, 右标签值*/
                ulResult = XML_COMM_PrintValueAndELabel(pstTmpNode,
                                                        ppcXmlStr,
                                                        pulLenRemain,
                                                        pstTraverseStack->ulStackDepth - 1,
                                                        enFormatting);
                if (XML_COMM_RESULT_SUCCEED != ulResult)
                {
                    PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
                    return ulResult;
                }

                /*指向下一个兄弟节点*/
                pstTmpNode = pstTmpNode->pstNexBrother;
            }
        }

        /*不存在孩子节点，或者当前节点已经访问过了,则可以弹出栈*/
        if ( (VOS_NULL_PTR == stTmpStackNode.pstXmlNode->pstFirstChild)
          || (VOS_TRUE == stTmpStackNode.ulVisited) )
        {
            /* 弹栈 */
            XML_COMM_StackPopNode(pstTraverseStack, &stTmpStackNode);
        }

    }while (0 != pstTraverseStack->ulStackDepth);

    PS_MEM_FREE(WUEPS_PID_TAF, pstTraverseStack);
    return ulResult;
}

/*****************************************************************************
函 数 名  : XML_COMM_BuildXMLStr
功能描述  : 从一颗XML树结构生成XML格式码流
输入参数  : pstNode     XML树根节点
            pulLength   用于存放XML格式码流的内存长度
输出参数  : pcXmlStr    用于存放XML格式码流的内存
            pulLength   实际生成的XML格式码流的长度
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_BuildXMLStr(
    XML_COMM_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcXmlStr,
    VOS_UINT32                         *pulLength,
    XML_COMM_FORMATTING_ENUM_UINT8      enXmlFormat)
{
    VOS_UINT32                          ulLenRemain;
    VOS_UINT32                          ulLen;
    XML_COMM_RESULT_ENUM_UINT32         ulReturnVal;

    /* 参数合法性检查 */
    if ( (VOS_NULL_PTR == pstNode)
      || (VOS_NULL_PTR == pcXmlStr)
      || (VOS_NULL_PTR == pulLength) )
    {
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 打印版本信息 */
    ulLen     = VOS_StrLen(XML_COMM_VERSION_STR);
    if (ulLen >= (*pulLength))
    {
        XML_WARNING_LOG("XML_COMM_BuildXMLStr: Memory not enough!");
        return XML_COMM_RESULT_FALIED_MEM_NOT_ENOUGH;
    }

    PS_MEM_CPY(pcXmlStr, XML_COMM_VERSION_STR, ulLen);
    pcXmlStr    += ulLen;
    ulLenRemain = *pulLength - ulLen;

    /* 打印回车换行 */
    ulReturnVal = XML_COMM_PrintCRLF(&pcXmlStr, &ulLenRemain, enXmlFormat);
    if (XML_COMM_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* 调用XML格式码流生成函数 */
    ulReturnVal = XML_COMM_GenerateXMLStr(pstNode, &pcXmlStr, &ulLenRemain, enXmlFormat);
    if (XML_COMM_RESULT_SUCCEED == ulReturnVal)
    {
        *pulLength -= ulLenRemain;
        *pcXmlStr = '\0';
    }

    return ulReturnVal;
}

/*****************************************************************************
函 数 名  : XML_COMM_ClearXMLCtx
功能描述  : 清理XML上下文, 每次使用完XML API都要求调用此函数
输入参数  : pstXmlCtx     XML API上下文
输出参数  : 无
返 回 值  : XML_COMM_RESULT_ENUM_UINT32
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年6月28日
  作    者  : 李紫剑 00198894
  修改内容  : 新生成函数
*****************************************************************************/
XML_COMM_RESULT_ENUM_UINT32 XML_COMM_ClearXMLCtx(XML_COMM_CTX_STRU *pstXmlCtx)
{
    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        return XML_COMM_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 释放上下文中占用的内存 */
    if (VOS_NULL_PTR != pstXmlCtx->pucXMLBuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstXmlCtx->pucXMLBuffer);
    }

    PS_MEM_SET(pstXmlCtx, 0x00, sizeof(XML_COMM_CTX_STRU));
    return XML_COMM_RESULT_SUCCEED;
}

#endif

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

