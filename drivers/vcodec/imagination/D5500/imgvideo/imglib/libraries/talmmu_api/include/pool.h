/*!
 *****************************************************************************
 *
 * @File       pool.h
 * @Description    Object Pool Memory Allocator.
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

#ifndef _pool_h_
#define _pool_h_

#if defined (__cplusplus)
    extern "C" {
#endif

struct sPool;

/*!
********************************************************************************

 @Function				POOL_Create

 @Description

 Create an sObject sPool

 @Input     pszName     : Name of sObject sPool for diagnostic purposes

 @Input     ui32Size    : size of each sObject in the sPool in bytes

 @Output    ppsPool     : Will contain NULL or sObject sPool handle

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Create(
    const   IMG_CHAR * const    pszName, 
            IMG_UINT32          ui32Size,
    struct  sPool ** const      ppsPool
);

/*!
********************************************************************************

 @Function				POOL_Delete

 @Description

 Delete an sObject sPool. All psObjects allocated from the sPool must
 be free'd with pool_free() before deleting the sObject sPool.

 @Input	    psPool      : Object Pool pointer

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Delete(
    struct sPool * const psPool
);

/*!
********************************************************************************

 @Function				POOL_Alloc

 @Description

 Allocate an sObject from an sObject sPool.

 @Input	    psPool      : Object Pool

 @Output    phObject    : Pointer containing the handle to
                           the object created or IMG_NULL

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Alloc(
    struct  sPool * const       psPool,
            IMG_HANDLE * const  phObject
);

/*!
********************************************************************************

 @Function				POOL_Free

 @Description

 Free an sObject previously allocated from an sObject sPool.

 @Input	    psPool      : Object Pool pointer.

 @Output    hObject     : Handle to the object to be freed.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Free(
    struct  sPool * const       psPool, 
            IMG_HANDLE const    hObject
);

#if defined (__cplusplus)
}
#endif

#endif
