

#ifndef __SOC_MEMMAP_APP_H__
#define __SOC_MEMMAP_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "soc_memmap_comm.h"

/**********************begin:timer********************/
/*非掉电区*/
#define HI_TIMER_00_REGBASE_ADDR          0xfff00000   //对应k3 timer00
#define HI_TIMER_01_REGBASE_ADDR          0xfff00000   //对应k3 timer01
#define HI_TIMER_02_REGBASE_ADDR          0xfff01000   //对应k3 timer10
#define HI_TIMER_03_REGBASE_ADDR          0xfff01000   //对应k3 timer11
#define HI_TIMER_04_REGBASE_ADDR          0xfff02000   //对应k3 timer20
#define HI_TIMER_05_REGBASE_ADDR          0xfff02000   //对应k3 timer21
#define HI_TIMER_06_REGBASE_ADDR          0xfff03000   //对应k3 timer30
#define HI_TIMER_07_REGBASE_ADDR          0xfff03000   //对应k3 timer31

/*掉电区*/
#define HI_TIMER_08_REGBASE_ADDR          0xe8a00000   //对应k3 timer40
#define HI_TIMER_09_REGBASE_ADDR          0xe8a00000   //对应k3 timer41
#define HI_TIMER_10_REGBASE_ADDR          0xe8a01000   //对应k3 timer50
#define HI_TIMER_11_REGBASE_ADDR          0xe8a01000   //对应k3 timer51
#define HI_TIMER_12_REGBASE_ADDR          0xe8a02000   //对应k3 timer60
#define HI_TIMER_13_REGBASE_ADDR          0xe8a02000   //对应k3 timer61
#define HI_TIMER_14_REGBASE_ADDR          0xe8a03000   //对应k3 timer70
#define HI_TIMER_15_REGBASE_ADDR          0xe8a03000   //对应k3 timer71
#define TIMER_ADDR_SIZE                   0X1000        //单个timer地址大小
/*K3形态以下timer打桩*/
#define HI_TIMER_16_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_17_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_18_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_19_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_20_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_21_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_22_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_23_REGBASE_ADDR          0xFFFFFFFF

/**********************end:timer********************/

#ifdef __cplusplus
}
#endif

#endif    /* __SOC_MEMMAP_APP_H__ */

