/*!
 *****************************************************************************
 *
 * @File       dman_api_km.c
 * @Description    This file contains the Device Manager API.
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

#include "dman_api.h"
#include "dman_api_km.h"
#include "sysos_api_km.h"
#include "sysbrg_api_km.h"
#include "sysdev_utils.h"
#include "rman_api.h"
#include "system.h"
#include "pman_api.h"
#include "report_api.h"

#ifdef IMG_KERNEL_MODULE
#include <linux/module.h>
#endif

//! Connection type Id.
#define DMAN_CONN_TYPE_ID	(0x80800001)
//! Connection type Id.
#define DMAN_ATTACH_TYPE_ID	(0x80800002)

/*!
******************************************************************************
 This structure contains the device context.
 ******************************************************************************/
typedef struct {
	LST_LINK; /*!< List link (allows the structure to be part of a MeOS list).*/
	IMG_UINT32 ui32DeviceId;			//!< DMAN allocated device ID.
	IMG_HANDLE hMutexHandle;			//!< For thread-safety
	IMG_CHAR * pszDeviceName;			//!< Device name
	DMANKM_pfnDevRegister pfnDevRegister;     //!< Device registration function
	SYSDEVU_sInfo *hSysDevHandle;			//!< SYSDEVKM device handle
	IMG_HANDLE hHISRHandle;			//!< HISR handle
	IMG_HANDLE hResBHandle;	//!< Resource bucket for connections and attachments
	IMG_UINT32 ui32ConnCnt;			//!< Count of connections
	DMANKM_sDevRegister sDevRegister;       //!< Device registration information
	IMG_VOID * pvDevInstanceData;		//!< Pointer to device instance data
	IMG_VOID * pvDevGlobalData;		//!< Pointer to device global data
	LST_T sConnList;//!< List of DMANKM_sConnContext structures associated with this device
	IMG_UINT8 ui8ApmPpmFlags;         //!< APM PPM states

} DMANKM_sDevContext;

/*!
 ******************************************************************************
 This structure contains the connection context.
 ******************************************************************************/
typedef struct {
	LST_LINK; /*!< List link (allows the structure to be part of a MeOS list).*/
	IMG_HANDLE hProcessId;				//!< Process id.
	IMG_UINT32 ui32ConnId;				//!< Connection id.
	IMG_HANDLE hResHandle;				//!< Resource handle.
	IMG_UINT32 ui32OpenCnt;			//!< Open count
	IMG_HANDLE hProcLostCbHandle;		//!< Process lost callback handle
	IMG_BOOL bInitConn;            //!< IMG_TRUE for the initialise connection
	DMANKM_sDevContext * psDevContext;			//!< Pointer to device context
	IMG_VOID * pvDevConnectionData;	//!< Pointer to device connection data
	LST_T sAttachList; //!< List of DMANKM_sAttachContext structures associated with this connection

} DMANKM_sConnContext;

/*!
 ******************************************************************************
 This structure contains the attachment context.
 ******************************************************************************/
typedef struct {
	LST_LINK; /*!< List link (allows the structure to be part of a MeOS list).*/
	IMG_CHAR * pszCompName;		//!< Resource allocator name
	IMG_UINT32 ui32AttachId;			//!< Attachment id.
	IMG_HANDLE hResHandle;				//!< Resource handle.
	DMANKM_pfnCompAttach pfnCompAttach; //!< Pointer to component attach function - used for cross check
	DMANKM_sConnContext * psConnContext;//!< Pointer to connection context
	DMANKM_sCompAttach sCompAttach;		//!< Component attach information
	IMG_VOID * pvCompAttachmentData; //!< Pointer to resource allocator specific data
	IMG_HANDLE hResBHandle;            //!< Attachment resource bucket

} DMANKM_sAttachContext;

/*!
 ******************************************************************************
 This type defines the individual flags within the ui8ApmPpmFlags flags word in device context.
 ******************************************************************************/
typedef enum {
	DMAN_DPPM = 0x01,    //!< PPM on/off
	DMAN_DAPM = 0x02,    //!< APM on/off
	DMAN_DPPM_TURNED_ON = 0x04,    //!< PPM turned back on

} DMANKM_ePwrMngFlags;

static IMG_BOOL gDmanKmInitialised = IMG_FALSE;	//!< Indicates where the API has been initialised in kernel mode

static IMG_BOOL gbDevListInitialised = IMG_FALSE;//!< Indicates whether the device list has been initialised
static LST_T gsDevList;				//!< List of DMANKM_sDevContext structures

static IMG_UINT32 gui32NextDeviceID = 0x88000001;//!< DMAN allocated device ID

static IMG_UINT32 gui32KmBuildFlags = SYS_BUILD_FLAGS;

/*!
 ******************************************************************************

 @Function              dmankm_fnProcessLostCb

 ******************************************************************************/
static IMG_VOID dmankm_fnProcessLostCb(IMG_VOID * pvParam) 
{
	DMANKM_sConnContext * psConnContext = pvParam;
	IMG_HANDLE hDevHandle;
	IMG_UINT32 ui32Result = IMG_SUCCESS;

	/* Get the device handle...*/
	hDevHandle = DMANKM_GetDevHandleFromConn(psConnContext);

	/* Lock the device...*/
	DMANKM_LockDeviceContext(hDevHandle);

	/* Call on to the kernel function...*/
	ui32Result = DMANKM_CloseDevice(hDevHandle, psConnContext,
			DMAN_DCONN_ABORT);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);

// NOTE: We do not unlock the device as this will be done by
//	     DMANKM_DevDisconnectComplete().
//	/* Unlock the device...*/
//	DMANKM_UnlockDeviceContext(hDevHandle);
}

/*!
 ******************************************************************************

 @Function              dmankm_DisconnectComps

 ******************************************************************************/
static IMG_RESULT dmankm_DisconnectComps(DMANKM_sConnContext * psConnContext) 
{
	DMANKM_sAttachContext * psAttachContext;
	IMG_UINT32 ui32Result;

	psAttachContext = (DMANKM_sAttachContext *) LST_first(
			&psConnContext->sAttachList);
	while (psAttachContext != IMG_NULL ) {
		/* If there is a disconnect function...*/
		if (psAttachContext->sCompAttach.pfnCompDisconnect != IMG_NULL ) {
			/* Call it...*/
			ui32Result = psAttachContext->sCompAttach.pfnCompDisconnect(
					psAttachContext, psAttachContext->pvCompAttachmentData);
			if (ui32Result != IMG_SUCCESS) {
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
				return ui32Result;
			}
		}

		/* Remove, free the name and control block...*/
		LST_remove(&psConnContext->sAttachList, psAttachContext);
		RMAN_DestroyBucket(psAttachContext->hResBHandle);
		RMAN_FreeResource(psAttachContext->hResHandle);
		IMG_FREE(psAttachContext->pszCompName);
		IMG_FREE(psAttachContext);
		psAttachContext = (DMANKM_sAttachContext *) LST_first(
				&psConnContext->sAttachList);
	}

	/* Return success...*/
	return IMG_SUCCESS;
}

