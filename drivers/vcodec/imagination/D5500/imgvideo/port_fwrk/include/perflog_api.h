/*!
 *****************************************************************************
 *
 * @File       perflog_api.h
 * @Title      Performance Logger API
 * @Description    This file contains the header file information for the
 *  Performance Logger API
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

#if !defined (__PERFLOG_API_H__)
#define __PERFLOG_API_H__

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#if defined (__cplusplus)
extern "C" {
#endif
/*!
******************************************************************************

 @Function      PERFLOG_Initialise

 @Description

 Allows to initialise Performance Logger API and creates directory
 where logs will be stored

 @Input     None.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code.

******************************************************************************/
IMG_RESULT PERFLOG_Initialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      PERFLOG_Open

 @Description

 Truncates performance file to zero length or create text file for writing.

 @Input     None.

 @Return    None.

******************************************************************************/
IMG_RESULT PERFLOG_Open(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      PERFLOG_WritePerfMsg

 @Description

 Writes performance message to file

 @Input     uiMsg      : performance message

 @Return    IMG_SUCCESS in case when level has been set successfully,
            error code otherwise

******************************************************************************/
IMG_RESULT PERFLOG_WritePerfMsg(
    IMG_UINT64  uiMsg
);


/*!
******************************************************************************

 @Function      PERFLOG_Deinitialise

 @Description

 Deinitialises Performance Logger API

 @Input     None.

 @Return    None.

******************************************************************************/
IMG_VOID PERFLOG_Deinitialise(
    IMG_VOID
);

#if defined (__cplusplus)
}
#endif


#endif /* __REPORT_API_H__  */
