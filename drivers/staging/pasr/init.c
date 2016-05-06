/*
 * Copyright (C) ST-Ericsson SA 2011
 * Author: Maxime Coquelin <maxime.coquelin@stericsson.com> for ST-Ericsson.
 * License terms:  GNU General Public License (GPL), version 2
 */

#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/sort.h>
#include <linux/hisi/pasr.h>

#include "helper.h"

#define NR_DIES 8
#define NR_INT 8
#define SZ_1536MB (0x60000000)
#define SZ_3072MB (0xC0000000)

struct ddr_die {
	phys_addr_t addr;
	unsigned long size;
	unsigned long section_nr;
	unsigned long section_size;
};

struct interleaved_area {
	phys_addr_t addr1;
	phys_addr_t addr2;
	unsigned long size;
};

struct pasr_info {
	int nr_dies;
	struct ddr_die die[NR_DIES];

	int nr_int;
	struct interleaved_area int_area[NR_INT];
};

static struct pasr_info __initdata pasr_info;
static struct pasr_map pasr_map;

static void add_ddr_die(phys_addr_t addr, unsigned long size);
static void add_interleaved_area(phys_addr_t a1,
		phys_addr_t a2, unsigned long size);

static int __init ddr_die_param(char *p)
{
	phys_addr_t start;
	unsigned long size;

    pr_debug("%s\n", __func__);

	size = memparse(p, &p);

	if (*p != '@')
		goto err;

	start = memparse(p + 1, &p);

	add_ddr_die(start, size);

	return 0;
err:
	return -EINVAL;
}
early_param("ddr_die", ddr_die_param);

static int __init interleaved_param(char *p)
{
	phys_addr_t start1, start2;
	unsigned long size;

	size = memparse(p, &p);

	if (*p != '@')
		goto err;

	start1 = memparse(p + 1, &p);

	if (*p != ':')
		goto err;

	start2 = memparse(p + 1, &p);

	add_interleaved_area(start1, start2, size);

	return 0;
err:
	return -EINVAL;
}
early_param("interleaved", interleaved_param);

void __init add_ddr_die(phys_addr_t addr, unsigned long size)
{
	unsigned long section_nr = 8;

	BUG_ON(pasr_info.nr_dies >= NR_DIES);

	if (size == SZ_1536MB || size == SZ_3072MB)
		section_nr = 6;

	pr_debug("%s: addr=0x%lx, size=0x%lx, nr = %lu\n", __func__, (long unsigned int)addr, size, section_nr);

	pasr_info.die[pasr_info.nr_dies].addr = addr;
	pasr_info.die[pasr_info.nr_dies].size = size;
	pasr_info.die[pasr_info.nr_dies].section_nr = section_nr;
	pasr_info.die[pasr_info.nr_dies++].section_size = size / section_nr;
}

void __init add_interleaved_area(phys_addr_t a1, phys_addr_t a2,
		unsigned long size)
{
	BUG_ON(pasr_info.nr_int >= NR_INT);

	pasr_info.int_area[pasr_info.nr_int].addr1 = a1;
	pasr_info.int_area[pasr_info.nr_int].addr2 = a2;
	pasr_info.int_area[pasr_info.nr_int++].size = size;
}

#ifdef DEBUG
/*#warning "DEBUG enabled, more messages"*/
static void __init pasr_print_info(struct pasr_info *info)
{
	int i;

	pr_err("PASR information coherent\n");


	pr_err("DDR Dies layout:\n");
	pr_err("\tid - start address - end address\n");
	for (i = 0; i < info->nr_dies; i++)
		pr_err("\t- %d : %#08x - %#08x\n",
			i, (unsigned int)info->die[i].addr,
			(unsigned int)(info->die[i].addr
				+ info->die[i].size - 1));

	if (info->nr_int == 0) {
		pr_err("No interleaved areas declared\n");
		return;
	}

	pr_err("Interleaving layout:\n");
	pr_err("\tid - start @1 - end @2 : start @2 - end @2\n");
	for (i = 0; i < info->nr_int; i++)
		pr_err("\t-%d - %#08x - %#08x : %#08x - %#08x\n"
			, i
			, (unsigned int)info->int_area[i].addr1
			, (unsigned int)(info->int_area[i].addr1
				+ info->int_area[i].size - 1)
			, (unsigned int)info->int_area[i].addr2
			, (unsigned int)(info->int_area[i].addr2
				+ info->int_area[i].size - 1));
}
#else
#define pasr_print_info(info) do {} while (0)
#endif /* DEBUG */

