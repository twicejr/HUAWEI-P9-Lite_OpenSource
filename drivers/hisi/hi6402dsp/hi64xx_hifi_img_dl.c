/*
 * hi64xx_hifi_img_dl.h -- 64xx hifi img download
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <linux/reboot.h>

#include <linux/firmware.h>
#include <linux/errno.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/hisi/etb.h>
#include <dsm/dsm_pub.h>
#include <linux/hisi/rdr_pub.h>

#include <hi6402_algo_interface.h>
#include <hi6402_hifi_interface.h>
#include <linux/hisi/hi64xx/hi64xx_dsp_regs.h>
#include "hi64xx_hifi_debug.h"
#include "slimbus.h"
#include "hi64xx_hifi_img_dl.h"

#define HI6402_DMA_CH_COUNT 16
#define HI6402_DMA_TIMEOUT 1000
#define HI6402_DMA_PAGESIZE (25*1024)
#define HI6402_DMA_WIDTH 16
#define DMA_IMG_DL_CH 10

#define SLIMBUS_PORT4_ADDR                 0xe8051100
#define HI6402_DSP_IF2                	   0x20012000
#define HI6402_SC_S2_IF_L                  (HI64xx_CODE_CORE_BASE + 0x02)
#define HI6402_SC_FS_S2_CTRL_L             (HI64xx_CODE_CORE_BASE + 0xB0)

uint64_t soc_dma_vir = 0x0;

struct hi64xx_hifi_img_dl_priv {
	struct hi64xx_irq *p_irq;
	uint32_t	*src_addr_v;
	dma_addr_t	 src_dma_addr;
	struct hi64xx_hifi_img_dl_config dl_config;
};

struct hi64xx_hifi_img_dl_priv *dl_data = NULL;

extern int slimbus_bus_configure(slimbus_bus_config_type_t type);

static int hi64xx_soc_dma_stop(int ch)
{
	int count = 0;

	/* stop dma */
	REG_CLEAR_BIT(ASP_DMAC_CX_CONFIG(ch), 0);

	/* wait dma transfer done */
	do {
		if(0 == (readl(ASP_DMAC_STAT) & (1 << ch))) {
			return 0;
		}
		count++;
	} while(count < HI6402_DMA_TIMEOUT);

	HI64XX_DSP_ERROR("dma not free ch_stat0x%x\n", hi64xx_hifi_read_reg(HI64xx_DMA_CH_STAT));
	return -EBUSY;

}

static int hi64xx_codec_dma_stop(int ch)
{
	int count = 0;

	/* stop dma */
	hi64xx_hifi_reg_clr_bit(HI64xx_CX_CONFIG(ch), 0);

	/* wait dma transfer done */
	do {
		if(0 == (hi64xx_hifi_read_reg(HI64xx_DMA_CH_STAT) & (1 << ch))) {
			return 0;
		}
		count++;
	} while(count < HI6402_DMA_TIMEOUT);

	HI64XX_DSP_ERROR("dma not free ch_stat0x%x\n", hi64xx_hifi_read_reg(HI64xx_DMA_CH_STAT));
	return -EBUSY;
}

int hi64xx_release_all_dma(void)
{
	int ch_num = 0;
	int ret = 0;

	for (ch_num = 0; ch_num < HI6402_DMA_CH_COUNT; ch_num++) {
		ret =  hi64xx_codec_dma_stop(ch_num);
		if (0 != ret) {
			//TODO : yhj retry maybe work! close dspif then close dma
			break;
		}
	}

	return ret;
}

