

/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include "product_config.h"
#include "OamXmlComm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_VSIM_XML_C

/*****************************************************************************
2 全局变量定义
*****************************************************************************/
typedef VOS_UINT32 (*OAM_XML_ANALYSE_FUNC)(OAM_XML_CTX_INNER_STRU *pstXmlCtxInner);

/*****************************************************************************
3 函数定义
*****************************************************************************/
#if (FEATURE_VSIM == FEATURE_ON)

VOS_INT32 OAM_XML_GetChildCount(OAM_XML_NODE_STRU *pstNode)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetChildCount: pstNode is VOS_NULL_PTR!");
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


OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lChildIndex)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetChildNodeByIndex: pstNode is VOS_NULL_PTR!");
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


OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByLabel(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabel)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    VOS_UINT32                          ulLabelLength;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcLabel))
    {
        XML_WARNING_LOG("OAM_XML_GetChildNodeByLabel: pstNode or pcLabel is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* 从长子链表头开始,遍历所有子节点 */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        ulLabelLength   = pstTmpNode->ulLabelLength;
        if (VOS_StrLen(pcLabel) == ulLabelLength)
        {
            if (0 == VOS_MemCmp(pstTmpNode->pcNodeLabel, pcLabel, ulLabelLength))
            {
                return pstTmpNode;
            }
        }
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return VOS_NULL_PTR;
}


OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByAttributeValue(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribValue)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_UINT32                          ulValueLength;
    VOS_CHAR                          *pcContent;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcAttribValue))
    {
        XML_WARNING_LOG("OAM_XML_GetChildNodeByAttributeValue: pstNode or pcAttribValue is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* 从长子链表头开始,遍历所有子节点 */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        pstTmpAttribute = pstTmpNode->pstFirstAttrib;
        if(VOS_NULL_PTR == pstTmpAttribute)
        {
            XML_WARNING_LOG("OAM_XML_GetChildNodeByAttributeValue: pstTmpAttribute is VOS_NULL_PTR!");
            return VOS_NULL_PTR;
        }

        pcContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstTmpAttribute->ulValueLength);

        if(VOS_NULL_PTR == pcContent)
        {
            XML_WARNING_LOG("OAM_XML_GetChildNodeByAttributeValue: The VOS_MemAlloc is NULL ");

            return VOS_NULL_PTR;
        }

        OAM_XML_GetStrContent(pstTmpAttribute->pcAttribValue,pstTmpAttribute->ulValueLength,pcContent,&ulValueLength);

        if (VOS_StrLen(pcAttribValue) == ulValueLength)
        {
            if (0 == VOS_MemCmp(pcContent, pcAttribValue, ulValueLength))
            {
                /*lint -e534*/
                VOS_MemFree(WUEPS_PID_USIM, pcContent);
                /*lint +e534*/
                return pstTmpNode;
            }
        }
        pstTmpNode = pstTmpNode->pstNexBrother;
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/
    }

    return VOS_NULL_PTR;
}


