/*!
 *****************************************************************************
 *
 * @File       pvdec_int.c
 * @Title      Low-level PVDEC interface component
 * @Description    This file contains functions to interface with an PVDEC core.
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
#include "talmmu_api.h"
#include "pvdec_int.h"
#include "pvdec_msg.h"
#include "pvdec_ctx.h"
#include "pvdec_ext_reg.h"
#include "vxd_io.h"
#include "vdecdd_mmu.h"

#include "tal.h"

#include "sysos_api_km.h"
#include "report_api.h"
#include "dbgopt_api_km.h"

#ifdef SECURE_MEDIA_SUPPORT
    #include "secureapi.h"
    #include "vxd_secure_msg.h"
#else
    #include "tal.h"
    #include "vxd_io.h"
#endif

#include "reg_io2.h"

#include "hwdefs/msvdx_mtx_regs.h"
#include "hwdefs/pvdec_core_regs.h"
#include "hwdefs/pvdec_pixel_regs.h"
#include "hwdefs/img_video_bus4_mmu_regs.h"
#include "hwdefs/pvdec_entropy_regs.h"
#include "hwdefs/pvdec_test_regs.h"

#define GET_BITS(v, lb, n)   ((v >> lb) & ((1 << n) - 1))

#define PVDECIO_MTX_CLK_MHZ  200

/*!
******************************************************************************
 This structure is used to describe version of PVDEC core.
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32MajRev;    /*!< VXD Core major revision.        */
    IMG_UINT32  ui32MinRev;    /*!< VXD Core minor revision.        */
    IMG_UINT32  ui32MaintRev;  /*!< VXD Core maintenance revision.  */
    IMG_UINT32  ui32IntRev;    /*!< VXD internal revision.          */

} PVDEC_sCoreRev;

/*!
******************************************************************************
 PVDEC core version information (for use of revision macro).
 NOTE: It is assumed that all cores on a device are the same revision.
******************************************************************************/
static IMG_UINT32  ui32MajRev;    /*!< VXD Core major revision.        */
static IMG_UINT32  ui32MinRev;    /*!< VXD Core minor revision.        */
static IMG_UINT32  ui32MaintRev;  /*!< VXD Core maintenance revision.  */


/*!
******************************************************************************
 This array defines the properties of each video standard for various core
 versions (and on). TRM 1.1: 4k for all but HEVC and JPEG

 D5500      7.0.0

*****************************************************************************/
static VXD_sVidStdProps asStdProps[] =
{
    { VDEC_STD_MPEG2,       CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_MPEG4,       CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_H263,        CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_H264,        CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0x10000,  8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_VC1,         CORE_REVISION(7,0,0), 80, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_AVS,         CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_REAL,        CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_JPEG,        CORE_REVISION(7,0,0), 64, 16, 32768, 32768, 0,      8, 8, PIXEL_FORMAT_444 },

    { VDEC_STD_VP6,         CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_VP8,         CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_SORENSON,    CORE_REVISION(7,0,0), 64, 16, 4096, 4096, 0,        8, 8, PIXEL_FORMAT_420 },

    { VDEC_STD_HEVC,        CORE_REVISION(7,0,0), 64, 16, 8192, 8192, 0,        8, 8, PIXEL_FORMAT_420 },
};



#ifndef SYSBRG_BRIDGING
/*
******************************************************************************

 @Function              pvdec_CheckInterruptFunc

 @Description

 Check interrupt function.

******************************************************************************/
static IMG_BOOL pvdec_CheckInterruptFunc(
    IMG_HANDLE  ui32MemSpaceId,
    IMG_VOID *  pCallbackParameter
)
{
    IMG_UINT32        ui32IntStatus = 0;
    PVDEC_sContext  * psContext = (PVDEC_sContext *)pCallbackParameter;

    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* Read the status register. */
    ui32IntStatus = REGIO_READ_REGISTER(psContext, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_STATUS);

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)
    VXDIO_ProcessDebugData(psContext->hDev);
#endif

    if (psContext->bCSim)
    {
        VXDIO_TriggerSim(psContext->hDev);
    }

    /* Re enable interrupts */
    SYSOSKM_EnableInt();

    return (ui32IntStatus != 0);
}
#endif /* not SYSBRG_BRIDGING */


/*!
******************************************************************************

 @Function              PVDEC_SendFirmwareMessage

******************************************************************************/
IMG_RESULT PVDEC_SendFirmwareMessage(
    const IMG_HANDLE    hVxd,
    VXD_eCommsArea      eArea,
    const IMG_VOID    * psMsgHdr
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT32        ui32Result;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    psPvdecContext->sFwMsgArgs.psMsgHdr = psMsgHdr;
    ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                    (IMG_BYTE *)&psPvdecContext->sFwMsgArgs,
                                    sizeof(psPvdecContext->sFwMsgArgs),
                                    ENDPOINT_VXD_INPUT);
#else
    ui32Result = VXDIO_SendFirmwareMessage(psPvdecContext->hDev,
                                           0,
                                           psMsgHdr);
#endif

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}


/*!
******************************************************************************

 @Function              PVDEC_GetCoreState

******************************************************************************/
IMG_RESULT PVDEC_GetCoreState(
    const IMG_HANDLE    hVxd,
    VXDIO_sState      * psState
)
{
    PVDEC_sContext       * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_RESULT             ui32Result;

#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    VXD_sGetStateArgs   sGetStateArgs;
#endif

    if (hVxd == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    sGetStateArgs.psState = psState;
    ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                    (IMG_BYTE *)&sGetStateArgs,
                                    sizeof(sGetStateArgs),
                                    ENDPOINT_VXD_GET_STATE);
#else
    ui32Result = VXDIO_GetCoreState(psPvdecContext->hDev,
                                    psState);
#endif
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Add firmware PANIC indicator. */
    psState->sFwState.bPanic = psPvdecContext->bFWPanic;

    return IMG_SUCCESS;

error:
    return ui32Result;
}


/*!
******************************************************************************

 @Function              pvdec_PrepareMTX

******************************************************************************/
static IMG_VOID pvdec_PrepareMTX(
    PVDEC_sContext  * psPvdecContext,
    VXDIO_sPtdInfo  * psPtdInfo,
    MMU_eMmuType      eMmuType
)
{
    IMG_UINT32  ui32Reg;
    IMG_ASSERT(psPvdecContext != IMG_NULL);
    /* Reset MTX */
    ui32Reg = 0;
    REGIO_WRITE_FIELD(ui32Reg, MTX_CORE, CR_MTX_SOFT_RESET, MTX_RESET, 1);
    REGIO_WRITE_REGISTER(psPvdecContext, MTX_CORE, CR_MTX_SOFT_RESET, ui32Reg);

    /* Set the MTX timer divide register - the value used is system dependent. */
    ui32Reg = 0;
    //        REGIO_WRITE_FIELD(ui32Reg, MTX_CORE, CR_MTX_SYSC_TIMERDIV, TIMER_EN, 1);                         /* Enabled. */
    REGIO_WRITE_FIELD(ui32Reg, MTX_CORE, CR_MTX_SYSC_TIMERDIV, TIMER_DIV, PVDECIO_MTX_CLK_MHZ - 1);  /* Set for 1MHz timer. */
    REGIO_WRITE_REGISTER(psPvdecContext, MTX_CORE, CR_MTX_SYSC_TIMERDIV, ui32Reg);


    /* always use bank 0 */
    REGIO_WRITE_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_BANK_INDEX, 0);

    /* Set base address of PTD */
