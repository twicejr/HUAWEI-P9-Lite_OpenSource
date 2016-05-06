/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r35FZMEQ2/oCJyWgNpvULJzpUtYptnJUmAQf6e1qjVQiWg3OJx0Sn9OK1FZYs4VxkuKtu
z6rOiK8Hdges+mb12gf5OnkUYo5YP2m8Rjbv7phWIXaBvHB7sKGkM1BLC+D34A==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************** 
*
* Copyright (c) 2009 Hisilicon - All Rights Reserved
*
* File: $postprocess.c$
* Date: $2009/04/08$
* Revision: $v1.0$
* Purpose: VDEC Post Process.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20090408   q45134            Original
*
************************************************************************/

#ifndef __POST_PROCESS_C__
#define __POST_PROCESS_C__


#include "public.h"
#include "vdm_drv.h"
#include "vdm_hal.h"
#include "postprocess.h"
#include "vfmw_ctrl.h"

#ifdef VFMW_HEVC_SUPPORT
extern UINT32  g_TsToRsMap[HEVC_MAX_MB_NUM];
extern UINT8   g_IsDeced[HEVC_MAX_MB_NUM];
extern VOID HEVC_CalcTileMap(HEVC_CTX_S *pHevcCtx);
SINT32 PostPro_GetHevcMbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport, HEVC_DEC_PIC_PARAM_S *pHevcDecParam, SINT32 VdhId);
#endif

extern SINT8  g_RepairDisable;
extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];
extern VDMDRV_PARAM_S g_VdmDrvParam[MAX_VDH_NUM];
SINT32 PostPro_GetRepairParam(VID_STD_E VidStd, VDMHAL_REPAIR_PARAM_S *pRepairParam, VOID *pDecParam, VDMHAL_DEC_REPORT_S *pDecReport, SINT32 VdhId);
SINT32 PostPro_GetH264MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport, UINT32 IsMbaff);
SINT32 PostPro_GetMp24MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport);
SINT32 PostPro_GetAvsMbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport);
SINT32 PostPro_GetVc1MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport);
SINT32 PostPro_GetDivx3MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport);
SINT32 PostPro_GetVp6MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport);
SINT32 PostPro_GetVp8MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport);
VOID PostPro_BubbleSort(VDMHAL_DEC_REPORT_S *pDecReport);
SINT32 PostPro_SetDecReport(VID_STD_E VidStd, VOID *pDecParam, VDMHAL_DEC_REPORT_S *pDecReport);

SINT32 PostPro_GetErrRatio(GetErrRatio_S *pParam)
{
    SINT32    err_ratio = 0;
    
#ifdef OPEN_REPAIR
    VID_STD_E VidStd;
    VOID     *pDecParam = NULL;
    SINT32    VdhId;
    MAKE_DEC_REPORT_S MakeDecReport;
    VDMHAL_REPAIR_PARAM_S *pRepairParam = NULL;
    VDMHAL_DEC_REPORT_S   *pDecReport   = NULL;

    if (NULL == pParam)
    {
       dprint(PRN_FATAL, "PostPro_GetErrRatio: pParam = NULL\n");
       return POSTPRO_FALSE;
    }

    VidStd    = pParam->VidStd;
    pDecParam = pParam->pDecParam;
    VdhId     = pParam->VdhId;

    memset(&MakeDecReport, 0, sizeof(MAKE_DEC_REPORT_S));
    MakeDecReport.VidStd     = VidStd;
    MakeDecReport.VdhId      = VdhId;

    pRepairParam = &(g_RepairParam[VdhId][0]);
    pDecReport   = &(g_DecReport[VdhId]);
    
    MakeDecReport.pDecReport = pDecReport;

    VDMHAL_MakeDecReport(&MakeDecReport);

    err_ratio = PostPro_GetRepairParam(VidStd, pRepairParam, pDecParam, pDecReport, VdhId);
    dprint(PRN_DBG,"err_ratio=%d\n",err_ratio);
#endif

    return err_ratio;
}

RP_STRATAGE_E PostPro_GetRepairStratage(VID_STD_E VidStd, VOID *pDecParam)
{
    if (1 == g_RepairDisable)
    {
        return RP_STRATAGE_DISABLE_REPAIR;
    }
    
    if (VFMW_H264 == VidStd)
    {
        H264_DEC_PIC_PARAM_S *pH264DecParam = (H264_DEC_PIC_PARAM_S *)pDecParam;
        if (0 == pH264DecParam->frame_mbs_only_flag)
        {
            return RP_STRATAGE_DISABLE_REPAIR;
        }
    }
  #ifdef VFMW_MVC_SUPPORT  
    else if (VFMW_MVC == VidStd)
    {
        MVC_DEC_PIC_PARAM_S *pMvcDecParam = (MVC_DEC_PIC_PARAM_S *)pDecParam;
        if (0 == pMvcDecParam->frame_mbs_only_flag)
        {
            return RP_STRATAGE_DISABLE_REPAIR;
        }
    }
  #endif
    return RP_STRATAGE_NORMAL;
}

#ifdef VFMW_MPEG4_SUPPORT  
SINT32 PostPro_CopyYuv(MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId)
{
    VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][0]);
	
    pRepairParam->VahbStride = pMp4DecParam->VahbStride;
    pRepairParam->ImageAddr = pMp4DecParam->DispFramePhyAddr;  //pMp2DecParam->CurPicPhyAddr;
	pRepairParam->Image2DAddr = pMp4DecParam->DispFramePhyAddr;
    pRepairParam->RefImageAddr = pMp4DecParam->FwdRefPicPhyAddr;//pMp2DecParam->FwdRefPhyAddr;
    pRepairParam->CurrPmvAddr = pMp4DecParam->CurPmvPhyAddr;//pMp2DecParam->PmvColmbPhyAddr;
    pRepairParam->ImageWidth = pMp4DecParam->PicWidthInMb;//pMp2DecParam->PicWidthInMb;
    pRepairParam->ImageHeight = pMp4DecParam->PicHeightInMb;//pMp2DecParam->PicHeightInMb;
    pRepairParam->IsFrame = 1;//(3==pMp2DecParam->PictureStructure);
    pRepairParam->ImageCSP = 0;

    pRepairParam->ValidGroupNum = 1;
    pRepairParam->MbGroup[0].StartMbn = 0;
    pRepairParam->MbGroup[0].EndMbn = pRepairParam->ImageWidth*pRepairParam->ImageHeight - 1;

    pRepairParam->Compress_en = pMp4DecParam->Compress_en;
	pRepairParam->Pic_type = 0;
	pRepairParam->FullRepair = 1;
    pRepairParam->CtbSize = 4;
    if (VDMHAL_OK != VDMHAL_PrepareRepair(VFMW_MPEG4, pMp4DecParam, FIRST_REPAIR, VdhId))
    {
        return POSTPRO_FALSE;
	}
    return POSTPRO_TRUE;
}
#endif


#ifdef VFMW_VC1_SUPPORT  
SINT32 PostPro_CopyYuv_Vc1(VC1_DEC_PARAM_S *pVc1DecParam, SINT32 VdhId)
{
    VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][0]);
    UINT32 level = 16;

    if(pVc1DecParam->DispPicWidth > 0 && pVc1DecParam->DispPicWidth <= 2048)
    {
        level = 16;
    }
    else if(pVc1DecParam->DispPicWidth > 2048 && pVc1DecParam->DispPicWidth <= 4096)
    {
        level = 32;
    }
    else if(pVc1DecParam->DispPicWidth > 4096 && pVc1DecParam->DispPicWidth <= 6144)
    {
        level = 48;
    }   
    else if(pVc1DecParam->DispPicWidth > 6144 && pVc1DecParam->DispPicWidth <= 8192)
    {
        level = 64;
    }

    pRepairParam->ImageAddr    = pVc1DecParam->ystaddr_1d;
	pRepairParam->Image2DAddr  = pVc1DecParam->CurFrmImgLuma2dPhyAddr;
    pRepairParam->RefImageAddr = pVc1DecParam->FwdRefAddr;
    pRepairParam->CurrPmvAddr  = pVc1DecParam->CurrColmbAddr;
    pRepairParam->ImageWidth   = pVc1DecParam->RepairWidthInMb;
    pRepairParam->ImageHeight  = pVc1DecParam->RepairHeightInMb;
    pRepairParam->IsFrame =  1;/*强制当前帧类型为帧存储*/  //(3!=pVc1DecParam->picstructure);
    pRepairParam->ImageCSP = 0;
    dprint(PRN_DBG,"pRepairParam->ImageWidth=%d,pRepairParam->ImageHeight=%d\n",pRepairParam->ImageWidth,pRepairParam->ImageHeight);
    pRepairParam->ValidGroupNum = 1;
    pRepairParam->MbGroup[0].StartMbn = 0;
    pRepairParam->MbGroup[0].EndMbn = pRepairParam->ImageWidth*pRepairParam->ImageHeight - 1;//pRepairParam->ImageWidth*(pVc1DecParam->mbheight + 1) - 1;//p
	pRepairParam->rpr_ref_pic_type = 0;/*强制参考帧的类型为帧存储*/  //(pVc1DecParam->ref_pic_type)&0x3;

    pRepairParam->Compress_en = pVc1DecParam->Compress_en;
	pRepairParam->Pic_type = 0;
	pRepairParam->rpr_ref_pic_type = 0;
	pRepairParam->FullRepair = 1;
    pRepairParam->level = level;
    pRepairParam->CtbSize = 4;
    if (VDMHAL_OK != VDMHAL_PrepareRepair(VFMW_VC1, pVc1DecParam, FIRST_REPAIR, VdhId))
    {
        return POSTPRO_FALSE;
    }

    return POSTPRO_TRUE;
}
#endif

