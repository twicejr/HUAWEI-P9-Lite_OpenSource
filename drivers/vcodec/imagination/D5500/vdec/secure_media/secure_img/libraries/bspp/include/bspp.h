/*!
 *****************************************************************************
 *
 * @File       bspp.h
 * @Title      VXD Bitstream Buffer Pre-Parser
 * @Description    This file contains the structure and function prototypes
 *  for the VXD Bitstream Buffer Pre-Parser.
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

#ifndef __BSPP_H__
#define __BSPP_H__

#include "img_defs.h"

#include "vdec_api.h"
#include "vdecdd_defs.h"
#include "lst.h"
#include "vdec_params.h"
#include "vxd_buf.h"


#ifdef __cplusplus
extern "C" {
#endif

//! There are up to 2 pictures in each buffer (plus trailing data for the next picture, e.g. PPS).
#define BSPP_MAX_PICTURES_PER_BUFFER 3

#define BSPP_MB_SIZE (16)

#define BSPP_INVALID ((IMG_UINT32)(-1))

#define I_FRAME_SIGNALS_CLOSED_GOP // This enables signalling of closed gop at every I frame. Add resilience to seeking functionallity.

#define IMG_SECURE_MALLOC(ui32BufSize)  IMG_BIGALLOC(ui32BufSize)//IMG_CALLOC(1, ui32BufSize)//IMG_BIGALLOC(ui32BufSize)//IMG_CALLOC(1, ui32BufSize)//IMG_CALLOC(1, ui32BufSize)
#define IMG_SECURE_FREE(ptr)            IMG_BIGFREE(ptr)//IMG_FREE(ptr)//IMG_BIGFREE(ptr)//IMG_FREE(ptr)//

#define GET_ELEMENT_FROM_PACKED_DEVICE_BUFFER(psBSPP_sDdBufArrayInfo) ((IMG_VOID*)((IMG_UINTPTR)((psBSPP_sDdBufArrayInfo)->sDdBufInfo.pvCpuVirt) + (psBSPP_sDdBufArrayInfo)->ui32BufOffset))

/*!
******************************************************************************

            enumeration of parsing error , different error flag for different
            data unit
******************************************************************************/
typedef enum
{
    BSPP_ERROR_NONE                     = (0),          //<!  No Error in parsing.
    BSPP_ERROR_CORRECTION_VSH           = (1<<0),       //<!  Correction in VSH, Replaced VSH with faulty one
    BSPP_ERROR_CORRECTION_VALIDVALUE    = (1<<1),       //<!  Correction in parsed Value, clamp the value if it goes beyond the limit
    BSPP_ERROR_AUXDATA                  = (1<<2),       //<!  Error in Aux data (i.e. PPS in H.264) parsing.
    BSPP_ERROR_DATA_REMAINS             = (1<<3),       //<!  Error in  parsing, more data remains in VSH data unit after parsing.
    BSPP_ERROR_INVALID_VALUE            = (1<<4),       //<!  Error in  parsing, parsed codeword is invalid
    BSPP_ERROR_DECODE                   = (1<<5),       //<!  Error in  parsing, parsing error
    BSPP_ERROR_NO_REF_FRAME             = (1<<6),       //<!  reference frame is not avilable for decoding .
    BSPP_ERROR_NONIDR_FRAME_LOSS        = (1<<7),       //<!  Non IDR frame loss detected .
    BSPP_ERROR_IDR_FRAME_LOSS           = (1<<8),       //<!  IDR frame loss detected .
    BSPP_ERROR_INSUFFICIENT_DATA        = (1<<9),       //<!  Error in  parsing, insufficient data to complete parsing
    BSPP_ERROR_UNSUPPORTED              = (1<<10),      //<!  Severe Error, Error indicates, no support for this picture data
    BSPP_ERROR_UNRECOVERABLE            = (1<<11),      //<!  Severe Error,Error in  which could not be recoverd
    BSPP_ERROR_NO_NALHEADER             = (1<<12),      //<!  Severe Error,Error, to indicate that NAL Header is absent after SCP
    BSPP_ERROR_NO_SEQUENCE_HDR          = (1<<13),
    BSPP_ERROR_SIGNALED_IN_STREAM       = (1<<14),
    BSPP_ERROR_UNKNOWN_DATAUNIT_DETECTED= (1<<15),
    BSPP_ERROR_NO_PPS                   = (1<<16),
    BSPP_ERROR_NO_VPS                   = (1<<17),
    BSPP_ERROR_OUT_OF_MEMORY            = (1<<18),

} BSPP_eErrorType;

