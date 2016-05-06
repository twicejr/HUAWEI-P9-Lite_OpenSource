/*!
 *****************************************************************************
 *
 * @File       vc1fw_data_shared.h
 * @Title      Public data structures for the VC1 parser firmware module
 * @Description    Public data structures for the VC1 parser firmware modules
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

#ifdef USE_SHARING
#endif

#ifndef _VC1FW_DATA_H_
#define _VC1FW_DATA_H_

#include "vdecfw_share.h"

#include "vdecfw_share.h"
#include <img_types.h>
#include "vdecfw.h"


//Maximum number pictures inside the Decoded Picture Buffer
#define VC1FW_MAX_DPB_SIZE     (2)

//Maximum number of bitplanes in a picture
#define VC1FW_MAX_NUM_BITPLANES (3)

//! Maximum number of pan/scan windows per frame (VC1 Specification: 7.1.1.20)
#define VC1FW_MAX_PANSCAN (4)

/*!
******************************************************************************
 This type defines the picture structure.
******************************************************************************/
typedef enum
{
    VC1FW_TYPE_NOT_PARSED                   = 0,        //!< No valid picture
    VC1FW_TYPE_TOP                          = 1,        //!< Picture contains the top (even) lines of the frame
    VC1FW_TYPE_BOTTOM                       = 2,        //!< Picture contains the bottom (odd) lines of the frame
    VC1FW_TYPE_FRAME                        = 3,        //!< Picture contains the entire frame
    VC1FW_TYPE_PAIR                         = 4,        //!< Picture contains top and bottom lines of the frame
    VC1FW_TYPE_MAX

} VC1FW_ePictureType;

typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LumScale1);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LumShift1);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LumScale2);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LumShift2);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PrevIC);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BackIC);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PrevLumShift);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PrevLumScale);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BackLumShift);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BackLumScale);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8ModeConfigComb);
}VC1FW_sIntensityCompensation;

/*!
******************************************************************************

 Information related to Intensity compensation parameter storage

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8LumScale);                    //!< 1st lumscale parameters specified for this field
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8LumShift);                    //!< 1st lumshift parameters specified for this field
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8FieldApplied[2]);             //!< field that applied the intensity compensation
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8NumberOfICCompensations);     //!< number of times this field is intensity compensated

} VC1FW_sICStorage;

/*!
******************************************************************************

 This describes an VC1 picture. It is part of the Context data

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer sPrimary;                       //!< Primary (reconstructed) picture buffers
    VDECFW_sImageBuffer sAlternate;                     //!< Secondary (alternative) picture buffers

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsSize);                        //!< Macroblock parameters buffer size
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);                 //!< Macroblock parameters base address for the picture

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, VC1FW_ePictureType, ePictureType);                    //!< Picture type

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransactionId);                       //!< Transaction Id

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSecondField);                              //!< Flag to indicate if this is the second field (interlaced only)
    //IMG_BOOL bReference;                                //!< Flag to indicate if the picture is a reference picture
    //IMG_BOOL bPictureRangeReduced;
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bTopFieldFirst);                             //!< Flag to indicate the arrangement of fields within the reference frame
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRangeRedFrm);                               //!< Flag to indicate whether range reduction is present within the reference frame
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8FrameCodingMode);                        //!< Frame coding mode of reference frame

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32ReferenceFrameDistance);               //!< Reference frame distance

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32BitPlanesBufferBaseAddress[VC1FW_MAX_NUM_BITPLANES]); //!< 

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8DisplayFlags);               //!< Flags for this picture for the display process
} VC1FW_sPicture;

/*!
******************************************************************************

 This describes the SPS header data required by the VC1 firmware 
 that should be supplied by the Host.

******************************************************************************/
typedef struct
{
    //Syntax elements from SPS
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bInterlace);                    //<                                                                                   
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8Profile);                    //<                                                                                                                                                                   
    //IMG_BOOL   bRefDistFlag;                  //<                                                                                   
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bLoopFilter);                   //<                                                                                   
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bFastUVMC);                     //< 6.2.6 (AP EP)/J.1.11 Fast UV Motion Compensation Flag (FASTUVMC)                              

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRangeMappingLuma);             //< 6.2.15 Range Mapping Luma Flag (RANGE_MAPY_FLAG)                                              
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8RangeMapLuma);               //< 6.2.15.1 Range Mapping Luma (RANGE_MAPY)                                                      
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRangeMappingChroma);           //< 6.2.16 Range Mapping Color-Difference Flag (RANGE_MAPUV_FLAG)                                 
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8RangeMapChroma);             //< 6.2.16.1 Range Mapping Chroma (RANGE_MAPUV)                                                   

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSynchronisationMarker);        //< J.1.16 Syncmarker Flag (SYNCMARKER) Main profile feature only                     

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bFrameInterpolation);           //< 6.1.11/J.1.20 Frame Interpolation Flag (FINTERPFLAG)                              
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8Quantizer);                  //< 6.2.11 (AP EP)/J.1.19 Quantizer (QUANTIZER) Incorporates bSequenceQuantizerExplicit 
                                              //    and PQUANTIZER/bFrameQuantizerExplicit for WMV9 simple/main                       

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRangeReduction);               //< J.1.17 Range Reduction Flag (RANGERED) Main profile feature only                  
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bMultiResolutions);             //< J.1.10 MultiResolution Coding (MULTIRES)                                          
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bX8INTRA);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bFastTTX);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8MaxConsecutiveBFrames);      //< J.1.18 Maximum number of consecutive B frames (MAXBFRAMES)                        
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bDCTTableSwitch);               //< Labelled as Reserved5 in VC1 specification                                        

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPostProcessing);               //< 6.1.5 Postprocessing Flag (POSTPROCFLAG)                                          
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPulldown);                     //< 6.1.8 Pulldown Flag (PULLDOWN)                                                    
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bFrameCounter);                 //< 6.1.10 Frame Counter Flag (TFCNTRFLAG)                                            
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bProgressiveSegmentedFrame);    //< 6.1.13 Progressive Segmented Frame (PSF)                                          
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPanScanPresent);               //< 6.2.3 Pan Scan Present Flag (PANSCAN_FLAG)                                        
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRefFrameDistance);             //< 6.2.4 Reference Frame Distance Flag (REFDIST_FLAG)                                

    //Also used for registers/commands
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bExtendedMV);                   //!< 6.2.7 (AP EP)/J.1.12 Extended Motion Vector Flag (bExtendedMV) (EXTENDED_MV)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8DQuant);                     //< 6.2.8 (AP EP)/J.1.13 Macroblock Quantization Flag (DQUANT)                        
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bVSTransform);                  //< 6.2.9 (AP EP)/J.1.14 Variable Sized Transform Flag (VSTRANSFORM)                  
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bOverlapTransform);             //< 6.2.10 (AP EP)/J.1.15 Overlapped Transform Flag (OVERLAP)                         
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bExtendedDifferentialMotionVectorRange);//< 6.2.14 Extended Differential Motion Vector Range Flag (EXTENDED_DMV)      

} VC1FW_sSequencePS;

