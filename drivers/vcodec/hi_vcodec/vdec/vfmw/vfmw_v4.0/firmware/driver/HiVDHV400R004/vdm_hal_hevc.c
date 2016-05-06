
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vdmv300vplus_hal.c
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
#include 	"basedef.h"
#include 	"vfmw.h"
#include 	"mem_manage.h"
#include 	"public.h"
#include    "vdm_hal_v400r004_api.h"
#include    "vdm_hal_v400r004_local.h"
#include 	"vdm_hal_v400r004_hevc.h"
#include    "vfmw_ctrl.h"


extern UINT8  g_not_direct_8x8_inference_flag;
extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];

const static UINT32 s_SliceTypeForPMV[3] = {2, 1, 0};                    // slice type idx
extern UINT32	g_TsToRsMap[HEVC_MAX_MB_NUM];
extern UINT8	g_IsDeced[HEVC_MAX_MB_NUM];

static SINT8 s_CabacMN[58 * 8][2];
static SINT32 s_InitValue[3][160] =
{
    {
        //I
        //addr0
        -1, -1, -1, -1, -1, -1, -1, -1,
        //addr1
        -1, -1, -1, -1, -1, -1, -1, -1,
        //2
        153, 200, 139, 141, 157, 154, -1, -1,
        //3
        -1, -1, 184, -1, -1, -1, 184, 63,
        //4
        94, 138, 182, 154, 111, 141, 154, 154,
        //5
        139, 139, 138, 153, 136, 167, 152, 152,
        //6
        110, 110, 124, 125, 140, 153, 125, 127,
        //7
        140, 109, 111, 143, 127, 111, 79, 108,
        //8
        123, 63, 110, 110, 124, 125, 140, 153,
        //9
        125, 127, 140, 109, 111, 143, 127, 111,
        //10
        79, 108, 123, 63, 91, 171, 134, 141,
        //11
        140, 92, 137, 138, 140, 152, 138, 139,
        //12
        153, 74, 149, 92, 139, 107, 122, 152,
        //13
        140, 179, 166, 182, 140, 227, 122, 197,
        //14
        111, 111, 125, 110, 110, 94, 124, 108,
        //15
        124, 107, 125, 141, 179, 153, 125, 107,
        //16
        125, 141, 179, 153, 125, 107, 125, 141,
        //17
        179, 153, 125, 140, 139, 182, 182, 152,
        //18
        136, 152, 136, 153, 136, 139, 111, 136,
        //19
        139, 111, -1, 153, 138, 138, -1, -1

    },
    //P
    {
        //0
        79, 110, 122, 95, 79, 63, 31, 31,
        //1
        153, 153, 168, 140, 198, -1, -1, -1,
        //2
        153, 185, 107, 139, 126, 154, 197, 185,
        //3
        201, 149, 154, 139, 154, 154, 154, 152,
        //4
        149, 107, 167, 154, 153, 111, 154, 154,
        //5
        139, 139, 107, 167, 91, 122, 107, 167,
        //6
        125, 110, 94, 110, 95, 79, 125, 111,
        //7
        110, 78, 110, 111, 111, 95, 94, 108,
        //8
        123, 108, 125, 110, 94, 110, 95, 79,
        //9
        125, 111, 110, 78, 110, 111, 111, 95,
        //10
        94, 108, 123, 108, 121, 140, 61, 154,
        //11
        154, 196, 196, 167, 154, 152, 167, 182,
        //12
        182, 134, 149, 136, 153, 121, 136, 137,
        //13
        169, 194, 166, 167, 154, 167, 137, 182,
        //14
        155, 154, 139, 153, 139, 123, 123, 63,
        //15
        153, 166, 183, 140, 136, 153, 154, 166,
        //16
        183, 140, 136, 153, 154, 166, 183, 140,
        //17
        136, 153, 154, 170, 153, 123, 123, 107,
        //18
        121, 107, 121, 167, 151, 183, 140, 151,
        //19
        183, 140, -1, 124, 138, 94, -1, -1
    },
    //B
    {
        //0
        79, 154, 137, 95, 79, 63, 31, 31,
        //1
        153, 153, 168, 169, 198, -1, -1, -1,
        //2
        153, 160, 107, 139, 126, 154, 197, 185,
        //3
        201, 134, 154, 139, 154, 154, 183, 152,
        //4
        149, 92, 167, 154, 153, 111, 154, 154,
        //5
        139, 139, 107, 167, 91, 107, 107, 167,
        //6
        125, 110, 124, 110, 95, 94, 125, 111,
        //7
        111, 79, 125, 126, 111, 111, 79, 108,
        //8
        123, 93, 125, 110, 124, 110, 95, 94,
        //9
        125, 111, 111, 79, 125, 126, 111, 111,
        //10
        79, 108, 123, 93, 121, 140, 61, 154,
        //11
        154, 196, 167, 167, 154, 152, 167, 182,
        //12
        182, 134, 149, 136, 153, 121, 136, 122,
        //13
        169, 208, 166, 167, 154, 152, 167, 182,
        //14
        170, 154, 139, 153, 139, 123, 123, 63,
        //15
        124, 166, 183, 140, 136, 153, 154, 166,
        //16
        183, 140, 136, 153, 154, 166, 183, 140,
        //17
        136, 153, 154, 170, 153, 138, 138, 122,
        //18
        121, 122, 121, 167, 151, 183, 140, 151,
        //19
        183, 140, -1, 224, 167, 122, -1, -1
    }
};
/*!
************************************************************************
*   函数原型 :  SINT32 WriteCabacTab(UADDR mn_phy_addr)
*   功能描述 :  写消息池cabac g_CabacMN code tab
*   参数说明 :
*   返回值   ：
************************************************************************
*/
SINT32 HEVCWriteCabacTab(UADDR mn_phy_addr)
{
    SINT32 i, j;
    SINT8 *p;
    SINT32 initValue, slopeIdx, offsetIdx;
    SINT32 idx = 0;

    for (i = 0; i < 3; i++)
    {
        if (0 == i)
        {
            j = 16;
        }
        else
        {
            j = 0;
        }

        for ( ; j < 160; j++)
        {
            initValue = s_InitValue[i][j];

            if (-1 == initValue)
            {
                s_CabacMN[idx][0] = 0;
                s_CabacMN[idx][1] = 0;
            }
            else
            {
                slopeIdx = initValue >> 4;
                offsetIdx = initValue & 15;
                s_CabacMN[idx][0] = slopeIdx * 5 - 45; //m
                s_CabacMN[idx][1] = (offsetIdx << 3) - 16;  //n
            }

            idx++;
        }
    }

    p = (SINT8 *)MEM_Phy2Vir(mn_phy_addr);
    VDMHAL_ASSERT_RET( p != NULL, "can not map mn virtual address!\n");

    for (i = 0; i < 464; i++)
    {
        *(p + 1) = s_CabacMN[i][0];
        *(p) = 	 s_CabacMN[i][1];
        p = p + 2;
    }

    return VDMHAL_OK;
}

