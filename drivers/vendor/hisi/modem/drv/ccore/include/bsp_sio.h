/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : balong_sio.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 
  最近修改   :
  功能描述   : drv_sio.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   :
    作    者   : 
    修改内容   : 

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BALONG_SIO_H__
#define __BALONG_SIO_H__

#include "bsp_memmap.h"
#include "drv_comm.h"
#include "bsp_clk.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define DRV_SIO_GET_STATUS_PTR()            (&g_stdrvsioctrl.stStatus)              /* 获取SIO状态寄存器指针 */
#define DRV_SIO_GET_INT_ISR_PTR()           (&g_stdrvsioctrl.stIsr)                 /* 获取SIO中断回调函数全局变量*/
#define DRV_SIO_GET_CFG_PTR()               (&g_stdrvsioctrl)

#define HI_SIO_REG_ADDR(offs)               (HI_LTESIO_REGBASE_ADDR_VIRT + (offs))

/*转定义按比特写函数*/
#define SIO_REG_WRITEBIT(uwAddr, uhwStartBit, uhwEndBit, swContent)    \
    BSP_REG_SETBITS(uwAddr, 0, uhwStartBit, uhwEndBit - uhwStartBit, swContent)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 实体名称  : DRV_SIO_INT_MASK_ENUM
 功能描述  : SIO各类中断掩码
*****************************************************************************/
typedef enum
{
    DRV_SIO_INT_MASK_RX_INTR            = 0x1,                                  /* 接收FIFO高于阈值中断                 */
    DRV_SIO_INT_MASK_TX_INTR            = 0x2,                                  /* 发送FIFO低于阈值中断                 */
    DRV_SIO_INT_MASK_RX_RIGHT_FIFO_OVER = 0x4,                                  /* I2S模式下为右声道接收FIFO上溢出中断  */
                                                                                /* PCM模式下为PCM接收FIFO上溢出中断     */
    DRV_SIO_INT_MASK_RX_LEFT_FIFO_OVER  = 0x8,                                  /* 左声道接收FIFO上溢出,只在I2S模式有效 */
    DRV_SIO_INT_MASK_TX_RIGHT_FIFO_UNDER= 0x10,                                 /* I2S模式下为右声道发送FIFO下溢出中断  */
                                                                                /* PCM模式下为PCM发送FIFO下溢出中断     */
    DRV_SIO_INT_MASK_TX_LEFT_FIFO_UNDER = 0x20,                                 /* 左声道接收FIFO下溢出,只在I2S模式有效 */
    DRV_SIO_INT_MASK_BUTT               = 0x40
}drv_sio_int_mask;

/*****************************************************************************
 实体名称  : DRV_SIO_STATE_ENUM
 功能描述  : SIO状态机
*****************************************************************************/
typedef enum
{
    DRV_SIO_STATE_CLOSE                  = 0,                                    /* SIO时钟关闭 */
    DRV_SIO_STATE_OPEN,                                                          /* SIO时钟打开 */
    DRV_SIO_STATE_BUTT
}drv_sio_state_e;

/*****************************************************************************
 实体名称  : DRV_SIO_SYNC_MODE_ENUM
 功能描述  : SIO时钟工作模式
*****************************************************************************/
typedef enum
{
    DRV_SIO_SYNC_MODE_SLAVE                  = 0,                                    /* SIO 从模式 */
    DRV_SIO_SYNC_MODE_MASTER,                                                        /* SIO 主模式 */
    DRV_SIO_SYNC_MODE_BUTT
}drv_sio_sync_mode_e;

/*****************************************************************************
 实体名称  : DRV_SIO_MODE_ENUM
 功能描述  : SIO工作模式
*****************************************************************************/
typedef enum
{
    DRV_SIO_MODE_I2S                            = 0,                /* SIO I2S工作模式 */
    DRV_SIO_MODE_PCM,                                               /* SIO PCM工作模式 */
    DRV_SIO_MODE_BUTT
}drv_sio_mode_e;

/*****************************************************************************
 实体名称  : drv_sio_chn_num_e
 功能描述  : SIO多路选择
*****************************************************************************/
typedef enum
{
    DRV_SIO_CHN_2                            = 0,               
    DRV_SIO_CHN_4,                                               
    DRV_SIO_CHN_8,
    DRV_SIO_CHN_16,
    DRV_SIO_CHN_BUTT
}drv_sio_chn_num_e;

/*****************************************************************************
 实体名称  : DRV_SIO_SAMPLING_ENUM
 功能描述  : SIO采样率
*****************************************************************************/
typedef enum
{
    DRV_SIO_SAMPLING_8K                        = 8000,               /* 采样率为8k */
    DRV_SIO_SAMPLING_16K                       = 16000,              /* 采样率为16k */
    DRV_SIO_SAMPLING_48K                       = 48000,              /* 采样率为48k */
    DRV_SIO_SAMPLING_BUTT
}drv_sio_sample_e;

/*****************************************************************************
 实体名称  : DRV_SIO_SAMPLING_ENUM
 功能描述  : SIO采样率
*****************************************************************************/
typedef enum
{
    DRV_SIO_DMA_CTRL                            = 0,               /* DMA工作方式 */
    DRV_SIO_INT_CTRL,                                              /* 中断工作方式 */
    DRV_SIO_POOL_CTRL,                                             /* 查询方式 */
    DRV_SIO_CTRL_BUTT
}drv_sio_ctrl_e;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : drv_sio_int_func
 功能描述  : SIO中断处理回调函数
 输入参数  : enIntType - 中断类型, 参见DRV_SIO_INT_TYPE_ENUM_UINT16
             uwPara    - 用户参数
 输出参数  : 无
 返 回 值  : void
