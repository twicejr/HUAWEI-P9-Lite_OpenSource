/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_driver.c
  版 本 号   : 初稿
  作    者   : fansaihua f00204170
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic device resource
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    作    者   : fansaihua f00204170
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/module.h>

#include <mach/irqs.h>

#include "soc_smart_interface.h"
#include "pmic_common.h"
#include "regulator_pmic_info.h"

/* channel voltage set list*/
PMU_LOCAL BSP_U32 buck1_set[]={BUCK1_LEVEL_0_VALUE,BUCK1_LEVEL_1_VALUE,BUCK1_LEVEL_2_VALUE,BUCK1_LEVEL_3_VALUE,
                               BUCK1_LEVEL_4_VALUE,BUCK1_LEVEL_5_VALUE,BUCK1_LEVEL_6_VALUE,BUCK1_LEVEL_7_VALUE,
                               BUCK1_LEVEL_8_VALUE,BUCK1_LEVEL_9_VALUE,BUCK1_LEVEL_10_VALUE,BUCK1_LEVEL_11_VALUE,
                               BUCK1_LEVEL_12_VALUE,BUCK1_LEVEL_13_VALUE,BUCK1_LEVEL_14_VALUE,BUCK1_LEVEL_15_VALUE,
                               BUCK1_LEVEL_16_VALUE,BUCK1_LEVEL_17_VALUE,BUCK1_LEVEL_18_VALUE,BUCK1_LEVEL_19_VALUE,
                               BUCK1_LEVEL_20_VALUE,BUCK1_LEVEL_21_VALUE,BUCK1_LEVEL_22_VALUE,BUCK1_LEVEL_23_VALUE,
                               BUCK1_LEVEL_24_VALUE,BUCK1_LEVEL_25_VALUE,BUCK1_LEVEL_26_VALUE,BUCK1_LEVEL_27_VALUE,
                               BUCK1_LEVEL_28_VALUE,BUCK1_LEVEL_29_VALUE,BUCK1_LEVEL_30_VALUE,BUCK1_LEVEL_31_VALUE,
                               BUCK1_LEVEL_32_VALUE,BUCK1_LEVEL_33_VALUE,BUCK1_LEVEL_34_VALUE,BUCK1_LEVEL_35_VALUE,
                               BUCK1_LEVEL_36_VALUE,BUCK1_LEVEL_37_VALUE,BUCK1_LEVEL_38_VALUE,BUCK1_LEVEL_39_VALUE,
                               BUCK1_LEVEL_40_VALUE,BUCK1_LEVEL_41_VALUE,BUCK1_LEVEL_42_VALUE,BUCK1_LEVEL_43_VALUE,
                               BUCK1_LEVEL_44_VALUE,BUCK1_LEVEL_45_VALUE,BUCK1_LEVEL_46_VALUE,BUCK1_LEVEL_47_VALUE,
                               BUCK1_LEVEL_48_VALUE,BUCK1_LEVEL_49_VALUE,BUCK1_LEVEL_50_VALUE,BUCK1_LEVEL_51_VALUE,
                               BUCK1_LEVEL_52_VALUE,BUCK1_LEVEL_53_VALUE,BUCK1_LEVEL_54_VALUE,BUCK1_LEVEL_55_VALUE,
                               BUCK1_LEVEL_56_VALUE,BUCK1_LEVEL_57_VALUE,BUCK1_LEVEL_58_VALUE,BUCK1_LEVEL_59_VALUE,
                               BUCK1_LEVEL_60_VALUE,BUCK1_LEVEL_61_VALUE,BUCK1_LEVEL_62_VALUE,BUCK1_LEVEL_63_VALUE};

