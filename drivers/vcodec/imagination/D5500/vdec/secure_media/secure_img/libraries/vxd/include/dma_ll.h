/*!
 *****************************************************************************
 *
 * @File       dma_ll.h
 * @Title      Utilities for MSVDX DMA linked list.
 * @Description    This file contains hardware related definitions and macros
 *  for MSVDX DMA linked list. DMA linked list is a feature which
 *  allows to transfer set of consecutive blocks without requestor
 *  intervention after initial setup. See the reference manual for
 *  further informations.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#if !defined (__DMA_LL_H__)
#define __DMA_LL_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_defs.h"
#include "img_types.h"
#ifndef VDEC_USE_PVDEC
#include "img_soc_dmac_regs_io2.h"
#include "img_soc_dmac_linked_list_io2.h"
#else /* def VDEC_USE_PVDEC */
#include "hwdefs/dmac_linked_list.h"
#include "hwdefs/dmac_regs.h"
#endif /* def VDEC_USE_PVDEC */
#include "reg_io2.h"

/*!
******************************************************************************

 This type defines the byte swap settings (see TRM "Transfer Sequence
 Linked-list - BSWAP").

******************************************************************************/
typedef enum
{
    DMAC_BSWAP_NO_SWAP = 0x0,   /*!< No byte swapping will be performed. */
    DMAC_BSWAP_REVERSE = 0x1,   /*!< Byte order will be reversed. */

} DMAC_eBSwap;

/*!
******************************************************************************

 This type defines the direction of the DMA transfer (see TRM "Transfer Sequence
 Linked-list - DIR").

******************************************************************************/
typedef enum
{
    DMAC_DIR_MEM_TO_PERI = 0x0, /*!< Data from memory to peripheral. */
    DMAC_DIR_PERI_TO_MEM = 0x1, /*!< Data from peripheral to memory. */

} DMAC_eDir;

/*!
******************************************************************************

 This type defines the peripheral width settings (see TRM "Transfer Sequence
 Linked-list - PW").

******************************************************************************/
typedef enum
{
    DMAC_PWIDTH_32_BIT = 0x0,       /*!< Peripheral width 32-bit. */
    DMAC_PWIDTH_16_BIT = 0x1,       /*!< Peripheral width 16-bit. */
    DMAC_PWIDTH_8_BIT  = 0x2,       /*!< Peripheral width 8-bit. */

} DMAC_ePW;

/*!
******************************************************************************

 This type defines whether the linked list element is last. (see TRM
 "Transfer Sequence Linked-list - List_FIN").

******************************************************************************/
typedef enum
{
    DMAC_LIST_FIN_OFF = 0,          /*!< No action. */
    DMAC_LIST_FIN_ON = 1            /*!< Generate interrupt, must be set for
                                         last element. */

} DMAC_eListFin;

/*!
******************************************************************************

 This type defines whether the peripheral address is static or
 auto-incremented.(see TRM "Transfer Sequence Linked-list - INCR").

******************************************************************************/
typedef enum
{
    DMAC_INCR_OFF = 0,          /*!< No action, no increment. */
    DMAC_INCR_ON  = 1           /*!< Generate address increment. */

} DMAC_eIncr;

/*!
******************************************************************************
 This type defines how much the peripheral address is incremented by
******************************************************************************/
typedef enum
{
    DMA_PERIPH_INCR_1    = 0x2,        //!< Increment peripheral address by 1
    DMA_PERIPH_INCR_2    = 0x1,        //!< Increment peripheral address by 2
    DMA_PERIPH_INCR_4    = 0x0,        //!< Increment peripheral address by 4

} DMA_ePeriphIncrSize;

/*!
******************************************************************************

 This type defines the access delay settings (see TRM "Transfer Sequence
 Linked-list - ACC_DEL").

******************************************************************************/
typedef enum
{
    DMAC_ACC_DEL_0      = 0x0,      /*!< Access delay zero clock cycles */
    DMAC_ACC_DEL_256    = 0x1,      /*!< Access delay 256 clock cycles */
    DMAC_ACC_DEL_512    = 0x2,      /*!< Access delay 512 clock cycles */
    DMAC_ACC_DEL_768    = 0x3,      /*!< Access delay 768 clock cycles */
    DMAC_ACC_DEL_1024   = 0x4,      /*!< Access delay 1024 clock cycles */
    DMAC_ACC_DEL_1280   = 0x5,      /*!< Access delay 1280 clock cycles */
    DMAC_ACC_DEL_1536   = 0x6,      /*!< Access delay 1536 clock cycles */
    DMAC_ACC_DEL_1792   = 0x7,      /*!< Access delay 1792 clock cycles */

} DMAC_eAccDel;