/*!
 ******************************************************************************

 @Function              DMANKM_LocateDevice

 ******************************************************************************/
IMG_RESULT DMANKM_LocateDevice(IMG_CHAR * pszDeviceName,
		IMG_HANDLE * phDevHandle) 
{
	DMANKM_sDevContext * psDevContext;

	/* Search list of registered devices for this device...*/
	IMG_ASSERT(gbDevListInitialised);
	psDevContext = (DMANKM_sDevContext *) LST_first(&gsDevList);
	while ((psDevContext != IMG_NULL )&&
	IMG_STRCMP(psDevContext->pszDeviceName, pszDeviceName)
	) {
		psDevContext = (DMANKM_sDevContext *) LST_next(psDevContext);
	}

	*phDevHandle = psDevContext;

	/* If not found...*/
	if (psDevContext == IMG_NULL ) 
    {
		return IMG_ERROR_DEVICE_NOT_FOUND;
	}

	return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(DMANKM_LocateDevice)

/*!
 ******************************************************************************

 @Function				DMANKM_LockDeviceContext

 ******************************************************************************/
IMG_VOID DMANKM_LockDeviceContext(
		IMG_HANDLE hDevHandle) 
{
	/* Take mutex */
	SYSOSKM_LockMutex(((DMANKM_sDevContext *) hDevHandle)->hMutexHandle);
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_LockDeviceContext)

/*!
 ******************************************************************************

 @Function				DMANKM_UnlockDeviceContext

 ******************************************************************************/
IMG_VOID DMANKM_UnlockDeviceContext(
		IMG_HANDLE hDevHandle) {
	/* Release mutex */
	SYSOSKM_UnlockMutex(((DMANKM_sDevContext *) hDevHandle)->hMutexHandle);
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_UnlockDeviceContext)

/*!
 ******************************************************************************

 @Function				DMANKM_GetDevHandleFromConn

 ******************************************************************************/
IMG_HANDLE DMANKM_GetDevHandleFromConn(IMG_HANDLE hConnHandle) 
{
    if(hConnHandle == IMG_NULL)
    {
        IMG_ASSERT(hConnHandle != IMG_NULL);
        return IMG_NULL;
    }

	/* Return the device handle...*/
	return (IMG_HANDLE) (((DMANKM_sConnContext *) hConnHandle)->psDevContext);
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_GetDevHandleFromConn)

/*!
 ******************************************************************************

 @Function				DMANKM_GetConnHandleFromAttach

 ******************************************************************************/
IMG_HANDLE DMANKM_GetConnHandleFromAttach(IMG_HANDLE hAttachHandle) 
{
	return (IMG_HANDLE) ((DMANKM_sAttachContext *) hAttachHandle)->psConnContext;
}

/*!
 ******************************************************************************

 @Function				DMANKM_GetDevHandleFromAttach

 ******************************************************************************/
IMG_HANDLE DMANKM_GetDevHandleFromAttach(IMG_HANDLE hAttachHandle) 
{
	return (IMG_HANDLE) ((DMANKM_sAttachContext *) hAttachHandle)->psConnContext->psDevContext;
}

/*!
 ******************************************************************************

 @Function              DMANKM_GetDeviceName

 ******************************************************************************/
IMG_CHAR * DMANKM_GetDeviceName(IMG_HANDLE hDevHandle) 
{
	return ((DMANKM_sDevContext *) hDevHandle)->pszDeviceName;
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_GetDeviceName)

/*!
 ******************************************************************************

 @Function				DMANKM_SetDevGlobalData

 ******************************************************************************/
IMG_VOID DMANKM_SetDevGlobalData(
		IMG_HANDLE hDevHandle, IMG_VOID * pvDevGlobalData) 
{
	((DMANKM_sDevContext *) hDevHandle)->pvDevGlobalData = pvDevGlobalData;
}

/*!
 ******************************************************************************

 @Function				DMANKM_GetDevGlobalData

 ******************************************************************************/
IMG_VOID * DMANKM_GetDevGlobalData(
		IMG_HANDLE hDevHandle) 
{
	return ((DMANKM_sDevContext *) hDevHandle)->pvDevGlobalData;
}

/*!
 ******************************************************************************

 @Function				DMANKM_GetDevInstanceData

 ******************************************************************************/
 IMG_VOID * DMANKM_GetDevInstanceData(
		IMG_HANDLE hDevHandle) 
{
	return ((DMANKM_sDevContext *) hDevHandle)->pvDevInstanceData;
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_GetDevInstanceData)

/*!
 ******************************************************************************

 @Function				DMANKM_GetDevConnectionData

 ******************************************************************************/
IMG_VOID * DMANKM_GetDevConnectionData(
		IMG_HANDLE hConnHandle) 
{
	/* Get device data - connection data is not associated with the initial connection...*/
	IMG_ASSERT(!((DMANKM_sConnContext *)hConnHandle)->bInitConn);
	return ((DMANKM_sConnContext *) hConnHandle)->pvDevConnectionData;
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_GetDevConnectionData)

/*!
 ******************************************************************************

 @Function				DMANKM_GetCompAttachmentData

 ******************************************************************************/
IMG_VOID * DMANKM_GetCompAttachmentData(
		IMG_HANDLE hAttachHandle) 
{
	return ((DMANKM_sAttachContext *) hAttachHandle)->pvCompAttachmentData;
}

/*!
 ******************************************************************************

 @Function              dmankm_fnDevKmHisr

 ******************************************************************************/
static IMG_VOID dmankm_fnDevKmHisr(IMG_VOID * pvParam) 
{
	DMANKM_sDevContext * psDevContext = (DMANKM_sDevContext *) pvParam;

    if(psDevContext == IMG_NULL)
    {
        IMG_ASSERT(psDevContext != IMG_NULL);
    }
    else if(psDevContext->sDevRegister.pfnDevKmHisr == IMG_NULL)
    {
        IMG_ASSERT(psDevContext->sDevRegister.pfnDevKmHisr != IMG_NULL);
    }
    else
    {
		psDevContext->sDevRegister.pfnDevKmHisr(psDevContext,
				psDevContext->pvDevInstanceData);
	}
}

/*!
 ******************************************************************************

 @Function              dmankm_fnDevKmLisr

 ******************************************************************************/
static IMG_BOOL dmankm_fnDevKmLisr(IMG_VOID * pvParam) 
{
	DMANKM_sDevContext * psDevContext = (DMANKM_sDevContext *) pvParam;

    if(psDevContext == IMG_NULL)
    {
        IMG_ASSERT(psDevContext != IMG_NULL);
    }
    else if(psDevContext->sDevRegister.pfnDevKmLisr == IMG_NULL)
    {
        IMG_ASSERT(psDevContext->sDevRegister.pfnDevKmLisr != IMG_NULL);
    }
	else 
    {
		return psDevContext->sDevRegister.pfnDevKmLisr(psDevContext,
				psDevContext->pvDevInstanceData);
	}
	return IMG_FALSE;
}

/*!
 ******************************************************************************

 @Function				DMANKM_OpenDevice

 ******************************************************************************/
IMG_RESULT DMANKM_OpenDevice(IMG_HANDLE hDevHandle, DMAN_eOpenMode eOpenMode,
		IMG_HANDLE * phConnHandle, IMG_UINT32 * pui32ConnId) 
{
	DMANKM_sDevContext * psDevContext = (DMANKM_sDevContext *) hDevHandle;
	DMANKM_sConnContext * psConnContext;
	DMANKM_sConnContext * psInitConnContext = IMG_NULL;
	IMG_UINT32 ui32Result;
	IMG_HANDLE hProcessId;

	/* Check mode. */
	if ((eOpenMode != DMAN_OMODE_EXCLUSIVE)
			&& (eOpenMode != DMAN_OMODE_SHARED)) {
		IMG_ASSERT(IMG_FALSE);
		return IMG_ERROR_INVALID_PARAMETERS;
	}

	/* Loop over the device connections to see if this process already has a connection...*/
	hProcessId = SYSOSKM_GetProcessId();
	psConnContext = (DMANKM_sConnContext *) LST_first(&psDevContext->sConnList);
	while (psConnContext != IMG_NULL ) {
		/* If process already has a connection. */
		if (psConnContext->hProcessId == hProcessId) {
			/* Update the open count...*/
			psConnContext->ui32OpenCnt++;

			/* Return the connection handle and/or id...*/
			if (phConnHandle != IMG_NULL ) {
				*phConnHandle = psConnContext;
			}
			if (pui32ConnId != IMG_NULL ) {
				*pui32ConnId = psConnContext->ui32ConnId;
			}

			/* Return success...*/
			return IMG_SUCCESS;
		}

		/* Look at next connection. */
		psConnContext = (DMANKM_sConnContext *) LST_next(psConnContext);
	}

	/* See if we have a connection exclusive access required or only exclusive access available. */
	psConnContext = (DMANKM_sConnContext *) LST_first(&psDevContext->sConnList);
	if ((psConnContext != IMG_NULL )&&
	( (eOpenMode == DMAN_OMODE_EXCLUSIVE) ||
			(psConnContext->psDevContext->sDevRegister.ui32ConnFlags == DMAN_CFLAG_EXCLUSIVE) )
	){
	IMG_ASSERT(IMG_FALSE);
	return IMG_ERROR_DEVICE_UNAVAILABLE;
}

	/* Allocate connection context...*/
	psConnContext = IMG_MALLOC(sizeof(*psConnContext));
	if (psConnContext == IMG_NULL ) 
    {
        IMG_ASSERT(psConnContext != IMG_NULL);
		return IMG_ERROR_OUT_OF_MEMORY;
	}
	IMG_MEMSET(psConnContext, 0, sizeof(*psConnContext));

	/* Initialise list of resource allocator...*/
	LST_init(&psConnContext->sAttachList);

	/* Setup connection context...*/
	psConnContext->psDevContext = psDevContext;
	psConnContext->ui32OpenCnt = 1;
	psConnContext->hProcessId = hProcessId;

	/* Update the count of connections...*/
	psDevContext->ui32ConnCnt++;

	/* If this is the first connection...*/
	if (psDevContext->ui32ConnCnt == 1) {
		/* Create resource bucket for connections and attachments...*/
		RMAN_Initialise();
		ui32Result = RMAN_CreateBucket(&psDevContext->hResBHandle);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS) {
			goto error_create_bucket;
		}
	}

	/* Add to list of connections...*/
	LST_add(&psDevContext->sConnList, psConnContext);
	ui32Result = RMAN_RegisterResource(psDevContext->hResBHandle,
			DMAN_CONN_TYPE_ID, IMG_NULL, psConnContext,
			&psConnContext->hResHandle, &psConnContext->ui32ConnId);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		goto error_register_resource;
	}

	/* Register with the Process Manager in case the process dies...*/
	ui32Result = PMAN_Initialise();
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		goto error_pman_init;
	}
	PMAN_RegisterProcessLostCb(dmankm_fnProcessLostCb, psConnContext,
			&psConnContext->hProcLostCbHandle);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		goto error_pman_register_cb;
	}

	/* If this the first connection and initialise function...*/
	if ((psDevContext->ui32ConnCnt == 1)
			&& (psDevContext->sDevRegister.pfnDevInit != IMG_NULL )) {
		/* Allocate implicit connection context...*/
		psInitConnContext = IMG_MALLOC(sizeof(*psInitConnContext));
		if (psInitConnContext == IMG_NULL ) 
        {
            IMG_ASSERT(psInitConnContext != IMG_NULL);
			ui32Result = IMG_ERROR_OUT_OF_MEMORY;
			goto error_init_conn_ctx;
		}
		IMG_MEMSET(psInitConnContext, 0, sizeof(*psInitConnContext));

		/* Associated this connection with the device and process...*/
		psInitConnContext->psDevContext = psDevContext;
		psInitConnContext->ui32OpenCnt = 1;
		psInitConnContext->hProcessId = hProcessId;

		/* Mark this as the init connection...*/
		psInitConnContext->bInitConn = IMG_TRUE;

		/* Add implicit to list of connections...*/
		LST_add(&psDevContext->sConnList, psInitConnContext);
		ui32Result = RMAN_RegisterResource(psDevContext->hResBHandle,
				DMAN_CONN_TYPE_ID, IMG_NULL, psInitConnContext,
				&psInitConnContext->hResHandle, &psInitConnContext->ui32ConnId);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS) {
			goto error_register_resource_init_ctx;
		}

		IMG_ASSERT(
				(psDevContext->sDevRegister.ui32ConnFlags == DMAN_CFLAG_EXCLUSIVE) || (psDevContext->sDevRegister.ui32ConnFlags == DMAN_CFLAG_SHARED));

		/* If it's not a pseudo device...  */
		if ((psDevContext->sDevRegister.ui32DevFlags & DMAN_DFLAG_PSEUDO_DEVICE)
				== 0) {
			/* Open the device...*/
			ui32Result = SYSDEVU_OpenDevice(psDevContext->pszDeviceName,
					&psDevContext->hSysDevHandle);
			IMG_ASSERT(ui32Result == IMG_SUCCESS);
			if (ui32Result != IMG_SUCCESS) {
				goto error_open_device;
			}

			/* Power the device on.  */
			SYSDEVU_SetPowerState(psDevContext->hSysDevHandle,
					SYSOSKM_POWERSTATE_S0, IMG_FALSE);
		}

		ui32Result = psDevContext->sDevRegister.pfnDevInit(psDevContext,
				psInitConnContext, &psDevContext->pvDevInstanceData);
		if (ui32Result != IMG_SUCCESS) {
			REPORT(REPORT_MODULE_DMAN, REPORT_ERR, "dev init failed (%d)",
				ui32Result);
			goto error_dev_init;
		}

		/* If there is a Device Kernel mode HISR...*/
		if (psDevContext->sDevRegister.pfnDevKmHisr != IMG_NULL ) {
			IMG_ASSERT(psDevContext->sDevRegister.pfnDevKmLisr != IMG_NULL);
			ui32Result = SYSOSKM_CreateKmHisr(&dmankm_fnDevKmHisr, psDevContext,
					&psDevContext->hHISRHandle);
			IMG_ASSERT(ui32Result == IMG_SUCCESS);
			if (ui32Result != IMG_SUCCESS) {
				goto error_create_km_hisr;
			}
		}

		/* If there is a Device Kernel mode LISR...*/
		if (psDevContext->sDevRegister.pfnDevKmLisr != IMG_NULL ) {
			/* Register the LISR wrapper...*/
			SYSDEVU_RegisterDevKmLisr(psDevContext->hSysDevHandle,
					&dmankm_fnDevKmLisr, psDevContext);
		}
	}

	/* If connect/open function...*/
	if (psDevContext->sDevRegister.pfnDevConnect != IMG_NULL ) {
		ui32Result = psDevContext->sDevRegister.pfnDevConnect(psConnContext,
				psDevContext->pvDevInstanceData,
				&psConnContext->pvDevConnectionData);
		IMG_ASSERT(
				ui32Result == IMG_SUCCESS || ui32Result == IMG_ERROR_INTERRUPTED);
		if (ui32Result != IMG_SUCCESS && ui32Result != IMG_ERROR_INTERRUPTED) {
			goto error_dev_connect;
		}
	}

	/* Return the connection handle and/or id...*/
	if (phConnHandle != IMG_NULL ) {
		*phConnHandle = psConnContext;
	}
	if (pui32ConnId != IMG_NULL ) {
		*pui32ConnId = psConnContext->ui32ConnId;
	}

	/* Return success...*/
	return ui32Result;

	/* Error handling. */
