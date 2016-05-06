/******************************************************************************

版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名      : XMLDecode.h
版 本 号      : 初稿
作    者      : 郑继树 176513
生成日期      : 2010年12月20日
最近修改      :
功能描述      : 该头文件为XML相关操作头文件
函数列表      :
修改历史      :
1.日    期    : 2010年12月20日
作    者    : 郑继树 176513
修改内容    : 创建文件

******************************************************************************/

#ifndef _XML_DEOCDE_H_
#define _XML_DEOCDE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
1 其他头文件包含
*****************************************************************************/
#include "comm_adapter.h"

/*****************************************************************************
2 宏定义
*****************************************************************************/
#define  XML_FILE_READ_BUFF_SIZE              (4096)  /* 读文件缓冲区大小         */
#define  XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL  (128)   /* 节点标签缓冲区大小       */
#define  XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL  (32768) /* 节点值缓冲区大小         */
#define  XML_MAX_HARDWARE_LEN                 (32)    /* 单板Product Id的最大长度 */

/* MAP文件头部文件标识符 */
#define  XML_MAP_FILE_MAGIC_NUM               (0x13579BDE)
#define  XML_CHECK_BUFF_SIZE                  (32*1024) /* 用于计算xml校验的buff大小 */

/* MAP文件中MD5 HASH值长度 */
#define  XML_MAP_MD5_HASH_LEN                 (16)

/* xnv.xml的最大大小 */
#define  XML_MAX_FILE_SIZE                    (64*1024*1024)

#if 1
#ifndef XML_CHECK_MD5
#define XML_CHECK_MD5
#endif
#else
#ifdef XML_CHECK_MD5
#undef XML_CHECK_MD5
#endif
#endif

/*****************************************************************************
3 枚举定义
*****************************************************************************/

/*****************************************************************************
枚举名    : XML_RESULT_ENUM_UINT32
协议表格  :
ASN.1描述 :
枚举说明  : XML函数的运行状态返回值
*****************************************************************************/
enum XML_RESULT_ENUM
{
    XML_RESULT_SUCCEED                        = 0 , /* 成功                      */
    XML_RESULT_SUCCEED_IGNORE_CHAR                , /* 可以忽略的字符\r\n\t      */
    XML_RESULT_FALIED_PARA_POINTER                , /* 错误的参数指针            */
    XML_RESULT_FALIED_MALLOC                      , /* 内存申请失败              */
    XML_RESULT_FALIED_BAD_SYNTAX                  , /* 错误的XML语法             */
    XML_RESULT_FALIED_BAD_CHAR                    , /* 错误的字符                */
    XML_RESULT_FALIED_READ_FILE                   , /* 读取文件失败              */
    XML_RESULT_FALIED_WRITE_NV                    , /* 写NV Value出错            */
    XML_RESULT_FALIED_OUT_OF_BUFF_LEN             , /* 超出缓冲区长度            */
    XML_RESULT_FALIED_OUT_OF_MAX_VALUE            , /* 超出NV ID的最大值         */
    XML_RESULT_FALIED_OUT_OF_0_9                  , /* NV ID值不在0-9            */
    XML_RESULT_FALIED_OUT_OF_0_F                  , /* NV Value值不在0-F         */
    XML_RESULT_FALIED_OUT_OF_2_CHAR               , /* NV Value值超过1Byte       */
    XML_RESULT_FALIED_NV_ID_IS_NULL               , /* NV ID值为空               */
    XML_RESULT_FALIED_NV_VALUE_IS_NULL            , /* NV Value值为空            */
    XML_RESULT_FALIED_PRODUCT_MATCH               , /* <product>结束标签没有匹配 */
    XML_RESULT_NOT_NEED_DECODE_XML                , /* XML 不需要解析 */
    XML_RESULT_FALIED_FILE_OPERATE                , /* XML 文件操作失败 */
    XML_RESULT_FALIED_NV_READ                     , /* NV读失败 */
    XML_RESULT_FALIED_BAD_MAGIC_NUM               , /* MAP文件标识符错误 */
    XML_RESULT_FALIED_PRODUCT_NUM                 , /* MAP头中产品个数错误 */
    XML_RESULT_FALIED_BAD_FILE                    , /* XML文件校验失败 */
    XML_RESULT_FALIED_SEEK_FILE                   , /* MAP文件指针跳转失败 */
    XML_RESULT_FALIED_GET_PRODUCTID               , /* 获取产品id失败 */
    XML_RESULT_FALIED_GET_PRODUCT_OFFSET          , /* 获取产品偏移失败 */
    XML_RESULT_FALIED_FILE_TOO_BIG                , /* XML文件校验失败 */
    XML_RESULT_FALIED_OPEN_FILE                   , /* 读取文件失败              */
    XML_RESULT_BUTT
};
typedef VOS_UINT32 XML_RESULT_ENUM_UINT32;

