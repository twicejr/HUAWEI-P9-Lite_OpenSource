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

/*lint -save -e537*/
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "product_config.h"
#include "osl_bio.h"
#include "osl_sem.h"
#include "osl_thread.h"
#include "osl_wait.h"
#include "osl_spinlock.h"
#include "soc_clk.h"
#include "bsp_memmap.h"
#include "hi_base.h"
#include "hi_efuse.h"

#include "bsp_icc.h"
#include "bsp_hardtimer.h"
#include "bsp_om.h"
#include "bsp_efuse.h"


/*lint -restore*/

#ifndef CONFIG_TRUSTZONE

#define TIMEMAXDELAY   (0x1000000)       /*最大延迟时间*/

static struct spinlock efuse_lock;
static void* efuse_base_addr = 0;

typedef unsigned int (*punptr)(void);
/*********************************************************************************************
Function:           test_bit_value
Description:        测试寄存器中的某位，是否等于指定的值
Calls:              无
Data Accessed:      无
Data Updated:       无
Input:              addr：  寄存器地址
                    bitMask：需要检测的位置
                    bitValue：指定的值
Output:             无
Return:             成功则返回TRUE， 失败则返回FALSE
Others:             无
*********************************************************************************************/
int test_bit_value(punptr pfun,  u32 bitValue)
{
    u32 time;                       /*延时时间*/

    for(time = 0; time < TIMEMAXDELAY; time++)
    {
        if(bitValue == (*pfun)())
        {
            return EFUSE_OK;
        }
    }

    return EFUSE_ERROR;
}
int hi_efuse_get_reg(unsigned int *value,unsigned int offset,unsigned int lowbit,unsigned int highbit)
{
    unsigned int mask = 0;
    unsigned int temp = 0;

    if(!efuse_base_addr)
    {
        efuse_print_error("efuse_base_addr may be not initial!\n,pls check!\n");
        return EFUSE_ERROR;
    }
    if(highbit > 31  || (highbit < lowbit) )
    {
        efuse_print_error("param error ,lowbit:%d,highbit:%d\n",lowbit,highbit);
        return EFUSE_ERROR;
    }

    temp   = readl(efuse_base_addr + offset);
    mask   = ((1 << (highbit - lowbit + 1) )-1) << lowbit;
    *value = (temp & mask)>>lowbit;

    return EFUSE_OK;
}

int hi_efuse_set_reg(unsigned int value,unsigned int offset,unsigned int lowbit,unsigned highbit)
{
    void* reg    = efuse_base_addr + offset;
    unsigned int temp   = 0;
    unsigned int mask   = 0;

    if(!efuse_base_addr){
        efuse_print_error("efuse_base_addr may be not initial!\n,pls check!\n");
        return EFUSE_ERROR;
    }
    if(highbit > 31  || (highbit < lowbit) )
    {
        efuse_print_error("param error ,lowbit:%d,highbit:%d\n",lowbit,highbit);
        return EFUSE_ERROR;
    }

    temp   = readl(reg);
    mask   = ((1 << (highbit - lowbit + 1)) -1) << lowbit;

    value  = (temp & (~mask)) | ((value << lowbit) & mask);
    writel(value  ,reg);

    return EFUSE_OK;

}
/*****************************************************************************
* 函 数   : hi_efuse_get_pd_status
* 功 能   : 获取efuse power-down状态
* 输 入   : 无
* 输 出   : 无
* 返 回   : -1表示获取失败，0为pd，1为正常态
* 说 明   :
*****************************************************************************/
unsigned int hi_efuse_get_pd_status(void)
{
    unsigned int val = 0;
    int          ret = 0;

    ret = hi_efuse_get_reg(&val, HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PD_STAT_BIT, HI_EFUSE_PD_STAT_BIT);
    if(ret){
        efuse_print_error("get efuse pd status faild\n");
    }

    return val;
}
/*****************************************************************************
* 函 数   : hi_efusec_set_pd_en
* 功 能   : 使能efuse power-down状态
* 输 入   : 无
* 输 出   : 无
* 返 回   : -1表示获取失败，0为pd,11为正常态
* 说 明   :
*****************************************************************************/
void hi_efusec_set_pd_en(void)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(0, HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PD_EN_BIT, HI_EFUSE_PD_EN_BIT);
    if(ret){
        efuse_print_error("get efuse pd status faild\n");
    }

    return ;
}
/*****************************************************************************
* 函 数   : hi_efusec_set_pd_en
* 功 能   : 选择信号为apb操作efuse
* 输 入   : 无
* 输 出   : 无
* 返 回   :
* 说 明   :
*****************************************************************************/
void hi_efusec_cfg_aib_sel(void)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(1, HI_EFUSEC_CFG_OFFSET, HI_EFUSE_AIB_SEL_BIT, HI_EFUSE_AIB_SEL_BIT);
    if(ret){
        efuse_print_error("Set efuse AIB_sel faild\n");
    }

    return ;

}
/*****************************************************************************
* 函 数   : hi_efusec_set_pd_en
* 功 能   : 设置efuse group
* 输 入   : 无
* 输 出   : 无
* 返 回   :
* 说 明   :
*****************************************************************************/
void hi_efusec_set_group(unsigned int val)
{

    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(val, HI_EFUSE_GROUP_OFFSET, HI_EFUSE_GROUP_LBIT, HI_EFUSE_GROUP_HBIT);
    if(ret){
        efuse_print_error("Set efuse group faild\n");
    }

    return ;
}

