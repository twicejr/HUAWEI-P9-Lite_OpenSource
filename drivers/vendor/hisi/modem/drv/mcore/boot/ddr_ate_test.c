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
#include "ddr_ate_test.h"
#include "bsp_ate.h"

struct ddr_sample_cfg ddr_sample_cfgs[ddr_sample_window_num]={
        {0x9004E22C,0,8 ,0x1FF,{0},{0},{0},{30,30,30,30},{30,30,30,30}},
        {0x9004E234,8,13,0x1F ,{0},{0},{0},{ 1, 1, 1, 1},{ 1, 1, 1, 1}}
};
char *sample_value ="0x000 0x000 0x000 \r\n";

static inline void ddr_ate_print_info(const char *buffer)
{
    int loop;
    volatile unsigned int status = 0;
    while (*buffer != '\0')
    {
        /* wait for the tx fifo is empty and the uart is idle */
        loop = 0x10000;
        while ((status != 0x10) && loop--)
        {
            status = *(volatile unsigned *)(HI_UART0_REGBASE_ADDR + UART_REGOFFSET_FR) & 0x18;
        }
		*(volatile unsigned *)(HI_UART0_REGBASE_ADDR + UART_REGOFFSET_RBR) = (unsigned int)(*buffer);
        buffer++;
    }
}

void ddr_sample_cfg_enforce(void)
{
    osl_reg_set_bit((void *)(0x9004E070), 19, 19, 0x1);
	udelay(1000);
    osl_reg_set_bit((void *)(0x9004E070), 19, 19, 0x0);
	udelay(1000);
    osl_reg_set_bit((void *)(0x9004E004), 15, 15, 0x1);
	udelay(1000);
    osl_reg_set_bit((void *)(0x9004E004), 15, 15, 0x0);
}

/* val max = 0x1FF */
void set_sample_char( u32 sample_start, u32 val )
{
    u32 hex[3];
    char xxx;
    hex[2] = val%0x10;
    hex[1] = val/0x10%0x10;
    hex[0] = val/0x100%0x10;

    xxx = ( ((0xB)>=0xA) ? ('A'+(0xB)-0xA) : ('0'+(0xB)-0) );
    
    sample_value[sample_start]   = HEX_2_ASIC(hex[0]);
    sample_value[sample_start+1] = HEX_2_ASIC(hex[1]);
    sample_value[sample_start+2] = HEX_2_ASIC(hex[2]);
}
void val_to_char(u32 val_original, u32 val_left, u32 val_right)
{
    set_sample_char(2,val_original);
    set_sample_char(8,val_left);
    set_sample_char(14,val_right);
}

s32 ddr_packbist(void)
{
	u32 loop = 0;
	unsigned lp_en = 0;
	unsigned bist_result = 0;
	/* reset bist */
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 0, 1, 0x2);
    
	lp_en = osl_reg_get_bit((void *)(0x90048000 + 0x1c), 0, 0);
	
	osl_reg_set_bit((void *)(0x90048000 + 0x1c), 0, 0, 0);
	osl_reg_set_bit((void *)(0x9004e000 + 0x74), 0, 31, 0x42108);
	for(loop = 0; loop < 4; loop++)
	{
		osl_reg_set_bit((void *)(0x9004e000 + 0x200 + 0x80 * loop), 16, 16, 0x1);
		osl_reg_set_bit((void *)(0x9004e000 + 0x200 + 0x80 * loop), 8, 15, 0xff);
		osl_reg_set_bit((void *)(0x9004e000 + 0x200 + 0x80 * loop), 0, 0, 0x1);
	}
	osl_reg_set_bit((void *)(0x9004e000 + 0x58), 0, 31, 0x67452301);
	osl_reg_set_bit((void *)(0x9004e000 + 0x5c), 0, 31, 0xefcdab89);
	
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 25, 31, 0);
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 24, 24, 0);
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 16, 23, 0);
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 8, 9, 0x3);
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 4, 6, 0x6);
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 0, 1, 0x1);

	udelay(10000);
	
	osl_reg_set_bit((void *)(0x9004e000 + 0x54), 0, 1, 0);
	
	while(osl_reg_get_bit((void *)(0x9004e000 + 0x60), 0, 0) != 0x1){}; /*等待bist finish*/
    
    bist_result = 0;
	for(loop = 0; loop < 4; loop++)
	{
		bist_result += osl_reg_get_bit((void *)(0x9004e000 + 0x204 + 0x80 * loop), 0, 31);//////////
	}
	
	osl_reg_set_bit((void *)(0x90048000 + 0x1c), 0, 0, lp_en);
	if(bist_result)
	{
		//ddr_ate_print_info("\r\npack bist error\r\n");
        return ERROR;
	}
	else
	{
		//ddr_ate_print_info("ok ");
        return OK;
	}
}

