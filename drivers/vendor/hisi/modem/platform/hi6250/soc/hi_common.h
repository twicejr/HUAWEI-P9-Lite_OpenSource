/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_common.h */
/* Version       : 2.0 */
/* Created       : 2013-03-22*/
/* Last Modified : */
/* Description   :  The C union definition file for the module socp*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_COMMON_H__
#define __HI_COMMON_H__

#include "bsp_memmap.h"



static __inline__ void hi_ccore_reset(void)
{
    (*(volatile unsigned *) (HI_IO_ADDRESS(0x90000060))) = (0x8000);
}

static __inline__ void hi_ccore_active(void)
{
    (*(volatile unsigned *) (HI_IO_ADDRESS(0x90000064))) = (0x8000);
}

static __inline__ void hi_ccore_set_entry_addr(int a)
{
    (*(volatile unsigned *) (HI_IO_ADDRESS(0x90000418))) = (a);
}

static __inline__ void hi_acore_set_entry_addr(int a)
{
    (*(volatile unsigned *) (HI_IO_ADDRESS(0x90000414))) = (a);
}


#endif
