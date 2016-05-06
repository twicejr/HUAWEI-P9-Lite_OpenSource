/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r3zRsBRHjgV999oyUsxM9hoV0K/gBNHzLxGoSenSW9hs8nooDwUMycSuJMzYmLgTgKBwg
4LD+23Zkkmh1lQ32SKJDIOxqF8/ezzgRukrHsX6fZjrlPDORUrxZ44C1od8hHQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************
*
* Copyright (c) 2009 HUAWEI - All Rights Reserved
*
* File: $real9_vfmw.c$
* Date: $2009/06/18$
* Revision: $v1.0$
* Purpose: real9 decoder file
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ====== 
* 2009/06/18       q45134            Original
*
* Dependencies:
*
************************************************************************/


#include    "syntax.h"
#include    "real9.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"

#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


#ifdef REAL9_ENABLE

#define RV9_CLEARREFFLAG do {                                       \
    FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->BwdFsID, 1);      \
    FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->FwdFsID, 1);      \
    pRv9CodecInfo->FwdFsID = 0;                                     \
    pRv9CodecInfo->BwdFsID = 0;                                     \
    pRv9CodecInfo->FwdFsID=pRv9CodecInfo->BwdFsID=FSP_GetNullLogicFs(pCtx->ChanID);\
} while(0)

#define RV9_CLEARREFNUM do {pRv9CodecInfo->RefNum=0;} while (0)


/* Bit stream field sizes */
#define FIELDLEN_PSC 22
static const UINT32 FIELDLEN_TR = 8;       /* temporal reference */
static const UINT32 FIELDLEN_TR_RV = 13;

static const UINT32 FIELDLEN_PTYPE = 13;   /* picture type */
static const UINT32 FIELDLEN_PTYPE_CONST = 2;
static const UINT32 FIELDLEN_PTYPE_SPLIT = 1;
static const UINT32 FIELDLEN_PTYPE_DOC = 1;
static const UINT32 FIELDLEN_PTYPE_RELEASE = 1;
static const UINT32 FIELDLEN_PTYPE_SRCFORMAT = 3;
static const UINT32 FIELDLEN_PTYPE_CODINGTYPE = 1;
static const UINT32 FIELDLEN_PTYPE_UMV = 1;
static const UINT32 FIELDLEN_PTYPE_AP = 1;
static const UINT32 FIELDLEN_PTYPE_PB = 1;

static const UINT32 FIELDLEN_PPTYPE_UFEP = 3;
static const UINT32 FIELDLEN_OPTIONAL_EPTYPE_RESERVED  =  3;
static const UINT32 FIELDLEN_MANDATORY_EPTYPE_RESERVED =  2;

static const UINT32 FIELDLEN_MPPTYPE_SRCFORMAT = 3;
static const UINT32 FIELDLEN_MPPTYPE_RPR = 1;
static const UINT32 FIELDLEN_MPPTYPE_RRU = 1;
static const UINT32 FIELDLEN_MPPTYPE_ROUNDING = 1;

static const UINT32 FIELDLEN_CSFMT_PARC = 4;
static const UINT32 FIELDLEN_CSFMT_FWI = 9;
static const UINT32 FIELDLEN_CSFMT_CONST = 1;
static const UINT32 FIELDLEN_CSFMT_FHI = 9;

static const UINT32 FIELDLEN_EPAR_WIDTH = 8;
static const UINT32 FIELDLEN_EPAR_HEIGHT = 8;

static const UINT32 FIELDLEN_PQUANT = 5;   /* picture quant value */
static const UINT32 FIELDLEN_CPM = 1;      /* continuous presence multipoint indicator */
static const UINT32 FIELDLEN_TRB = 3;      /* temporal reference for B frames */
static const UINT32 FIELDLEN_DBQUANT = 2;  /* B frame differential quant value */
static const UINT32 FIELDLEN_PSPARE = 8;   /* spare information */

#define FIELDLEN_GBSC 17    /* Group of blocks start code */
static const UINT32 FIELDLEN_GN = 5;       /* GOB number. */
static const UINT32 FIELDLEN_GLCI = 2; /* GOB logical channel indicator */
static const UINT32 FIELDLEN_GFID = 2; /* GOB Frame ID */
static const UINT32 FIELDLEN_GQUANT = 5;   /* GQUANT */
static const UINT32 FIELDLEN_SQUANT = 5;   /* SQUANT */

#define FIELDLEN_SSC 24         /* Slice start code */
#define FIELDLEN_SSC_RV8 17     /* Slice start code */

static const UINT32 FIELDLEN_WDA = 2;      /* RPR warping displacement accuracy */
static const UINT32 FIELDLEN_RPR_FILL_MODE = 2;
static const UINT32 FIELDLEN_RPR_COLOR = 8;

static const UINT32 FIELDLEN_PWIDTH_RV = 8;
static const UINT32 FIELDLEN_PHEIGHT_RV = 8;
/* Bit stream field values */

static const UINT32 FIELDVAL_PSC   = (0x00008000 >> (32 - FIELDLEN_PSC));
static const UINT32 FIELDVAL_SSC   = (0x1D1C105E >> (32 - FIELDLEN_SSC));
static const UINT32 FIELDVAL_SSC_RV8   = (0x00008000 >> (32 - FIELDLEN_SSC_RV8));
static const UINT32 FIELDVAL_GBSC = (0x00008000 >> (32 - FIELDLEN_GBSC));
static const UINT32 FIELDVAL_EPTYPE_RESERVED   =  0;

/* Bitstream Version Information */
/* */
/* Starting with RV_FID_REALVIDEO30, for RealVideo formats we embed the */
/* minor bitstream version number in the slice header. */
/* The encoder only ever produces one bitstream format.  But the decoder */
/* must be backwards compatible, and able to decode any prior minor */
/* bitstream version number. */
/* */
/* It is assumed that if the bitstream major version number changes, */
/* then a new RV_FID is introduced.  So, only the minor version number */
/* is present in the bitstream. */
/* */
/* The minor version number is encoded in the bitstream using 3 bits. */
/* RV89Combo's first bitstream minor version number is "2", which is encoded */
/* as all 0's.  The following table maps the bitstream value to the */
/* actual minor version number. */

static const UINT32 FIELDLEN_RV_BITSTREAM_VERSION = 3;
#define UNSUPPORTED_RV_BITSTREAM_VERSION 9999
#define ENCODERS_CURRENT_RV_BITSTREAM_VERSION 2
    /* This should match RV_BITSTREAM_MINOR_VERSION in "hiverv.h" */

static const UINT32 s_RVVersionEncodingToMinorVersion[8] =
{
    2,
    UNSUPPORTED_RV_BITSTREAM_VERSION,
    UNSUPPORTED_RV_BITSTREAM_VERSION,
    UNSUPPORTED_RV_BITSTREAM_VERSION,
    UNSUPPORTED_RV_BITSTREAM_VERSION,
    UNSUPPORTED_RV_BITSTREAM_VERSION,
    UNSUPPORTED_RV_BITSTREAM_VERSION,
    UNSUPPORTED_RV_BITSTREAM_VERSION
};

#define NUMBER_OF_RV_BITSTREAM_VERSIONS \
                   (sizeof(s_RVVersionEncodingToMinorVersion) \
                   / sizeof(s_RVVersionEncodingToMinorVersion[0]))


UINT32 Real9_CB_GetBits(BS *pBs, UINT32 nBits)
{
    UINT32 Data;

    /* make sure that the number of bits given is <= 25 */    
    Data = BsShow(pBs, nBits);
    BsSkip(pBs, nBits);

    return Data;
}


UINT32 Real9_CB_Get1Bit(BS *pBs)
{
    UINT32 Data;
    
    Data = BsShow(pBs, 1);
    BsSkip(pBs, 1);

    return Data;
}


/* gs_VLCDecodeTable maps the leading 8-bits of the unread bitstream */
/* into the length and info of the VLC code at the head of those 8 bits. */
/* The table's contents can be summarized as follows, where p, q, r, s */
/* and '*' are arbitrary binary digits {0, 1}. */
/* */
/*  8 Bits      Length  Info */
/*  ========    ======  ==== */
/*  0p0q0r0s    8       pqrs combined with VLC at head of next 8 bits */
/*  0p0q0r1*    7       pqr */
/*  0p0q1***    5       pq */
/*  0p1*****    3       p */
/*  1*******    1       0 */
/* */
/* Note that when the length is 8, or even, we need to read another 8 bits */
/* from the bitstream, look up these 8 bits in the same table, and combine */
/* the length and info with the previously decoded bits. */
/* */
/* For a given 8-bit chunk of bitstream bits, the maximum length is 8, */
/* and the maximum info value is contained in 4 bits.  Thus, we can pack */
/* the length and info in a U8.  The info is in the least significant */
/* 4 bits, and the length is in the most significant 4 bits. */
#define PACK_LENGTH_AND_INFO(length, info) (((length) << 4) | (info))

static const UINT8 gs_VLCDecodeTable[256] =
{
    PACK_LENGTH_AND_INFO(8,  0),   /* 00000000 */
    PACK_LENGTH_AND_INFO(8,  1),   /* 00000001 */
    PACK_LENGTH_AND_INFO(7,  0),   /* 00000010 */
    PACK_LENGTH_AND_INFO(7,  0),   /* 00000011 */
    PACK_LENGTH_AND_INFO(8,  2),   /* 00000100 */
    PACK_LENGTH_AND_INFO(8,  3),   /* 00000101 */
    PACK_LENGTH_AND_INFO(7,  1),   /* 00000110 */
    PACK_LENGTH_AND_INFO(7,  1),   /* 00000111 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001000 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001001 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001010 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001011 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001100 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001101 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001110 */
    PACK_LENGTH_AND_INFO(5,  0),   /* 00001111 */
    PACK_LENGTH_AND_INFO(8,  4),   /* 00010000 */
    PACK_LENGTH_AND_INFO(8,  5),   /* 00010001 */
    PACK_LENGTH_AND_INFO(7,  2),   /* 00010010 */
    PACK_LENGTH_AND_INFO(7,  2),   /* 00010011 */
    PACK_LENGTH_AND_INFO(8,  6),   /* 00010100 */
    PACK_LENGTH_AND_INFO(8,  7),   /* 00010101 */
    PACK_LENGTH_AND_INFO(7,  3),   /* 00010110 */
    PACK_LENGTH_AND_INFO(7,  3),   /* 00010111 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011000 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011001 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011010 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011011 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011100 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011101 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011110 */
    PACK_LENGTH_AND_INFO(5,  1),   /* 00011111 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100000 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100001 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100010 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100011 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100100 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100101 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100110 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00100111 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101000 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101001 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101010 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101011 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101100 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101101 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101110 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00101111 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110000 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110001 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110010 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110011 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110100 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110101 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110110 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00110111 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111000 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111001 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111010 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111011 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111100 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111101 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111110 */
    PACK_LENGTH_AND_INFO(3,  0),   /* 00111111 */
    PACK_LENGTH_AND_INFO(8,  8),   /* 01000000 */
    PACK_LENGTH_AND_INFO(8,  9),   /* 01000001 */
    PACK_LENGTH_AND_INFO(7,  4),   /* 01000010 */
    PACK_LENGTH_AND_INFO(7,  4),   /* 01000011 */
    PACK_LENGTH_AND_INFO(8, 10),   /* 01000100 */
    PACK_LENGTH_AND_INFO(8, 11),   /* 01000101 */
    PACK_LENGTH_AND_INFO(7,  5),   /* 01000110 */
    PACK_LENGTH_AND_INFO(7,  5),   /* 01000111 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001000 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001001 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001010 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001011 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001100 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001101 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001110 */
    PACK_LENGTH_AND_INFO(5,  2),   /* 01001111 */
    PACK_LENGTH_AND_INFO(8, 12),   /* 01010000 */
    PACK_LENGTH_AND_INFO(8, 13),   /* 01010001 */
    PACK_LENGTH_AND_INFO(7,  6),   /* 01010010 */
    PACK_LENGTH_AND_INFO(7,  6),   /* 01010011 */
    PACK_LENGTH_AND_INFO(8, 14),   /* 01010100 */
    PACK_LENGTH_AND_INFO(8, 15),   /* 01010101 */
    PACK_LENGTH_AND_INFO(7,  7),   /* 01010110 */
    PACK_LENGTH_AND_INFO(7,  7),   /* 01010111 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011000 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011001 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011010 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011011 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011100 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011101 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011110 */
    PACK_LENGTH_AND_INFO(5,  3),   /* 01011111 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100000 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100001 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100010 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100011 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100100 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100101 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100110 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01100111 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101000 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101001 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101010 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101011 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101100 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101101 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101110 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01101111 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110000 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110001 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110010 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110011 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110100 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110101 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110110 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01110111 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111000 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111001 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111010 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111011 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111100 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111101 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111110 */
    PACK_LENGTH_AND_INFO(3,  1),   /* 01111111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10000111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10001111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10010111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10011111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10100111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10101111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10110111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 10111111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11000111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11001111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11010111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11011111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11100111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11101111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110110 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11110111 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11111000 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11111001 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11111010 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11111011 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11111100 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11111101 */
    PACK_LENGTH_AND_INFO(1,  0),   /* 11111110 */
    PACK_LENGTH_AND_INFO(1,  0)    /* 11111111 */
};


