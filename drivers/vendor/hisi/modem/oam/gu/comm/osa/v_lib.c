/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_lib.c                                                         */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement general function                                   */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "v_lib.h"
#include "v_blkMem.h"
#include "v_IO.h"
#include "v_timer.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_LIB_C
/*lint +e767 modify:x51137; review:h59254; */


#define COPY_LONG_SIZE          ( sizeof(VOS_UINT32) )
#define COPY_WORD_SIZE          ( sizeof(VOS_UINT16) )
#define COPY_LONG_MARK          ( COPY_LONG_SIZE - 1 )
#define COPY_WORD_MARK          ( COPY_WORD_SIZE - 1 )

#define MAX_SHIFT_NUM           32
#define MASK_BIT_ALL            0xFFFFFFFF
#define MASK_BIT_32             0x80000000
#define MASK_BIT_01             0x00000001
#define MASK_HI_NBITS(x)        (MASK_BIT_ALL << (MAX_SHIFT_NUM - (x)))

#define VOS_STOL(S)             (VOS_UINT_PTR)(S)


typedef enum _bit64CompareResult
{
    BIT64_GREAT,
    BIT64_EQUAL,
    BIT64_LESS
} bit64CompareResult;


#define BIT64_COMPARE(argAHi, argALo, argBHi, argBLo, result) \
    do \
    { \
        if ((argAHi) > (argBHi)) \
        { \
            result = BIT64_GREAT; \
        } \
        else if (((argAHi) == (argBHi)) && ((argALo) > (argBLo))) \
        { \
            result = BIT64_GREAT; \
        } \
        else if (((argAHi) == (argBHi)) && ((argALo) == (argBLo))) \
        { \
            result = BIT64_EQUAL; \
        } \
        else \
        { \
            result = BIT64_LESS; \
        } \
    } while (0)

#define BIT64_ADD(argAHi, argALo, argBHi, argBLo) \
    do \
    { \
        if ((argALo) > 0xFFFFFFFF - (argBLo)) \
        { \
            (argAHi) += ((argBHi) + 1); \
        } \
        else \
        { \
            (argAHi) += (argBHi); \
        } \
        (argALo) += (argBLo); \
    } while (0)

/* Notes: we assumed argA always great than or equal to argB */
#define BIT64_SUB(argAHi, argALo, argBHi, argBLo) \
    do \
    { \
        if ((argALo) < (argBLo)) \
        { \
            (argAHi) -= ((argBHi) + 1); \
        } \
        else \
        { \
            (argAHi) -= (argBHi); \
        } \
        (argALo) -= (argBLo); \
    } while (0)



/* the seed of radom */
static VOS_UINT32 g_ulVosRadomSeed = 0;

VOS_UINT32        g_ulErrorNo = 0;                  /* 存放错误码 */

#if (VOS_VXWORKS == VOS_OS_VER)
extern int errnoSet(int errorValue);
#endif

#if ((VOS_WIN32 == VOS_OS_VER)||(VOS_NUCLEUS== VOS_OS_VER)||(VOS_LINUX == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))
int errnoSet(int errorValue)
{
    return 0;
}
#endif

/******************************************************************************
 Function    : V_SetErrorNo
 Description : Set global error number.
 Input       : ulErrorNo -- Error number
 Return      : VOS_OK on Success and VOS_ERROR on Failure
 *****************************************************************************/
VOS_UINT32 V_SetErrorNo( VOS_UINT32 ulErrorNo,
                         VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    g_ulErrorNo = ulErrorNo;
    /*lint -e534*/
    LogPrint3("# VOS_SetErrorNo, F:%d, L:%d, ErrNo:%x.\r\n",
        (VOS_INT)ulFileID, usLineNo, (VOS_INT)ulErrorNo);
    /*lint +e534*/
    return VOS_OK;
}

/******************************************************************************
 Function    : VOS_GetErrorNo
 Description : Get global error number.
 Input       : None
 Output      : None
 Return      : Error number of current task
 *****************************************************************************/
VOS_UINT32 VOS_GetErrorNo(VOS_VOID)
{
    return g_ulErrorNo;
}

/*****************************************************************************
 Function   : VOS_CharIsUpper
 Description:
 Input      :
 Output     :
 Return     :
 *****************************************************************************/
