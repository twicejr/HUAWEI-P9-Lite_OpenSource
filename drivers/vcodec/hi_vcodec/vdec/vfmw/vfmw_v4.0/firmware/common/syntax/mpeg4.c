/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r3zgf1+WEFfjGanItDorz8ydwpTT9vmJ9o+SYFiXTdvhqwORIxdb2bUzVNCrFBw2f8QYs
1+0X4ONhnbUlw4f+FRWBHlSYphUPzBG3Mantzvxvg08vDpxGF+vso7p/0QDsxA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************
*
* Copyright (c) 2007 HUAWEI - All Rights Reserved
*
* File: $mpeg4.c$
* Date: $2007/03/1$
* Revision: $v1.0$
* Purpose: MPEG4 standard vfmw interface.
*
* Change History:
*
* Date                       Author                          Change
* ====                       ======                          ====== 
* 2007/03/08                 l42896 & l48485
*
*
* Dependencies:
* Linux OS
*
************************************************************************/

#ifndef __MPEG4_C__
#define __MPEG4_C__


#include    "public.h"
#include    "basedef.h"
#include    "bitstream.h"
#include    "vfmw.h"
#include    "syntax.h"
#include    "mpeg4.h"
#include	"vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"
#include    "vdm_hal.h"


extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];

#define SEARCH_IVOP
#define NVOP_VDM_PRO

#define MP4_CLEARREFFLAG do{\
     IMAGE *pImg;\
     pImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->BwdFsID);\
     if (NULL != pImg)\
     {\
         FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);\
         FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);\
         FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[2]);\
         FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[3]);\
         pImg->p_usrdat[0] = NULL;\
         pImg->p_usrdat[1] = NULL;\
         pImg->p_usrdat[2] = NULL;\
         pImg->p_usrdat[3] = NULL;\
         FSP_ClearLogicFs(pCtx->ChanID, pCtx->BwdFsID, 1);\
         FSP_ClearLogicFs(pCtx->ChanID, pCtx->FwdFsID, 1);\
         pCtx->FwdFsID = 0; \
         pCtx->BwdFsID = 0; \
         pCtx->FwdFsID=pCtx->BwdFsID=FSP_GetNullLogicFs(pCtx->ChanID);\
     }\
}while(0)

#define MP4_CLEARREFNUM do{pCtx->RefNum=0;}while(0)

SINT32 const scan_tables[3][64] = 
{
	/* zig_zag_scan */
	{
		0,  1,  8, 16,  9,  2,  3, 10,
		17, 24, 32, 25, 18, 11,  4,  5,
		12, 19, 26, 33, 40, 48, 41, 34,
		27, 20, 13,  6,  7, 14, 21, 28,
		35, 42, 49, 56, 57, 50, 43, 36,
		29, 22, 15, 23, 30, 37, 44, 51,
		58, 59, 52, 45, 38, 31, 39, 46,
		53, 60, 61, 54, 47, 55, 62, 63
	},

	/* horizontal_scan */
	{
		0,  1,  2,  3,  8,  9, 16, 17,
		10, 11,  4,  5,  6,  7, 15, 14,
		13, 12, 19, 18, 24, 25, 32, 33,
		26, 27, 20, 21, 22, 23, 28, 29,
		30, 31, 34, 35, 40, 41, 48, 49,
		42, 43, 36, 37, 38, 39, 44, 45,
		46, 47, 50, 51, 56, 57, 58, 59,
		52, 53, 54, 55, 60, 61, 62, 63
	},

	/* vertical_scan */
	{
		0,  8, 16, 24,  1,  9,  2, 10,
		17, 25, 32, 40, 48, 56, 57, 49,
		41, 33, 26, 18,  3, 11,  4, 12,
		19, 27, 34, 42, 50, 58, 35, 43,
		51, 59, 20, 28,  5, 13,  6, 14,
		21, 29, 36, 44, 52, 60, 37, 45,
		53, 61, 22, 30,  7, 15, 23, 31,
		38, 46, 54, 62, 39, 47, 55, 63
	}
};

SINT32 const default_intra_matrix[64] = 
{ 
    8, 17, 18, 19, 21, 23, 25, 27,
    17, 18, 19, 21, 23, 25, 27, 28,
    20, 21, 22, 23, 24, 26, 28, 30,
    21, 22, 23, 24, 26, 28, 30, 32,
    22, 23, 24, 26, 28, 30, 32, 35,
    23, 24, 26, 28, 30, 32, 35, 38,
    25, 26, 28, 30, 32, 35, 38, 41,
    27, 28, 30, 32, 35, 38, 41, 45
};

SINT32 const default_inter_matrix[64] = 
{  
    16, 17, 18, 19, 20, 21, 22, 23,
    17, 18, 19, 20, 21, 22, 23, 24,
    18, 19, 20, 21, 22, 23, 24, 25,
    19, 20, 21, 22, 23, 24, 26, 27,
    20, 21, 22, 23, 25, 26, 27, 28,
    21, 22, 23, 24, 26, 27, 28, 30,
    22, 23, 24, 26, 27, 28, 30, 31,
    23, 24, 25, 27, 28, 30, 31, 33
};

typedef struct
{
	UINT32 code;
	UINT8  len;
} VLC;

VLC sprite_trajectory_len[15] =
{
	{ 0x00 , 2},
	{ 0x02 , 3}, { 0x03, 3}, { 0x04, 3}, { 0x05, 3}, { 0x06, 3},
	{ 0x0E , 4}, { 0x1E, 5}, { 0x3E, 6}, { 0x7E, 7}, { 0xFE, 8},
    { 0x1FE, 9}, {0x3FE, 10}, {0x7FE, 11}, {0xFFE, 12}
};

#define MARKER_VOL( local_bs )    \
do{                               \
    if ( !BsGet( &local_bs, 1 ) )     \
    {                                 \
        dprint(PRN_ERROR, "fatal stream error --- VOP marker_bit = 0\n" );    \
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOPERR;    \
        BitUsed = BsPos(&local_bs);                          \
        REPORT_SE_ERR(pCtx->ChanID);                        \
        return BitUsed;                                      \
    }    \
} while(0)
    

#define MARKER_VOP( local_bs )    \
do{    \
    if ( !BsGet( &local_bs, 1 ) )     \
    {                                 \
        dprint(PRN_ERROR, "fatal stream error --- VOP marker_bit = 0\n" );    \
        pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;    \
        BitUsed = BsPos(&local_bs);                          \
        REPORT_SE_ERR(pCtx->ChanID);                         \
        return BitUsed;                                      \
    }    \
} while(0)

#define MARKER_GOP( local_bs )    \
do{    \
    if ( !BsGet( &local_bs, 1 ) )     \
    {                                 \
        dprint(PRN_ERROR, "fatal stream error --- GOP marker_bit = 0\n" );    \
        pCtx->MP4SyntaxState.gop_decode_right = SYN_GOPERR;    \
        BitUsed = BsPos(&local_bs);                          \
        REPORT_SE_ERR(pCtx->ChanID);                         \
        return BitUsed;                                      \
    }    \
} while(0)


/****************************************************************************/
/*                           自用函数声明                                   */
/****************************************************************************/
UINT32 GetTrailingOneLen(UINT8* pCode, SINT32 CodeLen);
SINT32 Frame_Init(MP4_CTX_S *pCtx, UINT32 PicWidth, UINT32 PicHeight);
SINT32 MP4_GetPacketState(MP4_CTX_S *pCtx);
SINT32 Mp4_Check_Slice_NotSH(MP4_CTX_S *pCtx);
SINT32 Mp4_Combine_SliceData(MP4_CTX_S *pCtx, SINT32 CodeLen);
SINT32 Mp4_Syntax_Slice_NotSH(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len);
SINT32 Mp4_Syntax_Slice_SH(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len);
SINT32 MP4_Check_StreamType(MP4_CTX_S *pCtx, UINT32 *StartCode);
SINT32 MP4_Dec_Slice(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len);
VOID MP4_Record_SlcSegID(MP4_CTX_S *pCtx);
VOID MP4_ClearCurPacket(SINT32 ChanID, DEC_STREAM_PACKET_S *pMp4Packet);
VOID MP4_ClearCurPic(MP4_CTX_S *pCtx);
VOID MP4_GetScdUpMsg(MP4_CTX_S *pCtx, DEC_STREAM_PACKET_S *pMp4Packet);
VOID   MP4_Record_HeadPacketInfo(MP4_CTX_S *pCtx, UINT32 StartCode);
VOID   MP4_Clean_HeadPacket(MP4_CTX_S *pCtx);
SINT32 MP4_Check_CurPacket(MP4_CTX_S *pCtx);
VOID  MP4_Record_PacketID(MP4_CTX_S *pCtx);
SINT32 MP4_Combine_HdPacket(MP4_CTX_S *pCtx);
SINT32  MP4_Renew_CurPacket(MP4_CTX_S *pCtx);


/****************************************************************************/
/*                             函数实现                                     */
/****************************************************************************/
SINT32 log2bin(UINT32 value)
{
    SINT16 n = 0;

    while (value!=0) 
    {
        value >>= 1;
        n++;
    }

    return n;
}

UINT32 bs_get_spritetrajectory(BS * pBs)
{
	UINT32 i;
	for (i = 0; i < 12; i++)
	{
		if (BsShow(pBs, sprite_trajectory_len[i].len) == (SINT32)(sprite_trajectory_len[i].code))
		{
			BsSkip(pBs, sprite_trajectory_len[i].len);
			return i;
		}
	}
	return -1;
}



VOID MP4_GetGMCparam( MP4_SYNTAX  *p_syntax_des, MP4_GMC_DATA *p_gmc)
{
    UINT64 nb_pts;
	MPEG4_WARPPOINTS *p_gmcwarp = &(p_syntax_des->syn_vop.gmc_warp);
//	static SINT32 cnt = 0;
	SINT32 shift[2] = {0, 0};
	
    SINT32 a= 2<<p_syntax_des->syn_vol.sprite_warping_accuracy;
    SINT32 rho= 3-p_syntax_des->syn_vol.sprite_warping_accuracy;
    SINT32 r=16/a;
    const SINT32 vop_ref[4][2]= {{0,0}, {p_syntax_des->image_width,0}, {0, p_syntax_des->image_height}, {p_syntax_des->image_width, p_syntax_des->image_height}}; // only true for rectangle shapes
    SINT32 d[4][2]={{0,0}, {0,0}, {0,0}, {0,0}};
    SINT32 sprite_ref[4][2];
    SINT32 virtual_ref[2][2];
    SINT32 w2, h2, w3, h3;
    SINT32 alpha=0, beta=0;
    SINT32 w= p_syntax_des->image_width;
    SINT32 h= p_syntax_des->image_height;
    SINT32 min_ab;
    SINT32 shift_y;//= 16 - s->sprite_shift[0];
    SINT32 shift_c;//= 16 - s->sprite_shift[1];
    //SINT32 i;


	p_gmc->sW = p_syntax_des->image_width<< 4;
	p_gmc->sH = p_syntax_des->image_height<< 4;
	p_gmc->accuracy = p_syntax_des->syn_vol.sprite_warping_accuracy;
	p_gmc->num_wp = p_syntax_des->syn_vol.sprite_warping_points;


	d[0][0] = p_gmcwarp->duv[0].x;
	d[0][1] = p_gmcwarp->duv[0].y;	
	d[1][0] = p_gmcwarp->duv[1].x;
	d[1][1] = p_gmcwarp->duv[1].y;	
	d[2][0] = p_gmcwarp->duv[2].x;
	d[2][1] = p_gmcwarp->duv[2].y;		

    while ((1 << alpha) < w) { alpha++; }
    while ((1 << beta ) < h) { beta++; } // there seems to be a typo in the mpeg4 std for the definition of w' and h'
    w2= 1<<alpha;
    h2= 1<<beta;
	
    nb_pts = p_gmc->num_wp;
	#if 0
	/* reduce the number of points, if possible */
	if ((nb_pts<2) || (p_gmcwarp->duv[2].x==0 && p_gmcwarp->duv[2].y==0 && p_gmcwarp->duv[1].x==0 && p_gmcwarp->duv[1].y==0 )) 
    {
      	if ((nb_pts<2) || (p_gmcwarp->duv[1].x==0 && p_gmcwarp->duv[1].y==0)) 
        {
    	  	if ((nb_pts<1) || (p_gmcwarp->duv[0].x==0 && p_gmcwarp->duv[0].y==0)) 
            {
    		    nb_pts = 0;
      		}
    	  	else 
            {
                nb_pts = 1;
            }
      	}
        else
        {
            nb_pts = 2;
        }
    }
    p_gmc->num_wp = nb_pts;
	/* now, nb_pts stores the actual number of points required for interpolation */
    #endif
	#if 1
    if (p_syntax_des->FF_BUG_DIVX500B413 == 1)
	{
        sprite_ref[0][0]= a*vop_ref[0][0] + d[0][0];
        sprite_ref[0][1]= a*vop_ref[0][1] + d[0][1];
        sprite_ref[1][0]= a*vop_ref[1][0] + d[0][0] + d[1][0];
        sprite_ref[1][1]= a*vop_ref[1][1] + d[0][1] + d[1][1];
        sprite_ref[2][0]= a*vop_ref[2][0] + d[0][0] + d[2][0];
        sprite_ref[2][1]= a*vop_ref[2][1] + d[0][1] + d[2][1];
    } 
	else 
	{
        sprite_ref[0][0]= (a>>1)*(2*vop_ref[0][0] + d[0][0]);
        sprite_ref[0][1]= (a>>1)*(2*vop_ref[0][1] + d[0][1]);
        sprite_ref[1][0]= (a>>1)*(2*vop_ref[1][0] + d[0][0] + d[1][0]);
        sprite_ref[1][1]= (a>>1)*(2*vop_ref[1][1] + d[0][1] + d[1][1]);
        sprite_ref[2][0]= (a>>1)*(2*vop_ref[2][0] + d[0][0] + d[2][0]);
        sprite_ref[2][1]= (a>>1)*(2*vop_ref[2][1] + d[0][1] + d[2][1]);
    }
/*    sprite_ref[3][0]= (a>>1)*(2*vop_ref[3][0] + d[0][0] + d[1][0] + d[2][0] + d[3][0]);
    sprite_ref[3][1]= (a>>1)*(2*vop_ref[3][1] + d[0][1] + d[1][1] + d[2][1] + d[3][1]); */

// this is mostly identical to the mpeg4 std (and is totally unreadable because of that ...)
// perhaps it should be reordered to be more readable ...
// the idea behind this virtual_ref mess is to be able to use shifts later per pixel instead of divides
// so the distance between points is converted from w&h based to w2&h2 based which are of the 2^x form
    virtual_ref[0][0]= 16*(vop_ref[0][0] + w2)
        + RDIV(((w - w2)*(r*sprite_ref[0][0] - 16*vop_ref[0][0]) + w2*(r*sprite_ref[1][0] - 16*vop_ref[1][0])),w);
    virtual_ref[0][1]= 16*vop_ref[0][1]
        + RDIV(((w - w2)*(r*sprite_ref[0][1] - 16*vop_ref[0][1]) + w2*(r*sprite_ref[1][1] - 16*vop_ref[1][1])),w);
    virtual_ref[1][0]= 16*vop_ref[0][0]
        + RDIV(((h - h2)*(r*sprite_ref[0][0] - 16*vop_ref[0][0]) + h2*(r*sprite_ref[2][0] - 16*vop_ref[2][0])),h);
    virtual_ref[1][1]= 16*(vop_ref[0][1] + h2)
        + RDIV(((h - h2)*(r*sprite_ref[0][1] - 16*vop_ref[0][1]) + h2*(r*sprite_ref[2][1] - 16*vop_ref[2][1])),h);

    switch(nb_pts)
    {
        case 0:
            p_gmc->Uo = 0;
            p_gmc->Vo = 0;
            p_gmc->Uco= 0;
            p_gmc->Vco= 0;
            p_gmc->dU[0]= a;
            p_gmc->dU[1]= 0;
            p_gmc->dV[0]= 0;
            p_gmc->dV[1]= a;
            shift[0]= 0;
            shift[1]= 0;
            break;
        case 1: //GMC only
            p_gmc->Uo = sprite_ref[0][0] - a*vop_ref[0][0];
            p_gmc->Vo = sprite_ref[0][1] - a*vop_ref[0][1];
            p_gmc->Uco= ((sprite_ref[0][0]>>1)|(sprite_ref[0][0]&1)) - a*(vop_ref[0][0]/2);
            p_gmc->Vco= ((sprite_ref[0][1]>>1)|(sprite_ref[0][1]&1)) - a*(vop_ref[0][1]/2);
            p_gmc->dU[0]= a;
            p_gmc->dU[1]= 0;
            p_gmc->dV[0]= 0;
            p_gmc->dV[1]= a;
            shift[0]= 0;
            shift[1]= 0;
            break;
        case 2:
            p_gmc->Uo= (sprite_ref[0][0]<<(alpha+rho))
                                                  + (-r*sprite_ref[0][0] + virtual_ref[0][0])*(-vop_ref[0][0])
                                                  + ( r*sprite_ref[0][1] - virtual_ref[0][1])*(-vop_ref[0][1])
                                                  + (1<<(alpha+rho-1));
            p_gmc->Vo= (sprite_ref[0][1]<<(alpha+rho))
                                                  + (-r*sprite_ref[0][1] + virtual_ref[0][1])*(-vop_ref[0][0])
                                                  + (-r*sprite_ref[0][0] + virtual_ref[0][0])*(-vop_ref[0][1])
                                                  + (1<<(alpha+rho-1));
            p_gmc->Uco= ( (-r*sprite_ref[0][0] + virtual_ref[0][0])*(-2*vop_ref[0][0] + 1)
                                     +( r*sprite_ref[0][1] - virtual_ref[0][1])*(-2*vop_ref[0][1] + 1)
                                     +2*w2*r*sprite_ref[0][0]
                                     - 16*w2
                                     + (1<<(alpha+rho+1)));
            p_gmc->Vco= ( (-r*sprite_ref[0][1] + virtual_ref[0][1])*(-2*vop_ref[0][0] + 1)
                                     +(-r*sprite_ref[0][0] + virtual_ref[0][0])*(-2*vop_ref[0][1] + 1)
                                     +2*w2*r*sprite_ref[0][1]
                                     - 16*w2
                                     + (1<<(alpha+rho+1)));
            p_gmc->dU[0]=   (-r*sprite_ref[0][0] + virtual_ref[0][0]);
            p_gmc->dU[1]=   (+r*sprite_ref[0][1] - virtual_ref[0][1]);
            p_gmc->dV[0]=   (-r*sprite_ref[0][1] + virtual_ref[0][1]);
            p_gmc->dV[1]=   (-r*sprite_ref[0][0] + virtual_ref[0][0]);

            shift[0]= alpha+rho;
            shift[1]= alpha+rho+2;
            break;
        case 3:
            min_ab= FFMIN(alpha, beta);
            w3= w2>>min_ab;
            h3= h2>>min_ab;
            p_gmc->Uo=  (sprite_ref[0][0]<<(alpha+beta+rho-min_ab))
                                   + (-r*sprite_ref[0][0] + virtual_ref[0][0])*h3*(-vop_ref[0][0])
                                   + (-r*sprite_ref[0][0] + virtual_ref[1][0])*w3*(-vop_ref[0][1])
                                   + (1<<(alpha+beta+rho-min_ab-1));
            p_gmc->Vo=  (sprite_ref[0][1]<<(alpha+beta+rho-min_ab))
                                   + (-r*sprite_ref[0][1] + virtual_ref[0][1])*h3*(-vop_ref[0][0])
                                   + (-r*sprite_ref[0][1] + virtual_ref[1][1])*w3*(-vop_ref[0][1])
                                   + (1<<(alpha+beta+rho-min_ab-1));
            p_gmc->Uco=  (-r*sprite_ref[0][0] + virtual_ref[0][0])*h3*(-2*vop_ref[0][0] + 1)
                                   + (-r*sprite_ref[0][0] + virtual_ref[1][0])*w3*(-2*vop_ref[0][1] + 1)
                                   + 2*w2*h3*r*sprite_ref[0][0]
                                   - 16*w2*h3
                                   + (1<<(alpha+beta+rho-min_ab+1));
            p_gmc->Vco=  (-r*sprite_ref[0][1] + virtual_ref[0][1])*h3*(-2*vop_ref[0][0] + 1)
                                   + (-r*sprite_ref[0][1] + virtual_ref[1][1])*w3*(-2*vop_ref[0][1] + 1)
                                   + 2*w2*h3*r*sprite_ref[0][1]
                                   - 16*w2*h3
                                   + (1<<(alpha+beta+rho-min_ab+1));
            p_gmc->dU[0]=   (-r*sprite_ref[0][0] + virtual_ref[0][0])*h3;
            p_gmc->dU[1]=   (-r*sprite_ref[0][0] + virtual_ref[1][0])*w3;
            p_gmc->dV[0]=   (-r*sprite_ref[0][1] + virtual_ref[0][1])*h3;
            p_gmc->dV[1]=   (-r*sprite_ref[0][1] + virtual_ref[1][1])*w3;

            shift[0]= alpha + beta + rho - min_ab;
            shift[1]= alpha + beta + rho - min_ab + 2;
            break;
    }
	#if 1
    /* try to simplify the situation */
    if(   p_gmc->dU[0] == a<<shift[0]
       && p_gmc->dU[1] == 0
       && p_gmc->dV[0] == 0
       && p_gmc->dV[1] == a<<shift[0])
    {
        p_gmc->Uo >>=shift[0];
        p_gmc->Vo >>=shift[0];
        p_gmc->Uco>>=shift[1];
        p_gmc->Vco>>=shift[1];
        p_gmc->dU[0]= a;
        p_gmc->dU[1]= 0;
        p_gmc->dV[0]= 0;
        p_gmc->dV[1]= a;
        shift[0]= 0;
        shift[1]= 0;
        p_gmc->num_wp=1;
    }
    else
    {
	#else
	if(p_gmc->num_wp>1)
	{
	#endif
        shift_y= 16 - shift[0];
        shift_c= 16 - shift[1];
        p_gmc->Uo<<= shift_y;
        p_gmc->Vo<<= shift_y;
        p_gmc->Uco<<= shift_c;
        p_gmc->Vco<<= shift_c;	
        p_gmc->dU[0]<<= shift_y;
        p_gmc->dU[1]<<= shift_y;
        p_gmc->dV[0]<<= shift_y;
        p_gmc->dV[1]<<= shift_y;			
    }

	#else
	if (nb_pts<=1)
	{
    	if (nb_pts==1) 
        {
    	    if(g_mp4_syntax.divx_version==500 && g_mp4_syntax.divx_build==413)
    	    {        
    	    SINT32 Alpha1 = log2bin(p_syntax_des->image_width - 1);
			SINT32 rho1	 = 3 - p_gmc->accuracy;
			 
        		/* store as 4b fixed point */
        		p_gmc->Uo = p_gmcwarp->duv[0].x ;//<< p_gmc->accuracy; //sprite_ref i0'
        		p_gmc->Vo = p_gmcwarp->duv[0].y ;//<< p_gmc->accuracy;//sprite_ref j0'
        		p_gmc->Uco = ((p_gmcwarp->duv[0].x>>1) | (p_gmcwarp->duv[0].x&1));//<< p_gmc->accuracy;	 /* DIV2RND() */
        		p_gmc->Vco = ((p_gmcwarp->duv[0].y>>1) | (p_gmcwarp->duv[0].y&1)) ;//<< p_gmc->accuracy;	 /* DIV2RND() */
    	    }
    		else
    		{
        		/* store as 4b fixed point */
        		p_gmc->Uo = p_gmcwarp->duv[0].x << p_gmc->accuracy; //sprite_ref i0'
        		p_gmc->Vo = p_gmcwarp->duv[0].y << p_gmc->accuracy;//sprite_ref j0'
        		p_gmc->Uco = ((p_gmcwarp->duv[0].x>>1) | (p_gmcwarp->duv[0].x&1)) << p_gmc->accuracy;	 /* DIV2RND() */
        		p_gmc->Vco = ((p_gmcwarp->duv[0].y>>1) | (p_gmcwarp->duv[0].y&1)) << p_gmc->accuracy;	 /* DIV2RND() */
    		}
    	}
    	else 
        {	/* zero points?! */
    		p_gmc->Uo	= p_gmc->Vo	= 0;
    		p_gmc->Uco = p_gmc->Vco = 0;
    	}
	}
	else 
    {		/* 2 or 3 points */
    	const SINT32 rho	 = 3 - p_gmc->accuracy;	/* = {3,2,1,0} for Acc={0,1,2,3} */
    	SINT32 Alpha = log2bin(p_syntax_des->image_width - 1);
    	SINT32 Ws = 1 << Alpha;
        const SINT32 Beta = log2bin(p_syntax_des->image_height - 1);
    	const SINT32 Hs = 1<<Beta;
		
	    if(g_mp4_syntax.divx_version==500 && g_mp4_syntax.divx_build==413)
	    {
        	p_gmc->dU[0] = 16*Ws + RDIV( (16*Ws*(p_gmcwarp->duv[1].x+p_gmcwarp->duv[0].x*(1-2<<p_gmc->accuracy)))/(2<<p_gmc->accuracy), (SINT32)p_syntax_des->image_width );	 /* dU/dx */
        	p_gmc->dV[0] =		   RDIV( (16*Ws*(p_gmcwarp->duv[1].y+p_gmcwarp->duv[0].y*(1-2<<p_gmc->accuracy)))/(2<<p_gmc->accuracy), (SINT32)p_syntax_des->image_width );	 /* dV/dx */
        
        	if (nb_pts==2) 
            {
        		p_gmc->dU[1] = -p_gmc->dV[0];	/* -Sin */
        		p_gmc->dV[1] =	p_gmc->dU[0] ;	/* Cos */
				shift = Alpha+rho;
        	}
        	else
        	{
        		p_gmc->dU[1] =		 RDIV( 8*Hs*p_gmcwarp->duv[2].x, (SINT32)p_syntax_des->image_height );	 /* dU/dy */
        		p_gmc->dV[1] = 16*Hs + RDIV( 8*Hs*p_gmcwarp->duv[2].y, (SINT32)p_syntax_des->image_height );	 /* dV/dy */
        		if (Beta>Alpha) 
                {
            		p_gmc->dU[0] <<= (Beta-Alpha);
            		p_gmc->dV[0] <<= (Beta-Alpha);
            		Alpha = Beta;
            		Ws = Hs;
					shift = Beta + rho;
        		}
        		else 
       			{
            		p_gmc->dU[1] <<= (Alpha - Beta);
            		p_gmc->dV[1] <<= (Alpha - Beta);
					shift = Alpha + rho;
        		}
        	}
			#if 0
     	    if(   p_gmc->dU[0] == (2<<p_gmc->accuracy)<<shift
            && p_gmc->dV[0] == 0
            && p_gmc->dV[0] == 0
            && p_gmc->dU[1] == (2<<p_gmc->accuracy)<<shift)
     	    {
     	    #endif
     	    if (1)
     	    	{
     	        nb_pts = 1;
            	p_gmc->Uo	= ( p_gmcwarp->duv[0].x	 <<(16+ p_gmc->accuracy)) + (1<<15);
            	p_gmc->Vo	= ( p_gmcwarp->duv[0].y	 <<(16+ p_gmc->accuracy)) + (1<<15);
            	p_gmc->Uco = ((p_gmcwarp->duv[0].x-1)<<(17+ p_gmc->accuracy)) + (1<<17);
            	p_gmc->Vco = ((p_gmcwarp->duv[0].y-1)<<(17+ p_gmc->accuracy)) + (1<<17);
            	p_gmc->Uco = (p_gmc->Uco + p_gmc->dU[0] + p_gmc->dU[1])>>2;
            	p_gmc->Vco = (p_gmc->Vco + p_gmc->dV[0] + p_gmc->dV[1])>>2;	
				p_gmc->Uo >>= shift;
				p_gmc->Vo >>= shift;
				p_gmc->Uco >>= shift;
				p_gmc->Vco >>= shift;		
				p_gmc->num_wp = nb_pts;
     	    }
			else
			{
            	/* upscale to 16b fixed-point */
            	p_gmc->dU[0] <<= (16-Alpha - rho);
            	p_gmc->dU[1] <<= (16-Alpha - rho);
            	p_gmc->dV[0] <<= (16-Alpha - rho);
            	p_gmc->dV[1] <<= (16-Alpha - rho);
    			
            	p_gmc->Uo	= ( p_gmcwarp->duv[0].x	 <<(16+ p_gmc->accuracy)) + (1<<15);
            	p_gmc->Vo	= ( p_gmcwarp->duv[0].y	 <<(16+ p_gmc->accuracy)) + (1<<15);
            	p_gmc->Uco = ((p_gmcwarp->duv[0].x-1)<<(17+ p_gmc->accuracy)) + (1<<17);
            	p_gmc->Vco = ((p_gmcwarp->duv[0].y-1)<<(17+ p_gmc->accuracy)) + (1<<17);
            	p_gmc->Uco = (p_gmc->Uco + p_gmc->dU[0] + p_gmc->dU[1])>>2;
            	p_gmc->Vco = (p_gmc->Vco + p_gmc->dV[0] + p_gmc->dV[1])>>2;
			}
	    }
		else
	    {
        	p_gmc->dU[0] = 16*Ws + RDIV( 8*Ws*p_gmcwarp->duv[1].x, (SINT32)p_syntax_des->image_width );	 /* dU/dx */
        	p_gmc->dV[0] =		 RDIV( 8*Ws*p_gmcwarp->duv[1].y, (SINT32)p_syntax_des->image_width );	 /* dV/dx */
        
        	if (nb_pts==2) 
            {
        		p_gmc->dU[1] = -p_gmc->dV[0];	/* -Sin */
        		p_gmc->dV[1] =	p_gmc->dU[0] ;	/* Cos */
				
        	}
        	else
        	{
        		p_gmc->dU[1] =		 RDIV( 8*Hs*p_gmcwarp->duv[2].x, (SINT32)p_syntax_des->image_height );	 /* dU/dy */
        		p_gmc->dV[1] = 16*Hs + RDIV( 8*Hs*p_gmcwarp->duv[2].y, (SINT32)p_syntax_des->image_height );	 /* dV/dy */
        		if (Beta>Alpha) 
                {
            		p_gmc->dU[0] <<= (Beta-Alpha);
            		p_gmc->dV[0] <<= (Beta-Alpha);
            		Alpha = Beta;
            		Ws = Hs;
        		}
        		else 
       			{
            		p_gmc->dU[1] <<= Alpha - Beta;
            		p_gmc->dV[1] <<= Alpha - Beta;
        		}
        	}

        	/* upscale to 16b fixed-point */
        	p_gmc->dU[0] <<= (16-Alpha - rho);
        	p_gmc->dU[1] <<= (16-Alpha - rho);
        	p_gmc->dV[0] <<= (16-Alpha - rho);
        	p_gmc->dV[1] <<= (16-Alpha - rho);
        
        	p_gmc->Uo	= ( p_gmcwarp->duv[0].x	 <<(16+ p_gmc->accuracy)) + (1<<15);
        	p_gmc->Vo	= ( p_gmcwarp->duv[0].y	 <<(16+ p_gmc->accuracy)) + (1<<15);
        	p_gmc->Uco = ((p_gmcwarp->duv[0].x-1)<<(17+ p_gmc->accuracy)) + (1<<17);
        	p_gmc->Vco = ((p_gmcwarp->duv[0].y-1)<<(17+ p_gmc->accuracy)) + (1<<17);
        	p_gmc->Uco = (p_gmc->Uco + p_gmc->dU[0] + p_gmc->dU[1])>>2;
        	p_gmc->Vco = (p_gmc->Vco + p_gmc->dV[0] + p_gmc->dV[1])>>2;
	    }
    }
#endif
}


/*------------------------------------------------------------------------------

        Function name: Mp4_GetUserDataBuf

        Description: 申请user data buf
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VDEC_USRDAT_S *Mp4_GetUserDataBuf(SINT32 ChanID, VDEC_USRDAT_S* *pUserData, UINT32 UserID)
{       
    if (pUserData[UserID]==NULL)
    {
        pUserData[UserID] = GetUsd(ChanID);
        if (pUserData[UserID] != NULL)
        {
            pUserData[UserID]->from=UserID+4;
        }        
    }

    return pUserData[UserID];
}

/*------------------------------------------------------------------------------

        Function name: Mp4_RecycleUsrData

        Description: 如果user data空间申请后，该帧又丢弃，则需要释放
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VOID Mp4_ClearUsrData(SINT32 ChanID, VDEC_USRDAT_S* *pUserData)
{
    UINT32 i;

    for (i=0; i<4; i++)
    {
        FreeUsdByDec(ChanID, pUserData[i]);
        pUserData[i] = NULL;
    }         
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_Init

        Description: 初始化语法部分
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VOID Mp4_Syntax_Init(MP4_CTX_S *pCtx)
{
    UINT16 i;

    memset(&pCtx->MP4Vos,0,sizeof(pCtx->MP4Vos));
    memset(&pCtx->MP4Vol,0,sizeof(pCtx->MP4Vol));
    memset(&pCtx->MP4Vop,0,sizeof(pCtx->MP4Vop));
    memset(&pCtx->MP4Syntax,0,sizeof(pCtx->MP4Syntax));
    memset(&pCtx->MP4SyntaxState,0,sizeof(pCtx->MP4SyntaxState));

    /* VOL pCtx->MP4Vol.video_object_layer_verid 容错处理*/
    pCtx->MP4Syntax.syn_vos.visual_object_verid = 1;
    pCtx->IPVopErr = 1; 
    for (i=0; i<64; i++)
    {
        pCtx->MP4Vol.intra_quant_mat[i] = default_intra_matrix[i];
    }
    for (i=0;i<64;i++)
    {
        pCtx->MP4Vol.nonintra_quant_mat[i] = default_inter_matrix[i];
    }
}


/*------------------------------------------------------------------------------

        Function name: Global_Data_Init

        Description: 初始化全局数据
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Global_Data_Init(MP4_CTX_S *pCtx)
{
    UINT32 i;
 
    /*全局信息清零操作 */
    memset((UINT8*)&pCtx->VdmMemAllot, 0, sizeof(VDM_MEM_ALLOT));
    memset((UINT8*)&pCtx->BitsObj, 0, sizeof(BITS_OBJ));

    /*语法信息初始化 */
    Mp4_Syntax_Init(pCtx);

    for (i=0; i<4; i++)
    {
        pCtx->UsrData[i] = NULL;
    }
    
    pCtx->FrameNum = 0;
    pCtx->DecMode = IPB_MODE;
    pCtx->SeqCnt = 0;
    pCtx->ImgCntOfSeq = 0;
    pCtx->ErrorLevel = 0;
    pCtx->CurUsrData = NULL;
    pCtx->OldPicWidth = 0;
    pCtx->OldPicHeight = 0;
    pCtx->NewPicWidth = 0;
    pCtx->NewPicHeight = 0;
    pCtx->UserID = 0;

    return MPEG4_INIT_SUCCESS;
}


