

#include "decoder.h"
#include "vfmw_ext.h"
#include "processor.h"


/*================ EXTERN VALUE ================*/
extern HI_BOOL  g_DynamicFsEnable;
extern HI_U32   g_DispNum;
extern HI_U32   g_SegSize;         // (M)
extern HI_BOOL  g_RawMoveEnable;   // 码流搬移使能标志，解决scd切割失败不释放码流的情况
extern OMXVDEC_ENTRY *g_pOmxVdec;
extern OMXVDEC_FUNC   g_OmxFunc;


/*================ STATIC VALUE ================*/
static VFMW_EXPORT_FUNC_S* pVfmwFunc = HI_NULL;
static HI_S32       gIsNormalInit = 0;
static HI_S32       gIsSecureInit = 0;
static MEM_BUFFER_S gNormalHalMem;
static MEM_BUFFER_S gSecureHalMem;
struct semaphore    gDecoderSem;


/*================== DATA TYPE =================*/
typedef enum {
	CFG_CAP_SD = 0,
	CFG_CAP_HD,
	CFG_CAP_UHD,
}eCFG_CAP;


/*============== INTERNAL FUNCTION =============*/
static inline HI_S32 decoder_translate_protocol(OMXVDEC_CODEC_TYPE protocol)
{
    HI_S32  eVidStd = VFMW_START_RESERVED;
    
    switch (protocol)
    {
        case OMXVDEC_H264:
           eVidStd = STD_H264;
           break;

        case OMXVDEC_AVS:
           eVidStd = STD_AVS;
           break;

        case OMXVDEC_MPEG1:
           eVidStd = STD_MPEG2;
           break;

        case OMXVDEC_MPEG2:
           eVidStd = STD_MPEG2;
           break;

        case OMXVDEC_MPEG4:
           eVidStd = STD_MPEG4;
           break;

        case OMXVDEC_VC1:
           eVidStd = STD_VC1;
           break;

        case OMXVDEC_DIVX3:
           eVidStd = STD_DIVX3;
           break;

        case OMXVDEC_REAL8:
           eVidStd = STD_REAL8;
           break;

        case OMXVDEC_REAL9:
           eVidStd = STD_REAL9;
           break;

        case OMXVDEC_VP6:
           eVidStd = STD_VP6;
           break;

        case OMXVDEC_VP6F:
           eVidStd = STD_VP6F;
           break;
            
        case OMXVDEC_VP6A:
           eVidStd = STD_VP6A;
           break;

        case OMXVDEC_VP8:
           eVidStd = STD_VP8;
           break;

        case OMXVDEC_H263:
           eVidStd = STD_H263;
           break;

        case OMXVDEC_SORENSON:
           eVidStd = STD_SORENSON;
           break;

        case OMXVDEC_MVC:
           eVidStd = STD_MVC;
           break;
           
       case OMXVDEC_HEVC:
           eVidStd = STD_HEVC;
          break;

        default:
           OmxPrint(OMX_ERR, "%s unkown protocol %d.\n", __func__, protocol);
           break;
    }

    return eVidStd;
}


