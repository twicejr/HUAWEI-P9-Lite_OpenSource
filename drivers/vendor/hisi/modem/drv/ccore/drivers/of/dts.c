/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  base.c
*
*   作    者 :  y00184236
*
*   描    述 :  本文件主要完成dts基础代码
*
*   修改记录 :  2014年11月17日  v1.00  y00184236  创建
**************************************************************************/
#include <securec.h>
#include <osl_types.h>
#include <osl_module.h>
#include <osl_malloc.h>
#include <osl_list.h>
#include <osl_spinlock.h>
#include <osl_sem.h>
#include <of.h>
#include "dts.h"
/*lint --e{64, 124, 502, 506, 573, 578, 613, 712, 713, 732, 737, 747}*/

#define FOUR_BYTE_ALIGN   (4)
#define EIGHT_BYTE_ALIGN  (8)
#define UNFLATTEN_DT_FLAG (0xdeadbeef)

static void *dts_dt_alloc(unsigned long *mem, unsigned long size,
				       unsigned long align)
{
	void *resource;

	*mem = ALIGN(*mem, align);
	resource = (void *)*mem;
	*mem += size;

	return resource;
}

static unsigned long dts_dt_node(struct boot_param_header *blob,
				unsigned long mem,
				unsigned long *current_node,
				struct device_node *father,
				struct device_node ***allnextpp,
				unsigned long fp_size)
{
	struct device_node *np;
	struct property *pp, **prev_property = NULL;
	char *currentp;
	u32 tag;
	u32 length = 0;
	u32 alloc_size;
	int has_name = 0;
	int new_style = 0;

	tag = be32_to_cpup((__be32 *)(*current_node));
	if (tag != OF_DT_BEGIN_NODE)
	{
		of_pr_err("invalid begin tag: %x\n", tag);
		return mem;
	}
	*current_node += FOUR_BYTE_ALIGN;
	currentp = (char *)*current_node;
	length = alloc_size = strlen(currentp) + 1;
	*current_node = ALIGN(*current_node + length, FOUR_BYTE_ALIGN);

	if ((*currentp) != '/')
	{
		new_style = 1;
		if (fp_size == 0) {
			fp_size = 1;
			alloc_size = 2;
			length = 1;
			*currentp = '\0';
		} else {
			fp_size += length;
			alloc_size = fp_size;
		}
	}

	np = dts_dt_alloc(&mem, sizeof(struct device_node) + alloc_size, __alignof__(struct device_node)); /*lint !e732 */
	if (allnextpp) 
	{
		char *full_name = NULL;
		(void)memset_s(np, sizeof(*np), 0, sizeof(*np));
		np->full_name = full_name = ((char *)np) + sizeof(*np);
		if (new_style) 
		{
			/* 重建新格式的路径信息 */
			if (father && father->parent) {
				(void)strcpy_s(full_name, alloc_size, father->full_name);
				full_name += strlen(full_name);
			}
			*(full_name++) = '/';
		}
		(void)memcpy_s(full_name, length, currentp, length);

		prev_property = &np->properties;
		**allnextpp = np;
		*allnextpp = &np->allnext;
		if (father != NULL)
		{
			np->parent = father;
			if (father->next == NULL)
				father->child = np;
			else
				father->next->sibling = np;
			father->next = np;
		}
	}
	while (1)
	{
		u32 size = 0;
		u32 offset = 0;
		char *pname = NULL;

		tag = be32_to_cpup((__be32 *)(*current_node));
		if (tag == OF_DT_NOP) {
			*current_node += FOUR_BYTE_ALIGN;
			continue;
		}
		if (tag != OF_DT_PROP)
			break;
		*current_node += FOUR_BYTE_ALIGN;
		size = be32_to_cpup((__be32 *)(*current_node));
		offset = be32_to_cpup((__be32 *)((*current_node) + FOUR_BYTE_ALIGN));
		*current_node += EIGHT_BYTE_ALIGN;
		if (be32_to_cpu(blob->version) < 0x10)
			*current_node = ALIGN(*current_node, size >= EIGHT_BYTE_ALIGN? EIGHT_BYTE_ALIGN: FOUR_BYTE_ALIGN);

		pname = dts_fdt_string_get(blob, offset);
		if (NULL == pname)
		{
			of_pr_info("cann't find prop_name\n");
			break;
		}
		if (strcmp(pname, "name") == 0)
			has_name = 1;
		length = strlen(pname) + 1;
		pp = dts_dt_alloc(&mem, sizeof(struct property), __alignof__(struct property)); /*lint !e732 */
		if (allnextpp) {
			if ((strcmp(pname, "phandle") == 0) ||
			    (strcmp(pname, "linux,phandle") == 0)) {
				if (np->phandle == 0)
					np->phandle = be32_to_cpup((__be32*)*current_node);
			}
			if (strcmp(pname, "ibm,phandle") == 0)
				np->phandle = be32_to_cpup((__be32 *)*current_node);
			pp->name = pname;
			pp->length = size;
			pp->value = (void *)*current_node;/* [false alarm]:屏蔽Fortify错误 */
			*prev_property = pp;/* [false alarm]:屏蔽Fortify错误 */
			prev_property = &pp->next;
		}
		*current_node = ALIGN((*current_node) + size, FOUR_BYTE_ALIGN);
	}
	if (!has_name) {
		char *p1 = currentp, *ps = currentp, *pa = NULL;
		int size;

		while (*p1) {
			if ('@' == (*p1))
				pa = p1;
			if ('/' == (*p1))
				ps = p1 + 1;
			p1++;
		}
		if (pa < ps)
			pa = p1;
		size = (pa - ps) + 1;
		pp = dts_dt_alloc(&mem, sizeof(struct property) + size, __alignof__(struct property)); /*lint !e732 */
		if (allnextpp) {
			pp->name = "name";
			pp->length = size;
			pp->value = pp + 1;
			*prev_property = pp;
			prev_property = &pp->next;
			(void)memcpy_s(pp->value, size - 1, ps, size - 1); /*lint !e732 */
			((char *)pp->value)[size - 1] = 0;
			of_pr_debug("new name for %s to %s\n", currentp, (char *)pp->value);
		}
	}
	if (allnextpp) {/* [false alarm]:屏蔽Fortify错误 */
		*prev_property = NULL;/* [false alarm]:屏蔽Fortify错误 */
		np->name = dts_get_property(np, "name", NULL);
		np->type = dts_get_property(np, "device_type", NULL);

		if (!np->name)
			np->name = "<NULL>";
		if (!np->type)
			np->type = "<NULL>";
	}
	while (OF_DT_BEGIN_NODE == tag || OF_DT_NOP == tag) {
		if (OF_DT_NOP == tag)
			*current_node += FOUR_BYTE_ALIGN;
		else
			mem = dts_dt_node(blob, mem, current_node, np, allnextpp, fp_size);
		tag = be32_to_cpup((__be32 *)(*current_node));
	}
	if (tag != OF_DT_END_NODE) {
		of_pr_err("invalid end tag: %x\n", tag);
		return mem;
	}
	*current_node += FOUR_BYTE_ALIGN;
	return mem;
}

