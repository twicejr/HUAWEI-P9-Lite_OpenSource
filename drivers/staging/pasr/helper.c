/*
 * Copyright (C) ST-Ericsson SA 2011
 * Author: Maxime Coquelin <maxime.coquelin@stericsson.com> for ST-Ericsson.
 * License terms:  GNU General Public License (GPL), version 2
 */

#include <linux/hisi/pasr.h>

/*#define PASR_DEBUG pr_err*/
#define PASR_DEBUG(...)


struct pasr_die *pasr_addr2die(struct pasr_map *map, phys_addr_t addr)
{
	unsigned int left, right, mid;

	if (!map)
		return NULL;

	left = 0;
	right = map->nr_dies;

	//addr &= ~(PASR_SECTION_SZ - 1);
	//addr = (addr / PASR_SECTION_SZ) * PASR_SECTION_SZ;

	while (left != right) {
		struct pasr_die *d;

		mid = (left + right) >> 1;
		d = &map->die[mid];
		/*start = (addr / (d->section_size * d->nr_sections)) * (d->section_size * d->nr_sections);*/
		PASR_DEBUG("addr: 0x%lx; left: 0x%lx; right: 0x%lx; mid: 0x%lx\n", addr, left, right, mid);
		PASR_DEBUG("d->start: 0x%lx; \n", d->start);

		if ((addr >= d->start) && (addr <= (d->start + (d->section_size * d->nr_sections)))) {
			PASR_DEBUG("0x%lx, 0x%lx\n", addr, d->start);
			PASR_DEBUG("0x%lx \n", addr-d->start);
			PASR_DEBUG("%d\n", __LINE__);
			return d;
		}
		else if (addr < d->start) {
			PASR_DEBUG("%d\n", __LINE__);
			right = mid;
		}
		else if (addr > (d->start + (d->section_size * d->nr_sections))) {
			PASR_DEBUG("%d %lx, %lx\n", __LINE__, addr, (d->start + (d->section_size * d->nr_sections)));
			left = mid;
		}
	}

	pr_err("%s: No die found for address %lx",
			__func__, (long unsigned int)addr);
	return NULL;
}

struct pasr_section *pasr_addr2section(struct pasr_map *map
				, phys_addr_t addr)
{
	unsigned int left, right, mid;
	struct pasr_die *die;

	/* Find the die the address it is located in */
	die = pasr_addr2die(map, addr);
	if (!die)
		goto err;

	left = 0;
	right = die->nr_sections;
	PASR_DEBUG("right: %d, section_size: 0x%x\n", right, die->section_size);

	//addr &= ~(PASR_SECTION_SZ - 1);
	addr = (addr / die->section_size) * die->section_size;
	PASR_DEBUG("addr: 0x%x\n", addr);

	 while (left != right) {
		struct pasr_section *s;

		mid = (left + right) >> 1;
		s = &die->section[mid];
		PASR_DEBUG("s->start: 0x%x, mid: 0x%x \n", s->start, mid);
		if (addr == s->start)
			return s;
		else if (addr > s->start)
			left = mid;
		else
			right = mid;
	}

err:
	/* Provided address isn't in any declared section */
	pr_err("%s: No section found for address %lx",
			__func__, (long unsigned int)addr);

	return NULL;
}

phys_addr_t pasr_section2addr(struct pasr_section *s)
{
	return s->start;
}
