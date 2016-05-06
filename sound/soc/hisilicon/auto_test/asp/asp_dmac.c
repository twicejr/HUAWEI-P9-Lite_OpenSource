/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : asp_dmac.c
  版 本 号   : 初稿
  作    者   : w00262566
  生成日期   : 2015年1月26日
  最近修改   :
  功能描述   : asp dmac 模块
  函数列表   :

  修改历史   :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>

#include "util.h"
#include "asp_dmac.h"
#include "asp_edmac_reg_offset.h"



/*****************************************************************************
  2 全局变量与宏定义定义
*****************************************************************************/
#define DRV_NAME                    "asp_dmac"
#define BASE_ADDR_ASP_DMAC           0xE804B000
#define BASE_ADDR_ASP_DMAC_SIZE      0x1000
#define TX_SIZE                      0x100
#define CH_0_INT_MASK                0x1
#define CH_UNMASK                    0xfff
#define CH_INT_CLR                   0xfff
#define DMA_SIZE_TX                  0x100
#define DMA_TYPE_PLAY                0x1
#define DMA_TYPE_CAP                 0x0

static void* g_dmac_base_addr = 0;

#define ASP_DMAC_SI_OFFSET              31
#define ASP_DMAC_DI_OFFSET              30
#define ASP_DMAC_SMODE_OFFSET           29
#define ASP_DMAC_DMODE_OFFSET           28
#define ASP_DMAC_SL_OFFSET              24
#define ASP_DMAC_DL_OFFSET              20
#define ASP_DMAC_SW_OFFSET              16
#define ASP_DMAC_DW_OFFSET              12
#define ASP_DMAC_PERI_OFFSET            4
#define ASP_DMAC_FLOW_CTRL_OFFSET       2
#define ASP_DMAC_ITC_EN_OFFSET          1
#define ASP_DMAC_CH_EN_OFFSET           0


/* dma config cb*/
#define CONFIG_SI_RX                    (0x0 << ASP_DMAC_SI_OFFSET)
#define CONFIG_DI_RX                    (0x1 << ASP_DMAC_DI_OFFSET)

/* dma config pb*/
#define CONFIG_SI_TX                    (0x1 << ASP_DMAC_SI_OFFSET)
#define CONFIG_DI_TX                    (0x0 << ASP_DMAC_DI_OFFSET)

/* addr increase mode*/
#define CONFIG_SMODE                    (0x0 << ASP_DMAC_SMODE_OFFSET)
#define CONFIG_DMODE                    (0x0 << ASP_DMAC_DMODE_OFFSET)

/* burst length is 4 */
#define CONFIG_SL                       (0x3 << ASP_DMAC_SL_OFFSET)
#define CONFIG_DL                       (0x3 << ASP_DMAC_DL_OFFSET)

/* data length is 32bit */
#define CONFIG_SW                       (0x2 << ASP_DMAC_SW_OFFSET)
#define CONFIG_DW                       (0x2 << ASP_DMAC_DW_OFFSET)

/* for audio tx/rx request num*/
#define CONFIG_PERI_AUDIO_TX            (0x17 << ASP_DMAC_PERI_OFFSET)
#define CONFIG_PERI_AUDIO_RX            (0x16 << ASP_DMAC_PERI_OFFSET)

/* 0x1 dmac flow ctrl*/
#define CONFIG_FLOW_CTRL                (0x1 << ASP_DMAC_FLOW_CTRL_OFFSET)

/* 0x1 list item trans complete interrupt */
#define CONFIG_ITC_EN                   (0x1 << ASP_DMAC_ITC_EN_OFFSET)

/* 0x0 dma logic channel disable*/
#define CONFIG_CH_EN                    (0x0 << ASP_DMAC_CH_EN_OFFSET)

/* 0x2 list item enable*/
#define DMA_LLI_ENABLE                  (0x2)
#define DMA_LLI_DISABLE                 (0x0)