VOS_BOOL VOS_CharIsUpper( VOS_CHAR Char )
{
    if ( Char >= 'A' && Char <= 'Z' )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function   : VOS_CharIsLower
 Description:
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_BOOL VOS_CharIsLower( VOS_CHAR Char )
{
    if ( Char >= 'a' && Char <= 'z' )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function   : VOS_CharToUpper
 Description:
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_CHAR VOS_CharToUpper( VOS_CHAR Char )
{
    if ( VOS_CharIsLower( Char ) )
    {
        Char = (VOS_CHAR)(Char + ( 'A' - 'a' ));
    }

    return Char;
}

/*****************************************************************************
 Function   : VOS_CharToLower
 Description:
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_CHAR VOS_CharToLower( VOS_CHAR Char )
{
    if ( VOS_CharIsUpper( Char ) )
    {
        Char = (VOS_CHAR)(Char - ( 'A' - 'a' ));
    }

    return Char;
}

#ifndef DMT
/*****************************************************************************
 Function   : VOS_StrNiCmp
 Description:
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT8 VOS_StrNiCmp( VOS_CHAR * Str1, VOS_CHAR * Str2, VOS_SIZE_T Length )
{
    VOS_CHAR Char1, Char2;
    VOS_CHAR *pTempStr1 = Str1;
    VOS_CHAR *pTempStr2 = Str2;

    if( ( VOS_NULL_PTR == Str1 ) || ( VOS_NULL_PTR == Str2 ) )
    {
        return 0;
    }

    Char1 = 0;
    Char2 = 0;

    while( Length > 0 )
    {
        Length--;
        Char1 = *pTempStr1;
        Char2 = *pTempStr2;
        pTempStr1++;
        pTempStr2++;

        if( ( !Char1 ) || ( !Char2 ) )
        {
            break;
        }

        if( Char1 == Char2 )
        {
            continue;
        }

        if( ( Char1 >= 'a' && Char1 <= 'z' ) && ( Char2 >= 'A' && Char2 <= 'Z' ) )
        {
            if( ( Char1 - Char2 ) != 0x20 )
            {
                break;
            }
        }
        else if( ( Char1 >= 'A' && Char1 <= 'Z' ) && ( Char2 >= 'a' && Char2 <= 'z' ) )
        {
            if( ( Char2 - Char1 ) != 0x20 )
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    Char1 = VOS_CharToLower( Char1 );
    Char2 = VOS_CharToLower( Char2 );

    return (VOS_INT8)( ( VOS_INT8 )Char1 - ( VOS_INT8 )Char2 );
}
#endif /* DMT */

/*****************************************************************************
 Function   : VOS_StrToUpper
 Description: Transform a string to upper
 Input      : Str -- String
 Output     : None
 Return     : None
 *****************************************************************************/
VOS_VOID VOS_StrToUpper( VOS_CHAR* Str )
{
    VOS_CHAR *pTempStr = Str;

    if( VOS_NULL_PTR == Str )
    {
        return;
    }

    while( *pTempStr )
    {
        *pTempStr  = VOS_CharToUpper( *pTempStr );
        pTempStr++;
    }

    return;
}

/*****************************************************************************
 Function   : VOS_StrToLower
 Description: Transform a string to lower
 Input      : Str -- String
 Output     : None
 Return     : None
 *****************************************************************************/
VOS_VOID VOS_StrToLower( VOS_CHAR* Str )
{
    VOS_CHAR *pTempStr = Str;

    if( VOS_NULL_PTR == Str )
    {
        return;
    }

    while( *pTempStr )
    {
        *pTempStr = VOS_CharToLower( *pTempStr );
        pTempStr++;
    }

    return;
}


/*****************************************************************************
 Function   : VOS_StrCpy
 Description: copy one string to another
 Input      : Dest -- string to copy to
              Src  -- string to copy from
 Output     :
 Return     : A pointer to Dest
 Other      :
 *****************************************************************************/
VOS_CHAR *VOS_StrCpy( VOS_CHAR *Dest, VOS_CHAR *Src )
{
    char *tmp = Dest;
    char *pSrctmp = Src;

    if( ( VOS_NULL_PTR == Dest ) || ( VOS_NULL_PTR == Src ) )
    {
        return Dest;
    }

    while ((*tmp++ = *pSrctmp++) != '\0')
        /* nothing */;

    return Dest;
}

/*****************************************************************************
 Function   : VOS_StrLen
 Description: determine the length of a string
 Input      : Str --- string
 Output     :
 Return     : The number of non-null characters in the string
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_StrLen( VOS_CHAR * Str )
{
    const char *sc;

    if( VOS_NULL_PTR == Str )
    {
        return 0;
    }

    for (sc = Str; *sc != '\0'; ++sc)
        /* nothing */;
    return (VOS_UINT32)(VOS_STOL(sc) - VOS_STOL(Str));
}

/*****************************************************************************
 Function   : VOS_StrRChr
 Description: find the last occurrence of a character in a string
 Input      : Str  --- string to search
              Char --- character to look for
 Output     :
 Return     : A pointer to the last occurrence of the character, or
              VOS_NULL_PTR if the character is not found.
 Other      :
 *****************************************************************************/
VOS_CHAR* VOS_StrRChr( VOS_CHAR * Str, VOS_CHAR Char )
{
    VOS_CHAR * Temp = VOS_NULL_PTR;

    if( VOS_NULL_PTR == Str )
    {
        return VOS_NULL_PTR;
    }

    Temp= Str + VOS_StrLen( Str );

    do
    {
        if ( *Temp == Char )
        {
            return Temp;
        }

    } while ( --Temp >= Str );

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function   : VOS_MemCmp
 Description: comp two memory info
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT VOS_MemCmp( const VOS_VOID * Dest, const VOS_VOID * Src, VOS_SIZE_T Count )
{
#if (VOS_LINUX == VOS_OS_VER)
    const unsigned char *su1, *su2;
    int res = 0;
#endif

#if (VOS_YES == VOS_CHECK_PARA)
    if( ( VOS_NULL_PTR == Dest ) || ( VOS_NULL_PTR == Src ) )
    {
        return 0;
    }
#endif

#if (VOS_LINUX == VOS_OS_VER)

    for( su1 = Dest, su2 = Src; 0 < Count; ++su1, ++su2, Count--)
    {
        if ((res = *su1 - *su2) != 0)
        {
            break;
        }
    }

    return res;
#else

    return memcmp( Dest, Src, Count );
#endif
}


/*****************************************************************************
 Function   : VOS_StrStr
 Description: find the first occurrence of a substring in a string
 Input      : Str1 --- string to search
              Str2 --- substring to look for
 Output     :
 Return     : A pointer to the located substring, or Str1 if find points to a
              zero-length string, or VOS_NULL_PTR if the string is not found.
 Other      :
 *****************************************************************************/
VOS_CHAR * VOS_StrStr( VOS_CHAR * Str1, VOS_CHAR * Str2 )
{
    VOS_UINT32 Len1, Len2;
    VOS_CHAR * pTempStr1 = Str1;
    VOS_CHAR * pTempStr2 = Str2;

    if( ( VOS_NULL_PTR == Str1 ) || ( VOS_NULL_PTR == Str2 ) )
    {
        return VOS_NULL_PTR;
    }

    Len2 = VOS_StrLen( pTempStr2 );

    if( !Len2 )
    {
        return ( VOS_CHAR * )pTempStr1;
    }

    Len1 = VOS_StrLen( pTempStr1 );

    while ( Len1 >= Len2 )
    {
        Len1--;

        if ( !VOS_MemCmp( pTempStr1, pTempStr2, Len2 ) )
        {
            return pTempStr1;
        }

        pTempStr1++;
    }

    return VOS_NULL_PTR;
}

#ifndef DMT
/*****************************************************************************
 Function   : VOS_StrNCpy
 Description: copy characters from one string to another
 Input      : Dest  -- string to copy to
              Src   -- string to copy from
              Count -- max no. of characters to copy
 Output     :
 Return     : A pointer to Dest
 Other      :
 *****************************************************************************/
VOS_CHAR *VOS_StrNCpy( VOS_CHAR *Dest, VOS_CHAR *Src, VOS_SIZE_T Count )
{
    char *tmp = Dest;
    char *pTempSrc = Src;

    if( ( VOS_NULL_PTR == Dest ) || ( VOS_NULL_PTR == Src ) )
    {
        return Dest;
    }

    if ( 0 != Count )
    {
        while ((*tmp++ = *pTempSrc++) != 0)
        {
            if (--Count == 0)
            {
                return (Dest);
            }
        }

        while (--Count > 0)
        {
            *tmp++ = '\0';
        }
    }

    return (Dest);
}

/*****************************************************************************
 Function   : VOS_StrCmp
 Description: compare two strings lexicographically
 Input      : Str1 -- string to compare
              Str2 -- string to compare Str1 to
 Output     :
 Return     : An integer greater than, equal to, or less than 0, according
              to whether Str1 is lexicographically greater than, equal to,
              or less than Str2, respectively.
 Other      :
 *****************************************************************************/
VOS_INT VOS_StrCmp( VOS_CHAR *Str1, VOS_CHAR *Str2 )
{
    register VOS_CHAR *s1 = Str1;
    register VOS_CHAR *s2 = Str2;

    if( ( VOS_NULL_PTR == Str1 ) || ( VOS_NULL_PTR == Str2 ) )
    {
        return 0;
    }

    while ((*s1 == *s2) && *s1)
    {
        s1++;
        s2++;
    }

    return (*s1 - *s2);
}

/*****************************************************************************
 Function   : VOS_StrNLen
 Description:
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_StrNLen( VOS_CHAR * Str, VOS_UINT32 Count )
{
    VOS_CHAR * Temp;

    if( VOS_NULL_PTR == Str )
    {
        return 0;
    }

    for( Temp = Str; Count-- && ( *Temp != '\0' ); ++Temp )
    {
        /* nothing */
    }

    return (VOS_UINT32)(VOS_STOL( Temp ) - VOS_STOL( Str ));
}
#endif /* DMT */

