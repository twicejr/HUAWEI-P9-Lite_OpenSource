/*!
 *****************************************************************************
 *
 * @File       addr_alloc1.h
 * @Title      Address allocation management API.
 * @Description    Address allocation APIs - used to manage address allocation
 *  with a number of predefined regions.
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

#if !defined (__ADDR_ALLOC_H__)
#define __ADDR_ALLOC_H__

#include <img_types.h>
#include <img_defs.h>
#include <ra.h>

#if defined (__cplusplus)
    extern "C" {
#endif

typedef struct ADDR_tag_sRegion		 ADDR_sRegion;		/*!< Memory region structure */

/*!
******************************************************************************
  This structure contains information about the memory region.
******************************************************************************/
struct ADDR_tag_sRegion
{
	IMG_CHAR *			pszName;			/*!< A pointer to a sring containing the name of the region.
											     IMG_NULL for the default memory region.				*/
	IMG_UINT64			ui64BaseAddr;		/*!< The base address of the memory region.					*/
	IMG_UINT64			ui64Size;			/*!< The size of the memory region.							*/
	IMG_UINT32			ui32GuardBand;		/*!< The size of any guard band to be used.  Guard bands
											     can be useful in separating block allocations and allows
												 the caller to detect erroneor accesses into these
												 areas.													*/

	ADDR_sRegion *		psNextRegion;		/*!< Used internally by the ADDR API...
												 A pointer used to point to the next memory region		*/
	IMG_HANDLE	        phArena;			/*!< Used internally by the ADDR API...
												 A to a structure used to maintain and perform
												 address allocation.									*/
};


/*!
******************************************************************************
  This structure contains the context for allocation.
******************************************************************************/
typedef struct
{
    ADDR_sRegion *	psRegions;				    /*!< Pointer the first region in the list.	*/
    ADDR_sRegion *	psDefaultRegion;			/*!< Pointer the default region.			*/
	IMG_UINT32		ui32NoRegions;				/*!< Number of regions currently available (including default) */
	IMG_BOOL		bUseRandomBlocks;			/*!< If set, memory will be allocated in any
													random block, not necessarily the one defined */
	IMG_BOOL		bUseRandomAllocation;		/*!< If set, memory will be allocated in any
													position of the block*/
} ADDR_sContext;

