


#ifndef __VDM_HAL_VC1_C__
#define __VDM_HAL_VC1_C__

#include "basedef.h"
#include "public.h"
#include "vdm_hal_v400r004_api.h"
#include "vdm_hal_v400r004_local.h"
#include "vdm_hal_v400r004_vc1.h"


SINT32 VC1HAL_V400R004_CfgReg( VC1_DEC_PARAM_S *pVc1DecParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId);
SINT32 VC1HAL_V400R004_CfgDnMsg(VC1_DEC_PARAM_S *pVc1DecParam, VDMHAL_HWMEM_S *pHwMem);
SINT32 VC1HAL_V400R004_StartDec( VC1_DEC_PARAM_S *pVc1DecParam, SINT32 VdhId  );
void   VC1HAL_V400R004_CfgSliceMsg(VC1_DEC_PARAM_S *pVc1DecParam, VDMHAL_HWMEM_S *pHwMem);

SINT32 VC1HAL_V400R004_InitHal(UADDR CodeTabAddr)
{
    return VDMHAL_OK;
}

SINT32 VC1HAL_V400R004_StartDec( VC1_DEC_PARAM_S *pVc1DecParam, SINT32 VdhId )
{
    VDMHAL_HWMEM_S *pHwMem = &g_HwMem[VdhId];
    SINT32 *p32;
    SINT32 *pMsgBase;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    /*  检查参数是否超出规格 */
    VDMHAL_ASSERT_RET(NULL != pVc1DecParam, "point of picture para null\n");
    VDMHAL_ASSERT_RET( pVc1DecParam->mbwidth <= MAX_IMG_WIDTH_IN_MB, "picture width out of range");
    VDMHAL_ASSERT_RET( pVc1DecParam->mbheight <= MAX_IMG_HEIGHT_IN_MB, "picture height out of range");

    pMsgBase = (SINT32 *)MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);
    VDMHAL_ASSERT_RET( NULL != pMsgBase, "can not map down msg virtual address!" );

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

    VC1HAL_V400R004_CfgSliceMsg(pVc1DecParam, pHwMem);
    VC1HAL_V400R004_CfgReg(pVc1DecParam, pHwMem, VdhId);
    VC1HAL_V400R004_CfgDnMsg(pVc1DecParam, pHwMem);

    return VDMHAL_OK;
}