static HI_S32 decoder_event_handler(HI_S32 chan_id, HI_S32 event_type, HI_VOID *pargs, HI_U32 len)
{
    HI_S32  ret = HI_SUCCESS;
    HI_U32 *ptemp = HI_NULL;
    OMXVDEC_CHAN_CTX  *pchan = HI_NULL;

    pchan = channel_find_inst_by_decoder_id(g_pOmxVdec, chan_id);
    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, chan_id);
        return HI_FAILURE;
    }

    // OMXVDEC的消息处理分支，注意新增消息，需在安全侧的上报出口处同步放开，以免错误过滤  y00226912
    switch (event_type)
    {
        case EVNT_NEED_ARRANGE:
        {
            pchan->dfs_alloc_flag  = DFS_WAIT_ALLOC;
            VDEC_SYS_GetTimeStampMs(&pchan->dfs_delay_time);
            pchan->ref_frame_num   = ((HI_U32*)pargs)[0];
            pchan->ref_frame_size  = ((HI_U32*)pargs)[1];

            g_pOmxVdec->task.task_state = TASK_STATE_ONCALL;
            wake_up(&g_pOmxVdec->task.task_wait);
            break;
        }

        case EVNT_NEED_ARRANGE_L:
        {
            pchan->dfs_alloc_flag  = DFS_WAIT_ALLOC;
            VDEC_SYS_GetTimeStampMs(&pchan->dfs_delay_time);
            pchan->ref_frame_num   = ((HI_U32*)pargs)[0];
            pchan->ref_frame_size  = ((HI_U32*)pargs)[1];
            pchan->ref_pmv_size    = ((HI_U32*)pargs)[2];
            pchan->report_width    = ((HI_U32*)pargs)[3];
            pchan->report_height   = ((HI_U32*)pargs)[4];
            pchan->report_stride   = ((HI_U32*)pargs)[5];
            
            OmxPrint(OMX_INFO, "EVNT_NEED_ARRANGE_L: frame_num=%d, frame_size=%d, pmv_size=%d, width=%d, height=%d, stride=%d\n",
                     pchan->ref_frame_num, pchan->ref_frame_size, pchan->ref_pmv_size, pchan->report_width, pchan->report_height, pchan->report_stride);

            g_pOmxVdec->task.task_state = TASK_STATE_ONCALL;
            wake_up(&g_pOmxVdec->task.task_wait);

            channel_clear_buf_ext_info(pchan, PORT_DIR_OUTPUT);
            break;
        }

        case EVNT_NEW_IMAGE:
        {
            ret = processor_ctrl_inst(pchan, PP_CMD_THREAD_WAKE_UP, HI_NULL);
            if (ret != HI_SUCCESS)
            {
                OmxPrint(OMX_ERR, "%s call processor_ctrl_inst failed\n", __func__);
            }
            pchan->dec_frame_num++;
            break;
        }

        case EVNT_LAST_FRAME:
        {
            OmxPrint(OMX_INFO, "Get Last Frame Report!\n");
            if (HI_NULL == pargs)
            {
                OmxPrint(OMX_ERR, "Last frame report but pargs = NULL\n");
                ret = HI_FAILURE;
                break;
            }

            /* pargs[0]-> 0: success, 1: fail,  2+: report last frame image id */
            ptemp = pargs;
            pchan->last_frame_state = LAST_FRAME_DECODER_REPORT;

            if (REPORT_LAST_FRAME_FAIL == ptemp[0])
            {
                pchan->last_frame_state = LAST_FRAME_DECODER_FAILED;
                OmxPrint(OMX_ERR, "Last frame report failed!\n");
            }
            else if (REPORT_LAST_FRAME_SUCCESS == ptemp[0])
            {
                OmxPrint(OMX_INFO, "Last frame report success!\n");
            }
            else
            {
                pchan->last_frame_image_id = ptemp[0];
                OmxPrint(OMX_INFO, "Last frame report image id %d!\n", pchan->last_frame_image_id);
            }
            break;
        }

        default:
        {
            //OmxPrint(OMX_INFO, "%s unsupport Event Type: %d, arg=%p\n", __func__, event_type, pargs);
            break;
        }
    }

    return ret;
}

static HI_S32 decoder_buffer_handler(HI_S32 chan_id, HI_S32 type, HI_VOID *pargs)
{
    HI_S32  ret = HI_FAILURE;
    OMXVDEC_CHAN_CTX  *pchan = HI_NULL;

    pchan = channel_find_inst_by_decoder_id(g_pOmxVdec, chan_id);
    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, chan_id);
        return HI_FAILURE;
    }    

    switch (type)
    {
        case BC_CHK_BUF:
        {
            ret = processor_ctrl_inst(pchan, PP_CMD_IS_BUF_USABLE, pargs);
            break;
        }
            
        case BC_REPORT_BUF:
        {
            ret = processor_ctrl_inst(pchan, PP_CMD_REPORT_BUF_OUT, pargs);
            break;
        }

        default:
        {
            OmxPrint(OMX_ERR, "%s unsupport type %d\n", __func__, type);
            break;
        }
    }

    return ret;
}

