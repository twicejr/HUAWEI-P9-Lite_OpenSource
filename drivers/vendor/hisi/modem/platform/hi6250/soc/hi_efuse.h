/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_efuse.h */
/* Version       : 2.0 */
/* Created       : 2013-02-27*/
/* Last Modified : */
/* Description   :  The C union definition file for the module efuse*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_EFUSE_H__
#define __HI_EFUSE_H__

/*
 * Project: hi
 * Module : efuse
 */

#define HI_K3_EFUSE

#define EFUSE_MAX_SIZE          (64)

#define EFUSE_GRP_DIEID         (32)
#define EFUSE_DIEID_SIZE        (5)
#define EFUSE_DIEID_BIT         (28)
#define EFUSE_DIEID_LEN         (EFUSE_DIEID_SIZE * EFUSE_GROUP_SIZE)

#define EFUSE_GRP_HUK           (28)
#define EFUSE_HUK_SIZE          (4)
#define EFUSE_HUK_LEN           (EFUSE_HUK_SIZE * EFUSE_GROUP_SIZE)

#define EFUSE_GRP_CHIPID        (57)
#define EFUSE_CHIPID_SIZE       (2)
#define EFUSE_CHIPID_LEN        (EFUSE_CHIPID_SIZE * EFUSE_GROUP_SIZE)

#define HUK_SEC_DDR_ADDR        0x35c80000
#define HUK_SEC_DDR_SIZE        0x1000
#define HUK_SEC_DDR_OFFSET      0x150


#endif // __HI_EFUSE_H__

