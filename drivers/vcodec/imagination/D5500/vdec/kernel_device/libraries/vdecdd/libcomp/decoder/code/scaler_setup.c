/*!
 *****************************************************************************
 *
 * @File       scaler_setup.c
 * @Title      VDECDD Scaler Setup.
 * @Description    This file contains the VDECDD Scaler command generation.
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

#include "scaler_setup.h"
#include "vxd_int.h"

#ifndef SYSBRG_BRIDGING

#else
    #include "msvdx_ext.h"
#endif

#if  !defined(FXDPNT_SCALER_CALC)
#include <math.h>   /* fabs, exp, sqrt, sin - to calc scaler coeffs */
#endif

#define DECODER_ROUND_UP_EVEN(s, f)             (s + ((f) ? (s % 2) : 0))


/*!
******************************************************************************
 This struct contains input and derived parameters for Scaling
******************************************************************************/
typedef struct
{
    SCALER_sConfig            * psConfig;

    PIXEL_sPixelInfo          *  psInLoopPixelInfo;
    const PIXEL_sPixelInfo    *  psOutLoopPixelInfo;

    SCALER_sPitch               sPitch;
    SCALER_sFilter              sFilter;
    SCALER_sParams              sParams;
    SCALER_sCoeffs              sCoeffs;

} SCALER_sScaleCtx;



#if  !defined(FXDPNT_SCALER_CALC)    /* Floats are not allowed in the kernel */
/*
******************************************************************************

 @Function              scaler_CalculateScalerCoeffsBessi0

******************************************************************************/
static IMG_FLOAT
scaler_CalculateScalerCoeffsBessi0(
    IMG_FLOAT  x
)
{
    IMG_FLOAT ax,ans;
    IMG_FLOAT y;

    ax=(IMG_FLOAT)fabs(x);
    if (ax < 3.75)
    {
        y=(IMG_FLOAT)(x/3.75);
        y*=y;
        ans=(IMG_FLOAT)(1.0+y*(3.5156229+y*(3.0899424+y*(1.2067492
            +y*(0.2659732+y*(0.360768e-1+y*0.45813e-2))))));
    }
    else
    {
        y=(IMG_FLOAT)(3.75/ax);
        ans=(IMG_FLOAT)((IMG_FLOAT)((exp(ax)/sqrt(ax))*(0.39894228+y*(0.1328592e-1
            +y*(0.225319e-2+y*(-0.157565e-2+y*(0.916281e-2
            +y*(-0.2057706e-1+y*(0.2635537e-1+y*(-0.1647633e-1
            +y*0.392377e-2))))))))));
    }

    return ans;
}


/*
******************************************************************************

 @Function              scaler_CalcCoeffsSyncFunc

 @Description

******************************************************************************/
static IMG_FLOAT
scaler_CalcCoeffsSyncFunc(
    IMG_FLOAT  fi,
    IMG_FLOAT  ft,
    IMG_FLOAT  fI,
    IMG_FLOAT  fT,
    IMG_FLOAT  fScale
)
{
    const IMG_FLOAT cfPI = 3.1415926535897f;
    IMG_FLOAT fx, fIBeta, fBeta, fTempval, fSincfunc;

    /* Kaiser window */
    fx = ((ft*fI + fi)-(fT*fI/2))/(fT*fI/2);
    fBeta = 2.0f;
    fIBeta = 1.0f/(scaler_CalculateScalerCoeffsBessi0(fBeta));
    fTempval = scaler_CalculateScalerCoeffsBessi0(fBeta*(IMG_FLOAT)sqrt(1.0f-fx*fx)) * fIBeta;

    /* Sinc function    */
    if ((fT/2 - ft - fi/fI) == 0)
    {
        fSincfunc = 1.0f;
    }
    else
    {
        fx=0.9f*fScale*cfPI*(fT/2 - (ft + fi/fI));
        fSincfunc=(IMG_FLOAT)(sin(fx)/fx);
    }

    return fSincfunc*fTempval;
}

#define SCC_MAXTAP              9
#define SCC_MAXINTPT            16

