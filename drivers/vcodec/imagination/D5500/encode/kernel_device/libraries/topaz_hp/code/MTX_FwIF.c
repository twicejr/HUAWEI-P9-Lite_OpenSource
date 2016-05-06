/*!
 *****************************************************************************
 *
 * @File       MTX_FwIF.c
 * @Title      MTX Firmware Interface
 * @Description    MTX Firmware Interface
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

#include "tal.h"
#include "tal_old.h"
#include "img_types.h"

#ifdef WIN32
#define TRACK_FREE(ptr) 		IMG_FREE(ptr)
#define TRACK_MALLOC(ptr) 		IMG_MALLOC(ptr)
#define TRACK_DEVICE_MEMORY_INIT
#define TRACK_DEVICE_MEMORY_SHOW
#include <sys/timeb.h>
#define TIMER_INIT
#define TIMER_START(a,b)
#define TIMER_END(a)
#define TIMER_CAPTURE(a)
#define TIMER_CLOSE
#define __func__ __FUNCTION__
//#include "timer.h"
#else
#define TRACK_FREE(ptr) 		IMG_FREE(ptr)
#define TRACK_MALLOC(ptr) 		IMG_MALLOC(ptr)
#define TRACK_DEVICE_MEMORY_INIT
#define TRACK_DEVICE_MEMORY_SHOW
#define TIMER_INIT
#define TIMER_START(...)
#define TIMER_END(...)
#define TIMER_CLOSE
#define TIMER_CAPTURE(...)
#endif

#if defined (IMG_KERNEL_MODULE)
#define PRINT printk
#define SPRINT sprintf
#else
#define PRINT printf
#define SPRINT sprintf
#define FPRINT fprintf
#endif

#include "MTX_FwIF.h"

#include "topaz_device.h"

#include "defs.h"
#if defined(HW_4_0)
#include "e4500_public_regdefs.h"
#include "img_video_bus4_mmu_regs.h"
#include "../../../../firmware/onyx/fw_binaries/include_all_fw_variants.h"
#endif
#if defined(HW_3_X)
#include "vxe_public_regdefs.h"
#include "../../../../firmware/topaz_hp/fw_binaries/include_all_fw_variants.h"
#endif
#include "mtx_regs.h"

#include "memmgr_km.h"

/* still used for DMAC regs */
#include "defs.h"
#include "img_soc_dmac_regs.h"


#if !defined (IMG_KERNEL_MODULE)
extern IMG_BOOL g_bDoingPdump;
#endif
/*
 ***********************************************************************************
 *      Static Function Decl
 ************************************************************************************/
static IMG_VOID
mtx_getMTXControlFromDash(
	IMG_FW_CONTEXT * psFwCtxt
);

static IMG_UINT32
mtx_readCoreReg(
	IMG_FW_CONTEXT * psFwCtxt,
	const  IMG_UINT32 ui32Reg
);

static IMG_VOID
mtx_writeCoreReg(
	IMG_FW_CONTEXT * psFwCtxt,
	const IMG_UINT32 ui32Reg,
	const IMG_UINT32 ui32Val
);

static IMG_ERRORCODE
mtx_selectFirmwareBuild(
	IMG_FW_CONTEXT * psFwCtxt,
	IMG_CODEC eCodec
);

static IMG_VOID
mtx_regIfUpload(
	IMG_FW_CONTEXT * psFwCtxt,
	const IMG_UINT32 ui32DataMem ,
	IMG_UINT32 ui32Address ,
	const IMG_UINT32 ui32Words ,
	const IMG_UINT32 *const pui32Data
);

extern IMG_BOOL g_bUseSecureFwUpload;
/*!
 ***********************************************************************************
 *
 * Polling Configuration for TAL
 *
 ************************************************************************************/
#define TAL_REG_RD_WR_TRIES		1000	/* => try 1000 times before giving up */
#define TAL_REG_RD_WR_TIMEOUT	50		/* 50 CYCLES => wait for 50 cycles before next poll */


/*!
 ***********************************************************************************
 *
 * Description        : defines that should come from auto generated headers
 *
 ************************************************************************************/
#define MTX_DMA_MEMORY_BASE (0x82880000)
#define PC_START_ADDRESS    (0x80900000)

#define MTX_CORE_CODE_MEM   (0x10)
#define MTX_CORE_DATA_MEM   (0x18)

#define MTX_PC              (0x05)

/*!
******************************************************************************

 @Function              mtx_getMTXControlFromDash

 @Description

 Get control of the MTX.

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Return   None

******************************************************************************/
static IMG_VOID
mtx_getMTXControlFromDash(
	IMG_FW_CONTEXT * psFwCtxt
)
{
    IMG_UINT32 ui32RegValue = 0;

	IMG_ASSERT( !psFwCtxt->bDriverHasMtxCtrl );

	/* Request the bus from the Dash...*/
	ui32RegValue = F_ENCODE(1, TOPAZHP_TOP_CR_MTX_MSTR_DBG_IS_SLAVE) | F_ENCODE(0x2, TOPAZHP_TOP_CR_MTX_MSTR_DBG_GPIO_IN);
	TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MTX_DEBUG_MSTR, ui32RegValue);

    do
    {
		TALREG_ReadWord32(
			psFwCtxt->ui32TopazMulticoreRegId,
			TOPAZHP_TOP_CR_MTX_DEBUG_MSTR,
			&ui32RegValue);

    } while ((ui32RegValue&0x18) != 0);

    /* Save the access control register...*/
	TALREG_ReadWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_RAM_ACCESS_CONTROL,
		&psFwCtxt->ui32AccessControl);

	psFwCtxt->bDriverHasMtxCtrl = IMG_TRUE;
}


/*!
******************************************************************************

 @Function              mtx_releaseMTXControlFromDash

 @Description

 Release control of the MTX.

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Return   None

******************************************************************************/
IMG_VOID
mtx_releaseMTXControlFromDash(
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_UINT32 ui32RegValue = 0;

	IMG_ASSERT( psFwCtxt->bDriverHasMtxCtrl );

    /* Restore the access control register...*/
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_RAM_ACCESS_CONTROL,
		psFwCtxt->ui32AccessControl);

	/* Release the bus...*/
	ui32RegValue = F_ENCODE(1, TOPAZHP_TOP_CR_MTX_MSTR_DBG_IS_SLAVE);
	TALREG_WriteWord32(
		psFwCtxt->ui32TopazMulticoreRegId,
		TOPAZHP_TOP_CR_MTX_DEBUG_MSTR,
		ui32RegValue);

	psFwCtxt->bDriverHasMtxCtrl = IMG_FALSE;
}


/*!
******************************************************************************

 @Function              mtx_readCoreReg

 @Description

 Read an MTX register.

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Input    ui32Reg          : Offset of register to read

 @Return   IMG_UINT32       : Register value

******************************************************************************/
static IMG_UINT32
mtx_readCoreReg(
	IMG_FW_CONTEXT * psFwCtxt,
	const  IMG_UINT32 ui32Reg
)
{
	IMG_UINT32 ui32ReturnVAl = 0;

	mtx_getMTXControlFromDash(psFwCtxt);

	/* Issue read request */
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_REGISTER_READ_WRITE_REQUEST,
		MASK_MTX_MTX_RNW | (ui32Reg & ~MASK_MTX_MTX_DREADY));

	/* Wait for done */
	TALREG_Poll32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_REGISTER_READ_WRITE_REQUEST,
		TAL_CHECKFUNC_ISEQUAL,
		MASK_MTX_MTX_DREADY,
		MASK_MTX_MTX_DREADY,
		1000 ,
		TAL_REG_RD_WR_TIMEOUT );

	/* Read */
	TALREG_ReadWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_REGISTER_READ_WRITE_DATA,
		&ui32ReturnVAl );

	mtx_releaseMTXControlFromDash(psFwCtxt);

	return ui32ReturnVAl;
}


/*!
******************************************************************************

 @Function              mtx_writeCoreReg

 @Description

 Write an MTX register.

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Input    ui32Reg          : Offset of register to write

 @Input    ui32Val          : Value to write to register

 @Return   None

******************************************************************************/
static IMG_VOID
mtx_writeCoreReg(
	IMG_FW_CONTEXT * psFwCtxt,
	const IMG_UINT32 ui32Reg,
	const IMG_UINT32 ui32Val
)
{
	mtx_getMTXControlFromDash(psFwCtxt);

	/* Put data in MTX_RW_DATA */
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_REGISTER_READ_WRITE_DATA,
		ui32Val);

	/* DREADY is set to 0 and request a write*/
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_REGISTER_READ_WRITE_REQUEST,
		ui32Reg & ~MASK_MTX_MTX_DREADY);

	/* Wait for DREADY to become set*/
	TALREG_Poll32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_REGISTER_READ_WRITE_REQUEST,
		TAL_CHECKFUNC_ISEQUAL,
		MASK_MTX_MTX_DREADY,
		MASK_MTX_MTX_DREADY,
		1000 ,
		5 );

	mtx_releaseMTXControlFromDash(psFwCtxt);
}

