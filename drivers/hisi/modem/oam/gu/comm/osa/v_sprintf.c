

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_sprintf.c                                                     */
/*                                                                           */
/* Author:                                                                   */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date:                                                                     */
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
extern "C"{
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "v_IO.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_SPRINTF_C
/*lint +e767 modify:x51137; review:h59254; */


/*****************************************************************************
 Function   : _Second2DateTime
 Description: Convert the number of seconds to the dates
 Input      : ulSec      -- The seconds set by the user
              pstRetDate -- The current date, in the format of Y/M/D (31-16/15-8/7-0)
              pstRetTime -- The current time, in the format of h/m/s (31-16/15-8/7-0)
 Output     : None
 Return     : None
 ******************************************************************************/
VOS_VOID _Second2DateTime( VOS_UINT32 ulSec,
                          VOS_UINT32 *pulRetDate,
                          VOS_UINT32 *pulRetTime )
{
    VOS_UINT32 dmsize[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    VOS_UINT32 ulYear;
    VOS_UINT32 ulMonth;
    VOS_UINT32 ulTempSec;
    VOS_UINT32 ulHour, ulMin;
    VOS_UINT32 ulTemp = ulSec;

    if( VOS_NULL_PTR == pulRetDate )
    {
        return;
    }

    if( VOS_NULL_PTR == pulRetTime )
    {
        return;
    }

    /*year*/
    for( ulYear = 1970;; )
    {
        ulTempSec = ( VOS_IsLeap( ulYear ) ? 366 : 365 ) * 24 * 60 * 60;
        if( ulTemp >= ulTempSec )
        {
            ulYear ++;
            ulTemp -= ulTempSec;
        }
        else
        {
            break;
        }
    }

    /*month*/
    for( ulMonth = 1;; )
    {
        ulTempSec = (VOS_UINT32 )( ( VOS_IsLeap( ulYear ) && ( ulMonth == 2 ) ) ? \
                    ( dmsize[ulMonth] + 1 ) : dmsize[ulMonth] ) * 24 * 60 * 60;
        if( ulTemp >= ulTempSec )
        {
            ulMonth ++;
            ulTemp -= ulTempSec;
        }
        else
        {
            break;
        }
    }
    *pulRetDate = ( ulYear << 16 ) | ( ulMonth<<8 ) | \
        ( ulTemp / ( 24 * 60 * 60 ) + 1 );

    ulTemp %= ( 24 * 60 * 60 );

    ulHour = ulTemp/ ( 60 * 60 );
    ulTemp %= ( 60 * 60 );

    ulMin = ulTemp / 60;
    ulTemp %= 60;

    *pulRetTime = ( ulHour << 16 ) | ( ulMin << 8 ) | ulTemp;

    return;
}

/**************************************************************************
 Function    : _C_formatter
 Description :

 Calls       :
 Called By   :
 Input       :
 Output      :
 Return      :
 **************************************************************************/
VOS_INT32 _C_formatter(const VOS_CHAR *format,
                VOS_VOID        put_one_char(VOS_UINT8, VOS_VOID *,VOS_CHAR *),
                VOS_VOID       *secret_pointer,
                va_list     ap,     VOS_CHAR * str)
{
    VOS_CHAR                format_flag;
    VOS_INT32                 precision;
    VOS_INT32                 length, mask, nr_of_bits, n;
    VOS_INT32                 field_width;
    VOS_CHAR                flag_char, left_adjust;
    VOS_UINT_PTR           ulong;

#ifdef VOS_FLOAT_SUPPORT
        VOS_DOUBLE              fvalue;
#endif

    VOS_INT32                num;
    VOS_CHAR               *buf_pointer;
    VOS_CHAR               *ptr, *hex;
    VOS_CHAR                zeropad;
    VOS_CHAR                buf[FRMWRI_BUFSIZE];
    VOS_UINT32              ulDate;/* added by wuxiaoqian 2k/09/20 for "%t"*/
    VOS_UINT32              ulTime;/* added by wuxiaoqian 2k/09/20 for "%t"*/

    for (;;)    /* Until full format string read */
    {
        while ((format_flag = *format++) != '%')        /* Until '%' or '\0' */
        {
            if (!format_flag)
            {
                *(str+*((VOS_INT32 *)secret_pointer))='\0';
                /*nr_of_chars计数有错,当\n时,实际是2个字符,nr_of_chars只记了一次*/
                return *((VOS_INT32 *)secret_pointer);
            }
            put_one_char ((VOS_UINT8)format_flag, secret_pointer,str);

        }   /* while () */

        if (*format == '%')             /* %% prints as % */
        {
            format++;
            put_one_char('%',secret_pointer,str);

            continue;
        }   /* if () */

        flag_char = 0;
        left_adjust = 0;
        /*=====================================*/
        /* check for leading -, + or ' 'flags  */
        /*=====================================*/
        for (;;)
        {
            if (*format == '+' || *format == ' ')
            {
                flag_char = *format++;
            }
            else if (*format == '-')
            {
                left_adjust++;
                format++;
            }
            else
            {
                break;
            }
        }   /* for (;;) */

        /*======================================*/
        /* a '0' may follow the flag character  */
        /* this is the requested fill character */
        /*======================================*/
        if (*format == '0')
        {
            zeropad = 1;
            format++;
        }
        else
        {
            zeropad = 0;
        }

        /*===================================*/
        /* Optional field width (may be '*') */
        /*===================================*/
        if (*format == '*')
        {
            /*lint -e147 -e586*/
            field_width = va_arg(ap, VOS_INT32);
            /*lint +e147 +e586*/
            if (field_width < 0)
            {
                field_width = (VOS_CHAR)(-field_width);
                left_adjust = (VOS_CHAR)(!left_adjust);
            }   /* if () */
            format++;
        }
        else
        {
            field_width = 0;
            while (*format >= '0' && *format <= '9')
            {
                field_width = field_width * 10 + (*format++ - '0');
            }
        }   /* if () */

        /*=============================*/
        /* Optional precision (or '*') */
        /*=============================*/
        if (*format=='.')
        {
            if (*++format == '*')
            {
                /*lint -e147 -e586*/
                precision = va_arg(ap, VOS_INT32);
                /*lint +e147 +e586*/
                format++;
            }
            else
            {
                precision = 0;
                while (*format >= '0' && *format <= '9')
                {
                    precision = precision * 10 + (*format++ - '0');
                }
            }   /* if () */
        }
        else
        {
            precision = -1;
        }

        /*======================================================*/
        /* At this point, "left_adjust" is nonzero if there was */
        /* a sign, "zeropad" is 1 if there was a leading zero   */
        /* and 0 otherwise, "field_width" and "precision"       */
        /* contain numbers corresponding to the digit strings   */
        /* before and after the decimal point, respectively,    */
        /* and "flag_char" is either 0 (no flag) or contains    */
        /* a plus or space character. If there was no decimal   */
        /* point, "precision" will be -1.                       */
        /*======================================================*/

        /*========================*/
        /* Optional "l" modifier? */
        /*========================*/
        if (*format == 'l')
        {
            length = 1;
            format++;
        }
        else
            if (*format == 'F')
            {
                length = 1;
                format++;
            }
            else
            {
                length = 0;
            }

        /*===================================================*/
        /* At exit from the following switch, we will emit   */
        /* the characters starting at "buf_pointer" and      */
        /* ending at "ptr"-1                                 */
        /*===================================================*/
        switch (format_flag = *format++)
        {
        case 'c':
            /*lint -e147 -e586*/
            buf[0] = (VOS_CHAR)va_arg(ap, VOS_INT32);
            /*lint +e147 +e586*/
            ptr = buf_pointer = &buf[0];
            if (buf[0])
            {
                ptr++;
            }
            break;

        case 's':
            /*lint -e147 -e586*/
            if ((buf_pointer = va_arg(ap,VOS_CHAR *)) == NULL_PTR)
            {
                /*lint +e147 +e586*/
                buf_pointer = "(null pointer)";
            }
            if (precision < 0)
            {
                precision = 10000;
            }
            for (n=0; *buf_pointer++ && n < precision; n++)
            {
                ;
            }
            ptr = --buf_pointer;
            buf_pointer -= n;
            break;

        case 'o':
        case 'p':
        case 'X':
        case 'x':
            if (format_flag == 'p')
            { /* huyong ??? ---- %p和标准的输出不同 */
                if (length)
                {
                    /*lint -e147 -e586*/
                    ulong = (VOS_UINT_PTR)va_arg(ap,VOS_CHAR *);
                    /*lint +e147 +e586*/
                }
                else
                {
                    /*lint -e147 -e586*/
                    ulong = (VOS_UINT_PTR)va_arg(ap,VOS_CHAR *);
                    /*lint +e147 +e586*/
                }
            }
            else if (length)
            {
                /*lint -e147 -e586*/
                ulong = va_arg(ap,VOS_UINT32);
                /*lint +e147 +e586*/
            }
            else
            {
                /*lint -e147 -e586*/
                ulong = (VOS_UINT_PTR)va_arg(ap,VOS_INT32);
                /*lint +e147 +e586*/
            }

            ptr = buf_pointer = &buf[FRMWRI_BUFSIZE - 1];
            hex = "0123456789ABCDEF";
            if (format_flag == 'o')
            {
                mask = 0x7;
                nr_of_bits = 3;
            }
            else
            {
                if (format_flag == 'x')
                {
                    hex = "0123456789abcdef";
                }
                mask = 0xf;
                nr_of_bits = 4;
            }   /* if () */

            do
            {
                *--buf_pointer = *(hex + ((VOS_INT32) ulong & mask));
            }
            while ( ( ulong >>= nr_of_bits ) != 0 );

            if (precision < 0)          /* "precision" takes precedence */
            {
                if (zeropad)
                {
                    precision = field_width;
                }
            }
            while (precision > ptr - buf_pointer)
            {
                *--buf_pointer = '0';
            }
            break;

        case 'd':
        case 'i':
        case 'u':
            if (length)
            {
                /*lint -e147 -e586*/
                num = va_arg(ap,VOS_INT32);
                /*lint +e147 +e586*/
            }
            else
            {
                /*lint -e147 -e586*/
                n = va_arg(ap,VOS_INT32);
                /*lint +e147 +e586*/
                num = (VOS_INT32) n;
            }   /* if () */
            if ( format_flag != 'u' && num < 0  )
            {
                n = 1;
                flag_char = '-';
                ulong = (VOS_UINT32)-num;
            }
            else
            {
                n = (VOS_INT)(flag_char != 0);
                ulong = (VOS_UINT32)num;
            }   /* if () */

            /*=======================*/
            /* now convert to digits */
            /*=======================*/
            ptr = buf_pointer = &buf[FRMWRI_BUFSIZE - 1];
            do
            {
                *--buf_pointer = (VOS_CHAR)((ulong % 10) + '0');
            }
            while ( (ulong /= 10) != 0 );

            if (precision < 0)        /* "precision" takes precedence */
            {
                if (zeropad)
                {
                    precision = field_width - n;
                }
            }
            while (precision > ptr - buf_pointer)
            {
                *--buf_pointer = '0';
            }
            break;

        case 'f':
            format_flag = 0;
            /*fall though*/
        case 'e':
            /*fall though*/
        case 'E':
#ifdef VOS_FLOAT_SUPPORT
            /* Because can't find float_conversion,so comment these code. these should be added. */
            #if 0
            if (precision < 0)
            {
                precision = 6;
            }
            buf_pointer = buf;
            if ((fvalue = va_arg(ap,VOS_DOUBLE)) < 0)
            {
                flag_char = '-';
                fvalue = -fvalue;
            }   /* if () */

            ptr = float_conversion (fvalue, precision, buf, format_flag);
            #endif
            ptr = buf_pointer = "FLOATS can't support now!";
#else
            ptr = buf_pointer = "FLOATS? wrong formatter installed!";
            while (*ptr)
            {
                ptr++;
            }
#endif
            break;
        
        case 'T':
            /*lint -e147 -e586*/
            num = va_arg(ap,VOS_INT32);
            /*lint +e147 +e586*/
            _Second2DateTime((VOS_UINT32)num, &ulDate, &ulTime);

            ptr = buf_pointer = &buf[FRMWRI_BUFSIZE - 1];

            /* second */
            ulong = ulTime & 0xff;
            /*do
                *--buf_pointer = (CHAR)(( ulong % 10) + '0');
            while ( (ulong /= 10) != 0 );*/
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            *--buf_pointer = ':';

            /* minute */
            ulong = ( ulTime >> 8 ) & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            *--buf_pointer = ':';

            /* hour */
            ulong = ulTime >> 16;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            *--buf_pointer = ' ';

            /* date */
            ulong = ulDate & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            *--buf_pointer = '/';

            /* month */
            ulong = ( ulDate >> 8 ) & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            *--buf_pointer = '/';

            /* year */
            ulong = ulDate >> 16;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            break;

        case 't':
            /*lint -e147 -e586*/
            num = va_arg(ap,VOS_INT32);
            /*lint +e147 +e586*/
            _Second2DateTime((VOS_UINT32)num, &ulDate, &ulTime);

            ptr = buf_pointer = &buf[FRMWRI_BUFSIZE - 1];

            /* date */
            ulong = ulDate & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            *--buf_pointer = '/';

            /* month */
            ulong = ( ulDate >> 8 ) & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            *--buf_pointer = '/';

            /* year */
            ulong = ulDate >> 16;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');
            ulong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulong % 10) + '0');

            break;

        case '\0':              /* Really bad place to find NUL in */
        format--;
        /*lint -e616 */
        default:
        /*lint +e616 */
        /*=======================*/
        /* Undefined conversion! */
        /*=======================*/
        /*lint -e585 */
        ptr = buf_pointer = "???";
        /*lint +e585 */
        ptr += 4;
        break;
        }   /* switch () */

        /*===========================================================*/
        /* This part emittes the formatted string to "put_one_char". */
        /*===========================================================*/
        if ((length = ptr - buf_pointer) > field_width)
        {
            n = 0;
        }
        else
        {
            n = field_width - length - (VOS_INT)(flag_char != 0);
        }

        /*=================================*/
        /* emit any leading pad characters */
        /*=================================*/
        if (!left_adjust)
        {
            while (--n >= 0)
            {
                put_one_char(' ', secret_pointer,str);

            }   /* while () */
        }

        /*===============================*/
        /* emit flag characters (if any) */
        /*===============================*/
        if (flag_char)
        {
            put_one_char((VOS_UINT8)flag_char, secret_pointer,str);

        }   /* if () */

        /*========================*/
        /* emit the string itself */
        /*========================*/
        while (--length >= 0)
        {
            put_one_char((VOS_UINT8)(*buf_pointer++), secret_pointer,str);

        }   /* while () */

        /*================================*/
        /* emit trailing space characters */
        /*================================*/
        if (left_adjust)
        {
            while (--n >= 0)
            {
                put_one_char(' ', secret_pointer,str);

            }   /* while () */
        }
    }   /* for (;;) */


}   /* _C_formatter(,,,) */

