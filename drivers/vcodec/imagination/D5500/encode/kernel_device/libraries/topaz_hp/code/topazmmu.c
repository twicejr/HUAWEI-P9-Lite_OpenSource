/*!
 *****************************************************************************
 *
 * @File       topazmmu.c
 * @Title      Topaz Core MMU functions.
 * @Description    Topaz Core mmu functions
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

/************************************************************** Header files */
#include "sysdev_utils.h"

#if defined (__PORT_FWRK__)
	#include "dman_api.h"
#endif

#if !defined (__TALMMU_NO_OS__)
	#include <sysos_api_km.h>
#endif

#include "img_types.h"
#include "tal.h"
#include "memmgr_km.h"
#include "defs.h"
#if defined(HW_4_0)
#include "e4500_public_regdefs.h"
#include "img_video_bus4_mmu_regs.h"
#endif
#if defined(HW_3_X)
#include "vxe_public_regdefs.h"
#endif
#include "hostutils.h"
#include "topazmmu.h"


#if defined (IMG_KERNEL_MODULE)
#define PRINT printk
#define SPRINT sprintf
#else
#define PRINT printf
#define SPRINT sprintf
#endif

/************************************************** Globals */

IMG_BOOL g_bUseTiledMemory = IMG_FALSE;
IMG_BOOL g_bUseInterleavedTiling = IMG_FALSE;
IMG_BOOL g_bUseExtendedAddressing = IMG_FALSE;
IMG_UINT32 g_ui32MMUTileStride = 0;
IMG_UINT32 	g_MMU_ControlVal;
struct Topaz_CoreMMUContext {
	IMG_HANDLE Topaz_Core_mmu_context;
	IMG_UINT32 ptd_phys_addr;
} hTopaz_CoreMMUContext = { IMG_NULL, 0};

IMG_HANDLE hPageTableDirectory = IMG_NULL;
IMG_BOOL g_bUseSecureFwUpload = IMG_FALSE;

extern SYSDEVU_sInfo topaz_device;
//extern IMG_UINT32 gui32SysMemId;

/************************************************** Internal data structures */
enum heap_ids
{
		MMU_TILED_HEAP_ID		= 0x00,
		MMU_GENERAL_HEAP_ID		= 0x01,
		// Do not remove - keeps count of size
		HEAP_ID_NO_OF_HEAPS
};

// These determine the sizes of the MMU heaps we are using.
// The tiled heap is set arbitrarily large at present.
#define TILEDMMUHEAPLENGTH   0x40000000
// The general heap is set arbitrarily large at present.
#define GENERALMMUHEAPLENGTH 0x40000000

/* This describes the heaps - the separate areas mapped by the MMU
   Currently we only use a single large heap as Topaz Core has no MMU specific memory features.*/
TALMMU_sHeapInfo	asMMU_HeapInfo [HEAP_ID_NO_OF_HEAPS]=
{
	/* Heap Id					Heap type,					Heap Flags,						Mem space name,		Start addr,								Length,						bTiled,		Tile Stride	*/
	{ MMU_TILED_HEAP_ID,		TALMMU_HEAP_PERCONTEXT,		TALMMU_HEAPFLAGS_NONE,			"MEMSYSMEM",		0x00400000+GENERALMMUHEAPLENGTH,		TILEDMMUHEAPLENGTH,			IMG_TRUE,	DEFAULT_TILE_STRIDE	},
	{ MMU_GENERAL_HEAP_ID,		TALMMU_HEAP_PERCONTEXT,		TALMMU_HEAPFLAGS_NONE,			"MEMSYSMEM",		0x00400000 ,			                GENERALMMUHEAPLENGTH,		0,			0	}
};

/* This describes the memory being mapped by the MMU */
TALMMU_sDevMemInfo	sMMU_DeviceMemoryInfo = {
		1, /* ui32DeviceId */
		TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR, /* eMMUType */
		TALMMU_MMUTILING_SCHEME_0, /* eTilingScheme */
		TALMMU_DEVFLAGS_NONE, /* eDevFlags */
		"MEMSYSMEM", /* pszPageDirMemSpaceName */
		"MEMSYSMEM", /* pszPageTableMemSpaceName */
		4096, /* ui32PageSize */
		0, /* ui32PageTableDirAlignment */
		0, /* eMemAttrib */
		0, /* eMemPool */
		(IMG_CHAR *)&TOPAZ_DEV_NAME /* pszDeviceName */
};


