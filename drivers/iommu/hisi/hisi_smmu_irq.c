/*
 * hisi_smmu_irq: Common code for smmu interrupt interface.
 *
 * Copyright (C) 2013-2014 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/iommu.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/hisi/hisi-iommu.h>
#include <linux/of.h>
#include <linux/workqueue.h>

#define MODULE_NAME        "smmu-irq"
#define SMMU_REG_PRINT_NUM 32
#define SMMU_NS_INTSTAT    0x28
#define SMMU_NS_INTCLR     0x2C
#define SMMU_EXC_TYPE_NUM  6

#define ISP_SMMU_ERR_WR_OFFSET (0x800)
#define ISP_SMMU_ERR_RD_ADDR   (0xE000)
#define ISP_SMMU_ERR_WR_ADDR   (ISP_SMMU_ERR_RD_ADDR + ISP_SMMU_ERR_WR_OFFSET)
#define ISP_SMMU_ERR_SIZE      (0x1000)

#define ISP_REGBASE_CRGPERI    (0xFFF35000)
#define ISP_SEC_RSTSTAT_OFFSET (0xC88)

struct smmu_irq {
    /*  Lock to protect registers requiring read/modify/write ops. */
    spinlock_t                  lock;
    struct platform_device      *adev;
    int                         irq[2];
    unsigned int                bootware_paddr;
    unsigned int                rderr_paddr;
    unsigned int                wrerr_paddr;
    void __iomem                *smmu_base;
    void __iomem                *mem_base;
    void __iomem                *sec_rststat;
    struct device               *platform_dev;
    void                        *priv;
    void                        *dma;
    void                        *va;
    unsigned int                read_value;
    struct work_struct          my_work;
    unsigned int                base[SMMU_REG_PRINT_NUM];
    unsigned int                value[SMMU_REG_PRINT_NUM];
};

static struct workqueue_struct *my_wq;

typedef enum smmu_int_stat {
    ints_permis_stat      = 1<<0,
    ints_ext_stat         = 1<<1,
    ints_tlbmiss_stat     = 1<<2,
    ints_ptw_trans_stat   = 1<<3,
    ints_ptw_invalid_stat = 1<<4,
    ints_ptw_ns_stat      = 1<<5,
} smmu_inti_stat_e;

typedef enum smmu_int_clr {
    ints_permis_clr      = 1<<0,
    ints_ext_clr         = 1<<1,
    ints_tlbmiss_clr     = 1<<2,
    ints_ptw_trans_clr   = 1<<3,
    ints_ptw_invalid_clr = 1<<4,
    ints_ptw_ns_clr      = 1<<5,
} smmu_inti_clr_e;

static void save_smmu_reg_value(unsigned int start,
    unsigned int end, unsigned int index, struct smmu_irq *isp_smmu_irq)
{
    void __iomem  *uw_loop;
    unsigned int us_loop = isp_smmu_irq->priv + start;

    for (uw_loop = isp_smmu_irq->smmu_base + start; uw_loop <= (isp_smmu_irq->smmu_base + end); uw_loop+=4)
    {
        if(index >= SMMU_REG_PRINT_NUM )
        {
            dev_err(isp_smmu_irq->platform_dev, "save_smmu_reg_value error(j = %d, us_loop = 0x%x)\n", index, us_loop);
            return;
        }
        isp_smmu_irq->base[index]  = us_loop;
        isp_smmu_irq->value[index] = __raw_readl(uw_loop);
        us_loop += 4;
        index++;
    }
}