void ddr_sample_window_test_12(enum ddr_sample_window_type type)
{
    u32 i,cur_rdqsbdl;
    u32 reg_addr,bit_start,bit_end,val_max;
    char* bl = "0 == bl num, ";

    reg_addr  = ddr_sample_cfgs[type].reg_addr;
    bit_start = ddr_sample_cfgs[type].bit_start;
    bit_end   = ddr_sample_cfgs[type].bit_end;
    val_max   = ddr_sample_cfgs[type].val_max;
    
    ddr_ate_print_info("\r\n pack bist training\r\n");
    
    osl_reg_set_bit((void *)(0x9004e080), 13, 13, 0x0);
    
    for(i=0;i<NUM_OF_DXNRDQSDLY;i++){
        ddr_sample_cfgs[type].val_original[i] = osl_reg_get_bit((void *)(reg_addr + i*0x80), bit_start, bit_end);
        cur_rdqsbdl = ddr_sample_cfgs[type].val_original[i];

        while(1){
            cur_rdqsbdl--;
            if(0==(cur_rdqsbdl)){
                ddr_sample_cfgs[type].val_left[i] = cur_rdqsbdl;
                break;
            }
            
            osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);
            ddr_sample_cfg_enforce();
            if(ddr_packbist() == OK){
                continue;
            }else{
                ddr_sample_cfgs[type].val_left[i] = cur_rdqsbdl+1;
                break;
            }
        }

        cur_rdqsbdl = ddr_sample_cfgs[type].val_original[i];
        osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);
        ddr_sample_cfg_enforce();
        while(1){
            cur_rdqsbdl++;
            if(val_max==(cur_rdqsbdl)){
                ddr_sample_cfgs[type].val_right[i] = cur_rdqsbdl;
                break;
            }
            
            osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);
            ddr_sample_cfg_enforce();
            if(ddr_packbist() == OK){
                continue;
            }else{
                ddr_sample_cfgs[type].val_right[i] = cur_rdqsbdl-1;
                break;
            }
        }

        cur_rdqsbdl = ddr_sample_cfgs[type].val_original[i];
        osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);
        ddr_sample_cfg_enforce();

        switch(type){
            case ddr_sample_window_read:
                ddr_ate_print_info("<read sample> ");
                break;
            case ddr_sample_window_write:
                ddr_ate_print_info("<wirte sample> ");
                break;
            default:
                ddr_ate_print_info("read/wirte sample type error\r\n");
                return;
                break;
        }
        bl[0] = i+'0';
        ddr_ate_print_info(bl);
        ddr_ate_print_info( "original left right ");
        val_to_char(ddr_sample_cfgs[type].val_original[i],ddr_sample_cfgs[type].val_left[i], ddr_sample_cfgs[type].val_right[i]);
        ddr_ate_print_info(sample_value);
    }
    osl_reg_set_bit((void *)(0x9004e080), 13, 13, 0x1);
}

