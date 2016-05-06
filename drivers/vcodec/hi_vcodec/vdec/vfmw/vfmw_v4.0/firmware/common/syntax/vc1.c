/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r37p3ELbs/bdDqVORskOWWzbyjFMuPxNo4xK/b5FsMpre+pJk9U9kShcBqcc/r0/nyukf
RRZPnuMcSYEySyxA76L+rghiGcq86Mf2c76RP6CZlS/Co8bn5kb9nllXq0Zk6w==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : vc1_vfmw.c
  版 本 号   : 初稿
  作    者   : y62639
  生成日期   : 2009年9月21日
  最近修改   :
  功能描述   : vc1 firmware
  函数列表   :
              VC1DEC_Decode
              VC1DEC_Destroy
              VC1DEC_GetRemainImg
              VC1DEC_Init
              VC1DEC_RecycleImage
  修改历史   :
  1.日    期   : 2009年9月21日
    作    者   : y62639
    修改内容   : 创建文件

******************************************************************************/

#undef __VC1_VFMW_C__
#define __VC1_VFMW_C__

#include    "vfmw.h"
#include	"syn_cmn.h"
#include	"vdm_hal.h"
#include    "vc1.h"
#include    "vdm_drv.h"
#include    "sysconfig.h"
#include    "fsp.h"
#include    "syntax.h"
#include    "vfmw_ctrl.h"
#include    "bitplane.h"


#define VC1_VFMW_ENABLE

/*    VC1模块编译开关，如果没有打开则不编译    */
#ifdef VC1_VFMW_ENABLE

	#ifndef ENV_EDA
  		#if defined (ENV_ARMLINUX)

  		#endif
 	#endif

/*----------------------------------------------*
* 外部变量说明                                 *
*----------------------------------------------*/
//extern VDMHAL_HWMEM_S    g_HwMem[MAX_VDH_NUM];
/*----------------------------------------------*
* 外部函数原型说明                             *
*----------------------------------------------*/

/*----------------------------------------------*
* 内部函数原型说明                             *
*----------------------------------------------*/
SINT32 VC1_ReceivePacket(VC1_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket);
VOID VC1_ClearCurPacket(SINT32 ChanID, VC1_STREAM_PACKET *pVc1Packet);
VOID VC1_ClearCurPic(VC1_VFMWCODECINF_S *pCodeInfo, SINT32 ChanID);
VOID VC1_SetCodeInfo(VC1_CTX_S *pCtx, VC1_STREAM_PACKET *pVc1Packet);

/*----------------------------------------------*
* 全局变量                                     *
*----------------------------------------------*/

/*----------------------------------------------*
* 模块级变量                                   *
*----------------------------------------------*/

/*----------------------------------------------*
* 常量定义                                     *
*----------------------------------------------*/

/*----------------------------------------------*
* 宏定义                                       *
*----------------------------------------------*/

#define VC1_STOPPIC    0
#define DBG_TRACE      1
#if (1==DBG_TRACE)
#define VC1_DBGPRT     dprint
#else
#define VC1_DBGPRT     emp_print
#endif

#define VC1_CHECKSTAT(stat, flag) ((flag) == ((stat) & (flag)))

static SINT32 a2On4Off[] = { 3, 5, 6, 9, 10, 12, 17, 18, 20, 24, 33, 34, 36, 40, 48 };

// aCount is the number of 1s
static SINT32 aCount[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
                           1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5
                         };

static const SINT32 FldPTypeTab[8][2] =
{
    {VC1_VFMW_IPIC, VC1_VFMW_IPIC}, {VC1_VFMW_IPIC, VC1_VFMW_PPIC }, {VC1_VFMW_PPIC,  VC1_VFMW_IPIC}, {
        VC1_VFMW_PPIC,
        VC1_VFMW_PPIC
    },
    {VC1_VFMW_BPIC, VC1_VFMW_BPIC}, {VC1_VFMW_BPIC, VC1_VFMW_BIPIC}, {VC1_VFMW_BIPIC, VC1_VFMW_BPIC}, {
        VC1_VFMW_BIPIC,
        VC1_VFMW_BIPIC
    },
};

#define VC1_CLEARREFFLAG do{\
    IMAGE *pImg;\
    pImg = FSP_GetFsImagePtr(pVC1_CTX_S->ChanID, pCodecInf->BwdFsID);\
    if (NULL != pImg)\
    { \
        FreeUsdByDec(pVC1_CTX_S->ChanID, pImg->p_usrdat[0]);\
        FreeUsdByDec(pVC1_CTX_S->ChanID, pImg->p_usrdat[1]);\
        FreeUsdByDec(pVC1_CTX_S->ChanID, pImg->p_usrdat[2]);\
        FreeUsdByDec(pVC1_CTX_S->ChanID, pImg->p_usrdat[3]);\
        pImg->p_usrdat[0] = NULL;\
        pImg->p_usrdat[1] = NULL;\
        pImg->p_usrdat[2] = NULL;\
        pImg->p_usrdat[3] = NULL;\
        FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pCodecInf->BwdFsID, 1);\
        FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pCodecInf->FwdFsID, 1);\
        pCodecInf->FwdFsID = 0; \
        pCodecInf->BwdFsID = 0; \
        pCodecInf->FwdFsID=pCodecInf->BwdFsID=FSP_GetNullLogicFs(pVC1_CTX_S->ChanID);\
    }\
}while(0)

#define VC1_CLEARREFNUM do{pCodecInf->RefNum=0;}while(0)

SINT32 emp_print (UINT32 type, const SINT8 *format, ...)
{
    return 0;
}

UINT32 AbandonBitsLenthNoUse(UINT8 *pCode)
{
    UINT32 biteat = 0;
    UINT8 data;
    UINT8* ptr = pCode;

    while (1)
    {
        data = *ptr;
        if (data==0)
        {
            biteat+=8;
        }
        else
        {
            while ((data&0x1)==0)
            {
                biteat+=1;
                data>>=1;
            }
            biteat+=1;
            break;
        }
        ptr--;
    }
    return biteat;
}            


SINT32 VC1DEC_Init(VC1_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    SINT32 ImgQueRstMagic;
    UADDR BpdMemAddr;

    //清除上下文
    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    memset(pCtx, 0, sizeof(VC1_CTX_S));
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue);
    BpdMemAddr = (pstExtraData->s32BpdMemAddr + 255)&(~255);
        
    pCtx->pstExtraData             = pstExtraData;
    pCtx->CodecInfo.LastIs2ndFld   = 1;
    pCtx->CodecInfo.UsedDecMode    = pCtx->pstExtraData->s32DecMode;
    pCtx->CodecInfo.MVTYPEMB_ADDR  = BpdMemAddr;
    pCtx->CodecInfo.SKIPMB_ADDR    = BpdMemAddr + 2048;
    pCtx->CodecInfo.DIRECTMB_ADDR  = BpdMemAddr + 2048 *2;
    pCtx->CodecInfo.ACPRED_ADDR    = BpdMemAddr + 2048 * 3;
    pCtx->CodecInfo.OVERFLAGS_ADDR = BpdMemAddr + 2048 * 4;
    pCtx->CodecInfo.FIELDTX_ADDR   = BpdMemAddr + 2048 * 5;
    pCtx->CodecInfo.FORWARDMB_ADDR = BpdMemAddr + 2048 * 6;
    pCtx->CodecInfo.LastPicRNDCTRL = 1;
    pCtx->CodecInfo.PPicFound      = 0;
    pCtx->CodecInfo.BPicCount      = 0;
    
    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }
    
    return VF_OK;
}

SINT32 Vc1SMPSeqHdr(UINT8 *pBitBuf, SINT32 ByteLen, VC1_PREPARSEINFO_S *pVc1Info)
{
    BS Bs;
    VC1_SMPSEQSYNTAX_S *pSeqSynTax;
    SINT32 data = 0;
    pSeqSynTax = &(pVc1Info->SMPSeqSyntax);

    BsInit(&Bs, pBitBuf, ByteLen * 8);
	
    data = BsGet(&Bs, 8) ;
    data += BsGet(&Bs, 8)<<8 ;
    data += BsGet(&Bs, 8)<<16 ;
    data += BsGet(&Bs, 8)<<24 ;
    pVc1Info->FrmWidth = data;
    data = BsGet(&Bs, 8) ;
    data += BsGet(&Bs, 8)<<8 ;
    data += BsGet(&Bs, 8)<<16 ;
    data += BsGet(&Bs, 8)<<24 ;
    pVc1Info->FrmHeight= data;
    //dprint(PRN_DBG,"pVc1Info->FrmWidth=%d,pVc1Info->FrmHeight=%d\n",pVc1Info->FrmWidth,pVc1Info->FrmHeight);
    /*  检查参数是否超出规格 */
    VDMHAL_ASSERT_RET( pVc1Info->FrmWidth <= MAX_IMG_WIDTH_IN_MB * 16, "picture width out of range");
    VDMHAL_ASSERT_RET( pVc1Info->FrmHeight <= MAX_IMG_HEIGHT_IN_MB * 16, "picture height out of range");
    VDMHAL_ASSERT_RET( pVc1Info->FrmWidth >= 2 * 16, "picture width out of range");
    VDMHAL_ASSERT_RET( pVc1Info->FrmHeight >= 2 * 16, "picture height out of range");

    pSeqSynTax->PROFILE = (UINT8) BsGet(&Bs, 2);
    VDMHAL_ASSERT_RET( pSeqSynTax->PROFILE<=1, "Vc1SMPSeqHdr Err, BS is wrong");

    //reserved should be zero
    VDMHAL_ASSERT_RET( 0 == BsGet(&Bs, 2), "Vc1SMPSeqHdr Err, BS is wrong");

    pSeqSynTax->FRMRTQ = (UINT8) BsGet(&Bs, 3);
    pSeqSynTax->BITRTQ = (UINT8) BsGet(&Bs, 5);
    pSeqSynTax->LOOPFILTER = (UINT8) BsGet(&Bs, 1);

    //reserved should be zero
    VDMHAL_ASSERT_RET( 0 == BsGet(&Bs, 1), "Vc1SMPSeqHdr Err, BS is wrong");

    pSeqSynTax->MULTIRES = (UINT8) BsGet(&Bs, 1);
    pSeqSynTax->B16BITTRANSFORM = (UINT8) BsGet(&Bs, 1); //here 16bits total
    pSeqSynTax->FASTUVMC = (UINT8) BsGet(&Bs, 1);
    pSeqSynTax->EXTENDED_MV = (UINT8) BsGet(&Bs, 1);

    pSeqSynTax->DQUANT = (UINT8) BsGet(&Bs, 2);
    pSeqSynTax->VSTRANSFORM = (UINT8) BsGet(&Bs, 1);

    //reserved should be zero
    VDMHAL_ASSERT_RET( 0 == BsGet(&Bs, 1), "Vc1SMPSeqHdr Err, BS is wrong");

    pSeqSynTax->OVERLAP = (UINT8) BsGet(&Bs, 1);
    pSeqSynTax->SYNCMARKER = (UINT8) BsGet(&Bs, 1);
    pSeqSynTax->RANGERED    = (UINT8) BsGet(&Bs, 1);
    if (VC1_VFMW_SIMPLE == pSeqSynTax->PROFILE)
    {
        pSeqSynTax->RANGERED = 0;
    }
    pSeqSynTax->MAXBFRAMES  = (UINT8) BsGet(&Bs, 3);
    pSeqSynTax->QUANTIZER   = (UINT8) BsGet(&Bs, 2);
    pSeqSynTax->FINTERPFLAG = (UINT8) BsGet(&Bs, 1);
    if ((BsGet(&Bs, 1) == 1) && (Bs.TotalPos <= Bs.BsLen))
    {
        //!!!for RTM-beta version mismatch
    }

    data = BsGet(&Bs, 32);  //Reserved for extension
    if (0 != data)
    {
        dprint(PRN_FATAL, "Vc1SMPSeqHdr Err, BS is wrong\n");
        //return VDMHAL_ERR;
    }

    return VDMHAL_OK;
}

VOID VC1_SetImgFormat(VC1_CTX_S *pCtx)
{
    //UINT32 codtype, csp, sfmt, fldflg;//, vfmt, fldfst, dar;
    VC1_VFMWCODECINF_S *pVc1CodecInfo;
    IMAGE *pImg;
    UINT32 fldflg = 0;
	UINT32 dar;
	UINT32 Stride = 0;
	UINT32 ChromOfst = 0;

    pVc1CodecInfo = &pCtx->CodecInfo;
	dar = 0;
	
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pVc1CodecInfo->CurFsID);
    if (NULL == pImg)
    {
        return;
    }
	
    if (VC1_VFMW_FIELDINTER == pVc1CodecInfo->Last_Struct_IPB)
    {
         fldflg = (pImg->format>>10)&0x3;
         fldflg = fldflg|(pCtx->Vc1DecParam.curparity + 1);
		 if (fldflg > 3)
		 {
		     fldflg = 0;
		 }
		 pImg->format = fldflg<<10;
		 pImg->format |= 1<<8;
		 pImg->format |= 1<<12;
	}
    else
    {
         pImg->format = 0x1c00;
    } 
    /*帧存是按照偶数宏块个数分配的，现在要将实际的给IMG结构体*/
	pImg->image_height = pVc1CodecInfo->DispPicHeight;
	pImg->image_width= pVc1CodecInfo->DispPicWidth;

	SetAspectRatio(pImg,(VDEC_DAR_E)dar);
	
	Stride = pImg->image_stride;//(pImg->image_width + 63) & (~63);
	ChromOfst = pCtx->Vc1DecParam.uvoffset_1d;//(Stride / 16) * ((pImg->image_height + 31) / 32) * 32 + ((pImg->image_height + 31) / 32) * 32 * 16;//level;
	pImg->chrom_phy_addr = pImg->luma_phy_addr + ChromOfst;
	pImg->top_luma_phy_addr  = pImg->luma_phy_addr;
	pImg->top_chrom_phy_addr = pImg->top_luma_phy_addr + ChromOfst;
	pImg->btm_luma_phy_addr  = pImg->top_luma_phy_addr + Stride;
	pImg->btm_chrom_phy_addr = pImg->top_chrom_phy_addr + Stride;
	pImg->luma_2d_phy_addr   = pImg->luma_phy_addr;
	pImg->chrom_2d_phy_addr  = pImg->top_chrom_phy_addr;

	pImg->disp_height = pVc1CodecInfo->DispPicHeight;
	pImg->disp_width= pVc1CodecInfo->DispPicWidth;
	
	return;
}

SINT32 VC1DEC_Destroy(VC1_CTX_S *pCtx)
{
    return VC1_TRUE;
}