/*****************************************************************************************
原型  SINT32 VDMHAL_Init()
功能  初始化VDMHAL.
    VDMHAL将"消息池"、"寄存器"等信息作为与通道无关的私有资源管理，但消息池是从上层程序
    分配的空间中划拨的，为了实现换台或重启解码器时VDMHAL可以更新消息池地址，必须对外实
    现一个初始化函数。
    本函数的具体功能是：清除静态信息。
参数  无
返回值  成功返回OK（0），否则返回错误码
******************************************************************************************/
SINT32 HEVCHAL_V400R004_InitHal(VDMHAL_HWMEM_S *pHwMem)
{
    if (HEVCWriteCabacTab(pHwMem->mn_phy_addr) != VDMHAL_OK)
    {
        dprint(PRN_ERROR, "HEVCWriteCabacTab return error.\n");
        return VDMHAL_ERR;
    }

    return VDMHAL_OK;
}


/*!
************************************************************************
*   函数原型 :  UINT32 *Get_V200R001_VirAddr(UINT32 Dn，UINT32 *base_vir_addr)
*   功能描述 :  获取对应Dn_num所在行在消息池中的虚拟地址
*   参数说明 :
*   返回值   ：
************************************************************************
*/
UINT32 *HEVCGet_V400R004_VirAddr(UINT32 Dn, UINT32 *pbase_vir_addr)
{
    return (pbase_vir_addr + Dn); // one line addr
}


/*!
************************************************************************
*   函数原型 :  UINT32 *Get_V200R001_PhyAddr(UINT32 Dn，UADDR base_phy_addr)
*   功能描述 :  获取对应Dn_num所在行在消息池中的物理地址
*   参数说明 :
*   返回值   ：
************************************************************************
*/
UINT32 HEVCGet_V400R004_PhyAddr(UINT32 Dn, UADDR base_phy_addr)
{
    return (base_phy_addr + Dn * 4); // one line addr
}


SINT32 HEVCHAL_V400R004_CutSliceChain(UADDR CurrMsgSlotPhy )
{
    UINT32 *pSLOT_BASE, *pSLOT;
    UINT32  Dn_num;

    // get base vir addr and phy addr of the slot will write slice para of currslice
    pSLOT_BASE = (UINT32 *)(MEM_Phy2Vir(CurrMsgSlotPhy)); // slot addr
    VDMHAL_ASSERT_RET( pSLOT_BASE != NULL, "can not map slice msg virtual address!\n");
    Dn_num = 0;
    pSLOT = HEVCGet_V400R004_VirAddr(Dn_num, pSLOT_BASE);

    //D42
    *(pSLOT + 63) = 0;

    return  VDMHAL_OK;
}


VOID HEVC_WriteQmatrix(UINT32 *qmatrix, UINT32 size, UADDR phy_addr, UINT32 *vir_addr)
{
    UINT32 i;

    for (i = 0; i < size; i++)
    {
        *(vir_addr + i) = *(qmatrix + i);
        dprint(PRN_DNMSG, "qmatrix[%d] = 0x%x\n", i, *(qmatrix + i));
        dprint(PRN_DNMSG, "picmsg Dxx addr 0x%x = 0x%x\n", phy_addr + i * 4, *(vir_addr + i));
    }

    return;
}


SINT32 HEVC_WriteTileInfo(HEVC_DEC_PIC_PARAM_S *pParam, VDMHAL_HWMEM_S *pHwMem)
{
    UINT32 i, j;
    UINT32 *p_base;
    UINT32 tmp;

    p_base = (UINT32 *)MEM_Phy2Vir(pHwMem->tile_segment_info_phy_addr);
    VDMHAL_ASSERT_RET( p_base != NULL, "can not map slice segment info virtual address!\n");

    //TileId
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 512; j += 4)
        {
            if (j < HEVC_MAX_CTB_NUM_PER_LINE - 3)
            {
                tmp = pParam->TileId[i][j + 3] << 24
                      | pParam->TileId[i][j + 2] << 16
                      | pParam->TileId[i][j + 1] << 8
                      | pParam->TileId[i][j];

                *(p_base++) = tmp;
                dprint(PRN_DNMSG, "TileId: 0x%x\n", tmp);
            }
            else
            {
                *(p_base++) = 0;
                dprint(PRN_DNMSG, "TileId: 0x%x\n", 0);
            }
        }
    }

    //TilePosX
    for (i = 0; i < 20; i++)
    {
        if (i < HEVC_LOGIC_TILE_COLUMNS_LIMIT)
        {
            tmp = pParam->TilePosX[i][1] << 16 | \
                  pParam->TilePosX[i][0];
            *(p_base++) = tmp;
        }
        else
        {
            *(p_base++) = 0;
        }
    }

    //TilePosY
    for (i = 0; i < 22; i++)
    {
        if (i < HEVC_LOGIC_TILE_ROWS_LIMIT)
        {
            tmp = pParam->TilePosY[i][1] << 16 | \
                  pParam->TilePosY[i][0];
            *(p_base++) = tmp;
        }
        else
        {
            *(p_base++) = 0;
        }
    }

    return VDMHAL_OK;
}


