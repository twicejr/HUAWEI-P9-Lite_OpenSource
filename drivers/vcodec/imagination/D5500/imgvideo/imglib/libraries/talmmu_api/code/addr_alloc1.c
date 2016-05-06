/*!
 *****************************************************************************
 *
 * @File       addr_alloc1.c
 * @Description    Address allocation APIs - used to manage address allocation
 *  with a number of predefined regions.
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

#include <img_types.h>
#include <img_defs.h>
#include <img_errors.h>

#include <addr_alloc1.h>
#include <hash.h>

#if !defined (IMG_KERNEL_MODULE)
    #include <stdio.h> // printf
#endif

#ifdef __cplusplus
    #define PREF extern "C"
#else
    #define PREF
#endif

#if !defined (__TALMMU_NO_OS__)
    #if defined (IMG_KERNEL_MODULE)
        #include <sysmem_utils.h>
        #include <sysdev_utils.h>
        static IMG_HANDLE hMutex;
        #define addr_alloc_Lock()             SYSOSKM_LockMutex(hMutex)
        #define addr_alloc_UnLock()           SYSOSKM_UnlockMutex(hMutex)
        #define addr_alloc_CreateLock()       SYSOSKM_CreateMutex(&hMutex)
        #define addr_alloc_DestroyLock()      SYSOSKM_DestroyMutex(hMutex)
    #else
        #define addr_alloc_Lock()             
        #define addr_alloc_UnLock()           
        #define addr_alloc_CreateLock()       
        #define addr_alloc_DestroyLock() 
    #endif
#else
    #define addr_alloc_Lock()             
    #define addr_alloc_UnLock()           
    #define addr_alloc_CreateLock()       
    #define addr_alloc_DestroyLock()      
#endif


//Defines whether sequential or random allocation is used
enum
{
    SEQUENTIAL_ALLOCATION,
    RANDOM_ALLOCATION
};

#define RANDOM_BLOCK_SEED 0x82647868
static ADDR_sContext gsContext;              /*!< Global context.        				*/

static IMG_BOOL bInitalised = IMG_FALSE;    /*!< Sub-system initialised.				*/
static IMG_UINT32 gui32NoContext = 0;       /*!< Count of contexts.     				*/

/*!
******************************************************************************

@Function				ADDR_Initialise

******************************************************************************/
PREF IMG_RESULT ADDR_Initialise(IMG_VOID)
{
    IMG_UINT32 ui32Result = IMG_ERROR_ALREADY_INITIALISED;

    //If we are not initialised
    if (!bInitalised)
    {
        ui32Result = ADDR_CxInitialise(&gsContext);
    }

    return ui32Result;
}

/*!
******************************************************************************

@Function				ADDR_CxInitialise

******************************************************************************/
PREF IMG_RESULT ADDR_CxInitialise(
    ADDR_sContext * const psContext
)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psContext);
    if (IMG_NULL == psContext)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    //If we are not initialised
    if (!bInitalised)
    {
	    //Initialise context
    	IMG_MEMSET(psContext, 0x00, sizeof(*psContext));
		
        addr_alloc_CreateLock();
        addr_alloc_Lock();

        //Initialise the hash functions..
        ui32Result = VID_HASH_Initialise();
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if(IMG_SUCCESS != ui32Result)
        {
            addr_alloc_UnLock();
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        //Initialise the arena functions
        ui32Result = VID_RA_Initialise();
        if(IMG_SUCCESS != ui32Result)
        {
            addr_alloc_UnLock();
            ui32Result = VID_HASH_Finalise();
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

#if !defined (IMG_KERNEL_MODULE)
        //Seed the random number generator 
        srand(RANDOM_BLOCK_SEED);
#endif
        //We are now initalised 
        bInitalised = IMG_TRUE;
        ui32Result = IMG_SUCCESS;
    }
    else
    {
        addr_alloc_Lock();
    }

    gui32NoContext++;
    addr_alloc_UnLock();

error:
    return ui32Result;
}

/*!
******************************************************************************

@Function				ADDR_Deinitialise

******************************************************************************/
PREF IMG_RESULT ADDR_Deinitialise(IMG_VOID)
{
    return ADDR_CxDeinitialise(&gsContext);
}

/*!
******************************************************************************

@Function				ADDR_CxDeinitialise

******************************************************************************/
IMG_RESULT ADDR_CxDeinitialise(
    ADDR_sContext * const psContext
)
{
    ADDR_sRegion * psTmpRegion = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(gui32NoContext != 0);

    IMG_ASSERT(IMG_NULL != psContext);
    if (IMG_NULL == psContext)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(IMG_TRUE == bInitalised); 
    if (bInitalised)
    {
        addr_alloc_Lock();

        psTmpRegion = psContext->psRegions;

        //Delete all arena structure
        if (IMG_NULL != psContext->psDefaultRegion)
        {
            ui32Result = VID_RA_Delete(psContext->psDefaultRegion->phArena);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                //error handling
            }
        }

        while (IMG_NULL != psTmpRegion)
        {
            ui32Result = VID_RA_Delete(psTmpRegion->phArena);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                //error handling
            }
            psTmpRegion = psTmpRegion->psNextRegion;
        }

        IMG_ASSERT(0 != gui32NoContext);
        if(0 != gui32NoContext)
        {
            gui32NoContext--;
        }

        ui32Result = IMG_SUCCESS;
        if ( 0 == gui32NoContext)
        {
            //Free off resources
            ui32Result = VID_HASH_Finalise();
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                //error handling
            }
            ui32Result = VID_RA_Finalise();
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                //error handling
            }
            bInitalised = IMG_FALSE;

            addr_alloc_UnLock();
            addr_alloc_DestroyLock();
        }
        else
        {
            addr_alloc_UnLock();
        }
    }

