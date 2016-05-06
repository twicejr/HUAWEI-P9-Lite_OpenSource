/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPARingBuffer.c                                                 */
/*                                                                           */
/* Author: Windriver                                                         */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement ring buffer subroutine                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author: x51137                                                         */
/*    Modification: Adapt this file                                          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "hparingbuffer.h"

/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_HPA_RINGBUFFER_C

VOS_UINT8 g_ucHPABufferOccupiedFlag[HPA_MAX_RING_BUFFER_NUM] = {0};
HPA_RING  g_stHPAControlBlock[HPA_MAX_RING_BUFFER_NUM];

VOS_CHAR g_acHpaRingBuf[HPA_RING_BUF_SIZE];

/*the location of buf which should be allocated */
VOS_UINT32 g_ulHpaRingBufSuffix = 0;

/*******************************************************************************
*
* HPA_RealMemCopy - copy one buffer to another
*
* This routine copies the first <nbytes> characters from <source> to
* <destination>.  Overlapping buffers are handled correctly.  Copying is done
* in the most efficient way possible, which may include long-word, or even
* multiple-long-word moves on some architectures.  In general, the copy
* will be significantly faster if both buffers are long-word aligned.
* (For copying that is restricted to byte, word, or long-word moves, see
* the manual entries for bcopyBytes(), bcopyWords(), and bcopyLongs().)
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* SEE ALSO:
*/
void HPA_RealMemCopy( const char *source, char *destination, int nbytes )
{
    char *dstend;
    long *src;
    long *dst;
    int tmp = destination - source;

    if ( 0 == nbytes )
    {
        return;
    }

    if ( (tmp <= 0) || (tmp >= nbytes) )
    {
        /* forward copy */
        dstend = destination + nbytes;

        /* do byte copy if less than ten or alignment mismatch */
        if ((nbytes < 10) || (((int)destination ^ (int)source) & HPA_ARM_ALIGNMENT))
        {
            /*lint -e801 */
            goto byte_copy_fwd;
            /*lint +e801 */
        }

        /* if odd-aligned copy byte */
        while ((int)destination & HPA_ARM_ALIGNMENT)
        {
            *destination++ = *source++;
        }

        src = (long *) source;
        dst = (long *) destination;

        do
        {
            *dst++ = *src++;
        }while (((char *)dst + sizeof (long)) <= dstend);

        destination = (char *)dst;
        source      = (char *)src;

byte_copy_fwd:
        while (destination < dstend)
        {
            *destination++ = *source++;
        }
    }
    else
    {
        /* backward copy */
        dstend       = destination;
        destination += nbytes;
        source      += nbytes;

        /* do byte copy if less than ten or alignment mismatch */
        if ((nbytes < 10) || (((int)destination ^ (int)source) & HPA_ARM_ALIGNMENT))
        {
            /*lint -e801 */
            goto byte_copy_bwd;
            /*lint +e801 */
        }

        /* if odd-aligned copy byte */
        while ((int)destination & HPA_ARM_ALIGNMENT)
        {
            *--destination = *--source;
        }

        src = (long *) source;
        dst = (long *) destination;

        do
        {
            *--dst = *--src;
        }while (((char *)dst - sizeof(long)) >= dstend);

        destination = (char *)dst;
        source      = (char *)src;

byte_copy_bwd:
        while (destination > dstend)
        {
            *--destination = *--source;
        }
    }
}

/*******************************************************************************
*
* HPA_RingBufferCreate - create an empty ring buffer
*
* This routine creates a ring buffer of size <nbytes>, and initializes
* it.  Memory for the buffer is allocated from the system memory partition.
*
* RETURNS
* The ID of the ring buffer, or NULL if memory cannot be allocated.
*
* ERRNO: N/A.
*/
HPA_RING_ID HPA_RingBufferCreate( int nbytes )
{
    char         *buffer;
    HPA_RING_ID  ringId;
    VOS_INT      i;
    VOS_INT      lTempSufffix = VOS_NULL_WORD;
    VOS_INT      lLockLevel;

    lLockLevel = VOS_SplIMP();

    for ( i=HPA_MAX_RING_BUFFER_NUM -1; i>=0; i-- )
    {
        if ( VOS_FALSE == g_ucHPABufferOccupiedFlag[i] )
        {
            lTempSufffix = i;
            g_ucHPABufferOccupiedFlag[i] = VOS_TRUE;
            break;
        }
    }

    VOS_Splx(lLockLevel);

    if ( VOS_NULL_WORD == lTempSufffix )
    {
        return VOS_NULL_PTR;
    }

    /*
     * bump number of bytes requested because ring buffer algorithm
     * always leaves at least one empty byte in buffer
     */

    /*buffer = (char *) malloc ((unsigned) ++nbytes);*/

    buffer = (char *)VOS_StaticMemAlloc(g_acHpaRingBuf, sizeof(g_acHpaRingBuf),\
                            ((unsigned) ++nbytes), &g_ulHpaRingBufSuffix);

    if ( VOS_NULL_PTR == buffer )
    {
        lLockLevel = VOS_SplIMP();

        g_ucHPABufferOccupiedFlag[lTempSufffix] = VOS_FALSE;

        VOS_Splx(lLockLevel);

        return VOS_NULL_PTR;
    }

    ringId = &(g_stHPAControlBlock[lTempSufffix]);

    ringId->bufSize = nbytes;
    ringId->buf     = buffer;

    HPA_RingBufferFlush (ringId);

    return (ringId);
}