SINT32 HEVCHAL_V400R004_SetPicMsg(HEVC_DEC_PIC_PARAM_S *pParam, VDMHAL_HWMEM_S *pHwMem,
                                  UADDR PicMsgSlotPhy, UADDR FstSlcMsgSlotPhy)
{

    UINT32 *pSlot = NULL, *pSlot_base = NULL;
    UADDR pSlot_phy, pSlot_phy_base;
    UINT32 Dn_num, i;
    UINT32 tmp;

    // D0~D63
    // pic_slot_num是用第三个消息池，即为slot_num = 2

    pSlot_base = (UINT32 *)(MEM_Phy2Vir(PicMsgSlotPhy)); // slot addr
    VDMHAL_ASSERT_RET( pSlot_base != NULL, "can not map down msg virtual address!\n");
    pSlot_phy_base = (UINT32)PicMsgSlotPhy;
    pSlot = pSlot_base;
    pSlot_phy = pSlot_phy_base;

    //memset(pSlot_base, 0, 4 * HEVC_ONE_MSG_SLOT_LEN);

    dprint(PRN_DNMSG, "pic msg burst0:\n");

    /*burst 0*/
    //D0
    tmp = pParam->strong_intra_smoothing_enabled_flag << 25 | \
          pParam->scaling_list_enabled_flag           << 24 | \
          pParam->pcm_loop_filter_disabled_flag       << 23 | \
          pParam->sample_adaptive_offset_enabled_flag << 22 | \
          pParam->amp_enabled_flag                    << 21 | \
          pParam->chroma_format_idc                   << 19 | \
          pParam->pcm_enabled_flag                    << 18 | \
          pParam->PicHightInCtbsYMinus1               << 9  | \
          (pParam->PicWidthInCtbsYMinus1);

    WR_MSGWORD(pSlot, tmp);
    dprint(PRN_DNMSG, "picmsg D[0] addr 0x%x = 0x%x\n", pSlot_phy + (0x0) * 4, *(pSlot + 0x0));

    //D1
    tmp = pParam->ThisPoc;
    WR_MSGWORD(pSlot + 1, tmp);

    //D2
    tmp = pParam->log2_parallel_merge_level_minus2    << 29 | \
          pParam->weighted_bipred_flag                << 28 | \
          pParam->weighted_pred_flag                  << 27 | \
          pParam->max_transform_hierarchy_depth_inter << 24 | \
          pParam->max_transform_hierarchy_depth_intra << 21 | \
          pParam->Log2MinIpcmCbSizeY                  << 18 | \
          pParam->Log2MaxIpcmCbSizeY                  << 15 | \
          pParam->Log2MinTrafoSize                    << 12 | \
          pParam->Log2MaxTrafoSize                    << 9  | \
          pParam->MaxCuDepth                          << 6  | \
          pParam->Log2MinCbSizeY                      << 3  | \
          pParam->CtbLog2SizeY;

    WR_MSGWORD(pSlot + 2, tmp);

    //D3
    tmp = pParam->QpBdOffsetC  << 22 | \
          pParam->QpBdOffsetY  << 16 | \
          pParam->PcmBitDepthC << 12 | \
          pParam->PcmBitDepthY << 8  | \
          pParam->BitDepthC    << 4  | \
          pParam->BitDepthY;

    WR_MSGWORD(pSlot + 3, tmp);

    //D4
    tmp = pHwMem->sed_top_phy_addr;
    WR_MSGWORD(pSlot + 4, tmp);

    //D5
    tmp = pHwMem->pmv_top_phy_addr;
    WR_MSGWORD(pSlot + 5, tmp);

    //D6
    tmp = pParam->PmvPhyAddr[pParam->CurrPicPmvIdc ];
    WR_MSGWORD(pSlot + 6, tmp);

    //D7
    tmp = pHwMem->rcn_top_phy_addr;
    WR_MSGWORD(pSlot + 7, tmp);

    //D8~D24
    //pic_addr of all apc
    for (i = 0; i < pParam->ApcSize; i++)
    {
        tmp = (pParam->ImgPhyAddr[pParam->Apc2Idc[i]]) ;
        WR_MSGWORD(pSlot + (i + 8), tmp);
    }

    for (i = pParam->ApcSize; i < 16; i++)
    {
        tmp = (pParam->ImgPhyAddr[pParam->Apc2Idc[0]]);
        WR_MSGWORD(pSlot + (i + 8), tmp);
    }

    //D25
    tmp = pHwMem->mn_phy_addr;
    WR_MSGWORD(pSlot + 25, tmp);

    //D26~D41
    for (i = 0; i < 16; i++)
    {
        tmp = pParam->Apc2PocTable[i];
        WR_MSGWORD(pSlot + (i + 26), tmp);
    }

    //D43
    tmp = pHwMem->pmv_left_phy_addr;  //保存pmv模块左相邻信息，计算BS用,h00216273,2014/4/19
    WR_MSGWORD(pSlot + 43, tmp);

    //D54
    tmp = pParam->pic_height_in_luma_samples << 16 | \
          pParam->pic_width_in_luma_samples;

    WR_MSGWORD(pSlot + 54, tmp);

    //D55
    if (HEVC_WriteTileInfo(pParam, pHwMem) != VDMHAL_OK)
    {
        dprint(PRN_ERROR, "HEVC_WriteTileInfo return error.\n");
        return VDMHAL_ERR;
    }

    tmp = pHwMem->tile_segment_info_phy_addr;
    WR_MSGWORD(pSlot + 55, tmp);

    //D56
    tmp = pHwMem->sao_left_phy_addr;
    WR_MSGWORD(pSlot + 56, tmp);

    //D57
    tmp = pHwMem->dblk_left_phy_addr;
    WR_MSGWORD(pSlot + 57, tmp);

    //D58
    tmp = pHwMem->sao_top_phy_addr;
    WR_MSGWORD(pSlot + 58, tmp);

    //D59
    tmp = pHwMem->dblk_top_phy_addr;
    WR_MSGWORD(pSlot + 59, tmp);

    //D60
    tmp = pParam->loop_filter_across_tiles_enabled_flag << 24 | \
          pParam->transform_skip_enabled_flag           << 23 | \
          pParam->sign_data_hiding_enabled_flag         << 22 | \
          pParam->entropy_coding_sync_enabled_flag      << 21 | \
          pParam->uniform_spacing_flag                  << 20 | \
          pParam->tiles_enabled_flag                    << 19 | \
          pParam->Log2MinCuQpDeltaSize                  << 16 | \
          pParam->diff_cu_qp_delta_depth                << 13 | \
          pParam->cu_qp_delta_enabled_flag              << 12 | \
          pParam->transquant_bypass_enabled_flag        << 11 | \
          pParam->constrained_intra_pred_flag           << 10 | \
          (pParam->pps_cb_qp_offset & 0x1f)             << 5  | \
          (pParam->pps_cr_qp_offset & 0x1f);

    WR_MSGWORD(pSlot + 60, tmp);

    //D61
    tmp = pParam->num_tile_rows_minus1 << 16 | \
          pParam->num_tile_columns_minus1;

    WR_MSGWORD(pSlot + 61, tmp);

    //D63
    tmp = FstSlcMsgSlotPhy;//下一个下行消息也即第一个sliceMsg addr l00214825
    WR_MSGWORD(pSlot + 63, tmp);

    /*burst 1 ~ burst 4*/
    Dn_num = 0 + 64;
    pSlot = HEVC_GetVirAddr(Dn_num, pSlot_base);
    pSlot_phy = HEVC_GetPhyAddr(Dn_num, pSlot_phy_base);

    //write ScalingList
    HEVC_WriteQmatrix(pParam->Qmatrix, 4 * 64, pSlot_phy, pSlot);

    return VDMHAL_OK;
}

