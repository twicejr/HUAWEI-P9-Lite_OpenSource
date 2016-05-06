

#include <linux/slab.h>
#include <linux/rpmsg.h>
#include "../../cam_log.h"

extern int fake_fw_register_rpmsg_driver(struct rpmsg_driver *rpmsg_client);

extern int fake_fw_unregister_rpmsg_driver(struct rpmsg_driver *rpdrv);

extern int fake_rpmsg_send(struct rpmsg_channel *rpdev, void *data, int len);

extern struct rpmsg_endpoint *fake_fw_rpmsg_create_ept(struct rpmsg_channel *rpdev,
						rpmsg_rx_cb_t cb, void *priv, u32 addr);

extern void fake_fw_rpmsg_destroy_ept(struct rpmsg_endpoint *rpdrv);

/**
 * register_rpmsg_driver() - register an rpmsg driver with the fake rpmsg bus
 * @rpdrv: pointer to a struct rpmsg_driver
 *
 * Returns 0 on success, and an appropriate error value on failure.
 */
int register_rpmsg_driver(struct rpmsg_driver *rpdrv)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return fake_fw_register_rpmsg_driver(rpdrv);
}
EXPORT_SYMBOL(register_rpmsg_driver);

/**
 * unregister_rpmsg_driver() - unregister an rpmsg driver from the fake rpmsg bus
 * @rpdrv: pointer to a struct rpmsg_driver
 */
void unregister_rpmsg_driver(struct rpmsg_driver *rpdrv)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	fake_fw_unregister_rpmsg_driver(rpdrv);
}
EXPORT_SYMBOL(unregister_rpmsg_driver);

/**
 * rpmsg_send_offchannel_raw() - send a message across to the remote
 * processor
 * @rpdev: the rpmsg channel
 * @src: source address
 * @dst: destination address
 * @data: payload of message
 * @len: length of payload
 * @wait: indicates whether caller should block in case no TX buffers available
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
int rpmsg_send_offchannel_raw(struct rpmsg_channel *rpdev, u32 src, u32 dst,
							void *data, int len, bool wait)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return fake_rpmsg_send(rpdev, data, len);
}

EXPORT_SYMBOL(rpmsg_send_offchannel_raw);

/**
 * rpmsg_create_ept() - create a new rpmsg_endpoint
 * @rpdev: rpmsg channel device
 * @cb: rx callback handler
 * @priv: private data for the driver's use
 * @addr: local rpmsg address to bind with @cb
 *
 * Returns a pointer to the endpoint on success, or NULL on error.
 */
 struct rpmsg_endpoint *rpmsg_create_ept(struct rpmsg_channel *rpdev,
						rpmsg_rx_cb_t cb, void *priv, u32 addr)
{
	struct rpmsg_endpoint *ept;
	cam_info("%s:%s() enter", __FILE__, __func__);
	ept =  fake_fw_rpmsg_create_ept(rpdev, cb, priv, addr);
	cam_info("create ept %p ", ept);
	return ept;
//	return fake_fw_rpmsg_create_ept(rpdev, cb, priv, addr);
}

/**
 * rpmsg_destroy_ept() - do nothing for fake rpmsg bus
 * @ept: endpoing to destroy
 *
 * Should be used by drivers to destroy an rpmsg endpoint previously
 * created with rpmsg_create_ept().
 */
void rpmsg_destroy_ept(struct rpmsg_endpoint *ept)
{
	cam_info("%s:%s() destory ept %p enter", __FILE__, __func__, ept);
	fake_fw_rpmsg_destroy_ept(ept);
	return;
}
EXPORT_SYMBOL(rpmsg_destroy_ept);

void hisi_rproc_flush(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return;
}

struct completion channel_sync;

int hisi_isp_rproc_disable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return 0;
}

int hisi_isp_rproc_enable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return 0;
}

/* enable rproc a7 and isp core*/
int hisi_isp_rproc_device_enable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
#ifdef PORTING_L
	return 0;
#else
	return fake_fw_rproc_device_enable();
#endif
}

void hisi_isp_rproc_device_disable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
#ifdef PORTING_L
	return;
#else
	fake_fw_rproc_device_disable();
#endif
}

void flush_rproc_carveout_cache(void)
{
	return;
}

int rpmsg_reset_device(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return 0;
}

int rproc_fw_elf_reload(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return 0;
}

void print_rpmsg_vq_msg(void)
{
}