UINT32 Real9_CB_GetVLCBits(BS *pBs, UINT32 *pInfo)
{
    UINT32 bits, info = 0, length = 0;
    UINT32 lengthAndInfo;
    UINT32 thisChunksLength;

    do
    {
        /* Extract the leading 8-bits into 'bits' */    
        bits = BsShow(pBs, 8);
    
        lengthAndInfo = gs_VLCDecodeTable[bits];
        thisChunksLength = lengthAndInfo >> 4;

        info = (info << (thisChunksLength >> 1)) | (lengthAndInfo & 0xf);
        length += thisChunksLength;

        BsSkip(pBs, thisChunksLength);  
    }
    while (!(length & 1));    /* We're done when length is an odd number */

    *pInfo = info;

    return length;
}


/*!
************************************************************************
*    函数原型 :  Real9_GetImageBuffer()
*    功能描述 :  取一块帧存
*    参数说明 :  **p_vobuf 用于指向当前可用帧存的指针的地址
*    返回值   :  0: 无法找到可用帧存;1: 能够找到可用帧存
************************************************************************
*/
UINT32 Real9_GetImageBuffer(RV9_CTX_S *pCtx)
{
    SINT32 ret = RV9_VFMW_FALSE;
    RV9_CODECINF *pRv9CodecInfo;
    RV9_VOBUFINF *pVOBufInf;

    pRv9CodecInfo = &pCtx->CodecInfo;
    pVOBufInf = pCtx->CodecInfo.VOBufInf;

    pRv9CodecInfo->CurFsID = FSP_NewLogicFs(pCtx->ChanID, 1);
    if (pRv9CodecInfo->CurFsID < 0)
    {
        /* 获取帧存失败 */
        dprint(PRN_FATAL,"get frame store fail!\n");
        RV9_CLEARREFFLAG;
        RV9_CLEARREFNUM;		
		#if 0
		ResetVoQueue(&pCtx->ImageQue);
		FSP_EmptyInstance(pCtx->ChanID);
		#else
		FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		#endif

        return 0;
    }

    ret = RV9_VFMW_TRUE;
    {
        FSP_LOGIC_FS_S *pLf = FSP_GetLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID);
        if (NULL == pLf)
        {
            dprint(PRN_DBG, "line: %d, pImage is NULL!\n", __LINE__);
            return RV9_VFMW_FALSE;
        }
        
        dprint(PRN_PIC, "get image buffer ok: LogicFsID = %d\n", pRv9CodecInfo->CurFsID);
        if ( (NULL!=pLf->pstDecodeFs) && (NULL!=pLf->pstDispOutFs) && (NULL!=pLf->pstTfOutFs) )
        {
            dprint(PRN_PIC, "decode %p, disp %p, tf %p\n", pLf->pstDecodeFs->PhyAddr, pLf->pstDispOutFs->PhyAddr, pLf->pstTfOutFs->PhyAddr);
        }
        if(pRv9CodecInfo->CurFsID == 2)
        {
            pRv9CodecInfo->CurFsID = pRv9CodecInfo->CurFsID;
        }
    }

    return ret;
}


