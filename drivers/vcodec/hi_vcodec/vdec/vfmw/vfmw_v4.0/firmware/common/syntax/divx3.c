/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r33h4NPqO4RWTjpsxE3p03dWu4qWcICm/GJutgKmhFBEJU9pw5AUYhpyuGpN06dJNpvCt
jR41kYOP4p0KB8toaCf8W+6sPIxtyYrvzWpXVfHSC7AQVYoxZQRjpCnXrYvAeg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************
*
* Copyright (c) 2012 HUAWEI - All Rights Reserved
*
* File: $divx3_vfmw.c$
* Date: $2012/01/06$
* Revision: $v1.0$
* Purpose: divx3 decoder file
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ====== 
* 2012/01/06       q45134                       Original
*
* Dependencies:
*
************************************************************************/


#include    "syntax.h"
#include    "divx3.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"

#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


#ifdef DIVX3_ENABLE

#define DIVX3_CLEARREFFLAG do {                                       \
    FSP_ClearLogicFs(pCtx->ChanID, pDivx3CodecInfo->FwdFsID, 1);      \
    pDivx3CodecInfo->FwdFsID = 0;                                     \
    pDivx3CodecInfo->FwdFsID=FSP_GetNullLogicFs(pCtx->ChanID);\
} while(0)

#define DIVX3_CLEARREFNUM do {pDivx3CodecInfo->RefNum=0;} while (0)



/*!
************************************************************************
*    函数原型 :  Divx3_GetImageBuffer()
*    功能描述 :  取一块帧存
*    参数说明 :  **p_vobuf 用于指向当前可用帧存的指针的地址
*    返回值   :  0: 无法找到可用帧存;1: 能够找到可用帧存
************************************************************************
*/
UINT32 Divx3_GetImageBuffer(DIVX3_CTX_S *pCtx)
{
    SINT32 ret = DIVX3_VFMW_FALSE;
    DIVX3_CODECINF *pDivx3CodecInfo;
    DIVX3_VOBUFINF *pVOBufInf;

    pDivx3CodecInfo = &pCtx->CodecInfo;
    pVOBufInf = pCtx->CodecInfo.VOBufInf;

    pDivx3CodecInfo->CurFsID = FSP_NewLogicFs(pCtx->ChanID, 1);
    if (pDivx3CodecInfo->CurFsID < 0)
    {
        /* 获取帧存失败 */
        dprint(PRN_FATAL, "get frame store fail!\n");
		#if 0
		ResetVoQueue(&pCtx->ImageQue);
		FSP_EmptyInstance(pCtx->ChanID);
		#else
		FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		#endif

        DIVX3_CLEARREFFLAG;
        DIVX3_CLEARREFNUM;
        return 0;
    }

    ret = DIVX3_VFMW_TRUE;
    {
        FSP_LOGIC_FS_S *pLf = FSP_GetLogicFs(pCtx->ChanID, pDivx3CodecInfo->CurFsID);
        if (NULL == pLf)
        {
            dprint(PRN_FATAL, "line: %d, pImage is NULL!\n", __LINE__);
            return DIVX3_VFMW_FALSE;
        }
        
        dprint(PRN_PIC, "get image buffer ok: LogicFsID = %d\n", pDivx3CodecInfo->CurFsID);
        if ( (NULL!=pLf->pstDecodeFs) && (NULL!=pLf->pstDispOutFs) && (NULL!=pLf->pstTfOutFs) )
        {
            dprint(PRN_PIC, "decode %p, disp %p, tf %p\n", pLf->pstDecodeFs->PhyAddr, pLf->pstDispOutFs->PhyAddr, pLf->pstTfOutFs->PhyAddr);
        }
        if (pDivx3CodecInfo->CurFsID == 2)
        {
            pDivx3CodecInfo->CurFsID = pDivx3CodecInfo->CurFsID;
        }
    }

    return ret;
}