/*!
******************************************************************************

 @Function				ADDR_Initialise

 @Description

 This function is used to initialise the address alocation sub-system.

 NOTE: This function may be called multiple times.  The initialisation only
 happens the first time it is called.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_Initialise(IMG_VOID);

/*!
******************************************************************************

 @Function				ADDR_Deinitialise

 @Description

 This function is used to de-initialise the address alocation sub-system.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_Deinitialise(IMG_VOID);

/*!
******************************************************************************

 @Function				ADDR_DefineMemoryRegion

 @Description

 This function is used define a memory region.

 NOTE: The region structure MUST be defined in static memory as this
 is retained and used by the ADDR sub-system.

 NOTE: Invalid parameters are trapped by asserts.

 @Input	    psRegion	: A pointer to a region structure.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_DefineMemoryRegion(
    ADDR_sRegion * const psRegion
);

/*!
******************************************************************************

 @Function				ADDR_Malloc

 @Description

 This function is used allocate space within a memory region.

 NOTE: Allocation failures or invalid parameters are trapped by asserts.

 @Input	    pszName		: Is a pointer the name of the memory region.
						  IMG_NULL can be used to allocate space from the
						  default memory region.

 @Input	    ui64Size	: The size (in bytes) of the allocation.

 @Output	pui64Base : The address of the allocated space.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_Malloc(
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64 * const      pui64Base
);

/*!
******************************************************************************

 @Function				ADDR_Malloc1

 @Description

 This function is used allocate space within a memory region.

 NOTE: Allocation failures or invalid parameters are trapped by asserts.

 @Input	    pszName		: Is a pointer the name of the memory region.
						  IMG_NULL can be used to allocate space from the
						  default memory region.

 @Input	    ui64Size	: The size (in bytes) of the allocation.

 @Input		ui64Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Return	pui64Base : The address of the allocated space.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_Malloc1(
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64              ui64Alignment,
            IMG_UINT64 * const      pui64Base
);

/*!
******************************************************************************

 @Function				ADDR_Free

 @Description

 This function is used free a previously allocate space within a memory region.

 NOTE: Invalid parameters are trapped by asserts.

 @Input	pszName		: Is a pointer to the name of the memory region.
 						  IMG_NULL is used to free space from the
						  default memory region.

 @Input	ui64Addr	: The address allocated.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_Free(
	const   IMG_CHAR * const    pszName,
	        IMG_UINT64			ui64Addr
);

/*!
******************************************************************************

 @Function				ADDR_CxInitialise

 @Description

 This function is used to initialise the address alocation sub-system with
 an external context structure.

 NOTE: This function should be call only once for the context.

 @Input	    psContext   : Pointer to context structure.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxInitialise(
    ADDR_sContext * const psContext
);

/*!
******************************************************************************

 @Function				ADDR_CxDeinitialise

 @Description

 This function is used to de-initialise the address alocation sub-system with
 an external context structure.


 @Input	    psContext   : Pointer to context structure.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxDeinitialise(
    ADDR_sContext * const psContext
);

/*!
******************************************************************************

 @Function				ADDR_CxDefineMemoryRegion

 @Description

 This function is used define a memory region with an external context structure.

 NOTE: The region structure MUST be defined in static memory as this
 is retained and used by the ADDR sub-system.

 NOTE: Invalid parameters are trapped by asserts.

 @Input	    psContext   : Pointer to context structure.

 @Input	    psRegion	: A pointer to a region structure.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxDefineMemoryRegion(
    ADDR_sContext *  const psContext,
    ADDR_sRegion *   const psRegion
);

/*!
******************************************************************************

 @Function				ADDR_CxMalloc

 @Description

 This function is used allocate space within a memory region with
 an external context structure.

 NOTE: Allocation failures or invalid parameters are trapped by asserts.

 @Input	    psContext   : Pointer to context structure.

 @Input	    pszName		: Is a pointer the name of the memory region.
						  IMG_NULL can be used to allocate space from the
						  default memory region.

 @Input	    ui64Size	: The size (in bytes) of the allocation.

 @Output	pui64Base   : The address of the allocated space.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxMalloc(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64 * const      pui64Base
);

/*!
******************************************************************************

 @Function				ADDR_CxMalloc1

 @Description

 This function is used allocate space within a memory region with
 an external context structure.

 NOTE: Allocation failures or invalid parameters are trapped by asserts.

 @Input	    psContext   : Pointer to context structure.

 @Input	    pszName		: Is a pointer the name of the memory region.
						  IMG_NULL can be used to allocate space from the
						  default memory region.

 @Input	    ui64Size	: The size (in bytes) of the allocation.

 @Input		ui64Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Output	pui64Base   : The address of the allocated space.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxMalloc1(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64              ui64Alignment,
            IMG_UINT64 * const      pui64Base
);

/*!
******************************************************************************

 @Function				ADDR_CxMallocRes

 @Description

 This function is used allocate space within a memory region with
 an external context structure. 

 NOTE: Allocation failures are returned in IMG_RESULT, however invalid 
 parameters are trapped by asserts.

 @Input	    psContext   : Pointer to context structure.

 @Input	    pszName		: Is a pointer the name of the memory region.
						  IMG_NULL can be used to allocate space from the
						  default memory region.

 @Input	    ui64Size	: The size (in bytes) of the allocation.

 @Input		pui64Base   : Pointer to the address of the allocated space.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxMallocRes(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64 * const      pui64Base
);

/*!
******************************************************************************

 @Function				ADDR_CxMalloc1Res

 @Description

 This function is used allocate space within a memory region with
 an external context structure.

 NOTE: Allocation failures are returned in IMG_RESULT, however invalid 
 parameters are trapped by asserts.

 @Input	    psContext   : Pointer to context structure.

 @Input	    pszName		: Is a pointer the name of the memory region.
						  IMG_NULL can be used to allocate space from the
						  default memory region.

 @Input	    ui64Size	: The size (in bytes) of the allocation.

 @Input		ui64Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Input		pui64Base   : Pointer to the address of the allocated space.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxMalloc1Res(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64              ui64Alignment,
            IMG_UINT64 * const      pui64Base
);

/*!
******************************************************************************

 @Function				ADDR_CxFree

 @Description

 This function is used free a previously allocate space within a memory region
 with an external context structure.

 NOTE: Invalid parameters are trapped by asserts.

 @Input	    psContext   : Pointer to context structure.

 @Input	    pszName		: Is a pointer the name of the memory region.
 						  IMG_NULL is used to free space from the
						  default memory region.

 @Input	    ui64Addr	: The address allocated.

 @Return	IMG_RESULT  : IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT ADDR_CxFree(
            ADDR_sContext * const   psContext,
	const   IMG_CHAR * const        pszName,
	        IMG_UINT64			    ui64Addr
);

#if defined (__cplusplus)
}
#endif

#endif /* __ADDR_ALLOC_H__	*/
