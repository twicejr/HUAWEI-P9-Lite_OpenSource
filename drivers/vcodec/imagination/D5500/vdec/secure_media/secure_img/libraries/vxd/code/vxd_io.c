/*!
 *****************************************************************************
 *
 * @File       vxd_io.c
 * @Title      Low-level MSVDX secure hardware access component
 * @Description    This file contains functions to communicate with an MSVDX core.
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

#include "img_include.h"
#include "img_defs.h"

#include "lst.h"
#include "tal.h"

#ifdef SECURE_MEDIA_REPORTING
#include "report_api.h"
#else
#define REPORT(MODULE, LEVEL, fmt, ...)
#define DEBUG_REPORT(MODULE, fmt, ...)
#endif

#include "vxd.h"
#include "vxd_io_common.h"
#include "vxd_io.h"
#include "target.h"
#ifdef VDEC_USE_PVDEC
#include "pvdec_io.h"
#else /* ndef VDEC_USE_PVDEC */
#include "msvdx_io.h"
#include "msvdx_ext.h"
#include "mtxio.h"
#endif /* ndef VDEC_USE_PVDEC */

static IMG_UINT32 ui32NumOfCoresInit = 0;

/*
******************************************************************************

 @Function              VXDIO_GetHandle

******************************************************************************/
IMG_HANDLE
VXDIO_GetHandle(
    const IMG_CHAR    * pszPrefix,
    IMG_CHAR          * pszMemSpceName
)
{
    IMG_CHAR acMemSpceName[VXDIO_MEMSPACE_PREFIX_MAX + VXDIO_MEMSPACE_NAME_MAX];

    IMG_STRNCPY(acMemSpceName, pszPrefix, VXDIO_MEMSPACE_PREFIX_MAX);
    strncat(acMemSpceName, pszMemSpceName, VXDIO_MEMSPACE_NAME_MAX);

    return TAL_GetMemSpaceHandle(acMemSpceName);
}

/*!
******************************************************************************

 @Function              VXDIO_ReadRegister

******************************************************************************/
IMG_UINT32
VXDIO_ReadRegister(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT8           ui8Pipe
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_UINT32          ui32Value = 0;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        goto error;
    }

    IMG_ASSERT(psVxdCtx->ui32MemSpaceCount != 0);
    if (ui32MemRegion >= psVxdCtx->ui32MemSpaceCount)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VXD memory region must be provided");
        goto error;
    }

    IMG_ASSERT(psVxdCtx->bInitialised);

    if (psVxdCtx->bClocks)
    {
        if (psVxdCtx->sCoreFuncs.pfnSelectPipe != IMG_NULL)
        {
            psVxdCtx->sCoreFuncs.pfnSelectPipe(psVxdCtx->hCoreCtx, ui8Pipe);
        }

#ifdef SECURE_CPU_REG_ACCESS
        IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnSecRegAccess != IMG_NULL);
        psVxdCtx->sCoreFuncs.pfnSecRegAccess(psVxdCtx->hCoreCtx);
#endif
        TALREG_ReadWord32(psVxdCtx->pahMemSpace[ui32MemRegion], ui32Offset, &ui32Value);
    }
    else
    {
        REPORT(REPORT_MODULE_VXDIO,
               REPORT_NOTICE,
               "Didn't READ register while clocks are turned off");
    }

    return ui32Value;

error:
    return 0;
}


#ifdef STACK_USAGE_TEST
/*!
******************************************************************************

 @Function              VXDIO_GetStackUsage

******************************************************************************/
extern IMG_RESULT
VXDIO_GetStackUsage(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32        * paui32StackInfoArray
)
{
    IMG_RESULT rResult = IMG_SUCCESS;

#ifdef VDEC_MSVDX_HARDWARE

    /* call realted MSVDX function */
    rResult = MSVDXIO_GetStackUsage(hVxdCtx, paui32StackInfoArray);

#else

    /* do nothing. should never arrive here */
    /* check and related error is performed before this function calla the moment */

#endif

    return rResult;
}
#endif


