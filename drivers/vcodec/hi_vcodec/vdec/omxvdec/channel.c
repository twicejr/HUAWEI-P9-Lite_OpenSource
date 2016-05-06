

#include "omxvdec.h"
#include "channel.h"
#include "decoder.h"
#include "processor.h"


/*=================== MACRO ====================*/
#define RESOLUTION_THRESHOLD (1920 * 1080)
#define INST_NUM_THRESHOLD   (1)


/*================ EXTERN VALUE ================*/
extern HI_BOOL  g_SaveRawEnable;
extern HI_CHAR  g_SavePath[];
extern HI_CHAR  g_SaveName[];


/*============== INTERNAL FUNCTION =============*/
static inline const HI_PCHAR channel_show_chan_state(eCHAN_STATE state)
{
	switch (state)
    {
       case CHAN_STATE_IDLE:
            return "IDLE";
            break;

       case CHAN_STATE_WORK:
            return "WORK";
            break;

       case CHAN_STATE_PAUSE:
            return "PAUSE";
            break;

       case CHAN_STATE_PAUSE_PENDING:
            return "PAUSE_PENDING";
            break;

       default:
            return "INVALID";
            break;
	}
}

static inline const HI_PCHAR channel_show_protocol(OMXVDEC_CODEC_TYPE protocol)
{
    /* CodecType Relative */
    HI_PCHAR s;
    switch (protocol)
    {
        case OMXVDEC_H264:
           s = "H264";
           break;

        case OMXVDEC_AVS:
           s = "AVS";
           break;

        case OMXVDEC_MPEG1:
           s = "MPEG1";
           break;

        case OMXVDEC_MPEG2:
           s = "MPEG2";
           break;

        case OMXVDEC_MPEG4:
           s = "MPEG4";
           break;

        case OMXVDEC_VC1:
           s = "VC1";
           break;

        case OMXVDEC_DIVX3:
           s = "DIVX3";
           break;

        case OMXVDEC_REAL8:
           s = "REAL8";
           break;

        case OMXVDEC_REAL9:
           s = "REAL9";
           break;

        case OMXVDEC_VP6:
           s = "VP6";
           break;

        case OMXVDEC_VP6F:
           s = "VP6F";
           break;

        case OMXVDEC_VP6A:
           s = "VP6A";
           break;

        case OMXVDEC_VP8:
           s = "VP8";
           break;

        case OMXVDEC_H263:
           s = "H263";
           break;

        case OMXVDEC_SORENSON:
           s = "SORENSON";
           break;

        case OMXVDEC_MVC:
           s = "MVC";
           break;

       case OMXVDEC_HEVC:
          s = "HEVC";
          break;

        default:
           s = "Unknow";
           break;
    }

    return s;
}

static inline const HI_PCHAR channel_show_dfs_state(eDFS_STATE state)
{
	switch (state)
    {
       case DFS_INIT:
            return "INIT";
            break;

       case DFS_WAIT_ALLOC:
            return "WAIT ALLOC";
            break;

       case DFS_WAIT_INSERT:
            return "WAIT INSERT";
            break;

       case DFS_WAIT_BIND:
            return "WAIT BIND";
            break;

       case DFS_WAIT_FILL:
            return "WAIT FILL";
            break;

       case DFS_WAIT_ACTIVATE:
            return "WAIT ACTIVATE";
            break;

       case DFS_ALREADY_ALLOC:
            return "ALREADY ALLOC";
            break;

       default:
            return "UNKOWN";
            break;
	}
}

static inline const HI_PCHAR channel_show_color_format(HI_U32 format)
{
    HI_PCHAR s;
    switch (format)
    {
       case OMX_PIX_FMT_NV12:
           s = "YUV420SemiPlanar";
           break;

       case OMX_PIX_FMT_NV21:
           s = "YVU420SemiPlanar";
           break;

       case OMX_PIX_FMT_YUV420Planar:
           s = "YUV420Planar";
           break;

       case OMX_PIX_FMT_YUV420Tile:
           s = "YUV420Tile";
           break;

       default:
           OmxPrint(OMX_ERR, "unkown format %d\n", format);
           s = "unkown format";
           break;
    }

    return s;
}

static inline const HI_PCHAR channel_show_buffer_state(eBUFFER_STATE state)
{
	switch (state)
    {
        case BUF_STATE_IDLE:
            return "idle";
            break;

        case BUF_STATE_QUEUED:
            return "queued";
            break;

        case BUF_STATE_USING:
            return "using";
            break;

        default:
            return "invalid";
            break;
	}
}

static HI_VOID channel_show_chan_config(OMXVDEC_CHAN_CFG *pcfg)
{
    OmxPrint(OMX_INFO, "\n");
    OmxPrint(OMX_INFO, " Protocol         = %s\n",    channel_show_protocol(pcfg->cfg_codec_type));
    OmxPrint(OMX_INFO, " Resolution       = %dx%d\n", pcfg->cfg_width, pcfg->cfg_height);
    OmxPrint(OMX_INFO, " Stride           = %d\n",    pcfg->cfg_stride);
    OmxPrint(OMX_INFO, " ColorFormat      = %s\n",    channel_show_color_format(pcfg->cfg_color_format));
    OmxPrint(OMX_INFO, " IsAdvProfile     = %d\n",    pcfg->cfg_codec_ext.vc1_ext.is_adv_profile);
    OmxPrint(OMX_INFO, " CodecVersion     = %d\n",    pcfg->cfg_codec_ext.vc1_ext.codec_version);
    OmxPrint(OMX_INFO, " bReversed        = %d\n",    pcfg->cfg_codec_ext.vp6_ext.need_reverse);
    OmxPrint(OMX_INFO, " SpecMode         = %d\n",    pcfg->spec_mode);
    OmxPrint(OMX_INFO, " Priority         = %d\n",    pcfg->priority);
    OmxPrint(OMX_INFO, " ErrThreshold     = %d\n",    pcfg->err_threshold);
    OmxPrint(OMX_INFO, " DecMode          = %d\n",    pcfg->dec_mode);
    OmxPrint(OMX_INFO, " OutputOrder      = %d\n",    pcfg->output_order);
    OmxPrint(OMX_INFO, " LowdlyEnable     = %d\n",    pcfg->lowdly_enable);
    OmxPrint(OMX_INFO, " CompressEnbale   = %d\n",    pcfg->compress_enable);
    OmxPrint(OMX_INFO, " ActInBufNum      = %d\n",    pcfg->act_inbuf_num);
    OmxPrint(OMX_INFO, " ActInBufSize     = %d\n",    pcfg->act_inbuf_size);
    OmxPrint(OMX_INFO, "\n");

	return;
}

static HI_S32 channel_add_chan_record(OMXVDEC_ENTRY *omxvdec, OMXVDEC_CHAN_CTX *pchan)
{
	HI_U32 record_id  = 0;
	HI_U32 channel_id = 0;
	unsigned long flags;
	OMXVDEC_CHAN_CTX *recorded_chan = HI_NULL;

    if (HI_NULL == omxvdec || pchan == HI_NULL)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
		return HI_FAILURE;
	}

	spin_lock_irqsave(&omxvdec->channel_lock, flags);
	if (!list_empty(&omxvdec->chan_list))
    {
        do {
            record_id = channel_id;
            list_for_each_entry(recorded_chan, &omxvdec->chan_list, chan_list)
            {
                if(recorded_chan->channel_id == channel_id)
                {
                    channel_id++;
                    break;
                }
            }
        }while(record_id != channel_id);
    }
    pchan->channel_id = channel_id;

	list_add_tail(&pchan->chan_list, &omxvdec->chan_list);
    omxvdec->total_chan_num++;

    /* Dynamic select vcodec freq*/    
    if (HI_FAILURE == channel_dynamic_freq_sel(pchan))
    {
        OmxPrint(OMX_ERR, "%s select vcodec freq failed\n", __func__);
    }

	spin_unlock_irqrestore(&omxvdec->channel_lock, flags);

    OmxPrint(OMX_INFO, "%s: channel %d create successfully!\n", __func__, channel_id);

	return HI_SUCCESS;
}

static HI_S32 channel_delete_chan_record(OMXVDEC_ENTRY *omxvdec, OMXVDEC_CHAN_CTX *pchan)
{
	unsigned long flags;

    if (HI_NULL == omxvdec || pchan == HI_NULL)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
		return HI_FAILURE;
	}

	spin_lock_irqsave(&omxvdec->channel_lock, flags);
	list_del(&pchan->chan_list);
    omxvdec->total_chan_num --;

    /* Dynamic select vcodec freq*/    
    if (HI_FAILURE == channel_dynamic_freq_sel(pchan))
    {
        OmxPrint(OMX_ERR, "%s select vcodec freq failed\n", __func__);
    }

	spin_unlock_irqrestore(&omxvdec->channel_lock, flags);

    OmxPrint(OMX_INFO, "%s: channel %d release successfully!\n", __func__, pchan->channel_id);

	return HI_SUCCESS;
}