SINT32 VC1DEC_GetRemainImg(VC1_CTX_S *pCtx)
{
    VC1_VFMWCODECINF_S *pVc1CodecInfo;
    IMAGE *pImg = NULL;
    SINT32 display_flag;
    SINT32 ret = LAST_OUTPUT_FAIL;

    pVc1CodecInfo = &pCtx->CodecInfo;
    if (NULL == pVc1CodecInfo->pRef[0])
    {
        return ret;
    }
	
    if (OUTPUT_IN_DEC == pCtx->pstExtraData->s32DecOrderOutput)
    {
        ret = LAST_ALREADY_OUT;
    }
    else
    {
        pImg = FSP_GetFsImagePtr(pCtx->ChanID, pVc1CodecInfo->BwdFsID);
        //pImg->disp_height = pVc1CodecInfo->MbHeight *16;
        //pImg->image_height = pVc1CodecInfo->MbHeight *16;
        if (NULL != pImg)
        {
            display_flag = FSP_GetDisplay(pCtx->ChanID, pVc1CodecInfo->BwdFsID);
            if (FS_DISP_STATE_DEC_COMPLETE == display_flag)
            {
                VC1_SetImgFormat(pCtx);
                pImg->last_frame = 1;      // last frame
                //MP2_SetImgFormat(pCtx);
                //MP2_ATTACHUDINF(pImg->p_usrdat[0], pVc1CodecInfo->p_SeqUD);
                //pVc1CodecInfo->p_SeqUD = NULL;
                //MP2_ATTACHUDINF(pImg->p_usrdat[1], pVc1CodecInfo->p_PicUD);
                //pVc1CodecInfo->p_PicUD = NULL;
                pImg->p_usrdat[0] = NULL;
                pImg->p_usrdat[1] = NULL;

                FSP_SetDisplay(pCtx->ChanID, pImg->image_id, 1);
                if (pVc1CodecInfo->pRef[0]->is_to_ref == 1)
                {
                    pVc1CodecInfo->pRef[0]->is_to_display = 1;
                    pVc1CodecInfo->pRef[0]->is_to_ref = 0;
                    pVc1CodecInfo->RefId = 3;
                }

                if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_VC1, pCtx, &pCtx->ImageQue, pImg) )
                {
                    VC1DEC_RecycleImage(pCtx, pImg->image_id);
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
            else  // 之前已经插到队列中
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

SINT32 VC1DEC_RecycleImage(VC1_CTX_S *pCtx, UINT32 img_id)
{
    VC1_VFMWCODECINF_S *pVc1CodecInfo;
    IMAGE *pImg;
    pVc1CodecInfo = &pCtx->CodecInfo;

    FSP_SetDisplay(pCtx->ChanID, img_id, 0);

#if 0
    if (pVc1CodecInfo->RefId == 3)
    {
        pVc1CodecInfo->pRef[0]->is_to_display = 0;
	    pVc1CodecInfo->RefId =0;
	 //pVc1CodecInfo->FrameObj[pVc1CodecInfo->pRef[0]->img.image_id].is_to_display = 0;
    }
    if (pVc1CodecInfo->RefId == 1)
    {
    
        pVc1CodecInfo->pRef[1]->is_to_display = 0;
	    pVc1CodecInfo->RefId =0;
	 //pVc1CodecInfo->FrameObj[pVc1CodecInfo->pRef[1]->img.image_id].is_to_display = 0;
    }
    if (pVc1CodecInfo->RefId == 2)
    {
        
        pVc1CodecInfo->pCurFrm->is_to_display = 0;
	    pVc1CodecInfo->RefId =0;
	 //pVc1CodecInfo->FrameObj[pVc1CodecInfo->pCurFrm->img.image_id].is_to_display = 0;
    }

#endif  
	pImg = FSP_GetFsImagePtr(pCtx->ChanID, img_id);
	if (NULL != pImg)
	{
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        pImg->p_usrdat[0] = NULL;
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        pImg->p_usrdat[1] = NULL;            
	}
    return VC1_TRUE;
}


UINT32 VC1DEC_VDMPostProc(VC1_CTX_S *pCtx, SINT32 ErrRatio)
{ 
    VC1_VFMWCODECINF_S *pVc1CodecInfo;
    IMAGE *pCurImg, *pBwdImg, *pFwdImg, *pToQueImg;
    UINT8 pref=0;

    pVc1CodecInfo = &pCtx->CodecInfo;

    //dprint(PRN_DBG, "ErrRatio = %d\n", ErrRatio);
    /*加入判断是否为AP*/
//  ReleasePacket(VFMW_VC1, pCtx);
    VC1_ClearCurPic(pVc1CodecInfo, pCtx->ChanID);
    
    pCurImg = FSP_GetFsImagePtr(pCtx->ChanID, pVc1CodecInfo->CurFsID);
    pBwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pVc1CodecInfo->BwdFsID);
    pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pVc1CodecInfo->FwdFsID);

    if (pCurImg == NULL)//(pFwdImg == NULL))  前向参考帧此函数不用，因此无需判断
    {
        dprint(PRN_FATAL,"pImg is null, pCurImg %p pBwdImg %p pFwdImg %p\n", pCurImg, pBwdImg, pFwdImg);
		return VC1_FALSE;
	}

    pCurImg->error_level = ErrRatio;	
    pCurImg->error_level = CLIP1(100, (SINT32)(pCurImg->error_level));
    VC1_SetImgFormat(pCtx);
    if (!((VC1_VFMW_FIELDINTER == pVc1CodecInfo->Last_Struct_IPB) && (1 != pVc1CodecInfo->LastIs2ndFld)))
    {
        //MP2_ATTACHUDINF(pCurImg->p_usrdat[0], pVc1CodecInfo->p_SeqUD);
        //MP2_ATTACHUDINF(pCurImg->p_usrdat[1], pVc1CodecInfo->p_PicUD);
        //pMp2CodecInfo->p_SeqUD = NULL;
        //pMp2CodecInfo->p_PicUD = NULL;
        pCurImg->p_usrdat[0] = NULL;
	    pCurImg->p_usrdat[1] = NULL;
        //dprint(PRN_DBG,"insert to queue in postprocess!\n");
        if (OUTPUT_IN_DEC != pCtx->pstExtraData->s32DecOrderOutput) /* if(显示序输出) */
        {
        #if 0
            if ((((VC1_VFMW_IPIC == pVc1CodecInfo->PicCodingType)||(VC1_VFMW_PPIC == pVc1CodecInfo->PicCodingType))&&(1 == pVc1CodecInfo->skpic_flag))||((VC1_VFMW_SKPIC == pVc1CodecInfo->PicCodingType)&&(1 < pVc1CodecInfo->skpic_flag)))
            {
                //pVc1CodecInfo->ToQueFsID = -1;	
                pVc1CodecInfo->pRef[1]->is_to_display = 0;
				FSP_SetDisplay(pCtx->ChanID, pVc1CodecInfo->FwdFsID, 0);
				pVc1CodecInfo->skpic_flag = pVc1CodecInfo->skpic_flag - 1;
				return VC1_FALSE;
			}
			else
		#endif
			{
                if ((VC1_VFMW_BPIC != pVc1CodecInfo->PicCodingType)&&(VC1_VFMW_BIPIC != pVc1CodecInfo->PicCodingType))
                {
                    pVc1CodecInfo->ToQueFsID = (pVc1CodecInfo->RefNum > 1)? pVc1CodecInfo->FwdFsID: -1;
    		        if (pVc1CodecInfo->RefNum > 1)
    		        {
    		            pref = 1;
    		        }
                }
                else 
                {
                    pVc1CodecInfo->ToQueFsID = pVc1CodecInfo->CurFsID;

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
        }
        else
        {
            pVc1CodecInfo->ToQueFsID = pVc1CodecInfo->CurFsID;
        }
        
        pVc1CodecInfo->PicCnt++; 
           
        if ( -1 != pVc1CodecInfo->ToQueFsID )
        {
            pToQueImg = FSP_GetFsImagePtr(pCtx->ChanID, pVc1CodecInfo->ToQueFsID);
            if (NULL == pToQueImg)
            {
                dprint(PRN_DBG, "line: %d, pToQueImg is Null!\n",__LINE__);
                return VC1_FALSE;
            }
            
            if (pToQueImg->error_level == 0 || pToQueImg->error_level <= pCtx->pstExtraData->s32OutErrThr)
            {
	            dprint(PRN_QUEUE, "insert buf %d ref %d\n", pVc1CodecInfo->ToQueFsID, FSP_GetRef(pCtx->ChanID, pVc1CodecInfo->ToQueFsID));
			
		        FSP_SetDisplay(pCtx->ChanID, pVc1CodecInfo->ToQueFsID, 1);
		        if (pref == 1)
		        {
		            pVc1CodecInfo->pRef[1]->is_to_display = 1;
			        pVc1CodecInfo->RefId = 1;
		        }
		        else
		        {
			        pVc1CodecInfo->pCurFrm->is_to_display = 1;
			        pVc1CodecInfo->RefId = 2;
		        }
	            if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_VC1, pCtx, &pCtx->ImageQue, pToQueImg))
	            {
	                FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
	                pToQueImg->p_usrdat[0] = NULL;
	                FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
	                pToQueImg->p_usrdat[1] = NULL;
			        FSP_SetDisplay(pCtx->ChanID, pVc1CodecInfo->ToQueFsID, 0);
			        if (pref == 1)
			        {
                        pVc1CodecInfo->pRef[1]->is_to_display = 0;
			        }
			        else
			        {
                        pVc1CodecInfo->pCurFrm->is_to_display = 0;
			        }
	                return VC1_FALSE;
	            }
		        else
		        {
                    //dprint(PRN_DBG,"postproc :409::::pVc1CodecInfo->RefId =%d\n",pVc1CodecInfo->RefId);
                    if (pVc1CodecInfo->RefId == 3)
                    {
                        pVc1CodecInfo->pRef[0]->is_to_display = 0;
			            pVc1CodecInfo->RefId =0;
                    }
                    if (pVc1CodecInfo->RefId == 1)
                    {
                        pVc1CodecInfo->pRef[1]->is_to_display = 0;
			            pVc1CodecInfo->RefId =0;
                    }
                    if (pVc1CodecInfo->RefId == 2)
                    {
                        pVc1CodecInfo->pCurFrm->is_to_display = 0;
			            pVc1CodecInfo->RefId =0;
                    }
		        }
            }
	        else
	        {
	            dprint(PRN_ERROR,"err(%d) > out_thr(%d)\n", pToQueImg->error_level, pCtx->pstExtraData->s32OutErrThr);
	            FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
	            pToQueImg->p_usrdat[0] = NULL;
	            FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
	            pToQueImg->p_usrdat[1] = NULL;
			    FSP_SetDisplay(pCtx->ChanID, pVc1CodecInfo->ToQueFsID, 0);
			    if (pref == 1)
			    {
                    pVc1CodecInfo->pRef[1]->is_to_display = 0;
			    }
			    else
			    {
                    pVc1CodecInfo->pCurFrm->is_to_display = 0;
			    }
	        }
        }		
    }	
	
    return VC1_TRUE;        
}
    	

/*********************************************************************************
*函数原型
*SINT32 VC1_ArrangeVahbMem(VC1_CTX_S *pVc1Ctx, UINT32 ImgWidth, UINT32 ImgHeight, UINT32 ImgNum, UINT32 PmvBlkNum)
*功能描述
*VC1协议下VAHB地址规划，同时计算VAHB存储占用量。
*
*  参数说明
*  ImgWidth： 图像宽度，以象素为单位
*  ImgHeight：图像高度， 以象素为单位
*  ImgNum：   需要在VAHB空间中开辟的图像存储块个数，
*  PmvBlkNum：需要在VAHB空间中开辟的MV信息存储块个数
*  返回值
*  如果规划成功返回1，否则返回错误码
*  数据依赖
*  g_VfmwCfgInfo：VFMW的配置信息，定义于public.c
*  g_Memory：     VFMW的存储分配信息，定义于public.c
*  g_VfmwState：  VFMW的状态信息，定义于public.c
*  g_H264MemInfo：H.264模块地址规划信息，定义于h264.c
*  算法描述
*  从g_VfmwCfgInfo中获取每个图像需要支持多少个slice的信息；
*  从g_Memory中获取VAHB起始地址，并且将H264消耗的VAHB空间填入g_Memory.VAHB_access_size
*  刷新g_VfmwState中相关的状态信息；
*  H.264模块的地址明细存入g_H264MemInfo，供H.264其它函数使用
*********************************************************************************/
SINT32 VC1_ArrangeVahbMem(VC1_CTX_S *pVc1Ctx, UINT32 ImgWidth, UINT32 ImgHeight, UINT32 PmvBlkNum)
{
	FSP_INST_CFG_S  FspInstCfg;
	VC1_VFMWFRAMEOBJ_S *pfrmbuf = &(pVc1Ctx->CodecInfo.FrameObj[0]);
	SINT8 i;
    SINT32 DecFsNum, DispFsNum;

    if( ImgWidth < 32 || ImgWidth > MAX_HOR_SIZE || ImgHeight < 32 || ImgHeight > MAX_VER_SIZE)
    {
        dprint(PRN_FATAL, "image size abnormal(%dx%d)\n", ImgWidth, ImgHeight );
        return VC1_VFMW_FALSE;
    }
	
    for (i = 0; i < 5; i++)
    {
        pfrmbuf->img.image_id = i;
        pfrmbuf->is_to_display = 0;
        pfrmbuf->is_to_ref    = 0;
        pfrmbuf++;
    }

    if ((pVc1Ctx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pVc1Ctx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
    {
        if (ImgWidth > pVc1Ctx->pstExtraData->stChanOption.s32MaxWidth || ImgHeight > pVc1Ctx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "vc1 actual frame size(%dx%d) exeed max config(%dx%d)\n", ImgWidth, ImgHeight,
				pVc1Ctx->pstExtraData->stChanOption.s32MaxWidth, pVc1Ctx->pstExtraData->stChanOption.s32MaxHeight);
			
			return VC1_VFMW_FALSE;
		}
		
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        ImgWidth  = pVc1Ctx->pstExtraData->stChanOption.s32MaxWidth;
        ImgHeight = pVc1Ctx->pstExtraData->stChanOption.s32MaxHeight;
		
        if (VC1_CHECKSTAT(pVc1Ctx->CodecInfo.CodecStatus, VC1_MALCOK))
        {
            return VC1_VFMW_TRUE;
		}
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/		
		DecFsNum = pVc1Ctx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pVc1Ctx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvBlkNum = 1;
        }
        else
        {
            PmvBlkNum = pVc1Ctx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvBlkNum = MIN(PmvBlkNum,17);
        }		
		DispFsNum = pVc1Ctx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}
	else if (pVc1Ctx->pstExtraData->eCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION)
	{
		DecFsNum = 3;
		PmvBlkNum = 2;
		DispFsNum = 5;		
	}
	else
	{
        if (ImgWidth > pVc1Ctx->pstExtraData->stChanOption.s32MaxWidth || ImgHeight > pVc1Ctx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "vc1 actual frame size(%dx%d) exeed max config(%dx%d)\n", ImgWidth, ImgHeight,
				pVc1Ctx->pstExtraData->stChanOption.s32MaxWidth, pVc1Ctx->pstExtraData->stChanOption.s32MaxHeight);
			
			return VC1_VFMW_FALSE;
		}
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/			
		DecFsNum = pVc1Ctx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pVc1Ctx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvBlkNum = 1;
        }
        else
        {
            PmvBlkNum = pVc1Ctx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvBlkNum = MIN(PmvBlkNum,17);
        }		
		DispFsNum = pVc1Ctx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}

	memset(&FspInstCfg, 0, sizeof(FSP_INST_CFG_S));
	FspInstCfg.s32DecFsWidth        = ImgWidth; 
	FspInstCfg.s32DecFsHeight       = ImgHeight;        
	FspInstCfg.s32DispFsWidth       = ImgWidth;
	FspInstCfg.s32DispFsHeight      = ImgHeight;
	FspInstCfg.s32ExpectedDecFsNum  = (pVc1Ctx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 0: DecFsNum;
	FspInstCfg.s32ExpectedDispFsNum = DispFsNum;
	FspInstCfg.s32ExpectedPmvNum    = (pVc1Ctx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 1: PmvBlkNum;
	
	/* 配置FSP实例，并分割帧存 */
 	if (FSP_OK == FSP_ConfigInstance(pVc1Ctx->ChanID, &FspInstCfg))
 	{
 	    SINT32 Ret, UsedMemSize;
        Ret = FSP_PartitionFsMemory(pVc1Ctx->ChanID, pVc1Ctx->pstExtraData->s32SyntaxMemAddr, 
			        pVc1Ctx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
		if (Ret != FSP_OK)
		{
            // 分割帧存失败，返回
            return VC1_VFMW_FALSE;
		}
	}
	else
	{
	    dprint(PRN_FATAL, "ERROR: FSP_ConfigInstance fail!\n");
	    return VC1_VFMW_FALSE;
	}
	
    return VC1_VFMW_TRUE;
}


SINT32 VC1DEC_Decode(VC1_CTX_S *pVC1_CTX_S, DEC_STREAM_PACKET_S *p_Packet)
{
    SINT32 Ret = VC1_VFMW_TRUE;

    if (NULL == pVC1_CTX_S || NULL == p_Packet)
    {
        dprint(PRN_FATAL, "%s ERROR: pVC1_CTX_S(%p)/p_Packet(%p) = NULL!\n", pVC1_CTX_S, p_Packet);
        return VC1_VFMW_FALSE;
    }
    
    memcpy(&(pVC1_CTX_S->LastPacket), p_Packet, sizeof(DEC_STREAM_PACKET_S));
    if(VC1_VFMW_FALSE == VC1_ReceivePacket(pVC1_CTX_S, &(pVC1_CTX_S->LastPacket)))
    {        
        dprint(PRN_FATAL, "ERROR: frm %d, Invalid packet pointer!\n", pVC1_CTX_S->CodecInfo.PicCnt);
        return VC1_VFMW_FALSE;
	}

    if((1 == pVC1_CTX_S->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
       (1 == pVC1_CTX_S->pstExtraData->s32WaitFsFlag))
    {
        pVC1_CTX_S->CodecInfo.CodecStatus = pVC1_CTX_S->CodecInfo.u8LastCodecStatus;
        pVC1_CTX_S->CodecInfo.CodecStatus &= (~(VC1_MALCOK));
    }
    else
    {
        pVC1_CTX_S->CodecInfo.u8LastCodecStatus = pVC1_CTX_S->CodecInfo.CodecStatus;
    }

    do
    {
        Ret = VC1_Vfmw_ParseHeader(&(pVC1_CTX_S->CodecInfo), &(pVC1_CTX_S->CodecInfo.SynNew), pVC1_CTX_S->ChanID);
		if (VC1_VFMW_FALSE == Ret)
        {
            VC1_ClearCurPacket(pVC1_CTX_S->ChanID,&(pVC1_CTX_S->CodecInfo.stCurPacket));
			//dprint(PRN_FATAL, "Parsing header error, release the current packet!\n");
	        REPORT_DECSYNTAX_ERR(pVC1_CTX_S->ChanID);
            break;
        }
        if (VC1_VFMW_FALSE == VC1_Vfmw_DecodeArbiter(pVC1_CTX_S))
        {
            Ret = VC1_VFMW_FALSE;
            break;
        }
		if (VC1_VFMW_FALSE == VC1_Vfmw_PrepareDecode(pVC1_CTX_S))
        {
            if((1 != pVC1_CTX_S->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) || \
              ((1 == pVC1_CTX_S->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
               (0 == pVC1_CTX_S->pstExtraData->s32WaitFsFlag)))
            {
                VC1_ClearCurPic(&(pVC1_CTX_S->CodecInfo), pVC1_CTX_S->ChanID);
            }
            Ret = VC1_VFMW_FALSE;
	        REPORT_DECSYNTAX_ERR(pVC1_CTX_S->ChanID);
            break;
        }
        if (VC1_VFMW_FALSE == VC1_Vfmw_StartDecode(pVC1_CTX_S))
        {
            FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pVC1_CTX_S->CodecInfo.CurFsID, 1);
            pVC1_CTX_S->CodecInfo.pCurFrm->is_to_ref = 0;
            pVC1_CTX_S->CodecInfo.pCurFrm->is_to_display = 0;
			Ret = VC1_VFMW_FALSE;
	        REPORT_DECSYNTAX_ERR(pVC1_CTX_S->ChanID);
            break;
        }
    }
    while (0);

    return Ret;
}

VOID VC1_WritePicMsg(VC1_CTX_S * pCtx,VC1_DEC_PARAM_S *pVc1DecParam)
{
    UINT32  FwdRefIdx, BwdRefIdx, RANGEREDFRM ,RANGEREDFRM0 ,RANGEREDFRM1;
    FSP_LOGIC_FS_S *pCur;
    VC1_VFMWCODECINF_S *pCodecInf;
    pCodecInf = &pCtx->CodecInfo;
    //dprint(PRN_DBG,"==================pic %d====================\n",pCodecInf->PicCnt);
    pCur = FSP_GetLogicFs(pCtx->ChanID, pCodecInf->CurFsID);
    if (NULL == pCur)
    {
        dprint(PRN_DBG, "line: %d, pImage is NULL!\n", __LINE__);
        return;
    }
    
    if (pCodecInf->PreParseInfo.IsAdvProfile)
    {
        pVc1DecParam->fcm = pCodecInf->AdvPicSyntax.FCM;

        pVc1DecParam->profile = pCodecInf->AdvSeqSyntax.PROFILE;
        pVc1DecParam->ptype = (SINT32)((VC1_VFMW_BIPIC==pCodecInf->AdvPicSyntax.PTYPE) ? (pCodecInf->AdvPicSyntax.PTYPE-1): pCodecInf->AdvPicSyntax.PTYPE);

        if (VC1_VFMW_FIELDINTER==pCodecInf->AdvPicSyntax.FCM)
        {
            pVc1DecParam->mbheight  = ((SINT32)pCodecInf->CurPicMbHeight +1)/2-1;//field: 
	    }
        else
	    {
	        pVc1DecParam->mbheight  = (SINT32)pCodecInf->CurPicMbHeight -1;
	    }
	    pVc1DecParam->mbwidth     = (SINT32)pCodecInf->CurPicMbWidth -1;

        pVc1DecParam->curparity  = pCodecInf->AdvPicSyntax.CurParity;
        pVc1DecParam->loopfilter = pCodecInf->AdvEntSyntax.LOOPFILTER;
        pVc1DecParam->numref = pCodecInf->AdvPicSyntax.NUMREF;
        pVc1DecParam->issecondfld = pCodecInf->Is2ndFld;
	    pVc1DecParam->fwd_fcm = pCodecInf->FrameObj[pCodecInf->RefList0.ImgObj[0]].PicStruct;
	    pVc1DecParam->bwd_fcm = pCodecInf->FrameObj[pCodecInf->RefList1.ImgObj[0]].PicStruct;

        pVc1DecParam->condover    = pCodecInf->AdvPicSyntax.CONDOVER;
        pVc1DecParam->fastuvmc    = pCodecInf->AdvEntSyntax.FASTUVMC;
        pVc1DecParam->overlap     = pCodecInf->AdvEntSyntax.OVERLAP;
        pVc1DecParam->rndctrl     = pCodecInf->AdvPicSyntax.RNDCTRL;

        pVc1DecParam->altpquant = pCodecInf->AdvPicSyntax.VOPDQUANT.ALTPQUANT;
        pVc1DecParam->halfqp      = pCodecInf->AdvPicSyntax.HALFQP;
        pVc1DecParam->pqindex     = pCodecInf->AdvPicSyntax.PQINDEX;
        pVc1DecParam->pquant      = pCodecInf->AdvPicSyntax.PQUANT;

        if (0 == pCodecInf->AdvEntSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = (pCodecInf->AdvPicSyntax.PQINDEX <= 8)  ? 1 : 0;
        }
        else if (1 == pCodecInf->AdvEntSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = (pCodecInf->AdvPicSyntax.PQUANTIZER) ? 1 : 0;
        }
        else if (2 == pCodecInf->AdvEntSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = 0;
        }
        else //(3 == pCodecInf->AdvEntSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = 1;
        }

        pVc1DecParam->dqbilevel = pCodecInf->AdvPicSyntax.VOPDQUANT.DQBILEVEL;
        pVc1DecParam->dqprofile = pCodecInf->AdvPicSyntax.VOPDQUANT.DQPROFILE;
        pVc1DecParam->dquant      = pCodecInf->AdvEntSyntax.DQUANT;
        pVc1DecParam->dquantfrm   = pCodecInf->AdvPicSyntax.VOPDQUANT.DQUANTFRM;
        pVc1DecParam->quantmode   = pCodecInf->AdvPicSyntax.VOPDQUANT.QuantMode;
        pVc1DecParam->usealtqp    = pCodecInf->AdvPicSyntax.VOPDQUANT.UseAltQp;

        pVc1DecParam->mvmode      = pCodecInf->AdvPicSyntax.MVMODE;
        pVc1DecParam->mvmode2     = pCodecInf->AdvPicSyntax.MVMODE2;

        pVc1DecParam->reffiled     = pCodecInf->AdvPicSyntax.REFFIELD;
        pVc1DecParam->dmvrange     = pCodecInf->AdvPicSyntax.DMVRANGE;
        pVc1DecParam->colishalfpel = pCodecInf->pRef[0]->IsHalfPel[pCodecInf->AdvPicSyntax.CurParity];
        pVc1DecParam->curishalfpel = pCodecInf->pCurFrm->IsHalfPel[pCodecInf->AdvPicSyntax.CurParity];
        pVc1DecParam->mvrange     = pCodecInf->AdvPicSyntax.MVRANGE;
        pVc1DecParam->refdist     = pCodecInf->AdvPicSyntax.REFDIST;

        pVc1DecParam->transdctab  = pCodecInf->AdvPicSyntax.TRANSDCTAB;
        pVc1DecParam->vstransform = pCodecInf->AdvEntSyntax.VSTRANSFORM;
        pVc1DecParam->ttmbf       = pCodecInf->AdvPicSyntax.TTMBF;
        pVc1DecParam->transacfrm  = pCodecInf->AdvPicSyntax.TRANSACFRM;
        pVc1DecParam->transacfrm2 = pCodecInf->AdvPicSyntax.TRANSACFRM2;
        pVc1DecParam->ttfrm       = pCodecInf->AdvPicSyntax.TTFRM;

        pVc1DecParam->acpredmodeisskipraw    = ( 0 == pCodecInf->AdvPicSyntax.ACPREDMode) ;
        pVc1DecParam->directmbmodeisskipraw  = ( 0 == pCodecInf->AdvPicSyntax.DIRECTMBMode);
        pVc1DecParam->fieldtxmodeisskipraw   = ( 0 == pCodecInf->AdvPicSyntax.FIELDTXMode);
        pVc1DecParam->forwardmbmodeisskipraw = ( 0 == pCodecInf->AdvPicSyntax.FORWARDMBMode);
        pVc1DecParam->mvtypembmodeisskipraw  = ( 0 == pCodecInf->AdvPicSyntax.MVTYPEMBMode);
        pVc1DecParam->overflagsmodeisskipraw = ( 0 == pCodecInf->AdvPicSyntax.OVERFLAGSMode);
        pVc1DecParam->skipmbmodeisskipraw    = ( 0 == pCodecInf->AdvPicSyntax.SKIPMBMode);

        pVc1DecParam->bfraction = pCodecInf->AdvPicSyntax.BFRACTION;
        pVc1DecParam->cbptab = pCodecInf->AdvPicSyntax.CBPTAB;
        pVc1DecParam->mvtab  = pCodecInf->AdvPicSyntax.MVTAB;

        pVc1DecParam->fourmvbptab  = pCodecInf->AdvPicSyntax.QMVBPTAB;
        pVc1DecParam->fourmvswtich = pCodecInf->AdvPicSyntax.QMVSWITCH;
        pVc1DecParam->mbmodetab   = pCodecInf->AdvPicSyntax.MBMODETAB;
        pVc1DecParam->twomvbptab  = pCodecInf->AdvPicSyntax.BMVBPTAB;


        /* D12 scalefactor */
        pVc1DecParam->ScaleFactor = pCodecInf->AdvPicSyntax.ScaleFactor;

        /* D13 frfd  */
        pVc1DecParam->FRFD = pCodecInf->FRFD;

        /* D14 brfd  */
        pVc1DecParam->BRFD = pCodecInf->BRFD;

	    pVc1DecParam->rangemapyflag   = pCodecInf->AdvEntSyntax.RANGE_MAPY_FLAG;
	    pVc1DecParam->rangemapy       = pCodecInf->AdvEntSyntax.RANGE_MAPY;
	    pVc1DecParam->rangemapuvflag  = pCodecInf->AdvEntSyntax.RANGE_MAPUV_FLAG;
	    pVc1DecParam->rangemapuv      = pCodecInf->AdvEntSyntax.RANGE_MAPUV;
        
        /* D28  */
	    pVc1DecParam->CodecVersion = pCodecInf->CodecVersion;  

    }
    else
    {
        pVc1DecParam->fcm         = VC1_VFMW_PROGRESSIVE;
        pVc1DecParam->profile     = pCodecInf->SMPSeqSyntax.PROFILE;
        pVc1DecParam->ptype       = (SINT32)((VC1_VFMW_BIPIC==pCodecInf->SMPPicSyntax.PTYPE) ? (pCodecInf->SMPPicSyntax.PTYPE-1): pCodecInf->SMPPicSyntax.PTYPE);

	    pVc1DecParam->mbheight    = (SINT32)pCodecInf->CurPicMbHeight -1;
	    pVc1DecParam->mbwidth     = (SINT32)pCodecInf->CurPicMbWidth -1;

        //d2.curparity
        pVc1DecParam->curparity  = 0;
        pVc1DecParam->loopfilter = pCodecInf->SMPSeqSyntax.LOOPFILTER;
        pVc1DecParam->numref = 0;
        pVc1DecParam->issecondfld = pCodecInf->Is2ndFld;
	    pVc1DecParam->fwd_fcm = 0;
	    pVc1DecParam->bwd_fcm = 0;


	    pVc1DecParam->fastuvmc    = pCodecInf->SMPSeqSyntax.FASTUVMC;
        pVc1DecParam->overlap     = pCodecInf->SMPSeqSyntax.OVERLAP;
	    pVc1DecParam->rndctrl     = pCodecInf->SMPPicSyntax.RNDCTRL;

        pVc1DecParam->altpquant   = pCodecInf->SMPPicSyntax.VOPDQUANT.ALTPQUANT;
        pVc1DecParam->halfqp      = pCodecInf->SMPPicSyntax.HALFQP;
        pVc1DecParam->pqindex     = pCodecInf->SMPPicSyntax.PQINDEX;
        pVc1DecParam->pquant      = pCodecInf->SMPPicSyntax.PQUANT; 
        	
        if (0 == pCodecInf->SMPSeqSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = (pCodecInf->SMPPicSyntax.PQINDEX <= 8)  ? 1 : 0;
        }
        else if (1 == pCodecInf->SMPSeqSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = (pCodecInf->SMPPicSyntax.PQUANTIZER) ? 1 : 0;
        }
        else if (2 == pCodecInf->SMPSeqSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = 0;
        }
        else //(3 == pCodecInf->SMPSeqSyntax.QUANTIZER)
        {
            pVc1DecParam->buniform = 1;
        }

        pVc1DecParam->dqbilevel   = pCodecInf->SMPPicSyntax.VOPDQUANT.DQBILEVEL;
        pVc1DecParam->dqprofile   = pCodecInf->SMPPicSyntax.VOPDQUANT.DQPROFILE;
        pVc1DecParam->dquant      = pCodecInf->SMPSeqSyntax.DQUANT;
        pVc1DecParam->dquantfrm   = pCodecInf->SMPPicSyntax.VOPDQUANT.DQUANTFRM;
        pVc1DecParam->quantmode   = pCodecInf->SMPPicSyntax.VOPDQUANT.QuantMode;
        pVc1DecParam->usealtqp    = pCodecInf->SMPPicSyntax.VOPDQUANT.UseAltQp;

        pVc1DecParam->mvmode      = pCodecInf->SMPPicSyntax.MVMODE;
        pVc1DecParam->mvmode2     = pCodecInf->SMPPicSyntax.MVMODE2;

        pVc1DecParam->colishalfpel = pCodecInf->pRef[0]->IsHalfPel[0];
        pVc1DecParam->curishalfpel = pCodecInf->pCurFrm->IsHalfPel[0];
        pVc1DecParam->mvrange     = pCodecInf->SMPPicSyntax.MVRANGE;
        pVc1DecParam->refdist     = pCodecInf->AdvPicSyntax.REFDIST;  

        pVc1DecParam->transdctab  = pCodecInf->SMPPicSyntax.TRANSDCTAB;
        pVc1DecParam->vstransform = pCodecInf->SMPSeqSyntax.VSTRANSFORM;
        pVc1DecParam->ttmbf       = pCodecInf->SMPPicSyntax.TTMBF;
        pVc1DecParam->transacfrm  = pCodecInf->SMPPicSyntax.TRANSACFRM;
        pVc1DecParam->transacfrm2 = pCodecInf->SMPPicSyntax.TRANSACFRM2;
        pVc1DecParam->ttfrm       = pCodecInf->SMPPicSyntax.TTFRM;   

        pVc1DecParam->directmbmodeisskipraw = ( 0 == pCodecInf->SMPPicSyntax.DIRECTMBMode);
        pVc1DecParam->mvtypembmodeisskipraw = ( 0 == pCodecInf->SMPPicSyntax.MVTYPEMBMode);
        pVc1DecParam->skipmbmodeisskipraw   = ( 0 == pCodecInf->SMPPicSyntax.SKIPMBMode); 

        pVc1DecParam->bfraction = pCodecInf->SMPPicSyntax.BFRACTION;
        pVc1DecParam->cbptab = pCodecInf->SMPPicSyntax.CBPTAB;
        pVc1DecParam->mvtab  = pCodecInf->SMPPicSyntax.MVTAB; 

        /* D12  scalefactor */
        pVc1DecParam->ScaleFactor = pCodecInf->SMPPicSyntax.ScaleFactor;

		if (1 == pCodecInf->SMPSeqSyntax.RANGERED)
		{
			FwdRefIdx = pCodecInf->RefList0.ImgObj[0];
			RANGEREDFRM0 = pCodecInf->FrameObj[FwdRefIdx].RANGEREDFRM;

			BwdRefIdx = pCodecInf->RefList1.ImgObj[0];
			RANGEREDFRM1 = pCodecInf->FrameObj[BwdRefIdx].RANGEREDFRM;

			if ( (VC1_VFMW_BPIC == pCodecInf->SMPPicSyntax.PTYPE) || (VC1_VFMW_BIPIC == pCodecInf->SMPPicSyntax.PTYPE) )
			{
				RANGEREDFRM =RANGEREDFRM1;
			}
			else
			{
				RANGEREDFRM = pCodecInf->SMPPicSyntax.RANGEREDFRM;
			}
		}
        else
        {
            RANGEREDFRM  = 0;
            RANGEREDFRM0 = 0;
            RANGEREDFRM1 = 0;
        }

        pVc1DecParam->RANGEREDFRM  = RANGEREDFRM ;
        pVc1DecParam->RANGEREDFRM0 = RANGEREDFRM0;
        pVc1DecParam->RANGEREDFRM1 = RANGEREDFRM1;
    }

    /* D15  totalslicenum */
	pVc1DecParam->totalslicenum = pCodecInf->SlcNum & 0xFFFF;

    /* D16  curr_rcn_addr */

    /* D17 fwd_ref_addr  */

    /* D18 bwd_ref_addr  */

    /* D27  */
	pVc1DecParam->DispPicWidth = pCodecInf->DispPicWidth;
	pVc1DecParam->DispPicHeight = pCodecInf->DispPicHeight;


    /* D28  */
    pVc1DecParam->CodecVersion = pCodecInf->CodecVersion;
    pVc1DecParam->PostCresent = pCodecInf->PostCresent;
    /* D29-36  BPD  */
    pVc1DecParam->BPD_STRIDE = (pCodecInf->MbWidth + 127)/128*16;
    pVc1DecParam->MVTYPEMB_ADDR = pCodecInf->MVTYPEMB_ADDR;
    pVc1DecParam->SKIPMB_ADDR = pCodecInf->SKIPMB_ADDR;
    pVc1DecParam->DIRECTMB_ADDR = pCodecInf->DIRECTMB_ADDR;
    pVc1DecParam->ACPRED_ADDR = pCodecInf->ACPRED_ADDR;
    pVc1DecParam->OVERFLAGS_ADDR = pCodecInf->OVERFLAGS_ADDR;
    pVc1DecParam->FIELDTX_ADDR = pCodecInf->FIELDTX_ADDR;
    pVc1DecParam->FORWARDMB_ADDR = pCodecInf->FORWARDMB_ADDR;

    /* D29-62  reserve  */
	pVc1DecParam->pIntensityConvertTab =  &(pCodecInf->IntensityConvertTab[0][0][0][0]);
    //memcpy(pVc1DecParam->IntensityConvertTab, pCodecInf->IntensityConvertTab, 3 * 1024);

}

void VC1_WriteSliceMsg(VC1_VFMWCODECINF_S *pCodecInf, VC1_DEC_PARAM_S *pVc1DecParam)
{
    pVc1DecParam->SlcNum = pCodecInf->SlcNum;
    memcpy(&(pVc1DecParam->SlcStr[0]), &(pCodecInf->SlcStr[0]), sizeof(VC1_SLCSTREAM_S)*pCodecInf->SlcNum);
    return;
}

#ifndef VFMW_BPD_H_SUPPORT
VOID VC1_WriteBitplaneMsg(VC1_VFMWCODECINF_S *pCodecInf, VC1_DEC_PARAM_S *pVc1DecParam)
{
    SINT32 _index = 0;
    UINT32 i = 0;
    UINT32  Round = (pVc1DecParam->basic_cfg0 + 4) / 4;// basic_cfg0 is mbtodec,should plus 1 tobe total mb unmber, so( basic_cfg0 + 1 + 3)/4  //(pCodecInf->CurPicMbNum + 3) / 4;
    SINT8 *p0, *p1,*p2,*p3,*p4,*p5,*p6;
    VC1BITPLANE_MB m_bitplane_group[4];
    pVc1DecParam->BitPlaneNum = Round;
    pVc1DecParam->NoBitplaneFlag = 0;
	
    if (VC1_VFMW_SKPIC == pCodecInf->PicCodingType)
    {
	    pVc1DecParam->NoBitplaneFlag = 1;
        return;
	}
	
	#if 1
    p0 = pCodecInf->OVERFLAGS;
    p1 = pCodecInf->ACPRED;
    p2 = pCodecInf->SKIPMB;
    p3 = pCodecInf->FIELDTX;
    p4 = pCodecInf->MVTYPEMB;
    p5 = pCodecInf->DIRECTMB;
    p6 = pCodecInf->FORWARDMB;
    #endif
	
	if (pCodecInf->PreParseInfo.IsAdvProfile)
	{
	    if ((pVc1DecParam->ptype == VC1_VFMW_PPIC)&&(pVc1DecParam->fcm == VC1_VFMW_FIELDINTER))
	    {
	        pVc1DecParam->NoBitplaneFlag = 1;
            return;
		}
		
	    if ((pVc1DecParam->ptype == VC1_VFMW_BPIC)&&(pVc1DecParam->fcm == VC1_VFMW_FIELDINTER))
	    {
	        if (1 == pVc1DecParam->forwardmbmodeisskipraw)
	        {
                pVc1DecParam->NoBitplaneFlag = 1;
				return;
			}
			else
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = (p6[i]&1);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p6 += 4;
                }
    			return;
			}
		}
		
	    if (((pVc1DecParam->ptype == VC1_VFMW_BIPIC - 1)||(pVc1DecParam->ptype == VC1_VFMW_IPIC))&&(pVc1DecParam->fcm != VC1_VFMW_FRAMEINTER))
	    {
	        if ((1==pVc1DecParam->overflagsmodeisskipraw)&&(1==pVc1DecParam->acpredmodeisskipraw))
	        {
                pVc1DecParam->NoBitplaneFlag = 1;
				return;
			}
			else if (1==pVc1DecParam->overflagsmodeisskipraw)
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p1[i]&1)<<5) ;
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p1 += 4;
                }
    			return;
			}
			else if (1==pVc1DecParam->acpredmodeisskipraw)
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p0[i]&1)<<6) ;
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p0 += 4;
                }
    			return;
			}
			else
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p0[i]&1)<<6) | ((p1[i]&1)<<5) ;
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p0 += 4;
            		p1 += 4;
                }
    			return;
			}
		}
	    if (((pVc1DecParam->ptype == VC1_VFMW_BIPIC - 1)||(pVc1DecParam->ptype == VC1_VFMW_IPIC))&&(pVc1DecParam->fcm == VC1_VFMW_FRAMEINTER))
	    {
	        if ((1 == pVc1DecParam->fieldtxmodeisskipraw)&&(1 == pVc1DecParam->acpredmodeisskipraw)&&(1 == pVc1DecParam->overflagsmodeisskipraw))
	        {
                pVc1DecParam->NoBitplaneFlag = 1;
				return;
			}
            else if ((1 == pVc1DecParam->fieldtxmodeisskipraw)&&(1 != pVc1DecParam->acpredmodeisskipraw)&&(1 != pVc1DecParam->overflagsmodeisskipraw))
            {
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p0[i]&1)<<6) | ((p1[i]&1)<<5);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p0 += 4;
            		p1 += 4;
                }
    			return;
			}
            else if ((1 != pVc1DecParam->fieldtxmodeisskipraw)&&(1 == pVc1DecParam->acpredmodeisskipraw)&&(1 != pVc1DecParam->overflagsmodeisskipraw))
            {
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p0[i]&1)<<6) | ((p3[i]&1)<<3);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p0 += 4;
            		p3 += 4;
                }
    			return;
			}
            else if ((1 != pVc1DecParam->fieldtxmodeisskipraw)&&(1 != pVc1DecParam->acpredmodeisskipraw)&&(1 == pVc1DecParam->overflagsmodeisskipraw))
            {
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p1[i]&1)<<5) | ((p3[i]&1)<<3);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p1 += 4;
            		p3 += 4;
                }
    			return;
			}
            else if ((1 == pVc1DecParam->fieldtxmodeisskipraw)&&(1 == pVc1DecParam->acpredmodeisskipraw)&&(1 != pVc1DecParam->overflagsmodeisskipraw))
            {
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p0[i]&1)<<6);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p0 += 4;
                }
			    return;
			}
            else if ((1 == pVc1DecParam->fieldtxmodeisskipraw)&&(1 != pVc1DecParam->acpredmodeisskipraw)&&(1 == pVc1DecParam->overflagsmodeisskipraw))
            {
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 =  ((p1[i]&1)<<5) ;
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p1 += 4;
                }
    			return;
			}
            else if ((1 != pVc1DecParam->fieldtxmodeisskipraw)&&(1 == pVc1DecParam->acpredmodeisskipraw)&&(1 == pVc1DecParam->overflagsmodeisskipraw))
            {
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 =  ((p3[i]&1)<<3);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p3 += 4;
                }
    			return;
			}
			else
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p0[i]&1)<<6) | ((p1[i]&1)<<5) | ((p3[i]&1)<<3);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p0 += 4;
            		p1 += 4;
            		p3 += 4;
                }
    			return;
			}
		}
	    if ((pVc1DecParam->ptype == VC1_VFMW_PPIC)&&(pVc1DecParam->fcm == VC1_VFMW_FRAMEINTER))
	    {
	        if (1 == pVc1DecParam->skipmbmodeisskipraw)
	        {
	            pVc1DecParam->NoBitplaneFlag = 1;
                return;
			}
			else
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p2[i]&1)<<4);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
                }
    			return;
			}
	    }
	    if ((pVc1DecParam->ptype == VC1_VFMW_PPIC)&&(pVc1DecParam->fcm == VC1_VFMW_PROGRESSIVE))
	    {
	        if ((1 == pVc1DecParam->mvtypembmodeisskipraw)&&(1 == pVc1DecParam->skipmbmodeisskipraw))
	        {
	            pVc1DecParam->NoBitplaneFlag = 1;
                return;
			}
			else if (1 == pVc1DecParam->mvtypembmodeisskipraw)
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p2[i]&1)<<4);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
                }
    			return;
			}
			else if (1 == pVc1DecParam->skipmbmodeisskipraw)
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p4[i]&1)<<2);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p4 += 4;
                }
    			return;
			}
			else
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p2[i]&1)<<4) | ((p4[i]&1)<<2);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
            		p4 += 4;
                }
    			return;
			}
		}
	    if ((pVc1DecParam->ptype == VC1_VFMW_BPIC)&&(pVc1DecParam->fcm != VC1_VFMW_FIELDINTER))
	    {
	        if ((1 == pVc1DecParam->directmbmodeisskipraw)&&(1 == pVc1DecParam->skipmbmodeisskipraw))
	        {
                pVc1DecParam->NoBitplaneFlag = 1;
				return;
			}
			else if (1 == pVc1DecParam->directmbmodeisskipraw)
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 =  ((p2[i]&1)<<4) ;
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
                }
    			return;
			}
			else if (1 == pVc1DecParam->skipmbmodeisskipraw)
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 =  ((p5[i]&1)<<1);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p5 += 4;
                }
    			return;
			}
			else
			{
                for (_index = 0; _index < Round; _index++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 =  ((p2[i]&1)<<4) | ((p5[i]&1)<<1);
                    }
            		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
            		p5 += 4;
                }
    			return;
			}
		}
	}
	else
	{
	    if (((pVc1DecParam->ptype == VC1_VFMW_BIPIC - 1)||(pVc1DecParam->ptype == VC1_VFMW_IPIC))&&(pVc1DecParam->fcm != VC1_VFMW_FIELDINTER))
	    {
            pVc1DecParam->NoBitplaneFlag = 1;
			return;
		}
	    if ((pVc1DecParam->ptype == VC1_VFMW_PPIC)&&(pVc1DecParam->fcm != VC1_VFMW_FIELDINTER))
	    {
            if ((1 == pVc1DecParam->skipmbmodeisskipraw)&&(1 == pVc1DecParam->mvtypembmodeisskipraw))
            {
                pVc1DecParam->NoBitplaneFlag = 1;
			    return;
			}
			else if (1 == pVc1DecParam->skipmbmodeisskipraw)
			{
        	    for (_index = 0; _index < Round; _index++)
        	    {
        	        for (i = 0; i < 4; i++)
        	        {
             	        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p4[i]&1)<<2);
        	        }
        			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p4 += 4;
                }
				return;
			}
			else if (1 == pVc1DecParam->mvtypembmodeisskipraw)
			{
        	    for (_index = 0; _index < Round; _index++)
        	    {
        	        for (i = 0; i < 4; i++)
        	        {
             	        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p2[i]&1)<<4) ;
        	        }
        			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
                }
				return;
			}
			else
			{
        	    for (_index = 0; _index < Round; _index++)
        	    {
        	        for (i = 0; i < 4; i++)
        	        {
             	        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p2[i]&1)<<4) | ((p4[i]&1)<<2) ;
        	        }
        			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
            		p4 += 4;
                }
				return;
			}
		}

	    if ((pVc1DecParam->ptype == VC1_VFMW_BPIC)&&(pVc1DecParam->fcm != VC1_VFMW_FIELDINTER))
	    {
            if ((1 == pVc1DecParam->directmbmodeisskipraw)&&(1 == pVc1DecParam->skipmbmodeisskipraw))
            {
                pVc1DecParam->NoBitplaneFlag = 1;
			    return;
			}
			else if (1 == pVc1DecParam->directmbmodeisskipraw)
			{
        	    for (_index = 0; _index < Round; _index++)
        	    {
        	        for (i = 0; i < 4; i++)
        	        {
             	        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p2[i]&1)<<4);
        	        }
        			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
                }
				return;
			}
			else if (1 == pVc1DecParam->skipmbmodeisskipraw)
			{
        	    for (_index = 0; _index < Round; _index++)
        	    {
        	        for (i = 0; i < 4; i++)
        	        {
             	        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p5[i]&1)<<1);
        	        }
        			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p5 += 4;
                }
				return;
			}
			else
			{
        	    for (_index = 0; _index < Round; _index++)
        	    {
        	        for (i = 0; i < 4; i++)
        	        {
             	        m_bitplane_group[i].u8 = 0;
            			m_bitplane_group[i].u8 = ((p2[i]&1)<<4) | ((p5[i]&1)<<1);
        	        }
        			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
            		p2 += 4;
            		p5 += 4;
                }
				return;
			}
	    }
		#if 0
	    for (_index = 0; _index < Round; _index++)
	    {
	        for (i = 0; i < 4; i++)
	        {
     	        m_bitplane_group[i].u8 = 0;
//     	        m_bitplane_group[0].u8 = 0;
                //m_bitplane_group[i].bits.skipmb   = pCodecInf->SKIPMB[_index * 4 + i];
                //m_bitplane_group[i].bits.mbtypemb = pCodecInf->MVTYPEMB[_index * 4 + i];
                //m_bitplane_group[i].bits.directmb = pCodecInf->DIRECTMB[_index * 4 + i];
    			m_bitplane_group[i].u8 = ((p2[i]&1)<<4) | ((p4[i]&1)<<2) | ((p5[i]&1)<<1);
	        }
			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
    		p2 += 4;
    		p4 += 4;
    		p5 += 4;
        }
		#endif
	}

    return;
}
#endif
#if 0
VOID VC1_WriteBitplaneMsg(VC1_VFMWCODECINF_S *pCodecInf, VC1_DEC_PARAM_S *pVc1DecParam)
{
    SINT32 _index = 0;
    UINT32 i = 0;
	UINT32  Round = (pVc1DecParam->basic_cfg0 + 4) / 4;// basic_cfg0 is mbtodec,should plus 1 tobe total mb unmber, so( basic_cfg0 + 1 + 3)/4  //(pCodecInf->CurPicMbNum + 3) / 4;
    SINT8 *p0, *p1,*p2,*p3,*p4,*p5,*p6;
    VC1BITPLANE_MB m_bitplane_group[4];
	pVc1DecParam->BitPlaneNum = Round;
    pVc1DecParam->NoBitplaneFlag = 0;
    p0 = pCodecInf->OVERFLAGS;
    p1 = pCodecInf->ACPRED;
    p2 = pCodecInf->SKIPMB;
    p3 = pCodecInf->FIELDTX;
    p4 = pCodecInf->MVTYPEMB;
    p5 = pCodecInf->DIRECTMB;
    p6 = pCodecInf->FORWARDMB;
	if (pCodecInf->PreParseInfo.IsAdvProfile)
	{
        for (_index = 0; _index < Round; _index++)
        {
            for (i = 0; i < 4; i++)
            {
                m_bitplane_group[i].u8 = 0;
    			m_bitplane_group[i].u8 = ((p0[i]&1)<<6) | ((p1[i]&1)<<5) | ((p2[i]&1)<<4) | ((p3[i]&1)<<3) | ((p4[i]&1)<<2) | ((p5[i]&1)<<1) | ((p6[i]&1));
            }
    		pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
    		p0 += 4;
    		p1 += 4;
    		p2 += 4;
    		p3 += 4;
    		p4 += 4;
    		p5 += 4;
    		p6 += 4;
        }
	}
	else
	{
	    for (_index = 0; _index < Round; _index++)
	    {
	        for (i = 0; i < 4; i++)
	        {
     	        m_bitplane_group[i].u8 = 0;
				//m_bitplane_group[0].u8 = 0;
                //m_bitplane_group[i].bits.skipmb   = pCodecInf->SKIPMB[_index * 4 + i];
                //m_bitplane_group[i].bits.mbtypemb = pCodecInf->MVTYPEMB[_index * 4 + i];
                //m_bitplane_group[i].bits.directmb = pCodecInf->DIRECTMB[_index * 4 + i];
    			m_bitplane_group[i].u8 = ((p2[i]&1)<<4) | ((p4[i]&1)<<2) | ((p5[i]&1)<<1);
	        }
			pVc1DecParam->vc1bitplane[_index] = m_bitplane_group[0].u8+ (m_bitplane_group[1].u8 << 8) + (m_bitplane_group[2].u8 << 16)+ (m_bitplane_group[3].u8 << 24);
    		p2 += 4;
    		p4 += 4;
    		p5 += 4;
        }
	}

    return;
}
#endif
static void VC1_ClearRefDispFlag(VC1_VFMWFRAMEOBJ_S* p_FrmObj)
{
    UINT32 i = 0;
	for(i = 0; i < VC1VFMW_MAX_FRAME_BUF_NUM; i++)
	{
		p_FrmObj[i].is_to_display = 0;
		p_FrmObj[i].is_to_ref= 0;  
	}
	return;
}

