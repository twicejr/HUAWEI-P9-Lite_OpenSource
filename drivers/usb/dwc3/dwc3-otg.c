#include <linux/kernel.h>
#include <linux/pm_runtime.h>
#include <linux/platform_device.h>

#include "core.h"
#include "io.h"
#include "dwc3-otg.h"

#define DBG(format, arg...) printk(KERN_INFO "[%s]" format, __func__, ##arg)

struct dwc3_otg *dwc_otg_handler;

static void dump_otg_regs(struct dwc3 *dwc)
{
#define DUMP_REG(__reg) printk(KERN_INFO "%s:\t0x%x\n",	\
		#__reg, dwc3_readl(dwc->regs, __reg))
	DUMP_REG(DWC3_OCFG);
	DUMP_REG(DWC3_OCTL);
	DUMP_REG(DWC3_OEVT);
	DUMP_REG(DWC3_OEVTEN);
	DUMP_REG(DWC3_OSTS);

	DUMP_REG(DWC3_BCFG);
	DUMP_REG(DWC3_BCEVT);
	DUMP_REG(DWC3_BCEVTEN);
}

#ifndef DWC3_OTG_FORCE_MODE
static void dwc3_disable_otg_event(struct dwc3 *dwc)
{
	dwc3_writel(dwc->regs, DWC3_OEVT, 0x0ffffff0);
	dwc3_writel(dwc->regs, DWC3_OEVTEN, 0);
}

static void dwc3_enable_otg_event(struct dwc3 *dwc)
{
	dwc3_writel(dwc, DWC3_OEVTEN, 0);
	dwc3_writel(dwc->regs, DWC3_OEVT, 0x0ffffff0);
	dwc3_writel(dwc->regs, DWC3_OEVTEN, DWC3_OEVT_OTGBDEVVBUSCHNGEVNT |
				DWC3_OEVT_OTGCONIDSTSCHNGEVNT);
}
#endif

int dwc3_otg_resume(struct dwc3 *dwc)
{
#ifndef DWC3_OTG_FORCE_MODE
	u32 reg;

	reg = dwc3_readl(dwc->regs, DWC3_OSTS);
	if (reg & DWC3_OSTS_CONIDSTS) {
		DBG("%s: ID is 1, set peripheral mode\n", __func__);
		reg = dwc3_readl(dwc->regs, DWC3_OCTL);
		reg |= DWC3_OCTL_PERIMODE;
		dwc3_writel(dwc->regs, DWC3_OCTL, reg);
	} else {
		DBG("%s: ID is 0, clear peripheral mode\n", __func__);
		reg = dwc3_readl(dwc->regs, DWC3_OCTL);
		reg &= ~DWC3_OCTL_PERIMODE;
		dwc3_writel(dwc->regs, DWC3_OCTL, reg);
	}
#endif

	return 0;
}

int dwc3_otg_suspend(struct dwc3 *dwc)
{
	return 0;
}

static int dwc3_otg_start_host(struct dwc3_otg *dwc_otg)
{
	struct dwc3 *dwc = dwc_otg->dwc;
	unsigned long flags;
	int ret;
	u32 reg;

	DBG("+\n");

	spin_lock_irqsave(&dwc->lock, flags);

#ifdef DWC3_OTG_FORCE_MODE
	reg = dwc3_readl(dwc->regs, DWC3_GCTL);
	pr_debug("%s: GCTL value 0x%x\n", __func__, reg);
	dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_HOST);
#else
	/* check ID ststus */
	reg = dwc3_readl(dwc->regs, DWC3_OSTS);
	if (reg & DWC3_OSTS_CONIDSTS) {
		pr_warning("%s: CONIDSTS wrong!\n");
		dump_otg_regs(dwc);
	}

	reg = dwc3_readl(dwc->regs, DWC3_OCFG);
	reg |= DWC3_OCFG_OTGSFTRSTMSK;
	reg |= DWC3_OCFG_DISPRTPWRCUTOFF;
	reg &= ~(DWC3_OCFG_HNPCAP | DWC3_OCFG_SRPCAP);
	dwc3_writel(dwc->regs, DWC3_OCFG, reg);

	DBG("set OCFG 0x%x\n", dwc3_readl(dwc->regs, DWC3_OCFG));

	reg = dwc3_readl(dwc->regs, DWC3_OCTL);
	reg &= ~DWC3_OCTL_PERIMODE;
	reg |= DWC3_OCTL_PRTPWRCTL;
	dwc3_writel(dwc->regs, DWC3_OCTL, reg);

	DBG("set OCTL 0x%x\n", dwc3_readl(dwc->regs, DWC3_OCTL));
