/******************************************************************************
 * @file lookup.h
 *
 * lookup.h
 *
 * @version 0.0.1
 * @authors btok
 *
 *****************************************************************************//*
 * Copyright (2014), Cypress Semiconductor Corporation. All rights reserved.
 *
 * This software, associated documentation and materials ("Software") is owned
 * by Cypress Semiconductor Corporation ("Cypress") and is protected by and
 * subject to worldwide patent protection (United States and foreign), United
 * States copyright laws and international treaty provisions. Therefore, unless
 * otherwise specified in a separate license agreement between you and Cypress,
 * this Software must be treated like any other copyrighted material.
 * Reproduction, modification, translation, compilation, or representation of
 * this Software in any other form (e.g., paper, magnetic, optical, silicon) is
 * prohibited without Cypress's express written permission.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * Cypress reserves the right to make changes to the Software without notice.
 * Cypress does not assume any liability arising out of the application or use
 * of Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use as critical components in any products
 * where a malfunction or failure may reasonably be expected to result in
 * significant injury or death ("High Risk Product"). By including Cypress's
 * product in a High Risk Product, the manufacturer of such system or
 * application assumes all risk of such use and in doing so indemnifies Cypress
 * against all liability.
 *
 * Use of this Software may be limited by and subject to the applicable Cypress
 * software license agreement.
 *****************************************************************************/

#ifndef _LOOKUP_H_
#define _LOOKUP_H_

/* RX Attenuator Lookup Table */
struct rx_attenuator_lookup {
    int index;
    int value;
};

#define RX_ATTENUATOR_LOOKUP_TABLE    \
    {1, 240},             \
    {2, 120},             \
    {3, 80},             \
    {4, 60},             \
    {5, 48},             \
    {6, 40},             \
    {8, 30},             \
    {11, 20},             \
    {12, 10}

/* MTX Sum Lookup Table */
#define MTX_ORDER_MIN    1
#define MTX_ORDER_MAX    24

#define IS_MTX_ORDER_VALID(mtx_order)    \
    ((mtx_order) >= MTX_ORDER_MIN && (mtx_order) <= MTX_ORDER_MAX)

#define GET_MTX_SUM_OFFSET(mtx_order)    \
    ((mtx_order) - MTX_ORDER_MIN)

#define MTX_SUM_LOOKUP_TABLE            \
    1, 2, 2, 2, 3, 2, 1, 2, 3, 2, 3, 2,    \
    3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4

/* SelfCap Signal Swing Lookup Table */
#define REF_SCALE_MIN    0
#define REF_SCALE_MAX    7
#define RXDAC_MIN    0
#define RXDAC_MAX    15

#define VREF_LOW_INDEX    0
#define VREF_MID_INDEX    1
#define VREF_HIGH_INDEX    2

#define IS_REF_SCALE_VALID(ref_scale)    \
    ((ref_scale) >= REF_SCALE_MIN && (ref_scale) <= REF_SCALE_MAX)
#define IS_RXDAC_VALID(rxdac)    \
    ((rxdac) >= RXDAC_MIN && (rxdac) <= RXDAC_MAX)

#define GET_SELFCAP_SIGNAL_SWING_OFFSET(ref_scale, rxdac)    \
    (((ref_scale) * (RXDAC_MAX - RXDAC_MIN + 1) + (rxdac)) * 3)

#define GET_VREF_LOW_OFFSET(ref_scale, rxdac)    \
    (GET_SELFCAP_SIGNAL_SWING_OFFSET(ref_scale, rxdac) + VREF_LOW_INDEX)
#define GET_VREF_MID_OFFSET(ref_scale, rxdac)    \
    (GET_SELFCAP_SIGNAL_SWING_OFFSET(ref_scale, rxdac) + VREF_MID_INDEX)
#define GET_VREF_HIGH_OFFSET(ref_scale, rxdac)    \
    (GET_SELFCAP_SIGNAL_SWING_OFFSET(ref_scale, rxdac) + VREF_HIGH_INDEX)

