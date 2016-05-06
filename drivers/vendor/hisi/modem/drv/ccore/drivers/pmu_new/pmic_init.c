#include <string.h>


#include <product_config.h>
#include "securec.h"

#include <osl_bio.h>
#include <osl_spinlock.h>
#include <osl_thread.h>
#include <of.h>
#include <soc_memmap.h>
#include <bsp_version.h>
#include <bsp_hardtimer.h>
#include <bsp_hw_spinlock.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <bsp_slice.h>
#include <LNvCommon.h>
#include <PhyNvInterface.h>
#include <bsp_shared_ddr.h>
#include "pmu_balong.h"
#include "pmu_pmic.h"

struct pmic_xo_info g_pmic_xoinfo;

static u32 pmic_base_addr = 0;
/*----------------------------------基本寄存器操作接口---------------------------------------*/
/*****************************************************************************
* 函 数 名  : pmic_get_base_addr
*
* 功能描述  : 返回pmu基地址
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : pmu初始化之前为0，初始化之后是映射后的基址
*****************************************************************************/

u32 pmic_get_base_addr(void)
{
    return pmic_base_addr;
}
void pmic_reg_write(u32 addr, u32 value)
{
    writel(value,(pmic_base_addr + (addr << 2)));
}
/*****************************************************************************
* 函 数 名  : pmu_reg_read
*
* 功能描述  : 对pmu芯片寄存器的读函数
*
* 输入参数  : u16 addr：待写入的寄存器地址
*             u8 u8Data：读出的数据
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void  pmic_reg_read(u32 addr, u32 *pValue)
{
    *pValue = readl(pmic_base_addr + (addr << 2));
}
/*****************************************************************************
* 函 数 名  : pmu_reg_write_mask
*
* 功能描述  : 对pmu芯片寄存器的某些bit置位
*
* 输入参数  : u16 addr：待写入的寄存器地址
*             u8 u8Data：读出的数据
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void pmic_reg_write_mask(u32 addr, u32 value, u32 mask)
{
    u32 reg_tmp = 0;

    pmic_reg_read(addr, &reg_tmp);
    reg_tmp &= ~mask;
    reg_tmp |= value;
    pmic_reg_write(addr, reg_tmp);
}
int pmic_reg_show(u32 addr)
{
    u32 value = 0;

    pmic_reg_read(addr, &value);
    pmu_print_error("pmuRead addr 0x%x value is 0x%x!!\n",addr,value);
    return (int)value;
}
/*****************************************************************************
 函 数 名  : pmu_version_get
 功能描述  : 获取pmu的版本号
 输入参数  : void
 输出参数  : 无
 返 回 值  : pmu版本号
 调用函数  :
 被调函数  : pmu adp文件调用
*****************************************************************************/

char* pmic_version_get(void)
{
    u32 val = 0;
    u32 i = 0;
    
    static bool b_geted=false;
    static char version[5];

    if(!b_geted)
    {
        (void)memset_s((void*)version, 5, 0, 5);
        
        for(i = 0; i < 4; i++)
        {
            pmic_reg_read(PMIC_VERSION_REG0+i, &val);
            version[i] = (char)val;
        }
        version[4] = '\0';
        b_geted=true;      
    }
    pmu_print_error("version:%s\n", version);
    return  version;

}

u32 pmic_subversion_get(void)
{
    u32 regval = 0;
    u32 val1 = 0;
    u32 val2 = 0;

    pmic_reg_read(PMIC_VERSION_REG4, &val1);
    pmic_reg_read(PMIC_VERSION_REG5, &val2);

    regval = ((val1 << 8) | val2);
    return  regval;
}

