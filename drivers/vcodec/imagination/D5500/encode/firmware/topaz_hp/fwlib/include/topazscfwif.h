/*!
 *****************************************************************************
 *
 * @File       topazscfwif.h
 * @Title      VXE Firmware Interface
 * @Description    Communication interface between VXE firmware and the Host.
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

#ifndef _TOPAZSCFWIF_H_
#define _TOPAZSCFWIF_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "coreflags.h"
#include "img_types.h"

typedef IMG_UINT16 IMG_BOOL16;

#define MAX_QP_H264			(51)

#if defined(HW_4_0)	
#define QP_OFFSET_10BITS	(12)
#define BITDEPTH_10BITS		(10)
//#define DISABLE_BUFFER_UPDATE_ON_SLICE 1
#endif

/*!
 *****************************************************************************
 *
 * @details    Minimum and maximum core revision numbers for each core minor revision
 *
 * @brief      Min/max core revisions
 *
 ****************************************************************************/
#define MIN_30_REV 0x00030000
#define MAX_30_REV 0x00030099
#define MIN_32_REV 0x00030200
#define MAX_32_REV 0x00030299
#define MIN_34_REV 0x00030400
#define MAX_34_REV 0x00030499
#define MIN_36_REV 0x00030600
#define MAX_36_REV 0x00030699
#define MIN_39_REV 0x00030900
#define MAX_39_REV 0x00030999
#define MIN_40_REV 0x00040000
#define MAX_40_REV 0x00040499

/*!
 *****************************************************************************
 *
 * @details    The number of bytes used by each MVEA MV param & above param region
 *
 * @brief      MVEA data sizes
 *
 ****************************************************************************/
#define MVEA_MV_PARAM_REGION_SIZE 16

#if defined(HW_3_X)
#define MVEA_ABOVE_PARAM_REGION_SIZE 96
#endif

#if defined(HW_4_0)
// Now we have 444 encode, this becomes potentially larger (see TRM 3.3 'Above params')
//#define MVEA_ABOVE_PARAM_REGION_SIZE 96
#define MVEA_ABOVE_A_PARAMS_REGION_SIZE 64
#define MVEA_ABOVE_B_PARAMS_REGION_SIZE 32
#define MVEA_ABOVE_A_EXT_PARAMS_REGION_SIZE 32
#endif


/*!
 *****************************************************************************
 *
 * @details    Macros to align to the correct number of bytes
 *
 * @brief      Data alignment
 *
 ****************************************************************************/
#define ALIGN_4(X)  (((X)+3) &~3)
#define ALIGN_8(X)  (((X)+7) &~7)
#define ALIGN_16(X)  (((X)+15) &~15)
#define ALIGN_32(X)  (((X)+31) &~31)
#define ALIGN_64(X)  (((X)+63) &~63)
#define ALIGN_128(X)  (((X)+127) &~127)
#define ALIGN_256(X)  (((X)+255) &~255)
#define ALIGN_1024(X)	(((X)+1023) &~1023)


/*!
 *****************************************************************************
 *
 * @details    Minimum number of bytes required in a buffer
 *
 * @brief      Coded buffer margins
 *
 ****************************************************************************/
#define CODED_BUFFER_MARGIN_H264 10000 
#define CODED_BUFFER_MARGIN_H263 768000 


/*!
 *****************************************************************************
 *
 * @details    Context size allocated from host application
 *
 * @brief      Context size
 *
 ****************************************************************************/
#define MTX_CONTEXT_SIZE (13 * 1024)

/*!
 *****************************************************************************
 *
 * @details    SEI (Buffering Period and Picture Timing) Constants shared between host and firmware
 *
 * @brief      SEI Constants
 *
 ****************************************************************************/
#define BPH_SEI_NAL_INITIAL_CPB_REMOVAL_DELAY_SIZE 23
#define BPH_SEI_NAL_INITIAL_CPB_REMOVAL_DELAY_OFFSET_SIZE BPH_SEI_NAL_INITIAL_CPB_REMOVAL_DELAY_SIZE
#define	PTH_SEI_NAL_CPB_REMOVAL_DELAY_SIZE 23
#define PTH_SEI_NAL_DPB_OUTPUT_DELAY_SIZE 7

#if defined(VP8_DRIVER) 
/*!
 *****************************************************************************
 *
 * @details    VP8 number of probability buffers
 *
 * @brief      VP8 number of probability buffers
 *
 ****************************************************************************/
#define VP8_NUM_PROB_BUFFERS			(4)
/*!
 *****************************************************************************
 *
 * @details    VP8 IVF Header Size
 *
 * @brief      VP8 IVF Header Size 
 *
 ****************************************************************************/
#define VP8_IVF_CONTAINER_HEADER_SIZE			(12) 
#endif

/*!
 *****************************************************************************
 *
 * @details    Size of Inter/Intra & Coded/Skipped tables
 *
 * @brief      Size of Inter/Intra & Coded/Skipped tables
 *
 ****************************************************************************/
#define SCALE_TBL_SZ                    (8)


/*!
 *****************************************************************************
 *
 * @details    Size of the header in output coded buffer. This varies based on 
 *              whether data logging is enabled/disabled
 *
 * @brief      Size of the header in output coded buffer
 *
 ****************************************************************************/

//#define INCLUDE_CRC_REGISTER_CHECKS // This is a debug mode that increases firmware size, so by default we leave it off.

#if defined (INCLUDE_CRC_REGISTER_CHECKS)
#define CRC_REGISTER_FEEDBACK_SIZE	(80*4)
#else
#define CRC_REGISTER_FEEDBACK_SIZE	0
#endif

#if defined(HW_4_0)	
// Note: this is the actual DMA memory to set aside for BUOS information (info is DMAC'd into the area in 128 bit chunks)
#define LL_BUFFER_FULLNESS_DATA_SIZE 64
#endif

#define CODED_BUFFER_HEADER_SIZE    64 // MUST be aligned to the DMA 64 byte boundary condition (CRC data is DMA'd after the coded buffer header)

#define CODED_BUFFER_INFO_SECTION_SIZE (CODED_BUFFER_HEADER_SIZE + CRC_REGISTER_FEEDBACK_SIZE)




/*!
 *****************************************************************************
 *
 * @details    Mask defines for the -ui8EnableSelStatsFlags variable
 *
 * @brief      Selectable first pass and multipass statistics flag values
 *
 ****************************************************************************/
#define ESF_FIRST_STAGE_STATS 1
#define ESF_MP_BEST_MB_DECISION_STATS 2
#define ESF_MP_BEST_MOTION_VECTOR_STATS 4


#if defined(HW_3_X)
	#define CUSTOM_QUANT_PARAMSIZE_8x8 2
#endif	
#if defined(HW_4_0)
	#define CUSTOM_QUANT_PARAMSIZE_8x8 6
#endif	
#define CUSTOM_QUANT_TABLESIZE_8x8 (6+CUSTOM_QUANT_PARAMSIZE_8x8)

/*!
 *****************************************************************************
 *
 * @details    Combined size of H.264 quantization lists (6 * 16 + {2 or 6} * 64)
 *
 * @brief          H.264 quantization lists size
 *
 ****************************************************************************/
#define QUANT_LISTS_SIZE		(6 * 16 + CUSTOM_QUANT_PARAMSIZE_8x8 * 64)


/*!
 *****************************************************************************
 *
 * @details    JPEG input quantization table size
 *
 * @brief          JPEG quant table size
 *
 ****************************************************************************/
#define QUANT_TABLE_SIZE_BYTES	(64)


/*!
 *****************************************************************************
 *
 * @details    JPEG input parameter sizes
 *
 * @brief          JPEG ...
 *
 ****************************************************************************/
#define MTX_MAX_COMPONENTS		(3)

	
/*!
 *****************************************************************************
 *
 * @Name           Output data header size
 *
 * @details    Size in bytes and words of memory to transfer partially coded header data
 *
 *****************************************************************************/
/* @{ */
#define MAX_HEADERSIZEBYTES		(128)
#define MAX_HEADERSIZEWORDS		(32)
/* @} */


/*!
 *****************************************************************************
 *
 * @details    Maximum number of slices per field
 *
 * @brief      Maximum number of slices per field
 *
 ****************************************************************************/
#define MAX_SLICESPERPIC		(128)


/*!
 *****************************************************************************
 *
 * @Name           Picture Parameter Flags
 *
 * @details    Picture parameter flags used in the PIC_PARAM structure
 *
 ****************************************************************************/
/* @{ */
#define ISINTERP_FLAGS					(0x00000001)
#define ISRC_FLAGS						(0x00000010)
#define ISRC_I16BIAS					(0x00000020)
#define ISINTERB_FLAGS					(0x00000080)
#define ISSCENE_DISABLED				(0x00000100)
#define ISMULTIREF_FLAGS				(0x00000200)
#define SPATIALDIRECT_FLAGS				(0x00000400)

/* @} */

 
/*!
 *****************************************************************************
 *
 * @details    Enum describing contents of scratch registers
 *
 * @brief          Scratch registers
 * 
 ****************************************************************************/
typedef enum
{
	MTX_SCRATCHREG_BOOTSTATUS = 0,
	MTX_SCRATCHREG_UNUSED = 0,
	MTX_SCRATCHREG_TOHOST,			//!< Reg for MTX->Host data
	MTX_SCRATCHREG_TOMTX,			//!< Reg for Host->MTX data

	MTX_SCRATCHREG_SIZE				//!< End marker for enum

} MTX_eScratchRegData;

/*
	`MTX_SCRATCHREG_IDLE` register that is used for synchronous communication and debug.

	Current register usage:
	<bits, inclusive boundaries> : <usage>
	2-10 : Number of executed commands (mod 255)
	0-1 : FW idle status
*/
#define MTX_SCRATCHREG_IDLE			TOPAZHP_TOP_CR_FIRMWARE_REG_4 //!< Reg for firmware IDLE status

#if defined(HW_3_X)
/*
	`FW_LINE_COUNTER` register that is used for low-latency encoding

	Current register usage:
	<bits, inclusive boundaries> : <usage>
	31-16	: Frame counter
	11-0	: Line counter
*/
#define FW_LINE_COUNTER				TOPAZHP_TOP_CR_FIRMWARE_REG_5 //!< Reg for firmware line counter
#endif

/* Flags relating to MTX_SCRATCHREG_IDLE */
#define SHIFT_FW_IDLE_REG_LINE_REQUESTED	(10)										/* Bits [10-22] are used for the line information */
#define MASK_FW_IDLE_REG_LINE_REQUESTED		(0xFFF << SHIFT_FW_IDLE_REG_LINE_REQUESTED)	/* TOPAZHP_LINE_COUNTER (see TRM 8.1.1) uses 12 bits for the line count */
#define SHIFT_FW_IDLE_REG_RECEIVED_COMMANDS	(2)
#define MASK_FW_IDLE_REG_RECEIVED_COMMANDS	(0x3FC)
#define SHIFT_FW_IDLE_REG_STATUS			(0)
#define MASK_FW_IDLE_REG_STATUS				(3)

#define FW_IDLE_STATUS_LINE_COUNTER		(0)				/* New line counter information */
#define FW_IDLE_STATUS_IDLE				(1)
#define FW_IDLE_STATUS_HW_ACTIVE		(2)
#define FW_IDLE_STATUS_BUSY				(3)


#define FW_DEBUG_TRACKING		TOPAZHP_TOP_CR_FIRMWARE_REG_6  //!< Reg for fw debug 

/* Flags relating to MTX_SCRATCHREG_FWTRACE */
#define SHIFT_FW_DEBUG_TRACKING_PIPE(x)		((x)*4)
#define MASK_FW_DEBUG_TRACKING_PIPE(x)		(0xf << SHIFT_FW_DEBUG_TRACKING_PIPE(x))	
#define SHIFT_FW_DEBUG_TRACKING_PIPE0		(0)										
#define MASK_FW_DEBUG_TRACKING_PIPE0		(0xf << MASK_FW_DEBUG_TRACKING_PIPE0)	
#define SHIFT_FW_DEBUG_TRACKING_PIPE1		(4)										
#define MASK_FW_DEBUG_TRACKING_PIPE1		(0xf << MASK_FW_DEBUG_TRACKING_PIPE1)	
#define SHIFT_FW_DEBUG_TRACKING_CMD_CTXT	(16)
#define MASK_FW_DEBUG_TRACKING_CMD_CTXT		(0xf << SHIFT_FW_DEBUG_TRACKING_CMD_CTXT)
#define SHIFT_FW_DEBUG_TRACKING_CMD_ID		(24)
#define MASK_FW_DEBUG_TRACKING_CMD_ID		(0xff << SHIFT_FW_DEBUG_TRACKING_CMD_ID)