/*****************************************************************************
 Function   : comio
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID comio(VOS_UINT8 output, VOS_VOID *number,VOS_CHAR * strbuf)
{
    /* (*((VOS_INT32 *) number))++;*/

    /*if (output == '\n')
    {
        *(strbuf+*((VOS_INT32 *)number))=('\r');
        (*((VOS_INT32*)number))++;
        if( (*((VOS_INT32 *)number)) == (Str_Length-1))  *((VOS_INT32 *)number)-=1;
    }*/

    *(strbuf+*((VOS_INT32 *)number))=(VOS_INT8)output;
    (*((VOS_INT32 *)number))++;
    if( (*((VOS_INT32 *)number)) == (Str_Length-1))  *((VOS_INT32 *)number)-=1;
}

#ifdef FLOAT_SUPPORT

#if VOS_BYTE_ORDER == VOS_BIG_ENDIAN

typedef struct IEEEdp
{
    VOS_UINT sign :  1;
    VOS_UINT  exp : 11;
    VOS_UINT manh : 20;
    VOS_UINT manl : 32;
}IEEEdp;

#elif VOS_BYTE_ORDER == VOS_LITTLE_ENDIAN

typedef struct IEEEdp
{
    VOS_UINT manl : 32;
    VOS_UINT manh : 20;
    VOS_UINT  exp : 11;
    VOS_UINT sign :  1;
}IEEEdp;

