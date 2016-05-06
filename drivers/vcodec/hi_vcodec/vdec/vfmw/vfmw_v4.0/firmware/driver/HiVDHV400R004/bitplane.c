


#include "bitplane.h"
#ifdef HIVDEC_SMMU_SUPPORT
#include "smmu.h"
#endif


SINT32 BPD_CfgReg(VC1_VFMWCODECINF_S *pCodecInfo, BS *pBS, VC1_VFMWSYNTAX_S *pSyntax, VDMHAL_HWMEM_S *pHwMem)
{
    SINT32 *p32;
    SINT32 D32 = 0;
    UINT8 *pCurStreamVirAddr;

    if ( NULL == pHwMem->pBpdRegVirAddr )
    {
        if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir(gBpdRegBaseAddr)) )
        {
            pHwMem->pBpdRegVirAddr = p32;
        }
        else
        {
            dprint(PRN_FATAL, "BPD register virtual address not mapped, reset failed!\n");
            return VDMHAL_ERR;
        }
    }

    // clear int
    WR_BPD_VREG( REG_BPD_INT_STATE, 0xFFFFFFFF);
    /* 0x00b: INT_V200_MASK */
#ifdef VDM_BUSY_WAITTING
    // mask int
    WR_BPD_VREG( REG_BPD_INT_STATE, 0xFFFFFFFF );
#else
    // enable int
    WR_BPD_VREG( REG_BPD_INT_STATE, 0xFFFFFFFE);
#endif

    pCurStreamVirAddr = (pBS->pHead + (pBS->BufPos + (pBS->TotalPos + 31) / 32 * 32 - pBS->TotalPos) % 32 / 8 + (pBS->TotalPos) / 8);

    D32 = 0;

    if (pCodecInfo->PreParseInfo.IsAdvProfile)
    {
        if ((VC1_MIXMV == pSyntax->AdvPicSyntax.MVMODE)
            || ((VC1_INTCMP == pSyntax->AdvPicSyntax.MVMODE) && (VC1_MIXMV == pSyntax->AdvPicSyntax.MVMODE2)))
        {
            ((BPD_CFG0 *)(&D32))->mvmode_en = 1;
        }

        if ((1 == pSyntax->AdvEntSyntax.OVERLAP) && (8 >= pSyntax->AdvPicSyntax.PQUANT))
        {
            ((BPD_CFG0 *)(&D32))->overflag_en = 1;
        }

        ((BPD_CFG0 *)(&D32))->pic_coding_type = (SINT32)((VC1_VFMW_BIPIC == pSyntax->AdvPicSyntax.PTYPE) ? (pSyntax->AdvPicSyntax.PTYPE - 1) : pSyntax->AdvPicSyntax.PTYPE);
        ((BPD_CFG0 *)(&D32))->pic_structure = pSyntax->AdvPicSyntax.FCM;
        ((BPD_CFG0 *)(&D32))->profile = pSyntax->AdvSeqSyntax.PROFILE;
    }
    else
    {
        if ((VC1_MIXMV == pSyntax->SMPPicSyntax.MVMODE)
            || ((VC1_INTCMP == pSyntax->SMPPicSyntax.MVMODE) && (VC1_MIXMV == pSyntax->SMPPicSyntax.MVMODE2)))
        {
            ((BPD_CFG0 *)(&D32))->mvmode_en = 1;
        }

        ((BPD_CFG0 *)(&D32))->pic_coding_type = (SINT32)((VC1_VFMW_BIPIC == pSyntax->SMPPicSyntax.PTYPE) ? (pSyntax->SMPPicSyntax.PTYPE - 1) : pSyntax->SMPPicSyntax.PTYPE);
        ((BPD_CFG0 *)(&D32))->pic_structure = VC1_VFMW_PROGRESSIVE;
        ((BPD_CFG0 *)(&D32))->profile = pSyntax->SMPSeqSyntax.PROFILE;
    }

    if ((pCodecInfo->PreParseInfo.IsAdvProfile) && (VC1_VFMW_FIELDINTER == pSyntax->AdvPicSyntax.FCM))
    {
        ((BPD_CFG0 *)(&D32))->pic_mbheigt_mod3 = ((pCodecInfo->MbHeight + 1) / 2) % 3;
    }
    else
    {
        ((BPD_CFG0 *)(&D32))->pic_mbheigt_mod3 = pCodecInfo->MbHeight % 3;
    }

    ((BPD_CFG0 *)(&D32))->pic_mbwidth_mod3 = pCodecInfo->MbWidth % 3;
    ((BPD_CFG0 *)(&D32))->bit_offset = ((pCurStreamVirAddr - pCodecInfo->stCurPacket.BsVirAddr[0] + pCodecInfo->stCurPacket.BsPhyAddr[0]) & 0xf) * 8 + (pBS->TotalPos & 0x7);
