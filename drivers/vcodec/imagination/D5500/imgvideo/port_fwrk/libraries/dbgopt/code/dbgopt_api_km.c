/*!
 *****************************************************************************
 *
 * @File       dbgopt_api_km.c
 * @Title      The Debug Options kernel mode API.
 * @Description    This file contains the source file information for the
 *  Debug Options API (kernel mode)
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

#include "dbgopt_api_km.h"
#include "report_api.h"
#include "system.h"

#include <lst.h>
#include <img_errors.h>
#include <img_defs.h>

#ifdef _MSC_VER
#include <stdio.h>
//Be aware that the _snprintf does not terminate the string with '\0' if the string goes beyond the buffer
//but both snprintf and _snprintf return -1 in this case
#define snprintf _snprintf
#endif

#define SAFE_PRINT(A) IMG_ASSERT((A) >= 0)

/*!
******************************************************************************
 This structure contains the "regular" (not keyed) debug options
******************************************************************************/
typedef struct
{
    LST_LINK;              /*!< List link (allows the structure to be part of a MeOS list).*/
    IMG_CHAR *    pszName; /*!< Name of the option */
    DBGOPT_eType  eType;   /*!< Type of the underlying option */
    DBGOPT_sValue sValue;  /*!< Union which holds the value of the option */
} DBGOPTKM_sOption;


/*!
******************************************************************************
 This structure contains the keyed debug options
******************************************************************************/
typedef struct
{
    LST_LINK;
    DBGOPT_i32Key i32Key;
    LST_T         sOptions;
} DBGOPTKM_sKeyBucket;


/*!
******************************************************************************
 Context structure which preserves full information about the state of DBGOPTKM
******************************************************************************/
typedef struct
{
    IMG_UINT32 ui32InitCnt;    /*!< Initialization marker/counter */
    LST_T      sOptList;       /*!< Regular options list */
    LST_T      sOptKeyedList;  /*!< Keyed options list */
} DBGOPTKM_sContext;


 /* Context information for DBGOPTKM */
static DBGOPTKM_sContext gsDbgOptKmContext = { 0, {IMG_NULL, IMG_NULL}, {IMG_NULL, IMG_NULL}};


static DBGOPTKM_sOption * dbgoptkm_GetEntry(
    LST_T *    sList,
    const IMG_CHAR * pszName
);


static IMG_RESULT dbgoptkm_InsertEntry(
    LST_T *         sList,
    IMG_CHAR **     pszName,
    DBGOPT_eType    eType,
    DBGOPT_sValue   sVal
);


static DBGOPTKM_sKeyBucket * dbgoptkm_GetKeyBucket(
    DBGOPT_i32Key i32Key,
    IMG_BOOL bCreate
);


static IMG_VOID dbgoptkm_RemoveEntries(
    LST_T * sList
);


static IMG_VOID dbgoptkm_DeinitEntry(
    DBGOPTKM_sOption * psOpt
);


static IMG_SIZE dbgoptkm_GetSize(
    DBGOPTKM_sOption * psOpt
);


