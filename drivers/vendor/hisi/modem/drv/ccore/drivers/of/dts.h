/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  dts.h
*
*   作    者 :  y00184236
*
*   描    述 :  DTS模块内部头文件
*
*   修改记录 :  2014年07月28日  v1.00  y00184236  创建
*
*************************************************************************/
#ifndef __CCORE_DTS_H__
#define __CCORE_DTS_H__

#include <string.h>
#include <osl_types.h>
#include <osl_list.h>
#include <osl_spinlock.h>
#include <osl_generic.h>
#include <osl_bug.h>
#include <bsp_om.h>
#include <of.h>

/*lint --e{43}*/
#ifndef ULLONG_MAX
#define ULLONG_MAX     (~0ULL)
#endif
#define KSTRTOX_OVERFLOW	(1U << 31)
#define DT_BOOTM_SIZE  102400
#define DT_BOOTM_ALIGN 16
#define OF_ROOT_NODE_ADDR_CELLS_DEFAULT 1
#define OF_ROOT_NODE_SIZE_CELLS_DEFAULT 1
#define OF_DT_HEADER      0xd00dfeed
#define OF_DT_BEGIN_NODE  0x1
#define OF_DT_END_NODE    0x2
#define OF_DT_PROP        0x3
#define OF_DT_NOP         0x4
#define OF_DT_END         0x9
#define OF_DT_VERSION     0x10

#define kfree                    free
#define WARN_ON(condition)       (condition)
#define of_compat_cmp(s1, s2, l) strcasecmp((s1), (s2))
#define of_prop_cmp(s1, s2)		 strcmp((s1), (s2))
#define of_node_cmp(s1, s2)		 strcasecmp((s1), (s2))
#define  of_pr_debug(fmt, ...)    \
	(bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_OF, "[of]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  of_pr_warn(fmt, ...)      \
	(bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_OF, "[of]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  of_pr_info(fmt, ...)      \
	(bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_OF, "[of]:"fmt, ##__VA_ARGS__))
#define  of_pr_err(fmt, ...)      \
	(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OF, "[of]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

struct alias_prop {
	struct list_head link;
	const char *alias;
	struct device_node *np;
	int id;
	char stem[0];
};

struct dts_ctrl
{
	u32 state;
	struct device_node *allnodes;
	struct device_node *aliases;
	struct list_head aliases_list;
	struct boot_param_header *dtb_file_header;
	spinlock_t dn_lock;
	int  root_addr_cells;
	int  root_size_cells;
	u32  dev_tree_size;
};

/* 全局变量声明 */
extern struct dts_ctrl g_dts_ctrl;

/* 函数声明和inline函数定义 */
char *dts_fdt_string_get(struct boot_param_header *blob, u32 offset);
void *dts_fdt_property_get(struct boot_param_header *blob, unsigned long node, const char *name, unsigned long *size);
int dts_scan_flat_dt(int (*it)(unsigned long node, const char *uname, int depth,void *data), void *data);
void * dts_init_dt_alloc_memory_arch(u64 size, u64 align);
void *dts_get_flat_dt_prop(unsigned long node, const char *name, unsigned long *size);
int dts_init_dt_scan_root(unsigned long node, const char *uname, int depth, void *data);
void dts_tree_unflat(void);

int __must_check strtoint(const char *s, unsigned int base, int *res);

static inline char isxdigit(const char c)
{
	return (c >= '0' && c <= '9');
}

static inline const char *basename_get(const char *path)
{
	const char *tail = strrchr(path, '/');
	return tail ? tail + 1 : path;
}

static inline const char *dts_node_full_name_get(const struct device_node *np)
{
	return np ? np->full_name : "<no-node>";
}

#endif /* __CCORE_DTS_H__ */
