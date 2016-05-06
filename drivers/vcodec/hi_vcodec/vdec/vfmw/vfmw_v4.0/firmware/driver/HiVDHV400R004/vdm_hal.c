
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vdm_hal.c
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

#include "basedef.h"
#include "vfmw.h"
#include "mem_manage.h"
#include "public.h"
#include "scd_drv.h"
#include "vdm_hal_v400r004_api.h"
#include "vdm_hal_v400r004_local.h"
#ifdef VFMW_MPEG2_SUPPORT
#include "vdm_hal_v400r004_mpeg2.h"
#endif
#ifdef VFMW_H264_SUPPORT
#include "vdm_hal_v400r004_h264.h"
#endif
#ifdef VFMW_HEVC_SUPPORT
#include "vdm_hal_v400r004_hevc.h"
#endif
#ifdef VFMW_MPEG4_SUPPORT
#include "vdm_hal_v400r004_mpeg4.h"
#endif
#ifdef VFMW_AVS_SUPPORT
#include "vdm_hal_v400r004_avs.h"
#endif
#ifdef VFMW_REAL8_SUPPORT
#include "vdm_hal_v400r004_real8.h"
#endif
#ifdef VFMW_REAL9_SUPPORT
#include "vdm_hal_v400r004_real9.h"
#endif
#ifdef VFMW_VC1_SUPPORT
#include "vdm_hal_v400r004_vc1.h"
#endif
#ifdef VFMW_DIVX3_SUPPORT
#include "vdm_hal_v400r004_divx3.h"
#endif
#ifdef VFMW_VP6_SUPPORT
#include "vdm_hal_v400r004_vp6.h"
#endif
#ifdef VFMW_VP8_SUPPORT
#include "vdm_hal_v400r004_vp8.h"
#endif
#include "vfmw_ctrl.h"
#ifdef HIVDEC_SMMU_SUPPORT
#include "smmu.h"
#endif

extern UINT8 g_not_direct_8x8_inference_flag;
extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];
extern DSP_STATE_E   g_DSPState[MAX_CHAN_NUM];
extern CHAN_CTX g_ChanCtx;
extern FSP_INST_S *s_pFspInst[MAX_CHAN_NUM];
extern SINT32 g_LastFrameRate[MAX_CHAN_NUM];
extern UINT8  g_not_allow_H264FullPictureRepair_flag;

/************************************************************************/
/*  函数实现                                                            */
/************************************************************************/
SINT32 VDMHAL_V400R004_GetHalMemSize(VOID)
{
    SINT32 size = 0;
#ifdef VFMW_HEVC_SUPPORT
    //hevc时,消息池和码表 各模块内存总大小需要更大l00214825
    size = HW_V400R004_HEVC_MEM_SIZE;
        
    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        size += (HEVC_SED_TOP_ADDR_LEN + 0xF) &(~0xF);
    }
    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        size += (HEVC_PMV_TOP_ADDR_LEN + 0xF) &(~0xF);
    }
    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        size += (HEVC_RCN_TOP_ADDR_LEN + 0xF) &(~0xF);
    }
    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        size += (HEVC_DBLK_TOP_ADDR_LEN + 0xF) &(~0xF);
    }
    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        size += (HEVC_SAO_TOP_ADDR_LEN + 0xF) &(~0xF);
    }

    return size;
#else
    size = HW_V400R004_MEM_SIZE;

    return size;
#endif
}

SINT32 VDMHAL_V400R004_OpenHAL(VDMHAL_OPENPARAM_S *pOpenParam)
{
    SINT32 i;
    SINT32 Ret;
    UADDR  PhyAddr;
    UADDR  PhyAddr_HEVC;
    UADDR  MemBaseAddr;
    SINT32 Size, VdhId;
 
    VDMHAL_ASSERT_RET(NULL!=pOpenParam, "pOpenParam = NULL error!");
    MemBaseAddr = pOpenParam->MemBaseAddr;
    Size        = pOpenParam->Size;
    VdhId       = pOpenParam->VdhId;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    VDMHAL_ASSERT_RET(0 != MemBaseAddr, "MemBaseAddr = 0 error!");
#ifdef VFMW_HEVC_SUPPORT
    VDMHAL_ASSERT_RET(Size >= HW_V400R004_HEVC_MEM_SIZE, "VDMHAL_V400R004_OpenHAL: Size error!");
#else
    VDMHAL_ASSERT_RET(Size >= HW_V400R004_MEM_SIZE, "VDMHAL_V400R004_OpenHAL: Size error!");
#endif

    /* clear */
    memset( &g_HwMem[VdhId], 0, sizeof(VDMHAL_HWMEM_S) );

    /* reg vir addr, for RD_VREG, WR_VREG, and reset vdm */
    g_HwMem[VdhId].pVdmRegVirAddr = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr);
    g_HwMem[VdhId].pBpdRegVirAddr = (SINT32 *)MEM_Phy2Vir(gBpdRegBaseAddr);

    /* overall info */
    g_HwMem[VdhId].HALMemBaseAddr = (MemBaseAddr + 1023) & (~1023);
    g_HwMem[VdhId].HALMemSize     = Size - (g_HwMem[VdhId].HALMemBaseAddr - MemBaseAddr);
    g_HwMem[VdhId].VahbStride     = VHB_V400R004_STRIDE_BYTE;

    /* message pool */
    PhyAddr = g_HwMem[VdhId].HALMemBaseAddr;

#ifdef VFMW_HEVC_SUPPORT
    //由于hevc消息池,消息比较大,分配消息地址时,按照hevc消息大小分配,先如此分配,l00214825 01174_STRIDE_BYTE;
    for ( i = 0; i < HEVC_MAX_SLOT_NUM; i++ )
    {
        g_HwMem[VdhId].MsgSlotAddr[i] = PhyAddr + i * 4 * HEVC_ONE_MSG_SLOT_LEN;
    }

    PhyAddr += HEVC_MAX_SLOT_NUM * 4 * HEVC_ONE_MSG_SLOT_LEN;
    g_HwMem[VdhId].ValidMsgSlotNum = HEVC_MAX_SLOT_NUM;
#else

    for ( i = 0; i < MSG_V400R004_SLOT_NUM; i++ )
    {
        g_HwMem[VdhId].MsgSlotAddr[i] = PhyAddr + i * 4 * MSG_SLOT_SIZE;
    }

    PhyAddr += MSG_V400R004_SLOT_NUM * 4 * MSG_SLOT_SIZE;
    g_HwMem[VdhId].ValidMsgSlotNum = MSG_V400R004_SLOT_NUM;
#endif

    /*H264MnAddr和mn_phy_addr必须在这里分配，否则会导致265解完带tile的码流后再解264会导致264解码错误的问题*/
    /*cabac mn tab*/
	PhyAddr = (PhyAddr + 1023) & (~1023);
    g_HwMem[VdhId].H264MnAddr = PhyAddr;
    PhyAddr += (CA_V400R004_MN_ADDR_LEN + 0xF) &(~0xF);

#ifdef VFMW_HEVC_SUPPORT
	PhyAddr = (PhyAddr + 1023) & (~1023);
    g_HwMem[VdhId].mn_phy_addr = PhyAddr;
    PhyAddr += (CA_V400R004_HEVC_MN_ADDR_LEN + 0xF) &(~0xF);
#endif

    /* code table */
    PhyAddr_HEVC = PhyAddr = (PhyAddr + 0x8000) & (~0x8000);

    /*sed_top + pmv_top + rcn_top*/
    g_HwMem[VdhId].SedTopAddr = PhyAddr;
    PhyAddr += (SED_V400R004_TOP_ADDR_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].PmvTopAddr = PhyAddr;
    PhyAddr += (PMV_V400R004_TOP_ADDR_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].RcnTopAddr = PhyAddr;
    PhyAddr += 0;//(RCN_V400R004_TOP_ADDR_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].ItransTopAddr = PhyAddr;
    PhyAddr += (ITRANS_V400R004_TOP_ADDR_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].DblkTopAddr = PhyAddr;
    PhyAddr += (DBLK_V400R004_TOP_ADDR_LEN + 0xF) &(~0xF);
    g_HwMem[VdhId].PpfdBufAddr = PhyAddr;
    g_HwMem[VdhId].PpfdBufLen = (PPFD_V400R004_BUF_LEN_DEFAULT / 128) - 1;
    PhyAddr += (PPFD_V400R004_BUF_LEN_DEFAULT + 0xF) &(~0xF);

    g_HwMem[VdhId].IntensityConvTabAddr = PhyAddr;
    PhyAddr += 256 * 2 * 2 * 3;

    g_HwMem[VdhId].BitplaneInfoAddr = PhyAddr;
#ifdef VFMW_VC1_SUPPORT
    PhyAddr += (VC1VFMW_MAX_PIC_MB + 0xF) &(~0xF);
#endif

    g_HwMem[VdhId].Vp8TabAddr = PhyAddr;
    PhyAddr += 32 * 1024;

    g_HwMem[VdhId].Vp6TabAddr = PhyAddr;
    PhyAddr += 4 * 1024;

#ifdef VFMW_HEVC_SUPPORT
    /* 因为HAL内存不重合，而且HEVC所需内存比上述值要大所以这里可以重复对HEVC专门的赋值，避免内存浪费。y00226912 */
    g_HwMem[VdhId].sed_top_phy_addr = PhyAddr_HEVC;

    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        PhyAddr_HEVC += (HEVC_SED_TOP_ADDR_LEN + 0xF) &(~0xF);
    }

    g_HwMem[VdhId].pmv_top_phy_addr = PhyAddr_HEVC;

    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        PhyAddr_HEVC += (HEVC_PMV_TOP_ADDR_LEN + 0xF) &(~0xF);
    }

    g_HwMem[VdhId].pmv_left_phy_addr = PhyAddr_HEVC;
    PhyAddr_HEVC += (HEVC_PMV_LEFT_ADDR_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].rcn_top_phy_addr = PhyAddr_HEVC;

    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        PhyAddr_HEVC += (HEVC_RCN_TOP_ADDR_LEN + 0xF) &(~0xF);
    }

    g_HwMem[VdhId].tile_segment_info_phy_addr = PhyAddr_HEVC;
    PhyAddr_HEVC += (HEVC_TILE_SEGMENT_INFO_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].dblk_left_phy_addr = PhyAddr_HEVC;
    PhyAddr_HEVC += (HEVC_DBLK_LEFT_ADDR_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].dblk_top_phy_addr = PhyAddr_HEVC;

    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        PhyAddr_HEVC += (HEVC_DBLK_TOP_ADDR_LEN + 0xF) &(~0xF);
    }

    g_HwMem[VdhId].sao_left_phy_addr = PhyAddr_HEVC;
    PhyAddr_HEVC += (HEVC_SAO_LEFT_ADDR_LEN + 0xF) &(~0xF);

    g_HwMem[VdhId].sao_top_phy_addr = PhyAddr_HEVC;

    if (HEVC_MAX_PIX_WIDTH > 4096)  //z00290437  20141016  超4K使用片外RAM
    {
        PhyAddr_HEVC += (HEVC_SAO_TOP_ADDR_LEN + 0xF) &(~0xF);
    }

    g_HwMem[VdhId].ppfd_phy_addr = PhyAddr_HEVC;
    g_HwMem[VdhId].ppfd_buf_len = 0;    //z00290437 20141016  HEVC协议PPFD模块删除
