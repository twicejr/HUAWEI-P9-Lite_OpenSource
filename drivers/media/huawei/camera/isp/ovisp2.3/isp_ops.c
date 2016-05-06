

#include <linux/of.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ioctl.h>
#include <linux/spinlock.h>
#include <linux/proc_fs.h>
#include <linux/atomic.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/videodev2.h>
#include <linux/iommu.h>
#include <linux/platform_device.h>
#include <media/v4l2-fh.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/pinctrl/consumer.h>
#include <linux/hisi/hisi-iommu.h>
#include <linux/fs.h>
#include <linux/dma-mapping.h>
#include "../../io/hw_isp_io.h"
#include "hwisp_intf.h"
#include "isp_ops.h"
#include "cam_log.h"
#include "sensor_commom.h"
#include "platform_cfg.h"
#include "hw_csi.h"
#include <linux/hisi/ion-iommu.h>


#define CREATE_TRACE_POINTS
#include "trace_ovisp23.h"

#include <linux/hisi/hi3xxx/global_ddr_map.h>

//extern struct hisi_sensor_ctrl_t hisi_s_ctrl_0;
//extern struct hisi_sensor_ctrl_t hisi_s_ctrl_1;
#define DUMMY_META_DATA_PAD	(0x55)
#define PD_DATA_LENTH 772
/* #define SENSOR_EXPO_EFFECT_DELAY 2 */

#define IRQ_TWO_TIME_BUGFIX 1
static isp_hw_data_t isp_hw_data;
static hisi_eg_ctrl_t hisi_eg_ctrl;
extern u32 isp_debug_flag;

#define FIRMWARE_MEM_SIZE   (200*1024)
static u8 *isp_firmware_addr;
static u32 isp_firmware_size;

/* additional definition for V4L2_PIX_FMT, not inlcuded in <linux/videodev2.h> */
#define V4L2_PIX_FMT_RAW8    v4l2_fourcc('R', 'A', 'W', '8')
#define V4L2_PIX_FMT_RAW10   v4l2_fourcc('R', 'A', 'W', 'X')
#define V4L2_PIX_FMT_RAW12   v4l2_fourcc('R', 'A', 'W', '2')
#define V4L2_PIX_FMT_RAW14   v4l2_fourcc('R', 'A', 'W', '4')

static void hw_aec_cmd_tasklet(unsigned long arg);
DECLARE_TASKLET(hw_isr_aec_tasklet, hw_aec_cmd_tasklet, (unsigned long) 0);
struct timeval tm_v[2];
static void hw_eofs_tasklet(unsigned long data);
DECLARE_TASKLET(hw_isr_eofs_tasklet, hw_eofs_tasklet, (unsigned long) 0);

static void hw_isr_do_tasklet(unsigned long data);
DECLARE_TASKLET(hw_isr_tasklet, hw_isr_do_tasklet,((unsigned long)&(isp_hw_data.irq_val)));

DEFINE_MUTEX(cmdset_mutex);

static void isp_save_raw_info(raw_buffer_info_t *raw_info, int flow);
static void ispv3_hardware_clear_ready(int port);
/* #define set8(reg, value) (*((volatile unsigned char *)(reg)) = (value)) */
#define set32(reg, value) (*((volatile u32 *)(reg)) = (value))
/* #define get8(reg) (*(volatile unsigned char *)(reg)) */
/* #define get32(reg) (*(volatile u32 *)(reg)) */

/*
 **************************************************************************
 * FunctionName: dump_file;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
#define DUMP_FILE   0
#if DUMP_FILE
phys_addr_t phy_addr;
uint32_t frame_index;

void dump_file_handler(struct work_struct *work)
{
    dump_pic(1,phy_addr,1280*720*3/2,frame_index,0);
}

static DECLARE_WORK(dump_work, dump_file_handler);
void dump_file(char *filename, unsigned long addr, u32 size)
{
#if DUMP_FILE
	struct file *file1 = NULL;
	mm_segment_t old_fs;
	memset(&old_fs, 0x0, sizeof(old_fs));

	printk("dumpfile %s with size %u", filename, size);
	if (filename == NULL) {
		printk("dump file with NULL file name!");
		return;
	}
	file1 = filp_open(filename, O_CREAT | O_RDWR, 0644);
	if (IS_ERR(file1)) {
		printk("error occured while opening file %s, exiting...\n", filename);
		return;
	} else {
		old_fs = get_fs();
		set_fs(KERNEL_DS);
		file1->f_op->write(file1, (char *)addr, size, &file1->f_pos);
		set_fs(old_fs);
		filp_close(file1, NULL);
		return;
	}
#endif
}

void dump_pic(int type,phys_addr_t addr, u32 size,u32 frame_index,int port)
{
	char filename[32];
	void __iomem *viraddr;
	memset(filename,0,sizeof(filename));
	if(frame_index % 32 != 0)
                return;
/*	switch(type)
	{
		case 1:
			snprintf(filename, sizeof(filename), "/data/img/pic_port%d_%d.yuv",port,frame_index);
			break;
	}*/
	if(type == 1)
	{
		snprintf(filename, sizeof(filename), "/data/img/pic_port%d_%d.yuv",port,frame_index);
	}

	viraddr = ioremap_nocache(addr, size);
	if(0 != viraddr)
	{
		dump_file(filename, (unsigned long)viraddr, size);
		mb();
		iounmap(viraddr);
	}
	else
	{
		printk("don't have enough memory");
	}
}
#endif

static void hw_eofs_tasklet(unsigned long data)
{
	//unsigned long lock_flags;
	//struct sensor_t *sensor = NULL;
	//struct expo_gain_seq *me_seq = &hisi_eg_ctrl.me_seq;
	//int index = hisi_eg_ctrl.seq_index;
	//sensor = hisi_eg_ctrl.sensor;

	/* set expo & gain
	 * never print any log in this section
	 */
	do_gettimeofday(&tm_v[0]);
	/* wind
	if (0 == index) {
		sensor->func_tbl->sensor_set_hts(sensor, me_seq->hts);
		sensor->func_tbl->sensor_set_vts(sensor, me_seq->vts);
	}


	if (index < me_seq->seq_size) {
		if (sensor->func_tbl->sensor_set_expo_gain != NULL)
			sensor->func_tbl->sensor_set_expo_gain(sensor, me_seq->expo[index], me_seq->gain[index - 1]);
		else {
			sensor->func_tbl->sensor_set_expo(sensor, me_seq->expo[index]);
			sensor->func_tbl->sensor_set_gain(sensor, me_seq->gain[index]);
		}
	}

	if (index >= SENSOR_EXPO_EFFECT_DELAY && index < me_seq->seq_size + SENSOR_EXPO_EFFECT_DELAY) {
		spin_lock_irqsave(&isp_hw_data.irq_status_lock, lock_flags);
		isp_hw_data.irq_val.host_ae_applied = MANUAL_AE_APPLIED;
		isp_hw_data.irq_val.expo = me_seq->expo[index - SENSOR_EXPO_EFFECT_DELAY];
		isp_hw_data.irq_val.gain = me_seq->gain[index - SENSOR_EXPO_EFFECT_DELAY + sensor->sensor_info->sensor_type];
		isp_hw_data.irq_val.hts = me_seq->hts;
		isp_hw_data.irq_val.vts = me_seq->vts;
		spin_unlock_irqrestore(&isp_hw_data.irq_status_lock, lock_flags);
	}

	hisi_eg_ctrl.seq_index++;
*/
	do_gettimeofday(&tm_v[1]);
	cam_info("tasklet used %dus",
		(int)((tm_v[1].tv_sec - tm_v[0].tv_sec)*1000000 + (tm_v[1].tv_usec - tm_v[0].tv_usec)));
}

static int wait_fw_load_timeout(int time_out)
{
	long jiffies = 0;

	jiffies = msecs_to_jiffies(time_out);

	if (down_timeout(&isp_hw_data.sem_cmd_done, jiffies)) {
		cam_err("MCU not respond when downloading firmware.\n");
		return -ETIME;
	} else if (ISP_GETREG8(COMMAND_FINISHED) != CMD_FIRMWARE_DOWNLOAD) {
		cam_err("COMMAND_FINISHED[%d] not is cmd firmware download.\n", ISP_GETREG8(COMMAND_FINISHED));
		return -EINVAL;
	} else {
		cam_info("firmware download successfully.");
	}

	return 0;
}

#if IRQ_TWO_TIME_BUGFIX

#define REG_SHIFT_WRITE_DONE	1

typedef  enum {
	PORT0_DONE = 0,
	PORT1_DONE,
	PORT2_DONE,
	PORT3_DONE,
	PORT_MAX,
}irq_port_done;

static long long int now_time[PORT_MAX], last_time[PORT_MAX];

void hw_init_irq_done_time(void)
{
	memset(now_time, 0x0, sizeof(now_time));
	memset(last_time, 0x0, sizeof(last_time));
}

