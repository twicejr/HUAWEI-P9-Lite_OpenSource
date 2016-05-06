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
/* FileNmae: v_nsprintf.c                                                    */
/*                                                                           */
/* Author:Tong ChaoZhu                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date:  2001-12-26                                                         */
/*                                                                           */
/* Description: copy this file from Dopra                                    */
/*                                                                           */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification:                                                          */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "v_IO.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_NSPRINTF_C
/*lint +e767 modify:x51137; review:h59254; */


/*****************************************************************************
 Function   : ANSI_nvsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 ANSI_nvsprintf(VOS_CHAR *out_buf, VOS_UINT32 ulStrLen, const VOS_CHAR *fmt0, va_list argp)
{
    VOS_UINT_PTR    ulLong;
    VOS_INT         lBase;
    VOS_INT         lDprec;
    VOS_INT         lFieldSize;
    VOS_INT         lFlags;
    VOS_INT         lFpprec;
    VOS_INT         lPrec;
    VOS_INT         lRealSize;
    VOS_INT         lConverSize;
    VOS_INT         lFormatWidth;
    VOS_INT         lChar;
    VOS_INT         ltemp;

    VOS_UCHAR       *pucFmt;
    VOS_CHAR        *pcBuf;
    VOS_CHAR        ucPrefixSign;
    VOS_CHAR        *pucDigs;
    VOS_CHAR        ucBuf[BUF];
    VOS_CHAR        *pucOutBuf=out_buf;
#ifdef FLOAT_SUPPORT
    VOS_CHAR        ucSoftSign;
#endif
    VOS_UINT32      ulWriteLen = ulStrLen;

    pucFmt  = (VOS_UCHAR*)fmt0;
    pucDigs = "0123456789abcdef";


    /*lint -e801 -e445 屏蔽goto语句*/
    for (;; ++pucFmt)
    {
            for (; ((lChar = *pucFmt)!=0) && lChar != '%'; ++pucFmt)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++ = (VOS_CHAR)lChar;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }
            if (!lChar)
            {
                goto    lvspret;
            }

            lFlags          = 0;
            lDprec          = 0;
            lFpprec         = 0;
            lFormatWidth    = 0;
            lPrec           = -1;
            ucPrefixSign = '\0';