static HI_S32 decoder_init_option(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_CHAN_CFG *pchan_cfg, VDEC_CHAN_CFG_S *pVfmwCfg, VDEC_CHAN_CAP_LEVEL_E *pFmwCap, VDEC_CHAN_OPTION_S *pOption)
{
    eCFG_CAP  ConfigCap = CFG_CAP_HD;

    if (HI_NULL == pchan || HI_NULL == pchan_cfg || HI_NULL == pVfmwCfg || HI_NULL == pFmwCap || HI_NULL == pOption)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }
    
    // record basic config
    pchan->is_tvp   = pchan_cfg->is_tvp;
    pchan->protocol = pchan_cfg->cfg_codec_type;
    
    // init vfmw chan config
    pVfmwCfg->s8IsOmxPath                = 1;
    pVfmwCfg->eVidStd                    = decoder_translate_protocol(pchan_cfg->cfg_codec_type);
    pVfmwCfg->s8SpecMode                 = pchan_cfg->spec_mode;
    pVfmwCfg->u8UVOrder                  = pchan_cfg->uv_order;
    pVfmwCfg->s8DecOrderOutput           = pchan_cfg->output_order;
    pVfmwCfg->s32DecMode                 = pchan_cfg->dec_mode;
    pVfmwCfg->s32ChanPriority            = pchan_cfg->priority;
    pVfmwCfg->s32ChanErrThr              = pchan_cfg->err_threshold;
    pVfmwCfg->s8LowdlyEnable             = (HI_TRUE == pchan_cfg->lowdly_enable)?   1: 0;
    pVfmwCfg->s8VcmpEn                   = (HI_TRUE == pchan_cfg->compress_enable)? 1: 0;;
    pVfmwCfg->s32MaxRawPacketNum         = (HI_TRUE == g_RawMoveEnable)? pchan_cfg->act_inbuf_num: -1;
    pVfmwCfg->s32MaxRawPacketSize        = (HI_TRUE == g_RawMoveEnable)? pchan_cfg->act_inbuf_size: -1;
    pVfmwCfg->StdExt.Vc1Ext.IsAdvProfile = pchan_cfg->cfg_codec_ext.vc1_ext.is_adv_profile;
    pVfmwCfg->StdExt.Vc1Ext.CodecVersion = pchan_cfg->cfg_codec_ext.vc1_ext.codec_version;
    pVfmwCfg->StdExt.Vp6Ext.bReversed    = pchan_cfg->cfg_codec_ext.vp6_ext.need_reverse;
    
    // init vfmw chan option
    pOption->eAdapterType          = ADAPTER_TYPE_OMXVDEC;
    pOption->Purpose               = PURPOSE_DECODE;
    pOption->s32SupportBFrame      = 1;
    pOption->s32ReRangeEn          = 1;
    pOption->s32DisplayFrameNum    = g_DispNum;

    if (pchan->out_width*pchan->out_height > HD_FRAME_WIDTH*HD_FRAME_HEIGHT)
    {
        ConfigCap = CFG_CAP_UHD;
        pOption->s32MaxWidth       = MAX(UHD_FRAME_WIDTH,  pchan->out_width);
        pOption->s32MaxHeight      = MAX(UHD_FRAME_HEIGHT, pchan->out_height);
        pOption->s32SCDBufSize     = 4*g_SegSize*1024*1024;
        pOption->s32MaxRefFrameNum = 4;
    }
    else
    {
        ConfigCap = CFG_CAP_HD;
        pOption->s32MaxWidth       = MAX(HD_FRAME_WIDTH,  pchan->out_width);
        pOption->s32MaxHeight      = MAX(HD_FRAME_HEIGHT, pchan->out_height);
        pOption->s32SCDBufSize     = g_SegSize*1024*1024;
        pOption->s32MaxRefFrameNum = 10;
    }

    if (STD_HEVC == pVfmwCfg->eVidStd)
    {
        switch (ConfigCap)
        {
            case CFG_CAP_SD:
    	        *pFmwCap = CAP_LEVEL_HEVC_720;
                break;
            case CFG_CAP_UHD:
    	        *pFmwCap = CAP_LEVEL_HEVC_UHD;
                break;
            case CFG_CAP_HD:
            default:
    	        *pFmwCap = CAP_LEVEL_HEVC_FHD;
                break;
        }
        
        pOption->u32SupportStd = 1<<2;
    }
    else if (STD_H264 == pVfmwCfg->eVidStd || STD_MVC == pVfmwCfg->eVidStd)
    {
        if (STD_MVC == pVfmwCfg->eVidStd)
        {
            *pFmwCap = CAP_LEVEL_MVC_FHD;
            pOption->u32SupportStd = 1<<1;
        }
        else
        {
            switch (ConfigCap)
            {
                case CFG_CAP_SD:
        	        *pFmwCap = CAP_LEVEL_H264_720;
                    break;
                case CFG_CAP_UHD:
        	        *pFmwCap = CAP_LEVEL_4096x2160;
                    break;
                case CFG_CAP_HD:
                default:
        	        *pFmwCap = CAP_LEVEL_H264_FHD;
                    break;
            }
            pOption->u32SupportStd = 1;
        }
    }
    else
    {
        switch (ConfigCap)
        {
            case CFG_CAP_SD:
    	        *pFmwCap = CAP_LEVEL_MPEG_720;
                break;
            case CFG_CAP_UHD:
    	        *pFmwCap = CAP_LEVEL_4096x2160;
                break;
            case CFG_CAP_HD:
            default:
    	        *pFmwCap = CAP_LEVEL_MPEG_FHD;
                break;
        }

        if (STD_VP8 == pVfmwCfg->eVidStd)
        {
            pOption->s32MaxRefFrameNum = 3;
        }
        else
        {
            pOption->s32MaxRefFrameNum = 2;
        }
        pOption->u32SupportStd = 0;
    }
    
    if (HI_TRUE == g_DynamicFsEnable)
    {
        pOption->u32DynamicFrameStoreAllocEn = 1;
        pOption->MemAllocMode                = MODE_PART_BY_SDK;
    }
    else
    {
        pOption->u32DynamicFrameStoreAllocEn = 0;
        pOption->MemAllocMode                = MODE_ALL_BY_SDK;
    }
    
    if (HI_TRUE == pchan->is_tvp)
    {
        pOption->u32IsSecMode = 1;
    }
    else
    {
        pOption->u32IsSecMode = 0;
    }

    pOption->u32OmxBypassMode = 1;

    return HI_SUCCESS;
}

