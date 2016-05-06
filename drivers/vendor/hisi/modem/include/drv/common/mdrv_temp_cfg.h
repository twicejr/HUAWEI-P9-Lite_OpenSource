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

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __DRV_TEMP_CFG_H__
#define __DRV_TEMP_CFG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define HKADC_LOGIC_CHAN_MAX 32 /* 最大逻辑通道号 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*定义hkadc物理通道号*/
#define HKADC_CHAN_MAX 16
#define TSENS_REGION_MAX 3

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
struct drv_hkadc_map
{
    unsigned int logic_chan;
    unsigned int phy_chan;
    unsigned int nv_id;
    unsigned int nv_len;
    unsigned int modem_id;
    char * name;
};

/* 温度输出区结构 */
typedef struct hkadc_chan_out
{
    unsigned short volt_l;    /* 返回的HKADC电压值，单位:毫伏 */
    unsigned short volt_r;   /* 返回的HKADC电压值取反 */
    short          temp_l;     /* 返回的温度值，单位:摄氏度 */
    short          temp_r;    /* 返回的温度值取反 */
}DRV_CHANNEL_OUTPUT;

/* 温度电压对应表结构 */
typedef struct hkadc_tem_value
{
    short   temp;             /* 温度点，单位:摄氏度 */
    unsigned short volt;      /* 电压点，单位:毫伏 */
}TEM_VOLT_TABLE;

/* 输出配置bit结构 */
typedef struct hkadc_out_config
{
   unsigned int out_prop:2;
   unsigned int out_wake:1;
   unsigned int out_vol_temp:1;
   unsigned int out_reserv1:4;
   unsigned int out_acore:1;
   unsigned int out_ccore:1;
   unsigned int out_reserv2:22;
} OUT_PROP_CONFIG;

/* 温度配置区结构 */
typedef struct hkadc_chan_config
{
    union
    {
        unsigned int out_config;       /* bit0-bit1 0:不输出 1:单次输出 2:循环输出 */
                                       /* bit2 1:唤醒输出 0:非唤醒输出 */
                                       /* bit3: 0:只输出电压 1:电压温度均输出 */
                                       /* bit8: A核输出 */
                                       /* bit9: C核输出 */
        struct hkadc_out_config bit_out_config;
    } outcfg;

    unsigned int have_config;
    unsigned short out_peroid;     /* 循环输出时的循环周期，单位:秒 */
    unsigned short temp_data_len;  /* 温度转换表长度 */
    struct hkadc_tem_value temp_table[32]; /* 温度转换表，实际长度参见temp_data_len */
} DRV_CHANNEL_CONFIG;

/* 系统放电温度保护配置结构 */
typedef struct sys_temp_cfg
{
    unsigned short enable;        /* bit0:高温保护使能 bit1:低温保护使能 1 使能 0 关闭*/
    unsigned short hkadc_id;      /* 系统放电温度保护的hkadc通道ID */
    short          high_thres;    /* 系统放电高温保护的电压阀值 ，温度越高，电压越低*/
    unsigned short high_count;    /* 系统放电高温保护次数上限，到了后系统关机 */
    short          low_thres;     /* 系统放电低温保护的电压阀值 ，温度越低，电压越高*/
    unsigned short low_count;     /* 系统放电低温保护次数上限，到了后系统关机 */

    unsigned int   reserved[2];   /*保留*/
} DRV_SYS_TEMP_PRO;

/* 共享温度区数据结构 */
typedef struct thermal_data_area
{
    unsigned int               magic_start;                 /* 分区起始Magic Code 0x5A5A5A5A*/
    struct hkadc_chan_out       chan_out[HKADC_CHAN_MAX];    /* 各通道输出区域*/
    struct hkadc_chan_config    chan_cfg[HKADC_CHAN_MAX];    /* 各通道配置区域 */
    struct sys_temp_cfg         sys_temp_cfg;                /* 系统放电温保配置 */
    unsigned int               hw_ver_id;                   /* 版本ID */
    unsigned char               phy_tbl[HKADC_LOGIC_CHAN_MAX];     /* HKADC逻辑通道到物理通道对应表 */
    unsigned int               debug_flag;                  /* 调测开关 */
    unsigned int               magic_end;                   /* 分区结束Magic Code 0x5A5A5A5A*/
} DRV_HKADC_DATA_AREA;

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