SINT32 HEVCHAL_V400R004_SetSliceMsg(HEVC_DEC_PIC_PARAM_S *pPicParam, VDMHAL_HWMEM_S *pHwMem, HEVC_DEC_SLICE_PARAM_S *pSliceParam,
                                    UADDR CurrMsgSlotPhy, UADDR ForwardSlcMsgPhy, UADDR NextSlcMsgSlotPhy, SINT32 slice_segment_address, SINT32 SliceSegmentTileAddress, SINT32 end_ctb_in_slice_raster, SINT32 end_ctb_in_slice_tile)
{
    UINT32 *pSLOT, *pSLOT_BASE;
    UINT32 *pSLOT_line0, *pSLOT_line1;
    UADDR  pSLOT_phy_base, pSLOT_phy;
    UADDR  stream_base_addr, stream_start_addr;
    UINT32 Dn_num, Dn_0;
    UINT32 i;
    UINT32 SliceSegmentAddressX, SliceSegmentAddressY;
    UINT32 tmp, tmp1;

    // get base vir addr and phy addr of the slot will write slice para of currslice
    pSLOT_BASE = (UINT32 *)(MEM_Phy2Vir(CurrMsgSlotPhy)); // slot addr
    VDMHAL_ASSERT_RET( pSLOT_BASE != NULL, "HEVCHAL_V400R004_SetSliceMsg can not map slice msg virtual address!\n");
    pSLOT_phy_base = CurrMsgSlotPhy;
	
    //memset(pSLOT_BASE, 0x0, 4 * HEVC_ONE_MSG_SLOT_LEN);

    /*burst 0*/
    Dn_num    = 0;
    pSLOT     = HEVCGet_V400R004_VirAddr(Dn_num, pSLOT_BASE);
    pSLOT_phy = HEVCGet_V400R004_PhyAddr(Dn_num, pSLOT_phy_base);

    for (i = 0; i < 2; i++)
    {
        if (0 == i && 0 == pSliceParam->valid_bitlen[i])
        {
            dprint(PRN_FATAL, "%s FATAL: i=0, valid_bitlen=0\n", __func__);
            return VDMHAL_ERR;
        }

        if (0 < pSliceParam->valid_bitlen[i])
        {
            stream_base_addr  = (pPicParam->stream_base_addr & 0xfffffff0);
            stream_start_addr = (pSliceParam->bytespos[i]    & 0xfffffff0);

            tmp = (stream_start_addr - stream_base_addr);
            WR_MSGWORD(pSLOT + 3 * i, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3 * i, pSLOT_phy + (3 * i) * 4, *(pSLOT + 3 * i));

            tmp = (pSliceParam->bitsoffset[i] + 8 * (pSliceParam->bytespos[i] & 0xf)) & 0x7f ;
            WR_MSGWORD(pSLOT + 3 * i + 1, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3 * i + 1, pSLOT_phy + (3 * i + 1) * 4, *(pSLOT + 3 * i + 1));

            tmp = pSliceParam->valid_bitlen[i];
            WR_MSGWORD(pSLOT + 3 * i + 2, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3 * i + 2, pSLOT_phy + (3 * i + 2) * 4, *(pSLOT + 3 * i + 2));
        }
        else
        {
            tmp = 0;
            WR_MSGWORD(pSLOT + 3 * i, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3 * i, pSLOT_phy + (3 * i) * 4, *(pSLOT + 3 * i));

            tmp = 0;
            WR_MSGWORD(pSLOT + 3 * i + 1, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3 * i + 1, pSLOT_phy + (3 * i + 1) * 4, *(pSLOT + 3 * i + 1));

            tmp = 0;
            WR_MSGWORD(pSLOT + 3 * i + 2, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3 * i + 2, pSLOT_phy + (3 * i + 2) * 4, *(pSLOT + 3 * i + 2));
        }
    }

    //D6
    tmp = pSliceParam->IsLowDelay                   << 27 | \
          pSliceParam->dependent_slice_segment_flag << 26 | \
          (pSliceParam->SliceQpY & 0x3f)            << 19 | \
          pSliceParam->cabac_init_flag              << 18 | \
          pSliceParam->IndependentSliceSegmentAddr;
    WR_MSGWORD(pSLOT + 6, tmp);

    //D7
    tmp = pSliceParam->ColPicApc                       << 28 | \
          pSliceParam->collocated_from_l0_flag         << 27 | \
          pSliceParam->MaxNumMergeCand                 << 24 | \
          pSliceParam->num_ref_idx_l1_active_minus1    << 20 | \
          pSliceParam->num_ref_idx_l0_active_minus1    << 16 | \
          pSliceParam->slice_temporal_mvp_enabled_flag << 15 | \
          pSliceParam->mvd_l1_zero_flag                << 14 | \
          pSliceParam->listXsize[1]                    << 8	 | \
          pSliceParam->listXsize[0]                    << 2	 | \
          s_SliceTypeForPMV[pSliceParam->SliceType];
    WR_MSGWORD(pSLOT + 7, tmp);

    // D8
    tmp = slice_segment_address; //slice起始ctb地址
    WR_MSGWORD(pSLOT + 8, tmp);

    // D9
    SliceSegmentAddressX = slice_segment_address % (pPicParam->PicWidthInCtbsYMinus1 + 1);
    SliceSegmentAddressY = slice_segment_address / (pPicParam->PicWidthInCtbsYMinus1 + 1);

    tmp = SliceSegmentAddressY << 16 | \
          SliceSegmentAddressX;
    WR_MSGWORD(pSLOT + 9, tmp);

    //D10
    tmp = SliceSegmentTileAddress;
    WR_MSGWORD(pSLOT + 10, tmp);

    //D11
    tmp = (pSliceParam->slice_cb_qp_offset & 0x1f) << 8 | \
          (pSliceParam->slice_cr_qp_offset & 0x1f);
    WR_MSGWORD(pSLOT + 11, tmp);

    //D12
    tmp = (pSliceParam->slice_tc_offset_div2 & 0xf) 		 << 16 | \
          (pSliceParam->slice_beta_offset_div2 & 0xf)		 <<  8 | \
          pSliceParam->slice_sao_luma_flag                   <<  3 | \
          pSliceParam->slice_sao_chroma_flag                 <<  2 | \
          pSliceParam->slice_deblocking_filter_disabled_flag <<  1 | \
          pSliceParam->slice_loop_filter_across_slices_enabled_flag;
    WR_MSGWORD(pSLOT + 12, tmp);

    //D13 list0
    tmp = 0;

    for (i = 0; i < pSliceParam->listXsize[0]; i++)
    {
        tmp  |= ((pSliceParam->IsLongTerm[0][i]) << i);
    }

    WR_MSGWORD(pSLOT + 13, tmp);
    tmp = 0;

    for (i = 0; i < pSliceParam->listXsize[1]; i++)
    {
        tmp  |= ((pSliceParam->IsLongTerm[1][i]) << i);
    }

    WR_MSGWORD(pSLOT + 14, tmp);
    tmp1 = 0;
    Dn_0 = 15;

    for (i = 0; i < pSliceParam->listXsize[0]; i++)
    {
        tmp1 |= ((pSliceParam->Idx2Apc[0][i]) << (4 * (i & 0x7)));

        if (i % 8 == 7)
        {
            WR_MSGWORD(pSLOT + (Dn_0), tmp1);
            tmp1 = 0;
            ++Dn_0;
        }
        else if (i == (pSliceParam->listXsize[0] - 1))
        {
            WR_MSGWORD(pSLOT + (Dn_0), tmp1);
        }
    }

    //D17~D18 list1中refidx对应的APC索引号
    tmp1 = 0;
    Dn_0 = 17;

    for (i = 0; i < pSliceParam->listXsize[1]; i++)
    {
        tmp1 |= ((pSliceParam->Idx2Apc[1][i]) << (4 * (i & 0x7)));

        if (i % 8 == 7)
        {
            WR_MSGWORD(pSLOT + (Dn_0), tmp1);
            tmp1 = 0;
            ++Dn_0;
        }
        else if (i == (pSliceParam->listXsize[1] - 1))
        {
            WR_MSGWORD(pSLOT + (Dn_0), tmp1);
        }
    }

    //D23 对应的MvAddr值
    tmp = pSliceParam->Apc2MvAddr;
    WR_MSGWORD(pSLOT + 23, tmp);

    tmp = end_ctb_in_slice_raster;
    WR_MSGWORD(pSLOT + 43, tmp);

    tmp = end_ctb_in_slice_tile;
    WR_MSGWORD(pSLOT + 44, tmp);

    //D63
    tmp = NextSlcMsgSlotPhy;
    WR_MSGWORD(pSLOT + 63, tmp);

    /*burst 1 and burst 2*/
    if ((pPicParam->weighted_pred_flag && (HEVC_P_SLICE == pSliceParam->SliceType)) ||
        ((1 == pPicParam->weighted_bipred_flag) && (HEVC_B_SLICE == pSliceParam->SliceType)))
    {
        // list0
        // D0~D31 of burst1, Dn_num = 1*64 + D0 ,luma wp
        pSLOT_line0 = HEVC_GetVirAddr(64, pSLOT_BASE);

        // D0~D31 of burst2, Dn_num = 2*64 + D0 ,luma wp
        pSLOT_line1 = HEVC_GetVirAddr(128, pSLOT_BASE);

        for (i = 0; i < pSliceParam->listXsize[0]; i++)
        {
            tmp = (pSliceParam->luma_offset_l0[i] & 0xff)	<< 12 | \
                  (pSliceParam->LumaWeightL0[i]   & 0x1ff)	<< 3  | \
                  (pSliceParam->luma_log2_weight_denom & 0x7);
            WR_MSGWORD(pSLOT_line0 + i, tmp);

            tmp = (pSliceParam->ChromaOffsetL0[i][0] & 0xff)  << 12 | \
                  (pSliceParam->ChromaWeightL0[i][0] & 0x1ff) << 3  | \
                  (pSliceParam->chroma_log2_weight_denom & 0x7);
            WR_MSGWORD(pSLOT_line1 + i, tmp);

            tmp = (pSliceParam->ChromaOffsetL0[i][1] & 0xff) << 9 | \
                  (pSliceParam->ChromaWeightL0[i][1] & 0x1ff);
            WR_MSGWORD(pSLOT_line1 + (i + 32), tmp);
        }

        // list1
        if (HEVC_B_SLICE == pSliceParam->SliceType)
        {
            for (i = 0; i < pSliceParam->listXsize[1]; i++)
            {
                tmp = (pSliceParam->luma_offset_l1[i] & 0xff)  << 12 | \
                      (pSliceParam->LumaWeightL1[i]   & 0x1ff) << 3  | \
                      (pSliceParam->luma_log2_weight_denom & 0x7);
                WR_MSGWORD(pSLOT_line0 + (i + 16), tmp);

                tmp = (pSliceParam->ChromaOffsetL1[i][0] & 0xff)  << 12 | \
                      (pSliceParam->ChromaWeightL1[i][0] & 0x1ff) << 3  | \
                      (pSliceParam->chroma_log2_weight_denom & 0x7);
                WR_MSGWORD(pSLOT_line1 + (i + 16), tmp);

                tmp = (pSliceParam->ChromaOffsetL1[i][1] & 0xff) << 9 | \
                      (pSliceParam->ChromaWeightL1[i][1] & 0x1ff);
                WR_MSGWORD(pSLOT_line1 + (i + 48), tmp);
            }
        }
    }

    return VDMHAL_OK;
}


