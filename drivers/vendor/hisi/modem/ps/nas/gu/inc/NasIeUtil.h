/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasIeUtil.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2008年2月18日
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月18日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NASIEUTIL_H__
#define __NASIEUTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含                            
*****************************************************************************/
#include "vos.h"
#include "PsLib.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*
设置IE最后一个字节的位置
    pIe - 指向IE结构变量的指针
    oct - 最后一个有效的IE字节(IE 结构中的字段名称)
*/
#define NAS_IE_SET_LAST_OCTET_OFFSET(pIe, oct) \
    ((pIe)->LastOctOffset = (VOS_UINT8)((VOS_UINT32)&(pIe)->oct - (VOS_UINT32)&(pIe)->LastOctOffset))

/*
检查指定的IE字节是否存在
    pIe - 指向IE结构变量的指针
    oct - 需要检查的字节(IE 结构中的字段名称)
*/
#define NAS_IE_OCTET_PRESENT(pIe, oct) \
    (((VOS_UINT32)&(pIe)->oct - (VOS_UINT32)&(pIe)->LastOctOffset <= (pIe)->LastOctOffset) ? \
     VOS_TRUE : VOS_FALSE)

/*
设置IE中数据块的大小。
如果IE的数据块(多字节单元)中填写了数据，需要调用该宏设置填入的数据长度。
    pIe   - 指向IE结构变量的指针
    block - 需要设置的数据块(IE 结构中的数组字段名称)
    size  - 填入数据块中的数据长度
*/
#define NAS_IE_SET_BLOCK_SIZE(pIe, block, size) \
    ((pIe)->LastOctOffset = (VOS_UINT8)((((VOS_UINT32)&(pIe)->block[0] - (VOS_UINT32)&(pIe)->LastOctOffset) + size) - 1))

/*
取得IE中数据块的数据长度。
    pIe   - 指向IE结构变量的指针
    block - 需要取得数据长度的数据块(IE 结构中的数组字段名称)
*/
#define NAS_IE_GET_BLOCK_SIZE(pIe, block) \
    (((((VOS_UINT32)&(pIe)->block[0] - (VOS_UINT32)&(pIe)->LastOctOffset) - 1) <= (pIe)->LastOctOffset) ? \
     (((pIe)->LastOctOffset - ((VOS_UINT32)&(pIe)->block[0] - (VOS_UINT32)&(pIe)->LastOctOffset)) + 1) : 0)

/*
设置一个IE字节的值。
对于一些不需要逐位赋值的IE字节，可以使用该宏设置整个字节的值。
    pIe - 指向IE结构变量的指针
    oct - 需要设置的字节(IE 结构中的字段名称)
    val - 字节的值
*/
#define NAS_IE_SET_OCTET(pIe, oct, val) \
    (*((VOS_UINT8 *)&(pIe)->oct) = (VOS_UINT8)(val))


/*
取得一个IE字节的值。
    pIe - 指向IE结构变量的指针
    oct - 需要获取值的字节(IE 结构中的字段名称)
*/
#define NAS_IE_GET_OCTET(pIe, oct) \
    (*((VOS_UINT8 *)&(pIe)->oct))

/*
设置指定的IE不存在。只有当IE在消息中表现为存在时，才会被编码到空口消息流中。
    pIe - 指向IE结构变量的指针
*/
#define NAS_IE_SET_ABSENT(pIe)  ((pIe)->IsExist = 0)


/*
设置指定的IE存在。只有当IE在消息中表现为存在时，才会被编码到空口消息流中。
    pIe - 指向IE结构变量的指针
*/
#define NAS_IE_SET_PRESENT(pIe)  ((pIe)->IsExist = 1)


/*
检查指定的IE是否存在
    pIe - 指向IE结构变量的指针
*/
#define NAS_IE_IS_PRESENT(pIe)   (((pIe)->IsExist != 0) ? VOS_TRUE : VOS_FALSE)


/*****************************************************************************
  3 接口函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __NASIEUTIL_H__ */

