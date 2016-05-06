#ifndef HISI_USB_OTG_TYPE_H
#define HISI_USB_OTG_TYPE_H
#include <linux/wakelock.h>
#include <linux/notifier.h>
#include <linux/huawei/usb/hisi_usb.h>
#include <linux/regulator/consumer.h>
#include <linux/clk.h>

/**
 * usb otg ahbif registers definations
 */
union usbotg2_ctrl0 {
	uint32_t reg;
	struct {
		uint32_t  idpullup_sel:1;  /* bit[0]    : ID上拉电阻使能选择：
							 0：控制器；
							 1：寄存器 */
		uint32_t  idpullup:1;  /* bit[1]    : ID上拉电阻使能 */
		uint32_t  acaenb_sel:1;  /* bit[2]    : ACA接口使能选择来源：
							 0：控制器
							 1：寄存器 */
		uint32_t  acaenb:1;  /* bit[3]    : ACA接口使能 */
		uint32_t  id_sel:2;  /* bit[4-5]  : ACA接口来源选择：
							 00：来自寄存器；
							 01：来自PHY的iddig；
							 10：来自PHY的ACA接口；
							 其他：保留 */
		uint32_t  id:1;  /* bit[6]    : 工作模式识别 */
		uint32_t  drvvbus_sel:1;  /* bit[7]    : 开启vbus电压选择：
							 0：来自控制器；
							 1：来自寄存器 */
		uint32_t  drvvbus:1;  /* bit[8]    : 使能vbus施加电压 */
		uint32_t  vbusvalid_sel:1;  /* bit[9]    : 控制器的vbusvalid信号来源选择：
							 0：选择PHY输出的vbusvalid;
							 1：选择内部的drvvbus信号 */
		uint32_t  sessvld_sel:1;  /* bit[10]   : 控制器的sessvld信号来源选择：
							 0：选择PHY输出的sessvld;
							 1：选择寄存器的sessvld */
		uint32_t  sessvld:1;  /* bit[11]   : session有效指示 */
		uint32_t  dpdmpulldown_sel:1;  /* bit[12]   : PHY的DP/DM下拉电阻使能选择：
							 0：选择控制器的dp/mpulldown；
							 1：选择寄存器的dp/mpulldown */
		uint32_t  dppulldown:1;  /* bit[13]   : 使能DP信号的下拉电阻 */
		uint32_t  dmpulldown:1;  /* bit[14]   : 使能DM信号的下拉电阻 */
		uint32_t  dbnce_fltr_bypass:1;  /* bit[15]   : 去除vbusvalid,avalid,bvalid,sessend和iddig信号的滤波器 */
		uint32_t  reserved:16; /* bit[16-31]: 保留。 */
	} bits;
};

union usbotg2_ctrl1 {
	uint32_t reg;
	struct {
		uint32_t _scaledown_mode:2;
		uint32_t _reserved:30;
	} bits;
};

union usbotg2_ctrl2 {
	uint32_t reg;
	struct {
		uint32_t  commononn:1;  /* bit[0]    : PHY的COMMON电路电源开关 */
		uint32_t  otgdisable:1;  /* bit[1]    : 关闭PHY的OTG特性 */
		uint32_t  vbusvldsel:1;  /* bit[2]    : VBUS有效选择：
						     0：来自PHY内部比较器
						     1：来自寄存器 */
		uint32_t  vbusvldext:1;  /* bit[3]    : VBUS有效 */
		uint32_t  txbitstuffen:1;
		uint32_t  txbitstuffenh:1;
		uint32_t  fsxcvrowner:1;
		uint32_t  txenablen:1;
		uint32_t  fsdataext:1;  /* bit[8]    : 串行接口数据输出 */
		uint32_t  fsse0ext:1;  /* bit[9]    : 串行接口输出SE0 */
		uint32_t  vatestenb:2;
		uint32_t  reserved:20; /* bit[12-31]: 保留。 */
	} bits;
};

