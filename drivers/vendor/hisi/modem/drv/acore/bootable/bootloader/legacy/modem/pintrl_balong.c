#include <product_config.h>

#include <boot.h>
#include <debug.h>
#include <platform.h>
#include <bsp_memmap.h>
#include <fdt_ops.h>
#include <hi_modem.h>
#include <module.h>
#include <system.h>
#include <module_level.h>
#include <sys.h>
#include <gpio.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <nv_boot.h>

#include <pintrl_balong.h>
//lint --e{715,717,749,835}
#define GPIO_MAX_NUMBER      0x8
#define PINCONFIG_NF_VAL     0xffff

#define SHM_MEM_MODEM_PINTRL_ADDR ((char*)SHM_BASE_ADDR + SHM_OFFSET_IOS)
#define SHM_MEM_MODEM_PINTRL_SIZE SHM_SIZE_IOS

enum
{
    MODEM_PIN_INIT = 0,
    MODEM_PIN_NORMAL,
    MODEM_PIN_POWERDOWN,
    MODEM_PIN_BUTT,
};

struct pinctrl{
    unsigned int gpio;
    unsigned int iomg_off;
    unsigned int iomg_val;
    unsigned int iocg_off;
    unsigned int iocg_val;
    unsigned int gpio_dir;
    unsigned int gpio_val;
    unsigned int reserve;
};

struct pinctrl_property{
    unsigned int gpio_grp;
    unsigned int gpio_bit;
    unsigned int iomg_off;
    unsigned int iomg_val;
    unsigned int iocg_off;
    unsigned int iocg_val;
    unsigned int gpio_dir;
    unsigned int gpio_val;
};

struct pinctrl_head
{
    unsigned int offset;
    unsigned int size;
};

struct modem_pinctrl_head
{
    struct pinctrl_head head[MODEM_PIN_BUTT];
};

#define EXTRACT_BYTE(n)    ((unsigned long long)((uint8_t *)&x)[n])
static inline uint32_t fdt32_to_cpu(uint32_t x)
{
        return ((EXTRACT_BYTE(0) << 24) | (EXTRACT_BYTE(1) << 16) | (EXTRACT_BYTE(2) << 8) | EXTRACT_BYTE(3));
}

static inline unsigned int bsp_pinctrl_base_addr(unsigned int gpio)
{
    return gpio < 176 ? HI_PINTRL_REG_ADDR : HI_PINTRL_SYS_REG_ADDR;
}

#ifdef CONFIG_MODEM_PINTRL
void pinctrl_data_convert(struct pinctrl *pctl, const struct pinctrl_property *prop, unsigned int len)
{
    unsigned int i;

    for(i = 0;i < len;i++)
    {
        pctl[i].gpio      = fdt32_to_cpu(prop[i].gpio_grp) * GPIO_MAX_NUMBER \
                            + fdt32_to_cpu(prop[i].gpio_bit);/* [false alarm]:fortify */

        pctl[i].iomg_off  = fdt32_to_cpu(prop[i].iomg_off);/* [false alarm]:fortify */
        pctl[i].iomg_val  = fdt32_to_cpu(prop[i].iomg_val);/* [false alarm]:fortify */
        pctl[i].iocg_off  = fdt32_to_cpu(prop[i].iocg_off);/* [false alarm]:fortify */
        pctl[i].iocg_val  = fdt32_to_cpu(prop[i].iocg_val);/* [false alarm]:fortify */
        pctl[i].gpio_dir  = fdt32_to_cpu(prop[i].gpio_dir);/* [false alarm]:fortify */
        pctl[i].gpio_val  = fdt32_to_cpu(prop[i].gpio_val);/* [false alarm]:fortify */
        pctl[i].reserve   = 0;/* [false alarm]:fortify */
    }
}

int bsp_pinctrl_conf_set(const struct pinctrl *pctl, unsigned int conf)
{
    unsigned base, addr, value;
//lint --e{438,550}
    if(!pctl)
        return -1;

    base = (unsigned)bsp_pinctrl_base_addr(pctl->gpio);
    addr = base + 0x800 + pctl->iocg_off;

    value = (readl(addr)) & (~0x03);
    writel(value | conf, addr);

    return 0;
}


int bsp_pinctrl_mux_set(const struct pinctrl *pctl, unsigned int mux)
{
    unsigned base;
//lint --e{438,550}
    if(!pctl)
        return -1;

    base = (unsigned)bsp_pinctrl_base_addr(pctl->gpio);
    writel(mux, base + pctl->iomg_off);

    return 0;

}

