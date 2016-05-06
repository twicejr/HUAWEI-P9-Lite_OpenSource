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
#include "bsp_ate.h"
#include "ddr_ate_test_v722.h"

struct ddr_sample_cfg ddr_sample_cfgs = {
    {0x90040abc,0x90040b3c,0x90040bbc,0x90040c3c},
    {0,8,16},
    {7,15,23},
    255,
    {{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
    {{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
    {{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
#if 0
    {{0x29,0x2f,0x2f},{0x28,0x2f,0x2f},{0x28,0x2f,0x30},{0x27,0x30,0x2c}},
    {{0x2f,0x1f,0x24},{0x31,0x1e,0x20},{0x30,0x1f,0x22},{0x31,0x20,0x26}}
#else
    {{13,14,15},{12,14,15},{12,13,15},{12,13,13}},
    {{15,14,10},{10,13,14},{10,13,15},{10,13,10}}
#endif
};

void ddr_sample_window_get_empirical(void)
{
    u32 i,cur_rdqsbdl,j;
    u32 reg_addr,bit_start,bit_end,val_max;
    int ret = 0;
    val_max   = ddr_sample_cfgs.val_max;
    
    print_info("\r\npack bist training start...");

    for(i=0; i<NUM_OF_REGADDR; i++){
        reg_addr = ddr_sample_cfgs.reg_addr[i];
        print_info_with_hex("\r\nreg_addr=0x",reg_addr);
        for(j=0;j<NUM_OF_DXNRDQSDLY;j++){
            bit_start = ddr_sample_cfgs.bit_start[j];
            bit_end   = ddr_sample_cfgs.bit_end[j];
            ddr_sample_cfgs.val_original[i][j] = osl_reg_get_bit((void *)reg_addr, bit_start, bit_end);
            cur_rdqsbdl = ddr_sample_cfgs.val_original[i][j];

            while(1){
                if(0 == cur_rdqsbdl){
                    ddr_sample_cfgs.val_left[i][j] = cur_rdqsbdl;
                    break;
                }

                cur_rdqsbdl--;
                            
                osl_reg_set_bit((void *)reg_addr, bit_start, bit_end, cur_rdqsbdl);

                ret = exmbist_test_simple(2);
                if(OK == ret){
                    continue;
                }else{
                    ddr_sample_cfgs.val_left[i][j] = cur_rdqsbdl + 1;
                    break;
                }
            }

            ddr_sample_cfgs.val_left[i][j] = ddr_sample_cfgs.val_original[i][j] - ddr_sample_cfgs.val_left[i][j];/*get delta value*/
            cur_rdqsbdl = ddr_sample_cfgs.val_original[i][j];
            osl_reg_set_bit((void *)reg_addr, bit_start, bit_end, cur_rdqsbdl);

            while(1){
                if(val_max == cur_rdqsbdl){
                    ddr_sample_cfgs.val_right[i][j] = cur_rdqsbdl;
                    break;
                }

                cur_rdqsbdl++;

                osl_reg_set_bit((void *)reg_addr, bit_start, bit_end, cur_rdqsbdl);

                ret = exmbist_test_simple(2);
                if(ret == OK){
                    continue;
                }else{
                    ddr_sample_cfgs.val_right[i][j] = cur_rdqsbdl - 1;
                    break;
                }
            }

            ddr_sample_cfgs.val_right[i][j] = ddr_sample_cfgs.val_right[i][j] - ddr_sample_cfgs.val_original[i][j];/*get delta value*/
            cur_rdqsbdl = ddr_sample_cfgs.val_original[i][j];
            osl_reg_set_bit((void *)reg_addr, bit_start, bit_end, cur_rdqsbdl);

            print_info("\r\n<i bits original left right>:");
            print_dec(i);
            print_info_with_dec(" ",bit_start);
            print_info_with_dec("~",bit_end);
            print_info_with_hex(" ",ddr_sample_cfgs.val_original[i][j]);
            print_info_with_hex(" ",ddr_sample_cfgs.val_left[i][j]);
            print_info_with_hex(" ",ddr_sample_cfgs.val_right[i][j]);
        }

        print_info("\r\n------------------------------------------------------------------------");
        print_info("\r\n<skew_addr original left right>:");
        print_hex(reg_addr);
        print_info_with_hex(" ",ddr_sample_cfgs.val_original[i][0] 
                    | ddr_sample_cfgs.val_original[i][1]<<8 
                    |ddr_sample_cfgs.val_original[i][2]<<16);

        print_info_with_hex(" ",ddr_sample_cfgs.val_left[i][0] 
                    | ddr_sample_cfgs.val_left[i][1]<<8 
                    |ddr_sample_cfgs.val_left[i][2]<<16);
        print_info_with_hex(" ",ddr_sample_cfgs.val_right[i][0] 
                    | ddr_sample_cfgs.val_right[i][1]<<8 
                    |ddr_sample_cfgs.val_right[i][2]<<16);
        print_info("\r\n------------------------------------------------------------------------");
    }

    print_info("\r\npack bist training end...\r\n");
}

s32 ddr_sample_window_test(void)
{
    u32 i,cur_rdqsbdl,j;
    u32 reg_addr,bit_start,bit_end,val_max;
    val_max   = ddr_sample_cfgs.val_max;
    u32 start = get_elapse_ms();
    
    print_info("ddr win test start\r\n");

    for(i=0;i<NUM_OF_REGADDR;i++){
        reg_addr = ddr_sample_cfgs.reg_addr[i];
        for(j=0;j<NUM_OF_DXNRDQSDLY;j++){
            bit_start = ddr_sample_cfgs.bit_start[j];
            bit_end   = ddr_sample_cfgs.bit_end[j];

            ddr_sample_cfgs.val_original[i][j] = osl_reg_get_bit((void *)reg_addr, bit_start, bit_end);
            cur_rdqsbdl = ddr_sample_cfgs.val_original[i][j];

            /* 使用经验值测试左值 */
            if(cur_rdqsbdl > ddr_sample_cfgs.left_empirical[i][j]){
                cur_rdqsbdl = cur_rdqsbdl - ddr_sample_cfgs.left_empirical[i][j];
            }
            else{
                cur_rdqsbdl = 0;
            }
            osl_reg_set_bit((void *)reg_addr, bit_start, bit_end, cur_rdqsbdl);

            if(exmbist_test_simple(2) == OK){
                //continue;
            }else{
                print_info("ddr win left error\r\n");
                goto err0;
            }

            /* 使用经验值测试右值 */
            cur_rdqsbdl = ddr_sample_cfgs.val_original[i][j];
            osl_reg_set_bit((void *)reg_addr , bit_start, bit_end,cur_rdqsbdl);

            cur_rdqsbdl = cur_rdqsbdl + ddr_sample_cfgs.right_empirical[i][j];
            cur_rdqsbdl = (cur_rdqsbdl < ddr_sample_cfgs.val_max)?cur_rdqsbdl:ddr_sample_cfgs.val_max;

            osl_reg_set_bit((void *)reg_addr , bit_start, bit_end,cur_rdqsbdl);

            if(exmbist_test_simple(2) == OK){
                //continue;
            }else{
                print_info("[ATE]:ddr win right error\r\n");
                goto err0;
            }

            /* 恢复原值 */
            cur_rdqsbdl = ddr_sample_cfgs.val_original[i][j];
            osl_reg_set_bit((void *)reg_addr , bit_start, bit_end,cur_rdqsbdl);

            print_info("\r\n<i bits original emp_left emp_right>:");
            print_dec(i);
            print_info_with_dec(" ",bit_start);
            print_info_with_dec("~",bit_end);
            print_info_with_hex(" ",ddr_sample_cfgs.val_original[i][j]);
            print_info_with_hex(" ",ddr_sample_cfgs.left_empirical[i][j]);
            print_info_with_hex(" ",ddr_sample_cfgs.right_empirical[i][j]);
            print_info("\r\n");
        }
    }

	print_info("ddr win test pass\r\n");
    print_info_with_dec("time in ddr win test:", get_elapse_ms() - start);
    print_info("ms\r\n");

    return 0;

err0:
    print_info("\r\n<i bits original emp_left emp_right cur>:");
    print_dec(i);
    print_info_with_dec(" ",bit_start);
    print_info_with_dec("~",bit_end);
    print_info_with_hex(" ",ddr_sample_cfgs.val_original[i][j]);
    print_info_with_hex(" ",ddr_sample_cfgs.left_empirical[i][j]);
    print_info_with_hex(" ",ddr_sample_cfgs.right_empirical[i][j]);
    print_info_with_hex(" ",cur_rdqsbdl);
    print_info("\r\n");
    
    /* 恢复原值 */
    cur_rdqsbdl = ddr_sample_cfgs.val_original[i][j];
    osl_reg_set_bit((void *)reg_addr , bit_start, bit_end,cur_rdqsbdl);

    __asm__ __volatile__("b .");
    return ERROR;
}

int ate_vector_m3_addr_window(void)
{
    int ret = 0;

    if(0){
        __asm__ __volatile__("b .");
    }

    if(0){//ddr sample window left/right empirical value
        ddr_sample_window_get_empirical();
    }

    if (1){//ddr sample window test
        ret = ddr_sample_window_test();
     }

    return ret;
}