#ifdef SYSBRG_BRIDGING
    REGIO_WRITE_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_DIR_BASE_ADDR, psPtdInfo->ui32PtdPhysAddr);
#else /* not SYSBRG_BRIDGING */
    TALINTVAR_WriteToReg32(psPvdecContext->hPvdecCoreRegSpace, IMG_VIDEO_BUS4_MMU_MMU_DIR_BASE_ADDR_OFFSET,
            psPtdInfo->hPtdMemSpace, psPtdInfo->ui32IntRegNum);
#endif /* not SYSBRG_BRIDGING */

    /* clear the bypass bits */
    ui32Reg = 0;
    REGIO_WRITE_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_ADDRESS_CONTROL, UPPER_ADDRESS_FIXED, 0 );
    REGIO_WRITE_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_ADDRESS_CONTROL, MMU_ENABLE_EXT_ADDRESSING,
            (eMmuType = MMU_TYPE_40BIT) ? 1 : 0 );
    REGIO_WRITE_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_ADDRESS_CONTROL, MMU_BYPASS, 0 );
    REGIO_WRITE_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_ADDRESS_CONTROL, ui32Reg);

    //        ui32Reg = REGIO_READ_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1);
    //        REGIO_WRITE_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1, MMU_PAUSE_CLEAR, 1);
    //        REGIO_WRITE_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1, ui32Reg);
}


/*!
******************************************************************************

 @Function              pvdec_Poll

******************************************************************************/
static IMG_RESULT pvdec_Poll(
    const PVDEC_sContext  * psPvdecContext,
    IMG_UINT32              ui32MemRegion,
    IMG_UINT32              ui32Offset,
    IMG_UINT32              ui32RequValue,
    IMG_UINT32              ui32Enable
)
{
    IMG_UINT32  ui32Result = IMG_SUCCESS;

#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    VXD_sPollArgs sPollArgs;
    sPollArgs.ui32MemRegion = ui32MemRegion;
    sPollArgs.ui32Offset    = ui32Offset;
    sPollArgs.ui32RequValue = ui32RequValue;
    sPollArgs.ui32Enable    = ui32Enable;

    ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                    (IMG_BYTE *)&sPollArgs,
                                    sizeof(sPollArgs),
                                    ENDPOINT_VXD_POLL_NOPDUMP);
#else
    ui32Result = VXDIO_Poll(psPvdecContext->hDev,
                            ui32MemRegion,
                            ui32Offset,
                            ui32RequValue,
                            ui32Enable,
                            VXDIO_POLL_EQUAL);
#endif

    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    return ui32Result;
}

/*!
******************************************************************************

 @Function              pvdec_ConfigureMemStaller

******************************************************************************/
static IMG_VOID
pvdec_ConfigureMemStaller(
    PVDEC_sContext  * psPvdecContext
)
{
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_TEST, MEM_READ_LATENCY, 0);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_TEST, MEM_WRITE_RESPONSE_LATENCY, 0);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_TEST, MEM_CTRL, 0);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_TEST, RAND_STL_MEM_CMD_CONFIG, 0);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_TEST, RAND_STL_MEM_WDATA_CONFIG, 0);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_TEST, RAND_STL_MEM_WRESP_CONFIG, 0);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_TEST, RAND_STL_MEM_RDATA_CONFIG, 0);
}

/*!
******************************************************************************

 @Function              pvdec_PvdecReset

******************************************************************************/
static IMG_RESULT pvdec_PvdecReset(
    PVDEC_sContext  * psPvdecContext
)
{
    IMG_UINT32  ui32Reg;
    IMG_RESULT  ui32Result = IMG_SUCCESS;
    IMG_UINT8   ui8Pipe = 1;
    IMG_UINT32  ui32RegCoreClock = 0;
    IMG_UINT32  ui32I = 0;

    DEBUG_REPORT(REPORT_MODULE_VXDIO, "Doing PVDEC Reset");

    for (ui32I = 0; ui32I < 2; ui32I++)
    {
        /* Turn off all the clocks except core */
        REGIO_WRITE_FIELD(ui32RegCoreClock, PVDEC_CORE, CR_PVDEC_MAN_CLK_ENABLE, CR_PVDEC_REG_MAN_CLK_ENABLE, 1);
        REGIO_WRITE_FIELD(ui32RegCoreClock, PVDEC_CORE, CR_PVDEC_MAN_CLK_ENABLE, CR_CORE_MAN_CLK_ENABLE, 1);
        REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_MAN_CLK_ENABLE, ui32RegCoreClock);
        /* Make sure all the clocks are off except core */
        ui32Reg = REGIO_READ_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_MAN_CLK_ENABLE);
        IMG_ASSERT(ui32Reg == ui32RegCoreClock);

        /* Turn all clocks on */
        REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_MAN_CLK_ENABLE, 0xffffffff);
        REGIO_WRITE_PIPE_REGISTER(psPvdecContext, ui8Pipe, PVDEC_PIXEL, CR_PIXEL_MAN_CLK_ENABLE, 0xffffffff);
        REGIO_WRITE_PIPE_REGISTER(psPvdecContext, ui8Pipe, PVDEC_ENTROPY, CR_ENTROPY_MAN_CLK_ENABLE , 0xffffffff);

        /* Issue software reset for all but core */
        ui32Reg = 0;
        REGIO_WRITE_FIELD(ui32Reg, PVDEC_CORE, CR_PVDEC_SOFT_RESET, CR_PVDEC_PIXEL_PROCESSING_SOFT_RESET, 0xFF);
        REGIO_WRITE_FIELD(ui32Reg, PVDEC_CORE, CR_PVDEC_SOFT_RESET, CR_PVDEC_ENTROPY_SOFT_RESET, 0xFF);
        REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_SOFT_RESET, ui32Reg);

        REGIO_READ_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_SOFT_RESET);
        REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_SOFT_RESET, 0);

        ui32Reg = 0;
        REGIO_WRITE_FIELD(ui32Reg, PVDEC_CORE, CR_PVDEC_SOFT_RESET, CR_PVDEC_SOFT_RESET, 0x1);
        REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_SOFT_RESET, ui32Reg);

        ui32Result = pvdec_Poll(psPvdecContext,
                                REGION_PVDEC_CORE_REGSPACE,
                                PVDEC_CORE_CR_PVDEC_SOFT_RESET_OFFSET,
                                0,
                                PVDEC_CORE_CR_PVDEC_SOFT_RESET_CR_PVDEC_SOFT_RESET_MASK);
        IMG_ASSERT((ui32Result == IMG_SUCCESS) || (ui32Result == IMG_ERROR_TIMEOUT));
        if ((ui32Result != IMG_SUCCESS) && (ui32Result != IMG_ERROR_TIMEOUT))
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed poll waiting for reset bits to be set.");
            return ui32Result;
        }

        if (ui32I == 0)
        {
            /* Issue software reset for MMU */
            ui32Reg = 0x10000000; //REGIO_WRITE_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1, CR_MMU_SOFT_RESET, 1);
            REGIO_WRITE_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1 , ui32Reg);

            ui32Result = pvdec_Poll(psPvdecContext,
                                    REGION_IMG_VIDEO_BUS4_MMU_REGSPACE,
                                    IMG_VIDEO_BUS4_MMU_MMU_CONTROL1_OFFSET,
                                    0,
                                    0x10000000);
            IMG_ASSERT((ui32Result == IMG_SUCCESS) || (ui32Result == IMG_ERROR_TIMEOUT));
            if ((ui32Result != IMG_SUCCESS) && (ui32Result != IMG_ERROR_TIMEOUT))
            {
                REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed poll for MMU soft reset.");
                return ui32Result;
            }
        }
    }

    /* Clear interrupt enabled flag */
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_ENABLE, 0);

    /* Clear any pending interrupt flags */
    ui32Reg = 0;
    REGIO_WRITE_FIELD(ui32Reg, PVDEC_CORE, CR_PVDEC_INTERRUPT_CLEAR, CR_IRQ_CLEAR, 0xFFFF);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_INTERRUPT_CLEAR, ui32Reg);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PVDEC_Initialise

