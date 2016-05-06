
/**
* AES加解密接口封装
* 支持的密钥长度：256位
* 支持的模式：ECB
* 支持的填充方式：PKCS5Padding
*
* liulianxi, 2013-3-20
*/

/*#include <openssl/crypto.h>*/
#include "aes.h"
#include "string.h"
#include <stdio.h>
#include "v_lib.h"
#include "product_config.h"

/*lint -e701 -e702 -e732 -e734 -e713 -e737 -e734*/

#if (FEATURE_VSIM == FEATURE_ON)
#if ((VOS_WIN32 == VOS_OS_VER)||((VOS_RTOSCK == VOS_OS_VER)))
#include <malloc.h>
#endif
typedef unsigned char		word8;
typedef unsigned short		word16;
typedef unsigned long		word32;

#define MAXBC				(256/32)
#define MAXKC				(256/32)
#define MAXROUNDS			14

/*AES 256的数据块大小*/
#define BLOCK_LEN	16


/**
* PKCS5Padding方式填充
* 参数说明：
*	data: [in, out] 需转换的数据
*	dataLen: [in] 数据长度
* 返回值：
*	填充后的长度
*/
int Padding_PKCS5(unsigned char* data, int dataLen)
{
    int i = 0;
    int padLen = 0;

    padLen = BLOCK_LEN - dataLen % BLOCK_LEN;
    for (i=0; i < padLen; i++)
    {
        data[dataLen + i] = padLen;
    }
    return padLen + dataLen;
}

/**
* 去除PKCS5填充的内容
* 参数说明：
*	data: [in, out] 需转换的数据
*	dataLen: [in] 数据长度
* 返回值：
*	去除填充后的数据长度
*/
int Unpadding_PKCS5(unsigned char data[], int dataLen)
{
    int i = 0;
    int padLen = 0;

    padLen= data[dataLen - 1];
    if(padLen > BLOCK_LEN)
    {
        return dataLen;
    }

    for(i = 0; i < padLen; i++)
    {
        if(data[dataLen - 1 - i] != padLen)
        {
            return 0;
        }
        data[dataLen - 1 - i] = 0;
    }
    return dataLen - padLen;
}

/**
* AES加密
* 参数说明：
*	input: [in] 需要加密的明文
*	inputLen: [in] 明文长度
*	Key: [in] 加密密钥
*	KeyLen: [in] 密钥长度
*	cipher:[out] 加密后的密文数据
*	cipherLen: [in] cipher输出数据长度
* 返回值：
*	密文长度
*/
int AESEncrypt(word8 *input, int inputLen, word8 *Key, int keyBits, word8 *cipher, int cipherLen)
{
    int block;
    int blockNum;
    int PaddedLen = 0;
    AES_KEY AesKey;

    /*�����Ҫ���16�ֽ�*/
    word8 *plain = (word8 *)malloc(inputLen + 16);
    if(0 == plain)
    {
        return 0;
    }
    memcpy(plain, input, inputLen);

    PaddedLen = Padding_PKCS5(plain, inputLen);
    if(cipherLen < PaddedLen || PaddedLen == 0)
    {
        free(plain);
        return 0;
    }

    blockNum = PaddedLen / BLOCK_LEN;
    /*initKey(Key, KeyLen, tkey, keySched);*/

    private_AES_set_encrypt_key(Key, keyBits, &AesKey);
    for(block = 0; block < blockNum; block++)
    {
        USIMM_AES_encrypt(&plain[block * BLOCK_LEN], &cipher[block * BLOCK_LEN], &AesKey);
    }

    /*
    //ECBģʽ���ֿ���ܣ�ÿ���С16�ֽ�
    for(block = 0; block < blockNum; block++)
    {
        // convert plain
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                tplain[j][i] = plain[block * BLOCK_LEN + 4*i+j];
            }
        }
        // AES Encryption
        rijndaelEncrypt(tplain, KeyLen, BLOCK_LEN * 8, keySched);
        // convert result
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                cipher[block * BLOCK_LEN + 4*i+j] = tplain[j][i];
            }
        }
    }
    */

    free(plain);

    return PaddedLen;

}

