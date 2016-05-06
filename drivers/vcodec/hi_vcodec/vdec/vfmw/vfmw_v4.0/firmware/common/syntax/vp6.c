/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r38dmnv8ozrkqhet8KFDQuwlt5WiR9qQGYkiiPt+K7pkyV77KzQF/0ltCQyf8wFHR2PdN
3L5FuAZE70cc/ivMy+KZV42R5FsyjMsWNrWrJ8OlZhinwjqck1BPuzEorSc1fA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************
*
* Copyright (c) 2010 HUAWEI - All Rights Reserved
*
* File: $vp6_vfmw.c$
* Date: $2010/07/28$
* Revision: $v1.0$
* Purpose: vp6 decoder file
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ====== 
* 2010/07/28       l48485            Original
*
* Dependencies:
*
************************************************************************/
#ifndef __VP6_C__
#define __VP6_C__

#include    "public.h"
#include    "basedef.h"
#include    "bitstream.h"
#include    "vfmw.h"
#include    "syntax.h"
#include    "vp6.h"
#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


#ifdef VP6_ENABLE

/*********const define**********/

static const UINT8 VP6_LoopFilterLimitValues[64] = 
{ 
    14, 14, 13, 13, 12, 12, 10, 10, 
    10, 10,  8,  8,  8,  8,  8,  8,
     8,  8,  8,  8,  8,  8,  8,  8,
     8,  8,  8,  8,  8,  8,  8,  8,  
     8,  8,  8,  8,  7,  7,  7,  7,     
     7,  7,  6,  6,  6,  6,  6,  6,     
     5,  5,  5,  5,  4,  4,  4,  4,  
     4,  4,  4,  3,  3,  3,  3,  2 
};

static const UINT16 DcQuantTab[64]=
{
    188,188,188,188,180,172,172,172,
    172,172,168,164,164,160,160,160,
    160,140,140,140,140,132,132,132,
    132,128,128,128,108,108,104,104,
    100,100, 96, 96, 92, 92, 76, 76,
     76, 76, 72, 72, 68, 64, 64, 64,
     64, 64, 60, 44, 44, 44, 40, 40,
     36, 32, 28, 20, 12, 12,  8,  8
};

static const UINT16 AcQuantTab[64]=
{
    376,368,360,352,344,328,312,296,
    280,264,248,232,216,212,208,204,
    200,196,192,188,184,180,176,172,
    168,160,156,148,144,140,136,132,
    128,124,120,116,112,108,104,100,
     96, 92, 88, 84, 80, 76, 72, 68,
     64, 60, 56, 52, 48, 44, 40, 36,
     32, 28, 24, 20, 16, 12,  8,  4
};




const LINE_EQ VP6_DcNodeEqs[CONTEXT_NODES][DC_TOKEN_CONTEXTS] =
{
    { { 122, 133 },{ 133,  51 },{ 142, -16 } },             // Zero Node    
    { {   0,   1 },{   0,   1 },{   0,   1 } },             // EOB Node             Dummy as no EOBs in DC
    { {  78, 171 },{ 169,  71 },{ 221, -30 } },             // One Node
    { { 139, 117 },{ 214,  44 },{ 246,  -3 } },             // Low Val Node
    { { 168,  79 },{ 210,  38 },{ 203,  17 } }            // Two Node (2 vs 3 or 4)
};

