/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  sec_balong.h
*
*   作    者 :  wangxiandong
*
*   描    述 :  sec_balong.c 的头文件
*
*   修改记录 :  
*
*************************************************************************/
#ifndef _INTER_SEC_BALONG_H_
#define _INTER_SEC_BALONG_H_

#include <osl_types.h>
#include "product_config.h"


/* EFUSE空间划分*/
#define EFUSE_GRP_ROOT_CA       0x00
/* 安全校验使能标志 */
#define EFUSE_GRP_SECURITY      15
#define EFUSEC_SEC_EN_POS       4
#define EFUSEC_SEC_EN_WIDTH     1
#define EFUSEC_SEC_EN_MASK      (((1<<EFUSEC_SEC_EN_WIDTH)-1)<<EFUSEC_SEC_EN_POS)
#define EFUSEC_SEC_EN           (1<<EFUSEC_SEC_EN_POS)


#define UNSECBOOT_FLAG          (0x00)
#define SECBOOT_FLAG            (0x01)

#define P531_M3_LEN_INDEX       (45 * 4)
#define P531_ROOT_CA_INDEX      (P531_M3_LEN_INDEX + 4)


/*extern int efuse_read(u32 group, u32* pBuf, u32 num);
extern int efuse_write( u32 *pBuf, u32 group, u32 len );*/



#define SEC_OK 0
#define SEC_ERROR -1

enum sec_err_code
{
	SEC_ERR_NULL_PTR = 1,
	SEC_ERR_SHA_ERR,
	SEC_ERR_EFUSE_READ_ERR,
	SEC_ERR_NV_READ_ERR,
	SEC_ERR_IMG_SECURY_NOT_SUPPORT
};

#define SEC_ERROR_BASE_CODE              0x10000000
#define SEC_ERROR_NULL_PTR               (SEC_ERROR_BASE_CODE | SEC_ERR_NULL_PTR)
#define SEC_ERROR_SHA_ERR                (SEC_ERROR_BASE_CODE | SEC_ERR_SHA_ERR)
#define SEC_ERROR_EFUSE_READ_ERR         (SEC_ERROR_BASE_CODE | SEC_ERR_EFUSE_READ_ERR)
#define SEC_ERROR_NV_READ_ERR            (SEC_ERROR_BASE_CODE | SEC_ERR_NV_READ_ERR)
#define SEC_ERROR_IMG_SECURY_NOT_SUPPORT (SEC_ERROR_BASE_CODE | SEC_ERR_IMG_SECURY_NOT_SUPPORT)

#ifdef BSP_HAS_SEC_FEATURE
s32 secureSupport(u8* pData);
s32 secureAlreadyUse(u8 * pData);
s32 drvSecCheck(void);
s32 startSecure(void);

#else
static inline BSP_S32 secureSupport(u8* pData)
{
    return 0;
}


static inline s32 secureAlreadyUse(u8 * pData)
{
    if(pData)
        *pData = 0;

    return 0;
}
static inline unsigned int drvSecCheck(void)
{
    return 0;
}

static inline s32 startSecure(void)
{
    return 0;
}

#endif



#endif