#endif

	spin_unlock_irqrestore(&dwc->lock, flags);

	ret = platform_device_add(dwc->xhci);
	if (ret) {
		pr_err("%s: failed to register xHCI device\n", __func__);
		return ret;
	}

	DBG("-\n");

	return ret;
}

static void dwc3_otg_stop_host(struct dwc3_otg *dwc_otg)
{
	DBG("+\n");
	platform_device_del(dwc_otg->dwc->xhci);
	DBG("-\n");
}

static int dwc3_otg_start_peripheral(struct dwc3_otg *dwc_otg)
{
	int ret;
	unsigned long flags;
	struct dwc3 *dwc = dwc_otg->dwc;
	u32 reg;

	DBG("+\n");

	spin_lock_irqsave(&dwc->lock, flags);

#ifdef DWC3_OTG_FORCE_MODE
	reg = dwc3_readl(dwc->regs, DWC3_GCTL);
	pr_debug("%s: GCTL value 0x%x\n", __func__, reg);
	dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_DEVICE);
#else
	reg = dwc3_readl(dwc->regs, DWC3_OSTS);
	if (!(reg & DWC3_OSTS_CONIDSTS) || !(reg & DWC3_OSTS_BSESVLD)) {
		pr_warning("%s: CONIDSTS or BSESVLD wrong!\n");
		dump_otg_regs(dwc);
	}

	/* set mode as peripheral */
	reg = dwc3_readl(dwc->regs, DWC3_OCTL);
	reg |= DWC3_OCTL_PERIMODE;
	dwc3_writel(dwc->regs, DWC3_OCTL, reg);
#endif

	ret = dwc3_gadget_resume(dwc);
	if (ret) {
		spin_unlock_irqrestore(&dwc->lock, flags);
		return ret;
	}

	dwc3_gadget_complete(dwc);

	spin_unlock_irqrestore(&dwc->lock, flags);
	DBG("-\n");

	return ret;
}

static int dwc3_otg_stop_peripheral(struct dwc3_otg *dwc_otg)
{
	int ret;
	unsigned long flags;
	struct dwc3 *dwc = dwc_otg->dwc;

	DBG("+\n");
	spin_lock_irqsave(&dwc->lock, flags);
	ret = dwc3_gadget_prepare(dwc);
	if (ret)
		goto err;

	ret = dwc3_gadget_suspend(dwc);
	if (ret) {
		dwc3_gadget_complete(dwc);
		goto err;
	}
err:
	spin_unlock_irqrestore(&dwc->lock, flags);
	DBG("-\n");

	return ret;
}

int dwc3_otg_id_value(struct dwc3_otg *dwc_otg)
{
	if (dwc_otg)
		return !!(dwc3_readl(dwc_otg->dwc->regs, DWC3_OSTS)
				& DWC3_OSTS_CONIDSTS);
	else
		return 1;
}