#endif

    PhyAddr = MAX(PhyAddr, PhyAddr_HEVC);

    /* if memory is enough, init code table for all standards */
    if ((PhyAddr - MemBaseAddr) <= Size)
    {
        Ret = VDMHAL_OK;
#if defined(VFMW_H264_SUPPORT) || defined(VFMW_MVC_SUPPORT)

        if ( VDMHAL_OK != H264HAL_V400R004_InitHal(&g_HwMem[VdhId]) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_HEVC_SUPPORT

        if ( VDMHAL_OK != HEVCHAL_V400R004_InitHal(&g_HwMem[VdhId]) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_MPEG2_SUPPORT

        if ( VDMHAL_OK != MP2HAL_V400R004_InitHal(g_HwMem[VdhId].MPEG2TabAddr, VdhId) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_MPEG4_SUPPORT

        if ( VDMHAL_OK != MP4HAL_V400R004_InitHal(g_HwMem[VdhId].MPEG4TabAddr) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_AVS_SUPPORT

        if ( VDMHAL_OK != AVSHAL_V400R004_InitHal(g_HwMem[VdhId].AVSTabAddr) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_REAL8_SUPPORT

        if ( VDMHAL_OK != RV8HAL_V400R004_InitHal() )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_REAL9_SUPPORT

        if ( VDMHAL_OK != RV9HAL_V400R004_InitHal() )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_VC1_SUPPORT

        if ( VDMHAL_OK != VC1HAL_V400R004_InitHal(g_HwMem[VdhId].VC1TabAddr) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_VP6_SUPPORT

        if ( VDMHAL_OK != VP6HAL_V400R004_InitHal(g_HwMem[VdhId].Vp6TabAddr) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
#ifdef VFMW_VP8_SUPPORT

        if ( VDMHAL_OK != VP8HAL_V400R004_InitHal(g_HwMem[VdhId].Vp8TabAddr) )
        {
            Ret = VDMHAL_ERR;
        }

#endif
        return Ret;
    }
    else
    {
        dprint(PRN_FATAL, "!!!!!! HAL memory not enouph! need %d, have %d\n", PhyAddr - MemBaseAddr, Size);
        return VDMHAL_ERR;
    }

    return VDMHAL_OK;
}

VOID VDMHAL_V400R004_CloseHAL(SINT32 VdhId)
{
    SINT32 *ps32;

    ps32 = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr);

    if ( NULL != ps32 )
    {
        VDMHAL_ResetVdm(VdhId);
    }

    return;
}

/*****************************************************************************************
  原型    static UINT32 VDMHAL_V400R004_CalcFsSize(SINT32 ChanID, SINT32 Width, SINT32 Height, SINT32 UserDec, VID_STD_E VidStd)
  功能    计算所需的每一帧的帧存大小
  参数    ChanID  通道号
  Width   帧图的宽
  Height  帧图的高
  UserDec 用户态解码
  VidStd  视频协议类型(HEVC的计算方式有不同)
  返回值  所需要的帧存大小
 ******************************************************************************************/
static UINT32 VDMHAL_V400R004_CalcFsSize(SINT32 ChanID, SINT32 Width, SINT32 Height, VID_STD_E VidStd)
{
    SINT32 ImgWidthInMb;
    SINT32 ImgHeightInMb;
    SINT32 ImgWidthInPixAln;
    SINT32 ImgHeightInPixAln;
    SINT32 ColMbSize;
    SINT32 PmvSlotLen;
    SINT32 SlotWidth;
    SINT32 ImgSlotLen;
    SINT32 level = 0;
    SINT32 AlignLost;
    SINT32 LowDelay;

    VDMHAL_ASSERT_RET(Width >= 32 && Width <= MAX_HOR_SIZE && \
                      Height >= 32 && Height <= MAX_VER_SIZE, \
                      "image size out of range");

    /*计算PMV大小*/
    ImgWidthInMb  = (Width + 15) >> 4;
    ImgHeightInMb = (Height + 15) >> 4;
    ImgWidthInPixAln = ImgWidthInMb * 16;
    ImgHeightInPixAln = ImgHeightInMb * 16;

    if ((ImgWidthInMb <= 45) && (ImgHeightInMb <= 36))
    {
        ColMbSize = 16 * 4;  //ONEMB_V200_PMV_COLMB_ADDR_LEN;
    }
    else
    {
        ColMbSize = 8 * 4;  //ONEMB_V200_PMV_COLMB_ADDR_LEN;
    }

    if (1 == g_not_direct_8x8_inference_flag)
    {
        ColMbSize = 16 * 4;
    }

    if (VFMW_HEVC == VidStd)
    {
        ColMbSize = 4 * 4;
    }

    PmvSlotLen = (ColMbSize * ImgWidthInMb * ImgHeightInMb + (2 * ALIGN_LEN - 1)) \
                 & (~(2 * ALIGN_LEN - 1));

    /*计算Frame store尺寸*/
    if (VFMW_HEVC == VidStd)
    {
        SlotWidth  = (Width + ((4 * ALIGN_LEN) - 1)) & (~((4 * ALIGN_LEN) - 1));
    }
    else
    {
        SlotWidth  = (ImgWidthInPixAln + ((4 * ALIGN_LEN) - 1)) & (~((4 * ALIGN_LEN) - 1));
    }

    /*默认开压缩，为其头信息开辟内存*/
    if (ImgWidthInPixAln > 0 && ImgWidthInPixAln <= 2048)
    {
        level = 16;
    }
    else if (ImgWidthInPixAln > 2048 && ImgWidthInPixAln <= 4096)
    {
        level = 32;
    }
    else if (ImgWidthInPixAln > 4096 && ImgWidthInPixAln <= 6144)
    {
        level = 48;
    }
    else if (ImgWidthInPixAln > 6144 && ImgWidthInPixAln <= 8192)
    {
        level = 64;
    }

    if (VFMW_HEVC == VidStd)
    {
        ImgSlotLen = SlotWidth * Height * 3 / 2;
    }
    else
    {
        ImgSlotLen = ((SlotWidth) * ((ImgHeightInPixAln + 31) / 32) * 32 * 3) / 2 + \
                     level * ((ImgHeightInPixAln + 31) / 32) * 32 * 3 / 2;
    }

    /*计算地址对齐耗损*/
    AlignLost = VHB_V400R004_STRIDE_BYTE;
    /*计算lowdelay, 默认只要打开支持模块间低延迟就将等号所需要的内存资源分配，一个帧存只需要 32 BYTE*/
    LowDelay = 32;

    /*这里因为已经计算出来了一些帧存元素，先存储一部分*/
    memset(&(s_pstVfmwChan[ChanID]->stMemArrangeInfo), 0, sizeof(VFMW_MEM_ARRANGE_INFO_S));
    s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange.HafPmvOffset = PmvSlotLen / 2;
    s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange.VahbStride = SlotWidth * 16 ;  // ystride x 16

    if (VFMW_HEVC == VidStd)
    {
        s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange.ChromOffset = SlotWidth * Height;
    }
    else
    {
        s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange.ChromOffset = SlotWidth * ((ImgHeightInPixAln + 31) / 32) * 32 + level * ((ImgHeightInPixAln + 31) / 32) * 32;
    }

    s_pstVfmwChan[ChanID]->stMemArrangeInfo.ImgSlotLen = ImgSlotLen;
    s_pstVfmwChan[ChanID]->stMemArrangeInfo.PmvSlotLen = PmvSlotLen;

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    return (ImgSlotLen + PmvSlotLen + AlignLost + LowDelay);
#else
    return (ImgSlotLen + PmvSlotLen + AlignLost);
#endif
}

/*****************************************************************************************
  原型    staitc SINT32 VDMHAL_V400R004_FillVdmMemElement(SINT32 ChanID, VDMHAL_MEM_ARRANGE_S *pVdmMemArrange)
  功能    在已经分配好的空间中填充内存元素
  参数    ChanID 通道号
  pVdmMemArrange  VDM各个内存元素的空间划分
  返回值  成功返回OK（0），否则返回错误码
 ******************************************************************************************/
static UINT32 VDMHAL_V400R004_CalcFsSize_l (SINT32 ChanID, SINT32 Width, SINT32 Height, VID_STD_E VidStd, SINT32* decSize, SINT32* pmvSize, SINT32* stride)
{
    SINT32 ImgWidthInMb;
    SINT32 ImgHeightInMb;
    SINT32 ImgHeightInPixAln;
    SINT32 ColMbSize;
    SINT32 PmvSlotLen;
    SINT32 SlotWidth;
    SINT32 ImgSlotLen;

    VDMHAL_ASSERT_RET(Width >= 32 && Width <= MAX_HOR_SIZE && \
                     Height >= 32 && Height <= MAX_VER_SIZE,  \
                     "image size out of range");

    /*计算PMV大小*/
    ImgWidthInMb  = (Width + 15) >> 4;
    ImgHeightInMb = (Height + 15) >> 4;
    ImgHeightInPixAln   =  ((ImgHeightInMb + 1) / 2) * 2 * 16;

    if((ImgWidthInMb <= 45) && (ImgHeightInMb <= 36))
    {
        ColMbSize = 16 * 4;  //ONEMB_V200_PMV_COLMB_ADDR_LEN;
    }
    else
    {
        ColMbSize = 8 * 4;   //ONEMB_V200_PMV_COLMB_ADDR_LEN;
    }

    if(1 == g_not_direct_8x8_inference_flag)
    {
        ColMbSize = 16 * 4;
    }

    if(VFMW_HEVC == VidStd)
	{
		ColMbSize = 4*4;
	}

    /*计算Pmv store尺寸*/
    PmvSlotLen = (ColMbSize * ImgWidthInMb * ImgHeightInMb + (2 * ALIGN_LEN - 1))  & (~(2 * ALIGN_LEN - 1));

    /*计算Frame store尺寸*/
	SlotWidth  = (Width + ((ALIGN_LEN) - 1)) & (~((ALIGN_LEN) - 1));

    /*计算Frame store尺寸*/
    ImgSlotLen = SlotWidth * ImgHeightInPixAln * 3 / 2;

    /*这里因为已经计算出来了一些帧存元素，先存储一部分*/
    memset(&(s_pstVfmwChan[ChanID]->stMemArrangeInfo), 0, sizeof(VFMW_MEM_ARRANGE_INFO_S));
    s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange.HafPmvOffset = PmvSlotLen / 2;
    s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange.VahbStride    = SlotWidth * 16 ;  // ystride x 16
    s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange.ChromOffset = SlotWidth * ImgHeightInPixAln;


    *decSize = ImgSlotLen;
    *pmvSize = PmvSlotLen;
    *stride  = SlotWidth;

    s_pstVfmwChan[ChanID]->stMemArrangeInfo.ImgSlotLen = ImgSlotLen;
    s_pstVfmwChan[ChanID]->stMemArrangeInfo.PmvSlotLen = PmvSlotLen;
	s_pstVfmwChan[ChanID]->s32RefPmvSize               = *pmvSize;

    return *decSize;
}

static SINT32 VDMHAL_V400R004_FillVdmMemElement(SINT32 ChanID, VDMHAL_MEM_ARRANGE_S *pVdmMemArrange)
{
    SINT32 s32Ret = VDMHAL_OK;
    SINT32 i = 0;
    SINT32 s32TotalFrmNum = 0;
    VDMHAL_MEM_ARRANGE_S *pstVdmMem = HI_NULL;
    UADDR  s32PhyAddr = 0;
    SINT32  ImgSlotLen = 0, PmvSlotLen = 0, s32Offset = 0;

    VDMHAL_ASSERT_RET(HI_NULL != pVdmMemArrange, "pVdmMemArrange is NULL");

    pstVdmMem = &(s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange);
    ImgSlotLen = s_pstVfmwChan[ChanID]->stMemArrangeInfo.ImgSlotLen;
    PmvSlotLen = s_pstVfmwChan[ChanID]->stMemArrangeInfo.PmvSlotLen;

    if (0 == s_pstVfmwChan[ChanID]->s32RefFrameNum)
    {
        dprint(PRN_FS, "%s, no ref frame!\n", __FUNCTION__);
    }

    if (s_pstVfmwChan[ChanID]->s32ActualFrameNum > 30)
    {
        dprint(PRN_FS, "%s, Frame number = %d > 30, Then, Frame num = 30, \n", __FUNCTION__, s_pstVfmwChan[ChanID]->s32ActualFrameNum);
        s_pstVfmwChan[ChanID]->s32ActualFrameNum = 30;
    }

    s32TotalFrmNum = s_pstVfmwChan[ChanID]->s32ActualFrameNum;
    pstVdmMem->ValidFrameNum = s32TotalFrmNum;

    for (i = 0; i < s32TotalFrmNum; i++)
    {
        s32PhyAddr = s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.PhyAddr;

        if (HI_NULL == s32PhyAddr)
        {
            break;
        }

        /*对齐*/
        s32Offset = ((s32PhyAddr + VHB_V400R004_STRIDE_BYTE - 1) & (~(VHB_V400R004_STRIDE_BYTE - 1))) - s32PhyAddr;

        /*分配Img的空间*/
        pstVdmMem->FrameAddr[i] = s32PhyAddr + s32Offset;
        s32Offset += ImgSlotLen;

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
        // 默认只要打开支持模块间低延迟就将等号所需要的内存资源分配，一个帧存只需要 32 BYTE
        pstVdmMem->LineNumAddr[i] = s32PhyAddr + s32Offset;
        s32Offset += 32;
#endif

        /*分配PMV的空间*/
        pstVdmMem->PMVAddr[i] = s32PhyAddr + s32Offset;
        s32Offset += PmvSlotLen;

        if (s32Offset > s_pstVfmwChan[ChanID]->s32RefFrameSize)
        {
            break;
        }
    }

    if (i < s32TotalFrmNum)
    {
        dprint(PRN_ERROR, "%s, FrameStore %d over bountry, Offset: 0x%x, curFsSize: 0x%x, phyadd: 0x%x\n", __FUNCTION__, i, s32Offset, \
               s_pstVfmwChan[ChanID]->s32RefFrameSize, s32PhyAddr);
        s32Ret = VDMHAL_ERR;
    }
    else
    {
        pstVdmMem->TotalMemUsed = s32TotalFrmNum * (s_pstVfmwChan[ChanID]->s32RefFrameSize);
        pstVdmMem->ValidPMVNum  = s32TotalFrmNum;
        memcpy(pVdmMemArrange, pstVdmMem, sizeof(VDMHAL_MEM_ARRANGE_S));
    }

    return s32Ret;
}

static SINT32 VDMHAL_V400R004_FillVdmMemElement_l(SINT32 ChanID, VDMHAL_MEM_ARRANGE_S *pVdmMemArrange)
{
    SINT32 s32Ret = VDMHAL_OK;
    SINT32 i = 0;
    SINT32 s32TotalFrmNum = 0;
    VDMHAL_MEM_ARRANGE_S* pstVdmMem = HI_NULL;
    UADDR  s32FrmPhyAddr = 0;
    UADDR  s32PmvPhyAddr = 0;
    SINT32 ImgSlotLen = 0;
	SINT32 PmvSlotLen = 0;
	SINT32 DecBufLen = 0;
	SINT32 PmvBufLen = 0;

    VDMHAL_ASSERT_RET(HI_NULL != pVdmMemArrange, "pVdmMemArrange is NULL");

    pstVdmMem = &(s_pstVfmwChan[ChanID]->stMemArrangeInfo.stMemArrange);
    ImgSlotLen = s_pstVfmwChan[ChanID]->stMemArrangeInfo.ImgSlotLen;
    PmvSlotLen = s_pstVfmwChan[ChanID]->stMemArrangeInfo.PmvSlotLen;

    if(0 == s_pstVfmwChan[ChanID]->s32RefFrameNum)
    {
        dprint(PRN_FS,"DFS, no ref frame!\n");
    }

    if(s_pstVfmwChan[ChanID]->s32ActualFrameNum > 30)
    {
        dprint(PRN_FS,"DFS, Frame number = %d > 30, Then, Frame num = 30, \n", s_pstVfmwChan[ChanID]->s32ActualFrameNum);
        s_pstVfmwChan[ChanID]->s32ActualFrameNum = 30;
    }

    s32TotalFrmNum = s_pstVfmwChan[ChanID]->s32ActualFrameNum;
    pstVdmMem->ValidFrameNum = s32TotalFrmNum;
    for(i = 0; i < s32TotalFrmNum; i++)
    {
        s32FrmPhyAddr = s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.PhyAddr;
		DecBufLen     = s_pstVfmwChan[ChanID]->stFrmBuf[i].stFrameBuffer.Length;

		s32PmvPhyAddr = s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.PhyAddr;
		PmvBufLen     = s_pstVfmwChan[ChanID]->stPmvBuf[i].stFrameBuffer.Length;
        if(0 == s32FrmPhyAddr || 0 == s32PmvPhyAddr)
        {
            break;
        }

        if(ImgSlotLen > DecBufLen)
        {
            dprint(PRN_ERROR, "%s dec buffer overflow %d > %d\n", __func__, ImgSlotLen, DecBufLen);
            break;
        }
        /*分配Img的空间*/
        pstVdmMem->FrameAddr[i] = s32FrmPhyAddr;

        if(PmvSlotLen > PmvBufLen)
        {
            dprint(PRN_ERROR, "%s pmv buffer overflow %d > %d\n", __func__, PmvSlotLen, PmvBufLen);
            break;
        }

        /*分配PMV的空间*/
        pstVdmMem->PMVAddr[i] = s32PmvPhyAddr;
    }

    if(i < s32TotalFrmNum)
    {
        dprint(PRN_ERROR,"%s FrameStore %d over bountry, ImgSlotLen: 0x%x, PmvSlotLen: 0x%x, FrmPhyAddr: 0x%x, PmvPhyAddr: 0x%x\n",
               __func__, i, ImgSlotLen, PmvSlotLen, s32FrmPhyAddr, s32PmvPhyAddr);
        s32Ret = VDMHAL_ERR;
    }
    else
    {
        pstVdmMem->TotalMemUsed = s32TotalFrmNum * (ImgSlotLen + PmvSlotLen);
        pstVdmMem->ValidPMVNum  = s32TotalFrmNum;
        memcpy(pVdmMemArrange, pstVdmMem, sizeof(VDMHAL_MEM_ARRANGE_S));
    }

    return s32Ret;
}


/*****************************************************************************************
  原型    SINT32 VDMHAL_V400R004_ArrangeMem( VDMHAL_MEM_ARRANGE_S *pVdmMemArrange )
  功能    划分VDM所使用的空间。
  VDM所使用的空间包括帧存、消息池、PMV信息块以及其他VDM所需要的外存区域，由于不同版本
  的VDM对外存使用的要求不同，所以将这部分划分到HAL。
  本函数只在已分配好的空间中安插各种内存元素，并不负责内存的申请和释放。
  参数    pVdmMemArrange  VDM各个内存元素的空间划分
  返回值  成功返回OK（0），否则返回错误码
 ******************************************************************************************/
SINT32 VDMHAL_V400R004_ArrangeMem( UADDR MemAddr, SINT32 MemSize, SINT32 Width, SINT32 Height, SINT32 PmvNum, SINT32 FrameNum, ARRANGE_FLAG_E eFlag, VDMHAL_MEM_ARRANGE_S *pVdmMemArrange )
{
    SINT32 i, Offset, PmvPoolSize, FramePoolSize;
    SINT32 ImgWidthInMb, ImgHeightInMb, ImgHeightInPixAln;
    SINT32 SlotWidth, PmvSlotLen, ImgSlotLen;
    SINT32 ColMbSize;
    //y00226912 新增变量
    SINT32 ChanID = -1;
    SINT32 ChanSlotLen, ChanSlotWidth;
    SINT32 ChanWidth, ChanHeight;
    SINT32 ChanImgWidthInPixAln, ChanImgHeightInPixAln;
    UINT32 Chanlevel = 16;

    SINT32 OldRefNum     = 0;
    SINT32 NewRefNum     = 0;
    SINT32 NewFrameSize  = 0;
    SINT32 OldFrameSize  = 0;
    UINT32 OldFrameWidth = 0; 
    UINT32 OldFrameHeight= 0; 
    SINT32 ret = VDMHAL_OK;
    SINT32 DecSize = 0;
    SINT32 PmvSize = 0;
	SINT32 Stride  = 0;

    VID_STD_E VidStd = VFMW_END_RESERVED;

    //开始如果不知道协议类型，则按照最大的HEVC来 申请
    if (CAP_HEVC_SPECIFIC == eFlag)
    {
        VidStd = VFMW_HEVC;
    }
    else if (eFlag >= VALID_CHAN_ID_START)
    {
        VidStd = VCTRL_GetVidStd(eFlag);
    }


    ChanID = eFlag;

    if ((ChanID >= 0) && (1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn))
    {
        OldFrameSize = s_pstVfmwChan[ChanID]->s32RefFrameSize;
        if (s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32OmxBypassMode)
        {
            NewFrameSize = VDMHAL_V400R004_CalcFsSize_l(ChanID, Width, Height, VidStd, &DecSize, &PmvSize, &Stride);
        }
        else
        {
            NewFrameSize = VDMHAL_V400R004_CalcFsSize(ChanID, Width, Height, VidStd);
        }

	    if (NewFrameSize <= 0)
	    {
	        dprint(PRN_FS, "DFS ERROR: NewFrameSize %d <= 0\n", NewFrameSize);
	    	return VDMHAL_ERR;
	    }

        //支持DPB Size变化
        OldRefNum = s_pstVfmwChan[ChanID]->s32RefFrameNum;
        NewRefNum = FrameNum;

        OldFrameWidth  = s_pstVfmwChan[ChanID]->u32CurFrameWidth;
        OldFrameHeight = s_pstVfmwChan[ChanID]->u32CurFrameHeight;

        if ((OldFrameWidth != Width) || (OldFrameHeight != Height) || (OldRefNum != NewRefNum))
        {
            dprint(PRN_ERROR, "DFS report event. Resolution: %dx%d -> %dx%d, RefNum: %d -> %d.\n", OldFrameWidth, OldFrameHeight, Width, Height, OldRefNum, NewRefNum);

            s_pstVfmwChan[ChanID]->s32RefFrameNum    = NewRefNum;
            s_pstVfmwChan[ChanID]->s32RefFrameSize   = NewFrameSize;
            
            s_pstVfmwChan[ChanID]->u32CurFrameWidth  = Width;
            s_pstVfmwChan[ChanID]->u32CurFrameHeight = Height;
            
			if(s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32OmxBypassMode)
			{
				REPORT_NEED_ARRANGE_L(ChanID, NewRefNum, DecSize, PmvSize, Width, Height, Stride);
			}
			else
            {
                REPORT_NEED_ARRANGE(ChanID, NewRefNum, NewFrameSize, Width, Height);
            }
            
            s_pstVfmwChan[ChanID]->stDynamicFSTimestamp.u32StartTime = VFMW_OSAL_GetTimeInMs();
            s_pstVfmwChan[ChanID]->FspInst.eFspPartitionState = FSP_PARTITION_STATE_WAIT;
            ret = VDMHAL_NOT_ARRANGE;
        }
        else
        {
            dprint(PRN_ERROR, "DFS fill element. Resolution: %dx%d, RefNum: %d.\n", Width, Height, NewRefNum);
    
        	if(s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32OmxBypassMode)
        	{
        		ret = VDMHAL_V400R004_FillVdmMemElement_l(ChanID, pVdmMemArrange);
        	}
			else
			{
				ret = VDMHAL_V400R004_FillVdmMemElement(ChanID, pVdmMemArrange);
			}
        }

        return ret;
    }
    else
    {
        VDMHAL_ASSERT_RET(0 != MemAddr, "VDMHAL_V400R004_ArrangeMem Mem addr is NULL");

        VDMHAL_ASSERT_RET(Width >= 32 && Width <= MAX_HOR_SIZE && Height >= 32 && Height <= MAX_VER_SIZE, "image size out of range");

        VDMHAL_ASSERT_RET(NULL != pVdmMemArrange, "'pVdmMemArrange' is NULL");
        PmvNum = MIN(20, PmvNum);

        /* clear, and set overall info */
        memset(pVdmMemArrange, 0, sizeof(VDMHAL_MEM_ARRANGE_S));

        /*------------------- 1. 尝试分配PMV，然后用剩下的空间动态分配物理帧存. --------------------*/
        ImgWidthInMb  = (Width + 15) >> 4;
        ImgHeightInMb = (Height + 15) >> 4;
        ImgHeightInPixAln   =  ((ImgHeightInMb + 1) / 2) * 2 * 16;

        if ( (ImgWidthInMb <= 45) && (ImgHeightInMb <= 36) )
        {
            ColMbSize = 16 * 4; //ONEMB_V200_PMV_COLMB_ADDR_LEN;
        }
        else
        {
            ColMbSize = 8 * 4; //ONEMB_V200_PMV_COLMB_ADDR_LEN;
        }

        if (1 == g_not_direct_8x8_inference_flag)
        {
            ColMbSize = 16 * 4;
        }

        if (VidStd == VFMW_HEVC)
        {
            ColMbSize = 4 * 4;
        }

        PmvSlotLen = ( ColMbSize * ImgWidthInMb * ImgHeightInMb + (ALIGN_LEN - 1)) & (~(ALIGN_LEN - 1));

        PmvPoolSize = (PmvSlotLen * PmvNum);
        VDMHAL_ASSERT_RET(PmvPoolSize < MemSize, "MemSize not enough for pmv slot");
        pVdmMemArrange->HafPmvOffset = PmvSlotLen / 2;
        pVdmMemArrange->ValidPMVNum = PmvNum;

        /*---------- 2. 在mem头部开始动态分配物理帧存，可用容量为MemSize－PmvSize-align. -----------*/
        Offset = ((MemAddr + VHB_V400R004_STRIDE_BYTE - 1) & (~(VHB_V400R004_STRIDE_BYTE - 1))) - MemAddr;
        FramePoolSize = MemSize - PmvPoolSize - Offset;

        SlotWidth  = (Width + ((ALIGN_LEN) - 1)) & (~((ALIGN_LEN) - 1));

        pVdmMemArrange->VahbStride = SlotWidth * 16 ; // ystride x 16

        /*计算Frame store尺寸*/
        ImgSlotLen = SlotWidth * ImgHeightInPixAln * 3 / 2;

        /* 检测图像分配帧存是否越界，和通道最大支持帧存比较 */
        /* 传入通道id 有效才执行，不是每次进入该函数均会检测 */
        if (eFlag >= VALID_CHAN_ID_START)
        {
            ChanID = eFlag;
            ChanWidth = VCTRL_GetChanWidth(ChanID);
            ChanHeight = VCTRL_GetChanHeight(ChanID);

            if (VCTRL_ERR == ChanWidth || VCTRL_ERR == ChanHeight )
            {
                dprint(PRN_FATAL, "VDMHAL_V400R004_ArrangeMem get ChanWidth/ChanHeight failed!\n");
                return VDMHAL_ERR;
            }

            ChanImgWidthInPixAln  = ((ChanWidth + 15) >> 4) * 16;
            ChanImgHeightInPixAln = ((ChanHeight + 15) >> 4) * 16;

            ChanSlotWidth  = (ChanImgWidthInPixAln + ((4 * ALIGN_LEN) - 1)) & (~((4 * ALIGN_LEN) - 1));

            if (ChanImgWidthInPixAln > 0 && ChanImgWidthInPixAln <= 2048)
            {
                Chanlevel = 16;
            }
            else if (ChanImgWidthInPixAln > 2048 && ChanImgWidthInPixAln <= 4096)
            {
                Chanlevel = 32;
            }
            else if (ChanImgWidthInPixAln > 4096 && ChanImgWidthInPixAln <= 6144)
            {
                Chanlevel = 48;
            }
            else if (ChanImgWidthInPixAln > 6144 && ChanImgWidthInPixAln <= 8192)
            {
                Chanlevel = 64;
            }

            ChanSlotLen = ((ChanSlotWidth) * ((ChanImgHeightInPixAln + 31) / 32) * 32 * 3) / 2 +  Chanlevel * ((ChanImgHeightInPixAln + 31) / 32) * 32 * 3 / 2;

            VDMHAL_ASSERT_RET(ImgSlotLen <= ChanSlotLen, "ImgSlotLen > ChanSlotLen");
        }

        pVdmMemArrange->ChromOffset = SlotWidth * ImgHeightInPixAln;
			
        if (0 == FrameNum)
        {
            //pVdmMemArrange->ValidFrameNum = MIN(MAX_FRAME_NUM, FramePoolSize/ImgSlotLen);
            pVdmMemArrange->ValidFrameNum = 0;
        }
        else
        {
            pVdmMemArrange->ValidFrameNum = MIN( MIN(MAX_FRAME_NUM, FramePoolSize / ImgSlotLen), FrameNum );
        }

        VDMHAL_ASSERT_RET(0 != pVdmMemArrange->ValidFrameNum, "cann't allocate img slot");

        for (i = 0; i < pVdmMemArrange->ValidFrameNum; i++)
        {
            pVdmMemArrange->FrameAddr[i] = MemAddr + Offset + i * ImgSlotLen;
        }

        Offset += (pVdmMemArrange->ValidFrameNum * ImgSlotLen);
        
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
        // 默认只要打开支持模块间低延迟就将等号所需要的内存资源分配，一个帧存只需要 32 BYTE
        for (i = 0; i < pVdmMemArrange->ValidFrameNum; i++)
        {
            pVdmMemArrange->LineNumAddr[i] = MemAddr + Offset + i * 32;
        }

        Offset += (pVdmMemArrange->ValidFrameNum * 32);
#endif

        /*-------------------- 3. 把PMV的偏移地址转换成绝对地址，接在帧存池之后. --------------------*/
        MemAddr += Offset;

        for ( i = 0; i < pVdmMemArrange->ValidPMVNum; i++ )
        {
            pVdmMemArrange->PMVAddr[i] = MemAddr + i * PmvSlotLen;
        }

        pVdmMemArrange->TotalMemUsed = Offset + PmvSlotLen * pVdmMemArrange->ValidPMVNum;

        return VDMHAL_OK;
    }
}


/*****************************************************************************************
  原型    VOID VDMHAL_V400R004_ResetVdm( VOID )
  功能    复位视频解码单元（VDM）
  这里的VDM指的是广义的视频解码加速模块，并不局限于VDMV20，VDMV300等IP
  参数    无
  返回值  无
 ******************************************************************************************/
VOID VDMHAL_V400R004_ResetVdm( SINT32 VdhId)
{
    SINT32 i;
    SINT32 tmp = 0;
    UINT32 reg;
    UINT32 reg_rst_ok;
    UINT32 *pVdmResetVirAddr, *pVdmResetOkVirAddr;

    pVdmResetVirAddr   = (SINT32 *)MEM_Phy2Vir(gSOFTRST_REQ_Addr);
    pVdmResetOkVirAddr = (SINT32 *)MEM_Phy2Vir(gSOFTRST_OK_ADDR);

    if ( NULL == pVdmResetVirAddr  || NULL == pVdmResetOkVirAddr)
    {
        dprint(PRN_FATAL, "VDMHAL_V400R004_ResetVdm: map vdm register fail, vir(pVdmResetVirAddr) = (%p), vir(pVdmResetOkVirAddr) = (%p)\n",
               pVdmResetVirAddr, pVdmResetOkVirAddr);
        return;
    }
	
    RD_VREG( VREG_V400R004_INT_MASK, tmp, VdhId );
	
    /* require mfde reset */
    reg = *(volatile UINT32 *)pVdmResetVirAddr;
    *(volatile UINT32 *)pVdmResetVirAddr = reg | (UINT32)(1 << MFDE_RESET_CTRL_BIT);


    /* wait for reset ok */
    for (i = 0; i < 100; i++)
    {
        reg_rst_ok = *(volatile UINT32 *)pVdmResetOkVirAddr;
        if ( reg_rst_ok & (1 <<MFDE_RESET_OK_BIT))
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
    *(volatile UINT32 *)pVdmResetVirAddr = reg & (UINT32)(~(1 << MFDE_RESET_CTRL_BIT));

    /* 为了实现互斥功能，VDM中断使能在复位后的值保持复位前相同 */
    WR_VREG( VREG_V400R004_INT_MASK, tmp, VdhId );

    return;
}


VOID VDMHAL_V400R004_GlbReset( VOID )
{
    SINT32 i;
    UINT32 reg, reg_rst_ok;
    UINT32 *pResetVirAddr = NULL;
    UINT32 *pResetOKVirAddr = NULL;

    pResetVirAddr   = (SINT32 *)MEM_Phy2Vir(gSOFTRST_REQ_Addr);
    pResetOKVirAddr = (SINT32 *)MEM_Phy2Vir(gSOFTRST_OK_ADDR);

    if ( NULL == pResetVirAddr  || NULL == pResetOKVirAddr)
    {
        dprint(PRN_FATAL, "VDMHAL_V400R004_GlbReset: map vdm register fail, vir(pResetVirAddr) = (%p), vir(pResetOKVirAddr) = (%p)\n",
               pResetVirAddr, pResetOKVirAddr);
        return;
    }

    /* require all reset, include mfde scd bpd */
    reg = *(volatile UINT32 *)pResetVirAddr;
    *(volatile UINT32 *)pResetVirAddr = reg | (UINT32)(1 << ALL_RESET_CTRL_BIT);

    /* wait for reset ok */
    for (i = 0; i < 100; i++)
    {
        reg_rst_ok = *(volatile UINT32 *)pResetOKVirAddr;
        if ( reg_rst_ok & (1 << ALL_RESET_OK_BIT))
        {
            break;
        }	
        VFMW_OSAL_uDelay(10);
    }	
	
    if (i >= 100)
    {
        dprint(PRN_FATAL, "Glb Reset Failed!!!\n");
    }
    else
    {
        //dprint(PRN_ALWS, "Glb Reset Success!\n");
    }

    /* clear reset require */
    *(volatile UINT32 *)pResetVirAddr = reg & (UINT32)(~(1 << ALL_RESET_CTRL_BIT));

    // temperory, we can not use default mfde clk en value for now. 
    //WR_VREG( VREG_V400R004_CRG_CLK_EN,  CRG_CLK_EN_DEFAULT_VALUE,  0 );
    //WR_VREG( VREG_V400R004_MFDE_CLK_EN, MFDE_CLK_EN_DEFAULT_VALUE, 0 );
	
#ifdef HIVDEC_SMMU_SUPPORT
    // initialize smmu common and master registers
    SMMU_InitGlobalReg();
#endif

    return;
	
}

VOID VDMHAL_V400R004_ClearIntState( SINT32 VdhId )
{
    SINT32 *p32;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    SINT32 dat;
    SINT32 ChanId = g_VdmDrvParam[VdhId].ChanId;
    SINT32 ModuleLowlyEnable = 0;
#endif

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return ;
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
            return;
        }
    }

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (NULL != s_pstVfmwChan[ChanId])
    {
        ModuleLowlyEnable = s_pstVfmwChan[ChanId]->stSynExtraData.s32ModuleLowlyEnable;
    }
    else
    {
        ModuleLowlyEnable = 0;
    }
    
    if (1 == ModuleLowlyEnable)
    {
        if (1 == g_VdmDrvParam[VdhId].ChanIntState)
        {
            WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );
        }
        else
        {
            // 清除中断
            RD_VREG( VREG_V400R004_VDH_STATE, dat, VdhId );

            //如果是行号中断则清行号中断
            if (2 == g_VdmDrvParam[VdhId].ChanIntState)
            {
                WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFF4, VdhId );
            }
            //如果是解码完成中断则清解码完成中断
            else if (3 == g_VdmDrvParam[VdhId].ChanIntState )
            {
                WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFF1, VdhId );
            }
        }
    }
    else
    {
        WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );
    }

#else
    // 清除中断
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );
#endif

    return;
}

