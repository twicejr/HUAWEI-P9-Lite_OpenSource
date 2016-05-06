/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/
#ifndef _CMD_LIST_UTILS_H_
#define _CMD_LIST_UTILS_H_

#ifdef CONFIG_HISI_FB_3650
#include "hisi_overlay_utils_hi3650.h"
#endif

#ifdef CONFIG_HISI_FB_6250
#include "hisi_overlay_utils_hi6250.h"
#endif

#ifdef CONFIG_HISI_FB_3660
#include "hisi_overlay_utils_hi3660.h"
#endif


#define CONFIG_HISI_DSS_CMDLIST_LAST_USED

#define HISI_DSS_CMDLIST_MAX	(14)
#define HISI_DSS_CMDLIST_DATA_MAX	(3)
#define HISI_DSS_CMDLIST_NODE_MAX	(32)
#define HISI_DSS_CMDLIST_BLOCK_MAX	(32)

#define HISI_DSS_SUPPORT_DPP_MODULE_BIT(module)     (BIT(module) & HISI_DSS_DPP_MAX_SUPPORT_BIT)

enum dpp_module_idx {
	DPP_MODULE_POST_SCF = 0,
	DPP_MODULE_DBUF,
	DPP_MODULE_SBL,
	DPP_MODULE_ACM,
	DPP_MODULE_ACE,
	DPP_MODULE_LCP_IGM,
	DPP_MODULE_LCP_GMP,
	DPP_MODULE_LCP_XCC,
	DPP_MODULE_GAMA,
	DPP_MODULE_DITHER,
	DPP_MODULE_IFBC,
	DPP_MODULE_MAX
};

enum wb_type {
	WB_TYPE_WCH0,
	WB_TYPE_WCH1,
	WB_TYPE_WCH0_WCH1,

	WB_TYPE_MAX,
};

enum dss_cmdlist_idx {
	DSS_CMDLIST_NONE = -1,
	DSS_CMDLIST_D2 = 0,
	DSS_CMDLIST_D3,
	DSS_CMDLIST_V0,
	DSS_CMDLIST_G0,
	DSS_CMDLIST_V1,
	DSS_CMDLIST_G1,
	DSS_CMDLIST_D0,
	DSS_CMDLIST_D1,

	DSS_CMDLIST_W0,
	DSS_CMDLIST_W1,

	DSS_CMDLIST_OV0,
	DSS_CMDLIST_OV1,
	DSS_CMDLIST_OV2,
	DSS_CMDLIST_OV3,

	DSS_CMDLIST_MAX,
};


typedef union {
	struct {
		uint32_t exec:1;
		uint32_t last:1;
		uint32_t nop:1;
		uint32_t interrupt:1;
		uint32_t pending:1;
		uint32_t id:10;
		uint32_t event_list:6;
		uint32_t qos:1;
		uint32_t task_end:1;
		uint32_t reserved:1;
		uint32_t valid_flag:8; //0xA5 is valid
	} bits;
	uint32_t ul32;
} cmd_flag_t;

typedef union {
	struct {
		uint32_t count:14;
		uint32_t reserved:18;
	} bits;
	uint32_t ul32;
} total_items_t;

typedef union {
	struct {
		uint32_t add0:18;
		uint32_t add1:6;
		uint32_t add2:6;
		uint32_t cnt:2;
	} bits;
	uint32_t ul32;
} reg_addr_t;

typedef struct cmd_item {
	reg_addr_t reg_addr;
	uint32_t data0;
	uint32_t data1;
	uint32_t data2;
} cmd_item_t;

typedef struct cmd_header {
	cmd_flag_t flag;
	uint32_t next_list;
	total_items_t total_items;
	uint32_t list_addr; //128bit align
} cmd_header_t;

enum dss_cmdlist_node_valid {
	CMDLIST_NODE_INVALID = 0x0,
	CMDLIST_NODE_VALID = 0xA5,
};

enum dss_cmdlist_node_type {
	CMDLIST_NODE_NONE = 0x0,
	CMDLIST_NODE_NOP = 0x1,
	CMDLIST_NODE_FRAME = 0x2,
};

enum dss_cmdlist_status {
	e_status_idle = 0x0,
	e_status_wait = 0x1,
	e_status_other,
};

