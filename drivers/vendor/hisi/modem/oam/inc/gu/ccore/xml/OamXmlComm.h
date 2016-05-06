/******************************************************************************

版权所有 (C), 2001-2012, 华为技术有限公司

******************************************************************************
文 件 名      : OamXmlComm.h
版 本 号      : 初稿
作    者      : 朱凯 00208519
生成日期      : 2013年3月16日
最近修改      :
功能描述      : 该头文件为XML相关操作头文件
                在使用前需要先定义一个OAM_XML_CTX_STRU结构XML API上下文,
                并调用接口函数OAM_XML_InitXMLCtx对上下文初始化, 使用后必须
                调用接口函数OAM_XML_ClearXMLCtx对上下文进行进行清理。
函数列表      :
修改历史      :
1.日    期    : 2013年3月16日
  作    者    : 朱凯 00208519
  修改内容    : 创建文件

******************************************************************************/

#ifndef _OAM_XML_COMM_H_
#define _OAM_XML_COMM_H_

/*****************************************************************************
1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "pamom.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
2 宏定义
*****************************************************************************/
#define OAM_XML_MAX_LEVEL                      (10)                /* 支持的XML最大层数    */
#define OAM_XML_BUFF_SIZE                      (8000)              /* XML上下文内存长度    */
#define OAM_XML_MAX_STACK_DEPTH                (100)               /* 目前定义栈深度为100  */
#define OAM_XML_MAX_NUM_LEN                    (11)                /* 有符整型数字最大长度 */
#define OAM_XML_INDENTATION_SPACE_NUM          (4)                 /* 缩进空格个数         */
#define OAM_XML_ATTRIB_PUNCTUATION_LEN         (4)                 /* 属性值中包含的字符数 */
#define OAM_XML_CRLF_LEN                       (2)                 /* 回车换行符的长度     */
#define OAM_XML_LABEL_START_LEN                (1)                 /* 标签起始符"<"长度    */
#define OAM_XML_LABEL_END_LEN                  (1)                 /* 标签结束符">"长度    */
#define OAM_XML_SINGLE_LABLE_END_LEN           (2)                 /* 单标签结束符"/>"长度 */
#define OAM_XML_END_LABEL_START_LEN            (2)                 /* 右标签起始符"</"长度 */
#define OAM_XML_MAX_STR_LEN                    (10240)             /* 解析XML码流最大长度  */
/* XML码流版本信息字符串 */
#define OAM_XML_VERSION_STR                     "<?xml version=\"1.0\" encoding=\"utf-8\"?>"

#if (VOS_WIN32 == VOS_OS_VER)
#define XML_WARNING_LOG(string)                 vos_printf("%s \r\n", string)
#define XML_WARNING1_LOG(string, para1)         vos_printf("%s %d.\r\n", string, para1)
#define XML_WARNING2_LOG(string, para1, para2)  vos_printf("%s %d, %d.\r\n", string, para1, para2)
#define XML_ERROR_LOG(string)                   vos_printf("%s \r\n", string)
#define XML_ERROR1_LOG(string, para1)           vos_printf("%s %d.\r\n", string, para1)
#define XML_ERROR2_LOG(string, para1, para2)    vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define XML_WARNING_LOG(string)                 PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_WARNING,  string)
#define XML_WARNING1_LOG(string, para1)         PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_WARNING,  string, (VOS_INT32)para1)
#define XML_WARNING2_LOG(string, para1, para2)  PS_LOG2(WUEPS_PID_USIM, 0, PS_PRINT_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#define XML_ERROR_LOG(string)                   PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,  string)
#define XML_ERROR1_LOG(string, para1)           PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,  string, (VOS_INT32)para1)
#define XML_ERROR2_LOG(string, para1, para2)    PS_LOG2(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

/*****************************************************************************
3 枚举定义
*****************************************************************************/

