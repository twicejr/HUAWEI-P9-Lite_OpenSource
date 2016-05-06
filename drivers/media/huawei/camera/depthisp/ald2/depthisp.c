/*
 * A driver for the mini isp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/spi/spi.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
//#include <mach/gpio.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/ctype.h>
#include <linux/regulator/consumer.h>
#include <linux/vmalloc.h>
#include <linux/random.h>
#include <linux/irq.h>
#include "depthisp.h"
#include "cam_log.h"
#include <linux/amba/pl022.h>
#include <linux/pinctrl/consumer.h>
#include <dsm/dsm_pub.h>
#include <media/huawei/depthisp_cfg.h>
#include "sensor_commom.h"
#include "depthisp_reg.h"


#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "depth_isp"
#endif


#define DEPTH_ISP_DMD_ERROR_COUNT    (17)

#define DEPTH_ISP_SPI_SPEED_BOOT	(10000000)
#define DEPTH_ISP_SPI_SPEED_NORMAL	(30000000)

#define DEPTH_ISP_WAIT_TIMEOUT	(HZ*2)
#define DEPTH_ISP_POLL_TIMES		(20)
#define DEPTH_ISP_MAX_ERR_CODE	(10)

#define DEPTH_ISP_FW_LOG_BUF		(4096)

#define SPI_TX_BUF_SIZE			(64)
#define SPI_RX_BUF_SIZE			(64)
#define SPI_BLOCK_BUF_SIZE		(8192)

#define ISPCMD_DUMMYBYTES		(4)
#define ISPCMD_LENFLDBYTES		(2)
#define ISPCMD_OPCODEBYTES		(2)
#define ISPCMD_CKSUMBYTES		(2)
#define ISPCMD_HDRSIZE			(ISPCMD_LENFLDBYTES + ISPCMD_OPCODEBYTES)
#define ISPCMD_HDRSIZEWDUMMY	(ISPCMD_HDRSIZE + ISPCMD_DUMMYBYTES)

#define DEPTH_ISP_DEBUG_DUMP_LOG


static struct dsm_client_ops ops={
	.poll_state = NULL,
	.dump_func = NULL,
};

static struct dsm_dev dev_depthisp = {
	.name = "dsm_extisp",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &ops,
	.buff_size = 256,
};

struct disp_plat_data {
	int spi_cs_gpio;
	int irq_gpio;
	int reset_gpio;
	int chip_type;
	/* spi master config */
	struct pl022_config_chip spidev0_chip_info;
	/* pin control config */
	struct pinctrl			*pinctrl;
	struct pinctrl_state	*pins_default;
	struct pinctrl_state	*pins_idle;
};

enum ssp_writing {
	WRITING_NULL,
	WRITING_U8,
	WRITING_U16,
	WRITING_U32
};

enum ssp_reading {
	READING_NULL,
	READING_U8,
	READING_U16,
	READING_U32
};
/*
enum ssp_chip_select {
	SSP_CHIP_SELECT,
	SSP_CHIP_DESELECT
};
*/

struct chip_data {
	u32 cr0;
	u16 cr1;
	u16 dmacr;
	u16 cpsr;
	u8 n_bytes;
	bool enable_dma;
	enum ssp_reading read;
	enum ssp_writing write;
	void (*cs_control) (u32 command);
	int xfer_type;
};

struct disp_fw_ver_info {
	char	info[16];
	u32		product;
	u16		major;
	u16		minor;
	char	user[9];
};

struct disp_data {
	struct spi_device	*spi;
	struct mutex		busy_lock;
	struct disp_plat_data	plat_data;
	struct workqueue_struct	*work_queue;
	wait_queue_head_t	wait_queue;
	wait_queue_head_t	sync_queue;
	int		state;
	u32		last_error_code[DEPTH_ISP_MAX_ERR_CODE];
	/*
	 * NOTE: All buffers should be dma-safe buffers
	 * ext_buf:used only for 1-byte ctrl_byte in font of tx or rx
	 * tx_buf :used for 64-Bytes CMD-send or 8K-Bytes Block-send
	 * rx_buf :used for 64-Bytes CMD-recv or 4K-Bytes Block-recv
	 */
	u8		*tx_buf;
	u8		*rx_buf;
	u8		*ext_buf;
	/*
	 * NOTE:
	 * all these tx/rx/ext buffers above used with mutex lock, but
	 * irq cannot use mutex lock, so a special buffer is supplied
	 */
	u8		*irq_buf;
	/* debug config & debug info */
	u32		debug_config;
	u32		debug_log_level;
	struct work_struct	dump_err_work;
	struct work_struct	dump_log_work;
	struct disp_fw_ver_info fw_info;
	struct disp_fw_ver_info boot_info;
	u32 	flush_reg_flag;
	struct dsm_client *client_depthisp;
};


typedef enum {
    USPICTRL_MS_CB_ORG                  = (0x00<<6),    /*!< Ctrl-Byte, original command */
    USPICTRL_MS_CB_STS                  = (0x01<<6),    /*!< Ctrl-Byte, polling status */
    USPICTRL_MS_CB_RSP                  = (0x02<<6),    /*!< Ctrl-Byte, get response */
    USPICTRL_MS_CB_DIS                  = (0x03<<6),    /*!< Ctrl-Byte, disable Ctrl-Byte mode */

    USPICTRL_MS_ORG                     = 0x5A,     /*!< Ctrl-Byte, original command */
    USPICTRL_MS_RSP                     = 0xA5,     /*!< Ctrl-Byte, get response */
    USPICTRL_MS_BK0                     = 0xB5,     /*!< Ctrl-Byte, send bulk for 1~(N-1) one */
    USPICTRL_MS_BKN                     = 0xBB,     /*!< Ctrl-Byte, senc bulk for last one */
    USPICTRL_MS_DIS                     = 0x05,     /*!< Ctrl-Byte, disable get response */
} USPICTRL_MS_CB_ID;

enum {
	SPI_TO_RAM_CTRL = 0x15,
	SPI_TO_REG_CTRL = 0x19,
};

enum {
	DEPTH_ISP_OCRAM_FAIL = 0xA500,
	DEPTH_ISP_OCRAM_SUCC = 0xB500,
};

enum {
	DEPTH_ISP_STATE_IDLE				= (0U),
	DEPTH_ISP_STATE_READY			= (1U<<0),
	DEPTH_ISP_STATE_SYNC				= (1U<<1),
};

enum {
	DEPTH_ISP_IRQ_READY_DONE			= (1U<<0),
	DEPTH_ISP_IRQ_CMD_ERR			= (1U<<1),
	DEPTH_ISP_IRQ_OTHRE_ERR			= (1U<<2),
	DEPTH_ISP_IRQ_LOG_FULL			= (1U<<3),
	DEPTH_ISP_IRQ_SYNC				= (1U<<4),
	DEPTH_ISP_IRQ_PWDN				= (1U<<5),
};

enum {
	DEPTH_ISP_DEBUG_SPI_DATA			= (1U<<0),
	DEPTH_ISP_DEBUG_LOG_FILE			= (1U<<1),
};

enum {
	DEPTH_ISP_LOG_LEVEL_NONE			= (0x0),
	DEPTH_ISP_LOG_LEVEL_SW1			= (0x00000001),
	DEPTH_ISP_LOG_LEVEL_SW2			= (0x00000002),
	DEPTH_ISP_LOG_LEVEL_SW3			= (0x00000004),
	DEPTH_ISP_LOG_LEVEL_IQ1			= (0x00000010),
	DEPTH_ISP_LOG_LEVEL_IQ2			= (0x00000020),
	DEPTH_ISP_LOG_LEVEL_IQ3			= (0x00000040),
	DEPTH_ISP_LOG_LEVEL_ISR			= (0x00000100),
};

enum {
	DEPTH_ISP_FLUSH_REG_NONE		= (0U),
	DEPTH_ISP_FLUSH_REG_ALREADY		= (1U),
};

enum {
	DEPTH_ISP_CALI_ID_OTP_DATA		= (0x0),
	DEPTH_ISP_CALI_ID_PACK_DATA		= (0x1),
	DEPTH_ISP_CALI_ID_SCENARIO_TAB	= (0x2),
};

static struct disp_reg_t init_regs_boot[] = {
	{0xffe40050, 0x1},
	{0xffef0308, 0x0},
	{TIMER_DELAY, 70},// us
	{0xffef030c, 0x0},
	{0xffe81080, 0x1},
	{0xffef0088, 0xffbf7fff},
	{0xffe800c4, 0xfffffff0},
	{TIMER_DELAY, 100},//us
	{0xffef0240, 0},
};
static struct disp_data *disp_drv_data;

/* old style: al6405 compatible, should be removed later */
#define DEPTH_ISP_BOOT_CODE		("/system/miniisp/miniBoot.bin")
#define DEPTH_ISP_BASIC_CODE	("/system/miniisp/TBM_Latour.bin")

/* for al6610 fw */
#define DEPTH_ISP_BOOT_BIN		("/system/miniisp/Boot.bin")
#define DEPTH_ISP_MAIN_BIN		("/system/miniisp/Main.bin")
#define DEPTH_ISP_SCENARIO_TAB	("/system/miniisp/SCTable.bin")

/* for al6610 Ocram test */
#define DEPTH_ISP_OCRAM_BOOT	("/system/miniisp/BootOcram.bin")

static int disp_init_regs(struct disp_data *devdata, struct disp_reg_t *preg, int cnt);
static int disp_send_cmd(struct disp_data *devdata, u16 opcode, u8 *param, u32 len);
static int disp_recv_data(struct disp_data *devdata, u8 *param, u32 len);
static int disp_recv_block(struct disp_data *devdata, u8 *out, u32 len);
static u16 calculate_checksum(u8 *buf, u16 size);
static void spi_data_debug(const void *buf, int data_len, int dbg_len);
static void disp_cmd_delay(void);
static void disp_dump_err(struct work_struct *work);
static void disp_dump_log(struct work_struct *work);

static int disp_spi_send(struct disp_data *devdata, u32 len);
static int disp_spi_recv(struct disp_data *devdata, u32 len);
static int disp_poll_status(struct disp_data *devdata);
static int disp_load_boot_code(struct disp_data *devdata, char *name);
static int disp_load_basic_code(struct disp_data *devdata, char *name);

static void disp_config_spi(struct disp_data *pdata, u32 mode, u32 bits, u32 speed);
static void disp_config_log(struct disp_data *pdata, u32 new_config, u32 new_log_level);
static void disp_spi_dump_reg(struct disp_data *pdata, u32 reg_start, u32 reg_end);
static void disp_spi_dump_ram(struct disp_data *pdata, u32 ram_start, u32 len);
static void disp_switch_spi_channel_to_hw(struct disp_data *pdata);
static void disp_dump_ram(struct disp_data *pdata, u32 start, u32 total, u32 mode);
static int disp_spi_write_reg(struct disp_data *devdata, u32 addr, u32 val);
static int disp_spi_read_reg(struct disp_data *devdata, u32 addr, u32* val);
static int disp_spi_read_ram(struct disp_data *devdata, u32 addr, u32 len);
static void disp_test_spi(struct disp_data *pdata);
static void parser_dmd_error(u32 err, char* out_err_name, char* out_err_num);