static HI_S32 decoder_get_stream(HI_S32 chan_id, STREAM_DATA_S *stream_data)
{
	HI_S32 ret = HI_FAILURE;
	unsigned long flags;
	OMXVDEC_BUF_S *pbuf     = HI_NULL;
	OMXVDEC_CHAN_CTX *pchan = HI_NULL;

	pchan = channel_find_inst_by_channel_id(g_pOmxVdec, chan_id);
	if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, chan_id);
        return HI_FAILURE;
	}

	if (pchan->channel_state != CHAN_STATE_WORK)
    {
		return HI_FAILURE;
	}
    
	spin_lock_irqsave(&pchan->raw_lock, flags);
	if (list_empty(&pchan->raw_queue))
    {
		spin_unlock_irqrestore(&pchan->raw_lock, flags);
		return HI_FAILURE;
	}

	if (pchan->input_flush_pending)
    {
		spin_unlock_irqrestore(&pchan->raw_lock, flags);
        OmxPrint(OMX_INBUF, "Invalid: input_flush_pending\n");
		return HI_FAILURE;
	}

	list_for_each_entry(pbuf, &pchan->raw_queue, list)
    {
		if(BUF_STATE_USING == pbuf->status)
        {
			continue;
        }

        memset(stream_data, 0, sizeof(STREAM_DATA_S));

        pbuf->status                      = BUF_STATE_USING;
		stream_data->PhyAddr	          = pbuf->phy_addr + pbuf->offset;
		stream_data->VirAddr	          = pbuf->kern_vaddr + pbuf->offset;
		stream_data->Length	              = pbuf->act_len;
		stream_data->Pts	              = (UINT64)pbuf->time_stamp;
		stream_data->RawExt.Flags         = pbuf->flags;
		stream_data->RawExt.BufLen        = pbuf->buf_len;
		stream_data->RawExt.CfgWidth      = pchan->out_width;
		stream_data->RawExt.CfgHeight     = pchan->out_height;

        if (pchan->seek_pending)
        {
            stream_data->RawExt.IsSeekPending = 1;
            pchan->seek_pending = 0;
        }

        if (pbuf->flags & VDEC_BUFFERFLAG_ENDOFFRAME)
        {
            stream_data->is_not_last_packet_flag = 0;
        }
        else
        {
            stream_data->is_not_last_packet_flag = 1;
        }

        if (pbuf->buf_id == LAST_FRAME_BUF_ID)
        {
            OmxPrint(OMX_INFO, "Decoder get eos packet.\n");
            stream_data->is_stream_end_flag = 1;
        }

        pchan->raw_use_cnt++;
        pchan->get_packet_num++;

        OmxPrint(OMX_PTS, "Get Time Stamp: %lld\n", stream_data->Pts);

		ret = HI_SUCCESS;

        OmxPrint(OMX_INBUF, "Decoder get stream: PhyAddr = 0x%08x, VirAddr = %p, Len = %d\n",
                            stream_data->PhyAddr, stream_data->VirAddr, stream_data->Length);

		break;
	}

	spin_unlock_irqrestore(&pchan->raw_lock, flags);

	return ret;
}

static HI_S32 decoder_release_stream(HI_S32 chan_id, STREAM_DATA_S *stream_data)
{
    unsigned long flags;
    HI_S32        is_find = 0;
    OMXVDEC_BUF_S    *pbuf  = HI_NULL;
    OMXVDEC_BUF_S    *ptmp  = HI_NULL;
    OMXVDEC_CHAN_CTX *pchan = HI_NULL;

    OMXVDEC_BUF_DESC  user_buf;

    if (HI_NULL == stream_data)
    {
        OmxPrint(OMX_FATAL, "%s stream_data = NULL.\n", __func__);
        return HI_FAILURE;
    }

    pchan = channel_find_inst_by_channel_id(g_pOmxVdec, chan_id);
    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, chan_id);
        return HI_FAILURE;
    }

    /* for we del element during, so use safe methods for list */
    spin_lock_irqsave(&pchan->raw_lock, flags);
    if (list_empty(&pchan->raw_queue))
    {
        spin_unlock_irqrestore(&pchan->raw_lock, flags);
        OmxPrint(OMX_ERR, "%s: list is empty\n", __func__);
        return 0;
    }

    list_for_each_entry_safe(pbuf, ptmp, &pchan->raw_queue, list)
    {
        if (stream_data->PhyAddr == (pbuf->phy_addr + pbuf->offset))
        {
            if (BUF_STATE_USING != pbuf->status)
            {
                OmxPrint(OMX_ERR, "%s: buf(0x%08x) flag confused!\n",__func__,  stream_data->PhyAddr);
            }

            pbuf->status = BUF_STATE_IDLE;
            list_del(&pbuf->list);
            is_find = 1;
            break;
        }
    }

    if (!is_find)
    {
        spin_unlock_irqrestore(&pchan->raw_lock, flags);
        OmxPrint(OMX_ERR, "%s: buffer(0x%08x) not in queue!\n", __func__, stream_data->PhyAddr);
        return HI_FAILURE;
    }

    if (pbuf->buf_id != LAST_FRAME_BUF_ID)
    {
        /* let msg to indicate buffer was given back */

        user_buf.dir         = PORT_DIR_INPUT;
        user_buf.bufferaddr  = pbuf->user_vaddr;
        user_buf.buffer_len  = pbuf->buf_len;
        user_buf.client_data = pbuf->client_data;
        user_buf.data_len    = 0;
        user_buf.timestamp   = 0;
        user_buf.phyaddr     = pbuf->phy_addr;

        pbuf->act_len        = user_buf.data_len;

        message_queue(pchan->msg_queue, VDEC_MSG_RESP_INPUT_DONE, VDEC_S_SUCCESS, (HI_VOID *)&user_buf);
    }
    else
    {
        pchan->eos_in_list = 0;
        OmxPrint(OMX_INFO, "Decoder release eos packet.\n");
    }

    pchan->raw_use_cnt = (pchan->raw_use_cnt > 0) ? (pchan->raw_use_cnt-1) : 0;

    if (pchan->input_flush_pending && (pchan->raw_use_cnt == 0))
    {
        OmxPrint(OMX_INBUF, "%s: input flush done!\n", __func__);
        message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_INPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
        pchan->input_flush_pending = 0;
    }

    spin_unlock_irqrestore(&pchan->raw_lock, flags);

    OmxPrint(OMX_INBUF, "Decoder release stream: PhyAddr = 0x%08x, VirAddr = %p, Len = %d\n",
    stream_data->PhyAddr, stream_data->VirAddr, stream_data->Length);

    return HI_SUCCESS;
}

