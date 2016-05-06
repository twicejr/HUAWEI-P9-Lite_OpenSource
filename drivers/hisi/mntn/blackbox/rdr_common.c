#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/uaccess.h>
#include <linux/rtc.h>
#include <linux/notifier.h>
#include <linux/suspend.h>
#include <linux/atomic.h>
#include <linux/delay.h>
#include <linux/reboot.h>
#include <linux/vmalloc.h>
#include <linux/syscalls.h>

#include <linux/hisi/rdr_pub.h>
#include "rdr_inner.h"
#include "rdr_field.h"
#include "rdr_print.h"
#include "rdr_debug.h"

static char *s_internal_beta_infor[EDITION_INFOR_MAX] = {
	INTERNEL_BETA_FILE_1, INTERNEL_BETA_FILE_2, NULL
};
static char *s_oversea_beta_infor[EDITION_INFOR_MAX] = {
	OVERSEA_BETA_FILE_1, OVERSEA_BETA_FILE_2, NULL
};

/*
 * 函数名: bbox_check_edition
 * 函数参数:
 *     void
 * 返回值:
 *     unsigned int:	返回版本信息
 *				0x01        USER
 *				0x02        INTERNAL BETA
 *                         0x03        OVERSEA BETA
 *
 * 该函数会访问用户的data分区，因此依赖于文件系统的正确挂载。
 * 由于没有超时机制，等待文件系统挂载的过程会导致进程进入
 * 不确定时长的睡眠。综上在不能睡眠的场景不能调用该接口。
 */
unsigned int bbox_check_edition(void)
{
	int internalfile_exist = 0;
	int oversealfile_exist = 0;
	mm_segment_t old_fs;
	static unsigned int dump_flag = EDITION_UNKNOWN;
	int i;

	/* 如果已经检查过版本信息则直接返回 */
	if (dump_flag != EDITION_UNKNOWN) {
		return dump_flag;
	}

	BB_PRINT_DBG("============wait for fs ready start =============\n");
	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;
	BB_PRINT_DBG("============wait for fs ready e n d =============\n");

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	/* 判断国内beta文件是否存在 */
	for (i = 0; i < EDITION_INFOR_MAX && s_internal_beta_infor[i]; i++) {
		BB_PRINT_DBG("%s: Is checking %s!\n", __func__,
			     s_internal_beta_infor[i]);
		if (sys_access(s_internal_beta_infor[i], 0) == 0) {
			BB_PRINT_DBG("%s: %s is exist!\n", __func__,
				     s_internal_beta_infor[i]);
			internalfile_exist = 1;
			break;
		}
	}

	/* 判断海外beta文件是否存在 */
	for (i = 0; i < EDITION_INFOR_MAX && s_oversea_beta_infor[i]; i++) {
		BB_PRINT_DBG("%s: Is checking %s!\n", __func__,
			     s_oversea_beta_infor[i]);
		if (sys_access(s_oversea_beta_infor[i], 0) == 0) {
			BB_PRINT_DBG("%s: %s is exist!\n", __func__,
				     s_oversea_beta_infor[i]);
			oversealfile_exist = 1;
			break;
		}
	}

	if (internalfile_exist && oversealfile_exist) {
		BB_PRINT_DBG("%s: The edition is Oversea BETA\n", __func__);
		dump_flag = EDITION_OVERSEA_BETA;
	} else if (internalfile_exist && !oversealfile_exist) {
		BB_PRINT_DBG("%s: The edition is Internal BETA\n", __func__);
		dump_flag = EDITION_INTERNAL_BETA;
	} else {
		BB_PRINT_DBG("%s: The edition is User\n", __func__);
		dump_flag = EDITION_USER;
	}

	set_fs(old_fs);
	return dump_flag;
}

void rdr_get_builddatetime(u8 *out)
{
	u8 *pout = out;
	u8 *p = (u8 *) __DATE__;	/* Nov 11 2013 */
	int cnt = RDR_BUILD_DATE_TIME_LEN;

	if (NULL == out) {
		BB_PRINT_ERR("[%s], out is null!\n", __func__);
		return;
	}
	memset((void *)out, 0, RDR_BUILD_DATE_TIME_LEN);

	while (*p) {
		if (!cnt)
			return;
		if (*p != ' ') {
			*pout++ = *p++;
			cnt--;
		} else
			p++;
	}

	p = (u8 *) __TIME__;	/* 11:04:08 */
	while (*p) {
		if (!cnt)
			return;
		if (*p != ':') {
			*pout++ = *p++;
			cnt--;
		} else
			p++;
	}
	out[RDR_BUILD_DATE_TIME_LEN - 1] = '\0';
	return;
}

