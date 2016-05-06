/*
 * Copyright (C) 2012 Broadcom Corporation.
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/poll.h>
#include <linux/version.h>
#include <linux/of_gpio.h>

#include "bcm2079x.h"

#define USE_WAKE_LOCK

#ifdef USE_WAKE_LOCK
#include <linux/wakelock.h>
#endif

#define TRUE		1
#define FALSE		0
#define STATE_HIGH	1
#define STATE_LOW	0

/* end of compile options */

/* do not change below */
#define MAX_BUFFER_SIZE		780

#define MAX_I2C_BUFFER_SIZE      64


	/* Read data */
#define PACKET_HEADER_SIZE_NCI	(4)
#define PACKET_HEADER_SIZE_HCI	(3)
#define PACKET_TYPE_NCI		(16)
#define PACKET_TYPE_HCIEV	(4)
#define MAX_PACKET_SIZE		(PACKET_HEADER_SIZE_NCI + 255)

struct bcm2079x_dev {
	wait_queue_head_t read_wq;
	struct mutex read_mutex;
	struct i2c_client *client;
	struct miscdevice bcm2079x_device;
	unsigned int wake_gpio;
	unsigned int en_gpio;
	unsigned int irq_gpio;
	bool irq_enabled;
	spinlock_t irq_enabled_lock;
	unsigned int error_write;
	unsigned int error_read;
	unsigned int count_read;
	unsigned int count_irq;
    int original_address;
#ifdef USE_WAKE_LOCK
    struct wake_lock wake_lock;
#endif

};

static void bcm2079x_init_stat(struct bcm2079x_dev *bcm2079x_dev)
{
	bcm2079x_dev->error_write = 0;
	bcm2079x_dev->error_read = 0;
	bcm2079x_dev->count_read = 0;
	bcm2079x_dev->count_irq = 0;
}

static void bcm2079x_disable_irq(struct bcm2079x_dev *bcm2079x_dev)
{
	unsigned long flags;
	spin_lock_irqsave(&bcm2079x_dev->irq_enabled_lock, flags);
	if (bcm2079x_dev->irq_enabled) {
		disable_irq_nosync(bcm2079x_dev->client->irq);
		bcm2079x_dev->irq_enabled = false;
	}
	spin_unlock_irqrestore(&bcm2079x_dev->irq_enabled_lock, flags);
}

static void bcm2079x_enable_irq(struct bcm2079x_dev *bcm2079x_dev)
{
	unsigned long flags;
	spin_lock_irqsave(&bcm2079x_dev->irq_enabled_lock, flags);
	if (!bcm2079x_dev->irq_enabled) {
		bcm2079x_dev->irq_enabled = true;
		enable_irq(bcm2079x_dev->client->irq);
	}
	spin_unlock_irqrestore(&bcm2079x_dev->irq_enabled_lock, flags);
}

/*
 The alias address 0x79, when sent as a 7-bit address from the host processor
 will match the first byte (highest 2 bits) of the default client address
 (0x1FA) that is programmed in bcm20791.
 When used together with the first byte (0xFA) of the byte sequence below,
 it can be used to address the bcm20791 in a system that does not support
 10-bit address and change the default address to 0x38.
 the new address can be changed by changing the CLIENT_ADDRESS below if 0x38
 conflicts with other device on the same i2c bus.
 */
#define ALIAS_ADDRESS	  0x79

static void set_client_addr(struct bcm2079x_dev *bcm2079x_dev, int addr)
{
	struct i2c_client *client = bcm2079x_dev->client;
	client->addr = addr;
	if (addr > 0x7F)
		client->flags |= I2C_CLIENT_TEN;
    	else
        client->flags &= ~I2C_CLIENT_TEN;

	dev_info(&client->dev,
		"Set client device changed to (0x%04X) flag = %04x\n",
		client->addr, client->flags);
}

