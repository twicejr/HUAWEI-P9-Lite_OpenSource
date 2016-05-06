/*
 *
 * Copyright (C) 2013 HUAWEI, Inc.
 * Author: mouzhenguo<mike.mou@huawei.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>
#include <linux/delay.h>
#include <asm/segment.h>
#include <linux/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/ctype.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/vmalloc.h>
#include <linux/random.h>
#include <linux/irq.h>
#include <linux/amba/pl022.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/platform_device.h>
#include <linux/sysfs.h>
#include <linux/wakelock.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/wakelock.h>
#include <linux/workqueue.h>
#include <asm/atomic.h>
#include <linux/of_gpio.h>
#include <dsm/dsm_pub.h>
#include "fpga_ice40.h"
#include <linux/kernel.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#define HWLOG_TAG antenna_fpga
HWLOG_REGIST();
#define DRIVER_VERSION        "1.0.0"
#define GPIO_PULL_HIGH 1
#define GPIO_PULL_LOW 0
#define FPGA_READ 0
#define FPGA_CLOCK_OPEN 0x30
#define FPGA_CLOCK_CLOSE 0xc0
#define FPGA_WRITE 1
#define FPGA_REGISTER_VERSION 0x40
#define FPGA_REGISTER_TESTMODE 0xc0
#define FPGA_REGISTER_EXCEPTION 0x80
#define CRC_ERR_MAX 3
#define PRE_ICE40_IMAGE_FILENAME 32
#define ICE40_VCCIO0_STR 32
#define INVALID_CDONE_GPIO 123
#define MAX_DOWNLOAD_TIMES 3
#define ICE40_IMAGE_FILE_DIR "/system/fpgaice40/"
#define ICE40_IMAGE_FILENAME_LENTH 32
#define ICE40_IMAGE_FILEPAHT_LENTH (64 + ICE40_IMAGE_FILENAME_LENTH)
#define SPI_DATA_LEN 10
#define SPI_OUTPUT_DATA_LEN 8+3
#define TEST_MODE_INPUT_LEN 9+2
#define INVALID_VERSION1 "00000000"
#define INVALID_VERSION2 "ffffffff"
#define INVALID_CRC_GPIO 0
#define FPGA_TALBE_INPUT_LEN 16
#define FPGA_TALBE_OUTPUT_LEN 16
#define FPGA_TALBE_ITEM_SIZE 600
#define FPGA_TALBE_FILE_SIZE FPGA_TALBE_ITEM_SIZE*(FPGA_TALBE_OUTPUT_LEN + FPGA_TALBE_INPUT_LEN)
#define FPGA_DSM_BUF_SIZE 1024
#define FPGA_REG_NUM 2
#define STR_RETURN_LEN 32
#define SLEEP_BETWEEN_DOWNLOAD 10
#define RETRY_TIME 10
#define DUMMY_DATA_LEN 49
#define FPGA_TESTMODE_WRITE_REGISTER 0x80
#define BYTE_PER_COUNT 8
#define NORMAL_GPIO_MAX 224
#define DMD_ERR_NO 21900
#define BASE_BINARY 2
#define BASE_HEX 16
#define INPUT_FLAG_CHAR ','
#define OUTPUT_FLAG_CHAR ';'


typedef struct fpga_plat_data {
    int spi_cs_gpio;
    int crc_gpio;
    int reset_gpio;
    int power_gpio;
    int cdone_gpio;
    int power_disable;
    char ice40_pre_image_filename[PRE_ICE40_IMAGE_FILENAME];
    char ice40_fpga_vccio0[ICE40_VCCIO0_STR];
}fpga_plat_data;

typedef struct fpga_data {
    struct spi_device    *spi;
    struct fpga_plat_data plat_data;
    unsigned char    *tx_buf;
    struct mutex fpga_download_mutex;
}fpga_data;

typedef enum {
    NO_ERR,
    DOWNLOAD_ERR,
    VOLTAGE_ERR,
    CLK_ERR,
    CRC_ERR,
    SPI_READ_ERR,
    SCAN_TABLE_ERR,
    HARDWARE_ERR,
    INVILED_ERR
} FPGA_EXCEPTION;

typedef enum {
    FPGA_ERR,
    FPGA_SUCCESS,
    FPGA_DONE,
}FPGA_SCAN_TXT ;

typedef struct {
    int input;
    char output[SPI_DATA_LEN];
}talbe_command;

typedef struct talbe_data{
   char inputdata[FPGA_TALBE_INPUT_LEN];
   char outputdata[FPGA_TALBE_OUTPUT_LEN];
}table_data;

static char ice40_bin_dir[ICE40_IMAGE_FILEPAHT_LENTH] = {0};
static FPGA_EXCEPTION erro_num = NO_ERR;
static FPGA_EXCEPTION scan_table_error = SCAN_TABLE_ERR;
static unsigned char reg_val[FPGA_REG_NUM] = {0};
static struct dsm_client *fpga_ice40_dclient = NULL;
static struct dsm_dev fpga_ice40 = {
    .name = "dsm_fpgaice40",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
    .fops = NULL,
    .buff_size = FPGA_DSM_BUF_SIZE,
};
static  fpga_data *fpga_drv_data = NULL;
static struct wake_lock spi_write_lock;
static FPGA_EXCEPTION download_err = DOWNLOAD_ERR;
static struct work_struct exception_callback_work;
static struct workqueue_struct *exception_callback_q = NULL;
static struct work_struct download_work;
static struct workqueue_struct *download_q = NULL;
static unsigned int fpga_download_times = 0;

static int check_valid_version();
static int get_image_version(char *buf);
static  fpga_data* get_fpga_data(void);
static int hexTou16(const unsigned char *indata, int len);
static int ice40_dir_download_firmware(char *name, int cs_ps);

int g_spi_fpga_cs_gpio;

static void fpga_notify_exception(FPGA_EXCEPTION fpga_err)
{
    if (!dsm_client_ocuppy(fpga_ice40_dclient)) {
        /* record message */
        dsm_client_record(fpga_ice40_dclient, "fpga  reg 0x%x,  reg 0x%x\n", reg_val[0], reg_val[1]);
        /* notify */
        dsm_client_notify(fpga_ice40_dclient, fpga_err + DMD_ERR_NO -1);
    }
    return;
}

static int get_exception_type()
{
    int ret = 0;
    char read_exception[SPI_DATA_LEN];
    char indata[SPI_DATA_LEN];
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return -1;
    }
    plat_data = &drv_data->plat_data;
    memset(read_exception, 0, SPI_DATA_LEN);
    memset(indata, 0, SPI_DATA_LEN);
    indata[0] = FPGA_READ;
    indata[1] = FPGA_REGISTER_EXCEPTION;
    indata[2] = 0;
    ice40_set_cs_callback(NORMAL_RATE, plat_data->spi_cs_gpio);
    ret = ice40_data_spi_write_then_read(indata, SPI_DATA_LEN, read_exception, SPI_DATA_LEN);
    if(ret) {
        hwlog_err("%s read exception register fail!\n", __func__);
        return -1;
    }
    return read_exception[5];
}