/*****************************************************************************
枚举名    : OAM_XML_RESULT_ENUM_UINT32
枚举说明  : XML函数的运行状态返回值
1.日    期  : 2013年3月16日
  作    者  : 朱凯 00208519
  修改内容  : 新建枚举
*****************************************************************************/
enum OAM_XML_RESULT_ENUM
{
    OAM_XML_RESULT_SUCCEED                         = 0 ,   /* 成功                 */

    /* XML格式码流解析过程中的结果码 */
    OAM_XML_RESULT_SUCCEED_ALL_ENDS                    ,   /* 解析结束             */
    OAM_XML_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT        ,   /* 根节点外存在非法字符 */
    OAM_XML_RESULT_FALIED_DECLARATION_NO_END           ,   /* XML声明未正确结束    */
    OAM_XML_RESULT_FALIED_COMMENT_NO_END               ,   /* 注释未正确结束       */
    OAM_XML_RESULT_FALIED_COMMENT_SYNTAX_ERROR         ,   /* 注释语法错误         */
    OAM_XML_RESULT_FALIED_LABEL_NAMES_NOT_SAME         ,   /* 左右标签名不匹配     */
    OAM_XML_RESULT_FALIED_BAD_LABEL_NAME               ,   /* 标签名非法           */
    OAM_XML_RESULT_FALIED_BAD_END_LABEL                ,   /* 错误的收尾标签       */
    OAM_XML_RESULT_FALIED_BAD_ATTRIB_NAME              ,   /* 属性名非法           */
    OAM_XML_RESULT_FALIED_CREATE_NODE_ERROR            ,   /* 创建节点错误         */
    OAM_XML_RESULT_FALIED_CREATE_ATTRIB_ERROR          ,   /* 创建属性错误         */
    OAM_XML_RESULT_FALIED_EXPECT_EQUAL_SIGN            ,   /* 属性名后找不到等号   */
    OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK            ,   /* 缺少属性值的引号     */
    OAM_XML_RESULT_FALIED_CHAR_UNEXPECT                ,   /* 遇到非法字符         */
    OAM_XML_RESULT_FALIED_ANALYSE_STATUS_ERROR         ,   /* 非法的解析状态       */

    /* 提供公共调用接口返回的错误码 */
    OAM_XML_RESULT_FAILED_ATTRIB_NOT_FOUND             ,   /* 没找到指定的属性     */
    OAM_XML_RESULT_FAILED_NODE_NOT_FOUND               ,   /* 没找到指定的节点     */
    OAM_XML_RESULT_FAILED_CANT_UNLOAD_ROOT_NODE        ,   /* 根节点不予拆除       */
    OAM_XML_RESULT_FALIED_PARA_NULL_POINTER            ,   /* 参数空指针           */
    OAM_XML_RESULT_FALIED_MEM_NOT_ENOUGH               ,   /* 内存不足             */
    OAM_XML_RESULT_FALIED_MALLOC                       ,   /* 内存申请失败         */

    OAM_XML_RESULT_BUTT
};
typedef VOS_UINT32 OAM_XML_RESULT_ENUM_UINT32;