VOID VC1_CfgVDH(VC1_VFMWCODECINF_S *pCodecInf,VC1_DEC_PARAM_S *pVc1DecParam)
{
    UINT32 mbwidth, mbheight, mbtodec;
    SINT32 _index;
    UINT32 fwd_type, bwd_type, cur_type;

    if ((pCodecInf->PreParseInfo.IsAdvProfile)&&(VC1_VFMW_FIELDINTER==pCodecInf->AdvPicSyntax.FCM))
    {   
        mbheight  = ((SINT32)pCodecInf->CurPicMbHeight + 1)/2;
        mbwidth   = (SINT32)pCodecInf->CurPicMbWidth;
        mbtodec   = mbwidth * mbheight;
	    pVc1DecParam->basic_cfg0 = (mbtodec -1);   //field
    }
    else
    {
        pVc1DecParam->basic_cfg0 = (pCodecInf->CurPicMbNum -1); //frame
    }

    _index = pCodecInf->RefList0.ImgObj[0];
    fwd_type = pCodecInf->FrameObj[_index].img.is_fld_save;

    _index = pCodecInf->RefList1.ImgObj[0];
    bwd_type = pCodecInf->FrameObj[_index].img.is_fld_save;

    cur_type = pCodecInf->pCurFrm->img.is_fld_save;

    //REF_PIC_TYPE
    pVc1DecParam->ref_pic_type = 0;
    pVc1DecParam->ref_pic_type |= ( (fwd_type & 0x03) << 0 );
    pVc1DecParam->ref_pic_type |= ( (bwd_type & 0x03) << 2 );
    pVc1DecParam->ref_pic_type |= ( (cur_type & 0x03) << 4 );

    //FF_APT_EN
    pVc1DecParam->ff_apt_en = 0;//USE_FF_APT_EN;  // 0:frm save, 1:apt save
}

SINT32 VC1_Vfmw_GenerateDecPara(VC1_VFMWCODECINF_S *pCodecInf)
{
    return VC1_VFMW_TRUE;
}
SINT32 VC1DEC_GetImageBuffer(VC1_CTX_S * pCtx)
{
    VC1_VFMWCODECINF_S *pCodecInfo;

    pCodecInfo = &pCtx->CodecInfo;

    /* 1. 如果之前解了一个场对中的一场，另一场待解，返回TRUE */
    if ((VC1_VFMW_FIELDINTER == pCodecInfo->Last_Struct_IPB) && (1 != pCodecInfo->LastIs2ndFld))
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
SINT32  VC1_Vfmw_GetImageBuffer( VC1_CTX_S *pVC1_CTX_S)
{
    SINT32 i, k;
    SINT32 get_flag = 0;
    VC1_VFMWCODECINF_S  *pCodecInf;
    VC1_VFMWFRAMEOBJ_S *p_vobuf;
	
    pCodecInf = &(pVC1_CTX_S->CodecInfo);
    pCodecInf->CurFsID = FSP_NewLogicFs(pVC1_CTX_S->ChanID, 1);
    if (pCodecInf->CurFsID < 0)
    {
        /* 获取帧存失败 */
        dprint(PRN_FATAL,"get frame store fail!\n");
        VC1_CLEARREFFLAG;
        VC1_CLEARREFNUM;		
        FSP_ClearNotInVoQueue(pVC1_CTX_S->ChanID, &(pVC1_CTX_S->ImageQue));
        
        dprint(PRN_ERROR, "VC1_Vfmw_GetImageBuffer get imgbuf err, clear all ref!\n");
        return VC1_VFMW_FALSE;
    }
    p_vobuf = &(pCodecInf->FrameObj[0]);
    for (i = 0; i < VC1VFMW_MAX_FRAME_BUF_NUM; i++)
    {
        if ((p_vobuf[i].is_to_display== 0) && (p_vobuf[i].is_to_ref== 0))
        {
            get_flag = 1;
            pCodecInf->pCurFrm = &(p_vobuf[i]);
            p_vobuf[i].is_to_display = 1;
    
            for (k=0; k<256; k++)
            {
                pCodecInf->pCurFrm->IntensityConvertTab[0][0][k] = k;
                pCodecInf->pCurFrm->IntensityConvertTab[0][1][k] = k;
                pCodecInf->pCurFrm->IntensityConvertTab[1][0][k] = k;
                pCodecInf->pCurFrm->IntensityConvertTab[1][1][k] = k;
            }
    	    break;
        }
    }     
	
    if (get_flag == 1)
    {
        return VC1_VFMW_TRUE;
    }
    else
    {
        FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pCodecInf->CurFsID, 1);
        dprint(PRN_ERROR, "VC1_Vfmw_GetImageBuffer get_flag!=1, FSP_ClearLogicFs.\n");
        for (i = 0; i < VC1VFMW_MAX_FRAME_BUF_NUM; i++)
        {
            p_vobuf[i].is_to_display = 0;
            p_vobuf[i].is_to_ref= 0;
        }     
        return VC1_VFMW_FALSE;
    }
}