static void change_client_addr(struct bcm2079x_dev *bcm2079x_dev, int addr)
{
#if 0
	struct i2c_client *client;
	int ret;
	int i;
	int offset = 1;
	char addr_data[] = {
		0xFA, 0xF2, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x2A
	};

	client = bcm2079x_dev->client;
	if ((client->flags & I2C_CLIENT_TEN) == I2C_CLIENT_TEN) {
		client->addr = ALIAS_ADDRESS;
		client->flags &= ~I2C_CLIENT_TEN;
		offset = 0;
	}

	addr_data[5] = addr & 0xFF;
	ret = 0;
	for (i = 1; i < sizeof(addr_data) - 1; ++i)
		ret += addr_data[i];
	addr_data[sizeof(addr_data) - 1] = (ret & 0xFF);
	dev_info(&client->dev,
		 "Change client device from (0x%04X) flag = "\
		 "%04x, addr_data[%d] = %02x\n",
		 client->addr, client->flags, sizeof(addr_data) - 1,
		 addr_data[sizeof(addr_data) - 1]);
	ret = i2c_master_send(client, addr_data+offset, sizeof(addr_data)-offset);
	if (ret != sizeof(addr_data)-offset) {
		client->addr = ALIAS_ADDRESS;
		client->flags &= ~I2C_CLIENT_TEN;
		dev_info(&client->dev,
			 "Change client device from (0x%04X) flag = "\
			 "%04x, addr_data[%d] = %02x\n",
			 client->addr, client->flags, sizeof(addr_data) - 1,
			 addr_data[sizeof(addr_data) - 1]);
		ret = i2c_master_send(client, addr_data, sizeof(addr_data));
	}
	client->addr = addr_data[5];

	dev_info(&client->dev,
		 "Change client device changed to (0x%04X) flag = %04x, ret = %d\n",
		 client->addr, client->flags, ret);
#endif
}

static irqreturn_t bcm2079x_dev_irq_handler(int irq, void *dev_id)
{
	struct bcm2079x_dev *bcm2079x_dev = dev_id;
	unsigned long flags;

#ifdef USE_WAKE_LOCK
	int wakelockcnt = 0;
	if(! (wakelockcnt =  wake_lock_active(&bcm2079x_dev->wake_lock )))
	{
		printk("irq aquire wake lock\n");
		wake_lock(&bcm2079x_dev->wake_lock);
	}else
	{
//		printk("irq wake lock count = %d\n", wakelockcnt);
	}
	//printk("irq handler ( wake lock %d)...\n", wakelockcnt);
#endif

	spin_lock_irqsave(&bcm2079x_dev->irq_enabled_lock, flags);
	bcm2079x_dev->count_irq++;
	spin_unlock_irqrestore(&bcm2079x_dev->irq_enabled_lock, flags);
	wake_up(&bcm2079x_dev->read_wq);

	return IRQ_HANDLED;
}

static unsigned int bcm2079x_dev_poll(struct file *filp, poll_table *wait)
{
	struct bcm2079x_dev *bcm2079x_dev = filp->private_data;
	unsigned int mask = 0;
	unsigned long flags;

	spin_lock_irqsave(&bcm2079x_dev->irq_enabled_lock, flags);
	if(!gpio_get_value(bcm2079x_dev->irq_gpio) && (bcm2079x_dev->count_irq < 1) )
	{
		spin_unlock_irqrestore(&bcm2079x_dev->irq_enabled_lock, flags);
//		printk("poll wait, irq count %d, irq_gpio %d\n", bcm2079x_dev->count_irq,  bcm2079x_dev->irq_gpio  );
		poll_wait(filp, &bcm2079x_dev->read_wq, wait);
	}else
	{
		if (bcm2079x_dev->count_irq < 1)
			bcm2079x_dev->count_irq = 1;

		spin_unlock_irqrestore(&bcm2079x_dev->irq_enabled_lock, flags);
//		printk("poll there is data to read!!! no wait any more.\n");
		return (POLLIN | POLLRDNORM);
	}

	spin_lock_irqsave(&bcm2079x_dev->irq_enabled_lock, flags);
	if (bcm2079x_dev->count_irq > 0)
		mask |= POLLIN | POLLRDNORM;
	spin_unlock_irqrestore(&bcm2079x_dev->irq_enabled_lock, flags);

	return mask;
}