SINT32 HEVCHAL_V400R004_CfgVdmReg(HEVC_DEC_PIC_PARAM_S *pPicParam, VDMHAL_HWMEM_S *pHwMem, SINT32 VdhId)
{
    UINT8  uv_order = 0;
    SINT32 D32;
    UINT32 datTmp;
    SINT32 ChanId = g_VdmDrvParam[VdhId].ChanId;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    SINT32 ModuleLowlyEnable = 0;
#endif

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
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
#endif

    //BASIC_CFG0
    D32 = 0;
    ((HEVC_BASIC_CFG0 *)(&D32))->marker_bit_detect_en = 0;
    ((HEVC_BASIC_CFG0 *)(&D32))->ac_last_detect_en    = 0;
    ((HEVC_BASIC_CFG0 *)(&D32))->coef_idx_detect_en   = 1; //此变量表示是否对run_cnt大于64进行检错
    ((HEVC_BASIC_CFG0 *)(&D32))->vop_type_detect_en   = 0;
    ((HEVC_BASIC_CFG0 *)(&D32))->load_qmatrix_flag    = pPicParam->scaling_list_enabled_flag;
    ((HEVC_BASIC_CFG0 *)(&D32))->luma_sum_en          = 0; //亮度像素和计算使能
    ((HEVC_BASIC_CFG0 *)(&D32))->luma_histogram_en    = 0; //亮度直方图计算使能
    ((HEVC_BASIC_CFG0 *)(&D32))->mbamt_to_dec         = (pPicParam->PicHightInCtbsYMinus1 + 1) * (pPicParam->PicWidthInCtbsYMinus1 + 1) - 1;
#ifdef ENV_SOS_KERNEL
    ((HEVC_BASIC_CFG0*)(&D32))->vdh_safe_flag         = 1;
#else
    ((HEVC_BASIC_CFG0*)(&D32))->vdh_safe_flag         = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId );    

    //BASIC_CFG1
    /*因为HEVC做CRC校验是用NV12格式的图像，所以这里uv_order反转一下*/
    if (NULL != s_pstVfmwChan[ChanId])
    {
        uv_order = (1 == s_pstVfmwChan[ChanId]->stChanCfg.u8UVOrder)? 1: 0;
    }
    else
    {
        uv_order = 0;
    }
    D32 = 0;
    ((HEVC_BASIC_CFG1 *)(&D32))->video_standard       = 0xD;
    ((HEVC_BASIC_CFG1 *)(&D32))->fst_slc_grp          = pPicParam->NewPicFlag;
    ((HEVC_BASIC_CFG1 *)(&D32))->mv_output_en         = 1;
    ((HEVC_BASIC_CFG1 *)(&D32))->uv_order_en          = uv_order;
    ((HEVC_BASIC_CFG1 *)(&D32))->vdh_2d_en            = 1;
    ((HEVC_BASIC_CFG1 *)(&D32))->max_slcgrp_num       = 3;
    ((HEVC_BASIC_CFG1 *)(&D32))->line_num_output_en   = 0; //当前帧已解完的像素行号是否要输出到DDR
    ((HEVC_BASIC_CFG1 *)(&D32))->frm_cmp_en           = pPicParam->Compress_en;
    ((HEVC_BASIC_CFG1 *)(&D32))->ppfd_en              = 0;
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );

    //AVM_ADDR
    D32 = 0;
    ((AVM_V400R004_ADDR *)(&D32))->av_msg_addr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "AVM_ADDR = 0x%x\n", D32);

    //VAM_ADDR
    D32 = 0;
    ((VAM_V400R004_ADDR *)(&D32))->va_msg_addr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId );

    //STREAM_BASE_ADDR
    D32 = 0;
    ((STREAM_V400R004_BASE_ADDR *)(&D32))->stream_base_addr = pPicParam->stream_base_addr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId );

    //TIME_OUT
    D32 = 0x00300C03; //这个值配置 l00214825
    WR_VREG( VREG_V400R004_SED_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_ITRANS_TO, D32 , VdhId);
    WR_VREG( VREG_V400R004_PMV_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_PRC_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_RCN_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_DBLK_TO,   D32 , VdhId);
    WR_VREG( VREG_V400R004_PPFD_TO,   D32, VdhId );

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (1 == ModuleLowlyEnable)
    {
        D32 = 10;
        WR_VREG(VREG_V400R004_PART_DEC_OVER_INT_LEVEL, D32, VdhId );
        dprint(PRN_VDMREG, "VREG_V400R004_PART_DEC_OVER_INT_LEVEL=0x%x\n", D32);
        
        D32 = pPicParam->LineNumPhyAddr[pPicParam->CurrPicImgIdc];
        WR_VREG( VREG_V400R004_LINE_NUM_STADDR, D32, VdhId );
        dprint(PRN_VDMREG, "VREG_LINE_NUM_STADDR = 0x%x\n", D32);
    }