******************************************************************************/
IMG_RESULT PVDEC_Initialise(
    const IMG_HANDLE        hVxd,
    VDECFW_sCoreInitData  * psInitConfig
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT32        ui32Result;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    // Enable the clocks to allow for reset.
#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                    (IMG_BYTE *)&psPvdecContext->sEnableClocksArgs,
                                    sizeof(psPvdecContext->sEnableClocksArgs),
                                    ENDPOINT_VXD_ENABLE_CLOCKS);
#else
    ui32Result = VXDIO_EnableClocks(psPvdecContext->hDev,
                                    IMG_FALSE,
                                    IMG_FALSE,
                                    IMG_FALSE);
#endif
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Reset PVDEC: the core may have been powered down.
    ui32Result = pvdec_PvdecReset(psPvdecContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Enable the clocks since the core could have been powered down.
#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    // Enable the clocks since the core could have been powered down.
    ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                    (IMG_BYTE *)&psPvdecContext->sEnableClocksArgs,
                                    sizeof(psPvdecContext->sEnableClocksArgs),
                                    ENDPOINT_VXD_ENABLE_CLOCKS);
#else
    ui32Result = VXDIO_EnableClocks(psPvdecContext->hDev,
                                    IMG_FALSE,
                                    IMG_FALSE,
                                    IMG_FALSE);
#endif
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)
    VXDIO_EnableDebugFifo(psPvdecContext->hDev);
#endif

    pvdec_PrepareMTX(psPvdecContext,
                     &psPvdecContext->sPtdInfo,
                     psPvdecContext->sProps.eMmuType);

    /* Load the firmware base component. */
#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    ui32Result = SECURE_LoadCoreFW(psPvdecContext->hDev);
#else
    ui32Result = VXDIO_LoadBaseFirmware(psPvdecContext->hDev);
#endif
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
                "Failed loading firmware base component for core %d",
                psPvdecContext->ui32CoreNum);
        return ui32Result;
    }

#ifndef SYSBRG_BRIDGING
    ui32Result = TALINTERRUPT_RegisterCheckFunc(psPvdecContext->hPvdecCoreRegSpace,
                                                pvdec_CheckInterruptFunc,
                                                psPvdecContext);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif /* not SYSBRG_BRIDGING */

    /* check DBGOPTS for CSim property */
    {
        DBGOPT_sValue sVal;
        if (DBGOPTKM_GetSize("CSim", DBGOPT_TYPE_BOOL) &&
            DBGOPTKM_Get("CSim", IMG_NULL, &sVal))
        {
            psPvdecContext->bCSim = sVal.bVal;
        }
        else
        {
            psPvdecContext->bCSim = IMG_FALSE;
        }
    }

    psPvdecContext->bInitialised = IMG_TRUE;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PVDEC_DeInitialise

******************************************************************************/
IMG_RESULT
PVDEC_DeInitialise(
    const IMG_HANDLE  hVxd
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT32        ui32Result;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (!psPvdecContext->bInitialised)
    {
        return IMG_SUCCESS;
    }

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)
    /* Check debug FIFO before reset */
    {
        IMG_UINT32 ui32FifoSize, ui32FifoCtrl = 0;

        VXDIO_ProcessDebugData(psPvdecContext->hDev);

        ui32FifoSize = VXDIO_GetDebugFifoSize(psPvdecContext->hDev);
        REGIO_WRITE_FIELD_LITE(ui32FifoCtrl, PVDEC_CORE,
            CR_PROC_DEBUG_FIFO_CTRL_0, CR_PROC_DEBUG_FIFO_COUNT, ui32FifoSize);
        REGIO_WRITE_FIELD_LITE(ui32FifoCtrl, PVDEC_CORE,
            CR_PROC_DEBUG_FIFO_CTRL_0, CR_PROC_DEBUG_FIFO_SIZE, ui32FifoSize);

        /* Wait for empty fifo */
        pvdec_Poll(psPvdecContext, REGION_PVDEC_CORE_REGSPACE,
                                   PVDEC_CORE_CR_PROC_DEBUG_FIFO_CTRL_0_OFFSET,
                                   ui32FifoCtrl,
                                   0xFFFFFFFF);
        VXDIO_DisableDebugFifo(psPvdecContext->hDev);
    }
#endif /* !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG) */

    /* Reset the MTX-PVDEC first. */
    ui32Result = pvdec_PvdecReset(hVxd);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Reset PANIC indicator. */
    psPvdecContext->bFWPanic = IMG_FALSE;

#ifndef SYSBRG_BRIDGING
    ui32Result = TALINTERRUPT_UnRegisterCheckFunc(psPvdecContext->hPvdecCoreRegSpace);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif /* not SYSBRG_BRIDGING */

    // Disable the clocks
#ifdef SECURE_MEDIA_SUPPORT
    {
        VXD_sDisableClocksArgs  sDisableClocksArgs;

        //Using Secure Interface
        ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                        (IMG_BYTE *)&sDisableClocksArgs,
                                        sizeof(sDisableClocksArgs),
                                        ENDPOINT_VXD_DISABLE_CLOCKS);
    }
#else
    ui32Result = VXDIO_DisableClocks(psPvdecContext->hDev);