/*
 * func name: rdr_get_tick
 * .
 * func args:
 *  char*  buf,   return data buf.
 *  int    len    buf len.
 * return
 *	<0 fail
 *	0  success
 */
u64 rdr_get_tick(void)
{
	/* use only one int value to save time: */
	struct timespec uptime;
	do_posix_clock_monotonic_gettime(&uptime);
	monotonic_to_bootbased(&uptime);
	return (u64)uptime.tv_sec;
}

/*
 * func name: rdr_get_timestamp
 * .
 * func args:
 *  char*  buf,   return data buf.
 *  int    len    buf len.
 * return
 *	<0 fail
 *	0  success
 */
char *rdr_get_timestamp(void)
{
	struct rtc_time tm;
	struct timeval tv;
	static char databuf[DATA_MAXLEN + 1];
	BB_PRINT_START();

	memset(databuf, 0, DATA_MAXLEN + 1);

	memset(&tv, 0, sizeof(struct timeval));
	memset(&tm, 0, sizeof(struct rtc_time));
	do_gettimeofday(&tv);
	tv.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(tv.tv_sec, &tm);

	snprintf(databuf, DATA_MAXLEN + 1, "%04d%02d%02d%02d%02d%02d",
		 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		 tm.tm_hour, tm.tm_min, tm.tm_sec);

	BB_PRINT_DBG("rdr: rdr_get_timestamp [%s] !\n", databuf);
	BB_PRINT_END();
	return databuf;
}