#ifdef ENV_SOS_KERNEL
    ((BPD_CFG0 *)(&D32))->safe_flag = 1;
#else
    ((BPD_CFG0 *)(&D32))->safe_flag = 0;
#endif
    WR_BPD_VREG( REG_BPD_CFG0, D32);
    //dprint(PRN_VDMREG, "REG_BPD_CFG0 %#x\n", D32);
    
	D32 = 0;
    ((BPD_CFG1 *)(&D32))->bs_staddr = (pCurStreamVirAddr - pCodecInfo->stCurPacket.BsVirAddr[0] + pCodecInfo->stCurPacket.BsPhyAddr[0]) & (~0xF);
    WR_BPD_VREG( REG_BPD_CFG1, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG1 %#x\n", D32);

    D32 = 0;
    if ((pCodecInfo->PreParseInfo.IsAdvProfile) && (VC1_VFMW_FIELDINTER == pSyntax->AdvPicSyntax.FCM))
    {
        ((BPD_CFG2 *)(&D32))->pic_mbheight_m1 = (pCodecInfo->MbHeight + 1) / 2 - 1;//field
    }
    else
    {
        ((BPD_CFG2 *)(&D32))->pic_mbheight_m1 = pCodecInfo->MbHeight - 1;//frame
    }
    ((BPD_CFG2 *)(&D32))->pic_mbwidth_m1 = pCodecInfo->MbWidth - 1;
    WR_BPD_VREG( REG_BPD_CFG2, D32);
    //dprint(PRN_VDMREG, "REG_BPD_CFG2 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG3 *)(&D32))->bp_sride = (pCodecInfo->MbWidth + 127) / 128 * 16;
    WR_BPD_VREG( REG_BPD_CFG3, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG3 %#x\n", D32);
    
    D32 = 0;
    ((BPD_CFG4 *)(&D32))->bp0_staddr =  pCodecInfo->MVTYPEMB_ADDR;
    WR_BPD_VREG( REG_BPD_CFG4, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG4 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG5 *)(&D32))->bp1_staddr =  pCodecInfo->SKIPMB_ADDR;
    WR_BPD_VREG( REG_BPD_CFG5, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG5 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG6 *)(&D32))->bp2_staddr =  pCodecInfo->DIRECTMB_ADDR;
    WR_BPD_VREG( REG_BPD_CFG6, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG6 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG7 *)(&D32))->bp3_staddr =  pCodecInfo->ACPRED_ADDR;
    WR_BPD_VREG( REG_BPD_CFG7, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG7 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG8 *)(&D32))->bp4_staddr =  pCodecInfo->OVERFLAGS_ADDR;
    WR_BPD_VREG( REG_BPD_CFG8, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG8 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG9 *)(&D32))->bp5_staddr =  pCodecInfo->FIELDTX_ADDR;
    WR_BPD_VREG( REG_BPD_CFG9, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG9 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG10 *)(&D32))->bp6_staddr =  pCodecInfo->FORWARDMB_ADDR;
    WR_BPD_VREG( REG_BPD_CFG10, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG10 %#x\n", D32);

    D32 = 0;
    ((BPD_CFG11 *)(&D32))->axi_id = 0;
    ((BPD_CFG11 *)(&D32))->axi_rd_outstanding = 3;
    ((BPD_CFG11 *)(&D32))->axi_wr_outstanding = 3;
    ((BPD_CFG11 *)(&D32))->bpd_axi_sep        = 2;
    WR_BPD_VREG( REG_BPD_CFG11, D32 );
    //dprint(PRN_VDMREG, "REG_BPD_CFG11 %#x\n", D32);

    return VDMHAL_OK;
}