static ssize_t bcm2079x_dev_read(struct file *filp, char __user *buf,
				  size_t count, loff_t *offset)
{
	struct bcm2079x_dev *bcm2079x_dev = filp->private_data;
	unsigned char tmp[MAX_BUFFER_SIZE];
	int total, len, ret;

	total = 0;
	len = 0;

	if (bcm2079x_dev->count_irq > 0)
		bcm2079x_dev->count_irq--;

	bcm2079x_dev->count_read++;
	if (count > MAX_BUFFER_SIZE)
		count = MAX_BUFFER_SIZE;

	mutex_lock(&bcm2079x_dev->read_mutex);

	/** Read the first 4 bytes to include the length of the NCI or HCI packet.
	**/
	ret = i2c_master_recv(bcm2079x_dev->client, tmp, 4);
	if (ret == 4) {
		total = ret;
		/** First byte is the packet type
		**/
		switch(tmp[0]) {
			case PACKET_TYPE_NCI:
				len = tmp[PACKET_HEADER_SIZE_NCI-1];
				break;

			case PACKET_TYPE_HCIEV:
				len = tmp[PACKET_HEADER_SIZE_HCI-1];
				if (len == 0)
					total--;				/*Since payload is 0, decrement total size (from 4 to 3) */
				else
					len--;					/*First byte of payload is in tmp[3] already */
				break;

			default:
				len = 0;					/*Unknown packet byte */
				break;
		} /* switch*/

		/** make sure full packet fits in the buffer
		**/
		if (len > 0 && (len + total) <= count) {
			/** read the remainder of the packet.
			**/
			
			for( ; len>(MAX_I2C_BUFFER_SIZE -1); len -= (MAX_I2C_BUFFER_SIZE -1))
			{
				ret = i2c_master_recv(bcm2079x_dev->client, tmp+total, (MAX_I2C_BUFFER_SIZE-1));
				if (ret == (MAX_I2C_BUFFER_SIZE -1))
				{
					total += (MAX_I2C_BUFFER_SIZE -1);
				}
				else{
					/*log*/
					dev_err(&bcm2079x_dev->client->dev,"failed to recv I2C message");
				}
			}
			ret = i2c_master_recv(bcm2079x_dev->client, tmp+total, len);
			if (ret == len)
				total += len;
			else
				dev_err(&bcm2079x_dev->client->dev,"failed to recv I2C message");
		} /* if */

	} /* if */

	mutex_unlock(&bcm2079x_dev->read_mutex);

	if (total > count || copy_to_user(buf, tmp, total)) {
		dev_err(&bcm2079x_dev->client->dev,
			"failed to copy to user space, total = %d\n", total);
		total = -EFAULT;
		bcm2079x_dev->error_read++;
	}

	return total;
}

int send_data_over_i2c(struct bcm2079x_dev* bcm2079x_dev, char* pbuf, int len)
{
    int ret = 0;
    int count, sent;
    
    if (len <= (MAX_I2C_BUFFER_SIZE - 1)) {
        return 
			 i2c_master_send(bcm2079x_dev->client, pbuf, len);
    }

    count = (MAX_I2C_BUFFER_SIZE - 1);
    sent = 0;
    do {
        ret = i2c_master_send(bcm2079x_dev->client, pbuf + sent, count);
        if (ret != count) {
            printk("Send data failed\n");
            ret = -1;
            break;
        } else {
            sent += count;
            if (sent == len) {
                //printk("bcm2079x sent data %d\n", len);
                ret = len;
                break;
            }
            if ((len-sent) > (MAX_I2C_BUFFER_SIZE - 1)) {
                count = (MAX_I2C_BUFFER_SIZE - 1);
            } else {
                count = len - sent;
            }
        }

    } while(1);

    return ret;
}

static ssize_t bcm2079x_dev_write(struct file *filp, const char __user *buf,
				   size_t count, loff_t *offset)
{
	struct bcm2079x_dev *bcm2079x_dev = filp->private_data;
	char tmp[MAX_BUFFER_SIZE];
	int ret;
	//int len;
	//int total = 0;

	if (count > MAX_BUFFER_SIZE) {
		dev_err(&bcm2079x_dev->client->dev, "out of memory\n");
		return -ENOMEM;
	}

	if (copy_from_user(tmp, buf, count)) {
		dev_err(&bcm2079x_dev->client->dev,
			"failed to copy from user space\n");
		return -EFAULT;
	}

	mutex_lock(&bcm2079x_dev->read_mutex);
	/* Write data */

/*
	for( len = count; len>MAX_I2C_BUFFER_SIZE; len -= MAX_I2C_BUFFER_SIZE )
	{
		ret = i2c_master_send(bcm2079x_dev->client, tmp, MAX_I2C_BUFFER_SIZE);
		if( ret != MAX_I2C_BUFFER_SIZE )
		{
			dev_err(&bcm2079x_dev->client->dev,
				"failed to write %d\n", ret);
			ret = -EIO;
			bcm2079x_dev->error_write++;
			
			mutex_unlock(&bcm2079x_dev->read_mutex);
			
			return ret;
		}
		else
		{
			//total += ret;
			len    -= MAX_I2C_BUFFER_SIZE;
		}
	}

	ret = i2c_master_send(bcm2079x_dev->client, tmp, len);
	if (ret != len) {
*/
	//ret = i2c_master_send(bcm2079x_dev->client, tmp, count);
	ret = send_data_over_i2c(bcm2079x_dev, tmp, count);
	if (ret != count) {

#if 0
		if ((bcm2079x_dev->client->flags & I2C_CLIENT_TEN) != I2C_CLIENT_TEN && bcm2079x_dev->error_write == 0) {
			set_client_addr(bcm2079x_dev, 0x1FA);
			ret = i2c_master_send(bcm2079x_dev->client, tmp, count);
            if (ret != count) {
				bcm2079x_dev->error_write++;
                set_client_addr(bcm2079x_dev, bcm2079x_dev->original_address);
            }
		} 
		else
#endif
		{
			dev_err(&bcm2079x_dev->client->dev,
				"failed to write %d\n", ret);
			ret = -EIO;
			bcm2079x_dev->error_write++;
		}
	}
	mutex_unlock(&bcm2079x_dev->read_mutex);

	return ret;
}