/*------------------------------------------------------------------------------

        Function name: Bs_Get_Matrix

        Description: 更新量化表
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VOID Bs_Get_Matrix(BS *bs,UINT32 *matrix)
{
    SINT16 i = 0;
    UINT32 last, value = 0;

    do 
    {
        last = value;
        value = BsGet(bs, 8);
        matrix[scan_tables[0][i++]] = value;
    }
    while (value != 0 && i < 64);

    if (value != 0)
    {
        return;
    }

    i--;
    while (i < 64) 
    {
        matrix[scan_tables[0][i++]] = last;
    }

    return;
}


/*------------------------------------------------------------------------------

        Function name: NextStartCode

        Description: 分析头信息
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 NextStartCode(MP4_SYNTAX *pMp4Syntax, UINT8* pCode, SINT32 CodeLen, UINT32 *pStartCode)
{
    UINT32 start_code;
    SINT32 len = CodeLen;
    UINT8* ptr = pCode;
    SINT32 BitUsed = 0x0;
    BS     local_bs;
  
    BsInit(&local_bs, ptr, len);
    while ((len*8 - BitUsed) >= 32)
    {
        start_code = BsShow(&local_bs, 32);
        if ((start_code == VOP_START_CODE)
         ||(VIDOBJLAY_START_CODE == (start_code & ~VIDOBJLAY_START_CODE_MASK)))
        {
            /* 当前码流格式标记为"非短头模式" */
            pMp4Syntax->is_short_header = NON_SHORT_HEADER_ID;
            /* 对ShortHeader Picture 计数清0 */
            pMp4Syntax->SH_num = 0;
            *pStartCode = start_code;
            BitUsed = BsPos(&local_bs);
            return BitUsed;
        }
        else if (SHORT_VIDEO_START_CODE == (start_code & 0xfffffc00))
        {
            if (NON_SHORT_HEADER_ID != pMp4Syntax->is_short_header)
            {
                /* 当前码流尚未标记为非短头模式,将当前码流格式标记为"短头"模式 */
                pMp4Syntax->is_short_header = SHORT_HEADER_ID;
                *pStartCode = SHORT_HEADER;
                BitUsed = BsPos(&local_bs);
                return BitUsed;
            }
            else 
            {
                /* 码流已经标记为"非短头"模式,Picture 计数 */
                pMp4Syntax->SH_num++;
                if (pMp4Syntax->SH_num > SH_THRESHOLD)
                {
                    /* 将当前码流格式标记为"短头"模式 */
                    *pStartCode = SHORT_HEADER;
                    pMp4Syntax->is_short_header = SHORT_HEADER_ID;
                    BitUsed = BsPos(&local_bs);
                    return BitUsed;
                }
                BsSkip(&local_bs, 8);
                BitUsed = BsPos(&local_bs);
            }
        }
        else if (START_CODE_PRE == (start_code & 0xffffff00))
        {
            /* 找到非VOL、VOP、SH同步头 */
            *pStartCode = start_code;
            BitUsed = BsPos(&local_bs);
            return BitUsed;
        }
        else
        {
            /* 未找到同步头 */
            BsSkip(&local_bs, 8);
            BitUsed = BsPos(&local_bs);
        }
        
    }
    
    /* 跳出while，一定是码流不足 */
    *pStartCode = NO_START_CODE;
    BitUsed = BsPos(&local_bs);

    return BitUsed;
}    