/*****************************************************************************
枚举名    : XML_RESULT_ENUM_UINT32
协议表格  :
ASN.1描述 :
枚举说明  : XML函数的状态
*****************************************************************************/
enum XML_ANALYSE_STATUS_ENUM
{
    XML_ANASTT_ORIGINAL                       = 0 , /* 初始                 */
    XML_ANASTT_ENTER_LABLE                        , /* 进入标签             */
    XML_ANASTT_IGNORE                             , /* 序言或注释           */
    XML_ANASTT_NODE_LABLE                         , /* 解析标签名           */
    XML_ANASTT_SINGLE_ENDS_LABLE                  , /* 独立结尾标签         */
    XML_ANASTT_LABLE_END_MUST_RIGHT               , /* 标签开始即收尾       */
    XML_ANASTT_PROPERTY_START                     , /* 开始解析属性         */
    XML_ANASTT_PROPERTY_NAME_START                , /* 开始解析属性名称     */
    XML_ANASTT_PROPERTY_NAME_END                  , /* 属性名称结束，等待"  */
    XML_ANASTT_PROPERTY_VALUE_START               , /* "结束，等待="        */
    XML_ANASTT_PROPERTY_VALUE_END                 , /* 属性值结束，等待>    */
    XML_ANASTT_BUTT
};
typedef VOS_UINT32 XML_ANALYSE_STATUS_ENUM_UINT32;
typedef VOS_UINT32 (*XML_FUN)(VOS_CHAR cNowChar);

/*****************************************************************************
枚举名    : XML_PRODUCT_NODE_STATUS_ENUM_UINT32
协议表格  :
ASN.1描述 :
枚举说明  : 用于解析xnv.xml文件时，记录product节点下各子节点节点是否有效
*****************************************************************************/
enum XML_PRODUCT_STATUS_ENUM
{
    XML_PRODUCT_NODE_STATUS_INVALID           = 0 , /* Product节点对应的ID是有效的 */
    XML_PRODUCT_NODE_STATUS_VALID                 , /* Product节点对应的ID是无效的 */
    XML_PRODUCT_NODE_BUTT
};
typedef VOS_UINT32 XML_PRODUCT_STATUS_ENUM_UINT32;

/*****************************************************************************
枚举名    : XML_DECODE_STATE_ENUM_UINT32
协议表格  :
ASN.1描述 :
枚举说明  : 用于解析xnv.xml文件时，记录当前XML文件是否解析完成
*****************************************************************************/
enum XML_DECODE_STATUS_ENUM
{
    XML_DECODE_STATUS_DECODING                = 0 , /* 当前XML文件解析中   */
    XML_DECODE_STATUS_FINISHED                    , /* 当前XML文件解析完成 */
    XML_DECODE_BUTT
};
typedef VOS_UINT32 XML_DECODE_STATE_ENUM_UINT32;

/*****************************************************************************
枚举名    : XML_PRODUCT_DECODE_STATUS_ENUM
协议表格  :
ASN.1描述 :
枚举说明  : 用于解析xnv.xml文件时，记录当前XML文件是否解析完成
*****************************************************************************/
enum XML_PRODUCT_DECODE_STATUS_ENUM
{
    XML_PRODUCT_ANALYZE_START                 = 0 , /* 初始状态 */
    XML_PRODUCT_COMMON_ANALYZE_FINISH             , /* common nv解析完成 */
    XML_PRODUCT_CAT_ANALYZE_START                 , /* product cat公共nv解析开始 */
    XML_PRODUCT_CAT_ANALYZE_FINISH                , /* product cat公共nv解析完成 */
    XML_PRODUCT_ID_ANALYZE_START                  , /* 产品私有nv解析开始 */
    XML_PRODUCT_ID_ANALYZE_FINISH                 , /* 产品私有nv解析完成 */
    XML_PRODUCT_BUTT
};

typedef VOS_UINT32 XML_PRODUCT_DECODE_STATUS_ENUM_UINT32;

/*****************************************************************************
4 UNION定义
*****************************************************************************/

/*****************************************************************************
5 STRUCT定义
*****************************************************************************/

/*****************************************************************************
结构名    : XML_PATH_STRU
协议表格  :
ASN.1描述 :
结构说明  : XML路径配置结构
*****************************************************************************/
typedef struct
{
    VOS_CHAR    *pcXNVPath;
    VOS_CHAR    *pcCUSTPath;
}XML_PATH_STRU;

/*****************************************************************************
结构名    : XML_MAP_PATH_STRU
协议表格  :
ASN.1描述 :
结构说明  : XML路径配置结构
*****************************************************************************/
typedef struct
{
    VOS_CHAR    *pcMapPath;
}XML_MAP_PATH_STRU;

