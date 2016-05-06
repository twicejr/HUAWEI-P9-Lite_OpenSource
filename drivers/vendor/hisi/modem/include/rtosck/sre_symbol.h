/**
 * @file sre_symbol.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：符号表模块的头文件 \n
 */

/**
 * @defgroup SRE_symbol 符号表
 * @ingroup SRE_inspect
*/

#ifndef _SRE_SYMBOL_H
#define _SRE_SYMBOL_H

#include "sre_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:入参指针为空。
 *
 * 值: 0x02002900
 *
 * 解决方案: 排查函数入参是否为空
 *
 */
#define OS_ERRNO_SYMBOL_PARA_POINT_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x00)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:符号表管理内存申请失败。
 *
 * 值: 0x02002901
 *
 * 解决方案: 检查符号表创建的分区内存大小是否够用或者OS内存分区不足
 *
 */
#define OS_ERRNO_SYMBOL_MEM_ALLOC_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x01)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:符号重定义。
 *
 * 值: 0x02002902
 *
 * 解决方案:检查是否有符号项重名
 *
 */
#define OS_ERRNO_SYMBOL_REDEFINE_ERROR                       SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x02)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:在符号表中没有查找到地址匹配的符号节点。
 *
 * 值: 0x02002903
 *
 * 解决方案: 请确认查找的地址是否正确
 *
 */
#define OS_ERRNO_SYMBOL_FIND_ADDR_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x03)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:在符号表中没有查找到符号名字匹配的符号节点。
 *
 * 值: 0x02002904
 *
 * 解决方案: 请确认查找的符号名是否正确
 *
 */
#define OS_ERRNO_SYMBOL_FIND_NAME_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x04)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:符号表节点删除失败，静态符号表不允许删除。
 *
 * 值: 0x02002905
 *
 * 解决方案: 查看删除的符号项对应的UnitInterNo是否是正确，UnitInterNo为0表示静态符号项，不允许删除。
 *
 */
#define OS_ERRNO_SYMBOL_REMOVE_ID_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x05)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:动态添加符号项的序列ID与静态的重复。
 *
 * 值: 0x02002906
 *
 * 解决方案: 查看动态添加符号项序列UnitInterNo是否正确，不能为0(UnitInterNo为0表示静态符号项)。
 *
 */
#define OS_ERRNO_SYMBOL_PARA_ID_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x06)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:符号表中使用的镜像ID不可用。
 *
 * 值: 0x02002907
 *
 * 解决方案: 如果在初始化时遇到该错误码，检查是否是同一镜像重复初始化或者镜像ID配置错误。
 *           如果在使用时遇到该错误码，查看对应镜像是否存在或者该镜像的符号表是否打开。
 *
 */
#define OS_ERRNO_SYMBOL_IMAGE_ID_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x07)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:符号表配置的分区起始地址或大小不合法。
 *
 * 值: 0x02002908
 *
 * 解决方案: 用户配置的分区号不为0时，符号表模块配置的分区起始地址或者大小不能为0。
 *
 */
#define OS_ERRNO_SYMBOL_ADDR_SIZE_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x08)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:符号表配置的分区号不合法。
 *
 * 值: 0x02002909
 *
 * 解决方案: SD6183/SD6182/SD6108/SD6181/SD6157平台，符号表模块分区号不能配置为0。
 *
 */
#define OS_ERRNO_SYMBOL_PT_NUM_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x09)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:同一镜像符号表配置的分区参数或不一致。
 *
 * 值: 0x0200290a
 *
 * 解决方案: SD6182/SD6157/SD6183/SD6108/SD6181平台，检查同一镜像sre_config.h中符号表模块分区配置是否相同。
 *
 */
#define OS_ERRNO_SYMBOL_PT_PARA_NOT_SAME                     SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x0a)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:根据符号名获取符号地址时，输入的指针参数为NULL。
 *
 * 值: 0x0200290b
 *
 * 解决方案: 根据符号名获取符号地址时，须保证输入的指针参数不能为NULL。
 *
 */
#define OS_ERRNO_SYMBOL_GET_ADDR_PTR_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x0b)

/**
 * @ingroup SRE_symbol
 * 符号表管理错误码:入参非法
 *
 * 值: 0x0200290c
 *
 * 解决方案: 排查函数入参的段结束地址是否大于起始地址
 *
 */
