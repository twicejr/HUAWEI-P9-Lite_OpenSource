#include <string.h>
#include <product_config.h>

#include "securec.h"

#include <osl_bio.h>
#include <osl_spinlock.h>
#include <osl_thread.h>
#include <osl_types.h>
#include <of.h>
#include <soc_memmap.h>
#include <bsp_version.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <LNvCommon.h>
#include <PhyNvInterface.h>
#include <bsp_shared_ddr.h>
#include "pmu_balong.h"
#include "pmu_pmic.h"

spinlock_t g_pmufpga_xofre_spinlock;
typedef unsigned long pmufpga_xoflags_t;
static u32 pmu_fpga_base_addr;
/*----------------------------------基本寄存器操作接口---------------------------------------*/
void pmu_fpga_reg_write( u32 addr, u32 value)
{
    writel( value,(pmu_fpga_base_addr + (addr << 2)));
}
/*****************************************************************************
* 函 数 名  : pmu_fpga_reg_read
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
void  pmu_fpga_reg_read( u32 addr, u32 *pValue)
{
    *pValue = readl((pmu_fpga_base_addr + (addr << 2)));
}
/*****************************************************************************
* 函 数 名  : pmu_fpga_reg_write_mask
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
void pmu_fpga_reg_write_mask(u32 addr, u32 value, u32 mask)
{
    u32 reg_tmp = 0;

    pmu_fpga_reg_read(addr, &reg_tmp);
    reg_tmp &= ~mask;
    reg_tmp |= value;
    pmu_fpga_reg_write(addr, reg_tmp);
}
int pmu_fpga_reg_show(u32 addr)
{
    u32 Value = 0;

    pmu_fpga_reg_read(addr, &Value);
    pmu_print_error("pmuRead addr 0x%x value is 0x%x!!\n",addr,Value);
    return Value;
}
/*****************************************************************************
 函 数 名  : pmu_fpga_version_get
 功能描述  : 获取pmu的版本号
 输入参数  : void
 输出参数  : 无
 返 回 值  : pmu版本号
 调用函数  :
 被调函数  : pmu adp文件调用
*****************************************************************************/
char* pmu_fpga_version_get(void)
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
            pmu_fpga_reg_read(PMIC_VERSION_REG0+i, &val);
            version[i] = (u8)val;
        }
        version[4] = '\0';
        b_geted=true;      
    }    
    return  version;
}


u32 pmu_fpga_subversion_get(void)
{
    u32 regval = 0;
    u32 val1 = 0;
    u32 val2 = 0;

    pmu_fpga_reg_read(PMIC_VERSION_REG4, &val1);
    pmu_fpga_reg_read(PMIC_VERSION_REG5, &val2);

    regval = ((val1 << 8) | val2);
    return  regval;
}


struct pmic_reg_cfg g_hi6421_init_cfg[] ={
    /* BUCK0 */
    {0x00D, 0xC3},
    {0x00E, 0x41},
    {0x00F, 0x63},
    {0x010, 0x21},
    {0x011, 0x60},
    {0x014, 0x19},
    /* BUCK1 */
    {0x019, 0xE3},
    {0x01A, 0x81},
    {0x01B, 0x63},
    {0x01C, 0x21},
    {0x01D, 0x60},
    {0x01E, 0x05},
    {0x020, 0x1C},
    {0x021, 0x02},
    /* BUCK2 */
    {0x025, 0xD3},
    {0x026, 0x41},
    {0x027, 0x63},
    {0x028, 0x21},
    {0x029, 0x60},
    {0x02A, 0x05},
    {0x02C, 0x1A},
    {0x02D, 0x02},
    /* BUCK3 */
    {0x031, 0xE3},
    {0x032, 0x41},
    {0x033, 0x63},
    {0x034, 0x21},
    {0x035, 0x60},
    {0x036, 0x05},
    {0x039, 0x02},
    /* BUCK4 */
    {0x03D, 0xC3},
    {0x03E, 0x01},
    {0x03F, 0x63},
    {0x040, 0x21},
    {0x041, 0x60},
    {0x044, 0x18},
    /* LDO1 */
    {0x049, 0x12},
    /* LDO22 */
    {0x053, 0x21},
    /* LDO08 */
    {0x068,0x00},
    /* LDO15 */
    {0x076,0x00},
    /* LDO24 */
    {0x086,0x00},
    /* LDO29 */
    {0x090,0x00},
    /* HARDWIRE_CTRL1 */
    {0x0C6,0x1A},    
    /* BST_MODE_EN */
    {0x0A4,0x01},
    /* PERI_CTRL0 */
    {0x0C7,0xFF},
    /* PERI_CTRL1 */
    {0x0C8,0xBD},
    /* PERI_VSET_CTRL */
    {0x0C9,0x01},
    /* HARDWIRE_CTRL0 */
    {0x0C5,0x02},
    /* NOPWR_CTRL */
    {0x0A5,0x00},
    /* SYS_CTRL1 */
    {0x0DC,0x10},
    /*32k clk open*/
    {0x0cc, 0x7},
    /*open rfclk*/
    {0x10A, 0x3F},
    {0x109, 0xFF},
    {0x108, 0x0F},
};

