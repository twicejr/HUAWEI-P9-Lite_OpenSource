/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_pmu.h */
/* Version       : 2.0 */
/* Created       : 2013-05-14*/
/* Last Modified : */
/* Description   :  The C union definition file for the module pmu*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_PMU_H__
#define __HI_PMU_H__

/*
 * Project: hi
 * Module : pmu
 */
 /* PMIC BASE ADDR */
#ifdef BSP_CONFIG_SFT
#define PMIC_BASE_ADDR 0xE1FD8000
#else
#define PMIC_BASE_ADDR 0x9001a000
#endif

#define PMIC_VERSION_REG0                        0x00
#define PMIC_VERSION_REG1                        0x01
#define PMIC_VERSION_REG2                        0x02
#define PMIC_VERSION_REG3                        0x03
#define PMIC_VERSION_REG4                        0x04
#define PMIC_VERSION_REG5                        0x05

#endif // __HI_PMU_H__