static int __init is_in_physmem(phys_addr_t addr, struct ddr_die *d)
{
	return ((addr >= d->addr) && (addr <= d->addr + d->size));
}

static int __init pasr_check_interleave_in_physmem(struct pasr_info *info,
						struct interleaved_area *i)
{
	struct ddr_die *d;
	int j;
	int err = 4;

	for (j = 0; j < info->nr_dies; j++) {
		d = &info->die[j];
		if (is_in_physmem(i->addr1, d))
			err--;
		if (is_in_physmem(i->addr1 + i->size, d))
			err--;
		if (is_in_physmem(i->addr2, d))
			err--;
		if (is_in_physmem(i->addr2 + i->size, d))
			err--;
	}

	return err;
}

static int __init ddrdie_cmp(const void *_a, const void *_b)
{
	const struct ddr_die *a = _a, *b = _b;

	return a->addr < b->addr ? -1 : a->addr > b->addr ? 1 : 0;
}

static int __init interleaved_cmp(const void *_a, const void *_b)
{
	const struct interleaved_area *a = _a, *b = _b;

	return a->addr1 < b->addr1 ? -1 : a->addr1 > b->addr1 ? 1 : 0;
}

static struct ddr_die * __init addr2die(struct pasr_info *info, phys_addr_t addr)
{
	struct ddr_die * die = info->die;
	int i;

	for (i = 0; i < NR_DIES; i++) {
		if (addr >= die[i].addr && addr < die[i].addr + die[i].size)
			return &die[i];
	}

	pr_err("%s: No die found for address %lx",
			__func__, (long unsigned int)addr);

	return NULL;
}

static int __init pasr_info_sanity_check(struct pasr_info *info)
{
	int i;

	/* Check at least one physical chunk is defined */
	if (info->nr_dies == 0) {
		pr_err("%s: No DDR dies declared in command line\n", __func__);
		return -EINVAL;
	}

	/* Sort DDR dies areas */
	sort(&info->die, info->nr_dies,
			sizeof(info->die[0]), ddrdie_cmp, NULL);

	/* Physical layout checking */
	for (i = 0; i < info->nr_dies; i++) {
		struct ddr_die *d1, *d2;

		d1 = &info->die[i];

		if (d1->size == 0) {
			pr_err("%s: DDR die at %lx has 0 size\n",
					__func__, (long unsigned int)d1->addr);
			return -EINVAL;
		}

		/*  Check die is aligned on section boundaries */
		if (((d1->addr % d1->section_size) != 0)
			|| ((d1->size % d1->section_size) != 0)) {
			pr_err("%s: DDR die at %lx (size %#lx) is not aligned"
					"on section boundaries %#lx\n",
					__func__, (long unsigned int)d1->addr,
					(long unsigned int)d1->size, (long unsigned int)d1->section_size);
			return -EINVAL;
		}

		if (i == 0)
			continue;

		/* Check areas are not overlapping */
		d2 = d1;
		d1 = &info->die[i-1];
		if ((d1->addr + d1->size - 1) >= d2->addr) {
			pr_err("%s: DDR dies at %lx and %lx are overlapping\n",
					__func__, (long unsigned int)d1->addr, (long unsigned int)d2->addr);
			return -EINVAL;
		}
	}

	/* Interleave layout checking */
	if (info->nr_int == 0)
		goto out;

	/* Sort interleaved areas */
	sort(&info->int_area, info->nr_int,
			sizeof(info->int_area[0]), interleaved_cmp, NULL);

	for (i = 0; i < info->nr_int; i++) {
		struct interleaved_area *i1;
		struct ddr_die *d1, *d2;

		i1 = &info->int_area[i];
		if (i1->size == 0) {
			pr_err("%s: Interleaved area %lx/%lx  has 0 size\n",
					__func__, (long unsigned int)i1->addr1, (long unsigned int)i1->addr2);
			return -EINVAL;
		}

		d1 = addr2die(info, i1->addr1);
		if (!d1) {
			pr_err("%s:[1] No DDR die corresponding to address 0x%lx\n",
					__func__, (long unsigned int)i1->addr1);
			return -EINVAL;
		}

		d2 = addr2die(info, i1->addr2);
		if (!d2) {
			pr_err("%s:[2] No DDR die corresponding to address 0x%lx\n",
					__func__, (long unsigned int)i1->addr2);
			return -EINVAL;
		}

		if (d1->section_size != d2->section_size) {
			pr_err("%s: Interleaved section size not matched\n", __func__);
			return -EINVAL;
		}

		/* Check area is aligned on section boundaries */
		if (((i1->addr1 % d1->section_size) != 0)
			|| ((i1->addr2 % d2->section_size) != 0)
			|| ((i1->size % d1->section_size) != 0)) {
			pr_err("%s: Interleaved area at %lx/%lx (size %lx) is not"
					"aligned on section boundaries %lx\n",
					__func__, (long unsigned int)i1->addr1, (long unsigned int)i1->addr2,
					(long unsigned int)i1->size, (long unsigned int)d1->section_size);
			return -EINVAL;
		}

		/* Check interleaved areas are not overlapping */
		if ((i1->addr1 + i1->size - 1) >= i1->addr2) {
			pr_err("%s: Interleaved areas %lx"
					"and %lx are overlapping\n",
					__func__, (long unsigned int)i1->addr1, (long unsigned int)i1->addr2);
			return -EINVAL;
		}

		/* Check the interleaved areas are in the physical areas */
		if (pasr_check_interleave_in_physmem(info, i1)) {
			pr_err("%s: Interleaved area %lx/%lx"
					"not in physical memory\n",
					__func__, (long unsigned int)i1->addr1, (long unsigned int)i1->addr2);
			return -EINVAL;
		}
	}

out:
	return 0;
}