#else
#error "Unknown VOS_BYTE_ORDER"
#endif /*VOS_BYTE_ORDER*/


VOS_INT v_isnan(VOS_DOUBLE d)
{
    register IEEEdp *p = (IEEEdp *)&d;

    return(p->exp == 0x7FF && (p->manh || p->manl));
}

VOS_INT v_isinf(VOS_DOUBLE d)
{
    register IEEEdp *p = (IEEEdp *)&d;

    return(p->exp == 0x7FF && !p->manh && !p->manl);
}

int cvt(double number,register int prec,
         int flags,
         unsigned char  fmtch,
         char *signp,
         char *startp,
         char *endp)
 {
     register char *p, *t;
     register double fract;
     int dotrim, expcnt, gformat;
     double integer, tmp;

     /* do this before tricky precision changes */
     if (v_isinf(number)) {
        /*lint -e534*/
         VOS_StrCpy(startp, "Inf");
        /*lint +e534*/

         return 3; /*strlen("Inf")*/
     }

     if (v_isnan(number)) {
        /*lint -e534*/
         VOS_StrCpy(startp, "NaN");
        /*lint +e534*/

         return 3; /*strlen("NaN")*/
     }


     expcnt = gformat = 0;
     fract = modf(number, &integer);

     /* get an extra slot for rounding. */
     t = ++startp;

     
     /*lint -e440 -e443 */
     for (p = endp - 1; integer; ++expcnt) {
         tmp = modf(integer / 10, &integer);
         *p-- = (char)(tochar((int)((tmp + .01) * 10)));
     }
     /*lint +e440 +e443 */
     switch(fmtch) {
     case 'f':
         /* reverse integer into beginning of buffer */
         if (expcnt)
             /*lint -e722 */
             for (; ++p < endp; *t++ = *p);
             /*lint +e722 */
         else
             *t++ = '0';
         /*
          * if precision required or alternate flag set, add in a
          * decimal point.
          */
         if (prec || flags&ALT)
             *t++ = '.';
         /* if requires more precision and some fraction left */
         if (fract) {
             if (prec)
                 do {
                     fract = modf(fract * 10, &tmp);
                     *t++ = (char)(tochar((int)tmp));
                 } while (--prec && fract);
             if (fract)
                 startp = vos_round(fract, (int *)NULL, startp,
                     t - 1, (char)0, signp);
         }
         /*lint -e722 */
         for (; prec--; *t++ = '0');
         /*lint +e722 */
         break;
     case 'e':
     case 'E':
 eformat:    if (expcnt) {
             *t++ = *++p;
             if (prec || flags&ALT)
                 *t++ = '.';
             /* if requires more precision and some integer left */
             /*lint -e722 */
             for (; prec && ++p < endp; --prec)
             /*lint +e722 */
                 *t++ = *p;
             /*
              * if done precision and more of the integer component,
              * round using it; adjust fract so we don't re-round
              * later.
              */
             if (!prec && ++p < endp) {
                 fract = 0;
                 startp = vos_round((double)0, &expcnt, startp,
                     t - 1, *p, signp);
             }
             /* adjust expcnt for digit in front of decimal */
             --expcnt;
         }
         /* until first fractional digit, decrement exponent */
         else if (fract) {
             /* adjust expcnt for digit in front of decimal */
             /*lint -e722 */
             for (expcnt = -1;; --expcnt) {
             /*lint +e722 */
                 fract = modf(fract * 10, &tmp);
                 if (tmp)
                     break;
             }
             *t++ = (char)tochar((int)tmp);
             if (prec || flags&ALT)
                 *t++ = '.';
         }
         else {
             *t++ = '0';
             if (prec || flags&ALT)
                 *t++ = '.';
         }
         /* if requires more precision and some fraction left */
         if (fract) {
             if (prec)
                 do {
                     fract = modf(fract * 10, &tmp);
                     *t++ = (char)(tochar((int)tmp));
                 } while (--prec && fract);
             if (fract)
                 startp = vos_round(fract, &expcnt, startp,
                     t - 1, (char)0, signp);
         }
         /* if requires more precision */
         /*lint -e722 */
         for (; prec--; *t++ = '0');
         /*lint +e722 */

         /* unless alternate flag, trim any g/G format trailing 0's */
         if (gformat && !(flags&ALT)) {
             while (t > startp && *--t == '0')
             {
                ;
             }
             if (*t == '.')
                 --t;
             ++t;
         }
         t = exponent(t, expcnt, fmtch);
         break;
     case 'g':
     case 'G':
         /* a precision of 0 is treated as a precision of 1. */
         if (!prec)
             ++prec;
         /*
          * ``The style used depends on the value converted; style e
          * will be used only if the exponent resulting from the
          * conversion is less than -4 or greater than the precision.''
          *    -- ANSI X3J11
          */
         if (expcnt > prec || (!expcnt && fract && (fract < .0001))) {
             /*
              * g/G format counts "significant digits, not digits of
              * precision; for the e/E format, this just causes an
              * off-by-one problem, i.e. g/G considers the digit
              * before the decimal point significant and e/E doesn't
              * count it as precision.
              */
             --prec;
             fmtch -= 2;        /* G->E, g->e */
             gformat = 1;
             /*lint -e801 屏蔽goto语句*/
             goto eformat;
             /*lint +e801 屏蔽goto语句*/
         }
         /*
          * reverse integer into beginning of buffer,
          * note, decrement precision
          */
         if (expcnt)
             /*lint -e722 */
             for (; ++p < endp; *t++ = *p, --prec);
             /*lint +e722 */
         else
             *t++ = '0';
         /*
          * if precision required or alternate flag set, add in a
          * decimal point.  If no digits yet, add in leading 0.
          */
         if (prec || flags&ALT) {
             dotrim = 1;
             *t++ = '.';
         }
         else
             dotrim = 0;
         /* if requires more precision and some fraction left */
         if (fract) {
             if (prec) {
                 do {
                     fract = modf(fract * 10, &tmp);
                     *t++ = (char)tochar((int)tmp);
                 } while(!tmp);
                 while (--prec && fract) {
                     fract = modf(fract * 10, &tmp);
                     *t++ = (char)tochar((int)tmp);
                 }
             }
             if (fract)
                 startp = vos_round(fract, (int *)NULL, startp,
                     t - 1, (char)0, signp);
         }
         /* alternate format, adds 0's for precision, else trim 0's */
         if (flags&ALT)
             /*lint -e722 */
             for (; prec--; *t++ = '0')
             {
                ;
             }
             /*lint +e722 */
         else if (dotrim) {
             while (t > startp && *--t == '0')
             {
                ;
             }
             if (*t != '.')
                 ++t;
         }
         else
         {
            ;
         }
        break;
     /*lint -e616 */
     default:
        break;
     /*lint +e616 */
     }
     return(t - startp);
 }