static inline HI_S32 decoder_bind_mem(OMXVDEC_CHAN_CTX *pchan, VDEC_CHAN_FRAME_STORES *pFsParam)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_BIND_MEM_TO_CHANNEL, pFsParam, sizeof(VDEC_CHAN_FRAME_STORES));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s bind mem to channel failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}

static inline HI_S32 decoder_sync_ext_buffer(OMXVDEC_CHAN_CTX *pchan, EXTBUF_PARAM_S *pParam)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_SYNC_EXT_BUFFER, pParam, sizeof(EXTBUF_PARAM_S));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s sync ext buffer failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}

static inline HI_S32 decoder_activate_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_ACTIVATE_CHANNEL, HI_NULL, 0);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s activate channel failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}

static inline HI_S32 decoder_clear_stream(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_RELEASE_STREAM, HI_NULL, 0);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s release stream failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}

static inline HI_S32 decoder_alloc_mem(OMXVDEC_CHAN_CTX *pchan, VDEC_CHAN_FRAME_PARAM_S *pFsParam)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_ALLOC_MEM_TO_CHANNEL, pFsParam, sizeof(VDEC_CHAN_FRAME_PARAM_S));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s alloc mem to channel failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}


/*============ EXPORT INTERFACE =============*/
HI_S32 decoder_init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    pVfmwFunc = HI_NULL;

    ret = VDEC_MODULE_GetFunction(MODULE_VFMW, &g_OmxFunc.pDecoderFunc);
    if (HI_SUCCESS != ret || HI_NULL == g_OmxFunc.pDecoderFunc)
    {
        OmxPrint(OMX_FATAL, "%s get vfmw function failed!\n", __func__);
        return HI_FAILURE;
    }

    pVfmwFunc = (VFMW_EXPORT_FUNC_S *)(g_OmxFunc.pDecoderFunc);
    
    gIsNormalInit = 0;
    gIsSecureInit = 0;

    memset(&gNormalHalMem, 0, sizeof(MEM_BUFFER_S));
    memset(&gSecureHalMem, 0, sizeof(MEM_BUFFER_S));
    
    VDEC_INIT_MUTEX(&gDecoderSem);

    //decoder power on
    VDEC_Regulator_Enable();
    
    return HI_SUCCESS;
}

HI_S32 decoder_exit(HI_VOID)
{
    if (gIsNormalInit != 0)
    {
        (pVfmwFunc->pfnVfmwExit)(0);
        gIsNormalInit = 0;
    }

    if (gNormalHalMem.u32Size != 0)
    {
        omxvdec_release_mem(&gNormalHalMem);
    }
    
    if (gIsSecureInit != 0)
    {
        (pVfmwFunc->pfnVfmwExit)(1);
        gIsSecureInit = 0;
    }
    
    if (gSecureHalMem.u32Size != 0)
    {
        omxvdec_release_mem(&gSecureHalMem);
    }
    
    pVfmwFunc = HI_NULL;

    //decoder power off
    VDEC_Regulator_Disable();
    
    return HI_SUCCESS;
}