#if 0
static struct pmic_reg_cfg g_hi6421_init_cfg[] =
{
#if 0
    {0x10A, 0x3F},
    {0x109, 0xFF},
    {0x108, 0x0F}
#endif
};
static struct pmic_reg_cfg g_hi6552_init_cfg[] =
{
    {0x64, 0x00},
    {0x65, 0x00},
    {0x66, 0x57},
    {0x67, 0x03},
    {0x35, 0x19},
    {0x2f, 0x02}
};
#endif
/*配置pmu初始化确认*/
void pmic_init_show(void)
{
#if 0
    u32 i = 0;
    u32 reg_value = 0;
    u8 version = 0;

    version = (u8)pmic_version_get();
    if(version == 0x36)
    {
        /*coverity[unsigned_compare] */
        for (i = 0; i < sizeof(g_hi6421_init_cfg) / sizeof(g_hi6421_init_cfg[0]); i++)
        {
            pmic_reg_read(g_hi6421_init_cfg[i].addr, &reg_value);
            pmu_print_error("addr 0x%x ,value is 0x%x,read reg is 0x%x.\n",g_hi6421_init_cfg[i].addr,g_hi6421_init_cfg[i].value,reg_value);
        }
    }
    else if(0x31 == version)
    {
        for (i = 0; i < sizeof(g_hi6552_init_cfg) / sizeof(g_hi6552_init_cfg[0]); i++)
        {
            pmic_reg_read(g_hi6552_init_cfg[i].addr, &reg_value);
            pmu_print_error("addr 0x%x ,value is 0x%x,read reg is 0x%x.\n",g_hi6552_init_cfg[i].addr,g_hi6552_init_cfg[i].value,reg_value);
        }
    }
    else
    {
        pmu_print_error("don't support version %d!\n",version);
        return;
    }
#endif
    pmu_print_error("init reg show over!");
}

static inline int pmic_rfclk_para_check(u32 rf_id)
{
    /* 有效性检查 */
    if (g_pmic_xoinfo.xorf_num <= rf_id)
    {
        pmu_print_error("doesn't have rfclk %d!\n",rf_id);
        return BSP_PMU_ERROR;
    }
    else
    {
        return BSP_PMU_OK;
    }
}
u32 rfclk_stamp[4] = {0};
void pmic_mutli_core_lock(void)
{
    int ret = 0;

    print_stamp((u32)&rfclk_stamp[0]);
    if(bsp_get_version_info()->chip_type == CHIP_V750)
    {
        (void)bsp_ipc_spin_lock(IPC_SEM_PMU);
    }
    else if(bsp_get_version_info()->chip_type == CHIP_K3V5)
    {
        ret = hwspin_lock_timeout(HW_PMUCLK_LOCKID,HW_SPINLOCK_WAIT_FOREVER);
        if(BSP_OK != ret){
            pmu_print_error("hwspin lock timeout !\n");
        }
    }
    print_stamp((u32)&rfclk_stamp[1]);
}
void pmic_mutli_core_unlock(void)
{
    int ret = 0;

    print_stamp((u32)&rfclk_stamp[2]);
    if(bsp_get_version_info()->chip_type == CHIP_V750)
    {
        (void)bsp_ipc_spin_unlock(IPC_SEM_PMU);
    }
    else if(bsp_get_version_info()->chip_type == CHIP_K3V5)
    {
        ret = hwspin_unlock(HW_PMUCLK_LOCKID);
        if(BSP_OK != ret){
            pmu_print_error("hwspin unlock error!\n");
        }
    }
    print_stamp((u32)&rfclk_stamp[3]);
}
void pmic_rffreq_set(u32 rf_id,u32 freq)
{
    struct xorf_freq_ctrl *freq_ctrl = NULL;

    if(pmic_rfclk_para_check(rf_id))
        return;

    freq_ctrl = &g_pmic_xoinfo.xorf_ctrl[rf_id].freq_ctrl;

    pmic_reg_write_mask(freq_ctrl->freq_addr,freq << freq_ctrl->freq_offset,freq_ctrl->freq_mask);
}
u32 pmic_rffreq_get(u32 rf_id)
{
    struct xorf_freq_ctrl *freq_ctrl = NULL;
    u32 regval = 0;

    if(pmic_rfclk_para_check(rf_id))
        return (u32)BSP_PMU_ERROR;

    freq_ctrl = &g_pmic_xoinfo.xorf_ctrl[rf_id].freq_ctrl;

    pmic_reg_read(freq_ctrl->freq_addr,&regval);

    return (u32)((regval & freq_ctrl->freq_mask) >> freq_ctrl->freq_offset);
}

