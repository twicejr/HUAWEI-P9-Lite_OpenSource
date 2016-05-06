#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/skbuff.h>

#include "balong_acm.h"

#include <linux/usb/drv_acm.h>
#include <linux/usb/bsp_acm.h>
#include <linux/usb/drv_udi.h>

#ifdef DEBUG
#define D(format, arg...) pr_info("[%s]" format, __func__, ##arg)
#else
#define D(format, arg...) do {} while (0)
#endif

struct adp_acm_stat {
	int stat_open_err;
	long stat_open_last_err;
	int stat_read_err;
	int stat_read_last_err;
	int stat_write_err;
	int stat_write_last_err;
	int stat_ioctl_err;
	int stat_ioctl_last_err;
	int stat_wait_close;
};

struct adp_acm_context {
	char			*dev_name;
	int			port_num;
	int			is_open;
	atomic_t		opt_cnt;
	struct adp_acm_stat	stat;
};

static struct adp_acm_context adp_acm_ctx[] = {
	/* dev_name		port_num			is_open opt_cnt stat */
	{"/dev/acm_ctrl",	4,	/*UDI_USB_ACM_CTRL*/		0, {0}, {0} },
	{"/dev/acm_at",		0,	/*UDI_USB_ACM_AT*/		0, {0}, {0} },
	{"/dev/acm_c_shell",	3,	/*UDI_USB_ACM_SHELL*/		0, {0}, {0} },
	{"/dev/acm_4g_diag",	5,	/*UDI_USB_ACM_LTE_DIAG*/	0, {0}, {0} },
	{"/dev/acm_3g_diag",	1,	/*UDI_USB_ACM_OM*/		0, {0}, {0} },
	{"/dev/acm_modem",	9,	/*UDI_USB_ACM_MODEM*/		0, {0}, {0} },
	{"/dev/acm_gps",	6,	/*UDI_USB_ACM_GPS*/		0, {0}, {0} },
	{"/dev/acm_a_shell",	2,	/*UDI_USB_ACM_3G_GPS*/		0, {0}, {0} },
	{"/dev/acm_3g_pcvoice",	0xf,	/*UDI_USB_ACM_3G_PCVOICE*/	0, {0}, {0} },
	{"/dev/acm_pcvoice",	0xf,	/*UDI_USB_ACM_PCVOICE*/		0, {0}, {0} },
	{"/dev/acm_skytone",	8,	/*UDI_USB_ACM_SKYTONE*/		0, {0}, {0} },
	{"/dev/acm_err",	0xf,					0, {0}, {0} },
};

static int stat_invalid_devid;
static int stat_invalid_filp;

static u32 port_dev_id[] = {
	UDI_USB_ACM_AT,
	UDI_USB_ACM_OM,
	UDI_USB_ACM_3G_GPS,
	UDI_USB_ACM_SHELL,
	UDI_USB_ACM_CTRL,
	UDI_USB_ACM_LTE_DIAG,
	UDI_USB_ACM_GPS,
	UDI_USB_ACM_MAX,	/* invalid */
	UDI_USB_ACM_SKYTONE,
	UDI_USB_ACM_MODEM,
};

#define PORT_NUM_HANDLE(__port_num)	\
	((void *)((unsigned long)__port_num + ACM_CDEV_COUNT))
#define HANDLE_PORT_NUM(__handle)	\
	((int)((unsigned long)__handle - ACM_CDEV_COUNT))
#define PORT_NUM_INVALID(__port_num)	\
	(__port_num < 0 || __port_num >= ARRAY_SIZE(port_dev_id))

static struct adp_acm_context *port_num_to_ctx(int port_num)
{
	u32 dev_id = port_dev_id[port_num];
	if (dev_id >= ARRAY_SIZE(adp_acm_ctx))
		return NULL;
	return (struct adp_acm_context *)(&adp_acm_ctx[dev_id]);
}

