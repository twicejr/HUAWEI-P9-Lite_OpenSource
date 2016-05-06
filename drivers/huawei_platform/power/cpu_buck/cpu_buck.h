/*
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#ifndef _CPU_BUCK__H_
#define _CPU_BUCK__H_

#define ERROR_NO_CPU_BUCK_BASE 10450
#define REG_NUMBERS 5
enum error_number
{
    /*for lp8758*/
    LP8758_INT_BUCK3=0,
    LP8758_INT_BUCK2,
    LP8758_INT_BUCK1,
    LP8758_INT_BUCK0,
    LP8758_TDIE_SD,
    LP8758_TDIE_WARN,
    LP8758_BUCK1_ILIM_INT,
    LP8758_BUCK0_PG_INT,
    LP8758_BUCK0_SC_INT,
    LP8758_BUCK0_ILIM_INT,
    /*for hi6422v100*/
    HI6422V100_VSYS_UV,
    HI6422V100_VSYS_OV,
    HI6422V100_OTMP_R,
    HI6422V100_OTMP150_D10R,
    HI6422V100_VBAT2P6_F,
    HI6422V100_VBAT2P3_2D,
    HI6422V100_BUCK34_SCP,
    HI6422V100_BUCK012_SCP,
    HI6422V100_OCPBUCK4,
    HI6422V100_OCPBUCK3,
    HI6422V100_OCPBUCK2,
    HI6422V100_OCPBUCK1,
    HI6422V100_OCPBUCK0,
    VBAT_OCPBUCK4,
    VBAT_OCPBUCK3,
    VBAT_OCPBUCK2,
    VBAT_OCPBUCK1,
    VBAT_OCPBUCK0,
};

struct cpu_buck_info
{
    enum error_number err_no;
    char error_mask;
    int reg_number;
    char* error_info;
};

struct cpu_buck_sample
{
    struct cpu_buck_sample* cbs;
    struct cpu_buck_info* cbi;
    char* reg;
    int info_size;
};

struct cpu_buck_device_info {
    struct device   *dev;
    struct delayed_work cpu_buck_delayed_work;
};
void cpu_buck_register(struct cpu_buck_sample* cbs);
void str_to_reg(char* str, char* reg, int size);
#endif
