/*!
 *****************************************************************************
 *
 * @File       sysbrg_utils.c
 * @Description    This file contains the System Bridge Kernel Mode Utilities API.
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

#ifdef SYSBRG_BRIDGING
#define __SYS_BRIDGE_APIS__
#include <system.h>
#endif /* SYSBRG_BRIDGING */

#ifdef WIN32
    #ifndef WINCE
    //Win32 Only
        #define DEBUGMSG //Only supported in WinCE
        #ifdef UNICODE
            #define TEXT(t) L##t
            #define _T(t) L##t
            #define T(t) L##t
        #else
            #define TEXT(t) t
            #define _T(t) t
            #define T(t) t
        #endif
    #endif
#endif

#include "sysbrg_utils.h"
#include "sysos_api_km.h"
#include "report_api.h"

#ifdef IMG_KERNEL_MODULE
#include <linux/module.h>
#endif

IMG_BOOL    gSysBrgInitialised = IMG_FALSE;        /*!< Indicates where the API has been initialised    */

/*!
******************************************************************************
 This structure contains the "process lost" callback information.
******************************************************************************/
typedef struct
{
    LST_LINK;                  /*!< List link (allows the structure to be part of a MeOS list).*/
    IMG_HANDLE                 hProcessId;        //!< Process id.
    SYSBRGKM_pfnProcessLostCb  pfnProcessLostCb;  //!< Process lost callback function.
    IMG_VOID *                 pvParam;           //!< Callback parameter.

} SYSBRG_sProcLostCb;

static LST_T  gsProcLostCbList;   //!< List of active process lost callbacks

static LST_T  gsMappableRegList;  //!< List of active mappable regions

static LST_T  gsKernelAPIList;    //!< List of registered APIs

#ifdef SYSBRG_BRIDGING
#include "dman_api_rpc.h"
#include "dbgopt_api_rpc.h"
#include "wrap_utils_rpc.h"


#include "page_alloc_rpc.h"


static SYSBRGKM_sAPIInfo asAPIInfo[] = {
    		SYS_BRIDGE(DBGOPTBRG)	\
    		SYS_BRIDGE(DMAN)		\
			SYS_BRIDGE(WRAPU)		\
    		SYS_BRIDGE(PALLOC) };


#endif


/*!
******************************************************************************

 @Function              SYSBRGU_GetAPI

******************************************************************************/
IMG_BOOL SYSBRGU_GetAPI(
    IMG_UINT32            ui32APIId,
    SYSBRGKM_sAPIInfo **  ppslAPIInfo)
{
    SYSBRGKM_sAPIInfo *  psTmpKernelAPIInfo;

    psTmpKernelAPIInfo = (SYSBRGKM_sAPIInfo *) LST_first(&gsKernelAPIList);

    while (
           (psTmpKernelAPIInfo != IMG_NULL) &&
           (psTmpKernelAPIInfo->ui32APIId != ui32APIId)
          )
    {
        psTmpKernelAPIInfo = (SYSBRGKM_sAPIInfo *) LST_next(psTmpKernelAPIInfo);
    }

    if (psTmpKernelAPIInfo && (psTmpKernelAPIInfo->ui32APIId == ui32APIId))
    {
        *ppslAPIInfo = psTmpKernelAPIInfo;
        return IMG_TRUE;
    }

    return IMG_FALSE;
}


/*!
******************************************************************************

 @Function              SYSBRGU_RegisterAPI

******************************************************************************/
IMG_RESULT SYSBRGU_RegisterAPI (
    SYSBRGKM_sAPIInfo *  psKernelAPIInfo
)
{
    IMG_BOOL             bFoundInList;
    SYSBRGKM_sAPIInfo *  psTmpKernelAPIInfo;

    /* If the info structure is null...*/
    IMG_ASSERT(psKernelAPIInfo != IMG_NULL);
    if (psKernelAPIInfo == IMG_NULL)
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }

    /* Check the API has not already been registered...*/
    bFoundInList = SYSBRGU_GetAPI(psKernelAPIInfo->ui32APIId, &psTmpKernelAPIInfo);
    IMG_ASSERT(!bFoundInList);
    if (bFoundInList)
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }

    /* Add to list....*/
    LST_add(&gsKernelAPIList, psKernelAPIInfo);

    /* Return success...*/
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSBRGU_RegisterAPI)


/*!
******************************************************************************

 @Function              SYSBRGU_RegisterAPI

******************************************************************************/
IMG_RESULT SYSBRGU_RemoveAPI (
    SYSBRGKM_sAPIInfo *  psKernelAPIInfo
)
{
    return LST_remove(&gsKernelAPIList, psKernelAPIInfo) ? IMG_SUCCESS : IMG_ERROR_GENERIC_FAILURE;
}
IMGVIDEO_EXPORT_SYMBOL(SYSBRGU_RemoveAPI)




