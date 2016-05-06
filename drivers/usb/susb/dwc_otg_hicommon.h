#ifndef _DWC_OTG_HICOMMON_
#define _DWC_OTG_HICOMMON_

/* include platform head-file */
#if defined(CONFIG_HI6250_USB)
#include "dwc_otg_hi6250.h"
#else
#error "Passable some error, It should be set a platform"
#endif

#define USB2OTG_HCLK_FREQ 240000000

/* Public inteface */
void dwc_otg_hicommon_wake_lock(void);
void dwc_otg_hicommon_wake_unlock(void);
int dwc_otg_hicommon_probe_stage2(void);
int dwc_otg_hicommon_is_power_on(void);

int dwc_otg_hcd_setup(void);
void dwc_otg_hcd_shutdown(void);

typedef ssize_t (*hiusb_debug_show_ops)(void *, char *, ssize_t);
typedef ssize_t (*hiusb_debug_store_ops)(void *, const char *, ssize_t);
void hiusb_debug_init(void *data);
void hiusb_debug_quick_register(void *dev_data, hiusb_debug_show_ops show, hiusb_debug_store_ops store);

#endif