error_dev_connect:
	/* If this not the first connection or there's no initialise function...*/
	if ((1 != psDevContext->ui32ConnCnt)
			|| (IMG_NULL == psDevContext->sDevRegister.pfnDevInit)) {
		/* ...skip de-initialisation of this part. */
		goto error_init_conn_ctx;
	}

	if (IMG_NULL != psDevContext->sDevRegister.pfnDevKmHisr) {
		SYSOSKM_DestroyKmHisr(psDevContext->hHISRHandle);
	}

error_create_km_hisr:
	if (IMG_NULL
			!= psDevContext->sDevRegister.pfnDevDeinit) {
		psDevContext->sDevRegister.pfnDevDeinit(psDevContext, psInitConnContext,
				psDevContext->pvDevInstanceData);
	}

error_dev_init:
	if ((psDevContext->sDevRegister.ui32DevFlags
			& DMAN_DFLAG_PSEUDO_DEVICE) == 0) {
		SYSDEVU_CloseDevice(psDevContext->hSysDevHandle);
	}

error_open_device:
	RMAN_FreeResource(psInitConnContext->hResHandle);

error_register_resource_init_ctx:
	LST_remove(&psDevContext->sConnList, psInitConnContext);
	IMG_FREE(psInitConnContext);

error_init_conn_ctx:
	PMAN_RemoveProcessLostCb(psConnContext->hProcLostCbHandle);
	/* release per-process resources in PMAN, allocated inside
	   PMAN_RegisterProcessLostCb. We have to use device disconnect,
	   although the device wasn't actually initialised, because no
	   other function is exposed by PMAN */
	PMAN_DevDisconnectComplete(hProcessId);

