/*
 * FileName: hi6xxx-lcd_type.h
 * Copyright (C) Hisilicon technologies Co., Ltd All rights reserved.
 * Discription: privoid the interfaces for the use of getting current platform's BOARDID.
 * Author:   fengquansheng
 */
#ifndef LCD_TYPE_H_
#define LCD_TYPE_H_
#define UNKNOWN_LCD       0
#define TM_NT35521_LCD    1
#define BOE_NT35521_LCD   2
#define CMI_NT35521_LCD   3
#define JDI_1902B_LCD     4
#define YASSY_HX8394_LCD  5
#define JDI_LPM070W425C_LCD    6 
#define JDI_1282B_LCD     7
#define TM_HX8394_LCD	8
#define YASSY_ILI9881_3_LCD	9
#define CMI_OTM1284A_LCD	10
#define CMI_OTM1283A_LCD    11
#define BOE_NT35521_5P0_LCD   12
#define BOE_NT35521S_5P0_LCD   13
int get_lcd_type(void);
int get_isfullhd(void);
#endif
