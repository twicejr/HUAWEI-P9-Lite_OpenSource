/*
 * hi3630-sio.c -- ALSA SoC HI3630 SIO DAI driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_SIO"

#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <sound/core.h>
#include <sound/dmaengine_pcm.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/soc.h>
#include <linux/pm_runtime.h>

#include "hi3630_log.h"
#include "hi3630_sio.h"
#include "asp_edmac_reg_offset.h"

#define HISI_SIO_RATES (SNDRV_PCM_RATE_8000_96000)
/* for ko
extern void sio_audio_module_enable(bool enable);
extern void sio_voice_module_enable(bool enable);
extern void sio_bt_module_enable(bool enable);
extern void sio_modem_module_enable(bool enable);

extern void set_sio_audio_master(bool enable);
extern void set_sio_voice_master(bool enable);
extern void set_sio_bt_master(bool enable);
extern void set_sio_modem_master(bool enable);
*/
#define REGULATOR_ENABLE 1

#define HIFI_BASE_ADDR					(0x35400000)
#define HIFI_IMAGE_SIZE 				(0x380000)
#define HIFI_SIZE						(0x900000)
#define BASE_ADDR_ASP_DMAC 			(0xE804B000)
#define BASE_ADDR_ASP_DMAC_SIZE  		(0x1000)
#define TX_SIZE 							(0x100)
#define CH_0_INT_MASK 					(0x1)
#define CH_UNMASK 						(0xfff)
#define CH_INT_CLR 						(0xfff)

#define HIFI_DDR_TEST_SIZE 				(HIFI_SIZE - HIFI_IMAGE_SIZE)
#define HIFI_ITCM_TEST_SIZE                     (0x5fff)
#define HIFI_DTCM_TEST_SIZE                    (0x17fff)
#define HIFI_OCRAM_TEST_SIZE                  (0x2ffff)
#define CODEC_SSI_SIZE                  		(0xfff)
#define CODEC_SSI_BASE_ADDR                   (0xE82B9000)

#define ASP_REG_BASE_ADDR                   (0xE804E000)
#define ASP_REG_SIZE                                   (0x3ff)



static void* 					g_dmac_base_addr 	= NULL; 
static struct platform_device  	*s_dev				= NULL;

#define mem_remap_nocache(phys_addr, size) mem_remap_type(phys_addr, size, pgprot_noncached(PAGE_KERNEL))
// #define PINCTRL_ENABLE 
#if 0
static unsigned int hi3630_sio_reg_read(struct hi3630_sio_platform_data *pdata,
					unsigned int reg)
{
	return readl(pdata->reg_base_addr + reg);
}
#endif
static int hi3630_sio_reg_write(struct hi3630_sio_platform_data *pdata,
				unsigned int reg,
				unsigned int value)
{
	writel(value, pdata->reg_base_addr + reg);
	return 0;
}

static int sio_dai_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);
	BUG_ON(NULL == pdata);

	switch (pdata->id) {
	case SIO_AUDIO_ID:

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_get_sync(pdata->dev);
#else
	{
		struct pinctrl_state *pinctrl_state;
		int ret = -1;

#ifdef  REGULATOR_ENABLE
		ret = regulator_enable(pdata->regu_asp);
		if (0 != ret) {
			loge("couldn't enable regulators %d\n", ret);
			return -ENOENT;
		}
		else {
			loge("============== Enable regulators ===========\n");
		}
#endif

		mutex_lock(&pdata->mutex);
		if (0 == pdata->active_count) {
			/* config iomux */
#ifdef PINCTRL_ENABLE
			pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_DEFAULT);
			if (IS_ERR(pinctrl_state)) {
				loge("could not get defstate (%li)\n", PTR_ERR(pinctrl_state));
				mutex_unlock(&pdata->mutex);
				return ret;
			}
			ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
			if (ret) {
				loge("could not set pins to default state\n");
				mutex_unlock(&pdata->mutex);
				return ret;
			}
#endif
		}		
		pdata->active_count++;
		mutex_unlock(&pdata->mutex);
	}
