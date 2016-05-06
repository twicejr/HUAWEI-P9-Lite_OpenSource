/*!
 *****************************************************************************
 *
 * @File       dbgopt_api_um.h
 * @Title      The Debug Options user mode API.
 * @Description    This file contains the header file information for the
 *  Debug Options API, usermode part
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

#if !defined (__DBGOPT_API_UM_H__)
#define __DBGOPT_API_UM_H__

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#if defined(__cplusplus)
extern "C" {
#endif


#define DBGOPT_STR_MAX_SIZE 256
#define DBGOPT_STR_MAX_LEN (DBGOPT_STR_MAX_SIZE - 1)


/*!
******************************************************************************
 This enumeration defines option type
******************************************************************************/
typedef enum
{
    DBGOPT_TYPE_NUMBER = 0,
    DBGOPT_TYPE_BOOL,
    DBGOPT_TYPE_STRING,
    DBGOPT_TYPE_BUF,
    /* possibly more to come */

    DBGOPT_TYPE_MAX

} DBGOPT_eType;

/*!
******************************************************************************
 This struct enables DBGOPT API to pass buffers of memory via pointer to void
******************************************************************************/
typedef struct
{
    IMG_VOID *  pvVal;
    IMG_SIZE  stSize;
} DBGOPT_sBuf;

/*!
******************************************************************************
 This union allows to pass options of various types
******************************************************************************/
typedef union
{
    IMG_UINT32  ui32Val;
    IMG_BOOL    bVal;
    IMG_CHAR*   pszVal;
    DBGOPT_sBuf sBufVal;
} DBGOPT_sValue;


/*!
******************************************************************************
 Type of the key to be used in *WithKey functions
******************************************************************************/
typedef IMG_INT32 DBGOPT_i32Key;


/*!
******************************************************************************

 @Function      DBGOPT_Initialise

 @Description

 This function is used to initialise the Debug Options component and should
 be called at start-up.

 @Input     None.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code.

******************************************************************************/
extern IMG_RESULT DBGOPT_Initialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      DBGOPT_Deinitialise

 @Description

 This function is used to deinitialise the Debug Options component and should
 be called at shutdown

 @Input     None.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code.

******************************************************************************/
extern IMG_VOID DBGOPT_Deinitialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      DBGOPT_Set

 @Description

 This function allows to set the value of debug option of given type.
 Debug options set with this function can be retrieved only with DBGOPT_Get.

 @Input     pszName :   Name of the option to be set

 @Input     eType :     Type of the passed option

 @Input     sVal :      Value of the passed option

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code in case of any errors

******************************************************************************/
extern IMG_RESULT DBGOPT_Set(
    const IMG_CHAR * pszName,
    DBGOPT_eType     eType,
    DBGOPT_sValue    sVal
);


/*!
******************************************************************************

 @Function      DBGOPT_GetSize

 @Description

 This function allows to get the size of underlying debug option of given
 name and type.
 If the option is not set then 0 is returned.

 This function can be used in two scenarios:
 1. To check whether the option is set
 2. To get the size of memory which has to be allocated to get the
    options of type DBGOPT_TYPE_STRING and DBGOPT_TYPE_BUF

 @Input     pszName     Name of the option to get the size of

 @Input     eType :     Type of the option

 @Return    IMG_SIZE :    Size of the underlying debug option

******************************************************************************/
extern IMG_SIZE DBGOPT_GetSize(
    const IMG_CHAR * pszName,
    DBGOPT_eType     eType
);


/*!
******************************************************************************

 @Function      DBGOPT_Get

 @Description

 This function allows to get the value of debug option of given name.
 When peType or psVal are passed IMG_NULL then they are simply not returned.

 Usage of this function should be preceded by the call to DBGOPT_GetSize.
 In case of DBGOPT_TYPE_STRING and DBGOPT_TYPE_BUF it is a necessity.
 This way user can prepare (malloc) proper buffer in psVal union.

 @Input     pszName     Name of the option to get

 @Output    peType      Type of the option under the pszName (can be omitted)

 @Output    psVal       Value of the retrieved option (can be omitted)

 @Return    IMG_BOOL :      This function returns IMG_TRUE when value of the
 *                          option has been retrieved successfully, IMG_FALSE
 *                          otherwise

******************************************************************************/
extern IMG_BOOL DBGOPT_Get(
    const IMG_CHAR * pszName,
    DBGOPT_eType *   peType,
    DBGOPT_sValue *  psVal
);


