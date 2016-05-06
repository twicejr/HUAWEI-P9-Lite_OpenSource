#include <osl_common.h>
#include <osl_malloc.h>
#include <osl_bio.h>

#include "securec.h"

#include "bsp_shared_ddr.h"
#include "bsp_memmap.h"
#include <bsp_hardtimer.h>
#include "gpio_balong.h"
#include "bsp_om.h"

#include "pintrl_balong.h"

#define PINCONFIG_NF_VAL     0xffff

#define SHM_MEM_MODEM_PINTRL_ADDR ((unsigned char*)SHM_BASE_ADDR + SHM_OFFSET_IOS)
#define SHM_MEM_MODEM_PINTRL_SIZE SHM_SIZE_IOS

#define ios_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IOS, "[pinctrl]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define ios_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_IOS, "[pinctrl]: "fmt, ##__VA_ARGS__))


struct pinctrl_head
{
    unsigned int offset;
    unsigned int size;
};

struct modem_pintrl_head
{    
    struct pinctrl_head head[MODEM_PIN_BUTT];
};

/* config modem pintrl status */
struct modem_pintrl_head *g_pinctrl_head = NULL;
unsigned int pinctrl_addr_ao = 0;
unsigned int pinctrl_addr_pd = 0;

static inline unsigned int bsp_pinctrl_base_addr(unsigned int gpio)
{
    return (gpio < 176) ? pinctrl_addr_pd : pinctrl_addr_ao;
}

static struct pinctrl * get_pinctrl(unsigned int mode, unsigned int gpio)
{
    unsigned int begin = 0;
    unsigned int end   = 0;
    unsigned int index = 0;
    struct pinctrl *pctl  = NULL;
    struct modem_pintrl_head *phead = g_pinctrl_head;

    if(mode >= MODEM_PIN_BUTT || (gpio >= GPIO_MAX_GROUP * GPIO_MAX_NUMBER))
    {
        ios_print_error("pintrl get error, mode=%d, gpio=%d.\n", mode, gpio);        
        return NULL;
    }
    
    end  = phead->head[mode].size - 1;
    pctl = (struct pinctrl *)((char*)phead + phead->head[mode].offset);

    while(begin <= end)
    {
        index = begin + ((end - begin) / 2);
        if(gpio < pctl[index].gpio)
        {
            end = index - 1;
        }
        else if(gpio > pctl[index].gpio)
        {
            begin = index + 1;
        }
        else{
            return &pctl[index];
        }
    }

    return NULL;

}

struct pinctrl *bsp_pinctrl_get(unsigned int mode, unsigned int gpio)
{
    return get_pinctrl(mode, gpio);
}

void bsp_pinctrl_put(const struct pinctrl *pctl)
{
    if(!pctl)
        return ;

    /*do nothing*/
}

int bsp_pinctrl_conf_set(const struct pinctrl *pctl, unsigned int conf)
{
    unsigned int base, addr, value;

    if(!pctl)
        return -1;
    
    base = bsp_pinctrl_base_addr(pctl->gpio);
    addr = base + 0x800 + pctl->iocg_off;

    value = readl(addr) & (~0x03);
    writel(value | conf, addr);

    return 0;
}


int bsp_pinctrl_mux_set(const struct pinctrl *pctl, unsigned int mux)
{
    unsigned int base;

    if(!pctl)
        return -1;
    
    base = bsp_pinctrl_base_addr(pctl->gpio);
    writel(mux, base + pctl->iomg_off);

    return 0;

}

int bsp_pinctrl_mux_get(const struct pinctrl *pctl)
{
    unsigned int base;

    if(!pctl)
        return -1;

    base = bsp_pinctrl_base_addr(pctl->gpio);

    return (int)readl(base + pctl->iomg_off);
}

int bsp_pinctrl_mux_modify (struct pinctrl *pctl, unsigned int mux)
{
    if(!pctl)
        return -1;
    //if(PINCONFIG_NF_VAL != pinctrl->iomg_val)
    pctl->iomg_val = mux;
    return 0;
}

int bsp_pinctrl_conf_modify(struct pinctrl *pctl, unsigned int conf)
{
    if(!pctl)
        return -1;

    //if(PINCONFIG_NF_VAL != pinctrl->iocg_val)
    pctl->iocg_val = conf;
    return 0;
}

