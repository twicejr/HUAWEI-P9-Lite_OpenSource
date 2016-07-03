

#ifndef  __DSP_H__
#define  __DSP_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

struct dsp_pm_om_qos_log {
	unsigned int load_start;
	unsigned int load_end;
	unsigned int msp_store;
	unsigned int dpm_store;
	unsigned int dsp_store;
    unsigned int dsp_store_end;
	unsigned int poweroff;
	unsigned int poweron;
	unsigned int dpm_wait_store_ok;
	unsigned int dpm_restore;
    unsigned int dsp_restore;
	unsigned int msp_restore;
	unsigned int msp_restore_ok;
};


int dsp_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif   /* __DSP_H__ */