static HI_S32 channel_map_kernel_viraddr(OMXVDEC_BUF_DESC *puser_buf)
{
    HI_S32        ret;
    MEM_BUFFER_S  stBuffer;
    
    if (OMX_USE_NATIVE == puser_buf->buffer_type)
    {
        memset(&stBuffer, 0, sizeof(MEM_BUFFER_S));
        stBuffer.u8IsSecure      = puser_buf->is_secure;
	    stBuffer.u32StartPhyAddr = puser_buf->phyaddr;
        stBuffer.u32Size         = puser_buf->buffer_len;
	    ret = VDEC_MEM_MapKernel(puser_buf->share_fd, &stBuffer);
	    if(ret != HI_SUCCESS)
	    {
	        OmxPrint(OMX_ERR, "%s get use buffer phyaddr or kern_vaddr failed!\n", __func__);
			return HI_FAILURE;
	    }
		puser_buf->kerneladdr = (HI_U64)stBuffer.pStartVirAddr;
    }
    else
    {
        // add other method if neccessary
    }

    return HI_SUCCESS;
}

static HI_S32 channel_unmap_kernel_viraddr(OMXVDEC_BUF_DESC *puser_buf)
{
    MEM_BUFFER_S  stBuffer;

    if (OMX_USE_NATIVE == puser_buf->buffer_type)
    {
        memset(&stBuffer, 0, sizeof(MEM_BUFFER_S));
        stBuffer.u8IsSecure      = puser_buf->is_secure;
        stBuffer.pStartVirAddr   = (HI_VOID *)puser_buf->kerneladdr;
	    stBuffer.u32StartPhyAddr = puser_buf->phyaddr;
        stBuffer.u32Size         = puser_buf->buffer_len;
        VDEC_MEM_UnmapKernel(&stBuffer);
    }
    else
    {
        // add other method if neccessary
    }

    return HI_SUCCESS;
}

static OMXVDEC_BUF_S *channel_lookup_addr_table(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
	HI_S32         i = 0;
    HI_S32        *num_of_buffers = HI_NULL;
	HI_U32        tmp_addr        = 0;
	OMXVDEC_BUF_S *buf_addr_table = HI_NULL;

	if (HI_NULL == pchan || HI_NULL == puser_buf)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
		return HI_NULL;
	}

	if (puser_buf->dir == PORT_DIR_INPUT)
    {
		buf_addr_table = (OMXVDEC_BUF_S *)pchan->in_buf_table;
		num_of_buffers = &pchan->input_buf_num;
	}
    else if (puser_buf->dir == PORT_DIR_OUTPUT)
    {
        buf_addr_table = (OMXVDEC_BUF_S *)pchan->out_buf_table;
        num_of_buffers = &pchan->output_buf_num;
    }
    else
    {
        OmxPrint(OMX_ERR, "%s buf dir invalid!\n", __func__);
        return HI_NULL;
    }

	for (i = 0; i < *num_of_buffers; i++)
    {
        tmp_addr = buf_addr_table[i].phy_addr;
        if (puser_buf->phyaddr == tmp_addr)
        {
            break;
        }
    }

    if (i < *num_of_buffers)
    {
	    // in alloc usr path, insert in table before map user addr, so update user addr here
        buf_addr_table[i].user_vaddr = puser_buf->bufferaddr;
        return &buf_addr_table[i];
    }

    OmxPrint(OMX_ERR, "%s buffer(0x%08x) not found!\n", __func__, puser_buf->phyaddr);

	return HI_NULL;
}

static HI_U32 channel_insert_addr_table(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
	HI_S32   i = 0;
	HI_S32   ret = HI_FAILURE;
	HI_U32   phyaddr         = 0;
	HI_S32  *num_of_buffers       = HI_NULL;
	OMXVDEC_BUF_S *buf_addr_table = HI_NULL;
	OMXVDEC_BUF_S *pbuf           = HI_NULL;
    
    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);
    
	if (puser_buf->dir == PORT_DIR_INPUT)
    {
        OmxPrint(OMX_INBUF, "Insert Input Buffer, phy addr = 0x%08x\n", puser_buf->phyaddr);
        pchan->max_in_buf_num = MIN(MAX_BUFFER_SLOT_NUM, puser_buf->max_frm_num);

        buf_addr_table = (OMXVDEC_BUF_S *)pchan->in_buf_table;
        num_of_buffers = &pchan->input_buf_num;
        if (*num_of_buffers >= pchan->max_in_buf_num)
        {
            OmxPrint(OMX_ERR, "%s: number of buffers reached max in value(%d)\n", __func__, pchan->max_in_buf_num);
            VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
            return HI_FAILURE;
        }
    }
    else if (puser_buf->dir == PORT_DIR_OUTPUT)
    {
        OmxPrint(OMX_OUTBUF, "Insert Output Buffer, phy addr = 0x%08x\n", puser_buf->phyaddr);
        pchan->max_out_buf_num = MIN(MAX_BUFFER_SLOT_NUM, puser_buf->max_frm_num);

        buf_addr_table = (OMXVDEC_BUF_S *)pchan->out_buf_table;
        num_of_buffers = &pchan->output_buf_num;
        if (*num_of_buffers >= pchan->max_out_buf_num)
        {
            OmxPrint(OMX_ERR, "%s: number of buffers reached max out value(%d)\n", __func__, pchan->max_out_buf_num);
            VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
            return HI_FAILURE;
        }
    }
    else
    {
        OmxPrint(OMX_ERR, "%s: Buffer dir(%d) Invalid!\n", __func__, puser_buf->dir);
        VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
		return HI_FAILURE;
	}

	phyaddr = puser_buf->phyaddr;
	i = 0;
	while ((i < *num_of_buffers) && (phyaddr != buf_addr_table[i].phy_addr))
    {
        i++;
    }

	if (i < *num_of_buffers)
    {
        OmxPrint(OMX_ERR, "%s: phyaddr = 0x%x already insert\n", __func__, phyaddr);
        VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
        return HI_FAILURE;
    }

    if (OMX_ALLOCATE_DRV != puser_buf->buffer_type)
    {
        /* get kernel virtual address */
        if (channel_map_kernel_viraddr(puser_buf) != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s: get_addr failed (phyaddr: 0x%x)\n", __func__, phyaddr);
            VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
            return HI_FAILURE;
        }
    }

    pbuf = buf_addr_table + *num_of_buffers;
    pbuf->user_vaddr  = puser_buf->bufferaddr;
    pbuf->phy_addr    = puser_buf->phyaddr;
    pbuf->kern_vaddr  = (HI_VOID *)puser_buf->kerneladdr;
    pbuf->client_data = puser_buf->client_data;
    pbuf->buf_len     = puser_buf->buffer_len;
    pbuf->act_len     = 0;
    pbuf->offset      = 0;
    pbuf->buf_type    = puser_buf->buffer_type;
    pbuf->status      = BUF_STATE_IDLE;
    pbuf->buf_id      = *num_of_buffers;
    
    channel_sync_frame_buffer(pchan, pbuf->phy_addr, EXTBUF_INSERT);

    // buffer num increase
    *num_of_buffers   = *num_of_buffers + 1;
    
	if (puser_buf->dir == PORT_DIR_INPUT)
    {
        OmxPrint(OMX_INBUF, "Insert Input Buffer, PhyAddr = 0x%08x, Success!\n", puser_buf->phyaddr);
    }
    else
    {
        OmxPrint(OMX_OUTBUF, "Insert Output Buffer, PhyAddr = 0x%08x, Success!\n", puser_buf->phyaddr);
        
        // record actual frame size
        if (pchan->output_buf_size != puser_buf->buffer_len)
        {
            if (1 == *num_of_buffers)
            {
                pchan->output_buf_size = puser_buf->buffer_len;
            }
            else
            {
                OmxPrint(OMX_ERR, "%s ERROR: new buf size %d != old buf size %d\n", __func__, puser_buf->buffer_len, pchan->output_buf_size);
                pchan->output_buf_size = MIN(pchan->output_buf_size, puser_buf->buffer_len);
            }
        }

        if (*num_of_buffers == puser_buf->max_frm_num)
        {
            if (DFS_WAIT_INSERT == pchan->dfs_alloc_flag)
            {
                OmxPrint(OMX_INFO, "All inserted, wake up task to bind mem.\n");
                pchan->dfs_alloc_flag = DFS_WAIT_BIND;
                ret = channel_bind_mem_to_inst(pchan);
        		if (ret != HI_SUCCESS)
        	    {
        	        OmxPrint(OMX_ERR, "%s bind mem to inst failed!\n", __func__);
                    message_queue(pchan->msg_queue, VDEC_ERR_DYNAMIC_ALLOC_FAIL, HI_FAILURE, NULL);
        		}
                else
                {
                    pchan->dfs_alloc_flag = DFS_WAIT_FILL;
                }
            }
        }
    }
    
    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);

	return HI_SUCCESS;
}