static int crc_err_num = 0;
static void fpga_exception_work(struct work_struct *work)
{
    int ret = 0;
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    FPGA_EXCEPTION fpga_err = NO_ERR;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return;
    }
    plat_data = &drv_data->plat_data;
    ret = gpio_get_value_cansleep(plat_data->crc_gpio);
    hwlog_info("%s %d gpio_get_value_cansleep(plat_data->crc_gpio) = %d \n",__func__,__LINE__,ret);
    if(ret){
             return;
    }
    /* cdone pin disconnected, judge power err by reading version register
       cdone pin connected, judge power err by reading cdone gpio value */
    if(((INVALID_CDONE_GPIO == plat_data->cdone_gpio) && (SUCCESS == check_valid_version())) 
        || ((INVALID_CDONE_GPIO != plat_data->cdone_gpio) && (0 != gpio_get_value(plat_data->cdone_gpio)))){
        ret = get_exception_type();
        if (ret < 0){
            hwlog_err("%s %d read spi register ret=%d fail! \n",__func__,__LINE__,ret);
            fpga_err = SPI_READ_ERR;
        }else{
            hwlog_err("%s %d fpga exception type is %d! \n",__func__,__LINE__,ret);
            fpga_err = ret;
        }
    }else {
         hwlog_err("%s %d voltage err occured! \n",__func__,__LINE__);
         fpga_err = VOLTAGE_ERR;
    }
    /*dmd process*/
    fpga_notify_exception(fpga_err);
    switch(fpga_err) {
        case VOLTAGE_ERR:
        case CLK_ERR:
            crc_err_num = 0;//Clear crc err, before download the firmware.
            ret = ice40_dir_download_firmware(ice40_bin_dir, BOOT_RATE);
            break;
        case CRC_ERR:
        {
            if(crc_err_num == CRC_ERR_MAX) {
                crc_err_num = 0;
                ret = ice40_dir_download_firmware(ice40_bin_dir, BOOT_RATE);
            }else{
                crc_err_num++;
            }
            break;
        }
        case SPI_READ_ERR:
        case INVILED_ERR:
        default:
            hwlog_err("%s %d fpga unhandled error ! \n",__func__,__LINE__);
            break;
    }
}

static irqreturn_t fpga_exception_callback(int irq, void *data)
{
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    plat_data = &drv_data->plat_data;
    if(get_firmware_is_downloading()) {
        hwlog_err("%s %d fpga is downloading firmware, not response the exception! \n",__func__,__LINE__);
        return IRQ_HANDLED;
    }

    if(GPIO_OEM_VALID(plat_data->crc_gpio )){
        queue_work(exception_callback_q, &exception_callback_work);
    }
    return IRQ_HANDLED;
}

static int ice40_firmware_cdone()
{
    int ret = 0;
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    plat_data = &drv_data->plat_data;
    ret = gpio_get_value(plat_data->cdone_gpio);
    hwlog_info("FPGA: firmware cdone = %d \n", ret);
    return ret;
}

static fpga_data* get_fpga_data(void)
{
    if (likely(fpga_drv_data))
        return fpga_drv_data;
    else
        return NULL;
}

static int ice40_send_dummy_data()
{
    unsigned char  dummy_data[DUMMY_DATA_LEN];
    return ice40_data_spi_write(dummy_data, DUMMY_DATA_LEN);
}

static int check_valid_version()
{
    char buf[SPI_OUTPUT_DATA_LEN] = {0};

    get_image_version(buf);
    hwlog_info("%s check_valid_version image version: %s.\n", __func__, buf);
    if(!strncasecmp(buf,INVALID_VERSION1 , strlen(INVALID_VERSION1)) ||
        !strncasecmp(buf,INVALID_VERSION2 , strlen(INVALID_VERSION2)) ) {
        return FAIL;
    }
    return SUCCESS;
}

static int read_file_and_download_firmware(char *name)
{
    mm_segment_t oldfs = get_fs();
    struct file *fp = NULL;
    int file_size = 0;
    loff_t pos;
    int ret = 0;
    int dummy_datalen = 7;//The dummy data len.Move the dummy data here, will never be able to change the truth table.
    fpga_data *drv_data = get_fpga_data();
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }

    set_fs(KERNEL_DS);
    fp = filp_open(name, O_RDONLY, 755);
    if (IS_ERR_OR_NULL(fp)) {
        hwlog_err("%s open file %s error\n", __func__, name);
        goto erro_open_file;
    }

    file_size =(int)(vfs_llseek(fp, 0L, SEEK_END)) + dummy_datalen;
    hwlog_info("start sending fpga firmware.. size=0x%x\n", file_size);
    drv_data->tx_buf = __get_free_pages(GFP_KERNEL|GFP_DMA|__GFP_ZERO, get_order(file_size));
    if (!drv_data->tx_buf ){
        hwlog_err("probe - can not alloc dma buf page\n");
        goto error_alloc;
    }
    vfs_llseek(fp, 0L, SEEK_SET);
    pos = fp->f_pos;
    ret = vfs_read(fp, (char *)drv_data->tx_buf, file_size - dummy_datalen, &pos);
    if (ret < 0) {
        hwlog_err("%s vfs read error %d\n", __func__, ret);
        goto error_read_file;
    }
    ret = ice40_data_spi_write_whole_image(drv_data->tx_buf, file_size);
    if (ret) {
        hwlog_err("%s spi send error %d\n", __func__, ret);
        goto error_read_file;
    }
    filp_close(fp, 0);
    set_fs(oldfs);
    free_pages((unsigned long)drv_data->tx_buf,  get_order(file_size));
    return SUCCESS;

error_read_file:
    filp_close(fp, 0);
    free_pages((unsigned long)drv_data->tx_buf,  get_order(file_size));
error_alloc:
erro_open_file:
    set_fs(oldfs);
    return FAIL;
}

