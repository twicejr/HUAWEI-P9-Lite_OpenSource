/*
 * Copyright (C) 20013-2013 hisilicon. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
#define pr_fmt(fmt) "[ivp-smmu]  " fmt

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/dma-mapping.h>
#include <asm/cacheflush.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/scatterlist.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include "ivp_smmu.h"

/* Address Space 0: Non-security, page_size=0x1000, pagenum=2 */
#define     SMMU_NS_CR0             0x0000
/* #define     SMMU_NS_ACR             0x0010 */
#define     SMMU_NS_IDR0            0x0020
/* #define     SMMU_NS_IDR1            0x0024
#define     SMMU_NS_IDR2            0x0028
#define     SMMU_NS_IDR7            0x003C
#define     SMMU_NS_GFAR_LOW        0x0040
#define     SMMU_NS_GFAR_HIGH       0x0044 */
#define     SMMU_NS_GFSR            0x0048
/* #define		SMMU_NS_GFSRRESTORE     0x004C */
#define		SMMU_NS_GFSYNR0         0x0050
#define		SMMU_NS_GFSYNR1         0x0054
#define		SMMU_NS_GFSYNR2         0x0058
#define		SMMU_NS_TLBIVMID        0x0064 //invalid tlb by VMID
/* #define		SMMU_NS_TLBIALLNSNH     0x0068 */
#define		SMMU_NS_TLBGSYNC        0x0070
#define		SMMU_NS_TLBGSTATUS      0x0074

#define		SMMU_NS_CBA2R0          0x1800
#define		SMMU_NS_SMR0            0x0800
/* #define		SMMU_NS_SMR1            0x0804
#define		SMMU_NS_SMR2            0x0808
#define		SMMU_NS_SMR3            0x080C */
#define		SMMU_NS_S2CR0           0x0C00
/* #define		SMMU_NS_S2CR1           0x0C04
#define		SMMU_NS_S2CR2           0x0C08
#define		SMMU_NS_S2CR3           0x0C0C
#define		SMMU_NS_CBFRSYNRA0      0x1400
#define		SMMU_NS_CBFRSYNRA1      0x1404
#define		SMMU_NS_CBFRSYNRA2      0x1408
#define		SMMU_NS_CBFRSYNRA3      0x140C */
#define		SMMU_NS_CBAR0           0x1000
/* #define		SMMU_NS_CBAR1           0x1004
#define		SMMU_NS_CBAR2           0x1008
#define		SMMU_NS_CBAR3           0x100C */
#define		SMMU_NS_CB0_SCTLR       0x8000
#define		SMMU_NS_CB0_RESUME      0x8008
#define		SMMU_NS_CB0_TTBCR2      0x8010 //SMMU_CB0_TCR2
#define		SMMU_NS_CB0_TTBR0_LOW   0x8020
#define		SMMU_NS_CB0_TTBR0_HIGH  0x8024
#define		SMMU_NS_CB0_TTBCR       0x8030 //SMMU_CB0_TCR
#define		SMMU_NS_CB0_FSR         0x8058
/* #define		SMMU_NS_CB0_FSRRESTORE  0x805C */
#define		SMMU_NS_CB0_FAR_LOW     0x8060
#define		SMMU_NS_CB0_FAR_HIGH    0x8064
#define		SMMU_NS_CB0_FSYNR0      0x8068
/* #define		SMMU_NS_CB0_TLBIVA      0x8600 //invalid tlb by VA
#define		SMMU_NS_CB0_TLBIASID    0x8610 //invalid tlb by ASID
#define		SMMU_NS_CB0_TLBIALL     0x8618 //invalid tlb ALL
#define		SMMU_NS_CB0_TLBSYNC     0x87F0 //invalid tlb sync
#define		SMMU_NS_CB0_TLBSTATUS   0x87F4 //invalid tlb status */


#define     SMMU_IDR0_CTTW          (1 << 14)   //Coherent Translation Table Walk

#define     SMMU_FAULT_READ	        0x0         //smmu read  fault
#define     SMMU_FAULT_WRITE	    0x1         //smmu write fault

#define     SMMU_CB_IDX_IVP			0		    //cbidx for ivp
#define     SMMU_CB_VMID_IVP		0		    //vmid  for ivp

#define     SMMU_CB_FSYNR0_WNR			(1 << 4)
#define     SMMU_CB_FSR_SS				(1 << 30)
/* #define     SMMU_CB_RESUME_RETRY		(0 << 0) */
#define     SMMU_CB_RESUME_TERMINATE	(1 << 0)

