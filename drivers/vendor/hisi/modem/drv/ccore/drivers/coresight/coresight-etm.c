/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  Coresight-etm.c
*
*   作    者 :  l00169177
*
*   描    述 :  Embedded Trace Macrocell驱动程序
*
*   修改记录 :  2014年10月24日  v1.00  l00169177  创建
*************************************************************************/
#include <stdio.h>
#include <string.h>
#include "osl_malloc.h"
#include "of.h"
#include "coresight-dts.h"
#include "coresight-platform.h"
#include "bsp_hardtimer.h"
#include "bsp_coresight.h"
#include "securec.h"
/*lint --e{801, 830, 160, 525, 534, 586, 522}*/


#define etm_writel(drvdata, val, off)					\
({									\
	if (drvdata->use_cp14)						\
		etm_writel_cp14(val, off);				\
	else								\
		coresight_writel(drvdata->base, val, off);			\
})
#define etm_readl(drvdata, off)						\
({									\
	u32 val;							\
	if (drvdata->use_cp14)						\
		val = etm_readl_cp14(off);				\
	else								\
		val = coresight_readl(drvdata->base, off);			\
	val;								\
})

#define CORESIGHT_ETM_LOCK(base)						\
do {									\
	/* Recommended by spec to ensure ETM writes are committed */	\
	/* prior to resuming execution */				\
	mb();								\
	isb();								\
	coresight_writel(base, 0x0, CORESIGHT_LAR);			\
} while (0)
#define CORESIGHT_ETM_UNLOCK(base)						\
do {									\
    /*write 0xC5ACCE55 to unlock*/        \
	coresight_writel(base, 0xC5ACCE55, CORESIGHT_LAR);	\
	/* Ensure unlock and any pending writes are committed prior */	\
	/* to programming ETM registers */				\
	mb();								\
	isb();								\
} while (0)

#define PORT_SIZE_MASK		(BM(21, 21) | BM(4, 6))

/*
 * Device registers:
 * 0x000 - 0x2FC: Trace		registers
 * 0x300 - 0x314: Management	registers
 * 0x318 - 0xEFC: Trace		registers
 *
 * Coresight registers
 * 0xF00 - 0xF9C: Management	registers
 * 0xFA0 - 0xFA4: Management	registers in PFTv1.0
 *		  Trace		registers in PFTv1.1
 * 0xFA8 - 0xFFC: Management	registers
 */

