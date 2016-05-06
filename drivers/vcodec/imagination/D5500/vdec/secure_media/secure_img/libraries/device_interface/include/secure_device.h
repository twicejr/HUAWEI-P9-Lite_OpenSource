/*!
 *****************************************************************************
 *
 * @File       secure_device.h
 * @Description    This file declares the memory-mapped device interface.
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

#ifndef __SECDEV_H__
#define __SECDEV_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_include.h"
#include "img_defs.h"


/*!
******************************************************************************

 @Function              SECDEV_pfnDevKmLisr

 @Description

 This is the prototype for device Kernel Mode LISR callback functions.  This
 function is called when the device interrupt is suspected.

 NOTE: The Kernel Mode LISR should return IMG_FALSE if the device did not
 cause the interrupt. This allows for several devices to share an interrupt
 line.  The Kernel Mode LISR returns IMG_TRUE if the interrupt has been handled.

 NOTE: By convention, further device interrupts are disabled whilst the Kernel
 Mode LISR is active.  Device interrupts must be re-enabled by a synchronous,
 or asynchronous call to SYSDEVKN_EnableDeviceInt().

 @Input		pvParam :		Pointer parameter, defined when the
						    callback was registered.

							NOTE: This pointer must be valid in interrupt
							context.

 @Return	IMG_BOOL :		IMG_TRUE if the interrupt has been handles by the
							Kernel Mode LISR, otherwise IMG_FALSE.

******************************************************************************/
typedef IMG_BOOL ( * SECDEV_pfnDevKmLisr) (
    IMG_VOID *                  pvParam
);

/*!
******************************************************************************
 This enum describes the device region to map.
******************************************************************************/
typedef enum 
{
	SECDEV_MAPAREA_REGISTER = 0,
	SECDEV_MAPAREA_MEMORY = 1,
	SECDEV_MAPAREA_REG_MEM = 2,
	SECDEV_MAPAREA_MAX = 3
} SECDEV_eMapArea;

/*!
******************************************************************************
 This structure contains device information.

 #SYSDEVKM_sDevInfo MUST be the first element in this structure.
******************************************************************************/
typedef struct
{
	IMG_CHAR *					pszDeviceName;		//!< The device name
	IMG_BOOL				    bDevLocated;		//!< IMG_TRUE when the device has been located
	SECDEV_pfnDevKmLisr			pfnDevKmLisr;		//!< Pointer to any registered Kernel Mode LISR callback
	IMG_VOID *                  pvParam;			//!< Pointer to be passed to the Kernel Mode LISR callback
	IMG_VOID *				    pvLocParam;			//!< Pointer used to retains "located" information
	IMG_PHYSADDR 		        paPhysRegBase;	    //!< A pointer to the device registers physical address (or mappable to user mode) - IMG_NULL if not defined
	IMG_VOID *  		        pvKmRegBase;		//!< A pointer to the device register base in kernel mode - IMG_NULL if not defined
	IMG_UINT32 				    ui32RegSize;		//!< The size of the register block (0 if not known)
} SECURE_sDev;

/*!
******************************************************************************

 @Function				SECDEV_Initialise

******************************************************************************/
extern IMG_RESULT 
SECDEV_Initialise(
     IMG_VOID
);
/*!
******************************************************************************

 @Function				SECDEV_DeInitialise

******************************************************************************/
extern IMG_VOID 
SECDEV_DeInitialise(
    SECDEV_eMapArea    eArea
);

/*!
******************************************************************************

 @Function				SECDEV_LocateDevice

 @Description

******************************************************************************/
extern IMG_RESULT 
SECDEV_LocateDevice(
	SECURE_sDev *			psInfo,
	SECDEV_eMapArea        eArea
);

/*!
******************************************************************************

 @Function				SECDEV_GetMemoryInfo

******************************************************************************/
IMG_VOID SECDEV_GetMemoryInfo(
	IMG_VOID **         ppui32KmMemory,
	IMG_UINT64 *        pui64MemSize
);
/*!
******************************************************************************

 @Function				SECDEV_CpuVirtAddrToCpuPAddr

******************************************************************************/
IMG_PHYSADDR SECDEV_CpuVirtAddrToCpuPAddr(
	IMG_VOID *pvCpuKmAddr
);


#if defined(__cplusplus)
}
#endif

#endif /* __SECDEV_H__ */