#endif

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    psPvdecContext->bInitialised = IMG_FALSE;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              PVDEC_Destroy

******************************************************************************/
IMG_RESULT PVDEC_Destroy(
    const IMG_HANDLE  hVxd
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT32        ui32Result = IMG_SUCCESS;;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    PVDEC_DeInitialise(hVxd);

    if (psPvdecContext->eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
    {
#ifdef SECURE_MEDIA_SUPPORT
        VXD_sDeInitialiseArgs   sDeInitialiseArgs;
        //Using Secure Interface
        ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                        (IMG_BYTE *)&sDeInitialiseArgs,
                                        sizeof(sDeInitialiseArgs),
                                        ENDPOINT_VXD_DEINITIALISE);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);

        ui32Result = SECURE_ReleaseHandle(psPvdecContext->hDev);
#else
        //Using Secure Interface
        ui32Result = VXDIO_DeInitialise(psPvdecContext->ui32CoreNum,
                                        psPvdecContext->hDev);
#endif
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    IMG_FREE(psPvdecContext);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              pvdec_InitCoreProperties

******************************************************************************/
static IMG_VOID pvdec_InitCoreProperties(
    VXD_sCoreProps    * psCoreProps,
    PVDEC_sCoreRev    * psCoreRev,
    IMG_UINT32          ui32CoreConfig,
    IMG_UINT32        * aui32PixelPipeConfig,
    IMG_UINT32        * aui32PixelMiscConfig
)
{
    IMG_UINT8    ui8PipeMinus1 = 0;
    IMG_UINT32  i;
    IMG_UINT32   ui32MaxH264HwChromaFormat = 0;
    IMG_UINT32   ui32MaxHEVCHwChromaFormat = 0;
    IMG_UINT32   ui32MaxBitDepthLuma = 0;

    //////////////////////////////////////
    //  Default settings                //
    //////////////////////////////////////

    for (i = 0; i < sizeof(asStdProps)/sizeof(asStdProps[0]); i++)
    {
        // Update video standard properties if the core is beyond specified version and
        // the properties are for newer cores than the previous.
        if (FROM_REV(MAJOR_REVISION(asStdProps[i].ui32CoreRev),
                     MINOR_REVISION(asStdProps[i].ui32CoreRev),
                     MAINT_REVISION(asStdProps[i].ui32CoreRev)) &&
            asStdProps[i].ui32CoreRev >= psCoreProps->asVidStdProps[asStdProps[i].eVidStd].ui32CoreRev)
        {
            psCoreProps->asVidStdProps[asStdProps[i].eVidStd] = asStdProps[i];
        }
    }

    // Default latency.
    psCoreProps->ui32Latency = 128;

    // Default VDMC cache size.
    psCoreProps->ui32VdmcCacheSize = 1;
    psCoreProps->bVdmcBurst4 = IMG_FALSE;

    // SR DMA burst size
    // Value must be re-mapped for hardware use (2 = 1, 4 = 2, 8 = 3). CR_VEC_CONTROL_2, SR_BURST_SIZE,
    psCoreProps->ui32SrDmaBurstSize = 4;

    // Default master.
    psCoreProps->ui32NumCores = 1;

    // Populate the core properties.


    if (GET_BITS(ui32CoreConfig, 11, 1))
    {
        psCoreProps->bHdSupport = IMG_TRUE;
    }

    for(ui8PipeMinus1 = 0; ui8PipeMinus1 < psCoreProps->ui32NumPixelPipes; ui8PipeMinus1++)
    {
        IMG_UINT32 ui32CurrentBitDepth = GET_BITS(aui32PixelMiscConfig[ui8PipeMinus1], 4, 3) + 8;
        IMG_UINT32 ui32CurrentH264HwChromaFormat = GET_BITS(aui32PixelMiscConfig[ui8PipeMinus1], 0, 2);
        IMG_UINT32 ui32CurrentHEVCHwChromaFormat = GET_BITS(aui32PixelMiscConfig[ui8PipeMinus1], 2, 2);

        if (GET_BITS(aui32PixelMiscConfig[ui8PipeMinus1], 7, 1))
        {
            psCoreProps->bHevcRangeExt[ui8PipeMinus1] = IMG_TRUE;
        }

        if (GET_BITS(aui32PixelMiscConfig[ui8PipeMinus1], 8, 1))
        {
            psCoreProps->abRotationSupport[ui8PipeMinus1] = IMG_TRUE;
        }
        if (GET_BITS(aui32PixelMiscConfig[ui8PipeMinus1], 9, 1))
        {
            psCoreProps->abScalingSupport[ui8PipeMinus1] = IMG_TRUE;
        }

        psCoreProps->aui32NumStreams[ui8PipeMinus1] = GET_BITS(aui32PixelMiscConfig[ui8PipeMinus1], 12, 2) + 1;

    // Video standards.
        psCoreProps->abMpeg2[ui8PipeMinus1]    = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 0, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abMpeg4[ui8PipeMinus1]    = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 1, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abH264[ui8PipeMinus1]     = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 2, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abVc1[ui8PipeMinus1]      = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 3, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abJpeg[ui8PipeMinus1]     = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 5, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abAvs[ui8PipeMinus1]      = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 7, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abReal[ui8PipeMinus1]     = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 8, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abVp6[ui8PipeMinus1]      = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 9, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abVp8[ui8PipeMinus1]      = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 10, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abSorenson[ui8PipeMinus1] = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 11, 1) ? IMG_TRUE : IMG_FALSE;
        psCoreProps->abHEVC[ui8PipeMinus1]     = GET_BITS(aui32PixelPipeConfig[ui8PipeMinus1], 22, 1) ? IMG_TRUE : IMG_FALSE;

        ui32MaxBitDepthLuma = (ui32MaxBitDepthLuma > ui32CurrentBitDepth ? ui32MaxBitDepthLuma : ui32CurrentBitDepth);
        ui32MaxH264HwChromaFormat = (ui32MaxH264HwChromaFormat > ui32CurrentH264HwChromaFormat ? ui32MaxH264HwChromaFormat : ui32CurrentH264HwChromaFormat);
        ui32MaxHEVCHwChromaFormat = (ui32MaxHEVCHwChromaFormat > ui32CurrentHEVCHwChromaFormat ? ui32MaxHEVCHwChromaFormat : ui32CurrentHEVCHwChromaFormat);
    }

    // Override default bit-depth with value signalled explicitly by core.
    psCoreProps->asVidStdProps[0].ui32MaxLumaBitDepth = ui32MaxBitDepthLuma;
    psCoreProps->asVidStdProps[0].ui32MaxChromaBitDepth = psCoreProps->asVidStdProps[0].ui32MaxLumaBitDepth;
    for (i = 1; i < VDEC_STD_MAX; i++)
    {
        psCoreProps->asVidStdProps[i].ui32MaxLumaBitDepth = psCoreProps->asVidStdProps[0].ui32MaxLumaBitDepth;
        psCoreProps->asVidStdProps[i].ui32MaxChromaBitDepth = psCoreProps->asVidStdProps[0].ui32MaxChromaBitDepth;
    }

    // Colour Format (H.264)
    switch (ui32MaxH264HwChromaFormat)
    {
    case 1:
        psCoreProps->asVidStdProps[VDEC_STD_H264].eMaxChromaFormat = PIXEL_FORMAT_420;
        break;

    case 2:
        psCoreProps->asVidStdProps[VDEC_STD_H264].eMaxChromaFormat = PIXEL_FORMAT_422;
        break;

    case 3:
        psCoreProps->asVidStdProps[VDEC_STD_H264].eMaxChromaFormat = PIXEL_FORMAT_444;
        break;

    default:
        break;
    }

    // Colour Format (H.265)
    switch (ui32MaxHEVCHwChromaFormat)
    {
    case 1:
        psCoreProps->asVidStdProps[VDEC_STD_HEVC].eMaxChromaFormat = PIXEL_FORMAT_420;
        break;

    case 2:
        psCoreProps->asVidStdProps[VDEC_STD_HEVC].eMaxChromaFormat = PIXEL_FORMAT_422;
        break;

    case 3:
        psCoreProps->asVidStdProps[VDEC_STD_HEVC].eMaxChromaFormat = PIXEL_FORMAT_444;
        break;

    default:
        break;
    }

    //////////////////////////////////////////////////////////////////////////
    //  Version specific settings (we are in PVDEC so version 7.0 onwards)  //
    //////////////////////////////////////////////////////////////////////////

    psCoreProps->bAutoClockGatingSupport = IMG_TRUE; // from rev 2.0.0
    psCoreProps->b64ByteFixedStrides     = IMG_TRUE; // from rev 3.0.0
    psCoreProps->bExtendedStrides        = IMG_TRUE; // from rev 3.0.0
    psCoreProps->ui32CmdBufferSize       = 64;       // from rev 3.0.0
    psCoreProps->bErrorHandling          = IMG_TRUE; // from rev 3.0.5
    psCoreProps->bErrorConcealment       = IMG_TRUE; // from rev 3.0.5
    psCoreProps->bNewTestRegSpace        = IMG_TRUE; // from rev 4.0.3

    psCoreProps->b4kScalingCoeffs     = IMG_TRUE; // from rev 5.0.0
    psCoreProps->b8kScalingCoeffs     = IMG_TRUE; // from rev 7.0.0
    psCoreProps->bScalingWithOold     = IMG_TRUE; // from rev 5.0.0
    psCoreProps->bExtClockGating      = IMG_TRUE; // from rev 5.0.0
    psCoreProps->bAuxLineBufSupported = IMG_TRUE; // from rev 5.0.0

    psCoreProps->bImprovedErrorConcealment = IMG_TRUE; // from rev 5.0.0

    psCoreProps->ui32Latency       = 384; // from rev 5.0.0
    psCoreProps->ui32VdmcCacheSize = 2;   // from rev 5.0.0

    psCoreProps->bNewCacheSettings = IMG_TRUE; // from rev 5.5.0
    psCoreProps->ui32VdmcCacheSize = 4;        // from rev 5.5.0
    psCoreProps->bVdmcBurst4       = IMG_TRUE; // from rev 5.5.0
    psCoreProps->bLossless         = IMG_TRUE; // from rev 5.5.0

    psCoreProps->ui32SrDmaBurstSize = 8; // from rev 5.5.2

    psCoreProps->ui32ScalingPrecision = 12;       // from rev 5.6.0

    psCoreProps->bMultiCoreSupport = IMG_TRUE; // from rev 5.6.0

    // This may not work/be invalid for slave cores.
    //psCoreProps->ui32NumCores = ui32NumPixelPipes; // from rev 7.0.0

    psCoreProps->BRN40493 = IMG_FALSE; // from rev 6.0.0
}

