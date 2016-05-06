/*!
 *****************************************************************************
 *
 * @File       fw_interface.h
 * @Title      Host<->Firmware interface structure definition
 * @Description    This file defines structures/types shared between the host and
 *  firmware. It is to be always updated in the firmware tree and
 *  then propagated to the host driver, not vice-versa.
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

#ifndef FW_INTERFACE_H_
#define FW_INTERFACE_H_

#define MSG_TYPE_PADDING				( 0x00 )
#define	MSG_TYPE_START_PSR_HOSTMTX_MSG  ( 0x80 )	//!< Start of parser specific Host->MTX messages.
#define	MSG_TYPE_START_PSR_MTXHOST_MSG  ( 0xC0 )	//!< Start of parser specific MTX->Host messages.


enum
{
	FW_DEVA_INIT				= MSG_TYPE_START_PSR_HOSTMTX_MSG,
	FW_DEVA_DECODE_FE,
	FW_DEVA_RES_0,
	FW_DEVA_RES_1,
	FW_DEVA_DECODE_BE,
	FW_DEVA_HOST_BE_OPP,
	FW_DEVA_DEBLOCK,
	FW_DEVA_INTRA_OOLD,
	FW_DEVA_ENDFRAME,

	FW_DEVA_PARSE,
	FW_DEVA_BEGINFRAME,

	/*! Sent by the firmware on the MTX to the host.
	 */
	FW_DEVA_COMPLETED			= MSG_TYPE_START_PSR_MTXHOST_MSG,
	FW_DEVA_RES_2,
	FW_DEVA_RES_3,
	FW_DEVA_RES_4,
	FW_DEVA_RES_5,

	FW_DEVA_RES_6,
	FW_DEVA_CONTIGUITY_WARNING,
	FW_DEVA_PANIC,
	FW_DEVA_RES_7,
	FW_DEVA_RES_8,
	FW_DEVA_SIGNATURES_LEGACY	= 0xD0,
	FW_DEVA_SIGNATURES_HEVC		= 0xE0,
};

/*************************************************************************//**
Defines the Host/Firmware communication area
******************************************************************************/
//size
#ifndef VDEC_USE_PVDEC_COMPATIBILITY
#define COMMS_HEADER_SIZE		(0x34)
#else /* def VDEC_USE_PVDEC_COMPATIBILITY */
#define COMMS_HEADER_SIZE       (0x38)
#endif /* def VDEC_USE_PVDEC_COMPATIBILITY */
//dwords
#define PVDEC_COM_RAM_FW_STATUS_OFFSET						0x00
#define PVDEC_COM_RAM_TASK_STATUS_OFFSET					0x04
#define PVDEC_COM_RAM_FW_ID_OFFSET							0x08
#define PVDEC_COM_RAM_FW_MTXPC_OFFSET						0x0c
#define PVDEC_COM_RAM_MSG_COUNTER_OFFSET					0x10
#define PVDEC_COM_RAM_SIGNATURE_OFFSET						0x14
#define PVDEC_COM_RAM_TO_HOST_BUF_SIZE_AND_OFFSET_OFFSET	0x18
#define PVDEC_COM_RAM_TO_HOST_RD_INDEX_OFFSET				0x1c
#define PVDEC_COM_RAM_TO_HOST_WRT_INDEX_OFFSET				0x20
#define PVDEC_COM_RAM_TO_MTX_BUF_SIZE_AND_OFFSET_OFFSET		0x24
#define PVDEC_COM_RAM_TO_MTX_RD_INDEX_OFFSET				0x28
#define PVDEC_COM_RAM_FLAGS_OFFSET							0x2c
#define PVDEC_COM_RAM_TO_MTX_WRT_INDEX_OFFSET				0x30
#ifdef VDEC_USE_PVDEC_COMPATIBILITY
#define PVDEC_COM_RAM_STATE_BUF_SIZE_AND_OFFSET_OFFSET      0x34
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */
//fields
#define PVDEC_COM_RAM_TO_HOST_BUF_SIZE_AND_OFFSET_SIZE_MASK		0xFFFF
#define PVDEC_COM_RAM_TO_HOST_BUF_SIZE_AND_OFFSET_SIZE_SHIFT	0
#define PVDEC_COM_RAM_TO_HOST_BUF_SIZE_AND_OFFSET_OFFSET_MASK	0xFFFF0000
#define PVDEC_COM_RAM_TO_HOST_BUF_SIZE_AND_OFFSET_OFFSET_SHIFT	16

