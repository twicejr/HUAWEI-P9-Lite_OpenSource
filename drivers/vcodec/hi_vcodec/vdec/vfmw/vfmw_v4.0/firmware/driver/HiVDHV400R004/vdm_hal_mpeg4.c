
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 文 件 名   : vdmv300plus_hal.c
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
#include 	"vdm_hal_v400r004_mpeg4.h"


/************************************************************************/
/*  模块内共享数据                                                      */
/************************************************************************/

/************************************************************************/
/*  自用函数申明                                                        */
/************************************************************************/
SINT32 MP4HAL_V400R004_CfgReg(MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId, UINT32 *pBaseAddr);
SINT32 MP4HAL_V400R004_CfgDnMsg(MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId);
SINT32 MP4HAL_V400R004_WriteSlicMsg(MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId, UADDR StreamBaseAddr);


/************************************************************************/
/*  函数实现                                                            */
/************************************************************************/
SINT32 MP4HAL_V400R004_Log2bin(UINT32 value)
{
    SINT16 n = 0;

    while (value != 0)
    {
        value >>= 1;
        n++;
    }

    return n;
}


/*****************************************************************************************
  原型 SINT32 VDMHAL_Init()
  功能 初始化VDMHAL.
  VDMHAL将"消息池"、"寄存器"等信息作为与通道无关的私有资源管理，但消息池是从上层程序
  分配的空间中划拨的，为了实现换台或重启解码器时VDMHAL可以更新消息池地址，必须对外实
  现一个初始化函数。
  本函数的具体功能是：清除静态信息。
  参数 无
  返回值 成功返回OK（0），否则返回错误码
 ******************************************************************************************/
SINT32 MP4HAL_V400R004_InitHal( UADDR CodeTabAddr )
{
    return VDMHAL_OK;
}

/*****************************************************************************************
  原型 SINT32 VDMHAL_Init()
  功能 初始化VDMHAL.
  VDMHAL将"消息池"、"寄存器"等信息作为与通道无关的私有资源管理，但消息池是从上层程序
  分配的空间中划拨的，为了实现换台或重启解码器时VDMHAL可以更新消息池地址，必须对外实
  现一个初始化函数。
  本函数的具体功能是：清除静态信息。
  参数 无
  返回值 成功返回OK（0），否则返回错误码
 ******************************************************************************************/
SINT32 MP4HAL_V400R004_StartDec( MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId )
{
    SINT32 ret;
    UADDR StreamBaseAddr = 0;

    /* 1.  检查参数是否超出规格 */
    VDMHAL_ASSERT_RET( pMp4DecParam->PicWidthInMb <= MAX_IMG_WIDTH_IN_MB, "picture width out of range");
    VDMHAL_ASSERT_RET( pMp4DecParam->PicHeightInMb <= MAX_IMG_HEIGHT_IN_MB, "picture width out of range");

    /* 配置寄存器 */
    ret = MP4HAL_V400R004_CfgReg(pMp4DecParam, VdhId, &StreamBaseAddr);

    if (VDMHAL_OK != ret)
    {
        dprint(PRN_FATAL, "MP4HAL_V400R004_CfgReg failed!\n");
        return VDMHAL_ERR;
    }

    /* 配置PIC DMSG */
    ret = MP4HAL_V400R004_CfgDnMsg(pMp4DecParam, VdhId);

    if (VDMHAL_OK != ret)
    {
        dprint(PRN_FATAL, "MP4HAL_V400R004_CfgDnMsg failed!\n");
        return VDMHAL_ERR;
    }

    /* 配置SLICE DMSG*/
    ret = MP4HAL_V400R004_WriteSlicMsg(pMp4DecParam, VdhId, StreamBaseAddr);

    if (VDMHAL_OK != ret)
    {
        dprint(PRN_FATAL, "MP4HAL_V400R004_WriteSlicMsg failed!\n");
        return VDMHAL_ERR;
    }

    return VDMHAL_OK;
}

