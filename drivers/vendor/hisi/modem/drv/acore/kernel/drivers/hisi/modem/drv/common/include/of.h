/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __OF_H__
#define __OF_H__ 

#include <product_config.h>

#ifdef __KERNEL__
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#elif defined(_WRS_KERNEL) || defined(__OS_VXWORKS__) ||  defined(__OS_RTOSCK__)
#ifdef __OS_VXWORKS__
#include <vmLibCommon.h>
#include <private/kernelBaseLibP.h>	/* kernelId */
#include <private/vmLibP.h>
#include <arch/arm/mmuArmArch6PalLib.h>
#endif

#include <stdlib.h>
#include <errno.h>
#include <osl_err.h>
#include <osl_types.h>
#include <osl_generic.h>
#include <bsp_om.h>

struct boot_param_header {
	__be32	magic;
	__be32	totalsize;
	__be32	off_dt_struct;
	__be32	off_dt_strings;
	__be32	off_mem_rsvmap;
	__be32	version;
	__be32	last_comp_version;
	__be32	boot_cpuid_phys;
	__be32	dt_strings_size;
	__be32	dt_struct_size;
};

struct of_device_id
{
	char       name[32];
	char       type[32];
	char       compatible[128];
	const void *data;
};

typedef u32 phandle;
typedef u32 ihandle;

struct property {
	char            *name;
	int             length;
	void            *value;
	struct property *next;
};

struct device_node {
	const char         *name;
	const char         *type;
	phandle            phandle;
	const char         *full_name;
	struct property    *properties;
	struct device_node *parent;
	struct device_node *child;
	struct device_node *sibling;
	struct device_node *next;      /* next device of same type */
	struct device_node *allnext;   /* next in list of all nodes */
	void               *data;
};

#define MAX_PHANDLE_ARGS 8
struct of_phandle_args {
	struct device_node *np;
	int                args_count;
	uint32_t           args[MAX_PHANDLE_ARGS];
};

static inline void of_node_put(struct device_node *node) { }
static inline struct device_node *of_node_get(struct device_node *node)
{
       return node;
}

#ifdef CONFIG_OF
struct device_node *dts_find_node_by_name(struct device_node *from, const char *name);
struct device_node *dts_find_node_by_type(struct device_node *from, const char *type);
struct device_node *dts_find_compatible_node(struct device_node *from, const char *type, const char *compat);
struct device_node *dts_find_matching_node_and_match(struct device_node *from,
	const struct of_device_id *matches,
	const struct of_device_id **match);
struct device_node *dts_find_node_by_path(const char *path);
struct device_node *dts_find_node_by_phandle(phandle handle);
struct device_node *dts_get_parent(const struct device_node *node);
struct device_node *dts_get_next_child(const struct device_node *node, struct device_node *prev);
struct device_node *dts_get_next_available_child(const struct device_node *node, struct device_node *prev);
struct device_node *dts_get_child_by_name(const struct device_node *node, const char *name);
struct device_node *dts_find_node_with_property(struct device_node *from, const char *prop_name);
struct property *dts_find_property(const struct device_node *np, const char *name, int *lenp);
int dts_property_read_u32_index(const struct device_node *np, const char *propname, u32 index, u32 *out_value);
int dts_property_read_u8_array(const struct device_node *np, const char *propname, u8 *out_values, size_t sz);
int dts_property_read_u16_array(const struct device_node *np, const char *propname, u16 *out_values, size_t sz);
int dts_property_read_u32_array(const struct device_node *np, const char *propname, u32 *out_values, size_t sz);
int dts_property_read_u64(const struct device_node *np, const char *propname, u64 *out_value);
int dts_property_read_string(struct device_node *np, const char *propname, const char **out_string);
int dts_property_read_string_index(struct device_node *np, const char *propname, int index, const char **output);
int dts_property_match_string(struct device_node *np, const char *propname, const char *string);
int dts_property_count_strings(struct device_node *np, const char *propname);
int dts_device_is_compatible(const struct device_node *device, const char *);
int dts_device_is_available(const struct device_node *device);
const void *dts_get_property(const struct device_node *node, const char *name, int *lenp);
int dts_n_addr_cells(struct device_node *np);
int dts_n_size_cells(struct device_node *np);
const struct of_device_id *of_match_node(const struct of_device_id *matches, const struct device_node *node);
int dts_modalias_node(struct device_node *node, char *modalias, int len);
struct device_node *of_parse_phandle(const struct device_node *np, const char *phandle_name, int index);
int dts_parse_phandle_with_args(const struct device_node *np,
	const char *list_name, const char *cells_name, int index,
	struct of_phandle_args *out_args);
