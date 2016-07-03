

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