/*
 *Input:The ice40bin file data and the size of the image.
 *Output:If download success.

*/
static int ice40_dir_download_firmware(char *name, int cs_ps)
{
    int ret = SUCCESS;
    int i = 0;
    fpga_plat_data *plat_data = NULL;
    fpga_data *drv_data = get_fpga_data();

    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    mutex_lock(&drv_data->fpga_download_mutex);

    plat_data = &drv_data->plat_data;
    /*Try MAX_DOWNLOAD_TIMES times if one time failed. If it is still fail, we think that there is hardware exception.*/
    wake_lock(&spi_write_lock);

    ret = ice40_set_cs_callback(cs_ps, plat_data->spi_cs_gpio);
    if(ret) {
        hwlog_err("%s vice40_set_cs_callback fail\n", __func__);
        wake_unlock(&spi_write_lock);
        return FAIL;
    }
    for (i = 0; i < MAX_DOWNLOAD_TIMES; i++) {
        hwlog_info("%s firmware try download %d times!\n", __func__, i);
        fpga_download_times ++;
        hwlog_info("%s fgpa firmware has been loaded %d times in total!\n", __func__, fpga_download_times);
        /*step1:set the downloading mode. */
        set_firmware_reset_gpio(plat_data->reset_gpio);
        set_firmware_is_downloading(TRUE);
        /*step2:open the image file and get the image.*/
        ret = read_file_and_download_firmware(name);
        if(ret) {
            hwlog_err("%s:FPGA:send dummy firmware fail\n", __func__);
            msleep(SLEEP_BETWEEN_DOWNLOAD);
            continue;
        }

        /*step3:send the dummy data. move the dummy data sending follow firmware.*/
        /*step4:get the cdone gpio to judge if firmware success.*/
        if(INVALID_CDONE_GPIO != plat_data->cdone_gpio) {
            ret = ice40_firmware_cdone();
            if(!ret) {
                hwlog_info("FPGA:firmware cdone fail\n");
                if(MAX_DOWNLOAD_TIMES/2 == i) {
                    ret = ice40_set_cs_callback(NORMAL_RATE, plat_data->spi_cs_gpio);
                    if(ret) {
                        hwlog_err("%s vice40_set_cs_callback fail\n", __func__);
                        return FAIL;
                    }
                }
                msleep(SLEEP_BETWEEN_DOWNLOAD);
                continue;
            }else {
                hwlog_info("FPGA:firmware download successfully!\n");
                break;
            }
        }

        ret = check_valid_version();
        hwlog_err("%s check_valid_version = %d \n", __func__, ret);
        if(ret) {
            hwlog_info("FPGA:firmware version fail!\n");
            msleep(SLEEP_BETWEEN_DOWNLOAD);
            continue;
        }else{
            hwlog_info("FPGA:firmware download successfully!\n");
            break;
        }
    }
    wake_unlock(&spi_write_lock);

    mutex_unlock(&drv_data->fpga_download_mutex);
    if(i == MAX_DOWNLOAD_TIMES){
        download_err = DOWNLOAD_ERR;
        fpga_notify_exception(DOWNLOAD_ERR);
        return FAIL;
    }
    download_err = NO_ERR;
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
    set_hw_dev_flag(DEV_SPI_FPGA);
#endif
    return SUCCESS;
}

static void fpga_download_work(struct work_struct *work)
{
    int ret = FAIL;
    int irq = -1;
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return;
    }

    plat_data = &drv_data->plat_data;
    ret = ice40_dir_download_firmware(ice40_bin_dir, BOOT_RATE);
    if(ret){
        hwlog_err("%s firmware error through ice40_download_firmware!\n", __func__);
        return;
    }
    hwlog_info("%s: firmware download success!\n", __func__);

    ret = gpio_request(plat_data->crc_gpio, DRIVER_NAME "(fpga_crc)");
    if(ret < 0){
        hwlog_err("%s: %d fail to requset  crc_gpio gpio %d ret =%d!\n", __func__, __LINE__, plat_data->crc_gpio, ret);
        return;
    }

    ret = gpio_direction_input(plat_data->crc_gpio);
    if (ret < 0) {
        hwlog_err("%s: bt_host_wake gpio_direction_input failed\n", __func__);
        return;
    }

    irq = gpio_to_irq(plat_data->crc_gpio);
    if(irq < 0) {
        hwlog_err("%s: %d gpio_to_irq irq = %d!\n", __func__, __LINE__, irq);
        return;
    }

    if(plat_data->crc_gpio > NORMAL_GPIO_MAX){
        //ret = request_threaded_irq (irq, NULL, fpga_exception_callback, IRQF_TRIGGER_FALLING, DRIVER_NAME "(fpga_crc)", NULL);
        //if (ret) {
        //    hwlog_err("%s: %d fail to request irq for CRC_Result!\n", __func__, __LINE__);
        //}
    }else {
        ret = request_irq(irq, fpga_exception_callback, IRQF_TRIGGER_FALLING, DRIVER_NAME "(fpga_crc)", NULL);
        if (ret < 0) {
            hwlog_err("%s: %d fail to request irq for CRC_Result ret = %d!\n", __func__, __LINE__, ret);
        }
    }
}
/*
*Now, there are two mode of download. Up level could send the ice40 image context or the file dir.
*
*/
static ssize_t store_ice40bin_dir(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int ret = 0;
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    plat_data = &drv_data->plat_data;
    if(!buf) {
        hwlog_err("store_ice40bin buf is null!\n");
        return ret;
    }
    download_err = DOWNLOAD_ERR;
    if(!strncasecmp(buf,ICE40_IMAGE_FILE_DIR, strlen(ICE40_IMAGE_FILE_DIR)) ) {
        if(count > ICE40_IMAGE_FILEPAHT_LENTH) {
             hwlog_err("%s wrong file path len %d!\n", __func__, count);
            return count;
        }
        ret = sscanf(buf, "%s",ice40_bin_dir );
    } else {
        snprintf(ice40_bin_dir, ICE40_IMAGE_FILEPAHT_LENTH - 1, "%s%s", ICE40_IMAGE_FILE_DIR, plat_data->ice40_pre_image_filename);
    }

    hwlog_info("%s sscanf ice40_bin_dir = %s\n", __func__, ice40_bin_dir);
    queue_work(download_q, &download_work);
    return count;
}

static ssize_t show_download_result(struct device *pdev, struct device_attribute *attr, char *buf)
{
    if(download_err == NO_ERR)
        return snprintf(buf, STR_RETURN_LEN, "DOWNLOAD SUCCESS\n");
    else
        return snprintf(buf, STR_RETURN_LEN, "DOWNLOAD FAIL\n");
}

