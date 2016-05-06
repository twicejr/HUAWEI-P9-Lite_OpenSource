/*
 * arch/arm/mach-k3v2/common.c
 *
 * Copyright (C) 2011 Hisilicon Co. Ltd.
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/printk.h> 
#include <linux/init.h>
#include <linux/hisi/hi6xxx-lcd_type.h>
#define LCD_TYPE_STR_NOLCD_C                     "NO_LCD_C"
#define LCD_TYPE_STR_NOLCD_S                     "NO_LCD_S"
#define LCD_TYPE_STR_TM_NT35521_LCD         "TM_NT35521_LCD"
#define LCD_TYPE_STR_BOE_NT35521_LCD        "BOE_NT35521_LCD"
#define LCD_TYPE_STR_CMI_NT35521_LCD        "CMI_NT35521_LCD"
#define LCD_TYPE_STR_YASSY_HX8394_LCD        "YASSY_HX8394_LCD"
#define LCD_TYPE_STR_JDI_1902B_LCD     "JDI_1902B_LCD"

#define LCD_TYPE_STR_TM_HX8394_LCD        "TM_HX8394_LCD"
#define LCD_TYPE_STR_YASSY_ILI9881_3_LCD        "YASSY_ILI9881-3_LCD"
#define LCD_TYPE_STR_CMI_OTM1284A_LCD        "CMI_OTM1284A_LCD"
#define LCD_TYPE_STR_CMI_OTM1283A_LCD        "CMI_OTM1283A_LCD"
#define LCD_TYPE_STR_BOE_NT35521_5P0_LCD        "BOE_NT35521_5P0_LCD"
#define LCD_TYPE_STR_BOE_NT35521S_5P0_LCD        "BOE_NT35521S_5P0_LCD"
static char lcd_type_buf[50];
int get_lcd_type(void)
{
    if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_NOLCD_C, strlen(LCD_TYPE_STR_NOLCD_C))) {
        printk("%s : found no lcd ,default is TM_NT35521_LCD.\n", __func__);
        return TM_NT35521_LCD;
    } else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_NOLCD_S, strlen(LCD_TYPE_STR_NOLCD_S))) {
        printk("%s : found no lcd,default is CMI_OTM1283A_LCD\n", __func__);
        return CMI_OTM1283A_LCD;
    } else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_TM_NT35521_LCD, strlen(LCD_TYPE_STR_TM_NT35521_LCD))) {
        printk("%s : found TM_NT35521_LCD.\n", __func__);
        return TM_NT35521_LCD;
    } else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_BOE_NT35521_LCD, strlen(LCD_TYPE_STR_BOE_NT35521_LCD))) {
        printk("%s : found BOE_NT35521_LCD.\n", __func__);
        return BOE_NT35521_LCD;
    } else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_CMI_NT35521_LCD, strlen(LCD_TYPE_STR_CMI_NT35521_LCD))) {
        printk("%s : found CMI_NT35521_LCD.\n", __func__);
        return CMI_NT35521_LCD;
    }else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_YASSY_HX8394_LCD, strlen(LCD_TYPE_STR_YASSY_HX8394_LCD))) {
        printk("%s : found YASSY_HX8394_LCD.\n", __func__);
        return YASSY_HX8394_LCD;
    }else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_JDI_1902B_LCD, strlen(LCD_TYPE_STR_JDI_1902B_LCD))) {
        printk("%s : found JDI_1902B_LCD.\n", __func__);
        return JDI_1902B_LCD;
    }else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_TM_HX8394_LCD, strlen(LCD_TYPE_STR_TM_HX8394_LCD))){
        printk("%s : found TM_HX8394_LCD.\n", __func__);
        return TM_HX8394_LCD;
    }else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_YASSY_ILI9881_3_LCD, strlen(LCD_TYPE_STR_YASSY_ILI9881_3_LCD))) {
        printk("%s : found YASSY_ILI9881_3_LCD.\n", __func__);
        return YASSY_ILI9881_3_LCD;
    }else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_CMI_OTM1284A_LCD, strlen(LCD_TYPE_STR_CMI_OTM1284A_LCD))) {
        printk("%s : found CMI_OTM1284A_LCD.\n", __func__);
        return CMI_OTM1284A_LCD;
    }else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_CMI_OTM1283A_LCD, strlen(LCD_TYPE_STR_CMI_OTM1283A_LCD))) {
        printk("%s : found CMI_OTM1283A_LCD.\n", __func__);
        return CMI_OTM1283A_LCD;
    }else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_BOE_NT35521_5P0_LCD, strlen(LCD_TYPE_STR_BOE_NT35521_5P0_LCD))){
        printk("%s : found BOE_NT35521_5P0_LCD.\n", __func__);
        return BOE_NT35521_5P0_LCD;
    }
    else if (0 == strncmp(lcd_type_buf, LCD_TYPE_STR_BOE_NT35521S_5P0_LCD, strlen(LCD_TYPE_STR_BOE_NT35521S_5P0_LCD))){
        printk("%s : found BOE_NT35521S_5P0_LCD.\n", __func__);
        return BOE_NT35521S_5P0_LCD;
    }else{
        printk("%s : there is no lcd.\n", __func__);
        return TM_NT35521_LCD;
    }
}
EXPORT_SYMBOL_GPL(get_lcd_type);

static int __init early_parse_lcd_type_cmdline(char *p)
{
    unsigned int len = 0;
    memset(lcd_type_buf, 0, sizeof(lcd_type_buf));
    if (p) 
    {
        len = strlen(p);
        if(len > sizeof(lcd_type_buf))
        {
           len = sizeof(lcd_type_buf);
        }
        memcpy(lcd_type_buf, p, len);
    }
    else
    {
        pr_info("%s : p is NULL\n", __func__);
    }
    
    return 0;
}
early_param("LCD_TYPE", early_parse_lcd_type_cmdline);

#define FULLHD_STRING_MAX   1
static int isfullhd = 0;
static int __init isfullhd_setup(char *val)
{
    char fullhd[FULLHD_STRING_MAX + 1];
    char *endptr = NULL;
    memset(fullhd, 0, (FULLHD_STRING_MAX + 1));
    memcpy(fullhd, val, FULLHD_STRING_MAX);
    fullhd[FULLHD_STRING_MAX] = '\0';
    isfullhd = (int )simple_strtoul(fullhd, &endptr, 10);
    return 0;
}
early_param("isfullhd", isfullhd_setup);

int get_isfullhd(void)
{
    return isfullhd;
}
EXPORT_SYMBOL(get_isfullhd);