static void dts_alias_add(struct alias_prop *ap, struct device_node *np,
			 int id, const char *stem, int stem_len)
{
	ap->np = np;
	ap->id = id;
	(void)strncpy(ap->stem, stem, stem_len); /*lint !e732 */
	ap->stem[stem_len] = 0;
	list_add_tail(&ap->link, &g_dts_ctrl.aliases_list);
	of_pr_debug("%s: stem=%s id=%i node=%s\n",ap->alias, ap->stem, ap->id, dts_node_full_name_get(np));
}

void dts_alias_scan(void * (*dt_alloc)(u64 size, u64 align))
{
	struct property *pp;

	g_dts_ctrl.aliases = of_find_node_by_path("/aliases");
	if (!g_dts_ctrl.aliases)
		return;

	for_each_property_of_node(g_dts_ctrl.aliases, pp) {
		const char *start = pp->name;
		const char *end = start + strlen(start);
		struct device_node *np;
		struct alias_prop *ap;
		int id = 0, len;

		/* Skip those we do not want to proceed */
		if (!strcmp(pp->name, "name") || !strcmp(pp->name, "phandle") || !strcmp(pp->name, "linux,phandle"))
			continue;

		np = of_find_node_by_path(pp->value);
		if (!np)
			continue;

		/* walk the alias backwards to extract the id and work out
		 * the 'stem' string */
		while (isxdigit(*(end-1)) && end > start)
			end--;
		len = end - start;

		if (strtoint(end, 10, &id) < 0)
			continue;

		/* Allocate an alias_prop with enough space for the stem */
		ap = dt_alloc(sizeof(*ap) + len + 1, 4);
		if (!ap)
			continue;
		(void)memset_s(ap, sizeof(*ap) + len + 1, 0, sizeof(*ap) + len + 1);
		ap->alias = start;
		dts_alias_add(ap, np, id, start, len);
	}
}

