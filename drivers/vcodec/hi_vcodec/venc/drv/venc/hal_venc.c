#include "hal_venc.h"
#include "hi_drv_mem.h"
#include "venc_regulator.h"
#include <linux/hisi/hisi-iommu.h>
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/syscalls.h>
#include <linux/random.h>

extern VeduEfl_IpCtx_S VeduIpCtx;
extern OPTM_VENC_CHN_S g_stVencChn[VENC_MAX_CHN_NUM];

HI_VOID VENC_HAL_ClrAllInt(S_HEVC_AVC_REGS_TYPE *pVeduReg)
{
    pVeduReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.u32 = 0xFFFFFFFF;
}

HI_VOID VENC_HAL_DisableAllInt(S_HEVC_AVC_REGS_TYPE *pVeduReg)
{
    pVeduReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.u32 = 0;
}

HI_VOID VENC_HAL_ResetReg()
{
	Venc_Regulator_Disable();
	Venc_Regulator_Enable();
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     : read back IntStat & rate control register
Return     :
Others     :
******************************************************************************/
HI_VOID VeduHal_ReadReg_Venc( VeduEfl_EncPara_S *pEncPara )
{
    HI_U64 uTime = 0;
	int i        = 0;
    S_HEVC_AVC_REGS_TYPE *pAllReg = (S_HEVC_AVC_REGS_TYPE *)pEncPara->pRegBase;

	pEncPara->VencEndOfPic	= pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_ve_eop_ns;
	pEncPara->VencBufFull	= pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_ve_buffull_ns;

	if (pEncPara->vcpi_protocol == VEDU_H265)
    {
		pEncPara->PicBits = pAllReg->VEDU_CABAC_REGS.CABAC_PIC_STRMSIZE*8;
		pEncPara->I8x8Num = pAllReg->VEDU_SEL_REGS.SEL_OPT_4X4_CNT.bits.opt_4x4_cnt + pAllReg->VEDU_SEL_REGS.SEL_INTRA_OPT_8X8_CNT.bits.intra_opt_8x8_cnt
            + pAllReg->VEDU_SEL_REGS.SEL_INTRA_OPT_16X16_CNT.bits.intra_opt_16x16_cnt + pAllReg->VEDU_SEL_REGS.SEL_INTRA_OPT_32X32_CNT.bits.intra_opt_32x32_cnt;
    }
	else
    {
		pEncPara->PicBits = pAllReg->VEDU_VLC_REGS.VLC_PIC_TOTAL_BITS*8;
        pEncPara->I8x8Num = pAllReg->VEDU_SEL_REGS.SEL_OPT_4X4_CNT.bits.opt_4x4_cnt + pAllReg->VEDU_SEL_REGS.SEL_INTRA_OPT_8X8_CNT.bits.intra_opt_8x8_cnt
            + pAllReg->VEDU_SEL_REGS.SEL_INTRA_PCM_OPT_8X8_CNT.bits.pcm_opt_8x8_cnt + pAllReg->VEDU_SEL_REGS.SEL_INTRA_OPT_16X16_CNT.bits.intra_opt_16x16_cnt;
    }
	HI_INFO_VENC("RCinfo: pEncPara->PicBits:%d pEncPara->I8x8Num:%d\n",pEncPara->PicBits,pEncPara->I8x8Num);

	pEncPara->VEDU_SLICE_LENGTH[0] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR00.bits.slc_len0 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR01.bits.invalidnum0;
	pEncPara->VEDU_SLICE_LENGTH[1] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR10.bits.slc_len1 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR11.bits.invalidnum1;
	pEncPara->VEDU_SLICE_LENGTH[2] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR20.bits.slc_len2 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR21.bits.invalidnum2;
	pEncPara->VEDU_SLICE_LENGTH[3] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR30.bits.slc_len3 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR31.bits.invalidnum3;
	pEncPara->VEDU_SLICE_LENGTH[4] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR40.bits.slc_len4 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR41.bits.invalidnum4;
	pEncPara->VEDU_SLICE_LENGTH[5] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR50.bits.slc_len5 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR51.bits.invalidnum5;
	pEncPara->VEDU_SLICE_LENGTH[6] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR60.bits.slc_len6 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR61.bits.invalidnum6;
	pEncPara->VEDU_SLICE_LENGTH[7] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR70.bits.slc_len7 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR71.bits.invalidnum7;
	pEncPara->VEDU_SLICE_LENGTH[8] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR80.bits.slc_len8 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR81.bits.invalidnum8;
	pEncPara->VEDU_SLICE_LENGTH[9] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR90.bits.slc_len9 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR91.bits.invalidnum9;
	pEncPara->VEDU_SLICE_LENGTH[10] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR100.bits.slc_len10 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR101.bits.invalidnum10;
	pEncPara->VEDU_SLICE_LENGTH[11] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR110.bits.slc_len11 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR111.bits.invalidnum11;
	pEncPara->VEDU_SLICE_LENGTH[12] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR120.bits.slc_len12 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR121.bits.invalidnum12;
	pEncPara->VEDU_SLICE_LENGTH[13] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR130.bits.slc_len13 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR131.bits.invalidnum13;
	pEncPara->VEDU_SLICE_LENGTH[14] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR140.bits.slc_len14 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR141.bits.invalidnum14;
	pEncPara->VEDU_SLICE_LENGTH[15] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR150.bits.slc_len15 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR151.bits.invalidnum15;

/*
	for(i=0;i<16;i++)
	{
		HI_DBG_VENC("pEncPara->VEDU_SLICE_LENGTH[%d]:%d\n",i,pEncPara->VEDU_SLICE_LENGTH[i]);
	}
*/
	pEncPara->VEDU_SLICE_IS_END[0] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR01.bits.islastslc0;
	pEncPara->VEDU_SLICE_IS_END[1] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR11.bits.islastslc1;
	pEncPara->VEDU_SLICE_IS_END[2] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR21.bits.islastslc2;
	pEncPara->VEDU_SLICE_IS_END[3] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR31.bits.islastslc3;
	pEncPara->VEDU_SLICE_IS_END[4] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR41.bits.islastslc4;
	pEncPara->VEDU_SLICE_IS_END[5] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR51.bits.islastslc5;
	pEncPara->VEDU_SLICE_IS_END[6] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR61.bits.islastslc6;
	pEncPara->VEDU_SLICE_IS_END[7] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR71.bits.islastslc7;
	pEncPara->VEDU_SLICE_IS_END[8] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR81.bits.islastslc8;
	pEncPara->VEDU_SLICE_IS_END[9] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR91.bits.islastslc9;
	pEncPara->VEDU_SLICE_IS_END[10] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR101.bits.islastslc10;
	pEncPara->VEDU_SLICE_IS_END[11] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR111.bits.islastslc11;
	pEncPara->VEDU_SLICE_IS_END[12] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR121.bits.islastslc12;
	pEncPara->VEDU_SLICE_IS_END[13] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR131.bits.islastslc13;
	pEncPara->VEDU_SLICE_IS_END[14] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR141.bits.islastslc14;
	pEncPara->VEDU_SLICE_IS_END[15] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR151.bits.islastslc15;

	for(i=0;i<16;i++)
	{
		pEncPara->stStream_OMX[i].data_len = pEncPara->VEDU_SLICE_LENGTH[i];
		if (pEncPara->VEDU_SLICE_IS_END[i] == 1)
		{
			break;
		}
		HI_DBG_VENC("%s, pEncPara->VEDU_SLICE_IS_END[%d]:%d\n", __func__, i, pEncPara->VEDU_SLICE_IS_END[i]);
	}

	HI_DBG_VENC("%s, pEncPara->iSliceSplitNum:%d i:%d\n", __func__, pEncPara->iSliceSplitNum, i);
	if (i+1 != pEncPara->iSliceSplitNum)
	{
		HI_WARN_VENC("%s, slice split is not correct!!!\n", __func__);
	}

#ifdef SAO_LOWPOWER_EN
    if(pEncPara->abSaoLumaFlag || pEncPara->abSaoChromaFlag)
    {
        pEncPara->sao2vcpi_lcu_cnt             = pAllReg->VEDU_SAO_REGS.SAO_LCU_CNT.bits.sao2vcpi_lcu_cnt;
        pEncPara->sao2vcpi_saooff_num_chroma   = pAllReg->VEDU_SAO_REGS.SAO_OFF_NUM.bits.sao2vcpi_saooff_num_chroma;
        pEncPara->sao2vcpi_saooff_num_luma     = pAllReg->VEDU_SAO_REGS.SAO_OFF_NUM.bits.sao2vcpi_saooff_num_luma;
    }
#endif
    uTime = pAllReg->VEDU_VCPI_REGS.VEDU_TIMER;
    pEncPara->stStat.Total_VEDU_TIMER += uTime;
    pEncPara->stStat.Avg_VEDU_TIMER = pEncPara->stStat.Total_VEDU_TIMER/pEncPara->stStat.TotalFrame;
    uTime = pAllReg->VEDU_VCPI_REGS.VEDU_IDLE_TIMER;
    pEncPara->stStat.Total_VEDU_IDLE_TIMER += uTime;
    pEncPara->stStat.Avg_VEDU_IDLE_TIMER = pEncPara->stStat.Total_VEDU_IDLE_TIMER/pEncPara->stStat.TotalFrame;
}

HI_VOID VeduHal_ReadReg_VencSimple( VeduEfl_EncPara_S *pEncPara )
{
	int i = 0;
    S_HEVC_AVC_REGS_TYPE *pAllReg = (S_HEVC_AVC_REGS_TYPE *)pEncPara->pRegBase;

	pEncPara->VencEndOfPic	= pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_ve_eop_ns;
	pEncPara->VencBufFull	= pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_ve_buffull_ns;

	pEncPara->VEDU_SLICE_LENGTH[0] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR00.bits.slc_len0 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR01.bits.invalidnum0;
	pEncPara->VEDU_SLICE_LENGTH[1] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR10.bits.slc_len1 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR11.bits.invalidnum1;
	pEncPara->VEDU_SLICE_LENGTH[2] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR20.bits.slc_len2 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR21.bits.invalidnum2;
	pEncPara->VEDU_SLICE_LENGTH[3] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR30.bits.slc_len3 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR31.bits.invalidnum3;
	pEncPara->VEDU_SLICE_LENGTH[4] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR40.bits.slc_len4 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR41.bits.invalidnum4;
	pEncPara->VEDU_SLICE_LENGTH[5] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR50.bits.slc_len5 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR51.bits.invalidnum5;
	pEncPara->VEDU_SLICE_LENGTH[6] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR60.bits.slc_len6 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR61.bits.invalidnum6;
	pEncPara->VEDU_SLICE_LENGTH[7] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR70.bits.slc_len7 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR71.bits.invalidnum7;
	pEncPara->VEDU_SLICE_LENGTH[8] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR80.bits.slc_len8 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR81.bits.invalidnum8;
	pEncPara->VEDU_SLICE_LENGTH[9] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR90.bits.slc_len9 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR91.bits.invalidnum9;
	pEncPara->VEDU_SLICE_LENGTH[10] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR100.bits.slc_len10 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR101.bits.invalidnum10;
	pEncPara->VEDU_SLICE_LENGTH[11] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR110.bits.slc_len11 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR111.bits.invalidnum11;
	pEncPara->VEDU_SLICE_LENGTH[12] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR120.bits.slc_len12 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR121.bits.invalidnum12;
	pEncPara->VEDU_SLICE_LENGTH[13] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR130.bits.slc_len13 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR131.bits.invalidnum13;
	pEncPara->VEDU_SLICE_LENGTH[14] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR140.bits.slc_len14 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR141.bits.invalidnum14;
	pEncPara->VEDU_SLICE_LENGTH[15] = pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR150.bits.slc_len15 - pAllReg->VEDU_VLCST_REGS.VLCST_DSRPTR151.bits.invalidnum15;

	for(i=0;i<16;i++)
	{
		pEncPara->stStream_OMX[i].data_len = pEncPara->VEDU_SLICE_LENGTH[i];
		if (pEncPara->VEDU_SLICE_IS_END[i] == 1)
		{
			break;
		}
		HI_DBG_VENC("%s, pEncPara->VEDU_SLICE_IS_END[%d]:%d\n",__func__, i, pEncPara->VEDU_SLICE_IS_END[i]);
	}
}

HI_VOID VENC_HAL_ReadReg( HI_HANDLE EncHandle )
{
    VeduEfl_EncPara_S *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    VeduHal_ReadReg_Venc(pEncPara);
    /* clear vedu int */
    //VENC_HAL_ClrAllInt(pAllReg);      /*pAllReg->VEDU_INTCLR.u32 = 0xFFFFFFFF;*/
}

HI_VOID VENC_HAL_ReadRegSimple( HI_HANDLE EncHandle )
{
    VeduEfl_EncPara_S *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    VeduHal_ReadReg_VencSimple(pEncPara);
    /* clear vedu int */
    //VENC_HAL_ClrAllInt(pAllReg);      /*pAllReg->VEDU_INTCLR.u32 = 0xFFFFFFFF;*/
}

HI_VOID VENC_HAL_CfgAXIReg(HI_HANDLE EncHandle, HI_BOOL bAXI_en)
{
 	HI_U8 *p = NULL;
	HI_U8* q = NULL;
	VeduEfl_EncPara_S *pEncPara = (VeduEfl_EncPara_S *)EncHandle;
	HI_U32* reg_ff00 = (HI_U32*)q;
	HI_U32* reg_ff04 = (HI_U32*)q;
	HI_U32* reg_ff08 = (HI_U32*)q;
	HI_U32* reg_ff0c = (HI_U32*)q;
	HI_U32* reg_ff10 = (HI_U32*)q;
	HI_U32* reg_ff20 = (HI_U32*)q;
	HI_U32 randomvalue;

	//S_HEVC_AVC_REGS_TYPE * pAllReg = (S_HEVC_AVC_REGS_TYPE *)pEncPara->pRegBase;
	HI_INFO_VENC("%s, VENC_HAL_CfgAXIReg!!\n", __func__);

	if (bAXI_en == 1)
    {
        if (pEncPara->stRc.FrmNumSeq % 2)
        {
         	p = (HI_U8 *)(pEncPara->pRegBase);
			q = p + 0xff00;
			reg_ff00 = (HI_U32*)q;
			q = p + 0xff04;
			reg_ff04 = (HI_U32*)q;
			q = p + 0xff08;
			reg_ff08 = (HI_U32*)q;
			q = p + 0xff0c;
			reg_ff0c = (HI_U32*)q;
			q = p + 0xff10;
			reg_ff10 = (HI_U32*)q;
			q = p + 0xff20;
			reg_ff20 = (HI_U32*)q;

			get_random_bytes(&randomvalue,sizeof(int));
            *(reg_ff00) = 0x00000 | ((2000 + randomvalue%500) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
            *(reg_ff04) = 0x00000 | ((2000 + randomvalue%500) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
			*(reg_ff08) = 0x00000 | ((2000 + randomvalue%500) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
			*(reg_ff0c) = 0x00000 | ((2000 + randomvalue%500) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
			*(reg_ff10) = 0x00000 | ((2000 + randomvalue%500) & 0xffff);
            *(reg_ff20) = 0;
              msleep(1);
            *(reg_ff20) = 1;
        }
        else
        {
            p = (HI_U8 *)(pEncPara->pRegBase);
			q = p + 0xff00;
			reg_ff00 = (HI_U32*)q;
			q = p + 0xff04;
			reg_ff04 = (HI_U32*)q;
			q = p + 0xff08;
			reg_ff08 = (HI_U32*)q;
			q = p + 0xff0c;
			reg_ff0c = (HI_U32*)q;
			q = p + 0xff10;
			reg_ff10 = (HI_U32*)q;
			q = p + 0xff20;
			reg_ff20 = (HI_U32*)q;
			get_random_bytes(&randomvalue,sizeof(int));
            *(reg_ff00) = 0x00000 | ((10 + randomvalue%2000) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
			*(reg_ff04) = 0x00000 | ((10 + randomvalue%2000) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
			*(reg_ff08) = 0x00000 | ((10 + randomvalue%2000) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
            *(reg_ff0c) = 0x00000 | ((10 + randomvalue%2000) & 0xffff);
			get_random_bytes(&randomvalue,sizeof(int));
            *(reg_ff10) = 0x00000 | ((10 + randomvalue%2000) & 0xffff);

            *(reg_ff20) = 0;
               msleep(1);
            *(reg_ff20) = 1;
        }
    }
	else
    {
        volatile HI_U8 *p = (HI_U8 *)(((VeduEfl_EncPara_S *)EncHandle)->pRegBase);
        *((volatile HI_U32 *)(p + 0xff00)) = (HI_U32)0x80000000;
        *((volatile HI_U32 *)(p + 0xff20)) = (HI_U32)0x0;
        *((volatile HI_U32 *)(p + 0xff20)) = (HI_U32)0x1;
    }
}


/******************************************************************************
Function   :
Description: config vedu reg & start one frame encode.
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_VOID VENC_HAL_CfgReg( HI_HANDLE EncHandle )
{
	HI_BOOL bResetFlag     = HI_FALSE;
	HI_BOOL bRegularOnFlag = HI_FALSE;
    VeduEfl_EncPara_S  *pEncPara  = (VeduEfl_EncPara_S *)EncHandle;
#ifdef TEST_TIME
	pEncPara->stStat.StartCfgRegTime = HI_GetTS();
#endif

	HI_DBG_VENC("%s, pEncPara->vcpi_protocol:%d pre_enc_protocol:%d\n", __func__, pEncPara->vcpi_protocol,pre_enc_protocol);
#ifdef SHUTDOWN_REGULATOR_EN
	//每帧配置寄存器前venc上电
	if (b_Regular_down_flag == HI_TRUE)
	{
		Venc_Regulator_Enable();
		bRegularOnFlag = HI_TRUE;
		b_Regular_down_flag = HI_FALSE;
		HI_INFO_VENC("%s, hardware power on!!!\n", __func__);
	}
#endif

	if ( (pEncPara->vcpi_protocol != pre_enc_protocol || EncHandle != h_pre_enc_handle)&& (bRegularOnFlag != HI_TRUE) )
	{
		VENC_HAL_ResetReg();
		HI_INFO_VENC("%s, reset reg!!!\n", __func__);
		pre_enc_protocol = pEncPara->vcpi_protocol;
		h_pre_enc_handle = EncHandle;
		bResetFlag = HI_TRUE;
	}

	HI_INFO_VENC("%s, pEncPara->stRc.FrmNumSeq:%d pEncPara->IntraPic:%d pEncPara->InterFrmCnt:%d\n", __func__, pEncPara->stRc.FrmNumSeq,pEncPara->IntraPic,pEncPara->InterFrmCnt);

	 //if (pEncPara->stStat.TotalFrame < 2|| bResetFlag == 1 ||  EncHandle != h_pre_enc_handle)
	 if (pEncPara->IntraPic || pEncPara->InterFrmCnt == 0 || bResetFlag == 1 ||  EncHandle != h_pre_enc_handle || bRegularOnFlag == HI_TRUE)
	 //if (pEncPara->stRc.FrmNumSeq < 2|| bResetFlag == 1 ||  EncHandle != h_pre_enc_handle)
    {
	    VeduHal_CfgReg( EncHandle );
	    HI_ERR_VENC("%s, allcfg reg TotalFrame:%d bResetFlag:%d EncHandle:0x%llx h_pre_enc_handle:0x%llx\n", __func__,
			pEncPara->stStat.TotalFrame,bResetFlag,EncHandle,h_pre_enc_handle);
	    h_pre_enc_handle = EncHandle;
    }
    else
    {
         VeduHal_CfgRegSimple( EncHandle );
    }

#ifdef TEST_TIME
    pEncPara->stStat.EndCfgRegTime = HI_GetTS();
    if(pEncPara->stStat.TotalFrame>5)
    {
        pEncPara->stStat.TotalCfgRegTime += pEncPara->stStat.EndCfgRegTime - pEncPara->stStat.StartCfgRegTime;
        pEncPara->stStat.AvgCfgRegTime = pEncPara->stStat.TotalCfgRegTime/(pEncPara->stStat.TotalFrame-5);//timetmp - pEncPara->stStat.StartVencTime;//
    }
#endif
}

HI_VOID VeduHal_CfgRegSimple( HI_HANDLE EncHandle  )
{
	S_HEVC_AVC_REGS_TYPE *pAllReg = NULL;
	VeduEfl_EncPara_S *pEncPara_channel = (VeduEfl_EncPara_S *)EncHandle;
	VeduEfl_EncPara_S_Cfg *pEncPara = pEncPara_channel->pstCfg_EncPara;
	HI_INFO_VENC("%s, *****VeduHal_CfgRegSimple*******\n", __func__);

#ifdef TEST_TIME
	pEncPara_channel->stStat.StartCfgRegTime2 = HI_GetTS();
#endif

	pAllReg	= (S_HEVC_AVC_REGS_TYPE *)pEncPara_channel->pRegBase;

    if (pEncPara_channel->vcpi_frame_type == 0)
    {
    	pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_idr_pic = 1;
    }
    else if (pEncPara_channel->vcpi_frame_type == 1)
    {
    	pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_idr_pic = 0;
    }

	pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_frame_type = pEncPara_channel->vcpi_frame_type;
	//pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_frame_type =  pEncPara->frame_type;

	pEncPara->vcpi_frm_qp	=	pEncPara_channel->iFrameQp;

	pAllReg->VEDU_VCPI_REGS.VEDU_QPCFG.bits.vcpi_frm_qp           = pEncPara->vcpi_frm_qp               ;
	pAllReg->VEDU_QPG_REGS.QPG_AVERAGE_LCU_BITS.bits.ave_lcu_bits = pEncPara_channel->iAveLcuBits;
	pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_sao_chroma = pEncPara->vcpi_sao_chroma;
	pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_sao_luma = pEncPara->vcpi_sao_luma;


#if 1//manzhiqiang add 6.30
	if (pEncPara_channel->vcpi_frame_type == 0 && pEncPara->vcpi_protocol == VEDU_H265)
	{
		pEncPara->lambda00 = 0x12;
		pEncPara->lambda01 = 0x16;
		pEncPara->lambda02 = 0x1c;
		pEncPara->lambda03 = 0x24;
		pEncPara->lambda04 = 0x2d;
		pEncPara->lambda05 = 0x39;
		pEncPara->lambda06 = 0x48;
		pEncPara->lambda07 = 0x5b;
		pEncPara->lambda08 = 0x73;
		pEncPara->lambda09 = 0x91;
		pEncPara->lambda10 = 0xb7;
		pEncPara->lambda11 = 0xe7;
		pEncPara->lambda12 = 0x123;
		pEncPara->lambda13 = 0x16f;
		pEncPara->lambda14 = 0x1cf;
		pEncPara->lambda15 = 0x247;
		pEncPara->lambda16 = 0x2df;
		pEncPara->lambda17 = 0x39e;
		pEncPara->lambda18 = 0x48f;
		pEncPara->lambda19 = 0x5be;
		pEncPara->lambda20 = 0x73d;
		pEncPara->lambda21 = 0x91e;
		pEncPara->lambda22 = 0xb7d;
		pEncPara->lambda23 = 0xe7a;
		pEncPara->lambda24 = 0x123d;
		pEncPara->lambda25 = 0x16fb;
		pEncPara->lambda26 = 0x1cf4;
		pEncPara->lambda27 = 0x247a;
		pEncPara->lambda28 = 0x2df6;
		pEncPara->lambda29 = 0x39e8;
		pEncPara->lambda30 = 0x48f5;
		pEncPara->lambda31 = 0x5bec;
		pEncPara->lambda32 = 0x73d1;
		pEncPara->lambda33 = 0x91eb;
		pEncPara->lambda34 = 0xb7d9;
		pEncPara->lambda35 = 0xe7a2;
		pEncPara->lambda36 = 0x123d7;
		pEncPara->lambda37 = 0x16fb2;
		pEncPara->lambda38 = 0x1cf44;
		pEncPara->lambda39 = 0x1ffff;
		pEncPara->lambda40 = 0xc1;
		pEncPara->lambda41 = 0xd8;
		pEncPara->lambda42 = 0xf3;
		pEncPara->lambda43 = 0x111;
		pEncPara->lambda44 = 0x132;
		pEncPara->lambda45 = 0x158;
		pEncPara->lambda46 = 0x182;
		pEncPara->lambda47 = 0x1b1;
		pEncPara->lambda48 = 0x1e7;
		pEncPara->lambda49 = 0x222;
		pEncPara->lambda50 = 0x265;
		pEncPara->lambda51 = 0x2b0;
		pEncPara->lambda52 = 0x305;
		pEncPara->lambda53 = 0x363;
		pEncPara->lambda54 = 0x3ce;
		pEncPara->lambda55 = 0x445;
		pEncPara->lambda56 = 0x4cb;
		pEncPara->lambda57 = 0x561;
		pEncPara->lambda58 = 0x60a;
		pEncPara->lambda59 = 0x6c7;
		pEncPara->lambda60 = 0x79c;
		pEncPara->lambda61 = 0x88a;
		pEncPara->lambda62 = 0x996;
		pEncPara->lambda63 = 0xac3;
		pEncPara->lambda64 = 0xc14;
		pEncPara->lambda65 = 0xd8f;
		pEncPara->lambda66 = 0xf38;
		pEncPara->lambda67 = 0x1115;
		pEncPara->lambda68 = 0x132c;
		pEncPara->lambda69 = 0x1586;
		pEncPara->lambda70 = 0x1828;
		pEncPara->lambda71 = 0x1b1e;
		pEncPara->lambda72 = 0x1e70;
		pEncPara->lambda73 = 0x222a;
		pEncPara->lambda74 = 0x2659;
		pEncPara->lambda75 = 0x2b0c;
		pEncPara->lambda76 = 0x3051;
		pEncPara->lambda77 = 0x363c;
		pEncPara->lambda78 = 0x3ce0;
		pEncPara->lambda79 = 0x4455;

	}
	else if (pEncPara_channel->vcpi_frame_type == 1 && pEncPara->vcpi_protocol == VEDU_H265)
	{
		pEncPara->lambda00 = 0x12;
		pEncPara->lambda01 = 0x17;
		pEncPara->lambda02 = 0x1d;
		pEncPara->lambda03 = 0x24;
		pEncPara->lambda04 = 0x2e;
		pEncPara->lambda05 = 0x3a;
		pEncPara->lambda06 = 0x49;
		pEncPara->lambda07 = 0x5d;
		pEncPara->lambda08 = 0x75;
		pEncPara->lambda09 = 0x93;
		pEncPara->lambda10 = 0xba;
		pEncPara->lambda11 = 0xea;
		pEncPara->lambda12 = 0x127;
		pEncPara->lambda13 = 0x174;
		pEncPara->lambda14 = 0x1d5;
		pEncPara->lambda15 = 0x24f;
		pEncPara->lambda16 = 0x2e9;
		pEncPara->lambda17 = 0x3ab;
		pEncPara->lambda18 = 0x49f;
		pEncPara->lambda19 = 0x5d3;
		pEncPara->lambda20 = 0x757;
		pEncPara->lambda21 = 0x93f;
		pEncPara->lambda22 = 0xba6;
		pEncPara->lambda23 = 0xeae;
		pEncPara->lambda24 = 0x127e;
		pEncPara->lambda25 = 0x174d;
		pEncPara->lambda26 = 0x1d5c;
		pEncPara->lambda27 = 0x24fd;
		pEncPara->lambda28 = 0x2e9b;
		pEncPara->lambda29 = 0x3ab8;
		pEncPara->lambda30 = 0x49fb;
		pEncPara->lambda31 = 0x5d36;
		pEncPara->lambda32 = 0x7571;
		pEncPara->lambda33 = 0x93f7;
		pEncPara->lambda34 = 0xba6d;
		pEncPara->lambda35 = 0xeae2;
		pEncPara->lambda36 = 0x127ef;
		pEncPara->lambda37 = 0x174db;
		pEncPara->lambda38 = 0x1d5c4;
		pEncPara->lambda39 = 0x1ffff;
		pEncPara->lambda40 = 0xc2;
		pEncPara->lambda41 = 0xda;
		pEncPara->lambda42 = 0xf5;
		pEncPara->lambda43 = 0x113;
		pEncPara->lambda44 = 0x134;
		pEncPara->lambda45 = 0x15a;
		pEncPara->lambda46 = 0x185;
		pEncPara->lambda47 = 0x1b4;
		pEncPara->lambda48 = 0x1ea;
		pEncPara->lambda49 = 0x226;
		pEncPara->lambda50 = 0x269;
		pEncPara->lambda51 = 0x2b5;
		pEncPara->lambda52 = 0x30a;
		pEncPara->lambda53 = 0x369;
		pEncPara->lambda54 = 0x3d4;
		pEncPara->lambda55 = 0x44c;
		pEncPara->lambda56 = 0x4d3;
		pEncPara->lambda57 = 0x56b;
		pEncPara->lambda58 = 0x615;
		pEncPara->lambda59 = 0x6d3;
		pEncPara->lambda60 = 0x7a9;
		pEncPara->lambda61 = 0x899;
		pEncPara->lambda62 = 0x9a7;
		pEncPara->lambda63 = 0xad6;
		pEncPara->lambda64 = 0xc2a;
		pEncPara->lambda65 = 0xda7;
		pEncPara->lambda66 = 0xf53;
		pEncPara->lambda67 = 0x1133;
		pEncPara->lambda68 = 0x134f;
		pEncPara->lambda69 = 0x15ac;
		pEncPara->lambda70 = 0x1854;
		pEncPara->lambda71 = 0x1b4e;
		pEncPara->lambda72 = 0x1ea6;
		pEncPara->lambda73 = 0x2267;
		pEncPara->lambda74 = 0x269e;
		pEncPara->lambda75 = 0x2b59;
		pEncPara->lambda76 = 0x30a8;
		pEncPara->lambda77 = 0x369d;
		pEncPara->lambda78 = 0x3d4d;
		pEncPara->lambda79 = 0x44cf;

	}
#endif


	//mmu   0x20623400
	pAllReg->VEDU_MMU1_REGS.MST_VEDU_MODE_MMU.bits.vcpi_protocol = pEncPara->vcpi_protocol;
	pAllReg->VEDU_MMU1_REGS.MST_VEDU_MODE_MMU.bits.vcpi_str_fmt = pEncPara_channel->vcpi_str_fmt;
    HI_DBG_VENC("pEncPara_channel->iSliceSplitNum:%d\n",pEncPara_channel->iSliceSplitNum);


    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVST_ADDR_STR = pEncPara_channel->VEDU_NBI_MVST_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVST_ADDR_END = pEncPara_channel->VEDU_NBI_MVST_ADDR + pEncPara_channel->VEDU_NBI_MVST_Length - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVLD_ADDR_STR = pEncPara_channel->VEDU_NBI_MVLD_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVLD_ADDR_END = pEncPara_channel->VEDU_NBI_MVLD_ADDR + pEncPara_channel->VEDU_NBI_MVLD_Length - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMEST_ADDR_STR = pEncPara_channel->VEDU_PMEST_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMEST_ADDR_END = pEncPara_channel->VEDU_PMEST_ADDR + pEncPara_channel->VEDU_PMEST_Length - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMELD_ADDR_STR = pEncPara_channel->VEDU_PMELD_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMELD_ADDR_END = pEncPara_channel->VEDU_PMELD_ADDR + pEncPara_channel->VEDU_PMELD_Length - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YH_ADDR_STR = pEncPara_channel->RcnYHeadAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YH_ADDR_END = pEncPara_channel->RcnYHeadAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYHeadLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CH_ADDR_STR = pEncPara_channel->RcnCHeadAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CH_ADDR_END = pEncPara_channel->RcnCHeadAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnCHeadLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YADDR_STR = pEncPara_channel->RcnYAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YADDR_END = pEncPara_channel->RcnYAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CADDR_STR = pEncPara_channel->RcnCAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CADDR_END = pEncPara_channel->RcnCAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnCLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YH_ADDR_STR = pEncPara_channel->RcnYHeadAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YH_ADDR_END = pEncPara_channel->RcnYHeadAddr[!pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYHeadLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CH_ADDR_STR = pEncPara_channel->RcnCHeadAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CH_ADDR_END = pEncPara_channel->RcnCHeadAddr[!pEncPara_channel->RcnIdx]+ pEncPara_channel->RcnCHeadLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YADDR_STR = pEncPara_channel->RcnYAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YADDR_END = pEncPara_channel->RcnYAddr[!pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CADDR_STR = pEncPara_channel->RcnCAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CADDR_END = pEncPara_channel->RcnCAddr[!pEncPara_channel->RcnIdx] + pEncPara_channel->RcnCLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_YADDR_STR = pEncPara_channel->VEDU_SRC_YADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_YADDR_END = pEncPara_channel->VEDU_SRC_YADDR + pEncPara_channel->VEDU_SRC_YLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_CADDR_STR = pEncPara_channel->VEDU_SRC_CADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_CADDR_END = pEncPara_channel->VEDU_SRC_CADDR + pEncPara_channel->VEDU_SRC_CLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_VADDR_STR = pEncPara_channel->VEDU_SRC_VADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_VADDR_END = pEncPara_channel->VEDU_SRC_VADDR + pEncPara_channel->VEDU_SRC_VLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR0_STR = pEncPara_channel->VEDU_STRM_ADDR[0];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR1_STR = pEncPara_channel->VEDU_STRM_ADDR[1];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR2_STR = pEncPara_channel->VEDU_STRM_ADDR[2];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR3_STR = pEncPara_channel->VEDU_STRM_ADDR[3];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR4_STR = pEncPara_channel->VEDU_STRM_ADDR[4];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR5_STR = pEncPara_channel->VEDU_STRM_ADDR[5];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR6_STR = pEncPara_channel->VEDU_STRM_ADDR[6];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR7_STR = pEncPara_channel->VEDU_STRM_ADDR[7];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR8_STR = pEncPara_channel->VEDU_STRM_ADDR[8];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR9_STR = pEncPara_channel->VEDU_STRM_ADDR[9];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR10_STR = pEncPara_channel->VEDU_STRM_ADDR[10];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR11_STR = pEncPara_channel->VEDU_STRM_ADDR[11];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR12_STR = pEncPara_channel->VEDU_STRM_ADDR[12];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR13_STR = pEncPara_channel->VEDU_STRM_ADDR[13];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR14_STR = pEncPara_channel->VEDU_STRM_ADDR[14];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR15_STR = pEncPara_channel->VEDU_STRM_ADDR[15];


    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR0_END = pEncPara_channel->VEDU_STRM_ADDR[0] + pEncPara_channel->VEDU_STRM_BUFLEN[0] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR1_END = pEncPara_channel->VEDU_STRM_ADDR[1] + pEncPara_channel->VEDU_STRM_BUFLEN[1] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR2_END = pEncPara_channel->VEDU_STRM_ADDR[2] + pEncPara_channel->VEDU_STRM_BUFLEN[2] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR3_END = pEncPara_channel->VEDU_STRM_ADDR[3] + pEncPara_channel->VEDU_STRM_BUFLEN[3] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR4_END = pEncPara_channel->VEDU_STRM_ADDR[4] + pEncPara_channel->VEDU_STRM_BUFLEN[4] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR5_END = pEncPara_channel->VEDU_STRM_ADDR[5] + pEncPara_channel->VEDU_STRM_BUFLEN[5] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR6_END = pEncPara_channel->VEDU_STRM_ADDR[6] + pEncPara_channel->VEDU_STRM_BUFLEN[6] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR7_END = pEncPara_channel->VEDU_STRM_ADDR[7] + pEncPara_channel->VEDU_STRM_BUFLEN[7] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR8_END = pEncPara_channel->VEDU_STRM_ADDR[8] + pEncPara_channel->VEDU_STRM_BUFLEN[8] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR9_END = pEncPara_channel->VEDU_STRM_ADDR[9] + pEncPara_channel->VEDU_STRM_BUFLEN[9] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR10_END = pEncPara_channel->VEDU_STRM_ADDR[10] + pEncPara_channel->VEDU_STRM_BUFLEN[10] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR11_END = pEncPara_channel->VEDU_STRM_ADDR[11] + pEncPara_channel->VEDU_STRM_BUFLEN[11] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR12_END = pEncPara_channel->VEDU_STRM_ADDR[12] + pEncPara_channel->VEDU_STRM_BUFLEN[12] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR13_END = pEncPara_channel->VEDU_STRM_ADDR[13] + pEncPara_channel->VEDU_STRM_BUFLEN[13] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR14_END = pEncPara_channel->VEDU_STRM_ADDR[14] + pEncPara_channel->VEDU_STRM_BUFLEN[14] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR15_END = pEncPara_channel->VEDU_STRM_ADDR[15] + pEncPara_channel->VEDU_STRM_BUFLEN[15] - 1;

    // reg cfg end
    pAllReg->VEDU_VCPI_REGS.VEDU_TUNLCELL_ADDR = pEncPara_channel->TUNLCELL_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_YADDR     = pEncPara_channel->VEDU_SRC_YADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_CADDR     = pEncPara_channel->VEDU_SRC_CADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_VADDR     = pEncPara_channel->VEDU_SRC_VADDR  ;
    pAllReg->VEDU_VCPI_REGS.VEDU_YH_ADDR       = pEncPara_channel->VEDU_YH_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_CH_ADDR       = pEncPara_channel->VEDU_CH_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_package_sel  = pEncPara_channel->vcpi_package_sel;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_str_fmt = pEncPara_channel->vcpi_str_fmt;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_store_mode  = pEncPara_channel->vcpi_store_mode;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_y_stride = pEncPara_channel->curld_y_stride;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_c_stride = pEncPara_channel->curld_c_stride;

    // curld yh Êµ¼ÊÃ»ÓÐÆð×÷ÓÃ
    pAllReg->VEDU_VCPI_REGS.VEDU_HEAD_STRIDE.bits.curld_yh_stride = pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_y_stride*2;
    pAllReg->VEDU_VCPI_REGS.VEDU_HEAD_STRIDE.bits.curld_ch_stride = pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_c_stride*2;

    pAllReg->VEDU_VCPI_REGS.VEDU_REC_YADDR  = pEncPara_channel->RcnYAddr[pEncPara_channel->RcnIdx] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_CADDR   = pEncPara_channel->RcnCAddr[pEncPara_channel->RcnIdx];

    /* Define the union U_VEDU_REC_STRIDE */
    {
        U_VEDU_REC_STRIDE D32;
        D32.u32 = 0;
        D32.bits.recst_ystride = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        D32.bits.recst_cstride = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        pAllReg->VEDU_VCPI_REGS.VEDU_REC_STRIDE.u32 = D32.u32;
    }
    // REC_YH_ADDR
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_YH_ADDR  = pEncPara_channel->RcnYHeadAddr[pEncPara_channel->RcnIdx] ;
    //REC_CH_ADDR
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_CH_ADDR = pEncPara_channel->RcnCHeadAddr[pEncPara_channel->RcnIdx] ;
    //REC_HEAD_STRIDE
    {
        U_VEDU_REC_HEAD_STRIDE D32;
        D32.u32 = 0;
        if (pEncPara->vcpi_protocol == VEDU_H265)
        {
            D32.bits.recst_head_stride   = (pEncPara->vcpi_imgwidth_pix + 63)/64*32;
        }
        else if (pEncPara->vcpi_protocol == VEDU_H264)
        {
            D32.bits.recst_head_stride   = (pEncPara->vcpi_imgwidth_pix + 255)/256*32;
        }
        pAllReg->VEDU_VCPI_REGS.VEDU_REC_HEAD_STRIDE.u32 = D32.u32;
    }

     //VEDU_LUMA_REF_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_YADDR = pEncPara_channel->RcnYAddr[!pEncPara_channel->RcnIdx] ;
     //VEDU_CHROMA_REF_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_CADDR = pEncPara_channel->RcnCAddr[!pEncPara_channel->RcnIdx] ;

     /* Define the union U_VEDU_VSTRIDE */
    {
        U_VEDU_REF_STRIDE D32;
        D32.u32 = 0;
        D32.bits.refld_chroma_vstride   = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        D32.bits.refld_luma_vstride   = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        pAllReg->VEDU_VCPI_REGS.VEDU_REF_STRIDE.u32 = D32.u32;
    }

     //VEDU_REF_YH_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_YH_ADDR  = pEncPara_channel->RcnYHeadAddr[!pEncPara_channel->RcnIdx] ;
     //VEDU_REF_CH_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_CH_ADDR  = pEncPara_channel->RcnCHeadAddr[!pEncPara_channel->RcnIdx] ;
     /* Define the union U_VEDU_REF_HSTRIDE */
    {
        U_VEDU_REF_HSTRIDE D32;
        D32.u32 = 0;
        if (pEncPara->vcpi_protocol == VEDU_H265)
        {
            D32.bits.refld_yh_stride  = (pEncPara->vcpi_imgwidth_pix + 63)/64*32;
            D32.bits.refld_ch_stride  = (pEncPara->vcpi_imgwidth_pix + 63)/64*32;
        }
        else if (pEncPara->vcpi_protocol == VEDU_H264)
        {
            D32.bits.refld_yh_stride  = (pEncPara->vcpi_imgwidth_pix + 255)/256*32;
            D32.bits.refld_ch_stride  = (pEncPara->vcpi_imgwidth_pix + 255)/256*32;
        }
        pAllReg->VEDU_VCPI_REGS.VEDU_REF_HSTRIDE.u32 = D32.u32;
    }

     ///////VEDU_PMELD_ADDR
    pAllReg->VEDU_VCPI_REGS.VEDU_PMELD_ADDR  = pEncPara_channel->VEDU_PMELD_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_PMEST_ADDR  = pEncPara_channel->VEDU_PMEST_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_NBI_MVST_ADDR   = pEncPara_channel->VEDU_NBI_MVST_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_NBI_MVLD_ADDR   = pEncPara_channel->VEDU_NBI_MVLD_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR0  = pEncPara_channel->VEDU_STRM_ADDR[0] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR1  = pEncPara_channel->VEDU_STRM_ADDR[1] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR2  = pEncPara_channel->VEDU_STRM_ADDR[2] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR3  = pEncPara_channel->VEDU_STRM_ADDR[3] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR4  = pEncPara_channel->VEDU_STRM_ADDR[4] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR5  = pEncPara_channel->VEDU_STRM_ADDR[5] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR6  = pEncPara_channel->VEDU_STRM_ADDR[6] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR7  = pEncPara_channel->VEDU_STRM_ADDR[7] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR8  = pEncPara_channel->VEDU_STRM_ADDR[8] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR9  = pEncPara_channel->VEDU_STRM_ADDR[9] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR10  = pEncPara_channel->VEDU_STRM_ADDR[10] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR11  = pEncPara_channel->VEDU_STRM_ADDR[11] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR12  = pEncPara_channel->VEDU_STRM_ADDR[12] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR13  = pEncPara_channel->VEDU_STRM_ADDR[13] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR14  = pEncPara_channel->VEDU_STRM_ADDR[14] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR15  = pEncPara_channel->VEDU_STRM_ADDR[15] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN0  = pEncPara_channel->VEDU_STRM_BUFLEN[0] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN1  = pEncPara_channel->VEDU_STRM_BUFLEN[1] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN2  = pEncPara_channel->VEDU_STRM_BUFLEN[2] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN3  = pEncPara_channel->VEDU_STRM_BUFLEN[3] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN4  = pEncPara_channel->VEDU_STRM_BUFLEN[4] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN5  = pEncPara_channel->VEDU_STRM_BUFLEN[5] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN6  = pEncPara_channel->VEDU_STRM_BUFLEN[6] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN7  = pEncPara_channel->VEDU_STRM_BUFLEN[7] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN8  = pEncPara_channel->VEDU_STRM_BUFLEN[8] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN9  = pEncPara_channel->VEDU_STRM_BUFLEN[9] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN10  = pEncPara_channel->VEDU_STRM_BUFLEN[10] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN11  = pEncPara_channel->VEDU_STRM_BUFLEN[11] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN12  = pEncPara_channel->VEDU_STRM_BUFLEN[12] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN13  = pEncPara_channel->VEDU_STRM_BUFLEN[13] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN14  = pEncPara_channel->VEDU_STRM_BUFLEN[14] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN15  = pEncPara_channel->VEDU_STRM_BUFLEN[15] ;

#ifdef HARDWARE_SPLIT_SPS_PPS_EN
    pAllReg->VEDU_VCPI_REGS.VEDU_CURLD_LOWDLY.bits.vcpi_para_sprat_en        = 1;
    if (pEncPara_channel->bFirstNal2Send)
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_PARA_ADDR = pEncPara_channel->stStreamHeader_OMX.bufferaddr_Phy;
        pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_STR = pEncPara_channel->stStreamHeader_OMX.bufferaddr_Phy ;
        pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_END = pEncPara_channel->stStreamHeader_OMX.bufferaddr_Phy + pEncPara_channel->stStreamHeader_OMX.buffer_size  - 1;
        HI_INFO_VENC("pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_STR:0x%x pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_END:0x%x\n",
        pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_STR,pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_END);
    }
#else
      pAllReg->VEDU_VCPI_REGS.VEDU_CURLD_LOWDLY.bits.vcpi_para_sprat_en        = 0;
#endif



	 /*-----------------------------------------  slice 寄存器额外配置l00214825  ---------------------------------------------*/

    /* Define the union U_CABAC_GLB_CFG */
    {
        U_CABAC_GLB_CFG D32;
        D32.u32 = 0;

        D32.bits.max_num_mergecand = pEncPara->max_num_mergecand ;//

        if(pEncPara_channel->vcpi_frame_type ==1)
        {
            D32.bits.nal_unit_head = 0x0201;// pEncPara->nal_unit_head ;P frame
        }
        else
        {
            D32.bits.nal_unit_head = 0x2601;// pEncPara->nal_unit_head ;
        }
        pAllReg->VEDU_CABAC_REGS.CABAC_GLB_CFG.u32 = D32.u32;
    }

	/* Define the union U_CABAC_SLCHDR_SIZE */
	{
	   U_CABAC_SLCHDR_SIZE D32;
	   D32.u32 = 0;

	   D32.bits.slchdr_size_part1					= pEncPara_channel->slchdr_size_part1 ;  //
	   D32.bits.slchdr_size_part2					= pEncPara_channel->slchdr_size_part2 ;

	   pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_SIZE.u32 = D32.u32;
	}
	/* Define the union U_CABAC_SLCHDR_PART1 */
	{
	   U_CABAC_SLCHDR_PART1 D32;
	   D32.u32 = 0;

	   D32.bits.slchdr_part1				   = pEncPara_channel->slchdr_part1  << (16 - pEncPara_channel->slchdr_size_part1);

	   pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART1.u32 = D32.u32;
	}

    /* Define the union U_CABAC_SLCHDR_PART2_SEG1 */

    if (pEncPara_channel->vcpi_protocol== VEDU_H265)
    {
        if(pEncPara_channel->slchdr_size_part2 < 32)
        {
            pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG1 = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[0] << (32 - pEncPara_channel->slchdr_size_part2) ;
        }
        else
        {
            pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG1  = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[0] ;
        }

        if(pEncPara_channel->slchdr_size_part2 > 32)
        {
            pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG2   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[1] << (32 - (pEncPara_channel->slchdr_size_part2 - 32)) ;
        }
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG3   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[2] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG4   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[3] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG5   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[4] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG6   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[5] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG7   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[6] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG8   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[7] ;
    }
    else
    {
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm0 = pEncPara_channel->SlcHdrStream [0];
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm1 = pEncPara_channel->SlcHdrStream [1];
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm2 = pEncPara_channel->SlcHdrStream [2];
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm3 = pEncPara_channel->SlcHdrStream [3];
        pAllReg->VEDU_VLC_REGS.VLC_ReorderStrm0 = pEncPara_channel->ReorderStream[0];
        pAllReg->VEDU_VLC_REGS.VLC_ReorderStrm1  = pEncPara_channel->ReorderStream[1];
        pAllReg->VEDU_VLC_REGS.VLC_MarkingStrm0  = pEncPara_channel->MarkingStream[0];
        pAllReg->VEDU_VLC_REGS.VLC_MarkingStrm1 = pEncPara_channel->MarkingStream[1];
        pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_parabit = ((pEncPara_channel->SlcHdrBits >>  0) & 0xFF) - 1;
        pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_reorderbit = ((pEncPara_channel->SlcHdrBits >>  8) & 0xFF) - 1;
        pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_markingbit = ((pEncPara_channel->SlcHdrBits >> 16) & 0xFF) - 1;
    }

	pAllReg->VEDU_VLCST_REGS.VLCST_PARAMETER.bits.vlcst_para_set_en = pEncPara_channel->vlcst_para_set_en;
	if (pEncPara_channel->vlcst_para_set_en == 1)
	{
		pAllReg->VEDU_VLCST_REGS.VLCST_PARAMETER.bits.vlcst_para_set_len = pEncPara_channel->vlcst_para_set_len;
        pEncPara_channel->vlcst_para_set_en = 0;
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA0 = pEncPara_channel->VEDU_HEADER[0];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA1 = pEncPara_channel->VEDU_HEADER[1];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA2 = pEncPara_channel->VEDU_HEADER[2];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA3 = pEncPara_channel->VEDU_HEADER[3];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA4 = pEncPara_channel->VEDU_HEADER[4];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA5 = pEncPara_channel->VEDU_HEADER[5];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA6 = pEncPara_channel->VEDU_HEADER[6];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA7 = pEncPara_channel->VEDU_HEADER[7];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA8 = pEncPara_channel->VEDU_HEADER[8];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA9 = pEncPara_channel->VEDU_HEADER[9];
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA0:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA0);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA1:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA1);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA2:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA2);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA3:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA3);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA4:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA4);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA5:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA5);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA6:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA6);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA7:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA7);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA8:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA8);

		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA10 = pEncPara_channel->VEDU_HEADER[10];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA11 = pEncPara_channel->VEDU_HEADER[11];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA12 = pEncPara_channel->VEDU_HEADER[12];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA13 = pEncPara_channel->VEDU_HEADER[13];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA14 = pEncPara_channel->VEDU_HEADER[14];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA15 = pEncPara_channel->VEDU_HEADER[15];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA16 = pEncPara_channel->VEDU_HEADER[16];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA17 = pEncPara_channel->VEDU_HEADER[17];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA18 = pEncPara_channel->VEDU_HEADER[18];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA19 = pEncPara_channel->VEDU_HEADER[19];

		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA20 = pEncPara_channel->VEDU_HEADER[20];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA21 = pEncPara_channel->VEDU_HEADER[21];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA22 = pEncPara_channel->VEDU_HEADER[22];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA23 = pEncPara_channel->VEDU_HEADER[23];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA24 = pEncPara_channel->VEDU_HEADER[24];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA25 = pEncPara_channel->VEDU_HEADER[25];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA26 = pEncPara_channel->VEDU_HEADER[26];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA27 = pEncPara_channel->VEDU_HEADER[27];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA28 = pEncPara_channel->VEDU_HEADER[28];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA29 = pEncPara_channel->VEDU_HEADER[29];

		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA30 = pEncPara_channel->VEDU_HEADER[30];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA31 = pEncPara_channel->VEDU_HEADER[31];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA32 = pEncPara_channel->VEDU_HEADER[32];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA33 = pEncPara_channel->VEDU_HEADER[33];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA34 = pEncPara_channel->VEDU_HEADER[34];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA35 = pEncPara_channel->VEDU_HEADER[35];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA36 = pEncPara_channel->VEDU_HEADER[36];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA37 = pEncPara_channel->VEDU_HEADER[37];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA38 = pEncPara_channel->VEDU_HEADER[38];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA39 = pEncPara_channel->VEDU_HEADER[39];

		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA40 = pEncPara_channel->VEDU_HEADER[40];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA41 = pEncPara_channel->VEDU_HEADER[41];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA42 = pEncPara_channel->VEDU_HEADER[42];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA43 = pEncPara_channel->VEDU_HEADER[43];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA44 = pEncPara_channel->VEDU_HEADER[44];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA45 = pEncPara_channel->VEDU_HEADER[45];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA46 = pEncPara_channel->VEDU_HEADER[46];
		pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA47 = pEncPara_channel->VEDU_HEADER[47];
	}