/*!
******************************************************************************

 @Function				Topaz_MMU_EventCallback

******************************************************************************/
IMG_RESULT Topaz_MMU_EventCallback (
    TALMMU_eEvent               eEvent,
    IMG_VOID *                  pCallbackParameter,
    IMG_UINT32                  ui32IntRegIdOrAddr,
    IMG_HANDLE  			    hMemSpac
) {
	switch(eEvent)
	{
	case TALMMU_EVENT_WRITE_PAGE_DIRECTORY_REF: {
#ifndef SYSBRG_NO_BRIDGING
		struct Topaz_CoreMMUContext *ctx = (struct Topaz_CoreMMUContext *)pCallbackParameter;
		ctx->ptd_phys_addr = ui32IntRegIdOrAddr;
#endif
		break;
	}
	case TALMMU_EVENT_FLUSH_CACHE:
		Topaz_Core_MMU_FlushCache();
		break;
	default:
		break;
	}
	return IMG_SUCCESS;
}


IMG_HANDLE hMMUTemplate = IMG_NULL;

/*!
******************************************************************************

 @function              Topaz_Core_MMU_Configure

@details	Called once during initialisation to intitialise the MMU hardware, create the template and define the MMU heap.



 @return   IMG_BOOL : BOOLEAN indicating success or failure

******************************************************************************/
IMG_BOOL Topaz_Core_MMU_Configure(IMG_VOID)
{
	IMG_UINT32 ui32i;
	IMG_RESULT result;
	IMG_UINT32 ui32XTileStride = 0;
	IMG_HANDLE ui32TopazMulticoreRegId;
#if defined(HW_4_0)
	IMG_HANDLE ui32MMUId;
#endif	
	IMG_UINT32 ui32HWRev;

	/* This describes the memory being mapped by the MMU */
	TALMMU_sDevMemInfo	sMMU_DeviceMemoryInfo = {1,TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR,TALMMU_MMUTILING_SCHEME_0,TALMMU_DEVFLAGS_NONE, "MEMSYSMEM", "MEMSYSMEM", 4096};

#ifdef __TALMMU_USE_PALLOC__
	{
		//***************** INITIALISING MMU SUPPORT - Do this once only
		IMG_UINT32        ui32AttachId;
		IMG_UINT32        ui32Result;

		ui32Result = PALLOC_Initialise();

		IMG_ASSERT(ui32Result == IMG_SUCCESS);

		ui32Result = PALLOC_AttachToConnection(ui32ConnId, &ui32AttachId);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		sMMU_DeviceMemoryInfo.ui32AttachId     = ui32AttachId;
	}
#endif

	sMMU_DeviceMemoryInfo.eMemAttrib = (SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE);
	sMMU_DeviceMemoryInfo.eMemPool = topaz_device.sMemPool;

	/* Initialise TALMMU API and create a template */
	result = TALMMU_Initialise();
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
	{
		return IMG_FALSE;
	}

#if defined(HW_4_0)
	ui32MMUId = TAL_GetMemSpaceHandle("REG_MMU");
#endif	
	ui32TopazMulticoreRegId = TAL_GetMemSpaceHandle("REG_TOPAZHP_MULTICORE");

	TALREG_ReadWord32(ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_TOPAZHP_CORE_REV, &ui32HWRev);
	ui32HWRev &= (MASK_TOPAZHP_TOP_CR_TOPAZHP_MAINT_REV | MASK_TOPAZHP_TOP_CR_TOPAZHP_MINOR_REV | MASK_TOPAZHP_TOP_CR_TOPAZHP_MAJOR_REV);

	if (g_bUseExtendedAddressing)
	{
		IMG_UINT32 ui32RegVal;

		if (ui32HWRev >= MIN_36_REV)
		{
			// Versions 3.6 and above may be 32-bit, 36-bit or 40-bit
			TALREG_ReadWord32(ui32TopazMulticoreRegId, TOPAZHP_TOP_CR_MULTICORE_HW_CFG, &ui32RegVal);

			switch (F_DECODE(ui32RegVal, TOPAZHP_TOP_CR_EXTENDED_ADDR_RANGE))
			{
			case 0:
				sMMU_DeviceMemoryInfo.eMMUType = TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR;
				break;
			case 4:
				sMMU_DeviceMemoryInfo.eMMUType = TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR;
				break;
			case 8:
				sMMU_DeviceMemoryInfo.eMMUType = TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR;
				break;
			default:
				return IMG_FALSE;
				break;
			}
		}
		else if (ui32HWRev >= MIN_34_REV)
		{
			// 3.4 only supports 36-bit
			sMMU_DeviceMemoryInfo.eMMUType = TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR;
		}
		else
		{
			// 3.0 and 3.2 don't support extended addressing
			return IMG_FALSE;
		}
	}

	if (g_bUseTiledMemory)
	{
		sMMU_DeviceMemoryInfo.eTilingScheme = TALMMU_MMUTILING_SCHEME_0; /* Our hardware only support 256x16 tiles */

		ui32XTileStride = 0;
		while ((IMG_UINT32)(512 << ui32XTileStride) < g_ui32MMUTileStride) ui32XTileStride++;

	}

	sMMU_DeviceMemoryInfo.pszDeviceName = (IMG_CHAR *)&TOPAZ_DEV_NAME;
	result = TALMMU_DevMemTemplateCreate (&sMMU_DeviceMemoryInfo, &hMMUTemplate);
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
	{
		TALMMU_Deinitialise();
		return IMG_FALSE;
	}

        result = TALMMU_AddCallback(hMMUTemplate, Topaz_MMU_EventCallback, IMG_NULL);
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
	{
		TALMMU_DevMemTemplateDestroy(hMMUTemplate);
		TALMMU_Deinitialise();
		return IMG_FALSE;
	}

	// Add heaps to the template
	for (ui32i=0;ui32i<HEAP_ID_NO_OF_HEAPS;ui32i++)
	{
		if(asMMU_HeapInfo[ui32i].bTiled == IMG_TRUE && g_bUseInterleavedTiling)
		{
			if ((ui32HWRev >= 0x30908) && (ui32HWRev < MIN_40_REV))
			{
				/* from hardware rev 3.9.8 TopazHP has a different interleaved tile mode */
				asMMU_HeapInfo[ui32i].eHeapFlags |= TALMMU_HEAPFLAGS_256BYTE_INTERLEAVE;
			}
			else
			{
				asMMU_HeapInfo[ui32i].eHeapFlags |= TALMMU_HEAPFLAGS_128BYTE_INTERLEAVE;
			}
		}
		asMMU_HeapInfo[ui32i].ui32XTileStride = ui32XTileStride;
		result = TALMMU_DevMemHeapAdd (hMMUTemplate, &(asMMU_HeapInfo[ui32i]));
		IMG_ASSERT(result == IMG_SUCCESS);
		if(result != IMG_SUCCESS)
		{
			TALMMU_DevMemTemplateDestroy(hMMUTemplate);
			TALMMU_Deinitialise();
			return IMG_FALSE;
		}

	}

	// Create a context from the template
	result = TALMMU_DevMemContextCreate(hMMUTemplate, 1, &hTopaz_CoreMMUContext.Topaz_Core_mmu_context); // (Template, User allocated user ID)
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
	{
		TALMMU_DevMemTemplateDestroy(hMMUTemplate);
		TALMMU_Deinitialise();
		return IMG_FALSE;
	}

        result = TALMMU_DevMemContextSetMMUPtd(hTopaz_CoreMMUContext.Topaz_Core_mmu_context, &hTopaz_CoreMMUContext);
	if(result != IMG_SUCCESS)
	{
		TALMMU_DevMemTemplateDestroy(hMMUTemplate);
		TALMMU_Deinitialise();
		return IMG_FALSE;
	}
    
	TOPAZKM_MMUFlushMMUTableCache();

	if (g_bUseTiledMemory)
	{
		IMG_UINT32 ui32TiledHeap;
		ui32TiledHeap = 0;
		for (ui32i = 0; ui32i < HEAP_ID_NO_OF_HEAPS; ui32i++)
		{
			if (asMMU_HeapInfo[ui32i].bTiled)
			{
				IMG_ASSERT(ui32TiledHeap < 2);
#if defined(HW_4_0)				
				TALREG_WriteWord32(ui32MMUId,
					IMG_BUS4_MMU_TILE_CFG(ui32TiledHeap),
						F_ENCODE(1, IMG_BUS4_TILE_ENABLE) |
						F_ENCODE(asMMU_HeapInfo[ui32i].ui32XTileStride, IMG_BUS4_TILE_STRIDE));
				TALREG_WriteWord32(ui32MMUId, IMG_BUS4_MMU_TILE_MAX_ADDR(ui32TiledHeap), F_ENCODE((asMMU_HeapInfo[ui32i].ui32BaseDevVirtAddr + asMMU_HeapInfo[ui32i].ui32Size), IMG_BUS4_TILE_MAX_ADDR));
				TALREG_WriteWord32(ui32MMUId, IMG_BUS4_MMU_TILE_MIN_ADDR(ui32TiledHeap++), F_ENCODE(asMMU_HeapInfo[ui32i].ui32BaseDevVirtAddr, IMG_BUS4_TILE_MIN_ADDR));
#endif
#if defined(HW_3_X)
				TALREG_WriteWord32(ui32TopazMulticoreRegId,
						TOPAZHP_TOP_CR_MMU_TILE(ui32TiledHeap++),
						F_ENCODE(1, TOPAZHP_TOP_CR_TILE_ENABLE) |
						F_ENCODE(asMMU_HeapInfo[ui32i].ui32XTileStride, TOPAZHP_TOP_CR_TILE_STRIDE) |
						F_ENCODE((asMMU_HeapInfo[ui32i].ui32BaseDevVirtAddr + asMMU_HeapInfo[ui32i].ui32Size) >> 20, TOPAZHP_TOP_CR_TILE_MAX_ADDR) |
						F_ENCODE(asMMU_HeapInfo[ui32i].ui32BaseDevVirtAddr >> 20, TOPAZHP_TOP_CR_TILE_MIN_ADDR) |
						F_ENCODE((asMMU_HeapInfo[ui32i].eHeapFlags & (TALMMU_HEAPFLAGS_128BYTE_INTERLEAVE | TALMMU_HEAPFLAGS_256BYTE_INTERLEAVE))?1:0,TOPAZHP_TOP_CR_TILE_128BYTE_INTERLEAVE));
#endif				
			}
		}
	}

	return IMG_TRUE;
}