static HI_U32 channel_delete_addr_table(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
	HI_U32 i            = 0;
	HI_S32 is_find      = 0;
	HI_U32 phyaddr      = 0;
	unsigned long flags = 0;
    spinlock_t        *p_lock         = HI_NULL;
	HI_U32            *num_of_buffers = HI_NULL;
	OMXVDEC_BUF_S     *ptmp           = HI_NULL;
	OMXVDEC_BUF_S     *pbuf           = HI_NULL;
	struct list_head  *p_queue        = HI_NULL;
	OMXVDEC_BUF_S     *p_qbuf         = HI_NULL;
	OMXVDEC_BUF_S     *buf_addr_table = HI_NULL;
    
    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);
    
	if (puser_buf->dir == PORT_DIR_INPUT)
    {
        OmxPrint(OMX_INBUF, "Delete Input Buffer, phy addr = 0x%08x\n", puser_buf->phyaddr);
        buf_addr_table = pchan->in_buf_table;
        num_of_buffers = &pchan->input_buf_num;
        p_lock = &pchan->raw_lock;
        p_queue = &pchan->raw_queue;
	}
    else if (puser_buf->dir == PORT_DIR_OUTPUT)
	{
        OmxPrint(OMX_OUTBUF, "Delete Output Buffer, phy addr = 0x%08x\n", puser_buf->phyaddr);
        buf_addr_table = pchan->out_buf_table;
        num_of_buffers = &pchan->output_buf_num;
        p_lock = &pchan->yuv_lock;
        p_queue = &pchan->yuv_queue;
	}

	if (HI_NULL == num_of_buffers || HI_NULL == buf_addr_table || HI_NULL == p_lock || HI_NULL == p_queue)
    {
        OmxPrint(OMX_ERR, "%s Table is empty!!\n", __func__);
        VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
		return HI_FAILURE;
	}

	phyaddr = puser_buf->phyaddr;
	while ((i < *num_of_buffers) && (phyaddr != buf_addr_table[i].phy_addr))
    {
        i++;
    }

    if (i >= *num_of_buffers)
    {
        i=0;
        OmxPrint(OMX_ERR, "%s: in table, phyaddr = 0x%x not found\n", __func__, phyaddr);
        OmxPrint(OMX_ERR, "--------table--------\n");
        while (i < *num_of_buffers)
        {
            OmxPrint(OMX_ERR, "%d phy addr = 0x%x\n", i, buf_addr_table[i].phy_addr);
            i++;
        }
        OmxPrint(OMX_ERR, "--------------------\n");
        
        VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
        return HI_FAILURE;
    }

	pbuf = &buf_addr_table[i];

	if (BUF_STATE_USING == pbuf->status)
    {
        OmxPrint(OMX_ERR, "WARN: buffer 0x%x still in use?!\n", phyaddr);
	}
    channel_sync_frame_buffer(pchan, pbuf->phy_addr, EXTBUF_NULL);

    if (OMX_ALLOCATE_DRV != puser_buf->buffer_type)
    {
        /* unmap kernel virtual address */
        channel_unmap_kernel_viraddr(puser_buf);
    }
    pbuf->kern_vaddr = HI_NULL;

	if (i < (*num_of_buffers - 1))
    {
        /* copy into new addr slot */
        memcpy(pbuf, &buf_addr_table[*num_of_buffers - 1], sizeof(OMXVDEC_BUF_S));
        pbuf->buf_id = i;

        spin_lock_irqsave(p_lock, flags);
        if (!list_empty(p_queue))
        {
			list_for_each_entry_safe(p_qbuf, ptmp, p_queue, list)
			{
				if (buf_addr_table[*num_of_buffers - 1].phy_addr == (p_qbuf->phy_addr))
				{
					is_find = 1;
					/* delete old node in list */
					list_del(&p_qbuf->list);
					break;
				}
			}

			/* insert new node into list */
			if (is_find)
			{
				list_add_tail(&pbuf->list, p_queue);
			}
		}
		spin_unlock_irqrestore(p_lock, flags);
    }

    memset(&buf_addr_table[*num_of_buffers - 1], 0, sizeof(OMXVDEC_BUF_S));
	*num_of_buffers = *num_of_buffers - 1;

	if (puser_buf->dir == PORT_DIR_INPUT)
    {
        OmxPrint(OMX_INBUF, "Delete Input Buffer, phy addr = 0x%08x, Done!\n", puser_buf->phyaddr);
    }
    else
    {
        OmxPrint(OMX_OUTBUF, "Delete Output Buffer, phy addr = 0x%08x, Done!\n", puser_buf->phyaddr);
    }
    
    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);

	return HI_SUCCESS;
}

HI_S32 channel_insert_in_raw_list(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_S *pstream)
{
	HI_S32 is_find = 0;
	unsigned long  flags;
	OMXVDEC_BUF_S *pbuf = HI_NULL;

    spin_lock_irqsave(&pchan->raw_lock, flags);
    if (!(list_empty(&pchan->raw_queue)))
    {
        list_for_each_entry(pbuf, &pchan->raw_queue, list)
        {
            if (pstream->phy_addr == pbuf->phy_addr)
            {
                is_find = 1;
                break;
            }
        }

        if (is_find)
        {
            OmxPrint(OMX_ERR, "0x%x already in raw list!\n", pstream->phy_addr);
            spin_unlock_irqrestore(&pchan->raw_lock, flags);
            return HI_FAILURE;
        }
    }

    OmxPrint(OMX_INBUF, "Empty this buffer, phyaddr: 0x%08x, data_len: %d\n", pstream->phy_addr, pstream->act_len);

    /* insert the stream packet to raw queue */
    pstream->status = BUF_STATE_QUEUED;
    list_add_tail(&pstream->list, &pchan->raw_queue);

    spin_unlock_irqrestore(&pchan->raw_lock, flags);

    return HI_SUCCESS;
}

HI_S32 channel_insert_in_yuv_list(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_S *pframe)
{
	HI_S32 is_find = 0;
	unsigned long  flags;
	OMXVDEC_BUF_S *pbuf = HI_NULL;

    spin_lock_irqsave(&pchan->yuv_lock, flags);
    if (!(list_empty(&pchan->yuv_queue)))
    {
        list_for_each_entry(pbuf, &pchan->yuv_queue, list)
        {
            if (pframe->phy_addr == pbuf->phy_addr)
            {
                is_find = 1;
                break;
            }
        }

        if (is_find)
        {
            OmxPrint(OMX_ERR, "0x%x already in yuv list!\n", pframe->phy_addr);
            spin_unlock_irqrestore(&pchan->yuv_lock, flags);
            return HI_FAILURE;
        }
    }

	OmxPrint(OMX_OUTBUF, "Fill this buffer, phyaddr:0x%08x\n", pframe->phy_addr);

	pframe->status = BUF_STATE_QUEUED;
	list_add_tail(&pframe->list, &pchan->yuv_queue);
    
    channel_sync_frame_buffer(pchan, pframe->phy_addr, EXTBUF_READY);

	spin_unlock_irqrestore(&pchan->yuv_lock, flags);

    return HI_SUCCESS;
}

static HI_S32 channel_add_last_frame(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_S *pstream)
{
    if (HI_NULL == pchan || HI_NULL == pstream)
    {
        OmxPrint(OMX_ERR, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

    pstream->act_len    = pstream->buf_len;
    pstream->offset     = 0;
    pstream->flags      = VDEC_BUFFERFLAG_ENDOFFRAME;
    pstream->time_stamp = HI_INVALID_PTS;
    pstream->buf_id     = LAST_FRAME_BUF_ID;

    return HI_SUCCESS;
}

static HI_S32 channel_save_stream(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_S *pstream)
{
    HI_S32        len = 0;
    mm_segment_t  oldfs;
    HI_CHAR       FilePath[PATH_LEN];

    if (HI_TRUE == g_SaveRawEnable && pchan->raw_file == HI_NULL)
    {
        snprintf(FilePath, sizeof(FilePath), "%s/%s_%d.raw", g_SavePath, g_SaveName, pchan->channel_id);
        pchan->raw_file = filp_open(FilePath, O_RDWR|O_CREAT|O_TRUNC, S_IRWXO);
        if (IS_ERR(pchan->raw_file))
        {
            OmxPrint(OMX_ERR, "%s open raw file %s failed, ret=%ld\n", __func__, FilePath, PTR_ERR(pchan->raw_file));
            pchan->raw_file = HI_NULL;
        }
        else
        {
            OmxPrint(OMX_ALWS, "Start to save raw data of inst_%d in %s\n", pchan->channel_id, FilePath);
        }
    }
    else if (HI_FALSE == g_SaveRawEnable && pchan->raw_file != HI_NULL)
    {
        filp_close(pchan->raw_file, HI_NULL);
        pchan->raw_file = HI_NULL;
        OmxPrint(OMX_ALWS, "Stop saving raw data of inst_%d.\n", pchan->channel_id);
    }
    if (pchan->raw_file != HI_NULL)
    {
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        len = pchan->raw_file->f_op->write(pchan->raw_file, pstream->kern_vaddr, pstream->act_len, &pchan->raw_file->f_pos);
        set_fs(oldfs);
        OmxPrint(OMX_ALWS, "Saving raw data of inst_%d, length = %d\n", pchan->channel_id, pstream->act_len);
    }

    return HI_SUCCESS;
}


/*============== EXPORT INTERFACE =============*/
HI_S32 channel_init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

	OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    ret = VDEC_MEM_Init();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s init ion mem failed!\n", __func__);
        return HI_FAILURE;
    }

    ret = decoder_init();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s init decoder failed!\n", __func__);
		goto error0;
    }

    ret = processor_init();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s init processor failed!\n", __func__);
		goto error1;
    }
    
	OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;