/*!
******************************************************************************

 @Function              pvdec_GetCoreProperties

******************************************************************************/
static IMG_RESULT pvdec_GetCoreProperties(
    PVDEC_sContext    * psPvdecContext,
    VXD_sCoreProps    * psProps
)
{
    IMG_UINT32  ui32Reg;
    IMG_UINT32  ui32Revision;
    IMG_UINT32  ui32CoreConfig;
    IMG_UINT32  ui32GroupId;
    IMG_UINT32  ui32PvdecCoreId;
    IMG_UINT32  ui32CoreId;
    IMG_UINT32  ui32ExtendedAddressRange;

    IMG_UINT8   ui8PipeNum;
    IMG_UINT32  aui32PixelPipeConfig[VDEC_MAX_PIXEL_PIPES] = {0};
    IMG_UINT32  aui32PixelMiscConfig[VDEC_MAX_PIXEL_PIPES] = {0};

    PVDEC_sCoreRev sCoreRev;

    /* PVDEC Core Revision Information */
    ui32Revision =
        REGIO_READ_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_CORE_REV);
    sCoreRev.ui32MajRev = ui32MajRev =
        REGIO_READ_FIELD(ui32Revision, PVDEC_CORE, CR_PVDEC_CORE_REV, CR_PVDEC_MAJOR_REV);
    sCoreRev.ui32MinRev = ui32MinRev =
        REGIO_READ_FIELD(ui32Revision, PVDEC_CORE, CR_PVDEC_CORE_REV, CR_PVDEC_MINOR_REV);
    sCoreRev.ui32MaintRev = ui32MaintRev =
        REGIO_READ_FIELD(ui32Revision, PVDEC_CORE, CR_PVDEC_CORE_REV, CR_PVDEC_MAINT_REV);

    // ui32LatencyConfig =
    //      REGIO_READ_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_LATENCY_CONFIG);

    /* Core ID */
    ui32PvdecCoreId =
        REGIO_READ_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_CORE_ID);
    ui32GroupId =
        REGIO_READ_FIELD(ui32PvdecCoreId, PVDEC_CORE, CR_PVDEC_CORE_ID, CR_GROUP_ID);
    ui32CoreId =
        REGIO_READ_FIELD(ui32PvdecCoreId, PVDEC_CORE, CR_PVDEC_CORE_ID, CR_CORE_ID);

    // Ensure that the core is IMG Video Decoder (PVDEC).
    if (ui32GroupId != 3 || ui32CoreId != 3)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
            "IMG Video Decoder (VXD) not detected");
        return IMG_ERROR_DEVICE_NOT_FOUND;
    }

    // Insert Group and Core Id into PDUMP