/*!
******************************************************************************

 @function              Topaz_Core_MMU_HWSetup

 @details			 Called for each Topaz core when MMU support is activated, sets up the MMU hardware for the specified core.
					(Must be called after sim output capture has been enabled)

 @param    IMG_UINT32 ui32TCoreReg	: Topaz Core Register ID	


 @return   IMG_BOOL  : indicating success or failure

******************************************************************************/
IMG_BOOL Topaz_Core_MMU_HWSetup(IMG_HANDLE ui32TCoreReg)
{
	IMG_UINT32 ui32Cmd;
#ifdef SYSBRG_NO_BRIDGING
	IMG_RESULT result;
	IMG_UINT8 uiByteShift;
	IMG_UINT32 ui32CoreRev;
	IMG_UINT32 ui32RegVal;
#endif
	IMG_HANDLE ui32SysMemId;
#if defined(HW_4_0)
	IMG_HANDLE ui32MMUId;
#endif

#ifdef SYSBRG_NO_BRIDGING
	// Obtain page table directory handle
	result = TALMMU_DevMemContextGetPtd(hTopaz_CoreMMUContext.Topaz_Core_mmu_context, &hPageTableDirectory);
#endif
	
	//	Register ID is now provided to the function (each Core done seperately)
	//ui32HpCoreRegId = TAL_GetMemSpaceHandle("REG_TOPAZHP_CORE_0");

	ui32SysMemId = TAL_GetMemSpaceHandle("MEMSYSMEM");
#if defined(HW_4_0)
	ui32MMUId = TAL_GetMemSpaceHandle("REG_MMU");
#endif	

	// Bypass all requesters while MMU is being configured
	// Bypass requestors (listed in TRM)
#if defined(HW_4_0)	
	ui32Cmd = F_ENCODE(1, IMG_BUS4_MMU_BYPASS);
	TALREG_WriteWord32 ( ui32MMUId, IMG_BUS4_MMU_ADDRESS_CONTROL, ui32Cmd );
#endif
#if defined(HW_3_X)
	ui32Cmd = F_ENCODE(1, TOPAZHP_TOP_CR_MMU_BYPASS_TOPAZ);
	TALREG_WriteWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL0, ui32Cmd );