/*****************************************************************************
枚举名    : OAM_XML_ANALYSE_STATUS_ENUM_UINT32
枚举说明  : XML解析的状态
1.日    期  : 2013年3月16日
  作    者  : 朱凯 00208519
  修改内容  : 新建枚举
*****************************************************************************/
enum OAM_XML_ANALYSE_STATUS_ENUM
{
    OAM_XML_PARSE_ORIGINAL                     = 0 , /* 初始状态               */
    OAM_XML_PARSE_ENTER_LABEL                      , /* 进入标签               */
    OAM_XML_PARSE_DECLARATION                      , /* XML声明                */
    OAM_XML_PARSE_COMMENT                          , /* 注释状态               */
    OAM_XML_PARSE_NODE_LABEL_START                 , /* 解析标签名             */
    OAM_XML_PARSE_SINGLE_ENDS_LABEL                , /* 独立结尾标签           */
    OAM_XML_PARSE_LABEL_END_MUST_RIGHT             , /* 标签开始即收尾         */
    OAM_XML_PARSE_ATTRIB_START                     , /* 开始解析属性           */
    OAM_XML_PARSE_ATTRIB_NAME_START                , /* 开始解析属性名称       */
    OAM_XML_PARSE_ATTRIB_NAME_END                  , /* 属性名称结束，等待引号 */
    OAM_XML_PARSE_ATTRIB_VALUE_SINGLE              , /* 以单引号结束的属性值   */
    OAM_XML_PARSE_ATTRIB_VALUE_DOUBLE              , /* 以双引号结束的属性值   */
    OAM_XML_PARSE_AFTER_ROOT_NODE                  , /* 根节点结束后           */
    OAM_XML_RESULT_FALIED_UNKOWN_ERROR             , /* 未知错误 */
    OAM_XML_PARSE_BUTT
};
typedef VOS_UINT32 OAM_XML_ANALYSE_STATUS_ENUM_UINT32;

/*****************************************************************************
枚举名    : OAM_XML_FORMATTING_ENUM_UINT32
枚举说明  : XML输出格式
1.日    期  : 2013年3月16日
  作    者  : 朱凯 00208519
  修改内容  : 新建枚举
*****************************************************************************/
enum OAM_XML_FORMATTING_ENUM
{
    XML_FORMATTING_NONE                 = 0 , /* 无格式, 即紧凑格式  */
    XML_FORMATTING_INDENTED                 , /* 换行缩进格式        */
    XML_FORMATTING_BUTT
};
typedef VOS_UINT8 OAM_XML_FORMATTING_ENUM_UINT8;


/*****************************************************************************
4 UNION定义
*****************************************************************************/


/*****************************************************************************
5 OTHERS定义
*****************************************************************************/


/*****************************************************************************
6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
结构名    : OAM_XML_NODE_ATTRIBUTE_STRU
结构说明  : 节点属性链表的单元
1.日    期  : 2013年3月16日
  作    者  : 朱凯 00208519
  修改内容  : 新建结构
*****************************************************************************/
typedef struct OAM_XML_NODE_ATTRIBUTE
{
    /* 属性双向链表 */
    struct OAM_XML_NODE_ATTRIBUTE     *pstPreBrother;              /* 哥哥属性                 */
    struct OAM_XML_NODE_ATTRIBUTE     *pstNexBrother;              /* 弟弟属性                 */

    /* 属性主体 */
    VOS_CHAR                           *pcAttribName;               /* 属性名称                 */
    VOS_CHAR                           *pcAttribValue;              /* 属性值                   */

    VOS_UINT32                          ulNameLength;               /* pcAttribName  缓冲区长度 */
    VOS_UINT32                          ulValueLength;              /* pcAttribValue 缓冲区长度 */

}OAM_XML_NODE_ATTRIBUTE_STRU;

/*****************************************************************************
结构名    : OAM_XML_NODE_STRU
结构说明  : XML树的节点
1.日    期  : 2013年3月16日
  作    者  : 朱凯 00208519
  修改内容  : 新建结构
*****************************************************************************/
typedef struct OAM_XML_NODE
{
    /* 树形结构连接点 */
    struct OAM_XML_NODE               *pstFather;                  /* 父节点                    */
    struct OAM_XML_NODE               *pstPreBrother;              /* 哥哥节点                  */
    struct OAM_XML_NODE               *pstNexBrother;              /* 弟弟节点                  */
    struct OAM_XML_NODE               *pstFirstChild;              /* 大儿子节点                */

    /* 本节点属性链表 */
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstFirstAttrib;             /* 第一个属性                */

    /* 节点主体 */
    VOS_CHAR                           *pcNodeLabel;                /* 节点标签                  */
    VOS_CHAR                           *pcNodeLabelEnd;             /* 结尾独立标签              */
    VOS_CHAR                           *pcNodeValue;                /* 节点值                    */

    VOS_UINT32                          ulLabelLength;              /* pcNodeLabel    缓冲区长度 */
    VOS_UINT32                          ulLabelEndLength;           /* pcNodeLabelEnd 缓冲区长度 */
    VOS_UINT32                          ulValueLength;              /* pcNodeValue    缓冲区长度 */

}OAM_XML_NODE_STRU;