/*-----------------------------------------  slice 寄存器额外配置l00214825	 end---------------------------------------------*/
#ifdef TEST_TIME

	pEncPara_channel->stStat.EndCfgRegTime2 = HI_GetTS();

	if(pEncPara_channel->stStat.TotalFrame>5)
	{
			pEncPara_channel->stStat.TotalCfgRegTime2 += pEncPara_channel->stStat.EndCfgRegTime2 - pEncPara_channel->stStat.StartCfgRegTime2;
			pEncPara_channel->stStat.AvgCfgRegTime2 = pEncPara_channel->stStat.TotalCfgRegTime2/(pEncPara_channel->stStat.TotalFrame-5);//timetmp - pEncPara->stStat.StartVencTime;//
	}
#endif

}

void VencHal_SaveFile(char *filename, char *buf, uint32_t buf_len)
{
    ssize_t write_len = 0;
    struct file *fd = NULL;
    mm_segment_t old_fs;
    loff_t pos = 0;
    fd = filp_open(filename, O_CREAT|O_RDWR|O_APPEND, 0);
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    write_len = vfs_write(fd, (char __user*)buf, buf_len, &pos);
    pos = 0;
    set_fs(old_fs);
    filp_close(fd, NULL);
}


HI_VOID VeduHal_CfgReg( HI_HANDLE EncHandle  )
{

    VeduEfl_EncPara_S *pEncPara_channel = (VeduEfl_EncPara_S *)EncHandle;
    VeduEfl_EncPara_S_Cfg *pEncPara = pEncPara_channel->pstCfg_EncPara;
    struct iommu_domain_data* domain_data;
    S_HEVC_AVC_REGS_TYPE *pAllReg = NULL;
    HI_U32 phy_pgd_base = 0;
    HI_U32 chanlnum = 0;
    HI_U8 Reg[1024];
    HI_U8* pReg = NULL;
    HI_U8* pLogicReg = NULL;
    int ii = 0;
#ifdef TEST_TIME
    pEncPara_channel->stStat.StartCfgRegTime1 = HI_GetTS();
#endif

    HI_INFO_VENC("enter %s\n", __FUNCTION__);
    pAllReg = (S_HEVC_AVC_REGS_TYPE *)pEncPara_channel->pRegBase;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_cfg_err_ns = pEncPara->enable_cfg_err;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_vedu_timeout_ns = pEncPara->enable_vedu_timeout;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_vedu_step_ns = pEncPara->enable_vedu_step;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_vedu_brkpt_ns = pEncPara->enable_vedu_brkpt;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_vedu_slice_end_ns = pEncPara->enable_vedu_slice_end;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_ve_pbitsover_ns = pEncPara->enable_ve_pbitsover;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_ve_buffull_ns = pEncPara->enable_ve_buffull;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTMASK_NS.bits.enable_ve_eop_ns = pEncPara->enable_ve_eop;
    HI_INFO_VENC("timeout:%d slice_end:%d  buffull:%d\n",pEncPara->enable_vedu_timeout,pEncPara->enable_vedu_slice_end,pEncPara->enable_ve_buffull);
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_cfg_err_ns = pEncPara->clr_cfg_err;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_vedu_timeout_ns = pEncPara->clr_vedu_timeout;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_vedu_step_ns = pEncPara->clr_vedu_step;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_vedu_brkpt_ns = pEncPara->clr_vedu_brkpt;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_vedu_slice_end_ns = pEncPara->clr_vedu_slice_end;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_ve_pbitsover_ns = pEncPara->clr_ve_pbitsover;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_ve_buffull_ns = pEncPara->clr_ve_buffull;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.bits.clr_ve_eop_ns = pEncPara->clr_ve_eop;
    pAllReg->VEDU_VCPI_REGS.VEDU_START.bits.vcpi_vstep = pEncPara->vcpi_vstep;
    pAllReg->VEDU_VCPI_REGS.VEDU_START.bits.vcpi_vstart = 0;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_dbgmod = pEncPara->vcpi_dbgmod;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_bkp_en = pEncPara->vcpi_bkp_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_time_en = pEncPara->vcpi_time_en;

    if (pEncPara->vcpi_protocol == VEDU_H265)
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_lcu_size = 2;
    }
    else if (pEncPara->vcpi_protocol == VEDU_H264)
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_lcu_size = 0;
    }
    else
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_lcu_size = 3;
    }

    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_tiles_en = pEncPara->vcpi_tiles_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_ref_cmp_en = pEncPara->vcpi_ref_cmp_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_trans_mode = pEncPara->vcpi_trans_mode;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_pskp_en = pEncPara->vcpi_pskp_en;

    if (pEncPara_channel->vcpi_frame_type == 0)
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_idr_pic = 1;
    }
    else if (pEncPara_channel->vcpi_frame_type == 1)
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_idr_pic = 0;
    }


    if (pEncPara_channel->vcpi_frame_type == 0 && pEncPara->vcpi_protocol == VEDU_H265)
    {
        pEncPara->lambda00 = 0x12;
        pEncPara->lambda01 = 0x16;
        pEncPara->lambda02 = 0x1c;
        pEncPara->lambda03 = 0x24;
        pEncPara->lambda04 = 0x2d;
        pEncPara->lambda05 = 0x39;
        pEncPara->lambda06 = 0x48;
        pEncPara->lambda07 = 0x5b;
        pEncPara->lambda08 = 0x73;
        pEncPara->lambda09 = 0x91;
        pEncPara->lambda10 = 0xb7;
        pEncPara->lambda11 = 0xe7;
        pEncPara->lambda12 = 0x123;
        pEncPara->lambda13 = 0x16f;
        pEncPara->lambda14 = 0x1cf;
        pEncPara->lambda15 = 0x247;
        pEncPara->lambda16 = 0x2df;
        pEncPara->lambda17 = 0x39e;
        pEncPara->lambda18 = 0x48f;
        pEncPara->lambda19 = 0x5be;
        pEncPara->lambda20 = 0x73d;
        pEncPara->lambda21 = 0x91e;
        pEncPara->lambda22 = 0xb7d;
        pEncPara->lambda23 = 0xe7a;
        pEncPara->lambda24 = 0x123d;
        pEncPara->lambda25 = 0x16fb;
        pEncPara->lambda26 = 0x1cf4;
        pEncPara->lambda27 = 0x247a;
        pEncPara->lambda28 = 0x2df6;
        pEncPara->lambda29 = 0x39e8;
        pEncPara->lambda30 = 0x48f5;
        pEncPara->lambda31 = 0x5bec;
        pEncPara->lambda32 = 0x73d1;
        pEncPara->lambda33 = 0x91eb;
        pEncPara->lambda34 = 0xb7d9;
        pEncPara->lambda35 = 0xe7a2;
        pEncPara->lambda36 = 0x123d7;
        pEncPara->lambda37 = 0x16fb2;
        pEncPara->lambda38 = 0x1cf44;
        pEncPara->lambda39 = 0x1ffff;
        pEncPara->lambda40 = 0xc1;
        pEncPara->lambda41 = 0xd8;
        pEncPara->lambda42 = 0xf3;
        pEncPara->lambda43 = 0x111;
        pEncPara->lambda44 = 0x132;
        pEncPara->lambda45 = 0x158;
        pEncPara->lambda46 = 0x182;
        pEncPara->lambda47 = 0x1b1;
        pEncPara->lambda48 = 0x1e7;
        pEncPara->lambda49 = 0x222;
        pEncPara->lambda50 = 0x265;
        pEncPara->lambda51 = 0x2b0;
        pEncPara->lambda52 = 0x305;
        pEncPara->lambda53 = 0x363;
        pEncPara->lambda54 = 0x3ce;
        pEncPara->lambda55 = 0x445;
        pEncPara->lambda56 = 0x4cb;
        pEncPara->lambda57 = 0x561;
        pEncPara->lambda58 = 0x60a;
        pEncPara->lambda59 = 0x6c7;
        pEncPara->lambda60 = 0x79c;
        pEncPara->lambda61 = 0x88a;
        pEncPara->lambda62 = 0x996;
        pEncPara->lambda63 = 0xac3;
        pEncPara->lambda64 = 0xc14;
        pEncPara->lambda65 = 0xd8f;
        pEncPara->lambda66 = 0xf38;
        pEncPara->lambda67 = 0x1115;
        pEncPara->lambda68 = 0x132c;
        pEncPara->lambda69 = 0x1586;
        pEncPara->lambda70 = 0x1828;
        pEncPara->lambda71 = 0x1b1e;
        pEncPara->lambda72 = 0x1e70;
        pEncPara->lambda73 = 0x222a;
        pEncPara->lambda74 = 0x2659;
        pEncPara->lambda75 = 0x2b0c;
        pEncPara->lambda76 = 0x3051;
        pEncPara->lambda77 = 0x363c;
        pEncPara->lambda78 = 0x3ce0;
        pEncPara->lambda79 = 0x4455;
    }
    else if (pEncPara_channel->vcpi_frame_type == 1 && pEncPara->vcpi_protocol == VEDU_H265)
    {
        pEncPara->lambda00 = 0x12;
        pEncPara->lambda01 = 0x17;
        pEncPara->lambda02 = 0x1d;
        pEncPara->lambda03 = 0x24;
        pEncPara->lambda04 = 0x2e;
        pEncPara->lambda05 = 0x3a;
        pEncPara->lambda06 = 0x49;
        pEncPara->lambda07 = 0x5d;
        pEncPara->lambda08 = 0x75;
        pEncPara->lambda09 = 0x93;
        pEncPara->lambda10 = 0xba;
        pEncPara->lambda11 = 0xea;
        pEncPara->lambda12 = 0x127;
        pEncPara->lambda13 = 0x174;
        pEncPara->lambda14 = 0x1d5;
        pEncPara->lambda15 = 0x24f;
        pEncPara->lambda16 = 0x2e9;
        pEncPara->lambda17 = 0x3ab;
        pEncPara->lambda18 = 0x49f;
        pEncPara->lambda19 = 0x5d3;
        pEncPara->lambda20 = 0x757;
        pEncPara->lambda21 = 0x93f;
        pEncPara->lambda22 = 0xba6;
        pEncPara->lambda23 = 0xeae;
        pEncPara->lambda24 = 0x127e;
        pEncPara->lambda25 = 0x174d;
        pEncPara->lambda26 = 0x1d5c;
        pEncPara->lambda27 = 0x24fd;
        pEncPara->lambda28 = 0x2e9b;
        pEncPara->lambda29 = 0x3ab8;
        pEncPara->lambda30 = 0x49fb;
        pEncPara->lambda31 = 0x5d36;
        pEncPara->lambda32 = 0x7571;
        pEncPara->lambda33 = 0x93f7;
        pEncPara->lambda34 = 0xba6d;
        pEncPara->lambda35 = 0xeae2;
        pEncPara->lambda36 = 0x127ef;
        pEncPara->lambda37 = 0x174db;
        pEncPara->lambda38 = 0x1d5c4;
        pEncPara->lambda39 = 0x1ffff;
        pEncPara->lambda40 = 0xc2;
        pEncPara->lambda41 = 0xda;
        pEncPara->lambda42 = 0xf5;
        pEncPara->lambda43 = 0x113;
        pEncPara->lambda44 = 0x134;
        pEncPara->lambda45 = 0x15a;
        pEncPara->lambda46 = 0x185;
        pEncPara->lambda47 = 0x1b4;
        pEncPara->lambda48 = 0x1ea;
        pEncPara->lambda49 = 0x226;
        pEncPara->lambda50 = 0x269;
        pEncPara->lambda51 = 0x2b5;
        pEncPara->lambda52 = 0x30a;
        pEncPara->lambda53 = 0x369;
        pEncPara->lambda54 = 0x3d4;
        pEncPara->lambda55 = 0x44c;
        pEncPara->lambda56 = 0x4d3;
        pEncPara->lambda57 = 0x56b;
        pEncPara->lambda58 = 0x615;
        pEncPara->lambda59 = 0x6d3;
        pEncPara->lambda60 = 0x7a9;
        pEncPara->lambda61 = 0x899;
        pEncPara->lambda62 = 0x9a7;
        pEncPara->lambda63 = 0xad6;
        pEncPara->lambda64 = 0xc2a;
        pEncPara->lambda65 = 0xda7;
        pEncPara->lambda66 = 0xf53;
        pEncPara->lambda67 = 0x1133;
        pEncPara->lambda68 = 0x134f;
        pEncPara->lambda69 = 0x15ac;
        pEncPara->lambda70 = 0x1854;
        pEncPara->lambda71 = 0x1b4e;
        pEncPara->lambda72 = 0x1ea6;
        pEncPara->lambda73 = 0x2267;
        pEncPara->lambda74 = 0x269e;
        pEncPara->lambda75 = 0x2b59;
        pEncPara->lambda76 = 0x30a8;
        pEncPara->lambda77 = 0x369d;
        pEncPara->lambda78 = 0x3d4d;
        pEncPara->lambda79 = 0x44cf;
    }

    HI_INFO_VENC("RCinfo: pEncPara_channel->vcpi_frame_type:%d\n",pEncPara_channel->vcpi_frame_type);
    HI_INFO_VENC("RCinfo: FrameQp:%d  max:%d  min:%d tarBits:%d startQp:%d\n",pEncPara_channel->iFrameQp,pEncPara->max_qp,pEncPara->min_qp, pEncPara_channel->iTargetBits, pEncPara_channel->iStartQP);
    HI_INFO_VENC("RCinfo: pEncPara_channel->iAveLcuBits:%d\n",pEncPara_channel->iAveLcuBits);
    HI_INFO_VENC("RpEncPara->vcpi_sw_height:%d  pEncPara->vcpi_sw_width:%d \n",pEncPara->vcpi_sw_height, pEncPara->vcpi_sw_width);
    HI_INFO_VENC("region_en0-7: %d %d %d %d %d %d %d %d \n",pEncPara->region0en,pEncPara->region1en,pEncPara->region2en,pEncPara->region3en,pEncPara->region4en,pEncPara->region5en,pEncPara->region6en,pEncPara->region7en);
    HI_INFO_VENC("roistartx0-7: %d %d %d %d %d %d %d %d \n",pEncPara->start0_roistartx,pEncPara->start1_roistartx,pEncPara->start2_roistartx,pEncPara->start3_roistartx,pEncPara->start4_roistartx,pEncPara->start5_roistartx,pEncPara->start6_roistartx,pEncPara->start7_roistartx);
    HI_INFO_VENC("roistarty0-7: %d %d %d %d %d %d %d %d \n",pEncPara->start0_roistarty,pEncPara->start1_roistarty,pEncPara->start2_roistarty,pEncPara->start3_roistarty,pEncPara->start4_roistarty,pEncPara->start5_roistarty,pEncPara->start6_roistarty,pEncPara->start7_roistarty);
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_frame_type     = pEncPara_channel->vcpi_frame_type;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_entropy_mode   = pEncPara->vcpi_entropy_mode;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_img_improve_en = pEncPara->vcpi_img_improve_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_rec_cmp_en     = pEncPara->vcpi_rec_cmp_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_sao_chroma     = pEncPara->vcpi_sao_chroma;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_sao_luma       = pEncPara->vcpi_sao_luma;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_slice_int_en   = pEncPara->vcpi_slice_int_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_protocol       = pEncPara->vcpi_protocol;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_cfg_mode       = pEncPara->vcpi_cfg_mode;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_lcu_time_sel   = 1;
    pAllReg->VEDU_VCPI_REGS.VEDU_MODE.bits.vcpi_vedsel           = pEncPara->vcpi_vedsel;
    pAllReg->VEDU_VCPI_REGS.VEDU_TILE_SIZE.bits.vcpi_tile_height = pEncPara->vcpi_tile_height;
    pAllReg->VEDU_VCPI_REGS.VEDU_TILE_SIZE.bits.vcpi_tile_width  = pEncPara->vcpi_tile_width;
    pAllReg->VEDU_VCPI_REGS.VEDU_SLICE.bits.vcpi_multislc_en     = pEncPara->vcpi_multislc_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_SLICE.bits.vcpi_slcspilt_mod    = pEncPara->vcpi_slcspilt_mod;
    pAllReg->VEDU_VCPI_REGS.VEDU_SLICE.bits.vcpi_slice_size      = pEncPara->vcpi_slice_size -1;
    pEncPara->vcpi_frm_qp = pEncPara_channel->iFrameQp;
    pAllReg->VEDU_VCPI_REGS.VEDU_QPCFG.bits.vcpi_frm_qp          = pEncPara->vcpi_frm_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_QPCFG.bits.vcpi_cb_qp_offset    = pEncPara->vcpi_cb_qp_offset;
    pAllReg->VEDU_VCPI_REGS.VEDU_QPCFG.bits.vcpi_cr_qp_offset    = pEncPara->vcpi_cr_qp_offset;
    pAllReg->VEDU_VCPI_REGS.VEDU_CNTCLR  = pEncPara->vcpi_cnt_clr;
    pAllReg->VEDU_VCPI_REGS.VEDU_FRAMENO = pEncPara->vcpi_frame_no ;
    pAllReg->VEDU_VCPI_REGS.VEDU_DBLKCFG.bits.vcpi_dblk_filter_flag = pEncPara->vcpi_dblk_filter_flag;
    pAllReg->VEDU_VCPI_REGS.VEDU_DBLKCFG.bits.vcpi_dblk_alpha       = pEncPara->vcpi_dblk_alpha;
    pAllReg->VEDU_VCPI_REGS.VEDU_DBLKCFG.bits.vcpi_dblk_beta        = pEncPara->vcpi_dblk_beta;

    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.vcpi_protocol_clkgate_en = pEncPara->vcpi_protocol_clkgate_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.vcpi_mem_clkgate_en = pEncPara->vcpi_mem_clkgate_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.vcpi_clkgate_en     = pEncPara->vcpi_clkgate_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.fme_gtck_en         = pEncPara->fme_gtck_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.mrg_gtck_en         = pEncPara->mrg_gtck_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.tqitq_gtck_en       = pEncPara->tqitq_gtck_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.vcpi_ime_lowpow     = pEncPara->vcpi_ime_lowpow;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.vcpi_fme_lowpow     = pEncPara->vcpi_fme_lowpow;
    pAllReg->VEDU_VCPI_REGS.VEDU_LOW_POWER.bits.vcpi_intra_lowpow   = pEncPara->vcpi_intra_lowpow;

    pAllReg->VEDU_VCPI_REGS.VEDU_PICSIZE_PIX.bits.vcpi_imgheight_pix  = pEncPara->vcpi_imgheight_pix -1;
    pAllReg->VEDU_VCPI_REGS.VEDU_PICSIZE_PIX.bits.vcpi_imgwidth_pix   = pEncPara->vcpi_imgwidth_pix -1;
    pAllReg->VEDU_VCPI_REGS.VEDU_BP_POS.bits.vcpi_bp_lcu_y            = pEncPara->vcpi_bp_lcu_y -1;
    pAllReg->VEDU_VCPI_REGS.VEDU_BP_POS.bits.vcpi_bp_lcu_x            = pEncPara->vcpi_bp_lcu_x -1;
    pAllReg->VEDU_VCPI_REGS.VEDU_TIMEOUT                    = pEncPara->vedu_timeout;
    pAllReg->VEDU_VCPI_REGS.VEDU_OUTSTD.bits.vcpi_w_outstanding = pEncPara->vcpi_w_outstanding;
    pAllReg->VEDU_VCPI_REGS.VEDU_OUTSTD.bits.vcpi_r_outstanding = pEncPara->vcpi_r_outstanding;

    if (pEncPara->vcpi_protocol == VEDU_H265)
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_SW_SIZE.bits.vcpi_sw_height = pEncPara->vcpi_sw_height -1;
        pAllReg->VEDU_VCPI_REGS.VEDU_SW_SIZE.bits.vcpi_sw_width  = pEncPara->vcpi_sw_width -1;
    }
    else if  (pEncPara->vcpi_protocol == VEDU_H264)
    {
        pAllReg->VEDU_VCPI_REGS.VEDU_SW_SIZE.bits.vcpi_sw_height = pEncPara->vcpi_sw_height  -0;
        pAllReg->VEDU_VCPI_REGS.VEDU_SW_SIZE.bits.vcpi_sw_width  = pEncPara->vcpi_sw_width   -0;
    }

    pAllReg->VEDU_VCPI_REGS.VEDU_MV_LOAD.bits.vcpi_tmv_wr_rd_avail = pEncPara->vcpi_tmv_wr_rd_avail;

    pAllReg->VEDU_VCPI_REGS.VEDU_CROSS_TILE_SLC.bits.vcpi_cross_tile  = pEncPara->vcpi_cross_tile;
    pAllReg->VEDU_VCPI_REGS.VEDU_CROSS_TILE_SLC.bits.vcpi_cross_slice = pEncPara->vcpi_cross_slice;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd_en      = pEncPara->osd_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd7_absqp  = pEncPara->osd7_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd6_absqp  = pEncPara->osd6_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd5_absqp  = pEncPara->osd5_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd4_absqp  = pEncPara->osd4_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd3_absqp  = pEncPara->osd3_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd2_absqp  = pEncPara->osd2_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd1_absqp  = pEncPara->osd1_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd0_absqp  = pEncPara->osd0_absqp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd7_en     = pEncPara->osd7_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd6_en     = pEncPara->osd6_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd5_en     = pEncPara->osd5_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd4_en     = pEncPara->osd4_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd3_en     = pEncPara->osd3_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd2_en     = pEncPara->osd2_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd1_en     = pEncPara->osd1_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_ENABLE.bits.osd0_en     = pEncPara->osd0_en;

    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_0.bits.osd0_y  = pEncPara->osd0_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_0.bits.osd0_x  = pEncPara->osd0_x;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_1.bits.osd1_y  = pEncPara->osd1_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_1.bits.osd1_x  = pEncPara->osd1_x;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_2.bits.osd2_y  = pEncPara->osd2_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_2.bits.osd2_x  = pEncPara->osd2_x;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_3.bits.osd3_y  = pEncPara->osd3_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_3.bits.osd3_x  = pEncPara->osd3_x;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_4.bits.osd4_y  = pEncPara->osd4_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_4.bits.osd4_x  = pEncPara->osd4_x;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_5.bits.osd5_y  = pEncPara->osd5_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_5.bits.osd5_x  = pEncPara->osd5_x;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_6.bits.osd6_y  = pEncPara->osd6_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_6.bits.osd6_x  = pEncPara->osd6_x;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_7.bits.osd7_y  = pEncPara->osd7_y;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_POS_7.bits.osd7_x  = pEncPara->osd7_x;

    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_0.bits.osd0_h = pEncPara->osd0_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_0.bits.osd0_w = pEncPara->osd0_w;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_1.bits.osd1_h = pEncPara->osd1_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_1.bits.osd1_w = pEncPara->osd1_w;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_2.bits.osd2_h = pEncPara->osd2_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_2.bits.osd2_w = pEncPara->osd2_w;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_3.bits.osd3_h = pEncPara->osd3_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_3.bits.osd3_w = pEncPara->osd3_w;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_4.bits.osd4_h = pEncPara->osd4_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_4.bits.osd4_w = pEncPara->osd4_w;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_5.bits.osd5_h = pEncPara->osd5_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_5.bits.osd5_w = pEncPara->osd5_w;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_6.bits.osd6_h = pEncPara->osd6_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_6.bits.osd6_w = pEncPara->osd6_w;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_7.bits.osd7_h = pEncPara->osd7_h;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_SIZE_7.bits.osd7_w = pEncPara->osd7_w;

    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd7_layer_id  = pEncPara->osd7_layer_id;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd6_layer_id  = pEncPara->osd6_layer_id;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd5_layer_id  = pEncPara->osd5_layer_id;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd4_layer_id  = pEncPara->osd4_layer_id;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd3_layer_id  = pEncPara->osd3_layer_id;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd2_layer_id  = pEncPara->osd2_layer_id;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd1_layer_id  = pEncPara->osd1_layer_id;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_LAYERID.bits.osd0_layer_id  = pEncPara->osd0_layer_id;

    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP0.bits.osd3_qp = pEncPara->osd3_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP0.bits.osd2_qp = pEncPara->osd2_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP0.bits.osd1_qp = pEncPara->osd1_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP0.bits.osd0_qp = pEncPara->osd0_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP1.bits.osd7_qp = pEncPara->osd7_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP1.bits.osd6_qp = pEncPara->osd6_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP1.bits.osd5_qp = pEncPara->osd5_qp;
    pAllReg->VEDU_VCPI_REGS.VEDU_OSD_QP1.bits.osd4_qp = pEncPara->osd4_qp;

    pAllReg->VEDU_VCPI_REGS.VEDU_TUNLCELL_ADDR   = pEncPara->curld_tunlcell_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_YADDR       = pEncPara->curld_y_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_CADDR       = pEncPara->curld_c_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_VADDR       = pEncPara->curld_v_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_YH_ADDR         = pEncPara->curld_yh_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_CH_ADDR         = pEncPara->curld_ch_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_y_stride       = pEncPara->curld_y_stride;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_c_stride       = pEncPara->curld_c_stride;
    pAllReg->VEDU_VCPI_REGS.VEDU_HEAD_STRIDE.bits.curld_yh_stride = pEncPara->curld_yh_stride;
    pAllReg->VEDU_VCPI_REGS.VEDU_HEAD_STRIDE.bits.curld_ch_stride = pEncPara->curld_ch_stride;

    pAllReg->VEDU_VCPI_REGS.VEDU_REC_YADDR     = pEncPara->recst_yaddr;
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_CADDR     = pEncPara->recst_caddr;
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_YH_ADDR   = pEncPara->recst_yh_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_CH_ADDR   = pEncPara->recst_ch_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_REF_YADDR     = pEncPara->refld_luma_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_REF_CADDR     = pEncPara->refld_chroma_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_REF_YH_ADDR   = pEncPara->refld_yh_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_REF_CH_ADDR   = pEncPara->refld_ch_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_PMELD_ADDR    = pEncPara->vcpi_pmeld_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_PMEST_ADDR    = pEncPara->vcpi_pmest_addr;
    pAllReg->VEDU_VCPI_REGS.VEDU_NBI_MVST_ADDR = pEncPara->mvst_address;
    pAllReg->VEDU_VCPI_REGS.VEDU_NBI_MVLD_ADDR = pEncPara->mvld_address;

    pAllReg->VEDU_VCPI_REGS.VEDU_CURLD_LOWDLY.bits.curld_lowdly_en      = pEncPara->curld_lowdly_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_CURLD_LOWDLY.bits.curld_read_interval  = pEncPara->curld_read_interval;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_package_sel           = pEncPara->vcpi_package_sel;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_str_fmt               = pEncPara->vcpi_str_fmt;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_blk_type              = pEncPara->vcpi_blk_type;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_store_mode            = pEncPara->vcpi_store_mode;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_scale_en              = pEncPara->vcpi_scale_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_crop_en               = pEncPara->vcpi_crop_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_CROP_START.bits.vcpi_crop_ystart       = pEncPara->vcpi_crop_ystart;
    pAllReg->VEDU_VCPI_REGS.VEDU_CROP_START.bits.vcpi_crop_xstart       = pEncPara->vcpi_crop_xstart;
    pAllReg->VEDU_VCPI_REGS.VEDU_CROP_END.bits.vcpi_crop_yend           = pEncPara->vcpi_crop_yend;
    pAllReg->VEDU_VCPI_REGS.VEDU_CROP_END.bits.vcpi_crop_xend           = pEncPara->vcpi_crop_xend;
    pAllReg->VEDU_VCPI_REGS.VEDU_SCALE_PARA.bits.vcpi_yscale            = pEncPara->vcpi_yscale;
    pAllReg->VEDU_VCPI_REGS.VEDU_SCALE_PARA.bits.vcpi_xscale            = pEncPara->vcpi_xscale;
    pAllReg->VEDU_VCPI_REGS.VEDU_ORI_PICSIZE.bits.vcpi_oriheight_pix    = pEncPara->vcpi_oriheight_pix -1;
    pAllReg->VEDU_VCPI_REGS.VEDU_ORI_PICSIZE.bits.vcpi_oriwidth_pix     = pEncPara->vcpi_oriwidth_pix -1;

    pAllReg->VEDU_VCPI_REGS.VEDU_INTRA_INTER_CU_EN.bits.vcpi_mrg_cu_en  = pEncPara->vcpi_mrg_cu_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTRA_INTER_CU_EN.bits.vcpi_fme_cu_en  = pEncPara->vcpi_fme_cu_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTRA_INTER_CU_EN.bits.vcpi_ipcm_en    = pEncPara->vcpi_ipcm_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_INTRA_INTER_CU_EN.bits.vcpi_intra_cu_en = pEncPara->vcpi_intra_cu_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_VLC_CONFIG.bits.vcpi_byte_stuffing      = pEncPara->vcpi_byte_stuffing;
    pAllReg->VEDU_VCPI_REGS.VEDU_VLC_CONFIG.bits.vcpi_num_refidx         = pEncPara->vcpi_num_refidx;
	pAllReg->VEDU_VCPI_REGS.VEDU_VLC_CONFIG.bits.vcpi_cabac_init_idc     = pEncPara->vcpi_cabac_init_idc;
    pAllReg->VEDU_VCPI_REGS.VEDU_VLC_CONFIG.bits.vcpi_ref_idc            = 3; //pEncPara->vcpi_ref_idc;
    pAllReg->VEDU_VCPI_REGS.VEDU_PRE_JUDGE_EXT_EN.bits.vcpi_ext_edge_en  = pEncPara->vcpi_ext_edge_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_PRE_JUDGE_EXT_EN.bits.vcpi_force_inter  = pEncPara->vcpi_force_inter;
    pAllReg->VEDU_VCPI_REGS.VEDU_PRE_JUDGE_EXT_EN.bits.vcpi_pblk_pre_en  = pEncPara->vcpi_pblk_pre_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_PRE_JUDGE_EXT_EN.bits.vcpi_iblk_pre_en  = pEncPara->vcpi_iblk_pre_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_PRE_JUDGE_COST_THR.bits.vcpi_pblk_pre_cost_thr = pEncPara->vcpi_pblk_pre_cost_thr;
    pAllReg->VEDU_VCPI_REGS.VEDU_PRE_JUDGE_COST_THR.bits.vcpi_iblk_pre_cost_thr = pEncPara->vcpi_iblk_pre_cost_thr;
    pAllReg->VEDU_VCPI_REGS.VEDU_IBLK_PRE_MV_THR.bits.vcpi_iblk_pre_mvy_thr     = pEncPara->vcpi_iblk_pre_mvy_thr;
    pAllReg->VEDU_VCPI_REGS.VEDU_IBLK_PRE_MV_THR.bits.vcpi_iblk_pre_mvx_thr     = pEncPara->vcpi_iblk_pre_mvx_thr;
    pAllReg->VEDU_VCPI_REGS.VEDU_IBLK_PRE_MV_THR.bits.vcpi_iblk_pre_mv_dif_thr1 = pEncPara->vcpi_iblk_pre_mv_dif_thr1;
    pAllReg->VEDU_VCPI_REGS.VEDU_IBLK_PRE_MV_THR.bits.vcpi_iblk_pre_mv_dif_thr0 = pEncPara->vcpi_iblk_pre_mv_dif_thr0;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE0.bits.vcpi_win0_height             = pEncPara->vcpi_win0_height;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE0.bits.vcpi_win0_width              = pEncPara->vcpi_win0_width;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE1.bits.vcpi_win1_height             = pEncPara->vcpi_win1_height;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE1.bits.vcpi_win1_width              = pEncPara->vcpi_win1_width;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE2.bits.vcpi_win2_height             = pEncPara->vcpi_win2_height;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE2.bits.vcpi_win2_width              = pEncPara->vcpi_win2_width;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE3.bits.vcpi_win3_height             = pEncPara->vcpi_win3_height;
    pAllReg->VEDU_VCPI_REGS.VEDU_WINDOW_SIZE3.bits.vcpi_win3_width              = pEncPara->vcpi_win3_width;
    pAllReg->VEDU_VCPI_REGS.VEDU_PIC_STRONG_EN.bits.vcpi_static_en              = pEncPara->vcpi_static_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_PIC_STRONG_EN.bits.vcpi_highedge_en            = pEncPara->vcpi_highedge_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_PIC_STRONG_EN.bits.vcpi_skin_en                = pEncPara->vcpi_skin_en;
    pAllReg->VEDU_VCPI_REGS.VEDU_PBLK_PRE_MV_THR.bits.vcpi_pblk_pre_mvy_thr     = pEncPara->vcpi_pblk_pre_mvy_thr;
    pAllReg->VEDU_VCPI_REGS.VEDU_PBLK_PRE_MV_THR.bits.vcpi_pblk_pre_mvx_thr     = pEncPara->vcpi_pblk_pre_mvx_thr;

    //vctrl 0x20620200
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.vcpi_roi_en     = pEncPara->vcpi_roi_en ;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region7keep     = pEncPara->region7keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region6keep     = pEncPara->region6keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region5keep     = pEncPara->region5keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region4keep     = pEncPara->region4keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region3keep     = pEncPara->region3keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region2keep     = pEncPara->region2keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region1keep     = pEncPara->region1keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region0keep     = pEncPara->region0keep;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp7          = pEncPara->absqp7;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp6          = pEncPara->absqp6;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp5          = pEncPara->absqp5;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp4          = pEncPara->absqp4;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp3          = pEncPara->absqp3;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp2          = pEncPara->absqp2;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp1          = pEncPara->absqp1;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.absqp0          = pEncPara->absqp0;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region7en       = pEncPara->region7en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region6en       = pEncPara->region6en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region5en       = pEncPara->region5en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region4en       = pEncPara->region4en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region3en       = pEncPara->region3en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region2en       = pEncPara->region2en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region1en       = pEncPara->region1en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG0.bits.region0en       = pEncPara->region0en;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG1.bits.roiqp3          = pEncPara->roiqp3;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG1.bits.roiqp2          = pEncPara->roiqp2;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG1.bits.roiqp1          = pEncPara->roiqp1;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG1.bits.roiqp0          = pEncPara->roiqp0;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG2.bits.roiqp7          = pEncPara->roiqp7;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG2.bits.roiqp6          = pEncPara->roiqp6;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG2.bits.roiqp5          = pEncPara->roiqp5;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_CFG2.bits.roiqp4          = pEncPara->roiqp4;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_0.bits.size0_roiheight       = pEncPara->size0_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_0.bits.size0_roiwidth        = pEncPara->size0_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_0.bits.start0_roistarty     = pEncPara->start0_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_0.bits.start0_roistartx     = pEncPara->start0_roistartx;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_1.bits.size1_roiheight       = pEncPara->size1_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_1.bits.size1_roiwidth        = pEncPara->size1_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_1.bits.start1_roistarty     = pEncPara->start1_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_1.bits.start1_roistartx     = pEncPara->start1_roistartx;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_2.bits.size2_roiheight       = pEncPara->size2_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_2.bits.size2_roiwidth        = pEncPara->size2_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_2.bits.start2_roistarty     = pEncPara->start2_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_2.bits.start2_roistartx     = pEncPara->start2_roistartx;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_3.bits.size3_roiheight       = pEncPara->size3_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_3.bits.size3_roiwidth        = pEncPara->size3_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_3.bits.start3_roistarty     = pEncPara->start3_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_3.bits.start3_roistartx     = pEncPara->start3_roistartx;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_4.bits.size4_roiheight       = pEncPara->size4_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_4.bits.size4_roiwidth        = pEncPara->size4_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_4.bits.start4_roistarty     = pEncPara->start4_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_4.bits.start4_roistartx     = pEncPara->start4_roistartx;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_5.bits.size5_roiheight       = pEncPara->size5_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_5.bits.size5_roiwidth        = pEncPara->size5_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_5.bits.start5_roistarty     = pEncPara->start5_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_5.bits.start5_roistartx     = pEncPara->start5_roistartx;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_6.bits.size6_roiheight       = pEncPara->size6_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_6.bits.size6_roiwidth        = pEncPara->size6_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_6.bits.start6_roistarty     = pEncPara->start6_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_6.bits.start6_roistartx     = pEncPara->start6_roistartx;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_7.bits.size7_roiheight       = pEncPara->size7_roiheight;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_SIZE_7.bits.size7_roiwidth        = pEncPara->size7_roiwidth;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_7.bits.start7_roistarty     = pEncPara->start7_roistarty;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_ROI_START_7.bits.start7_roistartx     = pEncPara->start7_roistartx;

    pAllReg->VEDU_VCTRL_REGS.VCTRL_LCU_TARGET_BIT.bits.lcu_target_bit                         = pEncPara->lcu_target_bit;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NARROW_THRESHOLD.bits.narrow_tile_width                    = pEncPara->narrow_tile_width;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_LCU_BASELINE.bits.lcu_performance_baseline                 = pEncPara->lcu_performance_baseline;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORM_TR32X32_COEFF_DENOISE.bits.norm32_tr1_denois_max_num  = pEncPara->norm32_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORM_TR32X32_COEFF_DENOISE.bits.norm32_coeff_protect_num   = pEncPara->norm32_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORM_TR16X16_COEFF_DENOISE.bits.norm16_tr1_denois_max_num  = pEncPara->norm16_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORM_TR16X16_COEFF_DENOISE.bits.norm16_coeff_protect_num   = pEncPara->norm16_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_TR32X32_COEFF_DENOISE.bits.skin32_tr1_denois_max_num  = pEncPara->skin32_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_TR32X32_COEFF_DENOISE.bits.skin32_coeff_protect_num   = pEncPara->skin32_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_TR16X16_COEFF_DENOISE.bits.skin16_tr1_denois_max_num  = pEncPara->skin16_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_TR16X16_COEFF_DENOISE.bits.skin16_coeff_protect_num   = pEncPara->skin16_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_STATIC_TR32X32_COEFF_DENOISE.bits.static32_tr1_denois_max_num = pEncPara->static32_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_STATIC_TR32X32_COEFF_DENOISE.bits.static32_coeff_protect_num  = pEncPara->static32_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_STATIC_TR16X16_COEFF_DENOISE.bits.static16_tr1_denois_max_num = pEncPara->static16_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_STATIC_TR16X16_COEFF_DENOISE.bits.static16_coeff_protect_num = pEncPara->static16_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HEDGE_TR32X32_COEFF_DENOISE.bits.hedge32_tr1_denois_max_num  = pEncPara->hedge32_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HEDGE_TR32X32_COEFF_DENOISE.bits.hedge32_coeff_protect_num   = pEncPara->hedge32_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HEDGE_TR16X16_COEFF_DENOISE.bits.hedge16_tr1_denois_max_num  = pEncPara->hedge16_tr1_denois_max_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HEDGE_TR16X16_COEFF_DENOISE.bits.hedge16_coeff_protect_num   = pEncPara->hedge16_coeff_protect_num;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_INTRA_RDO_FACTOR.bits.norm_intra_cu32_rdcost_offset= pEncPara->norm_intra_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_INTRA_RDO_FACTOR.bits.norm_intra_cu16_rdcost_offset= pEncPara->norm_intra_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_INTRA_RDO_FACTOR.bits.norm_intra_cu8_rdcost_offset = pEncPara->norm_intra_cu8_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_INTRA_RDO_FACTOR.bits.norm_intra_cu4_rdcost_offset = pEncPara->norm_intra_cu4_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_MRG_RDO_FACTOR.bits.norm_mrg_cu64_rdcost_offset    = pEncPara->norm_mrg_cu64_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_MRG_RDO_FACTOR.bits.norm_mrg_cu32_rdcost_offset    = pEncPara->norm_mrg_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_MRG_RDO_FACTOR.bits.norm_mrg_cu16_rdcost_offset    = pEncPara->norm_mrg_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_MRG_RDO_FACTOR.bits.norm_mrg_cu8_rdcost_offset     = pEncPara->norm_mrg_cu8_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_FME_RDO_FACTOR.bits.norm_fme_cu64_rdcost_offset    = pEncPara->norm_fme_cu64_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_FME_RDO_FACTOR.bits.norm_fme_cu32_rdcost_offset    = pEncPara->norm_fme_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_FME_RDO_FACTOR.bits.norm_fme_cu16_rdcost_offset    = pEncPara->norm_fme_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_NORMAL_FME_RDO_FACTOR.bits.norm_fme_cu8_rdcost_offset     = pEncPara->norm_fme_cu8_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_INTRA_RDO_FACTOR.bits.skin_intra_cu32_rdcost_offset = pEncPara->skin_intra_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_INTRA_RDO_FACTOR.bits.skin_intra_cu16_rdcost_offset = pEncPara->skin_intra_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_INTRA_RDO_FACTOR.bits.skin_intra_cu8_rdcost_offset  = pEncPara->skin_intra_cu8_rdcost_offset ;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_INTRA_RDO_FACTOR.bits.skin_intra_cu4_rdcost_offset  = pEncPara->skin_intra_cu4_rdcost_offset ;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_MRG_RDO_FACTOR.bits.skin_mrg_cu64_rdcost_offset = pEncPara->skin_mrg_cu64_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_MRG_RDO_FACTOR.bits.skin_mrg_cu32_rdcost_offset = pEncPara->skin_mrg_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_MRG_RDO_FACTOR.bits.skin_mrg_cu16_rdcost_offset = pEncPara->skin_mrg_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_MRG_RDO_FACTOR.bits.skin_mrg_cu8_rdcost_offset  = pEncPara->skin_mrg_cu8_rdcost_offset  ;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_FME_RDO_FACTOR.bits.skin_fme_cu64_rdcost_offset = pEncPara->skin_fme_cu64_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_FME_RDO_FACTOR.bits.skin_fme_cu32_rdcost_offset = pEncPara->skin_fme_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_FME_RDO_FACTOR.bits.skin_fme_cu16_rdcost_offset = pEncPara->skin_fme_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_SKIN_REGION_FME_RDO_FACTOR.bits.skin_fme_cu8_rdcost_offset  = pEncPara->skin_fme_cu8_rdcost_offset  ;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR.bits.hedge_intra_cu32_rdcost_offset = pEncPara->hedge_intra_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR.bits.hedge_intra_cu16_rdcost_offset = pEncPara->hedge_intra_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR.bits.hedge_intra_cu8_rdcost_offset  = pEncPara->hedge_intra_cu8_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR.bits.hedge_intra_cu4_rdcost_offset  = pEncPara->hedge_intra_cu4_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_MRG_RDO_FACTOR.bits.hedge_mrg_cu64_rdcost_offset = pEncPara->hedge_mrg_cu64_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_MRG_RDO_FACTOR.bits.hedge_mrg_cu32_rdcost_offset = pEncPara->hedge_mrg_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_MRG_RDO_FACTOR.bits.hedge_mrg_cu16_rdcost_offset = pEncPara->hedge_mrg_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_MRG_RDO_FACTOR.bits.hedge_mrg_cu8_rdcost_offset  = pEncPara->hedge_mrg_cu8_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_FME_RDO_FACTOR.bits.hedge_fme_cu64_rdcost_offset = pEncPara->hedge_fme_cu64_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_FME_RDO_FACTOR.bits.hedge_fme_cu32_rdcost_offset = pEncPara->hedge_fme_cu32_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_FME_RDO_FACTOR.bits.hedge_fme_cu16_rdcost_offset = pEncPara->hedge_fme_cu16_rdcost_offset;
    pAllReg->VEDU_VCTRL_REGS.VCTRL_HIGH_EDGE_FME_RDO_FACTOR.bits.hedge_fme_cu8_rdcost_offset  = pEncPara->hedge_fme_cu8_rdcost_offset;
    //Pme  0x20620600
    pAllReg->VEDU_PME_REGS.PME_SW_EN.bits.vcpi_new_cost_en    = pEncPara->vcpi_new_cost_en;
    pAllReg->VEDU_PME_REGS.PME_SW_EN.bits.vcpi_psw_adapt_en   = pEncPara->vcpi_psw_adapt_en;
    pAllReg->VEDU_PME_REGS.PME_SW_TR0.bits.vcpi_psw_thr0      = pEncPara->vcpi_psw_thr0;
    pAllReg->VEDU_PME_REGS.PME_SW_TR1.bits.vcpi_psw_thr1      = pEncPara->vcpi_psw_thr1;
    pAllReg->VEDU_PME_REGS.PME_SW_TR2.bits.vcpi_psw_thr2      = pEncPara->vcpi_psw_thr2;
    pAllReg->VEDU_PME_REGS.PME_TR_WEIGHTX.bits.tr_weightx_2   = pEncPara->tr_weightx_2;
    pAllReg->VEDU_PME_REGS.PME_TR_WEIGHTX.bits.tr_weightx_1   = pEncPara->tr_weightx_1;
    pAllReg->VEDU_PME_REGS.PME_TR_WEIGHTX.bits.tr_weightx_0   = pEncPara->tr_weightx_0;
    pAllReg->VEDU_PME_REGS.PME_TR_WEIGHTY.bits.tr_weighty_2   = pEncPara->tr_weighty_2;
    pAllReg->VEDU_PME_REGS.PME_TR_WEIGHTY.bits.tr_weighty_1   = pEncPara->tr_weighty_1;
    pAllReg->VEDU_PME_REGS.PME_TR_WEIGHTY.bits.tr_weighty_0   = pEncPara->tr_weighty_0;
    pAllReg->VEDU_PME_REGS.PME_SR_WEIGHT.bits.sr_weight_2     = pEncPara->sr_weight_2;
    pAllReg->VEDU_PME_REGS.PME_SR_WEIGHT.bits.sr_weight_1     = pEncPara->sr_weight_1;
    pAllReg->VEDU_PME_REGS.PME_SR_WEIGHT.bits.sr_weight_0     = pEncPara->sr_weight_0;
    pAllReg->VEDU_PME_REGS.pme_skin_thr.bits.skin_v_min_thr   = pEncPara->skin_v_min_thr;
    pAllReg->VEDU_PME_REGS.pme_skin_thr.bits.skin_v_max_thr   = pEncPara->skin_v_max_thr;
    pAllReg->VEDU_PME_REGS.pme_skin_thr.bits.skin_u_min_thr   = pEncPara->skin_u_min_thr;
    pAllReg->VEDU_PME_REGS.pme_skin_thr.bits.skin_u_max_thr   = pEncPara->skin_u_max_thr;
    pAllReg->VEDU_PME_REGS.pme_high_edge.bits.still_scene_thr = pEncPara->still_scene_thr;
    pAllReg->VEDU_PME_REGS.pme_high_edge.bits.high_edge_cnt   = pEncPara->high_edge_cnt;
    pAllReg->VEDU_PME_REGS.pme_high_edge.bits.high_edge_thr   = pEncPara->high_edge_thr;
    pAllReg->VEDU_PME_REGS.pme_high_edge.bits.skin_num        = pEncPara->skin_num;
    // Refld 0x20620800
    pAllReg->VEDU_REFID_REGS.REFLD_CMD_CFG.bits.refld_vcpi2cont_title_en  = 1;
    pAllReg->VEDU_REFID_REGS.REFLD_CMD_CFG.bits.ddr_cross_idx             = pEncPara->refld_ddr_cross_idx;
    // Ime  0x20620a00
    pAllReg->VEDU_IME_REGS.INTER_MODE.bits.vcpi_high3pre_en               = pEncPara->vcpi_high3pre_en;
    pAllReg->VEDU_IME_REGS.INTER_MODE.bits.vcpi_rect3_mod                 = pEncPara->vcpi_rect3_mod;
    pAllReg->VEDU_IME_REGS.INTER_MODE.bits.vcpi_rect2_mod                 = pEncPara->vcpi_rect2_mod;
    pAllReg->VEDU_IME_REGS.INTER_MODE.bits.vcpi_rect1_mod                 = pEncPara->vcpi_rect1_mod;
    pAllReg->VEDU_IME_REGS.INTER_MODE.bits.vcpi_inter8x8_en               = pEncPara->vcpi_inter8x8_en;
    pAllReg->VEDU_IME_REGS.IME_CFG1.bits.vcpi_rect0_vstep                 = pEncPara->vcpi_rect0_vstep;
    pAllReg->VEDU_IME_REGS.IME_CFG1.bits.vcpi_rect0_hstep                 = pEncPara->vcpi_rect0_hstep;
    pAllReg->VEDU_IME_REGS.IME_CFG2.bits.vcpi_rect1_vstep                 = pEncPara->vcpi_rect1_vstep;
    pAllReg->VEDU_IME_REGS.IME_CFG2.bits.vcpi_rect1_hstep                 = pEncPara->vcpi_rect1_hstep;
    pAllReg->VEDU_IME_REGS.IME_CFG3.bits.vcpi_rect2_vstep                 = pEncPara->vcpi_rect2_vstep;
    pAllReg->VEDU_IME_REGS.IME_CFG3.bits.vcpi_rect2_hstep                 = pEncPara->vcpi_rect2_hstep;
    pAllReg->VEDU_IME_REGS.IME_CFG4.bits.vcpi_rect3_vstep                 = pEncPara->vcpi_rect3_vstep;
    pAllReg->VEDU_IME_REGS.IME_CFG4.bits.vcpi_rect3_hstep                 = pEncPara->vcpi_rect3_hstep;
    pAllReg->VEDU_IME_REGS.IME_THR0.bits.vcpi_start_thr                   = pEncPara->vcpi_start_thr;
    pAllReg->VEDU_IME_REGS.IME_THR1.bits.vcpi_intra_thr                   = pEncPara->vcpi_intra_thr;
    pAllReg->VEDU_IME_REGS.IME_RDOCFG.bits.vcpi_lambdaoff16               = pEncPara->vcpi_lambdaoff16;
    pAllReg->VEDU_IME_REGS.IME_RDOCFG.bits.vcpi_lambdaoff8                = pEncPara->vcpi_lambdaoff8;
    pAllReg->VEDU_IME_REGS.IME_FME_LPOW_THR.bits.vcpi_lowpow_fme_thr1     = pEncPara->vcpi_lowpow_fme_thr1;
    pAllReg->VEDU_IME_REGS.IME_FME_LPOW_THR.bits.vcpi_lowpow_fme_thr0     = pEncPara->vcpi_lowpow_fme_thr0;
    //Qpg  0x20620c00
    pAllReg->VEDU_QPG_REGS.QPG_MAX_MIN_QP.bits.max_qp                     = pEncPara->max_qp;
    pAllReg->VEDU_QPG_REGS.QPG_MAX_MIN_QP.bits.min_qp                     = pEncPara->min_qp;
    pAllReg->VEDU_QPG_REGS.QPG_AVERAGE_LCU_BITS.bits.ave_lcu_bits         = pEncPara_channel->iAveLcuBits;
    pAllReg->VEDU_QPG_REGS.QPG_QP_DELTA.bits.qp_delta                     = pEncPara->qp_delta;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG0.bits.cu_qp_delta_thresh3  = pEncPara->cu_qp_delta_thresh3;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG0.bits.cu_qp_delta_thresh2  = pEncPara->cu_qp_delta_thresh2;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG0.bits.cu_qp_delta_thresh1  = pEncPara->cu_qp_delta_thresh1;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG0.bits.cu_qp_delta_thresh0  = pEncPara->cu_qp_delta_thresh0;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG1.bits.cu_qp_delta_thresh7  = pEncPara->cu_qp_delta_thresh7;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG1.bits.cu_qp_delta_thresh6  = pEncPara->cu_qp_delta_thresh6;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG1.bits.cu_qp_delta_thresh5  = pEncPara->cu_qp_delta_thresh5;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG1.bits.cu_qp_delta_thresh4  = pEncPara->cu_qp_delta_thresh4;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG2.bits.cu_qp_delta_thresh11 = pEncPara->cu_qp_delta_thresh11;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG2.bits.cu_qp_delta_thresh10 = pEncPara->cu_qp_delta_thresh10;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG2.bits.cu_qp_delta_thresh9  = pEncPara->cu_qp_delta_thresh9;
    pAllReg->VEDU_QPG_REGS.QPG_CU_QP_DELTA_THRESH_REG2.bits.cu_qp_delta_thresh8  = pEncPara->cu_qp_delta_thresh8;
    pAllReg->VEDU_QPG_REGS.QPG_STRONG_EDGE_QP_DELTA.bits.strong_edge_qp_delta    = pEncPara->strong_edge_qp_delta;
    pAllReg->VEDU_QPG_REGS.QPG_SKIN_QP_DELTA.bits.skin_qp_delta                  = pEncPara->skin_qp_delta;

    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG00.bits.lambda00 = pEncPara->lambda00;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG01.bits.lambda01 = pEncPara->lambda01;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG02.bits.lambda02 = pEncPara->lambda02;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG03.bits.lambda03 = pEncPara->lambda03;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG04.bits.lambda04 = pEncPara->lambda04;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG05.bits.lambda05 = pEncPara->lambda05;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG06.bits.lambda06 = pEncPara->lambda06;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG07.bits.lambda07 = pEncPara->lambda07;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG08.bits.lambda08 = pEncPara->lambda08;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG09.bits.lambda09 = pEncPara->lambda09;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG10.bits.lambda10 = pEncPara->lambda10;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG11.bits.lambda11 = pEncPara->lambda11;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG12.bits.lambda12 = pEncPara->lambda12;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG13.bits.lambda13 = pEncPara->lambda13;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG14.bits.lambda14 = pEncPara->lambda14;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG15.bits.lambda15 = pEncPara->lambda15;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG16.bits.lambda16 = pEncPara->lambda16;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG17.bits.lambda17 = pEncPara->lambda17;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG18.bits.lambda18 = pEncPara->lambda18;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG19.bits.lambda19 = pEncPara->lambda19;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG20.bits.lambda20 = pEncPara->lambda20;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG21.bits.lambda21 = pEncPara->lambda21;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG22.bits.lambda22 = pEncPara->lambda22;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG23.bits.lambda23 = pEncPara->lambda23;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG24.bits.lambda24 = pEncPara->lambda24;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG25.bits.lambda25 = pEncPara->lambda25;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG26.bits.lambda26 = pEncPara->lambda26;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG27.bits.lambda27 = pEncPara->lambda27;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG28.bits.lambda28 = pEncPara->lambda28;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG29.bits.lambda29 = pEncPara->lambda29;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG30.bits.lambda30 = pEncPara->lambda30;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG31.bits.lambda31 = pEncPara->lambda31;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG32.bits.lambda32 = pEncPara->lambda32;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG33.bits.lambda33 = pEncPara->lambda33;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG34.bits.lambda34 = pEncPara->lambda34;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG35.bits.lambda35 = pEncPara->lambda35;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG36.bits.lambda36 = pEncPara->lambda36;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG37.bits.lambda37 = pEncPara->lambda37;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG38.bits.lambda38 = pEncPara->lambda38;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG39.bits.lambda39 = pEncPara->lambda39;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG40.bits.lambda40 = pEncPara->lambda40;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG41.bits.lambda41 = pEncPara->lambda41;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG42.bits.lambda42 = pEncPara->lambda42;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG43.bits.lambda43 = pEncPara->lambda43;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG44.bits.lambda44 = pEncPara->lambda44;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG45.bits.lambda45 = pEncPara->lambda45;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG46.bits.lambda46 = pEncPara->lambda46;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG47.bits.lambda47 = pEncPara->lambda47;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG48.bits.lambda48 = pEncPara->lambda48;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG49.bits.lambda49 = pEncPara->lambda49;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG50.bits.lambda50 = pEncPara->lambda50;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG51.bits.lambda51 = pEncPara->lambda51;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG52.bits.lambda52 = pEncPara->lambda52;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG53.bits.lambda53 = pEncPara->lambda53;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG54.bits.lambda54 = pEncPara->lambda54;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG55.bits.lambda55 = pEncPara->lambda55;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG56.bits.lambda56 = pEncPara->lambda56;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG57.bits.lambda57 = pEncPara->lambda57;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG58.bits.lambda58 = pEncPara->lambda58;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG59.bits.lambda59 = pEncPara->lambda59;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG60.bits.lambda60 = pEncPara->lambda60;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG61.bits.lambda61 = pEncPara->lambda61;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG62.bits.lambda62 = pEncPara->lambda62;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG63.bits.lambda63 = pEncPara->lambda63;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG64.bits.lambda64 = pEncPara->lambda64;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG65.bits.lambda65 = pEncPara->lambda65;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG66.bits.lambda66 = pEncPara->lambda66;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG67.bits.lambda67 = pEncPara->lambda67;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG68.bits.lambda68 = pEncPara->lambda68;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG69.bits.lambda69 = pEncPara->lambda69;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG70.bits.lambda70 = pEncPara->lambda70;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG71.bits.lambda71 = pEncPara->lambda71;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG72.bits.lambda72 = pEncPara->lambda72;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG73.bits.lambda73 = pEncPara->lambda73;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG74.bits.lambda74 = pEncPara->lambda74;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG75.bits.lambda75 = pEncPara->lambda75;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG76.bits.lambda76 = pEncPara->lambda76;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG77.bits.lambda77 = pEncPara->lambda77;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG78.bits.lambda78 = pEncPara->lambda78;
    pAllReg->VEDU_QPG_REGS.QPG_QP_LAMBDA_CTRL_REG79.bits.lambda79 = pEncPara->lambda79;
    //Intra  0x20621200
    pAllReg->VEDU_INTRA_REGS.INTER_AVAIL.bits.inter_avail                 = pEncPara->inter_avail;
    pAllReg->VEDU_INTRA_REGS.INTRA_SMOOTH.bits.intra_smooth               = pEncPara->intra_smooth;
    pAllReg->VEDU_INTRA_REGS.INTRA_BIT_WEIGHT.bits.intra_bit_weight       = pEncPara->intra_bit_weight;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode31_en = pEncPara->intra_cu4_mode31_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode30_en = pEncPara->intra_cu4_mode30_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode29_en = pEncPara->intra_cu4_mode29_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode28_en = pEncPara->intra_cu4_mode28_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode27_en = pEncPara->intra_cu4_mode27_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode26_en = pEncPara->intra_cu4_mode26_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode25_en = pEncPara->intra_cu4_mode25_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode24_en = pEncPara->intra_cu4_mode24_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode23_en = pEncPara->intra_cu4_mode23_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode22_en = pEncPara->intra_cu4_mode22_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode21_en = pEncPara->intra_cu4_mode21_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode20_en = pEncPara->intra_cu4_mode20_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode19_en = pEncPara->intra_cu4_mode19_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode18_en = pEncPara->intra_cu4_mode18_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode17_en = pEncPara->intra_cu4_mode17_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode16_en = pEncPara->intra_cu4_mode16_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode15_en = pEncPara->intra_cu4_mode15_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode14_en = pEncPara->intra_cu4_mode14_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode13_en = pEncPara->intra_cu4_mode13_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode12_en = pEncPara->intra_cu4_mode12_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode11_en = pEncPara->intra_cu4_mode11_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode10_en = pEncPara->intra_cu4_mode10_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode9_en  = pEncPara->intra_cu4_mode9_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode8_en  = pEncPara->intra_cu4_mode8_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode7_en  = pEncPara->intra_cu4_mode7_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode6_en  = pEncPara->intra_cu4_mode6_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode5_en  = pEncPara->intra_cu4_mode5_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode4_en  = pEncPara->intra_cu4_mode4_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode3_en  = pEncPara->intra_cu4_mode3_en;

    if (pEncPara->vcpi_protocol == VEDU_H265)
    {
        pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode2_en     = pEncPara->intra_cu4_mode2_en;
    }
    else if (pEncPara->vcpi_protocol == VEDU_H264)
    {
        if((pEncPara->vcpi_intra_cu_en & 0x1) == 1)
        {
            pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode2_en = 1 ;
        }
    }

    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode1_en   = pEncPara->intra_cu4_mode1_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_0EN.bits.intra_cu4_mode0_en   = pEncPara->intra_cu4_mode0_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_1EN.bits.intra_cu4_mode34_en  = pEncPara->intra_cu4_mode34_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_1EN.bits.intra_cu4_mode33_en  = pEncPara->intra_cu4_mode33_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL4_ANG_1EN.bits.intra_cu4_mode32_en  = pEncPara->intra_cu4_mode32_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode31_en  = pEncPara->intra_cu8_mode31_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode30_en  = pEncPara->intra_cu8_mode30_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode29_en  = pEncPara->intra_cu8_mode29_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode28_en  = pEncPara->intra_cu8_mode28_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode27_en  = pEncPara->intra_cu8_mode27_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode26_en  = pEncPara->intra_cu8_mode26_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode25_en  = pEncPara->intra_cu8_mode25_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode24_en  = pEncPara->intra_cu8_mode24_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode23_en  = pEncPara->intra_cu8_mode23_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode22_en  = pEncPara->intra_cu8_mode22_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode21_en  = pEncPara->intra_cu8_mode21_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode20_en  = pEncPara->intra_cu8_mode20_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode19_en  = pEncPara->intra_cu8_mode19_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode18_en  = pEncPara->intra_cu8_mode18_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode17_en  = pEncPara->intra_cu8_mode17_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode16_en  = pEncPara->intra_cu8_mode16_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode15_en  = pEncPara->intra_cu8_mode15_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode14_en  = pEncPara->intra_cu8_mode14_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode13_en  = pEncPara->intra_cu8_mode13_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode12_en  = pEncPara->intra_cu8_mode12_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode11_en  = pEncPara->intra_cu8_mode11_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode10_en  = pEncPara->intra_cu8_mode10_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode9_en   = pEncPara->intra_cu8_mode9_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode8_en   = pEncPara->intra_cu8_mode8_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode7_en   = pEncPara->intra_cu8_mode7_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode6_en   = pEncPara->intra_cu8_mode6_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode5_en   = pEncPara->intra_cu8_mode5_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode4_en   = pEncPara->intra_cu8_mode4_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode3_en   = pEncPara->intra_cu8_mode3_en;

    if (pEncPara->vcpi_protocol == VEDU_H265)
    {
        pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode2_en  = pEncPara->intra_cu8_mode2_en;
    }
    else if (pEncPara->vcpi_protocol == VEDU_H264)
    {
        if((pEncPara->vcpi_intra_cu_en& 0x2) == 2)
        {
           pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode2_en = 1;
        }
    }
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode1_en    = pEncPara->intra_cu8_mode1_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_0EN.bits.intra_cu8_mode0_en    = pEncPara->intra_cu8_mode0_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_1EN.bits.intra_cu8_mode34_en   = pEncPara->intra_cu8_mode34_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_1EN.bits.intra_cu8_mode33_en   = pEncPara->intra_cu8_mode33_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL8_ANG_1EN.bits.intra_cu8_mode32_en   = pEncPara->intra_cu8_mode32_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode31_en = pEncPara->intra_cu16_mode31_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode30_en = pEncPara->intra_cu16_mode30_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode29_en = pEncPara->intra_cu16_mode29_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode28_en = pEncPara->intra_cu16_mode28_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode27_en = pEncPara->intra_cu16_mode27_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode26_en = pEncPara->intra_cu16_mode26_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode25_en = pEncPara->intra_cu16_mode25_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode24_en = pEncPara->intra_cu16_mode24_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode23_en = pEncPara->intra_cu16_mode23_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode22_en = pEncPara->intra_cu16_mode22_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode21_en = pEncPara->intra_cu16_mode21_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode20_en = pEncPara->intra_cu16_mode20_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode19_en = pEncPara->intra_cu16_mode19_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode18_en = pEncPara->intra_cu16_mode18_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode17_en = pEncPara->intra_cu16_mode17_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode16_en = pEncPara->intra_cu16_mode16_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode15_en = pEncPara->intra_cu16_mode15_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode14_en = pEncPara->intra_cu16_mode14_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode13_en = pEncPara->intra_cu16_mode13_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode12_en = pEncPara->intra_cu16_mode12_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode11_en = pEncPara->intra_cu16_mode11_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode10_en = pEncPara->intra_cu16_mode10_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode9_en   = pEncPara->intra_cu16_mode9_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode8_en   = pEncPara->intra_cu16_mode8_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode7_en   = pEncPara->intra_cu16_mode7_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode6_en   = pEncPara->intra_cu16_mode6_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode5_en   = pEncPara->intra_cu16_mode5_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode4_en   = pEncPara->intra_cu16_mode4_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode3_en   = pEncPara->intra_cu16_mode3_en;

    if (pEncPara->vcpi_protocol == VEDU_H265)
    {
        pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode2_en = pEncPara->intra_cu16_mode2_en;
    }
    else if (pEncPara->vcpi_protocol == VEDU_H264)
    {
        if((pEncPara->vcpi_intra_cu_en& 0x4) == 4)
        {
            pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode2_en = 1;
        }
    }

    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode1_en   = pEncPara->intra_cu16_mode1_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_0EN.bits.intra_cu16_mode0_en   = pEncPara->intra_cu16_mode0_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_1EN.bits.intra_cu16_mode34_en  = pEncPara->intra_cu16_mode34_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_1EN.bits.intra_cu16_mode33_en  = pEncPara->intra_cu16_mode33_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL16_ANG_1EN.bits.intra_cu16_mode32_en  = pEncPara->intra_cu16_mode32_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode31_en  = pEncPara->intra_cu32_mode31_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode30_en  = pEncPara->intra_cu32_mode30_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode29_en  = pEncPara->intra_cu32_mode29_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode28_en  = pEncPara->intra_cu32_mode28_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode27_en  = pEncPara->intra_cu32_mode27_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode26_en  = pEncPara->intra_cu32_mode26_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode25_en  = pEncPara->intra_cu32_mode25_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode24_en  = pEncPara->intra_cu32_mode24_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode23_en  = pEncPara->intra_cu32_mode23_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode22_en  = pEncPara->intra_cu32_mode22_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode21_en  = pEncPara->intra_cu32_mode21_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode20_en  = pEncPara->intra_cu32_mode20_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode19_en  = pEncPara->intra_cu32_mode19_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode18_en  = pEncPara->intra_cu32_mode18_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode17_en  = pEncPara->intra_cu32_mode17_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode16_en  = pEncPara->intra_cu32_mode16_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode15_en  = pEncPara->intra_cu32_mode15_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode14_en  = pEncPara->intra_cu32_mode14_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode13_en  = pEncPara->intra_cu32_mode13_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode12_en  = pEncPara->intra_cu32_mode12_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode11_en  = pEncPara->intra_cu32_mode11_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode10_en  = pEncPara->intra_cu32_mode10_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode9_en   = pEncPara->intra_cu32_mode9_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode8_en   = pEncPara->intra_cu32_mode8_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode7_en   = pEncPara->intra_cu32_mode7_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode6_en   = pEncPara->intra_cu32_mode6_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode5_en   = pEncPara->intra_cu32_mode5_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode4_en   = pEncPara->intra_cu32_mode4_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode3_en   = pEncPara->intra_cu32_mode3_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode2_en   = pEncPara->intra_cu32_mode2_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode1_en   = pEncPara->intra_cu32_mode1_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_0EN.bits.intra_cu32_mode0_en   = pEncPara->intra_cu32_mode0_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_1EN.bits.intra_cu32_mode34_en  = pEncPara->intra_cu32_mode34_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_1EN.bits.intra_cu32_mode33_en  = pEncPara->intra_cu32_mode33_en;
    pAllReg->VEDU_INTRA_REGS.INTRA_CHNL32_ANG_1EN.bits.intra_cu32_mode32_en  = pEncPara->intra_cu32_mode32_en;
    //Pmv  0x20621400
    pAllReg->VEDU_PMV_REGS.PMV_TMV_EN.bits.tmv_en                            = pEncPara->tmv_en;
    //Tqitq  0x20621600
    pAllReg->VEDU_TQITQ_REGS.TQITQ_QSCALINGLIST.bits.q_scaling_waddr         = pEncPara->q_scaling_waddr;
    pAllReg->VEDU_TQITQ_REGS.TQITQ_QSCALINGLIST.bits.q_scaling_wdata         = pEncPara->q_scaling_wdata;
    // Pack  0x20621e00

    pAllReg->VEDU_PACK_REGS.PACK_CU_PARAMETER.bits.vcpi2cu_qp_min_cu_size         = pEncPara->vcpi2cu_qp_min_cu_size;
    pAllReg->VEDU_PACK_REGS.PACK_CU_PARAMETER.bits.vcpi2cu_tq_bypass_enabled_flag = pEncPara->vcpi2cu_tq_bypass_enabled_flag;
    pAllReg->VEDU_PACK_REGS.PACK_PCM_PARAMETER.bits.vcpi2pu_log2_max_ipcm_cbsizey = pEncPara->vcpi2pu_log2_max_ipcm_cbsizey;
    pAllReg->VEDU_PACK_REGS.PACK_PCM_PARAMETER.bits.vcpi2pu_log2_min_ipcm_cbsizey = pEncPara->vcpi2pu_log2_min_ipcm_cbsizey;
    pAllReg->VEDU_PACK_REGS.PACK_TF_SKIP_FLAG.bits.vcpi2res_tf_skip_enabled_flag  = pEncPara->vcpi2res_tf_skip_enabled_flag;
    //Cabac  0x20622000
    pAllReg->VEDU_CABAC_REGS.CABAC_GLB_CFG.bits.nal_unit_head                     = pEncPara->nal_unit_head;
    pAllReg->VEDU_CABAC_REGS.CABAC_GLB_CFG.bits.max_num_mergecand                 = pEncPara->max_num_mergecand;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_SIZE.bits.slchdr_size_part2             = pEncPara->slchdr_size_part2;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_SIZE.bits.slchdr_size_part1             = pEncPara->slchdr_size_part1;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART1.bits.slchdr_part1                 = pEncPara->slchdr_part1;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG1                           = pEncPara->slchdr_part2_seg1;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG2                           = pEncPara->slchdr_part2_seg2;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG3                           = pEncPara->slchdr_part2_seg3;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG4                           = pEncPara->slchdr_part2_seg4;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG5                           = pEncPara->slchdr_part2_seg5;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG6                           = pEncPara->slchdr_part2_seg6;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG7                           = pEncPara->slchdr_part2_seg7;
    pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG8                           = pEncPara->slchdr_part2_seg8;
    //recst  0x20622a00
    pAllReg->VEDU_RECST_REGS.RECST_DDR_CROSS.bits.ddr_cross_idx                = pEncPara->recst_ddr_cross_idx;      //0725

    //vlcst  0x20622c00
    pAllReg->VEDU_VLCST_REGS.VLCST_PTBITS_EN.bits.ptbits_en                    = pEncPara->ptbits_en;
    pAllReg->VEDU_VLCST_REGS.VLCST_PTBITS                                      = pEncPara->ptbits;

    //vlc  0x20622e00
    pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm0                       = pEncPara->vcpi_slchdrstrm0;
    pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm1                       = pEncPara->vcpi_slchdrstrm1;
    pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm2                       = pEncPara->vcpi_slchdrstrm2;
    pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm3                       = pEncPara->vcpi_slchdrstrm3;
    pAllReg->VEDU_VLC_REGS.VLC_ReorderStrm0                      = pEncPara->vcpi_reorderstrm0;
    pAllReg->VEDU_VLC_REGS.VLC_ReorderStrm1                      = pEncPara->vcpi_reorderstrm1;
    pAllReg->VEDU_VLC_REGS.VLC_MarkingStrm0                      = pEncPara->vcpi_markingstrm0;
    pAllReg->VEDU_VLC_REGS.VLC_MarkingStrm1                      = pEncPara->vcpi_markingstrm1;
	pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_parabit      = pEncPara->vcpi_parabit;
	pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_reorderbit   = pEncPara->vcpi_reorderbit;
	pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_markingbit   = pEncPara->vcpi_markingbit;
    pAllReg->VEDU_VLC_REGS.VLC_SVC.bits.vcpi_svc_strm            = pEncPara->vcpi_svc_strm;
    pAllReg->VEDU_VLC_REGS.VLC_SVC.bits.vcpi_svc_en              = pEncPara->vcpi_svc_en;

    //Curpre    0x20623000
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER0.bits.curld_filter_hshift    = pEncPara->curld_filter_hshift;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER0.bits.curld_filter_hrnd      = pEncPara->curld_filter_hrnd;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER0.bits.curld_filter_h3        = pEncPara->curld_filter_h3;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER0.bits.curld_filter_h2        = pEncPara->curld_filter_h2;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER0.bits.curld_filter_h1        = pEncPara->curld_filter_h1;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER0.bits.curld_filter_h0        = pEncPara->curld_filter_h0;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER1.bits.curld_filter_vshift    = pEncPara->curld_filter_vshift;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER1.bits.curld_filter_vrnd      = pEncPara->curld_filter_vrnd;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER1.bits.curld_filter_v3        = pEncPara->curld_filter_v3;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER1.bits.curld_filter_v2        = pEncPara->curld_filter_v2;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER1.bits.curld_filter_v1        = pEncPara->curld_filter_v1;
    pAllReg->VEDU_CURPRE_REGS.VEDU_FILTER_PARAMETER1.bits.curld_filter_v0        = pEncPara->curld_filter_v0;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER0.bits.curld_y_filt_01coef = pEncPara->curld_y_filt_01coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER0.bits.curld_y_filt_00coef = pEncPara->curld_y_filt_00coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER1.bits.curld_y_filt_03coef = pEncPara->curld_y_filt_03coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER1.bits.curld_y_filt_02coef = pEncPara->curld_y_filt_02coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER2.bits.curld_y_filt_11coef = pEncPara->curld_y_filt_11coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER2.bits.curld_y_filt_10coef = pEncPara->curld_y_filt_10coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER3.bits.curld_y_filt_13coef = pEncPara->curld_y_filt_13coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER3.bits.curld_y_filt_12coef = pEncPara->curld_y_filt_12coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER4.bits.curld_y_filt_21coef = pEncPara->curld_y_filt_21coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER4.bits.curld_y_filt_20coef = pEncPara->curld_y_filt_20coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER5.bits.curld_y_filt_23coef = pEncPara->curld_y_filt_23coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER5.bits.curld_y_filt_22coef = pEncPara->curld_y_filt_22coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER6.bits.curld_y_filt_31coef = pEncPara->curld_y_filt_31coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER6.bits.curld_y_filt_30coef = pEncPara->curld_y_filt_30coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER7.bits.curld_y_filt_33coef = pEncPara->curld_y_filt_33coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER7.bits.curld_y_filt_32coef = pEncPara->curld_y_filt_32coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER8.bits.curld_c_filt_01coef = pEncPara->curld_c_filt_01coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER8.bits.curld_c_filt_00coef = pEncPara->curld_c_filt_00coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER9.bits.curld_c_filt_03coef = pEncPara->curld_c_filt_03coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER9.bits.curld_c_filt_02coef = pEncPara->curld_c_filt_02coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER10.bits.curld_c_filt_11coef = pEncPara->curld_c_filt_11coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER10.bits.curld_c_filt_10coef = pEncPara->curld_c_filt_10coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER11.bits.curld_c_filt_13coef = pEncPara->curld_c_filt_13coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER11.bits.curld_c_filt_12coef = pEncPara->curld_c_filt_12coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER12.bits.curld_c_filt_21coef = pEncPara->curld_c_filt_21coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER12.bits.curld_c_filt_20coef = pEncPara->curld_c_filt_20coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER13.bits.curld_c_filt_23coef = pEncPara->curld_c_filt_23coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER13.bits.curld_c_filt_22coef = pEncPara->curld_c_filt_22coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER14.bits.curld_c_filt_31coef = pEncPara->curld_c_filt_31coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER14.bits.curld_c_filt_30coef = pEncPara->curld_c_filt_30coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER15.bits.curld_c_filt_33coef = pEncPara->curld_c_filt_33coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_PARAMETER15.bits.curld_c_filt_32coef = pEncPara->curld_c_filt_32coef;

    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER0.bits.curld_y_filt_col_01coef = pEncPara->curld_y_filt_col_01coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER0.bits.curld_y_filt_col_00coef = pEncPara->curld_y_filt_col_00coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER1.bits.curld_y_filt_col_03coef = pEncPara->curld_y_filt_col_03coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER1.bits.curld_y_filt_col_02coef = pEncPara->curld_y_filt_col_02coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER2.bits.curld_y_filt_col_11coef = pEncPara->curld_y_filt_col_11coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER2.bits.curld_y_filt_col_10coef = pEncPara->curld_y_filt_col_10coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER3.bits.curld_y_filt_col_13coef = pEncPara->curld_y_filt_col_13coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER3.bits.curld_y_filt_col_12coef = pEncPara->curld_y_filt_col_12coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER4.bits.curld_y_filt_col_21coef = pEncPara->curld_y_filt_col_21coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER4.bits.curld_y_filt_col_20coef = pEncPara->curld_y_filt_col_20coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER5.bits.curld_y_filt_col_23coef = pEncPara->curld_y_filt_col_23coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER5.bits.curld_y_filt_col_22coef = pEncPara->curld_y_filt_col_22coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER6.bits.curld_y_filt_col_31coef = pEncPara->curld_y_filt_col_31coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER6.bits.curld_y_filt_col_30coef = pEncPara->curld_y_filt_col_30coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER7.bits.curld_y_filt_col_33coef = pEncPara->curld_y_filt_col_33coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER7.bits.curld_y_filt_col_32coef = pEncPara->curld_y_filt_col_32coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER8.bits.curld_c_filt_col_01coef = pEncPara->curld_c_filt_col_01coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER8.bits.curld_c_filt_col_00coef = pEncPara->curld_c_filt_col_00coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER9.bits.curld_c_filt_col_03coef = pEncPara->curld_c_filt_col_03coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER9.bits.curld_c_filt_col_02coef = pEncPara->curld_c_filt_col_02coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER10.bits.curld_c_filt_col_11coef = pEncPara->curld_c_filt_col_11coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER10.bits.curld_c_filt_col_10coef = pEncPara->curld_c_filt_col_10coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER11.bits.curld_c_filt_col_13coef = pEncPara->curld_c_filt_col_13coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER11.bits.curld_c_filt_col_12coef = pEncPara->curld_c_filt_col_12coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER12.bits.curld_c_filt_col_21coef = pEncPara->curld_c_filt_col_21coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER12.bits.curld_c_filt_col_20coef = pEncPara->curld_c_filt_col_20coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER13.bits.curld_c_filt_col_23coef = pEncPara->curld_c_filt_col_23coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER13.bits.curld_c_filt_col_22coef = pEncPara->curld_c_filt_col_22coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER14.bits.curld_c_filt_col_31coef = pEncPara->curld_c_filt_col_31coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER14.bits.curld_c_filt_col_30coef = pEncPara->curld_c_filt_col_30coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER15.bits.curld_c_filt_col_33coef = pEncPara->curld_c_filt_col_33coef;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_SCALE_COL_PARAMETER15.bits.curld_c_filt_col_32coef = pEncPara->curld_c_filt_col_32coef;

    pAllReg->VEDU_CURPRE_REGS.VEDU_CUR_GCFG.bits.curld_clip_en = pEncPara->curld_clip_en;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CLIP_THX.bits.clip_chrm_max = pEncPara->clip_chrm_max;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CLIP_THX.bits.clip_chrm_min = pEncPara->clip_chrm_min;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CLIP_THX.bits.clip_luma_max = pEncPara->clip_luma_max;
    pAllReg->VEDU_CURPRE_REGS.VEDU_CLIP_THX.bits.clip_luma_min = pEncPara->clip_luma_min;

    if (pEncPara_channel->vcpi_package_sel == 0x8 || pEncPara_channel->vcpi_package_sel == 0x5)
    {
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF0.bits.vcpi_coeff_ry = pEncPara->vcpi_coeff_by;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF0.bits.vcpi_coeff_gy = pEncPara->vcpi_coeff_gy;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF1.bits.vcpi_coeff_by = pEncPara->vcpi_coeff_ry;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF1.bits.vcpi_coeff_rcb = pEncPara->vcpi_coeff_bcb;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF2.bits.vcpi_coeff_gcb = pEncPara->vcpi_coeff_gcb;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF2.bits.vcpi_coeff_bcb = pEncPara->vcpi_coeff_rcb;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF3.bits.vcpi_coeff_rcr = pEncPara->vcpi_coeff_bcr;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF3.bits.vcpi_coeff_gcr = pEncPara->vcpi_coeff_gcr;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF4.bits.vcpi_coeff_bcr = pEncPara->vcpi_coeff_rcr;
        if (pEncPara_channel->vcpi_package_sel == 0x8)
        {
            pEncPara_channel->vcpi_package_sel  =0xd;
        }
        else
        {
            pEncPara_channel->vcpi_package_sel  =0x0;
        }
    }
    else
    {
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF0.bits.vcpi_coeff_ry  = pEncPara->vcpi_coeff_ry;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF0.bits.vcpi_coeff_gy  = pEncPara->vcpi_coeff_gy;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF1.bits.vcpi_coeff_by  = pEncPara->vcpi_coeff_by;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF1.bits.vcpi_coeff_rcb = pEncPara->vcpi_coeff_rcb;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF2.bits.vcpi_coeff_gcb = pEncPara->vcpi_coeff_gcb;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF2.bits.vcpi_coeff_bcb = pEncPara->vcpi_coeff_bcb;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF3.bits.vcpi_coeff_rcr = pEncPara->vcpi_coeff_rcr;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF3.bits.vcpi_coeff_gcr = pEncPara->vcpi_coeff_gcr;
        pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF4.bits.vcpi_coeff_bcr = pEncPara->vcpi_coeff_bcr;
    }

    pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF5.bits.vcpi_rgb_shift      = pEncPara->vcpi_rgb_shift;
    pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF5.bits.vcpi_rgb_rndy       = pEncPara->vcpi_rgb_rndy;
    pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF6.bits.vcpi_rgb_rndcb      = pEncPara->vcpi_rgb_rndcb;
    pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_COEF6.bits.vcpi_rgb_rndcr      = pEncPara->vcpi_rgb_rndcr;
    pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_CLIP.bits.vcpi_rgb_clip_en     = pEncPara->vcpi_rgb_clip_en;
    pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_CLIP.bits.vcpi_rgb_clpmax      = pEncPara->vcpi_rgb_clpmax;
    pAllReg->VEDU_CURPRE_REGS.VEDU_RGB_CLIP.bits.vcpi_rgb_clpmin      = pEncPara->vcpi_rgb_clpmin;
    pAllReg->VEDU_CURPRE_REGS.VEDU_WIDE_NARROW_EN.bits.curld_y_wide_narrow_en  = pEncPara->vcpi_wide_narrow_en;

    //emar   0x20623400
    pAllReg->VEDU_EMAR_REGS.EMAR_WAIT_TIM_OUT.bits.vcpi_wtmax         =pEncPara->vcpi_wtmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_WAIT_TIM_OUT.bits.vcpi_rtmax         =pEncPara->vcpi_rtmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH0.bits.vcpi_ch00_rrmax     =pEncPara->vcpi_ch00_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH0.bits.vcpi_ch01_rrmax     =pEncPara->vcpi_ch01_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH0.bits.vcpi_ch02_rrmax     =pEncPara->vcpi_ch02_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH0.bits.vcpi_ch03_rrmax     =pEncPara->vcpi_ch03_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH0.bits.vcpi_ch04_rrmax     =pEncPara->vcpi_ch04_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH0.bits.vcpi_ch05_rrmax     =pEncPara->vcpi_ch05_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH1.bits.vcpi_ch06_rrmax     =pEncPara->vcpi_ch06_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH1.bits.vcpi_ch07_rrmax     =pEncPara->vcpi_ch07_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH1.bits.vcpi_ch08_rrmax     =pEncPara->vcpi_ch08_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH1.bits.vcpi_ch09_rrmax     =pEncPara->vcpi_ch09_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH1.bits.vcpi_ch10_rrmax     =pEncPara->vcpi_ch10_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH1.bits.vcpi_ch11_rrmax     =pEncPara->vcpi_ch11_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH2.bits.vcpi_ch12_rrmax     =pEncPara->vcpi_ch12_rrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH3.bits.vcpi_ch00_wrmax    =pEncPara->vcpi_ch00_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH3.bits.vcpi_ch01_wrmax    =pEncPara->vcpi_ch01_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH3.bits.vcpi_ch02_wrmax    =pEncPara->vcpi_ch02_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH3.bits.vcpi_ch03_wrmax    =pEncPara->vcpi_ch03_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH3.bits.vcpi_ch04_wrmax    =pEncPara->vcpi_ch04_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH3.bits.vcpi_ch05_wrmax    =pEncPara->vcpi_ch05_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH4.bits.vcpi_ch06_wrmax    =pEncPara->vcpi_ch06_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH4.bits.vcpi_ch07_wrmax    =pEncPara->vcpi_ch07_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH4.bits.vcpi_ch08_wrmax    =pEncPara->vcpi_ch08_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH4.bits.vcpi_ch09_wrmax    =pEncPara->vcpi_ch09_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH4.bits.vcpi_ch10_wrmax    =pEncPara->vcpi_ch10_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH4.bits.vcpi_ch11_wrmax    =pEncPara->vcpi_ch11_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH5.bits.vcpi_ch12_wrmax    =pEncPara->vcpi_ch12_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH5.bits.vcpi_ch13_wrmax    =pEncPara->vcpi_ch13_wrmax;
    pAllReg->VEDU_EMAR_REGS.EMAR_RCH_RPT_TH5.bits.vcpi_ch14_wrmax    =pEncPara->vcpi_ch14_wrmax;

   /* mmu com0ÅäÖÃ */
 #if 1 //modify by gaoyajun
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.ptw_mid       =  pEncPara->comn0_ptw_mid;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.ptw_pf        =  pEncPara->comn0_ptw_pf;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.smr_rd_shadow =  pEncPara->comn0_smr_rd_shadow;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.wqos          =  pEncPara->comn0_wqos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.rqos          =  pEncPara->comn0_rqos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.cache_l2_en   =  pEncPara->comn0_cache_l2_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.cache_l1_en   =  pEncPara->comn0_cache_l1_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.int_en        =  pEncPara->comn0_int_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.wqos_en       =  pEncPara->comn0_wqos_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.rqos_en       =  pEncPara->comn0_rqos_en;
#endif
 //    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.glb_bypass = pEncPara_channel->bMMUByPass;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.glb_bypass = pEncPara->comn0_glb_bypass;//glb bypass ÅäÖÃ£¬ÊÇ·ñÐèÒªÈ·ÈÏ?