#define MTX_SCRATCHREG_FWTRACE		TOPAZHP_TOP_CR_FIRMWARE_REG_7  //!< Reg for fw debug trace 

/* 
 * In secure FW mode the first value written to the command FIFO is copied to MMU_CONTROL_0 by the firmware.
 * When we don't want that to happen we can write this value instead.  The firmware will know to ignore it as 
 * long as it is written BEFORE the firmware starts up
 */
 #define TOPAZHP_NON_SECURE_FW_MARKER	(0xffffffff)

/*
 * This value is an arbitrary value that the firmware will write to TOPAZHP_TOP_CR_FIRMWARE_REG_1 (MTX_SCRATCHREG_BOOTSTATUS)
 * when it has completed the boot process to indicate that it is ready
 */
 #define TOPAZHP_FW_BOOT_SIGNAL		(0x12345678)

/*!
 *****************************************************************************
 *
 * @details    Sizes for arrays that depend on reference usage pattern
 *
 * @brief      Reference usage
 *
 ****************************************************************************/
#define MAX_REF_B_LEVELS		3
#define MAX_REF_SPACING			1
#define MAX_REF_I_OR_P_LEVELS	(MAX_REF_SPACING + 2)
#define MAX_REF_LEVELS			(MAX_REF_B_LEVELS + MAX_REF_I_OR_P_LEVELS)
#define MAX_PIC_NODES			(MAX_REF_LEVELS + 2)
#define MAX_MV					(MAX_PIC_NODES * 2)

#define MAX_BFRAMES				7                    //B-frame count limit for Hierarchical mode
#define MAX_BFRAMES_FLAT_MODE   3                    //B-frame count limit for Flat mode
#define MAX_GOP_SIZE			(MAX_BFRAMES + 1)
#define MAX_SOURCE_SLOTS_SL		(MAX_GOP_SIZE + 1)


/*!
 *****************************************************************************
 *
 * @details    
 *
 * @brief      
 *
 ****************************************************************************/
#define MV_ROW_STRIDE (ALIGN_64(sizeof(IMG_MV_SETTINGS) * MAX_BFRAMES))


/*!
 *****************************************************************************
 *
 * @details    Enable the firmware to patch reference and reconstructed buffers
 *
 * @brief      
 *
 ****************************************************************************/
#define FORCED_REFERENCE 1
#define LTREFHEADER 1


/*!
 *****************************************************************************
 *
 * @details    MTX -> host message FIFO
 *
 * @brief      WB FIFO
 *
 ****************************************************************************/
#define LOG2_WB_FIFO_SIZE	( 5 )

#define WB_FIFO_SIZE		( 1 << (LOG2_WB_FIFO_SIZE) )

#define SHIFT_WB_PRODUCER	( 0 )
#define MASK_WB_PRODUCER	( ((1 << LOG2_WB_FIFO_SIZE) - 1) << SHIFT_WB_PRODUCER )


#define SHIFT_WB_CONSUMER	( 0 )
#define MASK_WB_CONSUMER	( ((1 << LOG2_WB_FIFO_SIZE) - 1) << SHIFT_WB_CONSUMER )

/*!
 *****************************************************************************
 *
 * @details    Number of buffers per encode task (default: 2 - double bufferring)
 *
 * @brief      Number of buffers per encode task (default: 2 - double bufferring)
 *
 ****************************************************************************/
#define CODED_BUFFERING_CNT 2 //default to double-buffering

/*!
 *****************************************************************************
 *
 * @details    Calculates the ideal minimun coded buffers for a frame level encode
 *
 * @brief      Coded buffer count
 *
 ****************************************************************************/

#define CALC_OPTIMAL_CODED_PACKAGES_FRAME_ENCODE(numcores, isinterlaced) ((((isinterlaced) ? 2 : 1) * (numcores)) * CODED_BUFFERING_CNT)

/*!
 *****************************************************************************
 *
 * @details    Calculates the ideal minimum coded buffers for a slice level encode
 *
 * @brief      Coded buffer count
 *
 ****************************************************************************/
#define CALC_OPTIMAL_CODED_PACKAGES_SLICE_ENCODE(slicesperpic) (slicesperpic * CODED_BUFFERING_CNT)

/*!
 *****************************************************************************
 *
 * @details    Calculates the ideal minimum coded buffers for an encode
 *
 * @brief      Coded buffer count
 *
 ****************************************************************************/
#define CALC_OPTIMAL_CODED_PACKAGES_ENCODE(bisSliceLevel, slicesperpic, numcores, isinterlaced) \
	(bisSliceLevel ? CALC_OPTIMAL_CODED_PACKAGES_SLICE_ENCODE(slicesperpic) : CALC_OPTIMAL_CODED_PACKAGES_FRAME_ENCODE(numcores, isinterlaced))

/*!
 *****************************************************************************
 *
 * @details    Calculates the actual number of coded buffers that can be used for an encode
 *
 * @brief      Coded buffer count
 *
 ****************************************************************************/
#if defined(HW_3_X)
#define CALC_NUM_CODED_PACKAGES_ENCODE(bisSliceLevel, slicesperpic, numcores, isinterlaced) \
	(CALC_OPTIMAL_CODED_PACKAGES_ENCODE(bisSliceLevel, slicesperpic, numcores, isinterlaced))
#endif
#if defined(HW_4_0)
#define CALC_NUM_CODED_PACKAGES_ENCODE(bisSliceLevel, slicesperpic, numcores, isinterlaced, islinkedlist) \
	(islinkedlist ? CALC_OPTIMAL_CODED_PACKAGES_ENCODE(bisSliceLevel, slicesperpic, numcores, isinterlaced) : CALC_OPTIMAL_CODED_PACKAGES_ENCODE(bisSliceLevel, slicesperpic, numcores, isinterlaced))
//	(islinkedlist ? CODED_BUFFERING_CNT : CALC_OPTIMAL_CODED_PACKAGES_ENCODE(bisSliceLevel, slicesperpic, numcores, isinterlaced))
#endif


/*!
 *****************************************************************************
 *
 * @details    Maximum number of coded packages
 *
 * @brief      Maximum number of coded packages
 *
 ****************************************************************************/

//#define MAX_CODED_PACKAGES	(CODED_BUFFERING_CNT * TOPAZHP_MAX_NUM_PIPES * 2)
// Use the same Macros used in API so we don't accidentally under-allocate (worst case values)
#if defined(HW_3_X)
#define MAX_CODED_PACKAGES	CALC_NUM_CODED_PACKAGES_ENCODE(0,0, TOPAZHP_MAX_NUM_PIPES, 1)
#endif
#if defined(HW_4_0)
#define MAX_CODED_PACKAGES	CALC_NUM_CODED_PACKAGES_ENCODE(0,0, TOPAZHP_MAX_NUM_PIPES, 1, 0)
#endif




/*!
 ***********************************************************************************
 *
 * DMA configuration parameters
 *
 ************************************************************************************/
#define MTX_DMA_BURSTSIZE_BYTES 32
#define MTX_DMA_ALIGNMENT_BYTES 64


/*!
 ***********************************************************************************
 *
 * Description        : types that should be in DMAC header file
 *
 ************************************************************************************/
typedef enum
{
	DMAC_ACC_DEL_0 = 0x0,			//!< Access delay zero clock cycles
	DMAC_ACC_DEL_256 = 0x1,			//!< Access delay 256 clock cycles
	DMAC_ACC_DEL_512 = 0x2,			//!< Access delay 512 clock cycles
	DMAC_ACC_DEL_768 = 0x3,			//!< Access delay 768 clock cycles
	DMAC_ACC_DEL_1024 = 0x4,		//!< Access delay 1024 clock cycles
	DMAC_ACC_DEL_1280 = 0x5,		//!< Access delay 1280 clock cycles
	DMAC_ACC_DEL_1536 = 0x6,		//!< Access delay 1536 clock cycles
	DMAC_ACC_DEL_1792 = 0x7,		//!< Access delay 1792 clock cycles
} DMAC_eAccDel;

typedef enum
{
	DMAC_BSWAP_NO_SWAP = 0x0,		//!< No byte swapping will be performed.
	DMAC_BSWAP_REVERSE = 0x1,		//!< Byte order will be reversed.
} DMAC_eBSwap;

typedef enum
{
	DMAC_BURST_0 = 0x0,				//!< burst size of 0
	DMAC_BURST_1 = 0x1,				//!< burst size of 1
	DMAC_BURST_2 = 0x2,				//!< burst size of 2
	DMAC_BURST_3 = 0x3,				//!< burst size of 3
	DMAC_BURST_4 = 0x4,				//!< burst size of 4
	DMAC_BURST_5 = 0x5,				//!< burst size of 5
	DMAC_BURST_6 = 0x6,				//!< burst size of 6
	DMAC_BURST_7 = 0x7,				//!< burst size of 7
} DMAC_eBurst;

typedef enum
{
	DMAC_DIR_MEM_TO_PERIPH = 0x0,	//!< Data from memory to peripheral.
	DMAC_DIR_PERIPH_TO_MEM = 0x1,	//!< Data from peripheral to memory.
} DMAC_eDir;

#define DMAC_VALUE_COUNT(BSWAP,PW,DIR,PERIPH_INCR,COUNT)			 \
    (((BSWAP)		<< SHIFT_IMG_SOC_BSWAP)	& MASK_IMG_SOC_BSWAP)	|\
	(((PW)			<< SHIFT_IMG_SOC_PW)	& MASK_IMG_SOC_PW)		|\
	(((DIR)			<< SHIFT_IMG_SOC_DIR)	& MASK_IMG_SOC_DIR)		|\
	(((PERIPH_INCR)	<< SHIFT_IMG_SOC_PI)	& MASK_IMG_SOC_PI)		|\
	(((COUNT)		<< SHIFT_IMG_SOC_CNT)	& MASK_IMG_SOC_CNT)
#define DMAC_VALUE_PERIPH_PARAM(ACC_DEL,INCR,BURST)					 \
	(((ACC_DEL)	<< SHIFT_IMG_SOC_ACC_DEL)	& MASK_IMG_SOC_ACC_DEL)	|\
	(((INCR)	<< SHIFT_IMG_SOC_INCR)		& MASK_IMG_SOC_INCR)	|\
	(((BURST)	<< SHIFT_IMG_SOC_BURST)		& MASK_IMG_SOC_BURST)

typedef enum
{
	DMAC_PWIDTH_32_BIT = 0x0,		//!< Peripheral width 32-bit.
	DMAC_PWIDTH_16_BIT = 0x1,		//!< Peripheral width 16-bit.
	DMAC_PWIDTH_8_BIT = 0x2,		//!< Peripheral width 8-bit.
} DMAC_ePW;


/*!
 *****************************************************************************
 *
 * @details   
 *
 * Enum describing Command IDs.  Some commands require data to be DMA'd in
 * from the Host, with the base address of the data specified in the Command  
 * Data Address word of the command.  The data required is specific to each
 * command type.
 * 
 * @brief          Command IDs
 *
 ****************************************************************************/