/* 配置寄存器 */
SINT32 MP4HAL_V400R004_CfgReg(MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId, UINT32 *pBaseAddr)
{
    SINT32 D32;
    SINT32 datTmp;
    SINT32 i, k;
    UADDR stream_base_addr, tmp_base_addr;
    UINT32 height_in_mb;

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

    for (i = 0, stream_base_addr = 0xFFFFFFFF; i < pMp4DecParam->SlcNum; i++)
    {
        /*查找最小的码流包地址作为基地址时，如果有分包的情况，则码流包开头并非起始码，因此不要在此判断*/
        for (k = 0; k < 2; k++)
        {
            if ((pMp4DecParam->SlcPara[i].phy_address[k] > 0) && (pMp4DecParam->SlcPara[i].bit_len[k] > 0))
            {
                tmp_base_addr = (pMp4DecParam->SlcPara[i].phy_address[k]) & 0xFFFFFFF0;
                stream_base_addr = (stream_base_addr < tmp_base_addr) ? stream_base_addr : tmp_base_addr;
            }
        }
    }

    if (stream_base_addr == 0xFFFFFFFF)
    {
        dprint(PRN_FATAL, "stream_base_addr = %#x\n", stream_base_addr);
        return VDMHAL_ERR;
    }

    *pBaseAddr = stream_base_addr;
    pMp4DecParam->StreamBaseAddr = stream_base_addr;

    //BASIC_V400R004_CFG0
    /* 2.  配置寄存器(启动寄存器除外) */
    D32 = 0;
    D32 = ((pMp4DecParam->PicWidthInMb * pMp4DecParam->PicHeightInMb - 1) & 0x000FFFFF) // [15:0] mbamt_to_dec
          | ( 1 << 22 )
          | ( 0 << 23 )
          | ( 0 << 24 )
          | ( 1 << 25 )
          | ( 1 << 30 )     // ld_qmatrix_flag
#ifdef ENV_SOS_KERNEL
          | ( 1 << 31 );    // Secure Mode
#else
          | ( 0 << 31 );    // Normal Mode
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG0=0x%x\n", D32);

    //BASIC_V400R004_CFG1
    D32 = 0x2               // [3:0] video_standard
          | ( 0 << 13 )     // uv_order_en
          | ( 1 << 14 )     // [14] fst_slc_grp
          | ( 1 << 15 )     // [15] mv_output_en
          | ( 1 << 16 )     // [27:16] max_slcgrp_num
          | ( 0 << 28)      // line_num_output_en
          | ( 1 << 29)
          | ( (pMp4DecParam->Compress_en & 1) << 30)   //compress_en
          | ( 0 << 31 );    // [31] ppfd_en   0==not ppfd dec
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG1=0x%x\n", D32);

    //AVM_V400R004_ADDR
    D32 = g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;  // mpeg4 down msg
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "AVM_V400R004_ADDR=0x%x\n", D32);

    //VAM_V400R004_ADDR
    D32 = g_HwMem[VdhId].MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;  // mpeg4 up msg
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "VAM_V400R004_ADDR=0x%x\n", D32);

    //STREAM_V400R004_BASE_ADDR
    D32 = stream_base_addr;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "STREAM_V400R004_BASE_ADDR=0x%x\n", D32);

    //EMAR_ID
    if (pMp4DecParam->PicWidthInMb > 120)
    {
        D32 = 0;
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

    //YSTADDR_V400R004_1D
    D32 = pMp4DecParam->CurPicPhyAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTADDR_V400R004_1D=0x%x\n", D32);

    //YSTRIDE_V400R004_1D
    D32 = pMp4DecParam->VahbStride;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTRIDE_V400R004_1D=0x%x\n", D32);

    //UVOFFSET_V400R004_1D
    height_in_mb = pMp4DecParam->PicHeightInMb;
    D32 = (pMp4DecParam->VahbStride) * ((height_in_mb + 1) / 2) * 2;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId );
    dprint(PRN_VDMREG, "UVOFFSET_V400R004_1D=0x%x\n", D32);

    //PRCNUM_1D_CNT
    D32 = 0;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId );
    //  dprint(PRN_VDMREG, "PRCNUM_1D_CNT=0x%x\n", D32);

    D32 = 0;
    WR_VREG( VREG_V400R004_FF_APT_EN, 0, VdhId );
    dprint(PRN_VDMREG, "PRCMEM2_1D_CNT=0x%x\n", D32);

    // 清除中断
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );

    return VDMHAL_OK;
}