static void device_tree_unflatten(struct boot_param_header *dtb,
			     struct device_node **all_dts_nodes,
			     void * (*dts_mem_alloc)(u64 size, u64 align))
{
	unsigned long begin = 0;
	unsigned long alloc_size  = 0;
	unsigned long mem   = 0;
	struct device_node **allnext_node = all_dts_nodes;

	of_pr_debug("enter\n");

	if (!dtb)
	{
		of_pr_debug("no dtb file\n");
		return;
	}

	of_pr_debug("magic=0x%08x, size=0x%08x, version=0x%08x\n", be32_to_cpu(dtb->magic), be32_to_cpu(dtb->totalsize), be32_to_cpu(dtb->version));

	if (OF_DT_HEADER != be32_to_cpu(dtb->magic)) 
	{
		of_pr_err("invalid dtb file(0x%x)\n", be32_to_cpu(dtb->magic));
		return;
	}

	/* 首次扫描, 确认整个设备树的大小 */
	begin = ((unsigned long)dtb) + be32_to_cpu(dtb->off_dt_struct);
	alloc_size = dts_dt_node(dtb, 0, &begin, NULL, NULL, 0);
	alloc_size = (alloc_size | 3) + 1;

	of_pr_debug("alloced size=0x%lx\n", alloc_size);

	/* 为展开的设备数分配内存 */
	mem = (unsigned long)dts_mem_alloc(alloc_size + 4, __alignof__(struct device_node)); /*lint !e732 */
	if ((unsigned long)NULL == mem)
	{
		of_pr_err("no mem space left\n");
		return;
	}

	(void)memset_s((void *)mem, alloc_size, 0, alloc_size);

	((__be32 *)mem)[alloc_size / 4] = cpu_to_be32(UNFLATTEN_DT_FLAG);

	of_pr_debug("unflatten device tree at 0x%lx\n", mem);

	/* 第二次扫描, 展开 */
	begin = ((unsigned long)dtb) + be32_to_cpu(dtb->off_dt_struct);
	(void)dts_dt_node(dtb, mem, &begin, NULL, &allnext_node, 0);
	if (OF_DT_END != be32_to_cpup((__be32 *)begin))
	{
		of_pr_warn("invalid end tag(0x%08x)\n", *((u32 *)begin));
	}
	if (UNFLATTEN_DT_FLAG != be32_to_cpu(((__be32 *)mem)[alloc_size / 4]))
	{
		of_pr_warn("end tag(0x%08x) was overwriten\n", be32_to_cpu(((__be32 *)mem)[alloc_size / 4]));
	}
	*allnext_node = NULL;

	of_pr_debug("exit\n");
}

void dts_tree_unflat(void)
{
	device_tree_unflatten(g_dts_ctrl.dtb_file_header, &g_dts_ctrl.allnodes, dts_init_dt_alloc_memory_arch);

	dts_alias_scan(dts_init_dt_alloc_memory_arch);
}

char *dts_fdt_string_get(struct boot_param_header *blob, u32 offset)
{
	return ((char *)blob) +	be32_to_cpu(blob->off_dt_strings) + offset;
}