/*****************************************************************************
结构名    : OAM_XML_CTX
结构说明  : XML API调用者提供的上下文
1.日    期  : 2013年3月16日
  作    者  : 朱凯 00208519
  修改内容  : 新建结构
*****************************************************************************/
typedef struct OAM_XML_CTX
{
    VOS_UINT8                          *pucXMLBuffer;               /* 节点、属性内存区首地址    */
    VOS_UINT8                          *pucXMLBuffCur;              /* 内存区当前分配地址        */
    VOS_UINT32                          ulXMLBuffSize;              /* 内存区大小                */
}OAM_XML_CTX_STRU;

/*****************************************************************************
结构名    : OAM_XML_CTX_INNER_STRU
结构说明  : XML API内部内存管理、码流解析时的上下文
1.日    期  : 2013年3月16日
  作    者  : 朱凯 00208519
  修改内容  : 新建结构
*****************************************************************************/
typedef struct OAM_XML_CTX_INNER
{
    OAM_XML_CTX_STRU                  *pstXMLCtx;                  /* 调用者提供的上下文        */
    OAM_XML_NODE_STRU                 *pstXMLRootNode;             /* 根节点                    */
    OAM_XML_NODE_STRU                 *pstXMLCurrentNode;          /* 当前节点                  */
    VOS_CHAR                           *pcXMLStrCurChar;            /* 当前解析字符              */
    OAM_XML_ANALYSE_STATUS_ENUM_UINT32 enXMLAnalyseStatus;         /* 当前解析状态              */
}OAM_XML_CTX_INNER_STRU;

/*****************************************************************************
7 消息头定义
*****************************************************************************/


/*****************************************************************************
8 消息定义
*****************************************************************************/


/*****************************************************************************
9 全局变量声明
*****************************************************************************/


/*****************************************************************************
10 函数声明
*****************************************************************************/

/* 取得某节点子节点数量 */
VOS_INT32 OAM_XML_GetChildCount(OAM_XML_NODE_STRU *pstNode);

/* 按照索引取得某节点子节点, 索引从0开始 */
OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lChildIndex);

/* 按照标签名字取得某节点子节点 */
OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByLabel(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabel);

/* 根据属性值取得某节点子节点 */
OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByAttributeValue(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribValue);

/* 取得某节点属性数量 */
VOS_INT32 OAM_XML_GetAttributeCount(OAM_XML_NODE_STRU *pstNode);

/* 按照索引取得某节点属性值, 索引从0开 */
OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lAttribIndex);

/* 按照属性名取得某节点属性 */
OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByAttributeName(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribName);

/* 初始化XML API上下文 */
OAM_XML_RESULT_ENUM_UINT32 OAM_XML_InitXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx);

/* 传入带解析的XML格式码流首地址，XML上下文，输出XML树的根节点 */
OAM_XML_NODE_STRU* OAM_XML_BuildXMLTree(
    VOS_CHAR                           *pcXmlStr,
    OAM_XML_CTX_STRU                  *pstXmlCtx);

/* 清理XML上下文 */
OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ClearXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx);

/* 获取字符串内容 */
VOS_VOID OAM_XML_GetStrContent(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen);

VOS_VOID OAM_XML_FilterStrInvalidChar(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen);

/* 转换字符串为Ascii */
VOS_UINT32 OAM_XML_GetIntArray(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen);

OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_SearchAttNodeByName(
                                    OAM_XML_NODE_ATTRIBUTE_STRU *pstFirstAttrNode,
                                    VOS_CHAR                    *pcAttribName);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
    #pragma pack()
#else
    #pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* _OAM_XML_COMM_H_ */

