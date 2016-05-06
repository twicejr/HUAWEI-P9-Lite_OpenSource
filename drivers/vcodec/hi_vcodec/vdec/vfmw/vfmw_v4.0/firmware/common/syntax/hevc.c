/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r34h86uRmYnCq/RIoXGPYXMJbh16KjuqSUjxZ+lpYgivW6ILK60yih04IihJ/5HMKqthF
CfBXwHSO69C8VIiL9GFYGbDbRF7MIqnj2P8w/y3uNa5VGuiH9xG+xBjA8sILdg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/


#include    "syntax.h"
#include    "hevc.h"
#include    "public.h"
#include    "bitstream.h"
#include	"vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


/* HEVC模块编译开关，如果没有打开则不编译 */
#ifdef HEVC_ENABLE

#define TEST_PRINT_ENABLE 0

extern UINT8 g_allow_B_before_P;

static const SINT32 g_CropUnitX[4] = {1,2,2,1};
static const SINT32 g_CropUnitY[4] = {1,2,1,1};

static const UINT8  g_HEVCNalTypeEOPIC[] = {0x00, 0x00, 0x01, 0x60, 0x00, 0x48, 0x53, 0x50, 0x49, 0x43, 0x45, 0x4E, 0x44};

static const UINT32 quant_ts_default[4] = {0x10101010, 0x10101010, 0x10101010, 0x10101010};

static UINT8 g_quantTSDefault4x4[16] =
{
    16, 16, 16, 16,
    16, 16, 16, 16,
    16, 16, 16, 16,
    16, 16, 16, 16
};

static UINT8 g_quantIntraDefault8x8[64] =
{
    16, 16, 16, 16, 17, 18, 21, 24,
    16, 16, 16, 16, 17, 19, 22, 25,
    16, 16, 17, 18, 20, 22, 25, 29,
    16, 16, 18, 21, 24, 27, 31, 36,
    17, 17, 20, 24, 30, 35, 41, 47,
    18, 19, 22, 27, 35, 44, 54, 65,
    21, 22, 25, 31, 41, 54, 70, 88,
    24, 25, 29, 36, 47, 65, 88, 115
};

static UINT32 quant8_intra_default[16] =
{
    0x10101010, 0x18151211, 0x10101010, 0x19161311,
    0x12111010, 0x1d191614, 0x15121010, 0x241f1b18,
    0x18141111, 0x2f29231e, 0x1b161312, 0x41362c23,
    0x1f191615, 0x58463629, 0x241d1918, 0x7358412f
};

static UINT8 g_quantInterDefault8x8[64] =
{
    16, 16, 16, 16, 17, 18, 20, 24,
    16, 16, 16, 17, 18, 20, 24, 25,
    16, 16, 17, 18, 20, 24, 25, 28,
    16, 17, 18, 20, 24, 25, 28, 33,
    17, 18, 20, 24, 25, 28, 33, 41,
    18, 20, 24, 25, 28, 33, 41, 54,
    20, 24, 25, 28, 33, 41, 54, 71,
    24, 25, 28, 33, 41, 54, 71, 91
};

static const UINT32 quant8_inter_default[16] =
{
    0x10101010, 0x18141211, 0x11101010, 0x19181412,
    0x12111010, 0x1c191814, 0x14121110, 0x211c1918,
    0x18141211, 0x29211c19, 0x19181412, 0x3629211c,
    0x1c191814, 0x47362921, 0x211c1918, 0x5b473629
};

static UINT32  s_auiSigLastScan[HEVC_MAX_CU_DEPTH][HEVC_MAX_CU_SIZE *HEVC_MAX_CU_SIZE];     //z00290437 20141016 仅保存对角扫描映射
HEVC_TMP_PARAM_SET_S s_TmpParam;
UINT32 g_TsToRsMap[HEVC_MAX_MB_NUM];
UINT8  g_IsDeced[HEVC_MAX_MB_NUM];

VOID HEVC_InitScalingOrderTable(HEVC_CTX_S *pHevcCtx)
{
    SINT32 i, c;
	
	for (i=0;i<sizeof(pHevcCtx->aucConvertToBit);i++)
	{
		pHevcCtx->aucConvertToBit[i] = -1;
	}

  #if 0 // 这个会越界
	c=0;
	for (i=4; i<HEVC_MAX_CU_SIZE; i*=2)
	{
	    pHevcCtx->aucConvertToBit[i] = c;
		c++;
	}
	pHevcCtx->aucConvertToBit[i] = c;
  #else
	c=0;
	for (i=2; i<HEVC_MAX_CU_DEPTH; i++)
	{
	    pHevcCtx->aucConvertToBit[(1<<i)] = c;
		c++;
	}
  #endif
	
	c=2;
	for (i=0; i<HEVC_MAX_CU_DEPTH; i++)
	{  
        HEVC_InitSigLastScan(pHevcCtx, NULL, NULL, NULL, s_auiSigLastScan[i], c, c, i);
        c <<= 1;
	}  

    return;
}


VOID HEVC_InitSigLastScan(HEVC_CTX_S *pHevcCtx, UINT32 *pBuffZ, UINT32 *pBuffH, UINT32 *pBuffV, UINT32 *pBuffD, SINT32 iWidth, SINT32 iHeight, SINT32 iDepth)
{
    UINT32 uiNumScanPos;
    UINT32 uiNextScanPos = 0;
    SINT32 uiScanLine, iPrimDim, iScndDim;
    UINT32 *pBuffTemp;
    UINT32 uiNumBlkSide, uiNumBlks, uiBlk, initBlkPos;
    SINT32 log2Blk;
    UINT32 offsetY, offsetX, offsetD, offsetScan;


    uiNumScanPos  = iWidth * iWidth;

    if (iWidth < 16)
    {
        pBuffTemp = pBuffD;

        if (8 == iWidth)
        {
            pBuffTemp = pHevcCtx->sigLastScanCG32x32;
        }

        for (uiScanLine = 0; uiNextScanPos < uiNumScanPos; uiScanLine++)
        {
            iPrimDim = uiScanLine;
            iScndDim = 0;

            while (iPrimDim >= iWidth)
            {
                iScndDim++;
                iPrimDim--;
            }

            while (iPrimDim >= 0 && iScndDim < iWidth)
            {
                pBuffTemp[uiNextScanPos] = iPrimDim * iWidth + iScndDim ;
                uiNextScanPos++;
                iScndDim++;
                iPrimDim--;
            }
        }
    }

    if (iWidth > 4)
    {
        uiNumBlkSide = iWidth >> 2;
        uiNumBlks	 = uiNumBlkSide * uiNumBlkSide;
        log2Blk		 = pHevcCtx->aucConvertToBit[uiNumBlkSide] + 1;

        for (uiBlk = 0; uiBlk < uiNumBlks; uiBlk++)
        {
            uiNextScanPos = 0;
            initBlkPos    = s_auiSigLastScan[ log2Blk ][ uiBlk ];

            if (32 == iWidth)
            {
                initBlkPos = pHevcCtx->sigLastScanCG32x32[uiBlk];
            }

            offsetY	= initBlkPos / uiNumBlkSide;
            offsetX	= initBlkPos - offsetY * uiNumBlkSide;
            offsetD	= 4 * (offsetX + offsetY * iWidth);
            offsetScan = 16 * uiBlk;

            for (uiScanLine = 0; uiNextScanPos < 16; uiScanLine++)
            {
                iPrimDim = uiScanLine ;
                iScndDim = 0;

                while (iPrimDim >= 4)
                {
                    iScndDim++;
                    iPrimDim--;
                }

                while (iPrimDim >= 0 && iScndDim < 4)
                {
                    pBuffD[uiNextScanPos + offsetScan] = iPrimDim * iWidth + iScndDim + offsetD;
                    uiNextScanPos++;
                    iScndDim++;
                    iPrimDim--;
                }


            }
        }
    }

    return;
}


#define CONST_DAR_235_100  (235*1024/100)
#define CONST_DAR_221_100  (221*1024/100)
#define CONST_DAR_16_9  (16*1024/9)
#define CONST_DAR_4_3   (4*1024/3)
SINT32  HEVCGetDar(SINT32 ar_idc, SINT32 sar_width, SINT32 sar_height, SINT32 img_width, SINT32 img_height)
{
    static SINT32 SarTable[][2] =
    {
        { 1, 1}, { 1, 1}, {12, 11}, {10, 11}, {16, 11}, {40, 33}, {24, 11}, {20, 11}, {32, 11}, {80, 33},
        {18, 11}, {15, 11}, {64, 33}, {160, 99}, {4, 3}, { 3, 2}, { 2, 1}
    };
    SINT32 dar, final_dar = DAR_UNKNOWN;

    if (ar_idc == 0 || (ar_idc > 16 && ar_idc != 255) || ((sar_width == 0 || sar_height == 0) && (ar_idc == 255)))
    {
        final_dar = DAR_UNKNOWN;
    }
    /* z56361, 2011-11-21.
       sample_aspect_ratio = 1:1本来意味着显示宽高比等于图象的宽度:高度，以下分支本来无错. 但目前VO把1:1理解为无效，
       做法是填充输出窗口，这使得显示效果不可控.
       鉴于各种条件VO不敢做改动，以免使现有效果被改变而引起客户投诉. 未来VO会对宽高比做一次彻底重构，所以暂时把下面
       ar_idc==1的分支去掉，以配合VO把眼下的问题解决掉. */
    else if (ar_idc == 1)
    {
        final_dar = DAR_IMG_SIZE;
    }
    else
    {
        if (ar_idc != 255)
        {
            sar_width  = SarTable[ar_idc][0];
            sar_height = SarTable[ar_idc][1];
        }

        //dar = (sar_width * img_width * 1024) / (sar_height * img_height);
        /* 20131012: l165842 上面的计算方法有可能导致数值(sar_width * img_width * 1024)
           溢出，最终将导致SINT32类型的da值为 -1 */
        dar = (((sar_width * 1024) / (sar_height)) * ((img_width * 1024) / (img_height))) / 1024;

        if (ABS(dar - CONST_DAR_235_100) < ABS(dar - CONST_DAR_221_100))
        {
            final_dar = DAR_235_100;
        }
        else if (ABS(dar - CONST_DAR_221_100) < ABS(dar - CONST_DAR_16_9))
        {
            final_dar = DAR_221_100;
        }
        else if (ABS(dar - CONST_DAR_16_9) < ABS(dar - CONST_DAR_4_3))
        {
            final_dar = DAR_16_9;
        }
        else
        {
            final_dar = DAR_4_3;
        }
    }

    dprint(PRN_DBG, "dar=%d\n", final_dar);

    return final_dar;
}

VOID HEVC_PrintNaluArraySlot(HEVC_CTX_S *pHevcCtx)
{
    UINT32 Pos;

    dprint(PRN_ERROR, "--------------- PrintNaluArraySlot START ---------------\n");

    for (Pos = 0; Pos < pHevcCtx->MaxSlotNum + 1; Pos++)
    {
        dprint(PRN_ERROR, "NalArray[%d]=%p,is_valid=%d   ", Pos, &pHevcCtx->pNalArray[Pos], pHevcCtx->pNalArray[Pos].is_valid);

        if (Pos % 10 == 0)
        {
            dprint(PRN_ERROR, "\n");
        }
    } 
    dprint(PRN_ERROR, "\n");
    dprint(PRN_ERROR, "--------------- PrintNaluArraySlot END ---------------\n");
    
    return;
}

VOID HEVC_PrintCurrSlicelistX(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;

    dprint(PRN_ERROR, "--------------- PrintCurrSlicelistX START ---------------\n");
    dprint(PRN_ERROR, "List0, size: %d\n", pHevcCtx->CurrSlice.listXsize[0]);
    for (i=0; i<pHevcCtx->CurrSlice.listXsize[0]; i++)
    {
        dprint(PRN_ERROR, "pListX[0][%d]:%p ", i, pHevcCtx->pListX[0][i]); 
        if (pHevcCtx->pListX[0][i] != NULL)
        {
            dprint(PRN_ERROR, "pFrameStore:%p ", pHevcCtx->pListX[0][i]->frame_store); 
            if (pHevcCtx->pListX[0][i]->frame_store != NULL)
            {
                dprint(PRN_ERROR, "pLogicFs:%p ", FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->pListX[0][i]->frame_store->logic_fs_id));
            }
        }
        dprint(PRN_ERROR, "\n");
    }
    
    dprint(PRN_ERROR, "List1, size: %d\n", pHevcCtx->CurrSlice.listXsize[1]);
    for (i=0; i<pHevcCtx->CurrSlice.listXsize[1]; i++)
    {
        dprint(PRN_ERROR, "pListX[1][%d]: %p", i, pHevcCtx->pListX[1][i]); 
        if (pHevcCtx->pListX[1][i] != NULL)
        {
            dprint(PRN_ERROR, "pFrameStore:%p ", pHevcCtx->pListX[1][i]->frame_store); 
            if (pHevcCtx->pListX[1][i]->frame_store != NULL)
            {
                dprint(PRN_ERROR, "pLogicFs:%p ", FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->pListX[1][i]->frame_store->logic_fs_id));
            }
        }
        dprint(PRN_ERROR, "\n");
    }
    dprint(PRN_ERROR, "--------------- PrintCurrSlicelistX END ---------------\n");
    
    return;
}

VOID HEVC_PrintFrameStoreState(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;
    UINT32 usrdat_idx;

    dprint(PRN_ERROR, "--------------- PrintFrameStoreState START ---------------\n");
    for (i=0; i<pHevcCtx->TotalFsNum; i++)
    {
        dprint(PRN_ERROR, "Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displayed=%d ", 
            i, &pHevcCtx->FrameStore[i], pHevcCtx->FrameStore[i].eFrameStoreState, pHevcCtx->FrameStore[i].is_reference, pHevcCtx->FrameStore[i].is_displayed);

        for (usrdat_idx=0; usrdat_idx <4; usrdat_idx++)
        {
            dprint(PRN_ERROR, "p_usrdat[%d]=%p ", usrdat_idx, pHevcCtx->FrameStore[i].fs_image.p_usrdat[usrdat_idx]);
        }   
        dprint(PRN_ERROR, "\n");
    }
    dprint(PRN_ERROR, "--------------- PrintFrameStoreState END ---------------\n");
    
    return;
}

VOID HEVC_PrintAPCState(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;

    dprint(PRN_ERROR, "--------------- PrintAPCState START ---------------\n");
    
    dprint(PRN_ERROR,"APC.used_size:%d, APC.size:%d\n", pHevcCtx->APC.used_size, pHevcCtx->APC.size);
    for (i=0; i<HEVC_APC_SIZE; i++)
	{
        dprint(PRN_ERROR,"%d: is_used=%d, idc=%d, poc=%d\n", i, pHevcCtx->APC.is_used[i], pHevcCtx->APC.idc[i], pHevcCtx->APC.poc[i]);
	}
    dprint(PRN_ERROR, "--------------- PrintAPCState END ---------------\n");
    
    return;
}

VOID HEVC_PrintDPBState(HEVC_CTX_S *pHevcCtx)
{
    FSP_LOGIC_FS_S* pLogicFs ;
    FSP_PHY_FS_S* pDecFs;
    FSP_PHY_FS_S* pDispFs; 
    UINT32 j;

    dprint(PRN_ERROR, "--------------- PrintDPBState START ---------------\n");
    
    dprint(PRN_ERROR,"DPB: size:%d, used_size:%d, negative:%d, positive:%d, longterm:%d\n", pHevcCtx->DPB.size, pHevcCtx->DPB.used_size, pHevcCtx->DPB.negative_ref_frames_in_buffer, pHevcCtx->DPB.positive_ref_frames_in_buffer, pHevcCtx->DPB.ltref_frames_in_buffer);
    for (j=0; j<pHevcCtx->DPB.used_size; j++)
    {     
        dprint(PRN_ERROR,"fs[%d]:%p non_existing:%d state:%d is_ref:%d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_ref:%d fsp_disp:%d logic_id:%d img_id:%d\n",
                j,pHevcCtx->DPB.fs[j], pHevcCtx->DPB.fs[j]->non_existing, pHevcCtx->DPB.fs[j]->eFrameStoreState, 
                pHevcCtx->DPB.fs[j]->is_reference,pHevcCtx->DPB.fs[j]->is_displayed,
                pHevcCtx->DPB.fs[j]->poc,pHevcCtx->DPB.fs[j]->frame.is_long_term,
                FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id),
                FSP_GetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id),
                FSP_GetDisplay(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id),
                pHevcCtx->DPB.fs[j]->logic_fs_id,pHevcCtx->DPB.fs[j]->fs_image.image_id);
    }
        
    dprint(PRN_ERROR,"\n");   
    for (j=0; j<pHevcCtx->DPB.used_size; j++)
    {
        pLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id);
        pDecFs   = FSP_GetDecPhyFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id);
        pDispFs  = FSP_GetDispPhyFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id);             
        dprint(PRN_ERROR,"fs[%d]\t",j);
        if (pLogicFs != NULL)
        {
            dprint(PRN_ERROR,"LogicFs:%p\t",pLogicFs);
            dprint(PRN_ERROR,"LogicTick:%d\t",pLogicFs->u32Tick);
			dprint(PRN_ERROR,"IsRef:%d\t",pLogicFs->s32IsRef);
			dprint(PRN_ERROR,"s32DispState:%d\t",pLogicFs->s32DispState);
        }
        else
        {
            dprint(PRN_ERROR,"LogicFs:Null\t");
        }
        
        if (pDecFs != NULL)
        {
            dprint(PRN_ERROR,"DecFs:%p\t",pDecFs);
            dprint(PRN_ERROR,"DecTick:%d\t",pDecFs->u32Tick);
        }
        else
        {
            dprint(PRN_ERROR,"DecFs:Null\t");
        }
        
        if (pDispFs != NULL)
        {
            dprint(PRN_ERROR,"DispFs:%p\t",pDispFs);
            dprint(PRN_ERROR,"DispTick:%d\t",pDispFs->u32Tick);
        }
        else
        {
            dprint(PRN_ERROR,"DispFs:Null\t");
        }
                         
        dprint(PRN_ERROR,"\n");          
    }       
    
    dprint(PRN_ERROR, "--------------- PrintDPBState END ---------------\n");

    return;
}


/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_IsSliceUnit()
*   功能描述 :  检测当前nal unit是否是一个slice
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/	
SINT8 HEVC_IsSliceUnit(UINT32 nal_unit_type) 
{
    return ((NAL_UNIT_CODED_SLICE_TRAIL_R    == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_TRAIL_N    == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_TLA_R      == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_TSA_N      == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_STSA_R     == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_STSA_N     == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_BLA_W_LP   == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_BLA_W_RADL == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_BLA_N_LP   == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_IDR_W_RADL == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_IDR_N_LP   == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_CRA        == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_RADL_N     == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_RADL_R     == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_RASL_N     == nal_unit_type) \
         || (NAL_UNIT_CODED_SLICE_RASL_R     == nal_unit_type))\
            ? 1 : 0;
}

/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_IsIUnit()
*   功能描述 :  检测该帧是否指示I unit type
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/	
SINT8 HEVC_IsIUnit(UINT32 nal_unit_type) 
{
    return (nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_W_RADL \
         || nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_N_LP   \
         || nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_N_LP   \
         || nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_RADL \
         || nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_LP   \
         || nal_unit_type == NAL_UNIT_CODED_SLICE_CRA)
            ? 1 : 0;
}

/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_IsNonRefPic()
*   功能描述 :  检测该帧是否指示为非参考帧
*   参数说明 :  该函数能判定该帧是否一定不被参考，不会误判但会漏判
*   返回值   ：
************************************************************************
*/
SINT32 HEVC_IsNonRefPic(UINT32 nal_unit_type)
{
    return (nal_unit_type == NAL_UNIT_CODED_SLICE_TRAIL_N \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_TSA_N   \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_STSA_N  \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_RADL_N  \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_RASL_N  \
            || nal_unit_type == NAL_UNIT_RESERVED_VCL_N10    \
            || nal_unit_type == NAL_UNIT_RESERVED_VCL_N12    \
            || nal_unit_type == NAL_UNIT_RESERVED_VCL_N14)
           ? 1 : 0;
}

/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_IsFlushUnit()
*   功能描述 :  检测该帧是否指示Flush DPB
*   参数说明 :
*   返回值   ：
************************************************************************
*/
SINT32 HEVC_IsFlushUnit(UINT32 nal_unit_type)
{
    return (nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_W_RADL    \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_N_LP   \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_N_LP   \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_RADL \
            || nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_LP)
           ? 1 : 0;
}


/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_IsPVRFlushPic()
*   功能描述 :  pvr检测该帧是否当成IDR帧
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/	
SINT32 HEVC_IsPVRFlushPic(HEVC_CTX_S *pHevcCtx) 
{
    return ((HEVC_I_FRAME == pHevcCtx->CurrPic.pic_type)
	     && (1 == pHevcCtx->pstExtraData->stPvrInfo.u32BFrmRefFlag)
	     && (0 == pHevcCtx->pstExtraData->stPvrInfo.u32IDRFlag)
	     && (0 == pHevcCtx->pstExtraData->stPvrInfo.u32ContinuousFlag)
	     && (!(pHevcCtx->pstExtraData->s32FastForwardBackwardSpeed >= -1024 && pHevcCtx->pstExtraData->s32FastForwardBackwardSpeed <= 1024)))
		     ? 1 : 0;
}


VOID HEVC_InitDecPara(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;
    
    dprint(PRN_DBG, "Init dec para\n");

    pHevcCtx->LastDisplayPoc = -HEVC_MAX_INT;

    // nal array refresh
    HEVC_ClearAllNal(pHevcCtx);

    ResetVoQueue(&pHevcCtx->ImageQue);
    for (i=0; i<HEVC_MAX_FRAME_STORE; i++)
    {
        pHevcCtx->FrameStore[i].non_existing = 0;                 //a real pic;
        pHevcCtx->FrameStore[i].eFrameStoreState = FS_NOT_USED;   //empty;
        pHevcCtx->FrameStore[i].is_reference = 0;                 //not pic used for ref;
        pHevcCtx->FrameStore[i].poc = 0;
        pHevcCtx->FrameStore[i].is_displayed = 0;                 
        pHevcCtx->FrameStore[i].pmv_address_idc = HEVC_MAX_PMV_STORE;
        pHevcCtx->FrameStore[i].apc_idc = HEVC_APC_SIZE;
        memset(&pHevcCtx->FrameStore[i].fs_image, 0, sizeof(IMAGE));
        pHevcCtx->FrameStore[i].fs_image.image_id = i;        
        pHevcCtx->FrameStore[i].frame.frame_store = & pHevcCtx->FrameStore[i];
        pHevcCtx->FrameStore[i].frame.structure = 0;              //g_frame is frame, will be change when field paired   
    }

    // pmv slot refresh every stream
    for (i=0; i<HEVC_MAX_PMV_STORE; i++)
    {
        pHevcCtx->PmvStoreUsedFlag[i] = 0; 
    }

    // msg slot refresh every stream
    for (i = 0; i < pHevcCtx->MaxSlotNum; i++)
    {
        pHevcCtx->pMsgSlot[i].slot_addr_ph = 0;
        pHevcCtx->pMsgSlot[i].slot_addr_vir = NULL;
        pHevcCtx->pMsgSlot[i].slice_nal = NULL;
    }

    // init apc
    memset(&pHevcCtx->APC, 0, sizeof(HEVC_APC_S));
    pHevcCtx->APC.size = HEVC_APC_SIZE;

    // pHevcCtx->DPB refresh every stream
	for (i=0; i<HEVC_MAX_DPB_NUM; i++)		
    {
        pHevcCtx->DPB.fs[i] = pHevcCtx->DPB.fs_negative_ref[i] = pHevcCtx->DPB.fs_positive_ref[i] = pHevcCtx->DPB.fs_ltref[i] = NULL;
    }
    pHevcCtx->DPB.used_size = 0;
    pHevcCtx->DPB.max_long_term_pic_idx = 0;
    pHevcCtx->DPB.ltref_frames_in_buffer = 0;
    pHevcCtx->DPB.negative_ref_frames_in_buffer = 0;
    pHevcCtx->DPB.positive_ref_frames_in_buffer = 0;
	pHevcCtx->DPB.size = HEVC_MAX_DPB_NUM;

    // list refresh every stream
    for (i=0; i<HEVC_MAX_LIST_SIZE; i++)
    {
        pHevcCtx->pListX[0][i] = pHevcCtx->pListX[1][i] = NULL;
    }

    // init some global var
    pHevcCtx->pCurrNal = NULL;

    // refresh some statistic variable
    pHevcCtx->NumSlicePara = 0;
    pHevcCtx->MaxBytesReceived = 0;
	pHevcCtx->TotalSliceNum = 0;
    pHevcCtx->CurrMsgSlotNum = HEVC_SLICE_SLOT_START_NUM - 1;

    // init pHevcCtx->CurrSlice 
    memset(&pHevcCtx->CurrSlice, 0, sizeof(HEVC_SLICE_SEGMENT_HEADER));
    pHevcCtx->CurrSlice.slice_type = HEVC_I_SLICE;
    pHevcCtx->CurrSlice.new_pic_type = IS_NEW_PIC;

    pHevcCtx->bPPicFound = 0;
    pHevcCtx->bNewSequence = HEVC_TRUE;
    pHevcCtx->bNoOutputOfPriorPicsFlag = HEVC_FALSE;
    pHevcCtx->bNoRaslOutputFlag = HEVC_TRUE;

    pHevcCtx->AllowStartDec = 0;
    pHevcCtx->TotalFsNum  = HEVC_MAX_FRAME_STORE;   // change while pHevcCtx->DPB.size change
    pHevcCtx->TotalPmvNum = HEVC_MAX_PMV_STORE;     // change while pHevcCtx->DPB.size change

    pHevcCtx->BitDepthY = 8;
    pHevcCtx->BitDepthC = 8;
    pHevcCtx->PocRandomAccess = HEVC_MAX_INT;
    pHevcCtx->PrevRAPIsBLA = HEVC_FALSE;

    pHevcCtx->scalingListSize[0] = 16;
    pHevcCtx->scalingListSize[1] = 64;
    pHevcCtx->scalingListSize[2] = 256;
    pHevcCtx->scalingListSize[3] = 1025;

    pHevcCtx->scalingListSizeX[0] = 4;
    pHevcCtx->scalingListSizeX[1] = 8;
    pHevcCtx->scalingListSizeX[2] = 16;
    pHevcCtx->scalingListSizeX[3] = 32;

    pHevcCtx->scalingListNum[0] = 6;
    pHevcCtx->scalingListNum[1] = 6;
    pHevcCtx->scalingListNum[2] = 6;
    pHevcCtx->scalingListNum[3] = 2;
    
	memset(&pHevcCtx->Bs,0,sizeof(BS));  
	pHevcCtx->pBS = &pHevcCtx->Bs;
    
    return;
}


SINT32 HEVCDEC_DecodePacket(HEVC_CTX_S *pHevcCtx,HEVC_STREAM_PACKET *pPacket)
{
    SINT32 ret = HEVC_DEC_ERR;
    SINT32 RefNum =0, ReadNum = 0, NewNum = 0;
    SINT32 IsNewPic, IsSizeChanged;

    if (NULL == pPacket)
    {
    	dprint(PRN_FATAL, "HEVCDEC_DecodePacket NULL == pPacket!\n");
        return HEVC_DEC_ERR;
    }

    if (pHevcCtx->bIsInit != 1)
    {
    	dprint(PRN_FATAL, "HevcCtx not init!\n");
        return HEVC_DEC_ERR;
    }
    
    pHevcCtx->AdvancedCfg  = (pHevcCtx->pstExtraData->s32DecMode << 16) & 0x70000;
    pHevcCtx->RefErrorThr  = pHevcCtx->pstExtraData->s32RefErrThr;
    pHevcCtx->OutErrorThr  = pHevcCtx->pstExtraData->s32OutErrThr;

    // 接收到一个包并将其拼成一个完整的Nalu, 注意RecivePacket有三个返回值
    if (1 != pHevcCtx->bHaveNalNotDecoded)
    {
        if((1 == pHevcCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
           (1 == pHevcCtx->pstExtraData->s32WaitFsFlag) && \
           (1 == pHevcCtx->u32SCDWrapAround))
        {
            pHevcCtx->pCurrNal = pHevcCtx->pLastNal;  
            pHevcCtx->u32SCDWrapAround = 0;
        }
        else
        {
            ret = HEVC_ReceivePacket(pHevcCtx, pPacket);
            pHevcCtx->pLastNal = pHevcCtx->pCurrNal;
        }
    }
    else
    {
        ret = (NULL != pHevcCtx->pCurrNal) ? HEVC_DEC_NORMAL: HEVC_DEC_ERR;
		if (ret == HEVC_DEC_ERR)
		{
			dprint(PRN_FATAL, "HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\n");
            return HEVC_DEC_ERR;
		}
    }
    pHevcCtx->bHaveNalNotDecoded = 0; 

	if (ret == HEVC_DEC_NORMAL)
	{
		pHevcCtx->pCurrNal->nal_bitoffset = 0;
		
        BsInit(pHevcCtx->pBS, (UINT8 *)(((pHevcCtx->pCurrNal->stream[0].streamBuffer))), pHevcCtx->pCurrNal->stream[0].bitstream_length);
		// 丢弃起始码 0x00 0x00 0x01
		BsSkip(pHevcCtx->pBS, 24);

		pHevcCtx->pCurrNal->forbidden_zero_bit		= BsGet(pHevcCtx->pBS, 1);
		pHevcCtx->pCurrNal->nal_unit_type			= BsGet(pHevcCtx->pBS, 6);
		pHevcCtx->pCurrNal->nuh_reserved_zero_6bits = BsGet(pHevcCtx->pBS, 6);
		pHevcCtx->pCurrNal->nuh_temporal_id 		= BsGet(pHevcCtx->pBS, 3) - 1;

		if (1 == HEVC_IsSliceUnit(pHevcCtx->pCurrNal->nal_unit_type))
		{
			// HEVC_InquireSliceProperty 注意目的是检查是否是new pic
			if ( HEVC_DEC_NORMAL == HEVC_InquireSliceProperty(pHevcCtx, &IsNewPic, &IsSizeChanged) )
			{
                // 如果还有Slice未解码，说明还未遇到NALU_TYPE_EOPIC，就主动插入一个NALU_TYPE_EOPIC
				if ( (1 == IsNewPic) && (HEVC_DEC_NORMAL == HEVC_HaveSliceToDec(pHevcCtx)) )  
				{				
					pHevcCtx->pCurrNal->nal_bitoffset = 0;
					// 主动插入一个EOP nal
					BsInit(&(pHevcCtx->Bs), (UINT8 *)(g_HEVCNalTypeEOPIC), sizeof(g_HEVCNalTypeEOPIC));
                    BsSkip(pHevcCtx->pBS, 40);
					pHevcCtx->pCurrNal->nal_unit_type = NAL_UNIT_EOPIC;

					pHevcCtx->bIsInsertEOPICNal = 1;
					HEVC_DecOneNal(pHevcCtx);
					pHevcCtx->NewPicCounter++;
					pHevcCtx->bHaveNalNotDecoded = 1;  //记住刚才有一个NAL未处理

					return HEVC_NOTDEC;
				}
                
				if (1 == IsSizeChanged)
				{	
                    // SizeChanged时，需要检测下一帧要求flush还是empty DPB
                    if (HEVC_IsFlushUnit(pHevcCtx->CurrSlice.nal_unit_type))
                    {    
                        ret = HEVC_FlushOutputFrmFromDPB(pHevcCtx);
                        if (HEVC_DEC_NORMAL != ret)
                        {
                            dprint(PRN_ERROR,"%s call HEVC_FlushOutputFrmFromDPB failed\n", __func__);   
                        }
                    }
                    if (HEVC_TRUE == pHevcCtx->bNoOutputOfPriorPicsFlag)
                    {
                        ret = HEVC_EmptyFrmFromDPB(pHevcCtx);
                        if (HEVC_DEC_NORMAL != ret)
                        {
                            dprint(PRN_ERROR,"%s call HEVC_EmptyFrmFromDPB failed\n", __func__);   
                        }
                    }
                    
					VCTRL_GetChanImgNum(pHevcCtx->ChanID, &RefNum, &ReadNum, &NewNum);
					if (pHevcCtx->pstExtraData->stChanOption.s32ReRangeEn == 1)
					{
                     #ifdef PRODUCT_KIRIN
                        if (NewNum > 0)
                        {
                            pHevcCtx->bHaveNalNotDecoded = 1;  //记住刚才有一个NAL未处理(等原尺寸的帧流尽)
                            return HEVC_NOTDEC;
                        }
                     #else
						// 需要原尺寸全部帧流尽
						if (ReadNum + NewNum > 0) //ReadNum:读出但未释放的帧，NewNum:新插入帧
						{
							pHevcCtx->bHaveNalNotDecoded = 1;  //记住刚才有一个NAL未处理(等原尺寸的帧流尽)
							return HEVC_NOTDEC;
						}
                     #endif
					}
				}	
			}
			else
			{
				dprint(PRN_ERROR, "HEVC_InquireSliceProperty error.\n");
				HEVC_ClearCurrNal(pHevcCtx);
				REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID);
				return HEVC_DEC_ERR;
			}
		}
            
        // 赋g_BS中的值, BS的初始化需要从word对齐的位置开始，因为在前面已经解析了Slice头，所以Slice单元不需要初始化
        if (1 != HEVC_IsSliceUnit(pHevcCtx->pCurrNal->nal_unit_type))
        {
			pHevcCtx->pCurrNal->nal_bitoffset = 0;
			BsInit(&(pHevcCtx->Bs), (UINT8 *)((pHevcCtx->pCurrNal->stream[0].streamBuffer)), pHevcCtx->pCurrNal->stream[0].bitstream_length);
                     
			// scd切割码流与pv不一致,这里进行适配
			BsSkip(pHevcCtx->pBS,24);
                     
			// 这里是冗余,到时候再考虑删除
			pHevcCtx->pCurrNal->forbidden_zero_bit		= BsGet(pHevcCtx->pBS, 1);
			pHevcCtx->pCurrNal->nal_unit_type			= BsGet(pHevcCtx->pBS, 6);
			pHevcCtx->pCurrNal->nuh_reserved_zero_6bits = BsGet(pHevcCtx->pBS, 6);
			pHevcCtx->pCurrNal->nuh_temporal_id 		= BsGet(pHevcCtx->pBS, 3) - 1;	
		}
        
		ret = HEVC_DecOneNal(pHevcCtx);
        if(HEVC_NOTDEC == ret)
        {
            return HEVC_NOTDEC;
        }
		else if (HEVC_DEC_NORMAL != ret)
		{
			dprint(PRN_DBG, "HEVC_DecOneNal ERR\n");
			return HEVC_DEC_ERR;
		}
		else
		{
			return HEVC_DEC_NORMAL;
		}

	}
	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_DecOneNal(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    UINT32 code0, code1;//add for eopic
    UINT32 i;

    for (i=0; i<pHevcCtx->pCurrNal->nal_segment; i++)
    {
       pHevcCtx->MaxBytesReceived += pHevcCtx->pCurrNal->stream[i].bitstream_length;
    }
    pHevcCtx->pCurrNal->nal_used_segment = 0; // decode from first segment    

    if (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_EOS || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_EOB)
    {
            pHevcCtx->bNewSequence = HEVC_TRUE;
		
    }

    pHevcCtx->pCurrNal->nal_bitoffset += 16;   // used bits when decode nal, 使用了16 bit    

	switch (pHevcCtx->pCurrNal->nal_unit_type)
	{
	    case NAL_UNIT_VPS:
			ret = HEVC_DecVPS(pHevcCtx);
			HEVC_ClearCurrNal(pHevcCtx);
			if (HEVC_DEC_NORMAL != ret)
			{
				dprint(PRN_ERROR, "VPS decode error.\n");  
				REPORT_STRMERR(pHevcCtx->ChanID, HEVC_VPS_ERR);
				REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID); 
				return HEVC_DEC_ERR;
			}
			break;
		case NAL_UNIT_SPS:		
			ret = HEVC_DecSPS(pHevcCtx);
			HEVC_ClearCurrNal(pHevcCtx);
			if (HEVC_DEC_NORMAL != ret)
			{
				dprint(PRN_ERROR, "SPS decode error.\n");  
				REPORT_STRMERR(pHevcCtx->ChanID, HEVC_SPS_ERR);
				REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID); 
				return HEVC_DEC_ERR;
			}
			break;
		case NAL_UNIT_PPS:
			ret = HEVC_DecPPS(pHevcCtx);
			HEVC_ClearCurrNal(pHevcCtx);
			if (HEVC_DEC_NORMAL != ret)
			{
				dprint(PRN_ERROR, "PPS decode error.\n");  
				REPORT_STRMERR(pHevcCtx->ChanID, HEVC_PPS_ERR);
				REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID); 
				return HEVC_DEC_ERR;
			}
			break;
          case NAL_UNIT_PREFIX_SEI:
          case NAL_UNIT_SUFFIX_SEI:
             ret = HEVC_DecSEI(pHevcCtx);
			 HEVC_ClearCurrNal(pHevcCtx);
			 if (HEVC_DEC_NORMAL != ret)
			 {
				 dprint(PRN_ERROR, "SEI decode error.\n");	
				 REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID); 
				 return HEVC_DEC_ERR;
			 }
             break;
                
		case NAL_UNIT_CODED_SLICE_TRAIL_R:
		case NAL_UNIT_CODED_SLICE_TRAIL_N:
		case NAL_UNIT_CODED_SLICE_TLA_R:
		case NAL_UNIT_CODED_SLICE_TSA_N:
		case NAL_UNIT_CODED_SLICE_STSA_R:
		case NAL_UNIT_CODED_SLICE_STSA_N:
		case NAL_UNIT_CODED_SLICE_BLA_W_LP:
		case NAL_UNIT_CODED_SLICE_BLA_W_RADL:
		case NAL_UNIT_CODED_SLICE_BLA_N_LP:
		case NAL_UNIT_CODED_SLICE_IDR_W_RADL:
		case NAL_UNIT_CODED_SLICE_IDR_N_LP:
		case NAL_UNIT_CODED_SLICE_CRA:
		case NAL_UNIT_CODED_SLICE_RADL_N:
		case NAL_UNIT_CODED_SLICE_RADL_R:
        case NAL_UNIT_CODED_SLICE_RASL_N:
		case NAL_UNIT_CODED_SLICE_RASL_R:
			ret = HEVC_DecSlice(pHevcCtx);
            if(HEVC_NOTDEC == ret)
            {
                return HEVC_NOTDEC;
            }
			else if (HEVC_DEC_NORMAL != ret)
			{
				HEVC_ClearCurrSlice(pHevcCtx);
				REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID);
				return HEVC_DEC_ERR;
			}	
            	
			break;

		case NAL_UNIT_EOPIC:
			//真正的NAL_UNIT_RESERVED_VCL_N10类型nal,不进行特殊处理,
			//否则为每一帧结尾插入的特殊nal
			if (pHevcCtx->bIsInsertEOPICNal != 1)
			{
                HEVC_ClearCurrNal(pHevcCtx);
				if (HEVC_PIC_EMPTY == pHevcCtx->CurrPic.state)
                {
                    break;
                }
			}			
			pHevcCtx->bIsInsertEOPICNal = 0;
			code0 = BsGet(&(pHevcCtx->Bs), 32);
            code1 = BsGet(&(pHevcCtx->Bs), 32);
            if (HISI_STREAM_END_CODE1 == code0 && HISI_STREAM_END_CODE2 == code1)
            {
                REPORT_MEET_NEWFRM(pHevcCtx->ChanID);
                ret = HEVC_DecVDM(pHevcCtx);  // 启动VDM解码

                if (HEVC_DEC_NORMAL != ret)
                {
                    REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID);
                    return HEVC_DEC_ERR;
                }
	        }
			break;    
        case NAL_UNIT_EOSTREAM:      
			//真正的NAL_UNIT_RESERVED_VCL_N11类型nal,不进行特殊处理, 
            code0 = (UINT32)BsGet(&(pHevcCtx->Bs), 32);
    	    code1 = (UINT32)BsGet(&(pHevcCtx->Bs), 32);
            if (HEVC_STREAM_END_CODE1 == code0 && HEVC_STREAM_END_CODE2 == code1)
            {
                pHevcCtx->IsStreamEndFlag = 1;
                REPORT_MEET_NEWFRM(pHevcCtx->ChanID);
                ret = HEVC_DecVDM(pHevcCtx);  // 启动VDM解码
                if (HEVC_DEC_NORMAL != ret)
                {
    	            REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID);
                    return HEVC_DEC_ERR;
                }
            }
            HEVC_ClearCurrNal(pHevcCtx);
            break;
		default:
			dprint(PRN_DBG, "***** NAL: UNSUPPORT, nal_unit_type=%d\n", pHevcCtx->pCurrNal->nal_unit_type);

            
            if (pHevcCtx->pCurrNal->nal_unit_type <= NAL_UNIT_UNSPECIFIED_63)
			{
				HEVC_ClearCurrNal(pHevcCtx);
			}
			else
			{
				REPORT_UNSUPPORT(pHevcCtx->ChanID);
				HEVC_ClearCurrNal(pHevcCtx);
				REPORT_DECSYNTAX_ERR(pHevcCtx->ChanID);
			}
			break;
	}

    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
* 函数原型 : SINT32 HEVC_CalcTileInfo()
* 功能描述 : 计算逻辑用的Tile信息
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_CalcTileInfo(HEVC_CTX_S *pHevcCtx, UINT8 TileId[2][HEVC_MAX_CTB_NUM_PER_LINE], UINT32 TilePosX[HEVC_LOGIC_TILE_COLUMNS_LIMIT][2], UINT32 TilePosY[HEVC_LOGIC_TILE_ROWS_LIMIT][2])
{
    SINT32 TileX,TileY;
    SINT32 Start, End;
    SINT32 idx;
    SINT32 log2_ctb_sizeY   = pHevcCtx->pCurrSPS->log2_ctb_sizeY;
    SINT32 num_tile_columns = pHevcCtx->pCurrPPS->num_tile_columns;
    SINT32 num_tile_rows    = pHevcCtx->pCurrPPS->num_tile_rows;

    if (num_tile_columns <= 0 || num_tile_columns > HEVC_LOGIC_TILE_COLUMNS_LIMIT)
    {
		dprint(PRN_ERROR, "%s num_tile_columns(%d) out of range(0, %d].\n", __func__, num_tile_columns, HEVC_LOGIC_TILE_COLUMNS_LIMIT);
        return HEVC_DEC_ERR;
    }
    if(num_tile_rows <= 0 || num_tile_rows > HEVC_LOGIC_TILE_ROWS_LIMIT)
    {
		dprint(PRN_ERROR, "%s num_tile_rows(%d) out of range(0, %d].\n", __func__, num_tile_rows, HEVC_LOGIC_TILE_ROWS_LIMIT);
        return HEVC_DEC_ERR;
    }
    
    memset(TileId,   0, sizeof(UINT8) * 2 * HEVC_MAX_CTB_NUM_PER_LINE);

    memset(TilePosX, 0, sizeof(UINT32)*HEVC_LOGIC_TILE_COLUMNS_LIMIT * 2);

    memset(TilePosY, 0, sizeof(UINT32)*HEVC_LOGIC_TILE_ROWS_LIMIT * 2);
    
    //x
    Start = 0;
    End = 0;
    for (TileX = 0; TileX < num_tile_columns; TileX++)
    {
        TilePosX[TileX][0] = Start;
        End += pHevcCtx->pCurrPPS->column_bd[TileX];
        TilePosX[TileX][1] = End - 1;

        for (idx = (Start << (log2_ctb_sizeY - 4)); idx < (End << (log2_ctb_sizeY - 4)); idx++)
        {
            if (idx < 0 || idx >= HEVC_MAX_CTB_NUM_PER_LINE)
            {
                dprint(PRN_ERROR, "%s 0 idx(%d) out of range(0, 512).\n", __func__, idx);
                return HEVC_DEC_ERR;
            }

            TileId[0][idx] = TileX;
        }

        Start = End;
    }

    //y
    Start = 0;
    End = 0;
    for (TileY = 0; TileY < num_tile_rows; TileY++)
    {
        TilePosY[TileY][0] = Start;
        End += pHevcCtx->pCurrPPS->row_bd[TileY];
        TilePosY[TileY][1] = End - 1;

        for (idx = (Start << (log2_ctb_sizeY - 4)); idx < (End << (log2_ctb_sizeY - 4)); idx++)
        {
            if (idx < 0 || idx >= HEVC_MAX_CTB_NUM_PER_LINE)
            {
                dprint(PRN_ERROR, "%s 1 idx(%d) out of range(0, 512).\n", __func__, idx);
                return HEVC_DEC_ERR;
            }

            TileId[1][idx] = TileY;
        }

        Start = End;
    }

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_ProcessVPS(HEVC_CTX_S *pHevcCtx, HEVC_VIDEO_PARAM_SET_S *pVPS)
{
    char   buf[100];
    SINT32 ret;
    SINT32 i,j;
    SINT32 vps_max_sub_layers_minus1;

	pVPS->vps_reserved_three_2bits = HEVC_u_v(pHevcCtx->pBS, 2, "vps_reserved_three_2bits");
	if (pVPS->vps_reserved_three_2bits != 0x3)
    {
        dprint(PRN_ERROR, "vps_reserved_three_2bits(%d) not equal 0x3.\n", pVPS->vps_reserved_three_2bits);
    }

    pVPS->vps_max_layers_minus1 = HEVC_u_v(pHevcCtx->pBS, 6, "vps_max_layers_minus1");

    if (pVPS->vps_max_layers_minus1 < 0 || pVPS->vps_max_layers_minus1 > 63)
    {
        dprint(PRN_ERROR, "vps_max_layers_minus1 out of range(0,63).\n");
        return HEVC_DEC_ERR;
    }

    vps_max_sub_layers_minus1 = HEVC_u_v(pHevcCtx->pBS, 3, "vps_max_sub_layers_minus1");

    if (vps_max_sub_layers_minus1 < 0 || vps_max_sub_layers_minus1 > HEVC_MAX_TEMPLAYER)
    {
        dprint(PRN_ERROR, "vps_max_sub_layers_minus1=%d\n", vps_max_sub_layers_minus1);
        return HEVC_DEC_ERR;
    }

    pVPS->vps_max_sub_layers_minus1 = vps_max_sub_layers_minus1 + 1;
    pVPS->vps_temporal_id_nesting_flag = HEVC_u_v(pHevcCtx->pBS, 1, "vps_temporal_id_nesting_flag");

	pVPS->vps_reserved_0xffff_16bits = HEVC_u_v(pHevcCtx->pBS, 16, "vps_reserved_ffff_16bits");

	if (pVPS->vps_reserved_0xffff_16bits != 0xffff)
	{
		dprint(PRN_ERROR, "vps_reserved_0xffff_16bits not equal 0xffff.\n");
		return HEVC_DEC_ERR;
	}

	ret = HEVC_DecPTL(pHevcCtx, &(pVPS->profile_tier_level), 1, vps_max_sub_layers_minus1);
	if (HEVC_DEC_NORMAL != ret)
	{
		dprint(PRN_ERROR, "VPS HEVC_DecPTL error.\n");
		return HEVC_DEC_ERR;
	}

    pVPS->vps_sub_layer_ordering_info_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "vps_sub_layer_ordering_info_present_flag");

    for (i = 0; i <= vps_max_sub_layers_minus1; i++)
    {
        pVPS->vps_max_dec_pic_buffering[i] = HEVC_ue_v(pHevcCtx->pBS,  "vps_max_dec_pic_buffering_minus1[i]") + 1;
        pVPS->vps_num_reorder_pics[i] = HEVC_ue_v(pHevcCtx->pBS, "vps_num_reorder_pics[i]");
        pVPS->vps_max_latency_increase[i] = HEVC_ue_v(pHevcCtx->pBS,  "vps_max_latency_increase_plus1[i]");

        if (!pVPS->vps_sub_layer_ordering_info_present_flag)
        {
            for (i++; i <= vps_max_sub_layers_minus1; i++)
            {
                pVPS->vps_max_dec_pic_buffering[i] =  pVPS->vps_max_dec_pic_buffering[0] ;
                pVPS->vps_num_reorder_pics[i] = pVPS->vps_num_reorder_pics[0];
                pVPS->vps_max_latency_increase[i] =	pVPS->vps_max_latency_increase[0];
            }

            break;
        }
    }

    pVPS->vps_max_layer_id = HEVC_u_v(pHevcCtx->pBS, 6, "vps_max_layer_id");

    pVPS->vps_num_layer_sets_minus1 = HEVC_ue_v(pHevcCtx->pBS,  "vps_num_layer_sets_minus1");

    if (pVPS->vps_num_layer_sets_minus1 < 0 || pVPS->vps_num_layer_sets_minus1 > HEVC_MAX_VPS_OP_SETS_PLUS1)
    {
        dprint(PRN_ERROR, "vps_num_layer_sets_minus1(%d) out of range(0,%d).\n", pVPS->vps_num_layer_sets_minus1, HEVC_MAX_VPS_OP_SETS_PLUS1);
        return HEVC_DEC_ERR;
    }

    for (i = 1; i < pVPS->vps_num_layer_sets_minus1; i++)
    {
        //Operation point set
        for (j = 0; j < pVPS->vps_max_layer_id; j++)
        {
            snprintf(buf, sizeof(buf), "layer_id_included_flag[%d][%d]", i, j);
            pVPS->layer_id_included_flag[i][j]= HEVC_u_v(pHevcCtx->pBS, 1, buf);
        }
	}

	pVPS->vps_timing_info_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "vps_timing_info_present_flag");
	if (pVPS->vps_timing_info_present_flag)
	{
        pVPS->vps_num_units_in_tick = HEVC_u_v(pHevcCtx->pBS, 32, "vps_num_units_in_tick");
        pVPS->vps_time_scale = HEVC_u_v(pHevcCtx->pBS, 32, "vps_time_scale");
        pVPS->vps_poc_proportional_to_timing_flag = HEVC_u_v(pHevcCtx->pBS, 1, "vps_poc_proportional_to_timing_flag");
        if (pVPS->vps_poc_proportional_to_timing_flag)
        {
            pVPS->vps_num_ticks_poc_diff_one_minus1 = HEVC_ue_v(pHevcCtx->pBS, "vps_num_ticks_poc_diff_one_minus1");
        }
        pVPS->vps_num_hrd_parameters = HEVC_ue_v(pHevcCtx->pBS, "vps_num_hrd_parameters");

        if (pVPS->vps_num_hrd_parameters < 0  || pVPS->vps_num_hrd_parameters >= HEVC_MAX_VPS_OP_SETS_PLUS1)
        {
            dprint(PRN_ERROR, "vps_num_hrd_parameters(%d) out of range(0,%d).\n", pVPS->vps_num_hrd_parameters, HEVC_MAX_VPS_OP_SETS_PLUS1);
            return HEVC_DEC_ERR;
        }

        if (pVPS->vps_num_hrd_parameters > 0)
        {
            pVPS->cprms_present_flag[0] = HEVC_TRUE; 
        }
        
        for( i = 0; i < pVPS->vps_num_hrd_parameters; i++)
        {
            pVPS->hrd_layer_set_idx[i] = HEVC_ue_v(pHevcCtx->pBS, "hrd_layer_set_idx");
            if( i > 0 )
            {
                pVPS->cprms_present_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "cprms_present_flag");
            }
            ret = HEVC_DecHrdParam(pHevcCtx, &(pVPS->hrd_parameters), pVPS->cprms_present_flag[i], vps_max_sub_layers_minus1);
            if (HEVC_DEC_NORMAL != ret)
            {
                dprint(PRN_ERROR, "VPS HEVC_DecHrdParam error.\n");
                return HEVC_DEC_ERR;
            }
        }
    }

	pVPS->vps_extension_flag = HEVC_u_v(pHevcCtx->pBS, 1, "vps_extension_flag");
	if (pVPS->vps_extension_flag)
	{
        while (HEVC_MoreRbspData(pHevcCtx))
        {
            pVPS->vps_extension_data_flag = HEVC_u_v(pHevcCtx->pBS, 1, "");
            //pVPS->vps_extension_data_flag = HEVC_u_v(pHevcCtx->pBS, 1, "vps_extension_data_flags");
        }
	}

	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_VPSEqual(HEVC_VIDEO_PARAM_SET_S *pVPS1, HEVC_VIDEO_PARAM_SET_S *pVPS2)
{
    UINT32 i, j;
    SINT32 equal = 1;
    SINT32 ret;
	HEVC_PROFILE_TIER_LEVEL_S* pPTL1, *pPTL2;
	
    CHECK_NULL_PTR_ReturnValue(pVPS1, HEVC_DEC_ERR);
    CHECK_NULL_PTR_ReturnValue(pVPS2, HEVC_DEC_ERR);

    equal &= (pVPS1->vps_reserved_three_2bits == pVPS2->vps_reserved_three_2bits);
    equal &= (pVPS1->vps_max_layers_minus1 == pVPS2->vps_max_layers_minus1);
    equal &= (pVPS1->vps_max_sub_layers_minus1 == pVPS2->vps_max_sub_layers_minus1);
    equal &= (pVPS1->vps_temporal_id_nesting_flag == pVPS2->vps_temporal_id_nesting_flag);
    equal &= (pVPS1->vps_reserved_0xffff_16bits == pVPS2->vps_reserved_0xffff_16bits);
    equal &= (pVPS1->video_parameter_set_id == pVPS2->video_parameter_set_id);

	pPTL1 = &pVPS1->profile_tier_level;
	pPTL2 = &pVPS2->profile_tier_level;

	equal &= (pPTL1->general_profile_space == pPTL2->general_profile_space);
	equal &= (pPTL1->general_tier_flag == pPTL2->general_tier_flag);
	equal &= (pPTL1->general_profile_idc == pPTL2->general_profile_idc);
	for (i=0; i<32; i++)
	{
		equal &= (pPTL1->general_profile_compatibility_flag[i]  == pPTL2->general_profile_compatibility_flag[i] );
	}
	equal &= (pPTL1->general_progressive_source_flag == pPTL2->general_progressive_source_flag);
	equal &= (pPTL1->general_interlaced_source_flag == pPTL2->general_interlaced_source_flag);
	equal &= (pPTL1->general_non_packed_constraint_flag == pPTL2->general_non_packed_constraint_flag);
	equal &= (pPTL1->general_frame_only_constraint_flag == pPTL2->general_frame_only_constraint_flag);		

	equal &= (pVPS1->vps_sub_layer_ordering_info_present_flag == pVPS2->vps_sub_layer_ordering_info_present_flag);		

	for (i=0; i<=pVPS1->vps_max_sub_layers_minus1-1; i++)
	{
		equal &= (pVPS1->vps_max_dec_pic_buffering[i] == pVPS2->vps_max_dec_pic_buffering[i]);		
		equal &= (pVPS1->vps_num_reorder_pics[i] == pVPS2->vps_num_reorder_pics[i]);		
		equal &= (pVPS1->vps_max_latency_increase[i] == pVPS2->vps_max_latency_increase[i]);	
	}

	equal &= (pVPS1->vps_max_layer_id == pVPS2->vps_max_layer_id);		
	equal &= (pVPS1->vps_num_layer_sets_minus1 == pVPS2->vps_num_layer_sets_minus1);		
		
	for ( i = 1; i <= pVPS1->vps_num_layer_sets_minus1; i++)
	{
		for ( j = 0; j <= pVPS1->vps_max_layer_id; j++)
		{
			equal &= (pVPS1->layer_id_included_flag[i][j] == pVPS2->layer_id_included_flag[i][j]);		
		}
	}
	equal &= (pVPS1->vps_timing_info_present_flag == pVPS2->vps_timing_info_present_flag);		

	if (pVPS1->vps_timing_info_present_flag)
	{
		equal &= (pVPS1->vps_num_units_in_tick == pVPS2->vps_num_units_in_tick);		
		equal &= (pVPS1->vps_time_scale == pVPS2->vps_time_scale);		
		equal &= (pVPS1->vps_poc_proportional_to_timing_flag == pVPS2->vps_poc_proportional_to_timing_flag);		
		if (pVPS1->vps_poc_proportional_to_timing_flag)
		{
			equal &= (pVPS1->vps_num_ticks_poc_diff_one_minus1 == pVPS2->vps_num_ticks_poc_diff_one_minus1);		
		}
		equal &= (pVPS1->vps_num_hrd_parameters == pVPS2->vps_num_hrd_parameters);		
	}
    ret = equal ? HEVC_DEC_NORMAL: HEVC_DEC_ERR;

    return ret;
}


SINT32 HEVC_DecVPS(HEVC_CTX_S *pHevcCtx)
{
    UINT32  vps_video_parameter_set_id;
	HEVC_VIDEO_PARAM_SET_S *vps_tmp = NULL;

    vps_tmp = &(s_TmpParam.VpsTmp);
#ifndef HEVC_SYNTAX_OPT
    memset(vps_tmp, 0, sizeof(HEVC_VIDEO_PARAM_SET_S));        
#endif
    vps_video_parameter_set_id = HEVC_u_v(pHevcCtx->pBS,4, "vps_video_parameter_set_id");

    
    if (vps_video_parameter_set_id > 15)
	{
		dprint(PRN_ERROR, "pVPS->vps_video_parameter_set_id out of range(0,15).\n");
		return HEVC_DEC_ERR;			
	}

	if (pHevcCtx->pVPS[vps_video_parameter_set_id].valid) // 曾经解对过该id对应的VPS
	{
		vps_tmp->video_parameter_set_id  = vps_video_parameter_set_id;

		if (HEVC_DEC_NORMAL != HEVC_ProcessVPS(pHevcCtx, vps_tmp))
		{
			dprint(PRN_ERROR, "VPS[%d] decode error0.\n", vps_video_parameter_set_id);
			return HEVC_DEC_ERR;
		}

#ifndef HEVC_SYNTAX_OPT

        if (HEVC_DEC_NORMAL != HEVC_VPSEqual(vps_tmp, &(pHevcCtx->pVPS[vps_video_parameter_set_id])))
#endif
        {
            vps_tmp->is_refresh = 1;
			vps_tmp->valid = 1;
			memmove(&(pHevcCtx->pVPS[vps_video_parameter_set_id]), vps_tmp, sizeof(HEVC_VIDEO_PARAM_SET_S));	 
		}
	}
	else
	{
		pHevcCtx->pVPS[vps_video_parameter_set_id].video_parameter_set_id = vps_video_parameter_set_id;   

		if (HEVC_DEC_NORMAL != HEVC_ProcessVPS(pHevcCtx, &(pHevcCtx->pVPS[vps_video_parameter_set_id])))
		{
			dprint(PRN_ERROR, "VPS[%d] decode error1.\n", vps_video_parameter_set_id);
			pHevcCtx->pVPS[vps_video_parameter_set_id].is_refresh = 1;
			pHevcCtx->pVPS[vps_video_parameter_set_id].valid = 0;
			return HEVC_DEC_ERR;
		}
		pHevcCtx->pVPS[vps_video_parameter_set_id].is_refresh = 1;
		pHevcCtx->pVPS[vps_video_parameter_set_id].valid = 1;
	}

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_ProcessSPS(HEVC_CTX_S *pHevcCtx, HEVC_SEQ_PARAM_SET_S *pSPS)
{
	UINT32 i;
	SINT32 ret;
	UINT32 size, pic_size;
    UINT32 log2_max_pic_order_cnt_lsb_minus4;
    SINT32 s32TempData = 0;

	pSPS->chroma_format_idc = HEVC_ue_v(pHevcCtx->pBS, "chroma_format_idc");
    
	// in the first version we only support chroma_format_idc equal to 1 (4:2:0), so separate_colour_plane_flag cannot appear in the bitstream
	if (pSPS->chroma_format_idc != 1)
	{
        
        if (pSPS->chroma_format_idc > 3)
		{
			dprint(PRN_ERROR, "pSPS->chroma_format_idc out of range(0,3).\n");
			return HEVC_DEC_ERR;
		}
		else
		{
			dprint(PRN_ERROR, "pSPS->chroma_format_idc not equal(%d) 1.\n", pSPS->chroma_format_idc);
			return HEVC_DEC_ERR;
		}
	}

	if (3 == pSPS->chroma_format_idc)
	{
		pSPS->separate_colour_plane_flag = HEVC_u_v(pHevcCtx->pBS, 1, "separate_colour_plane_flag");
		if (0 != pSPS->separate_colour_plane_flag)
		{
			dprint(PRN_ERROR, "pSPS->separate_colour_plane_flag not equal 0.\n");	
		}
	}

	pSPS->pic_width_in_luma_samples   = HEVC_ue_v(pHevcCtx->pBS, "pic_width_in_luma_samples");
	if (pSPS->pic_width_in_luma_samples > 8192)
	{
		dprint(PRN_ERROR, "pic_width_in_luma_samples out of range(0,8192).\n"); 
		return HEVC_DEC_ERR;
	}

	pSPS->pic_height_in_luma_samples  = HEVC_ue_v(pHevcCtx->pBS, "pic_height_in_luma_samples");
	if (pSPS->pic_height_in_luma_samples > 4096)
	{
		dprint(PRN_ERROR, "pic_height_in_luma_samples out of range(0,4096).\n");
		return HEVC_DEC_ERR;
	}

	pic_size = pSPS->pic_width_in_luma_samples * pSPS->pic_height_in_luma_samples;

	switch (pSPS->profile_tier_level.general_level_idc)
	{
		case 0:
		case 30:
			size = 36864;
			break;
		case 60:
			size = 122880;
			break;
		case 63:
			size = 245760;
			break;
		case 90:
			size = 552960;
			break;
		case 93:
			size = 983040;
			break;
		case 120:
		case 123:
			size = 2228224;
			break;
		case 150:
		case 153:
		case 156:
			size = 8912896;
			break;
		case 180:
		case 183:
		case 186:
			size = 35651584;
			break;
		default:
            dprint(PRN_ERROR, "ERROR Unkown level: %d\n", pSPS->profile_tier_level.general_level_idc);
			return HEVC_LEVEL_ERR;
	}
	
	if (pic_size <= (size>>2))
	{
		pSPS->dpb_size = MIN(4*HEVC_MAX_DPB_PIC_BUF, 16);
	}
	else if (pic_size <= (size>>1))
	{
		pSPS->dpb_size = MIN(2*HEVC_MAX_DPB_PIC_BUF, 16);
	}
	else if (pic_size <= ((3*size)>>2))
	{
		pSPS->dpb_size = MIN((4*HEVC_MAX_DPB_PIC_BUF)/3, 16);
	}
	else
	{
		pSPS->dpb_size = HEVC_MAX_DPB_PIC_BUF;
	}

	pSPS->conformance_window_flag = HEVC_u_v(pHevcCtx->pBS, 1, "conformance_window_flag");

	if (pSPS->conformance_window_flag)
	{
		pSPS->conf_win_left_offset	 = HEVC_ue_v(pHevcCtx->pBS, "conf_win_left_offset");
		pSPS->conf_win_left_offset	 = pSPS->conf_win_left_offset  * g_CropUnitX[pSPS->chroma_format_idc];
		pSPS->conf_win_right_offset  = HEVC_ue_v(pHevcCtx->pBS, "conf_win_right_offset");
		pSPS->conf_win_right_offset  = pSPS->conf_win_right_offset * g_CropUnitX[pSPS->chroma_format_idc];

        
        s32TempData = (SINT32)(pSPS->pic_width_in_luma_samples - pSPS->conf_win_left_offset - pSPS->conf_win_right_offset);

        if (s32TempData < 0)
        {
            dprint(PRN_ERROR, "conf_win_left_offset+conf_win_right_offset out of range.\n");
            return HEVC_DEC_ERR;
        }
		
		pSPS->conf_win_top_offset	 = HEVC_ue_v(pHevcCtx->pBS, "conf_win_top_offset");
		pSPS->conf_win_top_offset	 = pSPS->conf_win_top_offset   * g_CropUnitY[pSPS->chroma_format_idc];
		pSPS->conf_win_bottom_offset = HEVC_ue_v(pHevcCtx->pBS, "conf_win_bottom_offset");
		pSPS->conf_win_bottom_offset = pSPS->conf_win_bottom_offset* g_CropUnitY[pSPS->chroma_format_idc];
        
        s32TempData = (SINT32)(pSPS->pic_height_in_luma_samples - pSPS->conf_win_top_offset - pSPS->conf_win_bottom_offset);

        if (s32TempData < 0)
        {
            dprint(PRN_ERROR, "conf_win_top_offset+conf_win_bottom_offset out of range.\n");
            return HEVC_DEC_ERR;
        }
	}
	pSPS->bit_depth_luma  = HEVC_ue_v(pHevcCtx->pBS, "bit_depth_luma_minus8") + 8;
	if (pSPS->bit_depth_luma != 8)
	{
		if (pSPS->bit_depth_luma < 8 || pSPS->bit_depth_luma > 14 )
		{
			dprint(PRN_ERROR, "bit_depth_luma(%d) out of range(8,14).\n", pSPS->bit_depth_luma);
			return HEVC_DEC_ERR;			
		}
		else
		{
            // 3798MV100 只支持8bit
            dprint(PRN_ERROR, "bit_depth_luma(%d) not equal 8.\n", pSPS->bit_depth_luma);
            REPORT_UNSUPPORT_SPEC(pHevcCtx->ChanID, SPEC_BIT_DEPTH, pSPS->bit_depth_luma);
            //return HEVC_DEC_ERR;
		}
	}

	pSPS->bit_depth_chroma = HEVC_ue_v(pHevcCtx->pBS, "bit_depth_chroma_minus8") + 8;
	if (pSPS->bit_depth_chroma != 8)
	{
		if (pSPS->bit_depth_chroma < 8 || pSPS->bit_depth_chroma > 14 )
		{
			dprint(PRN_ERROR, "bit_depth_chroma(%d) out of range[8,14].\n", pSPS->bit_depth_chroma);
			return HEVC_DEC_ERR;			
		}
		else
		{
            // 3798MV100 只支持8bit
            dprint(PRN_ERROR, "bit_depth_chroma(%d) not equal 8.\n", pSPS->bit_depth_chroma);
            REPORT_UNSUPPORT_SPEC(pHevcCtx->ChanID, SPEC_BIT_DEPTH, pSPS->bit_depth_chroma);
            //return HEVC_DEC_ERR;
		}
	}
    
	pHevcCtx->BitDepthY = pSPS->bit_depth_luma;
	pHevcCtx->BitDepthC = pSPS->bit_depth_chroma;

	pSPS->qp_bdOffset_y = (pSPS->bit_depth_luma - 8)   * 6;
	pSPS->qp_bdOffset_c = (pSPS->bit_depth_chroma - 8) * 6;

	log2_max_pic_order_cnt_lsb_minus4 = HEVC_ue_v(pHevcCtx->pBS, "log2_max_pic_order_cnt_lsb_minus4");

    
    if (log2_max_pic_order_cnt_lsb_minus4 > 12 )
    {
        dprint(PRN_ERROR, "log2_max_pic_order_cnt_lsb_minus4 out of range[0,12].\n");
        return HEVC_DEC_ERR;
    }

	pSPS->max_pic_order_cnt_lsb = log2_max_pic_order_cnt_lsb_minus4 + 4;
	pSPS->bits_for_poc = pSPS->max_pic_order_cnt_lsb;

	pSPS->sps_sub_layer_ordering_info_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sps_sub_layer_ordering_info_present_flag");

	for (i=0; i <= pSPS->sps_max_sub_layers_minus1; i++)
	{
		pSPS->max_dec_pic_buffering[i] = HEVC_ue_v(pHevcCtx->pBS, "sps_max_dec_pic_buffering_minus1")+1;
		pSPS->num_reorder_pics[i]	   = HEVC_ue_v(pHevcCtx->pBS, "sps_num_reorder_pics");
		pSPS->dpb_size = MIN(pSPS->dpb_size, pSPS->max_dec_pic_buffering[i]);  // 不用加上num_reorder_pics
		pSPS->max_latency_increase[i]  = HEVC_ue_v(pHevcCtx->pBS, "sps_max_latency_increase_plus1");
		if (!pSPS->sps_sub_layer_ordering_info_present_flag)
		{
            for (i++; i <= pSPS->sps_max_sub_layers_minus1; i++)
            {
                pSPS->max_dec_pic_buffering[i] = pSPS->max_dec_pic_buffering[0];
                pSPS->num_reorder_pics[i]	   = pSPS->num_reorder_pics[0];
                pSPS->max_latency_increase[i]  = pSPS->max_latency_increase[0];
            }
            break;
		}
	}

	pSPS->log2_min_luma_coding_block_size_minus3   = HEVC_ue_v(pHevcCtx->pBS, "log2_min_coding_block_size_minus3");
    
    if (pSPS->log2_min_luma_coding_block_size_minus3 > 3)
    {
        dprint(PRN_ERROR, "log2_min_luma_coding_block_size_minus3 out of range(0,3).\n");
        return HEVC_DEC_ERR;
    }

	pSPS->log2_diff_max_min_luma_coding_block_size = HEVC_ue_v(pHevcCtx->pBS, "log2_diff_max_min_coding_block_size");

    
    if (pSPS->log2_diff_max_min_luma_coding_block_size > 3)
    {
        dprint(PRN_ERROR, "log2_diff_max_min_luma_coding_block_size out of range(0,3).\n");
        return HEVC_DEC_ERR;
    }

	pSPS->log2_min_cb_sizeY = pSPS->log2_min_luma_coding_block_size_minus3 + 3;
	pSPS->log2_ctb_sizeY	= pSPS->log2_min_cb_sizeY + pSPS->log2_diff_max_min_luma_coding_block_size;
	if (pSPS->log2_ctb_sizeY < 4 || pSPS->log2_ctb_sizeY > 6)
	{
		dprint(PRN_ERROR, "log2_ctb_sizeY out of range(4,6).\n");
		return HEVC_DEC_ERR;		
	}
	
	pSPS->min_cb_sizeY		= 1 << pSPS->log2_min_cb_sizeY;
	pSPS->ctb_sizeY 		= 1 << pSPS->log2_ctb_sizeY;
	pSPS->max_cu_width		= 1 << pSPS->log2_ctb_sizeY;
	pSPS->max_cu_height 	= 1 << pSPS->log2_ctb_sizeY;
	pSPS->ctb_num_width 	= (pSPS->pic_width_in_luma_samples % pSPS->max_cu_width)
							  ? (pSPS->pic_width_in_luma_samples / pSPS->max_cu_width + 1)
							  : (pSPS->pic_width_in_luma_samples / pSPS->max_cu_width);
	pSPS->ctb_num_height	= (pSPS->pic_height_in_luma_samples % pSPS->max_cu_height)
							  ? (pSPS->pic_height_in_luma_samples / pSPS->max_cu_height + 1)
							  : (pSPS->pic_height_in_luma_samples / pSPS->max_cu_height);

	pSPS->log2_min_transform_block_size_minus2 = HEVC_ue_v(pHevcCtx->pBS, "log2_min_transform_block_size_minus2");

    
    if (pSPS->log2_min_transform_block_size_minus2 > 3)
    {
        dprint(PRN_ERROR, "log2_min_transform_block_size_minus2 out of range(0,3).\n");
        return HEVC_DEC_ERR;
    }

	pSPS->log2_diff_max_min_transform_block_size = HEVC_ue_v(pHevcCtx->pBS, "log2_diff_max_min_transform_block_size");
    
    if (pSPS->log2_diff_max_min_transform_block_size > 3)
    {
        dprint(PRN_ERROR, "log2_diff_max_min_transform_block_size out of range(0,3).\n");
        return HEVC_DEC_ERR;
    }
	pSPS->quadtree_tu_log2_min_size = pSPS->log2_min_transform_block_size_minus2 + 2;
	if (pSPS->quadtree_tu_log2_min_size >= pSPS->log2_min_cb_sizeY)
	{
		dprint(PRN_ERROR, "quadtree_tu_log2_min_size not less than log2_min_cb_sizeY.\n");
		return HEVC_DEC_ERR;		
	}
	
	pSPS->quadtree_tu_log2_max_size = pSPS->quadtree_tu_log2_min_size + pSPS->log2_diff_max_min_transform_block_size;
	if (pSPS->quadtree_tu_log2_max_size > 5 || pSPS->quadtree_tu_log2_max_size > pSPS->log2_ctb_sizeY)
	{
		dprint(PRN_ERROR, "quadtree_tu_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n");
		return HEVC_DEC_ERR;		
	}

	pSPS->max_transform_hierarchy_depth_inter = HEVC_ue_v(pHevcCtx->pBS, "max_transform_hierarchy_depth_inter");

    
    if (pSPS->max_transform_hierarchy_depth_inter > pSPS->log2_ctb_sizeY - pSPS->quadtree_tu_log2_min_size)
    {
        dprint(PRN_ERROR, "max_transform_hierarchy_depth_inter out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n");
        return HEVC_DEC_ERR;
    }

	pSPS->max_transform_hierarchy_depth_intra = HEVC_ue_v(pHevcCtx->pBS, "max_transform_hierarchy_depth_intra");
    
    if (pSPS->max_transform_hierarchy_depth_intra > pSPS->log2_ctb_sizeY - pSPS->quadtree_tu_log2_min_size )
    {
        dprint(PRN_ERROR, "max_transform_hierarchy_depth_intra out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n");
        return HEVC_DEC_ERR;
    }

	pSPS->quadtree_tu_max_depth_inter = pSPS->max_transform_hierarchy_depth_inter + 1;
	pSPS->quadtree_tu_max_depth_intra = pSPS->max_transform_hierarchy_depth_intra + 1;

	pHevcCtx->uiAddCuDepth = 0;
	while (((UINT32)(pSPS->max_cu_width >> pSPS->log2_diff_max_min_luma_coding_block_size))
		 > (UINT32)(1 << (pSPS->quadtree_tu_log2_min_size + pHevcCtx->uiAddCuDepth)))
	{
		pHevcCtx->uiAddCuDepth++;
	}
	pSPS->max_cu_depth = pSPS->log2_diff_max_min_luma_coding_block_size + pHevcCtx->uiAddCuDepth;

	// BB: these parameters may be removed completly and replaced by the fixed values
	pSPS->min_tr_depth = 0;
	pSPS->max_tr_depth = 1;

	pSPS->scaling_list_enabled_flag = HEVC_u_v(pHevcCtx->pBS, 1, "scaling_list_enabled_flag");
	if (pSPS->scaling_list_enabled_flag)
	{
		pSPS->sps_scaling_list_data_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sps_scaling_list_data_present_flag");
		if (pSPS->sps_scaling_list_data_present_flag)
		{
			ret = HEVC_DecScalingListData(pHevcCtx,&(pSPS->scaling_list));
			if (HEVC_DEC_NORMAL != ret)
			{
				dprint(PRN_ERROR, "SPS HEVC_DecScalingListData error.\n");
				return HEVC_DEC_ERR;
			}
		}
	}

	pSPS->amp_enabled_flag = HEVC_u_v(pHevcCtx->pBS, 1, "amp_enabled_flag");
	pSPS->sample_adaptive_offset_enabled_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sample_adaptive_offset_enabled_flag");
    //3798MV100逻辑不支持图像高度64以下没有sao的码流
    if (0 == pSPS->sample_adaptive_offset_enabled_flag && pSPS->pic_height_in_luma_samples <= 64)
    {
        dprint(PRN_ERROR, "SPS sao is off and pic height(%d) is too small.(Logic Unsupported).\n", pSPS->pic_height_in_luma_samples);
        REPORT_UNSUPPORT(pHevcCtx->ChanID);
        return HEVC_DEC_ERR;
    }
        
	pSPS->pcm_enabled_flag = HEVC_u_v(pHevcCtx->pBS, 1, "pcm_enabled_flag");
	if (pSPS->pcm_enabled_flag)
	{
		pSPS->pcm_bit_depth_luma = HEVC_u_v(pHevcCtx->pBS, 4, "pcm_sample_bit_depth_luma_minus1") + 1;
		pSPS->pcm_bit_depth_chroma = HEVC_u_v(pHevcCtx->pBS, 4, "pcm_sample_bit_depth_chroma_minus1") + 1;

        pSPS->log2_min_pcm_coding_block_size_minus3 = HEVC_ue_v(pHevcCtx->pBS, "log2_min_pcm_luma_coding_block_size_minus3");

        
        if (pSPS->log2_min_pcm_coding_block_size_minus3 > 2)
        {
            dprint(PRN_ERROR, "log2_min_pcm_coding_block_size_minus3(%d) out of range[0,2].\n", pSPS->log2_min_pcm_coding_block_size_minus3);
            //return HEVC_DEC_ERR;
        }

		pSPS->log2_diff_max_min_pcm_coding_block_size = HEVC_ue_v(pHevcCtx->pBS, "log2_diff_max_min_pcm_luma_coding_block_size");
        
        if (pSPS->log2_diff_max_min_pcm_coding_block_size > 2)
        {
            dprint(PRN_ERROR, "log2_diff_max_min_pcm_coding_block_size(%d) out of range[0,2].\n", pSPS->log2_diff_max_min_pcm_coding_block_size);
            //return HEVC_DEC_ERR;
        }
		pSPS->pcm_log2_min_size = pSPS->log2_min_pcm_coding_block_size_minus3 + 3;
		pSPS->pcm_log2_max_size = pSPS->pcm_log2_min_size + pSPS->log2_diff_max_min_pcm_coding_block_size;
		if (pSPS->pcm_log2_max_size > 5 || pSPS->pcm_log2_max_size > pSPS->log2_ctb_sizeY)
		{
			dprint(PRN_ERROR, "pcm_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n");
			return HEVC_DEC_ERR;		
		}
		
		pSPS->pcm_loop_filter_disable_flag = HEVC_u_v(pHevcCtx->pBS, 1, "pcm_loop_filter_disable_flag");
	}

	pSPS->num_short_term_ref_pic_sets  = HEVC_ue_v(pHevcCtx->pBS, "num_short_term_ref_pic_sets");
    
    if (pSPS->num_short_term_ref_pic_sets > HEVC_MAX_STRPS_NUM)
    {
        dprint(PRN_ERROR, "num_short_term_ref_pic_sets out of range[0,%d].\n", HEVC_MAX_STRPS_NUM);
        return HEVC_DEC_ERR;
    }

	for (i=0; i<pSPS->num_short_term_ref_pic_sets; i++)
	{
		//get short term reference picture sets
		ret = HEVC_DecShortTermRefPicSet(pHevcCtx, pSPS, &(pSPS->short_term_ref_pic_set[i]), i);
		if (ret != HEVC_DEC_NORMAL)
		{
			dprint(PRN_ERROR, "SPS HEVC_DecShortTermRefPicSet error.\n");
			return HEVC_DEC_ERR;				
		}
	}

	pSPS->long_term_ref_pics_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "long_term_ref_pics_present_flag");
	if (pSPS->long_term_ref_pics_present_flag)
	{
        pSPS->num_long_term_ref_pic_sps = HEVC_ue_v(pHevcCtx->pBS, "num_long_term_ref_pic_sps");

        
        if (pSPS->num_long_term_ref_pic_sps > HEVC_MAX_LSB_NUM - 1)
        {
            dprint(PRN_ERROR, "num_long_term_ref_pic_sps out of range[0,32].\n");
            return HEVC_DEC_ERR;
        }

		for (i=0; i<pSPS->num_long_term_ref_pic_sps; i++)
		{
			pSPS->lt_ref_pic_poc_lsb_sps[i] 	  = HEVC_u_v(pHevcCtx->pBS, pSPS->max_pic_order_cnt_lsb, "lt_ref_pic_poc_lsb_sps");
			pSPS->used_by_curr_pic_lt_sps_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "used_by_curr_pic_lt_sps_flag");
		}
	}
	pSPS->sps_temporal_mvp_enable_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sps_temporal_mvp_enable_flag");
	pSPS->sps_strong_intra_smoothing_enable_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sps_strong_intra_smoothing_enable_flag");
	pSPS->vui_parameters_present_flag			 = HEVC_u_v(pHevcCtx->pBS, 1, "vui_parameters_present_flag");
	if (pSPS->vui_parameters_present_flag)
	{
		ret = HEVC_DecVuiParam(pHevcCtx,&(pSPS->vui_parameters), pSPS);
		if (HEVC_DEC_NORMAL != ret)
		{
			dprint(PRN_ERROR, "SPS HEVC_DecVuiParam error.\n");
			return HEVC_DEC_ERR;				
		}
	}

    pSPS->vui_parameters.aspect_ratio = HEVCGetDar(pSPS->vui_parameters.aspect_ratio_idc, pSPS->vui_parameters.sar_width, pSPS->vui_parameters.sar_height, pSPS->pic_width_in_luma_samples, pSPS->pic_height_in_luma_samples);
	pSPS->sps_extension_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sps_extension_flag");

	if (pSPS->sps_extension_flag)
	{
		// more_rbsp_data_flag = HEVC_MoreRbspData();
		while (HEVC_MoreRbspData(pHevcCtx))
		{
			pSPS->sps_extension_data_flag = HEVC_u_v(pHevcCtx->pBS, 1, "");
			//pSPS->sps_extension_data_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sps_extension_data_flag");
		}
	}	
	pSPS->is_refresh = 1;

    if (pSPS->dpb_size != pHevcCtx->pSPS[pHevcCtx->PrevSpsId].dpb_size)
    {
        pSPS->dpbsize_changed = 1;
		//dprint(PRN_ALWS, "dpbsize_changed %d -> %d.\n", pHevcCtx->pSPS[pHevcCtx->PrevSpsId].dpb_size, pSPS->dpb_size);
    }
    else
    {
        pSPS->dpbsize_changed = 0;
    }

	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_DecSPS(HEVC_CTX_S *pHevcCtx)
{
	SINT32 ret;
	UINT32 video_parameter_set_id;
	UINT32 sps_max_sub_layers_minus1;
	UINT8 sps_temporal_id_nesting_flag;
	UINT32 sps_seq_parameter_set_id;
	HEVC_PROFILE_TIER_LEVEL_S profile_tier_level;
	HEVC_SEQ_PARAM_SET_S *sps_tmp = NULL;

    sps_tmp = &(s_TmpParam.SpsTmp);
    memset(sps_tmp, 0, sizeof(HEVC_SEQ_PARAM_SET_S));
    memset(&profile_tier_level,0,sizeof(HEVC_PROFILE_TIER_LEVEL_S));

	video_parameter_set_id    = HEVC_u_v(pHevcCtx->pBS, 4, "sps_video_parameter_set_id");
    
    if (video_parameter_set_id >= (pHevcCtx->MaxVpsNum))
    {
        dprint(PRN_ERROR, "sps_video_parameter_set_id out of range(0,%d).\n", pHevcCtx->MaxVpsNum);
        return HEVC_DEC_ERR;
    }

    sps_max_sub_layers_minus1 = HEVC_u_v(pHevcCtx->pBS, 3, "sps_max_sub_layers_minus1");

    
    if (sps_max_sub_layers_minus1 > HEVC_MAX_TEMPLAYER)
    {
        dprint(PRN_ERROR, "sps_max_sub_layers_minus1 out of range(0,%d).\n", HEVC_MAX_TEMPLAYER);
        return HEVC_DEC_ERR;
	}
	sps_temporal_id_nesting_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sps_temporal_id_nesting_flag");

	ret = HEVC_DecPTL(pHevcCtx, &(profile_tier_level), 1, sps_max_sub_layers_minus1);
	if (HEVC_DEC_NORMAL != ret)
	{
		dprint(PRN_ERROR, "SPS HEVC_DecPTL error.\n");
		return HEVC_DEC_ERR;
	}

	sps_seq_parameter_set_id = HEVC_ue_v(pHevcCtx->pBS,"sps_seq_parameter_set_id");

    
    if (sps_seq_parameter_set_id >= pHevcCtx->MaxSpsNum)
    {
        dprint(PRN_ERROR, "sps_seq_parameter_set_id out of range(0,%d).\n", pHevcCtx->MaxSpsNum);

        if (sps_seq_parameter_set_id >= pHevcCtx->MaxSpsNum)
        {
            REPORT_SPS_NUM_OVER( pHevcCtx->ChanID, sps_seq_parameter_set_id, pHevcCtx->MaxSpsNum);
        }

        return HEVC_DEC_ERR;
	}

	if (pHevcCtx->pSPS[sps_seq_parameter_set_id].valid) // 曾经解对过该id对应的SPS
	{
		sps_tmp->video_parameter_set_id  = video_parameter_set_id;
		sps_tmp->sps_max_sub_layers_minus1  = sps_max_sub_layers_minus1;
		sps_tmp->sps_temporal_id_nesting_flag  = sps_temporal_id_nesting_flag;
        memcpy(&(sps_tmp->profile_tier_level), &(profile_tier_level), sizeof(HEVC_PROFILE_TIER_LEVEL_S));
		sps_tmp->seq_parameter_set_id  = sps_seq_parameter_set_id;
		
		if (HEVC_DEC_NORMAL != HEVC_ProcessSPS(pHevcCtx, sps_tmp))
		{
			//此时pHevcCtx->SPS[sps_seq_parameter_set_id]为前一个可用
            memcpy(&pHevcCtx->SEISPS, &pHevcCtx->pSPS[sps_seq_parameter_set_id], sizeof(HEVC_SEQ_PARAM_SET_S));
			dprint(PRN_ERROR, "SPS[%d] decode error0.\n", sps_seq_parameter_set_id);
			return HEVC_DEC_ERR;
		}

		//不进行equal判断,只要能够正确解码,就进行拷贝,因为equal判断也比较复杂
		//if (HEVC_DEC_NORMAL != HEVC_SPSEqual(&sps_tmp, &(pHevcCtx->SPS[sps_seq_parameter_set_id])))
		{
			sps_tmp->is_refresh = 1;
			sps_tmp->valid = 1;
            memmove(&(pHevcCtx->pSPS[sps_seq_parameter_set_id]), sps_tmp, sizeof(HEVC_SEQ_PARAM_SET_S));
            memcpy(&pHevcCtx->SEISPS, &pHevcCtx->pSPS[sps_seq_parameter_set_id], sizeof(HEVC_SEQ_PARAM_SET_S));
		}
	}
	else
	{
		pHevcCtx->pSPS[sps_seq_parameter_set_id].video_parameter_set_id  = video_parameter_set_id;
		pHevcCtx->pSPS[sps_seq_parameter_set_id].sps_max_sub_layers_minus1  = sps_max_sub_layers_minus1;
		pHevcCtx->pSPS[sps_seq_parameter_set_id].sps_temporal_id_nesting_flag  = sps_temporal_id_nesting_flag;
        memcpy(&(pHevcCtx->pSPS[sps_seq_parameter_set_id].profile_tier_level), &(profile_tier_level), sizeof(HEVC_PROFILE_TIER_LEVEL_S));
		pHevcCtx->pSPS[sps_seq_parameter_set_id].seq_parameter_set_id  = sps_seq_parameter_set_id;

		if (HEVC_DEC_NORMAL != HEVC_ProcessSPS(pHevcCtx, &(pHevcCtx->pSPS[sps_seq_parameter_set_id])))
		{
			dprint(PRN_ERROR, "SPS[%d] decode error.\n", sps_seq_parameter_set_id);
			pHevcCtx->pSPS[sps_seq_parameter_set_id].is_refresh = 1;
			pHevcCtx->pSPS[sps_seq_parameter_set_id].valid = 0;
			return HEVC_DEC_ERR;
		}
		pHevcCtx->pSPS[sps_seq_parameter_set_id].is_refresh = 1;
		pHevcCtx->pSPS[sps_seq_parameter_set_id].valid = 1;
        memcpy(&pHevcCtx->SEISPS, &pHevcCtx->pSPS[sps_seq_parameter_set_id], sizeof(HEVC_SEQ_PARAM_SET_S));
	}

	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_ProcessPPS(HEVC_CTX_S *pHevcCtx, HEVC_PIC_PARAM_SET_S *pPPS)
{
    HEVC_SEQ_PARAM_SET_S *pSPS;
    SINT32 ret;
    SINT32 i;

    pPPS->loop_filter_across_tiles_enabled_flag = 1;
    pPPS->num_tile_columns = 1;
    pPPS->num_tile_rows = 1;
    pPPS->seq_parameter_set_id = HEVC_ue_v(pHevcCtx->pBS, "pps_seq_parameter_set_id");

    if (pPPS->seq_parameter_set_id < 0 || pPPS->seq_parameter_set_id >= (pHevcCtx->MaxSpsNum))
    {
    	dprint(PRN_ERROR, "pic_parameter_set_id(%d) out of range[0,15].\n", pPPS->seq_parameter_set_id);
    	return HEVC_DEC_ERR;			
    }
    else if (pHevcCtx->pSPS[pPPS->seq_parameter_set_id].valid == 0)
    {
        dprint(PRN_ERROR, "SPS(%d) haven't decode.\n", pPPS->seq_parameter_set_id);    
        return HEVC_DEC_ERR;
    }

    pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];

    pPPS->dependent_slice_segments_enabled_flag  = HEVC_u_v(pHevcCtx->pBS, 1, "dependent_slice_segments_enabled_flag");
    pPPS->output_flag_present_flag               = HEVC_u_v(pHevcCtx->pBS, 1, "output_flag_present_flag");
    pPPS->num_extra_slice_header_bits            = HEVC_u_v(pHevcCtx->pBS, 3, "num_extra_slice_header_bits");   	
    pPPS->sign_data_hiding_flag                  = HEVC_u_v(pHevcCtx->pBS, 1, "sign_data_hiding_flag");
    pPPS->cabac_init_present_flag                = HEVC_u_v(pHevcCtx->pBS, 1, "cabac_init_present_flag");
    
    pPPS->num_ref_idx_l0_default_active = 1 + HEVC_ue_v(pHevcCtx->pBS, "num_ref_idx_l0_default_active_minus1");
    if (pPPS->num_ref_idx_l0_default_active < 0 || pPPS->num_ref_idx_l0_default_active > 15)
    {
    	dprint(PRN_ERROR, "num_ref_idx_l0_default_active out of range[0,15].\n");
    	return HEVC_DEC_ERR;			
    }

    pPPS->num_ref_idx_l1_default_active = 1 + HEVC_ue_v(pHevcCtx->pBS, "num_ref_idx_l1_default_active_minus1");
    if (pPPS->num_ref_idx_l1_default_active < 0 || pPPS->num_ref_idx_l1_default_active > 15)
    {
    	dprint(PRN_ERROR, "num_ref_idx_l1_default_active out of range[0,15].\n");
    	return HEVC_DEC_ERR;			
    }

    pPPS->pic_init_qp                   = 26 + HEVC_se_v(pHevcCtx->pBS, "init_qp_minus26");
    if (pPPS->pic_init_qp < (SINT32)(-(pSPS->qp_bdOffset_y)) || pPPS->pic_init_qp > 51)
    {
    	dprint(PRN_ERROR, "pic_init_qp(%d) out of range[-%d,51].\n", pPPS->pic_init_qp, (pSPS->qp_bdOffset_y));
    	return HEVC_DEC_ERR;			
    }

    pPPS->constrained_intra_pred_flag   = HEVC_u_v(pHevcCtx->pBS, 1, "constrained_intra_pred_flag");
    pPPS->transform_skip_enabled_flag   = HEVC_u_v(pHevcCtx->pBS, 1, "transform_skip_enabled_flag");
    pPPS->cu_qp_delta_enabled_flag      = HEVC_u_v(pHevcCtx->pBS, 1, "cu_qp_delta_enabled_flag");
    
    if (pPPS->cu_qp_delta_enabled_flag)
    {
        pPPS->diff_cu_qp_delta_depth    = HEVC_ue_v(pHevcCtx->pBS, "diff_cu_qp_delta_depth");
    }
    else
    {
        pPPS->diff_cu_qp_delta_depth    = 0;
    }

    if (pPPS->diff_cu_qp_delta_depth < 0 || pPPS->diff_cu_qp_delta_depth > 3)
    {
    	dprint(PRN_ERROR, "diff_cu_qp_delta_depth out of range[0,3].\n");
    	return HEVC_DEC_ERR;	
    }	
    pPPS->max_cu_qp_delta_depth         = pPPS->diff_cu_qp_delta_depth;

    pPPS->pic_cb_qp_offset              = HEVC_se_v(pHevcCtx->pBS, "pps_cb_qp_offset");
    if (pPPS->pic_cb_qp_offset < -12 || pPPS->pic_cb_qp_offset > 12)
    {
    	dprint(PRN_ERROR, "pic_cb_qp_offset out of range[-12,12].\n");
    	return HEVC_DEC_ERR;	
    }

    pPPS->pic_cr_qp_offset              = HEVC_se_v(pHevcCtx->pBS, "pps_cr_qp_offset");
    if (pPPS->pic_cr_qp_offset < -12 || pPPS->pic_cr_qp_offset > 12)
    {
    	dprint(PRN_ERROR, "pic_cr_qp_offset out of range[-12,12].\n");
    	return HEVC_DEC_ERR;	
    }	

    pPPS->pic_slice_chroma_qp_offsets_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "pps_slice_chroma_qp_offsets_present_flag");
    pPPS->weighted_pred_flag                       = HEVC_u_v(pHevcCtx->pBS, 1, "weighted_pred_flag");
    pPPS->weighted_bipred_flag                     = HEVC_u_v(pHevcCtx->pBS, 1, "weighted_bipred_flag");
    pPPS->transquant_bypass_enable_flag            = HEVC_u_v(pHevcCtx->pBS, 1, "transquant_bypass_enable_flag");
    pPPS->tiles_enabled_flag                       = HEVC_u_v(pHevcCtx->pBS, 1, "tiles_enabled_flag");
    pPPS->entropy_coding_sync_enabled_flag         = HEVC_u_v(pHevcCtx->pBS, 1, "entropy_coding_sync_enabled_flag");

    if (pPPS->tiles_enabled_flag)
    {
        pPPS->num_tile_columns          = HEVC_ue_v(pHevcCtx->pBS, "num_tile_columns_minus1") + 1;
        if (pPPS->num_tile_columns <= 0 || pPPS->num_tile_columns > HEVC_MAX_TILE_COLUMNS)
        {
        	dprint(PRN_ERROR, "num_tile_columns(%d) out of range(0,%d).\n", pPPS->num_tile_columns, HEVC_MAX_TILE_COLUMNS);
        	return HEVC_DEC_ERR;			
        }

        pPPS->num_tile_rows             = HEVC_ue_v(pHevcCtx->pBS, "num_tile_rows_minus1") + 1;
        if (pPPS->num_tile_rows <= 0 || pPPS->num_tile_rows > HEVC_MAX_TILE_ROWS)
        {
        	dprint(PRN_ERROR, "num_tile_rows out(%d) of range(0,%d).\n", pPPS->num_tile_rows, HEVC_MAX_TILE_ROWS);
        	return HEVC_DEC_ERR;			
        }

        // 3798MV100逻辑限制column x row 为 20 x 22
        if (pPPS->num_tile_columns > HEVC_LOGIC_TILE_COLUMNS_LIMIT)
        {
            dprint(PRN_ERROR, "Logic limit(%d), num_tile_columns(%d) exceed.\n", HEVC_LOGIC_TILE_COLUMNS_LIMIT, pPPS->num_tile_columns);
            REPORT_UNSUPPORT(pHevcCtx->ChanID);
            return HEVC_DEC_ERR;
        }
        if (pPPS->num_tile_rows > HEVC_LOGIC_TILE_ROWS_LIMIT)
        {
            dprint(PRN_ERROR, "Logic limit(%d), num_tile_rows(%d) exceed.\n", HEVC_LOGIC_TILE_ROWS_LIMIT, pPPS->num_tile_rows);
            REPORT_UNSUPPORT(pHevcCtx->ChanID);
            return HEVC_DEC_ERR;
        }
            
        pPPS->uniform_spacing_flag      = HEVC_u_v(pHevcCtx->pBS, 1, "uniform_spacing_flag");

        if (!pPPS->uniform_spacing_flag)
        {
            for (i=0; i<(pPPS->num_tile_columns-1); i++)
            {
                pPPS->column_width[i] = HEVC_ue_v(pHevcCtx->pBS, "column_width_minus1") + 1;
                // 宽度约束
                if (pPPS->column_width[i] < 0 || pPPS->column_width[i] > pSPS->ctb_num_width )
                {
                	dprint(PRN_ERROR,"column_width[%d](%d) out of range (0 %d)\n", i,pPPS->column_width[i],pSPS->ctb_num_width);	
                	return HEVC_DEC_ERR;			
                }
            }
            for (i=0; i<(pPPS->num_tile_rows-1); i++)
            {
                pPPS->row_height[i] = HEVC_ue_v(pHevcCtx->pBS, "row_height_minus1") + 1;
                // 高度约束	
                if (pPPS->row_height[i] < 0 || pPPS->row_height[i] > pSPS->ctb_num_height )
                {
                    dprint(PRN_ERROR,"row_height[%d](%d) out of range (0 %d)\n", i,pPPS->row_height[i],pSPS->ctb_num_height);
                    return HEVC_DEC_ERR;			
                }
            }
        }

        if (pPPS->uniform_spacing_flag)
        {
            for (i=0; i<pPPS->num_tile_columns; i++)
            {
                pPPS->column_bd[i] = (i+1)*pSPS->ctb_num_width/pPPS->num_tile_columns - (i*pSPS->ctb_num_width)/pPPS->num_tile_columns;
            }
            for (i=0; i<pPPS->num_tile_rows; i++)
            {
                pPPS->row_bd[i] = (i+1)*pSPS->ctb_num_height/pPPS->num_tile_rows - (i*pSPS->ctb_num_height)/pPPS->num_tile_rows;
            }
        }
        else
        {
            pPPS->column_bd[pPPS->num_tile_columns-1] = pSPS->ctb_num_width;
            for (i=0; i<pPPS->num_tile_columns-1; i++)
            {
                pPPS->column_bd[i] = pPPS->column_width[i];
                pPPS->column_bd[pPPS->num_tile_columns-1] -= pPPS->column_bd[i];
            }

            if (pPPS->column_bd[pPPS->num_tile_columns-1] <= 0)
            {
                dprint(PRN_ERROR,"column_bd[%d](%d) <= 0, invalid!\n", pPPS->num_tile_columns-1, pPPS->column_bd[pPPS->num_tile_columns-1]);	
                return HEVC_DEC_ERR;			
            }

            pPPS->row_bd[pPPS->num_tile_rows-1] = pSPS->ctb_num_height;
            for (i=0; i<pPPS->num_tile_rows-1; i++)
            {
                pPPS->row_bd[i] = pPPS->row_height[i];
                pPPS->row_bd[pPPS->num_tile_rows-1] -= pPPS->row_bd[i];
            }

            if (pPPS->row_bd[pPPS->num_tile_rows-1] <= 0)
            {
                dprint(PRN_ERROR,"row_bd[%d](%d) <= 0, invalid!\n", pPPS->num_tile_rows-1, pPPS->row_bd[pPPS->num_tile_rows-1]);	
                return HEVC_DEC_ERR;			
            }

        }
        
        if (pPPS->num_tile_columns != 1 || pPPS->num_tile_rows != 1)
        {
            pPPS->loop_filter_across_tiles_enabled_flag = HEVC_u_v(pHevcCtx->pBS, 1, "loop_filter_across_tiles_enabled_flag");
        }
    }
    else
    {
        pPPS->column_bd[0] = pSPS->ctb_num_width;
        pPPS->row_bd[0] = pSPS->ctb_num_height;
    }
    
    //3798MV100逻辑不支持tile宽度<=64、tile高度<64的码流
    for (i=0; i<pPPS->num_tile_columns; i++)
    {            
        if(pPPS->column_bd[i]*pSPS->max_cu_width <= 64 && pSPS->pic_width_in_luma_samples > 64)
        {
            dprint(PRN_ERROR, "PPS tile width(%d) is too small.(Logic Unsupport)\n", pPPS->column_bd[i]*pSPS->max_cu_width);        
            REPORT_UNSUPPORT(pHevcCtx->ChanID);
			return HEVC_DEC_ERR;
        }
    }
    for (i=0; i<pPPS->num_tile_rows; i++)
    {            
        if(pPPS->row_bd[i]*pSPS->max_cu_width < 64 )
        {
            dprint(PRN_ERROR, "PPS tile height(%d) is too small.(Logic Unsupport)\n", pPPS->row_bd[i]*pSPS->max_cu_width);   
            REPORT_UNSUPPORT(pHevcCtx->ChanID);
			return HEVC_DEC_ERR;
        }
    }
    
	pPPS->loop_filter_across_slices_enabled_flag  = HEVC_u_v(pHevcCtx->pBS, 1, "loop_filter_across_slices_enabled_flag");
	pPPS->deblocking_filter_control_present_flag  = HEVC_u_v(pHevcCtx->pBS, 1, "deblocking_filter_control_present_flag");
	if (pPPS->deblocking_filter_control_present_flag)
	{
	    pPPS->deblocking_filter_override_enabled_flag = HEVC_u_v(pHevcCtx->pBS, 1, "deblocking_filter_override_enabled_flag");
		pPPS->pic_disable_deblocking_filter_flag      = HEVC_u_v(pHevcCtx->pBS, 1, "pps_disable_deblocking_filter_flag");
		if (!pPPS->pic_disable_deblocking_filter_flag)
		{
			pPPS->pps_beta_offset_div2 = HEVC_se_v(pHevcCtx->pBS, "pps_beta_offset_div2");
			if (pPPS->pps_beta_offset_div2 < -6 || pPPS->pps_beta_offset_div2 > 6)
			{
				dprint(PRN_ERROR, "pps_beta_offset_div2(%d) out of range(-6,6).\n", pPPS->pps_beta_offset_div2);
                pPPS->pps_beta_offset_div2 = 0; //赋值强解
				//钳位继续解
				//return HEVC_DEC_ERR;		
			}
			pPPS->pps_tc_offset_div2   = HEVC_se_v(pHevcCtx->pBS, "pps_tc_offset_div2");
			if (pPPS->pps_tc_offset_div2 < -6 || pPPS->pps_tc_offset_div2 > 6)
			{
				dprint(PRN_ERROR, "pps_tc_offset_div2(%d) out of range(-6,6).\n", pPPS->pps_tc_offset_div2);
                pPPS->pps_tc_offset_div2 = 0; //赋值强解	
				// 钳位继续解
				// return HEVC_DEC_ERR;			
			}
		}
	}
	pPPS->pic_scaling_list_data_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "pps_scaling_list_data_present_flag");
	if (pPPS->pic_scaling_list_data_present_flag)
	{
	    ret = HEVC_DecScalingListData(pHevcCtx,&(pPPS->scaling_list));
		if (HEVC_DEC_NORMAL != ret)
		{
			dprint(PRN_ERROR, "PPS HEVC_DecScalingListData error.\n");
			return HEVC_DEC_ERR;
		}		
	}
	pPPS->lists_modification_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "lists_modification_present_flag");
	pPPS->log2_parallel_merge_level = HEVC_ue_v(pHevcCtx->pBS, "log2_parallel_merge_level_minus2") + 2;
	if (pPPS->log2_parallel_merge_level < 2 || pPPS->log2_parallel_merge_level > pSPS->log2_ctb_sizeY)
	{
		dprint(PRN_ERROR, "log2_parallel_merge_level(%d) out of range(2,log2_ctb_sizeY).\n", pPPS->log2_parallel_merge_level);
		return HEVC_DEC_ERR;	
	}
	pPPS->slice_segment_header_extension_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "slice_segment_header_extension_present_flag");
	pPPS->pps_extension_flag        = HEVC_u_v(pHevcCtx->pBS, 1, "pps_extension_flag");
	if (pPPS->pps_extension_flag)
	{
	    //more_rbsp_data_flag = HEVC_MoreRbspData();
	    while (HEVC_MoreRbspData(pHevcCtx))
	    {
	        pPPS->pps_extension_data_flag = HEVC_u_v(pHevcCtx->pBS, 1, "");
	    }
	}
    
    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_DecPPS(HEVC_CTX_S *pHevcCtx)
{
    UINT32 pic_parameter_set_id;

	HEVC_PIC_PARAM_SET_S *pps_tmp = NULL;

    pps_tmp = &(s_TmpParam.PpsTmp);
#ifndef HEVC_SYNTAX_OPT
    memset(pps_tmp, 0, sizeof(HEVC_PIC_PARAM_SET_S));
#endif

    pic_parameter_set_id = HEVC_ue_v(pHevcCtx->pBS, "pps_pic_parameter_set_id");

    
    if (pic_parameter_set_id >= (pHevcCtx->MaxPpsNum))
    {
        dprint(PRN_ERROR, "pic_parameter_set_id(%d) out of range(0,%d).\n", pic_parameter_set_id, pHevcCtx->MaxPpsNum);
        return HEVC_DEC_ERR;
    }
	if (pHevcCtx->pPPS[pic_parameter_set_id].valid) // 曾经解对过该id对应的PPS
	{
		pps_tmp->pic_parameter_set_id = pic_parameter_set_id;
		if (HEVC_DEC_NORMAL != HEVC_ProcessPPS(pHevcCtx, pps_tmp))
		{
			dprint(PRN_ERROR, "PPS[%d] decode error.\n", pic_parameter_set_id);
			return HEVC_DEC_ERR;
		}
		//不进行equal判断,只要能够正确解码,就进行拷贝,因为equal判断也比较复杂
		//if (HEVC_DEC_NORMAL != HEVC_PPSEqual(&pps_tmp, &(pHevcCtx->PPS[pic_parameter_set_id])))
		{
			pps_tmp->is_refresh = 1;
			pps_tmp->valid = 1;
			memmove(&(pHevcCtx->pPPS[pic_parameter_set_id]), pps_tmp, sizeof(HEVC_PIC_PARAM_SET_S));
		}
	}
	else
	{
		pHevcCtx->pPPS[pic_parameter_set_id].pic_parameter_set_id = pic_parameter_set_id;
		if (HEVC_DEC_NORMAL != HEVC_ProcessPPS(pHevcCtx, &(pHevcCtx->pPPS[pic_parameter_set_id])))
		{
			dprint(PRN_ERROR, "PPS[%d] decode error.\n", pic_parameter_set_id);
			pHevcCtx->pPPS[pic_parameter_set_id].is_refresh = 1;
			pHevcCtx->pPPS[pic_parameter_set_id].valid = 0;
			return HEVC_DEC_ERR;
		}
		pHevcCtx->pPPS[pic_parameter_set_id].is_refresh = 1;
		pHevcCtx->pPPS[pic_parameter_set_id].valid = 1;
	}

	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_DecSEI(HEVC_CTX_S *pHevcCtx)
{
    HEVC_SEI_PARAM_SET_S *pSEI;
    HEVC_SEQ_PARAM_SET_S *pSPS;
    UINT32 rbsp_trailing_bits;
	SINT32 ret;

    pSEI = &pHevcCtx->SEI;
    pSPS = &pHevcCtx->SEISPS;
    //pHevcCtx->pBS->HistoryPos = pHevcCtx->pBS->TotalPos;
    do
    {
        ret = HEVC_SeiMessage(pHevcCtx,pSEI, pSPS);
		if (HEVC_DEC_NORMAL != ret)
		{
			dprint(PRN_ERROR, "SEI HEVC_SeiMessage error.\n");
			return HEVC_DEC_ERR;			
		}
        
		if (BsIsByteAligned(pHevcCtx->pBS) == 0)
		{
            dprint(PRN_ERROR, "SEI BsIsByteAligned error.\n");
            return HEVC_DEC_ERR;
        }
    }
    while (HEVC_More_Rbsp_Data(pHevcCtx));

    rbsp_trailing_bits = HEVC_u_v(pHevcCtx->pBS, 8, "rbsp_trailing_bits");

	if (0x80 != rbsp_trailing_bits)
	{
		dprint(PRN_ERROR, "SEI rbsp_trailing_bits(%d) not equal 0x80.\n", rbsp_trailing_bits);
		return HEVC_DEC_ERR;	
	}
    
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_SeiMessage(HEVC_CTX_S *pHevcCtx,HEVC_SEI_PARAM_SET_S * pSEI, HEVC_SEQ_PARAM_SET_S * pSPS)
{
    UINT32 payloadType;
    UINT32 payloadSize;
	SINT32 ret;

    payloadType = 0;

    while (0xFF == BsShow(pHevcCtx->pBS, 8))
    {
        BsSkip(pHevcCtx->pBS, 8);
        payloadType += 255;

        /* l00232354: 20141213 DPT产品遇到一条码流，发现SEI只有14bit,但因解析时
           没有做nal有效长度的限制，从而导致概率性访问到无效地址挂死。
           当前解决办法:加一个有效长度判断条件，加8是因为后面还有8个bit的消耗
           ((pHevcCtx->pBS->TotalPos + 8) > pHevcCtx->pBS->BsLen)
           建议最终解决办法:将这块容错放到码流解析函数里去。
        */
        if ((pHevcCtx->pBS->TotalPos + 8) > pHevcCtx->pBS->BsLen)
        {
            dprint(PRN_ERROR, "line:%d Cosume TotalPos(%d > %d)!!!\n", __LINE__,
                   pHevcCtx->pBS->TotalPos, pHevcCtx->pBS->BsLen);
            return HEVC_DEC_ERR;
        }
    }
    pSEI->last_payload_type_byte = HEVC_u_v(pHevcCtx->pBS, 8, "last_payload_type_byte");
    payloadType += pSEI->last_payload_type_byte;

    payloadSize = 0;
    while (0xFF == BsShow(pHevcCtx->pBS, 8))
    {
        BsSkip(pHevcCtx->pBS, 8);
        payloadSize += 255;

        /* l00232354: 20141213 DPT产品遇到一条码流，发现SEI只有14bit,但因解析时
           没有做nal有效长度的限制，从而导致概率性访问到无效地址挂死。
           当前解决办法:加一个有效长度判断条件，加8是因为后面还有8个bit的消耗
           ((pHevcCtx->pBS->TotalPos + 8) > pHevcCtx->pBS->BsLen)
           建议最终解决办法:将这块容错放到码流解析函数里去。
        */
        if ((pHevcCtx->pBS->TotalPos + 8) > pHevcCtx->pBS->BsLen)
        {
            dprint(PRN_ERROR, "line:%d Cosume TotalPos(%d > %d)!!!\n", __LINE__,
                   pHevcCtx->pBS->TotalPos, pHevcCtx->pBS->BsLen);
            return HEVC_DEC_ERR;
        }
    }
    pSEI->last_payload_size_byte = HEVC_u_v(pHevcCtx->pBS, 8, "last_payload_size_byte");
    payloadSize += pSEI->last_payload_size_byte;

    ret = HEVC_Sei_Payload(pHevcCtx,pSEI, pSPS, payloadType, payloadSize);
	if (HEVC_DEC_NORMAL != ret)
	{
		dprint(PRN_ERROR, "HEVC_SeiMessage HEVC_Sei_Payload error.\n");
		return HEVC_DEC_ERR;			
	}

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Payload(HEVC_CTX_S *pHevcCtx,HEVC_SEI_PARAM_SET_S * pSEI, HEVC_SEQ_PARAM_SET_S * pSPS, UINT32 payloadType, UINT32 payloadSize)
{
    UINT32 i;
	SINT32 ret;

    if (NAL_UNIT_PREFIX_SEI == pHevcCtx->pCurrNal->nal_unit_type)
    {
        switch (payloadType)
        {
        case 0:
            ret = HEVC_Sei_Buf_Period(pHevcCtx,&(pSEI->buf_period), &(pSPS->vui_parameters.hrd_parameters));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
            break;
        case 1:
            ret = HEVC_Sei_Pic_Timming(pHevcCtx,&(pSEI->pic_timming), &(pSPS->vui_parameters));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
            break;
        case 5:
            ret = HEVC_Sei_User_Data_Unregistered(pHevcCtx,&(pSEI->user_data_unreg), payloadSize);
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        case 6:
			ret = HEVC_Sei_Recovery_Point(pHevcCtx,&(pSEI->recovery_point));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;           
        case 23:
            ret = HEVC_Sei_Tone_Mapping_Info( pHevcCtx,&(pSEI->tone_mapping_info));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;	
			}		
            break;
        case 45:
            ret = HEVC_Sei_Frame_Packing_Arrangement( pHevcCtx,&(pSEI->frame_packing));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
            break;
        case 47:
            ret = HEVC_Sei_Display_Orientation( pHevcCtx,&(pSEI->display_orientation));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        case 128:
            ret = HEVC_Sei_Structure_Of_Pictures_Info( pHevcCtx,&(pSEI->sop_info),payloadSize);
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        case 129:
            ret = HEVC_Sei_Active_Param_sets(pHevcCtx, &(pSEI->active_param_sets));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        case 130:
            ret = HEVC_Sei_Dec_Unit_Info(pHevcCtx,&(pSEI->decoding_unit_info),&(pSPS->vui_parameters.hrd_parameters));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        case 131:
            ret = HEVC_Sei_Temporal_Sub_Layer_Zero_Index( pHevcCtx,&(pSEI->temporal_sub_layer));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        case 133:
            ret = HEVC_Sei_Scalable_Nesting( pHevcCtx,pSEI, pSPS, payloadSize);
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        case 134:
            ret = HEVC_Sei_Region_Refresh_Info( pHevcCtx,&(pSEI->region_refresh_info));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
				
			case 169:
				ret = HEVC_Sei_Mastering_Display_Colour_Volume( pHevcCtx, &(pSEI->mastering_display_colour_volume));
                if (HEVC_DEC_NORMAL != ret)
                {
                    return HEVC_DEC_ERR;
                }
				break;

            default:
            for (i=0; i<payloadSize; i++)
            {
                HEVC_u_v(pHevcCtx->pBS, 8, "unknown prefix SEI payload byte");
            }
            break;
        }
    }
    else
    {
        switch (payloadType)
        {           
        case 5:
            ret = HEVC_Sei_User_Data_Unregistered( pHevcCtx,&(pSEI->user_data_unreg), payloadSize);
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;

        case 132:
            ret = HEVC_Sei_Decoded_Picture_Hash(pHevcCtx,&(pSEI->decoded_picture_hash));
			if (HEVC_DEC_NORMAL != ret)
			{
				return HEVC_DEC_ERR;
			}
			break;
        default:
            //HEVC_Sei_Reserved_Sei_Message(payloadSize);
            for (i=0; i<payloadSize; i++)
            {
                HEVC_u_v(pHevcCtx->pBS, 8, "unknown suffix SEI payload byte");
            }
            break;
        }
    }

    if (HEVC_Sei_More_Data_In_Payload(pHevcCtx,payloadSize))
    {
        if (HEVC_Sei_Payload_Extension_Present(pHevcCtx,payloadSize))
        {
            pSEI->reserved_payload_extension_data= HEVC_ue_v(pHevcCtx->pBS, "reserved_payload_extension_data");
        }
        pSEI->payload_bit_equal_to_one = HEVC_u_v(pHevcCtx->pBS, 1, "payload_bit_equal_to_one");
        while (!BsIsByteAligned(pHevcCtx->pBS))
        {
            pSEI->payload_bit_equal_to_zero = HEVC_u_v(pHevcCtx->pBS, 1, "payload_bit_equal_to_zero");
        }
    }
    
    return HEVC_DEC_NORMAL;
}


UINT32 HEVC_Sei_More_Data_In_Payload(HEVC_CTX_S *pHevcCtx,UINT32 payloadSize)
{
    SINT32 ispayloadSize;

    ispayloadSize = ((pHevcCtx->pBS->TotalPos-pHevcCtx->pBS->HistoryPos) == (8*payloadSize)) ? 1:0;
    if (BsIsByteAligned(pHevcCtx->pBS) && (0 == ispayloadSize))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


UINT32 HEVC_Sei_Payload_Extension_Present(HEVC_CTX_S *pHevcCtx,UINT32 payloadSize)
{
    UINT32 pos;
    BS *pBs;
	BS Bs;
	pBs = &Bs;

    memcpy(pBs, pHevcCtx->pBS, sizeof(BS));

    pos = pBs->TotalPos - pBs->HistoryPos;
    if (pos < 8*payloadSize)
    {
        if (BsShow(pBs, 1))
        {
            BsSkip(pBs, 1);
            pos = pBs->TotalPos-pBs->HistoryPos;
            while ((!BsShow(pBs, 1)) && (pos < 8*payloadSize))
            {
                BsSkip(pBs, 1);
                pos = pBs->TotalPos-pBs->HistoryPos;
            }
            if (pos >= 8*payloadSize)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
       else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}


SINT32 HEVC_Sei_Decoded_Picture_Hash(HEVC_CTX_S *pHevcCtx,HEVC_SEI_DECODED_PICTURE_HASH_S * pDec)
{ 
    UINT32 i;  
    UINT32 j;  
    UINT32 val;  
    
    if (pHevcCtx == NULL || pDec == NULL)
    {
        return HEVC_DEC_ERR;
    }

    pDec->hash_type = HEVC_u_v(pHevcCtx->pBS, 8, "hash_type"); 
    pDec->method = (HEVC_SEI_Method)pDec->hash_type;
    for(j = 0; j < 3; j++)
    {    
        if(MD5 == pDec->method)    
        {     
            for ( i = 0; i < 16; i++)     
            {        
                pDec->digest[j][i] = HEVC_u_v(pHevcCtx->pBS, 8, "picture_md5");       
            }    
        }    
        else if(CRC == pDec->method)    
        {      
            val = HEVC_u_v(pHevcCtx->pBS, 16, "picture_crc");     
            pDec->digest[j][0] = val >> 8 & 0xFF;     
            pDec->digest[j][1] = val & 0xFF;  
        }    
        else if(CHECKSUM == pDec->method)   
        {     
            val = HEVC_u_v(pHevcCtx->pBS, 32, "picture_checksum"); 
            pDec->digest[j][0] = (val>>24) & 0xff;    
            pDec->digest[j][1] = (val>>16) & 0xff;     
            pDec->digest[j][2] = (val>>8)  & 0xff;      
            pDec->digest[j][3] =  val      & 0xff;   
        } 
    }
    
	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Scalable_Nesting(HEVC_CTX_S *pHevcCtx,HEVC_SEI_PARAM_SET_S * pSEI, HEVC_SEQ_PARAM_SET_S * pSPS, UINT32 payloadsize)
{
    UINT32 i;
	SINT32 ret;
    HEVC_SEI_SCALABLE_NESTING_S *pSca = NULL;

    pSca = &(pSEI->scalable_nesting);
    pSca->bitstream_subset_flag = HEVC_u_v(pHevcCtx->pBS, 1, "bitstream_subset_flag");      
    pSca->nesting_op_flag= HEVC_u_v(pHevcCtx->pBS, 1, "nesting_op_flag"); 
    
    if (pSca->nesting_op_flag)
    {
        pSca->default_op_flag = HEVC_u_v(pHevcCtx->pBS, 1, "default_op_flag");
        pSca->nesting_num_ops_minus1 = HEVC_ue_v(pHevcCtx->pBS, "nesting_num_ops_minus1");

        if (pSca->nesting_num_ops_minus1 >= HEVC_MAX_NESTING_NUM_LAYER)
        {
            dprint(PRN_ERROR, "nesting_num_ops_minus1 out of range(0,%d)\n", HEVC_MAX_NESTING_NUM_LAYER);
            return HEVC_DEC_ERR;
        }
        for (i = pSca->default_op_flag; i <= pSca->nesting_num_ops_minus1; i++)
        {
            pSca->nesting_max_temporal_id_plus1[i] = HEVC_u_v(pHevcCtx->pBS, 3, "nesting_max_temporal_id_plus1"); 
            pSca->nesting_op_idx[i] = HEVC_ue_v(pHevcCtx->pBS, "nesting_op_idx"); 
        }
    }
    else
    {
        pSca->all_layers_flag       = HEVC_u_v(pHevcCtx->pBS, 1, "all_layers_flag"); 
        if (!(pSca->all_layers_flag))
        {
            pSca->nesting_no_op_max_temporal_id_plus1 = HEVC_u_v(pHevcCtx->pBS, 3, "nesting_no_op_max_temporal_id_plus1"); 
            pSca->nesting_num_layers_minus1 = HEVC_ue_v(pHevcCtx->pBS,  "nesting_num_layers_minus1");
            if (pSca->nesting_num_layers_minus1 > 63)
            {
                dprint(PRN_ERROR, "nesting_num_layers_minus1 out of range(0,63)\n");
                return HEVC_DEC_ERR;
            }
            for (i = 0; i <= pSca->nesting_num_layers_minus1; i++)
            {
                pSca->nesting_layer_id[i]   = HEVC_u_v(pHevcCtx->pBS, 6, "nesting_num_layers_minus1"); 
            }
        }
    }
    
    BsToNextByte(pHevcCtx->pBS);
    
    pSca->callerOwnsSEIs = HEVC_FALSE;
    do
    {
        ret = HEVC_SeiMessage(pHevcCtx,pSEI,pSPS);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_ERROR, "SEI HEVC_SeiMessage error.\n");
            return HEVC_DEC_ERR;			
        }
    }
    while (HEVC_MoreRbspData(pHevcCtx));
    
    return HEVC_DEC_NORMAL; 
}


SINT32 HEVC_Sei_Structure_Of_Pictures_Info(HEVC_CTX_S *pHevcCtx,HEVC_SEI_SOP_INFO_S *pSop, UINT32 payloadSize)
{
    UINT32 i;
    
    pSop->sop_seq_parameter_set_id= HEVC_ue_v(pHevcCtx->pBS, "sop_seq_parameter_set_id"); 
    pSop->num_entries_in_sop_minus1 = HEVC_ue_v(pHevcCtx->pBS,  "num_entries_in_sop_minus1");
	if (pSop->num_entries_in_sop_minus1 > 1024)
	{
		dprint(PRN_ERROR, "num_entries_in_sop_minus1 out of range(0,1024)\n");
		return HEVC_DEC_ERR;
	}

    for (i=0; i<pSop->num_entries_in_sop_minus1; i++)
    {
        pSop->sop_vcl_nut[i]   = HEVC_u_v(pHevcCtx->pBS, 6, "sop_vcl_nut"); 
        pSop->sop_temporal_id[i]   = HEVC_u_v(pHevcCtx->pBS, 3, "sop_temporal_id"); 
        if ((NAL_UNIT_CODED_SLICE_IDR_W_RADL != pSop->sop_vcl_nut[i]) && (NAL_UNIT_CODED_SLICE_IDR_N_LP!= pSop->sop_vcl_nut[i]))
        {
            pSop->sop_short_term_rps_idx[i] = HEVC_ue_v(pHevcCtx->pBS,  "sop_short_term_rps_idx"); 
        }
        if (i>0)
        {
            pSop->sop_poc_delta[i] = HEVC_se_v(pHevcCtx->pBS,  "sop_poc_delta"); 
        }
    }

    BsToNextByte(pHevcCtx->pBS);
    
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Tone_Mapping_Info(HEVC_CTX_S *pHevcCtx,HEVC_SEI_TONE_MAPPING_INFO_S * pTon)
{
    UINT32 i;
    UINT32 num;
    
    pTon->tone_map_id  = HEVC_ue_v(pHevcCtx->pBS, "tone_map_id"); 
    pTon->tone_map_cancel_flag = HEVC_u_v(pHevcCtx->pBS, 1, "tone_map_cancel_flag"); 

    if ( !pTon->tone_map_cancel_flag )
    {
        pTon->tone_map_persistence_flag = HEVC_u_v(pHevcCtx->pBS, 1, "tone_map_persistence_flag"); 
        pTon->coded_data_bit_depth = HEVC_u_v(pHevcCtx->pBS, 8, "coded_data_bit_depth"); 
        pTon->target_bit_depth = HEVC_u_v(pHevcCtx->pBS, 8, "target_bit_depth"); 

		if (pTon->target_bit_depth > 8)//应该为1-16,为了节约内存，只支持到8.
		{
			dprint(PRN_ERROR, "Unsupport: target_bit_depth(%d) > 8\n", pTon->target_bit_depth);
			return HEVC_DEC_ERR;
		}
		
        pTon->tone_map_model_id = HEVC_u_v(pHevcCtx->pBS, 8, "tone_map_model_id"); 
    }
    switch(pTon->tone_map_model_id)
    {
      case 0:
          pTon->min_value = HEVC_u_v(pHevcCtx->pBS, 32, "min_value"); 
          pTon->max_value = HEVC_u_v(pHevcCtx->pBS, 32, "max_value"); 
          break;
      case 1:
          pTon->sigmoid_midpoint = HEVC_u_v(pHevcCtx->pBS, 32, "sigmoid_midpoint"); 
          pTon->sigmoid_width = HEVC_u_v(pHevcCtx->pBS, 32, "sigmoid_width"); 
          break;
      case 2:
          num = 1 << (pTon->target_bit_depth);
          for(i = 0; i < num; i++)
          {
              pTon->start_of_coded_interval[i] = HEVC_u_v(pHevcCtx->pBS, ((( pTon->coded_data_bit_depth+ 7 ) >> 3 ) << 3), "start_of_coded_interval"); 
          }
          pTon->start_of_coded_interval[num] = 1 << pTon->coded_data_bit_depth;
          break;
      case 3:
          pTon->num_pivots = HEVC_u_v(pHevcCtx->pBS, 16, "num_pivots"); 
		  if (pTon->num_pivots > 256)
		  {
			  dprint(PRN_ERROR, "pTon->num_pivots > 256\n");
			  return HEVC_DEC_ERR;			  
		  }	  
          for(i = 0; i < pTon->num_pivots; i++ )
          {
              pTon->coded_pivot_value[i] = HEVC_u_v(pHevcCtx->pBS, ((( pTon->coded_data_bit_depth + 7 ) >> 3 ) << 3), "coded_pivot_value"); 
              pTon->target_pivot_value[i] = HEVC_u_v(pHevcCtx->pBS, ((( pTon->target_bit_depth + 7 ) >> 3 ) << 3), "target_pivot_value"); 
          }
          break;
      case 4:
          pTon->camera_iso_speed_idc = HEVC_u_v(pHevcCtx->pBS, 8, "camera_iso_speed_idc"); 
          if( pTon->camera_iso_speed_idc == 255) //Extended_ISO
          {
            pTon->camera_iso_speed_value = HEVC_u_v(pHevcCtx->pBS, 32, "camera_iso_speed_value"); 
          }
          pTon->exposure_compensation_value_sign_flag = HEVC_u_v(pHevcCtx->pBS, 1, "exposure_compensation_value_sign_flag"); 
          pTon->exposure_compensation_value_numerator = HEVC_u_v(pHevcCtx->pBS, 16, "exposure_compensation_value_numerator"); 
          pTon->exposure_compensation_value_denom_idc = HEVC_u_v(pHevcCtx->pBS, 16, "exposure_compensation_value_denom_idc"); 
          pTon->ref_screen_luminance_white = HEVC_u_v(pHevcCtx->pBS, 32, "ref_screen_luminance_white"); 
          pTon->extended_range_white_level = HEVC_u_v(pHevcCtx->pBS, 32, "extended_range_white_level"); 
          pTon->nominal_black_level_code_value = HEVC_u_v(pHevcCtx->pBS, 16, "nominal_black_level_code_value");
          pTon->nominal_white_level_code_value= HEVC_u_v(pHevcCtx->pBS, 16, "nominal_white_level_code_value");
          pTon->exposure_compensation_value_numerator = HEVC_u_v(pHevcCtx->pBS, 16, "exposure_compensation_value_numerator");
          pTon->extended_white_level_code_value = HEVC_u_v(pHevcCtx->pBS, 16, "extended_white_level_code_value");
          break;
        }
    
      	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Region_Refresh_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_REGION_REFRESH_INFO_S *pReg)
{
    if (pHevcCtx == NULL || pReg == NULL)
    {
        return HEVC_DEC_ERR;
    }

    pReg->refreshed_region_flag = HEVC_u_v(pHevcCtx->pBS, 1, "refreshed_region_flag");

    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_Sei_Mastering_Display_Colour_Volume(HEVC_CTX_S *pHevcCtx, HEVC_SEI_MASTERING_DISPLAY_COLOUR_VOLUME_S *pReg)
{
	UINT32 i = 0;
    if (pHevcCtx == NULL || pReg == NULL)
    {
        return HEVC_DEC_ERR;
    }
	for(i=0; i<3; i++)
	{
	    pReg->display_primaries_x[i] = HEVC_u_v(pHevcCtx->pBS, 16, "display_primaries_x");
		pReg->display_primaries_y[i] = HEVC_u_v(pHevcCtx->pBS, 16, "display_primaries_y");
	}
	pReg->white_point_x = HEVC_u_v(pHevcCtx->pBS, 16, "white_point_x");
	pReg->white_point_y = HEVC_u_v(pHevcCtx->pBS, 16, "white_point_y");
	pReg->max_display_mastering_luminance = HEVC_u_v(pHevcCtx->pBS, 32, "max_display_mastering_luminance");
	pReg->min_display_mastering_luminance = HEVC_u_v(pHevcCtx->pBS, 32, "min_display_mastering_luminance");
	
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Temporal_Sub_Layer_Zero_Index(HEVC_CTX_S *pHevcCtx, HEVC_SEI_TEMPORAL_SUB_LAYER_S *pTem)
{
    if (pHevcCtx == NULL || pTem == NULL)
    {
        return HEVC_DEC_ERR;
    }

    pTem->temporal_sub_layer_zero_idx = HEVC_u_v(pHevcCtx->pBS, 1, "temporal_sub_layer_zero_idx");
    pTem->irap_pic_id = HEVC_u_v(pHevcCtx->pBS, 1, "irap_pic_id");
    BsToNextByte(pHevcCtx->pBS);

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Display_Orientation(HEVC_CTX_S *pHevcCtx, HEVC_SEI_DISPLAY_ORIENTATION_S *pDis)
{
    if (pHevcCtx == NULL || pDis == NULL)
    {
        return HEVC_DEC_ERR;
    }

    pDis->display_orientation_cancel_flag = HEVC_u_v(pHevcCtx->pBS, 1, "display_orientation_cancel_flag");

    if (!pDis->display_orientation_cancel_flag)
    {
        pDis->hor_flip = HEVC_u_v(pHevcCtx->pBS, 1, "hor_flip");
        pDis->ver_flip = HEVC_u_v(pHevcCtx->pBS, 1, "ver_flip");
        pDis->anticlockwise_rotation = HEVC_u_v(pHevcCtx->pBS, 16, "anticlockwise_rotation");
        pDis->display_orientation_persistence_flag = HEVC_u_v(pHevcCtx->pBS, 1, "display_orientation_persistence_flag");
    }

    BsToNextByte(pHevcCtx->pBS);

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Frame_Packing_Arrangement(HEVC_CTX_S *pHevcCtx, HEVC_SEI_FRAME_PACKING_ARRANGEMENT_S *pFrm)
{
    pFrm->frame_packing_arrangement_id = HEVC_ue_v(pHevcCtx->pBS, "frame_packing_arrangement_id");
    pFrm->frame_packing_arrangement_cancel_flag = HEVC_u_v(pHevcCtx->pBS, 1, "frame_packing_arrangement_cancel_flag");

    if ( !pFrm->frame_packing_arrangement_cancel_flag )
    {
        pFrm->frame_packing_arrangement_type = HEVC_u_v(pHevcCtx->pBS, 7, "frame_packing_arrangement_type");

        if ((pFrm->frame_packing_arrangement_type <= 2) || (pFrm->frame_packing_arrangement_type >= 6) )
        {
            dprint(PRN_ERROR, "frame_packing_arrangement_type(%d) out of range\n", pFrm->frame_packing_arrangement_type);
            return HEVC_DEC_ERR;
        }

        pFrm->quincunx_sampling_flag = HEVC_u_v(pHevcCtx->pBS, 1, "quincunx_sampling_flag");
        pFrm->content_interpretation_type = HEVC_u_v(pHevcCtx->pBS, 6, "content_interpretation_type");
        pFrm->spatial_flipping_flag = HEVC_u_v(pHevcCtx->pBS, 1, "spatial_flipping_flag");
        pFrm->frame0_flipped_flag = HEVC_u_v(pHevcCtx->pBS, 1, "frame0_flipped_flag");
        pFrm->field_views_flag = HEVC_u_v(pHevcCtx->pBS, 1, "field_views_flag");
        pFrm->current_frame_is_frame0_flag = HEVC_u_v(pHevcCtx->pBS, 1, "current_frame_is_frame0_flag");
        pFrm->frame0_self_contained_flag = HEVC_u_v(pHevcCtx->pBS, 1, "frame0_self_contained_flag");
        pFrm->frame1_self_contained_flag = HEVC_u_v(pHevcCtx->pBS, 1, "frame1_self_contained_flag");

        if ( (pFrm->quincunx_sampling_flag == 0) && (pFrm->frame_packing_arrangement_type != 5))
        {
            pFrm->frame0_grid_position_x = HEVC_u_v(pHevcCtx->pBS, 4, "frame0_grid_position_x");
            pFrm->frame0_grid_position_y = HEVC_u_v(pHevcCtx->pBS, 4, "frame0_grid_position_y");
            pFrm->frame1_grid_position_x = HEVC_u_v(pHevcCtx->pBS, 4, "frame1_grid_position_x");
            pFrm->frame1_grid_position_y = HEVC_u_v(pHevcCtx->pBS, 4, "frame1_grid_position_y");
        }

        pFrm->frame_packing_arrangement_reserved_byte = HEVC_u_v(pHevcCtx->pBS, 8, "frame_packing_arrangement_reserved_byte");
        pFrm->frame_packing_arrangement_persistence_flag = HEVC_u_v(pHevcCtx->pBS, 1, "frame_packing_arrangement_persistence_flag");
    }

    pFrm->upsampled_aspect_ratio_flag = HEVC_u_v(pHevcCtx->pBS, 1, "upsampled_aspect_ratio_flag");

    BsToNextByte(pHevcCtx->pBS);

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Recovery_Point(HEVC_CTX_S *pHevcCtx, HEVC_SEI_RECOVERY_POINT_S *pRec)
{
    if (pHevcCtx == NULL || pRec == NULL)
    {
        return HEVC_DEC_ERR;
    }

    pRec->recovery_poc_cnt = HEVC_se_v(pHevcCtx->pBS, "recovery_poc_cnt");
    pRec->exact_match_flag = HEVC_u_v(pHevcCtx->pBS, 1, "exact_match_flag");
    pRec->broken_link_flag = HEVC_u_v(pHevcCtx->pBS, 1, "broken_link_flag");
    BsToNextByte(pHevcCtx->pBS);

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Dec_Unit_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_DECODEING_UNIT_INFO_S *pDec, HEVC_HRD_PARAM_SET_S *pHrd)
{
    if (pHevcCtx == NULL || pDec == NULL || pHrd == NULL)
    {
        return HEVC_DEC_ERR;
    }

    pDec->decoding_unit_idx = HEVC_ue_v(pHevcCtx->pBS, "decoding_unit_idx");

    if (pHrd->sub_pic_cpb_params_in_pic_timing_sei_flag)
    {
        pDec->du_spt_cpb_removal_delay_increment = HEVC_u_v(pHevcCtx->pBS, pHrd->du_cpb_removal_delay_increment_length_minus1 + 1, "du_spt_cpb_removal_delay_increment");
    }
    else
    {
        pDec->du_spt_cpb_removal_delay_increment = 0;
    }

    pDec->dpb_output_du_delay_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "dpb_output_du_delay_present_flag");

    if (pDec->dpb_output_du_delay_present_flag)
    {
        pDec->pic_spt_dpb_output_du_delay = HEVC_u_v(pHevcCtx->pBS, pHrd->dpb_output_delay_du_length_minus1 + 1, "pic_spt_dpb_output_du_delay");
    }

    BsToNextByte(pHevcCtx->pBS);

    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_Sei_Active_Param_sets(HEVC_CTX_S *pHevcCtx, HEVC_SEI_ACTIVE_PARAMETER_SET_S *pAct)
{
    SINT32 i;
    pAct->active_video_parameter_set_id = HEVC_u_v(pHevcCtx->pBS, 4, "active_video_parameter_set_id");
    pAct->self_contained_cvs_flag = HEVC_u_v(pHevcCtx->pBS, 1, "self_contained_cvs_flag");
    pAct->no_parameter_set_update_flag = HEVC_u_v(pHevcCtx->pBS, 1, "no_parameter_set_update_flag");
    pAct->num_sps_ids_minus1 = HEVC_ue_v(pHevcCtx->pBS, "num_sps_ids_minus1");

    if (pAct->num_sps_ids_minus1 > 15)
    {
        dprint(PRN_ERROR, "pAct->num_sps_ids_minus1 > 15\n");
        return HEVC_DEC_ERR;
    }

    for (i = 0; i <= pAct->num_sps_ids_minus1; i++)
    {
        pAct->active_seq_parameter_set_id[i] = HEVC_ue_v(pHevcCtx->pBS, "active_seq_parameter_set_id");
    }

    BsToNextByte(pHevcCtx->pBS);

    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_Sei_Buf_Period(HEVC_CTX_S *pHevcCtx, HEVC_SEI_BUF_PERIOD_S *pBuf, HEVC_HRD_PARAM_SET_S *pHrd)
{
    UINT32 i = 0, j = 0;

    pBuf->bp_seq_parameter_set_id = HEVC_ue_v(pHevcCtx->pBS, "bp_seq_parameter_set_id");

    if ((pBuf->bp_seq_parameter_set_id) > 15)
    {
        dprint(PRN_ERROR, "Wrong bp_seq_parameter_set_id = %d, should be 0 to 15!\n", pBuf->bp_seq_parameter_set_id);
        return HEVC_DEC_ERR;
    }

    if ( !pHrd->sub_pic_hrd_params_present_flag)
    {
        pBuf->irap_cpb_params_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "irap_cpb_params_present_flag");
    }
    
    //Buf->concatenation_flag = HEVC_u_v(pHevcCtx->pBS, 1, "concatenation_flag");
    //pBuf->au_cpb_removal_delay_delta_minus1 = HEVC_u_v(pHevcCtx->pBS, pHrd->au_cpb_removal_delay_length_minus1+1, "au_cpb_removal_delay_delta_minus1");
    if( pBuf->irap_cpb_params_present_flag)
    {
        pBuf->cpb_delay_offset = HEVC_u_v(pHevcCtx->pBS, pHrd->au_cpb_removal_delay_length_minus1+1, "cpb_delay_offset");
        pBuf->dpb_delay_offset = HEVC_u_v(pHevcCtx->pBS, pHrd->dpb_output_delay_length_minus1+1, "dpb_delay_offset");    
    }

    pBuf->concatenation_flag = HEVC_u_v(pHevcCtx->pBS,1,"concatenation_flag");
    pBuf->au_cpb_removal_delay_delta_minus1 = HEVC_u_v(pHevcCtx->pBS,pHrd->au_cpb_removal_delay_length_minus1+1,"au_cpb_removal_delay_delta_minus1")+1;

    
    if (pHrd->hrd_sublayer[0].cpb_cnt_minus1 > 31)
    {
        dprint(PRN_ERROR, "HEVC_Sei_Buf_Period cpb_cnt_minus1(%d) out of range(0,31).\n", pHrd->hrd_sublayer[i].cpb_cnt_minus1);
        pHrd->hrd_sublayer[0].cpb_cnt_minus1 = 0;  // 赋值强解
        //return HEVC_DEC_ERR;
    }

    for( j = 0; j < 2; j ++ )
    {
      if(((j == 0) && (pHrd->nal_hrd_parameters_present_flag)) 
      || ((j == 1) && (pHrd->vcl_hrd_parameters_present_flag)))
      {
        for(i = 0; i < (pHrd->hrd_sublayer[0].cpb_cnt_minus1+1); i++)
        {
          pBuf->nal_vcl_inf[i][j].initial_cpb_removal_delay = HEVC_u_v(pHevcCtx->pBS, pHrd->initial_cpb_removal_delay_length_minus1+1, "nal_initial_cpb_removal_delay");
          pBuf->nal_vcl_inf[i][j].initial_cpb_removal_offset = HEVC_u_v(pHevcCtx->pBS, pHrd->initial_cpb_removal_delay_length_minus1+1, "nal_initial_cpb_removal_offset");
          if( pHrd->sub_pic_hrd_params_present_flag || pBuf->irap_cpb_params_present_flag)
          {
            pBuf->nal_vcl_inf[i][j].initial_alt_cpb_removal_delay = HEVC_u_v(pHevcCtx->pBS, pHrd->initial_cpb_removal_delay_length_minus1+1, "nal_initial_alt_cpb_removal_delay");
            pBuf->nal_vcl_inf[i][j].initial_alt_cpb_removal_offset = HEVC_u_v(pHevcCtx->pBS, pHrd->initial_cpb_removal_delay_length_minus1+1, "nal_initial_cpb_alt_removal_offset");
          }
        }
      }
    }
    BsToNextByte(pHevcCtx->pBS); 
    
	return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_Pic_Timming(HEVC_CTX_S *pHevcCtx,HEVC_SEI_PIC_TIMMING_S * pPic, HEVC_VUI_PARAM_SET_S * pVui)
{
    UINT32 i;
    HEVC_HRD_PARAM_SET_S *pHrd = NULL;
    
    pHrd = &(pVui->hrd_parameters);
    
    if( pVui->frame_field_info_present_flag)
    {
        pPic->pic_struct = HEVC_u_v(pHevcCtx->pBS, 4, "pic_struct");
        pPic->source_scan_type = HEVC_u_v(pHevcCtx->pBS, 2, "source_scan_type");
        pPic->duplicate_flag  = HEVC_u_v(pHevcCtx->pBS, 1, "duplicate_flag");
    }
  
    if( pHrd->nal_hrd_parameters_present_flag || pHrd->vcl_hrd_parameters_present_flag)
    {
      pPic->au_cpb_removal_delay_minus1 = HEVC_u_v(pHevcCtx->pBS, pHrd->au_cpb_removal_delay_length_minus1+1, "au_cpb_removal_delay_minus1")+1;
      pPic->pic_dpb_output_delay = HEVC_u_v(pHevcCtx->pBS, pHrd->dpb_output_delay_length_minus1+1, "pic_dpb_output_delay");
  
      if(pHrd->sub_pic_hrd_params_present_flag)
      {
          pPic->pic_dpb_output_du_delay = HEVC_u_v(pHevcCtx->pBS, pHrd->dpb_output_delay_du_length_minus1+1, "pic_dpb_output_du_delay");
      }
      if( pHrd->sub_pic_hrd_params_present_flag && pHrd->sub_pic_cpb_params_in_pic_timing_sei_flag)
      {
          pPic->num_decoding_units_minus1 = HEVC_ue_v(pHevcCtx->pBS, "num_decoding_units_minus1");
          pPic->du_common_cpb_removal_delay_flag =  HEVC_u_v(pHevcCtx->pBS, 1, "du_common_cpb_removal_delay_flag");
          if( pPic->du_common_cpb_removal_delay_flag)
          {
              pPic->du_common_cpb_removal_delay_increment_minus1 = HEVC_u_v(pHevcCtx->pBS, pHrd->du_cpb_removal_delay_increment_length_minus1+1, "du_common_cpb_removal_delay_minus1");
          } 
          
          if (pPic->num_decoding_units_minus1 > 255)
          {
              dprint(PRN_ERROR, "pPic->num_decoding_units_minus1 > 255\n");
              return HEVC_DEC_ERR;
          }
  
          for( i = 0; i <= pPic->num_decoding_units_minus1; i ++ )
          {
              pPic->num_nalus_in_du_minus1[ i ] = HEVC_ue_v(pHevcCtx->pBS, "num_nalus_in_du_minus1");
              if(!pPic->du_common_cpb_removal_delay_flag)
              {
                  pPic->du_cpb_removal_delay_increment_minus1[ i ] = HEVC_u_v(pHevcCtx->pBS, pHrd->du_cpb_removal_delay_increment_length_minus1+1, "du_cpb_removal_delay_increment_length_minus1");
              }
          }
      }
    }
    
    BsToNextByte(pHevcCtx->pBS); 
    
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_Sei_User_Data_Unregistered(HEVC_CTX_S *pHevcCtx,HEVC_SEI_USER_DATA_UNREG_S * pData, UINT32 payloadSize)
{
    UINT32 i;

	if (payloadSize < 16)
	{
		 dprint(PRN_ERROR, "HEVC_Sei_User_Data_Unregistered payloadSize < 16\n");
		 return HEVC_DEC_ERR;		
	}
	
    for (i=0; i<16; i++)
    {
        pData->uuid_iso_iec_11578[i] = HEVC_u_v(pHevcCtx->pBS, 8, "uuid_iso_iec_11578");
    }

    pData->userDataLength = payloadSize -16;
    if (!(pData->userDataLength))
    {
        pData->user_data_payload_byte = 0;
        return HEVC_DEC_NORMAL;
    }

    for (i=0; i<pData->userDataLength; i++)
    {
        HEVC_u_v(pHevcCtx->pBS, 8, "userData");//ignore the data
    }
    
	return HEVC_DEC_NORMAL;
}


/* 检查参考列表是否有错误 */
SINT32 HEVC_IsRefListWrong(HEVC_CTX_S *pHevcCtx)
{
    SINT32 i, ret = 0;
    //SINT32 FindExistFrame;

    FSP_LOGIC_FS_S *pstLogicFs = NULL;

    /* 检查list 0 */
    if (pHevcCtx->CurrSlice.listXsize[0] > 0)
    {
        //FindExistFrame = 0;
        for (i = 0; i < pHevcCtx->CurrSlice.listXsize[0]; i++)
        {
            if (pHevcCtx->pListX[0][i] == NULL)
            {
                ret = 1;
                dprint(PRN_ERROR, "pListX[0][%d] = NULL, listXsize[0] = %d\n", i, pHevcCtx->CurrSlice.listXsize[0]);
                break;
            }

            if (pHevcCtx->pListX[0][i]->frame_store == NULL)
            {
                ret = 1;
                dprint(PRN_ERROR, "pListX[0][%d]->frame_store = NULL, listXsize[0] = %d\n", i, pHevcCtx->CurrSlice.listXsize[0]);
                break;
            }

            pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->pListX[0][i]->frame_store->logic_fs_id);

            if ((NULL == pstLogicFs) || ((NULL != pstLogicFs) && (NULL == pstLogicFs->pstDecodeFs)))
            {
                ret = 1;
                dprint(PRN_ERROR, "pListX[0][%d] frame_store(%p), pstLogicFs(%p) invalid\n", i, pHevcCtx->pListX[0][i]->frame_store, pstLogicFs);
                break;
            }

            if (pHevcCtx->pListX[0][i]->frame_store->non_existing == 0)
            {
                //FindExistFrame = 1;
            }
        }
    }

    /* 若list 0检查无误，而且list 1非空，继续检查list 1 */
    if ((0 == ret) && (pHevcCtx->CurrSlice.listXsize[0] > 0))
    {
        //FindExistFrame = 0;

        for (i = 0; i < pHevcCtx->CurrSlice.listXsize[1]; i++)
        {
            if (pHevcCtx->pListX[1][i] == NULL)
            {
                ret = 1;
                dprint(PRN_ERROR, "pListX[1][%d] = NULL, listXsize[1] = %d\n", i, pHevcCtx->CurrSlice.listXsize[0]);
                break;
            }

            if (pHevcCtx->pListX[1][i]->frame_store == NULL)
            {
                ret = 1;
                dprint(PRN_ERROR, "pListX[1][%d]->frame_store = NULL, listXsize[1] = %d\n", i, pHevcCtx->CurrSlice.listXsize[0]);
                break;
            }

            pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->pListX[1][i]->frame_store->logic_fs_id);

            if ((NULL == pstLogicFs) || ((NULL != pstLogicFs) && (NULL == pstLogicFs->pstDecodeFs)))
            {
                ret = 1;
                dprint(PRN_ERROR, "pListX[i][%d] pstLogicFs(%p) invalid\n", i, pstLogicFs);
                break;
            }

#if 0

            if (pHevcCtx->pListX[1][i]->frame_store->non_existing == 0)
            {
                FindExistFrame = 1;
            }

#endif
        }
    }

    ret = (ret == 1) ? HEVC_DEC_ERR : HEVC_DEC_NORMAL;

    return ret;
}


SINT32 HEVC_GetUnRefPicWithMinPoc(HEVC_CTX_S *pHevcCtx, SINT32 *pos)
{
    UINT32 i;
    SINT32 poc = 0x7fffffff;;
    
    *pos = -1;

    if (pHevcCtx->DPB.used_size >= HEVC_MAX_DPB_NUM)
    {
        dprint(PRN_ERROR,"%s DPB.used_size(%d) >= 17.\n", __func__, pHevcCtx->DPB.used_size);   
        return HEVC_DEC_ERR;
    }
    
    for (i=0; i<pHevcCtx->DPB.used_size; i++)
    {
        if ((poc > pHevcCtx->DPB.fs[i]->poc)
         && (0 == pHevcCtx->DPB.fs[i]->is_displayed)
         && (0 == pHevcCtx->DPB.fs[i]->is_reference))
        {
            poc = pHevcCtx->DPB.fs[i]->poc;
            *pos = i;
        }
    }

    if (-1 == *pos)
    {
        dprint(PRN_ERROR,"%s can't find such pic.\n", __func__);   
        return HEVC_DEC_ERR;
    }
    else
    {
        dprint(PRN_ERROR,"%s find pos=%d, poc=%d.\n", __func__, *pos, poc);  
        return HEVC_DEC_NORMAL;
    }
}

SINT32 HEVC_IncreaseDPBSize(HEVC_CTX_S *pHevcCtx)
{
    SINT32 total_fs_num;
    
    if (pHevcCtx->DPB.size >= HEVC_MAX_DPB_NUM)
    {
		dprint(PRN_ERROR,"%s DPB.size(%d) already reached max(%d).\n", __func__, pHevcCtx->DPB.size, HEVC_MAX_DPB_NUM);
        pHevcCtx->DPB.size = HEVC_MAX_DPB_NUM;
        return HEVC_DEC_ERR;
    }
    
    total_fs_num = FSP_GetTotalValidFsNum(pHevcCtx->ChanID);
	if (total_fs_num > 0 && total_fs_num >= pHevcCtx->DPB.size+1)  // ExpectDecFsNum = pHevcCtx->DPB.size+1
	{
		pHevcCtx->DPB.size++;
		dprint(PRN_REF,"%s increase DPB size to %d\n", __func__, pHevcCtx->DPB.size);
        return HEVC_DEC_NORMAL;
	}
    else
    {
		dprint(PRN_ERROR,"%s no enough fs(total_fs_num=%d) to increase DPB size.\n", __func__, total_fs_num);
        return HEVC_DEC_ERR;
    }
}

SINT32 HEVC_OutputUnRefPicWithMinPoc(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    SINT32 pos;
    
    ret = HEVC_GetUnRefPicWithMinPoc(pHevcCtx, &pos);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_ERROR,"%s call HEVC_GetUnRefPicWithMinPoc failed\n", __func__);   
        return HEVC_DEC_ERR;
    }
    
    ret = HEVC_OutputOneFrmFromDPB(pHevcCtx, pos);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_ERROR,"%s call HEVC_OutputOneFrmFromDPB failed\n", __func__);   
        return HEVC_DEC_ERR;
    }

    return HEVC_DEC_NORMAL;
}


VOID HEVC_RecoverDPBProcess(HEVC_CTX_S *pHevcCtx)
{ 
    SINT32 ret;
    
    //检测DPB size是否能容纳当前帧，否则需要查看是否允许动态递增
    while(pHevcCtx->DPB.used_size >= pHevcCtx->DPB.size)
    {
        dprint(PRN_REF,"%s: DPB.used_size(%d) >= DPB.size(%d), need to increase DPB size.\n",__func__, pHevcCtx->DPB.used_size, pHevcCtx->DPB.size);
        ret = HEVC_IncreaseDPBSize(pHevcCtx);
        if (ret != HEVC_DEC_NORMAL)
        {
            dprint(PRN_ERROR,"%s call HEVC_IncreaseDPBSize failed\n", __func__);  
            break;
        }
    }
        
    //容错: 如DPB仍满，输出非参考帧中最小POC值的一帧，直到DPB有空闲允许当前帧解码
    while(pHevcCtx->DPB.used_size >= pHevcCtx->DPB.size)
    {
        dprint(PRN_ERROR,"%s: DPB.used_size(%d) >= DPB.size(%d), output minpoc frame.\n",__func__, pHevcCtx->DPB.used_size, pHevcCtx->DPB.size);
    
        ret = HEVC_OutputUnRefPicWithMinPoc(pHevcCtx);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_ERROR,"%s call HEVC_OutputOneFrmFromDPB failed\n", __func__);   
            HEVC_PrintDPBState(pHevcCtx);
            HEVC_ClearDPB(pHevcCtx);
            break;
        }
    }

    return;
}


SINT32 HEVC_RefPicProcess(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
	SINT32 iLostPoc;
    
	//清空填充的参考帧
	HEVC_RemoveDummyFrame(pHevcCtx);

    //检测所有帧存参考信息
    HEVC_ApplyReferencePictureSet(pHevcCtx);

    //补帧前先清除DPB不用的帧存
    HEVC_RemoveUnusedApcStore(pHevcCtx);
    ret = HEVC_RemoveUnUsedFrameStore(pHevcCtx);
    if(HEVC_TRUE != ret)
    {
        /* need do nothing */
    }
   
    //检测是否丢失参考帧
	while (0 == HEVC_CheckThatAllRefPicsAreAvailable(pHevcCtx, &iLostPoc))
	{
        dprint(PRN_ERROR,"Ref frame(poc %d) lost.\n", iLostPoc);   
        //如丢失，补充参考帧

		if (pHevcCtx->pstExtraData->s32OutErrThr != 0)
		{
		   ret = HEVC_CreateLostPicture(pHevcCtx, iLostPoc);
           if (HEVC_DEC_NORMAL != ret)
           {
	           HEVC_RemoveDummyFrame(pHevcCtx); 
               return HEVC_DEC_ERR;
           }		
		}
		else
		{
		    dprint(PRN_ERROR,"s32OutErrThr = %d,drop poc %d because lost ref frame(pod %d)\n",
				pHevcCtx->pstExtraData->s32OutErrThr,pHevcCtx->CurrSlice.poc, iLostPoc); 
		    return HEVC_DEC_ERR;
		}
    }

    //更新参考帧列表信息(长期参考帧，前向参考，后向参考)
    HEVC_UpdateReflist(pHevcCtx);
    HEVC_UpdateLTReflist(pHevcCtx);

    //检测DPB状态，进行错误纠正
    HEVC_RecoverDPBProcess(pHevcCtx);
    
    return HEVC_DEC_NORMAL;
}       


VOID HEVC_PicTypeStatistic(HEVC_CTX_S *pHevcCtx)
{
    /* 如是6种特定nal unit中的一种，则该帧直接指定为I Frame，
       同时将当前帧的nal_unit_type指定为该类型 */
    if (1 == HEVC_IsIUnit(pHevcCtx->CurrSlice.nal_unit_type))
    {
        pHevcCtx->CurrPic.nal_unit_type = pHevcCtx->CurrSlice.nal_unit_type;
        pHevcCtx->CurrPic.pic_type = HEVC_I_FRAME;
    }

    /* 判定pic_type: 如该帧有指定的五种nal_unit_type之一，
       强制设为I帧，不做判断。否则按以下优先级设定帧类型
       B slice > P slice > I slice */
    if (0 == (HEVC_IsIUnit(pHevcCtx->CurrPic.nal_unit_type)))
    {
        switch (pHevcCtx->CurrSlice.slice_type)
        {
            case HEVC_B_SLICE:
                pHevcCtx->CurrPic.pic_type = HEVC_B_FRAME;
                break;
            case HEVC_P_SLICE:
                if (pHevcCtx->CurrPic.pic_type != HEVC_B_FRAME)
                {
                    pHevcCtx->CurrPic.pic_type = HEVC_P_FRAME;
                }
                break;
            case HEVC_I_SLICE:
                if (pHevcCtx->CurrPic.pic_type != HEVC_B_FRAME 
                 && pHevcCtx->CurrPic.pic_type != HEVC_P_FRAME)
                {
                    pHevcCtx->CurrPic.pic_type = HEVC_I_FRAME;
                }
                break;
            default:
                break;           
        }
    }
    
    return;
}


SINT32 HEVC_DecSlice(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;

#ifndef HEVC_SYNTAX_OPT
    SINT32 i;
    memset(&pHevcCtx->CurrSlice, 0, sizeof(HEVC_SLICE_SEGMENT_HEADER));
#endif
	pHevcCtx->CurrSlice.nal_unit_type   = pHevcCtx->pCurrNal->nal_unit_type;
	pHevcCtx->CurrSlice.nuh_temporal_id = pHevcCtx->pCurrNal->nuh_temporal_id;

    //清除bNewSequence标志
    pHevcCtx->bNewSequence = HEVC_FALSE;
    
    if(IS_NEW_PIC == pHevcCtx->CurrSlice.new_pic_type)
    {
        //检测是否需要输出DPB中所有帧存
        if (HEVC_IsFlushUnit(pHevcCtx->CurrSlice.nal_unit_type) || HEVC_IsPVRFlushPic(pHevcCtx))
        {
            //指示要刷出当前DPB中所有帧存
            ret = HEVC_FlushOutputFrmFromDPB(pHevcCtx);
            if (HEVC_DEC_NORMAL != ret)
            {
                dprint(PRN_ERROR,"%s call HEVC_FlushOutputFrmFromDPB failed\n", __func__);   
                return HEVC_DEC_ERR;
            }
        }
        
        //检测是否需要清空DPB中所有帧存
        if (HEVC_TRUE == pHevcCtx->bNoOutputOfPriorPicsFlag)
        {
            if (pHevcCtx->DPB.used_size)
            {
                ret = HEVC_EmptyFrmFromDPB(pHevcCtx);
                if (HEVC_DEC_NORMAL != ret)
                {
                    dprint(PRN_ERROR,"%s call HEVC_EmptyFrmFromDPB failed\n", __func__);   
                    return HEVC_DEC_ERR;
                }
            }
        }
        
        pHevcCtx->TotalPicNum++;
        
        /* 在非I帧解码模式下，先检测DPB状态，进行补参考帧/递增DPB SIZE等动作 */
        if (I_MODE != pHevcCtx->pstExtraData->s32DecMode)
        {
            if (DEC_ORDER_SIMPLE_DPB == pHevcCtx->pstExtraData->s32DecOrderOutput)
            {
                /* 更新参考帧列表信息(长期参考帧，前向参考，后向参考) */
                HEVC_UpdateReflist(pHevcCtx);
                HEVC_UpdateLTReflist(pHevcCtx);
            }
            else
            {
                ret = HEVC_RefPicProcess(pHevcCtx);
                if (HEVC_DEC_NORMAL != ret)
                {
                    return HEVC_DEC_ERR;
                }
            }
        }
        
        ret = HEVC_InitPic(pHevcCtx);
        if(HEVC_NOTDEC == ret)
        {
            return HEVC_NOTDEC;
        }
        else if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_ERROR, "Init pic err, exit\n");
            return HEVC_DEC_ERR;
        }

        HEVC_SetScalingList(pHevcCtx);
		ret = HEVC_WritePicMsg(pHevcCtx);
        if (ret != HEVC_DEC_NORMAL)
        {
            dprint(PRN_ERROR, "HEVC_WritePicMsg failed!\n");
            return HEVC_DEC_ERR;
        }
    }
    
    // 容错: 防止当前消息池槽位已满溢出。
    if (pHevcCtx->NumSlicePara >= pHevcCtx->MaxSliceNum)
    {
        dprint(PRN_FATAL, "Start Reason: SliceParaNum= %d\n",  pHevcCtx->NumSlicePara);
        if (pHevcCtx->NumSlicePara >= pHevcCtx->MaxSliceNum)
        {
            REPORT_SLICE_NUM_OVER(pHevcCtx->ChanID, pHevcCtx->NumSlicePara, pHevcCtx->MaxSliceNum);
        }
        dprint(PRN_ERROR, "Too many slice , err!\n");
        HEVC_ClearCurrPic(pHevcCtx);
        return HEVC_DEC_ERR; 
    }

    // 容错: 如果该帧未正常走InitPic分配资源，该帧所有slice都应该丢弃不解。
    if (HEVC_PIC_EMPTY == pHevcCtx->CurrPic.state)
    {
        dprint(PRN_ERROR, "Cur pic not init yet, discard this slice!\n");
        return HEVC_DEC_ERR;
    }
    
    // 帧类型判断
    HEVC_PicTypeStatistic(pHevcCtx);
    
    // 码流信息计算
    HEVC_CalcStreamBits(pHevcCtx);
    
    //本来是写消息池的，现在先用全局数组代替
    if (IS_SKIP_PIC != pHevcCtx->CurrSlice.new_pic_type)
    {
        //not skip frame            
        //independent_slice ,一般为第一个slice 	
        if (!pHevcCtx->CurrSlice.dependent_slice_segment_flag)
        {
            // one slice one RefList    
        	// 在storePicInDpb中已经进行了参考帧管理
        	// 标记了DPB.fs_negative_ref  DPB.fs_positive_ref 
            ret = HEVC_DecList(pHevcCtx);
			if (HEVC_DEC_NORMAL != ret)
			{
				dprint(PRN_ERROR,"Dec List error, ret=%d\n", ret);
				return HEVC_DEC_ERR;
			}

			ret = HEVC_IsRefListWrong(pHevcCtx);
			if (HEVC_DEC_NORMAL != ret)
			{
                HEVC_PrintDPBState(pHevcCtx);
				dprint(PRN_ERROR, "Ref List is Wrong!\n");
				return HEVC_DEC_ERR;
            }

#ifndef HEVC_SYNTAX_OPT
            for (i = 0; i < pHevcCtx->CurrSlice.listXsize[0]; i++)
            {
                pHevcCtx->IsLongTerm[pHevcCtx->TotalSliceNum][0][i] = pHevcCtx->pListX[0][i]->is_long_term;
                pHevcCtx->ApcList[pHevcCtx->TotalSliceNum][0][i] = pHevcCtx->pListX[0][i]->frame_store->apc_idc;
            }

            for (i = 0; i < pHevcCtx->CurrSlice.listXsize[1]; i++)
            {
                pHevcCtx->IsLongTerm[pHevcCtx->TotalSliceNum][1][i] = pHevcCtx->pListX[1][i]->is_long_term;
                pHevcCtx->ApcList[pHevcCtx->TotalSliceNum][1][i] = pHevcCtx->pListX[1][i]->frame_store->apc_idc;
            }
#endif
        }

        ret = HEVC_WriteSliceMsg(pHevcCtx);

        if (HEVC_DEC_NORMAL != ret)
		{
			dprint(PRN_ERROR, "HEVC_WriteSliceMsg err.\n");
			return HEVC_DEC_ERR;
		}	
    }
	else
	{
		// skip帧nal可以直接释放，否则 nal slot可能不足
		HEVC_ClearCurrNal(pHevcCtx);
	}
    
    pHevcCtx->prev_pic_parameter_set_id = pHevcCtx->CurrSlice.pic_parameter_set_id;
    pHevcCtx->prev_poc = pHevcCtx->CurrSlice.poc;
    pHevcCtx->AllowStartDec = 1;
    
    return HEVC_DEC_NORMAL;
}


UINT8 HEVC_IsReferenceNalu(HEVC_CTX_S *pHevcCtx)
{
    return (UINT8)(((pHevcCtx->CurrSlice.nal_unit_type <= NAL_UNIT_RESERVED_VCL_R15) && (pHevcCtx->CurrSlice.nal_unit_type % 2 != 0))
                   || ((pHevcCtx->CurrSlice.nal_unit_type >= NAL_UNIT_CODED_SLICE_BLA_W_LP) && (pHevcCtx->CurrSlice.nal_unit_type <= NAL_UNIT_RESERVED_IRAP_VCL23)));
}


/*!
************************************************************************
* 函数原型 : HEVC_DecSliceSegmentHeader(HEVC_CTX_S *pHevcCtx)
* 功能描述 : 解析slice信息，第二个参数决定是否对pHevcCtx->bNewSequence赋值
* 参数说明 : IsDecSlice 
             0 InquireSliceProperty Call 
             1 DecSlice Call
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_DecSliceSegmentHeader(HEVC_CTX_S *pHevcCtx)
{
	UINT32 RAPPicFlag=0, IDRPicFlag=0;
    SINT32 numCUs = 0, maxParts = 0, reqBitsOuter = 0, reqBitsInner = 0; /*numParts=0,*/
	UINT32 lcuAddress=0, innerAddress=0, sliceAddress=0, bitsForLongTermPicInSPS=0;
	UINT32 i=0, j=0, isSAOEnabled=0, isDBFEnabled=0;
    SINT32 numRpsCurrTempList=0, offset=0;
    SINT32 pocLsbLt=0, lt_idx_sps=0;
	SINT32 prevDeltaMSB=0, deltaPocMSBCycleLT=0;
	UINT32 MaxPocLsb=0, PocLsb=0, PocMsb=0;
	UINT32 PrePocLsb=0, PrePocMsb=0;
	SINT32 PocLTCurr=0;
    UINT32 MaxCollocatedRefIdx=0, MaxNumEntryPointOffsets=0;
	UINT32 numBits=0;
   	UINT32 ue=0;
	SINT32 ret=0;		
	SINT32 bitsLeft=0;
		
    
	HEVC_VIDEO_PARAM_SET_S  *pVPS = NULL;
	HEVC_SEQ_PARAM_SET_S    *pSPS = NULL;
	HEVC_PIC_PARAM_SET_S    *pPPS = NULL;
	HEVC_SHORT_TERM_RPSET_S *pRPS = NULL;

	pHevcCtx->CurrSlice.first_slice_segment_in_pic_flag = HEVC_u_v(pHevcCtx->pBS, 1, "first_slice_segment_in_pic_flag");

	RAPPicFlag = HEVC_GetRapPicFlag(pHevcCtx);
	IDRPicFlag = HEVC_GetIdrPicFlag(pHevcCtx);

	if (RAPPicFlag)
	{
	    pHevcCtx->CurrSlice.no_output_of_prior_pics_flag = HEVC_u_v(pHevcCtx->pBS, 1, "no_output_of_prior_pics_flag");
	}
    
	pHevcCtx->CurrSlice.pic_parameter_set_id = HEVC_ue_v(pHevcCtx->pBS, "slice_pic_parameter_set_id");
    if (pHevcCtx->CurrSlice.pic_parameter_set_id < 0 || pHevcCtx->CurrSlice.pic_parameter_set_id >= (pHevcCtx->MaxPpsNum)) 
	{
        dprint(PRN_ERROR, "%s: pic_parameter_set_id(%d) out of range(0 %d)!\n", __func__, pHevcCtx->CurrSlice.pic_parameter_set_id, pHevcCtx->MaxPpsNum);
        return HEVC_DEC_ERR;
	}

	if (HEVC_DEC_NORMAL != HEVC_VpsSpsPpsCheck(pHevcCtx))
	{
	    if (pHevcCtx->TotalSliceNum>0)
		{
		    pHevcCtx->CurrSlice.poc = pHevcCtx->LastSlicePoc;
		}
		else
		{
		    pHevcCtx->CurrSlice.poc = 0;
		}
		pHevcCtx->CurrSlice.new_pic_type = HEVC_IsNewPic(pHevcCtx);
		dprint(PRN_ERROR,"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\n");
	    return HEVC_DEC_ERR;
	}

	pPPS = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
	pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];
	pVPS = &pHevcCtx->pVPS[pSPS->video_parameter_set_id];

	if ((pPPS->dependent_slice_segments_enabled_flag) && (!pHevcCtx->CurrSlice.first_slice_segment_in_pic_flag))
	{
	    pHevcCtx->CurrSlice.dependent_slice_segment_flag = HEVC_u_v(pHevcCtx->pBS, 1, "dependent_slice_segment_flag");
	}
	else
	{
	    pHevcCtx->CurrSlice.dependent_slice_segment_flag = HEVC_FALSE;
	}

    if (0 == pSPS->max_cu_width || 0 == pSPS->max_cu_height)
    {
		dprint(PRN_ERROR,"max_cu_width(%d)/max_cu_height(%d) = 0\n", pSPS->max_cu_width, pSPS->max_cu_height);
	    return HEVC_DEC_ERR;
    }
    
	numCUs = ((pSPS->pic_width_in_luma_samples + pSPS->max_cu_width -1)/pSPS->max_cu_width)
		    *((pSPS->pic_height_in_luma_samples+ pSPS->max_cu_height-1)/pSPS->max_cu_height);
	maxParts = (1 << (pSPS->max_cu_depth << 1));

	while (numCUs > (1<<reqBitsOuter))
	{
	    reqBitsOuter++;
	}

    
#if 0

    while (numParts > (1 << reqBitsInner))
    {
        reqBitsInner++;
    }

#endif

	if (!pHevcCtx->CurrSlice.first_slice_segment_in_pic_flag)
	{
	   	pHevcCtx->CurrSlice.slice_segment_address = HEVC_u_v(pHevcCtx->pBS, reqBitsInner+reqBitsOuter, "slice_segment_address");
        if (pHevcCtx->CurrSlice.slice_segment_address < 0 || pHevcCtx->CurrSlice.slice_segment_address >= (pSPS->ctb_num_width)*(pSPS->ctb_num_height))
		{
			dprint(PRN_ERROR, "slice_segment_address(%d) out of range(0,%d).\n", pHevcCtx->CurrSlice.slice_segment_address, (pSPS->ctb_num_width)*(pSPS->ctb_num_height));
			return HEVC_DEC_ERR;			
		}
		lcuAddress   = pHevcCtx->CurrSlice.slice_segment_address >> reqBitsInner;
		innerAddress = pHevcCtx->CurrSlice.slice_segment_address - (lcuAddress << reqBitsInner);
	}
	sliceAddress = maxParts * lcuAddress + innerAddress;
	pHevcCtx->CurrSlice.dependent_slice_curstart_cuaddr = sliceAddress;
	pHevcCtx->CurrSlice.dependent_slice_curend_cuaddr   = numCUs * maxParts;
    pHevcCtx->CurrSlice.poc = pHevcCtx->LastSlicePoc;
	
	if (!pHevcCtx->CurrSlice.dependent_slice_segment_flag)
	{
	    for (i = 0; i < pPPS->num_extra_slice_header_bits; i++)
		{
		    ue = HEVC_u_v(pHevcCtx->pBS, 1, "slice_reserved_flag");
		}
        
	    pHevcCtx->CurrSlice.slice_type = HEVC_ue_v(pHevcCtx->pBS, "slice_type");
		if (pHevcCtx->CurrSlice.slice_type < 0 || pHevcCtx->CurrSlice.slice_type > 2)
		{
			dprint(PRN_ERROR, "slice_type(%d) out of range(0,2].\n", pHevcCtx->CurrSlice.slice_type);
			return HEVC_DEC_ERR;			
		}
		
		if (pPPS->output_flag_present_flag)
		{
		    pHevcCtx->CurrSlice.pic_output_flag = HEVC_u_v(pHevcCtx->pBS, 1, "pic_output_flag");
		}
		else
		{
		    pHevcCtx->CurrSlice.pic_output_flag = HEVC_TRUE;
		}
		if (!IDRPicFlag)
		{
			pHevcCtx->CurrSlice.pic_order_cnt_lsb = HEVC_u_v(pHevcCtx->pBS, pSPS->bits_for_poc, "pic_order_cnt_lsb");
			/* calc poc of current slice*/
			PocLsb = pHevcCtx->CurrSlice.pic_order_cnt_lsb;
            MaxPocLsb = 1 << pSPS->max_pic_order_cnt_lsb;
			PrePocLsb = pHevcCtx->PrevSlicePoc % MaxPocLsb;
			PrePocMsb = pHevcCtx->PrevSlicePoc - PrePocLsb;

			if ((PocLsb < PrePocLsb) && ((PrePocLsb - PocLsb) >= (MaxPocLsb / 2)))
			{
				PocMsb = PrePocMsb + MaxPocLsb;
			}
			else if ((PocLsb > PrePocLsb) && ((PocLsb - PrePocLsb) > (MaxPocLsb / 2)))
			{
				PocMsb = PrePocMsb - MaxPocLsb;
			}
			else
			{
				PocMsb = PrePocMsb;
			}
            
		    if (NAL_UNIT_CODED_SLICE_BLA_W_LP   == pHevcCtx->CurrSlice.nal_unit_type
             || NAL_UNIT_CODED_SLICE_BLA_W_RADL == pHevcCtx->CurrSlice.nal_unit_type
             || NAL_UNIT_CODED_SLICE_BLA_N_LP   == pHevcCtx->CurrSlice.nal_unit_type)
			{
				PocMsb = 0;
			}
			pHevcCtx->CurrSlice.poc = PocLsb + PocMsb;
			pHevcCtx->LastSlicePoc = pHevcCtx->CurrSlice.poc;

             if ((0 == pHevcCtx->CurrSlice.nuh_temporal_id) 
			 	&& (HEVC_IsReferenceNalu(pHevcCtx) && (pHevcCtx->CurrSlice.nal_unit_type != NAL_UNIT_CODED_SLICE_RASL_R) && (pHevcCtx->CurrSlice.nal_unit_type != NAL_UNIT_CODED_SLICE_RADL_R)))
			{
				pHevcCtx->CurrSlice.prev_poc = pHevcCtx->CurrSlice.poc;
				pHevcCtx->PrevSlicePoc = pHevcCtx->CurrSlice.poc;
			}
			     
			pHevcCtx->CurrSlice.short_term_ref_pic_set_sps_flag = HEVC_u_v(pHevcCtx->pBS, 1, "short_term_ref_pic_set_sps_flag");


			if (!pHevcCtx->CurrSlice.short_term_ref_pic_set_sps_flag)
			{
				ret = HEVC_DecShortTermRefPicSet(pHevcCtx,pSPS, &(pHevcCtx->CurrSlice.short_term_ref_pic_set), pSPS->num_short_term_ref_pic_sets);
				if (HEVC_DEC_NORMAL != ret)
				{
					dprint(PRN_ERROR, "SH HEVC_DecShortTermRefPicSet error.\n");
					return HEVC_DEC_ERR;
				}
			}
			else
			{
				while ((1u << numBits) < pSPS->num_short_term_ref_pic_sets)
				{
					numBits++;
				}
				if (numBits > 0)
				{
					pHevcCtx->CurrSlice.short_term_ref_pic_set_idx = HEVC_u_v(pHevcCtx->pBS,numBits, "short_term_ref_pic_set_idx"); 
				}
				else
				{
					pHevcCtx->CurrSlice.short_term_ref_pic_set_idx = 0;
				}
                if (pHevcCtx->CurrSlice.short_term_ref_pic_set_idx < 0 || pHevcCtx->CurrSlice.short_term_ref_pic_set_idx > pSPS->num_short_term_ref_pic_sets-1)
                {
					dprint(PRN_ERROR, "short_term_ref_pic_set_idx(%d) out of range[0,%d].\n", pHevcCtx->CurrSlice.short_term_ref_pic_set_idx, pSPS->num_short_term_ref_pic_sets - 1);
					return HEVC_DEC_ERR;
                }
				pHevcCtx->CurrSlice.short_term_ref_pic_set = pSPS->short_term_ref_pic_set[pHevcCtx->CurrSlice.short_term_ref_pic_set_idx];				
			}
			pRPS = &(pHevcCtx->CurrSlice.short_term_ref_pic_set);

			if (pSPS->long_term_ref_pics_present_flag)
			{
				offset = pRPS->num_negative_pics + pRPS->num_positive_pics;
                if (pSPS->num_long_term_ref_pic_sps > 0)
                {
                    pHevcCtx->CurrSlice.num_long_term_sps = HEVC_ue_v(pHevcCtx->pBS, "num_long_term_sps");

                    
                    if (pHevcCtx->CurrSlice.num_long_term_sps > pSPS->num_long_term_ref_pic_sps)
                    {
                        dprint(PRN_ERROR, "num_long_term_sps(%d) out of range[0,%d].\n", pHevcCtx->CurrSlice.num_long_term_sps, pSPS->num_long_term_ref_pic_sps);
                        return HEVC_DEC_ERR;
                    }
				}
				bitsForLongTermPicInSPS = 0;
				while (pSPS->num_long_term_ref_pic_sps > ((UINT32)(1<<bitsForLongTermPicInSPS)))
				{
				    bitsForLongTermPicInSPS++;
				}
				pHevcCtx->CurrSlice.num_long_term_pics = HEVC_ue_v(pHevcCtx->pBS, "num_long_term_pics");
				pRPS->num_of_longterm_pics = pHevcCtx->CurrSlice.num_long_term_sps + pHevcCtx->CurrSlice.num_long_term_pics;

                if ((pRPS->num_negative_pics + pRPS->num_positive_pics + pRPS->num_of_longterm_pics) > HEVC_MAX_NUM_REF_PICS)
                {
					dprint(PRN_ERROR, "SH ERROR: (num_negative_pics(%d) + num_positive_pics(%d) + num_of_longterm_pics(%d)) > %d\n", pRPS->num_negative_pics, pRPS->num_positive_pics, pRPS->num_of_longterm_pics, HEVC_MAX_NUM_REF_PICS);
					return HEVC_DEC_ERR;
                }
                
				for (i=0, j=offset+pRPS->num_of_longterm_pics-1; i<pRPS->num_of_longterm_pics; j--,i++)
				{
				    if (i < pHevcCtx->CurrSlice.num_long_term_sps)
				    {
				        lt_idx_sps = 0;
						if (bitsForLongTermPicInSPS)
						{
							pHevcCtx->CurrSlice.lt_idx_sps[i] = HEVC_u_v(pHevcCtx->pBS, bitsForLongTermPicInSPS, "lt_idx_sps");
							lt_idx_sps = pHevcCtx->CurrSlice.lt_idx_sps[i];
                            if (lt_idx_sps < 0 || lt_idx_sps > pSPS->num_long_term_ref_pic_sps-1)
                            {
            					dprint(PRN_ERROR, "lt_idx_sps[%d] = %d, but out of range[0,%d].\n", i, lt_idx_sps, pSPS->num_long_term_ref_pic_sps-1);
            					return HEVC_DEC_ERR;
                            }    
						}  
                        
						pocLsbLt = pSPS->lt_ref_pic_poc_lsb_sps[lt_idx_sps];
						pRPS->used_flag[j] = pSPS->used_by_curr_pic_lt_sps_flag[lt_idx_sps];
				    }
					else
					{
                        pHevcCtx->CurrSlice.poc_lsb_lt[i] = HEVC_u_v(pHevcCtx->pBS, pSPS->bits_for_poc, "poc_lsb_lt");
                        pocLsbLt = pHevcCtx->CurrSlice.poc_lsb_lt[i];
                        pHevcCtx->CurrSlice.used_by_curr_pic_lt_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "used_by_curr_pic_lt_flag");
                        pRPS->used_flag[j] = pHevcCtx->CurrSlice.used_by_curr_pic_lt_flag[i];
					}

				    pHevcCtx->CurrSlice.pocLsbLt[i] = pocLsbLt;
					pHevcCtx->CurrSlice.delta_poc_msb_present_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "delta_poc_msb_present_flag");
					if (pHevcCtx->CurrSlice.delta_poc_msb_present_flag[i])
					{
					   pHevcCtx->CurrSlice.delta_poc_msb_cycle_lt[i] = HEVC_ue_v(pHevcCtx->pBS, "delta_poc_msb_cycle_lt");
				       if (i==0 || i==pHevcCtx->CurrSlice.num_long_term_sps)  
				       {
				           deltaPocMSBCycleLT = pHevcCtx->CurrSlice.delta_poc_msb_cycle_lt[i];
				       }
				       else
				       {
				           deltaPocMSBCycleLT = pHevcCtx->CurrSlice.delta_poc_msb_cycle_lt[i] + prevDeltaMSB;
				       }
				       pHevcCtx->CurrSlice.deltaPocMSBCycleLT[j] = deltaPocMSBCycleLT;

				       pHevcCtx->CurrSlice.CheckLTMSB[j] = 1;
					}
				    else
				    {
				        deltaPocMSBCycleLT = (i==0 || i==pHevcCtx->CurrSlice.num_long_term_sps)?0:prevDeltaMSB;
				        pHevcCtx->CurrSlice.CheckLTMSB[j] = 0;
				    }
				    //prevLSB = pocLsbLt;
				    prevDeltaMSB = deltaPocMSBCycleLT;
				}
				
				for (i=0, j=offset+pRPS->num_of_longterm_pics-1; i<pRPS->num_of_longterm_pics; j--,i++)
                {
                    if (pHevcCtx->CurrSlice.delta_poc_msb_present_flag[i])
                    {
                        PocLTCurr = pHevcCtx->CurrSlice.poc - pHevcCtx->CurrSlice.deltaPocMSBCycleLT[j] * MaxPocLsb
                                    - PocLsb + pHevcCtx->CurrSlice.pocLsbLt[i];
                        pRPS->poc[j] = PocLTCurr;
						
                        pRPS->delta_poc[j] = PocLTCurr - pHevcCtx->CurrSlice.poc;                       
                    }
                    else
                    {
                        pRPS->poc[j] = pHevcCtx->CurrSlice.pocLsbLt[i];
                        pRPS->delta_poc[j] = pHevcCtx->CurrSlice.pocLsbLt[i] - pHevcCtx->CurrSlice.poc;
                    }
                }
				
				pRPS->num_of_pics = offset + pRPS->num_of_longterm_pics;
				if (pRPS->num_of_pics > HEVC_MAX_NUM_REF_PICS)
				{
					dprint(PRN_ERROR, "ERROR: pRPS->num_of_pics(%d) > %d.\n", pRPS->num_of_pics, HEVC_MAX_NUM_REF_PICS);
					return HEVC_DEC_ERR;
				}
			}
			if (pSPS->sps_temporal_mvp_enable_flag)
			{
			    pHevcCtx->CurrSlice.slice_temporal_mvp_enable_flag = HEVC_u_v(pHevcCtx->pBS, 1, "slice_temporal_mvp_enable_flag");
			}
			else
			{
			    pHevcCtx->CurrSlice.slice_temporal_mvp_enable_flag = HEVC_FALSE;
			}
		}
		else
		{
		    pHevcCtx->CurrSlice.poc = 0;
			pHevcCtx->LastSlicePoc = pHevcCtx->CurrSlice.poc;
			if (0 == pHevcCtx->CurrSlice.nuh_temporal_id)
			{
			    pHevcCtx->CurrSlice.prev_poc = 0;
			    pHevcCtx->PrevSlicePoc = 0;
			}
		}

		if (pSPS->sample_adaptive_offset_enabled_flag)
		{
		    pHevcCtx->CurrSlice.slice_sao_luma_flag = HEVC_u_v(pHevcCtx->pBS, 1, "slice_sao_luma_flag");
		    pHevcCtx->CurrSlice.slice_sao_chroma_flag = HEVC_u_v(pHevcCtx->pBS, 1, "slice_sao_chroma_flag");
		}
        
		if (IDRPicFlag)
		{
		    pHevcCtx->CurrSlice.slice_temporal_mvp_enable_flag = HEVC_FALSE;
		}
		
		if (pHevcCtx->CurrSlice.slice_type != HEVC_I_SLICE)
		{
		    pHevcCtx->CurrSlice.num_ref_idx_active_override_flag = HEVC_u_v(pHevcCtx->pBS, 1, "num_ref_idx_active_override_flag");
			if (pHevcCtx->CurrSlice.num_ref_idx_active_override_flag)
			{
			    pHevcCtx->CurrSlice.num_ref_idx_l0_active = HEVC_ue_v(pHevcCtx->pBS, "num_ref_idx_l0_active_minus1") + 1;

                
                if (pHevcCtx->CurrSlice.num_ref_idx_l0_active > HEVC_MAX_NUM_REF_PICS)
                {
                    dprint(PRN_ERROR, "num_ref_idx_l0_active(%d) out of range(0,%d).\n", pHevcCtx->CurrSlice.num_ref_idx_l0_active, HEVC_MAX_NUM_REF_PICS);
                    return HEVC_DEC_ERR;
                }

                pHevcCtx->CurrSlice.num_ref_idx[0] = pHevcCtx->CurrSlice.num_ref_idx_l0_active;

                if (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)
                {
                    pHevcCtx->CurrSlice.num_ref_idx_l1_active = HEVC_ue_v(pHevcCtx->pBS, "num_ref_idx_l1_active_minus1") + 1;

                    
                    if (pHevcCtx->CurrSlice.num_ref_idx_l1_active > HEVC_MAX_NUM_REF_PICS)
                    {
                        dprint(PRN_ERROR, "num_ref_idx_l1_active(%d) out of range(0,%d).\n", pHevcCtx->CurrSlice.num_ref_idx_l1_active, HEVC_MAX_NUM_REF_PICS);
                        return HEVC_DEC_ERR;
					}	
					pHevcCtx->CurrSlice.num_ref_idx[1] = pHevcCtx->CurrSlice.num_ref_idx_l1_active;
				}
				else
				{
				    pHevcCtx->CurrSlice.num_ref_idx_l1_active = 0;
					pHevcCtx->CurrSlice.num_ref_idx[1] = 0;
				}
			}
			else
			{
			    pHevcCtx->CurrSlice.num_ref_idx[0] = pPPS->num_ref_idx_l0_default_active;
				if (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)
				{
				    pHevcCtx->CurrSlice.num_ref_idx[1] = pPPS->num_ref_idx_l1_default_active;
				}
				else
				{
				    pHevcCtx->CurrSlice.num_ref_idx[1] = 0;
				}
			}
		}

		if (HEVC_I_SLICE == pHevcCtx->CurrSlice.slice_type)
		{
		    numRpsCurrTempList = 0;
		}
		else
		{
			if (pRPS == NULL)
			{
				dprint(PRN_ERROR, "pRPS is null.\n");
				return HEVC_DEC_ERR;			
			}
		
			if (pRPS->num_of_pics > HEVC_MAX_NUM_REF_PICS)
			{
				dprint(PRN_ERROR, "pRPS->num_of_pics out(%d) of range(0,%d).\n", pRPS->num_of_pics, HEVC_MAX_NUM_REF_PICS);
				return HEVC_DEC_ERR;		
			}
		
			for (i=0; i<pRPS->num_of_pics; i++)
			{
			    if (pRPS->used_flag[i])
			    {
			        numRpsCurrTempList++;
			    }
			}
		}
    
	    if (HEVC_I_SLICE != pHevcCtx->CurrSlice.slice_type)
	    {
	        if (pPPS->lists_modification_present_flag && numRpsCurrTempList>1)
	        {
	            ret = HEVC_DecRefPicListsModification(pHevcCtx,&pHevcCtx->CurrSlice, &(pHevcCtx->CurrSlice.ref_pic_lists_modification), numRpsCurrTempList);
				if (HEVC_DEC_NORMAL != ret)
				{
					dprint(PRN_ERROR, "SH HEVC_DecRefPicListsModification error.\n");
					return HEVC_DEC_ERR;
				}
	        }
	    }
	    if (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)
	    {
	        pHevcCtx->CurrSlice.mvd_l1_zero_flag = HEVC_u_v(pHevcCtx->pBS, 1, "mvd_l1_zero_flag");
	    }
		if ((HEVC_I_SLICE != pHevcCtx->CurrSlice.slice_type)&& (pPPS->cabac_init_present_flag))
		{
		    pHevcCtx->CurrSlice.cabac_init_flag = HEVC_u_v(pHevcCtx->pBS, 1, "cabac_init_flag");
		}
		if (pHevcCtx->CurrSlice.slice_temporal_mvp_enable_flag)
		{
		    if (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)
		    {
		        pHevcCtx->CurrSlice.collocated_from_l0_flag = HEVC_u_v(pHevcCtx->pBS, 1, "collocated_from_l0_flag");
		    }
			else
			{
			    pHevcCtx->CurrSlice.collocated_from_l0_flag = 1;
			}
			if ((HEVC_I_SLICE != pHevcCtx->CurrSlice.slice_type) &&
			    ((pHevcCtx->CurrSlice.collocated_from_l0_flag && (pHevcCtx->CurrSlice.num_ref_idx[0] > 1)) ||
			    (!pHevcCtx->CurrSlice.collocated_from_l0_flag && (pHevcCtx->CurrSlice.num_ref_idx[1] > 1))))
			{
			    pHevcCtx->CurrSlice.collocated_ref_idx = HEVC_ue_v(pHevcCtx->pBS, "collocated_ref_idx");

                if (pHevcCtx->CurrSlice.collocated_from_l0_flag)
                {
                    MaxCollocatedRefIdx = pHevcCtx->CurrSlice.num_ref_idx_l0_active - 1;
                }
                else
                {
                    MaxCollocatedRefIdx = pHevcCtx->CurrSlice.num_ref_idx_l1_active - 1;
                }
				if (pHevcCtx->CurrSlice.collocated_ref_idx < 0 || pHevcCtx->CurrSlice.collocated_ref_idx > MaxCollocatedRefIdx)
				{
					dprint(PRN_ERROR, "collocated_from_l0_flag=%d, collocated_ref_idx(%d) out of range(0,%d).\n", pHevcCtx->CurrSlice.collocated_from_l0_flag, pHevcCtx->CurrSlice.collocated_ref_idx, MaxCollocatedRefIdx);
					return HEVC_DEC_ERR;					
				}
			}
		}
		if ((pPPS->weighted_pred_flag && (HEVC_P_SLICE == pHevcCtx->CurrSlice.slice_type)) ||
			(pPPS->weighted_bipred_flag && (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)))
		{
			
		    ret = HEVC_DecPredWeightTable(pHevcCtx);
			if (HEVC_DEC_NORMAL != ret)
			{
				dprint(PRN_ERROR, "SH HEVC_DecPredWeightTable error.\n");
				return HEVC_DEC_ERR;
			}
		}
       
		if (HEVC_I_SLICE != pHevcCtx->CurrSlice.slice_type)
		{
		    pHevcCtx->CurrSlice.max_num_merge_cand = MRG_MAX_NUM_CANDS - HEVC_ue_v(pHevcCtx->pBS, "five_minus_max_num_merge_cand");
			if (pHevcCtx->CurrSlice.max_num_merge_cand < 1 || pHevcCtx->CurrSlice.max_num_merge_cand > 5)
			{
				dprint(PRN_ERROR, "SH max_num_merge_cand(%d) out of range(1,5).\n", pHevcCtx->CurrSlice.max_num_merge_cand);
				return HEVC_DEC_ERR;
			}
		}
		pHevcCtx->CurrSlice.slice_qp_delta = HEVC_se_v(pHevcCtx->pBS, "slice_qp_delta");
		pHevcCtx->CurrSlice.slice_qp = pHevcCtx->CurrSlice.slice_qp_delta + pPPS->pic_init_qp;
		if (pHevcCtx->CurrSlice.slice_qp < (SINT32)(-pSPS->qp_bdOffset_y) || pHevcCtx->CurrSlice.slice_qp > 51)
		{
			dprint(PRN_ERROR, "SH slice_qp(%d) out of range [-%d,51].\n", pHevcCtx->CurrSlice.slice_qp, pSPS->qp_bdOffset_y);
			return HEVC_DEC_ERR;			
		}

		if (pPPS->pic_slice_chroma_qp_offsets_present_flag)
		{
		    pHevcCtx->CurrSlice.slice_cb_qp_offset = HEVC_se_v(pHevcCtx->pBS, "slice_cb_qp_offset");

			if (pHevcCtx->CurrSlice.slice_cb_qp_offset < -12 || pHevcCtx->CurrSlice.slice_cb_qp_offset > 12)
			{
				dprint(PRN_ERROR, "SH slice_cb_qp_offset(%d) out of range[-12,12].\n", pHevcCtx->CurrSlice.slice_cb_qp_offset);
				return HEVC_DEC_ERR;
			}

			if ((pHevcCtx->CurrSlice.slice_cb_qp_offset + pPPS->pic_cb_qp_offset) < -12 ||
				(pHevcCtx->CurrSlice.slice_cb_qp_offset + pPPS->pic_cb_qp_offset) > 12)
			{
				dprint(PRN_ERROR, "SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out of range[-12,12].\n", pHevcCtx->CurrSlice.slice_cb_qp_offset, pPPS->pic_cb_qp_offset);
				return HEVC_DEC_ERR;
			}
            
			pHevcCtx->CurrSlice.slice_cr_qp_offset = HEVC_se_v(pHevcCtx->pBS, "slice_cr_qp_offset");
			
			if (pHevcCtx->CurrSlice.slice_cr_qp_offset < -12 || pHevcCtx->CurrSlice.slice_cr_qp_offset > 12)
			{
				dprint(PRN_ERROR, "SH slice_cr_qp_offset(%d) out of range[-12,12].\n", pHevcCtx->CurrSlice.slice_cr_qp_offset);
				return HEVC_DEC_ERR;
			}

			if ((pHevcCtx->CurrSlice.slice_cr_qp_offset + pPPS->pic_cr_qp_offset) < -12 ||
				(pHevcCtx->CurrSlice.slice_cr_qp_offset + pPPS->pic_cr_qp_offset) > 12)
			{
				dprint(PRN_ERROR, "SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) out of range[-12,12].\n", (pHevcCtx->CurrSlice.slice_cr_qp_offset + pPPS->pic_cr_qp_offset));
				return HEVC_DEC_ERR;
			}
		}
        
		if (pPPS->deblocking_filter_control_present_flag)
		{
		    if (pPPS->deblocking_filter_override_enabled_flag)
		    {
		        pHevcCtx->CurrSlice.deblocking_filter_override_flag = HEVC_u_v(pHevcCtx->pBS, 1, "deblocking_filter_override_flag");
		    }
			else
			{
			    pHevcCtx->CurrSlice.deblocking_filter_override_flag = 0;
			}
			if (pHevcCtx->CurrSlice.deblocking_filter_override_flag)
			{
			    pHevcCtx->CurrSlice.slice_disable_deblocking_filter_flag = HEVC_u_v(pHevcCtx->pBS, 1, "slice_disable_deblocking_filter_flag");
				if (!pHevcCtx->CurrSlice.slice_disable_deblocking_filter_flag)
				{
				    pHevcCtx->CurrSlice.slice_beta_offset_div2 = HEVC_se_v(pHevcCtx->pBS, "slice_beta_offset_div2");
					if (pHevcCtx->CurrSlice.slice_beta_offset_div2 < -6 || pHevcCtx->CurrSlice.slice_beta_offset_div2 > 6)
					{
						dprint(PRN_ERROR, "SH slice_beta_offset_div2(%d) out of range(-6,6).\n", pHevcCtx->CurrSlice.slice_beta_offset_div2);
                        pHevcCtx->CurrSlice.slice_beta_offset_div2 = pPPS->pps_beta_offset_div2; // 赋值强解	
						//考虑钳位继续解
						//return HEVC_DEC_ERR;		
					}					
					pHevcCtx->CurrSlice.slice_tc_offset_div2 = HEVC_se_v(pHevcCtx->pBS, "slice_tc_offset_div2");
					if (pHevcCtx->CurrSlice.slice_tc_offset_div2  < -6 || pHevcCtx->CurrSlice.slice_tc_offset_div2  > 6)
					{
						dprint(PRN_ERROR, "SH slice_tc_offset_div2(%d) out of range(-6,6).\n", pHevcCtx->CurrSlice.slice_tc_offset_div2);
                        pHevcCtx->CurrSlice.slice_tc_offset_div2 = pPPS->pps_tc_offset_div2; // 赋值强解	
						// 考虑钳位继续解
						// return HEVC_DEC_ERR;			
					}					
				}
			}
			else
			{
			    pHevcCtx->CurrSlice.slice_disable_deblocking_filter_flag = pPPS->pic_disable_deblocking_filter_flag;
				pHevcCtx->CurrSlice.slice_beta_offset_div2 = pPPS->pps_beta_offset_div2;
				pHevcCtx->CurrSlice.slice_tc_offset_div2   = pPPS->pps_tc_offset_div2;
			}
		}
        
		isSAOEnabled = (!pSPS->sample_adaptive_offset_enabled_flag)? (HEVC_FALSE): (pHevcCtx->CurrSlice.slice_sao_luma_flag || pHevcCtx->CurrSlice.slice_sao_chroma_flag);
		isDBFEnabled = !(pHevcCtx->CurrSlice.slice_disable_deblocking_filter_flag);
		if (pPPS->loop_filter_across_slices_enabled_flag && (isSAOEnabled || isDBFEnabled))
		{
		    pHevcCtx->CurrSlice.slice_loop_filter_across_slices_enabled_flag = HEVC_u_v(pHevcCtx->pBS, 1, "slice_loop_filter_across_slices_enabled_flag");
		}
		else
		{
			pHevcCtx->CurrSlice.slice_loop_filter_across_slices_enabled_flag = pPPS->loop_filter_across_slices_enabled_flag;
		}
	}

	if (pPPS->tiles_enabled_flag || pPPS->entropy_coding_sync_enabled_flag)
	{
	    pHevcCtx->CurrSlice.num_entry_point_offsets = HEVC_ue_v(pHevcCtx->pBS, "num_entry_point_offsets");

        if (0 == pPPS->tiles_enabled_flag && 1 == pPPS->entropy_coding_sync_enabled_flag)
        {
            MaxNumEntryPointOffsets = pSPS->ctb_num_height - 1;
        }
        else if (1 == pPPS->tiles_enabled_flag && 0 == pPPS->entropy_coding_sync_enabled_flag)
        {
            MaxNumEntryPointOffsets = pPPS->num_tile_columns * pPPS->num_tile_rows - 1;
        }
        else
        {
            MaxNumEntryPointOffsets = pPPS->num_tile_columns * pSPS->ctb_num_height - 1;
        }

        if (pHevcCtx->CurrSlice.num_entry_point_offsets > MIN(MaxNumEntryPointOffsets, 255))
        {
			dprint(PRN_ERROR, "CurrSlice.num_entry_point_offsets(%d) out of range[0,%d].\n", pHevcCtx->CurrSlice.num_entry_point_offsets, MIN(MaxNumEntryPointOffsets, 255));
			return HEVC_DEC_ERR;
        }
        
		if (pHevcCtx->CurrSlice.num_entry_point_offsets > 0)
		{
		    pHevcCtx->CurrSlice.offset_len = 1 + HEVC_ue_v(pHevcCtx->pBS, "offset_len_minus1");
            if (pHevcCtx->CurrSlice.offset_len < 1 || pHevcCtx->CurrSlice.offset_len > 32)
            {
				dprint(PRN_ERROR, "CurrSlice.offset_len(%d) out of range[1,32].\n", pHevcCtx->CurrSlice.offset_len);
				return HEVC_DEC_ERR;
            }    
		}
		
		for (i=0; i<pHevcCtx->CurrSlice.num_entry_point_offsets; i++)
		{
		    pHevcCtx->CurrSlice.entry_point_offset[i] = HEVC_u_v(pHevcCtx->pBS, pHevcCtx->CurrSlice.offset_len, "entry_point_offset_minus1");
		}
	}
	else
	{
	    pHevcCtx->CurrSlice.num_entry_point_offsets = 0;
	}
    
	if (pPPS->slice_segment_header_extension_present_flag)
	{
	    pHevcCtx->CurrSlice.slice_segment_header_extension_length = HEVC_ue_v(pHevcCtx->pBS, "slice_segment_header_extension_length");
        if (pHevcCtx->CurrSlice.slice_segment_header_extension_length > 256 )
		{
			dprint(PRN_ERROR, "slice_segment_header_extension_length(%d) out of range [0,256]\n", pHevcCtx->CurrSlice.slice_segment_header_extension_length);
			return HEVC_DEC_ERR;
		}

		bitsLeft = BsResidBits(pHevcCtx->pBS);
		if (bitsLeft < pHevcCtx->CurrSlice.slice_segment_header_extension_length)
		{
			dprint(PRN_ERROR, "bitsLeft(%d) < slice_segment_header_extension_length(%d)\n",bitsLeft,pHevcCtx->CurrSlice.slice_segment_header_extension_length);
			return HEVC_DEC_ERR;
		}
        
		for (i=0; i<pHevcCtx->CurrSlice.slice_segment_header_extension_length; i++)
		{
		    pHevcCtx->CurrSlice.slice_segment_header_extension_data_byte = HEVC_u_v(pHevcCtx->pBS, 8, "slice_segment_header_extension_data_byte");
		}
	}
    
    if (pHevcCtx->CurrSlice.dependent_slice_curstart_cuaddr == 0)
    {
        if(pHevcCtx->bNewSequence)
        {
            if (RAPPicFlag)
            {
                pHevcCtx->bNoRaslOutputFlag = HEVC_TRUE;
            }
        }
        else
        {
            if (RAPPicFlag)
            {
                pHevcCtx->bNoRaslOutputFlag = HEVC_FALSE;
            }
        }
    } 
    
	if (pHevcCtx->bNoRaslOutputFlag && pHevcCtx->CurrSlice.poc != 0 && RAPPicFlag)
	{
	    if(pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_CRA)
	    {
	        pHevcCtx->bNoOutputOfPriorPicsFlag = HEVC_TRUE;
	    }
	    else
	    {
	        pHevcCtx->bNoOutputOfPriorPicsFlag = HEVC_FALSE;
	    }
	}
	else
	{
	    pHevcCtx->bNoOutputOfPriorPicsFlag = HEVC_FALSE;
	}
    
    pHevcCtx->CurrSlice.new_pic_type = HEVC_IsNewPic(pHevcCtx);
	ret = HEVC_ReadByteAlignment(pHevcCtx);
	if (HEVC_DEC_NORMAL != ret)
	{
		return HEVC_DEC_ERR;
	}
    
    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
* 函数原型 : SINT32 HEVC_WriteQmatrix_4x4()
* 功能描述 : 写ScalingList4x4
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
VOID HEVC_WriteQmatrix_4x4(UINT32 matrixId, HEVC_CTX_S *pHevcCtx,UINT32 Qmatrix[3*64])
{
    UINT32 tmp;
    
    //0,8,4,12
    tmp = (pHevcCtx->qmatrix[0][matrixId][12/4] & 0x000000FF)       << 24|\
              (pHevcCtx->qmatrix[0][matrixId][4/4] & 0x000000FF)        << 16|\
              (pHevcCtx->qmatrix[0][matrixId][8/4] & 0x000000FF)        << 8 |\
              (pHevcCtx->qmatrix[0][matrixId][0] & 0x000000FF);
    Qmatrix[0] = tmp;

     //1,9,5,13
    tmp = ((pHevcCtx->qmatrix[0][matrixId][13/4] & 0x0000FF00)>>8)       << 24|\
              ((pHevcCtx->qmatrix[0][matrixId][5/4] & 0x0000FF00)>>8)        << 16|\
              ((pHevcCtx->qmatrix[0][matrixId][9/4] & 0x0000FF00)>>8)        << 8 |\
              ((pHevcCtx->qmatrix[0][matrixId][1/4] & 0x0000FF00)>>8);
    Qmatrix[1] = tmp;

    //2,10,6,14
    tmp = ((pHevcCtx->qmatrix[0][matrixId][14/4] & 0x00FF0000)>>16)       << 24|\
              ((pHevcCtx->qmatrix[0][matrixId][6/4] & 0x00FF0000)>>16)        << 16|\
              ((pHevcCtx->qmatrix[0][matrixId][10/4] & 0x00FF0000)>>16)      << 8 |\
              ((pHevcCtx->qmatrix[0][matrixId][2/4] & 0x00FF0000)>>16);
    Qmatrix[2] = tmp;

    //3,11,7,15
    tmp = ((pHevcCtx->qmatrix[0][matrixId][15/4] & 0xFF000000)>>24)       << 24|\
              ((pHevcCtx->qmatrix[0][matrixId][7/4] & 0xFF000000)>>24)        << 16|\
              ((pHevcCtx->qmatrix[0][matrixId][11/4] & 0xFF000000)>>24)      << 8 |\
              ((pHevcCtx->qmatrix[0][matrixId][3/4] & 0xFF000000)>>24);
    Qmatrix[3] = tmp;

    return;
}


/*!
************************************************************************
* 函数原型 : SINT32 HEVC_WriteQmatrix_32x32()
* 功能描述 : 写ScalingList32x32
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
VOID HEVC_WriteQmatrix_32x32(UINT32 matrixId, HEVC_CTX_S *pHevcCtx,UINT32 Qmatrix[3*64])
{
    UINT32 tmp;
    
    //0,8,16,24
    tmp = (pHevcCtx->qmatrix[3][matrixId][24/4] & 0x000000FF)       << 24|\
              (pHevcCtx->qmatrix[3][matrixId][16/4] & 0x000000FF)       << 16|\
              (pHevcCtx->qmatrix[3][matrixId][8/4] & 0x000000FF)         << 8 |\
              (pHevcCtx->qmatrix[3][matrixId][0] & 0x000000FF);
    Qmatrix[0] = tmp;

    //32,40,48,56
    tmp = (pHevcCtx->qmatrix[3][matrixId][56/4] & 0x000000FF)       << 24|\
              (pHevcCtx->qmatrix[3][matrixId][48/4] & 0x000000FF)       << 16|\
              (pHevcCtx->qmatrix[3][matrixId][40/4] & 0x000000FF)       << 8 |\
              (pHevcCtx->qmatrix[3][matrixId][32/4] & 0x000000FF);
    Qmatrix[1] = tmp;

     //1,9,17,25
    tmp = ((pHevcCtx->qmatrix[3][matrixId][25/4] & 0x0000FF00)>>8)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][17/4] & 0x0000FF00)>>8)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][9/4] & 0x0000FF00)>>8)         << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][1/4] & 0x0000FF00)>>8);
    Qmatrix[2] = tmp;

    //33,41,49,57
    tmp = ((pHevcCtx->qmatrix[3][matrixId][57/4] & 0x0000FF00)>>8)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][49/4] & 0x0000FF00)>>8)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][41/4] & 0x0000FF00)>>8)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][33/4] & 0x0000FF00)>>8);
    Qmatrix[3] = tmp;

    //2,10,18,26
    tmp = ((pHevcCtx->qmatrix[3][matrixId][26/4] & 0x00FF0000)>>16)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][18/4] & 0x00FF0000)>>16)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][10/4] & 0x00FF0000)>>16)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][2/4] & 0x00FF0000)>>16);
    Qmatrix[4] = tmp;

    //24,42,50,58
    tmp = ((pHevcCtx->qmatrix[3][matrixId][58/4] & 0x00FF0000)>>16)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][50/4] & 0x00FF0000)>>16)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][42/4] & 0x00FF0000)>>16)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][34/4] & 0x00FF0000)>>16);
    Qmatrix[5] = tmp;

    //3,11,19,27
    tmp = ((pHevcCtx->qmatrix[3][matrixId][27/4] & 0xFF000000)>>24)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][19/4] & 0xFF000000)>>24)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][11/4] & 0xFF000000)>>24)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][3/4] & 0xFF000000)>>24);
    Qmatrix[6] = tmp;

    //35,43,51,59
    tmp = ((pHevcCtx->qmatrix[3][matrixId][59/4] & 0xFF000000)>>24)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][51/4] & 0xFF000000)>>24)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][43/4] & 0xFF000000)>>24)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][35/4] & 0xFF000000)>>24);
    Qmatrix[7] = tmp;

    //4,12,20,28
    tmp = (pHevcCtx->qmatrix[3][matrixId][28/4] & 0x000000FF)       << 24|\
              (pHevcCtx->qmatrix[3][matrixId][20/4] & 0x000000FF)       << 16|\
              (pHevcCtx->qmatrix[3][matrixId][12/4] & 0x000000FF)       << 8 |\
              (pHevcCtx->qmatrix[3][matrixId][4/4] & 0x000000FF);
    Qmatrix[8] = tmp;

    //36,44,52,60
    tmp = (pHevcCtx->qmatrix[3][matrixId][60/4] & 0x000000FF)       << 24|\
              (pHevcCtx->qmatrix[3][matrixId][52/4] & 0x000000FF)       << 16|\
              (pHevcCtx->qmatrix[3][matrixId][44/4] & 0x000000FF)       << 8 |\
              (pHevcCtx->qmatrix[3][matrixId][36/4] & 0x000000FF);
    Qmatrix[9] = tmp;

     //5,13,21,29
    tmp = ((pHevcCtx->qmatrix[3][matrixId][29/4] & 0x0000FF00)>>8)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][21/4] & 0x0000FF00)>>8)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][13/4] & 0x0000FF00)>>8)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][5/4] & 0x0000FF00)>>8);
    Qmatrix[10] = tmp;

    //37,45,53,61
    tmp = ((pHevcCtx->qmatrix[3][matrixId][61/4] & 0x0000FF00)>>8)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][53/4] & 0x0000FF00)>>8)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][45/4] & 0x0000FF00)>>8)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][37/4] & 0x0000FF00)>>8);
    Qmatrix[11] = tmp;

    //6,14,22,30
    tmp = ((pHevcCtx->qmatrix[3][matrixId][30/4] & 0x00FF0000)>>16)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][22/4] & 0x00FF0000)>>16)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][14/4] & 0x00FF0000)>>16)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][6/4] & 0x00FF0000)>>16);
    Qmatrix[12] = tmp;

    //38,46,54,62
    tmp = ((pHevcCtx->qmatrix[3][matrixId][62/4] & 0x00FF0000)>>16)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][54/4] & 0x00FF0000)>>16)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][46/4] & 0x00FF0000)>>16)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][38/4] & 0x00FF0000)>>16);
    Qmatrix[13] = tmp;

    //7,15,23,31
    tmp = ((pHevcCtx->qmatrix[3][matrixId][31/4] & 0xFF000000)>>24)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][23/4] & 0xFF000000)>>24)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][15/4] & 0xFF000000)>>24)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][7/4] & 0xFF000000)>>24);
    Qmatrix[14] = tmp;

    //39,47,55,63
    tmp = ((pHevcCtx->qmatrix[3][matrixId][63/4] & 0xFF000000)>>24)       << 24|\
              ((pHevcCtx->qmatrix[3][matrixId][55/4] & 0xFF000000)>>24)       << 16|\
              ((pHevcCtx->qmatrix[3][matrixId][47/4] & 0xFF000000)>>24)       << 8 |\
              ((pHevcCtx->qmatrix[3][matrixId][39/4] & 0xFF000000)>>24);
    Qmatrix[15] = tmp;

    return;
}


/*!
 ************************************************************************
 * 函数原型 : HEVC_WriteQmatrix_8x8
 * 功能描述 :  写ScalingList8x8
 * 参数说明 : 
 * 返回值   ： 
 ************************************************************************
 */
VOID HEVC_WriteQmatrix_8x8(UINT32 matrixId, HEVC_CTX_S *pHevcCtx,UINT32 Qmatrix[3*64])
{
    UINT32 tmp;
    
    //0,16,32,48
    tmp =   (pHevcCtx->qmatrix[1][matrixId][48/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[1][matrixId][32/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[1][matrixId][16/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[1][matrixId][0]  & 0x000000FF);
    Qmatrix[0] = tmp;

    //8,24,40,56
    tmp =   (pHevcCtx->qmatrix[1][matrixId][56/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[1][matrixId][40/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[1][matrixId][24/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[1][matrixId][8/4] & 0x000000FF);
    Qmatrix[1] = tmp;

    //1,17,33,49
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][49/4]& 0x0000FF00)>>8)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][33/4]& 0x0000FF00)>>8)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][17/4]& 0x0000FF00)>>8)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][1/4] & 0x0000FF00)>>8);
    Qmatrix[2] = tmp;

    //9,25,41,57
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][57/4]& 0x0000FF00)>>8)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][41/4]& 0x0000FF00)>>8)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][25/4]& 0x0000FF00)>>8)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][9/4] & 0x0000FF00)>>8);
    Qmatrix[3] = tmp;

    //2,18,34,50
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][50/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][34/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][18/4]& 0x00FF0000)>>16)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][2/4] & 0x00FF0000)>>16);
    Qmatrix[4] = tmp;

    //10,26,42,58
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][58/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][42/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][26/4]& 0x00FF0000)>>16)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][10/4] & 0x00FF0000)>>16);
    Qmatrix[5] = tmp;

    //3,19,35,51
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][51/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][35/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][19/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][3/4] & 0xFF000000)>>24);
    Qmatrix[6] = tmp;

    //11,27,43,59
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][59/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][43/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][27/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][11/4]& 0xFF000000)>>24);
    Qmatrix[7] = tmp;

    //4,20,36,52
    tmp =   (pHevcCtx->qmatrix[1][matrixId][52/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[1][matrixId][36/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[1][matrixId][20/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[1][matrixId][4/4] & 0x000000FF);
    Qmatrix[8] = tmp;

    //12,28,44,60
    tmp =   (pHevcCtx->qmatrix[1][matrixId][60/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[1][matrixId][44/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[1][matrixId][28/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[1][matrixId][12/4] & 0x000000FF);
    Qmatrix[9] = tmp;

    //5,21,37,53
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][53/4]& 0x0000FF00)>>8)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][37/4]& 0x0000FF00)>>8)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][21/4]& 0x0000FF00)>>8)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][5/4] & 0x0000FF00)>>8);
    Qmatrix[10] = tmp;

    //13,29,45,61
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][61/4]& 0x0000FF00)>>8)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][45/4]& 0x0000FF00)>>8)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][29/4]& 0x0000FF00)>>8)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][13/4] & 0x0000FF00)>>8);
    Qmatrix[11] = tmp;

    //6,22,38,54
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][54/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][38/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][22/4]& 0x00FF0000)>>16)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][6/4] & 0x00FF0000)>>16);
    Qmatrix[12] = tmp;

    //14,30,46,62
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][62/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][46/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][30/4]& 0x00FF0000)>>16)           << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][14/4] & 0x00FF0000)>>16);
    Qmatrix[13] = tmp;

    //7,23,39,55
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][55/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][39/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][23/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][7/4] & 0xFF000000)>>24);
    Qmatrix[14] = tmp;

    //15,31,47,63
    tmp =   ((pHevcCtx->qmatrix[1][matrixId][63/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[1][matrixId][47/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[1][matrixId][31/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[1][matrixId][15/4] & 0xFF000000)>>24);
    Qmatrix[15] = tmp;

    return;        
}


/*!
 ************************************************************************
 * 函数原型 : HEVC_WriteQmatrix_16x16
 * 功能描述 :  写ScalingList16x16
 * 参数说明 : 
 * 返回值   ： 
 ************************************************************************
 */
VOID HEVC_WriteQmatrix_16x16(UINT32 matrixId, HEVC_CTX_S *pHevcCtx,UINT32 Qmatrix[3*64])
{
    UINT32 tmp;
    
    //0,8,16,24
    tmp =   (pHevcCtx->qmatrix[2][matrixId][24/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[2][matrixId][16/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[2][matrixId][8/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[2][matrixId][0]  & 0x000000FF);
    Qmatrix[0] = tmp;

    //32,40,48,56
    tmp =   (pHevcCtx->qmatrix[2][matrixId][56/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[2][matrixId][48/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[2][matrixId][40/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[2][matrixId][32/4] & 0x000000FF);
    Qmatrix[1] = tmp;

    //1,9,17,25
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][25/4]& 0x0000FF00)>>8)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][17/4]& 0x0000FF00)>>8)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][9/4] & 0x0000FF00)>>8)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][1/4] & 0x0000FF00)>>8);
    Qmatrix[2] = tmp;

    //33,41,49,57
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][57/4]& 0x0000FF00)>>8)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][49/4]& 0x0000FF00)>>8)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][41/4]& 0x0000FF00)>>8)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][33/4] & 0x0000FF00)>>8);
    Qmatrix[3] = tmp;

    //2,10,18,26
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][26/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][18/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][10/4]& 0x00FF0000)>>16)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][2/4] & 0x00FF0000)>>16);
    Qmatrix[4] = tmp;

    //34,42,50,58
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][58/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][50/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][42/4]& 0x00FF0000)>>16)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][34/4]& 0x00FF0000)>>16);
    Qmatrix[5] = tmp;

    //3,11,19,27
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][27/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][19/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][11/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][3/4] & 0xFF000000)>>24);
    Qmatrix[6] = tmp;

    //35,43,51,59
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][59/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][51/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][43/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][35/4]& 0xFF000000)>>24);
    Qmatrix[7] = tmp;

    //4,12,20,28
    tmp =   (pHevcCtx->qmatrix[2][matrixId][28/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[2][matrixId][20/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[2][matrixId][12/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[2][matrixId][4/4] & 0x000000FF);
    Qmatrix[8] = tmp;

    //36,44,52,60
    tmp =   (pHevcCtx->qmatrix[2][matrixId][60/4]& 0x000000FF)            << 24| \
            (pHevcCtx->qmatrix[2][matrixId][52/4]& 0x000000FF)            << 16| \
            (pHevcCtx->qmatrix[2][matrixId][44/4]& 0x000000FF)            << 8 | \
            (pHevcCtx->qmatrix[2][matrixId][36/4] & 0x000000FF);
    Qmatrix[9] = tmp;

    //5,13,21,29
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][29/4]& 0x0000FF00)>>8)             << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][21/4]& 0x0000FF00)>>8)             << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][13/4]& 0x0000FF00)>>8)             << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][5/4] & 0x0000FF00)>>8);
    Qmatrix[10] = tmp;

    //37,45,53,61
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][61/4]& 0x0000FF00)>>8)             << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][53/4]& 0x0000FF00)>>8)             << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][45/4]& 0x0000FF00)>>8)             << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][37/4]& 0x0000FF00)>>8);
    Qmatrix[11] = tmp;

    //6,14,22,30
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][30/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][22/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][14/4]& 0x00FF0000)>>16)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][6/4] & 0x00FF0000)>>16);
    Qmatrix[12] = tmp;

    //38,46,54,62
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][62/4]& 0x00FF0000)>>16)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][54/4]& 0x00FF0000)>>16)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][46/4]& 0x00FF0000)>>16)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][38/4]& 0x00FF0000)>>16);
    Qmatrix[13] = tmp;

    //7,15,23,31
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][31/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][23/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][15/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][7/4] & 0xFF000000)>>24);
    Qmatrix[14] = tmp;

    //39,47,55,63
    tmp =   ((pHevcCtx->qmatrix[2][matrixId][63/4]& 0xFF000000)>>24)            << 24| \
            ((pHevcCtx->qmatrix[2][matrixId][55/4]& 0xFF000000)>>24)            << 16| \
            ((pHevcCtx->qmatrix[2][matrixId][47/4]& 0xFF000000)>>24)            << 8 | \
            ((pHevcCtx->qmatrix[2][matrixId][39/4] & 0xFF000000)>>24);
    Qmatrix[15] = tmp;

    return;   
}


/*!
************************************************************************
* 函数原型 : SINT32 Hevc_CtbRsAddrToTsAddr()
* 功能描述 : 将ctb光栅扫描转化为TILE地址
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_CtbRsAddrToTsAddr(HEVC_CTX_S *pHevcCtx,SINT32 CtbAddrRs)
{
    SINT32 idx;
    SINT32 pic_width_in_ctb_y = 0;
    //SINT32 pic_height_in_ctb_y = 0;
    SINT32 tile_x, tile_y;
    SINT32 ctb_size_y;
    SINT32 TileWidthInCtb, TileHeightInCtb, AbsWidthInCtb, AbsHeightInCtb, TileCtbAddrInTS, NextTileCtbAddrInTS;
    SINT32 leftUpOfTilePosXInCtb = 0, leftUpOfTilePosYInCtb = 0, CtbAddrTs;
    HEVC_TILE_INFO_S pTileInfo;
    HEVC_PIC_SIZE_INFO_S pPicSizeInfo;

    if (pHevcCtx->pCurrPPS->tiles_enabled_flag)
    {
        pPicSizeInfo.pic_width_in_luma_sample = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
        pPicSizeInfo.pic_height_in_luma_sample = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;
        pPicSizeInfo.CtbSizeYLog2 = pHevcCtx->pCurrSPS->log2_ctb_sizeY;
        pPicSizeInfo.MinTbSizeLog2 = pHevcCtx->pCurrSPS->quadtree_tu_log2_min_size;
        //pPicSizeInfo.PicHeithtInCtb = pic_height_in_ctb_y; //(SINT32)ceil(pHevcCtx->CurrSPS.pic_width_in_luma_samples *1.0 / (1 << pHevcCtx->CurrSPS.log2_ctb_sizeY));
        pPicSizeInfo.PicWidthInCtb = pic_width_in_ctb_y;  //(SINT32)ceil(pHevcCtx->CurrSPS.pic_height_in_luma_samples *1.0 / (1 << pHevcCtx->CurrSPS.log2_ctb_sizeY));

        pTileInfo.num_tile_rows_minus1 = pHevcCtx->pCurrPPS->num_tile_rows - 1;
        pTileInfo.num_tile_columns_minus1 = pHevcCtx->pCurrPPS->num_tile_columns - 1;
        pTileInfo.uniform_spacing_flag = pHevcCtx->pCurrPPS->uniform_spacing_flag;

        for (idx = 0; idx <= pHevcCtx->pCurrPPS->num_tile_rows - 1; idx++)
        {
            pTileInfo.row_height_minus1[idx] = pHevcCtx->pCurrPPS->row_bd[idx] - 1;
        }

        for (idx = 0; idx <= pHevcCtx->pCurrPPS->num_tile_columns - 1; idx++)
        {
            pTileInfo.column_width_minus1[idx] = pHevcCtx->pCurrPPS->column_bd[idx] - 1;
        }

        ctb_size_y = (1 << pPicSizeInfo.CtbSizeYLog2);
        pic_width_in_ctb_y = pPicSizeInfo.pic_width_in_luma_sample / ctb_size_y + !!(pPicSizeInfo.pic_width_in_luma_sample % ctb_size_y);
        //pic_height_in_ctb_y = pPicSizeInfo.pic_height_in_luma_sample/ctb_size_y + !!(pPicSizeInfo.pic_height_in_luma_sample%ctb_size_y);

        TileCtbAddrInTS = 0;
        NextTileCtbAddrInTS = 0;
        TileWidthInCtb = 0;
        TileHeightInCtb = 0;

        AbsWidthInCtb = CtbAddrRs % pic_width_in_ctb_y;
        AbsHeightInCtb = CtbAddrRs / pic_width_in_ctb_y;

        if (pTileInfo.uniform_spacing_flag)
        {

            for (tile_y = 0; tile_y <= pTileInfo.num_tile_rows_minus1; tile_y++)
            {
                leftUpOfTilePosXInCtb = 0;

                for (tile_x = 0; tile_x <= pTileInfo.num_tile_columns_minus1; tile_x++)
                {
                    TileCtbAddrInTS = NextTileCtbAddrInTS;
                    TileWidthInCtb = pTileInfo.column_width_minus1[tile_x] + 1;
                    TileHeightInCtb = pTileInfo.row_height_minus1[tile_y] + 1;

                    NextTileCtbAddrInTS += TileWidthInCtb * TileHeightInCtb;

                    if ((leftUpOfTilePosXInCtb + TileWidthInCtb) > AbsWidthInCtb && (leftUpOfTilePosYInCtb + TileHeightInCtb) > AbsHeightInCtb)
                    {
                        break;
                    }

                    leftUpOfTilePosXInCtb += TileWidthInCtb;
                }

                if ((leftUpOfTilePosXInCtb + TileWidthInCtb) > AbsWidthInCtb && (leftUpOfTilePosYInCtb + TileHeightInCtb) > AbsHeightInCtb)
                {
                    break;
                }

                leftUpOfTilePosYInCtb += TileHeightInCtb;
            }
        }
        else
        {

            for (tile_y = 0; tile_y <= pTileInfo.num_tile_rows_minus1; tile_y++)
            {
                leftUpOfTilePosXInCtb = 0;

                for (tile_x = 0; tile_x <= pTileInfo.num_tile_columns_minus1; tile_x++)
                {
                    TileCtbAddrInTS = NextTileCtbAddrInTS;
                    TileWidthInCtb = pTileInfo.column_width_minus1[tile_x] + 1;
                    TileHeightInCtb = pTileInfo.row_height_minus1[tile_y] + 1;
                    NextTileCtbAddrInTS += TileWidthInCtb * TileHeightInCtb;

                    if ((leftUpOfTilePosXInCtb + TileWidthInCtb) > AbsWidthInCtb && (leftUpOfTilePosYInCtb + TileHeightInCtb) > AbsHeightInCtb)
                    {
                        break;
                    }

                    leftUpOfTilePosXInCtb += TileWidthInCtb;
                }

                if ((leftUpOfTilePosXInCtb + TileWidthInCtb) > AbsWidthInCtb && (leftUpOfTilePosYInCtb + TileHeightInCtb) > AbsHeightInCtb)
                {
                    break;
                }

                leftUpOfTilePosYInCtb += TileHeightInCtb;
            }
        }

        CtbAddrTs = (AbsWidthInCtb - leftUpOfTilePosXInCtb) + (AbsHeightInCtb - leftUpOfTilePosYInCtb) * TileWidthInCtb + TileCtbAddrInTS;
    }
    else
    {
        CtbAddrTs = CtbAddrRs;
    }

    return CtbAddrTs;
}


/*!
************************************************************************
* 函数原型 : SINT32 HEVC_CtbTsAddrToRsAddr()
* 功能描述 : 将ctbTILE地址转化为光栅扫描
* 参数说明 :
* 返回值   ：
************************************************************************
*/
SINT32 HEVC_CtbTsAddrToRsAddr(HEVC_CTX_S *pHevcCtx, SINT32 CtbAddrTs)
{
    SINT32 idx;
    SINT32 pic_width_in_ctb_y = 0;
    //SINT32 pic_height_in_ctb_y = 0;
    SINT32 tile_x, tile_y;
    SINT32 ctb_size_y;
    SINT32 TileWidthInCtb, TileHeightInCtb, AbsWidthInCtb, AbsHeightInCtb, TileCtbAddrInTS, NextTileCtbAddrInTS;
    SINT32 CtbAddrRs;
    HEVC_TILE_INFO_S pTileInfo;
    HEVC_PIC_SIZE_INFO_S pPicSizeInfo;

    if (pHevcCtx->pCurrPPS->tiles_enabled_flag)
    {

        pPicSizeInfo.pic_width_in_luma_sample = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
        pPicSizeInfo.pic_height_in_luma_sample = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;
        pPicSizeInfo.CtbSizeYLog2 = pHevcCtx->pCurrSPS->log2_ctb_sizeY;
        pPicSizeInfo.MinTbSizeLog2 = pHevcCtx->pCurrSPS->quadtree_tu_log2_min_size;
        //pPicSizeInfo.PicHeithtInCtb = pic_height_in_ctb_y; //(SINT32)ceil(pHevcCtx->CurrSPS.pic_width_in_luma_samples *1.0 / (1 << pHevcCtx->CurrSPS.log2_ctb_sizeY));
        pPicSizeInfo.PicWidthInCtb = pic_width_in_ctb_y;  //(SINT32)ceil(pHevcCtx->CurrSPS.pic_height_in_luma_samples *1.0 / (1 << pHevcCtx->CurrSPS.log2_ctb_sizeY));

        pTileInfo.num_tile_rows_minus1 = pHevcCtx->pCurrPPS->num_tile_rows - 1;
        pTileInfo.num_tile_columns_minus1 = pHevcCtx->pCurrPPS->num_tile_columns - 1;
        pTileInfo.uniform_spacing_flag = pHevcCtx->pCurrPPS->uniform_spacing_flag;

        for (idx = 0; idx <= pHevcCtx->pCurrPPS->num_tile_rows - 1; idx++)
        {
            pTileInfo.row_height_minus1[idx] = pHevcCtx->pCurrPPS->row_bd[idx] - 1;
        }

        for (idx = 0; idx <= pHevcCtx->pCurrPPS->num_tile_columns - 1; idx++)
        {
            pTileInfo.column_width_minus1[idx] = pHevcCtx->pCurrPPS->column_bd[idx] - 1;
        }

        ctb_size_y = (1 << pPicSizeInfo.CtbSizeYLog2);
        pic_width_in_ctb_y = pPicSizeInfo.pic_width_in_luma_sample / ctb_size_y + !!(pPicSizeInfo.pic_width_in_luma_sample % ctb_size_y);
        //pic_height_in_ctb_y = pPicSizeInfo.pic_height_in_luma_sample/ctb_size_y + !!(pPicSizeInfo.pic_height_in_luma_sample%ctb_size_y);

        TileCtbAddrInTS = 0;
        NextTileCtbAddrInTS = 0;
        TileWidthInCtb = 0;
        TileHeightInCtb = 0;
        AbsWidthInCtb = 0;
        AbsHeightInCtb = 0;

        for (tile_y = 0; tile_y <= pTileInfo.num_tile_rows_minus1; tile_y++)
        {
            AbsWidthInCtb = 0;

            for (tile_x = 0; tile_x <= pTileInfo.num_tile_columns_minus1; tile_x++)
            {
                TileCtbAddrInTS = NextTileCtbAddrInTS;
                TileWidthInCtb = pTileInfo.column_width_minus1[tile_x] + 1;
                TileHeightInCtb = pTileInfo.row_height_minus1[tile_y] + 1;

                NextTileCtbAddrInTS += TileWidthInCtb * TileHeightInCtb;

                if (NextTileCtbAddrInTS > CtbAddrTs)
                {
                    break;
                }

                AbsWidthInCtb += TileWidthInCtb;
            }

            if (NextTileCtbAddrInTS > CtbAddrTs)
            {
                break;
            }

            AbsHeightInCtb += TileHeightInCtb;
        }

        if (0 == TileWidthInCtb)
        {
            dprint(PRN_ERROR, "TileWidthInCtb is 0\n");
            return HEVC_DEC_ERR;
        }


        AbsWidthInCtb += (CtbAddrTs - TileCtbAddrInTS) % TileWidthInCtb;
        AbsHeightInCtb += (CtbAddrTs - TileCtbAddrInTS) / TileWidthInCtb;

        CtbAddrRs = AbsWidthInCtb + pic_width_in_ctb_y * AbsHeightInCtb;
    }
    else
    {
        CtbAddrRs = CtbAddrTs;
    }

    return CtbAddrRs;
}


//解码顺序到光栅顺序映射表
VOID HEVC_CalcTileMap(HEVC_CTX_S *pHevcCtx)
{
    SINT32 idx   = 0;
    SINT32 TileX = 0;
    SINT32 TileY = 0;
    UINT32 i,j;
    UINT32 TileIdxX,TileIdxY;
    UINT32 picWidthInCtb;

    memset(g_TsToRsMap, 0, sizeof(g_TsToRsMap));
    memset(g_IsDeced,   0, sizeof(g_IsDeced));
    memset(pHevcCtx->DecPicPara.TileGroup,0,sizeof(pHevcCtx->DecPicPara.TileGroup));
		
    pHevcCtx->DecPicPara.TileNum = 0;
    picWidthInCtb = pHevcCtx->pCurrSPS->ctb_num_width;

    for (TileIdxY = 0; TileIdxY < pHevcCtx->pCurrPPS->num_tile_rows; TileIdxY++)
    {
        TileX = 0;

        for (TileIdxX = 0; TileIdxX < pHevcCtx->pCurrPPS->num_tile_columns; TileIdxX++)
        {
            //需要添加下标越界处理
            pHevcCtx->DecPicPara.TileGroup[pHevcCtx->DecPicPara.TileNum][0] = idx;//本tile的起始tile地址

            for (i = 0; i < pHevcCtx->pCurrPPS->row_bd[TileIdxY]; i++)
            {
                for (j = 0; j < pHevcCtx->pCurrPPS->column_bd[TileIdxX]; j++)
                {
                    g_TsToRsMap[idx] = (TileY + i) * picWidthInCtb + TileX + j;
                    idx++;
                }
            }

            pHevcCtx->DecPicPara.TileGroup[pHevcCtx->DecPicPara.TileNum][1] = idx - 1; //本tile的结束tile地址
            pHevcCtx->DecPicPara.TileNum++;
            TileX += pHevcCtx->pCurrPPS->column_bd[TileIdxX];
        }

        TileY += pHevcCtx->pCurrPPS->row_bd[TileIdxY];
    }

    return;
}


/*!
************************************************************************
* 函数原型 : SINT32 HEVC_WritePicMsg()
* 功能描述 : 写消息池pic para
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_WritePicMsg(HEVC_CTX_S *pHevcCtx)
{
	SINT32 i, ret;
    FSP_LOGIC_FS_S *pstLogicFs = NULL;
	
    dprint(PRN_CTRL,"image_id=%d, pmv_idc=%d\n",pHevcCtx->CurrPic.fs_image.image_id,pHevcCtx->CurrPic.pmv_address_idc);
    dprint(PRN_DNMSG,"pic msg burst0:\n");

    pHevcCtx->DecPicPara.imgstride = pHevcCtx->CurrPic.fs_image.image_stride;
    pHevcCtx->DecPicPara.UVOffset = pHevcCtx->CurrPic.fs_image.chrom_phy_addr - pHevcCtx->CurrPic.fs_image.luma_phy_addr;
    pHevcCtx->DecPicPara.CurrPicImgIdc = pHevcCtx->CurrPic.fs_image.image_id;
    pHevcCtx->DecPicPara.CurrPicPmvIdc = pHevcCtx->CurrPic.pmv_address_idc;

    pHevcCtx->NumSlicePara = 0;
    pHevcCtx->DecPicPara.pFirstSlice = &(pHevcCtx->pDecSlicePara[0]);

    pHevcCtx->DecPicPara.strong_intra_smoothing_enabled_flag = pHevcCtx->pCurrSPS->sps_strong_intra_smoothing_enable_flag;
    pHevcCtx->DecPicPara.scaling_list_enabled_flag = pHevcCtx->pCurrSPS->scaling_list_enabled_flag ;
    pHevcCtx->DecPicPara.pcm_loop_filter_disabled_flag = pHevcCtx->pCurrSPS->pcm_loop_filter_disable_flag;
    pHevcCtx->DecPicPara.sample_adaptive_offset_enabled_flag = pHevcCtx->pCurrSPS->sample_adaptive_offset_enabled_flag;
    pHevcCtx->DecPicPara.amp_enabled_flag = pHevcCtx->pCurrSPS->amp_enabled_flag;
    pHevcCtx->DecPicPara.chroma_format_idc = pHevcCtx->pCurrSPS->chroma_format_idc;
    pHevcCtx->DecPicPara.pcm_enabled_flag = pHevcCtx->pCurrSPS->pcm_enabled_flag;
    pHevcCtx->DecPicPara.PicHightInCtbsYMinus1 = pHevcCtx->pCurrSPS->ctb_num_height - 1;
    pHevcCtx->DecPicPara.PicWidthInCtbsYMinus1 = pHevcCtx->pCurrSPS->ctb_num_width - 1;
    pHevcCtx->DecPicPara.ThisPoc = pHevcCtx->CurrPic.thispoc;
    pHevcCtx->DecPicPara.log2_parallel_merge_level_minus2 = pHevcCtx->pCurrPPS->log2_parallel_merge_level - 2;
    pHevcCtx->DecPicPara.weighted_bipred_flag = pHevcCtx->pCurrPPS->weighted_bipred_flag;
    pHevcCtx->DecPicPara.weighted_pred_flag = pHevcCtx->pCurrPPS->weighted_pred_flag;

    pHevcCtx->DecPicPara.max_transform_hierarchy_depth_inter = pHevcCtx->pCurrSPS->max_transform_hierarchy_depth_inter;
    pHevcCtx->DecPicPara.max_transform_hierarchy_depth_intra = pHevcCtx->pCurrSPS->max_transform_hierarchy_depth_intra;
    pHevcCtx->DecPicPara.Log2MinIpcmCbSizeY = pHevcCtx->pCurrSPS->pcm_log2_min_size;
    pHevcCtx->DecPicPara.Log2MaxIpcmCbSizeY = pHevcCtx->pCurrSPS->pcm_log2_max_size;
    pHevcCtx->DecPicPara.Log2MinTrafoSize = pHevcCtx->pCurrSPS->quadtree_tu_log2_min_size;
    pHevcCtx->DecPicPara.Log2MaxTrafoSize = pHevcCtx->pCurrSPS->quadtree_tu_log2_max_size;
    pHevcCtx->DecPicPara.MaxCuDepth = pHevcCtx->pCurrSPS->max_cu_depth;
    pHevcCtx->DecPicPara.Log2MinCbSizeY = pHevcCtx->pCurrSPS->log2_min_cb_sizeY;
    pHevcCtx->DecPicPara.CtbLog2SizeY = pHevcCtx->pCurrSPS->log2_ctb_sizeY;
    pHevcCtx->DecPicPara.QpBdOffsetC = pHevcCtx->pCurrSPS->qp_bdOffset_c;
    pHevcCtx->DecPicPara.QpBdOffsetY = pHevcCtx->pCurrSPS->qp_bdOffset_y;
    pHevcCtx->DecPicPara.PcmBitDepthC = pHevcCtx->pCurrSPS->pcm_bit_depth_chroma;
    pHevcCtx->DecPicPara.PcmBitDepthY = pHevcCtx->pCurrSPS->pcm_bit_depth_luma;
    pHevcCtx->DecPicPara.BitDepthC = pHevcCtx->pCurrSPS->bit_depth_chroma;
    pHevcCtx->DecPicPara.BitDepthY = pHevcCtx->pCurrSPS->bit_depth_luma;

    memcpy(pHevcCtx->DecPicPara.Apc2PocTable, pHevcCtx->APC.poc, sizeof(pHevcCtx->DecPicPara.Apc2PocTable));
    pHevcCtx->DecPicPara.pic_height_in_luma_samples = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;
    pHevcCtx->DecPicPara.pic_width_in_luma_samples = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
    ret = HEVC_CalcTileInfo(pHevcCtx, pHevcCtx->DecPicPara.TileId, pHevcCtx->DecPicPara.TilePosX, pHevcCtx->DecPicPara.TilePosY);

    if (ret != HEVC_DEC_NORMAL)
    {
        dprint(PRN_ERROR, "%s call HEVC_CalcTileInfo failed.\n", __func__);
        return HEVC_DEC_ERR;
    }

    //D60
    pHevcCtx->DecPicPara.loop_filter_across_tiles_enabled_flag = pHevcCtx->pCurrPPS->loop_filter_across_tiles_enabled_flag;
    pHevcCtx->DecPicPara.transform_skip_enabled_flag = pHevcCtx->pCurrPPS->transform_skip_enabled_flag;
    pHevcCtx->DecPicPara.sign_data_hiding_enabled_flag = pHevcCtx->pCurrPPS->sign_data_hiding_flag;
    pHevcCtx->DecPicPara.entropy_coding_sync_enabled_flag = pHevcCtx->pCurrPPS->entropy_coding_sync_enabled_flag;
    pHevcCtx->DecPicPara.uniform_spacing_flag = pHevcCtx->pCurrPPS->uniform_spacing_flag;
    pHevcCtx->DecPicPara.tiles_enabled_flag = pHevcCtx->pCurrPPS->tiles_enabled_flag;

    pHevcCtx->pCurrPPS->log2_min_cu_qp_delta_size = pHevcCtx->pCurrSPS->log2_ctb_sizeY - pHevcCtx->pCurrPPS->max_cu_qp_delta_depth;
    pHevcCtx->DecPicPara.Log2MinCuQpDeltaSize = pHevcCtx->pCurrPPS->log2_min_cu_qp_delta_size;
    pHevcCtx->DecPicPara.diff_cu_qp_delta_depth = pHevcCtx->pCurrPPS->diff_cu_qp_delta_depth;
    pHevcCtx->DecPicPara.cu_qp_delta_enabled_flag = pHevcCtx->pCurrPPS->cu_qp_delta_enabled_flag ;
    pHevcCtx->DecPicPara.transquant_bypass_enabled_flag = pHevcCtx->pCurrPPS->transquant_bypass_enable_flag;
    pHevcCtx->DecPicPara.constrained_intra_pred_flag = pHevcCtx->pCurrPPS->constrained_intra_pred_flag;
    pHevcCtx->DecPicPara.pps_cb_qp_offset = pHevcCtx->pCurrPPS->pic_cb_qp_offset;
    pHevcCtx->DecPicPara.pps_cr_qp_offset = pHevcCtx->pCurrPPS->pic_cr_qp_offset;
    pHevcCtx->DecPicPara.num_tile_rows_minus1 = pHevcCtx->pCurrPPS->num_tile_rows - 1;
    pHevcCtx->DecPicPara.num_tile_columns_minus1 = pHevcCtx->pCurrPPS->num_tile_columns - 1;

    pHevcCtx->DecPicPara.weighted_pred_flag = pHevcCtx->pCurrPPS->weighted_pred_flag;
    pHevcCtx->DecPicPara.weighted_bipred_flag = pHevcCtx->pCurrPPS->weighted_bipred_flag;

	/* 帧存以及PMV地址表/id，要用FSP提供的机制去做 */
	pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->CurrPic.frame_store->logic_fs_id);
	if (pstLogicFs == NULL)
	{
		dprint(PRN_ERROR,"logic frame id(=%d): get LogicFs error!\n", pHevcCtx->CurrPic.frame_store->logic_fs_id);
		return HEVC_DEC_ERR;
	}
	else if (pstLogicFs->pstDecodeFs == NULL || pstLogicFs->pstDispOutFs == NULL)
	{
		dprint(PRN_ERROR,"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n", pstLogicFs->pstDecodeFs, pstLogicFs->pstDispOutFs);
		return HEVC_DEC_ERR;
	}

	/* 帧存地址表以及当前帧帧存ID */
	FSP_GetDecFsAddrTab(pHevcCtx->ChanID, &pHevcCtx->DecPicPara.ImgSlotNum, (SINT32*)pHevcCtx->DecPicPara.ImgPhyAddr,(SINT32*)pHevcCtx->DecPicPara.LineNumPhyAddr);
	pHevcCtx->DecPicPara.CurrPicImgIdc = pstLogicFs->pstDecodeFs->PhyFsID;

	/* PMV地址表以及当前帧PMV ID */
	FSP_GetPmvAddrTab(pHevcCtx->ChanID, &pHevcCtx->DecPicPara.PmvSlotNum, (SINT32*)pHevcCtx->DecPicPara.PmvPhyAddr);
	pHevcCtx->DecPicPara.CurrPicPmvIdc = pHevcCtx->CurrPic.pmv_address_idc;
	pHevcCtx->DecPicPara.half_pmvblk_offset = pstLogicFs->HalfPmvOffset;

    /* 当前帧2D地址 */
    pHevcCtx->DecPicPara.CurrPicImg2DAddr = pstLogicFs->pstDispOutFs->PhyAddr;
    pHevcCtx->DecPicPara.ChromaOffset     = pstLogicFs->pstDispOutFs->ChromOffset;

    pHevcCtx->DecPicPara.ApcSize = pHevcCtx->APC.size;
    for (i = 0; i < pHevcCtx->APC.size; i++)
    {
        pHevcCtx->DecPicPara.Apc2Idc[i] = pHevcCtx->APC.idc[i];
    }
    
    /*burst 1*/
    //D0~D23 write ScalingList4x4
    for (i=0; i<4; i++)
    {
        HEVC_WriteQmatrix_8x8(i, pHevcCtx,  pHevcCtx->DecPicPara.Qmatrix + 16*i);
    }

    /*burst 2*/
    //D0~D31 write ScalingList8x8
    for (i=0; i<2; i++)
    {
        HEVC_WriteQmatrix_8x8(i+4, pHevcCtx,  pHevcCtx->DecPicPara.Qmatrix + 64*1 + 16*i);
    }

    //D32~D63 write ScalingList16x16
    for (i=0; i<2; i++)
    {
        HEVC_WriteQmatrix_16x16(i, pHevcCtx,  pHevcCtx->DecPicPara.Qmatrix + 64*1 + 32 + 16*i);
    }

    /*burst 3*/
    //D0~D63 write ScalingList16x16
    for (i=0; i<4; i++)
    {
        HEVC_WriteQmatrix_16x16(i+2, pHevcCtx,  pHevcCtx->DecPicPara.Qmatrix + 64*2 + 16*i);
    }


    /*burst 4*/
    //D0~D23 write ScalingList32x32 
    for (i=0; i<2; i++)
    {
        HEVC_WriteQmatrix_32x32(i, pHevcCtx,  pHevcCtx->DecPicPara.Qmatrix + 64*3 + 16*i);
    }

    //D24~D55 write ScalingList4x4
    for (i=0; i<6; i++)
    {
        HEVC_WriteQmatrix_4x4(i, pHevcCtx, pHevcCtx->DecPicPara.Qmatrix + 64*3 + 32 + 4*i);
    }

    //D56 write scalingListDC
    pHevcCtx->DecPicPara.Qmatrix[64*3 + 56] = 
                (pHevcCtx->scalingListDC[2][3]) << 24|\
                (pHevcCtx->scalingListDC[2][2]) << 16|\
                (pHevcCtx->scalingListDC[2][1]) << 8 |\
                (pHevcCtx->scalingListDC[2][0]);
    //D57 write scalingListDC
    pHevcCtx->DecPicPara.Qmatrix[64*3 + 57] = 
              (pHevcCtx->scalingListDC[3][1]) << 24|\
              (pHevcCtx->scalingListDC[3][0]) << 16|\
              (pHevcCtx->scalingListDC[2][5]) << 8 |\
              (pHevcCtx->scalingListDC[2][4]);

	pHevcCtx->DecPicPara.pmv_address_idc = pHevcCtx->CurrPic.pmv_address_idc;


	if (pHevcCtx->DecPicPara.tiles_enabled_flag>0)
	{
        //HEVC_CalcTileMap(pHevcCtx);
	}

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_CheckListX(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;
    UINT32 list0size, list1size;
    HEVC_SLICE_SEGMENT_HEADER  *pSlice = NULL;

    if (0 == pHevcCtx->CurrSlice.dependent_slice_segment_flag)
    {
        pSlice = &pHevcCtx->CurrSlice;
    }
    else
    {
        if (0 == pHevcCtx->bHaveIndependentSlice)
        {
            dprint(PRN_FATAL, "%s ERROR: bHaveIndependentSlice = 0\n\n", __func__);
            return HEVC_DEC_ERR;
        }
        pSlice = &pHevcCtx->IndependentSlice;
    }

    list0size = pSlice->listXsize[0];
    list1size = pSlice->listXsize[1];

    if (list0size >= HEVC_MAX_LIST_SIZE)
    {
        dprint(PRN_FATAL, "ListX ERROR: list0size >= %d\n", list0size, HEVC_MAX_LIST_SIZE);
        return HEVC_DEC_ERR;
    }
    if (list1size >= HEVC_MAX_LIST_SIZE)
    {
        dprint(PRN_FATAL, "ListX ERROR: list1size >= %d\n", list1size, HEVC_MAX_LIST_SIZE);
        return HEVC_DEC_ERR;
    }
    
    for (i=0;i<list0size;i++)
    {
        if (pHevcCtx->pListX[0][i] == NULL)
        {
            dprint(PRN_FATAL, "pListX[0][%d] = NULL\n", i);
            return HEVC_DEC_ERR;
        }
        if (pHevcCtx->pListX[0][i]->frame_store == NULL)
        {
            dprint(PRN_FATAL, "pListX[0][%d]->frame_store = NULL\n", i);
            return HEVC_DEC_ERR;
        }
    }
    
    for (i=0;i<list1size;i++)
    {
        if (pHevcCtx->pListX[1][i] == NULL)
        {
            dprint(PRN_FATAL, "pListX[1][%d] = NULL\n", i);
            return HEVC_DEC_ERR;
        }
        if (pHevcCtx->pListX[1][i]->frame_store == NULL)
        {
            dprint(PRN_FATAL, "pListX[1][%d]->frame_store = NULL\n", i);
            return HEVC_DEC_ERR;
        }
    }
    
    return HEVC_DEC_NORMAL;
}


/*!
 ************************************************************************
 * 函数原型 : HEVC_WriteQmatrix_16x16
 * 功能描述 :  写ScalingList16x16
 * 参数说明 : 
 * 返回值   ： 
 ************************************************************************
 */
SINT32 HEVC_WriteSliceMsg(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;
    UINT32 slot_num;
    SINT32 ColPicApc;
    UINT8 IsLowDelay = 1;
    UADDR Apc2MvAddr[HEVC_APC_SIZE];
    HEVC_DEC_SLICE_PARAM_S  *pCurrSlicePara = NULL;
    HEVC_DEC_PIC_PARAM_S *pCurrPicPara = NULL;
    SINT32 end_ctb_in_slice_tile = 0;

    if (HEVC_CheckListX(pHevcCtx) != HEVC_DEC_NORMAL)
    {
        //pHevcCtx->NumSlicePara--;
        //pHevcCtx->CurrMsgSlotNum--;
        //pHevcCtx->TotalSliceNum--;
        return HEVC_DEC_ERR;
    }

    if (pHevcCtx->NumSlicePara >= pHevcCtx->MaxSliceNum)
    {
        dprint(PRN_ERROR, "NumSlicePara(%d) >= MaxSliceNum(%d)\n", pHevcCtx->NumSlicePara, pHevcCtx->MaxSliceNum);
        //pHevcCtx->NumSlicePara--;
        //pHevcCtx->CurrMsgSlotNum--;
        //pHevcCtx->TotalSliceNum--;
        return HEVC_DEC_ERR;
    }

    pCurrSlicePara = &(pHevcCtx->pDecSlicePara[pHevcCtx->NumSlicePara]);
    pCurrPicPara = &pHevcCtx->DecPicPara;

    memset(pCurrSlicePara, 0, sizeof(HEVC_DEC_SLICE_PARAM_S));
    memset(Apc2MvAddr,     0, sizeof(Apc2MvAddr));

    pHevcCtx->NumSlicePara++;

    if (pHevcCtx->NumSlicePara < pHevcCtx->MaxSliceNum)
    {
        pCurrSlicePara->pNextSlice = &(pHevcCtx->pDecSlicePara[pHevcCtx->NumSlicePara]);       
    }
    else
    {
        pCurrSlicePara->pNextSlice = NULL;
    }

    // 需要更新, 计算是否是新的一帧图像时用到
    // 仅需要用到pic_parameter_set_id
    pHevcCtx->Slice[pHevcCtx->TotalSliceNum] = pHevcCtx->CurrSlice.pic_parameter_set_id;

    pHevcCtx->CurrMsgSlotNum++; 
	pHevcCtx->TotalSliceNum++;
    
    slot_num = pHevcCtx->CurrMsgSlotNum;
    pHevcCtx->pMsgSlot[slot_num].slice_type = pHevcCtx->CurrSlice.slice_type;

    /*burst 0*/
    //D0~D5
    for (i = pHevcCtx->pCurrNal->nal_used_segment; ((i < pHevcCtx->pCurrNal->nal_segment) && (i < 2)) ; i++)
    {
        pCurrSlicePara->bitsoffset[i] = pHevcCtx->pCurrNal->stream[i].bitsoffset;
        pCurrSlicePara->valid_bitlen[i] = pHevcCtx->pCurrNal->stream[i].valid_bitlen;
        pCurrSlicePara->bytespos[i] = pHevcCtx->pCurrNal->stream[i].bytespos;
    }
    
    for (i = pHevcCtx->pCurrNal->nal_segment; i < 2; i++)
    {
        pCurrSlicePara->bitsoffset[i] = 0;
        pCurrSlicePara->valid_bitlen[i] = 0;
        pCurrSlicePara->bytespos[i] = 0;
    }

    //D6
    if (0 == pHevcCtx->CurrSlice.dependent_slice_segment_flag)
    {
#ifndef HEVC_SYNTAX_OPT
        memset(pCurrSlicePara->IsLongTerm,0,sizeof(pCurrSlicePara->IsLongTerm));
        memset(pCurrSlicePara->Idx2Apc,0,sizeof(pCurrSlicePara->Idx2Apc));
#endif
        memcpy(&pHevcCtx->IndependentSlice,&pHevcCtx->CurrSlice,sizeof(HEVC_SLICE_SEGMENT_HEADER));
        pHevcCtx->bHaveIndependentSlice = 1;
    }
	
    for (i=0;i<pHevcCtx->IndependentSlice.listXsize[0];i++)
    {
		Apc2MvAddr[pHevcCtx->pListX[0][i]->frame_store->apc_idc] = pHevcCtx->DecPicPara.PmvPhyAddr[pHevcCtx->pListX[0][i]->frame_store->pmv_address_idc];
		pCurrSlicePara->IsLongTerm[0][i] = pHevcCtx->pListX[0][i]->is_long_term;
        pCurrSlicePara->Idx2Apc[0][i] = pHevcCtx->pListX[0][i]->frame_store->apc_idc;//本帧在APC数组中 的id(索引)
    }
    
    for (i=0;i<pHevcCtx->IndependentSlice.listXsize[1];i++)
    {
		Apc2MvAddr[pHevcCtx->pListX[1][i]->frame_store->apc_idc] = pHevcCtx->DecPicPara.PmvPhyAddr[pHevcCtx->pListX[1][i]->frame_store->pmv_address_idc];
		pCurrSlicePara->IsLongTerm[1][i] = pHevcCtx->pListX[1][i]->is_long_term;
        pCurrSlicePara->Idx2Apc[1][i] = pHevcCtx->pListX[1][i]->frame_store->apc_idc;
    }

	for (i=0;i<pHevcCtx->IndependentSlice.listXsize[0];i++)
    {
        if (pHevcCtx->CurrPic.thispoc < pHevcCtx->APC.poc[pCurrSlicePara->Idx2Apc[0][i]])
    	{   	
    		IsLowDelay = 0;
			break;
    	}
    }

	if(pHevcCtx->IndependentSlice.slice_type == HEVC_B_SLICE)
	{
		for (i=0;i<pHevcCtx->IndependentSlice.listXsize[1]&&IsLowDelay;i++)
	    {
	        if (pHevcCtx->CurrPic.thispoc < pHevcCtx->APC.poc[pCurrSlicePara->Idx2Apc[1][i]])
	    	{
	    		IsLowDelay = 0;
				break;
	    	}
	    }
	}
    
    pCurrSlicePara->IsLowDelay = IsLowDelay;
    pCurrSlicePara->dependent_slice_segment_flag = pHevcCtx->CurrSlice.dependent_slice_segment_flag;
	pCurrSlicePara->SliceQpY = pHevcCtx->IndependentSlice.slice_qp;
	pCurrSlicePara->cabac_init_flag = pHevcCtx->IndependentSlice.cabac_init_flag;
	pCurrSlicePara->IndependentSliceSegmentAddr = pHevcCtx->IndependentSlice.slice_segment_address;
	//D7
	if (pHevcCtx->IndependentSlice.slice_type==HEVC_B_SLICE && !pHevcCtx->IndependentSlice.collocated_from_l0_flag)
    {
        ColPicApc = pCurrSlicePara->Idx2Apc[REF_PIC_LIST_1][pHevcCtx->IndependentSlice.collocated_ref_idx];
    }
    else if ((pHevcCtx->IndependentSlice.slice_type==HEVC_B_SLICE && pHevcCtx->IndependentSlice.collocated_from_l0_flag) || pHevcCtx->IndependentSlice.slice_type==HEVC_P_SLICE)
    {
        ColPicApc = pCurrSlicePara->Idx2Apc[REF_PIC_LIST_0][pHevcCtx->IndependentSlice.collocated_ref_idx];
    }
	else
	{
		ColPicApc = 0;
	}
	pCurrSlicePara->ColPicApc = ColPicApc;
	pCurrSlicePara->collocated_ref_idx = pHevcCtx->IndependentSlice.collocated_ref_idx;
	pCurrSlicePara->collocated_from_l0_flag = pHevcCtx->IndependentSlice.collocated_from_l0_flag;
	pCurrSlicePara->MaxNumMergeCand = pHevcCtx->IndependentSlice.max_num_merge_cand;
	
	if (pHevcCtx->IndependentSlice.num_ref_idx[0] > 0)
	{
		pCurrSlicePara->num_ref_idx_l0_active_minus1 = pHevcCtx->IndependentSlice.num_ref_idx[0] - 1;
	}
	else
	{
		pCurrSlicePara->num_ref_idx_l0_active_minus1 = 0;
	}
	
	if (pHevcCtx->IndependentSlice.num_ref_idx[1] > 0)
	{
		pCurrSlicePara->num_ref_idx_l1_active_minus1 = pHevcCtx->IndependentSlice.num_ref_idx[1] - 1;
	}
	else
	{
		pCurrSlicePara->num_ref_idx_l1_active_minus1 = 0;
	}
	pCurrSlicePara->slice_temporal_mvp_enabled_flag = pHevcCtx->IndependentSlice.slice_temporal_mvp_enable_flag;
	pCurrSlicePara->mvd_l1_zero_flag = pHevcCtx->IndependentSlice.mvd_l1_zero_flag;
	pCurrSlicePara->listXsize[0] = pHevcCtx->IndependentSlice.listXsize[0];
	pCurrSlicePara->listXsize[1] = pHevcCtx->IndependentSlice.listXsize[1];
    pCurrSlicePara->SliceType = pHevcCtx->IndependentSlice.slice_type;
    //D8
	pCurrSlicePara->slice_segment_address = pHevcCtx->CurrSlice.slice_segment_address; 
    //D9
    pCurrSlicePara->SliceSegmentAddressX = pHevcCtx->CurrSlice.slice_segment_address % pHevcCtx->pCurrSPS->ctb_num_width;
    pCurrSlicePara->SliceSegmentAddressY = pHevcCtx->CurrSlice.slice_segment_address / pHevcCtx->pCurrSPS->ctb_num_width;
    //D10
    pCurrSlicePara->SliceSegmentTileAddress = HEVC_CtbRsAddrToTsAddr(pHevcCtx, pHevcCtx->CurrSlice.slice_segment_address);
    //D11
    pCurrSlicePara->slice_cb_qp_offset = pHevcCtx->IndependentSlice.slice_cb_qp_offset;
    pCurrSlicePara->slice_cr_qp_offset = pHevcCtx->IndependentSlice.slice_cr_qp_offset;
    //D12
    pCurrSlicePara->slice_tc_offset_div2 = pHevcCtx->IndependentSlice.slice_tc_offset_div2;
    pCurrSlicePara->slice_beta_offset_div2 = pHevcCtx->IndependentSlice.slice_beta_offset_div2;
    pCurrSlicePara->slice_sao_chroma_flag = pHevcCtx->IndependentSlice.slice_sao_chroma_flag;
    pCurrSlicePara->slice_sao_luma_flag = pHevcCtx->IndependentSlice.slice_sao_luma_flag;
    pCurrSlicePara->slice_deblocking_filter_disabled_flag = pHevcCtx->IndependentSlice.slice_disable_deblocking_filter_flag;
    pCurrSlicePara->slice_loop_filter_across_slices_enabled_flag = pHevcCtx->IndependentSlice.slice_loop_filter_across_slices_enabled_flag;

    /*burst 1 and burst 2*/
    //D13-22
    if ((pHevcCtx->pCurrPPS->weighted_pred_flag && (HEVC_P_SLICE == pHevcCtx->IndependentSlice.slice_type)) ||
        ((1 == pHevcCtx->pCurrPPS->weighted_bipred_flag) && (HEVC_B_SLICE == pHevcCtx->IndependentSlice.slice_type)))
    {
		pCurrSlicePara->luma_log2_weight_denom   = pHevcCtx->IndependentSlice.pred_weight_table.luma_log2_weight_denom;
		pCurrSlicePara->chroma_log2_weight_denom = pHevcCtx->IndependentSlice.pred_weight_table.chroma_log2_weight_denom;

        // list0
        memcpy(pCurrSlicePara->LumaWeightL0, pHevcCtx->IndependentSlice.pred_weight_table.LumaWeightL0, sizeof(pCurrSlicePara->LumaWeightL0));

        memcpy(pCurrSlicePara->luma_offset_l0, pHevcCtx->IndependentSlice.pred_weight_table.luma_offset_l0, sizeof(pCurrSlicePara->luma_offset_l0));

        memcpy(pCurrSlicePara->ChromaWeightL0, pHevcCtx->IndependentSlice.pred_weight_table.ChromaWeightL0, sizeof(pCurrSlicePara->ChromaWeightL0));

        memcpy(pCurrSlicePara->ChromaOffsetL0, pHevcCtx->IndependentSlice.pred_weight_table.ChromaOffsetL0, sizeof(pCurrSlicePara->ChromaOffsetL0));

        // list1
        if (HEVC_B_SLICE == pHevcCtx->IndependentSlice.slice_type)
        {
            memcpy(pCurrSlicePara->LumaWeightL1, pHevcCtx->IndependentSlice.pred_weight_table.LumaWeightL1, sizeof(pCurrSlicePara->LumaWeightL1));

            memcpy(pCurrSlicePara->luma_offset_l1, pHevcCtx->IndependentSlice.pred_weight_table.luma_offset_l1, sizeof(pCurrSlicePara->luma_offset_l1));

            memcpy(pCurrSlicePara->ChromaWeightL1, pHevcCtx->IndependentSlice.pred_weight_table.ChromaWeightL1, sizeof(pCurrSlicePara->ChromaWeightL1));

            memcpy(pCurrSlicePara->ChromaOffsetL1, pHevcCtx->IndependentSlice.pred_weight_table.ChromaOffsetL1, sizeof(pCurrSlicePara->ChromaOffsetL1));
        }

    }
	if (pHevcCtx->IndependentSlice.slice_temporal_mvp_enable_flag)
	{
		pCurrSlicePara->Apc2MvAddr = Apc2MvAddr[ColPicApc];	
	}

    pHevcCtx->pMsgSlot[slot_num].slice_nal = pHevcCtx->pCurrNal;
    pHevcCtx->pCurrNal = NULL;  

	if (pHevcCtx->DecPicPara.tiles_enabled_flag>0)
	{
		if (pHevcCtx->TotalSliceNum-1 == 0)
		{
			pHevcCtx->DecPicPara.SliceGroup[pHevcCtx->TotalSliceNum-1][0] = pCurrSlicePara->SliceSegmentTileAddress;
		}
		else
		{
			pHevcCtx->DecPicPara.SliceGroup[pHevcCtx->TotalSliceNum-2][1] = pCurrSlicePara->SliceSegmentTileAddress-1;
			pHevcCtx->DecPicPara.SliceGroup[pHevcCtx->TotalSliceNum-1][0] = pCurrSlicePara->SliceSegmentTileAddress;
		}
		
		pHevcCtx->DecPicPara.SliceGroup[pHevcCtx->TotalSliceNum-1][1] = (pHevcCtx->DecPicPara.PicWidthInCtbsYMinus1+1)*(pHevcCtx->DecPicPara.PicHightInCtbsYMinus1+1) - 1;;
	}

    //为BVT省内存，将TsToRsMap和TsToRsMap提取为公共变量，
    //他们在语法解析中赋值，但会在中断中使用,
    //将end_ctb_in_slice_raster计算提前到语法解析中，避免多线程出错
    if (pCurrPicPara->tiles_enabled_flag)
    {
        end_ctb_in_slice_tile = pCurrSlicePara->SliceSegmentTileAddress - 1;

        if (end_ctb_in_slice_tile >= 0 && end_ctb_in_slice_tile < HEVC_MAX_MB_NUM)
        {
            /*这个地方不能用g_TsToRsMap，因为在多个tile码流同时解码的时候会公用g_TsToRsMap，导致解码出错
               z00183560*/
            pCurrSlicePara->end_ctb_in_slice_raster = HEVC_CtbTsAddrToRsAddr(pHevcCtx, end_ctb_in_slice_tile);
            //        pCurrSlicePara->end_ctb_in_slice_raster = g_TsToRsMap[end_ctb_in_slice_tile];
        }
    }

    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
* 函数原型 : SINT32 HEVC_GetVirAddr()
* 功能描述 : 获取对应Dn_num所在行在消息池中的虚拟地址
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
UINT32 *HEVC_GetVirAddr(UINT32 Dn, UINT32 * pbaHEVC_se_vir_addr)
{
    return (pbaHEVC_se_vir_addr + Dn); // one line addr
}

/*!
************************************************************************
* 函数原型 : UINT32 HEVC_GetPhyAddr()
* 功能描述 :获取对应Dn_num所在行在消息池中的物理地址
* 参数说明 :
* 返回值   ：
************************************************************************
*/
UINT32 HEVC_GetPhyAddr(UINT32 Dn, UADDR base_phy_addr)
{
    return (base_phy_addr + Dn * 4); // one line addr
}


/*!
************************************************************************
* 函数原型 : SINT32 CfgVDMReg(HEVC_CTX_S *pHevcCtx)
* 功能描述 :  写消息池slice para中的poc
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_CfgVDMReg(HEVC_CTX_S *pHevcCtx)
{
    pHevcCtx->DecPicPara.NewPicFlag       = (0 == pHevcCtx->CurrPic.start_count);
    pHevcCtx->DecPicPara.stream_base_addr = pHevcCtx->CurrPic.stream_base_addr;
	pHevcCtx->DecPicPara.NumSlicePara     = pHevcCtx->NumSlicePara;
    
    return HEVC_DEC_NORMAL;
}

UINT8 HEVC_IsRefForCurrPic(HEVC_CTX_S *pHevcCtx)
{
	SINT32 i;
    UINT8 is_reference = 0;
	SINT32 CurPoc, RefPoc;
	SINT32 PocCycle;
	HEVC_SHORT_TERM_RPSET_S *pTempRps = NULL;
	HEVC_PIC_PARAM_SET_S    *pPPS     = NULL;
	HEVC_SEQ_PARAM_SET_S    *pSPS     = NULL;

    is_reference = 0;

    /* l00232354, 20141223, 在使用id之前，应该做一个有效值判断，否则会因错误而
       导致coredown的问题。
    */
    if ((pHevcCtx->CurrSlice.pic_parameter_set_id < 0) ||
        (pHevcCtx->CurrSlice.pic_parameter_set_id >= (pHevcCtx->MaxPpsNum)))
    {
        dprint(PRN_FATAL, "line:%d pic_parameter_set_id(%d) out of range(0,%d).\n",
               __LINE__, pHevcCtx->CurrSlice.pic_parameter_set_id, pHevcCtx->MaxPpsNum);
        return is_reference;
    }
    pPPS = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];

    /* l00232354, 20141223, 在使用id之前，应该做一个有效值判断，否则会因错误而
       导致coredown的问题。
    */
    if ((pPPS->seq_parameter_set_id < 0) ||
        (pPPS->seq_parameter_set_id >= (pHevcCtx->MaxSpsNum)))
    {
        dprint(PRN_FATAL, "line:%d seq_parameter_set_id(%d) out of range[0,%d].\n", __LINE__,
               pPPS->seq_parameter_set_id, pHevcCtx->MaxSpsNum);
        return is_reference;
    }

	pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];
	PocCycle = 1 << pSPS->max_pic_order_cnt_lsb;

	//根据pic 第一个slice Rps信息
	pTempRps = &(pHevcCtx->CurrSlice.short_term_ref_pic_set);


    //long-time
    for (i = pTempRps->num_negative_pics + pTempRps->num_positive_pics; i < pTempRps->num_of_pics; i++)
    {
        /* l00232354, 20141223, 在使用i之前，应该做一个有效值判断，否则会因错误而
           导致coredown的问题。
        */
        if (i >= HEVC_MAX_NUM_REF_PICS)
        {
            dprint(PRN_FATAL, "line:%d, i(%d) > Max(%d) num_of_pics %d\n", __LINE__,
                   i, HEVC_MAX_NUM_REF_PICS, pTempRps->num_of_pics);
            break;
        }

    	CurPoc = pHevcCtx->CurrPic.thispoc;
		RefPoc = pTempRps->poc[i];
		
        if(!pHevcCtx->CurrSlice.CheckLTMSB[i])
        {
            CurPoc = CurPoc % PocCycle;
            RefPoc = RefPoc % PocCycle;
        }
        
        if(CurPoc == RefPoc)
        {
            is_reference = 1;
            break;
        }
    }

    //short-time
    for (i = 0; i < (pTempRps->num_negative_pics + pTempRps->num_positive_pics); i++)
    {
        /* l00232354, 20141223, 在使用i之前，应该做一个有效值判断，否则会因错误而
           导致coredown的问题。
        */
        if (i > HEVC_MAX_NUM_REF_PICS)
        {
            dprint(PRN_FATAL, "line:%d, i(%d) > Max(%d)(neg%d + pos%d)\n", __LINE__, i,
                   (HEVC_MAX_NUM_REF_PICS + 1), pTempRps->num_negative_pics, pTempRps->num_positive_pics);
            break;
        }

        if (pHevcCtx->CurrPic.thispoc == (pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i]))
        {
            is_reference = 1;
            break;
		}
	}
	
	return is_reference;
}


/*!
************************************************************************
* 函数原型 : SINT32 DecVDM(HEVC_CTX_S *pHevcCtx)
* 功能描述 : 启动vdm解码
* 参J}K5Cw :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_DecVDM(HEVC_CTX_S *pHevcCtx)
{
     SINT32  Size; 
	 UINT32 IPBDecMode;
     VDEC_CHAN_STATE_S *pChanState = NULL;
	 UINT32 final_slot_num = pHevcCtx->CurrMsgSlotNum;

	 if (HEVC_SLICE_SLOT_START_NUM > final_slot_num)
	 {
        HEVC_ClearCurrPic(pHevcCtx);
        if (pHevcCtx->MaxBytesReceived > MAX_BYTES_START)
        {
            dprint(PRN_FATAL, "DecVDM no slice and needn't start VDM, but MaxBytesReceived exceed threshold!\n");
            return HEVC_BS_OVERFLOW_ERR;
        }
        else
        {
            dprint(PRN_FATAL, "DecVDM no slice and needn't start VDM\n");
            return HEVC_DEC_ERR;
        }
	 }
     
     /* 统计帧数 */
     pChanState = &pHevcCtx->pstExtraData->stChanState;
     pHevcCtx->TotalFrameNum++;
     pHevcCtx->TotalFrameNum = MAX(pHevcCtx->TotalFrameNum, pHevcCtx->OutputFrameNum); 
     pChanState->total_frame_num = pHevcCtx->TotalFrameNum;
     pChanState->error_frame_num = pHevcCtx->TotalFrameNum - pHevcCtx->OutputFrameNum;

     //计算当期帧参考标志
     pHevcCtx->CurrPic.is_ref_idc = HEVC_IsRefForCurrPic(pHevcCtx);
     
	 //clean up information, clean here for statistic err mb when not start vdm or reset
	 IPBDecMode = (pHevcCtx->AdvancedCfg & 0x70000) >> 16;    
	 if( (pHevcCtx->OldDecMode != IPBDecMode) 
      && (pHevcCtx->OldDecMode == I_MODE || pHevcCtx->OldDecMode == DISCARD_MODE) 
      && (IPBDecMode != I_MODE) 
      && (IPBDecMode == IP_MODE || IPBDecMode == IPB_MODE || IPBDecMode == DISCARD_B_BF_P_MODE) )
	 {
		 dprint(PRN_ERROR, "IPBDecMode Changed (%d -> %d)\n", pHevcCtx->OldDecMode, IPBDecMode);
		 pHevcCtx->OldDecMode = IPBDecMode;
		 HEVC_ClearCurrPic(pHevcCtx);
		 HEVC_ClearDPB(pHevcCtx);
		 return HEVC_DEC_ERR;  //DPB_ERR
	 }
 
	 pHevcCtx->OldDecMode = IPBDecMode;
 
	 switch (pHevcCtx->OldDecMode)
	 {
	 case DISCARD_MODE:
		 HEVC_ClearCurrPic(pHevcCtx);
		 HEVC_ClearDPB(pHevcCtx);
		 return HEVC_DEC_ERR;  //IDR_LOST
	 case I_MODE:
		 if (HEVC_I_FRAME != pHevcCtx->CurrPic.pic_type)
		 {
			 HEVC_ClearCurrPic(pHevcCtx);
			 return HEVC_DEC_ERR;
		 }
		 break;
	 case IP_MODE:
	 	 //不是参考帧的B帧，可以删除
		 if ( (HEVC_B_FRAME == pHevcCtx->CurrPic.pic_type) && (0 == pHevcCtx->CurrPic.is_ref_idc) )
		 {
			 HEVC_ClearCurrPic(pHevcCtx);
			 return HEVC_DEC_ERR;
		 }
		 break;
	 case IPB_MODE:
	 case DISCARD_B_BF_P_MODE:	  
	 default :
		 break;
	 }
 
	 if (0 == pHevcCtx->TotalSliceNum)
	 {
		 HEVC_ClearCurrPic(pHevcCtx);
		 return HEVC_DEC_ERR;
	 }

#if 0
	/* HEVC很多码流仅有IB帧，使能该特性会导致很多码流无法播放 */
    if (pHevcCtx->pstExtraData->s8SpecMode != 1)
    {
        /* 容错处理，但在回归标准码流时，5X6的码流有I后面紧接着可解的B帧，
        这样做会丢掉这些B帧，而导致后面校验出错，所以回归时不使能 */
        if ((DISCARD_B_BF_P_MODE == pHevcCtx->OldDecMode)
        && (HEVC_I_FRAME == pHevcCtx->CurrPic.pic_type))
        {
            pHevcCtx->bPPicFound = 0;
        }

        /* 丢帧前提: 1.当前帧为B帧，2.还未出现过P帧，3.解码模式为显示序，4.初始参数未使能B_before_P */
        if ( (HEVC_B_FRAME == pHevcCtx->CurrPic.pic_type) 
          && (0 == pHevcCtx->bPPicFound) 
          && (NOT_DEC_ORDER == pHevcCtx->pstExtraData->s32DecOrderOutput) 
          && (1 != g_allow_B_before_P)) 
        {
            dprint(PRN_ERROR, "Discard this B(poc=%d) befor P, is_ref_idc=%d.\n",pHevcCtx->CurrPic.thispoc, pHevcCtx->CurrPic.is_ref_idc);
            HEVC_ClearCurrPic(pHevcCtx);
            return HEVC_DEC_ERR;
        }
        else if (HEVC_P_FRAME == pHevcCtx->CurrPic.pic_type) 
        {
            pHevcCtx->bPPicFound = 1;
        }
    }
#else
/* 因为HEVC很多码流仅有IB帧，所以仅在DISCARD_B_BF_P_MODE模式下使能丢I帧后B帧特性 */
     if ((DISCARD_B_BF_P_MODE == pHevcCtx->OldDecMode)
      && (HEVC_I_FRAME == pHevcCtx->CurrPic.pic_type))
     {
         pHevcCtx->bPPicFound = 2;
     }
     
     /* 丢帧前提: 1.当前帧为B帧，2.还未出现过P帧，3.解码模式为显示序，4.初始参数未使能B_before_P */
     if ( (HEVC_B_FRAME == pHevcCtx->CurrPic.pic_type) 
       && (2 == pHevcCtx->bPPicFound) 
       && (NOT_DEC_ORDER == pHevcCtx->pstExtraData->s32DecOrderOutput) 
       && (1 != g_allow_B_before_P)) 
     {
         dprint(PRN_ERROR, "Discard this B(poc=%d) before P, is_ref_idc=%d.\n",pHevcCtx->CurrPic.thispoc, pHevcCtx->CurrPic.is_ref_idc);
         HEVC_ClearCurrPic(pHevcCtx);
         return HEVC_DEC_ERR;
     }
     else if (HEVC_P_FRAME == pHevcCtx->CurrPic.pic_type) 
     {
         pHevcCtx->bPPicFound = 1;
     }
#endif
	 
	 dprint(PRN_CTRL, "VDM start, TotalPicNum=%d.\n", pHevcCtx->TotalPicNum - 1);	

	 if (0 == pHevcCtx->NumSlicePara)
	 {
		 HEVC_ClearCurrPic(pHevcCtx);
		 dprint(PRN_FATAL, "%s no correct slice in the pic\n", __func__); 
		 return HEVC_DEC_ERR;
	 }
     
     HEVC_CfgVDMReg(pHevcCtx);
		 
	 if (pHevcCtx->TotalPicNum >= (START_FRAME+1))
	 {
		 // Start VDM
		 pHevcCtx->pHevcDecParam = &pHevcCtx->DecPicPara;
		 pHevcCtx->CurrPic.start_count++;

		 // 发现I帧, 上报事件
		 if (HEVC_I_FRAME == pHevcCtx->CurrPic.pic_type)
		 {		 
			 Size = HEVC_GetPicStreamSize(pHevcCtx);
			 REPORT_FIND_IFRAME(pHevcCtx->ChanID, Size);
		 }
	 }
     
     return HEVC_DEC_NORMAL;
}


SINT32 HEVC_InitPic(HEVC_CTX_S *pHevcCtx)
{
    UINT32 RerangeMemFlag;
    SINT32 ret;
    SINT32 PrevSpsId;
    SINT32 i, PicWidth, PicHeight, log2_ctb_sizeY;
    UINT32 ChromaFormat;
	FSP_PHY_FS_STORE_TYPE_E eStoreType;
    SINT32 dar;
    UINT32 PreBitdepthLuma, PreBitdepthChroma;
    HEVC_VIDEO_PARAM_SET_S *vps      = NULL;
    HEVC_SEQ_PARAM_SET_S   *sps      = NULL;
    HEVC_PIC_PARAM_SET_S   *pps      = NULL;
    FSP_PHY_FS_S           *pstDecFs = NULL;

    PrevSpsId = pHevcCtx->PrevSpsId;
    PicWidth  = pHevcCtx->PrevPicWidth;
    PicHeight = pHevcCtx->PrevPicHeight;
    log2_ctb_sizeY = pHevcCtx->Prev_log2_ctb_sizeY;
    PreBitdepthLuma = pHevcCtx->pCurrSPS->bit_depth_luma;
    PreBitdepthChroma = pHevcCtx->pCurrSPS->bit_depth_chroma;
    
	// 前面已经限制,不可能进入这个分支
    if (pHevcCtx->CurrSlice.pic_parameter_set_id < 0 || pHevcCtx->CurrSlice.pic_parameter_set_id >= (pHevcCtx->MaxPpsNum))
    {
        return HEVC_DEC_NORMAL;
    }
    
    pps = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
    sps = &pHevcCtx->pSPS[pps->seq_parameter_set_id];
    vps = &pHevcCtx->pVPS[sps->video_parameter_set_id];

    /*1 refresh vps, sps and pps*/
    if ((pHevcCtx->pCurrVPS->video_parameter_set_id != vps->video_parameter_set_id)
        || (vps->is_refresh) || (!pHevcCtx->AllowStartDec))
    {
        vps->is_refresh = 0;
        memcpy(&pHevcCtx->pVPS[pHevcCtx->MaxVpsNum - 1], vps, sizeof(HEVC_VIDEO_PARAM_SET_S));

        pHevcCtx->pCurrVPS = &pHevcCtx->pVPS[pHevcCtx->MaxVpsNum - 1];
    }

    if ((pHevcCtx->pCurrSPS->seq_parameter_set_id != sps->seq_parameter_set_id)
        || (sps->is_refresh) || (!pHevcCtx->AllowStartDec)
        || PicWidth != sps->pic_width_in_luma_samples || PicHeight != sps->pic_height_in_luma_samples
        || log2_ctb_sizeY != sps->log2_ctb_sizeY)
    {
        sps->is_refresh = 0;
        memcpy(&pHevcCtx->pSPS[pHevcCtx->MaxSpsNum - 1], sps, sizeof(HEVC_SEQ_PARAM_SET_S));
        pHevcCtx->pCurrSPS = &pHevcCtx->pSPS[pHevcCtx->MaxSpsNum - 1];
        pHevcCtx->PrevSpsId    = pHevcCtx->pCurrSPS->seq_parameter_set_id;
        pHevcCtx->PrevPicWidth = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
        pHevcCtx->PrevPicHeight = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;
        pHevcCtx->Prev_log2_ctb_sizeY = pHevcCtx->pCurrSPS->log2_ctb_sizeY;
    }

    if ((pHevcCtx->pCurrPPS->pic_parameter_set_id != pps->pic_parameter_set_id)
        || (pps->is_refresh) || (!pHevcCtx->AllowStartDec)
        || PicWidth != sps->pic_width_in_luma_samples || PicHeight != sps->pic_height_in_luma_samples
        || log2_ctb_sizeY != sps->log2_ctb_sizeY) //sps变了之后，pps也要随着改变
    {
        pps->is_refresh = 0;
		if (pps->tiles_enabled_flag)
		{
	        if (pps->uniform_spacing_flag)
	        {
	            for (i=0; i<pps->num_tile_columns; i++)
	            {
	                pps->column_bd[i] = (i+1)*sps->ctb_num_width/pps->num_tile_columns
	                                       -(i*sps->ctb_num_width)/pps->num_tile_columns;
	            }
	            for (i=0; i<pps->num_tile_rows; i++)
	            {
	                pps->row_bd[i] = (i+1)*sps->ctb_num_height/pps->num_tile_rows
	                                     -(i*sps->ctb_num_height)/pps->num_tile_rows;
	            }
	        }
	        else
	        {
	            pps->column_bd[pps->num_tile_columns-1] = sps->ctb_num_width;
	            for (i=0; i<pps->num_tile_columns-1; i++)
	            {
	                pps->column_bd[i] = pps->column_width[i];
	                pps->column_bd[pps->num_tile_columns-1] -= pps->column_bd[i];
	            }
	            pps->row_bd[pps->num_tile_rows-1] = sps->ctb_num_height;
	            for (i=0; i<pps->num_tile_rows-1; i++)
	            {
	                pps->row_bd[i] = pps->row_height[i];
	                pps->row_bd[pps->num_tile_rows-1] -= pps->row_bd[i];
	            }

	        }
		}
		else
		{
			pps->column_bd[0] = sps->ctb_num_width;
			pps->row_bd[0] = sps->ctb_num_height;
		}
		
        memcpy(&pHevcCtx->pPPS[pHevcCtx->MaxPpsNum - 1], pps, sizeof(HEVC_PIC_PARAM_SET_S));
        pHevcCtx->pCurrPPS = &pHevcCtx->pPPS[pHevcCtx->MaxPpsNum - 1];
    }
    
    if ((PrevSpsId != sps->seq_parameter_set_id)
        || (sps->dpbsize_changed) || (!pHevcCtx->AllowStartDec)
        || (PicWidth != sps->pic_width_in_luma_samples) || (PicHeight != sps->pic_height_in_luma_samples) || (1 == pHevcCtx->pstExtraData->s32WaitFsFlag))
    {
        RerangeMemFlag = HEVC_GetReRangeFlag(pHevcCtx, PicWidth, PicHeight, log2_ctb_sizeY);
        if ((RerangeMemFlag) || (1 == pHevcCtx->pstExtraData->s32WaitFsFlag))
        {
            HEVC_GetBackPicFromVOQueue(pHevcCtx);
            
            ret = HEVC_InitDPB(pHevcCtx, 1);
            if(HEVC_NOTDEC == ret)
            {
                return HEVC_NOTDEC;
            }
			else if (ret != HEVC_DEC_NORMAL)
			{
				dprint(PRN_ERROR,"HEVC_InitDPB error, return %d\n", ret);
				HEVC_ClearAll(pHevcCtx,0);
                return HEVC_DEC_ERR;
			}
        }
        else
        {
            ;//处理待定
        }
        sps->dpbsize_changed = 0;
    }
	
    /*2 分配帧存和PMV空间*/	
    ret = HEVC_AllocFrameStore(pHevcCtx);
    if (HEVC_DEC_NORMAL != ret)
    {
    	dprint(PRN_ERROR,"HEVC_AllocFrameStore error\n");
        return ret;
    }

    /*3 初始化当前解码图像的参数*/
    // pmv_address_idc,structure, *frame_store均在帧存分配函数中产生
    pHevcCtx->CurrPic.state = HEVC_PIC_DECODING;
    pHevcCtx->CurrPic.nal_unit_type   = pHevcCtx->CurrSlice.nal_unit_type;
    pHevcCtx->CurrPic.thispoc = pHevcCtx->CurrSlice.poc;
    pHevcCtx->CurrPic.frame_store->poc = pHevcCtx->CurrSlice.poc;

    pHevcCtx->CurrPic.stream_base_addr = 0xffffffff;
    pHevcCtx->CurrPic.pic_width  = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
    pHevcCtx->CurrPic.pic_height = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;
    pHevcCtx->CurrPic.pic_ctbs   = pHevcCtx->pCurrSPS->ctb_num_height * pHevcCtx->pCurrSPS->ctb_num_width;
    pHevcCtx->CurrPic.start_count  = 0;

    //PTS的处理还不能这么简单。暂时如此
    pHevcCtx->CurrPic.fs_image.PTS = pHevcCtx->pstExtraData->pts;
    pHevcCtx->CurrPic.fs_image.Usertag = pHevcCtx->pstExtraData->Usertag;
    pHevcCtx->CurrPic.fs_image.DispTime = pHevcCtx->pstExtraData->DispTime;
    pHevcCtx->CurrPic.fs_image.DispEnableFlag = pHevcCtx->pstExtraData->DispEnableFlag;
    pHevcCtx->CurrPic.fs_image.DispFrameDistance = pHevcCtx->pstExtraData->DispFrameDistance;
    pHevcCtx->CurrPic.fs_image.DistanceBeforeFirstFrame = pHevcCtx->pstExtraData->DistanceBeforeFirstFrame;
    pHevcCtx->CurrPic.fs_image.GopNum = pHevcCtx->pstExtraData->GopNum;
    pHevcCtx->pstExtraData->pts = (UINT64)(-1);

    pHevcCtx->CurrPic.fs_image.image_width      = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
    pHevcCtx->CurrPic.fs_image.image_height     = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;

    /*
	缺省值
	g_CurrPic.fs_image.format = 0x0  << 14	|
	0x2  << 12	|
	0x0  << 10	|
	0x2  << 8	|
	0x5  << 5	|
	0x0  << 2	|
	0x0;
	*/
    /* [1:0] frame_type: 00(I), 01(P), 10(B), 11(Reserved)*/
    /* [4:2] CSP:  000(YUV:4:2:0), 001(YUV:4:0:0), 010~111(Reserved)*/
    /* [7:5] Norm: 000(component), 001(PLA), 010(NTSC), 011(SECAM), 100(MAC), 101(Unspecified Video Format), 110~111(Reserved)*/
    /* [9:8] source_format: 00(progressive), 01(interlaced), 10(infered_progressive), 11(infered_interlaced)*/
    /* [11:10] field_valid_flag: 00(top_field invalid, bottom_field invalid), 01(top_field valid, bottom_field invalid), 
                                 10(top_field invalid, bottom_field valid), 11(top_field valid, bottom_field valid)*/
    /* [13:12]top_field_first: 00(bottom field first), 01(top field first), 10(un-know), 11(Reserved)*/
    /* [16:14] aspect_ratio: 000(unspecified), 001(4:3), 010(16:9), 011(2.21:1),100(2.35:1),101(origin width and height), 111(Reserved)*/
    /* [31:17](Reserved)*/


    ChromaFormat = (pHevcCtx->pCurrSPS->chroma_format_idc == 1) ? 0 : 1;	// 4:2:0, 0;  4:0:0, 1;
    pHevcCtx->CurrPic.fs_image.format = ((pHevcCtx->pCurrSPS->vui_parameters.video_format & 0x7) << 5) | ((ChromaFormat & 0x7 ) << 2);

    /* set display AspectWidth and AspectHeight */
    dar = pHevcCtx->pCurrSPS->vui_parameters.aspect_ratio & 0x7;
    SetAspectRatio(&(pHevcCtx->CurrPic.fs_image), (VDEC_DAR_E)dar);

	//pHevcCtx->CurrPic.fs_image.seq_cnt = pHevcCtx->SeqCnt;
	pHevcCtx->CurrPic.fs_image.is_fld_save = 0;

	pHevcCtx->CurrPic.frame_store->fs_image.format = pHevcCtx->CurrPic.fs_image.format;
	pHevcCtx->CurrPic.frame_store->fs_image.is_fld_save = pHevcCtx->CurrPic.fs_image.is_fld_save;
	pHevcCtx->CurrPic.frame_store->fs_image.u32AspectHeight = pHevcCtx->CurrPic.fs_image.u32AspectHeight;
	pHevcCtx->CurrPic.frame_store->fs_image.u32AspectWidth	= pHevcCtx->CurrPic.fs_image.u32AspectWidth;
	pHevcCtx->CurrPic.frame_store->fs_image.image_width 	= pHevcCtx->CurrPic.fs_image.image_width;
	pHevcCtx->CurrPic.frame_store->fs_image.image_height	= pHevcCtx->CurrPic.fs_image.image_height;

	pstDecFs = FSP_GetDispPhyFs(pHevcCtx->ChanID, pHevcCtx->CurrPic.frame_store->logic_fs_id);
	if(NULL != pstDecFs)
	{
		eStoreType = (pHevcCtx->CurrPic.fs_image.is_fld_save != 0)? FSP_PHY_FS_STORE_TYPE_FIELD : FSP_PHY_FS_STORE_TYPE_FRAME;
		FSP_SetStoreType(pHevcCtx->ChanID, FSP_PHY_FS_TYPE_DECODE, pstDecFs->PhyFsID, eStoreType);
	}

    pHevcCtx->CurrPic.fs_image.left_offset      = pHevcCtx->pCurrSPS->conf_win_left_offset;
    pHevcCtx->CurrPic.fs_image.right_offset     = pHevcCtx->pCurrSPS->conf_win_right_offset;
    pHevcCtx->CurrPic.fs_image.top_offset       = pHevcCtx->pCurrSPS->conf_win_top_offset;
    pHevcCtx->CurrPic.fs_image.bottom_offset    = pHevcCtx->pCurrSPS->conf_win_bottom_offset;
    pHevcCtx->CurrPic.fs_image.disp_width       = pHevcCtx->pCurrSPS->pic_width_in_luma_samples - pHevcCtx->CurrPic.fs_image.left_offset - pHevcCtx->CurrPic.fs_image.right_offset;
    pHevcCtx->CurrPic.fs_image.disp_height      = pHevcCtx->pCurrSPS->pic_height_in_luma_samples - pHevcCtx->CurrPic.fs_image.top_offset - pHevcCtx->CurrPic.fs_image.bottom_offset;
    pHevcCtx->CurrPic.fs_image.bit_depth_luma   = pHevcCtx->pCurrSPS->bit_depth_luma;
    pHevcCtx->CurrPic.fs_image.bit_depth_chroma = pHevcCtx->pCurrSPS->bit_depth_chroma;
    pHevcCtx->CurrPic.fs_image.disp_center_x    = pHevcCtx->CurrPic.frame_store->fs_image.disp_center_x;
    pHevcCtx->CurrPic.fs_image.disp_center_y    = pHevcCtx->CurrPic.frame_store->fs_image.disp_center_y;
    
	pHevcCtx->CurrPic.frame_store->fs_image.disp_width	    = pHevcCtx->CurrPic.fs_image.disp_width;
	pHevcCtx->CurrPic.frame_store->fs_image.disp_height	    = pHevcCtx->CurrPic.fs_image.disp_height;
    
	pHevcCtx->CurrPic.frame_store->fs_image.disp_center_x   = pHevcCtx->CurrPic.fs_image.disp_center_x;
	pHevcCtx->CurrPic.frame_store->fs_image.disp_center_y   = pHevcCtx->CurrPic.fs_image.disp_center_y;
    
    pHevcCtx->CurrPic.pic_type = HEVC_I_FRAME;  // 默认I Frame，在每个slice解析时更新
 
    //ini table
#ifndef HEVC_SYNTAX_OPT
    memset(pHevcCtx->ApcList,0,sizeof(pHevcCtx->ApcList));
    memset(pHevcCtx->IsLongTerm,0,sizeof(pHevcCtx->IsLongTerm));
    memset(pHevcCtx->Apc2MvAddr,0,sizeof(pHevcCtx->Apc2MvAddr));
#endif

    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
* 函数原型 : SINT32 RepairList(HEVC_CTX_S *pHevcCtx)
* 功能描述 : 修补list,只考虑去掉list中的NULL
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_RepairList(HEVC_CTX_S *pHevcCtx)
{
    SINT8  found = -1;
    UINT32 i, i_list, i_list_cnt;
    HEVC_STORABLEPIC_S *pRepairPic = (HEVC_STORABLEPIC_S *)NULL;

    switch (pHevcCtx->CurrSlice.slice_type)
    {
        case HEVC_P_SLICE:
            i_list_cnt = 1;
            break;
        case HEVC_B_SLICE:
            i_list_cnt = 2;
            break;
        case HEVC_I_SLICE:
            i_list_cnt = 0;
            break;
        default:
            dprint(PRN_ERROR, "%s unkown slice type(%d).\n", __func__, pHevcCtx->CurrSlice.slice_type);
            return HEVC_DEC_ERR;
    }

    for (i_list=0; i_list<i_list_cnt; i_list++)
    {
        if (0 < pHevcCtx->CurrSlice.listXsize[i_list])
        {
            found = -1;
            for (i = 0; i < pHevcCtx->CurrSlice.listXsize[i_list]; i++)
            {
                if ((HEVC_STORABLEPIC_S *)NULL != pHevcCtx->pListX[i_list][i])
                {
                    found = i;
                    pRepairPic = pHevcCtx->pListX[i_list][i];
                    break;
                }
            }
            
            if ((-1 == found) || (NULL == pRepairPic))
            {
                if (DEC_ORDER_SIMPLE_DPB == pHevcCtx->pstExtraData->s32DecOrderOutput)
                {
                    /* 如果运行于DEC_ORDER_SIMPLE_DPB, 则用当前pic填充所有list节点 */
                    pRepairPic = &pHevcCtx->CurrPic.frame_store->frame;
                }
                else
                {
                    dprint(PRN_ERROR, "%s pListX[%d] no available pic to repair.\n", __func__, i_list);
                    return HEVC_DEC_ERR;
                }
            }

            for (i=0; i < pHevcCtx->CurrSlice.listXsize[i_list]; i++)
            {
                if ((HEVC_STORABLEPIC_S *)NULL == pHevcCtx->pListX[i_list][i])
                {
                    dprint(PRN_ERROR, "%s: pListX[%d][%d] = NULL, repair it with pos(%d).\n", __func__, i_list, i, found);
                    pHevcCtx->pListX[i_list][i] = pRepairPic;
                }
            }
        }
        else
        {
            if (DEC_ORDER_SIMPLE_DPB == pHevcCtx->pstExtraData->s32DecOrderOutput)
            {
                /* 如果运行于DEC_ORDER_SIMPLE_DPB, 则用当前pic填充所有list节点 */
                pHevcCtx->CurrSlice.listXsize[i_list] = 1;
                pHevcCtx->pListX[i_list][0] = &pHevcCtx->CurrPic.frame_store->frame;
            }
        }
    }

    return HEVC_DEC_NORMAL;
}

/***********************************************************************************
* Function:    HEVC_DecList()
* Description: 生成当前slice的参考列表
* Input:       pHevcCtx->CurrSlice   当前Slice参数
*              pHevcCtx->pListX[2][HEVC_MAX_LIST_SIZE]   List列表
* Output:      pHevcCtx->pListX[2][HEVC_MAX_LIST_SIZE]   List列表
* Return:      HEVC_DEC_NORMAL   可以正确生成List列表
*              HEVC_DEC_ERR      不可以正确生成List列表
* Others:      无
***********************************************************************************/ 
SINT32 HEVC_DecList(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    
    if (HEVC_I_SLICE == pHevcCtx->CurrSlice.slice_type)
    {
        pHevcCtx->CurrSlice.listXsize[0] = 0;
        pHevcCtx->CurrSlice.listXsize[1] = 0;
        return HEVC_DEC_NORMAL;
    }

    ret = HEVC_InitListX(pHevcCtx);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_ERROR, "HEVC_InitListX error.\n");
        return HEVC_DEC_ERR;       
    }

    ret = HEVC_RepairList(pHevcCtx);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_ERROR, "HEVC_RepairList error.\n");
        return HEVC_DEC_ERR;       
    }
    
    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
* 函数原型 : SINT32  HEVC_InitListX()
* 功能描述 : 参考列表初始化
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_InitListX(HEVC_CTX_S *pHevcCtx)
{
    HEVC_STORABLEPIC_S *pTempListX[2][HEVC_MAX_LIST_SIZE];
    HEVC_REF_PIC_LISTS_MODDIFICATION *pRPLModify;
    UINT32 i,idx,RefFrameNum;
    UINT32 NegRefFrameNum = 0;
    UINT32 PosRefFrameNum = 0;
    UINT32 LTRefFrameNum = 0;

    if (NULL == pHevcCtx)
    {
        return HEVC_DEC_ERR;
    }

	memset(pTempListX, 0, sizeof(pTempListX));
	
    idx = 0;
    for (i=0; i<pHevcCtx->DPB.negative_ref_frames_in_buffer; i++)
    {
        if ((1 == pHevcCtx->DPB.fs_negative_ref[i]->is_reference) &&
            (0 == pHevcCtx->DPB.fs_negative_ref[i]->frame.is_long_term) &&
            (1 == pHevcCtx->DPB.fs_negative_ref[i]->frame.is_short_term))
        {
            pTempListX[0][idx++] = &pHevcCtx->DPB.fs_negative_ref[i]->frame;
        }
    }
    NegRefFrameNum = idx;
    
    for (i=0; i<pHevcCtx->DPB.positive_ref_frames_in_buffer; i++)
    {
        if ((1 == pHevcCtx->DPB.fs_positive_ref[i]->is_reference) &&
            (0 == pHevcCtx->DPB.fs_positive_ref[i]->frame.is_long_term) &&
            (1 == pHevcCtx->DPB.fs_positive_ref[i]->frame.is_short_term))
        {
            pTempListX[0][idx++] = &pHevcCtx->DPB.fs_positive_ref[i]->frame;
        }
    }     
    PosRefFrameNum = idx - NegRefFrameNum;
    
    // long term handling
    for (i=0; i<pHevcCtx->DPB.ltref_frames_in_buffer; i++)
    {
        if ((1 == pHevcCtx->DPB.fs_ltref[i]->is_reference) &&
            (1 == pHevcCtx->DPB.fs_ltref[i]->frame.is_long_term) &&
            (0 == pHevcCtx->DPB.fs_ltref[i]->frame.is_short_term))
        {
            pTempListX[0][idx++] = &pHevcCtx->DPB.fs_ltref[i]->frame;
        }
    }
    LTRefFrameNum = idx - NegRefFrameNum - PosRefFrameNum;
    RefFrameNum = idx;

    if (RefFrameNum==0)
    {
        pHevcCtx->CurrSlice.listXsize[0] = 0;
        pHevcCtx->CurrSlice.listXsize[1] = 0;
        memset(pHevcCtx->pListX, 0, sizeof(pHevcCtx->pListX));

        /* Simple DPB模式下，用当前帧作为参考图强制解码 */
        if (DEC_ORDER_SIMPLE_DPB == pHevcCtx->pstExtraData->s32DecOrderOutput)
        {
            pHevcCtx->CurrSlice.listXsize[0] = 1;
            pHevcCtx->pListX[0][0] = &pHevcCtx->CurrPic.frame_store->frame;
        }
        return HEVC_DEC_NORMAL;
    }
    
    if (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)
    {
        idx = 0;
        for (i=0; i<PosRefFrameNum; i++)
        {
            pTempListX[1][idx++] = pTempListX[0][NegRefFrameNum + i];
        }
        for (i=0; i<NegRefFrameNum; i++)
        {
            pTempListX[1][idx++] = pTempListX[0][i];
        }
        for (i=0; i<LTRefFrameNum; i++)
        {
            pTempListX[1][idx++] = pTempListX[0][NegRefFrameNum + PosRefFrameNum + i];
        }
        //pHevcCtx->CurrSlice.listXsize[1] = list1Idx;
    }
    
    // set max size
    pHevcCtx->CurrSlice.listXsize[0] =  pHevcCtx->CurrSlice.num_ref_idx[0];
    pHevcCtx->CurrSlice.listXsize[1] =  pHevcCtx->CurrSlice.num_ref_idx[1]; 
    
    idx = 0;
    pRPLModify = &(pHevcCtx->CurrSlice.ref_pic_lists_modification);
    for (i=0; i<pHevcCtx->CurrSlice.listXsize[0]; i++)
    {
        idx = pRPLModify->ref_pic_list_modification_flag_l0?pRPLModify->list_entry_l0[i]:i%RefFrameNum;
        pHevcCtx->pListX[0][i] = pTempListX[0][idx];
    }

    if (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)
    {
        for (i=0; i<pHevcCtx->CurrSlice.listXsize[1]; i++)
        {
            idx = pRPLModify->ref_pic_list_modification_flag_l1?pRPLModify->list_entry_l1[i]:i%RefFrameNum;	
            pHevcCtx->pListX[1][i] = pTempListX[1][idx];        
        }

        //for generalized b slice
        if (pHevcCtx->CurrSlice.listXsize[1] == 0)
        {
            memcpy(pHevcCtx->pListX[1],pHevcCtx->pListX[0],sizeof(pHevcCtx->pListX[0]));
            pHevcCtx->CurrSlice.listXsize[1] = pHevcCtx->CurrSlice.listXsize[0];
        }
    }

    // set the unused list entries to a valid one
    for (i=pHevcCtx->CurrSlice.listXsize[0]; i<(HEVC_MAX_LIST_SIZE); i++)
    {
        pHevcCtx->pListX[0][i] = pHevcCtx->pListX[0][0];
    }
    for (i=pHevcCtx->CurrSlice.listXsize[1]; i<(HEVC_MAX_LIST_SIZE); i++)
    {
        pHevcCtx->pListX[1][i] = pHevcCtx->pListX[1][0];
    }
    
    // InitlistX over
    return HEVC_DEC_NORMAL;    
}


/*!
************************************************************************
* 函数原型 : SINT32 compare_pic_by_poc_asc(CONSTVOID *arg1, CONSTVOID *arg2)
* 功能描述 :  按升序比较HEVC_FRAMESTORE_S结构体中的元素poc的大小，
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
static SINT32 compare_pic_by_poc_asc(CONSTVOID *arg1, CONSTVOID *arg2)
{
    if ((*(HEVC_FRAMESTORE_S**)arg1)->poc < (*(HEVC_FRAMESTORE_S**)arg2)->poc)
    {
        return -1;
    }
    
    if ((*(HEVC_FRAMESTORE_S**)arg1)->poc > (*(HEVC_FRAMESTORE_S**)arg2)->poc)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_InitDPB(HEVC_CTX_S *pHevcCtx,UINT32 ReRangeFlag)
*      功能描述 :  初始化dpb
*      参数说明 :  
*      返回值   ： 
************************************************************************
*/
SINT32 HEVC_InitDPB(HEVC_CTX_S *pHevcCtx,UINT32 ReRangeFlag)
{
    SINT32 ret;
    UINT32 i, j;
    UINT32 ImageWidth, ImageHeight;
    UINT32 ImageWidthInCtb, ImageHeightInCtb;

    HEVC_ClearAllSlice(pHevcCtx);

    //清除逻辑帧存 DPB refresh
	for (i=0; i<HEVC_MAX_DPB_NUM; i++)	
    {
        if(pHevcCtx->DPB.fs[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 1);
        }
        if(pHevcCtx->DPB.fs_negative_ref[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs_negative_ref[i]->logic_fs_id, 1);
        }
        if(pHevcCtx->DPB.fs_positive_ref[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs_positive_ref[i]->logic_fs_id, 1);
        }
        if(pHevcCtx->DPB.fs_ltref[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs_ltref[i]->logic_fs_id, 1);
        }
        pHevcCtx->DPB.fs[i] = pHevcCtx->DPB.fs_negative_ref[i] = pHevcCtx->DPB.fs_positive_ref[i] = pHevcCtx->DPB.fs_ltref[i] = NULL;
    }
	
    pHevcCtx->DPB.size = pHevcCtx->pCurrSPS->dpb_size + 1;
	if (pHevcCtx->DPB.size > HEVC_MAX_DPB_NUM)
	{
		pHevcCtx->DPB.size = HEVC_MAX_DPB_NUM;
	}
    pHevcCtx->DPB.used_size = 0;
    pHevcCtx->DPB.negative_ref_frames_in_buffer   = 0;
    pHevcCtx->DPB.positive_ref_frames_in_buffer   = 0;
    pHevcCtx->DPB.ltref_frames_in_buffer = 0;
    pHevcCtx->DPB.max_long_term_pic_idx  = 0;

    //apc init
    memset(&pHevcCtx->APC, 0, sizeof(HEVC_APC_S));
    pHevcCtx->APC.size = HEVC_APC_SIZE; //apc size固定16
    pHevcCtx->APC.used_size = 0;

    for (i=0; i<2; i++)
    {
        for (j=0; j<HEVC_MAX_LIST_SIZE; j++)
        {
            pHevcCtx->pListX[i][j] = NULL;
        }
        pHevcCtx->CurrSlice.listXsize[i] = 0;
    }

    if (ReRangeFlag || (1 == pHevcCtx->pstExtraData->s32WaitFsFlag))
    {   	
        pHevcCtx->TotalFsNum  = HEVC_MAX_FRAME_STORE;
        pHevcCtx->TotalPmvNum = HEVC_MAX_PMV_STORE;

        ImageWidthInCtb  = pHevcCtx->pCurrSPS->ctb_num_width;
        ImageHeightInCtb = pHevcCtx->pCurrSPS->ctb_num_height;
        ImageWidth       = pHevcCtx->pCurrSPS->ctb_num_width  << pHevcCtx->pCurrSPS->log2_ctb_sizeY;
        ImageHeight      = pHevcCtx->pCurrSPS->ctb_num_height << pHevcCtx->pCurrSPS->log2_ctb_sizeY;

        ret = HEVC_ArrangeVahbMem(pHevcCtx,ImageWidth, ImageHeight, ImageWidthInCtb, ImageHeightInCtb, pHevcCtx->TotalFsNum, pHevcCtx->TotalPmvNum);
        if(1 != pHevcCtx->pstExtraData->s32WaitFsFlag)
        {
            if (ret != VF_OK)
            {
                dprint(PRN_FATAL, "%s arrange mem failed.\n", __func__);
                return HEVC_VHB_MEM_ERR;
            }
        }
        else
        {
            return HEVC_NOTDEC;
        }
        pHevcCtx->TotalFsNum = MIN(FSP_GetTotalValidFsNum(pHevcCtx->ChanID), HEVC_MAX_FRAME_STORE);
    }

    for (i=0; i<pHevcCtx->TotalPmvNum; i++)
    {
        pHevcCtx->PmvStoreUsedFlag[i] = 0;
    }

    //MSGPOOL init, 有关消息池的操作待定
    for (i = 0; i < pHevcCtx->MaxSlotNum; i++)
    {
        if (pHevcCtx->pMsgSlot[i].slice_nal != NULL
            && pHevcCtx->pMsgSlot[i].slice_nal != pHevcCtx->pCurrNal)
        {
            HEVC_ReleaseNAL(pHevcCtx->ChanID, pHevcCtx->pMsgSlot[i].slice_nal);
            pHevcCtx->pMsgSlot[i].slice_nal = NULL;
        }
    }
	
    return HEVC_DEC_NORMAL;
}


VOID Hevc_InitDecBuffers(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i,j;
	
    //Init DPB
    pHevcCtx->DPB.size = pHevcCtx->pCurrSPS->dpb_size + 1;
	if (pHevcCtx->DPB.size > HEVC_MAX_DPB_NUM)
	{
		pHevcCtx->DPB.size = HEVC_MAX_DPB_NUM;
	}
    pHevcCtx->DPB.used_size                     = 0;
    pHevcCtx->DPB.negative_ref_frames_in_buffer = 0;
    pHevcCtx->DPB.positive_ref_frames_in_buffer = 0;
    pHevcCtx->DPB.ltref_frames_in_buffer        = 0;
    pHevcCtx->DPB.max_long_term_pic_idx         = 0;

	for (i=0; i<HEVC_MAX_DPB_NUM; i++)
	{
        pHevcCtx->DPB.fs_ltref[i]        = NULL;
        pHevcCtx->DPB.fs_negative_ref[i] = NULL;
        pHevcCtx->DPB.fs_positive_ref[i] = NULL;
        pHevcCtx->DPB.fs[i]              = NULL;
    }

    //Init Frame store
    for (i=0; i<HEVC_MAX_FRAME_STORE; i++)
    {
        memset(&pHevcCtx->FrameStore[i].fs_image, 0, sizeof(IMAGE));
        pHevcCtx->FrameStore[i].fs_image.image_id = i; 
        pHevcCtx->FrameStore[i].non_existing      = 0;
        pHevcCtx->FrameStore[i].eFrameStoreState  = FS_NOT_USED;   
        pHevcCtx->FrameStore[i].is_reference      = 0;   
        pHevcCtx->FrameStore[i].poc               = 0;   
        pHevcCtx->FrameStore[i].is_displayed      = 0;   
        pHevcCtx->FrameStore[i].pmv_address_idc   = HEVC_MAX_PMV_STORE;   
        pHevcCtx->FrameStore[i].apc_idc           = HEVC_APC_SIZE;
        pHevcCtx->FrameStore[i].frame.frame_store = &pHevcCtx->FrameStore[i];   
        pHevcCtx->FrameStore[i].frame.structure   = 0;     
    }
    
    //Init Apc
    memset(&pHevcCtx->APC, 0, sizeof(HEVC_APC_S));
    pHevcCtx->APC.size      = HEVC_APC_SIZE;
    pHevcCtx->APC.used_size = 0;

    //Init ListX
    for (i=0; i<2; i++)
    {
        for (j=0; j<HEVC_MAX_LIST_SIZE; j++)
        {
            pHevcCtx->pListX[i][j] = NULL;
        }
        pHevcCtx->CurrSlice.listXsize[i] = 0;
    }

    //Init PMVAddr used flag
    for (i=0; i<pHevcCtx->TotalPmvNum; i++)
    {
        pHevcCtx->PmvStoreUsedFlag[i] = 0;
    }

    //MSGPOOL init,有关消息池的操作待定
    for (i = 0; i < pHevcCtx->MaxSlotNum; i++)
    {
        if (pHevcCtx->pMsgSlot[i].slice_nal != NULL
            && pHevcCtx->pMsgSlot[i].slice_nal != pHevcCtx->pCurrNal)
        {
            HEVC_ReleaseNAL(pHevcCtx->ChanID, pHevcCtx->pMsgSlot[i].slice_nal);
            pHevcCtx->pMsgSlot[i].slice_nal = NULL;
            pHevcCtx->NumSlicePara   = (pHevcCtx->NumSlicePara   > 0)? pHevcCtx->NumSlicePara-1:  0;
            pHevcCtx->TotalSliceNum  = (pHevcCtx->TotalSliceNum  > 0)? pHevcCtx->TotalSliceNum-1: 0;
            pHevcCtx->CurrMsgSlotNum = (pHevcCtx->CurrMsgSlotNum > HEVC_SLICE_SLOT_START_NUM-1)? pHevcCtx->CurrMsgSlotNum-1: HEVC_SLICE_SLOT_START_NUM - 1;
        }
    }

    return;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_DirectOutput()
*      功能描述 :  直接输出当前帧
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 成功;
*                  其他值
************************************************************************
*/
SINT32 HEVC_DirectOutput(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    HEVC_FRAMESTORE_S  *pDirectOutBuf = NULL;
    
    //把当前图像存入DirectOutBuf，再输出
    pDirectOutBuf = pHevcCtx->CurrPic.frame_store;
    
    pDirectOutBuf->eFrameStoreState = FS_DISPLAY_ONLY;
    pDirectOutBuf->is_reference     = 0;
    pDirectOutBuf->is_displayed     = 1;
    pDirectOutBuf->pic_type         = pHevcCtx->CurrPic.pic_type;
    pDirectOutBuf->err_level        = pHevcCtx->CurrPic.err_level;
    pDirectOutBuf->fs_image         = pHevcCtx->CurrPic.fs_image;
    pDirectOutBuf->frame.structure  = FRAME;
    pDirectOutBuf->frame.err_level  = pHevcCtx->CurrPic.err_level;

    FSP_SetRef(pHevcCtx->ChanID, pDirectOutBuf->logic_fs_id, 0);
    ret = HEVC_OutputFrmToVO(pHevcCtx, pDirectOutBuf);
    
    pDirectOutBuf->eFrameStoreState = FS_NOT_USED;
    memset(&pHevcCtx->CurrPic, 0, sizeof(pHevcCtx->CurrPic));

    return ret;
}

/*****************************************************************************
    简化的滑窗dpb管理策略.
    当DecOrderOutput == DEC_ORDER_SIMPLE_DPB时使用此策略. 
    在视频电话等领域中途不发I帧. 这样如果发生了误码，解码器不能清除参考图. 
    但是作为通用解码器这样非常危险，所以在这种应用中先把DPB管理机制进行简化，
    而通用码流的处理则沿用标准策略。
 *****************************************************************************/
VOID  HEVC_SimpleSlideDPB(HEVC_CTX_S *pHevcCtx)
{
    if(pHevcCtx->DPB.used_size >= pHevcCtx->DPB.size)
    {
        /* 如果已达上限，或尝试递增DPB Size失败，清空fs[0] 
           因为当前帧要插入DPB中，需要获取APC，而APC最大值等于16，所以
           在这里DPB上限不能超过APC个数(16)，而不是DPB数组上限(17) */
        if (pHevcCtx->DPB.size >= HEVC_APC_SIZE || HEVC_IncreaseDPBSize(pHevcCtx) != HEVC_DEC_NORMAL)
        {
            /* 把第0个帧存标识为不参考，并从DPB中删除这个帧 */
            HEVC_UnMarkFrameStoreRef(pHevcCtx,pHevcCtx->DPB.fs[0]);
            HEVC_RemoveApcStore(pHevcCtx, 0);
            HEVC_RemoveFrameStoreOutDPB(pHevcCtx, 0);
        }
    }

    return;
}


/*!
************************************************************************
*   函数原型 :  VOID HEVC_RemoveApcStore()
*   功能描述 :  将apc移出，将pmvIdc移出
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID HEVC_RemoveApcStore(HEVC_CTX_S *pHevcCtx, UINT32 pos)
{
	if (pHevcCtx->DPB.fs[pos]->apc_idc != HEVC_APC_SIZE)
	{
		//release APC and PMV Idc
	    pHevcCtx->APC.is_used[pHevcCtx->DPB.fs[pos]->apc_idc] = 0;
	    pHevcCtx->APC.idc[pHevcCtx->DPB.fs[pos]->apc_idc] = 0;
	    pHevcCtx->APC.poc[pHevcCtx->DPB.fs[pos]->apc_idc] = 0;
	    pHevcCtx->PmvStoreUsedFlag[pHevcCtx->DPB.fs[pos]->pmv_address_idc] = 0;
	    dprint(PRN_REF, "release(apc=%d, pmvIdc=%d)\t",pHevcCtx->DPB.fs[pos]->apc_idc,pHevcCtx->DPB.fs[pos]->pmv_address_idc);
		pHevcCtx->DPB.fs[pos]->apc_idc = HEVC_APC_SIZE;
		pHevcCtx->APC.used_size--;
	}
}

/*!
************************************************************************
*   函数原型 :  VOID HEVC_RemoveApcStore()
*   功能描述 :  将apc移出，APC与DPB分开处理
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID HEVC_RemoveUnusedApcStore(HEVC_CTX_S *pHevcCtx)
{
	SINT32 i;

	//find frames that were unused for reference and remove APC
	for (i = 0; i < pHevcCtx->DPB.used_size; i++)
	{
		if (!pHevcCtx->DPB.fs[i]->is_reference)
		{
			HEVC_RemoveApcStore(pHevcCtx, i);
		}
	}

	return;
}

/*!
************************************************************************
*   函数原型 :  VOID HEVC_RemoveApcStore()
*   功能描述 :  将补充的参考帧移出DPB，包括APC与帧存
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID HEVC_RemoveDummyFrame(HEVC_CTX_S *pHevcCtx)
{
	SINT32 i;

	for (i = 0; i < pHevcCtx->DPB.used_size; i++)
	{
		if (pHevcCtx->DPB.fs[i]->non_existing)
		{
            pHevcCtx->DPB.fs[i]->non_existing = 0;
			HEVC_RemoveApcStore(pHevcCtx, i);
			HEVC_RemoveFrameStoreOutDPB(pHevcCtx, i);
			i--; //删除一帧后，used_size会减1，i-1才是要处理的一帧
		}
	}

	return;
}


/*!
************************************************************************
*   函数原型 :  VOID HEVC_ApplyReferencePictureSet(HEVC_CTX_S *pHevcCtx)
*   功能描述 :  标记DPB中参考帧信息
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID HEVC_ApplyReferencePictureSet(HEVC_CTX_S *pHevcCtx)
{
	SINT32 i, j;
    SINT32 CurPoc;
    SINT32 RefPoc;
	SINT32 is_reference;
	SINT32 PocCycle;
	HEVC_SHORT_TERM_RPSET_S *pTempRps = NULL;
	HEVC_PIC_PARAM_SET_S    *pPPS = NULL;
	HEVC_SEQ_PARAM_SET_S    *pSPS = NULL;
	
	pPPS = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
	pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];
	PocCycle = 1 << pSPS->max_pic_order_cnt_lsb;

	pTempRps = &(pHevcCtx->CurrSlice.short_term_ref_pic_set);
    for (i=0; i<pHevcCtx->DPB.used_size; i++)
    {
        is_reference = 0;

        // long term reference
        for (j=pTempRps->num_negative_pics+pTempRps->num_positive_pics; j<pTempRps->num_of_pics; j++)
        {
            if (pHevcCtx->CurrSlice.CheckLTMSB[j])
            {
                if ((pHevcCtx->DPB.fs[i]->frame.is_long_term) &&
                    (pHevcCtx->DPB.fs[i]->poc == pTempRps->poc[j]))
                {
                    is_reference = 1;
                    pHevcCtx->DPB.fs[i]->is_reference = 1;
                    pHevcCtx->DPB.fs[i]->eFrameStoreState = FS_IN_DPB;
                    FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 1);
                }
            }
            else if( (pHevcCtx->DPB.fs[i]->frame.is_long_term) 
                 && ((pHevcCtx->DPB.fs[i]->poc % PocCycle) == (pTempRps->poc[j] % PocCycle)) )
            {
                is_reference = 1;
                pHevcCtx->DPB.fs[i]->is_reference = 1;
                pHevcCtx->DPB.fs[i]->eFrameStoreState = FS_IN_DPB;
                FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 1);
            }

            if(0 == is_reference)
            { 
                CurPoc = pHevcCtx->DPB.fs[i]->poc;
                RefPoc = pTempRps->poc[j];
                
                if(!pHevcCtx->CurrSlice.CheckLTMSB[j])
                {
                    CurPoc = CurPoc % PocCycle;
                    RefPoc = RefPoc % PocCycle;
                }

                if(pHevcCtx->DPB.fs[i]->is_reference && CurPoc == RefPoc)
                {
                    is_reference = 1;
                    pHevcCtx->DPB.fs[i]->is_reference = 1;
                    pHevcCtx->DPB.fs[i]->frame.is_long_term = 1;
                    pHevcCtx->DPB.fs[i]->eFrameStoreState = FS_IN_DPB;
                    FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 1);
                }
            }
        }
        
        // short term reference
        for (j=0; j<(pTempRps->num_negative_pics + pTempRps->num_positive_pics); j++)
        {
            if ((!pHevcCtx->DPB.fs[i]->frame.is_long_term) &&
                (pHevcCtx->DPB.fs[i]->poc == (pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[j])))
            {
                is_reference = 1;
                pHevcCtx->DPB.fs[i]->is_reference = 1;
                pHevcCtx->DPB.fs[i]->eFrameStoreState = FS_IN_DPB;
                FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 1);
            }
        }

        // mark the picture as "unused for reference" if it is not in
        // the Reference Picture Set
        if ((pHevcCtx->DPB.fs[i]->poc != pHevcCtx->CurrSlice.poc) && (0 == is_reference))
        {
            pHevcCtx->DPB.fs[i]->is_reference = 0;
            pHevcCtx->DPB.fs[i]->frame.is_long_term = 0;

            // 如果是快速输出帧，处于等待正常输出状态，先不清逻辑帧存ref状态，以免逻辑帧存被释放重用
            if (pHevcCtx->DPB.fs[i]->eFirstFrameState != FIRST_FRAME_WAIT_OUT)
            {
                FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 0);
            }
        }
    }

    return;
}


SINT32 HEVC_CheckThatAllRefPicsAreAvailable(HEVC_CTX_S *pHevcCtx, SINT32* piLostPoc)
{
    SINT32 i, j, isAvailable;
    SINT32 atLeastOneLost = 0;
    //SINT32 atLeastOneRemoved = 0;
    SINT32 iPocLost = 0;
    SINT32 PocCycle;
    HEVC_SHORT_TERM_RPSET_S *pTempRps = NULL;
	HEVC_PIC_PARAM_SET_S    *pPPS = NULL;
	HEVC_SEQ_PARAM_SET_S    *pSPS = NULL;
	
	pPPS = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
	pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];
	PocCycle = 1 << pSPS->max_pic_order_cnt_lsb;
  
    pTempRps = &(pHevcCtx->CurrSlice.short_term_ref_pic_set);
  
    // loop through all long-term pictures in the Reference Picture Set
    // to see if the picture should be kept as reference picture
    for(i = pTempRps->num_negative_pics+pTempRps->num_positive_pics; i < pTempRps->num_of_pics; i++)
    {
    	isAvailable = 0;
    	// loop through all pictures in the reference picture buffer
    	for (j = 0; j < pHevcCtx->DPB.used_size; j++)
    	{
            if(pHevcCtx->CurrSlice.CheckLTMSB[i])
            {
                if(pHevcCtx->DPB.fs[j]->frame.is_long_term && pHevcCtx->DPB.fs[j]->poc == pTempRps->poc[i] && pHevcCtx->DPB.fs[j]->is_reference)
                {
                    isAvailable = 1;
                }
            }
            else 
            {
                if(pHevcCtx->DPB.fs[j]->frame.is_long_term && ((pHevcCtx->DPB.fs[j]->poc % PocCycle) == (pTempRps->poc[i] % PocCycle)) && pHevcCtx->DPB.fs[j]->is_reference)
                {
                    isAvailable = 1;
                }
            }
    	}
              
        // report that a picture is lost if it is in the Reference Picture Set
        // but not available as reference picture
        if(isAvailable == 0)    
        {            
            if (pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i] >= pHevcCtx->PocRandomAccess)
            {
                if(!pTempRps->used_flag[i])
                {
                    //dprint(PRN_ERROR, "Long-term reference picture with POC = %3d seems to have been removed or not correctly decoded.\n", pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i]);
                    //atLeastOneRemoved = 1;
                }
                else
                {
                    //dprint(PRN_ERROR, "Long-term reference picture with POC = %3d is lost or not correctly decoded!\n", pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i]);
                    //dprint(PRN_ERROR, "CurrSlice.poc=%d delta_poc[%d]=%d PocRandomAccess=%d\n", pHevcCtx->CurrSlice.poc, i, pTempRps->delta_poc[i], pHevcCtx->PocRandomAccess);
                    atLeastOneLost = 1;
                    iPocLost = pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i];
                }
            }
        }
    }
    
    // loop through all short-term pictures in the Reference Picture Set
    // to see if the picture should be kept as reference picture
    for(i = 0; i < pTempRps->num_negative_pics+pTempRps->num_positive_pics; i++)
    {
        isAvailable = 0;
        // loop through all pictures in the reference picture buffer
        for (j = 0; j < pHevcCtx->DPB.used_size; j++)
        {
            if(!pHevcCtx->DPB.fs[j]->frame.is_long_term && pHevcCtx->DPB.fs[j]->poc == pHevcCtx->CurrSlice.poc+pTempRps->delta_poc[i] && pHevcCtx->DPB.fs[j]->is_reference)
            {
                isAvailable = 1;
            }
        }
        // report that a picture is lost if it is in the Reference Picture Set
        // but not available as reference picture
        if(isAvailable == 0)    
        {            
            if (pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i] >= pHevcCtx->PocRandomAccess)
            {
                if(!pTempRps->used_flag[i])
                {
                    //dprint(PRN_ERROR, "Short-term reference picture with POC = %3d seems to have been removed or not correctly decoded.\n",  pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i]);
                    //atLeastOneRemoved = 1;
                }
                else
                {
                    //dprint(PRN_ERROR, "Short-term reference picture with POC = %3d is lost or not correctly decoded!\n", pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i]);
                    atLeastOneLost = 1;
                    iPocLost = pHevcCtx->CurrSlice.poc + pTempRps->delta_poc[i];
                }
            }
        }
    }    
    
    if(atLeastOneLost)
    {
        *piLostPoc = iPocLost;
        return 0;
    }
    
    return 1;
}


SINT32 HEVC_CreateLostPicture(HEVC_CTX_S *pHevcCtx, SINT32 iLostPoc)
{
	SINT32 i;
	SINT32 ret;
    SINT32 closestPoc = HEVC_MAX_INT;
	SINT8  bIsFindPoc = 0;
	HEVC_CURRPIC_S stLostPic;
    SINT32 LogicFsID = 0;
    FSP_LOGIC_FS_S *pstLFs = NULL;	
	FSP_LOGIC_FS_S *pstRefLFs = NULL;	

    if (88 ==pHevcCtx->TotalPicNum-1)
    {
        //HEVC_PrintDPBState(pHevcCtx);
    }
      
	// 找一个没有用到的帧存
    for (i=0; i<HEVC_MAX_FRAME_STORE; i++)
    {
        if (FS_NOT_USED == pHevcCtx->FrameStore[i].eFrameStoreState && (1 == HEVC_IsOutDPB(pHevcCtx, &pHevcCtx->FrameStore[i])))
        {
            /* error_level必须标记为有错，否则在解gap，或者其它原因其实并未解码
               但发生了StorePicInDPB()的操作，则这个本当不该输出的图有可能被输出*/
            stLostPic.err_level                     = 101;
            stLostPic.state                         = HEVC_PIC_DECODING;
			stLostPic.thispoc                       = iLostPoc; 
            stLostPic.is_ref_idc                    = 1;
            
            stLostPic.fs_image                      = pHevcCtx->FrameStore[i].fs_image;
            stLostPic.fs_image.error_level          = 0;
            
            stLostPic.frame_store                   = &pHevcCtx->FrameStore[i];		
            stLostPic.frame_store->is_displayed     = 1; //防止该帧误输出
            stLostPic.frame_store->eFirstFrameState = FIRST_FRAME_OUT_INIT;
            stLostPic.frame_store->non_existing     = 1; //补参考帧的标识
            break;
        }
    }

    if (i >= HEVC_MAX_FRAME_STORE)
    {
        dprint(PRN_FATAL,"No frame store for lost pic.\n");		
        return HEVC_DEC_ERR;
    }

    for (i = 0; i < pHevcCtx->DPB.used_size; i++)
    {
    	if(ABS(pHevcCtx->DPB.fs[i]->poc - iLostPoc) < closestPoc && pHevcCtx->DPB.fs[i]->is_reference)
    	{
    		closestPoc = ABS(pHevcCtx->DPB.fs[i]->poc - iLostPoc);
    		bIsFindPoc = 1;
    	}
    }
    //如果DPB没有参考帧,不能补参考帧
    if(0 == bIsFindPoc)
    {
        stLostPic.frame_store->non_existing = 0;
        dprint(PRN_FATAL,"DPB no suited fs for lost pic.\n");
        return HEVC_DEC_ERR;
    }

    for (i = 0; i < pHevcCtx->DPB.used_size; i++)
    {
    	if(ABS(pHevcCtx->DPB.fs[i]->poc - iLostPoc) == closestPoc && pHevcCtx->DPB.fs[i]->is_reference)
        {
            pstRefLFs = FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id);
            dprint(PRN_ERROR,"Take poc(%d) to creat lost poc(%d).\n", pHevcCtx->DPB.fs[i]->poc, iLostPoc);   
            break;
        }
    }
    if(NULL == pstRefLFs)
    {
        dprint(PRN_FATAL, "DPB ERROR: Can not get ref_fs!\n");	
        return HEVC_FS_ALLOC_ERR;
    }
    else if (NULL == pstRefLFs->pstDecodeFs)
    {
        dprint(PRN_FATAL, "DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\n");
        HEVC_ClearDPB(pHevcCtx);
        return HEVC_FS_ALLOC_ERR;
    }
    
    /* FrameStore申请到之后, 还要新建逻辑帧存，这样才能得到真正的地址，不用物理帧存 */
    LogicFsID = FSP_NewLogicFs(pHevcCtx->ChanID, 0);  
    pstLFs = FSP_GetLogicFs(pHevcCtx->ChanID, LogicFsID);
    if (LogicFsID >= 0 && NULL != pstLFs)
    {
    	stLostPic.frame_store->logic_fs_id = LogicFsID;	
    }
    else
    {
        stLostPic.frame_store->non_existing = 0;
    	dprint(PRN_FATAL, "ERROR: Can not new logic fs!\n");	
    	return HEVC_FS_ALLOC_ERR;
    }

    pstLFs->pstDecodeFs       = pstRefLFs->pstDecodeFs;
    pstLFs->pstDispOutFs      = pstRefLFs->pstDispOutFs;
    pstLFs->pstTfOutFs        = pstRefLFs->pstTfOutFs;
    stLostPic.pmv_address_idc = pstRefLFs->PmvIdc;

    ret = HEVC_InsertFrmInDPB(pHevcCtx,pHevcCtx->DPB.used_size, &stLostPic);
    if (HEVC_DEC_NORMAL != ret)
    {
        stLostPic.frame_store->non_existing = 0;
        FSP_ClearLogicFs(pHevcCtx->ChanID, LogicFsID, 1);
        dprint(PRN_FATAL,"Lost pic insert in DPB Failed!\n");		
    	return HEVC_DEC_ERR;
    }

    FSP_SetDisplay(pHevcCtx->ChanID, LogicFsID, 0);
    
    if(pHevcCtx->PocRandomAccess == HEVC_MAX_INT)
    {
      pHevcCtx->PocRandomAccess = iLostPoc;
    }

	return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_IModeProcess()
*      功能描述 :  I 帧模式处理函数
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 成功返回;
*                  other: 异常错误
************************************************************************
*/
SINT32 HEVC_IModeProcess(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    
    ret = HEVC_DirectOutput(pHevcCtx);
    
    // pmv槽位设置成缺省值
    if (pHevcCtx->CurrPic.pmv_address_idc != pHevcCtx->TotalPmvNum)
    {
        pHevcCtx->PmvStoreUsedFlag[pHevcCtx->CurrPic.pmv_address_idc] = 0;
        pHevcCtx->CurrPic.pmv_address_idc = pHevcCtx->TotalPmvNum;
    }
    
    return ret;
}


/*!
************************************************************************
*      函数原型 :  VOID HEVC_SetFrmRepeatCount(HEVC_CTX_S *pHevcCtx, IMAGE *p_image)
*      功能描述 :  PVR要不要重复输出帧判断函数
*      参数说明 :  无 
*      返回值   ： 
************************************************************************
*/
VOID HEVC_SetFrmRepeatCount(HEVC_CTX_S *pHevcCtx, IMAGE *p_image)
{
    if (!((pHevcCtx->pstExtraData->s32FastForwardBackwardSpeed > -2048)&&(pHevcCtx->pstExtraData->s32FastForwardBackwardSpeed <= 2048)))
    {
        if (pHevcCtx->NewPicCounter >= (pHevcCtx->PicOutCounter + 1 + pHevcCtx->DPB.size))
        {
            if ((pHevcCtx->NewPicCounter - (pHevcCtx->PicOutCounter + 1 + pHevcCtx->DPB.size)) >= 2)
            {            
                p_image->u32RepeatCnt    = 2;
                pHevcCtx->PicOutCounter += 2;
            }			
			else
            {            
                p_image->u32RepeatCnt    = 1;
                pHevcCtx->PicOutCounter += 1;
            }			
        }
		else
        {
            p_image->u32RepeatCnt = 0;
        }
    }
	else
    {
        p_image->u32RepeatCnt = 0;
    }
	
    return;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_OutputCurrPic()
*      功能描述 :  直接输出当前帧，不经过排序处理
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 成功返回;
*                  other: 异常错误
************************************************************************
*/
SINT32 HEVC_OutputCurrPic(HEVC_CTX_S *pHevcCtx)
{
    IMAGE *pImg = NULL;
    HEVC_CURRPIC_S    *pOutPic = NULL;
    HEVC_FRAMESTORE_S *pOutFrameStore = NULL;

    pOutPic = &pHevcCtx->CurrPic;
    pOutFrameStore = pHevcCtx->CurrPic.frame_store;
       
    pOutFrameStore->err_level = pOutPic->err_level;
    pOutFrameStore->fs_image  = pOutPic->fs_image;
    
    HEVC_GetImagePara(pHevcCtx, pOutFrameStore);
    
    pImg = FSP_GetFsImagePtr(pHevcCtx->ChanID, pOutFrameStore->logic_fs_id);
    if (NULL == pImg)
    {
        dprint(PRN_FATAL,"%s: pImg is NULL!\n", __func__);
        return HEVC_DEC_ERR;
    }
    
    pImg->error_level = pOutFrameStore->err_level;
    if (pImg->error_level > 0 && pOutPic->pic_type == HEVC_I_FRAME) /* 如果I帧有错误，上报一个事件通知应用层 */
    {
        dprint(PRN_ERROR, "%s, REPORT_IFRAME_ERR\n", __func__);
        REPORT_IFRAME_ERR(pHevcCtx->ChanID);
    }
    if (pImg->error_level == 0 || pImg->error_level <= pHevcCtx->pstExtraData->s32OutErrThr)
    {
        if (pHevcCtx->CurrPic.is_ref_idc != 0)
        {
            FSP_SetRef(pHevcCtx->ChanID, pOutFrameStore->logic_fs_id, 1);
        }
        FSP_SetDisplay(pHevcCtx->ChanID, pOutFrameStore->logic_fs_id, 1);
        if (VF_OK != InsertImgToVoQueue(pHevcCtx->ChanID, VFMW_HEVC, pHevcCtx, &pHevcCtx->ImageQue, pImg))
        {
            dprint(PRN_ERROR, "%s: InsertImgToVoQueue failed!\n", __func__);
            FSP_SetDisplay(pHevcCtx->ChanID, pOutFrameStore->logic_fs_id, 0);
            return HEVC_DEC_ERR;
        }
		
		HEVC_SetFrmRepeatCount(pHevcCtx, pImg);
        pHevcCtx->OutputFrameNum++;
		pHevcCtx->PicOutCounter++;
    }
    else
    {
        FSP_SetDisplay(pHevcCtx->ChanID, pOutFrameStore->logic_fs_id, 0);
        dprint(PRN_ERROR, "%s: ImgErrorLevel = %d, OutErrThr:%d, discarded!\n", __func__, pImg->error_level, pHevcCtx->pstExtraData->s32OutErrThr);
        return HEVC_DEC_ERR;
    }

    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_FirstFrameFastOut()
*      功能描述 :  第一帧快速输出
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 成功返回;
*                  other: 异常错误
************************************************************************
*/
SINT32 HEVC_FirstFrameFastOut(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;

    /* 先直接输出 */
    ret = HEVC_OutputCurrPic(pHevcCtx);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_ERROR, "%s output current picture failed\n", __func__);
    }
    else
    {
        /* 标记是快速输出帧，这种帧虽被输出，但在经历正常输出序后才能从DPB中删除，比较特殊 */
        pHevcCtx->CurrPic.frame_store->eFirstFrameState = FIRST_FRAME_ALREADY_OUT;
        pHevcCtx->FirstFrameState = FIRST_FRAME_PROCESSED;
        pHevcCtx->LastDisplayPoc = pHevcCtx->CurrPic.thispoc;
        pHevcCtx->CurrPic.frame_store->is_displayed = 1;
    }

    return ret;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_SimpleDPBProcess()
*      功能描述 :  Simple DPB处理函数
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 成功返回;
*                  other: 异常错误

  为可视对讲定制的简化DPB处理，目的是做到误码时不发I帧也能解码，旁路原DPB
  管理机制，仅用滑窗方式管理参考帧.原来处理没有区分是否参考全做slide DPB, 
  实际上非参考帧不能参与滑窗，否则挤掉了真正的参考帧. 云游戏SVC-T就有这种情形. 
  解决方法是加上是否被参考的判断。

************************************************************************
*/
SINT32 HEVC_SimpleDPBProcess(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    
    if (0 != pHevcCtx->CurrPic.is_ref_idc)
    {
        HEVC_SimpleSlideDPB(pHevcCtx);
    
        /*把当前图像存入DPB*/
        ret = HEVC_InsertFrmInDPB(pHevcCtx,pHevcCtx->DPB.used_size, &pHevcCtx->CurrPic);
        if (HEVC_DEC_NORMAL != ret) 
        {
            dprint(PRN_FATAL,"%s %d: InsertFrmInDPB failed, return %d\n", __func__, __LINE__, ret);
            return HEVC_APC_ERR;
        }
    }
    else
    {
        pHevcCtx->CurrPic.frame_store->eFrameStoreState = FS_DISPLAY_ONLY;
    }
    
    /*输出当前图像*/
    pHevcCtx->CurrPic.frame_store->is_displayed = 1;
    ret = HEVC_CheckFrameStore(pHevcCtx, pHevcCtx->CurrPic.frame_store);
    if (HEVC_DEC_ERR == ret)
    {
        dprint(PRN_FATAL,"%s call HEVC_CheckFrameStore failed!\n", __func__);
        return HEVC_DEC_ERR;
    }
    else if (HEVC_ERR_FS_OUT_AGAIN == ret)
    {
        return HEVC_DEC_NORMAL;
    }
    else
    {
        ret = HEVC_OutputCurrPic(pHevcCtx);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_FATAL, "%s output current picture failed\n", __func__);
            return HEVC_DEC_ERR;
        }
    }

    return ret;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_DecOrderProcess()
*      功能描述 :  解码序输出处理函数
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 成功返回;
*                  other: 异常错误
************************************************************************
*/
SINT32 HEVC_DecOrderProcess(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    
    /*清空已经输出且不做参考的图像，可以不必等到DPB满的时候清除*/
    if (pHevcCtx->DPB.used_size >= pHevcCtx->DPB.size)
    {
        HEVC_RemoveUnusedApcStore(pHevcCtx);
        ret = HEVC_RemoveUnUsedFrameStore(pHevcCtx);
        if (ret != HEVC_TRUE)
        {
            dprint(PRN_FATAL,"%s call HEVC_RemoveUnUsedFrameStore Failed.\n", __func__);
        }   
    }
    
    /*把当前图像存入DPB*/
    ret = HEVC_InsertFrmInDPB(pHevcCtx,pHevcCtx->DPB.used_size, &pHevcCtx->CurrPic);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_FATAL,"%s call HEVC_InsertFrmInDPB Failed.\n", __func__);
        return HEVC_DEC_ERR;
    }
    
    /*输出当前图像*/
    ret = HEVC_CheckFrameStore(pHevcCtx, pHevcCtx->CurrPic.frame_store);
    if (HEVC_DEC_ERR == ret)
    {
        dprint(PRN_FATAL,"%s call HEVC_CheckFrameStore failed!\n", __func__);
        return HEVC_DEC_ERR;
    }
    else if (HEVC_ERR_FS_OUT_AGAIN == ret)
    {
        return HEVC_DEC_NORMAL;
    }
    else
    {
        ret = HEVC_OutputCurrPic(pHevcCtx);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_FATAL, "%s output current picture failed\n", __func__);
            return HEVC_DEC_ERR;
        }
    }

    return ret;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_SimpleDPBProcess()
*      功能描述 :  Simple DPB处理函数
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 成功返回;
*                  other: 异常错误
************************************************************************
*/
SINT32 HEVC_DispOrderProcess(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    
#if 1
    /*HEVC很多码流解码序第一帧不是显示序第一帧，使能后导致个别码流闪屏现象*/
    if (pHevcCtx->pstExtraData->s8SpecMode != 1)
    {
        /*第一帧快速输出处理: 回归采用的Allegro码流，解码序第一帧未必是显示序第一帧，所以不使能*/
        if (pHevcCtx->FirstFrameState != FIRST_FRAME_PROCESSED) 
        {
            ret = HEVC_FirstFrameFastOut(pHevcCtx);
            if (HEVC_DEC_NORMAL != ret)
            {
                dprint(PRN_FATAL,"%s call HEVC_FirstFrameFastOut Failed\n", __func__);
                return HEVC_DEC_ERR;
            }
        }
    }
#endif
 
    /*清空已经输出且不做参考的图像，可以不必等到DPB满的时候清除*/
    if (pHevcCtx->DPB.used_size >= pHevcCtx->DPB.size)
    {
        HEVC_RemoveUnusedApcStore(pHevcCtx);
        ret = HEVC_RemoveUnUsedFrameStore(pHevcCtx);
        if (ret != HEVC_TRUE)
        {
        	dprint(PRN_FATAL,"DPB.used_size may bigger than DPB.size\n");
        }	
    }
      
    /*把当前图像存入DPB*/
    ret = HEVC_InsertFrmInDPB(pHevcCtx,pHevcCtx->DPB.used_size, &pHevcCtx->CurrPic);
	if (HEVC_DEC_NORMAL != ret)
    {
	    dprint(PRN_FATAL,"HEVC_InsertFrmInDPB Failed, ret = %d\n", ret);
        return HEVC_DEC_ERR;
    }

    /*输出DPB中该显示的图像*/    
    if (pHevcCtx->DPB.used_size)    
    {        
        ret = HEVC_OutputFrmFromDPB(pHevcCtx);        
        if (HEVC_DEC_NORMAL != ret)        
        {            
            dprint(PRN_ERROR,"%s call HEVC_OutputFrmFromDPB failed\n", __func__);        
            return HEVC_DEC_ERR;       
        }    
    }   
     
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_GetFreeFrameStoreNum(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i = 0;
    SINT32 ret_value = 0;

    for (i=0; i<HEVC_MAX_FRAME_STORE; i++)
    {
        if (FS_NOT_USED == pHevcCtx->FrameStore[i].eFrameStoreState && (1 == HEVC_IsOutDPB(pHevcCtx, &pHevcCtx->FrameStore[i])))
        {
           ret_value++; 
        }
    }

    return ret_value;
}

/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_StorePicInDPB()
*      功能描述 :  把当前图像存入DPB
*      参数说明 :  无 
*      返回值   ： HEVC_DEC_NORMAL: 配成功;
*                  DPB_ERR: 在存入DPB时发现DPB出现重大错误，需要firmware重启
*                  HEVC_OUT_FLAG: 检测到适配层需要退出，返回该标志
************************************************************************
*/
#define HEVC_STORE_PIC_RET(ret_val) \
        do { \
            ret = ret_val;\
            dprint(PRN_DPB,"HEVC_StorePicInDpb return(%d) from L%d\n",ret_val, __LINE__); \
            goto store_pic_exit;\
        } while(0)
        
SINT32 HEVC_StorePicInDPB(HEVC_CTX_S *pHevcCtx, LUMA_INFO_S *pLumaInfo)
{
    SINT32 ret = HEVC_DEC_ERR;

  #if (TEST_PRINT_ENABLE == 1)
    dprint(PRN_ALWS,"PIC=%d, POC=%d, TYPE=%d, IsRef=%d, ImgID=%d, ERROR=%d\n", pHevcCtx->TotalPicNum-1, pHevcCtx->CurrPic.thispoc, pHevcCtx->CurrPic.pic_type, pHevcCtx->CurrPic.is_ref_idc, pHevcCtx->CurrPic.fs_image.image_id, pHevcCtx->CurrPic.err_level);
  #endif

    /******************** 处理流程0: 图像输出前处理 ****************************/
	/* 清空填充的参考帧 */
	HEVC_RemoveDummyFrame(pHevcCtx);

    /* 容错: 空图像直接丢弃 */
    if (HEVC_PIC_EMPTY == pHevcCtx->CurrPic.state)
    {
		dprint(PRN_ERROR,"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_NORMAL\n", __func__);
        return HEVC_DEC_NORMAL;    
    }
    
    /* 图像错误率门限控制 */
    if (pHevcCtx->CurrPic.err_level > pHevcCtx->pstExtraData->s32OutErrThr)
    {
        HEVC_ClearCurrPic(pHevcCtx);
		dprint(PRN_ERROR,"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\n", pHevcCtx->CurrPic.err_level, pHevcCtx->pstExtraData->s32OutErrThr);
        return HEVC_DEC_NORMAL;  
    }

    
    /******************** 处理流程1: I帧模式下直接输出 *************************/
    if (I_MODE == pHevcCtx->OldDecMode)
    {
        ret = HEVC_IModeProcess(pHevcCtx);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_FATAL,"%s call HEVC_IModeProcess Failed\n", __func__);
        }
        /* 处理完毕，直接退出 */
        HEVC_STORE_PIC_RET(ret);
    }


    /******************** 处理流程2: SIMPLE_DPB的特殊处理 **********************/ 
    if (DEC_ORDER_SIMPLE_DPB == pHevcCtx->pstExtraData->s32DecOrderOutput)
    {
        ret = HEVC_SimpleDPBProcess(pHevcCtx);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_FATAL,"%s call HEVC_SimpleDPBProcess Failed\n", __func__);
        }
        /* 处理完毕，直接退出 */
        HEVC_STORE_PIC_RET(ret);
    }


    /******************** 处理流程3: 解码序输出的特殊处理 **********************/
    if (DEC_ORDER_NORMAL_DPB == pHevcCtx->pstExtraData->s32DecOrderOutput)  
    {
        ret = HEVC_DecOrderProcess(pHevcCtx);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_FATAL,"%s call HEVC_DecOrderProcess Failed\n", __func__);
        }
        /* 正常返回，继续往下走 */
    }


    /******************** 处理流程4: 显示序标准处理流程 ************************/
    if (NOT_DEC_ORDER == pHevcCtx->pstExtraData->s32DecOrderOutput) 
    {
        ret = HEVC_DispOrderProcess(pHevcCtx);
        if (HEVC_DEC_NORMAL != ret)
        {
            dprint(PRN_FATAL,"%s call HEVC_DispOrderProcess Failed\n", __func__);
        }
        /* 正常返回，继续往下走 */
    }


store_pic_exit:
	if (ret == HEVC_DEC_ERR)
	{
        /* 既然Store失败，该帧的帧存应该释放掉，免得引起虚拟帧存泄漏 */
        HEVC_ClearCurrPic(pHevcCtx);
		dprint(PRN_ERROR,"%s return HEVC_DEC_ERR\n", __func__);
	}
	pHevcCtx->CurrPic.state = HEVC_PIC_EMPTY;
    
    return ret;
}


/*!
************************************************************************
*      函数原型 :  VOID HEVC_UpdateReflist()
*      功能描述 :  更新DPB中短期参考列表
*      参数说明 :  无
*      返回值   ： 无
************************************************************************
*/
VOID HEVC_UpdateReflist(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i=0, j=0, k=0;
    HEVC_SHORT_TERM_RPSET_S *pRps = NULL;
    SINT32 poc;
    SINT32 val;
        
    pRps = &(pHevcCtx->CurrSlice.short_term_ref_pic_set);
    for (i=0; i<pRps->num_negative_pics; i++)
    {
        if (pRps->used_flag[i])
        {
            poc = pHevcCtx->CurrSlice.poc + pRps->delta_poc[i];
            for (j=0; j<pHevcCtx->DPB.used_size; j++)
            {
                if (poc == pHevcCtx->DPB.fs[j]->poc)
                {
                    pHevcCtx->DPB.fs[j]->is_reference = 1;
					/* 逻辑帧标记为待参考 */
					if (0 != pHevcCtx->DPB.fs[j]->is_reference)
					{
						FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id, 1);
					}

                    pHevcCtx->DPB.fs[j]->frame.is_short_term = 1;
                    pHevcCtx->DPB.fs[j]->frame.is_long_term  = 0;
                    pHevcCtx->DPB.fs_negative_ref[k++] = pHevcCtx->DPB.fs[j];
                    break;
                }
            }
        }
    }
    pHevcCtx->DPB.negative_ref_frames_in_buffer = k;
    while (k<(SINT32)pHevcCtx->DPB.size)
    {
        pHevcCtx->DPB.fs_negative_ref[k++] = (HEVC_FRAMESTORE_S *)NULL;
    }

    k = 0;
    val = pRps->num_negative_pics+pRps->num_positive_pics;
    for (; i<val; i++)
    {
        if (pRps->used_flag[i])
        {
            poc = pHevcCtx->CurrSlice.poc + pRps->delta_poc[i];
            for (j=0; j<pHevcCtx->DPB.used_size; j++)
            {	
                if (poc == pHevcCtx->DPB.fs[j]->poc)
                {
                    pHevcCtx->DPB.fs[j]->is_reference = 1;
					/* 逻辑帧标记为待参考 */
					if (0 != pHevcCtx->DPB.fs[j]->is_reference)
					{
						FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id, 1);
					}
                    pHevcCtx->DPB.fs[j]->frame.is_short_term = 1;
                    pHevcCtx->DPB.fs[j]->frame.is_long_term  = 0;
                    pHevcCtx->DPB.fs_positive_ref[k++] = pHevcCtx->DPB.fs[j];
                    break;                   
                }
            }
        }
    }
    pHevcCtx->DPB.positive_ref_frames_in_buffer = k;
		
    while (k<pHevcCtx->DPB.size)
    {
        pHevcCtx->DPB.fs_positive_ref[k++] = (HEVC_FRAMESTORE_S *)NULL;
    }
    
    return;
}


/*!
************************************************************************
*      函数原型 :  VOID HEVC_UpdateLTReflist()
*      功能描述 :  更新DPB中长期参考列表
*      参数说明 :  无
*      返回值   ： 无
************************************************************************
*/
VOID HEVC_UpdateLTReflist(HEVC_CTX_S *pHevcCtx)
{
    SINT32 i=0, j=0, k=0;
    SINT32 RpsPoc;
    SINT32 CurPoc;
    UINT8  DeltaPocMsbCycleLtFlag;
    SINT32 PocCycle;
    HEVC_SHORT_TERM_RPSET_S *pRps = NULL;
    HEVC_PIC_PARAM_SET_S    *pPPS = NULL;
	HEVC_SEQ_PARAM_SET_S    *pSPS = NULL;
	
	pPPS = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
	pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];
	PocCycle = 1 << pSPS->max_pic_order_cnt_lsb;
	
    pRps = &(pHevcCtx->CurrSlice.short_term_ref_pic_set);
    for (i=(SINT32)pRps->num_of_pics-1; i>(SINT32)(pRps->num_negative_pics+pRps->num_positive_pics-1); i--)
    {
        if (pRps->used_flag[i])
        {
            RpsPoc = pRps->poc[i];
            DeltaPocMsbCycleLtFlag = pHevcCtx->CurrSlice.CheckLTMSB[i];
			RpsPoc = DeltaPocMsbCycleLtFlag ? RpsPoc : RpsPoc&(PocCycle-1);
	
            for (j=0; j<(SINT32)pHevcCtx->DPB.used_size; j++)
            {
                CurPoc = pHevcCtx->DPB.fs[j]->poc;
                CurPoc = DeltaPocMsbCycleLtFlag ? CurPoc : CurPoc&(PocCycle-1);
                if (CurPoc == RpsPoc)
                {
                    pHevcCtx->DPB.fs[j]->is_reference = 1;
				
                    pHevcCtx->DPB.fs[j]->frame.is_short_term = 0;
                    pHevcCtx->DPB.fs[j]->frame.is_long_term  = 1;
                    pHevcCtx->DPB.fs_ltref[k++] = pHevcCtx->DPB.fs[j];
                    break;
                }
            }
        }
    }
    pHevcCtx->DPB.ltref_frames_in_buffer = k;
    while (k<(SINT32)pHevcCtx->DPB.size)
    {
        pHevcCtx->DPB.fs_ltref[k++] = (HEVC_FRAMESTORE_S *)NULL;
    }
    
    return;
}


/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_InsertFrmInDPB(HEVC_CTX_S *pHevcCtx,UINT32 pos, HEVC_CURRPIC_S *pCurrPic)
*   功能描述 :  插入一幅图像到pHevcCtx->DPB
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
SINT32 HEVC_InsertFrmInDPB(HEVC_CTX_S *pHevcCtx, UINT32 pos, HEVC_CURRPIC_S *pCurrPic)
{
    SINT32 ret;

    if (pos >= HEVC_MAX_DPB_NUM)
    {
        dprint(PRN_FATAL,"%s with invalid pos(%d)\n", __func__, pos);
        HEVC_ClearDPB(pHevcCtx);
        return HEVC_DEC_ERR;  
    }

    pHevcCtx->DPB.fs[pos] = pCurrPic->frame_store;
	
    pHevcCtx->DPB.fs[pos]->eFrameStoreState = FS_IN_DPB;
    
    // 逻辑帧标记为待参考
    FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[pos]->logic_fs_id, 1);
    pHevcCtx->DPB.fs[pos]->is_reference = (pCurrPic->is_ref_idc == 0)? 0: 1;

    pHevcCtx->DPB.fs[pos]->pmv_address_idc = pCurrPic->pmv_address_idc;
    pHevcCtx->DPB.fs[pos]->fs_image = pCurrPic->fs_image;//结构体直接相等，赋值?
    pHevcCtx->DPB.fs[pos]->err_level = pHevcCtx->DPB.fs[pos]->frame.err_level = pCurrPic->err_level;

    pHevcCtx->DPB.fs[pos]->frame.frame_store = pCurrPic->frame_store;
    pHevcCtx->DPB.fs[pos]->pic_type = pHevcCtx->DPB.fs[pos]->frame.pic_type = pCurrPic->pic_type;

    pHevcCtx->DPB.fs[pos]->poc = pCurrPic->thispoc;
    pHevcCtx->DPB.fs[pos]->frame.poc = pCurrPic->thispoc;

	// DPB按照poc递增排序
    qsort((VOID *)pHevcCtx->DPB.fs, (pos+1), sizeof(HEVC_FRAMESTORE_S*), compare_pic_by_poc_asc);
    
    pHevcCtx->DPB.used_size++;
    
    ret = HEVC_GetAPC(pHevcCtx, pCurrPic->frame_store);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_FATAL,"%s get APC error, ret %d\n", __func__, ret);
        HEVC_PrintDPBState(pHevcCtx);
        HEVC_ClearDPB(pHevcCtx);
        return HEVC_APC_ERR;
    }

    // 当前图像置空
    pCurrPic->state = HEVC_PIC_EMPTY;

    return HEVC_DEC_NORMAL;    
}


/*!
************************************************************************
*   函数原型 :  SINT32    HEVC_GetAPC(HEVC_CTX_S *pHevcCtx,HEVC_FRAMESTORE_S *pFrameStore)
*   功能描述 :  分配apc，没分到时返回错误
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
SINT32 HEVC_GetAPC(HEVC_CTX_S *pHevcCtx,HEVC_FRAMESTORE_S *pFrameStore)
{
    UINT32 i;
    FSP_LOGIC_FS_S *pstLogicFs = NULL;

    CHECK_NULL_PTR_ReturnValue(pFrameStore, HEVC_APC_ERR);

	for (i=0; i<pHevcCtx->APC.size; i++)
	{
		if (0 == pHevcCtx->APC.is_used[i])
		{
            //apc is not used, allocate 
            pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, pFrameStore->logic_fs_id);	
			if (NULL != pstLogicFs && NULL != pstLogicFs->pstDecodeFs)
			{
				pHevcCtx->APC.is_used[i] = 1;
				pHevcCtx->APC.idc[i] = pstLogicFs->pstDecodeFs->PhyFsID;
				pHevcCtx->APC.poc[i] = pFrameStore->poc;
				pHevcCtx->APC.used_size++;
				dprint(PRN_REF, "framestore %d allocate apc %d\n", pFrameStore->fs_image.image_id, i);
				pFrameStore->apc_idc = i;
			    return HEVC_DEC_NORMAL;
			}
			else
			{
                dprint(PRN_FATAL,"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%d, logic_fs=%p, dec_fs=%p)\n", 
                                  pFrameStore->logic_fs_id, pFrameStore->poc, pFrameStore->is_reference, pstLogicFs, 
                                 (pstLogicFs)? pstLogicFs->pstDecodeFs: NULL);
                return HEVC_APC_ERR;
			}
		}
	}
    
	return HEVC_APC_ERR;
}

/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_OutputFrmFromDPB()
*   功能描述 :  从pHevcCtx->DPB中输出一帧
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
SINT32 HEVC_OutputFrmFromDPB(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret = 0;
    UINT32 i;
    UINT32 Nodisplayed = 0;   
                
    for (i=0; i<pHevcCtx->DPB.used_size; i++)
    {
        if ((0 == pHevcCtx->DPB.fs[i]->is_displayed) && (pHevcCtx->DPB.fs[i]->poc > pHevcCtx->LastDisplayPoc))
        {
            Nodisplayed++;
        }
    }

	// num_reorder_pics 某一层,最多有多少个reorder pic 
	// Nodisplayed > pHevcCtx->CurrSPS.num_reorder_pics[pHevcCtx->CurrSlice.nuh_temporal_id] 
	// 保证后续帧不可能比送显帧的poc小,因为我们知道最多有多少个前序的帧了, dpb中有多余
	// 这个值的帧送显,则多余的帧必定可以输出
    for (i=0; i<pHevcCtx->DPB.used_size; i++)
    {
        if ((0 == pHevcCtx->DPB.fs[i]->is_displayed) 
         && (pHevcCtx->DPB.fs[i]->poc > pHevcCtx->LastDisplayPoc) 
            && (Nodisplayed > pHevcCtx->pCurrSPS->num_reorder_pics[pHevcCtx->CurrSlice.nuh_temporal_id])
         && (pHevcCtx->DPB.fs[i]->poc < pHevcCtx->CurrSlice.poc || pHevcCtx->bNoOutputOfPriorPicsFlag))
        {
            Nodisplayed--;
            pHevcCtx->DPB.fs[i]->is_displayed = 1;
            ret = HEVC_OutputFrmToVO(pHevcCtx,pHevcCtx->DPB.fs[i]);
            pHevcCtx->LastDisplayPoc = pHevcCtx->DPB.fs[i]->poc;
        }
        else if((0 == pHevcCtx->LastDisplayPoc) && (pHevcCtx->DPB.fs[i]->poc < pHevcCtx->LastDisplayPoc))
        {
            FSP_SetDisplay(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 0);
            dprint(PRN_FS,"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\n", __func__, pHevcCtx->LastDisplayPoc, pHevcCtx->DPB.fs[i]->poc);
            
        }
    }

    return ret;
}


SINT32 HEVC_OutputOneFrmFromDPB(HEVC_CTX_S *pHevcCtx, UINT32 pos)
{
	SINT32 ret;

	pHevcCtx->DPB.fs[pos]->is_displayed = 1;
	ret = HEVC_OutputFrmToVO(pHevcCtx, pHevcCtx->DPB.fs[pos]);
	// free frame store and move empty store to end of buffer
	if (!HEVC_FrameStoreRefFlg(pHevcCtx->DPB.fs[pos]))
	{
		HEVC_RemoveApcStore(pHevcCtx, pos);
		HEVC_RemoveFrameStoreOutDPB(pHevcCtx, pos);
	}

	return ret;
}


/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_FlushOutputFrmFromDPB()
*   功能描述 :  从pHevcCtx->DPB中输出所有帧
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/

SINT32 HEVC_FlushOutputFrmFromDPB(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;

    if (pHevcCtx == NULL)
    {
        return HEVC_DEC_ERR;
    }

    for (i = 0; i < pHevcCtx->DPB.used_size; i++)
    {
        FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 0);

        if (0 == pHevcCtx->DPB.fs[i]->is_displayed)
        {
            pHevcCtx->DPB.fs[i]->is_displayed = 1;

            if (HEVC_OutputFrmToVO(pHevcCtx, pHevcCtx->DPB.fs[i]) == HEVC_DEC_ERR)
            {
                dprint(PRN_FATAL, "%s: HEVC_OutputFrmToVO err!\n", __func__);
                return HEVC_DEC_ERR;
            }
        }
        else
		{
			if (FSP_GetDisplay(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id) != FS_DISP_STATE_WAIT_DISP)
			{
				FSP_SetDisplay(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 0);
			}
			
		}
    }

    pHevcCtx->LastDisplayPoc = -HEVC_MAX_INT;
    Hevc_InitDecBuffers(pHevcCtx);
    
    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_EmptyFrmFromDPB()
*   功能描述 :  从pHevcCtx->DPB中清空所有帧，不管有没有显示帧
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
SINT32 HEVC_EmptyFrmFromDPB(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;

    if (pHevcCtx == NULL)
    {
        return HEVC_DEC_ERR;
    }

    for (i = 0; i < pHevcCtx->DPB.used_size; i++)
    {
        if (0 == pHevcCtx->DPB.fs[i]->is_displayed)
        {
            pHevcCtx->DPB.fs[i]->is_displayed = 1;
        }
    }
    pHevcCtx->LastDisplayPoc = -HEVC_MAX_INT;

    // DPB refresh 清除逻辑帧存
	for (i=0; i<HEVC_MAX_DPB_NUM; i++)
	{
        if(pHevcCtx->DPB.fs[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[i]->logic_fs_id, 1);
        }
        if(pHevcCtx->DPB.fs_negative_ref[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs_negative_ref[i]->logic_fs_id, 1);
        }
        if(pHevcCtx->DPB.fs_positive_ref[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs_positive_ref[i]->logic_fs_id, 1);
        }
        if(pHevcCtx->DPB.fs_ltref[i] != NULL)
        {
            FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs_ltref[i]->logic_fs_id, 1);
        }
        pHevcCtx->DPB.fs[i] = pHevcCtx->DPB.fs_negative_ref[i] = pHevcCtx->DPB.fs_positive_ref[i] = pHevcCtx->DPB.fs_ltref[i] = NULL;
    }

    Hevc_InitDecBuffers(pHevcCtx);
	
    return HEVC_DEC_NORMAL;   
}

/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_OutputFrmToVO(HEVC_CTX_S *pHevcCtx,HEVC_FRAMESTORE_S *pFrameStore)
*   功能描述 :  输出一帧图像
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
SINT32 HEVC_OutputFrmToVO(HEVC_CTX_S *pHevcCtx,HEVC_FRAMESTORE_S *pFrameStore)
{
    SINT32 ret;
    IMAGE *pstLogicFsImage = NULL;
    
	HEVC_GetImagePara(pHevcCtx,pFrameStore);

    ret = HEVC_CheckFrameStore(pHevcCtx, pFrameStore);
    if (HEVC_DEC_NORMAL == ret)
    {
        FSP_SetDisplay(pHevcCtx->ChanID, pFrameStore->logic_fs_id, 1);
        pstLogicFsImage = FSP_GetFsImagePtr(pHevcCtx->ChanID, pFrameStore->logic_fs_id);
        if (NULL == pstLogicFsImage)
        {
            dprint(PRN_FATAL,"%s: pstLogicFsImage is NULL!\n", __func__);
            return HEVC_DEC_ERR;
        }

        ret = InsertImgToVoQueue(pHevcCtx->ChanID, VFMW_HEVC, pHevcCtx, &pHevcCtx->ImageQue, pstLogicFsImage);
        if (VF_OK != ret)
        {
            //插入队列超时且需要退出
            dprint(PRN_FATAL, "HEVC InsertVO Failed return %d, ClearAll\n", ret);
            FSP_SetDisplay(pHevcCtx->ChanID, pFrameStore->logic_fs_id, 0);
            HEVC_ClearAll(pHevcCtx,1);
            return HEVC_DEC_ERR;
        }
		HEVC_SetFrmRepeatCount(pHevcCtx, pstLogicFsImage);
        pHevcCtx->OutputFrameNum++;
		pHevcCtx->PicOutCounter++;
    }
    else if (HEVC_ERR_FS_OUT_AGAIN == ret)
    {
     /* pFrameStore可能已经输出，若如此这里必须及时中止输出帧的操作.
        已输出的帧又走到这里的原因是，某些帧虽已输出但仍作参考，
        所以还在DPB里，有可能再次被挑中尝试输出. */
        return HEVC_DEC_NORMAL;
    }
    else
    {
        dprint(PRN_ERROR, "HEVC.c line %d: frame para err(ret=%d), recycle image self\n", __LINE__, ret);
        HEVC_DECRecycleImage(pHevcCtx, pFrameStore->fs_image.image_id);
        return HEVC_DEC_ERR;  //OUT_FLAG
    }
    
    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
*   函数原型 :  SINT32 Check_FrameStore(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S * pFrameStore)
*   功能描述 :  检查该图像是否能够输出到VO对列
*   参数说明 :  
*   返回值   ： 0:可以输出;-1不能输出
************************************************************************
*/
SINT32 HEVC_CheckFrameStore(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S * pFrameStore)
{
    SINT8  already_output_flag = 0;
    FSP_LOGIC_FS_S *pstLogicFs = NULL;
    SINT32 return_value = HEVC_DEC_NORMAL; 

    pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, pFrameStore->logic_fs_id);
    if (pstLogicFs != NULL)
    {
        if ((pstLogicFs->s32DispState == FS_DISP_STATE_WAIT_DISP)
         || (pstLogicFs->s32DispState == FS_DISP_STATE_NOT_USED))
        {
            dprint(PRN_REF, "%s frame logic_fs_id=%d, state=%d\n", __func__, pFrameStore->logic_fs_id, pstLogicFs->s32DispState);
            already_output_flag = 1;
        }
    }
    else
    {
        dprint(PRN_ERROR,"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null, logic_fs_id = %d\n", pFrameStore, pFrameStore->poc, pFrameStore->eFirstFrameState, pFrameStore->logic_fs_id);
        already_output_flag = 1;
    }
    
    /* 如果该帧是快速输出帧则标记它已经经历了正常输出序，后续不再强求它依然呆在DPB里. */
    if (pFrameStore->eFirstFrameState == FIRST_FRAME_WAIT_OUT)
    {
        pFrameStore->is_displayed = 1;
        pFrameStore->eFirstFrameState = FIRST_FRAME_ALREADY_OUT;
        return HEVC_ERR_FS_OUT_AGAIN;
    }

    if(already_output_flag == 1)
    {
        dprint(PRN_ERROR, "%s frame poc=%d, is already output\n", __func__, pFrameStore->poc);
        return HEVC_ERR_FS_OUT_AGAIN;
    }
    
    // the control condition would added
    if ((FS_NOT_USED == pFrameStore->eFrameStoreState) || (1 == pFrameStore->non_existing))
    {
        dprint(PRN_ERROR, "%s frame(%p) invalid, state:%d, non_existing:%d\n", __func__, pFrameStore, pFrameStore->eFrameStoreState, pFrameStore->non_existing);
        return HEVC_DEC_ERR;
    }

    return return_value;
}


/*!
************************************************************************
*   函数原型 :  VOID HEVC_GetImagePara(HEVC_FRAMESTORE_S *pFrameStore)
*   功能描述 :  赋值要输出的framestore的fs_image结构体
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID   HEVC_GetImagePara(HEVC_CTX_S *pHevcCtx,HEVC_FRAMESTORE_S *pFrameStore)
{    
	UINT32 pic_type = pFrameStore->pic_type;
	IMAGE  *pstLogicFsImage = NULL;

    UINT32 source_scan_type = 0;
    //clean format
    pFrameStore->fs_image.format &= HEVC_CLEAN_TOP_FILED_FIRST;
    pFrameStore->fs_image.format &= HEVC_CLEAN_FIELD_VALID;
    pFrameStore->fs_image.format &= HEVC_CLEAN_SOURCE_FORMAT;
    pFrameStore->fs_image.format &= HEVC_CLEAN_FRAME_TYPE;

	pFrameStore->fs_image.frame_rate = 25*1024;

    if (1 == pHevcCtx->pCurrVPS->profile_tier_level.general_progressive_source_flag && 0 == pHevcCtx->pCurrVPS->profile_tier_level.general_interlaced_source_flag)
    {
        source_scan_type = 0;
    }
    else if (0 == pHevcCtx->pCurrVPS->profile_tier_level.general_progressive_source_flag && 1 == pHevcCtx->pCurrVPS->profile_tier_level.general_interlaced_source_flag)
    {
        source_scan_type = 1;
    }
    else if (1 == pHevcCtx->pCurrVPS->profile_tier_level.general_progressive_source_flag && 1 == pHevcCtx->pCurrVPS->profile_tier_level.general_interlaced_source_flag && 0 == pHevcCtx->SEI.pic_timming.source_scan_type)
    {
        source_scan_type = 1;
    }
    else if (1 == pHevcCtx->pCurrVPS->profile_tier_level.general_progressive_source_flag && 1 == pHevcCtx->pCurrVPS->profile_tier_level.general_interlaced_source_flag && 1 == pHevcCtx->SEI.pic_timming.source_scan_type)
    {
        source_scan_type = 0;
    }

    pFrameStore->fs_image.format = pFrameStore->fs_image.format |
                                   (2 & 0x3) << 12 |
                                   (3 & 0x3) << 10 |
                                   (source_scan_type & 0x3) << 8  |
                                   (pic_type & 0x3);

    if (pFrameStore->eFrameStoreState != FS_NOT_USED)
    {
        pFrameStore->fs_image.error_level = pFrameStore->err_level;
    }   
    
    pstLogicFsImage = FSP_GetFsImagePtr(pHevcCtx->ChanID, pFrameStore->logic_fs_id);
    if (NULL != pstLogicFsImage)
    {
        memcpy(pstLogicFsImage, &pFrameStore->fs_image, sizeof(IMAGE));
    }
    
    return;
}

/*!
************************************************************************
*   函数原型 :  VOID HEVC_CheckOutputImage(UINT32 PicID)
*   功能描述 :  hevc回收VO已经显示且不被参考的图像槽位
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
SINT32 HEVC_CheckOutputImage(HEVC_CTX_S *pHevcCtx,UINT32 PicID)
{
    // if the frame is ref-frame then is_in_dpb = 1, else is_in_dpb = 0;
    if (PicID >= HEVC_MAX_FRAME_STORE)
    {
        return HEVC_DEC_ERR;
    }
    if (pHevcCtx->FrameStore[PicID].is_reference > 0)
    {
        // not eraser image
        return 1;
    }
    else
    {
        // eraser image
        return 0;
    }    
}


/*!
************************************************************************
*   函数原型 :  VOID HEVC_DECRecycleImage(UINT32 PicID)
*   功能描述 :  hevc回收VO已经显示的图像槽位
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
SINT32 HEVC_DECRecycleImage(HEVC_CTX_S *pHevcCtx,UINT32 PicID)
{
    UINT32 i;
    FSP_LOGIC_FS_S *pstLogicFs = NULL;

    /* 找到PicID所对应的逻辑帧存，从而找到image结构体，这样才能释放image所附带的userdata */
    pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, PicID);
    if (NULL != pstLogicFs)
    {
        /* 检查这个逻辑帧存是否正在等待显示释放 */
        if (pstLogicFs->s32DispState == FS_DISP_STATE_NOT_USED)
        {
        	dprint(PRN_ERROR,"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STATE_NOT_USED\n");
            return HEVC_DEC_ERR;
        }

        /* 释放userdata */
        for (i = 0; i < 4; i++)
        {
            if (NULL != pstLogicFs->stDispImg.p_usrdat[i])
            {
                FreeUsdByDec(pHevcCtx->ChanID, pstLogicFs->stDispImg.p_usrdat[i]);
                pstLogicFs->stDispImg.p_usrdat[i] = NULL;
            }
        }

        /* 将图像'PicID'标记为"显示结束" */
        FSP_SetDisplay(pHevcCtx->ChanID, PicID, 0);
        return HEVC_DEC_NORMAL;
    }
    
    return HEVC_DEC_ERR;
}


SINT32 HEVC_ArrangeVahbMem(HEVC_CTX_S *pHevcCtx,UINT32 ImgWidth, UINT32 ImgHeight, UINT32 ImgWidthInCtb, UINT32 ImgHeightInCtb, UINT32 ImgNum, UINT32 PmvBlkNum)
{
    SINT32 Ret, UsedMemSize;
    FSP_INST_CFG_S FspInstCfg;
    
    memset(&FspInstCfg, 0, sizeof(FSP_INST_CFG_S));
    FspInstCfg.s32DecFsWidth        = ImgWidth;
    FspInstCfg.s32DecFsHeight       = ImgHeight;
    FspInstCfg.s32DispFsWidth       = ImgWidth;
    FspInstCfg.s32DispFsHeight      = ImgHeight;
    FspInstCfg.s32ExpectedDecFsNum  = (pHevcCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 0: (pHevcCtx->DPB.size);  //(pHevcCtx->DPB.size+1) H265没有场，不用+1
    FspInstCfg.s32ExpectedDispFsNum = 5;
    FspInstCfg.s32ExpectedPmvNum    = (pHevcCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 1: PmvBlkNum;
	
    /* 配置FSP实例，并分割帧存 */
    if (FSP_OK == FSP_ConfigInstance(pHevcCtx->ChanID, &FspInstCfg))
    {
        Ret = FSP_PartitionFsMemory(pHevcCtx->ChanID, pHevcCtx->pstExtraData->s32SyntaxMemAddr, pHevcCtx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
        if (Ret != FSP_OK)
        {
            // 分割帧存失败，返回
            return VF_ERR_SYS; 
        }
    }
	else
	{
	    dprint(PRN_ERROR, "ERROR: HEVC FSP_ConfigInstance fail!\n");
	    return VF_ERR_SYS;
	}
        
    return VF_OK;
}

/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_AllocFrameStore()
*      功能描述 :  给当前图像分配一个帧存空间,pmv槽位
*      参数说明 :  无 
*      返回值   ： DEC_NORMAL:配成功;
*                  FS_ALLOC_ERR:能分配到PMV槽位,解码错误得不可恢复，
*                               需要重新启动解码（从某种程度上说该
*                               类错误出现，必定是出现了bug需要定位
*                               解决）
*                  OUT_FLAG: 检测到适配层需要退出，返回该标志               
************************************************************************
*/
SINT32 HEVC_AllocFrameStore(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i = 0;
    SINT32 LogicFsID = 0;
    FSP_LOGIC_FS_S *pstLFs = NULL;	
	IMAGE *pstImg = NULL;
	UINT32 HeightAligh;
	UINT32 ChromOffset;

    // Allocate frame store
    pHevcCtx->CurrPic.state = HEVC_PIC_EMPTY;

	// 找一个没有用到的帧存给当前帧
    for (i=0; i<HEVC_MAX_FRAME_STORE; i++)
    {
        if (FS_NOT_USED == pHevcCtx->FrameStore[i].eFrameStoreState && (1 == HEVC_IsOutDPB(pHevcCtx, &pHevcCtx->FrameStore[i])))
        {
            /* error_level必须标记为有错，否则在解gap，或者其它原因其实并未解码
               但发生了StorePicInDPB()的操作，则这个本当不该输出的图有可能被输出*/
            pHevcCtx->CurrPic.err_level                        = 101;
            pHevcCtx->CurrPic.state                            = HEVC_PIC_DECODING;
            
            pHevcCtx->CurrPic.fs_image                         = pHevcCtx->FrameStore[i].fs_image;
            pHevcCtx->CurrPic.fs_image.error_level             = 0;
            
            pHevcCtx->CurrPic.frame_store                      = &pHevcCtx->FrameStore[i];
            pHevcCtx->CurrPic.frame_store->err_level           = 0;
            pHevcCtx->CurrPic.frame_store->is_displayed        = 0;
			pHevcCtx->CurrPic.frame_store->non_existing        = 0;
			pHevcCtx->CurrPic.frame_store->frame.is_long_term  = 0;
            pHevcCtx->CurrPic.frame_store->frame.is_short_term = 0;
            pHevcCtx->CurrPic.frame_store->eFirstFrameState    = FIRST_FRAME_OUT_INIT;
            break;
        }
    }
    
    if (pHevcCtx->CurrPic.state != PIC_DECODING)
	{
        dprint(PRN_FATAL, "FS_ALLOC_ERR, ClearAll\n");
        return HEVC_FS_ALLOC_ERR;	
	}

	/* FrameStore申请到之后, 还要新建逻辑帧存，这样才能得到真正的地址 */
    
	// 获取逻辑帧存 
	LogicFsID = FSP_NewLogicFs(pHevcCtx->ChanID, 1);
	pstLFs = FSP_GetLogicFs(pHevcCtx->ChanID, LogicFsID);
	if (LogicFsID >= 0 && NULL != pstLFs)
	{
		if (pHevcCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION)
		{
			pstImg = &pstLFs->stDispImg;

            HeightAligh = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;
			ChromOffset = HeightAligh*pstImg->image_stride;
            pstImg->image_width 	   = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
			pstImg->image_height	   = HeightAligh;

			pstImg->chrom_phy_addr	   = pstImg->luma_phy_addr + ChromOffset;
			pstImg->top_chrom_phy_addr = pstImg->top_luma_phy_addr + ChromOffset;
			pstImg->btm_chrom_phy_addr = pstImg->top_chrom_phy_addr + pstImg->image_stride;
			pstImg->chrom_2d_phy_addr  = pstImg->luma_2d_phy_addr + ChromOffset;
		}
		/* FrameStore与fs_image不再具有一一对应关系，为延续已有处理，把新的image拷贝过来 */
		memcpy(&pHevcCtx->CurrPic.frame_store->fs_image, &pstLFs->stDispImg, sizeof(IMAGE));
		memcpy(&pHevcCtx->CurrPic.fs_image, &pHevcCtx->CurrPic.frame_store->fs_image, sizeof(IMAGE));
	
		pHevcCtx->CurrPic.frame_store->logic_fs_id = LogicFsID;	
		pHevcCtx->CurrPic.pmv_address_idc = pstLFs->PmvIdc;
	}
	else
	{
		pHevcCtx->CurrPic.state = HEVC_PIC_EMPTY;
		dprint(PRN_FATAL, "Can not new logic fs! ClearAll\n");
		//HEVC_ClearAll(pHevcCtx,1);
		return HEVC_FS_ALLOC_ERR;
	}

	return HEVC_DEC_NORMAL;
}


UINT32 HEVC_IsVoFinish(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;
    FSP_LOGIC_FS_S *pstLogicFs = NULL;
    
    dprint(PRN_ERROR, "FSP_GetFspType -1\n");
    return -1;

    for (i =0; i<MAX_FRAME_NUM; i++)
    {
        /* 找到PicID所对应的逻辑帧存，从而找到image结构体，这样才能释放image所附带的userdata */
        pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, i);
        if(NULL == pstLogicFs)
        {
            dprint(PRN_ERROR, "FSP_GetLogicFs return NULL\n");
            return -1;
        }
        if (pstLogicFs->s32DispState == FS_DISP_STATE_WAIT_DISP)
        {
            return 0;
        }
    }

    return 1;
}

VOID HEVC_GetBackPicFromVOQueue(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;
    UINT32 usrdat_idx;

    // clean VO queue
    ResetVoQueue(&pHevcCtx->ImageQue);

    // clean all frame store
    for (i=0; i<HEVC_MAX_FRAME_STORE; i++)
    {
        pHevcCtx->FrameStore[i].is_reference = 0;
        pHevcCtx->FrameStore[i].eFrameStoreState = FS_NOT_USED;
        for (usrdat_idx=0; usrdat_idx <4; usrdat_idx++)
        {
            if (NULL != pHevcCtx->FrameStore[i].fs_image.p_usrdat[usrdat_idx])
            {
                FreeUsdByDec(pHevcCtx->ChanID, pHevcCtx->FrameStore[i].fs_image.p_usrdat[usrdat_idx]);
                pHevcCtx->FrameStore[i].fs_image.p_usrdat[usrdat_idx] = NULL;
            }
        }   
    }

    // clean all pmv store
    for (i=0; i<pHevcCtx->TotalPmvNum; i++)
    {
        pHevcCtx->PmvStoreUsedFlag[i] = 0;
    }    

    return;
}

/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_RemoveUnUsedFrameStore()
*   功能描述 :  清除已经从pHevcCtx->DPB输出的非参考帧，针对已经vo显示与否两种情况对frame store 参数赋值
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
UINT32 HEVC_RemoveUnUsedFrameStore(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i, j, record_used_size;
    UINT32 IsRemoved = HEVC_FALSE;
    FSP_LOGIC_FS_S  *pstLogicFs = NULL;

    // check for frames that were already output and no longer used for reference
    /* DPB.used_size不能直接作为如下循环的控制变量，这是因为Remove操作本身会使used_size减1，
       若用它作循环控制变量，会使得DPB中的某些帧实际上并未遍历到，从而导致本该从DPB删除的帧依然留在DPB里. 
       这样，DPB和FSP的信息是冲突的，可以引发很多问题.
       同州卡顿码流即由此引起，原因是FSP和DPB冲突造成GetAPC()失败，进而清除了DPB，导致丢帧. */
    record_used_size = pHevcCtx->DPB.used_size;
    for (i=0,j=0; i<record_used_size; i++)
    {
        if((pstLogicFs = FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[j]->logic_fs_id)) != NULL)
        {
            /* 如果fsp帧存已经空闲，要确保该帧立即从DPB中删除 */
            if ((0 == pstLogicFs->s32IsRef)
             && (FS_DISP_STATE_NOT_USED == pstLogicFs->s32DispState ||  FS_DISP_STATE_WAIT_DISP == pstLogicFs->s32DispState)
             && (FIRST_FRAME_WAIT_OUT != pHevcCtx->DPB.fs[j]->eFirstFrameState))
            {
                pHevcCtx->DPB.fs[j]->logic_fs_id  = -1;
                pHevcCtx->DPB.fs[j]->is_reference = 0;
                pHevcCtx->DPB.fs[j]->is_displayed = 1;
            }
        }
        else
        {
            if (pHevcCtx->DPB.fs[j]->eFirstFrameState != FIRST_FRAME_WAIT_OUT)
            {
                pHevcCtx->DPB.fs[j]->logic_fs_id  = -1;
                pHevcCtx->DPB.fs[j]->is_reference = 0;
                pHevcCtx->DPB.fs[j]->is_displayed = 1;
            }
        }

        if ((0 == pHevcCtx->DPB.fs[j]->is_reference) 
         && (1 == pHevcCtx->DPB.fs[j]->is_displayed))
        {
            HEVC_RemoveFrameStoreOutDPB(pHevcCtx, j);
            IsRemoved = HEVC_TRUE;
        }
        else
        {
            j++;
        }
    }
    
    return IsRemoved;
}


/*!
************************************************************************
*   函数原型 :  VOID HEVC_RemoveFrameStoreOutDPB(UINT32 pos)
*   功能描述 :  将framestore指针移出dpb
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID HEVC_RemoveFrameStoreOutDPB(HEVC_CTX_S *pHevcCtx,UINT32 pos)
{
    UINT32 i;
    FSP_LOGIC_FS_S *pstLogic = NULL;

    pHevcCtx->DPB.fs[pos]->eFrameStoreState = FS_NOT_USED;
	
    pstLogic = FSP_GetLogicFs(pHevcCtx->ChanID, pHevcCtx->DPB.fs[pos]->logic_fs_id);
	if (NULL != pstLogic)
	{
		if (FS_DISP_STATE_WAIT_DISP != pstLogic->s32DispState)
		{
			FSP_SetDisplay(pHevcCtx->ChanID, pHevcCtx->DPB.fs[pos]->logic_fs_id, 0);
		}
		FSP_SetRef(pHevcCtx->ChanID, pHevcCtx->DPB.fs[pos]->logic_fs_id, 0);
	}

    //frame sort
    for (i=pos; i<= (pHevcCtx->DPB.used_size-1); i++)
    {
        pHevcCtx->DPB.fs[i] = pHevcCtx->DPB.fs[i+1];
    }
    pHevcCtx->DPB.fs[pHevcCtx->DPB.used_size-1] = (HEVC_FRAMESTORE_S *)NULL;
    pHevcCtx->DPB.used_size--;    

    return;    
}


/*!
************************************************************************
*   函数原型 :  SINT32 HEVC_GetMinPOC(SINT32 *poc, SINT32 *pos)
*   功能描述 :  找出最小poc 和最小poc图像位置
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID HEVC_GetMinPOC(HEVC_CTX_S *pHevcCtx,SINT32 *poc, UINT32 *pos)
{
    UINT32 i;
    
    *pos = 0;
    *poc = 0x7fffffff;
    
    if (pHevcCtx->DPB.used_size > pHevcCtx->DPB.size)
    {
        dprint(PRN_ERROR, "%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), error resilence.\n", pHevcCtx->DPB.used_size, pHevcCtx->DPB.size);
        pHevcCtx->DPB.used_size = pHevcCtx->DPB.size; // for error resilence
    }
    for (i=0; i<pHevcCtx->DPB.used_size; i++)
    {
        if (*poc>pHevcCtx->DPB.fs[i]->poc)
        {
            *poc = pHevcCtx->DPB.fs[i]->poc;
            *pos = i;
        }
    }

    return;
}


/*!
************************************************************************
*      函数原型 :      SINT32 HEVC_GetReRangeFlag()
*      功能描述 :  判断帧存空间是否要重新分配
*      参数说明 :  
*      返回值   ： 
************************************************************************
*/
SINT32 HEVC_GetReRangeFlag(HEVC_CTX_S *pHevcCtx,SINT32 OldWidth,SINT32 OldHeight, SINT32 OldLog2CtbSizeY)
{
    SINT32 ReRangeFlag;
    HEVC_SEQ_PARAM_SET_S *sps;
    HEVC_PIC_PARAM_SET_S *pps;
    UINT32 neww, newh;

    ReRangeFlag = 0;
    pps = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
    sps = &pHevcCtx->pSPS[pps->seq_parameter_set_id];
    neww = sps->pic_width_in_luma_samples;
    newh = sps->pic_height_in_luma_samples;

    if (sps->dpbsize_changed || (neww!= OldWidth) || (newh != OldHeight) || (!pHevcCtx->AllowStartDec))
    {
        //dprint(PRN_ALWS,"HEVC_GetReRangeFlag ReRangeFlag=1(dpbsize_changed:%d, resolution:%dx%d->%dx%d, log2_ctb_sizeY:%d->%d\n",sps->dpbsize_changed, OldWidth,OldHeight,neww,newh,OldLog2CtbSizeY,sps->log2_ctb_sizeY);
        ReRangeFlag = 1;
    }
    
    return ReRangeFlag;
}


VOID HEVC_CalcStreamBits(HEVC_CTX_S *pHevcCtx)
{
    UINT32 code_len_byte;
    UINT32 i;
    UINT8* VirAddr = NULL;

    VirAddr = pHevcCtx->pCurrNal->stream[0].streamBuffer + (pHevcCtx->pBS->TotalPos + 7)/8;

    // calculate bytes used before curr segment
    code_len_byte = 0;
    for (i=0; i<(UINT32)pHevcCtx->pCurrNal->nal_used_segment; i++)
    {
        code_len_byte += pHevcCtx->pCurrNal->stream[i].bitstream_length;  //length of nal in byte,2 nals起作用，when 1 nal,code_len_byte = 0
    }

    pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bitsoffset   = pHevcCtx->pBS->TotalPos&7;
    pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bytespos     = pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].stream_phy_addr + (pHevcCtx->pBS->TotalPos/8 - code_len_byte);
    pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].valid_bitlen = pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bitstream_length*8 - (pHevcCtx->pBS->TotalPos - code_len_byte*8);
    
    //16byte 对齐
#if 0

    while ((pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bytespos & 3) != 0)
    {
        pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bitsoffset += 8;
        pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bytespos--;
    }

#endif
    pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bitsoffset += 8 * (pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bytespos & 3);
    pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bytespos = ((pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_used_segment].bytespos) & (~3));

    // last sement sub trailing zeros, when cavlc sun stop one
    if (pHevcCtx->pCurrNal->nal_segment != 1 && pHevcCtx->pCurrNal->nal_segment != 2)
    {
        dprint(PRN_FATAL, "nal_segment = %d is not expected value\n", pHevcCtx->pCurrNal->nal_segment);
        return;
    }

    // other segment bitsoffset and so on
    for (i = pHevcCtx->pCurrNal->nal_used_segment + 1; (i < pHevcCtx->pCurrNal->nal_segment) && (i < 2); i++)
    {
        pHevcCtx->pCurrNal->stream[i].bitsoffset = 0;
        pHevcCtx->pCurrNal->stream[i].bytespos = pHevcCtx->pCurrNal->stream[i].stream_phy_addr;
        pHevcCtx->pCurrNal->stream[i].valid_bitlen = pHevcCtx->pCurrNal->stream[i].bitstream_length * 8;
#if 0

        while ((pHevcCtx->pCurrNal->stream[i].bytespos & HEVC_STREAM_BASE_ALIGN) != 0)
        {
            pHevcCtx->pCurrNal->stream[i].bitsoffset += 8;
            pHevcCtx->pCurrNal->stream[i].bytespos--;
        }

#endif
        pHevcCtx->pCurrNal->stream[i].bitsoffset += 8 * (pHevcCtx->pCurrNal->stream[i].bytespos & HEVC_STREAM_BASE_ALIGN);
        pHevcCtx->pCurrNal->stream[i].bytespos = pHevcCtx->pCurrNal->stream[i].bytespos & (~HEVC_STREAM_BASE_ALIGN);
    }

    // last segment sub trailing zeros, when cavlc sun stop one
    pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_segment-1].valid_bitlen -= pHevcCtx->pCurrNal->nal_trail_zero_bit_num;

    // find stream_base_addr
    for (i=pHevcCtx->pCurrNal->nal_used_segment; i<pHevcCtx->pCurrNal->nal_segment; i++)
    {
        if (pHevcCtx->pCurrNal->stream[i].bytespos < pHevcCtx->CurrPic.stream_base_addr)
        {
            //HEVC_StreamAddr_ReW(pHevcCtx,pHevcCtx->pCurrNal->stream[i].bytespos,pHevcCtx->CurrPic.stream_base_addr);
            pHevcCtx->CurrPic.stream_base_addr = pHevcCtx->pCurrNal->stream[i].bytespos;
        }
    }  

    return;
}


SINT32 HEVC_VpsSpsPpsCheck(HEVC_CTX_S *pHevcCtx)
{
    HEVC_VIDEO_PARAM_SET_S *pVPS = NULL;
    HEVC_SEQ_PARAM_SET_S   *pSPS = NULL;
    HEVC_PIC_PARAM_SET_S   *pPPS = NULL;

    //check pps is get or not
	if (pHevcCtx->CurrSlice.pic_parameter_set_id < 0 || pHevcCtx->CurrSlice.pic_parameter_set_id >= (pHevcCtx->MaxPpsNum))
	{
        dprint(PRN_ERROR, "HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of range\n", pHevcCtx->CurrSlice.pic_parameter_set_id);
        return HEVC_DEC_ERR;
	}
	
    pPPS = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
    if (!pPPS->valid)
    {
        dprint(PRN_ERROR, "pps with this pic_parameter_set_id = %d havn't be decoded\n", pHevcCtx->CurrSlice.pic_parameter_set_id);
        return HEVC_DEC_ERR;
    }

    //check sps is get or not
	if (pPPS->seq_parameter_set_id < 0 || pPPS->seq_parameter_set_id >= (pHevcCtx->MaxSpsNum))
	{
        dprint(PRN_ERROR, "HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of range\n", pPPS->seq_parameter_set_id);
        return HEVC_DEC_ERR;
	}
	
    pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];
    if (!pSPS->valid)
    {
        dprint(PRN_ERROR, "sps with this seq_parameter_set_id = %d havn't be decoded\n", pPPS->seq_parameter_set_id);
        return HEVC_DEC_ERR;
    }

    //check vps is get or not
    
    if (pSPS->video_parameter_set_id >= (pHevcCtx->MaxVpsNum))
    {
        dprint(PRN_ERROR, "HEVC_VpsSpsPpsCheck video_parameter_set_id out of range\n");
        return HEVC_DEC_ERR;
	}  

    pVPS = &pHevcCtx->pVPS[pSPS->video_parameter_set_id];
    if (!pVPS->valid)
    {
	    dprint(PRN_ERROR, "vps with this video_parameter_set_id = %d havn't be decoded\n", pSPS->video_parameter_set_id);
	    return HEVC_DEC_ERR;
    }

    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_IsNewPic(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret = 0;

    SINT32 flag = 0;

    /* as 'PocRandomAccess == HEVC_MAX_INT' is mean the first frame want to decode,
      it's nal type should be as fellow these type!*/
    /*第一次的时候，检测到是如下的几种nal_type才开始解码 add by l00228308*/
    if (HEVC_MAX_INT == pHevcCtx->PocRandomAccess)
    {
        flag |= pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_CRA;
        flag |= pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_LP;
        flag |= pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_N_LP;
        flag |= pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_RADL;
        flag |= pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_W_RADL;
        flag |= pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_N_LP;

        if (0 == flag)
        {
            return IS_SKIP_PIC;
        }
    }

    /* 此处要及时更新随机插入点PocRandomAccess的值，如果seek后第一个送过来的帧的nal type = CRA,其后有可能送
    参考CRA之前的RASL帧，此时随机参考点的值必须更新为当前CRA帧的poc值，接下来才会把RASL帧正确丢弃，
    在接下来遇到IDR帧的时候，才赋值为-HEVC_MAX_INT，此后再遇到CRA帧，也无需重新对PocRandomAccess赋值 change by l00228308*/
    if (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_CRA
        || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_LP
        || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_N_LP
        || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_RADL)
    {
        if (HEVC_MAX_INT == pHevcCtx->PocRandomAccess)
        {
            pHevcCtx->PocRandomAccess = pHevcCtx->CurrSlice.poc;
        }
    }
    else if ((pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_W_RADL) || (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_N_LP))
    {
        pHevcCtx->PocRandomAccess = -HEVC_MAX_INT;
    }

    if ((pHevcCtx->CurrSlice.poc < pHevcCtx->PocRandomAccess)
        && (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_RASL_R || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_RASL_N))
    {
        /*del by l00228308 : 这几行会引起H265 正常播放闪现之前出现的帧的现象，这几行是从PV模型中同步过来的，
           在skip 帧的时候，如果还自加LastDisplayPoc 会引起此前已经解码的几帧画面没有得到正确的时机输出，遗留在DPB管理队列中，
           在某个时刻才被刷出来.因此以下把LastDisplayPoc 自加的代码注释掉 (以下三处均是此原因)*/
        //pHevcCtx->LastDisplayPoc++;
        dprint(PRN_ERROR, "%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, nal_unit_type = %d, should skip this frame\n", __func__, __LINE__,
               pHevcCtx->CurrSlice.poc, pHevcCtx->PocRandomAccess, pHevcCtx->pCurrNal->nal_unit_type);
        return IS_SKIP_PIC;
    }
    else if ((pHevcCtx->bNoRaslOutputFlag)
             && (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_RASL_R || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_RASL_N))
    {
        //pHevcCtx->LastDisplayPoc++;
        dprint(PRN_ERROR, "%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d, nal_unit_type = %d, should skip this frame\n", __func__, __LINE__,
               pHevcCtx->CurrSlice.poc, pHevcCtx->bNoRaslOutputFlag, pHevcCtx->pCurrNal->nal_unit_type);
        return IS_SKIP_PIC;
    }

    /* check if picture should be skipped because of association with a previous BLA picture */
    if (pHevcCtx->PrevRAPIsBLA && pHevcCtx->CurrSlice.poc < pHevcCtx->PocCRA
        && (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_RASL_R || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_RASL_N))
    {
        //pHevcCtx->LastDisplayPoc++;
        dprint(PRN_ERROR, "%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocCRA = %d, nal_unit_type = %d, should skip this frame\n", __func__, __LINE__,
               pHevcCtx->PrevRAPIsBLA, pHevcCtx->CurrSlice.poc, pHevcCtx->PocCRA, pHevcCtx->pCurrNal->nal_unit_type);
        return IS_SKIP_PIC;
    }

    if (!pHevcCtx->CurrSlice.dependent_slice_segment_flag)
    {
        if (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_W_RADL
            || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_N_LP)
        {
            pHevcCtx->PocCRA = pHevcCtx->CurrSlice.poc;
            pHevcCtx->PrevRAPIsBLA = HEVC_FALSE;
        }
        else if (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_CRA)
        {
            pHevcCtx->PocCRA = pHevcCtx->CurrSlice.poc;
            pHevcCtx->PrevRAPIsBLA = HEVC_FALSE;
        }
        else if (pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_LP
                 || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_RADL
                 || pHevcCtx->pCurrNal->nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_N_LP)
        {
            pHevcCtx->PocCRA = pHevcCtx->CurrSlice.poc;
            pHevcCtx->PrevRAPIsBLA = HEVC_TRUE;
        }
    }

    ret |= pHevcCtx->CurrSlice.first_slice_segment_in_pic_flag;
	
    if (pHevcCtx->TotalSliceNum >= 1 && pHevcCtx->TotalSliceNum <= HEVC_MAX_SLICE_NUM)
    {
        if (pHevcCtx->CurrSlice.pic_parameter_set_id != pHevcCtx->Slice[pHevcCtx->TotalSliceNum - 1])
        {
            ret = IS_NEW_PIC;
        }
    }

	//容错处理
	if (pHevcCtx->prev_pic_parameter_set_id != pHevcCtx->CurrSlice.pic_parameter_set_id || pHevcCtx->prev_poc != pHevcCtx->CurrSlice.poc)
	{
		ret = IS_NEW_PIC;
	}
	
    return ret;
}

SINT32 HEVC_ReadByteAlignment(HEVC_CTX_S *pHevcCtx)
{
    SINT32 code, skiplen;

    code = HEVC_u_v(pHevcCtx->pBS, 1, "");
	if (0 == code)
	{
		dprint(PRN_ERROR,"HEVC_ReadByteAlignment: code should not be zero.\n");
		return HEVC_DEC_ERR;
	}

    skiplen = BsBitsToNextByte(pHevcCtx->pBS);
    if (0 == skiplen)
    {
        return HEVC_DEC_NORMAL;
    }
    else
    {
        code = HEVC_u_v(pHevcCtx->pBS, skiplen, "");
    }
    
    return HEVC_DEC_NORMAL;
}

UINT8 HEVC_GetRapPicFlag(HEVC_CTX_S *pHevcCtx)
{
    return (UINT8) (pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_W_RADL
                    || pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_N_LP
                    || pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_N_LP
                    || pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_RADL
                    || pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_BLA_W_LP
                    || pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_CRA);
}

UINT8 HEVC_GetIdrPicFlag(HEVC_CTX_S *pHevcCtx)
{
    return (UINT8)(pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_W_RADL
                   || pHevcCtx->CurrSlice.nal_unit_type == NAL_UNIT_CODED_SLICE_IDR_N_LP);
}

SINT32 HEVC_DecPTL(HEVC_CTX_S *pHevcCtx,HEVC_PROFILE_TIER_LEVEL_S *pPTL, SINT32 ProfilePresentFlag, SINT32 MaxNumSubLayersMinus1)
{
    SINT32 i, j;
    UINT32 uiCode;
    char buf[100];

    if (ProfilePresentFlag)
    {
        pPTL->general_profile_space = HEVC_u_v(pHevcCtx->pBS, 2, "general_profile_space[]");
        pPTL->general_tier_flag     = HEVC_u_v(pHevcCtx->pBS, 1, "general_tier_flag[]");
        pPTL->general_profile_idc   = HEVC_u_v(pHevcCtx->pBS, 5, "general_profile_idc[]");

        for (i=0; i<32; i++)
        {
            snprintf(buf, sizeof(buf), "general_profile_compatibility_flag[][%d]", i);
            pPTL->general_profile_compatibility_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, buf);
        }
        pPTL->general_progressive_source_flag = HEVC_u_v(pHevcCtx->pBS, 1, "general_progressive_source_flag");
        pPTL->general_interlaced_source_flag = HEVC_u_v(pHevcCtx->pBS, 1, "general_interlaced_source_flag");
        pPTL->general_non_packed_constraint_flag = HEVC_u_v(pHevcCtx->pBS, 1, "general_non_packed_constraint_flag");
        pPTL->general_frame_only_constraint_flag = HEVC_u_v(pHevcCtx->pBS, 1, "general_frame_only_constraint_flag");

        HEVC_u_v(pHevcCtx->pBS,16,"general_reserved_zero_44bits[0..15]");
        HEVC_u_v(pHevcCtx->pBS,16,"general_reserved_zero_44bits[16..31]");
        HEVC_u_v(pHevcCtx->pBS,12,"general_reserved_zero_44bits[32..43]");
        pHevcCtx->general_profile_idc = pPTL->general_profile_idc;
        pHevcCtx->general_profile_compatibility_flag_1 = pPTL->general_profile_compatibility_flag[1];
        pHevcCtx->general_profile_compatibility_flag_2 = pPTL->general_profile_compatibility_flag[2];
        
    }

    pPTL->general_level_idc = HEVC_u_v(pHevcCtx->pBS, 8, "general_level_idc");

    for (i=0; i<MaxNumSubLayersMinus1; i++)
    {
        if (ProfilePresentFlag)
        {
            pPTL->sub_layer_profile_present_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "sub_layer_profile_present_flag");        
        }
        pPTL->sub_layer_level_present_flag[i]   = HEVC_u_v(pHevcCtx->pBS, 1, "sub_layer_level_present_flag");
    }

    if (MaxNumSubLayersMinus1 > 0)
    {
        for (i = MaxNumSubLayersMinus1; i < 8; i++)
        {  
            uiCode = HEVC_u_v(pHevcCtx->pBS,2,"reserved_zero_2bits");
			if (uiCode != 0)
			{
				dprint(PRN_ERROR, "reserved_zero_2bits not equal 0.\n");
				return HEVC_DEC_ERR;
			}
        }        
    }

    for (i=0; i<MaxNumSubLayersMinus1;i++)
    {
        if (ProfilePresentFlag && pPTL->sub_layer_profile_present_flag[i])
        {
            pPTL->sub_layer_profile_space[i] = HEVC_u_v(pHevcCtx->pBS, 2, "sub_layer_profile_space");
            pPTL->sub_layer_tier_flag[i]     = HEVC_u_v(pHevcCtx->pBS, 1, "sub_layer_tier_flag");
            pPTL->sub_layer_profile_idc[i]   = HEVC_u_v(pHevcCtx->pBS, 5, "sub_layer_profile_idc");

            for (j=0; j<32; j++)
            {
                pPTL->sub_layer_profile_compatibility_flag[i][j] = HEVC_u_v(pHevcCtx->pBS, 1, "sub_layer_profile_compatibility_flag");
            }
            pPTL->sub_layer_progressive_source_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "general_progressive_source_flag");
            pPTL->sub_layer_interlaced_source_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "general_interlaced_source_flag");
            pPTL->sub_layer_non_packed_constraint_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "general_non_packed_constraint_flag");
            pPTL->sub_layer_frame_only_constraint_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "general_frame_only_constraint_flag");
            
            HEVC_u_v(pHevcCtx->pBS,16,"general_reserved_zero_44bits[0..15]");
            HEVC_u_v(pHevcCtx->pBS,16,"general_reserved_zero_44bits[16..31]");
            HEVC_u_v(pHevcCtx->pBS,12,"general_reserved_zero_44bits[32..43]");
        }

        if (pPTL->sub_layer_level_present_flag[i])
        {
            pPTL->sub_layer_level_idc[i] = HEVC_u_v(pHevcCtx->pBS, 8, "sub_layer_level_idc");
        }
    }
    
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_DecScalingListData(HEVC_CTX_S *pHevcCtx,HEVC_SCALING_LIST *pScalingList)
{
    UINT8   scalingListPredModeFlag;
    UINT32  code, sizeId, matrixId, reflistId;
    SINT32  coefNum, i;
    SINT32  nextCoef;
    UINT32 *pScan = NULL;
    UINT8 *pDstScalingList = NULL;
    UINT8 *pMatrixAddress = NULL;

    //init quantization matrix array
	memcpy(pScalingList->scalingListCoef[SCALING_LIST_32x32][3],pScalingList->scalingListCoef[SCALING_LIST_32x32][1],HEVC_MAX_MATRIX_COEF_NUM);

    //for each size
    for (sizeId=0; sizeId<SCALING_LIST_SIZE_NUM; sizeId++)
    {
        for (matrixId=0; matrixId<pHevcCtx->scalingListNum[sizeId]; matrixId++)
        {
            scalingListPredModeFlag = HEVC_u_v(pHevcCtx->pBS, 1, "scaling_list_pred_mode_flag");
            pScalingList->scaling_list_pred_mode_flag[sizeId][matrixId] = scalingListPredModeFlag;
            coefNum = MIN(HEVC_MAX_MATRIX_COEF_NUM, (SINT32)pHevcCtx->scalingListSize[sizeId]);
            pDstScalingList = pScalingList->scalingListCoef[sizeId][matrixId];
            pScan = (0 == sizeId) ? s_auiSigLastScan[1] : pHevcCtx->sigLastScanCG32x32;

            if (!scalingListPredModeFlag) //Copy Mode
            {
                code = HEVC_ue_v(pHevcCtx->pBS, "scaling_list_pred_matrix_id_delta");
				if (code > matrixId)
				{
					dprint(PRN_ERROR, "scaling_list_pred_matrix_id_delta out of range(0,matrixId).\n");
                    return HEVC_DEC_ERR;
				}
				
                pScalingList->scaling_list_pred_matrix_id_delta[sizeId][matrixId] = code;
                pScalingList->refMatrixId[sizeId][matrixId] = (UINT8)(matrixId - code);
                if (sizeId > SCALING_LIST_8x8)
                {
                    reflistId = pScalingList->refMatrixId[sizeId][matrixId];
                    code = (matrixId == reflistId)? 16 : pScalingList->scalingListDC[sizeId][reflistId];	
                    pScalingList->scalingListDC[sizeId][matrixId] = code;
                }
                reflistId = pScalingList->refMatrixId[sizeId][matrixId];
                pMatrixAddress = (matrixId == reflistId)? HEVC_GetScalingListDefaultAddress(sizeId, reflistId) :
                	pScalingList->scalingListCoef[sizeId][reflistId];
				if (pMatrixAddress == NULL)	
				{
					dprint(PRN_ERROR, "HEVC_DecScalingListData pMatrixAddress NULL.\n");
					return HEVC_DEC_ERR;					
				}
                memcpy(pDstScalingList, pMatrixAddress, sizeof(SINT32)*coefNum);	
            }
            else   //DPCM Mode
            {
                nextCoef = HEVC_SCALING_LIST_START_VALUE;
                if (sizeId > SCALING_LIST_8x8)
                {
                    pScalingList->scaling_list_dc_coef_minus8 = HEVC_se_v(pHevcCtx->pBS, "scaling_list_dc_coef_minus8");
					if (pScalingList->scaling_list_dc_coef_minus8 < -7 || pScalingList->scaling_list_dc_coef_minus8 > 247)
					{
						dprint(PRN_ERROR, "scaling_list_dc_coef_minus8 out of range(-7,247).\n");
                        return HEVC_DEC_ERR;					
					}						
                    pScalingList->scalingListDC[sizeId][matrixId] = pScalingList->scaling_list_dc_coef_minus8 + 8;
                    nextCoef = pScalingList->scalingListDC[sizeId][matrixId];
                }
                for (i=0; i<coefNum; i++)
                {
                    pScalingList->scaling_list_delta_coef = HEVC_se_v(pHevcCtx->pBS, "scaling_list_delta_coef");
					if (pScalingList->scaling_list_delta_coef < -128 || pScalingList->scaling_list_delta_coef > 127)
					{
						dprint(PRN_ERROR, "scaling_list_dc_coef_minus8 out of range(-128,127).\n");
                        return HEVC_DEC_ERR;					
					}
                    nextCoef = (nextCoef + pScalingList->scaling_list_delta_coef + 256) % 256;
                    pDstScalingList[pScan[i]] = (UINT8)nextCoef;
                }
            }
        }
    }
    
    return HEVC_DEC_NORMAL;
}

/*!
************************************************************************
* 函数原型 :  SINT32 HEVC_SetScalingList()
* 功能描述 :  设置scaling_list
* 参数说明 :  
* 返回值   ： 
************************************************************************
*/
SINT32 HEVC_SetScalingList(HEVC_CTX_S *pHevcCtx)
{
    //先给相应的元素的全局变量赋值，后面将写入消息池
    UINT32 i, j;
    UINT8 *pTempScalingList = NULL;

    //set scaling_list
    if (pHevcCtx->pCurrSPS->scaling_list_enabled_flag)
    {
        if (!pHevcCtx->pCurrSPS->sps_scaling_list_data_present_flag && !pHevcCtx->pCurrPPS->pic_scaling_list_data_present_flag)
        {
            HEVC_SetDefaultScalingList(pHevcCtx);
        }
        else if (pHevcCtx->pCurrPPS->pic_scaling_list_data_present_flag)
        {
            memset(pHevcCtx->qmatrix,0,sizeof(pHevcCtx->qmatrix));
            for (i=0; i<SCALING_LIST_SIZE_NUM; i++)
            {
                for(j=0; j<pHevcCtx->scalingListNum[i]; j++)
                {
                    pTempScalingList = pHevcCtx->pCurrPPS->scaling_list.scalingListCoef[i][j];
                    HEVC_CalScalingList(pHevcCtx,pTempScalingList, i, j);
                }
            }
            memcpy(pHevcCtx->scalingListDC, &pHevcCtx->pCurrPPS->scaling_list.scalingListDC, sizeof(pHevcCtx->scalingListDC));
        }
        else
        {
            memset(pHevcCtx->qmatrix,0,sizeof(pHevcCtx->qmatrix));
            for (i=0; i<SCALING_LIST_SIZE_NUM; i++)
            {
                for(j=0; j<pHevcCtx->scalingListNum[i]; j++)
                {
                    pTempScalingList = pHevcCtx->pCurrSPS->scaling_list.scalingListCoef[i][j];
                    HEVC_CalScalingList(pHevcCtx,pTempScalingList, i, j);
                }
            }
            memcpy(pHevcCtx->scalingListDC, &pHevcCtx->pCurrSPS->scaling_list.scalingListDC, sizeof(pHevcCtx->scalingListDC));
        }
    }


    return HEVC_DEC_NORMAL;
}

VOID HEVC_SetDefaultScalingList(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i, j;
    
    for (i=0; i<SCALING_LIST_SIZE_NUM; i++)
    {
        for (j=0; j<pHevcCtx->scalingListNum[i]; j++)
        {
            if (0 == i)
            {
                memcpy(pHevcCtx->qmatrix[i][j], quant_ts_default, 4*4);
            }
            else if(3 == i)
            {
                memcpy(pHevcCtx->qmatrix[i][j], (j<1)?quant8_intra_default : quant8_inter_default, 4*16);
            }
            else 
            {
                memcpy(pHevcCtx->qmatrix[i][j], (j<3)?quant8_intra_default : quant8_inter_default, 4*16);
            }
            pHevcCtx->scalingListDC[i][j] = HEVC_SCALING_LIST_DC;
        }
    }

    return;
}

VOID HEVC_CalScalingList(HEVC_CTX_S *pHevcCtx, UINT8 *pScalingListCoef, UINT32 ListSize, UINT32 MatrixId)
{
    UINT32 i, k;
    UINT32 CoefNum;

    CoefNum = MIN(HEVC_MAX_MATRIX_COEF_NUM, pHevcCtx->scalingListSize[ListSize]);
    k=0;
    while (k<(CoefNum/4))
    {
        for (i=0; i<CoefNum; i++)
        {
            pHevcCtx->qmatrix[ListSize][MatrixId][k] = pHevcCtx->qmatrix[ListSize][MatrixId][k] 
                    | (pScalingListCoef[i] << ((i%4)*8)); // 4个bytes拼在1个words中
            if (3 == i%4)
            {
                k++;
            }
        }
    }

    return;
}

/** get default address of quantization matrix 
 * \param sizeId size index
 * \param listId list index
 * \returns pointer of quantization matrix
 */
UINT8 *HEVC_GetScalingListDefaultAddress(UINT32 sizeId, UINT32 matrixId)
{
    UINT8 *src = NULL;

    switch (sizeId)
    {
    case SCALING_LIST_4x4:
        src = g_quantTSDefault4x4;
        break;
    case SCALING_LIST_8x8:
        src = (matrixId<3) ? g_quantIntraDefault8x8 : g_quantInterDefault8x8;
        break;
    case SCALING_LIST_16x16:
        src = (matrixId<3) ? g_quantIntraDefault8x8 : g_quantInterDefault8x8;
        break;
    case SCALING_LIST_32x32:
        src = (matrixId<1) ? g_quantIntraDefault8x8 : g_quantInterDefault8x8;
        break;
    default:
		dprint(PRN_ERROR, "HEVC_GetScalingListDefaultAddress NULL.\n");		
        src = NULL;
        break;
    }
    return src;
}


SINT32 HEVC_DecShortTermRefPicSet(HEVC_CTX_S *pHevcCtx,HEVC_SEQ_PARAM_SET_S *pSPS, HEVC_SHORT_TERM_RPSET_S *pShortTermRpset, UINT32 idx)
{
    UINT32 rIdx, code, refIdc;
    UINT32 k=0, k1=0, k2=0;
	SINT32 deltaRPS, j;
    SINT32 deltaPOC, temp, prev=0;
    UINT8  used;
    UINT32 numNegPics, i;
    UINT32 used_by_curr_pic_flag, use_delta_flag;
    UINT32 delta_poc_s0_minus1, used_by_curr_pic_s0_flag, delta_poc_s1_minus1, used_by_curr_pic_s1_flag;
    
	HEVC_SHORT_TERM_RPSET_S *pTempRPset = NULL;
	
    if (idx > 0)
    {
        pShortTermRpset->inter_ref_pic_set_prediction_flag = HEVC_u_v(pHevcCtx->pBS, 1, "inter_ref_pic_set_prediction_flag");
    }
	else
	{
	    pShortTermRpset->inter_ref_pic_set_prediction_flag = HEVC_FALSE;
	}
	if (pShortTermRpset->inter_ref_pic_set_prediction_flag)
	{
	    if (idx == pSPS->num_short_term_ref_pic_sets)
	    {
	        code = HEVC_ue_v(pHevcCtx->pBS, "delta_idx_minus1");
			pShortTermRpset->delta_idx = code + 1;
	    }
		else
		{
		    code = 0;
		    pShortTermRpset->delta_idx = 0;
		}
        
		if (pShortTermRpset->delta_idx > idx)
		{
			dprint(PRN_ERROR, "delta_idx(%d) > idx(%d).\n", pShortTermRpset->delta_idx, idx);
			return HEVC_DEC_ERR;			
		}

        rIdx = idx - 1 - code;

        
        if (rIdx > (idx - 1))
        {
			dprint(PRN_ERROR, "rIdx(%d) > (idx-1)(%d) or < 0).\n", rIdx, (idx-1));
			return HEVC_DEC_ERR;	
		}

		pTempRPset = &(pSPS->short_term_ref_pic_set[rIdx]);
		
		pShortTermRpset->delta_rps_sign = HEVC_u_v(pHevcCtx->pBS, 1, "delta_rps_sign");
		pShortTermRpset->abs_delta_rps = HEVC_ue_v(pHevcCtx->pBS, "abs_delta_rps_minus1") + 1;
		deltaRPS = (1 - (pShortTermRpset->delta_rps_sign << 1)) * pShortTermRpset->abs_delta_rps;

		if (pTempRPset->num_of_pics > HEVC_MAX_NUM_REF_PICS)
		{
			dprint(PRN_ERROR, "pTempRPset->num_of_pics(%d) out of range(0,15).\n", pTempRPset->num_of_pics);
			return HEVC_DEC_ERR;
		}
		
		for (i=0; i <= pTempRPset->num_of_pics; i++)
		{
		    used_by_curr_pic_flag = HEVC_u_v(pHevcCtx->pBS, 1, "used_by_curr_pic_flag"); //first bit is "1" if Idc is 1
		    refIdc = used_by_curr_pic_flag;
			
			if (0 == refIdc)
			{
			    use_delta_flag = HEVC_u_v(pHevcCtx->pBS, 1, "use_delta_flag");//second bit is "1" if Idc is 2, "0" otherwise.
			    refIdc = use_delta_flag << 1;
			}
			if (1 == refIdc || 2 == refIdc)
			{
                deltaPOC = deltaRPS + ((i < pTempRPset->num_of_pics)?pTempRPset->delta_poc[i]:0);
                pShortTermRpset->delta_poc[k] = deltaPOC;
                pShortTermRpset->used_flag[k] = (1 == refIdc);

                if (deltaPOC < 0)
                {
                    k1++;
                }
                else
                {
                    k2++;
                }
				k++;
			}
            
			pShortTermRpset->refIdc[i] = refIdc;
		}
		pShortTermRpset->numRefIdc = pTempRPset->num_of_pics + 1;
		pShortTermRpset->num_of_pics = k;
		pShortTermRpset->num_negative_pics = k1;
        pShortTermRpset->num_positive_pics = k2;

		if (pShortTermRpset->num_of_pics > HEVC_MAX_NUM_REF_PICS || pShortTermRpset->num_negative_pics > HEVC_MAX_NUM_REF_PICS || pShortTermRpset->num_positive_pics > HEVC_MAX_NUM_REF_PICS)
		{
			dprint(PRN_ERROR, "num_of_pics out of range(0,15).\n");
			return HEVC_DEC_ERR;
		}

        // sortDeltaPOC: sort in increasing order (smallest first)
        for (i=1; i<pShortTermRpset->num_of_pics; i++)
        {
            deltaPOC = pShortTermRpset->delta_poc[i];
            used = pShortTermRpset->used_flag[i];
            for (j=i-1; j>=0; j--)
            {
                temp = pShortTermRpset->delta_poc[j];
                if (deltaPOC < temp)
                {
                    pShortTermRpset->delta_poc[j+1] = temp;
                    pShortTermRpset->used_flag[j+1] = pShortTermRpset->used_flag[j];
                    pShortTermRpset->delta_poc[j] = deltaPOC;
                    pShortTermRpset->used_flag[j] = used;
                }
            }
        }
        // flip the negative values to largest first
        numNegPics = pShortTermRpset->num_negative_pics;
        for (i=0, j=(SINT32)(numNegPics-1); i<numNegPics>>1; i++, j--)
        {
            deltaPOC = pShortTermRpset->delta_poc[i];
            used = pShortTermRpset->used_flag[i];
            pShortTermRpset->delta_poc[i] = pShortTermRpset->delta_poc[j];
            pShortTermRpset->used_flag[i] = pShortTermRpset->used_flag[j];
            pShortTermRpset->delta_poc[j] = deltaPOC;
            pShortTermRpset->used_flag[j] = used;
        }
	}
	else
	{
        pShortTermRpset->num_negative_pics = HEVC_ue_v(pHevcCtx->pBS, "num_negative_pics");
        if (pShortTermRpset->num_negative_pics > HEVC_MAX_NUM_REF_PICS)
        {
            dprint(PRN_ERROR, "pTempRPset->num_negative_pics(%d) out of range(0,15).\n", pShortTermRpset->num_negative_pics);
            return HEVC_DEC_ERR;
        }

        pShortTermRpset->num_positive_pics = HEVC_ue_v(pHevcCtx->pBS, "num_positive_pics");
        if (pShortTermRpset->num_positive_pics > HEVC_MAX_NUM_REF_PICS)
        {
            dprint(PRN_ERROR, "pTempRPset->num_positive_pics(%d) out of range(0,15).\n", pShortTermRpset->num_negative_pics);
            return HEVC_DEC_ERR;
        }

        pShortTermRpset->num_of_pics = pShortTermRpset->num_negative_pics + pShortTermRpset->num_positive_pics;
        if (pShortTermRpset->num_of_pics > HEVC_MAX_NUM_REF_PICS)
        {
            dprint(PRN_ERROR, "pShortTermRpset->num_of_pics(%d) out of range[0,%d].\n",pShortTermRpset->num_of_pics, HEVC_MAX_NUM_REF_PICS);
        	return HEVC_DEC_ERR;
        }

        for (i=0; i<pShortTermRpset->num_negative_pics; i++)
        {
            delta_poc_s0_minus1           = HEVC_ue_v(pHevcCtx->pBS, "delta_poc_s0_minus1");
            deltaPOC                      = prev - delta_poc_s0_minus1 - 1;
            prev                          = deltaPOC;
            pShortTermRpset->delta_poc[i] = deltaPOC;
            used_by_curr_pic_s0_flag      = HEVC_u_v(pHevcCtx->pBS, 1, "used_by_curr_pic_s0_flag");
            pShortTermRpset->used_flag[i] = used_by_curr_pic_s0_flag;
        }
        
        prev = 0;
        for (i=pShortTermRpset->num_negative_pics; i<pShortTermRpset->num_of_pics; i++)
        {
            delta_poc_s1_minus1           = HEVC_ue_v(pHevcCtx->pBS, "delta_poc_s1_minus1");
            deltaPOC                      = prev + delta_poc_s1_minus1 + 1;
            prev                          = deltaPOC;
            pShortTermRpset->delta_poc[i] = deltaPOC;
            used_by_curr_pic_s1_flag      = HEVC_u_v(pHevcCtx->pBS, 1, "used_by_curr_pic_s1_flag");
            pShortTermRpset->used_flag[i] = used_by_curr_pic_s1_flag;
        }
	}
    
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_DecRefPicListsModification(HEVC_CTX_S *pHevcCtx,HEVC_SLICE_SEGMENT_HEADER *pSlice, HEVC_REF_PIC_LISTS_MODDIFICATION *pRpListModification, SINT32 numRpsCurrTempList)
{
    UINT32 i, length, temp;

    if (pHevcCtx == NULL || pSlice == NULL || pRpListModification == NULL)
    {
        return HEVC_DEC_ERR;
    }

    temp = numRpsCurrTempList;
	length = 1;
	numRpsCurrTempList--;
	while (numRpsCurrTempList >>= 1)
	{
		length++;
	}

    pRpListModification->ref_pic_list_modification_flag_l0 = HEVC_u_v(pHevcCtx->pBS, 1, "ref_pic_list_modification_flag_l0");
	if (pRpListModification->ref_pic_list_modification_flag_l0 && (temp > 1))
	{
	    for (i=0; i<pSlice->num_ref_idx[0]; i++)
	    {
	        pRpListModification->list_entry_l0[i] = HEVC_u_v(pHevcCtx->pBS, length, "list_entry_l0");
	    }
	}
    if (HEVC_B_SLICE == pSlice->slice_type)
    {
        pRpListModification->ref_pic_list_modification_flag_l1 = HEVC_u_v(pHevcCtx->pBS, 1, "ref_pic_list_modification_flag_l1");
		if (pRpListModification->ref_pic_list_modification_flag_l1 && (temp > 1))
		{
			for (i=0; i<pSlice->num_ref_idx[1]; i++)
			{
			    pRpListModification->list_entry_l1[i] = HEVC_u_v(pHevcCtx->pBS, length, "list_entry_l1");
			}
		}
    }
	
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_DecPredWeightTable(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i, j;
    SINT32 shift, pred;
    HEVC_SEQ_PARAM_SET_S    *pSPS = NULL;
    HEVC_PIC_PARAM_SET_S    *pPPS = NULL;
    HEVC_PRED_WEIGHT_TABLE  *pPwt = NULL;

    pPwt = &(pHevcCtx->CurrSlice.pred_weight_table);
    pPPS = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
    pSPS = &pHevcCtx->pSPS[pPPS->seq_parameter_set_id];

    if (((HEVC_P_SLICE == pHevcCtx->CurrSlice.slice_type) && (pPPS->weighted_pred_flag)) ||
        ((HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type) && (pPPS->weighted_bipred_flag)))
    {
        pPwt->luma_log2_weight_denom= HEVC_ue_v(pHevcCtx->pBS, "luma_log2_weight_denom");
		if (pPwt->luma_log2_weight_denom > 7 || pPwt->luma_log2_weight_denom < 0)
		{
			dprint(PRN_ERROR, "luma_log2_weight_denom out of range(0,7).\n");
			return HEVC_DEC_ERR;
		}

        if (0 != pSPS->chroma_format_idc)
        {
            pPwt->delta_chroma_log2_weight_denom = HEVC_se_v(pHevcCtx->pBS, "delta_chroma_log2_weight_denom");
			if (pPwt->delta_chroma_log2_weight_denom > 7 || pPwt->delta_chroma_log2_weight_denom < -7)
			{
				dprint(PRN_ERROR, "delta_chroma_log2_weight_denom out of range(-7,7).\n");
				return HEVC_DEC_ERR;
			}
		}
		
        pPwt->chroma_log2_weight_denom = pPwt->luma_log2_weight_denom + pPwt->delta_chroma_log2_weight_denom;
        
        for (i=0; i<pHevcCtx->CurrSlice.num_ref_idx[0]; i++)
        {
            pPwt->luma_weight_l0_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "luma_weight_l0_flag");
        }
        if (0 != pSPS->chroma_format_idc)
        {
            for (i=0; i<pHevcCtx->CurrSlice.num_ref_idx[0]; i++)
            {
                pPwt->chroma_weight_l0_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "chroma_weight_l0_flag");
            }
        }

        for (i=0; i<pHevcCtx->CurrSlice.num_ref_idx[0]; i++)
        {
            if (pPwt->luma_weight_l0_flag[i])
            {
                pPwt->delta_luma_weight_l0[i] = HEVC_se_v(pHevcCtx->pBS, "delta_luma_weight_l0");
				if (pPwt->delta_luma_weight_l0[i] > 127 || pPwt->delta_luma_weight_l0[i] < -128)
				{
					dprint(PRN_ERROR, "delta_luma_weight_l0(%d) out of range(-128,127).\n", pPwt->delta_luma_weight_l0[i]);
					return HEVC_DEC_ERR;
				}

                pPwt->LumaWeightL0[i] = pPwt->delta_luma_weight_l0[i] + (1 << pPwt->luma_log2_weight_denom);
                pPwt->luma_offset_l0[i] = HEVC_se_v(pHevcCtx->pBS, "luma_offset_l0");
				if (pPwt->luma_offset_l0[i] > 127 || pPwt->luma_offset_l0[i] < -128)
				{
					dprint(PRN_ERROR, "luma_offset_l0(%d) out of range(-128,127).\n", pPwt->luma_offset_l0[i]);
					return HEVC_DEC_ERR;
				}
            }
            else
            {
                pPwt->LumaWeightL0[i] = 1 << pPwt->luma_log2_weight_denom;
                pPwt->luma_offset_l0[i] = 0;
            }
            if (0 != pSPS->chroma_format_idc)
            {
                if (pPwt->chroma_weight_l0_flag[i])
                {
                    for (j=0; j<2; j++)
                    {
                        pPwt->delta_chroma_weight_l0[i][j] = HEVC_se_v(pHevcCtx->pBS, "delta_chroma_weight_l0");
						if (pPwt->delta_chroma_weight_l0[i][j] > 127 || pPwt->delta_chroma_weight_l0[i][j] < -128)
						{
							dprint(PRN_ERROR, "delta_chroma_weight_l0 out of range(-128,127).\n");
							return HEVC_DEC_ERR;
						}

                        pPwt->delta_chroma_offset_l0[i][j] = HEVC_se_v(pHevcCtx->pBS, "delta_chroma_offset_l0");
						if (pPwt->delta_chroma_offset_l0[i][j] > 511 || pPwt->delta_chroma_offset_l0[i][j] < -512)
						{
							dprint(PRN_ERROR, "delta_chroma_offset_l0 out of range(-512,511).\n");
							return HEVC_DEC_ERR;
						}

                        pPwt->ChromaWeightL0[i][j] = (1 << pPwt->chroma_log2_weight_denom)
                                                     + pPwt->delta_chroma_weight_l0[i][j];
                        //shift = 1 << (pHevcCtx->BitDepthC - 1);
                        shift = 128;
                        pred = (shift - ((shift * pPwt->ChromaWeightL0[i][j])>> (pPwt->chroma_log2_weight_denom)));
                        pPwt->ChromaOffsetL0[i][j] = CLIP3(HEVC_SINT8_MIN_VAL, HEVC_SINT8_MAX_VAL, (pred + pPwt->delta_chroma_offset_l0[i][j]));
                    }
                }
                else
                {
                    for (j=0; j<2; j++)
                    {
                        pPwt->ChromaWeightL0[i][j] = (1 << pPwt->chroma_log2_weight_denom);
                        pPwt->ChromaOffsetL0[i][j] = 0;
                    }
                }
            }
        }

        if (HEVC_B_SLICE == pHevcCtx->CurrSlice.slice_type)
        {
            for (i=0; i<pHevcCtx->CurrSlice.num_ref_idx[1]; i++)
            {
                pPwt->luma_weight_l1_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "luma_weight_l1_flag");
            }
            if (0 != pSPS->chroma_format_idc)
            {
                for (i=0; i<pHevcCtx->CurrSlice.num_ref_idx[1]; i++)
                {
                    pPwt->chroma_weight_l1_flag[i] = HEVC_u_v(pHevcCtx->pBS, 1, "chroma_weight_l1_flag");
                }
            }
            for (i=0; i<pHevcCtx->CurrSlice.num_ref_idx[1]; i++)
            {
                if (pPwt->luma_weight_l1_flag[i])
                {
                    pPwt->delta_luma_weight_l1[i] = HEVC_se_v(pHevcCtx->pBS, "delta_luma_weight_l1");
					if (pPwt->delta_luma_weight_l1[i] > 127 || pPwt->delta_luma_weight_l1[i] < -128)
					{
						dprint(PRN_ERROR, "delta_luma_weight_l1 out of range(-128,127).\n");
						return HEVC_DEC_ERR;
					}					
                    pPwt->LumaWeightL1[i] = pPwt->delta_luma_weight_l1[i] + (1 << pPwt->luma_log2_weight_denom);
                    pPwt->luma_offset_l1[i] = HEVC_se_v(pHevcCtx->pBS, "luma_offset_l1");
					if (pPwt->luma_offset_l1[i] > 127 || pPwt->luma_offset_l1[i] < -128)
					{
						dprint(PRN_ERROR, "luma_offset_l1 out of range(-128,127).\n");
						return HEVC_DEC_ERR;
					}	
                }
                else
                {
                    pPwt->LumaWeightL1[i] = 1 << pPwt->luma_log2_weight_denom;
                    pPwt->luma_offset_l1[i] = 0;
                }
                if (0 != pSPS->chroma_format_idc)
                {
                    if (pPwt->chroma_weight_l1_flag[i])
                    {
                        for (j=0; j<2; j++)
                        {
                            pPwt->delta_chroma_weight_l1[i][j] = HEVC_se_v(pHevcCtx->pBS, "delta_chroma_weight_l1");
							if (pPwt->delta_chroma_weight_l1[i][j] > 127 || pPwt->delta_chroma_weight_l1[i][j] < -128)
							{
								dprint(PRN_ERROR, "delta_chroma_weight_l1 out of range(-128,127).\n");
								return HEVC_DEC_ERR;
							}							
                            pPwt->delta_chroma_offset_l1[i][j] = HEVC_se_v(pHevcCtx->pBS, "delta_chroma_offset_l1");
							if (pPwt->delta_chroma_offset_l1[i][j] > 511 || pPwt->delta_chroma_offset_l1[i][j] < -512)
							{
								dprint(PRN_ERROR, "delta_chroma_offset_l1 out of range(-512,511).\n");
								return HEVC_DEC_ERR;
							}
                            pPwt->ChromaWeightL1[i][j] = (1 << pPwt->chroma_log2_weight_denom)
                                                         + pPwt->delta_chroma_weight_l1[i][j];
                            //shift = 1 << (pHevcCtx->BitDepthC - 1);
                            shift = 128;
                            pred = (shift - ((shift * pPwt->ChromaWeightL1[i][j])>> (pPwt->chroma_log2_weight_denom)));
                            pPwt->ChromaOffsetL1[i][j] = CLIP3(HEVC_SINT8_MIN_VAL, HEVC_SINT8_MAX_VAL, (pred + pPwt->delta_chroma_offset_l1[i][j]));
                        }
                    }
                    else
                    {
                        for (j=0; j<2; j++)
                        {
                            pPwt->ChromaWeightL1[i][j] = (1 << pPwt->chroma_log2_weight_denom);
                            pPwt->ChromaOffsetL1[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    
    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_DecVuiParam(HEVC_CTX_S *pHevcCtx,HEVC_VUI_PARAM_SET_S *pVUI,HEVC_SEQ_PARAM_SET_S * pSps)
{
	SINT32 ret;
    const UINT32 m_winUnitX[]={1,2,2,1};
    const UINT32 m_winUnitY[]={1,2,1,1};

    pVUI->aspect_ratio_info_present_flag = HEVC_u_v(pHevcCtx->pBS,1,"aspect_ratio_info_present_flag");
    if (pVUI->aspect_ratio_info_present_flag)
    {
        pVUI->aspect_ratio_idc = HEVC_u_v(pHevcCtx->pBS,8,"aspect_ratio_idc");
        if (255 == pVUI->aspect_ratio_idc)
        {
            pVUI->sar_width = HEVC_u_v(pHevcCtx->pBS,16,"sar_width");
            pVUI->sar_height = HEVC_u_v(pHevcCtx->pBS,16,"sar_height");
        }
    }

    pVUI->overscan_info_present_flag = HEVC_u_v(pHevcCtx->pBS,1,"overscan_info_present_flag");
    if (pVUI->overscan_info_present_flag)
    {
        pVUI->overscan_appropriate_flag = HEVC_u_v(pHevcCtx->pBS,1,"overscan_appropriate_flag"); 
    }

    pVUI->video_signal_type_present_flag = HEVC_u_v(pHevcCtx->pBS,1,"video_signal_type_present_flag");
    if (pVUI->video_signal_type_present_flag)
    {
        pVUI->video_format = HEVC_u_v(pHevcCtx->pBS,3,"video_format");
        pVUI->video_full_range_flag = HEVC_u_v(pHevcCtx->pBS,1,"video_full_range_flag");
        pVUI->colour_description_present_flag = HEVC_u_v(pHevcCtx->pBS,1,"colour_description_present_flag");
        if (pVUI->colour_description_present_flag)
        {
            pVUI->colour_primaries = HEVC_u_v(pHevcCtx->pBS,8,"colour_primaries");
            pVUI->transfer_characteristics = HEVC_u_v(pHevcCtx->pBS,8,"transfer_characteristics");
            pVUI->matrix_coeffs = HEVC_u_v(pHevcCtx->pBS,8,"matrix_coeffs"); 
        }
    }
    
    pVUI->chroma_loc_info_present_flag = HEVC_u_v(pHevcCtx->pBS,1,"chroma_loc_info_present_flag");
    if (pVUI->chroma_loc_info_present_flag)
    {
        pVUI->chroma_sample_loc_type_top_field = HEVC_ue_v(pHevcCtx->pBS,"chroma_sample_loc_type_top_field");
        pVUI->chroma_sample_loc_type_bottom_field = HEVC_ue_v(pHevcCtx->pBS,"chroma_sample_loc_type_bottom_field");
    }

    pVUI->neutral_chroma_indication_flag = HEVC_u_v(pHevcCtx->pBS,1,"neutral_chroma_indication_flag");

    pVUI->field_seq_flag = HEVC_u_v(pHevcCtx->pBS,1,"field_seq_flag");

    pVUI->frame_field_info_present_flag= HEVC_u_v(pHevcCtx->pBS,1,"frame_field_info_present_flag");
    
    pVUI->default_display_window_flag = HEVC_u_v(pHevcCtx->pBS,1,"default_display_window_flag");
    if (pVUI->default_display_window_flag)
    {
        pVUI->def_disp_win_left_offset = HEVC_ue_v(pHevcCtx->pBS, "def_disp_win_left_offset");

        
        if (pSps->chroma_format_idc > 3)
        {
            dprint(PRN_ERROR, "VUI pSps->chroma_format_idc out of range(0,3).\n");
            return HEVC_DEC_ERR;
		}	
        pVUI->def_disp_win_left_offset *= m_winUnitX[pSps->chroma_format_idc];
        pVUI->def_disp_win_right_offset = HEVC_ue_v(pHevcCtx->pBS,"def_disp_win_right_offset");
        pVUI->def_disp_win_right_offset *= m_winUnitX[pSps->chroma_format_idc];
        pVUI->def_disp_win_top_offset = HEVC_ue_v(pHevcCtx->pBS,"def_disp_win_top_offset");
        pVUI->def_disp_win_top_offset *= m_winUnitY[pSps->chroma_format_idc];
        pVUI->def_disp_win_bottom_offset = HEVC_ue_v(pHevcCtx->pBS,"def_disp_win_bottom_offset");
        pVUI->def_disp_win_bottom_offset *= m_winUnitY[pSps->chroma_format_idc];
    }

    pVUI->vui_timing_info_present_flag = HEVC_u_v(pHevcCtx->pBS,1,"vui_timing_info_present_flag");
    if (pVUI->vui_timing_info_present_flag)
    {
        pVUI->vui_num_units_in_tick = HEVC_u_v(pHevcCtx->pBS,32,"vui_num_units_in_tick");  
        pVUI->vui_time_scale = HEVC_u_v(pHevcCtx->pBS,32,"vui_time_scale");
        pVUI->vui_poc_proportional_to_timing_flag = HEVC_u_v(pHevcCtx->pBS,1,"vui_poc_proportional_to_timing_flag");
        if (pVUI->vui_poc_proportional_to_timing_flag)
        {
            pVUI->vui_num_ticks_poc_diff_one_minus1 = HEVC_ue_v(pHevcCtx->pBS,"vui_num_ticks_poc_diff_one_minus1");
        }
        pVUI->vui_hrd_parameters_present_flag = HEVC_u_v(pHevcCtx->pBS,1,"vui_hrd_parameters_present_flag");
        if (pVUI->vui_hrd_parameters_present_flag)
        {
            ret = HEVC_DecHrdParam(pHevcCtx,&(pVUI->hrd_parameters),1,pSps->sps_max_sub_layers_minus1);
			if (HEVC_DEC_NORMAL != ret)
			{
				dprint(PRN_ERROR, "VUI HEVC_DecHrdParam error.\n");
				return HEVC_DEC_ERR;				
			}
        }
    }

    pVUI->bitstream_restriction_flag = HEVC_u_v(pHevcCtx->pBS,1,"bitstream_restriction_flag");
    if (pVUI->bitstream_restriction_flag)
    {
        pVUI->tiles_fixed_structure_flag = HEVC_u_v(pHevcCtx->pBS,1,"tiles_fixed_structure_flag");
        pVUI->motion_vectors_over_pic_boundaries_flag = HEVC_u_v(pHevcCtx->pBS,1,"motion_vectors_over_pic_boundaries_flag");
        pVUI->restricted_ref_pic_lists_flag = HEVC_u_v(pHevcCtx->pBS,1,"restricted_ref_pic_lists_flag");
        pVUI->min_spatial_segmentation_idc = HEVC_ue_v(pHevcCtx->pBS,"min_spatial_segmentation_idc");
		if (pVUI->min_spatial_segmentation_idc >= 4096)
		{
			dprint(PRN_ERROR, "VUI min_spatial_segmentation_idc out of range(0,4095).\n");
            //return HEVC_DEC_ERR;
		}
        pVUI->max_bytes_per_pic_denom = HEVC_ue_v(pHevcCtx->pBS,"max_bytes_per_pic_denom");
        pVUI->max_bits_per_min_cu_denom = HEVC_ue_v(pHevcCtx->pBS,"max_bits_per_min_cu_denom");
        pVUI->log2_max_mv_length_horizontal = HEVC_ue_v(pHevcCtx->pBS,"log2_max_mv_length_horizontal");
        pVUI->log2_max_mv_length_vertical = HEVC_ue_v(pHevcCtx->pBS,"log2_max_mv_length_vertical");    
    }   
    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_DecHrdParam(HEVC_CTX_S *pHevcCtx,HEVC_HRD_PARAM_SET_S *pHrd, UINT8 commonInfPresentFlag,UINT32 maxNumSubLayersMinus1)
{
    UINT32 i, j, k;

    if (pHevcCtx == NULL || pHrd == NULL)
    {
        return HEVC_DEC_ERR;
    }

    if (commonInfPresentFlag)
    {
        pHrd->nal_hrd_parameters_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "nal_hrd_parameters_present_flag");
        pHrd->vcl_hrd_parameters_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "vcl_hrd_parameters_present_flag");

        if (pHrd->nal_hrd_parameters_present_flag ||  pHrd->vcl_hrd_parameters_present_flag)
        {
            pHrd->sub_pic_hrd_params_present_flag = HEVC_u_v(pHevcCtx->pBS, 1, "sub_pic_cpb_params_present_flag");

            if (pHrd->sub_pic_hrd_params_present_flag)
            {
                pHrd->tick_divisor_minus2 = HEVC_u_v(pHevcCtx->pBS, 8, "tick_divisor_minus2");
                pHrd->du_cpb_removal_delay_increment_length_minus1 = HEVC_u_v(pHevcCtx->pBS, 5, "du_cpb_removal_delay_increment_length_minus1");
                pHrd->sub_pic_cpb_params_in_pic_timing_sei_flag = HEVC_u_v(pHevcCtx->pBS,1,"sub_pic_cpb_params_in_pic_timing_sei_flag");
                pHrd->dpb_output_delay_length_minus1 = HEVC_u_v(pHevcCtx->pBS,5,"dpb_output_delay_du_length_minus1");
            }
            pHrd->bit_rate_scale = HEVC_u_v(pHevcCtx->pBS,4,"bit_rate_scale");
            pHrd->cpb_size_scale = HEVC_u_v(pHevcCtx->pBS,4,"cpb_size_scale");
            if (pHrd->sub_pic_hrd_params_present_flag)
            {
                pHrd->cpb_size_du_scale = HEVC_u_v(pHevcCtx->pBS,4,"cpb_size_du_scale");  
            }
            pHrd->initial_cpb_removal_delay_length_minus1 = HEVC_u_v(pHevcCtx->pBS,5,"initial_cpb_removal_delay_length_minus1");  
            pHrd->au_cpb_removal_delay_length_minus1 = HEVC_u_v(pHevcCtx->pBS,5,"au_cpb_removal_delay_length_minus1");  
            pHrd->dpb_output_delay_length_minus1 = HEVC_u_v(pHevcCtx->pBS,5,"dpb_output_delay_length_minus1");    
        }
    }

    for (i=0; i<=maxNumSubLayersMinus1;i++)
    {
        pHrd->hrd_sublayer[i].fixed_pic_rate_general_flag = HEVC_u_v(pHevcCtx->pBS,1,"fixed_pic_rate_general_flag");  
        if (!(pHrd->hrd_sublayer[i].fixed_pic_rate_general_flag))
        {
            pHrd->hrd_sublayer[i].fixed_pic_rate_within_cvs_flag = HEVC_u_v(pHevcCtx->pBS,1,"fixed_pic_rate_within_cvs_flag");          
        }
        else
        {
            pHrd->hrd_sublayer[i].fixed_pic_rate_within_cvs_flag = HEVC_TRUE;                      
        }
        pHrd->hrd_sublayer[i].low_delay_hrd_flag = 0;
        pHrd->hrd_sublayer[i].cpb_cnt_minus1 = 0;
        if (pHrd->hrd_sublayer[i].fixed_pic_rate_within_cvs_flag)
        {
            pHrd->hrd_sublayer[i].elemental_duration_in_tc_minus1 = HEVC_ue_v(pHevcCtx->pBS,"elemental_duration_in_tc_minus1");
        }
        else
        {
            pHrd->hrd_sublayer[i].low_delay_hrd_flag = HEVC_u_v(pHevcCtx->pBS,1,"low_delay_hrd_flag");
        }
        if (!(pHrd->hrd_sublayer[i].low_delay_hrd_flag))
        {
            pHrd->hrd_sublayer[i].cpb_cnt_minus1 = HEVC_ue_v(pHevcCtx->pBS,"cpb_cnt_minus1");
        }

        
        if (pHrd->hrd_sublayer[i].cpb_cnt_minus1 > 31)
        {
            dprint(PRN_ERROR, "cpb_cnt_minus1(%d) out of range(0,31).\n", pHrd->hrd_sublayer[i].cpb_cnt_minus1);
            pHrd->hrd_sublayer[i].cpb_cnt_minus1 = 0; // 赋值强解
            //return HEVC_DEC_ERR;
		}
        for (j=0;j<2;j++)
        {
            if (((0==j)&&(pHrd->nal_hrd_parameters_present_flag))
             || ((1==j)&&(pHrd->vcl_hrd_parameters_present_flag)))
            {
                for (k=0; k<=pHrd->hrd_sublayer[i].cpb_cnt_minus1; k++)
                {
                    pHrd->hrd_sublayer[i].bit_rate_value_minus1[k][j] = HEVC_ue_v(pHevcCtx->pBS,"bit_rate_value_minus1");
                    pHrd->hrd_sublayer[i].cpb_size_value_minus1[k][j] = HEVC_ue_v(pHevcCtx->pBS,"cpb_size_value_minus1");
                    if (pHrd->sub_pic_hrd_params_present_flag)
                    {
                        pHrd->hrd_sublayer[i].cpb_size_du_value_minus1[k][j] = HEVC_ue_v(pHevcCtx->pBS,"cpb_size_du_value_minus1");
                        pHrd->hrd_sublayer[i].bit_rate_du_value_minus1[k][j] = HEVC_ue_v(pHevcCtx->pBS,"bit_rate_du_value_minus1");
                    }
                    pHrd->hrd_sublayer[i].cbr_flag[k][j] = HEVC_u_v(pHevcCtx->pBS,1,"cbr_flag");
                }
            }   
        }    
    }
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_MoreRbspData(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret;
    SINT32 bitsLeft;

	bitsLeft = BsResidBits(pHevcCtx->pBS);
    if (bitsLeft > 0 && bitsLeft > (pHevcCtx->pCurrNal->nal_trail_zero_bit_num + 3))
	{
	    ret = HEVC_TRUE;
	}
    else
    {
        ret = HEVC_FALSE;
    }

    return ret;
}

SINT32 HEVC_More_Rbsp_Data(HEVC_CTX_S *pHevcCtx)
{
    if (pHevcCtx->pBS->BsLen * 8 <= pHevcCtx->pBS->TotalPos)
    {
        dprint(PRN_ERROR, "Error, BsLen: 0x%x, TotalPos: 0x%x\n", pHevcCtx->pBS->BsLen * 8, pHevcCtx->pBS->TotalPos);
        return HEVC_FALSE;
    }
    else
    {
        if (0x80 == BsShow(pHevcCtx->pBS, 8))
        {
            return HEVC_FALSE;
        }
        else
        {
            return HEVC_TRUE;
        }
    } 
}

/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_FindTrailZeros()
*      功能描述 :  找拖尾零的函数
*      参数说明 :  无
*      返回值   ： HEVC_DEC_NORMAL; DEC_ERR;
************************************************************************
*/
SINT32 HEVC_FindTrailZeros(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ctr_bit, bitoffset, zero_byte;
    UINT8  *last_byte = NULL;
    UINT32 NalSegmentMinus1; 

    // find trail_zeros
    NalSegmentMinus1 = pHevcCtx->pCurrNal->nal_segment - 1;
    last_byte = pHevcCtx->pCurrNal->stream[NalSegmentMinus1].streamBuffer + pHevcCtx->pCurrNal->stream[NalSegmentMinus1].bitstream_length - 1;
    zero_byte = 0; 

    while ((UINT8)0x00 == *(last_byte))
    {                 
        zero_byte++;
        if (last_byte == pHevcCtx->pCurrNal->stream[0].streamBuffer)  
        {
            dprint(PRN_ERROR, "Panic: All zero data sequence in RBSP \n");
            return HEVC_DEC_ERR;
        }
        else if (last_byte == pHevcCtx->pCurrNal->stream[NalSegmentMinus1].streamBuffer)
        {
			SM_ReleaseStreamSeg(pHevcCtx->ChanID, pHevcCtx->pCurrNal->stream[NalSegmentMinus1].StreamID);
			pHevcCtx->pCurrNal->stream[NalSegmentMinus1].streamBuffer = NULL;
            pHevcCtx->pCurrNal->nal_segment--;
            NalSegmentMinus1 = pHevcCtx->pCurrNal->nal_segment - 1;
            last_byte = pHevcCtx->pCurrNal->stream[NalSegmentMinus1].streamBuffer + pHevcCtx->pCurrNal->stream[NalSegmentMinus1].bitstream_length - 1;                     
            //先赋值为-1,再通过本身的zero_byte++;
            zero_byte = 0;
        }
        else
        {
            last_byte -= 1;
        }
    }               

    bitoffset = 0; // find trailing 1 
    ctr_bit = ((*(last_byte)) & 1); // set up control bit
    while (0 == ctr_bit)
    {                 
        bitoffset++;
        if (8 <= bitoffset)
        {  
            dprint(PRN_ERROR, "nal_trail_zero_bit_num err\n");
            return HEVC_DEC_ERR;                  
        }
        ctr_bit = (*last_byte) & (0x01 << (bitoffset));
    }

    pHevcCtx->pCurrNal->nal_bitoffset = 0;
    pHevcCtx->pCurrNal->nal_trail_zero_bit_num = bitoffset + 1 + zero_byte*8;

    return HEVC_DEC_NORMAL;    
}

/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_FindNaluArraySlot()
*      功能描述 :  find a good Nalu Slot to save current Nalu
*      参数说明 :  无
*      返回值   ： 返回空的Nalu数组中可用的位置
************************************************************************
*/
SINT32 HEVC_FindNaluArraySlot(HEVC_CTX_S *pHevcCtx)
{
    UINT32 Pos;
    UINT32 FindPosFlag;

#ifndef HEVC_SYNTAX_OPT
    FindPosFlag = 0;

    for (Pos = 0; Pos < pHevcCtx->MaxSlotNum + 1; Pos++)
    {
        if (0 == pHevcCtx->pNalArray[Pos].is_valid)
        {
            FindPosFlag = 1;
            break;
        }
    }

#else
    SINT32 i;
    FindPosFlag = 0;
    Pos = pHevcCtx->NalArrayPos;

    for (i = 0; i < pHevcCtx->MaxSlotNum + 1; i++)
    {
        Pos = (Pos + i) % (pHevcCtx->MaxSlotNum + 1);

        if (0 == pHevcCtx->pNalArray[Pos].is_valid)
        {
            FindPosFlag = 1;
            break;
        }
    }

    pHevcCtx->NalArrayPos = Pos;
#endif

    if ((1 == FindPosFlag) && (Pos < (pHevcCtx->MaxSlotNum + 1)))
    {
        pHevcCtx->pNalArray[Pos].is_valid = 1;
        return ((SINT32)Pos);
    }
    else
    {
        return HEVC_DEC_ERR;
    }    
}

/*!
************************************************************************
*   函数原型 :  VOID HEVC_ReleaseNAL(SINT32 ChanID, HEVC_NALU_S *p_nall)
*   功能描述 :  释放一个nal
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
VOID HEVC_ReleaseNAL(SINT32 ChanID, HEVC_NALU_S *p_nal)
{
    SINT32 i;
    
    CHECK_NULL_PTR_Return(p_nal);
    
    p_nal->is_valid = 0;
    p_nal->nal_integ = 0;
    for (i=0; i<2; i++)
    {
        if (p_nal->stream[i].streamBuffer != NULL)
        {
            SM_ReleaseStreamSeg(ChanID, p_nal->stream[i].StreamID);
            dprint(PRN_STREAM, "%s release streambuff=%p, bitstream_length=%d\n",__func__, p_nal->stream[i].streamBuffer, p_nal->stream[i].bitstream_length);
            p_nal->stream[i].streamBuffer = NULL; 
            p_nal->stream[i].bitsoffset = 0;
            p_nal->stream[i].bitstream_length = 0;
        }
    }
    
    memset(p_nal, 0, sizeof(HEVC_NALU_S));
    
    return;
}


/*!
************************************************************************
*      函数原型 :  VOID HEVC_CombinePacket()
*      功能描述 :  拼包功能函数
*      参数说明 :  无
*      返回值   ： VOID
************************************************************************
*/
VOID HEVC_CombinePacket(HEVC_CTX_S *pHevcCtx)
{
    SINT32 StreamId;
    
	if (pHevcCtx->pCurrNal == NULL)
	{
        dprint(PRN_FATAL, "HEVC_CombinePacket FATAL: pCurrNal=NULL!\n");
		return ;
	}
    
    // 表示肯定分包了，也就是说肯定Buf触底了
    if (pHevcCtx->pCurrNal->stream[0].bitstream_length < HEVC_GET_ONE_NALU_SIZE) // 需要copy本包到buf的头部
    {                       
        dprint(PRN_STREAM, "END of the bit buffer, copy the first packet!\n");

        // copy到最前面
        memcpy(pHevcCtx->pCurrNal->stream[1].streamBuffer - pHevcCtx->pCurrNal->stream[0].bitstream_length, pHevcCtx->pCurrNal->stream[0].streamBuffer, pHevcCtx->pCurrNal->stream[0].bitstream_length);

        StreamId =  pHevcCtx->pCurrNal->stream[0].StreamID;
        pHevcCtx->pCurrNal->stream[0].StreamID = pHevcCtx->pCurrNal->stream[1].StreamID;
		pHevcCtx->pCurrNal->stream[0].bitsoffset = 0;
        pHevcCtx->pCurrNal->stream[0].streamBuffer = pHevcCtx->pCurrNal->stream[1].streamBuffer - pHevcCtx->pCurrNal->stream[0].bitstream_length;
        pHevcCtx->pCurrNal->stream[0].stream_phy_addr = pHevcCtx->pCurrNal->stream[1].stream_phy_addr - pHevcCtx->pCurrNal->stream[0].bitstream_length; 
        pHevcCtx->pCurrNal->stream[0].bitstream_length = pHevcCtx->pCurrNal->stream[0].bitstream_length + pHevcCtx->pCurrNal->stream[1].bitstream_length;    //include nal header              
        pHevcCtx->pCurrNal->nal_segment = 1;

		//完成拼包 , 将第一个包拷贝到第2个包的位置,同时  释放原来第一个包,原来这里没有释放,造成码流泄露
		SM_ReleaseStreamSeg(pHevcCtx->ChanID, StreamId);
		pHevcCtx->pCurrNal->stream[1].streamBuffer = NULL; 
		pHevcCtx->pCurrNal->stream[1].bitsoffset = 0;
		pHevcCtx->pCurrNal->stream[1].bitstream_length = 0;
    }

    return;
}


/*!
************************************************************************
*      函数原型 :  SINT32 HEVC_ReceivePacket(HEVC_STREAM_PACKET *pPacket)
*      功能描述 :  获取一片码流，并判断该片码流是否是完整的nal
*      参数说明 :  无
*      返回值   ： 1:一个完整的Nalu;0不是一个完整的Nalu;DEC_ERR:解码错误
************************************************************************
*/
//错误处理可以提出来做,但有两种错误处理需要处理,所以暂时先放在这里
SINT32 HEVC_ReceivePacket(HEVC_CTX_S *pHevcCtx,HEVC_STREAM_PACKET *pPacket)
{
    SINT32 ret;

    pHevcCtx->u32SCDWrapAround = 0;
    
    // 第一次收到包
    if (NULL == pHevcCtx->pCurrNal)
    {  
        // 收到非零的包
        if ((0 < pPacket->stream_len) && (NULL != pPacket->p_stream) && (0 != pPacket->strm_phy_addr))
        { 
            // find a good Nalu Slot to save current Nalu        
            ret = HEVC_FindNaluArraySlot(pHevcCtx);
            if (HEVC_DEC_ERR == ret)
            {
                dprint(PRN_FATAL, "cann't find slot for current nal\n");
                //如果找不到空Nalu Array Slot,后续考虑加错误处理
                HEVC_ClearAll(pHevcCtx, 0);
                return HEVC_DEC_ERR;
            }        
            pHevcCtx->pCurrNal = &pHevcCtx->pNalArray[ret];
            pHevcCtx->pCurrNal->stream[0].streamBuffer = pPacket->p_stream;
            pHevcCtx->pCurrNal->stream[0].bitstream_length = pPacket->stream_len;    // include nal header   
            pHevcCtx->pCurrNal->stream[0].StreamID =  pPacket->StreamID; 

            pHevcCtx->pCurrNal->stream[0].stream_phy_addr = pPacket->strm_phy_addr;
            pHevcCtx->pCurrNal->stream[0].bitsoffset = 0;
            pHevcCtx->pCurrNal->nal_segment = 1;
            pHevcCtx->pCurrNal->nal_used_segment = 0;
            pHevcCtx->pCurrNal->nal_integ = pPacket->last_pack_in_nal;
        }
        else
        {
            dprint(PRN_ERROR, "receive a zero packet\n");
            return HEVC_DEC_ERR;
        }
    }
    else
    {		
        // 收到第二包数据
        pHevcCtx->pCurrNal->nal_integ = pPacket->last_pack_in_nal;

        if((1 != pHevcCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) || \
           ((1 == pHevcCtx->pstExtraData->stChanOption.u32DynamicFrameStoreAllocEn) && \
           (0 == pHevcCtx->pstExtraData->s32WaitFsFlag)))
        {
        if ((1 != pPacket->last_pack_in_nal)|| ((2 <= pHevcCtx->pCurrNal->nal_segment) && (1 == pHevcCtx->pCurrNal->nal_integ)))
        {
            dprint(PRN_ERROR, "nal_release_err\n");
            return HEVC_DEC_ERR; 
        }             
        if ((0 < pPacket->stream_len) && (NULL != pPacket->p_stream) && (0 != pPacket->strm_phy_addr))
        {
            pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_segment].streamBuffer = pPacket->p_stream;
            pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_segment].bitstream_length = pPacket->stream_len;    
            pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_segment].stream_phy_addr = pPacket->strm_phy_addr;
			pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_segment].StreamID =  pPacket->StreamID;
            pHevcCtx->pCurrNal->stream[pHevcCtx->pCurrNal->nal_segment].bitsoffset = 0;            
            pHevcCtx->pCurrNal->nal_segment++;      

            // 拼包功能函数
            HEVC_CombinePacket(pHevcCtx);
            pHevcCtx->u32SCDWrapAround = 1;
        }
        else
        {
            // 第二包长度为0或码流地址为空,那么就只解第一包数据
            pHevcCtx->pCurrNal->nal_integ = 1;
            SM_ReleaseStreamSeg(pHevcCtx->ChanID, pPacket->StreamID);
            } 
        }        
    }

	ret = pHevcCtx->pCurrNal->nal_integ ? HEVC_DEC_NORMAL: HEVC_DEC_ERR;
    
	return ret;
}


/***********************************************************************************
* Function:    UINT32 HEVCDEC_VDMPostProc( HEVC_CTX_S *pHevcCtx, SINT32 ErrRatio, SINT32 CalledByISR, LUMA_INFO_S *pLumaInfo )
* Description: 解码中断后处理函数
* Input:       无
* Output:      无
* Return:      DEC_NORMAL   可以解码此Nalu数据
*              DEC_ERR      不可以解码
* Others:      无
***********************************************************************************/  
UINT32 HEVCDEC_VDMPostProc( HEVC_CTX_S *pHevcCtx, SINT32 ErrRatio, SINT32 CalledByISR,LUMA_INFO_S *pLumaInfo,SINT32 ModuleLowlyEnable,SINT32 VdhId)
{
    SINT32 ret;
    
    pHevcCtx->CurrPic.err_level = ErrRatio;

#ifdef VFMW_MODULE_LOWDLY_SUPPORT		
	if(ModuleLowlyEnable)
	{
		if(g_VdmDrvParam[VdhId].ChanIntState == 3)
		{
			HEVC_ClearAllSlice(pHevcCtx);
			return HEVC_DEC_NORMAL;
		}
		if(g_VdmDrvParam[VdhId].ChanIntState == 1)
		{
			HEVC_ClearAllSlice(pHevcCtx);
		}
	}
	else
	{
		HEVC_ClearAllSlice(pHevcCtx);
	}
#else
    HEVC_ClearAllSlice(pHevcCtx);
#endif
 
	ret = HEVC_StorePicInDPB(pHevcCtx,pLumaInfo);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_FATAL, "HEVC_StorePicInDPB failed, ret = %d\n", ret);
        HEVC_ClearCurrPic(pHevcCtx);
        HEVC_ClearDPB(pHevcCtx);
        return HEVC_DEC_ERR;
    }
    pHevcCtx->AllowStartDec = 1;

    return HEVC_DEC_NORMAL;
}


SINT32  HEVC_IsOutDPB(HEVC_CTX_S *pHevcCtx,HEVC_FRAMESTORE_S  *pFrameStore)
{
    UINT32 i;
    
    if (NULL == pFrameStore)
    {
        return 1;
    }
    
    for (i = 0; i < pHevcCtx->DPB.used_size; i++)
    {
        if (pHevcCtx->DPB.fs[i] == pFrameStore)
        {
            return 0;
        }
    }
    
    return 1;
}


/* 查看是否有空闲帧存 */
SINT32 HEVCDEC_GetImageBuffer( HEVC_CTX_S *pHevcCtx )
{
    UINT32 i;
	SINT32 ret;
    SINT32 ReadImgNum, NewImgNum;

    // 第一次需判为有效使能帧存划分，当前帧如果已获取到帧存，可以不需查询
    if (pHevcCtx->TotalFsNum < 1 || HEVC_PIC_DECODING == pHevcCtx->CurrPic.state)
    {
        return 1;
    }
    
    // Check frame store
    for (i=0; i<HEVC_MAX_FRAME_STORE; i++)
    {
        if (FS_NOT_USED == pHevcCtx->FrameStore[i].eFrameStoreState && 1 == HEVC_IsOutDPB(pHevcCtx, &pHevcCtx->FrameStore[i]))
        {
			// 帧存结构获取到了，还要查询FSP是否真的有帧存可用
			ret = FSP_IsNewFsAvalible(pHevcCtx->ChanID);
			if (1 == ret)
			{
				return 1;
			}
			else if (-1 == ret)
			{
				FSP_ClearNotInVoQueue(pHevcCtx->ChanID, &(pHevcCtx->ImageQue));
				return 0;
			}
            else if (2 == ret)
            {
				return 0;
            }
			else if (0 == ret)
			{
                // 容错: 如果获取不到帧存，而且当前VO队列为空，则出现了异常
                if (1 == IsVoQueueEmpty(&pHevcCtx->ImageQue))
                {
                    dprint(PRN_FATAL, "Unkown Error: No available fs, try to remove unused fs!\n");
                    HEVC_PrintDPBState(pHevcCtx);
                    
                    // 尝试去除已经不用的帧存
                    HEVC_RemoveUnusedApcStore(pHevcCtx);
                    ret = HEVC_RemoveUnUsedFrameStore(pHevcCtx);
                    if (ret != HEVC_TRUE)
                    {
                        // 如上述清除动作无效，则强制清空DPB
                        dprint(PRN_FATAL, "Remove failed, clear DPB!\n");
                        HEVC_ClearDPB(pHevcCtx);
                    }
                    else
                    {
                        dprint(PRN_FATAL, "Remove success! DPB: used %d, size %d.\n",pHevcCtx->DPB.used_size,pHevcCtx->DPB.size);
                    }
                }
				return 0;
			}
        }        
    }

    // 检查帧存是否泄漏
    GetQueueImgNum(&pHevcCtx->ImageQue, &ReadImgNum, &NewImgNum);
    HEVC_PrintFrameStoreState(pHevcCtx);
    dprint(PRN_FATAL, "No frame store available!\n");
    HEVC_PrintDPBState(pHevcCtx);
    if ((ReadImgNum+NewImgNum) < (SINT32)(pHevcCtx->TotalFsNum-pHevcCtx->DPB.used_size-2))
    {
        dprint(PRN_FATAL, "%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak, ClearAll!\n", __func__, ReadImgNum, NewImgNum);	
        HEVC_ClearAll(pHevcCtx,1);
    }

    return 0;
}


SINT32 HEVC_ClearAll(HEVC_CTX_S *pHevcCtx,SINT32 flag)
{
    HEVC_ClearCurrPic(pHevcCtx);
    
    HEVC_InitDPB(pHevcCtx, 0);
    
    if(flag)
    {
        FSP_ClearNotInVoQueue(pHevcCtx->ChanID,&pHevcCtx->ImageQue);
    }
    else
    {
        FSP_EmptyInstance(pHevcCtx->ChanID);
    }

	HEVC_InitDecPara(pHevcCtx);

    return HEVC_DEC_NORMAL;
}


SINT32 HEVCDEC_Init(HEVC_CTX_S *pHevcCtx,SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    UINT32 MemOffset = 0;
    UINT8 *pCtx_Vir = NULL;
    SINT32 ImgQueRstMagic;
    
    // 清除上下文
    ImgQueRstMagic = pHevcCtx->ImageQue.ResetMagicWord;
    memset(pHevcCtx, 0, sizeof(HEVC_CTX_S));
    pHevcCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    
    pHevcCtx->pstExtraData = pstExtraData;
    pHevcCtx->pHevcDecParam = NULL;

    // init SPS PPS SLICE_PARA
    if (pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION)
    {
        pHevcCtx->MaxVpsNum   = pHevcCtx->pstExtraData->stChanOption.s32MaxVpsNum;
        pHevcCtx->MaxSpsNum   = pHevcCtx->pstExtraData->stChanOption.s32MaxSpsNum;
        pHevcCtx->MaxPpsNum   = pHevcCtx->pstExtraData->stChanOption.s32MaxPpsNum;
        pHevcCtx->MaxSliceNum = pHevcCtx->pstExtraData->stChanOption.s32MaxSliceNum;
        pHevcCtx->MaxSlotNum  = pHevcCtx->MaxSliceNum + 5;
    }
    else
    {
        pHevcCtx->MaxVpsNum   = HEVC_MAX_VIDEO_PARAM_SET_ID;
        pHevcCtx->MaxSpsNum   = HEVC_MAX_SEQ_PARAM_SET_ID;
        pHevcCtx->MaxPpsNum   = HEVC_MAX_PIC_PARAM_SET_ID;
        pHevcCtx->MaxSliceNum = HEVC_MAX_SLICE_NUM;     //z00290437  20141025  //Slice数不是Slot数
        pHevcCtx->MaxSlotNum  = HEVC_MAX_SLOT_NUM;
    }

    // 初始化VPS SPS PPS
    pCtx_Vir = (UINT8 *)MEM_Phy2Vir(pHevcCtx->pstExtraData->s32ContextMemAddr);
    if (NULL == pCtx_Vir)
    {
        dprint(PRN_FATAL, "%s: Get context addr failed!\n", __func__);
        return VF_ERR_SYS;
    }
    MemOffset  = pHevcCtx->pstExtraData->s32BasicCtxSize;
    
    pHevcCtx->pVPS = (HEVC_VIDEO_PARAM_SET_S*)(pCtx_Vir + MemOffset);
    MemOffset += sizeof(HEVC_VIDEO_PARAM_SET_S)*(pHevcCtx->MaxVpsNum);
    
    pHevcCtx->pSPS = (HEVC_SEQ_PARAM_SET_S*)(pCtx_Vir + MemOffset);
    MemOffset += sizeof(HEVC_SEQ_PARAM_SET_S)*(pHevcCtx->MaxSpsNum);
    
    pHevcCtx->pPPS = (HEVC_PIC_PARAM_SET_S*)(pCtx_Vir + MemOffset);
    MemOffset += sizeof(HEVC_PIC_PARAM_SET_S)*(pHevcCtx->MaxPpsNum);
    
    pHevcCtx->pDecSlicePara = (HEVC_DEC_SLICE_PARAM_S*)(pCtx_Vir + MemOffset);
    MemOffset += sizeof(HEVC_DEC_SLICE_PARAM_S) * (pHevcCtx->MaxSliceNum);
        
    pHevcCtx->pNalArray = (HEVC_NALU_S *)(pCtx_Vir + MemOffset);
    MemOffset += sizeof(HEVC_NALU_S) * (pHevcCtx->MaxSlotNum + 1);
    
    pHevcCtx->pMsgSlot = (HEVC_MSGSLOT_S *)(pCtx_Vir + MemOffset);
    MemOffset += sizeof(HEVC_MSGSLOT_S) * (pHevcCtx->MaxSlotNum);

    if (MemOffset > pHevcCtx->pstExtraData->s32ContextMemSize)
    {
        dprint(PRN_FATAL, "%s FATAL: MemOffset %d > ContextMemSize %d.\n", __func__, MemOffset, pHevcCtx->pstExtraData->s32ContextMemSize);
        return VF_ERR_SYS;
    }

    if (0 == pstExtraData->s32KeepSPSPPS)
    {
        if (NULL != pHevcCtx->pVPS)
        {
            memset(pHevcCtx->pVPS,  0, (pHevcCtx->MaxVpsNum)*sizeof(HEVC_VIDEO_PARAM_SET_S));
        }
        if (NULL != pHevcCtx->pSPS)
        {
            memset(pHevcCtx->pSPS,  0, (pHevcCtx->MaxSpsNum)*sizeof(HEVC_SEQ_PARAM_SET_S));
        }
        if (NULL != pHevcCtx->pPPS)
        {
            memset(pHevcCtx->pPPS,  0, (pHevcCtx->MaxPpsNum)* sizeof(HEVC_PIC_PARAM_SET_S));
        }
    }
    memset(pHevcCtx->pDecSlicePara, 0, (pHevcCtx->MaxSliceNum) * sizeof(HEVC_DEC_SLICE_PARAM_S));
    memset(pHevcCtx->pNalArray,     0, (pHevcCtx->MaxSlotNum + 1) * sizeof(HEVC_NALU_S));
    memset(pHevcCtx->pMsgSlot,      0, (pHevcCtx->MaxSlotNum) * sizeof(HEVC_MSGSLOT_S));
        
    pHevcCtx->pCurrVPS = &pHevcCtx->pVPS[pHevcCtx->MaxVpsNum - 1];
    pHevcCtx->pCurrPPS = &pHevcCtx->pPPS[pHevcCtx->MaxPpsNum - 1];
    pHevcCtx->pCurrSPS = &pHevcCtx->pSPS[pHevcCtx->MaxSpsNum - 1];
    pHevcCtx->pCurrVPS->video_parameter_set_id = pHevcCtx->MaxVpsNum;  //HEVC_MAX_VIDEO_PARAM_SET_ID;
    pHevcCtx->pCurrPPS->pic_parameter_set_id = pHevcCtx->MaxSpsNum;    //HEVC_MAX_PIC_PARAM_SET_ID;
    pHevcCtx->pCurrSPS->seq_parameter_set_id = pHevcCtx->MaxPpsNum;    //HEVC_MAX_SEQ_PARAM_SET_ID;

	HEVC_InitScalingOrderTable(pHevcCtx);

    pHevcCtx->ChanID = VCTRL_GetChanIDByCtx(pHevcCtx);
    if ( -1 == pHevcCtx->ChanID )
    {
        dprint(PRN_FATAL, "%s: VCTRL_GetChanIDByCtx() return -1!\n", __func__);
        return VF_ERR_SYS;
    }

    pHevcCtx->LastDisplayPoc = -HEVC_MAX_INT;
    
    HEVC_InitDecPara(pHevcCtx);  

	pHevcCtx->FirstFrameState = FIRST_FRAME_INIT;
	pHevcCtx->prev_pic_parameter_set_id = pHevcCtx->MaxPpsNum;
	pHevcCtx->prev_poc = 9999;
    
    pHevcCtx->bIsInit = 1;

    return HEVC_DEC_NORMAL;
}


/***********************************************************************************
* Function:    HEVC_IsNewPicNal( SINT32 *pNewPicDetector,  UINT32 *pu8 )
* Description: 分析一个nal是否属于新的一帧.
*              此函数在读到码流seg包时被调用，用以判断读到的seg包是否属于新的一帧，
*              这对于处理诸如PTS等问题至关重要。
* Input:       pu8          此nal包的码流首地址
* Return:      DEC_NORMAL   此nal属于新pic
*              DEC_ERR      此nal不属于新pic，可能与之前的nal同属一个pic
* Others:      无
***********************************************************************************/  
SINT32 HEVC_IsNewPicNal( SINT32 *pNewPicDetector, UINT8 *pu8 )
{
    return HEVC_OK;
}


/* 码字解析函数,区别h264 */
/*****************************************************************************
函 数 名  : u_v
功能描述  : 从码流中取无符号数
输入参数  : BS    *pBs
            SINT32 v
            SINT8 *Name
输出参数  : 无
返 回 值  : UINT32
调用函数  :
被调函数  :
*****************************************************************************/
UINT32 HEVC_u_v(BS *pBs, SINT32 v, SINT8 *Name)
{
    UINT32 Code;

    Code = BsGet(pBs, v);

	return Code;
}

/*****************************************************************************
函 数 名  : f_v
功能描述  : 从码流中取固定值
输入参数  : BS    *pBs
            SINT32 v
            SINT8 *Name
输出参数  : 无
返 回 值  : UINT32
调用函数  :
被调函数  :
*****************************************************************************/
UINT32 HEVC_f_v(BS *pBs, SINT32 v, SINT8 *Name)
{
    UINT32 Code;

    Code = BsGet(pBs, v);

    return Code;
}

/*****************************************************************************
函 数 名  : HEVC_ue_v
功能描述  : 解0阶无符号哥伦布码
输入参数  : BS    *pBs
            SINT8 *Name
输出参数  : 无
返 回 值  : UINT32
调用函数  :
被调函数  :
*****************************************************************************/
UINT32 HEVC_ue_v(BS *pBs, SINT8 *Name)
{
    UINT32 tmpbits;
    UINT32 Info;
    UINT32 LeadingZeros;

    tmpbits = BsShow(pBs, 32);
    LeadingZeros = ZerosMS_32(tmpbits);

    if (LeadingZeros < 32)
    {
        /* 因为最大的数为2的31次方，所以zeros+1的最大个数为32  */
        BsSkip(pBs, LeadingZeros);
        Info = BsShow(pBs, (LeadingZeros + 1)) - 1;
        BsSkip(pBs, (LeadingZeros + 1));
    }
    else
    {
        /* 这时有32个零，说明有错误发生 */
        Info = 0xffffeeee; // 0xffffffff
        dprint(PRN_ERROR, "HEVC_ue_v ERROR: LeadingZeros (%d) >= 32, return 0x%x\n", LeadingZeros, Info);
        return Info;
    }
	
    return Info;
}

/*****************************************************************************
函 数 名  : HEVC_se_v
功能描述  : 解0 阶有符号哥伦布码
输入参数  : BS *pBs
SINT8 *Name
输出参数  : 无
返 回 值  : SINT32
调用函数  :
被调函数  :
*****************************************************************************/
SINT32 HEVC_se_v(BS *pBs, SINT8 *Name)
{
    UINT32 tmpbits;
    SINT32 Info;
    UINT32 LeadingZeros;
    UINT32 InfoLastBit;

    tmpbits = BsShow(pBs, 32);
    LeadingZeros = ZerosMS_32(tmpbits);

    /* 因为最大的数为2的31次方，所以zeros的最大个数为32，所以在这种情况下需要BsShow两次  */
    if (LeadingZeros < 32)
    {
        BsSkip(pBs, LeadingZeros);
        Info = BsShow(pBs, (LeadingZeros + 1)) - 1;
        InfoLastBit = Info & 1;
        Info = Info >> 1;
        Info = ((InfoLastBit & 1) ? (Info + 1) : -1 * Info);
        BsSkip(pBs, (LeadingZeros + 1));
    }
    else
    {
        /* 这时有32个零，说明有错误发生  */
        Info = 0x7fffffff;
        return Info;
    }
	
    return Info;
}

SINT32 HEVC_ClearCurrNal(HEVC_CTX_S *pHevcCtx)
{
    if (NULL != pHevcCtx->pCurrNal)
    {
        HEVC_ReleaseNAL(pHevcCtx->ChanID, pHevcCtx->pCurrNal);
        pHevcCtx->pCurrNal = NULL;
    }
    
    return HEVC_DEC_NORMAL;
}

SINT32 HEVC_ClearDPB(HEVC_CTX_S *pHevcCtx)
{
   	SINT32 ret;
    
    ret = HEVC_FlushDPB(pHevcCtx);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_FATAL, "%s: flush dpb failed, return %d\n", __func__, ret);
    }

    HEVC_InitDPB(pHevcCtx, 0);
    
    return HEVC_DEC_NORMAL;
}

/*
************************************************************************
*   函数原型 :  UINT32 FrameStoreRefFlg(const HEVC_FRAMESTORE_S *pFS)
*   功能描述 :  指示该framestore是否用于参考
*   参数说明 :  
*   返回值   ： 
************************************************************************
*/
UINT32 HEVC_FrameStoreRefFlg(const HEVC_FRAMESTORE_S *pFS)
{
    return (pFS->is_reference > 0);
}


SINT32 HEVC_ClearCurrSlice(HEVC_CTX_S *pHevcCtx)
{
    HEVC_ClearCurrNal(pHevcCtx);
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_ClearAllSlice(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;

    for (i = 0; i < pHevcCtx->MaxSlotNum; i++)
    {
        if (NULL != pHevcCtx->pMsgSlot[i].slice_nal)
        {
            HEVC_ReleaseNAL(pHevcCtx->ChanID, pHevcCtx->pMsgSlot[i].slice_nal);
            pHevcCtx->pMsgSlot[i].slice_nal = NULL;
        }
    }
    pHevcCtx->NumSlicePara = 0;
    pHevcCtx->MaxBytesReceived = 0;
	pHevcCtx->TotalSliceNum = 0;
    pHevcCtx->CurrMsgSlotNum = HEVC_SLICE_SLOT_START_NUM - 1;
    pHevcCtx->bHaveIndependentSlice = 0;
    
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_ClearAllNal(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;

    for (i = 0; i < pHevcCtx->MaxSlotNum + 1; i++)
    {
        if (1 == (pHevcCtx->pNalArray[i].is_valid))
        {
            HEVC_ReleaseNAL(pHevcCtx->ChanID, &(pHevcCtx->pNalArray[i]));
        }
    }

    pHevcCtx->bHaveNalNotDecoded = 0;

#ifdef HEVC_SYNTAX_OPT
    pHevcCtx->NalArrayPos = 0;
#endif

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_ClearCurrPic(HEVC_CTX_S *pHevcCtx)
{
    HEVC_ClearAllSlice(pHevcCtx);
    if (pHevcCtx->CurrPic.frame_store != NULL)
    {
        FSP_ClearLogicFs(pHevcCtx->ChanID, pHevcCtx->CurrPic.frame_store->logic_fs_id, 1);
        pHevcCtx->CurrPic.frame_store->eFrameStoreState = FS_NOT_USED;
        pHevcCtx->CurrPic.frame_store = NULL;
    }
    pHevcCtx->CurrPic.state = HEVC_PIC_EMPTY;
    
    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_FlushDPB(HEVC_CTX_S *pHevcCtx)
{
    UINT32 i;
    SINT32 ret;
    UINT32 pos;
    SINT32 min_poc;

    // mark all frames unused
    for (i=0; i<pHevcCtx->DPB.used_size; i++)
    {
        if (0 != pHevcCtx->DPB.fs[i]->is_reference)
        {
            HEVC_UnMarkFrameStoreRef (pHevcCtx, pHevcCtx->DPB.fs[i]);
        }
    }

    while ( HEVC_RemoveUnUsedFrameStore(pHevcCtx) );

    // output frames in POC order
    while (pHevcCtx->DPB.used_size)
    {
        HEVC_GetMinPOC(pHevcCtx, &min_poc, &pos);
        ret = HEVC_OutputOneFrmFromDPB(pHevcCtx, pos);
        if (HEVC_DEC_ERR == ret)
        {
            return HEVC_DEC_ERR;
        }
    }

    return HEVC_DEC_NORMAL;
}


/*!
************************************************************************
*      函数原型 :  VOID UnMarkFrameStoreRef(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S *pFrameStore)
*      功能描述 :  将pFrameStore对因帧存中所有图像标记为不参考，同时释放pmv槽位
*      参数说明 :  pFrameStore帧存指针
*      返回值   ： 无
************************************************************************
*/
VOID HEVC_UnMarkFrameStoreRef(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S *pFrameStore)
{
    //经过以上步骤不一定就把is_reference赋成0，所有最后强制一下
    pFrameStore->is_reference = 0;
    /* 把逻辑帧存标记为不参考 */
	FSP_SetRef(pHevcCtx->ChanID, pFrameStore->logic_fs_id, 0);
    return;
}


SINT32 HEVC_InquireSliceProperty(HEVC_CTX_S *pHevcCtx, SINT32 *IsNewPic, SINT32 *IsSizeChanged)
{
    SINT32 ret;
    HEVC_SEQ_PARAM_SET_S *sps = NULL;
    HEVC_PIC_PARAM_SET_S *pps = NULL;
    SINT32 oldw, oldh, neww, newh;

    *IsNewPic = *IsSizeChanged = 0;

    memset(&pHevcCtx->CurrSlice, 0, sizeof(HEVC_SLICE_SEGMENT_HEADER));
	pHevcCtx->CurrSlice.nal_unit_type   = pHevcCtx->pCurrNal->nal_unit_type;
	pHevcCtx->CurrSlice.nuh_temporal_id = pHevcCtx->pCurrNal->nuh_temporal_id;

    ret = HEVC_DecSliceSegmentHeader(pHevcCtx);
    if (HEVC_DEC_NORMAL != ret)
    {
        dprint(PRN_ERROR, "HEVC_DecSliceSegmentHeader dec err\n");
        return HEVC_DEC_ERR;
    }

    *IsNewPic = (1 == pHevcCtx->CurrSlice.new_pic_type)? 1: 0;

    pps = &pHevcCtx->pPPS[pHevcCtx->CurrSlice.pic_parameter_set_id];
    sps = &pHevcCtx->pSPS[pps->seq_parameter_set_id];

    neww = sps->pic_width_in_luma_samples;
    newh = sps->pic_height_in_luma_samples;
    oldw = pHevcCtx->pCurrSPS->pic_width_in_luma_samples;
    oldh = pHevcCtx->pCurrSPS->pic_height_in_luma_samples;

    if ((sps->dpbsize_changed) || (oldw != neww) || (oldh != newh))
    {
		//dprint(PRN_ALWS,"HEVC_InquireSliceProperty (dpbsize_changed:%d, resolution:%dx%d->%dx%d\n",sps->dpbsize_changed, oldw,oldh,neww,newh);
        *IsSizeChanged = 1;
    }
	
    if (1 == *IsSizeChanged && pHevcCtx->TotalPicNum != 0)
    {
        REPORT_FAKE_FRAME(pHevcCtx->ChanID);
    }

    return HEVC_DEC_NORMAL;
}


SINT32 HEVC_HaveSliceToDec(HEVC_CTX_S *pHevcCtx)
{
    if (pHevcCtx->NumSlicePara > 0)
    {
        return HEVC_DEC_NORMAL;
    }
    else //pHevcCtx->NumSlicePara = 0
    {
        /*容错，在开始解新帧前，先判断上帧是否申请了帧存，
          而且未成功解出一个slice，如是先将其申请的帧存释放*/
        if (HEVC_PIC_EMPTY != pHevcCtx->CurrPic.state)
        {
            dprint(PRN_FATAL, "%s last frame fs unrelease, fix it!\n", __func__);
            HEVC_ClearCurrPic(pHevcCtx);
        }
        return HEVC_DEC_ERR;
    }
}


SINT32 HEVC_GetPicStreamSize(HEVC_CTX_S *pHevcCtx)
{
    SINT32 TotalSize = 0;
    HEVC_DEC_SLICE_PARAM_S *pHevcSliceParam = NULL;

    pHevcSliceParam = pHevcCtx->DecPicPara.pFirstSlice;

    while (pHevcSliceParam)
    {
        TotalSize += ((pHevcSliceParam->valid_bitlen[0] + pHevcSliceParam->valid_bitlen[1] + 7) / 8);
        pHevcSliceParam = pHevcSliceParam->pNextSlice;
    }

    return TotalSize;
}


SINT32 HEVCDEC_GetRemainImg(HEVC_CTX_S *pHevcCtx)
{
    SINT32 ret = LAST_OUTPUT_FAIL;
    UINT32 pos;
    SINT32 min_poc;
    IMAGE *pstLogicFsImage = NULL;
    HEVC_FRAMESTORE_S *pFrameStore = NULL;

    // output frames in POC order
    while (pHevcCtx->DPB.used_size)
    {
        HEVC_GetMinPOC(pHevcCtx, &min_poc, &pos);

        pFrameStore = pHevcCtx->DPB.fs[pos];
        if (pFrameStore != NULL && 0 == pFrameStore->is_displayed)
        {
            pFrameStore->is_displayed = 1;
            HEVC_GetImagePara(pHevcCtx,pFrameStore);
            ret = HEVC_CheckFrameStore(pHevcCtx, pFrameStore);
            if (HEVC_DEC_NORMAL == ret)
            {
                FSP_SetDisplay(pHevcCtx->ChanID, pFrameStore->logic_fs_id, 1);
                pstLogicFsImage = FSP_GetFsImagePtr(pHevcCtx->ChanID, pFrameStore->logic_fs_id);
                if (NULL == pstLogicFsImage)
                {
                    dprint(PRN_FATAL,"%s pstLogicFsImage is NULL!\n", __func__);
                    ret = LAST_OUTPUT_FAIL;
                }
                else
                {
                    if (1 == pHevcCtx->DPB.used_size)
                    {
                        pstLogicFsImage->last_frame = 1;
                    }
                    
                    ret = InsertImgToVoQueue(pHevcCtx->ChanID, VFMW_HEVC, pHevcCtx, &pHevcCtx->ImageQue, pstLogicFsImage);
                    if (VF_OK != ret)
                    {
                        dprint(PRN_FATAL, "%s InsertVO err:%d, ClearAll\n", __func__, ret);
                        FSP_SetDisplay(pHevcCtx->ChanID, pFrameStore->logic_fs_id, 0);
                        HEVC_ClearAll(pHevcCtx,1);
                        ret = LAST_OUTPUT_FAIL;
                    }
                    HEVC_SetFrmRepeatCount(pHevcCtx, pstLogicFsImage);
                    pHevcCtx->OutputFrameNum++;
                    pHevcCtx->PicOutCounter++;
                    if (1 == pHevcCtx->DPB.used_size)
                    {
                        ret = LAST_OUTPUT_OK;
                    }
                }
            }
        }

        // free frame store and move empty store to end of buffer
        HEVC_RemoveApcStore(pHevcCtx, pos);
        HEVC_RemoveFrameStoreOutDPB(pHevcCtx, pos);
    }

    if (LAST_OUTPUT_OK != ret)
    {
        ret = GetVoLastImageID(&pHevcCtx->ImageQue);
    }
    
  #if (TEST_PRINT_ENABLE == 1)
    dprint(PRN_ALWS, "HEVC flush last frame, ret = %d\n", ret);
  #endif

    return ret;
}


SINT32 HEVCDEC_GetImageWidth(HEVC_CTX_S *pHevcCtx)
{
    UINT32 uImageWidth = 0;
    uImageWidth = (((UINT32)pHevcCtx->pCurrSPS->pic_width_in_luma_samples + (UINT32)pHevcCtx->pCurrSPS->min_cb_sizeY - 1) & (~((UINT32)pHevcCtx->pCurrSPS->min_cb_sizeY - 1)));
    return uImageWidth;
}

SINT32 HEVCDEC_GetImageHeight(HEVC_CTX_S *pHevcCtx)
{
    UINT32 uImageHeight = 0;
    uImageHeight = (((UINT32)pHevcCtx->pCurrSPS->pic_height_in_luma_samples + (UINT32)pHevcCtx->pCurrSPS->min_cb_sizeY - 1) & (~((UINT32)pHevcCtx->pCurrSPS->min_cb_sizeY - 1)));
    return uImageHeight;
}
#endif //HEVC_VFMW_ENABLE

