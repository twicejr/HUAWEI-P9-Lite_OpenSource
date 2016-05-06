/*!
 *****************************************************************************
 *
 * @File       topaz_device_km.c
 * @Title      TOPAZ Device Kernel Mode component
 * @Description    This file contains the TOPAZ Device Kernel Mode component.
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

#include <tal.h>
#include <target.h>
#include <topaz_device_km.h>
#include <topaz_device.h>
#include <sysos_api_km.h>
#include <sysbrg_utils.h>
#if defined(HW_4_0)
#include "e4500_public_regdefs.h"
#endif
#if defined(HW_3_X)
#include "vxe_public_regdefs.h"
#endif

#include <reg_io2.h>
#include <rman_api.h>
#include <sysdev_utils.h>

#define __SYS_DEVICES__
#include <system.h>

#define MAX_TOPAZ_CORES 4

extern IMG_ERRORCODE comm_DispatchIncomingMsgs(IMG_COMM_SOCKET **sockets);
extern IMG_VOID topazkm_pfnDevPowerPreS5(IMG_HANDLE hDevHandle, IMG_VOID *pvDevInstanceData);
extern IMG_VOID topazkm_pfnDevPowerPostS0(IMG_HANDLE hDevHandle, IMG_VOID *pvDevInstanceData);

#if defined (IMG_KERNEL_MODULE)
#define PRINT printk
#define SPRINT sprintf
#else
#define PRINT printf
#define SPRINT sprintf
#endif

/*!
******************************************************************************

 @Function              topazdd_IntEnable

******************************************************************************/
static IMG_VOID	topazdd_IntEnable(
	TOPAZKM_DevContext *	psContext,
	IMG_UINT32			ui32IntMask
)
{
	IMG_UINT32		crImgTopazIntenab;

	SYSOSKM_DisableInt();

	/* config interrupts on Topaz core */
	TALREG_ReadWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, &crImgTopazIntenab );

	/* set enable interrupt bits */
	crImgTopazIntenab |= ui32IntMask;
	TALREG_WriteWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, crImgTopazIntenab );

	SYSOSKM_EnableInt();
}

/*!
******************************************************************************

 @Function              topazdd_IntDisable

******************************************************************************/
static IMG_VOID	topazdd_IntDisable(
	TOPAZKM_DevContext *	psContext,
	IMG_UINT32			ui32IntMask
)
{
	IMG_UINT32		crImgTopazIntenab;

	SYSOSKM_DisableInt();

	/* config interrupts on Topaz core */
	TALREG_ReadWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, &crImgTopazIntenab );

	/* clear enable interrupt bits */
	crImgTopazIntenab &= ~ui32IntMask;
	TALREG_WriteWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, crImgTopazIntenab );

	SYSOSKM_EnableInt();
}


/*!
******************************************************************************

 @Function              topazdd_IntClear

******************************************************************************/
static IMG_VOID	topazdd_IntClear(
	TOPAZKM_DevContext *		psContext,
	IMG_UINT32				intClearMask
)
{
	SYSOSKM_DisableInt();
	TALREG_WriteWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_INT_CLEAR, intClearMask);
	SYSOSKM_EnableInt();
}