/*******************************************************************************
*
* HPA_RingBufferCreateNoMem - create an empty ring buffer without memory.
*
* This routine creates a ring buffer of size <nbytes>, and initializes
* it.  Memory for the buffer is allocated from the system memory partition.
*
* RETURNS
* The ID of the ring buffer, or NULL if memory cannot be allocated.
*
* ERRNO: N/A.
*/
HPA_RING_ID HPA_RingBufferCreateNoMem( char* buffer, int nbytes )
{
    HPA_RING_ID  ringId;
    VOS_INT      i;
    VOS_INT      lTempSufffix = VOS_NULL_WORD;
    VOS_INT      lLockLevel;

    lLockLevel = VOS_SplIMP();

    for ( i=HPA_MAX_RING_BUFFER_NUM -1; i>=0; i-- )
    {
        if ( VOS_FALSE == g_ucHPABufferOccupiedFlag[i] )
        {
            lTempSufffix = i;
            g_ucHPABufferOccupiedFlag[i] = VOS_TRUE;
            break;
        }
    }

    VOS_Splx(lLockLevel);

    if ( VOS_NULL_WORD == lTempSufffix )
    {
        return VOS_NULL_PTR;
    }

    ringId = &(g_stHPAControlBlock[lTempSufffix]);

    ringId->bufSize = nbytes;
    ringId->buf     = buffer;

    HPA_RingBufferFlush (ringId);

    return (ringId);
}

/*******************************************************************************
*
* HPA_RingBufferFlush - make a ring buffer empty
*
* This routine initializes a specified ring buffer to be empty.
* Any data currently in the buffer will be lost.
*
* RETURNS: N/A
*
* ERRNO: N/A.
*/
void HPA_RingBufferFlush( HPA_RING_ID ringId )
{
    VOS_INT         lLockLevel;

    lLockLevel = VOS_SplIMP();

    ringId->pToBuf   = 0;
    ringId->pFromBuf = 0;

    VOS_Splx(lLockLevel);
}

/*******************************************************************************
*
* HPA_RingBufferGet - get characters from a ring buffer
*
* This routine copies bytes from the ring buffer <rngId> into <buffer>.
* It copies as many bytes as are available in the ring, up to <maxbytes>.
* The bytes copied will be removed from the ring.
*
* RETURNS:
* The number of bytes actually received from the ring buffer;
* it may be zero if the ring buffer is empty at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_RingBufferGet( HPA_RING_ID rngId, char *buffer, int maxbytes )
{
    int bytesgot;
    int pToBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pToBuf = rngId->pToBuf;

    if (pToBuf >= rngId->pFromBuf)
    {
        /* pToBuf has not wrapped around */
        bytesgot = HPA_MIN(maxbytes, pToBuf - rngId->pFromBuf);
        HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
        rngId->pFromBuf += bytesgot;
    }
    else
    {
        /* pToBuf has wrapped around.  Grab chars up to the end of the
         * buffer, then wrap around if we need to. */
        bytesgot = HPA_MIN(maxbytes, rngId->bufSize - rngId->pFromBuf);
        HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
        pRngTmp = rngId->pFromBuf + bytesgot;

        /* If pFromBuf is equal to bufSize, we've read the entire buffer,
         * and need to wrap now.  If bytesgot < maxbytes, copy some more chars
         * in now. */
        if (pRngTmp == rngId->bufSize)
        {
            bytes2 = HPA_MIN(maxbytes - bytesgot, pToBuf);
            HPA_RealMemCopy (rngId->buf, buffer + bytesgot, bytes2);
            rngId->pFromBuf = bytes2;
            bytesgot += bytes2;
        }
        else
        {
            rngId->pFromBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesgot);
}