inline void hw_check_done_time(u8 *val_mac, irq_port_done port_done)
{
	struct timeval time_val;
	long long int  time_gap;
	do_gettimeofday(&time_val);
	now_time[port_done]  = (long long)time_val.tv_sec * 1000000L + (long long)time_val.tv_usec;
	time_gap = now_time[port_done] - last_time[port_done];
	
	if( time_gap < 5000LL) {
		cam_info("IRQ_PORT0_WRITE_DONE time between now and last: %lld us", time_gap);
		(*val_mac) &= ~(1 << REG_SHIFT_WRITE_DONE);
	}
	last_time[port_done] = now_time[port_done];
}
#endif
#if 0
static void aec_sensor_handle(int flow, sensor_t *sensor)
{
	int interrupt_type;
	u32 expo;
	u16 gain;
	int hold_flag;

	hold_flag = ISP_GETREG8(HOST_HOLD_FLAG(flow));
	if (hold_flag == 0) {
		cam_warn("no valid host_hold_flag, flow %d", flow);
		return;
	}

	interrupt_type = ISP_GETREG8(REG_FW_AE_INT_TYPE(flow));

	expo = get_writeback_expo(flow);
	gain = get_writeback_gain(flow);

	cam_debug("enter %s ,expo 0x%x, gain 0x%x, sensor_name %s, interrupt_type 0x%x",
		__func__, expo, gain, sensor->board_info->name, interrupt_type);
/* wind
	if (interrupt_type == CMD_WRITEBACK_EXPO_GAIN ||
		interrupt_type == CMD_WRITEBACK_EXPO ||
		interrupt_type == CMD_WRITEBACK_GAIN) {
			if (sensor->func_tbl->sensor_set_expo_gain) {
				sensor->func_tbl->sensor_set_expo_gain(sensor, expo, gain);
			} else {
				if (sensor->func_tbl->sensor_set_expo)
					sensor->func_tbl->sensor_set_expo(sensor, expo);
				if (sensor->func_tbl->sensor_set_gain)
					sensor->func_tbl->sensor_set_gain(sensor, gain);
			}
	}

	ISP_SETREG8(REG_FW_AE_INT_TYPE(flow), 0);
	ISP_SETREG8(HOST_HOLD_FLAG(flow), 0);
*/
	return;
}
#endif
static void hw_aec_cmd_tasklet(unsigned long arg)
{
	int flag_pipe[2];
	int flow;

//	sensor_t *sensor = NULL;

	flag_pipe[0] = ISP_GETREG8(HOST_HOLD_FLAG(0));
	flag_pipe[1] = ISP_GETREG8(HOST_HOLD_FLAG(1));

	if (flag_pipe[0] == 1) {
		flow = 0;
	#if 0
		//sensor = hisi_s_ctrl_0.sensor;
		if (sensor != NULL) {
			aec_sensor_handle(flow, sensor);
		} else {
			ISP_SETREG8(REG_FW_AE_INT_TYPE(flow), 0);
			ISP_SETREG8(HOST_HOLD_FLAG(flow), 0);
		}
	#else
		ISP_SETREG8(REG_FW_AE_INT_TYPE(flow), 0);
		ISP_SETREG8(HOST_HOLD_FLAG(flow), 0);
	#endif
	}

	if (flag_pipe[1] == 1) {
		flow = 1;
	#if 0
		//sensor = hisi_s_ctrl_1.sensor;
		if (sensor != NULL) {
			aec_sensor_handle(flow, sensor);
		} else {
			ISP_SETREG8(REG_FW_AE_INT_TYPE(flow), 0);
			ISP_SETREG8(HOST_HOLD_FLAG(flow), 0);
		}
	#else
			ISP_SETREG8(REG_FW_AE_INT_TYPE(flow), 0);
			ISP_SETREG8(HOST_HOLD_FLAG(flow), 0);
	#endif
	}

	return;
}

static irqreturn_t isp_irq_handler(int irq, void *dev_id)
{
	unsigned long lock_flags;
	u8 val_level1[4];
	u8 val_mac1[4];
	u8 val_mac2[4];
	u8 val_mac3[4];
	u8 temp = 0;

	u8 cmd_result = 0;
	u8 cmd_done = 0;
	int flag_aec[2];
	int eof_trigger = hisi_eg_ctrl.eof_trigger;
    
	do_gettimeofday(&tm_v[0]);

	if (!isp_hw_data.poll_start) {
            val_level1[0] = ISPHW_GETREG8(REG_ISP_INT_STAT_1);
            up(&isp_hw_data.sem_cmd_done);

            return IRQ_HANDLED;
	}

	spin_lock_irqsave(&isp_hw_data.irq_status_lock, lock_flags);

	/* first read level1 interrupts */
	val_level1[0] = ISPHW_GETREG8(REG_ISP_INT_STAT_1);
	val_level1[1] = ISPHW_GETREG8(REG_ISP_INT_STAT_2);
	val_level1[2] = ISPHW_GETREG8(REG_ISP_INT_STAT_3);
	val_level1[3] = ISPHW_GETREG8(REG_ISP_INT_STAT_4);

	/*TO DO:access irq registers here, second class irq register should go first!*/
	val_mac1[0] = ISPHW_GETREG8(REG_ISP_MAC1_INT_STAT_H);
	val_mac1[1] = ISPHW_GETREG8(REG_ISP_MAC1_INT_STAT_S0);
	val_mac1[2] = ISPHW_GETREG8(REG_ISP_MAC1_INT_STAT_S1);
	val_mac1[3] = ISPHW_GETREG8(REG_ISP_MAC1_STREAM_SELECT);

	val_mac2[0] = ISPHW_GETREG8(REG_ISP_MAC2_INT_STAT_H);
	val_mac2[1] = ISPHW_GETREG8(REG_ISP_MAC2_INT_STAT_S0);
	val_mac2[2] = ISPHW_GETREG8(REG_ISP_MAC2_INT_STAT_S1);
	val_mac2[3] = ISPHW_GETREG8(REG_ISP_MAC2_STREAM_SELECT);

	val_mac3[0] = ISPHW_GETREG8(REG_ISP_MAC3_INT_STAT_H);
	val_mac3[1] = ISPHW_GETREG8(REG_ISP_MAC3_INT_STAT_S0);
	val_mac3[2] = ISPHW_GETREG8(REG_ISP_MAC3_INT_STAT_S1);
	val_mac3[3] = ISPHW_GETREG8(REG_ISP_MAC3_STREAM_SELECT);

#if IRQ_TWO_TIME_BUGFIX
	/* read status registers again to confirm read clear */
	/* re-read mac1 */
	if (val_mac1[1] != 0) {
		temp = ISPHW_GETREG8(REG_ISP_MAC1_INT_STAT_S0);
		if ((temp | val_mac1[1]) != val_mac1[1]) {
			val_mac1[1] |= temp;
			cam_info("re-read mac1[1] 0x%x exception", temp);
		}
		if (temp != 0)
			cam_info("re-read mac1[1] 0x%x helpful", temp);
	}
	if (val_mac1[2] != 0) {
		temp = ISPHW_GETREG8(REG_ISP_MAC1_INT_STAT_S1);
		if ((temp | val_mac1[2]) != val_mac1[2]) {
			val_mac1[2] |= temp;
			cam_info("re-read mac1[2] 0x%x exception", temp);
		}
		if (temp != 0)
			cam_info("re-read mac1[2] 0x%x helpful", temp);
	}

	/* re-read mac2 */
	if (val_mac2[1] != 0) {
		temp = ISPHW_GETREG8(REG_ISP_MAC2_INT_STAT_S0);
		if ((temp | val_mac2[1]) != val_mac2[1]) {
			val_mac2[1] |= temp;
			cam_info("re-read mac2[1] 0x%x exception", temp);
		}
		if (temp != 0)
			cam_info("re-read mac2[1] 0x%x helpful", temp);
	}
	if (val_mac2[2] != 0) {
		temp = ISPHW_GETREG8(REG_ISP_MAC2_INT_STAT_S1);
		if ((temp | val_mac2[2]) != val_mac2[2]) {
			val_mac2[2] |= temp;
			cam_info("re-read mac2[2] 0x%x exception", temp);
		}
		if (temp != 0)
			cam_info("re-read mac2[2] 0x%x helpful", temp);
	}

	/* re-read mac3 */
	if (val_mac3[1] != 0) {
		temp = ISPHW_GETREG8(REG_ISP_MAC3_INT_STAT_S0);
		if ((temp | val_mac3[1]) != val_mac3[1]) {
			val_mac3[1] |= temp;
			cam_info("re-read mac3[1] 0x%x exception", temp);
		}
		if (temp != 0)
			cam_info("re-read mac3[1] 0x%x helpful", temp);
	}
	if (val_mac3[2] != 0) {
		temp = ISPHW_GETREG8(REG_ISP_MAC3_INT_STAT_S1);
		if ((temp | val_mac3[2]) != val_mac3[2]) {
			val_mac3[2] |= temp;
			cam_info("re-read mac3[2] 0x%x exception", temp);
		}
		if (temp != 0)
			cam_info("re-read mac3[2] 0x%x helpful", temp);
	}

	/* PORT0 WRITE_DONE: calculater the time gap between this and  last  */
	if ((val_mac1[1] >> REG_SHIFT_WRITE_DONE) & 0x1) {
		hw_check_done_time(&val_mac1[1], PORT0_DONE);
	}

	/* PORT1 WRITE_DONE: calculater the time gap between this and  last  */
	if ((val_mac1[2] >> REG_SHIFT_WRITE_DONE) & 0x1) {
		hw_check_done_time(&val_mac1[2], PORT1_DONE);
	}

	/* PORT2 WRITE_DONE: calculater the time gap between this and  last  */
	if ((val_mac2[1] >> REG_SHIFT_WRITE_DONE) & 0x1) {
		hw_check_done_time(&val_mac2[1], PORT2_DONE);
	}

	/* PORT3 WRITE_DONE: calculater the time gap between this and  last  */
	if ((val_mac2[2] >> REG_SHIFT_WRITE_DONE) & 0x1) {
		hw_check_done_time(&val_mac2[2], PORT3_DONE);
	}
#endif

	if ((val_level1[0] & ISP_COMMAND_DONE_INT) != 0) {
		cmd_done = ISP_GETREG8(REG_FW_CMD_DONE_TYPE);

		if (cmd_done == 0) {
			val_level1[0] &= ~(1 << REG_SHIFT_CMD_DONE);
		} else {
			cmd_result = ISP_GETREG8(COMMAND_RESULT);

			/* clear cmd done type register */
			ISP_SETREG8(REG_FW_CMD_DONE_TYPE, 0);
            ovisp23_notify_cmd_ready(cmd_done,cmd_result);
		}

		flag_aec[0] = ISP_GETREG8(HOST_HOLD_FLAG(0));
		flag_aec[1] = ISP_GETREG8(HOST_HOLD_FLAG(1));
		if (flag_aec[0] != 0 || flag_aec[1] != 0)
			tasklet_schedule(&hw_isr_aec_tasklet);
	}

	/* save status later */
	isp_hw_data.irq_val.mac1_irq_status_h |= val_mac1[0];
	isp_hw_data.irq_val.mac1_irq_status_s0 |= val_mac1[1];
	isp_hw_data.irq_val.mac1_irq_status_s1 |= val_mac1[2];
	isp_hw_data.irq_val.mac1_irq_status_ss |= val_mac1[3];

	isp_hw_data.irq_val.mac2_irq_status_h |= val_mac2[0];
	isp_hw_data.irq_val.mac2_irq_status_s0 |= val_mac2[1];
	isp_hw_data.irq_val.mac2_irq_status_s1 |= val_mac2[2];
	isp_hw_data.irq_val.mac2_irq_status_ss |= val_mac2[3];

	isp_hw_data.irq_val.mac3_irq_status_h |= val_mac3[0];
	isp_hw_data.irq_val.mac3_irq_status_s0 |= val_mac3[1];
	isp_hw_data.irq_val.mac3_irq_status_s1 |= val_mac3[2];
	isp_hw_data.irq_val.mac3_irq_status_ss |= val_mac3[3];

	isp_hw_data.irq_val.irq_status_1 |= val_level1[0];
	isp_hw_data.irq_val.irq_status_2 |= val_level1[1];
	isp_hw_data.irq_val.irq_status_3 |= val_level1[2];
	isp_hw_data.irq_val.irq_status_4 |= val_level1[3];

	isp_hw_data.irq_val.cmd_done_id |= cmd_done;
	isp_hw_data.irq_val.cmd_result |= cmd_result;

	isp_hw_data.irq_query_flag = true;

    trace_hw_ovisp23_irq_handler_entry(&isp_hw_data.irq_val); 

	spin_unlock_irqrestore(&isp_hw_data.irq_status_lock, lock_flags);

	wake_up_interruptible(&isp_hw_data.poll_queue_head);

	if(((eof_trigger == PIPE0_TRIG) && (val_level1[3] & ISP_PIPE0_EOF_IDI))
		|| ((eof_trigger == PIPE1_TRIG) && (val_level1[2] & ISP_PIPE1_EOF_IDI)))
		tasklet_hi_schedule(&hw_isr_eofs_tasklet);

	tasklet_schedule(&hw_isr_tasklet);

	return IRQ_HANDLED;
}

