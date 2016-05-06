/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  Coresight-tmc.c
*
*   作    者 :  l00169177
*
*   描    述 :  Trace memory controller驱动程序
*
*   修改记录 :  2014年10月24日  v1.00  l00169177  创建
*************************************************************************/
#include <stdio.h>
#include "securec.h"
#include "coresight-platform.h"
#include "coresight-dts.h"
#include "bsp_hardtimer.h"
/*lint --e{801, 830, 539, 525, 534, 586, 522}*/

#define CORESIGHT_TMC_LOCK(base)						\
do {									\
	/* settle everything first */					\
	mb();								\
	coresight_writel(base, 0x0, CORESIGHT_LAR);			\
} while (0)
#define CORESIGHT_TMC_UNLOCK(base)						\
do {									\
    /*write 0xC5ACCE55 to unlock*/        \
	coresight_writel(base, 0xC5ACCE55, CORESIGHT_LAR);		\
	/* make sure everyone sees this */				\
	mb();								\
} while (0)

#define CORESIGHT_TMC_RSZ			(0x004)
#define CORESIGHT_TMC_STS			(0x00C)
#define CORESIGHT_TMC_RRD			(0x010)
#define CORESIGHT_TMC_RRP			(0x014)
#define CORESIGHT_TMC_RWP			(0x018)
#define CORESIGHT_TMC_TRG			(0x01C)
#define CORESIGHT_TMC_CTL			(0x020)
#define CORESIGHT_TMC_RWD			(0x024)
#define CORESIGHT_TMC_MODE		    (0x028)
#define CORESIGHT_TMC_LBUFLEVEL		(0x02C)
#define CORESIGHT_TMC_CBUFLEVEL		(0x030)
#define CORESIGHT_TMC_BUFWM		    (0x034)
#define CORESIGHT_TMC_RRPHI		    (0x038)
#define CORESIGHT_TMC_RWPHI		    (0x03C)
#define CORESIGHT_TMC_AXICTL		(0x110)
#define CORESIGHT_TMC_DBALO		    (0x118)
#define CORESIGHT_TMC_DBAHI		    (0x11C)
#define CORESIGHT_TMC_FFSR		    (0x300)
#define CORESIGHT_TMC_FFCR		    (0x304)
#define CORESIGHT_TMC_PSCR		    (0x308)
#define CORESIGHT_TMC_ITMISCOP0		(0xEE0)
#define CORESIGHT_TMC_ITTRFLIN		(0xEE8)
#define CORESIGHT_TMC_ITATBDATA0	(0xEEC)
#define CORESIGHT_TMC_ITATBCTR2		(0xEF0)
#define CORESIGHT_TMC_ITATBCTR1		(0xEF4)
#define CORESIGHT_TMC_ITATBCTR0		(0xEF8)

#define BYTES_PER_WORD		4
#define BUFFER_EXT_SIZE     16  /* extend buffer size for tmc int ETB*/

enum coresight_tmc_config_type {
	CORESIGHT_TMC_CONFIG_TYPE_ETB,
	CORESIGHT_TMC_CONFIG_TYPE_ETR,
	CORESIGHT_TMC_CONFIG_TYPE_ETF,
};

enum coresight_tmc_mode {
	CORESIGHT_TMC_MODE_CIRCULAR_BUFFER,
	CORESIGHT_TMC_MODE_SOFTWARE_FIFO,
	CORESIGHT_TMC_MODE_HARDWARE_FIFO,
};

enum coresight_tmc_mem_intf_width {
	CORESIGHT_TMC_MEM_INTF_WIDTH_32BITS	    = 0x2,
	CORESIGHT_TMC_MEM_INTF_WIDTH_64BITS	    = 0x3,
	CORESIGHT_TMC_MEM_INTF_WIDTH_128BITS	= 0x4,
	CORESIGHT_TMC_MEM_INTF_WIDTH_256BITS	= 0x5,
};

