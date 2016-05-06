/*!
 *****************************************************************************
 *
 * @File       img_systypes.h
 * @Title      Base type definitions using linux kernel headers
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

#ifndef __IMG_SYSTYPES__
#define __IMG_SYSTYPES__

#ifdef __cplusplus
extern "C" {
#endif

/* Posix environment */
#include <linux/stddef.h> // size_t and ptrdiff_t
#include <linux/types.h>


/*
 * integral types
 */

//typedef             char    IMG_CHAR; 
typedef          s16    IMG_WCHAR;

//typedef	             int	IMG_INT;
typedef	          s8	IMG_INT8;
typedef	         s16	IMG_INT16;
typedef	         s32	IMG_INT32;
typedef	         s64	IMG_INT64;

//typedef	    unsigned int	IMG_UINT;
typedef          u8		IMG_UINT8;
typedef	        u16		IMG_UINT16;
typedef	        u32		IMG_UINT32;
typedef	        u64		IMG_UINT64;

/*
 * memory related
 */
typedef	              u8	IMG_BYTE;   	/**< @brief Atom of memory */
typedef           size_t    IMG_SIZE;     /**< @brief Unsigned integer returned by sizeof operator (i.e. big enough to hold any memory allocation) (C89) */
typedef        uintptr_t    IMG_UINTPTR;    /**< @brief Integer vairable that can hold a pointer value (C99) */
typedef        ptrdiff_t    IMG_PTRDIFF;    /**< @brief Large enought to hold the signed difference of 2 pointer values (C89) */

#ifdef __cplusplus
}//extern C
#endif

#endif /* __IMG_SYSTYPES__ */
