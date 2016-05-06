/*
 *
 *
 * Copyright (C) 2013 Huawei Inc.
 */


#ifndef __HISI_COUL_DRV_TEST_H
#define __HISI_COUL_DRV_TEST_H


struct hisi_coul_test_info{
    int input_batt_exist;
    int input_batt_capacity;
    int input_batt_temp;
    int input_batt_full;
    int input_batt_volt;
    int input_batt_cur;
    int input_batt_fcc;
    int input_event;
    int test_start_flag;
};

extern  struct hisi_coul_test_info *g_hisi_coul_test_info;

#endif
