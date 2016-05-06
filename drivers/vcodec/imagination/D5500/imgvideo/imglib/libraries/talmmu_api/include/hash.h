/*!
 *****************************************************************************
 *
 * @File       hash.h
 * @Description    Self scaling hash tables.
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

#ifndef _HASH_H_
#define _HASH_H_

#include <img_types.h>
#include <img_defs.h>

#if defined (__cplusplus)
    extern "C" {
#endif


struct sHash;

/*! 
******************************************************************************

 @Function				VID_HASH_Initialise

 @Description

 To initialise the hash module.

 @Input	    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT VID_HASH_Initialise(IMG_VOID);
         	
/*! 
******************************************************************************

 @Function				VID_HASH_Finalise

 @Description

 To finalise the hash module. All allocated hash tables should
	            be deleted before calling this function.

 @Input	    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT VID_HASH_Finalise(IMG_VOID);

/*! 
******************************************************************************

 @Function				VID_HASH_Create

 @Description

 Create a self scaling hash table.

 @Input	    ui32InitialSize : Initial and minimum size of the hash table.

 @Output    psHash          : Hash table handle or IMG_NULL.

 @Return    IMG_RESULT      : IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT VID_HASH_Create (
            IMG_UINT32      ui32InitialSize, 
    struct  sHash ** const  ppsHash
);

/*! 
******************************************************************************

 @Function				VID_HASH_Delete

 @Description

 To delete a hash table, all entries in the table should be
	            removed before calling this function.

 @Input	    psHash      : Hash table pointer

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT VID_HASH_Delete (struct sHash * const psHash);

/*! 
******************************************************************************

 @Function				VID_HASH_Insert

 @Description

 To insert a key value pair into a hash table.

 @Input	    psHash      : Hash table pointer

 @Input	    ui64Key     : Key value

 @Input	    uipValue    : The value associated with the key.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT VID_HASH_Insert(
    struct  sHash * const   psHash, 
            IMG_UINT64      ui64Key, 
            IMG_UINTPTR     uipValue
);

/*! 
******************************************************************************

 @Function				VID_HASH_Remove

 @Description

 To remove a key value pair from a hash table

 @Input	    psHash      : Hash table pointer

 @Input	    ui64Key     : Key value

 @Input	    uipResult   : 0 if the key is missing or the value associated with the key.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT VID_HASH_Remove(
    struct  sHash * const       psHash, 
            IMG_UINT64          ui64Key, 
            IMG_UINTPTR * const puipResult
);

#if defined (__cplusplus)
    }
#endif

#endif
