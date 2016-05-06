/*
 *  Copyright (C), 2015-2018, Hisilicon Technologies Co., Ltd.
 *
 * File name     : ddr_ate_test.h
 * Created       : 2015-11-12
 * Last Modified :
 * Description   : ddr_ate_test.h
 * Modification  : Create file
 *
 */
#ifndef _DDR_ATE_TEST_H_
#define _DDR_ATE_TEST_H_

#include <product_config.h>
#include <osl_types.h>
#include <osl_bio.h>

#ifndef ERROR
#define ERROR         -1
#endif
#ifndef OK
#define OK            0
#endif

#define NUM_OF_DXNRDQSDLY 4

#define HEX_2_ASIC(val)       ( ((val)>=0xA) ? ('A'+(val)-0xA) : ('0'+(val)-0) )

enum ddr_sample_window_type
{
    ddr_sample_window_read,
    ddr_sample_window_write,
    ddr_sample_window_num,
};

struct ddr_sample_cfg
{
    u32 reg_addr;
    u32 bit_start;
    u32 bit_end;
    u32 val_max;
    u32 val_original[NUM_OF_DXNRDQSDLY];    /*reg 初始值*/
    u32 val_left[NUM_OF_DXNRDQSDLY];        /*traning 值*/
    u32 val_right[NUM_OF_DXNRDQSDLY];       /*traning 值*/
    u32 left_empirical[NUM_OF_DXNRDQSDLY];  /* 经验值，功能筛片时需要赋非0值 */
    u32 right_empirical[NUM_OF_DXNRDQSDLY]; /* 经验值，功能筛片时需要赋非0值 */
};

extern void ddr_sample_window_test_12(enum ddr_sample_window_type type);
extern s32 ddr_sample_window_test_3(enum ddr_sample_window_type type);
extern void ate_test_m3_ddr_window(void);
extern void ate_test_m3_ddr_rw(void);
#endif

