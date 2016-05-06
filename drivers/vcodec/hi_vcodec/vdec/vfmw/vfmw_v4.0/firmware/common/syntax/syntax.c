/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r38Q5WHnC73TsvSY6qCiPiaQMTMhAE+e74f+ErywNJ3Zv82bsOM6XJ/eABKppwppjRg85
8InPVasij3A6k4qUyFew1xfGNTAcNRtrVLc94jICHsHRDud2RJg97NoJJtNJvA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

#include "syntax.h"
#include "public.h"
#include "vfmw_ctrl.h"
#include "fsp.h"

SINT32 SegMan(SINT32 ChanID, STREAM_SEG_PACKET_S *pSegMan);
VOID ReleasePacket(VID_STD_E VidStd, VOID *pCtx);

extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];


/*********************************************************************************
函数原型
SINT32  InitVoQueue (SINT32 queue_size )
功能描述
初始化图像输出队列
参数说明
queue_size：VO队列的容量，取值1~MAX_QUEUE_IMAGE_NUM
返回值
如果初始化成功返回1，否则返回错误码
*********************************************************************************/
SINT32 InitVoQueue(IMAGE_VO_QUEUE *pstVoQue)
{
    dprint(PRN_QUEUE, "Initializing VO queue\n");

    /* 队列控制变量 */
    pstVoQue->max_queue_size = MAX_QUEUE_IMAGE_NUM; 
    pstVoQue->queue_size = 0;
    pstVoQue->history = 0;
    pstVoQue->head = 0;
    pstVoQue->tail = 0;

    /* 防止重复释放魔术字 */
    pstVoQue->ResetMagicWord = 0;
    
    /* 信息变化检测器 */
    pstVoQue->SideInfo.OldAspectRatio = 0xffffffff;
    pstVoQue->SideInfo.OldDispCenter  = 0xffffffff;
    pstVoQue->SideInfo.OldDispSize    = 0xffffffff;
    pstVoQue->SideInfo.OldFrameRate   = 0xffffffff;
    pstVoQue->SideInfo.OldScanType    = 0xffffffff;
    pstVoQue->SideInfo.OldSeqCnt      = 0xffffffff;
    pstVoQue->SideInfo.SeqImgCnt      = 0;

    return ( VF_OK );
}

VOID PrintVoQueue(IMAGE_VO_QUEUE *pstVoQue)
{
    UINT32 i;
    
    dprint(PRN_ERROR, "VoQueue state: head(%d) history(%d) tail(%d)", 
            pstVoQue->head, pstVoQue->history, pstVoQue->tail);

    for ( i=pstVoQue->history; ; i++ )
    {
        i &= 63;
        if (i == pstVoQue->tail)
        {
            break;
        }
        if (i%8 == 0)
        {
            dprint(PRN_ERROR, "\n");
        }
        dprint(PRN_ERROR, "%d ", pstVoQue->image_ptr[i]->image_id);
    }
    dprint(PRN_ERROR, "\n");

    return;
}

VOID ResetVoQueue(IMAGE_VO_QUEUE *pstVoQue)
{
    /* 队列控制变量 */
    VFMW_OSAL_SpinLock(G_SPINLOCK_VOQUEUE);

    if (pstVoQue->head != pstVoQue->history
     || pstVoQue->head != pstVoQue->tail)
    {
        dprint(PRN_ERROR, "ResetVoQueue but queue not empty: head(%d) history(%d) tail(%d)\n", pstVoQue->head, pstVoQue->history, pstVoQue->tail);
    }

    pstVoQue->max_queue_size = MAX_QUEUE_IMAGE_NUM; 
    pstVoQue->queue_size = 0;
    pstVoQue->history = 0;
    pstVoQue->head = 0;
    pstVoQue->tail = 0;

    /* 防止重复释放魔术字 */
    pstVoQue->ResetMagicWord += IMG_ID_MAGIC_STEP;

    /* 信息变化检测器 */
    pstVoQue->SideInfo.OldAspectRatio = 0xffffffff;
    pstVoQue->SideInfo.OldDispCenter  = 0xffffffff;
    pstVoQue->SideInfo.OldDispSize    = 0xffffffff;
    pstVoQue->SideInfo.OldFrameRate   = 0xffffffff;
    pstVoQue->SideInfo.OldScanType    = 0xffffffff;
    pstVoQue->SideInfo.OldSeqCnt      = 0xffffffff;
    pstVoQue->SideInfo.SeqImgCnt      = 0;   
    //pstVoQue->SideInfo.LastImageIdPlus2  = 0;   // 改值不用初始化，第一次传进来的就为0，以后进来保持原值不变

    /* 初始化PTS计算上下文 */
	pstVoQue->SideInfo.PrevPts = (UINT64)(-1);
	pstVoQue->SideInfo.PrevNumFramesBtwPTS = 0;
	pstVoQue->SideInfo.AveragePtsStep = 0;
	
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_VOQUEUE);

    return;
}


VOID ReturnImageToSyntax( VID_STD_E eVidStd, VOID *pCtx, IMAGE *p_image )
{
    switch( eVidStd )
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            H264DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
	#ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
            HEVC_DECRecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            MVC_DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            MPEG2DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            MPEG4DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            AVSDEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            VC1DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            REAL8DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            REAL9DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            DIVX3DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            VP8DEC_RecycleImage(pCtx, p_image->image_id);
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
    	case  VFMW_VP6:
        case  VFMW_VP6F:
        case  VFMW_VP6A:
            VP6DEC_RecycleImage(pCtx, p_image->image_id);
    		break;
    #endif
        default:
            break;
    }

    return;
}


UINT64 ProduceTimeStamp(IMAGE_VO_QUEUE *pstVoQue, IMAGE *p_image, VID_STD_E eVidStd )
{
    UINT64 ThisFramePts = p_image->PTS;
    UINT64 InferedPTS = 0;

    IMAGE_SIDE_INFO_S *pstSideInfo = &pstVoQue->SideInfo;

    if ( (ThisFramePts - pstSideInfo->PrevPts <= 5 && pstSideInfo->PrevPts != (UINT64)(-1))
      || (((VFMW_REAL8 == eVidStd) || (VFMW_REAL9 == eVidStd)) && (2 == (p_image->format & 3))) )
    {
        ThisFramePts = (UINT64)(-1);
        if ( (VFMW_REAL8 == eVidStd) || (VFMW_REAL9 == eVidStd) )
        {
            p_image->SrcPts = (UINT64)(-1);
        }
    }
    InferedPTS = ThisFramePts;

    return InferedPTS;
}