/*
******************************************************************************

 @Function              scaler_CalcCoeff

 @Description

 Calculates MSVDX scaler coefficients

 @Input     fPitch      :   Scale pitch

 @Output    Table       :  Table of coefficients

 @Input     I           :   Number of intpt? (   table dimension)

 @Input     T           :   Number of taps      (table dimension)


******************************************************************************/
static IMG_VOID
scaler_CalcCoeff(
    IMG_FLOAT   fPitch,
    IMG_UINT8   Table[SCC_MAXTAP][SCC_MAXINTPT],
    IMG_UINT32  I,
    IMG_UINT32  T
)
{
    /* Due to the nature of the function we will only ever want to calculate the first half of the    */
    /* taps and the middle one (is this really a tap ?) as the seconda half are derived from the    */
    /* first half as the function is symetrical.                                                    */

    IMG_FLOAT    fScale = 1.0f/fPitch;
    IMG_UINT32    i, t;
    IMG_FLOAT    flTable[SCC_MAXTAP][SCC_MAXINTPT]={{0.0}, {0.0}};
    IMG_INT32    nTotal;
    IMG_FLOAT    ftotal;
    IMG_INT32    val;
    IMG_INT32    mT, mI; /* mirrored / middle Values for I and T */

    if (fScale>1.0f)
    {
        fScale=1.0f;
    }
    for (i=0;i<I;i++)
    {
        for (t=0;t<T;t++)
        {
            flTable[t][i]=0.0;
        }
    }

    for (i=0;i<I;i++)
    {
        for (t=0;t<T;t++)
        {
            flTable[t][i]= scaler_CalcCoeffsSyncFunc(
                (IMG_FLOAT) i, (IMG_FLOAT) t,
                (IMG_FLOAT) I, (IMG_FLOAT) T, fScale);
        }
    }

    if (T>2)
    {
        for (t=0;t<((T/2)+(T%2));t++)
        {
            for (i=0;i<I;i++)
            {
                /* copy the table around the centrepoint */
                mT = ((T-1)-t)+(I-i)/I;
                mI = (I-i)%I;
                if (((IMG_UINT32)mI<I) && ((IMG_UINT32)mT<T) &&
                    ((t<((T/2)+(T%2)-1)) || ((I-i)>((T%2)*(I/2)))))
                {
                    flTable[mT][mI]=flTable[t][i];
                }
            }
        }

        /* the middle value */
        mT = T/2;
        if ((T%2) != 0)
        {
            mI = I/2;
        }
        else
        {
            mI = 0;
        }
        flTable[mT][mI]= scaler_CalcCoeffsSyncFunc(
            (IMG_FLOAT) mI, (IMG_FLOAT) mT,
            (IMG_FLOAT) I, (IMG_FLOAT) T, fScale);
    }

    /* normalize this interpolation point, and convert to 2.6 format trucating the result    */
    for (i=0;i<I;i++)
    {
        nTotal=0;
        for (ftotal=0,t=0;t<T;t++)
        {
            ftotal+=flTable[t][i];
        }
        for (t=0;t<T;t++)
        {
            val=(IMG_INT32) ((flTable[t][i]*64.0f)/ftotal);
            Table[t][i]=(IMG_UINT8) val;
            nTotal+=val;
        }
        if ((i<=(I/2)) || (T<=2)) /* normalize any floating point errors */
        {
            nTotal-=64;
            if ((i==(I/2)) && (T > 2))
            {
                nTotal/=2;
            }

            /* subtract the error from the I Point in the first tap */
            /* ( this will not get mirrored, as it would go off the end ). */
            Table[0][i]=(IMG_UINT8) (Table[0][i]-(IMG_UINT8) nTotal);
        }
    }

    /* copy the normalised table around the centrepoint */
    if (T>2)
    {
        for (t=0;t<((T/2)+(T%2));t++)
        {
            for (i=0;i<I;i++)
            {
                mT = ((T-1)-t)+(I-i)/I;
                mI = (I-i)%I;
                if (((IMG_UINT32)mI<I) && ((IMG_UINT32)mT<T) && ((t<((T/2)+(T%2)-1)) || ((I-i)>((T%2)*(I/2)))))
                {
                    Table[mT][mI]=Table[t][i];
                }
            }
        }
    }
}

