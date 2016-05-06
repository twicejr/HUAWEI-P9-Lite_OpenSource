#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/fs.h>
#include <linux/delay.h>
/* standard error codes */
#include <linux/errno.h>

#include "video_harden.h"
//#include "drv_regulator_user.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_media_sctrl_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_peri_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "video_reg_ops.h"


static struct regulator *media_pd_vdd = NULL;


static  video_harden_vote video_harden_regulator_vote     = {0,0,0,0};
static  video_harden_vote video_harden_rst_iso_clk_vote   = {0,0,0,0};
static  video_harden_vote video_harden_video_noc_vote     = {0,0,0,0};

static struct semaphore video_harden_busy_lock = __SEMAPHORE_INITIALIZER(video_harden_busy_lock, 1);

static int video_harden_device_id_check(video_harden_dev_id_enum dev_id)
{
    switch (dev_id)
    {
        printk(KERN_INFO "dev_id=%d.\n", dev_id);

        case VIDEO_HARDEN_DEV_ID_VCODEC: /* VCODEC */
        case VIDEO_HARDEN_DEV_ID_JPEG: /* JPEG */
        case VIDEO_HARDEN_DEV_ID_ISP: /* ISP */
        {
            return 0;
        }
        default:
        {
            printk(KERN_ERR "invalid dev_id.\n");
            return -1;
        }
     }
}


int video_harden_regulator_enable(video_harden_dev_id_enum dev_id)
{
    int ret = 0;

#if 0 /* refresh regulator logic name, z62576, 20140728 */
	struct device_node *np = NULL;
	struct platform_device *pdev=NULL;
	struct device *dev;

	np = of_find_compatible_node(NULL, NULL, "hisi,video_harden");
	if (np ==NULL) {
		printk(KERN_ERR "the device node video_harden is null\n");
		return ret;
	}

	pdev=of_find_device_by_node(np);
	if (pdev ==NULL) {
		printk(KERN_ERR "the device video_harden is null\n");
		return ret;
	}
	dev=&pdev->dev;
#endif

    printk(KERN_INFO "dev_id is %d.\n",dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return -1;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "video_harden_busy_lock failed\n");
		return -1;
	}

    if ((0 == video_harden_regulator_vote.vcodec_bit)
       && (0 == video_harden_regulator_vote.jpeg_bit)
       && (0 == video_harden_regulator_vote.isp_bit)) {
        /* AO_SC PW MTCMOS EN [0x830]: VIDEO HARDEN power on */
        //media_pd_vdd = regulator_get(dev, "SOC_MED_PD_VDD");
        media_pd_vdd = regulator_get(NULL, "soc_med");
        if (IS_ERR(media_pd_vdd)) {
            media_pd_vdd    = NULL;
            up(&video_harden_busy_lock);
            printk(KERN_ERR "get video harden regulator failed!\n");
            return -1;
        }

        ret = regulator_enable(media_pd_vdd);
        if (0 != ret) {
            regulator_put(media_pd_vdd);
            media_pd_vdd    = NULL;
            up(&video_harden_busy_lock);
            printk(KERN_ERR "failed to enable video harden regulator.\n");
            return -1;
        }

        printk(KERN_INFO "video harden regulator is enabled successfully.\n");
    } else {
        printk(KERN_INFO "video harden regulator is already enabled! skip. \n");
    }

    switch (dev_id) {
        case VIDEO_HARDEN_DEV_ID_VCODEC: /* VCODEC */
            video_harden_regulator_vote.vcodec_bit = 1;
            break;

        case VIDEO_HARDEN_DEV_ID_JPEG: /* JPEG */
            video_harden_regulator_vote.jpeg_bit = 1;
            break;

        case VIDEO_HARDEN_DEV_ID_ISP: /* ISP */
            video_harden_regulator_vote.isp_bit = 1;
            break;
        default:
            break;
    }

    up(&video_harden_busy_lock);

    printk(KERN_INFO "%s, g_video_harden_vote is 0x%x.\n",
        __func__, *((unsigned int *)&video_harden_regulator_vote));

    return 0;
}
EXPORT_SYMBOL(video_harden_regulator_enable);