/*Add, please keep the same as definition in reboot_reason.c in fastboot !!!!*/
struct cmdword reboot_reason_map[] = {
	{"AP_S_COLDBOOT", AP_S_COLDBOOT},
	{"bootloader", BOOTLOADER},
	{"recovery", RECOVERY},
	{"resetfactory", RESETFACTORY},
	{"resetuser", RESETUSER},
	{"sdupdate", SDUPDATE},
	{"chargereboot", CHARGEREBOOT},
	{"resize", RESIZE},
	{"erecovery", ERECOVERY},
	{"usbupdate", USBUPDATE},
	{"cust", CUST},
	{"usersdupdate", USERSDUPDATE},
	{"oem_rtc", OEM_RTC},
	{"reserved5", RESERVED5},
	{"mountfail", MOUNTFAIL},
	{"hungdetect", HUNGDETECT},
	{"coldboot", COLDBOOT},
	{"reserved1", RESERVED1},
	{"AP_S_FASTBOOTFLASH", AP_S_FASTBOOTFLASH},
	{"AP_S_ABNORMAL", AP_S_ABNORMAL},
	{"AP_S_TSENSOR0", AP_S_TSENSOR0},
	{"AP_S_TSENSOR1", AP_S_TSENSOR1},
	{"AP_S_AWDT", AP_S_AWDT},
	{"LPM3_S_GLOBALWDT", LPM3_S_GLOBALWDT},
	{"G3D_S_G3DTSENSOR", G3D_S_G3DTSENSOR},
	{"LPM3_S_LPMCURST", LPM3_S_LPMCURST},
	{"CP_S_CPTSENSOR", CP_S_CPTSENSOR},
	{"IOM3_S_IOMCURST", IOM3_S_IOMCURST},
	{"ASP_S_ASPWD", ASP_S_ASPWD},
	{"CP_S_CPWD", CP_S_CPWD},
	{"IVP_S_IVPWD", IVP_S_IVPWD},
	{"ISP_S_ISPWD", ISP_S_ISPWD},
	{"AP_S_DDR_UCE_WD", AP_S_DDR_UCE_WD},
	{"AP_S_DDR_FATAL_INTER", AP_S_DDR_FATAL_INTER},
	{"OCBC_S_WD", OCBC_S_WD},
	{"AP_S_PANIC", AP_S_PANIC},
	{"AP_S_NOC", AP_S_NOC},
	{"AP_S_DDRC_SEC", AP_S_DDRC_SEC},
	{"AP_S_COMBINATIONKEY", AP_S_COMBINATIONKEY},
	{"FASTBOOT_S_PANIC", FASTBOOT_S_PANIC},
	{"AP_S_MAILBOX", AP_S_MAILBOX},
	{"CP_S_MODEMDMSS", CP_S_MODEMDMSS},
	{"CP_S_MODEMAP", CP_S_MODEMAP},
	{"CP_S_MODEMNOC", CP_S_MODEMNOC},
	{"CP_S_EXCEPTION", CP_S_EXCEPTION},
	{"CP_S_RESETFAIL", CP_S_RESETFAIL},
	{"CP_S_NORMALRESET", CP_S_NORMALRESET},
	{"LPM3_S_EXCEPTION", LPM3_S_EXCEPTION},
	{"SOCHIFI_S_EXCEPTION", SOCHIFI_S_EXCEPTION},
	{"HIFI_S_RESETFAIL", HIFI_S_RESETFAIL},
	{"ISP_S_EXCEPTION", ISP_S_EXCEPTION},
	{"IVP_S_EXCEPTION", IVP_S_EXCEPTION},
	{"IOM3_S_EXCEPTION", IOM3_S_EXCEPTION},
	{"TEE_S_EXCEPTION", TEE_S_EXCEPTION},
	{"MMC_S_EXCEPTION", MMC_S_EXCEPTION},
	{"CODECHIFI_S_EXCEPTION", CODECHIFI_S_EXCEPTION},
	{"CP_S_RILD_EXCEPTION", CP_S_RILD_EXCEPTION},
	{"CP_S_3RD_EXCEPTION", CP_S_3RD_EXCEPTION},
	{"IOM3_S_USER_EXCEPTION", IOM3_S_USER_EXCEPTION},
	{"reserved4", RESERVED4},
	{"AP_S_PMU", AP_S_PMU},
	{"AP_S_SMPL", AP_S_SMPL},
	{"AP_S_SCHARGER", AP_S_SCHARGER},
	/*
	 * 以下复位类型未包含在PMU寄存器识别的类型内
	 * 部分类型在函数secondary_reboot_reason_check中处理
	 * 处理的具体类型参见secondary_reboot_reason_list
	 */
	{"VolUsbUpdate", BR_KEY_VOLUMN_DOWN_UP_UPDATE_USB},
	{"ForceSdUpdate", BR_KEY_VOLUMN_DOWN_UP_UPDATE_SD_FORCE},
	{"VolUpRecovery", BR_KEY_VOLUMN_UP},
	{"press1s", BR_KEY_POWERON_PRESS_1S},
	{"press10s", BR_KEY_POWERON_PRESS_10S},
	{"CheckpointRecovery", BR_CHECKPOINT_RECOVERY},
	{"CheckpointErecovery", BR_CHECKPOINT_ERECOVERY},
	{"CheckpointSdUpdate", BR_CHECKPOINT_SDUPDATE},
	{"CheckpointUsbUpdate", BR_CHECKPOINT_USBUPDATE},
	{"CheckpointResetFactory", BR_CHECKPOINT_RESETFACTORY},
	{"CheckpointHotaUpdate", BR_CHECKPOINT_HOTAUPDATE},
	{"CheckpointUserSdUpdate", BR_CHECKPOINT_USERSDUPDATE},
	{"PoweronNoBat", BR_POWERON_BY_USB_NO_BAT},
	{"nogui", BR_NOGUI},
	{"Factory", BR_FACTORY_VERSION},
	{"ResetHappen", BR_RESET_HAPPEN},
	{"OemRtc", BR_POWEROFF_ALARM},
	{"PoweroffCharging", BR_POWEROFF_CHARGE},
	{"SMPL", BR_POWERON_BY_SMPL},
	{"CheckpointUpdateDataimg", BR_CHECKPOINT_UPDATEDATAIMG},
	{"CPU_BUCK", BR_REBOOT_CPU_BUCK},
};