#if 0
    MSVDXIO_Poll(psPvdecContext->hDev,
                 REGION_PVDEC_CORE_REGSPACE,
                 PVDEC_CORE_CR_PVDEC_CORE_ID_OFFSET,
                 ui32GroupId << PVDEC_CORE_CR_PVDEC_CORE_ID_CR_GROUP_ID_SHIFT,
                 PVDEC_CORE_CR_PVDEC_CORE_ID_CR_GROUP_ID_MASK,
                 VXDIO_POLL_EQUAL);
    MSVDXIO_Poll(psPvdecContext->hDev,
                 REGION_PVDEC_CORE_REGSPACE,
                 PVDEC_CORE_CR_PVDEC_CORE_ID_OFFSET,
                 ui32CoreId << PVDEC_CORE_CR_PVDEC_CORE_ID_CR_CORE_ID_SHIFT,
                 PVDEC_CORE_CR_PVDEC_CORE_ID_CR_CORE_ID_MASK,
                 VXDIO_POLL_EQUAL);
#endif

    ui32CoreConfig = REGIO_READ_FIELD(ui32PvdecCoreId,
        PVDEC_CORE, CR_PVDEC_CORE_ID, CR_PVDEC_CORE_CONFIG);

    // check DBGOPTS for core properties
    {
        DBGOPT_sValue     sVal;
        DBGOPT_eType      eType;
        VXD_sCoreProps    sCoreProps;

        if (DBGOPTKM_GetSize("CoreConfig", DBGOPT_TYPE_BUF) == sizeof(sCoreProps) &&
            DBGOPTKM_Get("CoreConfig", &eType, &sVal))
        {
            *psProps = *((VXD_sCoreProps *) sVal.sBufVal.pvVal);

            DEBUG_REPORT(REPORT_MODULE_VXDIO,
                         "Setting core configuration from debug options");
            goto setting_props_ending;
        }
    }

    VDEC_BZERO(psProps);

    // Construct core version name.
    sprintf(psProps->acVersion, "%d.%d.%d",
            sCoreRev.ui32MajRev, sCoreRev.ui32MinRev, sCoreRev.ui32MaintRev);

    ui32Reg = REGIO_READ_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_CONFIG0);
    ui32ExtendedAddressRange =
        REGIO_READ_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONFIG0, EXTENDED_ADDR_RANGE);
    switch (ui32ExtendedAddressRange)
    {
        case 0:
            psProps->eMmuType = MMU_TYPE_32BIT;
            break;
        case 4:
            psProps->eMmuType = MMU_TYPE_36BIT;
            break;
        case 8:
            psProps->eMmuType = MMU_TYPE_40BIT;
            break;
        default:
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
                   "Unsupported MMU address extension: %d",
                   ui32ExtendedAddressRange);
            IMG_FREE(psPvdecContext);
            return IMG_ERROR_NOT_SUPPORTED;
    }

    ui32Reg = REGIO_READ_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONFIG0, GROUP_OVERRIDE_SIZE);

    psProps->ui32NumEntropyPipes = ui32CoreConfig & 0xF;
    psProps->ui32NumPixelPipes = ui32CoreConfig >> 4 & 0xF;

    REPORT(REPORT_MODULE_VXDIO, REPORT_INFO,
           "PVDEC revision %08x detected, id %08x."
           " Found %d entropy pipe(s), %d pixel pipe(s), %d group size",
           ui32Revision,
           ui32CoreId,
           psProps->ui32NumEntropyPipes,
           psProps->ui32NumPixelPipes, ui32Reg);

    for (ui8PipeNum = 1; ui8PipeNum <= psProps->ui32NumPixelPipes; ++ui8PipeNum)
    {
        aui32PixelPipeConfig[ui8PipeNum - 1] |= REGIO_READ_PIPE_REGISTER(psPvdecContext,
                                                        ui8PipeNum,
                                                        PVDEC_PIXEL,
                                                        CR_PIXEL_PIPE_CONFIG);

        aui32PixelMiscConfig[ui8PipeNum - 1] |= REGIO_READ_PIPE_REGISTER(psPvdecContext,
                                                        ui8PipeNum,
                                                        PVDEC_PIXEL,
                                                        CR_PIXEL_MISC_CONFIG);
    }

    pvdec_InitCoreProperties(psProps,
                             &sCoreRev,
                             ui32CoreConfig,
                             aui32PixelPipeConfig,
                             aui32PixelMiscConfig);

setting_props_ending:
    // Write trusted host pin
    //TALREG_WriteWord32(psPvdecContext->hPinTestMemSpace, 0x148, 1);

    return IMG_SUCCESS;
}


#ifndef IMG_KERNEL_MODULE
/*!
******************************************************************************

 @Function              MSVDX_PDUMPSync

******************************************************************************/
IMG_RESULT PVDEC_PDUMPSync(
    const IMG_HANDLE  hVxd
)
{
    PVDEC_sContext * psPvdecContext = (PVDEC_sContext *)hVxd;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A pointer to PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    return VXDIO_PDUMPSync(psPvdecContext->hDev);
}


/*!
******************************************************************************

 @Function              PVDEC_PDUMPLock

******************************************************************************/
IMG_RESULT PVDEC_PDUMPLock(
    const IMG_HANDLE hVxd
)
{
    PVDEC_sContext * psPvdecContext = (PVDEC_sContext *)hVxd;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A pointer to PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    return VXDIO_PDUMPLock(psPvdecContext->hDev);
}


/*!
******************************************************************************

 @Function              PVDEC_PDUMPUnLock

******************************************************************************/
IMG_RESULT PVDEC_PDUMPUnLock(
    const IMG_HANDLE hVxd
)
{
    PVDEC_sContext * psPvdecContext = (PVDEC_sContext *)hVxd;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A pointer to PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    return VXDIO_PDUMPUnLock(psPvdecContext->hDev);
}
#endif


/*!
******************************************************************************

 @Function              PVDEC_Create

******************************************************************************/
IMG_RESULT PVDEC_Create(
    const VDECDD_sDdDevConfig  * psDdDevConfig,
    IMG_UINT32                   ui32CoreNum,
    VXD_sCoreProps             * psCoreProps,
    HWCTRL_sRendec             * psRendec,
    IMG_HANDLE                 * phPvdecContext,
    HWCTRL_sFunctions          * psVxdFuncs
)
{
    PVDEC_sContext  * psPvdecContext;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(psCoreProps);
    IMG_ASSERT(psRendec);

    if (phPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "A pointer to PVDEC context handle must be provided");
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    VDEC_MALLOC(psPvdecContext);
    IMG_ASSERT(psPvdecContext);
    if(psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
            "Failed to allocate memory for PVDEC context");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psPvdecContext);

    psPvdecContext->ui32CoreNum = ui32CoreNum;
    psPvdecContext->eDecodeLevel = psDdDevConfig->eDecodeLevel;

    if (psDdDevConfig->eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
    {
#ifdef SECURE_MEDIA_SUPPORT
        VXD_sInitialiseArgs     sInitialiseArgs;

        IMG_MEMSET(&sInitialiseArgs, 0, sizeof(sInitialiseArgs));

        ui32Result = SECURE_GetHandle(VXD_CORE0, &psPvdecContext->hDev);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);

        /* Attempt to initialise PVDEC. */
        sInitialiseArgs.bFakeMtx = IMG_FALSE;
        //Using Secure Interface
        ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                        (IMG_BYTE *)&sInitialiseArgs,
                                        sizeof(sInitialiseArgs),
                                        ENDPOINT_VXD_INITIALISE);
