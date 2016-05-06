
     
#include "task.h"
#include "channel.h"
#include "decoder.h"
#include "processor.h"

/*================ EXTERN VALUE ================*/
extern HI_U32   g_DispNum;
extern HI_U32   g_NativeCancelNum;


/*============== INTERNAL FUNCTION =============*/
static inline const HI_PCHAR task_show_state(eTASK_STATE state)
{
	switch (state)
    {
       case TASK_STATE_INVALID:
            return "invalid";
            break;
    
       case TASK_STATE_SLEEPING:
            return "sleeping";
            break;
    
       case TASK_STATE_ONCALL:
            return "oncall";
            break;
            
       case TASK_STATE_RUNNING:
            return "running";
            break;
    
       default:
            return "unkown";
            break;
	}
}

static HI_S32 task_report_channel_mem(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret;
    
    pchan->out_width  = pchan->report_width;
    pchan->out_height = pchan->report_height;
    pchan->out_stride = pchan->report_stride;
    
    /* Dynamic select vcodec freq */
    if (HI_FAILURE == channel_dynamic_freq_sel(pchan))
    {
        OmxPrint(OMX_ERR, "%s select vcodec freq failed\n", __func__);
    }
    
	pchan->dfs_alloc_flag = DFS_WAIT_CLEAR;
    
    ret = processor_ctrl_inst(pchan, PP_CMD_THREAD_WAKE_UP, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s call processor_ctrl_inst failed\n", __func__);
        return HI_FAILURE;
    }

	return HI_SUCCESS;
}

static HI_S32 task_info_channel_mem(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;
    
    pchan->dfs_alloc_flag = DFS_WAIT_BIND;
    
    ret = channel_bind_mem_to_inst(pchan);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s bind mem to inst failed!\n", __func__);
        message_queue(pchan->msg_queue, VDEC_ERR_DYNAMIC_ALLOC_FAIL, HI_FAILURE, NULL);
        return ret;
	}
    
    pchan->dfs_alloc_flag = DFS_WAIT_ACTIVATE;
    
    ret = channel_activate_inst(pchan);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s activate inst failed!\n", __func__);
        message_queue(pchan->msg_queue, VDEC_ERR_DYNAMIC_ALLOC_FAIL, HI_FAILURE, NULL);
        return ret;
	}
    
    pchan->dfs_alloc_flag = DFS_ALREADY_ALLOC;

    return HI_SUCCESS;
}

static HI_S32 task_memory_manager(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 new_buf_num = pchan->ref_frame_num + g_DispNum + g_NativeCancelNum;

    if (pchan->out_width      != pchan->report_width
     || pchan->out_height     != pchan->report_height
     || pchan->out_stride     != pchan->report_stride
     || pchan->output_buf_num  < new_buf_num
     || pchan->output_buf_size < pchan->ref_frame_size)
    {
        OmxPrint(OMX_INFO, "REPORT_DEC_SIZE_CHG: width(%d->%d), height(%d->%d), stride=(%d->%d), frame_num(%d->%d), frame_size(%d->%d)\n",
                 pchan->out_width, pchan->report_width, pchan->out_height, pchan->report_height, pchan->out_stride, pchan->report_stride, pchan->output_buf_num, new_buf_num, pchan->output_buf_size, pchan->ref_frame_size);
        
        ret = task_report_channel_mem(pchan);
        
    }
    else
    {
        OmxPrint(OMX_INFO, "No need to REPORT_DEC_SIZE_CHG: width(%d), height(%d), stride=(%d), frame_num(%d, %d), frame_size(%d, %d)\n",
                 pchan->out_width, pchan->out_height, pchan->out_stride, pchan->output_buf_num, new_buf_num, pchan->output_buf_size, pchan->ref_frame_size);
        ret = task_info_channel_mem(pchan);
    }

    return ret; 
}


HI_S32 task_func_entry(HI_VOID* param)
{
    HI_S32            ret     = HI_SUCCESS;
    OMXVDEC_CHAN_CTX *pchan   = HI_NULL;
    OMXVDEC_ENTRY    *omxvdec = (OMXVDEC_ENTRY*)param;
    OMXVDEC_TASK     *task    = &(omxvdec->task);
    
    while(!kthread_should_stop())
    {
        task->task_state = TASK_STATE_SLEEPING;
        ret = wait_event_timeout(task->task_wait, (TASK_STATE_ONCALL == task->task_state), msecs_to_jiffies(500)); 
        task->task_state = TASK_STATE_RUNNING;
        
        // if is not wake up by time out
        if (ret > 0)
        {
            do {
                pchan = HI_NULL;
                pchan = channel_find_inst_need_wake_up(omxvdec);
                if (HI_NULL == pchan)
                {
                    break;
                }
                
                ret = task_memory_manager(pchan);
                if (ret != HI_SUCCESS)
                {
                    OmxPrint(OMX_FATAL, "Mem manage for chan %d failed\n", pchan->channel_id);
                    message_queue(pchan->msg_queue, VDEC_ERR_DYNAMIC_ALLOC_FAIL, HI_FAILURE, NULL);
                    break;
                }
            }while(1);
        }
    }
    
    task->task_state = TASK_STATE_INVALID;
    
    return ret;
}


/*============== EXPORT FUNCTION =============*/
HI_S32 task_create_thread(OMXVDEC_ENTRY* omxvdec)
{
    OMXVDEC_TASK *task = HI_NULL;
    
    if (HI_NULL == omxvdec)
    {
        OmxPrint(OMX_FATAL, "%s ppTask = NULL!\n", __func__);
        return HI_FAILURE;
    }
    task = &(omxvdec->task);
    
    init_waitqueue_head(&task->task_wait);
    task->task_thread = kthread_create(task_func_entry, (HI_VOID *)omxvdec, "OmxVdecTask");

    if (HI_NULL == task->task_thread)
    {
        OmxPrint(OMX_FATAL, "%s create task failed!\n", __func__);
        return HI_FAILURE;
    }
    else if (IS_ERR(task->task_thread))
    {
        OmxPrint(OMX_FATAL, "%s create task failed, error no = %ld!\n", __func__, PTR_ERR(task->task_thread));
        task->task_thread = HI_NULL;
        return HI_FAILURE;
    }
    wake_up_process(task->task_thread);

    return HI_SUCCESS;
}

HI_S32 task_destroy_thread(OMXVDEC_ENTRY* omxvdec)
{
    OMXVDEC_TASK *task = HI_NULL;
    
    if (HI_NULL == omxvdec)
    {
        OmxPrint(OMX_FATAL, "%s omxvdec = NULL!\n", __func__);
        return HI_FAILURE;
    }
    task = &(omxvdec->task);
    
    if(task->task_thread != HI_NULL)
    {
        kthread_stop(task->task_thread);
        task->task_thread = HI_NULL;
    }
    
    return HI_SUCCESS;
}

HI_VOID task_proc_entry(struct seq_file *p, OMXVDEC_TASK *ptask)
{
    PROC_PRINT(p, "%-20s :%s\n", "TaskState",         task_show_state(ptask->task_state));
}


