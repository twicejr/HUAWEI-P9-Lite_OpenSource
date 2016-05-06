/*
 * blackbox. (kernel run data recorder.)
 *
 * Copyright (c) 2013 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/slab.h>

#include <linux/hisi/rdr_pub.h>
#include "rdr_inner.h"
#include "rdr_field.h"
#include "rdr_print.h"

static LIST_HEAD(__rdr_module_ops_list);
static DEFINE_SPINLOCK(__rdr_module_ops_list_lock);
static u64 g_s_cur_regcore;

u64 rdr_get_cur_regcore()
{
	return g_s_cur_regcore;
}

void rdr_add_cur_regcore(u64 corid)
{
	g_s_cur_regcore |= corid;
}

static void __rdr_register_module_ops(struct rdr_module_ops_s *ops)
{
	struct rdr_module_ops_s *p_info = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	unsigned long lock_flag;
	BB_PRINT_START();
	if (ops == NULL) {
		BB_PRINT_PN("invalid  parameter. ops:%p\n", ops);
		BB_PRINT_END();
		return;
	}
	spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
	if (list_empty(&__rdr_module_ops_list)) {
		BB_PRINT_ERR("list_add_tail coreid is [0x%llx]\n",
			     ops->s_core_id);
		list_add_tail(&(ops->s_list), &__rdr_module_ops_list);
		goto out;
	}

	list_for_each_safe(cur, next, &__rdr_module_ops_list) {
		p_info = list_entry(cur, struct rdr_module_ops_s, s_list);
		if (ops->s_core_id > p_info->s_core_id) {
			BB_PRINT_ERR("list_add2 coreid is [0x%llx]\n",
				     ops->s_core_id);
			list_add(&(ops->s_list), cur);
			goto out;
		}
	}
	BB_PRINT_ERR("list_add_tail2 coreid is [0x%llx]\n", ops->s_core_id);
	list_add_tail(&(ops->s_list), &__rdr_module_ops_list);
out:
	spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);
	BB_PRINT_END();
}

/*
 * func name: rdr_check_coreid
 * func args:
 *   u64 core_id,       core id;
 * return value		e_modid
 *	!= 0 error
 *	= 0 success
 */
u64 rdr_check_coreid(u64 core_id)
{
	struct rdr_module_ops_s *p_module_ops = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	unsigned long lock_flag;
	BB_PRINT_START();
	spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
	list_for_each_safe(cur, next, &__rdr_module_ops_list) {
		p_module_ops = list_entry(cur, struct rdr_module_ops_s, s_list);
		if (p_module_ops == NULL) {
			BB_PRINT_DBG("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		if (core_id == p_module_ops->s_core_id) {
			spin_unlock_irqrestore(&__rdr_module_ops_list_lock,
					       lock_flag);
			BB_PRINT_END();
			return core_id;
		}
	}
	spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);
	BB_PRINT_END();
	return 0;
}

int rdr_get_module_info(u64 coreid, struct rdr_register_module_result *retinfo)
{
	int ret = -1;
	switch (coreid) {
	case RDR_AP:
		ret = rdr_get_areainfo(RDR_AREA_AP, retinfo);
		break;
	case RDR_CP:
		ret = rdr_get_areainfo(RDR_AREA_CP, retinfo);
		break;
	case RDR_TEEOS:
		ret = rdr_get_areainfo(RDR_AREA_TEEOS, retinfo);
		break;
	case RDR_HIFI:
		ret = rdr_get_areainfo(RDR_AREA_HIFI, retinfo);
		break;
	case RDR_LPM3:
		ret = rdr_get_areainfo(RDR_AREA_LPM3, retinfo);
		break;
	case RDR_IOM3:
		ret = rdr_get_areainfo(RDR_AREA_IOM3, retinfo);
		break;
	case RDR_ISP:
		ret = rdr_get_areainfo(RDR_AREA_ISP, retinfo);
		break;
	case RDR_EMMC:
		ret = rdr_get_areainfo(RDR_AREA_EMMC, retinfo);
		break;
	default:
		ret = -1;
	}

	if (ret >= 0)
		retinfo->nve = rdr_get_nve();
	return ret;
}

/*
 * func name: rdr_register_module_ops
 * func args:
 *   u32 core_id,       core id;
 *      .
 *   struct rdr_module_ops_pub* ops;
 *   struct rdr_register_module_result* retinfo;
 * return value		e_modid
 *	< 0 error
 *	>=0 success
 */
int rdr_register_module_ops(u64 coreid,
			    struct rdr_module_ops_pub *ops,
			    struct rdr_register_module_result *retinfo)
{
	struct rdr_module_ops_s *p_module_ops = NULL;