PMU_LOCAL BSP_U32 buck2_set[]={BUCK2_LEVEL_0_VALUE,BUCK2_LEVEL_1_VALUE,BUCK2_LEVEL_2_VALUE,BUCK2_LEVEL_3_VALUE,
                               BUCK2_LEVEL_4_VALUE,BUCK2_LEVEL_5_VALUE,BUCK2_LEVEL_6_VALUE,BUCK2_LEVEL_7_VALUE,
                               BUCK2_LEVEL_8_VALUE,BUCK2_LEVEL_9_VALUE,BUCK2_LEVEL_10_VALUE,BUCK2_LEVEL_11_VALUE,
                               BUCK2_LEVEL_12_VALUE,BUCK2_LEVEL_13_VALUE,BUCK2_LEVEL_14_VALUE,BUCK2_LEVEL_15_VALUE,
                               BUCK2_LEVEL_16_VALUE,BUCK2_LEVEL_17_VALUE,BUCK2_LEVEL_18_VALUE,BUCK2_LEVEL_19_VALUE,
                               BUCK2_LEVEL_20_VALUE,BUCK2_LEVEL_21_VALUE,BUCK2_LEVEL_22_VALUE,BUCK2_LEVEL_23_VALUE,
                               BUCK2_LEVEL_24_VALUE,BUCK2_LEVEL_25_VALUE,BUCK2_LEVEL_26_VALUE,BUCK2_LEVEL_27_VALUE,
                               BUCK2_LEVEL_28_VALUE,BUCK2_LEVEL_29_VALUE,BUCK2_LEVEL_30_VALUE,BUCK2_LEVEL_31_VALUE,
                               BUCK2_LEVEL_32_VALUE,BUCK2_LEVEL_33_VALUE,BUCK2_LEVEL_34_VALUE,BUCK2_LEVEL_35_VALUE,
                               BUCK2_LEVEL_36_VALUE,BUCK2_LEVEL_37_VALUE,BUCK2_LEVEL_38_VALUE,BUCK2_LEVEL_39_VALUE,
                               BUCK2_LEVEL_40_VALUE,BUCK2_LEVEL_41_VALUE,BUCK2_LEVEL_42_VALUE,BUCK2_LEVEL_43_VALUE,
                               BUCK2_LEVEL_44_VALUE,BUCK2_LEVEL_45_VALUE,BUCK2_LEVEL_46_VALUE,BUCK2_LEVEL_47_VALUE,
                               BUCK2_LEVEL_48_VALUE,BUCK2_LEVEL_49_VALUE,BUCK2_LEVEL_50_VALUE,BUCK2_LEVEL_51_VALUE,
                               BUCK2_LEVEL_52_VALUE,BUCK2_LEVEL_53_VALUE,BUCK2_LEVEL_54_VALUE,BUCK2_LEVEL_55_VALUE,
                               BUCK2_LEVEL_56_VALUE,BUCK2_LEVEL_57_VALUE,BUCK2_LEVEL_58_VALUE,BUCK2_LEVEL_59_VALUE,
                               BUCK2_LEVEL_60_VALUE,BUCK2_LEVEL_61_VALUE,BUCK2_LEVEL_62_VALUE,BUCK2_LEVEL_63_VALUE};

PMU_LOCAL BSP_U32 buck3_set[]={BUCK3_LEVEL_0_VALUE,BUCK3_LEVEL_1_VALUE,BUCK3_LEVEL_2_VALUE,BUCK3_LEVEL_3_VALUE,
                               BUCK3_LEVEL_4_VALUE,BUCK3_LEVEL_5_VALUE,BUCK3_LEVEL_6_VALUE,BUCK3_LEVEL_7_VALUE,
                               BUCK3_LEVEL_8_VALUE,BUCK3_LEVEL_9_VALUE,BUCK3_LEVEL_10_VALUE,BUCK3_LEVEL_11_VALUE,
                               BUCK3_LEVEL_12_VALUE,BUCK3_LEVEL_13_VALUE,BUCK3_LEVEL_14_VALUE,BUCK3_LEVEL_15_VALUE};

PMU_LOCAL BSP_U32 buck4_set[]={BUCK4_LEVEL_0_VALUE,BUCK4_LEVEL_1_VALUE,BUCK4_LEVEL_2_VALUE,BUCK4_LEVEL_3_VALUE,
                               BUCK4_LEVEL_4_VALUE,BUCK4_LEVEL_5_VALUE,BUCK4_LEVEL_6_VALUE,BUCK4_LEVEL_7_VALUE,
                               BUCK4_LEVEL_8_VALUE,BUCK4_LEVEL_9_VALUE,BUCK4_LEVEL_10_VALUE,BUCK4_LEVEL_11_VALUE,
                               BUCK4_LEVEL_12_VALUE,BUCK4_LEVEL_13_VALUE,BUCK4_LEVEL_14_VALUE,BUCK4_LEVEL_15_VALUE};

