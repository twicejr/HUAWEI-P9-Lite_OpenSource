/*
 * Copyright (C) ST-Ericsson SA 2011
 * Author: Maxime Coquelin <maxime.coquelin@stericsson.com> for ST-Ericsson.
 * License terms:  GNU General Public License (GPL), version 2
 */

#include <linux/mm.h>
#include <linux/spinlock.h>
#include <linux/hisi/pasr.h>

#include "helper.h"

/*#define SHOW_VAR(var)  pr_err(#var":0x%x\n", var)*/
/*#define PASR_DEBUG pr_err*/
#define PASR_DEBUG(...)

enum pasr_state {
	PASR_REFRESH,
	PASR_NO_REFRESH,
};

struct pasr_fw {
	struct pasr_map *map;
};

struct pasr_fw pasr;

void pasr_update_mask(struct pasr_section *section, enum pasr_state state)
{
	struct pasr_die *die = section->die;
	phys_addr_t addr = section->start - die->start;
	u8 bit = addr / die->section_size;
    /*unsigned int old_mem_reg = die->mem_reg;*/
	PASR_DEBUG("in %s\n", __func__);
    PASR_DEBUG("%s:%d: rank: %d; section->start:0x%x; section->size:0x%x state: %s;\n", __func__, __LINE__, die->cookie, section->start, die->section_size, state == PASR_REFRESH ? "PASR_REFRESH":"PASR_NO_REFRESH");
	if (state == PASR_REFRESH)
		die->mem_reg &= ~(1 << bit);    /* need refresh */
	else
		die->mem_reg |= (1 << bit);     /* no need refresh, that means we can throw away the data of this segment */

    /*pr_debug("die: 0x%x; die->mem_reg: 0x%x -> 0x%x\n", die, old_mem_reg, die->mem_reg);*/
	pr_debug("%s(): %s refresh section 0x%lx. Die%d mem_reg = 0x%08x\n"
			, __func__, state == PASR_REFRESH ? "Start" : "Stop"
			, (long unsigned int)section->start, die->idx, die->mem_reg);
	pr_debug("%s(): bit = %d\n", __func__, bit);
	if (die->apply_mask)
    {
        /*pr_debug("%s:%d: now apply_mask, [%d, %d]\n", __func__, __LINE__, die->mem_reg, (unsigned int)(die->cookie));*/
		die->apply_mask(&die->mem_reg, die->cookie);
    }

	return;
}

void pasr_put(phys_addr_t paddr, unsigned long size)
{
	struct pasr_section *s;
	unsigned long cur_sz;
	unsigned long flags = 0;

	PASR_DEBUG("%s: paddr=0x%lx, size=0x%lx\n", __func__, paddr, size);
	if (!pasr.map) {
		PASR_DEBUG("%s(): Map not initialized.\n"
			"\tCommand line parameters missing or incorrect\n"
			, __func__);
		goto out;
	}

	if (paddr >= 0x100000000) {		/*  if paddr >= 4G */
		paddr = paddr - 0x20000000;	/*	then   paddr = paddr - 0.5G */
	}

	PASR_DEBUG("%s: paddr=0x%lx, size=0x%lx\n", __func__, paddr, size);

	do {
		s = pasr_addr2section(pasr.map, paddr);
		if (!s)
			goto out;

		cur_sz = ((paddr + size) < (s->start + s->die->section_size)) ?
			size : s->start + s->die->section_size - paddr;

		if (s->lock)
			spin_lock_irqsave(s->lock, flags);

		s->free_size += cur_sz;
		BUG_ON(s->free_size > s->die->section_size);

		if (s->free_size < s->die->section_size)
			goto unlock;

		if (!s->pair)
			pasr_update_mask(s, PASR_NO_REFRESH);
		else if (s->pair->free_size == s->die->section_size) {
				pasr_update_mask(s, PASR_NO_REFRESH);
				pasr_update_mask(s->pair, PASR_NO_REFRESH);
		}
unlock:
		if (s->lock)
			spin_unlock_irqrestore(s->lock, flags);

		paddr += cur_sz;
		size -= cur_sz;
	} while (size);

out:
	return;
}

void pasr_get(phys_addr_t paddr, unsigned long size)
{
	unsigned long flags = 0;
	unsigned long cur_sz;
	struct pasr_section *s;

	PASR_DEBUG("%s:%d paddr=0x%lx, size=0x%lx\n", __func__, __LINE__, paddr, size);

	if (!pasr.map) {
		PASR_DEBUG("%s(): Map not initialized.\n"
			"\tCommand line parameters missing or incorrect\n"
			, __func__);
		return;
	}

	if (paddr >= 0x100000000) {		/*  if paddr >= 4G */
		paddr = paddr - 0x20000000;	/*	then   paddr = paddr - 0.5G */
	}

	PASR_DEBUG("%s:%d paddr=0x%lx, size=0x%lx\n", __func__, __LINE__, paddr, size);

	do {
		s = pasr_addr2section(pasr.map, paddr);
		if (!s)
			goto out;
		cur_sz = ((paddr + size) < (s->start + s->die->section_size)) ?
			size : s->start + s->die->section_size - paddr;

		if (s->lock)
			spin_lock_irqsave(s->lock, flags);

		if (s->free_size < s->die->section_size)
			goto unlock;

		if (!s->pair)
			pasr_update_mask(s, PASR_REFRESH);
		else if (s->pair->free_size == s->die->section_size) {
				pasr_update_mask(s, PASR_REFRESH);
				pasr_update_mask(s->pair, PASR_REFRESH);
		}
unlock:
		BUG_ON(cur_sz > s->free_size);
		s->free_size -= cur_sz;

		if (s->lock)
			spin_unlock_irqrestore(s->lock, flags);

		paddr += cur_sz;
		size -= cur_sz;
	} while (size);

out:
	return;
}

int pasr_register_mask_function(phys_addr_t addr, void *function, void *cookie)
{
	struct pasr_die *die = pasr_addr2die(pasr.map, addr);

	if (!die) {
		pr_err("%s: No DDR die corresponding to address 0x%lx\n",
				__func__, (long unsigned int)addr);
		return -EINVAL;
	}

	if (addr != die->start)
		pr_warning("%s: Addresses mismatch (Die = 0x%lx, addr = 0x%lx\n"
				, __func__, (long unsigned int)die->start, (long unsigned int)addr);

	die->cookie = cookie;
	die->apply_mask = function;
       pr_debug("%s:%d: die: %p; addr: 0x%lx; die->cookie: %p; die->mem_reg: 0x%x\n",
            __func__, __LINE__, die, (long unsigned int)addr, die->cookie, die->mem_reg);
	die->apply_mask(&die->mem_reg, die->cookie);

	return 0;
}
int pasr_switch = 0x33455432;
int __init pasr_init_core(struct pasr_map *map)
{
	if (pasr_switch == 0x33455432)
		pasr.map = map;
	return 0;
}