VOS_INT32 OAM_XML_GetAttributeCount(OAM_XML_NODE_STRU *pstNode)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetAttributeCount: pstNode is VOS_NULL_PTR!");
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


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lAttribIndex)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetAttributeByIndex: pstNode is VOS_NULL_PTR!");
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


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByAttributeName(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribName)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;
    VOS_UINT32                          ulNameLength;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcAttribName))
    {
        XML_WARNING_LOG("OAM_XML_GetAttributeByAttributeName: pstNode or pcAttribName is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* 从链表头开始,遍历所有属性 */
    pstTmpAttrib = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttrib)
    {
        ulNameLength = pstTmpAttrib->ulNameLength;
        if (VOS_StrLen(pcAttribName) == ulNameLength)
        {
            if (0 == VOS_MemCmp(pstTmpAttrib->pcAttribName, pcAttribName, ulNameLength))
            {
                return pstTmpAttrib;
            }
        }
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    XML_WARNING_LOG("OAM_XML_GetAttributeByAttributeName: Can't find the Attribute!");
    return VOS_NULL_PTR;
}


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetLastAttribute(
    OAM_XML_NODE_STRU                 *pstNode)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;

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


OAM_XML_RESULT_ENUM_UINT32 OAM_XML_InitMemory(OAM_XML_CTX_STRU *pstXmlCtx)
{
    /* 上下文中内存地址为空, 则分配内存并初始化 */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
    {
        pstXmlCtx->ulXMLBuffSize    = OAM_XML_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffer     = (VOS_UINT8*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT,pstXmlCtx->ulXMLBuffSize);
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;

        /* 申请内存失败 */
        if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
        {
            XML_ERROR_LOG("OAM_XML_InitMemory: Malloc Failure!");
            return OAM_XML_RESULT_FALIED_MALLOC;
        }
    }
    /* 上下文已分配内存空间, 则只需初始化 */
    else
    {
        pstXmlCtx->ulXMLBuffSize    = OAM_XML_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;
    }

    /*lint -e534*/
    VOS_MemSet(pstXmlCtx->pucXMLBuffer, 0x00, pstXmlCtx->ulXMLBuffSize);
    /*lint +e534*/

    return OAM_XML_RESULT_SUCCEED;
}


VOS_VOID* OAM_XML_Malloc(
    OAM_XML_CTX_STRU                  *pstXmlCtx,
    VOS_UINT32                          ulSize)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;
    VOS_INT32                           iRemainMemSize;
    VOS_VOID                           *pReturn;

    pReturn     = VOS_NULL_PTR;
    ulReturnVal = OAM_XML_RESULT_SUCCEED;

    /* 判断上下文中的当前内存指针是否可用, 不可用则调用初始化内存函数 */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffCur)
    {
        ulReturnVal = OAM_XML_InitMemory(pstXmlCtx);
    }

    if (OAM_XML_RESULT_SUCCEED == ulReturnVal)
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


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_CreateAnAttribute(OAM_XML_CTX_STRU *pstXmlCtx)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstAttribute;
    VOS_UINT32                          ulAttribStruSize;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("OAM_XML_CreateAnAttribute: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstAttribute        = VOS_NULL_PTR;
    ulAttribStruSize    = sizeof(OAM_XML_NODE_ATTRIBUTE_STRU);

    /* 调用XML模块内存分配函数，申请一块节点内存 */
    pstAttribute = (OAM_XML_NODE_ATTRIBUTE_STRU*)OAM_XML_Malloc(pstXmlCtx, ulAttribStruSize);

    return pstAttribute;
}



OAM_XML_NODE_STRU* OAM_XML_CreateANode(OAM_XML_CTX_STRU *pstXmlCtx)
{
    OAM_XML_NODE_STRU                 *pstNode;
    VOS_UINT32                          ulNodeStruSize;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("OAM_XML_CreateANode: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstNode         = VOS_NULL_PTR;
    ulNodeStruSize  = sizeof(OAM_XML_NODE_STRU);

    /* 调用XML模块内存分配函数，申请一块节点内存 */
    pstNode = (OAM_XML_NODE_STRU*)OAM_XML_Malloc(pstXmlCtx, ulNodeStruSize);

    return pstNode;
}




OAM_XML_RESULT_ENUM_UINT32 OAM_XML_AddAChildNode(
    OAM_XML_NODE_STRU                 *pstFather,
    OAM_XML_NODE_STRU                 *pstChild,
    OAM_XML_NODE_STRU                 *pstYoungBrother)
{
    OAM_XML_NODE_STRU                 *pstTmpChild;
    OAM_XML_NODE_STRU                 *pstLastChild;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstFather) || (VOS_NULL_PTR == pstChild))
    {
        XML_WARNING_LOG("OAM_XML_AddAChildNode: pstFather or pstChild is VOS_NULL_PTR!");
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
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

        return OAM_XML_RESULT_SUCCEED;
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
            return OAM_XML_RESULT_FAILED_NODE_NOT_FOUND;
        }
        else
        {
            pstLastChild->pstNexBrother = pstChild;
            pstChild->pstPreBrother     = pstLastChild;
            pstChild->pstNexBrother     = VOS_NULL_PTR;
            return OAM_XML_RESULT_SUCCEED;
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

    return OAM_XML_RESULT_SUCCEED;
}


