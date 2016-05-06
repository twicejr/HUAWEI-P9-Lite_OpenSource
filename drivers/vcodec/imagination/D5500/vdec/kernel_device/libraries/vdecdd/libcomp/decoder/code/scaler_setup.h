/*!
 *****************************************************************************
 *
 * @File       scaler_setup.h
 * @Title      VDECDD Scaler Setup.
 * @Description    This file contains the VDECDD scaler setup prototypes.
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

#ifndef __SCALER_SETUP_H__
#define __SCALER_SETUP_H__

#include "img_defs.h"
#include "vdec_api.h"
#include "report_api.h"
#include "vxd.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FXDPNT_SCALER_CALC  //Define this for fixed point scaling calculations
							//comment for floating point
#ifdef FXDPNT_SCALER_CALC

/***********************************************************************************
* Fixed Point library and constants for calculation of scalling coefficients       *
* in kernel mode																   *
************************************************************************************
* The library has two levels of precision. For the pitch calculations we are using *
* 18.14 format (demical part represented by 14bits) and for coefficients           *
* calculations we are using the 20.11 format. This in order to meet the driver's   *
* specs and yet use no more than 32bits (it seems that not all linux kernels       *
* support 64bit division in kernel).											   *
* Driver currently wants coefficients in 2.6 format and pitch in 3.12 so the       *
* library has better precision in all cases and can keep up with need for more     *
* precision in the future. 
* In fixed point calculations addition (and substraction) are implemented as usual *
* and division and multiplication are implemented in the macros defined below.     *
* The DIV1 macro implements division with integers in the fixed point format (ie   *
* as the divider is integer we can just use it in normal form (not fixed point     *
* transformed) and so not multiply the number divided with the library constant)   *
* This allows to divide bigger numbers with the same 32bit variables.              *
* The macro FIXED transforms an integer into the fixed point format                *
* Some macros need also the level of precision that the numbers in the current     *
* calculation are using (HIGHP for 14bit LOWP for 11bit).                          *
* The other constants defined below are real numbers needed in the calculations    *
* in the fixed point format.                                                       *
* The library has made some assumptions (most of them in functions used to         *
* calculate scaler coefficients based on the input that these functions take in    *
* order to simplify tha calculations. Everything is documented inside the functions*
*                                                                                  *
* In 18.14 format library can hold from -131072 to 131071.9 in any intermediate    *
* step  and can hold a value as small as 0.00006103515625.                         *
* In 20.11 format library can hold from -104876 to 1048575.9 in any intermediate   *
* step and can hold a value as small as 0.00048828125                              * 
***********************************************************************************/
typedef IMG_INT32	FXDPNT_20p11;
typedef IMG_UINT32	UFXDPNT_21p11;
typedef IMG_INT32	FXDPNT_18p14;

#define PI_LOWP			6434L
#define HALF_PI_LOWP	3217L
#define DOUBLE_PI_LOWP	12868L

#define INV_BESSI0_FBETA	898L  	//From function --- scaler_CalcCoeffsSyncFunc() ----
									//fBeta = 2.0f;
									//fIBeta = 1.0f/(scaler_CalculateScalerCoeffsBessi0(fBeta));
									//This constant holds the value of fIBeta in 20.11 format

#define NUM0P9				5791L   //Number 0.9 in 20.11 format
#define NUM3P75				7680L	//Number 3.75 in 20.11 format

#define BESSI0_C0			9L		//Coefficients in --- scaler_CalculateScalerCoeffsBessi0()---
#define BESSI0_C1			74L		//function in 20.11 format
#define BESSI0_C2			545L
#define BESSI0_C3			2471L
#define BESSI0_C4			6328L
#define BESSI0_C5			7200L

#define LOWP				11
#define HIGHP				14

#define HIGH_TO_LOW(a)		(((a) + (1 << ((HIGHP) - (LOWP) - 1))) >> ((HIGHP) - (LOWP)))
#define FLOOR(a,digits)		((a) & (0xFFFFFFFFL << (digits)))
#define MUL(a,b,digits)		((((a)*(b))+(1<<((digits)-1)))>> (digits))