#define PVDEC_COM_RAM_TO_MTX_BUF_SIZE_AND_OFFSET_SIZE_MASK		0xFFFF
#define PVDEC_COM_RAM_TO_MTX_BUF_SIZE_AND_OFFSET_SIZE_SHIFT		0
#define PVDEC_COM_RAM_TO_MTX_BUF_SIZE_AND_OFFSET_OFFSET_MASK	0xFFFF0000
#define PVDEC_COM_RAM_TO_MTX_BUF_SIZE_AND_OFFSET_OFFSET_SHIFT	16
#ifdef VDEC_USE_PVDEC_COMPATIBILITY
#define PVDEC_COM_RAM_STATE_BUF_SIZE_AND_OFFSET_SIZE_MASK       0xFFFF
#define PVDEC_COM_RAM_STATE_BUF_SIZE_AND_OFFSET_SIZE_SHIFT      0
#define PVDEC_COM_RAM_STATE_BUF_SIZE_AND_OFFSET_OFFSET_MASK     0xFFFF0000
#define PVDEC_COM_RAM_STATE_BUF_SIZE_AND_OFFSET_OFFSET_SHIFT    16
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */
#define PVDEC_COM_RAM_BUF_GET_SIZE(_reg_, _name_) \
    ((_reg_ & PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_SIZE_MASK) >> PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_SIZE_SHIFT)
#define PVDEC_COM_RAM_BUF_GET_OFFSET(_reg_, _name_) \
    ((_reg_ & PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_OFFSET_MASK) >> PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_OFFSET_SHIFT)