#define SELFCAP_SIGNAL_SWING_LOOKUP_TABLE    \
	1050, 1300, 1550, /* REF_SCALE = 0, RXDAC = 0 */	\
	1000, 1300, 1600, /* REF_SCALE = 0, RXDAC = 1 */	\
	950, 1300, 1650, /* REF_SCALE = 0, RXDAC = 2 */	\
	900, 1300, 1700, /* REF_SCALE = 0, RXDAC = 3 */	\
	850, 1300, 1750, /* REF_SCALE = 0, RXDAC = 4 */	\
	800, 1300, 1800, /* REF_SCALE = 0, RXDAC = 5 */	\
	750, 1300, 1850, /* REF_SCALE = 0, RXDAC = 6 */	\
	700, 1300, 1900, /* REF_SCALE = 0, RXDAC = 7 */	\
	650, 1300, 1950, /* REF_SCALE = 0, RXDAC = 8 */	\
	600, 1300, 2000, /* REF_SCALE = 0, RXDAC = 9 */	\
	550, 1300, 2050, /* REF_SCALE = 0, RXDAC = 10 */	\
	500, 1300, 2100, /* REF_SCALE = 0, RXDAC = 11 */	\
	450, 1300, 2150, /* REF_SCALE = 0, RXDAC = 12 */	\
	400, 1300, 2200, /* REF_SCALE = 0, RXDAC = 13 */	\
	350, 1300, 2250, /* REF_SCALE = 0, RXDAC = 14 */	\
	300, 1300, 2300, /* REF_SCALE = 0, RXDAC = 15 */	\
	1170, 1450, 1730, /* REF_SCALE = 1, RXDAC = 0 */	\
	1120, 1450, 1790, /* REF_SCALE = 1, RXDAC = 1 */	\
	1060, 1450, 1840, /* REF_SCALE = 1, RXDAC = 2 */	\
	1010, 1450, 1900, /* REF_SCALE = 1, RXDAC = 3 */	\
	950, 1450, 1950, /* REF_SCALE = 1, RXDAC = 4 */	\
	890, 1450, 2010, /* REF_SCALE = 1, RXDAC = 5 */	\
	840, 1450, 2070, /* REF_SCALE = 1, RXDAC = 6 */	\
	780, 1450, 2120, /* REF_SCALE = 1, RXDAC = 7 */	\
	730, 1450, 2180, /* REF_SCALE = 1, RXDAC = 8 */	\
	670, 1450, 2230, /* REF_SCALE = 1, RXDAC = 9 */	\
	610, 1450, 2290, /* REF_SCALE = 1, RXDAC = 10 */	\
	560, 1450, 2350, /* REF_SCALE = 1, RXDAC = 11 */	\
	500, 1450, 2400, /* REF_SCALE = 1, RXDAC = 12 */	\
	450, 1450, 2460, /* REF_SCALE = 1, RXDAC = 13 */	\
	390, 1450, 2510, /* REF_SCALE = 1, RXDAC = 14 */	\
	340, 1450, 2570, /* REF_SCALE = 1, RXDAC = 15 */	\
	1290, 1600, 1910, /* REF_SCALE = 2, RXDAC = 0 */	\
	1230, 1600, 1970, /* REF_SCALE = 2, RXDAC = 1 */	\
	1170, 1600, 2030, /* REF_SCALE = 2, RXDAC = 2 */	\
	1110, 1600, 2090, /* REF_SCALE = 2, RXDAC = 3 */	\
	1050, 1600, 2150, /* REF_SCALE = 2, RXDAC = 4 */	\
	990, 1600, 2220, /* REF_SCALE = 2, RXDAC = 5 */	\
	920, 1600, 2280, /* REF_SCALE = 2, RXDAC = 6 */	\
	860, 1600, 2340, /* REF_SCALE = 2, RXDAC = 7 */	\
	800, 1600, 2400, /* REF_SCALE = 2, RXDAC = 8 */	\
	740, 1600, 2460, /* REF_SCALE = 2, RXDAC = 9 */	\
	680, 1600, 2520, /* REF_SCALE = 2, RXDAC = 10 */	\
	620, 1600, 2590, /* REF_SCALE = 2, RXDAC = 11 */	\
	550, 1600, 2650, /* REF_SCALE = 2, RXDAC = 12 */	\
	490, 1600, 2710, /* REF_SCALE = 2, RXDAC = 13 */	\
	430, 1600, 2770, /* REF_SCALE = 2, RXDAC = 14 */	\
	370, 1600, 2830, /* REF_SCALE = 2, RXDAC = 15 */	\
	1440, 1790, 2130, /* REF_SCALE = 3, RXDAC = 0 */	\
	1370, 1790, 2200, /* REF_SCALE = 3, RXDAC = 1 */	\
	1300, 1790, 2260, /* REF_SCALE = 3, RXDAC = 2 */	\
	1240, 1790, 2330, /* REF_SCALE = 3, RXDAC = 3 */	\
	1170, 1790, 2400, /* REF_SCALE = 3, RXDAC = 4 */	\
	1100, 1790, 2470, /* REF_SCALE = 3, RXDAC = 5 */	\
	1030, 1790, 2540, /* REF_SCALE = 3, RXDAC = 6 */	\
	960, 1790, 2610, /* REF_SCALE = 3, RXDAC = 7 */	\
	890, 1790, 2680, /* REF_SCALE = 3, RXDAC = 8 */	\
	820, 1790, 2740, /* REF_SCALE = 3, RXDAC = 9 */	\
	750, 1790, 2810, /* REF_SCALE = 3, RXDAC = 10 */	\
	690, 1790, 2880, /* REF_SCALE = 3, RXDAC = 11 */	\
	620, 1790, 2950, /* REF_SCALE = 3, RXDAC = 12 */	\
	550, 1790, 3020, /* REF_SCALE = 3, RXDAC = 13 */	\
	480, 1790, 3080, /* REF_SCALE = 3, RXDAC = 14 */	\
	410, 1790, 3160, /* REF_SCALE = 3, RXDAC = 15 */	\
	1630, 2020, 2400, /* REF_SCALE = 4, RXDAC = 0 */	\
	1550, 2020, 2480, /* REF_SCALE = 4, RXDAC = 1 */	\
	1470, 2020, 2560, /* REF_SCALE = 4, RXDAC = 2 */	\
	1390, 2020, 2630, /* REF_SCALE = 4, RXDAC = 3 */	\
	1320, 2020, 2710, /* REF_SCALE = 4, RXDAC = 4 */	\
	1240, 2020, 2790, /* REF_SCALE = 4, RXDAC = 5 */	\
	1160, 2020, 2870, /* REF_SCALE = 4, RXDAC = 6 */	\
	1080, 2020, 2940, /* REF_SCALE = 4, RXDAC = 7 */	\
	1010, 2020, 3020, /* REF_SCALE = 4, RXDAC = 8 */	\
	930, 2020, 3100, /* REF_SCALE = 4, RXDAC = 9 */	\
	850, 2020, 3180, /* REF_SCALE = 4, RXDAC = 10 */	\
	770, 2020, 3250, /* REF_SCALE = 4, RXDAC = 11 */	\
	700, 2020, 3330, /* REF_SCALE = 4, RXDAC = 12 */	\
	620, 2020, 3410, /* REF_SCALE = 4, RXDAC = 13 */	\
	540, 2020, 3490, /* REF_SCALE = 4, RXDAC = 14 */	\
	470, 2020, 3560, /* REF_SCALE = 4, RXDAC = 15 */	\
	1800, 2230, 2660, /* REF_SCALE = 5, RXDAC = 0 */	\
	1720, 2230, 2750, /* REF_SCALE = 5, RXDAC = 1 */	\
	1630, 2230, 2830, /* REF_SCALE = 5, RXDAC = 2 */	\
	1540, 2230, 2920, /* REF_SCALE = 5, RXDAC = 3 */	\
	1460, 2230, 3000, /* REF_SCALE = 5, RXDAC = 4 */	\
	1370, 2230, 3090, /* REF_SCALE = 5, RXDAC = 5 */	\
	1290, 2230, 3180, /* REF_SCALE = 5, RXDAC = 6 */	\
	1200, 2230, 3260, /* REF_SCALE = 5, RXDAC = 7 */	\
	1120, 2230, 3350, /* REF_SCALE = 5, RXDAC = 8 */	\
	1030, 2230, 3430, /* REF_SCALE = 5, RXDAC = 9 */	\
	940, 2230, 3520, /* REF_SCALE = 5, RXDAC = 10 */	\
	860, 2230, 3600, /* REF_SCALE = 5, RXDAC = 11 */	\
	770, 2230, 3690, /* REF_SCALE = 5, RXDAC = 12 */	\
	690, 2230, 3780, /* REF_SCALE = 5, RXDAC = 13 */	\
	600, 2230, 3860, /* REF_SCALE = 5, RXDAC = 14 */	\
	520, 2230, 3950, /* REF_SCALE = 5, RXDAC = 15 */	\
	1940, 2400, 2870, /* REF_SCALE = 6, RXDAC = 0 */	\
	1850, 2400, 2960, /* REF_SCALE = 6, RXDAC = 1 */	\
	1760, 2400, 3050, /* REF_SCALE = 6, RXDAC = 2 */	\
	1660, 2400, 3140, /* REF_SCALE = 6, RXDAC = 3 */	\
	1570, 2400, 3240, /* REF_SCALE = 6, RXDAC = 4 */	\
	1480, 2400, 3330, /* REF_SCALE = 6, RXDAC = 5 */	\
	1390, 2400, 3420, /* REF_SCALE = 6, RXDAC = 6 */	\
	1290, 2400, 3510, /* REF_SCALE = 6, RXDAC = 7 */	\
	1200, 2400, 3600, /* REF_SCALE = 6, RXDAC = 8 */	\
	1110, 2400, 3700, /* REF_SCALE = 6, RXDAC = 9 */	\
	1020, 2400, 3790, /* REF_SCALE = 6, RXDAC = 10 */	\
	920, 2400, 3880, /* REF_SCALE = 6, RXDAC = 11 */	\
	830, 2400, 3970, /* REF_SCALE = 6, RXDAC = 12 */	\
	740, 2400, 4070, /* REF_SCALE = 6, RXDAC = 13 */	\
	650, 2400, 4150, /* REF_SCALE = 6, RXDAC = 14 */	\
	560, 2400, 4250, /* REF_SCALE = 6, RXDAC = 15 */	\
	2100, 2600, 3100, /* REF_SCALE = 7, RXDAC = 0 */	\
	2000, 2600, 3200, /* REF_SCALE = 7, RXDAC = 1 */	\
	1900, 2600, 3300, /* REF_SCALE = 7, RXDAC = 2 */	\
	1800, 2600, 3400, /* REF_SCALE = 7, RXDAC = 3 */	\
	1700, 2600, 3500, /* REF_SCALE = 7, RXDAC = 4 */	\
	1600, 2600, 3600, /* REF_SCALE = 7, RXDAC = 5 */	\
	1500, 2600, 3700, /* REF_SCALE = 7, RXDAC = 6 */	\
	1400, 2600, 3800, /* REF_SCALE = 7, RXDAC = 7 */	\
	1300, 2600, 3900, /* REF_SCALE = 7, RXDAC = 8 */	\
	1200, 2600, 4000, /* REF_SCALE = 7, RXDAC = 9 */	\
	1100, 2600, 4100, /* REF_SCALE = 7, RXDAC = 10 */	\
	1000, 2600, 4200, /* REF_SCALE = 7, RXDAC = 11 */	\
	900, 2600, 4300, /* REF_SCALE = 7, RXDAC = 12 */	\
	800, 2600, 4400, /* REF_SCALE = 7, RXDAC = 13 */	\
	700, 2600, 4500, /* REF_SCALE = 7, RXDAC = 14 */	\
	600, 2600, 4600, /* REF_SCALE = 7, RXDAC = 15 */
#endif /* _LOOKUP_H_ */