int bsp_pinctrl_gpio_modify(struct pinctrl *pctl, unsigned int dir, unsigned int val)
{
    if(!pctl)
        return -1;

    //if(PINCONFIG_NF_VAL != pinctrl->gpio_dir)
    pctl->gpio_dir = dir;
    
    //if(PINCONFIG_NF_VAL != pinctrl->gpio_val)
    pctl->gpio_val = val;
    return 0;
}



void pinctrl_config(struct pinctrl *pctl, unsigned int size)
{
    unsigned int i;
    if(NULL == pctl || (0 == size))
    {
        return;
    }
    
    for (i = 0; i < size; i++) {        
        /* gpio controller register */
        if(PINCONFIG_NF_VAL != pctl[i].gpio_dir) {
            if (!pctl[i].gpio_dir) {    /* direction is in */
                bsp_gpio_direction_input(pctl[i].gpio);
                
            } else {    /* direction is out */
                bsp_gpio_direction_output(pctl[i].gpio , PINCONFIG_NF_VAL != pctl[i].gpio_val ? pctl[i].gpio_val : 0);
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



void modem_pinctrl_debug(int mode)
{
    unsigned int i = 0;    
    unsigned int size = 0;
    struct pinctrl *pctl = NULL;
    struct modem_pintrl_head *phead = g_pinctrl_head;

    if(mode >= MODEM_PIN_BUTT) {
        ios_print_error("modem pintrl mode is error, mode=%d.\n", mode);
        return ;
    }
    
    size = phead->head[mode].size;
    pctl = (struct pinctrl *)((char*)phead + phead->head[mode].offset);
    
    ios_print_info("iocfg table size is %d\n", size);
    ios_print_info("  gpio  iomg  iocg  dir  value\n");
    
    for(i = 0;i < size;i++) {
        ios_print_info("%5d %5d %5d %5d %5d \n", pctl[i].gpio, 
                                                pctl[i].iomg_val,
                                                pctl[i].iocg_val, 
                                                pctl[i].gpio_dir, 
                                                pctl[i].gpio_val);

    }

}

void modem_pinctrl_init(void)
{
    struct modem_pintrl_head *pmem = (struct modem_pintrl_head *)SHM_MEM_MODEM_PINTRL_ADDR;
    unsigned int pin_num   = pmem->head[MODEM_PIN_INIT].size    \
                            + pmem->head[MODEM_PIN_NORMAL].size \
                            + pmem->head[MODEM_PIN_POWERDOWN].size;

    unsigned int size = sizeof(struct modem_pintrl_head) + pin_num * sizeof(struct pinctrl);
    if(size > SHM_MEM_MODEM_PINTRL_SIZE){
        ios_print_error("modem pinctrl memory %d expend %d!\n", size, SHM_MEM_MODEM_PINTRL_SIZE);
    }
    
    g_pinctrl_head = osl_malloc(size);
    if(NULL == g_pinctrl_head) {
        ios_print_error("modem pinctrl malloc %d not success, use share memory instead.\n", size);
        g_pinctrl_head = (struct modem_pintrl_head *)SHM_MEM_MODEM_PINTRL_ADDR;
        return;
    }
    memcpy_s(g_pinctrl_head, size, SHM_MEM_MODEM_PINTRL_ADDR, size);

    pinctrl_addr_pd = (unsigned int)ioremap((MMU_VA_T)HI_PINTRL_REG_ADDR, HI_PINTRL_REG_SIZE);
    if(0 == pinctrl_addr_pd) {
        ios_print_error("pinctrl ioremap fail, addr 0x%x, size 0x%x.\n", pinctrl_addr_pd, HI_PINTRL_REG_SIZE);
        return;
    }

    pinctrl_addr_ao = (unsigned int)ioremap((MMU_VA_T)HI_PINTRL_SYS_REG_ADDR, HI_PINTRL_SYS_REG_SIZE);
    if(0 == pinctrl_addr_ao) {
        ios_print_error("pinctrl ioremap fail, addr 0x%x, size 0x%x.\n", pinctrl_addr_ao, HI_PINTRL_SYS_REG_SIZE);
        return;
    }

    ios_print_error("modem pinctrl init ok!\n");
}
void modem_pintrl_config(int mode)
{

    if(mode >= MODEM_PIN_BUTT) {
        ios_print_error("modem pintrl mode is error, mode=%d.\n", mode);
        return;
    }

    if(NULL == g_pinctrl_head) {
        return;
    }

    pinctrl_config((struct pinctrl *)((char*)g_pinctrl_head + g_pinctrl_head->head[mode].offset), g_pinctrl_head->head[mode].size);

}