// *****************************************************************************
// ModeVQ: This structure holds a table of probability vectors for encoding modes
// To build this table a number of clips were run through and allowed to 
// select each of the probabilities that were best for them on each frame.  These 
// choices were output and a vector quantizer was used to optimize the selection 
// of 16 vectors for each MODETYPE (allmodes available, nonearest, and no near)
// *****************************************************************************
const UINT8 VP6_ModeVq[MODETYPES][MODEVECTORS][MAX_MODES*2] =
{
	{
			{  9, 15, 32, 25,  7, 19,  9, 21,  1, 12, 14, 12,  3, 18, 14, 23,  3, 10,  0,  4},
   			{ 48, 39,  1,  2, 11, 27, 29, 44,  7, 27,  1,  4,  0,  3,  1,  6,  1,  2,  0,  0},
   			{ 21, 32,  1,  2,  4, 10, 32, 43,  6, 23,  2,  3,  1, 19,  1,  6, 12, 21,  0,  7},
   			{ 69, 83,  0,  0,  0,  2, 10, 29,  3, 12,  0,  1,  0,  3,  0,  3,  2,  2,  0,  0},
   			{ 11, 20,  1,  4, 18, 36, 43, 48, 13, 35,  0,  2,  0,  5,  3, 12,  1,  2,  0,  0},
   			{ 70, 44,  0,  1,  2, 10, 37, 46,  8, 26,  0,  2,  0,  2,  0,  2,  0,  1,  0,  0},
    		{  8, 15,  0,  1,  8, 21, 74, 53, 22, 42,  0,  1,  0,  2,  0,  3,  1,  2,  0,  0},
  			{141, 42,  0,  0,  1,  4, 11, 24,  1, 11,  0,  1,  0,  1,  0,  2,  0,  0,  0,  0},
  			{  8, 19,  4, 10, 24, 45, 21, 37,  9, 29,  0,  3,  1,  7, 11, 25,  0,  2,  0,  1},
  			{ 46, 42,  0,  1,  2, 10, 54, 51, 10, 30,  0,  2,  0,  2,  0,  1,  0,  1,  0,  0},
  			{ 28, 32,  0,  0,  3, 10, 75, 51, 14, 33,  0,  1,  0,  2,  0,  1,  1,  2,  0,  0},
  			{100, 46,  0,  1,  3,  9, 21, 37,  5, 20,  0,  1,  0,  2,  1,  2,  0,  1,  0,  0},
  			{ 27, 29,  0,  1,  9, 25, 53, 51, 12, 34,  0,  1,  0,  3,  1,  5,  0,  2,  0,  0},
  			{ 80, 38,  0,  0,  1,  4, 69, 33,  5, 16,  0,  1,  0,  1,  0,  0,  0,  1,  0,  0},
  			{ 16, 20,  0,  0,  2,  8,104, 49, 15, 33,  0,  1,  0,  1,  0,  1,  1,  1,  0,  0},
  			{194, 16,  0,  0,  1,  1,  1,  9,  1,  3,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0}
  	},
  	{
  			{ 41, 22,  1,  0,  1, 31,  0,  0,  0,  0,  0,  1,  1,  7,  0,  1, 98, 25,  4, 10},
  			{123, 37,  6,  4,  1, 27,  0,  0,  0,  0,  5,  8,  1,  7,  0,  1, 12, 10,  0,  2},
  			{ 26, 14, 14, 12,  0, 24,  0,  0,  0,  0, 55, 17,  1,  9,  0, 36,  5,  7,  1,  3},
  			{209,  5,  0,  0,  0, 27,  0,  0,  0,  0,  0,  1,  0,  1,  0,  1,  0,  0,  0,  0},
  			{  2,  5,  4,  5,  0,121,  0,  0,  0,  0,  0,  3,  2,  4,  1,  4,  2,  2,  0,  1},
  			{175,  5,  0,  1,  0, 48,  0,  0,  0,  0,  0,  2,  0,  1,  0,  2,  0,  1,  0,  0},
  			{ 83,  5,  2,  3,  0,102,  0,  0,  0,  0,  1,  3,  0,  2,  0,  1,  0,  0,  0,  0},
  			{233,  6,  0,  0,  0,  8,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  1,  0,  0},
  			{ 34, 16,112, 21,  1, 28,  0,  0,  0,  0,  6,  8,  1,  7,  0,  3,  2,  5,  0,  2},
  			{159, 35,  2,  2,  0, 25,  0,  0,  0,  0,  3,  6,  0,  5,  0,  1,  4,  4,  0,  1},
  			{ 75, 39,  5,  7,  2, 48,  0,  0,  0,  0,  3, 11,  2, 16,  1,  4,  7, 10,  0,  2},
  			{212, 21,  0,  1,  0,  9,  0,  0,  0,  0,  1,  2,  0,  2,  0,  0,  2,  2,  0,  0},
  			{  4,  2,  0,  0,  0,172,  0,  0,  0,  0,  0,  1,  0,  2,  0,  0,  2,  0,  0,  0},
  			{187, 22,  1,  1,  0, 17,  0,  0,  0,  0,  3,  6,  0,  4,  0,  1,  4,  4,  0,  1},
  			{133,  6,  1,  2,  1, 70,  0,  0,  0,  0,  0,  2,  0,  4,  0,  3,  1,  1,  0,  0},
  			{251,  1,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
  	},
	{  
			{  2,  3,  2,  3,  0,  2,  0,  2,  0,  0, 11,  4,  1,  4,  0,  2,  3,  2,  0,  4},
  			{ 49, 46,  3,  4,  7, 31, 42, 41,  0,  0,  2,  6,  1,  7,  1,  4,  2,  4,  0,  1},
  			{ 26, 25,  1,  1,  2, 10, 67, 39,  0,  0,  1,  1,  0, 14,  0,  2, 31, 26,  1,  6},
  			{103, 46,  1,  2,  2, 10, 33, 42,  0,  0,  1,  4,  0,  3,  0,  1,  1,  3,  0,  0},
  			{ 14, 31,  9, 13, 14, 54, 22, 29,  0,  0,  2,  6,  4, 18,  6, 13,  1,  5,  0,  1},
  			{ 85, 39,  0,  0,  1,  9, 69, 40,  0,  0,  0,  1,  0,  3,  0,  1,  2,  3,  0,  0},
  			{ 31, 28,  0,  0,  3, 14,130, 34,  0,  0,  0,  1,  0,  3,  0,  1,  3,  3,  0,  1},
  			{171, 25,  0,  0,  1,  5, 25, 21,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  0},
  			{ 17, 21, 68, 29,  6, 15, 13, 22,  0,  0,  6, 12,  3, 14,  4, 10,  1,  7,  0,  3},
  			{ 51, 39,  0,  1,  2, 12, 91, 44,  0,  0,  0,  2,  0,  3,  0,  1,  2,  3,  0,  1},
  			{ 81, 25,  0,  0,  2,  9,106, 26,  0,  0,  0,  1,  0,  1,  0,  1,  1,  1,  0,  0},
  			{140, 37,  0,  1,  1,  8, 24, 33,  0,  0,  1,  2,  0,  2,  0,  1,  1,  2,  0,  0},
  			{ 14, 23,  1,  3, 11, 53, 90, 31,  0,  0,  0,  3,  1,  5,  2,  6,  1,  2,  0,  0},
  			{123, 29,  0,  0,  1,  7, 57, 30,  0,  0,  0,  1,  0,  1,  0,  1,  0,  1,  0,  0},
  			{ 13, 14,  0,  0,  4, 20,175, 20,  0,  0,  0,  1,  0,  1,  0,  1,  1,  1,  0,  0},
  			{202, 23,  0,  0,  1,  3,  2,  9,  0,  0,  0,  1,  0,  1,  0,  1,  0,  0,  0,  0}
   	}
};

const UINT8 VP6_BaselineXmittedProbs[4][2][10] =
{
   	{
   		{42,  2,  7, 42, 22,  3,  2,  5,  1,  0},
		{69,  1,  1, 44,  6,  1,  0,  1,  0,  0}
	},
   	
   	{
   		{  8,  1,  8,  0,  0,  2,  1,  0,  1,  0},
		{229,  1,  0,  0,  0,  1,  0,  0,  1,  0}
	},
   
   	{
   		{ 35,  1,  6, 34,  0,  2,  1,  1,  1,  0},  
		{122,  1,  1, 46,  0,  1,  0,  0,  1,  0}
	},

   	{
   		{64,  0, 64, 64, 64,  0,  0,  0,  0,  0},
		{64,  0, 64, 64, 64,  0,  0,  0,  0,  0}
	}
};


const UINT8 VP6_MvUpdateProbs[2][MV_NODES] = 
{ 
    { 237, 246, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 250, 250, 252 }, 
    { 231, 243, 245, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 251, 251, 254 }
};

const UINT8 DefaultMvShortProbs[2][7] = 
{ 
    { 225, 146, 172, 147, 214,  39, 156 }, 
    { 204, 170, 119, 235, 140, 230, 228 }
};

const UINT8 DefaultMvLongProbs[2][LONG_MV_BITS] =  
{ 
    { 247, 210, 135,  68, 138, 220, 239, 246 }, 
    { 244, 184, 201,  44, 173, 221, 239, 253 } 
};

const UINT8 DefaultIsShortProbs[2] = { 162, 164 };
const UINT8 DefaultSignProbs[2]    = { 128, 128 };

const UINT8 VP6_DcUpdateProbs[2][MAX_ENTROPY_TOKENS-1] = 
{ 
    { 146, 255, 181, 207, 232, 243, 238, 251, 244, 250, 249 },
    { 179, 255, 214, 240, 250, 255, 244, 255, 255, 255, 255 }
};

const UINT8 VP6_AcUpdateProbs[PREC_CASES][2][VP6_AC_BANDS][MAX_ENTROPY_TOKENS-1] =
{
    {   // preceded by 0
        {
            { 227, 246, 230, 247, 244, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 209, 231, 231, 249, 249, 253, 255, 255, 255 },
            { 255, 255, 225, 242, 241, 251, 253, 255, 255, 255, 255 },
            { 255, 255, 241, 253, 252, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 248, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
        },
        {
            { 240, 255, 248, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 240, 253, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
        },
    },
    {   // preceded by 1
        {
            { 206, 203, 227, 239, 247, 255, 253, 255, 255, 255, 255 },
            { 207, 199, 220, 236, 243, 252, 252, 255, 255, 255, 255 },
            { 212, 219, 230, 243, 244, 253, 252, 255, 255, 255, 255 },
            { 236, 237, 247, 252, 253, 255, 255, 255, 255, 255, 255 },
            { 240, 240, 248, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
        },
        {
            { 230, 233, 249, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 238, 238, 250, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 248, 251, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
        },
    },
    {   // preceded by > 1
        {
            { 225, 239, 227, 231, 244, 253, 243, 255, 255, 253, 255 },
            { 232, 234, 224, 228, 242, 249, 242, 252, 251, 251, 255 },
            { 235, 249, 238, 240, 251, 255, 249, 255, 253, 253, 255 },
            { 249, 253, 251, 250, 255, 255, 255, 255, 255, 255, 255 },
            { 251, 250, 249, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
        },
        {
            { 243, 244, 250, 250, 255, 255, 255, 255, 255, 255, 255 },
            { 249, 248, 250, 253, 255, 255, 255, 255, 255, 255, 255 },
            { 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
            { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
        }
    }
};

// Zero run probs 
const UINT8 ZeroRunProbDefaults[ZRL_BANDS][ZERO_RUN_PROB_CASES] = 
{  
    { 198, 197, 196, 146, 198, 204, 169, 142, 130, 136, 149, 149, 191, 249 },
    { 135, 201, 181, 154,  98, 117, 132, 126, 146, 169, 184, 240, 246, 254 }
};

const UINT8 ScanBandUpdateProbs[VP6_BLOCK_SIZE] = 
{  
    255, 132, 132, 159, 153, 151, 161, 170, 
    164, 162, 136, 110, 103, 114, 129, 118, 
    124, 125, 132, 136, 114, 110, 142, 135, 
    134, 123, 143, 126, 153, 183, 166, 161, 
    171, 180, 179, 164, 203, 218, 225, 217, 
    215, 206, 203, 217, 229, 241, 248, 243,
    253, 255, 253, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255 
};

const UINT8 ZrlUpdateProbs[ZRL_BANDS][ZERO_RUN_PROB_CASES] =
{
    { 219, 246, 238, 249, 232, 239, 249, 255, 248, 253, 239, 244, 241, 248 }, 
    { 198, 232, 251, 253, 219, 241, 253, 255, 248, 249, 244, 238, 251, 255 } 
};

const UINT8 DefaultScanBands[VP6_BLOCK_SIZE] = 
{
    0, 0, 1, 1, 1, 2, 2, 2, 
    2, 2, 2, 3, 3, 4, 4, 4, 
    5, 5, 5, 5, 6, 6, 7, 7, 
    7, 7, 7, 8, 8, 9, 9, 9, 
    9, 9, 9,10,10,11,11,11,
   11,11,11,12,12,12,12,12,
   12,13,13,13,13,13,14,14,
   14,14,15,15,15,15,15,15
};

#define VP6_CLEARREFFLAG do{\
     FSP_ClearLogicFs(pCtx->ChanID, pVp6CodecInfo->GoldenFsID, 1);\
     FSP_ClearLogicFs(pCtx->ChanID, pVp6CodecInfo->FwdFsID, 1);\
     pVp6CodecInfo->GoldenFsID = 0; \
     pVp6CodecInfo->FwdFsID = 0; \
     pVp6CodecInfo->GoldenFsID=pVp6CodecInfo->FwdFsID=FSP_GetNullLogicFs(pCtx->ChanID);\
}while(0)

#define VP6_CLEARREFNUM do{pVp6CodecInfo->RefNum = 0;}while(0)


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
UINT32 Vp6_Vfmw_DecodeBool(BS *pBs, VP6_BOOLCODER_S *pBr, UINT8 probability) 
{
    UINT32 bit=0;
    UINT32 split;
    UINT32 bigsplit;
    UINT32 count = pBr->count;
    UINT32 range = pBr->range;
    UINT32 value = pBr->value;

    split = 1 +  (((range-1) * probability) >> 8);  

	bigsplit = (split<<16);
    
    range = split;
    if(value >= bigsplit)
    {
        range = pBr->range-split;
        value = value-bigsplit;
        bit = 1;
    }

    if(range>=0x80)
    {
        pBr->value = value;
        pBr->range = range;
        return bit;
    }
    else
    {
        do
        {
            range +=range;
            value +=value;
            
            if (!--count) 
            {
                count = 8;
                value |= BsGet(pBs, 8);
            }
        } 
        while(range < 0x80 );
    }
	
    pBr->count = count;
    pBr->value = value;
    pBr->range = range;

    return bit;
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
UINT32 Vp6_Vfmw_DecodeBool128(BS *pBs,VP6_BOOLCODER_S *pBr) 
{
    UINT32 bit;
    UINT32 split;
    UINT32 bigsplit;
    UINT32 count = pBr->count;
    UINT32 range = pBr->range;
    UINT32 value = pBr->value;

    split = ( range + 1) >> 1;
    bigsplit = (split<<16);
    
    if (value >= bigsplit)
    {
        range = (range-split)<<1;
        value = (value-bigsplit)<<1;
        bit = 1;
    }
    else
    {       
        range = split<<1;
        value = value<<1;
        bit = 0;
    }

    if (!--count)
    {
        count = 8;
        value |= BsGet(pBs, 8);
    }
    pBr->count = count;
    pBr->value = value;
    pBr->range = range;

    return bit;
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 Vp6_Vfmw_BoolRead(BS *pBs, VP6_BOOLCODER_S *pBr, SINT32 nBits)
{
    SINT32 i;
    SINT32 value=0;

    for (i=nBits-1; i>=0; i--)
    {
        value |= (Vp6_Vfmw_DecodeBool128(pBs,pBr)<<i);
    }

    return value;
}

/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID Vp6_Vfmw_StartDecode(BS *pBs, VP6_BOOLCODER_S *pBr)
{
    pBr->lowvalue = 0;
    pBr->range    = 255;
    pBr->count    = 8;
    pBr->value    = BsGet(pBs,24);
}

UINT32 VP6_ArrangeVHBMem(VP6_CTX_S *pCtx)
{
    VP6_CODECINFO *pVp6CodecInfo;
    VP6_PictureHeader_S *pSyntaxInfNew;
    FSP_INST_CFG_S  FspInstCfg;
    SINT32 PicWidth, PicHeight, DecFsNum, DispFsNum, PmvNum;

    pVp6CodecInfo = &pCtx->Vp6CodecInfo;
    pSyntaxInfNew = &pVp6CodecInfo->NewHeaderInfo;

    if( pSyntaxInfNew->pic_height_in_mb <= 2 || pSyntaxInfNew->pic_width_in_mb <= 2 || pSyntaxInfNew->pic_height_in_mb > MAX_IMG_HEIGHT_IN_MB || pSyntaxInfNew->pic_width_in_mb > MAX_IMG_WIDTH_IN_MB )
    {
        dprint(PRN_FATAL, "image_size_in_mb abnormal(%d x %d)\n", pSyntaxInfNew->pic_width_in_mb, pSyntaxInfNew->pic_height_in_mb );
        return VP6_VFMW_FALSE;
    }

    if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
    {
        if ((pSyntaxInfNew->pic_width_in_mb*16) > pCtx->pstExtraData->stChanOption.s32MaxWidth || (pSyntaxInfNew->pic_height_in_mb*16) > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "vp6 actual frame size(%dx%d) exeed max config(%dx%d)\n", pSyntaxInfNew->pic_width_in_mb*16, pSyntaxInfNew->pic_height_in_mb*16,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return VP6_VFMW_FALSE;
		}
				
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        PicWidth  = pCtx->pstExtraData->stChanOption.s32MaxWidth;
        PicHeight = pCtx->pstExtraData->stChanOption.s32MaxHeight;
		
        if (pVp6CodecInfo->Imgbuf_allocated == VP6_VFMW_TRUE)
        {
            return VP6_VFMW_TRUE;
		}
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/		
		DecFsNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pCtx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvNum = 1;
        }
        else
        {
            PmvNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvNum = MIN(PmvNum,17);
        }		
		DispFsNum = pCtx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}	
	else if (pCtx->pstExtraData->eCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION)
	{
        PicWidth  = pSyntaxInfNew->pic_width_in_mb*16;
        PicHeight = pSyntaxInfNew->pic_height_in_mb*16;	
		DecFsNum = 3;//golden fwd cur
		PmvNum = 3;
		DispFsNum = 5;		
	}
	else
	{
        if ((pSyntaxInfNew->pic_width_in_mb*16) > pCtx->pstExtraData->stChanOption.s32MaxWidth || (pSyntaxInfNew->pic_height_in_mb*16) > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "vp6 actual frame size(%dx%d) exeed max config(%dx%d)\n", (pSyntaxInfNew->pic_width_in_mb*16), (pSyntaxInfNew->pic_height_in_mb*16),
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return VP6_VFMW_FALSE;
		}
        PicWidth  = (pSyntaxInfNew->pic_width_in_mb*16);
        PicHeight = (pSyntaxInfNew->pic_height_in_mb*16);
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/		
		DecFsNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pCtx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvNum = 1;
        }
        else
        {
            PmvNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvNum = MIN(PmvNum,17);
        }		
		DispFsNum = pCtx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}


    memset(&FspInstCfg, 0, sizeof(FSP_INST_CFG_S));
	FspInstCfg.s32DecFsWidth        = PicWidth;
	FspInstCfg.s32DecFsHeight       = PicHeight;
	FspInstCfg.s32DispFsWidth       = PicWidth;
	FspInstCfg.s32DispFsHeight      = PicHeight;
	FspInstCfg.s32ExpectedDecFsNum  = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 0: DecFsNum;
	FspInstCfg.s32ExpectedDispFsNum = DispFsNum;
	FspInstCfg.s32ExpectedPmvNum    = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 1: PmvNum;

 	if (FSP_OK == FSP_ConfigInstance(pCtx->ChanID, &FspInstCfg))
 	{
 	    SINT32 Ret, UsedMemSize;
        Ret = FSP_PartitionFsMemory(pCtx->ChanID, pCtx->pstExtraData->s32SyntaxMemAddr, 
			        pCtx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
		if (Ret != FSP_OK)
		{
            // 分割帧存失败，返回
            return VP6_VFMW_FALSE;
		}
	}
	else
	{
	    dprint(PRN_FATAL, "FSP_ConfigInstance fail!\n");
        return VP6_VFMW_FALSE;
	}		
	pVp6CodecInfo->Imgbuf_allocated = VP6_VFMW_TRUE;
		
    return VP6_VFMW_TRUE;
}

/*!
************************************************************************
*    函数原型 :  VP6_GetImageBuffer()
*    功能描述 :  取一块帧存
*    参数说明 : 
*    返回值   :  0: 无法找到可用帧存;1: 能够找到可用帧存
************************************************************************
*/
UINT32 VP6_GetImageBuffer(VP6_CTX_S *pCtx)
{
    VP6_CODECINFO *pVp6CodecInfo;
    FSP_LOGIC_FS_S *pLf;
    VP6_DEC_PARAM_S    *pVp6DecParam;
	
    pVp6CodecInfo = &pCtx->Vp6CodecInfo;
	pVp6DecParam = &pCtx->Vp6DecParam;
    pVp6CodecInfo->CurFsID = FSP_NewLogicFs(pCtx->ChanID, 1);
    if (pVp6CodecInfo->CurFsID < 0)
    {
        /* 获取帧存失败 */
		dprint(PRN_FATAL,"get frame store fail!\n");
		VP6_CLEARREFFLAG;
		VP6_CLEARREFNUM;		
		#if 0
		ResetVoQueue(&pCtx->ImageQue);
		FSP_EmptyInstance(pCtx->ChanID);
		#else
		FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		#endif
		return VP6_VFMW_FALSE;
    }
	pLf = FSP_GetLogicFs(pCtx->ChanID, pVp6CodecInfo->CurFsID);
    if (NULL == pLf)
    {
        dprint(PRN_DBG, "line: %d, pImage is NULL!\n", __LINE__);
        return VP6_VFMW_FALSE;
    }
    
    dprint(PRN_PIC, "get image buffer ok: LogicFsID = %d\n", pVp6CodecInfo->CurFsID);		
	if ( (NULL != pLf->pstDecodeFs) && (NULL != pLf->pstDispOutFs) && (NULL != pLf->pstTfOutFs) )
	{
        pVp6CodecInfo->DDR_Stride = pLf->pstDispOutFs->Stride;
	    dprint(PRN_PIC, "decode %p, disp %p, tf %p\n", pLf->pstDecodeFs->PhyAddr, pLf->pstDispOutFs->PhyAddr, pLf->pstTfOutFs->PhyAddr);
    }
	else
	{
	    return VP6_VFMW_FALSE;
	}

    return VP6_VFMW_TRUE;

}

SINT32 VP6DEC_GetImageBuffer(VP6_CTX_S *pCtx)
{
	if(FSP_IsNewFsAvalible(pCtx->ChanID) == 1)
	{
		return 1;
	}
    else if (FSP_IsNewFsAvalible(pCtx->ChanID) == -1)
    {
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
    }
	
	return 0;
}

/****************************************************************************
* 
*  ROUTINE       :     BuildScanOrder
*
*  INPUTS        :     PB_INSTANCE *pbi : Pointer to instance of a decoder.
*                      UINT8 *ScanBands : Pointer to array containing band for 
*                                         each DCT coeff position. 
*
*  OUTPUTS       :     None
*
*  RETURNS       :     VOID
*
*  FUNCTION      :     Builds a custom dct scan order from a set of band data.
*
*  SPECIAL NOTES :     None. 
*
****************************************************************************/
VOID VP6_BuildScanOrder(VP6_CODECINFO *pVp6CodecInfo, VP6_PictureHeader_S *pbi)
{
    UINT32 i, j;
    UINT32 ScanOrderIndex = 1;
    UINT32 MaxOffset;

    // DC is fixed
    pVp6CodecInfo->ModifiedScanOrder[0] = 0;

    // Create a scan order where within each band the coefs are in ascending order
    // (in terms of their original zig-zag positions).
    for ( i = 0; i < SCAN_ORDER_BANDS; i++ )
    {
        for ( j = 1; j < VP6_BLOCK_SIZE; j++ )
        {
            if ( pVp6CodecInfo->ScanBands[j] == i )
            {
                pVp6CodecInfo->ModifiedScanOrder[ScanOrderIndex] = j;
                ScanOrderIndex++;
            }
        }
    }

    // For each of the positions in the modified scan order work out the 
    // worst case EOB offset in zig zag order. This is used in selecting
    // the appropriate idct variant
    for ( i = 0; i < VP6_BLOCK_SIZE; i++ )
    {
        MaxOffset = 0;
        for ( j = 0; j <= i; j++ )
        {
            if ( pVp6CodecInfo->ModifiedScanOrder[j] > MaxOffset )
            {
                MaxOffset = pVp6CodecInfo->ModifiedScanOrder[j];
            }
        }

        pVp6CodecInfo->EobOffsetTable[i] = MaxOffset;

        if (pbi->Vp3VersionNo > 6)
        {
            pVp6CodecInfo->EobOffsetTable[i] = MaxOffset+1;
        }
    }
}

/****************************************************************************
 * 
 *  ROUTINE       : VP6_BuildModeTree
 *
 *  INPUTS        : PB_INSTANCE *pbi  : Pointer to decoder instance.
 *                                              
 *  OUTPUTS       : None.
 *
 *  RETURNS       : VOID    
 *
 *  FUNCTION      : Fills in probabilities at each branch of the huffman tree
 *                  based upon probXmitted, the frequencies transmitted in the bitstream.
 *
 ****************************************************************************/
VOID VP6_BuildModeTree( VP6_CODECINFO *pVp6CodecInfo, VP6_PictureHeader_S *pbi )
{
    SINT32 i, j, k;

    // create a huffman tree and code array for each of our modes 
    // Note: each of the trees is minus the node give by probmodesame
    for ( i=0; i<10; i++ )
    {
        UINT32 Counts[MAX_MODES];
        UINT32 total;

        // set up the probabilities for each tree
        for (k=0; k<MODETYPES; k++)
        {
            total = 0;
            for ( j=0; j<10; j++ )
            {       
                if ( i == j )
                {
                    Counts[j] = 0;
                }
                else
                {
                    Counts[j] = 100*pVp6CodecInfo->probXmitted[k][0][j];
                }

                total+=Counts[j];
            }

            pVp6CodecInfo->probModeSame[k][i] = 255-
                255 * pVp6CodecInfo->probXmitted[k][1][i] 
                /
                (       1 +
                    pVp6CodecInfo->probXmitted[k][1][i] +  
                    pVp6CodecInfo->probXmitted[k][0][i]
                );

            // each branch is basically calculated via 
            // summing all posibilities at that branch.
            pVp6CodecInfo->probMode[k][i][0]= 1 + 255 *
                (
                    Counts[VP6_CODE_INTER_NO_MV]+
                    Counts[VP6_CODE_INTER_PLUS_MV]+
                    Counts[VP6_CODE_INTER_NEAREST_MV]+
                    Counts[VP6_CODE_INTER_NEAR_MV]
                ) / 
                (   1 +
                    total
                );

            pVp6CodecInfo->probMode[k][i][1]= 1 + 255 *
                (
                    Counts[VP6_CODE_INTER_NO_MV]+
                    Counts[VP6_CODE_INTER_PLUS_MV]
                ) / 
                (
                    1 + 
                    Counts[VP6_CODE_INTER_NO_MV]+
                    Counts[VP6_CODE_INTER_PLUS_MV]+
                    Counts[VP6_CODE_INTER_NEAREST_MV]+
                    Counts[VP6_CODE_INTER_NEAR_MV]
                );

            pVp6CodecInfo->probMode[k][i][2]= 1 + 255 *
                (
                    Counts[VP6_CODE_INTRA]+
                    Counts[VP6_CODE_INTER_FOURMV]
                ) / 
                (
                    1 + 
                    Counts[VP6_CODE_INTRA]+
                    Counts[VP6_CODE_INTER_FOURMV]+
                    Counts[VP6_CODE_USING_GOLDEN]+
                    Counts[VP6_CODE_GOLDEN_MV]+
                    Counts[VP6_CODE_GOLD_NEAREST_MV]+
                    Counts[VP6_CODE_GOLD_NEAR_MV]
                );
            
            pVp6CodecInfo->probMode[k][i][3]= 1 + 255 *
                (
                    Counts[VP6_CODE_INTER_NO_MV]
                ) / 
                (
                    1 +
                    Counts[VP6_CODE_INTER_NO_MV]+
                    Counts[VP6_CODE_INTER_PLUS_MV]
                );

            pVp6CodecInfo->probMode[k][i][4]= 1 + 255 *
                (
                    Counts[VP6_CODE_INTER_NEAREST_MV]
                ) / 
                (
                    1 +
                    Counts[VP6_CODE_INTER_NEAREST_MV]+
                    Counts[VP6_CODE_INTER_NEAR_MV]
                ) ;

            pVp6CodecInfo->probMode[k][i][5]= 1 + 255 *
                (
                    Counts[VP6_CODE_INTRA]
                ) / 
                (
                    1 +
                    Counts[VP6_CODE_INTRA]+
                    Counts[VP6_CODE_INTER_FOURMV]
                );

            pVp6CodecInfo->probMode[k][i][6]= 1 + 255 *
                (
                    Counts[VP6_CODE_USING_GOLDEN]+
                    Counts[VP6_CODE_GOLDEN_MV]
                ) / 
                (
                    1 +
                    Counts[VP6_CODE_USING_GOLDEN]+
                    Counts[VP6_CODE_GOLDEN_MV]+
                    Counts[VP6_CODE_GOLD_NEAREST_MV]+
                    Counts[VP6_CODE_GOLD_NEAR_MV]
                );

            pVp6CodecInfo->probMode[k][i][7]= 1 + 255 *
                (
                    Counts[VP6_CODE_USING_GOLDEN]
                ) / 
                (
                    1 +
                    Counts[VP6_CODE_USING_GOLDEN]+
                    Counts[VP6_CODE_GOLDEN_MV]
                );

            pVp6CodecInfo->probMode[k][i][8]= 1 + 255 *
                (
                    Counts[VP6_CODE_GOLD_NEAREST_MV]
                ) / 
                (
                    1 +
                    Counts[VP6_CODE_GOLD_NEAREST_MV]+
                    Counts[VP6_CODE_GOLD_NEAR_MV]
                );
        }
    }
}

/****************************************************************************
 * 
 *  ROUTINE       :     VP6_ConfigureContexts
 *
 *  INPUTS        :     PB_INSTANCE *pbi : Pointer to decoder instance.
 *                      
 *  OUTPUTS       :     None.
 *
 *  RETURNS       :     VOID
 *
 *  FUNCTION      :     Configures the context dependant entropy probabilities.
 *
 *  SPECIAL NOTES :     None. 
 *
 ****************************************************************************/
VOID VP6_ConfigureContexts( VP6_CODECINFO *pVp6CodecInfo, VP6_PictureHeader_S *pbi )
{
    UINT32 i;
    UINT32 Node;
    UINT32 Plane;
    SINT32  Temp;

    // DC Node Probabilities
    for ( Plane=0; Plane<2; Plane++ )
    {
        for ( i=0; i<DC_TOKEN_CONTEXTS; i++ )
        {
            // Tree Nodes
            for ( Node=0; Node<CONTEXT_NODES; Node++ )
            {
                Temp = ( ( pVp6CodecInfo->DcProbs[DCProbOffset(Plane,Node)] * VP6_DcNodeEqs[Node][i].M + 128 ) >> 8) 
                        + VP6_DcNodeEqs[Node][i].C;     
                Temp = (Temp > 255)? 255: Temp;
                Temp = (Temp <   1)? 1  : Temp;
                
                //pbi->pVp6CodecInfo->DcNodeContexts[Plane][i][Node] = (UINT8)Temp;
                *(pVp6CodecInfo->DcNodeContexts + DcNodeOffset(Plane,i,Node)) = (UINT8)Temp;
            }

            for ( Node=5;Node<11;Node++)
            {
                *(pVp6CodecInfo->DcNodeContexts + DcNodeOffset(Plane,i,Node)) = pVp6CodecInfo->DcProbs[DCProbOffset(Plane,Node)];
            }
        }
    }
}
/****************************************************************************
* 
*  ROUTINE       :     VP6_ConfigureEntropyDecoder
*
*  INPUTS        :     PB_INSTANCE *pbi : Pointer to decoder instance.
*                      UINT32 FrameType  : Type of frame.
*
*  OUTPUTS       :     None.
*
*  RETURNS       :     VOID
*
*  FUNCTION      :     Configure entropy subsystem ready for decode
*
*  SPECIAL NOTES :     None. 
*
****************************************************************************/
VOID VP6_ConfigureEntropyDecoder(VP6_CODECINFO *pVp6CodecInfo, BS *pBs, VP6_PictureHeader_S *pbi, UINT32 FrameType)
{
    UINT32 i, j;
    UINT32 Plane;
    UINT32 Band;
    SINT32 Prec;
    UINT8  LastProb[MAX_ENTROPY_TOKENS-1];
    
    // Clear down Last Probs data structure
    memset( LastProb, 128, MAX_ENTROPY_TOKENS-1 );

    // Read in the Baseline DC probabilities and initialise the DC context for Y and then UV plane
    for ( Plane = 0; Plane < 2; Plane++ )
    {
        // If so then read them in.
        for ( i = 0; i < MAX_ENTROPY_TOKENS-1; i++ )
        {
            if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, VP6_DcUpdateProbs[Plane][i] ) )
            {
                // 0 is not a legal value, clip to 1.
                LastProb[i] = Vp6_Vfmw_BoolRead(pBs,  &pbi->br, PROB_UPDATE_BASELINE_COST ) << 1;
                LastProb[i] += ( LastProb[i] == 0 );
                pVp6CodecInfo->DcProbs[DCProbOffset(Plane,i)] = LastProb[i];

            }
            else if ( FrameType == BASE_FRAME )
            {
                pVp6CodecInfo->DcProbs[DCProbOffset(Plane,i)] = LastProb[i];
            }
        }
    }

    // Set Zero run probabilities to defaults if this is a key frame
    if ( FrameType == BASE_FRAME )
    {
        memcpy( pVp6CodecInfo->ZeroRunProbs, ZeroRunProbDefaults, sizeof(pVp6CodecInfo->ZeroRunProbs) );
    }

    // If this frame contains updates to the scan order then read them
    if ( Vp6_Vfmw_DecodeBool128(pBs, &pbi->br) )
    {
        // Read in the AC scan bands and build the custom scan order
        for ( i = 1; i < VP6_BLOCK_SIZE; i++ )
        {
            // Has the band for this coef been updated ?
            if ( Vp6_Vfmw_DecodeBool( pBs, &pbi->br, ScanBandUpdateProbs[i] ) )
            { pVp6CodecInfo->ScanBands[i] = Vp6_Vfmw_BoolRead( pBs, &pbi->br, SCAN_BAND_UPDATE_BITS ); }
        }
        // Build the scan order
        VP6_BuildScanOrder(pVp6CodecInfo, pbi);
    }

    // Update the Zero Run probabilities
    for ( i = 0; i < ZRL_BANDS; i++ )
    {
        for ( j = 0; j < ZERO_RUN_PROB_CASES; j++ )
        {
            if ( Vp6_Vfmw_DecodeBool( pBs, &pbi->br, ZrlUpdateProbs[i][j] )  )
            {
                // Probabilities sent
                pVp6CodecInfo->ZeroRunProbs[i][j] = Vp6_Vfmw_BoolRead( pBs, &pbi->br, PROB_UPDATE_BASELINE_COST ) << 1;
                pVp6CodecInfo->ZeroRunProbs[i][j] += ( pVp6CodecInfo->ZeroRunProbs[i][j] == 0 );
            }
        }               
    }

    // Read in the Baseline AC band probabilities and initialise the appropriate contexts
    // Prec=0 means last token in current block was 0: Prec=1 means it was 1. Prec=2 means it was > 1
    for ( Prec = 0; Prec < PREC_CASES; Prec++ )
    {
        //PrecNonZero = ( Prec > 0 ) ? 1 : 0;
        for ( Plane = 0; Plane < 2; Plane++ )
        {
            for ( Band = 0; Band < VP6_AC_BANDS; Band++ )
            {
                // If so then read them in.
                for ( i = 0; i < MAX_ENTROPY_TOKENS-1; i++ )
                {
                    if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, VP6_AcUpdateProbs[Prec][Plane][Band][i] ) )
                    {
                        // Probabilities transmitted at reduced resolution. 
                        // 0 is not a legal value, clip to 1.
                        LastProb[i] = Vp6_Vfmw_BoolRead( pBs, &pbi->br, PROB_UPDATE_BASELINE_COST ) << 1;
                        LastProb[i] += ( LastProb[i] == 0 );                        
                        pVp6CodecInfo->AcProbs[ACProbOffset(Plane,Prec,Band,i)] = LastProb[i];
                    }
                    else if ( FrameType == BASE_FRAME )
                    {
                        pVp6CodecInfo->AcProbs[ACProbOffset(Plane,Prec,Band,i)] = LastProb[i];
                    }
                }
            }
        }
    } 

    // Create all the context specific propabilities based upon the new baseline data
    VP6_ConfigureContexts(pVp6CodecInfo, pbi);
}


/****************************************************************************
 * 
 *  ROUTINE       : VP6_decodeModeDiff
 *
 *  INPUTS        : PB_INSTANCE *pbi  : Pointer to decoder instance.
 *                                              
 *  OUTPUTS       : None.
 *
 *  RETURNS       : a probability difference value decoded from the bitstream.
 *
 *  FUNCTION      : this function returns a probability difference value in
 *                  the range -256 to +256 (in steps of 4) transmitted in the
 *                  bitstream using a fixed tree with hardcoded probabilities.
 *
 *  SPECIAL NOTES : The hard coded probabilities for the difference tree
 *                  were calcualated by taking the average number of times a 
 *                  branch was taken on some sample material ie 
 *                  (bond,bike,beautifulmind)
 *
 ****************************************************************************/
SINT32 VP6_decodeModeDiff (BS *pBs, VP6_PictureHeader_S *pbi )
{
    SINT32 sign;

    if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, 205) == 0 )
    {
        return 0;
    }
        
    sign = 1 + -2 * Vp6_Vfmw_DecodeBool128(pBs, &pbi->br);
    
    if ( !Vp6_Vfmw_DecodeBool(pBs, &pbi->br, 171) )
    {
        return sign<<(3-Vp6_Vfmw_DecodeBool(pBs, &pbi->br, 83));
    }
 
    if ( !Vp6_Vfmw_DecodeBool(pBs, &pbi->br, 199) ) 
    {
        if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, 140) )
        {
                return sign * 12;
        }
		
        if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, 125) )
        {
                return sign * 16;
        }
		
        if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, 104) )
        {
                return sign * 20;
        }
        return sign * 24;
    }
    else 
    {
        SINT32 diff = Vp6_Vfmw_BoolRead(pBs, &pbi->br, 7);
        return sign * diff * 4;
    }

}


