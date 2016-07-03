/*
This file contains I/O address and related constants for the balongv7r2 clk .
*/

#ifndef __SOC_CLK_H
#define __SOC_CLK_H
#include <product_config.h>
#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
                  * soc clk *
***************************************************************************/

#define HI_TCXO_CLK                 (32*1024)
#define HI_TIMER_CLK                (19200000)
#define HI_TIMER_STAMP_CLK          (32*1024)
#define HI_SCI0_CLK                 (20000000)
#define HI_SCI1_CLK                 (20000000)


#ifdef __cplusplus
}
#endif

#endif    /* __SOC_CLK_H */