int disp_get_chipid(void)
{
	struct disp_data *drv_data = disp_drv_data;
	int type;
	if (drv_data)
		type = drv_data->plat_data.chip_type;
	else
		type = DEPTHISP_DUMMY;
	cam_info("%s chip_type = %d", __func__, type);
	return type;
}


int disp_exec_write_block_res(u16 cmd, u8 *in, u32 in_len, bool out_to_block, u8 *out,u32 bulk_len, u32 out_len)
{
	struct disp_data *devdata = disp_drv_data;
	int err = 0;
	u8 ctrl_byte = USPICTRL_MS_CB_DIS;
	struct spi_transfer	xfer[2];
	struct spi_message	m;
	int status;
	int timeout;
	cam_info("Enter: %s", __func__);

	if(!devdata) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}
	memset(xfer, 0, sizeof(xfer));

	mutex_lock(&devdata->busy_lock);

	devdata->state = DEPTH_ISP_STATE_IDLE;
	if(disp_send_cmd(devdata, cmd, in, in_len))
		goto out;

	cam_debug("%s send cmd to switch bulk mode", __func__);
	timeout = wait_event_freezable_timeout(devdata->wait_queue,\
				(devdata->state == DEPTH_ISP_STATE_READY),\
				DEPTH_ISP_WAIT_TIMEOUT);

	if (timeout == 0) {
		cam_err("%s wait ready signal timeout", __func__);
		err = -EAGAIN;
		goto out;
	}

	devdata->state = DEPTH_ISP_STATE_IDLE;  //reset devdata state

	/*one message only, incase broken by spi interrupt */
	devdata->ext_buf[0] = ctrl_byte;
	memcpy(devdata->tx_buf, out, bulk_len);
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].len = sizeof(ctrl_byte);
	xfer[0].cs_change = 1;
	xfer[0].delay_usecs = 1;
	xfer[1].tx_buf = devdata->tx_buf;
	xfer[1].len = bulk_len;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_info("%s - sync error: status=%d", __func__, status);
	}

	//TODO: cannot wait ready interrupt

	timeout = wait_event_freezable_timeout(devdata->wait_queue,\
				(devdata->state == DEPTH_ISP_STATE_READY),\
				DEPTH_ISP_WAIT_TIMEOUT);

	if (timeout == 0) {
		cam_warn("%s wait ready signal timeout2", __func__);
		err = -EAGAIN;
		goto out;
	}

	if (out_to_block)
		err = disp_recv_block(devdata, out, bulk_len);
	else
		err = disp_recv_data(devdata, in, out_len);


out:
	disp_cmd_delay();
	mutex_unlock(&devdata->busy_lock);
	return err;

}

int disp_exec_write_block(u16 cmd, u8 *in, u32 in_len, u8 *out, u32 out_len)
{
	struct disp_data *devdata = disp_drv_data;
	int err = 0;
	//int i;
	u8 ctrl_byte = USPICTRL_MS_CB_DIS;
	struct spi_transfer	xfer[2];
	struct spi_message	m;
	int status;
	int timeout;
	cam_debug("Enter: %s", __func__);

    if(!devdata) {
        cam_err("%s no driver data", __func__);
        return -ENODEV;
    }
	memset(xfer, 0, sizeof(xfer));

    mutex_lock(&devdata->busy_lock);

	devdata->state = DEPTH_ISP_STATE_IDLE;
	if(disp_send_cmd(devdata, cmd, in, in_len))
		goto out;

	timeout = wait_event_freezable_timeout(devdata->wait_queue,\
				(devdata->state == DEPTH_ISP_STATE_READY),\
				DEPTH_ISP_WAIT_TIMEOUT);

	if (0 == timeout) {
		cam_warn("%s wait ready signal timeout", __func__);
		err = -EAGAIN;
		goto out;
	}

	/*one message only, incase broken by spi interrupt */
	devdata->ext_buf[0] = ctrl_byte;
	memcpy(devdata->tx_buf, out, out_len);
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].len = sizeof(ctrl_byte);
	xfer[0].cs_change = 1;
	xfer[0].delay_usecs = 1;
	xfer[1].tx_buf = devdata->tx_buf;
	xfer[1].len = out_len;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_info("%s - sync error: status=%d", __func__, status);
	}

	wait_event_freezable_timeout(devdata->wait_queue,\
				(devdata->state == DEPTH_ISP_STATE_READY),\
				DEPTH_ISP_WAIT_TIMEOUT);

	if (devdata->state != DEPTH_ISP_STATE_READY) {
		cam_warn("%s wait ready signal timeout2", __func__);
		err = -EAGAIN;
		goto out;
	}

out:
	disp_cmd_delay();
	mutex_unlock(&devdata->busy_lock);
	return err;

    return 0;
}

int disp_exec_unidir_cmd(u16 cmd, bool set_flag,
							bool out_to_block, u8 *param, u32 len)
{
	struct disp_data *devdata = disp_drv_data;
	int err = 0;
	int timeout;

	if (!devdata) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	mutex_lock(&devdata->busy_lock);

	if (set_flag == true) {
		devdata->state = DEPTH_ISP_STATE_IDLE;
		if(disp_send_cmd(devdata, cmd, param, len))
			goto out;

	} else {
		devdata->state = DEPTH_ISP_STATE_IDLE;
		err = disp_send_cmd(devdata, cmd, NULL, 0);
		if (err)
			goto out;

		timeout = wait_event_freezable_timeout(devdata->wait_queue,\
					(devdata->state == DEPTH_ISP_STATE_READY),\
					DEPTH_ISP_WAIT_TIMEOUT*2);

		if (0 == timeout) {
			cam_warn("%s wait ready signal timeout", __func__);
			err = -EAGAIN;
			goto out;
		}

		if (out_to_block)
			err = disp_recv_block(devdata, param, len);
		else
			err = disp_recv_data(devdata, param, len);
	}
out:
	disp_cmd_delay();
	mutex_unlock(&devdata->busy_lock);
	return err;
}
EXPORT_SYMBOL(disp_exec_unidir_cmd);


int disp_exec_bidir_cmd(u16 cmd, u8 *in, u32 in_len,
						bool out_to_block, u8 *out, u32 out_len)
{
	struct disp_data *devdata = disp_drv_data;
	int err = 0, ret = 0;

	if (!devdata) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	if ((in == NULL) || (out == NULL)) {
		cam_err("%s in out buf invalid", __func__);
		return -EINVAL;
	}

	if (DEPTHISP_DUMMY == devdata->plat_data.chip_type) {
		cam_info("%s dummy chip, nothing need to do", __func__);
		return 0;
	}

	mutex_lock(&devdata->busy_lock);

	devdata->state = DEPTH_ISP_STATE_IDLE;
	err = disp_send_cmd(devdata, cmd, in, in_len);
	if (err)
		goto out;

	ret = wait_event_freezable_timeout(devdata->wait_queue,\
						(devdata->state == DEPTH_ISP_STATE_READY),\
						DEPTH_ISP_WAIT_TIMEOUT);
	if (ret == 0) {
		cam_warn("%s wait ready signal timeout", __func__);
		err = -EAGAIN;
		goto out;
	}

	if (out_to_block)
		err = disp_recv_block(devdata, out, out_len);
	else
		err = disp_recv_data(devdata, out, out_len);

out:
	disp_cmd_delay();
	mutex_unlock(&devdata->busy_lock);
	return err;
}
EXPORT_SYMBOL(disp_exec_bidir_cmd);

int disp_init(void)
{
	struct disp_data *drv_data = disp_drv_data;
	struct disp_plat_data *plat_data = NULL;
	int ret = 0;

	cam_info("%s enter", __func__);

	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	plat_data = &drv_data->plat_data;
	if (DEPTHISP_DUMMY == plat_data->chip_type) {
		cam_info("%s dummy chip, nothing need to do", __func__);
		return 0;
	}

	/* restore pin to normal state */
	if (!IS_ERR(plat_data->pins_default)) {
		ret = pinctrl_select_state(plat_data->pinctrl, plat_data->pins_default);
		if (ret)
			cam_err("%s could not set default pins", __func__);
	}

	/* restore gpio to output mode when init */
	/* gpio_direction_output(plat_data->spi_cs_gpio, 1); */
	gpio_direction_output(plat_data->reset_gpio,  0);

	/* debug level reset */
	drv_data->debug_log_level = DEPTH_ISP_LOG_LEVEL_NONE;
	drv_data->flush_reg_flag = DEPTH_ISP_FLUSH_REG_NONE;

	/* enable ISP irq handle */
	enable_irq(drv_data->spi->irq);
	return ret;
}
EXPORT_SYMBOL(disp_init);

int disp_exit(void)
{
	struct disp_data *drv_data = disp_drv_data;
	struct disp_plat_data *plat_data = NULL;
	int ret = 0;

	cam_info("%s enter", __func__);

	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	plat_data = &drv_data->plat_data;
	if (DEPTHISP_DUMMY == plat_data->chip_type) {
		cam_info("%s dummy chip, nothing need to do", __func__);
		return 0;
	}

	/* shutdown ISP irq handle */
	disable_irq(drv_data->spi->irq);

	/* set pin to LP state when exit*/
	if (!IS_ERR(plat_data->pins_idle)) {
		ret = pinctrl_select_state(plat_data->pinctrl, plat_data->pins_idle);
		if (ret)
			cam_err("%s could not set idle pins", __func__);
	}

	gpio_direction_output(plat_data->reset_gpio,  0);
	/* gpio_direction_output(plat_data->spi_cs_gpio, 1); */

	flush_work(&drv_data->dump_err_work);
	flush_work(&drv_data->dump_log_work);
	/* debug level reset */
	drv_data->debug_log_level = 0;

	return ret;
}
EXPORT_SYMBOL(disp_exit);


int disp_flush_log(void)
{
	struct disp_data *drv_data = disp_drv_data;

	cam_info("%s enter", __func__);

	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	if (DEPTHISP_DUMMY == drv_data->plat_data.chip_type) {
		cam_info("%s dummy chip, nothing need to do", __func__);
		return 0;
	}

	/* force to record last log when exit */
	if (drv_data->debug_config & DEPTH_ISP_DEBUG_LOG_FILE) {
		queue_work(drv_data->work_queue, &drv_data->dump_log_work);
		flush_work(&drv_data->dump_log_work);
	}

	return 0;
}
EXPORT_SYMBOL(disp_flush_log);


int disp_flush_reg(void)
{
	struct disp_data *drv_data = disp_drv_data;
	int type = 0, i = 0;

	cam_info("%s enter", __func__);

	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	type = drv_data->plat_data.chip_type;
	if(DEPTHISP_AL6610 != type) {
		cam_info("%s al6045 or dummy chip nothing need to do", __func__);
		return 0;
	}

	/* don't dump twice */
	if (drv_data->flush_reg_flag == DEPTH_ISP_FLUSH_REG_ALREADY)
		return 0;

	/* mark register already dumped */
	drv_data->flush_reg_flag = DEPTH_ISP_FLUSH_REG_ALREADY;
	disp_switch_spi_channel_to_hw(drv_data);
	for (i = 0; i < ARRAY_SIZE(default_reg_range_table); i++) {
		disp_spi_dump_reg(drv_data,
				default_reg_range_table[i].start,
				default_reg_range_table[i].end);
	}
	return 0;
}
EXPORT_SYMBOL(disp_flush_reg);

