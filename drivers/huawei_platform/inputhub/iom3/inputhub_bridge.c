/*
 *  drivers/misc/inputhub/inputhub_bridge.c
 *  Sensor Hub Channel Bridge
 *
 *  Copyright (C) 2013 Huawei, Inc.
 *  Author: huangjisong
 *
 */

#include "inputhub_bridge.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/notifier.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/wakelock.h>
#include <linux/delay.h>
#include <linux/hisi/hisi_mailbox.h>
#include <dsm/dsm_pub.h>
#include "inputhub_route.h"
#include <linux/hisi/hisi_rproc.h>

#define STARTUP_IOM3_CMD		(0x00070001)
#define RELOAD_IOM3_CMD		(0x00070301)
extern void dmd_log_report(int dmd_mark,const char * err_func,const char * err_msg);
#define REG_BASE_ADDR       (0xFFF35000)
#define IOM3RSTSTAT_ADDR    (REG_BASE_ADDR + 0x1EC)
#define PERRSTSTAT4_ADDR    (REG_BASE_ADDR + 0x098)
#define PERSTAT5_ADDR       (REG_BASE_ADDR + 0x05C)
#define IOM3CLKEN_ADDR      (REG_BASE_ADDR + 0x1E0)
//for iom3 recovery debug used
#define PERCLKEN2_ADDR    (REG_BASE_ADDR + 0x028)
#define PERRSTEN2_ADDR		(REG_BASE_ADDR + 0x078)
#define PERRSTDIS2_ADDR	(REG_BASE_ADDR + 0x07C)
#define PERRSTSTAT2_ADDR    (REG_BASE_ADDR + 0x080)
#define IOM3STAT_ADDR    (REG_BASE_ADDR + 0x1F4)

int (*api_inputhub_mcu_recv)(const char * buf,unsigned int length/*buf length*/)=0;
//called by inputhub_mcu module or test module.
extern int inputhub_route_init(void);
extern void inputhub_route_exit(void);
/*begin huangwen 20120706*/
static int isSensorMcuMode = 1; /*0:not mcu mode, Detect Sensor To AP by I2C   1:mcu mode , Detect Sensor To mcu*/

static struct notifier_block nb;
static struct completion send_complete;
#ifdef CONFIG_IOM3_RECOVERY
BLOCKING_NOTIFIER_HEAD(iom3_recovery_notifier_list);
atomic_t iom3_rec_state;
static struct delayed_work iom3_rec_work;
static struct workqueue_struct *iom3_rec_wq;
static struct wake_lock iom3_rec_wl;
static struct completion iom3_rec_done;
#endif

struct dsm_client *shb_dclient = NULL;

int getSensorMcuMode( void )
{
    return isSensorMcuMode;
}
static void setSensorMcuMode(int mode)
{
    isSensorMcuMode = mode;
}

int inputhub_mcu_recv(const char *buf, unsigned int length)
{
#ifdef CONFIG_IOM3_RECOVERY
    if(IOM3_RECOVERY_START == atomic_read(&iom3_rec_state)){
        hwlog_err("iom3 under recovery mode, ignore all recv data\n");
        return 0;
    }
#endif
    if (api_inputhub_mcu_recv != NULL) {
        return api_inputhub_mcu_recv(buf, length);
    } else {
        hwlog_err("---->error: api_inputhub_mcu_recv == NULL\n");
        dmd_log_report(DSM_SHB_ERR_READ, __func__, "---->error: api_inputhub_mcu_recv == NULL\n");
        return -1;
    }
}

//received data from mcu.
static int mbox_recv_notifier(struct notifier_block *nb, unsigned long len, void *msg)
{
/*
    int i;

    for (i = 0; i < len; ++i) {
        hwlog_info("-------->msg[%d] = %#.8x\n", i, ((int *)msg)[i]);
    }
*/
    inputhub_mcu_recv(msg, len * sizeof(int));//convert to bytes
    //send to mcu

    return 0;
}

int inputhub_mcu_connect( void )
{
    int ret = 0;
    //connect to inputhub_route
    api_inputhub_mcu_recv=inputhub_route_recv_mcu_data;//should supply an interface

    //connect to mcu
    hwlog_info("----%s--->\n",__func__);

    nb.next = NULL;
    nb.notifier_call = mbox_recv_notifier;

    /* register the rx notify callback */
    ret = RPROC_MONITOR_REGISTER(HISI_RPROC_IOM3, &nb);
    if (ret)
    	hwlog_info("%s:RPROC_MONITOR_REGISTER failed", __func__);

    return 0;
}
int inputhub_mcu_disconnect( void )
{
    RPROC_PUT(HISI_RPROC_IOM3);
    return 0;
}