	int ret = -1;
	BB_PRINT_START();
	if (!rdr_init_done()) {
		BB_PRINT_ERR("rdr init faild!\n");
		BB_PRINT_END();
		return ret;
	}
	if (ops == NULL) {
		BB_PRINT_PN("invalid  parameter. ops:%p\n", ops);
		BB_PRINT_END();
		return ret;
	}
	if (ops->ops_dump == NULL && ops->ops_reset == NULL) {
		BB_PRINT_PN("invalid  parameter. ops.dump or reset:%p\n", ops);
		BB_PRINT_END();
		return ret;
	}

	if (0 != rdr_check_coreid(coreid)) {
		BB_PRINT_ERR("core_id exist already\n");
		BB_PRINT_END();
		return ret;
	}
	p_module_ops = kmalloc(sizeof(struct rdr_module_ops_s), GFP_ATOMIC);
	if (p_module_ops == NULL) {
		BB_PRINT_PN("kmalloc error, e_tpye_info\n");
		BB_PRINT_END();
		return ret;
	}
	memset(p_module_ops, 0, sizeof(struct rdr_module_ops_s));
	/*check modid & modid_end region */

	p_module_ops->s_core_id = coreid;
	p_module_ops->s_ops.ops_dump = ops->ops_dump;
	p_module_ops->s_ops.ops_reset = ops->ops_reset;

	__rdr_register_module_ops(p_module_ops);
	rdr_add_cur_regcore(coreid);

	ret = rdr_get_module_info(coreid, retinfo);
	BB_PRINT_ERR("rdr_register_module_ops success.\n");
	BB_PRINT_END();
	return ret;
}

/*
 * func name: rdr_unregister_module_ops
 * func args:
 *   u32 coreid,			core id;
 * return
 *	< 0 fail
 *	>=0 success
 */
int rdr_unregister_module_ops(u64 coreid)
{
	struct rdr_module_ops_s *p_module_ops = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	unsigned long lock_flag;

	BB_PRINT_START();
	spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
	list_for_each_safe(cur, next, &__rdr_module_ops_list) {
		p_module_ops = list_entry(cur, struct rdr_module_ops_s, s_list);
		if (p_module_ops == NULL) {
			BB_PRINT_DBG("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		if (coreid == p_module_ops->s_core_id) {
			list_del(cur);
			kfree(p_module_ops);
			/*break; */
		}
	}
	spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);
	/*return e_type_info->e_modid_end; */
	BB_PRINT_END();
	return 0;
}

static u64 current_coremk;
static u32 current_modid;
static u64 current_mask;

static inline void set_curr_modid_coreid(u32 modid, u64 coremk)
{
	current_modid = modid;
	current_coremk = coremk;
	current_mask = 0;
}

static inline u64 check_coreid(u64 id)
{
	return current_coremk & id;
}

static inline u32 get_curr_modid(void)
{
	return current_modid;
}

/*
 * func name: rdr_dump_done
 * func args:
 *   u32 modid
 *   u32 coreid
 * return
 *	 NULL.
 * callback func.
 */
void rdr_dump_done(u32 modid, u64 coreid)
{
	BB_PRINT_START();
	BB_PRINT_ERR("%s: modid:[0x%x], coreid:[0x%llx]\n",
		     __func__, modid, coreid);
	if (modid != get_curr_modid()) {
		BB_PRINT_ERR("%s: invaild modid!!!\n", __func__);
		BB_PRINT_END();
		return;
	}
	if (0 == check_coreid(coreid)) {
		BB_PRINT_END();
		return;
	}
	current_mask |= coreid;
	BB_PRINT_ERR("rdr_dump_done current mask:[0x%llx]\n", current_mask);
	BB_PRINT_END();
}

/*
 * func name: rdr_get_dump_result
 * func args:
 *   u32 modid
 * return
 *	 dump_done state.
 */
u64 rdr_get_dump_result(u32 modid)
{
	BB_PRINT_START();
	if (modid != get_curr_modid()) {
		BB_PRINT_DBG("invalid modid :[0x%x]:[0x%x]\n",
			     modid, get_curr_modid());
		BB_PRINT_END();
		return 0;
	}
	BB_PRINT_DBG("current mask:[0x%llx]\n", current_mask);
	BB_PRINT_END();
	return current_mask;
}

/*
 * func name: rdr_notify_module_reset
 * func args:
 *   u32 modid
 *   rdr_exception_info_s e_info
 *   RDR_NVE nve
 * return
 *	 NULL
 */