static int bcm2079x_dev_open(struct inode *inode, struct file *filp)
{
	int ret = 0;

	struct bcm2079x_dev *bcm2079x_dev = container_of(filp->private_data,
							   struct bcm2079x_dev,
							   bcm2079x_device);
	filp->private_data = bcm2079x_dev;
	bcm2079x_init_stat(bcm2079x_dev);
	bcm2079x_enable_irq(bcm2079x_dev);
	dev_info(&bcm2079x_dev->client->dev,
		 "device node major=%d, minor=%d\n", imajor(inode), iminor(inode));

	return ret;
}

static long bcm2079x_dev_unlocked_ioctl(struct file *filp,
					 unsigned int cmd, unsigned long arg)
{
	struct bcm2079x_dev *bcm2079x_dev = filp->private_data;

	switch (cmd) {
	case BCMNFC_READ_FULL_PACKET:
		break;
	case BCMNFC_READ_MULTI_PACKETS:
		break;
	case BCMNFC_CHANGE_ADDR:
		dev_info(&bcm2079x_dev->client->dev,
			 "%s, BCMNFC_CHANGE_ADDR (%x, %lx):\n", __func__, cmd,
			 arg);
		change_client_addr(bcm2079x_dev, arg);
		break;
	case BCMNFC_POWER_CTL:
		dev_info(&bcm2079x_dev->client->dev,
			 "%s, BCMNFC_POWER_CTL (%x, %lx):\n", __func__, cmd,
			 arg);
        if (arg != 1)
            set_client_addr(bcm2079x_dev, bcm2079x_dev->original_address);
		gpio_set_value(bcm2079x_dev->en_gpio, arg);
		break;
	case BCMNFC_WAKE_CTL:
		dev_info(&bcm2079x_dev->client->dev,
			 "%s, BCMNFC_WAKE_CTL (%x, %lx):\n", __func__, cmd,
			 arg);
#ifdef USE_WAKE_LOCK
		if(arg != 0)
		{
			while(wake_lock_active(&bcm2079x_dev->wake_lock ))
			{
				printk("release wake lock!!!\n");
				wake_unlock(&bcm2079x_dev->wake_lock);
			}
			
			wake_lock_timeout(&bcm2079x_dev->wake_lock, HZ*2);
		}
#endif
		gpio_set_value(bcm2079x_dev->wake_gpio, arg);
		break;
	default:
		dev_err(&bcm2079x_dev->client->dev,
			"%s, unknown cmd (%x, %lx)\n", __func__, cmd, arg);
		return 0;
	}

	return 0;
}

static const struct file_operations bcm2079x_dev_fops = {
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.poll = bcm2079x_dev_poll,
	.read = bcm2079x_dev_read,
	.write = bcm2079x_dev_write,
	.open = bcm2079x_dev_open,
	.unlocked_ioctl = bcm2079x_dev_unlocked_ioctl
};

