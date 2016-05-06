/*
 * FileName: kernel/linux/mtd/nve.h
 * Description: define some macros and declear some functions that will be
 * used in file nve.c.
 * Copyright (C) Hisilicon technologies Co., Ltd All rights reserved.
 * Revision history:
 */

#ifndef __NVE_H
#define __NVE_H

#include "hisi_partition.h"

#define TEST_NV_IN_KERNEL       1

#define NVE_PARTITION_SIZE      (128 * 1024)
#define NVE_PARTITION_NUMBER    7
#define NV_NAME_LENGTH          8
#define NVE_NV_DATA_SIZE        104
#define NVE_INVALID_NVM         0xFFFFFFFF
#define NVE_PARTITION_COUNT	8


#define NVE_HEADER_NAME         "Hisi-NV-Partition"   /* ReliableData area */
#define NV_DEVICE_NAME          "block2mtd: /dev/block/mmcblk0p7"

#define NV_INFO_LEN  1024
/*
 *In case accidently power-off happened when NV
 * is writing,we put the partition_header at the
 * position that locate the last 128 Bytes of every
 * partition,so even if power-off happend,current
 * partition's age will not increase which means current
 * partition is not updated and is invalid partiton.
 */

#define PARTITION_HEADER_SIZE      128
#define PARTITION_HEADER_OFFSET    (NVE_PARTITION_SIZE - PARTITION_HEADER_SIZE)

struct NVE_index {
	char nv_name[NV_NAME_LENGTH];
	unsigned int nv_offset;
	unsigned int nv_size;
};

struct NVE_partition_header {
	char nve_partition_name[32];
	unsigned int nve_version;           /*should be built in image with const value*/
	unsigned int nve_block_id;          /*should be built in image with const value*/
	unsigned int nve_block_count;       /*should be built in image with const value*/
	unsigned int valid_items;           /*should be built in image with const value*/
	unsigned int nv_checksum;
	unsigned char reserved[72];
	unsigned int nve_age;               /*changed by run-time image*/
};

struct NV_header {
	unsigned int nv_number;
	char nv_name[NV_NAME_LENGTH];
	unsigned int nv_property;       /*bit 0:"0" for volatile;"1" for non-volatile.*/
	unsigned int valid_size;
	unsigned char reserved[4];
};

struct NV_struct {
	struct NV_header nv_header;
	u_char nv_data[NVE_NV_DATA_SIZE];
};

struct NVE_struct {
	int nve_major_number;
	int initialized;
	unsigned int nve_partition_count;
	unsigned int nve_current_id;
	struct NVE_index *nve_index_table;
	struct mtd_info *mtd;
	u_char *nve_ramdisk;
};

#endif