#define DMA_CONFIG_TX   (   \
            CONFIG_SI_TX                | CONFIG_DI_TX      |   \
            CONFIG_SMODE                | CONFIG_DMODE      |   \
            CONFIG_SL                   | CONFIG_DL         |   \
            CONFIG_SW                   | CONFIG_DW         |   \
            CONFIG_FLOW_CTRL            | CONFIG_ITC_EN     |   \
            CONFIG_CH_EN)

#define DMA_CONFIG_RX   (   \
            CONFIG_SI_RX                | CONFIG_DI_RX      |   \
            CONFIG_SMODE                | CONFIG_DMODE      |   \
            CONFIG_SL                   | CONFIG_DL         |   \
            CONFIG_SW                   | CONFIG_DW         |   \
            CONFIG_FLOW_CTRL            | CONFIG_ITC_EN     |   \
            CONFIG_CH_EN)


struct asp_dmac_list_cfg
{
    u32 next_addr_phys;
    u32 reserved[3];
    u32 count;
    u32 src_addr_phys;
    u32 des_addr_phys;
    u32 config;
} __aligned(32);


static int asp_dmac_remove(struct platform_device *pdev);
static int asp_dmac_probe(struct platform_device *pdev);

static const struct of_device_id asp_dmac_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver asp_dmac_driver = {
    .probe      = asp_dmac_probe,
    .remove     = asp_dmac_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = asp_dmac_of_match,
    },
};

static struct device* dmac_device = NULL;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : asp_dmac_reg_read
 功能描述  : 寄存器读函数
 输入参数  : unsigned int reg   寄存器偏移
 输出参数  : 无
 返 回 值  : int                寄存器值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int asp_dmac_reg_read(unsigned int reg)
{
    volatile unsigned int ret = 0;
    ret = readl(g_dmac_base_addr + reg);
    return ret;
}

/*****************************************************************************
 函 数 名  : asp_dmac_reg_write
 功能描述  : 寄存器写函数
 输入参数  : unsigned int reg   寄存器偏移
             unsigned int value 寄存器写入值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
void asp_dmac_reg_write(unsigned int reg, unsigned int value)
{
    writel(value, g_dmac_base_addr + reg);
    return;
}

/*****************************************************************************
 函 数 名  : asp_dmac_clear_interrupt
 功能描述  : dmac中断清除
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void asp_dmac_clear_interrupt()
{
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_TC1_RAW_REG,  CH_INT_CLR);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_TC2_RAW_REG , CH_INT_CLR);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_ERR1_RAW_REG, CH_INT_CLR);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_ERR2_RAW_REG, CH_INT_CLR);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_ERR3_RAW_REG, CH_INT_CLR);
}

/*****************************************************************************
 函 数 名  : asp_dmac_unmask
 功能描述  : dmac中断解屏蔽
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void asp_dmac_unmask(u32 cpu_num)
{
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_TC1_MASK_0_REG + 0x40 * cpu_num, CH_UNMASK);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_TC2_MASK_0_REG + 0x40 * cpu_num, CH_UNMASK);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_ERR1_MASK_0_REG+ 0x40 * cpu_num, CH_UNMASK);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_ERR2_MASK_0_REG+ 0x40 * cpu_num, CH_UNMASK);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_INT_ERR3_MASK_0_REG+ 0x40 * cpu_num, CH_UNMASK);

}


/*****************************************************************************
 函 数 名  : asp_dmac_fill_list_cfg
 功能描述  : 链式传输，链表配置
 输入参数  : struct asp_dmac_list_cfg* 链表配置指针
             dma_addr_t                链表物理地址
             dma_addr_t                源物理地址
             dma_addr_t                目的物理地址
             unsigned int              链表大小
             unsigned int              DMA 通道配置
             unsigned int              传输方向
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void asp_dmac_fill_list_cfg(struct asp_dmac_list_cfg *list_cfg,
                    dma_addr_t      lli_dma_addr,
                    dma_addr_t      src_dma_addr,
                    dma_addr_t      des_dma_addr,
                    unsigned int    size,
                    unsigned int    config,
                    unsigned int    type)
{

    u32 cnt  = DMA_SIZE_TX;
//    u32 cfg0 = 0x80022176;
    u32 addr = 0;
    u32 i    = 0;

    /* 链表初始化为0*/
    memset(list_cfg, 0x0, size * sizeof(struct asp_dmac_list_cfg));


    /* 设置各个链表项 */
    for (i = 0; i < size; i++){
        /* 指向链表下一项 */
        addr = (u32)(lli_dma_addr + (u32)sizeof(struct asp_dmac_list_cfg)*(i+1));
        list_cfg[i].next_addr_phys  = (addr) | 0x02;

        /* 根据传输方向，设置链表传输目的地址与源地址 */
        if(DMA_TYPE_PLAY == type){
            list_cfg[i].src_addr_phys   = src_dma_addr + cnt * i;
            list_cfg[i].des_addr_phys   = des_dma_addr;
        } else {
            list_cfg[i].src_addr_phys   = src_dma_addr;
            list_cfg[i].des_addr_phys   = des_dma_addr + cnt * i;
        }


        /* 设置链表传输大小与配置 */
        list_cfg[i].count           = cnt;
        list_cfg[i].config          = config;

        /*
        pr_info("%s,list_cfg[%d].list_cfg is %#x. list_cfg[%d] addr is %#x.\n",
                    __FUNCTION__, i, list_cfg[i].next_addr_phys, i + 1, addr);
        */
    }

    //pr_info("%s szie is %d\n",__FUNCTION__, size);

    /* 链表终止 */
    list_cfg[size - 1].next_addr_phys = 0x0;
}