/* 配置 pic 下行消息 */
SINT32 MP4HAL_V400R004_CfgDnMsg(MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId)
{
    UINT8 *pMsgBlock;
    UINT32 *pReg;
    UINT32 Dat;
    SINT32 i, j;//k;
    UINT32 WidthInMb, HeightInMb, MbCnt;
    SINT32 bitNumofMbCnt;
    SINT32 MbTotal;

    WidthInMb  = pMp4DecParam->PicWidthInMb;
    HeightInMb = pMp4DecParam->PicHeightInMb;
    MbCnt   = WidthInMb * HeightInMb;
    MbTotal = MbCnt;
    bitNumofMbCnt = MP4HAL_V400R004_Log2bin(MbCnt);

    /* step1: basic config < D0 ~ D7 > */
    pMsgBlock = (UINT8 *)MEM_Phy2Vir(g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX]);

    if (NULL == pMsgBlock)
    {
        dprint(PRN_FATAL, "line: %d ,pMsgBlock = NULL is not expected value!\n", __LINE__);
        return VDMHAL_ERR;
    }

    pReg = (UINT32 *)pMsgBlock;

    if ( 1 == pMp4DecParam->IsShortHeader)
    {
        /* short header!*/
        /* D0 */
        Dat = 4; // [2] is_short_header
        WR_MSGWORD( pReg, Dat );
        dprint(PRN_DNMSG, "D0=0x%x\n", Dat);

        /* D1 */
        Dat = ((UINT32)( (pMp4DecParam->VopGobNum - 1) & 0x1F ) << 0)  // [4:0] num_gobs_in_vop
              | ((UINT32)( (pMp4DecParam->GobMbNum) & 0x7F ) << 5)       // [11:5] num_macroblocks_in_gob
              | ((UINT32)( pMp4DecParam->VopQuant & 0x1F ) << 26);       // [30:26] vop_quant
        ++pReg;
        WR_MSGWORD( pReg, Dat );
        dprint(PRN_DNMSG, "D1=0x%x\n", Dat);

        /* D2 */
        Dat = ((UINT32)( pMp4DecParam->PicCodingType & 3 ) << 5)   // [6:5] vop_coding_type
              | ((UINT32)( bitNumofMbCnt & 0x0F ) << 22);            // [25:22] bit_num_of_mbnum
        ++pReg;
        WR_MSGWORD( pReg, Dat );
        dprint(PRN_DNMSG, "D2=0x%x\n", Dat);
    }
    else
    {
        /* D0 */
        Dat = 0;
        WR_MSGWORD( pReg, Dat );
        dprint(PRN_DNMSG, "D0=0x%x\n", Dat);

        /* D1 */
        Dat = ((UINT32)( pMp4DecParam->VopQuant & 0x1F ) << 26)    // [30:26] vop_quant
              | ((UINT32)( pMp4DecParam->PicQuantType & 1 ) << 31);  // [31] quant_type
        ++pReg;
        WR_MSGWORD( pReg, Dat );
        dprint(PRN_DNMSG, "D1=0x%x\n", Dat);

        if ( 2 == pMp4DecParam->PicCodingType ) //B_VOP
        {
            pMp4DecParam->vop_rounding_type = 0;
        }

        /* D2 */
        Dat = ((UINT32)( pMp4DecParam->Interlaced & 1 ) )    // [0] interlaced
              | ((UINT32)( pMp4DecParam->top_field_first & 1 ) << 1)    // [1] top_field_first
              | ((UINT32)( pMp4DecParam->alternate_vertical_scan & 1 ) << 2) // [2] alternative_vertical_scan_flag
              | ((UINT32)( pMp4DecParam->vop_rounding_type & 1 ) << 3)  // [3] vop_rounding_type
              | ((UINT32)( pMp4DecParam->QuarterSample & 1 ) << 4)  // [4] quarter_sample
              | ((UINT32)( pMp4DecParam->PicCodingType & 3 ) << 5) // [6:5] vop_coding_type
              | ((UINT32)( pMp4DecParam->resync_marker_disable & 1 ) << 7) // [7] resync_marker_disable
              | ((UINT32)( pMp4DecParam->intra_dc_vlc_thr & 7 ) << 8) // [10:8] intra_dc_vlc_thr
              | ((UINT32)( pMp4DecParam->FwdFcode & 7 ) << 11) // [13:11] vop_fcode_forward
              | ((UINT32)( pMp4DecParam->BwdFcode & 7 ) << 14) // [16:14] vop_fcode_backward
              | ((UINT32)( pMp4DecParam->BitsOfVopTimeIncr & 0x1F ) << 17)  // [21:17] bit_num_of_voptimeincrement
              | ((UINT32)( bitNumofMbCnt & 0x0F ) << 22)// [25:22] bit_num_of_mbnum
              | ((UINT32)( pMp4DecParam->sprite_enable & 3 ) << 26)
              | ((UINT32)( pMp4DecParam->sprite_warping_accuracy & 3 ) << 28)
              | ((UINT32)( pMp4DecParam->sprite_warping_points & 3 ) << 30);//实际的point，根据参数化简后的结果
        ++pReg;
        WR_MSGWORD( pReg, Dat );
        dprint(PRN_DNMSG, "D2=0x%x\n", Dat);

        /* D3 */
        if ( 2 == pMp4DecParam->PicCodingType ) //B_VOP
        {
            /*bp,pp硬件只用16比特表示的,如果数据超过16bit,则软件计算最大公约数,同等简化 */
            if (pMp4DecParam->Trd > 65535)
            {
                /*寻最大公约数,将bp,pp等比减小 */
                //wait for adding
            }

            Dat = ((pMp4DecParam->Trb << 1) & 0xFFFF) |  //  [15:0] trb
                  ( ((pMp4DecParam->Trd << 1) & 0xFFFF) << 16 ); // [31:16] trd
            ++pReg;
            WR_MSGWORD( pReg, Dat );
            dprint(PRN_DNMSG, "D3=0x%x\n", Dat);
        }
    }

    /* D4 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 4 );
    Dat = (((UINT32)(pMp4DecParam->PicWidthInMb - 1)) & 0x0000FFFF) |
          ((((UINT32)(pMp4DecParam->PicHeightInMb - 1)) & 0x0000FFFF) << 16);
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D4=0x%x\n", Dat);
    /* 显示宽高: D5 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 5 );
    Dat = ((UINT32)(pMp4DecParam->image_width))
          | ((UINT32)(pMp4DecParam->image_height) << 16);
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D5=0x%x\n", Dat);

    if (pMp4DecParam->PicCodingType == 3)
    {
        if (pMp4DecParam->sprite_warping_points == 1)
        {
            if (pMp4DecParam->FF_BUG_DIVX500B413 == 1)
            {
                /* GMC_1PT_MVX: D6 */
                pReg = (UINT32 *)( pMsgBlock + 4 * 6 );
                Dat = (UINT32)(pMp4DecParam->Uo / (1 << (pMp4DecParam->sprite_warping_accuracy - pMp4DecParam->QuarterSample)));
                WR_MSGWORD( pReg, Dat );
                dprint(PRN_DNMSG, "D6=0x%x\n", Dat);
                /* GMC_1PT_MVY: D7 */
                pReg = (UINT32 *)( pMsgBlock + 4 * 7 );
                Dat = (UINT32)(pMp4DecParam->Vo / (1 << (pMp4DecParam->sprite_warping_accuracy - pMp4DecParam->QuarterSample)));
                WR_MSGWORD( pReg, Dat );
                dprint(PRN_DNMSG, "D7=0x%x\n", Dat);
            }
            else
            {
                /* GMC_1PT_MVX: D6 */
                pReg = (UINT32 *)( pMsgBlock + 4 * 6 );
                Dat = (UINT32)RSHIFT(pMp4DecParam->Uo << pMp4DecParam->QuarterSample, pMp4DecParam->sprite_warping_accuracy);
                WR_MSGWORD( pReg, Dat );
                dprint(PRN_DNMSG, "D6=0x%x\n", Dat);
                /* GMC_1PT_MVY: D7 */
                pReg = (UINT32 *)( pMsgBlock + 4 * 7 );
                Dat = (UINT32)RSHIFT(pMp4DecParam->Vo << pMp4DecParam->QuarterSample, pMp4DecParam->sprite_warping_accuracy);
                WR_MSGWORD( pReg, Dat );
                dprint(PRN_DNMSG, "D7=0x%x\n", Dat);
            }

        }
    }

    /* step2: bitstream < D8 ~ D15 > */
    pReg = (UINT32 *)( pMsgBlock + 4 * 8 );
    /* D8 */
    Dat = 0;//StreamPhyAddr[0] & 0x00FFFFFF; //偏移地址
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D8=0x%x\n", Dat);

    /* D9 */
    Dat = 0;//((StreamBitOffset[0]<<24)&0x7F000000) | (StreamLength[0]&0x00FFFFFF);
    ++pReg;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D9=0x%x\n", Dat);

    /* D10 */
    Dat = 0;//StreamPhyAddr[1] & 0x00FFFFFF;
    ++pReg;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D10=0x%x\n", Dat);

    /* D11 */
    Dat = 0;//((StreamBitOffset[1]<<24)&0x7F000000) | (StreamLength[1]&0x00FFFFFF);
    ++pReg;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D11=0x%x\n", Dat);


    /* step3: space arrangement < D12 ~ D23 > */

    /* D12: image_curr_recon_addr */
    Dat = (pMp4DecParam->DispFramePhyAddr + 0xF) & 0xFFFFFFF0;
    pReg++;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D12= 0x%x\n", Dat);

    /* D13: image_forward_ref_addr */
    Dat = (pMp4DecParam->FwdRefPicPhyAddr + 0xF) & 0xFFFFFFF0;
    pReg++;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D13= 0x%x\n", Dat);

    /* D14: image_backward_ref_addr */
    Dat = (pMp4DecParam->BwdRefPicPhyAddr + 0xF) & 0xFFFFFFF0;
    pReg++;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D14= 0x%x\n", Dat);

    /* D15: pmv_colmb_addr */
    Dat = (pMp4DecParam->CurPmvPhyAddr + 0xF) & 0xFFFFFFF0;
    pReg++;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D15= 0x%x\n", Dat);

    /* D16: pmv_backward_ref_addr */
    Dat = (pMp4DecParam->BwdPmvPhyAddr + 0xF) & 0xFFFFFFF0;
    pReg++;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D16= 0x%x\n", Dat);

    /* D17: sed_top_addr */
    Dat = (g_HwMem[VdhId].ItransTopAddr + 0xF) & 0xFFFFFFF0;
    pReg++;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D17= 0x%x\n", Dat);

    /* D18: pmv_top_addr */
    Dat = (g_HwMem[VdhId].PmvTopAddr + 0xF) & 0xFFFFFFF0;
    pReg++;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D18= 0x%x\n", Dat);

    /*D19*/
    pMp4DecParam->FF_BUG_QPEL_FILED = 0;