SINT32 VC1_Vfmw_GetStreamInfo(VC1_CTX_S *pVC1_CTX_S)
{
    SINT32 MbWidth ;
    SINT32 MbHeight ;
    SINT32 TotalMbNum ;
    SINT32 MEM_HEIGHT_MB;
    SINT32 MEM_WIDTH_MB;
    SINT32 FspHeight;
    SINT32 FspWidth;
    SINT8 SizeChanged;
    FSP_LOGIC_FS_S *pCur, *pBwd, *pFwd;
    VC1_VFMWCODECINF_S  *pCodecInf;
	IMAGE *pImg;

    pCodecInf = &(pVC1_CTX_S->CodecInfo);
    MbWidth   = pCodecInf->MbWidth;
    MbHeight  = ((pCodecInf->PreParseInfo.IsAdvProfile)
                       && (VC1_VFMW_FIELDINTER == pCodecInf->AdvPicSyntax.FCM)) ?
                      ((pCodecInf->MbHeight+1) / 2) : pCodecInf->MbHeight;
    TotalMbNum = MbWidth * MbHeight;
    if (pCodecInf->PreParseInfo.IsAdvProfile)
    {
        MEM_HEIGHT_MB = (pCodecInf->SynNew.AdvSeqSyntax.MAX_CODED_HEIGHT + 15)/16;
        MEM_WIDTH_MB = (pCodecInf->SynNew.AdvSeqSyntax.MAX_CODED_WIDTH + 15)/16;
    }
    else
    {
        MEM_HEIGHT_MB = pCodecInf->MbHeight;
        MEM_WIDTH_MB = pCodecInf->MbWidth;
    }
    
    if( MEM_WIDTH_MB * 16 < 32 || MEM_WIDTH_MB * 16 > MAX_HOR_SIZE || MEM_HEIGHT_MB * 16 < 32 || MEM_HEIGHT_MB * 16 > MAX_VER_SIZE)
    {
        dprint(PRN_FATAL, "image size abnormal(%dx%d)\n", MEM_WIDTH_MB * 16, MEM_HEIGHT_MB * 16 );
        return VC1_VFMW_FALSE;
    }
	
    if (MEM_HEIGHT_MB!=pCodecInf->MbHeightLast || MEM_WIDTH_MB!=pCodecInf->MbWidthLast)
    {
    	SizeChanged = 1;
	    pCodecInf->MbHeightLast = pCodecInf->MbHeight;
	    pCodecInf->MbWidthLast = pCodecInf->MbWidth;
	}
	else
	{
    	SizeChanged = 0;
	}
	pCodecInf->DDR_Stride = ((pCodecInf->MbWidth * 16) + 63) & 0xffffffc0;
	
    if ((0 == pCodecInf->Is2ndFld)||(!((VC1_VFMW_FIELDINTER == pCodecInf->Last_Struct_IPB) && (1 != pCodecInf->LastIs2ndFld))))
	{
        if((!VC1_CHECKSTAT(pCodecInf->CodecStatus, VC1_MALCOK)) || (SizeChanged == 1))//or size changed
        {
	        //clear ref pointers
            pCodecInf->pRef[0] =
            pCodecInf->pRef[1] =
            pCodecInf->pRef[2] =
            pCodecInf->pCurFrm = &(pCodecInf->ZeroFrm);
		 
            VC1_CLEARREFFLAG;
            VC1_CLEARREFNUM;
			VC1_ClearRefDispFlag(&(pCodecInf->FrameObj[0]));
            FSP_ClearNotInVoQueue(pVC1_CTX_S->ChanID, &(pVC1_CTX_S->ImageQue));

            // kirin产品，使用实际分辨率分配内存，所以在sizechanged时也需要重新划分
        #ifndef PRODUCT_KIRIN
            if (!VC1_CHECKSTAT(pCodecInf->CodecStatus, VC1_MALCOK))
        #endif
            {
                //未分配或者大小变化后,需要修改VO管理结构内的信息        
                ResetVoQueue(&pVC1_CTX_S->ImageQue);

                FspWidth  = pVC1_CTX_S->CodecInfo.DispPicWidth;
                FspHeight = pVC1_CTX_S->CodecInfo.DispPicHeight;
                
                pVC1_CTX_S->Vc1DecParam.RepairWidthInMb  =  (pVC1_CTX_S->CodecInfo.DispPicWidth  + 15) / 16;
				pVC1_CTX_S->Vc1DecParam.RepairHeightInMb = ((pVC1_CTX_S->CodecInfo.DispPicHeight + 15) / 16 + 1) / 2 * 2;
            
                if (VC1_VFMW_TRUE == VC1_ArrangeVahbMem(pVC1_CTX_S, FspWidth, FspHeight, 2))
                {	
		            pCodecInf->CodecStatus |= VC1_MALCOK;
                }
			    else
		        {
		            dprint(PRN_ERROR, "VC1_Vfmw_GetStreamInfo VC1_ArrangeVahbMem err!\n");
				    pCodecInf->CodecStatus &= (~(VC1_MALCOK));
                    return VC1_VFMW_FALSE;
				}
			}			
        }
        
        if (VC1_Vfmw_GetImageBuffer(pVC1_CTX_S) == VC1_VFMW_FALSE)
        {
            dprint(PRN_ERROR, "VC1_Vfmw_GetStreamInfo VC1_Vfmw_GetImageBuffer err!\n");
            return VC1_VFMW_FALSE;
        }
		
        pImg = FSP_GetFsImagePtr(pVC1_CTX_S->ChanID, pCodecInf->CurFsID);
		if (NULL != pImg)
		{
            pImg->PTS = pVC1_CTX_S->pstExtraData->pts;
            pImg->Usertag = pVC1_CTX_S->pstExtraData->Usertag;
            pImg->DispTime = pVC1_CTX_S->pstExtraData->DispTime;
            pImg->DispEnableFlag = pVC1_CTX_S->pstExtraData->DispEnableFlag;
            pImg->DispFrameDistance = pVC1_CTX_S->pstExtraData->DispFrameDistance;
            pImg->DistanceBeforeFirstFrame = pVC1_CTX_S->pstExtraData->DistanceBeforeFirstFrame;
            pImg->GopNum = pVC1_CTX_S->pstExtraData->GopNum;

            pVC1_CTX_S->pstExtraData->pts = (UINT64)(-1);
            dprint(PRN_PTS,"dec_pts: %lld Usertag = %lld\n",pImg->PTS, pImg->Usertag);
		}

        if ( (pCodecInf->PreParseInfo.IsAdvProfile) && (VC1_VFMW_FIELDINTER == pCodecInf->AdvPicSyntax.FCM) && (USE_FF_APT_EN==1)) 
        {
            pCodecInf->pCurFrm->img.is_fld_save = 1;
        }
        else
        {
            pCodecInf->pCurFrm->img.is_fld_save = 0;
        }
        pCodecInf->pCurFrm->RANGEREDFRM = 0;
        if (0 == pCodecInf->PreParseInfo.IsAdvProfile)
        {
            if (1 == pCodecInf->SMPSeqSyntax.RANGERED)
            {
                pCodecInf->pCurFrm->RANGEREDFRM = pCodecInf->SMPPicSyntax.RANGEREDFRM;
            }
        }
	    /* 参考维护， 倒参考帧*/
        if ((VC1_VFMW_IPIC == pCodecInf->PicCodingType) || (VC1_VFMW_PPIC == pCodecInf->PicCodingType) || (VC1_VFMW_SKPIC == pCodecInf->PicCodingType))
        {
            pCodecInf->RefNum = pCodecInf->RefNum>0?2:1;
            if (pCodecInf->FwdFsID != pCodecInf->BwdFsID)
            {
                //这样释放的才是有效参考图
                dprint(PRN_REF, "---------- unref %d\n", pCodecInf->FwdFsID);
                FSP_SetRef(pVC1_CTX_S->ChanID, pCodecInf->FwdFsID, 0);
            }
    	    pCodecInf->FwdFsID = pCodecInf->BwdFsID;
    	    pCodecInf->BwdFsID = pCodecInf->CurFsID;
    	    //dprint(PRN_DBG,"pCodecInf->FwdFsID=%d,pCodecInf->CurFsID=%d,pCodecInf->BwdFsID=%d\n",pCodecInf->FwdFsID,pCodecInf->CurFsID,pCodecInf->BwdFsID);
    	    FSP_SetRef(pVC1_CTX_S->ChanID, pCodecInf->CurFsID, 1);
    	    FSP_RemovePmv(pVC1_CTX_S->ChanID, pCodecInf->FwdFsID);
        }
        else
        {
            if (pCodecInf->RefNum < 2)
            {
                FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pCodecInf->CurFsID, 1);
                pCodecInf->pCurFrm->is_to_ref = 0;
                pCodecInf->pCurFrm->is_to_display = 0;
                 dprint(PRN_ERROR, "VC1_Vfmw_GetStreamInfo B pic pCodecInf->RefNum < 2 err!\n");
                return VC1_VFMW_FALSE;
            }
        }

        if ((VC1_VFMW_IPIC == pCodecInf->PicCodingType) || (VC1_VFMW_PPIC == pCodecInf->PicCodingType) || (VC1_VFMW_SKPIC == pCodecInf->PicCodingType))
        {
            pCodecInf->pRef[1]->is_to_ref = 0;
            pCodecInf->pCurFrm->is_to_ref = 1;
            pCodecInf->pRef[1] = pCodecInf->pRef[0];
            pCodecInf->pRef[0] = pCodecInf->pCurFrm;
        }
        pCur = FSP_GetLogicFs(pVC1_CTX_S->ChanID, pCodecInf->CurFsID);
        pFwd = FSP_GetLogicFs(pVC1_CTX_S->ChanID, pCodecInf->FwdFsID);
        pBwd = FSP_GetLogicFs(pVC1_CTX_S->ChanID, pCodecInf->BwdFsID);

        if ((NULL == pCur) || (NULL == pFwd) || (NULL == pBwd))
        {
   	        FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pCodecInf->CurFsID, 1);
			pCodecInf->pCurFrm->is_to_ref = 0;
			pCodecInf->pCurFrm->is_to_display = 0;
    	    dprint(PRN_FATAL, "line: %d (pCur,pFwd,pBwd)(%p,%p,%p)\n",__LINE__,pCur, pFwd, pBwd);
			if ((VC1_VFMW_SKPIC == pCodecInf->PicCodingType)&&(pCodecInf->skpic_flag >= 1))
			{
			    pCodecInf->skpic_flag = pCodecInf->skpic_flag - 1;
			}
            dprint(PRN_ERROR, "VC1_Vfmw_GetStreamInfo imgbuf = NULL err!\n");
    	    return VC1_VFMW_FALSE;
        }

        if ( (pCodecInf->PreParseInfo.IsAdvProfile) && (VC1_VFMW_FIELDINTER == pCodecInf->AdvPicSyntax.FCM)&&(USE_FF_APT_EN==1) ) 
        {
            pCur->stDispImg.is_fld_save = 1;
        }
        else
        {
            pCur->stDispImg.is_fld_save = 0;
        }
            /*如果是SKPIC，注意赋成前一个I或P帧的帧场属性*/		
        if (VC1_VFMW_SKPIC == pCodecInf->PicCodingType)
	    {
            pCur->stDispImg.is_fld_save = pFwd->stDispImg.is_fld_save;
            pCodecInf->pCurFrm->img.is_fld_save = pCodecInf->pRef[1]->img.is_fld_save;
			pCodecInf->skpic_flag = pCodecInf->skpic_flag + 1;
	    }
    	if ((NULL == pCur->pstDecodeFs) || (NULL == pCur->pstTfOutFs) || ((NULL == pCur->pstDispOutFs)))
    	{
   	        FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pCodecInf->CurFsID, 1);
			pCodecInf->pCurFrm->is_to_ref = 0;
			pCodecInf->pCurFrm->is_to_display = 0;
    	    dprint(PRN_FATAL, "CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\n",pCodecInf->FwdFsID,pCodecInf->CurFsID,
    		pCodecInf->BwdFsID, pCur->pstDecodeFs, pCur->pstTfOutFs, pCur->pstDispOutFs);
			if ((VC1_VFMW_SKPIC == pCodecInf->PicCodingType)&&(pCodecInf->skpic_flag >= 1))
			{
			    pCodecInf->skpic_flag = pCodecInf->skpic_flag - 1;
			}
            dprint(PRN_ERROR, "VC1_Vfmw_GetStreamInfo imgbuf = NULL err!\n");
    	    return VC1_VFMW_FALSE;
    	}
    	else
    	{
    	    pVC1_CTX_S->Vc1DecParam.BwdRefAddr   = (NULL != pBwd->pstDecodeFs)?pBwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
    	    pVC1_CTX_S->Vc1DecParam.FwdRefAddr   = (NULL != pFwd->pstDecodeFs)?pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
    	    pVC1_CTX_S->Vc1DecParam.ystaddr_1d = pCur->pstDecodeFs->PhyAddr;
    	    pVC1_CTX_S->Vc1DecParam.CurrColmbAddr = pCur->PmvAddr;
    	    pVC1_CTX_S->Vc1DecParam.BwdColmbAddr = pBwd->PmvAddr;
    	    pVC1_CTX_S->Vc1DecParam.CurFrmImgLuma2dPhyAddr = pCur->pstDispOutFs->PhyAddr;
			pVC1_CTX_S->Vc1DecParam.VahbStride = pCur->pstDispOutFs->Stride;
    	}
    }
    if (!pCodecInf->PreParseInfo.IsAdvProfile)
    {
        //SMP basic picture info
        pCodecInf->pCurFrm->PicStruct = VC1_VFMW_PROGRESSIVE;
        pCodecInf->pCurFrm->PicCodingType = pCodecInf->SMPPicSyntax.PTYPE;
        pCodecInf->pCurFrm->IsHalfPel[0] = pCodecInf->pCurFrm->IsHalfPel[1] =
            ( (VC1_1MVHP == pCodecInf->SMPPicSyntax.MVMODE)
            ||(VC1_1MVHPB == pCodecInf->SMPPicSyntax.MVMODE)
            ||((VC1_INTCMP== pCodecInf->SMPPicSyntax.MVMODE)
            &&((VC1_1MVHP == pCodecInf->SMPPicSyntax.MVMODE2)||(VC1_1MVHPB == pCodecInf->SMPPicSyntax.MVMODE2))))?
            1 : 0;

        //as we know, VC1 just has 2 ref frames, just like mpeg
        //ref list

        //bit stream
        pCodecInf->SlcNum = 1;
        pCodecInf->SlcStr[0].SlcNo     = 0;
        pCodecInf->SlcStr[0].pStream   = pCodecInf->stCurPacket.BsVirAddr[0] + BsPos(pCodecInf->pBs) / 8;//pCodecInf->pBsPack->VirAddr + BsPos(pCodecInf->pBs) / 8;
        pCodecInf->SlcStr[0].Phy_addr  = pCodecInf->stCurPacket.BsPhyAddr[0] + BsPos(pCodecInf->pBs) / 8 ;//pCodecInf->pBsPack->PhyAddr + BsPos(pCodecInf->pBs) / 8 ;
        pCodecInf->SlcStr[0].BitOffset = BsPos(pCodecInf->pBs) & 0x7;
        pCodecInf->SlcStr[0].Len       = pCodecInf->stCurPacket.BsLength[0]* 8 - BsPos(pCodecInf->pBs);//pCodecInf->pBsPack->Length * 8 - BsPos(pCodecInf->pBs);
        pCodecInf->SlcStr[0].SlcEndMbn = (pCodecInf->CurPicMbWidth * pCodecInf->CurPicMbHeight) - 1;//TotalMbNum - 1;//Modify by l57648   	
    }
    else
    {
        //ADV info
        SINT32 i;
        VC1_SLCSTREAM_S *pSlc;

        pCodecInf->pCurFrm->PicStruct = pCodecInf->AdvPicSyntax.FCM;
        pCodecInf->pCurFrm->PicCodingType = pCodecInf->AdvPicSyntax.PTYPE;
        pCodecInf->pCurFrm->IsHalfPel[pCodecInf->AdvPicSyntax.CurParity] = 
            ( (VC1_1MVHP == pCodecInf->AdvPicSyntax.MVMODE)
            ||(VC1_1MVHPB == pCodecInf->AdvPicSyntax.MVMODE)
            ||((VC1_INTCMP== pCodecInf->AdvPicSyntax.MVMODE)
            &&((VC1_1MVHP == pCodecInf->AdvPicSyntax.MVMODE2)||(VC1_1MVHPB == pCodecInf->AdvPicSyntax.MVMODE2))))?
            1 : 0;

            
        pCodecInf->SlcNum = (0 == pCodecInf->SlcNum) ? 1 : pCodecInf->SlcNum;
    
        for (i = 0; i < (pCodecInf->SlcNum - 1); i++)
        {
            pSlc = &pCodecInf->SlcStr[i];
            pSlc->SlcNo   = i;
            //mbnum in each slice
            pSlc->SlcEndMbn = pSlc[1].SlcEndMbn * MbWidth - 1;
        }
        pSlc = &pCodecInf->SlcStr[pCodecInf->SlcNum - 1];
        pSlc->SlcNo   = pCodecInf->SlcNum - 1;
        //last slice mb num
        pSlc->SlcEndMbn = TotalMbNum - 1;
		
        if(VC1_VFMW_BPIC == pCodecInf->PicCodingType)
        {
            //BRFD & FRFD
            pCodecInf->FRFD = (pCodecInf->AdvPicSyntax.ScaleFactor * pCodecInf->AdvPicSyntax.REFDIST)>>8;
            pCodecInf->BRFD = pCodecInf->AdvPicSyntax.REFDIST - pCodecInf->FRFD - 1;
            if (pCodecInf->BRFD<0)
            {
                pCodecInf->BRFD = 0;
            }
        }
    }
    if (VC1_Vfmw_BuildRefList(pCodecInf, pCodecInf->PicCodingType, 0, 1) == VC1_VFMW_FALSE)
    {
        FSP_ClearLogicFs(pVC1_CTX_S->ChanID, pCodecInf->CurFsID, 1);
        pCodecInf->pCurFrm->is_to_ref = 0;
        pCodecInf->pCurFrm->is_to_display = 0;
        dprint(PRN_ERROR, "VC1_Vfmw_GetStreamInfo VC1_Vfmw_BuildRefList err!\n");
	    return VC1_VFMW_FALSE;
	}
    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_PrepareDecode(VC1_CTX_S *pVC1_CTX_S)
{
    if (VC1_VFMW_FALSE == VC1_Vfmw_GetStreamInfo(pVC1_CTX_S))
    {
        //dprint(PRN_FATAL, "VC1_Vfmw_GetStreamInfo error! Release all packets!\n");
        //ReleasePacket(VFMW_VC1, pVC1_CTX_S);
        //VC1_ClearCurPic(&(pVC1_CTX_S->CodecInfo), pVC1_CTX_S->ChanID);

        return VC1_VFMW_FALSE;
    }
    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_DecodeArbiter(VC1_CTX_S *pVC1_CTX_S)
{
    VC1_VFMWCODECINF_S *pCodecInf;
    VC1_VFMWSYNTAX_S *pSyntax;
    SINT32 ret = VC1_VFMW_TRUE;
	
    pCodecInf = &pVC1_CTX_S->CodecInfo;
    pSyntax = &(pVC1_CTX_S->CodecInfo.SynNew);
	
    if (!VC1_CHECKSTAT(pCodecInf->CodecStatus, VC1_ALLSLCOK))
    {
        return VC1_VFMW_FALSE;
    }	
    //clear pps ok and allslcoke
    pCodecInf->CodecStatus &= (~(VC1_ALLSLCOK | VC1_PPSOK));
	
    /* 解码模式(IPB,IP,I)的处理 */
    if ( (pCodecInf->UsedDecMode == I_MODE || pCodecInf->UsedDecMode == DISCARD_MODE) &&
		 (pVC1_CTX_S->pstExtraData->s32DecMode == IP_MODE || pVC1_CTX_S->pstExtraData->s32DecMode == IPB_MODE || 
		 pVC1_CTX_S->pstExtraData->s32DecMode == DISCARD_B_BF_P_MODE) )
    {
        /* I->IP 或 I->IPB都有可能引发参考错误，所以需要找下一个I帧才行 */
        dprint(PRN_CTRL,"----------------- VC1 Imode -> %d ------------------\n", pVC1_CTX_S->pstExtraData->s32DecMode);
        VC1_CLEARREFFLAG;
        pCodecInf->RefNum = 0;//清空参考图记数器，后续码流将完全重新来过
        
        if ( (NULL != pCodecInf->pRef[0]) && (NULL != pCodecInf->pRef[1]) )
        {
            pCodecInf->pRef[0]->is_to_display = 0;
            pCodecInf->pRef[1]->is_to_display = 0;
            pCodecInf->pRef[0]->is_to_ref = 0;
            pCodecInf->pRef[1]->is_to_ref = 0;
        }
    }
    pCodecInf->UsedDecMode = pVC1_CTX_S->pstExtraData->s32DecMode;
    switch (pCodecInf->UsedDecMode)
    {
        case DISCARD_MODE:
			ret = VC1_VFMW_FALSE;
			break;
        case IP_MODE://IP模式
            if ((pCodecInf->PicCodingType==VC1_VFMW_BIPIC)||(pCodecInf->PicCodingType==VC1_VFMW_BPIC))
            {
                //B图不解
                ret = VC1_VFMW_FALSE;
            }
            break;
        case I_MODE://I模式
            if (pCodecInf->PicCodingType!=VC1_VFMW_IPIC)
            {
                //B,P图不解
                ret = VC1_VFMW_FALSE;
            }
			#if 0
            if ((pSyntaxInfNew->picture_coding_type==P_TYPE)&&
               ((pSyntaxInfNew->picture_structure==FRAME_PICTURE)||
               (pMp2CodecInfo->LastDecPicCodingType!=I_TYPE)))
            {
                //如果不是IP场对的P图，也不解
                ret = MPEG2_FALSE;
            }
			#endif
            break;
        case DISCARD_B_BF_P_MODE:
            if (VC1_VFMW_IPIC==pCodecInf->PicCodingType)
            {
                 pCodecInf->PPicFound = 0;
            }
            
            if ( (VC1_VFMW_BPIC==pCodecInf->PicCodingType) && (0==pCodecInf->PPicFound) )  /*发现B帧*/
            {
                ret = VC1_VFMW_FALSE;
            }
            else if ( (VC1_VFMW_PPIC==pCodecInf->PicCodingType) || (VC1_VFMW_SKPIC==pCodecInf->PicCodingType) )
            {
                pCodecInf->PPicFound = 1;
            }
            break;
        default: 
          break;
    }
    if ((pCodecInf->RefNum<1)&&
        ((pCodecInf->PicCodingType==VC1_VFMW_PPIC)||
         (pCodecInf->PicCodingType==VC1_VFMW_SKPIC)||
         (pCodecInf->PicCodingType==VC1_VFMW_BIPIC)||
         (pCodecInf->PicCodingType==VC1_VFMW_BPIC)))
    {
        //解码非I/非D图而又没有参考图
        dprint(PRN_ERROR, "NOTE: Drop non-I\n");
        ret = VC1_VFMW_FALSE;
    }
    else if ((pCodecInf->RefNum<2)&&((pCodecInf->PicCodingType==VC1_VFMW_BIPIC)||(pCodecInf->PicCodingType==VC1_VFMW_BPIC)))
    {
        dprint(PRN_ERROR, "NOTE: Drop B\n");
        ret = VC1_VFMW_FALSE;
    }

    if (VC1_VFMW_FALSE == ret)
    {
//        ReleasePacket(VFMW_VC1, pVC1_CTX_S);
        VC1_ClearCurPic(&(pVC1_CTX_S->CodecInfo), pVC1_CTX_S->ChanID);
        REPORT_DECSYNTAX_ERR(pVC1_CTX_S->ChanID);
        
        return ret;
    }

    if (!pCodecInf->PreParseInfo.IsAdvProfile)
    {
        //SMP
        pCodecInf->SMPSeqSyntax = pSyntax->SMPSeqSyntax;
        pCodecInf->SMPPicSyntax = pSyntax->SMPPicSyntax;
    }
    else
    {
        //ADV profile
        //SINT32 i;
        pCodecInf->AdvSeqSyntax = pSyntax->AdvSeqSyntax;
        pCodecInf->AdvEntSyntax = pSyntax->AdvEntSyntax;
        pCodecInf->AdvPicSyntax = pSyntax->AdvPicSyntax;
        pCodecInf->PicStructure = pSyntax->AdvPicSyntax.FCM;
        //for (i = 0; i < pCodecInf->SlcNum; i++)
        //{
            //pCodecInf->AdvSlcSyntax[i] = pSyntax->AdvSlcSyntax[i];
        //}
		memcpy(pCodecInf->AdvSlcSyntax, pSyntax->AdvSlcSyntax, sizeof(VC1_ADVSLCSYNTAX_S)*pCodecInf->SlcNum);
    }

    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_StartDecode(VC1_CTX_S *pVC1_CTX_S)
{
    VC1_VFMWCODECINF_S  *pCodecInf;
    VC1_DEC_PARAM_S    *pVc1DecParam;
    pCodecInf = &(pVC1_CTX_S->CodecInfo);
    pVc1DecParam = &(pVC1_CTX_S->Vc1DecParam);
    pVc1DecParam->Compress_en = pVC1_CTX_S->pstExtraData->s32Compress_en;

    if (1 != pCodecInf->PreParseInfo.IsAdvProfile)
    {
        VC1_Vfmw_UpdataLastPicRNDCTRL(pCodecInf);
    }
    //dprint(PRN_FATAL,"pCodecInf->PicCodingType=%d\n",pCodecInf->PicCodingType);
    VC1_WritePicMsg(pVC1_CTX_S,pVc1DecParam);
    VC1_WriteSliceMsg(pCodecInf,pVc1DecParam);
    VC1_CfgVDH(pCodecInf,pVc1DecParam);
#ifndef VFMW_BPD_H_SUPPORT    
    VC1_WriteBitplaneMsg(pCodecInf,pVc1DecParam);
#endif
    if ((pCodecInf->PicCodingType == VC1_VFMW_IPIC)||(pCodecInf->PicCodingType == VC1_VFMW_PPIC))
    {
	    pCodecInf->Last_Struct = pCodecInf->PicStructure;
    }

	if (VC1_VFMW_SKPIC == pCodecInf->PicCodingType)
	{
        pVc1DecParam->IsSkpicCopy = 1;// 1
		pCodecInf->PicStructure = pCodecInf->Last_Struct;
		pCodecInf->Is2ndFld = 1;
		pVc1DecParam->basic_cfg0 = (pCodecInf->CurPicMbNum -1);
	}
	else
	{
        pVc1DecParam->IsSkpicCopy = 0;
	}
	pVc1DecParam->picstructure = pCodecInf->PicStructure;

    pCodecInf->Last_Struct_IPB = pCodecInf->PicStructure;
    pCodecInf->LastIs2ndFld = pCodecInf->Is2ndFld;

    if ( (VC1_VFMW_BPIC==pVc1DecParam->ptype) && (0==pCodecInf->PPicFound) )  //&& (pCodecInf->BPicCount<5) ) /* 发现B帧*/
    {
        //ReleasePacket(VFMW_VC1, (VOID *)pVC1_CTX_S);
        VC1_ClearCurPic(&(pVC1_CTX_S->CodecInfo), pVC1_CTX_S->ChanID);
        pCodecInf->pCurFrm->is_to_ref = 0;
        pCodecInf->BPicCount++;
        pVC1_CTX_S->pVc1DecParam = NULL;
        return VC1_VFMW_FALSE;
    }
    else if ( (VC1_VFMW_PPIC == pVc1DecParam->ptype) || (VC1_VFMW_SKPIC == pVc1DecParam->ptype) )
    {
        pCodecInf->PPicFound = 1;
    }

    pVC1_CTX_S->pVc1DecParam = &(pVC1_CTX_S->Vc1DecParam);

    if (1 == pVC1_CTX_S->pstExtraData->stDisParams.s32Mode)
    {
        if ((NULL != pVC1_CTX_S->pVc1DecParam) && 
           ((VC1_VFMW_BPIC == pVC1_CTX_S->pVc1DecParam->ptype) || 
           (VC1_VFMW_BIPIC == pVC1_CTX_S->pVc1DecParam->ptype)))
        {
	        pCodecInf->pCurFrm->is_to_display = 0;
            //FSP_SetDisplay(pVC1_CTX_S->ChanID, pVC1_CTX_S->CodecInfo.CurFsID, 0);
            VC1_ClearCurPic(&(pVC1_CTX_S->CodecInfo), pVC1_CTX_S->ChanID);
            pVC1_CTX_S->pVc1DecParam = NULL;
            return VC1_VFMW_FALSE;
        }
    }
    else if (2 == pVC1_CTX_S->pstExtraData->stDisParams.s32Mode)
    {
        if ((pVC1_CTX_S->pstExtraData->stDisParams.s32DisNums > 0) && (NULL != pVC1_CTX_S->pVc1DecParam)
           && ((VC1_VFMW_BPIC == pVC1_CTX_S->pVc1DecParam->ptype)||
           (VC1_VFMW_BIPIC == pVC1_CTX_S->pVc1DecParam->ptype)))
        {
	        pCodecInf->pCurFrm->is_to_display = 0;
            //FSP_SetDisplay(pVC1_CTX_S->ChanID, pVC1_CTX_S->CodecInfo.CurFsID, 0);
            pVC1_CTX_S->pstExtraData->stDisParams.s32DisNums--;
            VC1_ClearCurPic(&(pVC1_CTX_S->CodecInfo), pVC1_CTX_S->ChanID);
            pVC1_CTX_S->pVc1DecParam = NULL;
            return VC1_VFMW_FALSE;
        }
    }

    return VC1_VFMW_TRUE;
}

static VOID VC1_Vfmw_GenerateIntensityMap(UINT8 *pLUTable, SINT32 LUMSCALE, SINT32 LUMSHIFT, UINT8 YcFlg)
{
	SINT32 i, j;
    SINT32 iScale, iShift;
	iScale = LUMSCALE;
	iShift = LUMSHIFT;
	
	if (LUMSHIFT> 31)
    { LUMSHIFT -= 64; }
	
	// remap luminance scale and shift
	if (LUMSCALE == 0) 
	{ 
		iScale = - 64;
		iShift = 255 * 64 - LUMSHIFT * 2 * 64;
	}
	else 
	{
		iScale = LUMSCALE  + 32;
		iShift = LUMSHIFT * 64;
	}

	if (YcFlg == 0)  // luma
	{
		for (i = 0; i < 256; i++) 
		{
			j = (iScale * i + iShift + 32) >> 6;
			if (j > 255)
            { j = 255; }
			else if (j < 0)
            { j = 0; }
			pLUTable[i] = (UINT8) j;
		}
	}
	else // chroma
	{
		for (i = 0; i < 256; i++)
		{
			j = (iScale * (i - 128) + 128 * 64 + 32) >>6;
			
			if (j > 255)
            { j = 255; }
			else if (j < 0)
            { j = 0; }
			pLUTable[i] = (UINT8) j;
		}
	}
	return;
} 

SINT32 VC1_Vfmw_BuildRefList(VC1_VFMWCODECINF_S *pCodecInf, SINT32 PicType, SINT32 SndFld, SINT32 IsTop)
{
    SINT32 FwdRefIdx, BwdRefIdx;
    UINT8  LUTY[256], LUTUV[256];
    UINT8  LUMSCALE, LUMSHIFT, MVMODE;
    SINT32 i;

    memset(&pCodecInf->RefList0, 0, sizeof(pCodecInf->RefList0));
    memset(&pCodecInf->RefList1, 0, sizeof(pCodecInf->RefList1));
    if ((VC1_VFMW_PROGRESSIVE == pCodecInf->PicStructure)
        || (VC1_VFMW_FRAMEINTER == pCodecInf->PicStructure))
    {
        if (VC1_VFMW_PPIC == PicType)
        {
            pCodecInf->RefList0.ListLen = 1;
            pCodecInf->RefList1.ListLen = 0;
            pCodecInf->RefList0.FldFlag[0] = 0;
            pCodecInf->RefList0.ImgObj[0] = pCodecInf->pRef[1]->img.image_id;
			FwdRefIdx = pCodecInf->RefList0.ImgObj[0];

            if (pCodecInf->PreParseInfo.IsAdvProfile)
            {
               LUMSCALE = pCodecInf->AdvPicSyntax.LUMSCALE;
               LUMSHIFT = pCodecInf->AdvPicSyntax.LUMSHIFT;
               MVMODE   = pCodecInf->AdvPicSyntax.MVMODE;
			   if (VC1_VFMW_FRAMEINTER == pCodecInf->AdvPicSyntax.FCM && 
				   1 == pCodecInf->AdvPicSyntax.INTCOMP)
			   {
				   MVMODE = VC1_INTCMP;
			   }
            }
            else
            {
               LUMSCALE = pCodecInf->SMPPicSyntax.LUMSCALE;
               LUMSHIFT = pCodecInf->SMPPicSyntax.LUMSHIFT;
               MVMODE   = pCodecInf->SMPPicSyntax.MVMODE;
            }

            if (VC1_INTCMP == MVMODE)
            {
              VC1_Vfmw_GenerateIntensityMap(LUTY, LUMSCALE, LUMSHIFT, 0);
              VC1_Vfmw_GenerateIntensityMap(LUTUV, LUMSCALE, LUMSHIFT, 1); 
              for (i=0; i<256; i++)
              {
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i] = 
                  LUTY[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i]]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i] = 
                  LUTUV[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i]]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i] = 
                  LUTY[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i]]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i] = 
                  LUTUV[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i]]; 
              }
            }

            for (i=0; i<256; i++)
            {
              pCodecInf->IntensityConvertTab[0][0][0][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i];
              pCodecInf->IntensityConvertTab[0][0][1][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i];
              pCodecInf->IntensityConvertTab[0][1][0][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i];
              pCodecInf->IntensityConvertTab[0][1][1][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i];
            }
        }
        else if (VC1_VFMW_BPIC == PicType)
        {
            pCodecInf->RefList0.ListLen = pCodecInf->RefList1.ListLen = 1;
            pCodecInf->RefList0.FldFlag[0] = 0;
            pCodecInf->RefList0.ImgObj[0]  = pCodecInf->pRef[1]->img.image_id;
            pCodecInf->RefList1.FldFlag[0] = 0;
            pCodecInf->RefList1.ImgObj[0] = pCodecInf->pRef[0]->img.image_id;
			FwdRefIdx = pCodecInf->RefList0.ImgObj[0];
            BwdRefIdx = pCodecInf->RefList1.ImgObj[0];

            if (pCodecInf->PreParseInfo.IsAdvProfile)
            {
               LUMSCALE = pCodecInf->AdvPicSyntax.LUMSCALE;
               LUMSHIFT = pCodecInf->AdvPicSyntax.LUMSHIFT;
               MVMODE   = pCodecInf->AdvPicSyntax.MVMODE;
            }
            else
            {
               LUMSCALE = pCodecInf->SMPPicSyntax.LUMSCALE;
               LUMSHIFT = pCodecInf->SMPPicSyntax.LUMSHIFT;
               MVMODE   = pCodecInf->SMPPicSyntax.MVMODE;
            }

            if (VC1_INTCMP == MVMODE)
            {
              VC1_Vfmw_GenerateIntensityMap(LUTY, LUMSCALE, LUMSHIFT, 0);
              VC1_Vfmw_GenerateIntensityMap(LUTUV, LUMSCALE, LUMSHIFT, 1); 

              // 更新每个参考帧/场
#if 1
              for (i=0; i<256; i++)
              {
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i] = 
                  LUTY[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i]]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i] = 
                  LUTUV[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i]]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i] = 
                  LUTY[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i]]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i] = 
                  LUTUV[pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i]]; 

                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][0][i] = 
                  LUTY[pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][0][i]]; 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][1][i] = 
                  LUTUV[pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][1][i]]; 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][0][i] = 
                  LUTY[pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][0][i]]; 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][1][i] = 
                  LUTUV[pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][1][i]]; 
              }