static int bcm2079x_get_resource(struct bcm2079x_dev *bcm2079x_dev,  struct i2c_client *client)
{
	
#if 1
	bcm2079x_dev->irq_gpio = of_get_named_gpio(client->dev.of_node, "bcm2079x,irq", 0);
	if (!gpio_is_valid(bcm2079x_dev->irq_gpio)) {
		pr_err("NFC :[%s,%d],failed to get irq!\n", __FUNCTION__, __LINE__);
		return -ENODEV;
	}

	bcm2079x_dev->en_gpio = of_get_named_gpio(client->dev.of_node, "bcm2079x,ven", 0);
	if (!gpio_is_valid(bcm2079x_dev->en_gpio)) {
		pr_err("NFC :[%s,%d],failed to get ven!\n", __FUNCTION__, __LINE__);
		return -ENODEV;
	}

	bcm2079x_dev->wake_gpio = of_get_named_gpio(client->dev.of_node, "bcm2079x,wake", 0);
	if (!gpio_is_valid(bcm2079x_dev->wake_gpio)) {
		pr_err("NFC :[%s,%d],failed to get wake!\n", __FUNCTION__, __LINE__);
		return -ENODEV;
	}
#else
	enum of_gpio_flags gpio_flags;

	bcm2079x_dev->irq_gpio = of_get_gpio_by_prop(client->dev.of_node, "bcm2079x,irq", 0 , 0 , &gpio_flags);
	if (!gpio_is_valid(bcm2079x_dev->irq_gpio)) {
		pr_err("NFC :[%s,%d],failed to get irq!\n", __FUNCTION__, __LINE__);
		return -ENODEV;
	}
	bcm2079x_dev->en_gpio = of_get_gpio_by_prop(client->dev.of_node, "bcm2079x,ven", 0 , 0 , &gpio_flags);
	if (!gpio_is_valid(bcm2079x_dev->en_gpio)) {
		pr_err("NFC :[%s,%d],failed to get ven!\n", __FUNCTION__, __LINE__);
		return -ENODEV;
	}

	bcm2079x_dev->wake_gpio = of_get_gpio_by_prop(client->dev.of_node, "bcm2079x,wake", 0 , 0 , &gpio_flags);
	if (!gpio_is_valid(bcm2079x_dev->wake_gpio)) {
		pr_err("NFC :[%s,%d],failed to get wake!\n", __FUNCTION__, __LINE__);
		return -ENODEV;
	}

#endif

	return 0;
}

static int bcm2079x_gpio_request(struct bcm2079x_dev *bcm2079x_dev,  struct i2c_client *client)
{
	int ret, irqn;
	
	ret = gpio_request(bcm2079x_dev->irq_gpio, "nfc_int");
	if (ret < 0)
		return ret;
	ret = gpio_request(bcm2079x_dev->en_gpio, "nfc_ven");
	if (ret < 0)
		goto err_en;
	ret = gpio_request(bcm2079x_dev->wake_gpio, "nfc_firm");
	if (ret < 0)
		goto err_firm;

	gpio_direction_output(bcm2079x_dev->en_gpio, 0 );
	gpio_direction_output(bcm2079x_dev->wake_gpio, 0);
	gpio_set_value(bcm2079x_dev->en_gpio, 0);
	gpio_set_value(bcm2079x_dev->wake_gpio, 0);

	gpio_direction_input(bcm2079x_dev->irq_gpio );

	gpio_to_irq(0);		
	irqn = gpio_to_irq(bcm2079x_dev->irq_gpio);		
	if (irqn < 0) {			
		ret = irqn;			
		goto err_firm;		
	}		
	client->irq = irqn;

	return ret;

	err_firm:
		gpio_free(bcm2079x_dev->en_gpio);
	err_en:
		gpio_free(bcm2079x_dev->irq_gpio);
		
	return ret;
}

static int bcm2079x_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	int ret;
	struct bcm2079x_dev *bcm2079x_dev;
	printk(" bcm2079x_probe begin\n");

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "need I2C_FUNC_I2C\n");
		return -ENODEV;
	}

	bcm2079x_dev = kzalloc(sizeof(*bcm2079x_dev), GFP_KERNEL);
	if (bcm2079x_dev == NULL) {
		dev_err(&client->dev,
			"failed to allocate memory for module data\n");
		return -ENODEV;
	}
	
	ret = bcm2079x_get_resource(bcm2079x_dev, client);
	if (ret < 0) {
		pr_err("%s:  bcm2079x probe get resource failed \n",__func__);
		goto err_exit;
	}

	ret=bcm2079x_gpio_request(bcm2079x_dev, client);
	if(ret < 0)
	{
		pr_err("%s: bcm2079x probe gpio_requst failed \n",__func__);
		goto err_exit;
	}

	bcm2079x_dev->client = client;

	/* init mutex and queues */
	init_waitqueue_head(&bcm2079x_dev->read_wq);
	mutex_init(&bcm2079x_dev->read_mutex);
	spin_lock_init(&bcm2079x_dev->irq_enabled_lock);	
