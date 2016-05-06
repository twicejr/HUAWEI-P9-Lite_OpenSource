/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r3zBp2wTlmjopD1nGe6wtQi8vfawXyR7jn0qhgc/kR0/dxwc1PwR5D7lQIq7zGsDgnVi7
/zJFwn2kTFJnA2p8v30cy26DvGf61P0ZGDntkLfSgP1oeHpHpJHT6DES8ITdjQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
 /***********************************************************************
*
* Copyright (c) 2007 HUAWEI - All Rights Reserved
*
* File: $mpeg2.c$
* Date: $2007/01/24$
* Revision: $v1.0$
* Purpose: MPEG2 standard vfmw interface.
*
* Change History:
*
* Date                       Author                          Change
* ====                       ======                          ====== 
* 2007/01/24                  y62639                          Original
*
*
* Dependencies:
* Linux OS
*
************************************************************************/

#include    "syntax.h"
#include    "mpeg2.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"

#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


#ifdef MPEG2_ENABLE

#define MP2_CLEARREFFLAG do{\
    IMAGE *pImg;\
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->BwdFsID);\
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
        FSP_ClearLogicFs(pCtx->ChanID, pMp2CodecInfo->BwdFsID, 1);\
        FSP_ClearLogicFs(pCtx->ChanID, pMp2CodecInfo->FwdFsID, 1);\
        pMp2CodecInfo->FwdFsID = 0; \
        pMp2CodecInfo->BwdFsID = 0; \
    }\
}while(0)

#define MP2_CLEARREFNUM do{pMp2CodecInfo->RefNum=0;}while(0)
#define MP2_ATTACHUDINF(dst,src) {if(0!=(src)){(dst)=(src);(src)=0;}}


//UINT32 intra_quantizer_matrix[MPEG2_BLOCK_SIZE];
//UINT32 non_intra_quantizer_matrix[MPEG2_BLOCK_SIZE];

UINT8 default_intra_quantizer_matrix[MPEG2_BLOCK_SIZE] =
{
    8, 16, 19, 22, 26, 27, 29, 34,
   16, 16, 22, 24, 27, 29, 34, 37,
   19, 22, 26, 27, 29, 34, 34, 38,
   22, 22, 26, 27, 29, 34, 37, 40,
   22, 26, 27, 29, 32, 35, 40, 48,
   26, 27, 29, 32, 35, 40, 48, 58,
   26, 27, 29, 34, 38, 46, 56, 69,
   27, 29, 35, 38, 46, 56, 69, 83
};

UINT8 zigzag[MPEG2_BLOCK_SIZE] =
{
    0, 1, 8,16, 9, 2, 3,10,17,24,32,25,18,11, 4, 5,
   12,19,26,33,40,48,41,34,27,20,13, 6, 7,14,21,28,
   35,42,49,56,57,50,43,36,29,22,15,23,30,37,44,51,
   58,59,52,45,38,31,39,46,53,60,61,54,47,55,62,63
};

#define RESERVED (0xffffffff)

static UINT32 frame_rate_Table[16] = 
{
    0, 
    24000*1024/1001, 
    24*1024,
    25*1024, 
    30000*1024/1001, 
    30*1024, 
    50*1024,
    60000*1024/1001, 
    60*1024,
    
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED
};

static UINT32 tab_for_first_4bit[16][2] =   //for value 1 ~5
{
   {8,4},{9,5},{5,4}, {4,4},{3,3},{3,3},{2,3},{2,3},
   {1,1},{1,1},{1,1}, {1,1},{1,1},{1,1},{1,1},{1,1},
};
/*
static UINT32 tab_for_second_4bit[16][2] =  //for value 8~15
{
  {0, 0},{0, 0},{0, 0}, {33,11},{20,11},{19, 10}, {15,8},{14,8},
  {13,8},{12,8},{11,8}, {10, 8},{9 , 7},{9,   7}, {8, 7},{8, 7},
};

static UINT32 tab_for_last_3bit[8][2] =   //for value 20~25
{
  {25, 11},{24, 11}, {23, 11},{22, 11},{21, 10}, {21, 10},{20, 10},{20, 10}
};
*/

static UINT32 tab_for_last_7bit[104][2] =
{
  {33,11}, {32,11}, {31,11}, {30,11}, {29,11}, {28,11}, {27,11}, {26,11},
  {25,11}, {24,11}, {23,11}, {22,11}, {21,10}, {21,10}, {20,10}, {20,10},
  {19,10}, {19,10}, {18,10}, {18,10}, {17,10}, {17,10}, {16,10}, {16,10},
  {15,8},  {15,8},  {15,8},  {15,8},  {15,8},  {15,8},  {15,8},  {15,8},
  {14,8},  {14,8},  {14,8},  {14,8},  {14,8},  {14,8},  {14,8},  {14,8},
  {13,8},  {13,8},  {13,8},  {13,8},  {13,8},  {13,8},  {13,8},  {13,8},
  {12,8},  {12,8},  {12,8},  {12,8},  {12,8},  {12,8},  {12,8},  {12,8},
  {11,8},  {11,8},  {11,8},  {11,8},  {11,8},  {11,8},  {11,8},  {11,8},
  {10,8},  {10,8},  {10,8},  {10,8},  {10,8},  {10,8},  {10,8},  {10,8},
  {9,7},   {9,7},   {9,7},   {9,7},   {9,7},   {9,7},   {9,7},   {9,7},
  {9,7},   {9,7},   {9,7},   {9,7},   {9,7},   {9,7},   {9,7},   {9,7},
  {8,7},   {8,7},   {8,7},   {8,7},   {8,7},   {8,7},   {8,7},   {8,7},
  {8,7},   {8,7},   {8,7},   {8,7},   {8,7},   {8,7},   {8,7},   {8,7}
};

//MPEG2 VFWM函数
SINT32 MP2_VerifyMemPara(VOID);
UINT32 MP2_ArrangeVHBMem(MP2_CTX_S *pCtx, SINT32 ImageNum);
SINT32 MP2_GetHDR(MP2_CTX_S *pCtx);
UINT32 MP2_DecodingDecide(MP2_CTX_S *pCtx);
UINT32 MP2_GetPictureInfo(MP2_CTX_S *pCtx);
VOID MP2_GetSequenceInfo(MP2_CTX_S *pCtx);
SINT32 MP2_DecNewPic(MP2_CTX_S *pCtx);
VOID MP2_SetImgFormat(MP2_CTX_S *pCtx);
SINT32 MP2_SearchStartCode( UINT8* pCode, SINT32 CodeLen);
VOID MP2_ProtocolPPSCheck(MP2_CTX_S *pCtx);
UINT32 MP2_GetImageBuffer(MP2_CTX_S *pCtx, MP2VOBUFINF **p_vobuf);
VOID MP2_SetVDMInf(MP2_CTX_S *pCtx);
VOID MP2_StartVDMDec(VOID);
SINT32 MP2_CheckVDM(VOID);
VOID MP2_RecordVFMWState(MP2_CTX_S *pCtx);
//SINT32 MP2_GetUsrData(MP2_CTX_S *pCtx, VDEC_USRDAT_S **pp_UD);
SINT32 MP2_GetUsrData(MP2_CTX_S *pCtx);
SINT32 GetSliceHdr(MP2_CTX_S*  pCtx);

UINT32 next_start_code(MP2_CTX_S *pCtx);
UINT32 sequence_header(MP2_CTX_S *pCtx);
VOID group_of_pictures_header(MP2_CTX_S *pCtx);
UINT32 picture_header(MP2_CTX_S *pCtx);
VOID sequence_extension(MP2_CTX_S *pCtx);
VOID sequence_display_extension(MP2_CTX_S *pCtx);
VOID quant_matrix_extension(MP2_CTX_S *pCtx);
VOID sequence_scalable_extension(MP2_CTX_S *pCtx);
VOID picture_display_extension(MP2_CTX_S *pCtx);
VOID picture_coding_extension(MP2_CTX_S *pCtx);
VOID picture_spatial_scalable_extension(MP2_CTX_S *pCtx);
VOID picture_temporal_scalable_extension(MP2_CTX_S *pCtx);
UINT32 extra_bit_information(MP2_CTX_S *pCtx);
VOID copyright_extension(MP2_CTX_S *pCtx);
UINT32 extension(MP2_CTX_S *pCtx);
SINT32 MP2_ReceivePacket(MP2CODECINF *pMp2CodecInfo, DEC_STREAM_PACKET_S *pPacket, SINT32 ChanID);
VOID MP2_ClearCurPacket(SINT32 ChanID, MP2_STREAM_PACKET *pMp2Packet);
VOID MP2_ClearCurPic(MP2_CTX_S *pCtx);
SINT32 MP2_DecSlice(MP2_CTX_S *pCtx, UINT32 code);
SINT32 MP2_GetFirstMbInSlice( MP2_SLCINFO_S *pSlcInfo);
SINT32 MP2_DecSliceHeader(MP2_SLCINFO_S *pSlcInfo);
UINT32 MP2_u_v(BS *pBs, UINT32 LenInBits, SINT8 *SeTraceString);
SINT32 MP2_InitMb(MP2_SLCINFO_S *pSlcInfo);
VOID MP2_ExitMb(MP2_SLCINFO_S *pSlcInfo);
SINT32  MP2_WriteSliceInfo(MP2_CTX_S *pCtx);
UINT32 MP2_MbAddrInc(BS *pBs);

SINT32 MP2_VerifyMemPara(VOID)
{
    return MPEG2_TRUE;
}


/*!
************************************************************************
*    函数原型 :  MP2_ArrangeVHBMem()
*    功能描述 :  分配消息池和帧存空间并初始化管理帧存的队列
*    参数说明 :  ImageNum 需要分配的帧存
*    返回值   :  0: 分配失败 1: 分配成功
************************************************************************
*/
UINT32 MP2_ArrangeVHBMem(MP2_CTX_S *pCtx, SINT32 ImageNum)
{
    SINT32 Ret, UsedMemSize;
    MP2CODECINF *pMp2CodecInfo;
    MP2SYNTAXINF *pSyntaxInfNew;
    FSP_INST_CFG_S  FspInstCfg;
    SINT32 PicWidth, PicHeight, DecFsNum, DispFsNum, PmvNum;
	
    pMp2CodecInfo = &pCtx->CodecInfo;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    if( pSyntaxInfNew->horizontal_size < 32 || pSyntaxInfNew->vertical_size < 32 )
    {
        dprint(PRN_FATAL, "image size abnormal(%dx%d)\n", pSyntaxInfNew->horizontal_size, pSyntaxInfNew->vertical_size );
        return MPEG2_FALSE;
    }

    if ((pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION)&&(pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0))
    {
        if (pSyntaxInfNew->horizontal_size > pCtx->pstExtraData->stChanOption.s32MaxWidth || pSyntaxInfNew->vertical_size > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "mp2 actual frame size(%dx%d) exeed max config(%dx%d)\n", pSyntaxInfNew->horizontal_size, pSyntaxInfNew->vertical_size,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);
			
			return MPEG2_FALSE;
		}
		
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        PicWidth  = pCtx->pstExtraData->stChanOption.s32MaxWidth;
        PicHeight = pCtx->pstExtraData->stChanOption.s32MaxHeight;
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
        PicWidth  = pSyntaxInfNew->horizontal_size;
        PicHeight = pSyntaxInfNew->vertical_size;
		DecFsNum = 3;
		PmvNum = 2;
		DispFsNum = 5;		
	}
	else
	{
        if (pSyntaxInfNew->horizontal_size > pCtx->pstExtraData->stChanOption.s32MaxWidth || pSyntaxInfNew->vertical_size > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "mp2 actual frame size(%dx%d) exeed max config(%dx%d)\n", pSyntaxInfNew->horizontal_size, pSyntaxInfNew->vertical_size,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);
			
			return MPEG2_FALSE;
		}
	
        PicWidth  = pSyntaxInfNew->horizontal_size;
        PicHeight = pSyntaxInfNew->vertical_size;
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
	
	/* 配置FSP实例，并分割帧存 */
 	if (FSP_OK == FSP_ConfigInstance(pCtx->ChanID, &FspInstCfg))
 	{
        Ret = FSP_PartitionFsMemory(pCtx->ChanID, pCtx->pstExtraData->s32SyntaxMemAddr, 
			        pCtx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
		if (Ret != FSP_OK)
		{
            // 分割帧存失败，返回
            return MPEG2_FALSE;
		}
	}
	else
	{
		dprint(PRN_FATAL, "FSP_ConfigInstance fail!\n");
        // 分割帧存失败，返回
        return MPEG2_FALSE;
	}
	
    return MPEG2_TRUE;
}


/*!
************************************************************************
*    函数原型 :  MP2_GetHDR()
*    功能描述 :  为MPEG2解析码流头
*    参数说明 :  无
*    返回值   :  1:找到SLICE起始码;0:解头时码流消耗过界;-1:找头时码流消耗完毕
************************************************************************
*/
SINT32 MP2_GetHDR(MP2_CTX_S *pCtx)
{
    UINT32 code,ret;
    UINT32 BkStrmIntgrt;
    UINT32 end_code1, end_code2;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    BS  bs_tmp;
    MP2SYNTAXINF *pSyntaxInfNew;
    MP2SYNTAXINF *pSyntaxInfOld;

    ret = MPEG2_FALSE;
    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;
    pSyntaxInfOld = pCtx->pSyntaxInfOld;
    pCtx->IsWaitToDecFlag = 0;
    
    code = BsShow(pBs, 32);
       
    //由于PARSE_OVER时,可能产生错误的参数集信息,因此需要对其进行备份
    BkStrmIntgrt = pMp2CodecInfo->StreamIntegrality;
    pMp2CodecInfo->HDRUsedBits = BsPos(pBs);
    BsSkip(pBs, 32);

    if (SEQUENCE_END_CODE == code)
    {
          memcpy(&bs_tmp, pBs, sizeof(BS));
          end_code1 = (UINT32)BsGet(&bs_tmp, 32);
          end_code2 = (UINT32)BsGet(&bs_tmp, 32);
          if (HISI_STREAM_END_CODE1 == end_code1 && HISI_STREAM_END_CODE2 == end_code2)
          {
          #ifndef SCD_MP4_SLICE_ENABLE  
	       pCtx->IsStreamEndFlag = 1;              // last frame
              return  MPEG2_FALSE;
	   #else
	       if((STATE_GET_SLCHDR == pMp2CodecInfo->HDRState) && ((pMp2CodecInfo->StreamIntegrality & MPEG2_FOUND_SLICE) == MPEG2_FOUND_SLICE))
              {
	            pCtx->IsStreamEndFlag = 1;     
                   pCtx->IsWaitToDecFlag = 1;
                   pMp2CodecInfo->StreamIntegrality |= MPEG2_FOUND_NEXTHDR;
                   pMp2CodecInfo->HDRState = STATE_GET_PICHDR;
                   MP2_ProtocolPPSCheck(pCtx);
                   return MPEG2_TRUE;
              }
		else
		{
	            pCtx->IsStreamEndFlag = 1;     
                   return MPEG2_FALSE;
		}
         #endif	
         }
    }

#ifndef SCD_MP4_SLICE_ENABLE  
    if (((SEQUENCE_HEADER_CODE == code)||(GROUP_START_CODE == code)||(PICTURE_START_CODE == code)||(SEQUENCE_END_CODE == code))
                                && (STATE_GET_SLCHDR == pMp2CodecInfo->HDRState))
    {
        //查SLICE头过程中出现图像级的起始码则表明出现异常
        //应当放弃当前图,重新解析新图像
        pMp2CodecInfo->HDRState = STATE_GET_PICHDR;
        //由于重新解析图像,因此把码流图像级完整性信息清除
        pMp2CodecInfo->StreamIntegrality &= ~(MPEG2_FOUND_PICHDR|MPEG2_FOUND_PICEXT|MPEG2_FOUND_SLICE|MPEG2_FOUND_NEXTHDR);
        REPORT_DECSYNTAX_ERR(pCtx->ChanID);
        return NOTENOUGH_STREAM;
     }
#else
     if(((SEQUENCE_HEADER_CODE == code)||(GROUP_START_CODE == code)||(PICTURE_START_CODE == code)||(SEQUENCE_END_CODE == code))
         && (STATE_GET_SLCHDR == pMp2CodecInfo->HDRState) 
         && (((pMp2CodecInfo->StreamIntegrality & MPEG2_FOUND_SLICE) == MPEG2_FOUND_SLICE)))
     {
         pCtx->IsWaitToDecFlag = 1;
         pMp2CodecInfo->StreamIntegrality |= MPEG2_FOUND_NEXTHDR;
         pMp2CodecInfo->HDRState = STATE_GET_PICHDR;
         MP2_ProtocolPPSCheck(pCtx);
         return MPEG2_TRUE;
     }
#endif	 
     else
     {
         switch (code)
         {
            case SEQUENCE_HEADER_CODE:
                dprint(PRN_DBG, "found sh %#x\n", ((pMp2CodecInfo->Used_byte+pMp2CodecInfo->BsOffset))+((UINT32)BsPos(pBs))/8);
	            sequence_header(pCtx);
                if (BsResidBits(pBs)<0)
                {
                    pMp2CodecInfo->StreamIntegrality = BkStrmIntgrt;
					REPORT_DECSYNTAX_ERR(pCtx->ChanID);
                    MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
                    dprint(PRN_ERROR,"SEQUENCE_HEADER_CODE Bitstream is not enough!\n",code);
                    return NOTENOUGH_STREAM;
                }
                if (0==(pMp2CodecInfo->StreamIntegrality&
                        (MPEG2_ERROR_SEQEXT|
                        MPEG2_ERROR_SEQHDR|
                        MPEG2_ERROR_SEQDISPEXT)))
                {
                    pSyntaxInfNew->valid_flag = MPEG2_TRUE;
                    *pSyntaxInfOld = *pSyntaxInfNew;
                    pMp2CodecInfo->SeqCnt++;
                }
                else if (MPEG2_TRUE == pSyntaxInfOld->valid_flag)
                {
                /*SPS发生错误时,恢复备份的语法信息.由于是在
                        SPS之后马上恢复,即使PPS在恢复时被修改,也没有关系.在
                        后面的解析过程中会获得更新的PPS数据*/
                    *pSyntaxInfNew = *pSyntaxInfOld;
                    //备份恢复后,清除SPS错误标志
                    pMp2CodecInfo->StreamIntegrality &= ~(MPEG2_ALLSEQHDR_ERROR);
                REPORT_DECSYNTAX_ERR(pCtx->ChanID);
                }
	            else
	            {
	                REPORT_DECSYNTAX_ERR(pCtx->ChanID);
	            }
                break;
                    
            case GROUP_START_CODE:
                dprint(PRN_DBG, "found gh %#x\n", ((pMp2CodecInfo->Used_byte+pMp2CodecInfo->BsOffset))+((UINT32)BsPos(pBs))/8);
                group_of_pictures_header(pCtx);
                if(BsResidBits(pBs)<0)
                {
                    pMp2CodecInfo->StreamIntegrality = BkStrmIntgrt;
                    REPORT_DECSYNTAX_ERR(pCtx->ChanID);
                    MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
                    dprint(PRN_ERROR,"GROUP_START_CODE Bitstream is not enough!\n",code);
                    return NOTENOUGH_STREAM;
                }
                break;
                    
            case PICTURE_START_CODE:
                dprint(PRN_DBG, "found ph %#x\n", ((pMp2CodecInfo->Used_byte+pMp2CodecInfo->BsOffset))+((UINT32)BsPos(pBs))/8);
                picture_header(pCtx);
                if (BsResidBits(pBs) < 0)
                {
                    pMp2CodecInfo->StreamIntegrality = BkStrmIntgrt;
                    REPORT_DECSYNTAX_ERR(pCtx->ChanID);
                    MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
                    dprint(PRN_ERROR,"PICTURE_START_CODE Bitstream is not enough!\n",code);
                    return NOTENOUGH_STREAM;
                }
             #ifndef SCD_MP4_SLICE_ENABLE  
                if (//(MPEG2_FOUND_SEQHDR|MPEG2_FOUND_PICHDR) == 
                    (pMp2CodecInfo->StreamIntegrality & (MPEG2_FOUND_SEQHDR|MPEG2_FOUND_PICHDR)))
                {
                    //图像级和序列级头都已找到
                    pMp2CodecInfo->HDRState = STATE_GET_SLCHDR;
                 //   return GetSliceHdr(pCtx);
                 	if(GetSliceHdr(pCtx) == FOUND_SLCHDR)
                 	{
						return MPEG2_TRUE;
					}
					else
					{
						dprint(PRN_ERROR, "line %d get slice header failed!\n",__LINE__);
						return MPEG2_FALSE;
					}
                }
             #endif                
                break;
                    
            case USER_DATA_START_CODE:
            case YXSB_WATERMARK_CODE:
                dprint(PRN_DBG, "found ud %#x\n", ((pMp2CodecInfo->Used_byte+pMp2CodecInfo->BsOffset))+((UINT32)BsPos(pBs))/8);
                ret = MP2_GetUsrData(pCtx);
                if (MPEG2_FALSE == ret)
                {
                    MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
                    dprint(PRN_ERROR, "get usd err\n");
                    REPORT_DECSYNTAX_ERR(pCtx->ChanID);
                    return NOTENOUGH_STREAM;
                }
                else
                {
                    // if can not get pointer of UD, ret error, but here do nothing
                    // to deal with it, just go on decoding remain stream
                    dprint(PRN_ERROR, "cann't get ud pointer\n");
                }
            #ifndef SCD_MP4_SLICE_ENABLE  
                if ( STATE_GET_SLCHDR == pMp2CodecInfo->HDRState )
                {
                 //   return GetSliceHdr(pCtx);
                 	if(GetSliceHdr(pCtx) == FOUND_SLCHDR)
                 	{
						return MPEG2_TRUE;
					}
					else
					{
						dprint(PRN_ERROR, "line %d get slice header failed!\n", __LINE__);
						return MPEG2_FALSE;
					}
                }
            #endif    
                break;
                    
            case EXTENSION_START_CODE:
                dprint(PRN_DBG, "found ext %#x\n", ((pMp2CodecInfo->Used_byte+pMp2CodecInfo->BsOffset))+((UINT32)BsPos(pBs))/8);
                extension(pCtx);
                if (BsResidBits(pBs)<0)
                {
                    pMp2CodecInfo->StreamIntegrality = BkStrmIntgrt;
                    REPORT_DECSYNTAX_ERR(pCtx->ChanID);
                    MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
                    return NOTENOUGH_STREAM;
                }
            #ifndef SCD_MP4_SLICE_ENABLE  
                if( STATE_GET_SLCHDR == pMp2CodecInfo->HDRState )
                {
                 //   return GetSliceHdr(pCtx);
                 	if(GetSliceHdr(pCtx) == FOUND_SLCHDR)
                 	{
						return MPEG2_TRUE;
					}
					else
					{
						dprint(PRN_ERROR, "line %d get slice header failed!\n",__LINE__);
						return MPEG2_FALSE;
					}
                }
            #endif    
                break;
         
            case SEQUENCE_ERROR_CODE:
            case SEQUENCE_END_CODE:
                break;
				
            default:
                if((SLICE_START_CODE_MIN <= code) && (code <= SLICE_START_CODE_MAX))
                {
                    if (MPEG2_FALSE == pMp2CodecInfo->NewSeqInited)
                    {
                        MP2_GetSequenceInfo(pCtx);
                        if(MPEG2_FALSE == pMp2CodecInfo->Imgbuf_allocated || 1 == pCtx->IsWaitToReRange)
                        {
                            return MPEG2_FALSE;
                        }
                    }
                    if (pMp2CodecInfo->StreamIntegrality&(MPEG2_FOUND_SEQHDR|MPEG2_FOUND_PICHDR))
                    {
                        //图像级和序列级头都已找到
                        pMp2CodecInfo->HDRState = STATE_GET_SLCHDR;
                        pMp2CodecInfo->StreamIntegrality |= MPEG2_FOUND_SLICE;
                        if(MPEG2_TRUE == MP2_DecSlice(pCtx, code))
                        {
                            ret = MPEG2_TRUE;
                        }
                        else
                        {
                            /* slice 出错时，丢掉当前的slice */
                            dprint(PRN_ERROR,"MP2_DecSlice is wrong!\n",code);
                            //MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
                        }
                    }
                }
				else
				{
					REPORT_DECSYNTAX_ERR(pCtx->ChanID);
				}
                break;
         }                

     }

    return ret; 
}