struct coresight_tmc_drvdata_s {
	void		            *base;
	struct coresight_platform_device_s	*device;
	struct clk		        *clk;
	spinlock_t		        spinlock;
	int			            read_count;
	bool			        reading;
	char			        *buf;
	u32		                paddr;
	void		            *vaddr;
	u32		                size;
	bool			        enable;
	enum coresight_tmc_config_type	config_type;
	u32		                trigger_cntr;
};

u32 coresight_tmc_data_addr = 0;
u32 coresight_tmc_data_len  = 0;

static void tmc_wait_ready(struct coresight_tmc_drvdata_s *drvdata)
{
	int count;

	/* Ensure formatter, unformatter and hardware fifo are empty */
	for (count = TIMEOUT_US; BVAL((coresight_readl(drvdata->base, CORESIGHT_TMC_STS)), 2) != 1
				&& count > 0; count--)
		udelay(1);
    /*
	WARN(count == 0, "timeout while waiting for TMC ready, CORESIGHT_TMC_STS: %#x\n",
	     coresight_readl(drvdata->base, CORESIGHT_TMC_STS));
	*/
}

static void tmc_stop_and_flush(struct coresight_tmc_drvdata_s *drvdata)
{
	int count;
	u32 ffcr;

	ffcr = coresight_readl(drvdata->base, CORESIGHT_TMC_FFCR);
	ffcr |= BIT(12);
	coresight_writel(drvdata->base, ffcr, CORESIGHT_TMC_FFCR);
	ffcr |= BIT(6);
	coresight_writel(drvdata->base, ffcr, CORESIGHT_TMC_FFCR);
	/* Ensure flush completes */
	for (count = TIMEOUT_US; BVAL((coresight_readl(drvdata->base, CORESIGHT_TMC_FFCR)), 6) != 0
				&& count > 0; count--)
		udelay(1);
    /*
	WARN(count == 0, "timeout while flushing TMC, CORESIGHT_TMC_FFCR: %#x\n",
	     coresight_readl(drvdata->base, CORESIGHT_TMC_FFCR));
    */
	tmc_wait_ready(drvdata);

}

static void tmc_enable_etb(struct coresight_tmc_drvdata_s *drvdata)
{
	/* Zero out the memory to help with debug */
	memset_s(drvdata->buf, drvdata->size, 0, drvdata->size);

	CORESIGHT_TMC_UNLOCK(drvdata->base);

	coresight_writel(drvdata->base, CORESIGHT_TMC_MODE_CIRCULAR_BUFFER, CORESIGHT_TMC_MODE);
	coresight_writel(drvdata->base, 0x133, CORESIGHT_TMC_FFCR);
	coresight_writel(drvdata->base, drvdata->trigger_cntr, CORESIGHT_TMC_TRG);

    /*enable tmc*/
	coresight_writel(drvdata->base, 0x1, CORESIGHT_TMC_CTL);

	CORESIGHT_TMC_LOCK(drvdata->base);
}

static void tmc_enable_etr(struct coresight_tmc_drvdata_s *drvdata)
{
	u32 axictl;

	/* Zero out the memory to help with debug */
	memset_s(drvdata->vaddr, drvdata->size, 0, drvdata->size);

	CORESIGHT_TMC_UNLOCK(drvdata->base);

	coresight_writel(drvdata->base, drvdata->size / BYTES_PER_WORD, CORESIGHT_TMC_RSZ);
	coresight_writel(drvdata->base, CORESIGHT_TMC_MODE_CIRCULAR_BUFFER, CORESIGHT_TMC_MODE);

	axictl = coresight_readl(drvdata->base, CORESIGHT_TMC_AXICTL);
	axictl |= (0xF << 8);
	coresight_writel(drvdata->base, axictl, CORESIGHT_TMC_AXICTL);
	axictl &= ~(0x1 << 7);
	coresight_writel(drvdata->base, axictl, CORESIGHT_TMC_AXICTL);
	axictl = (axictl & ~0x3) | 0x2;
	coresight_writel(drvdata->base, axictl, CORESIGHT_TMC_AXICTL);

	coresight_writel(drvdata->base, drvdata->paddr, CORESIGHT_TMC_DBALO);
	coresight_writel(drvdata->base, 0x0, CORESIGHT_TMC_DBAHI);
	coresight_writel(drvdata->base, 0x133, CORESIGHT_TMC_FFCR);
	coresight_writel(drvdata->base, drvdata->trigger_cntr, CORESIGHT_TMC_TRG);
    /*enable tmc*/
	coresight_writel(drvdata->base, 0x1, CORESIGHT_TMC_CTL);

	CORESIGHT_TMC_LOCK(drvdata->base);
}