static int load_firmware(char *filename)
{
	struct kstat stat;
	mm_segment_t fs;
	struct file *fp = NULL;
	int file_flag = O_RDONLY;
	int ret = 0;


	if (NULL == filename) {
		cam_err("%s param error", __func__);
		return -EINVAL;
	}


	/* must have the following 2 statement */
	fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(filename, file_flag, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		cam_err("open file error!\n");
		set_fs(fs);
		return -ENOENT;
	}

	if (0 != vfs_stat(filename, &stat)) {
		cam_err("failed to get file stat!");
		ret = -EIO;
		goto ERROR;
	}
       isp_firmware_size = stat.size;
	cam_notice("firmware %s, file size : %d", filename, (u32) stat.size);
	ret = vfs_read(fp, (char *)isp_firmware_addr, (u32) isp_firmware_size, &fp->f_pos);
	if (ret != stat.size) {
		cam_err("read file error!, %s , ret=%d\n", filename, ret);
		ret = -EIO;
	} else {
		ret = 0;
	}
ERROR:
	/* must have the following 1 statement */
	set_fs(fs);
	filp_close(fp, 0);
	return ret;
}

#define MTCOMS_ISP_EN (1)
#define MTCOMS_DSS_EN ((1<<5)|(1<<6)|(1<<7))
#define ISP_ISO_DIS (1)
#define DSS_ISO_DIS ((1<<6)|(1<<7)|(1<<8))

#define ISP_MCU_CLK_EN ((1<<14)|(1<<30))
#define ISP_MIPI_CLK_EN ((1<<13)|(1<<29))
#define ISP_CLK_EN ((1<<12)|(1<<28))

#define ISP_CLK_DIV_EN (ISP_MCU_CLK_EN|ISP_MIPI_CLK_EN|ISP_CLK_EN)
#define DSS_CLK_DIV_EN ((1<<6)|(1<<7)|(1<<8)|(1<<9)|(1<<22)|(1<<23)|(1<<24)|(1<<25))

#define ISP_CLK_GATE ((1<<21)|(1<<23)|(1<<24)|(1<<25)|(1<<26)|(1<<27))
#define DSS_CLK_GATE ((1<<12)|(1<<13)|(1<<14)|(1<<15)|(1<<16)|(1<<17)|(1<<20)|(1<<22))


#define ISP_REST_DIS ((1<<12)|(1<<13)|(1<<14))
#define DSS_REST_DIS ((1<<10)|(1<<11))

void isp_fpga_clk_enable(void)
{
#if 0 /*enable all clk*/
    int i = 0;
    void __iomem * isp_unreset_reg;
    void __iomem * isp_clock_enable_reg;
    void __iomem * isp_noc_idle_req_reg;
    void __iomem * isp_iomg_reg;

    isp_unreset_reg = (unsigned long)ioremap_nocache(0xfff35088, 0x4);
    set32(isp_unreset_reg, 0xffffffff);
    msleep(10);
    isp_clock_enable_reg = (unsigned long)ioremap_nocache(0xfff35030, 0x4);
    set32(isp_clock_enable_reg, 0xffffffff);
    msleep(10);
    isp_noc_idle_req_reg = (unsigned long)ioremap_nocache(0xfff31380, 0x4);
    set32(isp_noc_idle_req_reg, 0x0);
    msleep(10);
    isp_iomg_reg = (unsigned long)ioremap_nocache(0xe8612010, 88);
    for (i = 0; i < 22; i++) {	
        set32(isp_iomg_reg, 0x1);
        isp_iomg_reg+=4;
        msleep(10);
    }
#else /*enable isp relational clk*/
    int i = 0;
    void __iomem * isp_mtcmos_reg;
    void __iomem * isp_diven_reg;
    void __iomem * isp_iso_dis_reg;
    void __iomem * isp_unreset_reg;
    void __iomem * isp_clock_enable_reg;
    void __iomem * isp_noc_idle_req_reg;
    void __iomem * isp_iomg_reg;

    /*unresset*/
    isp_mtcmos_reg = (void __iomem *)ioremap_nocache(0xfff35150, 0x4);
    //print_info("isp_mtcmos_reg=0x%x", (unsigned int)isp_mtcmos_reg);
    //set32(isp_mtcmos_reg,(MTCOMS_ISP_EN|MTCOMS_DSS_EN|(get32(isp_mtcmos_reg))));
    set32(isp_mtcmos_reg, MTCOMS_ISP_EN|MTCOMS_DSS_EN);
    //print_info("isp_mtcmos_reg = 0x%x",get32(isp_mtcmos_reg));
    msleep(100);

    isp_diven_reg = (void __iomem *)ioremap_nocache(0xfff350f0, 0x4);
    cam_notice("isp_diven_reg=%p", isp_diven_reg);
    set32(isp_diven_reg, ISP_CLK_DIV_EN|DSS_CLK_DIV_EN);
    msleep(100);

    isp_clock_enable_reg = (void __iomem *)ioremap_nocache(0xfff35030, 0x4);
    cam_notice("isp_clock_enable_reg=%p", isp_clock_enable_reg);
    set32(isp_clock_enable_reg, ISP_CLK_GATE|DSS_CLK_GATE);
    msleep(100);

    isp_iso_dis_reg = (void __iomem *)ioremap_nocache(0xfff35148, 0x4);
    cam_notice("isp_iso_dis_reg=%p", isp_iso_dis_reg);
    set32(isp_iso_dis_reg, ISP_ISO_DIS|DSS_ISO_DIS);
    msleep(100);

    isp_unreset_reg = (void __iomem *)ioremap_nocache(0xfff35088, 0x4);
    cam_notice("isp_unreset_reg=%p", isp_unreset_reg);
    set32(isp_unreset_reg, ISP_REST_DIS|DSS_REST_DIS);
    msleep(100);

    isp_noc_idle_req_reg = (void __iomem *)ioremap_nocache(0xfff31380, 0x4);
    cam_notice("isp_noc_idle_req_reg=%p", isp_noc_idle_req_reg);
    set32(isp_noc_idle_req_reg, 0x0);
    msleep(100);

    isp_iomg_reg = (void __iomem *)ioremap_nocache(0xe8612034, 16);
    for (i = 0; i < 4; i++) {
        set32(isp_iomg_reg, 0x1);
        isp_iomg_reg+=4;
        msleep(10);
    }

    isp_iomg_reg = (void __iomem *)ioremap_nocache(0xe8612044, 24);
    for (i = 0; i < 6; i++) {
        set32(isp_iomg_reg, 0x0);
        isp_iomg_reg+=4;
        msleep(10);
    }

    isp_iomg_reg = (void __iomem *)ioremap_nocache(0xe861205c, 8);
    for(i = 0; i < 2; i++) {
        set32(isp_iomg_reg, 0x1);
        isp_iomg_reg+=4;
        msleep(10);	
    }

    isp_iomg_reg = (void __iomem *)ioremap_nocache(0xe8612064, 8);
    for(i = 0; i < 2; i++) {
        set32(isp_iomg_reg, 0x0);
        isp_iomg_reg+=4;
        msleep(10);	
    }
#endif	
}

static int isp_res_init(struct device *pdev)
{
	struct device_node *of_node = pdev->of_node;
	uint32_t base_array[2] = {0};
	uint32_t count = 0;
	int ret = 0;
	static int flag = 0;

	if (hw_is_fpga_board()) {
		/* on fpga platform, open all isp clk and reset for test. */
		isp_fpga_clk_enable();
	}

	/* property(hisi,isp-base) = <address, size>, so count is 2 */
	count = 2;
	if (of_node) {
		ret = of_property_read_u32_array(of_node, "huawei,isp-base",
			base_array, count);
		if (ret < 0) {
			cam_err("%s failed line %d", __func__, __LINE__);
			return ret;
		}
	} else {
		cam_err("%s isp of_node is NULL.%d", __func__, __LINE__);
		return -ENXIO;
	}

	isp_hw_data.phyaddr = base_array[0];
	isp_hw_data.mem_size = base_array[1];

	isp_hw_data.viraddr = ioremap_nocache(isp_hw_data.phyaddr, isp_hw_data.mem_size);
	if (0 == isp_hw_data.viraddr) {
		cam_err("%s ioremap fail", __func__);
		return -ENXIO;
	}

	ret = of_property_read_u32(of_node, "huawei,isp-irq", &isp_hw_data.irq_no);
	if (ret < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		goto fail;
	}

	cam_notice("%s isp-base address = %p. isp-base size = 0x%x. isp-irq = %d",
		__func__,(void *)(isp_hw_data.phyaddr), isp_hw_data.mem_size, isp_hw_data.irq_no);

	spin_lock_init(&isp_hw_data.irq_status_lock);
	init_waitqueue_head(&isp_hw_data.poll_queue_head);
	sema_init(&isp_hw_data.sem_cmd_done, 0);

	/*request irq*/
	ret = request_irq(isp_hw_data.irq_no, isp_irq_handler, 0, "isp_irq", 0);

#if IRQ_TWO_TIME_BUGFIX
	hw_init_irq_done_time();
#endif

	if (ret != 0) {
		cam_err("fail to request irq [%d], error: %d", isp_hw_data.irq_no, ret);
		ret = -ENXIO;
		goto fail;
	}

	if (hw_is_fpga_board()) {
		return ret;
	}

	if (flag == 0) {
		/* get isp regulator */
		isp_hw_data.inter_ldo.supply = "vcc_isp";
		ret = devm_regulator_bulk_get(pdev, 1, &isp_hw_data.inter_ldo);
		if (ret != 0) {
			cam_err("%s: Could not get regulator : %s\n", __func__, "vcc_isp");
			ret = -ENXIO;
			goto fail;
		}
		flag = 1;
	}

	/* pinctrl enable */
	isp_hw_data.isp_pinctrl = devm_pinctrl_get(pdev);
	if (IS_ERR_OR_NULL(isp_hw_data.isp_pinctrl)) {
		cam_err("could not get pinctrl\n");
		ret = -ENXIO;
		goto fail;
	}

	isp_hw_data.pinctrl_def = pinctrl_lookup_state(isp_hw_data.isp_pinctrl,PINCTRL_STATE_DEFAULT);
	if (IS_ERR_OR_NULL(isp_hw_data.pinctrl_def)) {
		cam_err("could not get defstate (%li)\n",
					PTR_ERR(isp_hw_data.pinctrl_def));
		ret = -ENXIO;
		goto fail;
	}

	isp_hw_data.pinctrl_idle = pinctrl_lookup_state(isp_hw_data.isp_pinctrl,PINCTRL_STATE_IDLE);
	if (IS_ERR_OR_NULL(isp_hw_data.pinctrl_idle)) {
		cam_err("could not get idlestate (%li)\n",
				PTR_ERR(isp_hw_data.pinctrl_idle));
		ret = -ENXIO;
		goto fail;
	}

	hisi_eg_ctrl.eof_trigger = NONE_TRIG;

	return 0;
fail:
	if (isp_hw_data.viraddr)
		iounmap((void*)isp_hw_data.viraddr);

	if (isp_hw_data.irq_no) {
		free_irq(isp_hw_data.irq_no, 0);
		isp_hw_data.irq_no = 0;
	}

	return ret;
}