#endif	
		
#ifdef SYSBRG_NO_BRIDGING
	TALREG_ReadWord32(ui32TCoreReg, TOPAZHP_TOP_CR_TOPAZHP_CORE_REV, &ui32CoreRev);
	ui32CoreRev &= (MASK_TOPAZHP_TOP_CR_TOPAZHP_MAINT_REV | MASK_TOPAZHP_TOP_CR_TOPAZHP_MINOR_REV | MASK_TOPAZHP_TOP_CR_TOPAZHP_MAJOR_REV);
	uiByteShift=0;
	if(g_bUseExtendedAddressing)
	{
		if (ui32CoreRev >= MIN_36_REV)
		{
			// Versions 3.6 and above may be 32-bit, 36-bit or 40-bit
			TALREG_ReadWord32(ui32TCoreReg, TOPAZHP_TOP_CR_MULTICORE_HW_CFG, &ui32RegVal);
			uiByteShift=(IMG_UINT8) (F_DECODE(ui32RegVal, TOPAZHP_TOP_CR_EXTENDED_ADDR_RANGE));
			// 0=32 bits
			// 4=36 bit
			// 8=40 bit
		}
		else if (ui32CoreRev >= MIN_34_REV)
		{ // only supports 36 bit
			uiByteShift=4;
		}
	}

	TALINTVAR_WriteMemRef(hPageTableDirectory, 0, ui32TCoreReg, 1);
    TALINTVAR_RunCommand( TAL_PDUMPL_INTREG_SHR,
                                        ui32TCoreReg, 1,
                                        ui32TCoreReg, 1,
								        ui32TCoreReg, uiByteShift, IMG_FALSE );