typedef struct
{
    IMG_UINT32      ui32BufSize;        /*!< The size of the buffer (in bytes).                                */
    IMG_VOID *      pvCpuVirt;          /*!< The CPU virtual address  (mapped into the local cpu MMU)          */

    IMG_PHYSADDR *  ppaPhysAddr;        /*!< Array with physical addresses of the pages (assumed linear)       */
    SYS_eMemAttrib  eMemAttrib;         //!< Memory attributes

    IMG_UINT32      ui32BufMapId;

} BSPP_sDdBufInfo;

typedef struct
{
    BSPP_sDdBufInfo   sDdBufInfo;        /*!< Buffer info (cointainer)              */
    IMG_UINT32  ui32BufElementSize;      /*!< Size of each element                  */
    IMG_UINT32  ui32BufOffset;           /*!< Offset for each element               */
} BSPP_sDdBufArrayInfo;

typedef struct {

    SYSBRG_POINTER(IMG_VOID, lst_padding);                         /*!< Reserved space for LST_LINK link  (allows the structure to be part of a LST).*/
    

    IMG_UINT32              ui32DataSize;       /*!< The amount of bit stream data (in bytes)
                                                     from the start of the buffer of the data
                                                     that is part of this picture.                        */
    IMG_UINT32              ui32DataByteOffset; /*!< A byte offset from the start of this buffer to
                                                     the data which is part of this unit.                       */
    IMG_UINT32              ui32BitStrSegFlag;  /*!< Bitstream segment type.                              */
    IMG_UINT8               ui8StartCodeSuffix; /*!< Start code suffix to use when VDECDD_BSSEG_INSERT_STARTCODE
                                                     is set in ui32BitStrSegFlag                                */
    IMG_UINT32              ui32BufMapId;       /*!< Buffer mapping ID.                                   */

} BSPP_sBitStrSeg;


/*!
******************************************************************************
 This structure contains the picture header data information.
 @brief  Picture Header Data Information
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32BufMapId;   /*!< Buffer ID to use inside kernel #VXDIO_sDdBufInfo               */
    IMG_UINT32  ui32BufOffset;  /*!< Buffer offset (for packed device buffers, e.g. PPS)            */
    SYSBRG_POINTER(IMG_VOID, pvData);         /*!< Picture data.                                                  */
    IMG_UINT32  ui32Size;       /*!< Size (in bytes) of data.                                       */
    IMG_UINT32  ui32Id;         /*!< Data identifier.                                               */

} BSPP_sPictData;