/* Trace registers (0x000-0x2FC) */
#define CORESIGHT_ETMCR			    (0x000)
#define CORESIGHT_ETMCCR			(0x004)
#define CORESIGHT_ETMTRIGGER		(0x008)
#define CORESIGHT_ETMSR			    (0x010)
#define CORESIGHT_ETMSCR			(0x014)
#define CORESIGHT_ETMTSSCR		    (0x018)
#define CORESIGHT_ETMTECR2		    (0x01c)
#define CORESIGHT_ETMTEEVR		    (0x020)
#define CORESIGHT_ETMTECR1		    (0x024)
#define CORESIGHT_ETMFFLR			(0x02C)
#define CORESIGHT_ETMACVRn(n)		(0x040 + (n * 4))
#define CORESIGHT_ETMACTRn(n)		(0x080 + (n * 4))
#define CORESIGHT_ETMCNTRLDVRn(n)	(0x140 + (n * 4))
#define CORESIGHT_ETMCNTENRn(n)		(0x150 + (n * 4))
#define CORESIGHT_ETMCNTRLDEVRn(n)	(0x160 + (n * 4))
#define CORESIGHT_ETMCNTVRn(n)		(0x170 + (n * 4))
#define CORESIGHT_ETMSQ12EVR		(0x180)
#define CORESIGHT_ETMSQ21EVR		(0x184)
#define CORESIGHT_ETMSQ23EVR		(0x188)
#define CORESIGHT_ETMSQ31EVR		(0x18C)
#define CORESIGHT_ETMSQ32EVR		(0x190)
#define CORESIGHT_ETMSQ13EVR		(0x194)
#define CORESIGHT_ETMSQR			(0x19C)
#define CORESIGHT_ETMEXTOUTEVRn(n)	(0x1A0 + (n * 4))
#define CORESIGHT_ETMCIDCVRn(n)		(0x1B0 + (n * 4))
#define CORESIGHT_ETMCIDCMR		    (0x1BC)
#define CORESIGHT_ETMIMPSPEC0		(0x1C0)
#define CORESIGHT_ETMIMPSPEC1		(0x1C4)
#define CORESIGHT_ETMIMPSPEC2		(0x1C8)
#define CORESIGHT_ETMIMPSPEC3		(0x1CC)
#define CORESIGHT_ETMIMPSPEC4		(0x1D0)
#define CORESIGHT_ETMIMPSPEC5		(0x1D4)
#define CORESIGHT_ETMIMPSPEC6		(0x1D8)
#define CORESIGHT_ETMIMPSPEC7		(0x1DC)
#define CORESIGHT_ETMSYNCFR		    (0x1E0)
#define CORESIGHT_ETMIDR			(0x1E4)
#define CORESIGHT_ETMCCER			(0x1E8)
#define CORESIGHT_ETMEXTINSELR		(0x1EC)
#define CORESIGHT_ETMTESSEICR		(0x1F0)
#define CORESIGHT_ETMEIBCR		    (0x1F4)
#define CORESIGHT_ETMTSEVR		    (0x1F8)
#define CORESIGHT_ETMAUXCR		    (0x1FC)
#define CORESIGHT_ETMTRACEIDR		(0x200)
#define CORESIGHT_ETMVMIDCVR		(0x240)
/* Management registers (0x300-0x314) */
#define CORESIGHT_ETMOSLAR		    (0x300)
#define CORESIGHT_ETMOSLSR		    (0x304)
#define CORESIGHT_ETMOSSRR		    (0x308)
#define CORESIGHT_ETMPDCR			(0x310)
#define CORESIGHT_ETMPDSR			(0x314)

#define CORESIGHT_ETM_MAX_ADDR_CMP	(16)
#define CORESIGHT_ETM_MAX_CNTR		(4)
#define CORESIGHT_ETM_MAX_CTXID_CMP	(3)

#define CORESIGHT_ETM_MODE_EXCLUDE	    BIT(0)
#define CORESIGHT_ETM_MODE_CYCACC		BIT(1)
#define CORESIGHT_ETM_MODE_STALL		BIT(2)
#define CORESIGHT_ETM_MODE_TIMESTAMP	BIT(3)
#define CORESIGHT_ETM_MODE_CTXID		BIT(4)
#define CORESIGHT_ETM_MODE_ALL		    (0x1F)

#define CORESIGHT_ETM_EVENT_MASK		(0x1FFFF)
#define CORESIGHT_ETM_SYNC_MASK		    (0xFFF)
#define CORESIGHT_ETM_ALL_MASK		    (0xFFFFFFFF)

#define CORESIGHT_ETM_SEQ_STATE_MAX_VAL	(0x2)

#define CORESIGHT_ETM_TRACEID 3

enum coresight_etm_addr_type {
	CORESIGHT_ETM_ADDR_TYPE_NONE,
	CORESIGHT_ETM_ADDR_TYPE_SINGLE,
	CORESIGHT_ETM_ADDR_TYPE_RANGE,
	CORESIGHT_ETM_ADDR_TYPE_START,
	CORESIGHT_ETM_ADDR_TYPE_STOP,
};