#ifdef VFMW_VP6_SUPPORT
SINT32 PostPro_CopyYuv_Vp6(VP6_DEC_PARAM_S *pVp6DecParam, SINT32 VdhId)
{
    VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][0]);

    pRepairParam->ImageAddr = pVp6DecParam->image_curr_recon_addr;
	pRepairParam->Image2DAddr = pVp6DecParam->image_curr_recon_addr;
    pRepairParam->RefImageAddr = pVp6DecParam->image_last_ref_addr;//pMp2DecParam->FwdRefPhyAddr;
    pRepairParam->CurrPmvAddr = pVp6DecParam->CurPmvAddr;//pMp2DecParam->PmvColmbPhyAddr;
    pRepairParam->ImageWidth = pVp6DecParam->PicWidthInMb;//pMp2DecParam->PicWidthInMb;
    pRepairParam->ImageHeight = pVp6DecParam->PicHeightInMb;//pMp2DecParam->PicHeightInMb;
    pRepairParam->IsFrame =  1;/*强制当前帧类型为帧存储*/  //(3!=pVc1DecParam->picstructure);
    pRepairParam->ImageCSP = 0;
    dprint(PRN_DBG,"pRepairParam->ImageWidth=%d,pRepairParam->ImageHeight=%d\n",pRepairParam->ImageWidth,pRepairParam->ImageHeight);
    pRepairParam->ValidGroupNum = 1;
    pRepairParam->MbGroup[0].StartMbn = 0;
    pRepairParam->MbGroup[0].EndMbn = pRepairParam->ImageWidth*pRepairParam->ImageHeight - 1;//pRepairParam->ImageWidth*(pVc1DecParam->mbheight + 1) - 1;//p
	pRepairParam->rpr_ref_pic_type = 0;/*强制参考帧的类型为帧存储*/  //(pVc1DecParam->ref_pic_type)&0x3;

    pRepairParam->Compress_en = pVp6DecParam->Compress_en;
	pRepairParam->Pic_type = 0;
	pRepairParam->rpr_ref_pic_type = 0;
	pRepairParam->FullRepair = 1;
    pRepairParam->CtbSize = 4;
    if (VDMHAL_OK != VDMHAL_PrepareRepair(VFMW_VP6, pVp6DecParam, FIRST_REPAIR, VdhId))
    {
        return POSTPRO_FALSE;
    }

    return POSTPRO_TRUE;
}
#endif

