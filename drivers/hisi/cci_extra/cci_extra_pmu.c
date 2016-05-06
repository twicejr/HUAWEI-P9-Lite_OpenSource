/*
 * Hisilicon CCI extra driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <asm/cacheflush.h>
#include <asm/smp_plat.h>
#include <linux/arm-cci.h>
#include <linux/io.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/perf_event.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/bitops.h>

#define DRIVER_NAME_PMU	" CCI EXTRA PMU"

#define ENABLE_CTRL_OFFSET        0x00
#define DIRECT_CTRL_OFFSET        0x04
#define READ_FILTER_START_OFFSET  0x08
#define READ_FILTER_END_OFFSET    0x0c
#define WRITE_FILTER_START_OFFSET 0x10
#define WRITE_FILTER_END_OFFSET   0x14
#define INTERVAL_CTRL_OFFSET      0x18
#define COUNT_CTRL_OFFSET         0x1c
#define READ_TYPE_CTRL_OFFSET     0x20
#define WRITE_TYPE_CTRL_OFFSET    0x24
#define PORT_CTRL_OFFSET          0x28
#define ACCURACY_CTRL_OFFSET      0x2c
#define LATENCY_CFG0_OFFSET       0x80
#define LATENCY_CFG1_OFFSET       0x84
#define LATENCY_CFG2_OFFSET       0x88
#define LATENCY_CFG3_OFFSET       0x8c
#define LATENCY_CFG4_OFFSET       0x90
#define OUTSTANDING_CFG0_OFFSET   0xc0
#define OUTSTANDING_CFG1_OFFSET   0xc4
#define OUTSTANDING_CFG2_OFFSET   0xc8
#define OUTSTANDING_CFG3_OFFSET   0xcc
#define OUTSTANDING_CFG4_OFFSET   0xd0
#define LATENCY_COUNTER0          0x100
#define LATENCY_COUNTER1          0x104
#define LATENCY_COUNTER2          0x108
#define LATENCY_COUNTER3          0x10c
#define LATENCY_COUNTER4          0x110
#define LATENCY_COUNTER5          0x114
#define OUTSTANDING_COUNTER0      0x120
#define OUTSTANDING_COUNTER1      0x124
#define OUTSTANDING_COUNTER2      0x128
#define OUTSTANDING_COUNTER3      0x12c
#define OUTSTANDING_COUNTER4      0x130
#define OUTSTANDING_COUNTER5      0x134

static const unsigned int backup_reg[] = {DIRECT_CTRL_OFFSET,
	READ_FILTER_START_OFFSET, READ_FILTER_END_OFFSET,
	WRITE_FILTER_START_OFFSET, WRITE_FILTER_END_OFFSET,
	INTERVAL_CTRL_OFFSET, COUNT_CTRL_OFFSET, READ_TYPE_CTRL_OFFSET,
	WRITE_TYPE_CTRL_OFFSET, PORT_CTRL_OFFSET, ACCURACY_CTRL_OFFSET,
	LATENCY_CFG0_OFFSET, LATENCY_CFG1_OFFSET, LATENCY_CFG2_OFFSET,
	LATENCY_CFG3_OFFSET, LATENCY_CFG4_OFFSET, OUTSTANDING_CFG0_OFFSET,
	OUTSTANDING_CFG1_OFFSET, OUTSTANDING_CFG2_OFFSET,
	OUTSTANDING_CFG3_OFFSET, OUTSTANDING_CFG4_OFFSET,
};

#define NUM_REG_BACKUP (sizeof(backup_reg)/sizeof(backup_reg[0]))

struct cci_extra_pmu {
	void __iomem *base;
	spinlock_t lock;
	unsigned int backup_regs[NUM_REG_BACKUP];
};

/*
direct_ctrl_reg
offset=0x04
bit[0]=0 read
bit[1]=1 write
*/
static ssize_t pmu_direct_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg = readl(pmu->base + DIRECT_CTRL_OFFSET);

	return scnprintf(buf, PAGE_SIZE, "[1] %c\tread\n[2] %c\twrite\n",
				   ((reg & 0x1) == 0x0) ? '*' : ' ',
				   ((reg & 0x1) == 0x1) ? '*' : ' ');
}