#endif
		// for koset_sio_audio_master(pdata->is_master);
		// for kosio_audio_module_enable(true);
		break;
	case SIO_VOICE_ID:
#if 0
		set_sio_voice_master(pdata->is_master);
		sio_voice_module_enable(true);
#endif
		break;
	case SIO_BT_ID:
		// for ko set_sio_bt_master(pdata->is_master);
		// for ko sio_bt_module_enable(true);
		break;
	case SIO_MODEM_ID:
		// for koset_sio_modem_master(pdata->is_master);
		// for kosio_modem_module_enable(true);
		break;
	default:
		loge("unknown sio\n");
		break;
	}

	return 0;
}

static void sio_dai_shutdown(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	switch (pdata->id) {
	case SIO_AUDIO_ID:
		// for ko sio_audio_module_enable(false);

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_mark_last_busy(pdata->dev);
	pm_runtime_put_autosuspend(pdata->dev);
#else
	{
		struct pinctrl_state *pinctrl_state;
		int ret = -1;

		mutex_lock(&pdata->mutex);
		if (0 == pdata->active_count) {
			loge("sio iomux is alread set as default\n");
			goto err;
		}
		pdata->active_count--;
		if (0 == pdata->active_count) {
			/* config iomux */
#ifdef PINCTRL_ENABLE
			pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_IDLE);
			if (IS_ERR(pinctrl_state)) {
				loge("could not get defstate (%li)\n", PTR_ERR(pinctrl_state));
				goto err;
			}
			ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
			if (0 != ret) {
				loge("could not set pins to idle state\n");
				goto err;
			}
#endif
		}
	}
err:
#ifdef  REGULATOR_ENABLE
	regulator_disable(pdata->regu_asp);
#endif
	mutex_unlock(&pdata->mutex);
#endif
		break;
	case SIO_VOICE_ID:
#if 0
		sio_voice_module_enable(false);
#endif
		break;
	case SIO_BT_ID:
		// for ko sio_bt_module_enable(false);
		break;
	case SIO_MODEM_ID:
		// for ko sio_modem_module_enable(false);
		break;
	default:
		loge("unknown sio\n");
		break;
	}
}

static void enable_sio_audio_tx(struct hi3630_sio_platform_data *pdata)
{
	if (0 == pdata->pb_active) {
		/* clr fifo */
		hi3630_sio_reg_write(pdata, SIO_CTL_SET, SIO_TX_FIFO_DISABLE);
		hi3630_sio_reg_write(pdata, SIO_CTL_CLR,
				SIO_TX_ENABLE | SIO_TX_FIFO_DISABLE |
				SIO_TX_DATA_MERGE | SIO_TX_FIFO_THRESHOLD_CLR);
		hi3630_sio_reg_write(pdata, SIO_CTL_SET,
				SIO_TX_ENABLE | SIO_TX_DATA_MERGE | SIO_TX_FIFO_THRESHOLD);
	}

	pdata->pb_active++;
}

static void disable_sio_audio_tx(struct hi3630_sio_platform_data *pdata)
{
	if (0 == pdata->pb_active) {
		loge("sio audio has already closed");
		return;
	}

	pdata->pb_active--;

	if (0 == pdata->pb_active)
		hi3630_sio_reg_write(pdata, SIO_CTL_CLR, SIO_TX_ENABLE);
}

static inline void enable_sio_audio_rx(struct hi3630_sio_platform_data *pdata)
{
	/* clr fifo */
	hi3630_sio_reg_write(pdata, SIO_CTL_SET, SIO_RX_FIFO_DISABLE);
	hi3630_sio_reg_write(pdata, SIO_CTL_CLR,
			SIO_RX_ENABLE | SIO_RX_FIFO_DISABLE |
			SIO_RX_DATA_MERGE | SIO_RX_FIFO_THRESHOLD_CLR);
	hi3630_sio_reg_write(pdata, SIO_CTL_SET,
			SIO_RX_ENABLE | SIO_RX_DATA_MERGE | SIO_RX_FIFO_THRESHOLD);
}

