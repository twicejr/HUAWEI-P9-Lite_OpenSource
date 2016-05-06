/*!
 *****************************************************************************
 *
 * @File       sysbrg_utils.h
 * @Description    This file contains the header file information for the
 *  System Bridge Kernel Mode Utilities API.
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

#if !defined (__SYSBRG_UTILS_H__)
#define __SYSBRG_UTILS_H__

#include <img_defs.h>
#include <sysbrg_api_km.h>
#include "sysmem_utils.h"
#include "lst.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern IMG_BOOL	gSysBrgInitialised;		/*!< Indicates where the API has been initialised	*/



/*!
******************************************************************************
 This structure contains the "mappable region" information.

 @brief		This structure contains information for "mappable regions" 
 known to the SYSBRGU API.
******************************************************************************/
typedef struct
{
  LST_LINK;								/*!< List link (allows the structure to be part of a MeOS list).*/
  IMG_HANDLE					hProcessId;		//!< Process id.
  IMG_PHYSADDR                    paCpuPhysAddr;  //!< The Cpu Physical address
  IMG_UINT32					ui32Size;		//!< The size of the region
  SYS_eMemAttrib				eMemAttrib;		//!< The memory attributes
  SYSMEMU_sPages *              pSysMem;        //!< Pointer to associated sysmem struct
} SYSBRGU_sMappableReg;

/*!
******************************************************************************

 @Function				SYSBRGU_Initialise
 
 @Description 
 
 This function is used to initialise the System Bridge Utilities and is 
 called at start-up.  
  
 @Input		None. 

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSBRGU_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSBRGU_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the System Bridge Utilities and would 
 normally be called at shutdown. 
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSBRGU_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSBRGU_RegisterProcessLostCb
 
 @Description 
 
 This function is used to register a "process lost" callback function - 
 called by the bridging code if/when the CURRENT process dies.

 @Input		pfnProcessLostCb :	A pointer to the "process lost" function.

 @Input		pvParam :		An IMG_VOID * value passed to the "process lost" function
							when if/when the process dies.

 @Output	phProcLostCbHandle :	A pointer used to return a handle to the callback
									this can be used with SYSBRGKM_RemoveProcessLostCb()
									to removed the callback.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSBRGU_RegisterProcessLostCb(
	SYSBRGKM_pfnProcessLostCb		pfnProcessLostCb,
    IMG_VOID *                  pvParam,
    IMG_HANDLE *				phProcLostCbHandle
);


/*!
******************************************************************************

 @Function				SYSBRGU_RemoveProcessLostCb
 
 @Description 
 
 This function is used to removed a "process lost" callback.

 @Input		phProcLostCbHandle :	The callback handle returned by 
									SYSBRGKM_RegisterProcessLostCb().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSBRGU_RemoveProcessLostCb(
    IMG_HANDLE				hProcLostCbHandle
);


/*!
******************************************************************************

 @Function				SYSBRGU_MakeProcessLostCb
 
 @Description 
 
 This function is used to make a "process lost" callback.

 @Input		hProcessId :		The process id of the process for which the
								"process lost" callback is to be made.

 @Return	None.

******************************************************************************/
IMG_VOID SYSBRGU_MakeProcessLostCb(
	IMG_HANDLE			hProcessId
);


/*!
******************************************************************************

 @Function				SYSBRGU_CreateMappableRegion
 
 @Description 
 
 This function is used to register a "mappable region" - a region of
 memory that can be mapped via the bridge API SYSBRG_CreateCpuUmAddrMapping()
 into user mode.

 NOTE: Mappable regions are associated with the current process.  The same
 region or overlappling regions can be defined for different processes and
 with different attributes.

 @Input		pvCpuKmAddr :	The CPU kernel mode address of the region.

 @Input     ui64CpuPhysAddr : The CPU Physical address of the region

 @Input		ui32Size :		Size of the allocation.

 @Input		eMemAttrib :	The memory attributes.

 @Output	phRegHandle :	A pointer used to return a hanlde to this 
							mappable region.

 @Return	IMG_RESULT:		This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSBRGU_CreateMappableRegion(
						 IMG_PHYSADDR         paCpuPhysAddr,
						 IMG_UINT32			ui32Size,
						 SYS_eMemAttrib		eMemAttrib,
                         SYSMEMU_sPages *   pSysMem,
						 IMG_HANDLE *		phRegHandle					
						 );


/*!
******************************************************************************

 @Function				SYSBRGU_DestroyMappableRegion
 
 @Description 
 
 This function is used to removed a "mappable region".

 @Input		hRegHandle :	The region handle returned by 
							SYSBRGU_CreateMappableRegion().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSBRGU_DestroyMappableRegion(
	IMG_HANDLE					hRegHandle					
);



/*!
******************************************************************************

 @Function				SYSBRGU_GetMappableRegion
 
 @Description 
 
 This function is used to obtain the information for a "mappable region".

 @Input		pvCpuKmAddr :	The CPU kernel mode address of the region.

 @Return	SYSBRGU_sMappableReg * : A pointer to the information for
							the "mappable region", IMG_NULL if the region
							was not found.

******************************************************************************/
extern SYSBRGU_sMappableReg * SYSBRGU_GetMappableRegion(
	IMG_PHYSADDR					paCpuPhysAddr
);


/*!
******************************************************************************

 @Function              SYSBRGU_RegisterAPI

 @Description 
 
 This function is used to register a API with the SYSBRG component.

 @Input		psKernelAPIInfo :	A pointer to a kernel api object

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
IMG_RESULT SYSBRGU_RegisterAPI (
	SYSBRGKM_sAPIInfo *			psKernelAPIInfo	
);

IMG_RESULT SYSBRGU_RemoveAPI (
	SYSBRGKM_sAPIInfo *			psKernelAPIInfo
);


/*!
******************************************************************************

 @Function              SYSBRGU_GetAPI

 @Description			

 This function searches the registered APIs for one with API ID set to ui32APIId
 and it sets ppslAPIInfo to point to the SYSBRGKM_sAPIInfo for the API if found.
 Returns IMG_TRUE when API has been found, IMG_FALSE otherwise.

 @Input		ui32APIId :		ID of the API.

 @Input		ppslAPIInfo :	Set to point to the SYSBRGKM_sAPIInfo structure for the
							API searched by the function.

 @Return	IMG_BOOL :		IMG_TRUE when API has been found, IMG_FALSE otherwise.

******************************************************************************/
IMG_BOOL	SYSBRGU_GetAPI (
	IMG_UINT32					ui32APIId,   
	SYSBRGKM_sAPIInfo **		ppslAPIInfo
);

/*!
******************************************************************************

 @Function              SYSBRGU_ClearAllMappableRegions

 @Description			

 This function clears all the mappable regions previously allocated

 @Return	None

******************************************************************************/
IMG_VOID SYSBRGU_ClearAllMappableRegions (
	IMG_VOID
);

#if defined(__cplusplus)
}
#endif
 
#endif /* __SYSBRG_UTILS_H__	*/