static void smmu_reg_offset(struct smmu_irq *isp_smmu_irq)
{
    unsigned int end;
    unsigned int start;
    unsigned int num;
    unsigned int index = 0;

    /*print smmu offset 0x200 -0x224 reg value, total 10*/
    start  = 0x200;
    end    = 0x224;
    save_smmu_reg_value(start, end, index, isp_smmu_irq);
    num    = ((end - start) >> 2) + 1;
    index += num;
    
    /*print smmu offset 0x300 -0x318 reg value, total 7*/
    start  = 0x300;
    end    = 0x318;
    save_smmu_reg_value(start, end, index, isp_smmu_irq);
    num    = ((end - start) >> 2) + 1;
    index += num;
    
    /*print smmu offset 0x400 -0x41C reg value, total 8*/
    start  = 0x400;
    end    = 0x41C;
    save_smmu_reg_value(start, end, index, isp_smmu_irq);
    num    = ((end - start) >> 2) + 1;
    index += num;
    
    /*print smmu offset 0x500 -0x518 reg value, total 7*/
    start  = 0x500;
    end    = 0x518;
    save_smmu_reg_value(start, end, index, isp_smmu_irq);
}

static void check_smmu_interrupt_type(unsigned int value, struct smmu_irq *isp_smmu_irq)
{
    void __iomem  *smmu_clr_base = (isp_smmu_irq->smmu_base + SMMU_NS_INTCLR);
     
    switch(value)
    {
        case ints_permis_stat :
            /*clear int*/
            __raw_writel((value | ints_permis_clr), smmu_clr_base);
            dev_err(isp_smmu_irq->platform_dev, "This smmu int is ints_permis_stat\n");
            break;
        case ints_ext_stat :
            /*clear int*/
            __raw_writel((value | ints_ext_clr), smmu_clr_base);
            dev_err(isp_smmu_irq->platform_dev, "This smmu int is ints_ext_stat\n");
            break;
        case ints_tlbmiss_stat :
            /*clear int*/
            __raw_writel((value | ints_tlbmiss_clr), smmu_clr_base);
            dev_err(isp_smmu_irq->platform_dev, "This smmu int is ints_tlbmiss_stat\n");
            break;
        case ints_ptw_trans_stat :
            /*clear int*/
            __raw_writel((value | ints_ptw_trans_clr), smmu_clr_base);
            dev_err(isp_smmu_irq->platform_dev, "This smmu int is ints_ptw_trans_stat\n");
            break;
        case ints_ptw_invalid_stat :
            /*clear int*/
            __raw_writel((value | ints_ptw_invalid_clr), smmu_clr_base);
            dev_err(isp_smmu_irq->platform_dev, "This smmu int is ints_ptw_invalid_stat\n");
            break;
        case ints_ptw_ns_stat :
            /*clear int*/
            __raw_writel((value | ints_ptw_ns_clr), smmu_clr_base);
            dev_err(isp_smmu_irq->platform_dev, "This smmu int is ints_ptw_ns_stat\n");
            break;
        default:
            dev_err(isp_smmu_irq->platform_dev, "Error,this smmu int is not clear,SMMU INT_STAT REG = 0x%x\n", value);
            break;
    }
}

static void isp_smmu_reg_value_print(struct smmu_irq *isp_smmu_irq)
{
    unsigned int v;
    
    dev_err(isp_smmu_irq->platform_dev, "---------------SMMU REG DUMP BEGIN --------------- \n");
    for(v = 0; v < SMMU_REG_PRINT_NUM; v ++)
    {
        dev_err(isp_smmu_irq->platform_dev, "0x%x:0x%08x", isp_smmu_irq->base[v], isp_smmu_irq->value[v]);
    }
    if(isp_smmu_irq->mem_base)
    {
        dev_err(isp_smmu_irq->platform_dev, "0x%x:0x%08x; 0x%x:0x%08x", isp_smmu_irq->rderr_paddr, __raw_readl(isp_smmu_irq->mem_base), 
            isp_smmu_irq->wrerr_paddr, __raw_readl(isp_smmu_irq->mem_base + ISP_SMMU_ERR_WR_OFFSET));
    }
    dev_err(isp_smmu_irq->platform_dev, "---------------SMMU NS INT PARSE END--------------- \n");
    //BUG_ON(v == SMMU_REG_PRINT_NUM);
}

