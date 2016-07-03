
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

BST_VOID *BST_OPENSSL_Malloc( BST_UINT32 ulSize )
{
    return BST_OS_MALLOC( ulSize );
}

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
