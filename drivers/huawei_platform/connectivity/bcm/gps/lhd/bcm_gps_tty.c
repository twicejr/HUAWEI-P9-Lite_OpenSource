/*
 * Copyright 2015 Broadcom Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation (the "GPL").
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * A copy of the GPL is available at
 * http://www.broadcom.com/licenses/GPLv2.php, or by writing to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * 477x tty char driver to support MCU_REQ pin toggling
 *
 */
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/serial.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/of.h>
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/of_gpio.h>

#define PORT_NAME "/dev/ttyAMA3"

#define USE_TIMER 1
//#define BCM_TTY_DEBUG_INFO 0
//#define BCM_TTY_DEBUG 0
#define BCM_TTY_DELTA_MS_TO_TOGGLE_LOW 400
#define BCM_TTY_TIMER_IDLE_INTERVAL_MS 200
//#define BCM_TTY_MCU_REQ_RESP 1

#ifdef CONFIG_SENSORS_SSP_BBD
extern void bbd_parse_asic_data(unsigned char *pucData, unsigned short usLen, void (*to_gpsd)(unsigned char *packet, unsigned short len, void* priv), void* priv);
#endif

//--------------------------------------------------------------
//
//               Structs
//
//--------------------------------------------------------------
struct bcm_tty_priv
{
	struct file *tty;
	struct miscdevice misc;
	int mcu_req;
	int mcu_resp;
	//int host_req;
};


#ifdef USE_TIMER

enum ttyalarmtimer_type {
	TXALARM_REALTIME,
	TXALARM_MONOTONIC,
	TXALARM_KERNEL_TIMER,
	TXALARM_NUMTYPE,
};

static struct txalarm_base {
	spinlock_t		lock;
	int 			total_write_request; // total write request counter since total_bytes_to_write = 0
	unsigned long  	total_bytes_to_write;
	struct timer_list timer_idle;
	struct timer_list timer_tty;
	unsigned long   first_write_jiffies;
	unsigned long   last_write_jiffies;
	unsigned long   delta_since_last_write_jiffies; // delta time since last write inside timer_idle_callback
	unsigned long   timer_idle_expiration_ms;
	void (*timer_idle_function)( unsigned long data );
	void            *priv_data;
	int             toggled_low;

} txalarm_bases[3];

#endif


/*
 *  Misc. functions
 * bcm4773_hello - wakeup chip by toggling mcu_req while monitoring mcu_resp to check if awake
 *
 */
static bool bcm477x_hello(struct bcm_tty_priv *priv, unsigned total_bytes_in_queue, unsigned total_write_request)
{
#ifdef BCM_TTY_DEBUG
	pr_info("[SSPBBD]gpstty driver bcm477x_hello is coming %d total_bytes_in_queue=%d total_write_request=%d\n", priv->mcu_req, total_bytes_in_queue, total_write_request);
#endif

	gpio_set_value(priv->mcu_req, 1);
	//printk("[SSPBBD]gpstty driver to set mcu_req is 1\n" );

	// With hardware flow control this is not needed but this can be keep for debug purposes to make sure
#ifdef BCM_TTY_MCU_REQ_RESP
	// mcu req resp pin is toggled properly
	while (!gpio_get_value(priv->mcu_resp))
	{
		if (count++ > 100) {
			gpio_set_value(priv->mcu_req, 0);
			pr_info("MCU_REQ_RESP timeout. MCU_RESP(gpio%d) not responding to MCU_REQ(gpio%d)\n",
					priv->mcu_resp, priv->mcu_req);
			return false;
		}

		mdelay(1);

		/*if awake, done */
		if (gpio_get_value(priv->mcu_resp)) break;

		if (count%20==0 && retries++ < 3) {
			gpio_set_value(priv->mcu_req, 0);
			mdelay(1);
			gpio_set_value(priv->mcu_req, 1);
			mdelay(1);
		}
	}
#endif
	return true;
}


/*
 * bcm4773_bye - set mcu_req low to let chip go to sleep
 *
 */
static void bcm477x_bye(struct bcm_tty_priv *priv)
{
#ifdef BCM_TTY_DEBUG
	pr_info("[SSPBBD]gpstty driver bcm477x_bye is coming\n");
#endif

	gpio_set_value(priv->mcu_req, 0);
}