void *dts_fdt_property_get(struct boot_param_header *blob, unsigned long node, const char *name, unsigned long *size)
{
	u32 tag = 0;
	u32 dt_size = 0;
	u32 dt_offset = 0;
	unsigned long current_node = node;
	const char *str_name = NULL;

	do 
	{
		tag = be32_to_cpup((__be32 *)current_node);

		current_node += FOUR_BYTE_ALIGN;
		if (OF_DT_NOP == tag)
			continue;
		if (OF_DT_PROP != tag)
			return NULL;

		dt_size = be32_to_cpup((__be32 *)current_node);
		dt_offset = be32_to_cpup((__be32 *)(current_node + FOUR_BYTE_ALIGN));
		current_node += EIGHT_BYTE_ALIGN;
		if (be32_to_cpu(blob->version) < 0x10)
			current_node = ALIGN(current_node, dt_size >= EIGHT_BYTE_ALIGN ? EIGHT_BYTE_ALIGN : FOUR_BYTE_ALIGN);

		str_name = dts_fdt_string_get(blob, dt_offset);
		if (NULL == str_name) {
			of_pr_warn("no prop index name\n");
			return NULL;
		}
		if (strcmp(name, str_name) == 0)
		{
			if (size)
				*size = dt_size;
			return (void *)current_node;
		}
		current_node += dt_size;
		current_node = ALIGN(current_node, FOUR_BYTE_ALIGN);
	} while (1);
}

int dts_init_dt_scan_root(unsigned long node, const char *uname, int depth, void *data)
{
	__be32 *prop;

	if (depth != 0)
		return 0;

	g_dts_ctrl.root_size_cells = OF_ROOT_NODE_SIZE_CELLS_DEFAULT;
	g_dts_ctrl.root_addr_cells = OF_ROOT_NODE_ADDR_CELLS_DEFAULT;

	prop = dts_get_flat_dt_prop(node, "#size-cells", NULL);
	if (prop)
		g_dts_ctrl.root_size_cells = be32_to_cpup(prop);
	of_pr_debug("g_dts_ctrl.root_size_cells = %x\n", g_dts_ctrl.root_size_cells);

	prop = dts_get_flat_dt_prop(node, "#address-cells", NULL);
	if (prop)
		g_dts_ctrl.root_addr_cells = be32_to_cpup(prop);
	of_pr_debug("g_dts_ctrl.root_addr_cells = %x\n", g_dts_ctrl.root_addr_cells);

	return 1;
}

int dts_scan_flat_dt(int (*do_it)(unsigned long node, const char *dt_name, int depth,void *data), void *data)
{
	int resource = 0;
	int depth = -1;
	unsigned long current_node = 0;

	current_node = ((unsigned long)g_dts_ctrl.dtb_file_header) + be32_to_cpu(g_dts_ctrl.dtb_file_header->off_dt_struct);
	do 
	{
		u32 tag = be32_to_cpup((__be32 *)current_node);
		const char *base_path = NULL;

		current_node += FOUR_BYTE_ALIGN;
		if (OF_DT_END_NODE == tag) {
			depth--;
			continue;
		}
		if (OF_DT_NOP == tag)
			continue;
		if (OF_DT_END == tag)
			break;
		if (OF_DT_PROP == tag) {
			u32 dt_size = be32_to_cpup((__be32 *)current_node);
			current_node += EIGHT_BYTE_ALIGN;
			if (be32_to_cpu(g_dts_ctrl.dtb_file_header->version) < 0x10)
				current_node = ALIGN(current_node, dt_size >= EIGHT_BYTE_ALIGN? EIGHT_BYTE_ALIGN: FOUR_BYTE_ALIGN);
			current_node += dt_size;
			current_node = ALIGN(current_node, FOUR_BYTE_ALIGN);
			continue;
		}
		if (tag != OF_DT_BEGIN_NODE) {
			of_pr_err("invalid tag = 0x%8x\n", tag);
			return -EINVAL;
		}
		depth++;
		base_path = (char *)current_node;
		current_node = ALIGN(current_node + strlen(base_path) + 1, FOUR_BYTE_ALIGN);
		if (*base_path == '/')
			base_path = basename_get(base_path);
		resource = do_it(current_node, base_path, depth, data);
		if (resource != 0)
			break;
	} while (1);

	return resource;
}

void *dts_get_flat_dt_prop(unsigned long node, const char *name,
				 unsigned long *size)
{
	return dts_fdt_property_get(g_dts_ctrl.dtb_file_header, node, name, size);
}

int dts_n_addr_cells(struct device_node *np)
{
	const __be32 *ip;

	do {
		if (np->parent)
			np = np->parent;
		ip = of_get_property(np, "#address-cells", NULL);
		if (ip)
			return be32_to_cpup(ip);
	} while (np->parent);
	/* No #address-cells property for the root node */
	return OF_ROOT_NODE_ADDR_CELLS_DEFAULT;
}

