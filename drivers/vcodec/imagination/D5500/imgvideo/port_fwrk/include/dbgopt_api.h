/*!
 *****************************************************************************
 *
 * @File       dbgopt_api.h
 * @Title      The Debug Options bridged
 * @Description    This file contains the header file information for the
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

#if !defined (__DBGOPT_API_H__)
#define __DBGOPT_API_H__


#include <img_types.h>
#include <img_defs.h>

#include "dbgopt_api_um.h"

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef  __RPCCODEGEN__
    #define rpc_prefix      DBGOPTBRG
    #define rpc_filename    dbgopt_api
#endif

/* Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

/*!
******************************************************************************
 This union allows to pass options of various types
******************************************************************************/
typedef struct
{
    SYSBRG_UPOINTER(IMG_CHAR, pszStr);
    SYSBRG_UINT64 stLen;
} DBGOPT_sStrWithLen;

/*!
******************************************************************************
 This union allows to pass options of various types
******************************************************************************/
typedef union
{
    IMG_UINT32          ui32Val;
    IMG_BOOL            bVal;
    DBGOPT_sStrWithLen  sStrVal;
    struct {
        SYSBRG_UPOINTER(IMG_VOID, pvVal);
        SYSBRG_UINT64 stSize;
    } sBufVal;
} DBGOPT_sValueBrg;


/*!
******************************************************************************

 @Function      DBGOPTBRG_Initialise

 @Description

 This function is used to initialise the Debug Options component and should
 be called at start-up.

 @Input     None.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code.

******************************************************************************/
extern IMG_RESULT DBGOPTBRG_Initialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_Deinitialise

 @Description

 This function is used to deinitialise the Debug Options component and should
 be called at shutdown

 @Input     None.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code.

******************************************************************************/
extern IMG_VOID DBGOPTBRG_Deinitialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_Set

 @Description

 This function allows to set the value of debug option of given type.
 Debug options set with this function can be retrieved only with DBGOPT_Get.

 @Input     sStrName :  Name of the option to be set

 @Input     eType :     Type of the passed option

 @Input     sVal :      Value of the passed option

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code in case of any errors

******************************************************************************/
extern IMG_RESULT DBGOPTBRG_Set(
    DBGOPT_sStrWithLen sStrName,
    DBGOPT_eType       eType,
    DBGOPT_sValueBrg   sVal
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_Get

 @Description

 This function allows to get the value of debug option of given name.
 When peType or psVal are passed IMG_NULL then they are simply not returned.

 If type of the option is DBGOPT_TYPE_STRING and psVal passed is not IMG_NULL
 then memory is allocated under psVal->pszVal. This memory has to be freed by
 the user of the DBGOPT_Get function.

 @Input     sStrName    Name of the option to get

 @Output    peType      Type of the option under the pszName (can be omitted)

 @Output    psVal       Value of the retrieved option (can be omitted)

 @Return    IMG_SIZE :    This function returns size of underlying debug
                            option when value of the option has been retrieved
                            successfully, 0 otherwise

******************************************************************************/
extern IMG_UINT64 DBGOPTBRG_Get(
    DBGOPT_sStrWithLen        sStrName,
    SYSBRG_POINTER_ARG(DBGOPT_eType)     peType,
    SYSBRG_POINTER_ARG(DBGOPT_sValueBrg) psVal
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_Clear

 @Description

 This function allows to clear (remove) the value of debug option of given name.

 @Input     sStrName    Name of the option to clear

 @Return    IMG_VOID

******************************************************************************/
extern IMG_VOID DBGOPTBRG_Clear(
    DBGOPT_sStrWithLen sStrName
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_SetWithKey

 @Description

 This function allows to set the value of debug option of given type for given
 value of the key. Debug options set with this function can be retrieved only
 with DBGOPT_GetWithKey function.

 @Input     i32Key :    Value of the key for which option shall be set

 @Input     sStrName :   Name of the option to be set

 @Input     eType :     Type of the passed option

 @Input     sVal :      Value of the passed option

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code in case of any errors

******************************************************************************/
extern IMG_RESULT DBGOPTBRG_SetWithKey(
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName,
    DBGOPT_eType       eType,
    DBGOPT_sValueBrg   sVal
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_GetWithKey

 @Description

 This function allows to get the value of debug option of given name
 for given value of the key.
 When peType or psVal are passed IMG_NULL then they are simply not returned.

 If type of the option is DBGOPT_TYPE_STRING and psVal passed is not IMG_NULL
 then memory is allocated under psVal->pszVal. This memory has to be freed by
 the user of the DBGOPT_Get function.

 @Input     i32Key :    Value of the key for which option shall be retrieved

 @Input     sStrName     Name of the option to get

 @Output    peType      Type of the option under the pszName (can be omitted)

 @Output    psVal       Value of the retrieved option (can be omitted)

 @Return    IMG_SIZE :    This function returns size of underlying debug
                            option when value of the option has been retrieved
                            successfully, 0 otherwise

******************************************************************************/
extern IMG_UINT64 DBGOPTBRG_GetWithKey(
    DBGOPT_i32Key             i32Key,
    DBGOPT_sStrWithLen        sStrName,
    SYSBRG_POINTER_ARG(DBGOPT_eType)     peType,
    SYSBRG_POINTER_ARG(DBGOPT_sValueBrg) psVal
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_ClearWithKey

 @Description

 This function allows to clear (remove) the value of debug option of given
 name and key

 @Input     i32Key :    Value of the key for which option shall be cleared

 @Input     sStrName    Name of the option to clear

 @Return    IMG_VOID

******************************************************************************/
extern IMG_VOID DBGOPTBRG_ClearWithKey(
    DBGOPT_i32Key      i32Key,
    DBGOPT_sStrWithLen sStrName
);


/*!
******************************************************************************

 @Function      DBGOPTBRG_ClearAll

 @Description

 This function allows to clear (remove) the values of all debug options

 @Input     none

 @Return    IMG_VOID

******************************************************************************/
extern IMG_VOID DBGOPTBRG_ClearAll(
IMG_VOID
);


#if defined (__cplusplus)
}
#endif

#endif /* __DBGOPT_API_H__  */