int dts_count_phandle_with_args(const struct device_node *np, const char *list_name, const char *cells_name);
int dts_machine_is_compatible(const char *compat);
const __be32 *dts_prop_next_u32(struct property *prop, const __be32 *cur,u32 *pu);
const char *dts_prop_next_string(struct property *prop, const char *cur);
struct device_node *dts_parse_phandle(const struct device_node *np, const char *phandle_name, int index);
const struct of_device_id *dts_match_node(const struct of_device_id *matches, const struct device_node *node);

#define of_find_node_by_name(from, name)            dts_find_node_by_name(from,  name)
#define of_find_node_by_type(from, type)            dts_find_node_by_type(from,  type)
#define of_find_compatible_node(from, type, compat) dts_find_compatible_node(from, type, compat)
#define of_find_node_by_path(path)                  dts_find_node_by_path(path)
#define of_find_node_by_phandle(phandle)            dts_find_node_by_phandle(phandle)
#define of_get_parent(node)                         dts_get_parent(node)
#define of_get_next_child(node, prev)               dts_get_next_child(node, prev)
#define of_get_next_available_child(node, prev)     dts_get_next_available_child(node, prev)
#define of_get_child_by_name(node, name)            dts_get_child_by_name(node, name)
#define of_find_node_with_property(from, prop_name) dts_find_node_with_property(from, prop_name)
#define of_find_property(np, name, lenp)            dts_find_property(np, name, lenp)
#define of_device_is_compatible(np, compt)          dts_device_is_compatible(np, compt)
#define of_device_is_available(np)                  dts_device_is_available(np)
#define of_get_property(node, name, lenp)           dts_get_property(node, name, lenp)
#define of_n_addr_cells(np)                         dts_n_addr_cells(np)
#define of_n_size_cells(np)                         dts_n_size_cells(np)
#define of_match_node(matches, node)                dts_match_node(matches, node)
#define of_modalias_node(node, modalias, len)       dts_modalias_node(node, modalias, len)
#define of_parse_phandle(np, phandle_name, index)   dts_parse_phandle(np, phandle_name, index)
#define of_machine_is_compatible(compat)            dts_machine_is_compatible(compat)
#define of_prop_next_u32(prop, cur, pu)             dts_prop_next_u32(prop, cur, pu)
#define of_prop_next_string(prop, cur)              dts_prop_next_string(prop, cur)
#define of_find_matching_node_and_match(from, matches, match)      dts_find_matching_node_and_match(from, matches, match)
#define of_property_read_u32_index(np, propname, index, out_value) dts_property_read_u32_index(np, propname, index, out_value)
#define of_property_read_u8_array(np, propname, out_values, sz)    dts_property_read_u8_array(np, propname, out_values, sz)
#define of_property_read_u16_array(np, propname, out_values, sz)   dts_property_read_u16_array(np, propname, out_values, sz)
#define of_property_read_u32_array(np, propname, out_values, sz)   dts_property_read_u32_array(np, propname, out_values, sz)
#define of_property_read_u64(np, propname, out_values)             dts_property_read_u64(np, propname, out_values)
#define of_property_read_string(np, propname, out_string)          dts_property_read_string(np, propname, out_string)
#define of_property_read_string_index(np, propname, index, output) dts_property_read_string_index(np, propname, index, output)
#define of_property_match_string(np, propname, out_string)         dts_property_match_string(np, propname, out_string)
#define of_property_count_strings(np, propname)                    dts_property_count_strings(np, propname)
#define of_count_phandle_with_args(np, list_name, cells_name)      dts_count_phandle_with_args(np, list_name, cells_name)
#define of_parse_phandle_with_args(np, list_name, cells_name,index, out_args) \
	dts_parse_phandle_with_args(np, list_name, cells_name,index, out_args)