/* ****** Utility macroses for `mtx_selectFirmwareBuild` ************** */

#if FW_BIN_FORMAT_VERSION != 2
#	error Unsupported firmware format version
#endif


/*!
******************************************************************************

 @Function              mtx_selectFirmwareBuild

 @Description

 Assign a firmware binary to an MTX.

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Input    eCodec           : Firmware version to use

 
 @Return   None

******************************************************************************/
static IMG_ERRORCODE
mtx_selectFirmwareBuild(
	IMG_FW_CONTEXT * psFwCtxt,
	IMG_CODEC eCodec
)
{
	IMG_CHAR *sFormat, *sRcMode;
	IMG_UINT32 targetFwPipes = 0;
	IMG_UINT32 codecMask = 0;
	IMG_UINT32 currentHWConfig;
	IMG_BOOL bForceSpecificPipeCount = IMG_FALSE;

#	define HW_CONFIG_ALL_FEATURES 0
#	define HW_CONFIG_8CONTEXT	  1

#define CORE_REV_CONFIG_1_MIN 0x00030906
#define CORE_REV_CONFIG_1_MAX 0x00030907


#	define CODEC_MASK_JPEG		0x0001
#	define CODEC_MASK_MPEG2		0x0002
#	define CODEC_MASK_MPEG4		0x0004
#	define CODEC_MASK_H263		0x0008
#	define CODEC_MASK_H264		0x0010
#	define CODEC_MASK_H264MVC	0x0020
#	define CODEC_MASK_VP8		0x0040
#	define CODEC_MASK_H265		0x0080
#	define CODEC_MASK_FAKE		0x007F

#	define _ALL_CODEC_CASE(CODEC) \
		case IMG_CODEC_ ## CODEC ## _NO_RC: \
		case IMG_CODEC_ ## CODEC ## _VBR: \
		case IMG_CODEC_ ## CODEC ## _CBR:
#	define _MVC_CODEC_CASE(RC) case IMG_CODEC_H264MVC_ ## RC: sFormat = "H264MVC"; sRcMode = #RC; bForceSpecificPipeCount = IMG_TRUE; codecMask = CODEC_MASK_H264MVC; break;

	switch(eCodec)
	{
#if defined(HW_4_0)
#if defined(VP8_DRIVER)
			_ALL_CODEC_CASE(VP8)
			case IMG_CODEC_VP8_VCM:
				sFormat = "VP8";
				sRcMode = "ALL";
				codecMask = CODEC_MASK_VP8;
				break;
#endif
#endif
		_ALL_CODEC_CASE(H264)
		case IMG_CODEC_H264_VCM:
			sFormat = "H264";
			sRcMode = "ALL";
			bForceSpecificPipeCount = IMG_TRUE;
			codecMask = CODEC_MASK_H264;
			break;
		_ALL_CODEC_CASE(H263)
			sFormat = "LEGACY_VIDEO";
			sRcMode = "ALL";
			codecMask = CODEC_MASK_H263;
			break;
		_ALL_CODEC_CASE(MPEG2)
			sFormat = "LEGACY_VIDEO";
			sRcMode = "ALL";
			codecMask = CODEC_MASK_MPEG2;
			break;
		_ALL_CODEC_CASE(MPEG4)
			sFormat = "LEGACY_VIDEO";
			sRcMode = "ALL";
			codecMask = CODEC_MASK_MPEG4;
			break;
		_MVC_CODEC_CASE(NO_RC);
		_MVC_CODEC_CASE(VBR);
		_MVC_CODEC_CASE(CBR);
		_MVC_CODEC_CASE(ERC);
		case IMG_CODEC_JPEG:
			sFormat = "JPEG";
			sRcMode = "NO_RC";
			codecMask = CODEC_MASK_JPEG;
			break;
	default:
			PRINT("Failed to locate firmware for eCodec %d \n", eCodec);
			return IMG_ERR_UNDEFINED;
	}
#	undef _ALL_CODEC_CASE
#	undef _CODEC_CASE

	/* rc mode name fix */
	if(strcmp(sRcMode, "NO_RC") == 0)
	{
		sRcMode = "NONE";
	}

	{
		/* Pick firmware type (done implicitly via determining number of pipes given firmware is expected to have */
		const IMG_UINT32 coreId = psFwCtxt->ui32TopazCoreRev;
#		define	IS_REV(name) ((coreId >= MIN_ ## name ## _REV) && (coreId <= MAX_ ## name ## _REV))
		
#if defined(HW_3_X)
		if (( coreId >= CORE_REV_CONFIG_1_MIN ) && (coreId <= CORE_REV_CONFIG_1_MAX))
		{
			// For now, it is assumed that this revision ID means 8 context 2 pipe variant
			currentHWConfig = HW_CONFIG_8CONTEXT;
			targetFwPipes = 2;
		}
		else 
#endif		
		{
			currentHWConfig = HW_CONFIG_ALL_FEATURES;
#if defined(HW_4_0)
			if(IS_REV(40))
			{
				if(bForceSpecificPipeCount)
				{
					if(psFwCtxt->ui32HwNumPipes < 3)
					{
						targetFwPipes = 2;
					}
					else
					{
						targetFwPipes = psFwCtxt->ui32HwNumPipes;
						IMG_ASSERT(psFwCtxt->ui32HwNumPipes <= TOPAZHP_MAX_NUM_PIPES);
					}
				}
				else
				{
					targetFwPipes = 4;
				}
			}
            else
            {
                PRINT("Unsupported HW. CoreRev: 0x%08x\n", coreId);
                return IMG_ERR_UNDEFINED;
            }
#endif
#if defined(HW_3_X)
			if(IS_REV(39))
			{
				if((psFwCtxt->ui32HwNumPipes < 3)&&(bForceSpecificPipeCount))
				{
					targetFwPipes = 2;
				}
				else
				{
					targetFwPipes = 4;
				}
			}
			else if(IS_REV(36))
			{
				targetFwPipes = 3;
			}
			else
			{
				targetFwPipes = 2;
			}
#endif
		}
#		undef IS_REV
	}

	{
		/* Search for matching firmwares */
		
		IMG_UINT32 formatsIncluded = 0;
		IMG_UINT32 ii;
		IMG_BOOL bPreferredFWLocated = IMG_FALSE;
		IMG_UINT32 ui32RequestedSize = 0;
		struct IMG_COMPILED_FW_BIN_RECORD *selected, *iter;

		selected = IMG_NULL;

#if defined(HW_3_X)
		for(ii = 0; ii < ui32AllFirmwareBinariesCount; ii++)
		{
			iter = sAllFirmwareBinaries[ii];
			/* With HW_3_6, we want to allow 3 pipes if it was required, this is mainly for test purposes */
			if ( (strcmp("JPEG_H264", iter->sFormat) == 0) && (targetFwPipes != 3) )
			{
				bPreferredFWLocated = IMG_TRUE;
				ui32RequestedSize = (4 * iter->ui32DataSize + ( iter->ui32DataOrigin - MTX_DMA_MEMORY_BASE ));
				break;
			}
		}

		if ( bPreferredFWLocated 
			&& ui32RequestedSize <= psFwCtxt->ui32MtxRamSize
			&& currentHWConfig == iter->ui32HwConfig 
			&& iter->ui32Pipes >= targetFwPipes
			&& ((codecMask == CODEC_MASK_JPEG) || (codecMask == CODEC_MASK_H264))
			&& ((iter->ui32FormatsMask & codecMask) != 0)
			)
		{
			selected = iter;
		}
		else
#endif
#if defined(HW_4_0)
		for(ii = 0; ii < ui32AllFirmwareBinariesCount; ii++)
		{
			iter = sAllFirmwareBinaries[ii];
			if ( strcmp("JPEG_H264_VP8", iter->sFormat) == 0 )
			{
				bPreferredFWLocated = IMG_TRUE;
				ui32RequestedSize = (4 * iter->ui32DataSize + ( iter->ui32DataOrigin - MTX_DMA_MEMORY_BASE ));
				break;
			}
		}

		if ( bPreferredFWLocated 
			&& ui32RequestedSize <= psFwCtxt->ui32MtxRamSize
			&& currentHWConfig == iter->ui32HwConfig 
			&& iter->ui32Pipes >= targetFwPipes
			&& ((codecMask == CODEC_MASK_JPEG) || (codecMask == CODEC_MASK_H264) || (codecMask == CODEC_MASK_VP8))
			&& ((iter->ui32FormatsMask & codecMask) != 0)
			)
		{
			selected = iter;
		}
		else
#endif
		{
			for(ii = 0; ii < ui32AllFirmwareBinariesCount; ii++)
			{
				iter = sAllFirmwareBinaries[ii];
				if ( currentHWConfig != iter->ui32HwConfig ) // The hardware config modes need to match
				{
					continue;
				}
				formatsIncluded = iter->ui32FormatsMask;

				if( ((formatsIncluded & codecMask) != 0) && (codecMask == CODEC_MASK_JPEG || strcmp(sRcMode, iter->rcMode) == 0)) // no need to match RC for JPEG
				{
					/* This firmware matches by format / mode combination, now to check if it fits better than current best */
					if(
						(!selected) &&
						(iter->ui32Pipes >= targetFwPipes)
					)
					{
						/*
							Select firmware ether if it is first matchin one we've encountered or
							if it better matches desired number of pipes.
						*/
						selected = iter;
					}

					if(iter->ui32Pipes == targetFwPipes)
					{
						/* Found ideal firmware version */
						selected = iter;
						break;
					}
				}

			}
		}

		if(!selected)
		{
			PRINT("Failed to locate firmware for format '%s' and RC mode '%s'.\n", sFormat, sRcMode);
			return IMG_ERR_UNDEFINED;
		}
		else
		{
			PRINT("Using firmware: %s with %i pipes, hwconfig=%i (text size = %i, data size = %i) for requested codec: %s RC mode %s\n",
				selected->sFormat, selected->ui32Pipes, selected->ui32HwConfig, selected->ui32TextSize, selected->ui32DataSize, sFormat, sRcMode);
		}

		/* Export selected firmware to the fw context */
		psFwCtxt->ui32MTXTOPAZFWTextSize		= selected->ui32TextSize;
		psFwCtxt->ui32MTXTOPAZFWDataSize		= selected->ui32DataSize;
		psFwCtxt->pui32MTXTOPAZFWText			= selected->pui32Text;
		psFwCtxt->pui32MTXTOPAZFWData			= selected->pui32Data;
		psFwCtxt->ui32MTXTOPAZFWDataOrigin	= selected->ui32DataOrigin;
		psFwCtxt->ui32NumPipes = selected->ui32Pipes;
		psFwCtxt->intDefines.length = selected->ui32IntDefineCount;
		psFwCtxt->intDefines.names =  selected->pscIntDefineNames;
		psFwCtxt->intDefines.values = selected->pui32IntDefines;
		psFwCtxt->ui32SupportedCodecs = selected->ui32FormatsMask;
		psFwCtxt->ui32NumContexts = MTX_GetFwConfigInt(psFwCtxt, "TOPAZHP_MAX_NUM_STREAMS");
	}
	return IMG_ERR_OK;
}