static ssize_t pmu_direct_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg;
	unsigned int val;
	int error;

	error = kstrtouint(buf, 0, &val);
	if (error)
		return error;

	if ((val != 0) && (val != 1))
		return -EINVAL;

	spin_lock(&pmu->lock);

	reg = readl(pmu->base + DIRECT_CTRL_OFFSET);
	if (val == 0)
		reg &= ~0x1;
	else
		reg |= 0x1;
	writel(reg, pmu->base + DIRECT_CTRL_OFFSET);

	spin_unlock(&pmu->lock);
	return count;
}

/*
accuracy_ctrl_reg
offset=0x2c
bit[0-3]=n : accuracy=n+1
1 : more accuracy
16: less accracy 
*/
#define ACCURACY_BITMASK 0xf
#define MAX_ACCURACY 16
#define MIN_ACCURACY 1
static ssize_t pmu_accuracy_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg = readl(pmu->base + ACCURACY_CTRL_OFFSET);

	return scnprintf(buf, PAGE_SIZE, "%u [1~16]\n",
					(reg & ACCURACY_BITMASK) + 1);
}

static ssize_t pmu_accuracy_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg;
	unsigned int val;
	int error;

	error = kstrtouint(buf, 0, &val);
	if (error)
		return error;

	if (val < MIN_ACCURACY || val > MAX_ACCURACY)
		return -EINVAL;
	val -= 1;

	spin_lock(&pmu->lock);

	reg = readl(pmu->base + ACCURACY_CTRL_OFFSET);
	reg &= ~ACCURACY_BITMASK;
	reg |= val;
	writel(reg, pmu->base + ACCURACY_CTRL_OFFSET);

	spin_unlock(&pmu->lock);

	return count;
}

/*
port_ctrl_reg
offset=0x28
bit[0-1]=n : port=n
*/
#define PORT_BITMASK 0x3
#define MAX_PORT 3
static ssize_t pmu_port_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg = readl(pmu->base + PORT_CTRL_OFFSET);

	return scnprintf(buf, PAGE_SIZE, "%u [0~3]\n", (reg & PORT_BITMASK));
}

static ssize_t pmu_port_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg;
	unsigned int val;
	int error;

	error = kstrtouint(buf, 0, &val);
	if (error)
		return error;

	if (val > MAX_PORT)
		return -EINVAL;

	spin_lock(&pmu->lock);

	reg = readl(pmu->base + PORT_CTRL_OFFSET);
	reg &= ~PORT_BITMASK;
	reg |= val;
	writel(reg, pmu->base + PORT_CTRL_OFFSET);

	spin_unlock(&pmu->lock);

	return count;
}

/*
interval ctrl register
bit[0]=0  : unlimited interval
bit[0]=1  : depends on bit[1~5]
bit[4-7]=n: 0x100^n aclk cycles
bit[8]=0  : 0x100 aclk cycles
bit[8]=1  : depends bit[4~7]
*/
#define INTERVAL_BITMASK    0xf0
#define INTERVAL_CYCLE_UINT 0x100
#define MAX_INTERVAL 16
static ssize_t pmu_interval_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	ssize_t offset;
	unsigned int index;
	unsigned int i;
	unsigned int reg = readl(pmu->base + INTERVAL_CTRL_OFFSET);

	if (!(reg & BIT(0)))
		index = 0;
	else if (!(reg & BIT(8)))
		index = 1;
	else {
		reg = reg & INTERVAL_BITMASK;
		reg = reg >> 4;
		index = reg + 1;
	}

	offset = scnprintf(buf, PAGE_SIZE, "[0] %c\tunlimited\t\n",
					   index == 0 ? '*' : ' ');

	for (i = 0; i < 16; i++) {
		offset += scnprintf(buf + offset, PAGE_SIZE - offset,
						  "[%d] %c\t0x%08x\n", i + 1,
						  index == (i + 1) ? '*' : ' ',
						  INTERVAL_CYCLE_UINT << i);
	}

	return offset;
}

static ssize_t pmu_interval_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg;
	unsigned int val;
	int error;

	error = kstrtouint(buf, 0, &val);
	if (error)
		return error;

	if (val > MAX_INTERVAL)
		return -EINVAL;


	spin_lock(&pmu->lock);

	reg = readl(pmu->base + INTERVAL_CTRL_OFFSET);
	if (val == 0)
		reg &= ~(BIT(0));
	else {
		reg &= ~INTERVAL_BITMASK;
		reg |= (BIT(0) | BIT(8));
		reg |= (val - 1) << 4;
	}
	writel(reg, pmu->base + INTERVAL_CTRL_OFFSET);

	spin_unlock(&pmu->lock);

	return count;
}