struct blackbox_modid_list g_modid_list[] = {
	{HISI_BB_MOD_MODEM_DRV_START, HISI_BB_MOD_MODEM_DRV_END, "MODEM DRV"},
	{HISI_BB_MOD_MODEM_OSA_START, HISI_BB_MOD_MODEM_OSA_END, "MODEM OSA"},
	{HISI_BB_MOD_MODEM_OM_START, HISI_BB_MOD_MODEM_OM_END, "MODEM OM"},
	{HISI_BB_MOD_MODEM_GU_L2_START, HISI_BB_MOD_MODEM_GU_L2_END,
	 "MODEM GU L2"},
	{HISI_BB_MOD_MODEM_GU_WAS_START, HISI_BB_MOD_MODEM_GU_WAS_END,
	 "MODEM GU WAS"},
	{HISI_BB_MOD_MODEM_GU_GAS_START, HISI_BB_MOD_MODEM_GU_GAS_END,
	 "MODEM GU GAS"},
	{HISI_BB_MOD_MODEM_GU_NAS_START, HISI_BB_MOD_MODEM_GU_NAS_END,
	 "MODEM GU NAS"},
	{HISI_BB_MOD_MODEM_GU_DSP_START, HISI_BB_MOD_MODEM_GU_DSP_END,
	 "MODEM GU DSP"},
	{HISI_BB_MOD_AP_START, HISI_BB_MOD_AP_END, "ap"},
	{HISI_BB_MOD_ISP_START, HISI_BB_MOD_ISP_END, "isp"},
	{HISI_BB_MOD_EMMC_START, HISI_BB_MOD_EMMC_END, "emmc"},
	{HISI_BB_MOD_CP_START, HISI_BB_MOD_CP_END, "cp"},
	{HISI_BB_MOD_TEE_START, HISI_BB_MOD_TEE_END, "tee"},
	{HISI_BB_MOD_HIFI_START, HISI_BB_MOD_HIFI_END, "hifi"},
	{HISI_BB_MOD_LPM_START, HISI_BB_MOD_LPM_END, "lpm3"},
	{HISI_BB_MOD_IOM_START, HISI_BB_MOD_IOM_END, "iom3"},
	{HISI_BB_MOD_RESERVED_START, HISI_BB_MOD_RESERVED_END,
	 "blackbox reserved"},
	{HISI_BB_MOD_MODEM_LPS_START, HISI_BB_MOD_MODEM_LPS_END, "MODEM LPS"},
	{HISI_BB_MOD_MODEM_LMSP_START, HISI_BB_MOD_MODEM_LMSP_END,
	 "MODEM LMSP"},
	{HISI_BB_MOD_RANDOM_ALLOCATED_START, HISI_BB_MOD_RANDOM_ALLOCATED_END,
	 "blackbox random allocated"},
};

u32 get_reboot_reason_map_size(void)
{
	return (u32) (sizeof(reboot_reason_map) / sizeof(reboot_reason_map[0]));
}

/*
 * func name: rdr_get_exception_core
 * get exception core str for core id.
 * func args:
 *    u64 coreid
 * return value
 *	NULL  error
 *	!NULL core str.
 */
char *rdr_get_exception_type(u64 e_exce_type)
{
	int i;
	char *type = "UNDEF";

	for (i = 0; i < get_reboot_reason_map_size(); i++) {
		if (reboot_reason_map[i].num == e_exce_type) {
			return reboot_reason_map[i].name;
		}
	}

	return type;
}

char *exception_core[RDR_CORE_MAX + 1] = {
	"AP",
	"CP",
	"TEEOS",
	"HIFI",
	"LPM3",
	"IOM3",
	"ISP",
	"IVP",
	"EMMC",
	"UNDEF"
};

/*
 * func name: rdr_get_exception_core
 * get exception core str for core id.
 * func args:
 *    u64 coreid
 * return value
 *	NULL  error
 *	!NULL core str.
 */
char *rdr_get_exception_core(u64 coreid)
{
	char *core = NULL;
	switch (coreid) {
	case RDR_AP:
		core = exception_core[0];
		break;
	case RDR_CP:
		core = exception_core[1];
		break;
	case RDR_TEEOS:
		core = exception_core[2];
		break;
	case RDR_HIFI:
		core = exception_core[3];
		break;
	case RDR_LPM3:
		core = exception_core[4];
		break;
	case RDR_IOM3:
		core = exception_core[5];
		break;
	case RDR_ISP:
		core = exception_core[6];
		break;
	case RDR_IVP:
		core = exception_core[7];
		break;
	case RDR_EMMC:
		core = exception_core[8];
		break;
	default:
		core = exception_core[9];
		break;
	}
	return core;
}

atomic_t volatile bb_in_suspend = ATOMIC_INIT(0);
atomic_t volatile bb_in_reboot = ATOMIC_INIT(0);
atomic_t volatile bb_in_saving = ATOMIC_INIT(0);

int rdr_get_suspend_state()
{
	return atomic_read(&bb_in_suspend);
}

int rdr_get_reboot_state()
{
	return atomic_read(&bb_in_reboot);
}

int rdr_set_saving_state(int state)
{
	return atomic_set(&bb_in_saving, state);
}

#ifdef CONFIG_PM
static struct notifier_block bb_suspend_notifier;
static int bb_suspend_nb(struct notifier_block *this,
			 unsigned long event, void *ptr)
{
	switch (event) {
	case PM_POST_HIBERNATION:
	case PM_POST_SUSPEND:
		BB_PRINT_DBG("%s: resume +\n", __func__);
		atomic_set(&bb_in_suspend, 0);
		BB_PRINT_DBG("%s: resume -\n", __func__);
		break;

	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
		BB_PRINT_DBG("%s: suspend +\n", __func__);
		atomic_set(&bb_in_suspend, 1);
		while (1) {
			if (atomic_read(&bb_in_saving))
				msleep(1000);
			else
				break;
		}
		BB_PRINT_DBG("%s: suspend -\n", __func__);
		break;
	default:
		return NOTIFY_DONE;
	}
	return NOTIFY_OK;
}
#endif