/*****************************************************************************
 Function   : V_MemSet
 Description: Set a character to memory
 Input      : ToSet -- Memory address to set
              Char  -- char to be set to
              Count -- count to set
 Output     :
 Return     : None
 Other      :
 *****************************************************************************/
VOS_VOID * V_MemSet( VOS_VOID * ToSet, VOS_CHAR Char, VOS_SIZE_T Count,
                     VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_UINT32  ulSize;
#if (VOS_LINUX == VOS_OS_VER)
    char *xs = (char *) ToSet;
#endif

#if (VOS_YES == VOS_CHECK_PARA)
    if( VOS_NULL_PTR == ToSet )
    {
        return(VOS_NULL_PTR);
    }
#endif

    if ( 0 == Count )
    {
        return ToSet;
    }

    if ( VOS_OK != VOS_LocationMem( ToSet, &ulSize, ulFileID, usLineNo ) )
    {
        /*lint -e534*/
        Print2("# WARING:V_MemSet destination error.file %d l %d.\r\n",
            ulFileID, usLineNo);
        /*lint +e534*/
        return(VOS_NULL_PTR);
    }

    if ( Count > ulSize )
    {
        /*lint -e534*/
        Print4("# WARNING:V_MemSet big.file %d l %d.count %d real size %d.\r\n",
            ulFileID, usLineNo, Count, ulSize);
        /*lint +e534*/
        return(VOS_NULL_PTR);
    }

#if (VOS_LINUX == VOS_OS_VER)

    while (Count--)
    {
        *xs++ = Char;
    }

    return ToSet;
#else

    return memset( ToSet, (VOS_UCHAR)Char, Count );/* [false alarm]:前边已有严谨的判断  */
#endif
}