/*lint -e578 */
char *vos_round(double fract,    int *exp,
        char *start, char *end,
         char ch,
         char *signp)
{
/*lint +e578 */
     double tmp;

     if (fract)
         (void)modf(fract * 10, &tmp);
     else
         tmp = todigit(ch);
     if (tmp > 4)
         for (;; --end) {
             if (*end == '.')
                 --end;
             if (++*end <= '9')
                 break;
             *end = '0';
             if (end == start) {
                 if (exp) {    /* e/E; increment exponent */
                     *end = '1';
                     ++*exp;
                 }
                 else {        /* f; add extra digit */
                     *--end = '1';
                     --start;
                 }
                 break;
             }
         }
     /* ``"%.3f", (double)-0.0004'' gives you a negative 0. */
     else if (*signp == '-')
         for (;; --end) {
             if (*end == '.')
                 --end;
             if (*end != '0')
                 break;
             if (end == start)
                 *signp = 0;
         }
     return(start);
}
#endif

/*****************************************************************************
 Function   : exponent
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
/*lint -e578 */
char *exponent(char *p,int exp, unsigned char fmtch)
{
/*lint +e578 */

     register char *t;
     char expbuf[MAXEXP];

     *p++ =(char)fmtch;
     if (exp < 0) {
         exp = -exp;
         *p++ = '-';
     }
     else
         *p++ = '+';
     t = expbuf + MAXEXP;
     if (exp > 9) {
         do {
             *--t = (char)(tochar(exp % 10));
         } while ((exp /= 10) > 9);
         *--t = (char)(tochar(exp));
         /*lint -e722 */
         for (; t < expbuf + MAXEXP; *p++ = *t++)
         /*lint +e722 */
         {

         }
     }
     else {
         *p++ = '0';
         *p++ = (char)(tochar(exp));
     }
     return(p);
}