#else
              for (i=0; i<256; i++)
              {
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i] = 
                  pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i] = 
                  pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i] = 
                  pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i]; 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i] = 
                  pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i]; 

                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][0][i] = 
                  pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][0][i]; 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][1][i] = 
                  pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][1][i]; 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][0][i] = 
                  pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][0][i]; 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][1][i] = 
                  pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][1][i]; 
              }
#endif
            }

            for (i=0; i<256; i++)
            {
              pCodecInf->IntensityConvertTab[0][0][0][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i];
              pCodecInf->IntensityConvertTab[0][0][1][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i];
              pCodecInf->IntensityConvertTab[0][1][0][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i];
              pCodecInf->IntensityConvertTab[0][1][1][i] = 
                pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i];

              pCodecInf->IntensityConvertTab[1][0][0][i] = 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][0][i];
              pCodecInf->IntensityConvertTab[1][0][1][i] = 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][1][i];
              pCodecInf->IntensityConvertTab[1][1][0][i] = 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][0][i];
              pCodecInf->IntensityConvertTab[1][1][1][i] = 
                pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][1][i];
            }
        }
        else
        {
            pCodecInf->RefList0.ListLen = pCodecInf->RefList1.ListLen = 0;
        }
    }
    else
    {
        SINT32 NumOfRef = 0;
		SINT32 TopRefIdx, BotRefIdx, CurRefIdx;
        
        FwdRefIdx = pCodecInf->RefList0.ImgObj[0];
        BwdRefIdx = pCodecInf->RefList1.ImgObj[0];
		CurRefIdx = pCodecInf->pCurFrm->img.image_id;

		if (1 == pCodecInf->AdvPicSyntax.TFF)
		{
			if (0 == pCodecInf->AdvPicSyntax.CurParity)
			{
				TopRefIdx = pCodecInf->pRef[1]->img.image_id;
				BotRefIdx = pCodecInf->pRef[1]->img.image_id;
			}
			else
			{
				TopRefIdx = pCodecInf->pRef[0]->img.image_id;
				BotRefIdx = pCodecInf->pRef[1]->img.image_id;
			}
		}
		else
		{
			if (0 == pCodecInf->AdvPicSyntax.CurParity)
			{
				TopRefIdx = pCodecInf->pRef[1]->img.image_id;
				BotRefIdx = pCodecInf->pRef[0]->img.image_id;
			}
			else
			{
				TopRefIdx = pCodecInf->pRef[1]->img.image_id;
				BotRefIdx = pCodecInf->pRef[1]->img.image_id;
			}
		}

        if (VC1_VFMW_PPIC == PicType)
        {
            NumOfRef = (pCodecInf->AdvPicSyntax.NUMREF + 1);
            pCodecInf->RefList0.ListLen = NumOfRef;
            pCodecInf->RefList1.ListLen = 0;
            pCodecInf->RefList0.FldFlag[0] = 0;
            pCodecInf->RefList0.FldFlag[1] = 1;
            if (SndFld)
            {
                pCodecInf->RefList0.ImgObj[0] = (IsTop) ? pCodecInf->pRef[1]->img.image_id : pCodecInf->pCurFrm->img.image_id;
            }
            else
            {
                pCodecInf->RefList0.ImgObj[0] = pCodecInf->pRef[1]->img.image_id;
            }

            pCodecInf->RefList0.ImgObj[1] = pCodecInf->pRef[1]->img.image_id;

			FwdRefIdx = pCodecInf->RefList0.ImgObj[0];
			BwdRefIdx = pCodecInf->RefList1.ImgObj[0];
    		CurRefIdx = pCodecInf->pCurFrm->img.image_id;

            if ((VC1_BOTHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD || 
                VC1_TOPHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD) &&
                VC1_INTCMP == pCodecInf->AdvPicSyntax.MVMODE)
            {
				// 更新顶场 intensity表
                LUMSCALE = pCodecInf->AdvPicSyntax.LUMSCALE;
                LUMSHIFT = pCodecInf->AdvPicSyntax.LUMSHIFT;
                VC1_Vfmw_GenerateIntensityMap(LUTY, LUMSCALE, LUMSHIFT, 0);
                VC1_Vfmw_GenerateIntensityMap(LUTUV, LUMSCALE, LUMSHIFT, 1);

                //FwdRefIdx = pCodecInf->RefList0.ImgObj[0];
                for (i=0; i<256; i++)
                {
                  pCodecInf->FrameObj[TopRefIdx].IntensityConvertTab[0][0][i] = 
                    LUTY[pCodecInf->FrameObj[TopRefIdx].IntensityConvertTab[0][0][i]]; 
                  pCodecInf->FrameObj[TopRefIdx].IntensityConvertTab[0][1][i] = 
                    LUTUV[pCodecInf->FrameObj[TopRefIdx].IntensityConvertTab[0][1][i]]; 
                }
            }

            if ((VC1_BOTHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD || 
                VC1_BOTFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD) &&
                VC1_INTCMP == pCodecInf->AdvPicSyntax.MVMODE )
            {
				// 更新底场 intensity表
                LUMSCALE = (VC1_BOTHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD)? 
                    pCodecInf->AdvPicSyntax.LUMSCALE2: pCodecInf->AdvPicSyntax.LUMSCALE;
                LUMSHIFT = (VC1_BOTHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD)?
                    pCodecInf->AdvPicSyntax.LUMSHIFT2: pCodecInf->AdvPicSyntax.LUMSHIFT;
                VC1_Vfmw_GenerateIntensityMap(LUTY, LUMSCALE, LUMSHIFT, 0);
                VC1_Vfmw_GenerateIntensityMap(LUTUV, LUMSCALE, LUMSHIFT, 1);
        
                //FwdRefIdx = pCodecInf->RefList0.ImgObj[1];
                for (i=0; i<256; i++)
                {
                  pCodecInf->FrameObj[BotRefIdx].IntensityConvertTab[1][0][i] = 
                    LUTY[pCodecInf->FrameObj[BotRefIdx].IntensityConvertTab[1][0][i]]; 
                  pCodecInf->FrameObj[BotRefIdx].IntensityConvertTab[1][1][i] = 
                    LUTUV[pCodecInf->FrameObj[BotRefIdx].IntensityConvertTab[1][1][i]]; 
                }
            }
            
            // 生成 前向参考帧 和 当前帧的 intensity表
            for (i=0; i<256; i++)
            {
                pCodecInf->IntensityConvertTab[0][0][0][i] = 
			        pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i];
			    pCodecInf->IntensityConvertTab[0][0][1][i] = 
                    pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i];
                pCodecInf->IntensityConvertTab[0][1][0][i] = 
                    pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i];
                pCodecInf->IntensityConvertTab[0][1][1][i] = 
                    pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i];

                pCodecInf->IntensityConvertTab[2][0][0][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[0][0][i];
			    pCodecInf->IntensityConvertTab[2][0][1][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[0][1][i];
                pCodecInf->IntensityConvertTab[2][1][0][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[1][0][i];
                pCodecInf->IntensityConvertTab[2][1][1][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[1][1][i];
            }
        }
        else if (VC1_VFMW_BPIC == PicType)
        {
            NumOfRef = 2;
            pCodecInf->RefList0.ListLen = pCodecInf->RefList1.ListLen = 2;
            pCodecInf->RefList0.FldFlag[0] = 0;
            pCodecInf->RefList0.FldFlag[1] = 1;
            if (SndFld)
            {
                pCodecInf->RefList0.ImgObj[0] = (IsTop) ?
                                                pCodecInf->pRef[1]->img.image_id : pCodecInf->pCurFrm->img.image_id;
            }
            else
            {
                pCodecInf->RefList0.ImgObj[0] = pCodecInf->pRef[1]->img.image_id;
            }

            pCodecInf->RefList1.FldFlag[0] = 0;
            pCodecInf->RefList1.FldFlag[1] = 1;
            pCodecInf->RefList1.ImgObj[0] = pCodecInf->pRef[0]->img.image_id;
            pCodecInf->RefList1.ImgObj[1] = pCodecInf->pRef[0]->img.image_id;

			FwdRefIdx = pCodecInf->RefList0.ImgObj[0];
			BwdRefIdx = pCodecInf->RefList1.ImgObj[0];
    		CurRefIdx = pCodecInf->pCurFrm->img.image_id;

            if ((VC1_BOTHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD || 
                VC1_TOPHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD) &&
                VC1_INTCMP == pCodecInf->AdvPicSyntax.MVMODE)
            {
	            return VC1_VFMW_FALSE;
			}

            if ((VC1_BOTHFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD || 
                VC1_BOTFLDINT == pCodecInf->AdvPicSyntax.INTCOMPFIELD) &&
                VC1_INTCMP == pCodecInf->AdvPicSyntax.MVMODE )
            {
	            return VC1_VFMW_FALSE;
	        }

            // 生成 前向参考帧 和 当前帧的 intensity表
            for (i=0; i<256; i++)
            {
                pCodecInf->IntensityConvertTab[0][0][0][i] = 
					pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][0][i];
				pCodecInf->IntensityConvertTab[0][0][1][i] = 
                    pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[0][1][i];
                pCodecInf->IntensityConvertTab[0][1][0][i] = 
                    pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][0][i];
                pCodecInf->IntensityConvertTab[0][1][1][i] = 
                    pCodecInf->FrameObj[FwdRefIdx].IntensityConvertTab[1][1][i];

                pCodecInf->IntensityConvertTab[1][0][0][i] = 
					pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][0][i];
				pCodecInf->IntensityConvertTab[1][0][1][i] = 
                    pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[0][1][i];
                pCodecInf->IntensityConvertTab[1][1][0][i] = 
                    pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][0][i];
                pCodecInf->IntensityConvertTab[1][1][1][i] = 
                    pCodecInf->FrameObj[BwdRefIdx].IntensityConvertTab[1][1][i];
				
                pCodecInf->IntensityConvertTab[2][0][0][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[0][0][i];
				pCodecInf->IntensityConvertTab[2][0][1][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[0][1][i];
                pCodecInf->IntensityConvertTab[2][1][0][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[1][0][i];
                pCodecInf->IntensityConvertTab[2][1][1][i] = 
                    pCodecInf->FrameObj[CurRefIdx].IntensityConvertTab[1][1][i];
            }
        }
        else
        {
            pCodecInf->RefList0.ListLen = pCodecInf->RefList1.ListLen = 0;
        }
    }

	return VC1_VFMW_TRUE;
}

SINT32 VC1_DecMvrange(BS *pBs)
{
    const VC1_VFMW_VLC_S VlcTab[8] = {{0, 1}, { 0, 1}, { 0, 1}, { 0, 1},
        {1, 2}, { 1, 2}, { 2, 3}, { 3, 3}
    };
    SINT32 Code, Len;
    SINT32 Tmp = BsShow(pBs, 3);

    Len  = VlcTab[Tmp].Len;
    Code = VlcTab[Tmp].Code;
    BsSkip(pBs, Len);
    return Code;
}

SINT32 VC1_DecTransacfrm(BS *pBs)
{
    const VC1_VFMW_VLC_S VlcTab[8] = {{0, 1}, {0, 1}, {1, 2}, {2, 2}};
    SINT32 Code, Len;
    SINT32 Tmp = BsShow(pBs, 2);

    Len  = VlcTab[Tmp].Len;
    Code = VlcTab[Tmp].Code;
    BsSkip(pBs, Len);
    return Code;
}

VOID VC1_SetCurPicResolutionInfo(VC1_VFMWCODECINF_S *pCodecInfo, SINT32 RESPIC)
{
    //dprint(PRN_DBG,"VC1_SetCurPicResolutionInfo\n");
    switch (RESPIC)
    {
    case 0:
        //full all
        pCodecInfo->CurPicMbWidth = pCodecInfo->MbWidth;
        pCodecInfo->CurPicMbHeight = pCodecInfo->MbHeight;
	 //dprint(PRN_DBG,"full all\n");
        break;
    case 1:
        //hor half
        pCodecInfo->CurPicMbWidth = (pCodecInfo->MbWidth+1)/2;
        pCodecInfo->CurPicMbHeight = pCodecInfo->MbHeight;
	 //dprint(PRN_DBG,"hor half\n");
        break;
    case 2:
        //vert half
        pCodecInfo->CurPicMbWidth = pCodecInfo->MbWidth;
        pCodecInfo->CurPicMbHeight = (pCodecInfo->MbHeight+1)/2;
	 //dprint(PRN_DBG,"vert half\n");
        break;
    default:
        //half all
        pCodecInfo->CurPicMbWidth = (pCodecInfo->MbWidth+1)/2;
        pCodecInfo->CurPicMbHeight = (pCodecInfo->MbHeight+1)/2;
	 //dprint(PRN_DBG,"half all\n");
        break;
    }
    pCodecInfo->CurPicWidth = pCodecInfo->CurPicMbWidth * 16;
    pCodecInfo->CurPicHeight = pCodecInfo->CurPicMbHeight * 16;
    pCodecInfo->CurPicMbNum = pCodecInfo->CurPicMbWidth * pCodecInfo->CurPicMbHeight;
}

SINT32 VC1_DecMvmodeProgrP(BS *pBs, UINT8 PQUANT)
{
    SINT32 Code, Len;
    SINT32 Tmp = BsShow(pBs, 4);
    const SINT32 ModeLow[5]  = {VC1_1MVHPB, VC1_1MV, VC1_1MVHP, VC1_MIXMV, VC1_INTCMP};
    const SINT32 ModeHigh[5] = {VC1_1MV, VC1_MIXMV, VC1_1MVHP, VC1_1MVHPB, VC1_INTCMP};

    if (2 > Tmp)
    {
        Code = Tmp ? 4 : 3;
        Len = 4;
    }
    else if (4 > Tmp)
    {
        Code = 2;
        Len = 3;
    }
    else if (8 > Tmp)
    {
        Code = 1;
        Len = 2;
    }
    else
    {
        Code = 0;
        Len = 1;
    }

    BsSkip(pBs, Len);
    if (PQUANT > 12)
    {
        Code = ModeLow[Code];
    }
    else
    {
        Code = ModeHigh[Code];
    }

    return Code;
}

SINT32 VC1_DecMvmodeProgrB(BS *pBs, UINT8 PQUANT)
{
    SINT32 Code;
    SINT32 Tmp = BsSkip(pBs, 1);
    const SINT32 Mode[2]  = {VC1_1MVHPB, VC1_1MV};
    Code = Mode[Tmp];
    return Code;
}

SINT32 VC1_DecMvmodeInterB(BS *pBs, UINT8 PQUANT)
{
    SINT32 Code, Len;
    SINT32 Tmp = BsShow(pBs, 3);
    const SINT32 ModeLow[4]  = {VC1_1MVHPB, VC1_1MV, VC1_1MVHP, VC1_MIXMV};
    const SINT32 ModeHigh[5] = {VC1_1MV, VC1_MIXMV, VC1_1MVHP, VC1_1MVHPB};

    if (2 > Tmp)
    {
        Code = Tmp?2:3;
        Len = 3;
    }
    else if (4 > Tmp)
    {
        Code = 1;
        Len = 2;
    }
    else 
    {
        Code = 0;
        Len = 1;
    }

    BsSkip(pBs, Len);
    if (PQUANT > 12)
    {
        Code = ModeLow[Code];
    }
    else
    {
        Code = ModeHigh[Code];
    }

    return Code;
}

SINT32 VC1_DecMvmode2(BS *pBs, UINT8 PQUANT)
{
    SINT32 Code, Len;
    SINT32 Tmp = BsShow(pBs, 3);
    const SINT32 ModeLow[4]  = {VC1_1MVHPB, VC1_1MV, VC1_1MVHP, VC1_MIXMV};
    const SINT32 ModeHigh[4] = {VC1_1MV, VC1_MIXMV, VC1_1MVHP, VC1_1MVHPB};

    if (2 > Tmp)
    {
        Code = Tmp ? 2 : 3;
        Len = 3;
    }
    else if (4 > Tmp)
    {
        Code = 1;
        Len = 2;
    }
    else
    {
        Code = 0;
        Len = 1;
    }

    BsSkip(pBs, Len);
    if (PQUANT > 12)
    {
        Code = ModeLow[Code];
    }
    else
    {
        Code = ModeHigh[Code];
    }

    return Code;
}

SINT32 VC1_DecBfractionSMP(BS *pBs, SINT32 *pScaleFactor, UINT8 *pPTYPE)
{
    SINT32 Code, BfracIdx;
    SINT32 NumShortVLC[] = {1, 1, 2, 1, 3, 1, 2};
    SINT32 DenShortVLC[] = {2, 3, 3, 4, 4, 5, 5};
    SINT32 NumLongVLC[] = {3, 4, 1, 5, 1, 2, 3, 4, 5, 6, 1, 3, 5, 7};
    SINT32 DenLongVLC[] = {5, 5, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8};
    SINT32 Inverse[] = { 256, 128, 85, 64, 51, 43, 37, 32 };
    SINT32 Numerator, Denominator, FrameReciprocal, ScaleFactor;

    Code = BsShow(pBs, 3);
    if (Code < 7)
    {
        BsSkip(pBs, 3);
        BfracIdx    = Code;
        Numerator   = NumShortVLC[Code];
        Denominator = DenShortVLC[Code];
    }
    else
    {
        Code = BsGet(pBs, 7);
        if (0xf == (Code&0xf))
        {
            *pPTYPE = VC1_VFMW_BIPIC;
            return 22; //!!caution: the ref code don't recalc ScaleFactor here, just keep old value in memory. I don't know what will happen if we return -1.
        }
        BfracIdx    = (Code & 0xf) + 0x7;
        Numerator   = NumLongVLC[Code - 112];
        Denominator = DenLongVLC[Code - 112];
    }

    FrameReciprocal = Inverse[Denominator - 1];
    ScaleFactor   = Numerator * FrameReciprocal;
    *pScaleFactor = ScaleFactor;

    return BfracIdx;
}

SINT32 VC1_DecBfraction(BS *pBs, SINT32 *pScaleFactor)
{
    SINT32 Code, BfracIdx;
    SINT32 NumShortVLC[] = {1, 1, 2, 1, 3, 1, 2};
    SINT32 DenShortVLC[] = {2, 3, 3, 4, 4, 5, 5};
    SINT32 NumLongVLC[] = {3, 4, 1, 5, 1, 2, 3, 4, 5, 6, 1, 3, 5, 7};
    SINT32 DenLongVLC[] = {5, 5, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8};
    SINT32 Inverse[] = { 256, 128, 85, 64, 51, 43, 37, 32 };
    SINT32 Numerator, Denominator, FrameReciprocal, ScaleFactor;

    Code = BsShow(pBs, 3);
    if (Code < 7)
    {
        BsSkip(pBs, 3);
        BfracIdx    = Code;
        Numerator   = NumShortVLC[Code];
        Denominator = DenShortVLC[Code];
    }
    else
    {
        Code = BsGet(pBs, 7);
        #if 0
        // 20130822: TQE 无效代码
        if (0xe <= (Code&4))
        {
            //meet reserved code, nothing will be calced
            return 22;
        }
        #endif
        BfracIdx    = (Code & 0xf) + 0x7;
        Numerator   = NumLongVLC[Code - 112];
        Denominator = DenLongVLC[Code - 112];
    }

    FrameReciprocal = Inverse[Denominator - 1];
    ScaleFactor   = Numerator * FrameReciprocal;
    *pScaleFactor = ScaleFactor;

    return BfracIdx;
}


SINT32 VC1_VopDQuant(BS *pBs, UINT8 DQUANT, UINT8 PQUANT, VC1_VOPDQUANT_S *pVopDquant)
{
    if (2 == DQUANT)
    {
        pVopDquant->UseAltQp = 1;
        //!!caution, although protocol says here should be set default value to 0, but ref code set it to 1. we can only follow ref code.
        pVopDquant->DQUANTFRM = 1;
        pVopDquant->PQDIFF = BsGet(pBs, 3);
        if (7 == pVopDquant->PQDIFF)
        {
            pVopDquant->ABSPQ = BsGet(pBs, 5);
            pVopDquant->ALTPQUANT = pVopDquant->ABSPQ;
        }
        else
        {
            pVopDquant->ALTPQUANT = PQUANT + pVopDquant->PQDIFF + 1;
        }
        pVopDquant->QuantMode = VC1_QUANTMODEALLEDGES;
    }
    else
    {
        pVopDquant->DQUANTFRM = BsGet(pBs, 1);
        if (1 == pVopDquant->DQUANTFRM)
        {
            pVopDquant->DQPROFILE = BsGet(pBs, 2);
            if (VC1_ALLFOUREDGE == pVopDquant->DQPROFILE)
            {
                /* MB quantisation selection on all four edges */
                pVopDquant->QuantMode = VC1_QUANTMODEALLEDGES;
            }
            else if (VC1_SINGLEEDGE == pVopDquant->DQPROFILE)
            { 
                pVopDquant->DQSBEDGE = BsGet(pBs, 2);
                pVopDquant->QuantMode = (VC1_QUANTMODE)(pVopDquant->DQSBEDGE + VC1_QUANTMODELEFT);
            }
            else if (VC1_DOUBLEEDGE == pVopDquant->DQPROFILE)
            {
                pVopDquant->DQDBEDGE = BsGet(pBs, 2);
                pVopDquant->QuantMode = (VC1_QUANTMODE)(pVopDquant->DQDBEDGE + VC1_QUANTMODELEFTTOP);
            }
            else if (VC1_ALLMB == pVopDquant->DQPROFILE)
            {
                pVopDquant->DQBILEVEL = BsGet(pBs, 1);
                pVopDquant->QuantMode = (pVopDquant->DQBILEVEL) ? VC1_QUANTMODEMBDUAL : VC1_QUANTMODEMBANY;
            }
            else
            {
                pVopDquant->QuantMode = VC1_QUANTMODEDEFAULT;
            }

            if (!((VC1_ALLMB == pVopDquant->DQPROFILE)
                  && (0 == pVopDquant->DQBILEVEL)))
            {
            	pVopDquant->UseAltQp = 1;
                pVopDquant->PQDIFF = BsGet(pBs, 3);
                if (7 == pVopDquant->PQDIFF)
                {
                    pVopDquant->ABSPQ = BsGet(pBs, 5);
                    pVopDquant->ALTPQUANT = pVopDquant->ABSPQ;
                }
                else
                {
                    pVopDquant->ALTPQUANT = PQUANT + pVopDquant->PQDIFF + 1;
                }
            }
        }
    }

    return VC1_VFMW_TRUE;
}

#ifndef VFMW_BPD_H_SUPPORT
__inline VOID VC1_DecNorm2(BS *pBs, SINT32 MbNum, SINT8 *pElement)
{
    SINT32 i;
    SINT8 *pWt = pElement;

    if (MbNum & 1)
    {
        *pWt++ = BsGet(pBs, 1);
    }

    for (i = MbNum & 1; i < MbNum; i += 2)
    {
        if (BsGet(pBs, 1))
        {
            if (BsGet(pBs, 1))
            {
                *pWt = *(pWt + 1) = 1;
            }
            else
            {
                if (BsGet(pBs, 1))
                {
                    *pWt = 0;
                    *(pWt + 1) = 1;
                }
                else
                {
                    *pWt = 1;
                    *(pWt + 1) = 0;
                }
            }
        }
        else
        {
            *pWt = *(pWt + 1) = 0;
        }

        pWt += 2;
    }
}
#endif

SINT32 VC1_DecNormDiff6Tile (BS *pBs, SINT32 *pi6)
{
    SINT32 Invert = VC1_VFMW_FALSE;
    SINT32 iCode;
    SINT32 i6 = *pi6;

    // 4 stage decoding - read 1, 3, 1, 3 bits respectively
StartOfLocalFn6:

    // length 1 code
    if (BsGet(pBs, 1))
    {
        i6 = 0;
        goto EndOfLocalFn6;
    }

    iCode = BsGet(pBs, 3);
    if (iCode > 1)
    {
        // length 4 codes
        i6 = 1 << (iCode - 2);
        goto EndOfLocalFn6;
    }

    if (iCode == 1)
    {
        // length 5 codes
        if (BsGet(pBs, 1))
        {
            // complementary codes - send to start
            if (Invert)  // only one inversion possible
            {
                *pi6 = i6;
                return VC1_VFMW_FALSE;
            }

            Invert = VC1_VFMW_TRUE;
            goto StartOfLocalFn6;
        }
        else
        {
            // 3 on 3 off
            i6 = BsGet(pBs, 5);
            iCode = aCount[i6];
            if (iCode == 2)
            {
                i6 |= 32;
            }
            else if (iCode == 3)
            {
                ;
            }                      // do nothing
            else
            {
                *pi6 = i6;
                return VC1_VFMW_FALSE; // invalid symbol
            }

            goto EndOfLocalFn6;
        }
    }

    // length 8 codes
    iCode = BsGet(pBs, 4);
    if (iCode == 0xff)  // non-existent codeword
    {
        *pi6 = i6;
        return VC1_VFMW_FALSE;
    }

    i6 = a2On4Off[iCode];

EndOfLocalFn6:
    if (Invert)
    {
        i6 ^= 0x3f;
    }

    *pi6 = i6;
    return VC1_VFMW_TRUE;
}