error:
    return ui32Result;
}



/*!
******************************************************************************

@Function				ADDR_DefineMemoryRegion

******************************************************************************/
IMG_RESULT ADDR_DefineMemoryRegion(
    ADDR_sRegion * const psRegion
)
{
    return ADDR_CxDefineMemoryRegion(&gsContext, psRegion);
}

/*!
******************************************************************************

@Function				ADDR_CxDefineMemoryRegion

******************************************************************************/
IMG_RESULT ADDR_CxDefineMemoryRegion(
    ADDR_sContext *  const psContext,
    ADDR_sRegion *   const psRegion
)
{
    ADDR_sRegion * psTmpRegion = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_SUCCESS;

    IMG_ASSERT(IMG_NULL != psContext);
    IMG_ASSERT(IMG_NULL != psRegion);
    if (IMG_NULL == psContext ||
        IMG_NULL == psRegion)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    addr_alloc_Lock();

    psTmpRegion = psContext->psRegions;

    //Ensure the link to the next is NULL
    psRegion->psNextRegion = IMG_NULL;

    //If this is the default memory region
    if (IMG_NULL == psRegion->pszName)
    {
        //Should not previously have been defined
        IMG_ASSERT(IMG_NULL == psContext->psDefaultRegion);
        if (IMG_NULL != psContext->psDefaultRegion)
        {
            addr_alloc_UnLock();
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        psContext->psDefaultRegion = psRegion;
        psContext->ui32NoRegions ++;

        //Create an arena for memory allocation 
        ui32Result = VID_RA_Create (
            "memory",					//name of resource arena for debug 
            psRegion->ui64BaseAddr,		//start of resource 
            psRegion->ui64Size,			//size of resource 
            1,							//allocation quantum 
            IMG_NULL,					//import allocator 
            IMG_NULL,					//import deallocator 
            IMG_NULL,					//import handle 
            &psRegion->phArena);

        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if(IMG_SUCCESS != ui32Result)
        {
            addr_alloc_UnLock();
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
    }
    else
    {
        //Run down the list of existing named regions to check if there is a region with this name
        while ((IMG_NULL != psTmpRegion) &&
            (IMG_STRCMP(psRegion->pszName, psTmpRegion->pszName) != 0) &&
            (IMG_NULL != psTmpRegion->psNextRegion)
            )
        {
            psTmpRegion = psTmpRegion->psNextRegion;
        }

        //If we have items in the list
        if (IMG_NULL != psTmpRegion)
        {
            //Check we didn't stop because the name clashes with one already defined..
            IMG_ASSERT(IMG_STRCMP(psRegion->pszName, psTmpRegion->pszName) != 0);
            IMG_ASSERT(IMG_NULL == psTmpRegion->psNextRegion);

            if (IMG_STRCMP(psRegion->pszName, psTmpRegion->pszName) == 0 ||
                IMG_NULL != psTmpRegion->psNextRegion
                )
            {
                addr_alloc_UnLock();
                ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                goto error;
            }

            psTmpRegion->psNextRegion = psRegion;
        }
        else
        {
            //Add to head of list 
            psContext->psRegions = psRegion;
        }

        psContext->ui32NoRegions ++;

        //Create an arena for memory allocation 
        ui32Result = VID_RA_Create(
            psRegion->pszName,			//name of resource arena for debug 
            psRegion->ui64BaseAddr,		//start of resource 
            psRegion->ui64Size,			//size of resource 
            1,							//allocation quantum 
            IMG_NULL,					//import allocator 
            IMG_NULL,					//import deallocator 
            IMG_NULL,					//import handle 
            &psRegion->phArena);

        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if(IMG_SUCCESS != ui32Result)
        {
            addr_alloc_UnLock();
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
    }

    addr_alloc_UnLock();

    //Check the arean was created OK
    IMG_ASSERT(IMG_NULL != psRegion->phArena);
    if (IMG_NULL == psRegion->phArena)
    {
        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
        goto error;
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

@Function				ADDR_Malloc

******************************************************************************/
IMG_RESULT ADDR_Malloc(
    const   IMG_CHAR  * const   pszName,
            IMG_UINT64          ui64Size,
            IMG_UINT64 * const  puiBase
)
{
    return ADDR_CxMalloc(&gsContext, pszName, ui64Size, puiBase);
}


/*!
******************************************************************************

@Function				ADDR_Malloc1

******************************************************************************/
IMG_RESULT ADDR_Malloc1(
    const   IMG_CHAR  * const   pszName,
            IMG_UINT64          ui64Size,
            IMG_UINT64          ui64Alignment,
            IMG_UINT64 * const  pui64Base
)
{
    return ADDR_CxMalloc1(&gsContext, pszName, ui64Size, ui64Alignment, pui64Base);
}

/*!
******************************************************************************

@Function				addr_CxMalloc1

******************************************************************************/
static IMG_RESULT addr_CxMalloc1(
    const   ADDR_sContext *     psContext,
    const   IMG_CHAR * const    pszName,
            IMG_UINT64          ui64Size,
            IMG_UINT64          ui64Alignment,
            IMG_UINT64 * const  pui64Base
)
{
    ADDR_sRegion * psTmpRegion = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psContext);
    IMG_ASSERT(IMG_NULL != pui64Base);
    IMG_ASSERT(IMG_NULL != pszName);

    if(IMG_NULL == psContext ||
        IMG_NULL == pui64Base ||
        IMG_NULL == pszName)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_invalid_parameters;
    }

    do
    {
        psTmpRegion = psContext->psRegions;
		
        //If we are using random blocks, ignore the given blockname
        if (psContext->bUseRandomBlocks) 
        {
#if !defined (IMG_KERNEL_MODULE)
            IMG_UINT32 ui32BlockNo;

            //Select a random number from 0 to num blocks -1
            while (psContext->ui32NoRegions <= (ui32BlockNo = rand() / (RAND_MAX/psContext->ui32NoRegions)));

            //0 counts as default region
            if (0 == ui32BlockNo)
            {
                IMG_ASSERT(IMG_NULL != psContext->psDefaultRegion);
                if(IMG_NULL == psContext->psDefaultRegion)
                {
                    ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                    goto error_null_region;
                }
                psTmpRegion = psContext->psDefaultRegion;
            }
            else
            {
                //Count through the region list to the random one which has been selected
                while (ui32BlockNo > 1)
                {
                    IMG_ASSERT(psTmpRegion->psNextRegion);
                    if(IMG_NULL == psTmpRegion->psNextRegion)
                    {
                        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                        goto error_null_region;
                    }
                    psTmpRegion = psTmpRegion->psNextRegion;
                    ui32BlockNo --;
                }
            }
#else
            IMG_ASSERT(IMG_FALSE);	//Not supported in kernel mode 
            return IMG_ERROR_OUT_OF_MEMORY;
#endif
        }
        //If the allocation is for the default region
        else if (IMG_NULL == pszName)
        {
            IMG_ASSERT(IMG_NULL != psContext->psDefaultRegion);
            if(IMG_NULL == psContext->psDefaultRegion)
            {
                ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                goto error_null_region;
            }
            psTmpRegion = psContext->psDefaultRegion;
        }
        else
        {
            //Run down the list of existing named regions to locate this
            while((IMG_NULL != psTmpRegion) && 
                (IMG_STRCMP(pszName, psTmpRegion->pszName) != 0) &&
                (psTmpRegion->psNextRegion)
                )
            {
                psTmpRegion = psTmpRegion->psNextRegion;
            }

            //If there was no match.
            if ((IMG_NULL == psTmpRegion) ||
                (IMG_STRCMP(pszName, psTmpRegion->pszName) != 0)
                )
            {
                //Use the default
                IMG_ASSERT(IMG_NULL != psContext->psDefaultRegion);
                if(IMG_NULL == psContext->psDefaultRegion)
                {
                    ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                    goto error_null_region;
                }
                psTmpRegion = psContext->psDefaultRegion;
            }
        }

        IMG_ASSERT(IMG_NULL != psTmpRegion);
        if(IMG_NULL == psTmpRegion)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error_null_region;
        }

        //Allocate size + guard band
        ui32Result = VID_RA_Alloc( psTmpRegion->phArena, 
            ui64Size + psTmpRegion->ui32GuardBand, 
            IMG_NULL,
            IMG_NULL, 
            (psContext->bUseRandomAllocation) ? RANDOM_ALLOCATION : SEQUENTIAL_ALLOCATION, 
            ui64Alignment, 
            pui64Base);

        if (IMG_SUCCESS != ui32Result)
        {
            if (psContext->bUseRandomBlocks)
            {
                continue; //If we have overrun, pick a different region 
            }
#if !defined (IMG_KERNEL_MODULE)
            if (psTmpRegion->pszName)
            {
                printf("ERROR: Memory Region %s is full\n", psTmpRegion->pszName);
            }
            else
            {
                printf("ERROR: Default Memory Region is full\n");
            }
#endif			
            IMG_ASSERT(IMG_FALSE);
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        break;

    }while (IMG_TRUE);

error_invalid_parameters:
error_null_region:
    return ui32Result;
}

/*!
******************************************************************************

@Function				ADDR_CxMalloc

******************************************************************************/
IMG_RESULT ADDR_CxMalloc(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR *      const   pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64 *    const   pui64Base
)
{
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psContext);
    IMG_ASSERT(IMG_NULL != pszName);
    IMG_ASSERT(IMG_NULL != pui64Base);

    if(IMG_NULL == psContext ||
        IMG_NULL == pui64Base ||
        IMG_NULL == pszName)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_invalid_parameters;
    }

    *(pui64Base) = (IMG_UINT64)-1LL;

    addr_alloc_Lock();
    ui32Result = addr_CxMalloc1(psContext, pszName, ui64Size, 1, pui64Base);
    addr_alloc_UnLock();

    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        //error handling
    }

error_invalid_parameters:
    return ui32Result;
}