s32 ddr_sample_window_test_3(enum ddr_sample_window_type type)
{
    u32 i,cur_rdqsbdl;
    u32 reg_addr,bit_start,bit_end,val_max;
    reg_addr  = ddr_sample_cfgs[type].reg_addr;
    bit_start = ddr_sample_cfgs[type].bit_start;
    bit_end   = ddr_sample_cfgs[type].bit_end;
    val_max   = ddr_sample_cfgs[type].val_max;

    osl_reg_set_bit((void *)(0x9004e080), 13, 13, 0x0);
    for(i=0;i<NUM_OF_DXNRDQSDLY;i++){
        ddr_sample_cfgs[type].val_original[i] = osl_reg_get_bit((void *)(reg_addr + i*0x80), bit_start, bit_end);
        cur_rdqsbdl = ddr_sample_cfgs[type].val_original[i];

        /* 使用经验值测试左值 */
        if(cur_rdqsbdl>ddr_sample_cfgs[type].left_empirical[i]){
            cur_rdqsbdl = cur_rdqsbdl - ddr_sample_cfgs[type].left_empirical[i];
        }
        else{
            cur_rdqsbdl = 0;
        }
        osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);
        ddr_sample_cfg_enforce();
        if(ddr_packbist() == OK){
            continue;
        }else{
            ddr_ate_print_info( "ddr win left error\r\n ");
            ate_gpio_on(ATE_GPIO_BAD_CHIP);
            __asm__ __volatile__("b .");
            return ERROR;
        }
        /* 使用经验值测试右值 */
        cur_rdqsbdl = ddr_sample_cfgs[type].val_original[i];
        osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);

        cur_rdqsbdl = cur_rdqsbdl + ddr_sample_cfgs[type].right_empirical[i];
        cur_rdqsbdl = (cur_rdqsbdl<ddr_sample_cfgs[type].val_max)? cur_rdqsbdl:ddr_sample_cfgs[type].val_max;

        
        osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);
        ddr_sample_cfg_enforce();
        if(ddr_packbist() == OK){
            continue;
        }else{
            ddr_ate_print_info( "ddr win right error\r\n ");
            ate_gpio_on(ATE_GPIO_BAD_CHIP);
            __asm__ __volatile__("b .");
            return ERROR;
        }
        /* 恢复原值 */
        cur_rdqsbdl = ddr_sample_cfgs[type].val_original[i];
        osl_reg_set_bit((void *)(reg_addr + i*0x80), bit_start, bit_end,cur_rdqsbdl);
        ddr_sample_cfg_enforce();

    }
    osl_reg_set_bit((void *)(0x9004e080), 13, 13, 0x1);
    return 0;
}

void ate_test_m3_ddr_window(void)
{
    s32 ret = 0;
    ret += ddr_sample_window_test_3(ddr_sample_window_read);
    ret += ddr_sample_window_test_3(ddr_sample_window_write);
    if(0==ret){
        ate_gpio_on(ATE_GPIO_DDR_2);
        ddr_ate_print_info("ddr win test pass\r\n");
    }
}

s32 ddr_test_rw(u32 addr, u32 end_addr, u32 val)
{
    u32 test_addr ;
    
    for(test_addr = addr; test_addr<end_addr; ){
        writel(val,test_addr);
        test_addr +=4;
    }
    for(test_addr = addr; test_addr<end_addr; ){
        if( readl(test_addr) != val ){
            return -1;
        }
        test_addr +=4;
    }
    return 0;
}
void ate_test_m3_ddr_rw(void)
{
    u32 test_addr = 0x40000000;
    u32 test_val  = 0xa5a5a5a5;
    u32 test_size = 32*1024;
    u32 ret = 0;
    ret |= ddr_test_rw(test_addr, test_addr+test_size, test_val);
    test_val = 0x5a5a5a5a;
    ret |= ddr_test_rw(test_addr, test_addr+test_size, test_val);
    
    if(ret){
        ddr_ate_print_info("m3 rw ddr error \r\n");
        ate_gpio_on(ATE_GPIO_BAD_CHIP);
        __asm__ __volatile__("b .");
    }else{
    }
}   