#if defined(HW_4_0)	
    TALINTVAR_WriteToReg32(ui32MMUId,IMG_BUS4_MMU_DIR_BASE_ADDR(0),ui32TCoreReg, 1);
#endif
#if defined(HW_3_X)	
    TALINTVAR_WriteToReg32(ui32TCoreReg,TOPAZHP_TOP_CR_MMU_DIR_LIST_BASE(0),ui32TCoreReg, 1);
#endif
#else
#if defined(HW_4_0)	
    TALREG_WriteWord32(ui32MMUId, IMG_BUS4_MMU_DIR_BASE_ADDR(0), hTopaz_CoreMMUContext.ptd_phys_addr);
#endif
#if defined(HW_3_X)	
    TALREG_WriteWord32(ui32TCoreReg, TOPAZHP_TOP_CR_MMU_DIR_LIST_BASE(0), hTopaz_CoreMMUContext.ptd_phys_addr);
#endif
#endif
  


#if defined(HW_4_0)
	TALREG_ReadWord32(ui32MMUId,IMG_BUS4_MMU_DIR_BASE_ADDR(0),&ui32Cmd);
#endif
#if defined(HW_3_X)
	TALREG_ReadWord32(ui32TCoreReg,TOPAZHP_TOP_CR_MMU_DIR_LIST_BASE(0),&ui32Cmd);
#endif
	
	PRINT("Page table directory at physical address 0x%08x\n", ui32Cmd);
	// Set up the Index Register (to point to the base register)
	ui32Cmd=0; // We're setting all fields to zero (all flags pointing to directory bank 0)
//	TALREG_WriteWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_BANK_INDEX, ui32Cmd);


	// Now enable MMU access for all requesters
	// Enable requestors (listed in TRM)
#if defined(HW_4_0)
	g_MMU_ControlVal = F_ENCODE(0, IMG_BUS4_MMU_BYPASS);

	ui32Cmd = F_ENCODE(g_bUseExtendedAddressing ? 1 : 0, IMG_BUS4_MMU_ENABLE_EXT_ADDRESSING); 
	g_MMU_ControlVal |= ui32Cmd;

	if(g_bUseSecureFwUpload)
	{
		/* in secure FW mode we need to write the bits without switching off MMU bypass (which iwll be done by the FW later) */
		TALREG_WriteWord32 ( ui32MMUId, IMG_BUS4_MMU_ADDRESS_CONTROL, ui32Cmd | F_ENCODE(1, IMG_BUS4_MMU_BYPASS) );
	}
	else
	{
		TALREG_WriteWord32 ( ui32MMUId, IMG_BUS4_MMU_ADDRESS_CONTROL, g_MMU_ControlVal );
	}