/*******************************************************************************
*
* HPA_RingBufferRemove - remove characters from a ring buffer
*
* This routine copies bytes from the ring buffer <rngId> into <buffer>.
* It copies as many bytes as are available in the ring, up to <maxbytes>.
* The bytes copied will be removed from the ring.
*
* RETURNS:
* The number of bytes actually received from the ring buffer;
* it may be zero if the ring buffer is empty at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_RingBufferRemove( HPA_RING_ID rngId, int maxbytes )
{
    int bytesgot;
    int pToBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pToBuf = rngId->pToBuf;

    if (pToBuf >= rngId->pFromBuf)
    {
        /* pToBuf has not wrapped around */
        bytesgot = HPA_MIN(maxbytes, pToBuf - rngId->pFromBuf);
        rngId->pFromBuf += bytesgot;
    }
    else
    {
        /* pToBuf has wrapped around.  Grab chars up to the end of the
         * buffer, then wrap around if we need to. */
        bytesgot = HPA_MIN(maxbytes, rngId->bufSize - rngId->pFromBuf);
        pRngTmp = rngId->pFromBuf + bytesgot;

        /* If pFromBuf is equal to bufSize, we've read the entire buffer,
         * and need to wrap now.  If bytesgot < maxbytes, copy some more chars
         * in now. */
        if (pRngTmp == rngId->bufSize)
        {
            bytes2 = HPA_MIN(maxbytes - bytesgot, pToBuf);
            rngId->pFromBuf = bytes2;
            bytesgot += bytes2;
        }
        else
        {
            rngId->pFromBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesgot);
}

#if 0
/*******************************************************************************
*
* HPA_RingBufferGetReserve - get characters from a ring buffer,but didn't change
*                            pFromBuf
* This routine copies bytes from the ring buffer <rngId> into <buffer>.
* It copies as many bytes as are available in the ring, up to <maxbytes>.
* The bytes copied will be removed from the ring.
*
* RETURNS:
* The number of bytes actually received from the ring buffer;
* it may be zero if the ring buffer is empty at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_RingBufferGetReserve( HPA_RING_ID rngId, char *buffer, int maxbytes )
{
    int bytesgot;
    int pToBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pToBuf = rngId->pToBuf;

    if (pToBuf >= rngId->pFromBuf)
    {
        /* pToBuf has not wrapped around */
        bytesgot = HPA_MIN(maxbytes, pToBuf - rngId->pFromBuf);
        HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
    }
    else
    {
        /* pToBuf has wrapped around.  Grab chars up to the end of the
         * buffer, then wrap around if we need to. */
        bytesgot = HPA_MIN(maxbytes, rngId->bufSize - rngId->pFromBuf);
        HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
        pRngTmp = rngId->pFromBuf + bytesgot;

        /* If pFromBuf is equal to bufSize, we've read the entire buffer,
         * and need to wrap now.  If bytesgot < maxbytes, copy some more chars
         * in now. */
        if (pRngTmp == rngId->bufSize)
        {
            bytes2 = HPA_MIN(maxbytes - bytesgot, pToBuf);
            HPA_RealMemCopy (rngId->buf, buffer + bytesgot, bytes2);
            bytesgot += bytes2;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesgot);
}

