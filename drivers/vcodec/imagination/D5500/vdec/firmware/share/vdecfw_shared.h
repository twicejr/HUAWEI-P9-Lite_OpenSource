/*!
 *****************************************************************************
 *
 * @File       vdecfw_shared.h
 * @Title      Public data structures and enums for the firmware
 * @Description    Public data structures for the firmware
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


/** \defgroup FW Firmware (MSVDX)
 *  @{
 *      \defgroup FW_BASE Base
 *      @{
 *          \defgroup FW_BASE_MSVDX MSVDX
 *          @{
 *              \defgroup FW_BASE_MSVDX_CORE Core
 *              \defgroup FW_BASE_MSVDX_DMA DMA
 *              \defgroup FW_BASE_MSVDX_RENDEC RENDEC
 *              \defgroup FW_BASE_MSVDX_PERFORMANCE Performance
 *              \defgroup FW_BASE_MSVDX_SRAPI SR API
 *              \defgroup FW_BASE_MSVDX_H264SP H264 Second pass
 *          @}
 *          \defgroup FW_BASE_SERVICES Services
 *          @{
 *              \defgroup FW_BASE_SERVICES_INTAPI Interrupt API
 *              \defgroup FW_BASE_SERVICES_MEMSPCE Memory space
 *              \defgroup FW_BASE_SERVICES_REGSBASE Registers base
 *              \defgroup FW_BASE_SERVICES_RELOCAPI Relocation API
 *              \defgroup FW_BASE_SERVICES_SEMAPI Semaphores API
 *              \defgroup FW_BASE_SERVICES_SOCINTAPI SOC Int. API
 *          @}
 *          \defgroup FW_BASE_FAKEMTX Fake MTX
 *      @}
 *      \defgroup FW_PARSER Parser
 *      @{
 *          \defgroup FW_PARSER_AVS AVS
 *          \defgroup FW_PARSER_H264 H264
 *          \defgroup FW_PARSER_HEVC HEVC
 *          \defgroup FW_PARSER_JPEG JPEG
 *          \defgroup FW_PARSER_MPEG2 MPEG2
 *          \defgroup FW_PARSER_MPEG4 MPEG4
 *          \defgroup FW_PARSER_REAL REAL
 *          \defgroup FW_PARSER_VC1 VC1
 *          \defgroup FW_PARSER_VP6 VP6
 *          \defgroup FW_PARSER_VP8 VP8
 *      @}
 *  @}
 */

/** \addtogroup FW
 *  @{
 */

#ifdef USE_SHARING
#endif

#ifndef _VDECFW_H_
#define _VDECFW_H_

#include "vdecfw_share.h"

#include "img_include.h"
#ifndef VDEC_USE_PVDEC_COMPATIBILITY
#include "vdec.h"
#include "msvdx_core_regs_io2.h"
#else /* VDEC_USE_PVDEC_COMPATIBILITY */
#include "hwdefs/msvdx_core_regs.h"
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */


#ifndef VDEC_USE_PVDEC_COMPATIBILITY
/*! Comms header size - x3 32bit words in bytes */
#define VDECFW_COMMS_HEADER_SIZE (3 * 4)

/*! Control comms buffer size in 32-bit words */
#define VDECFW_CONTROL_COMMS_BUF_SIZE       ((VLR_CONTROL_COMMS_AREA_SIZE - VDECFW_COMMS_HEADER_SIZE) / 4)
/*! Decode comms buffer size in 32-bit words */
#define VDECFW_DECODE_COMMS_BUF_SIZE        ((VLR_DECODE_COMMS_AREA_SIZE - VDECFW_COMMS_HEADER_SIZE) / 4)
/*! Completion comms buffer size in 32-bit words */
#define VDECFW_COMPLETION_COMMS_BUF_SIZE    ((VLR_COMPLETION_COMMS_AREA_SIZE - VDECFW_COMMS_HEADER_SIZE) / 4)
/*! Page Table Directory area size in 32-bit words */
#define VDECFW_PAGE_TABLE_DIRECTORY_SIZE    (VLR_PAGE_TABLE_DIRECTORY_SIZE/4)

#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

/*! Number of scaling coefficients */
#define VDECFW_NUM_SCALE_COEFFS 4

/*! maximum number of pictures handled by the firmware
 * for H.264 (largest requirement): 32 for 4 view MVC */
#define VDECFW_MAX_NUM_PICTURES 32
#define VDECFW_MAX_NUM_VIEWS 4
#define EMERALD_CORE    6

/* Maximum number of colour planes. */
#define VDECFW_PLANE_MAX 4


#define NO_VALUE    0

/*! Indicates whether a cyclic sequence number (x) has reached another (y). */
#define HAS_X_REACHED_Y(x, y, range) ((((x)-(y) + (range)) % (range)) <= (((y)-(x) + (range)) % (range))) ? IMG_TRUE : IMG_FALSE

/*! Indicates whether a cyclic sequence number (x) has passed another (y). */
#define HAS_X_PASSED_Y(x, y, range)  ((((x)-(y) + (range)) % (range)) < (((y)-(x) + (range)) % (range))) ? IMG_TRUE : IMG_FALSE

#define FWIF_BIT_MASK(num)                      ((1 << num) - 1)

/*! Number of bits in transaction ID used to represent picture number in stream. */
#define FWIF_NUMBITS_STREAM_PICTURE_ID          16
/*! Number of bits in transaction ID used to represent picture number in core. */
#define FWIF_NUMBITS_CORE_PICTURE_ID            4
/*! Number of bits in transaction ID used to represent stream id. */
#define FWIF_NUMBITS_STREAM_ID                  8
/*! Number of bits in transaction ID used to represent core id. */
#define FWIF_NUMBITS_CORE_ID                    4

/*! Offset in transaction ID to picture number in stream. */
#define FWIF_OFFSET_STREAM_PICTURE_ID           0
/*! Offset in transaction ID to picture number in core. */
#define FWIF_OFFSET_CORE_PICTURE_ID             (FWIF_OFFSET_STREAM_PICTURE_ID + FWIF_NUMBITS_STREAM_PICTURE_ID)
/*! Offset in transaction ID to stream id. */
#define FWIF_OFFSET_STREAM_ID                   (FWIF_OFFSET_CORE_PICTURE_ID + FWIF_NUMBITS_CORE_PICTURE_ID)
/*! Offset in transaction ID to core id. */
#define FWIF_OFFSET_CORE_ID                     (FWIF_OFFSET_STREAM_ID + FWIF_NUMBITS_STREAM_ID)

