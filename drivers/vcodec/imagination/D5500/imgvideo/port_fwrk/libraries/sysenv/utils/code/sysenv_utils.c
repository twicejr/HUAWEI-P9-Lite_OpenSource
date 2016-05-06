/*!
 *****************************************************************************
 *
 * @File       sysenv_utils.c
 * @Description    This file contains the System Kernel Mode Utilities API.
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

#include "sysenv_utils.h"
#include "sysenv_api_km.h"
#include "sysdev_utils.h"
#include "sysmem_utils.h"
#include "sysos_api_km.h"
#include "sysbrg_api_km.h"
#include "sysbrg_utils.h"
#include "dman_api_km.h"
#include "rman_api.h"
#include "pman_api.h"
#include "dbgopt_api_km.h"
#include "page_alloc_km.h"


#ifndef IMG_KERNEL_MODULE
    #include "tal_setup.h"
#endif

#ifdef FW_PERFORMANCE_LOGGING
#include "perflog_api.h"
#endif

IMG_BOOL    gSysEnvInitialised = IMG_FALSE;        /*!< Indicates where the API has been initialised    */

#if defined (IMG_CHECK_MEMORY_LEAKS)
IMG_ATOMIC    gsStrDupCnt = ATOMIC_INIT(0);    //!< Count of IMG_STRDUP's
IMG_ATOMIC    gsMallocCnt = ATOMIC_INIT(0);    //!< Count of IMG_MALLOC's
IMG_ATOMIC    gsFreeCnt   = ATOMIC_INIT(0);    //!< Count of IMG_FREE's
#endif

/*!
******************************************************************************

 @Function                SYSENVU_Initialise

******************************************************************************/
IMG_RESULT SYSENVU_Initialise(IMG_VOID)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    /* If not initialised...*/
    if (!gSysEnvInitialised)
    {
        /* Initialise the Debug Options...*/
        ui32Result = DBGOPTKM_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto out;
        }

        /* Initialise the Process Manager...*/
        ui32Result = PMAN_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto dbgopt_deinit;
        }

        /* Initialise the OS component...*/
        ui32Result = SYSOSKM_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto pman_deinit;
        }

        /* Initialise the bridged APIs...*/
        ui32Result = SYSBRGKM_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto sysos_deinit;
        }

        /* Initialise the device component...*/
        ui32Result = SYSDEVU_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto sysbrg_deinit;
        }

        /* Initialise the memory component...*/
        ui32Result = SYSMEMU_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto sysdev_deinit;
        }

        /* Initialise the Resource Manager...*/
        ui32Result = RMAN_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto sysmem_deinit;
        }

        /* Initialise the Device Manager...*/
        ui32Result = DMANKM_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto rman_deinit;
        }

#ifndef IMG_KERNEL_MODULE
        TALSETUP_Initialise();
#endif

        PALLOCKM_Initialise();

#ifdef FW_PERFORMANCE_LOGGING
        /* Initialise the Performance Logger...*/
        ui32Result = PERFLOG_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto tal_deinit;
        }
#endif


        /* Now we are initialised...*/
        gSysEnvInitialised = IMG_TRUE;
    }

out:
    /* Return success...*/
    return ui32Result;
#ifdef FW_PERFORMANCE_LOGGING
tal_deinit:
    TALSETUP_Deinitialise();
#endif

    DMANKM_Deinitialise();

rman_deinit:
    RMAN_Deinitialise();

sysmem_deinit:
    SYSMEMU_Deinitialise();

sysdev_deinit:
    SYSDEVU_Deinitialise();

sysbrg_deinit:
    SYSBRGKM_Deinitialise();

sysos_deinit:
    SYSOSKM_Deinitialise();

pman_deinit:
    PMAN_Deinitialise();

dbgopt_deinit:
    DBGOPTKM_Deinitialise();
    goto out;
}


/*!
******************************************************************************

 @Function                SYSENVU_Deinitialise

******************************************************************************/
IMG_VOID SYSENVU_Deinitialise(IMG_VOID)
{
    if (gSysEnvInitialised)
    {
    	PALLOCKM_Deinitialise();

#ifndef WINCE
    #ifndef IMG_KERNEL_MODULE
        /* If not kernel mode....*/

        /* Fake process termination...*/
        {
            IMG_HANDLE                hProcessId;

            hProcessId= SYSOSKM_GetProcessId();
            SYSBRGU_MakeProcessLostCb(hProcessId);
        }
    #endif
#else
    #ifndef SYSBRG_BRIDGING
    #endif /* not SYSBRG_BRIDGING */
        /* Fake process termination...*/
        {
            IMG_HANDLE                hProcessId;

            hProcessId= SYSOSKM_GetProcessId();
            SYSBRGU_MakeProcessLostCb(hProcessId);
        }

#endif

#ifndef IMG_KERNEL_MODULE
        /* Deinitialise the TAL...*/
        TALSETUP_Deinitialise();
#endif

        /* Deinitialise the Debug Options...*/
        DBGOPTKM_Deinitialise();

        /* Deinitialise the Process Manager...*/
        PMAN_Deinitialise();

        /* Deinitialise the Device Manager...*/
        DMANKM_Deinitialise();

        /* Deinitialise the Resource Manager...*/
        RMAN_Deinitialise();

        /* Deinitialise the memory component...*/
        SYSMEMU_Deinitialise();

        /* Deinitialise the device component...*/
        SYSDEVU_Deinitialise();

        /* Deinitialise the OS component...*/
        SYSOSKM_Deinitialise();

#ifdef FW_PERFORMANCE_LOGGING
        /* Deinitialise the performance logger...*/
        PERFLOG_Deinitialise();
#endif

        /* Clear all allocated mappable regions.  */
        SYSBRGU_ClearAllMappableRegions();
#if defined (IMG_CHECK_MEMORY_LEAKS)
#if 0
        printk(KERN_INFO "gsStrDupCnt:%d\n", gsStrDupCnt);
        printk(KERN_INFO "gsMallocCnt:%d\n", gsMallocCnt);
        printk(KERN_INFO "gsFreeCnt:%d\n", gsFreeCnt);
#endif

        IMG_ASSERT(atomic_read(&gsStrDupCnt) + atomic_read(&gsMallocCnt) == atomic_read(&gsFreeCnt));
#endif
        /* Now we are deinitialised...*/
        gSysEnvInitialised = IMG_FALSE;
    }
}
