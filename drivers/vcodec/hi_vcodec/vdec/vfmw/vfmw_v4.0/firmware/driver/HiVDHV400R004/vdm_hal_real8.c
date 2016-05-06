
/***********************************************************************
*
* Copyright (c) 2010 Hisilicon - All Rights Reserved
*
* File: $vdm_hal_real8.c$
* Date: $2010/06/09$
* Revision: $v1.0$
* Purpose: HiVDHV100 IP REAL8 VDM HAL Module.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20100609   q45134            Original
*
************************************************************************/

#ifndef __VDM_HAL_REAL8_C__
#define __VDM_HAL_REAL8_C__

#include "public.h"
#include "vdm_hal_v400r004_api.h"
#include "vdm_hal_v400r004_local.h"
#include "vdm_hal_v400r004_real8.h"

VOID RV8HAL_V400R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId);
VOID RV8HAL_V400R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);
VOID RV8HAL_V400R004_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);

static SINT32 FrameNum = -1;


SINT32 RV8HAL_V400R004_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 RV8HAL_V400R004_StartDec( RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId )
{
    VDMHAL_HWMEM_S *pHwMem = &g_HwMem[VdhId];
    SINT32 *p32;

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

    RV8HAL_V400R004_WriteReg(pHwMem, pRv8DecParam, VdhId);
    RV8HAL_V400R004_WritePicMsg(pHwMem, pRv8DecParam);
    RV8HAL_V400R004_WriteSliceMsg(pHwMem, pRv8DecParam);

    return VDMHAL_OK;
}

VOID RV8HAL_V400R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId)
{
    UINT32 D32;
    UINT32 datTmp;
    UINT32 height_in_mb;
    UINT32 level = 16;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return ;
    }
    
    dprint(PRN_CTRL, "configuring VDM registers...\n");

    D32 = 0;
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->mbamt_to_dec         = pRv8DecParam->PicWidthInMb * pRv8DecParam->PicHeightInMb - 1;
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->ld_qmatrix_flag      = 0;
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->marker_bit_detect_en = 0;
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->ac_last_detect_en    = 0;
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->coef_idx_detect_en   = 1;
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->vop_type_detect_en   = 0;
#ifdef ENV_SOS_KERNEL
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->sec_mode_en          = 1;
#else
    ((RV8_V400R004_BASIC_CFG0 *)(&D32))->sec_mode_en          = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG0=0x%x\n", D32);

    //BASIC_V400R004_CFG1
    D32 = 0;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->video_standard       = 0x8;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->ddr_stride           = pRv8DecParam->DDRStride >> 6;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->fst_slc_grp          = pRv8DecParam->FstSlcGrp;
    if (pRv8DecParam->PicCodingType == 0 || pRv8DecParam->PicCodingType == 1 || pRv8DecParam->PicCodingType == 3)
    {
        ((RV8_V400R004_BASIC_CFG1 *)(&D32))->mv_output_en     = 1;
    }
    else
    {
        ((RV8_V400R004_BASIC_CFG1 *)(&D32))->mv_output_en     = 0;
    }
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->uv_order_en          = 0;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->vdh_2d_en            = 1;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->max_slcgrp_num       = 0;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->line_num_output_en   = 0;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->compress_en          = pRv8DecParam->Compress_en;
    ((RV8_V400R004_BASIC_CFG1 *)(&D32))->ppfd_en              = 0;
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG1=0x%x\n", D32);

    //AVM_V400R004_ADDR
    D32 = 0;
    ((RV8_V400R004_AVM_ADDR *)(&D32))->av_msg_addr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "AVM_V400R004_ADDR=0x%x\n", D32);

    //VAM_V400R004_ADDR
    D32 = 0;
    ((RV8_V400R004_VAM_ADDR *)(&D32))->va_msg_addr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "VAM_V400R004_ADDR=0x%x\n", D32);

    //STREAM_V400R004_BASE_ADDR
    D32 = 0;
    ((RV8_V400R004_STREAM_BASE_ADDR *)(&D32))->stream_base_addr = pRv8DecParam->StreamBaseAddr;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "STREAM_V400R004_BASE_ADDR=0x%x\n", D32);

    //EMAR_ID
    if (pRv8DecParam->PicWidthInMb > 256)
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
    dprint(PRN_VDMREG, "TIME_OUT = 0x%x\n", D32);

    //YSTADDR_V400R004_1D
    D32 = pRv8DecParam->CurPicPhyAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTADDR_V400R004_1D = 0x%x\n", D32);

    //YSTRIDE_V400R004_1D
    height_in_mb = pRv8DecParam->PicHeightInMb;
    //    D32 = pRv8DecParam->DDRStride*32;
    D32 = pRv8DecParam->DDRStride;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTRIDE_V400R004_1D = 0x%x\n", D32);

    //UVOFFSET_V400R004_1D
	level = 0;

    D32 = (pRv8DecParam->DDRStride) * ((height_in_mb + 1) / 2) * 2
          + ((pRv8DecParam->PicHeightInMb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId );
    dprint(PRN_VDMREG, "UVOFFSET_V400R004_1D = 0x%x\n", D32);

    //PRCNUM_1D_CNT
    D32 = ((pRv8DecParam->PicHeightInMb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId );
    //  dprint(PRN_VDMREG, "PRCNUM_1D_CNT = 0x%x\n", D32);
#if 0
    //PRCMEM1_1D_CNT
    D32 = 0x7F3CFC3C;
    WR_VREG( VREG_V400R004_PRCMEM1_1D_CNT, D32, VdhId );
    dprint(PRN_VDMREG, "PRCMEM1_1D_CNT = 0x%x\n", D32);

    //PRCMEM2_1D_CNT
    D32 = 0xFF3FFF12;
    WR_VREG( VREG_V400R004_PRCMEM2_1D_CNT, D32, VdhId );
    dprint(PRN_VDMREG, "PRCMEM2_1D_CNT = 0x%x\n", D32);
#endif

    //REF_V400R004_PIC_TYPE
    D32 = 0;
    WR_VREG( VREG_V400R004_REF_PIC_TYPE, D32, VdhId );
    dprint(PRN_VDMREG, "REF_V400R004_PIC_TYPE=0x%x\n", D32);

    //FF_V400R004_APT_EN
    D32 = 0;
    ((RV8_V400R004_FF_APT_EN *)(&D32))->ff_apt_en = 0;  //Always use FrameSave Mode, USE_FF_APT_EN
    WR_VREG( VREG_V400R004_FF_APT_EN, D32, VdhId );
    dprint(PRN_VDMREG, "FF_V400R004_APT_EN=0x%x\n", D32);

    // INT
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );

#if 0
    // INT_V400R004_MASK
#ifdef VDM_BUSY_WAITTING
    // 中断屏蔽
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFF, VdhId );
#else
    // 中断打开
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFE, VdhId );
#endif
#endif

    return;
}

VOID RV8HAL_V400R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam)
{
    UINT32 D32;
    SINT32 *pMsgBase, *p32;

    dprint(PRN_CTRL, "configuring Pic Msg...\n");

    pMsgBase = (SINT32 *)MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0);
    VDMHAL_ASSERT(NULL != pMsgBase, "can not map dn msg virtual address!\n");

    /* D0 */
    p32 = pMsgBase;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D0 *)(&D32))->pic_coding_type = pRv8DecParam->PicCodingType;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);

    /* D1 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D1 *)(&D32))->pic_width_in_mb = pRv8DecParam->PicWidthInMb - 1;
    ((RV8_V400R004_PICDNMSG_D1 *)(&D32))->pic_height_in_mb = pRv8DecParam->PicHeightInMb - 1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);

    /* D2 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D2 *)(&D32))->Ratio0 = pRv8DecParam->Ratio0;
    ((RV8_V400R004_PICDNMSG_D2 *)(&D32))->Ratio1 = pRv8DecParam->Ratio1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D2 = 0x%x\n", D32);

    /* D3 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D3 *)(&D32))->rv_deblocking_strength = RV8_Default_Deblocking_Strength;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D3 = 0x%x\n", D32);

    /* D4 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D4 *)(&D32))->currpicqp = pRv8DecParam->PQUANT;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D4 = 0x%x\n", D32);

    /* D5 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D5 *)(&D32))->prevpicqp = pRv8DecParam->PrevPicQP;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D5 = 0x%x\n", D32);

    /* D6 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D6 *)(&D32))->prevpicmb0qp = pRv8DecParam->PrevPicMb0QP;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D6 = 0x%x\n", D32);

    /* D16 */
    p32 = pMsgBase + 16;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D16 *)(&D32))->curr_rcn_addr = (pRv8DecParam->DispFramePhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D16 = 0x%x\n", D32);

    /* D17 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D17 *)(&D32))->fwd_ref_addr = (pRv8DecParam->FwdRefPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D17 = 0x%x\n", D32);

    /* D18 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D18 *)(&D32))->bwd_ref_addr = (pRv8DecParam->BwdRefPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D18 = 0x%x\n", D32);

    /* D19 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D19 *)(&D32))->curr_colmb_addr = (pRv8DecParam->CurrPmvPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D19 = 0x%x\n", D32);

    /* D20 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D20 *)(&D32))->bwd_colmb_addr = (pRv8DecParam->ColPmvPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D20 = 0x%x\n", D32);

    /* D21 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D21 *)(&D32))->sed_top_addr = (pHwMem->SedTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D21 = 0x%x\n", D32);

    /* D22 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D22 *)(&D32))->pmv_top_addr = (pHwMem->PmvTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D22 = 0x%x\n", D32);

    /* D23 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D23 *)(&D32))->rcn_top_addr = (pHwMem->RcnTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D23 = 0x%x\n", D32);

    /* D24 */
    ++p32;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D24 *)(&D32))->dblk_top_addr = (pHwMem->DblkTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D24 = 0x%x\n", D32);

    /* D63 */
    p32 = pMsgBase + 63;
    D32 = 0;
    ((RV8_V400R004_PICDNMSG_D63 *)(&D32))->next_slice_para_addr = (pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0) + 4 * 64;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);

    return;
}

VOID RV8HAL_V400R004_WriteSliceMsg(VDMHAL_HWMEM_S * pHwMem, RV8_DEC_PARAM_S * pRv8DecParam)
{
    UINT32 i, j;
    UINT32 D32;
    SINT32 *pMsgBase;
    RV8_SLC_PARAM_S *pSliceParam;
    SINT32 AddSlice0Flag = 0;
    UADDR MsgBlockPhy, next_slice_para_addr = 0;
    dprint(PRN_CTRL, "configuring Slice Msg...\n");

    pSliceParam = pRv8DecParam->SliceParam;
    MsgBlockPhy = (pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0) + 4 * 64;
    pMsgBase = (SINT32 *)MEM_Phy2Vir(MsgBlockPhy);
    VDMHAL_ASSERT(NULL != pMsgBase, "can not map dn msg virtual address!\n");

    if (pRv8DecParam->SliceParam[0].first_mb_in_slice != 0)
    {
        i = 0;
        /* D0 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D0 *)(&D32))->bit_len_0 = 0;
        ((RV8_V400R004_SLCDNMSG_D0 *)(&D32))->bit_offset_0 = pSliceParam[i].StreamBitOffset[0];
        WR_MSGWORD( pMsgBase + i * 64, D32 );
        dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);
        /* D1 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D1 *)(&D32))->bit_stream_addr_0 = pSliceParam[i].StreamPhyAddr[0];
        WR_MSGWORD( pMsgBase + 1 + i * 64, D32 );
        dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);
        /* D2 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D2 *)(&D32))->bit_len_1 = 0;
        ((RV8_V400R004_SLCDNMSG_D2 *)(&D32))->bit_offset_1 = pSliceParam[i].StreamBitOffset[1];
        WR_MSGWORD( pMsgBase + 2 + i * 64, D32 );
        dprint(PRN_DNMSG, "D2 = 0x%x\n", D32);
        /* D3 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D3 *)(&D32))->bit_stream_addr_1 = pSliceParam[i].StreamPhyAddr[1];
        WR_MSGWORD( pMsgBase + 3 + i * 64, D32 );
        dprint(PRN_DNMSG, "D3 = 0x%x\n", D32);
        /* D4 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D4 *)(&D32))->dblk_filter_passthrough = pSliceParam[i].dblk_filter_passthrough;
        ((RV8_V400R004_SLCDNMSG_D4 *)(&D32))->osvquant = pSliceParam[i].osvquant;
        ((RV8_V400R004_SLCDNMSG_D4 *)(&D32))->sliceqp = pSliceParam[i].sliceqp;
        WR_MSGWORD( pMsgBase + 4 + i * 64, D32 );
        dprint(PRN_DNMSG, "D4 = 0x%x\n", D32);
        /* D5 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D5 *)(&D32))->slice_start_mbn = 0;
        ((RV8_V400R004_SLCDNMSG_D5 *)(&D32))->slice_end_mbn = pSliceParam[i].first_mb_in_slice - 1;
        WR_MSGWORD( pMsgBase + 5 + i * 64, D32 );
        dprint(PRN_DNMSG, "D5 = 0x%x\n", D32);

        /* D63 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D63 *)(&D32))->next_slice_para_addr = MsgBlockPhy + (i + 1) * 4 * 64;
        WR_MSGWORD( pMsgBase + 63 + i * 64, D32 );
        dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);

        AddSlice0Flag = 1;

    }

    for (i = 0; i < pRv8DecParam->TotalSliceNum; i++)
    {
        if (i > 0)
        {
            if ((pSliceParam[i].first_mb_in_slice <= pSliceParam[i - 1].first_mb_in_slice))
            {
                continue;
            }
        }

        /* D0 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D0 *)(&D32))->bit_len_0 = pSliceParam[i].StreamLength[0];
        ((RV8_V400R004_SLCDNMSG_D0 *)(&D32))->bit_offset_0 = pSliceParam[i].StreamBitOffset[0];
        WR_MSGWORD( pMsgBase + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);
        /* D1 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D1 *)(&D32))->bit_stream_addr_0 = pSliceParam[i].StreamPhyAddr[0];
        WR_MSGWORD( pMsgBase + 1 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);
        /* D2 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D2 *)(&D32))->bit_len_1 = pSliceParam[i].StreamLength[1];
        ((RV8_V400R004_SLCDNMSG_D2 *)(&D32))->bit_offset_1 = pSliceParam[i].StreamBitOffset[1];
        WR_MSGWORD( pMsgBase + 2 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D2 = 0x%x\n", D32);
        /* D3 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D3 *)(&D32))->bit_stream_addr_1 = pSliceParam[i].StreamPhyAddr[1];
        WR_MSGWORD( pMsgBase + 3 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D3 = 0x%x\n", D32);
        /* D4 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D4 *)(&D32))->dblk_filter_passthrough = pSliceParam[i].dblk_filter_passthrough;
        ((RV8_V400R004_SLCDNMSG_D4 *)(&D32))->osvquant = pSliceParam[i].osvquant;
        ((RV8_V400R004_SLCDNMSG_D4 *)(&D32))->sliceqp = pSliceParam[i].sliceqp;
        WR_MSGWORD( pMsgBase + 4 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D4 = 0x%x\n", D32);
        /* D5 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D5 *)(&D32))->slice_start_mbn = pSliceParam[i].first_mb_in_slice;

        for (j = (i + 1); j < pRv8DecParam->TotalSliceNum; j++)
        {
            if (pSliceParam[i].first_mb_in_slice < pSliceParam[j].first_mb_in_slice)
            {
                break;
            }
        }

        if (j == pRv8DecParam->TotalSliceNum)
        {
            pSliceParam->last_mb_in_slice = ((pRv8DecParam->PicWidthInMb) * (pRv8DecParam->PicHeightInMb)) - 1;
            next_slice_para_addr = 0;
        }
        else
        {
            pSliceParam->last_mb_in_slice = (pSliceParam[j].first_mb_in_slice) - 1;
            next_slice_para_addr = MsgBlockPhy + j * 4 * 64 + AddSlice0Flag * 64;
        }

        ((RV8_V400R004_SLCDNMSG_D5 *)(&D32))->slice_end_mbn = pSliceParam[i].last_mb_in_slice;

        WR_MSGWORD( pMsgBase + 5 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D5 = 0x%x\n", D32);

        /* D63 */
        D32 = 0;
        ((RV8_V400R004_SLCDNMSG_D63 *)(&D32))->next_slice_para_addr = next_slice_para_addr;
        WR_MSGWORD( pMsgBase + 63 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);
        i = j - 1;
    }

    return;
}

#endif //__VDM_HAL_REAL8_C__
