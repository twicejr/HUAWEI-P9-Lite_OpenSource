/*!
 *****************************************************************************
 *
 * @File       idgen_api.h
 * @Title      The ID Generation API.
 * @Description    This file contains the header file information for the
 *  ID Generation API.
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

#if !defined (__IDGEN_API_H__)
#define __IDGEN_API_H__	//!< Defined to prevent file being included more than once

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#if defined(__cplusplus)
extern "C" {
#endif

#include <lst.h>



/*!
******************************************************************************

 @Function				IDGEN_CreateContext
 
 @Description 
 
 This function is used to create Id generation context.

 NOTE: Should only be called once to setup the context structure.

 NOTE: The client is responsible for providing thread/process safe locks on
 the context structure to maintain coherency.

 @Input		ui32MaxId	    : The maximum valid Id.

 @Input		ui32BlkSize	    : The number of handle per block. In case of incrementing
                              ids, size of the Hash table.

 @Input     bIncId          : Incrementing Ids
 
 @Output	phIdGenHandle	: A pointer used to return the context handle.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT IDGEN_CreateContext(
	IMG_UINT32					ui32MaxId,
	IMG_UINT32					ui32BlkSize,
    IMG_BOOL                    bIncId,
	IMG_HANDLE *				phIdGenHandle
);


/*!
******************************************************************************

 @Function				IDGEN_DestroyContext
 
 @Description 
 
 This function is used to destroy an Id generation context.  This function
 discards any handle blocks associated with the context.

 NOTE: The client is responsible for providing thread/process safe locks on
 the context structure to maintain coherency.
 
 @Input		hIdGenHandle	: The context handle.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT IDGEN_DestroyContext(
	IMG_HANDLE 					hIdGenHandle
);


/*!
******************************************************************************

 @Function				IDGEN_AllocId
 
 @Description 
 
 This function is used to associate a handle with an Id.

 NOTE: The client is responsible for providing thread/process safe locks on
 the context structure to maintain coherency.
 
 @Input		hIdGenHandle	: The context handle.

 @Input		hHandle		: The handle to be associated with the Id.

 @Output	pui32Id		: A pointer used to return the allocated Id.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT IDGEN_AllocId(
	IMG_HANDLE 					hIdGenHandle,
	IMG_HANDLE					hHandle,
	IMG_UINT32 *				pui32Id
);


/*!
******************************************************************************

 @Function				IDGEN_FreeId
 
 @Description 
 
 This function is used to free an Id.

 NOTE: The client is responsible for providing thread/process safe locks on
 the context structure to maintain coherency.
 
 @Input		hIdGenHandle	: The context handle.

 @Input		ui32Id		: The Id.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT IDGEN_FreeId(
	IMG_HANDLE 					hIdGenHandle,
	IMG_UINT32  				ui32Id
);


/*!
******************************************************************************

 @Function				IDGEN_GetHandle
 
 @Description 
 
 This function is used to get the handle associated with an Id.

 NOTE: The client is responsible for providing thread/process safe locks on
 the context structure to maintain coherency.
 
 @Input		hIdGenHandle	: The context handle.

 @Input		ui32Id		: The Id.

 @Output	phHandle	: A pointer used to return the handle associated
						  with the Id.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT IDGEN_GetHandle(
	IMG_HANDLE 					hIdGenHandle,
	IMG_UINT32  				ui32Id,
	IMG_HANDLE *				phHandle
);

#if defined(__cplusplus)
}
#endif
 
#endif /* __IDGEN_API_H__	*/