/*****************************************************************************
 Function   : V_MemSet_s
 Description: Set a character to memory
 Input      : ToSet -- Memory address to set
              Char  -- char to be set to
              Count -- count to set
 Output     :
 Return     : None
 Other      :
 *****************************************************************************/
VOS_VOID * V_MemSet_s( VOS_VOID * ToSet, VOS_SIZE_T ulDestSize, VOS_CHAR Char, VOS_SIZE_T Count,
                     VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    if ( Count > ulDestSize )
    {
        return(VOS_NULL_PTR);
    }

    if ( ulDestSize > VOS_SECUREC_MEM_MAX_LEN )
    {
        return(VOS_NULL_PTR);
    }

    return V_MemSet(ToSet, Char, Count, ulFileID, usLineNo);
}

/*****************************************************************************
 Function   : VOS_MemCpy
 Description: copy memory from one location to another
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID * V_MemCpy( VOS_VOID * Dest, const VOS_VOID * Src, VOS_SIZE_T Count,
                       VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_UINT32  ulSize;
#if (VOS_LINUX == VOS_OS_VER)
    char *tmp = (char *) Dest, *s = (char *) Src;
#endif

#if (VOS_YES == VOS_CHECK_PARA)
    if( VOS_NULL_PTR == Dest )
    {
        return(VOS_NULL_PTR);
    }

    if( VOS_NULL_PTR == Src )
    {
        return(VOS_NULL_PTR);
    }
#endif

    if ( 0 == Count )
    {
        return Dest;
    }

    if ( VOS_OK != VOS_LocationMem( Dest, &ulSize, ulFileID, usLineNo ) )
    {
        /*lint -e534*/
        Print2("WARING:VOS_MemCpy destination error.file %d l %d.\r\n",
            ulFileID, usLineNo);
        /*lint +e534*/

        return(VOS_NULL_PTR);
    }

    if ( Count > ulSize )
    {
        /*lint -e534*/
        Print4("WARNING:VOS_MemCpy big.file %d l %d.Count %d real size %d.\r\n",
            ulFileID, usLineNo, Count, ulSize);
        /*lint +e534*/

        return(VOS_NULL_PTR);
    }

#if (VOS_LINUX == VOS_OS_VER)
    while (Count--)
    {
        *tmp++ = *s++;
    }

    return Dest;
#else

    return memcpy (Dest,Src,Count);/* [false alarm]:前边已有严谨的判断  */
#endif
}

/*****************************************************************************
 Function   : VOS_MemCpy
 Description: copy memory from one location to another
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID * V_MemCpy_s( VOS_VOID * Dest, VOS_SIZE_T ulDestSize, const VOS_VOID * Src, VOS_SIZE_T Count,
                       VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    if ( Count > ulDestSize )
    {
        return(VOS_NULL_PTR);
    }

    if ( ulDestSize > VOS_SECUREC_MEM_MAX_LEN )
    {
        return(VOS_NULL_PTR);
    }

    if ( (Dest > Src) && ( (VOS_VOID *)((VOS_UINT8 *)Src + Count) > Dest ) )
    {
        return(VOS_NULL_PTR);
    }

    if ( (Src > Dest ) && ( (VOS_VOID *)((VOS_UINT8 *)Dest + Count) > Src ) )
    {
        return(VOS_NULL_PTR);
    }

    return V_MemCpy(Dest, Src, Count, ulFileID, usLineNo);
}

/*****************************************************************************
 Function   : V_MemMove
 Description: copy memory from one location to another
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID * V_MemMove( VOS_VOID * Dest, const VOS_VOID * Src, VOS_SIZE_T Count,
                        VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_UINT32  ulSize;

    if (VOS_NULL_PTR == Dest)
    {
        return VOS_NULL_PTR;
    }

    /* 如果目的为空，直接返回NULL */
    if (VOS_NULL_PTR == Src)
    {
        return VOS_NULL_PTR;
    }

    if ( 0 == Count )
    {
        return Dest;
    }

    if ( VOS_OK != VOS_LocationMem( Dest, &ulSize, ulFileID, usLineNo ) )
    {
        /*lint -e534*/
        Print2("WARING:VOS_MemCpy destination error.file %d l %d.\r\n",
            ulFileID, usLineNo);
        /*lint +e534*/

        return(VOS_NULL_PTR);
    }

    if ( Count > ulSize )
    {
        /*lint -e534*/
        Print4("WARNING:VOS_MemCpy big.file %d l %d.Count %d real size %d.\r\n",
            ulFileID, usLineNo, Count, ulSize);
        /*lint +e534*/

        return(VOS_NULL_PTR);
    }

    return memmove (Dest,Src,Count);/* [false alarm]:前边已有严谨的判断  */
}

