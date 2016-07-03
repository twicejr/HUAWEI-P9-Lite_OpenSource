/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/mfd/hi3630_asp_irq.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>

#include "slimbus.h"
#include "slimbus_drv.h"
#include "hi3630_asp_common.h"
#include "slimbus_utils.h"
#include <hisi/hilog.h>
#include <dsm/dsm_pub.h>


#define LOG_TAG "Slimbus"

extern int create_hi6403_slimbus_device(slimbus_device_info_t **device);
extern int create_hi6402_slimbus_device(slimbus_device_info_t **device);
extern int release_hi6403_slimbus_device(slimbus_device_info_t *device);
extern int release_hi6402_slimbus_device(slimbus_device_info_t *device);
extern void slimbus_hi6403_param_init(slimbus_device_info_t *dev);
extern void slimbus_hi6402_param_init(slimbus_device_info_t *dev);
extern int slimbus_hi6403_param_set(
				slimbus_device_info_t *dev,
				slimbus_track_type_t   track_type,
				slimbus_track_param_t *params);
extern int slimbus_hi6402_param_set(
				slimbus_device_info_t *dev,
				slimbus_track_type_t   track_type,
				slimbus_track_param_t *params);

extern struct dsm_client *dsm_audio_client;


#define REG_VIR_ADDR_MAP(phyAddr)		 	ioremap(phyAddr, sizeof(unsigned long))
#define REG_VIR_ADDR_UNMAP(virAddr) 	 		iounmap(virAddr)
#define PMU_AUDIOCLK_ADDR				(0xfff34428)