/*!
************************************************************************
*    函数原型 :  Real9_ArrangeVHBMem()
*    功能描述 :  分配消息池和帧存空间并初始化管理帧存的队列
*    参数说明 :  ImageNum 需要分配的帧存
*    返回值   :  0: 分配失败 1: 分配成功
************************************************************************
*/
UINT32 Real9_ArrangeVHBMem(SINT32 ImageNum, RV9_CTX_S *pCtx, RV9_PictureHeader *pPictureHeader)
{
    //SINT32 i;
    //UINT32 SlotWidth;
    //UINT32 BankOfst;
    //UINT32 ImgWidth, ImgHeight;

    RV9_CODECINF *pRv9CodecInfo;
    FSP_INST_CFG_S  FspInstCfg;
    SINT32 PicWidth, PicHeight, DecFsNum, DispFsNum, PmvNum;

    pRv9CodecInfo = &pCtx->CodecInfo;

    if( pPictureHeader->pic_width_in_mb < 2 || pPictureHeader->pic_height_in_mb < 2 )
    {
        dprint(PRN_FATAL, "image size abnormal (%dx%d) in MB\n", pPictureHeader->pic_width_in_mb, pPictureHeader->pic_height_in_mb);
        return RV9_VFMW_FALSE;
    }
	
    if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
    {
        if ((pPictureHeader->pic_width_in_pixel) > pCtx->pstExtraData->stChanOption.s32MaxWidth || (pPictureHeader->pic_height_in_pixel) > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "real9 actual frame size(%dx%d) exeed max config(%dx%d)\n", pPictureHeader->pic_width_in_pixel, pPictureHeader->pic_height_in_pixel,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return RV9_VFMW_FALSE;
		}
				
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        PicWidth  = pCtx->pstExtraData->stChanOption.s32MaxWidth;
        PicHeight = pCtx->pstExtraData->stChanOption.s32MaxHeight;
		
        if (pRv9CodecInfo->Imgbuf_allocated == RV9_VFMW_TRUE)
        {
            return RV9_VFMW_TRUE;
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
        PicWidth  = pPictureHeader->pic_width_in_pixel;
        PicHeight = pPictureHeader->pic_height_in_pixel;	
		DecFsNum = 4;
		PmvNum = 2;
		DispFsNum = 5;		
	}
	else
	{
        if ((pPictureHeader->pic_width_in_pixel) > pCtx->pstExtraData->stChanOption.s32MaxWidth || (pPictureHeader->pic_height_in_pixel) > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "real9 actual frame size(%dx%d) exeed max config(%dx%d)\n", (pPictureHeader->pic_width_in_pixel), (pPictureHeader->pic_height_in_pixel),
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return RV9_VFMW_FALSE;
		}
        PicWidth  = (pPictureHeader->pic_width_in_pixel);
        PicHeight = (pPictureHeader->pic_height_in_pixel);
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
    FspInstCfg.s32ExpectedDecFsNum  = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 0: DecFsNum;
    FspInstCfg.s32ExpectedDispFsNum = DispFsNum;
    FspInstCfg.s32ExpectedPmvNum    = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 1: PmvNum;
	
    /* 配置FSP实例，并分割帧存 */
    if (FSP_OK == FSP_ConfigInstance(pCtx->ChanID, &FspInstCfg))
    {
        SINT32 Ret, UsedMemSize;
        Ret = FSP_PartitionFsMemory(pCtx->ChanID, pCtx->pstExtraData->s32SyntaxMemAddr, 
              pCtx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
        if (Ret != FSP_OK)
        {
            // 分割帧存失败，返回
            return RV9_VFMW_FALSE;
        }
    }
    else
    {
        return RV9_VFMW_FALSE;
    }

    pRv9CodecInfo->Imgbuf_allocated = RV9_VFMW_TRUE;
	
    return RV9_VFMW_TRUE;
}


SINT32 Real9_CB_GetCPFMT(BS *pBs, RV9_PictureHeader *pPictureHeader)
{
    pPictureHeader->pixel_aspect_ratio = Real9_CB_GetBits(pBs, FIELDLEN_CSFMT_PARC);
    pPictureHeader->pic_width_in_pixel = (Real9_CB_GetBits(pBs, FIELDLEN_CSFMT_FWI) + 1) << 2;

    /* Bit 14 must be "1" to prevent start code emulation */
    if (Real9_CB_Get1Bit(pBs) != 1)
    {
        return RV9_VFMW_FALSE;
    }
    /* Frame height indication */
    /* The number of lines is given by FHI*4 */
    pPictureHeader->pic_height_in_pixel = Real9_CB_GetBits(pBs, FIELDLEN_CSFMT_FHI) << 2;

    return RV9_VFMW_TRUE;
}


/* --------------------------------------------------------------------------- */
/*  Real9_CB_SetDimensions() */
/*      use in the decoder to initialize size, m_nGOBs, m_nMBs, and m_mbaSize */
/* --------------------------------------------------------------------------- */
/* for PutSliceHeader              SQCIF, QCIF, CIF, 4CIF, 16CIF, 2048x1152 */
static const UINT32 MBA_NumMBs[]     = { 47,   98, 395, 1583,  6335, 9215 };
static const UINT32 MBA_FieldWidth[] = {  6,    7,   9,   11,    13,   14 };
static const UINT32 MBA_Widths = sizeof( MBA_FieldWidth ) / sizeof( MBA_FieldWidth[0] );

VOID Real9_CB_SetDimensions(RV9_PictureHeader *pPictureHeader)
{
    UINT32 i, j;
    RV9_ParsePicParam *pRv9ParsePicParam = &pPictureHeader->Rv9ParsePicParam;
    /* Set m_nMBs and m_nGOBs based on the image dimensions. */
    /* TBD, there's probably a formula that can be used here instead */
    /* of this nested if-then-else sequence. */

    if (pPictureHeader->pic_width_in_pixel == 128 && pPictureHeader->pic_height_in_pixel == 96)
    {
        pRv9ParsePicParam->m_nMBs   = 8;
        pRv9ParsePicParam->m_nGOBs  = 6;
    }
    else if (pPictureHeader->pic_width_in_pixel == 176 && pPictureHeader->pic_height_in_pixel == 144)
    {
        pRv9ParsePicParam->m_nMBs   = 11;
        pRv9ParsePicParam->m_nGOBs  = 9;
    }
    else if (pPictureHeader->pic_width_in_pixel == 352 && pPictureHeader->pic_height_in_pixel == 288)
    {
        pRv9ParsePicParam->m_nMBs   = 22;
        pRv9ParsePicParam->m_nGOBs  = 18;
    }
    else if (pPictureHeader->pic_width_in_pixel == 704 && pPictureHeader->pic_height_in_pixel == 576)
    {
        pRv9ParsePicParam->m_nMBs   = 44;
        pRv9ParsePicParam->m_nGOBs  = 36;
    }
    else if (pPictureHeader->pic_width_in_pixel == 1408 && pPictureHeader->pic_height_in_pixel == 1152)
    {
        pRv9ParsePicParam->m_nMBs   = 88;
        pRv9ParsePicParam->m_nGOBs  = 72;
    }
    else
    {
        pRv9ParsePicParam->m_nMBs  = (pPictureHeader->pic_width_in_pixel + 15) >> 4;
        pRv9ParsePicParam->m_nGOBs = (pPictureHeader->pic_height_in_pixel + 15) >> 4;
    }

    /* initialize m_mbaSize */
    j = pRv9ParsePicParam->m_nGOBs * pRv9ParsePicParam->m_nMBs - 1;
    for (i = 0; i < (MBA_Widths - 1) && MBA_NumMBs[i] <  j; i++);

    pRv9ParsePicParam->m_mbaSize = MBA_FieldWidth[i];
}


/* --------------------------------------------------------------------------- */
/*  CRealVideoBs::GetPicSize() */
/*  Gets the picture size from the bitstream. */
/* --------------------------------------------------------------------------- */
VOID Real9_CB_GetPicSize(BS *pBs, RV9_ParsePicParam *pRv9ParsePicParam, UINT32 *width, UINT32 *height)
{
    UINT32 code;
    UINT32 w, h;

    const UINT32 code_width[8] = {160, 176, 240, 320, 352, 640, 704, 0};
    const UINT32 code_height1[8] = {120, 132, 144, 240, 288, 480, 0, 0};
    const UINT32 code_height2[4] = {180, 360, 576, 0};

    /* If we're decoding a P or B frame, get 1 bit that signals */
    /* difference in size from previous reference frame. */
    if (pRv9ParsePicParam->ptype == RV9_ORG_INTERPIC || pRv9ParsePicParam->ptype == RV9_ORG_TRUEBPIC)
    {
        /* no diff in size */
        if ( Real9_CB_Get1Bit(pBs) )
        {
            *width = pRv9ParsePicParam->pwidth_prev;
            *height = pRv9ParsePicParam->pheight_prev;
            return;
        }
    }
    /* width */
    code = Real9_CB_GetBits(pBs, 3);

    w = code_width[code];
    if (w == 0)
    {
        do
        {
            code = Real9_CB_GetBits(pBs, 8);
            w += (code << 2);
        }
        while (code == 255);
    }

    /* height */
    code = Real9_CB_GetBits(pBs, 3);

    h = code_height1[code];
    if (h == 0)
    {
        code <<= 1;
        code |= Real9_CB_Get1Bit(pBs);
        code &= 3;
        h = code_height2[code];
        if (h == 0)
        {
            do
            {
                code = Real9_CB_GetBits(pBs, 8);
                h += (code << 2);
            }
            while (code == 255);
        }
    }

    *width = w;
    *height = h;
}


/* --------------------------------------------------------------------------- */
/*  [DEC] CBaseBitstream::GetBits() */
/*      Reads bits from buffer.  Supports up to 25 bits. */
/*      nbits   : number of bits to be read */
/* --------------------------------------------------------------------------- */
static const UINT32 GetBitsMask[25] =
{
    0x00000000, 0x00000001, 0x00000003, 0x00000007,
    0x0000000f, 0x0000001f, 0x0000003f, 0x0000007f,
    0x000000ff, 0x000001ff, 0x000003ff, 0x000007ff,
    0x00000fff, 0x00001fff, 0x00003fff, 0x00007fff,
    0x0000ffff, 0x0001ffff, 0x0003ffff, 0x0007ffff,
    0x000fffff, 0x001fffff, 0x003fffff, 0x007fffff,
    0x00ffffff
};


SINT32 Real9_CB_FindNextSliceStartCode(BS *pBs)
{
    SINT32 i, RemainByte;

    BsToNextByte(pBs);

    RemainByte = (BsResidBits(pBs) / 8) - 2;
    for (i = 0; i < RemainByte; i++)
    {
        if (FIELDVAL_SSC == (UINT32)BsShow(pBs, FIELDLEN_SSC))
        {
            return RV9_VFMW_TRUE;
        }

        BsSkip(pBs, 8);
    }

    return RV9_VFMW_FALSE;
}


/* --------------------------------------------------------------------------- */
/*  [DEC] CBaseBitstream::SearchBits_IgnoreOnly0() */
/*      Searches for a code with known number of bits.  Skips only zero bits. */
/*      Search fails if code has not been found and non-zero bit encountered. */
/*      nbits       : number of bits in the code */
/*      code        : code to search for */
/*      lookahead   : maximum number of bits to parse for the code */
/* --------------------------------------------------------------------------- */
SINT32 Real9_CB_SearchBits_IgnoreOnly0(
    BS *pBs,
    const UINT32   nbits,
    const UINT32   code,
    const UINT32   lookahead)
{
    UINT32 w, n, msb;

    msb = 1 << (nbits - 1);

    w = Real9_CB_GetBits(pBs, nbits);

    for (n = 0; w != code && n < lookahead; n++)
    {
        if (w & msb) { break; }
        w = ( (w << 1) & GetBitsMask[nbits] ) | Real9_CB_Get1Bit(pBs);     //???????
    }

    if (w == code)
    {
        return RV9_VFMW_TRUE;
    }
    else
    {
        return RV9_VFMW_FALSE;
    }
}


SINT32 Real9_CB_GetSSC(BS *pBs, RV9_PictureHeader *pPictureHeader)
{
    //const UINT32 MAX_SSC_LOOKAHEAD_NUMBER = 7;

    if (RV9_FID_REALVIDEO30 == pPictureHeader->Fid)
    {
#if 0
        UINT32 offset, i, deltaofs;

        offset = Real9_CB_GetBsOffset(t);
        RVAssert(offset >= SliceBitOffset(0) &&
                    offset < (Real9_CB_GetMaxBsSize(t) << 3));
        /* locate current slice, i - 1 */
        for (i = 1; i < t->m_nSlices && offset >= SliceBitOffset(i); i ++){};
        /* current slice must be valid at this point */
        RVAssert(SliceFlag(i - 1));
        /* check if just beginning to decode the current slice */
        if (offset == SliceBitOffset(i - 1))
        { return RV9_VFMW_TRUE; }
        /* there is no more slice header in the bitstream */
        if (i == t->m_nSlices)
        { return RV9_VFMW_FALSE; }
        /* skip stuffing if any */
        deltaofs = SliceBitOffset(i) - offset;
        if (deltaofs < 8 && Real9_CB_SearchBits(t,deltaofs, 0, 0))
        { return RV9_VFMW_TRUE; }
#endif
    }
    else  //(RV9_FID_RV89COMBO == pPictureHeader->Fid)
    {
        //if ( Real9_CB_SearchBits_IgnoreOnly0( pBs, FIELDLEN_SSC, FIELDVAL_SSC,
        //        MAX_SSC_LOOKAHEAD_NUMBER ) )
        if ( Real9_CB_FindNextSliceStartCode(pBs) )
        { return RV9_VFMW_TRUE; }
        //GetSSC - SSC not found;
    }

    return RV9_VFMW_FALSE;
}


SINT32 Real9_CB_GetSliceHeader(
    BS *pBs,
    UINT32 bFirstSlice,
    SINT32 *iSliceMBA,
    SINT32 *iSliceGFID,
    SINT32 *iSQUANT,
    RV9_PictureHeader *pPictureHeader)
{
    RV9_ParsePicParam *pRv9ParsePicParam = &pPictureHeader->Rv9ParsePicParam;

    if (RV9_FID_REALVIDEO30 == pPictureHeader->Fid)
    {
        /* skip if this is the first slice called from IAPass1ProcessFrame */
        /* otherwise read the slice header */
        if (!bFirstSlice)
        {
            /* this was called from GetPicHeader */
            if (pRv9ParsePicParam->mba == -1)
            {
                bFirstSlice = RV9_VFMW_TRUE;
            }
            /* RealNetworks Slice Header */
            /* ECC */
            if (Real9_CB_Get1Bit(pBs) != 0)
            {
                return RV9_VFMW_FALSE;
            }
            /* PTYPE */
            if (bFirstSlice)
            {
                pRv9ParsePicParam->ptype = (EnumRV9PicCodType)Real9_CB_GetBits(pBs, 2);
            }
            else
            {
                if ( (EnumRV9PicCodType)Real9_CB_GetBits(pBs, 2) != pRv9ParsePicParam->ptype )
                {
                    return RV9_VFMW_FALSE;
                }
            }
            /* PQUANT/SQUANT */
            pRv9ParsePicParam->pquant = Real9_CB_GetBits(pBs, FIELDLEN_SQUANT);
            /* 0-31 are legitimate QP values for RV89Combo */
            if (pRv9ParsePicParam->pquant > 31)
            {
                return RV9_VFMW_FALSE;
            }
            /* Bitstream version */
            if (Real9_CB_Get1Bit(pBs) != 0)
            {
                return RV9_VFMW_FALSE;
            }
            if (Real9_CB_Get1Bit(pBs))
            {
                return RV9_VFMW_FALSE;
            }
            /* OSV Quant */
            pPictureHeader->OSVQUANT = Real9_CB_GetBits(pBs, 2);
            /* In-loop deblocking */
            pRv9ParsePicParam->deblocking_filter_passthrough = 
            Real9_CB_GetBits(pBs, 1) ? 1 : 0;

            if (bFirstSlice)
            {
                pRv9ParsePicParam->tr = Real9_CB_GetBits(pBs, FIELDLEN_TR_RV);
            }
            else
            {
                if (Real9_CB_GetBits(pBs, FIELDLEN_TR_RV) != pRv9ParsePicParam->tr)
                {
                    return RV9_VFMW_FALSE;
                }
            }

            /* PCTSZ (RealVideo RPR picture size) */
            {
                UINT32 width, height;
                if (bFirstSlice)
                {
                    switch (pRv9ParsePicParam->ptype)
                    {
                    case RV9_ORG_INTRAPIC:
                    case RV9_ORG_FORCED_INTRAPIC:
                        pRv9ParsePicParam->pwidth_prev  = 0;
                        pRv9ParsePicParam->pheight_prev = 0;
                        break;
                    case RV9_ORG_INTERPIC:
                        pRv9ParsePicParam->pwidth_prev  = pRv9ParsePicParam->pwidth;
                        pRv9ParsePicParam->pheight_prev = pRv9ParsePicParam->pheight;
                        break;
                    default:      //???????
                        break;
                    }
                }

                Real9_CB_GetPicSize(pBs, pRv9ParsePicParam, &width, &height);
                if (bFirstSlice)
                {
                    pRv9ParsePicParam->pwidth = width;
                    pRv9ParsePicParam->pheight = height;
                    /* TBD, why is parc set here? */
                    pPictureHeader->pic_width_in_pixel = width;
                    pPictureHeader->pic_height_in_pixel = height;
                    if ( ( (pPictureHeader->pic_width_in_pixel<48) || (pPictureHeader->pic_width_in_pixel>MAX_HOR_SIZE) ) || 
                         ( (pPictureHeader->pic_height_in_pixel<48) || (pPictureHeader->pic_height_in_pixel>MAX_VER_SIZE) ) )
                    {
                           return RV9_VFMW_FALSE;
                    }
                    Real9_CB_SetDimensions(pPictureHeader);
                }
                else
                {
                    if (pRv9ParsePicParam->pwidth != width || pRv9ParsePicParam->pheight != height)
                    {
                        return RV9_VFMW_FALSE;
                    }
                }
            }

            /* MBA */
            pRv9ParsePicParam->mba = Real9_CB_GetBits(pBs, pRv9ParsePicParam->m_mbaSize);
        }

        *iSliceMBA = pRv9ParsePicParam->mba;
        *iSQUANT = pRv9ParsePicParam->pquant;
        *iSliceGFID = 0;
    }
    else  //(RV9_FID_RV89COMBO == pPictureHeader->Fid)
    {
        /* The SSC either does not exist because this is the first slice */
        /* after the picture start code, or the SSC has already been read */
        /* in IAPass1. */
        if (!bFirstSlice)
        {
            /* Must be 1 to prevent start code emulation (SEPB1) */
            if (Real9_CB_Get1Bit(pBs) != 1)
            {
                return RV9_VFMW_FALSE;
            }
            /* No SSBI since CPM can not be "1". */
            /* Get macro-block address */
            *iSliceMBA = Real9_CB_GetBits(pBs, pRv9ParsePicParam->m_mbaSize);
            if (pRv9ParsePicParam->m_mbaSize > 11)
            {
                /* Must be 1 to prevent start code emulation (SEPB2) */
                if (Real9_CB_Get1Bit(pBs) != 1)
                {
                    return RV9_VFMW_FALSE;
                }
            }
            /* Get SQUANT */
            *iSQUANT = Real9_CB_GetBits(pBs, FIELDLEN_SQUANT);
            /* 0-31 are legitimate QP values for RV89Combo */
            if (*iSQUANT > 31)
            {
                return RV9_VFMW_FALSE;
            }
            /* OSV Quant */
            pPictureHeader->OSVQUANT = Real9_CB_GetBits(pBs, 2);
            /* No SWI field. */
            /* Must be 1 to prevent start code emulation (SEPB3) */
            if (Real9_CB_Get1Bit(pBs) != 1)
            {
                return RV9_VFMW_FALSE;
            }
            /* Get GOB frame ID. */
            *iSliceGFID = Real9_CB_GetBits(pBs, FIELDLEN_GFID);
        }
        else
        {
            *iSliceMBA = 0;
            *iSQUANT = -1;
        }
    }

    return RV9_VFMW_TRUE;
}


SINT32 Real9_CB_GetPictureHeader(BS *pBs, RV9_PictureHeader *pPictureHeader)
{
    SINT32 Status = VF_OK;
    SINT32 gfid, mba, squant;
    SINT32 tmp;
    RV9_ParsePicParam *pRv9ParsePicParam = &pPictureHeader->Rv9ParsePicParam;

    if (RV9_FID_REALVIDEO30 == pPictureHeader->Fid)
    {
        /* get the first slice header */
        /* set m_rv.mba to -1 to indicate this is a call to GetSliceHeader from  */
        /* GetPicHeader */
        pRv9ParsePicParam->mba = -1;
        if ( RV9_VFMW_TRUE == Real9_CB_GetSliceHeader(pBs, RV9_VFMW_FALSE, &mba, &gfid, &squant, pPictureHeader) )
        {
            switch (pRv9ParsePicParam->ptype)
            {
                case RV9_ORG_FORCED_INTRAPIC:
                    pPictureHeader->PicCodType = RV9_INTRAPIC;
                    pRv9ParsePicParam->m_isForcedKey = RV9_VFMW_TRUE;
                    break;
                case RV9_ORG_INTRAPIC:
                    pPictureHeader->PicCodType = RV9_INTRAPIC;
                    pRv9ParsePicParam->m_isForcedKey = RV9_VFMW_FALSE;
                    break;
                case RV9_ORG_INTERPIC:
                    pPictureHeader->PicCodType = RV9_INTERPIC;
                    break;
                case RV9_ORG_TRUEBPIC:
                    pPictureHeader->PicCodType = RV9_TRUEBPIC;
                    break;
                default:
                    Status = VF_ERR_PARAM;
                    break;
            }
            pPictureHeader->Deblocking_Filter_Passthrough = pRv9ParsePicParam->deblocking_filter_passthrough;
            pPictureHeader->PQUANT = pRv9ParsePicParam->pquant;
            pPictureHeader->TR = pRv9ParsePicParam->tr;
            pPictureHeader->TRB = pRv9ParsePicParam->trb;
            pPictureHeader->DBQUANT = pRv9ParsePicParam->dbq;

            /* initialize m_nGOBS, m_nMBs, and m_mbaSize */
            if ( ( (pPictureHeader->pic_width_in_pixel<48) || (pPictureHeader->pic_width_in_pixel>MAX_HOR_SIZE) ) || 
                 ( (pPictureHeader->pic_height_in_pixel<48) || (pPictureHeader->pic_height_in_pixel>MAX_VER_SIZE) ) )
            {
                   return VF_ERR_PARAM;
            }
            Real9_CB_SetDimensions(pPictureHeader);
        }
        else
        {
            Status = VF_ERR_PARAM;
        }
    }
    else  //(RV9_FID_RV89COMBO == pPictureHeader->Fid)
    {
        UINT32 length, info;
        const UINT32 PSC_LEN = 31;

        memset(pPictureHeader, 0, sizeof(*pPictureHeader));

        /* SUPER_VLC needs longer start code to avoid emulation */
        tmp = Real9_CB_GetBits(pBs, 16);
        if (tmp != 0x5555)
        {
            return VF_ERR_PARAM;
        }
        tmp = Real9_CB_GetBits(pBs, 16);
        if (tmp != 0x5555)
        {
            return VF_ERR_PARAM;
        }
        length = Real9_CB_GetVLCBits(pBs, &info);
        if (length < PSC_LEN)
        {
            return VF_ERR_PARAM;
        }
        if (info & 1)
        {
            return VF_ERR_PARAM;
        }
        if (!((info>>1) & 1))
        {
            /* QCIF; */
            pPictureHeader->pic_width_in_pixel = 176;
            pPictureHeader->pic_height_in_pixel = 144;
        }
        else 
        {
            pPictureHeader->pic_width_in_pixel = 0;
            pPictureHeader->pic_height_in_pixel = 0;
            /* Read dimensions from the bitstream, below */
        }
        pPictureHeader->PQUANT = (info>>2) & 31;
        pPictureHeader->TR = (info>>(2+5)) & 255;

        /* Picture type */
        length = Real9_CB_GetVLCBits(pBs, &info);
        if (length == 1)
        {
            pPictureHeader->PicCodType = RV9_INTERPIC;
        }
        else if (length == 3 && info == 1)
        {
            pPictureHeader->PicCodType = RV9_INTRAPIC;
        }
        else if (length == 5 && info == 0)
        {
            pPictureHeader->PicCodType = RV9_TRUEBPIC;
        }
        else
        {
            return VF_ERR_PARAM;
        }
        /* Non-QCIF frame size */
        if (pPictureHeader->pic_width_in_pixel == 0)
        {
            if ( RV9_VFMW_FALSE == Real9_CB_GetCPFMT(pBs, pPictureHeader) )
            {
                return VF_ERR_PARAM;
            }
        }

        if ( ( (pPictureHeader->pic_width_in_pixel<48) || (pPictureHeader->pic_width_in_pixel>MAX_HOR_SIZE) ) || 
             ( (pPictureHeader->pic_height_in_pixel<48) || (pPictureHeader->pic_height_in_pixel>MAX_VER_SIZE) ) )
        {
               return VF_ERR_PARAM;
        }
        Real9_CB_SetDimensions(pPictureHeader);

        /* OSV Quant */
        pPictureHeader->OSVQUANT = Real9_CB_GetBits(pBs, 2);
    }

    pPictureHeader->pic_width_in_mb = (pPictureHeader->pic_width_in_pixel + 15) / 16;
    pPictureHeader->pic_height_in_mb = (pPictureHeader->pic_height_in_pixel + 15) / 16;
    pPictureHeader->total_mbs = pPictureHeader->pic_width_in_mb * pPictureHeader->pic_height_in_mb;

    return Status;
}


VOID Real9_SetImgFormat(RV9_CTX_S *pCtx)
{
    UINT32 codtype, csp, vfmt, sfmt, fldflg, fldfst = 0, dar;
    RV9_CODECINF *pRv9CodecInfo;
    RV9_PictureHeader *pPictureHeader;
    IMAGE *pImg;

    pRv9CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;

    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pRv9CodecInfo->CurFsID);
    if (NULL == pImg)
    {
        return;
    }

    codtype = pPictureHeader->PicCodType;
    csp = 0;
    vfmt = 5;
    sfmt = 0;
    fldflg = (pImg->format>>10)&0x3;
    fldflg |= 3;  // frame
    fldfst = 1;  //逐行序列指定顶场先显示
    dar = 0;

    pImg->format = ((dar&7)<<14)|((fldfst&0x3)<<12)|((fldflg&3)<<10)|((sfmt&3)<<8)|((vfmt&3)<<5)|((csp&7)<<2)|(codtype&3);
    pImg->top_fld_type = codtype&3;
    pImg->bottom_fld_type = codtype&3;
    pImg->is_fld_save = 0;
    pImg->image_width = pPictureHeader->pic_width_in_pixel;
    pImg->image_height = pPictureHeader->pic_height_in_pixel;

	SetAspectRatio(pImg,(VDEC_DAR_E)dar);
	
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
}

/*!
************************************************************************
*    函数原型 :  RV9_RecordVFMWState(VOID)
*    功能描述 :  记录VFMW的工作状态
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID RV9_RecordVFMWState(RV9_CTX_S *pCtx)
{
    RV9_CODECINF *pRv9CodecInfo;

    pRv9CodecInfo = &pCtx->CodecInfo;

    return;
}


VOID Real9_WriteSliceMsg(RV9_CTX_S *pCtx, SINT32 HoldSliceNum)
{
    RV9_DEC_PARAM_S *pRv9DecParam;
    RV9_CODECINF *pRv9CodecInfo;
    RV9_PictureHeader *pPictureHeader;
    RV9_SliceHeader *pSliceHeader;
    RV9_SLC_PARAM_S *pSliceParam;

    pRv9DecParam = &pCtx->Rv9DecParam;
    pRv9CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;
    pSliceHeader = &pCtx->CodecInfo.SliceHeader;

    pSliceParam = &pRv9DecParam->SliceParam[HoldSliceNum];

    pSliceParam->StreamPhyAddr[0] = pSliceHeader->bit_stream_addr_0;
    pSliceParam->StreamBitOffset[0] = pSliceHeader->bit_offset_0;
    pSliceParam->StreamLength[0] = pSliceHeader->bit_len_0;

    pSliceParam->StreamPhyAddr[1] = pSliceHeader->bit_stream_addr_1;
    pSliceParam->StreamBitOffset[1] = pSliceHeader->bit_offset_1;
    pSliceParam->StreamLength[1] = pSliceHeader->bit_len_1;

    pSliceParam->dblk_filter_passthrough = pSliceHeader->dblk_filter_passthrough;
    pSliceParam->osvquant = pSliceHeader->osvquant;
    pSliceParam->sliceqp = pSliceHeader->SliceQP;
    pSliceParam->first_mb_in_slice = pSliceHeader->first_mb_in_slice;
    //pSliceParam->last_mb_in_slice = pSliceHeader->last_mb_in_slice;

    pRv9DecParam->TotalSliceNum = HoldSliceNum + 1;

    return;
}


VOID Real9_WritePicMsg(RV9_CTX_S *pCtx)
{
    RV9_DEC_PARAM_S *pRv9DecParam;
    RV9_CODECINF *pRv9CodecInfo;
    RV9_PictureHeader *pPictureHeader;

    pRv9DecParam = &pCtx->Rv9DecParam;
    pRv9CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;

    pRv9DecParam->PicCodingType = pPictureHeader->PicCodType;
    pRv9DecParam->PicWidthInMb = pPictureHeader->pic_width_in_mb;
    pRv9DecParam->PicHeightInMb = pPictureHeader->pic_height_in_mb;
    pRv9DecParam->Ratio0 = pRv9CodecInfo->Ratio0;
    pRv9DecParam->Ratio1 = pRv9CodecInfo->Ratio1;

    pRv9DecParam->PQUANT = pPictureHeader->PQUANT;
    pRv9DecParam->PrevPicQP = pRv9CodecInfo->PrevPicQP;
    pRv9DecParam->PrevPicMb0QP = pRv9CodecInfo->PrevPicMb0QP;

    if (RV9_TRUEBPIC != pPictureHeader->PicCodType)
    {
        pRv9CodecInfo->PrevPicQP = pPictureHeader->PQUANT;
    }

    return;
}


VOID Real9_WriteReg(RV9_CTX_S *pCtx, UINT32 fst_slc_grp)
{
    RV9_DEC_PARAM_S *pRv9DecParam;

    pRv9DecParam = &pCtx->Rv9DecParam;
    pRv9DecParam->FstSlcGrp = fst_slc_grp;

    return;
}


SINT32 Real9_ModifySliceMsg(RV9_CTX_S *pCtx)
{
    RV9_DEC_PARAM_S *pRv9DecParam;
    UADDR stream_base_addr;
	UINT32 BytePos0, BytePos1;
    SINT32 i, TotalMbnMinus1;

    pRv9DecParam = &pCtx->Rv9DecParam;

    TotalMbnMinus1 = pRv9DecParam->PicWidthInMb * pRv9DecParam->PicHeightInMb - 1;

    if (0 != pRv9DecParam->SliceParam[0].first_mb_in_slice)
    {
        return RV9_VFMW_FALSE;
    }

    if (pRv9DecParam->TotalSliceNum > 2)
    {
        for (i=1; i<pRv9DecParam->TotalSliceNum-1; i++)
        {
            if ( (pRv9DecParam->SliceParam[i].first_mb_in_slice <= 0) || (pRv9DecParam->SliceParam[i].first_mb_in_slice >= TotalMbnMinus1) )
            {
                return RV9_VFMW_FALSE;
            }
        }
    }

    if (pRv9DecParam->TotalSliceNum > 1)
    {
        for (i=0; i<pRv9DecParam->TotalSliceNum-1; i++)
        {
            if (pRv9DecParam->SliceParam[i].first_mb_in_slice >= pRv9DecParam->SliceParam[i+1].first_mb_in_slice)
            {
                return RV9_VFMW_FALSE;
            }
        }

        if ( (pRv9DecParam->SliceParam[pRv9DecParam->TotalSliceNum-1].first_mb_in_slice <= 0) || 
        	  (pRv9DecParam->SliceParam[pRv9DecParam->TotalSliceNum-1].first_mb_in_slice > TotalMbnMinus1) )
        {
            return RV9_VFMW_FALSE;
        }
    }

    for (i=0; i<pRv9DecParam->TotalSliceNum; i++)
    {
        if (pRv9DecParam->TotalSliceNum-1 == i)
        {
            pRv9DecParam->SliceParam[i].last_mb_in_slice = TotalMbnMinus1;
        }
        else
        {
            pRv9DecParam->SliceParam[i].last_mb_in_slice = pRv9DecParam->SliceParam[i+1].first_mb_in_slice - 1;
        }

        if ( (pRv9DecParam->SliceParam[i].first_mb_in_slice > pRv9DecParam->SliceParam[i].last_mb_in_slice) ||
              ( (pRv9DecParam->SliceParam[i].first_mb_in_slice < 0) || (pRv9DecParam->SliceParam[i].first_mb_in_slice > TotalMbnMinus1) ) ||
              ( (pRv9DecParam->SliceParam[i].last_mb_in_slice < 0) || (pRv9DecParam->SliceParam[i].last_mb_in_slice > TotalMbnMinus1) )
           )
        {
            return RV9_VFMW_FALSE;
        }
    }

    // find stream_base_addr
    stream_base_addr = pRv9DecParam->SliceParam[0].StreamPhyAddr[0];

    for (i=0; i<pRv9DecParam->TotalSliceNum; i++)
    {
        if (pRv9DecParam->SliceParam[i].StreamPhyAddr[0] < stream_base_addr)
        {
            stream_base_addr = pRv9DecParam->SliceParam[i].StreamPhyAddr[0];
        }

        if ( (pRv9DecParam->SliceParam[i].StreamPhyAddr[1]<stream_base_addr) && (0!=pRv9DecParam->SliceParam[i].StreamLength[1]) )
        {
            stream_base_addr = pRv9DecParam->SliceParam[i].StreamPhyAddr[1];
        }
    }

    pRv9DecParam->StreamBaseAddr = stream_base_addr & 0xFFFFFFF0;

    for (i=0; i<pRv9DecParam->TotalSliceNum; i++)
    {
        if (0 == pRv9DecParam->SliceParam[i].StreamPhyAddr[1])  //只有一包码流
        {
            BytePos0 = pRv9DecParam->SliceParam[i].StreamPhyAddr[0] - pRv9DecParam->StreamBaseAddr 
                 + pRv9DecParam->SliceParam[i].StreamBitOffset[0]/8;

            pRv9DecParam->SliceParam[i].StreamPhyAddr[0] = BytePos0 & 0xFFFFFFF0;
            pRv9DecParam->SliceParam[i].StreamBitOffset[0] = 8*(BytePos0 & 0x0000000F)
                 + pRv9DecParam->SliceParam[i].StreamBitOffset[0]%8;
        }
        else  //两包码流
        {
            BytePos0 = pRv9DecParam->SliceParam[i].StreamPhyAddr[0] - pRv9DecParam->StreamBaseAddr 
                 + pRv9DecParam->SliceParam[i].StreamBitOffset[0]/8;
            pRv9DecParam->SliceParam[i].StreamPhyAddr[0] = BytePos0 & 0xFFFFFFF0;
            pRv9DecParam->SliceParam[i].StreamBitOffset[0] = 8*(BytePos0 & 0x0000000F)
                 + pRv9DecParam->SliceParam[i].StreamBitOffset[0]%8;

            BytePos1 = pRv9DecParam->SliceParam[i].StreamPhyAddr[1] - pRv9DecParam->StreamBaseAddr 
                 + pRv9DecParam->SliceParam[i].StreamBitOffset[1]/8;
            pRv9DecParam->SliceParam[i].StreamPhyAddr[1] = BytePos1 & 0xFFFFFFF0;
            pRv9DecParam->SliceParam[i].StreamBitOffset[1] = 8*(BytePos1 & 0x0000000F)
                 + pRv9DecParam->SliceParam[i].StreamBitOffset[1]%8;
        }
    }

    return RV9_VFMW_TRUE;
}


SINT32 REAL9DEC_Init(RV9_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    RV9_CODECINF *pRv9CodecInfo;
    RV9_PictureHeader *pPictureHeader;
    SINT32 ImgQueRstMagic;
    
    //初始化
    memset(pCtx, 0, sizeof(RV9_CTX_S));
    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue);
        
    pCtx->pstExtraData = pstExtraData;
    pRv9CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;

    pRv9CodecInfo->PrevPicQP = 0x0F;
    pRv9CodecInfo->PrevPicMb0QP = 0x0F;
    pRv9CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
    pRv9CodecInfo->Imgbuf_allocated = RV9_VFMW_FALSE;

    pPictureHeader->Fid = RV9_FID_REALVIDEO30;
    pPictureHeader->m_uTRWrap = RV9_TR_WRAP_RV;
    pPictureHeader->pixel_aspect_ratio = RV9_PARC_SQUARE;

    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }

    return 0;
}


VOID REAL9DEC_Destroy(RV9_CTX_S *pCtx)
{
    RV9_CODECINF *pRv9CodecInfo;

    pRv9CodecInfo = &pCtx->CodecInfo;
    dprint(PRN_CTRL, "Decoding quits at frm %d\n", pRv9CodecInfo->FrmCnt);

    return;
}


SINT32 REAL9DEC_Decode(RV9_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    RV9_PictureHeader TmpPictureHeader = {0};
    RV9_PictureHeader *pTmpPictureHeader = &TmpPictureHeader;
    RV9_PictureHeader *pPictureHeader = NULL;
    RV9_SliceHeader   *pSliceHeader   = NULL;
    UINT32 Ratio0, Ratio1;
    SINT32 trb, trd;
    SINT32 mbn, mbx, mby, SliceNum, HoldSliceNum;
    UINT32 bFirstSlice;
    SINT32 iSliceMBA, iSliceGFID, iSQUANT;
    SINT32 found_ssc;
    UINT32 QP, EntropyQP, quant_prev;
    UINT32 fst_slc_grp, last_slc_grp;
    UINT32 i, SliceByteOffset;
    SINT32 PrevHeaderBytes = 0, PrevOffsetBytes = 0;
    BS    *pBs  = NULL;
    IMAGE *pImg = NULL;
    FSP_LOGIC_FS_S *pCur, *pBwd, *pFwd;
    RV9_DEC_PARAM_S *pRv9DecParam  = NULL;
    RV9_CODECINF    *pRv9CodecInfo = NULL;

    pRv9DecParam = &pCtx->Rv9DecParam;
    pRv9CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;
    pSliceHeader = &pCtx->CodecInfo.SliceHeader;

    pPictureHeader->Rv9ParsePicParam.pwidth_prev = pPictureHeader->Rv9ParsePicParam.pwidth;
    pPictureHeader->Rv9ParsePicParam.pheight_prev = pPictureHeader->Rv9ParsePicParam.pheight;
    pTmpPictureHeader->Rv9ParsePicParam.pwidth_prev = pPictureHeader->Rv9ParsePicParam.pwidth;
    pTmpPictureHeader->Rv9ParsePicParam.pheight_prev = pPictureHeader->Rv9ParsePicParam.pheight;
    pTmpPictureHeader->Rv9ParsePicParam.pwidth = pPictureHeader->Rv9ParsePicParam.pwidth;
    pTmpPictureHeader->Rv9ParsePicParam.pheight = pPictureHeader->Rv9ParsePicParam.pheight;

    pPictureHeader->Fid = RV9_FID_REALVIDEO30;
    pPictureHeader->m_uTRWrap = RV9_TR_WRAP_RV;

    TmpPictureHeader.Fid = pPictureHeader->Fid;
    TmpPictureHeader.m_uTRWrap = pPictureHeader->m_uTRWrap;

    if (NULL == pPacket)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet pointer!\n", pRv9CodecInfo->FrmCnt);
        return RV9_VFMW_FALSE;
    }

    memset( pRv9DecParam, 0, sizeof(RV9_DEC_PARAM_S) );

    //if start new pic, length1 should be reserved for VFMW searching and parsing
    pRv9CodecInfo->BsOffset = 0;
    pRv9CodecInfo->PacketTail = pPacket->StreamPack[0].LenInByte;

    //adjust bs start address from updated offset
    pRv9CodecInfo->BsPhyAddr = pPacket->StreamPack[0].PhyAddr + pRv9CodecInfo->BsOffset;
    pRv9CodecInfo->BsVirAddr = pPacket->StreamPack[0].VirAddr + pRv9CodecInfo->BsOffset;
    pRv9CodecInfo->BsLength  = pPacket->StreamPack[0].LenInByte - pRv9CodecInfo->BsOffset;
    pRv9CodecInfo->IsLastSeg = pPacket->StreamPack[0].IsLastSeg;

    if (1 != pPacket->StreamPack[0].IsLastSeg)
    {
        pRv9CodecInfo->BsPhyAddr1 =  pPacket->StreamPack[1].PhyAddr;
        pRv9CodecInfo->BsVirAddr1 =  pPacket->StreamPack[1].VirAddr;
        pRv9CodecInfo->BsLength1 =  pPacket->StreamPack[1].LenInByte;
        pRv9CodecInfo->IsLastSeg1 = pPacket->StreamPack[1].IsLastSeg;
        if (1 != pPacket->StreamPack[1].IsLastSeg)
        {
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[0].StreamID);
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[1].StreamID);
            return RV9_VFMW_FALSE;
        }
    }
    else
    {
        pRv9CodecInfo->BsPhyAddr1 = 0;
        pRv9CodecInfo->BsVirAddr1 = 0;
        pRv9CodecInfo->BsLength1  = 0;
        pRv9CodecInfo->IsLastSeg1 = 0;
    }

    if ( (pRv9CodecInfo->BsLength < 10) || (pRv9CodecInfo->BsLength >= 3*1024*1024) )
    {
        return RV9_VFMW_FALSE;
    }

    /*码流管理初始化*/
    if (NULL == pRv9CodecInfo->BsVirAddr)
    {
        return RV9_VFMW_FALSE;
    }
    BsInit(pBs, pRv9CodecInfo->BsVirAddr, pRv9CodecInfo->BsLength);

    pRv9CodecInfo->TotalSliceNum = Real9_CB_GetBits(pBs, 8) + 1;
    if ( (pRv9CodecInfo->TotalSliceNum > 256) || (pRv9CodecInfo->TotalSliceNum < 1) )
    {
        return RV9_VFMW_FALSE;
    }

    for (i=0; i<pRv9CodecInfo->TotalSliceNum; i++)
    {
        BsSkip(pBs, 32);
        SliceByteOffset = Real9_CB_GetBits(pBs, 32);
        pRv9CodecInfo->SliceByteOffset[i] = REVERSE_ENDIAN32( SliceByteOffset );
        if (pRv9CodecInfo->SliceByteOffset[i] >= 3*1024*1024)
        {
            return RV9_VFMW_FALSE;
        }
    }

    for (i=0; i<pRv9CodecInfo->TotalSliceNum-1; i++)
    {
        if (pRv9CodecInfo->SliceByteOffset[i+1] <= pRv9CodecInfo->SliceByteOffset[i])
        {
            return RV9_VFMW_FALSE;
        }
    }

    /*Picture Header 解码*/
    PrevHeaderBytes = pRv9CodecInfo->TotalSliceNum*8+1;
    PrevOffsetBytes = PrevHeaderBytes + pRv9CodecInfo->SliceByteOffset[0];
    if ( (PrevHeaderBytes >= 3*1024*1024) || (PrevOffsetBytes >= 3*1024*1024) )
    {
        return RV9_VFMW_FALSE;
    }
    if ( (PrevOffsetBytes < 1) || (pRv9CodecInfo->BsLength-PrevOffsetBytes < 1) )
    {
        return RV9_VFMW_FALSE;
    }
    BsInit(pBs, pRv9CodecInfo->BsVirAddr+PrevOffsetBytes, pRv9CodecInfo->BsLength-PrevOffsetBytes);

    if ( VF_OK != Real9_CB_GetPictureHeader(pBs, &TmpPictureHeader) )
    {
        dprint(PRN_ERROR, "Real9_CB_GetPictureHeader Error!\n");
        return RV9_VFMW_FALSE;  //Error
    }

    //VHB 地址分配
     if ( (RV9_VFMW_FALSE == pRv9CodecInfo->Imgbuf_allocated) ||
         (pTmpPictureHeader->pic_width_in_mb != pPictureHeader->pic_width_in_mb) ||
         (pTmpPictureHeader->pic_height_in_mb != pPictureHeader->pic_height_in_mb) )
    {
        //未分配或者大小变化后,需要修改VO管理结构内的信息
        REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pPictureHeader->pic_width_in_mb, pPictureHeader->pic_height_in_mb,\
            pTmpPictureHeader->pic_width_in_mb, pTmpPictureHeader->pic_height_in_mb);
        RV9_CLEARREFFLAG;
        RV9_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过 
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		
		if((pTmpPictureHeader->pic_width_in_mb > MAX_IMG_WIDTH_IN_MB) ||
			(pTmpPictureHeader->pic_height_in_mb > MAX_IMG_HEIGHT_IN_MB))
		{
			dprint(PRN_PIC, "pic width/height to large,MbWidth = %d, MbHeight = %d",
				pTmpPictureHeader->pic_width_in_mb,
				pTmpPictureHeader->pic_height_in_mb);
			return RV9_VFMW_FALSE;
		}
		
        if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
        {
            if (pRv9CodecInfo->Imgbuf_allocated == RV9_VFMW_FALSE)
            {
                ResetVoQueue(&pCtx->ImageQue);
            }
        }
        else
        {
            //未分配或者大小变化后,需要修改VO管理结构内的信息        
            ResetVoQueue(&pCtx->ImageQue);
        }
        dprint(PRN_ERROR, "new seq size %d * %d\n", pTmpPictureHeader->pic_width_in_mb, pTmpPictureHeader->pic_height_in_mb);
		
        if(RV9_VFMW_FALSE == Real9_ArrangeVHBMem(REAL9_MAXIMUM_IMAGE_NUM, pCtx, pTmpPictureHeader))
        {
			dprint(PRN_ERROR, "Real9_ArrangeVHBMem err\n"); 
			return RV9_VFMW_FALSE;
        }
    }

    memcpy( pPictureHeader, pTmpPictureHeader, sizeof(RV9_PictureHeader) );

    bFirstSlice = RV9_VFMW_TRUE;
    
    //fixed 20130603
    pRv9CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;

    //获取帧存
    if ( RV9_VFMW_FALSE == Real9_GetImageBuffer(pCtx) )
    {
        dprint(PRN_FATAL, "Fatal Error: frm%d, get image buffer failed\n", pRv9CodecInfo->FrmCnt);
        return RV9_VFMW_FALSE;
    }

    /* PTS */
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pRv9CodecInfo->CurFsID);
    if (NULL != pImg)
    {
        pImg->PTS = pCtx->pstExtraData->pts;
        pImg->Usertag = pCtx->pstExtraData->Usertag;
        pImg->DispTime = pCtx->pstExtraData->DispTime;
        pImg->DispEnableFlag = pCtx->pstExtraData->DispEnableFlag;
        pImg->DispFrameDistance = pCtx->pstExtraData->DispFrameDistance;
        pImg->DistanceBeforeFirstFrame = pCtx->pstExtraData->DistanceBeforeFirstFrame;
        pImg->GopNum = pCtx->pstExtraData->GopNum;

        pCtx->pstExtraData->pts = (UINT64)(-1);    
	    dprint(PRN_PTS,"dec_pts: %lld Usertag = %lld\n",pImg->PTS,pImg->Usertag);
    }
    else
    {
        FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
        return RV9_VFMW_FALSE;
    }

    /* 参考维护 */
    if (RV9_TRUEBPIC != pPictureHeader->PicCodType)
    {
        if ( (RV9_INTERPIC == pPictureHeader->PicCodType) && (pRv9CodecInfo->RefNum < 1) )
        {
            return RV9_VFMW_FALSE;
        }
        pRv9CodecInfo->RefNum = pRv9CodecInfo->RefNum>0 ? 2 : 1;
        if (pRv9CodecInfo->FwdFsID != pRv9CodecInfo->BwdFsID)
        {
            //这样释放的才是有效参考图
            dprint(PRN_REF, "---------- unref %d\n", pRv9CodecInfo->FwdFsID);
            FSP_SetRef(pCtx->ChanID, pRv9CodecInfo->FwdFsID, 0);
        }
        pRv9CodecInfo->FwdFsID = pRv9CodecInfo->BwdFsID;
        pRv9CodecInfo->BwdFsID = pRv9CodecInfo->CurFsID;
        FSP_SetRef(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);

        FSP_RemovePmv(pCtx->ChanID, pRv9CodecInfo->FwdFsID);
        dprint(PRN_REF, "++++++++++ ref %d\n", pRv9CodecInfo->CurFsID);
    }
    else
    {
        if (pRv9CodecInfo->RefNum < 2)
        {
            FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
            return RV9_VFMW_FALSE;
        }
    }

    pCur = FSP_GetLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID);
    pFwd = FSP_GetLogicFs(pCtx->ChanID, pRv9CodecInfo->FwdFsID);
    pBwd = FSP_GetLogicFs(pCtx->ChanID, pRv9CodecInfo->BwdFsID);

    if ((NULL == pCur) || (NULL == pFwd) || (NULL == pBwd))
    {
		dprint(PRN_FATAL, "CurFsID abnormal!,%s %d (NULL == pCur) || (NULL == pFwd) || (NULL == pBwd)!!\n",__FUNCTION__,__LINE__);
        return RV9_VFMW_FALSE;
    }

    if ((NULL == pCur->pstDecodeFs) || (NULL == pCur->pstTfOutFs) || (NULL == pCur->pstDispOutFs))
    {
        FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
        dprint(PRN_FATAL, "CurFsID abnormal!\n");
        return RV9_VFMW_FALSE;
    }
    else
    {
        pRv9DecParam->BwdRefPhyAddr   = (NULL != pBwd->pstDecodeFs)? pBwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pRv9DecParam->FwdRefPhyAddr   = (NULL != pFwd->pstDecodeFs)? pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pRv9DecParam->CurPicPhyAddr   = pCur->pstDecodeFs->PhyAddr;
        pRv9DecParam->CurrPmvPhyAddr = pCur->PmvAddr;

        pRv9DecParam->ColPmvPhyAddr = pBwd->PmvAddr;
        pRv9DecParam->DispFramePhyAddr = pCur->pstDispOutFs->PhyAddr;
    }

    dprint(PRN_REF, "dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p,%p,%p,%p,%p\n", pRv9DecParam->CurPicPhyAddr, pRv9DecParam->DispFramePhyAddr, 
           pRv9DecParam->FwdRefPhyAddr, pRv9DecParam->BwdRefPhyAddr, pRv9DecParam->CurrPmvPhyAddr, pRv9DecParam->ColPmvPhyAddr);

    pRv9DecParam->DDRStride = pCur->pstDispOutFs->Stride;
    pRv9CodecInfo->ddr_stride = pCur->pstDispOutFs->Stride;

    //计算TRB, TRD
    if (RV9_TRUEBPIC == pPictureHeader->PicCodType)
    {
        /* Compute ratios needed for direct mode */
        trb = (SINT32)pPictureHeader->TR - (SINT32)pFwd->TR;
        trd = (SINT32)pBwd->TR - (SINT32)pFwd->TR;

        if (trb  < 0)
        {
            trb += pPictureHeader->m_uTRWrap;
        }
        if (trd < 0)
        {
            trd += pPictureHeader->m_uTRWrap;
        }        
        if (trb > trd)      /* just in case TR's are incorrect */
        {
            trb = 0;
        }
        if (trd > 0)
        {
            Ratio0 = (trb << RV9_TR_SHIFT) / trd;
            Ratio1 = ((trd-trb) << RV9_TR_SHIFT) / trd;
        }
        else
        {
            Ratio0 = Ratio1 = 0;
        }

        pRv9CodecInfo->trb = trb;
        pRv9CodecInfo->trd = trd;

        pRv9CodecInfo->Ratio0 = Ratio0;
        pRv9CodecInfo->Ratio1 = Ratio1;
    }

    pCur->TR = pPictureHeader->TR;

    QP = pPictureHeader->PQUANT;
    quant_prev = QP;
    EntropyQP = QP;
    switch (pPictureHeader->OSVQUANT)
    {
    case 0:
        break;
    case 1:
        if (QP <= 25)
        {
            EntropyQP = MIN(30, QP+5);
        }
        break;
    case 2:
        if (QP <= 18)
        {
            EntropyQP = MIN(30, QP+10);
        }
        else if (QP <= 25)
        {
            EntropyQP = MIN(30, QP+5);
        }
        break;
    default:
        dprint(PRN_DBG, "Pos0: Illegal OSVQUANT=%d", pPictureHeader->OSVQUANT);
        break;
    }

    Real9_WritePicMsg(pCtx);

    mbn = 0;
    mbx = 0;
    mby = 0;
    fst_slc_grp = 1;
    SliceNum = 0;
    HoldSliceNum = 0;

    // Cfg Slice Msg Start
    pSliceHeader->bit_offset_0 = BsPos(pBs)%8;
    if (1 == pRv9CodecInfo->TotalSliceNum)
    {
        pSliceHeader->bit_len_0 = (pRv9CodecInfo->BsLength - PrevHeaderBytes - pRv9CodecInfo->SliceByteOffset[0])*8 - BsPos(pBs);
    }
    else
    {
        pSliceHeader->bit_len_0 = (pRv9CodecInfo->SliceByteOffset[1] - pRv9CodecInfo->SliceByteOffset[0])*8 - BsPos(pBs);
    }
    pSliceHeader->bit_stream_addr_0 = pRv9CodecInfo->BsPhyAddr + PrevOffsetBytes + BsPos(pBs)/8;

    pSliceHeader->bit_offset_1 = 0;
    pSliceHeader->bit_len_1 = 0;
    pSliceHeader->bit_stream_addr_1 = 0;

    pSliceHeader->SliceQP = QP;
    pSliceHeader->osvquant = pPictureHeader->OSVQUANT;
    pSliceHeader->dblk_filter_passthrough = pPictureHeader->Deblocking_Filter_Passthrough;
    pSliceHeader->first_mb_in_slice = mbn;
    Real9_WriteSliceMsg(pCtx, HoldSliceNum);
    SliceNum++;
    HoldSliceNum++;

   /*Slice Header解码*/
    for (i=1; i<pRv9CodecInfo->TotalSliceNum; i++)
    {
        PrevOffsetBytes = PrevHeaderBytes + pRv9CodecInfo->SliceByteOffset[i];
        if (PrevOffsetBytes >= 3*1024*1024)
        {
            FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
            return RV9_VFMW_FALSE;
        }
        if ( (PrevOffsetBytes < 1) || (pRv9CodecInfo->BsLength-PrevOffsetBytes < 1) )
        {
            FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
            return RV9_VFMW_FALSE;
        }
        BsInit(pBs, pRv9CodecInfo->BsVirAddr+PrevOffsetBytes, pRv9CodecInfo->BsLength-PrevOffsetBytes);
        
        bFirstSlice = RV9_VFMW_FALSE;  //RV9_VFMW_TRUE;
        found_ssc = Real9_CB_GetSliceHeader(pBs, bFirstSlice, &iSliceMBA, &iSliceGFID, &iSQUANT, pPictureHeader);
        if (RV9_VFMW_TRUE != found_ssc)
        {
            continue;
        }

        mbn = iSliceMBA;
		//冗余?
        if (pPictureHeader->pic_width_in_mb == 0)
        {
            FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
            return RV9_VFMW_FALSE;
        }

        mby = mbn / pPictureHeader->pic_width_in_mb;
        mbx = mbn % pPictureHeader->pic_width_in_mb;
        
        if (iSQUANT >= 0)
        {
            QP = quant_prev = iSQUANT;
        }
        EntropyQP = QP;
        switch (pPictureHeader->OSVQUANT)
        {
            case 0:
                break;
            case 1:
                if (QP <= 25)
                {
                    EntropyQP = MIN(30, QP+5);
                }
                break;
            case 2:
                if (QP <= 18)
                {
                    EntropyQP = MIN(30, QP+10);
                }
                else if (QP <= 25)
                {
                    EntropyQP = MIN(30, QP+5);
                }
                break;
            default:
                dprint(PRN_DBG, "Pos1: Illegal OSVQUANT=%d", pPictureHeader->OSVQUANT);
                break;
        }

        // Cfg Slice Msg Start
        pSliceHeader->bit_offset_0 = BsPos(pBs)%8;
        if (i == (pRv9CodecInfo->TotalSliceNum-1) )
        {
            pSliceHeader->bit_len_0 = (pRv9CodecInfo->BsLength - PrevHeaderBytes - pRv9CodecInfo->SliceByteOffset[i])*8 - BsPos(pBs);
        }
        else
        {
             if (i > (RV9_MAX_SLC_PARAM_NUM - 2))
             {
                 dprint(PRN_DBG, "line:%d! i > (RV9_MAX_SLC_PARAM_NUM - 2)\n",__LINE__);
                 return RV9_VFMW_FALSE;
             }
             pSliceHeader->bit_len_0 = (pRv9CodecInfo->SliceByteOffset[i+1] - pRv9CodecInfo->SliceByteOffset[i])*8 - BsPos(pBs);
        }

        pSliceHeader->bit_stream_addr_0 = pRv9CodecInfo->BsPhyAddr + PrevOffsetBytes + BsPos(pBs)/8;
        pSliceHeader->bit_offset_1 = 0;
        pSliceHeader->bit_len_1 = 0;
        pSliceHeader->bit_stream_addr_1 = 0;

        pSliceHeader->SliceQP = QP;
        pSliceHeader->osvquant = pPictureHeader->OSVQUANT;
        pSliceHeader->dblk_filter_passthrough = pPictureHeader->Deblocking_Filter_Passthrough;
        pSliceHeader->first_mb_in_slice = mbn;
        Real9_WriteSliceMsg(pCtx, HoldSliceNum);
        SliceNum++;
        HoldSliceNum++;

        if (HoldSliceNum >= REAL9_SLC_DN_MSG_SLOT_FULL_THRESHOLD)
        {
            // Start VDM
            if ( RV9_VFMW_TRUE != Real9_ModifySliceMsg(pCtx) )
            {
                FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
                return RV9_VFMW_FALSE;
            }
            pCtx->pRv9DecParam = &pCtx->Rv9DecParam;
        }
        // Cfg Slice Msg End
    }    

    last_slc_grp = 1;
    Real9_WriteReg(pCtx, fst_slc_grp);
    fst_slc_grp = 0;
    HoldSliceNum = 0;
    if (NULL==pCtx->pRv9DecParam)
    {
        if ( RV9_VFMW_TRUE != Real9_ModifySliceMsg(pCtx) )
        {
	        FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
	        return RV9_VFMW_FALSE;
        }
        pCtx->pRv9DecParam = &pCtx->Rv9DecParam;
    }

    if (1 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((NULL != pCtx->pRv9DecParam) && (RV9_TRUEBPIC == pCtx->pRv9DecParam->PicCodingType))
        {
            pCtx->pRv9DecParam = NULL;
            FSP_SetDisplay(pCtx->ChanID, pCtx->CodecInfo.CurFsID, 0);
            ReleasePacket(VFMW_REAL9, pCtx);
            return RV9_VFMW_FALSE;
        }
    }
    else if (2 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((pCtx->pstExtraData->stDisParams.s32DisNums > 0) && (NULL != pCtx->pRv9DecParam) 
            && (RV9_TRUEBPIC == pCtx->pRv9DecParam->PicCodingType))
        {
            pCtx->pRv9DecParam = NULL;
            FSP_SetDisplay(pCtx->ChanID, pCtx->CodecInfo.CurFsID, 0);
            pCtx->pstExtraData->stDisParams.s32DisNums--;
            ReleasePacket(VFMW_REAL9, pCtx);
            return RV9_VFMW_FALSE;
        }
    }
    pCtx->Rv9DecParam.Compress_en = pCtx->pstExtraData->s32Compress_en;
    
    /*
    pCtx->Rv9DecParam.Compress_en = pCtx->pstExtraData->s32Compress_en;
    pCtx->pRv9DecParam = &pCtx->Rv9DecParam;
    */
    return RV9_VFMW_TRUE;
}