VOID BPD_Reset( VOID )
{ 
    UINT32 tmp;
    UINT32 i;
    UINT32 reg_rst_ok;
    UINT32 reg;
    UINT32 *pBpdResetReg = NULL;
    UINT32 *pBpdResetOkReg = NULL;
	
    pBpdResetReg   = (UINT32*)MEM_Phy2Vir(gSOFTRST_REQ_Addr);
    pBpdResetOkReg = (UINT32*)MEM_Phy2Vir(gSOFTRST_OK_ADDR);

    if( NULL == pBpdResetReg || NULL == pBpdResetOkReg)
    {
        dprint(PRN_FATAL, "BPD_Reset: map register fail, vir(pBpdResetReg) = (%p), vir(pBpdResetOkReg) = (%p)\n",
               pBpdResetReg, pBpdResetOkReg);
        return;
    }

    RD_BPD_VREG( REG_BPD_INT_MASK, tmp);

    /* require bpd reset */
    reg= *(volatile UINT32 *)pBpdResetReg;
    *(volatile UINT32 *)pBpdResetReg = reg | (UINT32)(1<<BPD_RESET_CTRL_BIT);

    /*wait for rest ok */
    for(i=0; i<100; i++)
    {
        reg_rst_ok =*(volatile UINT32 *)pBpdResetOkReg;
        if( reg_rst_ok & (1 <<BPD_RESET_OK_BIT))
        {
            break;
        }
        VFMW_OSAL_uDelay(10);
    }
    
    if (i >= 100)
    {
        dprint(PRN_FATAL, "%s reset failed!\n", __func__);
    }
    else
    {
        //dprint(PRN_ALWS,  "%s reset success!\n", __func__);
    }

    /* clear reset require */
    *(volatile UINT32 *)pBpdResetReg = reg & (UINT32)(~(1<<BPD_RESET_CTRL_BIT));

    WR_BPD_VREG( REG_BPD_INT_MASK, tmp );
	
    return;
}

VOID BPD_Start(VOID)
{
#ifdef HIVDEC_SMMU_SUPPORT
#ifdef ENV_SOS_KERNEL
    SMMU_SetMasterReg(BPD, SECURE_ON,  SMMU_OFF);
#else
    SMMU_SetMasterReg(BPD, SECURE_OFF, SMMU_ON);
#endif
#endif

    // Start BPD
    WR_BPD_VREG( REG_BPD_START, 0);
    WR_BPD_VREG( REG_BPD_START, 1);
    WR_BPD_VREG( REG_BPD_START, 0);
    
    return;
}

SINT32 IsBpd_Ready(VOID)
{
    SINT32 Data32 = 0;

    VDMHAL_ASSERT_RET( g_HwMem[0].pBpdRegVirAddr != NULL, "BPD register not mapped yet!" );

    RD_BPD_VREG(REG_BPD_STATE, Data32);

    Data32 = Data32 & 1;
    Data32 = (Data32 == 0) ? 0 : 1;

    return Data32;
}

SINT32 BPDDRV_WaitBpdReadyIfNoIsr( VOID )
{
    UINT32 cnt_wait = 0, max_wait = 10 * WAIT_NO_ISR_MAX;
    UINT32 StartTimeInMs = 0;
    UINT32 CurTimeInMs = 0;

    StartTimeInMs = VFMW_OSAL_GetTimeInMs();

    for ( cnt_wait = 0; cnt_wait < max_wait; )   /* 循环：等待VDM解码完成 */
    {
        if (IsBpd_Ready())
        {
            break;
        }
        else
        {
            CurTimeInMs = VFMW_OSAL_GetTimeInMs();

            if (CurTimeInMs < StartTimeInMs)
            {
                StartTimeInMs = 0;
            }

            cnt_wait = CurTimeInMs - StartTimeInMs;
        }
    }

    if (cnt_wait < max_wait)
    {
        return VFMW_TRUE;
    }
    else
    {
        dprint(PRN_FATAL, "BPD TimeOut!\n");
        return VFMW_FALSE;
    }
}