static int get_image_version(char *buf)
{
    int ret = 0;
    int i = 0, j = 0;
    char read_version[SPI_DATA_LEN];
    char indata[SPI_DATA_LEN];
    char *offset = NULL;
    fpga_plat_data *plat_data = NULL;
    fpga_data *drv_data =NULL;

    drv_data = get_fpga_data();
    if(!drv_data) {
        snprintf(buf, SPI_DATA_LEN, "ERROR");
        hwlog_err("%s drv_data is NULL!\n", __func__);
        return SPI_OUTPUT_DATA_LEN;
    }
    plat_data = &drv_data->plat_data;
    memset(read_version, 0, SPI_DATA_LEN);
    memset(indata, 0, SPI_DATA_LEN);
    indata[0] = FPGA_READ;
    indata[1] = FPGA_REGISTER_VERSION;
    indata[2] = 0;

    ice40_set_cs_callback(NORMAL_RATE, plat_data->spi_cs_gpio);
    for(i = 0; i < RETRY_TIME; i++) {
        offset = buf;
        ret = ice40_data_spi_write_then_read(indata, SPI_DATA_LEN, read_version, SPI_DATA_LEN);
        if(ret) {
            hwlog_err("%s read version fail!\n", __func__);
            return SPI_OUTPUT_DATA_LEN;
        }
        for(j = 3; j < SPI_DATA_LEN; j++){
            ret = snprintf(offset, SPI_OUTPUT_DATA_LEN, "%02x", read_version[j]);
            if(ret < 0) {
                hwlog_err("%s snprintf errror!\n", __func__);
                return SPI_OUTPUT_DATA_LEN;
            }
            offset += ret;
        }

        if(!strncasecmp(buf,INVALID_VERSION1 , SPI_OUTPUT_DATA_LEN) || !strncasecmp(buf,INVALID_VERSION2 , SPI_OUTPUT_DATA_LEN) ) {
            hwlog_err("%s check_valid_version = %d, get version %s \n", __func__, ret, buf);
            msleep(10);
            continue;
        }else{
            hwlog_info("FPGA:read version register successfully!\n");
            break;
        }
    }
    return SPI_OUTPUT_DATA_LEN;
}

static ssize_t show_version(struct device *pdev, struct device_attribute *attr, char *buf)
{
    return get_image_version(buf);
}

int check_input_exc(const char *inputdata, const char *outputdata)
{
    int i = 0, j = 0;
    int ret = -1;
    char *offset = NULL;
    char buf[SPI_OUTPUT_DATA_LEN + 1] = {0};
    unsigned char indata[SPI_DATA_LEN];
    char outdata[SPI_OUTPUT_DATA_LEN];
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if ((inputdata == NULL) ||(outputdata == NULL)) {
        hwlog_err("%s data is null.\n", __func__);
        return FAIL;
    }
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    for(i = 0; i < RETRY_TIME; i++){
        plat_data = &drv_data->plat_data;
        kstrtoint(inputdata, BASE_BINARY, &ret);
        hwlog_info("%s ret = %d\n", __func__, ret);
        memset(indata, 0, SPI_DATA_LEN);
        indata[0] = FPGA_WRITE;
        indata[1] = FPGA_REGISTER_TESTMODE;
        indata[3] = FPGA_TESTMODE_WRITE_REGISTER;
        indata[SPI_DATA_LEN - 3] = ((ret>>BYTE_PER_COUNT*2) & 0x07);
        indata[SPI_DATA_LEN - 2] = ((ret>>BYTE_PER_COUNT) & 0xff);
        indata[SPI_DATA_LEN - 1] = (ret & 0xff);

        ice40_set_cs_callback(NORMAL_RATE, plat_data->spi_cs_gpio);
        ret = ice40_data_spi_write(indata, SPI_DATA_LEN);
        if(ret) {
            hwlog_err("%s write testmode register fail!\n", __func__);
            continue;
        }

        msleep(1);
        offset = buf;
        memset(indata, 0, SPI_DATA_LEN);
        memset(outdata, 0, SPI_OUTPUT_DATA_LEN);
        indata[0] = FPGA_READ;
        indata[1] = FPGA_REGISTER_TESTMODE;
        indata[2] = 0;

        ret = ice40_data_spi_write_then_read(indata, SPI_DATA_LEN, outdata, SPI_DATA_LEN);
        if(ret) {
            hwlog_err("%s read testmode register fail!\n", __func__);
            return FAIL;
        }
        for(j = 3; j < SPI_DATA_LEN; j++){
            ret = snprintf(offset, SPI_OUTPUT_DATA_LEN, "%02x", outdata[j]);
            if(ret < 0) {
                hwlog_err("%s snprintf errror!\n", __func__);
                return FAIL;
            }
            offset += ret;
        }

        ret = snprintf(offset, SPI_OUTPUT_DATA_LEN, "\n");

        if(simple_strtoul(buf ,NULL, BASE_HEX) == simple_strtoul(outputdata, NULL, BASE_HEX)) {
            hwlog_info("%s Output is correct: inputdata = %s; expect outputdata = %s;return data = %s\n", __func__, inputdata, outputdata, buf);
            return SUCCESS;
        } else {
            hwlog_err("%s Output is error: inputdata = %s;expect outputdata = %s;return data = %s\n", __func__, inputdata, outputdata, buf);
            msleep(10);
            continue;
        }
    }
    return FAIL;
}

int scan_fpga_table(table_data *ice40_table, int size)
{
    int ret = SUCCESS;
    int i;

    for(i = 0; i < size; i++) {
        hwlog_info("%s The %d time test \n", __func__, i);
        ret = check_input_exc(ice40_table[i].inputdata, ice40_table[i].outputdata);
        if(ret) {
            hwlog_err("%s FAIL!\n", __func__);
            return FAIL;
        }
    }
    hwlog_info("%s SUCCESS!\n", __func__);
    return SUCCESS;
}

static char* check_str_value(char* pbuff)
{
    int i;
    int len = strlen(pbuff);

    for (i=0; i < len; i++) {
        if(isxdigit(pbuff[i])) {
            return (pbuff + i);
        }
     }
    return NULL;
}

static char* find_char_and_copy(char* srcStr, char dstChr, char* pSoure, int lenth)
{
    int lenStr = 0;
    char* tempStr = NULL;

    if(NULL == srcStr || NULL == pSoure) {
        hwlog_err("%s srcStr or pSoure is null\n", __func__);
        goto str_err;
    }

    if((tempStr = strchr(srcStr, dstChr)) != NULL) {
        lenStr = tempStr - srcStr;
        if (lenStr > lenth) {
            hwlog_err("%s str lenth over lenth\n", __func__);
            goto str_err;
        }
        strncpy(pSoure, srcStr, lenStr);
    } else {
        hwlog_err("%s txt file input data is not right\n", __func__);
        goto str_err;
    }

    return  tempStr;

    str_err:
        return NULL;
}

static int scan_and_copy(char** pStr, char dstChr, char* pSoure, int lenth)
{
    char* temp;
    char* string_add;

    string_add = check_str_value(*pStr);
    if(NULL == string_add) {
        return FPGA_DONE;
    }

    temp = find_char_and_copy(string_add, dstChr, pSoure, lenth);
    if(NULL == temp) {
        hwlog_err("%s input data length (%d) not right \n", __func__);
        return FPGA_ERR;
    }
    *pStr = temp;
    return FPGA_SUCCESS;
}