int dts_n_size_cells(struct device_node *np)
{
	const __be32 *ip;

	do {
		if (np->parent)
			np = np->parent;
		ip = of_get_property(np, "#size-cells", NULL);
		if (ip)
			return be32_to_cpup(ip);
	} while (np->parent);
	/* No #size-cells property for the root node */
	return OF_ROOT_NODE_SIZE_CELLS_DEFAULT;
}

static struct property *__dts_find_property(const struct device_node *np,
					   const char *name, int *lenp)
{
	struct property *pp;

	if (!np)
		return NULL;

	for (pp = np->properties; pp; pp = pp->next) {
		if (of_prop_cmp(pp->name, name) == 0) {
			if (lenp)
				*lenp = pp->length;
			break;
		}
	}

	return pp;
}

struct property *dts_find_property(const struct device_node *np, const char *name, int *lenp)
{
	struct property *pp;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	pp = __dts_find_property(np, name, lenp);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);

	return pp;
}

static const void *__dts_get_property(const struct device_node *np, const char *name, int *lenp)
{
	struct property *pp = __dts_find_property(np, name, lenp);

	return pp ? pp->value : NULL;
}

const void *dts_get_property(const struct device_node *np, const char *name,
			    int *lenp)
{
	struct property *pp = of_find_property(np, name, lenp);

	return pp ? pp->value : NULL;
}

static int __dts_device_is_compatible(const struct device_node *device,
				     const char *compat)
{
	const char* cp;
	int cplen, l;

	cp = __dts_get_property(device, "compatible", &cplen);
	if (cp == NULL)
		return 0;
	while (cplen > 0) {
		if (of_compat_cmp(cp, compat, strlen(compat)) == 0)
			return 1;
		l = strlen(cp) + 1;
		cp += l;
		cplen -= l;
	}

	return 0;
}

int dts_device_is_compatible(const struct device_node *device,
		const char *compat)
{
	unsigned long flags = 0;
	int res;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	res = __dts_device_is_compatible(device, compat);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return res;
}

int dts_machine_is_compatible(const char *compat)
{
	struct device_node *root;
	int rc = 0;

	root = of_find_node_by_path("/");
	if (root) {
		rc = of_device_is_compatible(root, compat);
		of_node_put(root);
	}
	return rc;
}

static int __dts_device_is_available(const struct device_node *device)
{
	const char *status;
	int statlen;

	status = __dts_get_property(device, "status", &statlen);
	if (status == NULL)
		return 1;

	if (statlen > 0) {
		if (!strcmp(status, "okay") || !strcmp(status, "ok"))
			return 1;
	}

	return 0;
}

int dts_device_is_available(const struct device_node *device)
{
	unsigned long flags = 0;
	int res;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	res = __dts_device_is_available(device);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return res;

}

struct device_node *dts_get_parent(const struct device_node *node)
{
	struct device_node *np;
	unsigned long flags = 0;

	if (!node)
		return NULL;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	np = of_node_get(node->parent);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

struct device_node *dts_get_next_child(const struct device_node *node, struct device_node *prev)
{
	struct device_node *next;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	next = prev ? prev->sibling : node->child;
	for (; next; next = next->sibling)
		if (of_node_get(next))
			break;
	of_node_put(prev);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return next;
}

struct device_node *dts_get_next_available_child(const struct device_node *node,
	struct device_node *prev)
{
	struct device_node *next;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	next = prev ? prev->sibling : node->child;
	for (; next; next = next->sibling) {
		if (!__dts_device_is_available(next))
			continue;
		if (of_node_get(next))
			break;
	}
	of_node_put(prev);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return next;
}

struct device_node *dts_get_child_by_name(const struct device_node *node,
				const char *name)
{
	struct device_node *child;

	for_each_child_of_node(node, child)
		if (child->name && (of_node_cmp(child->name, name) == 0))
			break;
	return child;
}

struct device_node *dts_find_node_by_path(const char *path)
{
	struct device_node *np = g_dts_ctrl.allnodes;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	for (; np; np = np->allnext) {
		if (np->full_name && (of_node_cmp(np->full_name, path) == 0)
		    && of_node_get(np))
			break;
	}
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

struct device_node *dts_find_node_by_name(struct device_node *from, const char *name)
{
	struct device_node *np;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	np = from ? from->allnext : g_dts_ctrl.allnodes;
	for (; np; np = np->allnext)
		if (np->name && (of_node_cmp(np->name, name) == 0)
		    && of_node_get(np))
			break;
	of_node_put(from);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

struct device_node *dts_find_node_by_type(struct device_node *from, const char *type)
{
	struct device_node *np;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	np = from ? from->allnext : g_dts_ctrl.allnodes;
	for (; np; np = np->allnext)
		if (np->type && (of_node_cmp(np->type, type) == 0)
		    && of_node_get(np))
			break;
	of_node_put(from);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

struct device_node *dts_find_compatible_node(struct device_node *from, const char *type, const char *compatible)
{
	struct device_node *np;
	unsigned long flags = 0;

