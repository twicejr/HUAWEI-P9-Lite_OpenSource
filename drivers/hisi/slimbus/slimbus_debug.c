/*
 *  slimbus is a kernel driver which is used to manager SLIMbus devices
 *  Copyright (C) 2014  Hisilicon

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/delay.h>

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/sysfs.h>

#include "slimbus.h"

#define CLASS_NAME    "slimbus_debug"

//#define __IMAGE_DOWN_TEST 1
#ifdef __IMAGE_DOWN_TEST
static uint32_t       simgdown = 0;
static uint64_t       gdmabaseaddr = 0;
static uint16_t       gimagearray[2000] = {0};
#endif

static struct class  *sclass;

static uint32_t       sregpagerd = 0;
static uint32_t       sregrd = 0;
static uint32_t       sregwr = 0;
static uint32_t       sswitchframer = 0;
static uint32_t       sclockgear = 10;
static uint32_t       spauseclock = 0;
static uint32_t       schannelctrl = 0;
static uint32_t       stracktype   = 0;
static uint32_t       sregtest = 0;
static uint32_t       sbusreset = 0;
static uint32_t       smixtest  = 0;
static uint32_t       srequestinfo = 0;
static uint32_t       scopyright_error = 0;
static uint32_t       sreg8_rd_error   = 0;
static uint32_t       sreg32_rd_error  = 0;

static uint32_t       srdwrerr_logcount = 0;
static uint32_t       srdwrerr_logtimes = 0;
static uint32_t       slostms_times     = 0;

static uint64_t       gregvalue = 0;
static slimbus_slice_size_t gslicesize = 0;
static uint32_t       sdevice_type = 0;


extern slimbus_bus_config_t bus_config[SLIMBUS_BUS_CONFIG_MAX];


#ifdef __IMAGE_DOWN_TEST
static ssize_t imgdown_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "usage: echo param>simgdown \n");
	ret += sprintf(buf+ret, "para: \n1: configure asp dma;\n");
	ret += sprintf(buf+ret, "2: configure 6402 dma;\n");
	ret += sprintf(buf+ret, "3: start and active slimbus image download channel;\n");
	ret += sprintf(buf+ret, "4: deactive and remove slimbus image download channel;\n");
	ret += sprintf(buf+ret, "else: set startvalue write to 6402 ocram;\n");

	return ret;
}

static ssize_t imgdown_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	uint32_t startvalue = 0;
	uint32_t ret = 0;
	uint32_t i = 0;
	uint32_t val = 0;

	sscanf(buf, "0x%x", &simgdown);

	printk(KERN_EMERG"[%s:%d] simgdown:%x!\n", __FUNCTION__, __LINE__, simgdown);

	switch (simgdown) {
		case 1:
			printk(KERN_EMERG"[%s:%d] configure asp dma!\n", __FUNCTION__, __LINE__);

			gdmabaseaddr = ioremap(0xe804b000, 0xa00);
			writel(0x400, gdmabaseaddr + 0x810);
			writel(gimagearray, gdmabaseaddr + 0x814);
			writel(0xe8051000, gdmabaseaddr + 0x818);
			writel(0x83322007, gdmabaseaddr + 0x81c);

			iounmap(gdmabaseaddr);

			break;
		case 2:
			printk(KERN_EMERG"[%s:%d] configure 6402 dma!\n", __FUNCTION__, __LINE__);
			slimbus_write_1byte(0x20007040, 0x3);
			slimbus_write_1byte(0x20007214, 0xff);
			slimbus_write_1byte(0x200072f2, 0x3);
			slimbus_write_1byte(0x20007045, 0xff);
			slimbus_write_1byte(0x20007052, 0x50);
			slimbus_write_4byte(0x20000810, 0x200);
			slimbus_write_4byte(0x20000814, 0x20010000);
			slimbus_write_4byte(0x20000818, 0x10000000);
			slimbus_write_4byte(0x2000081c, 0x47711007);
			slimbus_write_1byte(0x200073d8, 0x1);
			slimbus_write_1byte(0x20007031, 0x11);

			ret = slimbus_bus_configure(SLIMBUS_BUS_CONFIG_IMGDOWN);
			break;
		case 3:
			printk(KERN_EMERG"[%s:%d] configure and active slimbus channel!\n", __FUNCTION__, __LINE__);
			ret = slimbus_track_configure(sdevice_type, SLIMBUS_TRACK_IMAGE_LOAD, NULL);
			ret = slimbus_track_activate(sdevice_type, SLIMBUS_TRACK_IMAGE_LOAD);

			break;

		case 4:
			printk(KERN_EMERG"[%s:%d] deactivate and remove slimbus channel!\n", __FUNCTION__, __LINE__);

			slimbus_track_deactivate(sdevice_type, SLIMBUS_TRACK_IMAGE_LOAD);
			slimbus_track_remove(sdevice_type, SLIMBUS_TRACK_IMAGE_LOAD);
			ret = slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
			break;

		default:
			startvalue = simgdown;
			for (i=0; i<2000; i+=2) {
				gimagearray[i] = startvalue + i/2;
				gimagearray[i+1] = startvalue + i/2;
			}
			printk(KERN_EMERG"[%s:%d] startvalue:%x!\n", __FUNCTION__, __LINE__, startvalue);
			break;
	}

	return size;
}
#endif

static int64_t get_timeus()
{
	struct timeval time;
	int64_t timeus = 0;

	do_gettimeofday(&time);
	timeus = 1000000 * time.tv_sec + time.tv_usec;

	return timeus;
}

static ssize_t regpagerd_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t ret = 0;

	if (sregpagerd >= 0x10000000 && sregpagerd <= 0x20008000) {
		ret = sprintf(buf, "addr:%x:\n", sregpagerd);

		if ((sregpagerd >= 0x10000000 && sregpagerd <= 0x10001000)
			|| (sregpagerd >= 0x20000700 && sregpagerd < 0x20007000)){
			for (i=0; i<240; i+=16) {
				ret += sprintf(buf+ret, " %4x %4x %4x %4x \n",
							slimbus_read_4byte(sregpagerd+i), slimbus_read_4byte(sregpagerd+i+4),
							slimbus_read_4byte(sregpagerd+i+8), slimbus_read_4byte(sregpagerd+i+12));
				msleep(20);
			}
		}

		if (sregpagerd >= 0x20007000 && sregpagerd <= 0x20008000) {
			ret += sprintf(buf+ret, "begin\n");
			for (j=0; j<=0x1ff; j+=16) {
				for (i=j; i<j+16; i++) {
					ret += sprintf(buf+ret, " %3x ",slimbus_read_1byte(sregpagerd+i));
				}
				ret += sprintf(buf+ret, "\n");
			}
		}
		ret += sprintf(buf+ret, "end\n");
	}else {
		ret += sprintf(buf+ret, "usage: echo regaddr>sregpagerd\n");
		ret += sprintf(buf+ret, "sregpagerd:%x!\n", sregpagerd);
	}

	return ret;
}

static ssize_t regpagerd_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &sregpagerd);

	return size;
}

static ssize_t regrd_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	if (sregrd >= 0x20007000 && sregrd < 0x20008000) {
		gregvalue = slimbus_read_1byte(sdevice_type, sregrd);
		slimbus_read_pageaddr();

		ret = sprintf(buf, "sregrd:0x%x, value:%llx!\n", sregrd, gregvalue);
	} else {
		ret = sprintf(buf, "usage: echo param>sregrd\n");
		ret += sprintf(buf+ret, "param: 0xregaddr\n");
	}

	printk(KERN_ERR"[%s:%d] sregrd (%x %llx) !\n", __FUNCTION__, __LINE__, sregrd, gregvalue);

	return ret;
}

static ssize_t regrd_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &sregrd);

	return size;
}
static ssize_t regwr_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	int ret = 0;

	ret = sprintf(buf, "usage: echo param>sregrd\n");
	ret += sprintf(buf+ret, "param: 0xregaddr 0xvalue\n");

	return ret;
}

static ssize_t regwr_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x 0x%x", &sregwr, &gregvalue);

	if (sregwr >= 0x20007000 && sregwr <= 0x20008000) {
		slimbus_write_1byte(sdevice_type, sregwr, gregvalue);

		printk(KERN_ERR"[%s:%d] sregwr (%x %llx) !\n", __FUNCTION__, __LINE__, sregwr, gregvalue);
	} else {
		printk(KERN_ERR"[%s:%d] param error! sregwr (%x %llx) !", __FUNCTION__, __LINE__, sregwr, gregvalue);
	}

	return size;
}


static ssize_t switchframer_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "sswitchframer:0x%x!\n", sswitchframer);
	ret += sprintf(buf+ret, "usage: echo param>sswitchframer\n");
	ret += sprintf(buf+ret, "param: \n");
	ret += sprintf(buf+ret, "0x1: switch to soc \n");
	ret += sprintf(buf+ret, "0x2: switch to codec \n");

	return ret;
}

static ssize_t switchframer_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &sswitchframer);

	printk(KERN_ERR"[%s:%d] sswitchframer:0x%x!\n", __FUNCTION__, __LINE__, sswitchframer);

	switch (sswitchframer) {
		case 1:
			slimbus_switch_framer(sdevice_type, SLIMBUS_FRAMER_SOC);
			break;
		case 2:
			slimbus_switch_framer(sdevice_type, SLIMBUS_FRAMER_CODEC);

			break;
		default:
			printk(KERN_ERR"[%s:%d] default!\n", __FUNCTION__, __LINE__);
			break;
	}

	return size;
}

static ssize_t devtype_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "sdevicetype:0x%x!\n", sdevice_type);
	ret += sprintf(buf+ret, "usage: echo param>sdevice_type\n");

	return ret;
}

static ssize_t devtype_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &sdevice_type);

	printk(KERN_ERR"[%s:%d] sdevice_type:0x%x!\n", __FUNCTION__, __LINE__, sdevice_type);

	return size;
}


static ssize_t clockgear_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "sclockgear:0x%x!\n", sclockgear);
	ret += sprintf(buf+ret, "usage: echo param>sclockgear\n");

	return ret;
}

static ssize_t clockgear_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	slimbus_bus_config_t *bus_config;
	sscanf(buf, "0x%x", &sclockgear);

	bus_config = slimbus_bus_config_get();
	bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = sclockgear;

	printk(KERN_ERR"[%s:%d] sclockgear:%x,!\n", __FUNCTION__, __LINE__, sclockgear);
	slimbus_bus_configure(SLIMBUS_BUS_CONFIG_SWITCH_FRAMER);

	return size;
}

static ssize_t channelctrl_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "schannelctrl:0x%x 0x%x!\n", schannelctrl, stracktype);
	ret += sprintf(buf+ret, "usage: echo param>schannelctrl\n");
	ret += sprintf(buf+ret, "param: schannelctrl\n");
	ret += sprintf(buf+ret, "0x1: deactive  channel!\n");
	ret += sprintf(buf+ret, "0x2: active  channel!\n");
	ret += sprintf(buf+ret, "0x3: deactive/active  channel!\n");
	ret += sprintf(buf+ret, "0x3: deactive->remove->configure->active  channel!\n");
	ret += sprintf(buf+ret, "param: stracktype\n");
	ret += sprintf(buf+ret, "0x0:audio play; 0x1:audio record; 0x2:voice down; 0x3:voice up\n");

	return ret;
}

static ssize_t channelctrl_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x 0x%x", &schannelctrl, &stracktype);

	printk(KERN_ERR"[%s:%d] schannelctrl:%x, stracktype:%x,!\n", __FUNCTION__, __LINE__, schannelctrl,stracktype);

	switch (schannelctrl)
	{
		case 1:
			slimbus_track_deactivate(sdevice_type, stracktype);
			break;
		case 2:
			slimbus_track_activate(sdevice_type, stracktype);
			break;
		case 3:
			slimbus_track_deactivate(sdevice_type, stracktype);
			slimbus_track_activate(sdevice_type, stracktype);
			break;
		case 4:
			slimbus_track_deactivate(sdevice_type, stracktype);
			slimbus_track_remove(sdevice_type, stracktype);
			break;
		case 5:
			slimbus_track_configure(sdevice_type, stracktype, NULL);
			slimbus_track_activate(sdevice_type, stracktype);
			break;
		default:
			break;
	}

	return size;
}

static ssize_t pauseclock_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "spauseclock:0x%x!\n", spauseclock);
	ret += sprintf(buf+ret, "0x2: slimbus clk pause!\n");
	ret += sprintf(buf+ret, "himm 0xe8050020 0x8 to wakeup clk!\n");

	return ret;
}

static ssize_t pauseclock_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &spauseclock);

	printk(KERN_ERR"[%s:%d] g_pause_clock:%x!\n", __FUNCTION__, __LINE__, spauseclock);

	switch (spauseclock)
	{
		case 0:
			slimbus_pause_clock(sdevice_type, SLIMBUS_RT_FAST_RECOVERY);
		case 1:
			slimbus_pause_clock(sdevice_type, SLIMBUS_RT_CONSTANT_PHASE_RECOVERY);
		case 2:
			slimbus_pause_clock(sdevice_type, SLIMBUS_RT_UNSPECIFIED_DELAY);
		default:
			printk(KERN_ERR"[%s:%d] unsupport restarttime:%x!\n", __FUNCTION__, __LINE__, spauseclock);
			break;
	}

	return size;
}

static ssize_t regtest_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "sregtest:0x%x!\n", sregtest);
	ret += sprintf(buf+ret, "scopyright_error:0x%x!\n", scopyright_error);
	ret += sprintf(buf+ret, "sreg8_rd_error:0x%x!\n", sreg8_rd_error);
	ret += sprintf(buf+ret, "sreg32_rd_error:0x%x!\n", sreg32_rd_error);

	return ret;
}

static ssize_t regtest_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	int64_t start_time, end_time;
	int val = 0;
	int i = 0;

	scopyright_error = 0;
	sreg8_rd_error   = 0;
	sreg32_rd_error  = 0;

	sscanf(buf, "0x%x", &sregtest);

	start_time = get_timeus();
	for (i=0; i<1000; i++) {
		val = slimbus_read_1byte(0x20007000);
		if (i<=4) {
			printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
		}
		if (val != 0x11) {
			scopyright_error++;
			if (scopyright_error <= 4) {
				printk(KERN_ERR"[%s:%d] val:%x i:%x ! \n", __FUNCTION__, __LINE__, val, i);
			}
		}
	}
	end_time = get_timeus();
	printk(KERN_ERR"[%s:%d], read_1byte 1000s use %lld us!  (%lld, %lld) \n", __FUNCTION__, __LINE__, end_time-start_time, start_time, end_time);

	start_time = get_timeus();
	for (i=0; i<1000; i++) {
		slimbus_write_1byte(0x2000703a, i);
		val = slimbus_read_1byte(0x2000703a);
		if (i<=4) {
			printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
		}

		if ((i & 0xff) != val) {
			sreg8_rd_error++;
			if (sreg8_rd_error <= 4) {
				printk(KERN_ERR"[%s:%d] val:%x i:%x ! \n", __FUNCTION__, __LINE__, val, i);
			}
		}

	}
	end_time = get_timeus();
	printk(KERN_ERR"[%s:%d], write_1byte 1000s use %lld us!  (%lld, %lld) \n",__FUNCTION__, __LINE__,  end_time-start_time, start_time, end_time);

	start_time = get_timeus();
	for (i=0; i<1000; i++) {
		val = slimbus_read_4byte(sregtest);
		if (i<=4) {
			printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
		}
	}
	end_time = get_timeus();
	printk(KERN_ERR"[%s:%d], read_4byte 1000s use %lld us!  (%lld, %lld) \n",__FUNCTION__, __LINE__,  end_time-start_time, start_time, end_time);

	start_time = get_timeus();
	for (i=0; i<1000; i++) {
		slimbus_write_4byte(sregtest, i);
		val = slimbus_read_4byte(sregtest);
		if (i<=4) {
			printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
		}

		if (val != i) {
			sreg32_rd_error++;
			if (sreg32_rd_error <= 4) {
				printk(KERN_ERR"[%s:%d] val:%x i:%x ! \n", __FUNCTION__, __LINE__, val, i);
			}
		}
	}
	end_time = get_timeus();
	printk(KERN_ERR"[%s:%d], write_4byte 1000s use %lld us!  (%lld, %lld) \n", __FUNCTION__, __LINE__, end_time-start_time, start_time, end_time);

	return size;
}

static ssize_t busreset_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "sbusreset:0x%x!\n", sbusreset);

	return ret;
}

static ssize_t busreset_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &sbusreset);

	printk(KERN_ERR"[%s:%d] sbusreset:0x%x ! \n", __FUNCTION__, __LINE__, sbusreset);

	if (sbusreset == 1) {
		slimbus_drv_reset_bus();
	}

	return size;
}

static ssize_t mixtest_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "smixtest:0x%x sregtest:0x%x stracktype:0x%x!\n", smixtest, sregtest, stracktype);

	return ret;
}

static ssize_t mixtest_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	int64_t start_time, end_time;
	int val = 0;
	int i = 0;

	sscanf(buf, "0x%x 0x%x 0x%x", &smixtest, &sregtest, &stracktype);

	printk(KERN_ERR"[%s:%d] smixtest:0x%x sregtest:0x%x stracktype:0x%x! \n", __FUNCTION__, __LINE__, smixtest, sregtest, stracktype);

	if (smixtest == 1) {
		scopyright_error = 0;
		sreg8_rd_error   = 0;
		sreg32_rd_error  = 0;

		start_time = get_timeus();
		for (i=0; i<1000; i++) {
			val = slimbus_read_1byte(0x20007000);
			if (i<=4) {
				printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
			}
			if (val != 0x11) {
				scopyright_error++;
				if (scopyright_error <= 4) {
					printk(KERN_ERR"[%s:%d] val:%x i:%x ! \n", __FUNCTION__, __LINE__, val, i);
				}
			}
		}
		end_time = get_timeus();
		printk(KERN_ERR"[%s:%d], read_1byte:0x20007000 1000s use %lld us!  (%lld, %lld) \n", __FUNCTION__, __LINE__, end_time-start_time, start_time, end_time);

		start_time = get_timeus();
		for (i=0; i<1000; i++) {
			slimbus_write_1byte(0x2000703a, i);
			val = slimbus_read_1byte(0x2000703a);
			if (i<=4) {
				printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
			}

			if ((i & 0xff) != val) {
				sreg8_rd_error++;
				if (sreg8_rd_error <= 4) {
					printk(KERN_ERR"[%s:%d] val:%x i:%x ! \n", __FUNCTION__, __LINE__, val, i);
				}
			}
		}

		end_time = get_timeus();
		printk(KERN_ERR"[%s:%d], write_1byte:0x2000703a 1000s use %lld us!  (%lld, %lld) \n",__FUNCTION__, __LINE__,  end_time-start_time, start_time, end_time);

		start_time = get_timeus();
		for (i=0; i<1000; i++) {
			val = slimbus_read_4byte(sregtest);
			if (i<=4) {
				printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
			}
		}
		end_time = get_timeus();
		printk(KERN_ERR"[%s:%d], read_4byte:0x%x 1000s use %lld us!  (%lld, %lld) \n",__FUNCTION__, __LINE__,  sregtest, end_time-start_time, start_time, end_time);

		start_time = get_timeus();
		for (i=0; i<1000; i++) {
			slimbus_write_4byte(sregtest, i);
			val = slimbus_read_4byte(sregtest);
			if (i<=4) {
				printk(KERN_ERR"[%s:%d] %x! \n", __FUNCTION__, __LINE__, val);
			}

			if (val != i) {
				sreg32_rd_error++;
				if (sreg32_rd_error <= 4) {
					printk(KERN_ERR"[%s:%d] val:%x i:%x ! \n", __FUNCTION__, __LINE__, val, i);
				}
			}
		}
		end_time = get_timeus();
		printk(KERN_ERR"[%s:%d], write_4byte:0x%x 1000s use %lld us!  (%lld, %lld) \n", __FUNCTION__, __LINE__, sregtest, end_time-start_time, start_time, end_time);
		printk(KERN_ERR"[%s:%d] 8rderr:%d, 8wrerr:%d, 32rdwrerr:%d !\n",
			__FUNCTION__, __LINE__, scopyright_error, sreg8_rd_error, sreg32_rd_error);

		slimbus_drv_reset_bus();
		msleep(4);
		slimbus_track_configure(sdevice_type, stracktype, NULL);
		slimbus_track_activate(sdevice_type, stracktype);
	}

	return size;
}

static int info = 0;

static ssize_t requestinfo_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;

	ret = sprintf(buf, "srequestinfo:0x%x!, val:%x! \n", srequestinfo, info);

	return ret;
}

static ssize_t requestinfo_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &srequestinfo);

	printk(KERN_ERR"[%s:%d] srequestinfo:0x%x ! \n", __FUNCTION__, __LINE__, srequestinfo);

	switch (srequestinfo) {
		case 0x1:
			slimbus_drv_request_info(0x21, 0x400, SLIMBUS_SS_1_BYTE, &info);
			break;
		case 0x2:
			slimbus_drv_request_info(0x40, 0x400, SLIMBUS_SS_1_BYTE, &info);
			break;
		case 0x3:
			slimbus_drv_request_info(0x20, 0x400, SLIMBUS_SS_1_BYTE, &info);
			break;
		case 0x4:
			slimbus_drv_request_info(0x41, 0x400, SLIMBUS_SS_1_BYTE, &info);
			break;
		default:
			break;
	}
	printk(KERN_ERR"[%s:%d] srequestinfo:0x%x ! info:%x, -----\n", __FUNCTION__, __LINE__, srequestinfo, info);

	return size;
}

static ssize_t logcount_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;
	srdwrerr_logcount = slimbus_logcount_get();

	ret = sprintf(buf, "srdwrerr_logcount:0x%x!\n", srdwrerr_logcount);


	return ret;
}

static ssize_t logcount_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &srdwrerr_logcount);

	slimbus_logcount_set(srdwrerr_logcount);

	return size;
}

static ssize_t logtimes_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;
	srdwrerr_logtimes = slimbus_logtimes_get();

	ret = sprintf(buf, "srdwrerr_logtimes:0x%x!\n", srdwrerr_logtimes);


	return ret;
}

static ssize_t logtimes_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &srdwrerr_logtimes);

	slimbus_logtimes_set(srdwrerr_logtimes);

	return size;
}

static ssize_t lostmstimes_show(struct class *class, struct class_attribute *attr,
				 char *buf)
{
	uint32_t ret = 0;
	slostms_times = slimbus_drv_lostms_get();

	ret = sprintf(buf, "slostms_times:0x%x!\n", slostms_times);


	return ret;
}

static ssize_t lostmstimes_store(struct class *class, struct class_attribute *attr,
				 const char *buf, size_t size)
{
	sscanf(buf, "0x%x", &slostms_times);

	slimbus_drv_lostms_set(slostms_times);

	return size;
}

static const struct class_attribute slimbus_attrs[] = {
#ifdef __IMAGE_DOWN_TEST
	__ATTR(simgdown,            0644, imgdown_show,        imgdown_store),
#endif
	__ATTR(sregpagerd,          0644, regpagerd_show,      regpagerd_store),
	__ATTR(sregrd,              0644, regrd_show,          regrd_store),
	__ATTR(sregwr,              0644, regwr_show,          regwr_store),
	__ATTR(sswitchframer,       0664, switchframer_show,   switchframer_store),
	__ATTR(sclockgear,          0664, clockgear_show,      clockgear_store),
	__ATTR(schannelctrl,        0664, channelctrl_show,    channelctrl_store),
	__ATTR(spauseclock,         0664, pauseclock_show,     pauseclock_store),
	__ATTR(sregtest,            0664, regtest_show,        regtest_store),
	__ATTR(sbusreset,           0664, busreset_show,       busreset_store),
	__ATTR(smixtest,            0664, mixtest_show,        mixtest_store),
	__ATTR(srequestinfo,        0664, requestinfo_show,    requestinfo_store),
	__ATTR(srdwrerr_logcount,   0664, logcount_show,       logcount_store),
	__ATTR(srdwrerr_logtimes,   0664, logtimes_show,       logtimes_store),
	__ATTR(slostms_times,       0664, lostmstimes_show,    lostmstimes_store),
	__ATTR(sdevice_type,        0664, devtype_show,        devtype_store),
};

static int create_slimbus_attrs(struct class *class)
{
	int i = 0;
	int ret = 0;

	for (i=0; i < (sizeof(slimbus_attrs)/sizeof(struct class_attribute)); i++) {
		ret = class_create_file(class, &slimbus_attrs[i]);
		if (ret < 0) {
			break;
		}
	}

	return ret;
}

static void remove_slimbus_attrs(struct class *class)
{
	int i = 0;
	for (i=0; i < (sizeof(slimbus_attrs)/sizeof(struct class_attribute)); i++) {
		class_remove_file(class, &slimbus_attrs[i]);
	}
}

static int __init slimbus_debug_init(void) {
	int ret = 0;
	printk(KERN_ERR"[%s:%d], =====================!\n", __FUNCTION__, __LINE__);

	sclass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(sclass)) {
		printk(KERN_ERR"[%s:%d], class create error!\n", __FUNCTION__, __LINE__);
		return -EFAULT;
	}

	ret = create_slimbus_attrs(sclass);
	if(ret < 0) {
		class_destroy(sclass);
		printk(KERN_ERR"[%s:%d], create_slimbus_attrs error!\n", __FUNCTION__, __LINE__);
		return -EFAULT;
	}

	return 0;

}

static void __exit slimbus_debug_exit(void) {
	printk(KERN_ERR"[%s:%d], =====================!\n", __FUNCTION__, __LINE__);
	remove_slimbus_attrs(sclass);
	class_destroy(sclass);

	return 0;
}

module_init(slimbus_debug_init);
module_exit(slimbus_debug_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon");

