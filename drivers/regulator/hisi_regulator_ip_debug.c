/*
 * Device driver for tests in IP regulator IC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2011 Hisilicon.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/regulator/consumer.h>

#include <linux/string.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/delay.h>

#define REGULATOR_VIVOBUS_ENA  			100
#define REGULATOR_VIVOBUS_DIS  			101
#define REGULATOR_DSSSUBSYS_ENA			102
#define REGULATOR_DSSSUBSYS_DIS			103
#define REGULATOR_VCODECSUBSYS_ENA  		104
#define REGULATOR_VCODECSUBSYS_DIS  		105
#define REGULATOR_VDEC_ENA  				106
#define REGULATOR_VDEC_DIS  				107
#define REGULATOR_VENC_ENA  				108
#define REGULATOR_VENC_DIS  				109
#define REGULATOR_ISPSUBSYS_ENA  			110
#define REGULATOR_ISPSUBSYS_DIS  			111
#define REGULATOR_IVP_ENA	  				112
#define REGULATOR_IVP_DIS	  				113

#define REGULATOR_DEBUG_ENA	  				114
#define REGULATOR_DEBUG_DIS	  				115
#define REGULATOR_SEC_P_ENA	  				116
#define REGULATOR_SEC_P_DIS	  				117
#define REGULATOR_PERF_ENA	  				118
#define REGULATOR_PERF_DIS	  				119
#define REGULATOR_CSSYS_ENA	  				120
#define REGULATOR_CSSYS_DIS	  				121
#define REGULATOR_USBOTG_ENA	  				122
#define REGULATOR_USBOTG_DIS	  				123
#define REGULATOR_SEC_S_ENA	  				124
#define REGULATOR_SEC_S_DIS	  				125
#define REGULATOR_SOCP_ENA	  				126
#define REGULATOR_SOCP_DIS	  				127
#define REGULATOR_G3D_ENA	  					128
#define REGULATOR_G3D_DIS	  					129
#define REGULATOR_ASP_ENA	  					130
#define REGULATOR_ASP_DIS	  					131
#define REGULATOR_HIFI_ENA	  					132
#define REGULATOR_HIFI_DIS	  					133
#define REGULATOR_MMBUF_ENA	  				134
#define REGULATOR_MMBUF_DIS	  				135
#define REGULATOR_LDO8_ENA	  				136
#define REGULATOR_LDO8_DIS	  				137
#define REGULATOR_LDO26_ENA	  				138
#define REGULATOR_LDO26_DIS	  				139
/***************************ADDR begin*******************************/
#define DSSSUBSYS_BASE_ADDR 	0xE8600000
#define ISPSUBSYS_BASE_ADDR 	0xE8400000
#define VDEC_BASE_ADDR 		0xE8800000
#define VENC_BASE_ADDR 		0xE8900000
#define PERF_BASE_ADDR 		0xFF012000
#define TOP_CSSYS_BASE_ADDR 	0xEC000000
#define SOCP_BASE_ADDR 		0xFF030000
#define SEC_S_BASE_ADDR 		0xFF011000
#define SEC_P_BASE_ADDR 		0xFF010000
#define ASP_BASE_ADDR 			0xE804E000
#define G3D_BASE_ADDR 			0xE8970000
#define MMBUF_BASE_ADDR 		0xFFF02000
#define IVP32_BASE_ADDR 		0xE8D80000
#define IOMCU_BASE_ADDR 		0xFFD7E000
/***************************ADDR end********************************/

struct regulator_ip_test {
	struct resource	*res;
	struct device *dev;
	void __iomem *regs;

	spinlock_t lock;

	struct regulator *vivobus_ip;
	struct regulator *dsssubsys_ip;
	struct regulator *vcodecsubsys_ip;
	struct regulator *vdec_ip;
	struct regulator *venc_ip;
	struct regulator *ispsubsys_ip;
	struct regulator *ivp_ip;
	struct regulator *debugsubsys_ip;
	struct regulator *sec_p_ip;
	struct regulator *perf_ip;
	struct regulator *top_cssys_ip;
	struct regulator *usbotg_ip;
	struct regulator *sec_s_ip;
	struct regulator *socp_ip;
	struct regulator *g3d_ip;
	struct regulator *asp_ip;
	struct regulator *hifi_ip;
	struct regulator *mmbuf_ip;
	struct regulator *ldo8_ip;
	struct regulator *ldo26_ip;
	struct regulator *geterror_ip;

