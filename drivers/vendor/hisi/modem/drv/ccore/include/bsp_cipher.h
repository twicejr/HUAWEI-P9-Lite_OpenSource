/*************************************************************************
*   版权所有(C) 1987-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  Drvinterface.h
*
*   作    者 :  wangxiandong
*
*   描    述 :  本文件命名为"Drvinterface.h", 给出V7R1底软和协议栈之间的API接口统计
*
*   修改记录 :  2013年1月21日  v1.00  wangxiandong 创建
*************************************************************************/
#ifndef __BSP_CIPHER_H__
#define __BSP_CIPHER_H__

#include <osl_types.h>
#include <product_config.h>
#include <mdrv_cipher.h>
#include "kdf_balong.h"
#include "cipher_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_CIPHER
int cipher_init(void);
#else
int cipher_init(void)
{return 0;}
#endif
int cipher_start_channel(unsigned int chn, unsigned int num, CIPHER_SUBMIT_TYPE_E subm_attr);
int mdrv_cipher_chn_idle(unsigned int chn);
int kdf_rw_key (KDF_OPS kdf_op, void * pDestAddr, unsigned int u32KeyIndex ,unsigned int u32ReadLength);
int mdrv_cipher_gen_key(KEY_CONFIG_INFO_S * pstKeyCfgInfo, S_CONFIG_INFO_S * pstSCfgInfo,
	unsigned int u32DestIndex, KEY_MAKE_S * pstKeyMake);


/*************************KDF HASH START **********************************/
/*****************************************************************************
* 函 数 名  : kdf_init
*
* 功能描述  : A核KDF队列空间申请初始化，用于计算HASH值，在C核启动之前使用
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 0    : 正确
*             其他 : 错误
*****************************************************************************/
int kdf_init(void);

int kdf_hash_init(void);
int kdfdev_init(void);
void kdfdev_exit(void);
/*****************************************************************************
* 函 数 名  : kdf_reg_init
*
* 功能描述  : A核KDF寄存器配置，用于计算HASH值，在C核启动之前使用
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
void kdf_reg_init(void);
/*****************************************************************************
* 函 数 名  : kdf_hash_setkey
*
* 功能描述  : A核KDF操作设置key，用于计算HASH值，在C核启动之前使用
*
* 输入参数  : 传入key的首地址，默认key的长度固定为32字节
* 输出参数  : 无
* 返 回 值  : 0    : 正确
*             其他 : 错误
*****************************************************************************/
int kdf_hash_setkey(void * key_addr);
/*****************************************************************************
* 函 数 名  : kdf_result_hash_get
*
* 功能描述  : A核KDF操作获取结果HASH，在C核启动之前使用
*
* 输入参数  : 无
* 输出参数  : out_hash : 用于接收结果HASH的内存空间首地址，默认至少32字节
* 返 回 值  : 0    : 正确
*             其他 : 错误
*****************************************************************************/
int kdf_result_hash_get(void * out_hash);
/*****************************************************************************
* 函 数 名  : kdf_hash_make
*
* 功能描述  : A核KDF操作计算HASH，在C核启动之前使用
*
* 输入参数  : sha_s_addr : 传入数据的首地址，数据最大长度不能超过512字节
*             sha_s_len  : 传入数据的实际长度，以字节为单位
* 输出参数  : 无
* 返 回 值  : 0    : 正确
*             其他 : 错误
*****************************************************************************/
int kdf_hash_make(void * sha_s_addr, u32 sha_s_len);
/*************************KDF HASH END **********************************/

int bsp_cipher_set_channel_dma(int channel, int dma);

#ifdef __cplusplus
}
#endif

#endif /* end of __BSP_CIPHER_H__ */