int video_harden_regulator_disable(video_harden_dev_id_enum dev_id)
{
    int ret = 0;

    printk(KERN_INFO "dev_id is %d.\n", dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return -1;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "video_harden_busy_lock failed\n");
		return -1;
	}

    if ((video_harden_regulator_vote.vcodec_bit == 0)
     && (video_harden_regulator_vote.jpeg_bit == 0)
     && (video_harden_regulator_vote.isp_bit == 0)) {
        up(&video_harden_busy_lock);
        printk(KERN_ERR "Video harden regulator disable is already done! skip.\n");
        return -1;
    }

    switch (dev_id) {
        case VIDEO_HARDEN_DEV_ID_VCODEC: /* VCODEC */
            video_harden_regulator_vote.vcodec_bit    = 0;
            break;

        case VIDEO_HARDEN_DEV_ID_JPEG: /* JPEG */
            video_harden_regulator_vote.jpeg_bit      = 0;
            break;

        case VIDEO_HARDEN_DEV_ID_ISP: /* ISP */
            video_harden_regulator_vote.isp_bit       = 0;
            break;

        default:
            break;
    }

    if ((video_harden_regulator_vote.vcodec_bit == 0)
        && (video_harden_regulator_vote.jpeg_bit == 0)
        && (video_harden_regulator_vote.isp_bit == 0)) {
        /* AO_SC SC_PW_MTCMOS_DIS0 [0x834]: VIDEO HARDEN power off */
        if (NULL != media_pd_vdd) {
            ret = regulator_disable(media_pd_vdd);
            if (ret) {
                up(&video_harden_busy_lock);
                printk(KERN_ERR "Regulator vdec disable failed ret=%d.\n", ret);
                return -1;
            }
            regulator_put(media_pd_vdd);
            media_pd_vdd = NULL;
        }

        printk(KERN_INFO "video harden regulator disable is successful.\n");
    } else {
        printk(KERN_INFO "can't disable video harden Regulator, other module is runing on!.\n");
    }

    up(&video_harden_busy_lock);

    printk(KERN_INFO "%s, g_video_harden_vote is 0x%x.\n",
        __func__, *((unsigned int *)&video_harden_regulator_vote));

    return ret;
}
EXPORT_SYMBOL(video_harden_regulator_disable);

int video_harden_rstdis_isodis_clken(video_harden_dev_id_enum dev_id)
{
    int ret = 0;
    printk(KERN_INFO "dev_id is %d.\n", dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return -1;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "video_harden_busy_lock failed\n");
		return -1;
	}

    if ((0 == video_harden_rst_iso_clk_vote.vcodec_bit)
        && (0 == video_harden_rst_iso_clk_vote.jpeg_bit)
        && (0 == video_harden_rst_iso_clk_vote.isp_bit)) {

        /* AO_SC PW RST DIS [0x814] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(CALC_REG_OFFSET),
                       SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_2codecisp_START,
                       SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_2codecisp_END,
                       0x1);
        /* AO_SC PW ISO DIS [0x824] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(CALC_REG_OFFSET),
                       SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_2codecisp_START,
                       SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_2codecisp_END,
                       0x1);

        /* AO_SC PW CLK EN [0x800] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(CALC_REG_OFFSET),
                       SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_2codecisp_START,
                       SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_2codecisp_END,
                       0x1);

        printk(KERN_INFO "video harden rstdis_isodis_clken is sucessful.\n");
    } else {
        printk(KERN_INFO "video harden rstdis_isodis_clken is already done!. \n");
    }


    switch (dev_id) {
        case VIDEO_HARDEN_DEV_ID_VCODEC: /* VCODEC */
            video_harden_rst_iso_clk_vote.vcodec_bit = 1;
            break;

        case VIDEO_HARDEN_DEV_ID_JPEG: /* JPEG */
            video_harden_rst_iso_clk_vote.jpeg_bit = 1;
            break;

        case VIDEO_HARDEN_DEV_ID_ISP: /* ISP */
            video_harden_rst_iso_clk_vote.isp_bit = 1;
            break;

        default:
            break;
    }

    up(&video_harden_busy_lock);

    printk(KERN_INFO "%s, video_harden_rst_iso_clk_vote  is 0x%x.\n",
        __func__, *((unsigned int *)&video_harden_regulator_vote));

    return ret;
}
EXPORT_SYMBOL(video_harden_rstdis_isodis_clken);