/*!
******************************************************************************

 @Function                SYSBRGU_MakeProcessLostCb

******************************************************************************/
IMG_VOID SYSBRGU_MakeProcessLostCb(
    IMG_HANDLE  hProcessId
)
{
    SYSBRG_sProcLostCb *  psProcLostCb;

    /* Loop over the registered callbacks looking for callbacks registered for
       this process...*/
    SYSOSKM_DisableInt();
    psProcLostCb = (SYSBRG_sProcLostCb *)LST_first(&gsProcLostCbList);
    while (psProcLostCb != IMG_NULL)
    {
        /* This processes?...*/
        if (psProcLostCb->hProcessId == hProcessId)
        {
            /* Yes, re-enable interrupts...*/
            SYSOSKM_EnableInt();

            /* Call the process lost callback - we assume that this WILL
               removed the callback using SYSBRGKM_RemoveProcessLostCb()...*/
            psProcLostCb->pfnProcessLostCb(psProcLostCb->pvParam);

            /* Start again...*/
            SYSOSKM_DisableInt();
            psProcLostCb = (SYSBRG_sProcLostCb *)LST_first(&gsProcLostCbList);
        }
        else
        {
            /* Move to the next callback...*/
            psProcLostCb = (SYSBRG_sProcLostCb *)LST_next(psProcLostCb);
        }
    }
    SYSOSKM_EnableInt();
}