static void disp_msleep(unsigned int ms)
{
	ktime_t wait = ns_to_ktime(ms * 1000 * 1000);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_hrtimeout(&wait, HRTIMER_MODE_REL);
}

int disp_load_fw(void)
{
	struct disp_data *drv_data = disp_drv_data;
	struct disp_plat_data *plat_data = NULL;
	int ret = 0, timeout;
	char *fw_boot_path = NULL, *fw_main_path = NULL;

	cam_info("%s enter", __func__);
	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	plat_data = &drv_data->plat_data;
	if (DEPTHISP_DUMMY == plat_data->chip_type) {
		cam_info("%s dummy chip, nothing need to do", __func__);
		return 0;
	}

	mutex_lock(&drv_data->busy_lock);

	gpio_direction_output(plat_data->reset_gpio,  0);
	disp_msleep(15);
	gpio_direction_output(plat_data->reset_gpio,  1);
	disp_msleep(10);

	/* setup to load boot code firmware */
	drv_data->spi->max_speed_hz = DEPTH_ISP_SPI_SPEED_BOOT;
	ret = spi_setup(drv_data->spi);
	if (ret < 0) {
		cam_err("%s - failed to setup spi speed:%u", __func__,
										drv_data->spi->max_speed_hz);
		goto out;
	}

	if (DEPTHISP_AL6045 == plat_data->chip_type) {
		fw_boot_path = DEPTH_ISP_BOOT_CODE;
		fw_main_path = DEPTH_ISP_BASIC_CODE;
	} else {
		/* init register & confirm firmware */
		fw_boot_path = DEPTH_ISP_BOOT_BIN;
		fw_main_path = DEPTH_ISP_MAIN_BIN;
		disp_init_regs(drv_data, &init_regs_boot[0], ARRAY_SIZE(init_regs_boot));
		/* init bypass */
		/* disp_init_regs(drv_data, &init_regs_12m[0], ARRAY_SIZE(init_regs_12m)); */
		/* goto out; */
	}

	/* load boot code firmware */
	ret = disp_load_boot_code(drv_data, fw_boot_path);
	if (ret)
		goto out;
	disp_msleep(5);

	/* setup to load main code firmware */
	drv_data->spi->max_speed_hz = DEPTH_ISP_SPI_SPEED_NORMAL;
	ret = spi_setup(drv_data->spi);
	if (ret < 0) {
		cam_err("%s - failed to setup spi speed:%u", __func__,
										drv_data->spi->max_speed_hz);
		goto out;
	}

	/* setup to load main code firmware */
	drv_data->state = DEPTH_ISP_STATE_IDLE;
	ret |= disp_load_basic_code(drv_data, fw_main_path);
	if (ret)
		goto out;

	timeout = wait_event_timeout(drv_data->wait_queue,\
					(drv_data->state == DEPTH_ISP_STATE_READY),\
					HZ/4);
	if (0 == timeout) {
		cam_err("%s wait ready signal timeout", __func__);
		if(!dsm_client_ocuppy(drv_data->client_depthisp) &&
				(DEPTHISP_AL6610 == plat_data->chip_type)) {
			dsm_client_record(drv_data->client_depthisp, "%s wait ready signal timeout\n", __func__);
			dsm_client_notify(drv_data->client_depthisp, DSM_EXTISP_LOAD_FW_ERROR_NO);
			cam_info("[I/DSM] %s dsm_client_notify", drv_data->client_depthisp->client_name);
		}
		ret = -EAGAIN;
	} else {
		cam_info("%s sucess to load fw. timeout %d", __func__, timeout);
	}

out:
	mutex_unlock(&drv_data->busy_lock);
	return ret;
}
EXPORT_SYMBOL(disp_load_fw);

int disp_load_scenario_tab(void)
{
	struct disp_data *drv_data = disp_drv_data;
	int ret = 0, timeout;
	u8 param[11];
	u32 total_size, block_size;
	u16 check_sum;
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	u32 one_size, left, block;

	cam_info("%s enter", __func__);
	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	set_fs(KERNEL_DS);
	fp = filp_open(DEPTH_ISP_SCENARIO_TAB, O_RDONLY, 0644);
	if (IS_ERR_OR_NULL(fp)) {
		cam_info("%s open file error", __func__);
		set_fs(oldfs);
		return -EINVAL;
	}
	total_size = (u32)(vfs_llseek(fp, 0L, SEEK_END));
	block_size = SPI_BLOCK_BUF_SIZE;
	check_sum = 0x0; /*always set to 0x0 for scenario tab*/
	memcpy(&param[0], &total_size, 4);
	memcpy(&param[4], &block_size, 4);
	param[8] = DEPTH_ISP_CALI_ID_SCENARIO_TAB;
	memcpy(&param[9], &check_sum, 2);

	cam_info("%s start sending scenario tab... size=0x%x", __func__, total_size);

	mutex_lock(&drv_data->busy_lock); /*lock ++*/

	/* (1)send cmd to tell how many blocks to send*/
	drv_data->state = DEPTH_ISP_STATE_IDLE;
	ret = disp_send_cmd(drv_data, ISPCMD_WRITE_CALIBRATION_DATA,
			param, sizeof(param));
	if (ret) {
		cam_err("%s send cmd error", __func__);
		goto out;
	}

	/* wait irq to confirm */
	timeout = wait_event_freezable_timeout(drv_data->wait_queue,\
					(drv_data->state == DEPTH_ISP_STATE_READY),\
					HZ/4);
	if (0 == timeout) {
		cam_err("%s wait ready signal timeout", __func__);
		ret = -EAGAIN;
		goto out;
	}

	/* (2)send ctrl byte */
	/* todo: better to be one message with tx buf */
	drv_data->ext_buf[0] = USPICTRL_MS_CB_DIS;
	spi_write(drv_data->spi, drv_data->ext_buf, 1);

	/* (3)send table block */
	drv_data->state = DEPTH_ISP_STATE_IDLE;
	vfs_llseek(fp, 0L, SEEK_SET);
	for (left = total_size, block = 0; left != 0; left -= one_size) {
		/* memset(drv_data->ext_buf, 0, SPI_BLOCK_BUF_SIZE); */
		one_size = (left > SPI_BLOCK_BUF_SIZE) ? SPI_BLOCK_BUF_SIZE : left;
		ret = vfs_read(fp, drv_data->tx_buf, one_size, &fp->f_pos);
		if (ret < 0) {
			cam_err("%s vfs read error %d", __func__, ret);
			goto out; /*break;*/
		}
		ret = spi_write(drv_data->spi, drv_data->tx_buf, one_size);
		if (ret < 0) {
			cam_err("%s spi send error %d", __func__, ret);
			goto out; /*break;*/
		}
		block++;
	}

	/* wait irq to confirm */
	timeout = wait_event_freezable_timeout(drv_data->wait_queue,\
					(drv_data->state == DEPTH_ISP_STATE_READY),\
					HZ/4);
	if (0 == timeout) {
		cam_err("%s wait ready signal timeout", __func__);
		ret = -EAGAIN;
		goto out;
	}
	cam_info("%s sucess to load scenario table:%d blocks",
			__func__, block);

out:
	mutex_unlock(&drv_data->busy_lock); /*lock --*/
	filp_close(fp, 0);
	set_fs(oldfs);
	return ret;
}
EXPORT_SYMBOL(disp_load_scenario_tab);

int disp_load_calibration_data(int data_type, u8 *ext_data, u32 ext_len)
{
	struct disp_data *drv_data = disp_drv_data;
	int ret = 0, timeout;
	u8 param[11];
	u16 check_sum;
	u32 *p_total_size =  (u32 *)&param[0];
	u32 *p_block_size =  (u32 *)&param[4];
	char *type_name;
	u32 one_size, left, block;
	u8 *p_data_pos = NULL;

	if (NULL == ext_data) {
		cam_err("%s ext_data is NULL", __func__);
		return 0;
	}

	if (data_type == DEPTHISP_FW_CALIBRATION_OTP) {
		param[8] = DEPTH_ISP_CALI_ID_OTP_DATA;
		type_name  = "OTP data";
	} else if (data_type == DEPTHISP_FW_CALIBRATION_PACK) {
		param[8] = DEPTH_ISP_CALI_ID_PACK_DATA;
		type_name  = "PACK data";
	} else {
		param[8] = DEPTH_ISP_CALI_ID_SCENARIO_TAB;
		type_name  = "SCTable data";
	}

	cam_info("%s type=%s ext_data=0x%x len=%u", __func__,
			type_name, (u32)ext_data, ext_len);
	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	*p_total_size = ext_len;
	*p_block_size = SPI_BLOCK_BUF_SIZE;

	//warning!second param truncation
	check_sum = calculate_checksum(ext_data, ext_len);
	memcpy(&param[9], &check_sum, 2);

	cam_info("%s start sending calibration data... size=0x%x", __func__, *p_total_size);

	mutex_lock(&drv_data->busy_lock);

	/* (1)send cmd to tell how many blocks to send*/
	drv_data->state = DEPTH_ISP_STATE_IDLE;
	ret = disp_send_cmd(drv_data, ISPCMD_WRITE_CALIBRATION_DATA,
			param, sizeof(param));
	if (ret) {
		cam_err("%s send cmd error", __func__);
		goto out;
	}

	/* wait irq to confirm */
	timeout = wait_event_freezable_timeout(drv_data->wait_queue,\
					(drv_data->state == DEPTH_ISP_STATE_READY),\
					HZ/4);
	if (0 == timeout) {
		cam_err("%s wait ready signal timeout", __func__);
		ret = -EAGAIN;
		goto out;
	}

	/* (2)send ctrl byte */
	/* todo: better to be one message with tx buf */
	drv_data->ext_buf[0] = USPICTRL_MS_CB_DIS;
	spi_write(drv_data->spi, drv_data->ext_buf, 1);

	/* (3)send table block */
	drv_data->state = DEPTH_ISP_STATE_IDLE;
	p_data_pos = ext_data;
	for (left = *p_total_size, block = 0; left != 0; left -= one_size) {
		/* memset(drv_data->ext_buf, 0, SPI_BLOCK_BUF_SIZE); */
		one_size = (left > SPI_BLOCK_BUF_SIZE) ? SPI_BLOCK_BUF_SIZE : left;
		memcpy(drv_data->tx_buf, p_data_pos, one_size);

		ret = spi_write(drv_data->spi, drv_data->tx_buf, one_size);
		if (ret < 0) {
			cam_err("%s spi send error %d", __func__, ret);
			goto out; /*break;*/
		}
		block++;
		p_data_pos += one_size;
	}

	/* wait irq to confirm */
	timeout = wait_event_freezable_timeout(drv_data->wait_queue,\
					(drv_data->state == DEPTH_ISP_STATE_READY),\
					HZ/4);
	if (0 == timeout) {
		cam_err("%s wait ready signal timeout", __func__);
		ret = -EAGAIN;
		goto out;
	}
	cam_info("%s sucess to load calibration data:%d blocks",
			__func__, block);

out:
	mutex_unlock(&drv_data->busy_lock);
	return ret;
}
EXPORT_SYMBOL(disp_load_calibration_data);