rflag: switch (*++pucFmt) {
        case ' ':
            /* 若空格和加号同时出现，则忽略空格 -- ANSI X3J11  */
            if (!ucPrefixSign)
            {
                ucPrefixSign = ' ';
            }
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case '#':
            lFlags |= ALT;
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case '*':
            /*lint -e147 -e586*/
            if ((lFormatWidth = va_arg(argp, VOS_INT)) >= 0)
            {
                /*lint +e147 +e586*/
                /*lint -e801 */
                goto rflag;
                /*lint +e801 */
            }
            lFormatWidth = -lFormatWidth;
        /*lint -e616 */
        case '-':
        /*lint +e616 */
            lFlags |= LADJUST; /* 左对齐 */
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case '+':
            ucPrefixSign = '+';
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case '.':
            if (*++pucFmt == '*')
            {
                /*lint -e147 -e586*/
                ltemp = va_arg(argp, VOS_INT);
                /*lint +e147 +e586*/
            }
            else
            {
                ltemp = 0;
                while (isascii(*pucFmt) && isdigit(*pucFmt))
                {
                    ltemp = 10 * ltemp + todigit(*pucFmt++);
                }
                --pucFmt;
            }
            lPrec = ltemp < 0 ? -1 : ltemp;
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case '0':
            lFlags |= ZEROPAD;
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ltemp = 0;
            do
            {
                ltemp = 10 * ltemp + todigit(*pucFmt);
            } while (isascii(*++pucFmt) && isdigit(*pucFmt));
            lFormatWidth = ltemp;
            --pucFmt;
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case 'L':
            lFlags |= LONGDBL;
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case 'h':
            lFlags |= SHORTINT;
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case 'l':
            lFlags |= LONGINT;
            /*lint -e801 */
            goto rflag;
            /*lint +e801 */
        case 'c':
            /*lint -e147 -e586*/
            *(pcBuf = ucBuf) = (VOS_CHAR)va_arg(argp, VOS_INT);
            /*lint +e147 +e586*/
            lConverSize = 1;
            ucPrefixSign = '\0';
            /*lint -e801 */
            goto pforw;
            /*lint +e801 */
        case 'D':
            lFlags |= LONGINT;
            /*lint -save -e732 -e501 -e737 -e713*/
        case 'd':
        case 'i':
            /*lint -e147 -e586*/
            ARG(int);
            /*lint +e147 +e586*/
            if ((VOS_INT32)ulLong < 0)
            {
                ulLong = -ulLong;
                ucPrefixSign = '-';
            }
            lBase = 10;
            /*lint -e801 */
            goto number;
            /*lint +e801 */
#ifdef FLOAT_SUPPORT
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':

        {
            VOS_DOUBLE udDouble;        /* 双精度浮点数 */
            /*lint -e147 -e586*/
            udDouble = va_arg(argp, VOS_DOUBLE);
            /*lint +e147 +e586*/

            if (lPrec > MAXFRACT)
            {
                if ((*pucFmt != 'g' && *pucFmt != 'G') || (lFlags&ALT))
                {
                    lFpprec = lPrec - MAXFRACT;
                }
                lPrec = MAXFRACT;
            }
            else if (lPrec == -1)
            {
                if (lFlags&LONGINT)
                {
                    lPrec = DEFLPREC;
                }
                else
                {
                    lPrec = DEFPREC;
                }
            }

            if (udDouble < 0)
            {
                ucSoftSign = '-';
                udDouble = -udDouble;
            }
            else
            {
                ucSoftSign = 0;
            }

            *ucBuf = 0;
            lConverSize = cvt(udDouble, lPrec, lFlags,*pucFmt, &ucSoftSign, ucBuf,
            ucBuf + sizeof(ucBuf));

            if (ucSoftSign)
            {
                ucPrefixSign = '-';
            }
            pcBuf = *ucBuf ? ucBuf : ucBuf + 1;
            /*lint -e801 */
            goto pforw;
            /*lint +e801 */
        }
#endif
        case 'n':
            if (lFlags & LONGINT)
            {
                /*lint -e147 -e586*/
                *va_arg(argp, VOS_INT32*) = (VOS_INT32)(pucOutBuf-out_buf);
                /*lint +e147 +e586*/
            }
            else if (lFlags & SHORTINT)
            {
                /*lint -e147 -e586*/
                *va_arg(argp, VOS_INT16*) = (VOS_INT16)(pucOutBuf-out_buf);
                /*lint +e147 +e586*/
            }
            else
            {
                /*lint -e147 -e586*/
                *va_arg(argp, VOS_INT*) = (VOS_INT)(pucOutBuf-out_buf);
                /*lint +e147 +e586*/
            }
            break;
        case 'O':
            lFlags |= LONGINT;
        /*lint -e616 */
        case 'o':
        /*lint +e616 */
            /*lint -e147 -e586*/
            ARG(unsigned);
            /*lint +e147 +e586*/
            lBase = 8;
            /*lint -e801 */
            goto nosign;
            /*lint +e801 */
        case 'p':
            /*lint -e147 -e586*/
            ulLong = (VOS_UINT_PTR)va_arg(argp, VOS_VOID *);
            /*lint +e147 +e586*/
            lBase = 16;
            /*lint -e801 */
            goto nosign;
            /*lint +e801 */
        case 's':
            /*lint -e147 -e586*/
            if ( (pcBuf = va_arg(argp, VOS_CHAR*))==0 )
            {
            /*lint +e147 +e586*/
                pcBuf = "(null)";
            }
            if (lPrec >= 0)
            {
                VOS_CHAR *p;

                if ((p = (VOS_CHAR *)VOS_MemChr((const VOS_CHAR *)pcBuf, 0, lPrec))!=0)
                {
                    lConverSize = p - pcBuf;
                    if (lConverSize > lPrec)
                    {
                        lConverSize = lPrec;
                    }
                 }
                 else
                 {
                    lConverSize = lPrec;
                 }
            }
            else
            {
                lConverSize = VOS_StrLen(pcBuf);
            }
            ucPrefixSign = '\0';
            /*lint -e801 */
            goto pforw;
            /*lint +e801 */
        case 'U':
            lFlags |= LONGINT;
        /*lint -e616 */
        case 'u':
        /*lint +e616 */
            /*lint -e147 -e586*/
            ARG(unsigned);
            /*lint +e147 +e586*/
            lBase = 10;
            /*lint -e801 */
            goto nosign;
            /*lint +e801 */
        case 'X':
            pucDigs = "0123456789ABCDEF";
        /*lint -e616 */
        case 'x':
        /*lint +e616 */
            /*lint -e147 -e586*/
            ARG(unsigned);
            /*lint +e147 +e586*/
            lBase = 16;
            if (lFlags & ALT && ulLong != 0)
            {
                lFlags |= HEXPREFIX;
            }

            /* 无符号数转换 */
nosign:    ucPrefixSign = '\0';

number:     if ((lDprec = lPrec) >= 0)
            {
                lFlags &= ~ZEROPAD;
            }

            pcBuf = ucBuf + BUF;
            /*lint -save -e727 -e728 -e729 -e732 -e713 -e573 -e529*/
            if (ulLong != 0 || lPrec != 0)
            {
                do {
                    *--pcBuf = pucDigs[ulLong % lBase];
                    ulLong /= lBase;
                } while (ulLong);
                pucDigs = "0123456789abcdef";
                if (lFlags & ALT && lBase == 8 && *pcBuf != '0')
                {
                    *--pcBuf = '0'; /* 8进制标志 */
                }
            }
            lConverSize = ucBuf + BUF - pcBuf;

pforw:
            lFieldSize = lConverSize + lFpprec;
            if (ucPrefixSign)
            {
                lFieldSize++;
            }
            if (lFlags & HEXPREFIX)
            {
                lFieldSize += 2;
            }
            lRealSize = lDprec > lFieldSize ? lDprec : lFieldSize;

            if ((lFlags & (LADJUST|ZEROPAD)) == 0 && lFormatWidth)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++=' ';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            if (ucPrefixSign)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++=ucPrefixSign;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if (lFlags & HEXPREFIX)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++='0';
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
                if(ulWriteLen--)
                {
                    *pucOutBuf++=(VOS_CHAR)*pucFmt;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if ((lFlags & (LADJUST|ZEROPAD)) == ZEROPAD)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++='0';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            for (ltemp = lFieldSize; ltemp < lDprec; ltemp++)
            {
               if(ulWriteLen--)
               {
                  *pucOutBuf++='0';
               }
               else
               {
                   return (VOS_INT32)ulStrLen;
               }
            }

            ltemp = lConverSize;
            while (--ltemp >= 0)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++=*pcBuf++;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            while (--lFpprec >= 0)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++='0';
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if (lFlags & LADJUST)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++=' ';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            break;
        case '\0':
                        /*lint -e801 */
                        goto    lvspret;
                        /*lint +e801 */
        default:
                        if(ulWriteLen--)
                        {
                            *pucOutBuf++=(VOS_CHAR)*pucFmt;
                        }
                        else
                        {
                            return (VOS_INT32)ulStrLen;
                        }

            }
        }
        /*lint +e801 +e445 屏蔽goto语句*/
