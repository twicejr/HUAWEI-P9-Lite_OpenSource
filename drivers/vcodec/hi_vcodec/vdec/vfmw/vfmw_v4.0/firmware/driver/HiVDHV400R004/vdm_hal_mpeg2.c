
/***********************************************************************
*
* Copyright (c) 2009 Hisilicon - All Rights Reserved
*
* File: $vdm_hal_mpeg2.c$
* Date: $2009/03/06$
* Revision: $v1.0$
* Purpose: HiVDHV100 IP MPEG2 VDM HAL Module.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20090306   q45134            Original
*
************************************************************************/

#ifndef __VDM_HAL_MPEG2_C__
#define __VDM_HAL_MPEG2_C__

#include 	"public.h"
#include    "vdm_hal_v400r004_api.h"
#include    "vdm_hal_v400r004_local.h"
#include 	"vdm_hal_v400r004_mpeg2.h"

SINT32 MP2HAL_V400R004_CfgReg(MP2_DEC_PARAM_S *pMp2DecParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId, UINT32 *StreamBaseAddr);
SINT32 MP2HAL_V400R004_CfgDnMsg(MP2_DEC_PARAM_S *pMp2DecParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId, UADDR StreamBaseAddr);

static SINT32 FrameNum = -1;

SINT32 MP2HAL_V400R004_InitHal( UADDR CodeTabAddr, SINT32 VdhId )
{
    return VDMHAL_OK;
}

SINT32 MP2HAL_V400R004_StartDec( MP2_DEC_PARAM_S *pMp2DecParam, SINT32 VdhId)
{
    VDMHAL_HWMEM_S *pHwMem = &g_HwMem[VdhId];
    SINT32 *p32;
    UADDR StreamBaseAddr;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    if ( NULL == pHwMem->pVdmRegVirAddr )
    {
        if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr)) )
        {
            pHwMem->pVdmRegVirAddr = p32;
        }
        else
        {
            dprint(PRN_FATAL, "vdm register virtual address not mapped, reset failed!\n");
            return VDMHAL_ERR;
        }
    }

    FrameNum++;
    
    if (VDMHAL_OK != MP2HAL_V400R004_CfgReg(pMp2DecParam, pHwMem, VdhId, &StreamBaseAddr))
    {
        dprint(PRN_ERROR, "MP2HAL_V400R004_CfgReg ERROR!\n");
        return VDMHAL_ERR;
    }

    MP2HAL_V400R004_CfgDnMsg(pMp2DecParam, pHwMem, VdhId, StreamBaseAddr);

    return VDMHAL_OK;
}