/*!
******************************************************************************
 This structure contains the picture header information.
 NOTE: Should only contain information needed by the VDEC API.
 @brief  Picture Header Information
******************************************************************************/
typedef struct
{
    IMG_BOOL                    bIntraCoded;                    /*!< Picture is entirely intra-coded and doesn't use any reference data.
                                                                     NOTE: should be IMG_FALSE if this cannot be determined.                */
    IMG_BOOL                    bReference;                     /*!< Picture might be referenced by subsequent pictures.                    */
    IMG_BOOL                    bField;                         /*!< Picture is a field as part of a frame.                                 */
    IMG_BOOL                    bEmulationPrevention;           /*!< Emulation prevention bytes are present in picture data.                */
    IMG_BOOL                    bPostProcessing;                /*!< Post Processing.                                                       */
    IMG_BOOL                    bDiscontinuousMbs;              /*!< Macroblocks within the picture may not occur in raster-scan order.     */
    IMG_BOOL                    bFragmentedData;                /*!< Flag to indicate data is span across mulitple buffer.                  */

    IMG_UINT8					ui8SOSCount;					/*!< SOS fields count value                              */

    IMG_BOOL                    bFirstPicOfSequence;            /*!< This picture is the first of the sequence                              */

    VDECFW_eParserMode          eParserMode;                    /*!< */
    IMG_UINT32                  ui32PicDataSize;                /*!< Total size of picture data which is going to be submitted.             */

    VDEC_sPictSize              sCodedFrameSize;                /*!< Size of coded frame as specified in the bitstream.                     */
    VDEC_sPictDispInfo          sDispInfo;                      /*!< Display information for picture                                        */

    BSPP_sPictData              sPictAuxData;                   /*!< Picture auxiliary data (e.g. H.264 SPS/PPS).                           */
    BSPP_sPictData              sSecondPictAuxData;             /*!< Picture auxiliary data (e.g. H.264 SPS/PPS).                           */
    BSPP_sPictData              sPictSgmData;                   /*!< Slice group-map data.                                                  */

    union
    {
        struct
        {
            IMG_UINT32  aui32FragmentSize[REALFW_MAX_FRAGMENTS];
            IMG_UINT32  ui32NumOfFragments;
        } sRealExtraPictHdrInfo;

        VDEC_sJPEGPictHdrInfo   sJPEGPictHdrInfo;               /*!< JPEG specific picture header information.                              */

        struct
        {
            IMG_BOOL   bInterlacedFrame;                        /*!< VC1 specific picture header information.                               */

        } sVC1PictHdrInfo;

        struct
        {
            IMG_UINT32  ui32FirstPartSize;                        /*!< VP8 specific frame information.                                      */
            IMG_UINT8   ui8PartitionCount;
        } sVP8PictHdrInfo;

        struct
        {
            IMG_BOOL    bMultiStream;                        /*!< VP6 specific frame information.                                      */
            IMG_UINT32  ui32Buff2Offset;
        } sVP6PictHdrInfo;

        struct
        {
            IMG_BOOL    bRangeExtPresent;
            IMG_BOOL    bIsFullRangeExt;
        } sHEVCPictHdrInfo;
    };

} BSPP_sPictHdrInfo;

/*!
******************************************************************************
 This structure contains the sequence header information.
 NOTE: Should only contain information needed by the VDEC API.
 @brief  Sequence Header Information
******************************************************************************/
typedef struct
{
    IMG_UINT32              ui32SequHdrId;      /*!< Sequence header Id.                    INSECURE MEMORY HOST */

    // Temp ref count. Remove once the BSPP is properly managing sequence data.
    IMG_UINT32              ui32RefCount;       /*!< Reference count for sequence header.  */

    VDEC_sComSequHdrInfo    sComSequHdrInfo;    /*!< Common sequence header information.    INSECURE MEMORY HOST */

    IMG_UINT32              ui32BufMapId;       /*!< Buffer ID to be used in kernel                   */

    IMG_UINT32              ui32BufOffset;       /*!< Buffer Offeset to be used in kernel                   */


    union
    {
        //VDEC_sMPEG2SequHdrInfo  sMPEG2SequHdrInfo;  /*!< MPEG-2 specific sequence header information.  */
        //VDEC_sH264SequHdrInfo   sH264SequHdrInfo;     /*!< H264 specific sequence header information.  */
        //VDEC_sVC1SequHdrInfo    sVC1SequHdrInfo;    /*!< VC1 specific sequence header information.     */
        VDEC_sAVSSequHdrInfo    sAVSSequHdrInfo;    /*!< AVS specific sequence header information.     */
        //VDEC_sREALSequHdrInfo   sREALSequHdrInfo;   /*!< REAL specific sequence header information.    */
        VDEC_sJPEGSequHdrInfo   sJPEGSequHdrInfo;   /*!< JPEG specific sequence header information.    */
        VDEC_sVP6SequHdrInfo    sVP6SequHdrInfo;    /*!< VP6specific sequence header information.      */
    };

} BSPP_sSequHdrInfo;