#ifndef VFMW_BPD_H_SUPPORT
__inline SINT32 VC1_DecNorm6(BS *pBs, SINT32 MbWidth, SINT32 MbHeight, SINT8 *pElement)
{
    SINT32 i, j;
    SINT32 iStart = 0, jStart = 0;
    SINT8* pWt = pElement;
    SINT32 l, i6, tmp;
	
    if (((MbHeight % 3) == 0) && (MbWidth % 3))
    {
        // vertically oriented 2 x 3 tiles
        jStart = MbWidth & 1;
        for (i = 0; i < MbHeight; i += 3)
        {
            tmp = i * MbWidth;
            for (j = jStart; j < MbWidth; j += 2)
            {
                l = tmp + j;
                if (VC1_DecNormDiff6Tile (pBs, &i6) != VC1_VFMW_TRUE)
                {
                    return VC1_VFMW_FALSE;
                }

                *(pWt + l) = i6 & 1;
                i6 >>= 1;
                *(pWt + l + 1) = i6 & 1;
                i6 >>= 1;
                l += MbWidth;
                *(pWt + l) = i6 & 1;
                i6 >>= 1;
                *(pWt + l + 1) = i6 & 1;
                i6 >>= 1;
                l += MbWidth;
                *(pWt + l) = i6 & 1;
                i6 >>= 1;
                *(pWt + l + 1) = i6 & 1;
            }
        }
    }
    else
    {
        // horizontally oriented 3 x 2 tiles
        iStart = MbHeight & 1;
        jStart = (MbWidth % 3);
        for (i = iStart; i < (SINT32) MbHeight; i += 2)
        {
            tmp = i * MbWidth;
            for (j = jStart; j < (SINT32) MbWidth; j += 3)
            {
                l = tmp + j;
                if (VC1_DecNormDiff6Tile (pBs, &i6) != VC1_VFMW_TRUE)
                {
                    return VC1_VFMW_FALSE;
                }

                //dprint(PRN_PIC, "bit pos  :%4d    :0x%8x  : %4d\n", l, i6, pBs->TotalPos-tmp);

                *(pWt + l) = i6 & 1;
                i6 >>= 1;
                *(pWt + l + 1) = i6 & 1;
                i6 >>= 1;
                *(pWt + l + 2) = i6 & 1;
                i6 >>= 1;
                l += MbWidth;
                *(pWt + l) = i6 & 1;
                i6 >>= 1;
                *(pWt + l + 1) = i6 & 1;
                i6 >>= 1;
                *(pWt + l + 2) = i6 & 1;
            }
        }
    }

    // left column(s)
    for (j = 0; j < jStart; j++)
    {
        if (BsGet(pBs, 1))
        {
            for (i = 0; i < (SINT32) MbHeight; i++)
            {
                *(pWt + i * MbWidth + j) = BsGet(pBs, 1);
            }
        }
        else
        {
            for (i = 0; i < (SINT32) MbHeight; i++)
            {
                *(pWt + i * MbWidth + j) = 0;
            }
        }
    }

    // top row
    if (iStart)
    {
        if (BsGet(pBs, 1))
        {
            for (j = jStart; j < (SINT32) MbWidth; j++)
            {
                *(pWt + j) = BsGet(pBs, 1);
            }
        }
        else
        {
            for (j = jStart; j < (SINT32) MbWidth; j++)
            {
                *(pWt + j) = 0;
            }
        }
    }

    return VC1_VFMW_TRUE;
}
#endif

#ifndef VFMW_BPD_H_SUPPORT
SINT32 VC1_BitPlane(BS *pBs, VC1_VFMWCODECINF_S *pCodecInfo, SINT32 MbWidth, SINT32 MbHeight, VC1_BITPLANE_S *pSyn)
{
    SINT32 Invert, Imode, Len;
    SINT32 MbNum = MbWidth * MbHeight, i, j;
    SINT8 *pWt  = pSyn->pElement;
    SINT32 bDiff = 0;
	SINT32 iPred = 0;

    Invert = BsGet(pBs, 1);

   //get mode
    Imode = BsShow(pBs, 4);
    if (2 > Imode) //000x
    {
        Imode = (Imode == 0 ? VC1_RAW : VC1_DIFF6);
        Len = 4;
    }
    else if (4 > Imode) //001x
    {
        Imode = VC1_DIFF2;
        Len = 3;
    }
    else if (6 > Imode) //010x
    {
        Imode = VC1_ROWSKIP;
        Len = 3;
    }
    else if (8 > Imode) //011x
    {
        Imode = VC1_COLSKIP;
        Len = 3;
    }
    else if (12 > Imode) // 10xx
    {
        Imode = VC1_NORM2;
        Len = 2;
    }
    else // 11xx
    {
        Imode = VC1_NORM6;
        Len = 2;
    }

    BsSkip(pBs, Len);
    pSyn->Invert = Invert;
    pSyn->Imode = Imode;

    //get data
    pWt = pSyn->pElement;
    switch (Imode)
    {
    case VC1_RAW:

        //! in this mode, the syntax should be decoded at mb level,
        // so we do nothing here, just pass the mode to VDH
        if (Invert)
        {
            break;
		}
		else
		{
            return Imode;
		}
        
    case VC1_NORM2:
        VC1_DecNorm2(pBs, MbWidth * MbHeight, pSyn->pElement);
        break;
    case VC1_DIFF2:
        bDiff = 1;
        VC1_DecNorm2(pBs, MbWidth * MbHeight, pSyn->pElement);
        break;
    case VC1_NORM6:
        VC1_DecNorm6(pBs, MbWidth, MbHeight, pSyn->pElement);
        break;
    case VC1_DIFF6:
        bDiff = 1;
        VC1_DecNorm6(pBs, MbWidth, MbHeight, pSyn->pElement);
        break;
    case VC1_ROWSKIP:
        for (i = 0; i < MbHeight; i++)
        {
            if (BsGet(pBs, 1))
            {
                for (j = 0; j < MbWidth; j++)
                {
                    *(pWt + i * MbWidth + j) = BsGet(pBs, 1);
                }
            }
            else
            {
                for (j = 0; j < MbWidth; j++)
                {
                    *(pWt + i * MbWidth + j) = 0;
                }
            }
        }

        break;
    default:

        //COL SKIP
        for (j = 0; j < MbWidth; j++)
        {
            if (BsGet(pBs, 1))
            {
                for (i = 0; i < MbHeight; i++)
                {
                    *(pWt + i * MbWidth + j) = BsGet(pBs, 1);
                }
            }
            else
            {
                for (i = 0; i < MbHeight; i++)
                {
                    *(pWt + i * MbWidth + j) = 0;
                }
            }
        }

        break;
    }

    //diff process
    if (bDiff)
    {
        pWt = pSyn->pElement;

        // undo differential coding
        for (i = 0; i < MbHeight; i++)
        {
            for (j = 0; j < MbWidth; j++)
            {
                if (i + j == 0)
                {
                    iPred = Invert;
                }
                else if (i == 0)
                {
                    iPred = *(pWt - 1);
                }
                else if (j == 0)
                {
                    iPred = *(pWt - MbWidth);
                }
                else
                {
                    if (*(pWt - 1) == *(pWt - MbWidth))
                    {
                        iPred = *(pWt - 1);
                    }
                    else
                    {
                        iPred = Invert;
                    }
                }

                *pWt ^= iPred;
                pWt++;
            }
        }
    }
    else
    {
        // conditional inversion - only for nondifferential coding
        if (Invert)
        {
            for (i = 0; i < MbNum; i++)
            {
                *(pWt + i) ^= 1;
            }
        }
    }
    return Imode;
}
#endif
SINT32 VC1_Vfmw_ParseSMPIPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_SMPSEQSYNTAX_S *pSeqSyn = &pSyntax->SMPSeqSyntax;
    VC1_SMPPICSYNTAX_S *pPicSyn = &pSyntax->SMPPicSyntax;

    //decode BF
    pPicSyn->BF = BsGet(pBs, 7);
    pPicSyn->PQINDEX = BsGet(pBs, 5);
	if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pSeqSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pSeqSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
           pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->EXTENDED_MV)
    {
        pPicSyn->MVRANGE = VC1_DecMvrange(pBs);
    }
    else
    {
        pPicSyn->MVRANGE = 0;
    }
    if ((VC1_VFMW_BPIC != pPicSyn->PTYPE)&&(VC1_VFMW_BIPIC != pPicSyn->PTYPE))
    {
        if (1 == pSeqSyn->MULTIRES)
        {
            pPicSyn->RESPIC = BsGet(pBs, 2);
        }
    }
    //dprint(PRN_PIC, "Check Pos 2: %d\n", BsPos(pBs));
    VC1_SetCurPicResolutionInfo(pCodecInf, pPicSyn->RESPIC);

    pPicSyn->TRANSACFRM  = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSACFRM2 = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);
    
    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseSMPPPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_SMPSEQSYNTAX_S *pSeqSyn = &pSyntax->SMPSeqSyntax;
    VC1_SMPPICSYNTAX_S *pPicSyn = &pSyntax->SMPPicSyntax;
#ifndef VFMW_BPD_H_SUPPORT    
    SINT32 MbNum = pCodecInf->MbWidth * pCodecInf->MbHeight;
#endif
    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pSeqSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pSeqSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
           pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->EXTENDED_MV)
    {
        pPicSyn->MVRANGE = VC1_DecMvrange(pBs);
    }
    else
    {	 
        pPicSyn->MVRANGE = 0;
    }

    if (1 == pSeqSyn->MULTIRES)
    {
        pPicSyn->RESPIC = BsGet(pBs, 2);
    }
    VC1_SetCurPicResolutionInfo(pCodecInf, pPicSyn->RESPIC);

    dprint(PRN_PIC, "Check Pos 2: %d\n", BsPos(pBs));
    //MVMODE
    pPicSyn->MVMODE = VC1_DecMvmodeProgrP(pBs, (UINT8)pPicSyn->PQUANT);
    if (VC1_INTCMP == pPicSyn->MVMODE)
    {
        pPicSyn->MVMODE2  = VC1_DecMvmode2(pBs, (UINT8)pPicSyn->PQUANT);
        pPicSyn->LUMSCALE = BsGet(pBs, 6);
        pPicSyn->LUMSHIFT = BsGet(pBs, 6);
    }
#ifdef VFMW_BPD_H_SUPPORT
    if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
    {
        dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
        return VC1_VFMW_FALSE;
    }
#else
    if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    {
        if ((VC1_MIXMV == pPicSyn->MVMODE)
            || ((VC1_INTCMP == pPicSyn->MVMODE) && (VC1_MIXMV == pPicSyn->MVMODE2)))
        {
            pPicSyn->MVTYPEMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->CurPicMbWidth, pCodecInf->CurPicMbHeight, &pPicSyn->SKIPMB);
            if (VC1_RAW != pPicSyn->MVTYPEMBMode)
            {
                memcpy(pCodecInf->MVTYPEMB, pCodecInf->SKIPMB, MbNum);
            }
        }
        else
        {
            pPicSyn->MVTYPEMBMode = VC1_DECIDED;
            memset(pCodecInf->MVTYPEMB, 0, MbNum); 
        }

        pPicSyn->SKIPMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->CurPicMbWidth, pCodecInf->CurPicMbHeight, &pPicSyn->SKIPMB);
    }
    else
    {
        if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
        {
            dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
            return VC1_VFMW_FALSE;
        }
    }
#endif
    pPicSyn->MVTAB  = BsGet(pBs, 2);
    pPicSyn->CBPTAB = BsGet(pBs, 2);

    //vopdquant
    if (0 != pSeqSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pSeqSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }
    dprint(PRN_PIC, "Check Pos 3: %d\n", BsPos(pBs));

    if (1 == pSeqSyn->VSTRANSFORM)
    {
        pPicSyn->TTMBF = BsGet(pBs, 1);
        if (1 == pPicSyn->TTMBF)
        {
            pPicSyn->TTFRM = BsGet(pBs, 2);
        }
    }

    pPicSyn->TRANSACFRM = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);
    
    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseMPBPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_SMPSEQSYNTAX_S *pSeqSyn = &pSyntax->SMPSeqSyntax;
    VC1_SMPPICSYNTAX_S *pPicSyn = &pSyntax->SMPPicSyntax;

    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pSeqSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pSeqSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->EXTENDED_MV)
    {
        pPicSyn->MVRANGE = VC1_DecMvrange(pBs);
    }
    else
    {
        pPicSyn->MVRANGE = 0;
    }

    //MVMODE
    pPicSyn->MVMODE = (0 == BsGet(pBs, 1))? VC1_1MVHPB : VC1_1MV;
#ifdef VFMW_BPD_H_SUPPORT
    if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
    {
        dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
        return VC1_VFMW_FALSE;
    }
#else
    if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    {
        pPicSyn->DIRECTMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->CurPicMbWidth, pCodecInf->CurPicMbHeight, &pPicSyn->DIRECTMB);
        pPicSyn->SKIPMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->CurPicMbWidth, pCodecInf->CurPicMbHeight, &pPicSyn->SKIPMB);
    }
    else
    {
        if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
        {
            dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
            return VC1_VFMW_FALSE;
        }
    }
#endif
    pPicSyn->MVTAB  = BsGet(pBs, 2);
    pPicSyn->CBPTAB = BsGet(pBs, 2);

    //vopdquant
    if (0 != pSeqSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pSeqSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }

    if (1 == pSeqSyn->VSTRANSFORM)
    {
        pPicSyn->TTMBF = BsGet(pBs, 1);
        if (1 == pPicSyn->TTMBF)
        {
            pPicSyn->TTFRM = BsGet(pBs, 2);
        }
    }

    pPicSyn->TRANSACFRM = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);

    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseSMPPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_SMPSEQSYNTAX_S *pSeqSyn = &pSyntax->SMPSeqSyntax;
    VC1_SMPPICSYNTAX_S *pPicSyn = &pSyntax->SMPPicSyntax;
    SINT32 Ret;
	SINT32 Len = 0;
	UINT8  RESPIC = pPicSyn->RESPIC;
    VC1_SetCurPicResolutionInfo(pCodecInf, pPicSyn->RESPIC); //reset to the full all
    
    if (pBs->BsLen <= 1)
    {
        pPicSyn->PTYPE = VC1_VFMW_SKPIC;
        pCodecInf->PicCodingType = pPicSyn->PTYPE;
        return VC1_VFMW_TRUE;
    }

    memset(pPicSyn, 0, sizeof(VC1_SMPPICSYNTAX_S));
#ifndef VFMW_BPD_H_SUPPORT    
	pSyntax->SMPPicSyntax.DIRECTMB.pElement = pCodecInf->DIRECTMB;
	pSyntax->SMPPicSyntax.MVTYPEMB.pElement = pCodecInf->MVTYPEMB;
	pSyntax->SMPPicSyntax.SKIPMB.pElement = pCodecInf->SKIPMB;
#endif    
	pPicSyn->RESPIC = RESPIC;
    memset(pCodecInf->SlcStr, 0, sizeof(pCodecInf->SlcStr));
	if (VC1_STOPPIC  == pCodecInf->PicCnt)
	{
		pCodecInf->PicCnt = pCodecInf->PicCnt;
	}

    dprint(PRN_PIC, "\n======PicNum  :%6d=========\n", pCodecInf->PicCnt);

    pPicSyn->HdrLen = BsPos(pBs);
    if (pSeqSyn->FINTERPFLAG)
    {
        pPicSyn->INTERPFRM = BsGet(pBs, 1);
    }

    dprint(PRN_PIC, "INTERPFRM  :%#x\n", pPicSyn->INTERPFRM);

    pPicSyn->FRMCNT = BsGet(pBs, 2);
    if (pSeqSyn->RANGERED)
    {
        pPicSyn->RANGEREDFRM = BsGet(pBs, 1);
    }
	
    //decoding PTYPE
    if (0 == pSeqSyn->MAXBFRAMES)
    {
        pPicSyn->PTYPE = (0 == BsGet(pBs, 1) ? VC1_VFMW_IPIC : VC1_VFMW_PPIC);
    }
    else
    {
    
        if (1 == BsGet(pBs, 1))
        {
            pPicSyn->PTYPE = VC1_VFMW_PPIC;
        }
        else
        {
            pPicSyn->PTYPE = (1 == BsGet(pBs, 1) ? VC1_VFMW_IPIC : VC1_VFMW_BPIC);
        }

        if (VC1_VFMW_BPIC == pPicSyn->PTYPE)
        {
            // decode fraction from BFRACTION
            pPicSyn->BFRACTION = VC1_DecBfractionSMP(pBs, &pPicSyn->ScaleFactor, &pPicSyn->PTYPE);
			if (pPicSyn->BFRACTION == 22)
			{
				pPicSyn->BFRACTION = pPicSyn->BFRACTION;
			}
			if (21 == pPicSyn->BFRACTION)
			{
                return VC1_VFMW_FALSE;
		    }
        }
    }

    pCodecInf->PicCodingType = pPicSyn->PTYPE;
    pCodecInf->PicStructure = VC1_VFMW_PROGRESSIVE;
    switch (pPicSyn->PTYPE)
    {
    case VC1_VFMW_IPIC:
        Ret = VC1_Vfmw_ParseSMPIPicHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_PPIC:
        Ret = VC1_Vfmw_ParseSMPPPicHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_BPIC:
        if (pCodecInf->PreParseInfo.SMPSeqSyntax.PROFILE == 1)//main profile
        {
            Ret = VC1_Vfmw_ParseMPBPicHdr(pBs, pCodecInf, pSyntax);
			break;
		}
        else
        {
            return VC1_VFMW_FALSE;
		}
    case VC1_VFMW_BIPIC:
        if (pCodecInf->PreParseInfo.SMPSeqSyntax.PROFILE == 1)//main profile
        {
            Ret = VC1_Vfmw_ParseSMPIPicHdr(pBs, pCodecInf, pSyntax);
            break;
        }
		else
		{
            return VC1_VFMW_FALSE;
		}
    default:
        return VC1_VFMW_FALSE;
    }

    pPicSyn->HdrLen = BsPos(pBs) - pPicSyn->HdrLen;
//    Len = pCodecInf->pBsPack->Length * 8 - BsPos(pBs);
    Len = pCodecInf->stCurPacket.BsLength[0] * 8 - BsPos(pBs);
	if (Len <= 0)
	{
        dprint(PRN_ERROR, "After VC1_Vfmw_ParseSMPPicHdr BS Len <= 0 err!\n");
        return VC1_VFMW_FALSE;
    }

    //if (VC1_VFMW_SKPIC !=pSyntax->SMPPicSyntax.PTYPE)
    {
        //dprint(PRN_PIC, "TRANSACFRM :%#x\n", pPicSyn->TRANSACFRM);
    }

    //dprint(PRN_PIC, "Pic Hdr Len -->:0x%8x, Next 16 bit: 0x%2x\n", pPicSyn->HdrLen, BsShow(pBs, 16));
    return Ret;
}

SINT32 VC1_Vfmw_ParseAdvSeqHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    SINT32 i;

    memset(pSeqSyn, 0, sizeof(VC1_ADVSEQSYNTAX_S));

    pSeqSyn->HdrLen = BsPos(pBs);
    BsGet(pBs, 2);
    pSeqSyn->PROFILE = VC1_VFMW_ADVANCED;
    pSeqSyn->LEVEL = (UINT8)BsGet(pBs, 3);
    pSeqSyn->CHROMFORMAT = (UINT8)BsGet(pBs, 2);
    pSeqSyn->FRMRTQ_POSTPROC = (UINT8)BsGet(pBs, 3);
    pSeqSyn->BITRTQ_POSTPROC = (UINT8)BsGet(pBs, 5);
    pSeqSyn->POSTPROCFLAG = (UINT8)BsGet(pBs, 1);
    pSeqSyn->MAX_CODED_WIDTH  = 2 * (UINT16)BsGet(pBs, 12) + 2;
    pSeqSyn->MAX_CODED_HEIGHT = 2 * (UINT16)BsGet(pBs, 12) + 2;
    //dprint(PRN_SEQ, "\n---Seq inf: %4d(w) x %4d(h)---\n", pSeqSyn->MAX_CODED_WIDTH, pSeqSyn->MAX_CODED_HEIGHT);
    pSeqSyn->PULLDOWN    = (UINT8)BsGet(pBs, 1);
    pSeqSyn->INTERLACE   = (UINT8)BsGet(pBs, 1);
    pSeqSyn->TFCNTRFLAG  = (UINT8)BsGet(pBs, 1);
    pSeqSyn->FINTERPFLAG = (UINT8)BsGet(pBs, 1);
    BsSkip(pBs, 2); //reserved
    pSeqSyn->DISPLAY_EXT = (UINT8)BsGet(pBs, 1);

    //display ext
    if (1 == pSeqSyn->DISPLAY_EXT)
    {
        pSeqSyn->DISP_HORIZ_SIZE = (UINT16)BsGet(pBs, 14) + 1;
        pSeqSyn->DISP_VERT_SIZE = (UINT16)BsGet(pBs, 14) + 1;
        pSeqSyn->ASPECT_RATIO_FLAG = (UINT8)BsGet(pBs, 1);
        if (1 == pSeqSyn->ASPECT_RATIO_FLAG)
        {
            pSeqSyn->ASPECT_RATIO = (UINT8)BsGet(pBs, 4);
            if (15 == pSeqSyn->ASPECT_RATIO)
            {
                pSeqSyn->ASPECT_HORIZ_SIZE = (UINT8)BsGet(pBs, 8);
                pSeqSyn->ASPECT_VERT_SIZE = (UINT8)BsGet(pBs, 8);
            }
        }

    pSeqSyn->FRAMERATE_FLAG = (UINT8)BsGet(pBs, 1);

    //frame rate
    if (1 == pSeqSyn->FRAMERATE_FLAG)
    {
        pSeqSyn->FRAMERATEIND = (UINT8)BsGet(pBs, 1);
        if (0 == pSeqSyn->FRAMERATEIND)
        {
            pSeqSyn->FRAMERATENR = (UINT8)BsGet(pBs, 8);
            pSeqSyn->FRAMERATEDR = (UINT8)BsGet(pBs, 4);
        }
        else
        {
            pSeqSyn->FRAMERATEXP = (UINT16)BsGet(pBs, 16);
        }
    }

    pSeqSyn->COLOR_FORMAT_FLAG = (UINT8)BsGet(pBs, 1);

    //color format
    if (1 == pSeqSyn->COLOR_FORMAT_FLAG)
    {
        pSeqSyn->COLOR_PRIM = (UINT8)BsGet(pBs, 8);
        pSeqSyn->TRANSFER_CHAR = (UINT8)BsGet(pBs, 8);
        pSeqSyn->MATRIX_COEF = (UINT8)BsGet(pBs, 8);
		}
    }
    else
    {
        pSeqSyn->DISP_HORIZ_SIZE = pSeqSyn->MAX_CODED_WIDTH;
        pSeqSyn->DISP_VERT_SIZE = pSeqSyn->MAX_CODED_HEIGHT;
    }

    //hrd_param
    pSeqSyn->HRD_PARAM_FLAG = (UINT8)BsGet(pBs, 1);
    if (1 == pSeqSyn->HRD_PARAM_FLAG)
    {
        pSeqSyn->HRD_NUM_LEAKY_BUCKETS = (UINT8)BsGet(pBs, 5);
        if (pSeqSyn->HRD_NUM_LEAKY_BUCKETS >= 32)
        {
            return VC1_VFMW_FALSE;
		}
        pSeqSyn->BIT_RATE_EXPONENT = (UINT8)BsGet(pBs, 4);
        pSeqSyn->BUFFER_SIZE_EXPONENT = (UINT8)BsGet(pBs, 4);
        for (i = 0; i < pSeqSyn->HRD_NUM_LEAKY_BUCKETS; i++)
        {
            pSeqSyn->HRD_RATE[i]   = (UINT16)BsGet(pBs, 16);
            pSeqSyn->HRD_BUFFER[i] = (UINT16)BsGet(pBs, 16);
        }
    }

    pSeqSyn->HdrLen = BsPos(pBs) - pSeqSyn->HdrLen;
    //dprint(PRN_SEQ, "Seq Hdr Len -->:0x%8x\n", pSeqSyn->HdrLen);
    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseAdvEntptHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;

    memset(pEntSyn, 0, sizeof(VC1_ADVENTSYNTAX_S));

    pEntSyn->HdrLen = BsPos(pBs);
    pEntSyn->BROKEN_LINK  = (UINT8)BsGet(pBs, 1);
    pEntSyn->CLOSED_ENTRY = (UINT8)BsGet(pBs, 1);
    pEntSyn->PANSCAN_FLAG = (UINT8)BsGet(pBs, 1);
    pEntSyn->REFDIST_FLAG = (UINT8)BsGet(pBs, 1);
    pEntSyn->LOOPFILTER = (UINT8)BsGet(pBs, 1);
    pEntSyn->FASTUVMC = (UINT8)BsGet(pBs, 1);
    pEntSyn->EXTENDED_MV = (UINT8)BsGet(pBs, 1);
    pEntSyn->DQUANT = (UINT8)BsGet(pBs, 2);
    pEntSyn->VSTRANSFORM = (UINT8)BsGet(pBs, 1);
    pEntSyn->OVERLAP   = (UINT8)BsGet(pBs, 1);
    pEntSyn->QUANTIZER = (UINT8)BsGet(pBs, 2);

    //hrd fullness
    if (1 == pSeqSyn->HRD_PARAM_FLAG)
    {
        SINT32 i;
        for (i = 0; i < pSeqSyn->HRD_NUM_LEAKY_BUCKETS; i++)
        {
            pEntSyn->HRD_FULLNESS[i] = (UINT8)BsGet(pBs, 8);
        }
    }

    pEntSyn->CODED_SIZE_FLAG = (UINT8)BsGet(pBs, 1);
    if (1 == pEntSyn->CODED_SIZE_FLAG)
    {
        pEntSyn->CODED_WIDTH  = (UINT16)(BsGet(pBs, 12) * 2 + 2);        
        pEntSyn->CODED_HEIGHT = (UINT16)(BsGet(pBs, 12) * 2 + 2);
    }

    if((pEntSyn->CODED_WIDTH > pSeqSyn->MAX_CODED_WIDTH)||(pEntSyn->CODED_WIDTH < 16))
    {
        pEntSyn->CODED_WIDTH = pSeqSyn->MAX_CODED_WIDTH;
    }
    if((pEntSyn->CODED_HEIGHT > pSeqSyn->MAX_CODED_HEIGHT)||(pEntSyn->CODED_HEIGHT< 16))
    {
        pEntSyn->CODED_HEIGHT = pSeqSyn->MAX_CODED_HEIGHT;
    }


    if (1 == pEntSyn->EXTENDED_MV)
    {
        pEntSyn->EXTENDED_DMV = (UINT8)BsGet(pBs, 1);
    }

    pEntSyn->RANGE_MAPY_FLAG = (UINT8)BsGet(pBs, 1);
    if (1 == pEntSyn->RANGE_MAPY_FLAG)
    {
        pEntSyn->RANGE_MAPY = (UINT8)BsGet(pBs, 3);
    }

    pEntSyn->RANGE_MAPUV_FLAG = (UINT8)BsGet(pBs, 1);
    if (1 == pEntSyn->RANGE_MAPUV_FLAG)
    {
        pEntSyn->RANGE_MAPUV = (UINT8)BsGet(pBs, 3);
    }

    pEntSyn->HdrLen = BsPos(pBs) - pEntSyn->HdrLen;
    //dprint(PRN_SEQ, "Ent Hdr Len -->:0x%8x\n", pEntSyn->HdrLen);
    return VC1_VFMW_TRUE;
}

