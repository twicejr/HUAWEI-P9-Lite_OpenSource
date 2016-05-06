/*
 * Implementation of the kernel access vector cache (AVC).
 *
 * Authors:  Stephen Smalley, <sds@epoch.ncsc.mil>
 *	     James Morris <jmorris@redhat.com>
 *
 * Update:   KaiGai, Kohei <kaigai@ak.jp.nec.com>
 *	Replaced the avc_lock spinlock by RCU.
 *
 * Copyright (C) 2003 Red Hat, Inc., James Morris <jmorris@redhat.com>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2,
 *	as published by the Free Software Foundation.
 */
#include <linux/types.h>
#include <linux/list.h>
#include <linux/audit.h>
#include <linux/lsm_audit.h>

#include <dsm/dsm_pub.h>

/*
 * We only need this data after we have decided to send an audit message.
 */
struct selinux_audit_data {
	u32 ssid;
	u32 tsid;
	u16 tclass;
	u32 requested;
	u32 audited;
	u32 denied;
	int result;
};

extern void audit_log_data(struct audit_buffer *ab, char **data);

extern void selinux_dsm_upload(struct audit_buffer *ab, struct common_audit_data *a);

extern int get_selinux_client(struct dsm_client **dev);

static struct dsm_client *selinux_dsm_client = NULL;

static void selinux_dsm_client_notify(const char* content)
{
	if (selinux_dsm_client == NULL) {
		get_selinux_client(&selinux_dsm_client);
	}

	if(selinux_dsm_client && !dsm_client_ocuppy(selinux_dsm_client)) {
		dsm_client_record(selinux_dsm_client, "%s\n", content);
		dsm_client_notify(selinux_dsm_client, DSM_SELINUX_ERROR_NO);
		printk("selinux_dsm_client_notify OK\n ");
	}
}

static char * selinux_black_list [] = {
	"u:r:su:s0", // scontext=u:r:su:s0 don't upload dsm
	"u:r:shell:s0", // scontext=u:r:shell:s0 don't upload dsm
	"u:r:adbd:s0", // scontext=u:r:adbd:s0 don't upload dsm
	"module_request", // { module_request } * tcontext=u:r:kernel:s0 tclass=system permissive=0
	"sys_ptrace", // { sys_ptrace } * tclass=capability permissive=0
	"pool-3-thread-1", // { search } comm="pool-3-thread-1" * scontext=u:r:system_app:s0 tcontext=u:r:untrusted_app:s0:c512,c768 tclass=dir permissive=0
	"pool-3-thread-2", // { search } comm="pool-3-thread-1" * scontext=u:r:system_app:s0 tcontext=u:r:untrusted_app:s0:c512,c768 tclass=dir permissive=0
	"pool-3-thread-3", // { search } comm="pool-3-thread-1" * scontext=u:r:system_app:s0 tcontext=u:r:untrusted_app:s0:c512,c768 tclass=dir permissive=0
	"CallbackHandler", // { search } comm="CallbackHandler" * scontext=u:r:system_app:s0 tcontext=u:r:platform_app:s0:c512,c768 tclass=dir permissive=0 
};

static int selinux_dsm_filter_black_list(char *data)
{
	int index = 0;

	// filter black list
	for (index = 0; index < sizeof(selinux_black_list)/sizeof(char *); index++) {
		if (strstr(data, selinux_black_list[index]) != NULL) {
			return -1;
		}
	}

	return 0;
}

struct audit_node {
	struct list_head list;
	u32 ssid;
	u32 tsid;
	u16 tclass;
	u32 audited;
};

#define AUDIT_NODE_MAX_NUMBER	(100)
static unsigned int audit_node_number = 0;
static struct list_head audit_node_head = LIST_HEAD_INIT(audit_node_head);

static int find_node_by_audit(struct list_head *head, u32 ssid, u32 tsid, u16 tclass, u32 audited)
{
	struct audit_node *node;
	struct list_head *temp_head;

	list_for_each(temp_head, head) {
		node = list_entry(temp_head, struct audit_node, list);
		if ((node->ssid == ssid) && (node->tsid == tsid) && (node->tclass == tclass) && (node->audited == audited)) {
			/* find node by ssid & tsid & tclass &  audited */
			return 0;
		}
	}

	return -1;
}

static int selinux_dsm_filter_audit_list(struct common_audit_data *a)
{
	u32 ssid = a->selinux_audit_data->ssid;
	u32 tsid = a->selinux_audit_data->tsid;
	u16 tclass = a->selinux_audit_data->tclass;
	u32 audited = a->selinux_audit_data->audited;
	u32 denied = a->selinux_audit_data->denied;

	struct audit_node *node = NULL;

	// avc granted don't upload dsm
	if (denied == 0) {
		return -1;
	}

	if(audit_node_number > AUDIT_NODE_MAX_NUMBER) {
		return -1;
	}

	// return code is 0 when find node successfull
	if (find_node_by_audit(&audit_node_head, ssid, tsid, tclass, audited) == 0) {
		return -1;
	}

	node = kmalloc(sizeof(struct audit_node), GFP_KERNEL);
	if (!node) {
		printk("%s, kmalloc fail (node)\n", __func__);
		return -1;
	}
	memset(node, 0, sizeof(struct audit_node));

	node->ssid = ssid;
	node->tsid = tsid;
	node->tclass = tclass;
	node->audited = audited;

	// save a new audit node
	INIT_LIST_HEAD(&node->list);
	list_add_tail(&node->list, &audit_node_head);

	audit_node_number++;

	// every 4 times we can upload dsm
	if ((audit_node_number % 4) == 0) {
		return 0;
	}
	else {
		return -1;
	}
}

void selinux_dsm_upload(struct audit_buffer *ab, struct common_audit_data *a)
{
	char *data = NULL;

	audit_log_data(ab, &data);

	if (data == NULL) {
		return;
	}

	if (selinux_dsm_filter_black_list(data) == -1) {
		return;
	}

	if (selinux_dsm_filter_audit_list(a) == -1) {
		return;
	}

	selinux_dsm_client_notify(data);
}