typedef enum
{
	// Common Commands
	MTX_CMDID_NULL,						//!< (no data)\n Null command does nothing\n
	MTX_CMDID_SHUTDOWN,					//!< (no data)\n shutdown the MTX\n

	// Video Commands
	MTX_CMDID_DO_HEADER,				//!< (extra data: #MTX_HEADER_PARAMS)\n Command for Sequence, Picture and Slice headers\n
	MTX_CMDID_ENCODE_FRAME,				//!< (data: low latency encode activation, HBI usage)\n Encode frame data\n
	MTX_CMDID_START_FRAME,				//!< (no data)\n Prepare to encode frame\n
	MTX_CMDID_ENCODE_SLICE,				//!< (no data)\n Encode slice data\n
	MTX_CMDID_END_FRAME,				//!< (no data)\n Complete frame encoding\n
	MTX_CMDID_SETVIDEO,					//!< (data: pipe number, extra data: #IMG_MTX_VIDEO_CONTEXT)\n Set MTX Video Context\n
	MTX_CMDID_GETVIDEO,					//!< (data: pipe number, extra data: #IMG_MTX_VIDEO_CONTEXT)\n Get MTX Video Context\n
	MTX_CMDID_DO_CHANGE_PIPEWORK,		//!< (data: new pipe allocations for the context)\n Change pipe allocation for a Video Context\n
#if SECURE_IO_PORTS
	MTX_CMDID_SECUREIO,					//!< (data: )\n Change IO security\n
#endif 
	MTX_CMDID_PICMGMT,					//!< (data: subtype and parameters, extra data: #IMG_PICMGMT_CUSTOM_QUANT_DATA (optional))\n Change encoding parameters\n
	MTX_CMDID_RC_UPDATE,				//!< (data: QP and bitrate)\n Change encoding parameters\n
	MTX_CMDID_PROVIDE_SOURCE_BUFFER,	//!< (extra data: #IMG_SOURCE_BUFFER_PARAMS)\n Transfer source buffer from host\n
	MTX_CMDID_PROVIDE_REF_BUFFER,		//!< (data: buffer parameters, extra data: reference buffer)\n Transfer reference buffer from host\n
	MTX_CMDID_PROVIDE_CODEDPACKAGE_BUFFER,	//!< (data: slot and size, extra data: coded package)\n Transfer coded package from host (coded package contains addresses of header and coded output buffers/1st linked list node)\n
	MTX_CMDID_ABORT,					//!< (no data)\n Stop encoding and release all buffers\n

	// JPEG commands
	MTX_CMDID_SETQUANT,					//!< (extra data: #JPEG_MTX_QUANT_TABLE)\n
	MTX_CMDID_SETUP_INTERFACE,			//!< (extra data: #JPEG WRITEBACK POINTERS)\n
	MTX_CMDID_ISSUEBUFF,				//!< (extra data: #MTX_ISSUE_BUFFERS)\n
	MTX_CMDID_SETUP,					//!< (extra data: #JPEG_MTX_DMA_SETUP)\n\n

	MTX_CMDID_UPDATE_SOURCE_FORMAT,		//!< (extra data: #IMG_VXE_SCALER_SETUP)\nChange source pixel format after context creation\n
 	MTX_CMDID_UPDATE_CSC,				//!< (extra data: #IMG_VXE_CSC_SETUP)\nChange Colour Space Conversion setup dynamically\n

	MTX_CMDID_ENDMARKER					//!< end marker for enum
} MTX_CMD_ID;


/*!
 *****************************************************************************
 *
 * @details
 *
 * Priority for the command.
 * Each Command ID will only work with the correct priority.
 *
 * @brief      Command priority
 *
 ****************************************************************************/
#define MTX_CMDID_PRIORITY 0x80


/*!
 *****************************************************************************
 *
 * @details
 *
 * Indicates whether or not to issue an interrupt when the firmware sends the
 * command's writeback message.
 *
 * @brief      Interrupt on writeback
 *
 ****************************************************************************/
#define MTX_CMDID_WB_INTERRUPT 0x8000


/*!
 *****************************************************************************
 *
 * @details    Enum describing response IDs
 *
 * @brief      Response IDs
 *
 ****************************************************************************/
typedef enum
{
	MTX_MESSAGE_ACK,
	MTX_MESSAGE_CODED,
} MTX_MESSAGE_ID;


/*!
 *****************************************************************************
 *
 * @Name           Command word format
 *
 * @details    Mask and shift values for command word
 *
 ****************************************************************************/
/* @{ */
#define SHIFT_MTX_MSG_CMD_ID		(0)
#define MASK_MTX_MSG_CMD_ID			(0x7f << SHIFT_MTX_MSG_CMD_ID)
#define SHIFT_MTX_MSG_PRIORITY		(7)
#define MASK_MTX_MSG_PRIORITY		(0x1 << SHIFT_MTX_MSG_PRIORITY)
#define SHIFT_MTX_MSG_CORE			(8)
#define MASK_MTX_MSG_CORE			(0x7f << SHIFT_MTX_MSG_CORE)
#define SHIFT_MTX_MSG_WB_INTERRUPT	(15)
#define MASK_MTX_MSG_WB_INTERRUPT	(0x1 << SHIFT_MTX_MSG_WB_INTERRUPT)
#define SHIFT_MTX_MSG_COUNT			(16)
#define MASK_MTX_MSG_COUNT			(0xffff << SHIFT_MTX_MSG_COUNT)
#define SHIFT_MTX_MSG_MESSAGE_ID	(16)
#define MASK_MTX_MSG_MESSAGE_ID		(0xff << SHIFT_MTX_MSG_MESSAGE_ID)
/* @} */


/*!
 *****************************************************************************
 *
 * @Name           Data word formats
 *
 * @details    Mask and shift values for data word
 *
 ****************************************************************************/
/* @{ */
#define SHIFT_MTX_MSG_ENCODE_CODED_INTERRUPT		(0)
#define MASK_MTX_MSG_ENCODE_CODED_INTERRUPT			(0xff << SHIFT_MTX_MSG_ENCODE_CODED_INTERRUPT)
#define SHIFT_MTX_MSG_ENCODE_USE_LINE_COUNTER		(20)
#define MASK_MTX_MSG_ENCODE_USE_LINE_COUNTER		(0x1 << SHIFT_MTX_MSG_ENCODE_USE_LINE_COUNTER)

#if defined (HW_4_0)
/* Use the new optional Hardware Block Interface (Onyx) to upload source frame planes MB-by-MB */
#define SHIFT_MTX_MSG_ENCODE_USE_HBI				(21)
#define MASK_MTX_MSG_ENCODE_USE_HBI					(0x1 << SHIFT_MTX_MSG_ENCODE_USE_HBI)
#endif

#if defined(VP8_DRIVER)
#define SHIFT_MTX_MSG_VP8_REF_USE					(8)
#define MASK_MTX_MSG_VP8_REF_USE					(0x0f << SHIFT_MTX_MSG_VP8_REF_USE)
#define SHIFT_MTX_MSG_VP8_REF_UPDATE				(12)
#define MASK_MTX_MSG_VP8_REF_UPDATE					(0x07 << SHIFT_MTX_MSG_VP8_REF_UPDATE)
#define SHIFT_MTX_MSG_VP8_TEMPORAL_LAYER_ID			(15)
#define MASK_MTX_MSG_VP8_TEMPORAL_LAYER_ID			(0x03 << SHIFT_MTX_MSG_VP8_TEMPORAL_LAYER_ID)
#define SHIFT_MTX_MSG_VP8_REFRESH_PROBS				(17)
#define MASK_MTX_MSG_VP8_REFRESH_PROBS				(0x03 << SHIFT_MTX_MSG_VP8_REFRESH_PROBS)
#endif

#define SHIFT_MTX_MSG_PICMGMT_SUBTYPE				(0)
#define MASK_MTX_MSG_PICMGMT_SUBTYPE				(0xff << SHIFT_MTX_MSG_PICMGMT_SUBTYPE)
#define SHIFT_MTX_MSG_PICMGMT_DATA					(8)
#define MASK_MTX_MSG_PICMGMT_DATA					(0xffffff << SHIFT_MTX_MSG_PICMGMT_DATA)
#define SHIFT_MTX_MSG_PICMGMT_STRIDE_Y				(0)
#define MASK_MTX_MSG_PICMGMT_STRIDE_Y				(0x3ff << SHIFT_MTX_MSG_PICMGMT_STRIDE_Y)
#define SHIFT_MTX_MSG_PICMGMT_STRIDE_UV				(10)
#define MASK_MTX_MSG_PICMGMT_STRIDE_UV				(0x3ff << SHIFT_MTX_MSG_PICMGMT_STRIDE_UV)

/*Values for updating bitrate when Rate Control is enabled*/
#define SHIFT_MTX_MSG_RC_UPDATE_QP					(0)
#define MASK_MTX_MSG_RC_UPDATE_QP					(0xff << SHIFT_MTX_MSG_RC_UPDATE_QP)
#define SHIFT_MTX_MSG_RC_UPDATE_BITRATE				(8)
#define MASK_MTX_MSG_RC_UPDATE_BITRATE				(0x00ffffff << SHIFT_MTX_MSG_RC_UPDATE_BITRATE)
#define UPDATE_BITRATE_MULTIPLIER					(3)

/*Values for updating static Qp values when Rate Control is disabled*/
#define SHIFT_MTX_MSG_STATIC_UPDATE_QPI				(0)
#define MASK_MTX_MSG_STATIC_UPDATE_QPI				(0xff << SHIFT_MTX_MSG_STATIC_UPDATE_QPI)
#define SHIFT_MTX_MSG_STATIC_UPDATE_QPP				(8)
#define MASK_MTX_MSG_STATIC_UPDATE_QPP				(0xff << SHIFT_MTX_MSG_STATIC_UPDATE_QPP)
#define SHIFT_MTX_MSG_STATIC_UPDATE_QPB				(16)
#define MASK_MTX_MSG_STATIC_UPDATE_QPB				(0xff << SHIFT_MTX_MSG_STATIC_UPDATE_QPB)

#define SHIFT_MTX_MSG_PROVIDE_REF_BUFFER_USE		(0)
#define MASK_MTX_MSG_PROVIDE_REF_BUFFER_USE			(0xff << SHIFT_MTX_MSG_PROVIDE_REF_BUFFER_USE)
#define SHIFT_MTX_MSG_PROVIDE_REF_BUFFER_SLOT		(8)
#define MASK_MTX_MSG_PROVIDE_REF_BUFFER_SLOT		(0xff << SHIFT_MTX_MSG_PROVIDE_REF_BUFFER_SLOT)
#define SHIFT_MTX_MSG_PROVIDE_REF_BUFFER_LT			(16)
#define MASK_MTX_MSG_PROVIDE_REF_BUFFER_LT			(0xff << SHIFT_MTX_MSG_PROVIDE_REF_BUFFER_LT)

#if defined(HW_4_0)
#define SHIFT_MTX_MSG_PROVIDED_CODED_BUFFER_ISLINKEDLIST		(0)
#define MASK_MTX_MSG_PROVIDED_CODED_BUFFER_ISLINKEDLIST		(0x01 << SHIFT_MTX_MSG_PROVIDED_CODED_BUFFER_ISLINKEDLIST)
#define SHIFT_MTX_MSG_NUM_LIST_SEGMENTS_PER_CODED_BUFFER	(1)
#define MASK_MTX_MSG_NUM_LIST_SEGMENTS_PER_CODED_BUFFER		(0xf << SHIFT_MTX_MSG_NUM_LIST_SEGMENTS_PER_CODED_BUFFER)
#endif

#define SHIFT_MTX_MSG_NUM_CODED_BUFFERS_PER_HEADER			(5)
#define MASK_MTX_MSG_NUM_CODED_BUFFERS_PER_HEADER			(0xf << SHIFT_MTX_MSG_NUM_CODED_BUFFERS_PER_HEADER)
#define SHIFT_MTX_MSG_PROVIDE_LIST_SEGMENT_SIZE				(10)
#define MASK_MTX_MSG_PROVIDE_LIST_SEGMENT_SIZE				(0x3fffff << SHIFT_MTX_MSG_PROVIDE_LIST_SEGMENT_SIZE)


#define SHIFT_MTX_MSG_PROVIDE_CODEDPACKAGE_BUFFER_SLOT	(0)
#define MASK_MTX_MSG_PROVIDE_CODEDPACKAGE_BUFFER_SLOT		(0x0f << SHIFT_MTX_MSG_PROVIDE_CODEDPACKAGE_BUFFER_SLOT)
#define SHIFT_MTX_MSG_PROVIDE_CODED_BUFFER_SIZE		(4)
#define MASK_MTX_MSG_PROVIDE_CODED_BUFFER_SIZE		(0x3fffff << SHIFT_MTX_MSG_PROVIDE_CODED_BUFFER_SIZE)