/****************************************************************************
 * 
 *  ROUTINE       :     VP6_DecodeModeProbs
 *
 *  INPUTS        :     PB_INSTANCE *pbi  : Pointer to decoder instance.
 *                                              
 *  OUTPUTS       :     None.
 *
 *  RETURNS       :     VOID
 *
 *  FUNCTION      :     This function parses the probabilities transmitted in 
 *                      the bitstream. The bitstream may either use the 
 *                      last frames' baselines, or transmit a pointer to a
 *                      vector of new probabilities. It may then additionally
 *                      contain updates to each of these probabilities.
 *
 *  SPECIAL NOTES :     None. 
 *
 ****************************************************************************/
VOID VP6_DecodeModeProbs(VP6_CODECINFO *pVp6CodecInfo, 
		BS *pBs, VP6_PictureHeader_S *pbi )
{
    SINT32 i,j;

    // For each mode type (all modes available, no nearest, no near mode)
    for ( j=0; j<MODETYPES; j++ )
    {
        // determine whether we are sending a vector for this mode byte
        if ( Vp6_Vfmw_DecodeBool( pBs, &pbi->br, PROBVECTORXMIT ) )
        {
            // figure out which vector we have encoded
            SINT32 whichVector = Vp6_Vfmw_BoolRead(pBs, &pbi->br, 4);

            // adjust the vector
            for ( i=0; i<MAX_MODES; i++ )
            {
                pVp6CodecInfo->probXmitted[j][1][i] = VP6_ModeVq[j][whichVector][i*2];
                pVp6CodecInfo->probXmitted[j][0][i] = VP6_ModeVq[j][whichVector][i*2+1];
            }
        } 

        // decode whether updates to bring it closer to ideal 
        if ( Vp6_Vfmw_DecodeBool( pBs, &pbi->br, PROBIDEALXMIT) )
        {
            for ( i=0; i<MAX_MODES; i++ )
            {
                SINT32 diff;

                // determine difference 
                diff = VP6_decodeModeDiff(pBs, pbi);
                diff += pVp6CodecInfo->probXmitted[j][1][i];

                pVp6CodecInfo->probXmitted[j][1][i] = ( diff<0 ? 0 : (diff>255?255:diff) );

                // determine difference 
                diff = VP6_decodeModeDiff(pBs, pbi);
                diff += pVp6CodecInfo->probXmitted[j][0][i];

                pVp6CodecInfo->probXmitted[j][0][i] = ( diff<0 ? 0 : (diff>255?255:diff) );
            }
        }
    }
    
    VP6_BuildModeTree(pVp6CodecInfo, pbi);
}