SINT32 Mp4SearchStartCode(UINT8* pCode, SINT32 CodeLen)
{   
    UINT8 *ptr,*pEnd,byte;   
    SINT32 ofst;

    if (CodeLen < 5)
    {
        /* 如果码流字节小于5，不调用该函数 */
        return 0;
    }
    pEnd = pCode + CodeLen;
    for ( ptr=pCode+2; ptr<pEnd; )       
    {
        byte = ptr[0];
        if ( (byte != 0x00) && (byte != 0x01) &&((byte&0xfc)!=0x80))
        {
            ptr += 3;
            continue;
        }
        else if ( byte==0x00 )  
        {
            if ( ptr[-1] == 0x00 )
            {
                ptr += 1;
                continue;
            }
            else if ( ptr[1] == 0x00 )
            {
                ptr += 2;
                continue;
            }
            else
            {
                ptr+=4;
                continue;
            }
        }                
        else if ( byte == 0x01 )  //非短头
        {
            if ( ptr[-2]==0x00 && ptr[-1]==0x00 )
            {
                ofst = (SINT32)(ptr - pCode - 2);
                return ofst;
            }
            else
            {
                ptr+=3;
                continue;
            }
        }
        else //短头
        {
            if ( ptr[-2]==0x00 && ptr[-1]==0x00 )
            {
                ofst = (SINT32)(ptr - pCode - 2);
                return ofst;
            }
            else
            {
                ptr+=3;
                continue;
            }
        }
    }
 
    return (pEnd-pCode-2); 
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_Gop

        Description: GOP 语法分析
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Mp4_Syntax_Gop(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    BS     local_bs;
    SINT32 BitUsed = 0x0;
    //UINT32 hours, minutes, seconds;

    BsInit(&local_bs, ptr, len);

    BsSkip(&local_bs, 32);

    /* time_code */
    //hours = BsGet(&local_bs, 5);
    BsGet(&local_bs, 5);
    //minutes = BsGet(&local_bs, 6);
    BsGet(&local_bs, 6);
    MARKER_GOP(local_bs);
    //seconds = BsGet(&local_bs, 6);
    BsGet(&local_bs, 6);

    /* 目前这两个信息并没有用到*/
    pCtx->MP4Syntax.closed_gov = BsGet(&local_bs, 1);
    pCtx->MP4Syntax.broken_link = BsGet(&local_bs, 1);

    /* 返回状态和消耗码流bit数 */
    pCtx->MP4SyntaxState.gop_decode_right = SYN_GOPOK;
    BitUsed = BsPos(&local_bs);

    return BitUsed;
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_ShortHeader

        Description: 短头语法分析
                 
        Input: 
            
        Output:

        Return:

        Others:


------------------------------------------------------------------------------*/
SINT32 Mp4_Syntax_ShortHeader(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    BS     local_bs;
    SINT32 BitUsed = 0;
    UINT32 i = 0;
    UINT32 pei = 0;
    MP4_SLICE_INFO *pSlcPara = NULL;

    /* 进入vop时，slice num 应该是零 */
    if(0 != pCtx->Mp4DecParam.SlcNum)
    {
         dprint(PRN_ERROR,"Warning : vop slice num %d != 0\n",pCtx->Mp4DecParam.SlcNum);
         pCtx->Mp4DecParam.SlcNum = 0;
    }

    pSlcPara = &(pCtx->Mp4DecParam.SlcPara[pCtx->Mp4DecParam.SlcNum]);

    /* ShortHeader 标识判断在NextStartCode函数中完成 */
    BsInit(&local_bs, ptr, len);
    
    /* 初始化VOP结构体 */
    memset(&pCtx->MP4Vop,0,sizeof(pCtx->MP4Vop));
    
    BsSkip(&local_bs, 22);
    BsSkip(&local_bs, 13);
    
    pCtx->MP4Vop.source_format = BsGet(&local_bs, 3);
    switch (pCtx->MP4Vop.source_format)
    {
        case 1:
            pCtx->MP4Vop.num_gobs_invop = 6;
            pCtx->MP4Vop.num_mb_ingob = 8;
            pCtx->MP4Syntax.image_width = 128;
            pCtx->MP4Syntax.image_height = 96;
            break;
        case 2:
            pCtx->MP4Vop.num_gobs_invop = 9;             
            pCtx->MP4Vop.num_mb_ingob = 11;              
            pCtx->MP4Syntax.image_width = 176; 
            pCtx->MP4Syntax.image_height = 144;
            break;
        case 3:
            pCtx->MP4Vop.num_gobs_invop = 18;            
            pCtx->MP4Vop.num_mb_ingob = 22;              
            pCtx->MP4Syntax.image_width = 352; 
            pCtx->MP4Syntax.image_height = 288;
            break;
        case 4:
            pCtx->MP4Vop.num_gobs_invop = 18;            
            pCtx->MP4Vop.num_mb_ingob = 88;              
            pCtx->MP4Syntax.image_width = 704; 
            pCtx->MP4Syntax.image_height = 576;
            break;
        default:
            /* 其余值均不支持 */
            pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;
            BitUsed = BsPos(&local_bs);
            REPORT_UNSUPPORT(pCtx->ChanID);
            return BitUsed;                
    }

    pCtx->MP4Vop.vop_coding_type= BsGet(&local_bs, 1);

    #ifdef SEARCH_IVOP
    if ((NEXT_I_MODE == pCtx->MP4Syntax.coding_mode) || ((1 == pCtx->IPVopErr )&&( I_VOP != pCtx->MP4Vop.vop_coding_type)))
    {
        BitUsed = BsPos(&local_bs);
        return BitUsed;
    }
    #endif
   
    BsSkip(&local_bs, 4);
    pCtx->MP4Vop.vop_quant = BsGet(&local_bs, 5);
    if (pCtx->MP4Vop.vop_quant < 1)
    {
       pCtx->MP4Vop.vop_quant = 1; 
    }
    BsSkip(&local_bs,1);
    
    /* pei解析 */
    do
    {
        pei = BsGet(&local_bs, 1);
        
        /* 防止越界 */
        if (pei == 1)
        {
            BitUsed = BsPos(&local_bs);
            if (BitUsed  >(len * 8))
            {
                /* 认为解析正确，但越界 */
                BitUsed = BsPos(&local_bs);
                return BitUsed;    
            }
            BsSkip(&local_bs, 8);
        }
        i++;
    }
    while ((pei == 1) && (i < PEI_THRESHOLD));

    /* ShortHeader 解析完成，越界判断 */
    //BitUsed = BsPos(&local_bs);
    if (i >= PEI_THRESHOLD)
    {
        /* 没有越界，大于阈值，认为出错 */
        pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;
        BitUsed = BsPos(&local_bs);
        REPORT_SE_ERR(pCtx->ChanID);
        return BitUsed;    
    }
    
    pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPOK;
//    pCtx->MP4Syntax.decode_syntax_OK = SYNTAX_OK;
	pCtx->PicIntegrality |= MP4_FOUND_VOPHDR;

    pCtx->Mp4DecParam.SlcNum++;

    /* 正确解析IPVOP, 对标示清０*/   
    pCtx->MP4Vop.vop_fcode_forward = 1;
    BitUsed = BsPos(&local_bs);
    
    /* 记录第零个slice的码流信息 */
	pSlcPara->bit_len[0] = len * 8 - BitUsed;
	pSlcPara->bit_offset[0] = pCtx->BitsObj.offset + (BitUsed%8);
	pSlcPara->phy_address[0] = pCtx->BitsObj.phy_addr + (BitUsed/8);

	/* 如果出现分包，这记录另一包的信息*/
	if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)&& (1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg) )
	{
		pSlcPara->bit_len[1] = pCtx->stCurPacket.StreamPack[1].LenInByte * 8;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = pCtx->stCurPacket.StreamPack[1].PhyAddr;
	}
	else
	{
		pSlcPara->bit_len[1] = 0;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = 0;
	}
    /* 第零个slice的其他信息使用的是vop级的 */
	pSlcPara->vop_coding_type = pCtx->MP4Vop.vop_coding_type;
	pSlcPara->vop_fcode_backward = pCtx->MP4Vop.vop_fcode_backward;
	pSlcPara->vop_fcode_forward = pCtx->MP4Vop.vop_fcode_forward;	
	pSlcPara->vop_quant = pCtx->MP4Vop.vop_quant;
	pSlcPara->intra_dc_vlc_thr = pCtx->MP4Vop.intra_dc_vlc_thr;
    
    if(pCtx->StreamIDNum != 0)
    {
        dprint(PRN_ERROR,"warning streamIDNum %d != 0 \n",pCtx->StreamIDNum);
        MP4_ClearCurPic(pCtx);
    }
    MP4_Record_SlcSegID(pCtx);

    return BitUsed;
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_UserData

        Description: 用户数据分析
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Mp4_Syntax_UserData(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    UINT32  userdata_len;
    SINT32  BitUsed = 0x0;
    SINT32  i;
    /* 用以监控码流i-2, i-1, i三个字节组合情况，可一次判断 */
    UINT32  monitor;
    SINT32  ver = 0, build = 0, ver2 = 0, ver3 = 0;
    SINT32  tmp = 0;
    SINT32  e = 0;
    SINT8  last = 0;
	UINT8  *buf;
    /* 正确解userdata的最小组合：00 00 01 b2 00 00 01，此时userdata长度=0 */
    if ( len < 7 )
    {
        pCtx->MP4SyntaxState.userdata_decode_right = SYN_USERDATAERR;
        /* 通知上层程序码流不足，(len+1)是为了方便上层判断出码流越界 */
        BitUsed = (len+1)*8;
        return BitUsed;
    }
    /* 有效的user data字节计数 */
    userdata_len = 0;
    /* 故意赋一个无效的初值，避免后续错误检测出00 00 01 */
    monitor = 0xffffff00;
    for ( i = 4; i < len; i++ )
    {
        /* lhh: 这种地址取值的方式是否有endian方式影响 */
        monitor = ( monitor | (UINT32)ptr[i] ) << 8;
        /* 发现 00 00 01，这是userdata正常结束的条件 */
        if ( monitor == 0x00000100 )
        {
            /* 减2是为了把已经吃掉的00 00吐回去，避免消耗正常的起始码 */
            i -= 2;
            break;
        }
        else
        {
            /* 拷贝一个字节的user_data. */
            pCtx->TmpUserData[i-4] = ptr[i];
            userdata_len++;
            /* userdata 超长，认为是不正常的userdata，丢弃 */
            if ( userdata_len > (MAX_USRDAT_SIZE + 2))
            {
                /* 减2是因为担心最后两个字节是00 00，而这碰巧又是下一个起始码的一部分 */
                BitUsed = (i-2)*8;
                pCtx->MP4SyntaxState.userdata_decode_right = SYN_USERDATAERR;
                return BitUsed;
            }
        }
    }

    /* 循环退出有两种可能：遇到00 00 01正常解完userdata，或者userdata没有超长码流倒消耗完了 */
    if ( i <= len ) 
    {
        /* case1. 如果解码没有越界：正常解完userdata */
        pCtx->MP4SyntaxState.userdata_decode_right = SYN_USERDATAOK;
        BitUsed = i*8;
               
        if (userdata_len > 2)
        {
            /* user data 长度：userdata_len-2 */
            pCtx->CurUsrData=Mp4_GetUserDataBuf(pCtx->ChanID, pCtx->UsrData,pCtx->UserID);
            /* user data空间申请成功后才拷贝 */
            if (pCtx->CurUsrData!=NULL)
            {
                pCtx->CurUsrData->data_size=userdata_len-2;  
                userdata_len-=2;
                /*MAX_USRDAT_SIZE 不能大于1024，否则会有问题 */
                memcpy( pCtx->CurUsrData->data, pCtx->TmpUserData, CLIP1(MAX_USRDAT_SIZE, (SINT32)(userdata_len+2)) );
                pCtx->CurUsrData->PTS = pCtx->pstExtraData->pts;
                REPORT_USRDAT(pCtx->ChanID, pCtx->CurUsrData);
            }
            
        	tmp =  CLIP1(MAX_USRDAT_SIZE, (SINT32)(userdata_len+2));
            pCtx->TmpUserData[tmp]=0;
            buf = pCtx->TmpUserData;//+4;

            //:TODO: secure os must provide sscanf intf
        #ifdef ENV_ARMLINUX_KERNEL
            /* divx detection */
            e=sscanf(buf, "DivX%dBuild%d%c", &ver, &build, (char*)(&last));
            if(e<2)
            {
        	    e=sscanf(buf, "DivX%db%d%c", &ver, &build, (char*)(&last));
            }
            if(e>=2)
        	{
                pCtx->MP4Syntax.divx_version = ver;
                pCtx->MP4Syntax.divx_build   = build;
                pCtx->MP4Syntax.divx_packed  = (e==3) && (last=='p');
            }
            /* ffmpeg detection */
            e=sscanf(buf, "FFmpe%*[^b]b%d", &build)+3;
            if(e!=4)
            {
                e=sscanf(buf, "FFmpeg v%d.%d.%d / libavcodec build: %d", &ver, &ver2, &ver3, &build);
            }
            if(e!=4)
        	{
                e=sscanf(buf, "Lavc%d.%d.%d", &ver, &ver2, &ver3)+1;
                if (e>1)
                {
                    build= (ver<<16) + (ver2<<8) + ver3;
                }
            }
            if(e!=4)
        	{
                if(strncmp(buf, "ffmpeg", 7)==0)
        		{
                    pCtx->MP4Syntax.lavc_build= 4600;
                }
            }
            if(e==4)
        	{
                pCtx->MP4Syntax.lavc_build= build;
            }
        
            /* xvid detection */
            e=sscanf(buf, "XviD%d", &build);
            if(e==1)
        	{
                pCtx->MP4Syntax.xvid_build= build;
            }
        #endif
        	
        	pCtx->MP4Syntax.FF_BUG_QPEL_CHROMA = 0;
        	pCtx->MP4Syntax.FF_BUG_QPEL_CHROMA2 = 0;
        	pCtx->MP4Syntax.FF_BUG_EDGE_EXTEND = 0;
        	pCtx->MP4Syntax.FF_BUG_EDGE_FIND_POINT = 0;	
        	pCtx->MP4Syntax.FF_BUG_DIVX500B413 = 0;
            if((pCtx->MP4Syntax.xvid_build) && (pCtx->MP4Syntax.divx_version))
        	{
                pCtx->MP4Syntax.divx_version = 0;
                pCtx->MP4Syntax.divx_build = 0;
            }
            if(pCtx->MP4Syntax.divx_version>=500)
        	{
                pCtx->MP4Syntax.FF_BUG_QPEL_CHROMA = 1;
            }
            if((pCtx->MP4Syntax.xvid_build) && (pCtx->MP4Syntax.xvid_build<=1))
        	{
                pCtx->MP4Syntax.FF_BUG_QPEL_CHROMA = 1;
            }
        	if(pCtx->MP4Syntax.divx_version>502)
        	{
                pCtx->MP4Syntax.FF_BUG_QPEL_CHROMA2 = 1;
        	}
            if((pCtx->MP4Syntax.xvid_build) && (pCtx->MP4Syntax.xvid_build<=12))
            {
                pCtx->MP4Syntax.FF_BUG_EDGE_EXTEND = 1;
            }
            if((pCtx->MP4Syntax.lavc_build) && (pCtx->MP4Syntax.lavc_build<4670))
            {
                pCtx->MP4Syntax.FF_BUG_EDGE_EXTEND = 1;
            }
            if((pCtx->MP4Syntax.divx_version) && (pCtx->MP4Syntax.divx_version<500))
            {
                pCtx->MP4Syntax.FF_BUG_EDGE_EXTEND = 1;
            }
            if((pCtx->MP4Syntax.divx_version == 500) && (pCtx->MP4Syntax.divx_build == 413))
        	{
                pCtx->MP4Syntax.FF_BUG_DIVX500B413 = 1;
            }
        }
        else
        {
            /* no user data */
        }
    }
    else 
    {
        /* case2. 码流耗尽了 */
        /* 通知上层程序码流不足，(len+1)是为了方便上层判断出码流越界 */
        BitUsed = (len+1)*8;
    }

    return BitUsed;
}

/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_Vo

        Description: VO语法分析
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Mp4_Syntax_Vo(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    BS     local_bs;
    SINT32 BitUsed = 0x0;
    
    BsInit(&local_bs, ptr, len);
    
    /* 初始化 */
    pCtx->MP4Syntax.syn_vos.is_visual_object_identifier= 0;
    pCtx->MP4Syntax.syn_vos.visual_object_verid = 1;
    pCtx->MP4Syntax.syn_vos.visual_object_priority = 0;
    pCtx->MP4Syntax.syn_vos.visual_object_type = 0;
    pCtx->MP4Syntax.syn_vos.video_signal_type = 0;
    pCtx->MP4Syntax.syn_vos.video_format = 0;
    pCtx->MP4Syntax.syn_vos.video_range = 0;
    pCtx->MP4Syntax.syn_vos.colour_description = 0;
    pCtx->MP4Syntax.syn_vos.colour_primaries = 0;
    pCtx->MP4Syntax.syn_vos.transfer_characteristics = 0;
    pCtx->MP4Syntax.syn_vos.matrix_coefficients = 0;

    
    BsSkip(&local_bs, 32);
    pCtx->MP4Vos.is_visual_object_identifier= BsGet(&local_bs, 1);

    if (pCtx->MP4Vos.is_visual_object_identifier) 
    {
        pCtx->MP4Vos.visual_object_verid = BsGet(&local_bs, 4);     
        pCtx->MP4Vos.visual_object_priority = BsGet(&local_bs, 3);
    }
    else
    {
        pCtx->MP4Vos.visual_object_verid = 1;
    }

    pCtx->MP4Vos.visual_object_type = BsGet(&local_bs, 4);
      
    if (pCtx->MP4Vos.visual_object_type == VIDEO_ID)
    {
        /* Video 类型 */
        pCtx->MP4Vos.video_signal_type = BsGet(&local_bs, 1);
        if (pCtx->MP4Vos.video_signal_type)
        {
            pCtx->MP4Vos.video_format = BsGet(&local_bs, 3);
            pCtx->MP4Vos.video_range = BsGet(&local_bs, 1);    
            pCtx->MP4Vos.colour_description = BsGet(&local_bs, 1);

            if (pCtx->MP4Vos.colour_description)
            {
                pCtx->MP4Vos.colour_primaries = BsGet(&local_bs, 8);
                pCtx->MP4Vos.transfer_characteristics = BsGet(&local_bs, 8);
                pCtx->MP4Vos.matrix_coefficients = BsGet(&local_bs, 8);
            }
        }
    }
    else
    {
        /* 其他不支持类型 */
        pCtx->MP4SyntaxState.vo_decode_right = SYN_VOERR;
        BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
        return BitUsed;
    }

    /* 正确解码完成 */
    pCtx->MP4SyntaxState.vo_decode_right = SYN_VOOK;
    
    /* 备份语法信息 */
    if ( BsPos(&local_bs) <= len*8 )
    {
        pCtx->MP4Syntax.syn_vos.is_visual_object_identifier = pCtx->MP4Vos.is_visual_object_identifier;
        pCtx->MP4Syntax.syn_vos.visual_object_verid = pCtx->MP4Vos.visual_object_verid;
        pCtx->MP4Syntax.syn_vos.visual_object_priority = pCtx->MP4Vos.visual_object_priority;
        pCtx->MP4Syntax.syn_vos.visual_object_type = pCtx->MP4Vos.visual_object_type;
        pCtx->MP4Syntax.syn_vos.video_signal_type = pCtx->MP4Vos.video_signal_type;
        pCtx->MP4Syntax.syn_vos.video_format = pCtx->MP4Vos.video_format;
        pCtx->MP4Syntax.syn_vos.video_range = pCtx->MP4Vos.video_range;
        pCtx->MP4Syntax.syn_vos.colour_description = pCtx->MP4Vos.colour_description;
        pCtx->MP4Syntax.syn_vos.colour_primaries = pCtx->MP4Vos.colour_primaries;
        pCtx->MP4Syntax.syn_vos.transfer_characteristics = pCtx->MP4Vos.transfer_characteristics;
        pCtx->MP4Syntax.syn_vos.matrix_coefficients = pCtx->MP4Vos.matrix_coefficients;
    }
    BitUsed = BsPos(&local_bs);

    return BitUsed;
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_Vop

        Description: VOP 语法分析
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Mp4_Syntax_Vop(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    BS     local_bs;
    SINT32 BitUsed = 0x0;
    UINT32 i = 0;
    UINT32 time_incr = 0x0;
    UINT32 time_increment=0;
    SINT32 x, y;
	UINT32 length;
    MP4_SLICE_INFO *pSlcPara = NULL;

    /* 进入vop时，slice num 应该是零 */
    if(0 != pCtx->Mp4DecParam.SlcNum)
    {
         dprint(PRN_ERROR,"Warning : vop slice num %d != 0\n",pCtx->Mp4DecParam.SlcNum);
         pCtx->Mp4DecParam.SlcNum = 0;
    }

    pSlcPara = &(pCtx->Mp4DecParam.SlcPara[pCtx->Mp4DecParam.SlcNum]);

    /* VOL 有效性判断 */
    if (!pCtx->MP4Syntax.vol_decode_over)
    {
        /* VOL无效 */
        pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;
		dprint(PRN_ERROR, "%s vol_decode_over %d invalid\n", __func__, pCtx->MP4Syntax.vol_decode_over);
        return 32;
    }
    BsInit(&local_bs, ptr, len);
    
    /* 初始化VOP结构体 */
    memset(&pCtx->MP4Vop, 0, sizeof(pCtx->MP4Vop));
    pCtx->MP4SyntaxState.vop_decode_right = 0;
    
    BsSkip(&local_bs, 32);
    
    pCtx->MP4Vop.vop_coding_type = BsGet(&local_bs, 2);
    dprint(PRN_PIC, "vop ---%d\n", pCtx->MP4Vop.vop_coding_type);

    if ((pCtx->MP4Vop.vop_coding_type == S_VOP)&&((g_VdmCharacter&VDM_SUPPORT_GMC) == 0))
    {
        /* 无效VOP或Sprite编码 */
        pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;
        BitUsed = BsPos(&local_bs);
        REPORT_SE_ERR(pCtx->ChanID);
		dprint(PRN_ERROR, "VDH doesn't support S_VOP\n");
        return BitUsed;
    }

    /* 对于只解析I帧的判断 */
    if ((ONLY_I_MODE == pCtx->MP4Syntax.coding_mode)&&(pCtx->MP4Vop.vop_coding_type != I_VOP))
    {
        BitUsed = BsPos(&local_bs);
		dprint(PRN_ERROR, "%s I mode meet not I_VOP\n", __func__);
        return BitUsed;
    }

    #ifdef SEARCH_IVOP
    /* 对于参考帧错误，寻找下一个I帧的判断 */
    if ((NEXT_I_MODE == pCtx->MP4Syntax.coding_mode) || (1 == pCtx->IPVopErr && I_VOP != pCtx->MP4Vop.vop_coding_type))
    {
        BitUsed = BsPos(&local_bs);
        return BitUsed;
    }
    #endif

    /* modulo_time_base解析 */
    for(i = 0; i < MARKER_THRESHOLD; i++)
    {
        if(BsGet(&local_bs,1) == 0)
        {
            break;
        }

        /* 防止越界 */
        BitUsed = BsPos(&local_bs);
        if(BitUsed >(len * 8))
        {
            /* 越界，但解析正确 */
            BitUsed = BsPos(&local_bs);
            dprint(PRN_ERROR,"parse time_module_base stream not enough\n");
            return BitUsed;    
        }
        time_incr++;
    }

    if (i >= MARKER_THRESHOLD)
    {
        /* 大于阈值跳出，认为解析错误 */
        pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;
        BitUsed = BsPos(&local_bs);
        dprint(PRN_ERROR, "module time base parse error, more than %d '1' was found!\n", i);
        return BitUsed;
    }
 
    MARKER_VOP(local_bs);
    if (pCtx->MP4Syntax.syn_vol.vop_time_incr_bits)
    {
        time_increment = BsGet(&local_bs,pCtx->MP4Syntax.syn_vol.vop_time_incr_bits);
    }

    /* 时间信息计算 */
    pCtx->MP4Syntax.time_incr=time_incr;
    pCtx->MP4Syntax.time_increment=time_increment;
    MARKER_VOP(local_bs);
    
    pCtx->MP4Vop.vop_coded = BsGet(&local_bs,1);
    if (pCtx->MP4Vop.vop_coded == 0)
    {
        /* N_VOP处理 */
        pCtx->MP4Vop.vop_coding_type = N_VOP;
        pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPOK;
//        pCtx->MP4Syntax.decode_syntax_OK = SYNTAX_OK;
        pCtx->MP4Syntax.syn_vop.vop_coding_type = N_VOP;
        pCtx->PicIntegrality |= MP4_FOUND_NVOP;
        BitUsed = BsPos(&local_bs);
        return BitUsed;
    }
    
    if( (pCtx->MP4Vop.vop_coding_type == P_VOP) || (pCtx->MP4Vop.vop_coding_type == S_VOP && pCtx->MP4Syntax.syn_vol.sprite_enable == SPRITE_GMC) )
    {
        pCtx->MP4Vop.vop_rounding_type = BsGet(&local_bs, 1);
        //dprint(PRN_DBG, "g_mp4_vop.vop_rounding_type %d\n", pCtx->MP4Vop.vop_rounding_type);
    }
	else
	{
	    pCtx->MP4Vop.vop_rounding_type = 0;
	}    
    
    pCtx->MP4Vop.vop_reduced_resolution = 0;
   
    if (pCtx->MP4Syntax.syn_vol.video_object_layer_shape != VIDOBJLAY_SHAPE_BINARY_ONLY)
    {
        pCtx->MP4Vop.intra_dc_vlc_thr= BsGet(&local_bs,3);  
        if (pCtx->MP4Vol.interlaced)
        {
            pCtx->MP4Vop.top_field_first = BsGet(&local_bs,1);
            pCtx->MP4Vop.alternate_vertical_scan_flag = BsGet(&local_bs,1);
        }
        else
        {
            pCtx->MP4Vop.top_field_first = 2;
            pCtx->MP4Vop.alternate_vertical_scan_flag = 0;
        }
		
        if ((pCtx->MP4Syntax.syn_vol.sprite_enable == SPRITE_STATIC || pCtx->MP4Syntax.syn_vol.sprite_enable == SPRITE_GMC) && pCtx->MP4Vop.vop_coding_type == S_VOP) 
		{
	        //dprint(PRN_DBG, "points %d\n", pCtx->MP4Syntax.syn_vol.sprite_warping_points);
			for (i = 0 ; i < pCtx->MP4Syntax.syn_vol.sprite_warping_points; i++)
			{
			    x = 0;
				y = 0;
				length = bs_get_spritetrajectory(&local_bs);
				if(length)
				{
					x = BsGet(&local_bs, length);
					if ((x >> (length - 1)) == 0) /* if MSB not set it is negative*/
					{
						x = - (x ^ ((1 << length) - 1));
					}
				}
				if(!(pCtx->MP4Syntax.divx_version==500 && pCtx->MP4Syntax.divx_build==413))
                {
                    BsSkip(&local_bs, 1);
				}

				length = bs_get_spritetrajectory(&local_bs);
				if(length)
				{
					y = BsGet(&local_bs, length);
					if ((y >> (length - 1)) == 0) /* if MSB not set it is negative*/
					{
						y = - (y ^ ((1 << length) - 1));
					}
				}
				BsSkip(&local_bs, 1);

				pCtx->MP4Vop.gmc_warp.duv[i].x = x;
				pCtx->MP4Vop.gmc_warp.duv[i].y = y;
				//dprint(PRN_DBG, "duvx %d duvy %d\n", x, y);
			}
		}
		
        /* 因不支持not_8_bit,pCtx->MP4Vop.quant_precision必然为５ */
        pCtx->MP4Vop.vop_quant = BsGet(&local_bs, 5);
        
        if (pCtx->MP4Vop.vop_quant < 1)
        {
           pCtx->MP4Vop.vop_quant = 1; 
        }
        
        if (pCtx->MP4Vop.vop_coding_type != I_VOP)
        {
            pCtx->MP4Vop.vop_fcode_forward = BsGet(&local_bs,3);
            if (0 == pCtx->MP4Vop.vop_fcode_forward)
            {
                pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;
                BitUsed = BsPos(&local_bs);
                REPORT_SE_ERR(pCtx->ChanID);
                dprint(PRN_ERROR, "error: vop_coding_type = %d, but vop_fcode_forward = 0\n", pCtx->MP4Vop.vop_coding_type);
                return BitUsed;
            }
        }
        if (pCtx->MP4Vop.vop_coding_type == B_VOP)
        {
            pCtx->MP4Vop.vop_fcode_backward = BsGet(&local_bs,3);
            if ( (0 == pCtx->MP4Vop.vop_fcode_backward))
            {
                pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPERR;
                BitUsed = BsPos(&local_bs);
                REPORT_SE_ERR(pCtx->ChanID);
                dprint(PRN_ERROR, "error: B vop, but vop_fcode_backward = 0\n");
                return BitUsed;
            }
        }
        
    }
    
    /* 返回状态和消耗码流bit数 */
    pCtx->MP4SyntaxState.vop_decode_right = SYN_VOPOK;
//    pCtx->MP4Syntax.decode_syntax_OK = SYNTAX_OK;
	pCtx->PicIntegrality |= MP4_FOUND_VOPHDR;

    pCtx->Mp4DecParam.SlcNum++;
    
    memcpy(&pCtx->MP4Syntax.syn_vop, &pCtx->MP4Vop, sizeof(MP4_VOP));
    BitUsed = BsPos(&local_bs);

    /* 记录第零个slice的码流信息 */
	pSlcPara->bit_len[0] = len * 8 - BitUsed;
	pSlcPara->bit_offset[0] = pCtx->BitsObj.offset + (BitUsed%8);
	pSlcPara->phy_address[0] = pCtx->BitsObj.phy_addr + (BitUsed/8);

	/* 如果出现分包，这记录另一包的信息*/
	if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)&& (1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg) )
	{
		pSlcPara->bit_len[1] = pCtx->stCurPacket.StreamPack[1].LenInByte * 8;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = pCtx->stCurPacket.StreamPack[1].PhyAddr;
	}
	else
	{
		pSlcPara->bit_len[1] = 0;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = 0;
	}

    /* 第零个slice的其他信息使用的是vop级的 */
	pSlcPara->vop_coding_type = pCtx->MP4Vop.vop_coding_type;
	pSlcPara->vop_fcode_backward = pCtx->MP4Vop.vop_fcode_backward;
	pSlcPara->vop_fcode_forward = pCtx->MP4Vop.vop_fcode_forward;	
	pSlcPara->vop_quant = pCtx->MP4Vop.vop_quant;
	pSlcPara->intra_dc_vlc_thr = pCtx->MP4Vop.intra_dc_vlc_thr;

    if(pCtx->StreamIDNum != 0)
    {
        dprint(PRN_ERROR,"warning streamIDNum %d != 0 \n",pCtx->StreamIDNum);
        MP4_ClearCurPic(pCtx);
    }
    MP4_Record_SlcSegID(pCtx);

    
    return BitUsed;
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_Vol

        Description: VOL 语法分析
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Mp4_Syntax_Vol(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    BS     local_bs;
    SINT32 BitUsed = 0x0;
    SINT32 i=0;
    SINT32 MaxHorSize = 0;
    SINT32 MaxVerSize = 0;

    if (NULL != s_pstVfmwChan[pCtx->ChanID])
    {
        MaxHorSize = s_pstVfmwChan[pCtx->ChanID]->stSynExtraData.stChanOption.s32MaxWidth;
        MaxVerSize = s_pstVfmwChan[pCtx->ChanID]->stSynExtraData.stChanOption.s32MaxHeight; 
    }
    else
    {
        MaxHorSize = MAX_HOR_SIZE;
        MaxVerSize = MAX_VER_SIZE;
    }

    BsInit(&local_bs, ptr, len);
    pCtx->MP4Syntax.vol_decode_over = 0;
    /* 初始化VOL结构体 */
    memset(&pCtx->MP4Vol,0,sizeof(pCtx->MP4Vol));
    BsSkip(&local_bs, 32);
    
    pCtx->MP4Vol.random_accessible_vol = BsGet(&local_bs, 1);
    pCtx->MP4Vol.video_object_type_indication = BsGet(&local_bs, 8);
   
    pCtx->MP4Vol.is_object_layer_identifier = BsGet(&local_bs, 1);
    if (pCtx->MP4Vol.is_object_layer_identifier)
    {
        pCtx->MP4Vol.video_object_layer_verid = BsGet(&local_bs, 4);
        pCtx->MP4Vol.video_object_layer_priority = BsGet(&local_bs, 3);
    }
    else
    {
        pCtx->MP4Vol.video_object_layer_verid = pCtx->MP4Syntax.syn_vos.visual_object_verid;
    }
    
    pCtx->MP4Vol.aspect_ratio_info = BsGet(&local_bs, 4);
    if (pCtx->MP4Vol.aspect_ratio_info == VIDOBJLAY_AR_EXTPAR)
    {
        pCtx->MP4Vol.par_width = BsGet(&local_bs, 8);
        pCtx->MP4Vol.par_height = BsGet(&local_bs, 8);
    }
    
    pCtx->MP4Vol.vol_control_parameters = BsGet(&local_bs, 1);
    if (pCtx->MP4Vol.vol_control_parameters)
    {
        pCtx->MP4Vol.chroma_format = BsGet(&local_bs, 2);
        if (pCtx->MP4Vol.chroma_format != 0x0001)
        {
            /* 色彩格式错误不解码,返回错误状态和消耗的bit数 */
            pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
            BitUsed = BsPos(&local_bs);
		    dprint(PRN_ERROR, "%s chroma_format = %d, but only support 0x0001\n", __func__, pCtx->MP4Vol.chroma_format);
            return BitUsed;
        }
        pCtx->MP4Vol.low_delay = BsGet(&local_bs, 1);
          
        pCtx->MP4Vol.vbv_parameters = BsGet(&local_bs, 1);
        if (pCtx->MP4Vol.vbv_parameters)
        {
            pCtx->MP4Vol.first_half_bit_rate = BsGet(&local_bs,15);
            MARKER_VOL(local_bs);
            pCtx->MP4Vol.latter_half_bit_rate = BsGet(&local_bs,15);
            MARKER_VOL(local_bs);
            pCtx->MP4Vol.first_half_vbv_buffer_size = BsGet(&local_bs,15);
            MARKER_VOL(local_bs);
            pCtx->MP4Vol.latter_half_vbv_buffer_size = BsGet(&local_bs,3);
                  
            pCtx->MP4Vol.first_half_vbv_occupancy = BsGet(&local_bs,11);
            MARKER_VOL(local_bs);
            pCtx->MP4Vol.latter_half_vbv_occupancy = BsGet(&local_bs,15);
            MARKER_VOL(local_bs);   
        }
    }
    else
    {
        /* 传给VO的参数，format仅支持4：2：0，其余参数预留 */
        pCtx->MP4Vol.chroma_format = 0x0001;
    }
    
    pCtx->MP4Vol.video_object_layer_shape = BsGet(&local_bs, 2);
    if (pCtx->MP4Vol.video_object_layer_shape != VIDOBJLAY_SHAPE_RECTANGULAR)
    {
        /* 仅支持rectangular */
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
		dprint(PRN_ERROR, "%s video_object_layer_shape = %d, but only support VIDOBJLAY_SHAPE_RECTANGULAR\n", __func__, pCtx->MP4Vol.video_object_layer_shape);
        return BitUsed; 
    }
    MARKER_VOL(local_bs);
    
    pCtx->MP4Vol.vop_time_increment_resolution = BsGet(&local_bs, 16);
    if (pCtx->MP4Vol.vop_time_increment_resolution > 0)
    {
        pCtx->MP4Vol.vop_time_incr_bits = MAX(log2bin(pCtx->MP4Vol.vop_time_increment_resolution-1), 1);
    }
    else
    {
        pCtx->MP4Vol.vop_time_incr_bits = 1;
    }
    
    MARKER_VOL(local_bs);
    pCtx->MP4Vol.fixed_vop_rate = BsGet(&local_bs,1);
    if (pCtx->MP4Vol.fixed_vop_rate)
    {
        pCtx->MP4Vol.fixed_vop_time_increment = BsGet(&local_bs,pCtx->MP4Vol.vop_time_incr_bits);
    }
    
    MARKER_VOL(local_bs);
    pCtx->MP4Vol.video_object_layer_width = BsGet(&local_bs, 13);
    MARKER_VOL(local_bs);
    pCtx->MP4Vol.video_object_layer_height = BsGet(&local_bs, 13);
    MARKER_VOL(local_bs);
        
    /* 语法元素容错判断:硬件解析最小图像32*32，规格支持最大图像MAX_HOR_SIZE*MAX_VER_SIZE */
    if ((pCtx->MP4Vol.video_object_layer_width < 32)
    || (pCtx->MP4Vol.video_object_layer_height < 32)
    || ((pCtx->MP4Vol.video_object_layer_width*pCtx->MP4Vol.video_object_layer_height) > (MaxHorSize*MaxVerSize)))
    {
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        BitUsed = BsPos(&local_bs);
        REPORT_SE_ERR(pCtx->ChanID);
		dprint(PRN_ERROR, "%s resolution %dx%d out of range (%dx%d, %dx%d)\n", __func__, pCtx->MP4Vol.video_object_layer_width, pCtx->MP4Vol.video_object_layer_height, 32, 32, MaxHorSize, MaxVerSize);
        return BitUsed;
    }
    
    pCtx->MP4Vol.interlaced = BsGet(&local_bs, 1);
    pCtx->MP4Vol.obmc_disable = BsGet(&local_bs, 1);
    if (!pCtx->MP4Vol.obmc_disable)
    {                  
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        //BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
        //return BitUsed;
    }
    
    pCtx->MP4Vol.sprite_enable = BsGet(&local_bs,(pCtx->MP4Vol.video_object_layer_verid==1 ? 1:2));

    if ((pCtx->MP4Vol.sprite_enable != SPRITE_NONE)&&((g_VdmCharacter&VDM_SUPPORT_GMC) == 0))
    {
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
		dprint(PRN_ERROR, "VDH doesn't support SPRITE_STATIC & SPRITE_GMC\n");
		
        return BitUsed;
    }

    if(pCtx->MP4Vol.sprite_enable != SPRITE_NONE)
    {
		if (pCtx->MP4Vol.sprite_enable == SPRITE_STATIC || pCtx->MP4Vol.sprite_enable == SPRITE_GMC)
		{
		    #if 0
			int low_latency_sprite_enable;
            #endif
			if (pCtx->MP4Vol.sprite_enable != SPRITE_GMC)
			{
                pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
                BitUsed = BsPos(&local_bs);
                REPORT_UNSUPPORT(pCtx->ChanID);
		        dprint(PRN_ERROR, "VDH doesn't support SPRITE_STATIC\n");
				
                return BitUsed;				
			
			    #if 0
				int sprite_width;
				int sprite_height;
				int sprite_left_coord;
				int sprite_top_coord;
				sprite_width = BitstreamGetBits(bs, 13);		/* sprite_width */
				READ_MARKER();
				sprite_height = BitstreamGetBits(bs, 13);	/* sprite_height */
				READ_MARKER();
				sprite_left_coord = BitstreamGetBits(bs, 13);	/* sprite_left_coordinate */
				READ_MARKER();
				sprite_top_coord = BitstreamGetBits(bs, 13);	/* sprite_top_coordinate */
				READ_MARKER();
				#endif
			}
			pCtx->MP4Vol.sprite_warping_points = BsGet(&local_bs, 6);		/* no_of_sprite_warping_points */
			pCtx->MP4Vol.sprite_warping_accuracy = BsGet(&local_bs, 2);		/* sprite_warping_accuracy */
			pCtx->MP4Vol.sprite_brightness_change = BsGet(&local_bs, 1);		/* brightness_change */

			if (pCtx->MP4Vol.sprite_enable != SPRITE_GMC)
			{
			    #if 0
				low_latency_sprite_enable = BsGet(&local_bs, 1);		/* low_latency_sprite_enable */
				#endif
                pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
                BitUsed = BsPos(&local_bs);
                REPORT_UNSUPPORT(pCtx->ChanID);
		        dprint(PRN_ERROR, "VDH doesn't support SPRITE_STATIC\n");
				
                return BitUsed;				
			}
		}
		else
		{
            pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
            BitUsed = BsPos(&local_bs);
            REPORT_UNSUPPORT(pCtx->ChanID);
		    dprint(PRN_ERROR, "Unknown sprite_enable\n");
			
            return BitUsed;
		}
    }	

	
    pCtx->MP4Vol.not_8_bit = BsGet(&local_bs, 1);
    if (pCtx->MP4Vol.not_8_bit)
    {
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
		dprint(PRN_ERROR, "ERROR: not_8_bit !=0\n");
		
        return BitUsed;
    }

    /* 解析量化表 */
    pCtx->MP4Vol.quant_type = BsGet(&local_bs,1);
    if (pCtx->MP4Vol.quant_type)
    {
        pCtx->MP4Vol.load_intra_quant_mat = BsGet(&local_bs, 1);
        if (pCtx->MP4Vol.load_intra_quant_mat)
        {
            Bs_Get_Matrix(&local_bs,&pCtx->MP4Vol.intra_quant_mat[0]); 
        }
        else
        {
            for (i = 0;i < 64;i++)
            {
                pCtx->MP4Vol.intra_quant_mat[i] = default_intra_matrix[i];
            }
        }
        
        pCtx->MP4Vol.load_nonintra_quant_mat = BsGet(&local_bs, 1);
        if (pCtx->MP4Vol.load_nonintra_quant_mat)
        {
            Bs_Get_Matrix(&local_bs,&pCtx->MP4Vol.nonintra_quant_mat[0]);
        }
        else
        {
            for (i=0; i<64; i++)
            {
                pCtx->MP4Vol.nonintra_quant_mat[i] = default_inter_matrix[i];
            }
        }      
    }
    
    if (pCtx->MP4Vol.video_object_layer_verid != 1)
    {
        pCtx->MP4Vol.quarter_sample = BsGet(&local_bs, 1); 
    }
    else
    {
        pCtx->MP4Vol.quarter_sample = 0;
    }
    
    pCtx->MP4Vol.complexity_estimation_disable = BsGet(&local_bs, 1);
    if (!pCtx->MP4Vol.complexity_estimation_disable)
    {
        dprint(PRN_ERROR,"not support no complexity_estimation_disable\n");
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
        return BitUsed;
    }
    
    pCtx->MP4Vol.resync_marker_disable = BsGet(&local_bs, 1);
    pCtx->MP4Vol.data_partitioned = BsGet(&local_bs, 1);
    if (pCtx->MP4Vol.data_partitioned)
    {
        dprint(PRN_ERROR,"not support data_partitioned\n");
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
        return BitUsed;
    }
    
    if (pCtx->MP4Vol.video_object_layer_verid != 1)
    {
        pCtx->MP4Vol.newpred_enable = BsGet(&local_bs, 1);
        if (pCtx->MP4Vol.newpred_enable)
        {
            dprint(PRN_ERROR,"not support newpred_enable\n");
            pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
            BitUsed = BsPos(&local_bs);
            REPORT_UNSUPPORT(pCtx->ChanID);
            return BitUsed;
        }

        pCtx->MP4Vol.reduced_resolution_vop_enable = BsGet(&local_bs,1);
        if (pCtx->MP4Vol.reduced_resolution_vop_enable)
        {
            dprint(PRN_ERROR,"not support reduced_resolution_vop_eanble\n");
            pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
            BitUsed = BsPos(&local_bs);
            REPORT_UNSUPPORT(pCtx->ChanID);
            return BitUsed;
        }
    }
    else
    {
        pCtx->MP4Vol.newpred_enable=0;
        pCtx->MP4Vol.reduced_resolution_vop_enable=0;
    }
    
    pCtx->MP4Vol.scalability=BsGet(&local_bs,1);
    if (pCtx->MP4Vol.scalability)
    {
        dprint(PRN_ERROR,"not support scalability\n");
        pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLERR;
        BitUsed = BsPos(&local_bs);
        REPORT_UNSUPPORT(pCtx->ChanID);
        return BitUsed;
    }
   
    /* 返回状态和消耗码流bit数 */
    pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLOK;
    pCtx->MP4Syntax.vol_decode_over = 1;

    /* 备份VOL信息 */
    pCtx->MP4SyntaxState.last_vol_decode_right = SYN_VOLOK;
    memcpy(&(pCtx->MP4VolLastBack), &(pCtx->MP4Vol), sizeof(MP4_VOL));
                
    BitUsed = BsPos(&local_bs);

    return BitUsed;
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_Vos

        Description: VOS语法分析
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Mp4_Syntax_Vos(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    BS     local_bs;
    SINT32 BitUsed = 0x0;

    BsInit(&local_bs, ptr, len);
    pCtx->MP4Syntax.syn_vos.profile_and_level_indication = 0;

    BsSkip(&local_bs, 32);
    pCtx->MP4Vos.profile_and_level_indication = BsGet(&local_bs, 8);
    if ((SP_LEVEL1  == pCtx->MP4Vos.profile_and_level_indication)
     ||(SP_LEVEL2  == pCtx->MP4Vos.profile_and_level_indication)
     ||(SP_LEVEL3  == pCtx->MP4Vos.profile_and_level_indication)
     ||(SP_LEVEL0  == pCtx->MP4Vos.profile_and_level_indication)
     ||(ASP_LEVEL0 == pCtx->MP4Vos.profile_and_level_indication)
     ||(ASP_LEVEL1 == pCtx->MP4Vos.profile_and_level_indication)
     ||(ASP_LEVEL2 == pCtx->MP4Vos.profile_and_level_indication)
     ||(ASP_LEVEL3 == pCtx->MP4Vos.profile_and_level_indication)
     ||(ASP_LEVEL4 == pCtx->MP4Vos.profile_and_level_indication)
     ||(ASP_LEVEL5 == pCtx->MP4Vos.profile_and_level_indication))
    {
        /* VOS头解析正确 */
        pCtx->MP4SyntaxState.vos_decode_right = SYN_VOSOK;
        pCtx->MP4Syntax.syn_vos.profile_and_level_indication = pCtx->MP4Vos.profile_and_level_indication;
    }
    else if (0 == pCtx->MP4Vos.profile_and_level_indication)
    {
        dprint(PRN_ERROR, "warning! profile_and_level_indication=%#x, maybe HD pic...\n", pCtx->MP4Vos.profile_and_level_indication);
        /* VOS头解析正确 */
        pCtx->MP4SyntaxState.vos_decode_right = SYN_VOSOK;
        pCtx->MP4Syntax.syn_vos.profile_and_level_indication = pCtx->MP4Vos.profile_and_level_indication;
    }
    else
    {
        pCtx->MP4SyntaxState.vos_decode_right = SYN_VOSERR;       
        REPORT_UNSUPPORT(pCtx->ChanID);
    }
    BitUsed = BsPos(&local_bs);

    return BitUsed;
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Syntax_Parse

        Description: 语法分析部分
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
UINT32 Mp4_Syntax_Parse(MP4_CTX_S *pCtx, UINT8* pCode, SINT32 CodeLen)
{
    SINT8  bNeedPartition = 0;
    UINT8* ptr = pCode;
    /* CodeLen 为字节数 */
    SINT32 len = CodeLen;
    /* 设置起始码字初始值为0x0 */
    UINT32 StartCode = 0x0;
    UINT32 BitUsed = 0x0;
    UINT32 end_code1, end_code2;
    BS     local_bs, bs_tmp;
//    SINT32 ByteOffset=0;
    MP4_SCD_UPMSG   *pScdUpMsg = &(pCtx->ScdUpMsg);
    memset(&local_bs,0,sizeof(BS));
    
    BsInit(&local_bs, ptr, len);
    StartCode = BsShow(&local_bs, 32);
    pCtx->IsWaitToDecFlag = 0;    

    //while (1)
    {
		if (HISI_STREAM_END_CODE == StartCode)
		{
			memcpy(&bs_tmp, &local_bs, sizeof(BS));

			BsSkip(&bs_tmp, 32);

			end_code1 = (UINT32)BsGet(&bs_tmp, 32);
			end_code2 = (UINT32)BsGet(&bs_tmp, 32);
			
			if (HISI_STREAM_END_CODE1 == end_code1 && HISI_STREAM_END_CODE2 == end_code2)
			{
    			pCtx->IsStreamEndFlag = 1;              // last frame
                REPORT_STREAM_END_SYNTAX(pCtx->ChanID);

    			if (MP4_FOUND_VOPHDR == (pCtx->PicIntegrality & MP4_FOUND_VOPHDR) ||
                    MP4_FOUND_NVOP == (pCtx->PicIntegrality & MP4_FOUND_NVOP))
    			{
                    pCtx->PicIntegrality |= MP4_FOUND_NEXTVOPHDR;
                    pCtx->IsWaitToDecFlag = 1;
                }
                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));   

                return 0;
			}
		}
		
        /* 判断是短头是非短头码流 */
        MP4_Check_StreamType(pCtx, &StartCode);
        
        if(0 == pScdUpMsg->SliceFlag)
        {
//            pCtx->MP4Syntax.decode_syntax_OK = 0;

            /* 判断帧的完整性，即是收到了下一个vop头 */
            if(MP4_FOUND_VOPHDR == (pCtx->PicIntegrality & MP4_FOUND_VOPHDR) ||
               MP4_FOUND_NVOP == (pCtx->PicIntegrality & MP4_FOUND_NVOP))
            {
                /* 已收集完一帧的信息 */
                pCtx->PicIntegrality |= MP4_FOUND_NEXTVOPHDR;
                pCtx->IsWaitToDecFlag = 1;
                
                return 0;
            }

            if (NO_START_CODE == StartCode)
            {
                dprint(PRN_CTRL, "Not find start code \n");
                /* NO_START_CODE 表明没有找到起始码,返回长度以bit为单位 */
                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
                return (( ptr - pCode )* 8);
            }
            else if (VISOBJSEQ_START_CODE == StartCode)
            {
                /* VOS */
                dprint(PRN_CTRL, "VOS beginning ~ !\n");
                pCtx->UserID=0;
                BitUsed = Mp4_Syntax_Vos(pCtx, ptr, len);            
//                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));
                MP4_Record_HeadPacketInfo(pCtx, StartCode);
            }
            else if (VISOBJ_START_CODE == StartCode)
            {
                /* VO */
                dprint(PRN_CTRL, "VO beginning ~ !\n");
                pCtx->UserID=1;
                BitUsed = Mp4_Syntax_Vo(pCtx, ptr, len);
//                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
                MP4_Record_HeadPacketInfo(pCtx, StartCode);
            }
            else if (VIDOBJLAY_START_CODE == (StartCode & ~VIDOBJLAY_START_CODE_MASK))
            {
                /* VOL */
                dprint(PRN_CTRL, "VOL beginning ~ !\n");
                pCtx->UserID=2;
                BitUsed = Mp4_Syntax_Vol(pCtx, ptr, len);
//                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
                MP4_Record_HeadPacketInfo(pCtx, StartCode);
                /* 容错处理 */
                if((SYN_VOLOK != pCtx->MP4SyntaxState.vol_decode_right) && 
                   (SYN_VOLOK == pCtx->MP4SyntaxState.last_vol_decode_right))
                {
                    memcpy(&(pCtx->MP4Vol), &(pCtx->MP4VolLastBack), sizeof(MP4_VOL));
                    pCtx->MP4SyntaxState.vol_decode_right = SYN_VOLOK;
                    pCtx->MP4Syntax.vol_decode_over = 1;
                }
            }
            else if (GRPOFVOP_START_CODE == StartCode)
            {
                /* GOP */
                dprint(PRN_CTRL, "GOP beginning ~ !\n");
                pCtx->UserID=3;
                BitUsed = Mp4_Syntax_Gop(pCtx, ptr, len);
//                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
                MP4_Record_HeadPacketInfo(pCtx, StartCode);
            }
            else if (VOP_START_CODE == StartCode)
            {
                /* VOP */
                dprint(PRN_CTRL, "VOP beginning ~ !\n");

				if( len == 4 )
				{
                    MP4_Record_HeadPacketInfo(pCtx, StartCode);
				}
				else
				{
    	            BitUsed = Mp4_Syntax_Vop(pCtx, ptr, len);
	                if(MP4_FOUND_VOPHDR != (pCtx->PicIntegrality & MP4_FOUND_VOPHDR))
	                {
	                    MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
	                }
	                else
	                {
	                    MP4_Record_HeadPacketInfo(pCtx, StartCode);
	                }

				}
                dprint(PRN_STREAM, "BitUsed=%d\n",BitUsed);
            }
            else if (SHORT_HEADER == StartCode)
            {
                /* short_header起始码标识0xc4在NextStartCode()中得到 */
                dprint(PRN_CTRL, "SHVOP beginning ~ !\n");
                BitUsed = Mp4_Syntax_ShortHeader(pCtx, ptr, len);
                if(MP4_FOUND_VOPHDR != (pCtx->PicIntegrality & MP4_FOUND_VOPHDR))
                {
                    MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
                }
                else
                {
                    MP4_Record_HeadPacketInfo(pCtx, StartCode);
                }
            }
            else if (USERDATA_START_CODE == StartCode)
            {
                /* USERDATA */
                dprint(PRN_CTRL, "USERDATA beginning ~ !\n");
                BitUsed = Mp4_Syntax_UserData(pCtx, ptr, len);        
                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
            }
            else if (HISI_END_OF_FRAME == StartCode)
            {
                /* 为了统计已经解码的帧数 */
                REPORT_MEET_NEWFRM(pCtx->ChanID);
                
                ptr += 4;
                len -= 4;
                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
				if(MP4_FOUND_VOPHDR == (pCtx->PicIntegrality & MP4_FOUND_VOPHDR))
				{
					/* 已收集完一帧的信息,但这包不需要重新送进来解码 */
					pCtx->PicIntegrality |= MP4_FOUND_HISIHDR;
				}

               // continue;
            }
            else
            {
                /* 遇到未知同步头，跳过，找下一个同步头 */
                ptr += 4;
                len -= 4;
                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));                
                //continue;
            }
        }
        else
        {
            BitUsed = MP4_Dec_Slice(pCtx, ptr, len);            
        }

        if (1 == pCtx->SeekReset)
        {		
            if (pCtx->MP4Vol.video_object_layer_width > 0 && pCtx->MP4Vol.video_object_layer_height > 0)
            {
            if ( MPEG4_OK != Frame_Init(pCtx, pCtx->MP4Vol.video_object_layer_width, pCtx->MP4Vol.video_object_layer_height) )
            {
                dprint(PRN_FATAL, "MPEG4 Frame_Init return err 3!\n");
                 }
            }
            pCtx->SeekReset = 0;
        }
        
        if (BitUsed <= (len * 8))
        {
            /* 码流没有越界 */
            /* 帧的完备性判断条件已发生变化,对应这里同样需要发生变化,只有vop才能进去 */
            if (((VOP_START_CODE == StartCode) || (SHORT_HEADER == StartCode)) 
                && ((MP4_FOUND_VOPHDR == (pCtx->PicIntegrality & MP4_FOUND_VOPHDR)
                || (MP4_FOUND_NVOP == (pCtx->PicIntegrality & MP4_FOUND_NVOP)))))/*pCtx->MP4Syntax.decode_syntax_OK*/
            {
                if (pCtx->MP4Syntax.is_short_header==NON_SHORT_HEADER_ID)
                {
                    if (pCtx->MP4Vop.vop_coding_type != B_VOP)
                    {
                        pCtx->MP4Syntax.last_time_base = pCtx->MP4Syntax.time_base;
                        pCtx->MP4Syntax.time_base += pCtx->MP4Syntax.time_incr;
                        pCtx->MP4Syntax.time = pCtx->MP4Syntax.time_base*pCtx->MP4Vol.vop_time_increment_resolution + pCtx->MP4Syntax.time_increment;
                        pCtx->MP4Syntax.time_pp = (pCtx->MP4Syntax.time - pCtx->MP4Syntax.last_non_b_time);
                        pCtx->MP4Syntax.last_non_b_time = pCtx->MP4Syntax.time;
                    }
                    else
                    {
                        pCtx->MP4Syntax.time = (pCtx->MP4Syntax.last_time_base + pCtx->MP4Syntax.time_incr)*pCtx->MP4Vol.vop_time_increment_resolution + pCtx->MP4Syntax.time_increment;
                        pCtx->MP4Syntax.time_bp = pCtx->MP4Syntax.time_pp - (pCtx->MP4Syntax.last_non_b_time - pCtx->MP4Syntax.time);
                    }
                }
                else
                {
                    //shortheader 遇到图像大小切换，更新帧存信息
                    pCtx->NewPicWidth = pCtx->MP4Syntax.image_width;
                    pCtx->NewPicHeight = pCtx->MP4Syntax.image_height;
                
                    /* 信息上报 */    
                    if ((((pCtx->NewPicWidth!=0)&&(pCtx->OldPicWidth !=pCtx->NewPicWidth))||((pCtx->NewPicHeight!=0)&&(pCtx->OldPicHeight!=pCtx->NewPicHeight))) ||
                        (pCtx->FspPartitionOK != 1))
                    {
					    bNeedPartition = 1;
					}
					else
					{
					    bNeedPartition = 0;
					}

                    /* 信息上报 */
                    if (((pCtx->NewPicWidth!=0)&&(pCtx->OldPicWidth !=pCtx->NewPicWidth))||((pCtx->NewPicHeight!=0)&&(pCtx->OldPicHeight!=pCtx->NewPicHeight)))
                    {
					    REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pCtx->OldPicWidth, pCtx->OldPicHeight, pCtx->NewPicWidth, pCtx->NewPicHeight);
					}
					
					if (1 == bNeedPartition)
					{
                        MP4_CLEARREFFLAG;
                        MP4_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过 				
                		FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
                    
                	    if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
                	    {
                	        if (pCtx->FspPartitionOK == 0)
                	        {
                	            ResetVoQueue(&pCtx->ImageQue);
                	        }
                	    }
                        else
                        {
                            ResetVoQueue(&pCtx->ImageQue); 
                        }
                    
                        if ( MPEG4_OK != Frame_Init(pCtx, pCtx->NewPicWidth, pCtx->NewPicHeight) )
                        {
                            dprint(PRN_FATAL, "MPEG4 Frame_Init return err 1!\n");
                        }
                    }

                    pCtx->OldPicWidth = pCtx->NewPicWidth;
                    pCtx->OldPicHeight = pCtx->NewPicHeight;
                }

                /* VOP头正常解码或ShortHeader头正常解码 */
                memcpy(&pCtx->MP4Syntax.syn_vop, &pCtx->MP4Vop, sizeof(MP4_VOP)); 
                                
                dprint(PRN_CTRL, "vop right\n");

                pCtx->ImgCntOfSeq++;
                return ( (ptr-pCode)*8 + BitUsed );
            }
            else if (SYN_VOLOK == pCtx->MP4SyntaxState.vol_decode_right)
            {
                pCtx->SeqCnt++;
                pCtx->ImgCntOfSeq = 0;
                memcpy(&pCtx->MP4Syntax.syn_vol, &pCtx->MP4Vol, sizeof(MP4_VOL));
				
                if ((pCtx->MP4Syntax.image_height != pCtx->MP4Vol.video_object_layer_height ||
                  pCtx->MP4Syntax.image_width != pCtx->MP4Vol.video_object_layer_width) || 
                  (pCtx->FspPartitionOK != 1))
                {
				    bNeedPartition = 1;
				}
				else
				{
				    bNeedPartition = 0;
				}
				
				if (pCtx->MP4Syntax.image_height != pCtx->MP4Vol.video_object_layer_height ||
                    pCtx->MP4Syntax.image_width != pCtx->MP4Vol.video_object_layer_width)
				{
                    //frame size change
                    REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pCtx->MP4Syntax.image_width, pCtx->MP4Syntax.image_height,
                                          pCtx->MP4Vol.video_object_layer_width, pCtx->MP4Vol.video_object_layer_height);

                    pCtx->MP4Syntax.image_height = pCtx->MP4Vol.video_object_layer_height;
                    pCtx->MP4Syntax.image_width  = pCtx->MP4Vol.video_object_layer_width;
                }
                    
				if (1 == bNeedPartition)
				{
				    MP4_CLEARREFFLAG;
                    MP4_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过 				
                	FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
                    
                	if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
                	{
                	    if (pCtx->FspPartitionOK == 0)
                	    {
                	        ResetVoQueue(&pCtx->ImageQue);
                	    }
                	}
                    else
                    {
                        ResetVoQueue(&pCtx->ImageQue); 
                    }
					
                    if ( MPEG4_OK != Frame_Init(pCtx, pCtx->MP4Syntax.image_width, pCtx->MP4Syntax.image_height) )
                    {
                        dprint(PRN_FATAL, "MPEG4 Frame_Init return err 2!\n");
                    }
                }

                pCtx->OldPicWidth = pCtx->MP4Syntax.image_height;
                pCtx->OldPicHeight = pCtx->MP4Syntax.image_width;
    
                pCtx->MP4Syntax.image_height = pCtx->MP4Vol.video_object_layer_height;
                pCtx->MP4Syntax.image_width = pCtx->MP4Vol.video_object_layer_width;
                /* 修正ptr，解码后续语法 */
                ptr += ( BitUsed + 7 ) / 8;
                /* 记录还剩多少字节 */
                len -= ( BitUsed + 7 ) / 8;
                pCtx->MP4SyntaxState.vol_decode_right = 0;
            }
            else
            {
                /* 修正ptr，解码后续语法 */
                ptr += ( BitUsed + 7 ) / 8;
                /* 记录还剩多少字节 */
                len -= ( BitUsed + 7 ) / 8;
            }
        }
        else
        {
            dprint(PRN_CTRL, "bits over boundary\n");
            /* 码流越界 */
            pCtx->PicIntegrality &= ~MP4_PIC_OK;
            //pCtx->MP4Syntax.decode_syntax_OK = 0;
            return ( (ptr-pCode) * 8 );
        }
    }

    return BitUsed;
}