SINT32 PostPro_GetRepairParam(VID_STD_E VidStd, VDMHAL_REPAIR_PARAM_S *pRepairParam, VOID *pDecParam, VDMHAL_DEC_REPORT_S *pDecReport, SINT32 VdhId)
{
    UINT32 i, err_ratio, err_mbs, total_mbs;
#ifdef VFMW_H264_SUPPORT
    UINT32 ref_img_idc, IsMbaff;
    H264_DEC_PIC_PARAM_S *pH264DecParam = NULL;
#endif
#ifdef VFMW_HEVC_SUPPORT
    UINT32 hevc_ref_img_idc;
    HEVC_DEC_SLICE_PARAM_S *pSlice = NULL;
    HEVC_DEC_PIC_PARAM_S *pHevcDecParam = NULL;
#endif
#ifdef VFMW_MVC_SUPPORT
    UINT32 mvc_ref_img_idc, MvcIsMbaff;
    MVC_DEC_PIC_PARAM_S *pMvcDecParam = NULL;
#endif
#ifdef VFMW_MPEG2_SUPPORT
    MP2_DEC_PARAM_S *pMp2DecParam = NULL;   
#endif
#ifdef VFMW_MPEG4_SUPPORT
    MP4_DEC_PARAM_S *pMp4DecParam = NULL;
#endif
#ifdef VFMW_AVS_SUPPORT
    AVS_DEC_PARAM_S *pAvsDecParam = NULL;
#endif
#ifdef VFMW_VC1_SUPPORT    
    VC1_DEC_PARAM_S *pVc1DecParam = NULL;
#endif
#ifdef VFMW_REAL8_SUPPORT
    RV8_DEC_PARAM_S *pRv8DecParam = NULL;
#endif
#ifdef VFMW_REAL9_SUPPORT
    RV9_DEC_PARAM_S *pRv9DecParam = NULL;
#endif
#ifdef VFMW_DIVX3_SUPPORT    
    DIVX3_DEC_PARAM_S *pDivx3DecParam = NULL;
#endif
#ifdef VFMW_VP6_SUPPORT
    VP6_DEC_PARAM_S *pVp6DecParam = NULL;
#endif
#ifdef VFMW_VP8_SUPPORT
    VP8_DEC_PARAM_S *pVp8DecParam = NULL;	
#endif

    pRepairParam->VidStd = VidStd;
    //PostPro_BubbleSort(pDecReport);

    pRepairParam[0].ValidGroupNum = 0;
    pRepairParam[1].ValidGroupNum = 0;
    // 获取修补参数
    switch (VidStd)
    {
    #ifdef VFMW_H264_SUPPORT            
        case VFMW_H264:
            pH264DecParam = (H264_DEC_PIC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pH264DecParam->ImgPhyAddr[pH264DecParam->CurrPicImgIdc];
			pRepairParam->Image2DAddr = pH264DecParam->CurrPicImg2DAddr;
            ref_img_idc = pH264DecParam->pFirstSlice->declist[0][0].img_idc;
            pRepairParam->RefImageAddr = pH264DecParam->ImgPhyAddr[ref_img_idc];
            pRepairParam->CurrPmvAddr = pH264DecParam->PmvPhyAddr[pH264DecParam->CurrPicPmvIdc];
            pRepairParam->ImageWidth = pH264DecParam->pic_width_in_mb;
            pRepairParam->ImageHeight = pH264DecParam->pic_height_in_mb;
            pRepairParam->IsFrame = (0==pH264DecParam->pic_structure);  // ( (0==pH264DecParam->pic_structure) || (3==pH264DecParam->pic_structure) );
            pRepairParam->ImageCSP = (0==pH264DecParam->chroma_format_idc);

            /* 获取ref_img_idc所对应的物理帧存的存储类型(帧存 or 场存) */
            for (i = 0; i < pH264DecParam->ApcSize; i++)
            {
                if (ref_img_idc == pH264DecParam->RefPicFsId[i])
                {
                    pRepairParam->rpr_ref_pic_type = pH264DecParam->RefPicType[i];
                    break;
                }
            }
            IsMbaff = pH264DecParam->mb_adaptive_frame_field_flag && (0==pH264DecParam->pic_structure);

            if (pH264DecParam->NewPicFlag)
            {
                PostPro_GetH264MbGroup(pRepairParam, pDecReport, IsMbaff);
            }
            else
            {
                pDecReport->DecSliceNum = 0;
            }

            if (pRepairParam->ImageAddr == pRepairParam->RefImageAddr)
            {
                for (i=0; i<pH264DecParam->ImgSlotNum; i++)
                {
                    if (pRepairParam->ImageAddr != pH264DecParam->ImgPhyAddr[i])
                    {
                        pRepairParam->RefImageAddr = pH264DecParam->ImgPhyAddr[i];
                        break;
                    }
                }
            }
            if (0==pH264DecParam->pic_structure)
            {
				pRepairParam->Pic_type = 0;
            }
            else if (1 == pH264DecParam->pic_structure)
            {
            	pRepairParam->Pic_type = 1;
            }
            else if (2 == pH264DecParam->pic_structure)
            {
            	pRepairParam->Pic_type = 2;
            }
            else if (3 == pH264DecParam->pic_structure) //自适应帧
            {
            	pRepairParam->Pic_type = 0;
            }
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pH264DecParam->Compress_en;
			pRepairParam->CtbSize = 4;
            break;
    #endif    
	#ifdef VFMW_HEVC_SUPPORT  
		case VFMW_HEVC:
			pHevcDecParam = (HEVC_DEC_PIC_PARAM_S *)pDecParam;
			pRepairParam->ImageAddr = pHevcDecParam->ImgPhyAddr[pHevcDecParam->CurrPicImgIdc];
			pRepairParam->Image2DAddr = pHevcDecParam->CurrPicImg2DAddr;
			pSlice = (HEVC_DEC_SLICE_PARAM_S *)pHevcDecParam->pFirstSlice;
			//list0 的第0个refpic l00214825
			hevc_ref_img_idc = pSlice->Idx2Apc[0][0];
			pRepairParam->RefImageAddr = pHevcDecParam->ImgPhyAddr[hevc_ref_img_idc];
			pRepairParam->CurrPmvAddr = pHevcDecParam->PmvPhyAddr[pHevcDecParam->CurrPicPmvIdc];
			pRepairParam->CtbSize = pHevcDecParam->CtbLog2SizeY;			
            pRepairParam->Compress_en = pHevcDecParam->Compress_en;   
			pRepairParam->ImageWidth = (pHevcDecParam->pic_width_in_luma_samples+(1<<(pRepairParam->CtbSize))-1)/(1<<(pRepairParam->CtbSize));
			pRepairParam->ImageHeight = (pHevcDecParam->pic_height_in_luma_samples+(1<<(pRepairParam->CtbSize))-1)/(1<<(pRepairParam->CtbSize));
			pRepairParam->tiles_enabled_flag = pHevcDecParam->tiles_enabled_flag;
			pRepairParam->IsFrame = 1;	// ( (0==pH264DecParam->pic_structure) || (3==pH264DecParam->pic_structure) );
			pRepairParam->ImageCSP = (0==pHevcDecParam->chroma_format_idc);
			if (pHevcDecParam->NewPicFlag)
			{
                PostPro_GetHevcMbGroup(pRepairParam, pDecReport, pHevcDecParam, VdhId);
			}
			else
			{
				pDecReport->DecSliceNum = 0;
			}
			
			if (pRepairParam->ImageAddr == pRepairParam->RefImageAddr)
			{
				for (i=0; i<pHevcDecParam->ImgSlotNum; i++)
				{
					if (pRepairParam->ImageAddr != pHevcDecParam->ImgPhyAddr[i])
					{
						pRepairParam->RefImageAddr = pHevcDecParam->ImgPhyAddr[i];
						break;
					}
				}
			}
			pRepairParam->Pic_type = 0;
            break;
    #endif    
    #ifdef VFMW_MVC_SUPPORT            
        case VFMW_MVC:
            pMvcDecParam = (MVC_DEC_PIC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pMvcDecParam->ImgPhyAddr[pMvcDecParam->CurrPicImgIdc];
	     pRepairParam->Image2DAddr = pMvcDecParam->CurrPicImg2DAddr;
            mvc_ref_img_idc = pMvcDecParam->pFirstSlice->declist[0][0].img_idc;
            pRepairParam->RefImageAddr = pMvcDecParam->ImgPhyAddr[mvc_ref_img_idc];
            pRepairParam->CurrPmvAddr = pMvcDecParam->PmvPhyAddr[pMvcDecParam->CurrPicPmvIdc];
            pRepairParam->ImageWidth = pMvcDecParam->pic_width_in_mb;
            pRepairParam->ImageHeight = pMvcDecParam->pic_height_in_mb;
            pRepairParam->IsFrame = (0==pMvcDecParam->pic_structure);  // ( (0==pH264DecParam->pic_structure) || (3==pH264DecParam->pic_structure) );
            pRepairParam->ImageCSP = (0==pMvcDecParam->chroma_format_idc);

            /* 获取ref_img_idc所对应的物理帧存的存储类型(帧存 or 场存) */
            for (i = 0; i < pMvcDecParam->ApcSize; i++)
            {
                if (mvc_ref_img_idc == pMvcDecParam->RefPicFsId[i])
                {
                    pRepairParam->rpr_ref_pic_type = pMvcDecParam->RefPicType[i];
                    break;
                }
            }
            MvcIsMbaff = pMvcDecParam->mb_adaptive_frame_field_flag && (0==pMvcDecParam->pic_structure);

            if (pMvcDecParam->NewPicFlag)
            {
                PostPro_GetH264MbGroup(pRepairParam, pDecReport, MvcIsMbaff);
            }
            else
            {
                pDecReport->DecSliceNum = 0;
            }

            if (pRepairParam->ImageAddr == pRepairParam->RefImageAddr)
            {
                for (i=0; i<pMvcDecParam->ImgSlotNum; i++)
                {
                    if (pRepairParam->ImageAddr != pMvcDecParam->ImgPhyAddr[i])
                    {
                        pRepairParam->RefImageAddr = pMvcDecParam->ImgPhyAddr[i];
                        break;
                    }
                }
            }
            if (0==pMvcDecParam->pic_structure)
            {
				pRepairParam->Pic_type = 0;
            }
            else if (1 == pMvcDecParam->pic_structure)
            {
            	pRepairParam->Pic_type = 1;
            }
            else if (2 == pMvcDecParam->pic_structure)
            {
            	pRepairParam->Pic_type = 2;
            }
            else if (3 == pMvcDecParam->pic_structure) //自适应帧
            {
            	pRepairParam->Pic_type = 0;
            }
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pMvcDecParam->Compress_en;
			pRepairParam->CtbSize = 4;
            break;
    #endif   
    #ifdef VFMW_MPEG2_SUPPORT    
        case VFMW_MPEG2:
            pMp2DecParam = (MP2_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pMp2DecParam->CurPicPhyAddr;
			pRepairParam->Image2DAddr = pMp2DecParam->DispFramePhyAddr;
            pRepairParam->RefImageAddr = pMp2DecParam->FwdRefPhyAddr;
            pRepairParam->CurrPmvAddr = pMp2DecParam->PmvColmbPhyAddr;
            pRepairParam->ImageWidth = pMp2DecParam->PicWidthInMb;
            pRepairParam->ImageHeight = pMp2DecParam->PicHeightInMb;
            pRepairParam->IsFrame = (3==pMp2DecParam->PictureStructure);
            pRepairParam->ImageCSP = 0;
			
			if(1==pMp2DecParam->PictureStructure)
            {
				pRepairParam->Pic_type = 1;
            }
            else if (2 == pMp2DecParam->PictureStructure)
            {
            	pRepairParam->Pic_type = 2;
            }
            else if (3 == pMp2DecParam->PictureStructure)
            {
            	pRepairParam->Pic_type = 0;
            }
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pMp2DecParam->Compress_en;
			pRepairParam->CtbSize = 4;
            PostPro_GetMp24MbGroup(pRepairParam, pDecReport);
            break;
    #endif    
    #ifdef VFMW_MPEG4_SUPPORT    
        case VFMW_MPEG4:
            pMp4DecParam = (MP4_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pMp4DecParam->CurPicPhyAddr;
			pRepairParam->Image2DAddr = pMp4DecParam->DispFramePhyAddr;
            pRepairParam->RefImageAddr = pMp4DecParam->FwdRefPicPhyAddr;
            pRepairParam->CurrPmvAddr = pMp4DecParam->CurPmvPhyAddr;
            pRepairParam->ImageWidth = pMp4DecParam->PicWidthInMb;
            pRepairParam->ImageHeight = pMp4DecParam->PicHeightInMb;
            pRepairParam->IsFrame = 1;
            pRepairParam->ImageCSP = 0;
			pRepairParam->Pic_type = 0;
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pMp4DecParam->Compress_en;
			pRepairParam->CtbSize = 4;
            PostPro_GetMp24MbGroup(pRepairParam, pDecReport);
            break;
    #endif    
    #ifdef VFMW_AVS_SUPPORT    
        case VFMW_AVS:
            pAvsDecParam = (AVS_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pAvsDecParam->CurPicAddr;
            pRepairParam->Image2DAddr =  pAvsDecParam->rcn_address;
            pRepairParam->RefImageAddr = pAvsDecParam->FwdRefPic0Addr;
            pRepairParam->CurrPmvAddr = pAvsDecParam->CurPmvAddr;
            pRepairParam->ImageWidth = pAvsDecParam->PicWidthInMb;
            pRepairParam->ImageHeight = pAvsDecParam->PicHeightInMb;
            pRepairParam->IsFrame = (3==pAvsDecParam->PicStruct);            
            pRepairParam->ImageCSP = 0;
            pRepairParam[1].ImageAddr    = pRepairParam->ImageAddr; // + pDecReport->ImgStride;
            pRepairParam[1].RefImageAddr = pRepairParam->RefImageAddr;
            pRepairParam[1].CurrPmvAddr  = pRepairParam->CurrPmvAddr + (pRepairParam->ImageHeight/2) * pDecReport->ImgStride * 9;
            pRepairParam[1].ImageWidth   = pRepairParam->ImageWidth;
            pRepairParam[1].ImageHeight  = pRepairParam->ImageHeight;
            pRepairParam[1].IsFrame      = pRepairParam->IsFrame;
            pRepairParam[1].ImageCSP     = pRepairParam->ImageCSP;
            if(3==pAvsDecParam->PicStruct)
            {
                pRepairParam->Pic_type = 0;
            }
            else if (1 == pAvsDecParam->PicStruct)
            {
                pRepairParam->Pic_type = 1;
            }
            //pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
            pRepairParam->Compress_en = pAvsDecParam->Compress_en;
            pRepairParam->CtbSize = 4;
            pRepairParam[1].Compress_en = pAvsDecParam->Compress_en;
            pRepairParam[1].CtbSize = 4;
            PostPro_GetAvsMbGroup(pRepairParam, pDecReport);
            break;
    #endif    
    #ifdef VFMW_REAL8_SUPPORT    
        case VFMW_REAL8:
            pRv8DecParam = (RV8_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pRv8DecParam->CurPicPhyAddr;
            pRepairParam->RefImageAddr = pRv8DecParam->FwdRefPhyAddr;
            pRepairParam->CurrPmvAddr = pRv8DecParam->CurrPmvPhyAddr;
            pRepairParam->ImageWidth = pRv8DecParam->PicWidthInMb;
            pRepairParam->ImageHeight = pRv8DecParam->PicHeightInMb;
            pRepairParam->IsFrame = 1;
            pRepairParam->ImageCSP = 0;

			pRepairParam->Pic_type = 0;
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pRv8DecParam->Compress_en;
			pRepairParam->CtbSize = 4;
            PostPro_GetMp24MbGroup(pRepairParam, pDecReport);
            break;
    #endif    
    #ifdef VFMW_REAL9_SUPPORT    
        case VFMW_REAL9:
            pRv9DecParam = (RV9_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pRv9DecParam->CurPicPhyAddr;
            pRepairParam->RefImageAddr = pRv9DecParam->FwdRefPhyAddr;
            pRepairParam->CurrPmvAddr = pRv9DecParam->CurrPmvPhyAddr;
            pRepairParam->ImageWidth = pRv9DecParam->PicWidthInMb;
            pRepairParam->ImageHeight = pRv9DecParam->PicHeightInMb;
            pRepairParam->IsFrame = 1;
            pRepairParam->ImageCSP = 0;
			pRepairParam->Pic_type = 0;
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pRv9DecParam->Compress_en;
			pRepairParam->CtbSize = 4;
            PostPro_GetMp24MbGroup(pRepairParam, pDecReport);
            break;
    #endif            
    #ifdef VFMW_DIVX3_SUPPORT        
        case VFMW_DIVX3:
            pDivx3DecParam = (DIVX3_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pDivx3DecParam->CurPicPhyAddr;
            pRepairParam->RefImageAddr = pDivx3DecParam->FwdRefPhyAddr;
            pRepairParam->CurrPmvAddr = pDivx3DecParam->CurrPmvPhyAddr;
            pRepairParam->ImageWidth = pDivx3DecParam->PicWidthInMb;
            pRepairParam->ImageHeight = pDivx3DecParam->PicHeightInMb;
            pRepairParam->IsFrame = 1;
            pRepairParam->ImageCSP = 0;
			pRepairParam->Pic_type = 0;
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pDivx3DecParam->Compress_en;
			pRepairParam->CtbSize = 4;
            PostPro_GetDivx3MbGroup(pRepairParam, pDecReport);
            break;
    #endif    
    #ifdef VFMW_VC1_SUPPORT            
        case VFMW_VC1:
            pVc1DecParam = (VC1_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pVc1DecParam->ystaddr_1d;
	        pRepairParam->Image2DAddr = pVc1DecParam->CurFrmImgLuma2dPhyAddr;
            pRepairParam->RefImageAddr = pVc1DecParam->FwdRefAddr;
            pRepairParam->CurrPmvAddr = pVc1DecParam->CurrColmbAddr;
            pRepairParam->ImageWidth = pVc1DecParam->mbwidth +1;
            pRepairParam->ImageHeight = pVc1DecParam->mbheight +1;
            pRepairParam->IsFrame = (pVc1DecParam->fcm==0)||(pVc1DecParam->fcm==2);
            pRepairParam->ImageCSP = 0;
            PostPro_GetVc1MbGroup(pRepairParam, pDecReport);
	        pRepairParam->rpr_ref_pic_type = (pVc1DecParam->ref_pic_type)&0x3;
			if(1==pRepairParam->IsFrame)
			{
				pRepairParam->Pic_type = 0;
            }
            else if (3 == pVc1DecParam->fcm && 0 == pVc1DecParam->curparity)
			{
			    pRepairParam->Pic_type = 1;
            }
            else if (3 == pVc1DecParam->fcm && 1 == pVc1DecParam->curparity)
			{
				pRepairParam->Pic_type = 2;
			}
			pRepairParam->CtbSize = 4;
			pRepairParam->Compress_en = pVc1DecParam->Compress_en;
	     break;
    #endif
    #ifdef VFMW_VP6_SUPPORT    
        case VFMW_VP6:
        case VFMW_VP6A:
        case VFMW_VP6F:
            pVp6DecParam = (VP6_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pVp6DecParam->image_curr_recon_addr;
            pRepairParam->Image2DAddr = pVp6DecParam->image_curr_recon_addr;
            pRepairParam->RefImageAddr = pVp6DecParam->image_last_ref_addr;
            pRepairParam->CurrPmvAddr = pVp6DecParam->CurPmvAddr;
            pRepairParam->ImageWidth = pVp6DecParam->PicWidthInMb;
            pRepairParam->ImageHeight = pVp6DecParam->PicHeightInMb;
            pRepairParam->IsFrame = 1;//(pVp6DecParam->fcm==0)||(pVp6DecParam->fcm==2);
            pRepairParam->ImageCSP = 0;
            PostPro_GetVp6MbGroup(pRepairParam, pDecReport);
            pRepairParam->rpr_ref_pic_type = 0;//(pVp6DecParam->ref_pic_type)&0x3;
			pRepairParam->Pic_type = 0;
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pVp6DecParam->Compress_en;            
			pRepairParam->CtbSize = 4;
            break;		 
    #endif    
    #ifdef VFMW_VP8_SUPPORT    
        case VFMW_VP8:
            pVp8DecParam = (VP8_DEC_PARAM_S *)pDecParam;
            pRepairParam->ImageAddr = pVp8DecParam->image_curr_rcn_addr;
	        pRepairParam->Image2DAddr = pVp8DecParam->image_curr_rcn_addr;
            pRepairParam->RefImageAddr = pVp8DecParam->image_last_ref_addr;
            pRepairParam->CurrPmvAddr = pVp8DecParam->CurrPmvAddr;
            pRepairParam->ImageWidth = pVp8DecParam->pic_width_in_mb;
            pRepairParam->ImageHeight = pVp8DecParam->pic_height_in_mb;
            pRepairParam->IsFrame = 1;
            pRepairParam->ImageCSP = 0;
			pRepairParam->Pic_type = 0;
			//pRepairParam->rpr_ref_pic_type = pRepairParam->Pic_type;
			pRepairParam->Compress_en = pVp8DecParam->Compress_en;   
			pRepairParam->CtbSize = 4;
            PostPro_GetVp8MbGroup(pRepairParam, pDecReport);
	        break;		 
    #endif    
        default :
            dprint(PRN_FATAL, "%s %d VidStd Err!\n", __func__, __LINE__);
            break;
    }

    err_mbs = 0;
    total_mbs = pRepairParam->ImageWidth * pRepairParam->ImageHeight;

    for (i = 0; i < pRepairParam[0].ValidGroupNum; i++)
    {
        dprint(PRN_DBG,"pRepairParam[0].MbGroup[i].EndMbn=%d,pRepairParam[0].MbGroup[i].StartMbn=%d\n",pRepairParam[0].MbGroup[i].EndMbn,pRepairParam[0].MbGroup[i].StartMbn);
        err_mbs += (pRepairParam[0].MbGroup[i].EndMbn - pRepairParam[0].MbGroup[i].StartMbn + 1);
    }

    for (i = 0; i < pRepairParam[1].ValidGroupNum; i++)
    {
        err_mbs += (pRepairParam[1].MbGroup[i].EndMbn - pRepairParam[1].MbGroup[i].StartMbn + 1);
    }

    if (total_mbs == 0)
    {
        err_ratio = 0;
    }
    else
    {
        err_ratio = CLIP1(100, (UINT32)(((err_mbs * 100) / total_mbs)) );
    }
    pDecReport->DecSliceNum = 0;
    dprint(PRN_DBG,"total_mbs=%d,err_mbs=%d\n",total_mbs,err_mbs);

    return err_ratio;
}

#ifdef VFMW_HEVC_SUPPORT
//需要考虑tile的情况
SINT32 PostPro_GetHevcMbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport, HEVC_DEC_PIC_PARAM_S *pHevcDecParam, SINT32 VdhId)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    UINT32 i,j,k;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>MAX_UP_MSG_SLICE_NUM) )
    {
       dprint(PRN_FATAL, "DecSliceNum(=%d) out of range!\n",pDecReport->DecSliceNum);
       return POSTPRO_FALSE;
    }

    total_mbn = pRepairParam->ImageWidth * pRepairParam->ImageHeight;

    pRepairParam->ValidGroupNum = 0;
	pRepairParam->FullRepair = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;

	// tile情况特殊处理
	if (pRepairParam->tiles_enabled_flag)
	{
		UINT32 RsAddr;
		UINT32 start_repair_mb;
		UINT32 end_repair_mb;  
        HEVC_CalcTileMap(&s_pstVfmwChan[g_VdmDrvParam[VdhId].ChanId]->stSynCtx.unSyntax.stHevcCtx);
        
		for (i = 0; i < pDecReport->DecSliceNum; i++)
		{
			for (j = pDecReport->SliceMbRange[i][0]; j <= pDecReport->SliceMbRange[i][1];j++)
			{
                if (pDecReport->SliceMbRange[i][0] > total_mbn || pDecReport->SliceMbRange[i][1] > total_mbn)
                {
                    continue;
                }

                RsAddr = g_TsToRsMap[j];
                g_IsDeced[RsAddr] = 1;
			}				
		}

        //通过slice遍历，如果某个slice有错误，整个slice都置为错误
        for (i=0;i<pHevcDecParam->NumSlicePara;i++)
        {
            for (j = pHevcDecParam->SliceGroup[i][0]; j <= pHevcDecParam->SliceGroup[i][1]; j++)
            {
                if (g_IsDeced[g_TsToRsMap[j]] == 0)
                {
                    for (k = pHevcDecParam->SliceGroup[i][0]; k <= pHevcDecParam->SliceGroup[i][1]; k++)
                    {
                        g_IsDeced[g_TsToRsMap[k]] = 0;
                    }

                    break;
        		}
        	}	
        }

		i = 0;

        while (i < total_mbn)
        {
            //当前ctb解码正常
            if (g_IsDeced[i] == 1)
            {
                i++;
            }
            else
            {
                start_repair_mb = i;

                while ((i + 1 < total_mbn) && (g_IsDeced[i + 1] == 0))
                {
                    i++;
                }

                end_repair_mb = i;

				pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = start_repair_mb;	
				pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = end_repair_mb;
				pRepairParam->ValidGroupNum++;
				i++;
			}

			if (pRepairParam->ValidGroupNum >(MAX_UP_MSG_SLICE_NUM - 1))
			{
				dprint(PRN_ERROR,"pRepairParam->ValidGroupNum >(MAX_UP_MSG_SLICE_NUM - 1)\n");
				pRepairParam->MbGroup[0].StartMbn = 0;	
				pRepairParam->MbGroup[0].EndMbn = total_mbn-1;
				pRepairParam->ValidGroupNum = 1;
				return POSTPRO_TRUE;
			}
		}	
	}
	else
	{
		pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
		pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;	 
		for (i = 0; i <= pDecReport->DecSliceNum; i++)
		{
			 curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];// slice起始宏块 l00214825
			 curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];// slice 结束宏块 l00214825
			 if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) || 
				(curr_slice_start_mbn > curr_slice_end_mbn) )
			 {
				 continue;
			 }
			 else
			 {
    			 if (old_slice_end_mbn > curr_slice_start_mbn)
    			 {
    				 old_slice_end_mbn = old_slice_start_mbn;
    			 }
    	
    			 //中间有宏块没有被解码 即产生了错误
    			 if ( (old_slice_end_mbn+1) < curr_slice_start_mbn )
    			 {
    				 //dprint(PRN_ERROR,"(old_slice_end_mbn+1)(%d) < curr_slice_start_mbn(%d)\n", old_slice_end_mbn+1, curr_slice_start_mbn);
    			 
    				 if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
    				 {
    					 dprint(PRN_ERROR, "%s:0 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_SLICE_NUM - 1)\n", __func__, pRepairParam->ValidGroupNum);
    					 return POSTPRO_FALSE;
    				 }
    	
    				 //如果有错误, 修补起始是old_slice_start_mbn 而不是old_slice_end_mbn
    				 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0);
    				 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn	 = curr_slice_start_mbn - 1;
    				 
    				 /* z56361,20110928: old_slice如果发生了错误，上面的做法是有错即报全错. 同州反馈如此处理无法将轻微错误和完全错误区分开来，
    					这样如果码流有轻微错误也会导致大面积卡顿.
    					修改为: 从报错处向前回溯100个宏块，再之前的宏块视为正确 */
    				 if ((old_slice_end_mbn - 100) > pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn)
    				 {
    					 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = (old_slice_end_mbn - 100);
    				 }
    	
    				 // 统计validGroupNum  l00214825
    				 pRepairParam->ValidGroupNum++;
    			 }
				 /*add by l00225186
				   如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
				   只有一个宏块出错的话，不修补
				 */
				 if(i == (pDecReport->DecSliceNum - 1))
				 {
					 if(pDecReport->SliceMbRange[i][1] < total_mbn - 1)
					 {
        				 if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
        				 {
    					     dprint(PRN_ERROR, "%s:1 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_SLICE_NUM - 1)\n", __func__, pRepairParam->ValidGroupNum);
        					 return POSTPRO_FALSE;
        				 }
						 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[i][1];
						 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;
					  
						 pRepairParam->ValidGroupNum++;
						 return POSTPRO_TRUE;
					}
				 }
				 old_slice_start_mbn = curr_slice_start_mbn;
				 old_slice_end_mbn	 = curr_slice_end_mbn;
			 }
		}
	}

    return POSTPRO_TRUE;
}
#endif

SINT32 PostPro_GetH264MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport, UINT32 IsMbaff)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    UINT16 SliceMbRange_Tmp[MAX_UP_MSG_SLICE_NUM][2];
    UINT32 DecSliceNum_Tmp, DoubleImageWidth, doublelines0, doublelines1, mbsurplus0, mbsurplus1;
    UINT32 i, j, too_many_slice = 0;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>MAX_UP_MSG_SLICE_NUM) )
    {
       dprint(PRN_FATAL, "DecSliceNum(=%d) out of range!\n",pDecReport->DecSliceNum);
       return POSTPRO_FALSE;
    }

    total_mbn = pRepairParam->ImageWidth * pRepairParam->ImageHeight;

    if (IsMbaff)  // MBAFF
    {
        DoubleImageWidth = 2 * pRepairParam->ImageWidth;
        DecSliceNum_Tmp = pDecReport->DecSliceNum;
        for (i = 0; i < pDecReport->DecSliceNum; i++)
        {
            SliceMbRange_Tmp[i][0] = pDecReport->SliceMbRange[i][0];
            SliceMbRange_Tmp[i][1] = pDecReport->SliceMbRange[i][1];
        }

        j = 0;
        for (i = 0; i < DecSliceNum_Tmp; i++)
        {
            SliceMbRange_Tmp[i][0] &= 0xFFFFFFFE;
            SliceMbRange_Tmp[i][1] |= 0x00000001;

            if (DoubleImageWidth == 0)
            {
                break;
            }
			
            if ( 1 < (SliceMbRange_Tmp[i][0] % DoubleImageWidth) )  // NOT start from left most
            {
                if ( (DoubleImageWidth-2) > (SliceMbRange_Tmp[i][1] % DoubleImageWidth) )  // NOT end at right most
                {
                    doublelines0 = SliceMbRange_Tmp[i][0] / DoubleImageWidth;
                    doublelines1 = SliceMbRange_Tmp[i][1] / DoubleImageWidth;
                    mbsurplus0 = (SliceMbRange_Tmp[i][0] % DoubleImageWidth) / 2;
                    mbsurplus1 = (SliceMbRange_Tmp[i][1] % DoubleImageWidth) / 2;

                    if (doublelines1 - doublelines0 >= 1)
                    {
                        pDecReport->SliceMbRange[j][0] = doublelines0 * DoubleImageWidth + mbsurplus0;
                        pDecReport->SliceMbRange[j][1] = doublelines0 * DoubleImageWidth + pRepairParam->ImageWidth - 1;
                        j++;
                        if (j>=MAX_UP_MSG_SLICE_NUM)
                        {
                            too_many_slice = 1;
                        	break;
                        }

                        pDecReport->SliceMbRange[j][0] = doublelines0 * DoubleImageWidth + pRepairParam->ImageWidth + mbsurplus0;
                        pDecReport->SliceMbRange[j][1] = doublelines1 * DoubleImageWidth + mbsurplus1;
                        j++;
                        if (j>=MAX_UP_MSG_SLICE_NUM)
                        {
                            too_many_slice = 1;
                        	break;
                        }

                        pDecReport->SliceMbRange[j][0] = doublelines1 * DoubleImageWidth + pRepairParam->ImageWidth;
                        pDecReport->SliceMbRange[j][1] = pDecReport->SliceMbRange[j][0] + mbsurplus1;
                        j++;
                        if (j>=MAX_UP_MSG_SLICE_NUM)
                        {
                            too_many_slice = 1;
                        	break;
                        }
                    }
                    else
                    {
                        pDecReport->SliceMbRange[j][0] = doublelines0 * DoubleImageWidth + mbsurplus0;
                        pDecReport->SliceMbRange[j][1] = doublelines0 * DoubleImageWidth + mbsurplus1;
                        j++;
                        if (j>=MAX_UP_MSG_SLICE_NUM)
                        {
                            too_many_slice = 1;
                        	break;
                        }

                        pDecReport->SliceMbRange[j][0] = doublelines0 * DoubleImageWidth + pRepairParam->ImageWidth + mbsurplus0;
                        pDecReport->SliceMbRange[j][1] = doublelines1 * DoubleImageWidth + pRepairParam->ImageWidth + mbsurplus1;
                        j++;
                        if (j>=MAX_UP_MSG_SLICE_NUM)
                        {
                            too_many_slice = 1;
                        	break;
                        }
                    }

                }
                else  // end at right most
                {
                    doublelines0 = SliceMbRange_Tmp[i][0] / DoubleImageWidth;
                    mbsurplus0 = (SliceMbRange_Tmp[i][0] % DoubleImageWidth) / 2;
                    pDecReport->SliceMbRange[j][0] = doublelines0 * DoubleImageWidth + mbsurplus0;
                    pDecReport->SliceMbRange[j][1] = doublelines0 * DoubleImageWidth + pRepairParam->ImageWidth - 1;
                    j++;
                    if (j>=MAX_UP_MSG_SLICE_NUM)
                    {
                        too_many_slice = 1;
                    	break;
                    }

                    pDecReport->SliceMbRange[j][0] = doublelines0 * DoubleImageWidth + pRepairParam->ImageWidth + mbsurplus0;
                    pDecReport->SliceMbRange[j][1] = SliceMbRange_Tmp[i][1];
                    j++;
                    if (j>=MAX_UP_MSG_SLICE_NUM)
                    {
                        too_many_slice = 1;
                    	break;
                    }
                }
            }
            else  // start from left most
            {
                if ( (DoubleImageWidth-2) > (SliceMbRange_Tmp[i][1] % DoubleImageWidth) )  // NOT end at right most
                {
                    doublelines1 = SliceMbRange_Tmp[i][1] / DoubleImageWidth;
                    mbsurplus1 = (SliceMbRange_Tmp[i][1] % DoubleImageWidth) / 2;
                    pDecReport->SliceMbRange[j][0] = SliceMbRange_Tmp[i][0];
                    pDecReport->SliceMbRange[j][1] = doublelines1 * DoubleImageWidth + mbsurplus1;
                    j++;
                    if (j>=MAX_UP_MSG_SLICE_NUM)
                    {
                        too_many_slice = 1;
                    	break;
                    }

                    pDecReport->SliceMbRange[j][0] = doublelines1 * DoubleImageWidth + pRepairParam->ImageWidth;
                    pDecReport->SliceMbRange[j][1] = pDecReport->SliceMbRange[j][0] + mbsurplus1;
                    j++;
                    if (j>=MAX_UP_MSG_SLICE_NUM)
                    {
                        too_many_slice = 1;
                    	break;
                    }
                }
                else  // end at right most
                {
                    pDecReport->SliceMbRange[j][0] = SliceMbRange_Tmp[i][0];
                    pDecReport->SliceMbRange[j][1] = SliceMbRange_Tmp[i][1];
                    j++;
                    if (j>=MAX_UP_MSG_SLICE_NUM)
                    {
                        too_many_slice = 1;
                    	break;
                    }
                }
            }
        }

        if (1 == too_many_slice)
        {
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = total_mbn - 1;
        }
        else
        {
        	pDecReport->DecSliceNum = j;
        }
        #if 0
        dprint(PRN_UPMSG, "\n***** H.264 MBAFF UpMsg Before Bubble, DecSliceNum=%d\n", pDecReport->DecSliceNum);
        for (i = 0; i < pDecReport->DecSliceNum; i++)
        {
            dprint(PRN_UPMSG, "\n***** UpMsg [start_mbn, end_mbn]=[%d, %d]\n", pDecReport->SliceMbRange[i][0], pDecReport->SliceMbRange[i][1]);
        }
        #endif
        PostPro_BubbleSort(pDecReport);
    }

    pRepairParam->ValidGroupNum = 0;
    pRepairParam->FullRepair = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;

    pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;    

    for (i = 0; i <= pDecReport->DecSliceNum; i++)
    {
         curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];
         curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];

         if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) || 
            (curr_slice_start_mbn > curr_slice_end_mbn) )
         {
             continue;
         }
         else
         {
            //if(i != (pDecReport->DecSliceNum - 1))
            {
                 if (old_slice_end_mbn > curr_slice_start_mbn)
                 {
                     old_slice_end_mbn = old_slice_start_mbn;
                 }
                
                 if ( (old_slice_end_mbn+1) < curr_slice_start_mbn )
                 {
                     if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }

                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0);
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn   = curr_slice_start_mbn - 1;
                     
                     /* z56361,20110928: old_slice如果发生了错误，上面的做法是有错即报全错. 同州反馈如此处理无法将轻微错误和完全错误区分开来，
                        这样如果码流有轻微错误也会导致大面积卡顿.
                        修改为: 从报错处向前回溯100个宏块，再之前的宏块视为正确 */
                     if ((old_slice_end_mbn - 100) > pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn)
                     {
                         pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = (old_slice_end_mbn - 100);
                     }
                     pRepairParam->ValidGroupNum++;
                 }
            }
		  	 /*add by l00225186
	          如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
	         只有一个宏块出错的话，不修补
	         */
	         if(i == (pDecReport->DecSliceNum - 1))
	         {
                 if(pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] < total_mbn - 1)
                 {
                     if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }
			         pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1];
	                 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;
			      
			         pRepairParam->ValidGroupNum++;
			         return POSTPRO_TRUE;
                }
	         }
             old_slice_start_mbn = curr_slice_start_mbn;
             old_slice_end_mbn   = curr_slice_end_mbn;
         }
    }

    return POSTPRO_TRUE;
}