HI_S32 decoder_init_vfmw(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32           ret = HI_FAILURE;
    HI_CHAR          buf_name[20];
    HI_S32          *pIsInit = HI_NULL;
    MEM_BUFFER_S    *pHalMem = HI_NULL;
    MEM_DESC_S       stHalMem;
    VDEC_OPERATION_S stInitParam;
    
    VDEC_DOWN_INTERRUPTIBLE(&gDecoderSem);
    
    memset(&stInitParam, 0, sizeof(VDEC_OPERATION_S));

    if (HI_TRUE == pchan->is_tvp)
    {
        stInitParam.is_secure = 1;
        pHalMem = &gSecureHalMem;
        pIsInit = &gIsSecureInit;
    }
    else
    {
        stInitParam.is_secure = 0;
        pHalMem = &gNormalHalMem;
        pIsInit = &gIsNormalInit;
    }

    if (*pIsInit > 0)
    {
        OmxPrint(OMX_INFO, "Already init vfmw (%d), is_tvp = %d\n", *pIsInit, pchan->is_tvp);
        (*pIsInit)++;
        ret = HI_SUCCESS;
        goto EXIT;
    }
    
    if (0 == pHalMem->u32Size)
    {
        memset(&stHalMem, 0, sizeof(MEM_DESC_S));
        ret = (pVfmwFunc->pfnVfmwControl)(-1, VDEC_CID_GET_HAL_MEMSIZE, &stHalMem, sizeof(MEM_DESC_S));
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s call VDEC_CID_GET_HAL_MEMSIZE failed\n", __func__);
            ret = HI_FAILURE;
            goto EXIT;
        }
        pHalMem->u8IsSecure = (HI_TRUE==pchan->is_tvp)? 1 : 0;
        pHalMem->u32Size    = stHalMem.Length;
        snprintf(buf_name, sizeof(buf_name), "DEC_HAL_%s", (HI_TRUE==pchan->is_tvp)? "S" : "N");
        ret = VDEC_MEM_AllocAndMap(buf_name, OMXVDEC_ZONE, pHalMem);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s alloc mem for %s failed\n", __func__, buf_name);
            ret = HI_FAILURE;
            goto EXIT;
        }
    }

    stInitParam.adapter_type             = ADAPTER_TYPE_OMXVDEC;
    stInitParam.ext_halmem.IsSecure      = pHalMem->u8IsSecure;
    stInitParam.ext_halmem.PhyAddr       = pHalMem->u32StartPhyAddr;
    stInitParam.ext_halmem.VirAddr       = pHalMem->pStartVirAddr;
    stInitParam.ext_halmem.Length        = pHalMem->u32Size;
    stInitParam.ext_intf.event_handler   = decoder_event_handler;
    stInitParam.ext_intf.buffer_handler  = decoder_buffer_handler;
    stInitParam.ext_intf.mem_malloc      = VDEC_MEM_VfmwMalloc;
    stInitParam.ext_intf.mem_free        = VDEC_MEM_VfmwFree;
    stInitParam.ext_intf.power_on        = HI_NULL;  // not allow vfmw access to power intf
    stInitParam.ext_intf.power_off       = HI_NULL;

    ret = (pVfmwFunc->pfnVfmwInit)(&stInitParam);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s init vfmw failed!\n", __func__);
        omxvdec_release_mem(pHalMem);
        ret = HI_FAILURE;
        goto EXIT;
    }
    
    (*pIsInit) = 1;

    ret = HI_SUCCESS;

EXIT:
    VDEC_UP_INTERRUPTIBLE(&gDecoderSem);
    return ret;
}

HI_S32 decoder_exit_vfmw(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32        ret     = HI_FAILURE;
    HI_S32       *pIsInit = HI_NULL;
    MEM_BUFFER_S *pHalMem = HI_NULL;

    VDEC_DOWN_INTERRUPTIBLE(&gDecoderSem);

    if (HI_TRUE == pchan->is_tvp)
    {
        pHalMem = &gSecureHalMem;
        pIsInit = &gIsSecureInit;
    }
    else
    {
        pHalMem = &gNormalHalMem;
        pIsInit = &gIsNormalInit;
    }

    (*pIsInit) = ((*pIsInit)-1 < 0)? 0: (*pIsInit)-1;        
    if ((*pIsInit) > 0)
    {
        OmxPrint(OMX_INFO, "No need to exit vfmw (%d), is_tvp = %d\n", *pIsInit, pchan->is_tvp);
        ret = HI_SUCCESS;
        goto EXIT;
    }

    ret = (pVfmwFunc->pfnVfmwExit)(pchan->is_tvp);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit vfmw failed!\n", __func__);
    }

    omxvdec_release_mem(pHalMem);
    
    (*pIsInit) = 0;
    
EXIT:
    VDEC_UP_INTERRUPTIBLE(&gDecoderSem);
    return ret;
}

HI_S32 decoder_suspend(HI_VOID)
{
    if (pVfmwFunc != NULL && pVfmwFunc->pfnVfmwSuspend != NULL)
    {
        (pVfmwFunc->pfnVfmwSuspend)();

        //decoder power off
        VDEC_Regulator_Disable();
    }
    
    return HI_SUCCESS;
}

HI_S32 decoder_resume(HI_VOID)
{
    if (pVfmwFunc != NULL && pVfmwFunc->pfnVfmwResume != NULL)
    {
        //decoder power on
        VDEC_Regulator_Enable();

        (pVfmwFunc->pfnVfmwResume)();
    }
    
    return HI_SUCCESS;
}