*****************************************************************************/
typedef void (*drv_sio_int_func)(
                drv_sio_int_mask enIntType,
                unsigned int                   uwPara);

/*****************************************************************************
 实体名称  : drv_sio_int_isr_s
 功能描述  : 定义SIO中断回调函数数据实体
*****************************************************************************/
typedef struct
{
    drv_sio_int_func                      pfFunc;                                 /* 回调函数指针 */
    unsigned int                          uwPara;                               /* 回调参数     */
} drv_sio_int_isr_stru;

typedef void (*dma_int_func)(
                unsigned int                   uwPara);

/*****************************************************************************
 实体名称  : DRV_DMA_CXISR_STRU
 功能描述  : 定义DMA通道回调函数数据实体
*****************************************************************************/
typedef struct
{
    dma_int_func          pfFunc;         /* 回调函数指针 */
    unsigned int          uwPara;         /* 回调参数     */
} drv_dma_isr_stru;

typedef struct
{
   unsigned int       uwLli;              /* 通道Linked List Item地址     */
   unsigned short       uhwDstBIndex;       /* 通道的二维目的地址偏移量配置，占低16bit */
   unsigned short       uhwSrcBIndex;       /* 通道的二维源地址偏移量配置，占高16bit */
   unsigned short       uhwDstCIndex;       /* 通道的三维目的地址偏移量配置，占低16bit */
   unsigned short       uhwSrcCIndex;       /* 通道的三维源地址偏移量配置，占高16bit */
   unsigned short       uhwCCount;          /* 三维传输长度配置,单位Frame，占低16bit   */
   unsigned short       uhwRsv;             /* 保留位，占高16bit                    */
   unsigned short       uhwACount;          /* 一维传输长度配置,单位Byte，占低16bit */
   unsigned short       uhwBCount;          /* 二维传输长度配置,单位Array，占高16bit  */
   unsigned int       uwSrcAddr;          /* 通道源地址                   */
   unsigned int       uwDstAddr;          /* 通道目的地址                 */
   unsigned int       uwConfig;           /* 通道配置寄存器               */

} drv_dma_cfg_stru __attribute__((aligned(32)));

/*****************************************************************************
 实体名称  : pcm_data
 功能描述  : PCM数据实体
*****************************************************************************/
typedef struct
{
    unsigned int * usBufA;
    unsigned int ulBufALen;
    unsigned int * usBufB;
    unsigned int ulBufBLen;
}pcm_data;

/*****************************************************************************
 实体名称  : drv_sio_int_isr_s
 功能描述  : 定义SIO中断回调函数数据实体
*****************************************************************************/
typedef struct
{
    drv_dma_isr_stru                    pfFunc;                                 /* 回调函数指针 */
    drv_dma_cfg_stru                    play_cfg[2];
    drv_dma_cfg_stru                    record_cfg[2]; 
    unsigned int                        rx_channel_id;
    unsigned int                        tx_channel_id;
} dma_sio_cfg_stru;

/*****************************************************************************
 实体名称  : drv_sio_status_struct
 功能描述  : 定义SIO状态数据实体
*****************************************************************************/
typedef struct
{
    drv_sio_state_e               enOpen;                                       /* SIO开关状态 */
} drv_sio_status_stru;

/*****************************************************************************
 实体名称  : drv_sio_ctrk_struct
 功能描述  : 定义SIO控制实体
*****************************************************************************/
typedef struct
{
    drv_sio_status_stru                 stStatus;                                       /* SIO开关状态 */
    drv_sio_mode_e                      enMode;                                         /* SIO接口模式 */
    drv_sio_sync_mode_e                 enSyncMode;                                    /* SIO主从模式 */  
    drv_sio_chn_num_e                   chn_num;
    drv_sio_int_isr_stru                stIsr;                                          /* 保存SIO中断回调 */
    drv_sio_sample_e                    sample_rate;                                    /* 采样率 */     
    drv_sio_ctrl_e                      ctrl_mode;                                      /* 中断、查询或者DMA方式 */
    struct clk                         *sio_clk;
    dma_sio_cfg_stru                    dma_cfg;
} drv_sio_ctrl_stru;

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
void bsp_sio_close(void);
int bsp_sio_init(void);
void bsp_sio_isr(void);
int bsp_sio_open(
                       drv_sio_int_mask    enIntMask,
                       drv_sio_int_func    pfIntHandleFunc,
                       unsigned int        uwPara);

void bsp_sio_reset();
void bsp_sio_unreset();
void bsp_sio_set_mode(drv_sio_mode_e mode);
void bsp_sio_set_chn(drv_sio_chn_num_e chn_num);

#define DRV_SIO_DMA_LLI_LINK(uwAddr)        (((uwAddr) & 0xffffffe0UL) | (0x2UL))   /* 链表链接LLI配置字 */
#define DRV_SIO_DMA_LLI_CHAN(uhwChanNo)     (((unsigned int)(uhwChanNo) << 8)|(0x1UL))/* 通道链接LLI配置字 */
#define DRV_SIO_DMA_LLI_DISABLE             (0x0UL)                                 /* 链接模式不使能配置字 */

#define DRV_SIO_DMA_MEM_SIO_CFG             (0x83311057)                            /* 典型的MEM->SIO的DMA配置，源地址递增，16bit位宽burst4 */
#define DRV_SIO_DMA_SIO_MEM_CFG             (0x43311047)                            /* 典型的SIO->MEM的DMA配置，目的地址递增，16bit位宽burst4 */
#define DRV_SIO_DMA_MEM_MEM_CFG             (0xfff33003)                            /* 典型的MEM->MEM的DMA配置，地址双向递增，64bit位宽burst1  */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif 