/*!
******************************************************************************

 This type defines the burst size settings (see TRM "Transfer Sequence
 Linked-list - BURST").

******************************************************************************/
typedef enum
{
    DMAC_BURST_0    = 0x0,      //!< burst size of 0
    DMAC_BURST_1    = 0x1,      //!< burst size of 1
    DMAC_BURST_2    = 0x2,      //!< burst size of 2
    DMAC_BURST_3    = 0x3,      //!< burst size of 3
    DMAC_BURST_4    = 0x4,      //!< burst size of 4
    DMAC_BURST_5    = 0x5,      //!< burst size of 5
    DMAC_BURST_6    = 0x6,      //!< burst size of 6
    DMAC_BURST_7    = 0x7,      //!< burst size of 7
    DMAC_BURST_8    = 0x8,      //!< burst size of 8

} DMAC_eBurst;


/*!
******************************************************************************

 This type defines the additional burst size settings (see TRM "Transfer
 Sequence Linked-list - EXT_BURST").

******************************************************************************/
typedef enum
{
    DMAC_EXT_BURST_0    = 0x0,      //!< no extension
    DMAC_EXT_BURST_1    = 0x1,      //!< extension of 8
    DMAC_EXT_BURST_2    = 0x2,      //!< extension of 16
    DMAC_EXT_BURST_3    = 0x3,      //!< extension of 24
    DMAC_EXT_BURST_4    = 0x4,      //!< extension of 32
    DMAC_EXT_BURST_5    = 0x5,      //!< extension of 40
    DMAC_EXT_BURST_6    = 0x6,      //!< extension of 48
    DMAC_EXT_BURST_7    = 0x7,      //!< extension of 56
    DMAC_EXT_BURST_8    = 0x8,      //!< extension of 64
    DMAC_EXT_BURST_9    = 0x9,      //!< extension of 72
    DMAC_EXT_BURST_10   = 0xa,      //!< extension of 80
    DMAC_EXT_BURST_11   = 0xb,      //!< extension of 88
    DMAC_EXT_BURST_12   = 0xc,      //!< extension of 96
    DMAC_EXT_BURST_13   = 0xd,      //!< extension of 104
    DMAC_EXT_BURST_14   = 0xe,      //!< extension of 112
    DMAC_EXT_BURST_15   = 0xf,      //!< extension of 120

} DMAC_eExtBurst;

/*!
******************************************************************************

 This type defines the 2D mode settings (see TRM "Transfer Sequence
 Linked-list - 2D_MODE").

******************************************************************************/
typedef enum
{
    DMAC_2DMODE_DISABLE     = 0x0,      /*!< Disable 2D mode */
    DMAC_2DMODE_ENABLE      = 0x1,      /*!< Enable 2D mode */

} DMAC_e2DMode;

#ifdef WIN32
    /*! DMAC_LinkElement alignment not required under Windows. */
#   define DMAC_ALIGN_16_BYTE
#else
    /*! DMAC_LinkElement must be 16-byte alligned */
#   define DMAC_ALIGN_16_BYTE       __attribute__ ((aligned (16)))
#endif

/*! Hardware defined of fields of linked list element */
typedef struct
{
    IMG_UINT32  ui32DMAWord_0;      /*!< Word 0 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_1;      /*!< Word 1 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_2;      /*!< Word 2 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_3;      /*!< Word 3 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_4;      /*!< Word 4 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_5;      /*!< Word 5 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_6;      /*!< Word 6 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_7;      /*!< Word 7 of DMA linked-list. */
} DMAC_LinkElement DMAC_ALIGN_16_BYTE;