	if (NULL == compatible)
	{
		return NULL;
	}
	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	np = from ? from->allnext : g_dts_ctrl.allnodes;
	for (; np; np = np->allnext) {
		if (type
		    && !(np->type && (of_node_cmp(np->type, type) == 0)))
			continue;
		if (__dts_device_is_compatible(np, compatible) &&
		    of_node_get(np))
			break;
	}
	of_node_put(from);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

struct device_node *dts_find_node_with_property(struct device_node *from, const char *prop_name)
{
	struct device_node *np;
	struct property *pp;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	np = from ? from->allnext : g_dts_ctrl.allnodes;
	for (; np; np = np->allnext) {
		for (pp = np->properties; pp; pp = pp->next) {
			if (of_prop_cmp(pp->name, prop_name) == 0) {
				(void)of_node_get(np);
				goto out; /*lint !e801 */
			}
		}
	}
out:
	of_node_put(from);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

static const struct of_device_id *__dts_match_node(const struct of_device_id *matches, const struct device_node *node)
{
	if (!matches)
		return NULL;

	while (matches->name[0] || matches->type[0] || matches->compatible[0]) {
		int match = 1;
		if (matches->name[0])
			match &= node->name
				&& !strcmp(matches->name, node->name); /*lint !e514*/
		if (matches->type[0])
			match &= node->type
				&& !strcmp(matches->type, node->type); /*lint !e514*/
		if (matches->compatible[0])
			match &= __dts_device_is_compatible(node,
							   matches->compatible);
		if (match)
			return matches;
		matches++;
	}
	return NULL;
}

const struct of_device_id *dts_match_node(const struct of_device_id *matches, const struct device_node *node)
{
	const struct of_device_id *match;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	match = __dts_match_node(matches, node);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return match;
}

struct device_node *dts_find_matching_node_and_match(struct device_node *from,
					const struct of_device_id *matches,
					const struct of_device_id **match)
{
	struct device_node *np;
	const struct of_device_id *m;
	unsigned long flags = 0;

	if (match)
		*match = NULL;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	np = from ? from->allnext : g_dts_ctrl.allnodes;
	for (; np; np = np->allnext) {
		m = __dts_match_node(matches, np);
		if (m && of_node_get(np)) {
			if (match)
				*match = m;
			break;
		}
	}
	of_node_put(from);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

int dts_modalias_node(struct device_node *node, char *modalias, int len)
{
	const char *compatible, *p;
	int cplen;

	compatible = of_get_property(node, "compatible", &cplen);
	if (!compatible || strlen(compatible) > (unsigned int)cplen)
		return -ENODEV;
	p = strchr(compatible, ',');
	(void)strlcpy(modalias, p ? p + 1 : compatible, len);
	return 0;
}

struct device_node *dts_find_node_by_phandle(phandle handle)
{
	struct device_node *np;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_dts_ctrl.dn_lock, flags);
	for (np = g_dts_ctrl.allnodes; np; np = np->allnext)
		if (np->phandle == handle)
			break;
	(void)of_node_get(np);
	spin_unlock_irqrestore(&g_dts_ctrl.dn_lock, flags);
	return np;
}

static void *dts_find_property_value_of_size(const struct device_node *np,
			const char *propname, u32 len)
{
	struct property *prop = of_find_property(np, propname, NULL);

	if (!prop)
		return ERR_PTR(-EINVAL);
	if (!prop->value)
		return ERR_PTR(-ENODATA);
	if (len > (u32)prop->length)
		return ERR_PTR(-EOVERFLOW);

	return prop->value;
}

int dts_property_read_u32_index(const struct device_node *np,
				       const char *propname,
				       u32 index, u32 *out_value)
{
	const u32 *val = dts_find_property_value_of_size(np, propname,
					((index + 1) * sizeof(*out_value)));

	if (IS_ERR(val))
		return PTR_ERR(val);

	*out_value = be32_to_cpup(((__be32 *)val) + index);
	return 0;
}

int dts_property_read_u8_array(const struct device_node *np, const char *propname, u8 *out_values, size_t sz)
{
	const u8 *val = dts_find_property_value_of_size(np, propname,
						(sz * sizeof(*out_values)));

	if (IS_ERR(val))
		return PTR_ERR(val);

	while (sz--)
		*out_values++ = *val++;
	return 0;
}

int dts_property_read_u16_array(const struct device_node *np, const char *propname, u16 *out_values, size_t sz)
{
	const __be16 *val = dts_find_property_value_of_size(np, propname,
						(sz * sizeof(*out_values)));

	if (IS_ERR(val))
		return PTR_ERR(val);

	while (sz--)
		*out_values++ = be16_to_cpup(val++);
	return 0;
}

int dts_property_read_u32_array(const struct device_node *np,
			       const char *propname, u32 *out_values,
			       size_t sz)
{
	const __be32 *val = dts_find_property_value_of_size(np, propname,
						(sz * sizeof(*out_values)));

	if (IS_ERR(val))
		return PTR_ERR(val);

	while (sz--)
		*out_values++ = be32_to_cpup(val++);
	return 0;
}

int dts_property_read_u64(const struct device_node *np, const char *propname,
			 u64 *out_value)
{
	const __be32 *val = dts_find_property_value_of_size(np, propname,
						sizeof(*out_value));

	if (IS_ERR(val))
		return PTR_ERR(val);

	*out_value = of_read_number(val, 2);
	return 0;
}

int dts_property_read_string(struct device_node *np, const char *propname,
				const char **out_string)
{
	struct property *prop = of_find_property(np, propname, NULL);
	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;
	if (strnlen(prop->value, prop->length) >= (unsigned int)prop->length) /*lint !e732 */
		return -EILSEQ;
	*out_string = prop->value;
	return 0;
}

int dts_property_read_string_index(struct device_node *np, const char *propname,
				  int index, const char **output)
{
	struct property *prop = of_find_property(np, propname, NULL);
	int i = 0;
	size_t l = 0, total = 0;
	const char *p;

	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;
	if (strnlen(prop->value, prop->length) >= (unsigned int)prop->length) /*lint !e732 */
		return -EILSEQ;

	p = prop->value;

	for (i = 0; total < (size_t)prop->length; total += l, p += l) {
		l = strlen(p) + 1;
		if (i++ == index) {
			*output = p;
			return 0;
		}
	}
	return -ENODATA;
}

int dts_property_match_string(struct device_node *np, const char *propname,
			     const char *string)
{
	struct property *prop = of_find_property(np, propname, NULL);
	size_t l;
	int i;
	const char *p, *end;

	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;

	p = prop->value;
	end = p + prop->length;

	for (i = 0; p < end; i++, p += l) {
		l = strlen(p) + 1;
		if (p + l > end)
			return -EILSEQ;
		of_pr_debug("comparing %s with %s\n", string, p);
		if (strcmp(string, p) == 0)
			return i; /* Found it; return index */
	}
	return -ENODATA;
}

int dts_property_count_strings(struct device_node *np, const char *propname)
{
	struct property *prop = of_find_property(np, propname, NULL);
	int i = 0;
	size_t l = 0, total = 0;
	const char *p;

	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;
	if (strnlen(prop->value, prop->length) >= (unsigned int)prop->length) /*lint !e732 */
		return -EILSEQ;

	p = prop->value;

	for (i = 0; total < (size_t)prop->length; total += l, p += l, i++)
		l = strlen(p) + 1;

	return i;
}

struct device_node *dts_parse_phandle(const struct device_node *np, const char *phandle_name, int index)
{
	const __be32 *phandle;
	int size;

