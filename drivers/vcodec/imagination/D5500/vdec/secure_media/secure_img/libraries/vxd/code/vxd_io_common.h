/*!
 *****************************************************************************
 *
 * @File       vxd_io_common.h
 * @Title      Low-level video device interface component
 * @Description    This file contains the interface to communicate with a video device.
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

#if !defined (__VXDIO_COMMON_H__)
#define __VXDIO_COMMON_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_include.h"

#include "secure_defs.h"

#include "vxd_ext.h"
#include "vxd_buf.h"

#include "mem_io.h"
#include "reg_io2.h"

#if  !defined(SECURE_MEDIA_SUPPORT) && !defined(SECURE_TAL)
    #include "tal_setup.h"
    #include "tal_old.h"

#else
    #ifdef TARGET_HEADER_NAME
        #include TARGET_HEADER_NAME
    #else
        #error "Secure build HAS to have a static device header file"
    #endif

	#include "secure_device.h"
#endif

#ifdef WIN32
    //snprintf is not supported by MSVC
    #if _MSC_VER
        //Be aware that the _snprintf does not terminate the string with '\0' if the string goes beyond the buffer
        //but both snprintf and _snprintf return -1 in this case
        #define snprintf _snprintf
    #endif
#endif

#ifdef SYSBRG_BRIDGING

#ifdef SECURE_MEDIA_SUPPORT
#include "mem.h"
// Ensure secure memory is synchronised between host cpu and device
#define UPDATE_DEVICE(hMem, device) MEM_MemoryCpuToDevice((SECURE_MEM_HANDLE)hMem)
#define UPDATE_HOST(hMem, device)   MEM_MemoryDeviceToCpu((SECURE_MEM_HANDLE)hMem)
#else
#include "sysmem_utils.h"
// Ensure insecure memory is synchronised between host cpu and device
#define UPDATE_DEVICE(buf, device) SYSMEMU_UpdateMemory(buf->hMemoryAlloc, CPU_TO_DEV)
#define UPDATE_HOST(buf, device)   SYSMEMU_UpdateMemory(buf->hMemoryAlloc, DEV_TO_CPU)
#endif

#else

#include "talmmu_api.h"
// Update the device/host memory.
#define UPDATE_DEVICE(buf, device) { if(device) { TALMMU_CopyHostToDevMem(buf->hMemory); } }
#define UPDATE_HOST(buf, device)   { if(device) { TALMMU_CopyDevMemToHost(buf->hMemory); } }

#endif

#ifdef SEC_USE_REAL_FW

#define MSVDXIO_MTX_CORE_MEMORY  (0x18) /*!< 0x10 for code, 0x18 for data. */
#define MSVDXIO_TIMEOUT_COUNTER  (1000) /*!< Iteration time out counter for MTX I/0. */

#define MSVDXIO_MTX_CLK_MHZ      (150)  /*!< Set to the actual clock speed the MTX is running at. */

// Limit the bank size search.
#define MSVDXIO_MTX_MIN_BANK_SIZE  256
#define MSVDXIO_MTX_MAX_BANK_SIZE  1048576

/* Number of words needed to enable MTX: two words for setting PC + one word for MTX enable */
#define MSVDXIO_PC_CONF_WORDS 2
#define MSVDXIO_ENABLE_MTX_WORDS 1
#define MSVDXIO_MTX_EN_TOTAL_WORDS (MSVDXIO_ENABLE_MTX_WORDS + MSVDXIO_PC_CONF_WORDS)

/* Maximum number of words needed to fill gap between text and data section.
 * The gap can be there, because data section is 8 bytes aligned .*/
#define MSVDXIO_MTX_TEXT_DATA_SEC_GAP 1

#endif



/*!
******************************************************************************
 This structure contains MTX RAM information.
 @brief  MTX RAM Information
******************************************************************************/
typedef struct
{
    IMG_UINT32 ui32MTXBankSize;
    IMG_UINT32 ui32MTXRamSize;
    IMG_UINT32 ui32MTXRamMask;

} VXDIO_sMTXRamInfo;