void rdr_notify_module_reset(u32 modid, struct rdr_exception_info_s *e_info)
{
	struct rdr_module_ops_s *p_module_ops = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	u64 mask = 0;
	static bool rdr_reboot_later_flag; /* default value is false */
	unsigned long lock_flag;

	BB_PRINT_START();

	if (e_info == NULL) {
		BB_PRINT_PN("invalid  parameter. e:%p\n", e_info);
		BB_PRINT_END();
		return;
	}
	mask = e_info->e_reset_core_mask;
	spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
	list_for_each_safe(cur, next, &__rdr_module_ops_list) {
		p_module_ops = list_entry(cur, struct rdr_module_ops_s, s_list);
		if (p_module_ops == NULL) {
			BB_PRINT_DBG("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		BB_PRINT_ERR("p_module_ops->s_core_id is [0x%llx]\n",
			     p_module_ops->s_core_id);
		/* 针对AP复位的特殊处理 */
		if (p_module_ops->s_core_id == RDR_AP) {
			BB_PRINT_ERR("reboot priority[%s], need reboot flag[%s]"
				     " syserr list[%s], coreid mask[0x%llx]\n",
				     e_info->e_reboot_priority == RDR_REBOOT_NOW ? "Now" : "Later",
				     rdr_reboot_later_flag == true ? "true" : "false",
				     rdr_syserr_list_empty() ? "empty" : "Non empty",
				     mask & p_module_ops->s_core_id);
			/* 如果指定立即复位或者 之前有需要复位异常但因有异常未处理而搁置的复位
			  * 动作并且当前链表是空的情况下 或者当前异常需要AP复位并且没有异常需要
			  * 处理做AP复位动作
			  */
			if (e_info->e_reboot_priority == RDR_REBOOT_NOW ||
			    ((rdr_reboot_later_flag || (mask & p_module_ops->s_core_id))
			     && rdr_syserr_list_empty())) {
				BB_PRINT_ERR("reboot now!\n");
				spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);
				(*(p_module_ops->s_ops.ops_reset)) (modid,
								    e_info->e_exce_type, e_info->e_from_core);
				spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
			} else if ((mask & p_module_ops->s_core_id)
				   && !rdr_syserr_list_empty()) {
				BB_PRINT_ERR("reboot later!\n");
				rdr_reboot_later_flag = true;
			}
		} else if ((mask & p_module_ops->s_core_id) &&
			   (p_module_ops->s_ops.ops_reset != NULL)) {
			BB_PRINT_ERR("reset module [%s] start!\n",
				     rdr_get_exception_core(p_module_ops->s_core_id));
			spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);
			(*(p_module_ops->s_ops.ops_reset)) (modid,
							    e_info->e_exce_type, e_info->e_from_core);
			spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
			BB_PRINT_ERR("reset module [%s] end!\n",
				     rdr_get_exception_core(p_module_ops->s_core_id));
		}
	}
	spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);

	BB_PRINT_END();
	return;
}

/*
 * func name: rdr_notify_module_reset
 * func args:
 *   u32 modid
 *   rdr_exception_info_s e_info
 *   RDR_NVE nve
 * return
 *	 NULL
 */