void hi_efusec_set_read_en(void)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(1, HI_EFUSEC_CFG_OFFSET, HI_EFUSE_RD_EN_BIT, HI_EFUSE_RD_EN_BIT);
    if(ret){
        efuse_print_error("Set efuse read enable faild\n");
    }

    return ;

}
unsigned int hi_efusec_get_read_status(void)
{
    unsigned int val = 0;
    int          ret = 0;

    ret = hi_efuse_get_reg(&val, HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_RD_STAT_BIT, HI_EFUSE_RD_STAT_BIT);
    if(ret){
        efuse_print_error("get efuse read status faild\n");
    }

    return val;

}

unsigned int hi_efusec_get_data(void)
{
    unsigned int val = 0;
    int          ret = 0;

    ret = hi_efuse_get_reg(&val, HI_EFUSEC_DATA_OFFSET, HI_EFUSE_DATA_LBIT, HI_EFUSE_DATA_HBIT);
    if(ret){
        efuse_print_error("get efuse data faild\n");
    }

    return val;

}

unsigned int hi_efusec_get_pgm_disable_flag(void)
{
    unsigned int val = 0;
    int          ret = 0;

    ret = hi_efuse_get_reg(&val, HI_HW_CFG_OFFSET, HI_EFUSE_DISFLAG_BIT, HI_EFUSE_DISFLAG_BIT);
    if(ret){
        efuse_print_error("get efuse disable flag faild\n");
    }

    return val;

}

void hi_efusec_set_count(unsigned val)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(val, HI_EFUSEC_COUNT_OFFSET, HI_EFUSE_COUNT_LBIT, HI_EFUSE_COUNT_HBIT);
    if(ret){
        efuse_print_error("Set efuse count faild\n");
    }

    return ;

}

void hi_efusec_set_pgm_count(unsigned val)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(val, HI_PGM_COUNT_OFFSET, HI_EFUSE_PGM_COUNT_LBIT, HI_EFUSE_PGM_COUNT_HBIT);
    if(ret){
        efuse_print_error("Set efuse pgm count faild\n");
    }

    return ;

}

void hi_efusec_set_pre_pg(unsigned val)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(val, HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PRE_PG_BIT, HI_EFUSE_PRE_PG_BIT);
    if(ret){
        efuse_print_error("Set efuse pre pg faild\n");
    }

    return ;

}

void hi_efusec_set_pg_en(unsigned val)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(val, HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PGEN_BIT, HI_EFUSE_PGEN_BIT);
    if(ret){
        efuse_print_error("Set efuse pg en faild\n");
    }

    return ;

}

/*查询是否使能置位 */
unsigned int hi_efusec_get_pgenb_status(void)
{
    unsigned int val = 0;
    int          ret = 0;

    ret = hi_efuse_get_reg(&val, HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PGENB_STAT_BIT, HI_EFUSE_PGENB_STAT_BIT);
    if(ret){
        efuse_print_error("get efuse pgenb status faild\n");
    }

    return val;

}

void hi_efusec_set_pg_value(unsigned int val)
{
    unsigned int ret    = 0;

    ret = hi_efuse_set_reg(val, HI_PG_VALUE_OFFSET, HI_EFUSE_PG_VALUE_LBIT, HI_EFUSE_PG_VALUE_HBIT);
    if(ret){
        efuse_print_error("Set efuse pg value faild\n");
    }

    return ;

}

unsigned int hi_efusec_get_pg_status(void)
{
    unsigned int val = 0;
    int          ret = 0;

    ret = hi_efuse_get_reg(&val, HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PG_STAT_BIT, HI_EFUSE_PG_STAT_BIT);
    if(ret){
        efuse_print_error("get efuse pg status faild\n");
    }

    return val;

}