/*------------------------------------------------------------------------------

        Function name: Frame_Init

        Description: 帧空间初始化
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Frame_Init(MP4_CTX_S *pCtx, UINT32 PicWidth, UINT32 PicHeight)
{
    static VDMHAL_MEM_ARRANGE_S MemArrange;
    FSP_INST_CFG_S  FspInstCfg;
    SINT32 DecFsNum, DispFsNum, PmvNum;

    if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
    {
        if (PicWidth > pCtx->pstExtraData->stChanOption.s32MaxWidth || PicHeight > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "actual frame size(%dx%d) exeed max config(%dx%d)\n", PicWidth, PicHeight,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);
			
			//pCtx->FspPartitionOK = 0;
			return MPEG4_FAIL;
		}
		
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        PicWidth  = pCtx->pstExtraData->stChanOption.s32MaxWidth;
        PicHeight = pCtx->pstExtraData->stChanOption.s32MaxHeight;
		
        if (pCtx->FspPartitionOK == 1)
        {
            return MPEG4_OK;
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
		DecFsNum = 3;
		PmvNum = 2;
		DispFsNum = 5;		
	}
	else
	{
        if (PicWidth > pCtx->pstExtraData->stChanOption.s32MaxWidth || PicHeight > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "actual frame size(%dx%d) exeed max config(%dx%d)\n", PicWidth, PicHeight,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);
			
			//pCtx->FspPartitionOK = 0;
			return MPEG4_FAIL;
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
	if(1 != pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn)
    {
        if ( VDMHAL_OK != VDMHAL_ArrangeMem(pCtx->pstExtraData->s32SyntaxMemAddr, pCtx->pstExtraData->s32SyntaxMemSize, 
            PicWidth, PicHeight, 2, 40, pCtx->ChanID, &MemArrange) )
        {
            dprint(PRN_FATAL, "MPEG4 Frame_Init return err!\n");
            return MPEG4_FAIL;
        }
        if ( MemArrange.ValidPMVNum < 2 || MemArrange.ValidFrameNum < 3 )
        {
            dprint(PRN_FATAL, "MPEG4 Frame_Init PmvNum=%d, FrameNum=%d, error!\n", MemArrange.ValidPMVNum, MemArrange.ValidFrameNum );
            return MPEG4_FAIL;
        }

        /*帧、消息池等分配*/
        pCtx->VdmMemAllot.frame_phy_addr = MemArrange.FrameAddr[0];
        pCtx->VdmMemAllot.frame_vir_addr = (UINT8 *)MEM_Phy2Vir(MemArrange.FrameAddr[0]);
	}

    /* 重构帧信息初始化 */
    memset(&FspInstCfg, 0, sizeof(FSP_INST_CFG_S));
    FspInstCfg.s32DecFsWidth       = PicWidth;
    FspInstCfg.s32DecFsHeight      = PicHeight;
    FspInstCfg.s32DispFsWidth      = PicWidth;
    FspInstCfg.s32DispFsHeight     = PicHeight;
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
            pCtx->FspPartitionOK = 0;
            // 分割帧存失败，返回
            return MPEG4_FAIL;
        }
    }
	else
	{
	    dprint(PRN_FATAL, "ERROR: FSP_ConfigInstance fail!\n");
	    return MPEG4_FAIL;
	}

	pCtx->FspPartitionOK = 1;

    return MPEG4_OK;
}