static int bb_reboot_nb(struct notifier_block *nb, unsigned long foo, void *bar)
{
	int i = 10;
	/* prevent access the emmc now: */
	BB_PRINT_DBG("%s: shutdown +\n", __func__);
	atomic_set(&bb_in_reboot, 1);
	while (i--) {
		if (atomic_read(&bb_in_saving))
			msleep(1000);
		else
			break;
		BB_PRINT_DBG("rdr:is saving rdr, wait 1s ...\n");
	}
	rdr_field_reboot_done();
	BB_PRINT_DBG("%s: shutdown -\n", __func__);

	return 0;
}

static u64 RESERVED_RDR_PHYMEM_ADDR;
static u64 RESERVED_RDR_PHYMEM_SIZE;
static RDR_NVE g_nve;
static u64 g_max_logsize;
static u32 g_wait_dumplog_timeout;
static u32 g_max_reboot_times;

u32 rdr_get_reboot_times(void)
{
	return g_max_reboot_times;
}

u64 rdr_reserved_phymem_addr(void)
{
	return RESERVED_RDR_PHYMEM_ADDR;
}

u64 rdr_reserved_phymem_size(void)
{
	return RESERVED_RDR_PHYMEM_SIZE;
}

int rdr_get_dumplog_timeout(void)
{
	return g_wait_dumplog_timeout;
}

u64 rdr_get_logsize(void)
{
	return g_max_logsize;
}

RDR_NVE rdr_get_nve(void)
{
	return g_nve;
}

char *blackbox_get_modid_str(u32 modid)
{
	u32 i;
	u32 modid_size = sizeof(g_modid_list) / sizeof(g_modid_list[0]);
	for (i = 0; i < modid_size; ++i) {
		if (modid >= g_modid_list[i].modid_span_little
		    && modid <= g_modid_list[i].modid_span_big) {
			return g_modid_list[i].modid_str;
		}
	}

	return "error,modid not found";

}

#include <linux/of.h>
#include <linux/of_address.h>
int rdr_common_early_init(void)
{
	int i, ret, len;
	struct device_node *np = NULL;
	struct resource res;
	const char *prdr_dumpctrl;
	u32 value;
	u32 data[RDR_CORE_MAX];

	np = of_find_compatible_node(NULL, NULL, "hisilicon,rdr");
	if (!np) {
		BB_PRINT_ERR("[%s], find rdr_memory node fail!\n", __func__);
		return -ENODEV;
	}

	if (of_address_to_resource(np, 0, &res)) {
		BB_PRINT_ERR("[%s], of_address_to_resource fail!\n", __func__);
		return -ENODEV;
	}

	RESERVED_RDR_PHYMEM_ADDR = res.start;
	RESERVED_RDR_PHYMEM_SIZE = resource_size(&res);

	BB_PRINT_DBG("[%s], get phymem addr [%llx] size [%llx]in dts!\n",
		     __func__, RESERVED_RDR_PHYMEM_ADDR,
		     RESERVED_RDR_PHYMEM_SIZE);

	ret = of_property_read_string(np, "rdr-dumpctl", &prdr_dumpctrl);
	if (ret < 0 || NULL == prdr_dumpctrl
	    || strlen(prdr_dumpctrl) > 16) {
		BB_PRINT_ERR("[%s], find rdr-dumpctl node fail! [%s]\n",
			     __func__, prdr_dumpctrl);
		return ret;
	}
	BB_PRINT_DBG("[%s], get prdr_dumpctrl [%s] in dts!\n", __func__,
		     prdr_dumpctrl);
	g_nve = 0;
	len = strlen(prdr_dumpctrl);
	for (i = --len; i >= 0; i--) {
		if (prdr_dumpctrl[i] == '1')
			g_nve |= 1 << (len - i);
	}
	BB_PRINT_DBG("[%s], get nve [0x%llx] in dts!\n", __func__, g_nve);
	ret = of_property_read_u32(np, "rdr-log-max-size", &value);
	if (ret) {
		BB_PRINT_ERR("[%s], cannot find rdr-log-max-size in dts!\n",
			     __func__);
		return ret;
	}
	g_max_logsize = value;
	BB_PRINT_DBG("[%s], get rdr-log-max-size [0x%llx] in dts!\n", __func__,
		     g_max_logsize);

	ret = of_property_read_u32(np, "wait-dumplog-timeout", &value);
	if (ret) {
		BB_PRINT_ERR("[%s], cannot find wait-dumplog-timeout in dts!\n",
			     __func__);
		return ret;
	}
	g_wait_dumplog_timeout = value;
	BB_PRINT_DBG("[%s], get g_wait_dumplog_timeout [0x%x] in dts!\n",
		     __func__, g_wait_dumplog_timeout);

	ret = of_property_read_u32(np, "rdr_area_num", &value);
	if (ret) {
		BB_PRINT_ERR("[%s], cannot find rdr_area_num in dts!\n",
			     __func__);
		return ret;
	}
	BB_PRINT_DBG("[%s], get rdr_area_num [0x%x] in dts!\n", __func__,
		     value);

	if (value > RDR_CORE_MAX) {
		BB_PRINT_ERR("[%s], invaild core num in dts!\n", __func__);
		return -1;
	}
	ret = of_property_read_u32_array(np, "rdr_area_sizes", &data[0], value);
	if (ret) {
		BB_PRINT_ERR("[%s], cannot find rdr_area_sizes in dts!\n",
			     __func__);
		return ret;
	}
	rdr_set_area_info(0, value);
	for (i = 1; i < value; i++) {
		rdr_set_area_info(i, data[i]);
		BB_PRINT_DBG("[%s], get rdr_area_num[%d]:[0x%x] in dts!\n",
			     __func__, i, data[i]);
	}

	ret = of_property_read_u32(np, "unexpected-max-reboot-times", &value);
	if (ret) {
		BB_PRINT_ERR("[%s], cannot find unexpected-max-reboot-times in dts!\n",
			     __func__);
		return ret;
	}
	g_max_reboot_times = value;
	BB_PRINT_DBG("[%s], unexpected-max-reboot-times [0x%x] in dts!\n", __func__,
		     value);

	return ret;
}