/*********************************************************************************
函数原型
SINT32  InsertImgToVoQueue(SINT32 ChanID, IMAGE *p_image)
功能描述
将指定的图像插入到VO队列中
参数说明
p_image：待插入队列的图像描述
返回值
如果插入成功则返回1，否则（超时）返回错误码
算法描述
*********************************************************************************/
SINT32 InsertImgToVoQueue(SINT32 ChanID, VID_STD_E eVidStd, VOID *pCtx, IMAGE_VO_QUEUE *pstVoQue, IMAGE *p_image)
{
    SINT32 i;
    UINT32 dat = 0;
    UINT32 dsize, dcenter;
	UINT32 CurTime, Period;
    UINT32 AspectRatio, ScanType;
	VFMW_CHAN_STAT_S *pVfmwChanStat = &g_VfmwChanStat[ChanID];
    static UINT32 last_rec_pos_time[MAX_CHAN_NUM] = {0};
    IMAGE_SIDE_INFO_S *pstImageSideInfo = &pstVoQue->SideInfo;

    /* 入口参数检查 */
    if ( NULL == p_image )
    {
        dprint(PRN_FATAL, "image point NULL\n");
        return VF_ERR_PARAM;
    }

    VFMW_OSAL_SpinLock(G_SPINLOCK_VOQUEUE);

    /* 检查这幅图是否重复插入了 */
    for ( i=pstVoQue->history; ; i++ )
    {
        i &= 63;
        if ( i == pstVoQue->tail )
        {
            break;
        }
        
        if ( NULL == pstVoQue->image_ptr[i] )
        {
            continue;
        }

        if ( pstVoQue->image_ptr[i]->image_id == p_image->image_id)
        {
            dprint(PRN_FATAL,"FATAL: p_image(id=%d) has already in the VoQueue!\n",p_image->image_id);
            p_image->error_level = 1000;
        }
    }

    /* 如果图象不符合要求，拒绝接受 */
    if ( p_image->error_level > 100 || p_image->image_width < 32 || p_image->image_height < 32 )
    {
        dprint(PRN_FATAL, "error=%d,W=%d,H=%d,not acceptable!\n",p_image->error_level,p_image->image_width,p_image->image_height);
	    /*     如果是图像重复插入错误不应该在此释放，因为这可能导致永远无法输出图像. 例如:
	       队列中只有1个图(id=0)，某种未知错误导致又插入一次id=0的图，如果释放掉，则下一次很可能又把图像解在0号帧存，
	       又一次插入失败....., 后级设备拿不到新图，所以不会释放这个id=0的帧，而正是因为此帧在队列，解码器又插不进
	       有效的新帧，表现出来的是解码死掉(但码流在快速消耗).
	           为了避免此种情形，增加if (p_image->error_level != 1000)条件*/
		if (p_image->error_level != 1000)
		{
            ReturnImageToSyntax( eVidStd, pCtx, p_image );
		}
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_VOQUEUE);
        return VF_OK;
    }
    
    /* 补全PTS */
    p_image->SrcPts = p_image->PTS;
    p_image->PTS = ProduceTimeStamp(pstVoQue, p_image, eVidStd);
	dprint(PRN_PTS, "out_pts: %lld -> %lld Usertag %lld\n", p_image->SrcPts, p_image->PTS,p_image->Usertag);
	if (p_image->PTS == (UINT64)(-1))
    {
        p_image->PTS = PTS_NO_USE;
    }
    if (p_image->SrcPts == (UINT64)(-1))
    {
        p_image->SrcPts = PTS_NO_USE;
    }

    /* 如果显示区域为空，则置为与解码大小一致 */
    if ( (0==p_image->disp_width) || (0==p_image->disp_height) || (VFMW_H264 != eVidStd && VFMW_MVC != eVidStd && VFMW_HEVC != eVidStd) )
    {
	    p_image->disp_center_x = p_image->image_width / 2;
	    p_image->disp_center_y = p_image->image_height / 2;
	    p_image->disp_width = p_image->image_width;
	    p_image->disp_height = p_image->image_height;
    }

    /* 从p_image的format中提取相关信息，放到SideInfo中供上层查询 */
    pstImageSideInfo->ImageWidth  = p_image->image_width;
    pstImageSideInfo->ImageHeight = p_image->image_height;
    pstImageSideInfo->VideoFormat = ((p_image->format >> 5) & 7);
    pstImageSideInfo->ImageFormat = p_image->format;
    
    AspectRatio = ((p_image->format >> 14) & 7);
    ScanType    = ((p_image->format >> 8) & 3);
    dsize = (p_image->disp_height << 16) | (p_image->disp_width&0xffff);
    dcenter = (p_image->disp_center_x << 16) | (p_image->disp_center_y&0xffff);

    /* 更新图像的序列内编号 */
    if( p_image->seq_cnt != pstImageSideInfo->OldSeqCnt )
    {
        pstImageSideInfo->SeqCnt = p_image->seq_cnt;
    }
    p_image->seq_img_cnt = pstImageSideInfo->SeqImgCnt++;

    /* 检查图像的信息变化，并上报上层软件 */
    if( pstImageSideInfo->OldAspectRatio != AspectRatio ) /* 宽高比变化? */
    {
        REPORT_ASPR_CHANGE( ChanID, pstImageSideInfo->OldAspectRatio, AspectRatio );
        pstImageSideInfo->OldAspectRatio = AspectRatio;
    }
    if( pstImageSideInfo->OldScanType != ScanType )  /* 扫描类型变化? */
    {
        REPORT_SCAN_CHANGE(ChanID, ScanType);
        pstImageSideInfo->OldScanType = ScanType;
    }
    if( pstImageSideInfo->OldDispSize != dsize || pstImageSideInfo->OldDispCenter != dcenter ) /* 显示区域变化? */
    {
        pstImageSideInfo->OldDispSize = dsize;
        pstImageSideInfo->OldDispCenter = dcenter;
        REPORT_DISP_AREA_CHANGE(ChanID, p_image->disp_width, p_image->disp_height, p_image->disp_center_x, p_image->disp_center_y);
    }

    /* 补充图像的顶底场地址 */
    p_image->top_luma_phy_addr  = p_image->luma_phy_addr;
    p_image->btm_luma_phy_addr  = p_image->luma_phy_addr + p_image->image_stride;
    p_image->top_chrom_phy_addr = p_image->chrom_phy_addr;
    p_image->btm_chrom_phy_addr = p_image->chrom_phy_addr + p_image->image_stride;
    
#ifdef ENV_SOS_KERNEL 
    p_image->is_secure = 1;
#else
    p_image->is_secure = 0;
#endif

    dprint(PRN_QUEUE, "Queue=(%02d,%02d,%02d) + F%d\n", pstVoQue->history, pstVoQue->head, pstVoQue->tail, p_image->image_id );
    
    /* 将p_image插入到tail所指示的位置 */
    pstVoQue->image_ptr[pstVoQue->tail] = p_image;

    /* 移动队列尾指针，队列大小加1 */
    pstVoQue->tail = (pstVoQue->tail+1) & (MAX_QUEUE_IMAGE_NUM-1);

    pVfmwChanStat->u32IsFieldFlag = p_image->is_fld_save;

    pstImageSideInfo->LastImageIdPlus2 = p_image->image_id + 2;
    
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_VOQUEUE);

    /* 向上层程序发送“新帧就绪”的消息 */
    REPORT_IMGRDY(ChanID, p_image);

    if (CHECK_REC_POS_ENABLE(STATE_1D_TO_QUEUE))
    {
        CurTime = VFMW_OSAL_GetTimeInMs();
        if ((CurTime - last_rec_pos_time[ChanID]) > g_TraceFramePeriod)
        {
            last_rec_pos_time[ChanID] = CurTime;
            dat = ((ChanID)<<24) + (STATE_1D_TO_QUEUE<<16);
            REC_POS(dat);
        }
    }

    /* 统计帧率, 每1s统计一次 */
    pVfmwChanStat->u32FrImgNum++;
    CurTime = VFMW_OSAL_GetTimeInMs();
    Period = CurTime - pVfmwChanStat->u32FrBeginTime;
    if (Period >= 1000)
    {
        if (pVfmwChanStat->u32FrImgNum > 0)
        {
            pVfmwChanStat->u32FrFrameRate = pVfmwChanStat->u32FrImgNum * 10000 / Period;
		}

		pVfmwChanStat->u32FrBeginTime = CurTime;
		pVfmwChanStat->u32FrImgNum = 0;
	}

    return(VF_OK);
}

/*********************************************************************************
函数原型
VOID  GetQueueImgNum( SINT32 *pReadImgNum, SINT32 *pNewImgNum )
功能描述
获取队列中的图像数目
参数说明
pReadImgNum：已被读走，但尚未释放的图像个数( history ~ head )
pNewImgNum:  已插入队列还没有被读走的图像个数( head ~ tail )
返回值
无
算法描述
*********************************************************************************/
VOID GetQueueImgNum( IMAGE_VO_QUEUE *pstVoQue, SINT32 *pReadImgNum, SINT32 *pNewImgNum )
{
    SINT32 ReadNum, NewNum;

    VFMW_OSAL_SpinLock(G_SPINLOCK_VOQUEUE);

    ReadNum = (pstVoQue->head >= pstVoQue->history)? (pstVoQue->head - pstVoQue->history) :
    (pstVoQue->head + MAX_QUEUE_IMAGE_NUM - pstVoQue->history);

    NewNum  = (pstVoQue->tail >= pstVoQue->head)? (pstVoQue->tail - pstVoQue->head) :
    (pstVoQue->tail + MAX_QUEUE_IMAGE_NUM - pstVoQue->head);

    *pReadImgNum = (SINT32)ReadNum;
    *pNewImgNum  = (SINT32)NewNum;

    VFMW_OSAL_SpinUnLock(G_SPINLOCK_VOQUEUE);

    return;
}