/*!
******************************************************************************

 @Function              mtx_regIfUpload

 @Description

 Upload MTX text and data sections via register interface

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Input    ui32DataMem      : RAM ID for text/data section

 @Input    ui32Address      : Address to upload data to

 @Input    ui32Words        : Number of words of data to upload

 @Input    pui32Data        : Pointer to data to upload

 @Return   None

******************************************************************************/
static IMG_VOID
mtx_regIfUpload(
	IMG_FW_CONTEXT * psFwCtxt,
	const IMG_UINT32 ui32DataMem ,
	IMG_UINT32 ui32Address ,
	const IMG_UINT32 ui32Words ,
	const IMG_UINT32 *const pui32Data
)
{
	IMG_UINT32 ui32Loop,ui32Ctrl,ui32RamId,ui32Addr,ui32CurrBank = ~0;
	IMG_UINT32 nUploaded = 0;

	mtx_getMTXControlFromDash( psFwCtxt );

	TALREG_Poll32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_RAM_ACCESS_STATUS,
		TAL_CHECKFUNC_ISEQUAL,
		MASK_MTX_MTX_MTX_MCM_STAT,
		MASK_MTX_MTX_MTX_MCM_STAT,
		1000,
		5);

	for(ui32Loop=0 ; ui32Loop < ui32Words ; ui32Loop++)
	{
		ui32RamId = ui32DataMem + (ui32Address / psFwCtxt->ui32MtxBankSize);
		if( ui32RamId != ui32CurrBank )
		{
			ui32Addr = ui32Address>>2;
			ui32Ctrl = 0;
			ui32Ctrl = F_ENCODE(ui32RamId, MTX_MTX_MCMID) | F_ENCODE(ui32Addr, MTX_MTX_MCM_ADDR) | F_ENCODE(1, MTX_MTX_MCMAI);
			TALREG_WriteWord32(
				psFwCtxt->ui32MtxRegMemSpceId,
				MTX_CR_MTX_RAM_ACCESS_CONTROL,
				ui32Ctrl );
			ui32CurrBank = 	ui32RamId;
		}
		ui32Address+= 4;

		if(nUploaded>(1024*24))	// should this be RAM bank size??
			break;
		nUploaded+=4;

		TALREG_WriteWord32(
			psFwCtxt->ui32MtxRegMemSpceId,
			MTX_CR_MTX_RAM_ACCESS_DATA_TRANSFER,
			pui32Data[ui32Loop]);

		TALREG_Poll32(
			psFwCtxt->ui32MtxRegMemSpceId,
			MTX_CR_MTX_RAM_ACCESS_STATUS,
			TAL_CHECKFUNC_ISEQUAL,
			MASK_MTX_MTX_MTX_MCM_STAT,
			MASK_MTX_MTX_MTX_MCM_STAT,
			1000,
			5);
	}

	mtx_releaseMTXControlFromDash(psFwCtxt);
}