#if SECURE_IO_PORTS
#define SHIFT_MTX_MSG_SECUREIO_OUTPUT				(0)
#define MASK_MTX_MSG_SECUREIO_OUTPUT				(0x1 << SHIFT_MTX_MSG_SECUREIO_OUTPUT)
#define SHIFT_MTX_MSG_SECUREIO_INPUT				(8)
#define MASK_MTX_MSG_SECUREIO_INPUT					(0x1 << SHIFT_MTX_MSG_SECUREIO_INPUT)
#endif 
/* @} */

/*!
 *****************************************************************************
 *
 * @Name           Source Format data defines
 *
 * @details    Mask and shift values for Source format data word
 *
 ****************************************************************************/
/* @{ */
#define SHIFT_MTX_UPDATE_SOURCE_FORMAT_SC_ENABLE (0)
#define MASK_MTX_UPDATE_SOURCE_FORMAT_SC_ENABLE	(0x1 << SHIFT_MTX_UPDATE_SOURCE_FORMAT_SC_ENABLE)
/* @} */

/*!
 *****************************************************************************
 *
 * @details    Enum describing partially coded header element types
 *
 * @brief          Header element type
 *
 ****************************************************************************/
typedef enum
{
	ELEMENT_STARTCODE_RAWDATA = 0,					//!< Raw data that includes a start code
	ELEMENT_STARTCODE_MIDHDR,						//!< Raw data that includes a start code in the middle of the header
	ELEMENT_RAWDATA,								//!< Raw data
	ELEMENT_QP,										//!< Insert the H264 Picture Header QP parameter
	ELEMENT_SQP,									//!< Insert the H264 Slice Header QP parameter
	ELEMENT_FRAMEQSCALE,							//!< Insert the H263/MPEG4 Frame Q_scale parameter (vob_quant field)
	ELEMENT_SLICEQSCALE,							//!< Insert the H263/MPEG4 Slice Q_scale parameter (quant_scale field)
	ELEMENT_INSERTBYTEALIGN_H264,					//!< Insert the byte alignment bits for H264
	ELEMENT_INSERTBYTEALIGN_MPG4,					//!< Insert the byte alignment bits for MPEG4
	ELEMENT_INSERTBYTEALIGN_MPG2,					//!< Insert the byte alignment bits for MPEG2
	ELEMENT_VBV_MPG2,
	ELEMENT_TEMPORAL_REF_MPG2,
	ELEMENT_CURRMBNR,								//!< Insert the current macrloblock number for a slice.

	ELEMENT_FRAME_NUM,								//!< Insert frame_num field (used as ID for ref. pictures in H264)
	ELEMENT_TEMPORAL_REFERENCE,						//!< Insert Temporal Reference field (used as ID for ref. pictures in H263)
	ELEMENT_EXTENDED_TR,							//!< Insert Extended Temporal Reference field
	ELEMENT_IDR_PIC_ID,								//!< Insert idr_pic_id field (used to distinguish consecutive IDR frames)
	ELEMENT_PIC_ORDER_CNT,							//!< Insert pic_order_cnt_lsb field (used for display ordering in H264)
	ELEMENT_GOB_FRAME_ID,							//!< Insert gob_frame_id field (used for display ordering in H263)
	ELEMENT_VOP_TIME_INCREMENT,						//!< Insert vop_time_increment field (used for display ordering in MPEG4)

#if defined(VP8_DRIVER)
	ELEMENT_VP8_BOOL_CODED_PART1,					//!< Insert VP8 bool coded values, part 1
	ELEMENT_VP8_BOOL_CODED_PART2,					//!< Insert VP8 bool coded values, part 2
#endif

	ELEMENT_MODULO_TIME_BASE,						//!< Insert modulo_time_base used in MPEG4 (depends on vop_time_increment_resolution)

	ELEMENT_BOTTOM_FIELD,							//!< Insert bottom_field flag
	ELEMENT_SLICE_NUM,								//!< Insert slice num (used for GOB headers in H263)
	ELEMENT_MPEG2_SLICE_VERTICAL_POS,				//!< Insert slice vertical pos (MPEG2 slice header)
	ELEMENT_MPEG2_IS_INTRA_SLICE,					//!< Insert 1 bit flag indicating if slice is Intra or not (MPEG2 slice header)
	ELEMENT_MPEG2_PICTURE_STRUCTURE,				//!< Insert 2 bit field indicating if the current header is for a frame picture (11), top field (01) or bottom field (10) - (MPEG2 picture header)
	ELEMENT_REFERENCE,								//!< Insert flag indicating whether or not this picture is a reference
	ELEMENT_ADAPTIVE,								//!< Insert reference picture marking
	ELEMENT_DIRECT_SPATIAL_MV_FLAG,					//!< Insert spatial direct mode flag
	ELEMENT_NUM_REF_IDX_ACTIVE,						//!< Insert number of active references
	ELEMENT_REORDER_L0,								//!< Insert reference list 0 reordering
	ELEMENT_REORDER_L1,								//!< Insert reference list 1 reordering
	ELEMENT_TEMPORAL_ID,							//!< Insert temporal ID of the picture, used for MVC header
	ELEMENT_ANCHOR_PIC_FLAG,						//!< Insert flag indicating whether or not this picture is an anchor picture

	BPH_SEI_NAL_INITIAL_CPB_REMOVAL_DELAY,			//!< Insert nal_initial_cpb_removal_delay
	BPH_SEI_NAL_INITIAL_CPB_REMOVAL_DELAY_OFFSET,	//!< Insert nal_initial_cpb_removal_delay_offset
	PTH_SEI_NAL_CPB_REMOVAL_DELAY,					//!< Insert cpb_removal_delay
	PTH_SEI_NAL_DPB_OUTPUT_DELAY,					//!< Insert dpb_output_delay

	ELEMENT_SLICEWEIGHTEDPREDICTIONSTRUCT,			//!< Insert weighted prediciton parameters
	ELEMENT_CUSTOM_QUANT							//!< Insert custom quantization values
} HEADER_ELEMENT_TYPE;


/*!
 *****************************************************************************
 *
 * @details    Struct describing a partially coded header element
 *
 * @brief          Header element
 *
 ****************************************************************************/
typedef struct
{
	HEADER_ELEMENT_TYPE	Element_Type;	//!< Element type
	IMG_UINT8			ui8Size;		//!< Number of bits of coded data to be inserted
	IMG_UINT8			aui8Bits;		//!< Raw data to be inserted.
} MTX_HEADER_ELEMENT;


/*!
 *****************************************************************************
 *
 * @details    Struct describing partially coded header parameters
 *
 * @brief          Header parameters
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32			ui32Elements;								//!< Number of header elements
	MTX_HEADER_ELEMENT	asElementStream[MAX_HEADERSIZEWORDS - 1];	//!< array of element data
} MTX_HEADER_PARAMS;


/*!
 *****************************************************************************
 *
 * @details    Enum describing threshold values for skipped MB biasing
 *
 * @brief          Skip thresholds
 *
 ****************************************************************************/
typedef enum
{
	TH_SKIP_0 = 0,		//!< Bias threshold for QP 0 to 12
	TH_SKIP_12 = 1,		//!< Bias threshold for QP 12 to 24
	TH_SKIP_24 = 2		//!< Bias threshold for QP 24 and above
} TH_SKIP_SCALE;


/*!
 *****************************************************************************
 *
 * @details    Struct describing rate control input parameters
 *
 * @brief          Rate control input parameters
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32MBPerFrm;		//!< Number of MBs Per Frame
	IMG_UINT32	ui32MBPerBU;		//!< Number of MBs Per BU
	IMG_UINT16	ui16BUPerFrm;		//!< Number of BUs Per Frame

	IMG_UINT16	ui16IntraPeriod;	//!< Intra frame frequency
	IMG_UINT16	ui16BFrames;		//!< B frame frequency   

	IMG_INT32	i32BitsPerFrm;		//!< Bits Per Frame
	IMG_INT32	i32BitsPerBU;		//!< Bits Per BU

	IMG_INT32	i32BitRate;			//!< Bit Rate (bps)
	IMG_INT32	i32BufferSize;		//!< Size of Buffer in bits
	IMG_INT32	i32BufferSizeFrames;//!< Size of Buffer in frames, to be used in VCM
	IMG_INT32	i32InitialLevel;	//!< Initial Level of Buffer
	IMG_INT32	i32InitialDelay;	//!< Initial Delay of Buffer

	IMG_BOOL16	bFrmSkipDisable;	//!< Disable Frame skipping	

	IMG_UINT8	ui8SeInitQPI;		//!< Initial QP for sequence (I frames)
	IMG_UINT8	ui8SeInitQPP;		//!< Initial QP for sequence (P frames)
	IMG_UINT8	ui8SeInitQPB;		//!< Initial QP for sequence (B frames)

	IMG_UINT8	ui8MinQPVal;		//!< Minimum QP value to use
	IMG_UINT8	ui8MaxQPVal;		//!< Maximum QP value to use

	IMG_UINT8	ui8ScaleFactor;		//!< Scale Factor used to limit the range of arithmetic with high resolutions and bitrates	
	IMG_UINT16	ui16MBPerRow;		//!< Number of MBs Per Row

	IMG_BOOL16	bDisableVcmHardware; //!< Disable using vcm hardware in RC modes.

	union
	{
		struct
		{
			IMG_INT32	i32TransferRate;	//!< Rate at which bits are sent from encoder to the output after each frame finished encoding
			IMG_BOOL16	bScDetectDisable;	//!< Disable Scene Change detection
			IMG_BOOL16	bHierarchicalMode;	//!< Flag indicating Hierarchical B Pic or Flat mode rate control
			IMG_UINT32	ui32RCScaleFactor;	//!< Constant used in rate control = (GopSize/(BufferSize-InitialLevel))*256
			IMG_BOOL16	bEnableSliceBob;	//!< Enable movement of slice boundary when Qp is high
			IMG_UINT8  ui8MaxSliceBob;     //!< Maximum number of rows the slice boundary can be moved
			IMG_UINT8  ui8SliceBobQp;		//!< Minimum Qp at which slice bobbing should take place
		} h264;
#if defined(VP8_RC)
		struct
		{
			IMG_BOOL16	bDisableVp8Segmentation;	//!< Disable using segmentation for VP8
			IMG_UINT8	ui8NumTemporalLayers;		//!< Number of temporal layers in VP8
			IMG_UINT32	aui32LayerBitrate[3];		//!< Array of bitrates for each layer for temporal thinning for VP8
			IMG_UINT32	aui32CumLayerBitrate[3];	//!< Array of cumulative bitrates for each layer for temporal thinning for VP8
			IMG_INT32	ai32CumLayerBitsPerFrm[3];	//!< Array of cumulative bits per frame values for each layer for temporal thinning for VP8
			IMG_UINT32	aui32LayerBitsPerFrm[3];		//!< Array of bits per frame values for each layer for temporal thinning for VP8
			IMG_INT32	i32LayerBufferSize[3];		//!< Array of buffer sizes for each layer for temporal thinning for VP8
			IMG_INT32	i32LayerBufferSizeFrames[3];//!< Array of buffer sizes in frames for each layer for temporal thinning for VP8
		} vp8;
#endif
		struct
		{
			IMG_UINT8	ui8HalfFrameRate;	//!< Half Frame Rate (MP4 only)
			IMG_UINT8	ui8FCode;			//!< F Code (MP4 only)
			IMG_INT32	i32BitsPerGOP;		//!< Bits Per GOP (MP4 only)
			IMG_BOOL16	bBUSkipDisable;		//!< Disable BU skipping
			IMG_INT32	i32BitsPerMB;		//!< Bits Per MB
			IMG_UINT16	ui16AvQPVal;		//!< Average QP in Current Picture
			IMG_UINT16	ui16MyInitQP;		//!< Initial Quantizer
		} other;
	} mode;
} IN_RC_PARAMS;


/*!
 *****************************************************************************
 *
 * @details    Enum describing MTX firmware version (codec and rate control)
 *
 * @brief          Firmware version
 *
 ****************************************************************************/