/*********************************************************************************
从VDM图像队列中获取一幅图像
*********************************************************************************/
SINT32 SYNTAX_ReceiveImage ( SYNTAX_CTX_S *pSynCtx, IMAGE *p_image )
{
    SINT32 ChanID = -1;
    SINT32 ret;
    IMAGE_VO_QUEUE *pstVoQue = NULL;
 
    if ( NULL == p_image || NULL == pSynCtx )
    {
        return( VF_ERR_PARAM );
    }

    /* 获取图像队列 */
    switch (pSynCtx->eVidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            ChanID   = pSynCtx->unSyntax.stH264Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stH264Ctx.ImageQue;
            break;
    #endif
	#ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
            ChanID   = pSynCtx->unSyntax.stHevcCtx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stHevcCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            ChanID   = pSynCtx->unSyntax.stMvcCtx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stMvcCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            ChanID   = pSynCtx->unSyntax.stMpeg2Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stMpeg2Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            ChanID   = pSynCtx->unSyntax.stMpeg4Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stMpeg4Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            ChanID   = pSynCtx->unSyntax.stAvsCtx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stAvsCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            ChanID   = pSynCtx->unSyntax.stVc1Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stVc1Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            ChanID   = pSynCtx->unSyntax.stReal8Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stReal8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            ChanID   = pSynCtx->unSyntax.stReal9Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stReal9Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            ChanID   = pSynCtx->unSyntax.stDivx3Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stDivx3Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            ChanID   = pSynCtx->unSyntax.stVp8Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stVp8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
    	case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            ChanID   = pSynCtx->unSyntax.stVp6Ctx.ChanID;
            pstVoQue = &pSynCtx->unSyntax.stVp6Ctx.ImageQue;
    		break;
    #endif
        default:
        return VF_ERR_PARAM;
    }
    
    VFMW_OSAL_SpinLock(G_SPINLOCK_VOQUEUE);

    /* 检查解码图队列是否空，若非空则从队列取一个图象 */
    if( pstVoQue->head != pstVoQue->tail )
    {
        /* 取head所指示的图像信息指针 */
        memcpy( p_image, pstVoQue->image_ptr[pstVoQue->head], sizeof(IMAGE) );

        dprint( PRN_QUEUE, "Queue=(%02d,%02d,%02d) - F%d\n",
            pstVoQue->history, pstVoQue->head, pstVoQue->tail, p_image->image_id );

        p_image->image_id += pstVoQue->ResetMagicWord;

        /* 移动队头指针，队列大小减1 */
        pstVoQue->head = (pstVoQue->head+1) & (MAX_QUEUE_IMAGE_NUM-1);
        
        FSP_ExtBufHandler(ChanID, BC_REPORT_BUF, &p_image->top_luma_phy_addr);

        ret = VF_OK;
    }
    else
    {
        ret = VF_TIME_OUT;
    }

    VFMW_OSAL_SpinUnLock(G_SPINLOCK_VOQUEUE);

    return ret;
}

/*********************************************************************************
释放一幅图像给VDM驱动。系统软件调用此函数表明p_image所描述的图像已经使用，不再需
要保存，其存储空间可以被后续解码过程重新分配
*********************************************************************************/
SINT32 SYNTAX_ReleaseImage( SYNTAX_CTX_S *pSynCtx, IMAGE *p_image )
{
    SINT32 i, j, ret = VF_ERR_PARAM;
    SINT32 SameImageFlag = 0;
    IMAGE_VO_QUEUE *pstVoQue = NULL;

    /* 入口参数检查 */
    if( NULL == p_image )
    {
        dprint(PRN_FATAL, "%s unsupport p_image is null.\n", __func__);
        return VF_ERR_PARAM;
    }

    /* 获取图像队列 */
    switch(pSynCtx->eVidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            pstVoQue = &pSynCtx->unSyntax.stH264Ctx.ImageQue;
            break;
    #endif
	#ifdef VFMW_HEVC_SUPPORT
		case VFMW_HEVC:
		    pstVoQue = &pSynCtx->unSyntax.stHevcCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            pstVoQue = &pSynCtx->unSyntax.stMvcCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            pstVoQue = &pSynCtx->unSyntax.stMpeg2Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            pstVoQue = &pSynCtx->unSyntax.stMpeg4Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            pstVoQue = &pSynCtx->unSyntax.stAvsCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            pstVoQue = &pSynCtx->unSyntax.stVc1Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            pstVoQue = &pSynCtx->unSyntax.stReal8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            pstVoQue = &pSynCtx->unSyntax.stReal9Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            pstVoQue = &pSynCtx->unSyntax.stDivx3Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            pstVoQue = &pSynCtx->unSyntax.stVp8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
    	case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            pstVoQue = &pSynCtx->unSyntax.stVp6Ctx.ImageQue;
    		break;
    #endif

        default:
            dprint(PRN_FATAL, "%s unsupport std %d.\n", __func__, pSynCtx->eVidStd);
            return VF_ERR_PARAM;
    }

    VFMW_OSAL_SpinLock(G_SPINLOCK_VOQUEUE);

    /* 从魔术字中还原图像ID */
    p_image->image_id -= pstVoQue->ResetMagicWord;

    /* 在history和head之间搜索与p_image匹配的图并将其释放 */
    for ( i = pstVoQue->history; ; i++ )
    {
        i &= (MAX_QUEUE_IMAGE_NUM-1);  /* 若i跨越MAX_QUEUE_IMAGE_NUM，则卷绕到0 */
        if ( i == pstVoQue->head )
        {
            dprint(PRN_ERROR, "%s: image %d not found in queue.\n", __func__, p_image->image_id);
            break;                     /* 所有读出图都已被扫描，退出循环 */
        }

        /* 判断'p_image'所指示的图像是否与pstVoQue->image_ptr[i]是同一幅图 */
        if( NULL != pstVoQue->image_ptr[i] ) /* 由于没有锁保护，多线程释放有可能造成队列指针空的情况 */
        {
            if (p_image->image_id == pstVoQue->image_ptr[i]->image_id)
            {
                SameImageFlag = 1;
            }
            else
            {
                SameImageFlag = 0;
            }
        }
        else
        {
            dprint(PRN_FATAL, "%s image[%d] null\n", __func__, i);
            SameImageFlag = 2;  /* 发现空成员(出错了)，需要将其挤掉，但不能调用协议层的回收接口 */
        }

        if ( 0 != SameImageFlag )
        {
            /* 从VO队列中清除这个图，并将history到i-1之间的队列节点顺次移动一格 */
            while(1)
            {
                j = (i==0)? (MAX_QUEUE_IMAGE_NUM-1): (i-1);
                pstVoQue->image_ptr[i] = pstVoQue->image_ptr[j];
                if( i == pstVoQue->history )
                {
                    break;
                }
                else
                {
                    i = j;
                }
            }
            pstVoQue->history += 1;                       /* history前移一步 */
            pstVoQue->history &= (MAX_QUEUE_IMAGE_NUM-1); /* 若触底则卷绕到0 */

            if ( 1 == SameImageFlag ) /* 此时如果不等于1，那一定等于2。等于2说明发生了异常 */
            {
                dprint(PRN_QUEUE, "Queue=(%02d,%02d,%02d) x F%d\n", pstVoQue->history, pstVoQue->head, pstVoQue->tail, p_image->image_id );

                /* 调用各协议的recycle接口释放空间 */
                ret = VF_ERR_PARAM;
                switch(pSynCtx->eVidStd)
                {
                #ifdef VFMW_H264_SUPPORT
                    case  VFMW_H264:
                        ret = H264DEC_RecycleImage(&pSynCtx->unSyntax.stH264Ctx, p_image->image_id );
                        ret = (ret==H264_OK)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_HEVC_SUPPORT
                    case  VFMW_HEVC:
                        ret = HEVC_DECRecycleImage(&pSynCtx->unSyntax.stHevcCtx, p_image->image_id );
                        ret = (ret==HEVC_DEC_NORMAL)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_MVC_SUPPORT
                    case  VFMW_MVC:
                        ret = MVC_DEC_RecycleImage(&pSynCtx->unSyntax.stMvcCtx, p_image->image_id );
                        ret = (ret==MVC_OK)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_AVS_SUPPORT
                    case  VFMW_AVS:
                        ret = AVSDEC_RecycleImage(&pSynCtx->unSyntax.stAvsCtx, p_image->image_id );
                        ret = (ret==AVS_TRUE)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_MPEG2_SUPPORT
                    case  VFMW_MPEG2:
                        ret = MPEG2DEC_RecycleImage( &pSynCtx->unSyntax.stMpeg2Ctx, p_image->image_id );
                        ret = (ret==MPEG2_TRUE)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_MPEG4_SUPPORT
                    case  VFMW_MPEG4:
                        ret = MPEG4DEC_RecycleImage( &pSynCtx->unSyntax.stMpeg4Ctx, p_image->image_id );
                        ret = (ret==VF_OK)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_VC1_SUPPORT
                    case  VFMW_VC1:
                        ret = VC1DEC_RecycleImage( &pSynCtx->unSyntax.stVc1Ctx, p_image->image_id );
                        ret = (ret==VF_OK)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_REAL8_SUPPORT
                    case  VFMW_REAL8:
                        ret = REAL8DEC_RecycleImage( &pSynCtx->unSyntax.stReal8Ctx, p_image->image_id );
                        ret = (ret==RV8_VFMW_TRUE)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_REAL9_SUPPORT
                    case  VFMW_REAL9:
                        ret = REAL9DEC_RecycleImage( &pSynCtx->unSyntax.stReal9Ctx, p_image->image_id );
                        ret = (ret==RV9_VFMW_TRUE)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_DIVX3_SUPPORT
                    case  VFMW_DIVX3:
                        ret = DIVX3DEC_RecycleImage( &pSynCtx->unSyntax.stDivx3Ctx, p_image->image_id );
                        ret = (ret==DIVX3_VFMW_TRUE)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_VP8_SUPPORT
                    case  VFMW_VP8:
                        ret = VP8DEC_RecycleImage(&pSynCtx->unSyntax.stVp8Ctx, p_image->image_id );
                        ret = (ret==VP8_VFMW_TRUE)? VF_OK: VF_ERR_SYS;
                        break;
                #endif
                #ifdef VFMW_VP6_SUPPORT
                    case  VFMW_VP6:
                    case  VFMW_VP6F:
                    case  VFMW_VP6A:
                    	ret = VP6DEC_RecycleImage(&pSynCtx->unSyntax.stVp6Ctx, p_image->image_id );
                    	ret = (ret==VP6_VFMW_TRUE)? VF_OK: VF_ERR_SYS;
    					break;
                #endif
                    default:
                        dprint(PRN_FATAL, "%s unsupport std %d to recycle image.\n", __func__, pSynCtx->eVidStd);
                        ret = VF_ERR_PARAM;
                }

                if (ret != VF_OK)
                {
                    dprint(PRN_FATAL, "%s recycle image failed.\n", __func__);
                }
                break;  /* 释放帧存已处理，无需扫描其余图像，退出循环 */
            }
        }
    }

    VFMW_OSAL_SpinUnLock(G_SPINLOCK_VOQUEUE);

    return ret;
}