struct pmic_reg_cfg g_hi6559_init_cfg[] =
{
    /* BUCK0(G) */
    {0x05C, 0xBA},
    {0x062, 0x72},
    {0x065, 0x94},
    /* BUCK0(W/L) APT */
    {0x05F, 0x01},
    {0x063, 0x3C},
    {0x065, 0x94},
    {0x066, 0x6A},
    /* BUCK1 */
    {0x06B, 0xE4},
    /* BUCK2 */
    {0x073, 0xC5},
    /* BUCK3 */
    {0x07B, 0xD5},
    {0x07E, 0x89},
    /* LDO3 */
    {0x08B, 0x03},
    /* LDO10 */
    {0x092, 0x03},
    /* LDO11 */
    {0x093, 0x02},
    /* LDO15 */
    {0x09C, 0x05},
    /* CLK */
    {0x045, 0x00},
    /* open rf0 clk */
    {0x0BE, 0x01},
    /* open rf1clk */
    {0x0BF, 0x01},
    /* 驱动配置*/
    {0x0C6, 0x03},
    {0x0C7, 0x03},
    {0x0c9, 0x00},
    {0x0CC, 0xFF},
    /* open 32k */
    {0x0CD, 0x03},
};

struct pmic_reg_cfg g_hi6555_init_cfg[] =
{
    /* rf abb clk en */
    {0x117, 0x01},
    {0x118, 0x07},
    {0x10f, 0x01},
    /* ldo 1 3 14 22 28 en */
    {0x016, 0x01},
    {0x018, 0x01},
    {0x029, 0x01},
    {0x022, 0x01},
    {0x02f, 0x01},
};


/*配置pmu初始化确认*/
void pmu_init_reg_show(void)
{
    int i = 0;
    char* version = 0;

    version = pmu_fpga_version_get();

    if(!version)
    {
        pmu_print_error("get version error!");
        return;
    }
        
    if(!strncmp(version,"6421",strlen("6421")))
    {
        for (i = 0; i < sizeof(g_hi6421_init_cfg) / sizeof(g_hi6421_init_cfg[0]); i++)
        {
            pmu_fpga_reg_read(g_hi6421_init_cfg[i].addr, &g_hi6421_init_cfg[i].value);
            pmu_print_error("addr %x ,value is %x.\n",g_hi6421_init_cfg[i].addr,g_hi6421_init_cfg[i].value);
        }
    }
    else if(!strncmp(version,"6559",strlen("6559")))
    {
        for (i = 0; i < sizeof(g_hi6559_init_cfg) / sizeof(g_hi6559_init_cfg[0]); i++)
        {
            pmu_fpga_reg_read(g_hi6559_init_cfg[i].addr, &g_hi6559_init_cfg[i].value);
            pmu_print_error("addr %x ,value is %x.\n",g_hi6559_init_cfg[i].addr,g_hi6559_init_cfg[i].value);
        }
    }
    else
    {
        pmu_print_error("don't support version 0x%x!\n",version);
        return;
    }
    pmu_print_error("init reg show over!");
}

