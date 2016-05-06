/*!
 *****************************************************************************
 *
 * @File       report_levels.h
 * @Title      REPORT LEVELS
 * @Description    This file defines REPORT levels for REPORT API
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

#if !defined (__REPORT_LEVELS_H__)
#define __REPORT_LEVELS_H__


#if defined(__cplusplus)
extern "C" {
#endif


#if defined(IMG_KERNEL_MODULE)

#define REPORT_EMERG    KERN_ERR          /* system is unusable */
#define REPORT_ALERT    KERN_ERR          /* action must be taken immediately */
#define REPORT_CRIT     KERN_ERR          /* critical conditions */
#define REPORT_ERR      KERN_ERR          /* error conditions */
#define REPORT_WARNING  KERN_WARNING      /* warning conditions */
#define REPORT_NOTICE   KERN_INFO         /* normal but significant condition */
#define REPORT_INFO     KERN_INFO         /* informational */

#elif defined(ANDROID)

#define REPORT_EMERG    ANDROID_LOG_FATAL  /* system is unusable */
#define REPORT_ALERT    ANDROID_LOG_FATAL  /* action must be taken immediately */
#define REPORT_CRIT     ANDROID_LOG_ERROR  /* critical conditions */
#define REPORT_ERR      ANDROID_LOG_ERROR  /* error conditions */
#define REPORT_WARNING  ANDROID_LOG_WARN   /* warning conditions */
#define REPORT_NOTICE   ANDROID_LOG_INFO   /* normal but significant condition */
#define REPORT_INFO     ANDROID_LOG_INFO   /* informational */

#else

typedef enum
{
    REPORT_EMERG = 0,  /* system is unusable */
    REPORT_ALERT,      /* action must be taken immediately */
    REPORT_CRIT,       /* critical conditions */
    REPORT_ERR,        /* error conditions */
    REPORT_WARNING,    /* warning conditions */
    REPORT_NOTICE,     /* normal but significant condition */
    REPORT_INFO,       /* informational */
    REPORT_DEBUG,      /* debug-level messages */

    REPORT_NONE,
    REPORT_MAX
} REPORT_eLevel;

#endif /* defined(IMG_KERNEL_MODULE) */


#define REPORT_TEXT_EMERG        "emerg"
#define REPORT_TEXT_ALERT        "alert"
#define REPORT_TEXT_CRIT         "crit"
#define REPORT_TEXT_ERR          "err"
#define REPORT_TEXT_WARNING      "warning"
#define REPORT_TEXT_NOTICE       "notice"
#define REPORT_TEXT_INFO         "info"
#define REPORT_TEXT_DEBUG        "debug"
#define REPORT_TEXT_NONE         "none"


#if defined (__cplusplus)
}
#endif


#endif /* __REPORT_LEVELS_H__  */
