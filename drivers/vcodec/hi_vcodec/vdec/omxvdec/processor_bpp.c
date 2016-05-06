
 
#include "processor.h"


/*================ EXTERN VALUE ================*/
extern HI_U32   g_DispNum;
extern HI_U32   g_NativeCancelNum;
extern HI_BOOL  g_SaveYuvEnable;
extern HI_CHAR  g_SavePath[];
extern HI_CHAR  g_SaveName[];


/*================== MACRO ===================*/
#define REALID(id)          (id%100+2)


/*================ DEFINITION ================*/
typedef enum{
    BPP_THREAD_INVALID = 0,
    BPP_THREAD_SLEEPING,
    BPP_THREAD_ONCALL,
    BPP_THREAD_RUNNING,
    BPP_THREAD_EXIT,
    BPP_THREAD_BUTT,
}BPP_THREAD_STATE_E;

typedef enum{
	BPP_INST_INVALID = 0,
	BPP_INST_IDLE,
	BPP_INST_WORK,
	BPP_INST_SUSPEND,
	BPP_INST_BUTT,
}BPP_INST_STATE_E;

typedef struct{
	HI_U32 image_id;
	HI_U32 luma_phy_addr;
    HI_U32 chroma_phy_addr;
    HI_U32 length;
    HI_U32 frame_width;
    HI_U32 frame_height;
    HI_U32 disp_width;
    HI_U32 disp_height;
    HI_U32 left_offset;
    HI_U32 right_offset;
    HI_U32 top_offset;
    HI_U32 bottom_offset;
	HI_U32 stride;
    HI_U32 format;
    HI_U32 ActCRC[2];
    HI_S64 timestamp; 	
}BPP_VIDEO_FRAME_S;

typedef struct {
	HI_U32 inst_id;
	BPP_INST_STATE_E inst_state;
	BPP_THREAD_STATE_E thread_state;
	wait_queue_head_t  task_wait;
	struct task_struct *pThread;
	OMXVDEC_CHAN_CTX *pMaster;
}BPP_CONTEXT_S;


/*================ INTERNAL VALUE ================*/
HI_U8 g_BPPInit = 0;
BPP_CONTEXT_S       g_BPPContext[MAX_CHANNEL_NUM];


/*============== INTERNAL FUNCTION ==============*/
static inline const HI_PCHAR processor_show_thread_state(BPP_THREAD_STATE_E state)
{
	switch (state)
    {
       case BPP_THREAD_INVALID:
            return "INVALID";
            break;

       case BPP_THREAD_SLEEPING:
            return "SLEEPING";
            break;

       case BPP_THREAD_ONCALL:
            return "ONCALL";
            break;

       case BPP_THREAD_RUNNING:
            return "RUNNING";
            break;

       case BPP_THREAD_EXIT:
            return "EXIT";
            break;
            
       default:
            return "UNKOWN";
            break;
	}
}

static inline const HI_PCHAR processor_show_last_frame_state(eLAST_FRAME_STATE state)
{
    switch (state)
    {
        case LAST_FRAME_INIT:
            return "INIT";
            break;

        case LAST_FRAME_DECODER_REPORT:
            return "DECODER REPORT";
            break;

        case LAST_FRAME_DECODER_FAILED:
            return "DECODER FAILED";
            break;

        case LAST_FRAME_PROCESSOR_GOT:
            return "PROCESSOR GOT";
            break;

        case LAST_FRAME_WAIT_SLOT:
            return "WAIT SLOT";
            break;

        default:
            return "INVALID";
            break;
    }
}

static inline const HI_PCHAR processor_show_progressive(HI_U32 flag)
{
    /* CodecType Relative */
    HI_PCHAR s;
    switch (flag)
    {
        case 0:
           s = "Progressive";
           break;

        case 1:
           s = "Interlaced";
           break;

        case 2:
           s = "Infered Progressive";
           break;

        case 3:
           s = "Infered Interlaced";
           break;

        default:
           s = "unknow";
           break;
    }

    return s;
}

static inline const HI_PCHAR processor_show_field_valid(HI_U32 flag)
{
    /* CodecType Relative */
    HI_PCHAR s;
    switch (flag)
    {
        case 0:
           s = "Both Field Invalid";
           break;

        case 1:
           s = "Top Field Valid";
           break;

        case 2:
           s = "Bottom Field Valid";
           break;

        case 3:
           s = "Both Field Valid";
           break;

        default:
           s = "unknow";
           break;
    }

    return s;
}

static inline const HI_PCHAR processor_show_field_first(HI_U32 flag)
{
    /* CodecType Relative */
    HI_PCHAR s;
    switch (flag)
    {
        case 0:
           s = "Bottom Field First";
           break;

        case 1:
           s = "Top Field First";
           break;

        default:
           s = "unknow";
           break;
    }

    return s;
}