error1:
    ret = decoder_exit();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit decoder failed!\n", __func__);
    }
error0:
    ret = VDEC_MEM_Exit();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit ion mem failed!\n", __func__);
    }

    return HI_FAILURE;
}

HI_VOID channel_exit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

	OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    ret = decoder_exit();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit decoder failed!\n", __func__);
    }

    ret = processor_exit();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit processor failed!\n", __func__);
    }

    ret = VDEC_MEM_Exit();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit ion mem failed!\n", __func__);
    }
    
	OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);
    
    return;
}

HI_S32 channel_suspend(HI_VOID)
{
    HI_S32 ret;

    ret = processor_suspend();
    if (ret != HI_SUCCESS)
    {
	    OmxPrint(OMX_FATAL, "%s: processor suspend failed!\n", __func__);
    }

    ret = decoder_suspend();
    if (ret != HI_SUCCESS)
    {
	    OmxPrint(OMX_FATAL, "%s: decoder suspend failed!\n", __func__);
    }

    return HI_SUCCESS;
}

HI_S32 channel_resume(HI_VOID)
{
    HI_S32 ret;

    ret = decoder_resume();
    if (ret != HI_SUCCESS)
    {
	    OmxPrint(OMX_FATAL, "%s: decoder resume failed!\n", __func__);
    }

    ret = processor_resume();
    if (ret != HI_SUCCESS)
    {
	    OmxPrint(OMX_FATAL, "%s: processor resume failed!\n", __func__);
    }

    return HI_SUCCESS;
}

HI_S32 channel_create_inst(struct file *fd, OMXVDEC_CHAN_CFG *pcfg)
{
	HI_S32  ret = 0;
    HI_CHAR buf_name[20];
    MEM_BUFFER_S      chan_buf;
	OMXVDEC_CHAN_CTX *pchan   = HI_NULL;
	OMXVDEC_ENTRY    *omxvdec = HI_NULL;

    /* Get omxvdec */
    omxvdec = fd->private_data;
    if (HI_NULL == omxvdec)
    {
	    OmxPrint(OMX_FATAL, "%s: omxvdec = null, error!\n", __func__);
	    return HI_FAILURE;
    }

    /* Alloc context */
    memset(&chan_buf, 0, sizeof(MEM_BUFFER_S));
    chan_buf.u32Size = sizeof(OMXVDEC_CHAN_CTX);
    snprintf(buf_name, sizeof(buf_name), "Chan%d_OMX", omxvdec->total_chan_num);
    ret = VDEC_MEM_AllocAndMap(buf_name, OMXVDEC_ZONE, &chan_buf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s alloc chan buffer mem failed\n", __func__);
		return HI_FAILURE;
    }
    pchan = (OMXVDEC_CHAN_CTX *)chan_buf.pStartVirAddr;
    memset(pchan, 0, sizeof(OMXVDEC_CHAN_CTX));
    memcpy(&pchan->channel_buf, &chan_buf, sizeof(MEM_BUFFER_S));

    pchan->max_in_buf_num  = MIN(MAX_BUFFER_SLOT_NUM, pcfg->cfg_inbuf_num);
    pchan->max_out_buf_num = MIN(MAX_BUFFER_SLOT_NUM, pcfg->cfg_outbuf_num);

    /* Initialize ctx resource */
    VDEC_INIT_MUTEX(&pchan->chan_mutex);
	spin_lock_init(&pchan->raw_lock);
	spin_lock_init(&pchan->yuv_lock);

	INIT_LIST_HEAD(&pchan->chan_list);
	INIT_LIST_HEAD(&pchan->raw_queue);
	INIT_LIST_HEAD(&pchan->yuv_queue);
    
    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);

	pchan->vdec     = omxvdec;
    pchan->file_dec = (HI_U64)fd;

	/* Record this channel */
	ret = channel_add_chan_record(omxvdec, pchan);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s add chan record failed\n", __func__);
		goto cleanup0;
    }

    /* Create decoder */
    channel_show_chan_config(pcfg);
    pchan->out_width  = pcfg->cfg_width;
    pchan->out_height = pcfg->cfg_height;
	pchan->out_stride = pcfg->cfg_stride;
	ret = decoder_create_inst(pchan, pcfg);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call channel_create_with_vfmw failed!\n", __func__);
		goto cleanup1;
	}

    /* Create processor */
    ret = processor_create_inst(pchan, pcfg->cfg_color_format);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call channel_create_with_vpss failed!\n", __func__);
		goto cleanup2;
	}

    /* Initialize msg queue */
	pchan->msg_queue = message_queue_init(pchan->channel_id, QUEUE_DEFAULT_DEPTH);
	if (HI_NULL == pchan->msg_queue)
    {
        OmxPrint(OMX_FATAL, "%s call msg_queue_init failed!\n", __func__);
		goto cleanup3;
	}

    /* Get memory resource */
    pchan->decoder_eos_buf.u8IsSecure = (HI_TRUE==pchan->is_tvp)? 1 : 0;
    pchan->decoder_eos_buf.u32Size    = LAST_FRAME_BUF_SIZE;
    snprintf(buf_name, sizeof(buf_name), "Chan%d_EOS", pchan->channel_id);
    ret = VDEC_MEM_AllocAndMap(buf_name, OMXVDEC_ZONE, &pchan->decoder_eos_buf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s alloc eos buffer mem failed\n", __func__);
		goto cleanup4;
    }

    pchan->last_frame.phy_addr   = pchan->decoder_eos_buf.u32StartPhyAddr;
    pchan->last_frame.kern_vaddr = pchan->decoder_eos_buf.pStartVirAddr;
    pchan->last_frame.buf_len    = LAST_FRAME_BUF_SIZE;

	pchan->channel_state = CHAN_STATE_IDLE;
    
    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);

	return pchan->channel_id;
    
cleanup4:
    message_queue_deinit(pchan->msg_queue);
cleanup3:
	processor_release_inst(pchan);
cleanup2:
	decoder_release_inst(pchan);
cleanup1:
	channel_delete_chan_record(omxvdec, pchan);
cleanup0:
    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
	VDEC_MEM_UnmapAndRelease(&pchan->channel_buf);

	return HI_FAILURE;
}

HI_S32 channel_release_inst(OMXVDEC_CHAN_CTX *pchan)
{
    eCHAN_STATE state;
    OMXVDEC_ENTRY *omxvdec = HI_NULL;

	if (HI_NULL == pchan)
	{
        OmxPrint(OMX_FATAL, "%s pchan = NULL\n", __func__);
		return HI_FAILURE;
	}

    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);
    
    omxvdec = pchan->vdec;
	if (HI_NULL == omxvdec)
	{
        OmxPrint(OMX_FATAL, "%s omxvdec = NULL\n", __func__);
        VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
		return HI_FAILURE;
	}

	state = pchan->channel_state;
	if (CHAN_STATE_WORK == state || CHAN_STATE_PAUSE == state)
    {
		if (decoder_stop_inst(pchan) < 0)
        {
            OmxPrint(OMX_FATAL, "%s call decoder_stop_inst failed!\n", __func__);
		}

        if (processor_stop_inst(pchan) < 0)
        {
            OmxPrint(OMX_FATAL, "%s call processor_stop_inst failed!\n", __func__);
        }

		/*check if the msg queue read out*/
		pchan->channel_state = CHAN_STATE_IDLE;
	}

	if (processor_release_inst(pchan) < 0)
    {
        OmxPrint(OMX_FATAL, "%s call processor_release_inst failed!\n", __func__);
	}

	if (decoder_release_inst(pchan) < 0)
    {
        OmxPrint(OMX_FATAL, "%s call decoder_release_inst failed!\n", __func__);
	}

    if (pchan->raw_file != HI_NULL)
    {
        filp_close(pchan->raw_file, HI_NULL);
        pchan->raw_file = HI_NULL;
    }

    omxvdec_release_mem(&pchan->decoder_eos_buf);

	message_queue_deinit(pchan->msg_queue);

	pchan->channel_state = CHAN_STATE_INVALID;

	channel_delete_chan_record(omxvdec, pchan);

    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);

	VDEC_MEM_UnmapAndRelease(&pchan->channel_buf);

	return HI_SUCCESS;
}