#if 0
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_MEMCTRL.bits.mem_ctrl_rd   =  pEncPara->comn0_mem_ctrl_rd;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_MEMCTRL.bits.mem_ctrl_wr   =  pEncPara->comn0_mem_ctrl_wr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_LP_CTRL.bits.auto_clk_gt_en      =  pEncPara->comn0_auto_clk_gt_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel15     =  pEncPara->comn0_remap_sel15;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel14     =  pEncPara->comn0_remap_sel14;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel13     =  pEncPara->comn0_remap_sel13;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel12     =  pEncPara->comn0_remap_sel12;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel11     =  pEncPara->comn0_remap_sel11;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel10     =  pEncPara->comn0_remap_sel10;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel9      =  pEncPara->comn0_remap_sel9;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel8      =  pEncPara->comn0_remap_sel8;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel7      =  pEncPara->comn0_remap_sel7;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel6      =  pEncPara->comn0_remap_sel6;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel5      =  pEncPara->comn0_remap_sel5;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel4      =  pEncPara->comn0_remap_sel4;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel3      =  pEncPara->comn0_remap_sel3;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel2      =  pEncPara->comn0_remap_sel2;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel1      =  pEncPara->comn0_remap_sel1;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_PRESS_REMAP.bits.remap_sel0      =  pEncPara->comn0_remap_sel0;

     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ptw_ns_msk =  pEncPara->comn0_intns_ptw_ns_msk;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ptw_invalid_msk  =  pEncPara->comn0_intns_ptw_invalid_msk;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ptw_trans_msk    =  pEncPara->comn0_intns_ptw_trans_msk;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_tlbmiss_msk      =  pEncPara->comn0_intns_tlbmiss_msk;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ext_msk          =  pEncPara->comn0_intns_ext_msk;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_permis_msk       =  pEncPara->comn0_intns_permis_msk;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTCLR_NS.bits.intns_ptw_ns_clr        =  pEncPara->comn0_intns_ptw_ns_clr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTCLR_NS.bits.intns_ptw_invalid_clr   =  pEncPara->comn0_intns_ptw_invalid_clr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTCLR_NS.bits.intns_ptw_trans_clr     =  pEncPara->comn0_intns_ptw_trans_clr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTCLR_NS.bits.intns_tlbmiss_clr       =  pEncPara->comn0_intns_tlbmiss_clr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTCLR_NS.bits.intns_ext_clr           =  pEncPara->comn0_intns_ext_clr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTCLR_NS.bits.intns_permis_clr        =  pEncPara->comn0_intns_permis_clr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR0_NS.bits.smr0_offset_addr          =  pEncPara->comn0_smr0_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR0_NS.bits.smr0_ptw_qos              =  pEncPara->comn0_smr0_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR0_NS.bits.smr0_invld_en             =  pEncPara->comn0_smr0_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR0_NS.bits.smr0_bypass               =  pEncPara->comn0_smr0_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR1_NS.bits.smr1_offset_addr          =  pEncPara->comn0_smr1_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR1_NS.bits.smr1_ptw_qos              =  pEncPara->comn0_smr1_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR1_NS.bits.smr1_invld_en             =  pEncPara->comn0_smr1_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR1_NS.bits.smr1_bypass               =  pEncPara->comn0_smr1_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR2_NS.bits.smr2_offset_addr          =  pEncPara->comn0_smr2_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR2_NS.bits.smr2_ptw_qos              =  pEncPara->comn0_smr2_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR2_NS.bits.smr2_invld_en             =  pEncPara->comn0_smr2_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR2_NS.bits.smr2_bypass               =  pEncPara->comn0_smr2_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR3_NS.bits.smr3_offset_addr          =  pEncPara->comn0_smr3_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR3_NS.bits.smr3_ptw_qos              =  pEncPara->comn0_smr3_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR3_NS.bits.smr3_invld_en             =  pEncPara->comn0_smr3_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR3_NS.bits.smr3_bypass               =  pEncPara->comn0_smr3_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR4_NS.bits.smr4_offset_addr          =  pEncPara->comn0_smr4_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR4_NS.bits.smr4_ptw_qos              =  pEncPara->comn0_smr4_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR4_NS.bits.smr4_invld_en             =  pEncPara->comn0_smr4_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR4_NS.bits.smr4_bypass               =  pEncPara->comn0_smr4_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR5_NS.bits.smr5_offset_addr          =  pEncPara->comn0_smr5_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR5_NS.bits.smr5_ptw_qos              =  pEncPara->comn0_smr5_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR5_NS.bits.smr5_invld_en             =  pEncPara->comn0_smr5_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR5_NS.bits.smr5_bypass               =  pEncPara->comn0_smr5_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR6_NS.bits.smr6_offset_addr          =  pEncPara->comn0_smr6_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR6_NS.bits.smr6_ptw_qos              =  pEncPara->comn0_smr6_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR6_NS.bits.smr6_invld_en             =  pEncPara->comn0_smr6_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR6_NS.bits.smr6_bypass               =  pEncPara->comn0_smr6_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR7_NS.bits.smr7_offset_addr          =  pEncPara->comn0_smr7_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR7_NS.bits.smr7_ptw_qos              =  pEncPara->comn0_smr7_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR7_NS.bits.smr7_invld_en             =  pEncPara->comn0_smr7_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR7_NS.bits.smr7_bypass               =  pEncPara->comn0_smr7_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR8_NS.bits.smr8_offset_addr          =  pEncPara->comn0_smr8_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR8_NS.bits.smr8_ptw_qos              =  pEncPara->comn0_smr8_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR8_NS.bits.smr8_invld_en             =  pEncPara->comn0_smr8_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR8_NS.bits.smr8_bypass               =  pEncPara->comn0_smr8_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR9_NS.bits.smr9_offset_addr          =  pEncPara->comn0_smr9_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR9_NS.bits.smr9_ptw_qos              =  pEncPara->comn0_smr9_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR9_NS.bits.smr9_invld_en             =  pEncPara->comn0_smr9_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR9_NS.bits.smr9_bypass               =  pEncPara->comn0_smr9_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR10_NS.bits.smr10_offset_addr        =  pEncPara->comn0_smr10_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR10_NS.bits.smr10_ptw_qos            =  pEncPara->comn0_smr10_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR10_NS.bits.smr10_invld_en           =  pEncPara->comn0_smr10_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR10_NS.bits.smr10_bypass             =  pEncPara->comn0_smr10_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR11_NS.bits.smr11_offset_addr        =  pEncPara->comn0_smr11_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR11_NS.bits.smr11_ptw_qos            =  pEncPara->comn0_smr11_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR11_NS.bits.smr11_invld_en           =  pEncPara->comn0_smr11_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR11_NS.bits.smr11_bypass             =  pEncPara->comn0_smr11_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR12_NS.bits.smr12_offset_addr        =  pEncPara->comn0_smr12_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR12_NS.bits.smr12_ptw_qos            =  pEncPara->comn0_smr12_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR12_NS.bits.smr12_invld_en           =  pEncPara->comn0_smr12_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR12_NS.bits.smr12_bypass             =  pEncPara->comn0_smr12_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR13_NS.bits.smr13_offset_addr        =  pEncPara->comn0_smr13_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR13_NS.bits.smr13_ptw_qos            =  pEncPara->comn0_smr13_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR13_NS.bits.smr13_invld_en           =  pEncPara->comn0_smr13_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR13_NS.bits.smr13_bypass             =  pEncPara->comn0_smr13_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR14_NS.bits.smr14_offset_addr        =  pEncPara->comn0_smr14_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR14_NS.bits.smr14_ptw_qos            =  pEncPara->comn0_smr14_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR14_NS.bits.smr14_invld_en           =  pEncPara->comn0_smr14_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR14_NS.bits.smr14_bypass             =  pEncPara->comn0_smr14_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR15_NS.bits.smr15_offset_addr        =  pEncPara->comn0_smr15_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR15_NS.bits.smr15_ptw_qos            =  pEncPara->comn0_smr15_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR15_NS.bits.smr15_invld_en           =  pEncPara->comn0_smr15_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR15_NS.bits.smr15_bypass             =  pEncPara->comn0_smr15_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR16_NS.bits.smr16_offset_addr        =  pEncPara->comn0_smr16_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR16_NS.bits.smr16_ptw_qos            =  pEncPara->comn0_smr16_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR16_NS.bits.smr16_invld_en           =  pEncPara->comn0_smr16_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR16_NS.bits.smr16_bypass             =  pEncPara->comn0_smr16_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR17_NS.bits.smr17_offset_addr        =  pEncPara->comn0_smr17_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR17_NS.bits.smr17_ptw_qos            =  pEncPara->comn0_smr17_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR17_NS.bits.smr17_invld_en           =  pEncPara->comn0_smr17_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR17_NS.bits.smr17_bypass             =  pEncPara->comn0_smr17_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR18_NS.bits.smr18_offset_addr        =  pEncPara->comn0_smr18_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR18_NS.bits.smr18_ptw_qos            =  pEncPara->comn0_smr18_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR18_NS.bits.smr18_invld_en           =  pEncPara->comn0_smr18_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR18_NS.bits.smr18_bypass             =  pEncPara->comn0_smr18_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR19_NS.bits.smr19_offset_addr        =  pEncPara->comn0_smr19_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR19_NS.bits.smr19_ptw_qos            =  pEncPara->comn0_smr19_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR19_NS.bits.smr19_invld_en           =  pEncPara->comn0_smr19_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR19_NS.bits.smr19_bypass             =  pEncPara->comn0_smr19_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR20_NS.bits.smr20_offset_addr        =  pEncPara->comn0_smr20_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR20_NS.bits.smr20_ptw_qos            =  pEncPara->comn0_smr20_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR20_NS.bits.smr20_invld_en           =  pEncPara->comn0_smr20_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR20_NS.bits.smr20_bypass             =  pEncPara->comn0_smr20_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR21_NS.bits.smr21_offset_addr        =  pEncPara->comn0_smr21_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR21_NS.bits.smr21_ptw_qos            =  pEncPara->comn0_smr21_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR21_NS.bits.smr21_invld_en           =  pEncPara->comn0_smr21_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR21_NS.bits.smr21_bypass             =  pEncPara->comn0_smr21_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR22_NS.bits.smr22_offset_addr        =  pEncPara->comn0_smr22_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR22_NS.bits.smr22_ptw_qos            =  pEncPara->comn0_smr22_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR22_NS.bits.smr22_invld_en           =  pEncPara->comn0_smr22_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR22_NS.bits.smr22_bypass             =  pEncPara->comn0_smr22_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR23_NS.bits.smr23_offset_addr        =  pEncPara->comn0_smr23_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR23_NS.bits.smr23_ptw_qos            =  pEncPara->comn0_smr23_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR23_NS.bits.smr23_invld_en           =  pEncPara->comn0_smr23_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR23_NS.bits.smr23_bypass             =  pEncPara->comn0_smr23_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR24_NS.bits.smr24_offset_addr        =  pEncPara->comn0_smr24_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR24_NS.bits.smr24_ptw_qos            =  pEncPara->comn0_smr24_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR24_NS.bits.smr24_invld_en           =  pEncPara->comn0_smr24_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR24_NS.bits.smr24_bypass             =  pEncPara->comn0_smr24_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR25_NS.bits.smr25_offset_addr        =  pEncPara->comn0_smr25_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR25_NS.bits.smr25_ptw_qos            =  pEncPara->comn0_smr25_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR25_NS.bits.smr25_invld_en           =  pEncPara->comn0_smr25_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR25_NS.bits.smr25_bypass             =  pEncPara->comn0_smr25_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR26_NS.bits.smr26_offset_addr        =  pEncPara->comn0_smr26_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR26_NS.bits.smr26_ptw_qos            =  pEncPara->comn0_smr26_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR26_NS.bits.smr26_invld_en           =  pEncPara->comn0_smr26_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR26_NS.bits.smr26_bypass             =  pEncPara->comn0_smr26_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR27_NS.bits.smr27_offset_addr        =  pEncPara->comn0_smr27_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR27_NS.bits.smr27_ptw_qos            =  pEncPara->comn0_smr27_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR27_NS.bits.smr27_invld_en           =  pEncPara->comn0_smr27_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR27_NS.bits.smr27_bypass             =  pEncPara->comn0_smr27_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR28_NS.bits.smr28_offset_addr        =  pEncPara->comn0_smr28_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR28_NS.bits.smr28_ptw_qos            =  pEncPara->comn0_smr28_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR28_NS.bits.smr28_invld_en           =  pEncPara->comn0_smr28_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR28_NS.bits.smr28_bypass             =  pEncPara->comn0_smr28_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR29_NS.bits.smr29_offset_addr        =  pEncPara->comn0_smr29_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR29_NS.bits.smr29_ptw_qos            =  pEncPara->comn0_smr29_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR29_NS.bits.smr29_invld_en           =  pEncPara->comn0_smr29_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR29_NS.bits.smr29_bypass             =  pEncPara->comn0_smr29_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR30_NS.bits.smr30_offset_addr        =  pEncPara->comn0_smr30_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR30_NS.bits.smr30_ptw_qos            =  pEncPara->comn0_smr30_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR30_NS.bits.smr30_invld_en           =  pEncPara->comn0_smr30_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR30_NS.bits.smr30_bypass             =  pEncPara->comn0_smr30_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR31_NS.bits.smr31_offset_addr        =  pEncPara->comn0_smr31_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR31_NS.bits.smr31_ptw_qos            =  pEncPara->comn0_smr31_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR31_NS.bits.smr31_invld_en           =  pEncPara->comn0_smr31_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR31_NS.bits.smr31_bypass             =  pEncPara->comn0_smr31_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR32_NS.bits.smr32_offset_addr        =  pEncPara->comn0_smr32_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR32_NS.bits.smr32_ptw_qos            =  pEncPara->comn0_smr32_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR32_NS.bits.smr32_invld_en           =  pEncPara->comn0_smr32_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR32_NS.bits.smr32_bypass             =  pEncPara->comn0_smr32_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR33_NS.bits.smr33_offset_addr        =  pEncPara->comn0_smr33_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR33_NS.bits.smr33_ptw_qos            =  pEncPara->comn0_smr33_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR33_NS.bits.smr33_invld_en           =  pEncPara->comn0_smr33_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR33_NS.bits.smr33_bypass             =  pEncPara->comn0_smr33_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR34_NS.bits.smr34_offset_addr        =  pEncPara->comn0_smr34_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR34_NS.bits.smr34_ptw_qos            =  pEncPara->comn0_smr34_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR34_NS.bits.smr34_invld_en           =  pEncPara->comn0_smr34_invld_en;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR34_NS.bits.smr34_bypass             =  pEncPara->comn0_smr34_bypass;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR35_NS.bits.smr35_offset_addr        =  pEncPara->comn0_smr35_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR35_NS.bits.smr35_ptw_qos            =  pEncPara->comn0_smr35_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR35_NS.bits.smr35_invld_en           =  pEncPara->comn0_smr35_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR35_NS.bits.smr35_bypass             =  pEncPara->comn0_smr35_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR36_NS.bits.smr36_offset_addr        =  pEncPara->comn0_smr36_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR36_NS.bits.smr36_ptw_qos            =  pEncPara->comn0_smr36_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR36_NS.bits.smr36_invld_en           =  pEncPara->comn0_smr36_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR36_NS.bits.smr36_bypass             =  pEncPara->comn0_smr36_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR37_NS.bits.smr37_offset_addr        =  pEncPara->comn0_smr37_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR37_NS.bits.smr37_ptw_qos            =  pEncPara->comn0_smr37_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR37_NS.bits.smr37_invld_en           =  pEncPara->comn0_smr37_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR37_NS.bits.smr37_bypass             =  pEncPara->comn0_smr37_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR38_NS.bits.smr38_offset_addr        =  pEncPara->comn0_smr38_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR38_NS.bits.smr38_ptw_qos            =  pEncPara->comn0_smr38_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR38_NS.bits.smr38_invld_en           =  pEncPara->comn0_smr38_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR38_NS.bits.smr38_bypass             =  pEncPara->comn0_smr38_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR39_NS.bits.smr39_offset_addr        =  pEncPara->comn0_smr39_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR39_NS.bits.smr39_ptw_qos            =  pEncPara->comn0_smr39_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR39_NS.bits.smr39_invld_en           =  pEncPara->comn0_smr39_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR39_NS.bits.smr39_bypass             =  pEncPara->comn0_smr39_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR40_NS.bits.smr40_offset_addr        =  pEncPara->comn0_smr40_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR40_NS.bits.smr40_ptw_qos            =  pEncPara->comn0_smr40_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR40_NS.bits.smr40_invld_en           =  pEncPara->comn0_smr40_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR40_NS.bits.smr40_bypass             =  pEncPara->comn0_smr40_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR41_NS.bits.smr41_offset_addr        =  pEncPara->comn0_smr41_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR41_NS.bits.smr41_ptw_qos            =  pEncPara->comn0_smr41_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR41_NS.bits.smr41_invld_en           =  pEncPara->comn0_smr41_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR41_NS.bits.smr41_bypass             =  pEncPara->comn0_smr41_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR42_NS.bits.smr42_offset_addr        =  pEncPara->comn0_smr42_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR42_NS.bits.smr42_ptw_qos            =  pEncPara->comn0_smr42_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR42_NS.bits.smr42_invld_en           =  pEncPara->comn0_smr42_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR42_NS.bits.smr42_bypass             =  pEncPara->comn0_smr42_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR43_NS.bits.smr43_offset_addr        =  pEncPara->comn0_smr43_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR43_NS.bits.smr43_ptw_qos            =  pEncPara->comn0_smr43_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR43_NS.bits.smr43_invld_en           =  pEncPara->comn0_smr43_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR43_NS.bits.smr43_bypass             =  pEncPara->comn0_smr43_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR44_NS.bits.smr44_offset_addr        =  pEncPara->comn0_smr44_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR44_NS.bits.smr44_ptw_qos            =  pEncPara->comn0_smr44_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR44_NS.bits.smr44_invld_en           =  pEncPara->comn0_smr44_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR44_NS.bits.smr44_bypass             =  pEncPara->comn0_smr44_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR45_NS.bits.smr45_offset_addr        =  pEncPara->comn0_smr45_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR45_NS.bits.smr45_ptw_qos            =  pEncPara->comn0_smr45_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR45_NS.bits.smr45_invld_en           =  pEncPara->comn0_smr45_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR45_NS.bits.smr45_bypass             =  pEncPara->comn0_smr45_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR46_NS.bits.smr46_offset_addr        =  pEncPara->comn0_smr46_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR46_NS.bits.smr46_ptw_qos            =  pEncPara->comn0_smr46_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR46_NS.bits.smr46_invld_en           =  pEncPara->comn0_smr46_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR46_NS.bits.smr46_bypass             =  pEncPara->comn0_smr46_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR47_NS.bits.smr47_offset_addr        =  pEncPara->comn0_smr47_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR47_NS.bits.smr47_ptw_qos            =  pEncPara->comn0_smr47_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR47_NS.bits.smr47_invld_en           =  pEncPara->comn0_smr47_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR47_NS.bits.smr47_bypass             =  pEncPara->comn0_smr47_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR48_NS.bits.smr48_offset_addr        =  pEncPara->comn0_smr48_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR48_NS.bits.smr48_ptw_qos            =  pEncPara->comn0_smr48_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR48_NS.bits.smr48_invld_en           =  pEncPara->comn0_smr48_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR48_NS.bits.smr48_bypass             =  pEncPara->comn0_smr48_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR49_NS.bits.smr49_offset_addr        =  pEncPara->comn0_smr49_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR49_NS.bits.smr49_ptw_qos            =  pEncPara->comn0_smr49_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR49_NS.bits.smr49_invld_en           =  pEncPara->comn0_smr49_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR49_NS.bits.smr49_bypass             =  pEncPara->comn0_smr49_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR50_NS.bits.smr50_offset_addr        =  pEncPara->comn0_smr50_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR50_NS.bits.smr50_ptw_qos            =  pEncPara->comn0_smr50_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR50_NS.bits.smr50_invld_en           =  pEncPara->comn0_smr50_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR50_NS.bits.smr50_bypass             =  pEncPara->comn0_smr50_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR51_NS.bits.smr51_offset_addr        =  pEncPara->comn0_smr51_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR51_NS.bits.smr51_ptw_qos            =  pEncPara->comn0_smr51_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR51_NS.bits.smr51_invld_en           =  pEncPara->comn0_smr51_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR51_NS.bits.smr51_bypass             =  pEncPara->comn0_smr51_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR52_NS.bits.smr52_offset_addr        =  pEncPara->comn0_smr52_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR52_NS.bits.smr52_ptw_qos            =  pEncPara->comn0_smr52_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR52_NS.bits.smr52_invld_en           =  pEncPara->comn0_smr52_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR52_NS.bits.smr52_bypass             =  pEncPara->comn0_smr52_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR53_NS.bits.smr53_offset_addr        =  pEncPara->comn0_smr53_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR53_NS.bits.smr53_ptw_qos            =  pEncPara->comn0_smr53_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR53_NS.bits.smr53_invld_en           =  pEncPara->comn0_smr53_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR53_NS.bits.smr53_bypass             =  pEncPara->comn0_smr53_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR54_NS.bits.smr54_offset_addr        =  pEncPara->comn0_smr54_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR54_NS.bits.smr54_ptw_qos            =  pEncPara->comn0_smr54_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR54_NS.bits.smr54_invld_en           =  pEncPara->comn0_smr54_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR54_NS.bits.smr54_bypass             =  pEncPara->comn0_smr54_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR55_NS.bits.smr55_offset_addr        =  pEncPara->comn0_smr55_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR55_NS.bits.smr55_ptw_qos            =  pEncPara->comn0_smr55_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR55_NS.bits.smr55_invld_en           =  pEncPara->comn0_smr55_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR55_NS.bits.smr55_bypass             =  pEncPara->comn0_smr55_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR56_NS.bits.smr56_offset_addr        =  pEncPara->comn0_smr56_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR56_NS.bits.smr56_ptw_qos            =  pEncPara->comn0_smr56_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR56_NS.bits.smr56_invld_en           =  pEncPara->comn0_smr56_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR56_NS.bits.smr56_bypass             =  pEncPara->comn0_smr56_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR57_NS.bits.smr57_offset_addr        =  pEncPara->comn0_smr57_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR57_NS.bits.smr57_ptw_qos            =  pEncPara->comn0_smr57_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR57_NS.bits.smr57_invld_en           =  pEncPara->comn0_smr57_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR57_NS.bits.smr57_bypass             =  pEncPara->comn0_smr57_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR58_NS.bits.smr58_offset_addr        =  pEncPara->comn0_smr58_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR58_NS.bits.smr58_ptw_qos            =  pEncPara->comn0_smr58_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR58_NS.bits.smr58_invld_en           =  pEncPara->comn0_smr58_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR58_NS.bits.smr58_bypass             =  pEncPara->comn0_smr58_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR59_NS.bits.smr59_offset_addr        =  pEncPara->comn0_smr59_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR59_NS.bits.smr59_ptw_qos            =  pEncPara->comn0_smr59_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR59_NS.bits.smr59_invld_en           =  pEncPara->comn0_smr59_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR59_NS.bits.smr59_bypass             =  pEncPara->comn0_smr59_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR60_NS.bits.smr60_offset_addr        =  pEncPara->comn0_smr60_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR60_NS.bits.smr60_ptw_qos            =  pEncPara->comn0_smr60_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR60_NS.bits.smr60_invld_en           =  pEncPara->comn0_smr60_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR60_NS.bits.smr60_bypass             =  pEncPara->comn0_smr60_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR61_NS.bits.smr61_offset_addr        =  pEncPara->comn0_smr61_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR61_NS.bits.smr61_ptw_qos            =  pEncPara->comn0_smr61_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR61_NS.bits.smr61_invld_en           =  pEncPara->comn0_smr61_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR61_NS.bits.smr61_bypass             =  pEncPara->comn0_smr61_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR62_NS.bits.smr62_offset_addr        =  pEncPara->comn0_smr62_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR62_NS.bits.smr62_ptw_qos            =  pEncPara->comn0_smr62_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR62_NS.bits.smr62_invld_en           =  pEncPara->comn0_smr62_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR62_NS.bits.smr62_bypass             =  pEncPara->comn0_smr62_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR63_NS.bits.smr63_offset_addr        =  pEncPara->comn0_smr63_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR63_NS.bits.smr63_ptw_qos            =  pEncPara->comn0_smr63_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR63_NS.bits.smr63_invld_en           =  pEncPara->comn0_smr63_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR63_NS.bits.smr63_bypass             =  pEncPara->comn0_smr63_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR64_NS.bits.smr64_offset_addr        =  pEncPara->comn0_smr64_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR64_NS.bits.smr64_ptw_qos            =  pEncPara->comn0_smr64_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR64_NS.bits.smr64_invld_en           =  pEncPara->comn0_smr64_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR64_NS.bits.smr64_bypass             =  pEncPara->comn0_smr64_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR65_NS.bits.smr65_offset_addr        =  pEncPara->comn0_smr65_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR65_NS.bits.smr65_ptw_qos            =  pEncPara->comn0_smr65_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR65_NS.bits.smr65_invld_en           =  pEncPara->comn0_smr65_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR65_NS.bits.smr65_bypass             =  pEncPara->comn0_smr65_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR66_NS.bits.smr66_offset_addr        =  pEncPara->comn0_smr66_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR66_NS.bits.smr66_ptw_qos            =  pEncPara->comn0_smr66_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR66_NS.bits.smr66_invld_en           =  pEncPara->comn0_smr66_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR66_NS.bits.smr66_bypass             =  pEncPara->comn0_smr66_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR67_NS.bits.smr67_offset_addr        =  pEncPara->comn0_smr67_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR67_NS.bits.smr67_ptw_qos            =  pEncPara->comn0_smr67_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR67_NS.bits.smr67_invld_en           =  pEncPara->comn0_smr67_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR67_NS.bits.smr67_bypass             =  pEncPara->comn0_smr67_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR68_NS.bits.smr68_offset_addr        =  pEncPara->comn0_smr68_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR68_NS.bits.smr68_ptw_qos            =  pEncPara->comn0_smr68_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR68_NS.bits.smr68_invld_en           =  pEncPara->comn0_smr68_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR68_NS.bits.smr68_bypass             =  pEncPara->comn0_smr68_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR69_NS.bits.smr69_offset_addr        =  pEncPara->comn0_smr69_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR69_NS.bits.smr69_ptw_qos            =  pEncPara->comn0_smr69_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR69_NS.bits.smr69_invld_en           =  pEncPara->comn0_smr69_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR69_NS.bits.smr69_bypass             =  pEncPara->comn0_smr69_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR70_NS.bits.smr70_offset_addr        =  pEncPara->comn0_smr70_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR70_NS.bits.smr70_ptw_qos            =  pEncPara->comn0_smr70_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR70_NS.bits.smr70_invld_en           =  pEncPara->comn0_smr70_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR70_NS.bits.smr70_bypass             =  pEncPara->comn0_smr70_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR71_NS.bits.smr71_offset_addr        =  pEncPara->comn0_smr71_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR71_NS.bits.smr71_ptw_qos            =  pEncPara->comn0_smr71_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR71_NS.bits.smr71_invld_en           =  pEncPara->comn0_smr71_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR71_NS.bits.smr71_bypass             =  pEncPara->comn0_smr71_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR72_NS.bits.smr72_offset_addr        =  pEncPara->comn0_smr72_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR72_NS.bits.smr72_ptw_qos            =  pEncPara->comn0_smr72_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR72_NS.bits.smr72_invld_en           =  pEncPara->comn0_smr72_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR72_NS.bits.smr72_bypass             =  pEncPara->comn0_smr72_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR73_NS.bits.smr73_offset_addr        =  pEncPara->comn0_smr73_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR73_NS.bits.smr73_ptw_qos            =  pEncPara->comn0_smr73_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR73_NS.bits.smr73_invld_en           =  pEncPara->comn0_smr73_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR73_NS.bits.smr73_bypass             =  pEncPara->comn0_smr73_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR74_NS.bits.smr74_offset_addr        =  pEncPara->comn0_smr74_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR74_NS.bits.smr74_ptw_qos            =  pEncPara->comn0_smr74_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR74_NS.bits.smr74_invld_en           =  pEncPara->comn0_smr74_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR74_NS.bits.smr74_bypass             =  pEncPara->comn0_smr74_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR75_NS.bits.smr75_offset_addr        =  pEncPara->comn0_smr75_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR75_NS.bits.smr75_ptw_qos            =  pEncPara->comn0_smr75_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR75_NS.bits.smr75_invld_en           =  pEncPara->comn0_smr75_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR75_NS.bits.smr75_bypass             =  pEncPara->comn0_smr75_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR76_NS.bits.smr76_offset_addr        =  pEncPara->comn0_smr76_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR76_NS.bits.smr76_ptw_qos            =  pEncPara->comn0_smr76_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR76_NS.bits.smr76_invld_en           =  pEncPara->comn0_smr76_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR76_NS.bits.smr76_bypass             =  pEncPara->comn0_smr76_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR77_NS.bits.smr77_offset_addr        =  pEncPara->comn0_smr77_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR77_NS.bits.smr77_ptw_qos            =  pEncPara->comn0_smr77_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR77_NS.bits.smr77_invld_en           =  pEncPara->comn0_smr77_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR77_NS.bits.smr77_bypass             =  pEncPara->comn0_smr77_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR78_NS.bits.smr78_offset_addr        =  pEncPara->comn0_smr78_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR78_NS.bits.smr78_ptw_qos            =  pEncPara->comn0_smr78_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR78_NS.bits.smr78_invld_en           =  pEncPara->comn0_smr78_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR78_NS.bits.smr78_bypass             =  pEncPara->comn0_smr78_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR79_NS.bits.smr79_offset_addr        =  pEncPara->comn0_smr79_offset_addr;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR79_NS.bits.smr79_ptw_qos            =  pEncPara->comn0_smr79_ptw_qos    ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR79_NS.bits.smr79_invld_en           =  pEncPara->comn0_smr79_invld_en   ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR79_NS.bits.smr79_bypass             =  pEncPara->comn0_smr79_bypass     ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_RLD_EN0_NS                             =  pEncPara->comn0_smr_rld_en0;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_RLD_EN1_NS                             =  pEncPara->comn0_smr_rld_en1;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_RLD_EN2_NS.bits.smr_rld_en2            =  pEncPara->comn0_smr_rld_en2;
  #endif
    /* mmu com1ÅäÖÃ */