static void smmu_interrupt_status_value_read(struct work_struct *work)
{
    struct smmu_irq *isp_smmu_irq = container_of(work, struct smmu_irq, my_work);
    unsigned int i;

    dev_err(isp_smmu_irq->platform_dev, "---------------SMMU NS INT PARSE BEGIN--------------- \n");
    if(0 == isp_smmu_irq->read_value)
    {
        dev_err(isp_smmu_irq->platform_dev, "read_value is 0 ,there is no any intterupt \n");
    }
    for(i = 0; i < SMMU_EXC_TYPE_NUM; i++)
    {
        if((isp_smmu_irq->read_value >> i) & 0x1)
        {
            check_smmu_interrupt_type(1 << i, isp_smmu_irq);
        }
    }

    /*call isp_smmu_reg_value_print to print some important register value*/
    isp_smmu_reg_value_print(isp_smmu_irq);
}


static irqreturn_t isp_smmu_ns_irq_interrupt(int irq, void *dev_id)
{
    struct smmu_irq *isp_smmu_irq = dev_id;
    unsigned int flags;
    unsigned int rststat_value = 0;
        
    if((NULL == isp_smmu_irq->smmu_base) || (NULL == isp_smmu_irq->mem_base) 
        || (NULL == isp_smmu_irq->sec_rststat))
    {
        return 0;
    }
    /*if isp/a7 is in reset status, can not read smmu reg*/
    rststat_value = __raw_readl(isp_smmu_irq->sec_rststat + ISP_SEC_RSTSTAT_OFFSET);
    if((rststat_value & 0x1) || (rststat_value & 0x10))
    {
        return 0;
    }
    spin_lock_irqsave(&isp_smmu_irq->lock, flags);
    /*call smmu_reg_value_save to save some important register value*/
    smmu_reg_offset(isp_smmu_irq);
   
    /*read SMMU_INTSTAT_NS reg to check which intterups come*/
    isp_smmu_irq->read_value = __raw_readl(isp_smmu_irq->smmu_base + SMMU_NS_INTSTAT);
    queue_work(my_wq, &(isp_smmu_irq->my_work));
    spin_unlock_irqrestore(&isp_smmu_irq->lock, flags);
    
    return 0;
}