static inline void disable_sio_audio_rx(struct hi3630_sio_platform_data *pdata)
{
	hi3630_sio_reg_write(pdata, SIO_CTL_CLR, SIO_RX_ENABLE);
}

static int sio_dai_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	/* config sio mode & parameters */
	switch (pdata->id) {
	case SIO_AUDIO_ID:
		hi3630_sio_reg_write(pdata, SIO_CFG, SIO_CFG_SIO_MODE);
		/* to do*/
		hi3630_sio_reg_write(pdata, SIO_DATA_WIDTH, 0x24);
		hi3630_sio_reg_write(pdata, SIO_I2S_POS_MERGE, 0x1);

		/* config control regs */
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
			enable_sio_audio_tx(pdata);
		else
			enable_sio_audio_rx(pdata);
		break;
	case SIO_VOICE_ID:
		break;
	case SIO_BT_ID:
		/* not used */
		break;
	case SIO_MODEM_ID:
		hi3630_sio_reg_write(pdata, SIO_CFG, SIO_CFG_SIO_MODE);
		/* todo */
		break;
	default:
		loge("unknown sio\n");
		break;
	}

	return 0;
}

static int sio_dai_hw_free(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct hi3630_sio_platform_data *pdata = snd_soc_dai_get_drvdata(dai);

	BUG_ON(NULL == pdata);

	switch (pdata->id) {
	case SIO_AUDIO_ID:
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
			disable_sio_audio_tx(pdata);
		else
			disable_sio_audio_rx(pdata);
		break;
	case SIO_VOICE_ID:
		break;
	case SIO_BT_ID:
		/* not used */
		break;
	case SIO_MODEM_ID:
		/* todo */
		break;
	default:
		loge("unknown sio\n");
		break;
	}

	return 0;
}

static const struct snd_soc_dai_ops sio_dai_ops = {
	.startup	= sio_dai_startup,
	.shutdown	= sio_dai_shutdown,
	.hw_params	= sio_dai_hw_params,
	.hw_free	= sio_dai_hw_free,
};

static int hi3630_sio_probe(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static int hi3630_sio_remove(struct snd_soc_dai *dai)
{
	/* do nothing */
	return 0;
}

static const struct snd_soc_component_driver hi3630_sio_component = {
	.name		= "hi3630-sio",
};

static struct snd_soc_dai_driver hi3630_sio_dai = {
	.probe = hi3630_sio_probe,
	.remove = hi3630_sio_remove,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = HISI_SIO_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE,
	},
	.capture = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = HISI_SIO_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	},
	.ops = &sio_dai_ops,
};