#define OS_ERRNO_SYMBOL_PARA_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_SYMBOL, 0x0c)



/**
* @ingroup SRE_symbol
* 未定义的符号类型。
*
*/
#define OS_SYM_UNDF        0x0

/**
* @ingroup SRE_symbol
* 全局符号类型。
*
*/
#define OS_SYM_GLOBAL      0x1

/**
* @ingroup SRE_symbol
* 代码段符号类型。
*
*/
#define OS_SYM_TEXT        0x2

/**
* @ingroup SRE_symbol
* 数据段符号类型。
*
*/
#define OS_SYM_DATA        0x4

/**
* @ingroup SRE_symbol
* absolute符号类型。
*
*/
#define OS_SYM_ABS         0x8

/**
* @ingroup SRE_symbol
* 通用符号类型。
*
*/
#define OS_SYM_COMM        0x10

/**
* @ingroup SRE_symbol
*  缺省的序列ID号。
*
*/
#define OS_SYMBOL_REVID    0x0

/**
* @ingroup SRE_symbol
* 设置符号表模块信息。
*
*/
typedef struct tagSymbolModInfo
{
    UINT32 uwInitPhase;        /**<  符号表初始化标记      */
    UINT32 uwSymRegNum;        /**<  符号表分区号          */
    VOID*  uwSymRegAddr;       /**<  符号表分区起始地址    */
    UINT32 uwSymRegSize;       /**<  符号表分区大小        */
#if (OS_OPTION_SYMBOL_COREBITMAP == YES)
    UINT32 uwSymUnitNum;       /**<  符号表中一个进程组注册的LP单元数*/
#endif

} SYMBOL_MOD_INFO_S;


/**
 * @ingroup SRE_symbol
 * 单链表的链表节点结构体定义。
 *
 */
typedef struct tagSllNode
{
    struct tagSllNode *pstNext;/**<单链表指向下一个节点的指针*/
} OS_SLL_NODE_S;


/**
 * @ingroup SRE_symbol
 * Hash表的节点结构体。
 *
 */
typedef struct tagSymbolNode   /**< HASH_SYMBOL_NODE - entry in symbol table */
{
    OS_SLL_NODE_S stNameHNode;     /**< hash node (must come first)     */
    CHAR*       pcName;            /**< 指向符号名的指针                */
    VOID*       pscValue;          /**< 符号地址                        */
    UINT8       ucType;            /**< 符号类型: OS_SYM_UNDF&OS_SYM_GLOBAL&OS_SYM_ABS&OS_SYM_TEXT&OS_SYM_DATA等   */
    UINT8       ucSymGroupID;      /**< 符号动态添加的组ID，0~0xfe为LP使用(值为LP的GroupID+1)，0xff为shell使用,支持SRE_MNG功能下该字段为无效*/
    UINT16      usUnitInterNo;     /**< 符号的所属单元ID，1~9999为LP使用(值为LP的内部补丁单元号)，0xfffe为shell使用*/
    UINT32      uwSize;            /**< 符号的长度                      */
} OS_SYMBOL_NODE_S;


/**
 * @ingroup SRE_symbol
 * Hash表的每个链表头结构体定义，分别指向链表的首尾节点。
 *
 */
typedef struct tagSllList
{
    OS_SLL_NODE_S *pstHead;  /**< 链表头指针*/
    OS_SLL_NODE_S *pstTail;  /**< 链表尾指针*/
} OS_SLL_LIST_S;

/**
 * @ingroup SRE_symbol
 * Hash表表头，统计整张表的信息。
 *
 */
typedef struct tagSymbolTbl
{
    UINT32   uwElements;           /**< Hash表中Hash链表的个数      */
    UINT32   uwKeyArg;             /**< Hash表的种子                */
    UINT32   uwInitPhase;          /**< 符号表初始化标记            */
    UINT32   uwSymPartId;          /**< 符号表管理所在的内存分区号  */
    UINT32   uwSymbolNum;          /**< Hash表中符号的个数          */
    OS_SLL_LIST_S *pstHashTbl;     /**< 指向Hash链表的数组指针      */
} OS_SYMBOL_TBL_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_SYMBOL_H */

/**
 * History:
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/