SINT32 GetSliceHdr(MP2_CTX_S*  pCtx)
{
    UINT32 /*i, */ret = MPEG2_FALSE, code;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &(pCtx->Bs);
        
    while( MPEG2_TRUE == (ret = next_start_code(pCtx)))
    {
        code = BsShow(pBs, 32);

        pMp2CodecInfo->HDRUsedBits = BsPos(pBs);
        //查找SLICE头
        if (code>0x100 && code<0x1B0)
        {
            if (BsResidBits(pBs) <= 40)
            {
                //图像启动要求码流大于40比特
                ret = NOTENOUGH_STREAM;
                break;
            }
            else
            {
                pMp2CodecInfo->HDRState = STATE_GET_PICHDR;
                ret = FOUND_SLCHDR;
				#if 1
				if (MPEG2_FALSE == pMp2CodecInfo->NewSeqInited)
            	{
                	MP2_GetSequenceInfo(pCtx);
                    if(MPEG2_FALSE == pMp2CodecInfo->Imgbuf_allocated)
                    {
                        return MPEG2_FALSE;
                    }
            	}
				MP2_ProtocolPPSCheck(pCtx);
				#endif

                break;
            }
        }
        else
        {
            BsSkip(pBs, 32);
            ret = SYN_ERR;
        }
    }

    if (SYN_ERR == ret || NOTENOUGH_STREAM == ret)
    {
        REPORT_DECSYNTAX_ERR(pCtx->ChanID);
    }

    return ret;
}