static void raz_timer(void)
{
#ifdef USE_TIMER

#ifdef BCM_TTY_DEBUG
	pr_info( "[SSPBBD]gpstty driver raz_timer\n");
#endif

	txalarm_bases[TXALARM_KERNEL_TIMER].total_write_request = 0;
	txalarm_bases[TXALARM_KERNEL_TIMER].total_bytes_to_write   = 0;
	txalarm_bases[TXALARM_KERNEL_TIMER].first_write_jiffies   = 0;
	txalarm_bases[TXALARM_KERNEL_TIMER].last_write_jiffies   = 0;
	txalarm_bases[TXALARM_KERNEL_TIMER].delta_since_last_write_jiffies   = 0;
	txalarm_bases[TXALARM_KERNEL_TIMER].timer_idle_expiration_ms = 0;
	txalarm_bases[TXALARM_KERNEL_TIMER].toggled_low = 1;
#endif
}

void timer_idle_callback( unsigned long data )
{
#ifdef USE_TIMER
	struct txalarm_base *base = NULL;
	enum  ttyalarmtimer_type type = TXALARM_KERNEL_TIMER;
	unsigned long flags;
#ifdef BCM_TTY_DEBUG
	unsigned long j = jiffies;
#endif
	unsigned long delta_ms = 0;
	struct bcm_tty_priv *priv = NULL;

	base = &txalarm_bases[type];

	spin_lock_irqsave(&base->lock, flags);

	priv = (struct bcm_tty_priv *)base->priv_data;
	base->delta_since_last_write_jiffies = jiffies - base->last_write_jiffies;
	delta_ms = base->delta_since_last_write_jiffies * 1000 / HZ;   /* jiffies to milliseconds */

	// if delta_since_last_write_jiffies >= BCM_TTY_DELTA_MS_TO_TOGGLE_LOW then we toggle MCU_REQ low
	if (delta_ms >= BCM_TTY_DELTA_MS_TO_TOGGLE_LOW && base->toggled_low==0)
    {
		bcm477x_bye(priv);
		base->toggled_low = 1;
		raz_timer();
		mod_timer(&base->timer_idle, jiffies + msecs_to_jiffies(200 * 1));
	}
	else
    {
		mod_timer(&base->timer_idle, jiffies + msecs_to_jiffies(200 * 1));
	}

	spin_unlock_irqrestore(&base->lock, flags);

#ifdef USE_TIMER
#ifdef BCM_TTY_DEBUG
	pr_info( "[SSPBBD]gpstty driver timer_idle_callback %d jiffies delta %d jiffies => %d ms\n", (unsigned long)j, base->delta_since_last_write_jiffies, delta_ms);
	pr_info( KERN_INFO "[SSPBBD]gpstty driver timer_idle_callback exit\n");
#endif
#endif

#endif
}

// idle timer arm as a 100 ms timer to monitor interval since last write to check for end of transmission with an offset >=100 ms
static void alarm_idle_init(enum ttyalarmtimer_type type,
		void (*function)(unsigned long ),unsigned long timer_expiration_ms)

{
#ifdef USE_TIMER
	struct txalarm_base *base = &txalarm_bases[type];
	unsigned long flags;

#ifdef BCM_TTY_DEBUG
	pr_info( "[SSPBBD] alarm_idle_init enter\n");
#endif

	spin_lock_irqsave(&base->lock, flags);

	base->timer_idle_function = function;
	//base->type  = type;
	base->timer_idle_expiration_ms = timer_expiration_ms;

	// my_timer, my_timer.function, my_timer.data
	setup_timer( &base->timer_idle, base->timer_idle_function, (long)base );

	spin_unlock_irqrestore(&base->lock, flags);

#ifdef BCM_TTY_DEBUG
	pr_info( "[SSPBBD]gpstty driver alarm_idle_init exit\n");
#endif

#endif
}

static void alarm_idle_arm(void)
{
#ifdef USE_TIMER
	unsigned long j = jiffies;
	enum  ttyalarmtimer_type type = TXALARM_KERNEL_TIMER;
	struct txalarm_base *base = &txalarm_bases[type];
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&base->lock, flags);

	ret = mod_timer( &base->timer_idle, j + msecs_to_jiffies(base->timer_idle_expiration_ms));

	spin_unlock_irqrestore(&base->lock, flags);
#endif
}

static void config_timer(struct bcm_tty_priv *priv)
{
#ifdef USE_TIMER

#ifdef BCM_TTY_DEBUG
	pr_info( "[SSPBBD]gpstty driver config_timer\n");
#endif

	raz_timer();

	txalarm_bases[TXALARM_KERNEL_TIMER].priv_data = (void*)priv;
	spin_lock_init(&txalarm_bases[TXALARM_KERNEL_TIMER].lock);
#endif
}

/**
 * timer_idle_try_to_cancel - Tries to cancel timer_idle
 */
