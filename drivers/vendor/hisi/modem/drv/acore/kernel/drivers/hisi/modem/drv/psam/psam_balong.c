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

#include <linux/delay.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include "psam_balong.h"
#include "bsp_psam.h"
#include "bsp_om.h"
#include "bsp_ipf.h"


struct psam_device *g_psam_device;
static unsigned long long d_psam_mask;
static void * p_ctrl_base_addr = NULL;
static unsigned int idle_p_ctrl[3] = {0,};

static const struct of_device_id psam_match[] = {
	{ .compatible = "hisilicon,psam_balong_app" },
	{},
};
MODULE_DEVICE_TABLE(of, psam_match);

void psam_help(void)
{
	printk(KERN_ALERT "psam_ad_info 		打印单个ad描述符信息\n");
	printk(KERN_ALERT "psam_dump_ad_info 	打印所有ad描述符信息\n\n");

	printk(KERN_ALERT "********ad队列的基本信息\n");
	printk(KERN_ALERT "ad0 virtual addr  0x%x\n",g_psam_device->adq0_info.vir_addr);
	printk(KERN_ALERT "ad0 physical addr 0x%x\n",readl(g_psam_device->regs + HI_PSAM_ADQ0_BASE_OFFSET));
	printk(KERN_ALERT "ad0 lenth is %d\n",  	 g_psam_device->desc_num[0]);
	printk(KERN_ALERT "ad0 read index is %d\n",  readl(g_psam_device->regs + HI_PSAM_ADQ0_RPTR_OFFSET));
	printk(KERN_ALERT "ad0 write index is %d\n", readl(g_psam_device->regs + HI_PSAM_ADQ0_WPTR_OFFSET));

	printk(KERN_ALERT "ad1 virtual addr  0x%x\n",g_psam_device->adq1_info.vir_addr);
	printk(KERN_ALERT "ad1 physical addr 0x%x\n",readl(g_psam_device->regs + HI_PSAM_ADQ1_BASE_OFFSET));
	printk(KERN_ALERT "ad1 lenth is %d\n",  	 g_psam_device->desc_num[1]);
	printk(KERN_ALERT "ad1 read index is %d\n",  readl(g_psam_device->regs + HI_PSAM_ADQ1_RPTR_OFFSET));
	printk(KERN_ALERT "ad1 write index is %d\n\n", readl(g_psam_device->regs + HI_PSAM_ADQ1_WPTR_OFFSET));

	printk(KERN_ALERT "********ipf rd status\n");
	printk(KERN_ALERT "rd compile intr	%d\n", ((struct ipf_debug*)(g_psam_device->ipf_deb))->rd_comp_intr);
	printk(KERN_ALERT "rd full intr 	%d\n", ((struct ipf_debug*)(g_psam_device->ipf_deb))->rd_full_intr);
	printk(KERN_ALERT "rd_full 		%d\n", ((struct ipf_debug*)(g_psam_device->ipf_deb))->rd_full);
	printk(KERN_ALERT "rd_cb			%d\n", ((struct ipf_debug*)(g_psam_device->ipf_deb))->rd_cb);
	printk(KERN_ALERT "rd_cb_null		%d\n", ((struct ipf_debug*)(g_psam_device->ipf_deb))->rd_cb_null);
	printk(KERN_ALERT "get_rd_num_times		%d\n", ((struct ipf_debug*)(g_psam_device->ipf_deb))->get_rd_num_times);
	printk(KERN_ALERT "get_rd_times			%d\n", ((struct ipf_debug*)(g_psam_device->ipf_deb))->get_rd_times);
	printk(KERN_ALERT "dlrd short cnt %d\n",((struct ipf_debug*)(g_psam_device->ipf_deb))->get_rd_cnt[0]);
	printk(KERN_ALERT "dlrd long cnt  %d\n",((struct ipf_debug*)(g_psam_device->ipf_deb))->get_rd_cnt[1]);
    printk(KERN_ALERT "free ad numbers:  %d\n", g_psam_device->debug.adq_free_cnt);

	printk(KERN_ALERT "********ad队列空满统计\n");
	printk(KERN_ALERT "adq0 空的次数是 %d\n",g_psam_device->debug.adq0_epty_int1);
	printk(KERN_ALERT "adq1 空的次数是 %d\n",g_psam_device->debug.adq1_epty_int1);
	printk(KERN_ALERT "upoverflow 次数是 %d\n",g_psam_device->debug.lbdq_upoverflow);
	printk(KERN_ALERT "lbdq_full 次数是 %d\n",g_psam_device->debug.lbdq_full);
	printk(KERN_ALERT "lbdq_empty 次数是 %d\n\n",g_psam_device->debug.lbdq_empty);

	printk(KERN_ALERT "********接口信息统计\n");
	printk(KERN_ALERT "call get_dlad_num cnt is: %d\n\n",g_psam_device->debug.get_dlad_num);

	printk(KERN_ALERT "adq0 成功次数是 %d\n",g_psam_device->debug.cfg_dl_ad_succ[0]);
	printk(KERN_ALERT "参数 get_dlad0_num 为NULL %d\n",g_psam_device->debug.cfg_get_ad_para_null[0]);
	printk(KERN_ALERT "参数 ad0 desc 为NULL %d\n",g_psam_device->debug.dlad_desc_null[0]);
	printk(KERN_ALERT "adq0 outpointer为0 %d\n\n",g_psam_device->debug.dlad_outptr_err[0]);

	printk(KERN_ALERT "adq1 成功次数是 %d\n",g_psam_device->debug.cfg_dl_ad_succ[1]);
	printk(KERN_ALERT "参数 get_dlad0_num 为NULL %d\n",g_psam_device->debug.cfg_get_ad_para_null[1]);
	printk(KERN_ALERT "参数 ad1 desc 为NULL %d\n",g_psam_device->debug.dlad_desc_null[1]);
	printk(KERN_ALERT "adq1 outpointer为0 %d\n\n",g_psam_device->debug.dlad_outptr_err[1]);

	printk(KERN_ALERT "ad类型错误 %d\n",g_psam_device->debug.dlad_type_err);
	printk(KERN_ALERT "ad个数错误 %d\n",g_psam_device->debug.cfg_dlad_num_err);
	printk(KERN_ALERT "scr ad错误 %d\n",g_psam_device->debug.scr_ad_addr_exc);
}