/*!
************************************************************************
*    函数原型 :  MP2_DecodingDecide()
*    功能描述 :  对MPEG2解码器是否解码当前图进行判决
*    参数说明 :  
*    返回值   :  当前图像可以解码返回1,否则返回0
************************************************************************
*/
UINT32 MP2_DecodingDecide(MP2_CTX_S *pCtx)
{
    UINT32 ret = MPEG2_TRUE;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;
	IMAGE *pFwdImg, *pBwdImg;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    #ifdef SCD_MP4_SLICE_ENABLE  	
    if(!(pMp2CodecInfo->StreamIntegrality&(MPEG2_FOUND_NEXTHDR)))
    {
        return NOTENOUGH_STREAM;
    }
    #endif

    /* 统计总帧数 */
	if ( (pSyntaxInfNew->picture_structure==FRAME_PICTURE || pMp2CodecInfo->Second_Field==1) )
	{
        pCtx->numTotalFrame++;
	}

    if (pMp2CodecInfo->StreamIntegrality&(MPEG2_ALLSEQ_ERROR|MPEG2_ERROR_REFHDR|MPEG2_ERROR_REFPIC))
    {
        REPORT_SE_ERR(pCtx->ChanID);
        dprint(PRN_DBG, "ERROR: frm %d, integrality: %#x\n",
            pMp2CodecInfo->Frame_Cnt, pMp2CodecInfo->StreamIntegrality);
        return MPEG2_FALSE;
    }
    else if (MPEG2_FALSE == pMp2CodecInfo->Imgbuf_allocated)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, No Img buffer is allocated\n", pMp2CodecInfo->Frame_Cnt);
        return MPEG2_FALSE;
    }

    /* 解码模式(IPB,IP,I)的处理 */
    if ( (pMp2CodecInfo->UsedDecMode == I_MODE || pMp2CodecInfo->UsedDecMode == DISCARD_MODE) &&
         (pCtx->pstExtraData->s32DecMode == IP_MODE || pCtx->pstExtraData->s32DecMode == IPB_MODE ||
          pCtx->pstExtraData->s32DecMode == DISCARD_B_BF_P_MODE) )
    {
        /* I->IP 或 I->IPB都有可能引发参考错误，所以需要找下一个I帧才行 */
        dprint(PRN_CTRL,"----------------- mp2 Imode -> %d ------------------\n", pCtx->pstExtraData->s32DecMode);
        pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_REFPIC;
        MP2_CLEARREFFLAG;
        MP2_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过
    }
    pMp2CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
    switch (pMp2CodecInfo->UsedDecMode)
    {
        case DISCARD_MODE:
			ret = MPEG2_FALSE;
			break;
        case IP_MODE://IP模式
            if (pSyntaxInfNew->picture_coding_type==B_TYPE)
            {
                /* 20111223: 这种模式下，没有机会进入MP2_GetPictureInfo()函数，Second_Field 
                   的值没有得到轮换更新，故在这里进行轮换更新 */
                if(pSyntaxInfNew->picture_structure != FRAME_PICTURE)
                {
                    pMp2CodecInfo->Second_Field = !pMp2CodecInfo->Second_Field;
                }
                //B图不解
                ret = MPEG2_FALSE;
            }
            break;
        case I_MODE://I模式
            if((pSyntaxInfNew->picture_coding_type==B_TYPE) || (pSyntaxInfNew->picture_coding_type==P_TYPE) )    //  
            {
                /* 是IP场对得解 */
                if((pSyntaxInfNew->picture_coding_type==P_TYPE) && (pMp2CodecInfo->Last_FieldStruct != FRAME_PICTURE) &&
                    (pMp2CodecInfo->LastDecPicCodingType == I_TYPE))
                {
                    ret = MPEG2_TRUE;
                }
                else
                {
                    /* 20111223: 这种模式下，没有机会进入MP2_GetPictureInfo()函数，Second_Field 
                       的值没有得到轮换更新，故在这里进行轮换更新 */
                    if(pSyntaxInfNew->picture_structure != FRAME_PICTURE )
                    {
                        pMp2CodecInfo->Second_Field = !pMp2CodecInfo->Second_Field;
                    }                    
                    ret = MPEG2_FALSE;
                }
            }
            break;
        case DISCARD_B_BF_P_MODE://I模式
            if (pSyntaxInfNew->picture_coding_type==I_TYPE)
            {
                 pCtx->PPicFound = 0;
            }
            
            if ( (pSyntaxInfNew->picture_coding_type==B_TYPE) && (0==pCtx->PPicFound) ) /* 发现B帧 */
            {
                /* 20111223: 这种模式下，没有机会进入MP2_GetPictureInfo()函数，Second_Field 
                   的值没有得到轮换更新，故在这里进行轮换更新 */
                if (pSyntaxInfNew->picture_structure != FRAME_PICTURE )
                {
                    pMp2CodecInfo->Second_Field = !pMp2CodecInfo->Second_Field;
                }                    
                ret = MPEG2_FALSE;
            }
            else if (pSyntaxInfNew->picture_coding_type==P_TYPE) 
            {
                pCtx->PPicFound = 1;
            }
            break;
        default: 
          break;
    }
    //picture head
    dprint(PRN_PIC, "frm %d pic type %d struct is %d total pos %#x\n",
        pMp2CodecInfo->Frame_Cnt, pSyntaxInfNew->picture_coding_type,
        pSyntaxInfNew->picture_structure,
        ((pMp2CodecInfo->Used_byte+pMp2CodecInfo->BsOffset))+((UINT32)BsPos(pBs))/8);
    //解码判决完成后,码流的图像级完整性即可清除,为下一图像解码做准备
    pMp2CodecInfo->StreamIntegrality &= ~(MPEG2_FOUND_PICHDR|MPEG2_FOUND_PICEXT|MPEG2_FOUND_SLICE|MPEG2_FOUND_NEXTHDR);

    /* 允许解只有P帧的码流，未有参考帧时也不丢弃P帧 */
    if (1 == pCtx->pstExtraData->s32SupportAllP)
    {
        if ((pMp2CodecInfo->RefNum<1)&&
           (pSyntaxInfNew->picture_coding_type==B_TYPE))
        {
            //解码非I/非D图而又没有参考图
            dprint(PRN_ERROR, "NOTE: Drop non-I, cur is B\n");
            ret = MPEG2_FALSE;
        }
        else if ((pMp2CodecInfo->RefNum<1)&&
           (pSyntaxInfNew->picture_coding_type==P_TYPE))
        {
            //解码非I/非D图而又没有参考图
            dprint(PRN_ERROR, "NOTE: Drop non-I, cur is P\n");
            /* 全P 帧码流测试 */
            //ret = MPEG2_FALSE;
        }
    }
    else if ((pMp2CodecInfo->RefNum<1)&&
           ((pSyntaxInfNew->picture_coding_type==P_TYPE)||
           (pSyntaxInfNew->picture_coding_type==B_TYPE)))
    {
        //解码非I/非D图而又没有参考图
        dprint(PRN_ERROR, "NOTE: Drop non-I\n");
        ret = MPEG2_FALSE;
    }
    else if ((pMp2CodecInfo->RefNum<2)&&(1)&&(pSyntaxInfNew->picture_coding_type==B_TYPE))
    {
        //don't decode first B pictures when it belong to open GOP
        dprint(PRN_ERROR, "NOTE: Drop B\n");
        ret = MPEG2_FALSE;
    }

    /* 如果是P/B帧，要看其参考帧是否超出参考阈值，若超出则不解 */
	pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->FwdFsID);
	pBwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->BwdFsID);

    if(NULL == pFwdImg || NULL == pBwdImg)
    {
    	dprint(PRN_ERROR, "%s %d pFwdImg = NULL,  pBwdImg = NULL!!\n",__FUNCTION__,__LINE__);
    	return MPEG2_FALSE;
    }
    
	if (pSyntaxInfNew->picture_coding_type==P_TYPE)
	{
        if ( (NULL == pFwdImg) || (pFwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
        {
        	if(NULL == pFwdImg)
          	{
          	   dprint(PRN_ERROR, "fuction return value is null,%s %d !!\n",__FUNCTION__,__LINE__);
			   return MPEG2_FALSE;
          	}
			else
		  	{
		  	    dprint(PRN_ERROR, "dec P frame, fwd ref err(%d) > ref_thr(%d)\n", pFwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
			    return MPEG2_FALSE;
		  	}		
	   }
	}
	else if (pSyntaxInfNew->picture_coding_type==B_TYPE)
	{
        if ( (NULL == pFwdImg) || (pFwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
        {
            dprint(PRN_ERROR, "dec B frame, bwd ref err(%d) > ref_thr(%d)\n", pFwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
			return MPEG2_FALSE;
		}
        
        if ( (NULL == pBwdImg) || (pBwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
        {
            dprint(PRN_ERROR, "dec B frame, fwd ref err(%d) > ref_thr(%d)\n", pBwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
			return MPEG2_FALSE;
		}
	}

    if (MPEG2_FALSE == ret)
    {
        /* 注意!!!  Second_Field在GetPictureInfo中轮换，此时的Second_Field==0恰恰意味着这是第二个场图! */
        if (pSyntaxInfNew->picture_structure==FRAME_PICTURE || pMp2CodecInfo->Second_Field==0)
        {
            if(1 == pSyntaxInfNew->progressive_sequence)
            {
                pMp2CodecInfo->GopHist[3].GopFrmCnt += 
                    (pSyntaxInfNew->repeat_first_field+pSyntaxInfNew->top_field_first+1);
                pMp2CodecInfo->GopHist[3].GopFldCnt = 2 * pMp2CodecInfo->GopHist[3].GopFrmCnt;
            }
            else if(1 == pSyntaxInfNew->progressive_frame)
            {
                //in this case, fld num will not match (2 * frm num)
                pMp2CodecInfo->GopHist[3].GopFrmCnt++; 
                pMp2CodecInfo->GopHist[3].GopFldCnt += 
                    (2+pSyntaxInfNew->repeat_first_field);
            }
            else
            {
                pMp2CodecInfo->GopHist[3].GopFrmCnt++;
                pMp2CodecInfo->GopHist[3].GopFldCnt = 2 * pMp2CodecInfo->GopHist[3].GopFrmCnt;
            }
            pCtx->CodecInfo.GopHist[3].GopFrmCntNoRpt ++;
            pMp2CodecInfo->Frame_Cnt++;
        }

        return MPEG2_FALSE;
    }
    else
    {
        return MPEG2_TRUE;
    }
}
/*****************************************************************************
 函 数 名  : MP2_EstimatePicQp
 功能描述  : Parse the slice header of first slice, get Qp as estimation
             of picture Qp
 输入参数  : BS *pBs  
 输出参数  : 无
 返 回 值  : SINT32
*****************************************************************************/
SINT32 MP2_EstimatePicQp(MP2_CTX_S *pCtx)
{
#ifndef SCD_MP4_SLICE_ENABLE  
    BS Bs = pCtx->Bs;
    SINT32 RemainBytes,IsSliceVertExt;
#else
    MP2_DEC_PARAM_S *pMp2DecParam = &(pCtx->Mp2DecParam);
#endif

    SINT32 QuantScaleCode, QuantScale;
    const UINT32 Non_Linear_quantizer_scale[32] =
    {
        0, 1, 2, 3, 4, 5, 6, 7,
        8,10,12,14,16,18,20,22,
        24,28,32,36,40,44,48,52,
        56,64,72,80,88,96,104,112
    };
#ifndef SCD_MP4_SLICE_ENABLE  
    //parse first slice
    RemainBytes = BsResidBits(&Bs)/8;
    IsSliceVertExt = ((pCtx->pSyntaxInfNew->mb_height > 175) && (PROTOCOL_MPEG2 == pCtx->CodecInfo.MpegFlag));
    if(RemainBytes>4)
    {
        BsSkip(&Bs, 32);
    }
    else
    {
        SINT32 RemainScLen = CLIP3 (0, 4, 4 - RemainBytes);
        BsInit(&Bs, pCtx->CodecInfo.stMp2Packet.BsVirAddr[0], pCtx->CodecInfo.stMp2Packet.BsLength[0]);
        BsSkip(&Bs, RemainScLen*8);
    }
    /*下面要加是否为Mpeg2的判断*/
    if (IsSliceVertExt)
    {
        BsSkip(&Bs, 3);
    }
    QuantScaleCode = BsGet(&Bs, 5);
#else
    QuantScaleCode = pMp2DecParam->SlcStr[0].quantiser_scale_code;
#endif
    QuantScale = (PROTOCOL_MPEG1 == pCtx->CodecInfo.MpegFlag) ? QuantScaleCode :(pCtx->pSyntaxInfNew->q_scale_type ? Non_Linear_quantizer_scale[QuantScaleCode] : QuantScaleCode<<1);
    return QuantScale;
}

/*!
************************************************************************
*    函数原型 :  MP2_GetPictureInfo()
*    功能描述 :  获取MPEG2的解码信息,完成reorder控制
*    参数说明 :  无
*    返回值   :  1: 成功获取 0: 失败
************************************************************************
*/
UINT32 MP2_GetPictureInfo(MP2_CTX_S *pCtx)
{
    SINT32 i;
    MP2_DEC_PARAM_S *pMp2DecParam;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;
    MP2SYNTAXINF *pSyntaxInfOld;
    IMAGE *pImg;
	FSP_LOGIC_FS_S *pCur, *pBwd, *pFwd;

    pMp2DecParam = &pCtx->Mp2DecParam;
    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;
    pSyntaxInfOld = pCtx->pSyntaxInfOld;

    if (PROTOCOL_MPEG1 == pMp2CodecInfo->MpegFlag)
    {
        pSyntaxInfNew->f_code[1][1] = pSyntaxInfNew->backward_f_code;
        pSyntaxInfNew->f_code[1][0] = pSyntaxInfNew->backward_f_code;
        pSyntaxInfNew->f_code[0][1] = pSyntaxInfNew->forward_f_code;
        pSyntaxInfNew->f_code[0][0] = pSyntaxInfNew->forward_f_code;
    }
    //完成picture级的解码器设定
    if (FRAME_PICTURE != pSyntaxInfNew->picture_structure)
    {
        pMp2CodecInfo->Second_Field = !pMp2CodecInfo->Second_Field;
        if ((pSyntaxInfNew->temporal_reference!=pMp2CodecInfo->LastTempReference)&&
            (1==pMp2CodecInfo->Second_Field))
        {
            //丢场检测,如果第2场和第1场,时间戳相同,则可判断丢场发生
            dprint(PRN_ERROR, "ERROR: frm %d, lost one field\n", pMp2CodecInfo->Frame_Cnt);
            pMp2CodecInfo->Second_Field  = 0;//丢场后,场计数器归0

		    FSP_ClearLogicFs(pCtx->ChanID, pMp2CodecInfo->CurFsID, 1); //丢场后,当前图所占buffer应当释放
			
            if (pSyntaxInfOld->picture_coding_type!=B_TYPE)
            {
                pMp2CodecInfo->StreamIntegrality |= (MPEG2_ERROR_REFHDR|MPEG2_ERROR_REFPIC);//参考图丢场需要设置参考图错误
            }
        }
    }
    else
    {
        if ((FRAME_PICTURE!=pMp2CodecInfo->Last_FieldStruct)&&(0==pMp2CodecInfo->Second_Field))
        {
            //如果当前图是帧,上一个图是场,且场计数器为第2场,则可判断丢场
            dprint(PRN_ERROR, "ERROR: frm %d, lost one field flg = %d, last_struct = %d\n",
                   pMp2CodecInfo->Frame_Cnt, pMp2CodecInfo->Second_Field, pMp2CodecInfo->Last_FieldStruct);

		    FSP_ClearLogicFs(pCtx->ChanID, pMp2CodecInfo->CurFsID, 1);
			
            if (pSyntaxInfOld->picture_coding_type!=B_TYPE)
            {
                pMp2CodecInfo->StreamIntegrality |= (MPEG2_ERROR_REFHDR|MPEG2_ERROR_REFPIC);//参考图丢场需要设置参考图错误
            }
            /*此时需要抛弃原有不配对的场,或者令VO把全帧都由该场输出
              如果该场是参考图,问题将变为寻找下一个I图*/
        }
        pMp2CodecInfo->Second_Field = 1;//确保丢场的时候可以因遇到帧图而恢复
    }
    pMp2CodecInfo->Last_FieldStruct = pSyntaxInfNew->picture_structure;
    pMp2CodecInfo->LastTempReference = pSyntaxInfNew->temporal_reference;

    pMp2DecParam->PicWidthInMb = pSyntaxInfNew->mb_width;
    if (FRAME_PICTURE != pSyntaxInfNew->picture_structure)
    {
        pMp2DecParam->PicHeightInMb = pSyntaxInfNew->mb_height/2;
        pMp2DecParam->FrameHeightInMb = pSyntaxInfNew->mb_height;
    }
    else
    {
        /*帧图时，考虑分配帧存宏块高度按偶数，但实际宏块高度为奇数，因此减去pSyntaxInfNew->mb_height_progressive_subtract1mb*/
        pMp2DecParam->PicHeightInMb = pSyntaxInfNew->mb_height - pSyntaxInfNew->mb_height_progressive_subtract1mb;
        pMp2DecParam->FrameHeightInMb = pSyntaxInfNew->mb_height;
    }
    pMp2DecParam->FramePredFrameDct = pSyntaxInfNew->frame_pred_frame_dct;
    pMp2DecParam->PictureStructure = pSyntaxInfNew->picture_structure;
    pMp2DecParam->SecondFieldFlag = pMp2CodecInfo->Second_Field;
    pMp2DecParam->ConcealmentMotionVectors = pSyntaxInfNew->concealment_motion_vectors;
    pMp2DecParam->PicCodingType = pSyntaxInfNew->picture_coding_type;
    pMp2DecParam->Mpeg1Flag = (PROTOCOL_MPEG1 == pMp2CodecInfo->MpegFlag);
    if (PROTOCOL_MPEG1 == pMp2CodecInfo->MpegFlag)
    {
        pMp2DecParam->Mp1BwdmvFullPel = pSyntaxInfNew->full_pel_backward_vector;
        pMp2DecParam->Mp1FwdmvFullPel = pSyntaxInfNew->full_pel_forward_vector;
    }
    pMp2DecParam->Fcode[0] = pSyntaxInfNew->f_code[0][0];
    pMp2DecParam->Fcode[1] = pSyntaxInfNew->f_code[0][1];
    pMp2DecParam->Fcode[2] = pSyntaxInfNew->f_code[1][0];
    pMp2DecParam->Fcode[3] = pSyntaxInfNew->f_code[1][1];
    pMp2DecParam->TopFieldFirst = pSyntaxInfNew->top_field_first;
    pMp2DecParam->IntraDcPrecision = pSyntaxInfNew->intra_dc_precision;
    pMp2DecParam->QuantType = pSyntaxInfNew->q_scale_type;
    pMp2DecParam->IntraVlcFormat = pSyntaxInfNew->intra_vlc_format;
    pMp2DecParam->AlternateScan = pSyntaxInfNew->alternate_scan;

    if ((pSyntaxInfNew->picture_structure==FRAME_PICTURE) || (pMp2CodecInfo->Second_Field==0))
    {
        if ( 0 == MP2_GetImageBuffer(pCtx, NULL) )
        {
            dprint(PRN_FATAL, "Fatal Error: frm%d, get image buffer failed\n", pMp2CodecInfo->Frame_Cnt);
            return MPEG2_FALSE;
        }

		/* PTS */
		pImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->CurFsID);
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
			dprint(PRN_PTS,"dec_pts: %lld Usertag: %lld\n",pImg->PTS, pImg->Usertag);
            pImg->is_fld_save = (pSyntaxInfNew->picture_structure==FRAME_PICTURE) ? 0: 1;
		}
		else
		{
            // ???
		}
        
		/* 参考维护 */
        if (B_TYPE != pSyntaxInfNew->picture_coding_type)
        {
            pMp2CodecInfo->RefNum = pMp2CodecInfo->RefNum>0?2:1;
            if (pMp2CodecInfo->FwdFsID != pMp2CodecInfo->BwdFsID)
            {
                //这样释放的才是有效参考图
                dprint(PRN_REF, "---------- unref %d\n", pMp2CodecInfo->FwdFsID);
                FSP_SetRef(pCtx->ChanID, pMp2CodecInfo->FwdFsID, 0);
            }

            pMp2CodecInfo->FwdFsID = pMp2CodecInfo->BwdFsID;
            pMp2CodecInfo->BwdFsID = pMp2CodecInfo->CurFsID;
            FSP_SetRef(pCtx->ChanID, pMp2CodecInfo->CurFsID, 1);
            FSP_RemovePmv(pCtx->ChanID, pMp2CodecInfo->FwdFsID);
            dprint(PRN_REF,"++++++++++ ref %d\n", pMp2CodecInfo->CurFsID);
        }
    }

    pCur = FSP_GetLogicFs(pCtx->ChanID, pMp2CodecInfo->CurFsID);
    pFwd = FSP_GetLogicFs(pCtx->ChanID, pMp2CodecInfo->FwdFsID);
    pBwd = FSP_GetLogicFs(pCtx->ChanID, pMp2CodecInfo->BwdFsID);

    if ((NULL == pCur) || (NULL == pFwd) || (NULL == pBwd))
    {
        FSP_ClearLogicFs(pCtx->ChanID, pMp2CodecInfo->CurFsID, 1);
        dprint(PRN_FATAL, "line: %d(pCur, pFwd, pBwd)(%p, %p, %p)\n", __LINE__, pCur, pFwd, pBwd);
        return MPEG2_FALSE;
    }

	if ((NULL == pCur->pstDecodeFs) || (NULL == pCur->pstTfOutFs) || ((NULL == pCur->pstDispOutFs)))
	{
           FSP_ClearLogicFs(pCtx->ChanID, pMp2CodecInfo->CurFsID, 1);
           dprint(PRN_FATAL, "CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\n",pMp2CodecInfo->FwdFsID,pMp2CodecInfo->CurFsID,
                      pMp2CodecInfo->BwdFsID, pCur->pstDecodeFs, pCur->pstTfOutFs, pCur->pstDispOutFs);
           return MPEG2_FALSE;
	}
	else
	{
	    pMp2DecParam->BwdRefPhyAddr   = (NULL != pBwd->pstDecodeFs)?pBwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
	    pMp2DecParam->FwdRefPhyAddr   = (NULL != pFwd->pstDecodeFs)?pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
	    pMp2DecParam->CurPicPhyAddr   = pCur->pstDecodeFs->PhyAddr;
	    pMp2DecParam->PmvColmbPhyAddr = pCur->PmvAddr;

	    pMp2DecParam->TfBwdPhyAddr    = (NULL != pBwd->pstTfOutFs)?pBwd->pstTfOutFs->PhyAddr: pCur->pstTfOutFs->PhyAddr;
	    pMp2DecParam->TfFwdPhyAddr    = (NULL != pFwd->pstTfOutFs)?pFwd->pstTfOutFs->PhyAddr: pCur->pstTfOutFs->PhyAddr;
	    pMp2DecParam->TfCurPhyAddr    = pCur->pstTfOutFs->PhyAddr;

	    pMp2DecParam->DispFramePhyAddr = pCur->pstDispOutFs->PhyAddr;

	    pMp2DecParam->BwdRefIsFldSave = pBwd->stDispImg.is_fld_save;
	    pMp2DecParam->FwdRefIsFldSave = pFwd->stDispImg.is_fld_save;
	}

	dprint(PRN_REF, "dec addr: cur,cur2d,fwd,bwd,pmv = %p,%p,%p,%p,%p\n", pMp2DecParam->CurPicPhyAddr, pMp2DecParam->DispFramePhyAddr,
		pMp2DecParam->FwdRefPhyAddr, pMp2DecParam->BwdRefPhyAddr, pMp2DecParam->PmvColmbPhyAddr);

    pMp2DecParam->VahbStride = pCur->pstDispOutFs->Stride;
	
    //每个新的sequence到来不管是用码流中的量化矩阵还是使用缺省矩阵,都要
    //向VDM更新
    for (i=0; i<64; i++)
    {
        pMp2DecParam->IntraQuantTab[i] = pCtx->intra_quantizer_matrix[i];
        pMp2DecParam->NonIntraQuantTab[i] = pCtx->non_intra_quantizer_matrix[i];
    }

    pMp2DecParam->EstmatedPicQp = MP2_EstimatePicQp(pCtx);


    return MPEG2_TRUE;
}


/*!
************************************************************************
*    函数原型 :  MP2_GetSequenceInfo()
*    功能描述 :  获取MPEG2的序列级解码信息
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID MP2_GetSequenceInfo(MP2_CTX_S *pCtx)
{
    UINT32 FsNum = 0;
    SINT32 RefNum = 0, ReadNum = 0, NewNum = 0;
    MP2CODECINF *pMp2CodecInfo;
    MP2SYNTAXINF *pSyntaxInfNew;
    MP2SYNTAXINF *pSyntaxInfOld;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;
    pSyntaxInfOld = pCtx->pSyntaxInfOld;

    switch (pMp2CodecInfo->MpegFlag)
    {
    case PROTOCOL_MPEG1:
        if ((pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_SEQEXT)&&
            (!(pMp2CodecInfo->StreamIntegrality&MPEG2_ERROR_SEQEXT))&&
            (pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_PICEXT)&&
            (!(pMp2CodecInfo->StreamIntegrality&MPEG2_ERROR_PICEXT)))
        {
            //由MPEG1转为MPEG2需要确认找到序列和图像扩展头且扩展头无误
            pMp2CodecInfo->MpegFlag = PROTOCOL_MPEG2;
        }
        break;
    case PROTOCOL_MPEG2:
        if ((!(pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_SEQEXT))&&
            (!(pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_PICEXT))&&
            (pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_SEQHDR)&&
            (pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_PICHDR))
        {
            //由MPEG2转为MPEG1需要确认能找到序列头和图像头,但找不到序列以及图像扩展头
            pMp2CodecInfo->MpegFlag = PROTOCOL_MPEG1;
        }
        break;
    default:
        if (pMp2CodecInfo->StreamIntegrality&MPEG2_ALL_EXTENTION)
        {
            //只要序列中找到扩展,就是MPEG2码流
            pMp2CodecInfo->MpegFlag = PROTOCOL_MPEG2;
            if (!(pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_SEQEXT))
            {
                //如果没有找到seq_ext,则说明序列扩展有错
                pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_SEQEXT;
            }
            if (!(pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_PICEXT))
            {
                //如果没有找到pic_ext,则说明图像扩展有错
                //假如该图是参考图,在后续的protocol pps检查中还会置起参考图错误标志
                pMp2CodecInfo->StreamIntegrality|=MPEG2_ERROR_PICEXT;
            }
            //显示扩展的错误不影响解码,不进行检查
        }
        else
        {
            pMp2CodecInfo->MpegFlag = PROTOCOL_MPEG1;
        }
        break;
    }
    dprint(PRN_SEQ, "Protocol %d\n", pMp2CodecInfo->MpegFlag);
    
    //derive some variable
    if (PROTOCOL_MPEG1 == pMp2CodecInfo->MpegFlag)
    {
        pSyntaxInfNew->progressive_sequence = 1;
        pSyntaxInfNew->progressive_frame = 1;
        pSyntaxInfNew->picture_structure = FRAME_PICTURE;
        pSyntaxInfNew->frame_pred_frame_dct = 1;
        pSyntaxInfNew->chroma_format = 1;
        pSyntaxInfNew->matrix_coefficients = 5;
        pSyntaxInfNew->concealment_motion_vectors = 0;
        pSyntaxInfNew->q_scale_type = 0;
        pSyntaxInfNew->intra_vlc_format = 0;
        pSyntaxInfNew->alternate_scan = 0;
        pSyntaxInfNew->intra_dc_precision = 0;
    }
    
    pSyntaxInfNew->mb_width = (pSyntaxInfNew->horizontal_size+15)/16;
    pSyntaxInfNew->mb_height = ((PROTOCOL_MPEG2 == pMp2CodecInfo->MpegFlag)&&(!pSyntaxInfNew->progressive_sequence)) 
        ? 2*((pSyntaxInfNew->vertical_size+31)/32) : (pSyntaxInfNew->vertical_size+15)/16;
    
    /* mb_height_progressive_subtract1mb 用于记录宏块高度为奇数时的帧图分配帧存宏块高度和实际宏块高度的差值*/
    pSyntaxInfNew->mb_height_progressive_subtract1mb = 0;
    
    if ( (PROTOCOL_MPEG2==pMp2CodecInfo->MpegFlag) && (!pSyntaxInfNew->progressive_sequence) )
    {
        pSyntaxInfNew->mb_height_progressive_subtract1mb = 2*((pSyntaxInfNew->vertical_size+31)/32) - (pSyntaxInfNew->vertical_size+15)/16;
    }

    //VHB 地址分配
    if ((MPEG2_FALSE == pMp2CodecInfo->Imgbuf_allocated)||
        (pSyntaxInfNew->mb_width  != pSyntaxInfOld->mb_width)||
        (pSyntaxInfNew->mb_height != pSyntaxInfOld->mb_height))
    {
        MP2_CLEARREFFLAG;
        MP2_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
        
        if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
        {
            if (MPEG2_FALSE == pMp2CodecInfo->Imgbuf_allocated)
            {
                ResetVoQueue(&pCtx->ImageQue);
                pMp2CodecInfo->Imgbuf_allocated = MP2_ArrangeVHBMem(pCtx, FsNum);
                pMp2CodecInfo->QueueImageNum = 0;
            }
        }
        else
        {
            if (pMp2CodecInfo->Imgbuf_allocated != MPEG2_FALSE 
             && pSyntaxInfOld->mb_width != 0 && pSyntaxInfOld->mb_height != 0)
            {
                pMp2CodecInfo->Imgbuf_allocated = MPEG2_FALSE;
                dprint(PRN_ERROR, "seq size change, wait for all frames out.\n");   
                REPORT_FAKE_FRAME(pCtx->ChanID);
            }
         
            VCTRL_GetChanImgNum(pCtx->ChanID, &RefNum, &ReadNum, &NewNum);
            if (pCtx->pstExtraData->stChanOption.s32ReRangeEn == 1)
            {
             #ifdef PRODUCT_KIRIN
                if (NewNum > 0)
                {
                    pCtx->IsWaitToReRange = 1;
                    return;
                }
             #else
                if (ReadNum + NewNum > 0)
                {
                    pCtx->IsWaitToReRange = 1;
                    return;
                }
             #endif
            }
            
            ResetVoQueue(&pCtx->ImageQue); 
            pCtx->IsWaitToReRange = 0;
            
            pMp2CodecInfo->Imgbuf_allocated = MPEG2_FALSE;
            pMp2CodecInfo->QueueImageNum = 0;
            
            pMp2CodecInfo->Imgbuf_allocated = MP2_ArrangeVHBMem(pCtx, FsNum);
            dprint(PRN_ERROR, "new seq size %dx%d -> %dx%d\n", pSyntaxInfOld->mb_width*16, pSyntaxInfOld->mb_height*16, pSyntaxInfNew->mb_width*16, pSyntaxInfNew->mb_height*16);   
        }

        //未分配或者大小变化后,需要修改VO管理结构内的信息
        REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pSyntaxInfOld->mb_width,pSyntaxInfOld->mb_height,\
                               pSyntaxInfNew->mb_width, pSyntaxInfNew->mb_height);
        
    }
    
    pMp2CodecInfo->NewSeqInited = pMp2CodecInfo->Imgbuf_allocated;//MPEG2_TRUE;

    return;
}


/*!
************************************************************************
*    函数原型 :  MP2_ResumePic()
*    功能描述 :  按照新图像方式配置VDM解码,并对VDM运行结果进行处理
*    参数说明 :  无
*    返回值   :  VDM状态 -1,信号量超时0,VO队列插入失败;1,正常解码;4,码流不足;
************************************************************************
*/
SINT32 MP2_DecNewPic(MP2_CTX_S *pCtx)
{
    SINT32 Ret = DEC_OVER;

    MP2_SetVDMInf(pCtx);
    pCtx->Mp2DecParam.Compress_en = pCtx->pstExtraData->s32Compress_en;

    if ( (B_TYPE == pCtx->pSyntaxInfNew->picture_coding_type) && (0 == pCtx->PPicFound) && (2 != pCtx->CodecInfo.RefNum) ) /* 发现B帧 */
    {
        /* 20111223: 这种模式下，没有机会进入MP2_GetPictureInfo()函数，Second_Field 
           的值没有得到轮换更新，故在这里进行轮换更新 */
        if (pCtx->pSyntaxInfNew->picture_structure != FRAME_PICTURE )
        {
            pCtx->CodecInfo.Second_Field = !pCtx->CodecInfo.Second_Field;
        }
        return MPEG2_FALSE;
    }
    else if (P_TYPE == pCtx->pSyntaxInfNew->picture_coding_type) 
    {
        pCtx->PPicFound = 1;
    }
    
    pCtx->pMp2DecParam = &pCtx->Mp2DecParam;

    if (1 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((NULL != pCtx->pMp2DecParam)&& (B_TYPE == pCtx->pSyntaxInfNew->picture_coding_type))
        {
            pCtx->pMp2DecParam = NULL;
            //FSP_SetDisplay(pCtx->ChanID, pCtx->CodecInfo.CurFsID, 0);
            Ret = MPEG2_FALSE;
            return Ret;
        }
    }
    else if (2 == pCtx->pstExtraData->stDisParams.s32Mode)
    {
        if ((pCtx->pstExtraData->stDisParams.s32DisNums > 0) && (NULL != pCtx->pMp2DecParam)
            && (B_TYPE == pCtx->pSyntaxInfNew->picture_coding_type))
        {
            pCtx->pMp2DecParam = NULL;
            //FSP_SetDisplay(pCtx->ChanID, pCtx->CodecInfo.CurFsID, 0);
            pCtx->pstExtraData->stDisParams.s32DisNums--;
            Ret = MPEG2_FALSE;
            return Ret;
        }
    } 
    
	pCtx->CodecInfo.StreamIntegrality &= ~(MPEG2_FOUND_PICHDR|MPEG2_FOUND_PICEXT|MPEG2_FOUND_PICDISPEXT|MPEG2_FOUND_SLICE|MPEG2_FOUND_NEXTHDR);

    /*
    pCtx->pMp2DecParam = &pCtx->Mp2DecParam;
	pCtx->CodecInfo.StreamIntegrality &= ~(MPEG2_FOUND_PICHDR|MPEG2_FOUND_PICEXT|MPEG2_FOUND_PICDISPEXT|MPEG2_FOUND_SLICE|MPEG2_FOUND_NEXTHDR);
    */
    
    /* 发现I帧，报告一个事件 */
    if (pCtx->pSyntaxInfNew->picture_coding_type == I_TYPE)
    {
        REPORT_FIND_IFRAME(pCtx->ChanID, (pCtx->Mp2DecParam.StreamLength[0] + pCtx->Mp2DecParam.StreamLength[1]) / 8);
	}

    return Ret;
}

UINT32  MP2_CalcDar(MP2_CTX_S *pCtx)
{
    SINT32  dar;
    UINT32  ar_info = pCtx->pSyntaxInfNew->aspect_ratio_information;

    switch (ar_info)
    {
        case 1:
            dar = DAR_IMG_SIZE;
            break;
        case 2:
            dar = DAR_4_3;
            break;
        case 3:
            dar = DAR_16_9;
            break;
        default:
            dar = DAR_UNKNOWN;
            break;
    }

    return (UINT32)dar;
}

VOID MP2_SetImgFormat(MP2_CTX_S *pCtx)
{
    UINT32 codtype, csp, vfmt, sfmt, fldflg, fldfst=0, dar;
    MP2CODECINF *pMp2CodecInfo;
    MP2SYNTAXINF *pSyntaxInfNew;
    IMAGE *pImg;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

	pImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->CurFsID);
	if (NULL == pImg)
	{
        return;
	}

    if (pSyntaxInfNew->picture_coding_type==D_TYPE)
    {
        //D图作为I图处理
        codtype = 0;
    }
    else
    {
        codtype = pSyntaxInfNew->picture_coding_type-1;
    }
    csp = 0;

    vfmt = pSyntaxInfNew->video_format;
    //sfmt = !(pSyntaxInfNew->progressive_sequence||pSyntaxInfNew->progressive_frame);
    sfmt = !(pSyntaxInfNew->progressive_sequence);

    fldflg = (pImg->format>>10)&0x3;
    fldflg |= pSyntaxInfNew->picture_structure;

    if (pSyntaxInfNew->progressive_sequence)
    {
        fldfst = 1;//逐行序列指定顶场先显示
    }
    else if (pSyntaxInfNew->picture_structure==FRAME_PICTURE)
    {
        fldfst = (pSyntaxInfNew->top_field_first&1);//非逐行的帧编码场序由码流确定
    }
    else if (pMp2CodecInfo->Second_Field==0)
    {
        //场编码图用解码顺序指定
        fldfst = (pSyntaxInfNew->picture_structure==TOP_FIELD)?1:0;
    }
    else
    {
        //场编码图第2场需要倒序设定
        fldfst = (pSyntaxInfNew->picture_structure==TOP_FIELD)?0:1;
    }

    dar = MP2_CalcDar(pCtx);

    pImg->format = ((dar&7)<<14)|((fldfst&0x3)<<12)|((fldflg&3)<<10)|((sfmt&3)<<8)|((vfmt&3)<<5)|((csp&7)<<2)|(codtype&3);
    pImg->top_fld_type = codtype&3;
    pImg->bottom_fld_type = codtype&3;

	SetAspectRatio(pImg,(VDEC_DAR_E)dar);

	pImg->frame_rate = pSyntaxInfNew->frame_rate;
    pImg->image_width=pSyntaxInfNew->horizontal_size;
    pImg->image_height=pSyntaxInfNew->vertical_size; 
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
	if (pSyntaxInfNew->display_horizontal_size > 0 && pSyntaxInfNew->display_vertical_size > 0)
	{
	    pImg->disp_width  = (pSyntaxInfNew->display_horizontal_size > pImg->image_width)? pImg->image_width:
			pSyntaxInfNew->display_horizontal_size;
		pImg->disp_height = (pSyntaxInfNew->display_vertical_size > pImg->image_height)? pImg->image_height:
			pSyntaxInfNew->display_vertical_size;
	}
	else
	{
        pImg->disp_width = pImg->image_width;
		pImg->disp_height = pImg->image_height;
	}
}


SINT32 MP2_SearchStartCode( UINT8* pCode, SINT32 CodeLen)
{   
    UINT8 *ptr,*pEnd,byte;   
    SINT32 ofst;

    if (CodeLen<5)
    {
        /* 如果码流字节小于5，不调用该函数 */
        return 0;
    }
    pEnd = pCode + CodeLen;
    for ( ptr=pCode+2; ptr<pEnd; )       
    {
        byte = ptr[0];
        if ( byte>1 )
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
        else if ( byte == 0x01 )  
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
  
    return (CodeLen-3);  
}


/*!
************************************************************************
*    函数原型 :  MP2_ProtocolPPSCheck()
*    功能描述 :  检查协议相关的图像级参数语法正确性,并置相应标志
*    参数说明 : 
*    返回值   :  无
************************************************************************
*/
VOID MP2_ProtocolPPSCheck(MP2_CTX_S *pCtx)
{
    MP2CODECINF *pMp2CodecInfo;
    MP2SYNTAXINF *pSyntaxInfNew;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    //SPS基本和协议无关,可以解码时检查
    //PPS有很多跟协议相关,必须等协议确定后才能检查
    switch (pMp2CodecInfo->MpegFlag)
    {
        case PROTOCOL_MPEG1:
            if ((pSyntaxInfNew->picture_coding_type==0)||(pSyntaxInfNew->picture_coding_type>D_TYPE))
            {
                pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICHDR;
            }
            if (pSyntaxInfNew->picture_coding_type==P_TYPE || pSyntaxInfNew->picture_coding_type==B_TYPE)
            {
                if (pSyntaxInfNew->forward_f_code==0)
                {
                    pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICHDR;
                }
            }
            if (pSyntaxInfNew->picture_coding_type==B_TYPE)
            {
                if(pSyntaxInfNew->backward_f_code==0)
                {
                    pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICHDR;
                }
            }
            break;
        case PROTOCOL_MPEG2:
            if (!(pMp2CodecInfo->StreamIntegrality&MPEG2_FOUND_PICEXT))
            {
                //mpeg2下没有找到pic_ext属于错误情况,应该置上标记
                pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICEXT;
            }
            if ((pSyntaxInfNew->picture_coding_type==0)||(pSyntaxInfNew->picture_coding_type>B_TYPE))
            {
                pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICHDR;
            }
            break;
        default:
            pMp2CodecInfo->StreamIntegrality |= MPEG2_ALLSEQ_ERROR;
            break;
    }
    //参考图的错误标志需要单独确认
    if ((pMp2CodecInfo->StreamIntegrality&(MPEG2_ERROR_PICHDR|MPEG2_ERROR_PICEXT))
        &&(B_TYPE!=pSyntaxInfNew->picture_coding_type))
    {
        //reference picture error need to jump to next I picture
        pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_REFHDR;
        //参考图错误,释放所有参考图
        MP2_CLEARREFFLAG;
        MP2_CLEARREFNUM;
        return;
    }
    if (I_TYPE==pSyntaxInfNew->picture_coding_type)
    {
        //reference picture error can be recovered at I picture
        pMp2CodecInfo->StreamIntegrality &= ~(MPEG2_ERROR_REFHDR|MPEG2_ERROR_REFPIC);
    }

    return;
}


/*!
************************************************************************
*    函数原型 :  MP2_GetImageBuffer()
*    功能描述 :  取一块帧存
*    参数说明 :  **p_vobuf 用于指向当前可用帧存的指针的地址
*    返回值   :  0: 无法找到可用帧存;1: 能够找到可用帧存
************************************************************************
*/
UINT32 MP2_GetImageBuffer(MP2_CTX_S *pCtx, MP2VOBUFINF **p_vobuf)
{
    SINT32 ret = MPEG2_FALSE;
    MP2CODECINF *pMp2CodecInfo;
    MP2VOBUFINF *pVOBufInf;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pVOBufInf = pCtx->CodecInfo.VOBufInf;

    pMp2CodecInfo->CurFsID = FSP_NewLogicFs(pCtx->ChanID, 1);
	if (pMp2CodecInfo->CurFsID < 0)
	{
        /* 获取帧存失败 */
    	dprint(PRN_FATAL,"get frame store fail!\n");
    	MP2_CLEARREFFLAG;
    	MP2_CLEARREFNUM;		
    	#if 0
    	ResetVoQueue(&pCtx->ImageQue);
    	FSP_EmptyInstance(pCtx->ChanID);
    	#else
    	FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
    	#endif
    	
    	return 0;
    }
    ret = MPEG2_TRUE;
    {
          FSP_LOGIC_FS_S *pLf = FSP_GetLogicFs(pCtx->ChanID, pMp2CodecInfo->CurFsID);
          if (NULL == pLf)
          {
              dprint(PRN_FATAL, "line: %d, pImage is NULL!\n", __LINE__);
              return MPEG2_FALSE;
          }
          
          dprint(PRN_PIC, "get image buffer ok: LogicFsID = %d\n", pMp2CodecInfo->CurFsID);		
          if ( (NULL!=pLf->pstDecodeFs) && (NULL!=pLf->pstDispOutFs) && (NULL!=pLf->pstTfOutFs) )
          {
              dprint(PRN_PIC, "decode %p, disp %p, tf %p\n", pLf->pstDecodeFs->PhyAddr, pLf->pstDispOutFs->PhyAddr, pLf->pstTfOutFs->PhyAddr);
          }
    }

    return ret;

}


/*!
************************************************************************
*    函数原型 :  MP2_SetVDMInf()
*    功能描述 :  设定VDM的控制寄存器和下行消息
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID MP2_SetVDMInf(MP2_CTX_S *pCtx)
{
    UINT32 bs_offset;
    UADDR stream_base_addr;
    MP2_DEC_PARAM_S *pMp2DecParam;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;

    pMp2DecParam = &pCtx->Mp2DecParam;
    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;

    if (1 == pMp2CodecInfo->stMp2Packet.IsLastSeg[0])
    {
        stream_base_addr = ((pMp2CodecInfo->stMp2Packet.BsPhyAddr[0] + ((UINT32)pBs->TotalPos/8))&0xfffffffc);
        bs_offset = (UINT32)pBs->TotalPos + ((pMp2CodecInfo->stMp2Packet.BsPhyAddr[0]&0x3)<<3);

        pMp2CodecInfo->BsOffset += pBs->TotalPos/8;

        pMp2DecParam->StreamPhyAddr[0] = stream_base_addr;
        pMp2DecParam->StreamBitOffset[0] = bs_offset&0x1f;
        pMp2DecParam->StreamLength[0] = (UINT32)BsResidBits(pBs);
        
        pMp2DecParam->StreamPhyAddr[1] = 0;
        pMp2DecParam->StreamBitOffset[1] = 0;
        pMp2DecParam->StreamLength[1] = 0;
    }
    else
    {
        stream_base_addr = (pMp2CodecInfo->stMp2Packet.BsPhyAddr[1])&0xfffffffc;
      
        bs_offset = (UINT32)pBs->TotalPos + ((pMp2CodecInfo->stMp2Packet.BsPhyAddr[0]&0x3)<<3);     
        pMp2CodecInfo->BsOffset += pBs->TotalPos/8;

        pMp2DecParam->StreamPhyAddr[0] = ((pMp2CodecInfo->stMp2Packet.BsPhyAddr[0] + ((UINT32)pBs->TotalPos/8))&0xfffffffc);
        pMp2DecParam->StreamBitOffset[0] = bs_offset&0x1f;
        pMp2DecParam->StreamLength[0] = (UINT32)BsResidBits(pBs);

        pMp2DecParam->StreamPhyAddr[1] = stream_base_addr;
        pMp2DecParam->StreamBitOffset[1] = (pMp2CodecInfo->stMp2Packet.BsPhyAddr[1] & 0x3) << 3;
        pMp2DecParam->StreamLength[1] = pMp2CodecInfo->stMp2Packet.BsLength[1]*8;
    }

    return;
}


/*!
************************************************************************
*    函数原型 :  MP2_RecordVFMWState(VOID)
*    功能描述 :  记录VFMW的工作状态
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID MP2_RecordVFMWState(MP2_CTX_S *pCtx)
{
    MP2CODECINF *pMp2CodecInfo;
    MP2SYNTAXINF *pSyntaxInfNew;
	VDEC_CHAN_STATE_S  *pChanState = &pCtx->pstExtraData->stChanState;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

	pChanState->image_width        = pSyntaxInfNew->horizontal_size;
	pChanState->image_height       = pSyntaxInfNew->vertical_size;
	pChanState->aspect_ratio       = MP2_CalcDar(pCtx);
	pChanState->scan_type          = 0;
	pChanState->video_format       = 0;
	pChanState->frame_rate         = pSyntaxInfNew->frame_rate;
	pChanState->bit_rate           = 0;
	pChanState->sub_video_standard = pMp2CodecInfo->MpegFlag==PROTOCOL_MPEG1?1:0;
	pChanState->profile            = pSyntaxInfNew->profile;
	pChanState->level              = pSyntaxInfNew->level;
	pChanState->total_frame_num    = pCtx->numTotalFrame;
	pChanState->error_frame_num    = (pCtx->numTotalFrame >= pCtx->numOutputFrame)? 
		                                 (pCtx->numTotalFrame - pCtx->numOutputFrame): 0;

    return;
}


SINT8 g_tmpusd[MAX_USRDAT_SIZE];
SINT32 MP2_GetUsrData(MP2_CTX_S *pCtx)
{
    UINT32 Code, UDataNum;
    SINT32 RemainByte,i, cnt, NextHeaderFlag,k = 0;
//    VDEC_USRDAT_S *p_UD = *pp_UD;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;

    BsToNextByte(pBs); /*这些填充则应该全部为0*/
    RemainByte = (BsResidBits(pBs) / 8);// - 3;
    cnt = 0;
    NextHeaderFlag = 0;
    for (i = 0; (i < RemainByte); i++)
    {
        Code = BsShow(pBs, 24);
        if ((Code & 0xffffff) == 0x000001)
        {
            NextHeaderFlag = 1;
            break;
        }
        if (MAX_USRDAT_SIZE > cnt)
        {
            g_tmpusd[cnt] = BsGet(pBs, 8);
            cnt++;
        }
        else
        {
            BsGet(pBs, 8);
        }
    }

    if ((0 == NextHeaderFlag) && (0 ==pMp2CodecInfo->stMp2Packet.IsLastSeg[0]) && 
       (0!=pMp2CodecInfo->stMp2Packet.IsLastSeg[1]) && (0!=pMp2CodecInfo->stMp2Packet.BsLength[1]))
    {
        //second pack isn't zero
        //make sure that first pack len isn't less than 4 bytes
        dprint(PRN_FATAL, "MP2_GetUsrData mpeg2 copy last 3 bytes of the first packet!\n\n");
        memcpy(pMp2CodecInfo->stMp2Packet.BsVirAddr[1] - 3, pMp2CodecInfo->stMp2Packet.BsVirAddr[0] + pMp2CodecInfo->stMp2Packet.BsLength[0] - 3, 3);
        pMp2CodecInfo->stMp2Packet.BsLength[1]   += 3;
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[1]  -= 3;
        pMp2CodecInfo->stMp2Packet.BsVirAddr[1]  -= 3;

        //重新初始化码流，两包码流变成一包 
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[0]  = pMp2CodecInfo->stMp2Packet.BsPhyAddr[1];
        pMp2CodecInfo->stMp2Packet.BsVirAddr[0]  = pMp2CodecInfo->stMp2Packet.BsVirAddr[1];
        pMp2CodecInfo->stMp2Packet.BsLength[0]   = pMp2CodecInfo->stMp2Packet.BsLength[1]; 
        pMp2CodecInfo->stMp2Packet.IsLastSeg[0]  = 1;
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[1]  = 0;
        pMp2CodecInfo->stMp2Packet.BsVirAddr[1]  = 0;
        pMp2CodecInfo->stMp2Packet.BsLength[1]   = 0;
        pMp2CodecInfo->stMp2Packet.IsLastSeg[1]  = 0;
        BsInit(pBs, pMp2CodecInfo->stMp2Packet.BsVirAddr[0], pMp2CodecInfo->stMp2Packet.BsLength[0]);
        /* 恢复原来的值，主要是在释放码流包函数 MP2_ClearCurPacket 用到 */
        pMp2CodecInfo->stMp2Packet.IsLastSeg[0]  = 0;        
        pMp2CodecInfo->stMp2Packet.IsLastSeg[1]  = 1;
        
        BsToNextByte(pBs);  
        RemainByte = (BsResidBits(pBs) / 8) - 3;
        for (i = 0; (i < RemainByte); i++)
        {
            Code = BsShow(pBs, 24);
            if ((Code & 0xffffff) == 0x000001)
            {
                NextHeaderFlag = 1;
                break;
            }
            if (MAX_USRDAT_SIZE > cnt)
            {
                g_tmpusd[cnt] = BsGet(pBs, 8);
                cnt++;
            }
            else
            {
                BsGet(pBs, 8);
            }
        }
    }

    if (pMp2CodecInfo->TotalUsrDatNum > (MAX_USERDATA_NUM - 1))
    {
        for (k = 0; k < MAX_USERDATA_NUM ; k++)
        {
            FreeUsdByDec(pCtx->ChanID, pMp2CodecInfo->pUsrDatArray[k]);
            pMp2CodecInfo->pUsrDatArray[k] = NULL;
        }
        pMp2CodecInfo->TotalUsrDatNum = 0;
    }
    UDataNum = pMp2CodecInfo->TotalUsrDatNum;
    pMp2CodecInfo->pUsrDatArray[UDataNum] = GetUsd(pCtx->ChanID);
    if (NULL != pMp2CodecInfo->pUsrDatArray[pMp2CodecInfo->TotalUsrDatNum])
    {
        pMp2CodecInfo->pUsrDatArray[UDataNum]->PTS = pCtx->pstExtraData->pts;
        pMp2CodecInfo->pUsrDatArray[UDataNum]->seq_cnt = pMp2CodecInfo->SeqCnt;
        pMp2CodecInfo->pUsrDatArray[UDataNum]->data_size = cnt;
        pMp2CodecInfo->pUsrDatArray[UDataNum]->pic_coding_type = pCtx->pSyntaxInfNew->picture_coding_type;
        pMp2CodecInfo->pUsrDatArray[UDataNum]->pic_num_count = pCtx->numTotalFrame;
	    pMp2CodecInfo->pUsrDatArray[UDataNum]->top_field_first = pCtx->pSyntaxInfNew->top_field_first;
        if(MPEG2_FOUND_PICHDR == (pMp2CodecInfo->StreamIntegrality & MPEG2_FOUND_PICHDR))
        {
            pMp2CodecInfo->pUsrDatArray[UDataNum]->from = MP2UD_FROM_PIC;
        }
        else
        {    
            pMp2CodecInfo->pUsrDatArray[UDataNum]->from = MP2UD_FROM_SEQ;
        }
        if (pMp2CodecInfo->pUsrDatArray[UDataNum]->data_size > MAX_USRDAT_SIZE)
        {
            pMp2CodecInfo->pUsrDatArray[UDataNum]->data_size = MAX_USRDAT_SIZE;
        }
        memcpy(pMp2CodecInfo->pUsrDatArray[UDataNum]->data, g_tmpusd, pMp2CodecInfo->pUsrDatArray[UDataNum]->data_size);
        REPORT_USRDAT( pCtx->ChanID, pMp2CodecInfo->pUsrDatArray[UDataNum]);
        pMp2CodecInfo->TotalUsrDatNum++;
    }
    else
    {
        dprint(PRN_FATAL,"pMp2CodecInfo->pUsrDatArray[%d] is null\n",pMp2CodecInfo->TotalUsrDatNum);
    }
#if 0
    if (NULL == p_UD)
    {
        //only empty pointer need get, otherwise just overwrite pointer's content
        p_UD = GetUsd(pCtx->ChanID);
        if ( p_UD == NULL )
        {
            return MPEG2_ERROR;
        }
    }
    p_UD->PTS = pCtx->pstExtraData->pts;
    p_UD->seq_cnt = pMp2CodecInfo->SeqCnt;
    p_UD->data_size = cnt;
    p_UD->pic_coding_type = pCtx->pSyntaxInfNew->picture_coding_type;
	p_UD->top_field_first = pCtx->pSyntaxInfNew->top_field_first;
    p_UD->pic_num_count = pCtx->numTotalFrame;
    if (p_UD->data_size > MAX_USRDAT_SIZE)
    {
    	p_UD->data_size = MAX_USRDAT_SIZE;
    }
    memcpy(p_UD->data,g_tmpusd, p_UD->data_size);
    REPORT_USRDAT( pCtx->ChanID, p_UD );
    *pp_UD = p_UD;
#endif

    if (0 == NextHeaderFlag)
    {
        return MPEG2_FALSE;
    }
    else
    {
        return MPEG2_TRUE;
    }
}


/*!
************************************************************************
*    函数原型 :  next_start_code()
*    功能描述 :  寻找下一个MPEG2码流startcode
*    参数说明 :  无
*    返回值   :  找到返回1,否则返回0
************************************************************************
*/
UINT32 next_start_code(MP2_CTX_S *pCtx)
{
    SINT32 i, remain_byte;
    UINT8 *pcode;
    UINT32 offset, len;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;

    BsToNextByte(pBs);

    pcode = BsGetNextBytePtr(pBs);        
    len = (BsResidBits(pBs)/8);
    offset = MP2_SearchStartCode(pcode, len);
    BsLongSkip(pBs, (offset<<3));

    remain_byte = (BsResidBits(pBs)/8)-3;
    for (i=0; i<remain_byte; i++)
    {
        if (BsShow(pBs, 24)==0x01L)
        {
            return MPEG2_TRUE;
        }
        BsSkip(pBs, 8);
    }

    if ((0==pMp2CodecInfo->stMp2Packet.IsLastSeg[0]) && (0!=pMp2CodecInfo->stMp2Packet.IsLastSeg[1]) &&
        (0!=pMp2CodecInfo->stMp2Packet.BsLength[1]))
    {
        //second pack isn't zero
        //make sure that first pack len isn't less than 4 bytes
        dprint(PRN_STREAM, "next_start_code mpeg2 copy last 3 bytes of the first packet!\n\n");
        memcpy(pMp2CodecInfo->stMp2Packet.BsVirAddr[1] - 3, pMp2CodecInfo->stMp2Packet.BsVirAddr[0] + pMp2CodecInfo->stMp2Packet.BsLength[0] - 3, 3);
        pMp2CodecInfo->stMp2Packet.BsLength[1]   += 3;
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[1]  -= 3;
        pMp2CodecInfo->stMp2Packet.BsVirAddr[1]  -= 3;

        //重新初始化码流，两包码流变成一包 
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[0]  = pMp2CodecInfo->stMp2Packet.BsPhyAddr[1];
        pMp2CodecInfo->stMp2Packet.BsVirAddr[0]  = pMp2CodecInfo->stMp2Packet.BsVirAddr[1];
        pMp2CodecInfo->stMp2Packet.BsLength[0]   = pMp2CodecInfo->stMp2Packet.BsLength[1];
        pMp2CodecInfo->stMp2Packet.IsLastSeg[0]  = 1;
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[1]  = 0;
        pMp2CodecInfo->stMp2Packet.BsVirAddr[1]  = 0;
        pMp2CodecInfo->stMp2Packet.BsLength[1]   = 0;
        pMp2CodecInfo->stMp2Packet.IsLastSeg[1]  = 0;
        BsInit(pBs, pMp2CodecInfo->stMp2Packet.BsVirAddr[0], pMp2CodecInfo->stMp2Packet.BsLength[0]);
        /* 恢复原来的值，主要是在释放码流包函数 MP2_ClearCurPacket 用到 */
        pMp2CodecInfo->stMp2Packet.IsLastSeg[0]  = 0;        
        pMp2CodecInfo->stMp2Packet.IsLastSeg[1]  = 1;

        BsToNextByte(pBs);

        pcode = BsGetNextBytePtr(pBs);        
        len = (BsResidBits(pBs)/8);
        offset = MP2_SearchStartCode(pcode, len);    
        BsLongSkip(pBs, (offset<<3));

        remain_byte = (BsResidBits(pBs)/8)-3;
        for (i=0; i<remain_byte; i++)
        {
            if (BsShow(pBs, 24)==0x01L)
            {
                return MPEG2_TRUE;
            }
            BsSkip(pBs, 8);
        }
    }

    return MPEG2_FALSE;
}


/*!
************************************************************************
*    函数原型 :  sequence_header()
*    功能描述 :  为MPEG2解析sequence头
*    参数说明 :  无
*    返回值   :  1,找到起始码;0,找不到起始码
************************************************************************
*/
UINT32 sequence_header(MP2_CTX_S *pCtx)
{
    UINT32 i, ret = MPEG2_TRUE;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    pMp2CodecInfo->StreamIntegrality = MPEG2_FOUND_SEQHDR;
    pMp2CodecInfo->NewSeqInited = MPEG2_FALSE;
    pSyntaxInfNew->horizontal_size             = BsGet(pBs, 12);
    pSyntaxInfNew->vertical_size               = BsGet(pBs, 12);
    pSyntaxInfNew->aspect_ratio_information    = BsGet(pBs, 4);
    pSyntaxInfNew->frame_rate_code             = BsGet(pBs, 4);
    pSyntaxInfNew->bit_rate_value              = BsGet(pBs, 18);
    if ( 0 == BsGet(pBs, 1) )
    {
        pMp2CodecInfo->StreamIntegrality|=MPEG2_ERROR_SEQHDR;//marker bit error
    }
    pSyntaxInfNew->vbv_buffer_size             = BsGet(pBs, 10);
    pSyntaxInfNew->constrained_parameters_flag = BsGet(pBs, 1);

    if (1 == (pSyntaxInfNew->load_intra_quantizer_matrix = BsGet(pBs, 1)))
    {
        for (i = 0; i < 64; i++)
        { pCtx->intra_quantizer_matrix[zigzag[i]] = BsGet(pBs, 8); }
    }
    else
    {
        for (i = 0; i < 64; i++)
        { pCtx->intra_quantizer_matrix[i] = default_intra_quantizer_matrix[i]; }
    }

    if (1 == (pSyntaxInfNew->load_non_intra_quantizer_matrix = BsGet(pBs, 1)))
    {
        for (i = 0; i < 64; i++)
        { pCtx->non_intra_quantizer_matrix[zigzag[i]] = BsGet(pBs, 8); }
    }
    else
    {
        for (i = 0; i < 64; i++)
        { pCtx->non_intra_quantizer_matrix[i] = 16; }
    }
    return ret;
}


/*!
************************************************************************
*    函数原型 :  group_of_pictures_header()
*    功能描述 :  为MPEG2解析gop头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID group_of_pictures_header(MP2_CTX_S *pCtx)
{
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    pSyntaxInfNew->drop_flag   = BsGet(pBs, 1);
    pSyntaxInfNew->hour        = BsGet(pBs, 5);
    pSyntaxInfNew->minute      = BsGet(pBs, 6);
    BsSkip(pBs, 1); //marker bit,GOP头对解码过程没有影响,因此此处无须检测marker的正确性
    pSyntaxInfNew->sec         = BsGet(pBs, 6);
    pSyntaxInfNew->frame       = BsGet(pBs, 6);
    pSyntaxInfNew->closed_gop  = BsGet(pBs, 1);
    pSyntaxInfNew->broken_link = BsGet(pBs, 1);    
    //swap gop history
    pCtx->CodecInfo.GopHist[0] = pCtx->CodecInfo.GopHist[1];
    pCtx->CodecInfo.GopHist[1] = pCtx->CodecInfo.GopHist[2];
    pCtx->CodecInfo.GopHist[2] = pCtx->CodecInfo.GopHist[3];
    //update gop information
    pCtx->CodecInfo.GopHist[3].GopFrmCntNoRpt = 0;
    pCtx->CodecInfo.GopHist[3].GopFrmCnt = 0;
    pCtx->CodecInfo.GopHist[3].GopFldCnt = 0;
}


/*!
************************************************************************
*    函数原型 :  picture_header()
*    功能描述 :  为MPEG2解析picture头
*    参数说明 :  无
*    返回值   :  1,找到起始码;0,找不到起始码
************************************************************************
*/
UINT32 picture_header(MP2_CTX_S *pCtx)
{
    UINT32 ret = MPEG2_TRUE;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    //清除图像级查找标志和错误标志,避免前一个图像头信息残留下来
    pMp2CodecInfo->StreamIntegrality   &= ~MPEG2_ALLPIC_FLAG;
    pMp2CodecInfo->StreamIntegrality   |= MPEG2_FOUND_PICHDR;
    pSyntaxInfNew->temporal_reference  = BsGet(pBs, 10);
    pSyntaxInfNew->picture_coding_type = BsGet(pBs, 3);
    pSyntaxInfNew->vbv_delay           = BsGet(pBs, 16);

    if (pSyntaxInfNew->picture_coding_type==P_TYPE || pSyntaxInfNew->picture_coding_type==B_TYPE)
    {
        pSyntaxInfNew->full_pel_forward_vector = BsGet(pBs, 1);
        pSyntaxInfNew->forward_f_code = BsGet(pBs, 3);
    }
    if (pSyntaxInfNew->picture_coding_type==B_TYPE)
    {
        pSyntaxInfNew->full_pel_backward_vector = BsGet(pBs, 1);
        pSyntaxInfNew->backward_f_code = BsGet(pBs, 3);
    }
    
    extra_bit_information(pCtx);
    return ret;
}


/*!
************************************************************************
*    函数原型 :  sequence_extension()
*    功能描述 :  为MPEG2解析sequence扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID sequence_extension(MP2_CTX_S *pCtx)
{
    UINT32 horizontal_size_extension;
    UINT32 vertical_size_extension;
    UINT32 bit_rate_extension;
    UINT32 vbv_buffer_size_extension;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    pMp2CodecInfo->StreamIntegrality |= MPEG2_FOUND_SEQEXT;
    pMp2CodecInfo->NewSeqInited = MPEG2_FALSE;
    pSyntaxInfNew->profile_and_level_indication = BsGet(pBs, 8);
    pSyntaxInfNew->progressive_sequence         = BsGet(pBs, 1);
    pSyntaxInfNew->chroma_format                = BsGet(pBs, 2);
    horizontal_size_extension    = BsGet(pBs, 2);
    vertical_size_extension      = BsGet(pBs, 2);
    bit_rate_extension           = BsGet(pBs, 12);
    if ( 0 == BsGet(pBs, 1) )
    {
        pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_SEQEXT;//marker bit error
        return;
    }
    vbv_buffer_size_extension    = BsGet(pBs, 8);
    pSyntaxInfNew->low_delay                    = BsGet(pBs, 1);
    pSyntaxInfNew->frame_rate_extension_n       = BsGet(pBs, 2);
    pSyntaxInfNew->frame_rate_extension_d       = BsGet(pBs, 5);

    if ((pSyntaxInfNew->frame_rate_extension_d+1) == 0)
    {
        pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_SEQEXT;
        return;
    }
    pSyntaxInfNew->frame_rate = frame_rate_Table[pSyntaxInfNew->frame_rate_code] *
        ((pSyntaxInfNew->frame_rate_extension_n+1)/(pSyntaxInfNew->frame_rate_extension_d+1));
    
    /* special case for 422 g_pSyntaxInfNew->profile & level must be made */
    if ((pSyntaxInfNew->profile_and_level_indication>>7) & 1)
    {  /* escape bit of profile_and_level_indication set */
        
        /* 4:2:2 Profile @ Main Level */
        if ((pSyntaxInfNew->profile_and_level_indication&15)==5)
        {
            pSyntaxInfNew->profile = PROFILE_422;
            pSyntaxInfNew->level   = MAIN_LEVEL;  
        }
    }
    else
    {
        pSyntaxInfNew->profile = (pSyntaxInfNew->profile_and_level_indication >> 4) & 0x07;  /* Profile is upper nibble */
        pSyntaxInfNew->level   = pSyntaxInfNew->profile_and_level_indication & 0x0F;  /* Level is lower nibble */
    }
    pSyntaxInfNew->horizontal_size = (horizontal_size_extension<<12) | (pSyntaxInfNew->horizontal_size&0x0fff);
    pSyntaxInfNew->vertical_size = (vertical_size_extension<<12) | (pSyntaxInfNew->vertical_size&0x0fff);
    if ((pSyntaxInfNew->horizontal_size==0)||(pSyntaxInfNew->vertical_size==0))
    {
        pMp2CodecInfo->StreamIntegrality|=MPEG2_ERROR_SEQHDR;
    }
    if ((pSyntaxInfNew->horizontal_size>MAX_HOR_SIZE)||(pSyntaxInfNew->vertical_size>MAX_VER_SIZE))
    {
        pMp2CodecInfo->StreamIntegrality|=MPEG2_ERROR_SEQHDR;
        REPORT_UNSUPPORT(pCtx->ChanID);
    }

    /* ISO/IEC 13818-2 does not define bit_rate_value to be composed of
    * both the original bit_rate_value parsed in sequence_header() and
    * the optional bit_rate_extension in sequence_extension_header(). 
    * However, we use it for bitstream verification purposes. 
    */
    
    pSyntaxInfNew->bit_rate_value += (bit_rate_extension << 18);
    pSyntaxInfNew->bit_rate = (pSyntaxInfNew->bit_rate_value) * 400;
    pSyntaxInfNew->vbv_buffer_size += (vbv_buffer_size_extension << 10);
    //seq ext check
    if ((pSyntaxInfNew->profile>5) || (pSyntaxInfNew->profile<4))
    {
        //不支持的profile
        REPORT_UNSUPPORT(pCtx->ChanID);
        dprint(PRN_ERROR, "ERROR: unsupported profile %d\n", pSyntaxInfNew->profile);
        //g_Mpeg2CodecInf.StreamIntegrality|=MPEG2_ERROR_SEQEXT;
    }
    if ( (pSyntaxInfNew->level>10) || (pSyntaxInfNew->level<4) )
    {
        REPORT_UNSUPPORT(pCtx->ChanID);
        dprint(PRN_ERROR, "ERROR: unsupported level %d\n", pSyntaxInfNew->level);
        //g_Mpeg2CodecInf.StreamIntegrality|=MPEG2_ERROR_SEQEXT;
    }

    return;
}


/*!
************************************************************************
*    函数原型 :  sequence_display_extension()
*    功能描述 :  为MPEG2解析sequence显示扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID sequence_display_extension(MP2_CTX_S *pCtx)
{
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    pMp2CodecInfo->StreamIntegrality |= MPEG2_FOUND_SEQDISPEXT;
    
    pSyntaxInfNew->video_format      = BsGet(pBs, 3);
    pSyntaxInfNew->color_description = BsGet(pBs, 1);
    
    if (pSyntaxInfNew->color_description)
    {
        pSyntaxInfNew->color_primaries          = BsGet(pBs, 8);
        pSyntaxInfNew->transfer_characteristics = BsGet(pBs, 8);
        pSyntaxInfNew->matrix_coefficients      = BsGet(pBs, 8);
    }
    
    pSyntaxInfNew->display_horizontal_size = BsGet(pBs, 14);
    if ( 0 == BsGet(pBs, 1) )
    {
        pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_SEQDISPEXT;  //marker bit error
        return;
    }
    pSyntaxInfNew->display_vertical_size = BsGet(pBs, 14);

    return;
}


/*!
************************************************************************
*    函数原型 :  quant_matrix_extension()
*    功能描述 :  为MPEG2解析量化矩阵扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID quant_matrix_extension(MP2_CTX_S *pCtx)
{
    UINT32 i;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    if (1==(pSyntaxInfNew->load_intra_quantizer_matrix = BsGet(pBs, 1)))
    {
        for (i=0; i<64; i++)
        {
            pCtx->intra_quantizer_matrix[zigzag[i]] = BsGet(pBs, 8);
        }
    }
    
    if (1==(pSyntaxInfNew->load_non_intra_quantizer_matrix = BsGet(pBs, 1)))
    {
        for (i=0; i<64; i++)
        {
            pCtx->non_intra_quantizer_matrix[zigzag[i]] = BsGet(pBs, 8);
        }
    }
    
    //chroma matrix reload, should not occur in 4:2:0
    if ( BsGet(pBs, 1) )
    {
        for (i=0; i<64; i++)
        {
            BsGet(pBs, 8);
        }
    }
    
    if (BsGet(pBs,1))
    {
        for (i=0; i<64; i++)
        {
            BsGet(pBs, 8);
        }
    }

    return;
}


/*!
************************************************************************
*    函数原型 :  sequence_scalable_extension()
*    功能描述 :  略过MPEG2 sequence scalable扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID sequence_scalable_extension(MP2_CTX_S *pCtx)
{
    BS *pBs;

    pBs = &pCtx->Bs;
    BsSkip(pBs, 32);

    return;
}


/*!
************************************************************************
*    函数原型 :  picture_display_extension()
*    功能描述 :  为MPEG2解析picture 回放扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID picture_display_extension(MP2_CTX_S *pCtx)
{
    SINT32 i;
    SINT32 number_of_frame_center_offsets;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    pMp2CodecInfo->StreamIntegrality |= MPEG2_FOUND_PICDISPEXT;
    
    /* based on ISO/IEC 13818-2 section 6.3.12 
    (November 1994) Picture display extensions */
    
    /* derive number_of_frame_center_offsets */
    if (pSyntaxInfNew->progressive_sequence)
    {
        if (pSyntaxInfNew->repeat_first_field)
        {
            if (pSyntaxInfNew->top_field_first)
            { number_of_frame_center_offsets = 3; }
            else
            { number_of_frame_center_offsets = 2; }
        }
        else
        {
            number_of_frame_center_offsets = 1;
        }
    }
    else
    {
        if (FRAME_PICTURE != pSyntaxInfNew->picture_structure)
        {
            number_of_frame_center_offsets = 1;
        }
        else
        {
            if (pSyntaxInfNew->repeat_first_field)
            {
                number_of_frame_center_offsets = 3;
            }
            else
            {
                number_of_frame_center_offsets = 2;
            }
        }
    }
    
    /* now parse */
    for (i=0; i<number_of_frame_center_offsets; i++)
    {
        pSyntaxInfNew->frame_center_horizontal_offset[i] = BsGet(pBs, 16);
        if (0 == BsGet(pBs, 1))
        {
            pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICDISPEXT;
            return;  //marker bit error
        }
        
        pSyntaxInfNew->frame_center_vertical_offset[i]   = BsGet(pBs, 16);
        if (0 == BsGet(pBs, 1))
        {
            pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICDISPEXT;
            return;  //marker bit error
        }
    }

    return;
}


/*!
************************************************************************
*    函数原型 :  picture_coding_extension()
*    功能描述 :  为MPEG2解析picture coding扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID picture_coding_extension(MP2_CTX_S *pCtx)
{    
    UINT32 i, j;
    MP2CODECINF *pMp2CodecInfo;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    pMp2CodecInfo->StreamIntegrality |= MPEG2_FOUND_PICEXT;

    for (j=0;j<2;j++)
    {
        for (i=0;i<2;i++)
        {
            pSyntaxInfNew->f_code[j][i] = BsGet(pBs, 4);
            if ((pSyntaxInfNew->f_code[j][i]==0)||
               ((pSyntaxInfNew->f_code[j][i]>9)&&(pSyntaxInfNew->f_code[j][i]<15)))
            {
                pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICEXT;
            }
        }
    }

    pSyntaxInfNew->intra_dc_precision         = BsGet(pBs, 2);
    pSyntaxInfNew->picture_structure          = BsGet(pBs, 2);
    if (pSyntaxInfNew->picture_structure==0)
    {
        pMp2CodecInfo->StreamIntegrality |= MPEG2_ERROR_PICEXT;
        return;
    }
    pSyntaxInfNew->top_field_first            = BsGet(pBs, 1);
    pSyntaxInfNew->frame_pred_frame_dct       = BsGet(pBs, 1);
    pSyntaxInfNew->concealment_motion_vectors = BsGet(pBs, 1);
    pSyntaxInfNew->q_scale_type               = BsGet(pBs, 1);
    pSyntaxInfNew->intra_vlc_format           = BsGet(pBs, 1);
    pSyntaxInfNew->alternate_scan             = BsGet(pBs, 1);
    pSyntaxInfNew->repeat_first_field         = BsGet(pBs, 1);
    pSyntaxInfNew->chroma_420_type            = BsGet(pBs, 1);
    pSyntaxInfNew->progressive_frame          = BsGet(pBs, 1);
    pSyntaxInfNew->composite_display_flag     = BsGet(pBs, 1);
    
    if (pSyntaxInfNew->composite_display_flag)
    {
        pSyntaxInfNew->v_axis            = BsGet(pBs, 1);
        pSyntaxInfNew->field_sequence    = BsGet(pBs, 3);
        pSyntaxInfNew->sub_carrier       = BsGet(pBs, 1);
        pSyntaxInfNew->burst_amplitude   = BsGet(pBs, 7);
        pSyntaxInfNew->sub_carrier_phase = BsGet(pBs, 8);
    }

    return;
}


/*!
************************************************************************
*    函数原型 :  picture_spatial_scalable_extension()
*    功能描述 :  略过MPEG2 picture spatial scalable扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID picture_spatial_scalable_extension(MP2_CTX_S *pCtx)
{
    BS *pBs;

    pBs = &pCtx->Bs;
    BsSkip(pBs, 32);

    return;
}


/*!
************************************************************************
*    函数原型 :  picture_temporal_scalable_extension()
*    功能描述 :  略过MPEG2 picture temporal scalable扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID picture_temporal_scalable_extension(MP2_CTX_S *pCtx)
{
    BS *pBs;

    pBs = &pCtx->Bs;
    BsSkip(pBs, 32);

    return;
}


/*!
************************************************************************
*    函数原型 :  extra_bit_information()
*    功能描述 :  略过MPEG2 extra bit 信息
*    参数说明 :  无
*    返回值   :  消耗的字节数
************************************************************************
*/
UINT32 extra_bit_information(MP2_CTX_S *pCtx)
{
    UINT32 Byte_Count = 0;
    BS *pBs;

    pBs = &pCtx->Bs;

    while (BsGet(pBs, 1))
    {
        BsSkip(pBs, 8);
        Byte_Count++;
        if (BsResidBits(pBs)<9)
        {
            //此处是隐患,避免无限度吞噬码流
            //该调用不会太多,因此加入检查不会对效率有过多影响
            break;
        }
    }

    return Byte_Count;
}

/*!
************************************************************************
*    函数原型 :  copyright_extension()
*    功能描述 :  略过MPEG2版权扩展头
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID copyright_extension(MP2_CTX_S *pCtx)
{
    BS *pBs;

    pBs = &pCtx->Bs;
    BsSkip(pBs, 32);

    return;
}

/*!
************************************************************************
*    函数原型 :  extension()
*    功能描述 :  为MPEG2解析扩展
*    参数说明 :  无
*    返回值   :  1,找到起始码;0,找不到起始码
************************************************************************
*/
UINT32 extension(MP2_CTX_S *pCtx)
{
    UINT32 ext_ID, ret = MPEG2_TRUE;
    BS *pBs;
    MP2SYNTAXINF *pSyntaxInfNew = pCtx->pSyntaxInfNew;
 
    pSyntaxInfNew->display_horizontal_size = 0;
	pSyntaxInfNew->display_vertical_size = 0;
    pSyntaxInfNew->video_format = 0;   
    pSyntaxInfNew->color_description = 0; 
    pSyntaxInfNew->color_primaries = 0; 
    pSyntaxInfNew->transfer_characteristics = 0;
    pSyntaxInfNew->matrix_coefficients = 0; 
    pSyntaxInfNew->display_horizontal_size = 0; 
    pSyntaxInfNew->display_vertical_size = 0; 

    pBs = &pCtx->Bs;
    ext_ID = BsGet(pBs, 4);
    switch (ext_ID)
        {
            case SEQUENCE_EXTENSION_ID:
                sequence_extension(pCtx);
                break;
            case SEQUENCE_DISPLAY_EXTENSION_ID:
                sequence_display_extension(pCtx);
                break;
            case QUANT_MATRIX_EXTENSION_ID:
                quant_matrix_extension(pCtx);
                break;
            case SEQUENCE_SCALABLE_EXTENSION_ID:
                sequence_scalable_extension(pCtx);
                break;
            case PICTURE_DISPLAY_EXTENSION_ID:
                picture_display_extension(pCtx);
                break;
            case PICTURE_CODING_EXTENSION_ID:
				picture_coding_extension(pCtx);
				#if 0
				if (MPEG2_FALSE == pMp2CodecInfo->NewSeqInited)
            	{
                	MP2_GetSequenceInfo(pCtx);
            	}
            	MP2_ProtocolPPSCheck(pCtx);
				#endif
                break;
            case PICTURE_SPATIAL_SCALABLE_EXTENSION_ID:
                picture_spatial_scalable_extension(pCtx);
                break;
            case PICTURE_TEMPORAL_SCALABLE_EXTENSION_ID:
                picture_temporal_scalable_extension(pCtx);
                break;
            case COPYRIGHT_EXTENSION_ID:
                copyright_extension(pCtx);
                break;
            default:
                break;
        }

    return ret;
}


/*!
************************************************************************
*    函数原型 :  MPEG2_init_decoder()
*    功能描述 :  对MPEG2解码器进行初始化
*    参数说明 :  无
*    返回值   :  正确初始化返回1,否则返回错误码
************************************************************************
*/
SINT32 MPEG2DEC_Init(MP2_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    MP2CODECINF *pMp2CodecInfo;
    SINT32 ImgQueRstMagic;   
    UINT32 intra_quantizer_matrix[MPEG2_BLOCK_SIZE];
    UINT32 non_intra_quantizer_matrix[MPEG2_BLOCK_SIZE];
    MP2SYNTAXINF  SyntaxInfNew;
    MP2SYNTAXINF  SyntaxInfOld;
    
    if (1 == pstExtraData->s32KeepSPSPPS) //omx mpeg2 seek
    {
        memcpy(intra_quantizer_matrix, pCtx->intra_quantizer_matrix, sizeof(pCtx->intra_quantizer_matrix));
        memcpy(non_intra_quantizer_matrix, pCtx->non_intra_quantizer_matrix, sizeof(pCtx->non_intra_quantizer_matrix));
        memcpy(&SyntaxInfNew, pCtx->pSyntaxInfNew, sizeof(MP2SYNTAXINF));
        memcpy(&SyntaxInfOld, pCtx->pSyntaxInfOld, sizeof(MP2SYNTAXINF));
    }
    
    //初始化
    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    memset(pCtx, 0, sizeof(MP2_CTX_S));
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue); 

    pCtx->pstExtraData = pstExtraData;

    pMp2CodecInfo = &pCtx->CodecInfo;

    //语法结构需要有备份,以防错误的头修改正确信息
    pCtx->pSyntaxInfOld = &pCtx->SyntaxInf[0];
    pCtx->pSyntaxInfNew = &pCtx->SyntaxInf[1];
    pCtx->PPicFound = 0;        

    pMp2CodecInfo->Second_Field = 1;
    pMp2CodecInfo->Last_FieldStruct = FRAME_PICTURE;
    pMp2CodecInfo->HDRState = STATE_GET_PICHDR;
    pMp2CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
    pMp2CodecInfo->Imgbuf_allocated = MPEG2_FALSE;
	
    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }
    
    if (1 == pstExtraData->s32KeepSPSPPS)
    {
        memcpy(pCtx->intra_quantizer_matrix, intra_quantizer_matrix, sizeof(pCtx->intra_quantizer_matrix));
        memcpy(pCtx->non_intra_quantizer_matrix, non_intra_quantizer_matrix, sizeof(pCtx->non_intra_quantizer_matrix));
        memcpy(pCtx->pSyntaxInfNew, &SyntaxInfNew, sizeof(MP2SYNTAXINF));
        memcpy(pCtx->pSyntaxInfOld, &SyntaxInfOld, sizeof(MP2SYNTAXINF));
    }

    return VF_OK;
}


