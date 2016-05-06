
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vdm_hal_vp8.c
    版 本 号   : 初稿
    作    者   :
    生成日期   :
    最近修改   :
    功能描述   : VDMV300 硬件抽象


  修改历史   :
    1.日    期 : 2009-03-04
    作    者   :
    修改内容   :

******************************************************************************/

#ifndef __VDM_HAL_VP8_C__
#define __VDM_HAL_VP8_C__


#include "public.h"
#include "vdm_hal.h"
#include "vdm_hal_v400r004_local.h"
#include "vdm_hal_v400r004_vp8.h"


/************************************************************************/
/*  函数实现                                                            */
/************************************************************************/
SINT32 VP8HAL_V400R004_InitHal(UADDR CodeTabAddr)
{
    return VDMHAL_OK;
}

SINT32 VP8HAL_V400R004_CfgReg(VP8_DEC_PARAM_S *pVp8DecParam, VDMHAL_HWMEM_S *pHwMem , SINT32 VdhId)
{
    SINT32 D32 = 0, *p32;
    UINT32 datTmp;
    UINT32 ystride;
    UINT32 level = 16;

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

    //BASIC_CFG0
    D32 = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->mbamt_to_dec      = pVp8DecParam->pic_width_in_mb * pVp8DecParam->pic_height_in_mb - 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->load_qmatrix_flag = 0;
#ifdef ENV_SOS_KERNEL
    ((BASIC_V400R004_CFG0 *)(&D32))->sec_mode_en       = 1;
#else
	((BASIC_V400R004_CFG0 *)(&D32))->sec_mode_en       = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId);
    dprint(PRN_VDMREG, "BASIC_CFG0 = 0x%x\n", D32);

    //BASIC_CFG1
    D32 = 0x20000000;
    ((BASIC_V400R004_CFG1 *)(&D32))->video_standard    = 0x0C;
    ((BASIC_V400R004_CFG1 *)(&D32))->ddr_stride        = pVp8DecParam->ddr_stride >> 6;
    ((BASIC_V400R004_CFG1 *)(&D32))->fst_slc_grp       = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->mv_output_en      = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->uv_order_en       = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->vdh_2d_en         = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->max_slcgrp_num    = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->compress_en       = pVp8DecParam->Compress_en;
    ((BASIC_V400R004_CFG1 *)(&D32))->ppfd_en           = 0;
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId);
    dprint(PRN_VDMREG, "BASIC_CFG1 = 0x%x\n", D32);

    //AVM_ADDR
    D32 = 0;
    ((AVM_V400R004_ADDR *)(&D32))->av_msg_addr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId);
    dprint(PRN_VDMREG, "AVM_ADDR = 0x%x\n", D32);

    //VAM_ADDR
    D32 = 0;
    ((VAM_V400R004_ADDR *)(&D32))->va_msg_addr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId);
    dprint(PRN_VDMREG, "VAM_ADDR = 0x%x\n", D32);

    //STREAM_BASE_ADDR
    D32 = 0;
    ((STREAM_V400R004_BASE_ADDR *)(&D32))->stream_base_addr = pVp8DecParam->stream_base_addr;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId);
    dprint(PRN_VDMREG, "STREAM_BASE_ADDR = 0x%x\n", D32);


    //PPFD_BUF_ADDR
    D32 = pHwMem->PpfdBufAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_PPFD_BUF_ADDR, D32, VdhId);
    dprint(PRN_VDMREG, "PPFD_BUF_ADDR = 0x%x\n", D32);

    //PPFD_BUF_LEN
    D32 = pHwMem->PpfdBufLen;
    WR_VREG( VREG_V400R004_PPFD_BUF_LEN, D32, VdhId);
    dprint(PRN_VDMREG, "PPFD_BUF_LEN = 0x%x\n", D32);

    //EMAR_ID
    //width<=4096 配1 >4096 配0，h00216273
    if (pVp8DecParam->pic_width_in_mb > 256)
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

    //YSTADDR_1D
    D32 = 0;
    ((YSTADDR_V400R004_1D *)(&D32))->ystaddr_1d = pVp8DecParam->image_curr_rcn_addr & 0xFFFFFFF0; //caution
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId);
    dprint(PRN_VDMREG, "YSTADDR_1D = 0x%x\n", D32);

    //YSTRIDE_1D
    D32 = 0;
    //	ystride = pVp8DecParam->ddr_stride * 32;
    ystride = pVp8DecParam->ddr_stride;
    //	ystride = (( pVp8DecParam->pic_width_in_mb + 15) / 16) * 16*16*16;
    ((YSTRIDE_V400R004_1D *)(&D32))->ystride_1d = ystride;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId);
    dprint(PRN_VDMREG, "YSTRIDE_1D = 0x%x\n", D32);

    //UVOFFSET_1D
    D32 = 0;

	level = 0;

    ((UVOFFSET_V400R004_1D *)(&D32))->uvoffset_1d = ystride * ((pVp8DecParam->pic_height_in_mb + 1) / 2) * 2
            + ((pVp8DecParam->pic_height_in_mb * 16 + 31) / 32) * 32 * level;

    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId);
    dprint(PRN_VDMREG, "UVOFFSET_1D = 0x%x\n", D32);

    D32 = ((pVp8DecParam->pic_height_in_mb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId);
    // INT
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId);

