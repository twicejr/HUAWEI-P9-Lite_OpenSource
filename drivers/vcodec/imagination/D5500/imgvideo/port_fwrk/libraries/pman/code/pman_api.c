/*!
 *****************************************************************************
 *
 * @File       pman_api.c
 * @Title      The Process Manager API.
 * @Description    This file contains the implementation of the Process Manager API.
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

#include <pman_api.h>
#include <rman_api.h>
#include <sysos_api_km.h>
#include <sysbrg_api_km.h>


static IMG_BOOL    gbPmanInitialised = IMG_FALSE;        /*!< Indicates where the API has been initialised    */

typedef struct PMAN_tag_sProcContext        PMAN_sProcContext;

/*!
******************************************************************************
 This structure contains the "process lost" callback information.
******************************************************************************/
typedef struct
{
    LST_LINK;              /*!< List link (allows the structure to be part of a MeOS list).*/
    PMAN_sProcContext *    psProcContext;     //!< Pointer to PMAN_sProcContext structure.
    PMAN_pfnProcessLostCb  pfnProcessLostCb;  //!< Process lost callback function.
    IMG_VOID *             pvParam;           //!< Callback parameter

} PMAN_sProcLostCb;

/*!
******************************************************************************
 This structure contains the process context.
******************************************************************************/
struct PMAN_tag_sProcContext
{
    LST_LINK;   /*!< List link (allows the structure to be part of a MeOS list).*/
    IMG_HANDLE  hProcessId;         //!< Process id.
    IMG_HANDLE  hResBHandle;        //!< Process resource bucket
    IMG_HANDLE  hProcLostCbHandle;  //!< Process lost callback handle
    LST_T       sProcLostCbList;    //!< List of PMAN_sProcLostCb structures
    IMG_UINT32  ui32CntConn;        //!< Count of connections.
    IMG_BOOL    bProcessLostCb;     //!< IMG_TRUE when pman_fnProcessLostCb() has been call so process has terminated
    IMG_BOOL    bSyncDisconnect;    //!< IMG_TRUE if synchronous call to PMAN_DevDisconnectComplete() from callback

};

static LST_T  gsProcList;  //!< List of PMAN_sProcContext structures