/*! Picture id (stream) from transaction id. */
#define GET_STREAM_PICTURE_ID(transaction_id)       (transaction_id & FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_PICTURE_ID))
/*! Picture id (core) from transaction id. */
#define GET_CORE_PICTURE_ID(transaction_id)         ((transaction_id >> FWIF_OFFSET_CORE_PICTURE_ID) & FWIF_BIT_MASK(FWIF_NUMBITS_CORE_PICTURE_ID))
/*! Stream id from transaction id. */
#define GET_STREAM_ID(transaction_id)               ((transaction_id >> FWIF_OFFSET_STREAM_ID) & FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_ID))
/*! Core id from transaction id. */
#define GET_CORE_ID(transaction_id)                 ((transaction_id >> FWIF_OFFSET_CORE_ID) & FWIF_BIT_MASK(FWIF_NUMBITS_CORE_ID))

/*! Picture id (stream) for transaction id. */
#define SET_STREAM_PICTURE_ID(str_pic_id)           ((str_pic_id & FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_PICTURE_ID)) << FWIF_OFFSET_STREAM_PICTURE_ID)
/*! Picture id (core) for transaction id. */
#define SET_CORE_PICTURE_ID(core_pic_id)            ((core_pic_id % (1<<FWIF_NUMBITS_CORE_PICTURE_ID)) << FWIF_OFFSET_CORE_PICTURE_ID)
/*! Stream id for transaction id. */
#define SET_STREAM_ID(stream_id)                    ((stream_id & FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_ID)) << FWIF_OFFSET_STREAM_ID)
/*! Core id for transaction id. */
#define SET_CORE_ID(core_id)                        ((core_id & FWIF_BIT_MASK(FWIF_NUMBITS_CORE_ID)) << FWIF_OFFSET_CORE_ID)

#define CREATE_TRANSACTION_ID(core_id, stream_id, core_pic, stream_pic) \
              SET_CORE_ID(core_id) | SET_STREAM_ID(stream_id) | SET_CORE_PICTURE_ID(core_pic) | SET_STREAM_PICTURE_ID(stream_pic)

/* flag checking */
#define FLAG_MASK(_flagname_)                   ((1 << _flagname_##_SHIFT))
#define FLAG_IS_SET(_flagsword_, _flagname_)    ( (_flagsword_ & FLAG_MASK(_flagname_))? IMG_TRUE: IMG_FALSE )
#ifndef VDEC_USE_PVDEC_COMPATIBILITY

#ifndef USE_SHARING
/*!
******************************************************************************
 Additional types for integer pointers in shared data structures.
 NOTE: This part is copied from vdecfw_share.h to be able to compile
       without sharing being used.
******************************************************************************/
#ifdef __FAKE_MTX_INTERFACE__
typedef IMG_UINT64  VDECFW_SHARED_UINTPTR; /* If FakeMTX is compiled in always assume the worst case of having 64-bit shared pointers. */
#else /* not __FAKE_MTX_INTERFACE__ */
typedef IMG_UINT32  VDECFW_SHARED_UINTPTR; /* If FakeMTX is not compiled in 32-bit shared pointers are sufficient. */
#endif /* not __FAKE_MTX_INTERFACE__ */
#endif /* USE_SHARING */

typedef enum
{
    VDECFW_UNIT_HEADER = 0,
    VDECFW_UNIT_CONTEXT,
    VDECFW_UNIT_CONTROL

} VDECFW_eUnitType;

#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

/*!
******************************************************************************

 This type defines the parser component types

******************************************************************************/
typedef enum
{
    VDECFW_CODEC_H264 = 0,  //!< H.264, AVC, MVC
    VDECFW_CODEC_MPEG4,     //!< MPEG4, H.263, DivX, Sorenson
    VDECFW_CODEC_VP8,       //!< VP8

    VDECFW_CODEC_VC1,       //!< VC1 (includes WMV9)
    VDECFW_CODEC_MPEG2,     //!< MPEG2

    VDECFW_CODEC_JPEG,      //!< JPEG

    VDECFW_CODEC_VP6,       //!< VP6
    VDECFW_CODEC_AVS,       //!< AVS
    VDECFW_CODEC_RV,        //!< RV30, RV40

    VDECFW_CODEC_HEVC,      //!< HEVC/H265

    VDECFW_CODEC_MAX,       //!< End Marker

    VDEC_CODEC_NONE = -1,   //!< No codec

} VDECFW_eCodecType;


/*!
******************************************************************************

 This type defines the FW parser mode - SCP, size delimited, etc.

******************************************************************************/
typedef enum
{
    VDECFW_SCP_ONLY = 0,            //!< Every NAL is expected to have SCP
    VDECFW_SIZE_DELIMITED_4_ONLY,   //!< Every NAL is expect to be size delimited with field size 4
    VDECFW_SIZE_DELIMITED_2_ONLY,   //!< Every NAL is expect to be size delimited with field size 2
    VDECFW_SIZE_DELIMITED_1_ONLY,   //!< Every NAL is expect to be size delimited with field size 1
    VDECFW_SIZE_SIDEBAND,           //!< Size of NAL is provided in the picture header
    VDECFW_SKIPPED_PICTURE,         //!< Unit is a skipped picture with no data to process

} VDECFW_eParserMode;


/*!
******************************************************************************
 This enum defines values of ENTDEC_BE_MODE field of VEC_ENTDEC_BE_CONTROL
 register and ENTDEC_FE_MODE field of VEC_ENTDEC_FE_CONTROL register.
*****************************************************************************/
typedef enum
{
    VDECFW_ENTDEC_MODE_JPEG        = 0x0,    //!< JPEG
    VDECFW_ENTDEC_MODE_H264        = 0x1,    //!< H264 (MPEG4/AVC)
    VDECFW_ENTDEC_MODE_VC1         = 0x2,    //!< VC1
    VDECFW_ENTDEC_MODE_MPEG2       = 0x3,    //!< MPEG2
    VDECFW_ENTDEC_MODE_MPEG4       = 0x4,    //!< MPEG4
    VDECFW_ENTDEC_MODE_AVS         = 0x5,    //!< AVS
    VDECFW_ENTDEC_MODE_WMV9        = 0x6,    //!< WMV9
    VDECFW_ENTDEC_MODE_MPEG1       = 0x7,    //!< MPEG1
    VDECFW_ENTDEC_MODE_EXT_REAL8   = 0x0,    //!< RealVideo8, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDECFW_ENTDEC_MODE_EXT_REAL9   = 0x1,    //!< RealVideo9, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDECFW_ENTDEC_MODE_EXT_VP6     = 0x2,    //!< VP6, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDECFW_ENTDEC_MODE_EXT_VP8     = 0x3,    //!< VP8, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDECFW_ENTDEC_MODE_EXT_SVC     = 0x4,    //!< SVC, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set

} VDECFW_eMsvdxEntDecMode;


