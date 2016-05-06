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

#define HISIAP_KEYS_MAX  39
struct hisiap_ringbuffer_s {
	u32 max_num;
	u32 field_count;
	u32 rear;
	u32 is_full;
	char keys[HISIAP_KEYS_MAX + 1];	/*For parsing with PC tools */
	u8 data[1];
};

int hisiap_ringbuffer_init(struct hisiap_ringbuffer_s *q, u32 bytes,
			   u32 fieldcnt, const char *keys);
void hisiap_ringbuffer_write(struct hisiap_ringbuffer_s *q, u8 *element);
