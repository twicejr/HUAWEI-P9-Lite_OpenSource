#ifndef __DPM_BALONG_H__
#define __DPM_BALONG_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <osl_list.h>
#include <osl_types.h>
#include <osl_spinlock.h>

#ifndef OK
#define OK 0
#endif
#ifndef ERROR
#define ERROR (-1)
#endif

struct dpm_control
{
    struct list_head dpm_list;                      /*记录在dpm模块注册过的模块                 */
    struct list_head dpm_prepared_list;             /*记录已经prepare和resume_late过的模块                   */
    struct list_head dpm_sus_early_list;            /*记录已经suspend early和resume模块 */
    struct list_head dpm_suspend_list;              /*记录已经suspend和resume early的模块                 */
    struct list_head dpm_late_early_list;           /*记录已经suspend late模块 */
    spinlock_t    dpm_list_mtx;                     /*链表访问互斥信号量，两个链表用一个互斥信号量*/
    u32  dpm_count[DPM_CALLBACK_NUM];               /*0:pre failed,1:early,2:suspend failed,3:late failed,4:total suspend,5:total resume*/
    s32  (*current_callback)(struct dpm_device *dev);
    char *device_name;                              /*记录模块名字*/
    s32  flag;
};

extern u32 dpm_dump_drx_c_addr;

#define DPM_DUMP_START      (dpm_dump_drx_c_addr+CDRX_DUMP_DPM_OFFSET)
#define DPM_DUMP_SIZE       (CDRX_DUMP_DPM_SIZE)
#define DPM_CNT_RECORD_ADDR (DPM_DUMP_START)
#define DPM_STAMP_START     (DPM_CNT_RECORD_ADDR+0x10)

/*记录可维可测回调级别*/
enum dpm_stat_enum{
	PREPARE,
	SUS_EARLY,
	SUSPEND,
	LATE,
	EARLY,
	RESUME,
	RES_LATE,
	COMPLETE
};


/* ASCII define  */
enum dpm_ascii{
    /**/
    dpm_asc_dpm = 0x006D7064,/*  ASCII = "dpm " */
    dpm_asc_cnt = 0x00746E63,/*  ASCII = "cnt " */

    /* asc for dpm steps*/
    dpm_asc_sus_prepare  = 0x56727053,/*  ASCII = "Spre" */
    dpm_asc_sus_early    = 0x72616553,/*  ASCII = "Sear" */
    dpm_asc_sus_suspend  = 0x73757353,/*  ASCII = "Ssus" */
    dpm_asc_sus_late     = 0x74616C53,/*  ASCII = "Slat" */
    dpm_asc_res_early    = 0x72616552,/*  ASCII = "Rear" */
    dpm_asc_res_resume   = 0x76657252,/*  ASCII = "Sres" */
    dpm_asc_res_late     = 0x74616C52,/*  ASCII = "Slat" */
    dpm_asc_res_complete = 0x6D6F6352,/*  ASCII = "Scom" */
    
    dpm_asc_in           = 0x5F6E695F,/*  ASCII = "_in_" */
    dpm_asc_out          = 0x5F74756F,/*  ASCII = "out_" */
    dpm_asc_fail         = 0x6C696166,/*  ASCII = "fail" */
};


#endif