/*!
******************************************************************************

 @Function                PMAN_Initialise

******************************************************************************/
IMG_RESULT PMAN_Initialise(IMG_VOID)
{
    /* If we are not initialised....*/
    if (!gbPmanInitialised)
    {
        /* Initialise the active lists...*/
        LST_init(&gsProcList);

        /* Now we are initialised...*/
        gbPmanInitialised = IMG_TRUE;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                PMAN_Deinitialise

******************************************************************************/
IMG_VOID PMAN_Deinitialise(IMG_VOID)
{
    /* If initialised...*/
    if (gbPmanInitialised)
    {
        /* Ensure that the process list is empty...*/
        IMG_ASSERT(LST_first(&gsProcList) == IMG_NULL);

        /* We are no no longer initialised...*/
        gbPmanInitialised = IMG_FALSE;
    }
}


/*!
******************************************************************************

 @Function              pman_FreeProcContext

******************************************************************************/
static IMG_VOID pman_FreeProcContext (
    PMAN_sProcContext *  psProcContext
)
{
    /* Remove this from the list, destroy the resource bucket and structure...*/
    LST_remove(&gsProcList, psProcContext);
    RMAN_DestroyBucket(psProcContext->hResBHandle);
    IMG_FREE(psProcContext);
}

/*!
******************************************************************************

 @Function              pman_fnProcessLostCb

******************************************************************************/
static IMG_VOID pman_fnProcessLostCb (
    IMG_VOID *  pvParam
)
{
    PMAN_sProcContext *  psProcContext = (PMAN_sProcContext *) pvParam;
    PMAN_sProcLostCb *   psProcLostCb;

    /* Remove the callback from the SYSBRG component...*/
    SYSBRGKM_RemoveProcessLostCb(psProcContext->hProcLostCbHandle);

    /* Loop over the registered callbacks looking for callbacks registered for this process...*/
    SYSOSKM_DisableInt();
    psProcContext->bProcessLostCb  = IMG_TRUE;
    psProcContext->bSyncDisconnect = IMG_TRUE;
    psProcLostCb = (PMAN_sProcLostCb *)LST_first(&psProcContext->sProcLostCbList);
    while (psProcLostCb != IMG_NULL)
    {
        /* Re-enable interrupts...*/
        SYSOSKM_EnableInt();

        /* Call the process lost callback - we assume that this WILL
         * removed the callback using PMAN_RemoveProcessLostCb()...*/
        psProcLostCb->pfnProcessLostCb(psProcLostCb->pvParam);

        /* Start again...*/
        SYSOSKM_DisableInt();
        psProcLostCb = (PMAN_sProcLostCb *)LST_first(&psProcContext->sProcLostCbList);
    }
    psProcContext->bSyncDisconnect = IMG_FALSE;

    /* If no more connections...*/
    if (psProcContext->ui32CntConn == 0)
    {
        /* Free the process context...*/
        pman_FreeProcContext(psProcContext);
    }

    SYSOSKM_EnableInt();
}


/*!
******************************************************************************

 @Function              PMAN_DevDisconnectComplete

******************************************************************************/
IMG_VOID PMAN_DevDisconnectComplete(
    IMG_HANDLE  hProcessId
)
{
    PMAN_sProcContext *  psProcContext;

    /* Locate process context structure...*/
    SYSOSKM_DisableInt();
    psProcContext = (PMAN_sProcContext *)LST_first(&gsProcList);
    while (
            (psProcContext != IMG_NULL) &&
            (psProcContext->hProcessId != hProcessId)
            )
    {
        psProcContext = (PMAN_sProcContext *)LST_next(psProcContext);
    }
    SYSOSKM_EnableInt();

    /* Did we find a process context structure - we should...*/
    if(psProcContext == IMG_NULL)
    {
        IMG_ASSERT(psProcContext != IMG_NULL);
    }
    else if(psProcContext->ui32CntConn == 0)
    {
        IMG_ASSERT(psProcContext->ui32CntConn > 0);
    }
    else
    {
        SYSOSKM_DisableInt();
        psProcContext->ui32CntConn--;
        SYSOSKM_EnableInt();
        
        /* If no more connections, the process has been lost and this is an asynchronous diconnect...*/
        if (
            (psProcContext->ui32CntConn == 0) &&
            (psProcContext->bProcessLostCb) &&
            (!psProcContext->bSyncDisconnect)
            )
        {
            /* Free the process context...*/
            pman_FreeProcContext(psProcContext);
        }
    }
}


/*!
******************************************************************************

 @Function              PMAN_GetProcResBucket

 ******************************************************************************/
IMG_RESULT PMAN_GetProcResBucket(
    IMG_HANDLE    hProcessId,
    IMG_HANDLE *  phResBHandle
)
{
    PMAN_sProcContext *  psProcContext;
    IMG_UINT32           ui32Result;

    IMG_ASSERT(gbPmanInitialised);

    /* Locate process context structure...*/
    SYSOSKM_DisableInt();
    psProcContext = (PMAN_sProcContext *)LST_first(&gsProcList);
    while (
            (psProcContext != IMG_NULL) &&
            (psProcContext->hProcessId != hProcessId)
            )
    {
        psProcContext = (PMAN_sProcContext *)LST_next(psProcContext);
    }
    SYSOSKM_EnableInt();

    /* Did we find a process context structure...*/
    if (psProcContext == IMG_NULL)
    {
        /* No, create one...*/
        psProcContext = IMG_MALLOC(sizeof(*psProcContext));
        IMG_ASSERT(psProcContext != IMG_NULL);
        if (psProcContext == IMG_NULL)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        IMG_MEMSET(psProcContext, 0, sizeof(*psProcContext));

        /* Set process id and create a bucket for process resources...*/
        psProcContext->hProcessId = hProcessId;
        ui32Result = RMAN_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_rman_init;
        }

        ui32Result = RMAN_CreateBucket(&psProcContext->hResBHandle);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_create_bucket;
        }
        /* Initialise the active lists...*/
        LST_init(&psProcContext->sProcLostCbList);

        /* Add to list of process contexts...*/
        SYSOSKM_DisableInt();
        LST_add(&gsProcList, psProcContext);
        SYSOSKM_EnableInt();

        /* Register a callback with the SYSBRG component - to be called if the process dies...*/
        ui32Result = SYSBRGKM_Initialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_sysbrg_init;
        }

        ui32Result = SYSBRGKM_RegisterProcessLostCb(pman_fnProcessLostCb, psProcContext, &psProcContext->hProcLostCbHandle);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_register_cb;
        }
    }

    /* Did we find a process context structure...*/
    IMG_ASSERT(psProcContext != IMG_NULL);

    *phResBHandle =  psProcContext->hResBHandle;

    return IMG_SUCCESS;

    /* Error handling. */