void VC1HAL_V400R004_CfgSliceMsg(VC1_DEC_PARAM_S *pVc1DecParam, VDMHAL_HWMEM_S *pHwMem)
{
    UINT32 bit_offset_0;
    UINT32 bit_len_0;
    UADDR bit_steam_addr_0;

    UINT32 bit_offset_1;
    UINT32 bit_len_1;
    UADDR bit_steam_addr_1;
    UADDR next_slice_para_addr;
    UINT32 slice_end_mbn = 0;
    UINT32 slice_start_mbn = 0;
    UINT32 pre_end = 0;
    UINT32 _tmp = 0;
    UINT32 D32 = 0;
    SINT32 i, j, k, pre = 0;
    UADDR SlcDnMsgPhyAddr;
    SINT32 *pMsgBase;
    VC1_SLCSTREAM_S *SliceInfo = pVc1DecParam->SlcStr;
    SlcDnMsgPhyAddr  = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1];
    pMsgBase = (SINT32 *)(MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1]));

    if (NULL == pMsgBase)
    {
	    dprint(PRN_FATAL, "%s: pMsgBase = NULL\n",__func__);
        return ;
    }

    if (pVc1DecParam->profile == 2) //adv
    {
        //?è±è??pStream2!!!!
        pVc1DecParam->stream_base_addr = pVc1DecParam->SlcStr[0].Phy_addr;

        for (i = 0; i < pVc1DecParam->SlcNum; i++)
        {
            if ( (NULL != pVc1DecParam->SlcStr[i].pStream2) && (pVc1DecParam->SlcStr[i].Phy_addr2 < pVc1DecParam->stream_base_addr))
            {
                pVc1DecParam->stream_base_addr = pVc1DecParam->SlcStr[i].Phy_addr2;
            }
            else if (pVc1DecParam->SlcStr[i].Phy_addr < pVc1DecParam->stream_base_addr)
            {
                pVc1DecParam->stream_base_addr = pVc1DecParam->SlcStr[i].Phy_addr;
            }
        }

        pVc1DecParam->stream_base_addr = pVc1DecParam->stream_base_addr & 0xfffffff0;
        dprint(PRN_DNMSG, "pVc1DecParam->SlcNum = %d\n", pVc1DecParam->SlcNum);

        for (i = 0; i < pVc1DecParam->SlcNum; i++)
        {
            bit_steam_addr_0 = pVc1DecParam->SlcStr[i].Phy_addr - pVc1DecParam->stream_base_addr;
            _tmp  =  bit_steam_addr_0 & 0xF;
            bit_steam_addr_0 = bit_steam_addr_0 & (~0xF);
            bit_offset_0     = pVc1DecParam->SlcStr[i].BitOffset + (_tmp * 8);
            bit_len_0        = pVc1DecParam->SlcStr[i].Len;

            if (pVc1DecParam->SlcStr[i].pStream2 != NULL)
            {
                bit_steam_addr_1 = pVc1DecParam->SlcStr[i].Phy_addr2 - pVc1DecParam->stream_base_addr;
                _tmp  =  bit_steam_addr_1 & 0xF;
                bit_offset_1 = pVc1DecParam->SlcStr[i].BitOffset2 + (_tmp * 8);
                bit_len_1 = pVc1DecParam->SlcStr[i].Len2;
            }
            else
            {
                bit_steam_addr_1 = 0;
                bit_offset_1 = 0;
                bit_len_1 = 0;
            }

            if (0 == i)
            {
                slice_start_mbn = 0;
                slice_end_mbn = SliceInfo[i].SlcEndMbn;
                pre_end = slice_end_mbn;

                if (1 == pVc1DecParam->SlcNum)
                {
                    next_slice_para_addr = 0;
                }
                else
                {
                    for (k = i + 1; k < pVc1DecParam->SlcNum; k++)
                    {
                        if (SliceInfo[k].SlcEndMbn > SliceInfo[i].SlcEndMbn)
                        {
                            /* break 出来的认为已经找到一个有效的slice */
                            break;
                        }
                    }

                    /* 没有找的时，一定是for循环结束后出来的，此时的k == pVc1DecParam->SlcNum */
                    if (k == pVc1DecParam->SlcNum)
                    {
                        next_slice_para_addr = 0;
                    }
                    else
                    {
                        next_slice_para_addr = SlcDnMsgPhyAddr + (k) * 4 * 64;
                    }

                    pre = k;
                }
            }
            else
            {
                slice_end_mbn = SliceInfo[pre].SlcEndMbn;

                for (j = pre + 1; j < pVc1DecParam->SlcNum; j++)
                {
                    if (SliceInfo[j].SlcEndMbn > SliceInfo[pre].SlcEndMbn)
                    {
                        /* break 出来的认为已经找到一个有效的slice */
                        break;
                    }
                }

                /* 没有找的时，一定是for循环结束后出来的，此时的k == pVc1DecParam->SlcNum */
                if (j == pVc1DecParam->SlcNum)
                {
                    next_slice_para_addr = 0;
                }
                else
                {
                    pre = j;
                    next_slice_para_addr = SlcDnMsgPhyAddr + (j) * 4 * 64;
                }

                slice_start_mbn = pre_end + 1;
                pre_end = slice_end_mbn;
            }

            //D0
            D32 = (bit_offset_0 << 25) + bit_len_0;
            WR_MSGWORD( pMsgBase + i * 64, D32);
            dprint(PRN_DNMSG, "D0 = 0x%08x\n", D32);
            //D1
            D32 = bit_steam_addr_0;
            WR_MSGWORD( pMsgBase + i * 64 + 1, D32);
            dprint(PRN_DNMSG, "D1 = 0x%08x\n", D32);
            //D2
            D32 = (bit_offset_1 << 25) + bit_len_1;
            WR_MSGWORD( pMsgBase + i * 64 + 2, D32);
            dprint(PRN_DNMSG, "D2 = 0x%08x\n", D32);
            //D3
            D32 = bit_steam_addr_1;
            WR_MSGWORD( pMsgBase + i * 64 + 3, D32);
            dprint(PRN_DNMSG, "D3 = 0x%08x\n", D32);
            //D4
            D32 = (slice_end_mbn << 16) + slice_start_mbn;
            WR_MSGWORD( pMsgBase + i * 64 + 4, D32);
            dprint(PRN_DNMSG, "D4 = 0x%08x\n", D32);
            //D63
            D32 = next_slice_para_addr;
            WR_MSGWORD( pMsgBase + i * 64 + 63, D32);
            dprint(PRN_DNMSG, "D63 = 0x%08x\n", D32);
            //i = tmp-1;
        }

        //WR_MSGWORD( pMsgBase + pVc1DecParam->SlcNum * 64 - 1, 0);
    }
    else
    {
        pVc1DecParam->stream_base_addr = pVc1DecParam->SlcStr[0].Phy_addr;
        pVc1DecParam->stream_base_addr = pVc1DecParam->stream_base_addr & 0xfffffff0;

        for (i = 0; i < pVc1DecParam->SlcNum; i++)
        {
            bit_steam_addr_0 = pVc1DecParam->SlcStr[i].Phy_addr - pVc1DecParam->stream_base_addr;
            _tmp  =  bit_steam_addr_0 & 0xF;
            bit_steam_addr_0 = bit_steam_addr_0 & (~0xF);
            bit_offset_0     = pVc1DecParam->SlcStr[i].BitOffset + (_tmp * 8);
            bit_len_0        = pVc1DecParam->SlcStr[i].Len;

            if (pVc1DecParam->SlcStr[i].pStream2 != NULL)
            {
                bit_steam_addr_1 = pVc1DecParam->SlcStr[i].Phy_addr2 - pVc1DecParam->stream_base_addr;
                _tmp  =  bit_steam_addr_1 & 0xF;
                bit_offset_1 = pVc1DecParam->SlcStr[i].BitOffset2 + (_tmp * 8);
                bit_len_1 = pVc1DecParam->SlcStr[i].Len2;
            }
            else
            {
                bit_steam_addr_1 = 0;
                bit_offset_1 = 0;
                bit_len_1 = 0;
            }

            if (0 == i)
            {
                slice_start_mbn = 0;
                slice_end_mbn = SliceInfo[i].SlcEndMbn;
                pre_end = slice_end_mbn;

                if (1 == pVc1DecParam->SlcNum)
                {
                    next_slice_para_addr = 0;
                }
                else
                {
                    for (k = i + 1; k < pVc1DecParam->SlcNum; k++)
                    {
                        if (SliceInfo[k].SlcEndMbn > SliceInfo[i].SlcEndMbn)
                        {
                            /* break 出来的认为已经找到一个有效的slice */
                            break;
                        }
                    }

                    /* 没有找的时，一定是for循环结束后出来的，此时的k == pVc1DecParam->SlcNum */
                    if (k == pVc1DecParam->SlcNum)
                    {
                        next_slice_para_addr = 0;
                    }
                    else
                    {
                        next_slice_para_addr = SlcDnMsgPhyAddr + (k) * 4 * 64;
                    }

                    pre = k;
                }
            }
            else
            {
                slice_end_mbn = SliceInfo[pre].SlcEndMbn;

                for (j = pre + 1; j < pVc1DecParam->SlcNum; j++)
                {
                    if (SliceInfo[j].SlcEndMbn > SliceInfo[pre].SlcEndMbn)
                    {
                        break;
                    }
                }

                if (j == pVc1DecParam->SlcNum)
                {
                    next_slice_para_addr = 0;
                }
                else
                {
                    pre = j;
                    next_slice_para_addr = SlcDnMsgPhyAddr + (j) * 4 * 64;
                }

                slice_start_mbn = pre_end + 1;
                pre_end = slice_end_mbn;
            }

            bit_steam_addr_0 = pVc1DecParam->SlcStr[i].Phy_addr - pVc1DecParam->stream_base_addr;
            _tmp  =  bit_steam_addr_0 & 0xF;
            bit_steam_addr_0 = bit_steam_addr_0 & (~0xF);
            bit_offset_0     = pVc1DecParam->SlcStr[i].BitOffset + (_tmp * 8);
            bit_len_0        = pVc1DecParam->SlcStr[i].Len;
            bit_steam_addr_1 = 0;
            bit_offset_1 = 0;
            bit_len_1 = 0;
            D32 = (bit_offset_0 << 25) + bit_len_0;
            WR_MSGWORD( pMsgBase + i * 64, D32);
            D32 = bit_steam_addr_0;
            WR_MSGWORD( pMsgBase + i * 64 + 1, D32);
            WR_MSGWORD( pMsgBase + i * 64 + 2, 0);
            WR_MSGWORD( pMsgBase + i * 64 + 3, 0);
            D32 = (slice_end_mbn << 16) + slice_start_mbn;
            WR_MSGWORD( pMsgBase + i * 64 + 4, D32);
            D32 = next_slice_para_addr;
            WR_MSGWORD( pMsgBase + i * 64 + 63, D32);
            //i = tmp-1;

        }

        // WR_MSGWORD( pMsgBase + pVc1DecParam->SlcNum * 64 - 1, 0);

    }

    return;
}
SINT32 VC1HAL_V400R004_CfgReg( VC1_DEC_PARAM_S *pVc1DecParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId)
{
    UINT32 D32 = 0;
    UINT32 datTmp;
    UINT32 level = 16;
    
    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }
    
    // 清除中断
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );

    D32 = 0;
    D32 = (pVc1DecParam->basic_cfg0 & 0x000FFFFF)  // [19:0] mbamt_to_dec
          | ( 0 << 22 )
          | ( 0 << 23 )
          | ( 1 << 24 )
          | ( 0 << 25 )
          | ( 1 << 30 )     // [30] ld_qmatrix_flag