/*!
************************************************************************
*    函数原型 :  MPEG2_destroy_decoder()
*    功能描述 :  对MPEG2解码器进行销毁
*    参数说明 :  无
*    返回值   :  正确销毁返回1,否则返回错误码
************************************************************************
*/
SINT32 MPEG2DEC_Destroy(MP2_CTX_S *pCtx)
{
    MP2CODECINF *pMp2CodecInfo;

    pMp2CodecInfo = &pCtx->CodecInfo;
    dprint(PRN_CTRL, "Decoding quits at frm %d\n", pMp2CodecInfo->Frame_Cnt);

    return MPEG2_TRUE;
}


/*!
************************************************************************
*    函数原型 :  MPEG2_decode_packet()
*    功能描述 :  解码一个数据包
*    参数说明 :  packet 指向码流信息的指针.码流地址必须连续,地址必须没有折回
*    返回值   :  当前包已消耗的bit数,如果为负表示解析码流失败
************************************************************************
*/
SINT32 MPEG2DEC_Decode(MP2_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    SINT32 ret = MPEG2_FALSE;
//    MP2_DEC_PARAM_S *pMp2DecParam;
    MP2CODECINF *pMp2CodecInfo;

//    pMp2DecParam = &pCtx->Mp2DecParam;
    pMp2CodecInfo = &pCtx->CodecInfo;

//    memset(pMp2DecParam, 0, sizeof(MP2_DEC_PARAM_S));
    memcpy(&(pCtx->stCurPacket), pPacket, sizeof(DEC_STREAM_PACKET_S));
    
    if(MPEG2_TRUE != MP2_ReceivePacket(pMp2CodecInfo, &(pCtx->stCurPacket), pCtx->ChanID))
    {
        dprint(PRN_ERROR, "line %d, MP2_ReceivePacket receive packet failed!\n");
        return MPEG2_FALSE;
    }

#if 0
    if (NULL == pPacket)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet pointer!\n", pMp2CodecInfo->Frame_Cnt);
        return 0;
    }

    memset( pMp2DecParam, 0, sizeof(MP2_DEC_PARAM_S) );

    //if start new pic, length1 should be reserved for VFMW searching and parsing
    pMp2CodecInfo->BsOffset = 0;
    pMp2CodecInfo->PacketTail = pPacket->StreamPack[0].LenInByte;

    //adjust bs start address from updated offset
    pMp2CodecInfo->BsPhyAddr = pPacket->StreamPack[0].PhyAddr + pMp2CodecInfo->BsOffset;
    pMp2CodecInfo->BsVirAddr = pPacket->StreamPack[0].VirAddr + pMp2CodecInfo->BsOffset;
    pMp2CodecInfo->BsLength  = pPacket->StreamPack[0].LenInByte - pMp2CodecInfo->BsOffset;
    pMp2CodecInfo->IsLastSeg = pPacket->StreamPack[0].IsLastSeg;

    if (1 != pPacket->StreamPack[0].IsLastSeg)
    {
        pMp2CodecInfo->BsPhyAddr1 =  pPacket->StreamPack[1].PhyAddr;
        pMp2CodecInfo->BsVirAddr1 =  pPacket->StreamPack[1].VirAddr;
        pMp2CodecInfo->BsLength1 =  pPacket->StreamPack[1].LenInByte;
        pMp2CodecInfo->IsLastSeg1 = pPacket->StreamPack[1].IsLastSeg;
        if (1 != pPacket->StreamPack[1].IsLastSeg)
        {
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[0].StreamID);
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[1].StreamID);
            REPORT_DECSYNTAX_ERR(pCtx->ChanID);
            return 0;
        }
        //dprint(PRN_DBG,"****PhyAddr = 0x%x len = 0x%x******\n", pMp2CodecInfo->BsPhyAddr, pMp2CodecInfo->BsLength);
        //dprint(PRN_DBG,"****PhyAddr1 = 0x%x len1 = 0x%x******\n", pMp2CodecInfo->BsPhyAddr1, pMp2CodecInfo->BsLength1);    
    }
    else
    {
        //dprint(PRN_DBG,"****PhyAddr = 0x%x len = 0x%x******\n", pMp2CodecInfo->BsPhyAddr, pMp2CodecInfo->BsLength);
        pMp2CodecInfo->BsPhyAddr1 = 0;
        pMp2CodecInfo->BsVirAddr1 = 0;
        pMp2CodecInfo->BsLength1  = 0;
        pMp2CodecInfo->IsLastSeg1 = 0;
    }
