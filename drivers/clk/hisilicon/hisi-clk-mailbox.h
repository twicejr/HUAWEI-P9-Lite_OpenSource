#ifndef __HISI_CLK_MAILBOX_H__
#define __HISI_CLK_MAILBOX_H__
#include <linux/hisi/hisi_mailbox.h>
#include <linux/completion.h>

#define	LPM3_CMD_LEN	2

#define AUTO_ACK		1
#define NO_AUTO_ACK		0

struct clk_mbox_context {
	struct completion complete;
	unsigned long freq;
};

int hisi_clkmbox_is_ready(void);
int hisi_clkmbox_send_msg(mbox_msg_t *msg);
int hisi_clkmbox_send_msg_sync(mbox_msg_t *msg);
#endif