#else
/*
******************************************************************************

 @Function              FXDPNT_sqrt

 Square root for fixed point calculations

******************************************************************************/
static FXDPNT_20p11
FXDPNT_sqrt(
    FXDPNT_20p11  x
)
{
    FXDPNT_20p11 result = x/2 + 1, result_sq = -1;

    while((result_sq - result > 1) || (result - result_sq > 1))
    {
        //find sqrt using bisection function gn+1^2 = (g^2 - v)/2
        //stop when they have difference 1 or les (because for some numbers can not hit 0)
        //still is more than good enough
        result_sq = result;
        result = DIV1((DIV(x,result,LOWP) + result),2);

    }
    return result;

}
/*
******************************************************************************

 @Function              FXDPNT_sin

 Sin function for fixed point calculations

******************************************************************************/
static FXDPNT_20p11
FXDPNT_sin(
    FXDPNT_20p11  i
)
{
    UFXDPNT_21p11 x;    //Making the value unsigned for the intermediate calculations
                        //gives one more bit so the value x^7 does not overflow!

    IMG_INT32 sign = 1;


    //Translate all input values to 0-Pi
    if(i < 0)
    {
        x = (-1)*i;
        sign = -1;
    }
    else
    {
        x = i;
    }
    if(x > DOUBLE_PI_LOWP)
    {
        x = x - MUL(FLOOR(DIV(x,DOUBLE_PI_LOWP,LOWP),LOWP),DOUBLE_PI_LOWP,LOWP);
    }
    if(x > PI_LOWP)
    {
        x -= PI_LOWP;
        sign *= -1;
    }
    if(x > HALF_PI_LOWP)
        x =  PI_LOWP - x;

    //using Taylor series sin = x - x^3/3! + x^5/5! - x^7/7!
    x = x - DIV1(MUL(MUL(x,x,LOWP),x,LOWP),6L) + DIV1(MUL(MUL(MUL(MUL(x,x,LOWP),x,LOWP),x,LOWP),x,LOWP),120L)
        - DIV1(MUL(MUL(MUL(MUL(MUL(MUL(x,x,LOWP),x,LOWP),x,LOWP),x,LOWP),x,LOWP),x,LOWP),5040L);

    return sign*x;
}
/*
******************************************************************************

 @Function              scaler_CalculateScalerCoeffsBessi0

******************************************************************************/
static FXDPNT_20p11
scaler_CalculateScalerCoeffsBessi0(
    FXDPNT_20p11  x
)
{
    FXDPNT_20p11 y;

    //ax=(IMG_FLOAT)fabs(x); Don't need this ax is always positive and also x <= 2
    //if (ax < 3.75)
    //{
        y = DIV(x,NUM3P75,LOWP);
        y = MUL(y,y,LOWP);
        /*
        This
            ans=(IMG_FLOAT)(1.0+y*(3.5156229+y*(3.0899424+y*(1.2067492+y*(0.2659732+y*(0.360768e-1+y*0.45813e-2))))));
        Expands to
            ans = 1 + 0.0045813*(y^6) + 0.0360768*(y^5) + 0.265973*(y^4) + 1.20675*(y^3) + 3.08994*(y^2) + 3.51562*y

            for 0 < x <= 2  0 < y <= 0.28 and  1 <= ans <= 2.25
        */
        return FIXED(1,LOWP) + MUL(MUL(MUL(MUL(MUL(MUL(y,y,LOWP),y,LOWP),y,LOWP),y,LOWP),y,LOWP),BESSI0_C0,LOWP) +
                        MUL(MUL(MUL(MUL(MUL(y,y,LOWP),y,LOWP),y,LOWP),y,LOWP),BESSI0_C1,LOWP) +
                        MUL(MUL(MUL(MUL(y,y,LOWP),y,LOWP),y,LOWP),BESSI0_C2,LOWP) +
                        MUL(MUL(MUL(y,y,LOWP),y,LOWP),BESSI0_C3,LOWP) +
                        MUL(MUL(y,y,LOWP),BESSI0_C4,LOWP) +
                        MUL(y,BESSI0_C5,LOWP);

    //}
    /*
    else
    {
        y=(IMG_FLOAT)(3.75/ax);
        ans=(IMG_FLOAT)((IMG_FLOAT)((exp(ax)/sqrt(ax))*(0.39894228+y*(0.1328592e-1
            +y*(0.225319e-2+y*(-0.157565e-2+y*(0.916281e-2
            +y*(-0.2057706e-1+y*(0.2635537e-1+y*(-0.1647633e-1
            +y*0.392377e-2))))))))));
    }
    return ans;
    */
}