/*------------------------------------------------------------------------------

        Function name: Bits_Init

        Description: 码流管理初始化
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
static VOID Bits_Init(BITS_OBJ *pBitsObj, const DEC_STREAM_PACKET_S  *ptr_strm_para)
{
    pBitsObj->phy_addr = ptr_strm_para->StreamPack[0].PhyAddr;
    pBitsObj->vir_addr = ptr_strm_para->StreamPack[0].VirAddr;
    pBitsObj->len = ptr_strm_para->StreamPack[0].LenInByte;
    pBitsObj->offset = 0;

    return;
}


/*------------------------------------------------------------------------------

        Function name: Bits_Flush

        Description: 码流位置更新
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
static VOID Bits_Flush(BITS_OBJ *pBitsObj, UINT32 bits )
{
    UINT32 bits_effect;
    UINT32 byte_num;   
    bits_effect=bits;
    byte_num=bits_effect>>3;
      
    pBitsObj->vir_addr+=byte_num;
    pBitsObj->phy_addr+=byte_num;
    pBitsObj->len-=byte_num;
    pBitsObj->offset=bits_effect&7;

    return;
}


/*------------------------------------------------------------------------------

        Function name: Vdm_Mem_Move

        Description: 利用硬件进行数据搬移.
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VOID Vdm_Mem_Move(MP4_CTX_S * pCtx, FSP_LOGIC_FS_S * pCur, UADDR dst, UADDR dst_2d, UADDR src, UINT32 ImgWidth, UINT32 ImgHeight)
{    
    dprint(PRN_CTRL, "NVOP VDM copy process................\n");

    //用Repair方式拷贝NVOP图
    pCtx->Mp4DecParam.CurPicPhyAddr = dst;
	pCtx->Mp4DecParam.DispFramePhyAddr = dst_2d;
    pCtx->Mp4DecParam.CurPmvPhyAddr = pCur->PmvAddr;
    pCtx->Mp4DecParam.FwdRefPicPhyAddr = src;
    pCtx->Mp4DecParam.PicWidthInMb = (ImgWidth+15)/16;
    pCtx->Mp4DecParam.PicHeightInMb = (ImgHeight+15)/16;
    pCtx->Mp4DecParam.VahbStride = pCur->pstDispOutFs->Stride;
    pCtx->Mp4DecParam.Compress_en = pCtx->pstExtraData->s32Compress_en;

    /*
    pCtx->Mp4DecParam.IsNvopCopy = 1;
    pCtx->pMp4DecParam = &pCtx->Mp4DecParam;
    */
    pCtx->pMp4DecParam = &pCtx->Mp4DecParam;

    if (1 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((NULL != pCtx->pMp4DecParam))
        {
            pCtx->pMp4DecParam = NULL;
            FSP_SetDisplay(pCtx->ChanID, pCtx->CurFsID, 0);
            MP4_ClearCurPic(pCtx);
            return;
        }
    }
    else if (2 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((pCtx->pstExtraData->stDisParams.s32DisNums > 0) && (NULL != pCtx->pMp4DecParam))
        {
            pCtx->pMp4DecParam = NULL;
            FSP_SetDisplay(pCtx->ChanID, pCtx->CurFsID, 0);
            pCtx->pstExtraData->stDisParams.s32DisNums--;
            MP4_ClearCurPic(pCtx);
            return;
        }
    }
 
    pCtx->Mp4DecParam.IsNvopCopy = 1;

    return ;
}


/*------------------------------------------------------------------------------

        Function name: Mp4_RecordFrameAtr

        Description: 帧特性设置
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/

#define DAR10_16_9  ((16<<10)/9)
#define DAR10_4_3   ((4<<10)/3)

VOID Mp4_RecordFrameAtr(MP4_CTX_S *pCtx, UINT32 id)
{
    UINT32 aspect_ratio;
    UINT32 j;
    IMAGE  *pImg;

    SINT32 true_dar, sar_width, sar_height;

    sar_width = sar_height = 1;
	
    if (pCtx->MP4Syntax.syn_vol.aspect_ratio_info==15)
    {
        if (pCtx->MP4Syntax.syn_vol.aspect_ratio_info==15)
        {
            sar_width = pCtx->MP4Syntax.syn_vol.par_width;
            sar_height = pCtx->MP4Syntax.syn_vol.par_height;
        }
        if(sar_width==0 || sar_height==0)
        {
            aspect_ratio = DAR_UNKNOWN;
        }
        else
        {
            if ((pCtx->MP4Syntax.syn_vol.video_object_layer_height*sar_height) == 0)
            {
                aspect_ratio = DAR_UNKNOWN;
            }
            else
            {
                true_dar = (pCtx->MP4Syntax.syn_vol.video_object_layer_width*(sar_width<<10)) / (pCtx->MP4Syntax.syn_vol.video_object_layer_height*sar_height);
                aspect_ratio = (ABS(true_dar-DAR10_4_3) < ABS(true_dar-DAR10_16_9))? DAR_4_3: DAR_16_9;
            }
        }
    }
    else if ((pCtx->MP4Syntax.syn_vol.aspect_ratio_info==2)||(pCtx->MP4Syntax.syn_vol.aspect_ratio_info==3))
    {
        aspect_ratio=DAR_4_3;
    }
    else if ((pCtx->MP4Syntax.syn_vol.aspect_ratio_info==4)||(pCtx->MP4Syntax.syn_vol.aspect_ratio_info==5))
    {
        aspect_ratio=DAR_16_9;
    }
    else if (pCtx->MP4Syntax.syn_vol.aspect_ratio_info==1)
    {
    	aspect_ratio=DAR_IMG_SIZE;
    }
    else
    {
        aspect_ratio=DAR_UNKNOWN;
    }

    pImg = FSP_GetFsImagePtr(pCtx->ChanID, id);
    if (NULL == pImg)
    {
        return;
    }
	
    pImg->image_width=pCtx->MP4Syntax.image_width;
    pImg->image_height=pCtx->MP4Syntax.image_height; 

	SetAspectRatio(pImg,(VDEC_DAR_E)aspect_ratio);

	//liucan mark it.
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

    /*sequence display extension 和 picture display extension 属于studio profile*/
    pImg->disp_width    = pCtx->MP4Syntax.image_width;
    pImg->disp_height   = pCtx->MP4Syntax.image_height; 
    pImg->disp_center_x = pCtx->MP4Syntax.image_width/2;
    pImg->disp_center_y = pCtx->MP4Syntax.image_height/2;
    
    pImg->seq_img_cnt   = pCtx->ImgCntOfSeq;
    pImg->seq_cnt       = pCtx->SeqCnt;
    pImg->format        = (pCtx->MP4Syntax.syn_vop.vop_coding_type&3)
                          |((pCtx->MP4Syntax.syn_vos.video_format&7)<<5)
                          |((pCtx->MP4Syntax.syn_vol.interlaced & 1)<<8)  
                          |(3<<10)
                          |(pCtx->MP4Syntax.syn_vop.top_field_first<<12)
                          |(aspect_ratio<<14);
	
    pImg->top_fld_type    = pCtx->MP4Syntax.syn_vop.vop_coding_type&3;
    pImg->bottom_fld_type = pCtx->MP4Syntax.syn_vop.vop_coding_type&3;

    pImg->is_fld_save = 0;
    
    for (j=0; j<4; j++)
    {
        pImg->p_usrdat[j]=pCtx->UsrData[j];
    }

    pImg->PTS = pCtx->pstExtraData->pts;
    pImg->Usertag = pCtx->pstExtraData->Usertag;
    pImg->DispTime = pCtx->pstExtraData->DispTime;
    pImg->DispEnableFlag = pCtx->pstExtraData->DispEnableFlag;
    pImg->DispFrameDistance = pCtx->pstExtraData->DispFrameDistance;
    pImg->DistanceBeforeFirstFrame = pCtx->pstExtraData->DistanceBeforeFirstFrame;
    pImg->GopNum = pCtx->pstExtraData->GopNum;

    pCtx->pstExtraData->pts = (UINT64)(-1);
	dprint(PRN_PTS,"dec_pts: %lld Usertag: %lld\n",pImg->PTS, pImg->Usertag);	
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Frame_Atr

        Description: 帧空间申请及特性设置
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 Mp4_Frame_Atr(MP4_CTX_S *pCtx)
{
    pCtx->CurCodingType = pCtx->MP4Syntax.syn_vop.vop_coding_type;
	if (pCtx->CurCodingType == N_VOP)
	{
        g_VfmwChanStat[pCtx->ChanID].u32SkipFind++;
	}
	
    pCtx->CurFsID = FSP_NewLogicFs(pCtx->ChanID, 1);
    if (pCtx->CurFsID < 0 || pCtx->FspPartitionOK == 0)
    {
        /* 获取帧存失败 */
        dprint(PRN_FATAL,"get frame store fail!\n");
        MP4_CLEARREFFLAG;
        MP4_CLEARREFNUM;		
		FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		
        return 0;
    }

    Mp4_RecordFrameAtr(pCtx, pCtx->CurFsID);

    pCtx->ErrorLevel = 0;

    return FRAME_REQ_SUCCESS ;              
}