/*!
******************************************************************************

@Function				ADDR_CxMalloc1

******************************************************************************/
IMG_RESULT ADDR_CxMalloc1(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64              ui64Alignment,
            IMG_UINT64 * const      pui64Base
)
{
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psContext);
    IMG_ASSERT(IMG_NULL != pszName);
    IMG_ASSERT(IMG_NULL != pui64Base);

    if(IMG_NULL == psContext ||
        IMG_NULL == pui64Base ||
        IMG_NULL == pszName)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_invalid_parameters;
    }

    *(pui64Base) = (IMG_UINT64)-1LL;

    addr_alloc_Lock();
    ui32Result = addr_CxMalloc1(psContext, pszName, ui64Size, ui64Alignment, pui64Base);
    addr_alloc_UnLock();

    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        //error handling
    }

error_invalid_parameters:
    return ui32Result;
}

/*!
******************************************************************************

@Function				ADDR_CxMallocRes

******************************************************************************/
IMG_RESULT ADDR_CxMallocRes(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64 * const      pui64Base
)
{
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psContext);
    IMG_ASSERT(IMG_NULL != pszName);
    IMG_ASSERT(IMG_NULL != pui64Base);

    if(IMG_NULL == psContext ||
        IMG_NULL == pszName ||
        IMG_NULL == pui64Base)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_invalid_parameters;
    }

    addr_alloc_Lock();
    ui32Result = addr_CxMalloc1(psContext, pszName, ui64Size, 1, pui64Base);
    addr_alloc_UnLock();

    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        //error handling
    }