typedef enum
{
	IMG_CODEC_NONE = 0,			//!< There is no FW in MTX memory
	IMG_CODEC_JPEG,				//!< JPEG
	IMG_CODEC_H264_NO_RC,		//!< H264 with no rate control
	IMG_CODEC_H264_VBR,			//!< H264 variable bitrate
	IMG_CODEC_H264_CBR,			//!< H264 constant bitrate
	IMG_CODEC_H264_VCM,			//!< H264 video conferance mode
	IMG_CODEC_H263_NO_RC,		//!< H263 with no rate control
	IMG_CODEC_H263_VBR,			//!< H263 variable bitrate
	IMG_CODEC_H263_CBR,			//!< H263 constant bitrate
	IMG_CODEC_MPEG4_NO_RC,		//!< MPEG4 with no rate control
	IMG_CODEC_MPEG4_VBR,		//!< MPEG4 variable bitrate
	IMG_CODEC_MPEG4_CBR,		//!< MPEG4 constant bitrate
	IMG_CODEC_MPEG2_NO_RC,		//!< MPEG2 with no rate control
	IMG_CODEC_MPEG2_VBR,		//!< MPEG2 variable bitrate
	IMG_CODEC_MPEG2_CBR,		//!< MPEG2 constant bitrate
	IMG_CODEC_H264_ERC,			//!< H264 example rate control
	IMG_CODEC_H263_ERC,			//!< H263 example rate control
	IMG_CODEC_MPEG4_ERC,		//!< MPEG4 example rate control
	IMG_CODEC_MPEG2_ERC,		//!< MPEG2 example rate control
	IMG_CODEC_H264MVC_NO_RC,	//!< MVC H264 with no rate control
	IMG_CODEC_H264MVC_CBR,		//!< MVC H264 constant bitrate
	IMG_CODEC_H264MVC_VBR,		//!< MVC H264 variable bitrate
	IMG_CODEC_H264MVC_ERC,		//!< MVC H264 example rate control
	IMG_CODEC_H264_ALL_RC,		//!< H264 with multiple rate control modes
#if defined(VP8_RC) || defined(VP8_DRIVER)
	IMG_CODEC_VP8_NO_RC,		//!< VP8 with no rate control
	IMG_CODEC_VP8_VBR,			//!< VP8 variable bitrate
	IMG_CODEC_VP8_CBR,			//!< VP8 constant bitrate
	IMG_CODEC_VP8_VCM,			//!< VP8 video conferance mode
	IMG_CODEC_VP8_ERC,			//!< VP8 example rate control
#endif
} IMG_CODEC;


/*!
 *****************************************************************************
 *
 * @details    Enum describing encoding standard (codec)
 *
 * @brief          Encoding standard
 *
 ****************************************************************************/
typedef enum
{
	IMG_STANDARD_NONE = 0,	//!< There is no FW in MTX memory
	IMG_STANDARD_JPEG,		//!< JPEG
	IMG_STANDARD_H264,		//!< H264 with no rate control
	IMG_STANDARD_H263,		//!< H263 with no rate control
	IMG_STANDARD_MPEG4,		//!< MPEG4 with no rate control
	IMG_STANDARD_MPEG2,		//!< MPEG2 with no rate control
#if defined(VP8_RC) || defined(VP8_DRIVER)
	IMG_STANDARD_VP8,		//!< VP8 with no rate control
#endif
} IMG_STANDARD;


/*!
 *****************************************************************************
 *
 * @details    Enum describing image surface format types
 *
 * @brief          Image surface format
 *
 ****************************************************************************/
typedef enum
{
	IMG_CODEC_420_YUV=100,			//!< Planar Y U V
	IMG_CODEC_420_YV12=44,			//!< YV12 format Data
	IMG_CODEC_420_IMC2=36,			//!< IMC2 format Data
	IMG_CODEC_420_PL8=47,			//!< PL8 format YUV data
	IMG_CODEC_420_PL12=101,			//!< PL12 format YUV data
	IMG_CODEC_420_PL12_PACKED=25,   //|< PL12 format packed into a single plane (not currently supported by JPEG)
	IMG_CODEC_420_PL21_PACKED=26,   //!< PL21 format packed into a single plane (not currently supported by JPEG)
	IMG_CODEC_422_YUV=102,		//!< YUV format 4:2:2 data  // start the incrementing auto enumeration values after the last ones we have used.
	IMG_CODEC_422_YV12,			//!< YV12 format 4:2:2 data
	IMG_CODEC_422_PL8,			//!< PL8 format 4:2:2 data
	IMG_CODEC_422_IMC2,			//!< IMC2 format 4:2:2 data
	IMG_CODEC_422_PL12,			//!< PL12 format 4:2:2 data
	IMG_CODEC_Y0UY1V_8888,		//!< 4:2:2 YUYV data
	IMG_CODEC_Y0VY1U_8888,		//!< 4:2:2 YVYU data
	IMG_CODEC_UY0VY1_8888,		//!< 4:2:2 UYVY data
	IMG_CODEC_VY0UY1_8888,		//!< 4:2:2 VYUY data
	IMG_CODEC_444_YUV,		//!< YUV format 4:4:4 data (not currently supported by JPEG)
	IMG_CODEC_444_YV12,		//!< YV12 format 4:4:4 data (not currently supported by JPEG)
	IMG_CODEC_444_PL8,		//!< PL8 format 4:4:4 data (not currently supported by JPEG)
	IMG_CODEC_444_IMC2,		//!< PL8 format 4:4:4 data (not currently supported by JPEG)
	IMG_CODEC_444_PL12,		//!< PL12 format 4:4:4 data (not currently supported by JPEG)
	IMG_CODEC_ABCX,			//!< Interleaved 4:4:4 data (not currently supported by JPEG)
	IMG_CODEC_XBCA,			//!< Interleaved 4:4:4 data (not currently supported by JPEG)
	IMG_CODEC_ABC565,		//!< Packed 4:4:4 data (not currently supported by JPEG)

	IMG_CODEC_420_PL21,				//!< PL21 format YUV data
	IMG_CODEC_422_PL21,			//!< 4:2:2 PL21 format YUV data
	IMG_CODEC_444_PL21,				//!< 4:4:4 PL21 format YUV data (not currently supported by JPEG)

#if defined(HW_4_0)
	// 16 Bit (10 highest ten bits used) formats
	IMG_CODEC_444_YUV_16,  //!< 4:4:4, Y Cb Cr in 3 separate planes, 16-bit (most significant 10 bits used)
	IMG_CODEC_420_PL12_16, //!< 4:2:0, Y in 1 plane, CbCr interleaved in 2nd plane, 16-bit (most significant 10 bits used)
	IMG_CODEC_422_PL12_16,  //!< 4:2:2, Y in 1 plane, CbCr interleaved in 2nd plane, 16-bit (most significant 10 bits used)
	IMG_CODEC_444_PL12_16,  //!< 4:4:4, Y in 1 plane, CbCr interleaved in 2nd plane, 16-bit (most significant 10 bits used)

	// 10 Bit Packed formats
	IMG_CODEC_420_PL12_10,	//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_420PL12YCBCR10 4:2:0, Y in 1 plane, CbCr interleaved in 2nd plane, 10-bit components
	IMG_CODEC_420_PL21_10,	//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_420PL12YCRCB10	4:2:0, Y in 1 plane, CrCb interleaved in 2nd plane, 10-bit components
	IMG_CODEC_420_YUV_10,		//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_420PL111YCBCR10 4:2:0, Y Cb Cr in 3 separate planes, 10-bit components

	IMG_CODEC_422_PL12_10,	//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_422PL12YCBCR10 4:2:2, Y in 1 plane, CbCr interleaved in 2nd plane, 10-bit components
	IMG_CODEC_422_PL21_10,	//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_422PL12YCRCB10	4:2:2, Y in 1 plane, CrCb interleaved in 2nd plane, 10-bit components
	IMG_CODEC_422_YUV_10,		//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_422PL111YCBCR10 4:2:2, Y Cb Cr in 3 separate planes, 10-bit components

	IMG_CODEC_ABC_10,			//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_444IL3ABC10 4:4:4, Any 3 colour space components (e.g. RGB), 10-bit components, packed 32-bit per pixel in a single plane - TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_444IL3ABC10
	IMG_CODEC_444_PL12_10,	//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_444PL12YCBCR10 4:4:4, Y in 1 plane, CbCr interleaved in 2nd plane, 10-bit components
	IMG_CODEC_444_PL21_10,	//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_444PL12YCRCB10 4:4:4, Y in 1 plane, CrCb interleaved in 2nd plane, 10-bit components
	IMG_CODEC_444_YUV_10,		//!< TOPAZHP_CR_INPUT_FRAME_STORE_FORMAT_444PL111YCBCR10 4:4:4, Y Cb Cr in 3 separate planes, 10-bit components (could also be ABC, but colour space conversion is not supported by input scaler)
#endif
	PVR_SURF_UNSPECIFIED		//!< End of the enum
} IMG_FORMAT;

#if defined(HW_4_0)
typedef enum
{
	IMG_EncRes420,
	IMG_EncRes422,
	IMG_EncRes444
} IMG_ENCODERESOLUTION;
#endif

/*!
 *****************************************************************************
 *
 * @details    Enum describing presets for source image colour space conversion
 *
 * @brief          Colour space conversion presets
 *
 ****************************************************************************/
typedef enum
{
	IMG_CSC_NONE,			//!< No colour space conversion
	IMG_CSC_709_TO_601,		//!< ITU BT.709 YUV to be converted to ITU BT.601 YUV
	IMG_CSC_601_TO_709,		//!< ITU BT.601 YUV to be converted to ITU BT.709 YUV
	IMG_CSC_RGB_TO_601_ANALOG,	//!< RGB to be converted to ITU BT.601 YUV
	IMG_CSC_RGB_TO_601_DIGITAL,	//!< RGB to be converted to ITU BT.601 YCbCr for SDTV (reduced scale - 16-235)
	IMG_CSC_RGB_TO_601_DIGITAL_FS,	//!< RGB to be converted to ITU BT.601 YCbCr for HDTV (full range - 0-255)
	IMG_CSC_RGB_TO_709,		//!< RGB to be converted to ITU BT.709 YUV
	IMG_CSC_YIQ_TO_601,		//!< YIQ to be converted to ITU BT.601 YUV
	IMG_CSC_YIQ_TO_709,		//!< YIQ to be converted to ITU BT.709 YUV
	IMG_CSC_BRG_TO_601,		//!< BRG to be converted to ITU BT.601 YUV (for XRGB format)
	IMG_CSC_RBG_TO_601,		//!< RBG to be converted to ITU BT.601 YUV (for XBGR format)
    IMG_CSC_BGR_TO_601,     //!< BGR to be converted to ITU BT.601 YUV (for BGRX format)
	IMG_CSC_UYV_TO_YUV,     //!< UYV to be converted to YUV (BT.601 or BT.709)
	IMG_CSC_PRESETS			//!< End of the enum
} IMG_CSC_PRESET;


/*!
 *****************************************************************************
 *
 * @details    GOP structure information
 *
 * @brief      GOP structure
 *
 ****************************************************************************/
#define SHIFT_GOP_FRAMETYPE		(0)
#define MASK_GOP_FRAMETYPE		(0x3 << SHIFT_GOP_FRAMETYPE)
#define SHIFT_GOP_REFERENCE		(2)
#define MASK_GOP_REFERENCE		(0x1 << SHIFT_GOP_REFERENCE)
#define SHIFT_GOP_POS			(3)
#define MASK_GOP_POS			(0x1f << SHIFT_GOP_POS)
#define SHIFT_GOP_LEVEL			(4)
#define MASK_GOP_LEVEL			(0xF << SHIFT_GOP_LEVEL)
#define SHIFT_GOP_REF0			(0 + 8)
#define MASK_GOP_REF0			(0xf << SHIFT_GOP_REF0)
#define SHIFT_GOP_REF1			(4 + 8)
#define MASK_GOP_REF1			(0xf << SHIFT_GOP_REF1)


/*!
 *****************************************************************************
 *
 * @details    Frame types
 *
 * @brief      Frame types
 *
 ****************************************************************************/
typedef enum _frame_type_
{
	IMG_INTRA_IDR = 0,
	IMG_INTRA_FRAME,
	IMG_INTER_P,
	IMG_INTER_B,
} IMG_FRAME_TYPE;