typedef struct
{
    // Anonymous
    LST_T                   asPrePictSegList[BSPP_MAX_PICTURES_PER_BUFFER];    //!< Bitstream segments that contain other (non-picture) data before the picture in the buffer (elements of type #VDECDD_sBitStrSeg).

    // Picture
    IMG_UINT32              ui32SequHdrId;
    BSPP_sPictHdrInfo       sPictHdrInfo;
    LST_T                   asPictSegList[BSPP_MAX_PICTURES_PER_BUFFER];       //!< Bitstream segments that contain picture data, one for each field (if present in same group of buffers (elements of type #VDECDD_sBitStrSeg).

    IMG_VOID              * apvPictTagParam[BSPP_MAX_PICTURES_PER_BUFFER];

    IMG_BOOL                bIsPrefix;

} BSPP_sPictureData;
/*!
******************************************************************************
 This structure describes a pre-parsed set of buffer(s).
 @brief  Pre-parsed buffer information
******************************************************************************/
typedef struct
{
    // Sequence
    IMG_BOOL                bNewSequence;
    BSPP_sSequHdrInfo       sSequHdrInfo;
    IMG_BOOL                bSequenceEnd;

    // Closed GOP
    IMG_BOOL                bClosedGOP;

    // Picture
    IMG_BOOL                bNewPicture;
    BSPP_sPictureData       sPictureData;

    // Additional pictures (MVC extension)
    IMG_BOOL                bNewSubSequence;
    BSPP_sSequHdrInfo       sExtSequHdrInfo;
    BSPP_sPictureData       asExtPicturesData[VDEC_H264_MVC_MAX_VIEWS];         /*!<non-base view pictures + picture prefix for next frame */
    IMG_UINT32              ui32NumExtPictures;

    // Additional information
    IMG_UINT32              ui32ErrorFlags;         /*!< Flags word to indicate error in parsing/decoding - see #VDEC_eErrorType.           */
    IMG_UINT32              ui32WarningFlags;       /*!< Flags word to indicate warning in parsing/decoding - see #VDEC_eWarningType.       */
    IMG_UINT32              ui32CorrectionFlags;    /*!< Flags word to indicate correction in parsing/decoding - see #VDEC_eCorrectionType. */// Error/warning/correction flags?

} BSPP_sPreParsedData;


/*!
******************************************************************************
 This structure is used to store picture-decoded information for
 resource handling (sequences/PPSs).
******************************************************************************/
typedef struct
{
    LST_LINK;

    IMG_UINT32              ui32SequHdrId;
    IMG_UINT32              ui32PPSId;
    IMG_UINT32              ui32SecondPPSId;

} BSPP_sPictureDecoded;

