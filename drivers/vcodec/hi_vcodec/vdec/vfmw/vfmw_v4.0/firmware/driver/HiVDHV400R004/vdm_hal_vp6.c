
/******************************************************************************

  ???? (C), 2001-2011, ????????

******************************************************************************
    ? ? ?   : vdm_hal_avs.c
    ? ? ?   : ??
    ?    ?   :
    ????   :
    ????   :
    ????   : VDMV300 ????


  ????   :
    1.?    ? : 2009-03-04
    ?    ?   :
    ????   :

******************************************************************************/

#ifndef __VDM_HAL_VP6_C__
#define __VDM_HAL_VP6_C__


#include "basedef.h"
#include "vfmw.h"
#include "mem_manage.h"
#include "public.h"
#include "vp6.h"
#include "vdm_hal.h"
#include "vdm_hal_v400r004_vp6.h"
#include "vdm_hal_v400r004_local.h"

/************************************************************************/
/*  ????                                                            */
/************************************************************************/
SINT32 VP6HAL_V400R004_InitHal(UADDR CodeTabAddr)
{
    return VDMHAL_OK;
}

SINT32 VP6HAL_V400R004_StartDec(VP6_DEC_PARAM_S *pVp6DecParam, SINT32 VdhId)
{
    VDMHAL_HWMEM_S *pHwMem = &g_HwMem[VdhId];
    SINT32 *p32;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    /* 1.  ?????????? */
    VDMHAL_ASSERT_RET(((pVp6DecParam->PicWidthInMb > 0) && (pVp6DecParam->PicWidthInMb <= MAX_IMG_WIDTH_IN_MB)), "picture width out of range");
    VDMHAL_ASSERT_RET(((pVp6DecParam->PicHeightInMb > 0) && (pVp6DecParam->PicHeightInMb <= MAX_IMG_HEIGHT_IN_MB)), "picture height out of range");

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

    /* 2.  ?????(???????) */
    VP6HAL_V400R004_CfgReg(pVp6DecParam, pHwMem, VdhId);

    /* 3.  ??????? */
    VP6HAL_V400R004_CfgDnMsg(pVp6DecParam, pHwMem , VdhId);
    
    return VDMHAL_OK;
}