/*!
******************************************************************************

 This describes the Firmware Parser checkpoints in VEC Local RAM.
 Each checkpoint is updated with the TransactionID of the picture as it passes
 that point in its decode. Togther they describe the current position of
 pictures in the VXD/Firmware pipeline.

 Numbers indicate point in the "VDEC Firmware Component Timing" diagram.

******************************************************************************/
typedef enum
{
    VDECFW_CHECKPOINT_PICTURE_STARTED     = 1,  //!< Decode message has been read

    VDECFW_CHECKPOINT_FIRMWARE_READY      = 2,  //!< Firmware has been loaded and bitstream DMA started
    VDECFW_CHECKPOINT_SYNC_COMPLETE       = 3,  //!< Firmware has been synchronised on front-end with the previous picture
    VDECFW_CHECKPOINT_PICMAN_COMPLETE     = 4,  //!< Picture management operations have completed
    VDECFW_CHECKPOINT_FIRMWARE_SAVED      = 5,  //!< Firmware context for this picture has been saved

    VDECFW_CHECKPOINT_ENTDEC_STARTED      = 6,  //!< 1st Picture/Slice header has been read, registers written and Entdec started
    VDECFW_CHECKPOINT_FE_1SLICE_DONE      = 7,  //!< 1st Slice has been completed by Entdec
    VDECFW_CHECKPOINT_FE_PARSE_DONE       = 8,  //!< Parsing of picture has completed on FE
    VDECFW_CHECKPOINT_FE_PICTURE_COMPLETE = 9,  //!< Picture end code has been read and picture closed

    VDECFW_CHECKPOINT_BE_PICTURE_STARTED  = 10,  //!< Picture has started decoding on VXD Backend
    VDECFW_CHECKPOINT_BE_1SLICE_DONE      = 11, //!< 1st Slice has completed on VXD Backend
    VDECFW_CHECKPOINT_BE_PICTURE_COMPLETE = 12, //!< Picture decode has completed and done message sent to the Host

	VDECFW_CHECKPOINT_FI_INIT_START       = 13, //!< Firmware is started
    VDECFW_CHECKPOINT_FI_INIT_END         = 14, //!< Firmware has completed the initialisation successfully
    VDECFW_CHECKPOINT_FI_POST_MSG         = 15, //!< Firmware has received the first POST message
    VDECFW_CHECKPOINT_MAX,

    // Indicate which checkpoints mark the start and end of each group (FW, FE and BE).
    // before the current start or after the current end of any group.
    VDECFW_CHECKPOINT_FW_START = VDECFW_CHECKPOINT_PICTURE_STARTED,
    VDECFW_CHECKPOINT_FW_END   = VDECFW_CHECKPOINT_FIRMWARE_SAVED,
    VDECFW_CHECKPOINT_FE_START = VDECFW_CHECKPOINT_ENTDEC_STARTED,
    VDECFW_CHECKPOINT_FE_END   = VDECFW_CHECKPOINT_FE_PICTURE_COMPLETE,
    VDECFW_CHECKPOINT_BE_START = VDECFW_CHECKPOINT_BE_PICTURE_STARTED,
    VDECFW_CHECKPOINT_BE_END   = VDECFW_CHECKPOINT_BE_PICTURE_COMPLETE,

	VDECFW_CHECKPOINT_FI_START = VDECFW_CHECKPOINT_FI_INIT_START,
    VDECFW_CHECKPOINT_FI_END   = VDECFW_CHECKPOINT_FI_POST_MSG,
} VDECFW_eProgressCheckPoint;

#define NUM_OF_FW_INIT_CHECKPOINTS		((VDECFW_CHECKPOINT_FI_END - VDECFW_CHECKPOINT_FI_START) + 1)
#define CHKPNT_HOST_HIGHER_MASK_VALUE	((IMG_UINT32)0xADADAD00)
#define CHKPNT_FW_VALUE					((IMG_UINT32)0xCBCBCBCB)


/*!
******************************************************************************

 This describes the action currently being done by the Firmware.

******************************************************************************/
typedef enum
{
    VDECFW_FWACT_IDLE = 1,            //!< Firmware is currently doing nothing

    VDECFW_FWACT_BASE_LOADING_PSR,    //!< Loading parser context
    VDECFW_FWACT_BASE_SAVING_PSR,     //!< Saving parser context
    VDECFW_FWACT_BASE_LOADING_BEMOD,  //!< Loading Backend module
    VDECFW_FWACT_BASE_LOADING_FEMOD,  //!< Loading Frontend module

    VDECFW_FWACT_PARSER_SLICE,        //!< Parser active: parsing slice
    VDECFW_FWACT_PARSER_PM,           //!< Parser active: picture management

    VDECFE_FWACT_BEMOD_ACTIVE,        //!< Backend module active
    VDECFE_FWACT_FEMOD_ACTIVE,        //!< Frontend module active
#ifdef USE_MTX_BREAK_TRAP
    VDECFE_FWACT_BREAK_TRAP,          //!< Executing NOP loop, so MTX breakpoints can be set
#endif /* USE_MTX_BREAK_TRAP */

    VDECFW_FWACT_MAX,

} VDECFW_eFirmwareAction;

#ifndef VDEC_USE_PVDEC_COMPATIBILITY

/*!
******************************************************************************

 This describes Firmware config message types

******************************************************************************/
typedef enum
{
    VDECFW_CONFIG_RENDEC = 1,       //!< Rendec base addresses and sizes
    VDECFW_CONFIG_TIMEOUTS,         //!< Watchdog timeouts
    VDECFW_CONFIG_COREID,           //!< Core ID when used in multi-core mode

    VDECFW_CONFIG_MAX,

} VDECFW_eConfig;


/*!
******************************************************************************

 This describes Firmware control message types

******************************************************************************/
typedef enum
{
    VDECFW_CONTROL_STOP = 1,        //!< Stop a stream immediately
    VDECFW_CONTROL_CRCS,            //!< Turn CRC reporting on or off
    VDECFW_CONTROL_PERF,            //!< Turn performance reporting on or off

	VDECFW_CONTROL_POST,			//!< Start POST calculation test
    VDECFW_CONTROL_MAX,

} VDECFW_eControl;
typedef enum
{
	VDECFW_POST_FIRST_CMD
   ,VDECFW_POST_NO_CMD = VDECFW_POST_FIRST_CMD
   ,VDECFW_POST_FIRST_MSG
   ,VDECFW_POST_START_CALC
   ,VDECFW_POST_GET_INIT_RES
   ,VDECFW_POST_STOP
   ,VDECFW_POST_LAST_CMD = VDECFW_POST_STOP
} VDECFW_ePOSTCommand;