static void hi64xx_img_bss_page_dl(uint32_t des_addr, uint32_t src_addr, uint32_t size)
{
	int timeout = 0;
	IN_FUNCTION

	/* 6402 dma buffer->buffer*/
	hi64xx_hifi_write_reg(HI64xx_CX_CNT0(DMA_IMG_DL_CH), size);
	hi64xx_hifi_write_reg(HI64xx_CX_DES_ADDR(DMA_IMG_DL_CH), des_addr);
	hi64xx_hifi_reg_set_bit(HI64xx_CX_CONFIG(DMA_IMG_DL_CH), 0);

	do {
		usleep_range(100, 150);
		if (timeout++ > HI6402_DMA_TIMEOUT) {
			HI64XX_DSP_ERROR("bss timeout!codec dma curr count 0x%x, codec dma cfg 0x%x\n",
							 hi64xx_hifi_read_reg(HI64xx_CX_CURR_CNT0(DMA_IMG_DL_CH)),
							 hi64xx_hifi_read_reg(HI64xx_CX_CONFIG(DMA_IMG_DL_CH)));
			if (0 != hi64xx_codec_dma_stop(DMA_IMG_DL_CH)) {
				HI64XX_DSP_ERROR("section download error des_addr 0x%x\n", des_addr);
				return;
			}
			break;
		}
	} while (hi64xx_hifi_read_reg(HI64xx_CX_CONFIG(DMA_IMG_DL_CH)) & 0x1);
	OUT_FUNCTION

}

static void hi64xx_img_page_dl(uint32_t des_addr, uint32_t src_addr, uint32_t size)
{
	int count = 0;

	/* codec dma */
	hi64xx_hifi_write_reg(HI64xx_CX_CNT0(DMA_IMG_DL_CH), size);
	hi64xx_hifi_write_reg(HI64xx_CX_DES_ADDR(DMA_IMG_DL_CH), des_addr);

	/* start codec dma */
	hi64xx_hifi_reg_set_bit(HI64xx_CX_CONFIG(DMA_IMG_DL_CH), 0);

	/* set asp dma */
	writel(size*2, ASP_DMAC_CX_CNT0(DMA_IMG_DL_CH));
	writel(src_addr, ASP_DMAC_CX_SRC_ADDR(DMA_IMG_DL_CH));
	REG_SET_BIT(ASP_DMAC_CX_CONFIG(DMA_IMG_DL_CH), 0);

	/* enable dspif2 clk */
	hi64xx_hifi_reg_set_bit(dl_data->dl_config.dspif_clk_en_addr, 2);

	usleep_range(1000, 1050);

	slimbus_track_activate(SLIMBUS_DEVICE_HI6403, SLIMBUS_TRACK_IMAGE_LOAD);

	do {
		usleep_range(100, 150);
		if (count++ > HI6402_DMA_TIMEOUT) {
			HI64XX_DSP_ERROR("soc dma curr count 0x%x, soc dma cfg 0x%x,"
							 "codec dma curr count 0x%x, codec dma cfg 0x%x\n",
							 readl(ASP_DMAC_CX_CURR_CNT0(DMA_IMG_DL_CH)),
							 readl(ASP_DMAC_CX_CONFIG(DMA_IMG_DL_CH)),
							 hi64xx_hifi_read_reg(HI64xx_CX_CURR_CNT0(DMA_IMG_DL_CH)),
							 hi64xx_hifi_read_reg(HI64xx_CX_CONFIG(DMA_IMG_DL_CH)));

			/* transfer timeout stop dma */
			if (0 != hi64xx_codec_dma_stop(DMA_IMG_DL_CH)) {
				HI64XX_DSP_ERROR("section download error des_addr 0x%x\n", des_addr);
				return;
			}
			if(0 != hi64xx_soc_dma_stop(DMA_IMG_DL_CH)) {
				HI64XX_DSP_ERROR("section download error des_addr 0x%x\n", des_addr);
				return;
			}
			break;
		}
	} while ((readl(ASP_DMAC_CX_CONFIG(DMA_IMG_DL_CH)) & 0x1)
			||(hi64xx_hifi_read_reg(HI64xx_CX_CONFIG(DMA_IMG_DL_CH)) & 0x1));

	slimbus_track_deactivate(SLIMBUS_DEVICE_HI6403, SLIMBUS_TRACK_IMAGE_LOAD);
	hi64xx_hifi_reg_clr_bit(dl_data->dl_config.dspif_clk_en_addr,2);
}