#define     SMMU_TLBGSTATUS_GSACTIVE	(1 << 0)
#define     SMMU_TLB_LOOP_TIMEOUT		1000000     /* 1s! */

#define 	SMMU_CBAR_TYPE_SHIFT		16
/* #define 	SMMU_CBAR_TYPE_MASK			0x3
#define 	SMMU_CBAR_TYPE_S2_TRANS				(0 << SMMU_CBAR_TYPE_SHIFT) */
#define 	SMMU_CBAR_TYPE_S1_TRANS_S2_BYPASS	(1 << SMMU_CBAR_TYPE_SHIFT)
/* #define 	SMMU_CBAR_TYPE_S1_TRANS_S2_FAULT	(2 << SMMU_CBAR_TYPE_SHIFT)
#define 	SMMU_CBAR_TYPE_S1_TRANS_S2_TRANS	(3 << SMMU_CBAR_TYPE_SHIFT) */

struct ivp_smmu_dev *g_smmu_dev = NULL;
struct dsm_client *client_ivp;

struct dsm_client_ops ops5={
    .poll_state = NULL,
    .dump_func = NULL,
};

struct dsm_dev dev_ivp = {
    .name = "dsm_ivp",
    .device_name = NULL,
    .ic_name = NULL,
    .module_name = NULL,
    .fops = &ops5,
    .buff_size = 256,
};


/* Wait for any pending TLB invalidations to complete */
static void ivp_smmu_tlb_sync(struct ivp_smmu_dev *smmu_dev)
{
	int count = 0;

    writel(0, smmu_dev->reg_base + SMMU_NS_TLBGSYNC);
	while (readl(smmu_dev->reg_base + SMMU_NS_TLBGSTATUS) 
            & SMMU_TLBGSTATUS_GSACTIVE) {
		if (++count == SMMU_TLB_LOOP_TIMEOUT) {
			pr_err("TLB sync timed out -- SMMU may be deadlocked\n");
			return;
		}
		udelay(1);
	}
}

/* Invalid TLB by vmid */
int ivp_smmu_invalid_tlb(struct ivp_smmu_dev *smmu_dev, unsigned int vmid)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&smmu_dev->spinlock, flags);

	/* vmid = smmu_dev->vmid */
    writel(vmid, (smmu_dev->reg_base + SMMU_NS_TLBIVMID));
    ivp_smmu_tlb_sync(smmu_dev);
    
    spin_unlock_irqrestore(&smmu_dev->spinlock, flags);
    
	return 0;
}

/* Flush cache for the page tables after pgt updated */
void ivp_smmu_flush_pgtable(struct ivp_smmu_dev *smmu_dev, void *addr, size_t size)
{
	unsigned long offset = (unsigned long)addr & ~PAGE_MASK;
	unsigned int  idr0 = 0;

	if ((NULL == smmu_dev) || (NULL == addr)) {
		pr_err("smmu_dev or addr is null!");
		return;
	}

	/* IDR0 */
	idr0 = readl(smmu_dev->reg_base + SMMU_NS_IDR0);

	/* Coherent translation table walks are supported */
	if (idr0 & SMMU_IDR0_CTTW) {
		dsb(ishst);
	} else {
		/*
		 * If the SMMU can't walk tables in the CPU caches, treat them
		 * like non-coherent DMA since we need to flush the new entries
		 * all the way out to memory. There's no possibility of
		 * recursion here as the SMMU table walker will not be wired
		 * through another SMMU.
		 */
		dma_map_page(smmu_dev->dev, virt_to_page(addr), offset, size,
				DMA_TO_DEVICE);
	}
}