/*!
******************************************************************************

 @Function				TOPAZDD_Initialise

******************************************************************************/
IMG_RESULT topazdd_Initialise(
	TOPAZKM_DevContext *psContext
)
{
	if (!psContext->bInitialised)
	{
		psContext->ui32MultiCoreMemSpaceId = TAL_GetMemSpaceHandle("REG_TOPAZHP_MULTICORE");
		IMG_ASSERT(psContext->ui32MultiCoreMemSpaceId != IMG_NULL);
		if(psContext->ui32MultiCoreMemSpaceId == IMG_NULL)
		{
			return IMG_ERROR_DEVICE_NOT_FOUND;
		}
		// Interrupts are only enabled in bridging build.
#if !defined(POLL_FOR_INTERRUPT) //!defined (SYSBRG_NO_BRIDGING)
		/* Now enabled interrupts */
		topazdd_IntEnable(psContext, MASK_TOPAZHP_TOP_CR_HOST_INTEN_MTX | MASK_TOPAZHP_TOP_CR_HOST_TOPAZHP_MAS_INTEN | MASK_TOPAZHP_TOP_CR_HOST_INTEN_MMU_FAULT
#if defined (HW_3_X)
			| MASK_TOPAZHP_TOP_CR_HOST_INTEN_MMU_FAULT_B
#endif
			);
#endif
		/* Device now initailised...*/
		psContext->bInitialised = IMG_TRUE;
	}

	/* Return success...*/
	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function				TOPAZDD_Deinitialise

******************************************************************************/
IMG_VOID topazdd_Deinitialise(
	TOPAZKM_DevContext *psContext
)
{
#if !defined(POLL_FOR_INTERRUPT)
	topazdd_IntDisable(psContext, ~0);
#endif
}

/*!
******************************************************************************

 @Function              topazkm_fnDevKmHisr

******************************************************************************/
static IMG_VOID topazkm_fnDevKmHisr (
	IMG_HANDLE				hDevHandle,
    IMG_VOID *				pvDevInstanceData
)
{
}

/*!
******************************************************************************

 @Function              topazkm_fnDevKmLisr

******************************************************************************/
static IMG_BOOL topazkm_fnDevKmLisr (
	IMG_HANDLE				hDevHandle,
    IMG_VOID *				pvDevInstanceData
)
{
	IMG_UINT32 crMultiCoreIntStat;
	IMG_UINT32 ui32MaskMMUFault = MASK_TOPAZHP_TOP_CR_INT_STAT_MMU_FAULT;

	TOPAZKM_DevContext *psContext = (TOPAZKM_DevContext *)pvDevInstanceData;

#if defined (HW_3_X)
	/* More requesters with topaz hp */
	ui32MaskMMUFault |= MASK_TOPAZHP_TOP_CR_INTCLR_MMU_FAULT_B;
#endif

	/* If interrupts not defined then...*/
	if (!psContext->bInitialised)
	{
		/* Signal not this device...*/
		return IMG_FALSE;
	}

#if !defined(POLL_FOR_INTERRUPT)
	/* read device interrupt status */
	TALREG_ReadWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_INT_STAT, &crMultiCoreIntStat );
	
	/* if interrupts enabled and fired...*/
	if (((crMultiCoreIntStat & MASK_TOPAZHP_TOP_CR_INT_STAT_MTX)
		== (MASK_TOPAZHP_TOP_CR_INT_STAT_MTX )))
	{
		/* Clear interrupt source...*/
		topazdd_IntClear( psContext, MASK_TOPAZHP_TOP_CR_INTCLR_MTX );

		/* Now dispatch the messages */
		comm_DispatchIncomingMsgs(psContext->deviceSockets);

		/* Signal this interrupt has been handled...*/
		return IMG_TRUE;
	}

	/* if page fault ever happenned */
	if (crMultiCoreIntStat & (ui32MaskMMUFault))
	{
		static IMG_BOOL dump_once = IMG_TRUE;

		if (dump_once)
		{
			/*keep minimum from kernel hoping we will have enough time to dump all registers (print out MMU status)*/
			PRINT("Page fault [%08x]\n", crMultiCoreIntStat);

			dump_once = IMG_FALSE; // only on first page fault for readability
		}

		/* Clear interrupt source...*/
		topazdd_IntClear(psContext, ui32MaskMMUFault);

		/* IT served, we might never reach that point on kernel crashes */
		return IMG_TRUE;
	}
#endif

	/* Signal not this device...*/
	return IMG_FALSE;
}