int psam_ad_info( unsigned int ad_type, unsigned int adq_ptr)
{
    if(adq_ptr >= PSAM_DLAD1_DESC_SIZE)
    {
        return -1;
    }

 	printk(KERN_ALERT "===========DL AD%d Info==========\n",ad_type);
 	printk(KERN_ALERT "AD位置:             %d\n",adq_ptr);
 	printk(KERN_ALERT "u32OutPtr0(phy_addr, use by hardware): 0x%x\n",g_psam_device->desc[ad_type][adq_ptr].u32OutPtr0);
 	printk(KERN_ALERT "u32OutPtr1(usrfield skb_addr default): 0x%x\n",g_psam_device->desc[ad_type][adq_ptr].u32OutPtr1);
    printk(KERN_ALERT "************************\n");
    return 0;
}

int psam_dump_ad_info(unsigned int ad_type)
{
    int i;

    for(i = 0;i < PSAM_DLAD1_DESC_SIZE;i++)
    {
        psam_ad_info(i, ad_type);
    }

    return 0;
}

#ifdef CONFIG_PM
static int psam_dl_dpm_prepare(struct device *pdev)
{
	unsigned int dl_state;
	/* 判断下行psam是否空闲 */
	if(idle_p_ctrl[0]){
		dl_state = readl(p_ctrl_base_addr + idle_p_ctrl[1]);
		dl_state &= idle_p_ctrl[2];
		if(dl_state != idle_p_ctrl[2])
		{
			dev_err(g_psam_device->dev, "%s psam is busy\n", __func__);
			return ERROR;
		}
	}else{
	dl_state = readl(g_psam_device->regs + HI_PSAM_SRST_OFFSET);
	dl_state &= PSAM_IDLE_BIT;

	if(dl_state != PSAM_IDLE_BIT)
	{
		dev_err(g_psam_device->dev, "%s psam is busy\n", __func__);
		return ERROR;
		}
	}
	return 0;
}

static void psam_dl_dpm_complete(struct device *pdev)
{
	return ;
}

static int psam_dl_suspend(struct device *dev)
{
	return 0;
}

static int psam_dl_resume(struct device *dev)
{
	return 0;
}
#else
#define psam_dl_dpm_prepare		NULL
#define psam_dl_dpm_complete	NULL
#define psam_dl_suspend			NULL
#define psam_dl_resume			NULL
#endif

int bsp_psam_idle(void)
{
	unsigned int dl_state;
	if(idle_p_ctrl[0]){
		dl_state = readl(p_ctrl_base_addr + idle_p_ctrl[1]);
		dl_state &= idle_p_ctrl[2];
		if(dl_state != idle_p_ctrl[2])
		{
			return 0;
		}
	}
	return 1;
}