/*!
******************************************************************************

 @Function              VXDIO_WriteRegister

******************************************************************************/
IMG_RESULT
VXDIO_WriteRegister(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32Value,
    IMG_UINT32          ui32Mask,
    IMG_UINT8           ui8Pipe
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_UINT32          ui32Result;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(psVxdCtx->ui32MemSpaceCount != 0);
    if (ui32MemRegion >= psVxdCtx->ui32MemSpaceCount)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VXD memory region must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(psVxdCtx->bInitialised);

    if (psVxdCtx->bClocks)
    {
        IMG_UINT32 ui32RegValue;

        if (psVxdCtx->sCoreFuncs.pfnSelectPipe != IMG_NULL)
        {
            psVxdCtx->sCoreFuncs.pfnSelectPipe(psVxdCtx->hCoreCtx, ui8Pipe);
        }

        if (ui32Mask != -1)
        {
            TALREG_ReadWord32(psVxdCtx->pahMemSpace[ui32MemRegion], ui32Offset, &ui32RegValue);
            ui32RegValue &= ~ui32Mask;
            ui32RegValue |= ui32Value;
        }
        else
        {
            ui32RegValue = ui32Value;
        }
#ifdef SECURE_CPU_REG_ACCESS
        {
        IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnSecRegAccess != IMG_NULL);
        psVxdCtx->sCoreFuncs.pfnSecRegAccess(psVxdCtx->hCoreCtx);
        }
#endif
        TALREG_WriteWord32(psVxdCtx->pahMemSpace[ui32MemRegion], ui32Offset, ui32RegValue);
    }
    else
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_NOTICE,
            "Didn't WRITE register while clocks are turned off");
        ui32Result = IMG_ERROR_NOT_INITIALISED;
        goto error;
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              VXDIO_VLRWriteWords

******************************************************************************/
IMG_RESULT
VXDIO_VLRWriteWords(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Addr,
    IMG_UINT32          ui32NumWords,
    const IMG_UINT32  * pui32Values
)
{
    VXDIO_sContext    * psVxdCtx = (VXDIO_sContext *)hVxdCtx;
    IMG_UINT32          ui32WordCnt;
    IMG_UINT32          ui32Result;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

#if 0
    if (ui32MemRegion != REGION_VLR_REGSPACE &&
        ui32MemRegion != REGION_VLRFE_REGSPACE &&
        ui32MemRegion != REGION_VLRBE_REGSPACE)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VLR memory space must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }
#endif

    if ((ui32Addr & 0x3) != 0 ||
        ui32NumWords == 0 ||
        pui32Values == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VLR location (offset word aligned) must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    // Repeat for all words.
    for (ui32WordCnt = 0; ui32WordCnt < ui32NumWords; ui32WordCnt++)
    {
#ifdef SECURE_CPU_REG_ACCESS
        {
            IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnSecRegAccess != IMG_NULL);
            psVxdCtx->sCoreFuncs.pfnSecRegAccess(psVxdCtx->hCoreCtx);
        }
#endif
        ui32Result = TALREG_WriteWord32(psVxdCtx->pahMemSpace[ui32MemRegion],
                                        ui32Addr,
                                        *pui32Values);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        pui32Values++;
        ui32Addr += 4;
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}


/*!
******************************************************************************

 @Function              VXDIO_VLRReadWords

******************************************************************************/
IMG_RESULT
VXDIO_VLRReadWords(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Addr,
    IMG_UINT32          ui32NumWords,
    IMG_UINT32        * pui32Values,
    IMG_BOOL            bValidate
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_UINT32          ui32WordCnt = 0;
    IMG_UINT32          ui32Result = IMG_SUCCESS;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

#if 0
    if (ui32MemRegion != REGION_VLR_REGSPACE &&
        ui32MemRegion != REGION_VLRFE_REGSPACE &&
        ui32MemRegion != REGION_VLRBE_REGSPACE)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VLR memory space must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }
#endif

    if ((ui32Addr & 0x3) != 0 ||
        ui32NumWords == 0 ||
        pui32Values == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VLR location (offset word aligned) must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    // Repeat for all words.
    for (ui32WordCnt = 0; ui32WordCnt < ui32NumWords; ui32WordCnt++)
    {
#ifdef SECURE_CPU_REG_ACCESS
        {
            IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnSecRegAccess != IMG_NULL);
            psVxdCtx->sCoreFuncs.pfnSecRegAccess(psVxdCtx->hCoreCtx);
        }
#endif

        ui32Result = TALREG_ReadWord32(psVxdCtx->pahMemSpace[ui32MemRegion],
                                       ui32Addr,
                                       pui32Values);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
        if (bValidate)
        {
            IMG_UINT32 ui32Mask = 0xFFFFFFFF;
            ui32Result = VXDIO_PDUMPVerifPoll(psVxdCtx,
                                              ui32MemRegion,
                                              ui32Addr,
                                              *pui32Values,
                                              ui32Mask);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
        }
#endif

        pui32Values++;
        ui32Addr += 4;
    }

error:

    return ui32Result;
}


/*!
******************************************************************************

 @Function              VXDIO_Poll

******************************************************************************/
IMG_RESULT
VXDIO_Poll(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32RequValue,
    IMG_UINT32          ui32Enable,
    VXDIO_ePollMode     ePollMode
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnPoll != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnPoll(psVxdCtx->hCoreCtx,
                                        ui32MemRegion,
                                        ui32Offset,
                                        ui32RequValue,
                                        ui32Enable,
                                        ePollMode);
}

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
/*!
******************************************************************************

 @Function              VXDIO_PDUMPVerifPoll

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPVerifPoll(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32RequValue,
    IMG_UINT32          ui32Enable
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_RESULT          eResult;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    eResult = TALREG_Poll32(psVxdCtx->pahMemSpace[ui32MemRegion],
                            ui32Offset,
                            TAL_CHECKFUNC_ISEQUAL,
                            ui32RequValue,
                            ui32Enable,
                            5,
                            1);
    IMG_ASSERT(eResult == IMG_SUCCESS);
    return eResult;
}

/*!
******************************************************************************

 @Function              VXDIO_PDUMPComment

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPComment(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    const IMG_CHAR *    pszComment
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Invalid parameters provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    TALPDUMP_Comment( psVxdCtx->pahMemSpace[ui32MemRegion], pszComment );

    return IMG_SUCCESS;
}
/*!
******************************************************************************

 @Function              VXDIO_PDUMPSync

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPSync(
    const IMG_HANDLE    hVxdCtx
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Invalid parameters provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnPDUMPSync != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnPDUMPSync(psVxdCtx->hCoreCtx);
}

/*!
******************************************************************************

 @Function              VXDIO_PDUMPLock

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPLock(
    const IMG_HANDLE    hVxdCtx
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Invalid parameters provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnPDUMPLock != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnPDUMPLock(psVxdCtx->hCoreCtx);

}

/*!
******************************************************************************

 @Function              VXDIO_PDUMPUnLock

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPUnLock(
    const IMG_HANDLE    hVxdCtx
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Invalid parameters provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnPDUMPUnLock != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnPDUMPUnLock(psVxdCtx->hCoreCtx);
}

/*!
******************************************************************************

 @Function              VXDIO_PDUMPPollCircBuff

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPPollCircBuff(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32WriteOffsetVal,
    IMG_UINT32          ui32PacketSize,
    IMG_UINT32          ui32BufferSize
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_RESULT          eResult;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Invalid parameters provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    eResult = TALREG_CircBufPoll32(psVxdCtx->pahMemSpace[ui32MemRegion],
                                   ui32Offset,
                                   ui32WriteOffsetVal,
                                   ui32PacketSize,
                                   ui32BufferSize,
                                   1000000,
                                   100);
    IMG_ASSERT(eResult == IMG_SUCCESS);
    return eResult;
}

/*!
******************************************************************************

 @Function              VXDIO_PDUMPDisableCmds

******************************************************************************/
IMG_UINT32
VXDIO_PDUMPDisableCmds(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32DisableFlags
)
{
    VXDIO_sContext *psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    IMG_ASSERT(psVxdCtx != IMG_NULL);
    IMG_ASSERT(psVxdCtx->ui32MemSpaceCount != 0);

    if (ui32MemRegion >= psVxdCtx->ui32MemSpaceCount)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VXD memory region must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    TALPDUMP_DisableCmds(psVxdCtx->pahMemSpace[ui32MemRegion],
        ui32Offset, ui32DisableFlags);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              VXDIO_PDUMPGetDisableCmds

******************************************************************************/
IMG_UINT32
VXDIO_PDUMPGetDisableCmds(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset
)
{
    VXDIO_sContext *psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    IMG_ASSERT(psVxdCtx != IMG_NULL);
    IMG_ASSERT(psVxdCtx->ui32MemSpaceCount != 0);

    if (ui32MemRegion >= psVxdCtx->ui32MemSpaceCount)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid VXD memory region must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    return TALPDUMP_GetDisableCmds(psVxdCtx->pahMemSpace[ui32MemRegion], ui32Offset);
}

#endif /* !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING) */

/*!
******************************************************************************

 @Function              VXDIO_GetCoreState

******************************************************************************/
IMG_RESULT
VXDIO_GetCoreState(
    const IMG_HANDLE    hVxdCtx,
    VXDIO_sState      * psState
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (psState == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid state context must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnGetCoreState != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnGetCoreState(psVxdCtx->hCoreCtx,
                                                psState);
}


/*!
******************************************************************************

 @Function              VXDIO_HandleInterrupts

******************************************************************************/
IMG_UINT32
VXDIO_HandleInterrupts(
    const IMG_HANDLE      hVxdCtx,
    VXD_sIntStatus      * psIntStatus
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (psIntStatus == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A valid interrupt status context must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnHandleInterrupts != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnHandleInterrupts(psVxdCtx->hCoreCtx,
                                                    psIntStatus);
}


/*!
******************************************************************************

 @Function              VXDIO_SendFirmwareMessage

******************************************************************************/
IMG_RESULT
VXDIO_SendFirmwareMessage(
    const IMG_HANDLE         hVxdCtx,
    VXD_eCommsArea           eArea,
    const IMG_VOID         * psMsgHdr
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (psMsgHdr == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnSendFirmwareMessage != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnSendFirmwareMessage(psVxdCtx->hCoreCtx,
                                                       eArea,
                                                       psMsgHdr);

}


/*!
******************************************************************************

 @Function              VXDIO_LoadBaseFirmware

******************************************************************************/
IMG_RESULT
VXDIO_LoadBaseFirmware(
    const IMG_HANDLE      hVxdCtx
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnLoadBaseFirmware != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnLoadBaseFirmware(psVxdCtx->hCoreCtx);

}


/*!
******************************************************************************

 @Function              VXDIO_PrepareFirmware

******************************************************************************/
IMG_RESULT
VXDIO_PrepareFirmware(
    const IMG_HANDLE     hVxdCtx,
    const IMG_HANDLE     hFirmware
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnPrepareFirmware != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnPrepareFirmware(psVxdCtx->hCoreCtx,
                                                   hFirmware);

}


/*!
******************************************************************************

 @Function              VXDIO_DisableClocks

******************************************************************************/
IMG_RESULT
VXDIO_DisableClocks(
    const IMG_HANDLE    hVxdCtx
)
{
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnDisableClocks != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnDisableClocks(psVxdCtx->hCoreCtx);
}


/*!
******************************************************************************

 @Function              VXDIO_EnableClocks

******************************************************************************/
IMG_RESULT
VXDIO_EnableClocks(
    const IMG_HANDLE    hVxdCtx,
    IMG_BOOL            bAutoClockGatingSupport,
    IMG_BOOL            bExtClockGating,
    IMG_BOOL            bForceManual
)
{
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnEnableClocks != IMG_NULL);
    return psVxdCtx->sCoreFuncs.pfnEnableClocks(psVxdCtx->hCoreCtx,
                                                bAutoClockGatingSupport,
                                                bExtClockGating,
                                                bForceManual);
}
/*
******************************************************************************

 @Function              VXDIO_Initialise

******************************************************************************/
IMG_RESULT
VXDIO_DeInitialise(
    IMG_UINT32          ui32CoreNum,
    IMG_HANDLE          hVxdCtx
)
{
    VXDIO_sContext    * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_UINT32          ui32Result;

    if (hVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(psVxdCtx->sCoreFuncs.pfnDeInitialise != IMG_NULL);
    ui32Result = psVxdCtx->sCoreFuncs.pfnDeInitialise(ui32CoreNum,
                                                      psVxdCtx->hCoreCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

#ifdef VXD_BRIDGING
    ui32NumOfCoresInit = ui32NumOfCoresInit > 0 ? ui32NumOfCoresInit-1 : 0;
    if (ui32NumOfCoresInit == 0)
    {
#ifdef SECURE_TAL
#ifdef VDEC_USE_PVDEC
        ui32Result = TAL_DeviceUnRegister("PVDEC");
#else /* ndef VDEC_USE_PVDEC */
        ui32Result = TAL_DeviceUnRegister("MSVDX");
#endif /* ndef VDEC_USE_PVDEC */
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
#else /* ndef SECURE_TAL */
        ui32Result = TALSETUP_Deinitialise();
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
#endif /* ndef SECURE_TAL */

#ifdef SECURE_TAL
        ui32Result = TARGET_Deinitialise(&gsTargetConfig);
        SECDEV_DeInitialise(SECDEV_MAPAREA_REGISTER);
#else /* ndef SECURE_TAL */
        ui32Result = TARGET_Deinitialise(IMG_NULL);
#endif /* ndef SECURE_TAL */
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
    }
#endif

    IMG_FREE(psVxdCtx);

    return IMG_SUCCESS;

error:
    return ui32Result;
}

/*
******************************************************************************

 @Function              VXDIO_Initialise

******************************************************************************/
IMG_RESULT
VXDIO_Initialise(
    IMG_BOOL            bFakeMtx,
    IMG_BOOL            bPost,
    IMG_BOOL            bStackUsageTest,
    IMG_UINT32          ui32CoreNum,
    IMG_HANDLE        * phVxdCtx
)
{
    IMG_RESULT          ui32Result;
    VXDIO_sContext    * psVxdCtx;
#ifdef SECURE_TAL
    SECURE_sDev         sDevInfo;
#endif

    if (phVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An video decoder device context handle must be provided (%d)", __LINE__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psVxdCtx = IMG_MALLOC(sizeof(*psVxdCtx));
    IMG_ASSERT(psVxdCtx);
    if (psVxdCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
            "Failed to allocate memory for VXDIO context");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psVxdCtx, 0, sizeof(*psVxdCtx));
    *phVxdCtx = psVxdCtx;


    if (ui32NumOfCoresInit == 0)
    {
#ifdef SECURE_TAL
        IMG_UINT32 i;
        for(i = 0; i < gsTargetConfig.ui32DevNum; i++)
        {
            sDevInfo.pszDeviceName = gsTargetConfig.pasDevices[i].pszDeviceName;

            ui32Result = SECDEV_Initialise();
            if(ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
            ui32Result = SECDEV_LocateDevice(&sDevInfo, SECDEV_MAPAREA_REGISTER);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
            gsTargetConfig.pasDevices[i].pvKmRegBase = sDevInfo.pvKmRegBase;
            gsTargetConfig.pasDevices[i].ui32RegSize = sDevInfo.ui32RegSize;
        }

        TARGET_Initialise(&gsTargetConfig);
#else
        TARGET_Initialise(IMG_NULL);
#endif
    }

#ifndef VDEC_USE_PVDEC
#ifdef POST_TEST
#ifdef STACK_USAGE_TEST
        ui32Result = MSVDXIO_Initialise(bFakeMtx,
                                        bPost,
                                        bStackUsageTest,
                                        ui32CoreNum,
                                        (IMG_HANDLE)psVxdCtx,
                                        &psVxdCtx->hCoreCtx);
#else /* ndef STACK_USAGE_TEST */
        /* POST required only */
        ui32Result = MSVDXIO_Initialise(bFakeMtx,
                                        bPost,
                                        IMG_FALSE,
                                        ui32CoreNum,
                                        (IMG_HANDLE)psVxdCtx,
                                        &psVxdCtx->hCoreCtx);
#endif /* ndef STACK_USAGE_TEST */
#else /* ndef POST_TEST */
#ifdef STACK_USAGE_TEST
        /* STACK USAGE TEST required only */
        ui32Result = MSVDXIO_Initialise(bFakeMtx,
                                        IMG_FALSE,
                                        bStackUsageTest,
                                        ui32CoreNum,
                                        (IMG_HANDLE)psVxdCtx,
                                        &psVxdCtx->hCoreCtx);
#else /* ndef STACK_USAGE_TEST */
        /* POST and STACK USAGE TEST not required */
        ui32Result = MSVDXIO_Initialise(bFakeMtx,
                                        IMG_FALSE,
                                        IMG_FALSE,
                                        ui32CoreNum,
                                        (IMG_HANDLE)psVxdCtx,
                                        &psVxdCtx->hCoreCtx);
#endif /* ndef STACK_USAGE_TEST */
#endif /* ndef POST_TEST */
#else /*def VDEC_USE_PVDEC */
        ui32Result = PVDECIO_Initialise(bFakeMtx,
                                        ui32CoreNum,
                                        (IMG_HANDLE)psVxdCtx,
                                        &psVxdCtx->hCoreCtx);
#endif /* def VDEC_USE_PVDEC */

    return ui32Result;

#ifdef SECURE_TAL
error:
    IMG_FREE(psVxdCtx);
    *phVxdCtx = IMG_NULL;
    return ui32Result;
#endif /* SECURE_TAL */
}

/*!
******************************************************************************

 @Function              VXDIO_GetMemSpaceOffset

******************************************************************************/
IMG_RESULT
VXDIO_GetMemSpaceOffset(
    IMG_HANDLE               hVxdCtx,
    IMG_UINT32               ui32MemRegion,
    IMG_UINT64             * pui64MemSpaceOffset
)
{
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    return TAL_GetMemSpaceOffset(psVxdCtx->pahMemSpace[ui32MemRegion], pui64MemSpaceOffset);
}

/*!
******************************************************************************

 @Function              VXDIO_GetMemSpaces

******************************************************************************/
IMG_RESULT
VXDIO_GetMemSpacesHandles(IMG_UINT32          ui32CoreNum,
                          IMG_HANDLE       ** ppahMemSpace
)
{
#ifdef VDEC_USE_PVDEC
    *ppahMemSpace = IMG_MALLOC(REGION_PVDEC_MAX * sizeof(IMG_HANDLE));
    if (*ppahMemSpace == IMG_NULL)
    {
        return IMG_ERROR_MALLOC_FAILED;
    }
    IMG_MEMSET(*ppahMemSpace, 0, REGION_PVDEC_MAX * sizeof(IMG_HANDLE));
    return PVDECIO_GetMemSpaces(ui32CoreNum, *ppahMemSpace);
#else /* ndef VDEC_USE_PVDEC */
    return IMG_ERROR_NOT_SUPPORTED;
#endif /* ndef VDEC_USE_PVDEC */

}

/*!
******************************************************************************

 @Function              VXDIO_TriggerSim

******************************************************************************/
IMG_VOID
VXDIO_TriggerSim(
    const IMG_HANDLE    hVxdCtx
)
{
#ifdef VDEC_USE_PVDEC
    const IMG_UINT32 ui32RegOffset = 0;
    IMG_UINT32 ui32I = 1000;

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    /* Disable RDW PDUMP for VLR ui32RegOffset */
    IMG_UINT32 ui32DisableFlags;
    ui32DisableFlags = VXDIO_PDUMPGetDisableCmds(hVxdCtx,
        REGION_PVDEC_VLR_REGSPACE , ui32RegOffset);
    VXDIO_PDUMPDisableCmds(hVxdCtx, REGION_PVDEC_VLR_REGSPACE, ui32RegOffset,
        ui32DisableFlags | TAL_DISABLE_CAPTURE_RDW);
#endif

    while (ui32I-- > 0)
    {
        VXDIO_ReadRegister(hVxdCtx, REGION_PVDEC_VLR_REGSPACE, ui32RegOffset, 0);
    }

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    /* Restore PDUMP disable flags for VLR ui32RegOffset */
    VXDIO_PDUMPDisableCmds(hVxdCtx, REGION_PVDEC_VLR_REGSPACE, ui32RegOffset,
        ui32DisableFlags);
#endif

#endif /* VDEC_USE_PVDEC */
}

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)
/*!
******************************************************************************

 @Function              VXDIO_ProcessDebugData

******************************************************************************/
IMG_VOID
VXDIO_ProcessDebugData(
    const IMG_HANDLE    hVxdCtx
)
{
#ifdef VDEC_USE_PVDEC
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_ASSERT(psVxdCtx != IMG_NULL);
    PVDECIO_HandleDebugFifo(psVxdCtx->hCoreCtx);
#endif /* VDEC_USE_PVDEC */
}

/*!
******************************************************************************

 @Function              VXDIO_EnableDebugFifo

******************************************************************************/
IMG_VOID
VXDIO_EnableDebugFifo(
    const IMG_HANDLE    hVxdCtx
)
{
#ifdef VDEC_USE_PVDEC
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_ASSERT(psVxdCtx != IMG_NULL);
    PVDECIO_EnableDebugFifo(psVxdCtx->hCoreCtx);
#endif /* VDEC_USE_PVDEC */
}

/*!
******************************************************************************

 @Function              VXDIO_DisableDebugFifo

******************************************************************************/
IMG_VOID
VXDIO_DisableDebugFifo(
    const IMG_HANDLE    hVxdCtx
)
{
#ifdef VDEC_USE_PVDEC
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_ASSERT(psVxdCtx != IMG_NULL);
    PVDECIO_DisableDebugFifo(psVxdCtx->hCoreCtx);
#endif /* VDEC_USE_PVDEC */
}

/*!
******************************************************************************

 @Function              VXDIO_GetDebugFifoSize

******************************************************************************/
IMG_UINT32
VXDIO_GetDebugFifoSize(
    const IMG_HANDLE    hVxdCtx
)
{
#ifdef VDEC_USE_PVDEC
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_ASSERT(psVxdCtx != IMG_NULL);
    return PVDECIO_GetDebugFifoSize(psVxdCtx->hCoreCtx);
#else /* ndef VDEC_USE_PVDEC */
    return 0;
#endif /* ndef VDEC_USE_PVDEC */
}
#endif /* !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG) */

/*!
******************************************************************************

 @Function              VXDIO_ClocksEnabled

******************************************************************************/
IMG_BOOL
VXDIO_ClocksEnabled(
    const IMG_HANDLE    hVxdCtx
)
{
    VXDIO_sContext * psVxdCtx  = (VXDIO_sContext *)hVxdCtx;
    IMG_ASSERT(hVxdCtx != IMG_NULL);
    return psVxdCtx->bClocks;
}

/* EOF */
