/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_OS_Openssl_Mem.c
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 适配ssl的内存申请和释放函数的实现
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : z00220931
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_OS_Memory.h"
/*lint -e767*/
#define THIS_FILE_ID PS_FILE_ID_BST_OS_OPENSSL_MEM_C
/*lint +e767*/

/******************************************************************************
   2 函数实现
******************************************************************************/
/*****************************************************************************
函 数 名  : BST_OPENSSL_Malloc
功能描述  : 调用BST模块的内存申请宏函数分配内存
输入参数  : ulSize
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_VOID *BST_OPENSSL_Malloc( BST_UINT32 ulSize )
{
    return BST_OS_MALLOC( ulSize );
}
/*****************************************************************************
函 数 名  : BST_OPENSSL_Free
功能描述  : 调用BST模块的内存释放宏函数释放内存
输入参数  : pData 要释放的内存
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_VOID BST_OPENSSL_Free( BST_VOID *pData )
{
    if( BST_NULL_PTR == pData )
    {
        return;
    }
    BST_OS_FREE( pData );
/*lint -e438*/
}
/*lint +e438*/
/*****************************************************************************
函 数 名  : BST_OPENSSL_Realloc
功能描述  : 重新分配空间
输入参数  : pMemAddress:原有空间的地址
            ulNewSize：新分配地址的大小
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_VOID *BST_OPENSSL_Realloc( BST_VOID *pMemAddress, BST_UINT32 ulNewSize )
{
    BST_VOID            *pNewPtr;

    if ( BST_NULL_PTR == pMemAddress )
    {
        return BST_OS_MALLOC( ulNewSize );
    }
    else if ( 0 == ulNewSize )
    {
        BST_OS_FREE( pMemAddress );
    }
    else
    {
        pNewPtr          = BST_OS_MALLOC( ulNewSize );
        if ( pNewPtr )
        {
            BST_OS_MEMCPY( pNewPtr, pMemAddress, ulNewSize );
            BST_OS_FREE( pMemAddress );
            /*lint -e438*/
            return pNewPtr;
            /*lint +e438*/
        }
    }
    /*lint -e438*/
    return BST_NULL_PTR;
    /*lint +e438*/
}

#if( BST_VER_TYPE == BST_UT_VER )
/*This functions are for UT test, Because we won't compile OpenSSL in UT enviroment.*/
#include "lwip/sockets.h"
#include  <openssl/evp.h>
#include "openssl/ssl.h"
int EVP_EncodeBlock(unsigned char *t, const unsigned char *f, int dlen)
{
    return 0;
}

int EVP_CIPHER_CTX_cleanup(EVP_CIPHER_CTX *c)
{
    return 0;
}

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl)
{
    return 0;
}

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl,
         const unsigned char *in, int inl)
{
    return 0;
}

int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,const EVP_CIPHER *cipher, ENGINE *impl,
        const unsigned char *key, const unsigned char *iv)
{
    return 0;
}

const EVP_CIPHER *EVP_aes_128_ecb(void)
{
    return NULL;
}

void EVP_CIPHER_CTX_init(EVP_CIPHER_CTX *ctx)
{
}

int EVP_DecodeBlock(unsigned char *t, const unsigned char *f, int n)
{
    return 0;
}

int EVP_DecryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl)
{
    return 0;
}

int EVP_DecryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl,
         const unsigned char *in, int inl)
{
    return 0;
}

int EVP_DecryptInit_ex(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher, ENGINE *impl,
         const unsigned char *key, const unsigned char *iv)
{
    return 0;
}


int SSL_set_fd(SSL *s,int fd)
{
    return 0;
}

SSL *SSL_new(SSL_CTX *ctx)
{
    return NULL;
}

void SSL_CTX_set_verify(SSL_CTX *ctx,int mode,int (*cb)(int, X509_STORE_CTX *))
{
}

SSL_CTX *SSL_CTX_new(const SSL_METHOD *meth)
{
    return NULL;
}

const SSL_METHOD *TLSv1_client_method(void)
{
    return NULL;
}

void SSL_load_error_strings(void)
{
}

int SSL_library_init(void)
{
    return 0;
}

int SSL_get_error(const SSL *s,int i)
{
    return 0;
}

int SSL_connect(SSL *s)
{
    return 0;
}

int SSL_get_fd(const SSL *s)
{
    return 0;
}

int SSL_write(SSL *s,const void *buf,int num)
{
    return 0;
}

int SSL_pending(const SSL *s)
{
    return 0;
}

int SSL_read(SSL *s,void *buf,int num)
{
    return 0;
}

void SSL_CTX_free(SSL_CTX *a)
{
}

void SSL_free(SSL *s)
{
}

int SSL_shutdown(SSL *s)
{
    return 0;
}

#endif