void pmic_rfclk_enable(u32 rf_id)
{
    struct pmic_xorf_ctrl *xorf_ctrl = NULL;
    unsigned long rfclk_flag = 0;

    if(pmic_rfclk_para_check(rf_id))
        return;

    xorf_ctrl = &g_pmic_xoinfo.xorf_ctrl[rf_id];

    spin_lock_irqsave(&g_pmic_xoinfo.xorf_lock,rfclk_flag);
    /*set to small*/
    pmic_rffreq_set(rf_id,0x00);
    /*enable clk*/
    pmic_mutli_core_lock();
    pmic_reg_write_mask(xorf_ctrl->reg_ctrl.reg_base,(u32)1 << xorf_ctrl->reg_ctrl.reg_bit,(u32)1 << xorf_ctrl->reg_ctrl.reg_bit);
    pmic_mutli_core_unlock();
    /*delay 6us*/
    udelay(6);
    /*set config value*/
    pmic_rffreq_set(rf_id,xorf_ctrl->freq_ctrl.freq_value);
    spin_unlock_irqrestore(&g_pmic_xoinfo.xorf_lock,rfclk_flag);
}

void pmic_rfclk_disable(u32 rf_id)
{
    struct pmic_xorf_ctrl *xorf_ctrl = NULL;
    unsigned long rfclk_flag = 0;

    if(pmic_rfclk_para_check(rf_id))
        return;

    xorf_ctrl = &g_pmic_xoinfo.xorf_ctrl[rf_id];

    spin_lock_irqsave(&g_pmic_xoinfo.xorf_lock,rfclk_flag);
    pmic_mutli_core_lock();
    pmic_reg_write_mask(xorf_ctrl->reg_ctrl.reg_base,(u32)0 << xorf_ctrl->reg_ctrl.reg_bit,(u32)1 << xorf_ctrl->reg_ctrl.reg_bit);
    pmic_mutli_core_unlock();
    spin_unlock_irqrestore(&g_pmic_xoinfo.xorf_lock,rfclk_flag);
}

int pmic_rfclk_is_enabled(u32 rf_id)
{
    struct pmic_xorf_ctrl *xorf_ctrl = NULL;
    unsigned long rfclk_flag = 0;
    u32 regval = 0;

    if(pmic_rfclk_para_check(rf_id))
        return BSP_PMU_ERROR;

    xorf_ctrl = &g_pmic_xoinfo.xorf_ctrl[rf_id];

    spin_lock_irqsave(&g_pmic_xoinfo.xorf_lock,rfclk_flag);
    pmic_mutli_core_lock();
    pmic_reg_read(xorf_ctrl->reg_ctrl.reg_base,&regval);
    pmic_mutli_core_unlock();
    spin_unlock_irqrestore(&g_pmic_xoinfo.xorf_lock,rfclk_flag);

    return (int)(regval & ((u32)1 << xorf_ctrl->reg_ctrl.reg_bit));
}