error_register_cb:
error_sysbrg_init:
    SYSOSKM_DisableInt();
    LST_remove(&gsProcList, psProcContext);
    SYSOSKM_EnableInt();
    RMAN_DestroyBucket(psProcContext->hResBHandle);
error_create_bucket:
error_rman_init:
    IMG_FREE(psProcContext);

    return ui32Result;
}


/*!
******************************************************************************

 @Function                PMAN_RegisterProcessLostCb

******************************************************************************/
IMG_RESULT PMAN_RegisterProcessLostCb(
    PMAN_pfnProcessLostCb  pfnProcessLostCb,
    IMG_VOID *             pvParam,
    IMG_HANDLE *           phProcLostCbHandle
)
{
    IMG_HANDLE           hProcessId;
    PMAN_sProcLostCb *   psProcLostCb;
    IMG_HANDLE           hResBHandle;
    PMAN_sProcContext *  psProcContext;
    IMG_UINT32           ui32Result;

    IMG_ASSERT(gbPmanInitialised);

    /* Allocate a process lost structure...*/
    psProcLostCb = IMG_MALLOC(sizeof(*psProcLostCb));
    IMG_ASSERT(psProcLostCb != IMG_NULL);
    if (psProcLostCb == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psProcLostCb, 0, sizeof(*psProcLostCb));

    /* Get the resource bucket for this process (create if process not known)...*/
    hProcessId= SYSOSKM_GetProcessId();
    ui32Result = PMAN_GetProcResBucket(hProcessId, &hResBHandle);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        IMG_FREE(psProcLostCb);
        return ui32Result;
    }

    /* Locate process context structure...*/
    SYSOSKM_DisableInt();
    psProcContext = (PMAN_sProcContext *)LST_first(&gsProcList);
    while (
            (psProcContext != IMG_NULL) &&
            (psProcContext->hProcessId != hProcessId)
            )
    {
        psProcContext = (PMAN_sProcContext *)LST_next(psProcContext);
    }

    /* Did we find a process context structure - we should...*/
    if(psProcContext == NULL)
    {
        SYSOSKM_EnableInt();
        IMG_ASSERT(psProcContext != IMG_NULL);
        IMG_FREE(psProcLostCb);
        return IMG_ERROR_GENERIC_FAILURE;
    }

    /* Fill in the process lost structure...*/
    psProcLostCb->psProcContext    = psProcContext;
    psProcLostCb->pfnProcessLostCb = pfnProcessLostCb;
    psProcLostCb->pvParam          = pvParam;

    /* Add to active process lost list...*/
    LST_add(&psProcContext->sProcLostCbList, psProcLostCb);
    psProcContext->ui32CntConn++;
    SYSOSKM_EnableInt();

    *phProcLostCbHandle = psProcLostCb;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                PMAN_RemoveProcessLostCb

******************************************************************************/
IMG_VOID PMAN_RemoveProcessLostCb(
    IMG_HANDLE  hProcLostCbHandle
)
{
    PMAN_sProcLostCb *   psProcLostCb = (PMAN_sProcLostCb *)hProcLostCbHandle;
    PMAN_sProcContext *  psProcContext = psProcLostCb->psProcContext;

    IMG_ASSERT(gbPmanInitialised);

    /* Remove to active process lost list...*/
    SYSOSKM_DisableInt();
    LST_remove(&psProcContext->sProcLostCbList, psProcLostCb);
    SYSOSKM_EnableInt();

    IMG_FREE(psProcLostCb);
}
