/*!
 *****************************************************************************
 *
 * @File       topazmmu.h
 * @Title      Topaz Core mmu functions
 * @Description    Topaz Core mmu functions.
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

#include "talmmu_api.h"

// Function definitions

/*!
******************************************************************************

 @function              Topaz_Core_MMU_Configure

 @details			Configure the mmu



 @return   IMG_BOOL

******************************************************************************/
IMG_BOOL Topaz_Core_MMU_Configure(IMG_VOID);

/*!
******************************************************************************

 @function              Topaz_Core_MMU_HWSetup

 @details			

 @param    IMG_UINT32 ui32TCoreReg	:	Base address of the core


 @return   IMG_BOOL

******************************************************************************/
IMG_BOOL Topaz_Core_MMU_HWSetup(IMG_HANDLE ui32TCoreReg);

/*!
******************************************************************************

 @function              Topaz_Core_MMU_EnableTiling

 @details			 Enables tiling in the MMU for the specified core.

 @param    IMG_UINT32 ui32TCoreReg		: Topaz Core Register ID	

 @param    IMG_UINT32 ui32TileStride	: Tile stride


 @return   IMG_BOOL  : indicating success or failure

******************************************************************************/
IMG_BOOL Topaz_Core_MMU_EnableTiling(IMG_UINT32 ui32TCoreReg, IMG_UINT32 ui32TileStride);


/*!
******************************************************************************

 @function              Topaz_Core_MMU_FlushCache

 @details			Flush the MMU cache



 @return   IMG_BOOL

******************************************************************************/
IMG_BOOL Topaz_Core_MMU_FlushCache(IMG_VOID);