	phandle = of_get_property(np, phandle_name, &size);
	if ((!phandle) || ((unsigned int)size < sizeof(*phandle) * (index + 1)))
		return NULL;

	return dts_find_node_by_phandle(be32_to_cpup(phandle + index));
}

static int __dts_parse_phandle_with_args(const struct device_node *np,
					const char *list_name,
					const char *cells_name, int index,
					struct of_phandle_args *out_args)
{
	const __be32 *list, *list_end;
	int rc = 0, size, cur_index = 0;
	u32 count = 0;
	struct device_node *node = NULL;
	phandle phandle;

	/* Retrieve the phandle list property */
	list = of_get_property(np, list_name, &size);
	if (!list)
		return -ENOENT;
	list_end = list + size / sizeof(*list);

	/* Loop over the phandles until all the requested entry is found */
	while (list < list_end) {
		rc = -EINVAL;
		count = 0;

		/*
		 * If phandle is 0, then it is an empty entry with no
		 * arguments.  Skip forward to the next entry.
		 */
		phandle = be32_to_cpup(list++);
		if (phandle) {
			/*
			 * Find the provider node and parse the #*-cells
			 * property to determine the argument length
			 */
			node = dts_find_node_by_phandle(phandle);
			if (!node) {
				of_pr_err("%s: could not find phandle\n",
					 np->full_name);
				goto err; /*lint !e801 */
			}
			if (of_property_read_u32(node, cells_name, &count)) {
				of_pr_err("%s: could not get %s for %s\n",
					 np->full_name, cells_name,
					 node->full_name);
				goto err; /*lint !e801 */
			}

			/*
			 * Make sure that the arguments actually fit in the
			 * remaining property data length
			 */
			if (list + count > list_end) {
				of_pr_err("%s: arguments longer than property\n",
					 np->full_name);
				goto err; /*lint !e801 */
			}
		}

		/*
		 * All of the error cases above bail out of the loop, so at
		 * this point, the parsing is successful. If the requested
		 * index matches, then fill the out_args structure and return,
		 * or return -ENOENT for an empty entry.
		 */
		rc = -ENOENT;
		if (cur_index == index) {
			if (!phandle)
				goto err; /*lint !e801 */

			if (out_args) {
				u32 i;
				if (WARN_ON(count > MAX_PHANDLE_ARGS))
					count = MAX_PHANDLE_ARGS;
				out_args->np = node;
				out_args->args_count = count;
				for (i = 0; i < count; i++)
					out_args->args[i] = be32_to_cpup(list++);
			} else {
				of_node_put(node);
			}

			/* Found it! return success */
			return 0;
		}

		of_node_put(node);
		node = NULL;
		list += count;
		cur_index++;
	}