static int fpga_scan(char* string_org, int len)
{
    table_data *ice40_table;
    int index_talbe =0;
    char* temp = string_org;
    int ret = 0;

    ice40_table = kmalloc(FPGA_TALBE_FILE_SIZE, GFP_KERNEL);
    if (!ice40_table) {
        hwlog_err("%s can't allocate memory for fpga scan table ", __func__);
        return FAIL;
    }

    memset(ice40_table, 0, FPGA_TALBE_FILE_SIZE);

    while(temp) {
        ret = scan_and_copy(&temp, INPUT_FLAG_CHAR, ice40_table[index_talbe].inputdata, FPGA_TALBE_INPUT_LEN - 1);
        if (ret == FPGA_DONE) {
            break;
        }
        else if (ret == FPGA_ERR) {
            hwlog_err("%s txt file input format is not right \n", __func__);
            kfree(ice40_table);
            return FAIL;
        }
        ret = scan_and_copy(&temp, OUTPUT_FLAG_CHAR, ice40_table[index_talbe].outputdata, FPGA_TALBE_OUTPUT_LEN -1);
        if (ret == FPGA_DONE) {
            break;
        }
        if (ret == FPGA_ERR) {
            hwlog_err("%s txt file output format is not right \n", __func__);
            kfree(ice40_table);
            return FAIL;
        }
        index_talbe ++;
    }

    ret = scan_fpga_table(ice40_table, index_talbe);
    kfree(ice40_table);
    return ret;
}

static ssize_t input_scan_talbe(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    char ice40_bin_table_path[ICE40_IMAGE_FILEPAHT_LENTH];
    char *txt_str = ".txt";
    char *bin_str = ".bin";
    int len = 0, ret = 0;
    char * bin_path = ice40_bin_dir;
    char *stemp = strstr(ice40_bin_dir, bin_str);
    char *ice40_table = NULL;
    mm_segment_t oldfs = get_fs();
    struct file *fp = NULL;
    int file_size, one_size, left;
    loff_t pos;

    memset(ice40_bin_table_path, '\0', ICE40_IMAGE_FILEPAHT_LENTH);
    len = stemp - bin_path;
    strncpy(ice40_bin_table_path, ice40_bin_dir, len );
    strncpy(ice40_bin_table_path + len, txt_str, strlen(txt_str));
    hwlog_err("%s ice40_bin_table_path = %s!\n", __func__, ice40_bin_table_path);

    set_fs(KERNEL_DS);
    fp = filp_open(ice40_bin_table_path, O_RDONLY, 755);
    if (IS_ERR_OR_NULL(fp)) {
        hwlog_err("%s open file %s error\n", __func__, ice40_bin_table_path);
        set_fs(oldfs);
        return count;
    }
    file_size =(int)(vfs_llseek(fp, 0L, SEEK_END));
    hwlog_err("%s table.. size=0x%x\n", __func__, file_size);
    ice40_table = __get_free_pages(GFP_KERNEL|GFP_DMA, get_order(file_size+1));

    vfs_llseek(fp, 0L, SEEK_SET);
    pos = fp->f_pos;
    ret = vfs_read(fp, (char *)ice40_table, file_size, &pos);
    if (ret < 0) {
        hwlog_err("%s vfs read error %d\n", __func__, ret);
    }
    ice40_table[file_size] = '\0';
    ret = fpga_scan(ice40_table, file_size+1);
    if(ret) {
        scan_table_error = SCAN_TABLE_ERR;
        fpga_notify_exception(SCAN_TABLE_ERR);
    } else {
        scan_table_error = NO_ERR;
    }
    free_pages((unsigned long)ice40_table,  get_order(file_size));
    return count;
}

static ssize_t show_scan_result(struct device *pdev, struct device_attribute *attr, char *buf)
{
    if(scan_table_error == NO_ERR) {
        return snprintf(buf, STR_RETURN_LEN, "SUCCESS\n");
    }else {
        return snprintf(buf, STR_RETURN_LEN, "FAIL\n");
    }
}

static ssize_t show_exception(struct device *pdev, struct device_attribute *attr, char *buf)
{
    if(download_err == NO_ERR) {
        return snprintf(buf, STR_RETURN_LEN, "DOWNLOAD SUCCESS\n");
    }else {
        return snprintf(buf, STR_RETURN_LEN, "DOWNLOAD FAIL\n");
    }
}

static ssize_t show_cdone(struct device *pdev, struct device_attribute *attr, char *buf)
{
    fpga_data *drv_data = get_fpga_data();
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    int gpio_value = 0;
    int cdone = drv_data->plat_data.cdone_gpio;
    /* cdone pin disconnected */
    if(INVALID_CDONE_GPIO==cdone){
        if(NO_ERR == download_err){
            hwlog_info("%s: antennafpga firmware download successfully!\n", __func__);
            gpio_value = 1;
        }
        else{
            hwlog_err("%s: antennafpga firmware download failed, download_err = %d!\n", __func__, download_err);
            gpio_value = 0;
        }
    }
    /* cdone pin connected */
    else{
        gpio_value = gpio_get_value(cdone);
    }

    return snprintf(buf, PAGE_SIZE, "%d\n", gpio_value);
}

static ssize_t show_reset(struct device *pdev, struct device_attribute *attr, char *buf)
{
    fpga_data *drv_data = get_fpga_data();
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    int reset = drv_data->plat_data.reset_gpio;
    int gpio_value= gpio_get_value(reset);
    return snprintf(buf, PAGE_SIZE, "%d", gpio_value);
}

static ssize_t set_reset(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    fpga_data *drv_data = get_fpga_data();
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return count;
    }
    int reset = drv_data->plat_data.reset_gpio;

    if(buf[0] == '0') {
        gpio_direction_output(reset, 0);
    }else if (buf[0] == '1') {
        gpio_direction_output(reset, 1);
    }else {
        hwlog_err("%s Wrong input!\n", __func__);
    }

    return count;
}

static ssize_t show_spics(struct device *pdev, struct device_attribute *attr, char *buf)
{
    fpga_data *drv_data = get_fpga_data();
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    int cs = drv_data->plat_data.spi_cs_gpio;
    int gpio_value= gpio_get_value(cs);
    return snprintf(buf, PAGE_SIZE, "%d\n", gpio_value);
}

static ssize_t show_preimagename(struct device *pdev, struct device_attribute *attr, char  __user *buf)
{
    fpga_data *drv_data = get_fpga_data();
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    fpga_plat_data *plat_data = NULL;
    plat_data = &drv_data->plat_data;
    return snprintf(buf, PRE_ICE40_IMAGE_FILENAME, plat_data->ice40_pre_image_filename);
}

static int hexTou16(const unsigned char *indata, int len)
{
   int value = 0, i = 0, j = 1;

   for(i=len -1; i >= 0; i--) {
       if(indata[i] == '1'){
           value =  value + j;
       }
       j = j *2;
   }
   return value;
}

