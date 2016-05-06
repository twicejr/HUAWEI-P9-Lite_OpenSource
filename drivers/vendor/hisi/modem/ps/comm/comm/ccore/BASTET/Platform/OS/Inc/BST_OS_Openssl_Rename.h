/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_OS_Openssl_Rename.h
  版 本 号   : 初稿
  作    者   : z00220931
  生成日期   : 2014年06月04日
  最近修改   :
  功能描述   : SSL对外接口的适配
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月04日
    作    者   : z00220931
    修改内容   : 建立文件

******************************************************************************/
#ifndef __BST_OS_OPENSSL_RENAME_H__
#define __BST_OS_OPENSSL_RENAME_H__

#if( BST_VER_TYPE != BST_UT_VER )
#define SSL_set_fd                  BST_SSL_set_fd
#define SSL_library_init            BST_SSL_library_init
#define SSL_load_error_strings      BST_SSL_load_error_strings
#define TLSv1_client_method         BST_TLSv1_client_method
#define SSL_CTX_new                 BST_SSL_CTX_new
#define SSL_CTX_set_verify          BST_SSL_CTX_set_verify
#define SSL_new                     BST_SSL_new
#define SSL_get_fd                  BST_SSL_get_fd
#define SSL_connect                 BST_SSL_connect
#define SSL_get_error               BST_SSL_get_error
#define SSL_write                   BST_SSL_write
#define SSL_read                    BST_SSL_read
#define SSL_shutdown                BST_SSL_shutdown
#define SSL_free                    BST_SSL_free
#define SSL_CTX_free                BST_SSL_CTX_free
#define SSL_pending                 BST_SSL_pending
#define SSL_set_session             BST_SSL_set_session

#define EVP_EncodeBlock             BST_EVP_EncodeBlock
#define EVP_CIPHER_CTX_cleanup      BST_EVP_CIPHER_CTX_cleanup
#define EVP_EncryptFinal_ex         BST_EVP_EncryptFinal_ex
#define EVP_EncryptUpdate           BST_EVP_EncryptUpdate
#define EVP_EncryptInit_ex          BST_EVP_EncryptInit_ex
#define EVP_aes_128_ecb             BST_EVP_aes_128_ecb
#define EVP_CIPHER_CTX_init         BST_EVP_CIPHER_CTX_init
#define EVP_DecodeBlock             BST_EVP_DecodeBlock
#define EVP_DecryptFinal_ex         BST_EVP_DecryptFinal_ex
#define EVP_DecryptUpdate           BST_EVP_DecryptUpdate
#define EVP_DecryptInit_ex          BST_EVP_DecryptInit_ex
#endif

#endif

