/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  Coresight_platform.h 头文件
*
*   作    者 :  l00169177
*
*   描    述 :  coresight框架所使用的头文件
*
*   修改记录 :  2014年10月24日  v1.00  l00169177  创建
*************************************************************************/

#ifndef _CORESIGHT_PLATFORM_H
#define _CORESIGHT_PLATFORM_H

#include "osl_types.h"
#include "osl_list.h"
#include "osl_err.h"
#include "osl_spinlock.h"
#include "osl_malloc.h"
#include "bsp_om.h"
#include "of.h"

//#define isb()
//#define mb()
#define BIT(nr)                      (1UL << (nr))


#define cs_fatal(fmt, ...)          bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_UTRACE, "[coresight] <%s> "fmt, __FUNCTION__,##__VA_ARGS__)
#define cs_error(fmt, ...)          bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "[coresight] <%s> "fmt, __FUNCTION__,##__VA_ARGS__)
#define cs_debug(fmt, ...)          bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_UTRACE, "[coresight] <%s> "fmt, __FUNCTION__,##__VA_ARGS__)
#define cs_info(fmt, ...)           bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_UTRACE, "[coresight] <%s> "fmt, __FUNCTION__,##__VA_ARGS__)

static inline long __must_check IS_ERR_OR_NULL(const void *ptr)
{
	return !ptr || IS_ERR_VALUE((unsigned long)ptr);
}

/*
 * Coresight management registers (0xF00-0xFCC)
 * 0xFA0 - 0xFA4: Management	registers in PFTv1.0
 *		  Trace		registers in PFTv1.1
 */
#define CORESIGHT_ITCTRL	(0xF00)
#define CORESIGHT_CLAIMSET	(0xFA0)
#define CORESIGHT_CLAIMCLR	(0xFA4)
#define CORESIGHT_LAR		(0xFB0)
#define CORESIGHT_LSR		(0xFB4)
#define CORESIGHT_AUTHSTATUS	(0xFB8)
#define CORESIGHT_DEVID		(0xFC8)
#define CORESIGHT_DEVTYPE	(0xFCC)

#define TIMEOUT_US		(100)

#define BM(lsb, msb)		((BIT(msb) - BIT(lsb)) + BIT(msb))
#define BMVAL(val, lsb, msb)	((val & BM(lsb, msb)) >> lsb)
#define BVAL(val, n)		((val & BIT(n)) >> n)

enum coresight_dev_subtype_source {
	CORESIGHT_DEV_SUBTYPE_SOURCE_NONE,
	CORESIGHT_DEV_SUBTYPE_SOURCE_PROC,
	CORESIGHT_DEV_SUBTYPE_SOURCE_BUS,
	CORESIGHT_DEV_SUBTYPE_SOURCE_SOFTWARE,
};

enum coresight_platform_dev_type {
	CORESIGHT_DEV_TYPE_NONE,
	CORESIGHT_DEV_TYPE_SINK,    /*只作为目的端 */
	CORESIGHT_DEV_TYPE_LINK,    /*只作为中间通路*/
	CORESIGHT_DEV_TYPE_LINKSINK,/*既作为目的端又作为中间通路*/
	CORESIGHT_DEV_TYPE_SOURCE,  /*数据产生源*/
};

enum coresight_dev_subtype_link {
	CORESIGHT_DEV_SUBTYPE_LINK_NONE,
	CORESIGHT_DEV_SUBTYPE_LINK_MERG,        /*FUNNEL*/
	CORESIGHT_DEV_SUBTYPE_LINK_SPLIT,       /*TPIU*/
	CORESIGHT_DEV_SUBTYPE_LINK_FIFO,
};

enum coresight_dev_subtype_sink {
	CORESIGHT_DEV_SUBTYPE_SINK_NONE,
	CORESIGHT_DEV_SUBTYPE_SINK_PORT,
	CORESIGHT_DEV_SUBTYPE_SINK_BUFFER,
};