lvspret:
        if(ulWriteLen--)
        {
            *pucOutBuf=0;
        }
        else
        {
            return (VOS_INT32)ulStrLen;
        }
        return (VOS_INT)(pucOutBuf-out_buf);
}/*lint -restore*/

/*****************************************************************************
 Function   : VOS_nvsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 VOS_nvsprintf(VOS_CHAR * str, VOS_UINT32 ulMaxStrLen, const VOS_CHAR *format, va_list arguments)
{
    VOS_INT32 nc;

    if (( NULL == str ) || ( NULL == format ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        /*lint -e534*/
        VOS_MemSet(str, 0, ulMaxStrLen);
        /*lint +e534*/
    }

    nc = ANSI_nvsprintf(str, ulMaxStrLen - 1, (const VOS_CHAR *) format, arguments);

    return nc;
}


/*****************************************************************************
 Function   : VOS_nsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 VOS_nsprintf(VOS_CHAR *str, VOS_UINT32 ulMaxStrLen, const VOS_CHAR *fmt, ...)
{

    /*lint -e530 -e830 */
    va_list arg;
    register VOS_INT32 nc;


    if (( NULL == str ) || ( NULL == fmt ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        /*lint -e534*/
        VOS_MemSet(str, 0, ulMaxStrLen);
        /*lint +e534*/
    }

    /*lint -e586*/
    va_start(arg, fmt);
    /*lint +e586*/
    nc = ANSI_nvsprintf(str, ulMaxStrLen - 1, (const VOS_CHAR *) fmt, arg);
    /*lint -e586*/
    va_end(arg);
    /*lint +e586*/
    return (nc);
    /*lint +e530 +e830 */
}