OAM_XML_RESULT_ENUM_UINT32 OAM_XML_AddAnAttribute(
    OAM_XML_NODE_STRU                 *pstNode,
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstAttribute,
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstYoungBrother)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstAttribute))
    {
        XML_WARNING_LOG("OAM_XML_AddAnAttribute: pstNode or pstAttribute is VOS_NULL_PTR!");
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
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

        return OAM_XML_RESULT_SUCCEED;
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
        return OAM_XML_RESULT_FAILED_ATTRIB_NOT_FOUND;
    }

    /* 把pstAttribute插入pstTmpAttrib和pstYoungBrother之间 */
    pstTmpAttrib->pstNexBrother     = pstAttribute;
    pstAttribute->pstPreBrother     = pstTmpAttrib;
    pstAttribute->pstNexBrother     = pstYoungBrother;
    if (VOS_NULL_PTR != pstYoungBrother)
    {
        pstYoungBrother->pstPreBrother = pstAttribute;
    }

    return OAM_XML_RESULT_SUCCEED;
}


VOS_UINT32 OAM_XML_IsSeparator(VOS_CHAR cCharacter)
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


static VOS_UINT32 OAM_XML_IsLetter(VOS_CHAR cCharacter)
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


static VOS_UINT32 OAM_XML_IsKeySymbol(VOS_CHAR cCharacter)
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