/*******************************************************************************
*
* HPA_DSPRingBufferGetReserve - get characters from a ring buffer which at DSP,
*                               but didn't change pFromBuf
* This routine copies bytes from the ring buffer <rngId> into <buffer>.
* It copies as many bytes as are available in the ring, up to <maxbytes>.
* The bytes copied will be removed from the ring.
*
* RETURNS:
* The number of bytes actually received from the ring buffer;
* it may be zero if the ring buffer is empty at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_DspRingBufferGetReserve( HPA_RING_ID rngId, char *buffer, int maxbytes )
{
    int bytesgot;
    int pToBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pToBuf = rngId->pToBuf;

    if (pToBuf >= rngId->pFromBuf)
    {
        /* pToBuf has not wrapped around */
        bytesgot = HPA_MIN(maxbytes, pToBuf - rngId->pFromBuf);
        /*HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);*/
        HPA_GetDspMem (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
    }
    else
    {
        /* pToBuf has wrapped around.  Grab chars up to the end of the
         * buffer, then wrap around if we need to. */
        bytesgot = HPA_MIN(maxbytes, rngId->bufSize - rngId->pFromBuf);
        /*HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);*/
        HPA_GetDspMem (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
        pRngTmp = rngId->pFromBuf + bytesgot;

        /* If pFromBuf is equal to bufSize, we've read the entire buffer,
         * and need to wrap now.  If bytesgot < maxbytes, copy some more chars
         * in now. */
        if (pRngTmp == rngId->bufSize)
        {
            bytes2 = HPA_MIN(maxbytes - bytesgot, pToBuf);
            /*HPA_RealMemCopy (rngId->buf, buffer + bytesgot, bytes2);*/
            HPA_GetDspMem (rngId->buf, buffer + bytesgot, bytes2);
            bytesgot += bytes2;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesgot);
}
#endif

/*******************************************************************************
*
* HPA_RingBufferPut - put bytes into a ring buffer
*
* This routine puts bytes from <buffer> into ring buffer <ringId>.  The
* specified number of bytes will be put into the ring, up to the number of
* bytes available in the ring.
*
* INTERNAL
* Always leaves at least one byte empty between pToBuf and pFromBuf, to
* eliminate ambiguities which could otherwise occur when the two pointers
* are equal.
*
* RETURNS:
* The number of bytes actually put into the ring buffer;
* it may be less than number requested, even zero,
* if there is insufficient room in the ring buffer at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_RingBufferPut( HPA_RING_ID rngId, char *buffer, int nbytes )
{
    int bytesput;
    int pFromBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pFromBuf = rngId->pFromBuf;

    if (pFromBuf > rngId->pToBuf)
    {
        /* pFromBuf is ahead of pToBuf.  We can fill up to two bytes
         * before it */
        bytesput = HPA_MIN(nbytes, pFromBuf - rngId->pToBuf - 1);
        HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput);
        rngId->pToBuf += bytesput;
    }
    else if (pFromBuf == 0)
    {
        /* pFromBuf is at the beginning of the buffer.  We can fill till
         * the next-to-last element */
        bytesput = HPA_MIN(nbytes, rngId->bufSize - rngId->pToBuf - 1);
        HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput);
        rngId->pToBuf += bytesput;
    }
    else
    {
        /* pFromBuf has wrapped around, and its not 0, so we can fill
         * at least to the end of the ring buffer.  Do so, then see if
         * we need to wrap and put more at the beginning of the buffer. */
        bytesput = HPA_MIN(nbytes, rngId->bufSize - rngId->pToBuf);
        HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput);
        pRngTmp = rngId->pToBuf + bytesput;

        if (pRngTmp == rngId->bufSize)
        {
            /* We need to wrap, and perhaps put some more chars */
            bytes2 = HPA_MIN(nbytes - bytesput, pFromBuf - 1);
            HPA_RealMemCopy (buffer + bytesput, rngId->buf, bytes2);
            rngId->pToBuf = bytes2;
            bytesput += bytes2;
        }
        else
        {
            rngId->pToBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesput);
}

/*******************************************************************************
*
* HPA_RingBufferIsEmpty - test if a ring buffer is empty
*
* This routine determines if a specified ring buffer is empty.
*
* RETURNS:
* TRUE if empty, FALSE if not.
*
* ERRNO: N/A.
*/
VOS_BOOL HPA_RingBufferIsEmpty( HPA_RING_ID ringId )
{
    VOS_INT         lLockLevel;
    VOS_BOOL        bIsEmpty;

    lLockLevel = VOS_SplIMP();

    bIsEmpty = (ringId->pToBuf == ringId->pFromBuf);

    VOS_Splx(lLockLevel);

    return bIsEmpty;
}

/*******************************************************************************
*
* HPA_RingBufferIsFull - test if a ring buffer is full (no more room)
*
* This routine determines if a specified ring buffer is completely full.
*
* RETURNS:
* TRUE if full, FALSE if not.
*
* ERRNO: N/A.
*/
VOS_BOOL HPA_RingBufferIsFull( HPA_RING_ID ringId )
{
    VOS_INT         lLockLevel;
    int             n;
    VOS_BOOL        bIsEmpty;


    lLockLevel = VOS_SplIMP();

    n = ringId->pToBuf - ringId->pFromBuf + 1;
    bIsEmpty = ((n == 0) || (n == ringId->bufSize));

    VOS_Splx(lLockLevel);

    return bIsEmpty;
}

/*******************************************************************************
*
* HPA_RingBufferFreeBytes - determine the number of free bytes in a ring buffer
*
* This routine determines the number of bytes currently unused in a specified
* ring buffer.
*
* RETURNS: The number of unused bytes in the ring buffer.
*
* ERRNO: N/A.
*/
int HPA_RingBufferFreeBytes( HPA_RING_ID ringId)
{
    VOS_INT         lLockLevel;
    int             n;

    lLockLevel = VOS_SplIMP();

    n = ringId->pFromBuf - ringId->pToBuf - 1;

    if (n < 0)
    {
        n += ringId->bufSize;
    }

    VOS_Splx(lLockLevel);

    return (n);
}