#endif    
    BsInit(&pCtx->Bs, pMp2CodecInfo->stMp2Packet.BsVirAddr[0], pMp2CodecInfo->stMp2Packet.BsLength[0]);

    if((1 == pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
       (1 == pCtx->pstExtraData->s32WaitFsFlag))
    {
        pCtx->CodecInfo.StreamIntegrality = pCtx->CodecInfo.LastStreamIntegrality;
    }
    else
    {
        pCtx->CodecInfo.LastStreamIntegrality = pCtx->CodecInfo.StreamIntegrality;
    }
    /*new picture*/
    /*refresh register pointers and msg pointers*/
    ret = MP2_GetHDR(pCtx);
    if((ret == MPEG2_FALSE) || (ret == NOTENOUGH_STREAM))
    {
        if(((1 != pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) || \
           ((1 == pCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
            (0 == pCtx->pstExtraData->s32WaitFsFlag))) && 1 != pCtx->IsWaitToReRange)
        {
            MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
        }
        ret = MPEG2_FALSE;
        return ret;
    }

    ret = MP2_DecodingDecide(pCtx);
    if(ret == MPEG2_FALSE)
    {
        MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
        MP2_ClearCurPic(pCtx);
        REPORT_DECSYNTAX_ERR(pCtx->ChanID);
        dprint(PRN_DBG,"MP2 Decode Decide is wrong!\n");
        return MPEG2_FALSE;
    }
	else if(ret == NOTENOUGH_STREAM)
	{
	#ifndef SCD_MP4_SLICE_ENABLE 	
        MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
        MP2_ClearCurPic(pCtx);
	#endif		
		return MPEG2_FALSE;
	}
		
    if(MPEG2_FALSE == MP2_GetPictureInfo(pCtx))	
    {
        MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
        MP2_ClearCurPic(pCtx);
        REPORT_DECSYNTAX_ERR(pCtx->ChanID);
        dprint(PRN_ERROR,"MP2 get picture info is wrong!\n");
        ret = MPEG2_FALSE;
        return ret;
    }

    if(MPEG2_FALSE == MP2_DecNewPic(pCtx))
    {
        FSP_ClearLogicFs(pCtx->ChanID, pMp2CodecInfo->CurFsID, 1);
        MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
        MP2_ClearCurPic(pCtx);
        REPORT_DECSYNTAX_ERR(pCtx->ChanID);
        dprint(PRN_ERROR,"MP2 dec new pic failed!\n");
        ret = MPEG2_FALSE;
        return ret;
    }
#if 0    
    hdr = MP2_GetHDR(pCtx);
    if (FOUND_SLCHDR == hdr) 
    {
        ret = MP2_DecodingDecide(pCtx);
        if (MPEG2_TRUE == ret)
        {
            //当前图像适合解码
            ret = MP2_GetPictureInfo(pCtx);
            if (MPEG2_TRUE == ret)
            {
                MP2_DecNewPic(pCtx);
            }
            else
            {
                REPORT_DECSYNTAX_ERR(pCtx->ChanID);
            }
        }
        else
        {
            REPORT_DECSYNTAX_ERR(pCtx->ChanID);
        }
    }
    if(MPEG2_FALSE == ret)
    { 
        MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
#if 0
        SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[0].StreamID);

        if(1 != pPacket->StreamPack[0].IsLastSeg)
        {
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[1].StreamID);
        }
#endif        
        return MPEG2_FALSE;
    }