static inline unsigned int read_reg32(unsigned int phy_addr)
{
    unsigned int reg32_val = 0;
    unsigned int volatile *vir_addr = (unsigned int volatile *)ioremap(phy_addr, 4);

    if (vir_addr != NULL) {
        reg32_val = *vir_addr;
        iounmap(vir_addr);
    } else {
        hwlog_err("ioremap(%u) failed in %s!\n", phy_addr, __func__);
    }

    return reg32_val;
}

static void inputhub_mcu_send_complete(rproc_msg_t *ack_buffer,
				rproc_msg_len_t ack_buffer_len,
				int error,
				void *data)
{
    complete(&send_complete);
    	
    if ((-ETIMEOUT) == error) {
        hwlog_err("send failed timeout\n");
	        if(!dsm_client_ocuppy(shb_dclient)){
                    dsm_client_record(shb_dclient, "IOM3RSTSTAT: 0x%x\n", read_reg32(IOM3RSTSTAT_ADDR));
                    dsm_client_record(shb_dclient, "PERRSTSTAT4: 0x%x\n", read_reg32(PERRSTSTAT4_ADDR));
                    dsm_client_record(shb_dclient, "PERSTAT5: 0x%x\n", read_reg32(PERSTAT5_ADDR));
                    dsm_client_record(shb_dclient, "IOM3CLKEN: 0x%x\n", read_reg32(IOM3CLKEN_ADDR));
                    dsm_client_notify(shb_dclient, DSM_SHB_ERR_IPC_TIMEOUT);
            }
    }else{
    hwlog_debug("send success\n");
    }	
    return;
}

/*extern void hisi_rdr_nmi_notify_iom3(void);*/
int sensorhub_img_dump(int type, void *buff, int size)
{
	/*hisi_rdr_nmi_notify_iom3();*/
	return 0;
}

struct dsm_client_ops sensorhub_ops = {
	.poll_state = NULL,
	.dump_func = sensorhub_img_dump,
};

static struct dsm_dev dsm_sensorhub = {
	.name = "dsm_sensorhub",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = &sensorhub_ops,
	.buff_size = 1024,
};

int inputhub_mcu_send(const char *buf, unsigned int length)
{
    mbox_msg_len_t len=0;
    int i = 0;
    int ret = -1;
    len = (length + sizeof(mbox_msg_t) - 1) / (sizeof(mbox_msg_t));

    pr_debug("inputhub_mcu_send------------->length = %d, len = %d\n", (int)length, (int)len);
    for (i = 0; i < len; i++)
        pr_debug("buf[%d] = 0x%x\n", i, buf[i]);

    INIT_COMPLETION(send_complete);

    ret = RPROC_ASYNC_SEND(HISI_RPROC_IOM3, (mbox_msg_t *)buf, len, ASYNC_MSG, inputhub_mcu_send_complete, NULL);
    if(ret)
    {
        hwlog_err("RPROC_ASYNC_SEND return %d.\n", ret);
        return -1;
    }

    wait_for_completion(&send_complete);

    return ret;
}

static int g_boot_iom3 = STARTUP_IOM3_CMD;
static void inputhub_power_on_complete(rproc_msg_t *ack_buffer,
				rproc_msg_len_t ack_buffer_len,
				int error,
				void *data)
{
	return;
}
void boot_iom3(void)
{
    int ret = 0;
    ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3, (mbox_msg_t *)&g_boot_iom3, 1, ASYNC_MSG, inputhub_power_on_complete, NULL);
    if (ret) {
        hwlog_err("RPROC_ASYNC_SEND error in %s\n", __func__);
    }
}

#ifdef CONFIG_IOM3_RECOVERY
int register_iom3_recovery_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&iom3_recovery_notifier_list, nb);
}

extern int send_fileid_to_mcu_in_recovery(void);
extern int sensor_set_cfg_data_in_recovery(void);
int iom3_rec_sys_callback(const pkt_header_t *head)
{
	int ret = 0;

	if(IOM3_RECOVERY_MINISYS == atomic_read(&iom3_rec_state)){
		if (ST_MINSYSREADY == ((pkt_sys_statuschange_req_t *)head)->status)
		{
			hwlog_info("REC sys ready mini!\n");
			ret = send_fileid_to_mcu_in_recovery();
			if(ret)
				hwlog_err("REC get sensors cfg data from dts fail,ret=%d, use default config data!\n", ret);
			else
				hwlog_info( "REC get sensors cfg data from dts success!\n");
		}else if (ST_MCUREADY == ((pkt_sys_statuschange_req_t *)head)->status)
		{
			hwlog_info("REC mcu all ready!\n");
			ret = sensor_set_cfg_data_in_recovery();
			if(ret<0)
				hwlog_err("REC sensor_chip_detect ret=%d\n", ret);
			complete(&iom3_rec_done);
		}
	}
	return 0;
}

