

#ifndef __OMXVDEC_H__
#define __OMXVDEC_H__

#include "platform.h"
#include "drv_omxvdec.h"

#define MAX_OPEN_COUNT	                  (32)
#define MAX_CHANNEL_NUM                   (MAX_OPEN_COUNT)

#define OMX_ALWS                          (0xFFFFFFFF)
#define OMX_FATAL			              (0)
#define OMX_ERR			                  (1)
#define OMX_WARN			              (2)
#define OMX_INFO			              (3)
#define OMX_TRACE			              (4)
#define OMX_INBUF			              (5)
#define OMX_OUTBUF	 		       	      (6)
#define OMX_VPSS	 		              (7)
#define OMX_VER  	 		       	      (8)
#define OMX_PTS                           (9)
#define OMX_MEM                           (10)

extern HI_U32 g_TraceOption;

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define OmxPrint(flag, format,arg...) \
	do { \
		if (OMX_ALWS == flag || (0 != (g_TraceOption & (1 << flag)))) \
		    printk(KERN_ALERT format, ## arg); \
	} while (0)
#else
#define OmxPrint(flag, format,arg...)    ({do{}while(0);0;})
#endif

/* 
   g_TraceOption 常用值

   1:      OMX_FATAL
   2:      OMX_ERR
   4:      OMX_WARN
   8:      OMX_INFO      (用于查看创建配置项及跟踪最后一帧情况)
   16:     OMX_TRACE
   32:     OMX_INBUF
   64:     OMX_OUTBUF
   128:    OMX_VPSS      (用于跟踪图像不输出原因)
   256:    OMX_RAWCTRL   (用于等待MSG超时告警信息)
   512:    OMX_PTS       (用于查看输入输出PTS值)
   1024:   OMX_MEM       (用于查看内存申请释放信息)

   3:      OMX_FATAL & OMX_ERR
   7:      OMX_FATAL & OMX_ERR & OMX_WARN
   11:     OMX_FATAL & OMX_ERR & OMX_INFO
   19:     OMX_FATAL & OMX_ERR & OMX_TRACE
   96:     OMX_INBUF & OMX_OUTBUF
   35:     OMX_FATAL & OMX_ERR & OMX_INBUF
   67:     OMX_FATAL & OMX_ERR & OMX_OUTBUF
   99:     OMX_FATAL & OMX_ERR & OMX_INBUF & OMX_OUTBUF
   
*/

typedef enum {
	TASK_STATE_INVALID = 0,
	TASK_STATE_SLEEPING,
	TASK_STATE_ONCALL,
	TASK_STATE_RUNNING,
}eTASK_STATE;

typedef struct {
    eTASK_STATE         task_state;
	wait_queue_head_t   task_wait;
    struct task_struct *task_thread;
}OMXVDEC_TASK;

typedef struct {
	HI_U32              open_count;
	HI_U32              total_chan_num;
    OMXVDEC_TASK        task;
	struct list_head    chan_list;
    struct semaphore    omxvdec_mutex;
	spinlock_t          channel_lock;
	struct cdev         cdev;
	struct device      *device;
}OMXVDEC_ENTRY;

typedef struct {
  HI_VOID *pDecoderFunc; 	  /*decoder   external functions*/
  HI_VOID *pProcessorFunc; 	  /*processor external functions*/
}OMXVDEC_FUNC;


HI_VOID omxvdec_release_mem(MEM_BUFFER_S *pMMZ_Buf);

#endif