/*
 *	dsp img download
 */
static int hi64xx_hifi_fw_section_head_check(struct drv_hifi_image_head *img_head,
						 struct drv_hifi_image_sec *img_sec)
{
	/* BSS section do not need check offset and size,
	 * beacuse BSS section only record address and length, the content is 0 */
	if (img_sec->type == DRV_HIFI_IMAGE_SEC_TYPE_BSS
		&& (img_sec->sn < img_head->sections_num)
		&& (img_sec->load_attib < (unsigned char)DRV_HIFI_IMAGE_SEC_LOAD_BUTT))
		return 0;

	/* check section number and section size  */
	if ((img_sec->sn >= img_head->sections_num)
		|| (img_sec->src_offset + img_sec->size > img_head->image_size)
		|| (img_sec->type >= (unsigned char)DRV_HIFI_IMAGE_SEC_TYPE_BUTT)
		|| (img_sec->load_attib >= (unsigned char)DRV_HIFI_IMAGE_SEC_LOAD_BUTT))
	{
		HI64XX_DSP_ERROR("hifi: drv_hifi_check_sections ERROR.\n");
		return -1;
	}

	return 0;
}


static int hi64xx_hifi_fw_head_check(struct drv_hifi_image_head *head)
{
	int i = 0;
	int ret = 0;

	for (i = 0; i < head->sections_num; i++) {
		/* check the sections */
		ret = hi64xx_hifi_fw_section_head_check(head, &(head->sections[i]));

		if (ret != 0) {
			HI64XX_DSP_INFO("hifi: Invalid hifi section\n");
			goto exit;
		}
	}

exit:
	return ret;
}

static void hi64xx_img_sec_dl_reg(uint32_t *src, uint32_t des, int size, int type)
{
	switch (type) {
	case DRV_HIFI_IMAGE_SEC_TYPE_BSS:
		hi64xx_memset(des, size);
		break;
	case DRV_HIFI_IMAGE_SEC_TYPE_CODE:
	case DRV_HIFI_IMAGE_SEC_TYPE_DATA:
		hi64xx_memcpy(des, src, size);
		break;
	default:
		break;
	}
}

static void hi64xx_img_sec_dl_dma(uint32_t *src_addr, uint32_t des_addr, int type,
									int size)
{
	int i = 0;
	uint32_t dma_size = 0;
	int pagenum = size/HI6402_DMA_PAGESIZE;
	int pageextra = size%HI6402_DMA_PAGESIZE;
	int bytesleft = pageextra%HI6402_DMA_WIDTH;
	uint32_t *src_addr_v = dl_data->src_addr_v;

	switch (type) {
	case DRV_HIFI_IMAGE_SEC_TYPE_BSS:
		hi64xx_hifi_write_reg(des_addr, 0x0);
		hi64xx_hifi_write_reg(HI64xx_CX_SRC_ADDR(DMA_IMG_DL_CH), des_addr);
		hi64xx_hifi_write_reg(HI64xx_CX_CONFIG(DMA_IMG_DL_CH), 0x40022002);
		for (i = 0; i <= pagenum; i++) {
			if(i == pagenum) {
				dma_size = pageextra - bytesleft;
			} else {
				dma_size = HI6402_DMA_PAGESIZE;
			}
			hi64xx_img_bss_page_dl(des_addr + HI6402_DMA_PAGESIZE*i + 4, des_addr, dma_size);
		}
		break;
	case DRV_HIFI_IMAGE_SEC_TYPE_CODE:
	case DRV_HIFI_IMAGE_SEC_TYPE_DATA:
		for (i = 0; i < size/4; i++) {
			src_addr_v[2*i] = (src_addr[i]&0x0000ffff)<<16;
			src_addr_v[2*i+1] = src_addr[i]&0xffff0000;
		}

		HI64XX_DSP_INFO("codec dma des phy addr:0x%x, size:0x%x\n", des_addr, size);

		hi64xx_hifi_write_reg(HI64xx_CX_SRC_ADDR(DMA_IMG_DL_CH), HI6402_DSP_IF2);
		hi64xx_hifi_write_reg(HI64xx_CX_CONFIG(DMA_IMG_DL_CH), 0x47711046);
		writel(0x83322046, ASP_DMAC_CX_CONFIG(DMA_IMG_DL_CH));
		writel(SLIMBUS_PORT4_ADDR, ASP_DMAC_CX_DES_ADDR(DMA_IMG_DL_CH));

		for (i = 0; i <= pagenum; i++) {
			if(i == pagenum) {
				dma_size = pageextra - bytesleft;
			} else {
				dma_size = HI6402_DMA_PAGESIZE;
			}
			hi64xx_img_page_dl(des_addr + HI6402_DMA_PAGESIZE*i,
							   (dl_data->src_dma_addr + HI6402_DMA_PAGESIZE*i*2),
							   dma_size);
		}
		if(bytesleft > 0) {
			HI64XX_DSP_INFO("reg write size:%d\n", bytesleft);
			des_addr = des_addr + size - bytesleft;
			hi64xx_img_sec_dl_reg(src_addr + (size - bytesleft)/4, des_addr, bytesleft,
									DRV_HIFI_IMAGE_SEC_TYPE_CODE);
		}
		break;
	default:
		HI64XX_DSP_ERROR("section type invalid\n");
		break;
	}
}