void pmic_dcxo_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
    pmufpga_xoflags_t xo_flags;
    char* version = 0;
    u32 c1_addr;
    u32 c2_addr;
    u32 c2_mask;
    u32 c2_offset;
    u32 c2_value;
	u32 c1_value;
	unsigned int i;

	version = pmu_fpga_version_get();
    if(!strncmp(version,"6421",strlen("6421")))
    {
        c1_addr = 0x106;
        c2_addr = 0x107;
        c2_mask = 0x0f;
        c2_offset = 0;
    }
    else if(!strncmp(version,"6559",strlen("6559")))
    {
        c1_addr = 0xC5;
        c2_addr = 0xC8;
        c2_mask = 0x0f;
        c2_offset = 0;
    }
    else if(!strncmp(version,"6555",strlen("6555")))
    {
        c1_addr = 0x11C;
        c2_addr = 0x11B;
        c2_mask = 0xF0;
        c2_offset = 4;
    }
    else
    {
        pmu_print_error("don't support version %s!\n",version);
        return;
    }

    /*核内互斥*/
    spin_lock_irqsave(&g_pmufpga_xofre_spinlock,xo_flags);
    switch(dcxoId)
    {
        case DCXO_CFIX1:
            /*读取当前配置值*/
            pmu_fpga_reg_read(c1_addr,&c1_value);

            /*配置c1*/
            if(c1_value < value)
            {
                for(i=c1_value+1; i<=value; i++)
                {
                    pmu_fpga_reg_write(c1_addr,i);
                    //pmu_reg_show(c1_addr);
                }
            }
            else if(c1_value >value)
            {
                for(i=c1_value-1; i >= value; i--)
                {
                    pmu_fpga_reg_write(c1_addr,i);
                    //pmu_reg_show(c1_addr);
                    if(i == 0)
                        break;
                }
            }
            pmu_fpga_reg_read(c1_addr,&c1_value);
            pmu_print_info("pmu dcxo c1 is 0x%x!!\n",c1_value);
        break;

        case DCXO_CFIX2:
            /*读取当前配置值*/
            pmu_fpga_reg_read(c2_addr,&c2_value);
            /*bit2-0*/
            c2_value = (c2_value  & c2_mask) >>  c2_offset;

            if(c2_value < value)
            {
                for(i=c2_value+1; i <= value; i++)
                {
                    pmu_fpga_reg_write_mask(c2_addr,i << c2_offset,c2_mask);
                    //pmu_reg_reg_show(c2_addr);
                }
            }
            else if(c2_value > value)
            {
                for(i=c2_value-1; i >= value; i--)
                {
                    pmu_fpga_reg_write_mask(c2_addr,i << c2_offset,c2_mask);
                    //pmu_reg_reg_show(c2_addr);
                    if(i == 0)
                        break;
                }
            }
            /*打印出最后的配置值*/
            pmu_fpga_reg_read(c2_addr,&c2_value);
            /*bit2-0*/
            c2_value = (c2_value  & c2_mask) >>  c2_offset;
            pmu_print_info("pmu dcxo c2 is 0x%x!!\n",c2_value);
            break;

        default:
            pmu_print_error("nothing to do!!\n");
            break;
        }

        spin_unlock_irqrestore(&g_pmufpga_xofre_spinlock,xo_flags);
}
/*****************************************************************************
 函 数 名  : pmu_dcxo_c1c2_set
 功能描述  : pmu 中dcxo c1c2配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : pmu模块初始化时调用
*****************************************************************************/
void pmu_dcxo_c1c2_set(void)
{
#ifdef FEATURE_DRV_SINGLE_XO
    u32 iret;
#if 0
    NV_DCXO_C_TRIM dcxo_c_trim;/*初始化值配为多少?*/
    NV_DCXO_C2_FIX dcxo_c2_fix;


    /*配置初始值*/
    dcxo_c_trim.sCtrim = 0x05;
    dcxo_c_trim.usRsv = 0;
    dcxo_c2_fix.sC2fix = 0x3;
    dcxo_c2_fix.usRsv = 0;

    /*从nv中读取，若读取失败就按照默认值*/
    iret = bsp_nvm_read(EN_NV_ID_DCXO_C_TRIM,(u8*)&dcxo_c_trim,sizeof(NV_DCXO_C_TRIM));
    iret |= bsp_nvm_read(EN_NV_ID_DCXO_C2_FIX,(u8*)&dcxo_c2_fix,sizeof(NV_DCXO_C2_FIX));
#endif
    //UCOM_NV_DCXO_CTRIM_STRU dcxo_ctrim;
    //UCOM_NV_DCXO_C2_FIX_STRU dcxo_c2_fix;
    u16 dcxo_ctrim;
    u16 dcxo_c2_fix;

    dcxo_ctrim = 0x05;
    dcxo_c2_fix = 0x03;

    iret = bsp_nvm_read(en_NV_Item_DCXO_C_TRIM,(u8*)&dcxo_ctrim,sizeof(dcxo_ctrim));
    iret |= bsp_nvm_read(en_NV_Item_DCXO_C2_FIX,(u8*)&dcxo_c2_fix,sizeof(dcxo_c2_fix));

    if(NV_OK != iret)
    {
        pmu_print_error("pmu dcxo c1c2 read nv error,not set,use the default config!\n");
    }
    else
    {
        pmu_print_error("pmu dcxo c1 in nv is %d,c2 in nv is %d!\n",dcxo_ctrim,dcxo_c2_fix);
    }

    /*caitao建议先配置c2，再配置c1*/
    pmic_dcxo_compensate(DCXO_CFIX2,(u32)dcxo_c2_fix);
    pmic_dcxo_compensate(DCXO_CFIX1,(u32)dcxo_ctrim);
#endif
}

