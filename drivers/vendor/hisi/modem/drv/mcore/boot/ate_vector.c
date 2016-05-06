/*
 *  Copyright (C), 2015-2018, Hisilicon Technologies Co., Ltd.
 *
 * File name     : ddr_ate_test.c
 * Created       : 2015-11-12
 * Last Modified :
 * Description   : ddr test - read/write sample window size
 * Modification  : Create file
 *
 */
#include <product_config.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <hi_uart.h>
#include "soc_timer.h"

#include "bsp_ate.h"
#ifdef BSP_CONFIG_HI6932
#include "ddr_ate_test_v722.h"
#elif defined(BSP_CONFIG_HI6950)
#include "ddr_ate_test.h"
#endif

unsigned gpio_addr[] = {HI_GPIO0_REGBASE_ADDR, HI_GPIO1_REGBASE_ADDR, 
                        HI_GPIO2_REGBASE_ADDR, HI_GPIO3_REGBASE_ADDR, 
                        HI_GPIO4_REGBASE_ADDR, HI_GPIO5_REGBASE_ADDR, 
                        HI_GPIO6_REGBASE_ADDR, HI_GPIO7_REGBASE_ADDR, 
                        HI_GPIO8_REGBASE_ADDR, HI_GPIO9_REGBASE_ADDR};

u32 ate_vector_version = ATE_VECTOR_VERSION;//0~255

void gpio_output(unsigned group, unsigned index, unsigned level)
{
    unsigned value = 0;

    value = readl(gpio_addr[group]+0x3FC);
    value |= level << index;
    writel(value, gpio_addr[group]+0x3FC);
}

void ate_gpio_on(unsigned index)
{
    if(ATE_GPIO_NONE != index){
        gpio_output(index/ATE_GPIO_PINS_PER_GRP,index%ATE_GPIO_PINS_PER_GRP,1);
    }
}

unsigned int get_timer_value(void)
{
	return readl(FASTBOOT_TIMER_BASE+FASTBOOT_TIMER_CURRENTVALUE);
}

unsigned int get_elapse_ms()
{
	unsigned long long tmp;
	unsigned int timer_get = 0;

	timer_get = get_timer_value();
#ifdef CONFIG_USE_TIMER_STAMP
	timer_get = (unsigned int)0xFFFFFFFF - timer_get;
#endif
	tmp = (unsigned long long)(timer_get & 0xFFFFFFFF);
	tmp = (tmp*1000)>>15;

	return (unsigned int)tmp;
}

void ate_version_set(void)
{
    unsigned i = 0;
    unsigned ate_vector_temp = 0;
    unsigned ate_ver_bit[8];

    if(ate_vector_version > 255){
        return ;
    }

    ate_vector_temp = ate_vector_version;

    for(i = 0; i < 8; i++){
        ate_ver_bit[i] = 0;
    }

    for(i = 0; ate_vector_temp != 0; i++)
    {
        ate_ver_bit[i] = ate_vector_temp % 2;
        ate_vector_temp = ate_vector_temp / 2;
    }

    for(i = 0; i < 8; i++){
        gpio_output(ATE_GPIO_VECTOR_GRP, i, ate_ver_bit[i]);
    }

    return;
}

void ate_vector_init(void)
{
    unsigned i = 0;

    for (i = 0; i < ARRAY_SIZE(gpio_addr); i++) {
        writel(0xFFFFFFFF, gpio_addr[i] + 0x400);
        writel(0x0, gpio_addr[i] + 0x3FC);
    }

    ate_version_set();
}

struct ate_vector_wrap ate_vector_table[] = {
#ifdef BSP_CONFIG_HI6932
    {ate_vector_m3_addr_window, 1, 1, ATE_GPIO_M3BOOT_DDR_WIN_CASE_OK, ATE_GPIO_M3BOOT_DDR_WIN_CASE_FAIL, "m3 ddr window"}
#elif defined(BSP_CONFIG_HI6950)
    {ate_test_m3_ddr_rw, 1, 1, ATE_GPIO_M3BOOT_DDR_RW_CASE_OK, ATE_GPIO_M3BOOT_DDR_RW_CASE_FAIL, "m3 ddr rw"},
    {ate_test_m3_ddr_window, 1, 1, ATE_GPIO_M3BOOT_DDR_WIN_CASE_OK, ATE_GPIO_M3BOOT_DDR_WIN_CASE_FAIL, "m3 ddr window"}
#endif
};

void ate_vector_m3boot(void)
{
    int ret = 0, ret_sum = 0;
    unsigned int case_no = 0;
    
    print_info("[ATE]:m3boot ate case start..\r\n");
    ate_gpio_on(ATE_GPIO_FBOOT_CASE_BEGIN);

    for(case_no = 0; case_no < ARRAY_SIZE(ate_vector_table); case_no++){
        ret = ate_vector_table[case_no].func();
        if(ret){
            print_info("[ATE]:");
            print_info(ate_vector_table[case_no].case_name);
            print_info(" case failed\r\n");
            ate_gpio_on(ate_vector_table[case_no].fail_gpio);
            if(ate_vector_table[case_no].is_bad){
                ate_gpio_on(ATE_GPIO_BAD_CHIP);
            }
            if(ate_vector_table[case_no].is_while){
                while(1);
            }
        }else{
            print_info("[ATE]:");
            print_info(ate_vector_table[case_no].case_name);
            print_info(" case pass\r\n");
            ate_gpio_on(ate_vector_table[case_no].pass_gpio);
        }
        
        ret_sum |= ret;
    }

    if(!ret_sum){
        print_info("ATE]:m3boot ate case pass..\r\n");
        ate_gpio_on(ATE_GPIO_FBOOT_CASE_PASS);
    }else{
        print_info("ATE]:m3boot ate case fail..\r\n");
        ate_gpio_on(ATE_GPIO_FBOOT_CASE_FAIL);
    }
    
    return;
}