SINT32 REAL9DEC_Decode_User(RV9_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    UINT32 i;
    SINT32 TotalSliceBits = 0;
    RV9_PictureHeader *pPictureHeader = NULL;
    RV9_SliceHeader   *pSliceHeader   = NULL;
    UINT32 Ratio0, Ratio1;
    SINT32 trb, trd;
    SINT32 HoldSliceNum;
    UINT32 fst_slc_grp;
    BS    *pBs  = NULL;
    IMAGE *pImg = NULL;
    FSP_LOGIC_FS_S  *pCur, *pBwd, *pFwd;
    RV9_DEC_PARAM_S *pRv9DecParam  = NULL;
    RV9_CODECINF    *pRv9CodecInfo = NULL;
    CB_PicHdrEnc_S  *pPicHdrEnc    = NULL;
    CB_SlcHdrEnc_S  *pSlcHdrEnc    = NULL;

    pRv9DecParam = &pCtx->Rv9DecParam;
    pRv9CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;
    pSliceHeader = &pCtx->CodecInfo.SliceHeader;

    pPictureHeader->Rv9ParsePicParam.pwidth_prev = pPictureHeader->Rv9ParsePicParam.pwidth;
    pPictureHeader->Rv9ParsePicParam.pheight_prev = pPictureHeader->Rv9ParsePicParam.pheight;
    pPictureHeader->Fid = RV9_FID_REALVIDEO30;
    pPictureHeader->m_uTRWrap = RV9_TR_WRAP_RV;

    if (NULL == pPacket)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet pointer!\n", pRv9CodecInfo->FrmCnt);
        return RV9_VFMW_FALSE;
    }

    memset( pRv9DecParam, 0, sizeof(RV9_DEC_PARAM_S) );

    //if start new pic, length1 should be reserved for VFMW searching and parsing
    pRv9CodecInfo->BsOffset = 0;
    pRv9CodecInfo->PacketTail = pPacket->StreamPack[0].LenInByte;

    //init pre parse pic header & slice header
    //for IsLastSeg always be 1 in SM_CopyRawToSeg, so we don't care StreamPack[1]
    pPicHdrEnc = (CB_PicHdrEnc_S *)pPacket->StreamPack[0].VirAddr;
    pRv9CodecInfo->BsOffset += sizeof(CB_PicHdrEnc_S);
    pSlcHdrEnc = (CB_SlcHdrEnc_S *)(pPacket->StreamPack[0].VirAddr + pRv9CodecInfo->BsOffset);
    pRv9CodecInfo->BsOffset += sizeof(CB_SlcHdrEnc_S)*pPicHdrEnc->TotalSliceNum;

    if (pRv9CodecInfo->BsOffset >= pRv9CodecInfo->PacketTail)
    {
        dprint(PRN_ERROR, "%s ERROR: BsOffset(%d) >= PacketTail(%d)\n", __func__, pRv9CodecInfo->BsOffset, pRv9CodecInfo->PacketTail);
        return RV9_VFMW_FALSE;
    }
    
    //adjust bs start address from updated offset
    pRv9CodecInfo->BsPhyAddr = pPacket->StreamPack[0].PhyAddr + pRv9CodecInfo->BsOffset;
    pRv9CodecInfo->BsVirAddr = pPacket->StreamPack[0].VirAddr + pRv9CodecInfo->BsOffset;
    pRv9CodecInfo->BsLength  = pPacket->StreamPack[0].LenInByte - pRv9CodecInfo->BsOffset;
    pRv9CodecInfo->IsLastSeg = pPacket->StreamPack[0].IsLastSeg;

    if (1 != pPacket->StreamPack[0].IsLastSeg)
    {
        pRv9CodecInfo->BsPhyAddr1 =  pPacket->StreamPack[1].PhyAddr;
        pRv9CodecInfo->BsVirAddr1 =  pPacket->StreamPack[1].VirAddr;
        pRv9CodecInfo->BsLength1 =  pPacket->StreamPack[1].LenInByte;
        pRv9CodecInfo->IsLastSeg1 = pPacket->StreamPack[1].IsLastSeg;
        if (1 != pPacket->StreamPack[1].IsLastSeg)
        {
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[0].StreamID);
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[1].StreamID);
            dprint(PRN_ERROR, "ERROR: 1 != pPacket->StreamPack[1].IsLastSeg\n");
            return RV9_VFMW_FALSE;
        }
    }
    else
    {
        pRv9CodecInfo->BsPhyAddr1 = 0;
        pRv9CodecInfo->BsVirAddr1 = 0;
        pRv9CodecInfo->BsLength1  = 0;
        pRv9CodecInfo->IsLastSeg1 = 0;
    }
    
    if ( (pRv9CodecInfo->BsLength < 9) || (pRv9CodecInfo->BsLength >= 3*1024*1024) )
    {
        dprint(PRN_ERROR, "pRv9CodecInfo->BsLength<%d> out of range\n", pRv9CodecInfo->BsLength);
        return RV9_VFMW_FALSE;
    }

    pRv9CodecInfo->TotalSliceNum = pPicHdrEnc->TotalSliceNum;
    if ( (pRv9CodecInfo->TotalSliceNum > 256) || (pRv9CodecInfo->TotalSliceNum < 1) )
    {
        dprint(PRN_ERROR, "ERROR: pRv9CodecInfo->TotalSliceNum out of range\n");
        return RV9_VFMW_FALSE;
    }

    pPictureHeader->PicCodType = pPicHdrEnc->PicCodType;
    pPictureHeader->pic_width_in_mb = (pPicHdrEnc->PicWidthInPixel+15)/16;
    pPictureHeader->pic_height_in_mb = (pPicHdrEnc->PicHeightInPixel+15)/16;
    pPictureHeader->pic_width_in_pixel= pPictureHeader->pic_width_in_mb*16;
    pPictureHeader->pic_height_in_pixel = pPictureHeader->pic_height_in_mb*16;
    pPictureHeader->Rounding = pPicHdrEnc->Rounding;
    pPictureHeader->stream_base_addr = pRv9CodecInfo->BsPhyAddr & 0xFFFFFFF0;
    pPictureHeader->total_mbs = pPictureHeader->pic_width_in_mb * pPictureHeader->pic_height_in_mb;

    //VHB 地址分配
     if ( RV9_VFMW_FALSE == pRv9CodecInfo->Imgbuf_allocated )
    {
        RV9_CLEARREFFLAG;
        RV9_CLEARREFNUM;
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));        
        if(RV9_VFMW_FALSE == Real9_ArrangeVHBMem(REAL9_MAXIMUM_IMAGE_NUM, pCtx, pPictureHeader))
        {
			dprint(PRN_ERROR, "ERROR: Real9_ArrangeVHBMem err\n"); 
			return RV9_VFMW_FALSE;
        }
    }

    //fixed 20130603
    pRv9CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;

    //获取帧存
    if ( RV9_VFMW_FALSE == Real9_GetImageBuffer(pCtx) )
    {
        dprint(PRN_FATAL, "Fatal Error: frm%d, get image buffer failed\n", pRv9CodecInfo->FrmCnt);
        return RV9_VFMW_FALSE;
    }

    /* PTS */
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pRv9CodecInfo->CurFsID);
    if (NULL != pImg)
    {
        pImg->PTS = pCtx->pstExtraData->pts;
        pImg->Usertag = pCtx->pstExtraData->Usertag;
        pImg->DispTime = pCtx->pstExtraData->DispTime;
        pImg->DispEnableFlag = pCtx->pstExtraData->DispEnableFlag;
        pImg->DispFrameDistance = pCtx->pstExtraData->DispFrameDistance;
        pImg->DistanceBeforeFirstFrame = pCtx->pstExtraData->DistanceBeforeFirstFrame;
        pImg->GopNum = pCtx->pstExtraData->GopNum;

        pCtx->pstExtraData->pts = (UINT64)(-1);    
	    dprint(PRN_PTS,"dec_pts: %lld Usertag = %lld\n",pImg->PTS,pImg->Usertag);
    }
    else
    {
        FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
        dprint(PRN_ERROR, "ERROR: FSP_GetFsImagePtr err\n"); 
        return RV9_VFMW_FALSE;
    }

    /* 参考维护 */
    if (RV9_TRUEBPIC != pPictureHeader->PicCodType)
    {
        if ( (RV9_INTERPIC == pPictureHeader->PicCodType) && (pRv9CodecInfo->RefNum < 1) )
        {
            dprint(PRN_ERROR, "ERROR: PicCodType = RV9_INTERPIC, but RefNum %d < 1\n", pRv9CodecInfo->RefNum); 
            return RV9_VFMW_FALSE;
        }
        pRv9CodecInfo->RefNum = pRv9CodecInfo->RefNum>0 ? 2 : 1;
        if (pRv9CodecInfo->FwdFsID != pRv9CodecInfo->BwdFsID)
        {
            //这样释放的才是有效参考图
            dprint(PRN_REF, "---------- unref %d\n", pRv9CodecInfo->FwdFsID);
            FSP_SetRef(pCtx->ChanID, pRv9CodecInfo->FwdFsID, 0);
        }
        pRv9CodecInfo->FwdFsID = pRv9CodecInfo->BwdFsID;
        pRv9CodecInfo->BwdFsID = pRv9CodecInfo->CurFsID;
        FSP_SetRef(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);

        FSP_RemovePmv(pCtx->ChanID, pRv9CodecInfo->FwdFsID);
        dprint(PRN_REF, "++++++++++ ref %d\n", pRv9CodecInfo->CurFsID);
    }
    else
    {
        if (pRv9CodecInfo->RefNum < 2)
        {
            FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
            dprint(PRN_ERROR, "ERROR: pRv9CodecInfo->RefNum < 2\n"); 
            return RV9_VFMW_FALSE;
        }
    }

    pCur = FSP_GetLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID);
    pFwd = FSP_GetLogicFs(pCtx->ChanID, pRv9CodecInfo->FwdFsID);
    pBwd = FSP_GetLogicFs(pCtx->ChanID, pRv9CodecInfo->BwdFsID);

    if ((NULL == pCur) || (NULL == pFwd) || (NULL == pBwd))
    {
		dprint(PRN_FATAL, "CurFsID abnormal!,%s %d (NULL == pCur) || (NULL == pFwd) || (NULL == pBwd)!!\n",__FUNCTION__,__LINE__);
        return RV9_VFMW_FALSE;
    }

    if ((NULL == pCur->pstDecodeFs) || (NULL == pCur->pstTfOutFs) || (NULL == pCur->pstDispOutFs))
    {
        FSP_ClearLogicFs(pCtx->ChanID, pRv9CodecInfo->CurFsID, 1);
        dprint(PRN_FATAL, "ERROR: CurFsID abnormal!\n");
        return RV9_VFMW_FALSE;
    }
    else
    {
        pRv9DecParam->BwdRefPhyAddr   = (NULL != pBwd->pstDecodeFs)? pBwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pRv9DecParam->FwdRefPhyAddr   = (NULL != pFwd->pstDecodeFs)? pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pRv9DecParam->CurPicPhyAddr   = pCur->pstDecodeFs->PhyAddr;
        pRv9DecParam->CurrPmvPhyAddr = pCur->PmvAddr;

        pRv9DecParam->ColPmvPhyAddr = pBwd->PmvAddr;
        pRv9DecParam->DispFramePhyAddr = pCur->pstDispOutFs->PhyAddr;
    }

    pRv9DecParam->DDRStride = pCur->pstDispOutFs->Stride;
    pRv9CodecInfo->ddr_stride = pCur->pstDispOutFs->Stride;
    pRv9DecParam->StreamBaseAddr = pPictureHeader->stream_base_addr;

    //计算TRB, TRD
    if (RV9_TRUEBPIC == pPictureHeader->PicCodType)
    {
        pRv9CodecInfo->trb = pPicHdrEnc->Trb;
        pRv9CodecInfo->trd = pPicHdrEnc->Trd;

        trb = pRv9CodecInfo->trb;
        trd = pRv9CodecInfo->trd;
  
        if (trb > trd)      /* just in case TR's are incorrect */
        {
            trb = 0;
        }
        if (trd > 0)
        {
            Ratio0 = (trb << RV9_TR_SHIFT) / trd;
            Ratio1 = ((trd-trb) << RV9_TR_SHIFT) / trd;
        }
        else
        {
            Ratio0 = Ratio1 = 0;
        }

        pRv9CodecInfo->Ratio0 = Ratio0;
        pRv9CodecInfo->Ratio1 = Ratio1;
    }

    pPictureHeader->PQUANT = pSlcHdrEnc[0].SliceQP;
    
    Real9_WritePicMsg(pCtx);

    HoldSliceNum = 0;
    
    for(i=0; i<pPicHdrEnc->TotalSliceNum; i++)
    {
        pSliceHeader->bit_offset_0 = (TotalSliceBits + pSlcHdrEnc[i].BitOffset) % 128;
        pSliceHeader->bit_len_0 = pSlcHdrEnc[i].BitLen - pSlcHdrEnc[i].BitOffset;
        pSliceHeader->bit_stream_addr_0 = (TotalSliceBits/8) & 0xFFFFFFF0;
        pSliceHeader->bit_offset_1 = 0;
        pSliceHeader->bit_len_1 = 0;
        pSliceHeader->bit_stream_addr_1 = 0;
        TotalSliceBits += pSlcHdrEnc[i].BitLen;;
        
        pSliceHeader->SliceQP = pSlcHdrEnc[i].SliceQP;
        pSliceHeader->osvquant = pSlcHdrEnc[i].Osvquant;
        pSliceHeader->dblk_filter_passthrough = pSlcHdrEnc[i].DblkFilterPassThrough;
        pSliceHeader->first_mb_in_slice = pSlcHdrEnc[i].FirstMbInSlice;

        if(i < pPicHdrEnc->TotalSliceNum-1)
        {
            pSliceHeader->last_mb_in_slice = pSlcHdrEnc[i+1].FirstMbInSlice - 1;
        }
        else
        {
            pSliceHeader->last_mb_in_slice = pPictureHeader->pic_width_in_mb*pPictureHeader->pic_height_in_mb - 1;
        }

        Real9_WriteSliceMsg(pCtx, HoldSliceNum);
        HoldSliceNum++;
    }
    
    fst_slc_grp = 1;
    Real9_WriteReg(pCtx, fst_slc_grp);

    pCtx->pRv9DecParam = &pCtx->Rv9DecParam;
    pCtx->Rv9DecParam.Compress_en = pCtx->pstExtraData->s32Compress_en;
    
    return RV9_VFMW_TRUE;
}