/*!
******************************************************************************

 This describes the HW specific SPS header data required by the VC1
 firmware that should be supplied by the Host.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bAdvancedProfile);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RegEntdecFEControl);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32RegEntdecBEControl);
} VC1FW_sDdSequenceSPS;

/*!
******************************************************************************

 This describes the VC1 parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the VC1 firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer         sPrimary;           //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer         sAlternate;         //!< buffer base addresses for alternate output

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FrameSize);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bEmulationPrevention);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16CodedWidth);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16CodedHeight);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32VlcIndexSize);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsSize);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32BitPlanesBufferBaseAddress[VC1FW_MAX_NUM_BITPLANES]);

    VC1FW_sDdSequenceSPS sDdSequenceSPS;    //!< HW specific Sequence Parameter Set data
} VC1FW_sHeaderData;

/*!
******************************************************************************

 This describes the VC1 parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
     VC1FW_sPicture  asDpb[VC1FW_MAX_DPB_SIZE];      //!< Decoded Picture Buffer

     VC1FW_sSequencePS sSPS; //!< Sequence Parameter Set data;

     VC1FW_sICStorage sStorParams[2][2];                       //!< IC parameters stored ready to calculate parameters for subsequent pictures

     VC1FW_sPicture sNewRefPic;
     VC1FW_sPicture sOldRefPic;
     VC1FW_sPicture sCurrentPic;

     //Previous Intensity compensation Derived Parameters
     VC1FW_sIntensityCompensation sPrevIntensityCompensation;

     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32NumMBX);                             //!< number of MBs across picture width
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32NumMBY);                             //!< number of MBs in picture height
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSecondField);

     // Field Code Material support variables
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastLumaRecon);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChromaRecon);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChroma2Recon);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastLumaAlter);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChromaAlter);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChroma2Alter);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastMbParamsSize);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastMbParamsBaseAddress);

     VDECFW_sImageBuffer          sLastPrimary;
     VDECFW_sImageBuffer          sLastAlternative;

     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8ModeConfig[2]);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8LumScale1[2]);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8LumShift1[2]);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8LumScale2[2]);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8LumShift2[2]);

     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8PrevDisplayFlags);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPrevDisplay);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPrevRelease);

     //Previous I/P/BI RNDCTRL
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPreviousNotBRNDCTRL);

     //The standard does not specify what should happen for I/I, I/P, P/I and P/P pictures.
     //It seems that we need to save the value and restore it from the context for the following picture.
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PreviousREFDIST);

     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRef1RangeRed);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRef2RangeRed);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bTFF_FWD);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bTFF_BWD);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8FCM_REF0);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8FCM_REF1);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8FCM_REF2);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8REFDIST_BWD);

     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRANGEREDFRM);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bTFF);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8FCM);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8FPTYPE);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bRNDCTRL);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8BPictureFraction);
     IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8CONDOVER);

} VC1FW_sContextData;

#endif

