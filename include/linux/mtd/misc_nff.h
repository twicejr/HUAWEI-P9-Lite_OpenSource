/*
 * FileName: kernel/linux/mtd/misc_nff.h
 * Description: define some macros and declear some functions that will be
 * used in file misc_nff.c
 * Copyright (C) Hisilicon technologies Co., Ltd All rights reserved.
 * Revision history:
 */

#ifndef __MISC_H
#define __MISC_H

#include "hisi_partition.h"

#define MISC_DEVICE_NAME          BLK_MTD_MISC
#define MISC_WRITE                0           /*MISC write operation*/
#define MISC_READ                 1           /*MISC read  operation*/
#define MISC_PWSTATE_DATA_SIZE       1          /*1byte*/
#define MISCRW                       1

struct MISC_struct {
	int misc_major_number;
        int initialized;
	struct mtd_info *mtd;
};


struct misc_info_user {
	unsigned long misc_operation;             /*0-write,1-read*/
	unsigned char misc_data[MISC_PWSTATE_DATA_SIZE+1];
};


#endif

