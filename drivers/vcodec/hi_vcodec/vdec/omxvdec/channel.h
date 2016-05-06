

#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "omxvdec.h"
#include "message.h"
#include "vfmw.h"

// last frame report result
#define  REPORT_LAST_FRAME_SUCCESS   (0)
#define  REPORT_LAST_FRAME_FAIL      (1)
#define  REPORT_LAST_FRAME_WITH_ID   (2)

#define  MAX_BUFFER_SLOT_NUM         (32)

typedef enum {
	LAST_FRAME_INIT = 0,
	LAST_FRAME_DECODER_REPORT,
	LAST_FRAME_DECODER_FAILED,
	LAST_FRAME_PROCESSOR_GOT,
	LAST_FRAME_WAIT_SLOT,
}eLAST_FRAME_STATE;

typedef enum {
	CHAN_STATE_INVALID = 0,
	CHAN_STATE_IDLE,
	CHAN_STATE_WORK,
	CHAN_STATE_PAUSE,
	CHAN_STATE_PAUSE_PENDING,
}eCHAN_STATE;

typedef enum {
	BUF_STATE_INVALID = 0,
	BUF_STATE_IDLE,
	BUF_STATE_QUEUED,
	BUF_STATE_USING,
	BUF_STATE_WAIT_REPORT,
}eBUFFER_STATE;

typedef enum {
	DFS_INIT = 0,
	DFS_WAIT_ALLOC,
	DFS_WAIT_CLEAR,
	DFS_WAIT_INSERT,
	DFS_WAIT_BIND,
	DFS_WAIT_FILL,
	DFS_WAIT_ACTIVATE,
	DFS_ALREADY_ALLOC,
}eDFS_STATE;

typedef union {
	struct 
	{
		HI_U32 image_id;
	}PP_EXT;
}EXT_INFO;

typedef struct {
    
    eBUFFER_TYPE       buf_type;
	eBUFFER_STATE      status;
	HI_U32             phy_addr;
	HI_U32             buf_len;
	HI_U32             act_len;
	HI_U32             offset;
	HI_U32             flags;
	HI_U32             buf_id;
	EXT_INFO           ext_info;
	HI_S64             time_stamp;

	struct list_head   list;

	HI_VOID           *user_vaddr;
	HI_VOID           *kern_vaddr;
	HI_VOID           *client_data;

}OMXVDEC_BUF_S;
  
typedef struct {
    
	HI_S32             channel_id;
	HI_S32             decoder_id;
	HI_S32             processor_id;
	HI_U32             out_width;
	HI_U32             out_height;
	HI_U32             out_stride;
	HI_U32             color_format;
    HI_U32             pic_format;
    HI_U32             ref_frame_num;
    HI_U32             ref_frame_size;
    HI_U32             ref_pmv_size;
    HI_U32             report_width;
    HI_U32             report_height;
    HI_U32             report_stride;
    HI_U32             dfs_delay_time;
	HI_U32             input_buf_num;
	HI_U32             output_buf_num;
	HI_U32             output_buf_size;
	HI_U32             max_in_buf_num;
	HI_U32             max_out_buf_num;
	HI_U32             msg_queue_depth;
	HI_U32             raw_use_cnt;
	HI_U32             yuv_use_cnt;
	HI_U32             input_flush_pending:   1,
		               output_flush_pending:  1,
		               pause_pending:         1,
		               eos_in_list:           1,           // eos in list flag
		               eos_recv_flag:         1,           // end of stream flag
		               eof_send_flag:         1,           // last frame flag
		               recfg_flag:            1,           // reconfig flag
		               reset_pending:         1,           // reset flag
		               seek_pending:          1; 
    HI_U32             get_packet_num;
    HI_U32             dec_frame_num;
    HI_U32             out_frame_num;

    HI_BOOL            is_tvp;
    HI_U8              last_frame_processor_got;
    HI_U8              last_frame_image_id;
    HI_U64             file_dec;  
    
	OMXVDEC_CODEC_TYPE protocol;
    eLAST_FRAME_STATE  last_frame_state;
	eCHAN_STATE        channel_state;
	eDFS_STATE         dfs_alloc_flag;  
    
	OMXVDEC_BUF_S      in_buf_table[MAX_BUFFER_SLOT_NUM];
	OMXVDEC_BUF_S      out_buf_table[MAX_BUFFER_SLOT_NUM];
	msg_queue_s       *msg_queue;
	OMXVDEC_ENTRY     *vdec;
    struct file       *raw_file;

	struct list_head   chan_list;
	struct list_head   raw_queue;
	struct list_head   yuv_queue;
	OMXVDEC_BUF_S      last_frame;
    
    struct semaphore   chan_mutex;
	spinlock_t         raw_lock;
	spinlock_t         yuv_lock;

	IMAGE_INTF_S       image_ops;
                        
    MEM_BUFFER_S       decoder_ctx_buf;
    MEM_BUFFER_S       decoder_scd_buf;
    MEM_BUFFER_S       decoder_vdh_buf;
    MEM_BUFFER_S       decoder_eos_buf;
    MEM_BUFFER_S       channel_buf;
}OMXVDEC_CHAN_CTX;


HI_S32 channel_init(HI_VOID);

HI_VOID channel_exit(HI_VOID);

HI_S32 channel_suspend(HI_VOID);

HI_S32 channel_resume(HI_VOID);

HI_S32 channel_create_inst(struct file *fd, OMXVDEC_CHAN_CFG *pcfg);

HI_S32 channel_release_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 channel_start_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 channel_stop_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 channel_reset_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 channel_pause_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 channel_resume_inst(OMXVDEC_CHAN_CTX *pchan);
 
HI_S32 channel_bind_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf);

HI_S32 channel_unbind_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf);

HI_S32 channel_empty_this_stream(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf);
    
HI_S32 channel_fill_this_frame(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf);

HI_S32 channel_flush_inst(OMXVDEC_CHAN_CTX *pchan, ePORT_DIR dir);

HI_S32 channel_clear_buf_ext_info(OMXVDEC_CHAN_CTX* pchan, ePORT_DIR dir);

HI_S32 channel_bind_mem_to_inst(OMXVDEC_CHAN_CTX* pchan);

HI_S32 channel_activate_inst(OMXVDEC_CHAN_CTX* pchan);

HI_S32 channel_get_message(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_MSG_INFO *pmsg);

HI_S32 channel_check_avaible_frame_buffer(OMXVDEC_CHAN_CTX *pchan);

HI_VOID channel_sync_frame_buffer(OMXVDEC_CHAN_CTX *pchan, HI_U32 phy_addr, EXTBUF_STATE_E state);

OMXVDEC_CHAN_CTX* channel_find_inst_by_channel_id(OMXVDEC_ENTRY *vdec, HI_S32 handle);

OMXVDEC_CHAN_CTX* channel_find_inst_by_decoder_id(OMXVDEC_ENTRY *vdec, HI_S32 handle);

OMXVDEC_CHAN_CTX* channel_find_inst_by_processor_id(OMXVDEC_ENTRY *vdec, HI_S32 handle);

OMXVDEC_CHAN_CTX* channel_find_inst_need_wake_up(OMXVDEC_ENTRY *vdec);

HI_S32  channel_dynamic_freq_sel(OMXVDEC_CHAN_CTX *pchan);

HI_VOID channel_proc_entry(struct seq_file *p, OMXVDEC_CHAN_CTX *pchan);

HI_S32 channel_alloc_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf);

HI_S32 channel_free_user_buffer(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_BUF_DESC *puser_buf);

#endif