SINT32 REAL9DEC_RecycleImage(RV9_CTX_S *pCtx, UINT32 ImgID)
{
    RV9_CODECINF *pRv9CodecInfo;
    IMAGE *pImg;

    pRv9CodecInfo = &pCtx->CodecInfo;

    FSP_SetDisplay(pCtx->ChanID, ImgID, 0);
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, ImgID);
    if (NULL != pImg)
    {
        //FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        //pImg->p_usrdat[0] = NULL;
        //FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        //pImg->p_usrdat[1] = NULL;
    }

    return RV9_VFMW_TRUE;
}


SINT32 REAL9DEC_GetRemainImg(RV9_CTX_S *pCtx)
{
    RV9_CODECINF *pRv9CodecInfo;
    IMAGE *pImg = NULL;
    SINT32 display_flag;
    SINT32 ret = LAST_OUTPUT_FAIL;

    pRv9CodecInfo = &pCtx->CodecInfo;

    if (OUTPUT_IN_DEC == pCtx->pstExtraData->s32DecOrderOutput)
    {
        ret = LAST_ALREADY_OUT;
    }
    else
    {
        pImg = FSP_GetFsImagePtr(pCtx->ChanID, pRv9CodecInfo->BwdFsID);
        if (NULL != pImg)
        {
    	   display_flag = FSP_GetDisplay(pCtx->ChanID, pRv9CodecInfo->BwdFsID);
	   if (FS_DISP_STATE_DEC_COMPLETE == display_flag)
	   {
              Real9_SetImgFormat(pCtx);
	       pImg->last_frame = 1;
            pImg->last_frame = 1;

              FSP_SetDisplay(pCtx->ChanID, pRv9CodecInfo->BwdFsID, 1);
              if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_REAL9, pCtx, &pCtx->ImageQue, pImg) )
              {
                  FSP_SetDisplay(pCtx->ChanID, pRv9CodecInfo->BwdFsID, 0);
                  //FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
                  //pImg->p_usrdat[0] = NULL;
                  //FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
                  //pImg->p_usrdat[1] = NULL;
                  ret = LAST_OUTPUT_FAIL;
              }
	       else if ( pImg->error_level > 100 || pImg->image_width < 32 || pImg->image_height < 32 )        // 特殊情况下返回的VF_OK，并没实际插到队列中
              {
                  ret = LAST_OUTPUT_FAIL;
	       }
	       else   // 成功插入队列中
	       {
                  ret = LAST_OUTPUT_OK;
	       }
          }// 之前已经插到队列中
	   else
	   {
              ret = LAST_ALREADY_OUT;
	   }
       }
    }

    if (LAST_OUTPUT_OK != ret)
    {
        ret = GetVoLastImageID(&pCtx->ImageQue);
    }
	
    return ret;
}