/**************************************************************************** 
 * 
 *  ROUTINE       :     VP6_ConfigureMvEntropyDecoder
 *
 *  INPUTS        :     PB_INSTANCE *pbi : Pointer to decoder instance.
 *
 *  OUTPUTS       :     None.
 *
 *  RETURNS       :     VOID
 *
 *  FUNCTION      :     Builds the MV entropy decoding tree.
 *
 *  SPECIAL NOTES :     None. 
 *
***************************************************************************/
VOID VP6_ConfigureMvEntropyDecoder(VP6_CODECINFO *pVp6CodecInfo,
		BS *pBs, VP6_PictureHeader_S *pbi)
{
    SINT32 i;
    // This funciton is not called at all for a BASE_FRAME
    // Read any changes to mv probabilities.
    for ( i = 0; i < 2; i++ )
    {
        // Short vector probability
        if ( Vp6_Vfmw_DecodeBool(pBs,&pbi->br, VP6_MvUpdateProbs[i][0]) )
        {
            pVp6CodecInfo->IsMvShortProb[i] = Vp6_Vfmw_BoolRead( pBs, &pbi->br, PROB_UPDATE_BASELINE_COST ) << 1;
            if ( pVp6CodecInfo->IsMvShortProb[i] == 0 )
            {
                pVp6CodecInfo->IsMvShortProb[i] = 1;
            }
        }
		// Sign probability
        if ( Vp6_Vfmw_DecodeBool(pBs,&pbi->br,VP6_MvUpdateProbs[i][1]) )
        {
          	pVp6CodecInfo->MvSignProbs[i] = Vp6_Vfmw_BoolRead( pBs, &pbi->br, PROB_UPDATE_BASELINE_COST ) << 1;
            if ( pVp6CodecInfo->MvSignProbs[i] == 0 )
            {
                pVp6CodecInfo->MvSignProbs[i] = 1;
            }
        }
    }
	#if 0
	for(i = 0; i < 2; i++)
	{
		pVp6CodecInfo->TblProbMv[i*0x10] = pVp6CodecInfo->MvSignProbs[0];
		pVp6CodecInfo->TblProbMv[(i+2)*0x10] = pVp6CodecInfo->MvSignProbs[1];
		pVp6CodecInfo->TblProbMv[2*i*0x10 + 1] = pVp6CodecInfo->IsMvShortProb[i];
	}
	#endif
    // Short vector tree node probabilities
    for ( i = 0; i < 2; i++ )
    {
        UINT32 j;
        UINT32 MvUpdateProbsOffset = 2;                         // Offset into MvUpdateProbs[i][]

        for ( j = 0; j < 7; j++ )
        {
            if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, VP6_MvUpdateProbs[i][MvUpdateProbsOffset]) )
            {
                pVp6CodecInfo->MvShortProbs[i][j] = Vp6_Vfmw_BoolRead(pBs, &pbi->br, PROB_UPDATE_BASELINE_COST ) << 1;
                if ( pVp6CodecInfo->MvShortProbs[i][j] == 0 )
                {
                    pVp6CodecInfo->MvShortProbs[i][j] = 1;
                }
            }
            MvUpdateProbsOffset++;
        }
    }

    // Long vector tree node probabilities
    for ( i = 0; i < 2; i++ )
    {
        UINT32 j;
        UINT32 MvUpdateProbsOffset = 2 + 7;

        for ( j = 0; j < LONG_MV_BITS; j++ )
        {
            if ( Vp6_Vfmw_DecodeBool(pBs, &pbi->br, VP6_MvUpdateProbs[i][MvUpdateProbsOffset]) )
            {
                pVp6CodecInfo->MvSizeProbs[i][j] = Vp6_Vfmw_BoolRead( pBs, &pbi->br, PROB_UPDATE_BASELINE_COST ) << 1;
                if ( pVp6CodecInfo->MvSizeProbs[i][j] == 0 )
                {
                    pVp6CodecInfo->MvSizeProbs[i][j] = 1;
                }
            }
            MvUpdateProbsOffset++;
        }
    }
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID VP6_BoolTreeToHuffCodes(UINT8 *pBoolTreeProbs, UINT32* pHuffProbs)
{
    UINT32 Prob;
    UINT32 Prob1;
	
    pHuffProbs[DCT_EOB_TOKEN]       = ((UINT32)pBoolTreeProbs[0] * (UINT32)pBoolTreeProbs[1]) >> 8;
    pHuffProbs[ZERO_TOKEN]          = ((UINT32)pBoolTreeProbs[0] * (255 - (UINT32)pBoolTreeProbs[1])) >> 8;

    Prob = (255 - (UINT32)pBoolTreeProbs[0]);
    pHuffProbs[ONE_TOKEN]           = (Prob * (UINT32)pBoolTreeProbs[2]) >> 8;

    Prob = (Prob*(255 - (UINT32)pBoolTreeProbs[2])) >> 8;
    Prob1 = (Prob * (UINT32)pBoolTreeProbs[3]) >> 8;
	pHuffProbs[TWO_TOKEN]           = (Prob1 * (UINT32)pBoolTreeProbs[4]) >> 8; 
	
	Prob1 = (Prob1 * (255 - (UINT32)pBoolTreeProbs[4])) >> 8;
    pHuffProbs[THREE_TOKEN]         = (Prob1 * (UINT32)pBoolTreeProbs[5]) >> 8;
    pHuffProbs[FOUR_TOKEN]          = (Prob1 * (255 - (UINT32)pBoolTreeProbs[5])) >> 8;

    Prob = (Prob * (255 - (UINT32)pBoolTreeProbs[3])) >> 8;
    Prob1 = (Prob * (UINT32)pBoolTreeProbs[6]) >> 8;
    pHuffProbs[DCT_VAL_CATEGORY1]   = (Prob1 * (UINT32)pBoolTreeProbs[7]) >> 8;
    pHuffProbs[DCT_VAL_CATEGORY2]   = (Prob1 * (255 - (UINT32)pBoolTreeProbs[7])) >> 8;
    
    Prob = (Prob * (255 - (UINT32)pBoolTreeProbs[6])) >> 8;
    Prob1 = (Prob * (UINT32)pBoolTreeProbs[8]) >> 8; 
    pHuffProbs[DCT_VAL_CATEGORY3]   = (Prob1 * (UINT32)pBoolTreeProbs[9]) >> 8;
    pHuffProbs[DCT_VAL_CATEGORY4]   = (Prob1 * (255 - (UINT32)pBoolTreeProbs[9])) >> 8;

    Prob = (Prob * (255 - (UINT32)pBoolTreeProbs[8])) >> 8;
    pHuffProbs[DCT_VAL_CATEGORY5]   = (Prob * (UINT32)pBoolTreeProbs[10]) >> 8;
    pHuffProbs[DCT_VAL_CATEGORY6]   = (Prob * (255 - (UINT32)pBoolTreeProbs[10])) >> 8;
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID VP6_ZerosBoolTreeToHuffCodes ( UINT8 *pBoolTreeProbs, UINT32 *pHuffProbs )
{
    UINT32 Prob;

    Prob  = ((UINT32)pBoolTreeProbs[0] * (UINT32)pBoolTreeProbs[1]) >> 8;
    pHuffProbs[0] = (Prob * (UINT32)pBoolTreeProbs[2]) >> 8;
    pHuffProbs[1] = (Prob * (UINT32)(255 - pBoolTreeProbs[2])) >> 8;

    Prob = ((UINT32)pBoolTreeProbs[0] * (UINT32)(255 - pBoolTreeProbs[1])) >> 8;
    pHuffProbs[2] = (Prob * (UINT32)pBoolTreeProbs[3]) >> 8;
    pHuffProbs[3] = (Prob * (UINT32)(255 - pBoolTreeProbs[3])) >> 8;

    Prob = ((UINT32)(255 - pBoolTreeProbs[0]) * (UINT32)pBoolTreeProbs[4]) >> 8;
    Prob = (Prob * (UINT32)pBoolTreeProbs[5]) >> 8;
    pHuffProbs[4] = (Prob * (UINT32)pBoolTreeProbs[6]) >> 8;
    pHuffProbs[5] = (Prob * (UINT32)(255 - pBoolTreeProbs[6])) >> 8;

    Prob = ((UINT32)(255 - pBoolTreeProbs[0]) * (UINT32)pBoolTreeProbs[4]) >> 8;
    Prob = (Prob * (UINT32)(255 - pBoolTreeProbs[5])) >> 8;
    pHuffProbs[6] = (Prob * (UINT32)pBoolTreeProbs[7]) >> 8;
    pHuffProbs[7] = (Prob * (UINT32)(255 - pBoolTreeProbs[7])) >> 8;

    Prob = ((UINT32)(255 - pBoolTreeProbs[0]) * (UINT32)(255 - pBoolTreeProbs[4])) >> 8;
    pHuffProbs[8] = Prob;
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID VP6_InsertSorted(VP6_SORTNODE_S *pSn, UINT32 node, UINT32 *pStartnode)
{
    UINT32 which = *pStartnode;
    UINT32 prior = *pStartnode;

    // find the position at which to insert the node
    while( which != -1 && pSn[node].freq > pSn[which].freq )
    {
        prior = which;
        which = pSn[which].next;
    }

    if(which == *pStartnode)
    {
        *pStartnode = node;
        pSn[node].next = which;
    }
    else
    {
        pSn[prior].next = node;
        pSn[node].next = which;
    }
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID VP6_BuildHuffTree(VP6_HUFFNODE_S *pHn, UINT32 *pCounts, UINT32 values)
{
    UINT32 i;
	UINT32 sncount = 0;
    UINT32 startnode = 0;
	
	
	 
	//VP6_SORTNODE_S sn[256]; 
    VP6_SORTNODE_S sn[30];	
    
    /* 
     * NOTE: Create huffman tree in reverse order so 
     * that the root will always be 0.
     */
    UINT32 huffptr = values-1;
	
    /* Set up sorted linked list of values/pointers into 
     * the huffman tree.for the bits for sn[i].value.value
     * is only 4,the input function parameter "values" is 
     * ranged from 0-12.*/
     
    for ( i=0; i < values; i++ )
    {
        sn[i].value.selector = 1;
        sn[i].value.value = i;
 		sn[i].value.unused = 0;
		
        if(pCounts[i] == 0)
        { pCounts[i] = 1; }
        sn[i].freq = (UINT32)pCounts[i];
        sn[i].next = -1;
    }

    sncount = values;
	
    /* Connect above list into a linked list */
    for (i=1; i<values; i++)
    {
        VP6_InsertSorted(sn, i, &startnode);
    }

    /* while there is more than one node in our linked list*/
    while ( sn[startnode].next != -1 )
    {
        UINT32 first = startnode;
        UINT32 second = sn[startnode].next;
        UINT32 sumfreq = sn[first].freq + sn[second].freq;

        // set-up new merged huffman node.
        --huffptr;
        pHn[huffptr].leftunion.left = sn[first].value;
        pHn[huffptr].rightunion.right = sn[second].value;
 
        // set up new merged sort node.
        sn[sncount].value.selector = 0;
        sn[sncount].value.value = huffptr;
 
        sn[sncount].freq = sumfreq;
        sn[sncount].next = -1;

        // remove the two sort nodes we just merged.
        startnode = sn[second].next;

        // insert the new sort node
        VP6_InsertSorted(sn, sncount, &startnode);

        sncount++;
    }

    return;
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID VP6_BuildHuffLookupTable(VP6_HUFFNODE_S *pHuffTreeRoot, VP6_HUFFTABNODE_S *pHuffTable)
{
    UINT32 i, j;
    SINT32 bits;
    VP6_TOKENORPTR_S torp;

    for ( i=0; i<(1<<HUFF_LUT_LEVELS); i++ )
    {
        bits = i;        
        j=0;

        torp.value    = 0;
        torp.selector = 0;

        do
        {
            j++;
            if ( (bits>>(HUFF_LUT_LEVELS - j)) & 1 )
            {
                torp = pHuffTreeRoot[torp.value].rightunion.right;
            }
            else
            {
                torp = pHuffTreeRoot[torp.value].leftunion.left;
            }
        }
        while ( !(torp.selector) && (j < HUFF_LUT_LEVELS) );
        
        pHuffTable[i].value = torp.value;
        pHuffTable[i].length = j;
		pHuffTable[i].flag = torp.selector;
    }
}


VOID VP6_BuildTreeTab(VP6_CODECINFO *pVp6CodecInfo)
{
    UINT32 i, j, m, n, k;

    k = 0;
    for (i=0; i<2; i++)
  	{
        for (j=0; j<3; j++)
  	    {
            for (m=0; m<4; m++)
  	        {
                for (n=0; n<12; n++)
  	            {  	
                    pVp6CodecInfo->TreeTab[k++] = (pVp6CodecInfo->TblAcHuffTree[i][j][m][n].leftunion.l);
                    pVp6CodecInfo->TreeTab[k++] = (pVp6CodecInfo->TblAcHuffTree[i][j][m][n].rightunion.r);

                    if ( (5==n) || (11==n) )
                    {
                        k += 4;
                    }
	
  	            }
  	        }
        }
    }


    k = 0x300;
    for (i=0; i<2; i++)
  	{
        for (j=0; j<12; j++)
      	{
	
            pVp6CodecInfo->TreeTab[k++] = (pVp6CodecInfo->TblDcHuffTree[i][j].leftunion.l);
            pVp6CodecInfo->TreeTab[k++] = (pVp6CodecInfo->TblDcHuffTree[i][j].rightunion.r);

            if ( (5==j) || (11==j) )
            {
                k += 4;
            }
	
  	    }
  	}



    k = 0x340;
    for (i=0; i<2; i++)
  	{
        for (j=0; j<14; j++)
     	{

	
            pVp6CodecInfo->TreeTab[k++] = (pVp6CodecInfo->TblZeroHuffTree[i][j].leftunion.l);
            pVp6CodecInfo->TreeTab[k++] = (pVp6CodecInfo->TblZeroHuffTree[i][j].rightunion.r);

            if ( (5==j) || (11==j) )
            {
                k += 4;
            }
            else if (13==j)
            {
                k += (12+16);
            }
	
     	}
  	}
  
}
/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID VP6_ConvertBoolToHuff(VP6_CODECINFO *pVp6CodecInfo)
{
    UINT32 i;
    UINT32 Plane;
    UINT32 Band;
    UINT32 Prec;

    dprint(PRN_DBG,"enter VP6_ConvertBoolToHuff\n");
    for ( Plane = 0; Plane < 2; Plane++ )
    {
        VP6_BoolTreeToHuffCodes(&pVp6CodecInfo->DcProbs[DCProbOffset(Plane,0)],pVp6CodecInfo->DcHuffProbs[Plane]);
        VP6_BuildHuffTree(pVp6CodecInfo->TblDcHuffTree[Plane],pVp6CodecInfo->DcHuffProbs[Plane], 12);
        VP6_BuildHuffLookupTable(pVp6CodecInfo->TblDcHuffTree[Plane], pVp6CodecInfo->DcHuffLUT[Plane]);        
    }
    
    for ( i = 0; i < 2; i++ )
    {
        VP6_ZerosBoolTreeToHuffCodes ( pVp6CodecInfo->ZeroRunProbs[i], pVp6CodecInfo->ZeroHuffProbs[i] );
        VP6_BuildHuffTree ( pVp6CodecInfo->TblZeroHuffTree[i], pVp6CodecInfo->ZeroHuffProbs[i], 9 );
        VP6_BuildHuffLookupTable (pVp6CodecInfo->TblZeroHuffTree[i], pVp6CodecInfo->ZeroHuffLUT[i]);
    }
    for ( Plane = 0; Plane < 2; Plane++ )
    {
        for ( Prec = 0; Prec < 3; Prec++ )
        {
            for ( Band = 0; Band < 6; Band++ )
            {
                VP6_BoolTreeToHuffCodes( &pVp6CodecInfo->AcProbs[ACProbOffset(Plane,Prec,Band,0)], pVp6CodecInfo->AcHuffProbs[Plane][Prec][Band] );
                VP6_BuildHuffTree( pVp6CodecInfo->TblAcHuffTree[Plane][Prec][Band], pVp6CodecInfo->AcHuffProbs[Plane][Prec][Band], 12 );
                VP6_BuildHuffLookupTable (pVp6CodecInfo->TblAcHuffTree[Plane][Prec][Band], pVp6CodecInfo->AcHuffLUT[Plane][Prec][Band]);
            }
        }
    }
    VP6_BuildTreeTab(pVp6CodecInfo);
	dprint(PRN_DBG,"leave VP6_ConvertBoolToHuff\n");
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6_IntraFrmHeader(VP6_CODECINFO *pVp6CodecInfo, BS *pBs)
{
    UINT32 HFragments = 0;       
    UINT32 VFragments = 0;       
 	VP6_PictureHeader_S *pPictureHeader = &pVp6CodecInfo->NewHeaderInfo;
	
	dprint(PRN_DBG, "enter VP6_IntraFrmHeader\n");
	
    // Read the frame dimensions bytes (0,0 indicates vp31 or later)
    pPictureHeader->Vp3VersionNo = (UINT8)BsGet(pBs, 5);
    pPictureHeader->VpProfile = (UINT8)BsGet(pBs, 2);
	if (pPictureHeader->Vp3VersionNo > CURRENT_DECODE_VERSION)
    {
        dprint(PRN_ERROR, "error: Vp3VersionNo %d > CURRENT_DECODE_VERSION(8)\n", pPictureHeader->Vp3VersionNo);
        return VP6_VFMW_FALSE;
    }
	
    if ( (UINT8)BsGet(pBs, 1) != 0)
    {
        //this is an old test bitstream and is not supported
        dprint(PRN_ERROR, "error: bitstream error!\n");
        return VP6_VFMW_FALSE;
    }     
    
    /*Start the first bool decoder (modes, mv, probs and some flags)
     *The offset depends on whether or not we are using multiple bool
     *code streams*/
    if ( pPictureHeader->MultiStream )
    {
        /* Read the buffer offset for the second bool decoder buffer
         *if it is being used */ 
        pPictureHeader->Buff2Offset = (UINT32)BsGet(pBs, 16);
		Vp6_Vfmw_StartDecode(pBs,&pPictureHeader->br);
    }
    else
    {
        Vp6_Vfmw_StartDecode(pBs,&pPictureHeader->br);
    }

	pPictureHeader->pic_height_in_mb =  ((UINT8)Vp6_Vfmw_BoolRead( pBs,&pPictureHeader->br,8 ));
    pPictureHeader->pic_width_in_mb = ((UINT8)Vp6_Vfmw_BoolRead( pBs,&pPictureHeader->br,8 ));

	pPictureHeader->VMacroblockCount = 2 * pPictureHeader->pic_height_in_mb;
    pPictureHeader->HMacroblockCount = 2 * pPictureHeader->pic_width_in_mb;

    VFragments = 2 * pPictureHeader->pic_height_in_mb;
    HFragments = 2 * pPictureHeader->pic_width_in_mb;
	
    pPictureHeader->OutputVMacroblockCount = 2 * ((UINT8)Vp6_Vfmw_BoolRead(pBs, &pPictureHeader->br, 8 ));             
    pPictureHeader->OutputHMacroblockCount = 2 * ((UINT8)Vp6_Vfmw_BoolRead(pBs, &pPictureHeader->br, 8 ));              
    pPictureHeader->ScalingMode = ((UINT32)Vp6_Vfmw_BoolRead( pBs,&pPictureHeader->br,2 ));

	// we have a new input size
    if ( VFragments != pVp6CodecInfo->VOldScaled || HFragments != pVp6CodecInfo->HOldScaled)
    {
        dprint(PRN_DBG, "We have a new size image!\n The old size is %d x %d, and the new is %d x %d\n", pVp6CodecInfo->HOldScaled, pVp6CodecInfo->VOldScaled, HFragments, VFragments);
    }

    pVp6CodecInfo->HOldScaled = HFragments;
    pVp6CodecInfo->VOldScaled = VFragments;

    // Unless in SIMPLE_PROFILE read the the filter strategy for fractional pels
    if ( pPictureHeader->VpProfile != SIMPLE_PROFILE )
    {
        // Find out if selective bicubic filtering should be used for motion prediction.
        if ( Vp6_Vfmw_DecodeBool128(pBs,&pPictureHeader->br) )
        {
            pPictureHeader->PredictionFilterMode = VP6_AUTO_SELECT_PM;
            // Read in the variance threshold to be used
            pPictureHeader->PredictionFilterVarThresh = 
            	((UINT8)Vp6_Vfmw_BoolRead(pBs, &pPictureHeader->br, 5) << ((pPictureHeader->Vp3VersionNo > 7) ? 0 : 5) );
            // Read the bicubic vector length limit (0 actually means ignore vector length)
            pPictureHeader->PredictionFilterMvSizeThresh = (UINT8)Vp6_Vfmw_BoolRead(pBs, &pPictureHeader->br, 3 );
        }
        else
        {
            if ( Vp6_Vfmw_DecodeBool128(pBs,&pPictureHeader->br) )
            {
                pPictureHeader->PredictionFilterMode = VP6_BICUBIC_ONLY_PM;
            }
            else
            {
                pPictureHeader->PredictionFilterMode = VP6_BILINEAR_ONLY_PM;
            }
        }
        
        if ( pPictureHeader->Vp3VersionNo > 7 )
        {
            pPictureHeader->PredictionFilterAlpha = Vp6_Vfmw_BoolRead(pBs, &pPictureHeader->br, 4);
        }
        else
        {
            pPictureHeader->PredictionFilterAlpha = 16; // VP61 backwards compatibility
        }
    }
    else
    {
        // VP60 backwards compatibility
        pPictureHeader->PredictionFilterAlpha = 14; 
        pPictureHeader->PredictionFilterMode = VP6_BILINEAR_ONLY_PM; 
    }

	dprint(PRN_DBG,"leave VP6_IntraFrmHeader\n");
    return VP6_VFMW_TRUE;
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6_InterFrmHeader(VP6_CODECINFO *pVp6CodecInfo, BS *pBs)
{
    // Non key frame sopecific stuff
    //Check to make sure that the first frame is not a non-keyframe
    VP6_PictureHeader_S *pPictureHeader = &pVp6CodecInfo->NewHeaderInfo;	
	if (pVp6CodecInfo->OldHeaderInfo.Vp3VersionNo == 0)
	{
		dprint(PRN_ERROR, "VP6_InterFrmHeader VersionNo fault,old:%d,new:%d\n",
			pVp6CodecInfo->OldHeaderInfo.Vp3VersionNo,
			pVp6CodecInfo->NewHeaderInfo.Vp3VersionNo);
		return -88;
	}
	
	pPictureHeader->Vp3VersionNo = pVp6CodecInfo->OldHeaderInfo.Vp3VersionNo;
	pPictureHeader->VpProfile = pVp6CodecInfo->OldHeaderInfo.VpProfile;
	// Start the first bool decoder (modes, mv, probs and some flags)
	// The offset depends on whether or not we are using multiple bool code streams
	if ( pPictureHeader->MultiStream )
	{
	   // Read the buffer offset for the second bool decoder buffer if it is being used
	   pPictureHeader->Buff2Offset = (UINT32)BsGet(pBs, 16);
	   Vp6_Vfmw_StartDecode(pBs, &pPictureHeader->br);
	}
	else
	{
	   Vp6_Vfmw_StartDecode(pBs, &pPictureHeader->br);
	}

	// Find out if the golden frame should be refreshed this frame - use bool decoder
	pVp6CodecInfo->RefreshGoldenFrame = 
	pPictureHeader->RefreshGoldenFrame =
	Vp6_Vfmw_DecodeBool128(pBs,&pPictureHeader->br);

	if ( pVp6CodecInfo->OldHeaderInfo.VpProfile != SIMPLE_PROFILE )
	{
	   // Determine if loop filtering is on and if so what type should be used
	   pPictureHeader->UseLoopFilter = Vp6_Vfmw_DecodeBool128(pBs,&pPictureHeader->br);
	   if ( pPictureHeader->UseLoopFilter )
	   {
	       pPictureHeader->UseLoopFilter = (pPictureHeader->UseLoopFilter<<1) 
		   		| Vp6_Vfmw_DecodeBool128(pBs, &pPictureHeader->br);
	   }
	   
	   if ( pVp6CodecInfo->OldHeaderInfo.Vp3VersionNo > 7 ) //modify by liucan
	   {
	       if ( Vp6_Vfmw_DecodeBool128(pBs, &pPictureHeader->br) )
	       {
	           if ( Vp6_Vfmw_DecodeBool128(pBs, &pPictureHeader->br) )
	           {
	               pPictureHeader->PredictionFilterMode = VP6_AUTO_SELECT_PM;
	               pPictureHeader->PredictionFilterVarThresh = (UINT8)Vp6_Vfmw_BoolRead(pBs, &pPictureHeader->br,5 );
	               pPictureHeader->PredictionFilterMvSizeThresh = (UINT8)Vp6_Vfmw_BoolRead(pBs, &pPictureHeader->br,3 );
	           }
	           else
	           {
	               if ( Vp6_Vfmw_DecodeBool128(pBs,&pPictureHeader->br) )
	               {
	                   pPictureHeader->PredictionFilterMode = VP6_BICUBIC_ONLY_PM;
	               }
	               else
	               {
	                   pPictureHeader->PredictionFilterMode = VP6_BILINEAR_ONLY_PM;
	               }
	           }

	           pPictureHeader->PredictionFilterAlpha = Vp6_Vfmw_BoolRead(pBs,&pPictureHeader->br, 4);
	       }
	   }
	   else
	   {
	       pPictureHeader->PredictionFilterAlpha = 16; // VP61 backwards compatibility
	   }
	}
	else
	{
	   // VP60 backwards compatibility
	   pPictureHeader->PredictionFilterAlpha = 14; 
	   pPictureHeader->PredictionFilterMode = VP6_BILINEAR_ONLY_PM; 
	}
	
    return VP6_VFMW_TRUE;
}

/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6_GetPictureHeader(VP6_CODECINFO *pVp6CodecInfo, BS *pBs)
{
    // FrameType:Is the frame and inter frame or a key frame
    VP6_PictureHeader_S *pPictureHeader = NULL;
	SINT32 ret = VP6_VFMW_TRUE;
	
	if(!pVp6CodecInfo || !pBs)
	{	
		dprint(PRN_DBG,"[ERR]VP6_GetPictureHeader invalid param!\n");
		return VP6_VFMW_FALSE;
	}

	dprint(PRN_DBG,"VP6_GetPictureHeader enter!\n");
	
    pPictureHeader = &pVp6CodecInfo->NewHeaderInfo;
	
    pVp6CodecInfo->FrameType = pPictureHeader->FrameType = (UINT8)BsGet(pBs, 1);
	pPictureHeader->DctQMask = (UINT8)BsGet(pBs, 6);

    pPictureHeader->FLimit = VP6_LoopFilterLimitValues[pPictureHeader->DctQMask];
    pPictureHeader->DcQuant = DcQuantTab[pPictureHeader->DctQMask];
    pPictureHeader->AcQuant = AcQuantTab[pPictureHeader->DctQMask];

    pPictureHeader->MultiStream = (UINT8)BsGet(pBs, 1);

    /* If the frame was a base frame then read 
     * the frame dimensions and build a bitmap structure.
     */ 
    if (pPictureHeader->FrameType == BASE_FRAME)
    {
        ret = VP6_IntraFrmHeader(pVp6CodecInfo, pBs);
    }
    else
    {
        ret = VP6_InterFrmHeader(pVp6CodecInfo, pBs);
    }

	if( ret != VP6_VFMW_TRUE )
	{
		return ret;
	}
    // Should this frame use huffman for the dct data
    // need to check if huffman buffers have been initialized, if not, do it. 
    // dprint(PRN_DBG,"VP6_GetPictureHeader 1!\n");
    pPictureHeader->UseHuffman = Vp6_Vfmw_DecodeBool128(pBs, &(pPictureHeader->br));
    pPictureHeader->LastFrameQIndex = pPictureHeader->DctQMask;	

	//dprint(PRN_DBG,"VP6_GetPictureHeader 2!\n");
	dprint(PRN_DBG,"VP6_GetPictureHeader leave!\n");
	
	return VP6_VFMW_TRUE;
}

/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6DEC_Init(VP6_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    VP6_CODECINFO *pVp6CodecInfo;
    SINT32  ImgQueRstMagic;

    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    memset(pCtx, 0, sizeof(VP6_CTX_S));	
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue);
    
    pCtx->pstExtraData  = pstExtraData;
    
    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }
	
	pVp6CodecInfo = &pCtx->Vp6CodecInfo;
	memset(pVp6CodecInfo, 0, sizeof(VP6_CODECINFO));
	
    pVp6CodecInfo->DDR_Stride = 0x400;
	pVp6CodecInfo->Imgbuf_allocated = VP6_VFMW_FALSE;
    pVp6CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
	
    return VP6_VFMW_TRUE;
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6DEC_Destroy(VP6_CTX_S *pCtx)
{
    return VP6_VFMW_TRUE;
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6_DecodeDecide(VP6_CTX_S *pCtx)
{
    SINT32  DecMode;
    SINT32  ret = VP6_VFMW_TRUE;
    VP6_CODECINFO *pVp6CodecInfo;
    IMAGE *pFwdImg;
	
	pVp6CodecInfo = &pCtx->Vp6CodecInfo;
  	DecMode = pCtx->pstExtraData->s32DecMode;

    if (VP6_VFMW_FALSE == pVp6CodecInfo->Imgbuf_allocated)
    {
        dprint(PRN_ERROR, "ERROR: No Img buffer is allocated\n");
        return VP6_VFMW_FALSE;
    }

    /* 解码模式(IPB,IP,I)的处理 */
    if ( (pVp6CodecInfo->UsedDecMode == I_MODE || pVp6CodecInfo->UsedDecMode == DISCARD_MODE) &&
		 (pCtx->pstExtraData->s32DecMode == IP_MODE || pCtx->pstExtraData->s32DecMode == IPB_MODE || 
		  pCtx->pstExtraData->s32DecMode == DISCARD_B_BF_P_MODE) )
    {
        /* I->IP 或 I->IPB都有可能引发参考错误，所以需要找下一个I帧才行 */
        dprint(PRN_CTRL,"----------------- vp6 Imode -> %d ------------------\n", pCtx->pstExtraData->s32DecMode);
        VP6_CLEARREFFLAG;
        VP6_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过
    }
    pVp6CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
    switch (pVp6CodecInfo->UsedDecMode)
    {
        case DISCARD_MODE:
			ret = VP6_VFMW_FALSE;
			break;
        case I_MODE:
            if( BASE_FRAME != pVp6CodecInfo->FrameType)
            {
                ret = VP6_VFMW_FALSE;
    	        dprint(PRN_PIC, "-----I_MODE, but FrameType is %d-----\n", pVp6CodecInfo->FrameType);			
            }
            break;
        case IP_MODE:
        case IPB_MODE:			
        case DISCARD_B_BF_P_MODE:
            if((BASE_FRAME !=  pVp6CodecInfo->FrameType) && (pVp6CodecInfo->RefNum < 1))
            {
            	dprint(PRN_PIC, "-----cur framtype is %s, but refnum=%d-----\n",
        			(pVp6CodecInfo->FrameType == BASE_FRAME)? "I-frm":"P-frm" ,
        			pVp6CodecInfo->RefNum);
                ret = VP6_VFMW_FALSE;
            }
            break;
		default: 
			ret = VP6_VFMW_FALSE;
			dprint(PRN_ERROR, "error: DecMode illegal\n");
            break;
    }

    if (ret != VP6_VFMW_FALSE)
    {
        /* 如果是P/B帧，要看其参考帧是否超出参考阈值，若超出则不解 */
    	pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp6CodecInfo->FwdFsID);
        if(NULL == pFwdImg)
        {
        	dprint(PRN_DBG, "%s %d NULL == pFwdImg!!\n",__FUNCTION__,__LINE__);
        	return VP6_VFMW_FALSE;
        }
    	if (BASE_FRAME !=  pVp6CodecInfo->FrameType)
    	{
            if ( (NULL == pFwdImg) || (pFwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
            {
                dprint(PRN_ERROR, "dec P frame, fwd ref err(%d) > ref_thr(%d)\n",pFwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
    			return VP6_VFMW_FALSE;
    		}
			else
			{
			    return VP6_VFMW_TRUE;
			}
    	}
		else
		{
		    return VP6_VFMW_TRUE;
		}
    }
	else
	{
	    return VP6_VFMW_FALSE;
	}
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6_Set_DecParam(VP6_CTX_S *pCtx)
{
	VP6_DEC_PARAM_S *pVp6DecParam = &pCtx->Vp6DecParam;
	VP6_CODECINFO *pVp6CodecInfo = &pCtx->Vp6CodecInfo;
	VP6_PictureHeader_S *pPictureHeader = &pVp6CodecInfo->NewHeaderInfo;
	STREAM_PARAM *pVp6StreamParam = pCtx->pVp6StreamParam;
	FSP_LOGIC_FS_S *pCur, *pFwd, *pGolden;
	BS *pBs = &pCtx->Bs;
	UINT32 ResideBytes;
	SINT8* BaseAddrUnAligned;

    if (pVp6CodecInfo->FrameType == NVOP_FRAME)
    {
        pVp6DecParam->FrameType = NVOP_FRAME;
		pVp6DecParam->IsNvopCopy = 1;
    	pCur = FSP_GetLogicFs(pCtx->ChanID, pVp6CodecInfo->CurFsID);
    	pFwd = FSP_GetLogicFs(pCtx->ChanID, pVp6CodecInfo->FwdFsID);
    	pGolden = FSP_GetLogicFs(pCtx->ChanID, pVp6CodecInfo->GoldenFsID);
    	if((NULL == pCur) || (NULL == pFwd) || (NULL == pGolden))
    	{
    	    dprint(PRN_ERROR, "VP6_Set_DecParam but logic fs is null!\n");
    	    return VP6_VFMW_FALSE;
    	}
    	if(NULL == pCur->pstDecodeFs)
    	{
    		dprint(PRN_ERROR, "Decord FS is NULL!\n");
    		return VP6_VFMW_FALSE;
    	}
    	pVp6DecParam->image_curr_recon_addr = pCur->pstDecodeFs->PhyAddr;
    	pVp6DecParam->CurPmvAddr = pCur->PmvAddr;
        pVp6DecParam->image_golden_ref_addr = (NULL != pGolden->pstDecodeFs)?pGolden->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pVp6DecParam->image_last_ref_addr = (NULL != pFwd->pstDecodeFs)?pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
		pCtx->pVp6DecParam = &(pCtx->Vp6DecParam);
		
		return VP6_VFMW_TRUE;
    }
	
	memset(pVp6DecParam,0,sizeof(VP6_DEC_PARAM_S));	
	pVp6DecParam->FrameType = pPictureHeader->FrameType;
	pVp6DecParam->IsNvopCopy = 0;
	pVp6DecParam->DctQMask = pPictureHeader->DctQMask;
	pVp6DecParam->MultiStream = pPictureHeader->MultiStream;
	pVp6DecParam->UseHuffman = pPictureHeader->UseHuffman;
	pVp6DecParam->PredictionFilterMode = pPictureHeader->PredictionFilterMode;
	pVp6DecParam->PredictionFilterVarThresh = pPictureHeader->PredictionFilterVarThresh;
	pVp6DecParam->PredictionFilterMvSizeThresh = pPictureHeader->PredictionFilterMvSizeThresh;
	pVp6DecParam->PredictionFilterAlpha = pPictureHeader->PredictionFilterAlpha;

    pVp6DecParam->UseLoopFilter = pPictureHeader->UseLoopFilter;
	pVp6DecParam->FLimit = pPictureHeader->FLimit;
	pVp6DecParam->DcQuant = pPictureHeader->DcQuant;
	pVp6DecParam->AcQuant = pPictureHeader->AcQuant;

	pVp6DecParam->VpProfile = pPictureHeader->VpProfile;
	pVp6DecParam->Vp3VersionNo = pPictureHeader->Vp3VersionNo;
	
	pVp6DecParam->PicWidthInMb = pPictureHeader->pic_width_in_mb;
	pVp6DecParam->PicHeightInMb = pPictureHeader->pic_height_in_mb;

	pCur = FSP_GetLogicFs(pCtx->ChanID, pVp6CodecInfo->CurFsID);
	pFwd = FSP_GetLogicFs(pCtx->ChanID, pVp6CodecInfo->FwdFsID);
	pGolden = FSP_GetLogicFs(pCtx->ChanID, pVp6CodecInfo->GoldenFsID);
	if((NULL == pCur) || (NULL == pFwd) || (NULL == pGolden))
	{
	    dprint(PRN_ERROR, "VP6_Set_DecParam but logic fs is null!\n");
	    return VP6_VFMW_FALSE;
	}
	if(NULL == pCur->pstDecodeFs)
	{
		dprint(PRN_ERROR, "Decord FS is NULL!\n");
		return VP6_VFMW_FALSE;
	}
	pVp6DecParam->image_curr_recon_addr = pCur->pstDecodeFs->PhyAddr;
	pVp6DecParam->CurPmvAddr = pCur->PmvAddr;
    pVp6DecParam->image_golden_ref_addr = (NULL != pGolden->pstDecodeFs)?pGolden->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
    pVp6DecParam->image_last_ref_addr = (NULL != pFwd->pstDecodeFs)?pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
	pVp6DecParam->VahbStride = pVp6CodecInfo->DDR_Stride;

	pVp6DecParam->value = pPictureHeader->br.value;
	pVp6DecParam->range = pPictureHeader->br.range;
	pVp6DecParam->count = pPictureHeader->br.count;

	BaseAddrUnAligned =  pVp6StreamParam->VirAddr + (BsPos(pBs) / 8);
	pVp6DecParam->StreamBaseAddr = ((UINT32)MEM_Vir2Phy(BaseAddrUnAligned) & 0xFFFFFFF0) - 16;
	ResideBytes = (UINT32)(UINT32)MEM_Vir2Phy(BaseAddrUnAligned) & 0x0F;
    if(pPictureHeader->MultiStream || (pPictureHeader->VpProfile == SIMPLE_PROFILE))
    {
		pVp6DecParam->bit0_stream_addr_0 = 16;//0 ;//+ 0x100;
		pVp6DecParam->bit0_offset_0 = (ResideBytes << 3);// + (BsPos(pBs) & 0x03);
		pVp6DecParam->bit0_len_0 = pPictureHeader->Buff2Offset*8 - BsPos(pBs) ;//+ 1024;
		pVp6DecParam->bit0_stream_addr_1 = 0;
		pVp6DecParam->bit0_offset_1 = 0;
		pVp6DecParam->bit0_len_1 = 0;	
		BaseAddrUnAligned = pVp6StreamParam->VirAddr + (pPictureHeader->Buff2Offset);
		ResideBytes = (UINT32)MEM_Vir2Phy(BaseAddrUnAligned) & 0x0f;
		
		pVp6DecParam->bit1_stream_addr_0 = 
				((UINT32)MEM_Vir2Phy(BaseAddrUnAligned) & 0xfffffff0) - pVp6DecParam->StreamBaseAddr;
		pVp6DecParam->bit1_offset_0 =
				(ResideBytes << 3) ;//+ (pPictureHeader->Buff2Offset & 0x03) ;
		pVp6DecParam->bit1_len_0 =
				(pVp6StreamParam->Length << 3) - pPictureHeader->Buff2Offset*8;
		pVp6DecParam->bit1_stream_addr_1 = 0;
		pVp6DecParam->bit1_offset_1 = 0;
		pVp6DecParam->bit1_len_1 = 0;	
		
    }
    else
    {
   		pVp6DecParam->bit0_stream_addr_0 = 16;//0;
		pVp6DecParam->bit0_offset_0 = (ResideBytes << 3);// + (BsPos(pBs) & 0x03);
		pVp6DecParam->bit0_len_0 = (pVp6StreamParam->Length << 3) - BsPos(pBs);

		pVp6DecParam->bit0_stream_addr_1 = 0;
		pVp6DecParam->bit0_offset_1 = 0;
		pVp6DecParam->bit0_len_1 = 0;	
		pVp6DecParam->bit1_stream_addr_0 = 0;
		pVp6DecParam->bit1_offset_0 = 0;
		pVp6DecParam->bit1_len_0 = 0;

		pVp6DecParam->bit1_stream_addr_1 = 0;
		pVp6DecParam->bit1_offset_1 = 0;
		pVp6DecParam->bit1_len_1 = 0;	

    }
	pVp6DecParam->TblAcHuffLUT 			= pVp6CodecInfo->TblAcHuffLUT;
	pVp6DecParam->TblACProbs			= pVp6CodecInfo->TblACProbs;
	pVp6DecParam->TblDcHuffLUT  		= pVp6CodecInfo->TblDcHuffLUT;
	pVp6DecParam->TblDcNodeContexts		= pVp6CodecInfo->TblDcNodeContexts;
	pVp6DecParam->TblEobOffsetTable 	= pVp6CodecInfo->TblEobOffsetTable;
	pVp6DecParam->TblHuffTree			= pVp6CodecInfo->TblHuffTree;
	pVp6DecParam->TblModifiedScanOrder	= pVp6CodecInfo->TblModifiedScanOrder;
	pVp6DecParam->TblProbMode			= pVp6CodecInfo->TblProbMode;
	pVp6DecParam->TblProbModeSame		= pVp6CodecInfo->TblProbModeSame;
	pVp6DecParam->TblProbMv				= pVp6CodecInfo->TblProbMv;
	pVp6DecParam->TblZeroHuffLUT		= pVp6CodecInfo->TblZeroHuffLUT;
	pVp6DecParam->TblZeroProbs			= pVp6CodecInfo->TblZeroProbs;
    pVp6DecParam->Compress_en           = pCtx->pstExtraData->s32Compress_en;
	pCtx->pVp6DecParam = &(pCtx->Vp6DecParam);
	pCtx->pVp6DecParam->Compress_en     = pCtx->pstExtraData->s32Compress_en;
	return VP6_VFMW_TRUE;
}

SINT32  VP6_CfgTable(VP6_CODECINFO *pVp6CodecInfo,VP6_PictureHeader_S *pPictureHeader)
{  
	SINT32 i,j,k;
	UINT8 _ptr_msg_bank[16] = {0};

	for(i=0;i<3;i++)
	{       
		memcpy(pVp6CodecInfo->TblProbModeSame + i*0x10, pVp6CodecInfo->probModeSame[i],10);
    }
	for(i=0;i<4;i++)
	{
		for(j=0;j<10;j++)
		{
			memcpy(pVp6CodecInfo->TblProbMode +i*10*0x10 +j*0x10,&pVp6CodecInfo->probMode[i][j][0],9);
	    }
	}
    memset(_ptr_msg_bank,0,16);
    _ptr_msg_bank[0] = pVp6CodecInfo->MvSignProbs[0];//sign[x]
    _ptr_msg_bank[1] = pVp6CodecInfo->IsMvShortProb[0];//is_short[x]    
    _ptr_msg_bank[2] = pVp6CodecInfo->MvShortProbs[0][0];//short
    _ptr_msg_bank[3] = pVp6CodecInfo->MvShortProbs[0][1];
    _ptr_msg_bank[4] = pVp6CodecInfo->MvShortProbs[0][2];
    _ptr_msg_bank[5] = pVp6CodecInfo->MvShortProbs[0][3];
    _ptr_msg_bank[6] = pVp6CodecInfo->MvShortProbs[0][4];
    _ptr_msg_bank[7] = pVp6CodecInfo->MvShortProbs[0][5];
    _ptr_msg_bank[8] = pVp6CodecInfo->MvShortProbs[0][6];
    memcpy(pVp6CodecInfo->TblProbMv ,_ptr_msg_bank, 16);

    memset(_ptr_msg_bank, 0, 16);
    _ptr_msg_bank[0] = pVp6CodecInfo->MvSignProbs[0];//sign[x]
    _ptr_msg_bank[1] = pVp6CodecInfo->MvSizeProbs[0][0];//long[x]
    _ptr_msg_bank[2] = pVp6CodecInfo->MvSizeProbs[0][1];
    _ptr_msg_bank[3] = pVp6CodecInfo->MvSizeProbs[0][2];
    _ptr_msg_bank[4] = pVp6CodecInfo->MvSizeProbs[0][3];
    _ptr_msg_bank[5] = pVp6CodecInfo->MvSizeProbs[0][4];
    _ptr_msg_bank[6] = pVp6CodecInfo->MvSizeProbs[0][5];
    _ptr_msg_bank[7] = pVp6CodecInfo->MvSizeProbs[0][6];
    _ptr_msg_bank[8] = pVp6CodecInfo->MvSizeProbs[0][7];
    _ptr_msg_bank[9] = 0;
    _ptr_msg_bank[10]= 0;
    memcpy(pVp6CodecInfo->TblProbMv + 0x10,_ptr_msg_bank, 16);

    memset(_ptr_msg_bank, 0, 16);
    _ptr_msg_bank[0] = pVp6CodecInfo->MvSignProbs[1];//sign[x]
    _ptr_msg_bank[1] = pVp6CodecInfo->IsMvShortProb[1];//is_short[x]    
    _ptr_msg_bank[2] = pVp6CodecInfo->MvShortProbs[1][0];//short
    _ptr_msg_bank[3] = pVp6CodecInfo->MvShortProbs[1][1];
    _ptr_msg_bank[4] = pVp6CodecInfo->MvShortProbs[1][2];
    _ptr_msg_bank[5] = pVp6CodecInfo->MvShortProbs[1][3];
    _ptr_msg_bank[6] = pVp6CodecInfo->MvShortProbs[1][4];
    _ptr_msg_bank[7] = pVp6CodecInfo->MvShortProbs[1][5];
    _ptr_msg_bank[8] = pVp6CodecInfo->MvShortProbs[1][6];
    memcpy(pVp6CodecInfo->TblProbMv + 0x20,_ptr_msg_bank, 16);

    memset(_ptr_msg_bank, 0, 16);
    _ptr_msg_bank[0] = pVp6CodecInfo->MvSignProbs[1];//sign[x]
    _ptr_msg_bank[1] = pVp6CodecInfo->MvSizeProbs[1][0];//long[x]
    _ptr_msg_bank[2] = pVp6CodecInfo->MvSizeProbs[1][1];
    _ptr_msg_bank[3] = pVp6CodecInfo->MvSizeProbs[1][2];
    _ptr_msg_bank[4] = pVp6CodecInfo->MvSizeProbs[1][3];
    _ptr_msg_bank[5] = pVp6CodecInfo->MvSizeProbs[1][4];
    _ptr_msg_bank[6] = pVp6CodecInfo->MvSizeProbs[1][5];
    _ptr_msg_bank[7] = pVp6CodecInfo->MvSizeProbs[1][6];
    _ptr_msg_bank[8] = pVp6CodecInfo->MvSizeProbs[1][7];
    _ptr_msg_bank[9] = 0;
    _ptr_msg_bank[10]= 0;
    memcpy(pVp6CodecInfo->TblProbMv +0x30, _ptr_msg_bank, 16);

    if(pPictureHeader->UseHuffman)
    {
        memcpy(pVp6CodecInfo->TblDcHuffLUT,(UINT8*)(&(pVp6CodecInfo->DcHuffLUT[0][0])),0x80);
        memcpy(pVp6CodecInfo->TblZeroHuffLUT,(UINT8*)(&(pVp6CodecInfo->ZeroHuffLUT[0][0])),0x80);	

        for(i=0;i<2;i++)
            for(j=0;j<3;j++)
                for(k=0;k<4;k++)
                { memcpy(pVp6CodecInfo->TblAcHuffLUT + i * 3 * 4 * 0x40 + j * 4 * 0x40 + k * 0x40, (UINT8 *)&pVp6CodecInfo->AcHuffLUT[i][j][k][0], 0x40); }
                
        memcpy(pVp6CodecInfo->TblHuffTree, pVp6CodecInfo->TreeTab, 0x3c0);
    }
    else 
    {
    
    	for(i=0;i<2;i++)
    	{
            for(j=0;j<3;j++)
            {
                memcpy((pVp6CodecInfo->TblDcNodeContexts +i*3*0x10 +j*0x10),&pVp6CodecInfo->DcNodeContexts[i*3*11 +j*11],11);  	 
            }
    	}
    	   
    	for(i=0;i<2;i++)
    	{	
    		memcpy((pVp6CodecInfo->TblZeroProbs +i*0x10),pVp6CodecInfo->ZeroRunProbs[i],14);  	 
    	}
    
        for(i=0;i<2;i++)
        {
            for(j=0;j<6;j++)
            {
    		   for(k=0;k<3;k++)
    		   {
    			   memcpy((pVp6CodecInfo->TblACProbs +i*18*0x10 +j*3*0x10 + k*0x10),&pVp6CodecInfo->AcProbs[i*18*11 + k*6*11 +j*11],11);  	 
               }
            }
        }      
    }

    memcpy(pVp6CodecInfo->TblModifiedScanOrder, pVp6CodecInfo->ModifiedScanOrder, 0x40);
    memcpy(pVp6CodecInfo->TblEobOffsetTable, pVp6CodecInfo->EobOffsetTable, 0x40);
   
	return 0;
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6_BuildTables(VP6_CODECINFO *pVp6CodecInfo,VP6_PictureHeader_S *pPictureHeader, BS *pBs)
{
    if (pPictureHeader->FrameType != BASE_FRAME )
    {
        VP6_DecodeModeProbs(pVp6CodecInfo, pBs, pPictureHeader);
        VP6_ConfigureMvEntropyDecoder(pVp6CodecInfo, pBs, pPictureHeader);
    }
    else
    {
        memcpy ( pVp6CodecInfo->probXmitted,VP6_BaselineXmittedProbs,sizeof(pVp6CodecInfo->probXmitted));
        memcpy ( pVp6CodecInfo->IsMvShortProb, DefaultIsShortProbs, sizeof(pVp6CodecInfo->IsMvShortProb) );
        memcpy ( pVp6CodecInfo->MvShortProbs, DefaultMvShortProbs, sizeof(pVp6CodecInfo->MvShortProbs) );
        memcpy ( pVp6CodecInfo->MvSignProbs, DefaultSignProbs, sizeof(pVp6CodecInfo->MvSignProbs) );
        memcpy ( pVp6CodecInfo->MvSizeProbs, DefaultMvLongProbs, sizeof(pVp6CodecInfo->MvSizeProbs) );
        memcpy( pVp6CodecInfo->ScanBands, DefaultScanBands, sizeof(pVp6CodecInfo->ScanBands) );
    
        // Build the scan order
        VP6_BuildScanOrder( pVp6CodecInfo, pPictureHeader);
    } 

	VP6_ConfigureEntropyDecoder( pVp6CodecInfo, pBs, pPictureHeader, pPictureHeader->FrameType); 


	if(pPictureHeader->UseHuffman)
	{
        VP6_ConvertBoolToHuff(pVp6CodecInfo);
    }

	VP6_CfgTable(pVp6CodecInfo,pPictureHeader);

	return  VP6_VFMW_TRUE;
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 inline IsFrameSizeChanged(VP6_CODECINFO *pVp6CodecInfo)
{
    if((pVp6CodecInfo->OldHeaderInfo.pic_height_in_mb != pVp6CodecInfo->NewHeaderInfo.pic_height_in_mb) ||
			(pVp6CodecInfo->OldHeaderInfo.pic_width_in_mb != pVp6CodecInfo->NewHeaderInfo.pic_width_in_mb))
    {
        return VP6_VFMW_TRUE;
    }

    return VP6_VFMW_FALSE;
}

static SINT32 Vp6_UpdatePicHeader(VP6_CODECINFO *pVp6CodecInfo)
{
	if(pVp6CodecInfo->FrameType == BASE_FRAME)	
	{
		memcpy(&pVp6CodecInfo->OldHeaderInfo,
			&pVp6CodecInfo->NewHeaderInfo,
			sizeof(VP6_PictureHeader_S));
	}
	else
	{
		UINT32  TmpVp3VersionNo;
   	 	UINT32  TmpVpProfile;
		
		TmpVp3VersionNo = pVp6CodecInfo->OldHeaderInfo.Vp3VersionNo;
		TmpVpProfile = pVp6CodecInfo->OldHeaderInfo.VpProfile;
		
		memcpy(&pVp6CodecInfo->OldHeaderInfo,
			&pVp6CodecInfo->NewHeaderInfo,
			sizeof(VP6_PictureHeader_S));

		pVp6CodecInfo->OldHeaderInfo.Vp3VersionNo = TmpVp3VersionNo;
		pVp6CodecInfo->OldHeaderInfo.VpProfile = TmpVpProfile;
	}
	return VP6_VFMW_TRUE;
}
/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6DEC_Decode(VP6_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{	
	SINT32 ret = VP6_VFMW_TRUE;
	IMAGE *pImage = NULL;
    STREAM_PARAM *pVp6StreamParam = &pCtx->Vp6StreamParam;		
    VP6_CODECINFO *pVp6CodecInfo = &pCtx->Vp6CodecInfo;
    BS *pBs = &pCtx->Bs;
	
#if 1	
    pVp6StreamParam->VirAddr = pPacket->StreamPack[0].VirAddr;
    pVp6StreamParam->PhyAddr = pPacket->StreamPack[0].PhyAddr;
    pVp6StreamParam->Length = pPacket->StreamPack[0].LenInByte;	
#else
    pVp6StreamParam->VirAddr = pPacket->StreamPack[0].VirAddr+4;
    pVp6StreamParam->PhyAddr = pPacket->StreamPack[0].PhyAddr+4;
    pVp6StreamParam->Length = pPacket->StreamPack[0].LenInByte-4;	
#endif

	if(pVp6StreamParam->Length == 0)
	{
		pVp6CodecInfo->FrameType = NVOP_FRAME;
		goto VP6_DECIDE_DECODE;
	}
    else if (pVp6StreamParam->Length < 3)
    {
        dprint(PRN_ERROR, "Error! Truncated packet\n");
		return VP6_VFMW_FALSE;
    }
	
    BsInit(pBs, pVp6StreamParam->VirAddr, pVp6StreamParam->Length);
    pCtx->pVp6StreamParam = pVp6StreamParam;

    /*Picture Header 解码*/
    if ( VP6_VFMW_TRUE != VP6_GetPictureHeader(pVp6CodecInfo, pBs))
    {
        dprint(PRN_ERROR,"[ERR]VP6_GetPictureHeader Error!\n");
        return VP6_VFMW_FALSE;
    }

	ret = VP6_BuildTables(pVp6CodecInfo, &pVp6CodecInfo->NewHeaderInfo, pBs);
	if(VP6_VFMW_TRUE != ret)
	{
        dprint(PRN_ERROR, "[ERR] VP6_DecodeDecide Error!\n");
        return VP6_VFMW_FALSE;
    }

	/*alloc picture buffer for cur-picture & ref-frame*/
	if(VP6_VFMW_FALSE == pVp6CodecInfo->Imgbuf_allocated || IsFrameSizeChanged(pVp6CodecInfo))	
	{
		REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pVp6CodecInfo->OldHeaderInfo.pic_width_in_mb, pVp6CodecInfo->OldHeaderInfo.pic_height_in_mb,\
            pVp6CodecInfo->NewHeaderInfo.pic_width_in_mb, pVp6CodecInfo->NewHeaderInfo.pic_height_in_mb);    
		VP6_CLEARREFFLAG;
		VP6_CLEARREFNUM;		
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		
		if((pVp6CodecInfo->NewHeaderInfo.pic_width_in_mb > MAX_IMG_WIDTH_IN_MB) ||
			(pVp6CodecInfo->NewHeaderInfo.pic_height_in_mb > MAX_IMG_HEIGHT_IN_MB))
		{
			dprint(PRN_PIC, "pic width/height to large,MbWidth = %d, MbHeight = %d",
				pVp6CodecInfo->NewHeaderInfo.pic_width_in_mb,
				pVp6CodecInfo->NewHeaderInfo.pic_height_in_mb);
			return VP6_VFMW_FALSE;
		}
		
        if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
        {
            if (pVp6CodecInfo->Imgbuf_allocated == VP6_VFMW_FALSE)
            {
                ResetVoQueue(&pCtx->ImageQue);
            }
        }
        else
        {
            //未分配或者大小变化后,需要修改VO管理结构内的信息        
            ResetVoQueue(&pCtx->ImageQue);
        }

		ret = VP6_ArrangeVHBMem(pCtx);
		if(ret != VP6_VFMW_TRUE)
		{
			dprint(PRN_ERROR, "VP6_ArrangeVHBMem err\n"); 
			return VP6_VFMW_FALSE;
		}
	}

VP6_DECIDE_DECODE:	
	ret = VP6_DecodeDecide(pCtx);
	if (ret != VP6_VFMW_TRUE)
	{
		dprint(PRN_ERROR, "VP6_DecodeDecide err\n");   
        return VP6_VFMW_FALSE;
	}
	
	ret = VP6_GetImageBuffer(pCtx);
	if(ret != VP6_VFMW_TRUE)
	{
		dprint(PRN_ERROR, "VP6DEC_GetImageBuffer err\n");   
        return VP6_VFMW_FALSE;
	}

	FSP_SetRef(pCtx->ChanID, pVp6CodecInfo->CurFsID, 1);
    pImage = FSP_GetFsImagePtr(pCtx->ChanID, pVp6CodecInfo->CurFsID);
    if (NULL == pImage)
    {
        dprint(PRN_DBG, "line: %d, pImage is NULL!\n", __LINE__);
        return VP6_VFMW_FALSE;
    }

	/*init before use it*/
	pImage->PTS = pCtx->pstExtraData->pts;
	pImage->Usertag = pCtx->pstExtraData->Usertag;
	pImage->DispTime = pCtx->pstExtraData->DispTime;
    pImage->DispEnableFlag = pCtx->pstExtraData->DispEnableFlag;
    pImage->DispFrameDistance = pCtx->pstExtraData->DispFrameDistance;
    pImage->DistanceBeforeFirstFrame = pCtx->pstExtraData->DistanceBeforeFirstFrame;
	pImage->GopNum = pCtx->pstExtraData->GopNum;

	pImage->is_fld_save = 0;
    pCtx->pstExtraData->pts = (UINT64)(-1);
	dprint(PRN_PTS,"dec_pts: %lld Usertag = %lld\n",pImage->PTS,pImage->Usertag);

	/*config decparam for vdh*/
	if (VP6_VFMW_TRUE != VP6_Set_DecParam(pCtx))
    {
        dprint(PRN_ERROR, "VP6_PrePare_decode Error!\n");
        return VP6_VFMW_FALSE;  //Error
    }
	
	Vp6_UpdatePicHeader(pVp6CodecInfo);
	dprint(PRN_DBG, "leave VP6DEC_Decode\n");
	
    return VP6_VFMW_TRUE;
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
VOID VP6_SetImgFormat(VP6_CTX_S *pCtx)
{
    UINT32 codtype, csp, vfmt, sfmt, fldflg, dar;
	UINT32  fldfst = 0;
	VP6_CODECINFO *pVp6CodecInfo = &pCtx->Vp6CodecInfo;
	IMAGE *pImg;

	pImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp6CodecInfo->CurFsID);
	if(NULL == pImg)
	{
		return;
	}
    codtype = pVp6CodecInfo->FrameType;
    csp = 0;
    vfmt = 5;
    sfmt = 0;
    fldflg = 3; // frame
    fldfst = 1; //逐行序列指定顶场先显示
    dar = 0;

    pImg->format = ((dar&7)<<14)|((fldfst&0x3)<<12)|
					((fldflg&3)<<10)|((sfmt&3)<<8)|((vfmt&3)<<5)|
					((csp&7)<<2)|(codtype&3);
    pImg->top_fld_type = codtype&3;
    pImg->bottom_fld_type = codtype&3;

    SetAspectRatio(pImg,(VDEC_DAR_E)dar);
    pImg->image_width = pVp6CodecInfo->NewHeaderInfo.pic_width_in_mb*16;
    pImg->image_height = pVp6CodecInfo->NewHeaderInfo.pic_height_in_mb*16;
    if ((pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
	{
	    SINT32  Stride = pImg->image_stride;//(pImg->image_width + 63) & (~63);
		SINT32  ChromOfst = Stride * ((pImg->image_height + 15)/16)*16;

		pImg->chrom_phy_addr = pImg->luma_phy_addr + ChromOfst;			
	    pImg->top_luma_phy_addr  = pImg->luma_phy_addr;
	    pImg->top_chrom_phy_addr = pImg->top_luma_phy_addr + ChromOfst;
	    pImg->btm_luma_phy_addr  = pImg->top_luma_phy_addr + Stride;
	    pImg->btm_chrom_phy_addr = pImg->top_chrom_phy_addr + Stride;
	    pImg->luma_2d_phy_addr   = pImg->luma_phy_addr;
	    pImg->chrom_2d_phy_addr  = pImg->top_chrom_phy_addr;
	}
	
    pImg->disp_center_x = pImg->image_width / 2;
	pImg->disp_center_y = pImg->image_height / 2;
    pImg->disp_width = pImg->image_width;
    pImg->disp_height = pImg->image_height;
	
	return;
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6DEC_VDMPostProc(VP6_CTX_S *pCtx, SINT32 ErrRatio)
{
	VP6_CODECINFO *pVp6CodecInfo;
	SINT32 ret = VP6_VFMW_TRUE; 
	IMAGE *pCurImg, *pToQueImg;

	dprint(PRN_DBG, "ErrRatio = %d\n", ErrRatio);

	pVp6CodecInfo = &pCtx->Vp6CodecInfo;
    ReleasePacket(VFMW_VP6, pCtx);
	pCurImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp6CodecInfo->CurFsID);
	if(pCurImg == NULL)
   {
        dprint(PRN_FATAL,"pCurImg is null\n");
		return -1;
	}

	pCurImg->error_level = CLIP1(100, (SINT32)(ErrRatio));
    if (pCurImg->error_level > pCtx->pstExtraData->s32RefErrThr)
    {
        dprint(PRN_ERROR, "err_level(%d) over ref_thr(%d)\n",
					pCurImg->error_level, pCtx->pstExtraData->s32RefErrThr );
		
		VP6_CLEARREFFLAG;
        VP6_CLEARREFNUM;
        return -1;
    }
	
    VP6_SetImgFormat(pCtx);

	pVp6CodecInfo->RefNum = 1;
	
	if ((I_MODE == pVp6CodecInfo->UsedDecMode) && (pVp6CodecInfo->FrameType != BASE_FRAME))
	{
		pVp6CodecInfo->ToQueFsID = -1;
		FSP_SetDisplay(pCtx->ChanID, pVp6CodecInfo->CurFsID, 0);
	}
	else
	{
		pVp6CodecInfo->ToQueFsID = pVp6CodecInfo->CurFsID;
	}
	
	if(pVp6CodecInfo->ToQueFsID != -1)
	{
		FSP_SetDisplay(pCtx->ChanID, pVp6CodecInfo->ToQueFsID, 1);
        pToQueImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp6CodecInfo->ToQueFsID);
        if (NULL == pToQueImg)
        {
            dprint(PRN_DBG, "line: %d pToQueImg is null!\n", pToQueImg);
            return -1;            
        }
		ret = InsertImgToVoQueue(pCtx->ChanID, VFMW_VP6, pCtx, &pCtx->ImageQue, pToQueImg);
	    if (VP6_VFMW_TRUE != ret)
	    {
	    	FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
			pToQueImg->p_usrdat[0] = NULL;
			FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
	        pToQueImg->p_usrdat[1] = NULL;
			FSP_SetDisplay(pCtx->ChanID, pVp6CodecInfo->ToQueFsID, 0);
			dprint(PRN_FATAL, "insert img to Voqueue failed!\n");
	        return ret;
	    }
	}


	if (pVp6CodecInfo->FwdFsID!= pVp6CodecInfo->GoldenFsID)
    {
        if (pVp6CodecInfo->FwdFsID!=pVp6CodecInfo->CurFsID)
        {
            FSP_SetRef(pCtx->ChanID, pVp6CodecInfo->FwdFsID, 0);
        }
	}
    else if (0 == FSP_GetRef(pCtx->ChanID, pVp6CodecInfo->GoldenFsID))
    {
        if (pVp6CodecInfo->FwdFsID!=pVp6CodecInfo->CurFsID)
        {
            FSP_SetRef(pCtx->ChanID, pVp6CodecInfo->FwdFsID, 0);
        }
    }
	
    pVp6CodecInfo->FwdFsID = pVp6CodecInfo->CurFsID;
	FSP_SetRef(pCtx->ChanID, pVp6CodecInfo->FwdFsID, 1);			
		
	/*refresh golden frame */
    if ( (BASE_FRAME == pVp6CodecInfo->FrameType) || (pVp6CodecInfo->RefreshGoldenFrame) )
    {
        if (pVp6CodecInfo->GoldenFsID!=pVp6CodecInfo->CurFsID)
        {
		    FSP_SetRef(pCtx->ChanID, pVp6CodecInfo->GoldenFsID, 0);	
        }
		
        pVp6CodecInfo->GoldenFsID = pVp6CodecInfo->CurFsID;
		FSP_SetRef(pCtx->ChanID, pVp6CodecInfo->GoldenFsID, 1);	
	}
	
    return VP6_VFMW_TRUE;
}



/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6DEC_RecycleImage(VP6_CTX_S *pCtx,UINT32 ImgID)
{
    IMAGE *pImg;

    FSP_SetDisplay(pCtx->ChanID, ImgID, 0);
	pImg = FSP_GetFsImagePtr(pCtx->ChanID, ImgID);
	if (NULL != pImg)
	{
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        pImg->p_usrdat[0] = NULL;
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        pImg->p_usrdat[1] = NULL;            
	}
	
    return VP6_VFMW_TRUE;	
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP6DEC_GetRemainImg(VP6_CTX_S *pCtx)
{   
    SINT32 ret;

    ret = GetVoLastImageID(&pCtx->ImageQue);
    
    return ret;
}

#endif
#endif //VP6_VFMW_ENABLE