SINT32 PostPro_GetMp24MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    UINT32 i;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>MAX_UP_MSG_SLICE_NUM) )
    {
       dprint(PRN_FATAL, "DecSliceNum(=%d) out of range!\n",pDecReport->DecSliceNum);
       return POSTPRO_FALSE;
    }

    pRepairParam->ValidGroupNum = 0;
	pRepairParam->FullRepair = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;
    total_mbn = pRepairParam->ImageWidth * pRepairParam->ImageHeight;
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;

	/* 现在的逻辑有问题，mpeg4协议每帧最后一个slice最后一个宏块上报可能有误，即使解码正确，也可能上报少解一个宏块.
	   所以在此检查这种情形，若只少最后几个宏块，则修正解码报告使之完整 */
	if (pDecReport->DecSliceNum >= 1)
	{
        if (pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] >= total_mbn - 10)
        {
            pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] = total_mbn - 1;
		}
	}

    for (i = 0; i <= pDecReport->DecSliceNum; i++)
    {
         curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];
         curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];
         if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) ||
		 	  (curr_slice_start_mbn > curr_slice_end_mbn) ||
		 	  (curr_slice_start_mbn < old_slice_start_mbn) )
         {
             continue;
         }
         else
         {
            // if(i != (pDecReport->DecSliceNum - 1))
            // {
                 /*为了避免VDH上报old slice结束宏块号大于cur slice起始宏块号的情况导致最终计算StartMbn大于EndMbn，这种情况
                 进而会导致修补时出现无法正常结束该slice得修补，在输出mv信息时，也会使得mv信息覆盖到其他有用的内存空间*/
                 if (old_slice_end_mbn > curr_slice_start_mbn)
                 {
				     old_slice_end_mbn = old_slice_start_mbn;
                 }
         
                 if ( ((old_slice_end_mbn+1) != curr_slice_start_mbn) && 
			 	    old_slice_start_mbn + (old_slice_start_mbn<0) < curr_slice_start_mbn - 1)
                 {
                     if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }
                                   
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0);
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn   = curr_slice_start_mbn - 1;
				
				    
                     /* z56361,20110928: old_slice如果发生了错误，上面的做法是有错即报全错. 同州反馈如此处理无法将轻微错误和完全错误区分开来，
                        这样如果码流有轻微错误也会导致大面积卡顿.
                        修改为: 从报错处向前回溯100个宏块，再之前的宏块视为正确 */
                     if ((old_slice_end_mbn - 100) > pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn)
                     {
                         pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = (old_slice_end_mbn - 100);
                     }
                     pRepairParam->ValidGroupNum++;
                 }
            // }
             
			 /*add by l00225186
	          如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
	         只有一个宏块出错的话，不修补
	         */
	         if(i == (pDecReport->DecSliceNum - 1))
	         {
                 if(pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] < total_mbn - 1)
                 {
                     if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }
			         pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1];
	                 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;
			      
			         pRepairParam->ValidGroupNum++;
			         return POSTPRO_TRUE;
                }
	         }

			old_slice_start_mbn = curr_slice_start_mbn;
            old_slice_end_mbn = curr_slice_end_mbn;
         }
    }

    return POSTPRO_TRUE;
}

