
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include "BST_Typedefine.h"
/*lint -e767*/
#define THIS_FILE_ID PS_FILE_ID_BST_PAL_OPENSSL_FILE_C
/*lint +e767*/
/******************************************************************************
   2 函数实现
******************************************************************************/

FILE *fopen(
    const char *_name,
    const char *_type )
{
    return BST_NULL_PTR;
}

int fseek(
    FILE *str,
    long off,
    int smode )
{
    return 0;
}

long ftell(
    FILE *str )
{
    return 0;
}

size_t fread(
    _PTR ptr,
    size_t size,
    size_t nelem,
    FILE *str )
{
    return 0;
}

char * fgets(
    char    *buf,   /* where to store characters */
    int     n,      /* no. of bytes to read + 1 */
    FILE    *fp     /* stream to read from */
)
{
    return BST_NULL_PTR;
}

void perror(
    const char *__s /*error string*/
)
{
}

int vfprintf(
    FILE        *stream,
    const char  *format,
    __VALIST    param
    )
{
    return 1;
}

int fprintf(
    FILE        *fp,    /* stream to write to */
    const char  *fmt,   /* format string */
    ...                 /* optional arguments to format string */
)
{
    return 1;
}

int sscanf(
    const char *buffer,
    const char *format,
    ...)
{
    return 1;
}
#ifndef _WIN32

void exit(
    int status )
{
}

_sig_func_ptr signal(int sig, _sig_func_ptr fun)
{
    return BST_NULL_PTR;
}
#endif