error_pman_register_cb:
error_pman_init:
	RMAN_FreeResource(psConnContext->hResHandle);

error_register_resource:
	LST_remove(&psDevContext->sConnList,psConnContext);
	if (1 == psDevContext->ui32ConnCnt) {
		RMAN_DestroyBucket(psDevContext->hResBHandle);
	}

error_create_bucket:
	psDevContext->ui32ConnCnt--;
	IMG_FREE(psConnContext);

	return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_OpenDevice)

/*!
 ******************************************************************************

 @Function				DMANKM_CloseDevice

 ******************************************************************************/
IMG_RESULT DMANKM_CloseDevice(IMG_HANDLE hDevHandle, IMG_HANDLE hConnHandle,
		DMANKM_eDisconnType eDisconnType) 
{
	DMANKM_sDevContext * psDevContext = (DMANKM_sDevContext *) hDevHandle;
	DMANKM_sConnContext * psConnContext = (DMANKM_sConnContext *) hConnHandle;
	IMG_UINT32 ui32Result;

	IMG_ASSERT(gDmanKmInitialised);
	IMG_ASSERT(!psConnContext->bInitConn);
	IMG_ASSERT(psConnContext->ui32OpenCnt != 0);

	/* Update the open count...*/
	psConnContext->ui32OpenCnt--;

	/* If abort...*/
	if (eDisconnType == DMAN_DCONN_ABORT) {
		/* Set open count to 0...*/
		psConnContext->ui32OpenCnt = 0;
	}

	/* If this is not the last close...*/
	if (psConnContext->ui32OpenCnt != 0) {
		/* Unlock the device...*/
		DMANKM_UnlockDeviceContext(hDevHandle);

		/* Return success...*/
		return IMG_SUCCESS;
	}

	/* Removed the process lost callback...*/
	PMAN_RemoveProcessLostCb(psConnContext->hProcLostCbHandle);

	/* If disconnect/close function...*/
	if (psDevContext->sDevRegister.pfnDevDisconnect != IMG_NULL ) {
		ui32Result = psDevContext->sDevRegister.pfnDevDisconnect(psConnContext,
				psDevContext->pvDevInstanceData,
				psConnContext->pvDevConnectionData, eDisconnType);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS) {
			return ui32Result;
		}
	} else {
		/* Call complete function synchronously...*/
		DMANKM_DevDisconnectComplete(psConnContext);
	}

	/* Return success...*/
	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_CloseDevice)

/*!
 ******************************************************************************

 @Function              DMANKM_GetDeviceId

 ******************************************************************************/
IMG_RESULT DMANKM_GetDeviceId(IMG_HANDLE hDevHandle, IMG_UINT32 * pui32DeviceId) 
{
	DMANKM_sDevContext * psDevContext = (DMANKM_sDevContext *) hDevHandle;

	IMG_ASSERT(gDmanKmInitialised);

	/* Return the device id */
	*pui32DeviceId = psDevContext->ui32DeviceId;

	/* Return success...*/
	return IMG_SUCCESS;
}

/*!
 ******************************************************************************

 @Function				DMANKM_KmPowerEvent

 ******************************************************************************/
