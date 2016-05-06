/************************************************************************
 *                                                                      *
 *                             stac_def.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/20                                      *
 *  Author:             Shi  Yong                                       *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           STAC部分的私有宏                                *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_STAC == VRP_YES )

#ifndef     _STAC_PUB_H_
#define     _STAC_PUB_H_

#ifdef  __cplusplus
extern "C"{
#endif

/***************************************************************************/
#define STAC_FAIL 1
#define STAC_SUCCESS 0

/*压缩信息数据块*/
typedef struct tagStacCompressInfo {
    UCHAR    *pucInputStream;                     /* Pointer to input stream */
    UCHAR    *pucOutputStream;                    /* Pointer to output stream */
    VOS_UINT16   usInlen;                             /* Length of input stream */
    VOS_UINT16   usOutlen;                            /* Length of output stream */

    UCHAR    *pucBuffer;                          /* Pointer to history buffer */
    UCHAR    *pucHoldBuf;                         /* Pointer to hold buffer */
    VOS_UINT16   usBufferTail;                        /* Index of history buffer tail */
    VOS_UINT16   usHoldLen;                           /* Length of hold buffer */
    UCHAR   *pucOutput;                           /* Pointer to output buffer */
    struct  tagStacHashTable    *pstHashTable;    /* Pointer to hash table */
    UCHAR    ucBitMask;
    UCHAR    ucSequenceNum ;                      /* Current sequence number of the link */
} STAC_COMPRESSINFO_S;


/*解压信息数据块*/
typedef struct tagStacDecompressInfo {
    UCHAR    *pucInputStream;                     /* Pointer to input stream */
    UCHAR    *pucInput;                           /* Pointer to input buffer */
    VOS_UINT16   usInlen;                             /* Length of input stream */
    UCHAR    *pucOutputStream;                    /* Pointer to output stream */
    VOS_UINT16   usOutlen;                            /* Length of output stream */
    UCHAR    *pucBuffer;                          /* Pointer to history buffer */
    VOS_UINT16   usBufferTail;                        /* Index of history buffer tail */
    UCHAR    *pucHoldBuf;                         /* Pointer to hold buffer */
    VOS_UINT16   usHoldLen;                           /* Length of hold buffer */
    UCHAR    ucBitMask;
    UCHAR    ucSequenceNum ;                      /* Current sequence number of the link */
    UCHAR    ucResetReqSend ;
    VOS_UINT32    ulTimeOutTime;
    VOS_UINT32    ulTimeoutID;/*注意应初始化和在清除控制块时清除定时器*//*GGSNB03*//*要不要增加字段来记录数据字典的个数?*/
} STAC_DECOMPRESSINFO_S;
/***************************************************************************/

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif

#endif /*end of the *.h file*/
