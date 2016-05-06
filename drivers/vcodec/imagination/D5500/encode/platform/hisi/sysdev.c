/*************************************************************************/ /*!
@File           sysdev.c
@Title          Platform-specific implementation of SYSDEV backend
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@Description    Implementation for hisi.
@License        Strictly Confidential.
*/ /**************************************************************************/
#include <asm/io.h>
#include <asm/page.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/kobject.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>

#include <system.h>
#include <sysmem_utils.h>
#include <sysdev_utils.h>

#define DEVICE_NAME "DT_device"
#define REGULTOR_OPEN 1
static int module_irq = -1;
static IMG_PHYSADDR module_reg_base = 0;
static unsigned int module_reg_size = 0;
static void* reg_base_addr;
/* Device information...*/
static SYSDEVU_sInfo *gpsInfo = IMG_NULL;
static bool device_detected = IMG_FALSE;
struct clk *clk;
unsigned long  enc_clk_rate = 0;

struct regulator *gvenc_regulator;
int driver_probe(struct platform_device *ofdev);

static const struct of_device_id venc_of_match[] = {
	{ .compatible = "hisi,kirin950-venc", },
	{ }
};

static struct platform_driver local_driver = {
    .probe = driver_probe,
    .driver = {
        .name = "goldfish_msvxe",
	    .owner = THIS_MODULE,
	    .of_match_table = venc_of_match
     },
};
#if 1
#define PERI_CRG (0xFFF35000)
#define SCTRL (0xFFF0A000)
#define PMC (0xFFF31000)

//unsigned int val = 0;
//u8 __iomem *reset_mmio_PERI_CRG = NULL;
//reset_mmio_PERI_CRG = ioremap(0xfff35000,4);
//u8 __iomem *reset_mmio_PMC = NULL;
//reset_mmio_PMC= ioremap(0xfff31000,4);

void power_on_encode(int isDec)
{
    unsigned int val =  0;
    unsigned int val2 =  0;
    unsigned int val3 =  0;

    writel(0xe0000060,(ioremap(PERI_CRG,4) + 0x00));/*íaéèê±?óê1?ü*/
    writel(0xe018,(ioremap(PERI_CRG,4) + 0x64));

    val = readl(ioremap(PMC,4) + 0x380);
    //val &= (~(0x1<<4));
    //writel(val,(ioremap(PMC,4) + 0x380));/*????VCODEC_SUBSYSí?3?μí1|o??￡ê?*/
	writel(0x00100000,(ioremap(PMC,4) + 0x380));/*配置VCODEC_SUBSYS退出低功耗模式*/
    do
    {
        val = readl(ioremap(PMC,4) + 0x384);
        val &= (0x01<<4);
    }while(val);              /*2é?ˉí?3????óê?·?±??ìó|*/
    do
    {
        val = readl(ioremap(PMC,4) + 0x388);
        val &= (0x01<<4);
    }while(val);         /*è·è?VCODEC_SUBSYSò?í?3?μí1|o??￡ê?*/

    if(isDec)
    {
        writel(0x04,(ioremap(PERI_CRG,4) + 0x150));/*MTCMOSê1?ü*/
        writel(0x800,(ioremap(PERI_CRG,4) + 0x30));/*?a??VENCoíNOC_VENCê±?ó*/
        writel(0x04,(ioremap(PERI_CRG,4) + 0x148));/*ISOè￥ê1?ü*/
        writel(0x200,(ioremap(PERI_CRG,4) + 0x88));/*?a?′??*/

        val = readl(ioremap(PMC,4) + 0x380);
        val &= (~(0x1<<10));
	 writel(val,(ioremap(PMC,4) + 0x380));/*????NOC VDECí?3?μí1|o??￡ê?*/
        do
        {
            val = readl(ioremap(PMC,4) + 0x384);
            val &= (0x01<<10);
        }while(val);              //2é?ˉ???óê?·?±??ìó|
        do
        {
            val = readl(ioremap(PMC,4) + 0x388);
            val &= (0x01<<10);
        }while(val);         /*???ˉPMC?DNOC_POWER_IDLEACK￡¨0x384￡? bit 10oíNOC_POWER_IDLE￡¨0x388￡? bit 10???a1?ˉb0*/

    }
    else
    {
        writel(0x02,(ioremap(PERI_CRG,4) + 0x150));/*MTCMOSê1?ü*/
	    writel(0x400,(ioremap(PERI_CRG,4) + 0x30));/*?a??VENCoíNOC_VENCê±?ó*/
	    writel(0x02,(ioremap(PERI_CRG,4) + 0x148));	/*ISOè￥ê1?ü*/
        writel(0x100,(ioremap(PERI_CRG,4) + 0x88));/*?a?′??*/

        //val = readl(ioremap(PMC,4) + 0x380);
        //val &= (~(0x1<<11));
        //writel(val,(ioremap(PMC,4) + 0x380));/*????NOC VENCí?3?μí1|o??￡ê?*/
		writel(0x08000000,(ioremap(PMC,4) + 0x380));/*配置NOC VENC退出低功耗模式*/
        do
        {
            val = readl(ioremap(PMC,4) + 0x384);
            val &= (0x01<<11);
        }while(val);              //2é?ˉ???óê?·?±??ìó|

        do
        {
            val = readl(ioremap(PMC,4) + 0x388);
            val &= (0x01<<11);
        }while(val);         /*???ˉPMC?DNOC_POWER_IDLEACK￡¨0x384￡? bit 10oíNOC_POWER_IDLE￡¨0x388￡? bit 10???a1?ˉb0*/

    }

}
#endif
int driver_probe(struct platform_device *ofdev) {
	int ret;
    int err = 0;
	struct resource res;
	IMG_ASSERT(ofdev->resource[0].flags == IORESOURCE_MEM);
	//IMG_ASSERT(ofdev->resource[1].flags == IORESOURCE_IRQ);
      //power_on_encode(0);
	ret = of_address_to_resource(ofdev->dev.of_node, 0, &res);
	if (ret) {
		dev_err(&ofdev->dev, "missing 'reg' property in device tree\n");
		ret = -EINVAL;
		return ret;
	}
	module_reg_base = res.start;
	module_reg_size = resource_size(&res);
	reg_base_addr = of_iomap(ofdev->dev.of_node, 0);
	if (NULL == reg_base_addr) {
		printk("get reg base addr failed\n");
	}
	printk("[vxe] physical address : %llx,reg_size=0x%0x\n", module_reg_base,module_reg_size);

	module_irq = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	if (module_irq == 0) {
		dev_err(&ofdev->dev, "could not map IRQ\n");
		module_reg_base = 0;
		module_reg_size = 0;
		ret = -EINVAL;
		return ret;
	}

    err = of_property_read_u32(ofdev->dev.of_node, "enc_clk_rate", &enc_clk_rate);
    if(err)
    {
        printk(KERN_ERR "can not get enc_clk_rate\n");
    }
    clk = clk_get(NULL,"clk_venc");
    if (IS_ERR_OR_NULL(clk))
    {
        pr_err("clk venc not found!");
        ret = PTR_ERR(clk); return;
    }
    ret = clk_set_rate(clk,enc_clk_rate);
    if (ret)
    {
        printk(KERN_ERR "[ENC]Failed to clk_set_rate %s: %d\n", __func__, ret);
    }

#if REGULTOR_OPEN
		gvenc_regulator = devm_regulator_get(&ofdev->dev, "ldo_venc");
		if (IS_ERR(gvenc_regulator)) {
			printk("[VXE]Couldn't get regulator [%s]! \n", __func__);
			return;
		}
#endif
	
	gpsInfo->native_device = (void *)&ofdev->dev;
	device_detected = IMG_TRUE;
	return 0;
}