/*
latency config register
offset 0x80,0x84,0x88,0x8c,0x90
bit[0-11] =n: read config=n
bit[16-27]=n: write config=n

5 latency config
count[0]= count of latency between 0..config[0]
count[1]= count of latency between config[0]..config[1]
...
count[5]= count of latency between config[4]..MAX
*/
#define MAX_LATENCY_VAL ((1 << 12) - 1)
#define NUM_LATENCY_CFG 5
static ssize_t pmu_latency_config_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	void __iomem *base = pmu->base + LATENCY_CFG0_OFFSET;
	unsigned int reg[5];
	int i;

	for (i = 0; i < 5; i++) {
		reg[i] = readl(base + i * sizeof(unsigned int));
		reg[i] = reg[i] & 0xfff;
	}

	return scnprintf(buf, PAGE_SIZE, "%d %d %d %d %d\n", reg[0],
				   reg[1], reg[2], reg[3], reg[4]);
}

static ssize_t pmu_latency_config_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	void __iomem *base = pmu->base + LATENCY_CFG0_OFFSET;
	unsigned int val[NUM_LATENCY_CFG];
	unsigned int reg, reg1;
	int i;

	if (sscanf(buf, "%u %u %u %u %u", &val[0], &val[1],
			   &val[2], &val[3], &val[4]) != NUM_LATENCY_CFG)
		return -EINVAL;

	for (i = 0; i < NUM_LATENCY_CFG - 1; i++)
		if (val[i] > val[i + 1])
			return -EINVAL;

	if (val[4] > MAX_LATENCY_VAL)
		return -EINVAL;

	spin_lock(&pmu->lock);
	for (i = 0; i < NUM_LATENCY_CFG; i++) {
		reg = val[i] << 16 | val[i];
		writel(reg, base + i * sizeof(unsigned int));
		reg1 = readl(base + i * sizeof(unsigned int));
		if (reg1 != reg) {
			spin_unlock(&pmu->lock);
			return -EINVAL;
		}
	}
	spin_unlock(&pmu->lock);

	return count;
}

/*
outstanding config register
offset 0xc0,0xc4,0xc8,0xcc,0xd0
bit[0-6] =n: read config = n
bit[16-22]=n: write config = n

5 outstanding config
count[0]= count of outstanding between 0..config[0]
count[1]= count of outstanding between config[0]..config[1]
..
count[5]= count of outstanding between config[4]..MAX
*/
#define MAX_OUTSTANDING_VAL ((1 << 7) - 1)
#define NUM_OUTSTANDING_CFG 5
static ssize_t pmu_outstanding_config_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	void __iomem *base = pmu->base + OUTSTANDING_CFG0_OFFSET;
	unsigned int reg[5];
	int i;

	for (i = 0; i < 5; i++) {
		reg[i] = readl(base + i * sizeof(unsigned int));
		reg[i] = reg[i] & 0x7f;
	}

	return scnprintf(buf, PAGE_SIZE, "%d %d %d %d %d\n", reg[0],
					 reg[1], reg[2], reg[3], reg[4]);
}

static ssize_t pmu_outstanding_config_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	void __iomem *base = pmu->base + OUTSTANDING_CFG0_OFFSET;
	unsigned int val[NUM_OUTSTANDING_CFG];
	unsigned int reg, reg1;
	int i;

	if (sscanf(buf, "%u %u %u %u %u", &val[0], &val[1],
			   &val[2], &val[3], &val[4]) != NUM_OUTSTANDING_CFG)
		return -EINVAL;

	for (i = 0; i < NUM_OUTSTANDING_CFG - 1; i++)
		if (val[i] > val[i + 1])
			return -EINVAL;

	if (val[4] > MAX_OUTSTANDING_VAL)
		return -EINVAL;

	spin_lock(&pmu->lock);
	for (i = 0; i < NUM_OUTSTANDING_CFG; i++) {
		reg = val[i] << 16 | val[i];
		writel(reg, base + i * sizeof(unsigned int));
		reg1 = readl(base + i * sizeof(unsigned int));
		if (reg1 != reg) {
			return -EINVAL;
		}
	}
	spin_unlock(&pmu->lock);

	return count;
}