/*!
******************************************************************************

 @Function              BSPP_StreamCreate

 @Description

 Creates a stream context for which to pre-parse bitstream buffers. The following
 allocations will take place:
    - Local storage for high-level header parameters (secure)
    - Host memory for common sequence information (insecure)
    - Device memory for Sequence information (secure)
    - Device memory for PPS (secure, H.264 only)

 @Input    eVidStd : Video standard corresponding to bitstream data.

 @Input    eBstrFormat : Bitstream format of input buffers.

 @Output   phStrContext : A pointer used to return the stream context handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT BSPP_StreamCreate(
    const VDEC_sStrConfigData * psStrConfigData,
    IMG_HANDLE            * phStrContext,
    BSPP_sDdBufArrayInfo    asFWSequence[],
    BSPP_sDdBufArrayInfo    asFWPPS[]
);

/*!
******************************************************************************

 @Function              BSPP_SetCodecConfig

 @Description

 This function is used to set the out-of-band codec config data.

 @Input     hStrContext     : Stream context handle.

 @Input     psCodecConfig   : Codec-config data

 @Return    This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT BSPP_SetCodecConfig(
    const IMG_HANDLE            hStrContext,
    const VDEC_sCodecConfig   * psCodecConfig
);



/*!
******************************************************************************

 @Function              BSPP_StreamDestroy

 @Description

 Destroys a stream context used to pre-parse bitstream buffers.

 @Input    hStrContext  : Stream context handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT BSPP_StreamDestroy(
    IMG_HANDLE            hStrContext
);


/*!
******************************************************************************

 @Function              BSPP_SubmitPictureDecoded

 @Description

******************************************************************************/
extern IMG_RESULT
BSPP_SubmitPictureDecoded(
    IMG_HANDLE              hStrContext,
    IMG_UINT32              ui32SequHdrId,
    IMG_UINT32              ui32PPSId,
    IMG_UINT32              ui32SecondPPSId
);


/*!
******************************************************************************

 @Function              BSPP_StreamSubmitBuffer

******************************************************************************/
extern IMG_RESULT BSPP_StreamSubmitBuffer(
    IMG_HANDLE                  hStrContext,
    const BSPP_sDdBufInfo     * psDdBufInfo,
    IMG_UINT32                  ui32BufMapId,
    IMG_UINT32                  ui32DataSize,
    IMG_VOID                  * pvPictTagParam,
    VDEC_eBstrElementType       eBstrElementType
);


/*!
******************************************************************************

 @Function              BSPP_StreamPreParseBuffers

 @Description

 Pre-parses bistream buffer and returns picture information in structure that
 also signals when the buffer is last in picture.

 @Input    hStrContext      : Stream context handle.

 @Input    psContiguousBufInfo : Buffer for reconstructing reconstruct multiple
                                  segments that may be non contiguous in memory

 @Input    ui32ContiguousBufMapId : psContiguousBufInfo Buffer Map id

 @Input    psSegments       : Pointer to a list of segments (see #VDECDD_sBitStrSeg).

 @Output   psPreParsedData  : Container to return picture information. Only provide
                              when buffer is last in picture (see #bForceEop in
                              function #VDEC_StreamSubmitBstrBuf).

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT BSPP_StreamPreParseBuffers(
    IMG_HANDLE              hStrContext,
    const BSPP_sDdBufInfo * psContiguousBufInfo,
    IMG_UINT32              ui32ContiguousBufMapId,
    LST_T                 * psSegments,
    BSPP_sPreParsedData   * psPreParsedData
);

/*!
******************************************************************************

 @Function              BSPP_StreamLogPicture

 @Description

 Logs content of common picture header.

 @Input     hStrContext     : Stream context handle.

 @Input     psPictHdrInfo   : Pointer to picture header information.

******************************************************************************/
extern IMG_RESULT BSPP_StreamLogPicture(
    const IMG_HANDLE          hStrContext,
    const BSPP_sPictHdrInfo * psPictHdrInfo
);


/*!
******************************************************************************

 @Function              BSPP_StreamLogSequence

 @Description

 Logs content of common sequence header (if provided) else logs the last
 sequence header for the ID provided.

 @Input     hStrContext     : Stream context handle.

 @Input     ui32SequHdrId   : Sequence header ID.

 @Input     psSequHdrInfo   : Pointer to picture header information.

******************************************************************************/
extern IMG_RESULT BSPP_StreamLogSequence(
    const IMG_HANDLE            hStrContext,
    IMG_UINT32                  ui32SequHdrId,
    const BSPP_sSequHdrInfo   * psSequHdrInfo
);



#ifdef __cplusplus
}
#endif

#endif /* __BSPP_H__   */