static VOS_UINT32 OAM_XML_IsPunctuation(VOS_CHAR cCharacter)
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


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlOriginal(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 遇到<则更改状态 */
    if ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ENTER_LABEL;
    }
    /* 当前节点指针为空, 认为没有进入节点, 忽略该字符 */
    else if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode)
    {
        /* 此时如果没有根节点，且字符不能忽略需要返回异常 */
        if ( (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
          && (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode) )
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlOriginal: Unexpect charactor out of Root!");
            return OAM_XML_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
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
    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlEnterLabel(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 遇到首行版本信息 */
    if ('?' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_DECLARATION;
    }
    /* 遇到注释 */
    else if ('!' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_COMMENT;
    }
    /* 遇到尾节点标签 */
    else if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_SINGLE_ENDS_LABEL;
    }
    /* 进入一个新节点 */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_NODE_LABEL_START;
    }

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlDeclaration(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 将指针移到"<?"后 */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* 目前无解析版本信息的需求，暂不作处理, 直到遇到"?>"结束 */
    while ('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ( ('?' == *(pstXmlCtxInner->pcXMLStrCurChar++))
          && ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return OAM_XML_RESULT_SUCCEED;
        }
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlDeclaration: The declaration has no end!");
    return OAM_XML_RESULT_FALIED_DECLARATION_NO_END;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlComment(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 将指针移到"<!"后 */
    pstXmlCtxInner->pcXMLStrCurChar++;

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
                    pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
                    return OAM_XML_RESULT_SUCCEED;
                }
                else
                {
                    XML_WARNING_LOG("OAM_XML_ProcXmlComment: The comment has syntax error!");
                    return OAM_XML_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
                }
            }
        }

        XML_WARNING_LOG("OAM_XML_ProcXmlComment: The comment has no end!");
        return OAM_XML_RESULT_FALIED_COMMENT_NO_END;
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlComment: The comment has syntax error!");
    return OAM_XML_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlSingleEndLabel(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 将指针移到"</"后 */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* 标签名首字母不能为数字或标点符号 */
    /* 不支持双字节编码字符, 不支持命名空间, 点属性操作符等 */
    if (VOS_TRUE != OAM_XML_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlSingleEndLabel: Illegal label name!");
        return OAM_XML_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* 给节点右标签名赋值 */
    pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd = pstXmlCtxInner->pcXMLStrCurChar++;
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == OAM_XML_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == OAM_XML_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
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
        if (0 != VOS_MemCmp(pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabel,
                            pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd,
                            pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength))
        {
            return OAM_XML_RESULT_FALIED_LABEL_NAMES_NOT_SAME;
        }
    }
    else
    {
        return OAM_XML_RESULT_FALIED_BAD_END_LABEL;
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
                pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_AFTER_ROOT_NODE;
                pstXmlCtxInner->pcXMLStrCurChar++;
                return OAM_XML_RESULT_SUCCEED_ALL_ENDS;
            }
            break;
        }
        else if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlSingleEndLabel: Illegal label!");
            return OAM_XML_RESULT_FALIED_BAD_END_LABEL;
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
    pstXmlCtxInner->enXMLAnalyseStatus  = OAM_XML_PARSE_ORIGINAL;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlLabelStart(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_STRU                 *pstNewNode;
    OAM_XML_RESULT_ENUM_UINT32         enXmlRslt;

    /* 标签名首字母不能为数字或标点符号 */
    /* 不支持双字节编码字符, 不支持命名空间, 点属性操作符等 */
    if (VOS_TRUE != OAM_XML_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlLabelStart: Illegal label name!");
        return OAM_XML_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* 创建一个新节点 */
    pstNewNode  = OAM_XML_CreateANode(pstXmlCtxInner->pstXMLCtx);
    if (VOS_NULL_PTR == pstNewNode)
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlLabelStart: Create Node Error!");
        return OAM_XML_RESULT_FALIED_CREATE_NODE_ERROR;
    }

    /* 根节点为空, 意味着当前节点即根节点 */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode)
    {
        pstXmlCtxInner->pstXMLRootNode = pstNewNode;
    }

    /* 并加入到当前节点的子节点链表末端，并将当前节点指针指向这个新节点 */
    if (VOS_NULL_PTR != pstXmlCtxInner->pstXMLCurrentNode)
    {
        enXmlRslt = OAM_XML_AddAChildNode(pstXmlCtxInner->pstXMLCurrentNode,
                               pstNewNode,
                               VOS_NULL_PTR);
        if (OAM_XML_RESULT_SUCCEED != enXmlRslt)
        {
            XML_WARNING_LOG("OAM_XML_AddAChildNode: Error!");
        }
        /* 如果包含子节点, 则清空节点值 */
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue      = VOS_NULL_PTR;
        pstXmlCtxInner->pstXMLCurrentNode->ulValueLength    = 0;
    }
    pstXmlCtxInner->pstXMLCurrentNode = pstNewNode;

    /* 给节点Label赋值 */
    pstNewNode->pcNodeLabel = pstXmlCtxInner->pcXMLStrCurChar++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == OAM_XML_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == OAM_XML_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
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
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_LABEL_END_MUST_RIGHT;
    }
    /* 遇到>左标签结束 */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = pstXmlCtxInner->pcXMLStrCurChar + 1;
    }
    /* 标签名字结束, 进入属性解析状态 */
    else if (VOS_TRUE == OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_START;
    }
    else
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlLabelStart: Illegal label name!");
        return OAM_XML_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* 把这个字节放进当前节点值的缓冲区内 */
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength++;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlEndMustBeRight(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 必须是>，否则为错误格式 */
    if ('>' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlEndMustBeRight: Illegal end label!");
        return OAM_XML_RESULT_FALIED_BAD_END_LABEL;
    }

    /* 如果是根节点的结尾标签, 表明解析可以结束了 */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode->pstFather)
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_AFTER_ROOT_NODE;
        return OAM_XML_RESULT_SUCCEED_ALL_ENDS;
    }

    /* 当前节点退到父节点 */
    pstXmlCtxInner->pstXMLCurrentNode   = pstXmlCtxInner->pstXMLCurrentNode->pstFather;
    /* 变更状态 */
    pstXmlCtxInner->enXMLAnalyseStatus  = OAM_XML_PARSE_ORIGINAL;

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribStart(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 忽略Lable中的分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* 遇到尾节点标签 */
    if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_LABEL_END_MUST_RIGHT;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* 左标签结束, 回到初始状态 */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = pstXmlCtxInner->pcXMLStrCurChar + 1;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* 进入标签名解析 */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_NAME_START;
    }

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribNameStart(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstNewAttrib;

    /* 属性名首字母不能为数字或标点符号, 不支持双字节编码字符 */
    if (VOS_TRUE != OAM_XML_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameStart: Illegal attribute name!");
        return OAM_XML_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    /* 创建一个新节点, 并加入到当前节点的属性链表末端 */
    pstNewAttrib = OAM_XML_CreateAnAttribute(pstXmlCtxInner->pstXMLCtx);
    if (OAM_XML_RESULT_SUCCEED != OAM_XML_AddAnAttribute(pstXmlCtxInner->pstXMLCurrentNode,
                                                           pstNewAttrib,
                                                           VOS_NULL_PTR))
    {
        return OAM_XML_RESULT_FALIED_CREATE_ATTRIB_ERROR;
    }

    /* 给属性名赋值 */
    pstNewAttrib->pcAttribName = pstXmlCtxInner->pcXMLStrCurChar++;
    pstNewAttrib->ulNameLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == OAM_XML_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == OAM_XML_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
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
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_NAME_END;
    }
    else if (VOS_TRUE == OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_NAME_END;
    }
    else
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameStart: Illegal attribute name!");
        return OAM_XML_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribNameEnd(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 属性名结束后, 允许存在多个分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* 去掉分隔附后, 一定是'=' */
    if ('=' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameEnd: Lake of equal sign!");
        return OAM_XML_RESULT_FALIED_EXPECT_EQUAL_SIGN;
    }

    /* 等号与属性值之间允许多个分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* 去掉分隔附后, 一定是单引号或双引号 */
    if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_VALUE_SINGLE;
    }
    else if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_VALUE_DOUBLE;
    }
    else
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameEnd: Lake of quotation mark!");
        return OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK;
    }

    pstXmlCtxInner->pcXMLStrCurChar++;
    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribValueSingle(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* 给当前节点最后一个属性的属性值中 */
    pstTmpAttrib = OAM_XML_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return OAM_XML_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* 等待单引号 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* 属性值结束, 返回开始解析属性的状态 */
            pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return OAM_XML_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueSingle: Unexpect Char!");
            return OAM_XML_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueSingle: Lake of end quotation mark!");
    return OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribValueDouble(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* 给当前节点最后一个属性的属性值中 */
    pstTmpAttrib = OAM_XML_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return OAM_XML_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* 等待双引号 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* 属性值结束, 返回开始解析属性的状态 */
            pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return OAM_XML_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueDouble: Unexpect Char!");
            return OAM_XML_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueDouble: Lake of end quotation mark!");
    return OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAfterRootNode(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* 直到码流末尾都仅允许出现分隔符 */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlAfterRootNode: Unexpect charactor out of Root!");
            return OAM_XML_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    return OAM_XML_RESULT_SUCCEED_ALL_ENDS;
}


OAM_XML_RESULT_ENUM_UINT32 OAM_XML_Analyse(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;
    OAM_XML_ANALYSE_FUNC               afucXmlAnalyseFucs[] =
    {
        OAM_XML_ProcXmlOriginal,
        OAM_XML_ProcXmlEnterLabel,
        OAM_XML_ProcXmlDeclaration,
        OAM_XML_ProcXmlComment,
        OAM_XML_ProcXmlLabelStart,
        OAM_XML_ProcXmlSingleEndLabel,
        OAM_XML_ProcXmlEndMustBeRight,
        OAM_XML_ProcXmlAttribStart,
        OAM_XML_ProcXmlAttribNameStart,
        OAM_XML_ProcXmlAttribNameEnd,
        OAM_XML_ProcXmlAttribValueSingle,
        OAM_XML_ProcXmlAttribValueDouble,
        OAM_XML_ProcXmlAfterRootNode
    };

    /* 判断解析状态的合法性 */
    if (pstXmlCtxInner->enXMLAnalyseStatus >= OAM_XML_RESULT_FALIED_UNKOWN_ERROR)
    {
        XML_WARNING_LOG("OAM_XML_Analyse: Invalid Analyse Status!");
        return OAM_XML_RESULT_FALIED_ANALYSE_STATUS_ERROR;
    }

    /* 通过索引调用状态机处理函数 */
    ulReturnVal = afucXmlAnalyseFucs[pstXmlCtxInner->enXMLAnalyseStatus](pstXmlCtxInner);

    return ulReturnVal;
}


OAM_XML_RESULT_ENUM_UINT32 OAM_XML_InitXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;

    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("OAM_XML_InitXMLCtx: pstXmlCtx is VOS_NULL_PTR!");
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 初始化内存空间 */
    /*lint -e534*/
    VOS_MemSet(pstXmlCtx, 0x00, sizeof(OAM_XML_CTX_STRU));
    /*lint +e534*/
    ulReturnVal = OAM_XML_InitMemory(pstXmlCtx);

    return ulReturnVal;
}


OAM_XML_NODE_STRU* OAM_XML_BuildXMLTree(
    VOS_CHAR                           *pcXmlStr,
    OAM_XML_CTX_STRU                  *pstXmlCtx)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;
    OAM_XML_CTX_INNER_STRU             stXmlCtxInner;
    VOS_UINT32                          ulStrLen;

    /* 参数合法性检查 */
    if ((VOS_NULL_PTR == pcXmlStr) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("OAM_XML_BuildXMLTree: pcXmlStr or pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* 对解析的XML码流的长度进行约束 */
    ulStrLen = VOS_StrLen(pcXmlStr);
    if ( (0 == ulStrLen)
      || (ulStrLen > OAM_XML_MAX_STR_LEN) )
    {
        XML_WARNING_LOG("OAM_XML_BuildXMLTree: pcXmlStr Length Error!");
        return VOS_NULL_PTR;
    }

    /* 初始化内存管理 */
    ulReturnVal = OAM_XML_InitMemory(pstXmlCtx);
    if (OAM_XML_RESULT_SUCCEED != ulReturnVal)
    {
        return VOS_NULL_PTR;
    }

    stXmlCtxInner.pstXMLCtx             = pstXmlCtx;
    stXmlCtxInner.pstXMLRootNode        = VOS_NULL_PTR;
    stXmlCtxInner.pstXMLCurrentNode     = VOS_NULL_PTR;
    stXmlCtxInner.pcXMLStrCurChar       = pcXmlStr;
    stXmlCtxInner.enXMLAnalyseStatus    = OAM_XML_PARSE_ORIGINAL;

    /* 遍历XML格式码流，解析为XML树结构 */
    while ('\0' != *(stXmlCtxInner.pcXMLStrCurChar))
    {
        ulReturnVal = OAM_XML_Analyse(&stXmlCtxInner);

        /* 处理失败直接中断循环返回 */
        if ( (OAM_XML_RESULT_SUCCEED != ulReturnVal)
          && (OAM_XML_RESULT_SUCCEED_ALL_ENDS != ulReturnVal) )
        {
            break;
        }
    }

    /* 解析正常完成，返回XML树结构根节点 */
    if (OAM_XML_RESULT_SUCCEED_ALL_ENDS == ulReturnVal)
    {
        return stXmlCtxInner.pstXMLRootNode;
    }

    /* 解析异常, 释放上下文中分配的内存, 返回空指针 */
    XML_WARNING1_LOG("OAM_XML_BuildXMLTree: Xml Analyse Failure, Error Code: ", ulReturnVal);
    (VOS_VOID)OAM_XML_ClearXMLCtx(pstXmlCtx);
    return VOS_NULL_PTR;
}


OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ClearXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx)
{
    /* 参数合法性检查 */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* 释放上下文中占用的内存 */
    if (VOS_NULL_PTR != pstXmlCtx->pucXMLBuffer)
    {
        /*lint -e534*/
        VOS_MemFree(MAPS_PIH_PID, pstXmlCtx->pucXMLBuffer);
        /*lint +e534*/
    }

    /*lint -e534*/
    VOS_MemSet(pstXmlCtx, 0x00, sizeof(OAM_XML_CTX_STRU));
    /*lint +e534*/
    return OAM_XML_RESULT_SUCCEED;
}


VOS_VOID OAM_XML_GetStrContent(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32      i;
    VOS_UINT32      ulCharLen = 0;

    for(i=0; i<ulSrcLen; i++)
    {
        if((pcSrc[i] >= 'a')&&(pcSrc[i] <= 'z'))
        {
            pcDst[ulCharLen] = pcSrc[i]- ('a'-'A');
            ulCharLen++;
        }
        else if((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'Z'))
        {
            pcDst[ulCharLen] = pcSrc[i];
            ulCharLen++;
        }
        else if((pcSrc[i] >= '0')&&(pcSrc[i] <= '9'))
        {
            pcDst[ulCharLen] = pcSrc[i];
            ulCharLen++;
        }
        else
        {
        }

    }

    *pulDstLen = ulCharLen;

    return;
}



VOS_VOID OAM_XML_FilterStrInvalidChar(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32      i;
    VOS_UINT32      ulCharLen = 0;

    for(i=0; i<ulSrcLen; i++)
    {
        if( ((pcSrc[i] >= 'a')&&(pcSrc[i] <= 'z'))
          || ((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'Z'))
          || ((pcSrc[i] >= '0')&&(pcSrc[i] <= '9')) )
        {
            pcDst[ulCharLen] = pcSrc[i];
            ulCharLen++;
        }
        else
        {
        }

    }

    *pulDstLen = ulCharLen;

    return;
}



VOS_UINT32 OAM_XML_GetIntArray(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32      i;
    VOS_UINT32      j = 0;
    VOS_UINT32      ulLen = 0;
    VOS_CHAR        acTemp[2];

    for(i=0; i<ulSrcLen; i++)
    {
        if((pcSrc[i] >= '0')&&(pcSrc[i] <= '9'))            /*转换数字字符*/
        {
            acTemp[j] = pcSrc[i] - '0';

            j++;
        }
        else if((pcSrc[i] >= 'a')&&(pcSrc[i+j] <= 'f'))     /*转换小写字符*/
        {
            acTemp[j] = (pcSrc[i] - 'a') + 10;              /*字符相减后加上差值恢复*/

            j++;
        }
        else if((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'F'))       /*转换大写字符*/
        {
            acTemp[j] = (pcSrc[i] - 'A') + 10;

            j++;
        }
        else if((pcSrc[i] == '\r')||(pcSrc[i] == '\n')||(pcSrc[i] == '\t')||(pcSrc[i] == ' '))    /*跳过特殊字符*/
        {
            continue;
        }
        else                                                /*不能转换和跳过的字符*/
        {
            XML_WARNING1_LOG("OAM_XML_GetIntArray: Get Non Ascii Char ", pcSrc[i]);

            return VOS_ERR;
        }

        if (2 == j)                                         /*已经凑够两个字符*/
        {
            pucDst[ulLen] = (VOS_UINT8)(((VOS_UINT8)acTemp[0]<<4)+acTemp[1]);

            ulLen++;

            j = 0;
        }
    }

    if(1 == j)                                              /*转换的字符串为奇数*/
    {
        XML_WARNING1_LOG("OAM_XML_GetIntArray: The Str Len is Odd ", ulSrcLen);

        return VOS_ERR;
    }

    *pulDstLen = ulLen;

    return VOS_OK;
}


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_SearchAttNodeByName(
                                    OAM_XML_NODE_ATTRIBUTE_STRU *pstFirstAttrNode,
                                    VOS_CHAR                    *pcAttribName)
{
    OAM_XML_NODE_ATTRIBUTE_STRU *pstAttr;
    VOS_CHAR                    *pcNameData;
    VOS_UINT32                  ulStrLen;
    VOS_INT                     lResult;

    if(VOS_NULL_PTR == pstFirstAttrNode)
    {
        XML_WARNING_LOG("OAM_XML_SearchAttributeNoteByName: The pstFirstAttrNode is NULL ");

        return VOS_NULL_PTR;
    }

    pstAttr = pstFirstAttrNode;

    while(VOS_NULL_PTR != pstAttr)
    {
        /*当前节点属性名称或者节点值不存在，继续搜索*/
        if ((VOS_NULL_PTR == pstAttr->pcAttribName)
            ||(VOS_NULL_PTR == pstAttr->pcAttribValue)
            ||(0 == pstAttr->ulNameLength)
            ||(0 == pstAttr->ulValueLength))
        {
            pstAttr = pstAttr->pstNexBrother;

            continue;
        }

        pcNameData = (VOS_CHAR *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstAttr->ulNameLength);

        if(VOS_NULL_PTR == pcNameData)
        {
            XML_WARNING_LOG("OAM_XML_SearchAttributeNoteByName: The VOS_MemAlloc is NULL ");

            return VOS_NULL_PTR;
        }

        /*节点名字字符过滤*/
        OAM_XML_GetStrContent(pstAttr->pcAttribName, pstAttr->ulNameLength, pcNameData, &ulStrLen);

/*lint -e418*/
        lResult = VOS_MemCmp(pcAttribName, pcNameData, ulStrLen);
/*lint +e418*/

        /*释放节点名称内存*/
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcNameData);
        /*lint +e534*/

        if(VOS_OK == lResult)
        {
            return pstAttr;
        }

        /*指向下一个属性节点*/
        pstAttr = pstAttr->pstNexBrother;
    }

    XML_WARNING_LOG("OAM_XML_SearchAttributeNoteByName: Could Not Find Node ");

    return VOS_NULL_PTR;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