/*------------------------------------------------------------------------------

        Function name: Mp4_Set_DecPar

        Description: 解码器配置到结构体中
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VOID Mp4_Set_DecPar(MP4_CTX_S *pCtx, UINT32 slot, const DEC_STREAM_PACKET_S *ptr_strm_para)
{
    SINT32 i, T1Len; 
    MP4_SYNTAX *pMP4Syntax;
    BITS_OBJ *pBitsObj;
    MP4_DEC_PARAM_S *pMp4DecParam = NULL;
    FSP_LOGIC_FS_S *pCur, *pBwd, *pFwd;
    MP4_GMC_DATA gmc;
 
	memset(&gmc, 0, sizeof(MP4_GMC_DATA));
    pMp4DecParam = &pCtx->Mp4DecParam;
    pMP4Syntax = &pCtx->MP4Syntax;
    pBitsObj = &pCtx->BitsObj;
    
    //StreamSegID[5];
    //这个还有问题
    if (1 == ptr_strm_para->StreamPack[0].IsLastSeg)
    {
        pMp4DecParam->StreamBaseAddr = pBitsObj->phy_addr;
        pMp4DecParam->StreamPhyAddr[0] = pBitsObj->phy_addr & 0xFFFFFFFC;
        pMp4DecParam->StreamVirAddr[0] = pBitsObj->vir_addr;
        pMp4DecParam->StreamBitOffset[0] = ((pBitsObj->phy_addr&3)<<3) + pBitsObj->offset;
        if (SHORT_HEADER_ID == pMP4Syntax->is_short_header)
        {
            T1Len = 0;
        }
        else
        {
            //z56361, 20110622: 有些mpeg4拖尾填充有问题，去拖尾反而导致误伤有效码流，所以不去了
            T1Len = 0; //GetTrailingOneLen(pBitsObj->vir_addr, pBitsObj->len); 
        }
        pMp4DecParam->StreamLength[0] = (pBitsObj->len<<3) - pBitsObj->offset - T1Len;
        pMp4DecParam->StreamFirstIsLastFlag = 1;

        pMp4DecParam->StreamPhyAddr[1] = 0;
        pMp4DecParam->StreamBitOffset[1] = 0;
        pMp4DecParam->StreamLength[1] = 0;

    }
    else
    {
        pMp4DecParam->StreamBaseAddr = ptr_strm_para->StreamPack[1].PhyAddr & 0xFFFFFFFC; 
        pMp4DecParam->StreamPhyAddr[0] = pBitsObj->phy_addr;
        pMp4DecParam->StreamVirAddr[0] = pBitsObj->vir_addr;  //这个需要检查一下
        pMp4DecParam->StreamBitOffset[0] = ((pBitsObj->phy_addr&3)<<3) + pBitsObj->offset; 
        pMp4DecParam->StreamLength[0] = (pBitsObj->len << 3)-pBitsObj->offset;

        pMp4DecParam->StreamPhyAddr[1] = ptr_strm_para->StreamPack[1].PhyAddr;
        pMp4DecParam->StreamVirAddr[1] = ptr_strm_para->StreamPack[1].VirAddr;  //这个需要检查一下
        pMp4DecParam->StreamBitOffset[1] = ((ptr_strm_para->StreamPack[1].PhyAddr&3)<<3);
        if (SHORT_HEADER_ID == pMP4Syntax->is_short_header)
        {
            T1Len = 0;
        }
        else
        {
            //z56361, 20110728: 有些mpeg4拖尾填充有问题，去拖尾反而导致误伤有效码流，所以不去了
            T1Len = 0; //GetTrailingOneLen(ptr_strm_para->StreamPack[1].VirAddr, ptr_strm_para->StreamPack[1].LenInByte);
        }
        pMp4DecParam->StreamLength[1] = (ptr_strm_para->StreamPack[1].LenInByte << 3) - T1Len;

        pMp4DecParam->StreamFirstIsLastFlag = 0;
    }    


    pMp4DecParam->PicWidthInMb = ( pMP4Syntax->image_width+ 15 ) >> 4;
    pMp4DecParam->PicHeightInMb = ( pMP4Syntax->image_height+ 15 ) >> 4;
    pMp4DecParam->PicCodingType = pMP4Syntax->syn_vop.vop_coding_type;
    pMp4DecParam->PicQuantType = pMP4Syntax->syn_vol.quant_type;
    pMp4DecParam->IsShortHeader = pMP4Syntax->is_short_header;
    pMp4DecParam->VopQuant = pMP4Syntax->syn_vop.vop_quant;
    pMp4DecParam->GobMbNum = pMP4Syntax->syn_vop.num_mb_ingob;
    pMp4DecParam->VopGobNum = pMP4Syntax->syn_vop.num_gobs_invop;
    pMp4DecParam->BitsOfVopTimeIncr = pMP4Syntax->syn_vol.vop_time_incr_bits;
    pMp4DecParam->FwdFcode = pMP4Syntax->syn_vop.vop_fcode_forward;
    pMp4DecParam->BwdFcode = pMP4Syntax->syn_vop.vop_fcode_backward;
    pMp4DecParam->intra_dc_vlc_thr = pMP4Syntax->syn_vop.intra_dc_vlc_thr;
    pMp4DecParam->resync_marker_disable = pMP4Syntax->syn_vol.resync_marker_disable;
    pMp4DecParam->QuarterSample = pMP4Syntax->syn_vol.quarter_sample;
    pMp4DecParam->vop_rounding_type = pMP4Syntax->syn_vop.vop_rounding_type;
    pMp4DecParam->alternate_vertical_scan = pMP4Syntax->syn_vop.alternate_vertical_scan_flag;
    pMp4DecParam->top_field_first = pMP4Syntax->syn_vop.top_field_first;
    pMp4DecParam->Interlaced = pMP4Syntax->syn_vol.interlaced;
    pMp4DecParam->Trb = pMP4Syntax->time_bp;
    pMp4DecParam->Trd = pMP4Syntax->time_pp;

    pMp4DecParam->FF_BUG_DIVX500B413 = pMP4Syntax->FF_BUG_DIVX500B413;
    pMp4DecParam->FF_BUG_EDGE_EXTEND = pMP4Syntax->FF_BUG_EDGE_EXTEND;	
    pMp4DecParam->FF_BUG_EDGE_FIND_POINT = pMP4Syntax->FF_BUG_EDGE_FIND_POINT;		
    pMp4DecParam->FF_BUG_QPEL_CHROMA = pMP4Syntax->FF_BUG_QPEL_CHROMA;	
    pMp4DecParam->FF_BUG_QPEL_CHROMA2 = pMP4Syntax->FF_BUG_QPEL_CHROMA2;	
    pMp4DecParam->FF_BUG_QPEL_FILED = pMP4Syntax->FF_BUG_QPEL_FILED;
	
    pMp4DecParam->image_width = pMP4Syntax->image_width;
    pMp4DecParam->image_height = pMP4Syntax->image_height;	
    pMp4DecParam->sprite_enable = pMP4Syntax->syn_vol.sprite_enable;
    if ((pMP4Syntax->syn_vol.sprite_enable == SPRITE_GMC) && (pMP4Syntax->syn_vop.vop_coding_type == S_VOP))
    {
	    MP4_GetGMCparam(pMP4Syntax, &gmc);	
		pMp4DecParam->sprite_warping_accuracy = pMP4Syntax->syn_vol.sprite_warping_accuracy;
		pMp4DecParam->sprite_warping_points = gmc.num_wp;
		pMp4DecParam->dU[0] = gmc.dU[0];
		pMp4DecParam->dU[1] = gmc.dU[1];		
		pMp4DecParam->dV[0] = gmc.dV[0];
		pMp4DecParam->dV[1] = gmc.dV[1];
		
		pMp4DecParam->Uo = gmc.Uo;
		pMp4DecParam->Vo = gmc.Vo;
		pMp4DecParam->Uco = gmc.Uco;
		pMp4DecParam->Vco = gmc.Vco;		
    }
	else
	{
		pMp4DecParam->sprite_warping_accuracy = pMP4Syntax->syn_vol.sprite_warping_accuracy;
		pMp4DecParam->sprite_warping_points = 0;
		pMp4DecParam->dU[0] = 0;
		pMp4DecParam->dU[1] = 0;		
		pMp4DecParam->dV[0] = 0;
		pMp4DecParam->dV[1] = 0;
		
		pMp4DecParam->Uo = 0;
		pMp4DecParam->Vo = 0;
		pMp4DecParam->Uco = 0;
		pMp4DecParam->Vco = 0;		
	}

    pCur = FSP_GetLogicFs(pCtx->ChanID, pCtx->CurFsID);
    pFwd = FSP_GetLogicFs(pCtx->ChanID, pCtx->FwdFsID);
    pBwd = FSP_GetLogicFs(pCtx->ChanID, pCtx->BwdFsID);

	if (NULL == pCur || NULL == pFwd || NULL == pBwd)
	{	
	   dprint(PRN_FATAL, "%s %d  abnormal!\n",__FUNCTION__,__LINE__);
	   return;
	}
    if ((NULL == pCur->pstDecodeFs) || (NULL == pCur->pstTfOutFs) || (NULL == pCur->pstDispOutFs))
    {
         dprint(PRN_FATAL, "CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\n",pCtx->FwdFsID,pCtx->CurFsID,
         pCtx->BwdFsID, pCur->pstDecodeFs, pCur->pstTfOutFs, pCur->pstDispOutFs);
         return;
    }
    else
    {
        pMp4DecParam->CurPmvPhyAddr = pCur->PmvAddr;
	    pMp4DecParam->BwdPmvPhyAddr = pBwd->PmvAddr;
		
        pMp4DecParam->BwdRefPicPhyAddr   = (NULL != pBwd->pstDecodeFs)?pBwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pMp4DecParam->FwdRefPicPhyAddr   = (NULL != pFwd->pstDecodeFs)?pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pMp4DecParam->CurPicPhyAddr      = pCur->pstDecodeFs->PhyAddr;

        pMp4DecParam->TfBwdPhyAddr       = (NULL != pBwd->pstTfOutFs)?pBwd->pstTfOutFs->PhyAddr: pCur->pstTfOutFs->PhyAddr;
        pMp4DecParam->TfFwdPhyAddr       = (NULL != pFwd->pstTfOutFs)?pFwd->pstTfOutFs->PhyAddr: pCur->pstTfOutFs->PhyAddr;
        pMp4DecParam->TfCurPhyAddr       = pCur->pstTfOutFs->PhyAddr;
        pMp4DecParam->DispFramePhyAddr   = pCur->pstDispOutFs->PhyAddr;
    }

    pMp4DecParam->VahbStride = pCur->pstDispOutFs->Stride;

    for (i = 0; i < 64 ; i++)
    {
        pMp4DecParam->IntraQuantTab[i] = pMP4Syntax->syn_vol.intra_quant_mat[i];
        pMp4DecParam->NonintraQuantTab[i] = pMP4Syntax->syn_vol.nonintra_quant_mat[i];
    }

    pMP4Syntax->syn_vop.mb_total = pMp4DecParam->PicWidthInMb*pMp4DecParam->PicHeightInMb;
    pMp4DecParam->Compress_en = pCtx->pstExtraData->s32Compress_en;

    return ;
}

/*------------------------------------------------------------------------------

        Function name: Mp4_Get_DecMode

        Description: 获取解码模式
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VOID Mp4_Get_DecMode(MP4_CTX_S *pCtx)
{
    if ( pCtx->DecMode == I_MODE && pCtx->pstExtraData->s32DecMode != I_MODE )
    {
        /* 置找下一个I帧的标志 */
        pCtx->IPVopErr = 1;
    }

    /* 获取解码模式 */
    if (pCtx->pstExtraData->s32DecMode == I_MODE)
    {
        pCtx->DecMode = I_MODE;
    }
    else if (pCtx->pstExtraData->s32DecMode == IP_MODE)
    {
        pCtx->DecMode = IP_MODE;
    }
    else if (pCtx->pstExtraData->s32DecMode == DISCARD_B_BF_P_MODE)
    {
        pCtx->DecMode = DISCARD_B_BF_P_MODE;
    }
    else
    {
        pCtx->DecMode = IPB_MODE;
    }

    return;
}


UINT32 GetTrailingOneLen(UINT8* pCode, SINT32 CodeLen)
{
    UINT32 T1Len = 0;
    UINT8* ptr = pCode;
    /* CodeLen 为字节数 */
    /* 设置起始码字初始值为0x0 */
    
    ptr += CodeLen;
    ptr -= 1;

    {
        UINT8  _c_temp = ptr[0];
        UINT32 _r_bit_len = 0;
        
        if (0 == (_c_temp & 0x1))
        {
            _r_bit_len = 1;
        }
        else
        {         
            while (_c_temp & 0x1)
            {
                _r_bit_len ++;
                _c_temp >>= 1;
            }
            if (_r_bit_len) { _r_bit_len++; }
        }
        
        T1Len = _r_bit_len;
    } 

    return T1Len;
}            

/*------------------------------------------------------------------------------

        Function name: MPEG4DEC_Init

        Description: 解码器初始化
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 MPEG4DEC_Init(MP4_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    SINT32  ImgQueRstMagic;
    MP4_SYNTAX MP4Syntax;
    MP4_SYNTAX_STATE MP4SyntaxState;

    if( NULL == pCtx || NULL == pstExtraData )
    {
        return MPEG4_INIT_FAIL;
    }
        
    if (1 == pstExtraData->s32KeepSPSPPS) //omx mpeg4 seek
    {    
        memcpy(&MP4Syntax, &pCtx->MP4Syntax, sizeof(pCtx->MP4Syntax));
        memcpy(&(MP4Syntax.syn_vos), &pCtx->MP4Vos, sizeof(pCtx->MP4Vos));
        memcpy(&(MP4Syntax.syn_vol), &pCtx->MP4Vol, sizeof(pCtx->MP4Vol));
        memcpy(&MP4SyntaxState, &pCtx->MP4SyntaxState, sizeof(pCtx->MP4SyntaxState));
    }
     
    // 清除通道上下文 
    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    memset(pCtx, 0, sizeof(MP4_CTX_S));
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue);
    
    /* 记录附加信息指针 */
    pCtx->pstExtraData = pstExtraData;
    pCtx->pstExtraData->s32WaitFsFlag = 0;
    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }

    /* 全局信息初始化 */
    if ( MPEG4_INIT_SUCCESS != Global_Data_Init(pCtx) )
    {
        return MPEG4_INIT_FAIL;
    }

    /* 初始化成功 */
    pCtx->InitComplete = 1;
    pCtx->PPicFound = 0;

    if (1 == pstExtraData->s32KeepSPSPPS) 
    {    
        memcpy(&pCtx->MP4Syntax, &MP4Syntax, sizeof(pCtx->MP4Syntax));
        memcpy(&pCtx->MP4Vos, &(MP4Syntax.syn_vos), sizeof(pCtx->MP4Vos));
        memcpy(&pCtx->MP4Vol, &(MP4Syntax.syn_vol), sizeof(pCtx->MP4Vol));
        memcpy(&pCtx->MP4SyntaxState, &MP4SyntaxState, sizeof(pCtx->MP4SyntaxState));
        pCtx->SeekReset = 1;
    }
    
    return MPEG4_INIT_SUCCESS;
}


