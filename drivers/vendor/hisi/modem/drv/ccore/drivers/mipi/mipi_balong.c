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
#ifdef __cplusplus
extern "C"
{
#endif

#include <osl_bio.h>
#include <osl_types.h>
#include <osl_spinlock.h>
#include <hi_mipi.h>
#include <bsp_om.h>
#include <bsp_bbp.h>
#include <bsp_mipi.h>
#include <bsp_hardtimer.h>

#include <mipi_balong.h>


#define MIPI_OP_TIMEOUT (1000000)


unsigned int g_mipi_base_addr = 0;

spinlock_t g_mipi_spin_lock;


void* bsp_mipi_get_base_addr(void)
{
    return bsp_bbp_part_addr_get(BBP_CTU);
}

u64 bsp_mipi_parity_check(u64 value)
{
    u32 count = 0;

    while (value)
    {
        if (value & 0x01U)
            count++;
        value >>= 1U;
    }

    if (count%2)
        return 0;
    else
        return 1;
}

int bsp_mipi_is_write_op(union mipi_ex_cmd cmd)
{
    int ret = 0;

    ret = (int)((cmd.attr.cmd_type == MIPI_CMD_TYPE_R0_W) ||
        (cmd.attr.cmd_type == MIPI_CMD_TYPE_R_W) ||
        (cmd.attr.cmd_type == MIPI_CMD_TYPE_ER_W));

    return ret;
}
/*lint -save -e801*/
int bsp_mipi_op(union mipi_ex_cmd cmd, union mipi_ex_cmd *result)
{
    int ret = 0;
    u32 value = 0;
    u32 timeout = MIPI_OP_TIMEOUT;

    unsigned long irq_flags = 0;

    if ((!result) || (cmd.attr.cmd_type >= MIPI_CMD_TYPE_MAX))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MIPI, "MIPI args error\r\n");
        return -1;
    }

    spin_lock_irqsave(&g_mipi_spin_lock, irq_flags);

    /* disable xbbp's operate */
    value = readl(g_mipi_base_addr + MIPI_DSP_MIPI0_EN_IMI_OFFSET);
    value |= 0x01;
    writel(value, g_mipi_base_addr + MIPI_DSP_MIPI0_EN_IMI_OFFSET);

    /* write cmd frame */
    writel(cmd.cmd.low_value, g_mipi_base_addr + MIPI_DSP_MIPI0_WDATA_LOW_OFFSET);
    writel(cmd.cmd.high_value, g_mipi_base_addr + MIPI_DSP_MIPI0_WDATA_HIGH_OFFSET);

    /* wait for permission */
    do
    {
        timeout--;
        value = readl(g_mipi_base_addr + MIPI_MIPI0_GRANT_DSP_OFFSET) & 0x01;
    } while (!value && timeout);

    if (!value)
    {
        ret = -1;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MIPI, "MIPI wait for permission timeout\r\n");
        goto error;
    }

    /* start operate */
    value = readl(g_mipi_base_addr + MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET);
    value |= 0x01;
    writel(value, g_mipi_base_addr + MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET);

    if (bsp_mipi_is_write_op(cmd))
    {
        udelay(3);
    }
    else
    {
        timeout = MIPI_OP_TIMEOUT;
        do
        {
            timeout--;
            value = readl(g_mipi_base_addr + MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET) & 0x01;
        } while (!value && timeout);

        if (!value)
        {
            ret = -1;
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MIPI, "MIPI read timeout\r\n");
            goto error;
        }

        /* get data */
        (*result).cmd.low_value = readl(g_mipi_base_addr + MIPI_MIPI0_RD_DATA_LOW_SOFT_OFFSET);
        (*result).cmd.high_value = readl(g_mipi_base_addr + MIPI_MIPI0_RD_DATA_HIGH_SOFT_OFFSET);

        /* end of read */
        value = readl(g_mipi_base_addr + MIPI_DSP_MIPI0_RD_CLR_OFFSET);
        value |= 0x01;
        writel(value, g_mipi_base_addr + MIPI_DSP_MIPI0_RD_CLR_OFFSET);
    }

error:
    /* enable xbbp's operate */
    value = readl(g_mipi_base_addr + MIPI_DSP_MIPI0_EN_IMI_OFFSET);
    value &= (~0x01);
    writel(value, g_mipi_base_addr + MIPI_DSP_MIPI0_EN_IMI_OFFSET);

    spin_unlock_irqrestore(&g_mipi_spin_lock, irq_flags);

    return ret;
}
/*lint -restore*/

int bsp_mipi_r0_write(u32 mipi_id, u32 slave_id, u8 value)
{
    int ret = 0;
    union mipi_ex_cmd cmd;
    union mipi_ex_cmd result;

    union mipi_cmd_r0 cmd_32;

    cmd.value = 0;
    result.value = 0;

    cmd_32.value = 0;

    cmd_32.attr.cmd_type   = MIPI_CMD_TYPE_R0_W;
    cmd_32.attr.slave_id   = slave_id;
    cmd_32.attr.cmd_format = MIPI_CMD_FORMAT_R0_W;
    cmd_32.attr.byte_0 = value;
    cmd_32.attr.parity_cmd_frame = bsp_mipi_parity_check((u64)(cmd_32.value & 0x1FFF0000) >> 16);

    cmd_32.attr.mipi_id = mipi_id;

    cmd.cmd.high_value = cmd_32.value;

    ret = bsp_mipi_op(cmd, &result);

    return ret;
}