/* Enable the translation mode of SMMU */
int ivp_smmu_trans_enable(struct ivp_smmu_dev *smmu_dev)
{
    unsigned long flags = 0;
	unsigned int  cbar0 = 0;

    spin_lock_irqsave(&smmu_dev->spinlock, flags);

    /* Check the smmu state */
    if(SMMU_STATE_ENABLE == smmu_dev->state){
        spin_unlock_irqrestore(&smmu_dev->spinlock, flags);
        pr_err("%s: SMMU re-enable\n", __func__);
        return -EBUSY;
	}

    /* Check pgd base address */
    if(!smmu_dev->pgd_base){
        spin_unlock_irqrestore(&smmu_dev->spinlock, flags);
        pr_err("%s: invalid pgd_base\n", __func__);
        return -EINVAL;
	}

	/**
	 * clear smmu interrupt
	 */
	writel(0xFFFFFFFF, (smmu_dev->reg_base + SMMU_NS_CB0_FSR));
	writel(0xFFFFFFFF, (smmu_dev->reg_base + SMMU_NS_GFSR));

	/**
	 * smcfcfg-0b1(bit21):raise stream match conflict fault;
	 * gcfgfie-0b1(bit5):global configuration fault interrupt enable
	 * gcfgfie-0b1(bit4): global configuration fault report enable
	 * gfie-0b1(bit2): global fault interrupt enable
	 * gfre--0b1(bit1): global fault report enable
	 * clientpd-0b0(bit0):transcation enable
	 */
    writel(0x200036, (smmu_dev->reg_base + SMMU_NS_CR0));

	/**
	 * valid-0b1(bit31): entry is included in the stream mapping table search
	 * mask-0b10(bit16~30):mask of ID[1]
	 * id-0b1(bit0~14):stream identifier to match
	 */
    writel(0xFFFE0001, (smmu_dev->reg_base + SMMU_NS_SMR0));

	/**
	 * nscfg-0b11(bit18~19):no secure
	 * type-0b00(bit16~17):translation context bank index
	 * cbndx-0b00(bit0~7):context bank index is 0 
	 */
    writel(0x0, (smmu_dev->reg_base + SMMU_NS_S2CR0));

	/**
	 * type-0b01(bit16~17):stage 1 context with stage 2 bypass
	 * bpshcfg-0b00(bit8~9):reserved
 	 * vmid-0b00000000(bit0~7): Virtual Machine Identifier
	 */
	cbar0 |= smmu_dev->cbar | (smmu_dev->vmid & 0xFF);
    writel(cbar0, (smmu_dev->reg_base + SMMU_NS_CBAR0));
    
	/**
	 * va64-0x1(bit0):descriptor format(0-32bit 1-64bit)
	 */
    writel(0x0, (smmu_dev->reg_base + SMMU_NS_CBA2R0));
    
	/**
	 * pd1-0b1(bit5):no trasaction table walk using ttbr1 on tlb miss
	 * pd0-0b0(bit4):perform translation table walks using ttbr0
	 * t0sz-0b000(bit0~2):size offset(2^(32-t0sz))
	 */
    writel(0x0, (smmu_dev->reg_base + SMMU_NS_CB0_TTBCR));

	/**
	 * type-0b000(bit15~17):Sign Extension Position(bit[31]-4G)
	 * pasize-0b000(bit0~2):physical address size(4G)
	 */
    writel(0x0, (smmu_dev->reg_base + SMMU_NS_CB0_TTBCR2));

	/**
	 * set pgd base address and asid
	 */
	writel((u32)smmu_dev->pgd_base, (smmu_dev->reg_base + SMMU_NS_CB0_TTBR0_LOW));
	writel(0x0, (smmu_dev->reg_base + SMMU_NS_CB0_TTBR0_HIGH));

	if(request_irq(smmu_dev->irq, smmu_dev->isr, IRQF_DISABLED, 
            "ivp-smmu-isr", (void *)smmu_dev)){
        pr_err("%s: failed to request IRQ[%d]\n", __func__, smmu_dev->irq);
	}

	/**
	 * cfie-0b1(bit6):Context Fault Interrupt Enable 
	 * cfre-0b1(bit5):Context Fault Report Enable
	 * afe-0b1(bit2):AP[0] is an access flag
	 * m-0b1(bit0):smmu enable
	 */
    writel(0x65, (smmu_dev->reg_base + SMMU_NS_CB0_SCTLR));
    smmu_dev->state = SMMU_STATE_ENABLE;
    spin_unlock_irqrestore(&smmu_dev->spinlock, flags);

    return 0;
}

/* Disable the translation mode of SMMU (switch to bypass mode) */
int ivp_smmu_trans_disable(struct ivp_smmu_dev *smmu_dev)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&smmu_dev->spinlock, flags);
    smmu_dev->state = SMMU_STATE_DISABLE;

	/* free the irq */
    free_irq(smmu_dev->irq, (void *)smmu_dev);

	/**
	 * clientpd-0b1(bit0):transcation disable
	 */
    writel(0x200013, (smmu_dev->reg_base + SMMU_NS_CR0));
    spin_unlock_irqrestore(&smmu_dev->spinlock, flags);

    return 0;
}