int video_harden_clkdis_isoen_rsten(video_harden_dev_id_enum dev_id)
{
    int ret = 0;

    printk(KERN_INFO "dev_id is %d.\n", dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return -1;
    }

    if ((video_harden_rst_iso_clk_vote.vcodec_bit == 0)
        && (video_harden_rst_iso_clk_vote.jpeg_bit == 0)
        && (video_harden_rst_iso_clk_vote.isp_bit == 0)) {
        printk(KERN_ERR "video_harden_clkdis_isoen_rsten is already done!\n");
        return -1;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "video_harden_busy_lock failed\n");
		return -1;
	}

    switch (dev_id) {
        case VIDEO_HARDEN_DEV_ID_VCODEC: /* VCODEC */
            video_harden_rst_iso_clk_vote.vcodec_bit    = 0;
            break;

        case VIDEO_HARDEN_DEV_ID_JPEG: /* JPEG */
            video_harden_rst_iso_clk_vote.jpeg_bit      = 0;
            break;

        case VIDEO_HARDEN_DEV_ID_ISP: /* ISP */
            video_harden_rst_iso_clk_vote.isp_bit       = 0;
            break;

        default:
            break;
    }

    if ( (video_harden_rst_iso_clk_vote.vcodec_bit == 0)
        && (video_harden_rst_iso_clk_vote.jpeg_bit == 0)
        && (video_harden_rst_iso_clk_vote.isp_bit == 0)) {
        /* AO_SC SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR [0x804] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(CALC_REG_OFFSET),
                       SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_2codecisp_START,
                       SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_2codecisp_END,
                       0x1);

        /* AO_SC SC_PW_ISOEN0 [0x820] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(CALC_REG_OFFSET),
                       SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_2codecisp_START,
                       SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_2codecisp_END,
                       0x1);

        /* AO_SC SC_PW_RSTEN0 [0x810] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                      SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(CALC_REG_OFFSET),
                      SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_2codecisp_START,
                      SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_2codecisp_END,
                      0x1);

        printk(KERN_INFO "video harden clkdis_isoen_rsten is sucessful.\n");
    } else {
        printk(KERN_INFO "video_harden_clkdis_isoen_rsten is already done!.\n");
    }

    up(&video_harden_busy_lock);

    printk(KERN_INFO "video_harden_rst_iso_clk_vote is 0x%x.\n",
        *((unsigned int *)&video_harden_rst_iso_clk_vote));

    return ret;
}
EXPORT_SYMBOL(video_harden_clkdis_isoen_rsten);


int video_harden_regen_rstdis_isodis_clken_check(video_harden_dev_id_enum dev_id)
{
    unsigned int regTmp = 0xff;
    unsigned int regExpect = 0x0;
	int ret = 0;

    printk(KERN_INFO "dev_Id is %d. start video_harden_regen_rstdis_isodis_clken_check.....\n", dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return 0;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "video_harden_busy_lock failed\n");
		return 0;
	}

    if ((1 == video_harden_rst_iso_clk_vote.vcodec_bit)
        || (1 == video_harden_rst_iso_clk_vote.jpeg_bit)
        || (1 == video_harden_rst_iso_clk_vote.isp_bit)) {

        /*================== AO_SC PW MTCMOS STAT [0x838] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_pw_mtcmos_ack_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_pw_mtcmos_ack_stat0_2codecisp_END);
        printk(KERN_INFO "PW MTCMOS STAT = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x1;
        if (regTmp != regExpect)  {
            printk(KERN_ERR "ERR: PW MTCMOS STAT = 0x%x\n", regExpect);
            ret = -1;
        }
        regExpect = 0x0;
        regTmp = 0xffff;


        /*================== AO_SC PW CLK STAT [0x808] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_2codecisp_END);
        printk(KERN_INFO "PW CLK STAT: 2codecisp = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x1;
        if (regTmp != regExpect)  {
            printk(KERN_ERR "ERR:PW CLK STAT: 2codecisp = 0x%x\n", regExpect);
            ret = -1;
        }
        regExpect = 0x0;
        regTmp = 0xffff;


        /*================== AO_SC PW ISO STAT [0x828] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_2codecisp_END);
        printk(KERN_INFO "PW ISO STAT: 2codecisp = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x0;
        if (regTmp != regExpect) {
            printk(KERN_ERR "ERR:PW ISO STAT: 2codecisp = 0x%x\n", regExpect);
            ret = -1;
        }

        regExpect = 0x0;
        regTmp = 0xffff;


        /*================== AO_SC PW RST STAT [0x818] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_2codecisp_END);
        printk(KERN_INFO "PW RST STAT: 2codecisp = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x0;
        if (regTmp != regExpect) {
            printk(KERN_ERR "ERR:PW RST STAT: 2codecisp = 0x%x\n", regExpect);
            ret = -1;
        }

        regExpect = 0x0;
        regTmp = 0xffff;

    } else {
        printk(KERN_INFO "video_harden_regen_rstdis_isodis_clken_check is unnecessary!. \n");
    }

    up(&video_harden_busy_lock);

    return ret;
}
EXPORT_SYMBOL(video_harden_regen_rstdis_isodis_clken_check);


int video_harden_regdis_clkdis_isoen_rsten_check(video_harden_dev_id_enum dev_id)
{
    unsigned int regTmp = 0xff;
    unsigned int regExpect = 0x0;
	int ret = 0;

    printk(KERN_INFO "dev_Id is %d. start video_harden_rstdis_isodis_clken_check.....\n", dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return 0;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "video_harden_busy_lock failed\n");
		return 0;
	}

    if ((0 == video_harden_rst_iso_clk_vote.vcodec_bit)
        && (0 == video_harden_rst_iso_clk_vote.jpeg_bit)
        && (0 == video_harden_rst_iso_clk_vote.isp_bit)) {

        /*================== AO_SC PW MTCMOS STAT [0x838] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_pw_mtcmos_ack_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_pw_mtcmos_ack_stat0_2codecisp_END);
        printk(KERN_INFO "PW MTCMOS STAT = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x0;
        if (regTmp != regExpect) {
            printk(KERN_ERR "ERR: PW MTCMOS STAT = 0x%x\n", regExpect);
            ret = -1;
        }
        regExpect = 0x0;
        regTmp = 0xffff;


        /*================== AO_SC PW CLK STAT [0x808] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_2codecisp_END);
        printk(KERN_INFO "PW CLK STAT: 2codecisp = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x0;
        if (regTmp != regExpect) {
            printk(KERN_ERR "ERR:PW CLK STAT: 2codecisp = 0x%x\n", regExpect);
            ret = -1;
        }
        regExpect = 0x0;
        regTmp = 0xffff;


        /*================== AO_SC PW ISO STAT [0x828] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_2codecisp_END);
        printk(KERN_INFO "PW ISO STAT: 2codecisp = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x1;
        if (regTmp != regExpect) {
            printk(KERN_ERR "ERR:PW ISO STAT: 2codecisp = 0x%x\n", regExpect);
            ret = -1;
        }

        regExpect = 0x0;
        regTmp = 0xffff;


        /*================== AO_SC PW RST STAT [0x818] ==================*/
        regTmp =  phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                                SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(CALC_REG_OFFSET),
                                SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_2codecisp_START,
                                SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_2codecisp_END);
        printk(KERN_INFO "PW RST STAT: 2codecisp = 0x%x, addr=0x%x\n", regTmp,
            (SOC_AO_SCTRL_BASE_ADDR+SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(CALC_REG_OFFSET)));

        regExpect = 0x1;
        if (regTmp != regExpect) {
            printk(KERN_ERR "ERR:PW RST STAT: 2codecisp = 0x%x\n", regExpect);
            ret = -1;
        }

        regExpect = 0x0;
        regTmp = 0xffff;
    } else {
        printk(KERN_INFO "video_harden_regdis_clkdis_isoen_rsten_check is unnecessary!. \n");
    }

    up(&video_harden_busy_lock);

    return ret;
}
EXPORT_SYMBOL(video_harden_regdis_clkdis_isoen_rsten_check);