SINT32 VP6HAL_V400R004_CfgReg(VP6_DEC_PARAM_S *pVp6DecParam, VDMHAL_HWMEM_S *pHwMem , SINT32 VdhId)
{
    SINT32 D32;
    UINT32 datTmp;
    UINT32 width_in_mb, ystride;
    SINT32 *p32;
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
    ((BASIC_V400R004_CFG0 *)(&D32))->mbamt_to_dec      = pVp6DecParam->PicWidthInMb * pVp6DecParam->PicHeightInMb - 1;
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
    ((BASIC_V400R004_CFG1 *)(&D32))->video_standard    = 0xA;
    ((BASIC_V400R004_CFG1 *)(&D32))->ddr_stride        = pVp6DecParam->VahbStride >> 6;
    ((BASIC_V400R004_CFG1 *)(&D32))->fst_slc_grp       = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->mv_output_en      = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->uv_order_en       = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->vdh_2d_en         = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->max_slcgrp_num    = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->compress_en       = pVp6DecParam->Compress_en;
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
    ((STREAM_V400R004_BASE_ADDR *)(&D32))->stream_base_addr = pVp6DecParam->StreamBaseAddr;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId);
    dprint(PRN_VDMREG, "STREAM_BASE_ADDR = 0x%x\n", D32);

    //PPFD_V400R004_BUF_ADDR
    D32 = 0;
    ((PPFD_V400R004_BUF_ADDR *)(&D32))->ppfd_buf_addr = pHwMem->PpfdBufAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_PPFD_BUF_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "PPFD_V400R004_BUF_ADDR = 0x%x\n", D32);

    //PPFD_V400R004_BUF_LEN
    D32 = 0;
    ((PPFD_V400R004_BUF_LEN *)(&D32))->ppfd_buf_len = pHwMem->PpfdBufLen;
    WR_VREG( VREG_V400R004_PPFD_BUF_LEN, D32, VdhId );
    dprint(PRN_VDMREG, "PPFD_V400R004_BUF_LEN = 0x%x\n", D32);

    //EMAR_ID
    if (pVp6DecParam->PicWidthInMb > 256)
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
    WR_VREG( VREG_V400R004_SED_TO,    D32, VdhId);
    WR_VREG( VREG_V400R004_ITRANS_TO, D32, VdhId);
    WR_VREG( VREG_V400R004_PMV_TO,    D32, VdhId);
    WR_VREG( VREG_V400R004_PRC_TO,    D32, VdhId);
    WR_VREG( VREG_V400R004_RCN_TO,    D32, VdhId);
    WR_VREG( VREG_V400R004_DBLK_TO,   D32, VdhId);
    WR_VREG( VREG_V400R004_PPFD_TO,   D32, VdhId);

    //YSTADDR_1D
    D32 = 0;
    ((YSTADDR_V400R004_1D *)(&D32))->ystaddr_1d = pVp6DecParam->image_curr_recon_addr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId);
    dprint(PRN_VDMREG, "YSTADDR_1D = 0x%x\n", D32);

    //YSTRIDE_1D
    D32 = 0;
    width_in_mb = pVp6DecParam->PicWidthInMb;
    //((YSTRIDE_1D*)(&D32))->ystride_1d = height_in_mb << 4;
    //    ystride = pVp6DecParam->VahbStride * 32;
    ystride = pVp6DecParam->VahbStride;
    ((YSTRIDE_V400R004_1D *)(&D32))->ystride_1d = ystride;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId);
    dprint(PRN_VDMREG, "YSTRIDE_1D = 0x%x\n", D32);

    //UVOFFSET_1D
    D32 = 0;

	level = 0;

    ((UVOFFSET_V400R004_1D *)(&D32))->uvoffset_1d = (pVp6DecParam->VahbStride) * (((pVp6DecParam->PicHeightInMb + 1) / 2) * 2)
            + ((pVp6DecParam->PicHeightInMb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId);
    dprint(PRN_VDMREG, "UVOFFSET_1D = 0x%x\n", D32);

    //PRCNUM_1D_CNT
    D32 = ((pVp6DecParam->PicHeightInMb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId);
    // dprint(PRN_VDMREG, "PRCNUM_1D_CNT = 0x%x\n", D32);
#if 0
    //PRCMEM1_1D_CNT
    D32 = 0x7F3CFC3C;
    WR_VREG( VREG_V400R004_PRCMEM1_1D_CNT, D32, VdhId);
    dprint(PRN_VDMREG, "PRCMEM1_1D_CNT = 0x%x\n", D32);

    //PRCMEM2_1D_CNT
    D32 = 0xFF3FFF12;
    WR_VREG( VREG_V400R004_PRCMEM2_1D_CNT, D32, VdhId);
    dprint(PRN_VDMREG, "PRCMEM2_1D_CNT = 0x%x\n", D32);
#endif
    //FF_APT_EN
    D32 = 0;  // 0:frm save, 1:apt save
    WR_VREG( VREG_V400R004_FF_APT_EN, D32, VdhId);
    dprint(PRN_VDMREG, "FF_APT_EN = 0x%x\n", D32);

    // INT
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId);

    return VDMHAL_OK;
}