static HI_U32 calculate_data_len(BPP_VIDEO_FRAME_S *pstFrame, HI_U32 color_format) 
{
    switch(color_format)
    {
        case OMX_PIX_FMT_NV12:
        case OMX_PIX_FMT_NV21:
        case OMX_PIX_FMT_YUV420Planar:
        case OMX_PIX_FMT_YUV420Tile:
        {
            return ((pstFrame->chroma_phy_addr - pstFrame->luma_phy_addr)* 3)/2;
        }

        default:
        {
            OmxPrint(OMX_ERR, "Unkown format return OMX_PIX_FMT_NV12 default!\n");
            return 0;
        }
    }
}

static HI_S32 processor_stop_thread(BPP_CONTEXT_S *pBppContext) 
{
    HI_S32 count;

    for (count=0; count<100; count++)
    {
        if (BPP_THREAD_RUNNING == pBppContext->thread_state)
        {
            msleep(10);
        }
        else
        {
            break;
        }
    }

    if (count >= 100)
    {
        OmxPrint(OMX_ERR, "processor stop failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 processor_report_size_change(OMXVDEC_CHAN_CTX *pchan)
{
	OMXVDEC_DEC_SIZE DecSize;

	DecSize.frame_width   = pchan->report_width;
	DecSize.frame_height  = pchan->report_height;
	DecSize.frame_stride  = pchan->report_stride;
	DecSize.frame_size    = pchan->ref_frame_size;
	DecSize.min_frame_num = pchan->ref_frame_num + g_DispNum;
	DecSize.max_frame_num = pchan->ref_frame_num + g_DispNum + g_NativeCancelNum;
	
	pchan->recfg_flag = 1;
	pchan->dfs_alloc_flag = DFS_WAIT_INSERT;

    OmxPrint(OMX_INFO, "Report new resolution: width %d, stride %d, height %d, frame_size = %d, need_num = %d, ref_num = %d\n",
             DecSize.frame_width, DecSize.frame_stride, DecSize.frame_height, DecSize.frame_size, DecSize.max_frame_num, DecSize.min_frame_num);
    
    /* Report to allocate frame buffer outside */
	message_queue(pchan->msg_queue, VDEC_EVT_REPORT_DEC_SIZE_CHG, VDEC_S_SUCCESS, (HI_VOID *)&DecSize);

	return HI_SUCCESS;
}

static HI_S32 processor_ctrl_thread_wake_up(OMXVDEC_CHAN_CTX *pchan)
{	
    if(HI_NULL == pchan)
    {
        OmxPrint(OMX_ERR, "%s, pchan = NULL\n", __func__);
        return HI_FAILURE;
    }

    if(pchan->processor_id < 0 || pchan->processor_id >= MAX_CHANNEL_NUM)
    {
        OmxPrint(OMX_ERR, "%s, pchan->processor_id = %d\n", __func__, pchan->processor_id);
        return HI_FAILURE;
    }

    if (BPP_THREAD_SLEEPING == g_BPPContext[pchan->processor_id].thread_state)
    {
		g_BPPContext[pchan->processor_id].thread_state = BPP_THREAD_ONCALL;
        wake_up(&g_BPPContext[pchan->processor_id].task_wait);
    }

    return HI_SUCCESS;
}

static HI_S32 processor_is_buffer_usable(OMXVDEC_CHAN_CTX *pchan, HI_U32 phy_addr)
{
    unsigned long  flags;
    HI_S32         is_find = 0;
    OMXVDEC_BUF_S *pbuf    = HI_NULL;

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s pchan = NULL.\n", __func__);
    	return HI_FAILURE;
    }

    spin_lock_irqsave(&pchan->yuv_lock, flags);
    if (list_empty(&pchan->yuv_queue))
    {
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
        return 0;
    }

    list_for_each_entry(pbuf, &pchan->yuv_queue, list)
    {
        if (phy_addr == pbuf->phy_addr)
        {
            if (BUF_STATE_QUEUED == pbuf->status)
            {
                is_find = 1;
                break;
            }
        }
    }
    spin_unlock_irqrestore(&pchan->yuv_lock, flags);

    return is_find;
}

static HI_S32 processor_set_buffer_wait_report(OMXVDEC_CHAN_CTX *pchan, HI_U32 phy_addr)
{
    unsigned long  flags;
    HI_S32         is_find = 0;
    OMXVDEC_BUF_S *pbuf    = HI_NULL;

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s pchan = NULL.\n", __func__);
    	return HI_FAILURE;
    }

    spin_lock_irqsave(&pchan->yuv_lock, flags);
    if (list_empty(&pchan->yuv_queue))
    {
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
        return 0;
    }

    list_for_each_entry(pbuf, &pchan->yuv_queue, list)
    {
        if (phy_addr == pbuf->phy_addr)
        {
            if (BUF_STATE_QUEUED != pbuf->status)
            {
                OmxPrint(OMX_ERR, "%s: buffer(0x%08x) flags(%d) confused!\n",__func__, phy_addr, pbuf->status);
            }
            
            is_find = 1;
            pbuf->status = BUF_STATE_WAIT_REPORT;
		    pchan->yuv_use_cnt++;
            break;
        }
    }
    spin_unlock_irqrestore(&pchan->yuv_lock, flags);

    return is_find;
}

static HI_S32 processor_get_frame(OMXVDEC_CHAN_CTX *pchan, BPP_VIDEO_FRAME_S *pframe)
{
    HI_S32 ret = HI_FAILURE;
    unsigned long flags;
    OMXVDEC_BUF_S *pbuf = HI_NULL;
	
    spin_lock_irqsave(&pchan->yuv_lock, flags);
    if (list_empty(&pchan->yuv_queue))
    {
        OmxPrint(OMX_VPSS, "%s List is empty!\n", __func__);
        goto empty;
    }

    list_for_each_entry(pbuf, &pchan->yuv_queue, list)
    {
        if(BUF_STATE_QUEUED == pbuf->status)
        {
            pbuf->status          = BUF_STATE_USING;
            pframe->luma_phy_addr = pbuf->phy_addr + pbuf->offset;
            pframe->length        = pbuf->buf_len;

    		pchan->yuv_use_cnt++;
            ret = HI_SUCCESS;
    		
            channel_sync_frame_buffer(pchan, pbuf->phy_addr, EXTBUF_TAKEN);
            
            OmxPrint(OMX_OUTBUF, "got frame: phy addr = 0x%08x\n", pframe->luma_phy_addr);
            break;
        }
    }

empty:
    spin_unlock_irqrestore(&pchan->yuv_lock, flags);
    return ret;

}

static HI_S32 processor_release_frame(OMXVDEC_CHAN_CTX *pchan, BPP_VIDEO_FRAME_S *pframe)
{
    unsigned long flags;
    HI_S32 is_find      = 0;
    HI_S32 is_del       = 0;
    HI_U32 phyaddr      = 0;
    OMXVDEC_BUF_S *pbuf = HI_NULL;
    OMXVDEC_BUF_S *ptmp = HI_NULL;
    OMXVDEC_BUF_DESC user_buf;

    memset(&user_buf, 0, sizeof(OMXVDEC_BUF_DESC));

    if (HI_NULL == pchan || HI_NULL == pframe)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

    phyaddr = pframe->luma_phy_addr;

    /* for we del list during, so use safe means */
    spin_lock_irqsave(&pchan->yuv_lock, flags);
    if (list_empty(&pchan->yuv_queue))
    {
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
        OmxPrint(OMX_ERR, "%s: list is empty\n", __func__);
        return 0;
    }

    list_for_each_entry_safe(pbuf, ptmp, &pchan->yuv_queue, list)
    {
        if (phyaddr == (pbuf->phy_addr + pbuf->offset))
        {
            if (pbuf->status != BUF_STATE_USING)
            {
                OmxPrint(OMX_ERR, "%s: buffer(0x%08x) flags(%d) confused!\n",__func__, phyaddr, pbuf->status);
            }

            if (pchan->output_flush_pending || pchan->pause_pending)
            {
                list_del(&pbuf->list);
                is_del = 1;
                pbuf->status = BUF_STATE_IDLE;
                channel_sync_frame_buffer(pchan, pbuf->phy_addr, EXTBUF_NOT_READY);
            }
            else
            {
                pbuf->status = BUF_STATE_QUEUED;
                channel_sync_frame_buffer(pchan, pbuf->phy_addr, EXTBUF_READY);
            }

            is_find = 1;
            pchan->yuv_use_cnt = (pchan->yuv_use_cnt > 0) ? (pchan->yuv_use_cnt-1) : 0;
            break;
        }
    }
    spin_unlock_irqrestore(&pchan->yuv_lock, flags);

    if (!is_find)
    {
        OmxPrint(OMX_ERR, "%s: buffer(0x%08x) not in queue!\n",__func__,  phyaddr);
        return HI_FAILURE;
    }

    if (1 == is_del)
    {
        user_buf.dir = PORT_DIR_OUTPUT;
        user_buf.bufferaddr  = pbuf->user_vaddr;
        user_buf.buffer_len  = pbuf->buf_len;
        user_buf.client_data = pbuf->client_data;
        user_buf.data_len = 0;
        user_buf.timestamp = 0;

        message_queue(pchan->msg_queue, VDEC_MSG_RESP_OUTPUT_DONE, VDEC_S_SUCCESS, (HI_VOID *)&user_buf);

        if (0 == pchan->yuv_use_cnt)
        {
            if (pchan->output_flush_pending)
            {
                message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_OUTPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
                pchan->output_flush_pending = 0;
            }

            if (pchan->pause_pending)
            {
                message_queue(pchan->msg_queue, VDEC_MSG_RESP_PAUSE_DONE, VDEC_S_SUCCESS, HI_NULL);
                pchan->pause_pending = 0;
            }
        }

        OmxPrint(OMX_OUTBUF, "bpp release frame: phy addr = 0x%08x (delete)\n", phyaddr);
    }
    else
    {
        OmxPrint(OMX_OUTBUF, "bpp release frame: phy addr = 0x%08x (requeue)\n", phyaddr);
    }

    return HI_SUCCESS;
}

static HI_S32 processor_report_frame(OMXVDEC_CHAN_CTX *pchan, BPP_VIDEO_FRAME_S *pstFrame)
{
    unsigned long flags;
    HI_U32 phyaddr      = 0;
    HI_S32 is_find      = 0;
    OMXVDEC_BUF_S *pbuf = HI_NULL;
    OMXVDEC_BUF_S *ptmp = HI_NULL;
    OMXVDEC_BUF_DESC user_buf;

    phyaddr = pstFrame->luma_phy_addr;  
    if ((HI_NULL == pchan) || (0 == phyaddr))
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

    /* for we del list during, so use safe means */
    spin_lock_irqsave(&pchan->yuv_lock, flags);
    if (list_empty(&pchan->yuv_queue))
    {
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
        OmxPrint(OMX_ERR, "%s: list is empty\n", __func__);
        return HI_FAILURE;
    }

    list_for_each_entry_safe(pbuf, ptmp, &pchan->yuv_queue, list)
    {
        if (phyaddr == (pbuf->phy_addr + pbuf->offset))
        {
            if (pbuf->status != BUF_STATE_USING && pbuf->status != BUF_STATE_WAIT_REPORT)
            {
                OmxPrint(OMX_ERR, "%s: buffer(0x%08x) flags(%d) confused!\n", __func__, phyaddr, pbuf->status);
            }
            
            is_find = 1;
            pbuf->status = BUF_STATE_IDLE;
            list_del(&pbuf->list);
            
            channel_sync_frame_buffer(pchan, pbuf->phy_addr, EXTBUF_NOT_READY);

            pchan->yuv_use_cnt = (pchan->yuv_use_cnt > 0) ? (pchan->yuv_use_cnt-1) : 0;
            break;
        }
    }

    if (!is_find)
    {
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
        OmxPrint(OMX_ERR, "%s: buffer(0x%08x) not in queue!\n", __func__,  phyaddr);
        return HI_FAILURE;
    }

    /* let out msg to inform application */
    memset(&user_buf, 0, sizeof(OMXVDEC_BUF_DESC));
	
    user_buf.dir                     = PORT_DIR_OUTPUT;
    user_buf.buffer_type             = pbuf->buf_type;
    user_buf.bufferaddr              = pbuf->user_vaddr;
    user_buf.buffer_len              = pbuf->buf_len;
    user_buf.client_data             = pbuf->client_data;
    user_buf.flags                   = VDEC_BUFFERFLAG_ENDOFFRAME;
    user_buf.phyaddr                 = pstFrame->luma_phy_addr;
    user_buf.out_frame.phyaddr_Y     = pstFrame->luma_phy_addr; 
    user_buf.out_frame.phyaddr_C     = pstFrame->chroma_phy_addr; 
    user_buf.out_frame.stride        = pstFrame->stride; 
    user_buf.out_frame.frame_width   = pstFrame->frame_width;
    user_buf.out_frame.frame_height  = pstFrame->frame_height;
    user_buf.out_frame.disp_width    = pstFrame->disp_width;
    user_buf.out_frame.disp_height   = pstFrame->disp_height;
    user_buf.out_frame.left_offset   = pstFrame->left_offset;
    user_buf.out_frame.right_offset  = pstFrame->right_offset;
    user_buf.out_frame.top_offset    = pstFrame->top_offset;
    user_buf.out_frame.bottom_offset = pstFrame->bottom_offset;
    user_buf.out_frame.format        = pstFrame->format;
    user_buf.out_frame.save_yuv      = g_SaveYuvEnable;
    
    memcpy(user_buf.out_frame.act_crc, pstFrame->ActCRC, sizeof(user_buf.out_frame.act_crc));

    if (HI_TRUE == user_buf.out_frame.save_yuv)
    {
        snprintf(user_buf.out_frame.save_path, sizeof(user_buf.out_frame.save_path),
                "%s/%s.yuv", g_SavePath, g_SaveName);
                user_buf.out_frame.save_path[PATH_LEN-1] = '\0';
    }

    if (LAST_FRAME_PROCESSOR_GOT == pchan->last_frame_state)
    {
        /* last frame */
        user_buf.flags                |= VDEC_BUFFERFLAG_EOS;
        user_buf.data_len              = 0;
        user_buf.timestamp             = 0;
        pbuf->ext_info.PP_EXT.image_id = 0;
        pchan->eof_send_flag++;

        OmxPrint(OMX_INFO, "report last frame, phyaddr = %x, timestamp = %lld\n", phyaddr, user_buf.timestamp);
    }
    else if (pchan->output_flush_pending)
    {
        user_buf.data_len              = 0;
        user_buf.timestamp             = 0;
        pbuf->ext_info.PP_EXT.image_id = 0;
        OmxPrint(OMX_OUTBUF, "output flush pending, unrelease buffer num: %d\n", pchan->yuv_use_cnt);
    }
    else
    {
        user_buf.timestamp             = pstFrame->timestamp; 
        user_buf.data_len              = MIN(pstFrame->length, user_buf.buffer_len);
        pbuf->ext_info.PP_EXT.image_id = pstFrame->image_id + 2;
        pchan->out_frame_num++;
    }

    pbuf->act_len = user_buf.data_len;
    OmxPrint(OMX_PTS, "Put Time Stamp: %lld\n", user_buf.timestamp);
    
    message_queue(pchan->msg_queue, VDEC_MSG_RESP_OUTPUT_DONE, VDEC_S_SUCCESS, (HI_VOID *)&user_buf);

    if (0 == pchan->yuv_use_cnt)
    {
        if (pchan->output_flush_pending)
        {
           message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_OUTPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
           pchan->output_flush_pending = 0;
        }

        if (pchan->pause_pending)
        {
           message_queue(pchan->msg_queue, VDEC_MSG_RESP_PAUSE_DONE, VDEC_S_SUCCESS, HI_NULL);
           pchan->pause_pending = 0;
        }
    }
	
    spin_unlock_irqrestore(&pchan->yuv_lock, flags);
    OmxPrint(OMX_OUTBUF, "bpp report frame: phy addr 0x%08x, data_len %d\n", phyaddr, user_buf.data_len);

    return HI_SUCCESS;
}

static HI_S32 processor_report_last_frame(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;
    BPP_VIDEO_FRAME_S stLastFrame;

    memset(&stLastFrame, 0, sizeof(stLastFrame));

    ret = processor_get_frame(pchan, &stLastFrame);
    if (HI_SUCCESS == ret)
    {
        pchan->last_frame_state = LAST_FRAME_PROCESSOR_GOT;
        ret = processor_report_frame(pchan, &stLastFrame);
        if (HI_SUCCESS == ret)
        {
            OmxPrint(OMX_INFO, "Processor report eos frame.\n");
        }
        else
        {
            OmxPrint(OMX_ERR, "Processor report eos frame failed!\n");
            processor_release_frame(pchan, &stLastFrame);
        }
        pchan->last_frame_state = LAST_FRAME_INIT;
    }
    else
    {
        OmxPrint(OMX_INFO, "No free frame slot for eos frame, wait for a while.\n");
        pchan->last_frame_state = LAST_FRAME_WAIT_SLOT;
    }

    return ret;
}

static HI_S32 processor_get_image(OMXVDEC_CHAN_CTX *pchan, BPP_VIDEO_FRAME_S *pstFrame)
{
    HI_S32 ret = HI_FAILURE;
	IMAGE stImage;
		
    if(HI_NULL == pchan || HI_NULL == pstFrame)
    {
        OmxPrint(OMX_ERR, "%s, pchan/pstFrame = NULL\n", __func__);
        return HI_FAILURE;
    }

    if(pchan->reset_pending)
    {
        OmxPrint(OMX_VPSS, "%s channel reset pending\n", __func__);
        return HI_FAILURE;
    }

    ret = pchan->image_ops.read_image(pchan->decoder_id, &stImage);
    if(ret != HI_SUCCESS)
    {
        if ((LAST_FRAME_DECODER_REPORT == pchan->last_frame_state && pchan->last_frame_processor_got == pchan->last_frame_image_id)
          || LAST_FRAME_DECODER_FAILED == pchan->last_frame_state)
        {
            OmxPrint(OMX_INFO, "Processor has handled all frames, prepare to report eos frame.\n");
            processor_report_last_frame(pchan);
        }
        OmxPrint(OMX_VPSS, "bpp read image failed\n");
        return HI_FAILURE;
    }

    memset(pstFrame, 0, sizeof(BPP_VIDEO_FRAME_S));

    pstFrame->luma_phy_addr   = stImage.top_luma_phy_addr;
    pstFrame->chroma_phy_addr = stImage.top_chrom_phy_addr;	
    pstFrame->frame_width  	  = stImage.image_width;
    pstFrame->frame_height 	  = stImage.image_height;
    pstFrame->disp_width  	  = stImage.disp_width;
    pstFrame->disp_height 	  = stImage.disp_height;
    pstFrame->left_offset 	  = stImage.left_offset;
    pstFrame->right_offset 	  = stImage.right_offset;
    pstFrame->top_offset 	  = stImage.top_offset;
    pstFrame->bottom_offset   = stImage.bottom_offset;
    pstFrame->stride 	      = stImage.image_stride/16;
    pstFrame->format          = stImage.format;
    pstFrame->timestamp    	  = (HI_S64)stImage.PTS;
    pstFrame->length          = calculate_data_len(pstFrame, pchan->color_format); 
    pstFrame->image_id        = stImage.image_id;
    memcpy(pstFrame->ActCRC, stImage.ActualCRC, sizeof(pstFrame->ActCRC));

    pchan->pic_format         = stImage.format;

    if (1 == stImage.last_frame)
    {
        pchan->last_frame_image_id = REALID(stImage.image_id);
        OmxPrint(OMX_INFO, "Processor get last frame, image id = %d.\n", pchan->last_frame_image_id);
    }

    pchan->last_frame_processor_got = REALID(stImage.image_id);
	
    return HI_SUCCESS;
}

static HI_S32 processor_release_image(OMXVDEC_CHAN_CTX *pchan, BPP_VIDEO_FRAME_S *pstFrame)
{
    HI_S32 ret = HI_FAILURE;
    IMAGE stImage;
	    
    if(HI_NULL == pchan || HI_NULL == pstFrame )
    {
        OmxPrint(OMX_ERR, "%s, pchan/pstFrame = NULL\n", __func__);
        return HI_FAILURE;
    }

	memset(&stImage, 0, sizeof(stImage));
    stImage.luma_phy_addr        = pstFrame->luma_phy_addr;
    stImage.top_luma_phy_addr    = pstFrame->luma_phy_addr;
    stImage.image_id             = pstFrame->image_id;
    stImage.image_id_1           = -1;

    ret = pchan->image_ops.release_image(pchan->decoder_id, &stImage);
    if(ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 processor_ctrl_release_image(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_S *pBuf)
{
    HI_S32 ret = HI_FAILURE;
    BPP_VIDEO_FRAME_S stFrame;
	
    if(HI_NULL == pBuf)
    {
        OmxPrint(OMX_ERR, "%s, pBuf = NULL\n", __func__);
        return HI_FAILURE;
    }

	memset(&stFrame, 0x00, sizeof(stFrame));
	stFrame.luma_phy_addr = pBuf->phy_addr;
	stFrame.image_id      = pBuf->ext_info.PP_EXT.image_id-2;
		
    ret = processor_release_image(pchan, &stFrame);
    if(ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
	
    return HI_SUCCESS;
}

static HI_S32 processor_do_one_work(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_SUCCESS;
    BPP_VIDEO_FRAME_S stFrame;
		
	/* get frame */
	ret = processor_get_image(pchan, &stFrame);
	if(ret != HI_SUCCESS)
	{
        if (DFS_WAIT_CLEAR == pchan->dfs_alloc_flag)
        {
            processor_report_size_change(pchan);
        }
		OmxPrint(OMX_VPSS, "%s get image failed!\n", __func__);
		return HI_FAILURE;
	}

	/* report frame */
	ret = processor_report_frame(pchan, &stFrame);
	if(ret != HI_SUCCESS)
	{
		OmxPrint(OMX_ERR, "%s report frame failed!\n", __func__);
		processor_release_image(pchan, &stFrame);
		return HI_FAILURE;
	}
	
    return ret;
}

static HI_S32 processor_thread(HI_VOID* param)
{
    HI_U32 i   = 0;
    HI_S32 ret = HI_SUCCESS;
    OMXVDEC_CHAN_CTX *pchan       = HI_NULL;
    BPP_CONTEXT_S    *pBppContext = (BPP_CONTEXT_S *)param;

    if(HI_NULL == pBppContext)	
    {
        OmxPrint(OMX_ERR, "%s pBppContext = NULL\n", __func__);
        return HI_FAILURE;
    }
    
    pchan = pBppContext->pMaster;
    if(HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "FATAL: %s g_BPPContext[%d].pMaster = NULL\n", __func__, i);
        return HI_FAILURE;
    }

    while(!kthread_should_stop())
    {
        pBppContext->thread_state = BPP_THREAD_SLEEPING;
        ret = wait_event_timeout(pBppContext->task_wait, (BPP_THREAD_ONCALL == pBppContext->thread_state), msecs_to_jiffies(200));
        pBppContext->thread_state = BPP_THREAD_RUNNING;

        if (BPP_INST_WORK == pBppContext->inst_state && CHAN_STATE_WORK == pchan->channel_state)
        {
            do {
                ret = processor_do_one_work(pchan);
                if (ret != HI_SUCCESS)
                {
                    OmxPrint(OMX_VPSS, "chan %d processor_do_one_work failed\n", pchan->processor_id);
                    break;
                } 
            }while(1);
        }
    }

    pBppContext->thread_state = BPP_THREAD_INVALID;

    return ret;
}

/*=============== EXPORT FUNCTION ==============*/
HI_S32 processor_init(HI_VOID)
{
	memset(g_BPPContext, 0, sizeof(g_BPPContext));
    g_BPPInit = 1;
    
	return HI_SUCCESS;
}

HI_S32 processor_exit(HI_VOID)
{
	HI_U32 i;
	HI_S32 ret = HI_FAILURE;
		
	for(i=0; i<MAX_CHANNEL_NUM; i++)
	{
		if(g_BPPContext[i].inst_state != BPP_INST_INVALID)
		{
			ret = processor_release_inst(g_BPPContext[i].pMaster);
			if (ret != HI_SUCCESS)
			{
			    OmxPrint(OMX_FATAL, "%s release inst %d failed!\n", __func__, i);
			}
		}
	}
	g_BPPInit = 0;
    
	return HI_SUCCESS;
}

HI_S32 processor_suspend(HI_VOID)
{
    HI_S32 i;
    HI_S32 ret;
    BPP_CONTEXT_S *pBppContext = HI_NULL;
	
    if (g_BPPInit != 1)
    {
        return HI_SUCCESS;
    }

    for (i=0; i<MAX_CHANNEL_NUM; i++)
    {
        pBppContext = &g_BPPContext[i];
        if (pBppContext->inst_state != BPP_INST_WORK)
        {
            continue;
        }
        pBppContext->inst_state = BPP_INST_SUSPEND;
        ret = processor_stop_thread(pBppContext);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_ERR, "%s stop inst %d thread failed!\n", __func__, i);
        }
    }

    return HI_SUCCESS;
}

HI_S32 processor_resume(HI_VOID)
{
    HI_S32 i;
    BPP_CONTEXT_S *pBppContext = HI_NULL;
    
    if (g_BPPInit != 1)
    {
        return HI_SUCCESS;
    }
    
    for (i=0; i<MAX_CHANNEL_NUM; i++)
    {
        pBppContext = &g_BPPContext[i];
        if (pBppContext->inst_state != BPP_INST_SUSPEND)
        {
            continue;
        }
        pBppContext->inst_state = BPP_INST_WORK;
    }

    return HI_SUCCESS;
}

HI_S32 processor_create_inst(OMXVDEC_CHAN_CTX *pchan, HI_U32 color_format)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 i = 0;

    pchan->color_format = color_format;
    pchan->processor_id  = -1;

    for(i=0; i<MAX_CHANNEL_NUM; i++)
    {
        if(g_BPPContext[i].inst_state == BPP_INST_INVALID)
        {
            memset(&g_BPPContext[i], 0, sizeof(BPP_CONTEXT_S));

            g_BPPContext[i].inst_id     = i;
            g_BPPContext[i].inst_state = BPP_INST_IDLE;
            g_BPPContext[i].pMaster    = pchan;

            init_waitqueue_head(&g_BPPContext[i].task_wait);
            g_BPPContext[i].pThread = kthread_create(processor_thread, (HI_VOID *)&g_BPPContext[i], "bpp processor thread");
            if(HI_NULL == g_BPPContext[i].pThread)
            {
                memset(&g_BPPContext[i], 0, sizeof(BPP_CONTEXT_S));
                OmxPrint(OMX_FATAL, "Create processor_thread %d failed!\n", i);
                return HI_FAILURE;
            }
            else if (IS_ERR(g_BPPContext[i].pThread))
            {
                OmxPrint(OMX_FATAL, "%s create task failed, error no = %ld!\n", __func__, PTR_ERR(g_BPPContext[i].pThread));
                g_BPPContext[i].pThread = HI_NULL;
                return HI_FAILURE;
            }
            wake_up_process(g_BPPContext[i].pThread);

            pchan->processor_id = g_BPPContext[i].inst_id;

            ret = HI_SUCCESS;
            break;
        }
    }

    if(i >= MAX_CHANNEL_NUM)
    {
        OmxPrint(OMX_ERR, "%s no free context slot!\n", __func__);	
    }

    return ret;
}