int dwc3_otg_work(struct dwc3_otg *dwc_otg, int evt)
{
	int ret = 0;

	DBG("+\n");

	/* if otg is not enabled, do nothing */
	if (!dwc_otg) {
		pr_info("%s: dwc3 is not otg mode!\n", __func__);
		return 0;
	}

	switch (evt) {
	case DWC3_OTG_EVT_ID_SET:
		dwc3_otg_stop_host(dwc_otg);
		dwc3_suspend_device(dwc_otg->dwc);
		break;
	case DWC3_OTG_EVT_ID_CLEAR:
		ret = dwc3_resume_device(dwc_otg->dwc);
		if (ret) {
			pr_err("%s: resume device failed!\n", __func__);
			return ret;
		}
		ret = dwc3_otg_start_host(dwc_otg);
		if (ret) {
			pr_err("%s: start host failed!\n", __func__);
			dwc3_suspend_device(dwc_otg->dwc);
			return ret;
		}
		break;
	case DWC3_OTG_EVT_VBUS_SET:
		ret = dwc3_resume_device(dwc_otg->dwc);
		if (ret) {
			pr_err("%s: resume device failed!\n", __func__);
			return ret;
		}
		ret = dwc3_otg_start_peripheral(dwc_otg);
		if (ret) {
			pr_err("%s: start peripheral failed!\n", __func__);
			dwc3_suspend_device(dwc_otg->dwc);
			return ret;
		}
		break;
	case DWC3_OTG_EVT_VBUS_CLEAR:
		ret = dwc3_otg_stop_peripheral(dwc_otg);
		dwc3_suspend_device(dwc_otg->dwc);
		break;
	default:
		break;
	}
	DBG("-\n");

	return ret;
}

static void dwc3_otg_work_fun(struct work_struct *w)
{
	struct dwc3_otg *dwc_otg = container_of(w, struct dwc3_otg, otg_work.work);

	mutex_lock(&dwc_otg->lock);
	if (dwc3_otg_work(dwc_otg, atomic_read(&dwc_otg->otg_evt_flag))) {
		pr_err("%s: dwc3_otg_work failed\n", __func__);
	}
	mutex_unlock(&dwc_otg->lock);

	return;
}

int dwc3_otg_init(struct dwc3 *dwc)
{
	struct dwc3_otg *dwc_otg;
	u32 reg;

	DBG("+\n");

	dwc_otg = devm_kzalloc(dwc->dev, sizeof(struct dwc3_otg), GFP_KERNEL);
	if (!dwc_otg) {
		dev_err(dwc->dev, "unable to allocate dwc3_otg\n");
		return -ENOMEM;
	}

	dwc_otg->dwc = dwc;
	dwc->dwc_otg = dwc_otg;

	mutex_init(&dwc_otg->lock);
	INIT_DELAYED_WORK(&dwc_otg->otg_work, dwc3_otg_work_fun);

	dwc_otg_handler = dwc_otg;


#ifdef DWC3_OTG_FORCE_MODE
	reg = dwc3_readl(dwc->regs, DWC3_GCTL);
	pr_debug("%s: GCTL value 0x%x\n", __func__, reg);

	/* default device mode */
	dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_DEVICE);
#else
	/* disable hnp and srp */
	reg = dwc3_readl(dwc->regs, DWC3_OCFG);
	reg &= ~(DWC3_OCFG_HNPCAP | DWC3_OCFG_SRPCAP);
	dwc3_writel(dwc->regs, DWC3_OCFG, reg);

	reg = dwc3_readl(dwc->regs, DWC3_OSTS);
	if (reg & DWC3_OSTS_CONIDSTS) {
		DBG("%s: ID is 1, set peripheral mode\n", __func__);
		reg = dwc3_readl(dwc->regs, DWC3_OCTL);
		reg |= DWC3_OCTL_PERIMODE;
		reg &= ~(DWC3_OCTL_HNPREQ | DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HSTSETHNPEN);
		dwc3_writel(dwc->regs, DWC3_OCTL, reg);
	} else {
		DBG("%s: ID is 0, clear peripheral mode\n", __func__);
		reg = dwc3_readl(dwc->regs, DWC3_OCTL);
		reg &= ~DWC3_OCTL_PERIMODE;
		dwc3_writel(dwc->regs, DWC3_OCTL, reg);
	}
#endif

	dump_otg_regs(dwc);

	DBG("-\n");

	return 0;
}

void dwc3_otg_exit(struct dwc3 *dwc)
{
	DBG("+\n");
	dwc_otg_handler = NULL;
	dwc->dwc_otg->dwc = NULL;
	dwc->dwc_otg = NULL;
	DBG("-\n");
	return;
}