/*!
 *****************************************************************************
 *
 * @details    Motion vector calculation register settings
 *
 * @brief      MV settings
 *
 ****************************************************************************/
typedef struct tag_IMG_MV_SETTINGS
{
	IMG_UINT32	ui32MVCalc_Below;
	IMG_UINT32	ui32MVCalc_Colocated;
	IMG_UINT32	ui32MVCalc_Config;
} IMG_MV_SETTINGS;


/*!
 *****************************************************************************
 *
 * @details    Frame template types
 *
 * @brief      Frame template types
 *
 ****************************************************************************/
typedef enum _frame_template_type_
{
	IMG_FRAME_IDR = 0,
	IMG_FRAME_INTRA,
	IMG_FRAME_INTER_P,
	IMG_FRAME_INTER_B,
	IMG_FRAME_INTER_P_IDR,
	IMG_FRAME_UNDEFINED
} IMG_FRAME_TEMPLATE_TYPE;


/*!
 *****************************************************************************
 *
 * @details    Rate control modes
 *
 * @brief      RC modes
 *
 ****************************************************************************/
typedef enum _IMG_RCMODE_
{
	IMG_RCMODE_NONE = 0,
	IMG_RCMODE_CBR,
	IMG_RCMODE_VBR,
	IMG_RCMODE_ERC,			// Example Rate Control
	IMG_RCMODE_VCM
} IMG_RCMODE;


/*!
 *****************************************************************************
 *
 * @details    Video Conferencing Mode (VCM) rate control method's sub modes
 *
 * @brief      VCM modes
 *
 ****************************************************************************/
typedef enum _IMG_RC_VCM_MODE_
{
	IMG_RC_VCM_MODE_DEFAULT = 0,
	IMG_RC_VCM_MODE_CFS_NONIFRAMES,
	IMG_RC_VCM_MODE_CFS_ALLFRAMES,
} IMG_RC_VCM_MODE;

/*!
 *****************************************************************************
 *
 * @details    Weighted prediction values
 *
 * @brief      Weighted prediction
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT8			frameType;
	IMG_BOOL8			weighted_pred_flag;			// Corresponds to field in the pps
	IMG_UINT8			weighted_bipred_idc;
	IMG_UINT32			luma_log2_weight_denom;
	IMG_UINT32			chroma_log2_weight_denom;
	IMG_BOOL8			weight_flag[3][2];			// Y, Cb, Cr Support for 2 ref pictures on P, or 1 pic in each direction on B.
	IMG_INT32			weight[3][2];
	IMG_INT32			offset[3][2];
} WEIGHTED_PREDICTION_VALUES;


/*!
 *****************************************************************************
 *
 * @details    
 *
 * @brief      
 *
 ****************************************************************************/
typedef enum _WEIGHTED_BIPRED_IDC_
{
	WBI_NONE = 0x0,
	WBI_EXPLICIT,
	WBI_IMPLICIT
} WEIGHTED_BIPRED_IDC;


/*!
 *****************************************************************************
 *
 * @details    Registers required to configure input scaler
 *
 * @brief      Scaler registers
 *
 ****************************************************************************/
typedef struct _IMG_VXE_SCALER_SETUP_
{
#if defined(HW_3_X)	
	IMG_UINT32		ui32InputScalerControl;
#endif	
#if defined(HW_4_0)	
	IMG_UINT32		ui32SeqCurPicConfig;
#endif
	IMG_UINT32		ui32ScalerInputSizeReg;
	IMG_UINT32		ui32ScalerCropReg;
	IMG_UINT32		ui32ScalerPitchReg;
	IMG_UINT32		ui32ScalerControl;
	IMG_UINT32		asHorScalerCoeffRegs[4];
	IMG_UINT32		asVerScalerCoeffRegs[4];
}IMG_VXE_SCALER_SETUP;

/*!
 *****************************************************************************
 *
 * @details    Registers required to configure input Colour Space conversion
 *
 * @brief      CSC registers
 *
 ****************************************************************************/
typedef struct _IMG_VXE_CSC_SETUP_
{
#if defined(HW_4_0)	
	IMG_UINT32		ui32CscSourceModY[3];
	IMG_UINT32		ui32CscOutputCoeff[2];
#endif
#if defined(HW_3_X)	
	IMG_UINT32		ui32CscSourceY[3];
	IMG_UINT32		ui32CscOutputClip[2];
#endif	
	IMG_UINT32		ui32CscSourceCbCr[3];
}
IMG_VXE_CSC_SETUP;


/*!
 *****************************************************************************
 *
 * @details    SETVIDEO & GETVIDEO - Video encode context
 *
 * @brief      Video context
 *
 ****************************************************************************/
typedef struct tag_IMG_MTX_VIDEO_CONTEXT
{
	IMG_UINT64		ui64ClockDivBitrate; // keep this at the top as it has alignment issues 

	IMG_UINT32		ui32WidthInMbs;							//!< target output width
	IMG_UINT32		ui32PictureHeightInMbs;					//!< target output height

#ifdef FORCED_REFERENCE
	IMG_UINT32		apTmpReconstructed[MAX_PIC_NODES];
#endif
	IMG_UINT32		apReconstructed[MAX_PIC_NODES];
	IMG_UINT32		apColocated[MAX_PIC_NODES];
	IMG_UINT32		apMV[MAX_MV];
	IMG_UINT32		apInterViewMV[2];

	IMG_UINT32		ui32DebugCRCs;							//!< Send debug information from Register CRCs to Host with the coded buffer

	IMG_UINT32		apWritebackRegions[WB_FIFO_SIZE];		//!< Data section

	IMG_UINT32		ui32InitialCPBremovaldelayoffset;
	IMG_UINT32		ui32MaxBufferMultClockDivBitrate;
	IMG_UINT32		pSEIBufferingPeriodTemplate;
	IMG_UINT32		pSEIPictureTimingTemplate;

	IMG_BOOL16		b16EnableMvc;
	IMG_UINT16		ui16MvcViewIdx;
	IMG_UINT32		apSliceParamsTemplates[5];
	IMG_UINT32		apPicHdrTemplates[4];

	IMG_UINT32		apSeqHeader;
	IMG_UINT32		apSubSetSeqHeader;
	IMG_BOOL16		b16NoSequenceHeaders;

	IMG_UINT32		aui32SliceMap[MAX_SOURCE_SLOTS_SL];		//!< Slice map of the source picture

	IMG_UINT32		ui32FlatGopStruct;						//!< Address of Flat MiniGop structure

	IMG_BOOL8		b8WeightedPredictionEnabled;
	IMG_UINT8		ui8MTXWeightedImplicitBiPred;
	IMG_UINT32		aui32WeightedPredictionVirtAddr[MAX_SOURCE_SLOTS_SL];

	IMG_UINT32		ui32HierarGopStruct;					//!< Address of hierarchical MiniGop structure

	IMG_UINT32		pFirstPassOutParamAddr[MAX_SOURCE_SLOTS_SL];				//!< Output Parameters of the First Pass
#ifndef EXCLUDE_BEST_MP_DECISION_DATA
	IMG_UINT32		pFirstPassOutBestMultipassParamAddr[MAX_SOURCE_SLOTS_SL];	//!< Selectable Output Best MV Parameters data of the First Pass
#endif
	IMG_UINT32		pMBCtrlInParamsAddr[MAX_SOURCE_SLOTS_SL];					//!< Input Parameters to the second pass

	IMG_UINT32		ui32PicRowStrideBytes;						//!< Strides of source Y data and chroma data

	IMG_UINT32		apAboveParams[TOPAZHP_MAX_NUM_PIPES];		//!< Picture level parameters (supplied by driver)

#if defined(VP8_DRIVER)
	IMG_UINT32		pVp8ProbBuffer[VP8_NUM_PROB_BUFFERS];		//!< Probability buffers for VP8
#endif

	IMG_UINT32		ui32IdrPeriod;
	IMG_UINT32		ui32IntraLoopCnt;
	IMG_UINT32		ui32BFrameCount;
	IMG_BOOL8		b8Hierarchical;
	IMG_UINT8		ui8MPEG2IntraDCPrecision;				//!< Only used in MPEG2, 2 bit field (0 = 8 bit, 1 = 9 bit, 2 = 10 bit and 3=11 bit precision). Set to zero for other encode standards.
	IMG_UINT8		aui8PicOnLevel[MAX_REF_LEVELS];

	IMG_UINT32		ui32VopTimeResolution;

	IMG_UINT16		ui16KickSize;							//!< Number of Macroblocks per kick
	IMG_UINT16		ui16KicksPerBU;							//!< Number of kicks per BU
	IMG_UINT16		ui16KicksPerPicture;					//!< Number of kicks per picture

	IMG_MV_SETTINGS	sMVSettingsIdr;

	IMG_MV_SETTINGS	sMVSettingsNonB[MAX_BFRAMES + 1];

	IMG_UINT32		ui32MVSettingsBTable;
	IMG_UINT32		ui32MVSettingsHierarchical;

	IMG_FORMAT		eFormat;								//!< Pixel format of the source surface
	IMG_STANDARD	eStandard;								//!< Encoder standard (H264 / H263 / MPEG4 / JPEG)
	IMG_RCMODE		eRCMode;								//!< RC flavour
	IMG_RC_VCM_MODE	eRCVcmMode;								//!< RC VCM flavour
	IMG_UINT32		uRCCfsMaxMarginPerc;					//!< RC VCM maximum frame size percentage allowed to exceed in CFS

	IMG_BOOL8		b8FirstPic;
	IMG_BOOL8		b8IsInterlaced;
	IMG_BOOL8		b8TopFieldFirst;
	IMG_BOOL8		b8ArbitrarySO;
	IMG_BOOL8		bOutputReconstructed;

	IMG_BOOL8		b8DisableBitStuffing;

	IMG_BOOL8		b8InsertHRDparams;

	IMG_UINT8		ui8MaxSlicesPerPicture;

	IMG_UINT32		ui32FCode;

	/* Contents Adaptive Rate Control parameters*/
	IMG_UINT32		ui32JMCOMP_RCReg_0;
	IMG_UINT32		ui32JMCOMP_RCReg_1;

	IMG_UINT32		ui32MVClip_Config;						//!< Value to use for MVClip_Config  register
	IMG_UINT32		ui32PredCombControl;					//!< Value to use for Predictor combiner register
	IMG_UINT32		ui32LRITC_Cache_Chunk_Config;			//!< Value to use for LRITC_Cache_Chunk_Config register
	IMG_UINT32		ui32IPEVectorClipping;					//!< Value to use for IPEVectorClipping register
	IMG_UINT32		ui32H264CompControl;					//!< Value to use for H264CompControl register
	IMG_UINT32		ui32H264CompIntraPredModes;				//!< Value to use for H264CompIntraPredMode register
	IMG_UINT32		ui32IPCM_0_Config;						//!< Value to use for IPCM_0 Config register
	IMG_UINT32		ui32IPCM_1_Config;						//!< Value to use for IPCM_1 Config register
	IMG_UINT32		ui32SPEMvdClipRange;					//!< Value to use for SPEMvdClipRange register
	IMG_UINT32		ui32MBHostCtrl;							//!< Value to use for MB_HOST_CONTROL register
	IMG_UINT32		ui32DeblockCtrl;						//!< Value for the CR_DB_DISABLE_DEBLOCK_IDC register
	IMG_UINT32		ui32SkipCodedInterIntra;				//!< Value for the CR_DB_DISABLE_DEBLOCK_IDC register

	IMG_UINT32		ui32VLCControl;
	IMG_UINT32		ui32VLCSliceControl;					//!< Slice control register value. Configures the size of a slice 
	IMG_UINT32		ui32VLCSliceMBControl;					//!< Slice control register value. Configures the size of a slice 
	IMG_UINT16		ui16CQPOffset;							//!< Chroma QP offset to use (when PPS id = 0) 

	IMG_BOOL8		b8CodedHeaderPerSlice;

	IMG_UINT8		ui8InitialQpI;							//!< Initial QP I frames 
	IMG_UINT8		ui8InitialQpP;							//!< Initial QP P frames 
	IMG_UINT8		ui8InitialQpB;							//!< Initial QP B frames 

	IMG_UINT32		ui32FirstPicFlags;
	IMG_UINT32		ui32NonFirstPicFlags;

#ifndef EXCLUDE_ADAPTIVE_ROUNDING
	IMG_BOOL16		bMCAdaptiveRoundingDisable;

#if defined(HW_3_X)
#define AR_REG_SIZE	18
#define AR_DELTA_SIZE 7
#endif
#if defined(HW_4_0)	
#define AR_REG_SIZE	39
#define AR_DELTA_SIZE 15
#endif

	IMG_UINT16		ui16MCAdaptiveRoundingOffsets[AR_REG_SIZE][4];
	IMG_INT16		i16MCAdaptiveRoundingOffsetsDelta[AR_DELTA_SIZE][4];
#endif

#ifdef FORCED_REFERENCE
	IMG_UINT32		ui32PatchedReconAddress;				//!< Reconstructed address to allow host picture management
	IMG_UINT32		ui32PatchedRef0Address;					//!< Reference 0 address to allow host picture management
	IMG_UINT32		ui32PatchedRef1Address;					//!< Reference 1 address to allow host picture management
#endif
#ifdef LTREFHEADER
	IMG_UINT32		aui32LTRefHeader[MAX_SOURCE_SLOTS_SL];
	IMG_INT8		i8SliceHeaderSlotNum;
#endif
	IMG_BOOL8		b8ReconIsLongTerm;
	IMG_BOOL8		b8Ref0IsLongTerm;
	IMG_BOOL8		b8Ref1IsLongTerm;
	IMG_UINT8		ui8RefSpacing;


#if defined(HW_4_0)
	IMG_BOOL8		b8Iipe0enable;
	IMG_UINT8		ui8BitDepth;
#endif	
	IMG_UINT8		ui8FWNumPipes;
	IMG_UINT8		ui8FWFirstPipe;
	IMG_UINT8		ui8FWLastPipe;
	IMG_UINT8		ui8FWPipesToUseFlags;

#if defined(VP8_DRIVER)
	IMG_BOOL8		bErrorResModeVp8;
#endif

#if defined(HW_4_0)
	IMG_BOOL8	b8HwFifo;
	IMG_BOOL8	b8LLEnabled;						// Enable linked list mode
	IMG_UINT8	ui8LLCodedBuffersPerPackage;			// Number of coded buffer slots per list (linked list mode only)
	IMG_UINT32	ui32LLNodesPerCodedBuffer;		// Size of a linked list segment in 1024 byte units
#if !defined(DISABLE_BUFFER_UPDATE_ON_SLICE)	
	IMG_UINT32	b8LLBufferUpdateOnSliceMode;		// Enable buffer update on slice mode (no slice can be larger than a linked list segment)
#endif	
#endif	
#if SECURE_IO_PORTS
	IMG_UINT32		ui32SecureIOControl;
#endif 
#if INPUT_SCALER_SUPPORTED
	IMG_VXE_SCALER_SETUP sScalerSetup;
	IMG_VXE_CSC_SETUP	sCsCSetup;
#endif
	IN_RC_PARAMS	sInParams;

} IMG_MTX_VIDEO_CONTEXT;