int bsp_mipi_raw_write(u32 mipi_id, u32 cmd_low, u32 cmd_high)
{
    int ret = 0;
    union mipi_ex_cmd cmd;
    union mipi_ex_cmd result;

    cmd.cmd.low_value = cmd_low;
    cmd.cmd.high_value = cmd_high;

    ret = bsp_mipi_op(cmd, &result);

    return ret;
}

int bsp_mipi_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value)
{
    int ret = 0;
    union mipi_ex_cmd cmd;
    union mipi_ex_cmd result;

    union mipi_cmd cmd_32;
    union mipi_cmd result_32;

    if (!value)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MIPI, "MIPI args error\r\n");
        return -1;
    }

    cmd.value = 0;
    result.value = 0;

    cmd_32.value = 0;
    result_32.value = 0;

    cmd_32.attr.cmd_type   = MIPI_CMD_TYPE_R_R;
    cmd_32.attr.slave_id   = slave_id;
    cmd_32.attr.cmd_format = MIPI_CMD_FORMAT_R_R;
    cmd_32.attr.reg_addr   = reg_addr;

    cmd_32.attr.parity_cmd_frame = bsp_mipi_parity_check((u64)(cmd_32.value & 0x1FFF0000) >> 16);

    cmd_32.attr.byte_0 = 0x01 << MIPI_READ_END_FLAG_BITS_IN_BYTE0;
    cmd_32.attr.parity_byte_0 = bsp_mipi_parity_check((u64)cmd_32.attr.byte_0);

    cmd_32.attr.mipi_id = mipi_id;

    cmd.cmd.high_value = cmd_32.value;

    ret = bsp_mipi_op(cmd, &result);

    if (!ret)
    {
        result_32.value = result.cmd.high_value;
        *value = result_32.attr.byte_0;
    }

    return ret;
}

int bsp_mipi_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value)
{
    int ret = 0;
    union mipi_ex_cmd cmd;
    union mipi_ex_cmd result;

    union mipi_cmd cmd_32;

    cmd.value = 0;
    result.value = 0;

    cmd_32.value = 0;

    cmd_32.attr.cmd_type   = MIPI_CMD_TYPE_R_W;
    cmd_32.attr.slave_id   = slave_id;
    cmd_32.attr.cmd_format = MIPI_CMD_FORMAT_R_W;
    cmd_32.attr.reg_addr   = reg_addr;
    cmd_32.attr.parity_cmd_frame = bsp_mipi_parity_check((u64)(cmd_32.value & 0x1FFF0000) >> 16);

    cmd_32.attr.byte_0 = value;
    cmd_32.attr.parity_byte_0 = bsp_mipi_parity_check((u64)cmd_32.attr.byte_0);

    cmd_32.attr.mipi_id = mipi_id;

    cmd.cmd.high_value = cmd_32.value;

    ret = bsp_mipi_op(cmd, &result);

    return ret;
}

int bsp_mipi_ex_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value, u32 byte_count)
{
    int i = 0;
    int ret = 0;
    union mipi_ex_cmd cmd;
    union mipi_ex_cmd result;
    u8 buffer[MIPI_MAX_BYTE_COUNT];

    if ((!value) || (byte_count > MIPI_MAX_BYTE_COUNT))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MIPI, "MIPI args error\r\n");
        return -1;
    }

    cmd.value = 0;
    result.value = 0;

    cmd.attr.cmd_type   = MIPI_CMD_TYPE_ER_R;
    cmd.attr.slave_id   = slave_id;
    cmd.attr.cmd_format = MIPI_CMD_FORMAT_ER_R;
    cmd.attr.byte_count = byte_count - 1;


    cmd.attr.parity_cmd_frame = bsp_mipi_parity_check((u64)(cmd.cmd.high_value & 0x1FFF0000) >> 16);
    cmd.attr.reg_addr   = reg_addr;
    cmd.attr.parity_addr_frame = bsp_mipi_parity_check(cmd.attr.reg_addr);

    cmd.attr.byte_0 = 0x01 << MIPI_READ_END_FLAG_BITS_IN_BYTE0;

    cmd.attr.mipi_id = mipi_id;

    ret = bsp_mipi_op(cmd, &result);

    if (!ret)
    {
        buffer[0] = result.attr.byte_0;
        buffer[1] = result.attr.byte_1;
        buffer[2] = result.attr.byte_2;
        buffer[3] = result.attr.byte_3;

        for (i = 0; i <= (int)cmd.attr.byte_count; i++)
        {
            *(value + i) = buffer[i];
        }
    }

    return ret;
}