/*!
************************************************************************
*    函数原型 :  Divx3_ArrangeVHBMem()
*    功能描述 :  分配消息池和帧存空间并初始化管理帧存的队列
*    参数说明 :  ImageNum 需要分配的帧存
*    返回值   :  0: 分配失败 1: 分配成功
************************************************************************
*/
UINT32 Divx3_ArrangeVHBMem(SINT32 ImageNum, DIVX3_CTX_S *pCtx, DIVX3_PictureHeader_S *pPictureHeader)
{
    DIVX3_CODECINF *pDivx3CodecInfo;
    FSP_INST_CFG_S  FspInstCfg;
    SINT32 PicWidth, PicHeight, DecFsNum, DispFsNum, PmvNum;
    SINT32 Ret, UsedMemSize;

    pDivx3CodecInfo = &pCtx->CodecInfo;

    if( pPictureHeader->pic_width_in_mb < 2 || pPictureHeader->pic_height_in_mb < 2 )
    {
        dprint(PRN_FATAL, "image size abnormal (%dx%d) in MB\n", pPictureHeader->pic_width_in_mb, pPictureHeader->pic_height_in_mb);
        return DIVX3_VFMW_FALSE;
    }

    if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
    {
        if ((pPictureHeader->pic_width_in_pix) > pCtx->pstExtraData->stChanOption.s32MaxWidth || (pPictureHeader->pic_height_in_pix) > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "divx3 actual frame size(%dx%d) exeed max config(%dx%d)\n", pPictureHeader->pic_width_in_pix, pPictureHeader->pic_height_in_pix,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return DIVX3_VFMW_FALSE;
		}
				
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        PicWidth  = pCtx->pstExtraData->stChanOption.s32MaxWidth;
        PicHeight = pCtx->pstExtraData->stChanOption.s32MaxHeight;
		
        if (pDivx3CodecInfo->Imgbuf_allocated == DIVX3_VFMW_TRUE)
        {
            return DIVX3_VFMW_TRUE;
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
        PicWidth  = pPictureHeader->pic_width_in_pix;
        PicHeight = pPictureHeader->pic_height_in_pix;	
		DecFsNum = 4;
		PmvNum = 2;
		DispFsNum = 5;		
	}
	else
	{
        if ((pPictureHeader->pic_width_in_pix) > pCtx->pstExtraData->stChanOption.s32MaxWidth || (pPictureHeader->pic_height_in_pix) > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "divx3 actual frame size(%dx%d) exeed max config(%dx%d)\n", (pPictureHeader->pic_width_in_pix), (pPictureHeader->pic_height_in_pix),
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return DIVX3_VFMW_FALSE;
		}
        PicWidth  = (pPictureHeader->pic_width_in_pix);
        PicHeight = (pPictureHeader->pic_height_in_pix);
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
        Ret = FSP_PartitionFsMemory(pCtx->ChanID, pCtx->pstExtraData->s32SyntaxMemAddr, 
                                    pCtx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
        if (Ret != FSP_OK)
        {
            // 分割帧存失败，返回
            return DIVX3_VFMW_FALSE;
        }
    }
    else
    {
        return DIVX3_VFMW_FALSE;
    }
	
    pDivx3CodecInfo->Imgbuf_allocated = DIVX3_VFMW_TRUE;

    return DIVX3_VFMW_TRUE;
}


VOID Divx3_SetImgFormat(DIVX3_CTX_S *pCtx)
{
    UINT32 codtype = 0, csp = 0, vfmt = 0, sfmt = 0, fldflg = 0, fldfst = 0, dar = 0;
    DIVX3_CODECINF *pDivx3CodecInfo;
    DIVX3_PictureHeader_S *pPictureHeader;
    IMAGE *pImg;

    pDivx3CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;

    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pDivx3CodecInfo->CurFsID);
    if (NULL == pImg)
    {
        return;
    }

    codtype = pPictureHeader->prediction_type;
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
    pImg->image_width = pPictureHeader->pic_width_in_pix;
    pImg->image_height = pPictureHeader->pic_height_in_pix;

	SetAspectRatio(pImg,(VDEC_DAR_E)dar);
	
    //pDivx3CodecInfo->pRCN->imginf.error_level = pDivx3CodecInfo->pRCN->err_level;
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
*    函数原型 :  Divx3_RecordVFMWState(VOID)
*    功能描述 :  记录VFMW的工作状态
*    参数说明 :  无
*    返回值   :  无
************************************************************************
*/
VOID Divx3_RecordVFMWState(DIVX3_CTX_S *pCtx)
{
    DIVX3_CODECINF *pDivx3CodecInfo;

    pDivx3CodecInfo = &pCtx->CodecInfo;

    return;
}


VOID Divx3_WritePicMsg(DIVX3_CTX_S *pCtx)
{
    DIVX3_DEC_PARAM_S *pDivx3DecParam;
    DIVX3_CODECINF *pDivx3CodecInfo;
    DIVX3_PictureHeader_S *pPictureHeader;

    pDivx3DecParam = &pCtx->Divx3DecParam;
    pDivx3CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;


    pDivx3DecParam->prediction_type = pPictureHeader->prediction_type;

    pDivx3DecParam->PicWidthInMb = pPictureHeader->pic_width_in_mb;
    pDivx3DecParam->PicHeightInMb = pPictureHeader->pic_height_in_mb;

    pDivx3DecParam->quantizer = pPictureHeader->quantizer;
    pDivx3DecParam->rounding_type = pPictureHeader->rounding_type;
    pDivx3DecParam->has_skips = pPictureHeader->has_skips;

    pDivx3DecParam->alternative_I_AC_chrom_DCT = pPictureHeader->alternative_I_AC_chrom_DCT;
    pDivx3DecParam->alternative_I_AC_lum_DCT = pPictureHeader->alternative_I_AC_lum_DCT;
    pDivx3DecParam->alternative_I_DC_DCT = pPictureHeader->alternative_I_DC_DCT;
    pDivx3DecParam->alternative_P_AC_DCT = pPictureHeader->alternative_P_AC_DCT;
    pDivx3DecParam->alternative_P_DC_DCT = pPictureHeader->alternative_P_DC_DCT;
    pDivx3DecParam->alternative_MV = pPictureHeader->alternative_MV;

    return;
}


VOID Divx3_WriteReg(DIVX3_CTX_S *pCtx)
{
    DIVX3_DEC_PARAM_S *pDivx3DecParam;

    pDivx3DecParam = &pCtx->Divx3DecParam;

    return;
}


SINT32 Divx3_DecodeDecide(DIVX3_CTX_S *pCtx)
{
    SINT32  DecMode;
    SINT32  ret = DIVX3_VFMW_TRUE;
    DIVX3_CODECINF *pDivx3CodecInfo;
    IMAGE *pFwdImg;
	UINT32 FrameType;
    
	pDivx3CodecInfo = &pCtx->CodecInfo;
  	DecMode = pCtx->pstExtraData->s32DecMode;
    FrameType = pDivx3CodecInfo->PictureHeader.prediction_type;

    if (DIVX3_VFMW_FALSE == pDivx3CodecInfo->Imgbuf_allocated)
    {
        dprint(PRN_ERROR, "ERROR: No Img buffer is allocated\n");
        return DIVX3_VFMW_FALSE;
    }

    /* 解码模式(IPB,IP,I)的处理 */
    if ( (pDivx3CodecInfo->UsedDecMode == I_MODE || pDivx3CodecInfo->UsedDecMode == DISCARD_MODE) &&
		 (pCtx->pstExtraData->s32DecMode == IP_MODE || pCtx->pstExtraData->s32DecMode == IPB_MODE || 
		 pCtx->pstExtraData->s32DecMode == DISCARD_B_BF_P_MODE) )
    {
        /* I->IP 或 I->IPB都有可能引发参考错误，所以需要找下一个I帧才行 */
        dprint(PRN_CTRL, "----------------- divx3 Imode -> %d ------------------\n", pCtx->pstExtraData->s32DecMode);
        DIVX3_CLEARREFFLAG;
        DIVX3_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过
    }
    pDivx3CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
    switch (pDivx3CodecInfo->UsedDecMode)
    {
        case DISCARD_MODE:
			ret = DIVX3_VFMW_FALSE;
			break;
        case I_MODE:
            if( DIVX3_I_VOP != FrameType)
            {
                ret = DIVX3_VFMW_FALSE;
    	        dprint(PRN_PIC, "-----I_MODE, but FrameType is %d-----\n", FrameType);			
            }
            break;
        case IP_MODE:
        case IPB_MODE:
        case DISCARD_B_BF_P_MODE:
            if((DIVX3_I_VOP != FrameType) && (pDivx3CodecInfo->RefNum < 1))
            {
            	dprint(PRN_PIC, "-----cur framtype is %s, but refnum=%d-----\n", 
        			(FrameType == DIVX3_I_VOP)? "I-frm":"P-frm", 
        			pDivx3CodecInfo->RefNum);
                ret = DIVX3_VFMW_FALSE;
            }
            break;
		default: 
			ret = DIVX3_VFMW_FALSE;
			dprint(PRN_ERROR, "error: DecMode illegal\n");
            break;
    }

    if (ret != DIVX3_VFMW_FALSE)
    {
        /* 如果是P/B帧，要看其参考帧是否超出参考阈值，若超出则不解 */
    	pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pDivx3CodecInfo->FwdFsID);
    	if (DIVX3_I_VOP != FrameType)
    	{
            if ( (NULL == pFwdImg) || (pFwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
            {
            	if(NULL == pFwdImg)
	            {
	            	dprint(PRN_FATAL, "fuction return value is null,%s %d unknow error!!\n",__FUNCTION__,__LINE__);
					return DIVX3_VFMW_FALSE;
	            }
			   	else
			   	{
			   		dprint(PRN_ERROR, "dec P frame, fwd ref err(%d) > ref_thr(%d)\n", pFwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
	    			return DIVX3_VFMW_FALSE;
			   	}
    		}
			else
			{
			    return DIVX3_VFMW_TRUE;
			}
    	}
		else
		{
		    return DIVX3_VFMW_TRUE;
		}
    }
	else
	{
	    return DIVX3_VFMW_FALSE;
	}
}


SINT32 Divx3_GetPictureHeader(BS *pBs, DIVX3_PictureHeader_S *pPictureHeader, UINT32 PrevSwitchRounding)
{
    pPictureHeader->prediction_type = BsGet(pBs, 2);
    if ( (DIVX3_I_VOP != pPictureHeader->prediction_type) &&
         (DIVX3_P_VOP != pPictureHeader->prediction_type)
       )
    {
        return DIVX3_VFMW_FALSE;
    }

    pPictureHeader->quantizer = BsGet(pBs, 5);

    if (pPictureHeader->prediction_type == DIVX3_I_VOP)
    {
        pPictureHeader->rounding_type = 1;
        pPictureHeader->vol_mode = BsGet(pBs, 5);
        if ( (23 != pPictureHeader->vol_mode) &&
             (24 != pPictureHeader->vol_mode) &&
             (26 != pPictureHeader->vol_mode) 
           )
        {
            return DIVX3_VFMW_FALSE;
        }

        pPictureHeader->alternative_I_AC_chrom_DCT = BsShow(pBs, 2);
        switch ( pPictureHeader->alternative_I_AC_chrom_DCT )
        {
        case 0:
        case 1:
            BsSkip(pBs, 1);
            break;
        case 2:
            BsSkip(pBs, 2);
            break;
        case 3:
            BsSkip(pBs, 2);
            break;
        }

        pPictureHeader->alternative_I_AC_lum_DCT = BsShow(pBs, 2);
        switch ( pPictureHeader->alternative_I_AC_lum_DCT )
        {
        case 0:
        case 1:
            BsSkip(pBs, 1);
            break;
        case 2:
            BsSkip(pBs, 2);
            break;
        case 3:
            BsSkip(pBs, 2);
            break;
        }

        pPictureHeader->alternative_I_DC_DCT = BsGet(pBs, 1);
    }
    else
    {
        SINT32 ac_index;
		
        pPictureHeader->switch_rounding = PrevSwitchRounding;
        if (pPictureHeader->switch_rounding)
        {
            pPictureHeader->rounding_type = 1 - pPictureHeader->rounding_type;
        }
        else
        {
            pPictureHeader->rounding_type = 0;
        }
        pPictureHeader->has_skips = BsGet(pBs, 1);

        pPictureHeader->alternative_P_AC_DCT = BsShow(pBs, 2);
        switch ( pPictureHeader->alternative_P_AC_DCT )
        {
        case 0:
        case 1:
            ac_index=0;
            BsSkip(pBs, 1);
            break;
        case 2:
            ac_index=1;
            BsSkip(pBs, 2);
            break;
        case 3:
            ac_index=2;
            BsSkip(pBs, 2);
            break;
        }

        pPictureHeader->alternative_P_DC_DCT = BsGet(pBs, 1);
        pPictureHeader->alternative_MV = BsGet(pBs, 1);
    }    

    return DIVX3_VFMW_TRUE;
}


SINT32 DIVX3DEC_Init(DIVX3_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    DIVX3_CODECINF *pDivx3CodecInfo;
    DIVX3_PictureHeader_S *pPictureHeader;
    SINT32 ImgQueRstMagic;
   
    //初始化
    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    memset(pCtx, 0, sizeof(DIVX3_CTX_S));
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue);
        
    pCtx->pstExtraData = pstExtraData;
    pDivx3CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;

    pDivx3CodecInfo->PrevSwitchRounding = 1;
    pDivx3CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
    pDivx3CodecInfo->Imgbuf_allocated = DIVX3_VFMW_FALSE;

    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }

    return 0;
}


VOID DIVX3DEC_Destroy(DIVX3_CTX_S *pCtx)
{
    DIVX3_CODECINF *pDivx3CodecInfo;

    pDivx3CodecInfo = &pCtx->CodecInfo;
    dprint(PRN_CTRL, "Decoding quits at frm %d\n", pDivx3CodecInfo->FrmCnt);

    return;
}


SINT32 DIVX3DEC_Decode(DIVX3_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    DIVX3_PictureHeader_S TmpPictureHeader = {0};
    DIVX3_PictureHeader_S *pTmpPictureHeader = &TmpPictureHeader;
    DIVX3_PictureHeader_S *pPictureHeader;

    UINT32 CurrPicTotalBits, CurrPicBitOffset;
    UINT32 total_slice_num = 1, slice_mb_height, slice_num;
    UINT32 slice_start_mbn[5] = {0}, slice_end_mbn[5] = {0};
    UINT32 w, h, width, height;
    UINT32 lastpic_vol_mode = 23;
    SINT32 ret;

    IMAGE *pImg;
    FSP_LOGIC_FS_S *pCur, *pFwd;

    DIVX3_DEC_PARAM_S *pDivx3DecParam;
    DIVX3_CODECINF *pDivx3CodecInfo;
    BS *pBs;

    pDivx3DecParam = &pCtx->Divx3DecParam;
    pDivx3CodecInfo = &pCtx->CodecInfo;
    pBs = &pCtx->Bs;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;


    if (NULL == pPacket)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet pointer!\n", pDivx3CodecInfo->FrmCnt);
        return DIVX3_VFMW_FALSE;
    }

    if (0 == pPacket->StreamPack[0].PhyAddr)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet PhyAddr!\n");
        return DIVX3_VFMW_FALSE;
    }

    if (NULL == pPacket->StreamPack[0].VirAddr)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet VirAddr!\n");
        return DIVX3_VFMW_FALSE;
    }

    if (NULL == pPacket->StreamPack[0].VirAddr)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet VirAddr!\n");
        return DIVX3_VFMW_FALSE;
    }

    if (pPacket->StreamPack[0].LenInByte < 10)
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid packet len!\n");
        return DIVX3_VFMW_FALSE;
    }

    memset( pDivx3DecParam, 0, sizeof(DIVX3_DEC_PARAM_S) );

    //if start new pic, length1 should be reserved for VFMW searching and parsing
    pDivx3CodecInfo->BsOffset = 0;
    pDivx3CodecInfo->PacketTail = pPacket->StreamPack[0].LenInByte;

    //adjust bs start address from updated offset
    pDivx3CodecInfo->BsPhyAddr = pPacket->StreamPack[0].PhyAddr + pDivx3CodecInfo->BsOffset;
    pDivx3CodecInfo->BsVirAddr = pPacket->StreamPack[0].VirAddr + pDivx3CodecInfo->BsOffset;
    pDivx3CodecInfo->BsLength  = pPacket->StreamPack[0].LenInByte - pDivx3CodecInfo->BsOffset;
    pDivx3CodecInfo->IsLastSeg = pPacket->StreamPack[0].IsLastSeg;

    if (1 != pPacket->StreamPack[0].IsLastSeg)
    {
        pDivx3CodecInfo->BsPhyAddr1 =  pPacket->StreamPack[1].PhyAddr;
        pDivx3CodecInfo->BsVirAddr1 =  pPacket->StreamPack[1].VirAddr;
        pDivx3CodecInfo->BsLength1 =  pPacket->StreamPack[1].LenInByte;
        pDivx3CodecInfo->IsLastSeg1 = pPacket->StreamPack[1].IsLastSeg;
        if (1 != pPacket->StreamPack[1].IsLastSeg)
        {
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[0].StreamID);
            SM_ReleaseStreamSeg(pCtx->ChanID, pPacket->StreamPack[1].StreamID);
            return DIVX3_VFMW_FALSE;
        }
        //dprint(PRN_DBG,"****PhyAddr = 0x%x len = 0x%x******\n", pDivx3CodecInfo->BsPhyAddr, pDivx3CodecInfo->BsLength);
        //dprint(PRN_DBG,"****PhyAddr1 = 0x%x len1 = 0x%x******\n", pDivx3CodecInfo->BsPhyAddr1, pDivx3CodecInfo->BsLength1);    
    }
    else
    {
        //dprint(PRN_DBG,"****PhyAddr = 0x%x len = 0x%x******\n", pDivx3CodecInfo->BsPhyAddr, pDivx3CodecInfo->BsLength);
        pDivx3CodecInfo->BsPhyAddr1 = 0;
        pDivx3CodecInfo->BsVirAddr1 = 0;
        pDivx3CodecInfo->BsLength1  = 0;
        pDivx3CodecInfo->IsLastSeg1 = 0;
    }

    if ( (pDivx3CodecInfo->BsLength < 10) || (pDivx3CodecInfo->BsLength >= 3*1024*1024) )
    {
        return DIVX3_VFMW_FALSE;
    }

    /*码流管理初始化*/
    if (NULL == pDivx3CodecInfo->BsVirAddr)
    {
        return DIVX3_VFMW_FALSE;
    }
    BsInit(pBs, pDivx3CodecInfo->BsVirAddr, pDivx3CodecInfo->BsLength);


    CurrPicTotalBits = BsResidBits(pBs);

    /*获取图像宽高*/
    w = BsGet(pBs, 32);
    width = 
        ((w) << 24) | \
        (((w) & 0x0000ff00) << 8) | \
        (((w) & 0x00ff0000) >> 8) | \
        (((w) >> 24) & 0x000000ff);
    pTmpPictureHeader->pic_width_in_mb = (width+15)/16;
    pTmpPictureHeader->pic_width_in_pix = width;

    h = BsGet(pBs, 32);
    height = 
        ((h) << 24) | \
        (((h) & 0x0000ff00) << 8) | \
        (((h) & 0x00ff0000) >> 8) | \
        (((h) >> 24) & 0x000000ff);
    pTmpPictureHeader->pic_height_in_mb = (height+15)/16;
    pTmpPictureHeader->pic_height_in_pix = height;

    if ( (width<32) || (height<32) || (width>1920) || (height>1088) )
    {
        dprint(PRN_ERROR, "ERROR: frm %d, Invalid WxH: %dx%d!\n", width, height);
        return DIVX3_VFMW_FALSE;
    }

    /*Picture Header 解码*/
    pTmpPictureHeader->rounding_type = pPictureHeader->rounding_type;
    if ( DIVX3_VFMW_TRUE != Divx3_GetPictureHeader(pBs, pTmpPictureHeader, pDivx3CodecInfo->PrevSwitchRounding) )
    {
        dprint(PRN_ERROR, "Divx3_GetPictureHeader Error!\n");
        return DIVX3_VFMW_FALSE;
    }

    if ( (0 == pDivx3CodecInfo->RefNum) && (DIVX3_I_VOP != pTmpPictureHeader->prediction_type) )
    {
        dprint(PRN_ERROR, "Can't decode from P frame!\n");
        return DIVX3_VFMW_FALSE;
    }

    pTmpPictureHeader->total_mbs = pTmpPictureHeader->pic_width_in_mb*pTmpPictureHeader->pic_height_in_mb;

    //VHB 地址分配
    if ( (DIVX3_VFMW_FALSE == pDivx3CodecInfo->Imgbuf_allocated) ||
         (pTmpPictureHeader->pic_width_in_mb != pPictureHeader->pic_width_in_mb) ||
         (pTmpPictureHeader->pic_height_in_mb != pPictureHeader->pic_height_in_mb) )
    {
		REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pPictureHeader->pic_width_in_mb, pPictureHeader->pic_height_in_mb,\
            pTmpPictureHeader->pic_width_in_mb, pTmpPictureHeader->pic_height_in_mb);        
        DIVX3_CLEARREFFLAG;
        DIVX3_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过 
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		
		if((pTmpPictureHeader->pic_width_in_mb > MAX_IMG_WIDTH_IN_MB) ||
			(pTmpPictureHeader->pic_height_in_mb > MAX_IMG_HEIGHT_IN_MB))
		{
			dprint(PRN_PIC, "pic width/height to large,MbWidth = %d, MbHeight = %d",
				pTmpPictureHeader->pic_width_in_mb,
				pTmpPictureHeader->pic_height_in_mb);
			return DIVX3_VFMW_FALSE;
		}
		
        if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
        {
            if (pDivx3CodecInfo->Imgbuf_allocated == DIVX3_VFMW_FALSE)
            {
                ResetVoQueue(&pCtx->ImageQue);
            }
        }
        else
        {     
            ResetVoQueue(&pCtx->ImageQue); 
        }
        dprint(PRN_ERROR, "new seq size %d * %d\n", pTmpPictureHeader->pic_width_in_mb, pTmpPictureHeader->pic_height_in_mb);
    
        ret = Divx3_ArrangeVHBMem(DIVX3_MAXIMUM_IMAGE_NUM, pCtx, pTmpPictureHeader);
		if(ret != DIVX3_VFMW_TRUE)
		{
			dprint(PRN_ERROR, "Divx3_ArrangeVHBMem err\n"); 
			return DIVX3_VFMW_FALSE;
		}
    }

    if (pTmpPictureHeader->prediction_type != DIVX3_I_VOP)
    {
        lastpic_vol_mode = pPictureHeader->vol_mode;
    }
    memcpy( pPictureHeader, pTmpPictureHeader, sizeof(DIVX3_PictureHeader_S) );
    if (pTmpPictureHeader->prediction_type != DIVX3_I_VOP)
    {
        pPictureHeader->vol_mode = lastpic_vol_mode;
    }

    ret = Divx3_DecodeDecide(pCtx);
    if (ret != DIVX3_VFMW_TRUE)
    {
        dprint(PRN_ERROR, "Divx3_DecodeDecide err\n");   
        return DIVX3_VFMW_FALSE;
    }

    //获取帧存
    if ( DIVX3_VFMW_FALSE == Divx3_GetImageBuffer(pCtx) )
    {
        dprint(PRN_FATAL, "Fatal Error: frm%d, get image buffer failed\n", pDivx3CodecInfo->FrmCnt);
        return DIVX3_VFMW_FALSE;
    }

    /* PTS */
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, pDivx3CodecInfo->CurFsID);
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
        dprint(PRN_ERROR, "FSP_GetFsImagePtr Error!\n");
        return DIVX3_VFMW_FALSE;
    }


    pCur = FSP_GetLogicFs(pCtx->ChanID, pDivx3CodecInfo->CurFsID);
    pFwd = FSP_GetLogicFs(pCtx->ChanID, pDivx3CodecInfo->FwdFsID);

    //dprint(PRN_ALWS,">>>>%d, %d, %d\n", (NULL == pCur->pstDecodeFs), (NULL == pCur->pstTfOutFs), (NULL == pCur->pstDispOutFs) );
    if ((NULL == pCur) || (NULL == pFwd) || (NULL == pCur->pstDecodeFs) || 
        (NULL == pCur->pstTfOutFs) || (NULL == pCur->pstDispOutFs) )
    {
        FSP_ClearLogicFs(pCtx->ChanID, pDivx3CodecInfo->CurFsID, 1);
        dprint(PRN_FATAL, "CurFsID abnormal!\n");
        return DIVX3_VFMW_FALSE;
    }
    else
    {
        pDivx3DecParam->FwdRefPhyAddr   = (NULL != pFwd->pstDecodeFs)? pFwd->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
        pDivx3DecParam->CurPicPhyAddr   = pCur->pstDecodeFs->PhyAddr;
        pDivx3DecParam->CurrPmvPhyAddr = pCur->PmvAddr;

        pDivx3DecParam->DispFramePhyAddr = pCur->pstDispOutFs->PhyAddr;
    }

    dprint(PRN_REF, "dec addr: cur,cur2d,fwd,currpmv,colpmv = %p,%p,%p,%p,%p,%p\n", pDivx3DecParam->CurPicPhyAddr, pDivx3DecParam->DispFramePhyAddr, 
           pDivx3DecParam->FwdRefPhyAddr, pDivx3DecParam->CurrPmvPhyAddr, pDivx3DecParam->ColPmvPhyAddr);

    pDivx3DecParam->DDRStride = pCur->pstDispOutFs->Stride;


    CurrPicBitOffset = CurrPicTotalBits - BsResidBits(pBs);
    pDivx3DecParam->StreamBaseAddr = pPacket->StreamPack[0].PhyAddr & 0xFFFFFFF0;
    CurrPicBitOffset = CurrPicBitOffset + (pPacket->StreamPack[0].PhyAddr & 0x0000000F)*8;
    pDivx3DecParam->StreamPhyAddr[0] = (CurrPicBitOffset/8/16)*16;
    pDivx3DecParam->StreamBitOffset[0] = CurrPicBitOffset - ((CurrPicBitOffset/8/16)*16)*8;
    pDivx3DecParam->StreamLength[0] = BsResidBits(pBs);

    pDivx3DecParam->StreamPhyAddr[1] = 0;
    pDivx3DecParam->StreamBitOffset[1] = 0;
    pDivx3DecParam->StreamLength[1] = 0;


    switch (pPictureHeader->vol_mode)
    {
        case 23:
            total_slice_num = 1;
            slice_mb_height = pPictureHeader->pic_height_in_mb / total_slice_num;
            slice_start_mbn[0] = 0;
            slice_end_mbn[0] = pPictureHeader->total_mbs - 1;
            break;
        case 24:
            total_slice_num = 2;
            slice_mb_height = pPictureHeader->pic_height_in_mb / total_slice_num;
            slice_start_mbn[0] = 0;
            slice_end_mbn[0] = slice_mb_height*pPictureHeader->pic_width_in_mb - 1;
            slice_start_mbn[1] = slice_end_mbn[0] + 1;
            slice_end_mbn[1] = 2 * slice_mb_height*pPictureHeader->pic_width_in_mb - 1;
            if (0 != (pPictureHeader->pic_height_in_mb % 2) )
            {
                total_slice_num++;
                slice_start_mbn[2] = slice_end_mbn[1] + 1;
                slice_end_mbn[2] = pPictureHeader->total_mbs - 1;
            }
            break;
        case 26:
            total_slice_num = 4;
            slice_mb_height = pPictureHeader->pic_height_in_mb / total_slice_num;
            slice_start_mbn[0] = 0;
            slice_end_mbn[0] = slice_mb_height*pPictureHeader->pic_width_in_mb - 1;
            slice_start_mbn[1] = slice_end_mbn[0] + 1;
            slice_end_mbn[1] = 2 * slice_mb_height*pPictureHeader->pic_width_in_mb - 1;
            slice_start_mbn[2] = slice_end_mbn[1] + 1;
            slice_end_mbn[2] = 3 * slice_mb_height*pPictureHeader->pic_width_in_mb - 1;
            slice_start_mbn[3] = slice_end_mbn[2] + 1;
            slice_end_mbn[3] = 4 * slice_mb_height*pPictureHeader->pic_width_in_mb - 1;
            if (0 != (pPictureHeader->pic_height_in_mb % 4) )
            {
                total_slice_num++;
                slice_start_mbn[4] = slice_end_mbn[3] + 1;
                slice_end_mbn[4] = pPictureHeader->total_mbs - 1;
            }
            break;
        default:
            total_slice_num = 1;  //default
            dprint(PRN_ERROR, "vol_mode Error!\n");
            return DIVX3_VFMW_FALSE;
            break;
    }

    Divx3_WritePicMsg(pCtx);

    pDivx3DecParam->TotalSliceNum = total_slice_num;
    for (slice_num=0; slice_num<total_slice_num; slice_num++)
    {
        pDivx3DecParam->slice_start_mbn[slice_num] = slice_start_mbn[slice_num];
        pDivx3DecParam->slice_end_mbn[slice_num] = slice_end_mbn[slice_num];
    }
    Divx3_WriteReg(pCtx);


    pCtx->pDivx3DecParam = &pCtx->Divx3DecParam;
	pCtx->Divx3DecParam.Compress_en = pCtx->pstExtraData->s32Compress_en;
    return DIVX3_VFMW_TRUE;
}


