/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  efuse.h
*
*   作    者 :  wuzechun
*
*   描    述 :  efuse.c 的头文件
*
*   修改记录 :  2011年6月9日  v1.00  wuzechun  创建
*
*************************************************************************/

#ifndef __EFUSE_BALONG_H__
#define __EFUSE_BALONG_H__



#ifdef __cplusplus
extern "C" {
#endif

#include "osl_types.h"
#include "bsp_efuse.h"



/*****************************************************************************
* 函 数 名  : efuseReadHUK
*
* 功能描述  : 读取efuse huk数据
*
* 输入参数  : pBuf   读取到的EFUSE中的数据
*             num    数组长度
* 输出参数  : 
*
* 返 回 值  : OK 成功
*             ERROR 失败
*
* 其它说明  : 
*
*****************************************************************************/
int efuseReadHUK(u32 *pBuf,u32 len);

#ifdef __cplusplus
}
#endif

#endif /* efuse_balong.h */