/*!
******************************************************************************

 This describes the flags word in the VDECFW_MSGID_BITSTREAM_BUFFER message

******************************************************************************/
typedef enum
{
    VDECFW_MSGFLAG_BUFFER_LAST_SHIFT = 0,  //!< Buffer is the last for the picture and contains a codec specific end marker
    VDECFW_MSGFLAG_BUFFER_MAX,

} VDECFW_eMsgFlagBuffer;


/*!
******************************************************************************

 This describes the flags word in the VDECFW_MSGID_FENCE message

******************************************************************************/
typedef enum
{
    VDECFW_MSGFLAG_FENCE_INT_SHIFT = 0,  //!< Raise an interrupt for this fence
    VDECFW_MSGFLAG_FENCE_MAX,

} VDECFW_eMsgFlagFence;


/*!
******************************************************************************

 This describes the flags word in the VDECFW_MSGID_BATCH message

******************************************************************************/
typedef enum
{
    VDECFW_MSGFLAG_BATCH_MAX,

} VDECFW_eMsgFlagBatch;


/*!
******************************************************************************

 This describes the flags word in the VDECFW_MSGID_PIC_DECODED message

******************************************************************************/
typedef enum
{
    VDECFW_MSGFLAG_DECODED_ABORTED_SHIFT = 0,   //!< Picture was aborted in some way.
    VDECFW_MSGFLAG_DECODED_DISCONTINUOUS_SHIFT, //!< Picture contained discontinous macroblocks
    VDECFW_MSGFLAG_DECODED_MAX,

} VDECFW_eMsgFlagDecoded;


/*!
******************************************************************************

 This describes the flags word in the VDECFW_MSGID_PIC_PERFORMANCE message

******************************************************************************/
typedef enum
{
    VDECFW_MSGFLAG_PERFORMANCE_FIELDPIC_SHIFT = 0,   //!< Picture is a field
    VDECFW_MSGFLAG_PERFORMANCE_MAX,

} VDECFW_eMsgFlagPerfomance;

#endif /* DEC_USE_PVDEC_COMPATIBILITY */

/*!
******************************************************************************

 This describes the FE_ERR flags word in the VDECFW_MSGID_PIC_DECODED message

******************************************************************************/
typedef enum
{
    VDECFW_MSGFLAG_DECODED_FEERROR_SRUNEXPECTEDSCPOREOD_SHIFT = 0,  //!< SR encountered unexpected SCP or end of data
    VDECFW_MSGFLAG_DECODED_FEERROR_SRUNEXPECTEDEXPGOULOMB_SHIFT,    //!< SR encountered unexpected exponential goublomb
    VDECFW_MSGFLAG_DECODED_FEERROR_PSRFATALSYNTAXERROR_SHIFT,       //!< PSR encountered fatal syntax error
    VDECFW_MSGFLAG_DECODED_FEERROR_SRERROR_FW_PARSING_SHIFT,        //!< Shift-register error while firmware parsing headers
    VDECFW_MSGFLAG_DECODED_FEERROR_PSRWDT_SHIFT,                    //!< PSR watchdog timeout
    VDECFW_MSGFLAG_DECODED_FEERROR_HWWDT_SHIFT,                     //!< Front-end hardware watchdog timeout (FE_WDT_CM0)
    VDECFW_MSGFLAG_DECODED_FEERROR_ENTDECERROR_SHIFT,               //!< Front-end entdec error (VEC_ERROR_DETECTED_ENTDEC)
    VDECFW_MSGFLAG_DECODED_FEERROR_SRERROR_SHIFT,                   //!< Shift-register error (VEC_ERROR_DETECTED_SR)
    VDECFW_MSGFLAG_DECODED_FEERROR_FW_PARSING_SEQ_ERROR_SHIFT,      //!< Error in normal firmware sequence (firmware is expected to do certaing things like
                                                                    //   parsing, write registers, picture managemnt etc at least once for each picture. If
                                                                    //   this does not happen for a picture there is error handling code after the parsing loop
                                                                    //   that will compensate for this and flag this error.
    VDECFW_MSGFLAG_DECODED_MISSING_REFERENCES_SHIFT,                //!< For cases when B frame comes after I without P.

    VDECFW_MSGFLAG_DECODED_BEERROR_HWWDT_SHIFT,                     //!< Back-end WDT timeout

    VDECFW_MSGFLAG_DECODED_FEERROR_MAX,

} VDECFW_eMsgFlagDecodedFeError;


/*!
******************************************************************************

 This type defines the IDs of the messages used to communicate with the
 Firmware.

 The Firmware has 3 message buffers, each buffer uses a different set of IDs.
 The buffers are:
    Host -> FW - Control messages (High Priority: processed in interrupt context)
    Host -> FW - Decode commands and associated information (Normal Priority: processed in baseloop)
    FW -> Host - Completion message

******************************************************************************/
typedef enum
{
    /* Control Messages */

    VDECFW_MSGID_BASE_PADDING = 0x01,   /*!< Host -> FW Padding message
                                            Sent to optionally pad the message buffer */

    VDECFW_MSGID_FIRMWARE_INIT,         /*!< Host -> FW Initialisation message
                                            Initialisation should be sent *immediately* after loading the base component
                                            ie. while the FW is idle */

    VDECFW_MSGID_FIRMWARE_CONFIG,       /*!< Host -> FW Configuration message
                                            Configuration should be setup after loading the base component
                                            and before decoding the next picture ie. while the FW is idle */

    VDECFW_MSGID_FIRMWARE_CONTROL,      /*!< Host -> FW Control message
                                            Firmware control command to have immediate affect
                                            eg. Stop stream, return CRCs, return Performance Data */
    VDECFW_MSGID_CONTROL_MAX,

    /* Decode Commands */

    VDECFW_MSGID_PSR_PADDING = 0x40,    /*!< Host -> FW Padding message
                                            Sent to optionally pad the message buffer */

    VDECFW_MSGID_DECODE_PICTURE,        /*!< Host -> FW Decode message
                                            Describes the picture to decode */

    VDECFW_MSGID_BITSTREAM_BUFFER,      /*!< Host -> FW Bitstream buffer information
                                            Information describing a bitstream buffer to DMA to VXD */

    VDECFW_MSGID_FENCE,                 /*!< Host -> FW Fence message
                                            Generate an interrupt when this is read,
                                            FenceID should be written to a location in VLR */

    VDECFW_MSGID_BATCH,                 /*!< Host -> FW Batch message
                                            Contains a pointer to a host memory buffer
                                            containing a batch of decode command FW messages */
    VDECFW_MSGID_DECODE_MAX,

    /* Completion Messages */

    VDECFW_MSGID_BE_PADDING = 0x80,     /*!< FW -> Host Padding message
                                            Sent to optionally pad the message buffer */

    VDECFW_MSGID_PIC_DECODED,           /*!< FW -> Host Decoded Picture message
                                            Notification of decoded picture including errors recorded */

    VDECFW_MSGID_PIC_CRCS,              /*!< FW -> Host CRC message
                                            Optionally sent with Decoded Picture message, contains VXD CRCs*/

    VDECFW_MSGID_PIC_PERFORMANCE,       /*!< FW -> Host Performance message
                                            Optional timestamps at the decode checkpoints and other information
                                            about the image to assist in measuring performance */
	VDECFW_MSGID_PIC_POST_RESP,			/*!< FW -> Host POST calculation test message */
    VDECFW_MSGID_COMPLETION_MAX,

} VDECFW_eMessageID;

