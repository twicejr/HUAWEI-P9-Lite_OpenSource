/*
 * FileName: boardid.h
 * Copyright (C) Hisilicon technologies Co., Ltd All rights reserved.
 * Discription: privoid the interfaces for the use of getting current platform's BOARDID.
 * Author:   fengquansheng
 */
#ifndef BOARD_ID_H_
#define BOARD_ID_H_

#define CS_CHIP_ID 0x36200110 /* mass-produced chip */
#define DI_CHIP_ID 0x36200100 /* Designe-in chip */

typedef struct board_id_parameter{
	unsigned int chip_id;
	unsigned int pmu_id;
	unsigned int board_id;
}boardid_parameter;

/* Format of hex string: 0x12345678 */
#define HEX_STRING_MAX		(10)
#define TRANSFER_BASE		(16)


unsigned int get_boardid(void);
unsigned int get_chipid(void);
unsigned int get_pmuid(void);



#endif