#else
        ui32Result = VXDIO_Initialise(IMG_FALSE /* fake MTX */,
                                      IMG_FALSE,/* POST */
                                      IMG_FALSE,/* Stack usage test */
                                      ui32CoreNum,
                                      &psPvdecContext->hDev);
#endif
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        pvdec_ConfigureMemStaller(psPvdecContext);

        pvdec_PvdecReset(psPvdecContext);

        ui32Result = pvdec_GetCoreProperties(psPvdecContext, &psPvdecContext->sProps);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        HWCTRL_PrintMSVDXProps(&psPvdecContext->sProps, psPvdecContext->ui32CoreNum);
    }

#ifndef SYSBRG_BRIDGING
    {
        IMG_CHAR    acMemSpceName[256];

        // Create the memory space name prefix based upon the core number.
        sprintf(acMemSpceName, "P%d_", ui32CoreNum);
        strcat(acMemSpceName, "REG_PVDEC_CORE");
        psPvdecContext->hPvdecCoreRegSpace = TAL_GetMemSpaceHandle(acMemSpceName);

        sprintf(acMemSpceName, "P%d_", ui32CoreNum);
        strcat(acMemSpceName, "REG_VIDEO_BUS4_MMU");
        psPvdecContext->hVideoBus4RegSpace = TAL_GetMemSpaceHandle(acMemSpceName);
    }
#endif

    if (psDdDevConfig->ui32RendecSize)
    {
        /* Create two buffers with a 4:1 split both multiples of 4k */
        psPvdecContext->sRendec.aui32BufferSize[1] = psDdDevConfig->ui32RendecSize / 5;
        psPvdecContext->sRendec.aui32BufferSize[1] &= ~0xfff;
        psPvdecContext->sRendec.aui32BufferSize[0] = psDdDevConfig->ui32RendecSize - psPvdecContext->sRendec.aui32BufferSize[1];
        psPvdecContext->sRendec.aui32BufferSize[0] &= ~0xfff;

        psPvdecContext->sRendec.aui32InitialContext[0] = 0x00101010;
        psPvdecContext->sRendec.aui32InitialContext[1] = 0x00101010;
        psPvdecContext->sRendec.aui32InitialContext[2] = 0x00101010;
        psPvdecContext->sRendec.aui32InitialContext[3] = 0x00101010;
        psPvdecContext->sRendec.aui32InitialContext[4] = 0x00101010;
        psPvdecContext->sRendec.aui32InitialContext[5] = 0x00101010;

        psPvdecContext->sRendec.bInUse = IMG_TRUE;
    }

    *psCoreProps = psPvdecContext->sProps;
    *psRendec    = psPvdecContext->sRendec;

    *phPvdecContext = psPvdecContext;

    psVxdFuncs->pfnReadVLR               = IMG_NULL;
    psVxdFuncs->pfnWriteVLR              = IMG_NULL;
    psVxdFuncs->pfnHandleInt             = PVDEC_HandleInterrupts;
    psVxdFuncs->pfnGetIntStatus          = PVDEC_GetIntStatus;
    psVxdFuncs->pfnDumpRegisters         = IMG_NULL;
    psVxdFuncs->pfnSendFirmwareMessage   = PVDEC_SendFirmwareMessage;
    psVxdFuncs->pfnGetCoreState          = PVDEC_GetCoreState;
    psVxdFuncs->pfnFlushMmuCache         = PVDEC_FlushMmuCache;
    psVxdFuncs->pfnDisableCoreInterrupts = PVDEC_DisableCoreInterrupts;
    psVxdFuncs->pfnInitialise            = PVDEC_Initialise;
    psVxdFuncs->pfnDeInitialise          = PVDEC_DeInitialise;
    psVxdFuncs->pfnDestroy               = PVDEC_Destroy;
    psVxdFuncs->pfnPrepareFirmware       = PVDEC_PrepareFirmware;
    psVxdFuncs->pfnGetRegsOffsets        = PVDEC_GetRegsOffsets;
    psVxdFuncs->pfnGetInitMessage        = PVDEC_GetInitMessage;
    psVxdFuncs->pfnGetDecodeMessage      = IMG_NULL;
    psVxdFuncs->pfnGetBatchMessage       = PVDEC_GetBatchMessage;
    psVxdFuncs->pfnGetEndBytesMessage    = IMG_NULL;
    psVxdFuncs->pfnGetFragmentMessage    = IMG_NULL;
    psVxdFuncs->pfnReturnMsg             = PVDEC_ReturnMsg;
    psVxdFuncs->pfnProcessMessage        = PVDEC_ProcessMessage;
#ifndef IMG_KERNEL_MODULE
    psVxdFuncs->pfnPDUMPLock             = PVDEC_PDUMPLock;
    psVxdFuncs->pfnPDUMPUnlock           = PVDEC_PDUMPUnLock;
    psVxdFuncs->pfnPDUMPSync             = PVDEC_PDUMPSync;
    psVxdFuncs->pfnPDUMPComment          = PVDEC_PdumpComment;
#endif
    return IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function              PVDEC_HandleInterrupts

******************************************************************************/
IMG_RESULT PVDEC_HandleInterrupts(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
)
{
    PVDEC_sContext           * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT32                 ui32Result = IMG_SUCCESS;
#ifdef SECURE_MEDIA_SUPPORT
    VXD_sHandleInterruptsArgs  sHandleInterruptsArgs;
#endif

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Disable interrupts */
    SYSOSKM_DisableInt();

#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    sHandleInterruptsArgs.psIntStatus = psIntStatus;
    ui32Result = SECURE_SendMessage(psPvdecContext->hDev,
                                    (IMG_BYTE *)&sHandleInterruptsArgs,
                                    sizeof(sHandleInterruptsArgs),
                                    ENDPOINT_VXD_HANDLE_INTERRUPTS);
#else
    ui32Result = VXDIO_HandleInterrupts(psPvdecContext->hDev,
                                        psIntStatus);
#endif
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    /* Re enable interrupts */
    SYSOSKM_EnableInt();

    return ui32Result;
}