//    pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_SCTRL.bits.cb_bypass               =  pEncPara->comn1_cb_bypass;
    domain_data = (struct iommu_domain_data *)(g_hisi_mmu_domain->priv);
    phy_pgd_base = (HI_U32)(domain_data->phy_pgd_base);
    HI_INFO_VENC("phy_pgd_base:0x%x\n",phy_pgd_base);

    pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_TTBR0 = phy_pgd_base;
    pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_TTBR1 = phy_pgd_base;
#if 0
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_TTBCR.bits.cb_ttbcr_t1sz            =  pEncPara->comn1_cb_ttbcr_t1sz;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_TTBCR.bits.cb_ttbcr_n               =  pEncPara->comn1_cb_ttbcr_n;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_TTBCR.bits.cb_ttbcr_t0sz            =  pEncPara->comn1_cb_ttbcr_t0sz;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_TTBCR.bits.cb_ttbcr_des             =  pEncPara->comn1_cb_ttbcr_des;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OFFSET_ADDR_NS.bits.offset_addr_ns     =  pEncPara->comn1_offset_addr_ns;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_SCACHEI_ALL.bits.cache_all_level       =  pEncPara->comn1_cache_all_level;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_SCACHEI_ALL.bits.cache_all_invalid     =  pEncPara->comn1_cache_all_invalid;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_SCACHEI_L1.bits.cache_l1_security      =  pEncPara->comn1_cache_l1_security;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_SCACHEI_L1.bits.cache_l1_invalid       =  pEncPara->comn1_cache_l1_invalid;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_SCACHEI_L2L3.bits.cache_l2l3_strmid    =  pEncPara->comn1_cache_l2l3_strmid;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_SCACHEI_L2L3.bits.cache_l2l3_invalid   =  pEncPara->comn1_cache_l2l3_invalid;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_FAMA_CTRL0_NS.bits.fama_bps_msb_ns     =  pEncPara->comn1_fama_bps_msb_ns;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_FAMA_CTRL0_NS.bits.fama_chn_sel_ns     =  pEncPara->comn1_fama_chn_sel_ns;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_FAMA_CTRL0_NS.bits.fama_sdes_msb_ns    =  pEncPara->comn1_fama_sdes_msb_ns;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_FAMA_CTRL1_NS.bits.fama_ptw_msb_ns     =  pEncPara->comn1_fama_ptw_msb_ns;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_ADDR_MSB.bits.msb_ova                  =  pEncPara->comn1_msb_ova;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_ADDR_MSB.bits.msb_errwr                =  pEncPara->comn1_msb_errwr;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_ADDR_MSB.bits.msb_errrd                =  pEncPara->comn1_msb_errrd;
#endif
    pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_ERR_RDADDR = pEncPara_channel->MMURdAddr;//config alloc phyaddr,in order system don't dump
    pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_ERR_WRADDR = pEncPara_channel->MMUWrAddr;
