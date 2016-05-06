

#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "channel.h"

typedef enum{
	PP_CMD_RELEASE_IMAGE = 0,
	PP_CMD_THREAD_WAKE_UP,
	PP_CMD_REPORT_LAST_FRAME,
	PP_CMD_IS_BUF_USABLE,
	PP_CMD_REPORT_BUF_OUT,
}PROCESSOR_CMD_E;

HI_S32  processor_init(HI_VOID);

HI_S32  processor_exit(HI_VOID);

HI_S32  processor_suspend(HI_VOID);

HI_S32  processor_resume(HI_VOID);

HI_S32  processor_create_inst(OMXVDEC_CHAN_CTX *pchan, HI_U32 color_format);

HI_S32  processor_release_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32  processor_start_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32  processor_stop_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32  processor_reset_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32  processor_ctrl_inst(OMXVDEC_CHAN_CTX *pchan, PROCESSOR_CMD_E eCmd, HI_VOID *pParam);

HI_VOID processor_proc_entry(OMXVDEC_CHAN_CTX *pchan, struct seq_file *p);

#endif