SINT32 PostPro_GetVc1MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    UINT32 i;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>MAX_UP_MSG_SLICE_NUM) )
    {
       dprint(PRN_FATAL, "DecSliceNum out of range!\n");
       return POSTPRO_FALSE;
    }

    pRepairParam->ValidGroupNum = 0;
	pRepairParam->FullRepair = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;
    total_mbn = pRepairParam->ImageWidth * pRepairParam->ImageHeight;
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;
    for (i = 0; i <= pDecReport->DecSliceNum; i++)
    {
         curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];
         curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];
         if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) ||
            (curr_slice_start_mbn > curr_slice_end_mbn) )
         {
             continue;
         }
         else
         {
             // if(i != (pDecReport->DecSliceNum - 1))
             {
                 if (old_slice_end_mbn > curr_slice_start_mbn)
                 {
                     old_slice_end_mbn = old_slice_start_mbn;
                 }
         
                 //if ( (old_slice_end_mbn+1) < curr_slice_start_mbn )
                 if ( ((old_slice_end_mbn+1) != curr_slice_start_mbn) && 
			     	old_slice_start_mbn + (old_slice_start_mbn<0) < curr_slice_start_mbn - 1)
                 {
                     if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }
                   
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0);
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn   = curr_slice_start_mbn - 1;
                     pRepairParam->ValidGroupNum++;
                 }
              }
			 /*add by l00225186
	          如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
	         只有一个宏块出错的话，不修补
	         */
	          if (i == (pDecReport->DecSliceNum - 1))
	          {
                  if (pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] < total_mbn - 1)
                  {
                      if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                      {
                          dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                          return POSTPRO_FALSE;
                      }

			          pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1];
	                  pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;
			      
			          pRepairParam->ValidGroupNum++;
			          return POSTPRO_TRUE;
                 }
	          }
             old_slice_start_mbn = curr_slice_start_mbn;
             old_slice_end_mbn   = curr_slice_end_mbn;
         }
    }

    return POSTPRO_TRUE;

}