SINT32 SYNTAX_ReturnImage(SYNTAX_CTX_S *pSynCtx)
{
    IMAGE_VO_QUEUE *pstVoQue = NULL;

  /* 获取图像队列 */
    switch(pSynCtx->eVidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            pstVoQue = &pSynCtx->unSyntax.stH264Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
            pstVoQue = &pSynCtx->unSyntax.stHevcCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            pstVoQue = &pSynCtx->unSyntax.stMvcCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            pstVoQue = &pSynCtx->unSyntax.stMpeg2Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            pstVoQue = &pSynCtx->unSyntax.stMpeg4Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
            pstVoQue = &pSynCtx->unSyntax.stAvsCtx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            pstVoQue = &pSynCtx->unSyntax.stVc1Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            pstVoQue = &pSynCtx->unSyntax.stReal8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            pstVoQue = &pSynCtx->unSyntax.stReal9Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            pstVoQue = &pSynCtx->unSyntax.stDivx3Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            pstVoQue = &pSynCtx->unSyntax.stVp8Ctx.ImageQue;
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
    	case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            pstVoQue = &pSynCtx->unSyntax.stVp6Ctx.ImageQue;
    		break;
    #endif

        default:
            return VF_ERR_PARAM;
    }

    /* 移动队头指针，队列大小减1 */
    VFMW_OSAL_SpinLock(G_SPINLOCK_VOQUEUE);
    pstVoQue->head = (pstVoQue->head-1) & (MAX_QUEUE_IMAGE_NUM-1);
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_VOQUEUE);

    return (VF_OK);
}