HI_S32 processor_release_inst(OMXVDEC_CHAN_CTX *pchan)
{
	BPP_CONTEXT_S *pBppContext = HI_NULL;
	
	if(HI_NULL == pchan)	
	{
		OmxPrint(OMX_ERR, "%s pchan = NULL\n", __func__);
		return HI_FAILURE;
	}
	
    if(pchan->processor_id < 0 || pchan->processor_id >= MAX_CHANNEL_NUM)
    {
        OmxPrint(OMX_ERR, "%s, pchan->processor_id = %d\n", __func__, pchan->processor_id);
        return HI_FAILURE;
    }
	
	pBppContext = &g_BPPContext[pchan->processor_id];
	pBppContext->inst_state = BPP_INST_INVALID;
	pBppContext->pMaster    = HI_NULL;
    
	if(pBppContext->pThread != HI_NULL)
    {
        if (pBppContext->thread_state != BPP_THREAD_EXIT)
        {
            kthread_stop(pBppContext->pThread);
        }
        pBppContext->pThread = HI_NULL;
    }
	
    return HI_SUCCESS;
}

HI_S32 processor_start_inst(OMXVDEC_CHAN_CTX *pchan)
{
    g_BPPContext[pchan->processor_id].inst_state = BPP_INST_WORK;

    return HI_SUCCESS;
}

