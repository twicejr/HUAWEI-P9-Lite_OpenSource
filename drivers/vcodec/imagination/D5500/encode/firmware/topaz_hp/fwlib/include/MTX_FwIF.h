/*!
 *****************************************************************************
 *
 * @File       MTX_FwIF.h
 * @Title      MTX Firmware Interface Header File
 * @Description    MTX Firmware Interface with host driver
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

#ifndef _MTX_FWIF_H_
#define _MTX_FWIF_H_

#include "vxe_common.h"
#include "topazscfwif.h"

//#define VXE_MEASURE_MTX_CLK_FREQ

/*!
 ***********************************************************************************
 *
 * Description        : enum describing the MTX load method
 *
 ************************************************************************************/
typedef enum
{
	MTX_LOADMETHOD_NONE = 0,        //!< don't load MTX code
	MTX_LOADMETHOD_BACKDOOR,        //!< backdoor - writes MTX load data direct to out.res
	MTX_LOADMETHOD_REGIF,           //!< load mtx code via register interface
	MTX_LOADMETHOD_DMA,             //!< load mtx code via DMA

} MTX_eLoadMethod;


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
 ***********************************************************************************
 *
 * Description        : MTX Firmware Context Structure
 *
 ************************************************************************************/
typedef struct tag_IMG_FW_INT_DEFINES_TABLE
{
	IMG_UINT32 length;
	IMG_CHAR** names;
	IMG_UINT* values;
} IMG_FW_INT_DEFINES_TABLE;

typedef struct tag_IMG_FW_CONTEXT
{
	IMG_BOOL16 bInitialized;                  //!< IMG_TRUE if MTX core is initialized
	IMG_BOOL16 bPopulated;                  //!< IMG_TRUE if MTX firmware context had been populated with data
	IMG_UINT8  ui8ActiveContextMask;		//!< A bit mask of active encode contexts in the firmware

	MTX_eLoadMethod eLoadMethod;			//!< method used to load this MTX

	IMG_UINT32 ui32SupportedCodecs;         //!< Codec mask

	IMG_UINT32 ui32MtxDebugVal;             //!< Value in MTX Debug register (for RAM config)
	IMG_UINT32 ui32MtxRamSize;              //!< Size of MTX RAM
	IMG_UINT32 ui32MtxBankSize;             //!< Size of MTX RAM banks


	IMG_HANDLE ui32MtxRegMemSpceId;         //!< Memspace ID for MTX registers
	IMG_HANDLE aui32TopazRegMemSpceId[TOPAZHP_MAX_NUM_PIPES];       //!< Memspace ID for TOPAZ registers
	IMG_HANDLE ui32TopazMulticoreRegId;     //!< Memspace ID for TOPAZ multicore control registers
#if defined(HW_4_0)
	IMG_HANDLE ui32MMURegId;			    //!< Memspace ID for TOPAZ MMU registers
#endif	
	IMG_UINT32 ui32TopazCoreRev;			//!< Hardware core revision ID
	IMG_UINT32 ui32TopazCoreDes1;			//!< Hardware core designer (feature bits)

	IMG_BOOL16 bDriverHasMtxCtrl;             //!< IMG_TRUE if driver (not DASH) has control of MTX
	IMG_UINT32 ui32AccessControl;           //!< Use to get read/write access to MTX

	IMG_UINT32 ui32HwNumPipes;				//!< Number of pipes available in hardware
	IMG_UINT32 ui32NumPipes;				//!< Number of pipes supported by firmware
	IMG_UINT32 ui32NumContexts;				//!< Number of contexts supported by firmware

	struct MEMORY_INFO_TAG* psMTXContextDataCopy[TOPAZHP_MAX_POSSIBLE_STREAMS];  //!< Copy of MTX Context Data during hibernate
	IMG_UINT32 *psMTXRegCopy;				//!< Copy of MTX Register block during hibernate

	IMG_UINT32 ui32MTXTOPAZFWTextSize;      //!< Size of MTX Firmware Text Section in words
	IMG_UINT32 *pui32MTXTOPAZFWText;        //!< Pointer to MTX Firmware Text Section

	IMG_UINT32 ui32MTXTOPAZFWDataSize;      //!< Size of MTX Firmware Data Section in words
	IMG_UINT32 *pui32MTXTOPAZFWData;        //!< Pointer to MTX Firmware Data Section

	IMG_UINT32 ui32MTXTOPAZFWDataOrigin;  //!< Offset to location of Data section

	IMG_FW_INT_DEFINES_TABLE intDefines;
}IMG_FW_CONTEXT;