#define for_each_node_by_name(dn, name) \
	for (dn = of_find_node_by_name(NULL, name); dn; \
	     dn = of_find_node_by_name(dn, name))
#define for_each_node_by_type(dn, type) \
	for (dn = of_find_node_by_type(NULL, type); dn; \
	     dn = of_find_node_by_type(dn, type))
#define for_each_compatible_node(dn, type, compatible) \
	for (dn = of_find_compatible_node(NULL, type, compatible); dn; \
	     dn = of_find_compatible_node(dn, type, compatible))
#define for_each_matching_node(dn, matches) \
	for (dn = of_find_matching_node(NULL, matches); dn; \
	     dn = of_find_matching_node(dn, matches))
#define for_each_matching_node_and_match(dn, matches, match) \
	for (dn = of_find_matching_node_and_match(NULL, matches, match); \
	     dn; dn = of_find_matching_node_and_match(dn, matches, match))
#define for_each_child_of_node(parent, child) \
	for (child = of_get_next_child(parent, NULL); child != NULL; \
	     child = of_get_next_child(parent, child))

#define for_each_available_child_of_node(parent, child) \
	for (child = of_get_next_available_child(parent, NULL); child != NULL; \
	     child = of_get_next_available_child(parent, child))

#define for_each_node_with_property(dn, prop_name) \
	for (dn = of_find_node_with_property(NULL, prop_name); dn; \
		 dn = of_find_node_with_property(dn, prop_name))
#define for_each_property_of_node(dn, pp) \
	for (pp = dn->properties; pp != NULL; pp = pp->next)
#define of_property_for_each_u32(np, propname, prop, p, u)	\
	for (prop = of_find_property(np, propname, NULL),	\
		p = of_prop_next_u32(prop, NULL, &u);		\
		p;						\
		p = of_prop_next_u32(prop, p, &u))
#define of_property_for_each_string(np, propname, prop, s)	\
	for (prop = of_find_property(np, propname, NULL),	\
		s = of_prop_next_string(prop, NULL);		\
		s;						\
		s = of_prop_next_string(prop, s))

static inline u64 of_read_number(const __be32 *cell, int size)
{
	u64 r = 0;
	while (size--)
	{
		r = (r << 32) | be32_to_cpu(*(cell));
		cell++;
	}
	return r;
}

static inline unsigned long of_read_ulong(const __be32 *cell, int size)
{
	return of_read_number(cell, size);
}

static inline int of_get_child_count(const struct device_node *np)
{
	struct device_node *child;
	int num = 0;

	for_each_child_of_node(np, child)
		num++;

	return num;
}

static inline struct device_node *of_find_matching_node(
	struct device_node *from,
	const struct of_device_id *matches)
{
	return of_find_matching_node_and_match(from, matches, NULL);
}

void bsp_dts_init(void);
int of_reg_info_get(struct device_node *np, int index, u64 *start, u64 *size);
void *of_iomap(struct device_node *np, int index);
unsigned int irq_of_parse_and_map(struct device_node *dev, int index);
int of_selftest(void);

#else /* CONFIG_OF */
static inline void bsp_dts_init(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OF, "<%s> is stub\n", __FUNCTION__);
}

static inline int of_selftest(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OF, "<%s> is stub\n", __FUNCTION__);
	return 0;
}

static inline int of_reg_info_get(struct device_node *np, int index, u64 *start, u64 *size)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OF, "<%s> is stub\n", __FUNCTION__);
	return 0;
}
static inline void *of_iomap(struct device_node *np, int index)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OF, "<%s> is stub\n", __FUNCTION__);
	return NULL;
}

static inline unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OF, "<%s> is stub\n", __FUNCTION__);
	return 0;
}

static inline const char* of_node_full_name(struct device_node *np)
{
	return "<no-node>";
}

static inline struct device_node *of_find_node_by_name(struct device_node *from,
	const char *name)
{
	return NULL;
}

static inline struct device_node *of_get_parent(const struct device_node *node)
{
	return NULL;
}

static inline bool of_have_populated_dt(void)
{
	return false;
}

#define for_each_child_of_node(parent, child) \
	while (0)