/*****************************************************************************
 函 数 名  : asp_dmac_set_list_first
 功能描述  : 链式传输，第一次传输配置
 输入参数  : u32                       逻辑通道号
             u32                       传输数据长度
             u32                       传输配置
             dma_addr_t                源物理地址
             dma_addr_t                目的物理地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void asp_dmac_set_list_first( u32 channel_num,
                                    u32 cnt_num,
                                    u32 config,
                                    dma_addr_t src_dma_addr,
                                    dma_addr_t des_dma_addr)
{
    pr_info("%s begin\n",__FUNCTION__);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_CNT0_0_REG     + 0x40 * channel_num, cnt_num);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG + 0x40 * channel_num, src_dma_addr);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG + 0x40 * channel_num, des_dma_addr);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_CONFIG_0_REG   + 0x40 * channel_num, config);
    pr_info("%s end\n",__FUNCTION__);
}

/*****************************************************************************
 函 数 名  : asp_dmac_set_list
 功能描述  : dmac使能链表传输
 输入参数  : u32    逻辑通道号
             u32    使能配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void asp_dmac_set_list(u32 channel_num, u32 val)
{
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_LLI_0_REG + 0x40 * channel_num, val);
}

/*****************************************************************************
 函 数 名  : asp_dmac_wait_transit_finish
 功能描述  : dmac等待传输完成函数
 输入参数  : u32    逻辑通道号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void asp_dmac_wait_transit_finish(unsigned int channel)
{
    u32 value = 0;
    u32 count = 0;
    u32 c_tc2 = 0;
    u32 ch_int_mast = 0x1;

    ch_int_mast = (ch_int_mast<<channel);

    while (1) {

        /* 读取中断状态寄存器 */
        value = asp_dmac_reg_read(HI3650_ASP_EDMAC_INT_STAT_0_REG);
        pr_info("audio:%s,state v:%#x\n", __FUNCTION__, value);
        if (value&ch_int_mast) {

            /* 读取中断完成寄存器，如果中断完成，则完成等待 */
            value = asp_dmac_reg_read(HI3650_ASP_EDMAC_INT_TC1_0_REG);
            pr_info("audio:%s,int tc1_0 v:%#x\n",__FUNCTION__,value);
            if (value&ch_int_mast) {
                pr_info("audio:%s, DMA transit finished\n",__FUNCTION__);
                break;
            }

            /* 读取中断错误寄存器，如果存在错误，则推出等待 */
            value = asp_dmac_reg_read(HI3650_ASP_EDMAC_INT_ERR1_0_REG);
            pr_info("audio:%s,int err1_0 v:%#x\n",__FUNCTION__,value);
            if ((value&ch_int_mast) == 1) {
                pr_info("audio:%s, DMA config error\n",__FUNCTION__);
                break;
            }

            /* 读取中断错误寄存器，如果存在错误，则推出等待 */
            value = asp_dmac_reg_read(HI3650_ASP_EDMAC_INT_ERR2_0_REG);
            pr_info("audio:%s,int err2_0 v:%#x\n",__FUNCTION__,value);
            if (value&ch_int_mast) {
                pr_info("audio:%s, DMA data transit error\n",__FUNCTION__);
                break;
            }
        }

        count++;
        if (10 == count) {
            pr_info("audio:%s, over time.\n",__FUNCTION__);
            break;
        }
        msleep(20);
    }
}