static void tmc_enable_etf(struct coresight_tmc_drvdata_s *drvdata)
{
	CORESIGHT_TMC_UNLOCK(drvdata->base);

	coresight_writel(drvdata->base, CORESIGHT_TMC_MODE_HARDWARE_FIFO, CORESIGHT_TMC_MODE);
	coresight_writel(drvdata->base, 0x3, CORESIGHT_TMC_FFCR);
	coresight_writel(drvdata->base, 0x0, CORESIGHT_TMC_BUFWM);
    /*enable tmc*/
	coresight_writel(drvdata->base, 0x1, CORESIGHT_TMC_CTL);

	CORESIGHT_TMC_LOCK(drvdata->base);
}

static void tmc_dump_etb(struct coresight_tmc_drvdata_s *drvdata)
{
	enum coresight_tmc_mem_intf_width memwidth;
	u8 memwords;
	char *bufp;
	u32 read_data;
	int i;

	memwidth = BMVAL((coresight_readl(drvdata->base, CORESIGHT_DEVID)), 8, 10);
	if (memwidth == CORESIGHT_TMC_MEM_INTF_WIDTH_32BITS)
		memwords = 1;
	else if (memwidth == CORESIGHT_TMC_MEM_INTF_WIDTH_64BITS)
		memwords = 2;
	else if (memwidth == CORESIGHT_TMC_MEM_INTF_WIDTH_128BITS)
		memwords = 4;
	else
		memwords = 8;

    coresight_tmc_data_addr =(u32)drvdata->buf;

	bufp = drvdata->buf;
	while (1) {
		for (i = 0; i < memwords; i++) {
			read_data = coresight_readl(drvdata->base, CORESIGHT_TMC_RRD);
			if (read_data == 0xFFFFFFFF)
			{
                coresight_tmc_data_len = (u32)(bufp - drvdata->buf);
				return;
			}
			memcpy_s(bufp, BYTES_PER_WORD, &read_data, BYTES_PER_WORD);
			bufp += BYTES_PER_WORD;

            if(bufp > (drvdata->buf+drvdata->size))
            {
                //cs_error("_tmc_etb_dump error: read CORESIGHT_TMC_RDD longer than buffer size.\n");
                return;
            }
		}
	}
}
extern u32 g_cs_suspend;
static void tmc_disable_etb(struct coresight_tmc_drvdata_s *drvdata)
{
	CORESIGHT_TMC_UNLOCK(drvdata->base);

	tmc_stop_and_flush(drvdata);
    if(!g_cs_suspend)
    {
	    tmc_dump_etb(drvdata);
    }

    /*disable tmc*/
    coresight_writel(drvdata->base, 0x0, CORESIGHT_TMC_CTL);

	CORESIGHT_TMC_LOCK(drvdata->base);
}

static void tmc_dump_etr(struct coresight_tmc_drvdata_s *drvdata)
{
	u32 rwp;
	rwp = coresight_readl(drvdata->base, CORESIGHT_TMC_RWP);

	if (BVAL((coresight_readl(drvdata->base, CORESIGHT_TMC_STS)), 0))
		drvdata->buf = (char*)drvdata->vaddr + rwp - drvdata->paddr;
	else
		drvdata->buf = drvdata->vaddr;
}