/*!
 *****************************************************************************
 *
 * @details    PICMGMT - Command sub-type
 *
 * @brief      PICMGMT sub-type
 *
 ****************************************************************************/
typedef enum _pic_mgmt_type_
{
	IMG_PICMGMT_REF_TYPE = 0,
	IMG_PICMGMT_GOP_STRUCT,
	IMG_PICMGMT_SKIP_FRAME,
	IMG_PICMGMT_EOS,
	IMG_PICMGMT_FLUSH,
	IMG_PICMGMT_QUANT,
	IMG_PICMGMT_STRIDE,
} IMG_PICMGMT_TYPE;


/*!
 *****************************************************************************
 *
 * @details    PROVIDE_REF_BUFFER - Purpose of the reference buffer
 *
 * @brief      Purpose of the reference buffer
 *
 ****************************************************************************/
typedef enum _buffer_type_
{
	IMG_BUFFER_REF0 = 0,
	IMG_BUFFER_REF1,
	IMG_BUFFER_RECON,
} IMG_REF_BUFFER_TYPE;


/*!
 *****************************************************************************
 *
 * @details    RC_UPDATE - IMG_V_RCUpdate parameters
 *
 * @brief      RC update parameters
 *
 ****************************************************************************/
typedef struct tag_IMG_PICMGMT_RC_UPDATE_DATA
{
	IMG_UINT32		ui32BitsPerFrame;		//!< Number of bits in a frame
	IMG_UINT8		ui8VCMIFrameQP;			//!< VCM I frame QP
} IMG_PICMGMT_RC_UPDATE_DATA;


/*!
 *****************************************************************************
 *
 * @details    PIC_MGMT - IMG_V_SetCustomScalingValues parameters
 *
 * @brief      Custom quantization parameters
 *
 ****************************************************************************/

typedef struct tag_IMG_PICMGMT_CUSTOM_QUANT_DATA
{
	IMG_UINT32	ui32Values;			//!< Address of custom quantization values
	IMG_UINT32	ui32Regs4x4Sp;		//!< Address of custom quantization register values for 4x4 Sp
	IMG_UINT32	ui32Regs8x8Sp;		//!< Address of custom quantization register values for 8x8 Sp
	IMG_UINT32	ui32Regs4x4Q;		//!< Address of custom quantization register values for 4x4 Q
	IMG_UINT32	ui32Regs8x8Q;		//!< Address of custom quantization register values for 8x8 Q
} IMG_PICMGMT_CUSTOM_QUANT_DATA;


/*!
 *****************************************************************************
 *
 * @details    MTX- > host message structure
 *
 * @brief      Response message structure
 *
 ****************************************************************************/
typedef struct tag_IMG_WRITEBACK_MSG
{
	IMG_UINT32 ui32CmdWord;
	union
	{
		struct
		{
			IMG_UINT32	ui32Data;
			IMG_UINT32	ui32ExtraData;
			IMG_UINT32	ui32WritebackVal;
		};
		IMG_UINT32	ui32CodedPackageConsumedIdx;
	};
} IMG_WRITEBACK_MSG;


/*!
 *****************************************************************************
 *
 * @details    PROVIDE_SOURCE_BUFFER - Details of the source picture buffer
 *
 * @brief      Source buffer parameters
 *
 ****************************************************************************/
typedef struct tag_IMG_SOURCE_BUFFER_PARAMS
{
	IMG_UINT64	ui64HostContext;			//!< Host context value. Keep at start for alignment.
	IMG_UINT32	ui32PhysAddrYPlane_Field0;	//!< Source pic phys addr (Y plane, Field 0)
	IMG_UINT32	ui32PhysAddrUPlane_Field0;	//!< Source pic phys addr (U plane, Field 0)
	IMG_UINT32	ui32PhysAddrVPlane_Field0;	//!< Source pic phys addr (V plane, Field 0)
	IMG_UINT32	ui32PhysAddrYPlane_Field1;	//!< Source pic phys addr (Y plane, Field 1)
	IMG_UINT32	ui32PhysAddrUPlane_Field1;	//!< Source pic phys addr (U plane, Field 1)
	IMG_UINT32	ui32PhysAddrVPlane_Field1;	//!< Source pic phys addr (V plane, Field 1)
	IMG_UINT8	ui8DisplayOrderNum;			//!< Number of frames in the stream (incl. skipped)
	IMG_UINT8	ui8SlotNum;					//!< Source slot number
	IMG_UINT8   uiReserved1;
	IMG_UINT8   uiReserved2;
} IMG_SOURCE_BUFFER_PARAMS;


/*!
 *****************************************************************************
 *
 * @details    Struct describing input parameters to encode a video slice
 *
 * @brief          Video slice parameters
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32Flags;					//!< Flags for slice encode

	// Config registers. These are passed straight through from drivers to hardware.
	IMG_UINT32	ui32SliceConfig;			//!< Value to use for Slice Config register
	IMG_UINT32	ui32IPEControl;				//!< Value to use for IPEControl register
	IMG_UINT32	ui32SeqConfig;				//!< Value to use for Sequencer Config register

	IMG_FRAME_TEMPLATE_TYPE	eTemplateType;	//!< Slice header template type
	MTX_HEADER_PARAMS sSliceHdrTmpl;		//!< Template of corresponding slice header
} SLICE_PARAMS;


/*!
 *****************************************************************************
 *
 * @details    Struct describing Minimum Coded Unit information for a single JPEG component plane.
 *				   Details the size of blocks to be taken from the plane and the maximum block positions.
 *				   Send to firmware in the MTX_CMDID_SETUP command as part of the JPEG_MTX_DMA_SETUP structure
 *
 * @brief          JPEG Minimum Coded Unit Information
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32WidthBlocks;	//!< Width in pixels, shall be a multiple of 8
	IMG_UINT32	ui32HeightBlocks;	//!< Height in pixels, shall be a multiple of 8
	IMG_UINT32	ui32XLimit;			//!< Blocks will not be encoded beyond this
	IMG_UINT32	ui32YLimit;			//!< Blocks will not be encoded beyond this
} MCUCOMPONENT;


/*!
 *****************************************************************************
 *
 * @details    Struct describing essential information about a single JPEG component plane, defines the
				   Physical address of the colour plane, its stride and its height.
 *				   Send to firmware in the MTX_CMDID_SETUP command as part of the JPEG_MTX_DMA_SETUP structure.
 *
 * @brief          Basic information for a single JPEG component plane, passed to firmware.
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32PhysAddr;	//!< Physical address Component plane in shared memory
	IMG_UINT32	ui32Stride;		//!< Stride of source plane */
	IMG_UINT32	ui32Height;		//!< Height of avaliable data in plane.  shall be a minumum of one MCU high
} COMPONENTPLANE;


/*!
 *****************************************************************************
 *
 * @details    Struct describing essential information required by firmware to encode a scan.
 *				   Send to firmware in the MTX_CMDID_SETUP command.
 *
 * @brief          Setup information for a single JPEG scan.
 *
 ****************************************************************************/
typedef struct
{
	COMPONENTPLANE	ComponentPlane[MTX_MAX_COMPONENTS];	//!< Array of component plane source information (detailing physical address, stride and height)
	MCUCOMPONENT	MCUComponent[MTX_MAX_COMPONENTS];	//!< Array of Minimum Coded Unit information for each component plane
	IMG_UINT32		ui32ComponentsInScan;				//!< Number of components
	IMG_UINT32		ui32TableA;							//!< Quantisation table for Luma component
	IMG_UINT16		ui16DataInterleaveStatus;			//!< Source component interleave status (0, C_INTERLEAVE, LC_UVINTERLEAVE or LC_VUINTERLEAVE)

	IMG_UINT8		ui8FWNumPipes;
	IMG_UINT8		ui8FWFirstPipe;
	IMG_UINT8		ui8FWLastPipe;
	IMG_UINT8		ui8FWPipesToUseFlags;

} JPEG_MTX_DMA_SETUP;