struct coresight_etm_drvdata_s {
	void            	        *base;
	struct coresight_platform_device_s		*device;
	struct clk			        *clock;
	spinlock_t			        spinlock;
	int				            cpu;
	int				            port_size;
	u8				            arch;
    u8                          reserved1[3];
	bool				        use_cp14;
	bool				        enable;
	bool				        sticky_enable;
	bool				        boot_enable;
	bool				        os_unlock;
	u8				            nr_addr_cmp;
	u8				            nr_cntr;
	u8				            nr_ext_inp;
	u8				            nr_ext_out;
	u8				            nr_ctxid_cmp;
	u8				            reset;
    u8                          reserved2[2];
	u32			                mode;
	u32			                ctrl;
	u32			                trigger_event;
	u32			                startstop_ctrl;
	u32			                enable_event;
	u32			                enable_ctrl1;
	u32			                fifofull_threshold;
	u8				            addr_idx;
    u8                          reserved3[3];
	u32			                addr_val[CORESIGHT_ETM_MAX_ADDR_CMP];
	u32			                addr_acctype[CORESIGHT_ETM_MAX_ADDR_CMP];
	u32			                addr_type[CORESIGHT_ETM_MAX_ADDR_CMP];
	u8				            cntr_idx;
    u8                          reserved4[3];
	u32			                cntr_rld_val[CORESIGHT_ETM_MAX_CNTR];
	u32			                cntr_event[CORESIGHT_ETM_MAX_CNTR];
	u32			                cntr_rld_event[CORESIGHT_ETM_MAX_CNTR];
	u32			                cntr_val[CORESIGHT_ETM_MAX_CNTR];
	u32			                seq_12_event;
	u32			                seq_21_event;
	u32			                seq_23_event;
	u32			                seq_31_event;
	u32			                seq_32_event;
	u32			                seq_13_event;
	u32			                seq_curr_state;
	u8				            ctxid_idx;
    u8                          reserved5[3];
	u32			                ctxid_val[CORESIGHT_ETM_MAX_CTXID_CMP];
	u32			                ctxid_mask;
	u32			                sync_freq;
	u32			                timestamp_event;
};

#define CORESIGHT_ETM_NUMS 4
static struct coresight_etm_drvdata_s *coresight_etm_drvdata[CORESIGHT_ETM_NUMS];

static void etm_set_pwrdwn(struct coresight_etm_drvdata_s *drvdata)
{
	u32 etm_mcr;

	/* Ensure pending cp14 accesses complete before setting pwrdwn */
	mb();
	isb();
	etm_mcr = etm_readl(drvdata, CORESIGHT_ETMCR);
	etm_mcr |= BIT(0);
	etm_writel(drvdata, etm_mcr, CORESIGHT_ETMCR);
}

static void etm_clr_pwrdwn(struct coresight_etm_drvdata_s *drvdata)
{
	u32 etm_mcr;

	etm_mcr = etm_readl(drvdata, CORESIGHT_ETMCR);
	etm_mcr &= ~BIT(0);
	etm_writel(drvdata, etm_mcr, CORESIGHT_ETMCR);
	/* Ensure pwrup completes before subsequent cp14 accesses */
	mb();
	isb();
}

static void etm_set_prog(struct coresight_etm_drvdata_s *drvdata)
{
	u32 etm_mcr;
	int time;

	etm_mcr = etm_readl(drvdata, CORESIGHT_ETMCR);
	etm_mcr |= BIT(10);
	etm_writel(drvdata, etm_mcr, CORESIGHT_ETMCR);
	/*
	 * after set ETMCR program bit[10] with 1,need to check the statu ETMSR bit
	 * to ensure the status is changed
	 */
	isb();
    time = TIMEOUT_US;
    while(time)
    {
        if(BVAL(etm_readl(drvdata, CORESIGHT_ETMSR), 1) == 1)
            break;
        udelay(1);
        time--;
    }

    if(time == 0)
        cs_error("setting prog bit time out, ETMSR: %#x\n",etm_readl(drvdata, CORESIGHT_ETMSR));

}