#if 0
    // INT_MASK
#ifdef VDM_BUSY_WAITTING
    // 中断屏蔽
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFF, VdhId);
#else
    // 中断打开
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFE, VdhId);
#endif
#endif

    return VDMHAL_OK;
}

SINT32 VP8HAL_V400R004_StartDec(VP8_DEC_PARAM_S *pVp8DecParam, SINT32 VdhId)
{
    VDMHAL_HWMEM_S *pHwMem = &g_HwMem[VdhId];
    SINT32 *p32;
    
    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    /* 1.  检查参数是否超出规格 */
    VDMHAL_ASSERT_RET( pVp8DecParam->pic_width_in_mb <= MAX_IMG_WIDTH_IN_MB, "picture width out of range");
    VDMHAL_ASSERT_RET( pVp8DecParam->pic_height_in_mb <= MAX_IMG_HEIGHT_IN_MB, "picture width out of range");

    if ( NULL == pHwMem->pVdmRegVirAddr )
    {
        if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir( gVdhRegBaseAddr)) )
        {
            pHwMem->pVdmRegVirAddr = p32;
        }
        else
        {
            dprint(PRN_FATAL, "vdm register virtual address not mapped, reset failed!\n");
            return VDMHAL_ERR;
        }
    }

    /* 3. configure register */
    VP8HAL_V400R004_CfgReg(pVp8DecParam, pHwMem, VdhId);
    
    /* 4. configure down message */
    VP8HAL_V400R004_CfgDnMsg(pVp8DecParam, pHwMem, VdhId);

    return VDMHAL_OK;
}

SINT32 VP8HAL_V400R004_CfgDnMsg(VP8_DEC_PARAM_S *pVp8DecParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId)
{
    SINT32 *pMsgBase, *p32;
    SINT32 D32, i;
    UINT32 D16_bit_len_0, D16_bit_offset_0, D17_bit_byte_offset_0;
    UINT8 *u8Tmp = 0;

    pMsgBase = MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);
    VDMHAL_ASSERT_RET( pMsgBase != NULL, "can not map down msg virtual address!");
    p32 = pMsgBase;

    /* D0 */
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D0 *)(&D32))->cur_frame_type	= pVp8DecParam->frame_type;
    ((VP8_V400R004_PICDNMSG_D0 *)(&D32))->last_frame_type = pVp8DecParam->last_frame_type;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);

    //caution: specical set --liucan
    /* D1 */
    ++p32;
    D32 = 0;
    D32 =  pVp8DecParam->full_pixel * 2 + 1 -  pVp8DecParam->use_bilinear_mc_filter;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);

    /* D2 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D2 *)(&D32))->pic_width_in_mb	= pVp8DecParam->pic_width_in_mb - 1;
    ((VP8_V400R004_PICDNMSG_D2 *)(&D32))->pic_height_in_mb = pVp8DecParam->pic_height_in_mb - 1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D2 = 0x%x\n", D32);

    /* D3 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D3 *)(&D32))->prob_skip_false = pVp8DecParam->prob_skip_false;
    ((VP8_V400R004_PICDNMSG_D3 *)(&D32))->mb_no_coeff_skip = pVp8DecParam->mb_no_coeff_skip;
    ((VP8_V400R004_PICDNMSG_D3 *)(&D32))->multi_token_partition = pVp8DecParam->multi_token_partition;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D3 = 0x%x\n", D32);

    /* D4 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D4 *)(&D32))->segmentation_enable	= pVp8DecParam->segmentation_enable;
    ((VP8_V400R004_PICDNMSG_D4 *)(&D32))->update_mb_segmentation_map = pVp8DecParam->update_mb_segmentation_map;
    ((VP8_V400R004_PICDNMSG_D4 *)(&D32))->mb_segmentation_abs_delta = pVp8DecParam->mb_segmentation_abs_delta;
    ((VP8_V400R004_PICDNMSG_D4 *)(&D32))->mode_ref_lf_delta_enabled = pVp8DecParam->mode_ref_lf_delta_enabled;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D4 = 0x%x\n", D32);

    /* D5 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D5 *)(&D32))->cur_filter_type = pVp8DecParam->filter_type;
    ((VP8_V400R004_PICDNMSG_D5 *)(&D32))->last_filter_type = pVp8DecParam->last_filter_type;
    ((VP8_V400R004_PICDNMSG_D5 *)(&D32))->filter_level = pVp8DecParam->filter_level;
    ((VP8_V400R004_PICDNMSG_D5 *)(&D32))->cur_sharpness_level = pVp8DecParam->sharpness_level;
    ((VP8_V400R004_PICDNMSG_D5 *)(&D32))->last_sharpness_level = pVp8DecParam->last_sharpness_level;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D5 = 0x%x\n", D32);

    /* D6 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->y1dc_sign	= pVp8DecParam->y1dc_sign;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->y1dc_absdelta_q = pVp8DecParam->y1dc_absdelta_q;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->y2dc_sign = pVp8DecParam->y2dc_sign;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->y2dc_absdelta_q = pVp8DecParam->y2dc_absdelta_q;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->y2ac_sign = pVp8DecParam->y2ac_sign;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->y2ac_absdelta_q = pVp8DecParam->y2ac_absdelta_q;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->uvdc_sign =  pVp8DecParam->uvdc_sign;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->uvdc_absdelta_q =  pVp8DecParam->uvdc_absdelta_q;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->uvac_sign = pVp8DecParam->uvac_sign;
    ((VP8_V400R004_PICDNMSG_D6 *)(&D32))->uvac_absdelta_q =  pVp8DecParam->uvac_absdelta_q;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D6 = 0x%x\n", D32);

    /* D7 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D7 *)(&D32))->base_qindex = pVp8DecParam->base_qindex;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D7 = 0x%x\n", D32);

    /* D8 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D8 *)(&D32))->value	= pVp8DecParam->value;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D8 = 0x%x\n", D32);

    /* D9 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D9 *)(&D32))->range	= pVp8DecParam->range;
    ((VP8_V400R004_PICDNMSG_D9 *)(&D32))->count	= pVp8DecParam->count;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D9 = 0x%x\n", D32);
    {
        D16_bit_len_0 = pVp8DecParam->bit_len_0 + pVp8DecParam->count;

        if (pVp8DecParam->bit_offset_0 >= pVp8DecParam->count)
        {
            D17_bit_byte_offset_0 = pVp8DecParam->bit_byte_offset_0;
            D16_bit_offset_0 = pVp8DecParam->bit_offset_0 - pVp8DecParam->count;
        }
        else
        {
            D17_bit_byte_offset_0 = pVp8DecParam->bit_byte_offset_0 - 16;
            D16_bit_offset_0 =  128 - (pVp8DecParam->count - pVp8DecParam->bit_offset_0);
        }
    }

    /* D16 */
    p32 += 7;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D16 *)(&D32))->bit_len_0	= D16_bit_len_0; //pVp8DecParam->bit_len_0;
    ((VP8_V400R004_PICDNMSG_D16 *)(&D32))->bit_offset_0	= D16_bit_offset_0; //pVp8DecParam->bit_offset_0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D16 = 0x%x\n", D32);

    /* D17 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D17 *)(&D32))->bit_stream_addr_0	= D17_bit_byte_offset_0; //pVp8DecParam->bit_byte_offset_0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D17 = 0x%x\n", D32);

    /* D18 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D18 *)(&D32))->bit_len_1	= pVp8DecParam->bit_len_1;
    ((VP8_V400R004_PICDNMSG_D18 *)(&D32))->bit_offset_1	= pVp8DecParam->bit_offset_1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D18 = 0x%x\n", D32);

    /* D19 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D19 *)(&D32))->bit_stream_addr_1	= pVp8DecParam->bit_byte_offset_1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D19 = 0x%x\n", D32);

    /* D20 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D20 *)(&D32))->segment_feature_dat00	= pVp8DecParam->segment_feature_dat0[0];
    ((VP8_V400R004_PICDNMSG_D20 *)(&D32))->segment_feature_dat01	= pVp8DecParam->segment_feature_dat0[1];
    ((VP8_V400R004_PICDNMSG_D20 *)(&D32))->segment_feature_dat02	= pVp8DecParam->segment_feature_dat0[2];
    ((VP8_V400R004_PICDNMSG_D20 *)(&D32))->segment_feature_dat03	= pVp8DecParam->segment_feature_dat0[3];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D20 = 0x%x\n", D32);

    /* D21 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D21 *)(&D32))->segment_feature_dat10	= pVp8DecParam->segment_feature_dat1[0];
    ((VP8_V400R004_PICDNMSG_D21 *)(&D32))->segment_feature_dat11	= pVp8DecParam->segment_feature_dat1[1];
    ((VP8_V400R004_PICDNMSG_D21 *)(&D32))->segment_feature_dat12	= pVp8DecParam->segment_feature_dat1[2];
    ((VP8_V400R004_PICDNMSG_D21 *)(&D32))->segment_feature_dat13	= pVp8DecParam->segment_feature_dat1[3];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D21 = 0x%x\n", D32);

    /* D22 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D22 *)(&D32))->ref_lf_delta0	= pVp8DecParam->ref_lf_delta[0];
    ((VP8_V400R004_PICDNMSG_D22 *)(&D32))->ref_lf_delta1	= pVp8DecParam->ref_lf_delta[1];
    ((VP8_V400R004_PICDNMSG_D22 *)(&D32))->ref_lf_delta2	= pVp8DecParam->ref_lf_delta[2];
    ((VP8_V400R004_PICDNMSG_D22 *)(&D32))->ref_lf_delta3	= pVp8DecParam->ref_lf_delta[3];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D22 = 0x%x\n", D32);

    /* D23 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D23 *)(&D32))->mode_lf_delta0	= pVp8DecParam->mode_lf_delta[0];
    ((VP8_V400R004_PICDNMSG_D23 *)(&D32))->mode_lf_delta1	= pVp8DecParam->mode_lf_delta[1];
    ((VP8_V400R004_PICDNMSG_D23 *)(&D32))->mode_lf_delta2	= pVp8DecParam->mode_lf_delta[2];
    ((VP8_V400R004_PICDNMSG_D23 *)(&D32))->mode_lf_delta3	= pVp8DecParam->mode_lf_delta[3];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D23 = 0x%x\n", D32);

    /* D24 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D24 *)(&D32))->ref_frame_sign_bias_0	= pVp8DecParam->ref_frame_sign_bias[0];
    ((VP8_V400R004_PICDNMSG_D24 *)(&D32))->ref_frame_sign_bias_1	= pVp8DecParam->ref_frame_sign_bias[1];
    ((VP8_V400R004_PICDNMSG_D24 *)(&D32))->ref_frame_sign_bias_2	= pVp8DecParam->ref_frame_sign_bias[2];
    ((VP8_V400R004_PICDNMSG_D24 *)(&D32))->ref_frame_sign_bias_3	= pVp8DecParam->ref_frame_sign_bias[3];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D24 = 0x%x\n", D32);

    /* D25 */
    ++p32;
    D32 = pVp8DecParam->SegIdAddr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D25 = 0x%x\n", D32);

    /* D32 */
    p32 += (8 - 1);
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D32 *)(&D32))->curr_rcn_addr = (pVp8DecParam->image_curr_rcn_addr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D32 = 0x%x\n", D32);

    /* D33 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D33 *)(&D32))->alt_ref_addr = (pVp8DecParam->image_alt_ref_addr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D33 = 0x%x\n", D32);

    /* D34 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D34 *)(&D32))->golden_ref_addr = (pVp8DecParam->image_gld_ref_addr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D34 = 0x%x\n", D32);

    /* D35 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D35 *)(&D32))->last_ref_addr = (pVp8DecParam->image_last_ref_addr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D35 = 0x%x\n", D32);

    /* D36 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D36 *)(&D32))->sed_top_addr = (pHwMem->SedTopAddr + 0xF) & 0xFFFFFFF0; //caution!!
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D36 = 0x%x\n", D32);

    // D37
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D37 *)(&D32))->pmv_top_addr = (pHwMem->PmvTopAddr + 0xF) & 0xFFFFFFF0; //caution!
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D37 = 0x%x\n", D32);

    // D38
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D38 *)(&D32))->rcn_top_addr = (pHwMem->RcnTopAddr + 0xF) & 0xFFFFFFF0; //caution!
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D38 = 0x%x\n", D32);

    // D39
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D39 *)(&D32))->tab_addr =  (pHwMem->Vp8TabAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D39 = 0x%x\n", D32);
    u8Tmp = (UINT8 *)MEM_Phy2Vir(D32);

    if (NULL == u8Tmp)
    {
        dprint(PRN_FATAL, "%s: u8Tmp = NULL\n", __func__);
        return VDMHAL_ERR;
    }

    memcpy(u8Tmp, pVp8DecParam->table, 2752);

    /* D40 */
    ++p32;
    D32 = 0;
    ((VP8_V400R004_PICDNMSG_D40 *)(&D32))->dblk_top_addr = (pHwMem->DblkTopAddr + 0xF) & 0xFFFFFFF0; //caution!
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D40 = 0x%x\n", D32);

    /* D59 */
    /*    p32 += 20;
    	D32 = 0;
    	((VP8_V400R004_PICDNMSG_D59*)(&D32))->dblk_top_addr = (pHwMem->DblkTopAddr + 0xF) & 0xFFFFFFF0; //caution!
        WR_MSGWORD( p32, D32 );
    	dprint(PRN_DNMSG, "D59 = 0x%x\n", D32);
    */

    /* D63  next msg group -- caution!!1 */
    //p32 += 4;
    p32 += 23;
    //D32 = 0;
    D32 = (UINT32)MEM_Vir2Phy((SINT8 *)pMsgBase) + 64 * 4;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);

    //stream second part config ,D64-D95
    for (i = 0; i < 8; i++)
    {
        ++p32;
        D32 = 0;
        ((VP8_V400R004_BITSTREAM_LEN_OFFSET *)(&D32))->bitn_len =  pVp8DecParam->bitn_len_0[i];
        ((VP8_V400R004_BITSTREAM_LEN_OFFSET *)(&D32))->bitn_offset =  pVp8DecParam->bitn_offset_0[i];
        WR_MSGWORD( p32, D32 );
        dprint(PRN_DNMSG, "D%d = 0x%x\n", 64 + i * 4, D32);

        ++p32;
        D32 = 0;
        ((VP8_V400R004_BITSTREAM_ADDR *)(&D32))->bitn_stream_addr =  pVp8DecParam->bitn_byte_offset_0[i];
        WR_MSGWORD( p32, D32 );
        dprint(PRN_DNMSG, "D%d = 0x%x\n", 64 + i * 4 + 1, D32);

        ++p32;
        D32 = 0;
        ((VP8_V400R004_BITSTREAM_LEN_OFFSET *)(&D32))->bitn_len =  pVp8DecParam->bitn_len_1[i];
        ((VP8_V400R004_BITSTREAM_LEN_OFFSET *)(&D32))->bitn_offset =  pVp8DecParam->bitn_offset_1[i];
        WR_MSGWORD( p32, D32 );
        dprint(PRN_DNMSG, "D%d = 0x%x\n", 64 + i * 4 + 2, D32);

        ++p32;
        D32 = 0;
        ((VP8_V400R004_BITSTREAM_ADDR *)(&D32))->bitn_stream_addr =  pVp8DecParam->bitn_byte_offset_1[i];
        WR_MSGWORD( p32, D32 );
        dprint(PRN_DNMSG, "D%d = 0x%x\n", 64 + i * 4 + 3, D32);
    }

    return VDMHAL_OK;
}
#endif