VOID VDMHAL_V400R004_MaskInt( SINT32 VdhId )
{
    SINT32 *p32 = NULL;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return ;
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
            return;
        }
    }

    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFF, VdhId );

    return;
}

VOID VDMHAL_V400R004_EnableInt( SINT32 VdhId )
{
    SINT32 *p32 = NULL;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    SINT32 ChanId = g_VdmDrvParam[VdhId].ChanId;
    SINT32 ModuleLowlyEnable = 0;
#endif
    
#ifdef VDM_BUSY_WAITTING
    return;
#endif

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return ;
    }

    if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr)) )
    {
        g_HwMem[VdhId].pVdmRegVirAddr = p32;
    }
    else
    {
        dprint(PRN_FATAL, " %s %d vdm register virtual address not mapped, reset failed! vdm_reg_phy_addr:%#x\n", __func__, __LINE__, gVdhRegBaseAddr);
        return;
    }

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (NULL != s_pstVfmwChan[ChanId])
    {
        ModuleLowlyEnable = s_pstVfmwChan[ChanId]->stSynExtraData.s32ModuleLowlyEnable;
        //fordsp 0xFFFFFFFa能上报行号中断
        if (1 == ModuleLowlyEnable)
        {
            WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFA, VdhId );
        }
        else
        {
            WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFE, VdhId );
        }
    }
    else
    {
        dprint(PRN_FATAL, "Function: %s\tLine: %d\tNULL == s_pstVfmwChan[ChanId]\n", __FUNCTION__, __LINE__);
        return;
    }