void hi64xx_hifi_download_slimbus(const struct firmware *fw)
{
	struct drv_hifi_image_head *head = NULL;
	uint32_t *src_addr;
	uint32_t des_addr;
	int i = 0;

	hi64xx_hifi_reg_write_bits(HI64xx_AUDIO_CLK_EN, 0x3, 0x3);

	/* TODO: yhj dp clk should not enable here!!! */
	hi64xx_hifi_reg_set_bit(HI64xx_CODEC_DP_CLK_EN, 0);

	/* disable RX, TX */
	hi64xx_hifi_reg_write_bits(HI6402_SC_S2_IF_L, 0x0, 0x3);
	/* disable i2s2 clk */
	hi64xx_hifi_reg_clr_bit(HI6402_SC_FS_S2_CTRL_L, 3);
	/* slibus i2s mux */
	hi64xx_hifi_write_reg(HI64xx_SC_CODEC_MUX_SEL3_0,	0x3f);
	hi64xx_hifi_reg_write_bits(HI64xx_SC_FS_SELC_TRL,	0xc, 0xc);
	hi64xx_hifi_reg_set_bit(HI64xx_SLIM_CTRL1, 0);
	/* close S2 src clk and pga clk */
	hi64xx_hifi_write_reg(HI64xx_S2_DP_CLK_EN,	0x0);
	/* set slimbus */
	slimbus_bus_configure(SLIMBUS_BUS_CONFIG_IMGDOWN);
	slimbus_track_configure(SLIMBUS_DEVICE_HI6403, SLIMBUS_TRACK_IMAGE_LOAD, NULL);

	soc_dma_vir = (uint64_t)ioremap(ASP_DMAC_BASE_ADDR, ASP_DMAC_SIZE);
	if (!soc_dma_vir) {
		HI64XX_DSP_ERROR("asp dmac base addr remap error\n");
		goto err;
	}

	hi64xx_soc_dma_stop(DMA_IMG_DL_CH);

	head = (struct drv_hifi_image_head *)fw->data;
	if(0 != hi64xx_hifi_fw_head_check(head)) {
		HI64XX_DSP_ERROR("img head invalid!\n");
		goto err;
	}

	HI64XX_DSP_INFO("img down begin, size:[%zu] !\n", fw->size);

	for (i = 0; i < head->sections_num; i++) {
		src_addr = (unsigned int *)((char *)head + head->sections[i].src_offset);
		des_addr = head->sections[i].des_addr;

		if (head->sections[i].size > IMAGEDOWN_SIZE_THRESH) {
			hi64xx_img_sec_dl_dma(src_addr, des_addr, head->sections[i].type,
								  head->sections[i].size);
		} else {
			hi64xx_img_sec_dl_reg(src_addr, des_addr, head->sections[i].size,
								  head->sections[i].type);
		}
	}

	iounmap((void __iomem *)soc_dma_vir);

err:
	slimbus_track_remove(SLIMBUS_DEVICE_HI6403, SLIMBUS_TRACK_IMAGE_LOAD);
	slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
	hi64xx_hifi_reg_clr_bit(HI64xx_SLIM_CTRL1, 0);
	hi64xx_hifi_write_reg(HI64xx_SC_CODEC_MUX_SEL3_0, 0x33);
	hi64xx_hifi_reg_write_bits(HI64xx_SC_FS_SELC_TRL, 0x0, 0xc0);
}