/*------------------------------------------------------------------------------

        Function name: MPEG4DEC_Destory

        Description: 解码器初始化
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
VOID MPEG4DEC_Destroy(MP4_CTX_S *pCtx)
{
    dprint(PRN_CTRL, "MPEG4 destroy\n");
    
    pCtx->InitComplete = 0;

}


/*------------------------------------------------------------------------------

        Function name: MPEG4DEC_Decode

        Description: 解码操作 
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 MPEG4DEC_Decode(MP4_CTX_S *pCtx, const DEC_STREAM_PACKET_S *ptr_strm_para)
{
    UINT32 bits_consume;
    SINT32 ret;
    MP4_DEC_PARAM_S *pMp4DecParam = NULL;
    IMAGE *pFwdImg, *pBwdImg;

    pMp4DecParam = &pCtx->Mp4DecParam;

    if ((pCtx->InitComplete==0)||(ptr_strm_para->StreamPack[0].LenInByte < 1)||
            (ptr_strm_para->StreamPack[0].PhyAddr==0)||(ptr_strm_para->StreamPack[0].VirAddr==0))
    {
        /* 返回初始化没有成功或者码流长度异常*/
        dprint(PRN_ERROR, "bitsream para error -----\n");
        return MPEG4_DEC_FAIL; 
    }
	
    dprint(PRN_CTRL, "MPEG4DEC Decode -----\n");
    dprint(PRN_STREAM, "ptr_strm_para->PhyAddr0=0x%x\n", ptr_strm_para->StreamPack[0].PhyAddr);
    dprint(PRN_STREAM, "ptr_strm_para->Length0=%d\n", ptr_strm_para->StreamPack[0].LenInByte);
    dprint(PRN_STREAM, "ptr_strm_para->IsLastSeg0=%d\n", ptr_strm_para->StreamPack[0].IsLastSeg);
    dprint(PRN_STREAM, "ptr_strm_para->PhyAddr1=0x%x\n", ptr_strm_para->StreamPack[1].PhyAddr);
    dprint(PRN_STREAM, "ptr_strm_para->Length1=%d\n", ptr_strm_para->StreamPack[1].LenInByte);
    dprint(PRN_STREAM, "ptr_strm_para->IsLastSeg1=%d\n", ptr_strm_para->StreamPack[1].IsLastSeg);
    
    dprint(PRN_STREAM, "ptr_strm_para->Length0 = %d\n", ptr_strm_para->StreamPack[0].LenInByte); 
    dprint(PRN_STREAM, "byte0: = 0x%x\n", *(ptr_strm_para->StreamPack[0].VirAddr + 0)); 
    dprint(PRN_STREAM, "byte1: = 0x%x\n", *(ptr_strm_para->StreamPack[0].VirAddr + 1));
    dprint(PRN_STREAM, "byte2: = 0x%x\n", *(ptr_strm_para->StreamPack[0].VirAddr + 2));
    dprint(PRN_STREAM, "byte3: = 0x%x\n", *(ptr_strm_para->StreamPack[0].VirAddr + 3)); 

    /* 解码模式设定 */
	memcpy(&(pCtx->stCurPacket), ptr_strm_para, sizeof(DEC_STREAM_PACKET_S));
    MP4_GetScdUpMsg(pCtx, &(pCtx->stCurPacket));

    if(MPEG4_FAIL == MP4_Check_CurPacket(pCtx))
    {
        dprint(PRN_ERROR,"MP4_Check_CurPacket failed!\n");
        return MPEG4_DEC_FAIL;
    }

    MP4_GetScdUpMsg(pCtx, &(pCtx->stCurPacket));

    /*码流管理初始化*/
    Bits_Init(&pCtx->BitsObj, &(pCtx->stCurPacket));

    do
    { 
        /* 解码模式设定 */
        Mp4_Get_DecMode(pCtx);
        
        if((1 == pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
           (1 == pCtx->pstExtraData->s32WaitFsFlag))
        {
            pCtx->PicIntegrality = pCtx->LastPicIntegrality;
        }
        else
        {
            pCtx->LastPicIntegrality = pCtx->PicIntegrality;
        }
        
        bits_consume = Mp4_Syntax_Parse(pCtx, pCtx->BitsObj.vir_addr, pCtx->BitsObj.len);

        Bits_Flush(&pCtx->BitsObj, bits_consume);
        
        if((1 != pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) || \
           ((1 == pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
           (0 == pCtx->pstExtraData->s32WaitFsFlag)))
        {
            if ((MP4_FOUND_NEXTVOPHDR == (pCtx->PicIntegrality & MP4_FOUND_NEXTVOPHDR))||
		        (MP4_FOUND_HISIHDR == (pCtx->PicIntegrality & MP4_FOUND_HISIHDR))) 
            {
                /* 清除完整信息 */
                pCtx->PicIntegrality &= ~MP4_PIC_OK;

            /* 解码模式选择 */ 
            if (((pCtx->DecMode==I_MODE)&&(pCtx->MP4Syntax.syn_vop.vop_coding_type!=I_VOP))||((pCtx->DecMode==IP_MODE)&&((pCtx->MP4Syntax.syn_vop.vop_coding_type==B_VOP))))
            {
                //dprint(PRN_CTRL, "Decode mode IP OR I processing---\n");
        
                /* I or IP 解码模式中对于跳过的帧，user data空间释放*/
                MP4_ClearCurPic(pCtx);
                MP4_Clean_HeadPacket(pCtx);
                //continue;
                return MPEG4_DEC_FAIL; 
            }
            else if (pCtx->DecMode==DISCARD_B_BF_P_MODE)
            {
                    if (pCtx->MP4Syntax.syn_vop.vop_coding_type == I_VOP)
                    {
                        if (pCtx->PPicFound == 0)
                        {
                            pCtx->PPicFound = 2;/*find the first I*/
                        }
                        else
                        {
                            pCtx->PPicFound = 1;/*find annother I*/
                        }
                    }

                    /* 这种模式下，N_VOP也丢弃 */
                    if ( ( (B_VOP == pCtx->MP4Syntax.syn_vop.vop_coding_type) || (pCtx->MP4Syntax.syn_vop.vop_coding_type == N_VOP) ) &&
                         (2 == pCtx->PPicFound) ) /* 发现B帧 */
                    {
                        // continue;
                        return MPEG4_DEC_FAIL;
                    }
                else if (P_VOP==pCtx->MP4Syntax.syn_vop.vop_coding_type) 
                {
                    pCtx->PPicFound = 1;
                }
            }

            /*帧空间申请及属性设置 */
            ret = Mp4_Frame_Atr(pCtx);  

            if (ret == FRAME_REQ_FAIL)
            {
                /* 这个返回类型和帧申请异常处理可不一样*/
                dprint(PRN_ERROR,"Mp4_Frame_Atr return fail\n");
                /* 这个返回类型和帧申请异常处理可不一样*/              
                MP4_ClearCurPic(pCtx);
                MP4_Clean_HeadPacket(pCtx);
                return MPEG4_DEC_FAIL; 
            }

                //dead code
#if 0
                /*如果帧申请出现异常，这里寻找下一个I帧处理，继续相关的语法解析 */
                if (ret == FRAME_REQ_ABNORMITY)
                {
                    dprint(PRN_ERROR, "Frame req error---\n");
                    MP4_ClearCurPic(pCtx);
                    MP4_Clean_HeadPacket(pCtx);
                    //continue;
                    return MPEG4_DEC_FAIL;
                }
#endif
            /* 如果是P/B帧，要看其参考帧是否超出参考阈值，若超出则不解 */
            pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->FwdFsID);
            pBwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->BwdFsID);

            if(NULL== pFwdImg || NULL == pBwdImg)
            {
            	dprint(PRN_ERROR, "fuction return value is null, %s %d!!\n",__FUNCTION__,__LINE__);
            	return MPEG4_DEC_FAIL;
            }
            
            if ((pCtx->MP4Syntax.coding_mode == P_VOP)||(pCtx->MP4Syntax.coding_mode == S_VOP))
            {
                if ( (NULL == pFwdImg) || (pFwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
                {
                    FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                    MP4_ClearCurPic(pCtx);
                    MP4_Clean_HeadPacket(pCtx);
			        if(NULL == pFwdImg)
			      	{
			      		dprint(PRN_ERROR, "fuction return value is null,%s %d!!\n",__FUNCTION__,__LINE__);
	                    return MPEG4_DEC_FAIL;
			      	}
				    else
				    {
				    	dprint(PRN_ERROR, "dec P/S frame, fwd ref err(%d) > ref_thr(%d)\n", pFwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
		                return MPEG4_DEC_FAIL;
				    }    
                }
            }
            else if (pCtx->MP4Syntax.coding_mode == B_VOP)
            {
                 if ( (NULL == pFwdImg) || (pFwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
                 {
                     FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                     MP4_ClearCurPic(pCtx);
                     MP4_Clean_HeadPacket(pCtx);
				     if(NULL == pFwdImg)
			       	 {
			       	 	dprint(PRN_ERROR, "fuction return value is null,%s %d!!\n",__FUNCTION__,__LINE__);
		                return MPEG4_DEC_FAIL;
			       	 }
					 else
					 {
					 	dprint(PRN_ERROR, "dec B frame, bwd ref err(%d) > ref_thr(%d)\n", pFwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
		                return MPEG4_DEC_FAIL;
					 } 
                 }

                 if ( (NULL == pBwdImg) || (pBwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
                 {
                     FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                     MP4_ClearCurPic(pCtx);
                     MP4_Clean_HeadPacket(pCtx);
				     if(NULL == pFwdImg)
			       	 {
			       	 	dprint(PRN_ERROR, "fuction return value is null,%s %d !!\n",__FUNCTION__,__LINE__);
		                return MPEG4_DEC_FAIL;
			       	 }
					 else
					 {
						 dprint(PRN_ERROR, "dec B frame, fwd ref err(%d) > ref_thr(%d)\n", pBwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
				         return MPEG4_DEC_FAIL;
					 }
                 }
            }

            /* 参考维护 */
            if (B_VOP != pCtx->MP4Syntax.syn_vop.vop_coding_type)
            {
                pCtx->RefNum = pCtx->RefNum>0?2:1;
	            /*当对参考帧数目有要求时，将此部分内容放于MPEG4DEC_VDMPostProc()*/

                if (pCtx->FwdFsID != pCtx->BwdFsID)
                {
                    //这样释放的才是有效参考图
                    FSP_SetRef(pCtx->ChanID, pCtx->FwdFsID, 0);
                    if (FS_DISP_STATE_WAIT_DISP != FSP_GetDisplay(pCtx->ChanID, pCtx->FwdFsID))
                    {
                        FSP_SetDisplay(pCtx->ChanID, pCtx->FwdFsID, 0);
                    }
                }

                pCtx->FwdFsID = pCtx->BwdFsID;
				pCtx->FwdCodingType = pCtx->BwdCodingType;
				pCtx->FwdTimePP = pCtx->BwdTimePP;

				pCtx->BwdFsID = pCtx->CurFsID;
				pCtx->BwdCodingType = pCtx->CurCodingType;
				pCtx->BwdTimePP = pCtx->MP4Syntax.time_pp;

                FSP_SetRef(pCtx->ChanID, pCtx->CurFsID, 1);
                FSP_RemovePmv(pCtx->ChanID, pCtx->FwdFsID);
            }

            if (pCtx->MP4Syntax.syn_vop.vop_coding_type != N_VOP)
            {
                /* 放到 pos */
                //memset(pMp4DecParam, 0, sizeof(MP4_DEC_PARAM_S));
                Mp4_Set_DecPar(pCtx, 0, ptr_strm_para);

                if (pCtx->pstExtraData->s8SpecMode != 1)
                {
                    /* 容错处理，但在回归标准码流时，码流有I 后面紧接着可解的B帧，这样做会丢掉该B,
                    而导致后面出错，回归时注释掉*/
                    /*
                        对于 I I BBBB I BBBB 这种流，不应该丢掉B帧  c00277632 20150706
                    */
                    if (I_VOP == pCtx->MP4Syntax.syn_vop.vop_coding_type)
                    {
                        if (pCtx->PPicFound == 0)
                        {
                            pCtx->PPicFound = 2;/*find the first I*/
                        }
                        else
                        {
                            pCtx->PPicFound = 1;/*find annother I*/
                        }
                    }

                    if ( ( (B_VOP == pCtx->MP4Syntax.syn_vop.vop_coding_type) || (pCtx->MP4Syntax.syn_vop.vop_coding_type == N_VOP) ) &&
                         (2 == pCtx->PPicFound) ) /* 发现B帧 */
                    {
                        FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                        return MPEG4_FAIL;
                    }
                    else if (P_VOP == pCtx->MP4Syntax.syn_vop.vop_coding_type)
                    {
                        pCtx->PPicFound = 1;
                    }
                }

                /*
                pCtx->Mp4DecParam.IsNvopCopy = 0;
                pCtx->pMp4DecParam = &pCtx->Mp4DecParam;
                */

                pCtx->pMp4DecParam = &pCtx->Mp4DecParam;

                if (1 == pCtx->pstExtraData->stDisParams.s32Mode)
                {
                    if ((NULL != pCtx->pMp4DecParam) && (B_VOP == pCtx->MP4Syntax.syn_vop.vop_coding_type))
                    {
                        /* 这时应该清空帧存信息和码流信息,DecParam信息是否要清空待定 */
                        pCtx->pMp4DecParam = NULL;
                       // FSP_SetDisplay(pCtx->ChanID, pCtx->CurFsID, 0);
                        FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                        MP4_ClearCurPic(pCtx);
                        MP4_Clean_HeadPacket(pCtx);

                        return -1;
                    }
                }
                else if (2 == pCtx->pstExtraData->stDisParams.s32Mode)
                {
                    if ((pCtx->pstExtraData->stDisParams.s32DisNums > 0) && (NULL != pCtx->pMp4DecParam) 
                        && (B_VOP == pCtx->MP4Syntax.syn_vop.vop_coding_type))
                    {
                        pCtx->pMp4DecParam = NULL;
                        //FSP_SetDisplay(pCtx->ChanID, pCtx->CurFsID, 0);
                        FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                        pCtx->pstExtraData->stDisParams.s32DisNums--;
                        MP4_ClearCurPic(pCtx);
                        MP4_Clean_HeadPacket(pCtx);
                        return -1;
                    }
                }
                
                pCtx->Mp4DecParam.IsNvopCopy = 0;

				if(pCtx->MP4Syntax.syn_vop.vop_coding_type == I_VOP)
				{
                    REPORT_FIND_IFRAME(pCtx->ChanID, 0);
				}
            }
            else
            {
                FSP_LOGIC_FS_S *pCur, *pFwd;
                if (pCtx->MP4Syntax.packed_mode == 0)
                {
                    /*NVOP 处理 */
                    /* 启动硬件搬移操作 */
                    dprint(PRN_IMAGE, "NVOP mem move--\n");
                    pCur = FSP_GetLogicFs(pCtx->ChanID, pCtx->CurFsID);
                    pFwd = FSP_GetLogicFs(pCtx->ChanID, pCtx->FwdFsID);
					
					if ((NULL == pCur) || (NULL == pFwd))
					{
                         FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                         dprint(PRN_FATAL, "line: %d pCur = %p, pFwd = %p\n", __LINE__, pCur, pFwd);
                         MP4_ClearCurPic(pCtx);
                         MP4_Clean_HeadPacket(pCtx);
                         return MPEG4_FAIL;
					}

                    if ((NULL == pCur->pstDecodeFs) || (NULL == pCur->pstTfOutFs) || (NULL == pCur->pstDispOutFs))
                    {
                         FSP_ClearLogicFs(pCtx->ChanID, pCtx->CurFsID, 1);
                         dprint(PRN_FATAL, "CurFsID(f%d,%d,b%d) abnormal!(%p,%p,%p)\n",pCtx->FwdFsID,pCtx->CurFsID,
                         pCtx->BwdFsID, pCur->pstDecodeFs, pCur->pstTfOutFs, pCur->pstDispOutFs);
                         MP4_ClearCurPic(pCtx);
                         MP4_Clean_HeadPacket(pCtx);
                         return MPEG4_FAIL;
                    }
                    else
                    {
	                    Vdm_Mem_Move( pCtx,pCur,
	                        pCur->pstDecodeFs->PhyAddr, 
	                        pCur->pstDispOutFs->PhyAddr, 
	                        (NULL != pFwd->pstDecodeFs)?pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr, 
	                        pCtx->MP4Syntax.image_width,
	                        pCtx->MP4Syntax.image_height
	                        );
                    }
                }
            }
        }
        else
        {
            dprint(PRN_CTRL, "bits not enought\n");                
            return MPEG4_FAIL;
            }
        }
    }
    while (0);

    return 0;
}


/*------------------------------------------------------------------------------

        Function name: MPEG4DEC_RecycleImage

        Description: 解码器释放帧
                 
        Input: 
            
        Output:

        Return:

        Others:

------------------------------------------------------------------------------*/
SINT32 MPEG4DEC_RecycleImage(MP4_CTX_S *pCtx, UINT32 ImgID)
{
    IMAGE *pImg;

    if (NULL == pCtx)
    {
        return VF_ERR_PARAM;
    }

    FSP_SetDisplay(pCtx->ChanID, ImgID, 0);
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, ImgID);

	if (NULL != pImg)
	{
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        pImg->p_usrdat[0] = NULL;
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        pImg->p_usrdat[1] = NULL;            
	}
     
    return VF_OK;
}

VOID MP4_SetImgFormat(MP4_CTX_S *pCtx)
{
    //UINT32 aspect_ratio;
    MP4_SYNTAX *pMP4Syntax = &pCtx->MP4Syntax;
    IMAGE *pImg;
    
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->CurFsID);
    if (NULL == pImg)
    {
        return;
    }

    if (pMP4Syntax->image_width > 0 && pMP4Syntax->image_height > 0)
    {
        pImg->disp_width=(pMP4Syntax->image_width > pImg->image_width)? pImg->image_width:
        pMP4Syntax->image_width;
        pImg->disp_height=(pMP4Syntax->image_height > pImg->image_height)? pImg->image_height:
        pMP4Syntax->image_height; 
    }
    else
    {
        pImg->disp_width = pImg->image_width;
        pImg->disp_height = pImg->image_height;    
    }

#if 0

    /*sequence display extension 和 picture display extension 属于studio profile*/
    if (pCtx->MP4Syntax.syn_vol.aspect_ratio_info == 1)
    {
        aspect_ratio = DAR_IMG_SIZE;
    }
    else if ((pCtx->MP4Syntax.syn_vol.aspect_ratio_info == 2) || (pCtx->MP4Syntax.syn_vol.aspect_ratio_info == 3))
    {
        aspect_ratio = DAR_4_3;
    }
    else if ((pCtx->MP4Syntax.syn_vol.aspect_ratio_info == 4) || (pCtx->MP4Syntax.syn_vol.aspect_ratio_info == 5))
    {
        aspect_ratio = DAR_16_9;
    }
    else
    {
        aspect_ratio = DAR_UNKNOWN;
    }

#endif
    return;
}

SINT32 MPEG4DEC_GetRemainImg(MP4_CTX_S *pCtx)
{
    IMAGE  *pImg = NULL;
    SINT32 display_flag;
    SINT32 ret = LAST_OUTPUT_FAIL;

    if (OUTPUT_IN_DEC == pCtx->pstExtraData->s32DecOrderOutput)
    {
        ret = LAST_ALREADY_OUT;
    }
    else
    {
        pImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->BwdFsID);
        if (NULL != pImg)
        {
    	   display_flag = FSP_GetDisplay(pCtx->ChanID, pCtx->BwdFsID);
	   if (FS_DISP_STATE_DEC_COMPLETE == display_flag)
	   {
             MP4_SetImgFormat(pCtx);
             pImg->last_frame = 1;      // last frame
             
             FSP_SetDisplay(pCtx->ChanID, pImg->image_id, 1);
             if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_MPEG4, pCtx, &pCtx->ImageQue, pImg) )
             {
                  MPEG4DEC_RecycleImage(pCtx, pImg->image_id);
                  FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
                  pImg->p_usrdat[0] = NULL;
                  FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
                  pImg->p_usrdat[1] = NULL;
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
          }
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


SINT32 MPEG4DEC_VDMPostProc(MP4_CTX_S *pCtx, SINT32 ErrRatio, LUMA_INFO_S *pLumaInfo)
{
    IMAGE  *pCurImg, *pBwdImg, *pToQueImg;//*pFwdImg;
	SINT32  ToQueCodingType, ToQueTimePP;
    MP4_DEC_PARAM_S *pMp4DecParam = NULL;
    FSP_LOGIC_FS_S* pstLogicFs = NULL;
    pMp4DecParam = &pCtx->Mp4DecParam;
    
    memset(pMp4DecParam, 0, sizeof(MP4_DEC_PARAM_S));
    MP4_ClearCurPic(pCtx);
    MP4_Clean_HeadPacket(pCtx);
 
    pCtx->ErrorLevel = ErrRatio;

    pCurImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->CurFsID);
    pBwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->BwdFsID);
    //pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->FwdFsID);
    if (pCurImg == NULL)//(pFwdImg == NULL))  前向参考帧此函数不用，因此无需判断
    {
        dprint(PRN_FATAL,"pImg is null, pCurImg = %p, pBwdImg = %p\n", pCurImg, pBwdImg);
		return MPEG4_FAIL;
	}

    /* 图像输出：*/
    dprint(PRN_IMAGE, "FrameNum=%d\n", pCtx->FrameNum); 
    dprint(PRN_IMAGE, "vop_coding_type=%d\n", pCtx->MP4Syntax.syn_vop.vop_coding_type); 

	if (pCurImg)
	{
        pCurImg->error_level = pCtx->ErrorLevel;
	}
    Mp4_ClearUsrData(pCtx->ChanID, pCtx->UsrData);

    /* 正确解析IPVOP, 对标识清０*/
    if ((B_VOP != pCtx->MP4Syntax.syn_vop.vop_coding_type) && (pCtx->ErrorLevel > (UINT32)pCtx->pstExtraData->s32RefErrThr) )
    {
		REPORT_OVER_REFTHR(pCtx->ChanID, pCtx->ErrorLevel, (UINT32)pCtx->pstExtraData->s32RefErrThr);
        pCtx->IPVopErr = 1;
        MP4_CLEARREFFLAG;
        MP4_CLEARREFNUM;
        return -1;  //MPEG4_FALSE
    }
    else
    {
        pCtx->IPVopErr = 0;
    }


    /* 输出图象 */
    MP4_SetImgFormat(pCtx);
	if (OUTPUT_IN_DEC != pCtx->pstExtraData->s32DecOrderOutput) /* if(显示序输出) */
    {
        if (B_VOP != pCtx->MP4Syntax.syn_vop.vop_coding_type )
        {
            pCtx->ToQueFsID = (pCtx->RefNum > 1)? pCtx->FwdFsID: -1;
		    ToQueCodingType = (pCtx->RefNum > 1)? pCtx->FwdCodingType: -1;
            ToQueTimePP = (pCtx->RefNum > 1)? pCtx->FwdTimePP : -1;
        }
        else
        {
            pCtx->ToQueFsID = pCtx->CurFsID;
			ToQueCodingType = B_VOP;
            ToQueTimePP = pCtx->MP4Syntax.time_pp;
            
            /* 为了保证输出的PTS单调增，此处需要检测当前B帧的时间戳是否小于其后向参考帧的时间戳，若是则交换它们.
               做此处理的原因是avi文件没有PTS，播放器下发的实际上是DTS，其顺序与播放序不同，引发诸多问题. */
            if (pBwdImg != NULL)
            {
                if ((SINT64)pBwdImg->PTS < (SINT64)pCurImg->PTS )
                {
                    UINT64  TmpPts = pCurImg->PTS;
    
                    pCurImg->PTS = pBwdImg->PTS;
                    pBwdImg->PTS = TmpPts;
                }					
            }
        }
    }
    else
    {
        pCtx->ToQueFsID = pCtx->CurFsID;
		ToQueCodingType = pCtx->MP4Syntax.syn_vop.vop_coding_type;
        ToQueTimePP = pCtx->MP4Syntax.time_pp;
    }

    if ( -1 != pCtx->ToQueFsID )
    {

        pToQueImg = FSP_GetFsImagePtr(pCtx->ChanID, pCtx->ToQueFsID);

        if ( NULL == pToQueImg )
        {
            dprint(PRN_FATAL,"line: %d pToQueImg is null!\n", __LINE__);
            return MPEG4_FAIL;
        }
        /* z56361, 2011-2-17.
           经过对手头所有N_VOP码流的研究，发现N_VOP的vop_time_increment都与其相邻的P帧相同，这暗示N_VOP
           是不需要输出显示的。而且杨亮亮在调试AVI文件播放的时候发现，如果N_VOP输出，同步将会有问题，而
           同步的问题恰好在于，N_VOP的输出使输出帧率比实际帧率要大.
           综合以上情况，决定修改为N_VOP不输出 */
        /* z56361, 2011-9-16.
           高飞发现一条mpeg4测试码流SUB-10.avi，我们播放的较快。经查，发现此码流NVOP的vop_time_increment与其相邻的
           P帧不同，不符合以前的判断. 而且，此码流如果输出NVOP，则播放速度是正常的。试验结果和正向推理均表明，如果
           vop_time_increment发生了变化，则这个NVOP是需要输出的。所以下面加上 "&& pCtx->MP4Syntax.time_pp == 0" */
        if (ToQueCodingType == N_VOP && ToQueTimePP == 0)
        {
            g_VfmwChanStat[pCtx->ChanID].u32SkipDiscard++;
            FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
            pToQueImg->p_usrdat[0] = NULL;
            FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
            pToQueImg->p_usrdat[1] = NULL;
            FSP_SetDisplay(pCtx->ChanID, pCtx->ToQueFsID, 0);
            return MPEG4_FAIL;
		}

        if (pToQueImg->error_level == 0 || pToQueImg->error_level <= pCtx->pstExtraData->s32OutErrThr)
        {
            pstLogicFs = FSP_GetLogicFs(pCtx->ChanID, pCtx->ToQueFsID);
            if (NULL == pstLogicFs)
            {
                FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
	            pToQueImg->p_usrdat[0] = NULL;
	            FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
	            pToQueImg->p_usrdat[1] = NULL;
                FSP_SetDisplay(pCtx->ChanID, pCtx->ToQueFsID, 0);
                return MPEG4_FAIL;
            }

            if ((B_VOP == ToQueCodingType) || (FS_DISP_STATE_DEC_COMPLETE == pstLogicFs->s32DispState))
            {
                FSP_SetDisplay(pCtx->ChanID, pCtx->ToQueFsID, 1);
                if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_MPEG4, pCtx, &pCtx->ImageQue, pToQueImg))
                {
                    FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
                    pToQueImg->p_usrdat[0] = NULL;
                    FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
                    pToQueImg->p_usrdat[1] = NULL;
                    FSP_SetDisplay(pCtx->ChanID, pCtx->ToQueFsID, 0);
                    return MPEG4_FAIL;
                }
            }
            else
            {
                /* l232354:在输出顺序不停切换时，解码序到显示序会出现一帧重复输出的情况，故加上IF条件分支
                   显示序到解码序会有一帧不输出，这里暂时不做任何处理 */
			    dprint(PRN_IMAGE, "CurImage %d is already out put\n", pCtx->ToQueFsID); 
            }
        }
        else
        {
		    REPORT_OVER_REFTHR(pCtx->ChanID, pToQueImg->error_level, pCtx->pstExtraData->s32OutErrThr);
            dprint(PRN_ERROR,"err(%d) > out_thr(%d)\n", pToQueImg->error_level, pCtx->pstExtraData->s32OutErrThr);
            FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
            pToQueImg->p_usrdat[0] = NULL;
            FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
            pToQueImg->p_usrdat[1] = NULL;
            FSP_SetDisplay(pCtx->ChanID, pCtx->ToQueFsID, 0);
        }
    }
      
    //end of change
    pCtx->FrameNum++;

    return 0;
}


SINT32 MPEG4DEC_GetImageBuffer( MP4_CTX_S *pCtx )
{
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

SINT32 MP4_GetPacketState(MP4_CTX_S *pCtx)
{
    SINT32 ret = MPEG4_FAIL;
    if(1 == pCtx->IsWaitToDecFlag)
    {
        ret = MPEG4_NOTDEC;
    }

    return ret;
}

VOID MP4_ClearCurPacket(SINT32 ChanID, DEC_STREAM_PACKET_S *pMp4Packet)
{
    SM_ReleaseStreamSeg(ChanID, pMp4Packet->StreamPack[0].StreamID);
    if((0 == pMp4Packet->StreamPack[0].IsLastSeg) && (1 == pMp4Packet->StreamPack[1].IsLastSeg))
    {
        SM_ReleaseStreamSeg(ChanID, pMp4Packet->StreamPack[1].StreamID);
    }

    memset(pMp4Packet, 0, sizeof(DEC_STREAM_PACKET_S));

    return;
}

VOID MP4_ClearCurPic(MP4_CTX_S *pCtx)
{
    SINT32 i;
    SINT32 ChanID = pCtx->ChanID;
    SINT32 StreamIDNum = pCtx->StreamIDNum;

    for(i = 0; i < StreamIDNum; i++)
    {
        SM_ReleaseStreamSeg(ChanID, pCtx->StreamID[i]);
    }

    pCtx->StreamIDNum = 0;

    return;
}

VOID MP4_GetScdUpMsg(MP4_CTX_S *pCtx, DEC_STREAM_PACKET_S *pMp4Packet)
{
    MP4_SCD_UPMSG *pScdUpMsg = &(pCtx->ScdUpMsg);
    MP4_SCD_UPMSG *pLastScdUpMsg = &(pCtx->LastScdUpMsg);

    if ((1 == pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
        (1 == pCtx->pstExtraData->s32WaitFsFlag))
    {
        memcpy(pScdUpMsg, pLastScdUpMsg, sizeof(MP4_SCD_UPMSG));
    }
    else
    {
        /* 如果是X6, scd only mpeg4 up msg info */
        memcpy(pScdUpMsg, &(pMp4Packet->StreamPack[0].stMp4UpMsg), sizeof(MP4_SCD_UPMSG));

        memcpy(pLastScdUpMsg, &(pMp4Packet->StreamPack[0].stMp4UpMsg), sizeof(MP4_SCD_UPMSG));
    }
    return;
}

/**********************************************************************/ 
/*   真假slice检测:                                                   */
/*   实际上报slice起始码的长度，等于根据VOP计算得出期望起始码的长度   */
/**********************************************************************/ 
SINT32 Mp4_Check_Slice_NotSH(MP4_CTX_S *pCtx)
{
	SINT32 ret = MPEG4_FAIL;
	SINT32 Fcode,StartCodeLen, goldenLen;
	SINT32 VopCodingType = pCtx->MP4Vop.vop_coding_type;

	/* 符合slice 的规则，但有可能是假的，得check下才知道 */
    /* 无论是短头非短头slice，只要符合非短头slice规则，均按slice来解析 */
	if((0 == pCtx->MP4Vol.resync_marker_disable) && (0 == pCtx->ScdUpMsg.StartCodeBitOffset))
	{
        goldenLen = SLICE_START_CODE_BASE_LEN + pCtx->ScdUpMsg.StartCodeLength;

		switch(VopCodingType)
		{
			case I_VOP:
				StartCodeLen = 17;
				break;	
			case S_VOP:
			case P_VOP:
				Fcode = pCtx->MP4Vop.vop_fcode_forward;
				StartCodeLen = 16 + Fcode;
				break;	
			case B_VOP:
				Fcode = MAX(pCtx->MP4Vop.vop_fcode_forward, pCtx->MP4Vop.vop_fcode_backward);
				StartCodeLen = MAX(16 + Fcode, 18);
				break;	
			case N_VOP:
			default:
				dprint(PRN_ERROR,"vop_coding_type = %d is not expected!\n",VopCodingType);
				return MPEG4_FAIL;
				break;	
		}

		if(StartCodeLen == goldenLen)
		{
			ret = MPEG4_OK;	
		}
	}

	return ret;
}


/* 处理假的 slice 信息 */
SINT32 Mp4_Combine_SliceData(MP4_CTX_S *pCtx, SINT32 CodeLen)
{
    UINT32  SlcNum;
    MP4_SLICE_INFO *pSlcPara;

    SlcNum = pCtx->Mp4DecParam.SlcNum;
    pSlcPara = pCtx->Mp4DecParam.SlcPara;

	/* 应该考虑分包的情况,分包了,其地址一定会小于前一包的地址,直接在前一包增加码流的长度是有问题的 */
	/* 前提:在时间前后的两包码流不可能同事出现分包的情况,一但出现分包时，第二包的码流地址应该较小 */
	if (MP4_FOUND_VOPHDR == (pCtx->PicIntegrality & MP4_FOUND_VOPHDR))
	{
	    if(1 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)
	    {
            /* slice info 应该有值，如果没有，肯定是出错了 */
            if((0 == SlcNum ) || (MAX_SLICE_NUM_IN_VOP <= SlcNum))
            {
                /* 肯定出现了错误 */
                dprint(PRN_ERROR," slice num %d is not extpected!\n", SlcNum);
                return MPEG4_FAIL;
            }

			/* 这么判断是否完备，需要在考虑  */
			if((0 == pSlcPara[SlcNum - 1].bit_len[1]) || (0 == pSlcPara[SlcNum - 1].phy_address[1]))  
	        {
	            /* 当前包和前一包都没有出现分包，这需要看看谁的地址大 */
                if(pCtx->stCurPacket.StreamPack[0].PhyAddr > pSlcPara[SlcNum - 1].phy_address[0])
                {
                    pSlcPara[SlcNum - 1].bit_len[0] += CodeLen * 8;               
                }
                else
                {
                    pSlcPara[SlcNum - 1].bit_len[1] = CodeLen * 8;
                    pSlcPara[SlcNum - 1].phy_address[1] = pCtx->stCurPacket.StreamPack[0].PhyAddr;
                }
			}
			else
			{
	            /* 前一包出现分包 */
			    if(pCtx->stCurPacket.StreamPack[0].PhyAddr < pSlcPara[SlcNum - 1].phy_address[1])
			    {
					/* 出现了分包，那么当前的PACKET 一定会比第二包大
					    否则将是一个致命的错误*/
                    dprint(PRN_ERROR," line %d packet is wrong!\n",__LINE__);
					return MPEG4_FAIL;
				}
				pSlcPara[SlcNum - 1].bit_len[1] += CodeLen * 8;				

			}
		}
	    else if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)&&(1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg))
	    {
			/* 这么判断是否完备，需要在考虑  */
			/* 如果当前包出现了分包，则前一个就一定不会出现分包 */
			if((0 != pSlcPara[SlcNum - 1].bit_len[1]) || (0 != pSlcPara[SlcNum - 1].phy_address[1]))
			{
				/* 一定出现了错误，前面的处理过程中 */
				return MPEG4_FAIL;
			}

			pSlcPara[SlcNum - 1].bit_len[0] += CodeLen * 8;
			pSlcPara[SlcNum - 1].phy_address[1] = pCtx->stCurPacket.StreamPack[1].PhyAddr;
			pSlcPara[SlcNum - 1].bit_len[1] = pCtx->stCurPacket.StreamPack[1].LenInByte * 8;
		}
		else
		{
            dprint(PRN_ERROR," line %d packet is wrong!\n",__LINE__);
            return MPEG4_FAIL;
		}
	}
	else
	{
        dprint(PRN_ERROR," line %d packet is wrong!\n",__LINE__);
        return MPEG4_FAIL;
	}

    return MPEG4_OK;
}

/* 非短头码流slice 解析 */
SINT32 Mp4_Syntax_Slice_NotSH(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    UINT32 JmpOverBits = 0;
    UINT32 MbCnt = 0;
    UINT32 WidthInMb  = 0;
    UINT32 HeightInMb = 0;
    UINT32 BitNumofMbCnt = 0;
    UINT32 Code = 0;
    SINT32 BitUsed = 0x0;
    BS local_bs;
    MP4_SLICE_INFO *pSlcPara = NULL;
    
    if(pCtx->Mp4DecParam.SlcNum < 1 || pCtx->Mp4DecParam.SlcNum >= MAX_SLICE_NUM_IN_VOP)
    {
        MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));
        MP4_ClearCurPic(pCtx);
        pCtx->PicIntegrality &= ~MP4_PIC_OK;
        dprint(PRN_ERROR,"FUN: %s Invalid SlcNum = %d\n",__FUNCTION__,pCtx->Mp4DecParam.SlcNum);
        return BitUsed;
    }

    pSlcPara = &(pCtx->Mp4DecParam.SlcPara[pCtx->Mp4DecParam.SlcNum]);

    /* slice num 个数增加 */
    pCtx->Mp4DecParam.SlcNum++;

    // 1. jump over start code
    JmpOverBits = SLICE_START_CODE_BASE_LEN + pCtx->ScdUpMsg.StartCodeLength;
    BsInit(&local_bs, ptr, len);
    BsSkip(&local_bs, JmpOverBits);

    // 2. parse data
    WidthInMb  = (pCtx->MP4Syntax.image_width + 15) >> 4;
    HeightInMb = (pCtx->MP4Syntax.image_height + 15) >> 4;
    MbCnt = WidthInMb * HeightInMb;
    BitNumofMbCnt = log2bin(MbCnt);
    pSlcPara->mb_start_num = BsGet(&local_bs, BitNumofMbCnt);
	if(pSlcPara->mb_start_num > (MbCnt-1))
	{
	    dprint(PRN_ERROR," pSlcPara->mb_start_num = %d, MbCnt = %d\n", pSlcPara->mb_start_num, MbCnt);
		return MPEG4_FAIL;
	}
    pSlcPara->vop_quant = BsGet(&local_bs, 5);
    Code = BsGet(&local_bs, 1);
    if (Code)
    {
        do
        {
            /*modulo_time_base*/
            Code = BsGet(&local_bs, 1);
        }
        while (0 != Code);

        /*skip bit_num_of_voptimeincrement*/
        BsSkip(&local_bs, 1);
        if (pCtx->MP4Vol.vop_time_incr_bits)
        {
            BsSkip(&local_bs, pCtx->MP4Vol.vop_time_incr_bits);
        }

        /*markerbit */
        BsSkip(&local_bs, 1);
        pSlcPara->vop_coding_type  = BsGet(&local_bs, 2);
        pSlcPara->intra_dc_vlc_thr = BsGet(&local_bs, 3);

        if (I_VOP != pSlcPara->vop_coding_type)
        {
            BsSkip(&local_bs, 3);
        }

        if (B_VOP == pSlcPara->vop_coding_type)
        {
            BsSkip(&local_bs, 3);
        }
    }
    else /*use vop info*/
    {
        pSlcPara->vop_coding_type  = pCtx->MP4Vop.vop_coding_type;
        pSlcPara->intra_dc_vlc_thr = pCtx->MP4Vop.intra_dc_vlc_thr;
    }

    pSlcPara->vop_fcode_forward  = pCtx->MP4Vop.vop_fcode_forward;
    pSlcPara->vop_fcode_backward = pCtx->MP4Vop.vop_fcode_backward;

	pCtx->PicIntegrality |= MP4_FOUND_SLCHDR;

    /* 记录slice码流信息 */
    BitUsed = BsPos(&local_bs);
	pSlcPara->bit_len[0] = len * 8 - BitUsed;
	pSlcPara->bit_offset[0] = pCtx->BitsObj.offset + (BitUsed%8);
	pSlcPara->phy_address[0] = pCtx->BitsObj.phy_addr + (BitUsed/8);

	/* 如果出现分包，这记录另一包的信息*/
	if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)&& (1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg) )
	{
		pSlcPara->bit_len[1] = pCtx->stCurPacket.StreamPack[1].LenInByte * 8;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = pCtx->stCurPacket.StreamPack[1].PhyAddr;
	}
	else
	{
		pSlcPara->bit_len[1] = 0;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = 0;
	}
    MP4_Record_SlcSegID(pCtx);

    return BitUsed;
}