SINT32 PostPro_GetVp6MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    UINT32 i;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>MAX_UP_MSG_SLICE_NUM) )
    {
       dprint(PRN_FATAL, "DecSliceNum out of range!\n");
       return POSTPRO_FALSE;
    }

    pRepairParam->ValidGroupNum = 0;
	pRepairParam->FullRepair = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;
    total_mbn = pRepairParam->ImageWidth * pRepairParam->ImageHeight;
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;
    for (i = 0; i <= pDecReport->DecSliceNum; i++)
    {
         curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];
         curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];
         if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) ||
            (curr_slice_start_mbn > curr_slice_end_mbn) )
         {
             continue;
         }
         else
         {
             // if(i != (pDecReport->DecSliceNum - 1))
             {
                 if (old_slice_end_mbn > curr_slice_start_mbn)
                 {
                     old_slice_end_mbn = old_slice_start_mbn;
                 }
         
                 //if ( (old_slice_end_mbn+1) < curr_slice_start_mbn )
                 if ( ((old_slice_end_mbn+1) != curr_slice_start_mbn) && 
		    	 	old_slice_start_mbn + (old_slice_start_mbn<0) < curr_slice_start_mbn - 1)
                 {
                     if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0);
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn   = curr_slice_start_mbn - 1;
                     pRepairParam->ValidGroupNum++;
                 }
             }
			 /*add by l00225186
	          如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
	         只有一个宏块出错的话，不修补
	         */
	          if (i == (pDecReport->DecSliceNum - 1))
	          {
                  if (pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] < total_mbn - 1)
                  {
                    if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }

			          pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1];
	                  pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;
			      
			          pRepairParam->ValidGroupNum++;
			          return POSTPRO_TRUE;
                 }
	          }
              old_slice_start_mbn = curr_slice_start_mbn;
              old_slice_end_mbn   = curr_slice_end_mbn;
         }
    }

    return POSTPRO_TRUE;

}
SINT32 PostPro_GetVp8MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    UINT32 i;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>MAX_UP_MSG_SLICE_NUM) )
    {
       dprint(PRN_FATAL, "DecSliceNum out of range!\n");
       return POSTPRO_FALSE;
    }

    pRepairParam->ValidGroupNum = 0;
	pRepairParam->FullRepair = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;
    total_mbn = pRepairParam->ImageWidth * pRepairParam->ImageHeight;
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;
    for (i = 0; i <= pDecReport->DecSliceNum; i++)
    {
         curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];
         curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];
         if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) ||
            (curr_slice_start_mbn > curr_slice_end_mbn) )
         {
             continue;
         }
         else
         {
            // if(i != (pDecReport->DecSliceNum - 1))
             {
                 if (old_slice_end_mbn > curr_slice_start_mbn)
                 {
                     old_slice_end_mbn = old_slice_start_mbn;
                 }
         
                 //if ( (old_slice_end_mbn+1) < curr_slice_start_mbn )
                 if ( ((old_slice_end_mbn+1) != curr_slice_start_mbn) && 
			     	old_slice_start_mbn + (old_slice_start_mbn<0) < curr_slice_start_mbn - 1)
                 {
                     if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
                     {
                         dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
                         return POSTPRO_FALSE;
                     }
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0);
                     pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn   = curr_slice_start_mbn - 1;
                     pRepairParam->ValidGroupNum++;
                 }
             }
			 /*add by l00225186
	          如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
	         只有一个宏块出错的话，不修补
	         */
	         if(i == (pDecReport->DecSliceNum - 1))
	         {
	             if(pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] < total_mbn - 1)
	             {
	                 if (pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1))
	                 {
	                     dprint(PRN_DBG, "line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n",__LINE__);
	                     return POSTPRO_FALSE;
	                 }

		             pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1];
	                 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;
			      
		             pRepairParam->ValidGroupNum++;
		             return POSTPRO_TRUE;
	            }
	         }
	         old_slice_start_mbn = curr_slice_start_mbn;
	         old_slice_end_mbn   = curr_slice_end_mbn;
         }
    }

    return POSTPRO_TRUE;

}