#define PVDEC_COM_RAM_BUF_SET_SIZE_AND_OFFSET(_name_, _size_, _offset_) \
    (((_size_ << PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_SIZE_SHIFT) & PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_SIZE_MASK) | \
     ((_offset_ << PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_OFFSET_SHIFT) & PVDEC_COM_RAM_##_name_##_BUF_SIZE_AND_OFFSET_OFFSET_MASK))
//values
/** Firmware ready signature value */
	#define FW_READY_SIGNATURE						(0xA5A5A5A5)

/** Firmware status values */
	#define FW_STATUS_BUSY										0
	#define FW_STATUS_IDLE										1
	#define FW_STATUS_PANIC										2
	#define FW_STATUS_ASSERT									3
	#define FW_STATUS_GAMEOVER									4
	#define FW_STATUS_FEWATCHDOG								5
	#define FW_STATUS_EPWATCHDOG								6
	#define FW_STATUS_BEWATCHDOG								7

/** ************************************************************************************************************************************************** */
/** Decode Message Flags*/
/** ************************************************************************************************************************************************** */

	#define	FW_DEVA_RENDER_IS_FIRST_SLICE			(0x00000001)
	#define	FW_DEVA_FORCE_RECON_WRITE_DISABLE		(0x00000002)	/* This is H264 Mbaff - required for state store */
	#define	FW_DEVA_RENDER_IS_LAST_SLICE 			(0x00000004)
	#define	FW_DEVA_DECODE_DISABLE_EOF_DETECTION	(0x00000008)	/* Prevents insertion of end of picture or flush at VEC EOS */

	#define FW_DEVA_CONTEXT_BUFFER_INVALID			(0x00000010)
	#define FW_DEVA_FORCE_ALT_OUTPUT				(0x00000020)
	#define	FW_SECURE_STREAM						(0x00000040)
	#define	FW_LOW_LATENCY							(0x00000080)

	#define FW_DEVA_CONTIGUITY_DETECTION			(0x00000100)
	//#define	FW_ENABLE_PARALLEL_DECODE				(0x00000200)	/* Sends EOP in Pre HL setup - needed for FS and Scaling */
	#define	FW_DEVA_DEBLOCK_ENABLE					(0x00000400)
	#define FW_DEVA_IMMEDIATE_ABORT_FAULTED			(0x00000800)

	#define FW_DEVA_FORCE_AUX_LINE_BUF_DISABLE		(0x00001000)
	#define FW_DEVA_RENDER_NO_RESPONCE_MSG			(0x00002000)  /* Cause no responce message to be sent, and no interupt generation on successfull completion */
	#define	FW_DEVA_RENDER_HOST_INT					(0x00004000)	/* Cause an interupt if a responce message is generated on successfull completion */
	#define FW_DEVA_CONTIGUITY_REPORTING			(0x00008000)	/* Report contiguity errors to host */

	#define FW_DEVA_VC1_SKIPPED_PICTURE				(0x00010000)	/* Output flag only */
	#define FW_INTERNAL_RENDER_SWITCH				(0x00020000)
	#define FW_INTERNAL_FIELD_TYPE_CHANGE			(0x00040000)
	#define DEBLOCKING_FORCED_OFF					(0x00080000)

	#define DEFER_BECAUSE_LAST_UN_COMPLETE			(0x00100000)
	#define DETECTED_RENDEC_FULL					(0x00200000)	/* Only for debug */
	#define DETECTED_RENDEC_EMPTY					(0x00400000)	/* Only for debug */
	#define FW_ONE_PASS_PARSE						(0x00800000)

	#define FW_DEVA_EARLY_COMPLETE					(0x01000000)
	#define	FW_DEVA_FE_EP_SIGNATURES_READY			(0x02000000)
	#define FW_VEC_EOS								(0x04000000)
	#define FW_DEVA_ERROR_DETECTED_ENT				(0x08000000)	/* hardware has reported an error relating to this command */

	#define FW_DEVA_ERROR_DETECTED_PIX				(0x10000000)
	#define FW_DEVA_MP_SYNC							(0x20000000)
	#define MORE_THAN_ONE_MB						(0x40000000)
	#define BRN52333_DETECTED						(0x80000000)
/** end of message flags */
#ifdef VDEC_USE_PVDEC_COMPATIBILITY
/** ************************************************************************************************************************************************** */
/** VDEC Decode Message Flags*/
/** ************************************************************************************************************************************************** */
#define FW_VDEC_NEW_SEQUENCE                    (0x00000001)    /* This is a first picture of a sequence. */
#define FW_VDEC_NAL_SIZE_DELIM                  (0x00000010)    /* H.264/H.265 are to be configured in SIZE_DELIMITED mode rather than SCP mode. */
/** end of message flags */
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

/* ********************************************************************************************************** */
/** FW flags */
/* ********************************************************************************************************** */
	#define	FWFLAG_DISABLE_VDEB_PRELOAD				(0x00000001)		/* TOOD : Temporary for HW tetsing */
	#define	FWFLAG_BIG_TO_HOST_BUFFER				(0x00000002)		
	#define	FWFLAG_FORCE_FS_FLOW					(0x00000004)		
	#define FWFLAG_DISABLE_WATCHDOG_TIMERS			(0x00000008)

	#define	FWFLAG_FAKE_BRN52333				(0x00000010)
	#define	FWFLAG_DISABLE_AEH						(0x00000020)
	#define	FWFLAG_DISABLE_AUTONOMOUS_RESET			(0x00000040)
	#define	FWFLAG_BRN52333_NO_RTM_CHECK		(0x00000080)

	#define	FWFLAG_DISABLE_2PASS_DEBLOCK			(0x00000100)
	#define	FWFLAG_NO_INT_ON_TOHOST_FULL			(0x00000200)
	#define	FWFLAG_FORCE_SINGLE_PP					(0x00000400)
	#define FWFLAG_RETURN_VDEB_CR					(0x00000800)

	#define FWFLAG_DISABLE_AUTOCLOCKGATING			(0x00001000)
	#define FWFLAG_DISABLE_IDLE_GPIO				(0x00002000)
	#define FWFLAG_XPL								(0x00004000)
	#define FWFLAG_INFINITE_MTX_TIMEOUT				(0x00008000)

	#define	FWFLAG_TILE_STRIDE_PER_CONTEXT			(0x00010000)
	#define	FWFLAG_DISABLE_FW_DEBLOCK				(0x00020000)
	#define	FWFLAG_ON_ERR_DEBLOCK_PRELOAD			(0x00040000)
	#define FWFLAG_ENABLE_SECURITY					(0x00080000)

	#define FWFLAG_ENABLE_CONCEALMENT				(0x00100000)
	#define	FWFLAG_PREEMPT							(0x00200000)
	#define FWFLAG_FORCE_FLUSHING					(0x00400000)
	#define	FWFLAG_DISABLE_GENC_FLUSHING			(0x00800000)

	#define FWFLAG_DISABLE_COREWDT_TIMERS			(0x01000000)
	#define FWFLAG_DISABLE_RENDEC_AUTOFLUSH			(0x02000000)
	#define FWFLAG_FORCE_STRICT_SINGLEPIPE			(0x04000000)
	#define FWFLAG_CONSISTENT_MULTIPIPE_FLOW		(0x08000000)

	#define	FWFLAG_DISABLE_IDLE_FAST_EVAL			(0x10000000)
	#define	FWFLAG_FAKE_COMPLETION					(0x20000000)
	#define	FWFLAG_MAN_PP_CLK						(0x40000000)
	#define	FWFLAG_STACK_CHK						(0x80000000)


/** end of FW flags */





/*****************************************************************/
/* Control Allocation */
/*****************************************************************/
#define CMD_MASK									(0xF0000000)

/*****************************************************************/
/* Ctrl Allocation Header */
/*****************************************************************/
#define CMD_CTRL_ALLOC_HEADER						(0x90000000)	
typedef struct _CTRL_ALLOC_HEADER_TAG
{
	IMG_UINT32 ui32Cmd_AdditionalParams;
	IMG_UINT32 ui32SliceParams;
	union
	{
		IMG_UINT32 uiVP8ProbabilityData;
		IMG_UINT32 uiH264PipeIntraBufferSize;
	};
	IMG_UINT32 uiChromaStrides;
	IMG_UINT32 uiSliceFirstMbYX;
	IMG_UINT32 uiPicLastMbYX;
	IMG_UINT32 ui32AltOutputAddr[2];				/* VC1 only : Store Range Map flags in bottom bits of [0] */
	IMG_UINT32 ui32AltOutputFlags;
	IMG_UINT32 ui32ExtOpMode;						/* H264 Only : Extended Operating Mode */
} CTRL_ALLOC_HEADER;
#define CMD_CTRL_ALLOC_HEADER_DWSIZE				(sizeof(CTRL_ALLOC_HEADER)/sizeof(IMG_UINT32))

/* Additional Parameter flags */
#define VC1_PARSEHDR_MASK							(0x00000001)
#define VC1_SKIPPIC_MASK							(0x00000002)

#define VP6_BUFFOFFSET_MASK							(0x0000ffff)
#define VP6_MULTISTREAM_MASK						(0x01000000)
#define VP6_FRAMETYPE_MASK							(0x02000000)

#define VP8_BUFFOFFSET_MASK							(0x00ffffff)
#define VP8_PARTITIONSCOUNT_MASK					(0x0f000000)
#define VP8_PARTITIONSCOUNT_SHIFT					( 24 )

/*****************************************************************/
/* Nop Command */
/*****************************************************************/
#define CMD_NOP										(0x00000000)
#define CMD_NOP_DWSIZE								(1)

/*****************************************************************/
/* Register Block  */
/*****************************************************************/
#define CMD_REGISTER_BLOCK							(0x10000000)
#define CMD_REGISTER_BLOCK_PATCHING_REQUIRED		(0x01000000)
#define CMD_REGISTER_BLOCK_FLAG_PRELOAD				(0x04000000)
#ifdef VDEC_USE_PVDEC_COMPATIBILITY
#define CMD_REGISTER_BLOCK_FLAG_VLC_DATA            (0x08000000)
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

/*****************************************************************/
/* Rendec Command */
/*****************************************************************/
#define CMD_RENDEC_BLOCK							(0x50000000)
#define CMD_RENDEC_BLOCK_FLAG_MASK					(0x0F000000)
#define CMD_RENDEC_FORCE							(0x08000000)
#define CMD_RENDEC_PATCHING_REQUIRED				(0x01000000)
#ifdef VDEC_USE_PVDEC_COMPATIBILITY
#define CMD_RENDEC_WORD_COUNT_MASK                  (0x00ff0000)
#define CMD_RENDEC_WORD_COUNT_SHIFT                 ( 16 )
#define CMD_RENDEC_ADDRESS_MASK                     (0x0000ffff)
#define CMD_RENDEC_ADDRESS_SHIFT                    ( 0 )
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

/*****************************************************************/
/* Deblock */
/*****************************************************************/
#define CMD_DEBLOCK									(0x70000000)
#define CMD_DEBLOCK_TYPE_STD						(0x00000000)
#define CMD_DEBLOCK_TYPE_OOLD						(0x00000001)
#define CMD_DEBLOCK_TYPE_SKIP						(0x00000002)
#define CMD_DEBLOCK_TYPE_EF							(0x00000003)  	/*End Of Frame*/

typedef struct _DEBLOCK_CMD_TAG
{
	IMG_UINT32 ui32Cmd;								/* 0x70000000 */
	IMG_UINT32 ui32SourceMbData;
	IMG_UINT32 ui32AddressA[2];
} DEBLOCK_CMD;
#define CMD_DEBLOCK_DWSIZE							(sizeof(DEBLOCK_CMD)/sizeof(IMG_UINT32))

/*****************************************************************/
/* Skip */
/*****************************************************************/
#define CMD_CONDITIONAL_SKIP						(0x80000000)
#define CMD_CONDITIONAL_SKIP_DWSIZE					(1)
#define CMD_CONDITIONAL_SKIP_DWORDS					(0x0000ffff)
#define CMD_CONDITIONAL_SKIP_CONTEXT_SWITCH			(1<<20)
#define ENABLE_SKIP_COMMAND							(1)

/*****************************************************************/
/* DMA */
/*****************************************************************/
#define CMD_DMA										(0xE0000000)
#define CMD_DMA_DMA_TYPE_MASK						(0x03000000)
#define CMD_DMA_DMA_TYPE_SHIFT						( 24 )
#define CMD_DMA_FLAG_MASK							(0x00100000)
#define CMD_DMA_FLAG_SHIFT							( 20 )
#define CMD_DMA_DMA_SIZE_MASK						(0x000fffff)

#define CMD_DMA_OFFSET_FLAG							(0x00100000)



#define CMD_DMA_MAX_OFFSET							(0xFFF)
#define	CMD_DMA_TYPE_VLC_TABLE						( 0 << CMD_DMA_DMA_TYPE_SHIFT )
#define	CMD_DMA_TYPE_PROBABILITY_DATA				( 1 << CMD_DMA_DMA_TYPE_SHIFT )

typedef struct
{
	IMG_UINT32 ui32Cmd;
	IMG_UINT32 ui32DevVirtAdd;
} DMA_CMD;

#define CMD_DMA_DWSIZE						(sizeof(DMA_CMD)/sizeof(IMG_UINT32))

typedef struct
{
	IMG_UINT32 ui32Cmd;
	IMG_UINT32 ui32DevVirtAdd;
	IMG_UINT32 ui32ByteOffset;
} DMA_CMD_WITH_OFFSET;

#define CMD_DMA_OFFSET_DWSIZE				(sizeof(DMA_CMD_WITH_OFFSET)/sizeof(IMG_UINT32))


/*****************************************************************/
/* HOST COPY */
/*****************************************************************/
#define CMD_HOST_COPY								(0xF0000000)
#define CMD_HOST_COPY_SIZE_MASK						(0x000fffff)

typedef struct
{
	IMG_UINT32 ui32Cmd;
	IMG_UINT32 ui32SrcDevVirtAdd;
	IMG_UINT32 ui32DstDevVirtAdd;
} HOST_COPY_CMD;

#define CMD_HOST_COPY_DWSIZE					(sizeof(HOST_COPY_CMD)/sizeof(IMG_UINT32))

/*****************************************************************/
/* Shift register setup and Bitstream DMA */
/*****************************************************************/
#define CMD_SR_SETUP				   				(0xB0000000)
#define CMD_SR_ENABLE_RBDU_EXTRACTION				(0x00000001)
#define CMD_SR_ENABLE_AES_COUNTER					(0x00000002)
#define CMD_SR_VERIFY_STARTCODE						(0x00000004)
#define CMD_SR_BITSTR_ADDR_DEREF					(0x00000008)
#define CMD_SR_BITSTR_PARSE_KEY						(0x00000010)
typedef struct
{
	IMG_UINT32 ui32Cmd;
	IMG_UINT32 ui32BitstreamOffsetBits;
	IMG_UINT32 ui32BitstreamSizeBytes;
} SR_SETUP_CMD;
#define CMD_SR_DWSIZE				   				(sizeof(SR_SETUP_CMD)/sizeof(IMG_UINT32))

#define CMD_BITSTREAM_DMA							(0xA0000000)
#define CMD_BITSTREAM_DMA_DWSIZE				   	(2)
/*****************************************************************/
/* VC1 Parse Header Command */
/*****************************************************************/
#define CMD_PARSE_HEADER							(0x30000000)
#define CMD_PARSE_HEADER_CONTEXT_MASK				(0x000000ff)
#define CMD_PARSE_HEADER_NEWSLICE					(0x00000001)
#define CMD_PARSE_HEADER_SKIP_PIC					(0x00000002)
#define CMD_PARSE_HEADER_ONEPASSPARSE				(0x00000004)
#define CMD_PARSE_HEADER_NUMSLICE_MINUS1			(0x00ffff00)

typedef struct _PARSE_HEADER_CMD_TAG {
	IMG_UINT32	ui32Cmd;
	IMG_UINT32	ui32SeqHdrData;
	IMG_UINT32	ui32PicDimensions;
	IMG_UINT32	ui32BitplaneAddr[3];
	IMG_UINT32	ui32VLCTableAddr;
} PARSE_HEADER_CMD;

#define CMD_PARSE_DWSIZE				   			(sizeof(PARSE_HEADER_CMD)/sizeof(IMG_UINT32))

#define CMD_SLICE_INFO								(0x20000000)
#define CMD_SLICE_INFO_SLICENUM						(0xff000000)
#define CMD_SLICE_INFO_FIRSTMBY						(0x00ff0000)
#define CMD_SLICE_INFO_MBBITOFFSET					(0x0000ffff)
typedef struct _SLICE_INFO_TAG {
	IMG_UINT8	ui8SliceNum;
	IMG_UINT8	ui8SliceFirstMBY;
	IMG_UINT16	ui16SliceMBBitOffset;
} SLICE_INFO;

#ifdef VDEC_USE_PVDEC_COMPATIBILITY
/*****************************************************************/
/* VDEC extension */
/*****************************************************************/
#define CMD_VDEC_EXT								(0xC0000000)

#define MEM2REG_SIZE_HOST_PART_MASK 0x0000FFFF
#define MEM2REG_SIZE_HOST_PART_SHIFT 0

#define MEM2REG_SIZE_BUF_TOTAL_MASK 0xFFFF0000
#define MEM2REG_SIZE_BUF_TOTAL_SHIFT 16

typedef struct _VDEC_EXT_CMD_TAG {
	IMG_UINT32	ui32Cmd;
	IMG_UINT32	ui32TransId;
	IMG_UINT32	ui32HdrAddr;
	IMG_UINT32	ui32HdrSize;
	IMG_UINT32	ui32CtxSaveAddr;
	IMG_UINT32	ui32CtxLoadAddr;
	IMG_UINT32	ui32CtxSize;
	IMG_UINT32	ui32BufCtrlAddr;
	IMG_UINT32	ui32SeqAddr;
	IMG_UINT32	ui32PPSAddr;
	IMG_UINT32	ui32PPS2Addr;
	IMG_UINT32  ui32MemToRegAddr;
	IMG_UINT32  ui32MemToRegSize; /* 31-16: buff size, 15-0: size filled by host; dwords */
	IMG_UINT32  ui32SliceParamsAddr;
	IMG_UINT32  ui32SliceParamsSize; /* dwords */
	IMG_UINT32  ui32LastLumaRecon;
	IMG_UINT32  ui32LastChromaRecon;
	IMG_UINT32  ui32ScaledDisplaySize;
	IMG_UINT32  ui32HorzScaleControl;
	IMG_UINT32  ui32VertScaleControl;
	IMG_UINT32  ui32ScaleOutputSize;
	IMG_UINT32  ui32VlcIdxTableSize;
	IMG_UINT32  ui32VlcIdxTableAddr;
	IMG_UINT32  ui32VlcTablesSize;
	IMG_UINT32  ui32VlcTablesAddr;
	IMG_UINT32  ui32DisplayPictureSize;
	IMG_UINT32  ui32ParserMode;
	/* needed for separate colour planes */
	IMG_UINT32 ui32IntraBufBaseAddr;
	IMG_UINT32 ui32IntraBufSizePerPlane;
	IMG_UINT32 ui32Chroma2ReconstructedAddr;
	IMG_UINT32 ui32LumaAltAddr;
	IMG_UINT32 ui32ChromaAltAddr;
	IMG_UINT32 ui32Chroma2AltAddr;
	IMG_UINT32 ui32AuxLineBufferBaseAddr;
	IMG_UINT32 ui32AltOutputPictRotation;
	/* MMU Tile configuration */
	IMG_UINT32 ui32MMUTileCfg;
	IMG_UINT32 ui32MMUTileMinAddr;
	IMG_UINT32 ui32MMUTileMaxAddr;
	/* miscellaneous flags */
	struct
	{
		unsigned bChromaInterleaved	: 1;
		unsigned bMMUTiling			: 1;
		unsigned bMMUTilingScheme1	: 1;
		unsigned bPackedFormat		: 1;
	};
} VDEC_EXT_CMD;
#define CMD_VDEC_EXT_DWSIZE				   			(sizeof(VDEC_EXT_CMD)/sizeof(IMG_UINT32))
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

/*****************************************************************/
/* Completion */
/*****************************************************************/
#define CMD_COMPLETION								(0x60000000)
#define CMD_COMPLETION_DWSIZE						(1)	
/*****************************************************************/
/* Bitstream segments */
/*****************************************************************/
#define CMD_BITSTREAM_SEGMENTS						(0xD0000000)
#define CMD_BITSTREAM_SEGMENTS_MINUS1_MASK			(0x0000001F)
#define CMD_BITSTREAM_PARSE_BLK_MASK				(0x0000FF00)
#ifdef VDEC_USE_PVDEC_COMPATIBILITY
#define CMD_BITSTREAM_SEGMENTS_MORE_FOLLOW_MASK     (0x00000020)
#define CMD_BITSTREAM_BS_TOT_SIZE_WORD_OFFSET       (1)
#define CMD_BITSTREAM_BS_SEG_LIST_WORD_OFFSET       (2)
#define CMD_BITSTREAM_HDR_DW_SIZE                   CMD_BITSTREAM_BS_SEG_LIST_WORD_OFFSET
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

#ifdef VDEC_USE_PVDEC_COMPATIBILITY
/*****************************************************************/
/* Signatures */
/*****************************************************************/
/* Signature set ids (see hwSignatureModules.c for exact order). */
/* -- FRONT END/ENTROPY_PIPE ----------------------------------- */
/* Signature group 0:
 * REG(PVDEC_ENTROPY, CR_SR_SIGNATURE)
 * REG(MSVDX_VEC,     CR_SR_CRC)
 */
#define PVDEC_SIGNATURE_GROUP_0  (1<<0)
/* Signature group 1:
 * REG(PVDEC_ENTROPY, CR_HEVC_PARSER_SIGNATURE)
 * REG(PVDEC_ENTROPY, CR_ENCAP_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_1  (1<<1)
/* Signature group 2:
 * REG(PVDEC_ENTROPY, CR_GENC_ENGINE_OUTPUT_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_2  (1<<2)
/* Signature group 3:
 * REGREP(PVDEC_ENTROPY, CR_GENC_BUFFER_SIGNATURE, 0)
 * REGREP(PVDEC_ENTROPY, CR_GENC_BUFFER_SIGNATURE, 1)
 * REGREP(PVDEC_ENTROPY, CR_GENC_BUFFER_SIGNATURE, 2)
 * REGREP(PVDEC_ENTROPY, CR_GENC_BUFFER_SIGNATURE, 3)
 * REG(   PVDEC_ENTROPY, CR_GENC_FRAGMENT_SIGNATURE)
 * REG(   PVDEC_ENTROPY, CR_GENC_FRAGMENT_READ_SIGNATURE)
 * REG(   PVDEC_ENTROPY, CR_GENC_FRAGMENT_WRADDR_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_3  (1<<3)
/* -- GENC_DEC -------------------------------------------------- */
/* Signature group 4:
 * REG(   PVDEC_VEC_BE, CR_GDEC_FRAGMENT_REQ_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_GDEC_SYS_WR_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_GDEC_MEM2REG_SYS_WR_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_SLICE_STRUCTURE_REQ_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_SLICE_STRUCTURE_OVER1K_REQ_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_MEM_STRUCTURE_REQ_SIGNATURE)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_DATA_REQ_SIGNATURE, 0)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_DATA_REQ_SIGNATURE, 1)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_DATA_REQ_SIGNATURE, 2)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_DATA_REQ_SIGNATURE, 3)
 */
#define PVDEC_SIGNATURE_GROUP_4  (1<<4)
/* Signature group 5:
 * REG(   PVDEC_VEC_BE, CR_GDEC_FRAGMENT_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_SLICE_STRUCTURE_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_SLICE_STRUCTURE_OVER1K_SIGNATURE)
 * REG(   PVDEC_VEC_BE, CR_MEM_STRUCTURE_SIGNATURE)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_BUFFER_SIGNATURE, 0)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_BUFFER_SIGNATURE, 1)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_BUFFER_SIGNATURE, 2)
 * REGREP(PVDEC_VEC_BE, CR_GDEC_BUFFER_SIGNATURE, 3)
 */
#define PVDEC_SIGNATURE_GROUP_5  (1<<5)
/* -- RESIDUAL AND COMMAND DEBUG--------------------------------- */
/* Signature group 12:
 * REG(PVDEC_VEC_BE, CR_DECODE_TO_COMMAND_PRIME_SIGNATURE)
 * REG(PVDEC_VEC_BE, CR_DECODE_TO_COMMAND_SECOND_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_12  (1<<12)
/* Signature group 13:
 * REG(PVDEC_VEC_BE, CR_DECODE_TO_RESIDUAL_PRIME_SIGNATURE)
 * REG(PVDEC_VEC_BE, CR_DECODE_TO_RESIDUAL_SECOND_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_13  (1<<13)
/* Signature group 14:
 * REG(PVDEC_VEC_BE, CR_COMMAND_ABOVE_READ_SIGNATURE)
 * REG(PVDEC_VEC_BE, CR_COMMAND_ABOVE_WRITE_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_14  (1<<14)
/* Signature group 15:
 * REG(PVDEC_VEC_BE, CR_TEMPORAL_READ_SIGNATURE)
 * REG(PVDEC_VEC_BE, CR_TEMPORAL_WRITE_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_15  (1<<15)
/* --VEC--------------------------------------------------------- */
/* Signature group 16:
 * REG(PVDEC_VEC_BE, CR_COMMAND_OUTPUT_SIGNATURE)
 * REG(MSVDX_VEC,    CR_VEC_IXFORM_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_16  (1<<16)
/* Signature group 17:
 * REG(PVDEC_VEC_BE, CR_RESIDUAL_OUTPUT_SIGNATURE)
 * REG(MSVDX_VEC,    CR_VEC_COMMAND_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_17  (1<<17)
/* --VDMC-------------------------------------------------------- */
/* Signature group 18:
 * REG(MSVDX_VDMC, CR_VDMC_REFERENCE_CACHE_SIGNATURE)
 * REG(MSVDX_VDMC, CR_VDMC_REFERENCE_CACHE_MEM_WADDR_SIGNATURE)
 * REG(MSVDX_VDMC, CR_VDMC_REFERENCE_CACHE_MEM_RADDR_SIGNATURE)
 * REG(MSVDX_VDMC, CR_VDMC_REFERENCE_CACHE_MEM_WDATA_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_18  (1<<18)
/* Signature group 19:
 * REG(MSVDX_VDMC, CR_VDMC_2D_FILTER_PIPELINE_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_19  (1<<19)
/* Signature group 20:
 * REG(MSVDX_VDMC, CR_VDMC_PIXEL_RECONSTRUCTION_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_20  (1<<20)
/* Signature group 21:
 * REG(MSVDX_VDMC, CR_VDMC_MCU_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_21  (1<<21)
/* ---VDEB------------------------------------------------------- */
/* Signature group 22:
 * REG(MSVDX_VDEB, CR_VDEB_SYS_MEM_RDATA_LUMA_SIGNATURE)
 * REG(MSVDX_VDEB, CR_VDEB_SYS_MEM_RDATA_CHROMA_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_22  (1<<22)
/* Signature group 23:
 * REG(MSVDX_VDEB, CR_VDEB_SYS_MEM_ADDR_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_23  (1<<23)
/* Signature group 24:
 * REG(MSVDX_VDEB, CR_VDEB_SYS_MEM_WDATA_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_24  (1<<24)
/* ---SCALER----------------------------------------------------- */
/* Signature group 25:
 * REG(MSVDX_VDEB, CR_VDEB_SCALE_ADDR_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_25  (1<<25)
/* Signature group 26:
 * REG(MSVDX_VDEB, CR_VDEB_SCALE_WDATA_SIGNATURE)
 */
#define PVDEC_SIGNATURE_GROUP_26  (1<<26)
/* ---PICTURE CHECKSUM------------------------------------------- */
/* Signature group 27:
 * REG(MSVDX_VDEB, CR_VDEB_HEVC_CHECKSUM_LUMA)
 * REG(MSVDX_VDEB, CR_VDEB_HEVC_CHECKSUM_CB)
 * REG(MSVDX_VDEB, CR_VDEB_HEVC_CHECKSUM_CR)
 */
#define PVDEC_SIGNATURE_GROUP_27  (1<<27)
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */
#endif /* FW_INTERFACE_H_ */
