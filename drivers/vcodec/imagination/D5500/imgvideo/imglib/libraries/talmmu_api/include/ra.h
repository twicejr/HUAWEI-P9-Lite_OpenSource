/*!
 *****************************************************************************
 *
 * @File       ra.h
 * @Description    Resource Allocator API.
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

#ifndef _RA_H_
#define _RA_H_

//C99 integer types, specifically IMG_UINT64
#include <img_types.h>
#include <img_defs.h>

//system types, specifically size_t
#ifndef WINCE
    #if !defined(IMG_KERNEL_MODULE)
        #include <stddef.h>
        #include "sys/types.h"
    #endif
#endif

#if defined (__cplusplus)
extern "C" {
#endif

/*!
******************************************************************************

 @Function				VID_RA_Initialise

 @Description

 Initialises the RA module. Must be called before any other ra API function.

 @Input	    None

 @Output 	None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Initialise(IMG_VOID);

/*!
******************************************************************************

 @Function				VID_RA_Finalise

 @Description

 Finalizes the RA module.

 @Input	    None

 @Output 	None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Finalise(IMG_VOID);

/*!
******************************************************************************

 @Function				VID_RA_Create

 @Description

 Used to create a resource arena.

 @Input     pszName              : The name of the arena for diagnostic purposes.
    
 @Input     ui64Base             : The base of an initial resource span or 0.

 @Input     ui64Size             : The size of an initial resource span or 0.

 @Input     quantum              : The arena allocation quantum.

 @Input     (* pfnImportAlloc)   : A resource allocation callback or IMG_NULL.

 @Input     (* pfnImportFree)    : A resource de-allocation callback or IMG_NULL.

 @Input     hImport              : Handle passed to alloc and free or IMG_NULL.

 @Output    phArena              : The handle for the arene being created, or IMG_NULL.

 @Return    IMG_RESULT          : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Create (const IMG_CHAR * const pszName,
                      IMG_UINT64 ui64Base,
                      IMG_UINT64 ui64Size,		
                      size_t quantum,	
                      IMG_RESULT (* pfnImportAlloc)(IMG_HANDLE const hImport, 
                                                    IMG_UINT64 ui64RequestedSize, 
                                                    IMG_UINT64 * const pui64ActualSize, 
                                                    IMG_VOID ** const ppvRef, 
                                                    IMG_UINT32 ui32AllocationFlags, 
                                                    IMG_UINT64 * const pui64Base),
                      IMG_RESULT (* pfnImportFree)(IMG_HANDLE const hImport, 
                                                   IMG_UINT64 ui64ImportBase, 
                                                   IMG_VOID * const pvImportRef),
                      IMG_HANDLE hImport,
                      IMG_HANDLE * phArena);

/*!
******************************************************************************

 @Function				VID_RA_Delete

 @Description

 Used to delete a resource arena. All resources allocated from the arena must
 be freed before deleting the arena.

 @Input	    hArena      : The handle to the the arena to delete.

 @Output    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Delete(IMG_HANDLE const hArena);

/*!
******************************************************************************

 @Function				VID_RA_Add

 @Description

 Used to add a resource span to an arena. 
 The span must not overlapp with any span previously added to the arena.

 @Input	    ui64Base    : The ui64Base of the span.

 @Input	    ui64Size    : The size of the span.

 @Output    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Add(IMG_HANDLE const hArena, 
                  IMG_UINT64 ui64Base, 
                  IMG_UINT64 ui64Size);

/*!
******************************************************************************

 @Function				VID_RA_Alloc

 @Description

 Used to allocate resource from an arena.

 @Input	    hArena              : The handle to the the arena to create the resource.

 @Input	    request_size        : The requested size of resource segment.

 @Input	    pui64ActualSize     : The actualSize of resource segment.

 @Input	    ppvRef              : The user reference associated with allocated resource span.

 @Input	    ui32AllocationFlags : AllocationFlags influencing allocation policy.

 @Input	    ui64Alignment       : The alignment constraint required for the allocated segment.

 @Output    ui64Base            : The base of the allocated resource.

 @Return    IMG_RESULT          : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Alloc(IMG_HANDLE const hArena, 
                    IMG_UINT64 request_size,
                    IMG_UINT64 * const pui64ActualSize,
                    IMG_VOID ** const ppvRef, 
                    IMG_UINT32 ui32AllocationFlags,
                    IMG_UINT64 ui64Alignment,
                    IMG_UINT64 * const ui64Base);

/*!
******************************************************************************

 @Function				VID_RA_Free

 @Description

 Used to free a resource segment.

 @Input	    hArena      : The arena the segment was originally allocated from.

 @Input	    ui64Base    : The ui64Base of the span.

 @Output    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Free(IMG_HANDLE const hArena, 
                   IMG_UINT64 ui64Base);

#if defined (__cplusplus)
}
#endif

#endif