/*!
******************************************************************************

 @Function      DBGOPT_Clear

 @Description

 This function allows to clear (remove) the value of debug option of given name.

 @Input     pszName     Name of the option to clear (remove)

 @Return    IMG_VOID

******************************************************************************/
extern IMG_VOID DBGOPT_Clear(
    const IMG_CHAR * pszName
);


/*!
******************************************************************************

 @Function      DBGOPT_SetWithKey

 @Description

 This function allows to set the value of debug option of given type for given
 value of the key. Debug options set with this function can be retrieved only
 with DBGOPT_GetWithKey function.

 @Input     i32Key :    Value of the key for which option shall be set

 @Input     pszName :   Name of the option to be set

 @Input     eType :     Type of the passed option

 @Input     sVal :      Value of the passed option

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code in case of any errors

******************************************************************************/
extern IMG_RESULT DBGOPT_SetWithKey(
    DBGOPT_i32Key    i32Key,
    const IMG_CHAR * pszName,
    DBGOPT_eType     eType,
    DBGOPT_sValue    sVal
);


/*!
******************************************************************************

 @Function      DBGOPT_GetSizeWithKey

 @Description

 This function allows to get the size of underlying debug option of given
 name and type under given key.
 If the option is not set then 0 is returned.

 This function can be used in two scenarios:
 1. To check whether the option is set
 2. To get the size of memory which has to be allocated to get the
    options of type DBGOPT_TYPE_STRING and DBGOPT_TYPE_BUF

 @Input     i32Key :    Value of the key for which option shall be set

 @Input     pszName     Name of the option to get the size of

 @Input     eType :     Type of the option to get the size of

 @Return    IMG_SIZE :    Size of the underlying debug option

******************************************************************************/
extern IMG_SIZE DBGOPT_GetSizeWithKey(
    DBGOPT_i32Key    i32Key,
    const IMG_CHAR * pszName,
    DBGOPT_eType     eType
);


/*!
******************************************************************************

 @Function      DBGOPT_GetWithKey

 @Description

 This function allows to get the value of debug option of given name
 for given value of the key.
 When peType or psVal are passed IMG_NULL then they are simply not returned.

 Usage of this function should be preceded by the call to DBGOPT_GetSizeWithKey.
 In case of DBGOPT_TYPE_STRING and DBGOPT_TYPE_BUF it is a necessity.
 This way user can prepare (malloc) proper buffer in psVal union.

 @Input     i32Key :    Value of the key for which option shall be retrieved

 @Input     pszName     Name of the option to get

 @Output    peType      Type of the option under the pszName (can be omitted)

 @Output    psVal       Value of the retrieved option (can be omitted)

 @Return    IMG_BOOL :      This function returns IMG_TRUE when value of the
 *                          option has been retrieved successfully, IMG_FALSE
 *                          otherwise

******************************************************************************/
extern IMG_BOOL DBGOPT_GetWithKey(
    DBGOPT_i32Key    i32Key,
    const IMG_CHAR * pszName,
    DBGOPT_eType *   peType,
    DBGOPT_sValue *  psVal
);


/*!
******************************************************************************

 @Function      DBGOPT_ClearWithKey

 @Description

 This function allows to clear (remove) the value of debug option of given name
 given its name and key

 @Input     i32Key :    Value of the key for which option shall be retrieved

 @Input     pszName     Name of the option to clear (remove)

 @Return    IMG_VOID

******************************************************************************/
extern IMG_VOID DBGOPT_ClearWithKey(
    DBGOPT_i32Key    i32Key,
    const IMG_CHAR * pszName
);


/*!
******************************************************************************

 @Function      DBGOPT_ClearAll

 @Description

 This function allows to clear (remove) the values of all debug options

 @Input     none

 @Return    IMG_VOID

******************************************************************************/
extern IMG_VOID DBGOPT_ClearAll(
IMG_VOID
);


#if defined (__cplusplus)
}
#endif

#endif /* __DBGOPT_API_UM_H__  */
