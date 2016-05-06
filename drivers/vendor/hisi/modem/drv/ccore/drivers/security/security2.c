/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  security.c
*
*   作    者 :  wuzechun
*
*   描    述 :  完成安全校验镜像的功能,可以使用
*                 OnChipRom共享的代码,在不使用OnChipRom的情况
*                 下,也可以使用单独的驱动.
*
*   修改记录 :  2011年8月10日  v1.00  wuzechun  创建
*
*************************************************************************/
#include <string.h>
#include <stdio.h>
#include <securec.h>
#include <osl_malloc.h>
#include <hi_efuse.h>
#include <mdrv_crypto.h>
#include <mdrv_efuse.h>
#include <bsp_efuse.h>
#include "security2.h"
#include "cipher_aes.h"
#include "rsa.h"
#include "ran.h"
#include "sha_alg.h"
#include "bsp_om.h"
#include "hi_efuse.h"

/*lint --e{534, 801} */
//#define EFUSE_HUK_SIZE          (4)
//#define EFUSE_GROUP_SIZE        (4)

//#ifdef HI_K3_EFUSE
//#define EFUSE_GRP_HUK           (28)
//#else
//#define EFUSE_GRP_HUK           (4)
//#endif

/*
 FIXME: too many params in each function, change to use struct.
 FIXME: use uint instead int for len/size params.
 FIXME: change char to void*
*/
#define  security_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SECURITY, "[SECURITY]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))

