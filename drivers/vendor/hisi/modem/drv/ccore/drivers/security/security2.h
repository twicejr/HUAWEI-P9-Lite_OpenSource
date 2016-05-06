/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  security.h
*
*   作    者 :  wuzechun
*
*   描    述 :  security.c 的头文件
*
*   修改记录 :  2011年8月10日  v1.00  wuzechun  创建
*
*************************************************************************/

#ifndef __SECURITY2_H__
#define __SECURITY2_H__

#include "drv_comm.h"

#define RSA_REG_MAX_DATA   0x80  /*RSA计算时数据寄存器最长大小的字节数128Byte*/    

#define SHA1_PADDING_LENGTH_LIMIT   ((512-64)/8)  /*SHA1计算时最后8位为长度,所以前面有56个字节*/

#define SHA1_HASH_LEN 20
#define MD5_HASH_LEN 128

#define NV_RSA_PUB_KEY 5555 /*for compile*/

#define RSA_KEY_LEN 520
#define AES_KEY_LEN 32

BSP_S32 secSetRootCa( BSP_U8 *pBlBuf );

#endif /* security.h */

