/*!
 *****************************************************************************
 *
 * @File       apiinternal.h
 * @Title      Defines shared between user and kernel VXE drivers
 * @Description    Defines shared between user and kernel VXE drivers
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

#ifndef __apiinternal__
#define __apiinternal__

//#define ISR_POLLING_ENABLED 1

#if defined(ISR_POLLING_ENABLED) || defined(SYSBRG_NO_BRIDGING)
#define POLL_FOR_INTERRUPT 1
#define SLEEP_DURING_POLL_IN_MS 10
#endif

#include "img_types.h"
#include "memmgr_common.h"

#include "MTX_FwIF.h"

#define MEM_POOL_SIZE 32
#define ENCODE_FIFO_SIZE 2
#define HIGH_CMD_FIFO_SIZE 15




#define TOPAZ_DEV_NAME 			"TOPAZ"



#define NUM_SLICE_TYPES     5

#define UNINIT_PARAM 0xCDCDCDCD

#define MV_OFFSET_IN_TABLE(BDistance, Position) ((BDistance) * MV_ROW_STRIDE + (Position) * sizeof(IMG_MV_SETTINGS))

/*!
 *****************************************************************************
 *
 * @details    Default value for CABAC_DB_MARGIN in VLC_IPCM_0 register
 *
 * @brief      Default value for CABAC_DB_MARGIN 
 *
 ****************************************************************************/
#define DEFAULT_CABAC_DB_MARGIN    (0x190)

/*!
 ***********************************************************************************
 *
 * Description        : An element of HIGH priority commands FIFO
 *
 ************************************************************************************/
typedef struct tag_HIGH_CMD_FIFO_ELEMENT
{
	IMG_UINT8		ui8HighCmdCnt;	//!< HIGH commands counter (used as ID)
	IMG_UINT32		ui32CmdWord;	//!< Command word (Command type, Priority, etc.)
	MEMORY_INFO *	pDataInfo;		//!< Data section
} HIGH_CMD_FIFO_ELEMENT;

/*!
*****************************************************************************

 @details    Handle for internal encoder context structure

 @brief          Encoder context handle

****************************************************************************/
typedef void *IMG_HCOMM_SOCKET;

typedef struct
{
	MTX_MESSAGE_ID	eCmdId;
	IMG_UINT32		ui32InputCmdWord;
	IMG_UINT8		ui8CodedPackageIdx;
	IMG_UINT32		ui32WritebackVal;
	IMG_UINT32		ui32Data;
	MEMORY_INFO		* pCommandDataBuf;
} MTX_TOHOST_MSG;

typedef struct
{
	MTX_CMD_ID	eCmdId;
	IMG_UINT32	ui32Data;
	MEMORY_INFO * pCommandDataBuf;
} MTX_TOMTX_MSG;



/*!
 *****************************************************************************
 *
 * @details    Struct describing input parameters to encode a video picture
 *
 * @brief          Video picture parameters
 *
 ****************************************************************************/
typedef struct
{
	IMG_UINT32		ui32Flags;				//!< Picture parameter flags
	IN_RC_PARAMS	sInParams;				//!< Rate control parameters

} PIC_PARAMS;

typedef struct
{
    int metadataBufferType;
    void* handle;
    int offset;
} video_metadata_t;


typedef struct {
	video_metadata_t meta;
	void *pBuffer;
} buf_meta_pair_t ;

typedef struct
{
	buf_meta_pair_t hBufHandle;
	IMG_UINT32 ui32PallocID;
	MEMORY_INFO *pMemoryInfo;
	IMG_FRAME *psFrame;
}EXTERNAL_BUFFER_ASSOC;
#define NUM_EXTERNAL_BUFFERS 30


/*!
 ***********************************************************************************
 *
 * Description        : Video encode context
 *
 ************************************************************************************/