slimbus_channel_property_t audio_playback[SLIMBUS_AUDIO_PLAYBACK_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t audio_capture[SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t voice_down[SLIMBUS_VOICE_DOWN_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t voice_up[SLIMBUS_VOICE_UP_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t img_download[SLIMBUS_IMAGE_DOWNLOAD_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t ec_ref[SLIMBUS_ECREF_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t sound_trigger[SLIMBUS_SOUND_TRIGGER_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t audio_debug[SLIMBUS_DEBUG_CHANNELS] = {{0,{0,},{{0,},},},};

struct slimbus_private_data
{
	void __iomem			*base_addr; 		/* SoC SLIMbus base address (virtual address) */
	void __iomem			*asp_reg_base_addr; /* asp address(virtual address) */
	void __iomem			*sctrl_base_addr;	/* sctrl address(virtual address) */
	uint32_t				asp_power_state_offset;
	int 					irq;				/* SoC SLIMbus irq num */
	struct regulator		*regu_asp;			/* regulator of asp */
	struct pinctrl			*pctrl;
	struct pinctrl_state	*pin_default;		/* pinctrl default */
	struct pinctrl_state	*pin_idle;			/* pinctrl idle */
	struct clk		*pmu_audio_clk; 	/* codec 19.2M clk */
	uint32_t		portstate;
	slimbus_framer_type_t	framerstate;
	slimbus_framer_type_t	lastframer;
	platform_type_t		platform_type;
	slimbus_device_type_t	device_type;
	struct timer_list	timer;
};

static struct slimbus_private_data *pdata;
slimbus_device_info_t *slimbus_devices[SLIMBUS_DEVICE_NUM] = {0};
uint32_t slimbus_log_count		= 300;
uint32_t slimbus_rdwrerr_times	= 0;
slimbus_device_info_t *slimbus_dev = NULL;

uint8_t track_state[SLIMBUS_TRACK_MAX];

/*
 * SLIMbus bus configuration
 */
slimbus_bus_config_t bus_config[SLIMBUS_BUS_CONFIG_MAX] = {
	/* normal run */
	{
		.sm = SLIMBUS_SM_4_CSW_32_SL,						/* control space:4; subframe length:32; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* img download */
	{
		.sm = SLIMBUS_SM_3_CSW_8_SL,						/* control space:3; subframe length:8; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* switch framer */
	{
		.sm = SLIMBUS_SM_4_CSW_32_SL,						 /* control space:4; subframe length:32; */
		.cg = SLIMBUS_CG_8, 								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* reg write img download */
	{
		.sm = SLIMBUS_SM_8_CSW_8_SL,						/* control space:8; subframe length:8; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
};

uint32_t slimbus_logcount_get(void)
{
	return slimbus_log_count;
}
EXPORT_SYMBOL(slimbus_logcount_get);

void slimbus_logcount_set(uint32_t count)
{
	slimbus_log_count = count;
}
EXPORT_SYMBOL(slimbus_logcount_set);

uint32_t slimbus_logtimes_get(void)
{
	return slimbus_rdwrerr_times;
}
EXPORT_SYMBOL(slimbus_logtimes_get);

void slimbus_logtimes_set(uint32_t times)
{
	slimbus_rdwrerr_times = times;
}
EXPORT_SYMBOL(slimbus_logtimes_set);


int slimbus_element_read(
				slimbus_device_info_t	*dev,
				int32_t			byte_address,
				slimbus_slice_size_t	slice_size,
				void			*value)
{
	static int slimbus_dmd_flag = 1;
	uint32_t reg_page = byte_address & (~0xff);
	uint8_t *paddr = (uint8_t*)&byte_address;
	uint8_t ret = 0;

	BUG_ON(slice_size >= SLIMBUS_SS_SLICE_BUT);

	mutex_lock(&dev->mutex);
	if (dev->page_sel_addr != reg_page) {
		ret  = slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (paddr+1));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (paddr+2));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (paddr+3));

		dev->page_sel_addr = reg_page;
	}
	ret += slimbus_drv_element_read(dev->generic_la, SLIMBUS_USER_DATA_BASE_ADDR + *paddr, slice_size, (uint8_t *)value);
	mutex_unlock(&dev->mutex);

	if (ret) {
		SLIMBUS_LIMIT_ERR("read error! slice_size=%d, addr=0x%x!\n", slice_size, byte_address);
		if (1 == slimbus_dmd_flag) {
			if (!dsm_client_ocuppy(dsm_audio_client)) {
				dsm_client_record(dsm_audio_client, "slice_size=%d, addr=0x%x\n",slice_size, byte_address);
				dsm_client_notify(dsm_audio_client, DSM_HI6402_SLIMBUS_READ_ERR);
				slimbus_dmd_flag = 0;
			}
		}
		return -EFAULT;
	}
	SLIMBUS_RECOVER_INFO("read recover, slice_size=%d, addr=%x!\n", slice_size, byte_address);

	return 0;
}

int slimbus_element_write(
				slimbus_device_info_t	*dev,
				int32_t			byte_address,
				slimbus_slice_size_t	slice_size,
				void			*value)
{
	uint32_t reg_page = byte_address & (~0xff);
	uint8_t *paddr = (uint8_t*)&byte_address;
	uint8_t ret = 0;

	BUG_ON(slice_size >= SLIMBUS_SS_SLICE_BUT);

	mutex_lock(&dev->mutex);
	if (dev->page_sel_addr != reg_page) {
		ret  = slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (paddr+1));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (paddr+2));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (paddr+3));

		dev->page_sel_addr = reg_page;
	}
	ret += slimbus_drv_element_write(dev->generic_la, (SLIMBUS_USER_DATA_BASE_ADDR + *paddr), slice_size, (uint8_t *)value);
	mutex_unlock(&dev->mutex);

	if (ret) {
		SLIMBUS_LIMIT_ERR("write error! slice_size=%d, addr=0x%x!\n", slice_size, byte_address);
		return -EFAULT;
	}
	SLIMBUS_RECOVER_INFO("write recover, slice_size=%d, addr=%x!\n", slice_size, byte_address);

	return 0;
}

unsigned int slimbus_reg_read_u32(unsigned int pAddr)
{
	unsigned int value = 0;
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	value = readl(virAddr);
	REG_VIR_ADDR_UNMAP(virAddr);

	return value;
}


unsigned int slimbus_read_1byte(unsigned int reg)
{
	static unsigned int value = 0;
	int retry_count = 0;
	static uint32_t info0 = 0xa1;
	static uint32_t info1 = 0xa2;
	static uint32_t info2 = 0xa3;
	static uint32_t info3 = 0xa4;

	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return -ENXIO;
	}

	value = 0x5A;
	do {
		slimbus_element_read(slimbus_dev, reg, SLIMBUS_SS_1_BYTE, &value);

		if (value == 0x5A) {
			SLIMBUS_LIMIT_INFO("SLIMbus read1byte retry: reg:%#x, val:%#x !\n", reg, value);
			retry_count++;
			mdelay(1);
		}
	} while ((value == 0x5A) && (retry_count <= 3));

	if (retry_count > 0) {
		uint32_t pmu_audioclk_val = 0;

		info0 = 0xa1;
		info1 = 0xa2;
		info2 = 0xa3;
		info3 = 0xa4;
		slimbus_drv_request_info(0x21, 0x400, SLIMBUS_SS_1_BYTE, &info0);
		slimbus_drv_request_info(0x40, 0x400, SLIMBUS_SS_1_BYTE, &info1);
		slimbus_drv_request_info(0x20, 0x400, SLIMBUS_SS_1_BYTE, &info2);
		slimbus_drv_request_info(0x41, 0x400, SLIMBUS_SS_1_BYTE, &info3);
		pmu_audioclk_val = slimbus_reg_read_u32(PMU_AUDIOCLK_ADDR);
		SLIMBUS_LIMIT_INFO("SLIMbus info: %#x, %#x, %#x, %#x ! clk: %#x \n", info0, info1, info2, info3, pmu_audioclk_val);
	}
	return value;
}
EXPORT_SYMBOL(slimbus_read_1byte);


unsigned int slimbus_read_4byte(unsigned int reg)
{
	static unsigned int value = 0;
	static int valbyte = 0;
	int retry_count = 0;

	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return -ENXIO;
	}

	value = 0x6A6A6A6A;
	valbyte = 0;
	do {
		slimbus_element_read(slimbus_dev, reg, SLIMBUS_SS_4_BYTES, &value);
		slimbus_element_read(slimbus_dev, 0x20007022, SLIMBUS_SS_1_BYTE, &valbyte);
		slimbus_element_read(slimbus_dev, 0x20007023, SLIMBUS_SS_4_BYTES, &value);

		if (value == 0x6A6A6A6A) {
			SLIMBUS_LIMIT_INFO("SLIMbus read4byte retry: reg:%#x, val:%#x !\n", reg, value);
			retry_count++;
			mdelay(1);
		}
	} while ((value == 0x6A6A6A6A) && (retry_count <= 3));

	return value;
}
EXPORT_SYMBOL(slimbus_read_4byte);

void slimbus_write_1byte(unsigned int reg, unsigned int val)
{
	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return;
	}

	slimbus_element_write(slimbus_dev, reg, SLIMBUS_SS_1_BYTE, &val);
}
EXPORT_SYMBOL(slimbus_write_1byte);

void slimbus_write_4byte(unsigned int reg, unsigned int val)
{
	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return;
	}

	slimbus_element_write(slimbus_dev, reg, SLIMBUS_SS_4_BYTES, &val);
}
EXPORT_SYMBOL(slimbus_write_4byte);

void slimbus_read_pageaddr(void)
{
	static int page0 = 0;
	static int page1 = 0;
	static int page2 = 0;

	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return;
	}

	page0 = 0xA5;
	page1 = 0xA5;
	page2 = 0xA5;
	mutex_lock(&slimbus_dev->mutex);
	slimbus_drv_element_read(slimbus_dev->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (uint8_t *)&page0);
	slimbus_drv_element_read(slimbus_dev->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (uint8_t *)&page1);
	slimbus_drv_element_read(slimbus_dev->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (uint8_t *)&page2);
	mutex_unlock(&slimbus_dev->mutex);

	pr_info("[%s:%d] cdc page addr:%#x, page0:%#x, page1:%#x, page2:%#x !\n",
		__FUNCTION__, __LINE__, slimbus_dev->page_sel_addr, page0, page1, page2);
}
EXPORT_SYMBOL(slimbus_read_pageaddr);


int slimbus_track_configure(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t	*params)
{
	int ret = 0;
	struct slimbus_device_info *dev = NULL;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	switch (track) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_configure(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_configure(audio_capture, dev->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_configure(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		if (!(dev->voice_up_chnum)) {
			dev->voice_up_chnum = SLIMBUS_VOICE_UP_CHANNELS;
		}
		ret = slimbus_drv_track_configure(voice_up, dev->voice_up_chnum);

		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_configure(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_configure(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		/*  request soc slimbus clk to 24.576M */
		slimbus_freq_request(pdata->asp_reg_base_addr);
		ret = slimbus_drv_track_configure(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		if (ret)
			break;
		ret = slimbus_drv_track_configure(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;
	case SLIMBUS_TRACK_DEBUG:
		ret = slimbus_drv_track_configure(audio_debug, SLIMBUS_DEBUG_CHANNELS);
		break;
	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		HiLOGE("audio", LOG_TAG, "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		break;
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_track_configure);

int slimbus_track_activate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track)
{
	int ret = 0;
	struct slimbus_device_info *dev = NULL;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	switch (track) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_activate(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_activate(audio_capture, dev->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_activate(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		ret = slimbus_drv_track_activate(voice_up, dev->voice_up_chnum);
		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_activate(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_activate(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		ret = slimbus_drv_track_activate(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		if (ret)
			break;
		ret = slimbus_drv_track_activate(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;
	case SLIMBUS_TRACK_DEBUG:
		ret = slimbus_drv_track_activate(audio_debug, SLIMBUS_DEBUG_CHANNELS);
		break;

	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		HiLOGE("audio", LOG_TAG, "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		break;
	}

	if (!ret)
		track_state[track] = 1;

	return ret;
}
EXPORT_SYMBOL(slimbus_track_activate);

int slimbus_track_deactivate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track)
{
	int ret = 0;
	struct slimbus_device_info *dev = NULL;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	switch (track) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_deactivate(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_deactivate(audio_capture, dev->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_deactivate(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		ret = slimbus_drv_track_deactivate(voice_up, dev->voice_up_chnum);
		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_deactivate(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_deactivate(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		(void)slimbus_drv_track_deactivate(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		ret = slimbus_drv_track_deactivate(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;
	case SLIMBUS_TRACK_DEBUG:
		ret = slimbus_drv_track_deactivate(audio_debug, SLIMBUS_DEBUG_CHANNELS);
		break;
	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		HiLOGE("audio", LOG_TAG,  "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		break;
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_track_deactivate);

int slimbus_track_remove(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track)
{
	int ret = 0;
	struct slimbus_device_info *dev = NULL;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	switch (track) {
	case SLIMBUS_TRACK_AUDIO_PLAY:
		ret = slimbus_drv_track_remove(audio_playback, SLIMBUS_AUDIO_PLAYBACK_CHANNELS);
		break;
	case SLIMBUS_TRACK_AUDIO_CAPTURE:
		ret = slimbus_drv_track_remove(audio_capture, dev->audio_up_chnum);
		break;
	case SLIMBUS_TRACK_VOICE_DOWN:
		ret = slimbus_drv_track_remove(voice_down, SLIMBUS_VOICE_DOWN_CHANNELS);
		break;
	case SLIMBUS_TRACK_VOICE_UP:
		ret = slimbus_drv_track_remove(voice_up, dev->voice_up_chnum);
		dev->voice_up_chnum = SLIMBUS_VOICE_UP_2CH;
		break;
	case SLIMBUS_TRACK_IMAGE_LOAD:
		ret = slimbus_drv_track_remove(img_download, SLIMBUS_IMAGE_DOWNLOAD_CHANNELS);
		break;
	case SLIMBUS_TRACK_ECREF:
		ret = slimbus_drv_track_remove(ec_ref, SLIMBUS_ECREF_CHANNELS);
		break;
	case SLIMBUS_TRACK_SOUND_TRIGGER:
		/*  release soc slimbus clk to 21.777M */
		slimbus_freq_release(pdata->asp_reg_base_addr);
		(void)slimbus_drv_track_remove(sound_trigger, SLIMBUS_SOUND_TRIGGER_CHANNELS);
		ret = slimbus_drv_track_remove(voice_up, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
		break;
	case SLIMBUS_TRACK_DEBUG:
		ret = slimbus_drv_track_remove(audio_debug, SLIMBUS_DEBUG_CHANNELS);
		break;
	default:
		ret = -EINVAL;
		pr_err("[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		HiLOGE("audio", LOG_TAG, "[%s:%d] unknown track type:%d! \n", __FUNCTION__, __LINE__, track);
		break;
	}

	if (!ret)
		track_state[track] = 0;

	return ret;
}
EXPORT_SYMBOL(slimbus_track_remove);

int slimbus_switch_framer(
				slimbus_device_type_t	dev_type,
				slimbus_framer_type_t	framer_type)
{
	int ret = -1;
	uint8_t la;
	struct slimbus_device_info *dev = NULL;
	slimbus_bus_config_t   *bus_cfg = NULL;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(framer_type >= SLIMBUS_FRAMER_NUM);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	la = slimbus_drv_get_framerla(framer_type);
	if (la == 0) {
		pr_err("[%s:%d] invalid la:%d framer_type:%#x \n", __FUNCTION__, __LINE__, la, framer_type);
		return -EINVAL;
	}
	if (framer_type == SLIMBUS_FRAMER_CODEC) {
		/*  modify soc slimbus clk to 24.576M */
		slimbus_freq_request(pdata->asp_reg_base_addr);
		bus_cfg = &bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER];
	} else if (framer_type == SLIMBUS_FRAMER_SOC) {
		bus_cfg = &bus_config[SLIMBUS_BUS_CONFIG_NORMAL];
		/*  modify soc slimbus clk to low to avoid signal interference to GPS */
		slimbus_freq_release(pdata->asp_reg_base_addr);
	} else {
		pr_err("[%s:%d] invalid la:%d framer_type:%#x \n", __FUNCTION__, __LINE__, la, framer_type);
		return -EINVAL;
	}

	if (dev->rf == SLIMBUS_RF_6144) {
		if (framer_type == SLIMBUS_FRAMER_CODEC) {
			ret = slimbus_drv_switch_framer(la, 4, 18, bus_cfg);
		} else if (framer_type == SLIMBUS_FRAMER_SOC) {
			ret = slimbus_drv_switch_framer(la, 17, 3, bus_cfg);
		}
	} else if (dev->rf == SLIMBUS_RF_24576) {
		ret = slimbus_drv_switch_framer(la, 4, 3, bus_cfg);
	}

	if (EOK == ret) {
		pdata->framerstate =  framer_type;
	} else {
		pr_err("slimbus_switch_framer faild, ret = %d, framer_type = %d!\n", ret, framer_type);
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_switch_framer);

int slimbus_pause_clock(
				slimbus_device_type_t	dev_type,
				slimbus_restart_time_t	newrestarttime)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_drv_pause_clock(newrestarttime);

	return ret;
}
EXPORT_SYMBOL(slimbus_pause_clock);

int slimbus_param_set(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t  *params)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(track >= SLIMBUS_TRACK_MAX);
	BUG_ON(NULL == params);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	if (SLIMBUS_DEVICE_HI6402 == dev_type) {
		ret = slimbus_hi6402_param_set(slimbus_devices[dev_type], track, params);
	} else if (SLIMBUS_DEVICE_HI6403 == dev_type) {
		ret = slimbus_hi6403_param_set(slimbus_devices[dev_type], track, params);
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_param_set);

int slimbus_track_recover(void)
{
	slimbus_track_type_t track_type;
	int ret = 0;

	for (track_type = SLIMBUS_TRACK_AUDIO_PLAY; track_type < SLIMBUS_TRACK_MAX; track_type++) {

		if (track_state[track_type]) {
			pr_info("[%s:%d] recover track:%#x \n", __FUNCTION__, __LINE__, track_type);
			ret = slimbus_track_configure(pdata->device_type, track_type, NULL);
			ret += slimbus_track_activate(pdata->device_type, track_type);
		}
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_track_recover);

slimbus_bus_config_t *slimbus_bus_config_get(void)
{
	return bus_config;
}
EXPORT_SYMBOL(slimbus_bus_config_get);

int slimbus_bus_configure(slimbus_bus_config_type_t type)
{
	int ret = 0;

	BUG_ON(type >= SLIMBUS_BUS_CONFIG_MAX);

	ret = slimbus_drv_bus_configure(&bus_config[type]);

	return ret;
}
EXPORT_SYMBOL(slimbus_bus_configure);

static int slimbus_probe(struct platform_device *pdev)
{
	struct slimbus_private_data *pd;
	struct device	*dev = &pdev->dev;
	struct resource *resource;
	const char *platformtype = NULL;
	const char *codectype = NULL;
	int   ret          = 0;

	pd = devm_kzalloc(dev, sizeof(struct slimbus_private_data), GFP_KERNEL);
	if (!pd) {
		dev_err(dev, "not enough memory for slimbus_private_data\n");
		return -ENOMEM;
	}

	/* get pmu audio clk */
	pd->pmu_audio_clk = devm_clk_get(dev, "clk_pmuaudioclk");
	if (IS_ERR_OR_NULL(pd->pmu_audio_clk)) {
		dev_err(dev, "devm_clk_get: pmu_audio_clk not found!\n");
		HiLOGE("audio", "Slimbus", "_clk_get: pmu_audio_clk not found!\n");
		goto get_pmu_audio_clk_err;
	}

	ret = clk_prepare_enable(pd->pmu_audio_clk);
	if (ret) {
		dev_err(dev, "pmu_audio_clk :clk prepare enable failed !\n");
		HiLOGE("audio","Slimbus", "pmu_audio_clk :clk prepare enable failed !\n");
		goto  pmu_audio_clk_enable_err;
	}
	mdelay(1);

	/* SLIMbus base address */
	resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!resource) {
		dev_err(dev, "get IORESOURCE_MEM failed\n");
		goto pmu_audio_clk_enable_err;
	}

	pd->base_addr = ioremap(resource->start, resource_size(resource));
	if (!pd->base_addr) {
		dev_err(dev, "remap base address %p failed\n", (void*)resource->start);
		goto pmu_audio_clk_enable_err;
	}

	resource = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!resource) {
		dev_err(dev, "get IORESOURCE_MEM failed\n");
		goto get_aspres_err;
	}

	pd->asp_reg_base_addr = ioremap(resource->start, resource_size(resource));
	if (!pd->asp_reg_base_addr) {
		dev_err(dev, "remap base address %p failed\n", (void*)resource->start);
		goto get_aspres_err;
	}

	/* get asp power state address from dts, step next if fail to protect no definition */
	resource = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!resource) {
		dev_err(dev, "get sctrl base addr failed\n");
	} else {
		pd->sctrl_base_addr = ioremap(resource->start, resource_size(resource));
		if (!pd->sctrl_base_addr) {
			dev_err(dev, "remap base address %p failed\n", (void*)resource->start);
			goto get_aspres_err;
		}

		ret = of_property_read_u32(pdev->dev.of_node, "asp_power_state_offset", &(pd->asp_power_state_offset));
		if (ret) {
			dev_err(dev, "of_property_read_u32 return error! ret:%d\n", ret);
			goto map_sctrl_err;
		}
		pr_info("[%s:%d] sctrl base addr:0x%p, virtaddr:0x%p, offset:0x%x \n",
			__FUNCTION__, __LINE__, (void*)resource->start, pd->sctrl_base_addr, pd->asp_power_state_offset);
	}

	dev_info(dev, "[%s:%d] virtual address slimbus:%p, asp:%p!\n", __FUNCTION__, __LINE__,pd->base_addr, pd->asp_reg_base_addr);

	/* SLIMbus irq */
	pd->irq = platform_get_irq_byname(pdev, "asp_irq_slimbus");
	if (pd->irq < 0) {
		dev_err(dev, "get irq failed\n");
		goto map_sctrl_err;
	}

	pd->regu_asp = devm_regulator_get(dev, "slimbus-reg");
	if (IS_ERR(pd->regu_asp)) {
		dev_err(dev, "couldn't get regulators !\n");
		goto map_sctrl_err;
	}

	ret = regulator_enable(pd->regu_asp);
	if (ret) {
		dev_err(dev, "couldn't enable regulators %d\n", ret);
		goto map_sctrl_err;
	}

	/* ssi&slimbus iomux config */
	pd->pctrl = pinctrl_get(dev);
	if (IS_ERR(pd->pctrl)) {
		dev_err(dev, "could not get pinctrl\n");
		goto get_pinctrl_err;
	}
	pd->pin_default = pinctrl_lookup_state(pd->pctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(pd->pin_default)) {
		dev_err(dev, "%s : could not get defstate (%li)\n", __FUNCTION__ , PTR_ERR(pd->pin_default));
		goto ops_pinctrl_err;
	}
	pd->pin_idle = pinctrl_lookup_state(pd->pctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR(pd->pin_idle)) {
		dev_err(dev, "%s : could not get defstate (%li)\n", __FUNCTION__ , PTR_ERR(pd->pin_idle));
		goto ops_pinctrl_err;
	}

	ret = pinctrl_select_state(pd->pctrl, pd->pin_default);
	if (ret) {
		dev_err(dev, "%s : could not set pins to default state\n", __FUNCTION__);
		HiLOGE("audio","Slimbus", "%s : could not set pins to default state\n", __FUNCTION__);
		goto ops_pinctrl_err;
	}

	pd->device_type = SLIMBUS_DEVICE_HI6402;
	ret = of_property_read_string(pdev->dev.of_node, "codec-type", &codectype);
	if (ret == 0 && !strcmp(codectype, "slimbus-6403")) {
		pd->device_type = SLIMBUS_DEVICE_HI6403;
		ret = create_hi6403_slimbus_device(&slimbus_devices[SLIMBUS_DEVICE_HI6403]);
	} else {
		pd->device_type = SLIMBUS_DEVICE_HI6402;
		ret = create_hi6402_slimbus_device(&slimbus_devices[SLIMBUS_DEVICE_HI6402]);
	}

	if (ret) {
		dev_err(dev, "slimbus device create failed! \n");
		goto ops_pinctrl_err;
	}

	ret = of_property_read_string(pdev->dev.of_node, "platform-type", &platformtype);
	if (ret) {
		dev_err(dev, "of_property_read_string return error! ret:%d\n", ret);
		goto ops_pinctrl_err;
	}
	pr_info("[%s:%d] platform type:%s codectype: %s!\n", __FUNCTION__, __LINE__, platformtype, codectype);
	slimbus_devices[pd->device_type]->rf = SLIMBUS_RF_6144;
	slimbus_devices[pd->device_type]->slimbusclk_drv = 0xA0;
	slimbus_devices[pd->device_type]->slimbusdata_drv = 0xA3;
	pd->platform_type = PLATFORM_PHONE;

	if(NULL == platformtype){
		dev_err(dev, "[%s:%d] platform not define! default:ASIC!\n", __FUNCTION__, __LINE__);
		slimbus_devices[pd->device_type]->rf = SLIMBUS_RF_24576;
		bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
	} else {
		if (!strcmp(platformtype, "ASIC")) {
			slimbus_devices[pd->device_type]->rf = SLIMBUS_RF_24576;
			bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
		} else if (!strcmp(platformtype, "UDP")) {
			slimbus_devices[pd->device_type]->rf = SLIMBUS_RF_24576;
			slimbus_devices[pd->device_type]->slimbusclk_drv = 0xC0;
			slimbus_devices[pd->device_type]->slimbusdata_drv = 0xC3;
			bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
			pd->platform_type = PLATFORM_UDP;
		} else if (!strcmp(platformtype, "FPGA")) {
			slimbus_devices[pd->device_type]->rf = SLIMBUS_RF_6144;
			pd->platform_type = PLATFORM_FPGA;
		} else {
			dev_err(dev, "platform type define err!\n");
			goto release_slimbusdev;
		}
	}

	memset(track_state, 0, sizeof(track_state));
	if(SLIMBUS_DEVICE_HI6402 == pd->device_type) {
		slimbus_hi6402_param_init(slimbus_devices[SLIMBUS_DEVICE_HI6402]);
	} else {
		bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_4_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_4_CSW_32_SL;
		slimbus_hi6403_param_init(slimbus_devices[SLIMBUS_DEVICE_HI6403]);
	}

	slimbus_module_enable(slimbus_devices[pd->device_type], pd ->asp_reg_base_addr, 1);

	ret = slimbus_drv_init(pd->platform_type, pd->base_addr, pd->asp_reg_base_addr, pd->irq);
	if (ret) {
		dev_err(dev, "slimbus drv init failed!\n");
		goto slimbus_err;
	}

	ret = slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
	if (ret) {
		dev_err(dev, "slimbus bus configure failed!!\n");
		slimbus_drv_release(pd->irq);
		goto slimbus_err;
	}

	slimbus_dev = slimbus_devices[pd->device_type];

	pd->framerstate = SLIMBUS_FRAMER_SOC;
	pd->lastframer	= SLIMBUS_FRAMER_SOC;
	platform_set_drvdata(pdev, pd);
	pdata = pd;

	return 0;

slimbus_err:
release_slimbusdev:
	if(SLIMBUS_DEVICE_HI6403 == pd->device_type) {
		release_hi6403_slimbus_device(slimbus_devices[SLIMBUS_DEVICE_HI6403]);
	} else {
		release_hi6402_slimbus_device(slimbus_devices[SLIMBUS_DEVICE_HI6402]);
	}
ops_pinctrl_err:
	pinctrl_put(pd->pctrl);
get_pinctrl_err:
	regulator_disable(pd->regu_asp);
map_sctrl_err:
	if (pd->sctrl_base_addr)
		iounmap(pd->sctrl_base_addr);
map_asp_err:
	iounmap(pd->asp_reg_base_addr);
get_aspres_err:
	iounmap(pd->base_addr);
pmu_audio_clk_enable_err:
	clk_disable_unprepare(pd->pmu_audio_clk);
get_pmu_audio_clk_err:
	devm_clk_put(dev, pd->pmu_audio_clk);

	devm_kfree(&pdev->dev, pd);

	return -EFAULT;
}

static int slimbus_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;

	BUG_ON(NULL == pd);

	ret = slimbus_switch_framer(pd->device_type, SLIMBUS_FRAMER_SOC);
	if (ret) {
		dev_err(dev, "switch framer to SLIMBUS_DEVICE_SOC fail, ret:%d\n", ret);
	}

	slimbus_drv_release(pd->irq);
	if (SLIMBUS_DEVICE_HI6402 == pd->device_type) {
		release_hi6402_slimbus_device(slimbus_devices[SLIMBUS_DEVICE_HI6402]);
	} else {
		release_hi6403_slimbus_device(slimbus_devices[SLIMBUS_DEVICE_HI6403]);
	}

	pinctrl_put(pd->pctrl);
	ret = regulator_disable(pd->regu_asp);
	if (ret) {
		dev_err(dev, "regulator disable failed!, ret:%d\n", ret);
	}

	iounmap(pd->asp_reg_base_addr);
	iounmap(pd->base_addr);
	if (pd->sctrl_base_addr)
		iounmap(pd->sctrl_base_addr);
	clk_disable_unprepare(pd->pmu_audio_clk);
	devm_clk_put(dev, pd->pmu_audio_clk);
	devm_kfree(dev, pd);

	platform_set_drvdata(pdev, NULL);

	return 0;
}

static int slimbus_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;
	int ret = 0;
	int asppower = 0;

	BUG_ON(NULL == pd);

	pd->portstate = slimbus_port_state_get(pd->base_addr);
	asppower = slimbus_asppower_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	pr_info("[%s:%d] portstate:%#x asppower:0x%x + \n", __FUNCTION__, __LINE__,  pd->portstate, asppower);

	if (!pd->portstate) {
		/* make sure last msg has been processed finished */
		mdelay(1);
		slimbus_int_need_clear_set(true);
		/*
		* while fm, hi64xx pll is in high freq, slimbus framer is in codec side
		* we need to switch to soc in this case, and switch to 64xx in resume
		*/

		if (pd->framerstate == SLIMBUS_FRAMER_CODEC) {
			ret = slimbus_switch_framer(pd->device_type, SLIMBUS_FRAMER_SOC);
			if (ret) {
				pr_err("%s : slimbus switch framer failed!\n", __FUNCTION__);
				goto exit;
			}
			pd->lastframer = SLIMBUS_FRAMER_CODEC;
		} else {
			pd->lastframer = SLIMBUS_FRAMER_SOC;
		}

		ret = slimbus_pause_clock(pd->device_type, SLIMBUS_RT_UNSPECIFIED_DELAY);
		if (ret) {
			dev_err(dev, "%s : slimbus pause clock failed, ret=%#x\n", __FUNCTION__, ret);
		}
		/* make sure para has updated */
		mdelay(1);

		ret = slimbus_drv_stop();
		if (ret) {
			pr_err("%s : slimbus stop failed!\n", __FUNCTION__);
		}

		/* set pin to  low power mode */
		ret = pinctrl_select_state(pd->pctrl, pd->pin_idle);
		if (ret) {
			dev_err(dev, "%s : could not set pins to idle state\n", __FUNCTION__);
			HiLOGE("audio", "Slimbus", "%s : could not set pins to idle state\n", __FUNCTION__);
			goto exit;
		}

		clk_disable_unprepare(pd->pmu_audio_clk);

		ret = regulator_disable(pd->regu_asp);
		if (ret) {
			dev_err(dev, "%s : regulator disable failed! \n", __FUNCTION__);
			goto exit;
		}
	}

exit:
	asppower = slimbus_asppower_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	pr_info("[%s:%d] asppower:0x%x - \n", __FUNCTION__, __LINE__, asppower);

	return ret;
}

static int slimbus_resume(struct platform_device *pdev)
{
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;
	int ret = 0;
	int asppower = 0;
	pr_info("[%s:%d] + \n", __FUNCTION__, __LINE__);

	BUG_ON(NULL == pd);
	asppower = slimbus_asppower_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);

	if (!pd->portstate) {
		ret = regulator_enable(pd->regu_asp);
		if (ret) {
			dev_err(dev, "couldn't enable regulators %d\n", ret);
			goto exit;
		}

		ret = clk_prepare_enable(pd->pmu_audio_clk);
		if (ret) {
			dev_err(dev, "pmu_audio_clk :clk prepare enable failed !\n");
			goto exit;
		}
		/* make sure pmu clk has stable */
		mdelay(1);

		ret = pinctrl_select_state(pd->pctrl, pd->pin_default);
		if (ret) {
			dev_err(dev, "could not set pins to default state\n");
			HiLOGE("audio","Slimbus", "%s : could not set pins to default state\n", __FUNCTION__);
			goto exit;
		}

		slimbus_int_need_clear_set(false);

		slimbus_module_enable(slimbus_devices[pd->device_type], pd->asp_reg_base_addr, true);
		ret = slimbus_drv_resume_clock();
		if (ret) {
			dev_err(dev, "slimbus resume clock failed, ret=%d\n", ret);
		}

		ret = slimbus_dev_init(pd->platform_type);
		if (ret) {
			dev_err(dev, "slimbus drv init failed!\n");
			goto exit;
		}

		ret = slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
		if (ret) {
			dev_err(dev, "slimbus bus configure failed!!\n");
			goto exit;
		}

		if (pd->lastframer == SLIMBUS_FRAMER_CODEC) {
			ret = slimbus_switch_framer(pd->device_type, SLIMBUS_FRAMER_CODEC);
			pr_info("[%s:%d] switch_framer:%#x + \n", __FUNCTION__, __LINE__,  pdata->lastframer);
		}
	}

exit:
	asppower = slimbus_asppower_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	pr_info("[%s:%d] portstate:%#x asppower:0x%x -\n", __FUNCTION__, __LINE__, pd->portstate, asppower);
	return ret;
}

static const struct of_device_id slimbus_match[] = {
	{
		.compatible = "candance,slimbus",
	},
	{},
};
MODULE_DEVICE_TABLE(of, slimbus_match);

static struct platform_driver slimbus_driver = {
	.probe	= slimbus_probe,
	.remove = slimbus_remove,
	.suspend = slimbus_suspend,
	.resume  = slimbus_resume,
	.driver = {
		.name	= "hisilicon,slimbus",
		.owner	= THIS_MODULE,
		.of_match_table = slimbus_match,
	},
};

static int __init slimbus_init(void)
{
	int ret;

	ret = platform_driver_register(&slimbus_driver);
	if (ret) {
		pr_err("driver register failed\n");
		HiLOGE("audio","Slimbus", "driver register failed\n");
	}

	return ret;
}

static void __exit slimbus_exit(void)
{
	platform_driver_unregister(&slimbus_driver);
}
fs_initcall(slimbus_init);
module_exit(slimbus_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon");