/*!
******************************************************************************

 @Function                SYSBRGU_Initialise

******************************************************************************/
IMG_RESULT SYSBRGU_Initialise(IMG_VOID)
{

    /* If we are not initialised....*/
    if (!gSysBrgInitialised)
    {

        /* Initialise the active lists...*/
        LST_init(&gsProcLostCbList);
        LST_init(&gsMappableRegList);
        LST_init(&gsKernelAPIList);

#if defined(SYSBRG_BRIDGING)
        {
			IMG_UINT32 i;
			for(i = 0; i < sizeof(asAPIInfo) / sizeof(asAPIInfo[0]);i++)
				SYSBRGU_RegisterAPI(&asAPIInfo[i]);
        }
#endif

        /* Now we are initilaised...*/
        gSysBrgInitialised = IMG_TRUE;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                SYSBRGU_Deinitialise

******************************************************************************/
IMG_VOID SYSBRGU_Deinitialise(IMG_VOID)
{
    /* If initialised...*/
    if (gSysBrgInitialised)
    {
        /* Ensure that the dynamic lists are empty...*/
        IMG_ASSERT(LST_first(&gsProcLostCbList) == IMG_NULL);
        IMG_ASSERT(LST_first(&gsMappableRegList) == IMG_NULL);

        /* We are no nolonger initialised...*/
        gSysBrgInitialised = IMG_FALSE;
    }
}


/*!
******************************************************************************

 @Function                SYSBRGU_RegisterProcessLostCb

******************************************************************************/
IMG_RESULT SYSBRGU_RegisterProcessLostCb(
    SYSBRGKM_pfnProcessLostCb  pfnProcessLostCb,
    IMG_VOID *                 pvParam,
    IMG_HANDLE *               phProcLostCbHandle
)
{
    SYSBRG_sProcLostCb *  psProcLostCb;

    IMG_ASSERT(gSysBrgInitialised);

    /* Allocate a process lost structure...*/
    psProcLostCb = IMG_MALLOC(sizeof(*psProcLostCb));
    IMG_ASSERT(psProcLostCb != IMG_NULL);
    if (psProcLostCb == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psProcLostCb, 0, sizeof(*psProcLostCb));

    /* Fill in the process lost structure...*/
    psProcLostCb->hProcessId        = SYSOSKM_GetProcessId();
    psProcLostCb->pfnProcessLostCb    = pfnProcessLostCb;
    psProcLostCb->pvParam            = pvParam;


    /* Add to active process lost list...*/
    SYSOSKM_DisableInt();
    LST_add(&gsProcLostCbList, psProcLostCb);
    SYSOSKM_EnableInt();

    *phProcLostCbHandle = psProcLostCb;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                SYSBRGU_RemoveProcessLostCb

******************************************************************************/
IMG_VOID SYSBRGU_RemoveProcessLostCb(
    IMG_HANDLE  hProcLostCbHandle
)
{
    SYSBRG_sProcLostCb *  psProcLostCb = (SYSBRG_sProcLostCb *)hProcLostCbHandle;

    IMG_ASSERT(gSysBrgInitialised);

    /* Remove to active process lost list...*/
    SYSOSKM_DisableInt();
    LST_remove(&gsProcLostCbList, psProcLostCb);
    SYSOSKM_EnableInt();

    IMG_FREE(psProcLostCb);
}


/*!
******************************************************************************

 @Function                SYSBRGU_CreateMappableRegion

******************************************************************************/
IMG_RESULT SYSBRGU_CreateMappableRegion(
    IMG_PHYSADDR    paCpuPhysAddr,
    IMG_UINT32      ui32Size,
    SYS_eMemAttrib  eMemAttrib,
    SYSMEMU_sPages *pSysMem,
    IMG_HANDLE *    phRegHandle
)
{
    SYSBRGU_sMappableReg *  psMappableReg;

    IMG_ASSERT(gSysBrgInitialised);

    DEBUG_REPORT(REPORT_MODULE_SYSBRG, "%s registering size %u phys 0x%llx",
           __FUNCTION__, ui32Size, paCpuPhysAddr);

    /* Allocate a mappable region structure...*/
    psMappableReg = IMG_MALLOC(sizeof(*psMappableReg));
    IMG_ASSERT(psMappableReg != IMG_NULL);
    if (psMappableReg == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psMappableReg, 0, sizeof(*psMappableReg));

    /* Fill in the mappable region structure...*/
    psMappableReg->hProcessId     = SYSOSKM_GetProcessId();
    psMappableReg->paCpuPhysAddr  = paCpuPhysAddr;
    psMappableReg->ui32Size       = ui32Size;
    psMappableReg->eMemAttrib     = eMemAttrib;
    psMappableReg->pSysMem        = pSysMem;

    /* Add to active process lost list...*/
    SYSOSKM_DisableInt();
    LST_add(&gsMappableRegList, psMappableReg);
    SYSOSKM_EnableInt();

    *phRegHandle = psMappableReg;

    /* Return success...*/
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSBRGU_CreateMappableRegion)

/*!
******************************************************************************

 @Function                SYSBRGU_DestroyMappableRegion

******************************************************************************/
IMG_VOID SYSBRGU_DestroyMappableRegion(
    IMG_HANDLE  hRegHandle
)
{
    SYSBRGU_sMappableReg *  psMappableReg = (SYSBRGU_sMappableReg *)hRegHandle;

    IMG_ASSERT(gSysBrgInitialised);

    /* Remove to active list...*/
    SYSOSKM_DisableInt();
    LST_remove(&gsMappableRegList, psMappableReg);
    SYSOSKM_EnableInt();

    IMG_FREE(psMappableReg);
}
IMGVIDEO_EXPORT_SYMBOL(SYSBRGU_DestroyMappableRegion)


/*!
******************************************************************************

 @Function                SYSBRGU_GetMappableRegion

******************************************************************************/
SYSBRGU_sMappableReg * SYSBRGU_GetMappableRegion(
    IMG_PHYSADDR  paCpuPhysAddr
)
{
    SYSBRGU_sMappableReg *  psMappableReg;
    IMG_HANDLE              hProcessId = SYSOSKM_GetProcessId();

    IMG_ASSERT(gSysBrgInitialised);

    /* Locate the mappable regions from the process ID and kernel mode address...*/
    SYSOSKM_DisableInt();
    psMappableReg = (SYSBRGU_sMappableReg *)LST_first(&gsMappableRegList);
    while (
           (psMappableReg != IMG_NULL) &&
           (
            (psMappableReg->hProcessId != hProcessId) ||
            (psMappableReg->paCpuPhysAddr != paCpuPhysAddr)
           )
          )
    {
        psMappableReg = (SYSBRGU_sMappableReg *)LST_next(psMappableReg);
    }
    SYSOSKM_EnableInt();

    /* Return the mappable region...*/
    return psMappableReg;
}

/*!
******************************************************************************

 @Function                SYSBRGU_ClearAllMappableRegions

******************************************************************************/
IMG_VOID SYSBRGU_ClearAllMappableRegions(
    IMG_VOID
)
{
    SYSBRGU_sMappableReg *  psMappableReg;
    SYSBRGU_sMappableReg *  psNext;

    psMappableReg = (SYSBRGU_sMappableReg *)LST_first(&gsMappableRegList);
    while(psMappableReg) {
        psNext = (SYSBRGU_sMappableReg *)LST_next(psMappableReg);
        LST_remove(&gsMappableRegList, psMappableReg);
        IMG_FREE(psMappableReg);
        psMappableReg = psNext;
    }
}