int video_harden_video_noc_enable(video_harden_dev_id_enum dev_id)
{
	int ret = 0;
    unsigned int reg_val = 0;
    unsigned int count = 0;

    printk(KERN_INFO "%s, dev_id is %d.\n", __func__, dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return -1;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "%s, video_harden_busy_lock failed.\n", __func__);
		return -1;
	}

    if ((0 == video_harden_video_noc_vote.vcodec_bit)
        && (0 == video_harden_video_noc_vote.jpeg_bit)
        && (0 == video_harden_video_noc_vote.isp_bit)) {

        /* AO_SC PW CTRL1[0x8C8]: video noc power idle req, BIT[30][14] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_CTRL1_ADDR(CALC_REG_OFFSET),
                       SOC_AO_SCTRL_SC_PW_CTRL1_acpu_sft_fiq_req_START,
                       SOC_AO_SCTRL_SC_PW_CTRL1_ade_domain_idlereq_msk_END,
                       0x40000000);

        /* AO_SC PW STAT1[0x854]: video noc stat */
        do {
            reg_val = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                SOC_AO_SCTRL_SC_PW_STAT1_ADDR(CALC_REG_OFFSET),
                SOC_AO_SCTRL_SC_PW_STAT1_video_domain_idleack_START,
                SOC_AO_SCTRL_SC_PW_STAT1_video_domain_idleack_END);
            printk(KERN_INFO "%s, SC_PW_STAT1_video_domain_idleack = 0x%0x.\n", __func__, reg_val);
            udelay(10);
            count ++;
            if (count >= 10) {
        		printk(KERN_ERR "%s, video noc stat is not expect.\n", __func__);
        		ret = -1;
                break;
            }
        } while (reg_val != 0);

        printk(KERN_INFO "%s, video noc enable is sucessful.\n", __func__);
    } else {
        printk(KERN_INFO "%s, video noc is already enabled!. \n", __func__);
    }

    switch (dev_id) {
        case VIDEO_HARDEN_DEV_ID_VCODEC: /* VCODEC */
            video_harden_video_noc_vote.vcodec_bit = 1;
            break;

        case VIDEO_HARDEN_DEV_ID_JPEG: /* JPEG */
            video_harden_video_noc_vote.jpeg_bit = 1;
            break;

        case VIDEO_HARDEN_DEV_ID_ISP: /* ISP */
            video_harden_video_noc_vote.isp_bit = 1;
            break;

        default:
            break;
    }

    up(&video_harden_busy_lock);

    printk(KERN_INFO "%s, video_noc_vote is 0x%x.\n",
        __func__, *((unsigned int *)&video_harden_video_noc_vote));

    return ret;
}
EXPORT_SYMBOL(video_harden_video_noc_enable);