/*
******************************************************************************

 @Function              scaler_CalcCoeffsSyncFunc

 @Description

******************************************************************************/
static FXDPNT_20p11
scaler_CalcCoeffsSyncFunc(
    FXDPNT_20p11  i,
    FXDPNT_20p11  t,
    FXDPNT_20p11  I,
    FXDPNT_20p11  T,
    FXDPNT_20p11  Scale
)
{
    //const FIXED_20_11 cPI = 6434;
    FXDPNT_20p11 x, Tempval, Sincfunc;

    /* Kaiser window */

    /*   fx = ((ft*fI + fi)-(fT*fI/2))/(fT*fI/2);
     *   fI = 16, fT = 4, 0 <= fi < 16, 0 <= ft < 4,
     *   so -1 <= fx <= 0.98
     * This assumption is used in scaler_CalculateScalerCoeffsBessi0()
     * to simplify the calculations ie if (ax < 3.75) else ... ax is always < 3.75 */

    x = DIV(MUL((MUL(t,I,LOWP) + i),FIXED(2,LOWP),LOWP),MUL(T,I,LOWP),LOWP) - FIXED(1,LOWP);



    //fBeta = 2.0f;
    //fIBeta = 1.0f/(scaler_CalculateScalerCoeffsBessi0(fBeta));
    //fTempval = scaler_CalculateScalerCoeffsBessi0(fBeta*(IMG_FLOAT)sqrt(1.0f-fx*fx)) * fIBeta;

    Tempval = scaler_CalculateScalerCoeffsBessi0(2L*FXDPNT_sqrt(FIXED(1,LOWP) - MUL(x,x,LOWP)));
    Tempval = MUL(Tempval,INV_BESSI0_FBETA,LOWP);

    /* fIBeta = 0.44 and scaler_CalculateScalerCoeffsBessi0 < 2.25 so Tempval <= 1 */


    /* Sinc function    */
    if ((DIV(T,FIXED(2,LOWP),LOWP) - t - DIV(i,I,LOWP)) == 0)
    {
        Sincfunc = FIXED(1,LOWP);
    }
    else
    {
        x=MUL(MUL(NUM0P9,Scale,LOWP),(DIV(T,FIXED(2,LOWP),LOWP) - (t + DIV(i,I,LOWP))),LOWP);

        /* x > 0.17 so Sincfunc < 5.66 so return value < 5.66 */

        Sincfunc=DIV(FXDPNT_sin(x),x,LOWP);
    }

    return MUL(Sincfunc,Tempval,LOWP);
}

#define SCC_MAXTAP              9
#define SCC_MAXINTPT            16