static struct notifier_block bb_reboot_notifier;
int rdr_common_init(void)
{

#ifdef CONFIG_PM
	/* Register to get PM events */
	bb_suspend_notifier.notifier_call = bb_suspend_nb;
	bb_suspend_notifier.priority = -1;
	if (register_pm_notifier(&bb_suspend_notifier)) {
		BB_PRINT_ERR("%s: Failed to register for PM events\n",
			     __func__);
		return -1;
	}
#endif

	bb_reboot_notifier.notifier_call = bb_reboot_nb;
	bb_reboot_notifier.priority = -1;
	if (register_reboot_notifier(&bb_reboot_notifier)) {
		BB_PRINT_ERR("%s: Failed to register for Reboot events\n",
			     __func__);
		return -1;
	}
	return 0;

}

static char g_reboot_reason[RDR_REBOOT_REASON_LEN] = "undef";
static u32 g_reboot_type;
char *rdr_get_reboot_reason(void)
{
	return g_reboot_reason;
}

u32 rdr_get_reboot_type(void)
{
	return g_reboot_type;
}

static int __init early_parse_reboot_reason_cmdline(char *reboot_reason_cmdline)
{
	int i;
	printk("[%s]\n", __func__);
	memset(g_reboot_reason, 0x0, RDR_REBOOT_REASON_LEN);
	memcpy(g_reboot_reason, reboot_reason_cmdline, RDR_REBOOT_REASON_LEN);

	for (i = 0; i < get_reboot_reason_map_size(); i++) {
		if (!strcmp(reboot_reason_map[i].name, g_reboot_reason)) {
			g_reboot_type = reboot_reason_map[i].num;
			break;
		}
	}
	printk("[%s][%s][%d]\n", __func__, g_reboot_reason, g_reboot_type);
	return 0;
}

early_param("reboot_reason", early_parse_reboot_reason_cmdline);

static void *bbox_vmap(phys_addr_t paddr, size_t size)
{
	int i;
	void *vaddr = NULL;
	pgprot_t pgprot;
	unsigned long offset;
	int pages_count;
	struct page **pages;

	offset = paddr & ~PAGE_MASK;
	paddr &= PAGE_MASK;
	pages_count = PAGE_ALIGN(size + offset) / PAGE_SIZE;

	pages = kmalloc(sizeof(struct page *) * pages_count, GFP_KERNEL);
	if (!pages)
		return NULL;

	pgprot = pgprot_writecombine(PAGE_KERNEL);

	for (i = 0; i < pages_count; i++) {
		*(pages + i) = phys_to_page(paddr + PAGE_SIZE * i);
	}

	vaddr = vmap(pages, pages_count, VM_MAP, pgprot);
	kfree(pages);
	if (NULL == vaddr)
		return NULL;

	return offset + (char *)vaddr;
}