#endif

    D32 = 0;
    ((YSTADDR_V400R004_1D *)(&D32))->ystaddr_1d = (pPicParam->ImgPhyAddr[pPicParam->CurrPicImgIdc]) & 0xFFFFFF00;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId );

    //YSTRIDE_1D
    D32 = 0;
    ((YSTRIDE_V400R004_1D *)(&D32))->ystride_1d = pPicParam->imgstride;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId );

    //UVOFFSET_1D
    D32 = 0;
    ((UVOFFSET_V400R004_1D *)(&D32))->uvoffset_1d = pPicParam->UVOffset;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId );

    //HEAD_INF_OFFSET
    D32 = 0;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId ); //文档这里不匹配  l00214825

    //PPFD_BUF_ADDR
    D32 = 0;
    ((PPFD_V400R004_BUF_ADDR *)(&D32))->ppfd_buf_addr = 0;      //z00290437  20141016  PPFD模块删除
    WR_VREG( VREG_V400R004_PPFD_BUF_ADDR, D32, VdhId );

    //PPFD_BUF_LEN
    D32 = 0;
    //((PPFD_V400R004_BUF_LEN*)(&D32))->ppfd_buf_len = pHwMem->ppfd_buf_len;
    ((PPFD_V400R004_BUF_LEN *)(&D32))->ppfd_buf_len = 0;        //z00290437  20141016  PPFD模块删除
    WR_VREG( VREG_V400R004_PPFD_BUF_LEN, D32, VdhId );

    //EMAR_ID
    //width<=4096 配1 >4096 配0，h00216273
    if (pPicParam->pic_width_in_luma_samples <= 4096)
    {
        D32 = 0x10000;

    }
    else
    {
        D32 = 0x0;
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

    //FF_APT_EN
    D32 = 0x2;
    WR_VREG( VREG_V400R004_FF_APT_EN, D32, VdhId);
    dprint(PRN_VDMREG, "VREG_V400R004_FF_APT_EN = 0x%x\n", D32);

    //CLEAR INT
    D32 = 0xFFFFFFFF;
    WR_VREG( VREG_V400R004_INT_STATE, D32, VdhId );
#ifdef VDM_BUSY_WAITTING
    // 中断屏蔽
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFF, VdhId );
#else
    // 中断打开
    WR_VREG( VREG_V400R004_INT_MASK, 0xFFFFFFFE , VdhId);