IMG_VOID DMANKM_KmPowerEvent(
		SYSOSKM_ePowerTrans ePowerTrans, SYSOSKM_ePowerState ePowerState,
		IMG_VOID * pvParam) 
{
	DMANKM_sDevContext * psDevContext;

	/* Search list of registered devices for this device...*/
	IMG_ASSERT(gbDevListInitialised);
	psDevContext = (DMANKM_sDevContext *) LST_first(&gsDevList);
	while (psDevContext != IMG_NULL ) {
		if (((psDevContext->sDevRegister.ui32DevFlags & DMAN_DFLAG_PSEUDO_DEVICE)
				== 0) && (psDevContext->ui32ConnCnt != 0)) {
			switch (ePowerTrans) {
			case SYSOSKM_POWERTRANS_PRE:
				switch (ePowerState) {
				case SYSOSKM_POWERSTATE_S0:
					if (psDevContext->sDevRegister.pfnDevPowerPostS0)
						SYSDEVU_SetPowerState(psDevContext->hSysDevHandle,
								ePowerState, IMG_FALSE);
					break;
				case SYSOSKM_POWERSTATE_S5:
					if (psDevContext->sDevRegister.pfnDevPowerPreS5) {
						if (!((psDevContext->ui8ApmPpmFlags & DMAN_DPPM)
								|| (psDevContext->ui8ApmPpmFlags & DMAN_DAPM))) {
							psDevContext->sDevRegister.pfnDevPowerPreS5(
									psDevContext,
									psDevContext->pvDevInstanceData);

							psDevContext->ui8ApmPpmFlags |= DMAN_DPPM;
						} else if ((psDevContext->ui8ApmPpmFlags & DMAN_DAPM)
								&& !(psDevContext->ui8ApmPpmFlags & DMAN_DPPM)) {
							psDevContext->ui8ApmPpmFlags |= DMAN_DPPM;
						} else {
							IMG_ASSERT(
									!"PPM Off Called while core is off by PPM");
						}
					}
					break;
				default:
					/* Unrecognised power state.  */
					IMG_ASSERT(IMG_FALSE);
					break;
				}
				;
				break;
			case SYSOSKM_POWERTRANS_POST:
				switch (ePowerState) {
				case SYSOSKM_POWERSTATE_S0:
					if (psDevContext->sDevRegister.pfnDevPowerPostS0) {
						if ((psDevContext->ui8ApmPpmFlags & DMAN_DPPM)
								&& !(psDevContext->ui8ApmPpmFlags & DMAN_DAPM)) {
							psDevContext->sDevRegister.pfnDevPowerPostS0(
									psDevContext,
									psDevContext->pvDevInstanceData);

							psDevContext->ui8ApmPpmFlags &= ~DMAN_DPPM;

							psDevContext->ui8ApmPpmFlags |= DMAN_DPPM_TURNED_ON;
						} else if ((psDevContext->ui8ApmPpmFlags & DMAN_DPPM)
								&& (psDevContext->ui8ApmPpmFlags & DMAN_DAPM)) {
							psDevContext->ui8ApmPpmFlags &= ~DMAN_DPPM;
						} else {
							IMG_ASSERT(
									!"PPM On Called while core is either On or off by APM");
						}
					}
					break;
				case SYSOSKM_POWERSTATE_S5:
					if (psDevContext->sDevRegister.pfnDevPowerPreS5)
						SYSDEVU_SetPowerState(psDevContext->hSysDevHandle,
								ePowerState, IMG_FALSE);
					break;
				default:
					/* Unrecognised power state.  */
					IMG_ASSERT(IMG_FALSE);
					break;
				}
				;
				break;
			default:
				/* Unrecognised power transition.  */
				IMG_ASSERT(IMG_FALSE);
				break;
			};
		}
		psDevContext = (DMANKM_sDevContext *) LST_next(psDevContext);
	}
}

/*!
 ******************************************************************************

 @Function				DMANKM_Initialise

 ******************************************************************************/
IMG_RESULT DMANKM_Initialise(IMG_VOID) 
{
	/* If not initialised...*/
	if (!gDmanKmInitialised) {
		/* Register Power Event callback function.  */
		SYSOSKM_RegisterKmPowerEventCb(DMANKM_KmPowerEvent, NULL );

		/* Device manager is initialised...*/
		gDmanKmInitialised = IMG_TRUE;
	}

	/* Return success...*/
	return IMG_SUCCESS;
}

/*!
 ******************************************************************************

 @Function				DMANKM_Deinitialise

 ******************************************************************************/
IMG_VOID DMANKM_Deinitialise(
		IMG_VOID) 
{
	/* If devices have been registered...*/
	if (gbDevListInitialised) {
		/* Free device contexts...*/
		IMG_ASSERT(gbDevListInitialised);
		/* Device list is no longer initialised...*/
		gbDevListInitialised = IMG_FALSE;
	}

	/* If initialised...*/
	if (gDmanKmInitialised) {
		/* Device manager is no longer initialised...*/
		gDmanKmInitialised = IMG_FALSE;
	}
}

/*!
 ******************************************************************************

 @Function				DMANKM_RegisterDevice

 ******************************************************************************/
IMG_RESULT DMANKM_RegisterDevice(IMG_CHAR * pszDeviceName,
		DMANKM_pfnDevRegister pfnDevRegister) 
{
	DMANKM_sDevContext * psDevContext;
	IMG_UINT32 ui32Result;

	/* If the device context list is not initialised...*/
	if (!gbDevListInitialised) {
		/* Initialise the device context list...*/
		LST_init(&gsDevList);

		gbDevListInitialised = IMG_TRUE;
	}

	/* Locate the device - ensure it's not registered twice...*/
	ui32Result = DMANKM_LocateDevice(pszDeviceName,
			(IMG_HANDLE *) &psDevContext);
	if (ui32Result != IMG_ERROR_DEVICE_NOT_FOUND) {
        IMG_ASSERT(ui32Result == IMG_ERROR_DEVICE_NOT_FOUND);
		return IMG_ERROR_GENERIC_FAILURE;
	}

	/* Allocate a device context structure...*/
	psDevContext = IMG_MALLOC(sizeof(*psDevContext));
	if (psDevContext == IMG_NULL ) 
    {
        IMG_ASSERT(psDevContext != IMG_NULL);
		return IMG_ERROR_OUT_OF_MEMORY;
	}

	IMG_MEMSET(psDevContext, 0, sizeof(*psDevContext));

	/* Setup the device context...*/
	psDevContext->ui32DeviceId = gui32NextDeviceID;
	gui32NextDeviceID++;
	psDevContext->pszDeviceName = IMG_STRDUP(pszDeviceName);
	if (psDevContext->pszDeviceName == IMG_NULL ) 
    {
        IMG_ASSERT(psDevContext->pszDeviceName != IMG_NULL);
		ui32Result = IMG_ERROR_OUT_OF_MEMORY;
		goto error_dev_name;
	}
	psDevContext->pfnDevRegister = pfnDevRegister;
	psDevContext->ui8ApmPpmFlags = 0;
	ui32Result = SYSOSKM_CreateMutex(&psDevContext->hMutexHandle);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		goto error_create_mutex;
	}
	LST_init(&psDevContext->sConnList);

	/* Disable interrupts...*/
	SYSOSKM_DisableInt();

	/* Add device to list...*/
	LST_add(&gsDevList, psDevContext);

	/* Re-enable interrupts...*/
	SYSOSKM_EnableInt();

	/* If initialised...*/
	if (gDmanKmInitialised) {
		/* Call device registration function...*/
		ui32Result = psDevContext->pfnDevRegister(&psDevContext->sDevRegister);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS) {
			goto error_dev_register;
		}

		/* Set default if required...*/
		if (psDevContext->sDevRegister.ui32ConnFlags == 0) {
			psDevContext->sDevRegister.ui32ConnFlags = DMAN_CFLAG_EXCLUSIVE;
		}
	}

	/* Return success...*/
	return IMG_SUCCESS;

	/* Error handling. */
	error_dev_register: SYSOSKM_DisableInt();
	LST_remove(&gsDevList, psDevContext);
	SYSOSKM_EnableInt();
	SYSOSKM_DestroyMutex(psDevContext->hMutexHandle);
	error_create_mutex:
	IMG_FREE(psDevContext->pszDeviceName);
	error_dev_name:
	IMG_FREE(psDevContext);

	return ui32Result;
}