void pmic_dcxo_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
    u32 c1_addr = g_pmic_xoinfo.xo_ctrl.c1_base;
    u32 c2_addr = g_pmic_xoinfo.xo_ctrl.c2_base;
    u32 c2_mask = g_pmic_xoinfo.xo_ctrl.c2_mask;
    u32 c2_offset = g_pmic_xoinfo.xo_ctrl.c2_offset;
    u32 c2_value;
    u32 c1_value;
    unsigned int i;
	unsigned long dcxo_flag = 0;

    /*核内互斥*/
    spin_lock_irqsave(&g_pmic_xoinfo.xo_lock, dcxo_flag);
    switch(dcxoId)
    {
        case DCXO_CFIX1:
            /*读取当前配置值*/
            pmic_reg_read(c1_addr,&c1_value);

            /*配置c1*/
            if(c1_value < value)
            {
                for(i=c1_value+1; i<=value; i++)
                {
                    pmic_reg_write(c1_addr,i);
                    //pmu_reg_show(c1_addr);
                }
            }
            else if(c1_value >value)
            {
                for(i=c1_value-1; i >= value; i--)
                {
                    pmic_reg_write(c1_addr,i);
                    //pmu_reg_show(c1_addr);
                    if(i == 0)
                        break;
                }
            }
            pmic_reg_read(c1_addr,&c1_value);
            pmu_print_info("pmu dcxo c1 is 0x%x!!\n",c1_value);
        break;

        case DCXO_CFIX2:
            /*读取当前配置值*/
            pmic_reg_read(c2_addr,&c2_value);
            /*bit2-0*/
            c2_value = (c2_value  & c2_mask) >>  c2_offset;

            if(c2_value < value)
            {
                for(i=c2_value+1; i <= value; i++)
                {
                    pmic_reg_write_mask(c2_addr,i << c2_offset,c2_mask);
                    //pmu_reg_reg_show(c2_addr);
                }
            }
            else if(c2_value > value)
            {
                for(i=c2_value-1; i >= value; i--)
                {
                    pmic_reg_write_mask(c2_addr,i << c2_offset,c2_mask);
                    //pmu_reg_reg_show(c2_addr);
                    if(i == 0)
                        break;
                }
            }
            /*打印出最后的配置值*/
            pmic_reg_read(c2_addr,&c2_value);
            /*bit2-0*/
            c2_value = (c2_value  & c2_mask) >>  c2_offset;
            pmu_print_info("pmu dcxo c2 is 0x%x!!\n",c2_value);
            break;

        default:
            pmu_print_error("nothing to do!!\n");
            break;
        }

        spin_unlock_irqrestore(&g_pmic_xoinfo.xo_lock, dcxo_flag);
}
unsigned int pmic_get_rtc_value(void)
{
    u32 addr = 0x12c;
    u32 val1 = 0;
    u32 val2 = 0;
    u32 val3 = 0;
    u32 val4 = 0;
    u32 value = 0;

    pmic_reg_read(addr + 0, &val1);
    pmic_reg_read(addr + 1, &val2);
    pmic_reg_read(addr + 2, &val3);
    pmic_reg_read(addr + 3, &val4);

    value = (u32)(val1 | ((u32)val2 << 8) | ((u32)val3 << 16) | ((u32)val4 << 24));

    return value;
}

#ifdef CONFIG_AVOID_RFIC6362_LDO27_LEAK
int pmic_set_ldo27_ao(int ao)
{
	if(ao)
	{
		pmic_reg_write_mask(0x0c6,0x1,0x1);
		pmic_reg_write(0x08c, 0x02);
	}
	else
	{
		pmic_reg_write_mask(0x0c6,0x0,0x1);
		pmic_reg_write(0x08c, 0x00);
	}
	return BSP_PMU_OK;
}
#endif

struct pmu_adp_ops pmic_ops = {
    .version_get = pmic_version_get,
    .dcxo_compensate = pmic_dcxo_compensate,
    .rfclk_enable = pmic_rfclk_enable,
    .rfclk_disable = pmic_rfclk_disable,
    .rfclk_is_enabled = pmic_rfclk_is_enabled,
    .get_rtc_value = pmic_get_rtc_value,
    .sim_upres_disable = dummy_sim_upres_disable,
    .ocp_register = pmic_ocp_register,
};
u32 pmic_dcxo_compensate_get(DCXO_COMPENSATE_ID_E dcxoId)
{
    u32 c1_addr = g_pmic_xoinfo.xo_ctrl.c1_base;
    u32 c2_addr = g_pmic_xoinfo.xo_ctrl.c2_base;
    u32 c2_mask = g_pmic_xoinfo.xo_ctrl.c2_mask;
    u32 c2_offset = g_pmic_xoinfo.xo_ctrl.c2_offset;
    u32 c2_value,c1_value,value = 0;

    switch(dcxoId)
    {
        case DCXO_CFIX1:
            /*读取当前配置值*/
            pmic_reg_read(c1_addr,&c1_value);
            pmu_print_info("pmu dcxo c1 is 0x%x!!\n",c1_value);
            value = c1_value;
        break;
        case DCXO_CFIX2:
            /*读取当前配置值*/
            pmic_reg_read(c2_addr,&c2_value);
            /*bit2-0*/
            c2_value = (c2_value  & c2_mask) >>  c2_offset;
            pmu_print_info("pmu dcxo c2 is 0x%x!!\n",c2_value);
            value = c2_value;
            break;

        default:
            pmu_print_error("not support dcxo%d!!\n",dcxoId);
            break;
    }

    return value;
}
/*****************************************************************************
 函 数 名  : pmic_dcxo_compensate_set
 功能描述  : pmic 中dcxo c1c2配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : pmu模块初始化时调用
*****************************************************************************/
void pmic_dcxo_compensate_set(void)
{
    u32 iret;
    //UCOM_NV_DCXO_CTRIM_STRU dcxo_ctrim;
    //UCOM_NV_DCXO_C2_FIX_STRU dcxo_c2_fix;
    u16 dcxo_ctrim = 0;
    u16 dcxo_c2_fix = 0;

    iret = bsp_nvm_read(en_NV_Item_DCXO_C_TRIM,(u8*)&dcxo_ctrim,sizeof(dcxo_ctrim));
    iret |= bsp_nvm_read(en_NV_Item_DCXO_C2_FIX,(u8*)&dcxo_c2_fix,sizeof(dcxo_c2_fix));

    if(NV_OK != iret)
    {
        pmu_print_error("pmu dcxo c1c2 read nv error,not set,need check!\n");
        return;
    }
    else
    {
        pmu_print_error("pmu dcxo c1 in nv is %d,c2 in nv is %d!\n",dcxo_ctrim,dcxo_c2_fix);
    }

    /*caitao建议先配置c2，再配置c1*/
    pmic_dcxo_compensate(DCXO_CFIX2,(u32)dcxo_c2_fix);
    pmic_dcxo_compensate(DCXO_CFIX1,(u32)dcxo_ctrim);
}