	/*
	 * Unlock node before returning result; will be one of:
	 * -ENOENT : index is for empty phandle
	 * -EINVAL : parsing error on data
	 * [1..n]  : Number of phandle (count mode; when index = -1)
	 */
	rc = index < 0 ? cur_index : -ENOENT;
 err:
	if (node)
		of_node_put(node);
	return rc;
}

int dts_parse_phandle_with_args(const struct device_node *np, const char *list_name,
				const char *cells_name, int index,
				struct of_phandle_args *out_args)
{
	if (index < 0)
		return -EINVAL;
	return __dts_parse_phandle_with_args(np, list_name, cells_name, index, out_args);
}

int dts_count_phandle_with_args(const struct device_node *np, const char *list_name,
				const char *cells_name)
{
	return __dts_parse_phandle_with_args(np, list_name, cells_name, -1, NULL);
}

const __be32 *dts_prop_next_u32(struct property *prop, const __be32 *cur,
			       u32 *pu)
{
	const void *curv = cur;

	if (!prop)
		return NULL;

	if (!cur) {
		curv = prop->value;
		goto out_val; /*lint !e801 */
	}

	curv += sizeof(*cur);
	if (curv >= prop->value + prop->length)
		return NULL;

out_val:
	*pu = be32_to_cpup(curv);
	return curv;
}

const char *dts_prop_next_string(struct property *prop, const char *cur)
{
	const void *curv = cur;

	if (!prop)
		return NULL;

	if (!cur)
		return prop->value;

	curv += strlen(cur) + 1;
	if (curv >= prop->value + prop->length)
		return NULL;

	return curv;
}