union usbotg2_ctrl3 {
	uint32_t reg;
	struct {
		uint32_t  comdistune:3;
		uint32_t  otgtune:3;
		uint32_t  sqrxtune:3;
		uint32_t  txfslstune:4;
		uint32_t  txpreempamptune:2;
		uint32_t  txpreemppulsetune:1;
		uint32_t  txrisetune:2;  /* bit[16-17]: 调整眼图斜率。
							 11：-8.1%
							 10：-7.2%
							 01：缺省值
							 00：+5.4% */
		uint32_t  txvreftune:4;
		uint32_t  txhsxvtune:2;
		uint32_t  txrestune:2;
		uint32_t  vdatreftune:2;
		uint32_t  reserved:4;
	} bits;
};

union usbotg2_ctrl4 {
	uint32_t reg;
	struct {
		uint32_t  siddq:1;  /* bit[0]    : IDDQ模式 */
		uint32_t  vregbypass:1;  /* bit[1]    : Vreg18选择控制。Scan模式下不能改变其值。
						     1：VDDH需要外供1.8V电压
						     0：VDDH要外供3.3V电压 */
		uint32_t  loopbackenb:1;  /* bit[2]    : 环回测试使能控制。仅在测试模式下使用。 */
		uint32_t  bypasssel:1;  /* bit[3]    : 控制收发器的bypass模式。 */
		uint32_t  bypassdmen:1;  /* bit[4]    : DM bypass使能 */
		uint32_t  bypassdpen:1;  /* bit[5]    : DP bypass使能 */
		uint32_t  bypassdmdata:1;  /* bit[6]    : DM bypass数据 */
		uint32_t  bypassdpdata:1;  /* bit[7]    : DP bypass数据 */
		uint32_t  hsxcvrrextctl:1;  /* bit[8]    : HS收发器异步控制。仅在高速模式下起作用。 */
		uint32_t  retenablen:1;  /* bit[9]    : retion使能，缺省为1 */
		uint32_t  autorsmenb:1;  /* bit[10]   : 自动唤醒。 */
		uint32_t  reserved:21; /* bit[11-31]: 保留。 */
	} bits;
};

union usbotg2_ctrl5 {
	uint32_t reg;
	struct {
		uint32_t _refclksel:2;
		uint32_t _fsel:3;
		uint32_t _reserved:27;
	} bits;
};

union bc_ctrl0 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_en:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl1 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_int_clr:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl2 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_int_msk:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl3 {
	uint32_t reg;
	struct {
		uint32_t  bc_mode:1;  /* bit[0]   : BC模式使能 */
		uint32_t  reserved:31; /* bit[1-31]: 保留。 */
	} bits;
};

union bc_ctrl4 {
	uint32_t reg;
	struct {
		uint32_t  bc_opmode:2;
		uint32_t  bc_xcvrselect:2;  /* bit[2-3]  : 收发器选择 */
		uint32_t  bc_termselect:1;  /* bit[4]    : 终端选择 */
		uint32_t  bc_txvalid:1;  /* bit[5]    : UTMI+低8bit数据发送使能 */
		uint32_t  bc_txvalidh:1;  /* bit[6]    : UTMI+高8bit数据发送使能 */
		uint32_t  bc_idpullup:1;  /* bit[7]    : ID上拉电阻使能 */
		uint32_t  bc_dppulldown:1;  /* bit[8]    : DP下拉电阻使能 */
		uint32_t  bc_dmpulldown:1;  /* bit[9]    : DM下拉电阻使能 */
		uint32_t  bc_suspendm:1;  /* bit[10]   : suspend模式 */
		uint32_t  bc_sleepm:1;  /* bit[11]   : sleep模式 */
		uint32_t  reserved:20; /* bit[12-31]: 保留。 */
	} bits;
};

union bc_ctrl5 {
	uint32_t reg;
	struct {
		uint32_t  bc_aca_en:1;  /* bit[0]   : ACA接口使能 */
		uint32_t  bc_chrg_sel:1;  /* bit[1]   : 选择施加电平数据线 */
		uint32_t  bc_vdat_src_en:1;  /* bit[2]   : 数据端口施加电平使能 */
		uint32_t  bc_vdat_det_en:1;  /* bit[3]   : 数据端口电平检测使能 */
		uint32_t  bc_dcd_en:1;  /* bit[4]   : DCD检测使能 */
		uint32_t  reserved:27; /* bit[5-31]: 保留。 */
	} bits;
};