/*!
******************************************************************************

 @Function              topazkm_fnDevInit

 See definition of #DMANKM_pfnDevInit.

******************************************************************************/
static IMG_RESULT topazkm_fnDevInit (
	IMG_HANDLE					hDevHandle,
	IMG_HANDLE					hInitConnHandle,
    IMG_VOID **					ppvDevInstanceData
)
{
	IMG_RESULT result;
	IMG_UINT32 ui32Result;
	TOPAZKM_DevContext *psContext;
	
	/* Allocate device structure...*/
	psContext = IMG_MALLOC(sizeof(*psContext));
	IMG_ASSERT(psContext != IMG_NULL);
	if (psContext == IMG_NULL)
	{
		return IMG_ERROR_OUT_OF_MEMORY;
	}
	IMG_MEMSET(psContext, 0, sizeof(*psContext));

	result = RMAN_CreateBucket(&psContext->hResBHandle);

	*ppvDevInstanceData = psContext;

	/* Get the device name...*/
	psContext->pszDeviceName = DMANKM_GetDeviceName(hDevHandle);

	/* Open the device...*/
	ui32Result = SYSDEVU_OpenDevice(psContext->pszDeviceName, &psContext->hSysDevHandle);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if 	(ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if 	(ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	psContext->bInitialised = IMG_FALSE; // No user application explicitly initialised the driver.

	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if 	(ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	/* Return success...*/
	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              topazkm_fnDevDeinit

 See definition of #DMANKM_pfnDevDeinit.

******************************************************************************/
static IMG_VOID topazkm_fnDevDeinit (
	IMG_HANDLE					hDevHandle,
	IMG_HANDLE					hInitConnHandle,
    IMG_VOID *					pvDevInstanceData
)
{
	TOPAZKM_DevContext *			psContext = (TOPAZKM_DevContext *)pvDevInstanceData;

	/* If the interrupt was defined then it is also safe to clear interrupts
	   and reset the core....*/
	if (psContext->bInitialised)
	{
		/* Disable interrupts...*/
		SYSOSKM_DisableInt();
		topazdd_Deinitialise(psContext);
		SYSOSKM_EnableInt();

		{
			IMG_UINT32		crImgTopazIntenab;

			/* disable interrupts on Topaz core */
			TALREG_ReadWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, &crImgTopazIntenab );

			crImgTopazIntenab &= ~MASK_TOPAZHP_TOP_CR_HOST_INTEN_MTX;
			TALREG_WriteWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, crImgTopazIntenab );

			/* clear interrupt - just in case */
			TALREG_WriteWord32 (psContext->ui32MultiCoreMemSpaceId, TOPAZHP_TOP_CR_MULTICORE_INT_CLEAR, MASK_TOPAZHP_TOP_CR_INTCLR_MTX );
		}

	}

	RMAN_DestroyBucket(psContext->hResBHandle);

	/* If we opened a device...*/
	if (psContext->hSysDevHandle != IMG_NULL)
	{
		SYSDEVU_CloseDevice(psContext->hSysDevHandle);
	}

	IMG_FREE(pvDevInstanceData);
}

/*!
******************************************************************************

 @Function              topazkm_fnDevConnect

 See definition of #DMANKM_fnDevConnect.

******************************************************************************/
static IMG_RESULT topazkm_fnDevConnect (
	IMG_HANDLE					hConnHandle,
    IMG_VOID *					pvDevInstanceData,
    IMG_VOID **					ppvDevConnectionData
)
{
	IMG_RESULT result;
	TOPAZKM_ConnData *connData = IMG_MALLOC(sizeof(TOPAZKM_ConnData));

	/* Create a bucket for the resources...*/
	result = RMAN_CreateBucket(&connData->hResBHandle);
	*ppvDevConnectionData = connData;
	/* Return success...*/
	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              topazkm_fnDevDisconnect

 See definition of #DMANKM_pfnDevDisconnect.

******************************************************************************/
static IMG_RESULT topazkm_fnDevDisconnect (
	IMG_HANDLE					hConnHandle,
    IMG_VOID *					pvDevInstanceData,
    IMG_VOID *					pvDevConnectionData,
	DMANKM_eDisconnType			eDisconnType
)
{
	IMG_UINT32				ui32Result;
	TOPAZKM_ConnData		*connData = pvDevConnectionData;

	/* Mark this socket as available */
	RMAN_DestroyBucket(connData->hResBHandle);

	IMG_FREE(pvDevConnectionData);

	ui32Result = DMANKM_DevDisconnectComplete(hConnHandle);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);

	/* Return success...*/
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              TOPAZKM_fnDevRegister

 See definition of #DMANKM_pfnDevRegister.

******************************************************************************/
IMG_RESULT TOPAZKM_fnDevRegister (
    DMANKM_sDevRegister *		psDevRegister
)
{
	psDevRegister->ui32ConnFlags = DMAN_CFLAG_SHARED;

	psDevRegister->pfnDevInit			= topazkm_fnDevInit;
	psDevRegister->pfnDevDeinit			= topazkm_fnDevDeinit;

	psDevRegister->pfnDevConnect		= topazkm_fnDevConnect;
	psDevRegister->pfnDevDisconnect		= topazkm_fnDevDisconnect;

	psDevRegister->pfnDevKmHisr			= topazkm_fnDevKmHisr;
	psDevRegister->pfnDevKmLisr			= topazkm_fnDevKmLisr;

	psDevRegister->pfnDevPowerPostS0	= topazkm_pfnDevPowerPostS0;
	psDevRegister->pfnDevPowerPreS5		= topazkm_pfnDevPowerPreS5;

	/* Return success...*/
	return IMG_SUCCESS;
}


#if !defined(SYSBRG_NO_BRIDGING)

#include <linux/module.h>
#include <linux/version.h>

#ifdef TAL_TARGET_HEADER_NAME
#include TAL_TARGET_HEADER_NAME
#else
#error TAL_TARGET_HEADER_NAME has to be defined in order to use TAL light
#endif

#include <api_common.h>
#include "memmgr_api_rpc.h"
#include "hostutils_api_rpc.h"

static SYSBRGKM_sAPIInfo asAPIInfo[] = {
	SYS_BRIDGE(HOSTUTILS)
	SYS_BRIDGE(MEMMGR)
};
#else
#define __init
#define __exit
#endif

SYSDEVU_sInfo topaz_device = { 0, SYS_DEVICE("TOPAZ", TOPAZ, IMG_FALSE)};

int __init init_topaz(void) {
	// register topaz to SYSDEV.
	SYSDEVU_RegisterDriver(&topaz_device);
	SYSDEVU_RegisterDevice(&topaz_device);

#if !defined(SYSBRG_NO_BRIDGING)
	{
		int i;

		gsTargetConfig.pasDevices[0].pvKmRegBase = topaz_device.pui32KmRegBase;
		gsTargetConfig.pasDevices[0].ui32RegSize = topaz_device.ui32RegSize;

		TARGET_Initialise(&gsTargetConfig);

		// register SYSBRG APIs.
		for (i = 0; i<(sizeof(asAPIInfo)/sizeof(SYSBRGKM_sAPIInfo)); i++)
			SYSBRGU_RegisterAPI(&asAPIInfo[i]);
	}
#else
	{
		IMG_RESULT result;
		result = TALSETUP_Initialise();
		IMG_ASSERT(result == IMG_SUCCESS);
	}
#endif

	return 0;
}

void __exit exit_topaz(void) {

	SYSDEVU_UnRegisterDriver(&topaz_device);
	SYSDEVU_UnRegisterDevice(&topaz_device);

#if !defined(SYSBRG_NO_BRIDGING)
	// ASSUMPTION : Only one device here.
	TAL_DeviceUnRegister("TOPAZ");

	{
		int i;

		// register SYSBRG APIs.
		for (i = 0; i<(sizeof(asAPIInfo)/sizeof(SYSBRGKM_sAPIInfo)); i++)
			SYSBRGU_RemoveAPI(&asAPIInfo[i]);
	}
#endif
}


#if !defined(SYSBRG_NO_BRIDGING)
module_init(init_topaz);
module_exit(exit_topaz);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(IMGSYSBRG_MODULE_NAME" - Imagination Technologies System Bridge Module");
MODULE_AUTHOR("Imagination Technologies Ltd");
#endif