static const struct of_device_id hi3630_sio_of_match[] = {
	{
		.compatible = "hisilicon,hi3630-sio",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_sio_of_match);

static void *mem_remap_type(unsigned long phys_addr, size_t size, pgprot_t pgprot)
{
    int i;
    u8* vaddr;
    int npages = PAGE_ALIGN((phys_addr & (PAGE_SIZE - 1)) + size) >> PAGE_SHIFT;
    unsigned long offset = phys_addr & (PAGE_SIZE - 1);
    struct page **pages;
    pages = vmalloc(sizeof(struct page *) * npages);
    if (!pages)
    {
        printk(KERN_ERR "%s: vmalloc return NULL!\n", __FUNCTION__);
        return NULL;
    }
    pages[0] = phys_to_page(phys_addr);
    for (i = 0; i < npages - 1 ; i++) {
        pages[i + 1] = pages[i] + 1;
    }
    vaddr = (u8*)vmap(pages, npages, VM_MAP, pgprot);
    if(vaddr == 0)
    {
        printk(KERN_ERR "%s: vmap return NULL!\n", __FUNCTION__);
    }
    else
    {
        vaddr += offset;
    }
    vfree(pages);
    printk(KERN_DEBUG "%s: phys_addr:0x%08lx size:0x%08lx npages:%d vaddr:%p offset:0x%08lx\n", __FUNCTION__, phys_addr, (unsigned long)size, npages, vaddr, offset);
    return (void *)vaddr;
}


 void asp_powerup(void)
{
	int ret = -1;
	struct hi3630_sio_platform_data *pdata;

	pdata = platform_get_drvdata(s_dev);
	
	printk( "asp_test:Asp power up \n");
	ret = regulator_enable(pdata->regu_asp);
	if (0 != ret){
		printk( "asp_test:couldn't enable regulators %d\n", ret);
	}
	else {
		printk( "asp_test:Asp power up success\n");
	}
}


void asp_test_hifi_ddr(void)
{
	int i = 0;
	void* hifi_ddr_beg  = NULL;
	void* hifi_ddr_end  =NULL;

	printk( "asp_test: hifi ddr write read test  \n");
	hifi_ddr_beg = mem_remap_nocache(HIFI_BASE_ADDR,HIFI_SIZE - HIFI_IMAGE_SIZE);
	hifi_ddr_end  = hifi_ddr_beg + HIFI_SIZE - HIFI_IMAGE_SIZE;
	
	for(i=0;i<HIFI_DDR_TEST_SIZE;i=i+4) {
		*((unsigned int *)(hifi_ddr_beg+i))= 0x12345678;
	}

	for(i=0;i<HIFI_DDR_TEST_SIZE;i=i+4) {
		if( *((unsigned int *)(hifi_ddr_beg+i)) != 0x12345678 ){
			printk( "asp_test: hifi ddr write read test failed \n");
			break;
		}
	}

	vfree (hifi_ddr_beg);
	printk( "asp_test: hifi ddr write read test  seccess\n");
}

void asp_test_hifi_ocram(void)
{
	int i = 0;
	unsigned int   ocram_addr = 0xe8000000;
       void* 		ocram_virt   = NULL; 
	   
	printk( "asp_test: hifi ocram write read test  \n");
	
	ocram_virt = ioremap(ocram_addr, HIFI_OCRAM_TEST_SIZE);

	for(i=0;i<HIFI_OCRAM_TEST_SIZE;i=i+4) {
		*((unsigned int *)(ocram_virt+i)) = 0x12345678;
	}
	
	for(i=0;i<HIFI_OCRAM_TEST_SIZE;i=i+4) {
		if( *((unsigned int *)(ocram_virt+i)) != 0x12345678 ){
			printk( "asp_test: hifi ocram write read test failed \n");
		}
	}

	iounmap(ocram_virt);
	printk( "asp_test: hifi ocram write read test seccess  \n");
}

void asp_test_hifi_itcm(void)
{
	int i = 0;
	unsigned int     itcm_addr = 0xe8070000;
       void			*itcm_virt   = NULL; 
	   
	printk( "asp_test: hifi itcm write read test  \n");
	
	itcm_virt = ioremap(itcm_addr, HIFI_ITCM_TEST_SIZE);

	for(i=0;i<HIFI_ITCM_TEST_SIZE;i=i+4) {
		*((unsigned int *)(itcm_virt+i)) = 0x12345678;
	}
	
	for(i=0;i<HIFI_ITCM_TEST_SIZE;i=i+4) {
		if( *((unsigned int *)(itcm_virt+i)) != 0x12345678 ){
			printk( "asp_test: hifi itcm write read test failed \n");
		}
	}

	iounmap(itcm_virt);
	printk( "asp_test: hifi itcm write read test success\n");
}

void asp_test_hifi_dtcm(void)
{
	int i = 0;
	unsigned int   dtcm_addr = 0xe8058000;
       void 	    *dtcm_virt   = NULL; 
	   
	printk( "asp_test: hifi dtcm write read test  \n");
	
	dtcm_virt = ioremap(dtcm_addr, HIFI_DTCM_TEST_SIZE);

	for(i=0;i<HIFI_DTCM_TEST_SIZE;i=i+4) {
		*((unsigned int *)(dtcm_virt+i)) = 0x12345678;
	}
	
	for(i=0;i<HIFI_DTCM_TEST_SIZE;i=i+4) {
		if( *((unsigned int *)(dtcm_virt+i))  != 0x12345678 ){
			printk( "asp_test: hifi dtcm write read test failed \n");
		}
	}
	iounmap(dtcm_virt);
	printk( "asp_test: hifi dtcm write read test success \n");
}

static unsigned int reg_read(void* base_addr, unsigned int reg)
{
    int ret = 0;
    ret = readl(base_addr + reg);
    return ret;
}

static unsigned int reg_write(void* base_addr, unsigned int reg, unsigned int value)
{
    writel(value, base_addr + reg);
    return 0;
}
void asp_test_dma(void)
{
	unsigned int cnt0_0 	= TX_SIZE;
	unsigned int config  	= 0xcff33081;;	
	unsigned int i 			= 0;
	unsigned int value 	= 0;
	unsigned int count  	= 0;
 	void* src_addr_v  	= NULL;
	void* des_addr_v  	= NULL; 
	
	dma_addr_t src_dma_addr;
	dma_addr_t dst_dma_addr;	
	
    	g_dmac_base_addr      = ioremap(BASE_ADDR_ASP_DMAC, BASE_ADDR_ASP_DMAC_SIZE);
    	pr_info("asp_test: set_base_addr g_dmac_base_addr = 0x%p\n",     	g_dmac_base_addr);

	
	//alloc memery for dma
	src_addr_v  = dma_alloc_coherent (&s_dev->dev, TX_SIZE,&src_dma_addr,GFP_KERNEL);	
	des_addr_v = dma_alloc_coherent (&s_dev->dev, TX_SIZE,&dst_dma_addr,GFP_KERNEL);
	
	pr_info("asp_test:des_addr_v:0x%p,src_dma_addr = 0x%x \n",src_addr_v, src_dma_addr);
	pr_info("asp_test:des_addr_v:0x%p,dst_dma_addr = 0x%x \n",des_addr_v,dst_dma_addr);

	if (src_addr_v == NULL || des_addr_v ==  NULL) {
	    pr_err("%s, malloc memary error\n", __FUNCTION__); 
	    return;   
	}

	//init memery
	pr_info("asp_test:init src memery to 0x12345678 \n");
	for (i = 0; i < TX_SIZE;i=i+4) {
	    *((unsigned int *)(src_addr_v+i)) = 0x12345678;
        	//pr_info("addr = 0x%p, value = 0x%x \n",src_addr_v+i, *((unsigned int *)(src_addr_0+i)));
	}
	
	pr_info("audio:init des memery to 0x87654321 \n");
	for (i = 0; i < TX_SIZE;i=i+4) {
	    *((unsigned int *)(des_addr_v+i)) = 0x87654321;
       // pr_info("des_addr_0 = 0x%p, value = 0x%x \n",des_addr_0+i, *((unsigned int *)(des_addr_0+i)));
	}

	
	pr_info("audio:set tc1 err1 err2 mast to 0xfff \n");
	reg_write(g_dmac_base_addr, HI3650_ASP_EDMAC_INT_TC1_MASK_0_REG, 	 	CH_UNMASK);
	reg_write(g_dmac_base_addr, HI3650_ASP_EDMAC_INT_ERR1_MASK_0_REG, 	CH_UNMASK);
	reg_write(g_dmac_base_addr, HI3650_ASP_EDMAC_INT_ERR2_MASK_0_REG, 	CH_UNMASK);

	
	pr_info("asp_test:set dma src addr,src_dma_addr = %#x \n",src_dma_addr);
    	reg_write(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG, src_dma_addr);
    	value = reg_read(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG);
	pr_info("asp_test:HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG:%#x\n", value);
	
	pr_info("asp_test:set dma des addr,dst_dma_addr = %#x \n",dst_dma_addr);
	reg_write(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG, dst_dma_addr);
	value = reg_read(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG);
	pr_info("asp_test:%s HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG:%#x\n", __FUNCTION__, value);
	
	pr_info("asp_test:set dma count,cnt0_0 = %#x \n",cnt0_0);
	reg_write(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_CNT0_0_REG, cnt0_0);
	value = reg_read(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_CNT0_0_REG);
	pr_info("asp_test:%s HI3650_ASP_EDMAC_CX_CNT0_0_REG:%#x\n", __FUNCTION__, value);
	
	pr_info("asp_test:set dma config,cfg_0 = %#x \n",config);
	reg_write(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_CONFIG_0_REG, config);
	value = reg_read(g_dmac_base_addr, HI3650_ASP_EDMAC_CX_CONFIG_0_REG);
	pr_info("asp_test:%s HI3650_ASP_EDMAC_CX_CONFIG_0_REG:%#x\n", __FUNCTION__, value);

	
   	 if ( 0 == memcmp((void *)src_addr_v, (void *)des_addr_v, cnt0_0)) {
        	pr_info("asp_test:%s dma transit success!\n",__FUNCTION__);  
    	} else {
        	pr_info("asp_test:%s dma transit failed!\n",__FUNCTION__);
        	pr_info("asp_test:There is some error occur!\n");  
             
		for (i = 0; i < TX_SIZE;i=i+4) {
			value = *((unsigned int *)(des_addr_v+i));
			pr_info("asp_test:des_addr_v = 0x%p, value = 0x%x \n",des_addr_v+i, value);
		}
    	}

	dma_free_coherent(&s_dev->dev, TX_SIZE, src_addr_v, src_dma_addr);
	dma_free_coherent(&s_dev->dev, TX_SIZE, des_addr_v, dst_dma_addr);
		
}

void asp_test_codec_version(void)
{
	void *codec_ssi_v =NULL;
	int version;
	
	printk( "asp_test: codec version  read test \n");
	
	codec_ssi_v = ioremap(CODEC_SSI_BASE_ADDR, CODEC_SSI_SIZE);

	// ssi page select
	writel (0x70, codec_ssi_v + 0x7F4);
	writel (0x00, codec_ssi_v + 0x7F8);
	writel (0x20, codec_ssi_v + 0x7Fc);
	
	// read version reg
	version = readl(codec_ssi_v);
	if(0x11 == version){
		printk( "asp_test: codec is cs,version  = %d\n",version);	
	}
	else if(0x1 == version ){
		printk( "asp_test: codec is es,version  = %d\n",version);	
	}
	else {
		printk( "asp_test: codec version  read test failed\n");	
	}
	
	printk( "asp_test: codec version  read test end\n");	
	iounmap(codec_ssi_v);
}


void asp_test_cfg_reg(void)
{	
	void *cfg_reg_v =NULL;
	int     value;
	printk( "asp_test: asp cfg reg read write test \n");
	
	cfg_reg_v = ioremap(ASP_REG_BASE_ADDR, ASP_REG_SIZE);
	value = readl(cfg_reg_v+0x118);
	
	if(0x104 == value){
		printk("read asp reg success, R_GATE_CLKEN = 0x%x \n", value);
	}
	else {
		printk("read asp reg failed, R_GATE_CLKEN = 0x%x \n",value);
	}
	
	printk( "asp_test: asp cfg reg read write test end \n");
	iounmap(cfg_reg_v);
}

void asp_test_select(int select)
{
	switch(select){
		case 0:			
			asp_powerup();
			asp_test_hifi_ddr();
			asp_test_hifi_itcm();
			asp_test_hifi_dtcm();
			asp_test_hifi_ocram();
			asp_test_dma();	
			break;
		case 1:
			asp_powerup();
			break;
		case 2:
			asp_test_hifi_ddr();
			break;
		case 3:
			asp_test_hifi_itcm();
			break;
		case 4:
			asp_test_hifi_dtcm();
			break;
		case 5:
			asp_test_hifi_ocram();
			break;
		case 6:
			asp_test_dma();	
			break;
		case 7:
			asp_test_codec_version();
			break;
		case 8:
			asp_test_cfg_reg();
			break;
		default:
			printk("Error select,no the test \n");
			break;			
	}
}

static int soc_sio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi3630_sio_platform_data *pdata = NULL;
	const struct of_device_id *match;
	int ret = -1;

	BUG_ON(NULL == dev);

	s_dev = pdev;
		
	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (NULL == pdata){
		dev_err(dev, "cannot allocate hi6401 codec platform data\n");
		return -ENOMEM;
	}

	pdata->dev = dev;

	pdata->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (NULL == pdata->res) {
		dev_err(dev, "platform_get_resource err\n");
		return -ENOENT;
	}

	pdata->reg_base_addr = devm_ioremap(dev, pdata->res->start,
					    resource_size(pdata->res));
	if (NULL == pdata->reg_base_addr) {
		dev_err(dev, "cannot map register memory\n");
		return -ENOMEM;
	}
#ifdef PINCTRL_ENABLE
	/* get pinctrl */
	pdata->pctrl = pinctrl_get(dev);
	if (IS_ERR(pdata->pctrl)) {
		dev_err(dev, "could not get pinctrl\n");
		return -ENOENT;
	}
#endif 
	match = of_match_device(hi3630_sio_of_match, dev);
	if (!match) {
		dev_err(dev, "get device info err\n");
		return -ENOENT;
	} else {
		struct device_node *node = dev->of_node;

		/* get defination */
		pdata->is_master = of_property_read_bool(node, "hisilicon,is_master");
	}

	logi("sio is_master = %s\n", pdata->is_master ? "t":"f");

	/* rename device name */
	switch (pdata->res->start) {
	case SIO_AUDIO_ADDR:
		dev_set_name(dev, "sio-audio");
		pdata->id = SIO_AUDIO_ID;
		pdata->pb_active = 0;

#ifdef  REGULATOR_ENABLE
		pdata->regu_asp = devm_regulator_get(dev,"sio-audio");
		if (IS_ERR(pdata->regu_asp)) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif
		break;
	case SIO_VOICE_ADDR:
		dev_set_name(dev, "sio-voice");
		pdata->id = SIO_VOICE_ID;

#ifdef  REGULATOR_ENABLE
		pdata->regu_asp = devm_regulator_get(dev,"sio-voice");
		if (IS_ERR(pdata->regu_asp)) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif
		break;
	case SIO_BT_ADDR:
		dev_set_name(dev, "sio-bt");
		pdata->id = SIO_BT_ID;

#ifdef  REGULATOR_ENABLE
		pdata->regu_asp = devm_regulator_get(dev,"sio-bt");
		if (IS_ERR(pdata->regu_asp)) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif
		break;
	case SIO_MODEM_ADDR:
		dev_set_name(dev, "sio-modem");
		pdata->id = SIO_MODEM_ID;

#ifdef  REGULATOR_ENABLE
		pdata->regu_asp = devm_regulator_get(dev,"sio-modem");
		if (IS_ERR(pdata->regu_asp)) {
			dev_err(dev, "couldn't get regulators %d\n", ret);
			return -ENOENT;
		}
#endif

		break;
	default:
		dev_err(dev, "unknown sio\n");
		break;
	}

	mutex_init(&pdata->mutex);

	pdata->active_count = 0;

	platform_set_drvdata(pdev, pdata);

#ifdef CONFIG_PM_RUNTIME
	pm_runtime_set_autosuspend_delay(dev, 100); /* 100ms */
	pm_runtime_use_autosuspend(dev);

	pm_runtime_enable(dev);
#endif
	return snd_soc_register_component(&pdev->dev, &hi3630_sio_component,
					  &hi3630_sio_dai, 1);
}