/*!
 *****************************************************************************
 *
 * @details    Struct containing writeback memory for interfacing between JPEG firmware and driver
 *
 * @brief          Setup information for a single JPEG scan.
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32	apWritebackRegions[WB_FIFO_SIZE];
} JPEG_MTX_WRITEBACK_MEMORY;


/*!
 *****************************************************************************
 *
 * @details    Struct sent with the MTX_CMDID_ISSUEBUFF command detailing
 *				   where a scan encode should begin (calculated from the total count of MCUs)
 *				   and how many MCU's should be processed in this scan.
 *				   
 * @brief          JPEG structure defining scan start position and how many MCUs to process
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32MCUPositionOfScanAndIndex;	//!< Scan start position in MCUs
	IMG_UINT32	ui32MCUCntAndResetFlag;			//!< [32:2] Number of MCU's to encode or decode, [1] Reset predictors (1=Reset, 0=No Reset)
} MTX_ISSUE_BUFFERS;

/*!
 *****************************************************************************
 *
 * @details    Struct describing JPEG quantization tables
 *
 * @brief          JPEG quantization tables
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT8	aui8LumaQuantParams[QUANT_TABLE_SIZE_BYTES];	//!< Luma quant params
	IMG_UINT8	aui8ChromaQuantParams[QUANT_TABLE_SIZE_BYTES];	//!< Chroma quant params
} JPEG_MTX_QUANT_TABLE;


/*!
 *****************************************************************************
 *
 * @details    Struct describing JPEG encode output header
 *
 * @brief          JPEG output buffer header
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32BytesUsed;		//!<
	IMG_UINT32	ui32BytesEncoded;	//!<
	IMG_UINT32	ui32BytesToEncode;	//!<
	IMG_UINT32	ui32Reserved3;		//!<
} BUFFER_HEADER;


/*!
 *****************************************************************************
 *
 * @details    Structure describing coded header data returned by the firmware.
 *             The size of the structure should not be more than 64 bytes (needs to have 64 byte alignment)
 *              (i.e. CODED_BUFFER_HEADER_SIZE)
 *
 * @brief      Coded header structure
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT64	ui64HostCtx;		//!< Host context value. Keep at top for alignment.
	IMG_UINT32	ui32BytesWritten;	//!< Bytes in this coded buffer excluding this header
	IMG_UINT32	ui32Feedback;		//!< Feedback word for this coded buffers
	IMG_UINT32	ui32ExtraFeedback;	//!< Extra feedback word for this coded buffers

	IMG_UINT16	ui16_I_MbCnt;		//!< Number of MBs coded as I-macroblocks in this slice
	IMG_UINT16	ui16_P_MbCnt;		//!< Number of MBs coded as P-macroblocks in this slice

	IMG_UINT16	ui16_B_MbCnt;		//!< Number of MBs coded as B-macroblocks in this slice
	IMG_UINT16	ui16_Skip_MbCnt;	//!< Number of MBs coded as skipped in this slice

	IMG_UINT16	ui16_IPCM_MbCnt;	//!< Number of macroblocks coded as IPCM in this slice
	IMG_UINT8	ui8_InterSumSatdHi;	//!< High 8 bits for the inter sum satd
	IMG_UINT8	ui8_IntraSumSatdHi;	//!< High 8 bits for the intra sum satd

	IMG_UINT32	ui32_DC_Bits;		//!< Number of bits use for coding DC coefficients in this slice
	IMG_UINT32	ui32_MV_Bits;		//!< Number of bits used for coding all Motion vector data in this slice
	IMG_UINT32	ui32_Symbols_Bits;	//!< Number of bits used for coding all MB level symbols in this slice
	IMG_UINT32	ui32_Residual_Bits;	//!< Number of bits used for coding residual data in all MBs in this slice

	IMG_UINT32	ui32_QpyInter;		//!< Sum of QPy/Qscale for all Inter-MBs in the slice
	IMG_UINT32	ui32_QpyIntra;		//!< Sum of QPy/Qscale for all Intra-MBs in the slice
	IMG_UINT32	ui32_InterSumSatd;	//!< Sum of SATD for all Inter-MBs in the slice
	IMG_UINT32	ui32_IntraSumSatd;	//!< Sum of SATD for all Intra-MBs in the slice
} CODED_DATA_HDR, *P_CODED_DATA_HDR;

#if defined(HW_4_0)
// Normal (non Linked-list) mode uses 1, VP8 uses 2
// Linked list can have multiple coded buffers (but they are not transferred to FW directly, they are filled in directly by hardware using the linked list provided)
	#define MAX_CODED_BUFFERS_PER_PACKAGE 14 // See above - there is no upper restriction on this value (can be greater if needed).
	#define MAX_CODED_BUFFERS_PER_PACKAGE_FW 2 // The actual maximum number of coded buffers per package in Firmware
#endif
#if defined(HW_3_X)
	#define MAX_CODED_BUFFERS_PER_PACKAGE_FW 1
	#define MAX_CODED_BUFFERS_PER_PACKAGE 1
#endif

// This structure is temporarily used during the 64 byte minimum DMA transfer from driver to FW
typedef struct
{
	IMG_UINT32 ui32CodedMemAddr[MAX_CODED_BUFFERS_PER_PACKAGE_FW];
	//////////////////
	// 2 Info words //
	//////////////////
	IMG_UINT32 ui32CodedHeaderAddr;
	IMG_UINT32 ui32CodedBuffer_Info; // Combined field Host->MTX = IsLinkedList, list segment (CB memory) size, number of list segments per coded buffer

	// PAD TO 64 BYTES
	IMG_UINT32 ui32Padding[16 - MAX_CODED_BUFFERS_PER_PACKAGE_FW - 2];
} CODED_PACKAGE_DMA_INFO;


#define SHIFT_JPEG_ISSUEBUFF_MPSP_SCANSTARTPOS		(2)				
#define MASK_JPEG_ISSUEBUFF_MPSP_SCANSTARTPOS		(0xFFFFFFFC)	
#define SHIFT_JPEG_ISSUEBUFF_MPSP_PIPENO				(0)				
#define MASK_JPEG_ISSUEBUFF_MPSP_PIPENO				(0x3)			


/*!
 *****************************************************************************
 *
 * @details    Contents of the coded data buffer header feedback word
 *
 * @brief      Coded header feedback
 *
 ****************************************************************************/
#define SHIFT_CODED_FIRST_BU			(24)
#define MASK_CODED_FIRST_BU				(0xFF << SHIFT_CODED_FIRST_BU)
#define SHIFT_CODED_SLICE_NUM			(16)
#define MASK_CODED_SLICE_NUM			(0xFF << SHIFT_CODED_SLICE_NUM)
#define SHIFT_CODED_STORAGE_FRAME_NUM	(14)
#define MASK_CODED_STORAGE_FRAME_NUM	(0x03 << SHIFT_CODED_STORAGE_FRAME_NUM)
#define SHIFT_CODED_LL_DISCARDED_FRAME	(13)
#define MASK_CODED_LL_DISCARDED_FRAME	(0x01 << SHIFT_CODED_LL_DISCARDED_FRAME)
#define SHIFT_CODED_ENTIRE_FRAME		(12)
#define MASK_CODED_ENTIRE_FRAME			(0x01 << SHIFT_CODED_ENTIRE_FRAME)
#define SHIFT_CODED_IS_SKIPPED			(11)
#define MASK_CODED_IS_SKIPPED			(0x01 << SHIFT_CODED_IS_SKIPPED)
#define SHIFT_CODED_IS_CODED			(10)
#define MASK_CODED_IS_CODED				(0x01 << SHIFT_CODED_IS_CODED)
#define SHIFT_CODED_RECON_IDX			(6)
#define MASK_CODED_RECON_IDX			(0x0F << SHIFT_CODED_RECON_IDX)
#define SHIFT_CODED_SOURCE_SLOT			(2)
#define MASK_CODED_SOURCE_SLOT			(0x0F << SHIFT_CODED_SOURCE_SLOT)
#define SHIFT_CODED_FRAME_TYPE			(0)
#define MASK_CODED_FRAME_TYPE			(0x03 << SHIFT_CODED_FRAME_TYPE)


/*!
 *****************************************************************************
 *
 * @details    Contents of the coded data buffer header extra feedback word
 *
 * @brief      Coded header extra feedback
 *
 ****************************************************************************/
#define SHIFT_CODED_SLICES_SO_FAR					(24)
#define MASK_CODED_SLICES_SO_FAR					(0xFF << SHIFT_CODED_SLICES_SO_FAR)

#define SHIFT_CODED_SLICES_IN_BUFFER				(16)
#define MASK_CODED_SLICES_IN_BUFFER					(0xFF << SHIFT_CODED_SLICES_IN_BUFFER)

#define SHIFT_CODED_BUFFER_PIPE						(14)
#define MASK_CODED_BUFFER_PIPE						(0x03 << SHIFT_CODED_BUFFER_PIPE)

#if defined(VP8_DRIVER)
#define SHIFT_CODED_FIRST_FRAME_VP8					(10)
#define MASK_CODED_FIRST_FRAME_VP8					(0x01 << SHIFT_CODED_FIRST_FRAME_VP8)
#endif

#define SHIFT_CODED_BUFFER_NUMBER_USED				(2)
#define MASK_CODED_BUFFER_NUMBER_USED				(0xFF << SHIFT_CODED_BUFFER_NUMBER_USED)

#define SHIFT_CODED_FIELD							(1)
#define MASK_CODED_FIELD							(0x01 << SHIFT_CODED_FIELD)

#define SHIFT_CODED_PATCHED_RECON					(0)
#define MASK_CODED_PATCHED_RECON					(0x01 << SHIFT_CODED_PATCHED_RECON) 

/*!
 *****************************************************************************
 *
 * @details    Bias and Shift Values for Second Pass Input 
 *
 * @brief      Second Pass Input (Input Control Buffer)
 *
 ****************************************************************************/

#if defined(HW_4_0)
#define SHIFT_EXACT_QP						  (3) // Starting Bit for the exact QP field of the Macroblock Control Input Structure
#define EXACT_QP_ENABLED					  (1) // The value specified in INPUT_QP field is to be used as absolute QP regardless a previous setting to use it as delta
#define EXACT_QP_DISABLED					  (0) // Do not override MB_HOST_CONTROL register settings
#endif

#define SHIFT_INTER_INTRA_SCALE_TAB_INDEX     (4) //Starting Bit for indicating the index of intra/intra scale table to be used
#define SHIFT_SKIPPED_CODED_SCALE_TAB_INDEX   (7) //Starting Bit for indicating the index of skipped/coded scale table to be used
#define SHIFT_INPUT_QP                        (10)//Starting Bit for requested QP for the particular macroblock

#define BIAS_CONFIG_INTRA_FOUR_INTER_ZERO     (0) // Force intra by scaling its cost by 0
#define BIAS_CONFIG_INTRA_THREE_INTER_ONE     (1) // favour intra by a factor 3
#define BIAS_CONFIG_INTRA_TWO_INTER_ONE       (2) // favour intra by a factor 2
#define BIAS_CONFIG_INTRA_ONE_INTER_ONE       (3) // no bias
#define BIAS_CONFIG_INTRA_ONE_INTER_ONE_DUP   (4) // no bias
#define BIAS_CONFIG_INTRA_ONE_INTER_TWO       (5) // favour inter by a factor 2
#define BIAS_CONFIG_INTRA_ONE_INTER_THREE     (6) // favour inter by a factor 3
#define BIAS_CONFIG_INTRA_ZERO_INTER_FOUR     (7) // Force inter by scaling it's cost by 0

#define BIAS_CONFIG_CODED_FOUR_SKIPPED_ZERO   (0) // Force coded by scaling its cost by 0
#define BIAS_CONFIG_CODED_THREE_SKIPPED_ONE   (1) // favour coded by a factor 3
#define BIAS_CONFIG_CODED_TWO_SKIPPED_ONE     (2) // favour coded by a factor 2
#define BIAS_CONFIG_CODED_ONE_SKIPPED_ONE     (3) // no bias
#define BIAS_CONFIG_CODED_ONE_SKIPPED_ONE_DUP (4) // no bias
#define BIAS_CONFIG_CODED_ONE_SKIPPED_TWO     (5) // favour skipped by a factor 2
#define BIAS_CONFIG_CODED_ONE_SKIPPED_THREE   (6) // favour skipped by a factor 3
#define BIAS_CONFIG_CODED_ZERO_SKIPPED_FOUR   (7) // Force skipped by scaling it's cost by 0


#if defined(HW_3_X)
/*!
 *****************************************************************************
 *
 * @details		Mask and Shift Values for software copy of line counter register
 *
 * @brief		Copy of the hardware TOPAZHP_LINE_COUNTER register maintained in
 *				FIRMWARE_REG_5 (show line and frame count)
 *
 ****************************************************************************/
// Bits [0:11] hold the line count
#define SHIFT_SW_LINE_COUNT		(0)
#define MASK_SW_LINE_COUNT		(0x00000FFF << SHIFT_SW_LINE_COUNT)
// Bits [16:31] hold the frame count
#define SHIFT_SW_FRAME_COUNT	(16)
#define MASK_SW_FRAME_COUNT		(0x0000FFFF << SHIFT_SW_FRAME_COUNT)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _TOPAZSCFWIF_H_ */
