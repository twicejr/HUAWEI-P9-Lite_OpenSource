/*lint -save -e19 -e123 -e537 -e713*/
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/module.h>

#include <linux/usb/bsp_acm.h>

#include "usb_vendor.h"

#define ERROR (-1)
#define OK (0)

#define USB_ENABLE_CB_MAX 32
typedef enum {
	USB_ENUM_DONE_CB_MSP = 0,
	USB_ENUM_DONE_CB_PS,
	USB_ENUM_DONE_CB_BSP,
	USB_ENUM_DONE_CB_BOTTEM
} USB_ENUM_DONE_CB_E;

typedef struct {
	USB_UDI_ENABLE_CB_T udi_enable_cb[USB_ENABLE_CB_MAX];
	USB_UDI_DISABLE_CB_T udi_disable_cb[USB_ENABLE_CB_MAX];
} USB_CTX_S;

static unsigned g_usb_enum_done_cur;
static unsigned g_usb_enum_dis_cur;

static int g_usb_enum_done_notify_complete;
static int g_usb_disable_notify_complete;

static USB_CTX_S g_usb_ctx = {
	.udi_enable_cb = {NULL},
	.udi_disable_cb = {NULL},
};

unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc)
{
	if (g_usb_enum_done_cur >= USB_ENABLE_CB_MAX) {
		pr_err("BSP_USB_RegUdiEnableCB error:0x%lx", (unsigned long)pFunc);
		return (unsigned int)ERROR;
	}

	g_usb_ctx.udi_enable_cb[g_usb_enum_done_cur] = pFunc;
	g_usb_enum_done_cur++;

	if (g_usb_enum_done_notify_complete) {
		if (pFunc)
			pFunc();
	}

	return OK;
}

unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc)
{
	if (g_usb_enum_dis_cur >= USB_ENABLE_CB_MAX) {
		pr_err("BSP_USB_RegUdiDisableCB error:0x%lx", (unsigned long)pFunc);
		return (unsigned int)ERROR;
	}

	g_usb_ctx.udi_disable_cb[g_usb_enum_dis_cur] = pFunc;
	g_usb_enum_dis_cur++;

	return OK;
}

static int gs_usb_adp_notifier_cb(struct notifier_block *nb,
				  unsigned long event, void *priv)
{
	int loop;

	switch (event) {

	case USB_BALONG_DEVICE_INSERT:
		g_usb_disable_notify_complete = 0;
		break;
	case USB_BALONG_ENUM_DONE:
		/* enum done */
		g_usb_disable_notify_complete = 0;
		if (!g_usb_enum_done_notify_complete) {
			pr_info("%s: enumdone\n", __func__);
			for (loop = 0; loop < USB_ENABLE_CB_MAX; loop++) {
				if (g_usb_ctx.udi_enable_cb[loop])
					g_usb_ctx.udi_enable_cb[loop]();
			}
		}
		g_usb_enum_done_notify_complete = 1;
		break;
	case USB_BALONG_DEVICE_DISABLE:
	case USB_BALONG_DEVICE_REMOVE:
		/* notify other cb */
		g_usb_enum_done_notify_complete = 0;
		if (!g_usb_disable_notify_complete) {
			pr_info("%s: disable\n", __func__);
			for (loop = 0; loop < USB_ENABLE_CB_MAX; loop++) {
				if (g_usb_ctx.udi_disable_cb[loop])
					g_usb_ctx.udi_disable_cb[loop]();
			}
			g_usb_disable_notify_complete = 1;
		}
		break;
	default:
		break;
	}
	return 0;
}

static struct notifier_block gs_adp_usb_nb;
static struct notifier_block *gs_adp_usb_nb_ptr;

int __init adp_usb_init(void)
{
	if (!gs_adp_usb_nb_ptr) {
		gs_adp_usb_nb_ptr = &gs_adp_usb_nb;
		gs_adp_usb_nb.priority = USB_NOTIF_PRIO_ADP;
		gs_adp_usb_nb.notifier_call = gs_usb_adp_notifier_cb;
		bsp_usb_register_notify(gs_adp_usb_nb_ptr);
	}
	return 0;
}
module_init(adp_usb_init);

static void __exit adp_usb_exit(void)
{
	if (gs_adp_usb_nb_ptr) {
		bsp_usb_unregister_notify(gs_adp_usb_nb_ptr);
		gs_adp_usb_nb_ptr = NULL;
	}
}

module_exit(adp_usb_exit);
/*lint -restore*/