SINT32 MP2HAL_V400R004_WriteSliceMsg(MP2_DEC_PARAM_S *pMp2DecParam,  SINT32 *SlcDnMsgVirAddr, UADDR SlcDnMsgPhyAddr, UADDR StreamBaseAddr)
{
    SINT32 i, j;
    UINT32 D32 = 0;
    SINT32 SliceNum = pMp2DecParam->SlcNum;
    MP2_SLCSTR_S *SliceInfo = pMp2DecParam->SlcStr;
    SINT32 slice_end_mbn = 0;
    UADDR next_slice_para_addr = 0,  bit_stream_address_0,  bit_stream_address_1;
    SINT32 bit_offset_0, bit_offset_1;
    SINT32 AddSlice0Flag = 0;

    if (SliceInfo[0].slice_start_mbn != 0)
    {
        i = 0;
        //D0
        /* 当第一个SLICE有错时，第一片码流的长度不能为零，所以在这种情况下，需要将
           第一片的码流强制设置为1 */
        D32 = 0;
        bit_stream_address_0 = (SliceInfo[i].BsPhyAddr[0] & 0xFFFFFFF0);
        bit_offset_0 = SliceInfo[i].BsBitOffset[0] + (SliceInfo[i].BsPhyAddr[0] & 0x0F) * 8;
        ((MP2SLCDNMSG_V400R004_D0 *)(&D32))->bit_len_0 = 1;
        ((MP2SLCDNMSG_V400R004_D0 *)(&D32))->bit_offset_0 = bit_offset_0;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 0, D32);
        dprint(PRN_DNMSG, "D0 = %#x \n", D32);

        //D1
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D1 *)(&D32))->bit_stream_address_0 = bit_stream_address_0 - StreamBaseAddr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 1, D32);
        dprint(PRN_DNMSG, "D1 = %#x \n", D32);

        //D2
        D32 = 0;
        bit_stream_address_1 = (SliceInfo[i].BsPhyAddr[1] & 0xFFFFFFF0);
        bit_offset_1 = SliceInfo[i].BsBitOffset[1] + (SliceInfo[i].BsPhyAddr[1] & 0x0F) * 8;
        ((MP2SLCDNMSG_V400R004_D2 *)(&D32))->bit_len_1 = 0;
        ((MP2SLCDNMSG_V400R004_D2 *)(&D32))->bit_offset_1 = bit_offset_1;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 2, D32);
        dprint(PRN_DNMSG, "D2 = %#x \n", D32);

        //D3
        D32 = 0;

        if (SliceInfo[i].BsPhyAddr[1] > 0)
        {
            ((MP2SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = bit_stream_address_1 - StreamBaseAddr;
        }
        else
        {
            ((MP2SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = 0;
        }

        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 3, D32);
        dprint(PRN_DNMSG, "D3 = %#x \n", D32);

        //D4
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D4 *)(&D32))->quantiser_scale_code = SliceInfo[i].quantiser_scale_code;
        ((MP2SLCDNMSG_V400R004_D4 *)(&D32))->intra_slice = SliceInfo[i].intra_slice;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 4, D32);
        dprint(PRN_DNMSG, "D4 = %#x \n", D32);

        //D5
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D5 *)(&D32))->slice_start_mbn = 0;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 5, D32);
        dprint(PRN_DNMSG, "D5 = %#x \n", D32);

        //D6
        D32 = 0;
        slice_end_mbn = (SliceInfo[0].slice_start_mbn) - 1;
        ((MP2SLCDNMSG_V400R004_D6 *)(&D32))->slice_end_mbn = slice_end_mbn;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 6, D32);
        dprint(PRN_DNMSG, "D6 = %#x \n", D32);
        //D7
        D32 = 0;
        next_slice_para_addr = SlcDnMsgPhyAddr + (i + 1) * 4 * 8;
        ((MP2SLCDNMSG_V400R004_D7 *)(&D32))->next_slice_para_addr = next_slice_para_addr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 7, D32);

        AddSlice0Flag = 1;
    }

    for (i = 0; i < SliceNum; i++)
    {
        if ((SliceInfo[i].slice_start_mbn <= SliceInfo[i - 1].slice_start_mbn) && (i > 0))
        {
            continue;
        }

        //D0
        D32 = 0;
        bit_stream_address_0 = (SliceInfo[i].BsPhyAddr[0] & 0xFFFFFFF0);
        bit_offset_0 = SliceInfo[i].BsBitOffset[0] + (SliceInfo[i].BsPhyAddr[0] & 0x0F) * 8;
        ((MP2SLCDNMSG_V400R004_D0 *)(&D32))->bit_len_0 = SliceInfo[i].BsLenInBit[0];
        ((MP2SLCDNMSG_V400R004_D0 *)(&D32))->bit_offset_0 = bit_offset_0;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 0 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D0 = %#x \n", D32);

        //D1
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D1 *)(&D32))->bit_stream_address_0 = bit_stream_address_0 - StreamBaseAddr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 1 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D1 = %#x \n", D32);

        //D2
        D32 = 0;
        bit_stream_address_1 = (SliceInfo[i].BsPhyAddr[1] & 0xFFFFFFF0);
        bit_offset_1 = SliceInfo[i].BsBitOffset[1] + (SliceInfo[i].BsPhyAddr[1] & 0x0F) * 8;
        ((MP2SLCDNMSG_V400R004_D2 *)(&D32))->bit_len_1 = SliceInfo[i].BsLenInBit[1];
        ((MP2SLCDNMSG_V400R004_D2 *)(&D32))->bit_offset_1 = bit_offset_1;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 2 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D2 = %#x \n", D32);

        //D3
        D32 = 0;

        if (SliceInfo[i].BsPhyAddr[1] > 0)
        {
            ((MP2SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = bit_stream_address_1 - StreamBaseAddr;
        }
        else
        {
            ((MP2SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = 0;
        }

        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 3 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D3 = %#x \n", D32);

        //D4
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D4 *)(&D32))->quantiser_scale_code = SliceInfo[i].quantiser_scale_code;
        ((MP2SLCDNMSG_V400R004_D4 *)(&D32))->intra_slice = SliceInfo[i].intra_slice;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 4 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D4 = %#x \n", D32);

        //D5
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D5 *)(&D32))->slice_start_mbn = SliceInfo[i].slice_start_mbn;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 5 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D5 = %#x \n", D32);

        for (j = (i + 1); j < SliceNum; j++)
        {
            if (SliceInfo[i].slice_start_mbn < SliceInfo[j].slice_start_mbn)
            {
                break;
            }
        }

        if (j == SliceNum)
        {
            slice_end_mbn = ((pMp2DecParam->PicWidthInMb) * (pMp2DecParam->PicHeightInMb)) - 1;
            next_slice_para_addr = 0;
        }
        else
        {
            slice_end_mbn = (SliceInfo[j].slice_start_mbn) - 1;
            next_slice_para_addr = SlcDnMsgPhyAddr + j * 4 * 8 + AddSlice0Flag * 4 * 8;
        }

        //D6
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D6 *)(&D32))->slice_end_mbn = slice_end_mbn;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 6 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D6 = %#x \n", D32);
        //D7
        D32 = 0;
        ((MP2SLCDNMSG_V400R004_D7 *)(&D32))->next_slice_para_addr = next_slice_para_addr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 7 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D7 = %#x \n", D32);

        i = j - 1;
    }

    return 0;
}