/*!
******************************************************************************

 @Function              mtx_dmacTransfer

 @Description

 Transfer memory between the Host and MTX via DMA.

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Input    channel          : DMAC channel to use (0 for TopazSC)

 @Input    hHostMemTransfer : IMG_HANDLE for the host memory

 @Input    hostMemOffset    : offset into the host memory

 @Input    ui32MtxAddr      : Address on MTX

 @Input    numWords         : size of transfer in 32-bit words (PW units)

 @Input    bRNW             : Read not Write (IMG_FALSE to write to the MTX)

 @Return   None

******************************************************************************/
IMG_VOID
mtx_dmacTransfer(
	IMG_FW_CONTEXT *psFwCtxt,
	IMG_UINT32 channel,
	struct MEMORY_INFO_TAG* hHostMemTransfer,
	IMG_UINT32 hostMemOffset,
	IMG_UINT32 ui32MtxAddr,
	IMG_UINT32 numWords,
	IMG_BOOL16 bRNW
)
{
	IMG_UINT32 irqStat;
	IMG_UINT32 countReg;
	IMG_HANDLE dmacRegId;
	IMG_HANDLE RegId;
	IMG_UINT32 ui32ConfigReg;
	IMG_UINT32 ui32MMU_STATUS = 0;

	IMG_UINT32 ui32DmacBurstSize = DMAC_BURST_2; // 2 * 128 bits = 32 bytes
	IMG_UINT32 ui32MtxBurstSize = 4;             // 4 * 2 * 32 bits = 32 bytes

	/* check the burst sizes */
	IMG_ASSERT( MTX_DMA_BURSTSIZE_BYTES == ui32DmacBurstSize * 16 );
	IMG_ASSERT( MTX_DMA_BURSTSIZE_BYTES == ui32MtxBurstSize * 8 );

	/* check transfer size matches burst width */
	IMG_ASSERT( 0 == ( numWords & ((MTX_DMA_BURSTSIZE_BYTES>>2)-1) ) );

	/* check DMA channel */
	IMG_ASSERT(channel < DMAC_MAX_CHANNELS);

	// check that no transfer is currently in progress
	dmacRegId = TAL_GetMemSpaceHandle("REG_DMAC");
	TALREG_ReadWord32(dmacRegId, IMG_SOC_DMAC_COUNT(channel), &countReg);
	IMG_ASSERT(0 == (countReg & (MASK_IMG_SOC_EN | MASK_IMG_SOC_LIST_EN)));
	
	/* check we don't already have a page fault condition */
#if defined(HW_3_X)
	RegId = TAL_GetMemSpaceHandle("REG_TOPAZHP_MULTICORE");
	TALREG_ReadWord32(RegId, TOPAZHP_TOP_CR_MMU_STATUS, &ui32MMU_STATUS);
#endif
#if defined(HW_4_0)
	RegId = TAL_GetMemSpaceHandle("REG_MMU");
	TALREG_ReadWord32(RegId, IMG_BUS4_MMU_STATUS0, &ui32MMU_STATUS);
#endif
	
	IMG_ASSERT(0 == ui32MMU_STATUS);

	if(ui32MMU_STATUS || (countReg & (MASK_IMG_SOC_EN | MASK_IMG_SOC_LIST_EN)))
	{
		/* DMA engine not idle or pre-existing page fault condition */
		psFwCtxt->bInitialized = IMG_FALSE;
		return;
	}

	// clear status of any previous interrupts
	TALREG_WriteWord32(
		dmacRegId, 
		IMG_SOC_DMAC_IRQ_STAT(channel),
		0);

	// and that no interrupts are outstanding
	TALREG_ReadWord32(dmacRegId, IMG_SOC_DMAC_IRQ_STAT(channel), &irqStat);
	IMG_ASSERT(0 == irqStat);

	//Give the DMAC access to the host memory via BIF
	//TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "Give DMAC access to system bus");
//	TALREG_WriteWord32(ui32TopazReg, TOPAZ_CR_IMG_TOPAZ_DMAC_MODE, 1);

	/* Write MTX DMAC registers (for current MTX) */
	/* MTX Address */
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_SYSC_CDMAA,
		ui32MtxAddr);

	/* MTX DMAC Config */
	ui32ConfigReg = F_ENCODE(ui32MtxBurstSize, MTX_BURSTSIZE) | 
		      F_ENCODE((bRNW?1:0), MTX_RNW) | 
			  F_ENCODE(1, MTX_ENABLE) | 
			  F_ENCODE(numWords, MTX_LENGTH);
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_SYSC_CDMAC,
		ui32ConfigReg	);

	/* Write System DMAC registers */
	/* per hold - allow HW to sort itself out */
	TALREG_WriteWord32(
		dmacRegId, 
		IMG_SOC_DMAC_PER_HOLD(channel), 
		16);

	if(!g_bUseSecureFwUpload)
	{
		writeMemoryRef(
			dmacRegId, 
			IMG_SOC_DMAC_SETUP(channel), 
			hHostMemTransfer, 
			hostMemOffset);
	}
	else
	{
		writeMemoryRefNoMMU(
			dmacRegId, 
			IMG_SOC_DMAC_SETUP(channel), 
			hHostMemTransfer, 
			hostMemOffset);
	}

	/* count reg */
	countReg = DMAC_VALUE_COUNT(DMAC_BSWAP_NO_SWAP, DMAC_PWIDTH_32_BIT, bRNW, DMAC_PWIDTH_32_BIT, numWords);
	countReg |= MASK_IMG_SOC_TRANSFER_IEN;	// generate an interrupt at end of transfer
	TALREG_WriteWord32(
		dmacRegId, 
		IMG_SOC_DMAC_COUNT(channel), 
		countReg);

	/* don't inc address, set burst size */
	TALREG_WriteWord32(
		dmacRegId, 
		IMG_SOC_DMAC_PERIPH(channel),
		DMAC_VALUE_PERIPH_PARAM(DMAC_ACC_DEL_0, IMG_FALSE, ui32DmacBurstSize) );

	/* Target correct MTX DMAC port */
	TALREG_WriteWord32(
		dmacRegId, 
		IMG_SOC_DMAC_PERIPHERAL_ADDR(channel), 
		MTX_CR_MTX_SYSC_CDMAT + REG_START_TOPAZ_MTX_HOST);

	// Finally, rewrite the count register with the enable bit set to kick off the transfer
	TALREG_WriteWord32(
		dmacRegId, 
		IMG_SOC_DMAC_COUNT(channel), 
		countReg | MASK_IMG_SOC_EN );

	//Wait for it to finish
	TALREG_Poll32(
		dmacRegId,
		IMG_SOC_DMAC_IRQ_STAT(channel),
		TAL_CHECKFUNC_ISEQUAL,
		F_ENCODE(1, IMG_SOC_TRANSFER_FIN), 
		F_ENCODE(1, IMG_SOC_TRANSFER_FIN),
		1000,
#if defined(IMG_KERNEL_MODULE)
		1000);
#else
		10000);
#endif
	TALREG_ReadWord32(dmacRegId, IMG_SOC_DMAC_COUNT(channel), &countReg);
#if defined(HW_3_X)
	TALREG_ReadWord32(RegId, TOPAZHP_TOP_CR_MMU_STATUS, &ui32MMU_STATUS);
#endif
#if defined(HW_4_0)
	TALREG_ReadWord32(RegId, IMG_BUS4_MMU_STATUS0, &ui32MMU_STATUS);
#endif
	if(ui32MMU_STATUS || (countReg & (MASK_IMG_SOC_EN | MASK_IMG_SOC_LIST_EN)))
	{
		/* DMA has failed or page faulted */
		psFwCtxt->bInitialized = IMG_FALSE;
	}

	//Clear the interrupt
	TALREG_WriteWord32(dmacRegId, IMG_SOC_DMAC_IRQ_STAT(channel), 0);

	//Give access back to Topaz Core
//	TALREG_WriteWord32(ui32TopazReg, TOPAZ_CR_IMG_TOPAZ_DMAC_MODE, 0);
}


/*!
******************************************************************************

 @Function              mtx_setTarget

 @Description

 Sets target MTX for DMA and register writes

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Input    bTargetAll       : IMG_TRUE indicates register and DMA writes go to all MTX

 @Return   None

******************************************************************************/
IMG_VOID
mtx_setTarget(
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_UINT32 ui32Reg = 0;
	ui32Reg = F_ENCODE(0, TOPAZHP_TOP_CR_WRITES_CORE_ALL);
	TALREG_WriteWord32(
		psFwCtxt->ui32TopazMulticoreRegId,
		TOPAZHP_TOP_CR_MULTICORE_CORE_SEL_0,
		ui32Reg );
}