/*******************************************************************************
*
* HPA_RingBufferNBytes - determine the number of bytes in a ring buffer
*
* This routine determines the number of bytes currently in a specified
* ring buffer.
*
* RETURNS: The number of bytes filled in the ring buffer.
*
* ERRNO: N/A.
*/
int HPA_RingBufferNBytes( HPA_RING_ID ringId )
{
    VOS_INT         lLockLevel;
    int             n;

    lLockLevel = VOS_SplIMP();

    n = ringId->pToBuf - ringId->pFromBuf;

    if (n < 0)
    {
        n += ringId->bufSize;
    }

    VOS_Splx(lLockLevel);

    return (n);
}

/*******************************************************************************
*
* HPA_RingBufferNBytes - determine the number of bytes in a ring buffer
*
* This routine determines the number of bytes currently in a specified
* ring buffer.
* destination cachedisable
*
* RETURNS: The number of bytes filled in the ring buffer.
*
* ERRNO: N/A.
*/
void HPA_PutDspMem( const char *source, char *destination, int nbytes )
{
    char *dstend;
    long *src;
    volatile long *dst;
    short *ussrc;
    volatile short *usdst;

    if ( 0 == nbytes )
    {
        return;
    }

    if ( nbytes & HPA_EVEN_NUBER )
    {
        /*lint -e534*/
        LogPrint("HPA_PutDspMem Length is odd.\r\n");
        /*lint +e534*/
        return;
    }

    /* alignment mismatch */
    if ( (((int)destination ^ (int)source) & HPA_ARM_ALIGNMENT))
    {
        /* 2 bytes copy */
        if ( ((int)destination & HPA_EVEN_NUBER)
            || ((int)source & HPA_EVEN_NUBER) )
        {
            /*lint -e534*/
            LogPrint("HPA_PutDspMem Sync mismatch.\r\n");
            /*lint +e534*/
            return;
        }

        dstend = destination + nbytes;

        ussrc = (short *)source;
        usdst = (volatile short *)destination;

        while (((char *)usdst + sizeof(short)) <= dstend)
        {
            *usdst++ = *ussrc++;
        }

        return;
    }

    if ( (int)destination & HPA_EVEN_NUBER )
    {
        /*lint -e534*/
        LogPrint("HPA_PutDspMem alignment mismatch.\r\n");
        /*lint +e534*/
        return;
    }

    /* forward copy */
    dstend = destination + nbytes;

    if ( (int)destination & HPA_ARM_ALIGNMENT )
    {
        ussrc = (short *)source;
        usdst = (volatile short *)destination;
        *usdst++ = *ussrc++;
        src = (long *)ussrc;
        dst = (volatile long *)usdst;
    }
    else
    {
        src = (long *)source;
        dst = (volatile long *)destination;
    }

    while (((char *)dst + sizeof (long)) <= dstend)
    {
        *dst++ = *src++;
    }

    if ( (char *)dst < dstend )
    {
        usdst = (volatile short *)dst;
        ussrc = (short *)src;
        *usdst = *ussrc;
    }
}

/*******************************************************************************
*
* HPA_GetDspMem - copy one buffer to another
*
* This routine copies the first <nbytes> characters from <source> to
* <destination>.  Overlapping buffers are handled correctly.  Copying is done
* in the most efficient way possible, which may include long-word, or even
* multiple-long-word moves on some architectures.  In general, the copy
* will be significantly faster if both buffers are long-word aligned.
* (For copying that is restricted to byte, word, or long-word moves, see
* the manual entries for bcopyBytes(), bcopyWords(), and bcopyLongs().)
*
* source cachedisable
* RETURNS: N/A
*
* ERRNO: N/A
*
* SEE ALSO:
*/
void HPA_GetDspMem( const char *source, char *destination, int nbytes )
{
    char *dstend;
    volatile long *src;
    long *dst;
    volatile short *ussrc;
    short *usdst;

    if ( 0 == nbytes )
    {
        return;
    }

    if ( nbytes & HPA_EVEN_NUBER )
    {
        /*lint -e534*/
        LogPrint("HPA_GetDspMem Length is odd.\r\n");
        /*lint +e534*/
        return;
    }

    /* alignment mismatch */
    if ( (((int)destination ^ (int)source) & HPA_ARM_ALIGNMENT))
    {
        /* 2 bytes copy */
        if ( ((int)destination & HPA_EVEN_NUBER)
            || ((int)source & HPA_EVEN_NUBER) )
        {
            /*lint -e534*/
            LogPrint("HPA_GetDspMem Sync mismatch.\r\n");
            /*lint +e534*/
            return;
        }

        dstend = destination + nbytes;

        ussrc = (volatile short *)source;
        usdst = (short *)destination;

        while (((char *)usdst + sizeof(short)) <= dstend)
        {
            *usdst++ = *ussrc++;
        }

        return;
    }

    if ( (int)destination & HPA_EVEN_NUBER )
    {
        /*lint -e534*/
        LogPrint("HPA_GetDspMem alignment mismatch.\r\n");
        /*lint +e534*/
        return;
    }

    /* forward copy */
    dstend = destination + nbytes;

    if ( (int)destination & HPA_ARM_ALIGNMENT )
    {
        ussrc = (volatile short *)source;
        usdst = (short *)destination;
        *usdst++ = *ussrc++;
        src = (volatile long *)ussrc;
        dst = (long *)usdst;
    }
    else
    {
        src = (volatile long *)source;
        dst = (long *)destination;
    }

    while (((char *)dst + sizeof (long)) <= dstend)
    {
        *dst++ = *src++;
    }

    if ( (char *)dst < dstend )
    {
        usdst = (short *)dst;
        ussrc = (volatile short *)src;
        *usdst = *ussrc;
    }
}