SINT32 PostPro_GetAvsMbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    SINT32 dectopfldmbs;
    VDMHAL_REPAIR_PARAM_S *pLocalRepairParam;
    UINT32 i;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>MAX_UP_MSG_SLICE_NUM) )
    {
       dprint(PRN_FATAL, "DecSliceNum(=%d) out of range!\n",pDecReport->DecSliceNum);
       return POSTPRO_FALSE;
    }

    pLocalRepairParam = &(pRepairParam[0]);
    pRepairParam->FullRepair = 0;
    dectopfldmbs = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;
    total_mbn = pLocalRepairParam->ImageWidth * pLocalRepairParam->ImageHeight;
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;
    for (i = 0; i <= pDecReport->DecSliceNum; i++)
    {
        curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];
        curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];
        if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) ||
           (curr_slice_start_mbn > curr_slice_end_mbn) )
        {
            continue;
        }
        else
        {
           // if(i != (pDecReport->DecSliceNum - 1))
            {
                if (old_slice_end_mbn > curr_slice_start_mbn)
                {
                    old_slice_end_mbn = old_slice_start_mbn;
                }

                if ( (old_slice_end_mbn+1) < curr_slice_start_mbn )
                {
                    pLocalRepairParam->MbGroup[pLocalRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0) - dectopfldmbs;
                    pLocalRepairParam->MbGroup[pLocalRepairParam->ValidGroupNum].EndMbn = curr_slice_start_mbn - 1 - dectopfldmbs;
                    pLocalRepairParam->ValidGroupNum++;
                    if ( (!pLocalRepairParam->IsFrame) && ( curr_slice_start_mbn >= (total_mbn/2 -1) ) )
                    {
                        pLocalRepairParam = &(pRepairParam[1]);
                        dectopfldmbs = total_mbn/2;
                    }
                }
            }
           
            /*add by l00225186
            如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
            只有一个宏块出错的话，不修补
            */
            if(i == (pDecReport->DecSliceNum - 1))
            {
                if(pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] < total_mbn - 1)
                {
                    pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1];
                    pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;

                    pRepairParam->ValidGroupNum++;
                    return POSTPRO_TRUE;
                }
            }

            old_slice_start_mbn = curr_slice_start_mbn;
            old_slice_end_mbn   = curr_slice_end_mbn;
        }
    }

    return POSTPRO_TRUE;
}

