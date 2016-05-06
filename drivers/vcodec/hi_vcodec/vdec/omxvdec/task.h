

#ifndef __TASK_H__
#define __TASK_H__

#include "omxvdec.h"


HI_S32 task_create_thread(OMXVDEC_ENTRY* vdec);

HI_S32 task_destroy_thread(OMXVDEC_ENTRY* vdec);

HI_VOID task_proc_entry(struct seq_file *p, OMXVDEC_TASK *ptask);


#endif

