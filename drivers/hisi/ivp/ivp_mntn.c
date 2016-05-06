#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/debugfs.h>
#include "ivp_reg.h"
#include "ivp_core.h"
#include "ivp_log.h"


static inline unsigned int ivp_wdg_reg_info(unsigned int reg)
{
    unsigned int val;
    val = ivp_wdg_reg_read(reg);
    ivp_warn("%#x:%#x", reg, val);
    return val;
}

static inline unsigned int ivp_smmu_reg_info(unsigned int reg)
{
    unsigned int val;
    val = ivp_smmu_reg_read(reg);
    ivp_warn("%#x:%#x", reg, val);
    return val;
}

static inline unsigned int ivp_cfg_reg_info(unsigned int reg)
{
    unsigned int val;
    val = ivp_reg_read(reg);
    ivp_warn("%#x:%#x", reg, val);
    return val;
}

inline void ivp_reg_dump_wdg(void)
{
    //unlock reg
    ivp_wdg_reg_write(WDG_REG_OFF_WDLOCK, WDG_REG_UNLOCK_KEY);
    ivp_info("===================WDG DUMP=======================");
    //dump watch dog reg
    ivp_wdg_reg_info(WDG_REG_OFF_WDLOAD);
    ivp_wdg_reg_info(WDG_REG_OFF_WDVALUE);
    ivp_wdg_reg_info(WDG_REG_OFF_WDCONTROL);
    ivp_wdg_reg_info(WDG_REG_OFF_WDRIS);
    ivp_wdg_reg_info(WDG_REG_OFF_WDMIS);
    ivp_info("===================WDG DUMP LEAVE=======================");
    //lock reg
    ivp_wdg_reg_write(WDG_REG_OFF_WDLOCK, WDG_REG_LOCK_KEY);
}

inline void ivp_reg_dump_smmu(void)
{
    unsigned int val;
    ivp_info("===================SMMU DUMP=======================");
    ivp_cfg_reg_info(IVP_REG_OFF_SMMU_AWAKEBYPASS);
    ivp_cfg_reg_info(IVP_REG_OFF_SMMU_PWR_HANDSHAKE_ST);
    val = ivp_cfg_reg_info(IVP_REG_OFF_SMMU_RST_ST);

    if (!(val & 0x3)) {
        ivp_warn("smmu in reset mode[%#x].Can not dump smmu reg.Return now", val);
        return;
    }

    ivp_smmu_reg_info(SMMU_NS_CB0_FSR);
    ivp_smmu_reg_info(SMMU_NS_GFSR);
    ivp_smmu_reg_info(SMMU_NS_CR0);
    ivp_smmu_reg_info(SMMU_NS_SMR0);
    ivp_smmu_reg_info(SMMU_NS_S2CR0);
    ivp_smmu_reg_info(SMMU_NS_CBAR0);
    ivp_smmu_reg_info(SMMU_NS_CBA2R0);
    ivp_smmu_reg_info(SMMU_NS_CB0_TTBCR);
    ivp_smmu_reg_info(SMMU_NS_CB0_TTBCR2);
    ivp_smmu_reg_info(SMMU_NS_CB0_TTBR0_LOW);
    ivp_smmu_reg_info(SMMU_NS_CB0_SCTLR);
    ivp_info("===================SMMU DUMP LEAVE=======================");
}

inline void ivp_reg_dump_cfg(void)
{
    ivp_info("===================IVP USEC CFG=======================");
    ivp_cfg_reg_info(IVP_REG_OFF_OCDHALTONRESET);
    ivp_cfg_reg_info(IVP_REG_OFF_STATVECTORSEL);
    ivp_cfg_reg_info(IVP_REG_OFF_RUNSTALL);
    ivp_cfg_reg_info(IVP_REG_OFF_PWAITMODE);
    ivp_cfg_reg_info(IVP_REG_OFF_BINTERRUPT);
    ivp_cfg_reg_info(IVP_REG_OFF_DSP_CORE_RESET_STATUS);
    ivp_cfg_reg_info(IVP_REG_OFF_REF_CLOCK_SEL);
    ivp_cfg_reg_info(IVP_REG_OFF_APB_GATE_CLOCK);
    ivp_cfg_reg_info(IVP_REG_OFF_BUS_GATE_CLOCK);
    ivp_cfg_reg_info(IVP_REG_OFF_TIMER_WDG_RST_STATUS);
    ivp_cfg_reg_info(IVP_REG_OFF_DSPCRE_GATE_ST);
    ivp_cfg_reg_info(IVP_REG_OFF_IVP_SYSTEM_QOS_CFG);
    ivp_cfg_reg_info(IVP_REG_OFF_MEM_CTRL0);
    ivp_cfg_reg_info(IVP_REG_OFF_MEM_CTRL1);
    ivp_cfg_reg_info(IVP_REG_OFF_MEM_CTRL2);
    ivp_cfg_reg_info(IVP_REG_OFF_CRG_PERI_GT_ST);
    ivp_cfg_reg_info(IVP_REG_OFF_ADDR_MON_INTR_STAT);
    ivp_info("===================IVP SEC CFG=======================");
    ivp_cfg_reg_info(ADDR_IVP_CFG_SEC_REG_START_REMAP_ADDR);
    ivp_cfg_reg_info(ADDR_IVP_CFG_SEC_REG_REMAP_LENGTH);
    ivp_cfg_reg_info(ADDR_IVP_CFG_SEC_REG_DDR_REMAP_ADDR);
    ivp_info("===================IVP CFG DUMP LEAVE=======================");
}