/*!
******************************************************************************

 @Function              mtx_uploadfw

 @Description

 Upload text and data sections via DMA

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Return   None

******************************************************************************/
static IMG_VOID
mtx_uploadfw(
	TOPAZKM_DevContext *devContext,
	IMG_FW_CONTEXT *psFwCtxt
)
{
	struct MEMORY_INFO_TAG *pText, *pData;
	IMG_PVOID addLinText, addLinData;
	IMG_UINT32 ui32TextSize = psFwCtxt->ui32MTXTOPAZFWTextSize; //TextSize;
	IMG_UINT32 ui32DataSize = psFwCtxt->ui32MTXTOPAZFWDataSize; //DataSize;

	IMG_HANDLE ui32DmacRegId;

	ui32DmacRegId = TAL_GetMemSpaceHandle("REG_DMAC");

	TALPDUMP_ConsoleMessage(ui32DmacRegId, "Allocate device memory for firmware load");
	if(g_bUseSecureFwUpload)
	{
		if(!allocNonMMUMemory(devContext, ui32TextSize*4 + MTX_DMA_BURSTSIZE_BYTES, 64, IMG_FALSE, &pText ))
		{
			psFwCtxt->bInitialized=IMG_FALSE;
			return;
		}
		if(!allocNonMMUMemory(devContext, ui32DataSize*4 + MTX_DMA_BURSTSIZE_BYTES, 64, IMG_FALSE, &pData ))
		{
			freeMemoryNonMMU(&pText);
			psFwCtxt->bInitialized=IMG_FALSE;
			return;
		}
	}
	else
	{
		if(!allocMemory(devContext, ui32TextSize*4 + MTX_DMA_BURSTSIZE_BYTES, 64, IMG_FALSE, &pText ))
		{
			psFwCtxt->bInitialized=IMG_FALSE;
			return;
		}
		if(!allocMemory(devContext, ui32DataSize*4 + MTX_DMA_BURSTSIZE_BYTES, 64, IMG_FALSE, &pData ))
		{
			freeMemory(&pText, IMG_TRUE);
			psFwCtxt->bInitialized=IMG_FALSE;
			return;
		}
	}
		
	TALPDUMP_ConsoleMessage(ui32DmacRegId, "Copy firmware code and data to device memory");

	addLinText = getKMAddress(pText);
	IMG_MEMCPY(addLinText, psFwCtxt->pui32MTXTOPAZFWText, ui32TextSize*4);
	addLinData = getKMAddress(pData);
	IMG_MEMCPY(addLinData, psFwCtxt->pui32MTXTOPAZFWData, ui32DataSize*4);
	
	if(g_bUseSecureFwUpload)
	{
		updateNonMMUDeviceMemory(pText);
		updateNonMMUDeviceMemory(pData);
	}
	else
	{
		updateDeviceMemory(pText);
		updateDeviceMemory(pData);
	}

	/* adjust transfer sizes of text and data sections to match burst size */
	ui32TextSize = ((ui32TextSize*4 + (MTX_DMA_BURSTSIZE_BYTES-1)) & ~(MTX_DMA_BURSTSIZE_BYTES-1))/4;
	ui32DataSize = ((ui32DataSize*4 + (MTX_DMA_BURSTSIZE_BYTES-1)) & ~(MTX_DMA_BURSTSIZE_BYTES-1))/4;

	/* ensure that data section (+stack) will not wrap in memory */
	IMG_ASSERT( psFwCtxt->ui32MtxRamSize >= (psFwCtxt->ui32MTXTOPAZFWDataOrigin+(ui32DataSize*4)-MTX_DMA_MEMORY_BASE) );
	if(psFwCtxt->ui32MtxRamSize < (psFwCtxt->ui32MTXTOPAZFWDataOrigin+(ui32DataSize*4)-MTX_DMA_MEMORY_BASE))
	{
		psFwCtxt->bInitialized=IMG_FALSE;
	}

	/* data section is already prepared/cached */
	/* Transfer the text section */
	TALPDUMP_ConsoleMessage(ui32DmacRegId, "Load MTX firmware text section via DMAC");
	if(psFwCtxt->bInitialized)
	{	
		mtx_dmacTransfer(
			psFwCtxt,
			0,
			pText,
			0,
			MTX_DMA_MEMORY_BASE,
			ui32TextSize,
			IMG_FALSE);
	}
	/* Transfer the data section */
	if(psFwCtxt->bInitialized)
	{	
		TALPDUMP_ConsoleMessage(ui32DmacRegId, "Load MTX firmware data section via DMAC");
		mtx_dmacTransfer(
			psFwCtxt,
			0,
			pData,
			0,
			psFwCtxt->ui32MTXTOPAZFWDataOrigin,
			ui32DataSize,
			IMG_FALSE);
	}
	
	if(g_bUseSecureFwUpload)
	{
		freeMemoryNonMMU(&pText);
		freeMemoryNonMMU(&pData);
	}
	else
	{
		freeMemory(&pText, IMG_TRUE);
		freeMemory(&pData, IMG_TRUE);
	}

	/* Flush the MMU table cache used during code download */
	TOPAZKM_MMUFlushMMUTableCache();
	if(psFwCtxt->bInitialized)
	{	
		TALPDUMP_ConsoleMessage(ui32DmacRegId, "mtx_uploadfw complete!");
	}
}

/*
******************************************************************************

 @Function              MTX_Load

 @Description

 Load text and data sections onto an MTX.

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Input    eLoadMethod      : Method to use for loading code

 @Input    bTargetAll       : Load to one (IMG_FALSE) or all (IMG_TRUE) MTX

 @Return   None

******************************************************************************/
IMG_VOID
MTX_Load(
	IMG_HANDLE context,
	IMG_FW_CONTEXT *psFwCtxt,
	MTX_eLoadMethod eLoadMethod
)
{
	TOPAZKM_DevContext *devContext;
	//IMG_CHAR szName[25];
	//IMG_UINT32 ui32MVEAId;
	IMG_UINT32 ui32Reg;
	IMG_UINT16 i;

	devContext = (TOPAZKM_DevContext *)context;

	IMG_ASSERT( psFwCtxt->bInitialized );
	if(!psFwCtxt->bInitialized)
	{
		return;
	}

	psFwCtxt->eLoadMethod = eLoadMethod;

	// set target to current or all MTXs
	mtx_setTarget( psFwCtxt );

	// MTX Reset
	TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"MTX Reset");
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_SOFT_RESET,
		MASK_MTX_MTX_RESET);
	TAL_Wait(psFwCtxt->ui32MtxRegMemSpceId,6);

	/* marker around code load */
	TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"START_CODE_LOAD");

	switch ( eLoadMethod )
	{
	case MTX_LOADMETHOD_REGIF:
		// Code Upload
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"Upload the code\n");

		mtx_regIfUpload(
			psFwCtxt,
			MTX_CORE_CODE_MEM,
			0,  // load at base of memory
			psFwCtxt->ui32MTXTOPAZFWTextSize,
			psFwCtxt->pui32MTXTOPAZFWText );

		// Data Upload
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"Upload the Data\n");

		mtx_regIfUpload(
			psFwCtxt,
			MTX_CORE_DATA_MEM,
			psFwCtxt->ui32MTXTOPAZFWDataOrigin - MTX_DMA_MEMORY_BASE,
			psFwCtxt->ui32MTXTOPAZFWDataSize,
			psFwCtxt->pui32MTXTOPAZFWData );
		break;

	case MTX_LOADMETHOD_DMA:
		mtx_uploadfw(devContext, psFwCtxt);
		break;

	case MTX_LOADMETHOD_NONE:
		break;

	default:
		IMG_ASSERT( IMG_FALSE );
	}

	/* marker around code load */
	TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"END_CODE_LOAD");
	
	/* if we have had any failures up to this point then return now */
	if(!psFwCtxt->bInitialized)
	{
		return;
	}
	
	if ( eLoadMethod != MTX_LOADMETHOD_NONE )
	{
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"Initialise registers D0.5, D0.6 and D0.7");
		for(i=5;i<8;i++)
		{
			mtx_writeCoreReg(psFwCtxt, 0x1 | (i<<4), 0);
		}

		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"Initialise registers D1.5, D1.6 and D1.7");
		// Restore 8 Registers of D1 Bank
		// D1Re0, D1Ar5, D1Ar3, D1Ar1, D1RtP, D1.5, D1.6 and D1.7
		for(i=5;i<8;i++)
		{
			mtx_writeCoreReg(psFwCtxt, 0x2 | (i<<4), 0);
		}

		// Set Starting PC address
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "Set Starting PC address");
		mtx_writeCoreReg(psFwCtxt, MTX_PC, PC_START_ADDRESS);

		// Verify Starting PC
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "Verify Starting PC");
		ui32Reg = mtx_readCoreReg(psFwCtxt, MTX_PC);

		PRINT("PC_START_ADDRESS = 0x%08X\n", ui32Reg );
		IMG_ASSERT( ui32Reg == PC_START_ADDRESS );
	}

}


/*
******************************************************************************

 @Function              MTX_Deinitialize

 @Description

 Deinitialise the given MTX context structure

 @Input    psFwCtxt         : Pointer to the context of the target MTX

 @Return   None

******************************************************************************/
IMG_VOID
MTX_Deinitialize(
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_INT i;
	if( !psFwCtxt->bInitialized ) 
	{
		PRINT("Warning detected multi de-initialiseations\n");
	}

	for(i=0;i<TOPAZHP_MAX_POSSIBLE_STREAMS;i++)
	{
		if ( psFwCtxt->psMTXContextDataCopy[i] )
		{
			freeMemory( &psFwCtxt->psMTXContextDataCopy[i], IMG_TRUE );
		}
		psFwCtxt->psMTXContextDataCopy[i]=NULL;
	}

	if ( psFwCtxt->psMTXRegCopy )
	{
		TRACK_FREE( psFwCtxt->psMTXRegCopy );
		psFwCtxt->psMTXRegCopy =NULL;
	}
/*
	if ( psFwCtxt->psWriteBackMem )
	{
		freeMemory( &psFwCtxt->psWriteBackMem, IMG_TRUE );
	}
	*/

	psFwCtxt->bInitialized = IMG_FALSE;
}