/*****************************************************************************
* 函 数 名  : bsp_acm_open
*
* 功能描述  : 打开设备(数据通道)
*
* 输入参数  : dev_id: 设备id
* 输出参数  : 无
* 返 回 值  :
*****************************************************************************/
void *bsp_acm_open(u32 dev_id)
{
	unsigned int port_num;
	int ret;

	if (dev_id >= ARRAY_SIZE(adp_acm_ctx)) {
		pr_err("%s: invalid dev_id %d\n", __func__, dev_id);
		stat_invalid_devid++;
		return ERR_PTR(-EINVAL);
	}

	port_num = adp_acm_ctx[dev_id].port_num;
	D("dev_id %d, port_num %d\n", dev_id, port_num);

	ret = gs_acm_open(port_num);
	if (ret) {
		pr_err("%s: gs_acm_open failed\n", __func__);
		adp_acm_ctx[dev_id].stat.stat_open_err++;
		adp_acm_ctx[dev_id].stat.stat_open_last_err = ret;
		return ERR_PTR(-EIO);
	}

	adp_acm_ctx[dev_id].is_open = 1;

	return PORT_NUM_HANDLE(port_num);
}

/*****************************************************************************
* 函 数 名  : bsp_acm_close
*
* 功能描述  : 关闭设备(数据通道)
*
* 输入参数  : handle: 设备的handle
* 输出参数  : 无
* 返 回 值  : 成功/失败
*****************************************************************************/
s32 bsp_acm_close(void *handle)
{
	struct adp_acm_context *ctx;
	int port_num = HANDLE_PORT_NUM(handle);

	D("dev_id %d, port_num %d\n", port_dev_id[port_num], port_num);

	if (unlikely(PORT_NUM_INVALID(port_num))) {
		pr_err("%s: invalid handle %p\n", __func__, handle);
		stat_invalid_filp++;
		return -EINVAL;
	}

	ctx = port_num_to_ctx(port_num);
	if (!ctx)
		return -ENODEV;

	ctx->is_open = 0;

	/* wait for file opt complete */
	while (atomic_read(&ctx->opt_cnt)) {
		ctx->stat.stat_wait_close++;
		msleep(10);
	}

	return gs_acm_close(port_num);
}

/*****************************************************************************
* 函 数 名  : bsp_acm_write
*
* 功能描述  : 数据写
*
* 输入参数  : handle:  设备的handle
*             buf: 地址
*             size: 大小
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
s32 bsp_acm_write(void *handle, void *buf, u32 size)
{
	struct adp_acm_context *ctx;
	int port_num = HANDLE_PORT_NUM(handle);
	int status;
	loff_t pos = 0;

	if (unlikely(PORT_NUM_INVALID(port_num))) {
		pr_err("%s: invalid handle %p\n", __func__, handle);
		stat_invalid_filp++;
		return -EINVAL;
	}
	ctx = port_num_to_ctx(port_num);
	if (!ctx)
		return -ENODEV;

	atomic_inc(&ctx->opt_cnt);

	if (unlikely(!ctx->is_open)) {
		pr_err("%s: port%d is not open\n", __func__, port_num);
		status = -ENXIO;
		goto write_ret;
	}

	status = gs_acm_write(port_num, (void __force __user *)buf, size, &pos);

write_ret:
	atomic_dec(&ctx->opt_cnt);
	if (status < 0) {
		pr_err("%s: port %d write failed\n", __func__, port_num);
		ctx->stat.stat_write_err++;
		ctx->stat.stat_write_last_err = status;
	}

	return status;
}

/*****************************************************************************
* 函 数 名  : bsp_acm_read
*
* 功能描述  : 数据读
*
* 输入参数  : handle:  设备的handle
*             buf: 地址
*             size: 大小
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
s32 bsp_acm_read(void *handle, void *buf, u32 size)
{
	struct adp_acm_context *ctx;
	int port_num = HANDLE_PORT_NUM(handle);
	int status;
	loff_t pos = 0;

	if (unlikely(PORT_NUM_INVALID(port_num))) {
		pr_err("%s: invalid handle %p\n", __func__, handle);
		stat_invalid_filp++;
		/* protect system running, usr often use read in while(1). */
		msleep(10);
		return -EINVAL;
	}
	ctx = port_num_to_ctx(port_num);
	if (!ctx)
		return -ENODEV;

	atomic_inc(&ctx->opt_cnt);
	if (unlikely(!ctx->is_open)) {
		pr_err("%s: port%d is not open\n", __func__, port_num);
		status = -ENXIO;
		goto read_ret;
	}

	status = gs_acm_read(port_num, (void *)buf, size, &pos);