#if 0
	  pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGRPTR_TLB.bits.dbg_tlb_type                =  pEncPara->comn1_dbg_tlb_type         ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGRPTR_TLB.bits.dbg_tlbentry_pointer        =  pEncPara->comn1_dbg_tlbentry_pointer ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGRPTR_TLB.bits.dbg_tlbword_pointer         =  pEncPara->comn1_dbg_tlbword_pointer  ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGRPTR_CACHE.bits.dbg_cache_l2_strmid       =  pEncPara->comn1_dbg_cache_l2_strmid  ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGRPTR_CACHE.bits.dbg_cache_l1_ns           =  pEncPara->comn1_dbg_cache_l1_ns      ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGRPTR_CACHE.bits.dbg_cache_l1_pointer      =  pEncPara->comn1_dbg_cache_l1_pointer ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGRPTR_CACHE.bits.dbg_cache_level           =  pEncPara->comn1_dbg_cache_level      ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_DBGAXI_CTRL.bits.dbg_axilock_en              =  pEncPara->comn1_dbg_axilock_en       ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OVA_ADDR                                     =  pEncPara->comn1_override_va          ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OVA_CTRL.bits.override_tbu_num               =  pEncPara->comn1_override_tbu_num     ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OVA_CTRL.bits.override_va_strmid             =  pEncPara->comn1_override_va_strmid   ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OVA_CTRL.bits.override_va_indexid            =  pEncPara->comn1_override_va_indexid  ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OVA_CTRL.bits.override_va_type               =  pEncPara->comn1_override_va_type     ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OVA_CTRL.bits.override_va_cfg                =  pEncPara->comn1_override_va_cfg      ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OPREF_ADDR                                   =  pEncPara->comn1_override_pref_addr   ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OPREF_CTRL.bits.override_pref_strmid         =  pEncPara->comn1_override_pref_strmid ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OPREF_CTRL.bits.override_pref_indexid        =  pEncPara->comn1_override_pref_indexid;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OPREF_CTRL.bits.override_pref_initial        =  pEncPara->comn1_override_pref_initial;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OPREF_CTRL.bits.override_pref_type           =  pEncPara->comn1_override_pref_type   ;
      pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_OPREF_CTRL.bits.override_pref_cfg            =  pEncPara->comn1_override_pref_cfg    ;

    /* mmu com2ÅäÖÃ */
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR0_S.bits.smr0_offset_addr_s               =  pEncPara->comn2_smr0_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR0_S.bits.smr0_nscfg_en                    =  pEncPara->comn2_smr0_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR0_S.bits.smr0_nscfg                       =  pEncPara->comn2_smr0_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR1_S.bits.smr1_offset_addr_s               =  pEncPara->comn2_smr1_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR1_S.bits.smr1_nscfg_en                    =  pEncPara->comn2_smr1_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR1_S.bits.smr1_nscfg                       =  pEncPara->comn2_smr1_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR2_S.bits.smr2_offset_addr_s               =  pEncPara->comn2_smr2_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR2_S.bits.smr2_nscfg_en                    =  pEncPara->comn2_smr2_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR2_S.bits.smr2_nscfg                       =  pEncPara->comn2_smr2_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR3_S.bits.smr3_offset_addr_s               =  pEncPara->comn2_smr3_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR3_S.bits.smr3_nscfg_en                    =  pEncPara->comn2_smr3_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR3_S.bits.smr3_nscfg                       =  pEncPara->comn2_smr3_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR4_S.bits.smr4_offset_addr_s               =  pEncPara->comn2_smr4_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR4_S.bits.smr4_nscfg_en                    =  pEncPara->comn2_smr4_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR4_S.bits.smr4_nscfg                       =  pEncPara->comn2_smr4_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR5_S.bits.smr5_offset_addr_s               =  pEncPara->comn2_smr5_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR5_S.bits.smr5_nscfg_en                    =  pEncPara->comn2_smr5_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR5_S.bits.smr5_nscfg                       =  pEncPara->comn2_smr5_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR6_S.bits.smr6_offset_addr_s               =  pEncPara->comn2_smr6_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR6_S.bits.smr6_nscfg_en                    =  pEncPara->comn2_smr6_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR6_S.bits.smr6_nscfg                       =  pEncPara->comn2_smr6_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR7_S.bits.smr7_offset_addr_s               =  pEncPara->comn2_smr7_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR7_S.bits.smr7_nscfg_en                    =  pEncPara->comn2_smr7_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR7_S.bits.smr7_nscfg                       =  pEncPara->comn2_smr7_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR8_S.bits.smr8_offset_addr_s               =  pEncPara->comn2_smr8_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR8_S.bits.smr8_nscfg_en                    =  pEncPara->comn2_smr8_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR8_S.bits.smr8_nscfg                       =  pEncPara->comn2_smr8_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR9_S.bits.smr9_offset_addr_s               =  pEncPara->comn2_smr9_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR9_S.bits.smr9_nscfg_en                    =  pEncPara->comn2_smr9_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR9_S.bits.smr9_nscfg                       =  pEncPara->comn2_smr9_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR10_S.bits.smr10_offset_addr_s             =  pEncPara->comn2_smr10_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR10_S.bits.smr10_nscfg_en                  =  pEncPara->comn2_smr10_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR10_S.bits.smr10_nscfg                     =  pEncPara->comn2_smr10_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR11_S.bits.smr11_offset_addr_s             =  pEncPara->comn2_smr11_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR11_S.bits.smr11_nscfg_en                  =  pEncPara->comn2_smr11_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR11_S.bits.smr11_nscfg                     =  pEncPara->comn2_smr11_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR12_S.bits.smr12_offset_addr_s             =  pEncPara->comn2_smr12_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR12_S.bits.smr12_nscfg_en                  =  pEncPara->comn2_smr12_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR12_S.bits.smr12_nscfg                     =  pEncPara->comn2_smr12_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR13_S.bits.smr13_offset_addr_s             =  pEncPara->comn2_smr13_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR13_S.bits.smr13_nscfg_en                  =  pEncPara->comn2_smr13_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR13_S.bits.smr13_nscfg                     =  pEncPara->comn2_smr13_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR14_S.bits.smr14_offset_addr_s             =  pEncPara->comn2_smr14_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR14_S.bits.smr14_nscfg_en                  =  pEncPara->comn2_smr14_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR14_S.bits.smr14_nscfg                     =  pEncPara->comn2_smr14_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR15_S.bits.smr15_offset_addr_s             =  pEncPara->comn2_smr15_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR15_S.bits.smr15_nscfg_en                  =  pEncPara->comn2_smr15_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR15_S.bits.smr15_nscfg                     =  pEncPara->comn2_smr15_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR16_S.bits.smr16_offset_addr_s             =  pEncPara->comn2_smr16_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR16_S.bits.smr16_nscfg_en                  =  pEncPara->comn2_smr16_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR16_S.bits.smr16_nscfg                     =  pEncPara->comn2_smr16_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR17_S.bits.smr17_offset_addr_s             =  pEncPara->comn2_smr17_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR17_S.bits.smr17_nscfg_en                  =  pEncPara->comn2_smr17_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR17_S.bits.smr17_nscfg                     =  pEncPara->comn2_smr17_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR18_S.bits.smr18_offset_addr_s             =  pEncPara->comn2_smr18_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR18_S.bits.smr18_nscfg_en                  =  pEncPara->comn2_smr18_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR18_S.bits.smr18_nscfg                     =  pEncPara->comn2_smr18_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR19_S.bits.smr19_offset_addr_s             =  pEncPara->comn2_smr19_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR19_S.bits.smr19_nscfg_en                  =  pEncPara->comn2_smr19_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR19_S.bits.smr19_nscfg                     =  pEncPara->comn2_smr19_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR20_S.bits.smr20_offset_addr_s             =  pEncPara->comn2_smr20_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR20_S.bits.smr20_nscfg_en                  =  pEncPara->comn2_smr20_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR20_S.bits.smr20_nscfg                     =  pEncPara->comn2_smr20_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR21_S.bits.smr21_offset_addr_s             =  pEncPara->comn2_smr21_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR21_S.bits.smr21_nscfg_en                  =  pEncPara->comn2_smr21_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR21_S.bits.smr21_nscfg                     =  pEncPara->comn2_smr21_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR22_S.bits.smr22_offset_addr_s             =  pEncPara->comn2_smr22_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR22_S.bits.smr22_nscfg_en                  =  pEncPara->comn2_smr22_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR22_S.bits.smr22_nscfg                     =  pEncPara->comn2_smr22_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR23_S.bits.smr23_offset_addr_s             =  pEncPara->comn2_smr23_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR23_S.bits.smr23_nscfg_en                  =  pEncPara->comn2_smr23_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR23_S.bits.smr23_nscfg                     =  pEncPara->comn2_smr23_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR24_S.bits.smr24_offset_addr_s             =  pEncPara->comn2_smr24_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR24_S.bits.smr24_nscfg_en                  =  pEncPara->comn2_smr24_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR24_S.bits.smr24_nscfg                     =  pEncPara->comn2_smr24_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR25_S.bits.smr25_offset_addr_s             =  pEncPara->comn2_smr25_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR25_S.bits.smr25_nscfg_en                  =  pEncPara->comn2_smr25_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR25_S.bits.smr25_nscfg                     =  pEncPara->comn2_smr25_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR26_S.bits.smr26_offset_addr_s             =  pEncPara->comn2_smr26_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR26_S.bits.smr26_nscfg_en                  =  pEncPara->comn2_smr26_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR26_S.bits.smr26_nscfg                     =  pEncPara->comn2_smr26_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR27_S.bits.smr27_offset_addr_s             =  pEncPara->comn2_smr27_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR27_S.bits.smr27_nscfg_en                  =  pEncPara->comn2_smr27_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR27_S.bits.smr27_nscfg                     =  pEncPara->comn2_smr27_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR28_S.bits.smr28_offset_addr_s             =  pEncPara->comn2_smr28_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR28_S.bits.smr28_nscfg_en                  =  pEncPara->comn2_smr28_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR28_S.bits.smr28_nscfg                     =  pEncPara->comn2_smr28_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR29_S.bits.smr29_offset_addr_s             =  pEncPara->comn2_smr29_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR29_S.bits.smr29_nscfg_en                  =  pEncPara->comn2_smr29_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR29_S.bits.smr29_nscfg                     =  pEncPara->comn2_smr29_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR30_S.bits.smr30_offset_addr_s             =  pEncPara->comn2_smr30_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR30_S.bits.smr30_nscfg_en                  =  pEncPara->comn2_smr30_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR30_S.bits.smr30_nscfg                     =  pEncPara->comn2_smr30_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR31_S.bits.smr31_offset_addr_s             =  pEncPara->comn2_smr31_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR31_S.bits.smr31_nscfg_en                  =  pEncPara->comn2_smr31_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR31_S.bits.smr31_nscfg                     =  pEncPara->comn2_smr31_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR32_S.bits.smr32_offset_addr_s             =  pEncPara->comn2_smr32_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR32_S.bits.smr32_nscfg_en                  =  pEncPara->comn2_smr32_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR32_S.bits.smr32_nscfg                     =  pEncPara->comn2_smr32_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR33_S.bits.smr33_offset_addr_s             =  pEncPara->comn2_smr33_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR33_S.bits.smr33_nscfg_en                  =  pEncPara->comn2_smr33_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR33_S.bits.smr33_nscfg                     =  pEncPara->comn2_smr33_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR34_S.bits.smr34_offset_addr_s             =  pEncPara->comn2_smr34_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR34_S.bits.smr34_nscfg_en                  =  pEncPara->comn2_smr34_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR34_S.bits.smr34_nscfg                     =  pEncPara->comn2_smr34_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR35_S.bits.smr35_offset_addr_s             =  pEncPara->comn2_smr35_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR35_S.bits.smr35_nscfg_en                  =  pEncPara->comn2_smr35_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR35_S.bits.smr35_nscfg                     =  pEncPara->comn2_smr35_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR36_S.bits.smr36_offset_addr_s             =  pEncPara->comn2_smr36_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR36_S.bits.smr36_nscfg_en                  =  pEncPara->comn2_smr36_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR36_S.bits.smr36_nscfg                     =  pEncPara->comn2_smr36_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR37_S.bits.smr37_offset_addr_s             =  pEncPara->comn2_smr37_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR37_S.bits.smr37_nscfg_en                  =  pEncPara->comn2_smr37_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR37_S.bits.smr37_nscfg                     =  pEncPara->comn2_smr37_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR38_S.bits.smr38_offset_addr_s             =  pEncPara->comn2_smr38_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR38_S.bits.smr38_nscfg_en                  =  pEncPara->comn2_smr38_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR38_S.bits.smr38_nscfg                     =  pEncPara->comn2_smr38_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR39_S.bits.smr39_offset_addr_s             =  pEncPara->comn2_smr39_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR39_S.bits.smr39_nscfg_en                  =  pEncPara->comn2_smr39_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR39_S.bits.smr39_nscfg                     =  pEncPara->comn2_smr39_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR40_S.bits.smr40_offset_addr_s             =  pEncPara->comn2_smr40_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR40_S.bits.smr40_nscfg_en                  =  pEncPara->comn2_smr40_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR40_S.bits.smr40_nscfg                     =  pEncPara->comn2_smr40_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR41_S.bits.smr41_offset_addr_s             =  pEncPara->comn2_smr41_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR41_S.bits.smr41_nscfg_en                  =  pEncPara->comn2_smr41_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR41_S.bits.smr41_nscfg                     =  pEncPara->comn2_smr41_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR42_S.bits.smr42_offset_addr_s             =  pEncPara->comn2_smr42_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR42_S.bits.smr42_nscfg_en                  =  pEncPara->comn2_smr42_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR42_S.bits.smr42_nscfg                     =  pEncPara->comn2_smr42_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR43_S.bits.smr43_offset_addr_s             =  pEncPara->comn2_smr43_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR43_S.bits.smr43_nscfg_en                  =  pEncPara->comn2_smr43_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR43_S.bits.smr43_nscfg                     =  pEncPara->comn2_smr43_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR44_S.bits.smr44_offset_addr_s             =  pEncPara->comn2_smr44_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR44_S.bits.smr44_nscfg_en                  =  pEncPara->comn2_smr44_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR44_S.bits.smr44_nscfg                     =  pEncPara->comn2_smr44_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR45_S.bits.smr45_offset_addr_s             =  pEncPara->comn2_smr45_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR45_S.bits.smr45_nscfg_en                  =  pEncPara->comn2_smr45_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR45_S.bits.smr45_nscfg                     =  pEncPara->comn2_smr45_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR46_S.bits.smr46_offset_addr_s             =  pEncPara->comn2_smr46_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR46_S.bits.smr46_nscfg_en                  =  pEncPara->comn2_smr46_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR46_S.bits.smr46_nscfg                     =  pEncPara->comn2_smr46_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR47_S.bits.smr47_offset_addr_s             =  pEncPara->comn2_smr47_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR47_S.bits.smr47_nscfg_en                  =  pEncPara->comn2_smr47_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR47_S.bits.smr47_nscfg                     =  pEncPara->comn2_smr47_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR48_S.bits.smr48_offset_addr_s             =  pEncPara->comn2_smr48_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR48_S.bits.smr48_nscfg_en                  =  pEncPara->comn2_smr48_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR48_S.bits.smr48_nscfg                     =  pEncPara->comn2_smr48_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR49_S.bits.smr49_offset_addr_s             =  pEncPara->comn2_smr49_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR49_S.bits.smr49_nscfg_en                  =  pEncPara->comn2_smr49_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR49_S.bits.smr49_nscfg                     =  pEncPara->comn2_smr49_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR50_S.bits.smr50_offset_addr_s             =  pEncPara->comn2_smr50_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR50_S.bits.smr50_nscfg_en                  =  pEncPara->comn2_smr50_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR50_S.bits.smr50_nscfg                     =  pEncPara->comn2_smr50_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR51_S.bits.smr51_offset_addr_s             =  pEncPara->comn2_smr51_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR51_S.bits.smr51_nscfg_en                  =  pEncPara->comn2_smr51_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR51_S.bits.smr51_nscfg                     =  pEncPara->comn2_smr51_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR52_S.bits.smr52_offset_addr_s             =  pEncPara->comn2_smr52_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR52_S.bits.smr52_nscfg_en                  =  pEncPara->comn2_smr52_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR52_S.bits.smr52_nscfg                     =  pEncPara->comn2_smr52_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR53_S.bits.smr53_offset_addr_s             =  pEncPara->comn2_smr53_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR53_S.bits.smr53_nscfg_en                  =  pEncPara->comn2_smr53_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR53_S.bits.smr53_nscfg                     =  pEncPara->comn2_smr53_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR54_S.bits.smr54_offset_addr_s             =  pEncPara->comn2_smr54_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR54_S.bits.smr54_nscfg_en                  =  pEncPara->comn2_smr54_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR54_S.bits.smr54_nscfg                     =  pEncPara->comn2_smr54_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR55_S.bits.smr55_offset_addr_s             =  pEncPara->comn2_smr55_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR55_S.bits.smr55_nscfg_en                  =  pEncPara->comn2_smr55_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR55_S.bits.smr55_nscfg                     =  pEncPara->comn2_smr55_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR56_S.bits.smr56_offset_addr_s             =  pEncPara->comn2_smr56_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR56_S.bits.smr56_nscfg_en                  =  pEncPara->comn2_smr56_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR56_S.bits.smr56_nscfg                     =  pEncPara->comn2_smr56_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR57_S.bits.smr57_offset_addr_s             =  pEncPara->comn2_smr57_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR57_S.bits.smr57_nscfg_en                  =  pEncPara->comn2_smr57_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR57_S.bits.smr57_nscfg                     =  pEncPara->comn2_smr57_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR58_S.bits.smr58_offset_addr_s             =  pEncPara->comn2_smr58_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR58_S.bits.smr58_nscfg_en                  =  pEncPara->comn2_smr58_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR58_S.bits.smr58_nscfg                     =  pEncPara->comn2_smr58_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR59_S.bits.smr59_offset_addr_s             =  pEncPara->comn2_smr59_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR59_S.bits.smr59_nscfg_en                  =  pEncPara->comn2_smr59_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR59_S.bits.smr59_nscfg                     =  pEncPara->comn2_smr59_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR60_S.bits.smr60_offset_addr_s             =  pEncPara->comn2_smr60_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR60_S.bits.smr60_nscfg_en                  =  pEncPara->comn2_smr60_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR60_S.bits.smr60_nscfg                     =  pEncPara->comn2_smr60_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR61_S.bits.smr61_offset_addr_s             =  pEncPara->comn2_smr61_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR61_S.bits.smr61_nscfg_en                  =  pEncPara->comn2_smr61_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR61_S.bits.smr61_nscfg                     =  pEncPara->comn2_smr61_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR62_S.bits.smr62_offset_addr_s             =  pEncPara->comn2_smr62_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR62_S.bits.smr62_nscfg_en                  =  pEncPara->comn2_smr62_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR62_S.bits.smr62_nscfg                     =  pEncPara->comn2_smr62_nscfg        ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR63_S.bits.smr63_offset_addr_s             =  pEncPara->comn2_smr63_offset_addr_s;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR63_S.bits.smr63_nscfg_en                  =  pEncPara->comn2_smr63_nscfg_en     ;
      pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR63_S.bits.smr63_nscfg                     =  pEncPara->comn2_smr63_nscfg        ;

    /* mmu com3ÅäÖÃ */
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR64_S.bits.smr64_offset_addr_s             = pEncPara->comn3_smr64_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR64_S.bits.smr64_nscfg_en                  = pEncPara->comn3_smr64_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR64_S.bits.smr64_nscfg                     = pEncPara->comn3_smr64_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR65_S.bits.smr65_offset_addr_s             = pEncPara->comn3_smr65_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR65_S.bits.smr65_nscfg_en                  = pEncPara->comn3_smr65_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR65_S.bits.smr65_nscfg                     = pEncPara->comn3_smr65_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR66_S.bits.smr66_offset_addr_s             = pEncPara->comn3_smr66_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR66_S.bits.smr66_nscfg_en                  = pEncPara->comn3_smr66_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR66_S.bits.smr66_nscfg                     = pEncPara->comn3_smr66_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR67_S.bits.smr67_offset_addr_s             = pEncPara->comn3_smr67_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR67_S.bits.smr67_nscfg_en                  = pEncPara->comn3_smr67_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR67_S.bits.smr67_nscfg                     = pEncPara->comn3_smr67_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR68_S.bits.smr68_offset_addr_s             = pEncPara->comn3_smr68_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR68_S.bits.smr68_nscfg_en                  = pEncPara->comn3_smr68_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR68_S.bits.smr68_nscfg                     = pEncPara->comn3_smr68_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR69_S.bits.smr69_offset_addr_s             = pEncPara->comn3_smr69_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR69_S.bits.smr69_nscfg_en                  = pEncPara->comn3_smr69_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR69_S.bits.smr69_nscfg                     = pEncPara->comn3_smr69_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR70_S.bits.smr70_offset_addr_s             = pEncPara->comn3_smr70_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR70_S.bits.smr70_nscfg_en                  = pEncPara->comn3_smr70_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR70_S.bits.smr70_nscfg                     = pEncPara->comn3_smr70_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR71_S.bits.smr71_offset_addr_s             = pEncPara->comn3_smr71_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR71_S.bits.smr71_nscfg_en                  = pEncPara->comn3_smr71_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR71_S.bits.smr71_nscfg                     = pEncPara->comn3_smr71_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR72_S.bits.smr72_offset_addr_s             = pEncPara->comn3_smr72_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR72_S.bits.smr72_nscfg_en                  = pEncPara->comn3_smr72_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR72_S.bits.smr72_nscfg                     = pEncPara->comn3_smr72_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR73_S.bits.smr73_offset_addr_s             = pEncPara->comn3_smr73_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR73_S.bits.smr73_nscfg_en                  = pEncPara->comn3_smr73_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR73_S.bits.smr73_nscfg                     = pEncPara->comn3_smr73_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR74_S.bits.smr74_offset_addr_s             = pEncPara->comn3_smr74_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR74_S.bits.smr74_nscfg_en                  = pEncPara->comn3_smr74_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR74_S.bits.smr74_nscfg                     = pEncPara->comn3_smr74_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR75_S.bits.smr75_offset_addr_s             = pEncPara->comn3_smr75_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR75_S.bits.smr75_nscfg_en                  = pEncPara->comn3_smr75_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR75_S.bits.smr75_nscfg                     = pEncPara->comn3_smr75_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR76_S.bits.smr76_offset_addr_s             = pEncPara->comn3_smr76_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR76_S.bits.smr76_nscfg_en                  = pEncPara->comn3_smr76_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR76_S.bits.smr76_nscfg                     = pEncPara->comn3_smr76_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR77_S.bits.smr77_offset_addr_s             = pEncPara->comn3_smr77_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR77_S.bits.smr77_nscfg_en                  = pEncPara->comn3_smr77_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR77_S.bits.smr77_nscfg                     = pEncPara->comn3_smr77_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR78_S.bits.smr78_offset_addr_s             = pEncPara->comn3_smr78_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR78_S.bits.smr78_nscfg_en                  = pEncPara->comn3_smr78_nscfg_en     ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR78_S.bits.smr78_nscfg                     = pEncPara->comn3_smr78_nscfg        ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR79_S.bits.smr79_offset_addr_s             = pEncPara->comn3_smr79_offset_addr_s;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR79_S.bits.smr79_nscfg_en                  = pEncPara->comn3_smr79_nscfg_en      ;
      pAllReg->VEDU_COMN3_REGS.COMN2_SMMU_SMR79_S.bits.smr79_nscfg                     = pEncPara->comn3_smr79_nscfg         ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_RLD_EN0_S                                    = pEncPara->comn3_smr_rld_en0_s       ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_RLD_EN1_S                                    = pEncPara->comn3_smr_rld_en1_s       ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_RLD_EN2_S.bits.smr_rld_en2_s                 = pEncPara->comn3_smr_rld_en2_s       ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ptw_ns_msk                = pEncPara->comn3_ints_ptw_ns_msk     ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ptw_invalid_msk           = pEncPara->comn3_ints_ptw_invalid_msk;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ptw_trans_msk             = pEncPara->comn3_ints_ptw_trans_msk  ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_tlbmiss_msk               = pEncPara->comn3_ints_tlbmiss_msk    ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ext_msk                   = pEncPara->comn3_ints_ext_msk        ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_permis_msk                = pEncPara->comn3_ints_permis_msk     ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTCLR_S.bits.ints_ptw_ns_clr                = pEncPara->comn3_ints_ptw_ns_clr     ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTCLR_S.bits.ints_ptw_invalid_clr           = pEncPara->comn3_ints_ptw_invalid_clr;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTCLR_S.bits.ints_ptw_trans_clr             = pEncPara->comn3_ints_ptw_trans_clr  ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTCLR_S.bits.ints_tlbmiss_clr               = pEncPara->comn3_ints_tlbmiss_clr    ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTCLR_S.bits.ints_ext_clr                   = pEncPara->comn3_ints_ext_clr        ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTCLR_S.bits.ints_permis_clr                = pEncPara->comn3_ints_permis_clr     ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_SCR_S.bits.glb_nscfg                         = pEncPara->comn3_glb_nscfg           ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_SCB_SCTRL.bits.scb_bypass                    = pEncPara->comn3_scb_bypass          ;
    //pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_SCB_TTBR =  phy_pgd_base;
	  pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_SCB_TTBCR.bits.scb_ttbcr_des                 = pEncPara->comn3_scb_ttbcr_des       ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_OFFSET_ADDR_S.bits.offset_addr_s             = pEncPara->comn3_offset_addr_s       ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_FAMA_CTRL0_S.bits.fama_bps_msb_s             = pEncPara->comn3_fama_bps_msb_s      ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_FAMA_CTRL0_S.bits.fama_chn_sel_s             = pEncPara->comn3_fama_chn_sel_s      ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_FAMA_CTRL0_S.bits.fama_sdes_msb_s            = pEncPara->comn3_fama_sdes_msb_s     ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_FAMA_CTRL1_S.bits.fama_ptw_msb_s             = pEncPara->comn3_fama_ptw_msb_s      ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_DBGRPTR_TLB_S.bits.dbg_tlb_en                = pEncPara->comn3_dbg_tlb_en          ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_DBGRPTR_CACHE_S.bits.dbg_cache_en            = pEncPara->comn3_dbg_cache_en        ;
      pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_OVERRIDE_CTRL_S.bits.override_va_security    = pEncPara->comn3_override_va_security;
