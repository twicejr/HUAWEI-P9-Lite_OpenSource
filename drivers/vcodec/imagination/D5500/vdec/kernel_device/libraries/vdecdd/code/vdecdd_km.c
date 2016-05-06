/*!
 *****************************************************************************
 *
 * @File       vdecdd_km.c
 * @Title      VDEC Kernel Mode Device Driver
 * @Description    This file contains the VDEC Kernel Mode Device Driver.
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

#include "vdecdd_utils.h"
#include "vdecdd.h"
#include "vdecdd_km.h"
#include "vdecdd_int.h"
#include "core_api.h"
#include "decoder.h"
#include "scheduler.h"
#include "null_device_km.h"

#include "rman_api.h"
#include "dman_api.h"
#include "dbgopt_api_km.h"
#include "sysdev_utils.h"
#include "report_api.h"

#ifdef SYSBRG_BRIDGING
    #include "vdecdd_devif.h"
    #include "bspp_km.h"

    #include <linux/module.h>
    #include <linux/version.h>
    #include "sysbrg_utils.h"
    #include <api_common.h>
    #include "vdecdd_rpc.h"
#ifdef SECURE_MEDIA_SUPPORT
    #include "bspp_km_rpc.h"
    #include "securemem.h"
#endif
#ifdef IMG_MEM_ERROR_INJECTION
#include "mem_error_injector.h"
#endif /* IMG_MEM_ERROR_INJECTION */
    static SYSBRGKM_sAPIInfo asAPIInfo[] = {
        SYS_BRIDGE(VDECDD)
#ifdef SECURE_MEDIA_SUPPORT
        SYS_BRIDGE(BSPP_KM)
#endif
    };
#else
#define __init
#endif


#define FUNCTION_START  DEBUG_REPORT(REPORT_MODULE_VDECDD, "Start: %s:%d", __FUNCTION__, __LINE__);
#define FUNCTION_END    DEBUG_REPORT(REPORT_MODULE_VDECDD, "End  : %s:%d", __FUNCTION__, __LINE__);

static SYSDEVU_sInfo vdec_device = {IMG_NULL, SYS_DEVICE("VDEC", VDEC, IMG_FALSE)};
static SYSDEVU_sInfo null_device = {IMG_NULL, SYS_DEVICE("NULL", NULL, IMG_FALSE)};

/*!
******************************************************************************
 This array defines names of the VDEC standards.
 Shall be in sync with #VDEC_eVidStd
 @brief  Names of the VDEC standards
******************************************************************************/
IMG_CHAR * gapszVidStd[] =
{
    "VDEC_STD_UNDEFINED",
    "VDEC_STD_MPEG2",
    "VDEC_STD_MPEG4",
    "VDEC_STD_H263",
    "VDEC_STD_H264",
    "VDEC_STD_VC1",
    "VDEC_STD_AVS",
    "VDEC_STD_REAL",
    "VDEC_STD_JPEG",
    "VDEC_STD_VP6",
    "VDEC_STD_VP8",
    "VDEC_STD_SORENSON",
    "VDEC_STD_HEVC"
};




/* Temporary fix to make vdec work with the new 64bit/32bit compatibility imgvideo implementation,
   at least for the pure 32/32 or 64/64 bit runtime mode */

/*!
******************************************************************************

 @Function              vdecddkm_GetStreamContext

 @Description

 Must be stopped when obtaining the stream context.

 ******************************************************************************/
static IMG_RESULT vdecddkm_GetStreamContext(
    IMG_UINT32               ui32StrId,
    VDECDD_sDdStrContext **  ppsDdStrContext
)
{
    IMG_RESULT ui32Result;

    /* Get access to stream context...*/
    ui32Result = RMAN_GetResource(ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)ppsDdStrContext, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
            "[SID=0x%08X] Stream ID not valid",
            ui32StrId);
        return ui32Result;
    }

    if ((*ppsDdStrContext)->eDdStrState != VDECDD_STRSTATE_STOPPED)
    {
        // Don't return the stream state if not stopped.
        IMG_ASSERT("Stream not stopped when accessing context from UM thread" == IMG_NULL);
        *ppsDdStrContext = IMG_NULL;

        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
               "[SID=0x%08X] Stream not stopped when accessing context from UM thread",
               ui32StrId);

        return IMG_ERROR_UNEXPECTED_STATE;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdeckm_fnDevInit

 See definition of #DMANKM_pfnDevInit.