/*!
******************************************************************************

 @Function              VXDIO_pfnSetSecRegAccess

 @Description

 This is the prototype of function for enabling secure register access.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Return   none

******************************************************************************/
typedef IMG_VOID    ( * VXDIO_pfnSetSecRegAccess)(const IMG_HANDLE hVxdCtx);

/*!
******************************************************************************

 @Function              VXDIO_pfnPoll

 @Description

 This is the prototype of function for waiting until specific register
 is filled with defined value.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Input    ui32MemRegion   : Memory region to use.

 @Input    ui32Offet       : Offset of register within register region.

 @Input    ui32RequValue   : Required value of register.

 @Input    bEnable         : Whether apply mask before comparing value.

 @Input    bPdump          : Whether to enable pdumping.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT  ( * VXDIO_pfnPoll)(const IMG_HANDLE hVxdCtx,
                                       IMG_UINT32       ui32MemRegion,
                                       IMG_UINT32       ui32Offset,
                                       IMG_UINT32       ui32RequValue,
                                       IMG_UINT32       ui32Enable,
                                       VXDIO_ePollMode  ePollMode);

/*!
******************************************************************************

 @Function              VXDIO_pfnSelectPipe

 @Description

 This is the prototype of function used for selecting HW pipe.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Input    ui8Pipe         : Pipe to select.


 @Return   none.

******************************************************************************/
typedef IMG_VOID  ( * VXDIO_pfnSelectPipe)(const IMG_HANDLE hVxdCtx,
                                           IMG_UINT8        ui8Pipe);

/*!
******************************************************************************

 @Function              VXDIO_pfnGetCoreState

 @Description

 This is the prototype of function for obtaining core state.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Output   psState         : Structure to be updated with core state.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnGetCoreState)(const IMG_HANDLE    hVxdCtx,
                                              VXDIO_sState      * psState);

/*!
******************************************************************************

 @Function              VXDIO_pfnHandleInterrupts

 @Description

 This is the prototype of function for handling core interrupts.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Output   psIntStatus     : Structure with interrupt status to set.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnHandleInterrupts)(const IMG_HANDLE    hVxdCtx,
                                                  VXD_sIntStatus    * psIntStatus);

/*!
******************************************************************************

 @Function              VXDIO_pfnSendFirmwareMessage

 @Description

 This is the prototype of function for sending message to firmware.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Input    eArea           : Type of communication area to use.

 @Input    psMsgHdr        : Buffer with message.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnSendFirmwareMessage)(const IMG_HANDLE    hVxdCtx,
                                                     VXD_eCommsArea      eArea,
                                                     const IMG_VOID    * psMsgHdr);
/*!
******************************************************************************

 @Function              VXDIO_pfnLoadBaseFirmware

 @Description

 This is the prototype of function for loading base firmware component into
 MTX RAM.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Input    eArea           : Type of communication area to use.

 @Input    psMsgHdr        : Buffer with message.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnLoadBaseFirmware)(const IMG_HANDLE hVxdCtx);


/*!
******************************************************************************

 @Function              VXDIO_pfnPrepareFirmware

 @Description

 This is the prototype of function for configuring device specific VXDIO
 device specific context with locations of firmware buffers.
 Firmware authentication and setup related to firmware upload is also
 performed.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Input    hFirmware       : Handle to structure with firmware buffers locations
                             and sizes.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnPrepareFirmware)(const IMG_HANDLE     hVxdCtx,
                                                 const IMG_HANDLE     hFirmware);

/*!
******************************************************************************

 @Function              VXDIO_pfnDisableClocks

 @Description

 This is the prototype of function for disabling device clocks.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnDisableClocks)(const IMG_HANDLE hVxdCtx);

/*!
******************************************************************************

 @Function              VXDIO_pfnEnableClocks

 @Description

 This is the prototype of function for enabling device clocks.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnEnableClocks)(const IMG_HANDLE    hVxdCtx,
                                              IMG_BOOL            bAutoClockGatingSupport,
                                              IMG_BOOL            bExtClockGating,
                                              IMG_BOOL            bForceManual);


/*!
******************************************************************************

 @Function              VXDIO_pfnDeInitialise

 @Description

 This is the prototype of function to deinitialize device-specific VXDIO
 context.

 @Input    ui32CoreNum     : Core number.

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an error
                             code.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnDeInitialise)(IMG_UINT32             ui32CoreNum,
                                              IMG_HANDLE             hVxdCtx);


#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
/*!
******************************************************************************

 @Function              VXDIO_pfnPDUMPSync

 @Description

 This is the prototype of function syncing pdump contexts

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnPDUMPSync)(const IMG_HANDLE    hVxdCtx);
/*!
******************************************************************************

 @Function              VXDIO_pfnPDUMPLock

 @Description

 This is the prototype of function for locking pdump contexts

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnPDUMPLock)(const IMG_HANDLE    hVxdCtx);


/*!
******************************************************************************

 @Function              VXDIO_pfnPDUMPUnLock

 @Description

 This is the prototype of function for unlocking pdump contexts

 @Input    hVxdCtx         : Handle to device-specific VXDIO context.

******************************************************************************/
typedef IMG_RESULT ( * VXDIO_pfnPDUMPUnLock)(const IMG_HANDLE    hVxdCtx);