/* Return the smmu device handler to upper layer */
struct ivp_smmu_dev *ivp_smmu_get_device(unsigned long select)
{
	return g_smmu_dev;
}

/* Update the physical base address of page table directory */
int ivp_smmu_set_pgd_base(struct ivp_smmu_dev *smmu_dev, unsigned long pgd_base)
{
    unsigned long flags = 0;

    spin_lock_irqsave(&smmu_dev->spinlock, flags);
    /* It's should be disabled then re-enabled */
    if (SMMU_STATE_ENABLE == smmu_dev->state) {
        spin_unlock_irqrestore(&smmu_dev->spinlock, flags);
        pr_warning("%s: error state for set pgd\n", __func__);
        return -EBUSY;
    }
    smmu_dev->pgd_base = pgd_base;
    spin_unlock_irqrestore(&smmu_dev->spinlock, flags);
    
	return 0;
}

/* SMMU ISR, handler that SMMU reports fault to */
static irqreturn_t ivp_smmu_isr(int irq, void *dev_id)
{
	struct ivp_smmu_dev *smmu_dev = (struct ivp_smmu_dev *)dev_id;
    u32 gfsr, gfsynr0, gfsynr1, gfsynr2;
	u32 fsr, far, fsynr;
	unsigned long iova;
    int flags = 0;

    if(!dsm_client_ocuppy(client_ivp))
    {
         dsm_client_record(client_ivp, "ivp\n");
         dsm_client_notify(client_ivp, DSM_IVP_SMMU_ERROR_NO);
         pr_info("[I/DSM] %s dsm_client_ivp_smmu", client_ivp->client_name);
    }

    spin_lock(&smmu_dev->spinlock);

	/* global fault, It seems not supported yet */
	gfsr = readl(smmu_dev->reg_base + SMMU_NS_GFSR);
    if (gfsr) {
		gfsynr0 = readl(smmu_dev->reg_base + SMMU_NS_GFSYNR0);
		gfsynr1 = readl(smmu_dev->reg_base + SMMU_NS_GFSYNR1);
		gfsynr2 = readl(smmu_dev->reg_base + SMMU_NS_GFSYNR2);
    	pr_err("Unexpected global fault, this could be serious\n");
    	pr_err("\tGFSR 0x%08x, GFSYNR0 0x%08x, GFSYNR1 0x%08x, GFSYNR2 0x%08x\n",
    		gfsr, gfsynr0, gfsynr1, gfsynr2);

    	writel(gfsr, smmu_dev->reg_base + SMMU_NS_GFSR);
    }

	/* context bank fault */
	fsr = readl(smmu_dev->reg_base + SMMU_NS_CB0_FSR);

	fsynr = readl(smmu_dev->reg_base + SMMU_NS_CB0_FSYNR0);
    flags = fsynr & SMMU_CB_FSYNR0_WNR ? SMMU_FAULT_WRITE : SMMU_FAULT_READ;

	far = readl(smmu_dev->reg_base + SMMU_NS_CB0_FAR_LOW);
	iova = far;
	far = readl(smmu_dev->reg_base + SMMU_NS_CB0_FAR_HIGH);
	iova |= ((unsigned long)far << 32);

	pr_err("Unexpected context fault (fsr 0x%x)\n", fsr);
	pr_err("Unhandled  context fault: iova=0x%08lx, fsynr=0x%x\n", iova, fsynr);

    /* Report about an MMU fault to high-level users */
	if (smmu_dev->domain) {
        report_iommu_fault(smmu_dev->domain, smmu_dev->dev, iova, flags);
    }

	/* Clear the faulting FSR */
	writel(fsr, smmu_dev->reg_base + SMMU_NS_CB0_FSR);

	/* Retry or terminate any stalled transactions */
	if (fsr & SMMU_CB_FSR_SS) {
		writel(SMMU_CB_RESUME_TERMINATE, smmu_dev->reg_base + SMMU_NS_CB0_RESUME);
    }
    
    /* 
     * Because ivp dma error or cause error may cause many smmu fault
     * continuously, there we only report once.
     * */
    pr_info("Disable smmu irq");
    writel(0x25, (smmu_dev->reg_base + SMMU_NS_CB0_SCTLR));
    writel(0x200032, (smmu_dev->reg_base + SMMU_NS_CR0));

    spin_unlock(&smmu_dev->spinlock);
    
	return IRQ_HANDLED;
}