PMU_LOCAL BSP_U32 ldo1_set[]={1900000,1950000,2000000,2050000,2100000,2150000,2200000,2250000};
PMU_LOCAL BSP_U32 ldo2_set[]={2500000,2600000,2700000,2800000,2900000,3000000,3100000,3200000};
PMU_LOCAL BSP_U32 ldo3_set[]={  800000,  850000, 900000,  950000,1000000,1050000,1100000,1150000};
PMU_LOCAL BSP_U32 ldo4_set[]={PMU_LVS_VOL_SET_INVAILD};
PMU_LOCAL BSP_U32 ldo5_set[]={1600000,1650000,1700000,1750000,1800000,1850000,1900000,1950000};
PMU_LOCAL BSP_U32 ldo6_set[]={2600000,2650000,2700000,2750000,2800000,2850000,2900000,2950000};
PMU_LOCAL BSP_U32 ldo7_set[]={1800000,1850000,2850000,2900000,3000000,3100000,3200000,3300000};
PMU_LOCAL BSP_U32 ldo8_set[]={1000000,1025000,1050000,1075000,1100000,1125000,1150000,1175000};
PMU_LOCAL BSP_U32 ldo9_set[]={1800000,1850000,2850000,2900000,3000000,3100000,3200000,3300000};
PMU_LOCAL BSP_U32 ldo10_set[]={1800000,1850000,1900000,2750000,2800000,2850000,2900000,3000000};
PMU_LOCAL BSP_U32 ldo11_set[]={1800000,1850000,2850000,2900000,3000000,3100000,3200000,3300000};
PMU_LOCAL BSP_U32 ldo12_set[]={1800000,1850000,2850000,2900000,3000000,3100000,3200000,3300000};
PMU_LOCAL BSP_U32 ldo13_set[]={1600000,1650000,1700000,1750000,1800000,1850000,1900000,1950000};
PMU_LOCAL BSP_U32 ldo14_set[]={2500000,2600000,2700000,2800000,2900000,3000000,3100000,3200000};
PMU_LOCAL BSP_U32 ldo15_set[]={1600000,1650000,1700000,1750000,1800000,1850000,1900000,1950000};
PMU_LOCAL BSP_U32 ldo16_set[]={1650000,1700000,1750000,1800000,1850000,1900000,1950000,2000000};
PMU_LOCAL BSP_U32 ldo17_set[]={2500000,2600000,2700000,2800000,2900000,3000000,3100000,3200000};
PMU_LOCAL BSP_U32 ldo18_set[]={1600000,1650000,1700000,1750000,1800000,1850000,1900000,1950000};
PMU_LOCAL BSP_U32 ldo19_set[]={1800000,1850000,1900000,2750000,2800000,2850000,2900000,3000000};
PMU_LOCAL BSP_U32 ldo20_set[]={1700000,1750000,1800000,1850000,1900000,1950000,2000000,2050000};
PMU_LOCAL BSP_U32 ldo21_set[]={1650000,1700000,1750000,1800000,1850000,1900000,1950000,2000000};
PMU_LOCAL BSP_U32 ldo22_set[]={  900000,1000000,1050000,1100000,1150000,1175000,1187500,1200000};

PMU_LOCAL BSP_U32 invalid_set[1]={PMU_LVS_VOL_SET_INVAILD};