#endif
    //only count stream usage before return
    pMp2CodecInfo->Used_byte += pMp2CodecInfo->stMp2Packet.BsLength[0];
#if 0
    if ((-1==ret) || (MPEG2_FALSE==ret))
    {
        return -1;
    }
    else
    {
        return pMp2CodecInfo->BsOffset*8;
    }
#endif 
    // 20130822:TQE 没有判断返回值
    return pMp2CodecInfo->BsOffset*8;

}


/*!
************************************************************************
*    函数原型 :  MPEG2DEC_RecycleImage()
*    功能描述 :  按照给定的帧存序号回收一个帧存空间
*    参数说明 :  img_id 需要回收的图像id
*    返回值   :  测试中永远为1
************************************************************************
*/
SINT32 MPEG2DEC_RecycleImage(MP2_CTX_S *pCtx, UINT32 img_id)
{
    MP2CODECINF *pMp2CodecInfo;
    IMAGE *pImg;
    SINT32 i = 0;

    if (NULL == pCtx)
    {
        return MPEG2_FALSE;
    }

    pMp2CodecInfo = &pCtx->CodecInfo;

    FSP_SetDisplay(pCtx->ChanID, img_id, 0);
	pImg = FSP_GetFsImagePtr(pCtx->ChanID, img_id);
	if (NULL != pImg)
	{
        for(i = 0; i < MAX_USERDATA_NUM; i++)
        {
            FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[i]);
            pImg->p_usrdat[i] = NULL;
        }
        #if 0
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        pImg->p_usrdat[0] = NULL;
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        pImg->p_usrdat[1] = NULL;            
        #endif
	}
    return MPEG2_TRUE;
}