static void set_smmu_rst_mode(int rst)
{
    if (rst) {
        ivp_reg_write(IVP_REG_OFF_SMMU_RST_DIS, 0x3);
    }
    else {
        ivp_reg_write(IVP_REG_OFF_SMMU_RST_EN, 0x3);
    }
    ivp_cfg_reg_info(IVP_REG_OFF_SMMU_RST_ST);
    ivp_info("smmu in rst mode %d", rst);
}

#define IVP_DIR_NAME    "hisi_ivp"
#define IVP_FILE_NAME   "ivp"
#define CMD_LEN_MAX     (32)

static ssize_t ivp_debug_read(struct file *fd, char __user *buf, size_t count, loff_t *pos)
{
    char tips[CMD_LEN_MAX] = "help!\n";

    ivp_info("Usage========================");
    ivp_info("echo cmd (space) [:param] > ivp");
    ivp_info("param format: 0x[xxx]");
    ivp_info("cmd: 0   ---- dump cfg reg");
    ivp_info("cmd: 1   ---- dump smmu reg");
    ivp_info("cmd: 2   ---- dump watch dog reg");
    ivp_info("other    ---- fault cmd");

    if (*pos >= CMD_LEN_MAX) {
        return 0;
    }

    if (*pos + count > CMD_LEN_MAX) {
        count = CMD_LEN_MAX - *pos;
    }

    if (copy_to_user(buf, tips + *pos, count)) {
        return -EFAULT;
    }

    *pos += count;
    ivp_info("read count:%lu", count);
    return count;
}

static int parse_cmd(const char cmd[], unsigned int *param)
{
    int ret, val;

    if (strchr(cmd, ':')) {
        ret = sscanf(cmd, "%d:%x", &val, param);
        if (ret != 2) {
            goto err;
        }
    }
    else {
        ret = sscanf(cmd, "%d", &val);
        if (ret != 1) {
            goto err;
        }
    }
    ivp_info("buf:[%s] cmd:[%d] param:[%#x]", cmd, val, *param);
    return val;
err:
    ivp_err("parse cmd fail:[%s]", cmd);
    return -1;
}

static ssize_t ivp_debug_write(struct file *fd, const char __user *buf, size_t size, loff_t *pos)
{
    int ret = 0;
    char cmd[CMD_LEN_MAX + 1] = {0};
    unsigned int param = 0;
    unsigned int len = size > CMD_LEN_MAX ? CMD_LEN_MAX : size;
    ret = copy_from_user(cmd, buf, len);
    if (ret) {
        ivp_err("copy fail");
        return -1;
    }
    ret = parse_cmd(cmd, &param);

    switch(ret) {
        case 1:
            ivp_reg_dump_cfg();
            break;
        case 2:
            ivp_reg_dump_smmu();
            break;
        case 3:
            ivp_reg_dump_wdg();
            break;
        case 11:
            set_smmu_rst_mode(param);
            break;
        default:
            ivp_warn("cmd err.%d", ret);
            break;
    }
    return size;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .read  = ivp_debug_read,
    .write = ivp_debug_write,
};

static struct dentry *ivp_parent = NULL;

int ivp_debugfs_register(void)
{
    struct dentry *child;
    ivp_info("enter");
    ivp_parent = debugfs_create_dir(IVP_DIR_NAME, NULL);
    if (NULL == ivp_parent) {
        ivp_err("create debug dir fail");
        return -ENOMEM;
    }
    child = debugfs_create_file(IVP_FILE_NAME, 0664,
				   ivp_parent, NULL,
				   &fops);
    if (NULL == child) {
        ivp_err("create debug dir fail");
        if (ivp_parent != NULL) {
            debugfs_remove_recursive(ivp_parent);
        }
        return -ENOMEM;
    }
    return 0;
}

void ivp_debugfs_unregister(void)
{
    if (ivp_parent != NULL) {
        debugfs_remove_recursive(ivp_parent);
    }
    ivp_info("leave");
}