static int soc_sio_remove(struct platform_device *pdev)
{
	struct hi3630_sio_platform_data *pdata = platform_get_drvdata(pdev);
	BUG_ON(NULL == pdata);
#ifdef PINCTRL_ENABLE
	pinctrl_put(pdata->pctrl);
#endif
	snd_soc_unregister_component(&pdev->dev);
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_disable(&pdev->dev);
#endif
	return 0;
}

#ifdef CONFIG_PM_RUNTIME
int hi3630_sio_runtime_suspend(struct device *dev)
{
	struct hi3630_sio_platform_data *pdata = dev_get_drvdata(dev);
	struct pinctrl_state *pinctrl_state;
	int ret = 0;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	/* VOICE SIO handled in HiFi */
	if (SIO_VOICE_ID == pdata->id) {
		goto err_exit;
	}
#ifdef REGULATOR_ENABLE
	regulator_disable(pdata->regu_asp);
#endif
#ifdef PINCTRL_ENABLE
	pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR(pinctrl_state)) {
		pr_err("%s : could not get defstate (%li)\n",
				__FUNCTION__ , PTR_ERR(pinctrl_state));
		ret = -ENOENT;
		goto err_exit;
	}
	ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
	if (0 != ret) {
		pr_err("%s : could not set pins to idle state\n",
				__FUNCTION__);
		ret = -ENOENT;
	}
