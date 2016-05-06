/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mbuf.h
*
*  Project Code: VISPV100R005
*   Module Name: Mbuf
*  Date Created: 2000-3-25
*        Author: zhang hong yan(19316)
*   Description: 此文件定义Mbuf相关的宏和数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)  Creat the first version.
*  2006-4-27  wang xin(03278)        根据编程规范，对文件进行规范化整理
*  2006-05-10  lu yao(60000758)     为支持ARM CPU字节对齐特性，修改结构。
*  2006-07-06 xiehuaguo             修改MBUF State字段赋值的开关中断保护 A82d03169
*******************************************************************************/

#include "tcpip/public/arith_cbb/include/mbuf.h"