HI_S32 processor_stop_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret;
    BPP_CONTEXT_S *pBppContext = HI_NULL;
	
    pBppContext = &g_BPPContext[pchan->processor_id];

    pBppContext->inst_state = BPP_INST_IDLE;
    
    ret = processor_stop_thread(pBppContext);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "processor_stop_thread failed!\n");
        return HI_FAILURE;
    }
        
    return HI_SUCCESS;
}

HI_S32 processor_reset_inst(OMXVDEC_CHAN_CTX *pchan)
{
    // fix me here for seek (not used now)	

    return HI_SUCCESS;
}

HI_S32 processor_ctrl_inst(OMXVDEC_CHAN_CTX *pchan, PROCESSOR_CMD_E eCmd, HI_VOID *pParam)
{
	HI_S32 ret = HI_FAILURE;
	
	switch(eCmd)
	{
		case PP_CMD_RELEASE_IMAGE:
	    {
			ret = processor_ctrl_release_image(pchan, (OMXVDEC_BUF_S *)pParam);
			break;	
		}

		case PP_CMD_THREAD_WAKE_UP:
	    { 
			ret = processor_ctrl_thread_wake_up(pchan);
			break;	
		}

		case PP_CMD_IS_BUF_USABLE:
	    { 
            if (HI_NULL == pParam)
            {
			    OmxPrint(OMX_ERR, "%s CmdID = %d, param = NULL.\n", __func__, eCmd);
    			return HI_FAILURE;	
            }
			ret = processor_is_buffer_usable(pchan, *(UADDR *)pParam);
			break;	
		}
        
		case PP_CMD_REPORT_BUF_OUT:
	    { 
            if (HI_NULL == pParam)
            {
			    OmxPrint(OMX_ERR, "%s CmdID = %d, param = NULL.\n", __func__, eCmd);
    			return HI_FAILURE;	
            }
			ret = processor_set_buffer_wait_report(pchan, *(UADDR *)pParam);
			break;	
		}

        case PP_CMD_REPORT_LAST_FRAME:
        {
            ret = processor_report_last_frame(pchan);
			break;	
        }
        
		default:
		{
			OmxPrint(OMX_ERR, "%s unkown command id %d\n", __func__, eCmd);
			return HI_FAILURE;	
		}	
	}

	return ret;
}

