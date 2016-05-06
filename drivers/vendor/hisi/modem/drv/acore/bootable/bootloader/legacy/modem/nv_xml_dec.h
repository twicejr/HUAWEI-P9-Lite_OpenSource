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

#ifndef _NV_XML_DEC_H_
#define _NV_XML_DEC_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
1 其他头文件包含
*****************************************************************************/
#include <types.h>
#include "bsp_nvim.h"
#include "nv_file.h"
#include "nv_boot.h"
/*****************************************************************************
2 宏定义
*****************************************************************************/
#define  XML_FILE_READ_BUFF_SIZE              (0x1000)  /* 读文件缓冲区大小         */
#define  XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL  (0X80)   /* 节点标签缓冲区大小       */
#define  XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL  (0X8000) /* 节点值缓冲区大小         */
#define  XML_MAX_HARDWARE_LEN                 (0X20)    /* 单板Product Id的最大长度 */

#define  EN_NV_ID_END                        (0XFFFF)

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
    XML_RESULT_BUTT
};
typedef u32 XML_RESULT_ENUM_UINT32;

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
typedef u32 XML_ANALYSE_STATUS_ENUM_UINT32;
typedef u32 (*XML_FUN)(s8 cnowchar);

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
typedef u32 XML_PRODUCT_STATUS_ENUM_UINT32;

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
typedef u32 XML_DECODE_STATE_ENUM_UINT32;

/*****************************************************************************
枚举名    : XML_DECODE_JUMP_FLAG_ENUM
协议表格  :
ASN.1描述 :
枚举说明  : 用于解析xnv.xml文件时，记录当前是否需要跳转
*****************************************************************************/
enum XML_DECODE_JUMP_FLAG_ENUM
{
    XML_DECODE_STATUS_NOJUMP    = 0,              /* product_NvInfo节点无需跳转   */
    XML_DECODE_STATUS_JUMP ,                       /* product_NvInfo节点需要跳转*/
    XML_DECODE_STATUS_2JUMP,                      /* product节点跳转*/
    XML_DECODE_STATUS_JUMP_BUTT
};
typedef u32 XML_DECODE_JUMP_FLAG_ENUM;



#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif


/*****************************************************************************
4 UNION定义
*****************************************************************************/

/*****************************************************************************
5 STRUCT定义
*****************************************************************************/

/*****************************************************************************
结构名    : XNV_MAP_PRODUCT_INFO
协议表格  :
ASN.1描述 :
结构说明  : XNV XML映射文件product节点信息
*****************************************************************************/
typedef struct
{
    u32 product_id;              /*product id*/
    u32 productCatOff;           /*product cat offset in the file*/
    u32 productIdOff;            /*product id  offset in the file*/
}XNV_MAP_PRODUCT_INFO;


/*****************************************************************************
结构名    : XNV_MAP_HEAD_STRU
协议表格  :
ASN.1描述 :
结构说明  : XNV XML映射文件头结构
*****************************************************************************/
typedef struct
{
    u32 magic_num;               /*0x13579bde*/
    u32 product_num;             /*product 数目*/
    u8  md5[16];                 /*MD5校验码*/
    XNV_MAP_PRODUCT_INFO product_info[0];
}XNV_MAP_HEAD_STRU;

/*****************************************************************************
结构名    : XML_NODE_PROPERTY
协议表格  :
ASN.1描述 :
结构说明  : 节点属性链表的单元
*****************************************************************************/
typedef struct
{
    u32 ulnamelength;                  /* pcPropertyName 缓冲区长度  */
    u32 ulvaluelength;                 /* pcPropertyValue 缓冲区长度 */
    s8* pcpropertyname;                 /* 属性名称                   */
    s8* pcpropertyvalue;                /* 属性值                     */
}XML_NODE_PROPERTY_STRU;

/*NV属性的个数*/

#define XML_NODE_PROPERTY_NUM   (2)
/*****************************************************************************
结构名    : XML_NODE_STRU
协议表格  :
ASN.1描述 :
结构说明  : XML树的节点
*****************************************************************************/
typedef struct
{
    u32 ullabellength;                 /* pcNodeLabel 缓冲区长度    */
    u32 ullabelendlength;              /* pcNodeLabelEnd 缓冲区长度 */
    u32 ulvaluelength;                 /* pcNodeValue 缓冲区长度    */
    u32  ulPropertyIndex;               /*属性节点索引,记录stproperty的下标值*/
    s8*  pcnodelabel;                   /* 节点标签                  */
    s8*  pcnodelabelend;                /* 结尾独立标签              */
    s8*  pcnodevalue;                   /* 节点值                    */
    XML_NODE_PROPERTY_STRU stproperty[XML_NODE_PROPERTY_NUM];        /* 属性                      */
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
    XML_PRODUCT_STATUS_ENUM_UINT32 envalidnode;
    /* 判断XML解析是否完成                      */
    XML_DECODE_STATE_ENUM_UINT32   enxmldecodestate;
    /* 有效的Product节点及其子product节点的个数 */
    u32                     ulnodelevel;
    /* 记录当前单板的product id                 */
    s8                       acproductid[XML_MAX_HARDWARE_LEN];
    /*判断XML解析是否需要根据product_NvInfo跳转*/
    XML_DECODE_JUMP_FLAG_ENUM      enxmldecodejump;
}XML_PRODUCT_STRU;

/*****************************************************************************
结构名    : XML_ERROR_INFO_STRU
协议表格  :
ASN.1描述 :
结构说明  : 用于记录XML错误信息
*****************************************************************************/
typedef struct
{
    u32 ulxmlline;      /* XML对应的行号      */
    u32 ulstatus;       /* XML对应的解析状态  */
    u32 ulcodeline;     /* 出错代码对应的行号 */
    u16 usnvid;         /* NV ID的值          */
    u16 usreserve;      /* NV ID的值          */
    u32 ulresult;       /* 返回的结果         */
} XML_ERROR_INFO_STRU;


typedef struct
{
    XML_NODE_STRU g_stlxmlcurrentnode;
    XML_PRODUCT_STRU g_stlxmlproductinfo;
    u8 *g_puclnvitem;
    s8  *g_pclfilereadbuff;
    u32 g_stlxml_lineno;
    s32 g_stlxmlproductid;
    XML_ERROR_INFO_STRU g_stlxmlerrorinfo;
    u32 card_type;
    /*根据映射文件判断能否跳转*/
    XML_DECODE_JUMP_FLAG_ENUM g_stlxmljumpflag;
    /*通过product id计算文件跳转位置*/
    XNV_MAP_PRODUCT_INFO g_stlxmljumpinfo;
}XML_DOCODE_INFO;
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

u32 xml_decode_main(FILE* fp,s8* map_path,u32 card_type);
void xml_help(void);
void xml_nv_boot_write_priority(u8* ref_offset , u16 priority);
u32 xml_nv_boot_search_byid(u32 itemid,u8* pdata,struct nv_ref_data_info_stru* ref_info,struct nv_file_list_info_stru* file_info, u8** ref_offset);





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _NV_XML_DEC_H_ */