/*
******************************************************************************

 @Function              MTX_Initialize

 @Description

 Initialise the given MTX context structure

 @Input    psFwCtxt       : Pointer to the context of the target MTX

 @Input    ui32CoreNum    : Core number of the MTX to target

 @Input    eCodec         : version of codec specific firmware to associate with this MTX

 @Return   None

******************************************************************************/
IMG_ERRORCODE 
MTX_PopulateFirmwareContext(
	IMG_CODEC eCodec,
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_CHAR szName[25];
	IMG_UINT32 ui32Size;
	IMG_UINT32 i;
#if !defined(IMG_KERNEL_MODULE)
	IMG_BOOL bPdumpState;
#endif

	if(psFwCtxt->bInitialized || psFwCtxt->bPopulated)
	{
		return IMG_ERR_COMPLETE;
	}

	/* initialise Context structure */
	psFwCtxt->ui32MtxRegMemSpceId = TAL_GetMemSpaceHandle("REG_MTX");
	psFwCtxt->ui32TopazMulticoreRegId = TAL_GetMemSpaceHandle("REG_TOPAZHP_MULTICORE");
#if defined(HW_4_0)
	psFwCtxt->ui32MMURegId = TAL_GetMemSpaceHandle("REG_MMU");
#endif	

#if !defined(IMG_KERNEL_MODULE)
	TALPDUMP_MemSpceCaptureEnable(psFwCtxt->ui32MtxRegMemSpceId, IMG_TRUE, &bPdumpState);
	TALPDUMP_MemSpceCaptureEnable(psFwCtxt->ui32TopazMulticoreRegId, IMG_TRUE, &bPdumpState);
#if defined(HW_4_0)
	TALPDUMP_MemSpceCaptureEnable(psFwCtxt->ui32MMURegId, IMG_TRUE, &bPdumpState);
#endif	
#endif	

	TALREG_ReadWord32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_TOPAZHP_CORE_REV, &psFwCtxt->ui32TopazCoreRev);
	psFwCtxt->ui32TopazCoreRev &= (MASK_TOPAZHP_TOP_CR_TOPAZHP_MAINT_REV | MASK_TOPAZHP_TOP_CR_TOPAZHP_MINOR_REV | MASK_TOPAZHP_TOP_CR_TOPAZHP_MAJOR_REV);
	TALREG_ReadWord32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_TOPAZHP_CORE_DES1, &psFwCtxt->ui32TopazCoreDes1);

	/* Number of hw pipes */
	{
		IMG_UINT32 pipeCnt;
		TALREG_ReadWord32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_HW_CFG, &pipeCnt);
		pipeCnt = (pipeCnt & MASK_TOPAZHP_TOP_CR_NUM_CORES_SUPPORTED);
		psFwCtxt->ui32HwNumPipes = pipeCnt;
	}

	IMG_ASSERT(psFwCtxt->ui32HwNumPipes > 0 && psFwCtxt->ui32HwNumPipes <= TOPAZHP_MAX_NUM_PIPES);

	for (i = 0; i < psFwCtxt->ui32HwNumPipes; i++) {
		SPRINT(szName, "REG_TOPAZHP_CORE_%d", i);
		psFwCtxt->aui32TopazRegMemSpceId[i] = TAL_GetMemSpaceHandle(szName);
	}

	TALREG_ReadWord32(
		psFwCtxt->ui32TopazMulticoreRegId,
		TOPAZHP_TOP_CR_MTX_DEBUG_MSTR,
		&psFwCtxt->ui32MtxDebugVal);

	/* last bank size */
	ui32Size = 0x1 << (F_EXTRACT( psFwCtxt->ui32MtxDebugVal, TOPAZHP_TOP_CR_MTX_MSTR_LAST_RAM_BANK_SIZE ) + 2);
	/* all other banks */
	psFwCtxt->ui32MtxBankSize = 0x1 << (F_EXTRACT( psFwCtxt->ui32MtxDebugVal, TOPAZHP_TOP_CR_MTX_MSTR_RAM_BANK_SIZE ) + 2);
	/* total RAM size */
	psFwCtxt->ui32MtxRamSize = ui32Size + ( psFwCtxt->ui32MtxBankSize * (F_EXTRACT( psFwCtxt->ui32MtxDebugVal, TOPAZHP_TOP_CR_MTX_MSTR_RAM_BANKS ) -1) );

	psFwCtxt->bDriverHasMtxCtrl = IMG_FALSE;
	psFwCtxt->ui32AccessControl = 0;

	psFwCtxt->ui8ActiveContextMask = 0;

	{
		if(mtx_selectFirmwareBuild(psFwCtxt, eCodec) != IMG_ERR_OK)
		{
			psFwCtxt->bPopulated = IMG_FALSE;
			psFwCtxt->bInitialized = IMG_FALSE;
			return 	IMG_ERR_UNDEFINED;
		}
	}

	if(psFwCtxt->ui32MTXTOPAZFWDataSize != 0)
	{
		/* check FW fits in memory */
		/* could also add stack size estimate */
		ui32Size = 4 * psFwCtxt->ui32MTXTOPAZFWDataSize;
		ui32Size += ( psFwCtxt->ui32MTXTOPAZFWDataOrigin - MTX_DMA_MEMORY_BASE );
		if (ui32Size > psFwCtxt->ui32MtxRamSize)
		{
				TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_PopulateFirmwareContext: ERROR - Firmware size larger than MTX memory.");
				IMG_ASSERT( psFwCtxt->ui32MtxRamSize > ui32Size );
				return IMG_ERR_MEMORY;
		}


	}

	psFwCtxt->bPopulated = IMG_TRUE;
	return IMG_ERR_OK;
}

IMG_VOID MTX_Initialize(IMG_HANDLE context, IMG_FW_CONTEXT * psFwCtxt)
{
	IMG_UINT32 i;
	TOPAZKM_DevContext *devContext = (TOPAZKM_DevContext *)context;
	if(psFwCtxt->bInitialized)
	{
		return;
	}

	if(psFwCtxt->ui32MTXTOPAZFWDataSize != 0)
	{

#if defined(HW_3_X)	
		psFwCtxt->psMTXRegCopy = TRACK_MALLOC(52*4);
#endif		
#if defined(HW_4_0)	
		psFwCtxt->psMTXRegCopy = TRACK_MALLOC(54*4);
#endif		
		for(i = 0; i< TOPAZHP_MAX_POSSIBLE_STREAMS ; i++)
		{
			allocMemory(
			    devContext,
				MTX_CONTEXT_SIZE,  
				64,
				IMG_FALSE,
				&psFwCtxt->psMTXContextDataCopy[i]);
		}

		psFwCtxt->bInitialized = IMG_TRUE;
	}
}


IMG_INT MTX_GetFwConfigInt(IMG_FW_CONTEXT const * const psFwCtxt, IMG_CHAR const * const name)
{
	const size_t maxLen = 1024;
	unsigned int ii;
	
	if(psFwCtxt->ui32MTXTOPAZFWDataSize == 0)
	{
		IMG_ASSERT(!"FW context structure is not initialised!");
		return -1;
	}

	for(ii = 0; ii < psFwCtxt->intDefines.length; ii++)
	{
		if(strncmp(psFwCtxt->intDefines.names[ii], name, maxLen) == 0)
		{
			return psFwCtxt->intDefines.values[ii];
		}
	}

	return -1;
}

/*
******************************************************************************

 @Function              MTX_Start

 @Description

 Start an MTX.

 @Input    psFwCtxt       : Pointer to the context of the target MTX

 @Return   None

******************************************************************************/
IMG_VOID
MTX_Start(
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_ASSERT( psFwCtxt->bInitialized );

	/* target only the current MTX */
	mtx_setTarget( psFwCtxt );

	// Turn on the thread
	TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "Turn on the thread");
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_ENABLE,
		MASK_MTX_MTX_ENABLE);
}


/*
******************************************************************************

 @Function              MTX_Stop

 @Description

 Stop an MTX.

 @Input    psFwCtxt       : Pointer to the context of the target MTX

 @Return   None

******************************************************************************/
IMG_VOID
MTX_Stop(
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_ASSERT( psFwCtxt->bInitialized );

	/* target only the current MTX */
	mtx_setTarget( psFwCtxt );

	// Turn off the thread by writing one to the MTX_TOFF field of the MTX_ENABLE register.
	TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "Turn off the thread");
	TALREG_WriteWord32(
		psFwCtxt->ui32MtxRegMemSpceId,
		MTX_CR_MTX_ENABLE,
		MASK_MTX_MTX_TOFF);
}