/********************************************************************************
********************************************************************************/
VOID DecodeStream( STREAM_SEG_PACKET_S *pSegMan, SINT32 VideoStandard, VOID *pstCtx )
{
    SINT32 ret;
    SINT32 ChanID = -1;
#ifdef VFMW_H264_SUPPORT
    H264_STREAM_PACKET  H264Pack;
#endif
#ifdef VFMW_HEVC_SUPPORT
    HEVC_STREAM_PACKET  HevcPack;
#endif
#ifdef VFMW_MVC_SUPPORT
    MVC_STREAM_PACKET   MvcPack;
#endif
#ifdef VFMW_VC1_SUPPORT
    SINT32 Vc1SMPHeadLenInByte;
#endif

    switch( VideoStandard )
    {
#ifdef VFMW_H264_SUPPORT
    case VFMW_H264:
        ChanID = ((H264_CTX_S*)pstCtx)->ChanID;
        H264Pack.pts = pSegMan->CurrSeg.Pts;
        H264Pack.p_stream = pSegMan->CurrSeg.VirAddr;
        H264Pack.strm_phy_addr = pSegMan->CurrSeg.PhyAddr;
        H264Pack.stream_len = pSegMan->CurrSeg.LenInByte;
        H264Pack.last_pack_in_nal = pSegMan->CurrSeg.IsLastSeg;
        H264Pack.StreamID = pSegMan->CurrSeg.StreamID;
        H264Pack.pack_is_pic_over_flag = pSegMan->CurrSeg.DspCheckPicOverFlag;
        ret = H264DEC_DecodePacket((H264_CTX_S*)pstCtx, &H264Pack);
        if (H264_NOTDEC == ret)
        {
            pSegMan->IsCurrSegWaitDec = 1;
        }
        else
        {
            pSegMan->IsCurrSegWaitDec = 0;
        }
        if(NULL == ((H264_CTX_S*)pstCtx)->pH264DecParam && 1 == ((H264_CTX_S*)pstCtx)->IsStreamEndFlag)
        {
            VCTRL_OutputLastFrame(ChanID);
            ((H264_CTX_S*)pstCtx)->IsStreamEndFlag = 0;
        }
        break;
#endif
#ifdef VFMW_HEVC_SUPPORT
    case VFMW_HEVC:
        ChanID = ((HEVC_CTX_S*)pstCtx)->ChanID;
        HevcPack.pts = pSegMan->CurrSeg.Pts;
        HevcPack.p_stream = pSegMan->CurrSeg.VirAddr;
        HevcPack.strm_phy_addr = pSegMan->CurrSeg.PhyAddr;
        HevcPack.stream_len = pSegMan->CurrSeg.LenInByte;
        HevcPack.last_pack_in_nal = pSegMan->CurrSeg.IsLastSeg;
        HevcPack.StreamID = pSegMan->CurrSeg.StreamID;
        HevcPack.pack_is_pic_over_flag = pSegMan->CurrSeg.DspCheckPicOverFlag;
        ret = HEVCDEC_DecodePacket((HEVC_CTX_S*)pstCtx, &HevcPack);
        if (HEVC_NOTDEC == ret)
        {
            pSegMan->IsCurrSegWaitDec = 1;
        }
        else
        {
            pSegMan->IsCurrSegWaitDec = 0;
        }

        if (NULL == ((HEVC_CTX_S*)pstCtx)->pHevcDecParam && 1 == ((HEVC_CTX_S*)pstCtx)->IsStreamEndFlag)
        {
            VCTRL_OutputLastFrame(ChanID);
            ((HEVC_CTX_S*)pstCtx)->IsStreamEndFlag = 0;
        }
        break;
#endif
#ifdef VFMW_MVC_SUPPORT
    case VFMW_MVC:
        ChanID = ((MVC_CTX_S*)pstCtx)->ChanID;
        MvcPack.pts = pSegMan->CurrSeg.Pts;
        MvcPack.p_stream = pSegMan->CurrSeg.VirAddr;
        MvcPack.strm_phy_addr = pSegMan->CurrSeg.PhyAddr;
        MvcPack.stream_len = pSegMan->CurrSeg.LenInByte;
        MvcPack.last_pack_in_nal = pSegMan->CurrSeg.IsLastSeg;
        MvcPack.StreamID = pSegMan->CurrSeg.StreamID;
        ret = MVC_DEC_DecodePacket((MVC_CTX_S*)pstCtx, &MvcPack);
        if (MVC_NOTDEC == ret)
        {
            pSegMan->IsCurrSegWaitDec = 1;
        }
        else
        {
            pSegMan->IsCurrSegWaitDec = 0;
        }
        if(NULL == ((MVC_CTX_S*)pstCtx)->pMvcDecParam && 1 == ((MVC_CTX_S*)pstCtx)->IsStreamEndFlag)
        {
            VCTRL_OutputLastFrame(ChanID);
            ((MVC_CTX_S*)pstCtx)->IsStreamEndFlag = 0;
        }
        break;
#endif
#ifdef VFMW_VC1_SUPPORT
    case VFMW_VC1:
        ChanID = ((VC1_CTX_S*)pstCtx)->ChanID;
        if ((((VC1_CTX_S*)pstCtx)->pstExtraData->StdExt.Vc1Ext.IsAdvProfile != 0) && (((VC1_CTX_S*)pstCtx)->pstExtraData->StdExt.Vc1Ext.IsAdvProfile != 1))
        {
            dprint(PRN_FATAL, "ERROR: Wrong PreParseInfo about Vc1 IsAdvProfile!\n");
            return;
        }
        if (((VC1_CTX_S*)pstCtx)->pstExtraData->StdExt.Vc1Ext.CodecVersion > 8)
        {
            dprint(PRN_FATAL, "ERROR: Wrong PreParseInfo about Vc1 CodecVersion!\n");
            return;
        }

        ((VC1_CTX_S*)pstCtx)->CodecInfo.PreParseInfo.IsAdvProfile = ((VC1_CTX_S*)pstCtx)->pstExtraData->StdExt.Vc1Ext.IsAdvProfile;
        ((VC1_CTX_S*)pstCtx)->CodecInfo.PreParseInfo.CodecVersion = ((VC1_CTX_S*)pstCtx)->pstExtraData->StdExt.Vc1Ext.CodecVersion;

        if (1 == ((VC1_CTX_S*)pstCtx)->CodecInfo.PreParseInfo.IsAdvProfile)
        {
            if (VC1_NOT_DEC == VC1_GetPacketState((VC1_CTX_S*)pstCtx))
            {
                if((1 != s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) || \
                  ((1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) && \
                  (0 == s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag)))//l00273086 区分动态帧存中的重送数据和正常解码过程中的重送数据
                {
                    VC1DEC_Decode((VC1_CTX_S*)pstCtx, &((VC1_CTX_S*)pstCtx)->LastPacket);
                }
            }

            ret = SegMan(ChanID, pSegMan);
            if (SYN_OK == ret)
            {
                VC1DEC_Decode((VC1_CTX_S*)pstCtx, &(pSegMan->Pack));
                memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            }

            if(NULL == ((VC1_CTX_S*)pstCtx)->pVc1DecParam && 1 == ((VC1_CTX_S*)pstCtx)->CodecInfo.IsStreamEndFlag)
            {
                VCTRL_OutputLastFrame(ChanID);
                ((VC1_CTX_S*)pstCtx)->CodecInfo.IsStreamEndFlag = 0;
            }
        }
        else
        {
            if (1 == pSegMan->CurrSeg.IsStreamEnd)
            {
                VCTRL_OutputLastFrame(ChanID);
                SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
                break;
            }
            Vc1SMPHeadLenInByte = 16;
            memcpy(&(pSegMan->Pack.StreamPack[0]),  &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S));
            memset(&(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S));

            /*SP MP码流至少长度为16 Bytes，对于SKIP_pic去除掉SMP码流头后码流长度<=1byte，因此码流总长度至少为16 Bytes*/
            if (pSegMan->Pack.StreamPack[0].LenInByte <= 15)
            {
                dprint(PRN_FATAL, "LENTH ERROR: VC1 S/MP BS is wrong!\n");
                SM_ReleaseStreamSeg(ChanID, pSegMan->Pack.StreamPack[0].StreamID);
                REPORT_DECSYNTAX_ERR(ChanID);
                return;
            }

            /*解析SMP码流头*/
            if (VDMHAL_OK == Vc1SMPSeqHdr(pSegMan->Pack.StreamPack[0].VirAddr, Vc1SMPHeadLenInByte, &(((VC1_CTX_S*)pstCtx)->CodecInfo.PreParseInfo)))
            {
                pSegMan->Pack.StreamPack[0].LenInByte -= Vc1SMPHeadLenInByte;
                pSegMan->Pack.StreamPack[0].VirAddr += Vc1SMPHeadLenInByte;
                pSegMan->Pack.StreamPack[0].PhyAddr += Vc1SMPHeadLenInByte;

                VC1DEC_Decode((VC1_CTX_S*)pstCtx, &(pSegMan->Pack));
                memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            }
            else
            {
                dprint(PRN_FATAL, "SYNTAX ERROR: VC1 S/MP BS is wrong!\n");
                SM_ReleaseStreamSeg(ChanID, pSegMan->Pack.StreamPack[0].StreamID);
                REPORT_DECSYNTAX_ERR(ChanID);
                return;
            }
        }
        break;
#endif
#ifdef VFMW_MPEG2_SUPPORT
    case VFMW_MPEG2:
        ChanID = ((MP2_CTX_S*)pstCtx)->ChanID;
        if(MPEG2_NOTDEC == MP2_GetPacketState((MP2_CTX_S*)pstCtx))
        {
            if((1 != s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) || \
              ((1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) && \
              (0 == s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag)))//l00273086 区分动态帧存中的重送数据和正常解码过程中的重送数据
            {
                MPEG2DEC_Decode((MP2_CTX_S*)pstCtx ,&(((MP2_CTX_S*)pstCtx)->stCurPacket));
            }
        }
        
        ret = SegMan(ChanID, pSegMan);
        if (SYN_OK == ret)
        {
            MPEG2DEC_Decode((MP2_CTX_S*)pstCtx, &(pSegMan->Pack));
            if (1 == ((MP2_CTX_S*)pstCtx)->IsWaitToReRange)
            {
                pSegMan->IsCurrSegWaitDec = 1;
            }
            else
            {
                pSegMan->IsCurrSegWaitDec = 0;
            }
        }
        else
        {
        }
        
        if(NULL == ((MP2_CTX_S*)pstCtx)->pMp2DecParam && 1 == ((MP2_CTX_S*)pstCtx)->IsStreamEndFlag)
        {
            VCTRL_OutputLastFrame(ChanID);
            ((MP2_CTX_S*)pstCtx)->IsStreamEndFlag = 0;
        }
        break;
#endif
#ifdef VFMW_MPEG4_SUPPORT
    case VFMW_MPEG4:
        ret = SYN_OK;
        ChanID = ((MP4_CTX_S*)pstCtx)->ChanID;
        if(MPEG4_NOTDEC == MP4_GetPacketState((MP4_CTX_S*)pstCtx))
        {
            if((1 != s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) || \
              ((1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) && \
              (0 == s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag)))//l00273086 区分动态帧存中的重送数据和正常解码过程中的重送数据
            {
                MPEG4DEC_Decode((MP4_CTX_S*)pstCtx ,&(((MP4_CTX_S*)pstCtx)->stCurPacket));
            }
        }

        ret = SegMan(ChanID, pSegMan);
        if (SYN_OK == ret)
        {
            MPEG4DEC_Decode(pstCtx, &(pSegMan->Pack));
        }

        /***************************************************************************************/
        if(NULL == ((MP4_CTX_S*)pstCtx)->pMp4DecParam && 1 == ((MP4_CTX_S*)pstCtx)->IsStreamEndFlag)
        {
            VCTRL_OutputLastFrame(ChanID);
            ((MP4_CTX_S*)pstCtx)->IsStreamEndFlag = 0;
        }
        break;
#endif
#ifdef VFMW_AVS_SUPPORT
    case VFMW_AVS:
        ChanID = ((AVS_CTX_S*)pstCtx)->ChanID;
        if(AVS_NOTDEC == AVS_GetPacketState((AVS_CTX_S*)pstCtx))
        {
            if((1 != s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) || \
              ((1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) && \
              (0 == s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag)))//l00273086 区分动态帧存中的重送数据和正常解码过程中的重送数据
            {
                AVSDEC_Decode((AVS_CTX_S*)pstCtx ,&(((AVS_CTX_S*)pstCtx)->LastPacket));
            }
        }
        
        ret = SegMan(ChanID, pSegMan);
        if (SYN_OK == ret)
        {
            AVSDEC_Decode((AVS_CTX_S*)pstCtx, &(pSegMan->Pack));
        }
        else
        {
        }
        
        if(NULL == ((AVS_CTX_S*)pstCtx)->pAvsDecParam && 1 == ((AVS_CTX_S*)pstCtx)->IsStreamEndFlag)
        {
            VCTRL_OutputLastFrame(ChanID);
            ((AVS_CTX_S*)pstCtx)->IsStreamEndFlag = 0;
        }
        break;
#endif
#ifdef VFMW_REAL8_SUPPORT
    case VFMW_REAL8:
        ChanID = ((RV8_CTX_S*)pstCtx)->ChanID;
        if (1 == pSegMan->CurrSeg.IsStreamEnd)
        {
            VCTRL_OutputLastFrame(ChanID);
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            break;
        }

        memcpy( &(pSegMan->Pack.StreamPack[0]), &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S) );
        memset( &(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S) );
        
        /* CRC mode go user decode */
        if (1 == s_pstVfmwChan[ChanID]->stSynExtraData.s8SpecMode)
        {
            REAL8DEC_Decode_User(pstCtx, &(pSegMan->Pack));
        }
        else
        {
            REAL8DEC_Decode(pstCtx, &(pSegMan->Pack));
        }
        
        if ( NULL == ((RV8_CTX_S*)pstCtx)->pRv8DecParam )
        {
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            REPORT_DECSYNTAX_ERR(ChanID);
        }
        break;