static ssize_t set_testmode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int ret = 0;
    unsigned char indata[SPI_DATA_LEN] = {0};
    unsigned char input_address[TEST_MODE_INPUT_LEN] = {0};
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return count;
    }
    plat_data = &drv_data->plat_data;
    ret = sscanf(buf, "%s",input_address );
    kstrtoint(input_address, BASE_BINARY, &ret);
    hwlog_info("%s ret = %d\n", __func__, ret);
    memset(indata, 0, SPI_DATA_LEN);
    indata[0] = FPGA_WRITE;
    indata[1] = FPGA_REGISTER_TESTMODE;
    indata[2] = 0;
    indata[3] = FPGA_TESTMODE_WRITE_REGISTER;
    indata[SPI_DATA_LEN - 3] = ((ret>>BYTE_PER_COUNT*2) & 0x07);
    indata[SPI_DATA_LEN - 2] = ((ret>>BYTE_PER_COUNT) & 0xff);
    indata[SPI_DATA_LEN - 1] = (ret & 0xff);

    ice40_set_cs_callback(NORMAL_RATE, plat_data->spi_cs_gpio);
    ret = ice40_data_spi_write(indata, SPI_DATA_LEN);
    if(ret) {
        hwlog_err("%s read version fail!\n", __func__);
    }
    return count;
}

static ssize_t show_testmode(struct device *pdev, struct device_attribute *attr, char *buf)
{
    int ret = 0;
    int i = 0;
    char indata[SPI_DATA_LEN];
    char outdata[SPI_DATA_LEN];
    char *offset = NULL;
    fpga_plat_data *plat_data = NULL;
    fpga_data *drv_data = get_fpga_data();
    offset = buf;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return SPI_OUTPUT_DATA_LEN;
    }
    plat_data = &drv_data->plat_data;

    ice40_set_cs_callback(NORMAL_RATE, plat_data->spi_cs_gpio);
    memset(indata, 0, SPI_DATA_LEN);
    memset(outdata, 0, SPI_DATA_LEN);
    indata[0] = FPGA_READ;
    indata[1] = FPGA_REGISTER_TESTMODE;
    indata[2] = 0;

    ret = ice40_data_spi_write_then_read(indata, SPI_DATA_LEN, outdata, SPI_DATA_LEN);
    if(ret) {
        hwlog_err("%s read version fail!\n", __func__);
        return SPI_OUTPUT_DATA_LEN;
    }

    for(i = 3; i < SPI_DATA_LEN; i++ ){
        ret = snprintf(offset, FPGA_TALBE_OUTPUT_LEN - ret, "%02X", outdata[i]);
        if(ret < 0) {
            hwlog_err("%s snprintf errror, i + %d!\n", __func__, i);
            return SPI_OUTPUT_DATA_LEN;
        }
        offset += ret;
    }
    ret = snprintf(offset, FPGA_TALBE_OUTPUT_LEN - ret, "\n");
    return FPGA_TALBE_OUTPUT_LEN;
}

static ssize_t show_gpio_crc(struct device *pdev, struct device_attribute *attr, char *buf)
{
    fpga_data *drv_data = get_fpga_data();
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    int crc_gpio = drv_data->plat_data.crc_gpio;
    int gpio_value= gpio_get_value(crc_gpio);
    return snprintf(buf, STR_RETURN_LEN, "%d", gpio_value);
}

static ssize_t show_download_times(struct device *pdev, struct device_attribute *attr, char *buf)
{
    return snprintf(buf, STR_RETURN_LEN, "%d", fpga_download_times);
}

static DEVICE_ATTR(ice40bin_download_dir, S_IRUGO |S_IWUSR, show_download_result, store_ice40bin_dir);
static DEVICE_ATTR(ice40bin_version,  S_IRUGO, show_version, NULL);
static DEVICE_ATTR(ice40bin_scan_fpga_table,  0660, show_scan_result, input_scan_talbe);
static DEVICE_ATTR(ice40bin_fpga_exception,  S_IRUGO , show_exception, NULL);
static DEVICE_ATTR(cdone,  S_IRUGO , show_cdone, NULL);
static DEVICE_ATTR(reset,  S_IRUGO |S_IWUSR , show_reset, set_reset);
static DEVICE_ATTR(spics,  S_IRUGO , show_spics, NULL);
static DEVICE_ATTR(crc,  S_IRUGO , show_gpio_crc, NULL);
static DEVICE_ATTR(preimagename,  S_IRUGO , show_preimagename, NULL);
static DEVICE_ATTR(testmode,  S_IRUGO |S_IWUSR , show_testmode, set_testmode);
static DEVICE_ATTR(download_times,  S_IRUGO , show_download_times, NULL);

static struct attribute *download_times_attributes[] = {
        &dev_attr_download_times.attr,
        NULL
};

static const struct attribute_group download_times_attr_group = {
        .attrs = download_times_attributes,
};

static struct attribute *crc_attributes[] = {
        &dev_attr_crc.attr,
        NULL
};

static const struct attribute_group crc_attr_group = {
        .attrs = crc_attributes,
};

static struct attribute *testmode_attributes[] = {
        &dev_attr_testmode.attr,
        NULL
};

static const struct attribute_group testmode_attr_group = {
        .attrs = testmode_attributes,
};

static struct attribute *preimagename_attributes[] = {
        &dev_attr_preimagename.attr,
        NULL
};

static const struct attribute_group preimagename_attr_group = {
        .attrs = preimagename_attributes,
};

static struct attribute *cdone_attributes[] = {
        &dev_attr_cdone.attr,
        NULL
};

static const struct attribute_group cdone_attr_group = {
        .attrs = cdone_attributes,
};

static struct attribute *reset_attributes[] = {
        &dev_attr_reset.attr,
        NULL
};

static const struct attribute_group reset_attr_group = {
        .attrs = reset_attributes,
};
static struct attribute *spics_attributes[] = {
        &dev_attr_spics.attr,
        NULL
};

static const struct attribute_group spics_attr_group = {
        .attrs = spics_attributes,
};

static struct attribute *ice40bin_download_dir_attributes[] = {
        &dev_attr_ice40bin_download_dir.attr,
        NULL
};

static const struct attribute_group ice40bin_download_dir_attr_group = {
        .attrs = ice40bin_download_dir_attributes,
};

static struct attribute *ice40bin_version_attributes[] = {
        &dev_attr_ice40bin_version.attr,
        NULL
};

static const struct attribute_group ice40bin_version_attr_group = {
        .attrs = ice40bin_version_attributes,
};

static struct attribute *ice40bin_scan_fpga_table_attributes[] = {
        &dev_attr_ice40bin_scan_fpga_table.attr,
        NULL
};

static const struct attribute_group ice40bin_scan_fpga_table_attr_group = {
        .attrs = ice40bin_scan_fpga_table_attributes,
};

static struct attribute *ice40bin_fpga_exception_attributes[] = {
        &dev_attr_ice40bin_fpga_exception.attr,
        NULL
};

static const struct attribute_group ice40bin_fpga_exception_attr_group = {
        .attrs =ice40bin_fpga_exception_attributes,
};

static struct platform_device fpga_ice40_dev = {
    .name = "antennafpga",
};

static int fpga_ice40_remove(struct platform_device *dev)
{
    hwlog_info("called remove %s\n", __func__);
    return 0;
}

