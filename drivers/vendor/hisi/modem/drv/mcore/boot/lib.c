/*
 *  Copyright (C), 2015-2017, Hisilicon Technologies Co., Ltd.
 *
 * File name     : lib.c
 * Author        :
 * Created       : 2015-12-19
 * Last Modified :
 * Description   :
 * Modification  : Create file
 *
 */
#include <hi_uart.h>

void print_info_with_u32(const void *msg, unsigned int  ulValue )
{
    static const unsigned char hex_value[] = "0123456789ABCDEF";
    unsigned char curr_msg [ 16 ];
    unsigned char *p;
    print_info( msg );
    p = curr_msg;
    *p++ = hex_value[ (ulValue >> 28) & 0x0F ];
    *p++ = hex_value[ (ulValue >> 24) & 0x0F ];
    *p++ = hex_value[ (ulValue >> 20) & 0x0F ];
    *p++ = hex_value[ (ulValue >> 16) & 0x0F ];
    *p++ = hex_value[ (ulValue >> 12) & 0x0F ];
    *p++ = hex_value[ (ulValue >>   8) & 0x0F ];
    *p++ = hex_value[ (ulValue >>   4) & 0x0F ];
    *p++ = hex_value[ (ulValue >>   0) & 0x0F ];
    *p++ = 0;

    print_info( curr_msg );
}

