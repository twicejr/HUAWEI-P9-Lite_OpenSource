#ifndef __MDRV_CCORE_CRYPTO_H__
#define __MDRV_CCORE_CRYPTO_H__
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    CREATE_CRYPTO_KEY_ALGORITHM_MD5 = 0x0,
    CREATE_CRYPTO_KEY_ALGORITHM_SHA1,
    CREATE_CRYPTO_KEY_ALGORITHM_SHA256,
    CREATE_CRYPTO_KEY_ALGORITHM_MAX,
}CREATE_CRYPTO_KEY_ALGORITHM_E;

typedef enum
{
    CRYPTO_ALGORITHM_MD5 = 0x0,
    CRYPTO_ALGORITHM_SHA1,
    CRYPTO_ALGORITHM_SHA256,
    CRYPTO_ALGORITHM_MAX,
}CRYPTO_HASH_ALGORITHM_E;

typedef enum
{
    CRYPTO_ENCRYPT_ALGORITHM_AES_ECB = 0x0,
    CRYPTO_ENCRYPT_ALGORITHM_MAX,
}CRYPTO_ENCRYPT_ALGORITHM_E;

/*****************************************************************************
* 函 数 名  : mdrv_crypto_gen_key
*
* 功能描述  : 用于生成新的密钥
*
* 输入参数  : char *data   存放用于生成密钥的数据
*             int len      存放输入数据长度(字节)
*             mdrv_crypto_gen_key_ALGORITHM algorithm  用于产生密钥的算法
*             char *key    生成的密钥
*             int *klen    作为输入时存放key的缓冲区的长度。作为输出参数，存放生成的密钥的长度。(字节)
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_gen_key (char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_hash
*
* 功能描述  : 计算HASH值
*
* 输入参数  : char *data   存放用于需要计算HASH值的数据
*             int len      存放输入数据长度(字节)
*             CRYPTO_HASH_ALGORITHM_E algorithm  HASH算法
*             char *hash   存放生成的HASH值
*             int *hlen    作为输入参数，存放HASH值的缓冲区的长度；作为输出参数，存放生成的HASH值的长度（字节）
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_hash (char *data, int len, CRYPTO_HASH_ALGORITHM_E algorithm, char *hash, int *hlen);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_enc
*
* 功能描述  : AES加密
*
* 输入参数  : char *data   待加密的数据
*             int len      明文数据长度(字节)
*             CRYPTO_ENCRYPT_ALGORITHM_E algorithm  加密算法
*             char *key    加密密钥
*             int klen     密钥的长度(字节)
*             char *cipher_data 加密后的数据
*             int *cipher_len  (字节)作为输入参数，存放密文的缓冲区的长度。作为输出参数，存放生成的密文的长度
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_enc (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *cipher_data, int *cipher_len);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_dec
*
* 功能描述  : AES解密
*
* 输入参数  : char *cipher_data  待解密的数据
*             int cipher_len     密文数据长度(字节)
*             CRYPTO_ENCRYPT_ALGORITHM_E algorithm  解密算法
*             char *key          密钥
*             int klen           密钥长度
*             char *data         解密后的数据
*             int *len           (byte)输入：解密后的数据的存放buffer的buffer size。 (没有检查)；输出：解密后的数据长度。
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_dec (char *cipher_data,int cipher_len,CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *data, int *len);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_enc_rsa
*
* 功能描述  : RSA加密
*
* 输入参数  : char *data     待加密的数据
*             int len        明文数据长度(字节)
*             char *rsa_key  密钥
*             int rsa_klen   密钥长度
*             char *cipher_data 加密后的数据
*             int *cipher_len   (字节)作为输入参数，存放密文的缓冲区的长度。作为输出参数，存放生成的密文的长度。
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_enc_rsa (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_dec_rsa
*
* 功能描述  : RSA解密
*
* 输入参数  : char *cipher_data  待解密的数据
*             int cipher_len     密文数据长度(字节)
*             char *rsa_key      密钥
*             int rsa_klen       密钥长度
*             char *data         解密后的数据
*             int *len           (byte)输入：解密后的数据的存放buffer的buffer size。 (没有检查)；输出：解密后的数据长度。
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_dec_rsa (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_gen_rand
*
* 功能描述  : 生成随机数
*
* 输入参数  : char *rand_data  随机数存放buffer
*             int len          期望得到的随机数字节数
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_gen_rand (char *rand_data, int len);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_secboot_supported
*
* 功能描述  : 当前版本是否支持安全启动
*
* 输入参数  : unsigned char *pu8Data 是否支持安全启动标志[1:支持   0:不支持]
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_secboot_supported (unsigned char *pu8Data);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_sec_started
*
* 功能描述  : 查询当前版本是否已经启用安全启动
*
* 输入参数  : unsigned char *pu8Data 是否已经启用安全启动标志[1:启用   0:未启用]
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_sec_started (unsigned char *pu8Data);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_start_secure
*
* 功能描述  : 启用安全启动
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_crypto_start_secure (void);

/*****************************************************************************
* 函 数 名  : mdrv_crypto_check_sec
*
* 功能描述  : 安全镜像判断
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 1，安全镜像；0，非安全镜像
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_crypto_check_sec (void);

#ifdef __cplusplus
}
#endif
#endif