#if 0
/*******************************************************************************
*
* HPA_RingBufferPutDsp - put DSP's bytes into a ring buffer
*
* This routine puts bytes from <buffer> into ring buffer <ringId>.  The
* specified number of bytes will be put into the ring, up to the number of
* bytes available in the ring.
*
* INTERNAL
* Always leaves at least one byte empty between pToBuf and pFromBuf, to
* eliminate ambiguities which could otherwise occur when the two pointers
* are equal.
*
* RETURNS:
* The number of bytes actually put into the ring buffer;
* it may be less than number requested, even zero,
* if there is insufficient room in the ring buffer at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_RingBufferPutDsp( HPA_RING_ID rngId, char *buffer, int nbytes )
{
    int bytesput;
    int pFromBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pFromBuf = rngId->pFromBuf;

    if (pFromBuf > rngId->pToBuf)
    {
        /* pFromBuf is ahead of pToBuf.  We can fill up to two bytes
         * before it */

        bytesput = HPA_MIN(nbytes, pFromBuf - rngId->pToBuf - 1);
        /* HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput); */
        HPA_GetDspMem (buffer, &rngId->buf [rngId->pToBuf], bytesput);

        rngId->pToBuf += bytesput;
    }
    else if (pFromBuf == 0)
    {
        /* pFromBuf is at the beginning of the buffer.  We can fill till
         * the next-to-last element */

        bytesput = HPA_MIN(nbytes, rngId->bufSize - rngId->pToBuf - 1);
        /* HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput); */
        HPA_GetDspMem (buffer, &rngId->buf [rngId->pToBuf], bytesput);
        rngId->pToBuf += bytesput;
    }
    else
    {
        /* pFromBuf has wrapped around, and its not 0, so we can fill
         * at least to the end of the ring buffer.  Do so, then see if
         * we need to wrap and put more at the beginning of the buffer. */

        bytesput = HPA_MIN(nbytes, rngId->bufSize - rngId->pToBuf);
        /* HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput); */
        HPA_GetDspMem (buffer, &rngId->buf [rngId->pToBuf], bytesput);
        pRngTmp = rngId->pToBuf + bytesput;

        if (pRngTmp == rngId->bufSize)
        {
            /* We need to wrap, and perhaps put some more chars */

            bytes2 = HPA_MIN(nbytes - bytesput, pFromBuf - 1);
            /* HPA_RealMemCopy (buffer + bytesput, rngId->buf, bytes2); */
            HPA_GetDspMem (buffer + bytesput, rngId->buf, bytes2);
            rngId->pToBuf = bytes2;
            bytesput += bytes2;
        }
        else
        {
            rngId->pToBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesput);
}

