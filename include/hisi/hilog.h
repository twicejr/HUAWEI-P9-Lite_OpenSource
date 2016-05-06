/* Copyright (c) 2008-2015, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __HILOG_H__
#define __HILOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * enum priority - define hisi log proiority.
 */
typedef enum {
    HI_LOG_UNKNOWN = 0,
    HI_LOG_DEFAULT,
    HI_LOG_VERBOSE,
    HI_LOG_DEBUG,
    HI_LOG_INFO,
    HI_LOG_WARN,
    HI_LOG_ERROR,
    HI_LOG_FATAL,
    HI_LOG_SILENT
}Hi_LogPriority;

/**
 * HiLOGE - Macro of print HiLOG error msg.
 */
#ifndef HiLOGE
#define HiLOGE(module, sub_module, fmt, ...) \
    __hi_log_print(HI_LOG_ERROR, module, sub_module, fmt" at (%s:%d - %s)", \
                   ##__VA_ARGS__, __FILE__, __LINE__, __FUNCTION__)
#endif

/* __hi_log_print declare */
int __hi_log_print(const size_t pri, const char* module, const char* sub_module, \
                           const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /*__HILOG_H__*/