#endif
    //mmu 0x20643e00
    /* MMUµÄ¼Ä´æÆ÷ÔÚ±àÂëÆ÷³õÊ¼»¯µÄÊ±ºòVENC_HAL_ConfigMMUÖÐÅäÖÃ */
   //mmu0 0x20643e00
      pAllReg->VEDU_MMU0_REGS.MST_GLB_SCR.bits.glb_scr = pEncPara->glb_scr;
      pAllReg->VEDU_MMU0_REGS.MST_GLB_BYPASS.bits.glb_bypass = pEncPara->glb_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid0_bypass = pEncPara->sid0_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid1_bypass = pEncPara->sid1_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid2_bypass = pEncPara->sid2_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid3_bypass = pEncPara->sid3_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid4_bypass = pEncPara->sid4_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid5_bypass = pEncPara->sid5_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid6_bypass = pEncPara->sid6_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid7_bypass = pEncPara->sid7_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid8_bypass = pEncPara->sid8_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid9_bypass = pEncPara->sid9_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid10_bypass = pEncPara->sid10_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid11_bypass = pEncPara->sid11_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid12_bypass = pEncPara->sid12_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid13_bypass = pEncPara->sid13_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid14_bypass = pEncPara->sid14_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid15_bypass = pEncPara->sid15_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid16_bypass = pEncPara->sid16_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid17_bypass = pEncPara->sid17_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid18_bypass = pEncPara->sid18_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid19_bypass = pEncPara->sid19_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid20_bypass = pEncPara->sid20_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid21_bypass = pEncPara->sid21_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid22_bypass = pEncPara->sid22_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid23_bypass = pEncPara->sid23_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid24_bypass = pEncPara->sid24_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid25_bypass = pEncPara->sid25_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid26_bypass = pEncPara->sid26_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid27_bypass = pEncPara->sid27_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid28_bypass = pEncPara->sid28_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid29_bypass = pEncPara->sid29_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid30_bypass = pEncPara->sid30_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID0_BYPASS.bits.sid31_bypass = pEncPara->sid31_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID1_BYPASS.bits.sid32_bypass = pEncPara->sid32_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID1_BYPASS.bits.sid33_bypass = pEncPara->sid33_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID1_BYPASS.bits.sid34_bypass = pEncPara->sid34_bypass;
      pAllReg->VEDU_MMU0_REGS.MST_SID1_BYPASS.bits.sid35_bypass = pEncPara->sid35_bypass;