struct coresight_platform_dev_subtype {
	enum coresight_dev_subtype_sink sink_subtype;
	enum coresight_dev_subtype_link link_subtype;
	enum coresight_dev_subtype_source source_subtype;
};

struct coresight_platform_data_s {
	int id;
	int cpu;
	const char *name;
	int nr_inports;
	const int *outports;
	const int *child_ids;
	const int *child_ports;
	unsigned int nr_outports;
	bool default_sink;
	struct clk *clk;
};

struct coresight_platform_desc_s {
	enum coresight_platform_dev_type type;
	struct coresight_platform_dev_subtype subtype;
	const struct coresight_platform_ops *ops;
	struct coresight_platform_data_s *pdata;
    void* drvdata;
};

struct coresight_connection_info_s {
	int outport;
	int child_id;
	int child_port;
	struct coresight_platform_device_s *child_dev;
	struct list_head link;
};

struct coresight_reference_count_s {
	int sink_refcnt;
	int *link_refcnts;
	int source_refcnt;
};

struct coresight_platform_device_s {
	int id;
	struct coresight_connection_info_s *conns;
	unsigned int nr_conns;
	enum coresight_platform_dev_type type;
	struct coresight_platform_dev_subtype subtype;
	const struct coresight_platform_ops *ops;
    void* drvdata;
	struct coresight_reference_count_s refcnt;
	struct list_head dev_link;
	struct list_head path_link;
	bool enable;
};


struct coresight_platform_sink_ops {
	int (*enable)(struct coresight_platform_device_s *device);
	void (*disable)(struct coresight_platform_device_s *device);
	void (*abort)(struct coresight_platform_device_s *device);
};

struct coresight_platform_link_ops {
	int (*enable)(struct coresight_platform_device_s *device, unsigned int iport, unsigned int oport);
	void (*disable)(struct coresight_platform_device_s *device, unsigned int iport, unsigned int oport);
};

struct coresight_platform_source_ops {
	int (*enable)(struct coresight_platform_device_s *device);
	void (*disable)(struct coresight_platform_device_s *device);
};

struct coresight_platform_ops {
	const struct coresight_platform_sink_ops *sink_ops;
	const struct coresight_platform_link_ops *link_ops;
	const struct coresight_platform_source_ops *source_ops;
};

/*coresight reg readl & writel*/
#define coresight_readl(base,off)        (*(volatile unsigned int*)((unsigned int)base + off))
#define coresight_writel(base,val,off)   (*(volatile unsigned int*)((unsigned int)base + off) = (val))

#ifdef CONFIG_CORESIGHT
extern struct coresight_platform_device_s *coresight_platform_device_register(struct coresight_platform_desc_s *desc);
extern void coresight_platform_device_unregister(struct coresight_platform_device_s *device);
extern int coresight_platform_device_enable(struct coresight_platform_device_s *device);
extern void coresight_platform_device_disable(struct coresight_platform_device_s *device);
extern void coresight_platform_device_abort(void);
extern struct clk *coresight_get_clk(void);
#else
static inline struct coresight_platform_device_s *
coresight_platform_device_register(struct coresight_platform_desc_s *desc) { return NULL; }
static inline void coresight_platform_device_unregister(struct coresight_platform_device_s *device) {}
static inline int coresight_platform_device_enable(struct coresight_platform_device_s *device) { return -22; }
static inline void coresight_platform_device_disable(struct coresight_platform_device_s *device) {}
static inline void coresight_platform_device_abort(void) {}
extern struct clk *coresight_get_clk(void) {};
#endif

#ifdef CONFIG_CORESIGHT_SOURCE_ETM
extern unsigned int etm_readl_cp14(uint32_t off);
extern void etm_writel_cp14(uint32_t val, uint32_t off);
#else
static inline unsigned int etm_readl_cp14(uint32_t off) { return 0; }
static inline void etm_writel_cp14(uint32_t val, uint32_t off) {}
#endif

#endif