/*
******************************************************************************

 @Function              scaler_CalcCoeff

 @Description

 Calculates MSVDX scaler coefficients

 @Input     fPitch      :   Scale pitch

 @Output    Table       :  Table of coefficients

 @Input     I           :   Number of intpt? (   table dimension)

 @Input     T           :   Number of taps      (table dimension)


******************************************************************************/
static IMG_VOID
scaler_CalcCoeff(
    FXDPNT_18p14  iPitch,
    IMG_UINT8     Table[SCC_MAXTAP][SCC_MAXINTPT],
    IMG_UINT32    I,
    IMG_UINT32    T
)
{
    /* Due to the nature of the function we will only ever want to calculate the first half of the  */
    /* taps and the middle one (is this really a tap ?) as the second half are derived from the     */
    /* first half as the function is symetrical.                                                    */

    FXDPNT_20p11  iScale = HIGH_TO_LOW(DIV(FIXED(1,HIGHP),iPitch,HIGHP));
    IMG_UINT32    i, t;
    FXDPNT_20p11  iTable[SCC_MAXTAP][SCC_MAXINTPT]={{0}, {0}};
    IMG_INT32     nTotal;
    FXDPNT_20p11  itotal;
    IMG_INT32     val;
    IMG_INT32     mT, mI; /* mirrored / middle Values for I and T */

    if (iScale>FIXED(1,LOWP))
    {
        iScale=FIXED(1,LOWP);
    }
    for (i=0;i<I;i++)
    {
        for (t=0;t<T;t++)
        {
            iTable[t][i]=0;
        }
    }

    for (i=0;i<I;i++)
    {
        for (t=0;t<T;t++)
        {
            iTable[t][i]= scaler_CalcCoeffsSyncFunc(FIXED(i,LOWP),  FIXED(t,LOWP), FIXED(I,LOWP), FIXED(T,LOWP), iScale);
        }
    }

    if (T>2)
    {
        for (t=0;t<((T/2)+(T%2));t++)
        {
            for (i=0;i<I;i++)
            {
                /* copy the table around the centrepoint */
                mT = ((T-1)-t)+(I-i)/I;
                mI = (I-i)%I;
                if (((IMG_UINT32)mI<I) && ((IMG_UINT32)mT<T) &&
                    ((t<((T/2)+(T%2)-1)) || ((I-i)>((T%2)*(I/2)))))
                {
                    iTable[mT][mI]=iTable[t][i];
                }
            }
        }

        /* the middle value */
        mT = T/2;
        if ((T%2) != 0)
        {
            mI = I/2;
        }
        else
        {
            mI = 0;
        }
        iTable[mT][mI]= scaler_CalcCoeffsSyncFunc(FIXED(mI,LOWP), FIXED(mT,LOWP), FIXED(I,LOWP), FIXED(T,LOWP), iScale);
    }

    /* normalize this interpolation point, and convert to 2.6 format trucating the result    */
    for (i=0;i<I;i++)
    {
        nTotal=0;
        for (itotal=0,t=0;t<T;t++)
        {
            /* Max value for scaler_CalcCoeffsSyncFunc is around 5.66 so 64 of them is 311
               so it will not overflow. */
            itotal+=iTable[t][i];
        }
        for (t=0;t<T;t++)
        {

            //val=(IMG_INT32) ((flTable[t][i]*64.0f)/ftotal);
            val = DIV(iTable[t][i],itotal,LOWP);
            //val += (1 << 4);
            val /= 32;  //Truncate to 2.6 format;
            Table[t][i]=(IMG_UINT8) val;
            nTotal+=val;
        }
        if ((i<=(I/2)) || (T<=2)) /* normalize any floating point errors */
        {
            nTotal-=64;
            if ((i==(I/2)) && (T > 2))
            {
                nTotal/=2;
            }

            /* subtract the error from the I Point in the first tap */
            /* ( this will not get mirrored, as it would go off the end ). */
            Table[0][i]=(IMG_UINT8) (Table[0][i]-(IMG_UINT8) nTotal);
        }
    }

    /* copy the normalised table around the centrepoint */
    if (T>2)
    {
        for (t=0;t<((T/2)+(T%2));t++)
        {
            for (i=0;i<I;i++)
            {
                mT = ((T-1)-t)+(I-i)/I;
                mI = (I-i)%I;
                if (((IMG_UINT32)mI<I) && ((IMG_UINT32)mT<T) && ((t<((T/2)+(T%2)-1)) || ((I-i)>((T%2)*(I/2)))))
                {
                    Table[mT][mI]=Table[t][i];
                }
            }
        }
    }
}