/*!
 ******************************************************************************

 @Function				DMANKM_UnRegisterDevice

 ******************************************************************************/
IMG_RESULT DMANKM_UnRegisterDevice(IMG_CHAR * pszDeviceName) 
{
	DMANKM_sDevContext *devContext;
	DMANKM_sConnContext *devConnection;
	IMG_RESULT ui32Result;

	devContext = (DMANKM_sDevContext *) LST_first(&gsDevList);
	while (devContext != IMG_NULL ) {
		if (!strcmp(devContext->pszDeviceName, pszDeviceName)) {
			devConnection = (DMANKM_sConnContext *) LST_first(
					&devContext->sConnList);
			while (devConnection != IMG_NULL ) {
				/* If this is the init connection....*/
				if (devConnection->bInitConn) {
					devConnection = (DMANKM_sConnContext *) LST_next(
							&devContext->sConnList);
				} else {
					/* Lock the device...*/
					DMANKM_LockDeviceContext(devContext);

					/* Call on to the kernel function...*/
					ui32Result = DMANKM_CloseDevice(devContext, devConnection,
							DMAN_DCONN_ABORT);
					IMG_ASSERT(ui32Result == IMG_SUCCESS);

					// NOTE: We do not unlock the device as this will be done by
					//	     DMANKM_DevDisconnectComplete().
					//					/* Unlock the device...*/
					//					DMANKM_UnlockDeviceContext(hDevHandle);

					/* Move to next connection...*/
					devConnection = (DMANKM_sConnContext *) LST_first(
							&devContext->sConnList);
				}
			}

			SYSOSKM_DestroyMutex(devContext->hMutexHandle);

			/* Remove entries in debug file system */
#ifdef IMG_KERNEL_MODULE
			//if (devContext->psDgRoot) {
			//	debugfs_remove_recursive(devContext->psDgRoot);
			//}
#endif
			LST_remove(&gsDevList, devContext);

			IMG_FREE(devContext->pszDeviceName);
			IMG_FREE(devContext);

			return IMG_SUCCESS;
		}
		devContext = LST_next(devContext);
	}
	return IMG_ERROR_GENERIC_FAILURE;
}

/*!
 ******************************************************************************

 @Function				DMANKM_DevDisconnectComplete

 ******************************************************************************/
IMG_RESULT DMANKM_DevDisconnectComplete(IMG_HANDLE hConnHandle) 
{
	IMG_UINT32 ui32Result;
	DMANKM_sConnContext * psConnContext = hConnHandle;
	DMANKM_sConnContext * psInitConnContext;
	DMANKM_sDevContext * psDevContext = psConnContext->psDevContext;
	IMG_HANDLE hProcessId;

	/* Disconnect components attached to this connection...*/
	ui32Result = dmankm_DisconnectComps(psConnContext);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		return ui32Result;
	}

	/* Save the process id...*/
	hProcessId = psConnContext->hProcessId;

	/* Remove and free this connection...*/
	LST_remove(&psDevContext->sConnList, psConnContext);
	RMAN_FreeResource(psConnContext->hResHandle);
	IMG_FREE(psConnContext);

	/* Update the connection count...*/
	psDevContext->ui32ConnCnt--;

	/* If connection count 0...*/
	if (psDevContext->ui32ConnCnt == 0) {
		/* Deinitailise the device....*/
		psInitConnContext = (DMANKM_sConnContext *) LST_first(
				&psDevContext->sConnList);
        if(psInitConnContext == NULL)
        {
            IMG_ASSERT(psInitConnContext != IMG_NULL);
            return IMG_ERROR_GENERIC_FAILURE;
        }
        else
        {
            IMG_ASSERT(psInitConnContext->bInitConn);
        }

		/* Deregister the LISR...*/
		if (psDevContext->sDevRegister.pfnDevKmLisr != IMG_NULL ) {
			SYSDEVU_RemoveDevKmLisr(psDevContext->hSysDevHandle);
		}

		/* Deregister the HISR...*/
		if (psDevContext->sDevRegister.pfnDevKmHisr != IMG_NULL ) {
			if (psDevContext->hHISRHandle) {
				IMG_HANDLE HISRHandle = psDevContext->hHISRHandle;
				psDevContext->hHISRHandle = IMG_NULL;
				SYSOSKM_DestroyKmHisr(HISRHandle);
			}
		}

		/* If we have a deinitialise function...*/
		if (psDevContext->sDevRegister.pfnDevDeinit != IMG_NULL ) {
			psDevContext->sDevRegister.pfnDevDeinit(psDevContext,
					psInitConnContext, psDevContext->pvDevInstanceData);
		}

		if ((psDevContext->sDevRegister.ui32DevFlags & DMAN_DFLAG_PSEUDO_DEVICE)
				== 0) {
			/* Power the device off.  */
			SYSDEVU_SetPowerState(psDevContext->hSysDevHandle,
					SYSOSKM_POWERSTATE_S5, IMG_FALSE);
		}

		/* Disconnect components attached to the implicit connection...*/
		ui32Result = dmankm_DisconnectComps(psInitConnContext);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS) {
			return ui32Result;
		}

		/* Remove and free the implicit connection...*/
		LST_remove(&psDevContext->sConnList, psInitConnContext);
		RMAN_FreeResource(psInitConnContext->hResHandle);
		IMG_FREE(psInitConnContext);

		/* Destroy the resource bucket used for connections and attachments...*/
		RMAN_DestroyBucket(psDevContext->hResBHandle);
		psDevContext->hResBHandle = IMG_NULL;

		/* If we opened the device with SYSDEVKM...*/
		if (psDevContext->hSysDevHandle != IMG_NULL ) {
			/* Close it...*/
			SYSDEVU_CloseDevice(psDevContext->hSysDevHandle);
			psDevContext->hSysDevHandle = IMG_NULL;
		}
	}

	/* Let the Process Manager know the connection has been broken...*/
	PMAN_DevDisconnectComplete(hProcessId);

	/* Unlock the device...*/
	DMANKM_UnlockDeviceContext(psDevContext);

	/* Return success...*/
	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_DevDisconnectComplete)

/*!
 ******************************************************************************

 @Function				dman_LocateComponentKM

 ******************************************************************************/