/*****************************************************************************
 Function   : ANSI_vsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 ANSI_vsprintf(VOS_CHAR *out_buf, const VOS_CHAR *fmt0, va_list argp)
{
    VOS_INT                 lChar;
    VOS_INT                 ltemp;
    VOS_INT                 lBase;
    VOS_INT                 lDprec;
    VOS_INT                 lFieldSize;
    VOS_INT                 lFlags;
    VOS_INT                 lFpprec;
    VOS_INT                 lPrec;
    VOS_INT                 lRealSize;
    VOS_INT                 lConverSize;
    VOS_INT                 lFormatWidth;
    VOS_UINT_PTR            ulLong;
    VOS_CHAR                ucPrefixSign;
    VOS_CHAR                *pucDigs;
    VOS_CHAR                ucBuf[BUF];
    VOS_CHAR                *pcBuf;
    VOS_CHAR                *pucOutBuf=out_buf;
    VOS_UCHAR               *pucFmt;
#ifdef FLOAT_SUPPORT
    VOS_CHAR                ucSoftSign;
#endif
    VOS_INT32               num;
    VOS_UINT32              ulTimelong;

    VOS_CHAR               *buf_pointer;

    VOS_UINT32              ulDate;             /* added by wuxiaoqian 2k/09/20 for "%t"*/
    VOS_UINT32              ulTime;             /* added by wuxiaoqian 2k/09/20 for "%t"*/

    pucFmt = (VOS_UCHAR *)fmt0;
    pucDigs = "0123456789abcdef";
    /*lint -e801 -e445 */
    for (;; ++pucFmt)
    {
            for (; ((lChar = *pucFmt)!=0) && lChar != '%'; ++pucFmt)
            {
                *pucOutBuf++ =(VOS_CHAR) lChar;
            }
            if (!lChar)
            {
                goto    lvspret;
            }

            lFlags = 0; lDprec = 0; lFpprec = 0; lFormatWidth = 0;
            lPrec = -1;
            ucPrefixSign = '\0';

rflag:  switch (*++pucFmt) {
        case ' ':
            if (!ucPrefixSign)
            {
                ucPrefixSign = ' ';
            }
            goto rflag;
        case '#':
            lFlags |= ALT;
            goto rflag;
        case '*':
            /*lint -e147 -e586*/
            if ((lFormatWidth = va_arg(argp, VOS_INT)) >= 0)
            {
                /*lint +e147 +e586*/
                goto rflag;
            }
            lFormatWidth = -lFormatWidth;
        /*lint -e616 */
        case '-':
        /*lint +e616 */
            lFlags |= LADJUST;
            goto rflag;
        case '+':
            ucPrefixSign = '+';
            goto rflag;
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
            goto rflag;
        case '0':
            lFlags |= ZEROPAD;
            goto rflag;
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
            do {
                ltemp = 10 * ltemp + todigit(*pucFmt);
            } while (isascii(*++pucFmt) && isdigit(*pucFmt));
            lFormatWidth = ltemp;
            --pucFmt;
            goto rflag;
        case 'L':
            lFlags |= LONGDBL;
            goto rflag;
        case 'h':
            lFlags |= SHORTINT;
            goto rflag;
        case 'l':
            lFlags |= LONGINT;
            goto rflag;
        case 'c':
            /*lint -e147 -e586*/
            *(pcBuf = ucBuf) = (VOS_CHAR)va_arg(argp, VOS_INT);
            /*lint +e147 +e586*/
            lConverSize = 1;
            ucPrefixSign = '\0';
            goto pforw;
        case 'D':
            lFlags |= LONGINT;
        /*lint -e616 */
        case 'd':
        /*lint +e616 */
        case 'i':
            /*lint -e147 -e586*/
            ARG(int);
            /*lint +e147 +e586*/
            if ((VOS_INT32)ulLong < 0)
            {
                ulLong = (VOS_UINT32)(-(VOS_INT32)ulLong);
                ucPrefixSign = '-';
            }
            lBase = 10;
            goto number;
#ifdef FLOAT_SUPPORT
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':

        {
            VOS_DOUBLE udDouble;
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
            goto pforw;
        }
#endif
        case 'n':
            if (lFlags & LONGINT)
            {
                /*lint -e147 -e586*/
                *va_arg(argp, VOS_INT32 *) = (VOS_INT32)(pucOutBuf-out_buf);
                /*lint +e147 +e586*/
            }
            else if (lFlags & SHORTINT)
            {
                /*lint -e147 -e586*/
                *va_arg(argp, VOS_INT16 *) = (VOS_INT16)(pucOutBuf-out_buf);
                /*lint +e147 +e586*/
            }
            else
            {
                /*lint -e147 -e586*/
                *va_arg(argp, VOS_INT *) = (VOS_INT)(pucOutBuf-out_buf);
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
            goto nosign;
        case 'p':
            /*lint -e147 -e586*/
            ulLong = (VOS_UINT_PTR)va_arg(argp, VOS_VOID *);
            /*lint +e147 +e586*/
            lBase = 16;
            goto nosign;
        case 's':
            /*lint -e147 -e586*/
            if ( (pcBuf = va_arg(argp, VOS_CHAR *))==0 )
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
                lConverSize =(VOS_INT)VOS_StrLen(pcBuf);
            }
            ucPrefixSign = '\0';
            goto pforw;
        case 'U':
            lFlags |= LONGINT;
        /*lint -e616 */
        case 'u':
        /*lint +e616 */
            /*lint -e147 -e586*/
            ARG(unsigned);
            /*lint +e147 +e586*/
            lBase = 10;
            goto nosign;
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

nosign:            ucPrefixSign = '\0';

number:    if ((lDprec = lPrec) >= 0)
            {
                lFlags &= ~ZEROPAD;
            }

            pcBuf = ucBuf + BUF;
            if (ulLong != 0 || lPrec != 0)
            {
                do {
                    *--pcBuf = pucDigs[ulLong %(VOS_UINT32) lBase];
                    ulLong /=(VOS_UINT32) lBase;
                } while (ulLong);
                pucDigs = "0123456789abcdef";
                if (lFlags & ALT && lBase == 8 && *pcBuf != '0')
                {
                    *--pcBuf = '0';
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
                    *pucOutBuf++=' ';
                }
            }

            if (ucPrefixSign)
            {
                *pucOutBuf++=ucPrefixSign;
            }
            if (lFlags & HEXPREFIX)
            {
                *pucOutBuf++='0';
                *pucOutBuf++=(char)*pucFmt;
            }
            if ((lFlags & (LADJUST|ZEROPAD)) == ZEROPAD)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    *pucOutBuf++='0';
                }
            }
            for (ltemp = lFieldSize; ltemp < lDprec; ltemp++)
            {
                *pucOutBuf++='0';
            }

            ltemp = lConverSize;
            while (--ltemp >= 0)
            {
                *pucOutBuf++=*pcBuf++;
            }

            while (--lFpprec >= 0)
            {
                *pucOutBuf++='0';
            }

            if (lFlags & LADJUST)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    *pucOutBuf++=' ';
                }
            }

            break;
        case '\0':
                        goto    lvspret;
        case 'T':
            /*lint -e147 -e586*/
            num = va_arg(argp,VOS_INT32);
            /*lint +e147 +e586*/
            _Second2DateTime((VOS_UINT32)num, &ulDate, &ulTime);

            buf_pointer = &ucBuf[BUF- 1];

            /* second */
            ulTimelong = ulTime & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            *--buf_pointer = ':';

            /* minute */
            ulTimelong = ( ulTime >> 8 ) & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            *--buf_pointer = ':';

            /* hour */
            ulTimelong = ulTime >> 16;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            *--buf_pointer = ' ';

            /* date */
            ulTimelong = ulDate & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            *--buf_pointer = '/';

            /* month */
            ulTimelong = ( ulDate >> 8 ) & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            *--buf_pointer = '/';

            /* year */
            ulTimelong = ulDate >> 16;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            /*lint -e534*/
            VOS_StrNCpy(pucOutBuf, buf_pointer, 19);
            /*lint +e534*/
            pucOutBuf += 19 ;
            continue ;

        case 't':
            /*lint -e147 -e586*/
            num = va_arg(argp,VOS_INT32);
            /*lint +e147 +e586*/
            _Second2DateTime((VOS_UINT32)num, &ulDate, &ulTime);

            buf_pointer = &ucBuf[BUF- 1];

            /* date */
            ulTimelong = ulDate & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            *--buf_pointer = '/';

            /* month */
            ulTimelong = ( ulDate >> 8 ) & 0xff;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            *--buf_pointer = '/';

            /* year */
            ulTimelong = ulDate >> 16;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');
            ulTimelong /= 10;
            *--buf_pointer = (VOS_CHAR)(( ulTimelong % 10) + '0');

            /*lint -e534*/
            VOS_StrNCpy(pucOutBuf, buf_pointer, 10);
            /*lint +e534*/
            pucOutBuf += 10 ;

            continue ;
        default:
                        *pucOutBuf++=(char)*pucFmt;

        }
    }
    /*lint +e801 +e445 */