HI_S32 channel_start_inst(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret    = HI_FAILURE;
	HI_U32 status = VDEC_S_FAILED;

    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);

	if (pchan->channel_state == CHAN_STATE_WORK)
    {
        OmxPrint(OMX_ERR, "%s already in work state!\n", __func__);
		goto error;
	}

	ret = decoder_start_inst(pchan);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call decoder_start_inst failed!\n", __func__);
		goto error;
	}

	ret = processor_start_inst(pchan);
	if (ret != HI_SUCCESS)
    {
        ret = decoder_stop_inst(pchan);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s call decoder_stop_inst failed!\n", __func__);
        }
        OmxPrint(OMX_FATAL, "%s call processor_start_inst failed!\n", __func__);
		goto error;
	}

	pchan->channel_state = CHAN_STATE_WORK;

	status = VDEC_S_SUCCESS;

error:
	message_queue(pchan->msg_queue, VDEC_MSG_RESP_START_DONE, status, HI_NULL);
    OmxPrint(OMX_INFO, "%s post msg ret=%d,status=%d!\n", __func__, ret, status);
    
    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);

	return ret;
}

HI_S32 channel_stop_inst(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret    = HI_FAILURE;
	HI_U32 status = VDEC_S_FAILED;
    
    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);

	if (pchan->channel_state == CHAN_STATE_IDLE)
    {
		status = VDEC_ERR_BAD_STATE;
        OmxPrint(OMX_FATAL, "%s already stop!\n", __func__);
	}
    else
    {
		status = VDEC_S_SUCCESS;
	    pchan->channel_state = CHAN_STATE_IDLE;
    }

    // stop order is important!!
    if (VDEC_S_SUCCESS == status)
    {
        ret = decoder_stop_inst(pchan);
    	if (ret != HI_SUCCESS)
        {
    		status = VDEC_ERR_HW_FATAL;
            OmxPrint(OMX_FATAL, "%s call channel_stop_with_vfmw failed!\n", __func__);
    	}

    	ret = processor_stop_inst(pchan);
    	if (ret != HI_SUCCESS)
        {
    		status = VDEC_ERR_HW_FATAL;
            OmxPrint(OMX_FATAL, "%s call channel_stop_with_vpss failed!\n", __func__);
    	}
        
    	ret = HI_SUCCESS;
    }
    else
    {
        OmxPrint(OMX_INFO, "%s post msg ret=%d,status=%d!\n", __func__, ret, status);
    	ret = HI_FAILURE;
    }

    message_queue(pchan->msg_queue, VDEC_MSG_RESP_STOP_DONE, status, HI_NULL);
    
    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
    
    return ret;
}

HI_S32 channel_reset_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_SUCCESS;

    pchan->reset_pending = 1;

    ret = processor_stop_inst(pchan);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s stop processor failed!\n", __func__);
    }

    ret = decoder_reset_inst(pchan);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s reset decoder failed!\n", __func__);
    }

    ret = processor_start_inst(pchan);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s start processor failed!\n", __func__);
    }

    pchan->reset_pending = 0;

    return ret;
}

HI_S32 channel_pause_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 post_msg = 0;
    
    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);

	if (pchan->channel_state != CHAN_STATE_WORK)
    {
        OmxPrint(OMX_ERR, "%s state != CHAN_STATE_WORK!\n", __func__);
        message_queue(pchan->msg_queue, VDEC_MSG_RESP_PAUSE_DONE, VDEC_ERR_BAD_STATE, HI_NULL);
        VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
		return HI_FAILURE;
	}

	pchan->channel_state = CHAN_STATE_PAUSE;
	if (0 == pchan->yuv_use_cnt)
    {
        post_msg = 1;
    }
	else
    {
        pchan->pause_pending = 1;
    }

	if (post_msg)
    {
        message_queue(pchan->msg_queue, VDEC_MSG_RESP_PAUSE_DONE, VDEC_S_SUCCESS, HI_NULL);
    }

    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);

	return HI_SUCCESS;
}

HI_S32 channel_resume_inst(OMXVDEC_CHAN_CTX *pchan)
{
    VDEC_DOWN_INTERRUPTIBLE(&pchan->chan_mutex);

	if (pchan->channel_state != CHAN_STATE_PAUSE)
    {
        OmxPrint(OMX_FATAL, "%s state != CHAN_STATE_PAUSE!\n", __func__);
	    message_queue(pchan->msg_queue, VDEC_MSG_RESP_RESUME_DONE, VDEC_ERR_BAD_STATE, HI_NULL);
        VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);
	    return HI_FAILURE;
	}

	/* bad state change */
	if (pchan->pause_pending)
    {
        pchan->pause_pending = 0;
    }

	pchan->channel_state = CHAN_STATE_WORK;

    message_queue(pchan->msg_queue, VDEC_MSG_RESP_RESUME_DONE, VDEC_S_SUCCESS, HI_NULL);

    VDEC_UP_INTERRUPTIBLE(&pchan->chan_mutex);

	return HI_SUCCESS;
}

HI_S32 channel_alloc_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
    HI_S32  ret = HI_FAILURE;
    HI_S32  share_fd = -1;
    HI_CHAR buf_name[20];
    MEM_BUFFER_S stMemBuf;

    if (HI_NULL == pchan || HI_NULL == puser_buf || 0 == puser_buf->buffer_len)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

    if (0 == puser_buf->dir)
    {
        snprintf(buf_name, sizeof(buf_name), "Chan%d_IN", pchan->channel_id);
    }
    else
    {
        snprintf(buf_name, sizeof(buf_name), "Chan%d_OUT", pchan->channel_id);
    }

    memset(&stMemBuf, 0, sizeof(MEM_BUFFER_S));
    stMemBuf.u8IsSecure = puser_buf->is_secure;
    stMemBuf.u32Size    = puser_buf->buffer_len;
    ret = VDEC_MEM_AllocAndShare(buf_name, OMXVDEC_ZONE, &stMemBuf, &share_fd);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s chan %d call DRV_MEM_AllocUserBuffer failed!\n", __func__, pchan->channel_id);
        return HI_FAILURE;
    }

    puser_buf->kerneladdr = (HI_U64)stMemBuf.pStartVirAddr;
    puser_buf->phyaddr    = stMemBuf.u32StartPhyAddr;
    puser_buf->share_fd   = share_fd;

    ret = channel_insert_addr_table(pchan, puser_buf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s call channel_insert_addr_table failed!\n", __func__);
        VDEC_MEM_CloseAndFree(&stMemBuf, &share_fd);
        return HI_FAILURE;
    }

    /*When using android native buffer, the stride may not be match!*/
    if (pchan->out_stride != puser_buf->out_frame.stride)
    {
        pchan->out_stride = puser_buf->out_frame.stride;
    }

    return HI_SUCCESS;
}

HI_S32 channel_free_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
    HI_S32 ret = HI_FAILURE;
    MEM_BUFFER_S stMemBuf;

    if (HI_NULL == pchan || HI_NULL == puser_buf || 0 == puser_buf->buffer_len)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

    ret = channel_delete_addr_table(pchan, puser_buf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call channel_delete_addr_table failed!\n", __func__);
    }

    stMemBuf.u8IsSecure      = puser_buf->is_secure;
    stMemBuf.u32StartPhyAddr = puser_buf->phyaddr;
    stMemBuf.pStartVirAddr   = (HI_VOID *)puser_buf->kerneladdr;
    stMemBuf.u32Size         = puser_buf->buffer_len;

    ret = VDEC_MEM_CloseAndFree(&stMemBuf, &puser_buf->share_fd);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call DRV_MEM_FreeUserBuffer failed\n", __func__);
        return HI_FAILURE;
    }

	return HI_SUCCESS;
}

HI_S32 channel_bind_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
	HI_S32 ret = HI_FAILURE;

	if (HI_NULL == pchan || HI_NULL == puser_buf || 0 == puser_buf->phyaddr)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
		return HI_FAILURE;
	}

	ret = channel_insert_addr_table(pchan, puser_buf);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s call channel_insert_addr_table failed!\n", __func__);
		return HI_FAILURE;
	}

	/*in order to deal with when using android_native_buffer, the stride is not match!*/
	if (pchan->out_stride != puser_buf->out_frame.stride)
	{
		pchan->out_stride = puser_buf->out_frame.stride;
	}

	return HI_SUCCESS;
}