#define VDECFW_MSGID_CONTROL_TYPES (VDECFW_MSGID_CONTROL_MAX-VDECFW_MSGID_BASE_PADDING)
#define VDECFW_MSGID_DECODE_TYPES (VDECFW_MSGID_DECODE_MAX-VDECFW_MSGID_PSR_PADDING)
#define VDECFW_MSGID_COMPLETION_TYPES (VDECFW_MSGID_COMPLETION_MAX-VDECFW_MSGID_BE_PADDING)

#ifndef VDEC_USE_PVDEC_COMPATIBILITY
/*!
******************************************************************************

 This describes the layout of Firmware state indicators in VEC Local RAM

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32CheckPoint[VDECFW_CHECKPOINT_MAX]); //!< TransactionID at each checkpoint
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, eFirmwareAction);                        //!< VDECFW_eFirmwareAction (UINT32 used to guarantee size)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FenceValue);                         //!< Value in the FENCE field of the FENCEMSG
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8CurCodec);                            //!< VDECFW_eCodecType - Codec currently loaded
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FESlices);                           //!< Number of FE Slices processed for the last picture in FE
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BESlices);                           //!< Number of BE Slices processed for the last picture in BE

    //!< FenceID of last message processed in the control message buffer
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8ControlFenceID[VDECFW_MSGID_CONTROL_TYPES]);

    //!< FenceID of last message processed in the decode message buffer
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8DecodeFenceID[VDECFW_MSGID_DECODE_TYPES]);

    //!< FenceID of last message processed in the completion message buffer
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8CompletionFenceID[VDECFW_MSGID_COMPLETION_TYPES]);

    //!< KEEP ALWAYS LAST IN THIS STRUCTURE, DO NOT MODIFY THE ORDER
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DebugTransferRequest);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DebugTransferAcknowledged);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DebugTransferData1);

} VDECFW_sFirmwareState;
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */


/*****************************************************************************
 This describes the layout of PVDEC Firmware state indicators in Comms RAM.
******************************************************************************/
/* Maximum number of PVDEC decoding pipes per core supported. */
#define VDECFW_MAX_DP  2

typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32CheckPoint[VDECFW_CHECKPOINT_MAX]); //!< TransactionID at each checkpoint
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, eFirmwareAction);                        //!< VDECFW_eFirmwareAction (UINT32 used to guarantee size)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FenceValue);                         //!< Value in the FENCE field of the FENCEMSG
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FESlices);                           //!< Number of FE Slices processed for the last picture in FE
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BESlices);                           //!< Number of BE Slices processed for the last picture in BE
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8CurCodec);                            //!< VDECFW_eCodecType - Codec currently loaded
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPipePresent);                           //!< IMG_TRUE if this pipe is available for processing

} VDECFW_sPVDECPipeState;

typedef struct
{
    //!< FenceID of last message processed in the control message buffer
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8ControlFenceID[VDECFW_MSGID_CONTROL_TYPES]);
    //!< FenceID of last message processed in the decode message buffer
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8DecodeFenceID[VDECFW_MSGID_DECODE_TYPES]);
    //!< FenceID of last message processed in the completion message buffer
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8CompletionFenceID[VDECFW_MSGID_COMPLETION_TYPES]);
    //!< Pipe state array.
    VDECFW_sPVDECPipeState asPipeState[VDECFW_MAX_DP];

} VDECFW_sPVDECFirmwareState;

#ifndef VDEC_USE_PVDEC_COMPATIBILITY

/*!
******************************************************************************

 Common comms header definition for comms areas.

 ******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BufSize);   //!< Buffer size (in 32-bit words)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RdIndex);   //!< Buffer read index (in 32-bit words)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32WrtIndex);  //!< Buffer write index (in 32-bit words)

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32Buf[1]);   //!< Buffer start.

} VDECFW_sCommsHeader;


/*!
******************************************************************************

 This type defines the control comms area

 ******************************************************************************/
typedef struct
{
    VDECFW_sCommsHeader sHeader;    //!< Header and start of control message buffer.
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32BufRem[VDECFW_CONTROL_COMMS_BUF_SIZE - 1]);      //!< Remainder control message buffer.

} VDECFW_sCommsControl;


/*!
******************************************************************************

 This type defines the decode comms area

 ******************************************************************************/
typedef struct
{
    VDECFW_sCommsHeader sHeader;    //!< Header and start of decode message buffer.
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32BufRem[VDECFW_DECODE_COMMS_BUF_SIZE - 1]);       //!< Remainder decode message buffer.

} VDECFW_sCommsDecode;


/*!
******************************************************************************

 This type defines the completion comms area

 ******************************************************************************/
typedef struct
{
    VDECFW_sCommsHeader sHeader;    //!< Header and start of completion message buffer.
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32BufRem[VDECFW_COMPLETION_COMMS_BUF_SIZE - 1]);   //!< Remainder completion message buffer.

} VDECFW_sCommsCompletion;

#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

/*!
******************************************************************************

 This describes the flags word in the aui8DisplayFlags in VDECFW_sBufferControl

******************************************************************************/
typedef enum
{
    VDECFW_BUFFLAG_DISPLAY_NODISPLAY_SHIFT          = 0, //!< TID has been flushed with a "no display" indication
    VDECFW_BUFFLAG_DISPLAY_SINGLE_FIELD_SHIFT       = 1, //!< TID contains an unpaired field
    VDECFW_BUFFLAG_DISPLAY_FIELD_CODED_SHIFT        = 2, //!< TID contains field coded picture(s) - single field or pair
    VDECFW_BUFFLAG_DISPLAY_BOTTOM_FIELD_SHIFT       = 3, //!< if TID contains a single field, this defines which field that is
    VDECFW_BUFFLAG_DISPLAY_MAX                      = 8  //!< End marker

} VDECFW_eBufFlagDisplay;