lvspret:
        *pucOutBuf=0;
        return (VOS_INT)(pucOutBuf-out_buf);
}

/*****************************************************************************
 Function   : VOS_vsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 VOS_vsprintf(VOS_CHAR * str,const VOS_CHAR *format,va_list argument)
{
    VOS_INT32 i;

    if (( VOS_NULL_PTR == str ) || ( VOS_NULL_PTR == format ) )
    {
        return -1;
    }

    i=(VOS_INT32)ANSI_vsprintf( str , format , argument );
    return i;
}

/*****************************************************************************
 Function   : VOS_sprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 VOS_sprintf(VOS_CHAR *str, const VOS_CHAR *fmt, ...)
{

    /*lint -e530 -e830 */
    va_list arg;
    register VOS_INT32 nc;

    /* HY17247 */
    if (( VOS_NULL_PTR == str ) || ( VOS_NULL_PTR == fmt ) )
    {
        return -1;
    }

    /*lint -e586*/
    va_start(arg, fmt);
    /*lint +e586*/
    nc = ANSI_vsprintf(str, (const VOS_CHAR *) fmt, arg);
    /*lint -e586*/
    va_end(arg);
    /*lint +e586*/
    return (nc);
    /*lint +e530 +e830 */
}

#define LENGTH_OF_PRINT_LINE_BUF        1024

