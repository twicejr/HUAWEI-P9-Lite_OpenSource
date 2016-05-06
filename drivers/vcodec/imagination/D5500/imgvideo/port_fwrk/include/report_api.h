/*!
 *****************************************************************************
 *
 * @File       report_api.h
 * @Title      REPORT API
 * @Description    This file contains the header file information for the
 *  REPORT API
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

#if !defined (__REPORT_API_H__)
#define __REPORT_API_H__

/**
 * @page How to use REPORT API
 *
  The goal of REPORT API is to provide consistent way of reporting debug and
  higher level messages across user-space and kernel-space.

  User-space reporting is implemented as printing lines with messages on
  standard error output (stderr) and is done using standard C functions except
  for Android OS where __android_log_print() function is used.

  Kernel-space reporting is currently available for Linux kernel.
  Debug messages are printed using pr_debug function which allows to benefit
  from dynamic debugging interface (http://lwn.net/Articles/434833/,
  http://lwn.net/Articles/434856/). Other messages are printed using standard
  printk.

  For both, user-space and kernel-space, the same reporting interface exits.
  It consists of two macros:
  @li DEBUG_REPORT(MODULE, fmt, ...)
  @li REPORT(MODULE, LEVEL, fmt, ...)
  The arguments can be described as follows:
  @li MODULE - is the module from information comes from; they are defined in report_modules.h file
  @li LEVEL  - is the the level of information significance and meaning; levels are defined in report_levels.h file
  @li fmt    - defines the format message with (optional) format specifiers inside (note that newline character is added automatically to the format message so it shall not be added to fmt argument)
  @li ...    - arguments for format messsage's format specifiers

  In case of REPORT macro one can use one of the following levels:
  @li REPORT_EMERG    - system is unusable
  @li REPORT_ALERT    - action must be taken immediately
  @li REPORT_CRIT     - critical conditions
  @li REPORT_ERR      - error conditions
  @li REPORT_WARNING  - warning conditions
  @li REPORT_NOTICE   - normal but significant condition
  @li REPORT_INFO     - informational
  Although they should not be used directly, two additional reporting levels
  are defined only in user space:
  @li REPORT_DEBUG (only for userspace) - debug-level messages; shall not be used via REPORT macro, only undirectly via DEBUG_REPORT
  @li REPORT_NONE  (only for userspace) - can only be used to disable some logs, see #REPORT_SetLevel() function

  @warning Reporting with REPORT macro, especially in modules designated to
  work in kernel-space, must be well-thought in order to avoid flooding the
  output with messages.
  For debug purposes it is strongly advised to use DEBUG_REPORT macro.
  It is especially profitable in kernel-space because there it is using
  dynamic debugging interface of Linux kernel.

  Examples:
  @code
  DEBUG_REPORT(REPORT_MODULE_DECODER,
               "Decoding %u picture",
               ui32PicNum + 1);

  REPORT(REPORT_MODULE_VDECAPI,
         REPORT_ERR,
         "Submitting the buffer to BSPP failed, reason: %u",
         ui32Result);
  @endcode
 */

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#include <stdarg.h>

#include <report_modules.h>
#include <report_levels.h>


#if defined(IMG_KERNEL_MODULE)
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37)
    #include <linux/printk.h>
#else
    #include <linux/kernel.h>
#endif
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define REPORT_IMG_VDEC_PREFIX "imgvideo"

#if defined(IMG_KERNEL_MODULE)

#define DEBUG_REPORT(MODULE, fmt, ...) \
    do {\
        pr_debug(REPORT_IMG_VDEC_PREFIX ":" MODULE ": " fmt "\n", ##__VA_ARGS__); \
    } while(0)

#define REPORT(MODULE, LEVEL, fmt, ...) \
    do {\
        printk(LEVEL pr_fmt(REPORT_IMG_VDEC_PREFIX ":" MODULE ": " fmt "\n"), ##__VA_ARGS__); \
    } while(0)

#elif defined(ANDROID)
    #include <android/log.h>

#ifdef __RELEASE_DEBUG__
#define DEBUG_REPORT(MODULE, fmt, ...) \
    do {\
    __android_log_print(ANDROID_LOG_DEBUG, REPORT_IMG_VDEC_PREFIX "-" MODULE, fmt, ##__VA_ARGS__); \
    } while(0)
#else
#define DEBUG_REPORT(MODULE, fmt, ...)
#endif

#define REPORT(MODULE, LEVEL, fmt, ...) \
    do {\
        __android_log_print(LEVEL, REPORT_IMG_VDEC_PREFIX "-" MODULE, fmt, ##__VA_ARGS__); \
    } while(0)

#else

#define DEBUG_REPORT(MODULE, fmt, ...) \
    do {\
        REPORT_AddInformation(REPORT_DEBUG, MODULE, fmt, ##__VA_ARGS__); \
    } while(0)

#define REPORT(MODULE, LEVEL, fmt, ...) \
    do {\
        typedef char reporting_level_shall_be_higher_than_REPORT_DEBUG[LEVEL <= REPORT_INFO?1:-1];\
        REPORT_AddInformation(LEVEL, MODULE, fmt, ##__VA_ARGS__); \
    } while(0)


/*!
******************************************************************************

 @Function      REPORT_Initialise

 @Description

 Allows to initialise REPORT API in user space code

 @Input     None.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
                            error code.

******************************************************************************/
IMG_RESULT REPORT_Initialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      REPORT_SetLevel

 @Description

 This function allows to configure logging system by setting level for certain
 module or for all modules (when REPORT_MODULE_ALL is passed as 2nd parameter).

 @Input     eLevel      : minimum level of logged messages

 @Input     eModule     : module which shall be configured

 @Input     None.

 @Return    IMG_SUCCESS in case when level has been set successfully,
            error code otherwise

******************************************************************************/
IMG_RESULT REPORT_SetLevel(
    REPORT_eLevel  eLevel,
    REPORT_eModule eModule
);


/*!
******************************************************************************

 @Function      REPORT_SetLevelByText

 @Description

 This function allows to configure logging system by setting level for certain
 module or for all modules (when REPORT_MODULE_TEXT_ALL is passed as 2nd
 parameter). using textual identifiers.

 @Input     pszLevel      : minimum level of logged messages

 @Input     pszModule     : module which shall be configured

 @Input     None.

 @Return    IMG_SUCCESS in case when level has been set successfully,
            error code otherwise

******************************************************************************/
IMG_RESULT REPORT_SetLevelByText(
    const IMG_CHAR *  pszLevel,
    const IMG_CHAR *  pszModule
);


/*!
******************************************************************************

 @Function      REPORT_Deinitialise

 @Description

 Deinitialises REPORT API

 @Input     None.

 @Return    None.

******************************************************************************/
IMG_VOID REPORT_Deinitialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function      REPORT_AddInformation

 @Description

 Allows to print report information (debug log or other message)

 @Warning: This function shall not be used directly, only through
           REPORT and DEBUG_REPORT macros

 @Input     eLevel      : level of message

 @Input     eModule     : module from which the message comes from

 @Input     pszFmt      : format message

 @Input     ...         : arguments suitable for pszFmt

 @Return    None.

******************************************************************************/
IMG_VOID REPORT_AddInformation(
    REPORT_eLevel    eLevel,
    REPORT_eModule   eModule,
    const IMG_CHAR * pszFmt,
    ...
);

#endif


#if defined (__cplusplus)
}
#endif


#endif /* __REPORT_API_H__  */