******************************************************************************/
static IMG_RESULT vdeckm_fnDevInit (
    IMG_HANDLE   hDevHandle,
    IMG_HANDLE   hInitConnHandle,
    IMG_VOID **  ppvDevInstanceData
)
{
    IMG_RESULT                    ui32Result;
    VDECDD_sDdDevContext *        psDdDevContext;

    /* Initialise the core...*/
    ui32Result = CORE_Initialise(hDevHandle, vdec_device.sMemPool, vdec_device.secureMemPool, &psDdDevContext);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    /* Return the device context...*/
    *ppvDevInstanceData = psDdDevContext;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdeckm_fnDevDeinit

 See definition of #DMANKM_pfnDevDeinit.

******************************************************************************/
static IMG_VOID vdeckm_fnDevDeinit (
    IMG_HANDLE                    hDevHandle,
    IMG_HANDLE                    hInitConnHandle,
    IMG_VOID *                    pvDevInstanceData
)
{
    VDECDD_sDdDevContext *        psDdDevContext = (VDECDD_sDdDevContext *)pvDevInstanceData;
    IMG_RESULT                    ui32Result;

    /* Deinitialise the core...*/
    ui32Result = CORE_Deinitialise(psDdDevContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
}


/*!
******************************************************************************

 @Function              vdeckm_fnDevConnect

 See definition of #DMANKM_fnDevConnect.

******************************************************************************/
static IMG_RESULT vdeckm_fnDevConnect (
    IMG_HANDLE      hConnHandle,
    IMG_VOID      * pvDevInstanceData,
    IMG_VOID     ** ppvDevConnectionData
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdDevContext  * psDdDevContext = (VDECDD_sDdDevContext *)pvDevInstanceData;
    VDECDD_sDdConnContext * psDdConnContext;

    /* Create a connection to the core..*/
    ui32Result = CORE_ConnectionCreate(psDdDevContext, &psDdConnContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    psDdConnContext->ui32ConnId = DMANKM_GetConnIdFromHandle(hConnHandle);

    /* Return the connection context...*/
    *ppvDevConnectionData = psDdConnContext;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdeckm_fnDevDisconnect

 See definition of #DMANKM_pfnDevDisconnect.

******************************************************************************/
static IMG_RESULT vdeckm_fnDevDisconnect (
    IMG_HANDLE                    hConnHandle,
    IMG_VOID *                    pvDevInstanceData,
    IMG_VOID *                    pvDevConnectionData,
    DMANKM_eDisconnType           eDisconnType
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdConnContext * psDdConnContext = (VDECDD_sDdConnContext *)pvDevConnectionData;

    // Only destroy connection if one was successfully made.
    if (psDdConnContext)
    {
        /* Destroy core connection. */
        ui32Result = CORE_ConnectionDestroy(psDdConnContext->ui32ConnId);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            DMANKM_DevDisconnectComplete(hConnHandle);
            return ui32Result;
        }
    }

    /* Signal the disconnect has completed. */
    ui32Result = DMANKM_DevDisconnectComplete(hConnHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdeckm_fnDevKmHisr

 See definition of #DMANKM_pfnDevKmHisr.

******************************************************************************/
static IMG_VOID vdeckm_fnDevKmHisr(
    IMG_HANDLE                hDevHandle,
    IMG_VOID *                pvDevInstanceData
)
{
    VDECDD_sDdDevContext *            psDdDevContext = (VDECDD_sDdDevContext *)pvDevInstanceData;

    /* Allow the core to process an event. */
    while(CORE_ProcessEvent(psDdDevContext) == IMG_SUCCESS)
    {
        // keep servicing the message queue until it is empty.
    }
}


/*!
******************************************************************************

 @Function              vdeckm_fnDevKmLisr

 See definition of #DMANKM_pfnDevKmLisr.

******************************************************************************/
static IMG_BOOL vdeckm_fnDevKmLisr(
    IMG_HANDLE                hDevHandle,
    IMG_VOID *                pvDevInstanceData
)
{
    VDECDD_sDdDevContext *            psDdDevContext = (VDECDD_sDdDevContext *)pvDevInstanceData;

    DECODER_HandleInterrupt(psDdDevContext);

    // Signal interrupt serviced
    return IMG_TRUE;
}

/*!
******************************************************************************

 @Function              vdeckm_fnDevPowerPreS5

 See definition of #DMANKM_pfnDevPowerPreS5.


******************************************************************************/
static IMG_VOID vdeckm_fnDevPowerPreS5(
    IMG_HANDLE                    hDevHandle,
    IMG_VOID *                    pvDevInstanceData
)
{
    VDECDD_sDdDevContext *            psDdDevContext = (VDECDD_sDdDevContext *)pvDevInstanceData;

    /* Pass on to core. */
    CORE_DevPowerPreS5(psDdDevContext);
}

/*!
******************************************************************************

 @Function              vdeckm_fnDevPowerPostS0

 See definition of #DMANKM_pfnDevPowerPostS0.

******************************************************************************/
static IMG_VOID vdeckm_fnDevPowerPostS0(
    IMG_HANDLE                    hDevHandle,
    IMG_VOID *                    pvDevInstanceData
)
{
    VDECDD_sDdDevContext *            psDdDevContext = (VDECDD_sDdDevContext *)pvDevInstanceData;

    /* Pass on to core. */
    CORE_DevPowerPostS0(psDdDevContext);
}


/*!
******************************************************************************

 @Function              VDECKM_fnDevRegister

 See definition of #DMANKM_pfnDevRegister.

******************************************************************************/
IMG_RESULT VDECKM_fnDevRegister (
    DMANKM_sDevRegister *        psDevRegister
)
{
    FUNCTION_START;

    psDevRegister->ui32ConnFlags    = DMAN_CFLAG_SHARED;
    psDevRegister->pfnDevInit       = vdeckm_fnDevInit;
    psDevRegister->pfnDevDeinit     = vdeckm_fnDevDeinit;
    psDevRegister->pfnDevDisconnect = vdeckm_fnDevDisconnect;
    psDevRegister->pfnDevConnect    = vdeckm_fnDevConnect;

    psDevRegister->pfnDevKmHisr     = vdeckm_fnDevKmHisr;
    psDevRegister->pfnDevKmLisr     = vdeckm_fnDevKmLisr;

    psDevRegister->pfnDevPowerPreS5  = vdeckm_fnDevPowerPreS5;
    psDevRegister->pfnDevPowerPostS0 = vdeckm_fnDevPowerPostS0;

    FUNCTION_END;
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              VDECDD_Init

******************************************************************************/
int __init VDECDD_Init(IMG_VOID)
{
    IMG_RESULT ui32Result;

#ifdef SYSBRG_BRIDGING
    IMG_UINT32 i;

    ui32Result = SYSDEVU_VDECRegisterDriver(&vdec_device);
    if(IMG_SUCCESS != ui32Result)
    {
        goto error_reg_drv_vdec;
    }
#ifdef SECURE_MEDIA_SUPPORT
    ui32Result = SECURE_AddSecureMemory(&vdec_device, &vdec_device.secureMemPool);
    if(IMG_SUCCESS != ui32Result)
    {
        goto error_add_sec_mem;
    }
    null_device.secureMemPool = vdec_device.secureMemPool;
#endif /* SECURE_MEDIA_SUPPORT */
#else /* ndef SYSBRG_BRIDGING */

    static IMG_BOOL bInit = IMG_FALSE;

    if(bInit)
        return 0;

    ui32Result = SYSDEVU_RegisterDriver(&vdec_device);
    if(IMG_SUCCESS != ui32Result)
    {
        goto error_reg_drv_vdec;
    }
#endif /* ndef SYSBRG_BRIDGING */

    null_device.sMemPool = vdec_device.sMemPool;

    ui32Result = SYSDEVU_RegisterDevice(&vdec_device);
    if(IMG_SUCCESS != ui32Result)
    {
        goto error_dev_reg_vdec;
    }

    ui32Result = SYSDEVU_RegisterDevice(&null_device);
    if(IMG_SUCCESS != ui32Result)
    {
        goto error_dev_reg_null;
    }

#ifdef SYSBRG_BRIDGING
    // register SYSBRG APIs.
    for (i = 0; i<(sizeof(asAPIInfo)/sizeof(SYSBRGKM_sAPIInfo)); i++)
    {
        ui32Result = SYSBRGU_RegisterAPI(&asAPIInfo[i]);
        if(IMG_SUCCESS != ui32Result)
        {
            goto error_api_reg;
        }
    }
#ifdef VDEC_MEM_ERROR_INJECTION
    /* Register this module with the Memory Error Injector. */
    MEMERRINJ_AddModuleInfo(__this_module.module_core, __this_module.core_text_size, "vdecdd");
#endif /* VDEC_MEM_ERROR_INJECTION */
#else /* ndef SYSBRG_BRIDGING */
    bInit = IMG_TRUE;
#endif /* ndef SYSBRG_BRIDGING */

    return 0;


    /* Error handling. */
#ifdef SYSBRG_BRIDGING
error_api_reg:
    SYSDEVU_UnRegisterDevice(&null_device);
#endif /* SYSBRG_BRIDGING */

error_dev_reg_null:
    SYSDEVU_UnRegisterDevice(&vdec_device);

#ifdef SYSBRG_BRIDGING
error_dev_reg_vdec:
    SYSDEVU_VDECUnRegisterDriver(&vdec_device);

#ifdef SECURE_MEDIA_SUPPORT
error_add_sec_mem:
    SYSDEVU_VDECUnRegisterDriver(&vdec_device);
#endif /* SECURE_MEDIA_SUPPORT */
#else /* ndef SYSBRG_BRIDGING */
error_dev_reg_vdec:
    SYSDEVU_UnRegisterDriver(&vdec_device);
#endif /* ndef SYSBRG_BRIDGING */

error_reg_drv_vdec:

    return -1;
}

#ifdef SYSBRG_BRIDGING
/*!
******************************************************************************

 @Function              VDECDD_Exit

******************************************************************************/
void __exit VDECDD_Exit(IMG_VOID)
{
    IMG_UINT32 i;
#ifdef SECURE_MEDIA_SUPPORT
    SYSMEMU_RemoveMemoryHeap(vdec_device.secureMemPool);
#endif
    SYSDEVU_VDECUnRegisterDriver(&vdec_device);
    SYSDEVU_UnRegisterDevice(&vdec_device);

    SYSDEVU_UnRegisterDevice(&null_device);

    // register SYSBRG APIs.
    for (i = 0; i<(sizeof(asAPIInfo)/sizeof(SYSBRGKM_sAPIInfo)); i++)
        SYSBRGU_RemoveAPI(&asAPIInfo[i]);
}

module_init(VDECDD_Init);
module_exit(VDECDD_Exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(IMGSYSBRG_MODULE_NAME" - Imagination Technologies System Bridge Module");
MODULE_AUTHOR("Imagination Technologies Ltd");

#endif


/*!
******************************************************************************

 @Function              VDECDD_IsSupportedFeature

******************************************************************************/
IMG_RESULT VDECDD_IsSupportedFeature(
    IMG_UINT32                  ui32ConnId,
    VDEC_eFeature               eFeature,
    SYSBRG_POINTER_ARG(IMG_BOOL)pbSupported
)
{
    IMG_RESULT                  ui32Result;
    IMG_HANDLE                  hConnHandle;
    VDECDD_sDdConnContext *     psDdConnContext;
    IMG_BOOL                    bSupported = IMG_FALSE;

    FUNCTION_START;

     /* Get the connection handle from it's ID...*/
    ui32Result = DMANKM_GetConnHandleFromId(ui32ConnId, &hConnHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Get access to the device connection context...*/
    psDdConnContext = (VDECDD_sDdConnContext *)DMANKM_GetDevConnectionData(hConnHandle);
    IMG_ASSERT(psDdConnContext != IMG_NULL);

    if(psDdConnContext == IMG_NULL)
    {
        FUNCTION_END;
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Result = DECODER_IsSupportedFeature(psDdConnContext->psDdDevContext->hDecoderContext, eFeature, &bSupported);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }


    ui32Result = SYSOSKM_CopyToUser(pbSupported, &bSupported, sizeof(bSupported));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_SupportedFeatures

******************************************************************************/
IMG_RESULT VDECDD_SupportedFeatures(
    IMG_UINT32                  ui32ConnId,
    SYSBRG_POINTER_ARG(VDEC_sFeatures)  psFeatures
)
{
    IMG_RESULT                  ui32Result;
    IMG_HANDLE                  hConnHandle;
    VDECDD_sDdConnContext *     psDdConnContext;
    VDEC_sFeatures              sFeatures;

    FUNCTION_START;

    /* Get the connection handle from it's ID...*/
    ui32Result = DMANKM_GetConnHandleFromId(ui32ConnId, &hConnHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Get access to the device connection context...*/
    psDdConnContext = (VDECDD_sDdConnContext *)DMANKM_GetDevConnectionData(hConnHandle);
    IMG_ASSERT(psDdConnContext != IMG_NULL);
    if(psDdConnContext == IMG_NULL)
    {
        FUNCTION_END;
        return IMG_ERROR_INVALID_PARAMETERS;
    }
    IMG_ASSERT(psDdConnContext->psDdDevContext != IMG_NULL);
    if(psDdConnContext->psDdDevContext == IMG_NULL)
    {
        FUNCTION_END;
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    VDEC_BZERO(&sFeatures);
    ui32Result = DECODER_SupportedFeatures(psDdConnContext->psDdDevContext->hDecoderContext, &sFeatures);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    ui32Result = SYSOSKM_CopyToUser(psFeatures, &sFeatures, sizeof(sFeatures));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_GetCallbackEvent

******************************************************************************/
IMG_RESULT VDECDD_GetCallbackEvent(
    IMG_UINT32                    ui32StrId,
    SYSBRG_POINTER_ARG(VDECDD_sCallBackInfo) psCallBackInfo
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext  * psDdStrContext;
    VDECDD_sCallBackInfo  * psNextCallBackInfo;

    FUNCTION_START;

    /* Get access to stream context...*/
    ui32Result = RMAN_GetResource(ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)&psDdStrContext, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
               "[SID=0x%08X] Stream ID not valid",
               ui32StrId);
        FUNCTION_END;
        return ui32Result;
    }

    /* Get event */
    SYSOSKM_DisableInt();
    psNextCallBackInfo = LST_removeHead(&psDdStrContext->sEventCbList);
    SYSOSKM_EnableInt();

    /* While no interrupts and not preempted...*/
    while (psNextCallBackInfo == IMG_NULL &&
           !psDdStrContext->bPreempt)
    {
        /* Wait for a signal...*/
        ui32Result = SYSOSKM_WaitEventObject(psDdStrContext->hEventHandle, IMG_FALSE);
        if (ui32Result == IMG_ERROR_INTERRUPTED)
        {
            /* Not really an error..*/
            FUNCTION_END;
            return ui32Result;
        }
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            FUNCTION_END;
            return ui32Result;
        }

        SYSOSKM_DisableInt();
        psNextCallBackInfo = LST_removeHead(&psDdStrContext->sEventCbList);
        SYSOSKM_EnableInt();
    }

    /* Return the callback info. */
    if (psNextCallBackInfo != IMG_NULL)
    {
        /* Copy across the data and clear the pointers to ensure that we don't expose KM structures. */
        *((void **) psNextCallBackInfo) = IMG_NULL;
//        *psCallBackInfo = *psNextCallBackInfo;
        ui32Result = SYSOSKM_CopyToUser(psCallBackInfo, psNextCallBackInfo, sizeof(*psNextCallBackInfo));
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            FUNCTION_END;
            return ui32Result;
        }

        IMG_FREE(psNextCallBackInfo);
    }
    else
    {
        IMG_ASSERT(psDdStrContext->bPreempt);
        psDdStrContext->bPreempt = IMG_FALSE;
    }

    FUNCTION_END;
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VDECDD_PreemptCallbackEvent

******************************************************************************/
IMG_RESULT VDECDD_PreemptCallbackEvent(
    IMG_UINT32                    ui32StrId
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext  * psDdStrContext;

    FUNCTION_START;

    /* Get access to stream context...*/
    ui32Result = RMAN_GetResource(ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)&psDdStrContext, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
               "[SID=0x%08X] Stream ID not valid",
               ui32StrId);
        FUNCTION_END;
        return ui32Result;
    }

    /* Flag preemption...*/
    psDdStrContext->bPreempt = IMG_TRUE;
    SYSOSKM_SignalEventObject(psDdStrContext->hEventHandle);

    FUNCTION_END;
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamCreate

******************************************************************************/
IMG_RESULT VDECDD_StreamCreate(
    SYSBRG_POINTER_ARG(VDEC_sStrConfigData) psStrConfigData,
    SYSBRG_POINTER_ARG(IMG_VOID)            pvStrCbParam,
    SYSBRG_POINTER_ARG(IMG_UINT32)          pui32StrId
)
{
    IMG_RESULT              ui32Result;
    IMG_HANDLE              hDevHandle;
    IMG_UINT32              ui32ConnId;
    IMG_UINT32              ui32StrId;
    VDEC_sStrConfigData     sStrConfigData;
    VDECDD_sDdStrContext *  psDdStrContext;

    FUNCTION_START;
    
    ui32Result = SYSOSKM_CopyFromUser(&sStrConfigData, psStrConfigData, sizeof(sStrConfigData));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Locate the device...*/
    ui32Result = DMANKM_LocateDevice("VDEC", &hDevHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Lock the device...*/
    DMANKM_LockDeviceContext(hDevHandle);

    // Open the device which triggers a call to CORE_ConnectionCreate().
    ui32Result = DMANKM_OpenDevice(hDevHandle, DMAN_OMODE_SHARED, IMG_NULL, &ui32ConnId);

    /* Unlock the device...*/
    DMANKM_UnlockDeviceContext(hDevHandle);

    if (ui32Result != IMG_SUCCESS && ui32Result != IMG_ERROR_INTERRUPTED)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
               "DMAN open device failed (%d)", ui32Result);
        FUNCTION_END;
        return ui32Result;
    }
    IMG_ASSERT(ui32ConnId);

    /* Get core to create a stream. */
    ui32Result = CORE_StreamCreate(ui32ConnId,
                                  &sStrConfigData,
                                  SYSBRG_POINTER_FROM_USER(pvStrCbParam),
                                  &ui32StrId);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Return the stream id. */
    ui32Result = SYSOSKM_CopyToUser(pui32StrId, &ui32StrId, sizeof(ui32StrId));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    // Ensure that the stream ID refers to a valid device driver stream context.
    ui32Result = RMAN_GetResource(ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)&psDdStrContext, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    REPORT(REPORT_MODULE_VDECDD,
           REPORT_INFO,
           "[SID=0x%08X] New stream created (stream id: 0x%08X)",
           ui32StrId,
           ui32StrId);

    FUNCTION_END;
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamDestroy

******************************************************************************/
IMG_RESULT VDECDD_StreamDestroy(
    IMG_UINT32                ui32StrId
)
{
    IMG_RESULT                   ui32Result;
    IMG_HANDLE                   hDestroyedEvent;
    IMG_UINT32                   ui32ConnId;
    IMG_HANDLE                   hConnHandle;
    IMG_HANDLE                   hDevHandle;
    VDECDD_sDdStrContext       * psDdStrContext;


    FUNCTION_START;

    ui32Result = RMAN_GetResource(ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)&psDdStrContext, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Create event object. */
    ui32Result = SYSOSKM_CreateEventObject(&hDestroyedEvent);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Pass destroy on to the core...*/
    ui32Result = CORE_StreamDestroy(ui32StrId, hDestroyedEvent, &ui32ConnId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    // Wait here until the stream is actually destroyed.
    ui32Result = SYSOSKM_WaitEventObject(hDestroyedEvent, IMG_TRUE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Destroy the event object. */
    SYSOSKM_DestroyEventObject(hDestroyedEvent);

    /* Get the connection handle from it's ID...*/
    ui32Result = DMANKM_GetConnHandleFromId(ui32ConnId, &hConnHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Get the device handle...*/
    hDevHandle = DMANKM_GetDevHandleFromConn(hConnHandle);

    /* Lock the device...*/
    DMANKM_LockDeviceContext(hDevHandle);

    /* Call on to the kernel function...*/
    ui32Result = DMANKM_CloseDevice(hDevHandle, hConnHandle, DMAN_DCONN_NORMAL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS || ui32Result == IMG_ERROR_INTERRUPTED);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

// NOTE: We do not unlock the device as this will be done by
//         DMANKM_DevDisconnectComplete().
//    /* Unlock the device...*/
//    DMANKM_UnlockDeviceContext(hDevHandle);
    
    REPORT(REPORT_MODULE_VDECDD,
           REPORT_INFO,
           "[SID=0x%08X] Stream destroyed (stream id: 0x%08X)",
           ui32StrId,
           ui32StrId);

    FUNCTION_END;
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamPlay

******************************************************************************/
IMG_RESULT VDECDD_StreamPlay(
    IMG_UINT32       ui32StrId,
    VDEC_ePlayMode   ePlayMode,
    VDEC_eStopPoint  eStopPoint,
    IMG_UINT32       ui32StopPointQual
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext *  psDdStrContext;

    FUNCTION_START;

    IMG_ASSERT(ePlayMode < VDEC_PLAYMODE_MAX);
    IMG_ASSERT(eStopPoint < VDEC_STOPPOINT_MAX);
    if ((ePlayMode >= VDEC_PLAYMODE_MAX) ||
        (eStopPoint >= VDEC_STOPPOINT_MAX))
    {
        FUNCTION_END;
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Get access to stream context...*/
    ui32Result = vdecddkm_GetStreamContext(ui32StrId, &psDdStrContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* For normal decode the output has to be configured to go on. */
    if ((VDEC_PLAYMODE_NORMAL_DECODE == ePlayMode) &&
        (psDdStrContext->psDdConnContext->psDdDevContext->eDecodeLevel > VDECDD_DECODELEVEL_SCHEDULER) &&
        (!psDdStrContext->bStrOutputConfigured))
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
            "[SID=0x%08X] Stream output must be configured before playing",
            ui32StrId);
        FUNCTION_END;
        return IMG_ERROR_OPERATION_PROHIBITED;
    }

    // Validate that the software currently supports this play mode and standard.
    if (ePlayMode == VDEC_PLAYMODE_NORMAL_DECODE &&
        psDdStrContext->psDdConnContext->psDdDevContext->eDecodeLevel > VDECDD_DECODELEVEL_SCHEDULER &&
        (
#ifdef HAS_AVS
        psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_AVS       &&
#endif /* HAS_AVS */
#ifdef HAS_H264
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_H264     &&
#endif /* HAS_H264 */
#ifdef HAS_HEVC
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_HEVC     &&
#endif /* HAS_HEVC */
#ifdef HAS_MPEG4
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_MPEG4    &&
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_H263     &&
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_SORENSON &&
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_VP6      &&
#endif /* HAS_VP6 */
#ifdef HAS_VP8
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_VP8      &&
#endif /* HAS_VP8 */
#ifdef HAS_JPEG
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_JPEG     &&
 #endif /* HAS_JPEG */
#ifdef HAS_REAL
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_REAL     &&
#endif /* HAS_REAL */
#ifdef HAS_MPEG2
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_MPEG2    &&
#endif /* HAS_MPEG2 */
#ifdef HAS_VC1
         psDdStrContext->sStrConfigData.eVidStd != VDEC_STD_VC1      &&
#endif /* HAS_VC1 */
         IMG_TRUE  /* Dummy, to avoid missing && errors */
        ))
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
            "[SID=0x%08X] UNSUPPORTED[SW]: Driver cannot currently decode VIDEO STANDARD [%s]",
            ui32StrId,
            gapszVidStd[psDdStrContext->sStrConfigData.eVidStd]);
        FUNCTION_END;
        return IMG_ERROR_NOT_SUPPORTED;
    }

    /* Pass play on to the core...*/
    ui32Result = CORE_StreamPlay(ui32StrId, ePlayMode, eStopPoint, ui32StopPointQual);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamStop

******************************************************************************/
IMG_RESULT VDECDD_StreamStop(
    IMG_UINT32              ui32StrId,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual
)
{
    IMG_RESULT      ui32Result;

    FUNCTION_START;

    IMG_ASSERT(eStopPoint < VDEC_STOPPOINT_MAX);
    if (eStopPoint >= VDEC_STOPPOINT_MAX)
    {
        FUNCTION_END;
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Pass stop on to the core...*/
    ui32Result = CORE_StreamStop(ui32StrId, eStopPoint, ui32StopPointQual);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamGetStopInfo

******************************************************************************/
IMG_RESULT VDECDD_StreamGetStopInfo(
    IMG_UINT32              ui32StrId,
    SYSBRG_POINTER_ARG(VDEC_sStopInfo)  psStopInfo
)
{
    VDECDD_sDdStrContext *  psDdStrContext;
    IMG_RESULT              ui32Result;

    FUNCTION_START;

    /* Get access to stream context...*/
    ui32Result = vdecddkm_GetStreamContext(ui32StrId, &psDdStrContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    ui32Result = SYSOSKM_CopyToUser(psStopInfo, &psDdStrContext->sStopInfo, sizeof(psDdStrContext->sStopInfo));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamGetSequHdrInfo

******************************************************************************/
IMG_RESULT VDECDD_StreamGetSequHdrInfo(
    IMG_UINT32                    ui32StrId,
    SYSBRG_POINTER_ARG(VDEC_sComSequHdrInfo)    psComSequHdrInfo
)
{
    VDECDD_sDdStrContext *        psDdStrContext;
    IMG_RESULT                    ui32Result;

    FUNCTION_START;

    /* Get access to stream context...*/
    ui32Result = vdecddkm_GetStreamContext(ui32StrId, &psDdStrContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    // Obtain the common sequence header if set.
    if (VDEC_SIZE_NZ(psDdStrContext->sComSequHdrInfo.sMaxFrameSize))
    {
        ui32Result = SYSOSKM_CopyToUser(psComSequHdrInfo, &psDdStrContext->sComSequHdrInfo, sizeof(psDdStrContext->sComSequHdrInfo));
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            FUNCTION_END;
            return ui32Result;
        }
    }
    else
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
            "[SID=0x%08X] Sequence header information is not valid/available",
            ui32StrId);
        FUNCTION_END;
        return IMG_ERROR_UNEXPECTED_STATE;
    }

    FUNCTION_END;
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECDD_StreamMapBuf

******************************************************************************/
IMG_RESULT VDECDD_StreamMapBuf(
    IMG_UINT32                  		ui32StrId,
    SYSBRG_POINTER_ARG(IMG_VOID) 		pvBufCbParam,
    VDEC_eBufType              	 		eBufType,
    SYSBRG_POINTER_ARG(VDEC_sBufInfo)   psBufInfo,
    SYSBRG_POINTER_ARG(IMG_UINT32)      pui32BufMapId
)
{
    IMG_RESULT      ui32Result;
    VDEC_sBufInfo   sBufInfo;
    IMG_UINT32      ui32BufMapId;

    FUNCTION_START;

    IMG_ASSERT(eBufType < VDEC_BUFTYPE_MAX);
    if (eBufType >= VDEC_BUFTYPE_MAX)
    {
        FUNCTION_END;
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Result = SYSOSKM_CopyFromUser(&sBufInfo, psBufInfo, sizeof(sBufInfo));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Get core to map the buffer...*/
    ui32Result = CORE_StreamMapBuf(ui32StrId, SYSBRG_POINTER_FROM_USER(pvBufCbParam), eBufType, &sBufInfo, &ui32BufMapId);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Return the buffer map id. */
    ui32Result = SYSOSKM_CopyToUser(pui32BufMapId, &ui32BufMapId, sizeof(ui32BufMapId));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamUnmapBuf

******************************************************************************/
IMG_RESULT VDECDD_StreamUnmapBuf(
    IMG_UINT32              ui32BufMapId
)
{
    IMG_RESULT      ui32Result;

    FUNCTION_START;

    /* Pass request on to the core...*/
    ui32Result = CORE_StreamUnmapBuf(ui32BufMapId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamSetOutputConfig

******************************************************************************/
IMG_RESULT VDECDD_StreamSetOutputConfig(
    IMG_UINT32                      ui32StrId,
    SYSBRG_POINTER_ARG(VDEC_sStrOutputConfig)   psStrOutputConfig,
    SYSBRG_POINTER_ARG(VDEC_sPictBufConfig)     psPictBufConfig
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext *  psDdStrContext;
    VDEC_sStrOutputConfig   sStrOutputConfig;
    VDEC_sPictBufConfig     sPictBufConfig;

    FUNCTION_START;

    ui32Result = SYSOSKM_CopyFromUser(&sStrOutputConfig, psStrOutputConfig, sizeof(sStrOutputConfig));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    if (IMG_NULL != SYSBRG_POINTER_FROM_USER(psPictBufConfig))
    {
        ui32Result = SYSOSKM_CopyFromUser(&sPictBufConfig, psPictBufConfig, sizeof(sPictBufConfig));
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            FUNCTION_END;
            return ui32Result;
        }
    }

    /* Get access to stream context...*/
    ui32Result = vdecddkm_GetStreamContext(ui32StrId, &psDdStrContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    /* Check if there's any VSH available. */
    if (VDEC_SIZE_EZ(psDdStrContext->sComSequHdrInfo.sMaxFrameSize))
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
            "[SID=0x%08X] Cannot set new output configuration without valid sequence header information",
            ui32StrId);
        FUNCTION_END;
        return IMG_ERROR_UNEXPECTED_STATE;
    }

    /* Propagate the output configuration changes to other DD components. */
    ui32Result = CORE_StreamSetOutputConfig(ui32StrId, &sStrOutputConfig, &sPictBufConfig);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamFillPictBuf

******************************************************************************/
IMG_RESULT VDECDD_StreamFillPictBuf(
    IMG_UINT32  ui32BufMapId
)
{
    IMG_RESULT              ui32Result;

    FUNCTION_START;

    /* Submit buffer to the core...*/
    ui32Result = CORE_StreamFillPictBuf(ui32BufMapId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function                VDECDD_StreamFlush

******************************************************************************/
IMG_RESULT VDECDD_StreamFlush(
    IMG_UINT32                  ui32StrId,
    IMG_BOOL                    bDiscardRefs
)
{
    IMG_RESULT          ui32Result;

    FUNCTION_START;

    /* Request a stream flush to the core. */
    ui32Result = CORE_StreamFlush(ui32StrId, bDiscardRefs);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        FUNCTION_END;
        return ui32Result;
    }

    DEBUG_REPORT(REPORT_MODULE_VDECDD,
        "[SID=0x%08X] Stream FLUSHED",
        ui32StrId);

    FUNCTION_END;
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamReleaseBufs

 ******************************************************************************/
IMG_RESULT VDECDD_StreamReleaseBufs(
    IMG_UINT32                   ui32StrId,
    VDEC_eBufType                eBufType
)
{
    IMG_RESULT                    ui32Result;

    FUNCTION_START;

    IMG_ASSERT(eBufType < VDEC_BUFTYPE_MAX);
    if (eBufType >= VDEC_BUFTYPE_MAX)
    {
        FUNCTION_END;
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Result = CORE_StreamReleaseBufs(ui32StrId, eBufType);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDD_StreamSetBehaviourOnErrors

******************************************************************************/
IMG_RESULT VDECDD_StreamSetBehaviourOnErrors(
    IMG_UINT32           ui32StrId,
    VDEC_eErrorHandling  eErrorHandling
)
{
    IMG_RESULT              ui32Result;

    FUNCTION_START;

    /* Pass stream unit to the core. */
    ui32Result = CORE_StreamSetBehaviourOnErrors(ui32StrId, eErrorHandling);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
        FUNCTION_END;
        return ui32Result;
}


/*!
******************************************************************************

 @Function                VDECDD_StreamSubmitUnit

******************************************************************************/
IMG_RESULT VDECDD_StreamSubmitUnit(
    IMG_UINT32                  ui32StrId,
    SYSBRG_POINTER_ARG(VDECDD_sStrUnit) psStrUnit
)
{
    IMG_RESULT                  ui32Result;
    VDECDD_sStrUnit           * psNewStrUnit;
    VDECDD_sStrUnit             sAuxStrUnit;
    SYSBRG_POINTER_ARG(BSPP_sBitStrSeg) psBitStrSeg;
    BSPP_sBitStrSeg           * psNewBitStrSeg;

    FUNCTION_START;

    /* Allocate a "new" stream unit...*/
    VDEC_MALLOC(psNewStrUnit);
    IMG_ASSERT(psNewStrUnit != IMG_NULL);
    if (psNewStrUnit == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "[SID=0x%08X] Failed to allocate memory for stream unit structure in KM",
            ui32StrId);
        FUNCTION_END;
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psNewStrUnit);

    /* Take copy of stream unit */
    ui32Result = SYSOSKM_CopyFromUser(&sAuxStrUnit, psStrUnit, sizeof(sAuxStrUnit));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Setup the new stream unit based on the auxiliary stream unit contents. */
    IMG_MEMCPY(psNewStrUnit, &sAuxStrUnit, sizeof(sAuxStrUnit));
    psNewStrUnit->psSequHdrInfo = IMG_NULL;
    psNewStrUnit->psPictHdrInfo = IMG_NULL;
    LST_init(&psNewStrUnit->sBitStrSegList);

    /* If sequence header...*/
    if (sAuxStrUnit.psSequHdrInfo != IMG_NULL)
    {
        SYSBRG_POINTER_ARG(BSPP_sSequHdrInfo) psUmSequHdrInfo;
#ifdef SYSBRG_BRIDGING
        psUmSequHdrInfo = make_sysbrg_pointer_from_ptr(sAuxStrUnit.psSequHdrInfo);
#else
        psUmSequHdrInfo = sAuxStrUnit.psSequHdrInfo;
#endif

        /* Allocate a "new" sequence header...*/
        VDEC_MALLOC(psNewStrUnit->psSequHdrInfo);
        IMG_ASSERT(psNewStrUnit->psSequHdrInfo != IMG_NULL);
        if (psNewStrUnit->psSequHdrInfo == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "[SID=0x%08X] Failed to allocate memory for sequence header information structure in KM",
                ui32StrId);
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto error;
        }

        /* Take a copy of the sequence header. */
        ui32Result = SYSOSKM_CopyFromUser(psNewStrUnit->psSequHdrInfo, psUmSequHdrInfo, sizeof(*psNewStrUnit->psSequHdrInfo));
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        /* Set the reference count. */
        psNewStrUnit->psSequHdrInfo->ui32RefCount = 1;
    }

    /* If picture header...*/
    if (sAuxStrUnit.psPictHdrInfo != IMG_NULL)
    {
        SYSBRG_POINTER_ARG(BSPP_sPictHdrInfo) psUmPictHdrInfo;
#ifdef SYSBRG_BRIDGING
        psUmPictHdrInfo = make_sysbrg_pointer_from_ptr(sAuxStrUnit.psPictHdrInfo);
#else
        psUmPictHdrInfo = sAuxStrUnit.psPictHdrInfo;
#endif

        /* Allocate a "new" picture header...*/
        VDEC_MALLOC(psNewStrUnit->psPictHdrInfo);
        IMG_ASSERT(psNewStrUnit->psPictHdrInfo != IMG_NULL);
        if (psNewStrUnit->psPictHdrInfo == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "[SID=0x%08X] Failed to allocate memory for picture header information structure in KM",
                ui32StrId);
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto error;
        }

        /* Take a copy of the picture header. */
        ui32Result = SYSOSKM_CopyFromUser(psNewStrUnit->psPictHdrInfo, psUmPictHdrInfo, sizeof(*psNewStrUnit->psPictHdrInfo));
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            psNewStrUnit->psPictHdrInfo->sPictSgmData.ui32Id = BSPP_INVALID;
            psNewStrUnit->psPictHdrInfo->sPictSgmData.pvData = IMG_NULL;
            goto error;
        }

        /* Copy the SGM data. */
        if (psNewStrUnit->psPictHdrInfo->sPictSgmData.ui32Id != BSPP_INVALID)
        {
            /* Get pointer to user mode data */
            SYSBRG_POINTER_ARG(IMG_VOID) pvUmData = (SYSBRG_POINTER_ARG(IMG_VOID))psNewStrUnit->psPictHdrInfo->sPictSgmData.pvData;
            BSPP_sPictData *  psPictData = &psNewStrUnit->psPictHdrInfo->sPictSgmData;

            /* Allocate "new" data buffer ...*/
            psPictData->pvData = IMG_MALLOC(psPictData->ui32Size);
            IMG_ASSERT(psPictData->pvData != IMG_NULL);
            if (psPictData->pvData == IMG_NULL)
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "Failed to allocate memory for picture data in KM");
                ui32Result = IMG_ERROR_OUT_OF_MEMORY;
                goto error;
            }

            /* Take a copy of the data buffer. */
            ui32Result = SYSOSKM_CopyFromUser(psPictData->pvData,
                                              pvUmData,
                                              psPictData->ui32Size);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "[SID=0x%08X] Failed to copy memory for picture data in KM",
                    ui32StrId);
                goto error;
            }
        }
    }

    /* Create copies of the bit stream segments...*/
    psBitStrSeg = (SYSBRG_POINTER_ARG(BSPP_sBitStrSeg))LST_first(&sAuxStrUnit.sBitStrSegList);
    while (IMG_NULL != SYSBRG_POINTER_FROM_USER(psBitStrSeg))
    {
        /* Allocate a "new" new bit stream segment...*/
        VDEC_MALLOC(psNewBitStrSeg);
        IMG_ASSERT(psNewBitStrSeg != IMG_NULL);
        if (psNewBitStrSeg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "[SID=0x%08X] Failed to allocate memory for bitstream segment in KM",
                ui32StrId);
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto error;
        }

        /* Take copy of bit stream segment */
        ui32Result = SYSOSKM_CopyFromUser(psNewBitStrSeg, psBitStrSeg, sizeof(*psNewBitStrSeg));
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            IMG_FREE(psNewBitStrSeg);
            goto error;
        }

        /* Invalidate the UM buffer mapping information pointer. */
        // IMG_ASSERT(psNewBitStrSeg->psBufMapInfo->eBufType == VDEC_BUFTYPE_BITSTREAM);
        // psNewBitStrSeg->psBufMapInfo = IMG_NULL;

        /* Get next bit stream segment (from um list). */
        psBitStrSeg = (SYSBRG_POINTER_ARG(BSPP_sBitStrSeg))LST_next(psNewBitStrSeg);

        /* Add segment to the list in the new descriptor. */
        LST_add(&psNewStrUnit->sBitStrSegList, psNewBitStrSeg);
    }

    /* Pass stream unit to the core. */
    ui32Result = CORE_StreamSubmitUnit(ui32StrId, psNewStrUnit);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    DEBUG_REPORT(REPORT_MODULE_VDECDD,
                 "[SID=0x%08X] Unit SUBMITTED",
                 ui32StrId);

    FUNCTION_END;
    return IMG_SUCCESS;

    /* Roll back in case of errors. */
error:
    VDECDDUTILS_FreeStrUnit(psNewStrUnit);

    FUNCTION_END;
    return ui32Result;
}


/*!
******************************************************************************

 @Function                VDECDD_StreamGetStatus

******************************************************************************/
IMG_RESULT VDECDD_StreamGetStatus(
    IMG_UINT32                  ui32StrId,
    SYSBRG_POINTER_ARG(VDECDD_sStrStatus)   psStrStatus
)
{
    IMG_RESULT           ui32Result = IMG_SUCCESS;
    VDECDD_sStrStatus  * psIntStrStatus;

    FUNCTION_START;

    /* Allocate a stream status since it is too large to go on the stack. */
    VDEC_MALLOC(psIntStrStatus);
    IMG_ASSERT(psIntStrStatus);
    if (!psIntStrStatus)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
               "[SID=0x%08X] Failed to allocate memory for stream status",
               ui32StrId);
        FUNCTION_END;
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Pass stream unit to the core. */
    ui32Result = CORE_StreamGetStatus(ui32StrId, psIntStrStatus);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    if (IMG_SUCCESS == ui32Result)
    {
        /* Copy to user space */
        ui32Result = SYSOSKM_CopyToUser(psStrStatus, psIntStrStatus, sizeof(*psIntStrStatus));
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    IMG_FREE(psIntStrStatus);

    FUNCTION_END;
    return ui32Result;
}