static void etm_clr_prog(struct coresight_etm_drvdata_s *drvdata)
{
	u32 etm_mcr;
	int time;

	etm_mcr = etm_readl(drvdata, CORESIGHT_ETMCR);
	etm_mcr &= ~BIT(10);
	etm_writel(drvdata, etm_mcr, CORESIGHT_ETMCR);
	/*
	 * after set ETMCR program bit[10] with 0 ,need to check the statu ETMSR bit
	 * to ensure the status is changed
	 */
	isb();
    time = TIMEOUT_US;
    while(time)
    {
        if(BVAL(etm_readl(drvdata, CORESIGHT_ETMSR), 1) == 0)
            break;
        udelay(1);
        time--;
    }

    if(time == 0)
        cs_error(" clearing prog bit timeout, ETMSR: %#x\n",etm_readl(drvdata, CORESIGHT_ETMSR));
}

static int coresight_etm_enable(struct coresight_platform_device_s *device)
{
	struct coresight_etm_drvdata_s *drvdata = (struct coresight_etm_drvdata_s*)device->drvdata;
    u32 etm_mcr;

	CORESIGHT_ETM_UNLOCK(drvdata->base);

    /* turn engine on */
	etm_clr_pwrdwn(drvdata);

    /* set program bit */
    etm_set_prog(drvdata);

    /* set trace id */
    etm_writel(drvdata, CORESIGHT_ETM_TRACEID, CORESIGHT_ETMTRACEIDR);

    /* monitor all */
    etm_writel(drvdata, 0x376f, CORESIGHT_ETMTEEVR);
    etm_writel(drvdata, 0x01000000, CORESIGHT_ETMTECR1);
    etm_writel(drvdata, 0x406f, CORESIGHT_ETMTRIGGER);

    /* set timestamp event */
    etm_writel(drvdata, 0x406f, CORESIGHT_ETMTSEVR);
    /* disable timestamp event */
    etm_mcr = etm_readl(drvdata, CORESIGHT_ETMCR);
    etm_mcr &= ~(BIT(28));
    etm_writel(drvdata, etm_mcr, CORESIGHT_ETMCR);

    /* set context id */
    etm_mcr = etm_readl(drvdata, CORESIGHT_ETMCR);
    etm_mcr |= BIT(14) | BIT(15);
    etm_writel(drvdata, etm_mcr, CORESIGHT_ETMCR);

    /* set sysnc requency */
    etm_writel(drvdata, 0x400, CORESIGHT_ETMSYNCFR);

    etm_clr_prog(drvdata);
	CORESIGHT_ETM_LOCK(drvdata->base);

	drvdata->enable = true;
	drvdata->sticky_enable = true;

	return 0;
}

static void coresight_etm_disable(struct coresight_platform_device_s *device)
{
	struct coresight_etm_drvdata_s *drvdata = (struct coresight_etm_drvdata_s*)device->drvdata;

    CORESIGHT_ETM_UNLOCK(drvdata->base);
    /*
	 * Executing __coresight_etm_disable on the cpu whose ETM is being disabled
	 * ensures that register writes occur when cpu is powered.
	 */

	etm_set_prog(drvdata);

	/* Program trace enable to low by using always false event */
	etm_writel(drvdata, 0x6F | BIT(14), CORESIGHT_ETMTEEVR);

	etm_set_pwrdwn(drvdata);

	CORESIGHT_ETM_LOCK(drvdata->base);

	/* dev_dbg(drvdata->dev, "cpu: %d disable smp call done\n", drvdata->cpu); */
	drvdata->enable = false;
}

static const struct coresight_platform_source_ops coresight_etm_source_ops = {
	.enable		= coresight_etm_enable,
	.disable	= coresight_etm_disable,
};

static const struct coresight_platform_ops coresight_etm_cs_ops = {
	.source_ops	= &coresight_etm_source_ops,
};

static struct of_device_id coresight_etm_match[] = {
	{.compatible = "arm,coresight"},
	{}
};

struct coresight_platform_data_s *coresight_etm_pdata = NULL;
struct coresight_platform_desc_s *coresight_etm_desc = NULL;
struct device_node* coresight_etm_node    = NULL;