/*!
******************************************************************************

 This describes the flags in the ui8PictMgmtFlags field in VDECFW_sBufferControl

******************************************************************************/
typedef enum
{
    VDECFW_PICMGMTFLAG_PICTURE_EXECUTED_SHIFT    = 0, //!< Picture management for this picture successfully executed
    VDECFW_PICMGMTFLAG_1ST_FIELD_EXECUTED_SHIFT  = 0, //!< Picture management for the first field of this picture successfully executed
    VDECFW_PICMGMTFLAG_2ND_FIELD_EXECUTED_SHIFT  = 1, //!< Picture management for the second field of this picture successfully executed

} VDECFW_ePictMgmtFlags;
/*! Macro for checking if picture management was successfully executed for field coded picture */
#define VDECFW_PICMGMT_FIELD_CODED_PICTURE_EXECUTED(_flagsword_) \
            ((FLAG_IS_SET(psBufferControl->ui8PictMgmtFlags, VDECFW_PICMGMTFLAG_1ST_FIELD_EXECUTED) && \
              FLAG_IS_SET(psBufferControl->ui8PictMgmtFlags, VDECFW_PICMGMTFLAG_2ND_FIELD_EXECUTED)) ? \
             IMG_TRUE : IMG_FALSE)


/*!
******************************************************************************

 This describes the buffer control structure that is used by the firmware to
 signal to the Host to control the display and release of buffers.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32DisplayList[VDECFW_MAX_NUM_PICTURES]);   //!< List of TransactionIDs indicating buffers ready to display, in display order
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32ReleaseList[VDECFW_MAX_NUM_PICTURES + VDECFW_MAX_NUM_VIEWS]);  //!< List of TransactionIDs indicating buffers that are no longer required for reference
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, aui8DisplayViewIds[VDECFW_MAX_NUM_PICTURES]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8DisplayFlags[VDECFW_MAX_NUM_PICTURES]);   //!< List of flags for each TID in the DisplayList
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DisplayListLength);                       //!< Number of TransactionIDs in aui32DisplayList
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32ReleaseListLength);                       //!< Number of TransactionIDs in aui32ReleaseList
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Width);                                   //!< Picture width (used by REAL)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Height);                                  //!< Picture height (used by REAL)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32ScaleWidth);                              //!< Scaled Picture Width (used by REAL)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32ScaleHeight);                             //!< Scaled Picture Height (used by REAL)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_eBufferType, eDecPictType);                            //!< Refers to the picture decoded with the current transaction ID (not affected by merge with field of previous transaction ID)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, b2ndFieldOfPair);                             //!< Set if the current field is a pair to the previous field
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, bTopFieldFirst);                              //!< Set if for a pair we decoded first the top field or if we have only top field
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8PictMgmtFlags);                            //!< Picture management flags for this picture
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TimeStamp);                               //!< timestamp parsed in firmware (used by REAL)

} VDECFW_sBufferControl;


/*!
******************************************************************************

 This describes an image buffer for one picture supplied to the firmware by the host

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32ByteOffset[VDECFW_PLANE_MAX]);  //!< Virtual Address of each plane

} VDECFW_sImageBuffer;


/*!
******************************************************************************

 This type defines the picture commands that are prepared for the firmware.

******************************************************************************/
typedef enum
{
    /* Reconstructed buffer */
    VDECFW_CMD_DISPLAY_PICTURE,                             /*!< DISPLAY_PICTURE_SIZE                           */
    VDECFW_CMD_CODED_PICTURE,                               /*!< CODED_PICTURE_SIZE                             */
    VDECFW_CMD_OPERATING_MODE,                              /*!< OPERATING_MODE                                 */

    VDECFW_CMD_LUMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS,     /*!< LUMA_RECONSTRUCTED_PICTURE_BASE_ADDRESSES      */
    VDECFW_CMD_CHROMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS,   /*!< CHROMA_RECONSTRUCTED_PICTURE_BASE_ADDRESSES    */
    VDECFW_CMD_CHROMA2_RECONSTRUCTED_PICTURE_BASE_ADDRESS,  /*!< CHROMA2_RECONSTRUCTED_PICTURE_BASE_ADDRESSES   */

    VDECFW_CMD_LUMA_ALTERNATIVE_PICTURE_BASE_ADDRESS,       /*!< VC1_LUMA_RANGE_MAPPING_BASE_ADDRESS            */
    VDECFW_CMD_CHROMA_ALTERNATIVE_PICTURE_BASE_ADDRESS,     /*!< VC1_CHROMA_RANGE_MAPPING_BASE_ADDRESS          */
    VDECFW_CMD_CHROMA2_ALTERNATIVE_PICTURE_BASE_ADDRESS,    /*!< CHROMA2_ALTERNATIVE_PICTURE_BASE_ADDRESS       */

    VDECFW_CMD_AUX_MSB_BUFFER,                              /*!< AUX_MSB_BUFFER_BASE_ADDRESSES (VC-1 only)      */
    VDECFW_CMD_INTRA_BUFFER_BASE_ADDRESS,                   /*!< INTRA_BUFFER_BASE_ADDRESS (various)            */
    VDECFW_CMD_AUX_LINE_BUFFER_BASE_ADDRESS,                /*!< AUX_LINE_BUFFER_BASE_ADDRESS                   */

    VDECFW_CMD_MBFLAGS_BUFFER_BASE_ADDRESS,                 /*!< MBFLAGS_BUFFER_BASE_ADDRESSES (VP8 only)       */
    VDECFW_CMD_FIRST_PARTITION_BUFFER_BASE_ADDRESS,         /*!< FIRST_PARTITION_BASE_ADDRESSES (VP8 only)      */
    VDECFW_CMD_CURRENT_PICTURE_BUFFER_BASE_ADDRESS,         /*!< CURRENT_PICTURE_BUFFER_BASE_ADDRESSES (VP8 only)*/
    VDECFW_CMD_SEGMENTID_BASE_ADDRESS,                      /*!< SEGMENTID_BUFFER_BASE_ADDRESSES (VP8 only)     */

    VDECFW_CMD_EXT_OP_MODE,                                 /*!< EXT_OP_MODE (H.264 only)                       */
    VDECFW_CMD_MC_CACHE_CONFIGURATION,                      /*!< MC_CACHE_CONFIGURATION                         */

    /* Alternative output buffer (rotation etc.) */
    VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION,         /*!< ALTERNATIVE_OUTPUT_PICTURE_ROTATION            */
    VDECFW_CMD_EXTENDED_ROW_STRIDE,                         /*!< EXTENDED_ROW_STRIDE                            */
    VDECFW_CMD_CHROMA_ROW_STRIDE,                           /*!< CHROMA_ROW_STRIDE (H.264 only)                 */
    VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL,                  /*!< ALTERNATIVE_OUTPUT_CONTROL                     */

    /* RPR specific commands */
    VDECFW_CMD_RPR_AX_INITIAL,                              /*!< RPR_AX_INITIAL                                 */
    VDECFW_CMD_RPR_AX_INCREMENT,                            /*!< RPR_AX_INCREMENT                               */
    VDECFW_CMD_RPR_AY_INITIAL,                              /*!< RPR_AY_INITIAL                                 */
    VDECFW_CMD_RPR_AY_INCREMENT,                            /*!< RPR_AY_INCREMENT                               */
    VDECFW_CMD_RPR_PICTURE_SIZE,                            /*!< RPR_PICTURE_SIZE                               */

    /* Scaling specific params */
    VDECFW_CMD_SCALED_DISPLAY_SIZE,                         /*!< SCALED_DISPLAY_SIZE                            */
    VDECFW_CMD_HORIZONTAL_SCALE_CONTROL,                    /*!< HORIZONTAL_SCALE_CONTROL                       */
    VDECFW_CMD_SCALE_HORIZONTAL_CHROMA,                     /*!< SCALE_HORIZONTAL_CHROMA (H.264 only)           */
    VDECFW_CMD_VERTICAL_SCALE_CONTROL,                      /*!< VERTICAL_SCALE_CONTROL                         */
    VDECFW_CMD_SCALE_VERTICAL_CHROMA,                       /*!< SCALE_VERTICAL_CHROMA (H.264 only)             */
    VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_0,              /*!< HORIZONTAL_LUMA_COEFFICIENTS_0                 */
    VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_1,              /*!< HORIZONTAL_LUMA_COEFFICIENTS_1                 */
    VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_2,              /*!< HORIZONTAL_LUMA_COEFFICIENTS_2                 */
    VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_3,              /*!< HORIZONTAL_LUMA_COEFFICIENTS_3                 */
    VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_0,                /*!< VERTICAL_LUMA_COEFFICIENTS_0                   */
    VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_1,                /*!< VERTICAL_LUMA_COEFFICIENTS_1                   */
    VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_2,                /*!< VERTICAL_LUMA_COEFFICIENTS_2                   */
    VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_3,                /*!< VERTICAL_LUMA_COEFFICIENTS_3                   */
    VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_0,            /*!< HORIZONTAL_CHROMA_COEFFICIENTS_0               */
    VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_1,            /*!< HORIZONTAL_CHROMA_COEFFICIENTS_1               */
    VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_2,            /*!< HORIZONTAL_CHROMA_COEFFICIENTS_2               */
    VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_3,            /*!< HORIZONTAL_CHROMA_COEFFICIENTS_3               */
    VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_0,              /*!< VERTICAL_CHROMA_COEFFICIENTS_0                 */
    VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_1,              /*!< VERTICAL_CHROMA_COEFFICIENTS_1                 */
    VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_2,              /*!< VERTICAL_CHROMA_COEFFICIENTS_2                 */
    VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_3,              /*!< VERTICAL_CHROMA_COEFFICIENTS_3                 */
    VDECFW_CMD_SCALE_OUTPUT_SIZE,                           /*!< SCALE_OUTPUT_SIZE                              */
    VDECFW_CMD_INTRA_BUFFER_PLANE_SIZE,

    VDECFW_CMD_MAX,

} VDECFW_ePictureCmds;