int disp_load_ocram_boot(void)
{
	struct disp_data *drv_data = disp_drv_data;
	struct disp_plat_data *plat_data = NULL;
	int ret = 0;
	char *fw_boot_path = NULL;

	cam_info("%s enter", __func__);
	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return -ENODEV;
	}

	plat_data = &drv_data->plat_data;

	mutex_lock(&drv_data->busy_lock);

	gpio_direction_output(plat_data->reset_gpio,  0);
	msleep(15);
	gpio_direction_output(plat_data->reset_gpio,  1);
	msleep(10);

	/*load ocram boot code*/
	drv_data->spi->max_speed_hz = DEPTH_ISP_SPI_SPEED_BOOT;
	ret = spi_setup(drv_data->spi);
	if (ret < 0) {
		cam_err("%s - failed to setup spi speed:%u", __func__,
				drv_data->spi->max_speed_hz);
		goto out;
	}

	disp_init_regs(drv_data, &init_regs_boot[0], ARRAY_SIZE(init_regs_boot));
	fw_boot_path = DEPTH_ISP_OCRAM_BOOT;
	cam_info("%s: d2_ocram_boot_code(%s)",__func__, fw_boot_path);

	ret = disp_load_boot_code(drv_data, fw_boot_path);
	if (ret)
		goto out;
	msleep(1);

out:
	mutex_unlock(&drv_data->busy_lock);
	return ret;
}
EXPORT_SYMBOL(disp_load_ocram_boot);

/*
 * mini isp local functions, no need to export to other driver modules.
 * include :
 * @lowlevel spi transfer
 * @firmware load
 * @interrupte handle...
 */
static struct disp_data* get_disp_data(void)
{
	if (likely(disp_drv_data))
		return disp_drv_data;
	else
		return NULL;
}

static int disp_init_regs(struct disp_data *devdata,
        struct disp_reg_t *preg, int cnt)
{
	int i, ret = 0;

	cam_info("%s enter", __func__);

	/* disp_spi_read_reg(devdata, 0xffef0020, &val); */
	for (i = 0; i < cnt; i++, preg++) {
		if (TIMER_DELAY == preg->reg) {
			udelay(preg->val);
		} else {
			ret |= disp_spi_write_reg(devdata, preg->reg, preg->val);
		}
	}
	return ret;
}


static int disp_send_cmd(struct disp_data *devdata, u16 opcode, u8 *param, u32 len)
{
    u16 *p_len, *p_opcode, total_len;
    int err = 0;
	u16 calc_chk_sum;

	memset(devdata->tx_buf, 0, SPI_TX_BUF_SIZE);

	p_len = (u16 *)&devdata->tx_buf[0];
	p_opcode = (u16 *)&devdata->tx_buf[ISPCMD_OPCODEBYTES];

	total_len = ISPCMD_HDRSIZE + len;
	*p_len      = total_len - ISPCMD_LENFLDBYTES;

	*p_opcode	= opcode;
	memcpy(&devdata->tx_buf[ISPCMD_HDRSIZE], param, len);

	/* calculate checksum */
	calc_chk_sum = calculate_checksum(devdata->tx_buf, total_len);
	memcpy(&devdata->tx_buf[total_len], &calc_chk_sum, ISPCMD_CKSUMBYTES);

	/* add bytes for checksum */
	total_len += ISPCMD_CKSUMBYTES;

	/* send command to slave */
	err = disp_spi_send(devdata,  total_len);

	return err;
}


static int disp_recv_data(struct disp_data *devdata, u8 *param, u32 len)
{
    int err = 0;
	u32 total_len;
	u16  calc_chk_sum, recv_chk_sum;

	memset(devdata->rx_buf, 0, SPI_RX_BUF_SIZE);
    total_len = len + ISPCMD_HDRSIZEWDUMMY + ISPCMD_CKSUMBYTES;

    /* get data via spi bus */
    err = disp_spi_recv(devdata, total_len);
	if (err)
		return err;

    /* calculate checksum */
    memcpy(&recv_chk_sum, &devdata->rx_buf[(total_len - ISPCMD_CKSUMBYTES)], ISPCMD_CKSUMBYTES);
	calc_chk_sum = calculate_checksum(devdata->rx_buf, (total_len - ISPCMD_CKSUMBYTES));
	if(calc_chk_sum != recv_chk_sum) {
		cam_err("%s recicev data check sum not match", __func__);
		return -1;
	}

    /* copy param data to caller */
    memcpy(param, &devdata->rx_buf[ISPCMD_HDRSIZEWDUMMY], len);

    return 0;

}

static int disp_recv_block(struct disp_data *devdata, u8 *out, u32 len)
{
	struct spi_transfer	xfer[2];
	struct spi_message	m;
	u8 ctrl_byte = USPICTRL_MS_CB_DIS;
	int ret = 0;

	if (len > PAGE_SIZE) {
		cam_err("%s invalid block len=%d", __func__, len);
		return -EINVAL;
	}

	cam_info("%s - recv block addr=%p len=%d ", __func__, out, len);

	/*one message only, incase broken by spi interrupt */
	memset(xfer, 0, sizeof(xfer));
	devdata->ext_buf[0] = ctrl_byte;
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].len = sizeof(ctrl_byte);
	xfer[0].cs_change = 1;
	xfer[0].delay_usecs = 1;
	xfer[1].rx_buf = devdata->rx_buf;
	xfer[1].len = len;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	ret = spi_sync(devdata->spi, &m);

	memcpy(out, devdata->rx_buf, len);
	return ret;
}

static u16 calculate_checksum(u8 *buf, u16 size)
{
    u16 index;
	u32 sum = 0;
	u16 sumvalue;

	for (index=0 ; index < size ; index++) {
	  	if( 0 == (index%2))
			sum += buf[index];
		else
			sum += (buf[index] << 8);
	}
	sumvalue = (u16) ( 65536 - (sum & 0x0000FFFF));
	return sumvalue;
}

static void spi_data_debug(const void *buf, int data_len, int dbg_len)
{
	int len=0, pos=0;
	unsigned char *cbuf = (unsigned char *)buf;

	len = (dbg_len>data_len)?data_len:dbg_len;
	len =  roundup(len, 16);
	len = (len<16)?16:len;

	pos = 0;
	while (len > 0) {
		cam_info("buf[%04d]:%02x %02x %02x %02x %02x %02x %02x %02x "
							 "%02x %02x %02x %02x %02x %02x %02x %02x",
					pos,
					cbuf[pos],   cbuf[pos+1], cbuf[pos+2], cbuf[pos+3],
					cbuf[pos+4], cbuf[pos+5], cbuf[pos+6], cbuf[pos+7],
					cbuf[pos+8], cbuf[pos+9], cbuf[pos+10],cbuf[pos+11],
					cbuf[pos+12],cbuf[pos+13],cbuf[pos+14],cbuf[pos+15]);
		len -= 16;
		pos += 16;
	}
}

static irqreturn_t disp_irq_thread(int irq, void *handle)
{
	struct disp_data *drv_data = (struct disp_data *)handle;
	u16	irq_code = 0;
	u8	ctrl_byte = USPICTRL_MS_CB_STS;
	int status;
	struct spi_message	m;
	struct spi_transfer	xfer[2] = {
		[0] = {
			.tx_buf = drv_data->irq_buf,
			.rx_buf = NULL,
			.len = sizeof(ctrl_byte),
		},
		[1] = {
			.tx_buf = NULL,
			.rx_buf = drv_data->irq_buf,
			.len = sizeof(irq_code),
		},
	};

	drv_data->irq_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(drv_data->spi, &m);
	if (status) {
		cam_info("%s - sync error: status=%d", __func__, status);
	}

	memcpy(&irq_code, drv_data->irq_buf, sizeof(irq_code));
	cam_info("disp irq state=0x%04x", irq_code);

	/* ocram test irq fail */
	if (irq_code == DEPTH_ISP_OCRAM_FAIL) {
		ald2_notify_ocram_done(false);
		return IRQ_HANDLED;
	}
	/* ocram test irq success */
	if (irq_code == DEPTH_ISP_OCRAM_SUCC) {
		ald2_notify_ocram_done(true);
		return IRQ_HANDLED;
	}

	/* handle ready done */
	if (irq_code & DEPTH_ISP_IRQ_READY_DONE) {
		drv_data->state = DEPTH_ISP_STATE_READY;
		wake_up(&drv_data->wait_queue);
	}

	/* handle sync signal */
	if (irq_code & DEPTH_ISP_IRQ_SYNC) {
		drv_data->state = DEPTH_ISP_STATE_SYNC;
		wake_up(&drv_data->sync_queue);
	}

	return IRQ_HANDLED;
}

struct err_map {
	u32 err_head;
	char *err_name;
	u32 err_num;
};

static struct err_map disp_error_table[] = {
	{0x001, "PQ", DSM_EXTISP_PQ_ERROR_NO},
	{0x020, "I2C", DSM_EXTISP_I2C_ERROR_NO},
	{0x021, "USPI", DSM_EXTISP_USPI_ERROR_NO},
	{0x022, "VCM", DSM_EXTISP_VCM_ERROR_NO},
	{0x044, "Interrupt", DSM_EXTISP_INTERRUPT_ERROR_NO},
	{0x045, "CommonFunc", DSM_EXTISP_COMMONFUNC_ERROR_NO},
	{0x060, "A3", DSM_EXTISP_A3_ERROR_NO},
	{0x061, "PIPE", DSM_EXTISP_PIPE_ERROR_NO},
	{0x062, "RDN", DSM_EXTISP_RDN_ERROR_NO},
	{0x070, "TXLM", DSM_EXTISP_TXLM_ERROR_NO},
	{0x074, "mipiTx", DSM_EXTISP_MTX_ERROR_NO},
	{0x0D0, "mipiRx", DSM_EXTISP_MRX_ERROR_NO},
	{0x0D2, "FEC0", DSM_EXTISP_FEC0_ERROR_NO},
	{0x0D4, "SENSOR", DSM_EXTISP_SENSOR_ERROR_NO},
	{0x202, "FEC1", DSM_EXTISP_FEC1_ERROR_NO},
	{0x203, "CAP", DSM_EXTISP_CAP_ERROR_NO},
	{0xfff, "other fail", DSM_EXTISP_OTHER_ERROR_NO}, //end
};