int coresight_etm_init(void)
{
    struct device_node * coresight_node;
    struct device_node * child;
    const char * node_name;
    struct coresight_etm_drvdata_s *  drvdata = NULL;

    coresight_node = of_find_compatible_node(NULL, NULL, coresight_etm_match[0].compatible);
    if(NULL == coresight_node)
    {
        cs_error(" find coresight node failed.\r\n");
        return BSP_ERROR;
    }

    for_each_child_of_node(coresight_node, child)
    {
        if(0 == of_property_read_string(child, "coresight-name", &node_name))
        {
            if(0 == strncmp("coresight-ptm-cp", node_name, sizeof("coresight-ptm-cp")))
            {
                coresight_etm_node = child;
            }
        }
    }

    if(NULL == coresight_etm_node)
    {
        cs_error("of_find_compatible_node failed.\r\n");
        return BSP_ERROR;
    }

    drvdata = osl_malloc(sizeof(struct coresight_etm_drvdata_s));
	if (!drvdata)
	{
        cs_error(" malloc drvdata failded.\r\n");
		return BSP_ERROR;
	}
    memset_s(drvdata, sizeof(struct coresight_etm_drvdata_s), 0, sizeof(struct coresight_etm_drvdata_s));

    coresight_etm_pdata = of_get_coresight_platform_cfg(coresight_etm_node);
    if(!coresight_etm_pdata)
    {
        cs_error("of_get_coresight_platform failed.\r\n");
        goto err0;
    }
    drvdata->use_cp14 = of_property_read_bool(coresight_etm_node, "arm,cp14");

    drvdata->base = (void *)of_iomap(coresight_etm_node, 0);
	if (NULL == drvdata->base)
	{
		cs_error("of_iomap failed.\r\n");
		goto err0;
	}
	spin_lock_init(&drvdata->spinlock);

	drvdata->cpu = coresight_etm_pdata->cpu;

	coresight_etm_drvdata[CP_CORE_SET] = drvdata;

    coresight_etm_desc = osl_malloc(sizeof(*coresight_etm_desc));
    if (!coresight_etm_desc)
	{
        cs_error("malloc desc failded.\r\n");
		goto err0;
	}
    memset_s(coresight_etm_desc, sizeof(*coresight_etm_desc), 0, sizeof(*coresight_etm_desc));

	coresight_etm_desc->type = CORESIGHT_DEV_TYPE_SOURCE;
	coresight_etm_desc->subtype.source_subtype = CORESIGHT_DEV_SUBTYPE_SOURCE_PROC;
	coresight_etm_desc->ops = &coresight_etm_cs_ops;
	coresight_etm_desc->pdata = coresight_etm_pdata;
    coresight_etm_desc->drvdata = drvdata;
	drvdata->device = coresight_platform_device_register(coresight_etm_desc);
	if (!drvdata->device)
    {
        cs_error("coresight_platform_device_register failed.\r\n");
        goto err1;
	}

#ifdef CONFIG_CORESIGHT_SOURCE_ETM_DEFAULT_ENABLE
	coresight_platform_device_enable(drvdata->device);/* [false alarm]:fortify */
	drvdata->boot_enable = true;
#endif
    cs_error(" ok!\n");

	return BSP_OK;
err1:
    osl_free(coresight_etm_desc);
    coresight_etm_desc = NULL;
err0:
    osl_free(drvdata);
    return BSP_ERROR;
}

int coresight_etm_cpu_enable(unsigned int cpu)
{
    if(coresight_etm_drvdata[cpu])
        return coresight_platform_device_enable(coresight_etm_drvdata[cpu]->device);
    return -1;
}

void coresight_etm_cpu_disable(unsigned int cpu)
{
    if(coresight_etm_drvdata[cpu])
        coresight_platform_device_disable(coresight_etm_drvdata[cpu]->device);
}

