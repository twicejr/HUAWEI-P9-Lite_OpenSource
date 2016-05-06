/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_apb_mipi.c */
/* Version       : 2.0 */
/* Created       : 2013-03-13*/
/* Last Modified : */
/* Description   :  The C union definition file for the module apb_mipi*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/
/*lint --e{537}*/
#include <osl_types.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MIPI_MAX_BYTE_COUNT     (4)

enum MIPI_CMD_TYPE
{
    MIPI_CMD_TYPE_R0_W   = 0,    /* Register0 Write */
    MIPI_CMD_TYPE_R_W    = 1,    /* Register Write */
    MIPI_CMD_TYPE_R_R    = 2,    /* Register Read */
    MIPI_CMD_TYPE_ER_W   = 3,    /* Extended Register Write */
    MIPI_CMD_TYPE_ER_R   = 4,    /* Extended Register Read */
    MIPI_CMD_TYPE_HS_R_R = 5,    /* Half Speed Register Read */
    MIPI_CMD_TYPE_HS_ER_R= 6,    /* Half Speed Extended Register Read */
    MIPI_CMD_TYPE_MAX,
};

#define MIPI_CMD_FORMAT_R0_W    (1) /* Register0 Write, 1 bit */
#define MIPI_CMD_FORMAT_R_W     (2) /* Register Write, 3 bits */
#define MIPI_CMD_FORMAT_R_R     (3) /* Register Read, 3 bits */
#define MIPI_CMD_FORMAT_ER_W    (0) /* Extended Register Write, 4 bits */
#define MIPI_CMD_FORMAT_ER_R    (2) /* Extended Register Read, 4 bits */
#define MIPI_CMD_FORMAT_HS_R_R  (3) /* Half Speed Register Read, 3 bits */
#define MIPI_CMD_FORMAT_HS_ER_R (3) /* Half Speed Extended Register Read, 3 bits */

/* Register 0 Write */
union mipi_cmd_r0
{
    struct
    {
        u32 mipi_id         : 3 ;
        u32 reserver        : 13;
        u32 parity_cmd_frame: 1 ;
        u32 byte_0          : 7 ;
        u32 cmd_format      : 1 ;
        u32 slave_id        : 4 ;
        u32 cmd_type        : 3 ;
    } attr;
    u32 value;
};

/* Register Read/Write */
union mipi_cmd
{
    struct
    {
        u32 mipi_id         : 3 ;
        u32 reserver        : 4 ;
        u32 parity_byte_0   : 1 ;
        u32 byte_0          : 8 ;
        u32 parity_cmd_frame: 1 ;
        u32 reg_addr        : 5 ;
        u32 cmd_format      : 3 ;
        u32 slave_id        : 4 ;
        u32 cmd_type        : 3 ;
    } attr;
    u32 value;
};

/* Extended Register Read/Write */
union mipi_ex_cmd
{
    struct
    {
        u64 mipi_id         : 3 ;
        u64 parity_byte_3   : 1 ;
        u64 byte_3          : 8 ;
        u64 parity_byte_2   : 1 ;
        u64 byte_2          : 8 ;
        u64 parity_byte_1   : 1 ;
        u64 byte_1          : 8 ;
        u64 parity_byte_0   : 1 ;
        u64 byte_0          : 8 ;
        u64 parity_addr_frame:1 ;
        u64 reg_addr        : 8 ;
        u64 parity_cmd_frame: 1 ;
        u64 byte_count      : 4 ;
        u64 cmd_format      : 4 ;
        u64 slave_id        : 4 ;
        u64 cmd_type        : 3 ;
    } attr;
    struct
    {
        u32 low_value;
        u32 high_value;
    } cmd;
    u64 value;
};


#define MIPI_READ_END_FLAG_BITS_IN_BYTE0    (3)


#ifdef __cplusplus
}
#endif