__inline SINT32 VC1_DecFcm(BS *pBs)
{
    SINT32 Code;

    Code = BsShow(pBs, 2);
    if (Code < 2)
    {
        Code = VC1_VFMW_PROGRESSIVE;
        BsSkip(pBs, 1);
    }
    else
    {
        BsSkip(pBs, 2);
    }

    return Code;
}

__inline SINT32 VC1_DecAdvPtype(BS *pBs)
{
    SINT32 Code, Len;

    Code = BsShow(pBs, 4);
    if (Code < 8)
    {
        Code = VC1_VFMW_PPIC;
        Len = 1;
    }
    else if (Code < 0xc)
    {
        Code = VC1_VFMW_BPIC;
        Len = 2;
    }
    else if (Code < 0xe)
    {
        Code = VC1_VFMW_IPIC;
        Len = 3;
    }
    else
    {
        Code = (0xe == Code) ? VC1_VFMW_BIPIC : VC1_VFMW_SKPIC;
        Len = 4;
    }

    BsSkip(pBs, Len);
    return Code;
}

SINT32 VC1_Vfmw_ParseAdvIPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;
    //SINT32 i, MbNum = pCodecInf->MbWidth * pCodecInf->MbHeight;

    pPicSyn->RNDCTRL = BsGet(pBs, 1);
    if (1 == pSeqSyn->INTERLACE)
    {
        pPicSyn->UVSAMP = BsGet(pBs, 1);
    }

    if (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM)
    {
        if (1 == pSeqSyn->FINTERPFLAG)
        {
            pPicSyn->INTERPFRM = BsGet(pBs, 1);
        }
    }

    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pEntSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pEntSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->POSTPROCFLAG)
    {
        pPicSyn->POSTPROC = BsGet(pBs, 2);
    }
    
#ifdef VFMW_BPD_H_SUPPORT
    if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
    {
        dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
        return VC1_VFMW_FALSE;
    }
#else
    if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    {
        if (VC1_VFMW_FRAMEINTER == pPicSyn->FCM)
        {
            pPicSyn->FIELDTXMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, pCodecInf->MbHeight, &pPicSyn->FIELDTX);
        }
        else
        {
            pPicSyn->FIELDTXMode = pPicSyn->FIELDTX.Imode = VC1_RAW;
        }

        pPicSyn->ACPREDMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, pCodecInf->MbHeight, &pPicSyn->ACPRED);
        if ((1 == pEntSyn->OVERLAP) && (8 >= pPicSyn->PQUANT))
        {
            pPicSyn->CONDOVER = (BsShow(pBs, 1) == 0 ? BsGet(pBs, 1) : BsGet(pBs, 2));
            if (1 == pPicSyn->CONDOVER)
            {
                return VC1_VFMW_FALSE;
            }
            if (3 == pPicSyn->CONDOVER)
            {
                pPicSyn->OVERFLAGSMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, pCodecInf->MbHeight, &pPicSyn->OVERFLAGS);
            }
        }
    }
    else
    {
        if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
        {
            dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
            return VC1_VFMW_FALSE;
        }
    }
#endif

    pPicSyn->TRANSACFRM  = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSACFRM2 = VC1_DecTransacfrm(pBs);
        
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);

    //vopdquant
    if (0 != pEntSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pEntSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }

    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseAdvPPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;
    //SINT32 i;
#ifndef VFMW_BPD_H_SUPPORT    
    SINT32 MbNum = pCodecInf->MbWidth * pCodecInf->MbHeight;
#endif
    pPicSyn->RNDCTRL = BsGet(pBs, 1);
    if ((1 == pSeqSyn->INTERLACE) || (VC1_VFMW_FRAMEINTER == pPicSyn->FCM))
    {
        pPicSyn->UVSAMP = BsGet(pBs, 1);
    }

    if ((1 == pSeqSyn->FINTERPFLAG) && (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM))
    {
        pPicSyn->INTERPFRM = BsGet(pBs, 1);
    }

    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pEntSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pEntSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->POSTPROCFLAG)
    {
        pPicSyn->POSTPROC = BsGet(pBs, 2);
    }

    if (1 == pEntSyn->EXTENDED_MV)
    {
        pPicSyn->MVRANGE = VC1_DecMvrange(pBs);
    }

    if (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM)
    {
        //progressive
        //mvmode
        pPicSyn->MVMODE = VC1_DecMvmodeProgrP(pBs, (UINT8)pPicSyn->PQUANT);
        if (VC1_INTCMP == pPicSyn->MVMODE)
        {
            pPicSyn->MVMODE2  = VC1_DecMvmode2(pBs, (UINT8)pPicSyn->PQUANT);
            pPicSyn->LUMSCALE = BsGet(pBs, 6);
            pPicSyn->LUMSHIFT = BsGet(pBs, 6);
        }
     #ifndef VFMW_BPD_H_SUPPORT   
    	if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    	{
            if ((VC1_MIXMV == pPicSyn->MVMODE)
                || ((VC1_INTCMP == pPicSyn->MVMODE) && (VC1_MIXMV == pPicSyn->MVMODE2)))
            {
                pPicSyn->MVTYPEMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, pCodecInf->MbHeight, &pPicSyn->MVTYPEMB);
            }
            else
            {
                pPicSyn->MVTYPEMBMode = VC1_DECIDED;
                memset(pCodecInf->MVTYPEMB, 0, MbNum); 
            }
		}
     #endif   
    }
    else
    {
        //frame interlace
        if (1 == pEntSyn->EXTENDED_DMV)
        {
            pPicSyn->DMVRANGE = VC1_DecMvrange(pBs);
        }
        else
        {
            pPicSyn->DMVRANGE = 0;
        }

        pPicSyn->QMVSWITCH = BsGet(pBs, 1);
        pPicSyn->INTCOMP = BsGet(pBs, 1);
        if (1 == pPicSyn->INTCOMP)
        {
            pPicSyn->LUMSCALE = BsGet(pBs, 6);
            pPicSyn->LUMSHIFT = BsGet(pBs, 6);
        }
		pPicSyn->MVTYPEMBMode = VC1_RAW;
    }
#ifdef VFMW_BPD_H_SUPPORT
    if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
    {
        dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
        return VC1_VFMW_FALSE;
    }
#else
    if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    {
        pPicSyn->SKIPMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, pCodecInf->MbHeight, &pPicSyn->SKIPMB);
    }
    else
    {
        if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
        {
            dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
            return VC1_VFMW_FALSE;
        }
    }
#endif
    if (VC1_VFMW_FRAMEINTER == pPicSyn->FCM)
    {
        pPicSyn->MBMODETAB = BsGet(pBs, 2);
    }

    pPicSyn->MVTAB  = BsGet(pBs, 2);
    pPicSyn->CBPTAB = (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM) ? BsGet(pBs, 2) : BsGet(pBs, 3);
    if (VC1_VFMW_FRAMEINTER == pPicSyn->FCM)
    {
        pPicSyn->BMVBPTAB = BsGet(pBs, 2);
        pPicSyn->QMVBPTAB = (1 == pPicSyn->QMVSWITCH) ? BsGet (pBs, 2) : 0;
    }

    //vopdquant
    if (0 != pEntSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pEntSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }

    if (1 == pEntSyn->VSTRANSFORM)
    {
        pPicSyn->TTMBF = BsGet(pBs, 1);
        if (1 == pPicSyn->TTMBF)
        {
            pPicSyn->TTFRM = BsGet(pBs, 2);
        }
    }

    pPicSyn->TRANSACFRM = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);
    
    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseAdvBPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;

    pPicSyn->RNDCTRL = BsGet(pBs, 1);
    if ((1 == pSeqSyn->INTERLACE) || (VC1_VFMW_FRAMEINTER == pPicSyn->FCM))
    {
        pPicSyn->UVSAMP = BsGet(pBs, 1);
    }

    if ((1 == pSeqSyn->FINTERPFLAG) && (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM))
    {
        pPicSyn->INTERPFRM = BsGet(pBs, 1);
    }

    if (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM)
	{
		// decode fraction from BFRACTION in progressive
		pPicSyn->BFRACTION = VC1_DecBfraction(pBs, &pPicSyn->ScaleFactor);
		if (21 == pPicSyn->BFRACTION)
		{
            return VC1_VFMW_FALSE;
		}
	}

    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pEntSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pEntSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
           pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->POSTPROCFLAG)
    {
        pPicSyn->POSTPROC = BsGet(pBs, 2);
    }

    if (VC1_VFMW_FRAMEINTER == pPicSyn->FCM)
    {
        // decode fraction from BFRACTION in frame interlace
        pPicSyn->BFRACTION = VC1_DecBfraction(pBs, &pPicSyn->ScaleFactor);
    }

    if (1 == pEntSyn->EXTENDED_MV)
    {
        pPicSyn->MVRANGE = VC1_DecMvrange(pBs);
    }

    if (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM)
    {
        //progressive
        //mvmode
        pPicSyn->MVMODE = (0 == BsGet(pBs, 1))? VC1_1MVHPB : VC1_1MV;
    }
    else
    {
        //dmvrange
        if (1 == pEntSyn->EXTENDED_DMV)
        {
            pPicSyn->DMVRANGE = VC1_DecMvrange(pBs);
        }

        //intcomp
        pPicSyn->INTCOMP = BsGet (pBs, 1);
    }
#ifdef VFMW_BPD_H_SUPPORT
    if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
    {
        dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
        return VC1_VFMW_FALSE;
    }
#else
    if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    {
        pPicSyn->DIRECTMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, pCodecInf->MbHeight, &pPicSyn->DIRECTMB);
        pPicSyn->SKIPMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, pCodecInf->MbHeight, &pPicSyn->SKIPMB);
    }
    else
    {
        if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
        {
            dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
            return VC1_VFMW_FALSE;
        }
    }
#endif
    if (VC1_VFMW_FRAMEINTER == pPicSyn->FCM)
    {
        pPicSyn->MBMODETAB = BsGet(pBs, 2);
    }

    pPicSyn->MVTAB  = BsGet(pBs, 2);
    pPicSyn->CBPTAB = (VC1_VFMW_PROGRESSIVE == pPicSyn->FCM) ? BsGet(pBs, 2) : BsGet(pBs, 3);

    if (VC1_VFMW_FRAMEINTER == pPicSyn->FCM)
    {
        pPicSyn->BMVBPTAB = BsGet(pBs, 2);
        pPicSyn->QMVBPTAB = BsGet (pBs, 2);
    }

    //vopdquant
    if (0 != pEntSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pEntSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }

    if (1 == pEntSyn->VSTRANSFORM)
    {
        pPicSyn->TTMBF = BsGet(pBs, 1);
        if (1 == pPicSyn->TTMBF)
        {
            pPicSyn->TTFRM = BsGet(pBs, 2);
        }
    }

    pPicSyn->TRANSACFRM = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);

    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseAdvFramePicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;
    SINT32 i, Ret;

    pPicSyn->PTYPE = VC1_DecAdvPtype(pBs);
	pCodecInf->PicCodingType = pCodecInf->SynNew.AdvPicSyntax.PTYPE;

    if (pSeqSyn->TFCNTRFLAG)
    {
        pPicSyn->TFCNTR = BsGet(pBs, 8);
    }

    if (pSeqSyn->PULLDOWN)
    {
        if (0 == pSeqSyn->INTERLACE)
        {
            pPicSyn->RPTFRM = BsGet(pBs, 2);
        }
        else
        {
            pPicSyn->TFF = BsGet(pBs, 1);
            pPicSyn->RFF = BsGet(pBs, 1);
        }
    }
	else
	{
		pPicSyn->TFF = 1;
	}

    //derive num of pan scan win
    if (1 == pSeqSyn->INTERLACE)
    {
        if (1 == pSeqSyn->PULLDOWN)
        {
            pPicSyn->NumOfPanScanWindows = 2 + pPicSyn->RFF;
        }
        else
        {
            pPicSyn->NumOfPanScanWindows = 2;
        }
    }
    else
    {
        if (1 == pSeqSyn->PULLDOWN)
        {
            pPicSyn->NumOfPanScanWindows = 1 + pPicSyn->RPTFRM;
        }
        else
        {
            pPicSyn->NumOfPanScanWindows = 1;
        }
    }

    if (1 == pEntSyn->PANSCAN_FLAG)
    {
        pPicSyn->PS_PRESENT = BsGet(pBs, 1);
        if (1 == pPicSyn->PS_PRESENT)
        {
            for (i = 0; i < pPicSyn->NumOfPanScanWindows; i++)
            {
                pPicSyn->PS_HOFFSET[i] = BsGet(pBs, 18);
                pPicSyn->PS_VOFFSET[i] = BsGet(pBs, 18);
                pPicSyn->PS_WIDTH[i]  = BsGet(pBs, 14);
                pPicSyn->PS_HEIGHT[i] = BsGet(pBs, 14);
            }
        }
    }

    switch (pPicSyn->PTYPE)
    {
    case VC1_VFMW_IPIC:
        Ret = VC1_Vfmw_ParseAdvIPicHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_PPIC:
        Ret = VC1_Vfmw_ParseAdvPPicHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_BPIC:
        Ret = VC1_Vfmw_ParseAdvBPicHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_BIPIC:
        Ret = VC1_Vfmw_ParseAdvIPicHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_SKPIC:
        Ret = VC1_VFMW_TRUE;
        break;
    default:
        Ret = VC1_VFMW_FALSE;
    }

    return Ret;
}

SINT32 VC1_DecRefdist(BS *pBs)
{
    SINT32 Code, Len;

    Code = BsShow(pBs, 5);
    if (0x18 > Code)
    {
        Code >>= 3;
        Len = 2;
    }
    else if (0x1c > Code)
    {
        Code >>= 2;
        Len = 3;
    }
    else if (0x1e > Code)
    {
        Code >>= 1;
        Len = 4;
    }
    else
    {
        Len = 5;
    }

    BsSkip(pBs, Len);
    return (Len > 2) ? Len : Code;
}

SINT32 VC1_DecIntCompField(BS *pBs)
{
    VC1_VFMW_VLC_S VlcTab[4] = {{VC1_TOPHFLDINT, 2}, {VC1_BOTFLDINT, 2}, {VC1_BOTHFLDINT, 1}, {VC1_BOTHFLDINT, 1}};
    SINT32 Code, Len, Tmp;

    Tmp  = BsShow(pBs, 2);
    Code = VlcTab[Tmp].Code;
    Len = VlcTab[Tmp].Len;
    BsSkip(pBs, Len);
    return Code;
}

SINT32 VC1_Vfmw_ParseAdvIFieldHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;
    //SINT32 i, MbNum = pCodecInf->MbWidth * pCodecInf->MbHeight;

    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pEntSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pEntSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->POSTPROCFLAG)
    {
        pPicSyn->POSTPROC = BsGet(pBs, 2);
    }
#ifdef VFMW_BPD_H_SUPPORT
    if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
    {
        dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
        return VC1_VFMW_FALSE;
    }
#else
    if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    {
        pPicSyn->ACPREDMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, (pCodecInf->MbHeight+1) / 2, &pPicSyn->ACPRED);
        if ((1 == pEntSyn->OVERLAP) && (8 >= pPicSyn->PQUANT))
        {
            pPicSyn->CONDOVER = (BsShow(pBs, 1) == 0 ? BsGet(pBs, 1) : BsGet(pBs, 2));
            if (1 == pPicSyn->CONDOVER)
            {
                return VC1_VFMW_FALSE;
            }
            if (3 == pPicSyn->CONDOVER)
            {
                pPicSyn->OVERFLAGSMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, (pCodecInf->MbHeight+1) / 2, &pPicSyn->OVERFLAGS);
            }
        }
    }
    else
    {
        if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
        {
            dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
            return VC1_VFMW_FALSE;
        }
    }
#endif
    pPicSyn->TRANSACFRM  = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSACFRM2 = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);

    //vopdquant
    if (0 != pEntSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pEntSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }

    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseAdvPFieldHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;

    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pEntSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pEntSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
           pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->POSTPROCFLAG)
    {
        pPicSyn->POSTPROC = BsGet(pBs, 2);
    }

    pPicSyn->NUMREF = BsGet(pBs, 1);
    if (0 == pPicSyn->NUMREF)
    {
        pPicSyn->REFFIELD = !BsGet(pBs, 1); //must be NOT operated
    }

    if (1 == pEntSyn->EXTENDED_MV)
    {
        pPicSyn->MVRANGE = VC1_DecMvrange(pBs);
    }
    if (1 == pEntSyn->EXTENDED_DMV)
    {
        pPicSyn->DMVRANGE = VC1_DecMvrange(pBs);
    }

    //mvmode
    pPicSyn->MVMODE = VC1_DecMvmodeProgrP(pBs, (UINT8)pPicSyn->PQUANT);
    if (VC1_INTCMP == pPicSyn->MVMODE)
    {
        pPicSyn->MVMODE2 = VC1_DecMvmode2(pBs, (UINT8)pPicSyn->PQUANT);
        pPicSyn->INTCOMPFIELD = VC1_DecIntCompField(pBs);
        pPicSyn->LUMSCALE = BsGet(pBs, 6);
        pPicSyn->LUMSHIFT = BsGet(pBs, 6);
        if (VC1_BOTHFLDINT == pPicSyn->INTCOMPFIELD)
        {
            pPicSyn->LUMSCALE2 = BsGet(pBs, 6);
            pPicSyn->LUMSHIFT2 = BsGet(pBs, 6);
        }
    }
    //dprint(PRN_PIC, "Check Pos 1: %d\n", BsPos(pBs));

    pPicSyn->MBMODETAB = BsGet(pBs, 3);

    pPicSyn->MVTAB  = (0 == pPicSyn->NUMREF) ? BsGet(pBs, 2) : BsGet(pBs, 3);
    pPicSyn->CBPTAB = BsGet(pBs, 3);

    if ((VC1_MIXMV == pPicSyn->MVMODE)
        || ((VC1_INTCMP == pPicSyn->MVMODE) && (VC1_MIXMV == pPicSyn->MVMODE2)))
    {
        pPicSyn->QMVBPTAB = BsGet(pBs, 2);
    }

    if (0 != pEntSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pEntSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }
    //dprint(PRN_PIC, "Check Pos 2: %d\n", BsPos(pBs));

    if (1 == pEntSyn->VSTRANSFORM)
    {
        pPicSyn->TTMBF = BsGet(pBs, 1);
        if (1 == pPicSyn->TTMBF)
        {
            pPicSyn->TTFRM = BsGet(pBs, 2);
        }
    }

    pPicSyn->TRANSACFRM = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);

    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseAdvBFieldHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;
    //SINT32 MbNum = pCodecInf->MbWidth * pCodecInf->MbHeight;

    pPicSyn->NUMREF = 1;
    pPicSyn->PQINDEX = BsGet(pBs, 5);
    if (pPicSyn->PQINDEX==0)
    {
        return VC1_VFMW_FALSE;
	}
    pPicSyn->PQUANT = VC1_Vfmw_DecPQUANT(pEntSyn->QUANTIZER, pPicSyn->PQINDEX);
    if (8 >= pPicSyn->PQINDEX)
    {
        pPicSyn->HALFQP = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->HALFQP = 0;
    }

    if (VC1_EXPLICITFRAMEQ1 == pEntSyn->QUANTIZER)
    {
        pPicSyn->PQUANTIZER = BsGet(pBs, 1);
    }
    else
    {
        pPicSyn->PQUANTIZER = 0;
    }

    if (1 == pSeqSyn->POSTPROCFLAG)
    {
        pPicSyn->POSTPROC = BsGet(pBs, 2);
    }

    if (1 == pEntSyn->EXTENDED_MV)
    {
        pPicSyn->MVRANGE = VC1_DecMvrange(pBs);
    }

    if (1 == pEntSyn->EXTENDED_DMV)
    {
        pPicSyn->DMVRANGE = VC1_DecMvrange(pBs);
    }

    pPicSyn->MVMODE = VC1_DecMvmodeInterB(pBs, (UINT8)pPicSyn->PQUANT);
#ifdef VFMW_BPD_H_SUPPORT
    if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
    {
        dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
        return VC1_VFMW_FALSE;
    }
#else
    if((g_VdmCharacter&VDM_SUPPORT_BPD) == 0)
    {
        pPicSyn->FORWARDMBMode = VC1_BitPlane(pBs, pCodecInf, pCodecInf->MbWidth, (pCodecInf->MbHeight+1) / 2, &pPicSyn->FORWARDMB);
    }
    else
    {
        if (BPD_Drv(pBs, pCodecInf, pSyntax, 0) == VFMW_FALSE)
        {
            dprint(PRN_FATAL, "%s %d BPD_Drv return err\n", __func__, __LINE__);
            return VC1_VFMW_FALSE;
        }
    }
#endif
    pPicSyn->MBMODETAB = BsGet(pBs, 3);

    pPicSyn->MVTAB  = BsGet(pBs, 3);
    pPicSyn->CBPTAB = BsGet(pBs, 3);

    if (VC1_MIXMV == pPicSyn->MVMODE)
    {
        pPicSyn->QMVBPTAB = BsGet(pBs, 2);
    }

    if (0 != pEntSyn->DQUANT)
    {
        VC1_VopDQuant(pBs, pEntSyn->DQUANT, (UINT8)pPicSyn->PQUANT, &pPicSyn->VOPDQUANT);
    }

    if (1 == pEntSyn->VSTRANSFORM)
    {
        pPicSyn->TTMBF = BsGet(pBs, 1);
        if (1 == pPicSyn->TTMBF)
        {
            pPicSyn->TTFRM = BsGet(pBs, 2);
        }
    }

    pPicSyn->TRANSACFRM = VC1_DecTransacfrm(pBs);
    pPicSyn->TRANSDCTAB = BsGet(pBs, 1);

    return VC1_VFMW_TRUE;
}

SINT32 VC1_Vfmw_ParseAdvFieldPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S *pEntSyn = &pSyntax->AdvEntSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;
    SINT32 Ret = VC1_VFMW_TRUE, i;

    if((0 == pCodecInf->Is2ndFld)||(0 < pCodecInf->SlcNum))
    {
        pPicSyn->FPTYPE = BsGet (pBs, 3);
        pPicSyn->FldPicType[0]   = FldPTypeTab[pPicSyn->FPTYPE ][0];
        pPicSyn->FldPicType[1]   = FldPTypeTab[pPicSyn->FPTYPE ][1];
        pPicSyn->PTYPE = (0 == pCodecInf->Is2ndFld)?pPicSyn->FldPicType[0]:pPicSyn->FldPicType[1];
		pCodecInf->PicCodingType = pCodecInf->SynNew.AdvPicSyntax.PTYPE;
        //dprint(PRN_DBG, "ptype : %#x, pCodecInf->PicCodingType : %#x\n", pPicSyn->PTYPE, pCodecInf->PicCodingType);
		if (pSeqSyn->TFCNTRFLAG)
        {
            pPicSyn->TFCNTR = BsGet(pBs, 8);
        }

        if (pSeqSyn->PULLDOWN)
        {
            if (0 == pSeqSyn->INTERLACE)
            {
                pPicSyn->RPTFRM = BsGet(pBs, 2);
            }
            else
            {
                pPicSyn->TFF = BsGet(pBs, 1);
                pPicSyn->RFF = BsGet(pBs, 1);
            }
        }
		else
		{
			pPicSyn->TFF = 1;
		}

        //derive num of pan scan win
        if (1 == pSeqSyn->INTERLACE)
        {
            if (1 == pSeqSyn->PULLDOWN)
            {
                pPicSyn->NumOfPanScanWindows = 2 + pPicSyn->RFF;
            }
            else
            {
                pPicSyn->NumOfPanScanWindows = 2;
            }
        }
        else
        {
            if (1 == pSeqSyn->PULLDOWN)
            {
                pPicSyn->NumOfPanScanWindows = 1 + pPicSyn->RPTFRM;
            }
            else
            {
                pPicSyn->NumOfPanScanWindows = 1;
            }
        }

        if (1 == pEntSyn->PANSCAN_FLAG)
        {
            pPicSyn->PS_PRESENT = BsGet(pBs, 1);
            if (1 == pPicSyn->PS_PRESENT)
            {
                for (i = 0; i < pPicSyn->NumOfPanScanWindows; i++)
                {
                    pPicSyn->PS_HOFFSET[i] = BsGet(pBs, 18);
                    pPicSyn->PS_VOFFSET[i] = BsGet(pBs, 18);
                    pPicSyn->PS_WIDTH[i]  = BsGet(pBs, 14);
                    pPicSyn->PS_HEIGHT[i] = BsGet(pBs, 14);
                }
            }
        }

        pPicSyn->RNDCTRL = BsGet(pBs, 1);
        pPicSyn->UVSAMP = BsGet(pBs, 1);
        if ((1 == pEntSyn->REFDIST_FLAG) && (VC1_BB > pPicSyn->FPTYPE))
        {
            pPicSyn->REFDIST = VC1_DecRefdist(pBs);
        }

        if (VC1_BB <= pPicSyn->FPTYPE)
        {
            pPicSyn->BFRACTION = VC1_DecBfraction(pBs, &pPicSyn->ScaleFactor);
        }

    }
    else
    {
        pPicSyn->PTYPE = pPicSyn->FldPicType[1];
		pCodecInf->PicCodingType = pCodecInf->SynNew.AdvPicSyntax.PTYPE;
    }
    //if (pCodecInf->SlcNum==0)
    //{
        //dprint(PRN_FATAL, "PTYPE      :%#x\n", pPicSyn->PTYPE);
    //}
    //!!!field layer for field 
    switch (pPicSyn->PTYPE)
    {
    case VC1_VFMW_IPIC:
    case VC1_VFMW_BIPIC:
        Ret = VC1_Vfmw_ParseAdvIFieldHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_PPIC:
        Ret = VC1_Vfmw_ParseAdvPFieldHdr(pBs, pCodecInf, pSyntax);
        break;
    case VC1_VFMW_BPIC:
        Ret = VC1_Vfmw_ParseAdvBFieldHdr(pBs, pCodecInf, pSyntax);
        break;
    default:
        Ret = VC1_VFMW_FALSE;
    }

    if (pPicSyn->TFF)
    {
        pPicSyn->CurParity = (0 == pCodecInf->Is2ndFld) ? VC1_VFMW_TOPFLD : VC1_VFMW_BOTFLD;
    } 
    else
    {
        pPicSyn->CurParity = (1 == pCodecInf->Is2ndFld) ? VC1_VFMW_TOPFLD : VC1_VFMW_BOTFLD;
    }
    return Ret;
}