#ifdef USE_WAKE_LOCK
	wake_lock_init(&bcm2079x_dev->wake_lock , WAKE_LOCK_SUSPEND, "nfcwakelock" );
#endif

	bcm2079x_dev->bcm2079x_device.minor = MISC_DYNAMIC_MINOR;
	bcm2079x_dev->bcm2079x_device.name = "bcm2079x";
	bcm2079x_dev->bcm2079x_device.fops = &bcm2079x_dev_fops;

	ret = misc_register(&bcm2079x_dev->bcm2079x_device);
	if (ret) {
		dev_err(&client->dev, "misc_register failed\n");
		goto err_misc_register;
	}

	dev_info(&client->dev,"%s, saving address %d\n", __func__, client->addr);
    	bcm2079x_dev->original_address = client->addr;

	/* request irq.  the irq is set whenever the chip has data available
	 * for reading.  it is cleared when all data has been read.
	 */
	dev_info(&client->dev, "requesting IRQ %d with IRQF_NO_SUSPEND\n", client->irq);
	bcm2079x_dev->irq_enabled = true;
	ret = request_irq(client->irq, bcm2079x_dev_irq_handler,
			  IRQF_TRIGGER_RISING|IRQF_NO_SUSPEND, client->name, bcm2079x_dev);
	if (ret) {
		dev_err(&client->dev, "request_irq failed\n");
		goto err_request_irq_failed;
	}
	enable_irq_wake(client->irq);//???
	bcm2079x_disable_irq(bcm2079x_dev);
	i2c_set_clientdata(client, bcm2079x_dev);
	dev_info(&client->dev,
		 "%s, probing bcm2079x driver exited successfully\n",
		 __func__);

	printk(" bcm2079x_probe end\n");
	return 0;

err_request_irq_failed:
	misc_deregister(&bcm2079x_dev->bcm2079x_device);
err_misc_register:
#ifdef USE_WAKE_LOCK
	wake_lock_destroy(&bcm2079x_dev->wake_lock);
#endif
	mutex_destroy(&bcm2079x_dev->read_mutex);
err_exit:
	kfree(bcm2079x_dev);
	
	return ret;
}

static int bcm2079x_remove(struct i2c_client *client)
{
	struct bcm2079x_dev *bcm2079x_dev;

	bcm2079x_dev = i2c_get_clientdata(client);
	free_irq(client->irq, bcm2079x_dev);
	misc_deregister(&bcm2079x_dev->bcm2079x_device);
	mutex_destroy(&bcm2079x_dev->read_mutex);
	wake_lock_destroy(&bcm2079x_dev->wake_lock);
	gpio_free(bcm2079x_dev->irq_gpio);
	gpio_free(bcm2079x_dev->en_gpio);
	gpio_free(bcm2079x_dev->wake_gpio);
	kfree(bcm2079x_dev);

	return 0;
}

static const struct i2c_device_id bcm2079x_id[] = {
	{"bcm2079x-i2c", 0},
	{}
};

static struct of_device_id bcm2079x_i2c_dt_ids[] = {
	{.compatible = "hisilicon,bcm2079x-i2c" },
	{}
};

MODULE_DEVICE_TABLE(of, bcm2079x_i2c_dt_ids);
static struct i2c_driver bcm2079x_driver = {
	.id_table 		= bcm2079x_id,
	.probe 		= bcm2079x_probe,
	.remove 		= bcm2079x_remove,
	.driver 		= {
		.owner 	= THIS_MODULE,
		.name 	= "bcm2079x-i2c",
		.of_match_table = of_match_ptr(bcm2079x_i2c_dt_ids),
	},
};

/*
 * module load/unload record keeping
 */

static int __init bcm2079x_dev_init(void)
{
	return i2c_add_driver(&bcm2079x_driver);
}
module_init(bcm2079x_dev_init);

static void __exit bcm2079x_dev_exit(void)
{
	i2c_del_driver(&bcm2079x_driver);
}
module_exit(bcm2079x_dev_exit);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("NFC bcm2079x driver");
MODULE_LICENSE("GPL");