HI_S32 channel_unbind_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
	HI_S32 ret = HI_FAILURE;

    if (HI_NULL == pchan || HI_NULL == puser_buf || 0 == puser_buf->phyaddr)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

	ret = channel_delete_addr_table(pchan, puser_buf);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call channel_delete_addr_table failed!\n", __func__);
		return HI_FAILURE;
	}

	return HI_SUCCESS;
}

HI_S32 channel_empty_this_stream(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
	unsigned long  flags;
	HI_S32         ret     = HI_FAILURE;
	OMXVDEC_BUF_S *pstream = HI_NULL;

	if (HI_NULL == pchan || HI_NULL == puser_buf)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
    	return HI_FAILURE;
	}

    // only process buffer with valid data len
    if (puser_buf->data_len != 0)
    {
    	pstream = channel_lookup_addr_table(pchan, puser_buf);
    	if (HI_NULL == pstream)
        {
            OmxPrint(OMX_ERR, "%s call channel_lookup_addr_table failed!\n", __func__);
	        message_queue(pchan->msg_queue, VDEC_MSG_RESP_INPUT_DONE, VDEC_ERR_ILLEGAL_OP, (HI_VOID *)puser_buf);
    	    return HI_FAILURE;
    	}

        pstream->act_len    = puser_buf->data_len;
        pstream->offset     = puser_buf->data_offset;
        pstream->time_stamp = puser_buf->timestamp;
        pstream->flags      = puser_buf->flags;

        /* save raw process*/
        if (HI_TRUE == pchan->is_tvp)
        {
            //:TODO: add save secure stream method 
        }
        else
        {
            channel_save_stream(pchan, pstream);
        }

        ret = channel_insert_in_raw_list(pchan, pstream);
        if (ret != HI_SUCCESS)
        {
	        message_queue(pchan->msg_queue, VDEC_MSG_RESP_INPUT_DONE, VDEC_ERR_ILLEGAL_OP, (HI_VOID *)puser_buf);
    	    return HI_FAILURE;
        }
    }

	if (puser_buf->flags & VDEC_BUFFERFLAG_EOS)
    {
        OmxPrint(OMX_INFO, "%s receive EOS flag!\n", __func__);
		if (0 == pchan->eos_in_list)
		{
	        pstream = &pchan->last_frame;
	        ret = channel_add_last_frame(pchan, pstream);
	        if (ret != HI_SUCCESS)
	        {
	           OmxPrint(OMX_ERR, "Chan(%d) send last frame failed!\n", pchan->channel_id);
	        }
	        else
	        {
	           pstream->status = BUF_STATE_QUEUED;
	           spin_lock_irqsave(&pchan->raw_lock, flags);
	           list_add_tail(&pstream->list, &pchan->raw_queue);
	           spin_unlock_irqrestore(&pchan->raw_lock, flags);
	           pchan->eos_in_list = 1;
	        }
	    }
		else
		{
	        OmxPrint(OMX_ERR, "Chan(%d) eos already in list!\n", pchan->channel_id);
		}
        pchan->eos_recv_flag++;
	}

    if (0 == puser_buf->data_len)
    {
        OmxPrint(OMX_WARN, "%s receive an empty buffer, return immediately.\n", __func__);
	    message_queue(pchan->msg_queue, VDEC_MSG_RESP_INPUT_DONE, VDEC_S_SUCCESS, (HI_VOID *)puser_buf);
    }

	return HI_SUCCESS;
}

HI_S32 channel_fill_this_frame(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf)
{
	HI_S32         ret    = HI_FAILURE;
	OMXVDEC_BUF_S *pframe = HI_NULL;

	if (HI_NULL == pchan || HI_NULL == puser_buf)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
		return HI_FAILURE;
	}

	pframe = channel_lookup_addr_table(pchan, puser_buf);
	if (HI_NULL == pframe)
    {
        OmxPrint(OMX_ERR, "%s call channel_lookup_addr_table failed!\n", __func__);
        message_queue(pchan->msg_queue, VDEC_MSG_RESP_OUTPUT_DONE, VDEC_ERR_ILLEGAL_OP, (HI_VOID *)puser_buf);
        return HI_FAILURE;
	}

	pframe->offset	= puser_buf->data_offset;
	pframe->act_len	= 0;

    ret = channel_insert_in_yuv_list(pchan, pframe);
    if (ret != HI_SUCCESS)
    {
        message_queue(pchan->msg_queue, VDEC_MSG_RESP_OUTPUT_DONE, VDEC_ERR_ILLEGAL_OP, (HI_VOID *)puser_buf);
	    return HI_FAILURE;
    }

	if (pframe->ext_info.PP_EXT.image_id != 0)
	{
    	processor_ctrl_inst(pchan, PP_CMD_RELEASE_IMAGE, (HI_VOID *)pframe);
        pframe->ext_info.PP_EXT.image_id = 0;
	}

    if (DFS_WAIT_FILL == pchan->dfs_alloc_flag)
    {
        OmxPrint(OMX_INFO, "First filled, wake up task to activate chan.\n");
        pchan->dfs_alloc_flag = DFS_WAIT_ACTIVATE;
        ret = channel_activate_inst(pchan);
		if (ret != HI_SUCCESS)
	    {
	        OmxPrint(OMX_ERR, "%s activate inst failed!\n", __func__);
            message_queue(pchan->msg_queue, VDEC_ERR_DYNAMIC_ALLOC_FAIL, HI_FAILURE, NULL);
		}
        else
        {
            pchan->dfs_alloc_flag = DFS_ALREADY_ALLOC;
        }
    }

	if (pchan->last_frame_state == LAST_FRAME_WAIT_SLOT)
	{
    	processor_ctrl_inst(pchan, PP_CMD_REPORT_LAST_FRAME, HI_NULL);
	}

	return HI_SUCCESS;
}

HI_S32 channel_flush_in_port(OMXVDEC_CHAN_CTX *pchan)
{
	unsigned long flags;
	OMXVDEC_BUF_S *pbuf = HI_NULL;
	OMXVDEC_BUF_S *ptmp = HI_NULL;
	OMXVDEC_BUF_DESC user_buf;
    memset(&user_buf, 0, sizeof(OMXVDEC_BUF_DESC));

	pbuf = ptmp = HI_NULL;

    spin_lock_irqsave(&pchan->raw_lock, flags);
    list_for_each_entry_safe(pbuf, ptmp, &pchan->raw_queue, list)
    {
        if (BUF_STATE_USING == pbuf->status)
        {
            continue;
        }

        pbuf->status = BUF_STATE_IDLE;
        list_del(&pbuf->list);

        if (pbuf->buf_id != LAST_FRAME_BUF_ID)
        {
            user_buf.dir = PORT_DIR_INPUT;
            user_buf.bufferaddr = pbuf->user_vaddr;
            user_buf.buffer_len =  pbuf->buf_len;
            user_buf.client_data = pbuf->client_data;

            user_buf.data_len = 0;
            user_buf.timestamp = 0;

            pbuf->act_len = user_buf.data_len;
            message_queue(pchan->msg_queue, VDEC_MSG_RESP_INPUT_DONE, VDEC_S_SUCCESS, (void *)&user_buf);
            OmxPrint(OMX_OUTBUF, "Release Idle In Buffer: phy addr = 0x%08x\n", pbuf->phy_addr);
        }
        else
        {
            pchan->eos_in_list = 0;
        }
	}

    if (pchan->raw_use_cnt > 0)
    {
        pchan->input_flush_pending = 1;
    }
    else
    {
        message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_INPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
    }

	spin_unlock_irqrestore(&pchan->raw_lock, flags);

    if (pchan->input_flush_pending)
    {
        OmxPrint(OMX_INBUF, "Call vfmw to release input buffers.\n");
        decoder_ctrl_inst(pchan, DEC_CMD_CLEAR_STREAM, HI_NULL); // call decoder to return all es buffer
    }

	return HI_SUCCESS;
}