static void parser_dmd_error(u32 err, char* out_err_name, char* out_err_num)
{
	u32 head = 0, index = 0;
	bool find = false;

	cam_info("%s: last_error_code[0] = 0x%08x", __func__, err);

	for (index = 0; index < DEPTH_ISP_DMD_ERROR_COUNT;index++) {
		head = (err>>20);
		if (head == disp_error_table[index].err_head ) {
			cam_info("%s: head = 0x%08x", __func__, head);
			snprintf(out_err_name, 16, "%s", disp_error_table[index].err_name);
			snprintf(out_err_num, 8, "%d",	disp_error_table[index].err_num);
			find = true;
			break;
		}
	}

	if (find == false) {
		cam_info("%s: head = 0x%08x", __func__, head);
		snprintf(out_err_name, 16, "%s", disp_error_table[DEPTH_ISP_DMD_ERROR_COUNT-1].err_name);
		snprintf(out_err_num, 8, "%d", disp_error_table[DEPTH_ISP_DMD_ERROR_COUNT-1].err_num);
	}

	cam_info("[I/DSM] %s: err_name = %s, err_num = %s", __func__, out_err_name, out_err_num);
}


static void disp_cmd_delay(void)
{
	enum {
		DEPTH_ISP_CMD_DELAY_US = 1200,
		DEPTH_ISP_MIN_DELAY_LOOP_US = 50,
	};

	int cnt = 0;
	int loop_cnt = DEPTH_ISP_CMD_DELAY_US / DEPTH_ISP_MIN_DELAY_LOOP_US;
	struct timeval start_time, end_time;
	long us_time_gap;

	do_gettimeofday(&start_time);
	for (cnt = 0; cnt < loop_cnt; cnt++) {
		udelay(DEPTH_ISP_MIN_DELAY_LOOP_US);
	}
	do_gettimeofday(&end_time);

	us_time_gap = ((end_time.tv_usec < start_time.tv_usec) ?
		(1000000 - start_time.tv_usec + end_time.tv_usec) :
		(end_time.tv_usec - start_time.tv_usec));
	if (us_time_gap < DEPTH_ISP_CMD_DELAY_US) {
		udelay(DEPTH_ISP_CMD_DELAY_US - us_time_gap);
	}
}

static void disp_dump_err(struct work_struct *work)
{
	struct disp_data *drv_data =
		container_of(work, struct disp_data, dump_err_work);
	int err = 0, index = 0;
	char err_info[256] = {0};
	char tmp_err[20] = {0};
	char err_name[16] = {0};
	char err_num[8] = {0};
	u32 err_code = 0;
	int iSize = 0;

	cam_info("%s enter", __func__);

	/* send get error cmd*/
	mutex_lock(&drv_data->busy_lock);

	err = disp_send_cmd(drv_data, ISPCMD_SYSTEM_GET_ERRORCODE, NULL, 0);
	if (err)
		goto out;
	err = disp_poll_status(drv_data);
	if (err)
		goto out;
	err = disp_recv_data(drv_data, (u8 *)drv_data->last_error_code,
						sizeof(u32)*DEPTH_ISP_MAX_ERR_CODE);
out:
	disp_cmd_delay();
	mutex_unlock(&drv_data->busy_lock);

	/* dump last error code */
	if (!err) {
		for (index=0; index<DEPTH_ISP_MAX_ERR_CODE; index++) {
			cam_info("disp last error code[%d] = 0x%08x",index, drv_data->last_error_code[index]);
			iSize = snprintf(tmp_err, sizeof(tmp_err), "[%d]: 0x%08x\n", index, drv_data->last_error_code[index]);
			strncat(err_info, tmp_err, (sizeof(err_info)-iSize));
		}

		cam_info("%s: last_error_code[0] = 0x%08x", __func__, drv_data->last_error_code[0]);

		if(drv_data->last_error_code[0] != 0){
			parser_dmd_error( drv_data->last_error_code[0], err_name, err_num);

			cam_info("[I/DSM] %s: err_name = %s", __func__, err_name);
			cam_info("[I/DSM] %s: err_num = %s", __func__, err_num);

			err_code = simple_strtoul(err_num, NULL, 0);

			if(!dsm_client_ocuppy(drv_data->client_depthisp)){
				dsm_client_record(drv_data->client_depthisp, "disp %s fail\n", err_name);
				dsm_client_record(drv_data->client_depthisp, "disp last error code:\n");
				dsm_client_record(drv_data->client_depthisp, err_info);
				dsm_client_notify(drv_data->client_depthisp, err_code);
				cam_info("[I/DSM] %s dsm_client_notify", drv_data->client_depthisp->client_name);
			}
		}
	}
}


static void disp_dump_log(struct work_struct *work)
{
	int err = 0;
	struct disp_data *devdata =
			container_of(work, struct disp_data, dump_log_work);
	struct file *fp = NULL;
	mm_segment_t oldfs = get_fs();
	u8 param[8], ctrl_byte = USPICTRL_MS_CB_DIS;
	u32 *psize, *pblock;
	size_t len;
	struct spi_transfer	xfer[2];
	struct spi_message	m;
	int status;

	cam_info("%s enter", __func__);

	psize  = (u32 *)&param[0];
	pblock = (u32 *)&param[4];
	*psize = DEPTH_ISP_FW_LOG_BUF;
	*pblock= SPI_BLOCK_BUF_SIZE;
	memset(xfer, 0, sizeof(xfer));

	/* save log to buffer */
	mutex_lock(&devdata->busy_lock);

	err = disp_send_cmd(devdata, ISPCMD_BULK_LOG_DUMP, param, sizeof(param));
	if (err)
		goto cmd_out;

	err = disp_poll_status(devdata);
	if (err)
		goto cmd_out;

	/*one message only, incase broken by spi interrupt */
	devdata->ext_buf[0] = ctrl_byte;
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].len = sizeof(ctrl_byte);
	xfer[0].cs_change = 1;
	xfer[0].delay_usecs = 1;
	xfer[1].rx_buf = devdata->rx_buf;
	xfer[1].len = DEPTH_ISP_FW_LOG_BUF;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_info("%s - sync error: status=%d", __func__, status);
	}

	/* dump log buffer to file */
	devdata->rx_buf[DEPTH_ISP_FW_LOG_BUF-1] = 0;
	len = strlen((char *)(devdata->rx_buf));
	if (len == 0) {
		cam_warn("%s no data in log buf", __func__);
		goto cmd_out;
	}

	set_fs(KERNEL_DS);
	fp = filp_open("/data/camera/disp.log", O_CREAT|O_APPEND|O_RDWR, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		cam_err("%s open log file error", __func__);
		goto file_out;
	}
	if (fp->f_pos < (4*1024*1024L)) {
		vfs_write(fp, devdata->rx_buf, len, &fp->f_pos);
	} else {
		cam_warn("%s log file is larger than 4MB", __func__);
		filp_close(fp, NULL);
		fp = filp_open("/data/camera/disp.log", O_CREAT|O_TRUNC|O_RDWR, 0666);
		if (IS_ERR_OR_NULL(fp)) {
			cam_err("%s create new log file error", __func__);
			goto file_out;
		}
		vfs_write(fp, devdata->rx_buf, len, &fp->f_pos);
	}

file_out:
	if (!IS_ERR_OR_NULL(fp))
		filp_close(fp, NULL);
	set_fs(oldfs);
cmd_out:
	disp_cmd_delay();
	mutex_unlock(&devdata->busy_lock);
}

static int disp_spi_send(struct disp_data *devdata, u32 len)
{
	int status;
	u8 ctrl_byte = USPICTRL_MS_CB_ORG;
	struct spi_transfer	xfer[2];
	struct spi_message	m;

	cam_debug("%s - send buf len=%d:", __func__, len);

	if ((!devdata) || (len > SPI_TX_BUF_SIZE)) {
		cam_err("%s - invalid arg devdata=%p,len=%d",__func__, devdata, len);
		return -EINVAL;
	}

 	memset(xfer, 0, sizeof(xfer));
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].rx_buf = NULL;
	xfer[0].len = 1;

	xfer[1].tx_buf = devdata->tx_buf;
	xfer[1].rx_buf = NULL;
	xfer[1].len = len;

	devdata->ext_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_err("%s - sync error: status=%d", __func__, status);
		return status;
	}

	if (devdata->debug_config & DEPTH_ISP_DEBUG_SPI_DATA)
		spi_data_debug(devdata->tx_buf, SPI_TX_BUF_SIZE, len);

	return status;
}

static int disp_spi_recv(struct disp_data *devdata, u32 len)
{
	int status;
	u8	ctrl_byte = USPICTRL_MS_CB_RSP;
	struct spi_transfer	xfer[2];
	struct spi_message	m;

	cam_info("%s - recv buf len=%d:", __func__, len);

	if ((!devdata) || (len > SPI_RX_BUF_SIZE)) {
		cam_err("%s - invalid arg devdata=%p,len=%d", __func__, devdata, len);
		return -EINVAL;
	}

	memset(xfer, 0, sizeof(xfer));
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].rx_buf = NULL;
	xfer[0].len = 1;

	xfer[1].tx_buf = NULL;
	xfer[1].rx_buf = devdata->rx_buf;
	xfer[1].len = len;

	devdata->ext_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_err("%s - sync error: status=%d", __func__, status);
		return status;
	}

	if (devdata->debug_config & DEPTH_ISP_DEBUG_SPI_DATA)
		spi_data_debug(devdata->rx_buf, SPI_RX_BUF_SIZE, len);

	return status;
}

static int disp_poll_status(struct disp_data *devdata)
{
	int status, trys;
	u8	ctrl_byte = USPICTRL_MS_CB_STS;
	u16 ack = 0;
	struct spi_transfer	xfer[2];
	struct spi_message	m;

	if (!devdata) {
		cam_err("%s - invalid arg devdata=%p", __func__, devdata);
		return -EINVAL;
	}

    memset(xfer, 0, sizeof(xfer));
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].rx_buf = NULL;
	xfer[0].len = 1;

	xfer[1].tx_buf = NULL;
	xfer[1].rx_buf = devdata->rx_buf;
	xfer[1].len = 2;

	devdata->ext_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);

	for (trys=0 ; trys<DEPTH_ISP_POLL_TIMES; trys++) {
		status = spi_sync(devdata->spi, &m);
		if (status) {
			cam_err("%s - sync error: status=%d", __func__, status);
			return status;
		}
		memcpy(&ack, devdata->rx_buf, sizeof(ack));
		if (ack == DEPTH_ISP_IRQ_READY_DONE)
			break;

		msleep(5);
	}

	if (ack == DEPTH_ISP_IRQ_READY_DONE) {
		cam_info("%s - try times=%d", __func__, trys);
		return 0;
	} else {
		cam_err("%s - timeout ack=0x%04x", __func__, ack);
		return -EAGAIN;
	}
}