/*
address range filter register
offset=0x08,0x0c,0x10,0x14
bit[0-31]: address 0~4G

4 address filter register
read  filter address range=reg[0]..reg[1]
write filter address range=reg[2]..reg[3]
*/
static ssize_t pmu_address_range_show(struct device *dev,
				struct device_attribute *attr, char *buf,
				unsigned int offset1, unsigned int offset2)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg1 = readl(pmu->base + offset1);
	unsigned int reg2 = readl(pmu->base + offset2);

	return scnprintf(buf, PAGE_SIZE, "0x%08x 0x%08x\n", reg1, reg2);
}

static ssize_t pmu_address_range_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count,
				     unsigned int offset1, unsigned int offset2)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg1;
	unsigned int reg2;
	unsigned int val1;
	unsigned int val2;

	if (sscanf(buf, "0x%08x 0x%08x", &val1, &val2) != 2)
		return -EINVAL;

	if (val1 > val2)
		return -EINVAL;

	val1 = PAGE_ALIGN(val1);
	val2 = PAGE_ALIGN(val2);

	spin_lock(&pmu->lock);

	writel(val1, pmu->base + offset1);
	writel(val2, pmu->base + offset2);

	reg1 = readl(pmu->base + offset1);
	reg2 = readl(pmu->base + offset2);

	spin_unlock(&pmu->lock);

	if ((val1 == reg1) && (reg2 == val2))
		return count;

	return -EINVAL;
}

static ssize_t pmu_read_range_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return pmu_address_range_show(dev, attr, buf,
		READ_FILTER_START_OFFSET, READ_FILTER_END_OFFSET);
}

static ssize_t pmu_read_range_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	return pmu_address_range_store(dev, attr, buf, count,
		READ_FILTER_START_OFFSET, READ_FILTER_END_OFFSET);
}

static ssize_t pmu_write_range_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return pmu_address_range_show(dev, attr, buf,
		WRITE_FILTER_START_OFFSET, WRITE_FILTER_END_OFFSET);
}

static ssize_t pmu_write_range_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	return pmu_address_range_store(dev, attr, buf, count,
		WRITE_FILTER_START_OFFSET, WRITE_FILTER_END_OFFSET);
}

/*
read type ctrl register
offset 0x24
bit[0-3]=n: 0 all
			1 device
			2 normal,non-shareable
			3 shareable WB,WC
			4 shareable WLU
			5 shareable WU
			6 evict
			7 write evict
			8 depends on bit[4-11]
			9~15 all
bit[4] =1: all
bit[5] =1: device
bit[6] =1: normal,non-shareable
bit[7] =1: shareable WB,WC
bit[8] =1: shareable WLU
bit[9] =1: shareable WU
bit[10]=1: evict
bit[11]=1: write evict
*/
static const char *write_type[] = {"device", "normal non-share",
	"shareable WB,WC", "shareable WLU", "shareable WU",
	"evict", "write evict"};

/*
write type ctrl register
offset 0x20
bit[0-3]=n: 0 all
			1 device
			2 normal,non-shareable
			3 normal,shareable,nonallocate
			4 normal,shareable,allocate
			5 read-unique
			6 cache-maint
			7 read-dvm
			8 depends on bit[4-11]
			9~15 all
bit[4] =1: all
bit[5] =1: device
bit[6] =1: normal,non-shareable
bit[7] =1: normal,shareable,nonallocate
bit[8] =1: normal,shareable,allocate
bit[9] =1: read-unique
bit[10]=1: cache-maint
bit[11]=1: read-dvm
*/
static const char *read_type[] = {"device", "normal non-share",
	"normal share non-allocate", "normal share allocate", "read unique",
	"cache maint", "read dvm"};

static ssize_t pmu_type_show(struct device *dev,
				struct device_attribute *attr, char *buf,
				unsigned int regs, const char *type_str[])
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg, val1, val2;
	unsigned int mask = 0;
	ssize_t offset = 0;
	int i;

	reg = readl(pmu->base + regs);

	/*check bit[0~3]*/
	val1 = reg & 0xf;
	switch (val1) {
	case 0x00:
		mask = ~0;
		break;
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
	case 0x05:
	case 0x06:
	case 0x07:
		mask = 1 << (val1 - 1);
		break;
	case 0x08:
		/*bit[3]==1, then check bit[4~11]*/
		val2 = (reg & 0xff0) >> 4;
		if (val2 & 0x1)
			mask = ~0;
		else
			mask = val2 >> 1;
		break;
	default:
		mask = ~0;
		break;
	}

	for (i = 0; i < 7; i++)
		offset += scnprintf(buf + offset, PAGE_SIZE - offset,
				"[%d] %c\t%s\n", i,
				(mask & (1 << i)) ? '*' : ' ', type_str[i]);

	return offset;
}