#endif
/*
******************************************************************************

 @Function              scaler_GetCoeff

******************************************************************************/
static IMG_RESULT
scaler_GetCoeff(
    SCALER_sScaleCtx  * psScaler,
    SCALER_sCoeffs    * psScalerCoeffs
)
{
    SCALER_sPitch * psPitch = &psScaler->sPitch;

    IMG_MEMSET(psScalerCoeffs, 0, sizeof(*psScalerCoeffs));

#ifdef FXDPNT_SCALER_CALC
    if (psPitch->iHorizLuma > FIXED(1,HIGHP))
    {
        scaler_CalcCoeff(
            psPitch->iHorizLuma,
            psScalerCoeffs->aui8HorizLumaCoeffs,
            16,
            4);
#else
    if (psPitch->fHorizLuma > 1)
    {
        scaler_CalcCoeff(
            psPitch->fHorizLuma,
            psScalerCoeffs->aui8HorizLumaCoeffs,
            16,
            4);
#endif
        psScalerCoeffs->paui8HorizLuma = psScalerCoeffs->aui8HorizLumaCoeffs;
    }


#ifdef FXDPNT_SCALER_CALC
    if ((psPitch->iHorizChroma > FIXED(1,HIGHP) &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YUYV8888 &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YVYU8888) ||
        (psPitch->iHorizLuma > FIXED(1,HIGHP) &&
        (psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YUYV8888 ||
        psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YVYU8888)))
    {
        if (psPitch->iHorizLuma != psPitch->iHorizChroma)
        {
            scaler_CalcCoeff(
                psPitch->iHorizChroma,
                psScalerCoeffs->aui8HorizChromaCoeffs,
                16,
                4);
#else
    if ((psPitch->fHorizChroma > 1 &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YUYV8888 &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YVYU8888) ||
        (psPitch->fHorizLuma > 1 &&
        (psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YUYV8888 ||
        psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YVYU8888)))
    {
        if (psPitch->fHorizLuma != psPitch->fHorizChroma)
        {
            scaler_CalcCoeff(
                psPitch->fHorizChroma,
                psScalerCoeffs->aui8HorizChromaCoeffs,
                16,
                4);
#endif

            psScalerCoeffs->paui8HorizChroma = psScalerCoeffs->aui8HorizChromaCoeffs;
        }
        else
        {
            // No specific chroma coefficients, use the luma.
            psScalerCoeffs->paui8HorizChroma = psScalerCoeffs->aui8HorizLumaCoeffs;
        }
    }


#ifdef FXDPNT_SCALER_CALC
    if (psPitch->iVertLuma > FIXED(1,HIGHP))
    {
        scaler_CalcCoeff(
            psPitch->iVertLuma,
            psScalerCoeffs->aui8VertLumaCoeffs,
            16,
            4);
#else
    if (psPitch->fVertLuma > 1)
    {
        scaler_CalcCoeff(
            psPitch->fVertLuma,
            psScalerCoeffs->aui8VertLumaCoeffs,
            16,
            4);
#endif
        psScalerCoeffs->paui8VertLuma = psScalerCoeffs->aui8VertLumaCoeffs;
    }



#ifdef FXDPNT_SCALER_CALC
    if ((psPitch->iVertChroma > FIXED(1,HIGHP) &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YUYV8888 &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YVYU8888) ||
        (psPitch->iVertLuma > FIXED(1,HIGHP) &&
        (psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YUYV8888 ||
        psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YVYU8888)))
    {
        if (psPitch->iVertLuma != psPitch->iVertChroma)
        {
            scaler_CalcCoeff(
                psPitch->iVertChroma,
                psScalerCoeffs->aui8VertChromaCoeffs,
                16,
                4);
#else
    if ((psPitch->fVertChroma > 1 &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YUYV8888 &&
        psScaler->psOutLoopPixelInfo->ePixelFormat != IMG_PIXFMT_YVYU8888) ||
        (psPitch->fVertLuma > 1 &&
        (psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YUYV8888 ||
        psScaler->psOutLoopPixelInfo->ePixelFormat == IMG_PIXFMT_YVYU8888)))
    {
        if (psPitch->fVertLuma != psPitch->fVertChroma)
        {
            scaler_CalcCoeff(
                psPitch->fVertChroma,
                psScalerCoeffs->aui8VertChromaCoeffs,
                16,
                4);
#endif
            psScalerCoeffs->paui8VertChroma = psScalerCoeffs->aui8VertChromaCoeffs;
        }
        else
        {
            psScalerCoeffs->paui8VertChroma = psScalerCoeffs->aui8VertLumaCoeffs;
        }
    }

    return IMG_SUCCESS;
}


/*
******************************************************************************

 @Function              scaler_GetFilterType

 Bilinear filter is used when pitch > 2 for chroma downsampling and always when
 output format is packed 422. Luma pitch is used for chroma samples when bilinear
 filter is used.

 @Input         psScaler : Pointer to scaler properties.

******************************************************************************/
static IMG_RESULT
scaler_GetFilterType(
    SCALER_sScaleCtx *  psScaler
)
{
    psScaler->sFilter.bHorizBilinear = IMG_FALSE;
    psScaler->sFilter.bVertBilinear = IMG_FALSE;

    // Bi-linear filter is always used with upsampling to packed 422.
    if (psScaler->psOutLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_422 &&
        psScaler->psOutLoopPixelInfo->ui32NoPlanes == 1)
    {
        psScaler->sFilter.bHorizBilinear = IMG_TRUE;
        psScaler->sFilter.bVertBilinear = IMG_TRUE;
    }
    else if (psScaler->psInLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_444 &&
             psScaler->psOutLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_420)
    {

#ifdef FXDPNT_SCALER_CALC

        if (psScaler->sPitch.iHorizLuma > FIXED(2,HIGHP))
        {
            psScaler->sFilter.bHorizBilinear = IMG_TRUE;
        }
        if (psScaler->sPitch.iVertLuma > FIXED(2,HIGHP))
        {
            psScaler->sFilter.bVertBilinear = IMG_TRUE;
        }
#else
        if (psScaler->sPitch.fHorizLuma > 2)
        {
            psScaler->sFilter.bHorizBilinear = IMG_TRUE;
        }
        if (psScaler->sPitch.fVertLuma > 2)
        {
            psScaler->sFilter.bVertBilinear = IMG_TRUE;
        }
#endif

    }
    else if (psScaler->psInLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_444 &&
             psScaler->psOutLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_422)
    {
#ifdef FXDPNT_SCALER_CALC

        if (psScaler->sPitch.iHorizLuma > FIXED(2,HIGHP))
        {
            psScaler->sFilter.bHorizBilinear = IMG_TRUE;
        }
#else
        if (psScaler->sPitch.fHorizLuma > 2)
        {
            psScaler->sFilter.bHorizBilinear = IMG_TRUE;
        }
#endif
    }
    else if (psScaler->psInLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_422 &&
             psScaler->psOutLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_420)
    {
#ifdef FXDPNT_SCALER_CALC
        if (psScaler->sPitch.iVertLuma > FIXED(2,HIGHP))
        {
            psScaler->sFilter.bVertBilinear = IMG_TRUE;
        }
#else
        if (psScaler->sPitch.fVertLuma > 2)
        {
            psScaler->sFilter.bVertBilinear = IMG_TRUE;
        }
#endif
    }

    return IMG_SUCCESS;
}


/*
******************************************************************************

 @Function              scaler_CalcParams

******************************************************************************/
static IMG_RESULT
scaler_CalcParams(
    SCALER_sScaleCtx *  psScaler
)
{
    IMG_UINT32  ui32UVWidth;
    IMG_UINT32  ui32UVHeight;
    IMG_UINT32  ui32UVScaledWidth;
    IMG_UINT32  ui32UVScaledHeight;

#ifdef FXDPNT_SCALER_CALC
    // Pitch: Luma Component.
    psScaler->sPitch.iHorizLuma = DIV1(FIXED(psScaler->psConfig->ui32ReconWidth,HIGHP),psScaler->psConfig->ui32ScaleWidth);
    psScaler->sPitch.iVertLuma = DIV1(FIXED(psScaler->psConfig->ui32ReconHeight,HIGHP),
        (DECODER_ROUND_UP_EVEN(psScaler->psConfig->ui32ScaleHeight, psScaler->psConfig->bFieldCoded)));
#else
    psScaler->sPitch.fHorizLuma = (IMG_FLOAT)psScaler->psConfig->ui32ReconWidth / (IMG_FLOAT)psScaler->psConfig->ui32ScaleWidth;
    psScaler->sPitch.fVertLuma = (IMG_FLOAT)(psScaler->psConfig->ui32ReconHeight) /
                     (IMG_FLOAT)(DECODER_ROUND_UP_EVEN(psScaler->psConfig->ui32ScaleHeight, psScaler->psConfig->bFieldCoded));
#endif
    // Pitch: Chroma Component.
    if (psScaler->psInLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_MONO ||
        psScaler->psInLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_444)
    {
        ui32UVWidth = psScaler->psConfig->ui32ReconWidth;
        ui32UVHeight = psScaler->psConfig->ui32ReconHeight;
    }
    else if (psScaler->psInLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_422)
    {
        ui32UVWidth = (psScaler->psConfig->ui32ReconWidth + 1) / 2;
        ui32UVHeight = psScaler->psConfig->ui32ReconHeight;

    }
    else // 420
    {
        ui32UVWidth = (psScaler->psConfig->ui32ReconWidth + 1) / 2;
        ui32UVHeight = (psScaler->psConfig->ui32ReconHeight + 1) / 2;
    }

    if (psScaler->psOutLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_MONO ||
        psScaler->psOutLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_444)
    {
        ui32UVScaledWidth = psScaler->psConfig->ui32ScaleWidth;
        ui32UVScaledHeight = DECODER_ROUND_UP_EVEN(psScaler->psConfig->ui32ScaleHeight, psScaler->psConfig->bFieldCoded);
    }
    else if (psScaler->psOutLoopPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_422)
    {
        ui32UVScaledWidth = (psScaler->psConfig->ui32ScaleWidth + 1) / 2;
        ui32UVScaledHeight = DECODER_ROUND_UP_EVEN(psScaler->psConfig->ui32ScaleHeight, psScaler->psConfig->bFieldCoded);
        //ui32UVScaledHeight *= 2;
    }
    else // 420
    {
        ui32UVScaledWidth = (psScaler->psConfig->ui32ScaleWidth + 1) / 2;
        ui32UVScaledHeight = DECODER_ROUND_UP_EVEN((psScaler->psConfig->ui32ScaleHeight+1)/2, psScaler->psConfig->bFieldCoded);
    }
#ifdef FXDPNT_SCALER_CALC

    psScaler->sPitch.iHorizChroma = DIV1(FIXED(ui32UVWidth,HIGHP),ui32UVScaledWidth);
    psScaler->sPitch.iVertChroma = DIV1(FIXED(ui32UVHeight,HIGHP),ui32UVScaledHeight);
    // All the above could be wrong...

    /* VXD can only downscale from the original display size. */
    IMG_ASSERT(psScaler->sPitch.iHorizLuma >= FIXED(1,HIGHP) && psScaler->sPitch.iVertLuma >= FIXED(1,HIGHP));
#else

    psScaler->sPitch.fHorizChroma = (IMG_FLOAT)ui32UVWidth / (IMG_FLOAT)ui32UVScaledWidth;
    psScaler->sPitch.fVertChroma = (IMG_FLOAT)ui32UVHeight / (IMG_FLOAT)ui32UVScaledHeight;
    // All the above could be wrong...

    /* VXD can only downscale from the original display size. */
    IMG_ASSERT(psScaler->sPitch.fHorizLuma >= 1 && psScaler->sPitch.fVertLuma >= 1);

#endif
    return IMG_SUCCESS;
}

#if 0

static IMG_RESULT
scaler_CalcParams(
    SCALER_sScaleCtx * psScaler
)
{
    //IMG_ASSERT(0);            /* Need to implement a non-floating point version for the kernel */
    return IMG_SUCCESS;
}
static IMG_RESULT
scaler_GetFilterType(
    SCALER_sScaleCtx * psScaler
)
{
    psScaler->sFilter.bHorizBilinear = 1;
    psScaler->sFilter.bVertBilinear = 1;
    return IMG_SUCCESS;        /* Need to implement a non-floating point version for the kernel */
}

#endif
/*
******************************************************************************

 @Function              SCALER_GetScalerCmds

******************************************************************************/
IMG_RESULT
SCALER_GetScalerCmds(
    SCALER_sConfig *  psConfig,
    IMG_UINT32 *      pui32PictCmds
)
{
    SCALER_sScaleCtx    sScaler;
    SCALER_sCoeffs      sCoeffs;
    
    // Initialise the scaler data.
    VDEC_BZERO(&sScaler);

    sScaler.psConfig = psConfig;

    DEBUG_REPORT(REPORT_MODULE_DECODER,
                 "Scaled display size, width: %d, height: %d",
                 psConfig->ui32ScaleWidth,
                 DECODER_ROUND_UP_EVEN(psConfig->ui32ScaleHeight,
                                       psConfig->bFieldCoded));

    sScaler.psInLoopPixelInfo = psConfig->psInPixelInfo;
    sScaler.psOutLoopPixelInfo = psConfig->psOutPixelInfo;

    scaler_CalcParams(&sScaler);
    scaler_GetFilterType(&sScaler);

    // Set the chroma to luma if using bi-linear filter.

#ifdef FXDPNT_SCALER_CALC
    if (sScaler.sFilter.bHorizBilinear)
    {
        sScaler.sPitch.iHorizChroma = sScaler.sPitch.iHorizLuma;
    }
    if (sScaler.sFilter.bVertBilinear)
    {
        sScaler.sPitch.iVertChroma = sScaler.sPitch.iVertLuma;
    }
#else
    if (sScaler.sFilter.bHorizBilinear)
    {
        sScaler.sPitch.fHorizChroma = sScaler.sPitch.fHorizLuma;
    }
    if (sScaler.sFilter.bVertBilinear)
    {
        sScaler.sPitch.fVertChroma = sScaler.sPitch.fVertLuma;
    }
#endif

    VXD_GetScalerCmds(sScaler.psConfig,
                      &sScaler.sPitch,
                      &sScaler.sFilter,
                      sScaler.psOutLoopPixelInfo,
                      &sScaler.sParams,
                      pui32PictCmds);

    // Calculate the scaler coefficients.
    scaler_GetCoeff(&sScaler, &sCoeffs);
    VXD_GetScalerCoeffCmds(&sCoeffs, pui32PictCmds);

    return IMG_SUCCESS;
}