static void tmc_disable_etr(struct coresight_tmc_drvdata_s *drvdata)
{
	CORESIGHT_TMC_UNLOCK(drvdata->base);

	tmc_stop_and_flush(drvdata);
	tmc_dump_etr(drvdata);

    /*disable tmc*/
    coresight_writel(drvdata->base, 0x0, CORESIGHT_TMC_CTL);

	CORESIGHT_TMC_LOCK(drvdata->base);
}

static void tmc_disable_etf(struct coresight_tmc_drvdata_s *drvdata)
{
	CORESIGHT_TMC_UNLOCK(drvdata->base);

	tmc_stop_and_flush(drvdata);

    /*disable tmc*/
    coresight_writel(drvdata->base, 0x0, CORESIGHT_TMC_CTL);

	CORESIGHT_TMC_LOCK(drvdata->base);
}

static int coresight_tmc_enable(struct coresight_tmc_drvdata_s *drvdata, enum coresight_tmc_mode mode)
{
	if (drvdata->reading) {
		return -EBUSY;
	}

	if (drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETB) {
		tmc_enable_etb(drvdata);
	} else if (drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETR) {
		tmc_enable_etr(drvdata);
	} else {
		if (mode == CORESIGHT_TMC_MODE_CIRCULAR_BUFFER)
		{
			tmc_enable_etb(drvdata);
		}
		else
		{
			tmc_enable_etf(drvdata);
		}
	}
	drvdata->enable = true;

	return 0;
}

static int coresight_tmc_enable_sink(struct coresight_platform_device_s *device)
{
	struct coresight_tmc_drvdata_s *drvdata = (struct coresight_tmc_drvdata_s*)device->drvdata;

	return coresight_tmc_enable(drvdata, CORESIGHT_TMC_MODE_CIRCULAR_BUFFER);
}

static int coresight_tmc_enable_link(struct coresight_platform_device_s *device, unsigned int inport,
			   unsigned int outport)
{
	struct coresight_tmc_drvdata_s *drvdata = (struct coresight_tmc_drvdata_s*)device->drvdata;

	return coresight_tmc_enable(drvdata, CORESIGHT_TMC_MODE_HARDWARE_FIFO);
}

static void coresight_tmc_disable(struct coresight_tmc_drvdata_s *drvdata, enum coresight_tmc_mode mode)
{
    if (drvdata->reading)
		goto out;

	if (drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETB) {
		tmc_disable_etb(drvdata);
	} else if (drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETR) {
		tmc_disable_etr(drvdata);
	} else {
		if (mode == CORESIGHT_TMC_MODE_CIRCULAR_BUFFER)
			tmc_disable_etb(drvdata);
		else
			tmc_disable_etf(drvdata);
	}
out:
	drvdata->enable = false;
}

static void coresight_tmc_disable_sink(struct coresight_platform_device_s *device)
{
	struct coresight_tmc_drvdata_s *drvdata = (struct coresight_tmc_drvdata_s*)device->drvdata;;

	coresight_tmc_disable(drvdata, CORESIGHT_TMC_MODE_CIRCULAR_BUFFER);
}

static void coresight_tmc_disable_link(struct coresight_platform_device_s *device, unsigned int inport,
			     unsigned int outport)
{
	struct coresight_tmc_drvdata_s *drvdata = (struct coresight_tmc_drvdata_s*)device->drvdata;;

	coresight_tmc_disable(drvdata, CORESIGHT_TMC_MODE_HARDWARE_FIFO);
}

static void coresight_tmc_abort(struct coresight_platform_device_s *device)
{
	struct coresight_tmc_drvdata_s *drvdata = (struct coresight_tmc_drvdata_s*)device->drvdata;;
	unsigned long flags;
	enum coresight_tmc_mode mode;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	if (drvdata->reading)
		goto out0;

	if (drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETB) {
		tmc_disable_etb(drvdata);
	} else if (drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETR) {
		tmc_disable_etr(drvdata);
	} else {
		mode = coresight_readl(drvdata->base, CORESIGHT_TMC_MODE);
		if (mode == CORESIGHT_TMC_MODE_CIRCULAR_BUFFER)
			tmc_disable_etb(drvdata);
		else
			goto out1;
	}
out0:
	drvdata->enable = false;
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	return;
out1:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
}