static int disp_load_boot_code(struct disp_data *devdata, char *name)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	int file_size, one_size, left, block, ret = 0;
	loff_t pos;

	set_fs(KERNEL_DS);
	fp = filp_open(name, O_RDONLY, 0644);
	if (IS_ERR_OR_NULL(fp)) {
		cam_info("%s open file error", __func__);
		set_fs(oldfs);
		return -EINVAL;
	}

	file_size =(int)(vfs_llseek(fp, 0L, SEEK_END));
	cam_info("start sending boot code... size=0x%x", file_size);

	vfs_llseek(fp, 0L, SEEK_SET);
	pos = fp->f_pos;
	for (left = file_size, block = 0; left > 0; left -= SPI_BLOCK_BUF_SIZE) {
		/* memset(devdata->tx_buf, 0, SPI_BLOCK_BUF_SIZE); */
		one_size = (left > SPI_BLOCK_BUF_SIZE)? SPI_BLOCK_BUF_SIZE : left;

		ret = vfs_read(fp, (char *)devdata->tx_buf, one_size, &pos);
		if (ret < 0) {
			cam_err("%s vfs read error %d", __func__, ret);
			break;
		}

		ret = spi_write(devdata->spi, devdata->tx_buf, one_size);
		if (ret < 0) {
			cam_err("%s spi send error %d", __func__, ret);
			break;
		}
		block++;
	}

	cam_info("%s succeed to send %d blocks", __func__, block);

	/* get boot code version info */
	vfs_llseek(fp, -32L, SEEK_END);
	vfs_read(fp, (char *)&devdata->boot_info, 32, &fp->f_pos);
	devdata->boot_info.info[15] = '\0';
	devdata->boot_info.user[8]  = '\0';
	cam_info("%s boot version: %01u.%04u user=%s", __func__, \
										devdata->boot_info.major,\
										devdata->boot_info.minor,\
										devdata->boot_info.user);
	filp_close(fp, 0);
	set_fs(oldfs);
	return ret;
}

static int disp_load_basic_code(struct disp_data *devdata, char *name)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	int one_size, left, block, ret;
	loff_t pos;
	u8 param[16];
	u32 *p_addr = (u32 *)&param[0];
	u32 *p_total_size =  (u32 *)&param[4];
	u32 *p_block_size =  (u32 *)&param[8];
	u32 *p_chk_sum =  (u32 *)&param[12];
	u8 ctrl_byte = USPICTRL_MS_CB_DIS;

	set_fs(KERNEL_DS);
	fp = filp_open(name, O_RDONLY, 0644);
	if (IS_ERR_OR_NULL(fp)) {
		cam_info("%s open file error", __func__);
		set_fs(oldfs);
		return -EINVAL;
	}

	vfs_llseek(fp, 0L, SEEK_SET);
	pos = fp->f_pos;
	vfs_read(fp, (char *)p_addr,		4, &pos);
	vfs_read(fp, (char *)p_total_size,	4, &pos);
	vfs_read(fp, (char *)p_chk_sum,		4, &pos);
	vfs_read(fp, (char *)p_block_size,	4, &pos);

	cam_info("start sending basic code... size=0x%08x", *p_total_size);
	cam_info("basic code info:addr=0x%08x chksum=0x%08x", *p_addr, *p_chk_sum);
	*p_block_size = SPI_BLOCK_BUF_SIZE;

	/* need to send a cmd to tell mini isp how many blocks to send*/
	ret = disp_send_cmd(devdata, ISPCMD_BULK_WRITE_BASICCODE, param, sizeof(param));
	if (ret) {
		cam_err("%s send cmd error", __func__);
		goto out;
	}

	/* disable other control bytes */
	/* todo: better to be one message with tx buf */
	devdata->ext_buf[0] = ctrl_byte;
	spi_write(devdata->spi, devdata->ext_buf, 1);

	/* basic code actually start with 16bytes offset */
	vfs_llseek(fp, 16L, SEEK_SET);
	pos = fp->f_pos;
	for (left = *p_total_size, block = 0; left > 0; left -= SPI_BLOCK_BUF_SIZE) {
		/* memset(devdata->ext_buf, 0, SPI_BLOCK_BUF_SIZE); */
		one_size = (left > SPI_BLOCK_BUF_SIZE)? SPI_BLOCK_BUF_SIZE : left;

		ret = vfs_read(fp, devdata->tx_buf, one_size, &pos);
		if (ret < 0) {
			cam_err("%s vfs read error %d", __func__, ret);
			break;
		}

		ret = spi_write(devdata->spi, devdata->tx_buf, one_size);
		if (ret < 0) {
			cam_err("%s spi send error %d", __func__, ret);
			break;
		}
		block++;
	}
	cam_info("%s succeed to send %d blocks", __func__, block);

	/* get firmware version info */
	vfs_llseek(fp, -32L, SEEK_END);
	vfs_read(fp, (char *)&devdata->fw_info, 32, &fp->f_pos);
	devdata->fw_info.info[15] = '\0';
	devdata->fw_info.user[8]  = '\0';
	cam_info("%s firmware version: %01u.%04u user=%s", __func__, \
											devdata->fw_info.major,\
											devdata->fw_info.minor,\
											devdata->fw_info.user);

out:
	filp_close(fp, 0);
	set_fs(oldfs);
	return ret;
}

/*
 * mini isp debug functions, used to debug.
 * include :
 * [spi config] item
 * [debug config] item
 *
 */
static ssize_t disp_config_show(struct device *dev,
				struct device_attribute *attr, char *buf);
static ssize_t disp_config_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count);
static DEVICE_ATTR(disp_config, 0644, disp_config_show, disp_config_store);

static ssize_t disp_config_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	int ret = 0, index;
	struct disp_data *pdata = NULL;
	char *offset;

	cam_info("%s - enter", __func__);

	pdata = (struct disp_data *)dev_get_drvdata(dev);
	if (NULL==pdata) {
		cam_err("%s - get pdata error", __func__);
		return 0;
	}

	/* show [spi config info] item */
	offset = buf;
	ret = snprintf(offset, PAGE_SIZE, "[spi config info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  mode=%d, bit=%d, speed=%d\n",
					pdata->spi->mode,
					pdata->spi->bits_per_word,
					pdata->spi->max_speed_hz);

	/* show [debug config info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[debug config info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  debug=0x%08x\n", pdata->debug_config);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  log level=0x%08x\n", pdata->debug_log_level);

	/* show [boot version info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[boot version info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  info=%s\n", pdata->boot_info.info);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  version=%01u.%04u\n",\
										pdata->boot_info.major,\
										pdata->boot_info.minor);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  user=%s\n", pdata->boot_info.user);

	/* show [fw version info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[fw version info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  info=%s\n", pdata->fw_info.info);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  version=%01u.%04u\n",\
										pdata->fw_info.major,\
										pdata->fw_info.minor);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  user=%s\n", pdata->fw_info.user);

	/* show [last error info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[last error info]\n");

	offset += ret;
	for (index=0; index<DEPTH_ISP_MAX_ERR_CODE; index++) {
		ret = snprintf(offset, PAGE_SIZE, "  error code(%d)=0x%08x\n",
						index, pdata->last_error_code[index]);
		offset += ret;
	}
	return (offset-buf);
}

static void disp_config_spi(struct disp_data *pdata,
								u32 mode, u32 bits, u32 speed)
{
	int err;

	if ((mode > 3) || (bits > 32) || (speed > 48000000)) {
		cam_warn("%s - invalid spi config [mode=0x%x bits=%d speed=%d]",
				__func__, mode, bits, speed);
		return ;
	}

	pdata->spi->mode= mode;
	pdata->spi->max_speed_hz = speed;
	pdata->spi->bits_per_word = bits;

	/* handle spi config */
	err = spi_setup(pdata->spi);
	if (!err) {
		cam_info("%s - setup spi [mode=%d bits=%d speed=%d]",
					__func__, mode, bits, speed);
		return;
	}

	/* invalid spi config , set default spi config */
	cam_warn("%s - setup spi failed. use default config", __func__);
	pdata->spi->mode = SPI_MODE_3;
	pdata->spi->max_speed_hz = DEPTH_ISP_SPI_SPEED_BOOT;
	pdata->spi->bits_per_word = 8;
	err = spi_setup(pdata->spi);
	if (!err) {
		cam_info("default spi config unsupport!");
		return;
	}
}

static void disp_config_log(struct disp_data *pdata,
								u32 new_config, u32 new_log_level)
{
	u32 old_config = pdata->debug_config;
	int ret;

	/* config disp linux driver log */
	if ( (old_config & DEPTH_ISP_DEBUG_LOG_FILE) &&
		!(new_config & DEPTH_ISP_DEBUG_LOG_FILE)) {
		queue_work(pdata->work_queue, &pdata->dump_log_work);
		flush_work(&pdata->dump_log_work);
	}
	pdata->debug_config = new_config;

	/* config disp internal firmware log */
	if (pdata->debug_log_level == new_log_level)
		return;
	pdata->debug_log_level = new_log_level;

	mutex_lock(&pdata->busy_lock);
	ret = disp_send_cmd(pdata, ISPCMD_SYSTEM_SET_LOG_LEVEL, (u8 *)&new_log_level, 4);
	mutex_unlock(&pdata->busy_lock);
}

static void disp_switch_spi_channel_to_hw(struct disp_data *pdata)
{
	int ret;

	mutex_lock(&pdata->busy_lock);
	pdata->tx_buf[0] = 0x20;
	ret = spi_write(pdata->spi, pdata->tx_buf, 1);
	if (ret < 0)
		cam_err("%s spi send error %d", __func__, ret);
	mutex_unlock(&pdata->busy_lock);
}


static void disp_spi_dump_reg(struct disp_data *pdata,
				u32 reg_start, u32 reg_end)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	u32 reg, val, size;
	char name[64];

	if (reg_start > reg_end) {
		cam_err("%s invalid range 0x%08x~0x%08x",
				__func__, reg_start, reg_end);
		return;
	}

	size = ((reg_end - reg_start) / 4) + 1;
	/* create reg file, context:start_addr + cnt + n*val */
	memset(name, 0, sizeof(name));
	snprintf(name, sizeof(name)-1,
		"/data/camera/disp_0x%08x-0x%08x.regx",
		reg_start, reg_end);
	set_fs(KERNEL_DS);
	fp = filp_open(name, O_CREAT|O_TRUNC|O_RDWR, 0644);
	if (IS_ERR_OR_NULL(fp)) {
		cam_err("%s create reg bin file error", __func__);
		set_fs(oldfs);
		return;
	}

	/* read register table */
	mutex_lock(&pdata->busy_lock);
	vfs_write(fp, (char*)&reg_start, sizeof(reg_start), &fp->f_pos);
	vfs_write(fp, (char*)&size, sizeof(size), &fp->f_pos);
	for (reg = reg_start; reg <= reg_end; reg += 4) {
		if (disp_spi_read_reg(pdata, reg, &val)) {
			val = 0xA5A5A5A5;
		}
		vfs_write(fp, (char*)&val, sizeof(val), &fp->f_pos);
	}
	mutex_unlock(&pdata->busy_lock);
	filp_close(fp, NULL);
	set_fs(oldfs);
}