/*!
******************************************************************************

 @Function              DMA_LL_SET_WD0

 @Description

 Set word 0 in a dma linked list entry.

 @Input    pList        : pointer to start of linked list entry

 @Input    BSWAP_VAL    : big/little endian byte swap (see DMA_eBSwap).

 @Input    DIR_VAL      : transfer direction (see DMA_eDir).

 @Input    PW_VAL       : peripheral width (see DMA_ePW).

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD0(pList, BSWAP_VAL, DIR_VAL, PW_VAL)                     \
    do{                                                                       \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD0, BSWAP, BSWAP_VAL);             \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD0, DIR, DIR_VAL);                 \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD0, PW, PW_VAL);                   \
    }while(0)


/*!
******************************************************************************

 @Function              DMA_LL_SET_WD1

 @Description

 Set word 1 in a dma linked list entry.

 @Input    pList        : pointer to start of linked list entry

 @Input    LIST_FIN_VAL : wheter elements is the last to be written

 @Input    PI_VAL       : how much to increment the peripheral address by
                          (see DMA_ePeriphIncrSize)

 @Input    INCR_VAL     : whether to increment the peripeheral address

 @Input    LEN_VAL      : length of transfer in peripheral width units

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD1(pList, LIST_FIN_VAL, PI_VAL, INCR_VAL, LEN_VAL)        \
    do    {                                                                   \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD1, LIST_FIN, LIST_FIN_VAL );      \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD1, PI, PI_VAL);                   \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD1, INCR, INCR_VAL);               \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD1, LEN, LEN_VAL);                 \
    }while(0)

/*!
******************************************************************************

 @Function              DMA_LL_SET_WD2

 @Description

 Set word 2 in a dma linked list entry.

 @Input    pList         : pointer to start of linked list entry

 @Input    PERI_ADDR_VAL : the perihperal address to transfer to/from

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD2(pList, PERI_ADDR_VAL)                                  \
    do {                                                                      \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD2, ADDR, PERI_ADDR_VAL);          \
    }while(0)

/*!
******************************************************************************

 @Function              DMA_LL_SET_WD3

 @Description

 Set word 3 in a dma linked list entry.

 @Input    pList             : pointer to start of linked list entry

 @Input    ACC_DEL_VAL       : access delay (see DMA_eAccDel)

 @Input    BURST_VAL         : burst size (see DMAc_eBurst)

 @Input    EXT_BURST_VAL     : extended burst size (see DMAC_eExtBurst)

 @Input    EXTSA_VAL         : extended start address

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD3(pList, ACC_DEL_VAL, BURST_VAL, EXT_BURST_VAL,          \
                       EXTSA_VAL)                                             \
    do {                                                                      \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD3, ACC_DEL, ACC_DEL_VAL);         \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD3, BURST, BURST_VAL);             \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD3, EXT_BURST, EXT_BURST_VAL);     \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD3, EXT_SA, EXTSA_VAL);            \
    }while(0)

/*!
******************************************************************************

 @Function              DMA_LL_SET_WD4

 @Description

 Set word 4 in a dma linked list entry.

 @Input    pList             : pointer to start of linked list entry

 @Input    MODE_2D_VAL       : enable/disable 2d mode (see DMA_eMode2D)

 @Input    REP_COUNT_VAL     : repeat count (the number of rows transferred)

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD4(pList, MODE_2D_VAL, REP_COUNT_VAL)                     \
    do {                                                                      \
    REGIO_WRITE_FIELD(pList, DMAC_LL, WD4, MODE_2D, MODE_2D_VAL);             \
    REGIO_WRITE_FIELD(pList, DMAC_LL, WD4, REP_COUNT, REP_COUNT_VAL);         \
    } while(0)

/*!
******************************************************************************

 @Function              DMA_LL_SET_WD5

 @Description

 Set word 5 in a dma linked list entry.

 @Input    pList             : pointer to start of linked list entry

 @Input    LINE_ADD_OFF_VAL  : number of bytes from the end of one row to the
                               start of the next row (only applicable when
                               using 2D transfer mode)

 @Input    ROW_LENGTH_VAL    : number of bytes per row
                               (only applicable when using 2D transfer mode)

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD5(pList, LINE_ADD_OFF_VAL, ROW_LENGTH_VAL)               \
    do{                                                                       \
    REGIO_WRITE_FIELD(pList, DMAC_LL, WD5, LINE_ADD_OFF, LINE_ADD_OFF_VAL);   \
    REGIO_WRITE_FIELD(pList, DMAC_LL, WD5, ROW_LENGTH, ROW_LENGTH_VAL);       \
    }while(0)

/*!
******************************************************************************

 @Function              DMA_LL_SET_WD6

 @Description

 Set word 6 in a dma linked list entry.

 @Input    pList             : pointer to start of linked list entry

 @Input    SA_VAL            : the host memory address to transfer to/from

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD6(pList, SA_VAL)                                         \
    do{                                                                       \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD6, SA, (SA_VAL));                 \
    }while(0)

/*!
******************************************************************************

 @Function              DMA_LL_SET_WD7

 @Description

 Set word 7 in a dma linked list entry.
 We have 128-bit boundary memory bus, so in LISTPTR, we need to set bits 31:4
 of byte start address of the system memory from where to read the linked
 list element describing the next transfer.

 @Input    pList              : pointer to start of linked list entry

 @Input    LISTPTR_VAL        : pointer to next linked list entry

 @Return   nothing

******************************************************************************/
#define DMA_LL_SET_WD7(pList, LISTPTR_VAL)                                    \
    do {                                                                      \
        REGIO_WRITE_FIELD(pList, DMAC_LL, WD7, LISTPTR,                       \
                         ( ((IMG_UINT32)(LISTPTR_VAL)) >> 4 ) );              \
    }while(0)

#if defined(__cplusplus)
}
#endif

#endif /* __DMA_LL_H__ */

