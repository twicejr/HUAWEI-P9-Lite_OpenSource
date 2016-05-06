#ifndef __DRIVERS_USB_DWC3_OTG_H
#define __DRIVERS_USB_DWC3_OTG_H

struct dwc3_otg {
	struct usb_otg otg;
	struct dwc3 *dwc;
	int otg_irq;
	struct delayed_work otg_work;

	atomic_t otg_evt_flag;
#define DWC3_OTG_EVT_ID_SET 1
#define DWC3_OTG_EVT_ID_CLEAR 2
#define DWC3_OTG_EVT_VBUS_SET 3
#define DWC3_OTG_EVT_VBUS_CLEAR 4

	struct mutex lock;
};

#ifdef CONFIG_USB_DWC3_OTG
extern struct dwc3_otg *dwc_otg_handler;
int dwc3_otg_init(struct dwc3 *dwc);
void dwc3_otg_exit(struct dwc3 *dwc);
int dwc3_otg_work(struct dwc3_otg *dwc_otg, int evt);
int dwc3_otg_resume(struct dwc3 *dwc);
int dwc3_otg_suspend(struct dwc3 *dwc);
int dwc3_otg_id_value(struct dwc3_otg *dwc_otg);
#else
#define dwc_otg_handler ((struct dwc3_otg *)NULL)
static inline int dwc3_otg_init(struct dwc3 *dwc)
{
	return 0;
}
static inline void dwc3_otg_exit(struct dwc3 *dwc) {}
static inline int dwc3_otg_work(struct dwc3_otg *dwc_otg, int evt)
{
	return 0;
}
static inline int dwc3_otg_resume(struct dwc3 *dwc)
{
	return 0;
}
static inline int dwc3_otg_suspend(struct dwc3 *dwc)
{
	return 0;
}
static inline int dwc3_otg_id_value(struct dwc3_otg *dwc_otg)
{
	return 0;
};
#endif

#endif /* __DRIVERS_USB_DWC3_OTG_H */