static int ivp_smmu_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct ivp_smmu_dev *smmu_dev  = NULL;
    struct iommu_domain_data *domain_info = NULL;
	struct resource *res = NULL; 
	unsigned int *ver = NULL;
    int ret = 0;
	    
	pr_info("%s: smmu driver start\n",__func__);
	
	smmu_dev = devm_kzalloc(&pdev->dev, sizeof(*smmu_dev), GFP_KERNEL);
	if (!smmu_dev){
		pr_err("%s: devm_kzalloc is failed\n", __func__);
        return -ENOMEM;
	}
	smmu_dev->dev = &pdev->dev;
    smmu_dev->state = SMMU_STATE_DISABLE;

	/* get smmu version */
	ver = (unsigned int *)of_get_property(np, "hisi,smmu-version", NULL);
	if (ver) {
		smmu_dev->version = be32_to_cpu(*ver); 
		pr_info("%s: smmu version is %u\n", __func__, be32_to_cpu(*ver));
	}

	/* get IOMEM resource */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		pr_err("%s:platform_get_resource err\n", __func__);
		return -ENOENT;
	}
	smmu_dev->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(smmu_dev->reg_base)) {
        pr_err("%s: remap resource err\n", __func__);
		return PTR_ERR(smmu_dev->reg_base);
    }
	smmu_dev->reg_size = resource_size(res);

	/* get IRQ resource */
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res){
		pr_err("%s: get IRQ IS failed\n", __func__);
		return -ENOENT;
	}
	smmu_dev->irq = (unsigned int)res->start;
	smmu_dev->isr = ivp_smmu_isr;

	/**
	 * get domain and physical pgd base address
	 */
	smmu_dev->domain = iommu_domain_alloc(pdev->dev.bus);
	if (!smmu_dev->domain) {
		pr_err("%s: get domain failed\n", __func__);
		return -ENODEV;
	} else {
		ret = iommu_attach_device(smmu_dev->domain, &pdev->dev);
        if (ret) {
            iommu_domain_free(smmu_dev->domain);
    		pr_err("%s: iommu attach failed ret[0x%x]\n", __func__, ret);
    		return -ENODEV;
        }
        
		domain_info = (struct iommu_domain_data *)smmu_dev->domain->priv;
        smmu_dev->pgd_base = (unsigned long)domain_info->phy_pgd_base;
	}

	/**
	 * for the ivp subsys, only support:
	 * Context Bank:0; Virtual Machine ID:0; CB attribute:S1_TRANS_S2_BYPASS
	 */
	smmu_dev->cbidx = SMMU_CB_IDX_IVP;
	smmu_dev->vmid  = SMMU_CB_VMID_IVP;
	smmu_dev->cbar  = SMMU_CBAR_TYPE_S1_TRANS_S2_BYPASS;

    spin_lock_init(&smmu_dev->spinlock);
    g_smmu_dev = smmu_dev;

	pr_info("%s: smmu driver probes finish\n", __func__);

    if(client_ivp == NULL)
    {
        client_ivp = dsm_register_client(&dev_ivp);
    }

	return 0;
}

static int ivp_smmu_remove(struct platform_device *pdev)
{
	struct ivp_smmu_dev *smmu_dev = g_smmu_dev;

	if (!smmu_dev) {
		pr_err("%s: smmu_dev invalid\n", __func__);
		return -ENODEV;
	}

	/**
	 * clientpd-0b1(bit0):transcation disable (switch to bypass mode)
	 */
    writel(0x200037, (smmu_dev->reg_base + SMMU_NS_CR0));

    if (smmu_dev->domain) {
        iommu_domain_free(smmu_dev->domain);
        smmu_dev->domain = NULL;
    }

    g_smmu_dev = NULL;
    
	return 0;
}

static struct of_device_id of_smmu_match_tbl[] = {
	{
		.compatible = "hisi,ivp-smmu",
	},
	{ },
};

static struct platform_driver ivp_smmu_driver = {
	.driver  ={
		.owner = THIS_MODULE,
		.name = "ivp-smmu",
		.of_match_table = of_smmu_match_tbl,
	},
	.probe  =  ivp_smmu_probe,
	.remove =  ivp_smmu_remove,
};

static int __init ivp_smmu_init(void)
{
	return platform_driver_register(&ivp_smmu_driver);
}

static void __exit ivp_smmu_exit(void)
{
    return platform_driver_unregister(&ivp_smmu_driver);
}

/* subsys_initcall(ivp_smmu_init); */
module_init(ivp_smmu_init);
module_exit(ivp_smmu_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("hisilicon");
