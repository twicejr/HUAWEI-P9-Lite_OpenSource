	/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*	3
*   文 件 名 :  device_tree.h
*	5
*   作    者 :  y00184236
*	7
*   描    述 :  提供设备树操作驱动头文件
*	9
*   修改记录 :  2014年07月28日  v1.00  y00184236  创建
*	11
*************************************************************************/
#ifndef _DEVICE_TREE_H
#define _DEVICE_TREE_H
#include <linux/types.h>

#define HSDT_MAGIC  		(0x54445348)       /* Master DTB magic "HSDT" */
#define HSDT_VERSION		(1)
#ifdef CONFIG_MODEMID_HI3650
#define CHIP_COMPITABLE_STR "hisilicon,hi3650"
#endif
#define BOARDID_STR         "hisi,boardid"
#define MODEMID_STR         "hisi,modem_id"
#define BSP_MODEM_DTB_HEADER (1024*6)

#define MODEMID_MASK_BITS	   (0xff)
#define MODEMID_K_BITS(n)      ((n >> 24) & MODEMID_MASK_BITS)
#define MODEMID_H_BITS(n)      ((n >> 16) & MODEMID_MASK_BITS)
#define MODEMID_M_BITS(n)      ((n >> 8) & MODEMID_MASK_BITS)
#define MODEMID_L_BITS(n)      (n & MODEMID_MASK_BITS)

#define BOARD_DTB_SIZE   (0x40000)
#define DTB_VRL_SIZE   	 (0x1000)

typedef struct modem_dt_table_t {
	uint32_t magic;
	uint32_t version;
	uint32_t num_entries;
} modem_dt_table_t;

typedef struct modem_dt_entry_t {
    uint8_t boardid[4];
    uint8_t reserved[4];
    uint32_t dtb_size;
    uint32_t vrl_size;
    uint32_t dtb_offset;
    uint32_t vrl_offset;
    uint64_t dtb_file;
    uint64_t vrl_file;
} modem_dt_entry_t;

#endif