static IMG_BOOL dman_LocateComponentKM(IMG_CHAR * pszCompName,
		DMANKM_sConnContext * psConnContext,
		DMANKM_sAttachContext ** ppsAttachContext) 
{
	DMANKM_sAttachContext * psAttachContext;

	/* Search list of attached resource allocator for this connection...*/
	psAttachContext = (DMANKM_sAttachContext *) LST_first(
			&psConnContext->sAttachList);
	while ((psAttachContext != IMG_NULL )&&
	(IMG_STRCMP(psAttachContext->pszCompName, pszCompName) != 0)
	){
	psAttachContext = (DMANKM_sAttachContext *)LST_next(psAttachContext);
}

	/* If resource allocator found...*/
	if (psAttachContext != IMG_NULL ) {
		*ppsAttachContext = psAttachContext;
		return IMG_TRUE;
	}

	/* Device not found....*/
	return IMG_FALSE;
}

/*!
 ******************************************************************************

 @Function				DMANKM_AttachComponent

 ******************************************************************************/
IMG_RESULT DMANKM_AttachComponent(IMG_HANDLE hConnHandle,
		IMG_CHAR * pszCompName, DMANKM_pfnCompAttach pfnCompAttach,
		IMG_HANDLE * phAttachHandle, IMG_UINT32 * pui32AttachId) 
{
	DMANKM_sConnContext * psConnContext = (DMANKM_sConnContext *) hConnHandle;
	IMG_BOOL bFound;
	DMANKM_sAttachContext * psAttachContext;
	IMG_UINT32 ui32Result;

	IMG_ASSERT(gDmanKmInitialised);

	/* See if this component is already register with this connection...*/
	bFound = dman_LocateComponentKM(pszCompName, psConnContext,
			&psAttachContext);
	if (bFound) {
		/* Cross check name and attach function should be the same...*/
		IMG_ASSERT(psAttachContext->pfnCompAttach == pfnCompAttach);

		/* Return the attachment handle and/or id...*/
		if (phAttachHandle != IMG_NULL ) {
			*phAttachHandle = psAttachContext;
		}
		if (pui32AttachId != IMG_NULL ) {
			*pui32AttachId = psAttachContext->ui32AttachId;
		}

		return IMG_SUCCESS;
	}

	/* Allocate a attachment context structure...*/
	psAttachContext = IMG_MALLOC(sizeof(*psAttachContext));
	if (psAttachContext == IMG_NULL ) 
    {
        IMG_ASSERT(psAttachContext != IMG_NULL);
		return IMG_ERROR_OUT_OF_MEMORY;
	}
	IMG_MEMSET(psAttachContext, 0, sizeof(*psAttachContext));

	/* Copy the component name etc...*/
	psAttachContext->pszCompName = IMG_STRDUP(pszCompName);
	if (psAttachContext->pszCompName == IMG_NULL ) 
    {
        IMG_ASSERT(psAttachContext->pszCompName != IMG_NULL);
		ui32Result = IMG_ERROR_OUT_OF_MEMORY;
		goto error_comp_name;
	}
	psAttachContext->pfnCompAttach = pfnCompAttach;
	psAttachContext->psConnContext = psConnContext;
	ui32Result = RMAN_CreateBucket(&psAttachContext->hResBHandle);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		goto error_create_bucket;
	}

	/* Add to the attachment component list...*/
	LST_add(&psConnContext->sAttachList, psAttachContext);
	ui32Result = RMAN_RegisterResource(psConnContext->psDevContext->hResBHandle,
			DMAN_ATTACH_TYPE_ID, IMG_NULL, psAttachContext,
			&psAttachContext->hResHandle, &psAttachContext->ui32AttachId);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		goto error_register_resource;
	}

	/* Call components attach function...*/
	ui32Result = pfnCompAttach(psAttachContext, &psAttachContext->sCompAttach);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS) {
		goto error_comp_attach;
	}

	/* If connect/open function...*/
	if (psAttachContext->sCompAttach.pfnCompConnect != IMG_NULL ) {
		ui32Result = psAttachContext->sCompAttach.pfnCompConnect(
				psAttachContext, &psAttachContext->pvCompAttachmentData);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS) {
			goto error_comp_connect;
		}
	}

	/* Return the attachment handle and/or id...*/
	if (phAttachHandle != IMG_NULL ) {
		*phAttachHandle = psAttachContext;
	}
	if (pui32AttachId != IMG_NULL ) {
		*pui32AttachId = psAttachContext->ui32AttachId;
	}

	/* Return success...*/
	return IMG_SUCCESS;

	/* Error handling. */
	error_comp_connect: error_comp_attach: RMAN_FreeResource(
			psAttachContext->hResHandle);
	error_register_resource: LST_remove(&psConnContext->sAttachList,
			psAttachContext);
	RMAN_DestroyBucket(psAttachContext->hResBHandle);
	error_create_bucket:
	IMG_FREE(psAttachContext->pszCompName);
	error_comp_name:
	IMG_FREE(psAttachContext);

	return ui32Result;
}

/*!
 ******************************************************************************

 @Function              DMANKM_GetConnIdFromHandle

 ******************************************************************************/
IMG_UINT32 DMANKM_GetConnIdFromHandle(IMG_HANDLE hConnHandle) {
	DMANKM_sConnContext * psConnContext = (DMANKM_sConnContext *) hConnHandle;
	return psConnContext->ui32ConnId;
}

IMGVIDEO_EXPORT_SYMBOL(DMANKM_GetConnIdFromHandle)
/*!
 ******************************************************************************

 @Function              DMANKM_GetConnHandleFromId

 ******************************************************************************/