/*lint -save -e718 -e746*/
/*****************************************************************************
* 函 数 名  : bsp_efuse_read
*
* 功能描述  : 按组读取EFUSE中的数据
*
* 输入参数  : group  起始group
*                   num  数组长度(word数,不超过16)
* 输出参数  : pBuf ：EFUSE中的数据
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int bsp_efuse_read(u32* pBuf, const u32 group, const u32 num)
{
    u32* pSh = 0;
    u32 cnt = 0;
    int ret = EFUSE_ERROR;

    unsigned long flags = 0;
    struct clk *efuse_clk = NULL;

    if((0 == num) || (group + num > EFUSE_MAX_SIZE) || (NULL == pBuf))
    {
        efuse_print_error(" parameter error, group=%d, num=%d, pBuf=0x%x.\n", group, num, pBuf);
        return ret;
    }

    efuse_clk = (struct clk *)clk_get(NULL,"efuse_clk");
    if(IS_ERR(efuse_clk))
    {
        efuse_print_error("efuse clk cannot get, 0x%x.\n", efuse_clk);
        return ret;
    }

    ret = clk_prepare(efuse_clk);
    if (ret) {
        efuse_print_error("efuse clk prepare error, 0x%x.\n", (u32)ret);
        goto clk_prepare_error;
    }

    if(0 != clk_enable(efuse_clk))
    {
        efuse_print_error("efuse clk enable is fail, 0x%x.\n", efuse_clk);
        goto clk_enable_error;
    }

    spin_lock_irqsave(&efuse_lock, flags);

    /*判断是否处在power_down状态*/
    if(hi_efuse_get_pd_status())
    {
       /*退出powerd_down状态*/
        hi_efusec_set_pd_en();

        /* 等待powerd_down退出标志设置成功，否则超时返回错误 */
        if(EFUSE_OK != test_bit_value(hi_efuse_get_pd_status, 0))
        {
            efuse_print_error(" powerd_down disable is fail .\n");
            goto efuse_rd_error;
        }
    }

    /*选择信号为apb操作efuse*/
    hi_efusec_cfg_aib_sel();

    pSh = pBuf;

    /* 循环读取efuse值 */
    for(cnt = 0; cnt < num; cnt++)
    {
        /* 设置读取地址 */
        hi_efusec_set_group( group+cnt);

        /* 使能读 */
        hi_efusec_set_read_en();

        /* 等待读完成 */
        if(EFUSE_OK != test_bit_value(hi_efusec_get_read_status, 1))
        {
            efuse_print_error(" read finish is fail .\n");
            goto efuse_rd_error;
        }
        /* 读取数据 */
        *pSh = hi_efusec_get_data();
        pSh++;

    }

    ret = EFUSE_OK;

efuse_rd_error:
    spin_unlock_irqrestore(&efuse_lock, flags);
    clk_disable(efuse_clk);

clk_enable_error:
    clk_unprepare(efuse_clk);

clk_prepare_error:
    clk_put(efuse_clk);

    return ret;
}
/*lint -restore*/

/*****************************************************************************
* 函 数 名  : bsp_efuse_write
*
* 功能描述  : 烧写Efsue
*
* 输入参数  : pBuf:待烧写的EFUSE值
*                 group,Efuse地址偏移
*                 len,烧写长度
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int bsp_efuse_write( u32 *pBuf, const u32 group, const u32 len )
{
    u32 i = 0;
    u32 u32Grp = 0;
    u32 *pu32Value = 0;

    int ret = EFUSE_ERROR;

    unsigned long flags = 0;
    struct clk *efuse_clk = NULL;
    struct regulator *efuse_regulator = NULL;

    if((0 == len) || (group + len > EFUSE_MAX_SIZE) || (NULL == pBuf))
    {
        efuse_print_error(" parameter error, group=%d, len=%d, pBuf=0x%x.\n", group, len, pBuf);
        return ret;
    }

    efuse_regulator = regulator_get(NULL, "EFUSE-vcc");
    if(NULL == efuse_regulator)
    {
        efuse_print_error("efuse regulator cannot get. \n");
        return ret;
    }

    efuse_clk = (struct clk *)clk_get(NULL,"efuse_clk");
    if(IS_ERR(efuse_clk))
    {
        efuse_print_error("efuse clk cannot get, 0x%x.\n", efuse_clk);
        goto clk_get_error;
    }

    ret = clk_prepare(efuse_clk);
    if (ret) {
        efuse_print_error("efuse clk prepare error, 0x%x.\n", (u32)ret);
        goto clk_prepare_error;
    }

    spin_lock_irqsave(&efuse_lock, flags);

    if(0 != regulator_enable(efuse_regulator))
    {
        efuse_print_error("efuse regulator enable is fail. \n");
        goto regulator_enable_error;
    }

    if(0 != clk_enable(efuse_clk))
    {
        efuse_print_error("efuse clk enable is fail, 0x%x.\n", efuse_clk);
        goto clk_enable_error;
    }

    udelay(1000);/*lint !e737*/

    /*判断是否处在power_down状态*/
    if(hi_efuse_get_pd_status())
    {
       /*退出powerd_down状态*/
        hi_efusec_set_pd_en();
        /* 等待powerd_down退出标志设置成功，否则超时返回错误 */
        if(EFUSE_OK != test_bit_value(hi_efuse_get_pd_status, 0))
        {
            efuse_print_error(" power_down disable is fail .\n");
            goto efuse_write_error;
        }
    }

    /* 判断是否允许烧写,为1禁止烧写,直接退出 */
    if(hi_efusec_get_pgm_disable_flag())
    {
        efuse_print_error(" burn write is disable .\n");
        goto efuse_write_error;
    }

    /*选择信号为apb操作efuse*/
    hi_efusec_cfg_aib_sel();

    /* 配置时序要求 */
    hi_efusec_set_count(EFUSE_COUNT_CFG);
    hi_efusec_set_pgm_count(PGM_COUNT_CFG);

    /* 使能预烧写 */
    hi_efusec_set_pre_pg(1);

    /*查询是否使能置位 */
    if(EFUSE_OK != test_bit_value(hi_efusec_get_pgenb_status, 1))
    {
        efuse_print_error(" pre write enable is fail .\n");
        goto efuse_write_error;
    }

    /* 循环烧写 */
    u32Grp = group;
    pu32Value = pBuf;
    for (i = 0; i < len; i++)
    {
        /* 设置group */
        hi_efusec_set_group(u32Grp);

        /* 设置value */
        hi_efusec_set_pg_value(*pu32Value);

        /* 使能烧写 */
        hi_efusec_set_pg_en(1);

        /* 查询烧写完成 */
        if(EFUSE_OK != test_bit_value(hi_efusec_get_pg_status, 1))
        {
            efuse_print_error(" burn write finish is fail .\n");
            goto efuse_write_error;
        }

        /* 烧写下一组 */
        u32Grp++;
        pu32Value++;
    }

    /*去使能预烧写*/
    hi_efusec_set_pre_pg(0);

    ret = EFUSE_OK;