int video_harden_video_noc_disable(video_harden_dev_id_enum dev_id)
{
	int ret = 0;
    unsigned int reg_val = 0;
    unsigned int count = 0;

    printk(KERN_INFO "%s, dev_id is %d.\n", __func__, dev_id);

    ret = video_harden_device_id_check(dev_id);
    if (ret != 0) {
        return -1;
    }

    ret = down_interruptible(&video_harden_busy_lock);
	if (0 != ret) {
		printk(KERN_ERR "%s, video_harden_busy_lock failed.\n", __func__);
		return -1;
	}

    switch (dev_id) {
        case VIDEO_HARDEN_DEV_ID_VCODEC: /* VCODEC */
            video_harden_video_noc_vote.vcodec_bit = 0;
            break;

        case VIDEO_HARDEN_DEV_ID_JPEG: /* JPEG */
            video_harden_video_noc_vote.jpeg_bit = 0;
            break;

        case VIDEO_HARDEN_DEV_ID_ISP: /* ISP */
            video_harden_video_noc_vote.isp_bit = 0;
            break;

        default:
            break;
    }

    if ((0 == video_harden_video_noc_vote.vcodec_bit)
        && (0 == video_harden_video_noc_vote.jpeg_bit)
        && (0 == video_harden_video_noc_vote.isp_bit)) {

        /* AO_SC PW CTRL1[0x8C8]: video noc power idle req, BIT[30][14] */
        phy_reg_writel(SOC_AO_SCTRL_BASE_ADDR,
                       SOC_AO_SCTRL_SC_PW_CTRL1_ADDR(CALC_REG_OFFSET),
                       SOC_AO_SCTRL_SC_PW_CTRL1_acpu_sft_fiq_req_START,
                       SOC_AO_SCTRL_SC_PW_CTRL1_ade_domain_idlereq_msk_END,
                       0x40004000);

        /* AO_SC PW STAT1[0x854]: video noc stat */
        do {
            reg_val = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR,
                SOC_AO_SCTRL_SC_PW_STAT1_ADDR(CALC_REG_OFFSET),
                SOC_AO_SCTRL_SC_PW_STAT1_video_domain_idleack_START,
                SOC_AO_SCTRL_SC_PW_STAT1_video_domain_idle_END);
            printk(KERN_INFO "%s, SC_PW_STAT1_video_domain_idleack&idle = 0x%0x \n", __func__, reg_val);
            udelay(10);
            count ++;
            if (count >= 10) {
        		printk(KERN_ERR "%s, video noc stat is not expect.\n", __func__);
        		ret = -1;
                break;
            }
        } while (reg_val != 0x3);

        printk(KERN_INFO "%s, video noc disable is sucessful.\n", __func__);
    } else {
        printk(KERN_INFO "%s, video noc is already disabled!. \n", __func__);
    }

    up(&video_harden_busy_lock);

    printk(KERN_INFO "%s, video_noc_vote is 0x%x.\n",
        __func__, *((unsigned int *)&video_harden_video_noc_vote));

    return ret;
}
EXPORT_SYMBOL(video_harden_video_noc_disable);

int __init video_harden_init(void)
{
    printk(KERN_INFO "begin video_harden_init!\n");
    return 0;
}

void __exit video_harden_exit(void)
{
    printk(KERN_INFO "video_harden_exit!\n");

    return;
}


module_init(video_harden_init);
module_exit(video_harden_exit);

MODULE_AUTHOR("Hisilicon, Inc.");
MODULE_DESCRIPTION("common interface of video harden for vpu¡¢jpeg¡¢isp driver");
MODULE_LICENSE("GPL");

