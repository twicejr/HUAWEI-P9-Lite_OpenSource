
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vdm_hal_avs.c
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

#ifndef __VDM_HAL_AVS_C__
#define __VDM_HAL_AVS_C__


#include 	"basedef.h"
#include 	"vfmw.h"
#include 	"mem_manage.h"
#include 	"public.h"
#include    "vdm_hal_v400r004_api.h"
#include    "vdm_hal_v400r004_local.h"
#include 	"vdm_hal_v400r004_avs.h"
#include    "scd_drv.h"

/*----------------------------------------------*
* 常量定义                                     *
*----------------------------------------------*/
static const UINT32 Avs_Vfmw_BitMask[33] =
{
    0,                          0x1,       0x3,       0x7,       0xf,           0x1f,           0x3f,           0x7f,
    0xff,         0x1ff,     0x3ff,             0x7ff,     0xfff,     0x1fff,     0x3fff,     0x7fff,
    0xffff,             0x1ffff,   0x3ffff,   0x7ffff,   0xfffff,       0x1fffff,       0x3fffff,       0x7fffff,
    0xffffff, 0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff, 0x1fffffff, 0x3fffffff, 0x7fffffff,
    0xffffffff
};

/*----------------------------------------------*
* 宏定义                                       *
*----------------------------------------------*/
//#define BIGENDIAN(val) (((val>>24)&0xff)|(((val>>16)&0xff)<<8)|(((val>>8)&0xff)<<16)|((val&0xff)<<24))
#define BIGENDIAN
#define AVS_VFMW_SETBIT(l, h, val) (((val) & Avs_Vfmw_BitMask[((h) - (l) + 1)]) << (l))
#define AVS_VFMW_GETBIT(l, h, val) (((val) >> (l)) & Avs_Vfmw_BitMask[((h) - (l) + 1)])

/************************************************************************/
/*  函数实现                                                            */
/************************************************************************/
SINT32 AVSHAL_V400R004_WirteSlicMsg(AVS_DEC_PARAM_S *pAvsDecParam, UADDR stream_base_addr, SINT32 VdhId);

SINT32 AVSHAL_V400R004_InitHal(UADDR CodeTabAddr)
{
    return VDMHAL_OK;
}


SINT32 AVSHAL_V400R004_StartDec(AVS_DEC_PARAM_S *pAvsDecParam, SINT32 VdhId)
{
    SINT32 i, k;
    SINT32 D32;
    SINT32 *pMsgBase, *p32;
    UINT32 height_in_mb;
    UADDR stream_base_addr, tmp_base_addr;
    UINT32 level = 16;
    SINT32 datTmp;
    SINT32 s32Ret;
    UINT32 WQNUM =  16;

    /* 1.  检查参数是否超出规格 */
    VDMHAL_ASSERT_RET( pAvsDecParam->PicWidthInMb <= MAX_IMG_WIDTH_IN_MB, "picture width out of range");
    VDMHAL_ASSERT_RET( pAvsDecParam->PicHeightInMb <= MAX_IMG_HEIGHT_IN_MB, "picture width out of range");

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    if ( NULL == g_HwMem[VdhId].pVdmRegVirAddr )
    {
        if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr)) )
        {
            g_HwMem[VdhId].pVdmRegVirAddr = p32;
        }
        else
        {
            dprint(PRN_FATAL, " %s %d vdm register virtual address not mapped, reset failed!\n", __func__, __LINE__);
            return VDMHAL_ERR;
        }
    }

    for (i = 0, stream_base_addr = 0xFFFFFFFF; i < pAvsDecParam->SlcNum; i++)
    {
        /*查找最小的码流包地址作为基地址时，如果有分包的情况，则码流包开头并非起始码，因此不要在此判断*/
        for (k = 0; k < 2; k++)
        {
            if ((pAvsDecParam->SlcStr[i].stream_phy_addr[k] > 0) && (pAvsDecParam->SlcStr[i].stream_lenInByte[k] > 0))
            {
                tmp_base_addr = pAvsDecParam->SlcStr[i].stream_phy_addr[k] & 0xFFFFFFF0;
                stream_base_addr = (stream_base_addr < tmp_base_addr) ? stream_base_addr : tmp_base_addr;
            }
        }
    }

    if (stream_base_addr == 0xFFFFFFFF)
    {
        dprint(PRN_FATAL, "stream_base_addr = %#x\n", stream_base_addr);
        return VDMHAL_ERR;
    }

    /* 2.  配置寄存器(启动寄存器除外) */
    //BASIC_V400R004_CFG0
    D32 = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->mbamt_to_dec         = pAvsDecParam->PicWidthInMb * pAvsDecParam->PicHeightInMb - 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->load_qmatrix_flag    = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->marker_bit_detect_en = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->ac_last_detect_en    = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->coef_idx_detect_en   = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->vop_type_detect_en   = 0;