void pmic_cfg_init(void)
{

}
void pmic_xo_init(void)
{

    u32 id = 0;
    
    pmic_xo_dts_init();
    /* 6555 rf0 rf1正弦波有问题，有些产品需要配置为方波0x117 bit2设为0*/
    for(id = 0; id < g_pmic_xoinfo.xorf_num; id++)
    {
        if(g_pmic_xoinfo.xorf_ctrl[id].rf_clk.freq_value == INVALIED_VALUE)
        {
            pmu_print_error("rfclk %d don't need change wave.\n", id);
        }
        else
        {
            pmic_reg_write_mask(g_pmic_xoinfo.xorf_ctrl[id].rf_clk.freq_addr, \
                g_pmic_xoinfo.xorf_ctrl[id].rf_clk.freq_value << g_pmic_xoinfo.xorf_ctrl[id].rf_clk.freq_offset, \
                g_pmic_xoinfo.xorf_ctrl[id].rf_clk.freq_mask);
        } 
    }
    
    /*init spinlock*/
    spin_lock_init(&(g_pmic_xoinfo.xo_lock));
    spin_lock_init(&(g_pmic_xoinfo.xorf_lock));

    pmic_dcxo_compensate_set();
}

/*****************************************************************************
 函 数 名  : pmu_init
 功能描述  : PMU模块初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 备注说明  : fastboot中完成将电压控制表拷贝到ddr中，
             设置nv项中设定的默认电压及eco模式。
             其他核目前均为打桩。
*****************************************************************************/
void pmu_pmic_init(void)
{
    char node_name[32]           = "hisilicon,pmu_pmic_mdm";
    struct device_node *dev_node = NULL;
    void *pmussi_base = NULL;
    int ret;

    //asm volatile("b .");
   
    dev_node = of_find_compatible_node(NULL,NULL,node_name);
    if(!dev_node)
    {
        pmu_print_error("get pmu dts node failed!\n");
    }
    /* 内存映射，获得基址 */
  
    pmussi_base = of_iomap(dev_node, 0);
    if (NULL == pmussi_base)
    {
        pmu_print_error("pmussi ioremap fail\n");
        return ;
    }

    if(bsp_get_version_info()->board_type == BSP_BOARD_TYPE_SFT)
    {
        dev_node = of_find_compatible_node(NULL,NULL,"hisilicon,pmu_pmicsft_mdm");
        if(!dev_node)
        {
            pmu_print_error("get pmic sft dts node failed!\n");
        }
        /* bbp已映射，直接读取基址 */
   
        ret = of_property_read_u32_index(dev_node, "reg", 0, (u32*)&pmussi_base);
        if(ret)
        {
            pmu_print_error("pmussi sft read for dts fail\n");
            return ;
        }
    }
    pmic_base_addr = (u32)pmussi_base;
    pmu_print_error("pmussi addr: 0x%x!\n",pmic_base_addr);

    pmic_xo_init();
    pmic_cfg_init();/*初始化硬件参数*/
    pmic_volt_init();/*初始化电压源控制*/
    (void)pmu_adpops_register(&pmic_ops);/*注册对外函数*/
}