/*******************************************************************************
*
* HPA_DspRingBufferPut - put bytes into a ring buffer which at DSP
*
* This routine puts bytes from <buffer> into ring buffer <ringId>.  The
* specified number of bytes will be put into the ring, up to the number of
* bytes available in the ring.
*
* INTERNAL
* Always leaves at least one byte empty between pToBuf and pFromBuf, to
* eliminate ambiguities which could otherwise occur when the two pointers
* are equal.
*
* RETURNS:
* The number of bytes actually put into the ring buffer;
* it may be less than number requested, even zero,
* if there is insufficient room in the ring buffer at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_DspRingBufferPut( HPA_RING_ID rngId, char *buffer, int nbytes )
{
    int bytesput;
    int pFromBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pFromBuf = rngId->pFromBuf;

    if (pFromBuf > rngId->pToBuf)
    {
        /* pFromBuf is ahead of pToBuf.  We can fill up to two bytes
         * before it */

        bytesput = HPA_MIN(nbytes, pFromBuf - rngId->pToBuf - 1);
        /* HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput); */
        HPA_PutDspMem (buffer, &rngId->buf [rngId->pToBuf], bytesput);

        rngId->pToBuf += bytesput;
    }
    else if (pFromBuf == 0)
    {
        /* pFromBuf is at the beginning of the buffer.  We can fill till
         * the next-to-last element */

        bytesput = HPA_MIN(nbytes, rngId->bufSize - rngId->pToBuf - 1);
        /* HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput); */
        HPA_PutDspMem (buffer, &rngId->buf [rngId->pToBuf], bytesput);
        rngId->pToBuf += bytesput;
    }
    else
    {
        /* pFromBuf has wrapped around, and its not 0, so we can fill
         * at least to the end of the ring buffer.  Do so, then see if
         * we need to wrap and put more at the beginning of the buffer. */

        bytesput = HPA_MIN(nbytes, rngId->bufSize - rngId->pToBuf);
        /* HPA_RealMemCopy (buffer, &rngId->buf [rngId->pToBuf], bytesput); */
        HPA_PutDspMem (buffer, &rngId->buf [rngId->pToBuf], bytesput);
        pRngTmp = rngId->pToBuf + bytesput;

        if (pRngTmp == rngId->bufSize)
        {
            /* We need to wrap, and perhaps put some more chars */

            bytes2 = HPA_MIN(nbytes - bytesput, pFromBuf - 1);
            /* HPA_RealMemCopy (buffer + bytesput, rngId->buf, bytes2); */
            HPA_PutDspMem (buffer + bytesput, rngId->buf, bytes2);
            rngId->pToBuf = bytes2;
            bytesput += bytes2;
        }
        else
        {
            rngId->pToBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesput);
}

/*******************************************************************************
*
* HPA_RingBufferGetDsp - get DSP's characters from a ring buffer
*
* This routine copies bytes from the ring buffer <rngId> into <buffer>.
* It copies as many bytes as are available in the ring, up to <maxbytes>.
* The bytes copied will be removed from the ring.
*
* RETURNS:
* The number of bytes actually received from the ring buffer;
* it may be zero if the ring buffer is empty at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_RingBufferGetDsp( HPA_RING_ID rngId, char *buffer, int maxbytes )
{
    int bytesgot;
    int pToBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pToBuf = rngId->pToBuf;

    if (pToBuf >= rngId->pFromBuf)
    {
        /* pToBuf has not wrapped around */

        bytesgot = HPA_MIN(maxbytes, pToBuf - rngId->pFromBuf);
        /* HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot); */
        HPA_PutDspMem (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
        rngId->pFromBuf += bytesgot;
    }
    else
    {
        /* pToBuf has wrapped around.  Grab chars up to the end of the
         * buffer, then wrap around if we need to. */

        bytesgot = HPA_MIN(maxbytes, rngId->bufSize - rngId->pFromBuf);
        /* HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot); */
        HPA_PutDspMem (&rngId->buf [rngId->pFromBuf], buffer, bytesgot);
        pRngTmp = rngId->pFromBuf + bytesgot;

        /* If pFromBuf is equal to bufSize, we've read the entire buffer,
         * and need to wrap now.  If bytesgot < maxbytes, copy some more chars
         * in now. */

        if (pRngTmp == rngId->bufSize)
        {
            bytes2 = HPA_MIN(maxbytes - bytesgot, pToBuf);
            /* HPA_RealMemCopy (rngId->buf, buffer + bytesgot, bytes2); */
            HPA_PutDspMem (rngId->buf, buffer + bytesgot, bytes2);
            rngId->pFromBuf = bytes2;
            bytesgot += bytes2;
        }
        else
        {
            rngId->pFromBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesgot);
}