/*
******************************************************************************

 @Function              MTX_Kick

 @Description

 Kick an MTX.

 @Input    psFwCtxt       : Pointer to the context of the target MTX

 @Input    ui32KickCount  : The number of kicks to register

 @Return   None

******************************************************************************/
IMG_VOID MTX_Kick(
	IMG_FW_CONTEXT *psFwCtxt,
	IMG_UINT32 ui32KickCount
)
{
	IMG_ASSERT( psFwCtxt->bInitialized );

	/* target only the current MTX */
	mtx_setTarget( psFwCtxt );

    {
    	TALPDUMP_ConsoleMessage(psFwCtxt->ui32MtxRegMemSpceId,"Kick the MTX");
    	TALREG_WriteWord32(
    		psFwCtxt->ui32MtxRegMemSpceId,
    		MTX_CR_MTX_KICK,
    		ui32KickCount);
    }
}


/*
******************************************************************************

 @Function              MTX_WaitForCompletion

 @Description

 Wait for MTX to halt

 @Input    psFwCtxt        : Pointer to the MTX context

 @Return   None

******************************************************************************/
IMG_VOID
MTX_WaitForCompletion(
	IMG_FW_CONTEXT *psFwCtxt
)
{
	IMG_ASSERT( psFwCtxt->bInitialized );

	if ( MTX_LOADMETHOD_NONE != psFwCtxt->eLoadMethod )
	{
		/* target only the current MTX */
		mtx_setTarget( psFwCtxt );

		// Wait for the Completion
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "Wait for the Completion");
		TALREG_Poll32(
			psFwCtxt->ui32MtxRegMemSpceId,
			MTX_CR_MTX_ENABLE,
			TAL_CHECKFUNC_ISEQUAL,
			MASK_MTX_MTX_TOFF,
			MASK_MTX_MTX_TOFF|MASK_MTX_MTX_ENABLE,
			1000,
			5);
	}
}


IMG_UINT32 PollHWInactive(	IMG_FW_CONTEXT * psFwCtxt)
{
 return		TALREG_Poll32(
			psFwCtxt->ui32TopazMulticoreRegId,
			MTX_SCRATCHREG_IDLE,
			TAL_CHECKFUNC_ISEQUAL,
			F_ENCODE( FW_IDLE_STATUS_IDLE, FW_IDLE_REG_STATUS),
			MASK_FW_IDLE_REG_STATUS,
			1000,
			500);
}




/*
******************************************************************************

 @Function              MTX_SaveState

 @Description

 Save the state of the MTX.  Registers, Data section and Stack

 @Input    psFwCtxt        : Pointer to the MTX context

 @Return   None

******************************************************************************/

IMG_VOID
MTX_SaveState(
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_UINT32 * psMtxRegState;
	IMG_UINT32 ui32RegValue;
	IMG_UINT32 i;
	IMG_UINT32 ui32NumPipes;

	TALREG_ReadWord32( psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_HW_CFG, &ui32RegValue);
	ui32NumPipes = (ui32RegValue & MASK_TOPAZHP_TOP_CR_NUM_CORES_SUPPORTED);

	if ( psFwCtxt->bInitialized )
	{
		/* target only the current MTX */
		mtx_setTarget( psFwCtxt );

		// Wait for HW complete
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_SaveState: Wait for HW Completion");

		PollHWInactive(psFwCtxt);

		// Turn Off MTX
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_SaveState: Stop the MTX");

		MTX_Stop(psFwCtxt);
		MTX_WaitForCompletion(psFwCtxt); // Is this necessary if we're using MTX_Stop?

		psMtxRegState = psFwCtxt->psMTXRegCopy;

		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_SaveState: Storing MMU Control Register States");

		// Save the MMU Control Registers
#if defined(HW_3_X)
		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_DIR_LIST_BASE(0), psMtxRegState);
		psMtxRegState++;

#if !defined(IMG_KERNEL_MODULE)
		if(g_bDoingPdump)
		{
			TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_SaveState: Save a copy of MMU_DIR_LIST_BASE(0) in a pdump register to restore later");
			/* if we are pdumping we can't just read and write this register */
			TALINTVAR_ReadFromReg32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_DIR_LIST_BASE(0), psFwCtxt->ui32TopazMulticoreRegId, 1);
		}
#endif
		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_TILE(0), psMtxRegState);
		psMtxRegState++;

		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_TILE(1), psMtxRegState);
		psMtxRegState++;

		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_CONTROL2, psMtxRegState);
		psMtxRegState++;		

		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_CONTROL1, psMtxRegState);
		psMtxRegState++;

		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_CONTROL0, psMtxRegState);
		psMtxRegState++;
#endif
#if defined(HW_4_0)
		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_FIRMWARE_REG_7, psMtxRegState);
		psMtxRegState++;

		TALREG_ReadWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_DIR_BASE_ADDR(0), psMtxRegState);
		psMtxRegState++;

#if !defined(IMG_KERNEL_MODULE)
		if(g_bDoingPdump)
		{
			TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_SaveState: Save a copy of MMU_DIR_LIST_BASE(0) in a pdump register to restore later");
			/* if we are pdumping we can't just read and write this register */
			TALINTVAR_ReadFromReg32(psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_DIR_BASE_ADDR(0), psFwCtxt->ui32MMURegId, 1);
		}
#endif
		TALREG_ReadWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_TILE_CFG(0), psMtxRegState);
		psMtxRegState++;

		TALREG_ReadWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_TILE_CFG(1), psMtxRegState);
		psMtxRegState++;

		TALREG_ReadWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_ADDRESS_CONTROL, psMtxRegState);
		psMtxRegState++;		

		TALREG_ReadWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_CONTROL1, psMtxRegState);
		psMtxRegState++;

		TALREG_ReadWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_CONTROL0, psMtxRegState);
		psMtxRegState++;
#endif

		/* JMComp statistics registers */
		for (i=0; i<ui32NumPipes; i++)
		{
			TALREG_ReadWord32 (psFwCtxt->aui32TopazRegMemSpceId[i], TOPAZHP_CR_JMCOMP_RC_STATS, psMtxRegState);
			psMtxRegState++;
		}

		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_SaveState: Storing Clock Gating States");
		// Save the gating states of the clocks
		for (i=0; i<ui32NumPipes; i++)
		{
			TALREG_ReadWord32 (psFwCtxt->aui32TopazRegMemSpceId[i], TOPAZHP_CR_TOPAZHP_AUTO_CLOCK_GATING, psMtxRegState);
			psMtxRegState++;
			TALREG_ReadWord32 (psFwCtxt->aui32TopazRegMemSpceId[i], TOPAZHP_CR_TOPAZHP_MAN_CLOCK_GATING, psMtxRegState);
			psMtxRegState++;
		}

		/* interrupt enable register */
		TALREG_ReadWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, psMtxRegState);
		psMtxRegState++;

		
	}
}

/*
******************************************************************************

 @Function              MTX_RestoreState

 @Description

 Restore the state of the MTX.  Registers and complete MTX memory.

 @Input    psFwCtxt        : Pointer to the MTX context

 @Return   None

******************************************************************************/
IMG_VOID
MTX_RestoreState(
	IMG_HANDLE context,
	IMG_FW_CONTEXT * psFwCtxt
)
{
	IMG_UINT32 *psMtxRegState;
	IMG_UINT32 ui32RegValue;
	IMG_UINT32 i;
	IMG_UINT32 ui32NumPipes;
	TOPAZKM_DevContext *devContext = (TOPAZKM_DevContext *)context;

	TALREG_ReadWord32( psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_HW_CFG, &ui32RegValue);
	ui32NumPipes = (ui32RegValue & MASK_TOPAZHP_TOP_CR_NUM_CORES_SUPPORTED);

	if ( psFwCtxt->bInitialized )
	{

		{
			/* Clear registers used for Host-FW communications */
			TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "Clear registers used for Host-FW communications");
			TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId, MTX_SCRATCHREG_IDLE, 0);

			TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_FIRMWARE_REG_1 + (MTX_SCRATCHREG_BOOTSTATUS << 2), 0);

			TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_FIRMWARE_REG_1 + (MTX_SCRATCHREG_TOHOST << 2), 0);

			TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_FIRMWARE_REG_1 + (MTX_SCRATCHREG_TOMTX  << 2), 0);
		}

		if(g_bUseSecureFwUpload)
		{
			TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "----SecHost START-----------------------------------");

			/* We need to make sure the MMU is bypassed.  That will be automatic after the reset in hardware but the simulator needs it done explicitly */
			TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "Explicitly set MMU bypass (for simulator)");
#if defined(HW_3_X)
			TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_CONTROL0, F_ENCODE(1,TOPAZHP_TOP_CR_MMU_BYPASS_TOPAZ)); // Required only for simulator