SINT32 MP2HAL_V400R004_CfgReg(MP2_DEC_PARAM_S *pMp2DecParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId, UINT32 *StreamBaseAddr)
{
    SINT32 *p32;
    SINT32 D32 = 0;
    UINT32 height_in_mb;
    SINT32 i, k;
    UADDR tmp_base_addr, stream_base_addr;
    UINT32 level = 16;
    SINT32 datTmp;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    if ( NULL == pHwMem->pVdmRegVirAddr )
    {
        if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr)) )
        {
            pHwMem->pVdmRegVirAddr = p32;
        }
        else
        {
            dprint(PRN_FATAL, "vdm register virtual address not mapped, reset failed!\n");
            return VDMHAL_ERR;
        }
    }

    // 清除中断
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );

    D32 = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->mbamt_to_dec         = pMp2DecParam->PicWidthInMb * pMp2DecParam->PicHeightInMb - 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->load_qmatrix_flag    = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->marker_bit_detect_en = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->ac_last_detect_en    = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->coef_idx_detect_en   = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->vop_type_detect_en   = 0;
#ifdef ENV_SOS_KERNEL
    ((BASIC_V400R004_CFG0 *)(&D32))->sec_mode_en          = 1;
#else
    ((BASIC_V400R004_CFG0 *)(&D32))->sec_mode_en          = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId  );

    D32 = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->video_standard       = 0x3;
    ((BASIC_V400R004_CFG1 *)(&D32))->ddr_stride           = pMp2DecParam->VahbStride >> 6;
    ((BASIC_V400R004_CFG1 *)(&D32))->fst_slc_grp          = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->mv_output_en         = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->uv_order_en          = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->vdh_2d_en            = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->max_slcgrp_num       = 3;
    ((BASIC_V400R004_CFG1 *)(&D32))->ppfd_en              = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->line_num_output_en   = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->compress_en = pMp2DecParam->Compress_en;
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );

    D32 = 0;
    ((AVM_V400R004_ADDR *)(&D32))->av_msg_addr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId  );

    D32 = 0;
    ((VAM_V400R004_ADDR *)(&D32))->va_msg_addr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId  );

    D32 = 0;
    for (i = 0, stream_base_addr = 0xFFFFFFFF; i < pMp2DecParam->SlcNum; i++)
    {
        /*查找最小的码流包地址作为基地址时，如果有分包的情况，则码流包开头并非起始码，因此不要在此判断*/
        for (k = 0; k < 2; k++)
        {
            if ((pMp2DecParam->SlcStr[i].BsPhyAddr[k] > 0) && (pMp2DecParam->SlcStr[i].BsLenInBit[k] > 0))
            {
                tmp_base_addr = pMp2DecParam->SlcStr[i].BsPhyAddr[k] & 0xFFFFFFF0;
                stream_base_addr = (stream_base_addr < tmp_base_addr) ? stream_base_addr : tmp_base_addr;
            }
        }
    }

    if (stream_base_addr == 0xFFFFFFFF)
    {
        dprint(PRN_FATAL, "stream_base_addr = %#x\n", stream_base_addr);
        *StreamBaseAddr = 0;
        return VDMHAL_ERR;
    }
    else
    {
        ((STREAM_V400R004_BASE_ADDR *)(&D32))->stream_base_addr = stream_base_addr;
        *StreamBaseAddr = stream_base_addr;
    }

    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId  );

    //EMAR_ID
    if (pMp2DecParam->PicWidthInMb > 120)
    {
        D32 = 0x0;
    }
    else
    {
        D32 = 0x10000;
    }

    datTmp = RD_SCDREG(REG_EMAR_ID);
    if (0 == D32)
    {
        datTmp = datTmp & (~(0x10000));
    }
    else
    {
        datTmp = datTmp | (0x10000);
    }
    WR_SCDREG(REG_EMAR_ID, datTmp);

    //TIME_OUT
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_SED_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_ITRANS_TO, D32, VdhId );
    WR_VREG( VREG_V400R004_PMV_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_PRC_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_RCN_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_DBLK_TO,   D32, VdhId );
    WR_VREG( VREG_V400R004_PPFD_TO,   D32, VdhId );

    D32 = 0;
    ((YSTADDR_V400R004_1D *)(&D32))->ystaddr_1d = pMp2DecParam->CurPicPhyAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId );
    D32 = 0;
    height_in_mb = pMp2DecParam->PicHeightInMb * ( ((1 == pMp2DecParam->PictureStructure) || (2 == pMp2DecParam->PictureStructure)) ? 2 : 1);
    ((YSTRIDE_V400R004_1D *)(&D32))->ystride_1d = pMp2DecParam->VahbStride;//pMp2DecParam->VahbStride*32;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId );
	
    D32 = 0;
	level = 0;

    ((UVOFFSET_V400R004_1D *)(&D32))->uvoffset_1d = (pMp2DecParam->VahbStride) * ((height_in_mb + 1) / 2) * 2
            + ((height_in_mb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId );

    D32 = 0;
    ((REF_V400R004_PIC_TYPE *)(&D32))->ref_pic_type_0 = pMp2DecParam->FwdRefIsFldSave;
    ((REF_V400R004_PIC_TYPE *)(&D32))->ref_pic_type_1 = pMp2DecParam->BwdRefIsFldSave;
    WR_VREG( VREG_V400R004_REF_PIC_TYPE, D32, VdhId );

    D32 = 0;
    ((FF_V400R004_APT_EN *)(&D32))->ff_apt_en = 0;//USE_FF_APT_EN;
    WR_VREG( VREG_V400R004_FF_APT_EN, D32, VdhId );

    //HEAD_INF_OFFSET
    D32 = ((height_in_mb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId );
    dprint(PRN_VDMREG, "HEAD_INF_OFFSET = 0x%x\n", D32);

    return VDMHAL_OK;
}


SINT32 MP2HAL_V400R004_CfgDnMsg(MP2_DEC_PARAM_S *pMp2DecParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId, UADDR StreamBaseAddr)
{
    SINT32 *pMsgBase;
    UINT32 D32 = 0;
    SINT32 i, j;
    UINT32 BytePos0, BytePos1;
    SINT8  *StreamVirAddr[2];
    UADDR stream_base_addr, SlcDnMsgPhyAddr;
    SINT32 *SlcDnMsgVirAddr;

    pMsgBase = (SINT32 *)MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);
    VDMHAL_ASSERT_RET( NULL != pMsgBase, "can not map down msg virtual address!" );
    /* 1. 检查参数是否超出规格 */
    VDMHAL_ASSERT_RET( pMp2DecParam->PicWidthInMb <= MAX_IMG_WIDTH_IN_MB, "picture width out of range");
    VDMHAL_ASSERT_RET( pMp2DecParam->PicHeightInMb <= MAX_IMG_HEIGHT_IN_MB, "picture height out of range");

    D32 = 0;
    ((MP2DNMSG_V400R004_D0 *)(&D32))->pic_width_in_mb = pMp2DecParam->PicWidthInMb - 1;
    ((MP2DNMSG_V400R004_D0 *)(&D32))->pic_height_in_mb = pMp2DecParam->PicHeightInMb - 1;
    ((MP2DNMSG_V400R004_D0 *)(&D32))->mpeg1_flag = pMp2DecParam->Mpeg1Flag;
    WR_MSGWORD( pMsgBase, D32);

    D32 = 0;
    ((MP2DNMSG_V400R004_D1 *)(&D32))->frame_pred_frame_dct = pMp2DecParam->FramePredFrameDct;
    ((MP2DNMSG_V400R004_D1 *)(&D32))->picture_structure = pMp2DecParam->PictureStructure;
    ((MP2DNMSG_V400R004_D1 *)(&D32))->second_field_flag = pMp2DecParam->SecondFieldFlag;
    ((MP2DNMSG_V400R004_D1 *)(&D32))->concealment_motion_vectors = pMp2DecParam->ConcealmentMotionVectors;
    ((MP2DNMSG_V400R004_D1 *)(&D32))->pic_coding_type = pMp2DecParam->PicCodingType;
    ((MP2DNMSG_V400R004_D1 *)(&D32))->full_pel_forward_vector = pMp2DecParam->Mp1FwdmvFullPel;
    ((MP2DNMSG_V400R004_D1 *)(&D32))->full_pel_backward_vector = pMp2DecParam->Mp1BwdmvFullPel;
    WR_MSGWORD( pMsgBase + 1, D32);

    D32 = 0;
    ((MP2DNMSG_V400R004_D2 *)(&D32))->fcode_11 = pMp2DecParam->Fcode[3];
    ((MP2DNMSG_V400R004_D2 *)(&D32))->fcode_10 = pMp2DecParam->Fcode[2];
    ((MP2DNMSG_V400R004_D2 *)(&D32))->fcode_01 = pMp2DecParam->Fcode[1];
    ((MP2DNMSG_V400R004_D2 *)(&D32))->fcode_00 = pMp2DecParam->Fcode[0];
    ((MP2DNMSG_V400R004_D2 *)(&D32))->top_field_first = pMp2DecParam->TopFieldFirst;
    WR_MSGWORD( pMsgBase + 2, D32);

    D32 = 0;
    ((MP2DNMSG_V400R004_D3 *)(&D32))->intra_dc_precision = pMp2DecParam->IntraDcPrecision;
    ((MP2DNMSG_V400R004_D3 *)(&D32))->q_scale_type = pMp2DecParam->QuantType;
    ((MP2DNMSG_V400R004_D3 *)(&D32))->intra_vlc_format = pMp2DecParam->IntraVlcFormat;
    ((MP2DNMSG_V400R004_D3 *)(&D32))->alternate_scan = pMp2DecParam->AlternateScan;
    WR_MSGWORD( pMsgBase + 3, D32);

    D32 = 0;
    ((MP2DNMSG_V400R004_D4 *)(&D32))->bwd_address = (pMp2DecParam->BwdRefPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 4, D32);

    D32 = 0;
    ((MP2DNMSG_V400R004_D5 *)(&D32))->fwd_address = (pMp2DecParam->FwdRefPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 5, D32);

    D32 = 0;
    ((MP2DNMSG_V400R004_D6 *)(&D32))->rcn_address = (pMp2DecParam->DispFramePhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 6, D32);

    D32 = 0;
    ((MP2DNMSG_V400R004_D7 *)(&D32))->current_pmv_addr = (pMp2DecParam->PmvColmbPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 7, D32);

    StreamVirAddr[0] = (SINT8 *)MEM_Phy2Vir(pMp2DecParam->StreamPhyAddr[0]);
    StreamVirAddr[1] = (SINT8 *)MEM_Phy2Vir(pMp2DecParam->StreamPhyAddr[1]);

    if (0 == pMp2DecParam->StreamLength[1])  //只有一包码流
    {
        BytePos0 = pMp2DecParam->StreamPhyAddr[0] + pMp2DecParam->StreamBitOffset[0] / 8;
        stream_base_addr = BytePos0 & 0xFFFFFFF0;

        D32 = 0;
        ((MP2DNMSG_V400R004_D8 *)(&D32))->bit_stream_address_0 = 0;
        WR_MSGWORD( pMsgBase + 8, D32);

        D32 = 0;
        ((MP2DNMSG_V400R004_D9 *)(&D32))->bit_len_0 = pMp2DecParam ->StreamLength[0] + MPEG2_DUMMY_BITS;
        ((MP2DNMSG_V400R004_D9 *)(&D32))->bit_offset_0 = 8 * (BytePos0 & 0x0F) + (pMp2DecParam->StreamBitOffset[0] % 8);
        WR_MSGWORD( pMsgBase + 9, D32);

        if ( NULL != StreamVirAddr[0] )
        {
            UINT8 *rp = StreamVirAddr[0] + pMp2DecParam->StreamBitOffset[0] / 8;
            dprint(PRN_STR_HEAD, "Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                   rp[0], rp[1], rp[2], rp[3], rp[4], rp[5], rp[6], rp[7]);
            rp = StreamVirAddr[0] + pMp2DecParam->StreamBitOffset[0] / 8 + pMp2DecParam ->StreamLength[0] / 8 - 8;
            dprint(PRN_STR_TAIL, "Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                   rp[0], rp[1], rp[2], rp[3], rp[4], rp[5], rp[6], rp[7]);
        }

        D32 = 0;
        ((MP2DNMSG_V400R004_D10 *)(&D32))->bit_stream_address_1 = 0;
        WR_MSGWORD( pMsgBase + 10, D32);

        D32 = 0;
        ((MP2DNMSG_V400R004_D11 *)(&D32))->bit_len_1 = 0;
        ((MP2DNMSG_V400R004_D11 *)(&D32))->bit_offset_1 = 0;
        WR_MSGWORD( pMsgBase + 11, D32);
    }
    else  //两包码流
    {
        BytePos1 = pMp2DecParam->StreamPhyAddr[1] + pMp2DecParam->StreamBitOffset[1] / 8;
        stream_base_addr = BytePos1 & 0xFFFFFFF0;
        BytePos0 = pMp2DecParam->StreamPhyAddr[0] + pMp2DecParam->StreamBitOffset[0] / 8;

        D32 = 0;
        ((MP2DNMSG_V400R004_D8 *)(&D32))->bit_stream_address_0 = (BytePos0 & 0xFFFFFFF0) - stream_base_addr;
        WR_MSGWORD( pMsgBase + 8, D32);

        D32 = 0;
        ((MP2DNMSG_V400R004_D9 *)(&D32))->bit_len_0 = pMp2DecParam ->StreamLength[0];
        ((MP2DNMSG_V400R004_D9 *)(&D32))->bit_offset_0 = 8 * (BytePos0 & 0x0F) + (pMp2DecParam->StreamBitOffset[0] % 8);
        WR_MSGWORD( pMsgBase + 9, D32);

        if ( NULL != StreamVirAddr[0] )
        {
            UINT8 *rp = StreamVirAddr[0] + pMp2DecParam->StreamBitOffset[0] / 8;
            dprint(PRN_STR_HEAD, "1p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                   rp[0], rp[1], rp[2], rp[3], rp[4], rp[5], rp[6], rp[7]);
            rp = StreamVirAddr[0] + pMp2DecParam->StreamBitOffset[0] / 8 + pMp2DecParam ->StreamLength[0] / 8 - 8;
            dprint(PRN_STR_TAIL, "1p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                   rp[0], rp[1], rp[2], rp[3], rp[4], rp[5], rp[6], rp[7]);
            dprint(PRN_DBG, "1p last phy addr = 0x%x\n", pMp2DecParam->StreamPhyAddr[0] + pMp2DecParam->StreamLength[0]);
        }

        D32 = 0;
        ((MP2DNMSG_V400R004_D10 *)(&D32))->bit_stream_address_1 = 0;
        WR_MSGWORD( pMsgBase + 10, D32);

        D32 = 0;
        ((MP2DNMSG_V400R004_D11 *)(&D32))->bit_len_1 = pMp2DecParam ->StreamLength[1] + MPEG2_DUMMY_BITS;
        ((MP2DNMSG_V400R004_D11 *)(&D32))->bit_offset_1 = 8 * (BytePos1 & 0x0F) + (pMp2DecParam->StreamBitOffset[1] % 8);
        WR_MSGWORD( pMsgBase + 11, D32);

        if ( NULL != StreamVirAddr[1] )
        {
            UINT8 *rp = StreamVirAddr[1] + pMp2DecParam->StreamBitOffset[1] / 8;
            dprint(PRN_STR_HEAD, "2p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                   rp[0], rp[1], rp[2], rp[3], rp[4], rp[5], rp[6], rp[7]);
            rp = StreamVirAddr[1] + pMp2DecParam->StreamBitOffset[1] / 8 + pMp2DecParam ->StreamLength[1] / 8 - 8;
            dprint(PRN_STR_TAIL, "2p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                   rp[0], rp[1], rp[2], rp[3], rp[4], rp[5], rp[6], rp[7]);
        }
    }

#if 0

    for (i = 0; i < 32; i++)
    {
        D32 = 0;
        ((MP2DNMSG_V200R004_D16_47 *)(&D32))->intra_quantiser_matrix_even = pMp2DecParam->IntraQuantTab[2 * i];
        ((MP2DNMSG_V200R004_D16_47 *)(&D32))->intra_quantiser_matrix_odd = pMp2DecParam->IntraQuantTab[2 * i + 1];
        ((MP2DNMSG_V200R004_D16_47 *)(&D32))->non_Intra_quantiser_matrix_even = pMp2DecParam->NonIntraQuantTab[2 * i];
        ((MP2DNMSG_V200R004_D16_47 *)(&D32))->non_Intra_quantiser_matrix_odd = pMp2DecParam->NonIntraQuantTab[2 * i + 1];
        WR_MSGWORD( pMsgBase + 16 + i, D32);
    }

#else

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 2; j++)
        {
            ((MP2DNMSG_V400R004_D16_31 *)(&D32))->intra_quantiser_matrix_0 =  pMp2DecParam->IntraQuantTab[i + 8 * j + 0];
            ((MP2DNMSG_V400R004_D16_31 *)(&D32))->intra_quantiser_matrix_1 = pMp2DecParam->IntraQuantTab[i + 8 * j + 16];
            ((MP2DNMSG_V400R004_D16_31 *)(&D32))->intra_quantiser_matrix_2 = pMp2DecParam->IntraQuantTab[i + 8 * j + 32];
            ((MP2DNMSG_V400R004_D16_31 *)(&D32))->intra_quantiser_matrix_3 = pMp2DecParam->IntraQuantTab[i + 8 * j + 48];

            WR_MSGWORD( pMsgBase + 16 + 2 * i + j, D32);

            ((MP2DNMSG_V400R004_D32_47 *)(&D32))->non_intra_quantiser_matrix_0 = pMp2DecParam->NonIntraQuantTab[i + 8 * j + 0];
            ((MP2DNMSG_V400R004_D32_47 *)(&D32))->non_intra_quantiser_matrix_1 = pMp2DecParam->NonIntraQuantTab[i + 8 * j + 16];
            ((MP2DNMSG_V400R004_D32_47 *)(&D32))->non_intra_quantiser_matrix_2 = pMp2DecParam->NonIntraQuantTab[i + 8 * j + 32];
            ((MP2DNMSG_V400R004_D32_47 *)(&D32))->non_intra_quantiser_matrix_3 = pMp2DecParam->NonIntraQuantTab[i + 8 * j + 48];

            WR_MSGWORD( pMsgBase + 32 + 2 * i + j, D32);
        }
    }

#endif

    D32 = 0;
    ((MP2DNMSG_V400R004_D48 *)(&D32))->pmv_top_addr = (pHwMem->PmvTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 48, D32);

    /* ?????? */
    SlcDnMsgPhyAddr = (pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0) + 64 * 4;
    SlcDnMsgVirAddr = MEM_Phy2Vir(SlcDnMsgPhyAddr);
    VDMHAL_ASSERT_RET(NULL != SlcDnMsgVirAddr, "can not map a valid SlcDnMsgVirAddr address");

    D32 = 0;
    ((MP2DNMSG_V400R004_D63 *)(&D32))->first_slc_dnmsg_addr = SlcDnMsgPhyAddr;
    WR_MSGWORD( pMsgBase + 63, D32);

    /* ??????? slice ?? */
    MP2HAL_V400R004_WriteSliceMsg(pMp2DecParam, SlcDnMsgVirAddr, SlcDnMsgPhyAddr, StreamBaseAddr);
    {
        UINT32 i_cnt;
        static UINT32 num = 0;

        if ((g_PrintEnable & (1 << PRN_DNMSG)) != 0)
        {
            num++;
            dprint(PRN_DNMSG, "\n*****No.%2d Down Msg (phy addr: %#8x) *****\n", num, pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);

            for (i_cnt = 0; i_cnt < 64 - 3; i_cnt += 4)
            {
                dprint(PRN_DNMSG, "\n0x%02x 0x%08x 0x%08x 0x%08x 0x%08x\n",
                       i_cnt, *(pMsgBase + i_cnt), *(pMsgBase + i_cnt + 1), *(pMsgBase + i_cnt + 2), *(pMsgBase + i_cnt + 3));
            }

            dprint(PRN_DNMSG, "\n***** Down Msg print finished *****\n");
        }
    }
    return VDMHAL_OK;
}

#endif //__VDM_HAL_MPEG2_C__