efuse_write_error:
    clk_disable(efuse_clk);

clk_enable_error:
    (void)regulator_disable(efuse_regulator);
    clk_unprepare(efuse_clk);

regulator_enable_error:
    spin_unlock_irqrestore(&efuse_lock, flags);

clk_prepare_error:
    clk_put(efuse_clk);

clk_get_error:
    regulator_put(efuse_regulator);

    return ret;
}

static int __init hi_efuse_init(void)
{
    void *addr = NULL;
    struct clk *efuse_clk = NULL;

    struct device_node *dev = NULL;
    const char name[] = "hisilicon,efuse_balong_app";

    dev = of_find_compatible_node(NULL, NULL, name);
    if(NULL == dev)
    {
        efuse_print_error("device node not found\n");
        return -1;
    }

    addr = of_iomap(dev, 0);
    if (0 == addr)
    {
        efuse_print_error("remap addr fail\n");
        return -1;
    }

    efuse_base_addr = addr;

    spin_lock_init(&efuse_lock);

    efuse_clk = (struct clk *)clk_get(NULL,"efuse_clk");
    if (IS_ERR(efuse_clk)) {
        efuse_print_error("efuse clk cannot get, 0x%x.\n", efuse_clk);
        return EFUSE_ERROR;
    }
    (void)clk_prepare(efuse_clk);
    (void)clk_enable(efuse_clk);
    clk_disable(efuse_clk);
    clk_unprepare(efuse_clk);
    clk_put(efuse_clk);

    efuse_print_info("efuse init ok.\n");

    return EFUSE_OK;
}

#else

int bsp_efuse_read(u32* pBuf, const u32 group, const u32 num)
{
    return EFUSE_OK;
}
int bsp_efuse_write( u32 *pBuf, const u32 group, const u32 len )
{
    return EFUSE_OK;
}
static int __init hi_efuse_init(void)
{
    return EFUSE_OK;
}

#endif

void bsp_efuse_show(void)
{
    unsigned int i = 0;
    unsigned int value = 0;

    for(i = 0;i < EFUSE_MAX_SIZE;i++)
    {
        if(OK == bsp_efuse_read(&value,i, 1))
        {
            efuse_print_info("efuse group%d value = 0x%x.\n ", i, value);
        }
        else
        {
            efuse_print_error("efuse group%d read fail.\n", i);
            return;
        }
    }
}

EXPORT_SYMBOL(bsp_efuse_show);
EXPORT_SYMBOL(bsp_efuse_read);
EXPORT_SYMBOL(bsp_efuse_write);

static void __exit hi_efuse_exit(void)
{
    /* do nothing */
}

module_init(hi_efuse_init);
module_exit(hi_efuse_exit);
MODULE_AUTHOR("Hisilicon Drive Group");
MODULE_DESCRIPTION("anten driver for the Hisilicon anten plug in/out");
MODULE_LICENSE("GPL");