SINT32 DIVX3DEC_RecycleImage(DIVX3_CTX_S *pCtx, UINT32 ImgID)
{
    DIVX3_CODECINF *pDivx3CodecInfo;
    IMAGE *pImg;

    pDivx3CodecInfo = &pCtx->CodecInfo;

    FSP_SetDisplay(pCtx->ChanID, ImgID, 0);
    pImg = FSP_GetFsImagePtr(pCtx->ChanID, ImgID);
    if (NULL != pImg)
    {
        //FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        //pImg->p_usrdat[0] = NULL;
        //FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        //pImg->p_usrdat[1] = NULL;
    }

    return DIVX3_VFMW_TRUE;
}


SINT32 DIVX3DEC_GetRemainImg(DIVX3_CTX_S *pCtx)
{
    DIVX3_CODECINF *pDivx3CodecInfo;
    IMAGE *pImg = NULL;
    SINT32 display_flag;
    SINT32 ret = LAST_OUTPUT_FAIL;

    pDivx3CodecInfo = &pCtx->CodecInfo;

    if (OUTPUT_IN_DEC == pCtx->pstExtraData->s32DecOrderOutput)
    {
        ret = LAST_ALREADY_OUT;
    }
    else
    {
        pImg = FSP_GetFsImagePtr(pCtx->ChanID, pDivx3CodecInfo->CurFsID);
        if (NULL != pImg)
        {
    	   display_flag = FSP_GetDisplay(pCtx->ChanID, pDivx3CodecInfo->CurFsID);
	   if (FS_DISP_STATE_DEC_COMPLETE == display_flag)
	   {
              Divx3_SetImgFormat(pCtx);
	       pImg->last_frame = 1;

              FSP_SetDisplay(pCtx->ChanID, pDivx3CodecInfo->CurFsID, 1);
              if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_DIVX3, pCtx, &pCtx->ImageQue, pImg) )
              {
                  FSP_SetDisplay(pCtx->ChanID, pDivx3CodecInfo->CurFsID, 0);
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


UINT32 DIVX3DEC_VDMPostProc(DIVX3_CTX_S *pCtx, SINT32 ErrRatio, UINT32 SwitchRounding)
{
    DIVX3_CODECINF *pDivx3CodecInfo;
    IMAGE *pCurImg, *pToQueImg;
//    IMAGE *pFwdImg;
    DIVX3_PictureHeader_S *pPictureHeader;

    pDivx3CodecInfo = &pCtx->CodecInfo;
    pPictureHeader = &pCtx->CodecInfo.PictureHeader;

    dprint(PRN_DBG, "ErrRatio = %d\n", ErrRatio);

    Divx3_RecordVFMWState(pCtx);  
    ReleasePacket(VFMW_DIVX3, pCtx);

    pCurImg = FSP_GetFsImagePtr(pCtx->ChanID, pDivx3CodecInfo->CurFsID);
//    pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pDivx3CodecInfo->FwdFsID);

    if (NULL == pCurImg)
    {
        return DIVX3_VFMW_FALSE;
    }

    //pDivx3CodecInfo->LastDecPicCodingType = pDivx3CodecInfo->PictureHeader.prediction_type;
    if (DIVX3_I_VOP == pDivx3CodecInfo->PictureHeader.prediction_type)
    {
        pDivx3CodecInfo->PrevSwitchRounding = SwitchRounding & 0x01;
    }

    /* 处理err_level */
    pCurImg->error_level = ErrRatio;
    pCurImg->error_level = CLIP1(100, (SINT32)(pCurImg->error_level));

    /* 将图像输出到VO队列 */
    dprint(PRN_DBG, "DEBUG: DEC over\n");

    Divx3_SetImgFormat(pCtx);

    if ( I_MODE == pDivx3CodecInfo->UsedDecMode )
    {
        pDivx3CodecInfo->ToQueFsID = pDivx3CodecInfo->CurFsID;
    }
    else
    {
        if (OUTPUT_IN_DEC != pCtx->pstExtraData->s32DecOrderOutput) /* if(显示序输出) */
        {
            pDivx3CodecInfo->ToQueFsID = (pDivx3CodecInfo->RefNum > 0)? pDivx3CodecInfo->FwdFsID: -1;
        }
        else
        {
            pDivx3CodecInfo->ToQueFsID = pDivx3CodecInfo->CurFsID;
        }
    }

    if ( -1 != pDivx3CodecInfo->ToQueFsID )
    {
        pToQueImg = FSP_GetFsImagePtr(pCtx->ChanID, pDivx3CodecInfo->ToQueFsID);
        dprint(PRN_QUEUE, "insert buf %d ref %d\n", pDivx3CodecInfo->ToQueFsID, FSP_GetRef(pCtx->ChanID, pDivx3CodecInfo->ToQueFsID));

        FSP_SetDisplay(pCtx->ChanID, pDivx3CodecInfo->ToQueFsID, 1);
        if (VF_OK != InsertImgToVoQueue(pCtx->ChanID, VFMW_DIVX3, pCtx, &pCtx->ImageQue, pToQueImg))
        {
            FSP_SetDisplay(pCtx->ChanID, pDivx3CodecInfo->ToQueFsID, 0);
            return DIVX3_VFMW_FALSE;
        }
    }

    pDivx3CodecInfo->FrmCnt++;


    /* 参考维护 */
    if ( (DIVX3_P_VOP == pPictureHeader->prediction_type) && (pDivx3CodecInfo->RefNum < 1) )
    {
        return DIVX3_VFMW_FALSE;
    }

    pDivx3CodecInfo->RefNum = 1;

    if (pDivx3CodecInfo->FwdFsID != pDivx3CodecInfo->CurFsID)	
    {
        //这样释放的才是有效参考图
        dprint(PRN_REF, "---------- unref %d\n", pDivx3CodecInfo->FwdFsID);
        FSP_SetRef(pCtx->ChanID, pDivx3CodecInfo->FwdFsID, 0);
        FSP_RemovePmv(pCtx->ChanID, pDivx3CodecInfo->FwdFsID);
    }

    pDivx3CodecInfo->FwdFsID = pDivx3CodecInfo->CurFsID;
    FSP_SetRef(pCtx->ChanID, pDivx3CodecInfo->FwdFsID, 1);
    dprint(PRN_REF, "++++++++++ ref %d\n", pDivx3CodecInfo->CurFsID);

    return DIVX3_VFMW_TRUE;
}


SINT32 DIVX3DEC_GetImageBuffer( DIVX3_CTX_S *pCtx )
{
    DIVX3_CODECINF *pDivx3CodecInfo;
    DIVX3_VOBUFINF *pVOBufInf;

    pDivx3CodecInfo = &pCtx->CodecInfo;
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


#endif //DIVX3_VFMW_ENABLE
