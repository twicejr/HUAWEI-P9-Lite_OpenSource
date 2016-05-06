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

#ifndef    _DRV_HSUART_H_
#define    _DRV_HSUART_H_


#ifdef __cplusplus
extern "C" 
{ 
#endif /* __cplusplus */

/**************************************************************************
  头文件包含                            
**************************************************************************/
#include "mdrv_udi.h"
/**************************************************************************
  宏定义 
**************************************************************************/
#define UART_IOCTL_SET_WRITE_CB      		0x7F001000
#define UART_IOCTL_SET_READ_CB       		0x7F001001
#define UART_IOCTL_SET_EVT_CB        		0x7F001002
#define UART_IOCTL_SET_FREE_CB       		0x7F001003
#define UART_IOCTL_WRITE_ASYNC       		0x7F001010
#define UART_IOCTL_GET_RD_BUFF       		0x7F001011
#define UART_IOCTL_RETURN_BUFF       		0x7F001012
#define UART_IOCTL_RELLOC_READ_BUFF  		0x7F001013
#define UART_IOCTL_SEND_BUFF_CAN_DMA 		0x7F001014
#define UART_IOCTL_SET_WRITE_TIMEOUT 		0x7F001015
#define UART_IOCTL_SET_BAUD           		0X7F001016
#define UART_IOCTL_SET_WLEN           		0X7F001017
#define UART_IOCTL_SET_STP2           		0X7F001018
#define UART_IOCTL_SET_EPS            		0X7F001019
#define UART_IOCTL_IS_IMPORT_DONE    		0x7F001020
#define UDI_UART_IOCTL_SET_READ_CB          UART_IOCTL_SET_READ_CB
#define UDI_UART_IOCTL_GET_READ_BUFFER_CB   UART_IOCTL_GET_RD_BUFF
#define UDI_UART_IOCTL_RETUR_BUFFER_CB      UART_IOCTL_RETURN_BUFF
#define UART_IOCTL_SET_MSC_READ_CB 			0x7F001021
#define UART_IOCTL_MSC_WRITE_CMD 			0x7F001022
#define UART_IOCTL_SWITCH_MODE_CB 			0x7F001023
#define UART_IOCTL_SET_FLOW_CONTROL 		0x7F001024
#define UART_IOCTL_SET_AC_SHELL 			0x7F001025
#define UART_IOCTL_SET_WATER_CB 			0x7F001026
#define UART_IOCTL_RELEASE_BUFF				0x7F001027

#define UART_A_SHELL  (0x5A5A5A5A)
#define UART_C_SHELL  (0xA5A5A5A5)
/**************************************************************************
  枚举定义
**************************************************************************/
enum MEM_TYPE_ENUM
{
    MEM_TYPE_SYS_DEFINED = 0,            /* 数据块由Linux系统提供*/
    MEM_TYPE_USER_DEFINED,               /* 数据块由用户管理的内存提供*/
    MEM_TYPE_BUTT
 };

/* UART数据位长*/
typedef enum
{
    WLEN_5_BITS,
    WLEN_6_BITS,
    WLEN_7_BITS,
    WLEN_8_BITS,
    WLEN_MAX,
}UART_WLEN_ENUM;

/* UART停止位长*/
typedef enum
{
    STP2_OFF,
    STP2_ON,
    STP2_MAX,
}uart_stp2_enum;

/* UART校验方式*/
typedef enum
{
    PARITY_NO_CHECK,
    PARITY_CHECK_ODD,
    PARITY_CHECK_EVEN,
    PARITY_CHECK_MARK,        /*校验位始终为1*/
    PARITY_CHECK_SPACE,       /*校验位始终为0*/
    PARITY_CHECK_MAX,
}uart_parity_enum;

typedef enum tagwater_level
{
	HIGH_LEVEL,
	LOW_LEVEL,
}water_level;

/**************************************************************************
  STRUCT定义
**************************************************************************/
typedef void (*hsuart_free_cb_t)(char* pBuff);
typedef void (*hsuart_read_cb_t)(void);
typedef void (*hsuart_msc_read_cb_t)(MODEM_MSC_STRU* pModemMsc);
typedef void (*hsuart_switch_mode_cb_t)(void);
typedef void (*hsuart_water_cb)(water_level level);

typedef struct tagUART_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}hsuart_read_buff_info;

/* 流控开关结构 */
typedef union
{
   unsigned int      value;
    struct
    {
		unsigned int  reserved1 : 14;/* bit[0-13] : reversed */
		unsigned int  rtsen         : 1;/* bit[14] : rts enable, up stream flow ctrl  */
 		unsigned int  ctsen         : 1;/* bit[15] : cts enable, down stream flow ctrl */
 		unsigned int  reserved2 : 16;/* bit[16-31] : reversed */
    } reg;
}uart_flow_ctrl_union;


#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif

