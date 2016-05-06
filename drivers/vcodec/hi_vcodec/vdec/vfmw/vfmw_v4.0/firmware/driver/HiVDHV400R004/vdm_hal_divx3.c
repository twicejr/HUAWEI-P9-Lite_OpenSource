
/***********************************************************************
*
* Copyright (c) 2012 Hisilicon - All Rights Reserved
*
* File: $vdm_hal_divx3.c$
* Date: $2012/01/06$
* Revision: $v1.0$
* Purpose: HiVDHV100 IP DIVX3 VDM HAL Module.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20120106   q45134            Original
*
************************************************************************/

#ifndef __VDM_HAL_DIVX3_C__
#define __VDM_HAL_DIVX3_C__

#include "public.h"
#include "vdm_hal_v400r004_api.h"
#include "vdm_hal_v400r004_local.h"
#include "vdm_hal_v400r004_divx3.h"

VOID DIVX3HAL_V400R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId);
VOID DIVX3HAL_V400R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam);
VOID DIVX3HAL_V400R004_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam);

static SINT32 FrameNum = -1;


SINT32 DIVX3HAL_V400R004_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 DIVX3HAL_V400R004_StartDec( DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId )
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
            dprint(PRN_FATAL, " %s %d vdm register virtual address not mapped, reset failed!\n", __func__, __LINE__);
            return VDMHAL_ERR;
        }
    }

    FrameNum++;

    DIVX3HAL_V400R004_WriteReg(pHwMem, pDivx3DecParam, VdhId);
    DIVX3HAL_V400R004_WritePicMsg(pHwMem, pDivx3DecParam);
    DIVX3HAL_V400R004_WriteSliceMsg(pHwMem, pDivx3DecParam);

    return VDMHAL_OK;
}