static const struct coresight_platform_sink_ops coresight_tmc_sink_ops = {
	.enable		= coresight_tmc_enable_sink,
	.disable	= coresight_tmc_disable_sink,
	.abort		= coresight_tmc_abort,
};

static const struct coresight_platform_link_ops coresight_tmc_link_ops = {
	.enable		= coresight_tmc_enable_link,
	.disable	= coresight_tmc_disable_link,
};

static const struct coresight_platform_ops coresight_tmc_etb_cs_ops = {
	.sink_ops	= &coresight_tmc_sink_ops,
};

static const struct coresight_platform_ops coresight_tmc_etr_cs_ops = {
	.sink_ops	= &coresight_tmc_sink_ops,
};

static const struct coresight_platform_ops coresight_tmc_etf_cs_ops = {
	.sink_ops	= &coresight_tmc_sink_ops,
	.link_ops	= &coresight_tmc_link_ops,
};

static struct of_device_id coresight_tmc_match[] = {
	{.compatible = "arm,coresight-tmc"},
	{}
};

struct coresight_platform_data_s *coresight_tmc_pdata = NULL;
struct coresight_tmc_drvdata_s *coresight_tmc_drvdata = NULL;
struct coresight_platform_desc_s *coresight_tmc_desc = NULL;
struct device_node* coresight_tmc_node    = NULL;
int coresight_tmc_init(void)
{
    int ret = 0;
    u32 device_id;

    coresight_tmc_node = of_find_compatible_node(NULL, NULL, coresight_tmc_match[0].compatible);
    if(NULL == coresight_tmc_node)
    {
        cs_error("error: of_find_compatible_node failed.\r\n");
        return BSP_ERROR;
    }

    coresight_tmc_pdata = of_get_coresight_platform_cfg(coresight_tmc_node);
    if (!coresight_tmc_pdata)
    {
        cs_error("error: of_get_coresight_platform_cfg failed.\r\n");
        return BSP_ERROR;
    }

    coresight_tmc_drvdata = osl_malloc(sizeof(*coresight_tmc_drvdata));
    if(!coresight_tmc_drvdata)
    {
        cs_error("error: malloc coresight_tmc_drvdata failed.\r\n");
        return BSP_ERROR;
    }
    memset_s(coresight_tmc_drvdata, sizeof(*coresight_tmc_drvdata), 0, sizeof(*coresight_tmc_drvdata));

    coresight_tmc_drvdata->base = (void *)of_iomap(coresight_tmc_node, 0);
	if (NULL == coresight_tmc_drvdata->base)
	{
		cs_error("error: of_iomap failed.\r\n");
        osl_free(coresight_tmc_drvdata);
		return BSP_ERROR;
	}

	spin_lock_init(&coresight_tmc_drvdata->spinlock);
	device_id = coresight_readl(coresight_tmc_drvdata->base, CORESIGHT_DEVID);
	coresight_tmc_drvdata->config_type = BMVAL(device_id, 6, 7);

	if (coresight_tmc_drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETR)
    {
        ret = of_property_read_u32(coresight_tmc_node, "arm,buffer-size", &coresight_tmc_drvdata->size);
		if (ret)
			coresight_tmc_drvdata->size = SZ_1M;
	} else {
		coresight_tmc_drvdata->size = coresight_readl(coresight_tmc_drvdata->base, CORESIGHT_TMC_RSZ) * BYTES_PER_WORD;
	}

	if (coresight_tmc_drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETR) {
		coresight_tmc_drvdata->vaddr = osl_cachedma_malloc(coresight_tmc_drvdata->size);
        coresight_tmc_drvdata->paddr = (u32)coresight_tmc_drvdata->vaddr;
		if (!coresight_tmc_drvdata->vaddr)
		{
            cs_error("error: osl_cachedma_malloc failed.\r\n");
			goto err0;
		}
		memset_s(coresight_tmc_drvdata->vaddr, coresight_tmc_drvdata->size, 0, coresight_tmc_drvdata->size);
		coresight_tmc_drvdata->buf = coresight_tmc_drvdata->vaddr;
	} else {
		coresight_tmc_drvdata->buf = osl_malloc(coresight_tmc_drvdata->size);
		if (!coresight_tmc_drvdata->buf)
		{
            cs_error("error: malloc drvdata->buf failed.\r\n");
			goto err0;
		}
        memset_s(coresight_tmc_drvdata->buf, coresight_tmc_drvdata->size, 0, coresight_tmc_drvdata->size);
	}

    coresight_tmc_desc = osl_malloc(sizeof(*coresight_tmc_desc));
	if (!coresight_tmc_desc) {
		cs_error("error: malloc desc failed.\r\n");
		goto err0;
	}
    memset_s(coresight_tmc_desc, sizeof(*coresight_tmc_desc), 0, sizeof(*coresight_tmc_desc));

	if (coresight_tmc_drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETB) {
        cs_error("CORESIGHT_TMC_CONFIG_TYPE_ETB \n");
		coresight_tmc_desc->type = CORESIGHT_DEV_TYPE_SINK;
		coresight_tmc_desc->subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_BUFFER;
		coresight_tmc_desc->ops = &coresight_tmc_etb_cs_ops;
		coresight_tmc_desc->pdata = coresight_tmc_pdata;
        coresight_tmc_desc->drvdata = coresight_tmc_drvdata;
		coresight_tmc_drvdata->device = coresight_platform_device_register(coresight_tmc_desc);
		if (!coresight_tmc_drvdata->device) {
			goto err0;
		}
	} else if (coresight_tmc_drvdata->config_type == CORESIGHT_TMC_CONFIG_TYPE_ETR) {
	    cs_error("CORESIGHT_TMC_CONFIG_TYPE_ETR \n");
		coresight_tmc_desc->type = CORESIGHT_DEV_TYPE_SINK;
		coresight_tmc_desc->subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_BUFFER;
		coresight_tmc_desc->ops = &coresight_tmc_etr_cs_ops;
		coresight_tmc_desc->pdata = coresight_tmc_pdata;
        coresight_tmc_desc->drvdata = coresight_tmc_drvdata;
		coresight_tmc_drvdata->device = coresight_platform_device_register(coresight_tmc_desc);
		if (!coresight_tmc_drvdata->device) {
            goto err0;
		}
	} else {
	    cs_error("CORESIGHT_TMC_CONFIG_TYPE_ETF \n");
		coresight_tmc_desc->type = CORESIGHT_DEV_TYPE_LINKSINK;
		coresight_tmc_desc->subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_BUFFER;
		coresight_tmc_desc->subtype.link_subtype = CORESIGHT_DEV_SUBTYPE_LINK_FIFO;
		coresight_tmc_desc->ops = &coresight_tmc_etf_cs_ops;
		coresight_tmc_desc->pdata = coresight_tmc_pdata;
        coresight_tmc_desc->drvdata = coresight_tmc_drvdata;
		coresight_tmc_drvdata->device = coresight_platform_device_register(coresight_tmc_desc);
		if (!coresight_tmc_drvdata->device) {
			goto err0;
		}
	}
    cs_error(" ok.\n");
	return BSP_OK;
err0:
    if(coresight_tmc_drvdata->paddr)
        osl_cachedma_free((void*)coresight_tmc_drvdata->paddr);
    if(coresight_tmc_drvdata->buf)
        osl_free(coresight_tmc_drvdata->buf);
    if(coresight_tmc_drvdata)
        osl_free(coresight_tmc_drvdata);
    if(coresight_tmc_desc)
        osl_free(coresight_tmc_desc);

	return BSP_ERROR;
}