#else
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFE, VdhId );
#endif

    return;
}

SINT32 VDMHAL_V400R004_CheckReg(REG_ID_E reg_id, SINT32 VdhId)
{
    SINT32 *p32;
    SINT32 dat = 0;
    UINT32 reg_type;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) Invalid!\n", __func__, VdhId);
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
            return 0;
        }
    }

    switch (reg_id)
    {
        case VDH_STATE_REG:
            reg_type = VREG_V400R004_VDH_STATE;
            break;

        case INT_STATE_REG:
            reg_type = VREG_V400R004_INT_STATE;
            break;

        case INT_MASK_REG:
            reg_type = VREG_V400R004_INT_MASK;
            break;

        case VCTRL_STATE_REG:
            reg_type = VREG_V400R004_VCTRL_STATE;
            break;

        default:
            dprint(PRN_FATAL, "%s: unkown reg_id = %d\n", __func__, reg_id);
            return 0;
    }

    RD_VREG(reg_type, dat, VdhId);

    return dat;
}

/*****************************************************************************************
  原型    SINT32 VDMHAL_V400R004_PrepareDec( VID_STD_E VidStd, VOID *pDecParam )
  功能    将一组参数配置到寄存器和消息池并启动解码
  在h.264协议下slice参数个数可能很多，但硬件的消息池槽位数目是有限的，所以一次硬件
  "解码"的slice个数应该由HAL的调用者保证不超过slice槽位总数。如果超过，HAL会把超过的slice丢弃。
  参数    VidStd  视频协议类型
  pDecParam   解码参数结构，与协议类型相关。
  举例，在MPEG2协议下，pDecParam指向MP2_DEC_PARAM_S结构，在H264协议下，指向H264_DEC_PARAM_S结构，
  至于slice参数，是在H264_DEC_PARAM_S中链接的。
  返回值  成功返回VDMHAL_OK,否则返回错误码
 ******************************************************************************************/