static ssize_t pmu_type_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count,
				     unsigned int regs)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	void __iomem *base = pmu->base + regs;
	unsigned int val[7];
	unsigned int reg = 0;
	int i;
	ssize_t n;

	n = sscanf(buf, "%d %d %d %d %d %d %d", &val[0], &val[1], &val[2],
			   &val[3], &val[4], &val[5], &val[6]);

	if (n < 0)
		return -EINVAL;

	for (i = 0; i < n; i++)
		if (val[i] < 0 || val[i] > 7)
			return -EINVAL;

	reg |= BIT(3);
	for (i = 0; i < n; i++)
		reg |= BIT(val[i] + 5);

	writel(reg, base);

	return count;
}

static ssize_t pmu_read_type_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return pmu_type_show(dev, attr, buf, READ_TYPE_CTRL_OFFSET, read_type);
}

static ssize_t pmu_read_type_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	return pmu_type_store(dev, attr, buf, count, READ_TYPE_CTRL_OFFSET);
}

static ssize_t pmu_write_type_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return pmu_type_show(dev, attr, buf, WRITE_TYPE_CTRL_OFFSET,
						 write_type);
}

static ssize_t pmu_write_type_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	return pmu_type_store(dev, attr, buf, count, WRITE_TYPE_CTRL_OFFSET);
}

/*
enable ctrl register
offset=0x00
bit[0]=0: disable
bit[1]=1: enable
*/
static ssize_t pmu_enable_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg = readl(pmu->base + ENABLE_CTRL_OFFSET);

	return scnprintf(buf, PAGE_SIZE, "%d\n", reg & 0x1);
}

static ssize_t pmu_enable_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg;
	unsigned int val;
	int error;

	error = kstrtouint(buf, 0, &val);
	if (error)
		return error;

	if ((val != 0) && (val != 1))
		return -EINVAL;

	spin_lock(&pmu->lock);

	reg = readl(pmu->base + COUNT_CTRL_OFFSET);
	if (val == 0)
		reg &= ~0x1;
	else
		reg |= 0x1;
	writel(reg, pmu->base + COUNT_CTRL_OFFSET);

	reg = readl(pmu->base + ENABLE_CTRL_OFFSET);
	if (val == 0)
		reg &= ~0x1;
	else
		reg |= 0x1;
	writel(reg, pmu->base + ENABLE_CTRL_OFFSET);

	spin_unlock(&pmu->lock);
	return count;
}

/*
latency/outstanding counter register
latency     offset=0x100,0x104,0x108,0x10c,0x110,0x114
outstanding offset=0x200,0x204,0x208,0x20c,0x210,0x214
bit[0-31]=n: counter value
*/
static ssize_t pmu_counter_show(struct device *dev,
				struct device_attribute *attr, char *buf,
				unsigned int offset)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(dev);
	unsigned int reg[6];
	int i;

	for (i = 0; i < 6; i++)
		reg[i] = readl(pmu->base + offset + i*sizeof(unsigned int));

	return scnprintf(buf, PAGE_SIZE, "%d %d %d %d %d %d\n", reg[0],
				reg[1], reg[2], reg[3], reg[4], reg[5]);
}

static ssize_t pmu_latency_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return pmu_counter_show(dev, attr, buf, LATENCY_COUNTER0);
}

static ssize_t pmu_outstanding_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return pmu_counter_show(dev, attr, buf, OUTSTANDING_COUNTER0);
}

#define EXTRA_PMU_RIGHT (S_IRUSR | S_IRGRP | S_IWUSR)

static DEVICE_ATTR(direct, EXTRA_PMU_RIGHT, pmu_direct_show,
		pmu_direct_store);
static DEVICE_ATTR(accuracy, EXTRA_PMU_RIGHT, pmu_accuracy_show,
		pmu_accuracy_store);
static DEVICE_ATTR(port, EXTRA_PMU_RIGHT, pmu_port_show, pmu_port_store);
static DEVICE_ATTR(interval, EXTRA_PMU_RIGHT, pmu_interval_show,
		pmu_interval_store);
static DEVICE_ATTR(read_range, EXTRA_PMU_RIGHT, pmu_read_range_show,
		pmu_read_range_store);
static DEVICE_ATTR(write_range, EXTRA_PMU_RIGHT, pmu_write_range_show,
		pmu_write_range_store);