#ifdef ENV_SOS_KERNEL
          | ( 1 << 31 );    // [31] sec_mode, 1==Secure Mode
#else
          | ( 0 << 31 );    // [31] sec_mode, 0==Normal Mode
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId );
	
    D32 =0;
    ((BASIC_V400R004_CFG1*)(&D32))->video_standard     = 0x1;
    ((BASIC_V400R004_CFG1*)(&D32))->ddr_stride         = pVc1DecParam->ystride_1d>>6;
    ((BASIC_V400R004_CFG1*)(&D32))->uv_order_en        = 0;
    ((BASIC_V400R004_CFG1*)(&D32))->fst_slc_grp        = 1;
    ((BASIC_V400R004_CFG1*)(&D32))->mv_output_en       = 1;
    ((BASIC_V400R004_CFG1*)(&D32))->max_slcgrp_num     = 1;
    ((BASIC_V400R004_CFG1*)(&D32))->line_num_output_en = 0;
    ((BASIC_V400R004_CFG1*)(&D32))->vdh_2d_en          = 1; // y00226912 K3配1 2D output
    ((BASIC_V400R004_CFG1*)(&D32))->compress_en        = pVc1DecParam->Compress_en;
    ((BASIC_V400R004_CFG1*)(&D32))->ppfd_en            = 0;
    pVc1DecParam->basic_cfg1 = D32;
    WR_VREG( VREG_V400R004_BASIC_CFG1, pVc1DecParam->basic_cfg1, VdhId );
    
    WR_VREG( VREG_V400R004_AVM_ADDR,         pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX], VdhId );
    WR_VREG( VREG_V400R004_VAM_ADDR,         pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX], VdhId );
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, pVc1DecParam->stream_base_addr, VdhId );

    //EMAR_ID
    if (pVc1DecParam->mbwidth > 256)
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

    pVc1DecParam->ystride_1d = pVc1DecParam->VahbStride;

	level = 0;

    pVc1DecParam->uvoffset_1d = (pVc1DecParam->VahbStride / 16) * ((pVc1DecParam->DispPicHeight + 31) / 32) * 32
                                + ((pVc1DecParam->DispPicHeight + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_YSTADDR_1D, pVc1DecParam->ystaddr_1d, VdhId );
    WR_VREG( VREG_V400R004_YSTRIDE_1D , pVc1DecParam->ystride_1d, VdhId );
    WR_VREG( VREG_V400R004_UVOFFSET_1D, pVc1DecParam->uvoffset_1d, VdhId );
    WR_VREG( VREG_V400R004_FF_APT_EN, pVc1DecParam->ff_apt_en, VdhId );
    WR_VREG( VREG_V400R004_REF_PIC_TYPE, pVc1DecParam->ref_pic_type, VdhId );

    //PRCNUM_1D_CNT
    D32 = ((pVc1DecParam->DispPicHeight + 31) / 32) * 32 * level;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId );
#if 0
    //PRCMEM1_1D_CNT
    D32 = 0x7F3CFC3C;
    WR_VREG( VREG_V400R004_PRCMEM1_1D_CNT, D32, VdhId );

    //PRCMEM2_1D_CNT
    D32 = 0xFF3FFF12;
    WR_VREG( VREG_V400R004_PRCMEM2_1D_CNT, D32, VdhId );
#endif
    return VDMHAL_OK;
}


SINT32 VC1HAL_V400R004_CfgDnMsg(VC1_DEC_PARAM_S *pVc1DecParam, VDMHAL_HWMEM_S *pHwMem)
{
    UINT32 D32;
    SINT32 *pMsgBase;
    UINT8 *u8Tmp = 0;
    pMsgBase = (SINT32 *)(MEM_Phy2Vir(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]));

    if (NULL == pMsgBase)
    {
	    dprint(PRN_FATAL, "%s: pMsgBase = NULL\n",__func__);
        return VDMHAL_ERR;
    }

    D32 = 0;
    ((VC1DNMSG_V400R004_D0 *)(&D32))->bits.fcm         = pVc1DecParam->fcm;
    ((VC1DNMSG_V400R004_D0 *)(&D32))->bits.profile     = pVc1DecParam->profile;
    ((VC1DNMSG_V400R004_D0 *)(&D32))->bits.ptype       = pVc1DecParam->ptype;
    WR_MSGWORD( pMsgBase, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D1 *)(&D32))->bits.mbheight    = pVc1DecParam->mbheight;
    ((VC1DNMSG_V400R004_D1 *)(&D32))->bits.mbwidth     = pVc1DecParam->mbwidth;
    WR_MSGWORD( pMsgBase + 1, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D2 *)(&D32))->bits.curparity   = pVc1DecParam->curparity;
    ((VC1DNMSG_V400R004_D2 *)(&D32))->bits.loopfilter  = pVc1DecParam->loopfilter;
    ((VC1DNMSG_V400R004_D2 *)(&D32))->bits.numref      = pVc1DecParam->numref;
    ((VC1DNMSG_V400R004_D2 *)(&D32))->bits.issecondfld = pVc1DecParam->issecondfld;
    ((VC1DNMSG_V400R004_D2 *)(&D32))->bits.fwd_fcm     = pVc1DecParam->fwd_fcm;
    ((VC1DNMSG_V400R004_D2 *)(&D32))->bits.bwd_fcm     = pVc1DecParam->bwd_fcm;
    WR_MSGWORD( pMsgBase + 2, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D3 *)(&D32))->bits.condover    = pVc1DecParam->condover;
    ((VC1DNMSG_V400R004_D3 *)(&D32))->bits.fastuvmc    = pVc1DecParam->fastuvmc;
    ((VC1DNMSG_V400R004_D3 *)(&D32))->bits.overlap     = pVc1DecParam->overlap;
    ((VC1DNMSG_V400R004_D3 *)(&D32))->bits.rndctrl     = pVc1DecParam->rndctrl;
    WR_MSGWORD( pMsgBase + 3, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D4 *)(&D32))->bits.altpquant   = pVc1DecParam->altpquant;
    ((VC1DNMSG_V400R004_D4 *)(&D32))->bits.halfqp      = pVc1DecParam->halfqp;
    ((VC1DNMSG_V400R004_D4 *)(&D32))->bits.pqindex     = pVc1DecParam->pqindex;
    ((VC1DNMSG_V400R004_D4 *)(&D32))->bits.pquant      = pVc1DecParam->pquant;
    WR_MSGWORD( pMsgBase + 4, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D5 *)(&D32))->bits.buniform    = pVc1DecParam->buniform;
    ((VC1DNMSG_V400R004_D5 *)(&D32))->bits.dqbilevel   = pVc1DecParam->dqbilevel;
    ((VC1DNMSG_V400R004_D5 *)(&D32))->bits.dqprofile   = pVc1DecParam->dqprofile;
    ((VC1DNMSG_V400R004_D5 *)(&D32))->bits.dquant      = pVc1DecParam->dquant;
    ((VC1DNMSG_V400R004_D5 *)(&D32))->bits.dquantfrm   = pVc1DecParam->dquantfrm;
    ((VC1DNMSG_V400R004_D5 *)(&D32))->bits.quantmode   = pVc1DecParam->quantmode;
    ((VC1DNMSG_V400R004_D5 *)(&D32))->bits.usealtqp    = pVc1DecParam->usealtqp;
    WR_MSGWORD( pMsgBase + 5, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D6 *)(&D32))->bits.mvmode      = pVc1DecParam->mvmode;
    ((VC1DNMSG_V400R004_D6 *)(&D32))->bits.mvmode2     = pVc1DecParam->mvmode2;
    WR_MSGWORD( pMsgBase + 6, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D7 *)(&D32))->bits.reffiled    = pVc1DecParam->reffiled;
    ((VC1DNMSG_V400R004_D7 *)(&D32))->bits.dmvrange    = pVc1DecParam->dmvrange;
    ((VC1DNMSG_V400R004_D7 *)(&D32))->bits.colishalfpel = pVc1DecParam->colishalfpel;
    ((VC1DNMSG_V400R004_D7 *)(&D32))->bits.curishalfpel = pVc1DecParam->curishalfpel;
    ((VC1DNMSG_V400R004_D7 *)(&D32))->bits.mvrange     = pVc1DecParam->mvrange;
    ((VC1DNMSG_V400R004_D7 *)(&D32))->bits.refdist     = pVc1DecParam->refdist;
    WR_MSGWORD( pMsgBase + 7, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D8 *)(&D32))->bits.transdctab  = pVc1DecParam->transdctab;
    ((VC1DNMSG_V400R004_D8 *)(&D32))->bits.vstransform = pVc1DecParam->vstransform;
    ((VC1DNMSG_V400R004_D8 *)(&D32))->bits.ttmbf       = pVc1DecParam->ttmbf;
    ((VC1DNMSG_V400R004_D8 *)(&D32))->bits.transacfrm  = pVc1DecParam->transacfrm;
    ((VC1DNMSG_V400R004_D8 *)(&D32))->bits.transacfrm2 = pVc1DecParam->transacfrm2;
    ((VC1DNMSG_V400R004_D8 *)(&D32))->bits.ttfrm       = pVc1DecParam->ttfrm;
    WR_MSGWORD( pMsgBase + 8, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D9 *)(&D32))->bits.acpredmodeisskipraw    = pVc1DecParam->acpredmodeisskipraw;
    ((VC1DNMSG_V400R004_D9 *)(&D32))->bits.directmbmodeisskipraw  = pVc1DecParam->directmbmodeisskipraw;
    ((VC1DNMSG_V400R004_D9 *)(&D32))->bits.fieldtxmodeisskipraw   = pVc1DecParam->fieldtxmodeisskipraw;
    ((VC1DNMSG_V400R004_D9 *)(&D32))->bits.forwardmbmodeisskipraw = pVc1DecParam->forwardmbmodeisskipraw;
    ((VC1DNMSG_V400R004_D9 *)(&D32))->bits.mvtypembmodeisskipraw  = pVc1DecParam->mvtypembmodeisskipraw;
    ((VC1DNMSG_V400R004_D9 *)(&D32))->bits.overflagsmodeisskipraw = pVc1DecParam->overflagsmodeisskipraw;
    ((VC1DNMSG_V400R004_D9 *)(&D32))->bits.skipmbmodeisskipraw    = pVc1DecParam->skipmbmodeisskipraw;
    WR_MSGWORD( pMsgBase + 9, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D10 *)(&D32))->bits.bfraction  = pVc1DecParam->bfraction;
    ((VC1DNMSG_V400R004_D10 *)(&D32))->bits.cbptab     = pVc1DecParam->cbptab;
    ((VC1DNMSG_V400R004_D10 *)(&D32))->bits.mvtab      = pVc1DecParam->mvtab;
    WR_MSGWORD( pMsgBase + 10, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D11 *)(&D32))->bits.fourmvbptab  = pVc1DecParam->fourmvbptab;
    ((VC1DNMSG_V400R004_D11 *)(&D32))->bits.fourmvswtich = pVc1DecParam->fourmvswtich;
    ((VC1DNMSG_V400R004_D11 *)(&D32))->bits.mbmodetab    = pVc1DecParam->mbmodetab;
    ((VC1DNMSG_V400R004_D11 *)(&D32))->bits.twomvbptab   = pVc1DecParam->twomvbptab;
    WR_MSGWORD( pMsgBase + 11, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D12 *)(&D32))->u32 = pVc1DecParam->ScaleFactor;
    WR_MSGWORD( pMsgBase + 12, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D13 *)(&D32))->u32 = pVc1DecParam->FRFD;
    WR_MSGWORD( pMsgBase + 13, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D14 *)(&D32))->u32 = pVc1DecParam->BRFD;
    WR_MSGWORD( pMsgBase + 14, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D15 *)(&D32))->bits.rangemapyflag   = pVc1DecParam->rangemapyflag;
    ((VC1DNMSG_V400R004_D15 *)(&D32))->bits.rangemapy       = pVc1DecParam->rangemapy;
    ((VC1DNMSG_V400R004_D15 *)(&D32))->bits.rangemapuvflag  = pVc1DecParam->rangemapuvflag;
    ((VC1DNMSG_V400R004_D15 *)(&D32))->bits.rangemapuv      = pVc1DecParam->rangemapuv;
    ((VC1DNMSG_V400R004_D15 *)(&D32))->bits.totalslicenum   = pVc1DecParam->totalslicenum;
    WR_MSGWORD( pMsgBase + 15, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D16 *)(&D32))->u32 = (pVc1DecParam->CurFrmImgLuma2dPhyAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 16, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D17 *)(&D32))->u32 = (pVc1DecParam->FwdRefAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 17, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D18 *)(&D32))->u32 = (pVc1DecParam->BwdRefAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 18, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D19 *)(&D32))->u32 = (pVc1DecParam->CurrColmbAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 19, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D20 *)(&D32))->u32 = (pVc1DecParam->BwdColmbAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 20, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D21 *)(&D32))->u32 = (pHwMem->SedTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 21, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D22 *)(&D32))->u32 = (pHwMem->PmvTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 22, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D23 *)(&D32))->u32 = (pHwMem->ItransTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 23, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D24 *)(&D32))->u32 = (pHwMem->DblkTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 24, D32);

    //D32 = 0;
    //((VC1DNMSG_V400R004_D25*)(&D32))->u32 = (pHwMem->BitplaneInfoAddr + 0xF) & 0xFFFFFFF0;
    //WR_MSGWORD( pMsgBase+25, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D26 *)(&D32))->u32 = (pHwMem->IntensityConvTabAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD( pMsgBase + 26, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D27 *)(&D32))->bits.DispPicWidth  = pVc1DecParam->DispPicWidth;
    ((VC1DNMSG_V400R004_D27 *)(&D32))->bits.DispPicHeight = pVc1DecParam->DispPicHeight;
    WR_MSGWORD( pMsgBase + 27, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D28 *)(&D32))->bits.CodecVersion  = pVc1DecParam->CodecVersion;
    ((VC1DNMSG_V400R004_D28 *)(&D32))->bits.RANGEREDFRM   = pVc1DecParam->RANGEREDFRM;
    ((VC1DNMSG_V400R004_D28 *)(&D32))->bits.RANGEREDFRM0  = pVc1DecParam->RANGEREDFRM0;
    ((VC1DNMSG_V400R004_D28 *)(&D32))->bits.RANGEREDFRM1  = pVc1DecParam->RANGEREDFRM1;
    ((VC1DNMSG_V400R004_D28 *)(&D32))->bits.PostCresent   = pVc1DecParam->PostCresent;
    WR_MSGWORD( pMsgBase + 28, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D29 *)(&D32))->bits.BPD_STRIDE  = pVc1DecParam->BPD_STRIDE;
    WR_MSGWORD( pMsgBase + 29, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D30 *)(&D32))->bits.MVTYPEMB_ADDR  = pVc1DecParam->MVTYPEMB_ADDR;
    WR_MSGWORD( pMsgBase + 30, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D31 *)(&D32))->bits.SKIPMB_ADDR  = pVc1DecParam->SKIPMB_ADDR;
    WR_MSGWORD( pMsgBase + 31, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D32 *)(&D32))->bits.DIRECTMB_ADDR  = pVc1DecParam->DIRECTMB_ADDR;
    WR_MSGWORD( pMsgBase + 32, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D33 *)(&D32))->bits.ACPRED_ADDR  = pVc1DecParam->ACPRED_ADDR;
    WR_MSGWORD( pMsgBase + 33, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D34 *)(&D32))->bits.OVERFLAGS_ADDR  = pVc1DecParam->OVERFLAGS_ADDR;
    WR_MSGWORD( pMsgBase + 34, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D35 *)(&D32))->bits.FIELDTX_ADDR  = pVc1DecParam->FIELDTX_ADDR;
    WR_MSGWORD( pMsgBase + 35, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D36 *)(&D32))->bits.FORWARDMB_ADDR  = pVc1DecParam->FORWARDMB_ADDR;
    WR_MSGWORD( pMsgBase + 36, D32);

    D32 = 0;
    ((VC1DNMSG_V400R004_D63 *)(&D32))->bits.SliceInfoPhyAddr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1];
    WR_MSGWORD( pMsgBase + 63, D32);

    u8Tmp = (UINT8 *)MEM_Phy2Vir(pHwMem->IntensityConvTabAddr);

    if (NULL == u8Tmp)
    {
	    dprint(PRN_FATAL, "%s: u8Tmp = NULL\n",__func__);
        return VDMHAL_ERR;
    }

    memcpy(u8Tmp, pVc1DecParam->pIntensityConvertTab, 3 * 1024);
    //if (1 !=pVc1DecParam->NoBitplaneFlag)
    {
        //memcpy((UINT8 *)MEM_Phy2Vir(pHwMem->BitplaneInfoAddr), pVc1DecParam->vc1bitplane,  pVc1DecParam->BitPlaneNum * 4);
    }
    return VDMHAL_OK;
}

#endif //__VDM_HAL_VC1_C__