/*****************************************************************************
 Function   : V_MemMove
 Description: copy memory from one location to another
 Input      :
 Output     :
 Return     :
 Other      :
 *****************************************************************************/
 VOS_VOID * V_MemMove_s( VOS_VOID * Dest, VOS_SIZE_T ulDestSize, const VOS_VOID * Src, VOS_SIZE_T Count,
                        VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    if ( Count > ulDestSize )
    {
        return(VOS_NULL_PTR);
    }

    if ( ulDestSize > VOS_SECUREC_MEM_MAX_LEN )
    {
        return(VOS_NULL_PTR);
    }

    return V_MemMove(Dest, Src, Count, ulFileID, usLineNo);
}

/*****************************************************************************
 Function   : VOS_MemChr
 Description: search a block of memory for a character
 Input      : buf -- block of memory
              c   -- character to search for
              n   -- size of memory to search
 Output     :
 Return     : If successful, it returns the address of the matching element;
              otherwise, it returns a null pointer.
 Other      :
 *****************************************************************************/
VOS_VOID * VOS_MemChr( const VOS_VOID *buf, VOS_UCHAR c, VOS_INT n )
{
    VOS_UCHAR *p = (VOS_UCHAR*)buf;

    if( VOS_NULL_PTR == buf )
    {
        return VOS_NULL_PTR;
    }

    if ( 0 == n )
    {
        return VOS_NULL_PTR;
    }

    do
    {
        if (*p++ == c)
        {
            return ((VOS_VOID *)(p - 1));
        }
    } while (--n != 0);

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function   : VOS_64Div64
 Description: A 64-bit number divided by a 64-bit one with the operation.
              When input is 32-bit, it's 32bit implement.
 Input      : ulDividendHigh   -- high 32 bits of dividend number
              ulDividendLow    -- low 32 bits of dividend number
              ulDivisorHigh    -- high 32 bits of divisor number
              ulDivisorLow     -- low 32 bits of divisor number
 Output     : pulQuotientHigh  -- pointer of high 32 bits of quotient number
              pulQuotientLow   -- pointer of low 32 bits of quotient number
              pulRemainderHigh -- pointer of high 32 bits of remainder number
              pulRemainderLow  -- pointer of low 32 bits of remainder number
 Note       : Especially, when input pulRemainderHigh or pulRemainderLow
              is a null pointer, remainder is ignored.
 Return     : VOS_OK--success,VOS_ERROR--fail.
 Other      : Note,result maybe 64-bit or 32-bit.
 *****************************************************************************/
VOS_UINT32 VOS_64Div64( VOS_UINT32 ulDividendHigh,
                        VOS_UINT32 ulDividendLow,
                        VOS_UINT32 ulDivisorHigh,
                        VOS_UINT32 ulDivisorLow,
                        VOS_UINT32 *pulQuotientHigh,
                        VOS_UINT32 *pulQuotientLow,
                        VOS_UINT32 *pulRemainderHigh,
                        VOS_UINT32 *pulRemainderLow )

{
    VOS_INT8   chShiftNumHi = 0, chShiftNumLo = 0;
    VOS_UINT32 ulTmpQuoHi, ulTmpQuoLo;
    VOS_UINT32 ulTmpDividendHi, ulTmpDividendLo;
    VOS_UINT32 ulTmpDivisorHi, ulTmpDivisorLo;
    bit64CompareResult tmpResult;

    if (VOS_NULL_PTR == pulQuotientHigh || VOS_NULL_PTR == pulQuotientLow)
    {
        return VOS_ERRNO_LIB_64DIV64_QUOTIENT_NULL;
    }

    if (0 == ulDivisorHigh)
    {
        if (0 == ulDivisorLow)
        {
            return VOS_ERRNO_LIB_64DIV64_DIVIDE_ZERO;
        }
        else if (1 == ulDivisorLow)
        {
            *pulQuotientHigh = ulDividendHigh;
            *pulQuotientLow  = ulDividendLow;

            if (pulRemainderHigh != VOS_NULL_PTR
                && pulRemainderLow != VOS_NULL_PTR)
            {
                *pulRemainderHigh = 0;
                *pulRemainderLow  = 0;
            }

            return VOS_OK;
        }
    }

    ulTmpQuoHi = ulTmpQuoLo = 0;
    ulTmpDividendHi = ulDividendHigh;
    ulTmpDividendLo = ulDividendLow;

    /* if divisor is larger than dividend, quotient equals to zero,
     * remainder equals to dividends */
    /*lint -e717 */
    BIT64_COMPARE(ulDividendHigh, ulDividendLow,
                  ulDivisorHigh, ulDivisorLow, tmpResult);
    /*lint +e717 */
    if (BIT64_LESS == tmpResult)
    {
        /*lint -e801 */
        goto returnHandle;
        /*lint +e801 */
    }
    else if (BIT64_EQUAL == tmpResult)
    {
        *pulQuotientHigh = 0;
        *pulQuotientLow  = 1;

        if (pulRemainderHigh != VOS_NULL_PTR && pulRemainderLow != VOS_NULL_PTR)
        {
            *pulRemainderHigh = 0;
            *pulRemainderLow  = 0;
        }

        return VOS_OK;
    }

    /* get shift number to implement divide arithmetic */
    if (ulDivisorHigh > 0)
    {
        for (chShiftNumHi = 0; chShiftNumHi < MAX_SHIFT_NUM; chShiftNumHi++)
        {
            if ( (ulDivisorHigh << chShiftNumHi) & MASK_BIT_32 )
            {
                break;
            }
        }
    }
    else
    {
        for (chShiftNumLo = 0; chShiftNumLo < MAX_SHIFT_NUM; chShiftNumLo++)
        {
            if ( (ulDivisorLow << chShiftNumLo) & MASK_BIT_32 )
            {
                break;
            }
        }
    }

    if (ulDivisorHigh > 0)
    {
        /* divisor's high 32 bits doesn't equal to zero */
        /*lint -save -e644*/
        for (; chShiftNumHi >= 0; chShiftNumHi--)
        {
        /*lint -restore*/
            if (0 == chShiftNumHi)
            {
                ulTmpDivisorHi = ulDivisorHigh;
            }
            else
            {
                ulTmpDivisorHi = (ulDivisorHigh << chShiftNumHi)
                    | (ulDivisorLow >> (MAX_SHIFT_NUM - chShiftNumHi));
            }

            ulTmpDivisorLo = ulDivisorLow << chShiftNumHi;

            /*lint -e717 */
            BIT64_COMPARE(ulTmpDividendHi, ulTmpDividendLo,
                          ulTmpDivisorHi, ulTmpDivisorLo, tmpResult);
            /*lint +e717 */

            /*lint -e701 */
            if (tmpResult != BIT64_LESS)
            {
            /*lint +e701 */
                /*lint -e717 */
                BIT64_SUB(ulTmpDividendHi, ulTmpDividendLo,
                          ulTmpDivisorHi, ulTmpDivisorLo);
                /*lint +e717 */
                /*lint -e701 */
                ulTmpQuoLo |= (1 << chShiftNumHi);
                /*lint +e701 */
                if (0 == ulTmpDividendHi && 0 == ulTmpDividendLo)
                {
                    /*lint -e801 */
                    goto returnHandle;
                    /*lint +e801 */
                }
            }
        }

    }
    else
    {
        /* divisor's high 32 bits equals to zero */
        /*lint -save -e644*/
        chShiftNumHi = chShiftNumLo;
        /*lint -restore*/
        for (; chShiftNumHi >= 0; chShiftNumHi--)
        {
            ulTmpDivisorHi = ulDivisorLow << chShiftNumHi;
            /*lint -e717 */
            BIT64_COMPARE(ulTmpDividendHi, ulTmpDividendLo,
                          ulTmpDivisorHi, 0, tmpResult);
            /*lint +e717 */

            /*lint -e701 */
            if (tmpResult != BIT64_LESS)
            /*lint +e701 */
            {   /*lint -save -e568*/
                /*lint -e717 -e685 */
                BIT64_SUB(ulTmpDividendHi, ulTmpDividendLo,
                          ulTmpDivisorHi, 0);
                /*lint +e717 +e685 */
                /*lint -restore*/
                /*lint -e701 */
                ulTmpQuoHi |= (1 << chShiftNumHi);
                /*lint +e701 */
                if ((0 == ulTmpDividendHi) && (0 == ulTmpDividendLo))
                {
                    /*lint -e801 */
                    goto returnHandle;
                    /*lint +e801 */
                }
            }
        }

        for (chShiftNumHi = MAX_SHIFT_NUM - 1; chShiftNumHi >= 0; chShiftNumHi--)
        {
            if (0 == chShiftNumHi)
            {
                ulTmpDivisorHi = 0;
            }
            else
            {
                ulTmpDivisorHi = ulDivisorLow  >> (MAX_SHIFT_NUM - chShiftNumHi);
            }

            ulTmpDivisorLo = ulDivisorLow << chShiftNumHi;

            /*lint -e717 */
            BIT64_COMPARE(ulTmpDividendHi, ulTmpDividendLo,
                          ulTmpDivisorHi, ulTmpDivisorLo, tmpResult);
            /*lint +e717 */
            /*lint -e701 */
            if (tmpResult != BIT64_LESS)
            /*lint +e701 */
            {
                /*lint -e717 */
                BIT64_SUB(ulTmpDividendHi, ulTmpDividendLo,
                          ulTmpDivisorHi, ulTmpDivisorLo);
                /*lint +e717 */
                /*lint -e701 */
                ulTmpQuoLo |= (1 << chShiftNumHi);
                /*lint +e701 */
                if ((0 == ulTmpDividendHi) && (0 == ulTmpDividendLo))
                {
                    /*lint -e801 */
                    goto returnHandle;
                    /*lint +e801 */
                }
            }
        }

    }

returnHandle:

    *pulQuotientHigh = ulTmpQuoHi;
    *pulQuotientLow  = ulTmpQuoLo;

    if (pulRemainderHigh != VOS_NULL_PTR && pulRemainderLow != VOS_NULL_PTR)
    {
        *pulRemainderHigh = ulTmpDividendHi;
        *pulRemainderLow  = ulTmpDividendLo;
    }

    return VOS_OK;
}


/*****************************************************************************
 Function   : VOS_64Div32
 Description: A 64-bit number divided by a 32-bit one with the operation.
 Input      : ulDividendHigh  -- high 32 bits of dividend number
              ulDividendLow   -- low 32 bits of dividend number
              ulDivisor       -- divisor, it's 32 bits number
 Output     : pulQuotientHigh -- pointer of high 32 bits of quotient number
              pulQuotientLow  -- pointer of low 32 bits of quotient number
              pulRemainder    -- pointer of remainder value after calculating
 Note       : Especially, when pulRemainder is not VOS_NULL_PTR, the remainder
              value will be stored in it pointed to.
 Return     : VOS_OK--success,VOS_ERROR--fail.
 Other      : Note,result maybe 64-bit or 32-bit.
 *****************************************************************************/
VOS_UINT32 VOS_64Div32( VOS_UINT32 ulDividendHigh,
                        VOS_UINT32 ulDividendLow,
                        VOS_UINT32 ulDivisor,
                        VOS_UINT32 *pulQuotientHigh,
                        VOS_UINT32 *pulQuotientLow,
                        VOS_UINT32 *pulRemainder )
{
    VOS_UINT32 ulTmpRemainderHi, ulTmpRemainderLo;
    VOS_UINT32 ulRet;

    if (VOS_NULL_PTR == pulQuotientHigh || VOS_NULL_PTR == pulQuotientLow)
    {
        return VOS_ERRNO_LIB_64DIV32_QUOTIENT_NULL;
    }
    if (0 == ulDivisor)
    {
        return VOS_ERRNO_LIB_64DIV32_DIVIDE_ZERO;
    }

    ulRet = VOS_64Div64( ulDividendHigh,
                         ulDividendLow,
                         0,
                         ulDivisor,
                         pulQuotientHigh,
                         pulQuotientLow,
                         &ulTmpRemainderHi,
                         &ulTmpRemainderLo );
    if (ulRet != VOS_OK)
    {
        return ulRet;
    }

    if (pulRemainder != VOS_NULL_PTR)
    {
        *pulRemainder = ulTmpRemainderLo;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_SetSeed
 Description: This function initializes the array of random numbers generated
              using with the seed value given
 Input      : ulSeed -- Seed for Random Number Generation
 Output     : None
 Return     : None
 Other      : g_ulRandNoSet_Array -- Array of random numbers
              g_ulInitArray       -- Initialization array
              g_pulTap1           -- First Tap
              g_pulTap2           -- Second Tap
 *****************************************************************************/
VOS_VOID VOS_SetSeed( VOS_UINT32 ulSeed )
{
    g_ulVosRadomSeed = ulSeed;

    return;
}

/*****************************************************************************
 Function   : VOS_Rand
 Description: This function returns random value within the range specified
              0..n-1 where n is the range specified.
 Input      : ulRange -- Range within which Random number is required
 Output     : None
 Return     : The random number generated
 Other      : g_ulRandNoSet_Array -- Array of random numbers
              g_ulInitArray       -- Initialization array
              g_pulTap1           -- First Tap
              g_pulTap2           -- Second Tap
 *****************************************************************************/
VOS_UINT32 VOS_Rand( VOS_UINT32 ulRange )
{
    register VOS_UINT32 ulGenTemp;
    register VOS_UINT32 ulGenTempHigh, ulRangeHigh, ulRangeLow;
    register VOS_UINT32 ulRandomNumber;

    /* 设置了种子用设置的种子，否则用系统时间做种子 */
    if (0 == g_ulVosRadomSeed )
    {
        ulGenTemp = VOS_GetSlice();
    }
    else
    {
        ulGenTemp = g_ulVosRadomSeed;
    }

    /* 网络搜索算法生成伪随机数 */
    ulGenTemp = (ulGenTemp * 1664525L + 1013904223L) ;

    g_ulVosRadomSeed = ulGenTemp;

    /* 将伪随机匹配到范围内 */
    ulGenTempHigh = ulGenTemp >> 16;
    ulGenTemp &= 0xffff;

    ulRangeHigh = (ulRange & 0xffffffff) >> 16;
    ulRangeLow = ulRange & 0xffff;

    ulRandomNumber = (ulGenTemp * ulRangeLow) >> 16;
    ulRandomNumber += ulGenTempHigh * ulRangeLow;

    if (ulRangeHigh == 0)
    {
        ulRandomNumber >>= 16;
    }
    else
    {
        ulRandomNumber += ulGenTemp * ulRangeHigh;
        ulRandomNumber = (ulRandomNumber >> 16)
                         + (ulGenTempHigh * ulRangeHigh);
    }

    return ulRandomNumber;
}

/* Notes:
 * when inputs are big enough, the overflow maybe occur,
 * please be aware of it in use.*/
void add64( VOS_UINT32 *low,
              VOS_UINT32 *high,
              VOS_UINT32 oldlow,
              VOS_UINT32 oldhigh )
{
    if (*low > 0xFFFFFFFF - oldlow)
    {
        *high += (oldhigh + 1);
    }
    else
    {
        *high += oldhigh;
    }
    *low += oldlow;
}


/*****************************************************************************
 Function   : VOS_64Multi32
 Description: A 64-bit number multiplied by a 32-bit one with the operation.
 Input      : ulMultiplicandHigh -- high 32 bits of multiplicand number
              ulMultiplicandLow  -- low 32 bits of multiplicand number
              ulMultiplicator    -- multiplicator, it's 32 bits number
 Output     : pulProductHigh     -- pointer of high 32 bits of product number
              pulProductLow      -- pointer of low 32 bits of product number
 Note       : when inputs are big enough, the overflow maybe occur,
              please be aware of it in use.
 Return     : VOS_OK--success,VOS_ERROR--fail.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_64Multi32( VOS_UINT32 ulMultiplicandHigh,
                          VOS_UINT32 ulMultiplicandLow,
                          VOS_UINT32 ulMultiplicator,
                          VOS_UINT32 *pulProductHigh,
                          VOS_UINT32 *pulProductLow )
{
    VOS_UINT32 count, xbit, record, tmpHigh, tmpLow;

    if (VOS_NULL_PTR == pulProductHigh || VOS_NULL_PTR == pulProductLow)
    {
        return VOS_ERRNO_LIB_64MUL32_QUOTIENT_NULL;
    }

    *pulProductHigh = *pulProductLow = 0;

    if ((0 == ulMultiplicandHigh && 0 == ulMultiplicandLow)
        || (0 == ulMultiplicator))
    {
        return VOS_OK;
    }

    for (count = 32, xbit = MASK_BIT_32;
         count > 1;  xbit >>= 1, count--)
    {
        if (ulMultiplicator & xbit)
        {
            if (0 != (ulMultiplicandHigh & MASK_HI_NBITS(count -1)))
            {
                /*lint -e801 */
                goto overflowHandle;
                /*lint +e801 */
            }
            record = ulMultiplicandLow & MASK_HI_NBITS(count -1);
            record >>= (32 - (count -1));
            tmpHigh = ulMultiplicandHigh << (count -1) | record;
            tmpLow  = ulMultiplicandLow << (count -1);

            add64( pulProductLow,
                   pulProductHigh,
                   tmpLow,
                   tmpHigh );
            /* If check failed, means overflow occurred */
            if (*pulProductHigh < tmpHigh)
            {
                /*lint -e801 */
                goto overflowHandle;
                /*lint +e801 */
            }
        }
    }

    if (ulMultiplicator & MASK_BIT_01)
    {
        add64( pulProductLow,
               pulProductHigh,
               ulMultiplicandLow,
               ulMultiplicandHigh );
        /* If check failed, means overflow occurred */
        if (*pulProductHigh < ulMultiplicandHigh)
        {
            /*lint -e801 */
            goto overflowHandle;
            /*lint +e801 */
        }
    }

    return VOS_OK;