static int isp_smmuirq_probe(struct platform_device *pdev)
{
    struct smmu_irq *isp_smmu_irq;
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    struct resource *res;
    unsigned int addr;
    int ret = 0;

    isp_smmu_irq = devm_kzalloc(&pdev->dev, sizeof(struct smmu_irq), GFP_KERNEL);
    if (!isp_smmu_irq) {
        dev_err(&pdev->dev, "mem alloc failed for smmu_irq data\n");
        return -ENOMEM;
    }

    /* NOTE: driver uses the static register mapping */
    res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
    if (!res)
        return -EINVAL;

    /*dts get*/
    if ((ret = of_property_read_u32(np, "isp-smmu-addr", &addr)) < 0 ) {
        dev_err(&pdev->dev, "Failed: isp-smmu-addr of_property_read_u32.%d\n", ret);
        return -EINVAL;
    }

    isp_smmu_irq->priv = (void *)(unsigned long)addr;
    isp_smmu_irq->smmu_base = (void __iomem *)ioremap(isp_smmu_irq->priv, SZ_4K);
    if (!isp_smmu_irq->smmu_base) {
        dev_err(&pdev->dev, "smmu base ioremap is failed \n");
        return -ENOMEM;
    }

    isp_smmu_irq->platform_dev= &pdev->dev;
    /* get irq 0,register smmu_int_ns intterupt*/
    isp_smmu_irq->irq[0]= platform_get_irq(pdev, 0);
    if (isp_smmu_irq->irq[0] < 0) {
        dev_err(&pdev->dev, "no irq resource\n");
        return isp_smmu_irq->irq[0];
    }

    /*add lock init*/
    spin_lock_init(&isp_smmu_irq->lock);
    
    isp_smmu_irq->bootware_paddr = get_a7remap_addr();
    isp_smmu_irq->rderr_paddr = isp_smmu_irq->bootware_paddr + ISP_SMMU_ERR_RD_ADDR;
    isp_smmu_irq->wrerr_paddr = isp_smmu_irq->bootware_paddr + ISP_SMMU_ERR_WR_ADDR;
    /*clear mem addr set into SMMU_ERR_RDADDR/SMMU_ERR_WRADDR in function hisi_smmu_err_reg_set()*/
    isp_smmu_irq->mem_base = (void __iomem *)ioremap_wc(isp_smmu_irq->rderr_paddr, ISP_SMMU_ERR_SIZE); 
    if (!isp_smmu_irq->mem_base) {
        dev_err(&pdev->dev, "0x%x ioremap is failed \n", isp_smmu_irq->rderr_paddr);
        return -ENOMEM;
    }
    memset(isp_smmu_irq->mem_base, 0, ISP_SMMU_ERR_SIZE);

    /*isp and a7 status*/
    isp_smmu_irq->sec_rststat = (void __iomem *)ioremap(ISP_REGBASE_CRGPERI, SZ_4K);
    if (!isp_smmu_irq->sec_rststat) {
        dev_err(&pdev->dev, "sec rststat ioremap is failed \n");
        return -ENOMEM;
    }

    dev_info(&pdev->dev, "########### request_irq: NO. = %d.%d\n",isp_smmu_irq->irq[0],isp_smmu_irq->irq[1]);
    ret = request_irq(isp_smmu_irq->irq[0], isp_smmu_ns_irq_interrupt, IRQF_TRIGGER_RISING, MODULE_NAME, isp_smmu_irq);
    if (ret) {
        dev_err(&pdev->dev, "Failulre requesting irq.\n");
        return -EINVAL;
    }

    my_wq = create_workqueue("my_wq");
    if(!my_wq)
    {
        return -ENOMEM;
    }
    INIT_WORK(&(isp_smmu_irq->my_work), smmu_interrupt_status_value_read);

    return 0;
}

static int isp_smmuirq_remove(struct platform_device *pdev)
{
    platform_set_drvdata(pdev, NULL);
    return 0;
}

static int __maybe_unused smmu_irq_suspend(struct device *dev)
{
    int ret = 0;
    flush_workqueue(my_wq);
    return ret;
}

static int __maybe_unused smmu_irq_resume(struct device *dev)
{
    int ret = 0;

    return ret;
}
static SIMPLE_DEV_PM_OPS(smmu_irq_dev_pm_ops, smmu_irq_suspend,
    smmu_irq_resume);

static struct of_device_id isp_smmu_irq_of_match[] = {
    { .compatible = "hisilicon,smmu-irq"},
    { },
};
MODULE_DEVICE_TABLE(of, isp_smmu_irq_of_match);


struct platform_driver isp_smmuirq_drv = {
    .probe = isp_smmuirq_probe,
    .remove = isp_smmuirq_remove,
    .driver = {
        .owner          = THIS_MODULE,
        .name           = "smmu-irq",
        .of_match_table = of_match_ptr(isp_smmu_irq_of_match),
        .pm             = &smmu_irq_dev_pm_ops,
    },
};

static int __init init_smmu_irq(void)
{
    int ret = 0;
    ret = platform_driver_register(&isp_smmuirq_drv);
    if(0 != ret)
    {
        pr_err("init_smmu_irq: platform_driver_register fail, ret = %d\n", ret);
    }
    return ret; 
}

static void __exit exit_smmu_irq(void)
{
    destroy_workqueue(my_wq);
    return platform_driver_unregister(&isp_smmuirq_drv);
}

late_initcall(init_smmu_irq);
module_exit(exit_smmu_irq);