//! Size of relocation data attached to VDECFW_sTransaction message in words
#define VDECFW_RELOC_SIZE 125


/*!
******************************************************************************
 This structure contains the Performance attributes to be given to the firmware.
 @brief  Performance Attributes
******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bFirstFieldReceived);
    //IMG_UINT16 ui32WidthMBS;            //!< Picture width in macroblocks
    //IMG_UINT16 ui16HeightMBS;           //!< Picture height in macroblocks
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16NumSlices);           //!< Number of slices in the picture
    //IMG_UINT16 ui161SliceSize;          //!< Number of macroblocks in the first slice
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PictureStarted);      //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FirmwareReady);       //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32SyncStart);           //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32SyncComplete);        //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PicmanComplete);      //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FirmwareSaved);       //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32EntdecStarted);       //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Fe1sliceDone);        //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FePictureComplete);   //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BePictureStarted);    //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Be1sliceDone);        //!< Timestamp
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BePictureComplete);   //!< Timestamp

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TotParseSliceHeader); //!< Cumulative Ticks
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TotSetupRegisters);   //!< Cumulative Ticks
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TotParseAndSetupReg); //!< Cumulative Ticks
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TotVLC);              //!< Cumulative Ticks
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TotParserLoad);       //!< Cumulative Ticks
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TotHwFEDecode);       //!< Cumulative Ticks
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TotHwBEDecode);       //!< Cumulative Ticks

} VDECFW_sPerformanceData;

/*!
******************************************************************************

 This structure defines the MMU Tile configuration.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8TilingScheme);                                            /*!< MMU_CONTROL2      */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32MmuTiling[MSVDX_CORE_CR_MMU_TILE_NO_ENTRIES]);          /*!< MMU_TILE          */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32MmuTilingExt[MSVDX_CORE_CR_MMU_TILE_EXT_NO_ENTRIES]);   /*!< MMU_TILE_EXT      */

} VDECFW_sMmuTileConfig;



typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispPsrTextLoadAddr);                /*!< DMA base address from which to load the parser code text section and first portion of data section (const data).       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrTextSize);                    /*!< Size of Parser code in bytes.                                                                                          */
#ifndef USE_FW_RELOC_INFO_PACKING
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrTextRelocSize);               /*!< Size of Parser relocation data in words.                                                                               */
#endif /* not USE_FW_RELOC_INFO_PACKING */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrTextOrig);                    /*!< Original address for which module text was linked.                                                                     */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrTextAddr);                    /*!< Address where to load module text.                                                                                     */

    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispPsrDataLoadAddr);                /*!< DMA base address from which to load the parser data section.                                                           */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrDataSize);                    /*!< Size of Parser data in bytes.                                                                                          */
#ifndef USE_FW_RELOC_INFO_PACKING
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrDataRelocSize);               /*!< Size of Parser relocation data in words.                                                                               */
#endif /* not USE_FW_RELOC_INFO_PACKING */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrDataOrig);                    /*!< Original address for which module data was linked.                                                                     */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrDataAddr);                    /*!< Address where to load module data.                                                                                     */

#ifdef USE_FW_CTX_TRIMMING
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrCtxSize);                     /*!< Size of Parser context in bytes.                                                                                          */
#endif /* USE_FW_CTX_TRIMMING */
#ifdef USE_FW_RELOC_INFO_PACKING
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrPackedRelocInfoSize);         /*!< Size of Parser packed relocation information in bytes.                                                                                          */
#endif /* USE_FW_RELOC_INFO_PACKING */