#endif

    return VDMHAL_OK;
}


SINT32 HEVCHAL_V400R004_StartDec(HEVC_DEC_PIC_PARAM_S *pParam, SINT32 VdhId)
{
    SINT32 i = 0, j = 0;
    UADDR  cur_slcmsg_phy             = 0;
    SINT32 add_slice0_flag            = 0;
    SINT32 valid_slice_num            = 0;
    UADDR  prev_slcmsg_phy            = 0;
    UADDR  next_slcmsg_phy            = 0;
    SINT32 tile_address_bak           = 0;
    SINT32 pic_end_ctb_in_raster      = 0;
    SINT32 slice_segment_address      = 0;
    SINT32 end_ctb_in_slice_tile      = 0;
    SINT32 end_ctb_in_slice_raster    = 0;
    SINT32 pre_end_ctb_in_slice_tile  = 0;
    SINT32 slice_segment_tile_address = 0;
    SINT32 bytespos[2]                = {0, 0};
    SINT32 bitsoffset[2]              = {0, 0};
    SINT32 valid_bitlen[2]            = {0, 0};
    SINT32                 *p32              = NULL;
    HEVC_DEC_SLICE_PARAM_S *pSlicePara       = NULL;
    HEVC_DEC_SLICE_PARAM_S *pTargetSlicePara = NULL;
    VDMHAL_HWMEM_S         *pHwMem           = &g_HwMem[VdhId];
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    SINT32 ChanId = g_VdmDrvParam[VdhId].ChanId;
    SINT32 ModuleLowlyEnable = 0;
#endif

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
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
#endif

    /* 1.  检查参数是否超出规格 */
    VDMHAL_ASSERT_RET(NULL != pParam, "pParam is null\n");
    VDMHAL_ASSERT_RET(pParam->ApcSize <= HEVC_APC_SIZE, "FATAL: ApcSize > 16\n");

    if ( NULL == pHwMem->pVdmRegVirAddr )
    {
        if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr)) )
        {
            pHwMem->pVdmRegVirAddr = p32;
        }
        else
        {
            dprint(PRN_FATAL, "%s vdm register virtual address not mapped, reset failed!\n", __func__);
            return VDMHAL_ERR;
        }
    }

    if (1 == pParam->NewPicFlag)
    {
        //3716cv200
        //VDMHAL_ResetVdm(VdhId);
    }

    /* 2.  配置寄存器(启动寄存器除外) */
    HEVCHAL_V400R004_CfgVdmReg(pParam, pHwMem, VdhId);

    /*3.配置pic消息池*/
    HEVCHAL_V400R004_SetPicMsg(pParam, pHwMem, pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX], pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1]);
    /*4. 配置slice消息池*/

    pSlicePara = pParam->pFirstSlice;

    if (NULL == pSlicePara)
    {
        dprint(PRN_FATAL, "%s pFirstSlice = NULL!\n", __func__);
        return VDMHAL_ERR;
    }

    //如果 第一个 slice的起始宏块号不为0，则添加一个slice,长度置为1 ,防止逻辑挂死   l00214825
    if (pSlicePara->SliceSegmentTileAddress != 0)
    {
        slice_segment_tile_address = 0;
        end_ctb_in_slice_tile = pSlicePara->SliceSegmentTileAddress - 1;

        if (pParam->tiles_enabled_flag)
        {
            slice_segment_address = 0;      //g_TsToRsMap[0]=0
            end_ctb_in_slice_raster = pSlicePara->end_ctb_in_slice_raster;  //WriteSliceMsg()已经计算
        }
        else
        {
            slice_segment_address = slice_segment_tile_address;
            end_ctb_in_slice_raster = end_ctb_in_slice_tile;
        }

        tile_address_bak = pSlicePara->SliceSegmentTileAddress;
        valid_bitlen[0] = pSlicePara->valid_bitlen[0];
        valid_bitlen[1] = pSlicePara->valid_bitlen[1];
        bitsoffset[0] = pSlicePara->bitsoffset[0];
        bitsoffset[1] = pSlicePara->bitsoffset[1];
        bytespos[0] = pSlicePara->bytespos[0];
        bytespos[1] = pSlicePara->bytespos[1];
        pSlicePara->valid_bitlen[0] = 1;
        pSlicePara->valid_bitlen[1] = 0;
        pSlicePara->bitsoffset[0] = 0;
        pSlicePara->bitsoffset[1] = 0;
        pSlicePara->bytespos[0] = pParam->stream_base_addr;
        pSlicePara->bytespos[1] = 0;
        add_slice0_flag = 1;
        prev_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX];
        cur_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1];
        next_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + add_slice0_flag + 1];

        if (HEVCHAL_V400R004_SetSliceMsg(pParam, pHwMem, pSlicePara, cur_slcmsg_phy, prev_slcmsg_phy, next_slcmsg_phy, slice_segment_address, slice_segment_tile_address, end_ctb_in_slice_raster, end_ctb_in_slice_tile) != VDMHAL_OK)
        {
            dprint(PRN_ERROR, "%s 0: set slice msg failed!\n", __func__);
            return VDMHAL_ERR;
        }

        pSlicePara->SliceSegmentTileAddress = tile_address_bak;
        pSlicePara->valid_bitlen[0] = valid_bitlen[0];
        pSlicePara->valid_bitlen[1] = valid_bitlen[1];
        pSlicePara->bitsoffset[0] = bitsoffset[0];
        pSlicePara->bitsoffset[1] = bitsoffset[1];
        pSlicePara->bytespos[0] = bytespos[0];
        pSlicePara->bytespos[1] = bytespos[1];
    }

    valid_slice_num = 0;
    pre_end_ctb_in_slice_tile = 0;
    pic_end_ctb_in_raster = (pParam->PicWidthInCtbsYMinus1 + 1) * (pParam->PicHightInCtbsYMinus1 + 1) - 1;

    pTargetSlicePara  = pParam->pFirstSlice;

    for (i = 0; i < pParam->NumSlicePara; i++)
    {
        pSlicePara = pTargetSlicePara;
        prev_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + add_slice0_flag + i];
        cur_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX  + add_slice0_flag + 1 + i];

        if (NULL == pSlicePara)
        {
            dprint(PRN_ERROR, "%s: i = %d, pSlicePara = NULL!\n", __func__, i);
            return VDMHAL_ERR;
        }

        // 容错处理: 当前slice起始宏块号不能小于前一个slice的结束宏块号
        if ((pSlicePara->SliceSegmentTileAddress < pre_end_ctb_in_slice_tile) && (i > 0))
        {
            pTargetSlicePara = pTargetSlicePara->pNextSlice;
            dprint(PRN_ERROR, "SliceSegmentTileAddress %d < pre_end_ctb_in_slice_tile %d\n", pSlicePara->SliceSegmentTileAddress, pre_end_ctb_in_slice_tile);
            //continue;
            return VDMHAL_ERR;
        }

        //找next slice para,必须保证本slice para比next slice para的slice_segment_address小
        for (j = (i + 1); j < pParam->NumSlicePara; j++)
        {
            pTargetSlicePara = pTargetSlicePara->pNextSlice;

            if (pTargetSlicePara != NULL)
            {
                if (pSlicePara->SliceSegmentTileAddress < pTargetSlicePara->SliceSegmentTileAddress)
                {
                    break;
                }
            }
            else
            {
                dprint(PRN_ERROR, "%s pTargetSlicePara is NULL!\n", __func__);
                return VDMHAL_ERR;
            }
        }

        if ((j == pParam->NumSlicePara) || (HEVC_MAX_SLOT_NUM == (DN_V400R004_MSG_SLOT_INDEX + 1 + add_slice0_flag + i + 1)))
        {
            end_ctb_in_slice_raster = pic_end_ctb_in_raster;
            end_ctb_in_slice_tile   = end_ctb_in_slice_raster;
            next_slcmsg_phy         = 0;
            pSlicePara->pNextSlice  = NULL;
        }
        else
        {
            end_ctb_in_slice_tile = pTargetSlicePara->SliceSegmentTileAddress - 1;

            if (end_ctb_in_slice_tile < 0)
            {
                dprint(PRN_ERROR, "%s end_ctb_in_slice_tile(%d) < 0\n", __func__, end_ctb_in_slice_tile);
                return VDMHAL_ERR;
            }

            if (pParam->tiles_enabled_flag)
            {
                end_ctb_in_slice_raster = pTargetSlicePara->end_ctb_in_slice_raster;  //WriteSliceMsg()已经计算
            }
            else
            {
                end_ctb_in_slice_raster = end_ctb_in_slice_tile ;
            }

            next_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + add_slice0_flag + 1 + j];
        }

        // 容错处理: slice结束宏块号不能大于图像最后一个宏块号
        if (end_ctb_in_slice_raster > pic_end_ctb_in_raster || end_ctb_in_slice_tile > pic_end_ctb_in_raster)
        {
            dprint(PRN_ERROR, "end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%d) > pic_max_ctb(%d)\n", end_ctb_in_slice_raster, end_ctb_in_slice_tile, pic_end_ctb_in_raster);
            return VDMHAL_ERR;
        }

        pSlicePara->end_ctb_in_slice_tile = end_ctb_in_slice_tile;

        // 容错处理: 当前slice起始宏块号不能大于其结束宏块号
        if (pSlicePara->SliceSegmentTileAddress > pSlicePara->end_ctb_in_slice_tile)
        {
            pTargetSlicePara = pTargetSlicePara->pNextSlice;
            dprint(PRN_ERROR, "SliceSegmentTileAddress %d > end_ctb_in_slice_tile %d\n", pSlicePara->SliceSegmentTileAddress, pSlicePara->end_ctb_in_slice_tile);
            //continue;
            return VDMHAL_ERR;
        }

        i = j - 1;

        if (i == (pParam->NumSlicePara - 1))
        {
            pSlicePara->pNextSlice = NULL;
        }

        slice_segment_tile_address = pSlicePara->SliceSegmentTileAddress;
        slice_segment_address      = pSlicePara->slice_segment_address;

        if (HEVCHAL_V400R004_SetSliceMsg(pParam, pHwMem, pSlicePara, cur_slcmsg_phy, prev_slcmsg_phy, next_slcmsg_phy, slice_segment_address, slice_segment_tile_address, end_ctb_in_slice_raster, end_ctb_in_slice_tile) != VDMHAL_OK)
        {
            dprint(PRN_ERROR, "%s 1: set slice msg failed!\n", __func__);
            return VDMHAL_ERR;
        }

        valid_slice_num++;
        pre_end_ctb_in_slice_tile = pSlicePara->end_ctb_in_slice_tile;

        if (0 == next_slcmsg_phy)
        {
            break;
        }
    }

    /*5. cut down slice chain*/
    if (0 < pParam->NumSlicePara && valid_slice_num > 0)
    {
        HEVCHAL_V400R004_CutSliceChain(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1 + pParam->NumSlicePara + add_slice0_flag - 1]);
    }
    else
    {
        dprint(PRN_ERROR, "No slice to dec, add up msg report.\n");
        return VDMHAL_ERR;
    }

    return VDMHAL_OK;
}
