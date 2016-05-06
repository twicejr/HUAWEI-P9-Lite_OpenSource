#ifndef _PWRCTRL_MCA_H
#define _PWRCTRL_MCA_H

#include <linux/hisi/pm/pwrctrl_multi_mca.h>

#define MCA_MAX_SESSION_NUM   (32)

typedef void (*mca_post_cb)(union mca_udata_rsp rsp, void* private_data);

extern void mca_init(void);
extern int mca_send(int cmd_id, union mca_udata_req req_data, union mca_udata_rsp* p_rsp_data, int time_out);
extern int mca_post(int cmd_id, union mca_udata_req req_data, mca_post_cb post_cb, void* private_data, int time_out);
extern int mca_inst(int cmd_id, union mca_udata_req req_data);

#endif