#ifndef USE_FW_RELOC_INFO_PACKING
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32PsrRelocData[VDECFW_RELOC_SIZE]);  /*!< Data for text section and data section relocations. We have DataReloc(IMG_UINT32), TextReloc (IMG_UINT32),
                                                                        TextRelocAddr (IMG_UINT32), and TextRelocType (IMG_UINT8). It gives 4 bytes for each relocated data element and 9
                                                                        bytes for each reallocated text element.                                                                                */
#endif /* not USE_FW_RELOC_INFO_PACKING */

} VDECFW_sPsrModInfo;


/*!
******************************************************************************
 This structure contains the transaction attributes to be given to the firmware.
 @brief  Transaction Attributes
 ******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransactionId);                  /*!< Unique identifier for the picture (driver-wide).                                                                       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, VDECFW_eCodecType, eCodec);                             /*!< Codec                                                                                                                  */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSecureStream);                      /*!< Flag to indicate that the stream needs to ge handled  in secure memory (if available)                                  */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32StreamId);                       /*!< Unique identifier for the current stream                                                                               */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, VDECFW_eParserMode, eParserMode);                        /*!< Dictates to the FW parser how the NALs are delimited                                                                   */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FeWdt);                          /*!< FE watchdog timeout value.                                                                                             */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BeWdt);                          /*!< BE watchdog timeout value.                                                                                             */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PSRWdt);                         /*!< Parser watchdog timeout value.                                                                                         */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FeSyncTransactionId);            /*!<                                                                                                                        */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BeSyncTransactionId);            /*!<                                                                                                                        */

    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispCtxLoadAddr);                    /*!< Address from which to load the parser context data.                                                                    */
    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispCtxSaveAddr);                    /*!< Address to save the parser state data including the updated "parser context data".                                     */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32CtxSize);                        /*!< Size of the parser context data in bytes.                                                                              */

    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispCtrlSaveAddr);                   /*!< Address to save the "buffer control" data.                                                                             */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32CtrlSize);                       /*!< Size of the buffer control data in bytes.                                                                              */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32PictCmds[VDECFW_CMD_MAX]);      /*!<                                                                                                                        */

    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispVlcTablesAddr);                  /*!< Address of VLC table data.                                                                                             */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32VlcTablesSize);                  /*!< Size of the VLC table data in bytes.                                                                                   */

    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispVlcIdxTableAddr);                /*!< Address of VLC index table data.                                                                                       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32VlcIdxTableSize);                /*!< Size of the VLC index table data in bytes.                                                                             */

    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uispPsrHdrAddr);                     /*!< Address of parser picture header.                                                                                      */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PsrHdrSize);                     /*!< Size of the parser picture header in bytes.                                                                            */

    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uipSequenceInfoSource);              /*!< Address of Sequence Info in the Host (secure)                                                                          */
    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uipPPSInfoSource);                   /*!< Address of PPS Info in the Host (secure)                                                                               */
    IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, VDECFW_SHARED_UINTPTR, uipSecondPPSInfoSource);             /*!< Address of Second PPS Info in the Host (secure)                                                                        */

    VDECFW_sMmuTileConfig   sMmuTileConfig;                     /*!< MMU Tile config comes down with each transaction.                                                                      */

} VDECFW_sTransaction;


/*!
******************************************************************************
 This structure contains the info for extracting a subset of VLC tables indexed
 inside the index table.
 aui32VlcTablesOffset is the offset to the first table inside the index table
 aui32VlcConsecutiveTables indicates the consecutive number of entries (from
    aui32VlcTablesOffset to aui32VlcTablesOffset+aui32VlcConsecutiveTables)
    which will be copied.
******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16VlcTablesOffset);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16VlcConsecutiveTables);
}
VDECFW_sVlcTableInfo;


/*!
******************************************************************************
 This structure contains the info for DMAing the VLC from one (or more) segments:
    - sVlcTableInfo is an array of structures to find the entries inside the index table
      which needs to be sent. The size of this array is statically defined for the
      codec with the biggest number of VLC fragments (VC-1 with 12).
    - ui8VlcTablesNum is the number of valid entries inside the previous array. If
      this variable equals to one we return to the base case when the section of the
      gaui16<STD>VlcTableData table from gaui16<STD>VlcIndexData[gaui16<STD>VlcIndexData[0][2]]
      and gaui16<STD>VlcIndexData[gaui16<STD>VlcIndexData[1][2]] is sent
 ******************************************************************************/
typedef struct
{
    VDECFW_sVlcTableInfo asVlcTableInfo[12];
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8VlcTablesNum);
} VDECFW_sVlcInfo;


/*!
******************************************************************************

 This structure defines the RENDEC buffer configuration.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RegVecRendecControl0);           /*!< VEC_RENDEC_CONTROL0                        */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RegVecRendecControl1);           /*!< VEC_RENDEC_CONTROL1                        */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RendecBufferBaseAddr0);          /*!< VEC_RENDEC_BASE_ADDR0                      */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RendecBufferBaseAddr1);          /*!< VEC_RENDEC_BASE_ADDR1                      */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RegVecRendecBufferSize);         /*!< VEC_RENDEC_BUFFER_SIZE                     */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32RendecInitialContext[6]);       /*!< VEC_RENDEC_CONTEXT0 - VEC_RENDEC_CONTEXT5  */

} VDECFW_sRendecConfig;


/*!
******************************************************************************

 This structure defines the MMU configuration.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, b36bitMemTwiddle);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MmuControl2);                                            /*!< MMU_CONTROL2      */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32PTD[1]);

} VDECFW_sMmuConfig;


/*!
******************************************************************************

 This structure defines the Core configuration.

******************************************************************************/
typedef struct
{
    VDECFW_sMmuConfig           sMmuConfig;
    VDECFW_sRendecConfig        sRendecConfig;

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RegVecControl2);                 /*!< CR_VEC_CONTROL_2 */

} VDECFW_sCoreInitData;


/*!
******************************************************************************

 This structure defines the Sequence, VPS and PPS(s) pointers

******************************************************************************/
typedef struct
{
        IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, IMG_UINTPTR, uipSequenceInfoDest);
        IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, IMG_UINTPTR, uipVPSInfoDest);
        IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, IMG_UINTPTR, uipPPSInfoDest);
        IMG_ALIGN_FIELD(VDECFW_SHARE_PTR_ALIGNMENT, IMG_UINTPTR, uipSecondPPSInfoDest);

        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32SequenceInfoSize);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32VPSInfoSize);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PPSInfoSize);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32SecondPPSInfoSize);

} VDECFW_sSeqPPSLocations;


#endif /* _VDECFW_H_ */

/** @}*/