error_invalid_parameters:
    return ui32Result;
}

/*!
******************************************************************************

@Function				ADDR_CxMalloc1Res

******************************************************************************/
IMG_RESULT ADDR_CxMalloc1Res(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Size,
            IMG_UINT64              ui64Alignment,
            IMG_UINT64 * const      pui64Base
)
{
    IMG_RESULT ui32Result;

    IMG_ASSERT(IMG_NULL != psContext);
    IMG_ASSERT(IMG_NULL != pui64Base);
    if(IMG_NULL == psContext ||
        IMG_NULL == pui64Base)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_invalid_parameters;
    }

    addr_alloc_Lock();
    ui32Result = addr_CxMalloc1(psContext, pszName, ui64Size, ui64Alignment, pui64Base);
    addr_alloc_UnLock();

error_invalid_parameters:
    return ui32Result;
}


/*!
******************************************************************************

@Function				ADDR_Free

******************************************************************************/
IMG_RESULT ADDR_Free(
    const   IMG_CHAR *  const pszName,
            IMG_UINT64  ui64Addr
)
{
    return ADDR_CxFree(&gsContext, pszName, ui64Addr);
}

/*!
******************************************************************************

@Function				ADDR_Free

******************************************************************************/
IMG_RESULT ADDR_CxFree(
            ADDR_sContext * const   psContext,
    const   IMG_CHAR * const        pszName,
            IMG_UINT64              ui64Addr
)
{
    ADDR_sRegion * psTmpRegion;
    IMG_RESULT ui32Result;

    IMG_ASSERT(IMG_NULL != psContext);
    if (IMG_NULL == psContext)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_invalid_parameters;
    }

	psTmpRegion = psContext->psRegions;

    addr_alloc_Lock();

	//Ignore given name, find using the address
    if (psContext->bUseRandomBlocks)  
    {
        //Try Default Region 
        psTmpRegion = psContext->psDefaultRegion;
        if ( IMG_NULL != psTmpRegion &&
            ui64Addr >= psTmpRegion->ui64BaseAddr &&
            ui64Addr < (psTmpRegion->ui64BaseAddr + psTmpRegion->ui64Size))
        { 
            //Memory is on the default region 
        }
        else
        {
            psTmpRegion = psContext->psRegions;
            //Continue looping while address is not inside current region 
            while ( (ui64Addr < psTmpRegion->ui64BaseAddr) 
                || (ui64Addr >= psTmpRegion->ui64BaseAddr + psTmpRegion->ui64Size) )
            {
                IMG_ASSERT(IMG_NULL != psTmpRegion->psNextRegion);
                if (IMG_NULL == psTmpRegion->psNextRegion)
                {
                    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
                    goto error;
                }
                psTmpRegion = psTmpRegion->psNextRegion;
            }
        }
    }
	//If the allocation is for the default region
    else if (IMG_NULL == pszName) 
    {
        IMG_ASSERT(IMG_NULL != psContext->psDefaultRegion);
        if (IMG_NULL == psContext->psDefaultRegion)
        {
            ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            goto error;
        }
        psTmpRegion = psContext->psDefaultRegion;
    }
    else
    {
        //Run down the list of existing named regions to locate this
        while ((IMG_NULL != psTmpRegion) &&
            (IMG_STRCMP(pszName, psTmpRegion->pszName) != 0) &&
            (psTmpRegion->psNextRegion))
        {
            psTmpRegion = psTmpRegion->psNextRegion;
        }

        //If there was no match.
        if ((IMG_NULL == psTmpRegion) ||
            (IMG_STRCMP(pszName, psTmpRegion->pszName) != 0))
        {
            //Use the default
            IMG_ASSERT(IMG_NULL != psContext->psDefaultRegion);
            if (IMG_NULL == psContext->psDefaultRegion)
            {
                ui32Result = IMG_ERROR_INVALID_PARAMETERS;
                goto error;
            }
            psTmpRegion = psContext->psDefaultRegion;
        }
    }

    //Free the address
    ui32Result = VID_RA_Free(psTmpRegion->phArena, ui64Addr);

error:
    addr_alloc_UnLock();

error_invalid_parameters:
    return ui32Result;
}
