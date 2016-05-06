/*!
 *****************************************************************************
 *
 * @File       dbgopt_api.c
 * @Title      Implementation of the Debug Options user mode API.
 * @Description    This file contains the implementation file information for the
 *  Debug Options API
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

#include "dbgopt_api.h"
#include "dbgopt_api_km.h"
#include "sysos_api_km.h"

#include <img_errors.h>
#include <img_defs.h>


/*
******************************************************************************

 Static functions

******************************************************************************/


static IMG_RESULT dbgoptbrg_Set(
    IMG_BOOL           bWithKey,
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName,
    DBGOPT_eType       eType,
    DBGOPT_sValueBrg   sVal
);


static IMG_UINT64 dbgoptbrg_Get(
    IMG_BOOL                  bWithKey,
    DBGOPT_i32Key             i32Key,
    DBGOPT_sStrWithLen        sStrName,
    SYSBRG_POINTER_ARG(DBGOPT_eType) peType,
    SYSBRG_POINTER_ARG(DBGOPT_sValueBrg) psVal
);


static IMG_VOID dbgoptbrg_Clear(
    IMG_BOOL           bWithKey,
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_Initialise

******************************************************************************/
IMG_RESULT DBGOPTBRG_Initialise(
    IMG_VOID
)
{
    return DBGOPTKM_Initialise();
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_Deinitialise

******************************************************************************/
IMG_VOID DBGOPTBRG_Deinitialise(
    IMG_VOID
)
{
    DBGOPTKM_Deinitialise();
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_Set

******************************************************************************/
IMG_RESULT DBGOPTBRG_Set(
    DBGOPT_sStrWithLen sStrName,
    DBGOPT_eType       eType,
    DBGOPT_sValueBrg   sVal
)
{
    return dbgoptbrg_Set(IMG_FALSE, 0, sStrName, eType, sVal);
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_Get

******************************************************************************/
IMG_UINT64 DBGOPTBRG_Get(
    DBGOPT_sStrWithLen        sStrName,
    SYSBRG_POINTER_ARG(DBGOPT_eType)     peType,
    SYSBRG_POINTER_ARG(DBGOPT_sValueBrg) psVal
)
{
    return dbgoptbrg_Get(IMG_FALSE, 0, sStrName, peType, psVal);
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_Clear

******************************************************************************/
IMG_VOID DBGOPTBRG_Clear(
    DBGOPT_sStrWithLen sStrName
)
{
    dbgoptbrg_Clear(IMG_FALSE, 0, sStrName);
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_SetWithKey

******************************************************************************/
IMG_RESULT DBGOPTBRG_SetWithKey(
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName,
    DBGOPT_eType       eType,
    DBGOPT_sValueBrg   sVal
)
{
    return dbgoptbrg_Set(IMG_TRUE, i32Key, sStrName, eType, sVal);
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_GetWithKey

******************************************************************************/
IMG_UINT64 DBGOPTBRG_GetWithKey(
    DBGOPT_i32Key             i32Key,
    DBGOPT_sStrWithLen        sStrName,
    SYSBRG_POINTER_ARG(DBGOPT_eType)     peType,
    SYSBRG_POINTER_ARG(DBGOPT_sValueBrg) psVal
)
{
    return dbgoptbrg_Get(IMG_TRUE, i32Key, sStrName, peType, psVal);
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_ClearWithKey

******************************************************************************/
IMG_VOID DBGOPTBRG_ClearWithKey(
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName
)
{
    dbgoptbrg_Clear(IMG_TRUE, i32Key, sStrName);
}


/*!
******************************************************************************

 @Function      DBGOPTBRG_ClearAll

******************************************************************************/
IMG_VOID DBGOPTBRG_ClearAll(
IMG_VOID
)
{
    DBGOPTKM_ClearAll();
}


/*!
******************************************************************************

 @Function      dbgoptbrg_Set

******************************************************************************/
static IMG_RESULT dbgoptbrg_Set(
    IMG_BOOL           bWithKey,
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName,
    DBGOPT_eType       eType,
    DBGOPT_sValueBrg   sVal
)
{
    IMG_CHAR *    pszLocName = IMG_NULL;
    IMG_RESULT    rResult = IMG_SUCCESS;
    DBGOPT_sValue sLocVal;

    /* check correctness of input parameters */
    IMG_ASSERT(SYSBRG_POINTER_FROM_USER(sStrName.pszStr) != IMG_NULL);
    if (SYSBRG_POINTER_FROM_USER(sStrName.pszStr) == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(eType < DBGOPT_TYPE_MAX);
    if (eType >= DBGOPT_TYPE_MAX)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (eType == DBGOPT_TYPE_STRING)
    {
        sLocVal.pszVal =
                (IMG_CHAR *) IMG_MALLOC((sVal.sStrVal.stLen + 1) * sizeof(IMG_CHAR));
        IMG_ASSERT(sLocVal.pszVal != IMG_NULL);
        if (sLocVal.pszVal == IMG_NULL)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }

        rResult = SYSOSKM_CopyFromUser(sLocVal.pszVal,
                                       sVal.sStrVal.pszStr,
                                       sVal.sStrVal.stLen + 1);

        IMG_ASSERT(rResult == IMG_SUCCESS);
        if (rResult != IMG_SUCCESS)
        {
            goto clearPszVal;
        }
    }
    else if (eType == DBGOPT_TYPE_BUF)
    {
        sLocVal.sBufVal.pvVal =
                (IMG_BYTE *) IMG_MALLOC(sVal.sBufVal.stSize * sizeof(IMG_BYTE));
        IMG_ASSERT(sLocVal.sBufVal.pvVal != IMG_NULL);
        if (sLocVal.sBufVal.pvVal == IMG_NULL)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }

        rResult = SYSOSKM_CopyFromUser(sLocVal.sBufVal.pvVal,
                                       sVal.sBufVal.pvVal,
                                       sVal.sBufVal.stSize);
        IMG_ASSERT(rResult == IMG_SUCCESS);
        if (rResult != IMG_SUCCESS)
        {
            goto clearPszVal;
        }

        sLocVal.sBufVal.stSize = sVal.sBufVal.stSize;
    }
    else if (eType == DBGOPT_TYPE_BOOL)
    {
        sLocVal.bVal = sVal.bVal;
    }
    else
    {
        sLocVal.ui32Val = sVal.ui32Val;
    }

    /* copy the name of the option to kernel memory */
    pszLocName = (IMG_CHAR *) IMG_MALLOC((sStrName.stLen + 1) * sizeof(IMG_CHAR));
    IMG_ASSERT(pszLocName != IMG_NULL);
    if (pszLocName == IMG_NULL)
    {
        rResult = IMG_ERROR_OUT_OF_MEMORY;
        goto clearPszVal;
    }

    rResult = SYSOSKM_CopyFromUser(pszLocName,
                                   sStrName.pszStr,
                                   sStrName.stLen + 1);

    IMG_ASSERT(rResult == IMG_SUCCESS);
    if (rResult != IMG_SUCCESS)
    {
        goto clearPszName;
    }

    /* Set the option; if success then memory pointed by pszLocName
       will be owned by DBGOPTKM */
    rResult = bWithKey ?
              DBGOPTKM_SetWithKey(i32Key, &pszLocName, eType, sLocVal) :
              DBGOPTKM_Set(&pszLocName, eType, sLocVal);

    IMG_ASSERT((rResult == IMG_SUCCESS) || (rResult == IMG_ERROR_ALREADY_INITIALISED));
    if (rResult != IMG_SUCCESS)
    {
        goto clearPszName;
    }

    return rResult;

clearPszName:
    IMG_FREE(pszLocName);
clearPszVal:
    if (eType == DBGOPT_TYPE_STRING)
    {
        IMG_FREE(sLocVal.pszVal);
    }
    else if (eType == DBGOPT_TYPE_BUF)
    {
        IMG_FREE(sLocVal.sBufVal.pvVal);
    }

    return rResult;
}


/*!
******************************************************************************

 @Function      dbgoptbrg_Get

******************************************************************************/
static IMG_UINT64 dbgoptbrg_Get(
    IMG_BOOL                  bWithKey,
    DBGOPT_i32Key             i32Key,
    DBGOPT_sStrWithLen        sStrName,
    SYSBRG_POINTER_ARG(DBGOPT_eType) peType,
    SYSBRG_POINTER_ARG(DBGOPT_sValueBrg) psVal
)
{
    IMG_CHAR *      pszLocName = IMG_NULL;
    DBGOPT_eType    eType;
    DBGOPT_sValue   sVal;
    IMG_RESULT      rResult = IMG_SUCCESS;
    IMG_UINT64      stRet = 0;

    /* check correctness of input parameters */
    IMG_ASSERT(SYSBRG_POINTER_FROM_USER(sStrName.pszStr) != IMG_NULL);
    if (SYSBRG_POINTER_FROM_USER(sStrName.pszStr) == IMG_NULL)
    {
        return stRet;
    }

    /* copy the name of the option to kernel memory */
    pszLocName =
            (IMG_CHAR *) IMG_MALLOC((sStrName.stLen + 1) * sizeof(IMG_CHAR));
    IMG_ASSERT(pszLocName != IMG_NULL);
    if (pszLocName == IMG_NULL)
    {
        return stRet;
    }

    rResult = SYSOSKM_CopyFromUser(pszLocName,
                                   sStrName.pszStr,
                                   sStrName.stLen + 1);

    IMG_ASSERT(rResult == IMG_SUCCESS);
    if (rResult != IMG_SUCCESS)
    {
        IMG_FREE(pszLocName);
        return stRet;
    }

    stRet = bWithKey ?
              DBGOPTKM_GetWithKey(i32Key, pszLocName, &eType, &sVal) :
              DBGOPTKM_Get(pszLocName, &eType, &sVal);

    IMG_FREE(pszLocName);
    if (stRet == 0)
    {
        return stRet;
    }

    if (SYSBRG_POINTER_FROM_USER(peType) != IMG_NULL)
    {
        rResult = SYSOSKM_CopyToUser(peType, &eType, sizeof(eType));
        IMG_ASSERT(rResult == IMG_SUCCESS);
        if (rResult != IMG_SUCCESS)
        {
            return 0;
        }
    }

    if (SYSBRG_POINTER_FROM_USER(psVal) != IMG_NULL)
    {
        if(eType == DBGOPT_TYPE_STRING || eType == DBGOPT_TYPE_BUF)
        {
            /* get user space pointers */
            DBGOPT_sValueBrg sTempVal;
            rResult = SYSOSKM_CopyFromUser(&sTempVal, psVal, sizeof(DBGOPT_sValueBrg));
            IMG_ASSERT(rResult == IMG_SUCCESS);
            if (rResult != IMG_SUCCESS)
            {
                return 0;
            }

            if (eType == DBGOPT_TYPE_STRING)
            {
                IMG_SIZE  stLen;

                if (SYSBRG_POINTER_FROM_USER(sTempVal.sStrVal.pszStr) == IMG_NULL)
                {
                    return 0;
                }

                stLen = strlen(sVal.pszVal);
                sTempVal.sStrVal.stLen = stLen;

                rResult = SYSOSKM_CopyToUser(sTempVal.sStrVal.pszStr, sVal.pszVal, stLen + 1);
                IMG_ASSERT(rResult == IMG_SUCCESS);
                if (rResult != IMG_SUCCESS)
                {
                    return 0;
                }

            }
            else if (eType == DBGOPT_TYPE_BUF)
            {
                if (SYSBRG_POINTER_FROM_USER(sTempVal.sBufVal.pvVal) == IMG_NULL)
                {
                    return 0;
                }

                sTempVal.sBufVal.stSize = sVal.sBufVal.stSize;

                rResult = SYSOSKM_CopyToUser(sTempVal.sBufVal.pvVal,
                                             sVal.sBufVal.pvVal,
                                             sVal.sBufVal.stSize);
                IMG_ASSERT(rResult == IMG_SUCCESS);
                if (rResult != IMG_SUCCESS)
                {
                    return 0;
                }

            }
            rResult = SYSOSKM_CopyToUser(psVal, &sTempVal, sizeof(sTempVal));
            IMG_ASSERT(rResult == IMG_SUCCESS);
            if (rResult != IMG_SUCCESS)
            {
                return 0;
            }
        }
        else
        {
            rResult = SYSOSKM_CopyToUser(psVal, &sVal, sizeof(sVal));
            IMG_ASSERT(rResult == IMG_SUCCESS);
            if (rResult != IMG_SUCCESS)
            {
                return 0;
            }
        }
    }

    return stRet;
}


/*!
******************************************************************************

 @Function      dbgoptbrg_Clear

******************************************************************************/
static IMG_VOID dbgoptbrg_Clear(
    IMG_BOOL           bWithKey,
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName
)
{
    IMG_CHAR *    pszLocName = IMG_NULL;
    IMG_RESULT    rResult;

    /* check correctness of input parameters */
    IMG_ASSERT(SYSBRG_POINTER_FROM_USER(sStrName.pszStr) != IMG_NULL);
    if (SYSBRG_POINTER_FROM_USER(sStrName.pszStr) == IMG_NULL)
    {
        return;
    }

    /* copy the name of the option to kernel memory */
    pszLocName = (IMG_CHAR *) IMG_MALLOC((sStrName.stLen + 1) * sizeof(IMG_CHAR));
    IMG_ASSERT(pszLocName != IMG_NULL);
    if (pszLocName == IMG_NULL)
    {
        goto clearPszName;
    }

    rResult = SYSOSKM_CopyFromUser(pszLocName,
                                   sStrName.pszStr,
                                   sStrName.stLen + 1);

    IMG_ASSERT(rResult == IMG_SUCCESS);
    if (rResult != IMG_SUCCESS)
    {
        goto clearPszName;
    }

    /* Set the option; if success then memory pointed by pszLocName
       will be owned by DBGOPTKM */
    bWithKey ? DBGOPTKM_ClearWithKey(i32Key, pszLocName) :
               DBGOPTKM_Clear(pszLocName);

    IMG_ASSERT(rResult == IMG_SUCCESS);
    if (rResult != IMG_SUCCESS)
    {
        goto clearPszName;
    }

clearPszName:
    IMG_FREE(pszLocName);
}