VOID DIVX3HAL_V400R004_WriteReg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId)
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
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->mbamt_to_dec         = pDivx3DecParam->PicWidthInMb * pDivx3DecParam->PicHeightInMb - 1;
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->ld_qmatrix_flag      = 0;
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->marker_bit_detect_en = 0;
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->ac_last_detect_en    = 0;
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->coef_idx_detect_en   = 0;
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->vop_type_detect_en   = 0;
#ifdef ENV_SOS_KERNEL
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->sec_mode_en          = 1; 
#else
    ((DIVX3_V400R004_BASIC_CFG0 *)(&D32))->sec_mode_en          = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG0 = 0x%x\n", D32);

    // BASIC_V400R004_CFG1
    D32 = 0;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->video_standard       = 0x5;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->ddr_stride           = pDivx3DecParam->DDRStride >> 6;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->fst_slc_grp          = 1;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->mv_output_en         = 1;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->uv_order_en          = 0;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->vdh_2d_en            = 1;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->max_slcgrp_num       = 0;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->line_num_output_en   = 0;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->compress_en          = pDivx3DecParam->Compress_en;
    ((DIVX3_V400R004_BASIC_CFG1 *)(&D32))->ppfd_en              = 0;
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG1=0x%x\n", D32);

    //AVM_V400R004_ADDR
    D32 = 0;
    ((DIVX3_V400R004_AVM_ADDR *)(&D32))->av_msg_addr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "AVM_V400R004_ADDR=0x%x\n", D32);

    //VAM_V400R004_ADDR
    D32 = 0;
    ((DIVX3_V400R004_VAM_ADDR *)(&D32))->va_msg_addr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "VAM_V400R004_ADDR=0x%x\n", D32);

    //STREAM_V400R004_BASE_ADDR
    D32 = 0;
    ((DIVX3_V400R004_STREAM_BASE_ADDR *)(&D32))->stream_base_addr = pDivx3DecParam->StreamBaseAddr;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "STREAM_V400R004_BASE_ADDR=0x%x\n", D32);

    //EMAR_ID
    if (pDivx3DecParam->PicWidthInMb > 256)
    {
        D32 = 0x0;
    }
    else
    {
        D32 = 0x010000;
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
    D32 = pDivx3DecParam->CurPicPhyAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTADDR_V400R004_1D = 0x%x\n", D32);

    //YSTRIDE_V400R004_1D
    height_in_mb = pDivx3DecParam->PicHeightInMb;
    //    D32 = pDivx3DecParam->DDRStride*32;
    D32 = pDivx3DecParam->DDRStride;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTRIDE_V400R004_1D = 0x%x\n", D32);

    //UVOFFSET_V400R004_1D
    D32 = 0;
	level = 0;

    D32 = (pDivx3DecParam->DDRStride) * (((height_in_mb + 1) / 2) * 2)
          + ((pDivx3DecParam->PicHeightInMb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId );
    dprint(PRN_VDMREG, "UVOFFSET_V400R004_1D = 0x%x\n", D32);

    //PRCNUM_1D_CNT
    D32 = ((height_in_mb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId );

    //REF_V400R004_PIC_TYPE
    D32 = 0;
    WR_VREG( VREG_V400R004_REF_PIC_TYPE, D32, VdhId );
    dprint(PRN_VDMREG, "REF_V400R004_PIC_TYPE=0x%x\n", D32);

    //FF_V400R004_APT_EN
    D32 = 0;
    ((DIVX3_V400R004_FF_APT_EN *)(&D32))->ff_apt_en = 0;  //Always use FrameSave Mode, USE_FF_APT_EN
    WR_VREG( VREG_V400R004_FF_APT_EN, D32, VdhId );
    dprint(PRN_VDMREG, "FF_V400R004_APT_EN=0x%x\n", D32);

    // INT
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );

    return;
}


VOID DIVX3HAL_V400R004_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    UINT32 D32;
    SINT32 *pMsgBase, *p32;

    dprint(PRN_CTRL, "configuring Pic Msg...\n");

    pMsgBase = (SINT32 *)MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0);
    VDMHAL_ASSERT(NULL != pMsgBase, "can not map dn msg virtual address!\n");

    /* D0 */
    p32 = pMsgBase;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D0 *)(&D32))->pic_coding_type = pDivx3DecParam->prediction_type;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);

    /* D1 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D1 *)(&D32))->pic_width_in_mb = pDivx3DecParam->PicWidthInMb - 1;
    ((DIVX3_V400R004_PICDNMSG_D1 *)(&D32))->pic_height_in_mb = pDivx3DecParam->PicHeightInMb - 1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);

    /* D2 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D2 *)(&D32))->quantizer = pDivx3DecParam->quantizer;
    ((DIVX3_V400R004_PICDNMSG_D2 *)(&D32))->rounding_type = pDivx3DecParam->rounding_type;
    ((DIVX3_V400R004_PICDNMSG_D2 *)(&D32))->has_skip = pDivx3DecParam->has_skips;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D2 = 0x%x\n", D32);

    /* D3 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D3 *)(&D32))->alternative_I_AC_chrom_DCT = pDivx3DecParam->alternative_I_AC_chrom_DCT;
    ((DIVX3_V400R004_PICDNMSG_D3 *)(&D32))->alternative_I_AC_lum_DCT = pDivx3DecParam->alternative_I_AC_lum_DCT;
    ((DIVX3_V400R004_PICDNMSG_D3 *)(&D32))->alternative_I_DC_DCT = pDivx3DecParam->alternative_I_DC_DCT;
    ((DIVX3_V400R004_PICDNMSG_D3 *)(&D32))->alternative_P_AC_DCT = pDivx3DecParam->alternative_P_AC_DCT;
    ((DIVX3_V400R004_PICDNMSG_D3 *)(&D32))->alternative_P_DC_DCT = pDivx3DecParam->alternative_P_DC_DCT;
    ((DIVX3_V400R004_PICDNMSG_D3 *)(&D32))->alternative_MV = pDivx3DecParam->alternative_MV;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D3 = 0x%x\n", D32);


    /* D16 */
    p32 = pMsgBase + 16;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D16 *)(&D32))->bit_stream_address_0 = pDivx3DecParam->StreamPhyAddr[0];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D16 = 0x%x\n", D32);

    /* D17 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D17 *)(&D32))->bit_offset_0 = pDivx3DecParam->StreamBitOffset[0];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D17 = 0x%x\n", D32);

    /* D18 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D18 *)(&D32))->bit_len_0 = pDivx3DecParam->StreamLength[0];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D18 = 0x%x\n", D32);

    /* D19 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D19 *)(&D32))->bit_stream_address_1 = pDivx3DecParam->StreamPhyAddr[1];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D19 = 0x%x\n", D32);

    /* D20 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D20 *)(&D32))->bit_offset_1 = pDivx3DecParam->StreamBitOffset[1];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D20 = 0x%x\n", D32);

    /* D21 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D21 *)(&D32))->bit_len_1 = pDivx3DecParam->StreamLength[1];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D21 = 0x%x\n", D32);


    /* D32 */
    p32 = pMsgBase + 32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D32 *)(&D32))->curr_rcn_addr = (pDivx3DecParam->DispFramePhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D32 = 0x%x\n", D32);

    /* D33 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D33 *)(&D32))->fwd_ref_addr = (pDivx3DecParam->FwdRefPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D33 = 0x%x\n", D32);

    /* D34 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D34 *)(&D32))->sed_top_addr = (pHwMem->SedTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D34 = 0x%x\n", D32);
    
    /* D35 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D35 *)(&D32))->pmv_top_addr = (pHwMem->PmvTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D35 = 0x%x\n", D32);
    
    /* D36 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D36 *)(&D32))->it_top_addr = (pHwMem->ItransTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D36 = 0x%x\n", D32);
    
    /* D37 */
    ++p32;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D37 *)(&D32))->pmv_colmb_addr = (pDivx3DecParam->CurrPmvPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D37 = 0x%x\n", D32);

    /* D63 */
    p32 = pMsgBase + 63;
    D32 = 0;
    ((DIVX3_V400R004_PICDNMSG_D63 *)(&D32))->next_slice_para_addr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1] & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);

    return;
}