VOS_PRINT_HOOK g_pfnPrintHook = VOS_NULL_PTR;

/*****************************************************************************
 Function   : VOS_HookPrint
 Description: Register the redirect funciton for vos_printf
 Input      : newHook -- New print hook
 Output     : None
 Return     : Old print hook
 Other      : 1) The print hook might be re-enterred.
              2) The print hook should be call in Interrupt level and task
                 context.
 *****************************************************************************/
VOS_PRINT_HOOK VOS_HookPrint( VOS_PRINT_HOOK newHook )
{
    VOS_PRINT_HOOK oldHook = g_pfnPrintHook;

    g_pfnPrintHook = newHook;

    return oldHook;
}

#if (VOS_WIN32 == VOS_OS_VER)
/* which comes from MFC of WIN32 */
extern void zprint(char *str);
#endif

/*****************************************************************************
 Function   : vos_printf
 Description: Print function
 Input      : format -- Format string to print
 Output     : None
 Return     : VOS_OK on success and VOS_ERROR on error
 *****************************************************************************/
VOS_INT32 vos_printf( const VOS_CHAR * format, ... )
{
    VOS_INT32  rc;
    VOS_UINT32 ulReturn = VOS_OK;

    /*lint -e530 -e830 */
    va_list    argument;
    VOS_CHAR   output_info[VOS_MAX_PRINT_LEN + 4];

    /*lint -e586*/
    va_start( argument, format );
    /*lint +e586*/
    rc = VOS_nvsprintf( output_info, VOS_MAX_PRINT_LEN, format, argument );
    /*lint -e586*/
    va_end( argument );
    /*lint +e586*/
    /*lint +e530 +e830 */

    output_info[VOS_MAX_PRINT_LEN - 1] = '\0';

    if( rc >= VOS_MAX_PRINT_LEN - 1 )
    {
        VOS_UINT32  ulTempLen;
        VOS_CHAR *  pcWarning = " [!!!Warning: Print too long!!!]\r\n";
        ulTempLen = VOS_StrLen( pcWarning );
        /*lint -e534*/
        VOS_StrNCpy( output_info + ( VOS_MAX_PRINT_LEN - ulTempLen - 1 ), pcWarning, ulTempLen );
        VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG );
        /*lint +e534*/
        ulReturn = VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG;
    }
    else if( rc < 0 )
    {
        VOS_CHAR *  pcWarning = "\r\n### vos printf error: unknown internal error. ###\r\n";
        /*lint -e534*/
        VOS_StrCpy( output_info, pcWarning );
        VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR );
        /*lint +e534*/
        ulReturn = VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR;
    }

    if( g_pfnPrintHook != VOS_NULL_PTR )
    {
        ulReturn = (VOS_UINT32)(*g_pfnPrintHook)( output_info );
        if( ulReturn != (VOS_UINT32)VOS_ERROR )
        {
            return (VOS_INT32)VOS_OK;
        }
    }

    /*lint -e534*/
#if ((VOS_VXWORKS == VOS_OS_VER)  || (VOS_NUCLEUS == VOS_OS_VER) )
    printf( "%s",output_info );
#endif

#if (VOS_WIN32 == VOS_OS_VER)
    zprint(output_info );
#endif

#if (VOS_LINUX == VOS_OS_VER)
    printk( "%s",output_info );
#endif

#if (VOS_RTOSCK == VOS_OS_VER)
    SRE_Printf( "%s",output_info );
#endif
    /*lint +e534*/

    return (VOS_INT32)ulReturn;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