#endif
#if defined(HW_4_0)
			// This reg holds different information now
			// Default is currently 0 (UPPER_ADDRESS_FIX, MMU_ENABLE_EXT_ADDRESSING, MMU_BYPASS)
			TALREG_WriteWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_ADDRESS_CONTROL, F_ENCODE(1,IMG_BUS4_MMU_BYPASS));
#endif
		}

		// target only the current MTX
		mtx_setTarget( psFwCtxt );

		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_RestoreState: Software reset MTX, IO and Cores");
		// write the topaz reset bits
		//1) Disable MTX by writing one to the MTX_TOFF field of the MTX_ENABLE register.
		TALREG_WriteWord32(psFwCtxt->ui32MtxRegMemSpceId, MTX_CR_MTX_ENABLE,	MASK_MTX_MTX_TOFF);

		//2) Software reset MTX only by writing 0x1 then 0x0 to the MULTICORE_SRST register.
		TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId,TOPAZHP_TOP_CR_MULTICORE_SRST,1);
		TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId,TOPAZHP_TOP_CR_MULTICORE_SRST,0);

		//3) Software reset MTX, cores, and IO by writing 0x7 then 0x0 to the MULTICORE_SRST register.
		TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId,TOPAZHP_TOP_CR_MULTICORE_SRST ,F_ENCODE(1,TOPAZHP_TOP_CR_IMG_TOPAZ_CORE_SOFT_RESET)| F_ENCODE(1,TOPAZHP_TOP_CR_IMG_TOPAZ_IO_SOFT_RESET)|F_ENCODE(1,TOPAZHP_TOP_CR_IMG_TOPAZ_MTX_SOFT_RESET));
		TALREG_WriteWord32(psFwCtxt->ui32TopazMulticoreRegId,TOPAZHP_TOP_CR_MULTICORE_SRST,0);

		// Reset MTX
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId,"MTX_RestoreState: MTX Reset");

		TALREG_WriteWord32(
			psFwCtxt->ui32MtxRegMemSpceId,
			MTX_CR_MTX_SOFT_RESET,
			MASK_MTX_MTX_RESET);
		TAL_Wait(psFwCtxt->ui32MtxRegMemSpceId,6);
		TALREG_WriteWord32(
			psFwCtxt->ui32MtxRegMemSpceId,
			MTX_CR_MTX_SOFT_RESET,
			0);


		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_RestoreState: Load firmware code and data");

		if(g_bUseSecureFwUpload)
		{
			// Restore MTX code and data
			MTX_Load(devContext, psFwCtxt, psFwCtxt->eLoadMethod);
			TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "----SecHost END-----------------------------------");
		}

		psMtxRegState = psFwCtxt->psMTXRegCopy;

		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_RestoreState: Restore MMU Control Register States");

		// Restore the MMU Control Registers
#if defined(HW_3_X)
		TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_DIR_LIST_BASE(0), *psMtxRegState); // Required
		psMtxRegState++;

#if !defined(IMG_KERNEL_MODULE)
		if(g_bDoingPdump)
		{
			TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_RestoreState: The MMU_DIR_LIST_BASE(0) register is an address and can't simply be written with an immediate value");
			/* if we are pdumping we can't just read and write this register */
			TALINTVAR_WriteToReg32(psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_DIR_LIST_BASE(0), psFwCtxt->ui32TopazMulticoreRegId, 1);
		}
#endif
		TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_TILE(0), *psMtxRegState);
		psMtxRegState++;

		TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_TILE(1), *psMtxRegState);
		psMtxRegState++;

		TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_CONTROL2, *psMtxRegState); // Required
		psMtxRegState++;

		TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_CONTROL1, *psMtxRegState); // Required
		psMtxRegState++;

		if(g_bUseSecureFwUpload)
		{
			/* in secure mode the firmware has to write the MMU_CONTROL0 register */
			TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "Write MMU control register value to CMD FIFO");
			TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_CMD_FIFO_WRITE, *psMtxRegState); // Required

		}
		else
		{
			{
				/* we do not want to run in secre FW mode so write a place holder to the FIFO that the firmware will know to ignore */
				TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "Write dummy value to CMD FIFO (Firmware will know to ignore it)");
				TALREG_WriteWord32(	psFwCtxt->ui32TopazMulticoreRegId,	TOPAZHP_TOP_CR_MULTICORE_CMD_FIFO_WRITE,TOPAZHP_NON_SECURE_FW_MARKER);
			}

			//*psMtxRegState &= ~0xC; //Don't write to bits 2 or 3 as they may cause unwanted cache flushes?
			TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MMU_CONTROL0, *psMtxRegState); // Required
#endif
#if defined(HW_4_0)		
		TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_FIRMWARE_REG_7, *psMtxRegState);
		psMtxRegState++;
			
		TALREG_WriteWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_DIR_BASE_ADDR(0), *psMtxRegState); // Required
		psMtxRegState++;

#if !defined(IMG_KERNEL_MODULE)
		if(g_bDoingPdump)
		{
			TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_RestoreState: The IMG_BUS4_MMU_DIR_BASE_ADDR(0) register is an address and can't simply be written with an immediate value");
			/* if we are pdumping we can't just read and write this register */
			TALINTVAR_WriteToReg32(psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_DIR_BASE_ADDR(0), psFwCtxt->ui32MMURegId, 1);
		}
#endif
		TALREG_WriteWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_TILE_CFG(0), *psMtxRegState);
		psMtxRegState++;

		TALREG_WriteWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_TILE_CFG(1), *psMtxRegState);
		psMtxRegState++;

		TALREG_WriteWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_ADDRESS_CONTROL, *psMtxRegState); // Required
		psMtxRegState++;

		TALREG_WriteWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_CONTROL1, *psMtxRegState); // Required
		psMtxRegState++;

		if(g_bUseSecureFwUpload)
		{
			/* in secure mode the firmware has to write the MMU_CONTROL0 register */
			TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "Write MMU control register value to CMD FIFO");
			TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_CMD_FIFO_WRITE, *psMtxRegState); // Required

		}
		else
		{
			{
				/* we do not want to run in secre FW mode so write a place holder to the FIFO that the firmware will know to ignore */
				TALPDUMP_Comment(psFwCtxt->ui32TopazMulticoreRegId, "Write dummy value to CMD FIFO (Firmware will know to ignore it)");
				TALREG_WriteWord32(	psFwCtxt->ui32TopazMulticoreRegId,	TOPAZHP_TOP_CR_MULTICORE_CMD_FIFO_WRITE,TOPAZHP_NON_SECURE_FW_MARKER);
			}

		//*psMtxRegState &= ~0xC; //Don't write to bits 2 or 3 as they may cause unwanted cache flushes?
		TALREG_WriteWord32 (psFwCtxt->ui32MMURegId, IMG_BUS4_MMU_CONTROL0, *psMtxRegState); // Required
#endif

			// Restore MTX code and data
			MTX_Load(devContext, psFwCtxt, psFwCtxt->eLoadMethod);
		}
		psMtxRegState++;

		/* JMComp statistics registers */
		for (i=0; i<ui32NumPipes; i++)
		{
			TALREG_WriteWord32 (psFwCtxt->aui32TopazRegMemSpceId[i], TOPAZHP_CR_JMCOMP_RC_STATS, *psMtxRegState);
			psMtxRegState++;
		}

		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_RestoreState: Restore Clock Gating States");
		// Restore the gating states of the clocks
		for (i=0; i<ui32NumPipes; i++)
		{
			TALREG_WriteWord32 (psFwCtxt->aui32TopazRegMemSpceId[i], TOPAZHP_CR_TOPAZHP_AUTO_CLOCK_GATING, *psMtxRegState);
			psMtxRegState++;
			TALREG_WriteWord32 (psFwCtxt->aui32TopazRegMemSpceId[i], TOPAZHP_CR_TOPAZHP_MAN_CLOCK_GATING, *psMtxRegState);
			psMtxRegState++;
		}

		/* interrupt enable register */
		TALREG_WriteWord32 (psFwCtxt->ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_HOST_INT_ENAB, *psMtxRegState);
		psMtxRegState++;
		
		TALPDUMP_Comment(psFwCtxt->ui32MtxRegMemSpceId, "MTX_RestoreState: Start the MTX");

		// Turn On MTX
		MTX_Start(psFwCtxt);

		/* Kick the MTX to get things running */
		MTX_Kick( psFwCtxt, 1 );

	}
}

/* EOF */