SINT32 PostPro_GetDivx3MbGroup(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_DEC_REPORT_S *pDecReport)
{
    SINT32 total_mbn, old_slice_start_mbn, old_slice_end_mbn, curr_slice_start_mbn, curr_slice_end_mbn;
    SINT32 dectopfldmbs;
    VDMHAL_REPAIR_PARAM_S *pLocalRepairParam;
    UINT32 i;

    if ( (pDecReport->DecSliceNum<=0) || (pDecReport->DecSliceNum>4) )
    {
       dprint(PRN_FATAL, "DecSliceNum(=%d) out of range!\n", pDecReport->DecSliceNum);
       return POSTPRO_FALSE;
    }

    pLocalRepairParam = &(pRepairParam[0]);
    pRepairParam->FullRepair = 0;
    dectopfldmbs = 0;
    old_slice_start_mbn = -1;
    old_slice_end_mbn = -1;
    total_mbn = pLocalRepairParam->ImageWidth * pLocalRepairParam->ImageHeight;
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][0] = 
    pDecReport->SliceMbRange[pDecReport->DecSliceNum][1] = total_mbn;
    for (i = 0; i <= pDecReport->DecSliceNum; i++)
    {
        curr_slice_start_mbn = pDecReport->SliceMbRange[i][0];
        curr_slice_end_mbn   = pDecReport->SliceMbRange[i][1];
        if ( (curr_slice_start_mbn > total_mbn) || (curr_slice_end_mbn > total_mbn) ||
           (curr_slice_start_mbn > curr_slice_end_mbn) )
        {
            continue;
        }
        else
        {
           // if(i != (pDecReport->DecSliceNum - 1))
            {
                if (old_slice_end_mbn > curr_slice_start_mbn)
                {
                    old_slice_end_mbn = old_slice_start_mbn;
                }
        
                if ( (old_slice_end_mbn+1) < curr_slice_start_mbn )
                {
                    pLocalRepairParam->MbGroup[pLocalRepairParam->ValidGroupNum].StartMbn = old_slice_start_mbn + (old_slice_start_mbn<0) - dectopfldmbs;
                    pLocalRepairParam->MbGroup[pLocalRepairParam->ValidGroupNum].EndMbn = curr_slice_start_mbn - 1 - dectopfldmbs;
                    pLocalRepairParam->ValidGroupNum++;
                    if ( (!pLocalRepairParam->IsFrame) && ( curr_slice_start_mbn >= (total_mbn/2 -1) ) )
                    {
                        pLocalRepairParam = &(pRepairParam[1]);
                        dectopfldmbs = total_mbn/2;
                    }
                }
            }
			 /*add by l00225186
	          如果一帧图像只有一个slice，并且这个slice的最后几个宏块出错的话，那么也需要对其进行修补
	         只有一个宏块出错的话，不修补
	         */
	         if(i == (pDecReport->DecSliceNum - 1))
	         {
                 if(pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1] < total_mbn - 1)
                 {

			         pRepairParam->MbGroup[pRepairParam->ValidGroupNum].StartMbn = pDecReport->SliceMbRange[pDecReport->DecSliceNum - 1][1];
	                 pRepairParam->MbGroup[pRepairParam->ValidGroupNum].EndMbn = total_mbn -1;
			      
			         pRepairParam->ValidGroupNum++;
			         return POSTPRO_TRUE;
                 }
	         }		
             old_slice_start_mbn = curr_slice_start_mbn;
             old_slice_end_mbn   = curr_slice_end_mbn;
        }
    }

    return POSTPRO_TRUE;
}


VOID PostPro_BubbleSort(VDMHAL_DEC_REPORT_S *pDecReport)
{
    UINT32 i, j, flag = 1;
    UINT32 swap0, swap1;
    UINT32 n = pDecReport->DecSliceNum;

    for (i=1; (i<n)&&(1==flag); i++)
    {
        flag = 0;
        for (j=0; j<n-i; j++)
        {
            if ( pDecReport->SliceMbRange[j][0] > pDecReport->SliceMbRange[j+1][0] )
            {
                flag = 1;
                swap0 = pDecReport->SliceMbRange[j][0];
                swap1 = pDecReport->SliceMbRange[j][1];
                pDecReport->SliceMbRange[j][0] = pDecReport->SliceMbRange[j+1][0];
                pDecReport->SliceMbRange[j][1] = pDecReport->SliceMbRange[j+1][1];
                pDecReport->SliceMbRange[j+1][0] = swap0;
                pDecReport->SliceMbRange[j+1][1] = swap1;
            }
        }
        if (0 == flag)
        {
            return;
        }
    }
}


SINT32 PostPro_SetFullRepair(VID_STD_E VidStd, VOID *pDecParam, SINT32 VdhId)
{
    SINT32 err_ratio = 0;
    VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][0]);
    VDMHAL_DEC_REPORT_S *pDecReport = &(g_DecReport[VdhId]);

    //VDMHAL_MakeDecReport(VidStd, pDecReport);
    pDecReport->RetType = VDM_RET_ERROR;
    pDecReport->DecSliceNum = 0;
    err_ratio = PostPro_GetRepairParam(VidStd, pRepairParam, pDecParam, pDecReport, VdhId);

    return err_ratio;
}


SINT32 PostPro_SetDecReport(VID_STD_E VidStd, VOID *pDecParam, VDMHAL_DEC_REPORT_S *pDecReport)
{
#ifdef VFMW_H264_SUPPORT
    H264_DEC_PIC_PARAM_S *pH264DecParam;
#endif
#ifdef VFMW_HEVC_SUPPORT
    HEVC_DEC_PIC_PARAM_S *pHevcDecParam;
#endif
#ifdef VFMW_MVC_SUPPORT
    MVC_DEC_PIC_PARAM_S *pMvcDecParam;
#endif
#ifdef VFMW_MPEG2_SUPPORT
    MP2_DEC_PARAM_S *pMp2DecParam;  
#endif
#ifdef VFMW_MPEG4_SUPPORT
    MP4_DEC_PARAM_S *pMp4DecParam;
#endif
#ifdef VFMW_AVS_SUPPORT
    AVS_DEC_PARAM_S *pAvsDecParam;
#endif
#ifdef VFMW_REAL8_SUPPORT
    RV8_DEC_PARAM_S *pRv8DecParam;
#endif
#ifdef VFMW_REAL9_SUPPORT
    RV9_DEC_PARAM_S *pRv9DecParam;
#endif
#ifdef VFMW_VC1_SUPPORT    
    VC1_DEC_PARAM_S *pVc1DecParam;
#endif
#ifdef VFMW_DIVX3_SUPPORT    
    DIVX3_DEC_PARAM_S *pDivx3DecParam;
#endif
#ifdef VFMW_VP6_SUPPORT
    VP6_DEC_PARAM_S *pVp6DecParam;
#endif
#ifdef VFMW_VP8_SUPPORT
    VP8_DEC_PARAM_S *pVp8DecParam;	
#endif
    /* clear */
    memset( pDecReport, 0, sizeof(VDMHAL_DEC_REPORT_S) );

    switch (VidStd)
    {
    #ifdef VFMW_H264_SUPPORT            
        case VFMW_H264:
            pH264DecParam = (H264_DEC_PIC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif  
    #ifdef VFMW_HEVC_SUPPORT 
        case VFMW_HEVC:
            pHevcDecParam = (HEVC_DEC_PIC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif           
    #ifdef VFMW_MVC_SUPPORT            
        case VFMW_MVC:
            pMvcDecParam = (MVC_DEC_PIC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif       
    #ifdef VFMW_MPEG4_SUPPORT    
        case VFMW_MPEG4:
            pMp4DecParam = (MP4_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif    
    #ifdef VFMW_MPEG2_SUPPORT    
        case VFMW_MPEG2:
            pMp2DecParam = (MP2_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif    
    #ifdef VFMW_AVS_SUPPORT    
        case VFMW_AVS:
            pAvsDecParam = (AVS_DEC_PARAM_S *)pDecParam;
            if (1==pAvsDecParam->PicStruct)
            {
                pDecReport->DecSliceNum = 2;
                pDecReport->SliceMbRange[0][0] = 0;
                pDecReport->SliceMbRange[0][1] = 0;
                pDecReport->SliceMbRange[1][0] = (pAvsDecParam->PicWidthInMb*pAvsDecParam->PicHeightInMb)/2;
                pDecReport->SliceMbRange[1][1] = (pAvsDecParam->PicWidthInMb*pAvsDecParam->PicHeightInMb)/2;
            }
            else
            {
                pDecReport->DecSliceNum = 1;
                pDecReport->SliceMbRange[0][0] = 0;
                pDecReport->SliceMbRange[0][1] = 0;
            }
            break;
    #endif    
    #ifdef VFMW_REAL8_SUPPORT    
        case VFMW_REAL8:
            pRv8DecParam = (RV8_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif    
    #ifdef VFMW_REAL9_SUPPORT    
        case VFMW_REAL9:
            pRv9DecParam = (RV9_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif    
    #ifdef VFMW_VC1_SUPPORT    
        case VFMW_VC1:
            pVc1DecParam = (VC1_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif    
    #ifdef VFMW_DIVX3_SUPPORT    
        case VFMW_DIVX3:
            pDivx3DecParam = (DIVX3_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;
    #endif    
    #ifdef VFMW_VP6_SUPPORT    
        case VFMW_VP6:
        case VFMW_VP6A:
        case VFMW_VP6F:
            pVp6DecParam = (VP6_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;			
    #endif    
    #ifdef VFMW_VP8_SUPPORT    
        case VFMW_VP8:
            pVp8DecParam = (VP8_DEC_PARAM_S *)pDecParam;
            pDecReport->DecSliceNum = 1;
            pDecReport->SliceMbRange[0][0] = 0;
            pDecReport->SliceMbRange[0][1] = 0;
            break;			
    #endif    
        default :
            dprint(PRN_FATAL, "%s %d VidStd Err!\n", __func__, __LINE__);
            break;
    }

    return VDMHAL_OK;
}

#endif //__POST_PROCESS_C__