overflowHandle:

    *pulProductHigh = *pulProductLow = 0;

    /*lint -e534*/
    VOS_SetErrorNo( VOS_ERRNO_LIB_64MUL32_OVERFLOW );
    /*lint +e534*/
    return VOS_ERRNO_LIB_64MUL32_OVERFLOW;
}

/*****************************************************************************
 Function   : VOS_StrSpn
 Description: return the string length
              up to the first character not in a given set
 Input      : Str1 -- string to search
              Str2 -- set of characters to look for in <Str1>
 Output     :
 Return     : The length of the string segment
 Other      :
 *****************************************************************************/
VOS_SIZE_T VOS_StrSpn(const VOS_CHAR *Str1, const VOS_CHAR *Str2)
{
    const VOS_CHAR *pscSave;
    const VOS_CHAR *pscTemp;
    VOS_CHAR c1;
    VOS_CHAR c2;

    for ( pscSave = Str1 + 1; '\0' != (c1 = *Str1++); )
    {
        for ( pscTemp = Str2; (c2 = *pscTemp++) != c1; )
        {
            if ( '\0' == c2 )
            {
                return (VOS_SIZE_T)(Str1 - pscSave);
            }
        }
    }

    return (VOS_SIZE_T)(Str1 - pscSave);
}

/*****************************************************************************
 Function   : VOS_StrPbrk
 Description: find the first occurrence in a string of a character
              from a given set
 Input      : Str1 -- string to search
              Str2 -- set of characters to look for in <Str1>
 Output     :
 Return     : A pointer to the character found in <Str1>,
              or NULL if no character from <Str2> occurs in <Str1>
 Other      :
 *****************************************************************************/
