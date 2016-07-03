/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_vic.h */
/* Version       : 2.0 */
/* Author        : xxx*/
/* Created       : 2013-01-10*/
/* Last Modified : */
/* Description   :  The C union definition file for the module timer*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : xxx*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_VIC_H__
#define __HI_VIC_H__

/*
 * Project: hi
 * Module : timer
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    vic 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_VIC_INTEN_L_OFFSET                      (0x0) 
#define    HI_VIC_INTEN_H_OFFSET                      (0x4) 
#define    HI_VIC_INTMASK_L_OFFSET                    (0x8) 
#define    HI_VIC_INTMASK_H_OFFSET                    (0xC) 
#define    HI_VIC_INTFORCE_L_OFFSET                   (0x10) 
#define    HI_VIC_INTFORCE_H_OFFSET                   (0x14) 
#define    HI_VIC_RAWSTATUS_L_OFFSET                  (0x18) 
#define    HI_VIC_RAWSTATUS_H_OFFSET                  (0x1C) 
#define    HI_VIC_STATUS_L_OFFSET                     (0x20) 
#define    HI_VIC_STATUS_H_OFFSET                     (0x24) 
#define    HI_VIC_MASKSTATUS_L_OFFSET                 (0x28) 
#define    HI_VIC_MASKSTATUS_H_OFFSET                 (0x2C) 
#define    HI_VIC_FINALSTATUS_L_OFFSET                (0x30) 
#define    HI_VIC_FINALSTATUS_H_OFFSET                (0x34) 
#define    HI_VIC_VECTOR_OFFSET                       (0x38) 
#define    HI_VIC_VECTOR_0_OFFSET                     (0x40) 
#define    HI_VIC_VECTOR_1_OFFSET                     (0x48) 
#define    HI_VIC_VECTOR_2_OFFSET                     (0x50) 
#define    HI_VIC_VECTOR_3_OFFSET                     (0x58) 
#define    HI_VIC_VECTOR_4_OFFSET                     (0x60) 
#define    HI_VIC_VECTOR_5_OFFSET                     (0x68) 
#define    HI_VIC_VECTOR_6_OFFSET                     (0x70) 
#define    HI_VIC_VECTOR_7_OFFSET                     (0x78) 
#define    HI_VIC_VECTOR_8_OFFSET                     (0x80) 
#define    HI_VIC_VECTOR_9_OFFSET                     (0x88) 
#define    HI_VIC_VECTOR_10_OFFSET                    (0x90) 
#define    HI_VIC_VECTOR_11_OFFSET                    (0x98)
#define    HI_VIC_VECTOR_12_OFFSET                    (0xA0)
#define    HI_VIC_VECTOR_13_OFFSET                    (0xA8)
#define    HI_VIC_VECTOR_14_OFFSET                    (0xB0)
#define    HI_VIC_VECTOR_15_OFFSET                    (0xB8)

#endif __HI_VIC_H__