SINT32 VDMHAL_V400R004_PrepareDec( VID_STD_E VidStd, VOID *pDecParam, SINT32 VdhId )
{
    //    SINT32 D32;
    if (pDecParam == NULL)
    { 
        return VDMHAL_ERR; 
    }

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    if (VFMW_AVS == VidStd)
    {
        WR_SCDREG(REG_AVS_FLAG, 0x00000001);//0xf8c3c000
    }
    else
    {
        WR_SCDREG(REG_AVS_FLAG, 0x00000000);//0xf8c3c000
    }

    /*开启VDH自复位*/
    WR_SCDREG(REG_VDH_SELRST, 0x00000001);

    switch (VidStd)
    {
#ifdef VFMW_H264_SUPPORT

        case VFMW_H264:
            return H264HAL_V400R004_StartDec( (H264_DEC_PIC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_HEVC_SUPPORT

        case VFMW_HEVC:
            return HEVCHAL_V400R004_StartDec( (HEVC_DEC_PIC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_MPEG2_SUPPORT

        case VFMW_MPEG2:
            return MP2HAL_V400R004_StartDec( (MP2_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_MPEG4_SUPPORT

        case VFMW_MPEG4:
            return MP4HAL_V400R004_StartDec( (MP4_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_AVS_SUPPORT

        case VFMW_AVS:
            return AVSHAL_V400R004_StartDec( (AVS_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_REAL8_SUPPORT

        case VFMW_REAL8:
            return RV8HAL_V400R004_StartDec( (RV8_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_REAL9_SUPPORT

        case VFMW_REAL9:
            return RV9HAL_V400R004_StartDec( (RV9_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_DIVX3_SUPPORT

        case VFMW_DIVX3:
            return DIVX3HAL_V400R004_StartDec( (DIVX3_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_VC1_SUPPORT

        case VFMW_VC1:
            return VC1HAL_V400R004_StartDec( (VC1_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_VP6_SUPPORT

        case VFMW_VP6:
        case VFMW_VP6A:
        case VFMW_VP6F:
            return VP6HAL_V400R004_StartDec( (VP6_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_VP8_SUPPORT

        case VFMW_VP8:
            return VP8HAL_V400R004_StartDec( (VP8_DEC_PARAM_S *)pDecParam, VdhId );
            break;
#endif
#ifdef VFMW_MVC_SUPPORT

        case VFMW_MVC:
            return H264HAL_V400R004_StartDec( (H264_DEC_PIC_PARAM_S *)pDecParam, VdhId );
            break;
#endif

        default:
            break;
    }

    return VDMHAL_ERR;
}


/*****************************************************************************************
  原型    SINT32 VDMHAL_V400R004_IsVdmReady( )
  功能    检查VDM是否ready
  参数    无

  返回值  类布尔数据，1表示VDM已经ready，反之返回0
 ******************************************************************************************/
SINT32 VDMHAL_V400R004_IsVdmReady(SINT32 VdhId)
{
    SINT32 Data32 = 0;

    VDMHAL_ASSERT_RET( g_HwMem[VdhId].pVdmRegVirAddr != NULL, "VDM register not mapped yet!" );

    RD_VREG(VREG_V400R004_VDH_STATE, Data32, VdhId);

    Data32 = (Data32 >> 17) & 1;
    Data32 = (Data32 == 0) ? 0 : 1;

    return Data32;
}

SINT32 VDMHAL_V400R004_IsVdmRun(SINT32 VdhId)
{
    SINT32 Data32 = 0;

    if ( g_HwMem[VdhId].pVdmRegVirAddr == NULL)
    {
        dprint(PRN_FATAL, "VDM register not mapped yet!\n" );
        return 0;
    }

    RD_VREG(VREG_V400R004_VCTRL_STATE, Data32, VdhId);

    if (Data32 == 1)
    {
        return 0;
    }
    else
    {
        return 1;//work
    }
}

SINT32 VDMHAL_V400R004_BackupInfo(BACKUP_INFO_S *pBackUpInfo)
{
    SINT32 *p32;
    SINT32 i = 0;
    VDMHAL_HWMEM_S *pHwMem = NULL;
    UADDR  UpMsgPhyAddr;
    UINT32 DecSliceNum;
    SINT32 *pMsgBase;
    SINT32 LowdlyFlag = 0;
    UINT32 *pMb0QpInCurrPic, VdhId;

    VDMHAL_ASSERT_RET(pBackUpInfo != NULL, "pBackUpInfo = NULL!" );
    pMb0QpInCurrPic = pBackUpInfo->pMb0QpInCurrPic;
    VdhId           = pBackUpInfo->VdhId;
    pHwMem          = &(g_HwMem[VdhId]);

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }
    
    // 只要有一个通道开启SCD低延迟，则将LowdlyFlag置为1，有些寄存器将不
    // 不再可信, 需要读取上行消息
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (DSP_STATE_SCDLOWDLY == g_DSPState[i])
        {
            LowdlyFlag = 1;
            break;
        }
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

    // Read Regs
    RD_VREG( VREG_V400R004_BASIC_CFG1, g_BackUp[VdhId].BasicCfg1, VdhId );
    RD_VREG( VREG_V400R004_VDH_STATE, g_BackUp[VdhId].VdmState, VdhId );

    if (1 == LowdlyFlag)
    {
        /* read up msg */
        DecSliceNum = (g_BackUp[VdhId].VdmState & 0x1FFFF);
        UpMsgPhyAddr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX];
        pMsgBase = (SINT32 *)MEM_Phy2Vir(UpMsgPhyAddr);
        VDMHAL_ASSERT_RET( NULL != pMsgBase , "can NOT map vir addr for up-msg");

        // DecSliceNum < 1 是为了后面的相减成负数
        if ((DecSliceNum > MAX_UP_MSG_SLICE_NUM) || (DecSliceNum < 1))
        {
            DecSliceNum = 1;
        }

        // 低延迟时需读取上行消息最后一个SLICE的第0个WORD[22:21],(上行消息最大128)
        // 00:没有错误
        // 10:码流上溢错误
        // 01:码流下溢错误
        // 11:reserved
        g_BackUp[VdhId].SedSta = *(pMsgBase + (DecSliceNum - 1) * 4);

        // 结束宏块号可从上行消息，第2个word [19:0]获得
        // 目前该参数没有用到
        g_BackUp[VdhId].SedEnd0 = *(pMsgBase + (DecSliceNum - 1) * 4 + 2);
    }
    else
    {
        RD_VREG( VREG_V400R004_SED_STA, g_BackUp[VdhId].SedSta, VdhId );
        RD_VREG( VREG_V400R004_SED_END0, g_BackUp[VdhId].SedEnd0, VdhId );
    }

    RD_VREG( VREG_V400R004_MB0_QP_IN_CURR_PIC, g_BackUp[VdhId].Mb0QpInCurrPic, VdhId );
    RD_VREG( VREG_V400R004_SWITCH_ROUNDING, g_BackUp[VdhId].SwitchRounding, VdhId );

    // 低延迟下面五个不可回读
    if (0 == LowdlyFlag)
    {
        RD_VREG(VREG_V400R004_DEC_CYCLEPERPIC, g_BackUp[VdhId].DecCyclePerPic, VdhId );
        RD_VREG(VREG_V400R004_RD_BDWIDTH_PERPIC, g_BackUp[VdhId].RdBdwidthPerPic, VdhId );
        RD_VREG(VREG_V400R004_WR_BDWIDTH_PERPIC, g_BackUp[VdhId].WrBdWidthPerPic, VdhId );
        RD_VREG(VREG_V400R004_RD_REQ_PERPIC, g_BackUp[VdhId].RdReqPerPic, VdhId );
        RD_VREG(VREG_V400R004_WR_REQ_PERPIC, g_BackUp[VdhId].WrReqPerPic, VdhId );
    }

    for (i = 0; i < 32; i++)
    {
        RD_VREG( VREG_V400R004_LUMA_HISTORGRAM + i * 4, g_BackUp[VdhId].LumaHistorgam[i], VdhId );
    }

    // 低延迟下面两个不可回读
    if (0 == LowdlyFlag)
    {
        RD_VREG( VREG_V400R004_LUMA_SUM_LOW, g_BackUp[VdhId].LumaSumLow, VdhId );
        RD_VREG( VREG_V400R004_LUMA_SUM_HIGH, g_BackUp[VdhId].LumaSumHigh, VdhId );
    }

    if ( VFMW_DIVX3 == (g_BackUp[VdhId].BasicCfg1 & 0x0F) )
    {
        *pMb0QpInCurrPic = g_BackUp[VdhId].SwitchRounding & 0x01;  //use 'Mb0QpInCurrPic' to store 'SwitchRounding'
    }
    else
    {
        *pMb0QpInCurrPic = g_BackUp[VdhId].Mb0QpInCurrPic & 0x1F;
    }

    return VDMHAL_OK;
}


SINT32 VDMHAL_V400R004_ReadMsgSlot(SINT32 *pDst, SINT32 *pSrc, UINT32 upmsg_size)
{
    if ((NULL == pDst) || (NULL == pSrc))
    {
        dprint(PRN_FATAL, "ReadUpMsgSlot error! pDst=%p, pSrc=%p\n", pDst, pSrc);
        return VDMHAL_ERR;
    }

    if (upmsg_size > UP_MSG_SIZE)
    {
        dprint(PRN_FATAL, "ReadUpMsgSlot error! upmsg_size(%d) > 512\n", upmsg_size);
        return VDMHAL_ERR;
    }

    memcpy( pDst, pSrc, upmsg_size << 2 );

    return VDMHAL_OK;
}


SINT32 VDMHAL_V400R004_WriteMsgSlot(SINT32 *pDst, SINT32 *pSrc, UINT32 dnmsg_size)
{
    if ( (NULL == pDst) || (NULL == pSrc) || (0 == dnmsg_size) || (dnmsg_size > MSG_SLOT_SIZE))
    {
        dprint(PRN_FATAL, "WriteMsgSlot error!\n");
        return VDMHAL_ERR;
    }

    memcpy( pDst, pSrc, dnmsg_size << 2 );

    return VDMHAL_OK;
}


SINT32 VDMHAL_V400R004_CfgRpMsg(VDMHAL_REPAIR_PARAM_S *pRepairParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId)
{
    SINT32 *pMsgBase;
    UINT32 D32;
    SINT32 i;
    UINT32 align_mb = 0;
    SINT32 pic_width, pic_height, SlotWidth, Stride1D, ChromaOffset, HeadInfOffset;
    SINT32 cur_EndMb = 0, cur_StartMb = 0, front_StartMb = 0, front_EndMb = 0;
    SINT32 start_Mb = 0, end_Mb = 0;
    SINT32 max_repairTime = 0, actual_repairTime = 0;
    SINT32 ImgHeightInMb;
    SINT32 ImgHeightInPixAln;
    UINT32 fld_image_w, fld_image_h;

    pMsgBase = (SINT32 *)MEM_Phy2Vir(pHwMem->MsgSlotAddr[RP_V400R004_MSG_SLOT_INDEX]);
    VDMHAL_ASSERT_RET( NULL != pMsgBase , "can not map repair msg virtual address!");

    if ( (pRepairParam->ValidGroupNum <= 0) || (pRepairParam->ValidGroupNum > MAX_UP_MSG_SLICE_NUM) )
    {
        dprint(PRN_FATAL, "ValidGroupNum=%d out of range!\n", pRepairParam->ValidGroupNum);
        return VDMHAL_ERR;
    }

    pic_width  = pRepairParam->ImageWidth * (1 << pRepairParam->CtbSize);
    pic_height = pRepairParam->ImageHeight * (1 << pRepairParam->CtbSize);

    ImgHeightInMb = (pic_height + 15) >> 4;
    ImgHeightInPixAln   =  ((ImgHeightInMb + 1) / 2) * 2 * 16;

    SlotWidth  = (pic_width + (ALIGN_LEN - 1)) & (~(ALIGN_LEN- 1));

    Stride1D = SlotWidth;

    ChromaOffset = SlotWidth * ImgHeightInPixAln;
    HeadInfOffset = 0; 

    D32 = 0;
    ((VDMRPMSG_V400R004_D0 *)(&D32))->src_luma_addr = pRepairParam->RefImageAddr;
    WR_MSGWORD( pMsgBase, D32);
    dprint(PRN_VDMREG, "repair: src_luma_addr = 0x%x\n", D32);
        
    D32 = 0;
    ((VDMRPMSG_V400R004_D1 *)(&D32))->src_chroma_addr = pRepairParam->RefImageAddr + ChromaOffset;
    WR_MSGWORD( pMsgBase + 1, D32);
    dprint(PRN_VDMREG, "repair: src_chroma_addr = 0x%x\n", D32);

    D32 = 0;
    ((VDMRPMSG_V400R004_D2 *)(&D32))->dst_luma_addr = pRepairParam->ImageAddr;
    WR_MSGWORD( pMsgBase + 2, D32);
    dprint(PRN_VDMREG, "repair: dst_luma_addr = 0x%x\n", D32);

    D32 = 0;
    ((VDMRPMSG_V400R004_D3 *)(&D32))->dst_chroma_addr = pRepairParam->ImageAddr + ChromaOffset;
    WR_MSGWORD( pMsgBase + 3, D32);
    dprint(PRN_VDMREG, "repair: dst_chroma_addr = 0x%x\n", D32);

    D32 = 0;
    ((VDMRPMSG_V400R004_D4 *)(&D32))->stride_1d = Stride1D;
    WR_MSGWORD( pMsgBase + 4, D32);
    dprint(PRN_VDMREG, "repair: stride_1d = 0x%x\n", D32);

    D32 = 0;
    ((VDMRPMSG_V400R004_D5 *)(&D32))->headInfOffset = HeadInfOffset;
    WR_MSGWORD( pMsgBase + 5, D32);
    dprint(PRN_VDMREG, "repair: headInfOffset = 0x%x\n", D32);

    D32 = 0;
    ((VDMRPMSG_V400R004_D6 *)(&D32))->pic_width_in_mb = (pRepairParam->ImageWidth) - 1;
    ((VDMRPMSG_V400R004_D6 *)(&D32))->pic_height_in_mb = (pRepairParam->ImageHeight) - 1;
    WR_MSGWORD( pMsgBase + 6, D32);
    dprint(PRN_VDMREG, "repair: pic_width_in_mb = 0x%x\n",  (pRepairParam->ImageWidth) - 1);
    dprint(PRN_VDMREG, "repair: pic_height_in_mb = 0x%x\n", (pRepairParam->ImageHeight) - 1);

    fld_image_w = pRepairParam->ImageWidth;
    fld_image_h = (1 == pRepairParam->Pic_type || 2 == pRepairParam->Pic_type)? pRepairParam->ImageHeight/2: pRepairParam->ImageHeight;

    /*计算一个最大的修补次数，当修补次数要超过最大次数的时候就将修补变成整帧修补*/
    max_repairTime = (RP_V400R004_MSG_SLOT_NUM * MSG_SLOT_SIZE - 8) / 2;

    if (pRepairParam->CtbSize == 6)
    {
        align_mb = 2;
    }
    else if (pRepairParam->CtbSize == 5)
    {
        align_mb = 4;
    }
    else if (pRepairParam->CtbSize == 4)
    {
        align_mb = 8;
    }
    else
    {
        align_mb = 1;
        dprint(PRN_ERROR, "%s CtbSize %d align_mb error\n", __func__, pRepairParam->CtbSize);
    }
    
    if (0 == pRepairParam->FullRepair)
    {
        for (i = 0; i < pRepairParam->ValidGroupNum; i++)
        {
            //8mb(宏块)对齐，其实宏块向前移动，结束宏块向后移动
            cur_StartMb = (pRepairParam->MbGroup[i].StartMbn) / align_mb * align_mb;
            cur_EndMb = (pRepairParam->MbGroup[i].EndMbn + align_mb - 1) / align_mb * align_mb;

            if (i > 0)
            {
                front_StartMb = (pRepairParam->MbGroup[i - 1].StartMbn) / align_mb * align_mb;
                front_EndMb = (pRepairParam->MbGroup[i - 1].EndMbn + align_mb - 1) / align_mb * align_mb;
            }

            if (i != 0 && (cur_EndMb <= front_EndMb))
            {
                /*如果当前修补的结束宏块号小于等于上次的结束宏块好，则不进行本次修补*/
                continue;
            }

            start_Mb = cur_StartMb;

            if (i > 0)
            {
                /*如果下次的修补和本次修补的宏块有重叠或者下次修补紧邻本次修补，那么将本次修补和下次修补在下次一起修补，不启动本次修补*/
                while ((i + 1 < pRepairParam->ValidGroupNum ) && ((pRepairParam->MbGroup[i].EndMbn + align_mb - 1) / align_mb * align_mb > (pRepairParam->MbGroup[i + 1].StartMbn) / align_mb * align_mb
                        || (pRepairParam->MbGroup[i].EndMbn + align_mb - 1) / align_mb * align_mb == ((pRepairParam->MbGroup[i + 1].StartMbn) / align_mb * align_mb + 1)
                        || (pRepairParam->MbGroup[i].EndMbn + align_mb - 1) / align_mb * align_mb <= (pRepairParam->MbGroup[i - 1].EndMbn + align_mb - 1) / align_mb * align_mb))
                {
                    i++;
                }
            }

            end_Mb = (pRepairParam->MbGroup[i].EndMbn + align_mb - 1) / align_mb * align_mb;

            if (end_Mb >= fld_image_w * fld_image_h)
            {
                end_Mb = fld_image_w * fld_image_h - 1;
            }

            if (start_Mb > end_Mb)
            {
                start_Mb = end_Mb;
            }

            actual_repairTime ++;

            /*如果修补次数超过了最大修补次数，则变为整帧修补*/
            if (actual_repairTime > max_repairTime)
            {
                pRepairParam->FullRepair = 1;
                break;
            }

            D32 = 0;
            ((VDMRPMSG_V400R004_D8 *)(&D32))->start_mbx = start_Mb % fld_image_w;
            ((VDMRPMSG_V400R004_D8 *)(&D32))->start_mby = start_Mb / fld_image_w;
            WR_MSGWORD( pMsgBase + 2 * (actual_repairTime - 1) + 8, D32);
            dprint(PRN_VDMREG, "repair: start_mbx = 0x%x\n", start_Mb % fld_image_w);
            dprint(PRN_VDMREG, "repair: start_mby = 0x%x\n", start_Mb / fld_image_w);
    
            D32 = 0;
            ((VDMRPMSG_V400R004_D9 *)(&D32))->end_mbx = (end_Mb) % fld_image_w;
            ((VDMRPMSG_V400R004_D9 *)(&D32))->end_mby = (end_Mb) / fld_image_w;
            WR_MSGWORD( pMsgBase + 2 * (actual_repairTime - 1) + 9, D32);
            dprint(PRN_VDMREG, "repair: end_mbx = 0x%x\n", (end_Mb) % fld_image_w);
            dprint(PRN_VDMREG, "repair: end_mby = 0x%x\n", (end_Mb) / fld_image_w);
        }
    }

    if ( 1 == pRepairParam->FullRepair)
    {
        pRepairParam->ValidGroupNum  = 1;
        actual_repairTime = pRepairParam->ValidGroupNum;

        D32 = 0;
        ((VDMRPMSG_V400R004_D8 *)(&D32))->start_mbx = 0;
        ((VDMRPMSG_V400R004_D8 *)(&D32))->start_mby = 0;
        WR_MSGWORD( pMsgBase + 8, D32);
        dprint(PRN_VDMREG, "repair: start_mbx = 0x%x\n", 0);
        dprint(PRN_VDMREG, "repair: start_mby = 0x%x\n", 0);

        D32 = 0;
        ((VDMRPMSG_V400R004_D9 *)(&D32))->end_mbx = fld_image_w - 1;
        ((VDMRPMSG_V400R004_D9 *)(&D32))->end_mby = fld_image_h - 1;
        WR_MSGWORD( pMsgBase + 9, D32);
        dprint(PRN_VDMREG, "repair: end_mbx = 0x%x\n", fld_image_w - 1);
        dprint(PRN_VDMREG, "repair: end_mby = 0x%x\n", fld_image_h - 1);
    }

    ((VDMRPMSG_V400R004_D7 *)(&D32))->total_grp_num_minus1 = actual_repairTime - 1;
    ((VDMRPMSG_V400R004_D7 *)(&D32))->compress_flag = pRepairParam->Compress_en;
    ((VDMRPMSG_V400R004_D7 *)(&D32))->dst_store_mode = pRepairParam->Pic_type;
    ((VDMRPMSG_V400R004_D7 *)(&D32))->src_load_mode = pRepairParam->Pic_type;
    ((VDMRPMSG_V400R004_D7 *)(&D32))->ctb_size = pRepairParam->CtbSize - 4;
    WR_MSGWORD( pMsgBase + 7, D32);
    dprint(PRN_VDMREG, "repair: total_grp_num_minus1 = 0x%x\n", actual_repairTime - 1);
    dprint(PRN_VDMREG, "repair: compress_flag = 0x%x\n", pRepairParam->Compress_en);
    dprint(PRN_VDMREG, "repair: dst_store_mode = 0x%x\n", pRepairParam->Pic_type);
    dprint(PRN_VDMREG, "repair: src_load_mode = 0x%x\n", pRepairParam->Pic_type);
    dprint(PRN_VDMREG, "repair: ctb_size = 0x%x\n", pRepairParam->CtbSize - 4);

    return VDMHAL_OK;
}


SINT32 VDMHAL_V400R004_CfgRpReg(VID_STD_E VidStd, VDMHAL_HWMEM_S *pHwMem, VOID *pDecParam, SINT32 VdhId)
{
    SINT32 *p32;
    SINT32 D32 = 0;

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

    D32 = 0;
    ((AVM_V400R004_ADDR *)(&D32))->av_msg_addr = pHwMem->MsgSlotAddr[RP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId  );
    D32 = 0x00000007;
    WR_VREG( VREG_V400R004_INT_MASK, D32, VdhId );
    D32 = 0x2000C203;
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_SED_TO, D32, VdhId );
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_ITRANS_TO, D32, VdhId );
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_PMV_TO, D32, VdhId );
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_PRC_TO, D32, VdhId );
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_RCN_TO, D32, VdhId );
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_DBLK_TO, D32, VdhId );
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_PPFD_TO, D32, VdhId );

    return VDMHAL_OK;
}

SINT32 VDMHAL_V400R004_MakeDecReport(MAKE_DEC_REPORT_S *pMakeDecReport)
{
    VDMHAL_HWMEM_S *pHwMem = NULL;
    UINT32 i, Step;
    UADDR  UpMsgPhyAddr;
    SINT32 *pMsgBase;
    SINT32 LowdlyFlag = 0;
    VID_STD_E VidStd;
    VDMHAL_DEC_REPORT_S *pDecReport;
    SINT32 VdhId;

    VDMHAL_ASSERT_RET( pMakeDecReport != NULL, "'pMakeDecReport' is NULL" );
    VidStd     = pMakeDecReport->VidStd;
    pDecReport = pMakeDecReport->pDecReport;
    VdhId      = pMakeDecReport->VdhId;
    pHwMem     = &(g_HwMem[VdhId]);
    
    VDMHAL_ASSERT_RET( pDecReport != NULL, "'pDecReport' is NULL" );
    VDMHAL_ASSERT_RET( pHwMem->pVdmRegVirAddr != NULL, "VDM register not mapped yet!" );


    // 只要有一个通道开启SCD低延迟，则将LowdlyFlag置为1，有些寄存器将不
    // 不再可信, 需要读取上行消息
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (DSP_STATE_SCDLOWDLY == g_DSPState[i])
        {
            LowdlyFlag = 1;
            break;
        }
    }

    /* clear */
    memset( pDecReport, 0, sizeof(VDMHAL_DEC_REPORT_S) );
    pDecReport->ImgStride = pHwMem->VahbStride;

    /* parse state register */
    pDecReport->RetType = (((g_BackUp[VdhId].VdmState >> 17) & 3) == 1) ? VDM_RET_RIGHT :
                          (((((g_BackUp[VdhId].VdmState >> 17) & 1) == 1) && (VFMW_MPEG2 == VidStd)) ? VDM_RET_RIGHT : VDM_RET_ERROR);
    pDecReport->DecSliceNum = (g_BackUp[VdhId].VdmState & 0x1FFFF);

    // 判断码流上溢,低延迟时需另走分支
    if ( (VFMW_H264 == VidStd) || (VFMW_MVC == VidStd) )
    {
        // 低延迟时，SedSta是通过上行消息读来了，表示上溢的BIT位不一样了[22:21]
        if (1 == LowdlyFlag)
        {
            if ( 0x02 == ( (g_BackUp[VdhId].SedSta >> 21) & 0x03 ) )
            {
                pDecReport->DecSliceNum = 1;
                pDecReport->SliceMbRange[0][0] = 0;
                pDecReport->SliceMbRange[0][1] = 0;

                return VDMHAL_OK;
            }
        }
        else
        {
            if (0 == g_not_allow_H264FullPictureRepair_flag)
            {
                if ( 0x02 == ( (g_BackUp[VdhId].SedSta >> 24) & 0x03 ) )
                {
                    pDecReport->DecSliceNum = 1;
                    pDecReport->SliceMbRange[0][0] = 0;
                    pDecReport->SliceMbRange[0][1] = 0;

                    return VDMHAL_OK;
                }
            }
        }
    }

    if ( pDecReport->DecSliceNum > MAX_UP_MSG_SLICE_NUM )
    {
        dprint(PRN_ERROR, "pDecReport->DecSliceNum(%d) > %d, set to 0 for full repair.\n", pDecReport->DecSliceNum, MAX_UP_MSG_SLICE_NUM);
        pDecReport->DecSliceNum = 0;
    }

    /* read up msg */
    UpMsgPhyAddr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX];
    pMsgBase = (SINT32 *)MEM_Phy2Vir(UpMsgPhyAddr);
    VDMHAL_ASSERT_RET( NULL != pMsgBase , "can NOT map vir addr for up-msg");

    VDMHAL_V400R004_ReadMsgSlot((SINT32 *)(&g_UpMsg[VdhId][0]), pMsgBase, 4 * pDecReport->DecSliceNum);

    Step = 4;//(VFMW_MPEG4==VidStd) ? 3: 2;  // MPEG4三个WORD描述一个slice，其余协议两个word描述一个slice //hi3531统一为4 word

    for (i = 0; i < pDecReport->DecSliceNum; i++)
    {
        pDecReport->SliceMbRange[i][0] = g_UpMsg[VdhId][i * Step + 1] & 0xFFFFF;
        pDecReport->SliceMbRange[i][1] = g_UpMsg[VdhId][i * Step + 2] & 0xFFFFF;
        //dprint(PRN_UPMSG, "\n***** UpMsg [start_mbn, end_mbn]=[%d, %d]\n", pDecReport->SliceMbRange[i][0], pDecReport->SliceMbRange[i][1]);
    }

    if (IsDprintTypeEnable(PRN_UPMSG))
    {
        UINT32 i_cnt;
        dprint(PRN_UPMSG, "\n***** UpMsg DecSliceNum=%d\n", pDecReport->DecSliceNum);
        dprint(PRN_UPMSG, "\n***** Up Msg (phy addr: %#8x) *****\n", UpMsgPhyAddr);

        for (i_cnt = 0; i_cnt < (4 * pDecReport->DecSliceNum - 3); i_cnt += 4)
        {
            dprint(PRN_UPMSG, "\n0x%02x 0x%08x 0x%08x 0x%08x 0x%08x\n",
                   i_cnt, g_UpMsg[VdhId][i_cnt], g_UpMsg[VdhId][i_cnt + 1], g_UpMsg[VdhId][i_cnt + 2], g_UpMsg[VdhId][i_cnt + 3]);
        }

        dprint(PRN_UPMSG, "\n***** Up Msg print finished *****\n");
    }

    return VDMHAL_OK;
}


/*****************************************************************************************
  原型    VOID VDMHAL_V400R004_PrepareRepair(VDMHAL_REPAIR_PARAM_S *pRepareParam)
  功能    将一组参数配置到寄存器和消息池
  参数    pRepairParam   修补参数
  返回值  无
 ******************************************************************************************/
SINT32 VDMHAL_V400R004_PrepareRepair( VID_STD_E VidStd, VOID *pDecParam, SINT32 RepairTime, SINT32 VdhId )
{
    VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][0]);
    VDMHAL_HWMEM_S *pHwMem = &(g_HwMem[VdhId]);
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
            dprint(PRN_FATAL, "vdm register virtual address not mapped, VDMHAL_V400R004_PrepareRepair failed!\n");
            return VDMHAL_ERR;
        }
    }

    if (FIRST_REPAIR == RepairTime)
    {
        if (pRepairParam->ValidGroupNum > 0)
        {
#ifdef VFMW_AVS_SUPPORT

            if (VFMW_AVS == VidStd)
            {
                VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][1]);

                if (1 == ((AVS_DEC_PARAM_S *)pDecParam)->PicStruct)
                {
                    pRepairParam->Pic_type = 1;
                }
                else
                {
                    pRepairParam->Pic_type = 0;
                }
            }

#endif
            VDMHAL_V400R004_CfgRpReg(VidStd, pHwMem, pDecParam, VdhId);
            VDMHAL_V400R004_CfgRpMsg(pRepairParam, pHwMem, VdhId);
            // Start Repair 删除，真正的启动操作放在外面，以便与VDMDRV状态机置位相配合
        }
        else
        {
            dprint(PRN_FATAL, "FIRST_REPAIR Parameter Error!\n");
            return VDMHAL_ERR;
        }
    }
    else if (SECOND_REPAIR == RepairTime)
    {
#ifdef VFMW_AVS_SUPPORT

        if ( (VFMW_AVS == VidStd) && (1 == ((AVS_DEC_PARAM_S *)pDecParam)->PicStruct) && (g_RepairParam[VdhId][1].ValidGroupNum > 0) )
        {
            VDMHAL_REPAIR_PARAM_S *pRepairParam = &(g_RepairParam[VdhId][1]);
            pRepairParam->Pic_type = 2;

            if (g_RepairParam[VdhId][1].ValidGroupNum > 0)
            {
                VDMHAL_ResetVdm(VdhId);
                VDMHAL_V400R004_CfgRpReg(VidStd, pHwMem, pDecParam, VdhId);
                VDMHAL_V400R004_CfgRpMsg(&(g_RepairParam[VdhId][1]), pHwMem, VdhId);
                // Start Repair 删除，真正的启动操作放在外面，以便与VDMDRV状态机置位相配合
            }
        }
        else
        {
            dprint(PRN_FATAL, "SECOND_REPAIR Parameter Error!\n");
            return VDMHAL_ERR;
        }

#else
        dprint(PRN_FATAL, "SECOND_REPAIR Parameter Error!\n");
        return VDMHAL_ERR;
#endif
    }

    return VDMHAL_OK;
}

VOID VDMHAL_V400R004_StartHwRepair(SINT32 VdhId)
{
    /*配置vdh的启动模式为修补模式*/
    SINT32 D32 = 0;
     
    RD_VREG(VREG_V400R004_BASIC_CFG0, D32, VdhId);
#ifdef ENV_SOS_KERNEL
    D32 = 0x84000000;  //secure repair mode
#else
    D32 = 0x4000000;   //normal repair mode
#endif 
    WR_VREG(VREG_V400R004_BASIC_CFG0, D32, VdhId); /*[27:26]	work_mode 00：解码；01：修补；10：RPR（REAL协议特有）*/

#ifdef HIVDEC_SMMU_SUPPORT
#ifdef ENV_SOS_KERNEL
    SMMU_SetMasterReg(MFDE, SECURE_ON,  SMMU_OFF);
#else
    SMMU_SetMasterReg(MFDE, SECURE_OFF, SMMU_ON);
#endif
#endif

    /*启动vdh*/
    VFMW_OSAL_Mb();
    WR_VREG( VREG_V400R004_VDH_START, 0, VdhId );
    WR_VREG( VREG_V400R004_VDH_START, 1, VdhId );
    WR_VREG( VREG_V400R004_VDH_START, 0, VdhId );

    return;
}

VOID VDMHAL_V400R004_StartHwDecode(SINT32 VdhId)
{
    SINT32 s32ChanId = 0;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return ;
    }

    /* VDH时钟门控 */
    s32ChanId = g_VdmDrvParam[VdhId].ChanId;
	
    //HiVCodecV100默认无需配置 ClockGating
    //WR_SCDREG(REG_VDH_CK_GT, 0);

#ifdef HIVDEC_SMMU_SUPPORT
#ifdef ENV_SOS_KERNEL
    SMMU_SetMasterReg(MFDE, SECURE_ON,  SMMU_OFF);
#else
    SMMU_SetMasterReg(MFDE, SECURE_OFF, SMMU_ON);
#endif
#endif

    VFMW_OSAL_Mb();
    WR_VREG( VREG_V400R004_VDH_START, 0, VdhId );
    WR_VREG( VREG_V400R004_VDH_START, 1, VdhId );
    WR_VREG( VREG_V400R004_VDH_START, 0, VdhId );

    return;
}

VOID VDMHAL_V400R004_GetCharacter(VOID)
{
    g_VdmCharacter = VDM_SUPPORT_VP6 | VDM_SUPPORT_BPD | VDM_SUPPORT_VCMP | VDM_SUPPORT_GMC;
    g_eVdmVersion  = VDM_VERSION_VDHV400_R004;
    return;
}

VOID VDMHAL_V400R004_WriteScdEMARID(VOID)
{
    WR_SCDREG(REG_EMAR_ID, DEFAULT_EMAR_ID_VALUE);
}