static int isp_res_deinit(void)
{
	int ret = 0;
	cam_notice("enter %s", __func__);

	if (isp_hw_data.viraddr)
		iounmap((void*)isp_hw_data.viraddr);

	if (isp_hw_data.irq_no) {
		free_irq(isp_hw_data.irq_no, 0);
		isp_hw_data.irq_no = 0;
	}

	hisi_eg_ctrl.eof_trigger = NONE_TRIG;

	return ret;
}

/***************** external interface definition start *****************************************/

unsigned int hw_poll_irq(struct file * filp, struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	unsigned long lock_flags;
	cam_debug("enter %s", __func__);

	if (!isp_hw_data.poll_start)
		isp_hw_data.poll_start = true;

	poll_wait(filp, &isp_hw_data.poll_queue_head, wait);

	spin_lock_irqsave(&isp_hw_data.irq_status_lock, lock_flags);
	if (isp_hw_data.irq_query_flag) {
		mask |= POLLPRI;
		isp_hw_data.irq_query_flag = false;
	}
	spin_unlock_irqrestore(&isp_hw_data.irq_status_lock, lock_flags);

	return mask;
}

void hw_query_irq(struct irq_reg_t *irq_info)
{
	unsigned long lock_flags;
	long long int  time_gap;
	long long int sec;

	cam_debug("enter %s", __func__);

	spin_lock_irqsave(&isp_hw_data.irq_status_lock, lock_flags);
	memcpy(irq_info, &isp_hw_data.irq_val, sizeof(struct irq_reg_t));
	memset(&isp_hw_data.irq_val, 0, offsetof(struct irq_reg_t, host_ae_applied));
	spin_unlock_irqrestore(&isp_hw_data.irq_status_lock, lock_flags);

	do_gettimeofday(&tm_v[1]);

	sec = tm_v[1].tv_sec - tm_v[0].tv_sec;
	time_gap = sec * 1000000 + (tm_v[1].tv_usec - tm_v[0].tv_usec);

	if (time_gap > 2000) {
		cam_info("ISP irq time interval %lldus", time_gap);
	}

	return;
}


