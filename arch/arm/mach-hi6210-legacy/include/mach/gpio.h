/*
 *
 * arch/arm/mach-k3v2/include/mach/gpio.h
 *
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 * GPIO definitions and inline macros
 *
 */
#ifndef __MACH_GPIO_H
#define __MACH_GPIO_H

#include <mach/irqs.h>

#define ARCH_NR_GPIOS	(20*8) 	/*we have gpio0 to gpio19, totally 20 chips, 8 ports per chip*/

#include <asm-generic/gpio.h>

#define gpio_get_value	__gpio_get_value
#define gpio_set_value	__gpio_set_value
#define gpio_cansleep	__gpio_cansleep
#define gpio_to_irq	__gpio_to_irq
#define irq_to_gpio(n)	(n - IRQ_GPIO_BASE)

#define GPIO_0_0	0
#define GPIO_0_1	1
#define GPIO_0_2	2
#define GPIO_0_3	3
#define GPIO_0_4	4
#define GPIO_0_5	5
#define GPIO_0_6	6
#define GPIO_0_7	7

#define GPIO_1_0	8
#define GPIO_1_1	9
#define GPIO_1_2	10
#define GPIO_1_3	11
#define GPIO_1_4	12
#define GPIO_1_5	13
#define GPIO_1_6	14
#define GPIO_1_7	15

#define GPIO_2_0	16
#define GPIO_2_1	17
#define GPIO_2_2	18
#define GPIO_2_3	19
#define GPIO_2_4	20
#define GPIO_2_5	21
#define GPIO_2_6	22
#define GPIO_2_7	23

#define GPIO_3_0	24
#define GPIO_3_1	25
#define GPIO_3_2	26
#define GPIO_3_3	27
#define GPIO_3_4	28
#define GPIO_3_5	29
#define GPIO_3_6	30
#define GPIO_3_7	31

#define GPIO_4_0	32
#define GPIO_4_1	33
#define GPIO_4_2	34
#define GPIO_4_3	35
#define GPIO_4_4	36
#define GPIO_4_5	37
#define GPIO_4_6	38
#define GPIO_4_7	39

#define GPIO_5_0	40
#define GPIO_5_1	41
#define GPIO_5_2	42
#define GPIO_5_3	43
#define GPIO_5_4	44
#define GPIO_5_5	45
#define GPIO_5_6	46
#define GPIO_5_7	47

#define GPIO_6_0	48
#define GPIO_6_1	49
#define GPIO_6_2	50
#define GPIO_6_3	51
#define GPIO_6_4	52
#define GPIO_6_5	53
#define GPIO_6_6	54
#define GPIO_6_7	55

#define GPIO_7_0	56
#define GPIO_7_1	57
#define GPIO_7_2	58
#define GPIO_7_3	59
#define GPIO_7_4	60
#define GPIO_7_5	61
#define GPIO_7_6	62
#define GPIO_7_7	63

#define GPIO_8_0	64
#define GPIO_8_1	65
#define GPIO_8_2	66
#define GPIO_8_3	67
#define GPIO_8_4	68
#define GPIO_8_5	69
#define GPIO_8_6	70
#define GPIO_8_7	71

#define GPIO_9_0	72
#define GPIO_9_1	73
#define GPIO_9_2	74
#define GPIO_9_3	75
#define GPIO_9_4	76
#define GPIO_9_5	77
#define GPIO_9_6	78
#define GPIO_9_7	79

#define GPIO_10_0 	80
#define GPIO_10_1 	81
#define GPIO_10_2 	82
#define GPIO_10_3 	83
#define GPIO_10_4 	84
#define GPIO_10_5 	85
#define GPIO_10_6 	86
#define GPIO_10_7 	87

#define GPIO_11_0 	88
#define GPIO_11_1 	89
#define GPIO_11_2 	90
#define GPIO_11_3 	91
#define GPIO_11_4 	92
#define GPIO_11_5 	93
#define GPIO_11_6 	94
#define GPIO_11_7 	95

#define GPIO_12_0 	96
#define GPIO_12_1 	97
#define GPIO_12_2 	98
#define GPIO_12_3 	99
#define GPIO_12_4 	100
#define GPIO_12_5 	101
#define GPIO_12_6 	102
#define GPIO_12_7 	103

#define GPIO_13_0 	104
#define GPIO_13_1 	105
#define GPIO_13_2 	106
#define GPIO_13_3 	107
#define GPIO_13_4 	108
#define GPIO_13_5 	109
#define GPIO_13_6 	110
#define GPIO_13_7 	111

#define GPIO_14_0 	112
#define GPIO_14_1 	113
#define GPIO_14_2 	114
#define GPIO_14_3 	115
#define GPIO_14_4 	116
#define GPIO_14_5 	117
#define GPIO_14_6 	118
#define GPIO_14_7 	119

#define GPIO_15_0 	120
#define GPIO_15_1 	121
#define GPIO_15_2 	122
#define GPIO_15_3 	123
#define GPIO_15_4 	124
#define GPIO_15_5 	125
#define GPIO_15_6 	126
#define GPIO_15_7 	127

#define GPIO_16_0 	128
#define GPIO_16_1 	129
#define GPIO_16_2 	130
#define GPIO_16_3 	131
#define GPIO_16_4 	132
#define GPIO_16_5 	133
#define GPIO_16_6 	134
#define GPIO_16_7 	135

#define GPIO_17_0 	136
#define GPIO_17_1 	137
#define GPIO_17_2 	138
#define GPIO_17_3 	139
#define GPIO_17_4 	140
#define GPIO_17_5 	141
#define GPIO_17_6 	142
#define GPIO_17_7 	143

#define GPIO_18_0 	144
#define GPIO_18_1 	145
#define GPIO_18_2 	146
#define GPIO_18_3 	147
#define GPIO_18_4 	148
#define GPIO_18_5 	149
#define GPIO_18_6 	150
#define GPIO_18_7 	151

#define GPIO_19_0 	152
#define GPIO_19_1 	153
#define GPIO_19_2 	154
#define GPIO_19_3 	155
#define GPIO_19_4 	156
#define GPIO_19_5 	157
#define GPIO_19_6 	158
#define GPIO_19_7 	159

#endif