HI_S32 channel_flush_out_port(OMXVDEC_CHAN_CTX *pchan)
{
    unsigned long flags;
    OMXVDEC_BUF_S *pbuf = HI_NULL;
    OMXVDEC_BUF_S *ptmp = HI_NULL;
    OMXVDEC_BUF_DESC user_buf;

    if (1 == pchan->recfg_flag) // flush command called by resolution change
    {
        OmxPrint(OMX_INFO, "Wait for output with no clear.\n");
        pchan->recfg_flag = 0;
    }
    else // flush command called by seek or quit
    {
        OmxPrint(OMX_INFO, "Call to clear remain pictures.\n");
        channel_reset_inst(pchan);  // reset channel to clear old image
        pchan->seek_pending = 1;
    }

    memset(&user_buf, 0, sizeof(OMXVDEC_BUF_DESC));

    pbuf = ptmp = HI_NULL;

    spin_lock_irqsave(&pchan->yuv_lock, flags);
    list_for_each_entry_safe(pbuf, ptmp, &pchan->yuv_queue, list)
    {
        if (BUF_STATE_USING == pbuf->status)
        {
            continue;
        }

        user_buf.dir          = PORT_DIR_OUTPUT;
        user_buf.bufferaddr   = pbuf->user_vaddr;
        user_buf.buffer_len   = pbuf->buf_len;
        user_buf.client_data  = pbuf->client_data;
        user_buf.flags        = 0;
        user_buf.data_len     = 0;
        user_buf.timestamp    = 0;

        pbuf->status = BUF_STATE_IDLE;
        list_del(&pbuf->list);
        
        channel_sync_frame_buffer(pchan, pbuf->phy_addr, EXTBUF_NOT_READY);

        message_queue(pchan->msg_queue, VDEC_MSG_RESP_OUTPUT_DONE, VDEC_S_SUCCESS, (HI_VOID *)&user_buf);
        OmxPrint(OMX_OUTBUF, "Release Idle Out Buffer: phy addr = 0x%08x\n", pbuf->phy_addr);
    }

	if (pchan->yuv_use_cnt > 0)
    {
		pchan->output_flush_pending = 1;
    }
	else
    {
		message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_OUTPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
	}
    spin_unlock_irqrestore(&pchan->yuv_lock, flags);

    return HI_SUCCESS;
}

HI_S32 channel_flush_inst(OMXVDEC_CHAN_CTX *pchan, ePORT_DIR dir)
{
    HI_S32 ret_in  = HI_SUCCESS;
    HI_S32 ret_out = HI_SUCCESS;

	if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
	}

    if ((PORT_DIR_INPUT == dir) || (PORT_DIR_BOTH == dir))
    {
        ret_in = channel_flush_in_port(pchan);
        if (ret_in != HI_SUCCESS)
        {
            OmxPrint(OMX_ERR, "channel_flush_in_port failed!\n");
        }
    }

    if ((PORT_DIR_OUTPUT == dir) || (PORT_DIR_BOTH == dir))
    {
        ret_out = channel_flush_out_port(pchan);
        if (ret_out != HI_SUCCESS)
        {
            OmxPrint(OMX_ERR, "channel_flush_out_port failed!\n");
        }
    }
    
    channel_clear_buf_ext_info(pchan, dir);

    return (ret_in | ret_out);
}

HI_S32 channel_clear_buf_ext_info(OMXVDEC_CHAN_CTX* pchan, ePORT_DIR dir)
{
    HI_U32 i;
    unsigned long flags;
	OMXVDEC_BUF_S *buf_addr_table = HI_NULL;

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_ERR, "%s pchan = NULL\n", __func__);
        return HI_FAILURE;
    }
    
    /* Clear input buffer record ext info */
    if ((PORT_DIR_INPUT == dir) || (PORT_DIR_BOTH == dir))
    {
        spin_lock_irqsave(&pchan->raw_lock, flags);
        buf_addr_table = (OMXVDEC_BUF_S *)pchan->in_buf_table;
        for (i=0; i<MAX_BUFFER_SLOT_NUM; i++)
        {
            memset(&buf_addr_table[i].ext_info, 0, sizeof(EXT_INFO));
        }
        spin_unlock_irqrestore(&pchan->raw_lock, flags);
    }
    
    /* Clear output buffer record ext info */
    if ((PORT_DIR_OUTPUT == dir) || (PORT_DIR_BOTH == dir))
    {
        spin_lock_irqsave(&pchan->yuv_lock, flags);
        buf_addr_table = (OMXVDEC_BUF_S *)pchan->out_buf_table;
        for (i=0; i<MAX_BUFFER_SLOT_NUM; i++)
        {
            memset(&buf_addr_table[i].ext_info, 0, sizeof(EXT_INFO));
        }
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
    }

    return HI_SUCCESS;
}

HI_S32 channel_bind_mem_to_inst(OMXVDEC_CHAN_CTX* pchan)
{
    HI_S32  i   = 0;
    HI_S32  ret = HI_SUCCESS;
    HI_U32  total_pmv_size = 0;
    HI_CHAR buf_name[20];
    OMXVDEC_BUF_S *buf_addr_table = NULL;
    VDEC_CHAN_FRAME_STORES stFsParam;

    memset(&stFsParam, 0, sizeof(stFsParam));

    /* Get output buffer table */
    buf_addr_table = (OMXVDEC_BUF_S *)pchan->out_buf_table;
    if(HI_NULL == buf_addr_table)
    {
        OmxPrint(OMX_FATAL, "%s, buf_addr_table = NULL!\n", __func__);
		return HI_FAILURE;
    }

    total_pmv_size = pchan->output_buf_num * pchan->ref_pmv_size;
    
    /* Check if need to realloc pmv buffer */
    if (pchan->decoder_vdh_buf.u32Size != total_pmv_size)
    {
        /* Allocate pmv buffer here */
        if (pchan->decoder_vdh_buf.u32Size != 0)
        {
            omxvdec_release_mem(&pchan->decoder_vdh_buf);
        }
                
        pchan->decoder_vdh_buf.u8IsSecure = (HI_TRUE==pchan->is_tvp)? 1 : 0;
        pchan->decoder_vdh_buf.u32Size    = pchan->output_buf_num * pchan->ref_pmv_size;
        snprintf(buf_name, sizeof(buf_name), "Chan%d_PMV", pchan->channel_id);
        ret = VDEC_MEM_AllocAndMap(buf_name, OMXVDEC_ZONE, &pchan->decoder_vdh_buf);
        if(ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s alloc pmv mem(size = %d) failed!\n", __func__, pchan->decoder_vdh_buf.u32Size);
            return HI_FAILURE;
        }
    }

    /* Record allocated buffer message */
	stFsParam.TotalFrameNum = pchan->output_buf_num;
    for(i=0; i<pchan->output_buf_num; i++)
    {
        //Frame buffer info
        stFsParam.stFrameBuf[i].PhyAddr = buf_addr_table[i].phy_addr;
        stFsParam.stFrameBuf[i].VirAddr = buf_addr_table[i].kern_vaddr;
        stFsParam.stFrameBuf[i].Length  = buf_addr_table[i].buf_len;
        //Pmv buffer info
        stFsParam.stPmvBuf[i].PhyAddr   = pchan->decoder_vdh_buf.u32StartPhyAddr + i*pchan->ref_pmv_size;
        stFsParam.stPmvBuf[i].VirAddr   = (HI_U8 *)pchan->decoder_vdh_buf.pStartVirAddr + i*pchan->ref_pmv_size;
        stFsParam.stPmvBuf[i].Length    = pchan->ref_pmv_size;
    }
    
    /* Bind buffer to decoder */
    ret = decoder_ctrl_inst(pchan, DEC_CMD_BIND_MEM, (HI_VOID*)&stFsParam);
    if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "channel bind mem to inst failed!\n");
        omxvdec_release_mem(&pchan->decoder_vdh_buf);
		return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 channel_activate_inst(OMXVDEC_CHAN_CTX* pchan)
{
    HI_S32  ret = HI_SUCCESS;
    HI_U32  u32DoneTime = 0;

    ret = decoder_ctrl_inst(pchan, DEC_CMD_ACTIVATE_INST, HI_NULL);
    if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "channel activate inst failed!\n");
		return HI_FAILURE;
    }

    VDEC_SYS_GetTimeStampMs(&u32DoneTime);
    pchan->dfs_delay_time = u32DoneTime - pchan->dfs_delay_time;

    return ret;
}

HI_S32 channel_get_message(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_MSG_INFO *pmsg)
{
	if (HI_NULL == pchan || HI_NULL == pmsg)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
	}

	return message_dequeue(pchan->msg_queue, pmsg);
}

HI_S32 channel_check_avaible_frame_buffer(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;
	unsigned long flags;
	OMXVDEC_BUF_S *pbuf = HI_NULL;

	spin_lock_irqsave(&pchan->yuv_lock, flags);

	list_for_each_entry(pbuf, &pchan->yuv_queue, list)
	{
        if (pbuf->status == BUF_STATE_QUEUED)
        {
            ret = HI_SUCCESS;
            break;
        }
	}

	spin_unlock_irqrestore(&pchan->yuv_lock, flags);

    return ret;
}

HI_VOID channel_sync_frame_buffer(OMXVDEC_CHAN_CTX *pchan, HI_U32 phy_addr, EXTBUF_STATE_E state)
{
    EXTBUF_PARAM_S param;

    if (HI_FALSE == pchan->is_tvp)
    {
        return;
    }

    param.State   = state;
    param.PhyAddr = phy_addr;
    
    decoder_ctrl_inst(pchan, DEC_CMD_SYNC_EXT_BUF, &param);

    return;
}