	void __iomem *dsssubsys_reg;
	void __iomem *ispsubsys_reg;
	void __iomem *vdec_reg;
	void __iomem *venc_reg;
	void __iomem *sec_p_reg;
	void __iomem *perf_reg;

	void __iomem *g3d_reg;
	void __iomem *top_cssys_reg;
	void __iomem *socp_reg;
	void __iomem *sec_s_reg;
	void __iomem *asp_reg;
	void __iomem *mmbuf_reg;
	void __iomem *ivp_reg;
};
struct regulator_ip_test *g_regulator_ip_test;
static struct kobject *regulatoriptestobj;
#define MODULE_NAME  "regulatoriptest"
/*const char *regulator_supply;*/
static void regulator_ip_vivobus_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		/*regulator_supply = "vivobustest";*/
		g_regulator_ip_test->vivobus_ip = devm_regulator_get(g_regulator_ip_test->dev, "vivobustest");
		if (IS_ERR(g_regulator_ip_test->vivobus_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->vivobus_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_vivobus_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->vivobus_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("\n<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_dsssubsys_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->dsssubsys_ip = devm_regulator_get(g_regulator_ip_test->dev, "dsssubsystest");
		if (IS_ERR(g_regulator_ip_test->dsssubsys_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->dsssubsys_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}

	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_dsssubsys_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->dsssubsys_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_vcodecsubsys_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->vcodecsubsys_ip = devm_regulator_get(g_regulator_ip_test->dev, "vcodecsubsystest");
		if (IS_ERR(g_regulator_ip_test->vcodecsubsys_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->vcodecsubsys_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}

	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}
static void regulator_ip_vcodecsubsys_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->vcodecsubsys_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}
static void regulator_ip_vdec_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->vdec_ip = devm_regulator_get(g_regulator_ip_test->dev, "vdectest");
		if (IS_ERR(g_regulator_ip_test->vdec_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->vdec_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}

	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}
static void regulator_ip_vdec_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->vdec_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_venc_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->venc_ip = devm_regulator_get(g_regulator_ip_test->dev, "venctest");
		if (IS_ERR(g_regulator_ip_test->venc_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->venc_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}

	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_venc_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->venc_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_ispsubsys_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->ispsubsys_ip = devm_regulator_get(g_regulator_ip_test->dev, "ispsubsystest");
		if (IS_ERR(g_regulator_ip_test->ispsubsys_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->ispsubsys_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}

	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}
static void regulator_ip_ispsubsys_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->ispsubsys_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}
static void regulator_ip_ivp_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->ivp_ip = devm_regulator_get(g_regulator_ip_test->dev, "ivptest");
		if (IS_ERR(g_regulator_ip_test->ivp_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->ivp_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}
static void regulator_ip_ivp_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->ivp_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_debugsubsys_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->debugsubsys_ip = devm_regulator_get(g_regulator_ip_test->dev, "debugsubsystest");
		if (IS_ERR(g_regulator_ip_test->debugsubsys_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->debugsubsys_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}

	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_debugsubsys_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->debugsubsys_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_sec_p_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->sec_p_ip = devm_regulator_get(g_regulator_ip_test->dev, "sec_ptest");
		if (IS_ERR(g_regulator_ip_test->sec_p_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->sec_p_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_sec_p_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->sec_p_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_perf_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->perf_ip = devm_regulator_get(g_regulator_ip_test->dev, "perftest");
		if (IS_ERR(g_regulator_ip_test->perf_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->perf_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_perf_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->perf_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_top_cssys_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->top_cssys_ip = devm_regulator_get(g_regulator_ip_test->dev, "top_cssystest");
		if (IS_ERR(g_regulator_ip_test->top_cssys_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->top_cssys_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_top_cssys_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->top_cssys_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_usbotg_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->usbotg_ip = devm_regulator_get(g_regulator_ip_test->dev, "usbotgtest");
		if (IS_ERR(g_regulator_ip_test->usbotg_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->usbotg_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}

	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_usbotg_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->usbotg_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_sec_s_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->sec_s_ip = devm_regulator_get(g_regulator_ip_test->dev, "sec_stest");
		if (IS_ERR(g_regulator_ip_test->sec_s_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->sec_s_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_sec_s_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->sec_s_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_socp_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->socp_ip = devm_regulator_get(g_regulator_ip_test->dev, "socptest");
		if (IS_ERR(g_regulator_ip_test->socp_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->socp_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_socp_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->socp_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_g3d_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->g3d_ip = devm_regulator_get(g_regulator_ip_test->dev, "g3dtest");
		if (IS_ERR(g_regulator_ip_test->g3d_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->g3d_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_g3d_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->g3d_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_asp_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->asp_ip = devm_regulator_get(g_regulator_ip_test->dev, "asptest");
		if (IS_ERR(g_regulator_ip_test->asp_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->asp_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_asp_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->asp_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}
static void regulator_ip_hifi_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->hifi_ip = devm_regulator_get(g_regulator_ip_test->dev, "hifitest");
		if (IS_ERR(g_regulator_ip_test->hifi_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->hifi_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_hifi_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->hifi_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_mmbuf_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->mmbuf_ip = devm_regulator_get(g_regulator_ip_test->dev, "mmbuftest");
		if (IS_ERR(g_regulator_ip_test->mmbuf_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->mmbuf_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_mmbuf_disable_test(void)
{
	int ret;

	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->mmbuf_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_ldo8_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->ldo8_ip = devm_regulator_get(g_regulator_ip_test->dev, "ldo8test");
		if (IS_ERR(g_regulator_ip_test->ldo8_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->ldo8_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_ldo8_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->ldo8_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_ldo26_enable_test(void)
{
	int ret;
	static int ip_get_flag;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	if (0 == ip_get_flag) {

		g_regulator_ip_test->ldo26_ip = devm_regulator_get(g_regulator_ip_test->dev, "ldo26test");
		if (IS_ERR(g_regulator_ip_test->ldo26_ip)) {
			pr_err("Couldn't get regulator ip [%s]! \n", __func__);
			return;
		} else {
			pr_info("Get regulator ip [%s] succuse!\n", __func__);
		}
		ip_get_flag = 1;
	}
	/*-----------------control ip enable-----------------------*/
	ret = regulator_enable(g_regulator_ip_test->ldo26_ip);
	if (ret != 0) {
		pr_err("Failed to enable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

static void regulator_ip_ldo26_disable_test(void)
{
	int ret;
	pr_info("\n<-----------------------[%s] test begin------------------------>\n", __func__);
	/*-----------------control ip disable-----------------------*/
	ret = regulator_disable(g_regulator_ip_test->ldo26_ip);
	if (ret != 0) {
		pr_err("Failed to disable %s: %d\n", __func__, ret);
		return ;
	}
	pr_info("<-----------------------[%s] test end------------------------>\n", __func__);
}

void regulator_ip_power_on(int regulator_id)
{
	if (regulator_id < 0) {
		printk("Input regulator id[%d] is error!\n", regulator_id);
		return ;
	}
	switch (regulator_id) {
	case REGULATOR_VIVOBUS_ENA:
		regulator_ip_vivobus_enable_test();
		break;
	case REGULATOR_VIVOBUS_DIS:
		regulator_ip_vivobus_disable_test();
		break;
	case REGULATOR_DSSSUBSYS_ENA:
		regulator_ip_dsssubsys_enable_test();
		break;
	case REGULATOR_DSSSUBSYS_DIS:
		regulator_ip_dsssubsys_disable_test();
		break;
	case REGULATOR_VCODECSUBSYS_ENA:
		regulator_ip_vcodecsubsys_enable_test();
		break;
	case REGULATOR_VCODECSUBSYS_DIS:
		regulator_ip_vcodecsubsys_disable_test();
		break;
	case REGULATOR_VDEC_ENA:
		regulator_ip_vdec_enable_test();
		break;
	case REGULATOR_VDEC_DIS:
		regulator_ip_vdec_disable_test();
		break;
	case REGULATOR_VENC_ENA:
		regulator_ip_venc_enable_test();
		break;
	case REGULATOR_VENC_DIS:
		regulator_ip_venc_disable_test();
		break;
	case REGULATOR_ISPSUBSYS_ENA:
		regulator_ip_ispsubsys_enable_test();
		break;
	case REGULATOR_ISPSUBSYS_DIS:
		regulator_ip_ispsubsys_disable_test();
		break;
	case REGULATOR_IVP_ENA:
		regulator_ip_ivp_enable_test();
		break;
	case REGULATOR_IVP_DIS:
		regulator_ip_ivp_disable_test();
		break;
	case REGULATOR_DEBUG_ENA:
		regulator_ip_debugsubsys_enable_test();
		break;
	case REGULATOR_DEBUG_DIS:
		regulator_ip_debugsubsys_disable_test();
		break;
	case REGULATOR_SEC_P_ENA:
		regulator_ip_sec_p_enable_test();
		break;
	case REGULATOR_SEC_P_DIS:
		regulator_ip_sec_p_disable_test();
		break;
	case REGULATOR_PERF_ENA:
		regulator_ip_perf_enable_test();
		break;
	case REGULATOR_PERF_DIS:
		regulator_ip_perf_disable_test();
		break;
	case REGULATOR_CSSYS_ENA:
		regulator_ip_top_cssys_enable_test();
		break;
	case REGULATOR_CSSYS_DIS:
		regulator_ip_top_cssys_disable_test();
		break;
	case REGULATOR_USBOTG_ENA:
		regulator_ip_usbotg_enable_test();
		break;
	case REGULATOR_USBOTG_DIS:
		regulator_ip_usbotg_disable_test();
		break;
	case REGULATOR_SEC_S_ENA:
		regulator_ip_sec_s_enable_test();
		break;
	case REGULATOR_SEC_S_DIS:
		regulator_ip_sec_s_disable_test();
		break;
	case REGULATOR_SOCP_ENA:
		regulator_ip_socp_enable_test();
		break;
	case REGULATOR_SOCP_DIS:
		regulator_ip_socp_disable_test();
		break;
	case REGULATOR_G3D_ENA:
		regulator_ip_g3d_enable_test();
		break;
	case REGULATOR_G3D_DIS:
		regulator_ip_g3d_disable_test();
		break;
	case REGULATOR_ASP_ENA:
		regulator_ip_asp_enable_test();
		break;
	case REGULATOR_ASP_DIS:
		regulator_ip_asp_disable_test();
		break;
	case REGULATOR_HIFI_ENA:
		regulator_ip_hifi_enable_test();
		break;
	case REGULATOR_HIFI_DIS:
		regulator_ip_hifi_disable_test();
		break;
	case REGULATOR_MMBUF_ENA:
		regulator_ip_mmbuf_enable_test();
		break;
	case REGULATOR_MMBUF_DIS:
		regulator_ip_mmbuf_disable_test();
		break;
	case REGULATOR_LDO8_ENA:
		regulator_ip_ldo8_enable_test();
		break;
	case REGULATOR_LDO8_DIS:
		regulator_ip_ldo8_disable_test();
		break;
	case REGULATOR_LDO26_ENA:
		regulator_ip_ldo26_enable_test();
		break;
	case REGULATOR_LDO26_DIS:
		regulator_ip_ldo26_disable_test();
		break;
	default:
		return;
	}
	return;
}

/********************sys interface begin************************************/
static ssize_t show_test_ip_enable(struct device *dev, struct device_attribute *da, char *buf)
{
	return sprintf(buf, "%d\n", 0);
}
static ssize_t set_test_ip_enable(struct device *dev, struct device_attribute *da,
		      const char *buf, size_t count)
{
	long new_value;
	int result = strict_strtol(buf, 10, &new_value);
	printk("----------->set_test_enable<-------------\n");
	if (result < 0)
		return -EINVAL;

	switch (new_value) {
	case REGULATOR_VIVOBUS_ENA:
		regulator_ip_vivobus_enable_test();
		break;
	case REGULATOR_VIVOBUS_DIS:
		regulator_ip_vivobus_disable_test();
		break;
	case REGULATOR_DSSSUBSYS_ENA:
		regulator_ip_dsssubsys_enable_test();
		break;
	case REGULATOR_DSSSUBSYS_DIS:
		regulator_ip_dsssubsys_disable_test();
		break;
	case REGULATOR_VCODECSUBSYS_ENA:
		regulator_ip_vcodecsubsys_enable_test();
		break;
	case REGULATOR_VCODECSUBSYS_DIS:
		regulator_ip_vcodecsubsys_disable_test();
		break;
	case REGULATOR_VDEC_ENA:
		regulator_ip_vdec_enable_test();
		break;
	case REGULATOR_VDEC_DIS:
		regulator_ip_vdec_disable_test();
		break;
	case REGULATOR_VENC_ENA:
		regulator_ip_venc_enable_test();
		break;
	case REGULATOR_VENC_DIS:
		regulator_ip_venc_disable_test();
		break;
	case REGULATOR_ISPSUBSYS_ENA:
		regulator_ip_ispsubsys_enable_test();
		break;
	case REGULATOR_ISPSUBSYS_DIS:
		regulator_ip_ispsubsys_disable_test();
		break;
	case REGULATOR_IVP_ENA:
		regulator_ip_ivp_enable_test();
		break;
	case REGULATOR_IVP_DIS:
		regulator_ip_ivp_disable_test();
		break;
	case REGULATOR_DEBUG_ENA:
		regulator_ip_debugsubsys_enable_test();
		break;
	case REGULATOR_DEBUG_DIS:
		regulator_ip_debugsubsys_disable_test();
		break;
	case REGULATOR_SEC_P_ENA:
		regulator_ip_sec_p_enable_test();
		break;
	case REGULATOR_SEC_P_DIS:
		regulator_ip_sec_p_disable_test();
		break;
	case REGULATOR_PERF_ENA:
		regulator_ip_perf_enable_test();
		break;
	case REGULATOR_PERF_DIS:
		regulator_ip_perf_disable_test();
		break;
	case REGULATOR_CSSYS_ENA:
		regulator_ip_top_cssys_enable_test();
		break;
	case REGULATOR_CSSYS_DIS:
		regulator_ip_top_cssys_disable_test();
		break;
	case REGULATOR_USBOTG_ENA:
		regulator_ip_usbotg_enable_test();
		break;
	case REGULATOR_USBOTG_DIS:
		regulator_ip_usbotg_disable_test();
		break;
	case REGULATOR_SEC_S_ENA:
		regulator_ip_sec_s_enable_test();
		break;
	case REGULATOR_SEC_S_DIS:
		regulator_ip_sec_s_disable_test();
		break;
	case REGULATOR_SOCP_ENA:
		regulator_ip_socp_enable_test();
		break;
	case REGULATOR_SOCP_DIS:
		regulator_ip_socp_disable_test();
		break;
	case REGULATOR_G3D_ENA:
		regulator_ip_g3d_enable_test();
		break;
	case REGULATOR_G3D_DIS:
		regulator_ip_g3d_disable_test();
		break;
	case REGULATOR_ASP_ENA:
		regulator_ip_asp_enable_test();
		break;
	case REGULATOR_ASP_DIS:
		regulator_ip_asp_disable_test();
		break;
	case REGULATOR_HIFI_ENA:
		regulator_ip_hifi_enable_test();
		break;
	case REGULATOR_HIFI_DIS:
		regulator_ip_hifi_disable_test();
		break;
	case REGULATOR_MMBUF_ENA:
		regulator_ip_mmbuf_enable_test();
		break;
	case REGULATOR_MMBUF_DIS:
		regulator_ip_mmbuf_disable_test();
		break;
	case REGULATOR_LDO8_ENA:
		regulator_ip_ldo8_enable_test();
		break;
	case REGULATOR_LDO8_DIS:
		regulator_ip_ldo8_disable_test();
		break;
	default:
		return -EINVAL;
	}

	return count;
}

static DEVICE_ATTR(testip_enable, S_IRUGO | S_IWUSR, show_test_ip_enable,
	set_test_ip_enable);

/* sensors present on all models */
static struct attribute *regulatoriptest_attributes[] = {
	&dev_attr_testip_enable.attr,
	NULL
};

static const struct attribute_group regulatoriptest_group = {
	.attrs = regulatoriptest_attributes,
};


static int regulator_ip_test_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regulator_ip_test *iptest = NULL;
	size_t reg_size = (64*1024);
	size_t reg_size1 = (2*1024*1024);
	int ret = 0;

	iptest = kzalloc(sizeof(*iptest), GFP_KERNEL);
	if (!iptest) {
		dev_err(dev, "cannot allocate regulator_ip_test device info\n");
		ret = -ENOMEM;
		return ret;
	}
	/* get resources */
	iptest->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!iptest->res) {
		ret = -ENOMEM;
		dev_err(dev, "platform_get_resource err, ret=%d\n", ret);
		goto error_res;
	}

	iptest->regs = ioremap(iptest->res->start, resource_size(iptest->res));
	if (!iptest->regs) {
		ret = -ENOMEM;
		dev_err(dev, "cannot map register memory\n");
		goto error_map;
	}

	iptest->dev = &(pdev->dev);

	{
		iptest->dsssubsys_reg = devm_ioremap(&pdev->dev, DSSSUBSYS_BASE_ADDR, reg_size);
		if (iptest->dsssubsys_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->ispsubsys_reg = devm_ioremap(&pdev->dev, ISPSUBSYS_BASE_ADDR, reg_size1);
		if (iptest->ispsubsys_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->venc_reg = devm_ioremap(&pdev->dev, VENC_BASE_ADDR, reg_size);
		if (iptest->venc_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->vdec_reg = devm_ioremap(&pdev->dev, VDEC_BASE_ADDR, reg_size);
		if (iptest->vdec_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->sec_p_reg = devm_ioremap(&pdev->dev, SEC_P_BASE_ADDR, reg_size);
		if (iptest->sec_p_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->perf_reg = devm_ioremap(&pdev->dev, PERF_BASE_ADDR, reg_size);
		if (iptest->perf_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->top_cssys_reg = devm_ioremap(&pdev->dev, TOP_CSSYS_BASE_ADDR, reg_size);
		if (iptest->top_cssys_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->socp_reg = devm_ioremap(&pdev->dev, SOCP_BASE_ADDR, reg_size);
		if (iptest->socp_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->g3d_reg = devm_ioremap(&pdev->dev, G3D_BASE_ADDR, reg_size);
		if (iptest->g3d_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->sec_s_reg = devm_ioremap(&pdev->dev, SEC_S_BASE_ADDR, reg_size);
		if (iptest->sec_s_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->asp_reg = devm_ioremap(&pdev->dev, ASP_BASE_ADDR, reg_size);
		if (iptest->asp_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->mmbuf_reg = devm_ioremap(&pdev->dev, MMBUF_BASE_ADDR, reg_size);
		if (iptest->mmbuf_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
		iptest->ivp_reg = devm_ioremap(&pdev->dev, IVP32_BASE_ADDR, reg_size);
		if (iptest->ivp_reg == NULL) {
			pr_err("%s:failed to get addr %d.\n", __func__, __LINE__);
			return -ENOMEM;
		}
	}

	g_regulator_ip_test = iptest;
	platform_set_drvdata(pdev, iptest);

	regulatoriptestobj = kobject_create_and_add(MODULE_NAME, NULL);
	if(!regulatoriptestobj) {
		pr_err("%s:failed create and add regulatoriptest kobject %d.\n", __func__, __LINE__);
		goto error_map;
	}
	ret = sysfs_create_group(regulatoriptestobj, &regulatoriptest_group);
	if (ret < 0) {
		printk("test_probe, sysfs create group failed.\n");
		goto error_obj_create;
	}
	goto probe_end;
error_obj_create:
	kobject_put(regulatoriptestobj);
error_map:
	release_mem_region(iptest->res->start, resource_size(iptest->res));
error_res:
	kfree(iptest);
probe_end:
	return ret;

}


static int regulator_ip_test_remove(struct platform_device *pdev)

{

	struct regulator_ip_test *iptest = platform_get_drvdata(pdev);

	iounmap(iptest->regs);
	release_mem_region(iptest->res->start, resource_size(iptest->res));

	kfree(iptest);

	platform_set_drvdata(pdev, NULL);


	return 0;

}


static struct of_device_id of_regulator_ip_test_match_tbl[] = {

	{

		.compatible = "hisilicon,regulator-ip-test",

	},

	{ /* end */ }

};


static struct platform_driver regulator_ip_test_driver = {

	.driver = {

		.name	= "regulator_ip_test",

		.owner  = THIS_MODULE,

		.of_match_table = of_regulator_ip_test_match_tbl,

	},

	.probe	= regulator_ip_test_probe,

	.remove	= regulator_ip_test_remove,

};


static int __init regulator_ip_test_init(void)

{
	return platform_driver_register(&regulator_ip_test_driver);

}

late_initcall(regulator_ip_test_init);


void __exit regulator_ip_test_exit(void)

{

	platform_driver_unregister(&regulator_ip_test_driver);

}

module_exit(regulator_ip_test_exit);


MODULE_DESCRIPTION("Hisi ip regulator test driver");

MODULE_LICENSE("GPL v2");