#ifdef DEBUG
static void __init pasr_print_map(struct pasr_map *map)
{
	int i, j;

	if (!map)
		goto out;

	pr_err("PASR map:\n");

	for (i = 0; i < map->nr_dies; i++) {
		struct pasr_die *die = &map->die[i];

		pr_err("Die %d:\n", i);
		for (j = 0; j < die->nr_sections; j++) {
			struct pasr_section *s = &die->section[j];
			pr_err("\tSection %d: @ = %lx, Pair = %s\n"
					, j, (long unsigned int)s->start, s->pair ? "Yes" : "No");
		}
	}
out:
	return;
}
#else
#define pasr_print_map(map) do {} while (0)
#endif /* DEBUG */

static int __init pasr_build_map(struct pasr_info *info, struct pasr_map *map)
{
	int i, j;
	struct pasr_die *die;

	map->nr_dies = info->nr_dies;
	die = map->die;

	for (i = 0; i < info->nr_dies; i++) {
		phys_addr_t addr = info->die[i].addr;
		struct pasr_section *section = die[i].section;

		die[i].start = addr;
		die[i].idx = i;
		die[i].nr_sections = info->die[i].section_nr;
		die[i].section_size = info->die[i].section_size;

		for (j = 0; j < die[i].nr_sections; j++) {
			section[j].start = addr;
			addr += die[i].section_size;
			section[j].die = &die[i];
		}
	}

	for (i = 0; i < info->nr_int; i++) {
		struct interleaved_area *ia = &info->int_area[i];
		struct pasr_section *s1, *s2;
		unsigned long offset = 0;
		struct pasr_die * d = pasr_addr2die(map, ia->addr1);;
		if (!d)
			return -EINVAL;

		for (j = 0; j < (ia->size / d->section_size); j++) {
			s1 = pasr_addr2section(map, ia->addr1 + offset);
			s2 = pasr_addr2section(map, ia->addr2 + offset);
			if (!s1 || !s2)
				return -EINVAL;

			offset += d->section_size;

			s1->pair = s2;
			s2->pair = s1;
		}
	}
	return 0;
}

int __init early_pasr_setup(void)
{
	int ret;

    pr_err("early_pasr_setup\n");
	ret = pasr_info_sanity_check(&pasr_info);
	if (ret) {
		pr_err("PASR info sanity check failed (err %d)\n", ret);
		return ret;
	}

	pasr_print_info(&pasr_info);

	ret = pasr_build_map(&pasr_info, &pasr_map);
	if (ret) {
		pr_err("PASR build map failed (err %d)\n", ret);
		return ret;
	}

	pasr_print_map(&pasr_map);

	ret = pasr_init_core(&pasr_map);

	pr_err("PASR: First stage init done.\n");

	return ret;
}

/*
 * late_pasr_setup() has to be called after Linux allocator is
 * initialized but before other CPUs are launched.
 */
int __init late_pasr_setup(void)
{
	int i, j;
	struct pasr_section *s;

	for_each_pasr_section(i, j, pasr_map, s) {
		if (!s->lock) {
			s->lock = kzalloc(sizeof(spinlock_t), GFP_KERNEL);
			BUG_ON(!s->lock);
			spin_lock_init(s->lock);
			if (s->pair)
				s->pair->lock = s->lock;
		}
	}

	pr_err("PASR Second stage init done.\n");

	return 0;
}