SINT32 VP6HAL_V400R004_CfgDnMsg(VP6_DEC_PARAM_S *pVp6DecParam, VDMHAL_HWMEM_S *pHwMem , SINT32 VdhId)
{
    SINT32 D32, *pMsgBase, *p32;
    UINT8 *TabBaseAddr;
    UINT8 *tmpAddr;
    UINT32 D16_bit_len_0, D16_bit_offset_0, D17_bit_byte_offset_0, Vp6_br_cnt;

    pMsgBase = MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);
    VDMHAL_ASSERT_RET( pMsgBase != NULL, "can not map down msg virtual address!");

    // D0
    D32 = 0;
    p32 = pMsgBase;
    ((VP6_V400R004_DWNMSG_D0 *)(&D32))->pic_coding_type	= pVp6DecParam->FrameType;
    //((VP6_V400R004_DWNMSG_D0*)(&D32))->RefreshGoldenFrame = pVp6DecParam->RefreshGoldenFrame;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);

    // D1
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D1 *)(&D32))->pic_width_in_mb    = pVp6DecParam->PicWidthInMb - 1;
    ((VP6_V400R004_DWNMSG_D1 *)(&D32))->pic_height_in_mb   = pVp6DecParam->PicHeightInMb - 1;
    ((VP6_V400R004_DWNMSG_D1 *)(&D32))->reserved1 = 0;
    ((VP6_V400R004_DWNMSG_D1 *)(&D32))->reserved0 = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);

    // D2
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D2 *)(&D32))->Vp3VersionNo  		= pVp6DecParam->Vp3VersionNo;
    ((VP6_V400R004_DWNMSG_D2 *)(&D32))->VpProfile				= pVp6DecParam->VpProfile;
    ((VP6_V400R004_DWNMSG_D2 *)(&D32))->MultiStream			= pVp6DecParam->MultiStream;
    ((VP6_V400R004_DWNMSG_D2 *)(&D32))->UseHuffman			= pVp6DecParam->UseHuffman;
    ((VP6_V400R004_DWNMSG_D2 *)(&D32))->UseLoopFilter			= (pVp6DecParam->UseLoopFilter >> 1) & 1;
    //((VP6_V400R004_DWNMSG_D2*)(&D32))->ScalingMode			= pVp6DecParam->ScalingMode;
    ((VP6_V400R004_DWNMSG_D2 *)(&D32))->reserved				= 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D2 = 0x%x\n", D32);

    // D3
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D3 *)(&D32))->PredictionFilterAlpha = pVp6DecParam->PredictionFilterAlpha;
    ((VP6_V400R004_DWNMSG_D3 *)(&D32))->PredictionFilterMvSizeThresh = pVp6DecParam->PredictionFilterMvSizeThresh;
    ((VP6_V400R004_DWNMSG_D3 *)(&D32))->PredictionFilterVarThresh = pVp6DecParam->PredictionFilterVarThresh;
    ((VP6_V400R004_DWNMSG_D3 *)(&D32))->PredictionFilterMode = pVp6DecParam->PredictionFilterMode;
    ((VP6_V400R004_DWNMSG_D3 *)(&D32))->reserved = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D3 = 0x%x\n", D32);

    // D4
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D4 *)(&D32))->FLimit = pVp6DecParam->FLimit;
    ((VP6_V400R004_DWNMSG_D4 *)(&D32))->DcQuant = pVp6DecParam->DcQuant;
    ((VP6_V400R004_DWNMSG_D4 *)(&D32))->AcQuant = pVp6DecParam->AcQuant;
    ((VP6_V400R004_DWNMSG_D4 *)(&D32))->reserved = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D4 = 0x%x\n", D32);

    // D8
    p32 += 4;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D8 *)(&D32))->value = pVp6DecParam->value;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D8 = 0x%x\n", D32);

    // D9
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D9 *)(&D32))->range = pVp6DecParam->range;
    ((VP6_V400R004_DWNMSG_D9 *)(&D32))->count = pVp6DecParam->count;
    ((VP6_V400R004_DWNMSG_D9 *)(&D32))->reserved0 = 0;
    ((VP6_V400R004_DWNMSG_D9 *)(&D32))->reserved1 = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D9 = 0x%x\n", D32);

    {
        Vp6_br_cnt = pVp6DecParam->count + 8;
        D16_bit_len_0 = pVp6DecParam->bit0_len_0 + Vp6_br_cnt;

        if (pVp6DecParam->bit0_offset_0 >= Vp6_br_cnt)
        {
            D17_bit_byte_offset_0 = pVp6DecParam->bit0_stream_addr_0;
            D16_bit_offset_0 = pVp6DecParam->bit0_offset_0 - Vp6_br_cnt;
        }
        else
        {
            D17_bit_byte_offset_0 = pVp6DecParam->bit0_stream_addr_0 - 16;
            D16_bit_offset_0 =	128 - (Vp6_br_cnt - pVp6DecParam->bit0_offset_0);
        }
    }

    // D16
    p32 += 7;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D16 *)(&D32))->bit0_len_0 = D16_bit_len_0; //pVp6DecParam->bit0_len_0;  //pAvsDecParam->CurPicAddr & 0xFFFFFFF0;
    ((VP6_V400R004_DWNMSG_D16 *)(&D32))->bit0_offset_0 = D16_bit_offset_0; //pVp6DecParam->bit0_offset_0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D16 = 0x%x\n", D32);

    // D17
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D17 *)(&D32))->bit0_stream_addr_0   = D17_bit_byte_offset_0; //pVp6DecParam->bit0_stream_addr_0;
    ((VP6_V400R004_DWNMSG_D17 *)(&D32))->reserved = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D17 = 0x%x\n", D32);
    tmpAddr = MEM_Phy2Vir(pVp6DecParam->StreamBaseAddr + pVp6DecParam->bit0_stream_addr_0);

    if (NULL == tmpAddr)
    {
        dprint(PRN_ERROR, "LINE:%d NULL == tmpAddr.\n", __LINE__);
    }

    // D18
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D18 *)(&D32))->bit0_len_1    = pVp6DecParam->bit0_len_1;
    ((VP6_V400R004_DWNMSG_D18 *)(&D32))->bit0_offset_1 = pVp6DecParam->bit0_offset_1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D18 = 0x%x\n", D32);

    // D19
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D19 *)(&D32))->bit0_stream_addr_1 = pVp6DecParam->bit0_stream_addr_1;
    ((VP6_V400R004_DWNMSG_D19 *)(&D32))->reserved = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D19 = 0x%x\n", D32);

    // D20
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D20 *)(&D32))->bit1_len_0    = pVp6DecParam->bit1_len_0;
    ((VP6_V400R004_DWNMSG_D20 *)(&D32))->bit1_offset_0 = pVp6DecParam->bit1_offset_0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D20 = 0x%x\n", D32);

    // D21
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D21 *)(&D32))->bit1_stream_addr_0 = pVp6DecParam->bit1_stream_addr_0;
    ((VP6_V400R004_DWNMSG_D21 *)(&D32))->reserved = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D21 = 0x%x\n", D32);

    // D22
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D22 *)(&D32))->bit1_len_1    = pVp6DecParam->bit1_len_1;
    ((VP6_V400R004_DWNMSG_D22 *)(&D32))->bit1_offset_1 = pVp6DecParam->bit1_offset_1;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D22 = 0x%x\n", D32);

    // D23
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D23 *)(&D32))->bit1_stream_addr_1 = pVp6DecParam->bit1_stream_addr_1;
    ((VP6_V400R004_DWNMSG_D23 *)(&D32))->reserved = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D23 = 0x%x\n", D32);

    // D32
    p32 += 9;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D32 *)(&D32))->curr_rcn_addr =
        (pVp6DecParam->image_curr_recon_addr + 0xF) & 0xFFFFFFF0;//pVp6DecParam->tab_addr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D32 = 0x%x\n", D32);

    // D34
    p32 += 2;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D34 *)(&D32))->golden_ref_addr =
        (pVp6DecParam->image_golden_ref_addr + 0xF) & 0xFFFFFFF0;//pVp6DecParam->tab_addr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D34 = 0x%x\n", D32);

    // D35
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D35 *)(&D32))->last_ref_addr =
        (pVp6DecParam->image_last_ref_addr + 0xF) & 0xFFFFFFF0;//pVp6DecParam->tab_addr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D35 = 0x%x\n", D32);

    // D36
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D36 *)(&D32))->sed_top_addr =
        (pHwMem->SedTopAddr + 0xF) & 0xFFFFFFF0;//FIXME: ;//pVp6DecParam->tab_addr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D36 = 0x%x\n", D32);

    // D37
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D37 *)(&D32))->pmv_top_addr =
        (pHwMem->PmvTopAddr + 0xF) & 0xFFFFFFF0;//FIXME: ;//pVp6DecParam->tab_addr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D37 = 0x%x\n", D32);

    // D38
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D38 *)(&D32))->rcn_top_addr =
        (pHwMem->RcnTopAddr + 0xF) & 0xFFFFFFF0;//FIXME: ;//pVp6DecParam->tab_addr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D38 = 0x%x\n", D32);

    // D39
    ++p32;
    D32 = 0;
    ((VP6_V400R004_DWNMSG_D39 *)(&D32))->tab_addr =
        (pHwMem->Vp6TabAddr + 0xF) & 0xFFFFFFF0;//FIXME: ;//pVp6DecParam->tab_addr;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D39 = 0x%x\n", D32);

    tmpAddr = TabBaseAddr = (UINT8 *)MEM_Phy2Vir(((VP6_V400R004_DWNMSG_D39 *)(&D32))->tab_addr);
    tmpAddr = (UINT8 *)MEM_Phy2Vir(pHwMem->Vp6TabAddr);

    if (NULL == tmpAddr || NULL == TabBaseAddr)
    {
	    dprint(PRN_FATAL, "%s: tmpAddr(%p) = NULL / TabBaseAddr(%p) = NULL\n",__func__, tmpAddr, TabBaseAddr);
        return VDMHAL_ERR;
    }

    memset(TabBaseAddr, 0, 4 * 1024);
    memcpy(TabBaseAddr, pVp6DecParam->TblProbModeSame, PROB_MODE_SAME_TBL_LEN);
    TabBaseAddr += PROB_MODE_SAME_TBL_LEN;

    memcpy(TabBaseAddr, pVp6DecParam->TblProbMode, PROB_MODE_TBL_LEN);
    TabBaseAddr += PROB_MODE_TBL_LEN;

    memcpy(TabBaseAddr, pVp6DecParam->TblProbMv, PROB_MV_TBL_LEN);
    TabBaseAddr += PROB_MV_TBL_LEN;

    if (0 == pVp6DecParam->UseHuffman)
    {
        TabBaseAddr = (UINT8 *)MEM_Phy2Vir(((VP6_V400R004_DWNMSG_D39 *)(&D32))->tab_addr) + 0x300;

        if (NULL == TabBaseAddr)
        {
            dprint(PRN_FATAL, "line: %d  NULL == TabBaseAddr.\n", __LINE__);
            return VDMHAL_ERR;
        }

        memcpy(TabBaseAddr, pVp6DecParam->TblDcNodeContexts, DC_NODE_CONTEXTS_TBL_LEN);
        TabBaseAddr += DC_NODE_CONTEXTS_TBL_LEN;

        memcpy(TabBaseAddr, pVp6DecParam->TblZeroProbs, PROB_ZERO_TBL_LEN);
        TabBaseAddr += PROB_ZERO_TBL_LEN;

        memcpy(TabBaseAddr, pVp6DecParam->TblACProbs, PROB_AC_TBL_LEN);
        TabBaseAddr += PROB_AC_TBL_LEN;
    }
    else
    {
        TabBaseAddr = (UINT8 *)MEM_Phy2Vir(((VP6_V400R004_DWNMSG_D39 *)(&D32))->tab_addr) + 0x300;

        if (NULL == TabBaseAddr)
        {
            dprint(PRN_FATAL, "line: %d  NULL == TabBaseAddr.\n", __LINE__);
            return VDMHAL_ERR;
        }

        memcpy(TabBaseAddr, pVp6DecParam->TblAcHuffLUT, AC_HUFF_LUT_TBL_LEN);
        TabBaseAddr += AC_HUFF_LUT_TBL_LEN; //0x600

        memcpy(TabBaseAddr, pVp6DecParam->TblDcHuffLUT, DC_HUFF_LUT_TBL_LEN);
        TabBaseAddr += DC_HUFF_LUT_TBL_LEN; //0x80

        memcpy(TabBaseAddr, pVp6DecParam->TblZeroHuffLUT, ZERO_HUFF_LUT_TBL_LEN);
        TabBaseAddr += ZERO_HUFF_LUT_TBL_LEN;   //0x80
    }

    TabBaseAddr = (UINT8 *)MEM_Phy2Vir(((VP6_V400R004_DWNMSG_D39 *)(&D32))->tab_addr) + 0xA00;

    if (NULL == TabBaseAddr)
    {
        dprint(PRN_FATAL, "line: %d  NULL == TabBaseAddr.\n", __LINE__);
        return VDMHAL_ERR;
    }

    memcpy(TabBaseAddr, pVp6DecParam->TblModifiedScanOrder, MV_MODIFIED_SCAN_ORDER_TBL_LEN);
    TabBaseAddr += MV_MODIFIED_SCAN_ORDER_TBL_LEN;

    memcpy(TabBaseAddr, pVp6DecParam->TblEobOffsetTable, EOB_OFFSET_TBL_LEN);
    TabBaseAddr += EOB_OFFSET_TBL_LEN;

    memcpy(TabBaseAddr, pVp6DecParam->TblHuffTree, HUFF_TREE_LEN);

    TabBaseAddr = (UINT8 *)MEM_Phy2Vir(((VP6_V400R004_DWNMSG_D39 *)(&D32))->tab_addr) + 0x800 + 0x300;

    if (NULL == TabBaseAddr)
    {
        dprint(PRN_FATAL, "line: %d  NULL == TabBaseAddr.\n", __LINE__);
        return VDMHAL_ERR;
    }

    memcpy(TabBaseAddr, pVp6DecParam->TblHuffTree, HUFF_TREE_LEN);
    TabBaseAddr += HUFF_TREE_LEN;
    
    return VDMHAL_OK;
}

#endif //__VDM_HAL_AVS_C__