int param_check(char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen)
{
    if(data == NULL || key == NULL || klen == NULL)
    {
        security_print("ERROR param_check: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len<=0)
    {
        security_print("ERROR param_check: param is invalid!\n");
        return BSP_ERROR;
    }
    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : create_crypto_key
*
* 功能描述  : 使用输入的数据和HUK，生成密钥。当前支持MD5、和SHA-1算法。
*
*             生成密钥的方法:
*             把HUK和输入的数据连接起来作为MD5或SHA-1算法的输入，计算其HASH值。
*
* 输入参数  : data:      用于生成密钥的数据。
*             len:       用于生成密钥的数据长度。(byte)
*             algorithm: 要使用的密钥生成算法。
*             klen:      作为输入参数，存放key的缓冲区的长度。(byte)
*
* 输出参数  : key:       存放生成的密钥。buffer必须大于16(MD5)/20(SHA-1)字节。
*             klen:      作为输出参数，存放生成的密钥的长度。(byte)
*
* 返 回 值  : BSP_OK:    生成成功。
*             BSP_ERROR: 生成失败。
*
* 其它说明  : klen为输入/输出参数，传入的klen变量所用内存必须可写回。
*             所以避免直接传入类似sizeof()的函数调用结果。
*
*****************************************************************************/
int create_crypto_key_o(char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen)
{
    char* crypto_data = NULL;
    UINT8 i=0;

        if(BSP_OK != param_check(data,len,algorithm,key,klen))
        {
        security_print("ERROR create_crypto_key: param is invalid!\n");
        goto ERROR_EXIT;
        }

    crypto_data = (char*)osl_malloc((unsigned int)(len + EFUSE_HUK_LEN));

    if(crypto_data == NULL)
    {
        security_print("ERROR create_crypto_key: malloc failed!\n");
        goto ERROR_EXIT;
    }

    memset_s(crypto_data, (size_t)(len + EFUSE_HUK_LEN), 0, (size_t)(len + EFUSE_HUK_LEN));

	/* Read & Copy HUK.*/
	if(BSP_OK != mdrv_efuse_read_huk((unsigned char*)crypto_data, EFUSE_HUK_LEN ))
	{
	    security_print("ERROR create_crypto_key: efuseRead failed!\n");
        goto ERROR_EXIT;
	}
    for(i=0;i<EFUSE_HUK_LEN;i++)
    {
            if(0 != *(((UINT8*)crypto_data)+i))
            {
                break;
            }
    }

    if(i>=EFUSE_HUK_LEN)
        {
            security_print("ERROR create_crypto_key: read_efuse NULL!\n");
            goto ERROR_EXIT;
    }


    // Copy user data.
    memcpy_s((void*)((UINT32)crypto_data + EFUSE_HUK_LEN), (size_t)len, data, (size_t)len);


    // Encrypt.
    switch(algorithm)
    {
    /*case CREATE_CRYPTO_KEY_ALGORITHM_MD5:*/
    /*case CREATE_CRYPTO_KEY_ALGORITHM_SHA1:*/
    case CREATE_CRYPTO_KEY_ALGORITHM_SHA256:
        if(BSP_OK != mdrv_crypto_hash(crypto_data, len + EFUSE_HUK_LEN, (CRYPTO_HASH_ALGORITHM_E)algorithm, key, klen))
        {
            security_print("ERROR create_crypto_key: mdrv_crypto_hash failed!\n");
            goto ERROR_EXIT;
        }

        break;

    default:
        security_print("ERROR create_crypto_key: unknown algorithm!\n");

        goto ERROR_EXIT;
    }

    osl_free(crypto_data);

#ifndef _DRV_LLT_
       /*REG_WRITE_32(PWR_SC_PERIPH_CLKDIS0, SOC_CLK_CLOSE_DIS0);*/
#endif
    return BSP_OK;

ERROR_EXIT:
    if(crypto_data != NULL)
    {
        osl_free(crypto_data);
    }

    return BSP_ERROR;
}

int mdrv_crypto_gen_key (char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen)
{
    if (create_crypto_key_o(data, len, algorithm, key, klen))
    {
        
        return BSP_ERROR;
    }
    
    return BSP_OK;
}
/*****************************************************************************
* 函 数 名  : mdrv_crypto_hash
*
* 功能描述  : 计算输入的数据，输出16字节的HASH值，当前支持MD5、和SHA-1算法。
*
* 输入参数  : data:      待计算HASH值的数据。
*             len:       待计算HASH值的数据长度。(byte)
*             algorithm: 所要使用的HASH算法。
*             hlen:      作为输入参数，存放HASH值的缓冲区的长度。(byte)
*
* 输出参数  : hash:      存放生成的HASH值。buffer必须大于16(MD5)/20(SHA-1)字节。
*             hlen:      作为输出参数，存放生成的HASH值的长度。(byte)
*
* 返 回 值  : OK:        生成成功。
*             ERROR:     生成失败。
*
* 其它说明  : hlen为输入/输出参数，传入的hlen变量所用内存必须可写回。
*             所以避免直接传入类似sizeof()的函数调用结果。
*
*****************************************************************************/
int crypto_hash_o(char *data, int len, CRYPTO_HASH_ALGORITHM_E algorithm, char *hash, int *hlen)
{
    if(data == NULL || hash == NULL || hlen == NULL)
    {
        security_print("ERROR mdrv_crypto_hash: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len<=0 )
    {
        security_print("ERROR mdrv_crypto_hash: param is invalid!\n");
        return BSP_ERROR;
    }

    switch(algorithm)
    {
    case CRYPTO_ALGORITHM_SHA256:

        if (*hlen < SHA256_DIGEST_LENGTH)
        {
            security_print("ERROR mdrv_crypto_hash: param hlen is invalid!(hash bufsize is too small)\n");
            return BSP_ERROR;
        }

        SHA256_Hash((unsigned char*)data,(unsigned long)len,(unsigned char*)hash);

        *hlen = SHA256_DIGEST_LENGTH;

        break;
    case CRYPTO_ALGORITHM_MD5:
    case CRYPTO_ALGORITHM_SHA1:
    default:
        security_print("ERROR mdrv_crypto_hash: unknown algorithm!\n");

        return BSP_ERROR;
    }

    return BSP_OK;
}/*lint !e429*/

int mdrv_crypto_hash (char *data, int len, CRYPTO_HASH_ALGORITHM_E algorithm, char *hash, int *hlen)
{
    if(crypto_hash_o(data, len,  algorithm, hash,  hlen))
    {
        
        return BSP_ERROR;
    }
    return BSP_OK;
}
/*****************************************************************************
* 函 数 名  : crypto_encrypt
*
* 功能描述  : 使用指定的密钥和指定的算法对输入的数据加密，输出加密后的数据。
*             当前支持AES-ECB算法。
*
* 输入参数  : data:        待加密数据。
*             len:         待加密数据长度。(byte)
*             algorithm:   所用HASH算法。
*             key:         密钥buffer。
*             klen:        密钥buffer长度。(byte)
*             cipher_len:  加密后的数据的存放buffer的buffer size。(byte)(没有检查)
*
* 输出参数  : cipher_data: 加密后的数据的存放buffer。
*             cipher_len:  加密后的数据的实际长度。(byte)
*
* 返 回 值  : BSP_OK:      加密成功。
*             BSP_ERROR:   加密失败。
*
* 其它说明  : cipher_len为输入/输出参数，传入的cipher_len变量所用内存必须可写回。
*             所以避免直接传入类似sizeof()的函数调用结果。
*
*****************************************************************************/
int crypto_encrypt_o (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *cipher_data, int *cipher_len)
{
    crypto_aes aes_ctx;
    int16 keybits = 0;
    if(data == NULL || key == NULL || cipher_data == NULL || cipher_len == NULL)
    {
        security_print("ERROR crypto_encrypt: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len<=0 || (klen != AES_KEY_LEN && klen != 16))
    {
        security_print("ERROR crypto_encrypt: param is invalid!\n");
        return BSP_ERROR;
    }
    if (klen == 16)
    {
        keybits = 128;/* [false alarm]:误报 */
    }
    else if(klen == AES_KEY_LEN)
    {
        keybits = 256;/* [false alarm]:误报 */
    }
    crypto_aes_init(&aes_ctx,(UINT8*)key,keybits,MODE_ECB,NULL);

    switch(algorithm)
    {
    case CRYPTO_ENCRYPT_ALGORITHM_AES_ECB:
        //if(0 != crypto_aes_encrypt_pad(&aes_ctx,data,len,cipher_data,cipher_len))
        if(0 != crypto_aes_encrypt_block(&aes_ctx,(UINT8*)data,len,(UINT8*)cipher_data,(int32*)cipher_len))
        {
            security_print("ERROR crypto_encrypt: crypto_aes_encrypt_pad failed!\n");
            return BSP_ERROR;
        }
        break;

    default:
        security_print("ERROR crypto_encrypt: unknown algorithm!\n");

        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_enc (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *cipher_data, int *cipher_len)
{
    if(crypto_encrypt_o(data, len, algorithm, key, klen, cipher_data, cipher_len))
    {
        
        return BSP_ERROR;        
    }
    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : crypto_decrypt
*
* 功能描述  : 使用指定的密钥和指定的算法对输入的数据解密，输出解密后的数据。
*             当前支持AES-ECB算法。
*
* 输入参数  :
*             cipher_data: 待密的数据的存放buffer。
*             cipher_len:  待解密的数据的实际长度。(byte)
*             algorithm:   所用解密算法，暂只提供AES-ECB。
*             key:         密钥buffer。
*             klen:        密钥buffer长度。(byte)
*             len:  解密后的数据的存放buffer的buffer size。(byte)(没有检查)
*
* 输出参数  :
*             data:        解密后的数据。
*             len:         解密后的数据长度。(byte)
*
* 返 回 值  : BSP_OK:      解密成功。
*             BSP_ERROR:   解密失败。
*
* 其它说明  : len为输入/输出参数，传入的len变量所用内存必须可写回。
*             所以避免直接传入类似sizeof()的函数调用结果。
*
*****************************************************************************/
int crypto_decrypt_o (char *cipher_data,int cipher_len,CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *data, int *len)
{
    crypto_aes aes_ctx;

    if((cipher_data == NULL) || (cipher_len == 0) || (data == NULL) || (key == NULL))
    {
        security_print("ERROR crypto_decrypt: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(cipher_len<=0 || klen != AES_KEY_LEN)
    {
        security_print("ERROR crypto_decrypt: param is invalid!\n");
        return BSP_ERROR;
    }

    crypto_aes_init(&aes_ctx,(UINT8*)key,256,MODE_ECB,NULL);

    switch(algorithm)
    {
    case CRYPTO_ENCRYPT_ALGORITHM_AES_ECB:
        if(0 != crypto_aes_decrypt_block(&aes_ctx, (uint8 *)cipher_data, (int32)cipher_len, (uint8 *)data, (int32 *)len ))
        {
            security_print("ERROR crypto_decrypt: crypto_aes_decrypt_block failed!\n");
            return BSP_ERROR;
        }
        break;

    default:
        security_print("ERROR crypto_decrypt: unknown algorithm!\n");

        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_dec (char *cipher_data,int cipher_len,CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *data, int *len)
{
    if(crypto_decrypt_o(cipher_data,  cipher_len,  algorithm, key, klen,  data,  len))
    {
        
        return BSP_ERROR;
    }
    return BSP_OK; 
}
/*****************************************************************************
* 函 数 名  : mdrv_crypto_enc_rsa
*
* 功能描述  : 使用保存在NV中的改制用RSA公钥，对输入的数据加密。
*             (读取时需要同样进行签名验证)
*
* 输入参数  : data:        待加密数据。
*             len:         待加密数据长度。(byte)
*             rsa_key:     RSA公钥buffer指针。
*             rsa_len:     RSA公钥buffer长度。(byte)
*             cipher_len:  加密后的数据的存放buffer的buffer size。(byte)(没有检查)
*
* 输出参数  : cipher_data: 加密后的数据的存放buffer。
*             cipher_len:  加密后的数据的实际长度。(byte)
*
* 返 回 值  : BSP_OK:      加密成功。
*             BSP_ERROR:   加密失败。
*
* 其它说明  : cipher_len为输入/输出参数，传入的cipher_len变量所用内存必须可写回。
*             所以避免直接传入类似sizeof()的函数调用结果。
*
*****************************************************************************/
int crypto_rsa_encrypt_o (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len)
{
    //rsa_public_key* p_rsa_key = (rsa_public_key*)rsa_key;/*模A*/
    rsa_public_key* p_rsa_key = NULL;

    if(data == NULL || rsa_key == NULL || cipher_data == NULL || cipher_len == NULL)
    {
        security_print("ERROR mdrv_crypto_enc_rsa: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len <=0 || rsa_klen != RSA_KEY_LEN)
    {
        security_print("ERROR mdrv_crypto_enc_rsa: param is invalid!\n");
        return BSP_ERROR;
    }

    p_rsa_key = (rsa_public_key*)(rsa_key+rsa_klen/2);/*模B*/

    if(0 != rsa_public_encrypt((UINT8*)data, (uint16)len, (UINT8*)cipher_data, (UINT16*)cipher_len, p_rsa_key))
    {
        security_print("ERROR mdrv_crypto_enc_rsa: rsa_private_encrypt failed!\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_enc_rsa (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len)
{
    if(crypto_rsa_encrypt_o( data,  len,  rsa_key,  rsa_klen,  cipher_data, cipher_len))
    {
        
        return BSP_ERROR;        
    }   
    return BSP_OK;
}
/*****************************************************************************
* 函 数 名  : mdrv_crypto_dec_rsa
*
* 功能描述  : 使用保存在NV中的改制用RSA公钥，对输入的数据解密。
*
* 输入参数  : cipher_data: 待解密数据。
*             cipher_len:  待解密数据长度。(byte)
*             rsa_key:     RSA公钥buffer指针
*             rsa_len:     RSA公钥buffer长度。(byte)
*             len:         解密后的数据的存放buffer的buffer size。(byte)(没有检查)
*
* 输出参数  : data:        解密后的数据的存放buffer。
*             len:         解密后的数据的实际长度。(byte)
*
* 返 回 值  : BSP_OK:      解密成功。
*             BSP_ERROR:   解密失败。
*
* 其它说明  : len为输入/输出参数，传入的len变量所用内存必须可写回。
*             所以避免直接传入类似sizeof()的函数调用结果。
*
*****************************************************************************/
int crypto_rsa_decrypt_o (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len)
{
    //rsa_public_key* p_rsa_key = (rsa_public_key*)rsa_key;/*模A*/
    rsa_public_key* p_rsa_key = NULL;

    if(cipher_data == NULL || rsa_key == NULL || data == NULL || len == NULL)
    {
        security_print("ERROR mdrv_crypto_dec_rsa: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(cipher_len <=0 || rsa_klen != RSA_KEY_LEN)
    {
        security_print("ERROR mdrv_crypto_dec_rsa: param is invalid!\n");
        return BSP_ERROR;
    }

    p_rsa_key = (rsa_public_key*)(rsa_key+rsa_klen/2);/*模B*/

    if(0 != rsa_public_decrypt((UINT8*)cipher_data,(uint16)cipher_len,(UINT8*)data,(UINT16*)len,p_rsa_key))
    {
        security_print("ERROR mdrv_crypto_dec_rsa: rsa_public_decrypt failed!\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_dec_rsa (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len)
{
    if(crypto_rsa_decrypt_o(cipher_data, cipher_len, rsa_key,  rsa_klen,  data,  len))
    {
        
        return BSP_ERROR;        
    }
    return BSP_OK;
}
/*****************************************************************************
* 函 数 名  : crypto_rand
*
* 功能描述  : 随机数生成接口
*
* 输入参数  : len:       期望得到的随机数字节数,只支持4字节。(byte)
*
* 输出参数  : rand_data: 随机数存放buffer。
*
* 返 回 值  : BSP_OK:    获取随机数成功。
*             BSP_ERROR: 获取随机数失败。
*
* 其它说明  : 1. 本接口以时间为种子获取随机数，并且获取结果与时钟强相关。请勿
*                在同一时钟粒度内连续反复调用。连续调用将获得同样结果。
*
*             2. len参数只接受传入4。
*
*****************************************************************************/
int crypto_rand_o (char *rand_data, int len)
{
    if(NULL == rand_data)
    {
        security_print("ERROR crypto_rand: param rand_data is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len!=4)
    {
        security_print("ERROR crypto_rand: param len is invalid!\n");
        return BSP_ERROR;
    }
	/* coverity[secure_coding] */
    *(uint32*)rand_data = bsp_random();/* [false alarm]:coverity消除时已经申请屏蔽 */

    return BSP_OK;
}

int mdrv_crypto_gen_rand (char *rand_data, int len)
{
        return crypto_rand_o(rand_data, len);
}