/*!
******************************************************************************

 @Function              PVDEC_GetIntStatus

******************************************************************************/
IMG_RESULT
PVDEC_GetIntStatus(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
)
{
    IMG_UINT32        ui32Reg;
    IMG_UINT32        ui32Enable;
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psIntStatus->ui32Pending = REGIO_READ_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_STATUS);

    ui32Enable = REGIO_READ_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_ENABLE);

    psIntStatus->ui32Pending &= ui32Enable;

    if (psIntStatus->ui32Pending & PVDEC_CORE_CR_PVDEC_HOST_INTERRUPT_STATUS_CR_HOST_MMU_FAULT_IRQ_MASK)
    {
        ui32Reg = REGIO_READ_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_STATUS0);
        psIntStatus->MMU_FAULT_ADDR = REGIO_READ_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_STATUS0, MMU_FAULT_ADDR) << 12 ;
        psIntStatus->MMU_PF_N_RW = REGIO_READ_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_STATUS0, MMU_PF_N_RW);

        ui32Reg = REGIO_READ_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_STATUS1);
        psIntStatus->ui32Requestor = REGIO_READ_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_STATUS1, MMU_FAULT_REQ_ID);
        psIntStatus->MMU_FAULT_RNW = REGIO_READ_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_STATUS1, MMU_FAULT_RNW);
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PVDEC_FlushMmuCache

******************************************************************************/
IMG_RESULT PVDEC_FlushMmuCache(
    const IMG_HANDLE  hVxd
)
{
    IMG_UINT32        ui32Reg = 0;
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Reg = REGIO_READ_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1);

    REGIO_WRITE_REPEATED_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1, MMU_INVALDC, 0, 1 );
    REGIO_WRITE_REPEATED_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1, MMU_INVALDC, 1, 1 );
    REGIO_WRITE_REPEATED_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1, MMU_INVALDC, 2, 1 );
    REGIO_WRITE_REPEATED_FIELD(ui32Reg, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1, MMU_INVALDC, 3, 1 );

    REGIO_WRITE_REGISTER(psPvdecContext, IMG_VIDEO_BUS4_MMU, MMU_CONTROL1 , ui32Reg);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PVDEC_DisableCoreInterrupts

******************************************************************************/
IMG_RESULT PVDEC_DisableCoreInterrupts(
    const IMG_HANDLE  hVxd
)
{
    IMG_UINT32        ui32Reg = 0;
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Clear interrupt enabled flag */
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_ENABLE, 0);

    /* Clear any pending interrupt flags */
    REGIO_WRITE_FIELD(ui32Reg, PVDEC_CORE, CR_PVDEC_INTERRUPT_CLEAR, CR_IRQ_CLEAR, 0xFFFF);
    REGIO_WRITE_REGISTER(psPvdecContext, PVDEC_CORE, CR_PVDEC_INTERRUPT_CLEAR, ui32Reg);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PVDEC_GetMemSpaceOffset

******************************************************************************/
IMG_RESULT PVDEC_GetMemSpaceOffset(
    const IMG_HANDLE    hVxd,
    IMG_UINT16          ui16MemRegion,
    IMG_UINT64        * pui64MemSpaceOffset
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    return VXDIO_GetMemSpaceOffset(psPvdecContext->hDev, ui16MemRegion, pui64MemSpaceOffset);
}

/*!
******************************************************************************

 @Function              PVDEC_PrepareFirmware

******************************************************************************/
IMG_RESULT PVDEC_PrepareFirmware(
    const IMG_HANDLE        hVxd,
    const MSVDXIO_sFw     * psFw,
    const VXDIO_sPtdInfo  * psPtdInfo
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT32        ui32Result;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }
    /* Prepare the firmware for loading to MTX. */
#ifdef SECURE_MEDIA_SUPPORT
    {
        AUTHENTICATIONKEY psKeyFw = IMG_NULL;

        //Using Secure Interface
        ui32Result = SECURE_PrepareFirmware(psPvdecContext->hDev,
                                            (IMG_BYTE *)psFw,
                                            0,
                                            VXD_CORE0 | VXD_CORE1,
                                            psKeyFw);
    }
#else
    ui32Result = VXDIO_PrepareFirmware(psPvdecContext->hDev,
                                       (IMG_HANDLE)psFw);
#endif
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Copy the device PTD for power-up initialisation.
    psPvdecContext->sPtdInfo = *psPtdInfo;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              PVDEC_GetRegsOffsets

******************************************************************************/
IMG_RESULT PVDEC_GetRegsOffsets(
    const IMG_HANDLE        hVxd,
    DECODER_sRegsOffsets  * psRegsOffsets
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT64        ui64RegspaceOffset;
    IMG_RESULT        ui32Result;
    IMG_HANDLE      * pahMemSpaces = IMG_NULL;

    if (psPvdecContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "An PVDEC context handle must be provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Result = VXDIO_GetMemSpacesHandles(psPvdecContext->ui32CoreNum, &pahMemSpaces);
    if (ui32Result != IMG_SUCCESS || pahMemSpaces == IMG_NULL)
    {
        return ui32Result;
    }

    ui32Result = TAL_GetMemSpaceOffset(pahMemSpaces[REGION_PVDEC_MSVDX_CMD], &ui64RegspaceOffset);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR, "Failed to get VDMC CMD offset.");
        goto error;
    }
    psRegsOffsets->ui32VdmcCmdOffset = IMG_UINT64_TO_UINT32(ui64RegspaceOffset);

    ui32Result = TAL_GetMemSpaceOffset(pahMemSpaces[REGION_PVDEC_MSVDX_VEC], &ui64RegspaceOffset);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR, "Failed to get VEC RAM offset.");
        goto error;
    }
    psRegsOffsets->ui32VecOffset = IMG_UINT64_TO_UINT32(ui64RegspaceOffset);

    ui32Result = TAL_GetMemSpaceOffset(pahMemSpaces[REGION_PVDEC_ENTROPY_PIPE_REGSPACE], &ui64RegspaceOffset);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR, "Failed to get PVDEC ENTROPY offset.");
        goto error;
    }
    psRegsOffsets->ui32EntropyOffset = IMG_UINT64_TO_UINT32(ui64RegspaceOffset);

    ui32Result = TAL_GetMemSpaceOffset(pahMemSpaces[REGION_PVDEC_VEC_BE], &ui64RegspaceOffset);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR, "Failed to get PVDEC VEC BE offset.");
        goto error;
    }
    psRegsOffsets->ui32VecBeRegsOffset = IMG_UINT64_TO_UINT32(ui64RegspaceOffset);

    ui32Result = TAL_GetMemSpaceOffset(pahMemSpaces[REGION_PVDEC_VEC_BE_CODEC], &ui64RegspaceOffset);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR, "Failed to get PVDEC VEC BE CODEC offset.");
        goto error;
    }
    psRegsOffsets->ui32VdecBeCodecRegsOffset = IMG_UINT64_TO_UINT32(ui64RegspaceOffset);

error:
    IMG_FREE(pahMemSpaces);

    return ui32Result;
}

IMG_RESULT PVDEC_GetTiledHeaps(
    VDEC_eTileScheme        eTileScheme,
    IMG_UINT32            * pui32NumHeaps,
    MMU_sHeapTilingInfo   * pasTilingInfo
)
{

    IMG_RESULT ui32Result;

    if (pui32NumHeaps == IMG_NULL || pasTilingInfo == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Invalid input params provided");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Result = MMU_GetTiledHeaps(eTileScheme, pui32NumHeaps, pasTilingInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}

/* EOF */