/*
** for normal node,all variable should be filled.
** for NOP node, just the list_header,header_ion_handle,list_node, node_flag should be filled.
** node_type must be CMDLIST_NODE_NOP when it is NOP node.
** And item_ion_handle in NOP node should be NULL.
*/
typedef struct dss_cmdlist_node {
	struct list_head list_node;

	struct ion_handle *header_ion_handle;
	ion_phys_addr_t header_phys;
	cmd_header_t *list_header;

	struct ion_handle *item_ion_handle;
	ion_phys_addr_t item_phys;
	cmd_item_t *list_item;

	uint32_t item_index;
	int item_flag;
	uint32_t node_type;
	int is_used;
	int reserved;
} dss_cmdlist_node_t;

typedef struct dss_cmdlist_heads {
	struct list_head cmdlist_head;

	dss_cmdlist_node_t *cmdlist_nodes[HISI_DSS_CMDLIST_NODE_MAX];
}dss_cmdlist_heads_t;

typedef struct dss_cmdlist_data {
	dss_cmdlist_heads_t *cmdlist_heads[HISI_DSS_CMDLIST_MAX];
	struct list_head cmdlist_head_temp[HISI_DSS_CMDLIST_MAX];
	dss_cmdlist_node_t *cmdlist_nodes_temp[HISI_DSS_CMDLIST_MAX][HISI_DSS_CMDLIST_NODE_MAX];
} dss_cmdlist_data_t;

typedef struct dss_cmdlist_info {
	struct semaphore cmdlist_wb_sem[2];  //for primary offline & copybit
	wait_queue_head_t cmdlist_wb_wq[WB_TYPE_MAX];
	uint32_t cmdlist_wb_done[WB_TYPE_MAX];
	uint32_t cmdlist_wb_flag[WB_TYPE_MAX];
} dss_cmdlist_info_t;


extern dss_cmdlist_data_t *g_cmdlist_data;


/******************************************************************************
** FUNCTIONS PROTOTYPES
*/
void hisi_cmdlist_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *addr, uint32_t value, uint8_t bw, uint8_t bs);
void hisi_cmdlist_flush_cache(struct hisi_fb_data_type *hisifd, struct ion_client *ion_client,
	uint32_t cmdlist_idxs);

dss_cmdlist_node_t* hisi_cmdlist_node_alloc(struct ion_client *ion_client);
void hisi_cmdlist_node_free(struct ion_client *ion_client, dss_cmdlist_node_t *node);

uint32_t hisi_cmdlist_get_cmdlist_need_start(struct hisi_fb_data_type *hisifd, uint32_t cmdlist_idxs);

int hisi_cmdlist_get_cmdlist_idxs(dss_overlay_t *pov_req, uint32_t *cmdlist_pre_idxs,
	uint32_t *cmdlist_idxs);
void hisi_cmdlist_data_get_online(struct hisi_fb_data_type *hisifd);
void hisi_cmdlist_data_get_offline(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);

int hisi_cmdlist_add_nop_node(struct hisi_fb_data_type *hisifd, uint32_t cmdlist_idxs, int pending, int reserved);
int hisi_cmdlist_add_new_node(struct hisi_fb_data_type *hisifd, uint32_t cmdlist_idxs, int pending,
	int task_end, int remove, int last, uint32_t wb_type);
int hisi_cmdlist_del_all_node(struct list_head *cmdlist_heads);

int hisi_cmdlist_config_start(struct hisi_fb_data_type *hisifd, int ovl_idx, uint32_t cmdlist_idxs, uint32_t wb_compose_type);
int hisi_cmdlist_config_stop(struct hisi_fb_data_type *hisifd, uint32_t cmdlist_idxs);
void hisi_cmdlist_config_reset(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, uint32_t cmdlist_idxs);

int hisi_cmdlist_del_node(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req, uint32_t cmdlist_idxs);
int hisi_cmdlist_check_rch_state(struct hisi_fb_data_type *hisifd, uint32_t cmdlist_idxs);

int hisi_cmdlist_exec(struct hisi_fb_data_type *hisifd, uint32_t cmdlist_idxs);
int hisi_cmdlist_dump_all_node (struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	uint32_t cmdlist_idxs);

int hisi_cmdlist_init(struct hisi_fb_data_type *hisifd);
int hisi_cmdlist_deinit(struct hisi_fb_data_type *hisifd);


#endif