void *hisi_bbox_map(phys_addr_t paddr, size_t size)
{
	void *vaddr = NULL;

	if (paddr < RESERVED_RDR_PHYMEM_ADDR || !size ||
	    (paddr + size) >
	    (RESERVED_RDR_PHYMEM_ADDR + RESERVED_RDR_PHYMEM_SIZE)) {
		BB_PRINT_ERR("Error BBox memory.\n");
		return NULL;
	}

	if (pfn_valid(RESERVED_RDR_PHYMEM_ADDR >> PAGE_SHIFT)) {
		vaddr = bbox_vmap(paddr, size);
	} else {
		vaddr = ioremap_wc(paddr, size);
	}

	return vaddr;
}

void hisi_bbox_unmap(const void *vaddr)
{
	if (pfn_valid(RESERVED_RDR_PHYMEM_ADDR >> PAGE_SHIFT)) {
		vunmap(vaddr);
	} else {
		iounmap((void __iomem *)vaddr);
	}
}

/*******************************************************************************
Function:       bbox_save_done
Description:	每次异常对应的log目录保存完毕后，需要调用此函数表示这个目录已经
		记录完毕了，logserver可以将其打包上传了。
Input:	logpath:异常对应的保存log的目录；
		step:异常log保存到了哪一步，是否还需要继续使用的标记；
Output:		    NA
Return:		    NA
Other:          used by rdr_core.c、rdr_hisi_ap_adapter.c
********************************************************************************/
void bbox_save_done(char *logpath, u32 step)
{
	int fd = 0, ret = 0;
	char path[PATH_MAXLEN];
	static mm_segment_t oldfs;

	BB_PRINT_START();
	if (!logpath
	    || (PATH_MAXLEN <
		strlen(logpath) + strlen(BBOX_SAVE_DONE_FILENAME) + 1)) {
		BB_PRINT_ERR("logpath is invalid.\n");
		return;
	}

	BB_PRINT_ERR("logpath is [%s], step is [%d]\n", logpath, step);
	if (BBOX_SAVE_STEP_DONE == step) {

		/*组合done文件的绝对路径，作为sys_mkdir的参数 */
		memset(path, 0, PATH_MAXLEN);
		memcpy(path, logpath, strlen(logpath));
		strncat(path, BBOX_SAVE_DONE_FILENAME,
			strlen(BBOX_SAVE_DONE_FILENAME));

		oldfs = get_fs();
		set_fs(KERNEL_DS);

		/*在时间戳目录下面创建done文件 */
		fd = sys_open(path, O_CREAT | O_WRONLY, FILE_LIMIT);
		if (fd < 0) {
			BB_PRINT_ERR("sys_mkdir [%s] error, fd is [%d]\n", path,
				     fd);
			return;
		}
		sys_close(fd);

		set_fs(oldfs);

		/*根据权限要求，hisi_logs目录及子目录群组调整为root-system */
		ret =
		    (int)bbox_chown((const char __user *)path, ROOT_UID,
				    SYSTEM_GID, false);
		if (ret) {
			BB_PRINT_ERR
			    ("chown %s uid [%d] gid [%d] failed err [%d]!\n",
			     PATH_ROOT, ROOT_UID, SYSTEM_GID, ret);
		}
	}

	BB_PRINT_END();
}

/*******************************************************************************
Function:		rdr_record_reboot_times2mem
Description:	save reboot times to specified memory.
Input:		NA
Output:		NA
Return:		NA
Other:		NA
********************************************************************************/
void rdr_record_reboot_times2mem(void)
{
	struct rdr_struct_s *pbb;
	BB_PRINT_START();
	pbb = rdr_get_pbb();
	pbb->top_head.reserve = RDR_UNEXPECTED_REBOOT_MARK_ADDR;
	BB_PRINT_END();
}

/*******************************************************************************
Function:		rdr_reset_reboot_times
Description:	reset the file saving reboot times.
Input:		NA
Output:		NA
Return:		NA
Other:		NA
********************************************************************************/
void rdr_reset_reboot_times(void)
{
	struct file *fp;
	ssize_t length;
	char buf;
	mm_segment_t old_fs;
	BB_PRINT_START();
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp = filp_open(RDR_REBOOT_TIMES_FILE, O_CREAT | O_RDWR, 0660);
	if (IS_ERR(fp))	{
		set_fs(old_fs);
		BB_PRINT_ERR("rdr:%s(),open %s fail\n", __func__,
			    RDR_REBOOT_TIMES_FILE);
		return;
	}
	buf = 0;
	vfs_llseek(fp, 0L, SEEK_SET);
	length = vfs_write(fp, &buf, sizeof(buf), &(fp->f_pos));
	if (length == sizeof(buf)) {
		vfs_fsync(fp, 0);
	}

	filp_close(fp, NULL);
	set_fs(old_fs);
	BB_PRINT_END();
}