#define for_each_matching_node(dn, matches) \
	while (0)

static inline struct device_node *of_get_child_by_name(
					const struct device_node *node,
					const char *name)
{
	return NULL;
}

static inline int of_get_child_count(const struct device_node *np)
{
	return 0;
}

static inline int of_device_is_compatible(const struct device_node *device,
					  const char *name)
{
	return 0;
}

static inline int of_device_is_available(const struct device_node *device)
{
	return 0;
}

static inline struct property *of_find_property(const struct device_node *np,
						const char *name,
						int *lenp)
{
	return NULL;
}

static inline struct device_node *of_find_compatible_node(
						struct device_node *from,
						const char *type,
						const char *compat)
{
	return NULL;
}

static inline int of_property_read_u32_index(const struct device_node *np,
			const char *propname, u32 index, u32 *out_value)
{
	return -ENOSYS;
}

static inline int of_property_read_u8_array(const struct device_node *np,
			const char *propname, u8 *out_values, size_t sz)
{
	return -ENOSYS;
}

static inline int of_property_read_u16_array(const struct device_node *np,
			const char *propname, u16 *out_values, size_t sz)
{
	return -ENOSYS;
}

static inline int of_property_read_u32_array(const struct device_node *np,
					     const char *propname,
					     u32 *out_values, size_t sz)
{
	*out_values = 0;
	return -ENOSYS;
}

static inline int of_property_read_string(struct device_node *np,
					  const char *propname,
					  const char **out_string)
{
	*out_string = NULL;
	return -ENOSYS;
}

static inline int of_property_read_string_index(struct device_node *np,
						const char *propname, int index,
						const char **out_string)
{
	*out_string = NULL;
	return -ENOSYS;
}

static inline int of_property_count_strings(struct device_node *np,
					    const char *propname)
{
	return -ENOSYS;
}

static inline const void *of_get_property(const struct device_node *node,
				const char *name,
				int *lenp)
{
	*lenp = 0;
	return NULL;
}

static inline int of_property_read_u64(const struct device_node *np,
				       const char *propname, u64 *out_value)
{
	*out_value = 0;
	return -ENOSYS;
}

static inline int of_property_match_string(struct device_node *np,
					   const char *propname,
					   const char *string)
{
	return -ENOSYS;
}

static inline struct device_node *of_parse_phandle(const struct device_node *np,
						   const char *phandle_name,
						   int index)
{
	return NULL;
}

static inline int of_parse_phandle_with_args(struct device_node *np,
					     const char *list_name,
					     const char *cells_name,
					     int index,
					     struct of_phandle_args *out_args)
{
	return -ENOSYS;
}

static inline int of_count_phandle_with_args(struct device_node *np,
					     const char *list_name,
					     const char *cells_name)
{
	return -ENOSYS;
}

static inline int of_alias_get_id(struct device_node *np, const char *stem)
{
	return -ENOSYS;
}

static inline int of_machine_is_compatible(const char *compat)
{
	return 0;
}

#define of_match_ptr(_ptr)	NULL
#define of_match_node(_matches, _node)	NULL
#define of_property_for_each_u32(np, propname, prop, p, u) \
	while (0)
#define of_property_for_each_string(np, propname, prop, s) \
	while (0)
#endif /* CONFIG_OF */

static inline bool of_property_read_bool(const struct device_node *np,
					 const char *propname)
{
	struct property *prop = of_find_property(np, propname, NULL);

	return prop ? true : false;/* [false alarm]:ÆÁ±ÎFortify´íÎó */
}

static inline int of_property_read_u8(const struct device_node *np,
				       const char *propname,
				       u8 *out_value)
{
	return of_property_read_u8_array(np, propname, out_value, 1);
}

static inline int of_property_read_u16(const struct device_node *np,
				       const char *propname,
				       u16 *out_value)
{
	return of_property_read_u16_array(np, propname, out_value, 1);
}

static inline int of_property_read_u32(const struct device_node *np,
				       const char *propname,
				       u32 *out_value)
{
	return of_property_read_u32_array(np, propname, out_value, 1);
}

#endif /* __KERNEL__ */
#endif /* __OF_H__ */