HI_S32 decoder_create_inst(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_CHAN_CFG *pchan_cfg)
{
    HI_S32  ret = HI_FAILURE;
    HI_S8   as8TmpBuf[128];
    HI_CHAR buf_name[20];
	STREAM_INTF_S         StreamIntf;
    VDEC_CHAN_CAP_LEVEL_E enFmwCap;
    VDEC_CHAN_OPTION_S    stOption;
    DETAIL_MEM_SIZE       stMemSize;
    VDEC_CHAN_CFG_S       VfmwCfg;

    memset(&stOption,  0, sizeof(VDEC_CHAN_OPTION_S));
    memset(&stMemSize, 0, sizeof(DETAIL_MEM_SIZE));
    memset(&VfmwCfg,   0, sizeof(VDEC_CHAN_CFG_S));

    ret = decoder_init_vfmw(pchan);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call decoder_init_vfmw failed\n", __func__);
        return HI_FAILURE;
    }

    ret = decoder_init_option(pchan, pchan_cfg, &VfmwCfg, &enFmwCap, &stOption);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call decoder_init_option failed\n", __func__);
        goto error0;
    }
    
    ((HI_SIZE_T*)as8TmpBuf)[0] = (HI_SIZE_T)enFmwCap;
    ((HI_SIZE_T*)as8TmpBuf)[1] = (HI_SIZE_T)&stOption; //use HI_SIZE_T to store member, compatible to 32 & 64 system

    ret = (pVfmwFunc->pfnVfmwControl)(-1, VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION, as8TmpBuf, sizeof(as8TmpBuf));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call GET_CHAN_DETAIL_MEMSIZE failed\n", __func__);
        goto error0;
    }
    stMemSize = *(DETAIL_MEM_SIZE *)as8TmpBuf;

    /* Allocate frame buffer memory(VDH) */
    if (1 == stOption.u32DynamicFrameStoreAllocEn)
    {
        stOption.MemDetail.ChanMemVdh.Length  = 0;
        stOption.MemDetail.ChanMemVdh.PhyAddr = 0;
        stOption.MemDetail.ChanMemVdh.VirAddr = HI_NULL;
    }
    else if (stMemSize.VdhDetailMem > 0)
    {
        pchan->decoder_vdh_buf.u8IsSecure = (HI_TRUE==pchan->is_tvp)? 1 : 0;
        pchan->decoder_vdh_buf.u32Size    = stMemSize.VdhDetailMem;
        snprintf(buf_name, sizeof(buf_name), "Chan%d_VDH", pchan->channel_id);
        ret = VDEC_MEM_AllocAndMap(buf_name, OMXVDEC_ZONE, &pchan->decoder_vdh_buf);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s alloc mem for VDH failed\n", __func__);
            goto error0;
        }

        stOption.MemDetail.ChanMemVdh.Length  = pchan->decoder_vdh_buf.u32Size;
        stOption.MemDetail.ChanMemVdh.PhyAddr = pchan->decoder_vdh_buf.u32StartPhyAddr;
        stOption.MemDetail.ChanMemVdh.VirAddr = pchan->decoder_vdh_buf.pStartVirAddr;
    }

    /* Alloc SCD buffer */
    if (stMemSize.ScdDetailMem > 0)
    {
        pchan->decoder_scd_buf.u8IsSecure = (HI_TRUE==pchan->is_tvp)? 1 : 0;
        pchan->decoder_scd_buf.u32Size    = stMemSize.ScdDetailMem;
        snprintf(buf_name, sizeof(buf_name), "Chan%d_SCD", pchan->channel_id);
        ret = VDEC_MEM_AllocAndMap(buf_name, OMXVDEC_ZONE, &pchan->decoder_scd_buf);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s alloc mem for SCD failed\n", __func__);
            goto error1;
        }

        stOption.MemDetail.ChanMemScd.Length  = pchan->decoder_scd_buf.u32Size;
        stOption.MemDetail.ChanMemScd.PhyAddr = pchan->decoder_scd_buf.u32StartPhyAddr;
        stOption.MemDetail.ChanMemScd.VirAddr = pchan->decoder_scd_buf.pStartVirAddr;
    }

    if (stMemSize.CtxDetailMem > 0)
    {
        pchan->decoder_ctx_buf.u8IsSecure = (HI_TRUE==pchan->is_tvp)? 1 : 0;
        pchan->decoder_ctx_buf.u32Size    = stMemSize.CtxDetailMem;
        snprintf(buf_name, sizeof(buf_name), "Chan%d_CTX", pchan->channel_id);
        ret = VDEC_MEM_AllocAndMap(buf_name, OMXVDEC_ZONE, &pchan->decoder_ctx_buf);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s alloc mem for CTX failed\n", __func__);
            goto error2;
        }

        stOption.MemDetail.ChanMemCtx.Length  = pchan->decoder_ctx_buf.u32Size;
        stOption.MemDetail.ChanMemCtx.PhyAddr = pchan->decoder_ctx_buf.u32StartPhyAddr;
        stOption.MemDetail.ChanMemCtx.VirAddr = pchan->decoder_ctx_buf.pStartVirAddr;
    }
    
    ((HI_SIZE_T*)as8TmpBuf)[0] = (HI_SIZE_T)enFmwCap;
    ((HI_SIZE_T*)as8TmpBuf)[1] = (HI_SIZE_T)&stOption;

    ret = (pVfmwFunc->pfnVfmwControl)(-1, VDEC_CID_CREATE_CHAN_WITH_OPTION, as8TmpBuf, sizeof(as8TmpBuf));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s CREATE_CHAN_WITH_OPTION failed:%#x\n", __func__, ret);
        goto error3;
    }

    pchan->decoder_id = *(HI_U32 *)as8TmpBuf;
    OmxPrint(OMX_INFO, "Create decoder %d success!\n", pchan->decoder_id);

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_CFG_CHAN, &VfmwCfg, sizeof(VDEC_CHAN_CFG_S));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s CFG_CHAN failed\n", __func__);
        goto error3;
    }

    StreamIntf.stream_provider_inst_id = pchan->channel_id;
    StreamIntf.read_stream = decoder_get_stream;
    StreamIntf.release_stream = decoder_release_stream;
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_SET_STREAM_INTF, &StreamIntf, sizeof(STREAM_INTF_S));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s SET_STREAM_INTF failed\n", __func__);
        goto error4;
    }

    pchan->image_ops.image_provider_inst_id = pchan->channel_id;
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_GET_IMAGE_INTF, &pchan->image_ops, sizeof(IMAGE_INTF_S));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s GET_IMAGE_INTF failed\n", __func__);
        goto error4;
    }
    
    return HI_SUCCESS;