UINT32 REAL9DEC_VDMPostProc(RV9_CTX_S *pCtx, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic)
{
    RV9_CODECINF *pRv9CodecInfo;
    IMAGE *pCurImg, *pToQueImg;

    pRv9CodecInfo = &pCtx->CodecInfo;

    dprint(PRN_DBG, "ErrRatio = %d\n", ErrRatio);

    RV9_RecordVFMWState(pCtx);  
    ReleasePacket(VFMW_REAL9, pCtx);

    pCurImg = FSP_GetFsImagePtr(pCtx->ChanID, pRv9CodecInfo->CurFsID);

    if (NULL == pCurImg)
    {
         return RV9_VFMW_FALSE;
    }

    pRv9CodecInfo->LastDecPicCodingType = pRv9CodecInfo->PictureHeader.PicCodType;
    if (RV9_TRUEBPIC != pRv9CodecInfo->PictureHeader.PicCodType)
    {
        pRv9CodecInfo->PrevPicMb0QP = Mb0QpInCurrPic & 0x1F;
    }

    /* 处理err_level */
    pCurImg->error_level = ErrRatio;
    pCurImg->error_level = CLIP1(100, (SINT32)(pCurImg->error_level));

    /* 将图像输出到VO队列 */
    dprint(PRN_DBG, "DEBUG: DEC over\n");

    Real9_SetImgFormat(pCtx);

    if ( I_MODE == pRv9CodecInfo->UsedDecMode )
    {
        pRv9CodecInfo->ToQueFsID = pRv9CodecInfo->CurFsID;
    }
    else
    {
        if (OUTPUT_IN_DEC != pCtx->pstExtraData->s32DecOrderOutput) /* if(显示序输出) */
        {
            if (RV9_TRUEBPIC != pRv9CodecInfo->PictureHeader.PicCodType)
            {
                pRv9CodecInfo->ToQueFsID = (pRv9CodecInfo->RefNum > 1)? pRv9CodecInfo->FwdFsID: -1;
            }
            else
            {
                pRv9CodecInfo->ToQueFsID = pRv9CodecInfo->CurFsID;
            }
        }
        else
        {
            pRv9CodecInfo->ToQueFsID = pRv9CodecInfo->CurFsID;
        }
    }

    if ( -1 != pRv9CodecInfo->ToQueFsID )
    {
        pToQueImg = FSP_GetFsImagePtr(pCtx->ChanID, pRv9CodecInfo->ToQueFsID);
        dprint(PRN_QUEUE, "insert buf %d ref %d\n", pRv9CodecInfo->ToQueFsID, FSP_GetRef(pCtx->ChanID, pRv9CodecInfo->ToQueFsID));

        FSP_SetDisplay(pCtx->ChanID, pRv9CodecInfo->ToQueFsID, 1);
        if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_REAL9, pCtx, &pCtx->ImageQue, pToQueImg))
        {
            FSP_SetDisplay(pCtx->ChanID, pRv9CodecInfo->ToQueFsID, 0);
            return RV9_VFMW_FALSE;
        }
    }

    pRv9CodecInfo->FrmCnt++;

    return RV9_VFMW_TRUE;
}


SINT32 REAL9DEC_GetImageBuffer( RV9_CTX_S *pCtx )
{
    RV9_CODECINF *pRv9CodecInfo;
    RV9_VOBUFINF *pVOBufInf;

    pRv9CodecInfo = &pCtx->CodecInfo;
    pVOBufInf = pCtx->CodecInfo.VOBufInf;

        /* 如果FSP中有新的帧存可以获取，返回TRUE */
    if (FSP_IsNewFsAvalible(pCtx->ChanID) == 1)
    {
        return 1;
    }
    else if (FSP_IsNewFsAvalible(pCtx->ChanID) == -1)
    {
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
    }

    return 0;
}

VOID REAL9DEC_Support(SINT32 *flag)
{
    *flag = 1;
    return;
}

#endif //REAL9_VFMW_ENABLE