#endif
#ifdef VFMW_REAL9_SUPPORT
    case VFMW_REAL9:
        ChanID = ((RV9_CTX_S*)pstCtx)->ChanID;
        if (1 == pSegMan->CurrSeg.IsStreamEnd)
        {
            VCTRL_OutputLastFrame(ChanID);
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            break;
        }
        memcpy( &(pSegMan->Pack.StreamPack[0]), &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S) );
        memset( &(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S) );

        /* CRC mode go user decode */
        if (1 == s_pstVfmwChan[ChanID]->stSynExtraData.s8SpecMode)
        {
            REAL9DEC_Decode_User(pstCtx, &(pSegMan->Pack));
        }
        else
        {
            REAL9DEC_Decode(pstCtx, &(pSegMan->Pack));
        }

        if ( NULL == ((RV9_CTX_S*)pstCtx)->pRv9DecParam )
        {
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            REPORT_DECSYNTAX_ERR(ChanID);
        }
        break;
#endif
#ifdef VFMW_DIVX3_SUPPORT
    case VFMW_DIVX3:
        ChanID = ((DIVX3_CTX_S*)pstCtx)->ChanID;
        if (1 == pSegMan->CurrSeg.IsStreamEnd)
        {
            VCTRL_OutputLastFrame(ChanID);
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            break;
        }
        memcpy( &(pSegMan->Pack.StreamPack[0]), &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S) );
        memset( &(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S) );

        DIVX3DEC_Decode(pstCtx, &(pSegMan->Pack));
        if ( NULL == ((DIVX3_CTX_S*)pstCtx)->pDivx3DecParam )
        {
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            REPORT_DECSYNTAX_ERR(ChanID);
        }
        break;
#endif
#ifdef VFMW_VP8_SUPPORT
    case VFMW_VP8:
        ChanID = ((VP8_CTX_S*)pstCtx)->ChanID;
        if (1 == pSegMan->CurrSeg.IsStreamEnd)
        {
            VCTRL_OutputLastFrame(ChanID);
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            break;
        }
        memcpy( &(pSegMan->Pack.StreamPack[0]), &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S) );
        memset( &(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S) );

        VP8DEC_Decode(pstCtx, &(pSegMan->Pack));
        if ( NULL == ((VP8_CTX_S*)pstCtx)->pVp8DecParam )
        {
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            REPORT_DECSYNTAX_ERR(ChanID);
        }
        break;
#endif
#ifdef VFMW_VP6_SUPPORT
    case VFMW_VP6:
    case VFMW_VP6F:
    case VFMW_VP6A:
        ChanID = ((VP6_CTX_S*)pstCtx)->ChanID;
        if (1 == pSegMan->CurrSeg.IsStreamEnd)
        {
            VCTRL_OutputLastFrame(ChanID);
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            break;
        }
        memcpy( &(pSegMan->Pack.StreamPack[0]), &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S) );
        memset( &(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S) );
        VP6DEC_Decode(pstCtx, &(pSegMan->Pack));
        if ( NULL == ((VP6_CTX_S*)pstCtx)->pVp6DecParam )
        {
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            SM_ReleaseStreamSeg(ChanID, pSegMan->CurrSeg.StreamID);
            REPORT_DECSYNTAX_ERR(ChanID);
        }
        break;
#endif
    default:
        break;
    }

    return;
}

SINT32 SegMan(SINT32 ChanID, STREAM_SEG_PACKET_S *pSegMan)
{
    SINT32 ret = SYN_ERR;
	SINT32 s32MinBottomSegLen=0;

    if (NULL == pSegMan || NULL == pSegMan->CurrSeg.VirAddr)
    {
        dprint(PRN_ERROR,"pSegMan error!\n");
        return SYN_ERR;
    }

    if((1 == s_pstVfmwChan[ChanID]->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn) && \
       (1 == s_pstVfmwChan[ChanID]->stSynExtraData.s32WaitFsFlag) && \
       (1 == pSegMan->u32SCDWrapAround))
    {
        pSegMan->Pack = pSegMan->LastPack;
        pSegMan->u32SCDWrapAround = 0;
        ret = SYN_OK;
    }
    else
	{
        pSegMan->u32SCDWrapAround = 0;
		if ((1 == pSegMan->CurrSeg.IsLastSeg) && (0 == pSegMan->ConvolutionPacketNum)/*(NULL == pSegMan->Pack.StreamPack[0].VirAddr)*/)
		{
	        memcpy(&(pSegMan->Pack.StreamPack[0]),  &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S));
	   	    memset(&(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S));
			pSegMan->ConvolutionPacketNum = 0;
			ret = SYN_OK;
		}
		else if (0 == pSegMan->CurrSeg.IsLastSeg)
	    {
	        memcpy(&(pSegMan->Pack.StreamPack[0]),  &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S));
			memset(&(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S));
	        pSegMan->ConvolutionPacketNum++;
	    	if (pSegMan->ConvolutionPacketNum >= 2)
	    	{
	    		SM_ReleaseStreamSeg(ChanID, pSegMan->Pack.StreamPack[0].StreamID);
	    		SM_ReleaseStreamSeg(ChanID, pSegMan->Pack.StreamPack[1].StreamID);
	    	    memset(&(pSegMan->Pack.StreamPack[0]), 0, sizeof(STREAM_SEG_S));
	    	    memset(&(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S));
	    		dprint(PRN_ERROR,"More than two packet!!!ERROR!!!\n");
				REPORT_DECSYNTAX_ERR(ChanID);
				pSegMan->ConvolutionPacketNum = 0;
	       	}
			ret = SYN_ERR;
	    }
		else if ((1 == pSegMan->CurrSeg.IsLastSeg) && (1 == pSegMan->ConvolutionPacketNum)/*(NULL != pSegMan->Pack.StreamPack[0].VirAddr)*/)
        {
	        if(VFMW_AVS == s_pstVfmwChan[ChanID]->eVidStd)
		    {
	           s32MinBottomSegLen = MIN_BOTTOM_AVS_SEG_LEN;	    
		    }
			else
			{
			   s32MinBottomSegLen = MIN_BOTTOM_SEG_LEN;
			}
	        if (pSegMan->Pack.StreamPack[0].LenInByte < s32MinBottomSegLen)
	        {
			    dprint(PRN_DBG,"*****************copy packets tobe one*****************\n");
	    	    memcpy((pSegMan->CurrSeg.VirAddr - pSegMan->Pack.StreamPack[0].LenInByte), pSegMan->Pack.StreamPack[0].VirAddr, pSegMan->Pack.StreamPack[0].LenInByte);
	            pSegMan->Pack.StreamPack[0].VirAddr = pSegMan->CurrSeg.VirAddr - pSegMan->Pack.StreamPack[0].LenInByte;
				pSegMan->Pack.StreamPack[0].PhyAddr = pSegMan->CurrSeg.PhyAddr - pSegMan->Pack.StreamPack[0].LenInByte;
	            pSegMan->Pack.StreamPack[0].LenInByte = pSegMan->Pack.StreamPack[0].LenInByte + pSegMan->CurrSeg.LenInByte;
	            pSegMan->Pack.StreamPack[0].IsLastSeg = 1;
	    		SM_ReleaseStreamSeg(ChanID, pSegMan->Pack.StreamPack[0].StreamID);
				pSegMan->Pack.StreamPack[0].StreamID = pSegMan->CurrSeg.StreamID;
	    	    memset(&(pSegMan->Pack.StreamPack[1]), 0, sizeof(STREAM_SEG_S));
				ret = SYN_OK;
			}
			else
			{
			    dprint(PRN_DBG,"*****************two packet*****************\n");
	            memcpy(&(pSegMan->Pack.StreamPack[1]),  &(pSegMan->CurrSeg), sizeof(STREAM_SEG_S));
				ret = SYN_OK;
			}
	        pSegMan->ConvolutionPacketNum = 0;
            pSegMan->u32SCDWrapAround = 1;
            pSegMan->LastPack = pSegMan->Pack;
    	}
	}

	return ret;
}