#define DIV1(a,b)			((a)/(b))   //Special division when divider has no fractional part
										//At this case the divider is divided with 1<<digits before
										//the division instead of multiplying the divident with 1<<digits

#define DIV(a,b,digits)		(((a) << (digits))/(b))
#define FIXED(a,digits)		((IMG_INT32)((a) * (1<<(digits))))

#endif


/*!
******************************************************************************
 This struct contains input and derived parameters for Scaling
******************************************************************************/
typedef struct
{
    VDEC_eVidStd                eVidStd;

    const VXD_sCoreProps      * psCoreProps;

    PIXEL_sPixelInfo          * psInPixelInfo;
    const PIXEL_sPixelInfo    * psOutPixelInfo;

    IMG_BOOL                    bFieldCoded;            // Field coded image
    IMG_BOOL                    bSeparateChromaPlanes;  // Separate planes for Y,U and V 

    IMG_UINT32                  ui32ReconWidth;         // Width of reconstructed image (without rounding)
    IMG_UINT32                  ui32ReconHeight;        // Height of reconstructed image (without rounding)
    IMG_UINT32                  ui32MbWidth;            // Width of reconstructed image in pixels (rounded up to nearest MB)
    IMG_UINT32                  ui32MbHeight;           // Height of reconstructed image in pixels (rounded up to nearest MB)
    IMG_UINT32                  ui32ScaleWidth;         // Width of scaled image (without rounding)
    IMG_UINT32                  ui32ScaleHeight;        // Height of scaled image (without rounding)

} SCALER_sConfig;


/*!
******************************************************************************
 This struct contains Scaler pitch parameters
******************************************************************************/
typedef struct
{
#ifdef FXDPNT_SCALER_CALC

    FXDPNT_18p14  iHorizLuma;
    FXDPNT_18p14  iVertLuma;
    FXDPNT_18p14  iHorizChroma;
    FXDPNT_18p14  iVertChroma;
#else
    IMG_FLOAT     fHorizLuma;
    IMG_FLOAT     fVertLuma;
    IMG_FLOAT     fHorizChroma;
    IMG_FLOAT     fVertChroma;
#endif

} SCALER_sPitch;


/*!
******************************************************************************
 This struct contains Scaler parameters prepared for hardware
******************************************************************************/
typedef struct
{
    IMG_UINT32  iVertPitch;
    IMG_UINT32  iVertStartPos;
    IMG_UINT32  iVertPitchChroma;
    IMG_UINT32  iVertStartPosChroma;
    IMG_UINT32  iHorzPitch;
    IMG_UINT32  iHorzStartPos;
    IMG_UINT32  iHorzPitchChroma;
    IMG_UINT32  iHorzStartPosChroma;
    IMG_UINT8   iFixedPointShift;

} SCALER_sParams;


/*!
******************************************************************************
 This struct contains Scaler filter selection
******************************************************************************/
typedef struct
{
    IMG_BOOL  bHorizBilinear;
    IMG_BOOL  bVertBilinear;

} SCALER_sFilter;


typedef struct
{
    IMG_UINT8       (*paui8HorizLuma)[16];
    IMG_UINT8       aui8HorizLumaCoeffs[4][16];

    IMG_UINT8       (*paui8HorizChroma)[16];
    IMG_UINT8       aui8HorizChromaCoeffs[4][16];

    IMG_UINT8       (*paui8VertLuma)[16];
    IMG_UINT8       aui8VertLumaCoeffs[4][16];

    IMG_UINT8       (*paui8VertChroma)[16];
    IMG_UINT8       aui8VertChromaCoeffs[4][16];

} SCALER_sCoeffs;



/*
******************************************************************************

 @Function              SCALER_GetScalerCmds

******************************************************************************/
extern IMG_RESULT
SCALER_GetScalerCmds(
    SCALER_sConfig            * psConfig,
    IMG_UINT32                * pui32PictCmds
);


#ifdef __cplusplus
}
#endif

#endif /* __SCALER_SETUP_H__   */