typedef struct tag_IMG_VIDEO_CONTEXT
{
	/* stream level params */
	IMG_STANDARD	eStandard;             	//!< Video standard
	IMG_UINT16		ui16Width;              //!< target output width
	IMG_UINT16		ui16FrameHeight;        //!< target output height
	IMG_UINT16		ui16PictureHeight;      //!< target output height
	IMG_UINT16		ui16BufferStrideBytes;        //!< input buffer stride
	IMG_UINT16		ui16BufferHeight;       //!< input buffer width
	IMG_UINT8		ui8FrameRate;

	IMG_UINT16		ui16UnroundedWidth;
	IMG_UINT16		ui16UnroundedFrameHeight;

	IMG_UINT32		ui32DebugCRCs;
	IMG_FORMAT		eFormat;				//!< Pixel format of the source surface
	IMG_CSC_PRESET	eCscPreset;				//!< Colour space conversion to be performed on the source surface

	/* Numbers of array elements that will be allocated */
	IMG_INT32		i32PicNodes;
	IMG_INT32		i32MVStores;
	IMG_INT32		i32CodedPackages;

	/* slice control parameters */

#if defined(VP8_DRIVER)
	IMG_UINT32		ui32Vp8RefStructMode;							//!< VP8 reference structure mode
	IMG_UINT32		ui32Vp8NoRefreshProbsPeriod;					//!< VP8 period of frames with no probability update
	IMG_BOOL   		bVp8TemporalThinning;							//!< VP8 temporal thinning enabled
	/* VP8 prob buffers */
	struct MEMORY_INFO_TAG* pVp8ProbBuffer[VP8_NUM_PROB_BUFFERS];	//!< VP8 probability buffers
	IMG_UINT32		ui32VP8RefFrmUpdateFrmCnt[3]; //Array of 3 elements for tracking the frame count of the reference frame - 0 for Previous ; 1 for Golden ; 2 for Alternate
	IMG_UINT8		ui8VP8RefFrameFlag; // Bit mapped flag for VP8 reference frame for Usage and Update
	IMG_BOOL		bSetVP8RefFrmFlagInternally;
#endif
	/* per core params */
	PIC_PARAMS sPicParams;  //!< Picture level parameters (supplied by driver)
	struct MEMORY_INFO_TAG* psAboveParams[TOPAZHP_MAX_NUM_PIPES];  //!< Picture level parameters (supplied by driver)
	struct MEMORY_INFO_TAG* apsReconPictures[MAX_PIC_NODES];	//!< Reference pictures (2 input and 1 output)
	struct MEMORY_INFO_TAG* apsColocated[MAX_PIC_NODES];		//!< Colocated vector stores (2 input and 1 output)
	struct MEMORY_INFO_TAG* apsMV[MAX_MV];						//!< Vector stores
    struct MEMORY_INFO_TAG* apsInterViewMV[2];					//!< Inter-view vector stores

	/* partially coded headers supplied to HW */
	// SEI_INSERTION
	struct MEMORY_INFO_TAG* pAUDHeaderMem;
	struct MEMORY_INFO_TAG* pSEIBufferingPeriodHeaderMem;
	struct MEMORY_INFO_TAG* pSEIPictureTimingHeaderMem;

	struct MEMORY_INFO_TAG* pSeqHeaderMem;                          //!< Partially coded Sequence header
	struct MEMORY_INFO_TAG* pSubSetSeqHeaderMem;                    //!< Partially coded Subset sequence header for H264 mvc
	struct MEMORY_INFO_TAG* apPicHdrTemplateMem[4];
	struct MEMORY_INFO_TAG* apSliceParamsTemplateMem[NUM_SLICE_TYPES];

	struct MEMORY_INFO_TAG* apSrcPhysAddr;

// WEIGHTED PREDICTION
	struct MEMORY_INFO_TAG* apsWeightedPredictionMem[MAX_SOURCE_SLOTS_SL];
	IMG_BOOL bWeightedPrediction;
	IMG_UINT8 ui8WeightedBiPred;
	
	struct MEMORY_INFO_TAG* pFlatGopStruct;                          	//!< Flat MiniGop structure
	struct MEMORY_INFO_TAG* pHierarGopStruct;                           //!< Hierarchical MiniGop structure
#ifdef LTREFHEADER
	struct MEMORY_INFO_TAG* pLtRefHeader[MAX_SOURCE_SLOTS_SL];
#endif

	struct MEMORY_INFO_TAG* psCustomQuant[2];				//!< Custom quantization values
	struct MEMORY_INFO_TAG* psCustomQuantRegs4x4Sp[2];		//!< Custom quantization register values for 4x4 Sp
	struct MEMORY_INFO_TAG* psCustomQuantRegs8x8Sp[2];		//!< Custom quantization register values for 8x8 Sp
	struct MEMORY_INFO_TAG* psCustomQuantRegs4x4Q[2];		//!< Custom quantization register values for 4x4 Q
	struct MEMORY_INFO_TAG* psCustomQuantRegs8x8Q[2];		//!< Custom quantization register values for 8x8 Q
	IMG_UINT8	ui8CustomQuantSlot;

	IMG_BUFFER   * apsSliceMap[MAX_SOURCE_SLOTS_SL];                      //!< Slice map of the source picture

    IMG_BUFFER   sFirstPassOutParamBuf[MAX_SOURCE_SLOTS_SL];              //!< Output Parameters of the First Pass
#ifndef EXCLUDE_BEST_MP_DECISION_DATA
	IMG_BUFFER	sFirstPassOutBestMultipassParamBuf[MAX_SOURCE_SLOTS_SL];  //!< Output Selectable Best MV Parameters of the First Pass
#endif
    IMG_BUFFER   sMBCtrlInParamsBuf[MAX_SOURCE_SLOTS_SL];                 //!< Input Parameters to the second pass

	/* these values set at picture level & written in at slice */
	IMG_UINT32	ui32IPEControl;         //!< common bits IPE control register for entire picture 
    IMG_UINT32  ui32PredCombControl;    //!< common bits of Predictor-combiner control register for entire picture
	IMG_BOOL	bCabacEnabled;          //!< FLAG to enable Cabac mode
    IMG_UINT32  ui32CabacBinLimit;      //!< Min Bin Limit after which the Topaz hardware would encode MB as IPCM
    IMG_UINT32  ui32CabacBinFlex;       //!< Max Flex-Limit, the Topaz-HW will encode MB as IPCM after (BinLimit+BinFlex)

	IMG_UINT32  ui32FirstPicFlags;
	IMG_UINT32  ui32NonFirstPicFlags;

	IMG_BOOL	bIsInterlaced;
	IMG_BOOL	bIsInterleaved;
	IMG_BOOL	bTopFieldFirst;
	IMG_BOOL	bArbitrarySO;
	IMG_UINT8	ui8SlicesPerPicture;
	IMG_UINT8	ui8DeblockIDC;
	IMG_UINT32	ui32KickSize;
	IMG_UINT32  ui32KicksPerBU;  
	IMG_UINT32	ui32VopTimeResolution;
	IMG_UINT32	ui32IdrPeriod;
	IMG_UINT32	ui32IntraCnt;
	IMG_BOOL    bMultiReferenceP;
	IMG_BOOL    bSpatialDirect;
	IMG_UINT8	ui8MPEG2IntraDCPrecision; //!< Only used in MPEG2, 2 bit field (0 = 8 bit, 1 = 9 bit, 2 = 10 bit and 3=11 bit precision). Set to zero for other encode standards.

	IMG_MV_SETTINGS sMVSettingsIdr;

	IMG_MV_SETTINGS sMVSettingsNonB[MAX_BFRAMES + 1];
	
	/*  | MVSetingsB0 | MVSetingsB1 | ... | MVSetings Bn |  */

	struct MEMORY_INFO_TAG* pMVSettingsBTable;						//!< three colocated vector stores (2 input and 1 output)
	struct MEMORY_INFO_TAG* pMVSettingsHierarchical;

	// Source slots
	IMG_FRAME *			apsSourceSlotBuff[MAX_SOURCE_SLOTS_SL];		//!< Source slots
	IMG_UINT32			aui32SourceSlotPOC[MAX_SOURCE_SLOTS_SL];	//!< POCs of frames in slots
	IMG_UINT8			ui8SlotsInUse;								//!< Number of source slots
	IMG_UINT8			ui8SlotsRequired;							//!< Number of source slots to be consumed
	IMG_BOOL			bSrcAllocInternally;						//!< True for internal source frame allocation
	IMG_FRAME_ARRAY		*psInternalSourceFrames;					//!< Frames placed in slots when using internal source frame allocation

	// Coded slots
	CODED_PACKAGE_HOST	*apsCodedPackage[MAX_CODED_PACKAGES];	// Collection of coded/header information
	IMG_BOOL			bCodedAllocInternally;						// True for internal coded frame allocation
	CODED_PACKAGE_HOST *apsInternalCodedPackage[MAX_CODED_PACKAGES];		// Frames placed in slots when using internal coded frame allocation

	IMG_UINT32			ui32FrameCount;
	IMG_UINT32			ui32FlushAtFrame;
	IMG_UINT32			ui32FlushedAtFrame;
	IMG_UINT32			ui32EncodeSent;
	IMG_UINT32			ui32EncodeRequested;
	IMG_UINT32			ui32FramesEncoded;
	IMG_BOOL			bEncoderIdle;		//!< Indicates that the encoder is waiting for data, Set to true at start of encode
	IMG_BOOL			bAborted;

	LIST_ITEM *			psRefFame;
	IMG_UINT32			ui32ReconPOC;
	IMG_UINT32			ui32NextRecon;

	struct MEMORY_INFO_TAG * psReconBuffer;
	struct MEMORY_INFO_TAG * psPatchedReconBuffer;

	IMG_RC_PARAMS		sRCParams;
	IMG_FRAME_TYPE		eFrameType;

	IMG_UINT32 ui32BuffersStatusReg;

	IMG_UINT32	ui32FCode;			    //!< value only used in MPEG4
	IMG_UINT8	ui8H263SourceFormat;

	IMG_BOOL	bInsertSeqHeader;
	IMG_BOOL	bOutputReconstructed;

	IMG_UINT32	ui32EncodePicProcessing;
	IMG_UINT8	ui8ExtraWBRetrieved;

    IMG_UINT8   ui8EnableSelStatsFlags;   //!< Flags to enable selective first-pass statistics gathering by the hardware. Bit 1 - First Stage Motion Search Data, Bit 2 - Best Multipass MB Decision Data, Bit 3 - Best Multipass Motion Vectors. (First stage Table 2 motion vectors are always switched on)

    IMG_BOOL    bEnableInpCtrl;     //!< Enable Macro-block input control
	IMG_BOOL	bEnableAIR;			//!< Enable Adaptive Intra Refresh
	IMG_INT32	i32NumAIRMBs;		//!< n = Max number of AIR MBs per frame, 0 = _ALL_ MBs over threshold will be marked as AIR Intras, -1 = Auto 10%
	IMG_INT32	i32AIRThreshold;	//!< n = SAD Threshold above which a MB is a AIR MB candidate,  -1 = Auto adjusting threshold
	IMG_INT16	i16AIRSkipCnt;		//!< n = Number of MBs to skip in AIR Table between frames, -1 = Random (0 - NumAIRMbs) skip between frames in AIR table

	IMG_BOOL	bEnableHostBias; 
	IMG_BOOL	bEnableHostQP;

	IMG_BOOL	bCustomScaling; 
	IMG_BOOL	bPpsScaling; 
	IMG_BOOL	bH2648x8Transform;
	IMG_BOOL	bH264IntraConstrained;
	IMG_UINT32	ui32VertMVLimit;
	IMG_UINT32			ui32IntraPredModes;
	IMG_BOOL16	bLimitNumVectors;
	IMG_BOOL16	bDisableBitStuffing;
	IMG_UINT8	ui8CodedSkippedIndex;
	IMG_UINT8	ui8InterIntraIndex;
	struct MEMORY_INFO_TAG* psMtxEncContextMem;
// SEI_INSERTION
	IMG_BOOL	bInsertHRDParams;
//
	IMG_UINT32 uChunksPerMb;
	IMG_UINT32 uMaxChunks;
	IMG_UINT32 uPriorityChunks;

	IMG_UINT8		ui8SourceSlotReserved;
	IMG_UINT8		ui8CodedPackageSlotReserved;
	IMG_HANDLE		sEncodePicSignal;

	IMG_UINT8		ui8HighestStorageNumber;


	IMG_UINT8		ui8VidCtxNum;


    IMG_BOOL        bEnableMvc;         //!< True if MVC is enabled. False by default
    IMG_UINT16      ui16MVCViewIdx;     //!< View Idx of this MVC view
	IMG_BOOL		bHighLatency;
	IMG_UINT32		uMBspS;

#if defined(HW_4_0)
	IMG_UINT8		ui8EncBitDepth;
	IMG_ENCODERESOLUTION eEncResolution;
#endif
	IMG_BOOL		bNoSequenceHeaders;
	IMG_UINT32		ui32NextSlice;
	IMG_BOOL		bAutoEncode;
	IMG_BOOL		bSliceLevel;
	IMG_BOOL		bCodedHeaderPerSlice;
#if defined(HW_4_0)
	IMG_BOOL8		b8Iipe0enable;
#endif	

	/* Scaler specific values */
	IMG_BOOL		bEnableScaler;
	IMG_UINT16		ui16CropLeft;
	IMG_UINT16		ui16CropRight;
	IMG_UINT16		ui16CropTop;
	IMG_UINT16		ui16CropBottom;
	IMG_UINT16		ui16SourceWidth;
	IMG_UINT16		ui16SourceFrameHeight;
	
#if SECURE_IO_PORTS
	IMG_BOOL			bSecureCtxInput;
	IMG_BOOL			bSecureCtxOutput;
#endif 

#if defined(HW_4_0)
	IMG_BOOL		bLLEnabled;							// Enable linked list mode
	IMG_UINT8		ui8LLCodedBuffersPerPackage;		// Number of coded buffer slots per list (linked list mode only)
	IMG_UINT32		ui32LLNodesPerCodedBuffer;			// Size of a linked list segment in 1024 byte units
#if !defined(DISABLE_BUFFER_UPDATE_ON_SLICE)
	IMG_UINT32		bLLBufferUpdateOnSliceMode;		// Enable buffer update on slice mode (no slice can be larger than a linked list segment)
#endif
	IMG_BOOL		bHwFifo;
#endif

	EXTERNAL_BUFFER_ASSOC asExternalBuffers[NUM_EXTERNAL_BUFFERS];
	IMG_BOOL		bLineCounter;		//!< Keep track of line counter activation

#if defined(HW_4_0)
	IMG_BOOL		bHardwareBlock;		//!< Use of the Hardware Block Interface (HBI)
#endif

} IMG_VIDEO_CONTEXT;

#endif