static inline void show_iom3_stat(void)
{
	hwlog_err("PERCLKEN2:0x%x, PERRSTSTAT2:0x%x, IOM3STAT:0x%x, IOM3RSTSTAT:0x%x, IOM3CLKEN:0x%x\n",
		read_reg32(PERCLKEN2_ADDR),
		read_reg32(PERRSTSTAT2_ADDR),
		read_reg32(IOM3STAT_ADDR),
		read_reg32(IOM3RSTSTAT_ADDR),
		read_reg32(IOM3CLKEN_ADDR));
}
#if 0
#define IOM3STAT_SLEEP_MASK	(0x2)
#define WAIT_IOM3_WFI_PERIOD	(100)
static int wait_for_iom3_wfi(int timeout)
{
	int count = (timeout > 0) ? timeout : 1;
	unsigned int reg32_val = 0;
	unsigned int volatile *vir_addr = (unsigned int volatile *)ioremap(IOM3STAT_ADDR, 4);

	if (!vir_addr) {
		hwlog_err("ioremap IOM3STAT_ADDR failed\n");
		return -1;
	}

	do{
		reg32_val = *vir_addr;
		if(reg32_val & IOM3STAT_SLEEP_MASK)
			break;
		else
			msleep(WAIT_IOM3_WFI_PERIOD);
	}while(--count > 0);
	iounmap(vir_addr);
	return count;
}
#endif

#define I2C_0_RST_VAL	(0x10)
static void reset_i2c_0_controller(void)
{
	unsigned long flags;
	unsigned int volatile *rsten_addr = (unsigned int volatile *)ioremap(PERRSTEN2_ADDR, 4);
	unsigned int volatile *rstdis_addr = (unsigned int volatile *)ioremap(PERRSTDIS2_ADDR, 4);

	if ((!rsten_addr) ||(!rstdis_addr)) {
		hwlog_err("ioremap i2c reset reg addr failed, 0x%x, 0x%x\n",
			(unsigned int)rsten_addr, (unsigned int)rstdis_addr);
		return;
	}

	local_irq_save(flags);
	writel(I2C_0_RST_VAL, rsten_addr);
	udelay(5);
	writel(I2C_0_RST_VAL, rstdis_addr);
	local_irq_restore(flags);
	iounmap(rsten_addr);
	iounmap(rstdis_addr);

	return;
}
static int hw_dmp_power_reset_for_recovery_iom3(void)
{
	int ret = 0;
	hwlog_info("DMP powerdown!\n");
/*TODO: power off*/
	return 0;
}
extern bool is_invensense_dmp_exist;
static void hw_power_reset_for_recovery_iom3(void)
{
	int ret = 0;
	if (true == is_invensense_dmp_exist) {
		ret = hw_dmp_power_reset_for_recovery_iom3();
		if (ret) {
			hwlog_err("hw_dmp_power_reset_for_recovery_iom3 error!\n");
		}
		return;
	}
	return;
}