static int create_system_group()
{
    int ret;
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &ice40bin_download_dir_attr_group);
    if (ret){
        hwlog_err("Error creating ice40bin_download_dir_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &ice40bin_version_attr_group);
    if (ret){
        hwlog_err("Error creating ice40bin_version_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &ice40bin_scan_fpga_table_attr_group);
    if (ret){
        hwlog_err("Error creating ice40bin_version_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &ice40bin_fpga_exception_attr_group);
    if (ret){
        hwlog_err("Error creating ice40bin_version_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &cdone_attr_group);
    if (ret){
        hwlog_err("Error creating cdone_attr_group sysfs entries\n");
        return FAIL;
    }
        ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &reset_attr_group);
    if (ret){
        hwlog_err("Error creating reset_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &spics_attr_group);
    if (ret){
        hwlog_err("Error creating spics_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &preimagename_attr_group);
    if (ret){
        hwlog_err("Error creating preimagename_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &testmode_attr_group);
    if (ret){
        hwlog_err("Error creating testmode_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &crc_attr_group);
    if (ret){
        hwlog_err("Error creating crc_attr_group sysfs entries\n");
        return FAIL;
    }
    ret =  sysfs_create_group(&fpga_ice40_dev.dev.kobj, &download_times_attr_group);
    if (ret){
        hwlog_err("Error creating download_times_attr_group sysfs entries\n");
        return FAIL;
    }

    return SUCCESS;
}

static int fpga_ice40_regulator_config(struct device *dev)
{
    struct regulator *fpga_vcc;
    int rc = 0;
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    plat_data = &drv_data->plat_data;

    if(0 == strlen(plat_data->ice40_fpga_vccio0))
    {
        /* the length is 0 means device-tree not config vccio0,no need to deal with vccio0. */
        hwlog_info("%s pmic vccio0 is not cofig, not need deal with vccio0.\n", __func__);
        return SUCCESS;
    }

    fpga_vcc = regulator_get(dev, plat_data->ice40_fpga_vccio0);
    if (IS_ERR(fpga_vcc)) {
        rc = PTR_ERR(fpga_vcc);
        hwlog_err("%s: regulator get failed rc=%d\n", __func__, rc);
        return FAIL;
    }
    rc = regulator_enable(fpga_vcc);
    if (rc) {
        pr_info("%s: regulator vcc_i2c enable failed rc=%d\n", __func__, rc);
        return FAIL;
    }
    return SUCCESS;
}

static int fpga_ice40_get_dts_config(struct fpga_plat_data *plat_data)
{
    int ret = 0;
    struct device_node *np = NULL;
    const char *p_string = NULL;

    hwlog_info("%s start...\n", __func__);
    np = of_find_compatible_node(NULL, NULL, "antenna_fpga");
    /*First, CDONE GPIO.*/
    plat_data->cdone_gpio = of_get_named_gpio(np, "antenna_fpga,gpio-cdone", 0);
    hwlog_info("%s get gpio-cdone gpio %d\n", __func__, plat_data->cdone_gpio);
    if(GPIO_OEM_VALID(plat_data->cdone_gpio) && INVALID_CDONE_GPIO != plat_data->cdone_gpio){
        ret = gpio_request(plat_data->cdone_gpio, DRIVER_NAME "(fpga_cdone)");
        if(ret < 0){
            hwlog_err("%s: %d fail to requset  cdone gpio %d ret =%d!\n", __func__, __LINE__, plat_data->cdone_gpio, ret);
            goto err_req_irq_cdone;
        }
        if (gpio_direction_input(plat_data->cdone_gpio))
            hwlog_err("probe - cdone_gpio direction input error");
    }
    /*Second, CRC_Result GPIO.*/
    plat_data->crc_gpio = of_get_named_gpio(np, "antenna_fpga,gpio-exception", 0);
    hwlog_info(" %s get gpio-exception %d\n", __func__, plat_data->crc_gpio );
    if(!GPIO_OEM_VALID(plat_data->crc_gpio)){
        goto err_req_irq_crc;
    }
    /*Third, FPGA reset GPIO.*/
    plat_data->reset_gpio = of_get_named_gpio(np, "antenna_fpga,gpio-reset", 0);
    hwlog_info("%s get gpio-reset gpio %d\n", __func__, plat_data->reset_gpio );
    if(GPIO_OEM_VALID(plat_data->reset_gpio)){
        ret = gpio_request(plat_data->reset_gpio, DRIVER_NAME "(fpga_reset)");
        if(ret < 0){
            hwlog_err("%s: %d fail to requset  reset_gpio gpio %d ret =%d!\n", __func__, __LINE__, plat_data->reset_gpio, ret);
            goto err_req_irq_rst;
        }
    }
    /*Fourth, FPGA spi cs GPIO.*/
    plat_data->spi_cs_gpio = of_get_named_gpio(np, "antenna_fpga,gpio-cs", 0);
    hwlog_info("%s get fpga_spi_cs gpio %d\n", __func__, plat_data->spi_cs_gpio );
    if(GPIO_OEM_VALID(plat_data->spi_cs_gpio)){
        ret = gpio_request(plat_data->spi_cs_gpio, DRIVER_NAME "(fpga_spi_cs)");
        if(ret < 0){
            hwlog_err("%s: %d fail to requset  cs_gpio gpio %d ret =%d!\n", __func__, __LINE__, plat_data->spi_cs_gpio, ret);
            goto err_req_irq_spi_cs;
        }
        g_spi_fpga_cs_gpio = plat_data->spi_cs_gpio;
    }
    /*Fifth, read pre-image-filename from dts.*/
    ret = of_property_read_string(np, "antenna_fpga,pre-image-filename", &p_string);
    if(ret < 0 || strlen(p_string) > PRE_ICE40_IMAGE_FILENAME) {
        hwlog_err("%s: %d fail to pre-image-filename!\n", __func__, __LINE__);
        goto err_get_pre_image_filename;
    }
    strncpy(plat_data->ice40_pre_image_filename, p_string, strlen(p_string));
    hwlog_info("antenna_fpga,pre-image-filename = %s\n", plat_data->ice40_pre_image_filename);

    /*sixth, read power control flag from dts.*/
    ret = of_property_read_u32(np, "antenna_fpga,power-disable",&(plat_data->power_disable));
    if((0 == ret) && (1 == plat_data->power_disable))
    {
        /* if power-disable is 1, means no need software control vccio0 */
        hwlog_info("antenna_fpga,power-disable = %d\n", plat_data->power_disable);
    }
    else
    {
        /* if power-disable is not 1 or not config this proprietary, get vccio0 dts config */
        ret = of_property_read_string(np, "antenna_fpga,vccio0", &p_string);
        if(ret < 0 || strlen(p_string) > ICE40_VCCIO0_STR) {
            hwlog_err("%s: %d fail to vccio0 str!\n", __func__, __LINE__);
            goto err_get_vccio0_str;
        }
        strncpy(plat_data->ice40_fpga_vccio0, p_string, strlen(p_string));
        hwlog_info("antenna_fpga,pre-vccio0-filename = %s\n", plat_data->ice40_fpga_vccio0);
    }
    return SUCCESS;

err_get_vccio0_str:
err_get_pre_image_filename:
    if(GPIO_OEM_VALID(plat_data->spi_cs_gpio)){
        gpio_free(plat_data->spi_cs_gpio);
    }
err_req_irq_spi_cs:
    if(GPIO_OEM_VALID(plat_data->reset_gpio)){
        gpio_free(plat_data->reset_gpio);
    }
err_req_irq_rst:
err_req_irq_crc:
    if(GPIO_OEM_VALID(plat_data->crc_gpio)){
        free_irq(gpio_to_irq(plat_data->crc_gpio), NULL);
    }
 err_req_irq_cdone:
    return FAIL;
}

static  int fpga_ice40_dmd_register()
{
   if (!fpga_ice40_dclient) {
        fpga_ice40_dclient = dsm_register_client(&fpga_ice40);
        if(!fpga_ice40_dclient){
            hwlog_err("dsm_register_client failed\n");
            return FAIL;
        }
    }
    return SUCCESS;
}

static int fpga_ice40_wakelock_init()
{
    wake_lock_init(&spi_write_lock, WAKE_LOCK_SUSPEND, "fpga_spi_write_wake_lock");
    return SUCCESS;
}

static int fpga_ice40_work_init()
{
    INIT_WORK(&exception_callback_work, fpga_exception_work);
    exception_callback_q = create_singlethread_workqueue("fpga_exception_queue");
    if (exception_callback_q == NULL) {
        hwlog_err( "%s: exception_callback_q is NULL\n", __func__);
        return FAIL;
    }

    INIT_WORK(&download_work, fpga_download_work);
    download_q = create_singlethread_workqueue("fpga_download_queue");
    if (download_q == NULL) {
        hwlog_err( "%s: download_q is NULL\n", __func__);
        return FAIL;
    }
    return SUCCESS;
}

int fpga_ice40_probe(struct platform_device *pdev)
{
    int ret = 0;
    fpga_data *drv_data = NULL;
    fpga_plat_data *plat_data = NULL;

    hwlog_info("%s date:1102", __func__);
    /* step 1: alloc driver data struct */
    drv_data = kmalloc(sizeof(*drv_data), GFP_KERNEL);
    if (!drv_data) {
        hwlog_err("probe - can not alloc driver data\n");
        goto err_data_alloc;
    }
    memset(drv_data, 0, sizeof(*drv_data));
    plat_data = &drv_data->plat_data;
    /*step 2: Configure gpio, and get irq*/
    ret = fpga_ice40_get_dts_config(plat_data);
    if(ret) {
         hwlog_err("fpga_ice40_get_dts_config error!\n");
         goto err_get_dts_config;
    }
    /*step3:register device*/
    ret = platform_device_register(&fpga_ice40_dev);
    if (ret) {
        hwlog_err( "%s: platform_device_register failed, ret:%d.\n", __func__, ret);
        goto err_register_platform_device;
    }
    ret =  create_system_group();
    if (ret) {
        hwlog_err( "%s: create group failed, ret:%d.\n", __func__, ret);
        goto err_create_sysfs_entries;
    }
    /*step4: set dev*/
    fpga_drv_data = drv_data;

    /*step5: dmd register.*/
    ret = fpga_ice40_dmd_register();
    if(ret) {
        hwlog_err( "%s: dmd register failed, ret:%d.\n", __func__, ret);
    }
    /*step6: init wakelock.*/
    ret = fpga_ice40_wakelock_init();
    if (ret) {
        hwlog_err( "%s: wakelock int failed, ret:%d.\n", __func__, ret);
        goto err_wakelock_init;
    }

    /*step7: enable vccio0*/
    ret = fpga_ice40_regulator_config(&pdev->dev);
    if(ret) {
        hwlog_err( "%s: fpga_ice40_regulator_config , ret:%d.\n", __func__, ret);
        goto err_regulatro_config;
    }
    /*step 8: work init*/
    ret = fpga_ice40_work_init();
    if(ret) {
        hwlog_err( "%s: fpga_ice40_work_init failed, ret:%d.\n", __func__, ret);
        goto err_work_init;
    }
    /*step 9: mutex init*/
    mutex_init(&drv_data->fpga_download_mutex);
    /*step 10: cs init*/
    gpio_direction_output(plat_data->spi_cs_gpio, 1);
    return SUCCESS;
err_work_init:
err_regulatro_config:
err_wakelock_init:
err_create_sysfs_entries:
    platform_device_unregister(&fpga_ice40_dev);
err_register_platform_device:
err_get_dts_config:
    kfree(drv_data);
err_data_alloc:
    return FAIL;
}

static const struct of_device_id fpga_ice40_match_table[] = {
    {
        .compatible = "antenna_fpga",
        .data = NULL,
    },
    {
    },
};

MODULE_DEVICE_TABLE(of, fpga_ice40_match_table);

static struct platform_driver fpga_ice40_driver = {
    .probe = fpga_ice40_probe,
    .remove = fpga_ice40_remove,
    .driver = {
        .name = "antenna_fpga",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(fpga_ice40_match_table),
    },

};

static int __init fpga_ice40__init(void)
{
    int err = 0;
    err = platform_driver_register(&fpga_ice40_driver);
    if (err){
        hwlog_err("FPGA__ %s fpga_ice40__init.\n", __func__);
    }

    return err;
}

static void __exit fpga_ice40__exit(void)
{
    fpga_data *drv_data = get_fpga_data();
    fpga_plat_data *plat_data = NULL;
    if(!drv_data) {
        hwlog_err("%s drv data is null.\n", __func__);
        return FAIL;
    }
    plat_data = &drv_data->plat_data;
    platform_driver_unregister(&fpga_ice40_driver);
    if(GPIO_OEM_VALID(plat_data->spi_cs_gpio)){
        gpio_free(plat_data->spi_cs_gpio);
    }
    if(GPIO_OEM_VALID(plat_data->reset_gpio)){
        gpio_free(plat_data->reset_gpio);
    }
     if(GPIO_OEM_VALID(plat_data->crc_gpio)){
        gpio_free(plat_data->crc_gpio);
    }
    if(GPIO_OEM_VALID(plat_data->crc_gpio)){
        free_irq(gpio_to_irq(plat_data->crc_gpio), NULL);
    }
    if(exception_callback_q){
        cancel_work_sync(&exception_callback_work);
        destroy_workqueue(exception_callback_q);
    }
    if(download_q){
        cancel_work_sync(&download_work);
        destroy_workqueue(download_q);
    }
    if(drv_data)
        kfree(drv_data);
}

late_initcall(fpga_ice40__init);
module_exit(fpga_ice40__exit);