/*******************************************************************************
*
* HPA_RingBufferPutDspRing - put DSP's ring into a ARM's ring buffer
*
* This routine puts bytes from <buffer> into ring buffer <ringId>.  The
* specified number of bytes will be put into the ring, up to the number of
* bytes available in the ring.
*
* INTERNAL
* Always leaves at least one byte empty between pToBuf and pFromBuf, to
* eliminate ambiguities which could otherwise occur when the two pointers
* are equal.
*
* RETURNS:
* The number of bytes actually put into the ring buffer;
* it may be less than number requested, even zero,
* if there is insufficient room in the ring buffer at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_DspRingToArmRing( HPA_RING_ID rngDspId, HPA_RING_ID rngArmId, int maxbytes )
{
    int bytesgot;
    int pToBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pToBuf = rngDspId->pToBuf;

    if (pToBuf >= rngDspId->pFromBuf)
    {
        /* pToBuf has not wrapped around */

        bytesgot = HPA_MIN(maxbytes, pToBuf - rngDspId->pFromBuf);
        /* HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot); */
        HPA_RingBufferPutDsp(rngArmId, &rngDspId->buf [rngDspId->pFromBuf], bytesgot);
        rngDspId->pFromBuf += bytesgot;
    }
    else
    {
        /* pToBuf has wrapped around.  Grab chars up to the end of the
         * buffer, then wrap around if we need to. */

        bytesgot = HPA_MIN(maxbytes, rngDspId->bufSize - rngDspId->pFromBuf);
        /* HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot); */
        HPA_RingBufferPutDsp(rngArmId, &rngDspId->buf [rngDspId->pFromBuf], bytesgot);
        pRngTmp = rngDspId->pFromBuf + bytesgot;

        /* If pFromBuf is equal to bufSize, we've read the entire buffer,
         * and need to wrap now.  If bytesgot < maxbytes, copy some more chars
         * in now. */

        if (pRngTmp == rngDspId->bufSize)
        {
            bytes2 = HPA_MIN(maxbytes - bytesgot, pToBuf);
            /* HPA_RealMemCopy (rngId->buf, buffer + bytesgot, bytes2); */
            HPA_RingBufferPutDsp(rngArmId, rngDspId->buf, bytes2);
            rngDspId->pFromBuf = bytes2;
            bytesgot += bytes2;
        }
        else
        {
            rngDspId->pFromBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesgot);
}

/*******************************************************************************
*
* HPA_RingBufferGetDsp - get DSP's ringbuffer from a ARM's ring buffer
*
* This routine copies bytes from the ring buffer <rngId> into <buffer>.
* It copies as many bytes as are available in the ring, up to <maxbytes>.
* The bytes copied will be removed from the ring.
*
* RETURNS:
* The number of bytes actually received from the ring buffer;
* it may be zero if the ring buffer is empty at the time of the call.
*
* ERRNO: N/A.
*/
int HPA_ArmRingToDspRing( HPA_RING_ID rngArmId, HPA_RING_ID rngDspId, int maxbytes )
{
    int bytesgot;
    int pToBuf;
    int bytes2;
    int pRngTmp;
    int lLockLevel;

    lLockLevel = VOS_SplIMP();

    pToBuf = rngArmId->pToBuf;

    if (pToBuf >= rngArmId->pFromBuf)
    {
        /* pToBuf has not wrapped around */

        bytesgot = HPA_MIN(maxbytes, pToBuf - rngArmId->pFromBuf);
        /* HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot); */
        HPA_DspRingBufferPut(rngDspId, &rngArmId->buf [rngArmId->pFromBuf], bytesgot);
        rngArmId->pFromBuf += bytesgot;
    }
    else
    {
        /* pToBuf has wrapped around.  Grab chars up to the end of the
         * buffer, then wrap around if we need to. */

        bytesgot = HPA_MIN(maxbytes, rngArmId->bufSize - rngArmId->pFromBuf);
        /* HPA_RealMemCopy (&rngId->buf [rngId->pFromBuf], buffer, bytesgot); */
        HPA_DspRingBufferPut(rngDspId, &rngArmId->buf [rngArmId->pFromBuf], bytesgot);
        pRngTmp = rngArmId->pFromBuf + bytesgot;

        /* If pFromBuf is equal to bufSize, we've read the entire buffer,
         * and need to wrap now.  If bytesgot < maxbytes, copy some more chars
         * in now. */

        if (pRngTmp == rngArmId->bufSize)
        {
            bytes2 = HPA_MIN(maxbytes - bytesgot, pToBuf);
            /* HPA_RealMemCopy (rngId->buf, buffer + bytesgot, bytes2); */
            HPA_DspRingBufferPut(rngDspId, rngArmId->buf, bytes2);
            rngArmId->pFromBuf = bytes2;
            bytesgot += bytes2;
        }
        else
        {
            rngArmId->pFromBuf = pRngTmp;
        }
    }

    VOS_Splx(lLockLevel);

    return (bytesgot);
}
#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif /* __cpluscplus */
#endif /* __cpluscplus */