SINT32 VC1_Vfmw_ParseAdvPicHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    VC1_ADVSEQSYNTAX_S *pSeqSyn = &pSyntax->AdvSeqSyntax;
    VC1_ADVPICSYNTAX_S *pPicSyn = &pSyntax->AdvPicSyntax;
    SINT32 Ret;
    
    VC1_SetCurPicResolutionInfo(pCodecInf, 0); //set to full all, ADV does not need this values, we here just for conformance
    if ((0 == pCodecInf->Is2ndFld)||(0 < pCodecInf->SlcNum))
    {
        pPicSyn->FCM = (1 == pSeqSyn->INTERLACE) ?  VC1_DecFcm(pBs) : 0;
    }
    //pCodecInf->PicStructure = pPicSyn->FCM;

    if ((VC1_VFMW_PROGRESSIVE == pPicSyn->FCM) || (VC1_VFMW_FRAMEINTER == pPicSyn->FCM))
    {
        Ret = VC1_Vfmw_ParseAdvFramePicHdr(pBs, pCodecInf, pSyntax);
    }
    else
    {
        Ret = VC1_Vfmw_ParseAdvFieldPicHdr(pBs, pCodecInf, pSyntax);
    }

    return Ret;
}

SINT32 VC1_Vfmw_ParseAdvSlcHdr(BS *pBs, VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    SINT32 Ret = VC1_VFMW_TRUE;
    VC1_ADVSLCSYNTAX_S *pSlcSyn = &pSyntax->AdvSlcSyntax[pCodecInf->SlcNum];
    VC1_VFMWSYNTAX_S *pTmpSyn = &pCodecInf->SynNewPicInSlcHeader;
    pSlcSyn->SLICE_ADDR = BsGet(pBs, 9);
    pSlcSyn->PIC_HEADER_FLAG = BsGet(pBs, 1);
    if (1 == pSlcSyn->PIC_HEADER_FLAG)
    {
        //BsSkip(pBs, pSyntax->AdvPicSyntax.HdrLen);
        //memcpy(pTmpSyn, pSyntax, sizeof(VC1_VFMWSYNTAX_S));

		pTmpSyn->AdvEntSyntax = pSyntax->AdvEntSyntax;
		pTmpSyn->AdvSeqSyntax = pSyntax->AdvSeqSyntax;
		pTmpSyn->AdvPicSyntax = pSyntax->AdvPicSyntax;

        Ret = VC1_Vfmw_ParseAdvPicHdr(pBs, pCodecInf, pTmpSyn);
    }

    return Ret;
}

SINT32 VC1_Vfmw_next_start_code(BS *pBs)
{
    SINT32 i, RemainByte;

    BsToNextByte(pBs); /*这些填充则应该全部为0*/
    RemainByte = (BsResidBits(pBs) / 8) - 3;

    for (i = 0; i < RemainByte; i++)
    {
        if (BsShow(pBs, 24) == 0x01L)
        {
            return VC1_VFMW_TRUE;
        }

        BsSkip(pBs, 8);
    }
    
    return VC1_VFMW_FALSE;
}

SINT32 VC1_Vfmw_UserData(BS *pBs)
{
    return VC1_VFMW_TRUE;
}

__inline SINT32 VC1_RecordSlcStream(VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax, UINT8 *pCurBsRealStart)
{
    VC1_SLCSTREAM_S *pSlc = pCodecInf->SlcStr + pCodecInf->SlcNum;
    VC1_ADVSLCSYNTAX_S *pSlcSyn = pSyntax->AdvSlcSyntax + pCodecInf->SlcNum;
    BS *pBs = pCodecInf->pBs;
    VC1_STREAM_PACKET *pPacket = &(pCodecInf->stCurPacket);
    UINT8 *pNextStartCode;
    UINT8 biteat = 0;
	UINT32 totalMbMin1;
    
    pSlc->SlcNo = pCodecInf->SlcNum;
    pSlc->pStream   = pCurBsRealStart + (pBs->TotalPos / 8); //point at first real byte aligned 
	pSlc->BitOffset = pBs->TotalPos & 7; //for start code occupy 32 bits
    pSlc->Len       = (pBs->BsLen * 8) - pBs->TotalPos; 
	pSlc->Phy_addr  = MEM_Vir2Phy(pSlc->pStream);
    pSlc->StreamID  = pPacket->StreamID[0];

    if((NULL != pPacket->BsVirAddr[1]) && (0 != pPacket->BsPhyAddr[1]))
    {
        pSlc->pStream2   = pPacket->BsVirAddr[1];
        pSlc->BitOffset2 = 0;
        pSlc->Len2       = pPacket->BsLength[1] * 8;
        pSlc->Phy_addr2  = pPacket->BsPhyAddr[1];
        pSlc->StreamID2  = pPacket->StreamID[1];
    }
    else
    {
        pSlc->pStream2   = NULL;
        pSlc->BitOffset2 = 0;
        pSlc->Len2       = 0;
        pSlc->Phy_addr2  = 0;
        pSlc->StreamID2  = 0;
    }
    
    if (NULL != pSlc->pStream2)
    {
        pNextStartCode = pPacket->BsLength[1] + pSlc->pStream2;
        pSlc->Len2 = pSlc->Len2 - biteat; //remained bit length is slic bit length
    }
	else
	{
		pNextStartCode = pBs->BsLen  + pCurBsRealStart;
        pSlc->Len = pSlc->Len - biteat; //remained bit length is slic bit length
	}

    totalMbMin1 = pCodecInf->MbHeight*pCodecInf->MbWidth - 1; 
	if (pCodecInf->Is2ndFld)
    {
        pSlc->SlcEndMbn = pSlcSyn->SLICE_ADDR - ((pCodecInf->MbHeight+1)/2); //it looks like ms count mb row in contiuous way when it's in 2nd field case
        /* 只有一个宏块时，由于上面的减法运算，会出现负数 */
		if(pSlc->SlcEndMbn > 0)
		{
			if(pSlc->SlcEndMbn > totalMbMin1)
			{
				dprint(	PRN_ERROR,"SLICE_ADDR = %d,SlcEndMbn = %d, MbHeight = %d\n",
					pSlcSyn->SLICE_ADDR, pSlc->SlcEndMbn, pCodecInf->MbHeight);
				return VC1_VFMW_FALSE;
			}
		}
    } 
    else
    {
        pSlc->SlcEndMbn = pSlcSyn->SLICE_ADDR;
		if(pSlc->SlcEndMbn > totalMbMin1)
		{
			dprint(	PRN_ERROR,"SLICE_ADDR = %d,SlcEndMbn = %d, totalMbMin1 = %d\n",
				pSlcSyn->SLICE_ADDR, pSlc->SlcEndMbn, totalMbMin1);
			return VC1_VFMW_FALSE;
		}
    }
	
	if ((pSlc->Len <= 0)||((NULL != pSlc->pStream2)&&(pSlc->Len2 <= 0)))
	{
        dprint(PRN_ERROR, "VC1_RecordSlcStream stream len <= 0\n");
        return VC1_VFMW_FALSE;
    }
    else
    {
        pCodecInf->SlcNum++;
        return VC1_VFMW_TRUE;
    }
}

SINT32 VC1_Vfmw_UpdateAdvSPS(VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax)
{
    SINT32 Ret = VC1_VFMW_FALSE;

    if (pSyntax->AdvEntSyntax.CODED_WIDTH != pCodecInf->AdvEntSyntax.CODED_WIDTH)
    {
        pCodecInf->MbWidth = (pSyntax->AdvEntSyntax.CODED_WIDTH + 15) / 16;
        pCodecInf->DispPicWidth = pSyntax->AdvEntSyntax.CODED_WIDTH;
        Ret = VC1_VFMW_TRUE;
    }
    
    if (pSyntax->AdvEntSyntax.CODED_HEIGHT != pCodecInf->AdvEntSyntax.CODED_HEIGHT)
    {
        pCodecInf->MbHeight = (pSyntax->AdvEntSyntax.CODED_HEIGHT + 15) / 16;
        pCodecInf->DispPicHeight = pSyntax->AdvEntSyntax.CODED_HEIGHT;
        Ret = VC1_VFMW_TRUE;
    }

    if (VC1_VFMW_TRUE == Ret)
    {
        pCodecInf->AdvSeqSyntax = pSyntax->AdvSeqSyntax;
        pCodecInf->AdvEntSyntax = pSyntax->AdvEntSyntax;
    }

    return Ret;
}

SINT32 VC1_Vfmw_ParseAdvHdr(VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax, SINT32 ChanID)
{
    SINT32 Code, BsLen;
    SINT32 Ret = VC1_VFMW_TRUE;
    UINT32 end_code1, end_code2;  
    BS *pBs = pCodecInf->pBs;
    UINT8 *pTmp;
    VC1_STREAM_PACKET *pVc1Packet = &(pCodecInf->stCurPacket);

    pCodecInf->IsWaitToDec = 0;
  
    Code  = (BsGet(pBs, 32)) & 0xff;
    BsLen = pVc1Packet->BsLength[0] - (pBs->TotalPos) / 8;//pCodecInf->pBsPack->Length - (pBs->TotalPos) / 8;
    pTmp = pVc1Packet->BsVirAddr[0] + (pBs->TotalPos) / 8;//pCodecInf->pBsPack->VirAddr + (pBs->TotalPos) / 8;
    BsInit(pBs, pTmp, BsLen);
    
    if ((VC1_SCSEQ >= Code)&&(VC1_SCEOS <= Code))
    {
        if (VC1_SCSLC == Code)
        {
            if ((VC1_CHECKSTAT(pCodecInf->CodecStatus, VC1_PPSOK | VC1_SPSOK | VC1_ENTOK)))
            {
                Ret = VC1_Vfmw_ParseAdvSlcHdr(pBs, pCodecInf, pSyntax);
				if (VC1_VFMW_TRUE == Ret)
				{
                    /* slice 个数以超过极限值 */
                    if(pCodecInf->SlcNum >= 256 )
                    {
                        /* 清除当前帧的所有 slice 信息 */
                        VC1_ClearCurPic(pCodecInf, ChanID);
                        dprint(PRN_ERROR, " pCodecInf->SlcNum = %d >= 256 \n",pCodecInf->SlcNum);
                        return VC1_VFMW_FALSE;
                    }
                    Ret = VC1_RecordSlcStream(pCodecInf, pSyntax, pTmp);
				}
                else
                {
                    VC1_ClearCurPacket(ChanID,pVc1Packet);
                    dprint(PRN_ERROR, "line %d, Code = VC1_SCSLC failed!\n",__LINE__);
                }
			}
            else
            {
                //wild slc? give a warning
//                pCodecInf->ParsePckNum++;
                VC1_ClearCurPacket(ChanID,pVc1Packet);
                //dprint(PRN_PIC, "DBG: Wild slice!!!\n");
				Ret = VC1_VFMW_FALSE;
            }
        }
        else
        {
            if ((VC1_CHECKSTAT(pCodecInf->CodecStatus, VC1_PPSOK | VC1_SPSOK | VC1_ENTOK)))
            {
                pCodecInf->CodecStatus |= VC1_ALLSLCOK;
                //dprint(PRN_STREAM, "///// all slc ready, this pack not parsed \n");
                pCodecInf->IsWaitToDec = 1;
                return VC1_VFMW_TRUE;
            }

//            pCodecInf->ParsePckNum++;
            pCodecInf->Is2ndFld = 0;

            //no slice collected yet
            pCodecInf->SlcNum = 0;
            switch (Code)
            {
            case VC1_SCEOS:
                pCodecInf->CodecStatus |= VC1_EOSOK;
                VC1_ClearCurPacket(ChanID,pVc1Packet);
                break;
            case VC1_SCFLD:
				pCodecInf->Is2ndFld = 1;
                memset(&pSyntax->AdvPicSyntax.VOPDQUANT, 0, sizeof(VC1_VOPDQUANT_S));
            case VC1_SCFRM:
                if (0 == pCodecInf->Is2ndFld)
                {
                    SINT32 REFDIST = pSyntax->AdvPicSyntax.REFDIST; //this value must be reserved between pictures
                    memset(&pSyntax->AdvPicSyntax, 0, sizeof(VC1_ADVPICSYNTAX_S));
                #ifndef VFMW_BPD_H_SUPPORT
					pSyntax->AdvPicSyntax.ACPRED.pElement = pCodecInf->ACPRED;
					pSyntax->AdvPicSyntax.OVERFLAGS.pElement = pCodecInf->OVERFLAGS;
                	pSyntax->AdvPicSyntax.MVTYPEMB.pElement = pCodecInf->MVTYPEMB;
                	pSyntax->AdvPicSyntax.DIRECTMB.pElement = pCodecInf->DIRECTMB;
                	pSyntax->AdvPicSyntax.SKIPMB.pElement = pCodecInf->SKIPMB;
                	pSyntax->AdvPicSyntax.FIELDTX.pElement = pCodecInf->FIELDTX;
                	pSyntax->AdvPicSyntax.FORWARDMB.pElement = pCodecInf->FORWARDMB;
                #endif
                    pSyntax->AdvPicSyntax.REFDIST = REFDIST;
                }
                memset(pCodecInf->SlcStr, 0, sizeof(pCodecInf->SlcStr));
                pSyntax->AdvPicSyntax.HdrLen = BsPos(pBs);
                //parse adv pic head

		        Ret = VC1_Vfmw_ParseAdvPicHdr(pBs, pCodecInf, pSyntax);
				if (VC1_VFMW_TRUE == Ret)
				{
                    //print pic hdr len
                    pSyntax->AdvPicSyntax.HdrLen = BsPos(pBs) - pSyntax->AdvPicSyntax.HdrLen;
                    pCodecInf->CodecStatus |= VC1_PPSOK;
                    
                    if ((BsPos (pBs) + 0x20) < (pVc1Packet->BsLength[0] * 8))
                    {
                        //there's remain bit for current pack. they should be first slc
                        Ret = VC1_RecordSlcStream(pCodecInf, pSyntax, pTmp);
                    }
                    else
                    {
                        VC1_ClearCurPacket(ChanID,pVc1Packet);
                        dprint(PRN_ERROR, "line %d, Code = VC1_SCFRM failed!\n",__LINE__);
                    }
				}
                else
                {
                    VC1_ClearCurPacket(ChanID,pVc1Packet);
                    dprint(PRN_ERROR, "line %d, Code = VC1_SCFRM failed!\n",__LINE__);
                }
                
                break;
            case VC1_SCENT:
                Ret = VC1_Vfmw_ParseAdvEntptHdr(pBs, pCodecInf, pSyntax);
				if (VC1_VFMW_TRUE == Ret)
				{
                    VC1_Vfmw_UpdateAdvSPS(pCodecInf, pSyntax);
                    pCodecInf->CodecStatus |= VC1_ENTOK;
				}
                VC1_ClearCurPacket(ChanID,pVc1Packet);
				break;
            case VC1_SCSEQ:
                Ret = VC1_Vfmw_ParseAdvSeqHdr(pBs, pCodecInf, pSyntax);
				if (VC1_VFMW_TRUE == Ret)
				{
                    pCodecInf->CodecStatus |= VC1_SPSOK;
				}
                VC1_ClearCurPacket(ChanID,pVc1Packet);
                break;
            default:
                VC1_ClearCurPacket(ChanID,pVc1Packet);
                Ret = VC1_VFMW_FALSE;
            }
        }
    }
    else if ((VC1_SCSEQUD >= Code)&&(VC1_SCSLCUD <= Code)) 	/*此处直接判断Code不小于VC1_SCSLCUD则为user data，但是大于VC1_SCSEQUD的情况是什么
                                                              呢枚举中好像有不全的现象，如跑stress_reserved_startcodesc.wmv.vc1 就会大于*/
    {
        VC1_Vfmw_UserData(pBs);
        VC1_ClearCurPacket(ChanID,pVc1Packet);
    }
    else
    {
        if(HISI_VC1AP_STREAM_END_CODE == Code)
        {
            end_code1 = (UINT32)BsGet(pBs, 32);
            end_code2 = (UINT32)BsGet(pBs, 32);
            if (HISI_STREAM_END_CODE1 == end_code1 && HISI_STREAM_END_CODE2 == end_code2)
            {
                pCodecInf->IsStreamEndFlag = 1;              // last frame
                if ((VC1_CHECKSTAT(pCodecInf->CodecStatus, VC1_PPSOK | VC1_SPSOK | VC1_ENTOK)))
                {
                    pCodecInf->CodecStatus |= VC1_ALLSLCOK;
                }
                VC1_ClearCurPacket(ChanID,pVc1Packet);
                return VC1_VFMW_TRUE;
            }
        }
        
        VC1_ClearCurPacket(ChanID,pVc1Packet);
        Ret = VC1_VFMW_FALSE;
	}

    return Ret;
}

SINT32 VC1_Vfmw_ParseHeader(VC1_VFMWCODECINF_S *pCodecInf, VC1_VFMWSYNTAX_S *pSyntax, SINT32 ChanID)
{
    SINT32 Ret = VC1_VFMW_FALSE;

    if (0 == pCodecInf->PreParseInfo.IsAdvProfile)
    {
        pCodecInf->CodecStatus |= VC1_SPSOK | VC1_ENTOK;

        //SMP just decode the picture head
        Ret = VC1_Vfmw_ParseSMPPicHdr(pCodecInf->pBs, pCodecInf, pSyntax);
        if (VC1_VFMW_TRUE == Ret)
        {
            pCodecInf->CodecStatus |= VC1_PPSOK | VC1_ALLSLCOK;
        }
    }
    else
    {
#if 0        
        //ADV need decode from seq
        //dprint(PRN_DBG,"rcvpacket : %d, parpacket : %d\n",pCodecInf->RcvPackNum,pCodecInf->ParsePckNum);
        for (i = 0; i < pCodecInf->RcvPackNum; i++)
        {
            pPacket = &pCodecInf->PackOfCurPic[i];
            pCodecInf->pBsPack = pPacket;
            BsInit (pCodecInf->pBs, pPacket->VirAddr, pPacket->Length);
            Ret = VC1_Vfmw_ParseAdvHdr(pCodecInf, pSyntax);
            if ((VC1_CHECKSTAT(pCodecInf->CodecStatus, VC1_ALLSLCOK)) && (VC1_VFMW_TRUE == Ret))
            {
                break;
            }
        }

        VC1_Vfmw_ReleasePacket(pCodecInf);
#endif
        Ret = VC1_Vfmw_ParseAdvHdr(pCodecInf, pSyntax,ChanID);
    }

    return Ret;
}


SINT32 VC1_Vfmw_UpdataLastPicRNDCTRL(VC1_VFMWCODECINF_S *pCodecInf)
{
	SINT32 RndCtrl;
//static SINT32 LastPicRNDCTRL = 1;

	if (!pCodecInf->PreParseInfo.IsAdvProfile)
	{
		if ( (VC1_VFMW_IPIC == pCodecInf->SMPPicSyntax.PTYPE) || (VC1_VFMW_BIPIC == pCodecInf->SMPPicSyntax.PTYPE) )
		{
			RndCtrl = 1;
		}
		else if (VC1_VFMW_PPIC == pCodecInf->SMPPicSyntax.PTYPE)
		{
			//RndCtrl = !LastPicRNDCTRL;  //!pCodecInf->LastPicRNDCTRL;
			RndCtrl = !pCodecInf->LastPicRNDCTRL;			
		}
		else
		{
			//RndCtrl = LastPicRNDCTRL;  //pCodecInf->LastPicRNDCTRL;
			RndCtrl = pCodecInf->LastPicRNDCTRL;			
		}

        pCodecInf->LastPicRNDCTRL = RndCtrl;
//LastPicRNDCTRL = RndCtrl;
	
		pCodecInf->SMPPicSyntax.RNDCTRL = RndCtrl;
	}

	return VC1_VFMW_TRUE;

}
SINT32 VC1_Vfmw_DecPQUANT(SINT32 Quantizer, SINT32 PqIndex)
{
    SINT32 PQuantIdex[32] = {0,   1,  2,  3,  4,  5,  6,  7,  8,  6,  7,  8, 9, 10, 11, 12, 13, 14, 15,
                             16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 29, 31
                            };

    if (VC1_EXPLICITFRAMEQ0 == Quantizer)
    {
        return PQuantIdex[PqIndex];
    }
    else
    {
        return PqIndex;
    }
}

SINT32 VC1_ReceivePacket(VC1_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    VC1_STREAM_PACKET *pstPacket = &pCtx->CodecInfo.stCurPacket;

    if (NULL == pPacket)
    {
        /* 返回初始化没有成功或者码流长度异常*/
        dprint(PRN_FATAL, "bitsream para error -----\n");
        return VC1_VFMW_FALSE; 
    }
    
    pstPacket->BsPhyAddr[0] = pPacket->StreamPack[0].PhyAddr;
    pstPacket->BsVirAddr[0] = pPacket->StreamPack[0].VirAddr;
    pstPacket->BsLength[0]  = pPacket->StreamPack[0].LenInByte;
    pstPacket->IsLastSeg[0] = pPacket->StreamPack[0].IsLastSeg;
    pstPacket->StreamID[0]  = pPacket->StreamPack[0].StreamID;

    if (1 != pPacket->StreamPack[0].IsLastSeg)
    {
        pstPacket->BsPhyAddr[1] =  pPacket->StreamPack[1].PhyAddr;
        pstPacket->BsVirAddr[1] =  pPacket->StreamPack[1].VirAddr;
        pstPacket->BsLength[1]  =  pPacket->StreamPack[1].LenInByte;
        pstPacket->IsLastSeg[1] =  pPacket->StreamPack[1].IsLastSeg;
        pstPacket->StreamID[1]  =  pPacket->StreamPack[1].StreamID;
        
        if (1 != pPacket->StreamPack[1].IsLastSeg)
        {
            VC1_ClearCurPacket(pCtx->ChanID, pstPacket);
            dprint(PRN_ERROR, "line %d, pPacket->StreamPack[1].IsLastSeg = %d\n", pPacket->StreamPack[1].IsLastSeg);
            return VC1_VFMW_FALSE;
        }
    }
    else
    {
        pstPacket->BsPhyAddr[1] = 0;
        pstPacket->BsVirAddr[1] = 0;
        pstPacket->BsLength[1]  = 0;
        pstPacket->IsLastSeg[1] = 0;
        pstPacket->StreamID[1]  = 0; 
    }

    VC1_SetCodeInfo(pCtx, pstPacket);

    return VC1_VFMW_TRUE;
}

VOID VC1_ClearCurPacket(SINT32 ChanID, VC1_STREAM_PACKET *pVc1Packet)
{
    SM_ReleaseStreamSeg(ChanID, pVc1Packet->StreamID[0]);
    if(1 != pVc1Packet->IsLastSeg[0])
    {
        SM_ReleaseStreamSeg(ChanID, pVc1Packet->StreamID[1]);
    }
    
    memset(pVc1Packet, 0, sizeof(VC1_STREAM_PACKET));
}

VOID VC1_ClearCurPic(VC1_VFMWCODECINF_S *pCodeInfo, SINT32 ChanID)
{
    SINT32 i = 0;
    VC1_SLCSTREAM_S *pSlcInfo = NULL;

    if (0 == pCodeInfo->PreParseInfo.IsAdvProfile)
    {
        VC1_ClearCurPacket(ChanID, &(pCodeInfo->stCurPacket));
    }
    else
    {
        for(i = 0; i < pCodeInfo->SlcNum; i++)
        {
            pSlcInfo = &(pCodeInfo->SlcStr[i]);
            SM_ReleaseStreamSeg(ChanID, pSlcInfo->StreamID);
            if((NULL != pSlcInfo->pStream2) && (0 != pSlcInfo->Phy_addr2))
            {
                SM_ReleaseStreamSeg(ChanID, pSlcInfo->StreamID2);
            }
        }
    }
}

VOID VC1_SetCodeInfo(VC1_CTX_S *pCtx, VC1_STREAM_PACKET *pVc1Packet)
{
    VC1_VFMWCODECINF_S *pCodeInfo = &(pCtx->CodecInfo);
    
    pCodeInfo->pBs = &(pCodeInfo->Bs);

    if (pCodeInfo->PreParseInfo.CodecVersion == WMVC1)
    {
        pCodeInfo->PostCresent = 1;
        pCodeInfo->CodecVersion = WMVA;
    } 
    else
    {
        pCodeInfo->PostCresent = 0;
        pCodeInfo->CodecVersion = pCodeInfo->PreParseInfo.CodecVersion;
    }

    if (0 == pCodeInfo->PreParseInfo.IsAdvProfile)
    {
        BsInit(pCodeInfo->pBs, pVc1Packet->BsVirAddr[0], pVc1Packet->BsLength[0]);
        pCodeInfo->MbWidth  = (pCodeInfo->PreParseInfo.FrmWidth + 15) / 16;
        pCodeInfo->MbHeight = (pCodeInfo->PreParseInfo.FrmHeight + 15) / 16; 
        pCodeInfo->DispPicWidth  = pCodeInfo->PreParseInfo.FrmWidth;
        pCodeInfo->DispPicHeight = pCodeInfo->PreParseInfo.FrmHeight; 
        pCodeInfo->SynNew.SMPSeqSyntax = pCodeInfo->PreParseInfo.SMPSeqSyntax;
    }
    else
    {
        BsInit(pCodeInfo->pBs, pVc1Packet->BsVirAddr[0], pVc1Packet->BsLength[0]);
    }

}

SINT32 VC1_GetPacketState(VC1_CTX_S *pCtx)
{
    SINT32 ret = VC1_VFMW_FALSE;
    if(1 == pCtx->CodecInfo.IsWaitToDec)
    {
        ret = VC1_NOT_DEC;
    }

    return ret;
}

#endif //VC1_VFMW_ENABLE