#ifdef ENV_SOS_KERNEL
    ((BASIC_V400R004_CFG0*)(&D32))->sec_mode_en           = 1; 
#else
    ((BASIC_V400R004_CFG0*)(&D32))->sec_mode_en           = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG0 = 0x%x\n", D32);

    //BASIC_V400R004_CFG1
    D32 = 0x30000000;
    ((BASIC_V400R004_CFG1 *)(&D32))->video_standard = 0x6;
    ((BASIC_V400R004_CFG1 *)(&D32))->ddr_stride     = pAvsDecParam->VahbStride >> 6;
    ((BASIC_V400R004_CFG1 *)(&D32))->fst_slc_grp    = 1;
    if (pAvsDecParam->PicCodingType == 0 || pAvsDecParam->PicCodingType == 1 || pAvsDecParam->PicCodingType == 3)
    {
        ((BASIC_V400R004_CFG1 *)(&D32))->mv_output_en = 1;
    }
    else
    {
        ((BASIC_V400R004_CFG1 *)(&D32))->mv_output_en = 0;
    }
    ((BASIC_V400R004_CFG1 *)(&D32))->uv_order_en      = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->vdh_2d_en        = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->max_slcgrp_num     = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->line_num_output_en = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->compress_en = pAvsDecParam->Compress_en;
    ((BASIC_V400R004_CFG1 *)(&D32))->ppfd_en     = 0;

    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG1 = 0x%x\n", D32);

    //AVM_V400R004_ADDR
    D32 = 0;
    ((AVM_V400R004_ADDR *)(&D32))->av_msg_addr = g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId);
    dprint(PRN_VDMREG, "AVM_V400R004_ADDR = 0x%x\n", D32);

    //VAM_V400R004_ADDR
    D32 = 0;
    ((VAM_V400R004_ADDR *)(&D32))->va_msg_addr = g_HwMem[VdhId].MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "VAM_V400R004_ADDR = 0x%x\n", D32);

    //STREAM_V400R004_BASE_ADDR
    D32 = 0;
    ((STREAM_V400R004_BASE_ADDR *)(&D32))->stream_base_addr = stream_base_addr;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "STREAM_V400R004_BASE_ADDR = 0x%x\n", D32);

    //EMAR_ID
    if (pAvsDecParam->PicWidthInMb > 120)
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
    WR_VREG( VREG_V400R004_RCN_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_DBLK_TO,   D32, VdhId );
    WR_VREG( VREG_V400R004_PPFD_TO,   D32, VdhId );

    //YSTADDR_V400R004_1D
    D32 = 0;
    ((YSTADDR_V400R004_1D *)(&D32))->ystaddr_1d = pAvsDecParam->CurPicAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTADDR_V400R004_1D = 0x%x\n", D32);

    //YSTRIDE_V400R004_1D
    D32 = 0;
    height_in_mb = pAvsDecParam->PicHeightInMb;
    ((YSTRIDE_V400R004_1D *)(&D32))->ystride_1d = pAvsDecParam->VahbStride; //pAvsDecParam->VahbStride*32;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTRIDE_V400R004_1D = 0x%x\n", D32);

    //UVOFFSET_V400R004_1D
    D32 = 0;
	level = 0;

    ((UVOFFSET_V400R004_1D *)(&D32))->uvoffset_1d = (pAvsDecParam->VahbStride) * (((height_in_mb + 1) / 2) * 2)
            +  ((height_in_mb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId );
    dprint(PRN_VDMREG, "UVOFFSET_V400R004_1D = 0x%x\n", D32);

    //PRCNUM_1D_CNT
    D32 = ((height_in_mb * 16 + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId );
    dprint(PRN_VDMREG, "PRCNUM_1D_CNT = 0x%x\n", D32);
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
    D32 = 0;   //AVS固定帧存,以保证安全. z56361, 2011-3-25
    WR_VREG( VREG_V400R004_REF_PIC_TYPE, D32, VdhId );
    dprint(PRN_VDMREG, "VREG_V400R004_REF_PIC_TYPE = 0x%x\n", D32);

    //FF_V400R004_APT_EN
    D32 = 0; //USE_FF_APT_EN;  // 0:frm save, 1:apt save  //AVS固定帧存,以保证安全. z56361, 2011-3-25
    WR_VREG( VREG_V400R004_FF_APT_EN, D32, VdhId );
    dprint(PRN_VDMREG, "VREG_V400R004_FF_APT_EN = 0x%x\n", D32);

    // INT
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );

#if 0
    // INT_V400R004_MASK
#ifdef VDM_BUSY_WAITTING
    // 中断屏蔽
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFF, VdhId);
#else
    // 中断打开
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFE, VdhId );
#endif
#endif

    /* 3.  配置下行消息池 */
    pMsgBase = (SINT32 *)MEM_Phy2Vir(g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);

    VDMHAL_ASSERT_RET( pMsgBase != NULL, "can not map down msg virtual address!");
    // D0
    p32 = pMsgBase;
    ((AVS_V400R004_DWNMSG_D0 *)(&D32))->pic_width_in_mb  = pAvsDecParam->PicWidthInMb - 1;
    ((AVS_V400R004_DWNMSG_D0 *)(&D32))->pic_height_in_mb = pAvsDecParam->PicHeightInMb - 1;
    ((AVS_V400R004_DWNMSG_D0 *)(&D32))->chroma_format = pAvsDecParam->ChromaFormat;
    ((AVS_V400R004_DWNMSG_D0 *)(&D32))->sample_precision = pAvsDecParam->SamplePrecision;
    ((AVS_V400R004_DWNMSG_D0 *)(&D32))->rsv0 = 0;
    ((AVS_V400R004_DWNMSG_D0 *)(&D32))->rsv1 = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D0 = 0x%x\n", D32);

    // D1
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->progressive_frame   = pAvsDecParam->ProgrsvFrame;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->picture_structure   = pAvsDecParam->PicStruct;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->pic_coding_type     = pAvsDecParam->PicCodingType;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->top_field_first     = pAvsDecParam->TopFieldFirst;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->repeat_first_field  = pAvsDecParam->RepeatFirstField;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->fix_qp              = pAvsDecParam->FixQPFlag;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->pic_qp              = pAvsDecParam->PicQuant;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->skip_mode_flag      = pAvsDecParam->SkipModeFlag;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->ad_pred_mode_disable = pAvsDecParam->AdvPredModeDisable;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->pic_ref_flag        = pAvsDecParam->PicRefFlag;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->no_fwd_ref_flag     = pAvsDecParam->NoFwdRefFlag;
    ((AVS_V400R004_DWNMSG_D1 *)(&D32))->rsv = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D1 = 0x%x\n", D32);

    // D2
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D2 *)(&D32))->loop_flt_disable    = pAvsDecParam->LoopFiltDisable;
    ((AVS_V400R004_DWNMSG_D2 *)(&D32))->loop_flt_para_flag  = pAvsDecParam->LoopFiltParamFlag;
    ((AVS_V400R004_DWNMSG_D2 *)(&D32))->alpha_c_offset      = pAvsDecParam->AlphaOffset;
    ((AVS_V400R004_DWNMSG_D2 *)(&D32))->beta_offset         = pAvsDecParam->BetaOffset;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D2 = 0x%x\n", D32);

    // D3
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D3 *)(&D32))->fwd_top_field_first_0 = pAvsDecParam->FwdTopFieldFirst0;
    ((AVS_V400R004_DWNMSG_D3 *)(&D32))->fwd_picture_structure_0 = pAvsDecParam->FwdPicStruct0;
    ((AVS_V400R004_DWNMSG_D3 *)(&D32))->fwd_top_field_first_1 = pAvsDecParam->FwdTopFieldFirst1;
    ((AVS_V400R004_DWNMSG_D3 *)(&D32))->fwd_picture_structure_1 = pAvsDecParam->FwdPicStruct1;
    ((AVS_V400R004_DWNMSG_D3 *)(&D32))->bwd_top_field_first = pAvsDecParam->BwdTopFieldFirst;
    ((AVS_V400R004_DWNMSG_D3 *)(&D32))->bwd_picture_structure = pAvsDecParam->BwdPicStruct;
    ((AVS_V400R004_DWNMSG_D3 *)(&D32))->rsv = 0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D3 = 0x%x\n", D32);

    // D4
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D4 *)(&D32))->bwd_address = (pAvsDecParam->BwdRefPicAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D4 = 0x%x\n", D32);

    // D5
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D5 *)(&D32))->fwd_address_0 = (pAvsDecParam->FwdRefPic0Addr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D5 = 0x%x\n", D32);

    // D6
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D6 *)(&D32))->fwd_address_1 = (pAvsDecParam->FwdRefPic1Addr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D6 = 0x%x\n", D32);

    // D7
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D7 *)(&D32))->rcn_address = (pAvsDecParam->rcn_address + 0xF) & 0xFFFFFFF0; //pAvsDecParam->CurPicAddr & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D7 = 0x%x\n", D32);

    // D8
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D8 *)(&D32))->col_pic_type   = pAvsDecParam->ColPicType;
    ((AVS_V400R004_DWNMSG_D8 *)(&D32))->col_pic_struct = pAvsDecParam->ColPicStruct;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D8 = 0x%x\n", D32);

    // D9
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D9 *)(&D32))->bit_stream_address_0 = pAvsDecParam->StreamPhyAddr[0];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D9 = 0x%x\n", D32);

    // D10
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D10 *)(&D32))->bit_len_0    = pAvsDecParam->StreamLength[0];
    ((AVS_V400R004_DWNMSG_D10 *)(&D32))->bit_offset_0 = pAvsDecParam->StreamBitOffset[0];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D10 = 0x%x\n", D32);

    // D11
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D11 *)(&D32))->bit_stream_address_1 = pAvsDecParam->StreamPhyAddr[1];
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D11 = 0x%x\n", D32);

    // D12
    ++p32;
    D32 = 0;