static int timer_idle_try_to_cancel(void)
{
	int ret = 0;
#ifdef USE_TIMER
	enum  ttyalarmtimer_type type = TXALARM_KERNEL_TIMER;
	struct txalarm_base *base = &txalarm_bases[type];
	unsigned long flags;

#ifdef BCM_TTY_DEBUG
	pr_info( "[SSPBBD]gpstty driver txalarm_try_to_cancel\n");
#endif

	spin_lock_irqsave(&base->lock, flags);
        /*to void timer null point*/
	ret = del_timer_sync( &base->timer_idle );
	spin_unlock_irqrestore(&base->lock, flags);

#ifdef BCM_TTY_DEBUG
	if (ret)
		pr_info("[SSPBBD]gpstty driver timer_idle still in use...\n");
	else
		pr_info("[SSPBBD]gpstty driver timer_idle deleted\n");
#endif

#endif
	return ret;
}


static int timer_idle_cancel(void)
{
#ifdef USE_TIMER
#ifdef BCM_TTY_DEBUG
	pr_info( "[SSPBBD]gpstty driver timer_idle_cancel\n");
#endif

	for (;;)
	{
		int ret = timer_idle_try_to_cancel();
		if (ret >= 0)
		{
			return ret;
		}
		cpu_relax();
	}
#endif
}

//--------------------------------------------------------------
//
//               Misc. functions
//
//--------------------------------------------------------------
static int bcm_tty_config(struct file *f)
{
	struct termios termios;
	mm_segment_t fs;
	long ret;

	/* Change address limit */
	fs = get_fs();
	set_fs(KERNEL_DS);

	/* Get termios */
	ret = f->f_op->unlocked_ioctl(f, TCGETS, (unsigned long)&termios);
	if (ret) {
		pr_err("%s TCGETS failed, err=%ld\n",__func__,ret);
		return -1;
	}

	termios.c_iflag = 0;
	termios.c_oflag = 0;
	termios.c_lflag = 0;
	termios.c_cflag = CRTSCTS | CLOCAL | CS8 | CREAD;
	termios.c_cc[VMIN ] = 0;
	termios.c_cc[VTIME] = 1;	/* 100ms timeout */
	termios.c_cflag |= B921600;	//TODO: How to change baud

	/* Set termios */
	ret = f->f_op->unlocked_ioctl(f, TCSETS, (unsigned long)&termios);
	if (ret) {
		pr_err("%s TCSETS failed, err=%ld\n",__func__,ret);
		return -1;
	}

	/* Restore address limit */
	set_fs(fs);

	return 0;
}

//--------------------------------------------------------------
//
//               File Operations
//
//--------------------------------------------------------------
static int bcm_tty_open(struct inode *inode, struct file *filp)
{
	/* Initially, file->private_data points device itself and we can get our priv structs from it. */
#ifdef USE_TIMER
	enum  ttyalarmtimer_type type = TXALARM_KERNEL_TIMER;
#endif
	struct bcm_tty_priv *priv = container_of(filp->private_data, struct bcm_tty_priv, misc);

#ifdef BCM_TTY_DEBUG_INFO
	pr_info("%s++\n", __func__);
#endif

	/* Open tty */
	priv->tty = filp_open(PORT_NAME, O_RDWR, 0);
	if (IS_ERR(priv->tty)) {
		int ret = (int)PTR_ERR(priv->tty);
		pr_err("%s can not open %s, error=%d\n", __func__, PORT_NAME, ret);
		return ret;
	}

	/* Config tty */
	if (bcm_tty_config(priv->tty)) {
		pr_err("%s can not change %s setting.\n", __func__, PORT_NAME);
		return -EIO;
	}

	filp->private_data = priv;


#ifdef USE_TIMER
	raz_timer();
	alarm_idle_init(type, timer_idle_callback, BCM_TTY_TIMER_IDLE_INTERVAL_MS);
	alarm_idle_arm();
#endif

#ifdef BCM_TTY_DEBUG_INFO
	pr_info("%s--\n", __func__);
#endif

	return 0;
}

static int bcm_tty_release(struct inode *inode, struct file *filp)
{
	struct bcm_tty_priv *priv = (struct bcm_tty_priv*) filp->private_data;
	struct file *tty = priv->tty;
#ifdef USE_TIMER
	timer_idle_cancel();
#endif

	return filp_close(tty, 0);
}

static ssize_t bcm_tty_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
	struct bcm_tty_priv *priv = (struct bcm_tty_priv*) filp->private_data;
	struct file *tty = priv->tty;
	ssize_t len;

	len = tty->f_op->read(tty, buf, size, ppos);

	return len;
}

static ssize_t bcm_tty_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long j = jiffies;
	struct bcm_tty_priv *priv = (struct bcm_tty_priv*) filp->private_data;
	struct file *tty = priv->tty;
	ssize_t ret = 0;

