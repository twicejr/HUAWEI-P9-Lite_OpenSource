/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              uio.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2000.4.3
*        Author: chenbin
*   Description: MID definition in socket
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-04-03   chenbin         created
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/
#ifndef _UIO_H
#define _UIO_H

#ifdef __cplusplus
extern "C"{
#endif

#define UIO_MAXIOV      1024         /* max 1K of iov's */
#define UIO_SMALLIOV    1            /* 8 on stack, else malloc */

/*IO Vector*/
typedef struct tagIOVEC 
{
    CHAR    *iov_pBase;    /* Base address. */
    LONG    iov_nLen;      /* Length. */
}IOVEC_S;

/* the length of IOVEC_S */
#define L_IOVEC_S        sizeof(IOVEC_S)

enum    uio_rw { UIO_READ, UIO_WRITE };


/* Segment flag values. */
enum uio_seg {
    UIO_USERSPACE,        /* from user data space */
    UIO_SYSSPACE,         /* from system space */
    UIO_USERISPACE        /* from user I space */
};

/*universal IO*/
typedef struct tagUIO 
{
    IOVEC_S     *uio_pIov;
    SHORT       uio_nIovCnt;
    UCHAR       ucPadding[2];
    LONG        uio_nOffSet;
    LONG        uio_nResid;
    enum uio_seg uio_eSegFlg;
    enum uio_rw  uio_eRw;
}UIO_S;
#define L_UIO_S        sizeof(UIO_S)


extern LONG UioMove(UIO_S *, CHAR *, LONG );


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