VOID DIVX3HAL_V400R004_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    UINT32 i, j;
    UINT32 D32;
    UADDR  MsgBlockPhy;
    SINT32 *pMsgBase, *p32;
    SINT32 AddSlice0Flag = 0;
    SINT32 last_mb_in_slice;
    UADDR  next_slice_para_addr;
    MsgBlockPhy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1] & 0xFFFFFFF0;
    pMsgBase = (SINT32 *)MEM_Phy2Vir(MsgBlockPhy);
    VDMHAL_ASSERT(NULL != pMsgBase, "can not map dn msg virtual address!\n");

    if (pDivx3DecParam->slice_start_mbn[0] != 0)
    {
        i = 0;
        /* D0 */
        D32 = 0;
        ((DIVX3_V400R004_SLCDNMSG_D0 *)(&D32))->slice_start_mbn = 0;
        WR_MSGWORD(  pMsgBase + 0 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);

        /* D1 */
        D32 = 0;
        ((DIVX3_V400R004_SLCDNMSG_D1 *)(&D32))->slice_end_mbn = pDivx3DecParam->slice_start_mbn[i] - 1;
        WR_MSGWORD(  pMsgBase + 1 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);

        /* D63 */
        D32 = 0;
        ((DIVX3_V400R004_SLCDNMSG_D63 *)(&D32))->next_slice_para_addr = MsgBlockPhy + (i + 1) * 4 * 64;
        WR_MSGWORD(  pMsgBase + 63 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);
        AddSlice0Flag = 1;
    }

    for (i = 0; i < pDivx3DecParam->TotalSliceNum; i++)
    {
        if ((i > 0) && (pDivx3DecParam->slice_start_mbn[i] <= pDivx3DecParam->slice_start_mbn[i - 1]))
        {
            continue;
        }

        /* D0 */
        p32 = pMsgBase;
        D32 = 0;
        ((DIVX3_V400R004_SLCDNMSG_D0 *)(&D32))->slice_start_mbn = pDivx3DecParam->slice_start_mbn[i];
        WR_MSGWORD(  pMsgBase + 0 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);

        for (j = (i + 1); j < pDivx3DecParam->TotalSliceNum; j++)
        {
            if (pDivx3DecParam->slice_start_mbn[i] < pDivx3DecParam->slice_start_mbn[j])
            {
                break;
            }
        }

        if (j == pDivx3DecParam->TotalSliceNum)
        {
            last_mb_in_slice = ((pDivx3DecParam->PicWidthInMb) * (pDivx3DecParam->PicHeightInMb)) - 1;
            next_slice_para_addr = 0;
        }
        else
        {
            last_mb_in_slice = (pDivx3DecParam->slice_start_mbn[j]) - 1;
            next_slice_para_addr = MsgBlockPhy + j * 4 * 64 + AddSlice0Flag * 64;
        }

        /* D1 */
        D32 = 0;
        ((DIVX3_V400R004_SLCDNMSG_D1 *)(&D32))->slice_end_mbn = last_mb_in_slice;
        WR_MSGWORD(  pMsgBase + 1 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);

        /* D63 */
        D32 = 0;
        ((DIVX3_V400R004_SLCDNMSG_D63 *)(&D32))->next_slice_para_addr = next_slice_para_addr;
        WR_MSGWORD( pMsgBase + 63 + i * 64 + AddSlice0Flag * 64, D32 );
        dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);
        i = j - 1;
    }

    return;
}

#endif //__VDM_HAL_REAL9_C__
