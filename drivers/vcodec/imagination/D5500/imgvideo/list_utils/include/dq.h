/*!
 *****************************************************************************
 *
 * @File       dq.h
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

#ifndef DQ_H
#define DQ_H

#if defined (__cplusplus)
extern "C" {
#endif

#ifdef DQ_INLINE
#define DQ_FQUALS inline static
#else
#ifdef DQ_FQUALS
#undef DQ_FQUALS
#endif
#define DQ_FQUALS 
#endif
	
/* Macro definitions */
	
#define  DQ_LINK DQ_LINKAGE_T DQ_link
		
/* Type definitions */
	
typedef struct DQ_tag { 
    struct DQ_tag *fwd;
    struct DQ_tag *back;
}DQ_LINKAGE_T ; /* Private  */
typedef struct {
    DQ_LINK;
}DQ_T ; /* Anonymous */

/* Function Prototypes */
DQ_FQUALS void DQ_addAfter(void *predecessor, void *item);
		DQ_FQUALS void DQ_addBefore(void *successor, void *item);
		DQ_FQUALS void DQ_addHead(DQ_T *queue, void *item);
		DQ_FQUALS void DQ_addTail(DQ_T *queue, void *item);
		DQ_FQUALS int DQ_empty(DQ_T *queue);
		DQ_FQUALS void * DQ_first(DQ_T *queue);
		DQ_FQUALS void * DQ_last(DQ_T *queue);
		DQ_FQUALS void DQ_init(DQ_T *queue);
		DQ_FQUALS void DQ_move(DQ_T *from, DQ_T *to);
		DQ_FQUALS void * DQ_next(void *item);
		DQ_FQUALS void * DQ_previous(void *item);
		DQ_FQUALS void DQ_remove(void *item);
		DQ_FQUALS void * DQ_removeHead(DQ_T *queue);
		DQ_FQUALS void * DQ_removeTail(DQ_T *queue);

#if defined (__cplusplus)
}
#endif
 

#ifdef DQ_INLINE
#define DQ_CINCLUDE
#include "dq.c"
#undef DQ_CINCLUDE
#endif



#endif /* #ifndef DQ_H */


