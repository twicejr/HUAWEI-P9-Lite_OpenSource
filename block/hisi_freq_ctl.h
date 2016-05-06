#ifndef _BLOCK_HISI_FREQ_CRTL_H_
#define _BLOCK_HISI_FREQ_CRTL_H_

#define FREQ_REQ_ADD				1
#define FREQ_REQ_REMOVE				0

void hisi_blk_freq_request(int req_type, int time_in_queue);
void hisi_blk_freq_ctrl_init(void);

#endif