int bsp_psam_get_used_dlad(IPF_AD_TYPE_E ad_type, unsigned int * ad_num, psam_ad_desc_s * pst_ad_desc)
{
    unsigned int time_out = 10;
    unsigned int free_ad_num = 0;
    unsigned int adq_wptr;
    unsigned int adq_rptr;
    if((NULL == ad_num)||(NULL == pst_ad_desc)){
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r input para ERROR!NULL == ad_num or NULL == pst_ad_desc\n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(bsp_get_init_status() == PSAM_ACORE_INIT_SUC){
        bsp_set_init_status(0);
    }
    
    do{
        if(bsp_psam_idle()){
            break;
        }
        msleep(20);
    }while(--time_out);
    if (!time_out){
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r After 20ms psam dl channel still on, unable to free AD \n");
        return IPF_ERROR;
    }

    if(IPF_AD_0 == ad_type){
        adq_wptr = readl(g_psam_device->regs + HI_PSAM_ADQ_WPTR_OFFSET(0));
		adq_rptr = readl(g_psam_device->regs + HI_PSAM_ADQ_RPTR_OFFSET(0));
        while(adq_rptr != adq_wptr){
            pst_ad_desc->u32OutPtr1 = g_psam_device->desc[ad_type][adq_rptr].u32OutPtr1;
            pst_ad_desc->u32OutPtr0 = g_psam_device->desc[ad_type][adq_rptr].u32OutPtr0;
            adq_rptr = ((adq_rptr + 1) < IPF_DLAD0_DESC_SIZE)? (adq_rptr + 1) : 0;
            pst_ad_desc++;
            free_ad_num++;
        }
    }
    else if(IPF_AD_1 == ad_type){
        adq_wptr = readl(g_psam_device->regs + HI_PSAM_ADQ_WPTR_OFFSET(1));
		adq_rptr = readl(g_psam_device->regs + HI_PSAM_ADQ_RPTR_OFFSET(1));
        while(adq_rptr != adq_wptr){
            pst_ad_desc->u32OutPtr1 = g_psam_device->desc[ad_type][adq_rptr].u32OutPtr1;
            pst_ad_desc->u32OutPtr0 = g_psam_device->desc[ad_type][adq_rptr].u32OutPtr0;
            adq_rptr = ((adq_rptr + 1) < IPF_DLAD1_DESC_SIZE)? (adq_rptr + 1) : 0;
            pst_ad_desc++;
            free_ad_num++;
        }
    }
    else{
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r para ERROR! u32AdType >= IPF_AD_MAX\n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    g_psam_device->debug.adq_free_cnt += free_ad_num;
    *ad_num = free_ad_num;
    return 0;
}
int psam_srset(void)
{
	unsigned int count = 10000;
	unsigned int reg_v = 1;

	writel(reg_v, g_psam_device->regs + HI_PSAM_SRST_OFFSET);
	while(reg_v & PSAM_SRST_BIT){
		reg_v = readl(g_psam_device->regs + HI_PSAM_SRST_OFFSET);
		if(count == 0){
			return -EINVAL;
		}
		count--;
	}
	return 0;
}

int psam_reinit_regs(void)
{
	int i = 0;

	if(g_psam_device ==  NULL)
		return -EINVAL;

	for (i = 0; i < PSAM_ADQ_NUM; i++) {
		writel(g_psam_device->dma[i], g_psam_device->regs + HI_PSAM_ADQ_BASE_OFFSET(i));
	}
	writel(PSAM_INT_MASK, g_psam_device->regs + HI_PSAM_INT0_MASK_OFFSET);
	writel(0xffffffff, g_psam_device->regs + HI_PSAM_INT0_STAT_OFFSET);
	writel(PSAM_ADQ_DEFAULT_SEETING, g_psam_device->regs + HI_PSAM_ADQ_CTRL_OFFSET);

	return 0;
}


int psam_register_adq_empty_dlcb(adq_emtpy_cb_t adq_emtpy_cb)
{
    g_psam_device->adq_emtpy_cb = adq_emtpy_cb;
	return 0;
}

int psam_get_dlad_num(unsigned int* ad0_num, unsigned int* ad1_num)
{
	unsigned int wptr = 0;
	unsigned int rptr = 0;
	unsigned int*  ad[PSAM_ADQ_NUM];
	int i;

	if(bsp_get_init_status()!= PSAM_ACORE_INIT_SUC){
		return -EINVAL;
	}
	g_psam_device->debug.get_dlad_num++;

	if(!g_psam_device->debug.init_ok) {
		return -EINVAL;
	}

	if(!ad0_num || !ad1_num) {
		!ad0_num? g_psam_device->debug.cfg_get_ad_para_null[0]++:\
				  g_psam_device->debug.cfg_get_ad_para_null[1]++;
		return -EINVAL;
	}
	ad[0] = ad0_num;
	ad[1] = ad1_num;
	for (i = 0; i < PSAM_ADQ_NUM; i++) {
		wptr = readl(g_psam_device->regs + HI_PSAM_ADQ_WPTR_OFFSET(i));
		rptr = readl(g_psam_device->regs + HI_PSAM_ADQ_RPTR_OFFSET(i));

		*ad[i] = (g_psam_device->desc_num[i] + rptr -(wptr + PSAM_ADQ_RESERVE_NUM)) % g_psam_device->desc_num[i];
	}
	return 0;
}

int psam_config_dlad(unsigned int type, unsigned int num, psam_ad_desc_s *desc)
{
	unsigned int wptr = 0;
	psam_ad_desc_s *cur = desc;
	unsigned int i;
	if(bsp_get_init_status()!= PSAM_ACORE_INIT_SUC){
		return -EINVAL;
	}

	if(type >= IPF_AD_MAX) {
		g_psam_device->debug.dlad_type_err++;
		return -EINVAL;
	}

	if(!desc) {
		g_psam_device->debug.dlad_desc_null[type]++;
		return -EINVAL;
	}

	if(!g_psam_device->debug.init_ok) {
		return -EINVAL;
	}

	if(num > g_psam_device->desc_num[type])	{
		g_psam_device->debug.cfg_dlad_num_err++;
		return -EINVAL;
	}

	wptr = readl(g_psam_device->regs + HI_PSAM_ADQ_WPTR_OFFSET(type));

	for (i=0; i < num; i++) {
		/*usr feild should not be zero*/
		if(!cur->u32OutPtr1) {
			g_psam_device->debug.dlad_outptr_err[type]++;
			break;
		}
		g_psam_device->desc[type][wptr].u32OutPtr1 = cur->u32OutPtr1;
		g_psam_device->desc[type][wptr].u32OutPtr0 = cur->u32OutPtr0;
		wptr = ((wptr + 1) % g_psam_device->desc_num[type]);
		cur++;
	}
	g_psam_device->debug.cfg_dl_ad_succ[type] += i;
	writel(wptr, g_psam_device->regs + HI_PSAM_ADQ_WPTR_OFFSET(type));
	/*g_psam_device->debug.*/
	return 0;
}

static irqreturn_t psam_interrupt(int irq, void *dev_id)
{
	struct psam_device *psam = dev_id;
	unsigned int pending;

	pending = readl(psam->regs + HI_PSAM_INT_STAT_OFFSET(0));
	writel(pending, psam->regs + HI_PSAM_INT_STAT_OFFSET(0));

	if(pending & PSAM_INT_ADQ0_EPTY_INT){
		g_psam_device->debug.adq0_epty_int1++;
		if (psam->adq_emtpy_cb)
			psam->adq_emtpy_cb(IPF_EMPTY_ADQ0);
	}

	if(pending & PSAM_INT_ADQ1_EPTY_INT){
		g_psam_device->debug.adq1_epty_int1++;
		if (psam->adq_emtpy_cb)
			psam->adq_emtpy_cb(IPF_EMPTY_ADQ1);
	}

	if(pending & PSAM_INT_LBDQ_UPOVERFLOW_INT){
		g_psam_device->debug.lbdq_upoverflow++;
	}

	if(pending & PSAM_INT_LBDQ_FULL_INT){
		g_psam_device->debug.lbdq_full++;
	}

	if(pending & PSAM_INT_LBDQ_EPTY_INT){
		g_psam_device->debug.lbdq_empty++;
	}

	if(pending & PSAM_SCR_AD_ADDR_EXCPTION){
		g_psam_device->debug.scr_ad_addr_exc++;
		printk(KERN_ALERT "psam dl ad out of reg!\n");

		system_error(DRV_ERRNO_PSAM_OUT_REG, 0, 0, (char *)(g_psam_device->desc[0]), g_psam_device->desc_num[0] * sizeof(psam_ad_desc_s));
	}
	return IRQ_HANDLED;
}

static int psam_probe(struct platform_device *pdev)
{
	struct psam_device *psam;
	struct resource	*regs;
	int i;
	int ret;

	psam = devm_kzalloc(&pdev->dev, sizeof(struct psam_device), GFP_KERNEL);
	if (!psam)
		return -ENOMEM;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!regs)
		return -ENXIO;

	psam->irq = platform_get_irq(pdev, 0);
	if (psam->irq < 0)
		return psam->irq;

	psam->irq_flags = IRQF_NO_SUSPEND;
	psam->dev = &pdev->dev;

	d_psam_mask = 0xffffffffULL;
	psam->dev->dma_mask = &d_psam_mask;
	psam->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(psam->regs))
		return PTR_ERR(psam->regs);

	psam->clk = devm_clk_get(psam->dev, "psam_aclk");
	if (IS_ERR(psam->clk)) {
		dev_err(psam->dev, "psam clock not available\n");
		return -EPERM;
	} else {
		ret = clk_prepare_enable(psam->clk);
		if (ret) {
			dev_err(psam->dev, "failed to enable psam clock\n");
			return ret;
		}
	}

	psam->desc_num[0] = PSAM_DLAD0_DESC_NUM;
	psam->desc_num[1] = PSAM_DLAD1_DESC_NUM;

	for (i = 0; i < PSAM_ADQ_NUM; i++) {
		psam->desc[i] = (psam_ad_desc_s*)dmam_alloc_coherent(psam->dev,
			psam->desc_num[i] * sizeof(psam_ad_desc_s), &psam->dma[i], GFP_KERNEL);
		if (psam->desc[i] == NULL)
			return -ENOMEM;
		writel(psam->dma[i], psam->regs + HI_PSAM_ADQ_BASE_OFFSET(i));
	}

	psam->adq0_info.vir_addr = (unsigned int)(unsigned long)(psam->desc[0]);
	psam->adq1_info.vir_addr = (unsigned int)(unsigned long)(psam->desc[1]);

	writel(PSAM_INT_MASK, psam->regs + HI_PSAM_INT0_MASK_OFFSET);
	writel(0xffffffff, psam->regs + HI_PSAM_INT0_STAT_OFFSET);

	ret = devm_request_irq(psam->dev, psam->irq, psam_interrupt,
			       psam->irq_flags, "psam", psam);

	writel(PSAM_ADQ_DEFAULT_SEETING, psam->regs + HI_PSAM_ADQ_CTRL_OFFSET);

	platform_set_drvdata(pdev, psam);

	g_psam_device = psam;
	bsp_ipf_set_debug_para(&(g_psam_device->ipf_deb));
	/*only dallas platform need to juduge idle by p_ctrl.*/
	(void)of_property_read_u32_array(pdev->dev.of_node, "idle_ctrl", idle_p_ctrl, 3);
	dev_info(psam->dev, "idle_p_ctrl %x, %x, %x\n", idle_p_ctrl[0],idle_p_ctrl[1],idle_p_ctrl[2]);
	if(idle_p_ctrl[0]){
		p_ctrl_base_addr=(void *)ioremap_nocache(idle_p_ctrl[0], P_CTRL_4K);
	}

	psam->debug.init_ok = 1;
	printk(KERN_ALERT "psam init ok!\n");

	return 0;
}

static int psam_remove(struct platform_device *pdev)
{
	struct psam_device *psam = NULL;

	psam = platform_get_drvdata(pdev);
	if (!psam)
		return -ENOMEM;

	platform_set_drvdata(pdev, NULL);

	clk_disable_unprepare(psam->clk);

	return 0;
}

static const struct dev_pm_ops psam_dev_pm_ops ={
	.prepare = psam_dl_dpm_prepare,
	.suspend = psam_dl_suspend,
	.resume = psam_dl_resume,
	.complete = psam_dl_dpm_complete,
};

static struct platform_driver psam_pltfm_driver = {
	.probe		= psam_probe,
	.remove		= psam_remove,
	.driver		= {
		.name		= "psam",
		.of_match_table	= psam_match,
		.pm = &psam_dev_pm_ops,
	},
};

module_platform_driver(psam_pltfm_driver);
EXPORT_SYMBOL(g_psam_device);
EXPORT_SYMBOL(psam_srset);
EXPORT_SYMBOL(psam_reinit_regs);
EXPORT_SYMBOL(psam_register_adq_empty_dlcb);
MODULE_DESCRIPTION("Balong Specific Psam Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:psam");