PMU_LOCAL COMMON_RES pmic_res[] =
{
    /*channel_id*/
    /*channel_name*/
    /*bat channel switch(on/off) register config*/
    /*voltage(current) set register config*/
    {
        BUCK1_ID,
        BUCK1_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE1_BUCK_ADDR(0),
                  SOC_SMART_ENABLE1_BUCK_en_buck1_int_START,
                  (SOC_SMART_ENABLE1_BUCK_en_buck1_int_END-SOC_SMART_ENABLE1_BUCK_en_buck1_int_START+1),
               },
               {
                  SOC_SMART_DISABLE1_BUCK_ADDR(0),
                  SOC_SMART_DISABLE1_BUCK_dis_buck1_int_START,
                  (SOC_SMART_DISABLE1_BUCK_dis_buck1_int_END-SOC_SMART_DISABLE1_BUCK_dis_buck1_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS1_BUCK_ADDR(0),
                  SOC_SMART_ONOFF_STATUS1_BUCK_st_buck1_int_START,
                  (SOC_SMART_ONOFF_STATUS1_BUCK_st_buck1_int_END-SOC_SMART_ONOFF_STATUS1_BUCK_st_buck1_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            buck1_set,
            sizeof(buck1_set)/sizeof(BSP_U32),
            {
                SOC_SMART_VSET_BUCK1_ADJ_ADDR(0),
                SOC_SMART_VSET_BUCK1_ADJ_buck1_dv_START,
                (SOC_SMART_VSET_BUCK1_ADJ_buck1_dv_END-SOC_SMART_VSET_BUCK1_ADJ_buck1_dv_START+1),
            },
        },
    },

    {
        BUCK2_ID,
        BUCK2_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE1_BUCK_ADDR(0),
                  SOC_SMART_ENABLE1_BUCK_en_buck2_int_START,
                  (SOC_SMART_ENABLE1_BUCK_en_buck2_int_END-SOC_SMART_ENABLE1_BUCK_en_buck2_int_START+1),
               },
               {
                  SOC_SMART_DISABLE1_BUCK_ADDR(0),
                  SOC_SMART_DISABLE1_BUCK_dis_buck2_int_START,
                  (SOC_SMART_DISABLE1_BUCK_dis_buck2_int_START-SOC_SMART_DISABLE1_BUCK_dis_buck2_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS1_BUCK_ADDR(0),
                  SOC_SMART_ONOFF_STATUS1_BUCK_st_buck2_int_START,
                  (SOC_SMART_ONOFF_STATUS1_BUCK_st_buck2_int_END-SOC_SMART_ONOFF_STATUS1_BUCK_st_buck2_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            buck2_set,
            sizeof(buck2_set)/sizeof(BSP_U32),
            {
                SOC_SMART_VSET_BUCK2_ADJ_ADDR(0),
                SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_START,
                (SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_END-SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_START+1),
            },
        },
    },

    {
        BUCK3_ID,
        BUCK3_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE1_BUCK_ADDR(0),
                  SOC_SMART_ENABLE1_BUCK_en_buck3_int_START,
                  (SOC_SMART_ENABLE1_BUCK_en_buck3_int_END-SOC_SMART_ENABLE1_BUCK_en_buck3_int_START+1),
               },
               {
                  SOC_SMART_DISABLE1_BUCK_ADDR(0),
                  SOC_SMART_DISABLE1_BUCK_dis_buck3_int_START,
                  (SOC_SMART_DISABLE1_BUCK_dis_buck3_int_END-SOC_SMART_DISABLE1_BUCK_dis_buck3_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS1_BUCK_ADDR(0),
                  SOC_SMART_ONOFF_STATUS1_BUCK_st_buck3_int_START,
                  (SOC_SMART_ONOFF_STATUS1_BUCK_st_buck3_int_START-SOC_SMART_ONOFF_STATUS1_BUCK_st_buck3_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },

        {
            buck3_set,
            sizeof(buck3_set)/sizeof(BSP_U32),
            {
                SOC_SMART_VSET_BUCK3_ADJ_ADDR(0),
                SOC_SMART_VSET_BUCK3_ADJ_buck3_dv_START,
                (SOC_SMART_VSET_BUCK3_ADJ_buck3_dv_END-SOC_SMART_VSET_BUCK3_ADJ_buck3_dv_START+1),
            },
        },
    },

    {
        BUCK4_ID,
        BUCK4_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE1_BUCK_ADDR(0),
                  SOC_SMART_ENABLE1_BUCK_en_buck4_int_START,
                  (SOC_SMART_ENABLE1_BUCK_en_buck4_int_END-SOC_SMART_ENABLE1_BUCK_en_buck4_int_START+1),
               },
               {
                  SOC_SMART_DISABLE1_BUCK_ADDR(0),
                  SOC_SMART_DISABLE1_BUCK_dis_buck4_int_START,
                  (SOC_SMART_DISABLE1_BUCK_dis_buck4_int_END-SOC_SMART_DISABLE1_BUCK_dis_buck4_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS1_BUCK_ADDR(0),
                  SOC_SMART_ONOFF_STATUS1_BUCK_st_buck4_int_START,
                  (SOC_SMART_ONOFF_STATUS1_BUCK_st_buck4_int_END-SOC_SMART_ONOFF_STATUS1_BUCK_st_buck4_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },

        {
            buck4_set,
            sizeof(buck4_set)/sizeof(BSP_U32),
            {
                SOC_SMART_VSET_BUCK4_ADJ0_ADDR(0),
                SOC_SMART_VSET_BUCK4_ADJ0_buck4_dv_START,
                (SOC_SMART_VSET_BUCK4_ADJ0_buck4_dv_END-SOC_SMART_VSET_BUCK4_ADJ0_buck4_dv_START+1),
            },
        },
    },

    {
        LDO1_ID,
        LDO1_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo1_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo1_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo1_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo1_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo1_int_START-SOC_SMART_DISABLE2_LDO1_8_dis_ldo1_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo1_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo1_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo1_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo1_set,
            sizeof(ldo1_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO1_REG_ADJ_ADDR(0),
                SOC_SMART_LDO1_REG_ADJ_vset_ldo1_START,
                (SOC_SMART_LDO1_REG_ADJ_vset_ldo1_END-SOC_SMART_LDO1_REG_ADJ_vset_ldo1_START+1),
            },
        },
    },

    {
        LDO2_ID,
        LDO2_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo2_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo2_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo2_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo2_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo2_int_END-SOC_SMART_DISABLE2_LDO1_8_dis_ldo2_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo2_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo2_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo2_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo2_set,
            sizeof(ldo2_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO2_REG_ADJ_ADDR(0),
                SOC_SMART_LDO2_REG_ADJ_vset_ldo2_START,
                (SOC_SMART_LDO2_REG_ADJ_vset_ldo2_END-SOC_SMART_LDO2_REG_ADJ_vset_ldo2_START+1),
            },
        },
    },

    {
        LDO3_ID,
        LDO3_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo3_buck_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo3_buck_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo3_buck_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo3_buck_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo3_buck_int_END-SOC_SMART_DISABLE2_LDO1_8_dis_ldo3_buck_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo3_buck_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo3_buck_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo3_buck_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo3_set,
            sizeof(ldo3_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO3_REG_ADJ0_ADDR(0),
                SOC_SMART_LDO3_REG_ADJ0_vset_ldo3_START,
                (SOC_SMART_LDO3_REG_ADJ0_vset_ldo3_END-SOC_SMART_LDO3_REG_ADJ0_vset_ldo3_START+1),
            },
        },
    },

    {
        LDO4_ID,
        LDO4_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo4_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo4_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo4_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo4_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo4_int_END-SOC_SMART_DISABLE2_LDO1_8_dis_ldo4_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo4_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo4_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo4_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo4_set,
            sizeof(ldo4_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        LDO5_ID,
        LDO5_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo5_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo5_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo5_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo5_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo5_int_START-SOC_SMART_DISABLE2_LDO1_8_dis_ldo5_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo5_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo5_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo5_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo5_set,
            sizeof(ldo5_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO5_REG_ADJ_ADDR(0),
                SOC_SMART_LDO5_REG_ADJ_vset_ldo5_START,
                (SOC_SMART_LDO5_REG_ADJ_vset_ldo5_END-SOC_SMART_LDO5_REG_ADJ_vset_ldo5_START+1),
            },
        },
    },

    {
        LDO6_ID,
        LDO6_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo6_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo6_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo6_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo6_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo6_int_END-SOC_SMART_DISABLE2_LDO1_8_dis_ldo6_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo6_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo6_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo6_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo6_set,
            sizeof(ldo6_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO6_REG_ADJ_ADDR(0),
                SOC_SMART_LDO6_REG_ADJ_vset_ldo6_START,
                (SOC_SMART_LDO6_REG_ADJ_vset_ldo6_END-SOC_SMART_LDO6_REG_ADJ_vset_ldo6_START+1),
            },
        },
    },

    {
        LDO7_ID,
        LDO7_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo7_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo7_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo7_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo7_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo7_int_END-SOC_SMART_DISABLE2_LDO1_8_dis_ldo7_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo7_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo7_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo7_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo7_set,
            sizeof(ldo7_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO7_REG_ADJ_ADDR(0),
                SOC_SMART_LDO7_REG_ADJ_vset_ldo7_START,
                (SOC_SMART_LDO7_REG_ADJ_vset_ldo7_END-SOC_SMART_LDO7_REG_ADJ_vset_ldo7_START+1),
            },
        },
    },

    {
        LDO8_ID,
        LDO8_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_ENABLE2_LDO1_8_en_ldo8_int_START,
                  (SOC_SMART_ENABLE2_LDO1_8_en_ldo8_int_END-SOC_SMART_ENABLE2_LDO1_8_en_ldo8_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_LDO1_8_ADDR(0),
                  SOC_SMART_DISABLE2_LDO1_8_dis_ldo8_int_START,
                  (SOC_SMART_DISABLE2_LDO1_8_dis_ldo8_int_END-SOC_SMART_DISABLE2_LDO1_8_dis_ldo8_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo8_int_START,
                  (SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo8_int_END-SOC_SMART_ONOFF_STATUS2_LDO1_8_st_ldo8_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo8_set,
            sizeof(ldo8_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO8_REG_ADJ_ADDR(0),
                SOC_SMART_LDO8_REG_ADJ_vset_ldo8_START,
                (SOC_SMART_LDO8_REG_ADJ_vset_ldo8_END-SOC_SMART_LDO8_REG_ADJ_vset_ldo8_START+1),
            },
        },
    },

    {
        LDO9_ID,
        LDO9_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo9_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo9_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo9_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo9_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo9_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo9_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo9_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo9_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo9_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo9_set,
            sizeof(ldo9_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO9_REG_ADJ_ADDR(0),
                SOC_SMART_LDO9_REG_ADJ_vset_ldo9_START,
                (SOC_SMART_LDO9_REG_ADJ_vset_ldo9_END-SOC_SMART_LDO9_REG_ADJ_vset_ldo9_START+1),
            },
        },
    },

    {
        LDO10_ID,
        LDO10_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo10_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo10_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo10_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo10_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo10_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo10_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo10_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo10_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo10_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo10_set,
            sizeof(ldo10_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO10_REG_ADJ_ADDR(0),
                SOC_SMART_LDO10_REG_ADJ_vset_ldo10_START,
                (SOC_SMART_LDO10_REG_ADJ_vset_ldo10_END-SOC_SMART_LDO10_REG_ADJ_vset_ldo10_START+1),
            },
        },
    },

    {
        LDO11_ID,
        LDO11_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo11_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo11_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo11_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo11_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo11_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo11_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo11_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo11_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo11_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo11_set,
            sizeof(ldo11_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO11_REG_ADJ_ADDR(0),
                SOC_SMART_LDO11_REG_ADJ_vset_ldo11_START,
                (SOC_SMART_LDO11_REG_ADJ_vset_ldo11_END-SOC_SMART_LDO11_REG_ADJ_vset_ldo11_START+1),
            },
        },
    },

    {
        LDO12_ID,
        LDO12_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo12_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo12_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo12_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo12_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo12_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo12_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo12_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo12_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo12_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo12_set,
            sizeof(ldo12_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO12_REG_ADJ_ADDR(0),
                SOC_SMART_LDO12_REG_ADJ_vset_ldo12_START,
                (SOC_SMART_LDO12_REG_ADJ_vset_ldo12_END-SOC_SMART_LDO12_REG_ADJ_vset_ldo12_START+1),
            },
        },
    },

    {
        LDO13_ID,
        LDO13_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo13_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo13_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo13_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo13_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo13_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo13_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo13_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo13_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo13_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo13_set,
            sizeof(ldo13_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO13_REG_ADJ_ADDR(0),
                SOC_SMART_LDO13_REG_ADJ_vset_ldo13_START,
                (SOC_SMART_LDO13_REG_ADJ_vset_ldo13_END-SOC_SMART_LDO13_REG_ADJ_vset_ldo13_START+1),
            },
        },
    },

    {
        LDO14_ID,
        LDO14_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo14_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo14_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo14_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo14_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo14_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo14_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo14_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo14_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo14_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo14_set,
            sizeof(ldo14_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO14_REG_ADJ_ADDR(0),
                SOC_SMART_LDO14_REG_ADJ_vset_ldo14_START,
                (SOC_SMART_LDO14_REG_ADJ_vset_ldo14_END-SOC_SMART_LDO14_REG_ADJ_vset_ldo14_START+1),
            },
        },
    },

    {
        LDO15_ID,
        LDO15_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo15_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo15_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo15_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo15_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo15_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo15_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo15_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo15_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo15_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo15_set,
            sizeof(ldo15_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO15_REG_ADJ_ADDR(0),
                SOC_SMART_LDO15_REG_ADJ_vset_ldo15_START,
               (SOC_SMART_LDO15_REG_ADJ_vset_ldo15_END-SOC_SMART_LDO15_REG_ADJ_vset_ldo15_START+1),
            },
        },
    },

    {
        LDO16_ID,
        LDO16_NAME,
        {
             {
               {
                  SOC_SMART_ENABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_ENABLE3_LDO9_16_en_ldo16_int_START,
                  (SOC_SMART_ENABLE3_LDO9_16_en_ldo16_int_END-SOC_SMART_ENABLE3_LDO9_16_en_ldo16_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_LDO9_16_ADDR(0),
                  SOC_SMART_DISABLE3_LDO9_16_dis_ldo16_int_START,
                  (SOC_SMART_DISABLE3_LDO9_16_dis_ldo16_int_END-SOC_SMART_DISABLE3_LDO9_16_dis_ldo16_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo16_int_START,
                  (SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo16_int_END-SOC_SMART_ONOFF_STATUS3_LDO9_16_st_ldo16_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo16_set,
            sizeof(ldo16_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO16_REG_ADJ_ADDR(0),
                SOC_SMART_LDO16_REG_ADJ_vset_ldo16_START,
                (SOC_SMART_LDO16_REG_ADJ_vset_ldo16_END-SOC_SMART_LDO16_REG_ADJ_vset_ldo16_START+1),
            },
        },
    },

    {
        LDO17_ID,
        LDO17_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_ENABLE4_LDO17_22_en_ldo17_int_START,
                  (SOC_SMART_ENABLE4_LDO17_22_en_ldo17_int_END-SOC_SMART_ENABLE4_LDO17_22_en_ldo17_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_DISABLE4_LDO17_22_dis_ldo17_int_START,
                  (SOC_SMART_DISABLE4_LDO17_22_dis_ldo17_int_END-SOC_SMART_DISABLE4_LDO17_22_dis_ldo17_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo17_int_START,
                  (SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo17_int_END-SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo17_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo17_set,
            sizeof(ldo17_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO17_REG_ADJ_ADDR(0),
                SOC_SMART_LDO17_REG_ADJ_vset_ldo17_START,
                (SOC_SMART_LDO17_REG_ADJ_vset_ldo17_END-SOC_SMART_LDO17_REG_ADJ_vset_ldo17_START+1),
            },
        },
    },

    {
        LDO18_ID,
        LDO18_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_ENABLE4_LDO17_22_en_ldo18_int_START,
                  (SOC_SMART_ENABLE4_LDO17_22_en_ldo18_int_END-SOC_SMART_ENABLE4_LDO17_22_en_ldo18_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_DISABLE4_LDO17_22_dis_ldo18_int_START,
                  (SOC_SMART_DISABLE4_LDO17_22_dis_ldo18_int_END-SOC_SMART_DISABLE4_LDO17_22_dis_ldo18_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo18_int_START,
                  (SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo18_int_END-SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo18_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo18_set,
            sizeof(ldo18_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO18_REG_ADJ_ADDR(0),
                SOC_SMART_LDO18_REG_ADJ_vset_ldo18_START,
                (SOC_SMART_LDO18_REG_ADJ_vset_ldo18_END-SOC_SMART_LDO18_REG_ADJ_vset_ldo18_START+1),
            },
        },
    },

    {
        LDO19_ID,
        LDO19_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_ENABLE4_LDO17_22_en_ldo19_int_START,
                  (SOC_SMART_ENABLE4_LDO17_22_en_ldo19_int_END-SOC_SMART_ENABLE4_LDO17_22_en_ldo19_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_DISABLE4_LDO17_22_dis_ldo19_int_START,
                  (SOC_SMART_DISABLE4_LDO17_22_dis_ldo19_int_END-SOC_SMART_DISABLE4_LDO17_22_dis_ldo19_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo19_int_START,
                  (SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo19_int_END-SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo19_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo19_set,
            sizeof(ldo19_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO19_REG_ADJ_ADDR(0),
                SOC_SMART_LDO19_REG_ADJ_vset_ldo19_START,
                (SOC_SMART_LDO19_REG_ADJ_vset_ldo19_END-SOC_SMART_LDO19_REG_ADJ_vset_ldo19_START+1),
            },
        },
    },

    {
        LDO20_ID,
        LDO20_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_ENABLE4_LDO17_22_en_ldo20_int_START,
                  (SOC_SMART_ENABLE4_LDO17_22_en_ldo20_int_END-SOC_SMART_ENABLE4_LDO17_22_en_ldo20_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_DISABLE4_LDO17_22_dis_ldo20_int_START,
                  (SOC_SMART_DISABLE4_LDO17_22_dis_ldo20_int_END-SOC_SMART_DISABLE4_LDO17_22_dis_ldo20_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo20_int_START,
                  (SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo20_int_END-SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo20_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo20_set,
            sizeof(ldo20_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO20_REG_ADJ_ADDR(0),
                SOC_SMART_LDO20_REG_ADJ_vset_ldo20_START,
                (SOC_SMART_LDO20_REG_ADJ_vset_ldo20_END-SOC_SMART_LDO20_REG_ADJ_vset_ldo20_START+1),
            },
        },
    },

    {
        LDO21_ID,
        LDO21_NAME,
       {
            {
                {
                  SOC_SMART_ENABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_ENABLE4_LDO17_22_en_ldo21_int_START,
                  (SOC_SMART_ENABLE4_LDO17_22_en_ldo21_int_END-SOC_SMART_ENABLE4_LDO17_22_en_ldo21_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_DISABLE4_LDO17_22_dis_ldo21_int_START,
                  (SOC_SMART_DISABLE4_LDO17_22_dis_ldo21_int_END-SOC_SMART_DISABLE4_LDO17_22_dis_ldo21_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo21_int_START,
                  (SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo21_int_END-SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo21_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo21_set,
            sizeof(ldo21_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO21_REG_ADJ_ADDR(0),
                SOC_SMART_LDO21_REG_ADJ_vset_ldo21_START,
                (SOC_SMART_LDO21_REG_ADJ_vset_ldo21_END-SOC_SMART_LDO21_REG_ADJ_vset_ldo21_START+1),
            },
        },
    },

    {
        LDO22_ID,
        LDO22_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_ENABLE4_LDO17_22_en_ldo22_int_START,
                  (SOC_SMART_ENABLE4_LDO17_22_en_ldo22_int_END-SOC_SMART_ENABLE4_LDO17_22_en_ldo22_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_LDO17_22_ADDR(0),
                  SOC_SMART_DISABLE4_LDO17_22_dis_ldo22_int_START,
                  (SOC_SMART_DISABLE4_LDO17_22_dis_ldo22_int_END-SOC_SMART_DISABLE4_LDO17_22_dis_ldo22_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo22_int_START,
                  (SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo22_int_END-SOC_SMART_ONOFF_STATUS4_LDO17_22_st_ldo22_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo22_set,
            sizeof(ldo22_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO22_REG_ADJ_ADDR(0),
                SOC_SMART_LDO22_REG_ADJ_vset_ldo22_START,
                (SOC_SMART_LDO22_REG_ADJ_vset_ldo22_END-SOC_SMART_LDO22_REG_ADJ_vset_ldo22_START+1),
            },
        },
    },

    {
        LVS2_ID,
        LVS2_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_LVS2_ADDR(0),
                      SOC_SMART_ENABLE5_LVS2_en_lvs2_int_START,
                      (SOC_SMART_ENABLE5_LVS2_en_lvs2_int_END-SOC_SMART_ENABLE5_LVS2_en_lvs2_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_LVS2_ADDR(0),
                      SOC_SMART_DISABLE5_LVS2_dis_lvs2_int_START,
                      (SOC_SMART_DISABLE5_LVS2_dis_lvs2_int_END-SOC_SMART_DISABLE5_LVS2_dis_lvs2_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_LVS2_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_LVS2_st_lvs2_int_START,
                      (SOC_SMART_ONOFF_STATUS5_LVS2_st_lvs2_int_END-SOC_SMART_ONOFF_STATUS5_LVS2_st_lvs2_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            invalid_set,
            sizeof(invalid_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        PMU_CHANNEL_ID_BUTT,
        "PMU_CHANNEL_BUTT",
        {
            {
                {
                      0,
                      0,
                      0,
                },
                {
                      0,
                      0,
                      0,
                },
                {
                      0,
                      0,
                      0,
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            invalid_set,
            sizeof(invalid_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    }
};

PMU_LOCAL PMU_RES_CTRL  smart_res_ctrl =
{
    pmic_res,
    PMU_CHANNEL_ID_BUTT,
    PMU_REGISTER_DATA_BIT,
    {SOC_SMART_VERSION_ADDR(0),0,0}
};



static struct platform_device smart_device = {
    .name       = "smartStar",
    .id         = 0,
    .dev.platform_data  = &smart_res_ctrl,
};

/* devices we initialise */
static struct platform_device __initdata *smart_devs[] = {
    &smart_device,
};

/*****************************************************************************
 函 数 名  : pmic_device_init
 功能描述  : device init
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : fansaihua f00204170
    修改内容   : 新生成函数

*****************************************************************************/
static int __init pmic_device_init(void)
{
    int i = 0;
    PMU_RES_CTRL*  res_ctrl = &smart_res_ctrl;
    res_ctrl->res_num = sizeof(pmic_res)/sizeof(COMMON_RES);

    platform_add_devices(smart_devs, ARRAY_SIZE(smart_devs));
    printk("pmic_device_init\n");
    return 0;
}

/*must after pmussi gpio*/
core_initcall(pmic_device_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon Tech.Co.,Ltd.<fansaihua@huawei.com>");
MODULE_DESCRIPTION(" Hisilicon PMIC driver");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