OMXVDEC_CHAN_CTX* channel_find_inst_by_channel_id(OMXVDEC_ENTRY *omxvdec, HI_S32 handle)
{
    HI_S8 find = 0;
	OMXVDEC_CHAN_CTX *pchan = HI_NULL;
	unsigned long flags;

	if (HI_NULL == omxvdec || handle < 0)
    {
        OmxPrint(OMX_FATAL, "%s: omxvdec = NULL / handle(%d) invalid\n", __func__, handle);
        return HI_NULL;
    }

	spin_lock_irqsave(&omxvdec->channel_lock, flags);
	if (!list_empty(&omxvdec->chan_list))
    {
        list_for_each_entry(pchan, &omxvdec->chan_list, chan_list)
        {
            if(pchan->channel_id == handle)
            {
                find = 1;
                break;
            }
        }
    }
	spin_unlock_irqrestore(&omxvdec->channel_lock, flags);

    if (0 == find)
    {
        pchan = HI_NULL;
    }

	return pchan;
}

OMXVDEC_CHAN_CTX* channel_find_inst_by_decoder_id(OMXVDEC_ENTRY *omxvdec, HI_S32 handle)
{
    HI_S8 find = 0;
	OMXVDEC_CHAN_CTX *pchan = HI_NULL;
	unsigned long flags;

	if (HI_NULL == omxvdec || handle < 0)
    {
        OmxPrint(OMX_FATAL, "%s: omxvdec = NULL / handle(%d) invalid\n", __func__, handle);
        return HI_NULL;
    }

	spin_lock_irqsave(&omxvdec->channel_lock, flags);
	if (!list_empty(&omxvdec->chan_list))
    {
        list_for_each_entry(pchan, &omxvdec->chan_list, chan_list)
        {
            if(pchan->decoder_id == handle)
            {
                find = 1;
                break;
            }
        }
    }
	spin_unlock_irqrestore(&omxvdec->channel_lock, flags);

    if (0 == find)
    {
        pchan = HI_NULL;
    }

	return pchan;
}

OMXVDEC_CHAN_CTX* channel_find_inst_by_processor_id(OMXVDEC_ENTRY *omxvdec, HI_S32 handle)
{
    HI_S8 find = 0;
	unsigned long flags;
	OMXVDEC_CHAN_CTX *pchan = HI_NULL;

	if (HI_NULL == omxvdec || handle < 0)
    {
        OmxPrint(OMX_FATAL, "%s: omxvdec = NULL / handle(%d) invalid\n", __func__, handle);
        return HI_NULL;
    }

	spin_lock_irqsave(&omxvdec->channel_lock, flags);
	if (!list_empty(&omxvdec->chan_list))
    {
        list_for_each_entry(pchan, &omxvdec->chan_list, chan_list)
        {
            if(pchan->processor_id == handle)
            {
                find = 1;
                break;
            }
        }
    }
	spin_unlock_irqrestore(&omxvdec->channel_lock, flags);

    if (0 == find)
    {
        pchan = HI_NULL;
    }

	return pchan;
}

OMXVDEC_CHAN_CTX* channel_find_inst_need_wake_up(OMXVDEC_ENTRY *omxvdec)
{
    HI_S8 find = 0;
	unsigned long flags;
	OMXVDEC_CHAN_CTX *pchan = HI_NULL;

	if (HI_NULL == omxvdec)
    {
        OmxPrint(OMX_FATAL, "%s: vdec = NULL, invalid\n", __func__);
        return HI_NULL;
    }

	spin_lock_irqsave(&omxvdec->channel_lock, flags);
	if (!list_empty(&omxvdec->chan_list))
    {
        list_for_each_entry(pchan, &omxvdec->chan_list, chan_list)
        {
            if(DFS_WAIT_ALLOC == pchan->dfs_alloc_flag)
            {
                find = 1;
                break;
            }
        }
    }
	spin_unlock_irqrestore(&omxvdec->channel_lock, flags);

    if (0 == find)
    {
        pchan = HI_NULL;
    }

	return pchan;
}

HI_S32 channel_dynamic_freq_sel(OMXVDEC_CHAN_CTX *pchan)
{
    struct device *dev     = NULL;
    HI_U32 chan_num = 0;
    HI_U32 width    = 0;
    HI_U32 height   = 0;
    HI_S32 ret      = 0;

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "Invalid param pChannel = NULL [%s]\n", __func__);
        return HI_FAILURE;
    }

    dev = pchan->vdec->device;
    if (HI_NULL == dev)
    {
        OmxPrint(OMX_ERR, "Invalid dev = NULL [%s]\n", __func__);
        return HI_FAILURE;
    }
    
    chan_num = pchan->vdec->total_chan_num;
    width    = pchan->out_width;
    height   = pchan->out_height;

    // Set to high frequency when resolution or chan num reach threshold
    if (width * height > RESOLUTION_THRESHOLD
     || chan_num > INST_NUM_THRESHOLD)
    {               
        ret = VDEC_Regulator_SetClkRate(dev, CLK_RATE_HIGH);
        if (ret != HI_SUCCESS) 
        {
            OmxPrint(OMX_ERR, "%s: VDEC_Regulator_SetClkRate high failed!\n", __func__);
            return HI_FAILURE;
        }
    }
    else
    {  
        ret = VDEC_Regulator_SetClkRate(dev, CLK_RATE_LOW);
        if (ret != HI_SUCCESS) 
        {
            OmxPrint(OMX_ERR, "%s: VDEC_Regulator_SetClkRate low failed!\n", __func__);
            return HI_FAILURE;
        }
    }
   
    return HI_SUCCESS;
}

HI_VOID channel_proc_entry(struct seq_file *p, OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 i;
    OMXVDEC_BUF_S *pVdecBufTable = HI_NULL;

    PROC_PRINT(p, "--------------- INST%2d --------------\n",   pchan->channel_id);
    PROC_PRINT(p, "%-20s :%s\n",    "State",        channel_show_chan_state(pchan->channel_state));
    PROC_PRINT(p, "%-20s :%d\n",    "IsTvp",        pchan->is_tvp);
    PROC_PRINT(p, "%-20s :%s\n",    "Protocol",     channel_show_protocol(pchan->protocol));
    PROC_PRINT(p, "%-20s :%dx%d\n", "Resolution",   pchan->out_width, pchan->out_height);
    PROC_PRINT(p, "%-20s :%d\n",    "Stride",       pchan->out_stride);
    PROC_PRINT(p, "%-20s :%s\n",    "ColorFormat",  channel_show_color_format(pchan->color_format));
    PROC_PRINT(p, "%-20s :%d\n",    "EosFlag",      pchan->eos_recv_flag);
    PROC_PRINT(p, "%-20s :%d\n",    "EosInList",    pchan->eos_in_list);
    PROC_PRINT(p, "%-20s :%d\n",    "EofFlag",      pchan->eof_send_flag);
    PROC_PRINT(p, "%-20s :%s\n",    "DfsState",     channel_show_dfs_state(pchan->dfs_alloc_flag));

    if (DFS_ALREADY_ALLOC == pchan->dfs_alloc_flag)
    {
    PROC_PRINT(p, "%-20s :%dms\n",  "DelayTime",    pchan->dfs_delay_time);
    }
    PROC_PRINT(p, "\n");

    decoder_proc_entry(pchan, p);
    processor_proc_entry(pchan, p);

    PROC_PRINT(p, "%-10s :%d/%d\n", "In Buffer",    pchan->input_buf_num, pchan->max_in_buf_num);
    PROC_PRINT(p, " %-10s%-10s%-10s%-10s\n", "phyaddr", "size", "fill", "status");

    pVdecBufTable = (OMXVDEC_BUF_S *)pchan->in_buf_table;
    for (i=0; i<pchan->input_buf_num; i++)
    {
       PROC_PRINT(p, " %-10x%-10d%-10d%-10s\n",
                     pVdecBufTable[i].phy_addr,
                     pVdecBufTable[i].buf_len,
                     pVdecBufTable[i].act_len,
                     channel_show_buffer_state(pVdecBufTable[i].status));
    }
    PROC_PRINT(p, "\n");

    PROC_PRINT(p, "%-10s :%d/%d\n", "Out Buffer",   pchan->output_buf_num, pchan->max_out_buf_num);
    PROC_PRINT(p, " %-10s%-10s%-10s%-10s\n", "phyaddr", "size", "fill", "status");
    pVdecBufTable = (OMXVDEC_BUF_S *)pchan->out_buf_table;
    for (i=0; i<pchan->output_buf_num; i++)
    {
       PROC_PRINT(p, " %-10x%-10d%-10d%-10s\n",
                     pVdecBufTable[i].phy_addr,
                     pVdecBufTable[i].buf_len,
                     pVdecBufTable[i].act_len,
                     channel_show_buffer_state(pVdecBufTable[i].status));
    }
    PROC_PRINT(p, "\n");
    PROC_PRINT(p, "-------------------------------------\n");
}