static int __rdr_create_dir(char *path)
{
	int fd;
	mm_segment_t old_fs;

	/* BB_PRINT_START(); */
	if (path == NULL) {
		BB_PRINT_PN("invalid  parameter. path:%p.\n", path);
		BB_PRINT_END();
		return -1;
	}
	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fd = sys_access(path, 0);
	if (0 != fd) {
		BB_PRINT_DBG("rdr: need create dir %s !\n", path);
		fd = sys_mkdir(path, DIR_LIMIT);
		if (fd < 0) {
			BB_PRINT_ERR("rdr: create dir %s failed! ret = %d\n",
				     path, fd);
			set_fs(old_fs);
			BB_PRINT_END();
			return fd;
		}
		BB_PRINT_DBG("rdr: create dir %s successed [%d]!!!\n", path,
			     fd);
	}

	set_fs(old_fs);

	/* BB_PRINT_END(); */
	return 0;
}


static int rdr_create_dir(const char *path)
{
	char cur_path[64];
	int index = 0;

	BB_PRINT_START();
	if (path == NULL) {
		BB_PRINT_PN("invalid  parameter. path:%p\n", path);
		BB_PRINT_END();
		return -1;
	}
	memset(cur_path, 0, 64);
	if (*path != '/')
		return -1;
	cur_path[index++] = *path++;

	while (*path != '\0') {
		if (*path == '/')
			__rdr_create_dir(cur_path);
		cur_path[index] = *path;
		path++;
		index++;
	}

	BB_PRINT_END();
	return 0;
}



/*******************************************************************************
Function:		rdr_record_erecovery_reason
Description:	write the enter reason of erecovery to /cache/recovery/last_erecovery_entry.
Input:		NA
Output:		NA
Return:		NA
Other:		NA
********************************************************************************/
void rdr_record_erecovery_reason(void)
{
	struct file *fp;
	ssize_t length;
	char *e_reason  = "erecovery_enter_reason:=2015\n";
	mm_segment_t old_fs;
	BB_PRINT_START();

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(RDR_ERECOVERY_REASON_FILE, O_CREAT | O_RDWR, 0660);
	if (IS_ERR(fp)) {
		set_fs(old_fs);
		BB_PRINT_ERR("rdr:%s(),open %s first fail,error No. %p\n", __func__, RDR_ERECOVERY_REASON_FILE, fp);
		rdr_create_dir("/cache/recovery/");
		fp = filp_open(RDR_ERECOVERY_REASON_FILE, O_CREAT | O_RDWR | O_TRUNC, 0660);
		if (IS_ERR(fp)) {
			set_fs(old_fs);
			BB_PRINT_ERR("rdr:%s(),open %s second fail,error No. %p\n", __func__, RDR_ERECOVERY_REASON_FILE, fp);
			return;
		}
	}
	vfs_llseek(fp, 0L, SEEK_SET);
	length = vfs_write(fp, e_reason, strlen(e_reason) + 1, &(fp->f_pos));
	if (length == (strlen(e_reason) + 1)) {
		vfs_fsync(fp, 0);
	}

	filp_close(fp, NULL);
	set_fs(old_fs);
	BB_PRINT_END();
}

/*******************************************************************************
Function:		rdr_record_reboot_times2file
Description:	record the reboot times to file.
Input:		NA
Output:		NA
Return:		int: reboot times.
Other:		NA
********************************************************************************/
int rdr_record_reboot_times2file(void)
{
	struct file *fp;
	ssize_t length;
	char buf  = 0;
	mm_segment_t old_fs;
	BB_PRINT_START();
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp = filp_open(RDR_REBOOT_TIMES_FILE, O_CREAT | O_RDWR, 0660);
	if (IS_ERR(fp)) {
		set_fs(old_fs);
		BB_PRINT_ERR("rdr:%s(),open %s fail\n", __func__,
			   RDR_REBOOT_TIMES_FILE);
		return 0;
	}

	vfs_llseek(fp, 0L, SEEK_SET);
	length = vfs_read(fp, &buf, sizeof(buf), &fp->f_pos);
	if (length == 0 || buf == 0) {
		buf = 0;
	}
	buf++;

	vfs_llseek(fp, 0L, SEEK_SET);
	length = vfs_write(fp, &buf, sizeof(buf), &(fp->f_pos));
	if (length == sizeof(buf)) {
		vfs_fsync(fp, 0);
	}

	filp_close(fp, NULL);
	set_fs(old_fs);
	BB_PRINT_END();
	return buf;
}