VOID ReleasePacket(VID_STD_E VidStd, VOID *pCtx)
{
    STREAM_SEG_PACKET_S *pSegMan;

    switch (VidStd)
    {
    #ifdef VFMW_H264_SUPPORT
        case VFMW_H264:
            pSegMan = &((H264_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            return;
            break;
    #endif
    #ifdef VFMW_HEVC_SUPPORT
        case VFMW_HEVC:
            pSegMan = &((HEVC_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            return;
            break;
    #endif
    #ifdef VFMW_MVC_SUPPORT
        case VFMW_MVC:
            pSegMan = &((MVC_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            return;
            break;
    #endif
    #ifdef VFMW_MPEG4_SUPPORT
        case VFMW_MPEG4:
            pSegMan = &((MP4_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            if (1 == pSegMan->Pack.StreamPack[0].IsLastSeg )
            {
                SM_ReleaseStreamSeg(((MP4_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[0].StreamID);
            }
            else
            {
                SM_ReleaseStreamSeg(((MP4_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[0].StreamID);
                SM_ReleaseStreamSeg(((MP4_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[1].StreamID);
            }
            memset(&(pSegMan->Pack),0, sizeof(DEC_STREAM_PACKET_S));
            break;
    #endif
    #ifdef VFMW_MPEG2_SUPPORT
        case VFMW_MPEG2:
            pSegMan = &((MP2_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            break;
    #endif
    #ifdef VFMW_AVS_SUPPORT
        case VFMW_AVS:
    	    dprint(PRN_DBG,"release segbuf together!\n");
            pSegMan = &((AVS_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            break;
    #endif
    #ifdef VFMW_REAL8_SUPPORT
        case VFMW_REAL8:
            pSegMan = &((RV8_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            if (1 == pSegMan->Pack.StreamPack[0].IsLastSeg )
            {
                SM_ReleaseStreamSeg(((RV8_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[0].StreamID);
            }
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            break;
    #endif
    #ifdef VFMW_REAL9_SUPPORT
        case VFMW_REAL9:
            pSegMan = &((RV9_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            if (1 == pSegMan->Pack.StreamPack[0].IsLastSeg )
            {
                SM_ReleaseStreamSeg(((RV9_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[0].StreamID);
            }
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            break;
    #endif
    #ifdef VFMW_DIVX3_SUPPORT
        case VFMW_DIVX3:
            pSegMan = &((DIVX3_CTX_S*)pCtx)->pstExtraData->stSegPacket;
            if (1 == pSegMan->Pack.StreamPack[0].IsLastSeg )
            {
                SM_ReleaseStreamSeg(((DIVX3_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[0].StreamID);
            }
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            break;
    #endif
    #ifdef VFMW_VC1_SUPPORT
        case VFMW_VC1:
            break;
    #endif
    #ifdef VFMW_VP8_SUPPORT
        case VFMW_VP8:
            pSegMan = &((VP8_CTX_S*)pCtx)->pstExtraData->stSegPacket;
    		SM_ReleaseStreamSeg(((VP8_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[0].StreamID);
            if (1 != pSegMan->Pack.StreamPack[0].IsLastSeg )
            {
    			dprint(PRN_ERROR, "ERROR: VFMW_VP8 one packet stream, but IsLastSeg == 0\n");
            }
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            break;
    #endif
    #ifdef VFMW_VP6_SUPPORT
        case VFMW_VP6:
        case VFMW_VP6F:
        case VFMW_VP6A:
            pSegMan = &((VP6_CTX_S*)pCtx)->pstExtraData->stSegPacket;
    		SM_ReleaseStreamSeg(((VP6_CTX_S*)pCtx)->ChanID, pSegMan->Pack.StreamPack[0].StreamID);
            if (1 != pSegMan->Pack.StreamPack[0].IsLastSeg )
            {
    			dprint(PRN_ERROR, "ERROR: VFMW_VP6 one packet stream, but IsLastSeg == 0\n");
            }
            memset(&(pSegMan->Pack), 0, sizeof(DEC_STREAM_PACKET_S));
            break;
    #endif
        default:
            dprint(PRN_FATAL, "VidStd=%d Error!\n", VidStd);
            return;
            break;
    }

    return;
}

SINT32 IsNewpicSeg(SINT32 *pNewPicDetector, VID_STD_E VidStd, STREAM_SEG_S *pStreamSeg)
{
    SINT32 ret = SYN_ERR;
    UINT8  *pu8;
    SINT32 IsShortHead = 0;

    pu8 = pStreamSeg->VirAddr;

    /* 先判断 mpeg4 短头码流, 短头的码流起始码较为特殊 */
    if((VFMW_MPEG4 == VidStd) &&((pu8[2] >= 0x80) || (pu8[2] <= 0x83))&&
        (pStreamSeg->stMp4UpMsg.IsShStreamFlag == 1))
    {
        IsShortHead = 1;
    }

    if ((IsShortHead != 1) &&((pu8[0]!=0) || (pu8[1]!=0)||(pu8[2]!=1)))
    {
        /* 如果不是00 00 01开头(卷绕第二包可能会出现)，直接返回否 */
        dprint(PRN_DBG,"pu8[0] = %x,pu8[1] = %x, pu8[2] = %x\n",pu8[0],pu8[1],pu8[2]);
        ret = SYN_ERR;
    }
    else
    {
        /* 分协议讨论 */
        switch (VidStd)
        {
        #ifdef VFMW_H264_SUPPORT
            case VFMW_H264:
                if( H264_OK == H264_IsNewPicNal(pNewPicDetector, pu8) )
                {
                    ret = SYN_OK;
                }
                break;
        #endif
        #ifdef VFMW_HEVC_SUPPORT
            case VFMW_HEVC:
                if( HEVC_OK == HEVC_IsNewPicNal(pNewPicDetector, pu8) )
                {
                    ret = SYN_OK;
                }
                break;
        #endif
        #ifdef VFMW_MVC_SUPPORT
            case VFMW_MVC:
                if(MVC_OK == MVC_IsNewPicNal(pNewPicDetector, pu8) )
                {
                    ret = SYN_OK;
                }
                break;
        #endif
        #ifdef VFMW_MPEG2_SUPPORT
            case VFMW_MPEG2:
                if ( ((pu8[3] == 0x00) || (pu8[3] == 0xb3) || (pu8[3] == 0xb8) || (pu8[3] == 0xb7)) && (0 == *pNewPicDetector) )
                {
                    *pNewPicDetector = 1;
                    ret = SYN_OK;
                }
                if( pu8[3] == 0x00 )
                {
                    *pNewPicDetector = 0;
                }
                break;
        #endif
        #ifdef VFMW_MPEG4_SUPPORT
            case VFMW_MPEG4:
                // 增加最后一帧自定义头 0xfe
                if ((((pu8[3] == 0xb6) || (pu8[3] == 0xb5) || (pu8[3] == 0xb3) || (pu8[3] == 0xb0) || (pu8[3] == 0xfe) || (pu8[3] <= 0x2f))
                     && (0 == *pNewPicDetector)) || (IsShortHead == 1))
                {
                    *pNewPicDetector = 1;
                    ret = SYN_OK;
                }
                if ( pu8[3] == 0xb6)
                {
                    *pNewPicDetector = 0;
                }
                break;
        #endif
        #ifdef VFMW_AVS_SUPPORT
            case VFMW_AVS:
                if ( ((pu8[3] == 0xb0) || (pu8[3] == 0xb3) || (pu8[3] == 0xb6) || (pu8[3] == 0xb7)) && (0 == *pNewPicDetector) )
                {
                    *pNewPicDetector = 1;
                    ret = SYN_OK;
                }
                if( (pu8[3] == 0xb3) || (pu8[3] == 0xb6) )
                {
                    *pNewPicDetector = 0;
                }
                break;
        #endif
        #ifdef VFMW_VC1_SUPPORT
            case VFMW_VC1:
                if ( ((pu8[3] == VC1_SCEOS) || (pu8[3] == VC1_SCFLD) || (pu8[3] == VC1_SCFRM)|| (pu8[3] == VC1_SCENT)|| (pu8[3] == VC1_SCSEQ))
                    && (0 == *pNewPicDetector) )
                {
                    *pNewPicDetector = 1;
                    ret = SYN_OK;
                }
                if(pu8[3] == VC1_SCFRM)
                {
                    *pNewPicDetector = 0;
                }
                break;

        #endif
            default:
                break;
        }
    }

    return ret;
}


/*################################################################################################
=== USER DATA管理相关, 包括下面函数 ====

  1. 初始化USRDAT池:
  VOID  InitUsdPool();
  2. 获取一个USRDAT块
  VDEC_USRDAT_S *GetUsd();
  3. 释放一个USRDAT块
  VOID  FreeUsdByDec( VDEC_USRDAT_S *pUsrdat );
#################################################################################################*/

VDEC_USRDAT_POOL_S  *pstVdecUsdPool[MAX_CHAN_NUM] = {0};

SINT32 OpenUsdPool(SINT32 ChanID)
{
    SINT32 ret;

    if (pstVdecUsdPool[ChanID] == NULL)
    {
        pstVdecUsdPool[ChanID] = VFMW_OSAL_AllocVirMem(sizeof(VDEC_USRDAT_POOL_S));
    }

    ret = InitUsdPool(ChanID);

    return ret;
}

VOID CloseUsdPool(SINT32 ChanID)
{

    if (pstVdecUsdPool[ChanID] != NULL)
    {
        VFMW_OSAL_FreeVirMem(pstVdecUsdPool[ChanID]);
        pstVdecUsdPool[ChanID] = NULL;
    }

    return;
}

SINT32 OpenUsdPool_WithMem(SINT32 ChanID, SINT8* Viraddr)
{
    SINT32 ret;

    if (pstVdecUsdPool[ChanID] == NULL)
    {
        pstVdecUsdPool[ChanID] = (VDEC_USRDAT_POOL_S *)Viraddr;
    }

    ret = InitUsdPool(ChanID);

    return ret;
}

VOID CloseUsdPool_WithMem(SINT32 ChanID)
{

    if (pstVdecUsdPool[ChanID] != NULL)
    {
        //OSAL_FreeVirMem(pstVdecUsdPool[ChanID]);
        pstVdecUsdPool[ChanID] = NULL;
    }

    return;
}


/* 初始化USRDAT池 */
SINT32  InitUsdPool(SINT32 ChanID)
{
    SINT32 i;
    VDEC_USRDAT_POOL_S *pstUsdPool;

    if (pstVdecUsdPool[ChanID] != NULL)
    {
        pstUsdPool = pstVdecUsdPool[ChanID];
        pstUsdPool->s32AccessIdx = 0;
        for (i = 0; i < MAX_USRDAT_BLK_NUM; i++)
        {
            pstUsdPool->stUsrDat[i].from = USD_INVALID;
            pstUsdPool->stUsrDat[i].dnr_used_flag = 0;
        }

        return SYN_OK;
    }
    else
    {
        return SYN_ERR;
    }

    return SYN_ERR;
}

/* 获取一个USRDAT块，如果所有块都不空闲，则返回NULL */
VDEC_USRDAT_S *GetUsd(SINT32 ChanID)
{
    SINT32 i;
    VDEC_USRDAT_POOL_S  *pstUsdPool;
    VDEC_USRDAT_S  *pstUsrDat = NULL;

    if (pstVdecUsdPool[ChanID] != NULL)
    {
        pstUsdPool = pstVdecUsdPool[ChanID];
        for (i = 0; i < MAX_USRDAT_BLK_NUM; i++)
        {
            if ((pstUsdPool->stUsrDat[i].from == USD_INVALID) && (pstUsdPool->stUsrDat[i].dnr_used_flag == 0))
            {
                pstUsrDat = &pstUsdPool->stUsrDat[i];
                pstUsrDat->dnr_used_flag = 0;
                pstUsrDat->PTS = 0;
                pstUsrDat->data_size = 0;
                pstUsrDat->seq_cnt = pstUsrDat->seq_img_cnt = 0;
                pstUsrDat->IsRegistered = 0;
                pstUsrDat->itu_t_t35_country_code = 0;
                pstUsrDat->itu_t_t35_country_code_extension_byte = 0;
		        pstUsrDat->itu_t_t35_provider_code = 0;
                break;
            }
        }
    }

    return pstUsrDat;
}


/* 解码器释放一个USRDAT块 */
VOID FreeUsdByDec(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat )
{
    if (pUsrdat != NULL)
    {
        pUsrdat->from = USD_INVALID;
    }

    return;
}


/* 标记一个USRDAT块被DNR占用 */
VOID MarkUsdByDnr(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat )
{
    if (pUsrdat != NULL)
    {
        pUsrdat->dnr_used_flag = 1;
    }

    return;
}

/* 标记一个USRDAT块被DNR释放 */
VOID UnMarkUsdByDnr(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat )
{
    if (pUsrdat != NULL)
    {
        pUsrdat->dnr_used_flag = 0;
    }

    return;
}

/* 判断该帧是否已被放到VO QUEUE 队列里 */
SINT32 IsImageInVoQueue(IMAGE_VO_QUEUE *pstVoQue, IMAGE *p_image)
{
    SINT32 i;

    if ( NULL == p_image )
    {
        dprint(PRN_FATAL, "image point NULL\n");
        return SYN_ERR;
    }

    for ( i=pstVoQue->history; ; i++ )
    {
        i &= 63;
        if ( i == pstVoQue->tail )
        {
            break;
        }
        if (NULL != pstVoQue->image_ptr[i])
        {
            if ( pstVoQue->image_ptr[i]->image_id == p_image->image_id)
            {
                return SYN_OK;
            }
        }
    }

    return SYN_ERR;

}

/* 判断Vo队列是否为空 */
SINT32 IsVoQueueEmpty(IMAGE_VO_QUEUE *pstVoQue)
{
    if (NULL == pstVoQue)
    {
        dprint(PRN_FATAL, "%s pstVoQue NULL\n", __func__);
        return 0;
    }

    if (pstVoQue->head == pstVoQue->tail && pstVoQue->head == pstVoQue->history)
	{
		return 1;
	}

    return 0;
}

VOID SetAspectRatio(IMAGE *pImg, VDEC_DAR_E Code)
{
    switch(Code)
    {
        case DAR_UNKNOWN:
            pImg->u32AspectWidth = 0;
            pImg->u32AspectHeight = 1;
            break;
        case DAR_4_3:
            pImg->u32AspectWidth = 4;
            pImg->u32AspectHeight = 3;
            break;
        case DAR_16_9:
            pImg->u32AspectWidth = 16;
            pImg->u32AspectHeight = 9;
            break;
        case DAR_221_100:
            pImg->u32AspectWidth = 221;
            pImg->u32AspectHeight = 100;
            break;
        case DAR_235_100:
            pImg->u32AspectWidth = 235;
            pImg->u32AspectHeight = 100;
            break;
        case DAR_IMG_SIZE:
            pImg->u32AspectWidth = 0;
            pImg->u32AspectHeight = 2;
            break;
        default:
            pImg->u32AspectWidth = 0;
            pImg->u32AspectHeight = 1;
            dprint(PRN_ERROR,"WARNNING: aspect ration (%d) is not expected!\n",Code);
            break;
    }

    return;
}

UINT32 GetVoLastImageID(IMAGE_VO_QUEUE *pstVoQue)
{
    IMAGE_SIDE_INFO_S *pstSideInfo = &pstVoQue->SideInfo;

    if (pstSideInfo->LastImageIdPlus2 < 2)  // 因为返回的是id+2，所以不应该出现小于2的值
    {
        return -1;
    }

    return pstSideInfo->LastImageIdPlus2;
}


