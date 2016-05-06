/*
 * record the data to rdr. (RDR: kernel run data recorder.)
 * This file wraps the ring buffer.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/string.h>

#include "rdr_hisi_ap_ringbuffer.h"

int hisiap_ringbuffer_init(struct hisiap_ringbuffer_s *q, u32 bytes,
			   u32 fieldcnt, const char *keys)
{
	if (bytes <
	    (sizeof(struct hisiap_ringbuffer_s) + sizeof(u8) * fieldcnt)) {
		printk(KERN_ERR "[%s], ringbuffer size [0x%x] is too short!\n",
		       __func__, bytes);
		return -EINVAL;
	}

	/* max_num: records count. */
	q->max_num = (bytes - sizeof(struct hisiap_ringbuffer_s)) /
	    (sizeof(u8) * fieldcnt);
	q->rear = 0;		/* point to the last NULL record. UNIT is record. */
	q->is_full = 0;
	q->field_count = fieldcnt;	/* How many u8 in ONE record. */
	strncpy(q->keys, keys, HISIAP_KEYS_MAX);	/*lint !e747 */
	return 0;
}

/*lint -e818 */
void hisiap_ringbuffer_write(struct hisiap_ringbuffer_s *q, u8 *element)
{
	int rear;

	if (q->rear >= q->max_num) {
		q->is_full = 1;
		q->rear = 0;
	}

/*lint -e713 */
	rear = q->rear++;
/*lint +e713 */

/*lint -e737 */
	memcpy((void *)&q->data[(long)rear * q->field_count],
	       (void *)element, q->field_count * sizeof(u8));
/*lint +e737 */
	return;
}

/*lint +e818 */