void hi64xx_hifi_download(const struct firmware *fw)
{
	struct drv_hifi_image_head *head = NULL;
	unsigned int des_addr;
	unsigned int *src_addr;
	int i = 0;
	int ret = 0;

	HI64XX_DSP_INFO("img dl++, size:[%zu] !\n", fw->size);

	head = (struct drv_hifi_image_head *)fw->data;
	if(!head) {
		HI64XX_DSP_ERROR("img head is null\n");
		return;
	}
	ret = hi64xx_hifi_fw_head_check(head);
	if(0 != ret) {
		HI64XX_DSP_ERROR("img head is invalid\n");
		return;
	}

	slimbus_bus_configure(SLIMBUS_BUS_CONFIG_REGIMGDOWN);
	for (i = 0; i < head->sections_num; i++) {
		src_addr = (unsigned int *)((char *)head + head->sections[i].src_offset);
		des_addr = head->sections[i].des_addr;
		HI64XX_DSP_DEBUG("hifi: sections_num = %d,des_addr = 0x%x, load_attib = %d, size = 0x%x,"
				 " sn = %d, src_offset = 0x%x, type = %d\n", \
				 head->sections_num,\
				 head->sections[i].des_addr,\
				 head->sections[i].load_attib,\
				 head->sections[i].size,\
				 head->sections[i].sn,\
				 head->sections[i].src_offset,\
				 head->sections[i].type);
		HI64XX_DSP_INFO("[0x%p]->[0x%x]\n", src_addr, des_addr);
		hi64xx_img_sec_dl_reg(src_addr, des_addr,
							  head->sections[i].size, head->sections[i].type);
	}
	slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);

	HI64XX_DSP_INFO("img dl--\n");
}

int hi64xx_hifi_img_dl_init(struct hi64xx_irq *irqmgr,
			struct hi64xx_hifi_img_dl_config *dl_config)
{
	int image_down_size = IMAGE_DOWN_MEM_SIZE;

	dl_data = kzalloc(sizeof(*dl_data), GFP_KERNEL);
	if(!dl_data){
		pr_err("%s : kzalloc error!\n", __FUNCTION__);
		return -ENOMEM;
	}

	memcpy(&dl_data->dl_config, dl_config, sizeof(*dl_config));

	dl_data->p_irq = irqmgr;

	dl_data->src_addr_v = dma_alloc_coherent(dl_data->p_irq->dev,
				image_down_size, &(dl_data->src_dma_addr), GFP_KERNEL);
	if (!dl_data->src_addr_v)
		HI64XX_DSP_WARNING("dma alloc failed\n");

	return 0;
}
EXPORT_SYMBOL(hi64xx_hifi_img_dl_init);

void hi64xx_hifi_img_dl_deinit(void)
{
	int image_down_size = IMAGE_DOWN_MEM_SIZE;

	if (!dl_data)
		return;

	dma_free_coherent(dl_data->p_irq->dev, image_down_size,
			dl_data->src_addr_v, dl_data->src_dma_addr);

	kfree(dl_data);

	dl_data = NULL;

	return;
}
EXPORT_SYMBOL(hi64xx_hifi_img_dl_deinit);

MODULE_DESCRIPTION("hi64xx hifi misc driver");
MODULE_LICENSE("GPL");