/**
* AES解密
* 参数说明：
*	cipher:[in] 密文数据
*	cipherLen: [in] 密文长度
*	Key: [in] 加密密钥
*	KeyLen: [in] 密钥长度
*	plain: [out] 解密后的明文
*	plainLen: [in] plain数组长度
* 返回值：
*	非0: 解密后的明文长度
*	0: 错误
*/
int AESDecrypt(word8 *cipher, int cipherLen, word8 *Key, int keyBits, word8 *plain, int plainLen)
{
    int block;
    int blockNum;
    AES_KEY AesKey;

    if(plainLen < cipherLen)
    {
        return 0;
    }

    blockNum = cipherLen / 16;

    /*initKey(Key, KeyLen, tkey, keySched);*/
    private_AES_set_decrypt_key(Key, keyBits, &AesKey);
    for(block = 0; block < blockNum; block++)
    {
        USIMM_AES_decrypt(&cipher[block * BLOCK_LEN], &plain[block * BLOCK_LEN], &AesKey);
    }

    /*
    //ECBģʽ���ֿ���ܣ�ÿ���С16�ֽ�
    for(block = 0; block < blockNum; block++)
    {
        // convert plain
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                tplain[j][i] = cipher[block * BLOCK_LEN + 4*i+j];
            }
        }
        // AES Encryption
        rijndaelDecrypt(tplain, KeyLen,BLOCK_LEN * 8, keySched);

        // convert result
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                plain[block * BLOCK_LEN + 4*i+j] = tplain[j][i];
            }
        }
    }
    */

    return Unpadding_PKCS5(plain, cipherLen);

}

/**
* AES加密
* 参数说明：
*	input: [in] 需要加密的明文
*	inputLen: [in] 明文长度
*	Key: [in] 加密密钥
*	KeyLen: [in] 密钥长度
*	cipher:[out] 加密后的密文数据
*	cipherLen: [in] cipher输出数据长度
* 返回值：
*	密文长度
*/
int AESEncryptS(word8 *input, int inputLen, word8 *Key, int keyBits, word8 *cipher, int cipherLen)
{
    int block;
    int blockNum;
    int PaddedLen = 0;
    AES_KEY AesKey;

    /*锟斤拷锟斤拷锟揭拷锟斤拷16锟街斤拷*/
    word8 *plain = (word8 *)malloc(inputLen);
    if(0 == plain)
    {
        return 0;
    }
    memcpy(plain, input, inputLen);

    PaddedLen = inputLen;
    if(cipherLen < PaddedLen || PaddedLen == 0)
    {
        free(plain);
        return 0;
    }

    blockNum = PaddedLen / BLOCK_LEN;
    /*initKey(Key, KeyLen, tkey, keySched);*/

    private_AES_set_encrypt_key(Key, keyBits, &AesKey);
    for(block = 0; block < blockNum; block++)
    {
        USIMM_AES_encrypt(&plain[block * BLOCK_LEN], &cipher[block * BLOCK_LEN], &AesKey);
    }

    free(plain);

    return PaddedLen;

}


/**
* AES解密
* 参数说明：
*	cipher:[in] 密文数据
*	cipherLen: [in] 密文长度
*	Key: [in] 加密密钥
*	KeyLen: [in] 密钥长度
*	plain: [out] 解密后的明文
*	plainLen: [in] plain数组长度
* 返回值：
*	非0: 解密后的明文长度
*	0: 错误
*/
int AESDecryptS(word8 *cipher, int cipherLen, word8 *Key, int keyBits, word8 *plain, int plainLen)
{
    int block;
    int blockNum;
    AES_KEY AesKey;

    if(plainLen < cipherLen)
    {
        return 0;
    }

    blockNum = cipherLen / 16;

    /*initKey(Key, KeyLen, tkey, keySched);*/
    private_AES_set_decrypt_key(Key, keyBits, &AesKey);
    for(block = 0; block < blockNum; block++)
    {
        USIMM_AES_decrypt(&cipher[block * BLOCK_LEN], &plain[block * BLOCK_LEN], &AesKey);
    }


    return cipherLen;
}

#endif

/*lint +e701 +e702 +e732 +e734 +e713 +e737 +e734*/