static void meta_data_raw_work_func(struct work_struct *work)
{
	int len=META_DATA_RAW_SIZE, pos=0;
	u8 *cbuf = (u8 *)isp_hw_data.meta_data_raw_buf;

	while (len > 0) {
		cam_info("meta[%04d]:%02x %02x %02x %02x %02x %02x %02x %02x "
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
static DECLARE_WORK(meta_data_raw_work, meta_data_raw_work_func);

static void pdaf_data_work_func(struct work_struct *work)
{
	int len=PD_DATA_LENTH, pos=0;
	u16 *pdbuf = (u16 *)(isp_hw_data.meta_data.pdaf_info);

	while (len > 0) {
		cam_info("PD[%04d]:%04x %04x %04x %04x %04x %04x %04x %04x "
						 "%04x %04x %04x %04x %04x %04x %04x %04x",
					pos,
					pdbuf[pos],   pdbuf[pos+1], pdbuf[pos+2], pdbuf[pos+3],
					pdbuf[pos+4], pdbuf[pos+5], pdbuf[pos+6], pdbuf[pos+7],
					pdbuf[pos+8], pdbuf[pos+9], pdbuf[pos+10],pdbuf[pos+11],
					pdbuf[pos+12],pdbuf[pos+13],pdbuf[pos+14],pdbuf[pos+15]);

		len -= 16;
		pos += 16;
	}
	
}
static DECLARE_WORK(pdaf_data_work, pdaf_data_work_func);

static void meta_data_done_hander(void)
{
	u8 *data_src, *data_dst;
	u16 *pd_dst;
	int index=0;
	hwisp_stream_t* stream_vc = NULL;
	hwisp_buf_t* buf = NULL;
	isp_hw_data_t *isp_hw = &isp_hw_data;
	u16 b_gain, g_gain, r_gain;
	u32 expo_line;
	u16 gain;
	u8 dummy_meta_data_pad;
	u32 debug_flag = isp_debug_flag;

	if (!isp_hw->meta_running) {
		cam_debug("%s isp meta is not running", __func__);
		return;
	}

	stream_vc = ovisp23_get_stream(ISP_PORT_VC0);
	if (NULL == stream_vc) {
		cam_warn("%s no meta stream", __func__);
		return;
	}

	dummy_meta_data_pad = *((u8 *)(isp_hw->meta_viraddr + META_DATA_RAW_SIZE));
	BUG_ON(DUMMY_META_DATA_PAD != dummy_meta_data_pad);

	/*todo: copy again from dmabuf for cached*/
	memcpy(isp_hw->meta_data_raw_buf, (void *)isp_hw->meta_viraddr, META_DATA_RAW_SIZE);

	data_src = (u8 *)isp_hw->meta_data_raw_buf;
	data_dst = (u8 *)&isp_hw->meta_data;

	for(index = 0; index < (META_DATA_RAW_SIZE/2); index++) {
		*data_dst = (*data_src >> 6) | (*(data_src+1) << 2);
		data_dst++;
		data_src += 2;
	}

	/* Add for pdaf parse */
	data_src = (u8 *)isp_hw->meta_data_raw_buf;
	pd_dst = (u16 *)(isp_hw->meta_data.pdaf_info);

	for(index = 0; index < PD_DATA_LENTH; index++) {
		*pd_dst = ((*data_src >> 1)&0x1F) | (((*(data_src+2)>>1)&0x1F) << 5);
		pd_dst++;
		data_src += 4;
	}

	/* PIPE0 */
	b_gain = isp_hw->meta_data.awb_info.b_gain >> 1;
	r_gain = isp_hw->meta_data.awb_info.r_gain >> 1;
	g_gain = isp_hw->meta_data.awb_info.g_gain >> 1;
	if (g_gain == G_GAIN_BASE) {
		ISP_SETREG16(MANUAL_AWB_GAIN_B(0), b_gain);
		ISP_SETREG16(MANUAL_AWB_GAIN_GB(0), g_gain);
		ISP_SETREG16(MANUAL_AWB_GAIN_GR(0), g_gain);
		ISP_SETREG16(MANUAL_AWB_GAIN_R(0), r_gain);
	}
	expo_line = isp_hw->meta_data.ae_info.expo_line << 4;
	gain = (isp_hw->meta_data.ae_info.gain << 4)/100;
	ISP_SETREG32(REG_FW_AECAGC_MANUAL_EXPO(0), expo_line);
	ISP_SETREG16(REG_FW_AECAGC_MANUAL_GAIN(0), gain);
	/* PIPE1 */
	b_gain = isp_hw->meta_data.ext_info.ext_b_gain_preview >> 1;
	r_gain = isp_hw->meta_data.ext_info.ext_r_gain_preview >> 1;
	g_gain = isp_hw->meta_data.ext_info.ext_g_gain_preview >> 1;
	if (g_gain == G_GAIN_BASE) {
		ISP_SETREG16(MANUAL_AWB_GAIN_B(1), b_gain);
		ISP_SETREG16(MANUAL_AWB_GAIN_GB(1), g_gain);
		ISP_SETREG16(MANUAL_AWB_GAIN_GR(1), g_gain);
		ISP_SETREG16(MANUAL_AWB_GAIN_R(1), r_gain);
	}
	expo_line = isp_hw->meta_data.ext_info.ext_expo_line << 4;
	gain = (isp_hw->meta_data.ext_info.ext_gain << 4)/100;
	ISP_SETREG32(REG_FW_AECAGC_MANUAL_EXPO(1), expo_line);
	ISP_SETREG16(REG_FW_AECAGC_MANUAL_GAIN(1), gain);

	isp_save_raw_info(&(isp_hw->meta_data.u.raw_info[0]), 0);
	isp_save_raw_info(&(isp_hw->meta_data.u.raw_info[1]), 1);

	/* copy struct to user space */
	buf = hwisp_stream_intf_get_buf(&stream_vc->intf);
	if (NULL == buf) {
		cam_warn("%s empty buf in idleq", __func__);
		return;
	}

	if (IS_ERR_OR_NULL(buf->info.ion_vaddr)) {
		cam_warn("%s invalid buf ion vaddr", __func__);
		hwisp_stream_intf_put_buf(&stream_vc->intf, buf);
		return;
	}

	memcpy(buf->info.ion_vaddr, (void*)&isp_hw->meta_data, sizeof(meta_data_t));
	memcpy(&buf->info.timestamp, &isp_hw->meta_attach_timeval, sizeof(struct timeval));
	hwisp_stream_intf_buf_done(&stream_vc->intf, buf);

	if ((isp_hw->meta_data.awb_info.g_gain != 256) ||
		(debug_flag & ISP_DEBUG_META_DATA)) {
		cam_info("%s findex=%d rgain=%d ggain=%d bgain=%d", __func__,
				isp_hw->meta_data.common_info.frame_index,
				isp_hw->meta_data.awb_info.r_gain,
				isp_hw->meta_data.awb_info.g_gain,
				isp_hw->meta_data.awb_info.b_gain);
	}

	if (debug_flag & ISP_DEBUG_META_DATA_RAW) {
		schedule_work(&meta_data_raw_work);
	}

	if (debug_flag & ISP_DEBUG_PDAF_DATA) {
		cam_info("%s findex=%d ", __func__,
						isp_hw->meta_data.common_info.frame_index);
		schedule_work(&pdaf_data_work);
	}

}


int hw_isp_init(struct device *pdev)
{
	int ret = 0;
	int port;

	cam_info("enter %s", __func__);

	/*init res */
	ret = isp_res_init(pdev);
	if (ret) {
		cam_err("failed init isp res!");
		return ret;
	}

	hw_io_set_isp_base(isp_hw_data.viraddr);

	for (port = ISP_PORT_WRITE0 ; port < ISP_PORT_MAX; port++) {
		isp_hw_data.mac_array[port].buf[0] = NULL;
		isp_hw_data.mac_array[port].buf[1] = NULL;
		spin_lock_init(&(isp_hw_data.mac_array[port].lock));
	}

	/* print meta data buffer to make sure valid address */
	cam_info("%s meta_viraddr=%p meta_phyaddr=%p size=%u", __func__,
			 isp_hw_data.meta_viraddr, (void *)(isp_hw_data.meta_phyaddr), META_DATA_RAW_SIZE);

	ret = load_firmware(FIRMWARE_FILE_PATH);
	return ret;
}

int hw_isp_deinit(struct device *pdev)
{
	int ret = 0;

	cam_info("enter %s", __func__);
	/*deinit res */
	ret = isp_res_deinit();
	if (ret) {
		cam_err("failed deinit isp res!");
		return ret;
	}

	hw_io_set_isp_base(0x00);

	return ret;
}

int hw_isp_poweron(void)
{
	int ret = 0;
	int retry = 0;

	cam_info("enter %s", __func__);

	isp_hw_data.poll_start = false;

power_on_try:
	if (!hw_is_fpga_board()) {
		ret = regulator_bulk_enable(1, &isp_hw_data.inter_ldo);
		if (ret) {
			cam_err("%s, failed to enable regulators", __func__);
			return ret;
		}
		ret = pinctrl_select_state(isp_hw_data.isp_pinctrl, isp_hw_data.pinctrl_def); //work mode
		if (ret) {
			cam_err("%s, could not set pins to default state.", __func__);
			return ret;
		}
	}

	/* Reset ISP */
	ISP_SETREG8(REG_ISP_SOFT_RST, DO_SOFT_RST);

	/* ISP dsiable stand by */
	ISP_SETREG8(REG_ISP_SOFT_STANDBY, DO_SOFTWARE_STAND_BY);
	udelay(1);
	/* MCU reset */
	ISP_SETREG8(REG_ISP_CLK_USED_BY_MCU, 0xf1);

	memcpy((void*)isp_hw_data.viraddr, (void*)isp_firmware_addr, isp_firmware_size);

	ISP_SETREG8(REG_ISP_INT_EN_1, 0x40);//enable cmd set done interrupt
	ISP_SETREG8(REG_ISP_INT_EN_2, 0x00);
	ISP_SETREG8(REG_ISP_INT_EN_3, 0x00);
	ISP_SETREG8(REG_ISP_INT_EN_4, 0x00);

	/* MCU enable */
	ISP_SETREG8(REG_ISP_CLK_USED_BY_MCU, 0xf0);

	ret = wait_fw_load_timeout(WAIT_FW_LOAD_TIMEOUT);
	if (ret) {
		cam_err("wait fw load timeout failed. retry %d",retry);
		hw_isp_poweroff();
		if (retry++ < 4)
			goto power_on_try;
		return ret;
	}

	cam_notice("%s isp poweron success. viraddr %p. firmware version: 0x%x",
        __func__, isp_hw_data.viraddr, ISP_GETREG16(REG_FW_VISION));
	isp_hw_data.poll_start = true;

    /* Enable IOMMU For each mac */
    MMU_SETREG32(REG_PORT_MMU_CTL_ADDR(ISP_PORT_WRITE0), 0x2);
    MMU_SETREG32(REG_PORT_MMU_CTL_ADDR(ISP_PORT_WRITE2), 0x2);
    MMU_SETREG32(REG_PORT_MMU_CTL_ADDR(ISP_PORT_WRITE4), 0x2);

	return ret;
}

int hw_isp_poweroff(void)
{
	int ret = 0;
	isp_hw_data_t *isp_hw = &isp_hw_data;

	cam_notice("%s enter", __func__);

	ISP_SETREG8(REG_ISP_SOFT_RST, DO_SOFT_RST);
	ISP_SETREG8(REG_ISP_INT_EN_4, 0x00);

	/* make sure work has been stopped */
	isp_hw->meta_running = false;

	if (hw_is_fpga_board())
		return 0;

	if (!regulator_is_enabled(isp_hw_data.inter_ldo.consumer))
		return 0;

	/* todo read dts file and config pin register */
	ret = pinctrl_select_state(isp_hw_data.isp_pinctrl, isp_hw_data.pinctrl_idle); /* power off mode */
	if (ret) {
		cam_err("%s, could not set pins to default state.", __func__);
		return ret;
	}

	/* disable isp regualtor */
	ret = regulator_bulk_disable(1, &isp_hw_data.inter_ldo);
	if (ret) {
		cam_err("%s, failed to disable regulators", __func__);
	}

	return ret;
}


void hw_isp_clear_port(int port)
{
	/* careful: only write port is allowed to clear*/
	ispv3_hardware_clear_ready(port);

	/* only clear buffer array, leave spinlock */
	isp_hw_data.mac_array[port].buf[0] = NULL;
	isp_hw_data.mac_array[port].buf[1] = NULL;
}

void hw_isp_setup_port(int port)
{
	spin_lock_init(&(isp_hw_data.mac_array[port].lock));
}

void meta_data_ctrl(int ctrl, uint32_t attach_port)
{
	u32 meta_phy_addr = (u32)isp_hw_data.meta_phyaddr;
	isp_hw_data_t *isp_hw = &isp_hw_data;

	if (META_CTRL_ENABLE== ctrl) {
		cam_info("%s: enable attach_port=%u", __func__, attach_port);
		//ROI smode enable
		ISP_SETREG8((REG_MAC_BASE(ISP_MAC0) + ROI_ENABLE_OFFSET),\
			(ISP_GETREG8(REG_MAC_BASE(ISP_MAC0) + ROI_ENABLE_OFFSET)) | SHIFT_BIT_0);

		ISP_SETREG16((REG_MAC_BASE(ISP_MAC0) + ROI_MEM_SIZE_OFFSET), META_DATA_RAW_SIZE);
		//mac write address
		ISP_SETREG32((REG_MAC_BASE(ISP_MAC0) + MAC_WRITE_ADDRESS_OFFSET), meta_phy_addr);

		//idi write size, half of mac size for imx135
		ISP_SETREG16(VC_IDI_SIZE, META_DATA_RAW_SIZE >> 1);
		//idi write line
		ISP_SETREG8(VC_IDI_LINES, 1);
		//mipi selection, only mipi0 supportted now
		ISP_SETREG8(VC_IDI_MIPI_INDEX, 0);
		//channel id
		ISP_SETREG8(VC_IDI_CHANNEL_ID, 0 << 2);
		//idi enable
		ISP_SETREG8(VC_IDI_ENABLE, 0x2c);

		memset((void *)isp_hw->meta_viraddr, 0, META_DATA_RAW_SIZE);
		memset((void *)(isp_hw->meta_viraddr + META_DATA_RAW_SIZE),
				DUMMY_META_DATA_PAD, META_DATA_RAW_SIZE);
		isp_hw->meta_attach_port = attach_port;
		isp_hw->meta_running = true;
	} else {
		cam_info("%s: disable", __func__);
		//idi disbale
		ISP_SETREG8(VC_IDI_ENABLE, 0x0);
		isp_hw->meta_running = false;
		isp_hw->meta_attach_port = attach_port;
	}
}

int meta_data_buf_prepare(struct device *pdev)
{
	u8 *meta_vir_addr = 0;
	dma_addr_t meta_phy_addr = 0;
	isp_hw_data_t *isp_hw = &isp_hw_data;
	int ret = 0;

	/* alloc buffer once when probe, never free */
	meta_vir_addr = (u8 *)dma_alloc_coherent(pdev, META_DATA_RAW_SIZE * 2,
											&meta_phy_addr, GFP_KERNEL);
	if (meta_vir_addr && meta_phy_addr) {
		 isp_hw->meta_viraddr = meta_vir_addr;
		 isp_hw->meta_phyaddr = meta_phy_addr;
		 cam_info("%s meta_viraddr=%p meta_phyaddr=%p size=%u", __func__,
					meta_vir_addr, (void *)meta_phy_addr, META_DATA_RAW_SIZE);
	} else {
		cam_err("%s nomem", __func__);
		ret = -ENOMEM;
	}

	return ret;
}

phys_addr_t hw_get_isp_base_addr(void)
{
	return isp_hw_data.phyaddr;
}

u32 hw_get_isp_mem_size(void)
{
	return isp_hw_data.mem_size;
}

int hw_setup_eof_tasklet(struct sensor_t *sensor, struct expo_gain_seq *me_seq)
{
	hisi_eg_ctrl.sensor = sensor;
	memcpy(&hisi_eg_ctrl.me_seq, me_seq, sizeof(struct expo_gain_seq));
	hisi_eg_ctrl.eof_trigger = me_seq->eof_trigger;
	hisi_eg_ctrl.seq_index = 0;

	return 0;
}

int hw_destory_eof_tasklet(void)
{

	hisi_eg_ctrl.eof_trigger = NONE_TRIG;
	tasklet_kill(&hw_isr_eofs_tasklet);
	hisi_eg_ctrl.sensor = NULL;
	memset(&hisi_eg_ctrl.me_seq, 0, sizeof(struct expo_gain_seq));

	isp_hw_data.irq_val.host_ae_applied = MANUAL_AE_NOT_APPLIED;


	return 0;
}
/***************** external interface definition end *****************************************/
int interworkq_full(isp_port_e port)
{
     if((isp_hw_data.mac_array[port].buf[0] !=NULL)
            &&(isp_hw_data.mac_array[port].buf[1] !=NULL)){
        return true;
     }
      else{
        return false;
    }
}

int interworkq_empty(isp_port_e port)
{
    return isp_hw_data.mac_array[port].buf[0] == NULL;
}

hwisp_buf_t * get_buf_from_interworkq(isp_port_e port)
{
	hwisp_buf_t * temp = NULL;

	temp = isp_hw_data.mac_array[port].buf[0];
	if(temp)
	{
		isp_hw_data.mac_array[port].buf[0] = isp_hw_data.mac_array[port].buf[1];
		isp_hw_data.mac_array[port].buf[1] = NULL;
		return temp;
	}
	else
		return NULL;
}

void put_buf_to_interworkq(isp_port_e port, hwisp_buf_t *buf)
{
	hwisp_buf_t * temp = NULL;

	temp =  isp_hw_data.mac_array[port].buf[0];
	if(temp)
		isp_hw_data.mac_array[port].buf[1] = buf;
	else
		isp_hw_data.mac_array[port].buf[0] = buf;
}


static inline int CHECK_PORT_VALID(int port)
{
	if (port < 0 || port >= ISP_PORT_MAX)
		return -1;
	else
		return 0;
}

static void ispv3_hardware_set_ready(int port)
{
	if (CHECK_PORT_VALID(port) != 0) {
		cam_err(" invalid port %d",port);
		return;
	}

	if ((port % 2) == 0)
		ISP_SETREG8(REG_PORT_READY(port), ISP_GETREG8(REG_PORT_READY(port)) | 0x1);
	else
		ISP_SETREG8(REG_PORT_READY(port), ISP_GETREG8(REG_PORT_READY(port)) | 0x4);
}

static void ispv3_hardware_clear_ready(int port)
{
	if (CHECK_PORT_VALID(port) != 0) {
		cam_err(" invalid port %d",port);
		return;
	}

	if ((port % 2) == 0)
		ISP_SETREG8(REG_PORT_READY(port), ISP_GETREG8(REG_PORT_READY(port)) & 0xfe);
	else
		ISP_SETREG8(REG_PORT_READY(port), ISP_GETREG8(REG_PORT_READY(port)) & 0xfb);
}

static u32 mmu_transid[] = {0x40100, 0x60120, 0x70123};
static u32 mac_transid[] = {0x01100000, 0x21100200, 0x21133200};

int ispv3_hardware_update_addr(isp_port_e port, hwisp_buf_t *buf)
{
        u32 ptba = 0, ptva = 0;
        if (CHECK_PORT_VALID(port) != 0) {
            cam_err(" invalid port %d",port);
            return -1;
        }

        if (buf->info.port.use_phy_memory == 0){
              /*config mmu registers*/
              /*ptba = HISI_RESERVED_SMMU_PHYMEM_BASE;*/
              /*ptva = HISI_IOMMU_IOVA_START;*/
              if (0 != hisi_iommu_get_info(&ptva,&ptba)){
			cam_err("ptba and ptva fail to get valid value");
			return -1;
		}
		MMU_SETREG32(REG_PORT_MMU_RDY_ADDR(port), 0x0);

		MMU_SETREG32(REG_PORT_MMU_PTBA_ADDR(port), ptba);
		MMU_SETREG32(REG_PORT_MMU_PTVA_ADDR(port), ptva);

        if (buf->info.port.pix_format == PIX_FMT_RAW10) {
            MMU_SETREG32(REG_PORT_MMU_TRANSID_ADDR(port), mmu_transid[0]);
            ISP_SETREG32(REG_PORT_MAC_TRANSID_ADDR(port), MMU_MAC_TRANSID(port % 2, mac_transid[0]));

            MMU_SETREG32(REG_PORT_MMU_AW0_ADDR(port), buf->info.y_addr_iommu);
            ISP_SETREG32(REG_PORT_WRITE_ADDR(port), buf->info.y_addr_iommu);
        } else {
            MMU_SETREG32(REG_PORT_MMU_TRANSID_ADDR(port), mmu_transid[1]);
            ISP_SETREG32(REG_PORT_MAC_TRANSID_ADDR(port), MMU_MAC_TRANSID(port % 2, mac_transid[1]));

            MMU_SETREG32(REG_PORT_MMU_AW0_ADDR(port), buf->info.y_addr_iommu);
            MMU_SETREG32(REG_PORT_MMU_AW1_ADDR(port), buf->info.u_addr_iommu);
            ISP_SETREG32(REG_PORT_WRITE_ADDR(port), buf->info.y_addr_iommu);
            ISP_SETREG32(REG_PORT_WRITE_ADDR_U(port), buf->info.u_addr_iommu);
            ISP_SETREG32(REG_PORT_WRITE_ADDR_V(port), buf->info.u_addr_iommu);
        }
		MMU_SETREG32(REG_PORT_MMU_RDY_ADDR(port), 0x1);
		/* use iommu virtual addr*/
		cam_debug("%s iova=0x%x.", __func__, buf->info.y_addr_iommu);
    }
    else {
        ISP_SETREG32(REG_PORT_WRITE_ADDR(port), buf->info.y_addr_phy);
        ISP_SETREG32(REG_PORT_WRITE_ADDR_U(port), buf->info.u_addr_phy);
        ISP_SETREG32(REG_PORT_WRITE_ADDR_V(port), buf->info.u_addr_phy);
        /* use PHY addr*/
        cam_debug("%s phy=0x%x.", __func__, buf->info.y_addr_phy);
   }
	ispv3_hardware_set_ready(port);
	return 0;
}

static int isp_write_start_handler(isp_port_e port)
{
	int                 ret = 0;
	hwisp_buf_t    *frame     = NULL;
	unsigned long       lock_flags;
	/* print_debug("enter %s", __func__); */

    trace_hw_ovisp23_write_start(port); 

	cam_debug("start port =%d",port);
	spin_lock_irqsave(&isp_hw_data.mac_array[port].lock, lock_flags);
    if(interworkq_full(port) == true)
    {
        cam_err("isp isr interworkq is full!");
        ispv3_hardware_set_ready(port);
        spin_unlock_irqrestore(&isp_hw_data.mac_array[port].lock, lock_flags);
        return -1;
    }

	frame = ovisp23_get_buf_from_readyq(port);
	if(frame)
	{
		ispv3_hardware_update_addr(port,frame);
		put_buf_to_interworkq(port,frame);
	} else {
		cam_err("%s, no more empty buffer !!!",  __func__);
		ret = -EINVAL;
	}
	spin_unlock_irqrestore(&isp_hw_data.mac_array[port].lock, lock_flags);
	return ret;
}

static int isp_write_done_handler(isp_port_e port)
{
	int                 ret = 0;
	hwisp_buf_t    *frame     = NULL;
	unsigned long       lock_flags;

    trace_hw_ovisp23_write_done(port); 

	cam_debug("done port =%d",port);
	spin_lock_irqsave(&isp_hw_data.mac_array[port].lock, lock_flags);
	isp_hw_data.frame_index[port]++;
	frame = get_buf_from_interworkq(port);
	spin_unlock_irqrestore(&isp_hw_data.mac_array[port].lock, lock_flags);

	if (frame) {
		do_gettimeofday(&frame->info.timestamp);

		if (isp_hw_data.meta_attach_port == port) {
			memcpy(&isp_hw_data.meta_attach_timeval,
				   &frame->info.timestamp,
				   sizeof(struct timeval));
			//schedule_work(&isp_hw_data.meta_data_work);
			meta_data_done_hander();
			ovisp23_notify_sof(0);
		}
		ovisp23_put_buf_to_doneq(port,frame);
	}
	hisi_csi_clear_dmd_counter();
	return ret;
}

static int isp_write_drop_handler(isp_port_e port)
{
	int                 ret = 0;
	hwisp_buf_t    *frame     = NULL;
	unsigned long       lock_flags;

    trace_hw_ovisp23_write_drop(port); 

	cam_info("drop port =%d",port);
	spin_lock_irqsave(&isp_hw_data.mac_array[port].lock, lock_flags);

	if(interworkq_empty(port)) {
		frame = ovisp23_get_buf_from_readyq(port);
		if(frame)
		{
			ispv3_hardware_update_addr(port,frame);
			put_buf_to_interworkq(port, frame);
		}
	}else {
		ispv3_hardware_set_ready(port);
	}
	spin_unlock_irqrestore(&isp_hw_data.mac_array[port].lock, lock_flags);

	if (isp_hw_data.meta_attach_port == port) {
		ovisp23_notify_sof(0);
	}
	return ret;
}
#if 1
static int isp_write_overflow_handler(isp_port_e port)
{
	int                 ret = 0;
	hwisp_buf_t    *frame     = NULL;
	unsigned long       lock_flags;

    trace_hw_ovisp23_write_overflow(port); 

	cam_info("overflow port =%d",port);

	spin_lock_irqsave(&isp_hw_data.mac_array[port].lock, lock_flags);
	frame = get_buf_from_interworkq(port);
	if(frame)
	{
		//ispv3_hardware_set_ready(port);
		ovisp23_put_buf_to_idelq(port, frame);
	}

       frame = get_buf_from_interworkq(port);
	if(frame)
	{
		//ispv3_hardware_set_ready(port);
		ovisp23_put_buf_to_idelq(port, frame);
	}
	frame = ovisp23_get_buf_from_readyq(port);
	if(frame)
	{
		ispv3_hardware_update_addr(port,frame);
		put_buf_to_interworkq(port, frame);
	}

	spin_unlock_irqrestore(&isp_hw_data.mac_array[port].lock, lock_flags);

	return ret;
}
#endif
int isp_cmd_update_buffer_cmd(isp_port_e port)
{
        int                 ret = 0;
        hwisp_buf_t    *frame     = NULL;
        unsigned long       lock_flags;

        hwisp_stream_t* stm = NULL;
        stm = ovisp23_get_stream(port);
        if(stm==NULL){
            cam_err("no stream match to the port %d",port);
            return -1;
        }
        cam_debug("enter %s port = %d",__func__,port);

        spin_lock_irqsave(&isp_hw_data.mac_array[port].lock, lock_flags);
        frame = get_buf_from_interworkq(port);
        if(frame)
        {
            //ispv3_hardware_set_ready(port);
            ovisp23_put_buf_to_idelq(port, frame);
        }

        frame = get_buf_from_interworkq(port);
        if(frame)
        {
            //ispv3_hardware_set_ready(port);
            ovisp23_put_buf_to_idelq(port, frame);
        }

        frame = ovisp23_get_buf_from_readyq(port);
        if(frame)
        {
            ispv3_hardware_update_addr(port,frame);
            put_buf_to_interworkq(port,frame);
        } else {
            cam_err("%s, no more empty buffer !!!",  __func__);
            ret = -1;
        }

        spin_unlock_irqrestore(&isp_hw_data.mac_array[port].lock, lock_flags);
        return ret;
}

static void isp_update_output_addr(int index, hwisp_stream_buf_info_t *output_buf)
{
       u32 ptba = 0, ptva = 0;
       u8 port;

       /*ptba = HISI_RESERVED_SMMU_PHYMEM_BASE;*/
       /*ptva = HISI_IOMMU_IOVA_START;*/
       if (0 != hisi_iommu_get_info(&ptva,&ptba)){
           cam_err("ptba and ptva fail to get valid value");
           return;
       }
       port = output_buf->port.id;

	cam_debug("%s output iova=0x%x. port = %d", __func__, output_buf->y_addr_iommu, output_buf->port.id);
	cam_debug("%s output uvoffset->u=0x%x.", __func__, output_buf->u_addr_iommu);
	cam_debug("%s output uvoffset->v=0x%x.", __func__, output_buf->v_addr_iommu);

	MMU_SETREG32(REG_PORT_MMU_RDY_ADDR(port), 0x0);

	MMU_SETREG32(REG_PORT_MMU_PTBA_ADDR(port), ptba);
	MMU_SETREG32(REG_PORT_MMU_PTVA_ADDR(port), ptva);

	MMU_SETREG32(REG_PORT_MMU_TRANSID_ADDR(port), mmu_transid[1]);
	ISP_SETREG32(REG_PORT_MAC_TRANSID_ADDR(port), MMU_MAC_TRANSID(port % 2, mac_transid[1]));

	MMU_SETREG32(REG_PORT_MMU_AW0_ADDR(port), output_buf->y_addr_iommu);
	MMU_SETREG32(REG_PORT_MMU_AW1_ADDR(port), output_buf->u_addr_iommu);
	ISP_SETREG32(ISP_MAC_OUTPUT_ADDR(index), output_buf->y_addr_iommu);
	ISP_SETREG32(ISP_MAC_OUTPUT_U_ADDR(index), output_buf->u_addr_iommu);

	MMU_SETREG32(REG_PORT_MMU_RDY_ADDR(port), 0x1);

}

static void ispv3_update_input_addr(hwisp_stream_buf_info_t *input_buf)
{
       u32 reg_val;
       u32 ptba = 0, ptva = 0;
       u8 port;

       cam_debug("%s input iova=0x%x. port = %d", __func__, input_buf->y_addr_iommu, input_buf->port.id);
       cam_debug("%s input uvoffset->u=0x%x.", __func__, input_buf->u_addr_iommu);
       cam_debug("%s input uvoffset->v=0x%x.", __func__, input_buf->v_addr_iommu);

       /*config mmu registers*/
       /*ptba = HISI_RESERVED_SMMU_PHYMEM_BASE;*/
       /*ptva = HISI_IOMMU_IOVA_START;*/
       if (0 != hisi_iommu_get_info(&ptva,&ptba)){
		cam_err("ptba and ptva fail to get valid value");
		return;
	}
	port = input_buf->port.id;

	MMU_SETREG32(REG_PORT_MMU_RDY_ADDR(port), 0x0);

	MMU_SETREG32(REG_PORT_MMU_PTBA_ADDR(port), ptba);
    
	MMU_SETREG32(REG_PORT_MMU_PTVA_ADDR(port), ptva);

	MMU_GETREG32(REG_PORT_MMU_TRANSID_ADDR(port), reg_val);
	cam_debug("mmu transid 0x%x", reg_val);
	MMU_SETREG32(REG_PORT_MMU_TRANSID_ADDR(port),( (reg_val) | (1 << 19)));

	MMU_SETREG32(REG_PORT_MMU_AR0_ADDR(port), input_buf->y_addr_iommu);
	ISP_SETREG32(ISP_MAC_INPUT_ADDR, input_buf->y_addr_iommu);

	MMU_SETREG32(REG_PORT_MMU_RDY_ADDR(port), 0x1);
}

static u8 ispv3_convert_input_fmt(u32 fmt)
{
	u8 isp_fmt = 0;
	/* fmt [2:0]:
	 * 0 for RAW8,
	 * 1 for RAW10,
	 * 2 for RAW12,
	 * 3 for RAW14,
	 * 4 for YUV422,
	 * 5 for RGB565,
	 * 6 for RGB888
	 */

	switch (fmt) {
	case V4L2_PIX_FMT_RAW8:
		isp_fmt = 0;
		break;
	case V4L2_PIX_FMT_RAW10:
		isp_fmt = 1;
		break;
	case V4L2_PIX_FMT_RAW12:
		isp_fmt = 2;
		break;
	case V4L2_PIX_FMT_RAW14:
		isp_fmt = 3;
		break;
	case V4L2_PIX_FMT_YUYV:
		isp_fmt = 4;
		break;
	default:
		cam_err("Bad format: %d", fmt);
		break;
	}

	return isp_fmt;
}

static u8 ispv3_convert_output_fmt(u32 fmt)
{
	u8 isp_fmt = 0;

	switch (fmt) {
	case V4L2_PIX_FMT_YUYV:
		isp_fmt = 4;
		break;

	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		isp_fmt = 5;
		break;

	case V4L2_PIX_FMT_YVU420:
	case V4L2_PIX_FMT_YUV420:
		isp_fmt = 8;
		break;

	default:
		cam_err("Bad format: %d", fmt);
		isp_fmt = 1; /* default use RAW10 */
		break;
	}


	return isp_fmt;
}

static void dump_process_raw_cmdset_regs(void)
{
	cam_info("The Process RAW command (0x6)parameters is:\n");
	cam_info("ISP_INPUT_TYPE 0x%0x", ISP_GETREG16(ISP_INPUT_TYPE));
	cam_info("ISP_INPUT_WIDTH 0x%0x", ISP_GETREG16(ISP_INPUT_WIDTH));
	cam_info("ISP_INPUT_HEIGHT 0x%0x", ISP_GETREG16(ISP_INPUT_HEIGHT));

	cam_info("ISP_ZOOMIN_RATIO 0x%0x \n", ISP_GETREG16(ISP_ZOOMIN_RATIO));

	cam_info("ISP_OUTPORT_SELECTION 0x%0x", ISP_GETREG16(ISP_OUTPORT_SELECTION));
	cam_info("ISP_OUT_TYPE 0x%0x", ISP_GETREG16(ISP_OUT_TYPE(0)));
	cam_info("ISP_OUT_WIDTH 0x%0x", ISP_GETREG16(ISP_OUT_WIDTH(0)));
	cam_info("ISP_OUT_HEIGHT 0x%0x", ISP_GETREG16(ISP_OUT_HEIGHT(0)));
	cam_info("ISP_OUT_MEMORY_WIDTH 0x%0x", ISP_GETREG16(ISP_OUT_MEM_WIDTH(0)));

	cam_info("ISP_READBACK_PORT_SELECTION 0x%0x", ISP_GETREG16(ISP_READBACK_PORT_SELECTION));
	cam_info("ISP_READBACK_WIDTH 0x%0x", ISP_GETREG16(ISP_READBACK_WIDTH));
	cam_info("ISP_READBACK_HEIGHT 0x%0x", ISP_GETREG16(ISP_READBACK_HEIGHT));
	cam_info("ISP_READBACK_MEM_WIDTH 0x%0x", ISP_GETREG16(ISP_READBACK_MEM_WIDTH));

	cam_info("ISP_MAC_OUTPUT_ADDR_1 0x%0x", ISP_GETREG16(ISP_MAC_OUTPUT_ADDR(0)));
	cam_info("ISP_MAC_OUTPUT_U_ADDR_1 0x%0x", ISP_GETREG16(ISP_MAC_OUTPUT_U_ADDR(0)));
	cam_info("ISP_MAC_OUTPUT_V_ADDR_1 0x%0x", ISP_GETREG16(ISP_MAC_OUTPUT_V_ADDR(0)));

	cam_info("ISP_MAC_INPUT_ADDR 0x%0x", ISP_GETREG16(ISP_MAC_INPUT_ADDR));

	cam_info("COMMAND_REG1 0x%0x \n", ISP_GETREG8(COMMAND_REG1));
}

static void isp_save_raw_info(raw_buffer_info_t *raw_info, int flow)
{
	raw_info->exposure = ISP_GETREG32(ISP_EXPOSURE_OUTPUT_ADDR(flow));
	raw_info->gain = ISP_GETREG16(ISP_GAIN_OUTPUT_ADDR(flow));
	raw_info->mean_y = ISP_GETREG16(ISP_MEAN_Y_OUTPUT_ADDR_ADDR(flow));
	raw_info->raw_stretch_low_level = ISP_GETREG16(ISP_RAW_STRETCH_LOW_LEVEL_OUTPUT_ADDR(flow));
	raw_info->raw_stretch_gain = ISP_GETREG16(ISP_RAW_STRETCH_GAIN_OUTPUT_ADDR(flow));
	raw_info->b_gain = ISP_GETREG16(ISP_BGAIN_OUTPUT_ADDR(flow));
	raw_info->g_gain = ISP_GETREG16(ISP_GGAIN_OUTPUT_ADDR(flow));
	raw_info->r_gain = ISP_GETREG16(ISP_RGAIN_OUTPUT_ADDR(flow));
	raw_info->b_offset = ISP_GETREG16(ISP_B_OFFSET_OUTPUT_ADDR(flow));
	raw_info->g_offset = ISP_GETREG16(ISP_G_OFFSET_OUTPUT_ADDR(flow));
	raw_info->r_offset = ISP_GETREG16(ISP_R_OFFSET_OUTPUT_ADDR(flow));
	raw_info->lens_online_ba = ISP_GETREG16(ISP_LENS_ONLINE_BA_OUTPUT_ADDR(flow));
	raw_info->lens_online_br = ISP_GETREG16(ISP_LENS_ONLINE_BR_OUTPUT_ADDR(flow));
	raw_info->lens_profile = ISP_GETREG16(ISP_LENS_PROFILE_OUTPUT_ADDR(flow));
}



static void isp_restore_raw_info(raw_buffer_info_t *raw_info, int flow)
{
	cam_info("raw_info expo=%x gain=%x mean_y=%x raw_stretch=%x raw_stretch_gain=%x",
		raw_info->exposure, raw_info->gain, raw_info->mean_y,
		raw_info->raw_stretch_low_level, raw_info->raw_stretch_gain);

	cam_info("raw_info b_gain=%x g_gain=%x r_gain=%x b_offset=%x g_offset=%x r_offset=%x",
		raw_info->b_gain, raw_info->g_gain, raw_info->r_gain,
		raw_info->b_offset, raw_info->g_offset, raw_info->r_offset);

	cam_info("raw_info lens_online_ba=%x lens_online_br=%x lens_profile=%x",
		raw_info->lens_online_ba, raw_info->lens_online_br, raw_info->lens_profile);

	ISP_SETREG32(ISP_EXPOSURE_INPUT_ADDR(flow), raw_info->exposure);
	ISP_SETREG16(ISP_GAIN_INPUT_ADDR(flow), raw_info->gain);
	ISP_SETREG16(ISP_MEAN_Y_INPUT_ADDR_ADDR(flow), raw_info->mean_y);
	ISP_SETREG16(ISP_RAW_STRETCH_LOW_LEVEL_INPUT_ADDR(flow), raw_info->raw_stretch_low_level);
	ISP_SETREG16(ISP_RAW_STRETCH_GAIN_INPUT_ADDR(flow), raw_info->raw_stretch_gain);
	ISP_SETREG16(ISP_BGAIN_INPUT_ADDR(flow), raw_info->b_gain);
	ISP_SETREG16(ISP_GGAIN_INPUT_ADDR(flow), raw_info->g_gain);
	ISP_SETREG16(ISP_RGAIN_INPUT_ADDR(flow), raw_info->r_gain);
	ISP_SETREG16(ISP_B_OFFSET_INPUT_ADDR(flow), raw_info->b_offset);
	ISP_SETREG16(ISP_G_OFFSET_INPUT_ADDR(flow), raw_info->g_offset);
	ISP_SETREG16(ISP_R_OFFSET_INPUT_ADDR(flow), raw_info->r_offset);
	ISP_SETREG16(ISP_LENS_ONLINE_BA_INPUT_ADDR(flow), raw_info->lens_online_ba);
	ISP_SETREG16(ISP_LENS_ONLINE_BR_INPUT_ADDR(flow), raw_info->lens_online_br);
	ISP_SETREG16(ISP_LENS_PROFILE_INPUT_ADDR(flow), raw_info->lens_profile);

}

int isp_reprocess_cmdset(struct reprocess_param_list *reprocess_params)
{
	u16 in_fmt = 0;
	u16 out_fmt = 0;
	u32 in_width, in_height, out_width, out_height;
	u8 pipeline;
	raw_buffer_info_t *raw_info;

	cam_info("enter %s", __func__);
	cam_info("reprocess_params list:");
	cam_info("input width %d, input height %d, output width %d, output height %d, "
		 "pipeline %d, zoom ratio 0x%04x, readport %d, writeport %d",
		reprocess_params->input_width, reprocess_params->input_height,
		reprocess_params->output_width, reprocess_params->output_height,
		reprocess_params->reprocess_pipeline, reprocess_params->zoom_ratio,
		reprocess_params->input_buf_info.port.id,
		reprocess_params->output_buf_info.port.id);

	//mutex_lock(&cmdset_mutex);

	in_width = reprocess_params->input_width;
	in_height = reprocess_params->input_height;
	out_width = reprocess_params->output_width;
	out_height = reprocess_params->output_height;

	pipeline = reprocess_params->reprocess_pipeline;

	raw_info = &reprocess_params->raw_buf_info;
	isp_restore_raw_info(raw_info, pipeline);

	in_fmt = ispv3_convert_input_fmt(reprocess_params->input_fmt);

	in_fmt |= (INPUT_TYPE_MEMORY | INPUT_TYPE_ISP_PROCESS_ENABLE);

	out_fmt = ispv3_convert_output_fmt(reprocess_params->output_fmt);
	cam_info("in_fmt: %d, out_fmt: %d", in_fmt, out_fmt);
	if (reprocess_params->output_fmt == V4L2_PIX_FMT_NV21) {
		ISP_SETREG8(REG_ISP_TOP7(pipeline), REG_UV_ORDER_V_AHEAD);
	} else if (reprocess_params->output_fmt == V4L2_PIX_FMT_NV12) {
		ISP_SETREG8(REG_ISP_TOP7(pipeline), REG_UV_ORDER_U_AHEAD);
	} else if (reprocess_params->output_fmt == V4L2_PIX_FMT_YUYV) {
		ISP_SETREG8(REG_ISP_TOP7(pipeline), REG_UV_ORDER_U_AHEAD);
	}

	ISP_SETREG16(ISP_ZOOMIN_RATIO, reprocess_params->zoom_ratio);

	CMD_SET_ISP_IN_FMT_SIZE(in_fmt, in_width, in_height);

	/* setup output attributes: configure write port */
	ISP_SETREG16(ISP_OUTPORT_SELECTION, 1 << reprocess_params->output_buf_info.port.id);
	CMD_SET_OUTPORT_PARAMS(0, out_fmt, out_width, out_height,
				out_width, out_width / 2);

	/* configure write address. Attention:should configure output address firstly!!!! */
	isp_update_output_addr(0, &reprocess_params->output_buf_info);

	/* ISP input port, RAW10 */
	ISP_SETREG16(ISP_READBACK_PORT_SELECTION, 1 << (reprocess_params->input_buf_info.port.id - ISP_PORT_READ0));
	CMD_SET_READPORT_PARAMS(in_width, in_height, in_width);

	/* configure read address */
	ispv3_update_input_addr(&reprocess_params->input_buf_info);

	ISP_SETREG8(COMMAND_REG1, pipeline);

	ISP_SETREG8(COMMAND_REG2, 1);

	/* REG7[0]:1-enable pingpang buffer; REG7[1]:1-enable single port ready */
	ISP_SETREG8(COMMAND_REG7, 0x02);

	dump_process_raw_cmdset_regs();
	/* send out cmdset */
	ISP_SETREG8(COMMAND_REG0, CMD_PROCESS_RAW);

	//mutex_unlock(&cmdset_mutex);

	return 0;
}


static void  hw_isr_do_tasklet(unsigned long data)
{
    unsigned long lock_flags = 0;
    u8 mac1_s0 = 0, mac1_s1 = 0, mac2_s0 = 0, mac2_s1 = 0, mac3_s0 = 0, mac3_s1 = 0;
    u8 pipe0_status = 0, pipe1_status = 0;

    spin_lock_irqsave(&isp_hw_data.irq_status_lock, lock_flags);

    swap(mac1_s0, isp_hw_data.irq_val.mac1_irq_status_s0);
    swap(mac1_s1, isp_hw_data.irq_val.mac1_irq_status_s1);
    swap(mac2_s0, isp_hw_data.irq_val.mac2_irq_status_s0);
    swap(mac2_s1, isp_hw_data.irq_val.mac2_irq_status_s1);
    swap(mac3_s0, isp_hw_data.irq_val.mac3_irq_status_s0);
    swap(mac3_s1, isp_hw_data.irq_val.mac3_irq_status_s1);
    swap(pipe0_status, isp_hw_data.irq_val.irq_status_4);
    swap(pipe1_status, isp_hw_data.irq_val.irq_status_3);

    spin_unlock_irqrestore(&isp_hw_data.irq_status_lock, lock_flags);

    /* printk("int status mac1_s0 = %x mac2_s0 = %x mac3_s0 = %x\n",mac1_s0,mac2_s0,mac3_s0); */
    /* printk("int status mac1_s1 = %x mac2_s1 = %x mac3_s1 = %x\n",mac1_s1,mac2_s1,mac3_s1); */
    /* printk("pipe0_status = %x, pipe1_status = %x\n", pipe0_status, pipe1_status); */

    //mac1
    /*done*/
    if (mac1_s0 & INT_ISP_MAC1_DONE0) {
        isp_write_done_handler(ISP_PORT_WRITE0);
    }

    /*start*/
    if (mac1_s0 & INT_ISP_MAC1_START0) {
        isp_write_start_handler(ISP_PORT_WRITE0);
    }

    /* drop */
    if (mac1_s0 & INT_ISP_MAC1_DROP0) {
        isp_write_drop_handler(ISP_PORT_WRITE0);
    }

    /* FIFO overflow */
    if (mac1_s0 & INT_ISP_MAC1_OVERFLOW0) {
        cam_warn("overflow port =%d",ISP_PORT_WRITE0);
        isp_write_overflow_handler(ISP_PORT_WRITE0);
    }

    /*done*/
    if (mac1_s1 & INT_ISP_MAC1_DONE1) {
        isp_write_done_handler(ISP_PORT_WRITE1);
    }

    if (mac1_s1 & INT_ISP_MAC1_START1) {
        isp_write_start_handler(ISP_PORT_WRITE1);
    }

    /* drop */
    if (mac1_s1 & INT_ISP_MAC1_DROP1) {
        isp_write_drop_handler(ISP_PORT_WRITE1);
    }

    //mac2
    /*done*/
    if (mac2_s0 & INT_ISP_MAC2_DONE0) {
        isp_write_done_handler(ISP_PORT_WRITE2);
    }

    /*start*/
    if (mac2_s0 & INT_ISP_MAC2_START0) {
        isp_write_start_handler(ISP_PORT_WRITE2);
    }

    /* drop */
    if (mac2_s0 & INT_ISP_MAC2_DROP0) {
        isp_write_drop_handler(ISP_PORT_WRITE2);
    }

    /* FIFO overflow */
    if (mac2_s0 & INT_ISP_MAC2_OVERFLOW0) {
        cam_info("mac2 overflow irq");
        isp_write_overflow_handler(ISP_PORT_WRITE2);
    }

    /*done*/
    if (mac2_s1 & INT_ISP_MAC2_DONE1) {
        isp_write_done_handler(ISP_PORT_WRITE3);
    }

    /* mac1 start1 */
    if (mac2_s1 & INT_ISP_MAC2_START1) {
        isp_write_start_handler(ISP_PORT_WRITE3);
    }

    /* drop */
    if (mac2_s1 & INT_ISP_MAC2_DROP1) {
        isp_write_drop_handler(ISP_PORT_WRITE3);
    }

    //mac3
    if (mac3_s0 & INT_ISP_MAC3_DONE0) {
        cam_info("mac3 done irq");
    }

    /*start*/
    if (mac3_s0 & INT_ISP_MAC3_START0) {
        cam_info("mac3 start irq");
    }

    /* drop */
    if (mac3_s0 & INT_ISP_MAC3_DROP0) {
        cam_info("mac3 drop irq");
    }

    /* FIFO overflow */
    if (mac3_s0 & INT_ISP_MAC3_OVERFLOW0) {
        cam_info("mac3 overflow irq");
    }

    /*done*/
    if (mac3_s1 & INT_ISP_MAC3_DONE1) {
    }

    if (mac3_s1 & INT_ISP_MAC3_START1) {
    }

    /* drop */
    if (mac3_s1 & INT_ISP_MAC3_DROP1) {
    }

    /* PIPELINE0 EOF */
    if(pipe0_status & ISP_PIPE0_EOF_IDI) {
        ovisp23_notify_eof(0);
    }

    /* PIPELINE1 EOF */
    if(pipe1_status & ISP_PIPE1_EOF_IDI) {
        ovisp23_notify_eof(1);
    }

    /* PIPELINE0 SOF */
    if(pipe0_status & ISP_PIPE0_SOF_IDI) {
        /* ovisp23_notify_sof(0); */
    }

    /* PIPELINE1 SOF */
    if(pipe1_status & ISP_PIPE1_SOF_IDI) {
        ovisp23_notify_sof(1);
    }

}

int hw_alloc_firmware_memory(void)
{
	isp_firmware_addr = kzalloc(FIRMWARE_MEM_SIZE, GFP_KERNEL);
	if (0 == isp_firmware_addr) {
		cam_err("%s kzalloc fail!", __func__);
		return -ENOMEM;
	} else {
		return 0;
	}
}
void hw_free_firmware_memory(void)
{
	kfree(isp_firmware_addr);
	isp_firmware_addr = NULL;
}

