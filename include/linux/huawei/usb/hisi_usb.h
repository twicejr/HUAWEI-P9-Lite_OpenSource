#ifndef _HISI_USB_H_
#define _HISI_USB_H_

enum hisi_charger_type {
	CHARGER_TYPE_SDP = 0,		/* Standard Downstreame Port */
	CHARGER_TYPE_CDP,		/* Charging Downstreame Port */
	CHARGER_TYPE_DCP,		/* Dedicate Charging Port */
	CHARGER_TYPE_UNKNOWN,		/* non-standard */
	CHARGER_TYPE_NONE,		/* not connected */

	/* other messages */
	PLEASE_PROVIDE_POWER,		/* host mode, provide power */
};

enum otg_dev_event_type {
	CHARGER_CONNECT_EVENT = 0,
	CHARGER_DISCONNECT_EVENT,
	ID_FALL_EVENT,
	ID_RISE_EVENT,
	NONE_EVENT
};

#if defined(CONFIG_USB_SUSB_HDRC) || defined(CONFIG_USB_DWC3)
int hisi_charger_type_notifier_register(struct notifier_block *nb);
int hisi_charger_type_notifier_unregister(struct notifier_block *nb);
enum hisi_charger_type hisi_get_charger_type(void);
int hisi_usb_otg_event(enum otg_dev_event_type event_type);
#else
static inline int hisi_charger_type_notifier_register(
		struct notifier_block *nb){return 0;}
static inline int hisi_charger_type_notifier_unregister(
		struct notifier_block *nb){return 0;}
static inline enum hisi_charger_type hisi_get_charger_type(void)
{
	return CHARGER_TYPE_NONE;
}
static inline int hisi_usb_otg_event(enum otg_dev_event_type event_type)
{
	return 0;
}
#endif /* CONFIG_USB_SUSB_HDRC || CONFIG_USB_DWC3 */

static inline int hisi_usb_id_change(enum otg_dev_event_type event)
{
	if ((event == ID_FALL_EVENT) || (event == ID_RISE_EVENT))
		return hisi_usb_otg_event(event);
	else
		return 0;
}

#endif /* _HISI_USB_H_*/