union bc_ctrl6 {
	uint32_t reg;
	struct {
		uint32_t _bc_chirp_int_clr:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl7 {
	uint32_t reg;
	struct {
		uint32_t _bc_chirp_int_msk:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl8 {
	uint32_t reg;
	struct {
		uint32_t _filter_len;
	} bits;
};
union bc_sts0 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_rawint:1;
		uint32_t _reserved:31;
	} bits;
};

union bc_sts1 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_mskint:1;
		uint32_t _reserved:31;
	} bits;
};

union bc_sts2 {
	uint32_t reg;
	struct {
		uint32_t  bc_vbus_valid:1;  /* bit[0]    : vbus 有效 */
		uint32_t  bc_sess_valid:1;  /* bit[1]    : session 有效 */
		uint32_t  bc_fs_vplus:1;  /* bit[2]    : DP状态 */
		uint32_t  bc_fs_vminus:1;  /* bit[3]    : DM状态 */
		uint32_t  bc_chg_det:1;  /* bit[4]    : 充电口检测 */
		uint32_t  bc_iddig:1;  /* bit[5]    : ID电平 */
		uint32_t  bc_rid_float:1;  /* bit[6]    : ACA接口状态 */
		uint32_t  bc_rid_gnd:1;  /* bit[7]    : ACA接口状态 */
		uint32_t  bc_rid_a:1;  /* bit[8]    : ACA接口状态 */
		uint32_t  bc_rid_b:1;  /* bit[9]    : ACA接口状态 */
		uint32_t  bc_rid_c:1;  /* bit[10]   : ACA接口状态 */
		uint32_t  bc_chirp_on:1;  /* bit[11]   : chirp状态 */
		uint32_t  bc_linestate:2;  /* bit[12-13]: 数据线缆状态 */
		uint32_t  reserved:18; /* bit[14-31]: 保留。 */
	} bits;
};

union bc_sts3 {
	uint32_t reg;
	struct {
		uint32_t _bc_rawint:1;
		uint32_t _reserved:31;
	} bits;
};

union bc_sts4 {
	uint32_t reg;
	struct {
		uint32_t _bc_mskint:1;
		uint32_t _reserved:31;
	} bits;
};

union usbotg2_ctrl6 {
	uint32_t reg;
	struct {
		uint32_t  testclk:1;  /* bit[0]    : 测试时钟。不需要一个连续的时钟，仅上升沿有效 */
		uint32_t  testdataoutsel:1;  /* bit[1]    : 输出总线数据选择。
						      1：模式定义的测试寄存器输出
						      0：模式定义的内部产生信号的输出 */
		uint32_t  test_sel:1;  /* bit[2]    : 测试接口选择。
						      1：选择由SOC test管脚驱动
						      0：由内部寄存器控制 */
		uint32_t  reserved_0:1;  /* bit[3]    : 保留 */
		uint32_t  testaddr:4;  /* bit[4-7]  : 测试寄存器地址 */
		uint32_t  testdatain:8;  /* bit[8-15] : 测试总线写数据 */
		uint32_t  test_mux:4;  /* bit[16-19]: 测试管脚选择。 */
		uint32_t  reserved_1:12; /* bit[20-31]: 保留。 */
	} bits;
};

union usbotg2_sts {
	uint32_t reg;
	struct {
		uint32_t  testdataout:4;  /* bit[0-3] : 测试总线读数据 */
		uint32_t  hssqyelch:1;  /* bit[4]   : HS squelch检测器输出 */
		uint32_t  hsrxdat:1;  /* bit[5]   : HS异步数据 */
		uint32_t  fslsrcv:1;  /* bit[6]   : 差分数值指示。
						   1：D+上的电压值大于D-
						   0：D-上的电压值大于D+ */
		uint32_t  reserved:25; /* bit[7-31]: 保留。 */
	} bits;
};