read_ret:
	atomic_dec(&ctx->opt_cnt);
	if (status <= 0) {
		pr_err("%s: port %d read failed\n", __func__, port_num);
		/* protect system running, usr often use read in while(1). */
		msleep(100);
		ctx->stat.stat_read_err++;
		ctx->stat.stat_read_last_err = status;
	}

	return status;
}

/*****************************************************************************
* 函 数 名  : bsp_acm_ioctl
*
* 功能描述  : 数据通道属性配置
*
* 输入参数  : handle: 设备的handle
*             u32Cmd: IOCTL命令码
*             pParam: 操作参数
* 输出参数  :
*
* 返 回 值  : 成功/失败
*****************************************************************************/
s32 bsp_acm_ioctl(void *handle, u32 cmd, void *para)
{
	struct adp_acm_context *ctx;
	int port_num = HANDLE_PORT_NUM(handle);
	int status;

	D("dev_id %d, port_num %d, cmd 0x%x\n", port_dev_id[port_num],
						port_num, cmd);

	if (unlikely(PORT_NUM_INVALID(port_num))) {
		pr_err("%s: invalid handle %p\n", __func__, handle);
		stat_invalid_filp++;
		return -EINVAL;
	}

	ctx = port_num_to_ctx(port_num);
	if (!ctx)
		return -ENODEV;

	atomic_inc(&ctx->opt_cnt);
	if (unlikely(!ctx->is_open)) {
		pr_err("%s: port%d is not open\n", __func__, port_num);
		status = -ENXIO;
		goto ioctl_ret;
	}

	status = gs_acm_ioctl(port_num, (unsigned int)cmd, (unsigned long)para);

ioctl_ret:
	atomic_dec(&ctx->opt_cnt);
	if (status < 0) {
		pr_err("%s: port %d ioctl failed\n", __func__, port_num);
		ctx->stat.stat_ioctl_err++;
		ctx->stat.stat_ioctl_last_err = status;
	}

	return status;
}

void acm_adp_dump(struct seq_file *s)
{
	int i;

	if (!s) {
		pr_err("adp dump error, seq null!\n");
		return ;
	}

	seq_printf(s, "stat_invalid_devid      :%d\n", stat_invalid_devid);
	seq_printf(s, "stat_invalid_filp       :%d\n", stat_invalid_filp);
	for (i = 0; i < ARRAY_SIZE(adp_acm_ctx); i++) {
		seq_printf(s, "==== dump dev:%s ====\n", adp_acm_ctx[i].dev_name);
		seq_printf(s, "is_open             :%d\n", adp_acm_ctx[i].is_open);
		seq_printf(s, "opt_cnt             :%d\n", atomic_read(&adp_acm_ctx[i].opt_cnt));
		seq_printf(s, "stat_open_err       :%d\n", adp_acm_ctx[i].stat.stat_open_err);
		seq_printf(s, "stat_open_last_err  :%ld\n", adp_acm_ctx[i].stat.stat_open_last_err);
		seq_printf(s, "stat_read_err       :%d\n", adp_acm_ctx[i].stat.stat_read_err);
		seq_printf(s, "stat_read_last_err  :%d\n", adp_acm_ctx[i].stat.stat_read_last_err);
		seq_printf(s, "stat_write_err      :%d\n", adp_acm_ctx[i].stat.stat_write_err);
		seq_printf(s, "stat_write_last_err :%d\n", adp_acm_ctx[i].stat.stat_write_last_err);
		seq_printf(s, "stat_ioctl_err      :%d\n", adp_acm_ctx[i].stat.stat_ioctl_err);
		seq_printf(s, "stat_ioctl_last_err :%d\n", adp_acm_ctx[i].stat.stat_ioctl_last_err);
		seq_printf(s, "stat_wait_close     :%d\n", adp_acm_ctx[i].stat.stat_wait_close);
		seq_printf(s, "\n");
	}
}