void pinctrl_config(const struct pinctrl *pctl, unsigned int size)
{
    unsigned int i;
    struct gpio_operators *gpio_ops;
    if(NULL == pctl || (0 == size))
    {
        return;
    }

    gpio_ops = get_operators(GPIO_MODULE_NAME_STR);
    if (NULL == gpio_ops) {
        PRINT_ERROR("[modem_pinctrl]:failed to get gpio_ops operators!\n");
        return ;
    }

    for (i = 0; i < size; i++) {
        /* gpio controller register */
        if(PINCONFIG_NF_VAL != pctl[i].gpio_dir) {
            gpio_ops->gpio_request(pctl[i].gpio);

            if (!pctl[i].gpio_dir) {    /* direction is in */
                gpio_ops->set_direction_input(pctl[i].gpio);

            } else {    /* direction is out */
                gpio_ops->set_direction_output(pctl[i].gpio);
                if(PINCONFIG_NF_VAL != pctl[i].gpio_val) {
                    gpio_ops->set_value(pctl[i].gpio, pctl[i].gpio_val);
                }
            }
        }

        /* set iomg register */
        if ((0xfff != pctl[i].iomg_off) &&
            (PINCONFIG_NF_VAL != pctl[i].iomg_val)) {
            if(bsp_pinctrl_mux_set(&pctl[i], pctl[i].iomg_val))
                return ;
        }

        /* set iocg register */
        if(PINCONFIG_NF_VAL != pctl[i].iocg_val){
            if(bsp_pinctrl_conf_set(&pctl[i], pctl[i].iocg_val))
                return ;
        }

    }

}


/* Modem pinctrl extract from the device tree. */
int modem_pintrl_dts_parse(void *fdt)
{
    int i;
    int ret;
    int len;
    int offset;

    int total_space = 0x80000;
    unsigned int offset_addr = sizeof(struct modem_pinctrl_head);
//lint --e{826,838}
    unsigned int *data = NULL;
    const struct fdt_property *pro;
    struct modem_pinctrl_head *phead = (struct modem_pinctrl_head *)SHM_MEM_MODEM_PINTRL_ADDR;
    char pinctrl_name[16] = "";

    PRINT_ERROR("modem pinctrl parse start!\n");

    memset((void*)SHM_MEM_MODEM_PINTRL_ADDR, 0, SHM_MEM_MODEM_PINTRL_SIZE); /* [false alarm]:Fortify Buffer Overflow */

    struct fdt_operators *fdt_ops = get_operators(FDT_MODULE_NAME_STR);
    if(!fdt_ops){
        PRINT_ERROR("can not get fdt_ops!\n");
        return -1;
    }

    /* let's give it all the room it could need */
    ret = fdt_ops->fdt_open_into(fdt, (void*)fdt, total_space);
    if (ret < 0){
        PRINT_ERROR("Could not open modem dts, fdt=0x%x ret=0x%x.\n", fdt, ret);
        return ret;
    }

    /* Get offset of the pinctrl node */
    ret = fdt_ops->fdt_path_offset(fdt, "/modem_pinctrl");
    if (ret < 0) {
        PRINT_ERROR("Could not find modem_pinctrl node, fdt=0x%x ret=0x%x.\n", fdt, ret);
        return ret;
    }

    offset = ret;

    /* Get property of the pinctrl node */
    pro = fdt_ops->fdt_get_property(fdt, offset, (const char*)"pinctrl-num",&len);
    if(NULL == pro){
        PRINT_ERROR("Could not get property, pro=0x%x fdt=0x%x offset=0x%x len=0x%x.\n", pro, fdt, offset, len);
        return -1;
    }

    data = (unsigned int*)(pro->data);

    for(i = 0;i < MODEM_PIN_BUTT;i++)
    {
        phead->head[i].size = fdt32_to_cpu(data[i]);

        snprintf(pinctrl_name,16,"pinctrl-%d",i);
        pro = fdt_ops->fdt_get_property(fdt, offset, pinctrl_name, &len);
        if(NULL == pro){
            PRINT_ERROR("Could not get property, pro=0x%x fdt=0x%x offset=0x%x len=0x%x.\n", pro, fdt, offset, len);
            return -1;
        }

        if(0 != i)
        {
            offset_addr += phead->head[i].size * (u32)sizeof(struct pinctrl);
        }

        phead->head[i].offset = offset_addr;

        pinctrl_data_convert((struct pinctrl *)((char*)SHM_MEM_MODEM_PINTRL_ADDR + offset_addr), (struct pinctrl_property *)pro->data, phead->head[i].size);

    }

    pinctrl_config((const struct pinctrl *)((char*)SHM_MEM_MODEM_PINTRL_ADDR + phead->head[MODEM_PIN_INIT].offset), phead->head[MODEM_PIN_INIT].size);

    fdt_ops->fdt_pack(fdt);

    PRINT_ERROR("modem pinctrl parse end!\n");

    return 0;
}

#else

int modem_pintrl_dts_parse(void *fdt)
{
    return 0;
}

#endif