#if 1

    if (pMp4DecParam->PicCodingType == 3)
    {
        if (pMp4DecParam->sprite_warping_points == 1)
        {
            /*1pt扩边规则依然是由FF_BUG_EDGE_EXTEND决定*/
            pMp4DecParam->FF_BUG_EDGE_FIND_POINT = 1;
        }

        if (pMp4DecParam->sprite_warping_points > 1)
        {
            /*23pt扩边规则与取点规则一致，均由FF_BUG_EDGE_EXTEND决定*/
            pMp4DecParam->FF_BUG_EDGE_FIND_POINT = pMp4DecParam->FF_BUG_EDGE_EXTEND;
        }
    }
    else
    {
        pMp4DecParam->FF_BUG_EDGE_FIND_POINT = pMp4DecParam->FF_BUG_EDGE_EXTEND;
    }

#else
    p_syntax_des->FF_BUG_EDGE_FIND_POINT = 0;
    //p_syntax_des->FF_BUG_EDGE_EXTEND = 0;
#endif
    //pMp4DecParam->FF_BUG_EDGE_FIND_POINT = 1;
    //pMp4DecParam->FF_BUG_EDGE_EXTEND = 1;
    Dat = ((UINT32)(pMp4DecParam->FF_BUG_QPEL_CHROMA & 1))
          | ((UINT32)(pMp4DecParam->FF_BUG_QPEL_CHROMA2 & 1) << 1)
          | ((UINT32)(pMp4DecParam->FF_BUG_EDGE_EXTEND & 1) << 2)
          | ((UINT32)(pMp4DecParam->FF_BUG_EDGE_FIND_POINT & 1) << 3)
          //|((UINT32)(pMp4DecParam->FF_BUG_DIVX500B413 & 1) << 4)
          | ((UINT32)(pMp4DecParam->FF_BUG_QPEL_FILED & 1) << 4)
          | (0 << 16);
    pReg++;
    //dprint(PRN_ALWS,"DAT %#x\n", Dat);
    //Dat = 0;//test
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D19= 0x%x\n", Dat);
#if 1
    /* W' : D20 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 20 );
    Dat = pMp4DecParam->dU[0];
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D20= 0x%x\n", Dat);

    /* W' : D21 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 21 );
    Dat = pMp4DecParam->dU[1];
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D21= 0x%x\n", Dat);

    /* W' : D22 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 22 );
    Dat = pMp4DecParam->dV[0];
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D22= 0x%x\n", Dat);

    /* W' : D23 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 23 );
    Dat = pMp4DecParam->dV[1];
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D23= 0x%x\n", Dat);

    /* W' : D24 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 24 );
    Dat = pMp4DecParam->Uo;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D24= 0x%x\n", Dat);

    /* W' : D25 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 25 );
    Dat = pMp4DecParam->Vo;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D25= 0x%x\n", Dat);

    /* W' : D26 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 26 );
    Dat = pMp4DecParam->Uco;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D26= 0x%x\n", Dat);

    /* W' : D27 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 27 );
    Dat = pMp4DecParam->Vco;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D27= 0x%x\n", Dat);
#endif
    /* step4: quant table < D28 ~ D59 > */
    pReg = (UINT32 *)( pMsgBlock + 4 * 28 );

    if ( (NON_SHORT_HEADER_ID == pMp4DecParam->IsShortHeader) && (0 != pMp4DecParam->PicQuantType) ) //NON_SHORT_HEADER_ID
    {
        /*
           for ( i = 0; i < 4; i++ )
           {
           for ( j = 0; j < 16; j += 2 )
           {
           Dat = ((SINT32)(pMp4DecParam->IntraQuantTab[i*16+j] ) )
           | ((SINT32)(pMp4DecParam->NonintraQuantTab[i*16+j]) << 8 )
           | ((SINT32)(pMp4DecParam->IntraQuantTab[i*16+j+1]) << 16 )
           | ((SINT32)(pMp4DecParam->NonintraQuantTab[i*16+j+1]) << 24 );
           WR_MSGWORD( pReg, Dat );
           pReg++;
           dprint(PRN_DNMSG, "D%d= 0x%x\n", i*8+j/2+28, Dat);
           }
           }
           */

        for ( i = 0; i < 8; i++ )
        {
            for ( j = 0; j < 2; j ++ )
            {
                Dat = ((SINT32)(pMp4DecParam->IntraQuantTab[i + j * 8 + 0] ) )
                      | ((SINT32)(pMp4DecParam->IntraQuantTab[i + j * 8 + 16]) << 8 )
                      | ((SINT32)(pMp4DecParam->IntraQuantTab[i + j * 8 + 32]) << 16 )
                      | ((SINT32)(pMp4DecParam->IntraQuantTab[i + j * 8 + 48]) << 24 );
                pReg = (UINT32 *)(pMsgBlock + 4 * 28 + 4 * (2 * i + j));
                WR_MSGWORD( pReg, Dat );
                dprint(PRN_DNMSG, "D%d= 0x%x\n", i * 8 + j / 2 + 24, Dat);
            }
        }

        for ( i = 0; i < 8; i++ )
        {
            for ( j = 0; j < 2; j ++ )
            {
                Dat = ((SINT32)(pMp4DecParam->NonintraQuantTab[i + j * 8 + 0] ) )
                      | ((SINT32)(pMp4DecParam->NonintraQuantTab[i + j * 8 + 16]) << 8 )
                      | ((SINT32)(pMp4DecParam->NonintraQuantTab[i + j * 8 + 32]) << 16 )
                      | ((SINT32)(pMp4DecParam->NonintraQuantTab[i + j * 8 + 48]) << 24 );
                pReg = (UINT32 *)(pMsgBlock + 4 * 28  + 4 * (16 + 2 * i + j));
                WR_MSGWORD( pReg, Dat );
                dprint(PRN_DNMSG, "D%d= 0x%x\n", i * 8 + j / 2 + 24, Dat);
            }
        }
    }

    /* W' : D60 */
    pReg = (UINT32*)( pMsgBlock + 4*60 );
    Dat = g_HwMem[VdhId].SedTopAddr & 0xFFFFFFF0;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D60= 0x%x\n", Dat);

    /* W' : D63 */
    pReg = (UINT32 *)( pMsgBlock + 4 * 63 );
    Dat = g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] + 4 * 64;
    WR_MSGWORD( pReg, Dat );
    dprint(PRN_DNMSG, "D63= 0x%x\n", Dat);

    return VDMHAL_OK;

}