#if 1
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->weighting_quant_flag        = pAvsDecParam->weighting_quant_flag;
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->chroma_quant_param_disable  = pAvsDecParam->chroma_quant_param_disable;
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->chroma_quant_param_delta_v  = pAvsDecParam->chroma_quant_param_delta_v;
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->chroma_quant_param_delta_u  = pAvsDecParam->chroma_quant_param_delta_u;
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->aec_enable                  = pAvsDecParam->aec_enable;
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->p_filed_enhanced_flag       = pAvsDecParam->p_filed_enhanced_flag;
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->b_filed_enhanced_flag       = pAvsDecParam->b_filed_enhanced_flag;
#endif
#if 0
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->bit_len_1    = pAvsDecParam->StreamLength[1];
    ((AVS_V400R004_DWNMSG_D12 *)(&D32))->bit_offset_1 = pAvsDecParam->StreamBitOffset[1];
#endif
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D12 = 0x%x\n", D32);

    // D13
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D13 *)(&D32))->pmv_top_addr = (g_HwMem[VdhId].PmvTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D13 = 0x%x\n", D32);

    // D14
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D14 *)(&D32))->topmb_intra_addr = (g_HwMem[VdhId].RcnTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D14 = 0x%x\n", D32);

    // D15
    ++p32;  //NULL

    // D16
    ++p32;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D16 *)(&D32))->colpic_mv_addr = (pAvsDecParam->ColPmvAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D16 = 0x%x\n", D32);

    // D17 ~ D48, PMV参数表
    for ( i = 17; i < 49; i++ )
    {
        p32 = pMsgBase + i;
        D32 = pAvsDecParam->PmvConfigTab[i - 17];
        WR_MSGWORD( p32, D32 );
    }

    // D49
    p32 = pMsgBase + 49;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D49 *)(&D32))->pmv_colmb_addr = (pAvsDecParam->CurPmvAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D49 = 0x%x\n", D32);

    // D50
    p32 = pMsgBase + 50;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D50 *)(&D32))->dblk_top_addr = (g_HwMem[VdhId].DblkTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D50 = 0x%x\n", D32);
    // D51
    p32 = pMsgBase + 51;
    D32 = 0;
    ((AVS_V400R004_DWNMSG_D51 *)(&D32))->sed_top_addr = (g_HwMem[VdhId].SedTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D51 = 0x%x\n", D32);

    // D63
    p32 = pMsgBase + 63;
    D32 = g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] + (64 + WQNUM) * 4; //g_HwMem.MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX+1];// + 64*sizeof(UINT32);
    WR_MSGWORD( p32, D32 );
    dprint(PRN_DNMSG, "D63 = 0x%x\n", D32);
#if 1
    p32 = pMsgBase + 64;

    if (1 == pAvsDecParam->weighting_quant_flag)
    {
        for (i = 0; i < WQNUM; i++)
        {
#if 0
            D32 = AVS_VFMW_SETBIT(0, 7, pAvsDecParam->cur_wq_matrix[i * 4 + 0]) |
                  AVS_VFMW_SETBIT(8, 15, pAvsDecParam->cur_wq_matrix[i * 4 + 1]) |
                  AVS_VFMW_SETBIT(16, 23, pAvsDecParam->cur_wq_matrix[i * 4 + 2]) |
                  AVS_VFMW_SETBIT(24, 31, pAvsDecParam->cur_wq_matrix[i * 4 + 3]);
#endif

            if (i % 2 == 0)
            {
                D32 =
                    AVS_VFMW_SETBIT(24, 31, pAvsDecParam->cur_wq_matrix[i * 4 + 6]) |
                    AVS_VFMW_SETBIT(16, 23, pAvsDecParam->cur_wq_matrix[i * 4 + 4]) |
                    AVS_VFMW_SETBIT(8, 15, pAvsDecParam->cur_wq_matrix[i * 4 + 2]) |
                    AVS_VFMW_SETBIT(0, 7, pAvsDecParam->cur_wq_matrix[i * 4 + 0]);
            }
            else
            {
                D32 =
                    AVS_VFMW_SETBIT(24, 31, pAvsDecParam->cur_wq_matrix[i * 4 + 3]) |
                    AVS_VFMW_SETBIT(16, 23, pAvsDecParam->cur_wq_matrix[i * 4 + 1]) |
                    AVS_VFMW_SETBIT(8, 15, pAvsDecParam->cur_wq_matrix[i * 4 - 1]) |
                    AVS_VFMW_SETBIT(0, 7, pAvsDecParam->cur_wq_matrix[i * 4 - 3]);
            }

            WR_MSGWORD( p32, D32 );
            p32++;
        }
    }

#endif
    s32Ret = AVSHAL_V400R004_WirteSlicMsg(pAvsDecParam, stream_base_addr, VdhId);
    VDMHAL_ASSERT_RET(VDMHAL_OK == s32Ret, "s32Ret is not VDMHAL_OK");

    return VDMHAL_OK;
}