/*****************************************************************************
 函 数 名  : asp_dmac_move_line
 功能描述  : dmac线性传输
 输入参数  : u32    逻辑通道号
             u32    使能配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int asp_dmac_move_line( unsigned int src,   unsigned int des,
                               unsigned int size,  unsigned int channel)
{
    unsigned int cnt0_0 = size;
    unsigned int config = 0xcff33001;
    unsigned int ret    = AT_SUCCESS;
    unsigned int value  = 0;
    unsigned int count  = 0;

    dma_addr_t  src_addr_phys,  des_addr_phys;

    src_addr_phys = src;
    des_addr_phys = des;

    pr_info("audio:src_addr_phys:0x%x,des_addr_phys = 0x%x \n",src_addr_phys,des_addr_phys);
    pr_info("audio:channel = 0x%x \n",channel);


    /* 清除中断并解除屏蔽 */
    pr_info("audio:clear interrupt and set tc1 err1 err2 mast to 0xfff \n");
    asp_dmac_clear_interrupt();
    asp_dmac_unmask(0);

    /* 设置传输源地址 */
    pr_info("audio:set dma src addr,src_addr_phys = %#x \n",src_addr_phys);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG+0x40*channel,
                        src_addr_phys);
    value = asp_dmac_reg_read(HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG+0x40*channel);
    pr_info("audio:HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG:%#x\n", value);


    /* 设置传输目的地址 */
    pr_info("audio:set dma des addr,des_addr_phys = %#x \n",des_addr_phys);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG+0x40*channel,
                        des_addr_phys);
    value = asp_dmac_reg_read(HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG+0x40*channel);
    pr_info("audio:%s HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG:%#x\n", __FUNCTION__,
                        value);
    /* 设置传输长度 */
    pr_info("audio:set dma count,cnt0_0 = %#x \n",cnt0_0);
    asp_dmac_reg_write(HI3650_ASP_EDMAC_CX_CNT0_0_REG+0x40*channel, cnt0_0);
    value = asp_dmac_reg_read(HI3650_ASP_EDMAC_CX_CNT0_0_REG+0x40*channel);
    pr_info("audio:%s HI3650_ASP_EDMAC_CX_CNT0_0_REG:%#x\n", __FUNCTION__, value);

    /* 设置DMA传输配置字 */
    pr_info("audio:set dma config,cfg_0 = %#x \n",config);
    asp_dmac_reg_write( HI3650_ASP_EDMAC_CX_CONFIG_0_REG+0x40*channel, config);
    value = asp_dmac_reg_read(HI3650_ASP_EDMAC_CX_CONFIG_0_REG+0x40*channel);
    pr_info("audio:%s HI3650_ASP_EDMAC_CX_CONFIG_0_REG:%#x\n", __FUNCTION__, value);

    /* 等待传输停止 */
    asp_dmac_wait_transit_finish(channel);

    /* 清除中断 */
    asp_dmac_clear_interrupt();

    return ret;
}