/* 配置 slice 下行消息 */
SINT32 MP4HAL_V400R004_WriteSlicMsg(MP4_DEC_PARAM_S *pMp4DecParam, SINT32 VdhId, UADDR StreamBaseAddr)
{
    SINT32 i, j;
    UINT32 D32 = 0;
    SINT32 SliceNum = pMp4DecParam->SlcNum;
    MP4_SLICE_INFO *SliceInfo = pMp4DecParam->SlcPara;
    SINT32 slice_end_mbn = 0;
    UADDR  next_slice_para_addr = 0, bit_stream_address_0, bit_stream_address_1;
    SINT32  bit_offset_0, bit_offset_1;
    UINT32 *SlcDnMsgVirAddr;
    UADDR   SlcDnMsgPhyAddr;
    SINT32 AddSlice0Flag = 0;

    SlcDnMsgPhyAddr = g_HwMem[VdhId].MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] + 4 * 64;
    SlcDnMsgVirAddr = (UINT32 *)MEM_Phy2Vir(SlcDnMsgPhyAddr);

    if (NULL == SlcDnMsgVirAddr)
    {
        dprint(PRN_FATAL, "%s: SlcDnMsgVirAddr = NULL\n", __func__);
        return VDMHAL_ERR;
    }

    if (SliceInfo[0].mb_start_num != 0)
    {
        i = 0;
        //D0
        D32 = 0;
        bit_stream_address_0 = (SliceInfo[i].phy_address[0] & 0xFFFFFFF0);
        bit_offset_0 = SliceInfo[i].bit_offset[0] + (SliceInfo[i].phy_address[0] & 0x0F) * 8;
        ((MP4SLCDNMSG_V400R004_D0 *)(&D32))->bit_len_0 = 0;
        ((MP4SLCDNMSG_V400R004_D0 *)(&D32))->bit_offset_0 = bit_offset_0;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 0, D32);
        dprint(PRN_DNMSG, "D0 = %#x \n", D32);

        //D1
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D1 *)(&D32))->bit_stream_address_0 = bit_stream_address_0 - StreamBaseAddr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 1, D32);
        dprint(PRN_DNMSG, "D1 = %#x \n", D32);

        //D2
        D32 = 0;
        bit_stream_address_1 = (SliceInfo[i].phy_address[1] & 0xFFFFFFF0);
        bit_offset_1 = SliceInfo[i].bit_offset[1] + (SliceInfo[i].phy_address[1] & 0x0F) * 8;
        ((MP4SLCDNMSG_V400R004_D2 *)(&D32))->bit_len_1 = 0;
        ((MP4SLCDNMSG_V400R004_D2 *)(&D32))->bit_offset_1 = bit_offset_1;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 2, D32);
        dprint(PRN_DNMSG, "D2 = %#x \n", D32);

        //D3
        D32 = 0;

        if (SliceInfo[i].phy_address[1] > 0)
        {
            ((MP4SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = bit_stream_address_1 - StreamBaseAddr;
        }
        else
        {
            ((MP4SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = 0;
        }

        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 3, D32);
        dprint(PRN_DNMSG, "D3 = %#x \n", D32);

        //D4
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_quant = SliceInfo[i].vop_quant;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_coding_type = SliceInfo[i].vop_coding_type;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->intra_dc_vlc_thr = SliceInfo[i].intra_dc_vlc_thr;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_fcode_forward = SliceInfo[i].vop_fcode_forward;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_fcode_backward = SliceInfo[i].vop_fcode_backward;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 4, D32);
        dprint(PRN_DNMSG, "D4 = %#x \n", D32);

        //D5
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D5 *)(&D32))->slice_start_mbn = 0;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 5, D32);
        dprint(PRN_DNMSG, "D5 = %#x \n", D32);

        //D6
        D32 = 0;
        slice_end_mbn = (SliceInfo[0].mb_start_num) - 1;
        ((MP4SLCDNMSG_V400R004_D6 *)(&D32))->slice_end_mbn = slice_end_mbn;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 6, D32);
        dprint(PRN_DNMSG, "D6 = %#x \n", D32);
        //D7
        D32 = 0;
        next_slice_para_addr = SlcDnMsgPhyAddr + (i + 1) * 4 * 8;
        ((MP4SLCDNMSG_V400R004_D7 *)(&D32))->next_slice_para_addr = next_slice_para_addr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 7, D32);
        dprint(PRN_DNMSG, "D7 = %#x \n", D32);

        AddSlice0Flag = 1;

    }

    for (i = 0; i < SliceNum ; i++)
    {
        if ((SliceInfo[i].mb_start_num <= SliceInfo[i - 1].mb_start_num) && (i > 0))
        {
            continue;
        }

        //D0
        D32 = 0;
        bit_stream_address_0 = (SliceInfo[i].phy_address[0] & 0xFFFFFFF0);
        bit_offset_0 = SliceInfo[i].bit_offset[0] + (SliceInfo[i].phy_address[0] & 0x0F) * 8;
        ((MP4SLCDNMSG_V400R004_D0 *)(&D32))->bit_len_0 = SliceInfo[i].bit_len[0];
        ((MP4SLCDNMSG_V400R004_D0 *)(&D32))->bit_offset_0 = bit_offset_0;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 0 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D0 = %#x \n", D32);

        //D1
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D1 *)(&D32))->bit_stream_address_0 = bit_stream_address_0 - StreamBaseAddr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 1 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D1 = %#x \n", D32);

        //D2
        D32 = 0;
        bit_stream_address_1 = (SliceInfo[i].phy_address[1] & 0xFFFFFFF0);
        bit_offset_1 = SliceInfo[i].bit_offset[1] + (SliceInfo[i].phy_address[1] & 0x0F) * 8;
        ((MP4SLCDNMSG_V400R004_D2 *)(&D32))->bit_len_1 = SliceInfo[i].bit_len[1];
        ((MP4SLCDNMSG_V400R004_D2 *)(&D32))->bit_offset_1 = bit_offset_1;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 2 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D2 = %#x \n", D32);

        //D3
        D32 = 0;

        if (SliceInfo[i].phy_address[1] > 0)
        {
            ((MP4SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = bit_stream_address_1 - StreamBaseAddr;
        }
        else
        {
            ((MP4SLCDNMSG_V400R004_D3 *)(&D32))->bit_stream_address_1 = 0;
        }

        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 3 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D3 = %#x \n", D32);

        //D4
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_quant = SliceInfo[i].vop_quant;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_coding_type = SliceInfo[i].vop_coding_type;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->intra_dc_vlc_thr = SliceInfo[i].intra_dc_vlc_thr;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_fcode_forward = SliceInfo[i].vop_fcode_forward;
        ((MP4SLCDNMSG_V400R004_D4 *)(&D32))->vop_fcode_backward = SliceInfo[i].vop_fcode_backward;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 4 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D4 = %#x \n", D32);

        //D5
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D5 *)(&D32))->slice_start_mbn = SliceInfo[i].mb_start_num;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 5 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D5 = %#x \n", D32);

        for (j = (i + 1); j < SliceNum; j++)
        {
            if (SliceInfo[i].mb_start_num < SliceInfo[j].mb_start_num)
            {
                break;
            }
        }

        if (j == SliceNum)
        {
            slice_end_mbn = ((pMp4DecParam->PicWidthInMb) * (pMp4DecParam->PicHeightInMb)) - 1;
            next_slice_para_addr = 0;
        }
        else
        {
            slice_end_mbn = (SliceInfo[j].mb_start_num) - 1;
            next_slice_para_addr = SlcDnMsgPhyAddr + j * 4 * 8 + AddSlice0Flag * 4 * 8;
        }

        //D6
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D6 *)(&D32))->slice_end_mbn = slice_end_mbn;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 6 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D6 = %#x \n", D32);
        //D7
        D32 = 0;
        ((MP4SLCDNMSG_V400R004_D7 *)(&D32))->next_slice_para_addr = next_slice_para_addr;
        WR_MSGWORD(SlcDnMsgVirAddr + i * 8 + 7 + AddSlice0Flag * 4 * 8, D32);
        dprint(PRN_DNMSG, "D7 = %#x \n", D32);

        i = j - 1;
    }

    return VDMHAL_OK;
}


