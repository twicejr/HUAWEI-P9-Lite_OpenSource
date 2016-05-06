/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <product_config.h>

#include <osl_types.h>

#include <bsp_om.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define mipi_print_error(fmt, ...)
#ifndef MIPI_OK
#define MIPI_OK (0)
#endif

#ifndef MIPI_ERROR
#define MIPI_ERROR  (-1)
#endif


#ifdef CONFIG_MIPI


/*****************************************************************************
* 函 数 名  : bsp_mipi_raw_write
*
* 功能描述  : MIPI Raw Write
*
* 输入参数  : u32 mipi_id   MIPI ID
*             u32 cmd_low   MIPI 指令的低32位
*             u32 cmd_high  MIPI 指令的高32位
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_raw_write(u32 mipi_id, u32 cmd_low, u32 cmd_high);


/*****************************************************************************
* 函 数 名  : bsp_mipi_r0_write
*
* 功能描述  : MIPI R0 Write
*
* 输入参数  : u32 mipi_id   MIPI ID
*             u32 slave_id  Slave ID
*             u8  value     需要向Slave写入的值
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_r0_write(u32 mipi_id, u32 slave_id, u8 value);

/*****************************************************************************
* 函 数 名  : bsp_mipi_read
*
* 功能描述  : MIPI Register Read
*
* 输入参数  : u32 mipi_id   MIPI ID
*             u32 slave_id  Slave ID
*             u32 reg_addr  Slave的寄存器地址
*             u32 is_half_speed 是否需要半速传输
* 输出参数  : u8 *value     回读结果
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value);


/*****************************************************************************
* 函 数 名  : bsp_mipi_write
*
* 功能描述  : MIPI Register Write
*
* 输入参数  : u32 mipi_id   MIPI ID
*             u32 slave_id  Slave ID
*             u32 reg_addr  Slave的寄存器地址
*             u8  value     需要向Slave写入的值
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value);


/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_read
*
* 功能描述  : MIPI Expended Register Read
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u32 is_half_speed 是否需要半速传输
*             u32 byte_count 需要回读的字节数
* 输出参数  : u8 *value      回读buffer地址
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value, u32 byte_count);


/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_write
*
* 功能描述  : MIPI Expended Register Write
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u8* value      需要向Slave写入的buffer地址
*             u32 byte_count 需要写入的字节数
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 *value, u32 byte_count);


/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_read_byte
*
* 功能描述  : MIPI Expended Register Read，单字节读取
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u32 is_half_speed 是否需要半速传输
* 输出参数  : u8  *value     回读buffer地址
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_read_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value);

/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_read_word
*
* 功能描述  : MIPI Expended Register Read，单字读取
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u32 is_half_speed 是否需要半速传输
* 输出参数  : u16 *value      回读buffer地址
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_read_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u16 *value);


/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_read_dword
*
* 功能描述  : MIPI Expended Register Read，双字读取
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u32 is_half_speed 是否需要半速传输
* 输出参数  : u32 *value      回读buffer地址
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_read_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u32 *value);


/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_write_byte
*
* 功能描述  : MIPI Expended Register Write，单字节写入
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u8  value      需要向Slave写入的值
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_write_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value);


/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_write_word
*
* 功能描述  : MIPI Expended Register Write，单字写入
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u16 value      需要向Slave写入的值
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_write_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u16 value);


/*****************************************************************************
* 函 数 名  : bsp_mipi_ex_write_dword
*
* 功能描述  : MIPI Expended Register Write，双字写入
*
* 输入参数  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave的寄存器地址
*             u32 value      需要向Slave写入的值
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int bsp_mipi_ex_write_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 value);


/*****************************************************************************
* 函 数 名  : bsp_mipi_init
*
* 功能描述  : MIPI 初始化
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
void bsp_mipi_init(void);

#else

static inline int bsp_mipi_raw_write(u32 mipi_id, u32 cmd_low, u32 cmd_high)
{
    return 0;
}

static inline int bsp_mipi_r0_write(u32 mipi_id, u32 slave_id, u8 value)
{
    return 0;
}

static inline int bsp_mipi_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value)
{
    return 0;
}

static inline int bsp_mipi_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value)
{
    return 0;
}

static inline int bsp_mipi_ex_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value, u32 byte_count)
{
    return 0;
}

static inline int bsp_mipi_ex_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 *value, u32 byte_count)
{
    return 0;
}

static inline int bsp_mipi_ex_read_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value)
{
    return 0;
}

static inline int bsp_mipi_ex_read_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u32 *value)
{
    return 0;
}

static inline int bsp_mipi_ex_read_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u16 *value)
{
    return 0;
}

static inline int bsp_mipi_ex_write_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value)
{
    return 0;
}

static inline int bsp_mipi_ex_write_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u16 value)
{
    return 0;
}

static inline int bsp_mipi_ex_write_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 value)
{
    return 0;
}

static inline void bsp_mipi_init(void)
{
}

#endif


#ifdef __cplusplus
    }
#endif