int bsp_mipi_ex_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 *value, u32 byte_count)
{
    int i = 0;
    int ret = 0;
    union mipi_ex_cmd cmd;
    union mipi_ex_cmd result;
    u8 buffer[MIPI_MAX_BYTE_COUNT] = {0};

    if ((!value) || (byte_count > MIPI_MAX_BYTE_COUNT))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MIPI, "MIPI args error\r\n");
        return -1;
    }

    cmd.value = 0;
    result.value = 0;

    cmd.attr.cmd_type   = MIPI_CMD_TYPE_ER_W;
    cmd.attr.slave_id   = slave_id;
    cmd.attr.cmd_format = MIPI_CMD_FORMAT_ER_W;
    cmd.attr.byte_count = byte_count - 1;

    for (i = 0; i <= (int)cmd.attr.byte_count; i++)
    {
        buffer[i] = *(value + i);
    }

    cmd.attr.parity_cmd_frame = bsp_mipi_parity_check((u64)(cmd.cmd.high_value & 0x1FFF0000) >> 16);

    cmd.attr.reg_addr   = reg_addr;
    cmd.attr.parity_addr_frame = bsp_mipi_parity_check(cmd.attr.reg_addr);

    cmd.attr.byte_0 = buffer[0];
    cmd.attr.parity_byte_0 = bsp_mipi_parity_check(cmd.attr.byte_0);
    cmd.attr.byte_1 = buffer[1];
    cmd.attr.parity_byte_1 = bsp_mipi_parity_check(cmd.attr.byte_1);
    cmd.attr.byte_2 = buffer[2];
    cmd.attr.parity_byte_2 = bsp_mipi_parity_check(cmd.attr.byte_2);
    cmd.attr.byte_3 = buffer[3];
    cmd.attr.parity_byte_3 = bsp_mipi_parity_check(cmd.attr.byte_3);

    cmd.attr.mipi_id = mipi_id;

    ret = bsp_mipi_op(cmd, &result);

    return ret;
}

int bsp_mipi_ex_read_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value)
{
    return bsp_mipi_ex_read(mipi_id, slave_id, reg_addr, is_half_speed, (u8*)value, sizeof(u8));
}

int bsp_mipi_ex_read_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u16 *value)
{
    return bsp_mipi_ex_read(mipi_id, slave_id, reg_addr, is_half_speed, (u8*)value, sizeof(u16));
}

int bsp_mipi_ex_read_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u32 *value)
{
    return bsp_mipi_ex_read(mipi_id, slave_id, reg_addr, is_half_speed, (u8*)value, sizeof(u32));
}

int bsp_mipi_ex_write_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value)
{
    return bsp_mipi_ex_write(mipi_id, slave_id, reg_addr, (u8*)&value, sizeof(value));
}

int bsp_mipi_ex_write_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u16 value)
{
    return bsp_mipi_ex_write(mipi_id, slave_id, reg_addr, (u8*)&value, sizeof(value));
}

int bsp_mipi_ex_write_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 value)
{
    return bsp_mipi_ex_write(mipi_id, slave_id, reg_addr, (u8*)&value, sizeof(value));
}

void bsp_mipi_init(void)
{
    spin_lock_init(&g_mipi_spin_lock);

    g_mipi_base_addr = (unsigned int)bsp_mipi_get_base_addr();

    bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_MIPI, "MIPI init ok\r\n");
}


int bsp_mipi_read_debug(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed)
{
    int ret = 0;
    u8 value = 0;

    ret = bsp_mipi_read(mipi_id, slave_id, reg_addr, is_half_speed, &value);
    bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI, "MIPI ID = %d, slave_id = %d, reg_addr = 0x%08X, reg_value = 0x%08X\r\n",
        mipi_id, slave_id, reg_addr, value);

    return ret;
}

int bsp_mipi_ex_read_byte_debug(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed)
{
    int ret = 0;
    u8 value = 0;

    ret = bsp_mipi_ex_read(mipi_id, slave_id, reg_addr, is_half_speed, (u8*)&value, sizeof(value));
    bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI, "MIPI ID = %d, slave_id = %d, reg_addr = 0x%08X, reg_value = 0x%08X\r\n",
        mipi_id, slave_id, reg_addr, value);

    return ret;
}

int bsp_mipi_ex_read_word_debug(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed)
{
    int ret = 0;
    u16 value = 0;

    ret = bsp_mipi_ex_read(mipi_id, slave_id, reg_addr, is_half_speed, (u8*)&value, sizeof(value));
    bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI, "MIPI ID = %d, slave_id = %d, reg_addr = 0x%08X, reg_value = 0x%08X\r\n",
        mipi_id, slave_id, reg_addr, value);

    return ret;
}

int bsp_mipi_ex_read_dword_debug(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed)
{
    int ret = 0;
    u32 value = 0;

    ret = bsp_mipi_ex_read(mipi_id, slave_id, reg_addr, is_half_speed, (u8*)&value, sizeof(value));
    bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_MIPI, "MIPI ID = %d, slave_id = %d, reg_addr = 0x%08X, reg_value = 0x%08X\r\n",
        mipi_id, slave_id, reg_addr, value);

    return ret;
}


#ifdef __cplusplus
}
#endif