#if 0
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_0chn  = pEncPara->mst_pref_0chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_1chn  = pEncPara->mst_pref_1chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_2chn  = pEncPara->mst_pref_2chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_3chn  = pEncPara->mst_pref_3chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_4chn  = pEncPara->mst_pref_4chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_5chn  = pEncPara->mst_pref_5chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_6chn  = pEncPara->mst_pref_6chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_7chn  = pEncPara->mst_pref_7chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_8chn  = pEncPara->mst_pref_8chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_9chn  = pEncPara->mst_pref_9chn ;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_10chn = pEncPara->mst_pref_10chn;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_11chn = pEncPara->mst_pref_11chn;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_12chn = pEncPara->mst_pref_12chn;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_13chn = pEncPara->mst_pref_13chn;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_14chn = pEncPara->mst_pref_14chn;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_15chn = pEncPara->mst_pref_15chn;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_16chn = pEncPara->mst_pref_16chn;
      pAllReg->VEDU_MMU0_REGS.MST_PREF_CHN.bits.mst_pref_17chn = pEncPara->mst_pref_17chn;


      pAllReg->VEDU_MMU0_REGS.MST_RD0_0CFG.bits.rd0_tlb_depth   = pEncPara->rd0_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_RD0_0CFG.bits.rd0_tlb_base    = pEncPara->rd0_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_RD0_0CFG.bits.rd0_tlb_last    = pEncPara->rd0_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_RD0_1CFG.bits.rd0_tlb_nxt     = pEncPara->rd0_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_RD0_1CFG.bits.rd0_tlb_uw      = pEncPara->rd0_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_RD0_1CFG.bits.rd0_tlb_upd_dis = pEncPara->rd0_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD0_1CFG.bits.rd0_tlb_upd_len = pEncPara->rd0_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_RD1_0CFG.bits.rd1_tlb_depth   = pEncPara->rd1_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_RD1_0CFG.bits.rd1_tlb_base    = pEncPara->rd1_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_RD1_0CFG.bits.rd1_tlb_last    = pEncPara->rd1_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_RD1_1CFG.bits.rd1_tlb_nxt     = pEncPara->rd1_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_RD1_1CFG.bits.rd1_tlb_uw      = pEncPara->rd1_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_RD1_1CFG.bits.rd1_tlb_upd_dis = pEncPara->rd1_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD1_1CFG.bits.rd1_tlb_upd_len = pEncPara->rd1_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_RD2_0CFG.bits.rd2_tlb_depth   = pEncPara->rd2_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_RD2_0CFG.bits.rd2_tlb_base    = pEncPara->rd2_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_RD2_0CFG.bits.rd2_tlb_last    = pEncPara->rd2_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_RD2_1CFG.bits.rd2_tlb_nxt     = pEncPara->rd2_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_RD2_1CFG.bits.rd2_tlb_uw      = pEncPara->rd2_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_RD2_1CFG.bits.rd2_tlb_upd_dis = pEncPara->rd2_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD2_1CFG.bits.rd2_tlb_upd_len = pEncPara->rd2_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_RD3_0CFG.bits.rd3_tlb_depth   = pEncPara->rd3_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_RD3_0CFG.bits.rd3_tlb_base    = pEncPara->rd3_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_RD3_0CFG.bits.rd3_tlb_last    = pEncPara->rd3_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_RD3_1CFG.bits.rd3_tlb_nxt     = pEncPara->rd3_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_RD3_1CFG.bits.rd3_tlb_uw      = pEncPara->rd3_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_RD3_1CFG.bits.rd3_tlb_upd_dis = pEncPara->rd3_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD3_1CFG.bits.rd3_tlb_upd_len = pEncPara->rd3_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_RD4_0CFG.bits.rd4_tlb_depth   = pEncPara->rd4_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_RD4_0CFG.bits.rd4_tlb_base    = pEncPara->rd4_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_RD4_0CFG.bits.rd4_tlb_last    = pEncPara->rd4_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_RD4_1CFG.bits.rd4_tlb_nxt     = pEncPara->rd4_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_RD4_1CFG.bits.rd4_tlb_uw      = pEncPara->rd4_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_RD4_1CFG.bits.rd4_tlb_upd_dis = pEncPara->rd4_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD4_1CFG.bits.rd4_tlb_upd_len = pEncPara->rd4_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_RD5_0CFG.bits.rd5_tlb_depth   = pEncPara->rd5_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_RD5_0CFG.bits.rd5_tlb_base    = pEncPara->rd5_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_RD5_0CFG.bits.rd5_tlb_last    = pEncPara->rd5_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_RD5_1CFG.bits.rd5_tlb_nxt     = pEncPara->rd5_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_RD5_1CFG.bits.rd5_tlb_uw      = pEncPara->rd5_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_RD5_1CFG.bits.rd5_tlb_upd_dis = pEncPara->rd5_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD5_1CFG.bits.rd5_tlb_upd_len = pEncPara->rd5_tlb_upd_len;
#endif


#if 1	//²»Í¬ÓÚÄ¬ÈÏÖµµÄÅäÖÃ
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SCR.bits.ptw_pf                        =  pEncPara->comn0_ptw_pf;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ptw_ns_msk       =  pEncPara->comn0_intns_ptw_ns_msk;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ptw_invalid_msk  =  pEncPara->comn0_intns_ptw_invalid_msk;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ptw_trans_msk    =  pEncPara->comn0_intns_ptw_trans_msk;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_tlbmiss_msk      =  pEncPara->comn0_intns_tlbmiss_msk;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_ext_msk          =  pEncPara->comn0_intns_ext_msk;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_INTMASK_NS.bits.intns_permis_msk       =  pEncPara->comn0_intns_permis_msk;
    pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR0_NS.bits.smr0_ptw_qos              =  pEncPara->comn0_smr0_ptw_qos;

    pAllReg->VEDU_COMN1_REGS.COMN1_SMMU_CB_TTBCR.bits.cb_ttbcr_des   =  1;

    if (pEncPara_channel->bSecureFlag)
    {
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR0_S.bits.smr0_nscfg   =  pEncPara->comn2_smr0_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR1_S.bits.smr1_nscfg   =  pEncPara->comn2_smr1_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR2_S.bits.smr2_nscfg   =  pEncPara->comn2_smr2_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR3_S.bits.smr3_nscfg   =  pEncPara->comn2_smr3_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR4_S.bits.smr4_nscfg   =  pEncPara->comn2_smr4_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR5_S.bits.smr5_nscfg   =  pEncPara->comn2_smr5_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR6_S.bits.smr6_nscfg   =  pEncPara->comn2_smr6_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR7_S.bits.smr7_nscfg   =  pEncPara->comn2_smr7_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR8_S.bits.smr8_nscfg   =  pEncPara->comn2_smr8_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR9_S.bits.smr9_nscfg   =  pEncPara->comn2_smr9_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR10_S.bits.smr10_nscfg =  pEncPara->comn2_smr10_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR11_S.bits.smr11_nscfg =  pEncPara->comn2_smr11_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR12_S.bits.smr12_nscfg =  pEncPara->comn2_smr12_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR13_S.bits.smr13_nscfg =  pEncPara->comn2_smr13_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR14_S.bits.smr14_nscfg =  pEncPara->comn2_smr14_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR15_S.bits.smr15_nscfg =  pEncPara->comn2_smr15_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR16_S.bits.smr16_nscfg =  pEncPara->comn2_smr16_nscfg;
        pAllReg->VEDU_COMN2_REGS.COMN2_SMMU_SMR17_S.bits.smr17_nscfg =  pEncPara->comn2_smr17_nscfg;

        pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ptw_ns_msk      = pEncPara->comn3_ints_ptw_ns_msk;
        pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ptw_invalid_msk = pEncPara->comn3_ints_ptw_invalid_msk;
        pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ptw_trans_msk   = pEncPara->comn3_ints_ptw_trans_msk;
        pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_tlbmiss_msk     = pEncPara->comn3_ints_tlbmiss_msk;
        pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_ext_msk         = pEncPara->comn3_ints_ext_msk;
        pAllReg->VEDU_COMN3_REGS.COMN3_SMMU_INTMAS_S.bits.ints_permis_msk      = pEncPara->comn3_ints_permis_msk;
	}

     // smr 0 - 35
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR0_NS.bits.smr0_ptw_qos    =  pEncPara->comn0_smr0_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR0_NS.bits.smr0_bypass     =  pEncPara->comn0_smr0_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR1_NS.bits.smr1_ptw_qos    =  pEncPara->comn0_smr1_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR1_NS.bits.smr1_bypass     =  pEncPara->comn0_smr1_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR2_NS.bits.smr2_ptw_qos    =  pEncPara->comn0_smr2_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR2_NS.bits.smr2_bypass     =  pEncPara->comn0_smr2_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR3_NS.bits.smr3_ptw_qos    =  pEncPara->comn0_smr3_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR3_NS.bits.smr3_bypass     =  pEncPara->comn0_smr3_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR4_NS.bits.smr4_ptw_qos    =  pEncPara->comn0_smr4_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR4_NS.bits.smr4_bypass     =  pEncPara->comn0_smr4_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR5_NS.bits.smr5_ptw_qos    =  pEncPara->comn0_smr5_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR5_NS.bits.smr5_bypass     =  pEncPara->comn0_smr5_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR6_NS.bits.smr6_ptw_qos    =  pEncPara->comn0_smr6_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR6_NS.bits.smr6_bypass     =  pEncPara->comn0_smr6_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR7_NS.bits.smr7_ptw_qos    =  pEncPara->comn0_smr7_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR7_NS.bits.smr7_bypass     =  pEncPara->comn0_smr7_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR8_NS.bits.smr8_ptw_qos    =  pEncPara->comn0_smr8_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR8_NS.bits.smr8_bypass     =  pEncPara->comn0_smr8_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR9_NS.bits.smr9_ptw_qos    =  pEncPara->comn0_smr9_ptw_qos ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR9_NS.bits.smr9_bypass     =  pEncPara->comn0_smr9_bypass  ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR10_NS.bits.smr10_ptw_qos  =  pEncPara->comn0_smr10_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR10_NS.bits.smr10_bypass   =  pEncPara->comn0_smr10_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR11_NS.bits.smr11_ptw_qos  =  pEncPara->comn0_smr11_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR11_NS.bits.smr11_bypass   =  pEncPara->comn0_smr11_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR12_NS.bits.smr12_ptw_qos  =  pEncPara->comn0_smr12_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR12_NS.bits.smr12_bypass   =  pEncPara->comn0_smr12_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR13_NS.bits.smr13_ptw_qos  =  pEncPara->comn0_smr13_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR13_NS.bits.smr13_bypass   =  pEncPara->comn0_smr13_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR14_NS.bits.smr14_ptw_qos  =  pEncPara->comn0_smr14_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR14_NS.bits.smr14_bypass   =  pEncPara->comn0_smr14_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR15_NS.bits.smr15_ptw_qos  =  pEncPara->comn0_smr15_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR15_NS.bits.smr15_bypass   =  pEncPara->comn0_smr15_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR16_NS.bits.smr16_ptw_qos  =  pEncPara->comn0_smr16_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR16_NS.bits.smr16_bypass   =  pEncPara->comn0_smr16_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR17_NS.bits.smr17_ptw_qos  =  pEncPara->comn0_smr17_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR17_NS.bits.smr17_bypass   =  pEncPara->comn0_smr17_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR18_NS.bits.smr18_ptw_qos  =  pEncPara->comn0_smr18_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR18_NS.bits.smr18_bypass   =  pEncPara->comn0_smr18_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR19_NS.bits.smr19_ptw_qos  =  pEncPara->comn0_smr19_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR19_NS.bits.smr19_bypass   =  pEncPara->comn0_smr19_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR20_NS.bits.smr20_ptw_qos  =  pEncPara->comn0_smr20_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR20_NS.bits.smr20_bypass   =  pEncPara->comn0_smr20_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR21_NS.bits.smr21_ptw_qos  =  pEncPara->comn0_smr21_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR21_NS.bits.smr21_bypass   =  pEncPara->comn0_smr21_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR22_NS.bits.smr22_ptw_qos  =  pEncPara->comn0_smr22_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR22_NS.bits.smr22_bypass   =  pEncPara->comn0_smr22_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR23_NS.bits.smr23_ptw_qos  =  pEncPara->comn0_smr23_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR23_NS.bits.smr23_bypass   =  pEncPara->comn0_smr23_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR24_NS.bits.smr24_ptw_qos  =  pEncPara->comn0_smr24_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR24_NS.bits.smr24_bypass   =  pEncPara->comn0_smr24_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR25_NS.bits.smr25_ptw_qos  =  pEncPara->comn0_smr25_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR25_NS.bits.smr25_bypass   =  pEncPara->comn0_smr25_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR26_NS.bits.smr26_ptw_qos  =  pEncPara->comn0_smr26_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR26_NS.bits.smr26_bypass   =  pEncPara->comn0_smr26_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR27_NS.bits.smr27_ptw_qos  =  pEncPara->comn0_smr27_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR27_NS.bits.smr27_bypass   =  pEncPara->comn0_smr27_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR28_NS.bits.smr28_ptw_qos  =  pEncPara->comn0_smr28_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR28_NS.bits.smr28_bypass   =  pEncPara->comn0_smr28_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR29_NS.bits.smr29_ptw_qos  =  pEncPara->comn0_smr29_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR29_NS.bits.smr29_bypass   =  pEncPara->comn0_smr29_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR30_NS.bits.smr30_ptw_qos  =  pEncPara->comn0_smr30_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR30_NS.bits.smr30_bypass   =  pEncPara->comn0_smr30_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR31_NS.bits.smr31_ptw_qos  =  pEncPara->comn0_smr31_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR31_NS.bits.smr31_bypass   =  pEncPara->comn0_smr31_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR32_NS.bits.smr32_ptw_qos  =  pEncPara->comn0_smr32_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR32_NS.bits.smr32_bypass   =  pEncPara->comn0_smr32_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR33_NS.bits.smr33_ptw_qos  =  pEncPara->comn0_smr33_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR33_NS.bits.smr33_bypass   =  pEncPara->comn0_smr33_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR34_NS.bits.smr34_ptw_qos  =  pEncPara->comn0_smr34_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR34_NS.bits.smr34_bypass   =  pEncPara->comn0_smr34_bypass ;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR35_NS.bits.smr35_ptw_qos  =  pEncPara->comn0_smr35_ptw_qos;
     pAllReg->VEDU_COMN0_REGS.COMN0_SMMU_SMR35_NS.bits.smr35_bypass   =  pEncPara->comn0_smr35_bypass ;

#endif
    /* ARGBºÍPACKETÄ£Ê½ÐèÒªÌØÊâ´¦Àí  */
    if(( pEncPara->vcpi_str_fmt != 6) && ( pEncPara->vcpi_str_fmt != 8 ))
    {
        pAllReg->VEDU_MMU0_REGS.MST_RD6_0CFG.bits.rd6_tlb_depth   = 0x80;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_0CFG.bits.rd6_tlb_base    = 0x8e;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_0CFG.bits.rd6_tlb_last    = 0x10d;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_nxt     = 0x18;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_uw      = 0x28;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_upd_dis = 0x60;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_upd_len = 0x8;
    }
    else
    {
        pAllReg->VEDU_MMU0_REGS.MST_RD6_0CFG.bits.rd6_tlb_depth   = 0x100;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_0CFG.bits.rd6_tlb_base    = 0x8e;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_0CFG.bits.rd6_tlb_last    = 0x18d;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_nxt     = 0x40;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_uw      = 0x80;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_upd_dis = 0xa0;
        pAllReg->VEDU_MMU0_REGS.MST_RD6_1CFG.bits.rd6_tlb_upd_len = 0x20;
    }
#if 0
      pAllReg->VEDU_MMU0_REGS.MST_RD7_0CFG.bits.rd7_tlb_depth   = pEncPara->rd7_tlb_depth  ;
      pAllReg->VEDU_MMU0_REGS.MST_RD7_0CFG.bits.rd7_tlb_base    = pEncPara->rd7_tlb_base   ;
      pAllReg->VEDU_MMU0_REGS.MST_RD7_0CFG.bits.rd7_tlb_last    = pEncPara->rd7_tlb_last   ;
      pAllReg->VEDU_MMU0_REGS.MST_RD7_1CFG.bits.rd7_tlb_nxt     = pEncPara->rd7_tlb_nxt    ;
      pAllReg->VEDU_MMU0_REGS.MST_RD7_1CFG.bits.rd7_tlb_uw      = pEncPara->rd7_tlb_uw     ;
      pAllReg->VEDU_MMU0_REGS.MST_RD7_1CFG.bits.rd7_tlb_upd_dis = pEncPara->rd7_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD7_1CFG.bits.rd7_tlb_upd_len = pEncPara->rd7_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_RD8_0CFG.bits.rd8_tlb_depth   = pEncPara->rd8_tlb_depth ;
      pAllReg->VEDU_MMU0_REGS.MST_RD8_0CFG.bits.rd8_tlb_base    = pEncPara->rd8_tlb_base  ;
      pAllReg->VEDU_MMU0_REGS.MST_RD8_0CFG.bits.rd8_tlb_last    = pEncPara->rd8_tlb_last  ;
      pAllReg->VEDU_MMU0_REGS.MST_RD8_1CFG.bits.rd8_tlb_nxt     = pEncPara->rd8_tlb_nxt   ;
      pAllReg->VEDU_MMU0_REGS.MST_RD8_1CFG.bits.rd8_tlb_uw      = pEncPara->rd8_tlb_uw    ;
      pAllReg->VEDU_MMU0_REGS.MST_RD8_1CFG.bits.rd8_tlb_upd_dis = pEncPara->rd8_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD8_1CFG.bits.rd8_tlb_upd_len = pEncPara->rd8_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_RD9_0CFG.bits.rd9_tlb_depth   = pEncPara->rd9_tlb_depth ;
      pAllReg->VEDU_MMU0_REGS.MST_RD9_0CFG.bits.rd9_tlb_base    = pEncPara->rd9_tlb_base  ;
      pAllReg->VEDU_MMU0_REGS.MST_RD9_0CFG.bits.rd9_tlb_last    = pEncPara->rd9_tlb_last  ;
      pAllReg->VEDU_MMU0_REGS.MST_RD9_1CFG.bits.rd9_tlb_nxt     = pEncPara->rd9_tlb_nxt   ;
      pAllReg->VEDU_MMU0_REGS.MST_RD9_1CFG.bits.rd9_tlb_uw      = pEncPara->rd9_tlb_uw    ;
      pAllReg->VEDU_MMU0_REGS.MST_RD9_1CFG.bits.rd9_tlb_upd_dis = pEncPara->rd9_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_RD9_1CFG.bits.rd9_tlb_upd_len = pEncPara->rd9_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR0_0CFG.bits.wr0_tlb_depth   = pEncPara->wr0_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR0_0CFG.bits.wr0_tlb_base    = pEncPara->wr0_tlb_base ;
      pAllReg->VEDU_MMU0_REGS.MST_WR0_0CFG.bits.wr0_tlb_last    = pEncPara->wr0_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR0_1CFG.bits.wr0_tlb_nxt     = pEncPara->wr0_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR0_1CFG.bits.wr0_tlb_uw      = pEncPara->wr0_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR0_1CFG.bits.wr0_tlb_upd_dis = pEncPara->wr0_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR0_1CFG.bits.wr0_tlb_upd_len = pEncPara->wr0_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR1_0CFG.bits.wr1_tlb_depth   = pEncPara->wr1_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR1_0CFG.bits.wr1_tlb_base    = pEncPara->wr1_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_WR1_0CFG.bits.wr1_tlb_last    = pEncPara->wr1_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR1_1CFG.bits.wr1_tlb_nxt     = pEncPara->wr1_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR1_1CFG.bits.wr1_tlb_uw      = pEncPara->wr1_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR1_1CFG.bits.wr1_tlb_upd_dis = pEncPara->wr1_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR1_1CFG.bits.wr1_tlb_upd_len = pEncPara->wr1_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR2_0CFG.bits.wr2_tlb_depth   = pEncPara->wr2_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR2_0CFG.bits.wr2_tlb_base    = pEncPara->wr2_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_WR2_0CFG.bits.wr2_tlb_last    = pEncPara->wr2_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR2_1CFG.bits.wr2_tlb_nxt     = pEncPara->wr2_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR2_1CFG.bits.wr2_tlb_uw      = pEncPara->wr2_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR2_1CFG.bits.wr2_tlb_upd_dis = pEncPara->wr2_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR2_1CFG.bits.wr2_tlb_upd_len = pEncPara->wr2_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR3_0CFG.bits.wr3_tlb_depth   = pEncPara->wr3_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR3_0CFG.bits.wr3_tlb_base    = pEncPara->wr3_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_WR3_0CFG.bits.wr3_tlb_last    = pEncPara->wr3_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR3_1CFG.bits.wr3_tlb_nxt     = pEncPara->wr3_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR3_1CFG.bits.wr3_tlb_uw      = pEncPara->wr3_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR3_1CFG.bits.wr3_tlb_upd_dis = pEncPara->wr3_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR3_1CFG.bits.wr3_tlb_upd_len = pEncPara->wr3_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR4_0CFG.bits.wr4_tlb_depth   = pEncPara->wr4_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR4_0CFG.bits.wr4_tlb_base    = pEncPara->wr4_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_WR4_0CFG.bits.wr4_tlb_last    = pEncPara->wr4_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR4_1CFG.bits.wr4_tlb_nxt     = pEncPara->wr4_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR4_1CFG.bits.wr4_tlb_uw      = pEncPara->wr4_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR4_1CFG.bits.wr4_tlb_upd_dis = pEncPara->wr4_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR4_1CFG.bits.wr4_tlb_upd_len = pEncPara->wr4_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR5_0CFG.bits.wr5_tlb_depth   = pEncPara->wr5_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR5_0CFG.bits.wr5_tlb_base    = pEncPara->wr5_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_WR5_0CFG.bits.wr5_tlb_last    = pEncPara->wr5_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR5_1CFG.bits.wr5_tlb_nxt     = pEncPara->wr5_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR5_1CFG.bits.wr5_tlb_uw      = pEncPara->wr5_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR5_1CFG.bits.wr5_tlb_upd_dis = pEncPara->wr5_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR5_1CFG.bits.wr5_tlb_upd_len = pEncPara->wr5_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR6_0CFG.bits.wr6_tlb_depth   = pEncPara->wr6_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR6_0CFG.bits.wr6_tlb_base    = pEncPara->wr6_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_WR6_0CFG.bits.wr6_tlb_last    = pEncPara->wr6_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR6_1CFG.bits.wr6_tlb_nxt     = pEncPara->wr6_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR6_1CFG.bits.wr6_tlb_uw      = pEncPara->wr6_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR6_1CFG.bits.wr6_tlb_upd_dis = pEncPara->wr6_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR6_1CFG.bits.wr6_tlb_upd_len = pEncPara->wr6_tlb_upd_len;

      pAllReg->VEDU_MMU0_REGS.MST_WR7_0CFG.bits.wr7_tlb_depth   = pEncPara->wr7_tlb_depth;
      pAllReg->VEDU_MMU0_REGS.MST_WR7_0CFG.bits.wr7_tlb_base    = pEncPara->wr7_tlb_base;
      pAllReg->VEDU_MMU0_REGS.MST_WR7_0CFG.bits.wr7_tlb_last    = pEncPara->wr7_tlb_last;
      pAllReg->VEDU_MMU0_REGS.MST_WR7_1CFG.bits.wr7_tlb_nxt     = pEncPara->wr7_tlb_nxt;
      pAllReg->VEDU_MMU0_REGS.MST_WR7_1CFG.bits.wr7_tlb_uw      = pEncPara->wr7_tlb_uw;
      pAllReg->VEDU_MMU0_REGS.MST_WR7_1CFG.bits.wr7_tlb_upd_dis = pEncPara->wr7_tlb_upd_dis;
      pAllReg->VEDU_MMU0_REGS.MST_WR7_1CFG.bits.wr7_tlb_upd_len = pEncPara->wr7_tlb_upd_len;