VOS_CHAR *VOS_StrPbrk(const VOS_CHAR *Str1, const VOS_CHAR *Str2)
{
    VOS_CHAR *pscScan;
    VOS_CHAR  c;
    VOS_CHAR  sc;

    while ( '\0' != (c = *Str1++) )/* wait until end of string */
    {
        /* loop, searching for character */
        for ( pscScan = (VOS_CHAR *)Str2; '\0' != (sc = *pscScan++); )
        {
            if (sc == c)
            {
                return ((VOS_CHAR *)(Str1 - 1));
            }
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function   : VOS_StrTok
 Description: break down a string into tokens
 Input      : Str1 -- string to separator
              Str2 -- separator indicator
 Output     :
 Return     : A pointer to the first character of a token, or a NULL pointer
              if there is no token.
 Other      :
 *****************************************************************************/
VOS_CHAR *VOS_StrTok(VOS_CHAR *Str1, const VOS_CHAR *Str2)
{
    static VOS_CHAR *pscLast = VOS_NULL_PTR;

    if ( (VOS_NULL_PTR == Str1) && (VOS_NULL_PTR == (Str1 = pscLast)) )
    {
        return VOS_NULL_PTR;
    }

    if ( '\0' == *(Str1 += VOS_StrSpn(Str1, Str2)) )
    {
        return (pscLast = VOS_NULL_PTR);
    }

    if ((pscLast = VOS_StrPbrk(Str1, Str2)) != VOS_NULL_PTR)
    {
        *pscLast++ = '\0';
    }

    return (Str1);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


