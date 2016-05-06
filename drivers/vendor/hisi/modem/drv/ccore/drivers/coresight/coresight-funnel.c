/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  Coresight-funnel.c
*
*   作    者 :  l00169177
*
*   描    述 :  funnel驱动程序
*
*   修改记录 :  2014年10月24日  v1.00  l00169177  创建
*************************************************************************/


#include <stdio.h>
#include "osl_malloc.h"
#include "of.h"
#include "coresight-dts.h"
#include "coresight-platform.h"
#include "securec.h"
/*lint --e{801, 830, 539, 534, 586, 522}*/


#define CORESIGHT_FUNNEL_LOCK(base)						\
do {									\
	/* wait for things to settle */					\
	mb();								\
	coresight_writel(base, 0x0, CORESIGHT_LAR);			\
} while (0)
#define CORESIGHT_FUNNEL_UNLOCK(base)					\
do {									\
    /*write 0xC5ACCE55 to unlock*/        \
	coresight_writel(base, 0xC5ACCE55, CORESIGHT_LAR);	\
	/* make sure everyone has seen this */				\
	mb();								\
} while (0)

#define CORESIGHT_FUNNEL_FUNCTL		(0x000)
#define CORESIGHT_FUNNEL_PRICTL		(0x004)

#define CORESIGHT_FUNNEL_HOLDTIME_MASK	(0xF00)
#define CORESIGHT_FUNNEL_HOLDTIME_SHFT	(0x8)
#define CORESIGHT_FUNNEL_HOLDTIME		(0x7 << CORESIGHT_FUNNEL_HOLDTIME_SHFT)

struct coresight_funnel_drvdata_s {
	void		                *base;
	struct coresight_platform_device_s	    *device;
	struct clk		            *clk;
	u32		            priority;
};

static int coresight_funnel_enable(struct coresight_platform_device_s *device, unsigned int inport,
			 unsigned int outport)
{
	struct coresight_funnel_drvdata_s *drvdata = (struct coresight_funnel_drvdata_s*)device->drvdata;
	unsigned int functl;

	CORESIGHT_FUNNEL_UNLOCK(drvdata->base);

	functl = coresight_readl(drvdata->base, CORESIGHT_FUNNEL_FUNCTL);
	functl &= ~CORESIGHT_FUNNEL_HOLDTIME_MASK;
	functl |= CORESIGHT_FUNNEL_HOLDTIME;
	functl |= ((unsigned int)1 << inport);
	coresight_writel(drvdata->base, functl, CORESIGHT_FUNNEL_FUNCTL);
	coresight_writel(drvdata->base, drvdata->priority, CORESIGHT_FUNNEL_PRICTL);

	CORESIGHT_FUNNEL_LOCK(drvdata->base);
	return 0;
}

static void coresight_funnel_disable(struct coresight_platform_device_s *device, unsigned int inport,
			   unsigned int outport)
{
	struct coresight_funnel_drvdata_s *drvdata = (struct coresight_funnel_drvdata_s*)device->drvdata;
	unsigned int functl;

	CORESIGHT_FUNNEL_UNLOCK(drvdata->base);

	functl = coresight_readl(drvdata->base, CORESIGHT_FUNNEL_FUNCTL);
	functl &= ~((unsigned int)1 << inport);
	coresight_writel(drvdata->base, functl, CORESIGHT_FUNNEL_FUNCTL);

	CORESIGHT_FUNNEL_LOCK(drvdata->base);
}

static const struct coresight_platform_link_ops coresight_funnel_link_ops = {
	.enable		= coresight_funnel_enable,
	.disable	= coresight_funnel_disable,
};

static const struct coresight_platform_ops coresight_funnel_cs_ops = {
	.link_ops	= &coresight_funnel_link_ops,
};

static struct of_device_id coresight_funnel_match[] = {
	{.compatible = "arm,coresight-funnel"},
	{}
};


struct coresight_platform_data_s *coresight_funnel_pdata = NULL;
struct coresight_funnel_drvdata_s *coresight_funnel_drvdata = NULL;
struct coresight_platform_desc_s *coresight_funnel_desc    = NULL;
struct device_node* coresight_funnel_node       = NULL;
int coresight_funnel_init(void)
{
    coresight_funnel_node = of_find_compatible_node(NULL, NULL, coresight_funnel_match[0].compatible);
    if(NULL == coresight_funnel_node)
    {
        cs_error("no funnel config\n");
        return BSP_OK;
    }

	coresight_funnel_pdata = of_get_coresight_platform_cfg(coresight_funnel_node);
	if (IS_ERR(coresight_funnel_pdata))
        return PTR_ERR(coresight_funnel_pdata);

    coresight_funnel_drvdata = osl_malloc(sizeof(*coresight_funnel_drvdata));
    if (!coresight_funnel_drvdata)
	{
        cs_error("error: malloc drvdata failded.\r\n");
		return BSP_ERROR;
	}
    memset_s(coresight_funnel_drvdata, sizeof(*coresight_funnel_drvdata), 0, sizeof(*coresight_funnel_drvdata));

    coresight_funnel_drvdata->base = (void *)of_iomap(coresight_funnel_node, 0);
	if (NULL == coresight_funnel_drvdata->base)
	{
		cs_error("error: of_iomap failed.\r\n");
		goto err0;
	}

/*
	if (coresight_funnel_pdata && coresight_funnel_pdata->clk)
		drvdata->clk = coresight_funnel_pdata->clk;
*/
	coresight_funnel_desc = osl_malloc(sizeof(*coresight_funnel_desc));
    if (!coresight_funnel_desc)
	{
        cs_error("error: malloc desc failded.\r\n");
		goto err0;
	}
    memset_s(coresight_funnel_desc, sizeof(*coresight_funnel_desc), 0, sizeof(*coresight_funnel_desc));

	coresight_funnel_desc->type = CORESIGHT_DEV_TYPE_LINK;
	coresight_funnel_desc->subtype.link_subtype = CORESIGHT_DEV_SUBTYPE_LINK_MERG;
	coresight_funnel_desc->ops = &coresight_funnel_cs_ops;
	coresight_funnel_desc->pdata = coresight_funnel_pdata;
    coresight_funnel_desc->drvdata = coresight_funnel_drvdata;
	coresight_funnel_drvdata->device = coresight_platform_device_register(coresight_funnel_desc);
	if (!coresight_funnel_drvdata->device)
		goto err1;
    cs_error(" ok.\n");
	return BSP_OK;

err1:
    osl_free(coresight_funnel_desc);
    coresight_funnel_desc = NULL;
err0:
    osl_free(coresight_funnel_drvdata);
    coresight_funnel_drvdata = NULL;
    return BSP_ERROR;
}