void hi6421_init(void)
{
    int i = 0;

    for (i = 0; i < sizeof(g_hi6421_init_cfg) / sizeof(g_hi6421_init_cfg[0]); i++)
    {
        pmu_fpga_reg_write(g_hi6421_init_cfg[i].addr, g_hi6421_init_cfg[i].value);
    }
}

void hi6559_init(void)
{
    int i = 0;

    for (i = 0; i < sizeof(g_hi6559_init_cfg) / sizeof(g_hi6559_init_cfg[0]); i++)
    {
        pmu_fpga_reg_write(g_hi6559_init_cfg[i].addr, g_hi6559_init_cfg[i].value);
    }
}

void hi6555_init(void)
{
    int i = 0;

    for (i = 0; i < sizeof(g_hi6555_init_cfg) / sizeof(g_hi6555_init_cfg[0]); i++)
    {
        pmu_fpga_reg_write(g_hi6555_init_cfg[i].addr, g_hi6555_init_cfg[i].value);
    }
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
int pmu_fpga_init(void)
{
    char node_name[32]           = "hisilicon,pmussifpga";
    char *pmussi_base_addr              = NULL;
    struct device_node *dev_node = NULL;
    char* version = 0;
    unsigned int ssi_delay_addr = 0x21fd6074;
    unsigned int ssi_delay_value = 0;
    int ret = 0;

    dev_node = of_find_compatible_node(NULL,NULL,node_name);
    if(!dev_node)
    {
        pmu_print_error("get pmu dts node failed!\n");
        return BSP_PMU_ERROR;
    }

    /* 内存映射，获得基址 */
    pmussi_base_addr = (char *)of_iomap(dev_node, 0);
    if (NULL == pmussi_base_addr)
    {
        pmu_print_error("pmu fpga iomap fail\n");
        return BSP_PMU_ERROR;
    }

    pmu_fpga_base_addr = (u32)pmussi_base_addr;

    ret = of_property_read_u32_index(dev_node, "ssi_delay_addr", 0, &ssi_delay_addr);
    ret = of_property_read_u32_index(dev_node, "ssi_delay_value", 0, &ssi_delay_value);
    if(ret)
    {
        pmu_print_error("read config form dts failed!\n");
        return BSP_PMU_ERROR;
    }
    writel(ssi_delay_value, ssi_delay_addr);



    version = pmu_fpga_version_get();
    if(!strncmp(version,"6421",strlen("6421")))
    {
        hi6421_init();
    }
    else if(!strncmp(version,"6559",strlen("6559")))
    {
        hi6559_init();
    }
    else if(!strncmp(version,"6555",strlen("6555")))
    {
        hi6555_init();
    }
    else
    {
        pmu_print_error("don't support version %d!\n",version);
        return BSP_PMU_ERROR;
    }

    spin_lock_init(&(g_pmufpga_xofre_spinlock));

    pmu_dcxo_c1c2_set();

    return BSP_PMU_OK;
}