SINT32 AVSHAL_V400R004_WirteSlicMsg(AVS_DEC_PARAM_S *pAvsDecParam, UADDR stream_base_addr, SINT32 VdhId)
{
    SINT32 i, j, k = 0, TotalSliceNum ;
    //STREAM_SEG_PACKET_S *pSeg;
    SINT32 D32 = 0;
    SINT32 *pMsgBase;
    UADDR MsgBlockPhy;
    UINT32 bit_offset_0 = 0;
    UINT32 bit_len_0 = 0;
    UADDR  bit_stream_addr_0 = 0;

    UINT32 bit_offset_1 = 0;
    UINT32 bit_len_1 = 0;
    UADDR  bit_stream_addr_1 = 0;                                                                                                                                

    UINT32 slice_end_mbn = 0;
    UINT32 slice_start_mbn = 0;
    UADDR next_slice_para_addr;
    SINT32 AddSlice0Flag = 0;
    int  WQNUM =  16;

    AVS_SLCSTR_S *SliceInfo = pAvsDecParam->SlcStr;
    TotalSliceNum = 0;

    MsgBlockPhy = g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] + 4 * (64 + WQNUM);
    pMsgBase = (SINT32 *)MEM_Phy2Vir(g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);
    VDMHAL_ASSERT_RET( pMsgBase != NULL, "can not map down msg virtual address!");

    pMsgBase = pMsgBase + 64 + WQNUM;

    if (SliceInfo[0].slice_start_mbn != 0)
    {
        i = 0;
        bit_stream_addr_0 = (SliceInfo[i].stream_phy_addr[0] + 4 - stream_base_addr) & 0xFFFFFFF0;
        bit_offset_0 = ((SliceInfo[i].stream_phy_addr[0] + 4  - stream_base_addr) & 0xf) * 8;
        bit_len_0 = 0;//head have 32 bits
        bit_stream_addr_1 = 0;
        bit_offset_1 = 0;
        bit_len_1 = 0;

      #if 0
        if(bit_offset_0 <8)
        {
           bit_stream_addr_0 = bit_stream_addr_0 -4;
           bit_offset_0= 128 - (8 - bit_offset_0);
           bit_len_0 = bit_len_0 + 8;
        }
      #else
        if(bit_offset_0 < 8)
        {
           bit_stream_addr_0 = bit_stream_addr_0 - 0x10;
           bit_offset_0 = bit_offset_0 + 128 - 8;
           bit_len_0 = bit_len_0 + 8;
        }
      #endif
        else
        {
            bit_offset_0 = bit_offset_0 - 8;
            bit_len_0 = bit_len_0 + 8;
        }

        //D0
        D32 = AVS_VFMW_SETBIT(25, 31, bit_offset_0) | AVS_VFMW_SETBIT(0, 24, bit_len_0);
        WR_MSGWORD( pMsgBase + i * 64 + 0, D32);
        //D1
        D32 = AVS_VFMW_SETBIT(0, 23, bit_stream_addr_0);
        WR_MSGWORD( pMsgBase + i * 64 + 1, D32);
        //D2
        D32 = AVS_VFMW_SETBIT(25, 31, bit_offset_1) | AVS_VFMW_SETBIT(0, 24, bit_len_1);
        WR_MSGWORD( pMsgBase + i * 64 + 2, D32);
        //D3
        D32 = AVS_VFMW_SETBIT(0, 23, bit_stream_addr_1);
        WR_MSGWORD( pMsgBase + i * 64 + 3, D32);
        //D4
        slice_start_mbn = 0;
        slice_end_mbn = (SliceInfo[0].slice_start_mbn) - 1;
        D32 = AVS_VFMW_SETBIT(16, 31, slice_end_mbn) | AVS_VFMW_SETBIT(0, 15, slice_start_mbn);
        WR_MSGWORD( pMsgBase + i * 64 + 4, D32);
        //D63
        D32 = MsgBlockPhy + (i + 1) * 4 * 64;
        WR_MSGWORD( pMsgBase + i * 64 + 63, D32);
        AddSlice0Flag = 1;
    }

    for (i = 0, j = 0; i < pAvsDecParam->SlcNum; i++)
    {
        if (j < MAX_IMG_HEIGHT_IN_MB)
        {
            if ((SliceInfo[i].slice_start_mbn <= SliceInfo[i - 1].slice_start_mbn) && (i > 0))
            {
                continue;
            }

            bit_stream_addr_0 = (SliceInfo[i].stream_phy_addr[0] + 4 - stream_base_addr) & 0xFFFFFFF0;
            bit_offset_0 = ((SliceInfo[i].stream_phy_addr[0] + 4  - stream_base_addr) & 0xf) * 8;
           
            bit_len_0 = SliceInfo[i].stream_lenInByte[0] * 8;// - 32;//head have 32 bits

            //this streamseg is two packets
            if ((SliceInfo[i].stream_phy_addr[1] > 0) && (pAvsDecParam->SlcStr[i].stream_lenInByte[1] > 0))
            {
                bit_stream_addr_1 = ((SliceInfo[i].stream_phy_addr[1]  - stream_base_addr) & 0xfffffff0);
                bit_offset_1 = ((SliceInfo[i].stream_phy_addr[1]  - stream_base_addr) & 0xf) * 8;
                bit_len_1 = SliceInfo[i].stream_lenInByte[1] * 8;

                if (bit_len_0 == 0)
                {
                    bit_stream_addr_0 = bit_stream_addr_1;
                    bit_offset_0 = bit_offset_1;
                    bit_len_0 = bit_len_1;
                    bit_stream_addr_1 = 0;
                    bit_offset_1 = 0;
                    bit_len_1 = 0;
                }
            }
            else
            {
                //this slc is one packet
                bit_stream_addr_1 = 0;
                bit_offset_1 = 0;
                bit_len_1 = 0;
            }

          #if 0
            if(bit_offset_0 <8)
            {
               bit_stream_addr_0 = bit_stream_addr_0 -4;
               bit_offset_0= 128 - (8 -bit_offset_0);
               bit_len_0 = bit_len_0 +8;
            }
          #else
            if(bit_offset_0 < 8)
            {
               bit_stream_addr_0 = bit_stream_addr_0 - 0x10;
               bit_offset_0 = bit_offset_0 + 128 - 8;
               bit_len_0 = bit_len_0 + 8;
            }
          #endif
            else
            {
                bit_offset_0 = bit_offset_0 - 8;
                bit_len_0 = bit_len_0 + 8;
            }

            //D0
            D32 = AVS_VFMW_SETBIT(25, 31, bit_offset_0) | AVS_VFMW_SETBIT(0, 24, bit_len_0);
            WR_MSGWORD( pMsgBase + i * 64 + 0, D32);
            //D1
            D32 = AVS_VFMW_SETBIT(0, 23, bit_stream_addr_0);
            WR_MSGWORD( pMsgBase + i * 64 + 1, D32);
            //D2
            D32 = AVS_VFMW_SETBIT(25, 31, bit_offset_1) | AVS_VFMW_SETBIT(0, 24, bit_len_1);
            WR_MSGWORD( pMsgBase + i * 64 + 2, D32);
            //D3
            D32 = AVS_VFMW_SETBIT(0, 23, bit_stream_addr_1);
            WR_MSGWORD( pMsgBase + i * 64 + 3, D32);

            //D4
            for (k = (i + 1); k < pAvsDecParam->SlcNum; k++)
            {
                if (SliceInfo[i].slice_start_mbn < SliceInfo[k].slice_start_mbn)
                {
                    break;
                }
            }

            if (k == pAvsDecParam->SlcNum)
            {
                slice_end_mbn = ((pAvsDecParam->PicWidthInMb) * (pAvsDecParam->PicHeightInMb)) - 1;
                next_slice_para_addr = 0;
            }
            else
            {
                slice_end_mbn = (SliceInfo[k].slice_start_mbn) - 1;
                next_slice_para_addr = MsgBlockPhy + k * 4 * 64 + AddSlice0Flag * 4 * 64;
            }

            slice_start_mbn = SliceInfo[i].slice_start_mbn;
            D32 = AVS_VFMW_SETBIT(16, 31, slice_end_mbn) | AVS_VFMW_SETBIT(0, 15, slice_start_mbn);
            WR_MSGWORD( pMsgBase + i * 64 + 4, D32);
            //D63
            D32 = next_slice_para_addr;
            WR_MSGWORD( pMsgBase + i * 64 + 63, D32);
            j++;
        }

        i = k - 1;
    }

    return VDMHAL_OK;
}

#endif //__VDM_HAL_AVS_C__