/* 短头码流slice 解析 */
SINT32 Mp4_Syntax_Slice_SH(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    UINT32 JmpOverBits = 0;
    SINT32 BitUsed = 0x0;
    BS local_bs;
    MP4_SLICE_INFO *pLastSlcPara = NULL;
    MP4_SLICE_INFO *pSlcPara = NULL;
    UINT32 totalMbMin1 = 0;

    /* 如果vop没有正确解析，则后面的slice不解 */
    if(pCtx->Mp4DecParam.SlcNum < 1 || pCtx->Mp4DecParam.SlcNum >= MAX_SLICE_NUM_IN_VOP)
    {
        MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));
        MP4_ClearCurPic(pCtx);
        pCtx->PicIntegrality &= ~MP4_PIC_OK;
        dprint(PRN_ERROR,"FUN: %s Invalid SlcNum = %d\n",__FUNCTION__,pCtx->Mp4DecParam.SlcNum);
        return BitUsed;
    }
    
    pLastSlcPara = &(pCtx->Mp4DecParam.SlcPara[pCtx->Mp4DecParam.SlcNum - 1]);
    pSlcPara = &(pCtx->Mp4DecParam.SlcPara[pCtx->Mp4DecParam.SlcNum]);
    /* slice num 个数增加 */
    pCtx->Mp4DecParam.SlcNum++;

	// 1. jump over start code
    JmpOverBits = SLICE_START_CODE_BASE_LEN + pCtx->ScdUpMsg.StartCodeBitOffset;
	BsInit(&local_bs, ptr, len);
    BsSkip(&local_bs, JmpOverBits);

	// 2. parse data
	/*flush gob resyncmark	*/
	pSlcPara->mb_start_num = BsGet(&local_bs, 5) * pCtx->MP4Vop.num_mb_ingob;
	totalMbMin1 = pCtx->Mp4DecParam.PicHeightInMb*pCtx->Mp4DecParam.PicWidthInMb - 1;
	if(pSlcPara->mb_start_num > totalMbMin1)
	{
	    dprint(PRN_ERROR,"pSlcPara->mb_start_num = %d, totalMbMin1 = %d\n",pSlcPara->mb_start_num, totalMbMin1);
		return MPEG4_FAIL;
	}
	/*skip gob_frame_id*/
	BsSkip(&local_bs, 2);
	pSlcPara->vop_quant = BsGet(&local_bs, 5);

    //用vop级信息
	pSlcPara->vop_coding_type  = pCtx->MP4Vop.vop_coding_type;
	pSlcPara->intra_dc_vlc_thr = pCtx->MP4Vop.intra_dc_vlc_thr;    
	pSlcPara->vop_fcode_forward  = pCtx->MP4Vop.vop_fcode_forward;
	pSlcPara->vop_fcode_backward = pCtx->MP4Vop.vop_fcode_backward;

    /* 记录slice码流信息 */
	BitUsed = BsPos(&local_bs);
	pSlcPara->bit_len[0] = len * 8 - BitUsed; 
	pSlcPara->bit_offset[0] = pCtx->BitsObj.offset + (BitUsed%8);
	pSlcPara->phy_address[0] = pCtx->BitsObj.phy_addr + (BitUsed/8);

	pCtx->PicIntegrality |= MP4_FOUND_SLCHDR;

	/* 如果出现分包，这记录另一包的信息*/
	if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)&& (1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg) )
	{
		pSlcPara->bit_len[1] = pCtx->stCurPacket.StreamPack[1].LenInByte * 8;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = pCtx->stCurPacket.StreamPack[1].PhyAddr;
	}
	else
	{
		pSlcPara->bit_len[1] = 0;
        pSlcPara->bit_offset[1] = 0;
		pSlcPara->phy_address[1] = 0;
	}

    /* 重新设置下上一个slice的长度，这个由于非字节对齐所产生的，考虑分包的情况 */
    if((0 != pLastSlcPara->phy_address[1]) && (0 != pLastSlcPara->bit_len[1]))
    {
        pLastSlcPara->bit_len[1] += pCtx->ScdUpMsg.StartCodeBitOffset;
    }
    else
    {
        pLastSlcPara->bit_len[0] += pCtx->ScdUpMsg.StartCodeBitOffset;
    }
    MP4_Record_SlcSegID(pCtx);

	return BitUsed;
}

SINT32 MP4_Check_StreamType(MP4_CTX_S *pCtx, UINT32 *StartCode)
{
    SINT32 ret = MPEG4_OK;
    MP4_SCD_UPMSG  *pScdUpMsg = &pCtx->ScdUpMsg;

    if(0 == pScdUpMsg->IsShStreamFlag)
    {
        pCtx->MP4Syntax.is_short_header = NON_SHORT_HEADER_ID;
        
        /* 这里需要判断是短头还是非短头，因为非短头的码流的假slice起始码可能恰好等于短头的起始码，这时sliceflag
           标志会是零，在语法判断时会出错, 0x000080xx ~ 0x000083xx*/
        if((((*StartCode)>>8) >= 0x80) && (((*StartCode)>>8) <= 0x83))
        {
            pCtx->ScdUpMsg.SliceFlag = 1;
        }
    }
    else
    {
        *StartCode = SHORT_HEADER;
        pCtx->MP4Syntax.is_short_header = SHORT_HEADER_ID;
    }

    return ret;
}

SINT32 MP4_Dec_Slice(MP4_CTX_S *pCtx, UINT8* ptr, SINT32 len)
{
    SINT32 ret;
    MP4_SCD_UPMSG   *pScdUpMsg = &(pCtx->ScdUpMsg);
    SINT32 BitUsed = 0;

    /* 非短头码流 */
    if(0 == pScdUpMsg->IsShStreamFlag)
    {
        if(MPEG4_OK == Mp4_Check_Slice_NotSH(pCtx))
        {
            /* 解析非短头slice */
            BitUsed =Mp4_Syntax_Slice_NotSH(pCtx, ptr, len);
			if(MPEG4_FAIL == BitUsed)
			{
				/* 释放当前包码流 */ 
                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket)); 
                dprint(PRN_ERROR,"FUN: %s MP4_ClearCurPacket\n",__FUNCTION__);
			}
        }
        else
        {
            /* 非slice即码流数据，则需进行数据拼接 */
            ret = Mp4_Combine_SliceData(pCtx, len);
            if(MPEG4_OK != ret)
            {
                /* 释放当前包码流 */ 
                MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket)); 
                dprint(PRN_ERROR,"FUN: %s MP4_ClearCurPacket\n",__FUNCTION__);
            }
            else
            {
                MP4_Record_SlcSegID(pCtx);
            }
        }
    }
    else
    {
        /* 短头码流，收到了非短头的slice，自行计算bit内偏移 */
        if((0 == pScdUpMsg->IsShortHeader) && (1 <= pScdUpMsg->StartCodeLength) && (pScdUpMsg->StartCodeLength <= 7))
        {
            pScdUpMsg->StartCodeBitOffset = pScdUpMsg->StartCodeLength;
        }
        BitUsed = Mp4_Syntax_Slice_SH(pCtx, ptr, len);
		if(MPEG4_FAIL == BitUsed)
		{
			/* 释放当前包码流 */ 
            MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket)); 
            dprint(PRN_ERROR,"FUN: %s MP4_ClearCurPacket\n",__FUNCTION__);
		}
    }

    return 0;
}

VOID MP4_Record_SlcSegID(MP4_CTX_S *pCtx)
{
    UINT32 *pStreamID = &(pCtx->StreamID[pCtx->StreamIDNum]); 

    /* 出现这种情况，肯定是某种异常的情况 */
    if(pCtx->StreamIDNum > (MAX_SEG_NUM_IN_VOP-2))
    {
        MP4_Clean_HeadPacket(pCtx);
        MP4_ClearCurPic(pCtx);
        MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));
        dprint(PRN_FATAL,"StreamIDNum = %d > (%d)\n",pCtx->StreamIDNum,MAX_SEG_NUM_IN_VOP - 2);
        return;
    }

    /* 记录第一片码流的ID */
    *pStreamID = pCtx->stCurPacket.StreamPack[0].StreamID;
    pCtx->StreamIDNum++;

    /* 如果有第二片码流，则记录第二片码流的ID */
    if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg) && (1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg))
    {
        pStreamID = &(pCtx->StreamID[pCtx->StreamIDNum]); 
        *pStreamID = pCtx->stCurPacket.StreamPack[1].StreamID;
        pCtx->StreamIDNum++;
    }
    
    return;
}

VOID MP4_Record_HeadPacketInfo(MP4_CTX_S *pCtx, UINT32 StartCode)
{
    DEC_STREAM_PACKET_S *pstPacket = NULL;
    MP4_SCD_UPMSG *pScdUpMsg = NULL;

    if(NULL == pCtx)
    {
        dprint(PRN_ERROR,"pCtx is NUL!!!\n");
        return;
    }

    /* 初始化 */
    pstPacket = &(pCtx->stHdPktInfo.stLastPacket);
    pScdUpMsg = &(pCtx->stHdPktInfo.stScdUpMsg);
    
    /* 只要是非slice的头信息，都记录下来，且这是不释放码流包 */
    memcpy(pstPacket, &(pCtx->stCurPacket), sizeof(DEC_STREAM_PACKET_S));   

    /* 记录UpMsg */
    memcpy(pScdUpMsg, &(pCtx->ScdUpMsg), sizeof(MP4_SCD_UPMSG));

    /* 记录头信息 */
    pCtx->stHdPktInfo.HeadCode = StartCode;

    /* 记录当前包的码流信息 */
    if(0 == pCtx->stHdPktInfo.GetHeadFirstFlag)
    {
        MP4_Record_PacketID(pCtx);
        pCtx->stHdPktInfo.GetHeadFirstFlag = 1;
    }
    pCtx->stHdPktInfo.CountVopNum++;

    return;
}

VOID MP4_Clean_HeadPacket(MP4_CTX_S *pCtx)
{
    SINT32 i;
    SINT32 ChanID = pCtx->ChanID;
    SINT32 StreamIDNum = pCtx->stHdPktInfo.StreamIDNum;

    StreamIDNum = MIN(StreamIDNum, MAX_PKT_NUM_IN_HD);
    /* 清除掉所有头包码流信息 */
    for(i = 0; i < StreamIDNum; i++)
    {
        SM_ReleaseStreamSeg(ChanID, pCtx->stHdPktInfo.StreamId[i]);
    }

    /* 初始化所有信息 */
    memset(&(pCtx->stHdPktInfo), 0, sizeof(MP4_HDPKT_INFO_S));

    return;
}

SINT32 MP4_Check_CurPacket(MP4_CTX_S *pCtx)
{
    BS local_bs;
    UINT32 StartCode = 0x0;
    SINT32 ret = MPEG4_OK;

    Bits_Init(&pCtx->BitsObj, &(pCtx->stCurPacket));
    BsInit(&local_bs, pCtx->BitsObj.vir_addr, pCtx->BitsObj.len);
    StartCode = BsShow(&local_bs, 32);

    /* 修正SliceFlag标志 */
    MP4_Check_StreamType(pCtx, &StartCode);
    
    /* 当前头是SLICE头,短头暂时不处理 */
    if(1 == pCtx->ScdUpMsg.SliceFlag)
    {
        /* vop 头需要进行特殊处理 */
    	if((VOP_START_CODE == pCtx->stHdPktInfo.HeadCode) || 
           (SHORT_HEADER == StartCode))
    	{
            if((SYN_VOPOK == pCtx->MP4SyntaxState.vop_decode_right) || 
               (SHORT_HEADER == StartCode))
            {
                /* 如果 vop_decode_right 已经OK，那就不需要再这里真假SLICE头了，
                因为在这里判断会导致帧的完备性出现误判，这种情况让它自行到SLICE
                CHECK 那里去判断 */				
			    if ((1 == pCtx->stHdPktInfo.GetHeadFirstFlag)&&
					(VOP_START_CODE == pCtx->stHdPktInfo.HeadCode) && 
					(4 == pCtx->stHdPktInfo.stLastPacket.StreamPack[0].LenInByte))
			    {
	                /* 说明是因为码流不足导致的, 更新相关信息 */
	                ret = MP4_Renew_CurPacket(pCtx);
				}			
            }
            else
            {
                /* 说明是因为码流不足导致的, 更新相关信息 */
                ret = MP4_Renew_CurPacket(pCtx);
            }
        }
        else
        {
            /* 更新相关信息 */
            ret = MP4_Renew_CurPacket(pCtx);
        }
     }
     else
     {
         /* 清除码流信息(非vop头),vop头信息不能清，因为它包含有slice的信息,
            码流出错的情况下，很可能出现误判，需要清前一个VOP的信息*/
        if(((VOP_START_CODE != pCtx->stHdPktInfo.HeadCode) && (SHORT_HEADER != StartCode))
            || ((VOP_START_CODE == pCtx->stHdPktInfo.HeadCode) && (VOP_START_CODE == StartCode) && (pCtx->stHdPktInfo.CountVopNum>=2 ))
            || ((SHORT_HEADER == pCtx->stHdPktInfo.HeadCode) && (SHORT_HEADER == StartCode) && (pCtx->stHdPktInfo.CountVopNum>=2 )))
        {
            MP4_Clean_HeadPacket(pCtx);
        }
     }

     if((NULL != pCtx->stCurPacket.StreamPack[0].VirAddr) 
        && (0 != pCtx->stCurPacket.StreamPack[0].PhyAddr))
     {
         return ret;
     }
     else
     {
        return MPEG4_FAIL;
     }
}

VOID MP4_Record_PacketID(MP4_CTX_S *pCtx)
{
    UINT32 *pStreamID = &(pCtx->stHdPktInfo.StreamId[pCtx->stHdPktInfo.StreamIDNum]); 

    /* 出现这种情况，肯定是某种异常的情况 */
    if(pCtx->stHdPktInfo.StreamIDNum > (MAX_PKT_NUM_IN_HD - 2))
    {
        MP4_Clean_HeadPacket(pCtx);
        MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));
        dprint(PRN_FATAL,"StreamIDNum = %d > (%d)\n",pCtx->stHdPktInfo.StreamIDNum,MAX_PKT_NUM_IN_HD - 2);
        return;
    }
    
    /* 记录第一片码流的ID */
    *pStreamID = pCtx->stCurPacket.StreamPack[0].StreamID;
    pCtx->stHdPktInfo.StreamIDNum++;

    /* 如果有第二片码流，则记录第二片码流的ID */
    if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg) && 
        (1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg))
    {
        pStreamID = &(pCtx->stHdPktInfo.StreamId[pCtx->stHdPktInfo.StreamIDNum]); 
        *pStreamID = pCtx->stCurPacket.StreamPack[1].StreamID;
        pCtx->stHdPktInfo.StreamIDNum++;
    }
    
    return ;
}


SINT32 MP4_Combine_HdPacket(MP4_CTX_S *pCtx)
{
    DEC_STREAM_PACKET_S *pLastPacket = &(pCtx->stHdPktInfo.stLastPacket);

    if(NULL == pLastPacket->StreamPack[0].VirAddr)
    {
        REPORT_SE_ERR(pCtx->ChanID);
        dprint(PRN_ERROR,"pLastPacket->StreamPack[0].VirAddr is NULL!!\n");
        return MPEG4_FAIL;
    }

    /* 分包的情况在连续进来的两包之间只可能存在其中一包里出现 */
    if(1 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)
    {
        /* 当前包没有出现分包时，很可能上一包出现了分包，得判断下 */
        if(1 == pLastPacket->StreamPack[0].IsLastSeg)
        {
            if(pCtx->stCurPacket.StreamPack[0].PhyAddr < pLastPacket->StreamPack[0].PhyAddr)
            {
                /* 出现了分包 */
                memcpy(&(pLastPacket->StreamPack[1]), &(pCtx->stCurPacket.StreamPack[0]),sizeof(STREAM_SEG_S));
                pLastPacket->StreamPack[0].IsLastSeg = 0;
                pLastPacket->StreamPack[1].IsLastSeg = 1;
            }
            else
            {
                pLastPacket->StreamPack[0].LenInByte += pCtx->stCurPacket.StreamPack[0].LenInByte;
            }
        }
        else if((0 == pLastPacket->StreamPack[0].IsLastSeg) &&
                (1 == pLastPacket->StreamPack[1].IsLastSeg))
        {
            pLastPacket->StreamPack[1].LenInByte += pCtx->stCurPacket.StreamPack[0].LenInByte;
        }
        else
        {
            dprint(PRN_ERROR," line %d packet is wrong!\n",__LINE__);
            return MPEG4_FAIL;
        }
    }
    else if((0 == pCtx->stCurPacket.StreamPack[0].IsLastSeg)&&
            (1 == pCtx->stCurPacket.StreamPack[1].IsLastSeg))
    {
        pLastPacket->StreamPack[0].LenInByte += pCtx->stCurPacket.StreamPack[0].LenInByte;
        memcpy(&(pLastPacket->StreamPack[1]),&(pCtx->stCurPacket.StreamPack[1]),sizeof(STREAM_SEG_S));
    }
    else
    {
        dprint(PRN_ERROR," line %d packet is wrong!\n",__LINE__);
        return MPEG4_FAIL;
    }
    
    return MPEG4_OK;
}

SINT32 MP4_Renew_CurPacket(MP4_CTX_S *pCtx)
{
    SINT32 ret;
    /* 合并Packet码流 */ 
    ret = MP4_Combine_HdPacket(pCtx);
    if(MPEG4_FAIL == ret)
    {
        MP4_ClearCurPacket(pCtx->ChanID, &(pCtx->stCurPacket));
        dprint(PRN_ERROR,"line %d MP4_Combine_HdPacket failed!!\n",__LINE__);
        return MPEG4_FAIL;
    }
    
    /* 更新curPacket前得记录STREAM ID */
    MP4_Record_PacketID(pCtx);
    
    /*合并完了之后，需要重新赋值给 curPacket*/
    memcpy(&(pCtx->stCurPacket), &(pCtx->stHdPktInfo.stLastPacket),sizeof(DEC_STREAM_PACKET_S));
    
    /*合并完了之后，需要重新赋值给 upMsg，该值是第一头信息对应的信息*/
    memcpy(&(pCtx->stCurPacket.StreamPack[0].stMp4UpMsg), &(pCtx->stHdPktInfo.stScdUpMsg),sizeof(MP4_SCD_UPMSG));

    return MPEG4_OK;
}

UINT32 MPEG4DEC_GetImageWidth(MP4_CTX_S *pCtx)
{
    UINT32 uImageWidth = 0;

    uImageWidth = pCtx->MP4Syntax.image_width;

    return uImageWidth;
}

UINT32 MPEG4DEC_GetImageHeight(MP4_CTX_S *pCtx)
{
    UINT32 uImageHeigth = 0;

    uImageHeigth = pCtx->MP4Syntax.image_height;

	
    return uImageHeigth;
}

#endif //__MPEG4_C__