/*****************************************************************************
结构名    : XML_NODE_PROPERTY
协议表格  :
ASN.1描述 :
结构说明  : 节点属性链表的单元
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulNameLength;                  /* pcPropertyName 缓冲区长度  */
    VOS_UINT32 ulValueLength;                 /* pcPropertyValue 缓冲区长度 */
    VOS_CHAR* pcPropertyName;                 /* 属性名称                   */
    VOS_CHAR* pcPropertyValue;                /* 属性值                     */
}XML_NODE_PROPERTY_STRU;


/*****************************************************************************
结构名    : XML_NODE_STRU
协议表格  :
ASN.1描述 :
结构说明  : XML树的节点
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulLabelLength;                 /* pcNodeLabel 缓冲区长度    */
    VOS_UINT32 ulLabelEndLength;              /* pcNodeLabelEnd 缓冲区长度 */
    VOS_UINT32 ulValueLength;                 /* pcNodeValue 缓冲区长度    */
    VOS_CHAR*  pcNodeLabel;                   /* 节点标签                  */
    VOS_CHAR*  pcNodeLabelEnd;                /* 结尾独立标签              */
    VOS_CHAR*  pcNodeValue;                   /* 节点值                    */
    XML_NODE_PROPERTY_STRU stProperty;        /* 属性                      */
}XML_NODE_STRU;

/*****************************************************************************
结构名    : XML_PRODUCT_STRU
协议表格  :
ASN.1描述 :
结构说明  : 用于记录PRODUCT节点信息
*****************************************************************************/
typedef struct
{
    /* 记录product节点下各子节点节点是否有效    */
    XML_PRODUCT_STATUS_ENUM_UINT32 enValidNode;
    /* 判断XML解析是否完成                      */
    XML_DECODE_STATE_ENUM_UINT32   enXMLDecodeState;
    /* 有效的Product节点及其子product节点的个数 */
    VOS_UINT32                     ulNodeLevel;
    /* 记录当前单板的product id                 */
    VOS_CHAR                       acProductId[XML_MAX_HARDWARE_LEN];
}XML_PRODUCT_STRU;

/*****************************************************************************
结构名    : XML_ERROR_INFO_STRU
协议表格  :
ASN.1描述 :
结构说明  : 用于记录XML错误信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulXMLLine;      /* XML对应的行号      */
    VOS_UINT32 ulStatus;       /* XML对应的解析状态  */
    VOS_UINT32 ulCodeLine;     /* 出错代码对应的行号 */
    VOS_UINT16 usNvId;         /* NV ID的值          */
    VOS_UINT16 usReserve;      /* NV ID的值          */
    VOS_UINT32 ulResult;       /* 返回的结果         */
} XML_ERROR_INFO_STRU;

/*****************************************************************************
结构名    : XML_XNV_MAP_HEAD_STRU
协议表格  :
ASN.1描述 :
结构说明  : 索引文件头部信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulMagNumber;      /* 文件标识码 0x13579BDE */
    VOS_UINT32  ulProductNum;     /* 产品个数 */
    VOS_UINT32  aulXnvMD5[4];     /* 对应xnv xml文件的128 bit MD5校验 */
} XML_XNV_MAP_HEAD_STRU;

/*****************************************************************************
结构名    : XML_XNV_PRDT_OFFSET_STRU
协议表格  :
ASN.1描述 :
结构说明  : 索引文件数据部分结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulPrdtID;          /* product ID */
    VOS_UINT32  ulCatNodeOffset;   /* product ID所属product_NvInfo在文件中的偏移 */
    VOS_UINT32  ulPrdtNodeOffset;  /* product ID节点在文件中的偏移 */
} XML_XNV_PRDT_OFFSET_STRU;

/*****************************************************************************
6 消息头定义
*****************************************************************************/


/*****************************************************************************
7 消息定义
*****************************************************************************/


/*****************************************************************************
8 全局变量声明
*****************************************************************************/


/*****************************************************************************
9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
10 函数声明
*****************************************************************************/
extern XML_RESULT_ENUM_UINT32 XML_WriteNVItem(VOS_VOID);

extern XML_RESULT_ENUM_UINT32 XML_StringToNvId(VOS_CHAR  *pcBuff,
                                        VOS_UINT16 *pusRetVal);

extern XML_RESULT_ENUM_UINT32 XML_StringToNvValue(VOS_UINT8  *pucBuff,
                                             VOS_UINT8  *pucRetBuff,
                                             VOS_UINT32 *pulRetBuffLen);

extern VOS_VOID XML_WriteErrorLog(VOS_UINT32 ulErrLine, VOS_UINT16 ulNvId,
                            VOS_UINT32 ulResult);

extern XML_RESULT_ENUM_UINT32 XML_ProcInit(VOS_VOID);

extern XML_RESULT_ENUM_UINT32 XML_DecodeXMLFile(FILE* pfFile);

extern VOS_VOID XML_FreeMem(VOS_VOID);

extern VOS_VOID XML_InitGlobal(VOS_VOID);

extern VOS_VOID XML_DecodeMain(VOS_BOOL *pbIsDecodeXml);

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

#endif /* _XML_H_ */