SINT32 MPEG2DEC_GetRemainImg(MP2_CTX_S *pCtx)
{
    MP2CODECINF *pMp2CodecInfo;
    IMAGE  *pImg = NULL;
    SINT32 display_flag;
    SINT32 ret = LAST_OUTPUT_FAIL;
    SINT32 i=0;
    pMp2CodecInfo = &pCtx->CodecInfo;

    if (OUTPUT_IN_DEC == pCtx->pstExtraData->s32DecOrderOutput)    // 解码序，已经输出
    { 
        ret = LAST_ALREADY_OUT;
    }
    else        //显示序
    {
        pImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->BwdFsID);
        if (NULL != pImg)
        {
            display_flag = FSP_GetDisplay(pCtx->ChanID,pMp2CodecInfo->BwdFsID);
            if (FS_DISP_STATE_DEC_COMPLETE == display_flag)           // 还没插入队列
            {
                MP2_SetImgFormat(pCtx);
            #if 0
                MP2_ATTACHUDINF(pImg->p_usrdat[0], pMp2CodecInfo->p_SeqUD);
                pMp2CodecInfo->p_SeqUD = NULL;
                MP2_ATTACHUDINF(pImg->p_usrdat[1], pMp2CodecInfo->p_PicUD);
                pMp2CodecInfo->p_PicUD = NULL;
            #endif
                for(i = 0; i < MAX_USERDATA_NUM; i++)
                {
                    MP2_ATTACHUDINF(pImg->p_usrdat[i], pMp2CodecInfo->pUsrDatArray[i]);
                    pMp2CodecInfo->pUsrDatArray[i] = NULL;
                }
                pMp2CodecInfo->TotalUsrDatNum = 0;
				pImg->last_frame = 1;

                FSP_SetDisplay(pCtx->ChanID, pImg->image_id, 1);
                if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_MPEG2, pCtx, &pCtx->ImageQue, pImg))   // 插入队列失败
                {
                    MPEG2DEC_RecycleImage(pCtx, pImg->image_id);
                #if 0
                    FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
                    pImg->p_usrdat[0] = NULL;
                    FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
                    pImg->p_usrdat[1] = NULL;
                #endif
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
            else  //  之前已经插到队列中
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


UINT32 MPEG2DEC_VDMPostProc(MP2_CTX_S *pCtx, SINT32 ErrRatio)
{
    MP2CODECINF *pMp2CodecInfo;
    MP2SYNTAXINF *pSyntaxInfNew;
	IMAGE  *pCurImg, *pBwdImg, *pFwdImg, *pToQueImg;
    MP2_DEC_PARAM_S *pMp2DecParam;
    SINT32 i=0;
    pMp2DecParam = &pCtx->Mp2DecParam;
    pMp2CodecInfo = &pCtx->CodecInfo;
    pSyntaxInfNew = pCtx->pSyntaxInfNew;

    pMp2CodecInfo->EstmatedPicQp = pMp2DecParam->EstmatedPicQp;   // Last frame

    MP2_RecordVFMWState(pCtx);  
//    ReleasePacket(VFMW_MPEG2, pCtx);
#ifndef SCD_MP4_SLICE_ENABLE  
    MP2_ClearCurPacket(pCtx->ChanID, &(pMp2CodecInfo->stMp2Packet));
#else
    MP2_ClearCurPic(pCtx);
#endif
    memset(pMp2DecParam, 0, sizeof(MP2_DEC_PARAM_S));

    pCurImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->CurFsID);
	pBwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->BwdFsID);
	pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->FwdFsID);

    if (pCurImg == NULL)//(pFwdImg == NULL))  前向参考帧此函数不用，因此无需判断
    {
        dprint(PRN_FATAL,"pImg is null, pCurImg %p pBwdImg %p pFwdImg %p\n", pCurImg, pBwdImg, pFwdImg);
		return MPEG2_FALSE;
	}

    pMp2CodecInfo->LastDecPicCodingType = pSyntaxInfNew->picture_coding_type;	

	/* 处理err_level */
    if(0) //if ((FRAME_PICTURE==pSyntaxInfNew->picture_structure) || (1==pMp2CodecInfo->Second_Field))
    {
        pCurImg->error_level += ErrRatio;
    }
	else
	{
        pCurImg->error_level = ErrRatio;
	}
	pCurImg->error_level = CLIP1(100, (SINT32)(pCurImg->error_level));

    if (B_TYPE != pSyntaxInfNew->picture_coding_type && pCurImg->error_level > pCtx->pstExtraData->s32RefErrThr)
    {
        MP2_CLEARREFFLAG;
        MP2_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过
        return DEC_OVER;
    }

	/* 将图像输出到VO队列 */
    dprint(PRN_DBG, "DEBUG: DEC over\n");
    MP2_SetImgFormat(pCtx);
    if ( (pSyntaxInfNew->picture_structure==FRAME_PICTURE || pMp2CodecInfo->Second_Field==1) )
    {
        for(i = 0; i < MAX_USERDATA_NUM; i++)
        {
            MP2_ATTACHUDINF(pCurImg->p_usrdat[i], pMp2CodecInfo->pUsrDatArray[i]);
            pMp2CodecInfo->pUsrDatArray[i] = NULL;
        }
        pMp2CodecInfo->TotalUsrDatNum = 0;
        #if 0
        MP2_ATTACHUDINF(pCurImg->p_usrdat[0], pMp2CodecInfo->p_SeqUD);
        MP2_ATTACHUDINF(pCurImg->p_usrdat[1], pMp2CodecInfo->p_PicUD);
        pMp2CodecInfo->p_SeqUD = NULL;
        pMp2CodecInfo->p_PicUD = NULL;
        #endif                
        //if ( I_MODE == pMp2CodecInfo->UsedDecMode )
        //{
        //pMp2CodecInfo->ToQueFsID = pMp2CodecInfo->CurFsID;
        //}
        //else
        {
            if (OUTPUT_IN_DEC != pCtx->pstExtraData->s32DecOrderOutput) /* if(显示序输出) */
            {
                if (B_TYPE != pSyntaxInfNew->picture_coding_type)
                {
                    //pMp2CodecInfo->ToQueFsID = (pMp2CodecInfo->RefNum > 1)? pMp2CodecInfo->FwdFsID: -1;
                    /* 为了缩短换台时间，第一个I帧需要快速输出，所以不判断 (pMp2CodecInfo->RefNum > 1)*/
                    pMp2CodecInfo->ToQueFsID = pMp2CodecInfo->FwdFsID;
                }
                else
                {
                    pMp2CodecInfo->ToQueFsID = pMp2CodecInfo->CurFsID;
                    #if 0
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
                    #endif
                }                
            }
            else
            {
                pMp2CodecInfo->ToQueFsID = pMp2CodecInfo->CurFsID;
            }
        }

        /* 为了缩短换台时间，第一个I帧需要快速输出，所以这里第一个I帧会重复输出。为了防止因此出现问题，
		   增加对帧存状态的判断，若已经WAIT_DISP, 则说明此帧已经输出，这次不予输出. */
        if ( -1 != pMp2CodecInfo->ToQueFsID && 
			(FS_DISP_STATE_ALLOCED == FSP_GetDisplay(pCtx->ChanID, pMp2CodecInfo->ToQueFsID) || 
			 FS_DISP_STATE_DEC_COMPLETE == FSP_GetDisplay(pCtx->ChanID, pMp2CodecInfo->ToQueFsID))
		   )
        {
            pToQueImg = FSP_GetFsImagePtr(pCtx->ChanID, pMp2CodecInfo->ToQueFsID);
            if (NULL == pToQueImg)
            {
                dprint(PRN_FATAL, "line: %d, pImage is NULL!\n", __LINE__);
                return MPEG2_FALSE;
            }
			
            if (pToQueImg->error_level == 0 || pToQueImg->error_level <= pCtx->pstExtraData->s32OutErrThr)
            {
	            dprint(PRN_QUEUE, "insert buf %d ref %d\n", pMp2CodecInfo->ToQueFsID, FSP_GetRef(pCtx->ChanID, pMp2CodecInfo->ToQueFsID));
			
				FSP_SetDisplay(pCtx->ChanID, pMp2CodecInfo->ToQueFsID, 1);
	            if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_MPEG2, pCtx, &pCtx->ImageQue, pToQueImg))
	            {
                    for(i = 0; i < MAX_USERDATA_NUM; i++)
                    {
                        FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[i]);
                        pToQueImg->p_usrdat[i] = NULL;
                    }
                    #if 0
	                FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
	                pToQueImg->p_usrdat[0] = NULL;
	                FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
	                pToQueImg->p_usrdat[1] = NULL;
                    #endif
					FSP_SetDisplay(pCtx->ChanID, pMp2CodecInfo->ToQueFsID, 0);
	                return MPEG2_FALSE;
	            }
				pCtx->numOutputFrame++;
            }
			else
			{
		        dprint(PRN_ERROR,"err(%d) > out_thr(%d)\n", pToQueImg->error_level, pCtx->pstExtraData->s32OutErrThr);
                for(i = 0; i < MAX_USERDATA_NUM; i++)
                {
                    FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[i]);
                    pToQueImg->p_usrdat[i] = NULL;
                }
                #if 0
                FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
                pToQueImg->p_usrdat[0] = NULL;
                FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
                pToQueImg->p_usrdat[1] = NULL;
                #endif
				FSP_SetDisplay(pCtx->ChanID, pMp2CodecInfo->ToQueFsID, 0);
			}
        }
		
        if(1 == pSyntaxInfNew->progressive_sequence)
        {
            pMp2CodecInfo->GopHist[3].GopFrmCnt += 
                (pSyntaxInfNew->repeat_first_field+pSyntaxInfNew->top_field_first+1);
            pMp2CodecInfo->GopHist[3].GopFldCnt = 2 * pMp2CodecInfo->GopHist[3].GopFrmCnt;
        }
        else if(1 == pSyntaxInfNew->progressive_frame)
        {
            //in this case, fld num will not match (2 * frm num)
            pMp2CodecInfo->GopHist[3].GopFrmCnt++; 
            pMp2CodecInfo->GopHist[3].GopFldCnt += 
                (2+pSyntaxInfNew->repeat_first_field);
        }
        else
        {
            pMp2CodecInfo->GopHist[3].GopFrmCnt++;
            pMp2CodecInfo->GopHist[3].GopFldCnt = 2 * pMp2CodecInfo->GopHist[3].GopFrmCnt;
        }
        pCtx->CodecInfo.GopHist[3].GopFrmCntNoRpt ++;
        pMp2CodecInfo->Frame_Cnt++;
    }

    return DEC_OVER;
}