#endif

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_MODE_MMU.bits.vcpi_protocol = pEncPara->vcpi_protocol;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_MODE_MMU.bits.vcpi_str_fmt = pEncPara_channel->vcpi_str_fmt;
    HI_DBG_VENC("pEncPara_channel->iSliceSplitNum:%d\n",pEncPara_channel->iSliceSplitNum);

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVST_ADDR_STR = pEncPara_channel->VEDU_NBI_MVST_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVST_ADDR_END = pEncPara_channel->VEDU_NBI_MVST_ADDR + pEncPara_channel->VEDU_NBI_MVST_Length - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVLD_ADDR_STR = pEncPara_channel->VEDU_NBI_MVLD_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVLD_ADDR_END = pEncPara_channel->VEDU_NBI_MVLD_ADDR + pEncPara_channel->VEDU_NBI_MVLD_Length - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMEST_ADDR_STR = pEncPara_channel->VEDU_PMEST_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMEST_ADDR_END = pEncPara_channel->VEDU_PMEST_ADDR + pEncPara_channel->VEDU_PMEST_Length - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMELD_ADDR_STR = pEncPara_channel->VEDU_PMELD_ADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMELD_ADDR_END = pEncPara_channel->VEDU_PMELD_ADDR + pEncPara_channel->VEDU_PMELD_Length - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YH_ADDR_STR = pEncPara_channel->RcnYHeadAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YH_ADDR_END = pEncPara_channel->RcnYHeadAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYHeadLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CH_ADDR_STR = pEncPara_channel->RcnCHeadAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CH_ADDR_END = pEncPara_channel->RcnCHeadAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnCHeadLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YADDR_STR = pEncPara_channel->RcnYAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YADDR_END = pEncPara_channel->RcnYAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CADDR_STR = pEncPara_channel->RcnCAddr[pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CADDR_END = pEncPara_channel->RcnCAddr[pEncPara_channel->RcnIdx] + pEncPara_channel->RcnCLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YH_ADDR_STR = pEncPara_channel->RcnYHeadAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YH_ADDR_END = pEncPara_channel->RcnYHeadAddr[!pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYHeadLength - 1;

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CH_ADDR_STR = pEncPara_channel->RcnCHeadAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CH_ADDR_END = pEncPara_channel->RcnCHeadAddr[!pEncPara_channel->RcnIdx]+ pEncPara_channel->RcnCHeadLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YADDR_STR = pEncPara_channel->RcnYAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YADDR_END = pEncPara_channel->RcnYAddr[!pEncPara_channel->RcnIdx] + pEncPara_channel->RcnYLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CADDR_STR = pEncPara_channel->RcnCAddr[!pEncPara_channel->RcnIdx];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CADDR_END = pEncPara_channel->RcnCAddr[!pEncPara_channel->RcnIdx] + pEncPara_channel->RcnCLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_YADDR_STR = pEncPara_channel->VEDU_SRC_YADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_YADDR_END = pEncPara_channel->VEDU_SRC_YADDR + pEncPara_channel->VEDU_SRC_YLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_CADDR_STR = pEncPara_channel->VEDU_SRC_CADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_CADDR_END = pEncPara_channel->VEDU_SRC_CADDR + pEncPara_channel->VEDU_SRC_CLength - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_VADDR_STR = pEncPara_channel->VEDU_SRC_VADDR;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_VADDR_END = pEncPara_channel->VEDU_SRC_VADDR + pEncPara_channel->VEDU_SRC_VLength - 1;

    HI_DBG_VENC("MST_VEDU_NBI_MVST_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVST_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_NBI_MVST_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVST_ADDR_END);
    HI_DBG_VENC("MST_VEDU_NBI_MVLD_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVLD_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_NBI_MVLD_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_NBI_MVLD_ADDR_END);
    HI_DBG_VENC("MST_VEDU_PMEST_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMEST_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_PMEST_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMEST_ADDR_END);
    HI_DBG_VENC("MST_VEDU_PMELD_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMELD_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_PMELD_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_PMELD_ADDR_END);
    HI_DBG_VENC("MST_VEDU_REC_YH_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YH_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_REC_YH_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YH_ADDR_END);
    HI_DBG_VENC("MST_VEDU_REC_CH_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CH_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_REC_CH_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CH_ADDR_END);
    HI_DBG_VENC("MST_VEDU_REC_YADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YADDR_STR);
    HI_DBG_VENC("MST_VEDU_REC_YADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_YADDR_END);
    HI_DBG_VENC("MST_VEDU_REC_CADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CADDR_STR);
    HI_DBG_VENC("MST_VEDU_REC_CADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REC_CADDR_END);
    HI_DBG_VENC("MST_VEDU_REF_YH_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YH_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_REF_YH_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YH_ADDR_END);
    HI_DBG_VENC("MST_VEDU_REF_CH_ADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CH_ADDR_STR);
    HI_DBG_VENC("MST_VEDU_REF_CH_ADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CH_ADDR_END);
    HI_DBG_VENC("MST_VEDU_REF_YADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YADDR_STR);
    HI_DBG_VENC("MST_VEDU_REF_YADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_YADDR_END);
    HI_DBG_VENC("MST_VEDU_REF_CADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CADDR_STR);
    HI_DBG_VENC("MST_VEDU_REF_CADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_REF_CADDR_END);
    HI_DBG_VENC("MST_VEDU_SRC_YADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_YADDR_STR);
    HI_DBG_VENC("MST_VEDU_SRC_YADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_YADDR_END);
    HI_DBG_VENC("MST_VEDU_SRC_CADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_CADDR_STR);
    HI_DBG_VENC("MST_VEDU_SRC_CADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_CADDR_END);
    HI_DBG_VENC("MST_VEDU_SRC_VADDR_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_VADDR_STR);
    HI_DBG_VENC("MST_VEDU_SRC_VADDR_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_SRC_VADDR_END);

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR0_STR = pEncPara_channel->VEDU_STRM_ADDR[0];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR1_STR = pEncPara_channel->VEDU_STRM_ADDR[1];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR2_STR = pEncPara_channel->VEDU_STRM_ADDR[2];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR3_STR = pEncPara_channel->VEDU_STRM_ADDR[3];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR4_STR = pEncPara_channel->VEDU_STRM_ADDR[4];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR5_STR = pEncPara_channel->VEDU_STRM_ADDR[5];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR6_STR = pEncPara_channel->VEDU_STRM_ADDR[6];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR7_STR = pEncPara_channel->VEDU_STRM_ADDR[7];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR8_STR = pEncPara_channel->VEDU_STRM_ADDR[8];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR9_STR = pEncPara_channel->VEDU_STRM_ADDR[9];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR10_STR = pEncPara_channel->VEDU_STRM_ADDR[10];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR11_STR = pEncPara_channel->VEDU_STRM_ADDR[11];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR12_STR = pEncPara_channel->VEDU_STRM_ADDR[12];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR13_STR = pEncPara_channel->VEDU_STRM_ADDR[13];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR14_STR = pEncPara_channel->VEDU_STRM_ADDR[14];
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR15_STR = pEncPara_channel->VEDU_STRM_ADDR[15];

    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR0_END = pEncPara_channel->VEDU_STRM_ADDR[0] + pEncPara_channel->VEDU_STRM_BUFLEN[0] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR1_END = pEncPara_channel->VEDU_STRM_ADDR[1] + pEncPara_channel->VEDU_STRM_BUFLEN[1] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR2_END = pEncPara_channel->VEDU_STRM_ADDR[2] + pEncPara_channel->VEDU_STRM_BUFLEN[2] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR3_END = pEncPara_channel->VEDU_STRM_ADDR[3] + pEncPara_channel->VEDU_STRM_BUFLEN[3] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR4_END = pEncPara_channel->VEDU_STRM_ADDR[4] + pEncPara_channel->VEDU_STRM_BUFLEN[4] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR5_END = pEncPara_channel->VEDU_STRM_ADDR[5] + pEncPara_channel->VEDU_STRM_BUFLEN[5] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR6_END = pEncPara_channel->VEDU_STRM_ADDR[6] + pEncPara_channel->VEDU_STRM_BUFLEN[6] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR7_END = pEncPara_channel->VEDU_STRM_ADDR[7] + pEncPara_channel->VEDU_STRM_BUFLEN[7] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR8_END = pEncPara_channel->VEDU_STRM_ADDR[8] + pEncPara_channel->VEDU_STRM_BUFLEN[8] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR9_END = pEncPara_channel->VEDU_STRM_ADDR[9] + pEncPara_channel->VEDU_STRM_BUFLEN[9] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR10_END = pEncPara_channel->VEDU_STRM_ADDR[10] + pEncPara_channel->VEDU_STRM_BUFLEN[10] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR11_END = pEncPara_channel->VEDU_STRM_ADDR[11] + pEncPara_channel->VEDU_STRM_BUFLEN[11] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR12_END = pEncPara_channel->VEDU_STRM_ADDR[12] + pEncPara_channel->VEDU_STRM_BUFLEN[12] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR13_END = pEncPara_channel->VEDU_STRM_ADDR[13] + pEncPara_channel->VEDU_STRM_BUFLEN[13] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR14_END = pEncPara_channel->VEDU_STRM_ADDR[14] + pEncPara_channel->VEDU_STRM_BUFLEN[14] - 1;
    pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR15_END = pEncPara_channel->VEDU_STRM_ADDR[15] + pEncPara_channel->VEDU_STRM_BUFLEN[15] - 1;

    HI_DBG_VENC("pEncPara_channel->VEDU_STRM_BUFLEN[0]:%d\n",pEncPara_channel->VEDU_STRM_BUFLEN[0]);
    HI_DBG_VENC("pEncPara_channel->VEDU_SRC_YLength[0]:%d\n",pEncPara_channel->VEDU_SRC_YLength);
    HI_DBG_VENC("pEncPara_channel->VEDU_SRC_CLength[0]:%d\n",pEncPara_channel->VEDU_SRC_CLength);
    HI_DBG_VENC("pEncPara_channel->VEDU_SRC_VLength[0]:%d\n",pEncPara_channel->VEDU_SRC_VLength);

    HI_DBG_VENC("MST_VEDU_STRMADDR0_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR0_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR1_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR1_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR2_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR2_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR3_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR3_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR4_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR4_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR5_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR5_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR6_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR6_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR7_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR7_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR8_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR8_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR9_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR9_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR10_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR10_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR11_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR11_STR);
    HI_DBG_VENC("MST_VEDU_STRMADDR12_STR:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR12_STR);

    HI_DBG_VENC("MST_VEDU_ENDMADDR0_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR0_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR1_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR1_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR2_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR2_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR3_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR3_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR4_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR4_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR5_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR5_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR6_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR6_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR7_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR7_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR8_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR8_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR9_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR9_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR10_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR10_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR11_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR11_END);
    HI_DBG_VENC("MST_VEDU_ENDMADDR12_END:0x%x\n",pAllReg->VEDU_MMU1_REGS.MST_VEDU_STRMADDR12_END);


    pAllReg->VEDU_VCPI_REGS.VEDU_TUNLCELL_ADDR = pEncPara_channel->TUNLCELL_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_YADDR     = pEncPara_channel->VEDU_SRC_YADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_CADDR     = pEncPara_channel->VEDU_SRC_CADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_SRC_VADDR     = pEncPara_channel->VEDU_SRC_VADDR  ;
    pAllReg->VEDU_VCPI_REGS.VEDU_YH_ADDR       = pEncPara_channel->VEDU_YH_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_CH_ADDR       = pEncPara_channel->VEDU_CH_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_package_sel  = pEncPara_channel->vcpi_package_sel;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_str_fmt = pEncPara_channel->vcpi_str_fmt;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRFMT.bits.vcpi_store_mode  = pEncPara_channel->vcpi_store_mode;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_y_stride = pEncPara_channel->curld_y_stride;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_c_stride = pEncPara_channel->curld_c_stride;

	 // curld yh 实际没有起作用
    pAllReg->VEDU_VCPI_REGS.VEDU_HEAD_STRIDE.bits.curld_yh_stride = pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_y_stride*2;
    pAllReg->VEDU_VCPI_REGS.VEDU_HEAD_STRIDE.bits.curld_ch_stride = pAllReg->VEDU_VCPI_REGS.VEDU_STRIDE.bits.curld_c_stride*2;

    pAllReg->VEDU_VCPI_REGS.VEDU_REC_YADDR  = pEncPara_channel->RcnYAddr[pEncPara_channel->RcnIdx] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_CADDR   = pEncPara_channel->RcnCAddr[pEncPara_channel->RcnIdx];

    /* Define the union U_VEDU_REC_STRIDE */
    {
        U_VEDU_REC_STRIDE D32;
        D32.u32 = 0;
        D32.bits.recst_ystride = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        D32.bits.recst_cstride = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        pAllReg->VEDU_VCPI_REGS.VEDU_REC_STRIDE.u32 = D32.u32;
    }
    // REC_YH_ADDR
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_YH_ADDR  = pEncPara_channel->RcnYHeadAddr[pEncPara_channel->RcnIdx] ;
    //REC_CH_ADDR
    pAllReg->VEDU_VCPI_REGS.VEDU_REC_CH_ADDR = pEncPara_channel->RcnCHeadAddr[pEncPara_channel->RcnIdx] ;
    //REC_HEAD_STRIDE
    {
        U_VEDU_REC_HEAD_STRIDE D32;
        D32.u32 = 0;
        if (pEncPara->vcpi_protocol == VEDU_H265)
        {
            D32.bits.recst_head_stride   = (pEncPara->vcpi_imgwidth_pix + 63)/64*32;
        }
        else if (pEncPara->vcpi_protocol == VEDU_H264)
        {
            D32.bits.recst_head_stride   = (pEncPara->vcpi_imgwidth_pix + 255)/256*32;
        }
        pAllReg->VEDU_VCPI_REGS.VEDU_REC_HEAD_STRIDE.u32 = D32.u32;
    }

     //VEDU_LUMA_REF_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_YADDR = pEncPara_channel->RcnYAddr[!pEncPara_channel->RcnIdx] ;
     //VEDU_CHROMA_REF_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_CADDR = pEncPara_channel->RcnCAddr[!pEncPara_channel->RcnIdx] ;

     /* Define the union U_VEDU_VSTRIDE */
    {
        U_VEDU_REF_STRIDE D32;
        D32.u32 = 0;

        D32.bits.refld_luma_vstride   = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        D32.bits.refld_chroma_vstride   = (pEncPara->vcpi_imgwidth_pix + 255)/256*256;
        pAllReg->VEDU_VCPI_REGS.VEDU_REF_STRIDE.u32 = D32.u32;
    }

     //VEDU_REF_YH_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_YH_ADDR  = pEncPara_channel->RcnYHeadAddr[!pEncPara_channel->RcnIdx] ;
     //VEDU_REF_CH_ADDR
     pAllReg->VEDU_VCPI_REGS.VEDU_REF_CH_ADDR  = pEncPara_channel->RcnCHeadAddr[!pEncPara_channel->RcnIdx] ;
     /* Define the union U_VEDU_REF_HSTRIDE */
    {
        U_VEDU_REF_HSTRIDE D32;
        D32.u32 = 0;
        if (pEncPara->vcpi_protocol == VEDU_H265)
        {
            D32.bits.refld_yh_stride  = (pEncPara->vcpi_imgwidth_pix + 63)/64*32;
            D32.bits.refld_ch_stride  = (pEncPara->vcpi_imgwidth_pix + 63)/64*32;
        }
        else if (pEncPara->vcpi_protocol == VEDU_H264)
        {
            D32.bits.refld_yh_stride  = (pEncPara->vcpi_imgwidth_pix + 255)/256*32;
            D32.bits.refld_ch_stride  = (pEncPara->vcpi_imgwidth_pix + 255)/256*32;
        }
        pAllReg->VEDU_VCPI_REGS.VEDU_REF_HSTRIDE.u32 = D32.u32;
    }

     ///////VEDU_PMELD_ADDR
    pAllReg->VEDU_VCPI_REGS.VEDU_PMELD_ADDR  = pEncPara_channel->VEDU_PMELD_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_PMEST_ADDR  = pEncPara_channel->VEDU_PMEST_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_NBI_MVST_ADDR   = pEncPara_channel->VEDU_NBI_MVST_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_NBI_MVLD_ADDR   = pEncPara_channel->VEDU_NBI_MVLD_ADDR ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR0  = pEncPara_channel->VEDU_STRM_ADDR[0] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR1  = pEncPara_channel->VEDU_STRM_ADDR[1] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR2  = pEncPara_channel->VEDU_STRM_ADDR[2] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR3  = pEncPara_channel->VEDU_STRM_ADDR[3] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR4  = pEncPara_channel->VEDU_STRM_ADDR[4] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR5  = pEncPara_channel->VEDU_STRM_ADDR[5] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR6  = pEncPara_channel->VEDU_STRM_ADDR[6] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR7  = pEncPara_channel->VEDU_STRM_ADDR[7] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR8  = pEncPara_channel->VEDU_STRM_ADDR[8] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR9  = pEncPara_channel->VEDU_STRM_ADDR[9] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR10  = pEncPara_channel->VEDU_STRM_ADDR[10] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR11  = pEncPara_channel->VEDU_STRM_ADDR[11] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR12  = pEncPara_channel->VEDU_STRM_ADDR[12] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR13  = pEncPara_channel->VEDU_STRM_ADDR[13] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR14  = pEncPara_channel->VEDU_STRM_ADDR[14] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMADDR15  = pEncPara_channel->VEDU_STRM_ADDR[15] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN0  = pEncPara_channel->VEDU_STRM_BUFLEN[0] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN1  = pEncPara_channel->VEDU_STRM_BUFLEN[1] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN2  = pEncPara_channel->VEDU_STRM_BUFLEN[2] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN3  = pEncPara_channel->VEDU_STRM_BUFLEN[3] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN4  = pEncPara_channel->VEDU_STRM_BUFLEN[4] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN5  = pEncPara_channel->VEDU_STRM_BUFLEN[5] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN6  = pEncPara_channel->VEDU_STRM_BUFLEN[6] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN7  = pEncPara_channel->VEDU_STRM_BUFLEN[7] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN8  = pEncPara_channel->VEDU_STRM_BUFLEN[8] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN9  = pEncPara_channel->VEDU_STRM_BUFLEN[9] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN10  = pEncPara_channel->VEDU_STRM_BUFLEN[10] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN11  = pEncPara_channel->VEDU_STRM_BUFLEN[11] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN12  = pEncPara_channel->VEDU_STRM_BUFLEN[12] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN13  = pEncPara_channel->VEDU_STRM_BUFLEN[13] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN14  = pEncPara_channel->VEDU_STRM_BUFLEN[14] ;
    pAllReg->VEDU_VCPI_REGS.VEDU_STRMBUFLEN15  = pEncPara_channel->VEDU_STRM_BUFLEN[15] ;

#ifdef HARDWARE_SPLIT_SPS_PPS_EN
      pAllReg->VEDU_VCPI_REGS.VEDU_CURLD_LOWDLY.bits.vcpi_para_sprat_en = 1;
	if (pEncPara_channel->bFirstNal2Send)
	{
		pAllReg->VEDU_VCPI_REGS.VEDU_PARA_ADDR	      = pEncPara_channel->stStreamHeader_OMX.bufferaddr_Phy;
		pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_STR = pEncPara_channel->stStreamHeader_OMX.bufferaddr_Phy ;
		pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_END = pEncPara_channel->stStreamHeader_OMX.bufferaddr_Phy + pEncPara_channel->stStreamHeader_OMX.buffer_size  - 1;
        HI_INFO_VENC("pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_STR:0x%x pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_END:0x%x\n",
			pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_STR,pAllReg->VEDU_MMU1_REGS.MST_VEDU_PPS_ADDR_END);
	}
#else
      pAllReg->VEDU_VCPI_REGS.VEDU_CURLD_LOWDLY.bits.vcpi_para_sprat_en = 0;
#endif



	 /*-----------------------------------------  slice 寄存器额外配置l00214825  ---------------------------------------------*/

    /* Define the union U_CABAC_GLB_CFG */
    {
        U_CABAC_GLB_CFG D32;
        D32.u32 = 0;

        D32.bits.max_num_mergecand = pEncPara->max_num_mergecand ;//

        if(pEncPara_channel->vcpi_frame_type ==1)
        {
            D32.bits.nal_unit_head = 0x0201;// pEncPara->nal_unit_head ;P frame
        }
        else
        {
            D32.bits.nal_unit_head = 0x2601;// pEncPara->nal_unit_head ;
        }
        pAllReg->VEDU_CABAC_REGS.CABAC_GLB_CFG.u32 = D32.u32;
    }

    /* Define the union U_CABAC_SLCHDR_SIZE */
    {
        U_CABAC_SLCHDR_SIZE D32;
        D32.u32 = 0;

        D32.bits.slchdr_size_part1 = pEncPara_channel->slchdr_size_part1 ;
        D32.bits.slchdr_size_part2 = pEncPara_channel->slchdr_size_part2 ;

        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_SIZE.u32 = D32.u32;
    }
        /* Define the union U_CABAC_SLCHDR_PART1 */
    {
        U_CABAC_SLCHDR_PART1 D32;
        D32.u32 = 0;

        D32.bits.slchdr_part1  = pEncPara_channel->slchdr_part1  << (16 - pEncPara_channel->slchdr_size_part1);

        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART1.u32 = D32.u32;
    }

    /* Define the union U_CABAC_SLCHDR_PART2_SEG1 */

    if (pEncPara_channel->vcpi_protocol== VEDU_H265)
    {
        if(pEncPara_channel->slchdr_size_part2 < 32)
        {
            pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG1 = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[0] << (32 - pEncPara_channel->slchdr_size_part2) ;
        }
        else
        {
            pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG1  = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[0] ;
        }

        if(pEncPara_channel->slchdr_size_part2 > 32)
        {
            pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG2   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[1] << (32 - (pEncPara_channel->slchdr_size_part2 - 32)) ;
        }
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG3   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[2] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG4   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[3] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG5   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[4] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG6   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[5] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG7   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[6] ;
        pAllReg->VEDU_CABAC_REGS.CABAC_SLCHDR_PART2_SEG8   = pEncPara_channel->CABAC_SLCHDR_PART2_SEG[7] ;
    }
    else
    {
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm0 = pEncPara_channel->SlcHdrStream [0];
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm1 = pEncPara_channel->SlcHdrStream [1];
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm2 = pEncPara_channel->SlcHdrStream [2];
        pAllReg->VEDU_VLC_REGS.VLC_SlcHdrStrm3 = pEncPara_channel->SlcHdrStream [3];
        pAllReg->VEDU_VLC_REGS.VLC_ReorderStrm0 = pEncPara_channel->ReorderStream[0];
        pAllReg->VEDU_VLC_REGS.VLC_ReorderStrm1  = pEncPara_channel->ReorderStream[1];
        pAllReg->VEDU_VLC_REGS.VLC_MarkingStrm0  = pEncPara_channel->MarkingStream[0];
        pAllReg->VEDU_VLC_REGS.VLC_MarkingStrm1 = pEncPara_channel->MarkingStream[1];
        pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_parabit = ((pEncPara_channel->SlcHdrBits >>  0) & 0xFF) - 1;
        pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_reorderbit = ((pEncPara_channel->SlcHdrBits >>  8) & 0xFF) - 1;
        pAllReg->VEDU_VLC_REGS.VLC_SLCHDRPARA.bits.vcpi_markingbit = ((pEncPara_channel->SlcHdrBits >> 16) & 0xFF) - 1;
    }

    pAllReg->VEDU_VLCST_REGS.VLCST_PARAMETER.bits.vlcst_para_set_en = pEncPara_channel->vlcst_para_set_en;
    if (pEncPara_channel->vlcst_para_set_en == 1)
    {
        pAllReg->VEDU_VLCST_REGS.VLCST_PARAMETER.bits.vlcst_para_set_len = pEncPara_channel->vlcst_para_set_len;
        pEncPara_channel->vlcst_para_set_en = 0;
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA0 = pEncPara_channel->VEDU_HEADER[0];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA1 = pEncPara_channel->VEDU_HEADER[1];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA2 = pEncPara_channel->VEDU_HEADER[2];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA3 = pEncPara_channel->VEDU_HEADER[3];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA4 = pEncPara_channel->VEDU_HEADER[4];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA5 = pEncPara_channel->VEDU_HEADER[5];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA6 = pEncPara_channel->VEDU_HEADER[6];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA7 = pEncPara_channel->VEDU_HEADER[7];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA8 = pEncPara_channel->VEDU_HEADER[8];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA9 = pEncPara_channel->VEDU_HEADER[9];
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA0:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA0);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA1:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA1);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA2:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA2);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA3:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA3);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA4:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA4);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA5:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA5);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA6:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA6);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA7:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA7);
        HI_DBG_VENC("pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA8:0x%x\n",pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA8);

        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA10 = pEncPara_channel->VEDU_HEADER[10];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA11 = pEncPara_channel->VEDU_HEADER[11];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA12 = pEncPara_channel->VEDU_HEADER[12];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA13 = pEncPara_channel->VEDU_HEADER[13];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA14 = pEncPara_channel->VEDU_HEADER[14];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA15 = pEncPara_channel->VEDU_HEADER[15];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA16 = pEncPara_channel->VEDU_HEADER[16];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA17 = pEncPara_channel->VEDU_HEADER[17];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA18 = pEncPara_channel->VEDU_HEADER[18];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA19 = pEncPara_channel->VEDU_HEADER[19];

        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA20 = pEncPara_channel->VEDU_HEADER[20];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA21 = pEncPara_channel->VEDU_HEADER[21];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA22 = pEncPara_channel->VEDU_HEADER[22];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA23 = pEncPara_channel->VEDU_HEADER[23];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA24 = pEncPara_channel->VEDU_HEADER[24];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA25 = pEncPara_channel->VEDU_HEADER[25];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA26 = pEncPara_channel->VEDU_HEADER[26];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA27 = pEncPara_channel->VEDU_HEADER[27];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA28 = pEncPara_channel->VEDU_HEADER[28];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA29 = pEncPara_channel->VEDU_HEADER[29];

        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA30 = pEncPara_channel->VEDU_HEADER[30];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA31 = pEncPara_channel->VEDU_HEADER[31];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA32 = pEncPara_channel->VEDU_HEADER[32];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA33 = pEncPara_channel->VEDU_HEADER[33];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA34 = pEncPara_channel->VEDU_HEADER[34];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA35 = pEncPara_channel->VEDU_HEADER[35];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA36 = pEncPara_channel->VEDU_HEADER[36];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA37 = pEncPara_channel->VEDU_HEADER[37];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA38 = pEncPara_channel->VEDU_HEADER[38];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA39 = pEncPara_channel->VEDU_HEADER[39];

        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA40 = pEncPara_channel->VEDU_HEADER[40];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA41 = pEncPara_channel->VEDU_HEADER[41];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA42 = pEncPara_channel->VEDU_HEADER[42];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA43 = pEncPara_channel->VEDU_HEADER[43];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA44 = pEncPara_channel->VEDU_HEADER[44];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA45 = pEncPara_channel->VEDU_HEADER[45];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA46 = pEncPara_channel->VEDU_HEADER[46];
        pAllReg->VEDU_VLCST_REGS.VLCST_PARA_DATA47 = pEncPara_channel->VEDU_HEADER[47];
    }
/*-----------------------------------------  slice 寄存器额外配置l00214825	 end---------------------------------------------*/
#if 0
     int *tmp = pEncPara_channel->pstCfg_EncPara;
     int i = 0;
    for(i = 0;i<(sizeof(VeduEfl_EncPara_S_Cfg)/64);i++)
    {
        HI_DBG_VENC("%d ",i);

        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);

        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);

        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);

        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("%x ",*tmp++);
        HI_DBG_VENC("\n");
    }
#else

    for (chanlnum = 0; chanlnum < VENC_MAX_CHN_NUM; chanlnum++)
    {
        if (g_stVencChn[chanlnum].hVEncHandle == EncHandle)
        {
            break;
        }
    }

    if (g_stVencChn[chanlnum].stProcWrite.bSaveYUVFileRun )
    {
        HI_INFO_VENC("save cfg\n");
        pReg = Reg;
        pLogicReg = (HI_U8 *)pAllReg;
        for (ii = 0;ii < 0x3e00;ii+=0x200)
        {
            memcpy((HI_VOID *)pReg,(HI_VOID *)pLogicReg,0x200);
            VencHal_SaveFile("/sdcard/reg.txt", pReg, 0x200);
            pLogicReg+= 0x200;
        }
    }
#endif
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