static irqreturn_t handle_interrupt(int irq, void *dev_id)
{
	bool handled;
	if ( (gpsInfo != IMG_NULL) && (gpsInfo->pfnDevKmLisr != IMG_NULL) )
	{
		SYSOSKM_DisableInt();
		handled = gpsInfo->pfnDevKmLisr(gpsInfo->pvParam);
		SYSOSKM_EnableInt();
		if (handled)
		{
			/* Signal this...*/
			return IRQ_HANDLED;
		}
	}
	printk("irq end.\n");
	return IRQ_NONE;
}

static void handle_suspend(SYSDEVU_sInfo *dev, IMG_BOOL forAPM)
{
	int ret; 

    if (!forAPM) {
        pr_info("[VXE] %s +\n", __func__);
    }
#if REGULTOR_OPEN
	ret = regulator_disable(gvenc_regulator);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
#endif
    if (!forAPM) {
        pr_info("[VXE] %s -\n", __func__);
    }
}

static void handle_resume(SYSDEVU_sInfo *dev, IMG_BOOL forAPM)
{
	int ret = -1;
    if (!forAPM) {
        pr_info("[VXE] %s +\n", __func__);
    }
#if REGULTOR_OPEN
	ret = regulator_enable(gvenc_regulator);
	if (ret != 0) {
		printk("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
#endif
    if (!forAPM) {
        pr_info("[VXE] %s -\n", __func__);
    }
}


static void free_device(SYSDEVU_sInfo *dev)
{
	if(!device_detected)
		return;

	iounmap(reg_base_addr);
	free_irq(module_irq, gpsInfo);
	platform_driver_unregister(&local_driver);
}

static struct SYSDEV_ops device_ops = {
		.free_device = free_device,

		.resume_device = handle_resume,
		.suspend_device = handle_suspend
};

IMG_RESULT SYSDEVU_RegisterDriver(SYSDEVU_sInfo *sysdev) {
	int ret = 0;

	gpsInfo = sysdev;

	ret = platform_driver_register(&local_driver);
	if (ret != 0) {
		ret = IMG_ERROR_DEVICE_NOT_FOUND;
		goto failure_register;
	}

	if (device_detected != IMG_TRUE) {
		ret = IMG_ERROR_DEVICE_NOT_FOUND;
		goto failure_detect;
	}

	if (request_irq(module_irq, handle_interrupt, 0, DEVICE_NAME, gpsInfo)) {
		printk(KERN_ERR "goldfish_device: Failed to get IRQ\n");
		ret = IMG_ERROR_GENERIC_FAILURE;
		goto failure_request_irq;
	}

	SYSDEVU_SetDevMap(sysdev, module_reg_base, ((IMG_UINT32 *)reg_base_addr), module_reg_size, 0, IMG_NULL, 0, 0);
	SYSDEVU_SetDeviceOps(sysdev, &device_ops);

	ret = SYSMEMKM_AddSystemMemory(sysdev, &sysdev->sMemPool);
	if(IMG_SUCCESS != ret)
	{
		goto failure_add_sys_mem;
	}

	/* Return success...*/
	return IMG_SUCCESS;

failure_add_sys_mem:
failure_request_irq:
	iounmap(reg_base_addr);
failure_detect:
	platform_driver_unregister(&local_driver);
failure_register:
	gpsInfo = IMG_NULL;
	return ret;
}

IMG_RESULT SYSDEVU_UnRegisterDriver(SYSDEVU_sInfo *sysdev) {
	SYSMEMU_RemoveMemoryHeap(sysdev->sMemPool);
	sysdev->ops->free_device(sysdev);
	return IMG_SUCCESS;
}