static void disp_spi_dump_ram(struct disp_data *pdata, u32 ram_start, u32 len)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	u32 one_size, one_start, left;
	char name[64];

	if (len == 0) {
		cam_info("%s length is 0", __func__);
		return;
	}

	cam_info("%s start=0x%08x len=%d", __func__, ram_start, len);
	memset(name, 0, sizeof(name));
	snprintf(name, sizeof(name)-1,
		"/data/camera/disp_0x%08x-0x%08x.ram",ram_start, ram_start + len);
	set_fs(KERNEL_DS);
	fp = filp_open(name, O_CREAT|O_TRUNC|O_RDWR, 0644);
	if (IS_ERR_OR_NULL(fp)) {
		cam_err("%s create ram bin file error", __func__);
		set_fs(oldfs);
		return;
	}

	mutex_lock(&pdata->busy_lock);
	one_start = ram_start;
	for (left = len; left != 0; left -= one_size) {
		one_size = (left > SPI_BLOCK_BUF_SIZE) ? SPI_BLOCK_BUF_SIZE : left;
		disp_spi_read_ram(pdata, one_start, one_size);
		vfs_write(fp, pdata->rx_buf, one_size, &fp->f_pos);
		one_start += one_size;
	}
	mutex_unlock(&pdata->busy_lock);
	filp_close(fp, NULL);
	set_fs(oldfs);
}

static void disp_cmd_write_reg(struct disp_data *pdata,
										u32 addr, u32 val)
{
	u8 param[8];
	u32 *paddr=(u32 *)&param[0], *pval=(u32 *)&param[4];

	cam_info("%s addr=0x%x, val=0x%x", __func__, addr, val);

	*paddr = addr;
	*pval = val;

	mutex_lock(&pdata->busy_lock);
	if(disp_send_cmd(pdata, ISPCMD_SYSTEM_SET_ISPREGISTER, param, sizeof(param))) {
		cam_err("%s send cmd error", __func__);
	}
	mutex_unlock(&pdata->busy_lock);
}

static int disp_spi_read_ram(struct disp_data *devdata, u32 addr, u32 len)
{
	int status;
	struct spi_transfer xfer[3];
	struct spi_message  m;

	if (len > SPI_BLOCK_BUF_SIZE) {
		cam_err("%s invalid len=%d", __func__, len);
		return -EINVAL;
	}

	memset(xfer, 0, sizeof(xfer));

	/* (1) write 0x15 + 4byte-address */
	memset(&(devdata->tx_buf[0]), 0, 5);
	devdata->tx_buf[0] = SPI_TO_RAM_CTRL;
	memcpy(&(devdata->tx_buf[1]), &addr, sizeof(addr));
	xfer[0].tx_buf = devdata->tx_buf;
	xfer[0].rx_buf = NULL;
	xfer[0].len = 5;

	/* (2) read 1byte dummy + 0xA5 */
	xfer[1].tx_buf = NULL;
	xfer[1].rx_buf = devdata->ext_buf;
	xfer[1].len = 2;

	/* (3) read n*byte ram */
	xfer[2].tx_buf = NULL;
	xfer[2].rx_buf = devdata->rx_buf;
	xfer[2].len = len;

	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	spi_message_add_tail(&xfer[2], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_err("%s - sync error: status=%d", __func__, status);
		return status;
	}

	if (devdata->ext_buf[1] == 0xA5) {
		status = 0;
		cam_info("%s read ram len=%d ok", __func__, len);
	} else {
		status = -EINVAL;
		cam_info("%s read ram failed check=[%02x %02x]",
			__func__,
			devdata->ext_buf[0], devdata->ext_buf[1]);
	}

	return status;
}

static int disp_spi_read_reg(struct disp_data *devdata, u32 addr, u32* val)
{
	int status;
	struct spi_transfer xfer;
	struct spi_message  m;
	int i;

	memset(&(devdata->tx_buf[0]), 0, 20);
	devdata->tx_buf[0] = SPI_TO_REG_CTRL;
	memcpy(&(devdata->tx_buf[1]), &addr, sizeof(addr));

	/* write 0x19 + 4byte-address + dummy */
	/* read dummy + 0xa5 + 4byte-val */
	memset(&xfer, 0, sizeof(xfer));
	xfer.tx_buf = devdata->tx_buf;
	xfer.rx_buf = devdata->rx_buf;
	xfer.len = 20;

	spi_message_init(&m);
	spi_message_add_tail(&xfer, &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_err("%s - sync error: status=%d", __func__, status);
		return status;
	}

	for (i = 5; i < 20; i++) {
		if (devdata->rx_buf[i] == 0xA5) {
			break;
		}
	}
	if (i < (20 - sizeof(*val))) {
		memcpy(val, &(devdata->rx_buf[i+1]), sizeof(*val));
		cam_info("%s reg=0x%08x val=0x%08x", __func__, addr, *val);
		status = 0;
	} else {
		cam_err("%s reg=0x%08x read failed", __func__, addr);
		status = -EINVAL;
	}

	/* if (devdata->debug_config & DEPTH_ISP_DEBUG_SPI_DATA) { */
	/* 	spi_data_debug(devdata->tx_buf, SPI_TX_BUF_SIZE, 5); */
	/* 	spi_data_debug(devdata->rx_buf, SPI_RX_BUF_SIZE, 20); */
	/* } */

	return status;
}


static int disp_spi_write_reg(struct disp_data *devdata, u32 addr, u32 val)
{
	u8 param[9];
	u32 *paddr=(u32 *)&param[1], *pval=(u32 *)&param[5];
	int status;
	struct spi_transfer xfer;
	struct spi_message  m;

	if (!devdata) {
		cam_err("%s - invalid arg devdata=%p,",__func__, devdata);
		return -EINVAL;
	}

	*paddr = addr;
	*pval = val;
	param[0] = 9;
	memcpy(&devdata->tx_buf[0], param, sizeof(param));

	memset(&xfer, 0, sizeof(xfer));

	xfer.tx_buf = devdata->tx_buf;
	xfer.rx_buf = NULL;
	xfer.len = 9;

	spi_message_init(&m);
	spi_message_add_tail(&xfer, &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		cam_err("%s - sync error: status=%d", __func__, status);
		return status;
	}
	if (devdata->debug_config & DEPTH_ISP_DEBUG_SPI_DATA)
		spi_data_debug(devdata->tx_buf, SPI_TX_BUF_SIZE, 9);

	return status;
}


static void disp_test_spi(struct disp_data *pdata)
{
	int index;
	int status;
	struct spi_transfer	xfer;
	struct spi_message m;

	if(!pdata){
		return;
	}

	memset(&xfer, 0, sizeof(xfer));
	xfer.tx_buf = pdata->tx_buf;
	xfer.rx_buf = pdata->rx_buf;
	xfer.len = SPI_TX_BUF_SIZE;

	mutex_lock(&pdata->busy_lock);

	for (index = 0; index < SPI_TX_BUF_SIZE; index++) {
		get_random_bytes(&(pdata->tx_buf[index]), 1);
		pdata->rx_buf[index] = 0;
	}

	spi_message_init(&m);
	spi_message_add_tail(&xfer, &m);
	status = spi_sync(pdata->spi, &m);
	if (status) {
		mutex_unlock(&pdata->busy_lock);
		cam_err("%s - sync error: status=%d", __func__, status);
		return;
	}

	mutex_unlock(&pdata->busy_lock);

	if (pdata->debug_config & DEPTH_ISP_DEBUG_SPI_DATA) {
		cam_info("%s - send buf len=%d:", __func__, SPI_TX_BUF_SIZE);
		spi_data_debug(pdata->tx_buf, SPI_TX_BUF_SIZE, SPI_TX_BUF_SIZE);
		cam_info("%s - recv buf len=%d:", __func__, SPI_RX_BUF_SIZE);
		spi_data_debug(pdata->rx_buf, SPI_TX_BUF_SIZE, SPI_TX_BUF_SIZE);
	}
}

#define MOVE_TO_DIGIT(pos) \
	while ((*pos) && (!isdigit(*pos))) { pos++; }


static void do_spi_config(struct disp_data *pdata, const char *pos)
{
	u32 mode = 0, bits = 0, speed = 0;

	MOVE_TO_DIGIT(pos);
	mode = simple_strtoul(pos, (char **)&pos, 0);
	MOVE_TO_DIGIT(pos);
	bits = simple_strtoul(pos, (char **)&pos, 0);
	MOVE_TO_DIGIT(pos);
	speed = simple_strtoul(pos, (char **)&pos, 0);

	disp_config_spi(pdata, mode, bits, speed);
}

static void do_log_config(struct disp_data *pdata, const char *pos)
{
	u32 new_log_config = 0, new_log_level = 0;

	MOVE_TO_DIGIT(pos);
	new_log_config = simple_strtoul(pos, (char **)&pos, 0);
	MOVE_TO_DIGIT(pos);
	new_log_level = simple_strtoul(pos, (char **)&pos, 0);

	disp_config_log(pdata, new_log_config, new_log_level);
}


static void do_write_reg_config(struct disp_data *pdata, const char *pos)
{
	u32 write_reg_addr = 0, write_reg_val = 0;

	MOVE_TO_DIGIT(pos);
	write_reg_addr = simple_strtoul(pos, (char **)&pos, 0);
	MOVE_TO_DIGIT(pos);
	write_reg_val = simple_strtoul(pos, (char **)&pos, 0);

	disp_spi_write_reg(pdata, write_reg_addr, write_reg_val);
}

static void do_dump_reg_config(struct disp_data *pdata, const char *pos)
{
	u32 dump_reg_start, dump_reg_end;
	int i;

	disp_switch_spi_channel_to_hw(pdata);
	if (*pos == '=') {
		MOVE_TO_DIGIT(pos);
		dump_reg_start = simple_strtoul(pos, (char **)&pos, 0);
		MOVE_TO_DIGIT(pos);
		dump_reg_end = simple_strtoul(pos, (char **)&pos, 0);

		disp_spi_dump_reg(pdata, dump_reg_start, dump_reg_end);
	} else {
		for (i = 0; i < ARRAY_SIZE(default_reg_range_table); i++) {
			disp_spi_dump_reg(pdata,
					default_reg_range_table[i].start,
					default_reg_range_table[i].end);
		}
	}
}

static void do_dump_ram_config(struct disp_data *pdata, const char *pos)
{
	u32 dump_ram_start = 0, dump_ram_total = 0;

	MOVE_TO_DIGIT(pos);
	dump_ram_start = simple_strtoul(pos, (char **)&pos, 0);
	MOVE_TO_DIGIT(pos);
	dump_ram_total = simple_strtoul(pos, (char **)&pos, 0);

	disp_switch_spi_channel_to_hw(pdata);
	disp_spi_dump_ram(pdata, dump_ram_start, dump_ram_total);
}

static ssize_t disp_config_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct disp_data *pdata = NULL;
	const char *pos;
	int ret;

	cam_info("%s - enter", __func__);

	pdata = (struct disp_data *)dev_get_drvdata(dev);
	if (NULL == pdata) {
		cam_err("%s - get pdata error", __func__);
		return 0;
	}

	if (count == 0)
		return 0;

	pos = buf;
	if (0 == strncmp("spi_config", pos, strlen("spi_config"))) {
		do_spi_config(pdata, pos + strlen("spi_config"));
	} else if (0 == strncmp("log_config", pos, strlen("log_config"))) {
		do_log_config(pdata, pos + strlen("log_config"));
	}  else if (0 == strncmp("spi_write_reg", pos, strlen("spi_write_reg"))) {
		do_write_reg_config(pdata, pos + strlen("spi_write_reg"));
	} else if (0 == strncmp("spi_dump_reg", pos, strlen("spi_dump_reg"))) {
		do_dump_reg_config(pdata, pos + strlen("spi_dump_reg"));
	} else if (0 == strncmp("spi_dump_ram", pos, strlen("spi_dump_ram"))) {
		do_dump_ram_config(pdata, pos + strlen("spi_dump_ram"));
	}

	return count;
}