#endif

/*!
******************************************************************************
 This structure contains core specific callbacks
******************************************************************************/
typedef struct
{
    VXDIO_pfnSetSecRegAccess        pfnSecRegAccess;
    VXDIO_pfnPoll                   pfnPoll;
    VXDIO_pfnSelectPipe             pfnSelectPipe;
    VXDIO_pfnGetCoreState           pfnGetCoreState;
    VXDIO_pfnHandleInterrupts       pfnHandleInterrupts;
    VXDIO_pfnSendFirmwareMessage    pfnSendFirmwareMessage;
    VXDIO_pfnLoadBaseFirmware       pfnLoadBaseFirmware;
    VXDIO_pfnPrepareFirmware        pfnPrepareFirmware;
    VXDIO_pfnDisableClocks          pfnDisableClocks;
    VXDIO_pfnEnableClocks           pfnEnableClocks;
    VXDIO_pfnDeInitialise           pfnDeInitialise;
#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_pfnPDUMPLock              pfnPDUMPLock;
    VXDIO_pfnPDUMPUnLock            pfnPDUMPUnLock;
    VXDIO_pfnPDUMPSync              pfnPDUMPSync;
#endif

} VXDIO_sFunctions;

/*!
******************************************************************************
 This structure describes common context for all video decoder devices.
******************************************************************************/
typedef struct
{
    IMG_BOOL                bInitialised;
    IMG_BOOL                bClocks;                    /*!< Clocks are on/off for the core.        */
    IMG_BOOL                bFakeMtx;                   /*!<                                        */
#ifdef POST_TEST
	IMG_BOOL                bPost;						/*!< POST test is needed if TRUE            */
#endif
#ifdef STACK_USAGE_TEST
	IMG_BOOL                bStackUsageTest;			/*!< Stack usage test is needed if TRUE     */
#endif

    IMG_HANDLE            * pahMemSpace;                /*!< Array of mem spaces handles            */
    IMG_UINT32              ui32MemSpaceCount;          /*!< Count of mem spaces in pahMemSpace     */

    VXDIO_sMTXRamInfo       sMTXRamInfo;                /*!<                                        */

    IMG_HANDLE              hCoreCtx;                   /*!< Core specific context                  */
    VXDIO_sFunctions        sCoreFuncs;                 /*!< Core specific functions.               */

} VXDIO_sContext;



#if defined(__cplusplus)
}
#endif

#endif /* __VXDIO_COMMON_H__ */