#endif

#if defined(HW_3_X)
	ui32Cmd = F_ENCODE(g_bUseExtendedAddressing ? 1 : 0, TOPAZHP_TOP_CR_MMU_ENABLE_36BIT_ADDRESSING); // 36-bit actually means "not 32-bit"
	TALREG_WriteWord32(ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL2, ui32Cmd);

	g_MMU_ControlVal = ui32Cmd= F_ENCODE(0, TOPAZHP_TOP_CR_MMU_BYPASS_TOPAZ);

	if(!g_bUseSecureFwUpload)
		TALREG_WriteWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL0, ui32Cmd );
#endif

	return IMG_TRUE;
}

/*!
******************************************************************************

 @function              Topaz_Core_MMU_FlushCache

 @details			



 @return   IMG_BOOL : Boolean indicating success or failure

******************************************************************************/
IMG_BOOL Topaz_Core_MMU_FlushCache(IMG_VOID)
{
#if defined(HW_3_X)
	static IMG_HANDLE ui32TCoreReg = IMG_NULL;
#endif	
	IMG_UINT32 ui32RegValue;
#if defined(HW_4_0)
	IMG_HANDLE ui32MMUReg;
#endif	

#if defined(HW_3_X)
    if(ui32TCoreReg == IMG_NULL) {
		ui32TCoreReg = TAL_GetMemSpaceHandle("REG_TOPAZHP_MULTICORE");
    }
#endif	

#if !defined (__TALMMU_NO_OS__)
    /* Disable interrupts */
    SYSOSKM_DisableInt();
#endif

#if defined(HW_4_0)
	ui32MMUReg = TAL_GetMemSpaceHandle("REG_MMU");
	
	// Following code translated from MSVDX implementation
	// Write the invalid cache line, instead of flush 

			TALREG_ReadWord32 ( ui32MMUReg, IMG_BUS4_MMU_CONTROL1, &ui32RegValue );


			ui32RegValue |= F_ENCODE(1, IMG_BUS4_MMU_INVALDC(0)); // Set Invalid flag (this causes a flush with MMU still operating afterwards even if not cleared, but may want to replace with MMU_FLUSH?


			TALREG_WriteWord32 ( ui32MMUReg, IMG_BUS4_MMU_CONTROL1, ui32RegValue ); //Write Invalid flag


#endif
#if defined(HW_3_X)
	TALREG_ReadWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL0, &ui32RegValue );

	// PAUSE
	ui32RegValue |= F_ENCODE(1, TOPAZHP_TOP_CR_MMU_PAUSE);
	TALREG_WriteWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL0, ui32RegValue);

	{
		IMG_UINT32 i, ui32MemReqReg;
wait_till_idle:
		for(i = 0; i < 10; i++)
		{
			TALREG_ReadWord32 (ui32TCoreReg, TOPAZHP_TOP_CR_MMU_MEM_REQ, &ui32MemReqReg);
			if (ui32MemReqReg != 0)
				goto wait_till_idle;
		}
	}

	// Set invalidate
	ui32RegValue |= F_ENCODE(1, TOPAZHP_TOP_CR_MMU_INVALDC);
	TALREG_WriteWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL0, ui32RegValue);

	// Clear invalidate
	ui32RegValue &= ~((IMG_UINT32)F_ENCODE(1, TOPAZHP_TOP_CR_MMU_INVALDC));
	TALREG_WriteWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL0, ui32RegValue);


	// UNPAUSE
	ui32RegValue &= ~((IMG_UINT32)F_ENCODE(1, TOPAZHP_TOP_CR_MMU_PAUSE));
	TALREG_WriteWord32 ( ui32TCoreReg, TOPAZHP_TOP_CR_MMU_CONTROL0, ui32RegValue);

#endif

#if !defined (__TALMMU_NO_OS__)
    /* Re-enable interrupts */
    SYSOSKM_EnableInt();
#endif
  return IMG_SUCCESS;
}