HI_VOID processor_proc_entry(OMXVDEC_CHAN_CTX *pchan, struct seq_file *p)
{
    HI_U32 source_format = (pchan->pic_format & 0x300)>>8;
    HI_U32 field_valid   = (pchan->pic_format & 0xC00)>>10;
    HI_U32 field_first   = (pchan->pic_format & 0x3000)>>12;
    
    PROC_PRINT(p, "%-20s :%d\n",   "Processor",       pchan->processor_id);
    PROC_PRINT(p, "%-20s :%s\n",   "ThreadState",     processor_show_thread_state(g_BPPContext[pchan->processor_id].thread_state));
    PROC_PRINT(p, "%-20s :%d\n",   "OutBufUse",       pchan->yuv_use_cnt);
    PROC_PRINT(p, "%-20s :%d\n",   "OutFrameNum",     pchan->out_frame_num);
    PROC_PRINT(p, "%-20s :%s\n",   "P/I",             processor_show_progressive(source_format));
    if (1 == source_format || 3 == source_format)
    {
    PROC_PRINT(p, "%-20s :%s\n",   "FieldValid",      processor_show_field_valid(field_valid));
    PROC_PRINT(p, "%-20s :%s\n",   "FieldFirst",      processor_show_field_first(field_first));
    }
    PROC_PRINT(p, "%-20s :%s\n",   "LastFrameState",  processor_show_last_frame_state(pchan->last_frame_state));
    PROC_PRINT(p, "\n");
}