#endif
err_exit:
	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

int hi3630_sio_runtime_resume(struct device *dev)
{
	struct hi3630_sio_platform_data *pdata = dev_get_drvdata(dev);
	struct pinctrl_state *pinctrl_state;
	int ret = 0;

	BUG_ON(NULL == pdata);

	dev_info(dev, "%s+", __FUNCTION__);

	/* VOICE SIO handled in HiFi */
	if (SIO_VOICE_ID == pdata->id) {
		goto err_exit;
	}

#ifdef PINCTRL_ENABLE
	pinctrl_state = pinctrl_lookup_state(pdata->pctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(pinctrl_state)) {
		pr_err("%s : could not get defstate (%li)\n",
				__FUNCTION__ , PTR_ERR(pinctrl_state));
		ret = -ENOENT;
		goto err_exit;
	}

	ret = pinctrl_select_state(pdata->pctrl, pinctrl_state);
	if (0 != ret) {
		pr_err("%s : could not set pins to default state\n", __FUNCTION__);
		goto err_exit;
	}
#endif 

#ifdef  REGULATOR_ENABLE
	
	ret = regulator_enable(pdata->regu_asp);
	if (0 != ret){
		dev_err(dev, "couldn't enable regulators %d\n", ret);
	}
	else {
		dev_err(dev, "============== Enable regulators ===========\n");
	}
	
#endif

err_exit:
	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

const struct dev_pm_ops hi3630_sio_pm_ops = {
	.runtime_suspend	= hi3630_sio_runtime_suspend,
	.runtime_resume		= hi3630_sio_runtime_resume,
};
#endif

static struct platform_driver hi3630_sio_driver = {
	.driver = {
		.name	= "hi3630-sio",
		.owner	= THIS_MODULE,
		.of_match_table = hi3630_sio_of_match,
#ifdef CONFIG_PM_RUNTIME
		.pm	= &hi3630_sio_pm_ops,
#endif
	},
	.probe	= soc_sio_probe,
	.remove	= soc_sio_remove,
};

static int __init hi_sio_init(void)
{
    pr_info("%s begin\n",__FUNCTION__);

    return platform_driver_register(&hi3630_sio_driver);
}
module_init(hi_sio_init);

static void __exit hi_sio_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&hi3630_sio_driver);
}
module_exit(hi_sio_exit);

//module_platform_driver(hi_asp_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("sio driver");
MODULE_LICENSE("GPL and additional rights");
MODULE_ALIAS("platform:hi3630_sio");