struct usb_ahbif_registers {
	union usbotg2_ctrl0     usbotg2_ctrl0;
	union usbotg2_ctrl1     usbotg2_ctrl1;
	union usbotg2_ctrl2     usbotg2_ctrl2;
	union usbotg2_ctrl3     usbotg2_ctrl3;
	union usbotg2_ctrl4     usbotg2_ctrl4;
	union usbotg2_ctrl5     usbotg2_ctrl5;
	union bc_ctrl0          bc_ctrl0;
	union bc_ctrl1          bc_ctrl1;
	union bc_ctrl2          bc_ctrl2;
	union bc_ctrl3          bc_ctrl3;
	union bc_ctrl4          bc_ctrl4;
	union bc_ctrl5          bc_ctrl5;
	union bc_ctrl6          bc_ctrl6;
	union bc_ctrl7          bc_ctrl7;
	union bc_ctrl8          bc_ctrl8;
	union bc_sts0           bc_sts0;
	union bc_sts1           bc_sts1;
	union bc_sts2           bc_sts2;
	union bc_sts3           bc_sts3;
	union bc_sts4           bc_sts4;
	union usbotg2_ctrl6     usbotg2_ctrl6;
	union usbotg2_sts       usbotg2_sts;
};

#define usb_dbg(format, arg...)    \
	do {                 \
		printk(KERN_INFO "[USB][%s]"format, __func__, ##arg); \
	} while (0)
#define usb_err(format, arg...)    \
	do {                 \
		printk(KERN_ERR "[USB]"format, ##arg); \
	} while (0)

enum otg_dev_status {
	OTG_DEV_OFF = 0,
	OTG_DEV_DEVICE,
	OTG_DEV_HOST,
};

enum otg_hcd_status {
	HCD_OFF = 0,
	HCD_ON,
};

struct otg_dev;
struct usb_phy_ops {
	void (*init)(struct otg_dev *otg_device, int is_host_mode);
	void (*close)(struct otg_dev *otg_device);
	int (*enable_clk)(struct otg_dev *otg_device);
	void (*disable_clk)(struct otg_dev *otg_device);
};

struct hiusb_event_queue {
	enum otg_dev_event_type *event;
	unsigned int num_event;
	unsigned int max_event;
	unsigned int enpos, depos;
};
#define MAX_EVENT_COUNT 16
#define EVENT_QUEUE_UNIT MAX_EVENT_COUNT

struct otg_dev {
	enum otg_dev_status status;
	enum otg_hcd_status hcd_status;
	enum otg_dev_event_type event;
	enum hisi_charger_type charger_type;
	enum hisi_charger_type fake_charger_type;

	unsigned gadget_initialized;
	bool dwc_otg_irq_enabled;

	struct lm_device    *lm_dev;
	struct platform_device *pdev;
	struct delayed_work event_work;
	struct wake_lock wake_lock;
	struct mutex lock;
	spinlock_t event_lock;

	struct atomic_notifier_head charger_type_notifier;

	void __iomem *pericrg_base;
	void __iomem *usb_ahbif_base;
	void __iomem *pctrl_reg_base;

	unsigned int is_regu_on;
	unsigned int eyePattern;
	struct regulator_bulk_data otgdebugsubsys_regu;
	struct usb_phy_ops *usb_phy_ops;
	int fpga_usb_mode_gpio;
	int fpga_flag;
	int eventmask;

	struct clk *clk;
	struct clk *hclk_usb2otg;

	int bc_again_flag;
	struct notifier_block conndone_nb;
	struct delayed_work bc_again_work;

	/* event queue for handle event */
	struct hiusb_event_queue event_queue;
};

#ifdef CONFIG_PM
extern struct dev_pm_ops dwc_otg_dev_pm_ops;
#define dwc_otg_dev_pm_ops_p (&dwc_otg_dev_pm_ops)
#else
#define dwc_otg_dev_pm_ops_p NULL
#endif

int dwc_otg_hicommon_probe(struct otg_dev *dev_p);
int dwc_otg_hicommon_remove(struct otg_dev *dev_p);

static inline void register_usb_phy_ops(struct otg_dev *dev_p,
					struct usb_phy_ops *ops)
{
	dev_p->usb_phy_ops = ops;
}

static inline struct usb_phy_ops *get_usb_phy_ops(struct otg_dev *dev_p)
{
	return dev_p->usb_phy_ops;
}

#endif /* hisi_usb_otg_type.h */