SINT32 BPD_GetParam(VC1_VFMWCODECINF_S *pCodecInfo, VC1_VFMWSYNTAX_S *pSyntax, BS *pBS)
{
    BPD_OUT0 *pbpd_out0;
    BPD_OUT1 *pbpd_out1;
    UINT32 data0 = 0;
    UINT32 data1 = 0;
    
    RD_BPD_VREG(REG_BPD_OUT0, data0);
    pbpd_out0 = (BPD_OUT0 *)(&data0);
    RD_BPD_VREG(REG_BPD_OUT1, data1);
    pbpd_out1 = (BPD_OUT1 *)(&data1);

    if (pbpd_out0->eaten_lenth >= (pBS->BsLen * 8 - pBS->TotalPos))
    {
        dprint(PRN_FATAL, " BPD ERROR: EAT TOO MUCH BS %#x, but available bs num %#x!!!\n",pbpd_out0->eaten_lenth,(pBS->BsLen - pBS->TotalPos));
        return VFMW_FALSE;
    }

    //注意给其他的赋成零
    if (pCodecInfo->PreParseInfo.IsAdvProfile)
    {
        pSyntax->AdvPicSyntax.MVTYPEMBMode = pbpd_out1->MVTYPEMBMode;
        pSyntax->AdvPicSyntax.ACPREDMode = pbpd_out1->ACPREDMode;
        pSyntax->AdvPicSyntax.OVERFLAGSMode = pbpd_out1->OVERFLAGSMode;
        pSyntax->AdvPicSyntax.FIELDTXMode = pbpd_out1->FIELDTXMode;
        pSyntax->AdvPicSyntax.DIRECTMBMode = pbpd_out1->DIRECTMBMode;
        pSyntax->AdvPicSyntax.FORWARDMBMode = pbpd_out1->FORWARDMBMode;
        pSyntax->AdvPicSyntax.SKIPMBMode = pbpd_out1->SKIPMBMode;
        pSyntax->AdvPicSyntax.CONDOVER = pbpd_out1->CONDOVER;
    }
    else
    {
        pSyntax->SMPPicSyntax.MVTYPEMBMode = pbpd_out1->MVTYPEMBMode;
        pSyntax->SMPPicSyntax.DIRECTMBMode = pbpd_out1->DIRECTMBMode;
        pSyntax->SMPPicSyntax.SKIPMBMode = pbpd_out1->SKIPMBMode;
    }

    BsLongSkip(pBS, pbpd_out0->eaten_lenth);

    return VFMW_TRUE;
}

SINT32 BPD_Drv(BS *pBs, VC1_VFMWCODECINF_S *pCodecInfo, VC1_VFMWSYNTAX_S *pSyntax, SINT32 ChanID)
{
    SINT32 ret;
    SINT32 ret_value = VFMW_FALSE;

    if ((pCodecInfo->MbHeight < 3) || (pCodecInfo->MbWidth < 3) || (pCodecInfo->MbWidth > VC1VFMW_MAX_PIC_WIDTH) || (pCodecInfo->MbHeight > VC1VFMW_MAX_PIC_HEIGHT))
    {
        dprint(PRN_FATAL, "NOT SUPPORT SIZE %d*%d\n", pCodecInfo->MbWidth * 16, pCodecInfo->MbHeight * 16);
        return VFMW_FALSE;
    }
    
    BPD_Reset();
    
    ret = BPD_CfgReg(pCodecInfo, pBs, pSyntax, &g_HwMem[0]);
    if (VDMHAL_OK == ret)
    {
        BPD_Start();
        
        ret = BPDDRV_WaitBpdReadyIfNoIsr();
        if (VFMW_TRUE == ret)
        {
            ret = BPD_GetParam(pCodecInfo, pSyntax, pBs);
            if (VFMW_TRUE == ret)
            {
                ret_value = VFMW_TRUE;
            }
        }
    }
    else
    {
        dprint(PRN_FATAL, "BPD error: no map reg!\n");
    }
        
    return ret_value;
}