static DEVICE_ATTR(read_type, EXTRA_PMU_RIGHT, pmu_read_type_show,
		pmu_read_type_store);
static DEVICE_ATTR(write_type, EXTRA_PMU_RIGHT, pmu_write_type_show,
		pmu_write_type_store);
static DEVICE_ATTR(latency_config, EXTRA_PMU_RIGHT, pmu_latency_config_show,
		pmu_latency_config_store);
static DEVICE_ATTR(outstanding_config, EXTRA_PMU_RIGHT,
		pmu_outstanding_config_show, pmu_outstanding_config_store);
static DEVICE_ATTR(enable, EXTRA_PMU_RIGHT, pmu_enable_show,
		pmu_enable_store);
static DEVICE_ATTR(latency, EXTRA_PMU_RIGHT, pmu_latency_show, NULL);
static DEVICE_ATTR(outstanding, EXTRA_PMU_RIGHT, pmu_outstanding_show,
		NULL);


static struct attribute *cci_extra_pmu_sysfs_entries[] = {
	&dev_attr_accuracy.attr,
	&dev_attr_port.attr,
	&dev_attr_direct.attr,
	&dev_attr_interval.attr,
	&dev_attr_read_range.attr,
	&dev_attr_write_range.attr,
	&dev_attr_read_type.attr,
	&dev_attr_write_type.attr,
	&dev_attr_latency_config.attr,
	&dev_attr_outstanding_config.attr,
	&dev_attr_enable.attr,
	&dev_attr_latency.attr,
	&dev_attr_outstanding.attr,
	NULL,
};

static struct attribute_group cci_extra_pmu_attr_group = {
	.attrs	= cci_extra_pmu_sysfs_entries,
};

static int cci_extra_pmu_probe(struct platform_device *pdev)
{
	struct cci_extra_pmu *pmu;
	struct resource *res;
	int ret;

	pmu = kzalloc(sizeof(struct cci_extra_pmu), GFP_KERNEL);
	if (!pmu) {
		dev_err(&pdev->dev, "fail to alloc !\n");
		return -ENOMEM;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pmu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pmu->base)) {
		ret = -ENOMEM;
		dev_err(&pdev->dev, "fail to ioremap !\n");
		goto err_map;
	}

	spin_lock_init(&pmu->lock);

	ret = sysfs_create_group(&pdev->dev.kobj,
				&cci_extra_pmu_attr_group);
	if (ret) {
		dev_err(&pdev->dev, "fail to create sysfs group !\n");
		goto err_sysfs;
	}

	dev_set_drvdata(&pdev->dev, pmu);

	return 0;

err_sysfs:
	iounmap(pmu->base);
err_map:
	kfree(pmu);
	return ret;
}

#ifdef CONFIG_PM
static int cci_extra_pmu_suspend(struct platform_device *pdev,
			pm_message_t state)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(&pdev->dev);
	int i;

	for (i = 0; i < NUM_REG_BACKUP; i++)
		pmu->backup_regs[i] = readl(pmu->base + backup_reg[i]);

	return 0;
}

static int cci_extra_pmu_resume(struct platform_device *pdev)
{
	struct cci_extra_pmu *pmu = dev_get_drvdata(&pdev->dev);
	unsigned int reg;
	int i;

	for (i = 0; i < NUM_REG_BACKUP; i++) {
		writel(pmu->backup_regs[i], pmu->base + backup_reg[i]);
		reg = readl(pmu->base + backup_reg[i]);
		if (reg != pmu->backup_regs[i])
			dev_err(&pdev->dev, "fail to restore 0x%x reg\n",
					backup_reg[i]);
	}

	return 0;
}
#endif

static const struct of_device_id cci_extra_pmu_matches[] = {
	{
		.compatible = "hisilicon,cci-extra-pmu",
		.data = NULL,
	},
	{},
};

static struct platform_driver cci_extra_pmu_driver = {
	.driver = {
		   .name = DRIVER_NAME_PMU,
		   .of_match_table = cci_extra_pmu_matches,
		  },
	.probe = cci_extra_pmu_probe,
#ifdef CONFIG_PM
	.suspend = cci_extra_pmu_suspend,
	.resume = cci_extra_pmu_resume,
#endif
};

static int __init cci_extra_pmu_platform_init(void)
{
	return platform_driver_register(&cci_extra_pmu_driver);
}

module_init(cci_extra_pmu_platform_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hisilicon CCI Extra PMU support");