IMG_RESULT DMANKM_GetConnHandleFromId(IMG_UINT32 ui32ConnId,
		IMG_HANDLE * phConnHandle) {
	IMG_UINT32 ui32Result;

	ui32Result = RMAN_GetResource(ui32ConnId, DMAN_CONN_TYPE_ID, phConnHandle,
			IMG_NULL );
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(DMANKM_GetConnHandleFromId)

/*!
 ******************************************************************************

 @Function              DMANKM_GetConnProcId

 ******************************************************************************/
IMG_HANDLE DMANKM_GetConnProcId(IMG_HANDLE hConnHandle) 
{
	DMANKM_sConnContext * psConnContext = (DMANKM_sConnContext *) hConnHandle;
	return psConnContext->hProcessId;
}

/*!
 ******************************************************************************

 @Function              DMANKM_GetAttachIdFromHandle

 ******************************************************************************/
IMG_UINT32 DMANKM_GetAttachIdFromHandle(IMG_HANDLE hAttachHandle) 
{
	DMANKM_sAttachContext * psAttachContext =
			(DMANKM_sAttachContext *) hAttachHandle;
	return psAttachContext->ui32AttachId;
}

/*!
 ******************************************************************************

 @Function              DMANKM_GetAttachHandleFromId

 ******************************************************************************/
IMG_RESULT DMANKM_GetAttachHandleFromId(IMG_UINT32 ui32AttachId,
		IMG_HANDLE * phAttachHandle) 
{
	IMG_UINT32 ui32Result;

	ui32Result = RMAN_GetResource(ui32AttachId, DMAN_ATTACH_TYPE_ID,
			phAttachHandle, IMG_NULL );
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	return ui32Result;
}

/*!
 ******************************************************************************

 @Function              DMANKM_GetAttachResBucket

 ******************************************************************************/
IMG_HANDLE DMANKM_GetAttachResBucket(IMG_HANDLE hAttachHandle) 
{
	DMANKM_sAttachContext * psAttachContext =
			(DMANKM_sAttachContext *) hAttachHandle;
	return psAttachContext->hResBHandle;
}

/*!
 ******************************************************************************

 @Function              DMANKM_GetConnFromAttachHandle

 ******************************************************************************/
IMG_HANDLE DMANKM_GetConnFromAttachHandle(IMG_HANDLE hAttachHandle) 
{
	DMANKM_sAttachContext * psAttachContext =
			(DMANKM_sAttachContext *) hAttachHandle;
	return psAttachContext->psConnContext;
}

/*!
 ******************************************************************************

 @Function				DMANKM_ActivateKmHisr

 ******************************************************************************/
IMG_VOID DMANKM_ActivateKmHisr(
		IMG_HANDLE hDevHandle)
{
	DMANKM_sDevContext * psDevContext = (DMANKM_sDevContext *) hDevHandle;

	/* Call HISR callback make callback...*/
	IMG_ASSERT(psDevContext->sDevRegister.pfnDevKmHisr != IMG_NULL);
	IMG_ASSERT(psDevContext->hHISRHandle != IMG_NULL);
	if (psDevContext->hHISRHandle != IMG_NULL ) {
		SYSOSKM_ActivateKmHisr(psDevContext->hHISRHandle);
	}
}

IMGVIDEO_EXPORT_SYMBOL(DMANKM_ActivateKmHisr)

/*!
 ******************************************************************************

 @Function				DMANKM_GetKmBuildFlags

 ******************************************************************************/
IMG_RESULT DMANKM_GetKmBuildFlags(IMG_UINT32 * pui32KmBuildFlags) 
{
	*pui32KmBuildFlags = gui32KmBuildFlags;
	return IMG_SUCCESS;
}

/*!
 ******************************************************************************

 @Function				DMANKM_ResetPowerManagementFlag

 ******************************************************************************/
IMG_VOID DMANKM_ResetPowerManagementFlag(
		IMG_HANDLE hDevHandle) 
{
	DMANKM_sDevContext * psDevContext;
	if (hDevHandle == IMG_NULL ) 
    {
		return;
	}

	psDevContext = (DMANKM_sDevContext *) hDevHandle;

	if ((psDevContext->sDevRegister.ui32DevFlags & DMAN_DFLAG_PSEUDO_DEVICE)
			== 0) {
		psDevContext->ui8ApmPpmFlags = 0;
	}

}

IMGVIDEO_EXPORT_SYMBOL(DMANKM_ResetPowerManagementFlag)
/*!
 ******************************************************************************

 @Function				DMANKM_SuspendDevice

 ******************************************************************************/
IMG_VOID DMANKM_SuspendDevice(
		IMG_HANDLE hDevHandle) 
{
	DMANKM_sDevContext * psDevContext;
	if (hDevHandle == IMG_NULL ) 
    {
		return;
	}

	/* Take mutex */
	SYSOSKM_LockMutex(((DMANKM_sDevContext *) hDevHandle)->hMutexHandle);

	psDevContext = (DMANKM_sDevContext *) hDevHandle;

	if ((psDevContext->sDevRegister.ui32DevFlags & DMAN_DFLAG_PSEUDO_DEVICE)
			== 0) {
		if (!((psDevContext->ui8ApmPpmFlags & DMAN_DAPM)
				|| (psDevContext->ui8ApmPpmFlags & DMAN_DPPM))) {
			//psDevContext->sDevRegister.pfnDevPowerPreS5(psDevContext, psDevContext->pvDevInstanceData);
			SYSDEVU_SetPowerState(psDevContext->hSysDevHandle,
					SYSOSKM_POWERSTATE_S5, IMG_TRUE);

			psDevContext->ui8ApmPpmFlags |= DMAN_DAPM;
		} else {
			IMG_ASSERT(
					!"APM off Called while core is off by either APM or PPM");
		}
	}
	/* Release mutex */
	SYSOSKM_UnlockMutex(((DMANKM_sDevContext *) hDevHandle)->hMutexHandle);
}

IMGVIDEO_EXPORT_SYMBOL(DMANKM_SuspendDevice)

/*!
 ******************************************************************************

 @Function				DMANKM_ResumeDevice

 ******************************************************************************/
IMG_VOID DMANKM_ResumeDevice(
		IMG_HANDLE hDevHandle,
		IMG_BOOL   bEnableLock)
{
	DMANKM_sDevContext * psDevContext;

	if (hDevHandle == IMG_NULL ) 
    {
		return;
	}
	if(IMG_TRUE == bEnableLock)
	{
		/* Take mutex */
		SYSOSKM_LockMutex(((DMANKM_sDevContext *) hDevHandle)->hMutexHandle);
	}

	psDevContext = (DMANKM_sDevContext *) hDevHandle;

	if ((psDevContext->sDevRegister.ui32DevFlags & DMAN_DFLAG_PSEUDO_DEVICE)
			== 0) {
		if ((psDevContext->ui8ApmPpmFlags & DMAN_DAPM)
				&& !(psDevContext->ui8ApmPpmFlags & DMAN_DPPM)) {
			SYSDEVU_SetPowerState(psDevContext->hSysDevHandle,
					SYSOSKM_POWERSTATE_S0, IMG_TRUE);
			//psDevContext->sDevRegister.pfnDevPowerPostS0(psDevContext, psDevContext->pvDevInstanceData);

			psDevContext->ui8ApmPpmFlags &= ~DMAN_DAPM;
		} else {
			IMG_ASSERT( !"APM On Called while core is on or is off by PPM");
		}
	}
	if(IMG_TRUE == bEnableLock)
	{
		/* Release mutex */
		SYSOSKM_UnlockMutex(((DMANKM_sDevContext *) hDevHandle)->hMutexHandle);
	}
}

IMGVIDEO_EXPORT_SYMBOL(DMANKM_ResumeDevice)
/*!
 ******************************************************************************

 @Function				DMANKM_ReadPpmTurnedOnFlag

 ******************************************************************************/
IMG_VOID DMANKM_ReadPpmTurnedOnFlag(
		IMG_HANDLE hDevHandle, IMG_UINT8 * pui8PpmTurnedOn) 
{
	DMANKM_sDevContext * psDevContext;

	psDevContext = (DMANKM_sDevContext *) hDevHandle;

	if ((psDevContext->sDevRegister.ui32DevFlags & DMAN_DFLAG_PSEUDO_DEVICE)
			== 0) {
		*pui8PpmTurnedOn = psDevContext->ui8ApmPpmFlags & DMAN_DPPM_TURNED_ON;
		if (*pui8PpmTurnedOn) {
			psDevContext->ui8ApmPpmFlags &= ~DMAN_DPPM_TURNED_ON; //clears the ppm turned on flag
		}
	}
}