static void disp_spi_cs_set(u32 control)
{
	int ret = 0;
	struct disp_data *drv_data = get_disp_data();
	struct disp_plat_data *plat_data = NULL;

	if (!drv_data) {
		cam_err("%s no driver data", __func__);
		return ;
	}

	//cam_info("%s: control = %s", __func__, (control==0)?"select":"diselect");

	plat_data = &drv_data->plat_data;
	if (SSP_CHIP_SELECT == control) {
		ret = gpio_direction_output(plat_data->spi_cs_gpio, control);
		/* cs steup time at least 10ns */
		ndelay(10);
	} else {
		/* cs hold time at least 4*40ns(@25MHz) */
		ret = gpio_direction_output(plat_data->spi_cs_gpio, control);
		ndelay(200);
	}

    if (ret < 0)
		cam_err("%s: fail to set gpio cs, result = %d.", __func__, ret);
}

static int disp_get_dt_data(struct device *dev, struct disp_plat_data *plat_data)
{
	struct device_node *np;
	int ret = 0;

	if (!dev || !dev->of_node) {
		cam_err("%s dev or dev node is NULL", __func__);
		return -EINVAL;
	}

	np = dev->of_node;
	ret  = of_property_read_u32(np, "depth_isp,cs_gpio", &plat_data->spi_cs_gpio);
	ret |= of_property_read_u32(np, "depth_isp,reset_gpio", &plat_data->reset_gpio);
	ret |= of_property_read_u32(np, "depth_isp,irq_gpio", &plat_data->irq_gpio);
	ret |= of_property_read_u32(np, "depth_isp,chip_type", &plat_data->chip_type);
	cam_info("%s spi_cs_gpio=%d, reset_gpio=%d, irq_gpio=%d, chip_type=%d",
		__func__,
		plat_data->spi_cs_gpio, plat_data->reset_gpio,
		plat_data->irq_gpio, plat_data->chip_type);

	plat_data->spidev0_chip_info.hierarchy = 0;
	ret |= of_property_read_u32(np, "pl022,interface", &plat_data->spidev0_chip_info.iface);
	ret |= of_property_read_u32(np, "pl022,com-mode", &plat_data->spidev0_chip_info.com_mode);
	ret |= of_property_read_u32(np, "pl022,rx-level-trig", &plat_data->spidev0_chip_info.rx_lev_trig);
	ret |= of_property_read_u32(np, "pl022,tx-level-trig", &plat_data->spidev0_chip_info.tx_lev_trig);
	ret |= of_property_read_u32(np, "pl022,ctrl-len", &plat_data->spidev0_chip_info.ctrl_len);
	ret |= of_property_read_u32(np, "pl022,wait-state", &plat_data->spidev0_chip_info.wait_state);
	ret |= of_property_read_u32(np, "pl022,duplex", &plat_data->spidev0_chip_info.duplex);
#if defined(CONFIG_ARCH_HI3630FPGA) || defined(CONFIG_ARCH_HI3630)
	plat_data->spidev0_chip_info.slave_tx_disable =
		of_property_read_bool(np, "pl022,slave-tx-disable");
#endif

	/* use gpio cs control */
	plat_data->spidev0_chip_info.cs_control = disp_spi_cs_set;
	if (ret) {
		cam_err("%s invalid property", __func__);
		return ret;
	}

	plat_data->pinctrl = devm_pinctrl_get(dev);
	if (IS_ERR(plat_data->pinctrl)) {
		cam_err("%s could not get pinctrl", __func__);
		return PTR_ERR(plat_data->pinctrl);
	}

	plat_data->pins_default = pinctrl_lookup_state(plat_data->pinctrl,
						 PINCTRL_STATE_DEFAULT);
	if (IS_ERR(plat_data->pins_default)) {
		cam_err("%s could not get default pinstate", __func__);
		return PTR_ERR(plat_data->pins_default);
	}

	plat_data->pins_idle = pinctrl_lookup_state(plat_data->pinctrl,
						 PINCTRL_STATE_IDLE);
	if (IS_ERR(plat_data->pins_idle)) {
		cam_err("%s could not get idle pinstate", __func__);
		return PTR_ERR(plat_data->pins_idle);
	}

	/* set pin from init state to normal state */
	if (!IS_ERR(plat_data->pins_default)) {
		ret = pinctrl_select_state(plat_data->pinctrl, plat_data->pins_default);
		if (ret) {
			cam_err("%s could not set default pins", __func__);
		}
	}

	return ret;
}

static int disp_probe(struct spi_device *spi)
{
	struct disp_data *drv_data = NULL;
	struct disp_plat_data *plat_data = NULL;
	int ret = 0;

	cam_info("%s enter", __func__);

	/* step 1: alloc driver data struct */
	drv_data = kmalloc(sizeof(*drv_data), GFP_KERNEL);
	if (!drv_data) {
		cam_err("probe - can not alloc driver data");
		return -ENOMEM;
	}
	memset(drv_data, 0, sizeof(*drv_data));

	plat_data = &drv_data->plat_data;
	ret = disp_get_dt_data(&spi->dev, plat_data);
	if (ret < 0) {
		cam_err("%s failed to depthisp_get_dt_data", __func__);
		goto err_no_pinctrl;
	}

	drv_data->tx_buf  = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(2*PAGE_SIZE));
	drv_data->rx_buf  = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(2*PAGE_SIZE));
	drv_data->ext_buf = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(PAGE_SIZE));
	drv_data->irq_buf = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(PAGE_SIZE));
	cam_info("%s tx_buf=0x%p rx_buf=0x%p ext_buf=0x%p, irq_buf=0x%p",
		__func__,
		drv_data->tx_buf, drv_data->rx_buf, drv_data->ext_buf, drv_data->irq_buf);
	if ((!drv_data->tx_buf) || (!drv_data->rx_buf) ||
		(!drv_data->ext_buf)|| (!drv_data->irq_buf)) {
		cam_err("%s can not alloc dma buf page", __func__);
		ret = -ENOMEM;
		goto err_alloc_buf;
	}

	/* step 2: init driver data */
	drv_data->spi = spi;
	drv_data->state = DEPTH_ISP_STATE_IDLE;
	drv_data->debug_config = DEPTH_ISP_DEBUG_SPI_DATA;
	mutex_init(&drv_data->busy_lock);
	INIT_WORK(&drv_data->dump_log_work, disp_dump_log);
	INIT_WORK(&drv_data->dump_err_work, disp_dump_err);
	init_waitqueue_head(&drv_data->wait_queue);
	init_waitqueue_head(&drv_data->sync_queue);
	drv_data->work_queue = create_singlethread_workqueue(
									dev_name(&spi->dev));
	if (!drv_data->work_queue) {
		cam_err("probe - create workqueue error");
		ret = -EBUSY;
		goto err_create_queue;
	}

	/* step 3: setup spi */
	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = DEPTH_ISP_SPI_SPEED_BOOT;
	spi->bits_per_word = 8;
	spi->controller_data = &plat_data->spidev0_chip_info;
	ret = spi_setup(spi);
	if (ret<0) {
		cam_err("probe - setup spi error");
		goto err_spi_setup;
	}

	/* step 4:config gpio & irq */
	ret = gpio_request(plat_data->spi_cs_gpio, "depth_isp_spi_cs");
	if (ret) {
		cam_err("probe - request spi cs gpio error");
		goto err_cs_gpio;
	}
	/* config spi_cs to OUT-HI */
	gpio_direction_output(plat_data->spi_cs_gpio, 1);

	ret = gpio_request(plat_data->reset_gpio, "depth_isp_reset");
	if (ret) {
		cam_err("probe - request reset gpio error");
		goto err_reset_gpio;
	}

	ret = gpio_request(plat_data->irq_gpio, "depth_isp_irq");
	if (ret) {
		cam_err("probe - request irq gpio error");
		goto err_irq_gpio;
	}
	if (gpio_direction_input(plat_data->irq_gpio))
		cam_warn("probe - irq gpio direction input error");
    spi->irq = gpio_to_irq(plat_data->irq_gpio); //add by hefei
	ret = request_threaded_irq(spi->irq, NULL, disp_irq_thread,
							IRQF_ONESHOT | IRQF_TRIGGER_RISING,
							"depth_isp", drv_data);
	if (ret) {
		cam_err("probe - request irq error(%d)", spi->irq);
		goto err_irq_config;
	}
	disable_irq(spi->irq);

	/* setp 5:other additional config */
	ret = device_create_file(&spi->dev, &dev_attr_disp_config);
	if (ret) {
	    cam_err("probe - create dev attr file fail");
		goto err_dev_attr;
	}

	/* setp 6: set driver_data to device */
	spi_set_drvdata(spi, drv_data);

	if (drv_data->client_depthisp == NULL) {
		drv_data->client_depthisp = dsm_register_client(&dev_depthisp);
	}

	disp_drv_data = drv_data;

	cam_info("depth isp probe success");
	return ret;

err_dev_attr:
	free_irq(spi->irq, drv_data);
err_irq_config:
	gpio_free(plat_data->irq_gpio);
err_irq_gpio:
	gpio_free(plat_data->reset_gpio);
err_reset_gpio:
	gpio_free(plat_data->spi_cs_gpio);
err_cs_gpio:
err_spi_setup:
	destroy_workqueue(drv_data->work_queue);
err_create_queue:
	free_pages((unsigned long)drv_data->tx_buf,  get_order(2*PAGE_SIZE));
	free_pages((unsigned long)drv_data->rx_buf,  get_order(2*PAGE_SIZE));
	free_pages((unsigned long)drv_data->ext_buf, get_order(PAGE_SIZE));
	free_pages((unsigned long)drv_data->irq_buf, get_order(PAGE_SIZE));
err_alloc_buf:
err_no_pinctrl:
	kfree(drv_data);
	disp_drv_data = NULL;
	return ret;
}

static const struct of_device_id spi_dt_ids[] = {
	{ .compatible = "depth_isp" },
	{},
};

MODULE_DEVICE_TABLE(of, spidev_dt_ids);
static struct spi_driver disp_drv = {
	.driver = {
		.name =         "depth_isp",
		.owner =        THIS_MODULE,
		.of_match_table = of_match_ptr(spi_dt_ids),
	},
	.probe =        disp_probe,
	.remove =       NULL,
};

static int __init disp_module_init(void)
{
	return spi_register_driver(&disp_drv);
}

static void __exit disp_module_exit(void)
{
	spi_unregister_driver(&disp_drv);
}

module_init(disp_module_init);
module_exit(disp_module_exit);
MODULE_LICENSE("Huawei/GPL");