SINT32 MPEG2DEC_GetImageBuffer( MP2_CTX_S *pCtx )
{
    MP2CODECINF *pMp2CodecInfo;
    MP2VOBUFINF *pVOBufInf;

    pMp2CodecInfo = &pCtx->CodecInfo;
    pVOBufInf = pCtx->CodecInfo.VOBufInf;

    /* 1. 如果之前解了一个场对中的一场，另一场待解，返回TRUE */
    if ((FRAME_PICTURE!=pMp2CodecInfo->Last_FieldStruct)&&(0==pMp2CodecInfo->Second_Field))
    {
        return 1;
	}

	/* 2. 否则，如果FSP中有新的帧存可以获取，返回TRUE */
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

SINT32 MP2_ReceivePacket(MP2CODECINF *pMp2CodecInfo, DEC_STREAM_PACKET_S *pPacket, SINT32 ChanID)
{
    
    if (NULL == pPacket)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet pointer!\n", pMp2CodecInfo->Frame_Cnt);
        return MPEG2_FALSE;
    }

    //if start new pic, length1 should be reserved for VFMW searching and parsing
    pMp2CodecInfo->BsOffset = 0;
    pMp2CodecInfo->PacketTail = pPacket->StreamPack[0].LenInByte;

    //adjust bs start address from updated offset
    pMp2CodecInfo->stMp2Packet.BsPhyAddr[0] = pPacket->StreamPack[0].PhyAddr + pMp2CodecInfo->BsOffset;
    pMp2CodecInfo->stMp2Packet.BsVirAddr[0] = pPacket->StreamPack[0].VirAddr + pMp2CodecInfo->BsOffset;
    pMp2CodecInfo->stMp2Packet.BsLength[0]  = pPacket->StreamPack[0].LenInByte - pMp2CodecInfo->BsOffset;
    pMp2CodecInfo->stMp2Packet.IsLastSeg[0] = pPacket->StreamPack[0].IsLastSeg;
    pMp2CodecInfo->stMp2Packet.StreamID[0]  = pPacket->StreamPack[0].StreamID;
    
    if (1 != pPacket->StreamPack[0].IsLastSeg)
    {
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[1] =  pPacket->StreamPack[1].PhyAddr;
        pMp2CodecInfo->stMp2Packet.BsVirAddr[1] =  pPacket->StreamPack[1].VirAddr;
        pMp2CodecInfo->stMp2Packet.BsLength[1]  =  pPacket->StreamPack[1].LenInByte;
        pMp2CodecInfo->stMp2Packet.IsLastSeg[1] = pPacket->StreamPack[1].IsLastSeg;
        pMp2CodecInfo->stMp2Packet.StreamID[1]  = pPacket->StreamPack[1].StreamID;
        
        if (1 != pPacket->StreamPack[1].IsLastSeg)
        {
            MP2_ClearCurPacket(ChanID, &(pMp2CodecInfo->stMp2Packet));
            dprint(PRN_ERROR, "line %d, pPacket->StreamPack[1].IsLastSeg = %d\n", pPacket->StreamPack[1].IsLastSeg);
            return MPEG2_FALSE;
        }
        //dprint(PRN_DBG,"****PhyAddr = 0x%x len = 0x%x******\n", pMp2CodecInfo->BsPhyAddr, pMp2CodecInfo->BsLength);
        //dprint(PRN_DBG,"****PhyAddr1 = 0x%x len1 = 0x%x******\n", pMp2CodecInfo->BsPhyAddr1, pMp2CodecInfo->BsLength1);    
    }
    else
    {
        //dprint(PRN_DBG,"****PhyAddr = 0x%x len = 0x%x******\n", pMp2CodecInfo->BsPhyAddr, pMp2CodecInfo->BsLength);
        pMp2CodecInfo->stMp2Packet.BsPhyAddr[1] = 0;
        pMp2CodecInfo->stMp2Packet.BsVirAddr[1] = 0;
        pMp2CodecInfo->stMp2Packet.BsLength[1]  = 0;
        pMp2CodecInfo->stMp2Packet.IsLastSeg[1] = 0;
        pMp2CodecInfo->stMp2Packet.StreamID[1]  = 0; 
    }

    return MPEG2_TRUE;
}

VOID MP2_ClearCurPacket(SINT32 ChanID, MP2_STREAM_PACKET *pMp2Packet)
{
    SM_ReleaseStreamSeg(ChanID, pMp2Packet->StreamID[0]);
    
    if(1 != pMp2Packet->IsLastSeg[0])
    {
        SM_ReleaseStreamSeg(ChanID, pMp2Packet->StreamID[1]);
    }
    
    memset(pMp2Packet, 0, sizeof(MP2_STREAM_PACKET));
}

VOID MP2_ClearCurPic(MP2_CTX_S *pCtx)
{
    SINT32 i;
    MP2_DEC_PARAM_S *pDecParam = &(pCtx->Mp2DecParam);

    for(i = 0; i < pDecParam->SlcNum; i++)
    {
        SM_ReleaseStreamSeg(pCtx->ChanID, pDecParam->SlcStr[i].BsID[0]); 
        if((pDecParam->SlcStr[i].BsPhyAddr[1] != 0) && (pDecParam->SlcStr[i].BsLenInBit[1] != 0))
        {
            SM_ReleaseStreamSeg(pCtx->ChanID, pDecParam->SlcStr[i].BsID[1]);
        }
    }
    pDecParam->SlcNum = 0;

}

SINT32 MP2_DecSlice(MP2_CTX_S *pCtx, UINT32 code)
{
    SINT32 ret = MPEG2_TRUE;
    MP2CODECINF *pMp2CodecInfo = NULL;
    MP2_SLCINFO_S *pSlcInfo = NULL;
    MP2SYNTAXINF *pSyntaxInfNew;
 
    pMp2CodecInfo = &pCtx->CodecInfo;
    pSlcInfo = &(pCtx->SliceInfo);
    pSyntaxInfNew = pCtx->pSyntaxInfNew;
        
    pSlcInfo->VirAddr = pMp2CodecInfo->stMp2Packet.BsVirAddr[0];
    pSlcInfo->ByteLen = pMp2CodecInfo->stMp2Packet.BsLength[0];
    pSlcInfo->mpeg1_flag = (PROTOCOL_MPEG1 == pMp2CodecInfo->MpegFlag);
    pSlcInfo->pic_height_in_mb = pSyntaxInfNew->mb_height;
    pSlcInfo->pic_width_in_mb = pSyntaxInfNew->mb_width;
    pSlcInfo->pic_total_mb_num = (((pSyntaxInfNew->horizontal_size + 15)/16)*
                                 ((pSyntaxInfNew->vertical_size + 15)/16));
    pSlcInfo->slice_vertical_position = code & 0xff;

    pSlcInfo->pBs = &(pCtx->Bs);

    if(MPEG2_TRUE != MP2_GetFirstMbInSlice(pSlcInfo))
    {
        dprint(PRN_ERROR, "MP2_GetFirstMbInSlice Failed!\n");
        return MPEG2_FALSE;
    }

    /* 计算下行消息所需要的 slice 信息 */
    if(MPEG2_TRUE != MP2_WriteSliceInfo(pCtx))
    {
        dprint(PRN_ERROR, "MP2_WriteSliceInfo Failed!\n");
        return MPEG2_FALSE;
    }

    return ret;

}

SINT32 MP2_GetFirstMbInSlice( MP2_SLCINFO_S *pSlcInfo)
{
    SINT32 ret;

    /*解码sliceHeader, 同时完成slicedata解码所需的相关信息初始化*/
    MP2_DecSliceHeader(pSlcInfo);

    /*Mb初始化: 完成宏块坐标计算，解码 macroblock_escape 和 address_increment解码 */
    ret = MP2_InitMb(pSlcInfo);

    /*退出宏块解码*/
    MP2_ExitMb(pSlcInfo);

    return ret;
}

SINT32 MP2_DecSliceHeader(MP2_SLCINFO_S *pSlcInfo)
{
    UINT32 mb_row, mb_width;
    BS *pBs = pSlcInfo->pBs;

    pSlcInfo->FirstMbInSliceFlag = 1;
    pSlcInfo->slice_vertical_position_extension = 0;

    /*下面要加是否为Mpeg2的判断*/
    if ((pSlcInfo->pic_height_in_mb > 175) && (0 == pSlcInfo->mpeg1_flag))
    {
        pSlcInfo->slice_vertical_position_extension = MP2_u_v(pBs, 3, "slice_vertical_position");
    }

    /*计算前一个slice对应的宏块行最后一个宏块地址*/
    mb_width = pSlcInfo->pic_width_in_mb;
    mb_row = (pSlcInfo->slice_vertical_position_extension << 7) + pSlcInfo->slice_vertical_position - 1;
    pSlcInfo->previous_macroblock_address = (mb_width*mb_row > 0)? (mb_width*mb_row -1): 0;
    pSlcInfo->quantiser_scale_code = MP2_u_v(pBs, 5, "quantiser_scale_code");

    /*slice header 附加信息*/
    pSlcInfo->intra_slice = 0;
    if (BsShow(pBs, 1))
    {
        MP2_u_v(pBs, 1, "intra_slice_flag");
        pSlcInfo->intra_slice =  MP2_u_v(pBs, 1, "intra_slice");
        MP2_u_v(pBs, 7, "reserved_bits");

        while (BsShow(pBs, 1))
        {
            MP2_u_v(pBs, 1, "extra_bit_slice");
            MP2_u_v(pBs, 8, "extra_infrmation_slice");
        }
    }

    MP2_u_v(pBs, 1, "extra_bit_slice");

    return 0;
}

UINT32 MP2_u_v(BS *pBs, UINT32 LenInBits, SINT8 *SeTraceString)
{
    UINT32 Info;

    Info = BsShow(pBs, LenInBits);
    BsSkip(pBs, LenInBits);

    dprint(PRN_CTRL,"%-40s%20d\n", SeTraceString, Info);

    return Info;
}

SINT32 MP2_InitMb(MP2_SLCINFO_S *pSlcInfo)
{
    SINT32 ret = MPEG2_TRUE;
    UINT32 macroblock_escape = 0;
    UINT32 macroblock_address_increment = 0;
    BS *pBs = pSlcInfo->pBs;
    UINT32 code;
    UINT32 SlcStartMbNum;
//	UINT32 PicTotalMbNum;

//	PicTotalMbNum = pSlcInfo->pic_width_in_mb * pSlcInfo->pic_height_in_mb;
	
    while ((code = BsShow(pBs, 11)) <24)//by lz
    {
        if (code!=15) /* if not macroblock_stuffing */
        {
            if (code==8) /* if macroblock_escape */
            {
                macroblock_escape += 33;
            }
            else
            {
                dprint(PRN_ERROR,"macroblock_escape ERROR\n");
                return MPEG2_FALSE;
            }
        }
        else
        {
        	//参考代码未对该分支做处理
            //dprint(PRN_ERROR,"macroblock_stuffing ERROR\n");
            //return MPEG2_FALSE;
        }

        MP2_u_v(pBs, 11, "macroblock_escape");                
    }

    macroblock_address_increment = MP2_MbAddrInc(pBs);

    if (pSlcInfo->FirstMbInSliceFlag) //slice的第一个mb
    {
        if (pSlcInfo->previous_macroblock_address != 0)
        {
             SlcStartMbNum = pSlcInfo->previous_macroblock_address + macroblock_escape + macroblock_address_increment;
        }
        else
        {
             SlcStartMbNum = pSlcInfo->previous_macroblock_address + macroblock_escape + macroblock_address_increment -1;
        }

        pSlcInfo->slicen_start_mb_num = SlcStartMbNum;
		//mpeg2发现过大的宏块号(l00225186)

//	   PicTotalMbNum = pSlcInfo->pic_height_in_mb*pSlcInfo->pic_width_in_mb-1;
	   if(pSlcInfo->slicen_start_mb_num > (pSlcInfo->pic_total_mb_num - 1))
		{
	        dprint(PRN_ERROR,"SlcStartMbNum = %d > PicEndMum = %d\n",SlcStartMbNum,(pSlcInfo->pic_total_mb_num -1));
			return 	MPEG2_FALSE;	
		}
    }
    else // slice的其他宏快, 可能有skip块的情况
    {
        dprint(PRN_ERROR,"FirstMbInSliceFlag = %d\n",pSlcInfo->FirstMbInSliceFlag);
        ret = MPEG2_FALSE;
    }
    return ret;

#if 0
    /*计算宏块坐标*/
    pMb->Mbx = pMb->Mbn%pSlcInfo->pic_width_in_mb;
    pMb->Mby = pMb->Mbn/pSlcInfo->pic_width_in_mb;

    /*复位宏块相关信息*/
    pMb->mb_type = 0;
    pMb->macroblock_intra = 0;
    pMb->macroblock_motion_backward = 0;
    pMb->macroblock_motion_forward = 0;
    pMb->IsSkip = 0;
    pMb->nC = 0;

    for (i = 0; i < 2; i++)
    {
        //pMb->motion_code[0][i] = 0;
        //pMb->motion_residual[0][i] = 0;
        //pMb->motion_code[1][i] = 0;
        pMb->motion_residual[0][0][i] = 0;
        pMb->motion_residual[0][1][i] = 0;
        pMb->motion_residual[1][0][i] = 0;
        pMb->motion_residual[1][1][i] = 0;
        pMb->motion_vertical_field_select[0][i] = 0;
        pMb->motion_vertical_field_select[1][i] = 0;
    }

 /* Level 和 Flag 清0 */
    for (i=0; i<6; i++)  
    {
        pMb->nCBlock[i] = 0;
        for(j = 0; j < 64; j++)
        {
            pMb->Flag[i][j] = 0;
            pMb->Level[i][j] = 0;
        }
    }
#endif
}


VOID MP2_ExitMb(MP2_SLCINFO_S *pSlcInfo)
{
    pSlcInfo->FirstMbInSliceFlag = 0;
}

SINT32  MP2_WriteSliceInfo(MP2_CTX_S *pCtx)
{
    MP2_DEC_PARAM_S *pMp2Decparam = NULL;
    MP2_SLCSTR_S *pMp2SlcStr = NULL;
    MP2_SLCINFO_S *pSlcInfo = NULL;
    MP2CODECINF *pCodecInfo = NULL;
    UADDR stream_base_addr = 0;
//    UINT32 temp_base_addr = 0;
    BS *pBs = NULL;
    UINT32 bs_offset = 0;
    
    pMp2Decparam = &(pCtx->Mp2DecParam);
    
    pMp2SlcStr = &(pMp2Decparam->SlcStr[pMp2Decparam->SlcNum]);
    pSlcInfo = &(pCtx->SliceInfo);
    pCodecInfo = &(pCtx->CodecInfo);
    pBs = &(pCtx->Bs);

    pMp2SlcStr->intra_slice = pSlcInfo->intra_slice;
    pMp2SlcStr->quantiser_scale_code = pSlcInfo->quantiser_scale_code;
    pMp2SlcStr->slice_start_mbn = pSlcInfo->slicen_start_mb_num;
#if 0
    /* 对齐到byte */
    temp_base_addr = (pCodecInfo->stMp2Packet.BsPhyAddr[0]&0xfffffffc) + ((((UINT32)pBs->TotalPos/128)*128)/8);
    bs_offset = ((UINT32)pBs->TotalPos)%128 + ((pCodecInfo->stMp2Packet.BsPhyAddr[0]&0x3)<<3);
    /* 对齐到word */
    stream_base_addr = temp_base_addr&0xfffffff0;
    bs_offset = bs_offset + (8*(temp_base_addr&0x0F));

    if(bs_offset >= 256)
    {
        pMp2SlcStr->BsPhyAddr[0] = stream_base_addr + 32;
        pMp2SlcStr->BsBitOffset[0] = bs_offset - 256;
    }
    else if (bs_offset >= 128)
    {
        pMp2SlcStr->BsPhyAddr[0] = stream_base_addr + 16;
        pMp2SlcStr->BsBitOffset[0] = bs_offset - 128;
    }
    else
    {
        pMp2SlcStr->BsPhyAddr[0] = stream_base_addr;
        pMp2SlcStr->BsBitOffset[0] = bs_offset;
    }
#endif

    /* slice 过多，该帧不解 */
    if(pMp2Decparam->SlcNum >= MP2_MAX_SLC_PARAM_NUM)
    {
        dprint(PRN_ERROR,"Slice num = %d >= %d\n",pMp2Decparam->SlcNum, MP2_MAX_SLC_PARAM_NUM);
        MP2_ClearCurPic(pCtx);
        pCodecInfo->StreamIntegrality &= ~(MPEG2_FOUND_PICHDR|MPEG2_FOUND_PICEXT|MPEG2_FOUND_SLICE);
        pCodecInfo->HDRState = STATE_GET_PICHDR;
        return MPEG2_FALSE;
    }

    stream_base_addr = pCodecInfo->stMp2Packet.BsPhyAddr[0]  +  ((UINT32)pBs->TotalPos)/8;
    bs_offset = ((UINT32)pBs->TotalPos)%8;

    pMp2SlcStr->BsPhyAddr[0] = stream_base_addr;
    pMp2SlcStr->BsBitOffset[0] = bs_offset;
    pMp2SlcStr->BsID[0] = pCodecInfo->stMp2Packet.StreamID[0];
    pMp2SlcStr->BsLenInBit[0] = (UINT32)BsResidBits(pBs);

    if ((1 == pCodecInfo->stMp2Packet.IsLastSeg[0]) && (0 == pCodecInfo->stMp2Packet.IsLastSeg[1]))
    {
        pMp2SlcStr->BsPhyAddr[1] = 0;
        pMp2SlcStr->BsBitOffset[1] = 0;
        pMp2SlcStr->BsID[1] = 0;
        pMp2SlcStr->BsLenInBit[1] = 0;
    }
    else if((0 == pCodecInfo->stMp2Packet.IsLastSeg[0]) && (1 == pCodecInfo->stMp2Packet.IsLastSeg[1]))
    {
        pMp2SlcStr->BsPhyAddr[1]   = pCodecInfo->stMp2Packet.BsPhyAddr[1];
        pMp2SlcStr->BsBitOffset[1] = 0;
        pMp2SlcStr->BsID[1]        = pCodecInfo->stMp2Packet.StreamID[1];
        pMp2SlcStr->BsLenInBit[1]  = pCodecInfo->stMp2Packet.BsLength[1]*8;
    }
    else
    {
        dprint(PRN_ERROR, "seg info is wrong! IsLastSeg[0] = %d, IsLastSeg[1] = %d\n",
            pCodecInfo->stMp2Packet.IsLastSeg[0], pCodecInfo->stMp2Packet.IsLastSeg[1]);
        return MPEG2_FALSE;
    }
    pMp2Decparam->SlcNum++;

    return MPEG2_TRUE;
   
}

UINT32 MP2_MbAddrInc(BS *pBs)
{
    UINT32 code;
    UINT32 MbAddrInc = 0;
    UINT32 SkipBit;

    /*step1: 前 4bit 查表*/
    code = BsShow(pBs, 4);

    MbAddrInc = tab_for_first_4bit[code][0];
    SkipBit = tab_for_first_4bit[code][1];

    if (MbAddrInc < 7)  // get value from 1~5
    {
        MP2_u_v(pBs, SkipBit, "macroblock_address_increment");

        return MbAddrInc;
    }
    else if (MbAddrInc == 9)  //get value from 6~7
    {
        MbAddrInc -= MP2_u_v(pBs, SkipBit, "macroblock_address_increment");
        return MbAddrInc;
    }

    /*step2: 取后面的7bit查表*/
    code = BsShow(pBs, 11);
    code &= 0x07f;

    code -= 24;

    MbAddrInc = tab_for_last_7bit[code][0];
    SkipBit = tab_for_last_7bit[code][1];

    MP2_u_v(pBs, SkipBit, "macroblock_address_increment");

    return MbAddrInc;
}

SINT32 MP2_GetPacketState(MP2_CTX_S *pCtx)
{
    SINT32 ret = MPEG2_FALSE;
    if(1 == pCtx->IsWaitToDecFlag)
    {
        ret = MPEG2_NOTDEC;
    }

    return ret;
}


#endif //MPEG2_ENABLE