/*****************************************************************************
 函 数 名  : asp_dmac_move_list
 功能描述  : dmac链式传输
 输入参数  : u32    逻辑通道号
             u32    使能配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int asp_dmac_move_list( unsigned int src,   unsigned int des,
                              unsigned int size,  unsigned int channel,
                              unsigned int req,   unsigned int type)
{
    unsigned int ret    = AT_SUCCESS;
    unsigned int config ;
    struct asp_dmac_list_cfg *list_cfg = NULL;


    dma_addr_t  lfg_addr_phys;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;

    src_addr_phys = src;
    des_addr_phys = des;

    /* 分配配置链表空间*/
    list_cfg = (struct asp_dmac_list_cfg *)dma_alloc_coherent(dmac_device,
                                               size * sizeof(struct asp_dmac_list_cfg),
                                               &lfg_addr_phys, GFP_KERNEL);
    /* 清除中断并解除屏蔽 */
    asp_dmac_clear_interrupt();
    asp_dmac_unmask(0);

    /* 设置链表配置 */
    if(DMA_TYPE_PLAY == type) {
        config = DMA_CONFIG_TX | (req << ASP_DMAC_PERI_OFFSET);
    } else {
        config = DMA_CONFIG_RX | (req << ASP_DMAC_PERI_OFFSET);
    }
    asp_dmac_fill_list_cfg(list_cfg,
                lfg_addr_phys,
                src_addr_phys,
                des_addr_phys,
                size,
                config,
                type);

    /* 使能链表配置 */
    asp_dmac_set_list(channel, list_cfg[0].next_addr_phys);

    /* 设置第一次链表 */
    asp_dmac_set_list_first(channel, DMA_SIZE_TX, config, src_addr_phys, des_addr_phys);

    /* 等待传输结束 */
    asp_dmac_wait_transit_finish(channel);

    /* 清除中断 */
    asp_dmac_clear_interrupt();

    /* 释放配置链表空间*/
    dma_free_coherent(dmac_device, size*sizeof(struct asp_dmac_list_cfg),
                        (void*)list_cfg, lfg_addr_phys);
    return ret;
}


/*****************************************************************************
 函 数 名  : asp_dmac_reg_rw_test
 功能描述  : dmac寄存器读写测试
 输入参数  : struct at_util_reg_test_type 寄存器测试数组
             int                          寄存器测试数组大小
 输出参数  : 无
 返 回 值  : int 测试结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int asp_dmac_reg_rw_test(struct at_util_reg_test_type regs[], int size)
{
    return at_util_reg_test (regs, size, asp_dmac_reg_read, asp_dmac_reg_write);
}

/*****************************************************************************
 函 数 名  : asp_dmac_probe
 功能描述  : asp dmac 驱动初始化
 输入参数  : struct platform_device* 设备指针
 输出参数  : 无
 返 回 值  : 初始化结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static int asp_dmac_probe(struct platform_device *pdev)
{
    dmac_device = &pdev->dev;
    pr_info("%s.\n",__FUNCTION__);

    g_dmac_base_addr = ioremap(BASE_ADDR_ASP_DMAC, BASE_ADDR_ASP_DMAC_SIZE);
    if (!g_dmac_base_addr) {
        pr_info("cannot map register memory\n");
        return -ENOMEM;
    }


    return 0;
}

/*****************************************************************************
 函 数 名  : asp_dmac_remove
 功能描述  : asp dmac 驱动移除
 输入参数  : struct platform_device* 设备指针
 输出参数  : 无
 返 回 值  : 驱动移除结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static int asp_dmac_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    if(NULL != g_dmac_base_addr){
        iounmap(g_dmac_base_addr);
    }

    return 0;
}


/*****************************************************************************
 函 数 名  : asp_dmac_init
 功能描述  : asp dmac 模块初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块初始化结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static int __init asp_dmac_init(void)
{
    pr_info("%s \n",__FUNCTION__);
    platform_device_register_simple(DRV_NAME,0,NULL,0);
    return platform_driver_register(&asp_dmac_driver);
}
module_init(asp_dmac_init);

/*****************************************************************************
 函 数 名  : asp_dmac_exit
 功能描述  : asp dmac 模块移除
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块移除结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void __exit asp_dmac_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&asp_dmac_driver);
}
module_exit(asp_dmac_exit);

EXPORT_SYMBOL(asp_dmac_reg_read);
EXPORT_SYMBOL(asp_dmac_reg_write);
EXPORT_SYMBOL(asp_dmac_move_line);
EXPORT_SYMBOL(asp_dmac_reg_rw_test);

MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