/*****************************************************************************
 Function   : vos_assert
 Description: Report an assert
 Input      : pcFileName -- File name of this assert occuring
              ulLineNo   -- Line number of this assert occuring
 Output     : None
 Return     : None
 *****************************************************************************/
VOS_VOID vos_assert( VOS_UINT32 ulFileID, VOS_INT LineNo)
{
    /*lint -e813 */
    VOS_CHAR vos_PrintBuf[LENGTH_OF_PRINT_LINE_BUF];
    /*lint +e813 */

    VOS_CHAR *String = "Assert";

    /*lint -e534*/
    VOS_sprintf( vos_PrintBuf, "%s File: %d, Line: %d", String, ulFileID, LineNo );

    vos_printf("\n %s.\r\n",vos_PrintBuf);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : PrintHexBuf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID PrintHexBuf(char *PrintBuf, char *MemBuf, int Length)
{
    /*char vos_PrintBuf[LENGTH_OF_PRINT_LINE_BUF];*/
    int i,HalfByte;
    char *ptrPrintBuf;
    unsigned char *Buf;

    if(Length >= LENGTH_OF_PRINT_LINE_BUF/3-1)
        return;

    ptrPrintBuf = PrintBuf;
    Buf = (unsigned char*)MemBuf;
    for(i=0;i<Length;i++)
    {
        HalfByte = Buf[i]/16;
        if(HalfByte < 0x0A)
            *ptrPrintBuf = (char)(HalfByte + '0');
        else
           *ptrPrintBuf = (char)(HalfByte - 0x0A + 'A');
        ptrPrintBuf++;

        HalfByte = Buf[i]%16;
        if(HalfByte < 0x0A)
            *ptrPrintBuf = (char)(HalfByte + '0');
        else
            *ptrPrintBuf = (char)(HalfByte - 0x0A + 'A');
        ptrPrintBuf++;

        *ptrPrintBuf = ' ';
        ptrPrintBuf++;
    }

    *ptrPrintBuf = '\0';
    return;
}

/*****************************************************************************
 Function   : PrintMemBuf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID PrintMemBuf(char *String ,char *Buf, int Length)
{
    /*lint -e813 */
    char vos_PrintBuf[LENGTH_OF_PRINT_LINE_BUF];
    /*lint +e813 */
    int iNumber;

    /* lint -e534 */
    /* iNumber = sprintf( vos_PrintBuf, "\n%s",String); */

    iNumber = VOS_sprintf( vos_PrintBuf, "\n%s",String);
    
    PrintHexBuf(&vos_PrintBuf[iNumber], Buf, Length);

    /*lint -e534*/
    vos_printf("\n%s.\r\n", vos_PrintBuf);
    /*lint +e534*/

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