error4:
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_DESTROY_CHAN, HI_NULL, 0);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s DESTROY_CHAN failed\n", __func__);
    }
error3:
    omxvdec_release_mem(&pchan->decoder_ctx_buf);
error2:
    omxvdec_release_mem(&pchan->decoder_scd_buf);
error1:
    omxvdec_release_mem(&pchan->decoder_vdh_buf);
error0:
    decoder_exit_vfmw(pchan);
    
    return HI_FAILURE;
}

HI_S32 decoder_release_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_DESTROY_CHAN, HI_NULL, 0);
    if (ret != HI_SUCCESS)
    {
       OmxPrint(OMX_FATAL, "%s destroy vfmw failed\n", __func__);
       //return ret;  /* 不退出，强制释放资源 */
    }

    decoder_exit_vfmw(pchan);

    if (pchan->decoder_ctx_buf.u32Size != 0 && pchan->decoder_ctx_buf.u32StartPhyAddr != 0)
    {
        omxvdec_release_mem(&pchan->decoder_ctx_buf);
    }

    if (pchan->decoder_scd_buf.u32Size != 0 && pchan->decoder_scd_buf.u32StartPhyAddr != 0)
    {
        omxvdec_release_mem(&pchan->decoder_scd_buf);
    }

    if (pchan->decoder_vdh_buf.u32Size != 0 && pchan->decoder_vdh_buf.u32StartPhyAddr != 0)
    {
        omxvdec_release_mem(&pchan->decoder_vdh_buf);
    }

    return ret;
}

HI_S32 decoder_start_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_START_CHAN, HI_NULL, 0);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s start vfmw failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 decoder_stop_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_STOP_CHAN, HI_NULL, 0);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s stop vfmw failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 decoder_reset_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;
    VDEC_CHAN_RESET_OPTION_S  Option;

    Option.s32KeepBS     = 0;
    Option.s32KeepSPSPPS = 1;
    Option.s32KeepFSP    = 1;
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_RESET_CHAN_WITH_OPTION, &Option, sizeof(VDEC_CHAN_RESET_OPTION_S));
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s reset vfmw with option failed\n", __func__);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 decoder_ctrl_inst(OMXVDEC_CHAN_CTX *pchan, DECODER_CMD_E eCmd, HI_VOID *pParam)
{
    HI_S32 ret = HI_FAILURE;

    switch(eCmd)
    {
        case DEC_CMD_CLEAR_STREAM:
            ret = decoder_clear_stream(pchan);
            break;

        case DEC_CMD_ALLOC_MEM:
            ret = decoder_alloc_mem(pchan, (VDEC_CHAN_FRAME_PARAM_S *)pParam);
            break;

        case DEC_CMD_BIND_MEM:
            ret = decoder_bind_mem(pchan, (VDEC_CHAN_FRAME_STORES *)pParam);
            break;

        case DEC_CMD_ACTIVATE_INST:
            ret = decoder_activate_inst(pchan);
            break;
            
        case DEC_CMD_SYNC_EXT_BUF:
            ret = decoder_sync_ext_buffer(pchan, (EXTBUF_PARAM_S *)pParam);
            break;

        default:
            OmxPrint(OMX_FATAL, "%s unkown command %d\n", __func__, eCmd);
            break;
    }

    return ret;
}

HI_VOID decoder_proc_entry(OMXVDEC_CHAN_CTX *pchan, struct seq_file *p)
{
    PROC_PRINT(p, "%-20s :%d\n",    "Decoder",         pchan->decoder_id);
    PROC_PRINT(p, "%-20s :%d\n",    "GetPacketNum",    pchan->get_packet_num);
    PROC_PRINT(p, "%-20s :%d\n",    "DecFrameNum",     pchan->dec_frame_num);

    PROC_PRINT(p, "\n");
}