u64 rdr_notify_onemodule_dump(u32 modid, u64 core, u32 type,
			      u64 formcore, char *path)
{
	struct rdr_module_ops_s *p_module_ops = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	u64 coreid = 0;
	unsigned long lock_flag;

	BB_PRINT_START();

	if (path == NULL) {
		BB_PRINT_PN("invalid  parameter. path:%p\n", path);
		BB_PRINT_END();
		return 0;
	}
	spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
	list_for_each_safe(cur, next, &__rdr_module_ops_list) {
		p_module_ops = list_entry(cur, struct rdr_module_ops_s, s_list);
		if (p_module_ops == NULL) {
			BB_PRINT_DBG("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		BB_PRINT_DBG
		    ("[%s][%d]core is [%llx],p_module_ops->s_core_id is [%llx]\n",
		     __func__, __LINE__, core, p_module_ops->s_core_id);
		if ((core & p_module_ops->s_core_id)
		    && (p_module_ops->s_ops.ops_dump != NULL)) {
			BB_PRINT_ERR("dump module data [%s] start!\n",
				     rdr_get_exception_core(p_module_ops->
							    s_core_id));
			spin_unlock_irqrestore(&__rdr_module_ops_list_lock,
					       lock_flag);
			(*(p_module_ops->s_ops.ops_dump)) (modid, type,
							   formcore, path,
							   rdr_dump_done);
			spin_lock_irqsave(&__rdr_module_ops_list_lock,
					  lock_flag);
			BB_PRINT_ERR("dump module data [%s] end!\n",
				     rdr_get_exception_core(p_module_ops->
							    s_core_id));
			/*spin_unlock(&__rdr_module_ops_list_lock);*/
			coreid = p_module_ops->s_core_id;
			break;
		}
	}
	spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);

	BB_PRINT_END();
	return coreid;
}

/*
 * func name: rdr_notify_module_dump
 * func args:
 *   u32 modid      exception id
 *   rdr_exception_info_s* e_info
 *   char* path         the path of save log.
 * return
 *	0 fail
 *	!0 success
 */
u64 rdr_notify_module_dump(u32 modid, struct rdr_exception_info_s *e_info,
			   char *path)
{
	u64 ret = 0;
	struct rdr_module_ops_s *p_module_ops = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	u64 mask = 0;
	unsigned long lock_flag;

	BB_PRINT_START();
	if (e_info == NULL) {
		BB_PRINT_PN("invalid  parameter. e:%p, p:%p\n", e_info, path);
		BB_PRINT_END();
		return ret;
	}
	mask = e_info->e_notify_core_mask;
	set_curr_modid_coreid(modid, mask);
	spin_lock_irqsave(&__rdr_module_ops_list_lock, lock_flag);
	list_for_each_safe(cur, next, &__rdr_module_ops_list) {
		p_module_ops = list_entry(cur, struct rdr_module_ops_s, s_list);
		if (p_module_ops == NULL) {
			BB_PRINT_DBG("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}

		/*
		 *First condition: Skip modules which hadn't triggered the exception, to ensure the trigger called firstly .
		 *Second condition: Skip the trigger, to avoid calling the dump-callback repeatedly.
		 */
		if ( (!ret && e_info->e_from_core != p_module_ops->s_core_id)
				||(ret && (e_info->e_from_core == p_module_ops->s_core_id)) ) {
			BB_PRINT_DBG("Skip module core [0x%llx]. %s:%d\n",
				p_module_ops->s_core_id, __func__, __LINE__);
			continue;
		}

		if ((mask & p_module_ops->s_core_id) &&
		    (p_module_ops->s_ops.ops_dump != NULL)) {
			BB_PRINT_ERR("dump module data [%s] start!\n",
				     rdr_get_exception_core(p_module_ops->s_core_id));
			spin_unlock_irqrestore(&__rdr_module_ops_list_lock,
					       lock_flag);
			(*(p_module_ops->s_ops.ops_dump)) (modid,
					e_info->e_exce_type,
					p_module_ops->s_core_id, path,
					rdr_dump_done);
			spin_lock_irqsave(&__rdr_module_ops_list_lock,
					  lock_flag);
			BB_PRINT_ERR("dump module data [%s] end!\n",
				     rdr_get_exception_core(p_module_ops->s_core_id));
			ret |= p_module_ops->s_core_id;
		}

		/*
		 *First, to call dump-callback of module which triggered the exception.
		 *After that, reset list pointer to the HEAD, and call other modules' callback.
		 */
		if (ret == p_module_ops->s_core_id){
			cur = &__rdr_module_ops_list;
			next = cur->next;
		}
	}
	spin_unlock_irqrestore(&__rdr_module_ops_list_lock, lock_flag);

	BB_PRINT_END();
	return ret;
}

/*
 * func name: rdr_print_all_ops
 * return	NULL
 */
void rdr_print_all_ops(void)
{
	int index = 1;
	struct rdr_module_ops_s *p_module_ops = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;

	BB_PRINT_START();
	spin_lock(&__rdr_module_ops_list_lock);
	list_for_each_safe(cur, next, &__rdr_module_ops_list) {
		p_module_ops = list_entry(cur, struct rdr_module_ops_s, s_list);
		if (p_module_ops == NULL) {
			BB_PRINT_DBG("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		BB_PRINT_DBG("==========[%.2d]-start==========\n", index);
		BB_PRINT_DBG(" core-id:    [0x%llx]\n",
			     p_module_ops->s_core_id);
		BB_PRINT_DBG(" dump-fn:    [0x%p]\n",
			     p_module_ops->s_ops.ops_dump);
		BB_PRINT_DBG(" reset-fn:   [0x%p]\n",
			     p_module_ops->s_ops.ops_reset);
		BB_PRINT_DBG("==========[%.2d]-e n d==========\n", index);
	}
	spin_unlock(&__rdr_module_ops_list_lock);

	BB_PRINT_END();
	return;
}