/*!
******************************************************************************

 @Function      DBGOPTKM_Initialise

******************************************************************************/
IMG_RESULT DBGOPTKM_Initialise(
    IMG_VOID
)
{
    if (gsDbgOptKmContext.ui32InitCnt)
    {
        ++gsDbgOptKmContext.ui32InitCnt;
        return IMG_SUCCESS;
    }

    LST_init(&gsDbgOptKmContext.sOptList);
    LST_init(&gsDbgOptKmContext.sOptKeyedList);
    ++gsDbgOptKmContext.ui32InitCnt;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function      DBGOPTKM_Deinitialise

******************************************************************************/
IMG_VOID DBGOPTKM_Deinitialise(
    IMG_VOID
)
{
    if (gsDbgOptKmContext.ui32InitCnt == 0)
    {
        return;
    }

    dbgoptkm_RemoveEntries(&gsDbgOptKmContext.sOptList);

    while (!LST_empty(&gsDbgOptKmContext.sOptKeyedList))
    {
        DBGOPTKM_sKeyBucket * psKeyBucket = LST_removeHead(&gsDbgOptKmContext.sOptKeyedList);

        dbgoptkm_RemoveEntries(&psKeyBucket->sOptions);

        IMG_FREE(psKeyBucket);
    }

    --gsDbgOptKmContext.ui32InitCnt;
}


/*!
******************************************************************************

 @Function      DBGOPTKM_Set

******************************************************************************/
IMG_RESULT DBGOPTKM_Set(
    IMG_CHAR **     pszName,
    DBGOPT_eType    eType,
    DBGOPT_sValue   sVal
)
{
    IMG_ASSERT(gsDbgOptKmContext.ui32InitCnt);
    if (!gsDbgOptKmContext.ui32InitCnt)
    {
        return IMG_ERROR_NOT_INITIALISED;
    }

    /* check correctness of input parameters */
    IMG_ASSERT(*pszName != IMG_NULL);
    if (*pszName == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(eType < DBGOPT_TYPE_MAX);
    if (eType >= DBGOPT_TYPE_MAX)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    return dbgoptkm_InsertEntry(&gsDbgOptKmContext.sOptList, pszName, eType, sVal);
}


/*!
******************************************************************************

 @Function      DBGOPTKM_GetSize

******************************************************************************/
IMG_SIZE DBGOPTKM_GetSize(
    const IMG_CHAR *  pszName,
    DBGOPT_eType      eType
)
{
    IMG_SIZE   stSize;
    DBGOPT_eType eGetType = DBGOPT_TYPE_MAX;

    stSize = DBGOPTKM_Get(pszName, &eGetType, IMG_NULL);

    if (eGetType == eType)
    {
        return stSize;
    }

    return 0;
}

IMGVIDEO_EXPORT_SYMBOL(DBGOPTKM_GetSize)

/*!
******************************************************************************

 @Function      DBGOPT_Get

******************************************************************************/
#define STRING_MAX_LENGTH   256
IMG_SIZE DBGOPTKM_Get(
    const IMG_CHAR *      pszName,
    DBGOPT_eType *  peType,
    DBGOPT_sValue * psVal
)
{
    DBGOPTKM_sOption * psOpt = IMG_NULL;

    /* Check if initialised */
    if (!gsDbgOptKmContext.ui32InitCnt)
    {
        return 0;
    }

    /* Check input parameter */
    if (pszName == IMG_NULL || strlen(pszName) == 0)
    {
        return 0;
    }

    /* get the option */
    psOpt = dbgoptkm_GetEntry(&gsDbgOptKmContext.sOptList, pszName);

    if (psOpt != IMG_NULL)
    {
        IMG_CHAR acReport[STRING_MAX_LENGTH];

        if (peType)
        {
            *peType = psOpt->eType;
        }

        if (psVal)
        {
            *psVal  = psOpt->sValue;

            switch (psOpt->eType)
            {
                case DBGOPT_TYPE_BOOL:
                    SAFE_PRINT(snprintf(acReport, STRING_MAX_LENGTH, "%u", psOpt->sValue.bVal));
                    break;
                case DBGOPT_TYPE_NUMBER:
                    SAFE_PRINT(snprintf(acReport, STRING_MAX_LENGTH, "%u", psOpt->sValue.ui32Val));
                    break;
                case DBGOPT_TYPE_STRING:
                    SAFE_PRINT(snprintf(acReport, STRING_MAX_LENGTH, "%s", psOpt->sValue.pszVal));
                    break;
                case DBGOPT_TYPE_BUF:
                    SAFE_PRINT(snprintf(acReport, STRING_MAX_LENGTH, "%s", "Buffer"));
                    break;
                default:
                    break;
            }

            REPORT(REPORT_MODULE_DBGOPT, REPORT_INFO,
                   "%s: %s",
                   pszName, acReport);
        }
    }

    return dbgoptkm_GetSize(psOpt);
}
IMGVIDEO_EXPORT_SYMBOL(DBGOPTKM_Get)


/*!
******************************************************************************

 @Function      DBGOPTKM_Clear

******************************************************************************/
IMG_VOID DBGOPTKM_Clear(
    const IMG_CHAR *      pszName
)
{
    DBGOPTKM_sOption * psOpt = IMG_NULL;

    /* Check if initialised */
    if (!gsDbgOptKmContext.ui32InitCnt)
    {
        return;
    }

    /* Check input parameter */
    if (pszName == IMG_NULL || strlen(pszName) == 0)
    {
        return;
    }

    /* get the option */
    psOpt = dbgoptkm_GetEntry(&gsDbgOptKmContext.sOptList, pszName);

    /* if such option exists -> remove it*/
    if (psOpt != IMG_NULL)
    {
        LST_remove(&gsDbgOptKmContext.sOptList, psOpt);
    }

    dbgoptkm_DeinitEntry(psOpt);
}


/*!
******************************************************************************

 @Function      DBGOPTKM_SetWithKey

******************************************************************************/
IMG_RESULT DBGOPTKM_SetWithKey(
    DBGOPT_i32Key    i32Key,
    IMG_CHAR ** pszName,
    DBGOPT_eType     eType,
    DBGOPT_sValue    sVal
)
{
    DBGOPTKM_sKeyBucket * psKeyBucket = IMG_NULL;

    IMG_ASSERT(gsDbgOptKmContext.ui32InitCnt);
    if (!gsDbgOptKmContext.ui32InitCnt)
    {
        return IMG_ERROR_NOT_INITIALISED;
    }

    /* check correctness of input parameters */
    IMG_ASSERT(*pszName != IMG_NULL);
    if (*pszName == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(eType < DBGOPT_TYPE_MAX);
    if (eType >= DBGOPT_TYPE_MAX)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psKeyBucket = dbgoptkm_GetKeyBucket(i32Key, IMG_TRUE);
    IMG_ASSERT(psKeyBucket);
    if (psKeyBucket == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    return dbgoptkm_InsertEntry(&psKeyBucket->sOptions, pszName, eType, sVal);
}


/*!
******************************************************************************

 @Function      DBGOPTKM_GetSizeWithKey

******************************************************************************/
IMG_SIZE DBGOPTKM_GetSizeWithKey(
    DBGOPT_i32Key     i32Key,
    const IMG_CHAR *  pszName,
    DBGOPT_eType      eType
)
{
    DBGOPT_eType eGetType;
    IMG_SIZE   stSize;

    stSize = DBGOPTKM_GetWithKey(i32Key, pszName, &eGetType, IMG_NULL);

    if (eGetType == eType)
    {
        return stSize;
    }

    return 0;
}
IMGVIDEO_EXPORT_SYMBOL(DBGOPTKM_GetSizeWithKey)


/*!
******************************************************************************

 @Function      DBGOPT_GetWithKey

******************************************************************************/
IMG_SIZE DBGOPTKM_GetWithKey(
    DBGOPT_i32Key    i32Key,
    const IMG_CHAR * pszName,
    DBGOPT_eType *   peType,
    DBGOPT_sValue *  psVal
)
{
    DBGOPTKM_sKeyBucket * psKeyBucket = IMG_NULL;
    DBGOPTKM_sOption *    psOpt = IMG_NULL;

    if (!gsDbgOptKmContext.ui32InitCnt)
    {
        return IMG_FALSE;
    }

    /* Check input parameter */
    if (pszName == IMG_NULL || strlen(pszName) == 0)
    {
        return IMG_FALSE;
    }

    psKeyBucket = dbgoptkm_GetKeyBucket(i32Key, IMG_FALSE);
    if (psKeyBucket == IMG_NULL)
    {
        return IMG_FALSE;
    }

    /* get the option */
    psOpt = dbgoptkm_GetEntry(&psKeyBucket->sOptions, pszName);

    if (psOpt != IMG_NULL)
    {
        if (peType)
        {
            *peType = psOpt->eType;
        }

        if (psVal)
        {
            *psVal  = psOpt->sValue;
        }
    }

    return dbgoptkm_GetSize(psOpt);
}
IMGVIDEO_EXPORT_SYMBOL(DBGOPTKM_GetWithKey)


/*!
******************************************************************************

 @Function      DBGOPTKM_ClearWithKey

******************************************************************************/
IMG_VOID DBGOPTKM_ClearWithKey(
    DBGOPT_i32Key     i32Key,
    const IMG_CHAR *  pszName
)
{
    DBGOPTKM_sKeyBucket * psKeyBucket = IMG_NULL;
    DBGOPTKM_sOption *    psOpt = IMG_NULL;

    if (!gsDbgOptKmContext.ui32InitCnt)
    {
        return;
    }

    /* Check input parameter */
    if (pszName == IMG_NULL || strlen(pszName) == 0)
    {
        return;
    }

    /* get the bucket */
    psKeyBucket = dbgoptkm_GetKeyBucket(i32Key, IMG_FALSE);
    if (psKeyBucket == IMG_NULL)
    {
        return;
    }

    /* get the option */
    psOpt = dbgoptkm_GetEntry(&psKeyBucket->sOptions, pszName);

    /* if such option exists -> remove it*/
    if (psOpt != IMG_NULL)
    {
        LST_remove(&psKeyBucket->sOptions, psOpt);
    }

    dbgoptkm_DeinitEntry(psOpt);
}


/*!
******************************************************************************

 @Function      DBGOPTKM_ClearAll

******************************************************************************/
IMG_VOID DBGOPTKM_ClearAll(
    IMG_VOID
)
{
    dbgoptkm_RemoveEntries(&gsDbgOptKmContext.sOptList);

    while (!LST_empty(&gsDbgOptKmContext.sOptKeyedList))
    {
        DBGOPTKM_sKeyBucket * psKeyBucket = LST_removeHead(&gsDbgOptKmContext.sOptKeyedList);

        dbgoptkm_RemoveEntries(&psKeyBucket->sOptions);

        IMG_FREE(psKeyBucket);
    }
}


/*!
******************************************************************************

 @Function      dbgoptkm_GetEntry

******************************************************************************/
static DBGOPTKM_sOption * dbgoptkm_GetEntry(
    LST_T *    sList,
    const IMG_CHAR * pszName
)
{
    DBGOPTKM_sOption * psOpt = IMG_NULL;

    psOpt = (DBGOPTKM_sOption *) LST_first(sList);
    while (psOpt != IMG_NULL &&
           strcmp(psOpt->pszName, pszName))
    {
        psOpt = (DBGOPTKM_sOption *) LST_next(psOpt);
    }

    return psOpt;
}


/*!
******************************************************************************

 @Function      dbgoptkm_InsertEntry

******************************************************************************/
static IMG_RESULT dbgoptkm_InsertEntry(
    LST_T *         sList,
    IMG_CHAR **     pszName,
    DBGOPT_eType    eType,
    DBGOPT_sValue   sVal
)
{
    DBGOPTKM_sOption * psOption = IMG_NULL;

    if (dbgoptkm_GetEntry(sList, *pszName) != IMG_NULL)
    {
        return IMG_ERROR_ALREADY_INITIALISED;
    }

    psOption = (DBGOPTKM_sOption *) IMG_MALLOC(sizeof(*psOption));
    IMG_ASSERT(psOption != IMG_NULL);
    if (psOption == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    psOption->pszName   = *pszName;
    psOption->eType     = eType;
    psOption->sValue    = sVal;

    LST_add(sList, psOption);

    /* take full ownership */
    *pszName = IMG_NULL;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function      dbgoptkm_GetKeyBucket

******************************************************************************/
static DBGOPTKM_sKeyBucket * dbgoptkm_GetKeyBucket(
    DBGOPT_i32Key i32Key,
    IMG_BOOL bCreate
)
{
    DBGOPTKM_sKeyBucket * psKeyBucket = IMG_NULL;

    psKeyBucket = (DBGOPTKM_sKeyBucket *) LST_first(&gsDbgOptKmContext.sOptKeyedList);
    while (psKeyBucket != IMG_NULL &&
           psKeyBucket->i32Key != i32Key)
    {
        psKeyBucket = (DBGOPTKM_sKeyBucket *) LST_next(psKeyBucket);
    }

    /* bucket not found but allowed to create one */
    if (psKeyBucket == IMG_NULL && bCreate)
    {
        psKeyBucket = (DBGOPTKM_sKeyBucket *) IMG_MALLOC(sizeof(*psKeyBucket));
        IMG_ASSERT(psKeyBucket != IMG_NULL);
        if (psKeyBucket == IMG_NULL)
        {
            return IMG_NULL;
        }

        psKeyBucket->i32Key = i32Key;
        LST_init(&psKeyBucket->sOptions);

        LST_add(&gsDbgOptKmContext.sOptKeyedList, psKeyBucket);
    }

    return psKeyBucket;
}


/*!
******************************************************************************

 @Function      dbgoptkm_RemoveEntries

******************************************************************************/
static IMG_VOID dbgoptkm_RemoveEntries(
    LST_T * sList
)
{
    while (!LST_empty(sList))
    {
        DBGOPTKM_sOption * psOpt = LST_removeHead(sList);

        dbgoptkm_DeinitEntry(psOpt);
    }
}


/*!
******************************************************************************

 @Function      dbgoptkm_DeinitEntry

******************************************************************************/
static IMG_VOID dbgoptkm_DeinitEntry(
    DBGOPTKM_sOption * psOpt
)
{
    if (psOpt == IMG_NULL)
    {
        return;
    }

    if (psOpt->pszName != IMG_NULL)
    {
        IMG_FREE(psOpt->pszName);
        psOpt->pszName = IMG_NULL;
    }

    if (psOpt->eType == DBGOPT_TYPE_STRING &&
        psOpt->sValue.pszVal != IMG_NULL)
    {
        IMG_FREE(psOpt->sValue.pszVal);
        psOpt->sValue.pszVal = IMG_NULL;
    }
    else if (psOpt->eType == DBGOPT_TYPE_BUF &&
        psOpt->sValue.sBufVal.pvVal != IMG_NULL)
    {
        IMG_FREE(psOpt->sValue.sBufVal.pvVal);
        psOpt->sValue.sBufVal.pvVal = IMG_NULL;
    }

    IMG_FREE(psOpt);
}


/*!
******************************************************************************

 @Function      dbgoptkm_DeinitEntry

******************************************************************************/
static IMG_SIZE dbgoptkm_GetSize(
    DBGOPTKM_sOption * psOpt
)
{
    if (psOpt == IMG_NULL)
    {
        return 0;
    }

    switch (psOpt->eType)
    {
        case DBGOPT_TYPE_BOOL:
            return sizeof(psOpt->sValue.bVal);
            break;
        case DBGOPT_TYPE_NUMBER:
            return sizeof(psOpt->sValue.ui32Val);
            break;
        case DBGOPT_TYPE_STRING:
            return strlen(psOpt->sValue.pszVal) + 1;
            break;
        case DBGOPT_TYPE_BUF:
            return psOpt->sValue.sBufVal.stSize;
            break;
        default:
            break;
    }

    return 0;
}