/*
******************************************************************************

 @Function              MTX_GetFirmwareContext

 @details

Populates MTX context structure

 @param    eCodec         : version of codec specific firmware to associate with this MTX

 @param    ui8NumPipes    : Number of pipes used

 @param    psFwCtxt       : Output context

 @return   IMG_ERRORCODE : Standard IMG_ERRORCODE

******************************************************************************/
IMG_ERRORCODE MTX_PopulateFirmwareContext(
	IMG_CODEC eCodec,
	IMG_FW_CONTEXT * psFwCtxt
);

/*
******************************************************************************

 @Function              MTX_Initialize

 @details

 Initialise the hardware using given (populated) MTX context structure

 @param    psFwCtxt       : Pointer to the context of the target MTX

 @return   None

******************************************************************************/
IMG_VOID MTX_Initialize(IMG_HANDLE context, IMG_FW_CONTEXT * psFwCtxt);

/*
******************************************************************************

 @Function              MTX_GetFwConfigInt

 @details

 Return the integer define used to compile given version of firmware.

 @param    psFwCtxt       : Pointer to the context of the target MTX

 @param    name       : Name of a define (string)

 @return   Value of define or -1 if not found.

******************************************************************************/
IMG_INT MTX_GetFwConfigInt(IMG_FW_CONTEXT const * const psFwCtxt, IMG_CHAR const * const name);


/*
******************************************************************************

 @Function              MTX_Load

 @details

 Load text and data sections onto an MTX.

 @param    psFwCtxt         : Pointer to the context of the target MTX

 @param    eLoadMethod      : Method to use for loading code

 @return   None

******************************************************************************/
IMG_VOID
MTX_Load(
	IMG_HANDLE context,
	IMG_FW_CONTEXT *psFwCtxt,
	MTX_eLoadMethod eLoadMethod);


/*!
 ***********************************************************************************
 * Function Name      : MTX_Deinitialize
 * Inputs             : 
 * Outputs            : 
 * Returns            : 
 * Description        : Deinitialises MTX and MTX control structure
 ************************************************************************************/
IMG_VOID MTX_Deinitialize(
	IMG_FW_CONTEXT *psFwCtxt );


/*!
 ***********************************************************************************
 * Function Name      : MTX_SaveState
 * Inputs             : 
 * Outputs            : 
 * Returns            : 
 * Description        : Saves MTX State -- Registers and Data Memory
 ************************************************************************************/
IMG_VOID MTX_SaveState(
	IMG_FW_CONTEXT *psFwCtxt);


/*!
 ***********************************************************************************
 * Function Name      : MTX_RestoreState
 * Inputs             : 
 * Outputs            : 
 * Returns            : 
 * Description        : Restores MTX State -- Registers and Data Memory
 ************************************************************************************/
IMG_VOID MTX_RestoreState(
	IMG_HANDLE context,
	IMG_FW_CONTEXT *psFwCtxt);


/*!
 ***********************************************************************************
 * Function Name      : MTX_Start
 * Inputs             : 
 * Outputs            : 
 * Returns            : 
 * Description        : 
 ************************************************************************************/
IMG_VOID MTX_Start(
	IMG_FW_CONTEXT *psFwCtxt);


/*!
 ***********************************************************************************
 * Function Name      : MTX_Stop
 * Inputs             : 
 * Outputs            : 
 * Returns            : 
 * Description        : 
 ************************************************************************************/
IMG_VOID
MTX_Stop(
	IMG_FW_CONTEXT * psFwCtxt);


/*!
 ************************************************************************************
 * Function Name      : MTX_Kick
 * Inputs             : 
 * Outputs            : 
 * Returns            : 
 * Description        : Kicks MTX
 ************************************************************************************/
IMG_VOID MTX_Kick(
	IMG_FW_CONTEXT *psFwCtxt,
	IMG_UINT32 ui32KickCount);


/*!
 ***********************************************************************************
 * Function Name      : MTX_WaitForCompletion
 * Inputs             : 
 * Outputs            : 
 * Returns            : 
 * Description        : Waits for MTX to halt
 ************************************************************************************/
IMG_VOID MTX_WaitForCompletion(
	IMG_FW_CONTEXT *psFwCtxt);



extern IMG_VOID
mtx_dmacTransfer(
	IMG_FW_CONTEXT *psFwCtxt,
	IMG_UINT32 channel,
	struct MEMORY_INFO_TAG* hHostMemTransfer,
	IMG_UINT32 hostMemOffset,
	IMG_UINT32 ui32MtxAddr,
	IMG_UINT32 numWords,
	IMG_BOOL16 bRNW
);



extern IMG_VOID
mtx_releaseMTXControlFromDash(
	IMG_FW_CONTEXT * psFwCtxt
);


extern IMG_VOID
mtx_setTarget(
	IMG_FW_CONTEXT * psFwCtxt
);
#endif