#define IOM3_REC_NEST_MAX		(5)
extern void operations_when_recovery_iom3(void);
static void iom3_recovery_work(struct work_struct *work)
{
	int rec_nest_count = 0;
	int rc;
	u32 ack_buffer;
	u32 tx_buffer;

	hwlog_err("%s enter\n", __func__);
	wake_lock(&iom3_rec_wl);

recovery_iom3:
	if(rec_nest_count++ > IOM3_REC_NEST_MAX){
		hwlog_err("unlucky recovery iom3 times exceed limit\n");
		atomic_set(&iom3_rec_state, IOM3_RECOVERY_FAILED);
		blocking_notifier_call_chain(&iom3_recovery_notifier_list, IOM3_RECOVERY_FAILED, NULL);
		atomic_set(&iom3_rec_state, IOM3_RECOVERY_IDLE);
		wake_unlock(&iom3_rec_wl);
		hwlog_err("%s exit\n", __func__);
		return;
	}

	//wait for iom3 enter WFI state
	show_iom3_stat();//only for IOM3 debug
	//rc = wait_for_iom3_wfi(100);
	//if(rc < 0 || 0 == rc) {//ioremap error || wait wfi timeout
	//	hwlog_err("RPROC wait for iom3 WFI failed %d, nest_count %d\n", rc, rec_nest_count);
	//	goto recovery_iom3;
	//}

	//reload iom3 system
	tx_buffer = RELOAD_IOM3_CMD;
	rc = RPROC_SYNC_SEND(HISI_RPROC_LPM3, &tx_buffer, 1, 1, &ack_buffer, 1);
	if (rc) {
		hwlog_err("RPROC reload iom3 failed %d, nest_count %d\n", rc, rec_nest_count);
		goto recovery_iom3;
	}

	show_iom3_stat();//only for IOM3 debug
	reset_i2c_0_controller();
	msleep(5);
	hw_power_reset_for_recovery_iom3();
	atomic_set(&iom3_rec_state, IOM3_RECOVERY_MINISYS);

	//startup iom3 system
	INIT_COMPLETION(iom3_rec_done);
	tx_buffer = STARTUP_IOM3_CMD;
	rc = RPROC_SYNC_SEND(HISI_RPROC_LPM3, &tx_buffer, 1, 1, &ack_buffer, 1);
	if (rc) {
		hwlog_err("RPROC start iom3 failed %d, nest_count %d\n", rc, rec_nest_count);
		goto recovery_iom3;
	}
	hwlog_err("RPROC restart iom3 success\n");
	show_iom3_stat();//only for IOM3 debug

	//dynamic loading
	if (!wait_for_completion_timeout(&iom3_rec_done, 5*HZ)) {
		hwlog_err("wait for iom3 system ready timeout\n");
		msleep(1000);
		goto recovery_iom3;
	}

	//repeat send cmd
	msleep(100);//wait iom3 finish handle config-data
	atomic_set(&iom3_rec_state, IOM3_RECOVERY_DOING);
	hwlog_err("%s doing\n", __func__);
	blocking_notifier_call_chain(&iom3_recovery_notifier_list, IOM3_RECOVERY_DOING, NULL);
	operations_when_recovery_iom3();
	atomic_set(&iom3_rec_state, IOM3_RECOVERY_IDLE);
	wake_unlock(&iom3_rec_wl);
	hwlog_err("%s finish recovery\n", __func__);
	blocking_notifier_call_chain(&iom3_recovery_notifier_list, IOM3_RECOVERY_IDLE, NULL);
	hwlog_err("%s exit\n", __func__);
	return;
}

int iom3_need_recovery(void)
{
	int ret = 0;
	int old_state;
	old_state = atomic_cmpxchg(&iom3_rec_state, IOM3_RECOVERY_IDLE, IOM3_RECOVERY_START);
	hwlog_err("recovery prev state %d\n", old_state);
	if(old_state == IOM3_RECOVERY_IDLE){//prev state is IDLE start recovery progress
		wake_lock_timeout(&iom3_rec_wl, 5*HZ);
		blocking_notifier_call_chain(&iom3_recovery_notifier_list, IOM3_RECOVERY_START, NULL);
		queue_delayed_work(iom3_rec_wq, &iom3_rec_work, 0);
	}
	return ret;
}
#else
int iom3_need_recovery(void)
{
	hwlog_err("[WARNING:] !!! recovery not support\n");
	return 0;
}
#endif
static int  inputhub_mcu_init(void)
{
    int ret;
    init_completion(&send_complete);
#ifdef CONFIG_IOM3_RECOVERY
    atomic_set(&iom3_rec_state, IOM3_RECOVERY_UNINIT);
    iom3_rec_wq = create_singlethread_workqueue("iom3_rec_wq");
    if (!iom3_rec_wq)
    {
        hwlog_err("--------------------> faild in create iom3 wq in %s!\n", __func__);
        return -1;
    }
    INIT_DELAYED_WORK(&iom3_rec_work, iom3_recovery_work);
    init_completion(&iom3_rec_done);
    wake_lock_init(&iom3_rec_wl, WAKE_LOCK_SUSPEND, "iom3_rec_wl");
#endif

    shb_dclient = dsm_register_client(&dsm_sensorhub);
    ret = inputhub_route_init();
    inputhub_mcu_connect();
    boot_iom3();
    setSensorMcuMode(1);
    hwlog_info("----%s--->\n",__func__);
    return ret;
}

static void __exit inputhub_mcu_exit(void)
{
    inputhub_route_exit();
    RPROC_PUT(HISI_RPROC_IOM3);
}
/*begin huangwen 20120706*/
fs_initcall_sync(inputhub_mcu_init);
/*end huangwen 20120706*/

module_exit(inputhub_mcu_exit);

MODULE_AUTHOR("Input Hub <smartphone@huawei.com>");
MODULE_DESCRIPTION("input hub bridge");
MODULE_LICENSE("GPL");