#ifdef USE_TIMER
	unsigned long flags;
	struct txalarm_base *base = NULL;
	enum  ttyalarmtimer_type type = TXALARM_KERNEL_TIMER;
	base = &txalarm_bases[type];
	// get priv from txalarm_bases
	priv = (struct bcm_tty_priv *)base->priv_data;

	spin_lock_irqsave(&base->lock, flags);
	base->total_bytes_to_write+=size;
	base->total_write_request++;

	bcm477x_hello(priv, base->total_bytes_to_write, base->total_write_request);
	base->toggled_low = 0;
	base->last_write_jiffies = j;
	spin_unlock_irqrestore(&base->lock, flags);
#else
	bcm477x_hello(priv, 0, 0);
#endif

	ret = tty->f_op->write(tty, buf, size, ppos);

#ifndef USE_TIMER
	bcm477x_bye(priv);
#endif
	return ret;
}

static unsigned int bcm_tty_poll(struct file *filp, poll_table *wait)
{
	struct bcm_tty_priv *priv = (struct bcm_tty_priv*) filp->private_data;
	struct file *tty = priv->tty;

	return tty->f_op->poll(tty, wait);
}

static long bcm_tty_ioctl( struct file *filp,
        unsigned int cmd, unsigned long arg)
{
#ifdef BCM_TTY_DEBUG
    pr_info("[SSPBBD]gpstty driver bcm_tty_ioctl is coming\n" );
#endif
    return 0;
}

static const struct file_operations bcm_tty_fops = {
	.owner          =  THIS_MODULE,
	.open           =  bcm_tty_open,
	.release        =  bcm_tty_release,
	.read           =  bcm_tty_read,
	.write          =  bcm_tty_write,
	.poll           =  bcm_tty_poll,
	.unlocked_ioctl = bcm_tty_ioctl,
};

//--------------------------------------------------------------
//
//               Module init/exit
//
//--------------------------------------------------------------
struct bcm_tty_priv *priv;
static int __init bcm_tty_init(void)
{

	int ret;
	int mcu_req = 0;
	int mcu_resp = 0;
	//int host_req = 0;
	/* Check GPIO# */

	/*===================================================
	  We need folowing OF node in dts

	  bcm477x-gpio {
		  ssp-mcu-req = <some_gpio_number>
		  ssp-mcu-resp = <some_gpio_number>
		  ssp-host-req = <some_gpio_number>
	  }
	  ===================================================== */
	struct device_node *np = of_find_node_by_name(NULL, "gps_power");
	if (!np) {
		pr_err("[SSPBBD]gpstty driver fail to find OF node huawei,gps_power\n");
		goto err_exit;
	}
	mcu_req = of_get_named_gpio(np,"huawei,mcu_req",0);
	mcu_resp = of_get_named_gpio(np,"huawei,mcu_req_rsp",0);
	//host_req = of_get_named_gpio(np,"huawei,gps_hostwake",0);
#ifdef BCM_TTY_DEBUG_INFO
	pr_info("[SSPBBD]gpstty driver huawei,mcu_req=%d, huawei,mcu_req_rsp=%d\n",  mcu_req, mcu_resp);
#endif
	if (mcu_req<0 || mcu_resp<0) {
		pr_err("[SSPBBD]: GPIO value not correct\n");
		goto err_exit;
	}

	/* Config GPIO */
	gpio_request(mcu_req, "MCU REQ");
	gpio_direction_output(mcu_req, 0);
	gpio_request(mcu_resp, "MCU RESP");
	gpio_direction_input(mcu_resp);

	/* Alloc */
	priv = (struct bcm_tty_priv*) kmalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		pr_err("%s Failed to allocate \"gpstty\"\n", __func__);
		goto err_exit;
	}

	memset(priv, 0, sizeof(*priv));

	/* Init - gpios */
	//priv->host_req = host_req;
	priv->mcu_req  = mcu_req;
	priv->mcu_resp = mcu_resp;

	/* Register misc device */
	priv->misc.minor = MISC_DYNAMIC_MINOR;
	priv->misc.name = "gpstty";
	priv->misc.fops = &bcm_tty_fops;

	/* Initialize alarm bases */
#ifdef USE_TIMER
	config_timer(priv);
#endif

	ret = misc_register(&priv->misc);
	if (ret) {
		pr_err("%s Failed to register gpstty. err=%d\n", __func__,ret);
		goto free_mem;
	}

	return 0;

free_mem:
	if (priv)
		kfree(priv);
err_exit:
	return -ENODEV;
}

static void __exit bcm_tty_exit(void)
{
	if(priv) {
		misc_deregister(&priv->misc);
		kfree(priv);
	}
}

module_init(bcm_tty_init);
module_exit(bcm_tty_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BCM TTY Driver");
MODULE_AUTHOR("Broadcom Corporation");    ///< The author -- visible when you use modinfo
MODULE_VERSION("1.0");            ///< A version number to inform users
