/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_cmd_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:19:59
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_CMD.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_CMD_INTERFACE_H__
#define __SOC_DSS_CMD_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_CMD
 ****************************************************************************/
/* 寄存器说明：CMDLIST通道控制寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ADDR(base, i)  ((base) + (0x0000+0x40*(i)))

/* 寄存器说明：CMDLIST通道控制寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_CTRL_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ADDR(base, i)     ((base) + (0x0004+0x40*(i)))

/* 寄存器说明：CMDLIST通道状态寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_STATUS_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ADDR(base, i)   ((base) + (0x0008+0x40*(i)))

/* 寄存器说明：CMDLIST通道起始地址寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_STAAD_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ADDR(base, i)    ((base) + (0x000C+0x40*(i)))

/* 寄存器说明：CMDLIST通道当前命令节点地址寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_CURAD_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ADDR(base, i)    ((base) + (0x0010+0x40*(i)))

/* 寄存器说明：CMDLIST通道中断使能寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_INTE_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ADDR(base, i)     ((base) + (0x0014+0x40*(i)))

/* 寄存器说明：CMDLIST通道中断清除寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_INTC_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ADDR(base, i)     ((base) + (0x0018+0x40*(i)))

/* 寄存器说明：CMDLIST通道中断状态寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_INTS_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ADDR(base, i)     ((base) + (0x001C+0x40*(i)))

/* 寄存器说明：CMDLIST通道debug计数寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_PERF_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ADDR(base, i)     ((base) + (0x0024+0x40*(i)))

/* 寄存器说明：DBG寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CH_DBG_UNION */
#define SOC_DSS_CMD_CMDLIST_CH_DBG_ADDR(base, i)      ((base) + (0x0028+0x40*(i)))

/* 寄存器说明：BUF DBG使能寄存器
   位域定义UNION结构:  SOC_DSS_CMD_BUF_DBG_EN_UNION */
#define SOC_DSS_CMD_BUF_DBG_EN_ADDR(base)             ((base) + (0x03F0))

/* 寄存器说明：BUF DBG计数清除寄存器
   位域定义UNION结构:  SOC_DSS_CMD_BUF_DBG_CNT_CLR_UNION */
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_ADDR(base)        ((base) + (0x03F4))

/* 寄存器说明：BUF DBG计数寄存器
   位域定义UNION结构:  SOC_DSS_CMD_BUF_DBG_CNT_UNION */
#define SOC_DSS_CMD_BUF_DBG_CNT_ADDR(base)            ((base) + (0x03F8))

/* 寄存器说明：CMDLIST超时阈值寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_UNION */
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_ADDR(base)     ((base) + (0x03FC))

/* 寄存器说明：CMDLIST通道启动寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_START_UNION */
#define SOC_DSS_CMD_CMDLIST_START_ADDR(base)          ((base) + (0x0400))

/* 寄存器说明：CMDLIST通道起始地址屏蔽寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_UNION */
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_ADDR(base) ((base) + (0x03E8))

/* 寄存器说明：CMDLIST通道起始地址屏蔽寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_UNION */
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_ADDR(base)  ((base) + (0x03EC))

/* 寄存器说明：CMDLIST通道起始地址屏蔽寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_UNION */
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_ADDR(base)   ((base) + (0x0404))

/* 寄存器说明：CMDLIST通道继续任务寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_UNION */
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_ADDR(base)  ((base) + (0x0408))

/* 寄存器说明：CMDLIST通道任务状态寄存器
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_TASK_STATUS_UNION */
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_ADDR(base)    ((base) + (0x040C))

/* 寄存器说明：CMDLIST控制寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_CTRL_UNION */
#define SOC_DSS_CMD_CMDLIST_CTRL_ADDR(base)           ((base) + (0x0410))

/* 寄存器说明：CMDLIST安全属性寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_SECU_UNION */
#define SOC_DSS_CMD_CMDLIST_SECU_ADDR(base)           ((base) + (0x0414))

/* 寄存器说明：CMDLIST中断状态寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_INTS_UNION */
#define SOC_DSS_CMD_CMDLIST_INTS_ADDR(base)           ((base) + (0x0418))

/* 寄存器说明：CMDLIST软件复位寄存器。
   位域定义UNION结构:  SOC_DSS_CMD_CMDLIST_SWRST_UNION */
#define SOC_DSS_CMD_CMDLIST_SWRST_ADDR(base)          ((base) + (0x041C))

/* 寄存器说明：MEM低功耗控制寄存器（TP）
   位域定义UNION结构:  SOC_DSS_CMD_CMD_MEM_CTRL_UNION */
#define SOC_DSS_CMD_CMD_MEM_CTRL_ADDR(base)           ((base) + (0x0420))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_CMD_CMD_CLK_SEL_UNION */
#define SOC_DSS_CMD_CMD_CLK_SEL_ADDR(base)            ((base) + (0x0428))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_CMD_CMD_CLK_EN_UNION */
#define SOC_DSS_CMD_CMD_CLK_EN_ADDR(base)             ((base) + (0x042C))





/*****************************************************************************
  3 枚举定义
*****************************************************************************/



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
  7 UNION定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_CMD
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_UNION
 结构说明  : CMDLIST_CH_PENDING_CLR 寄存器结构定义。地址偏移量:0x0000+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_pending_clr : 1;  /* bit[0]   : 1：退出pending状态 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ch_pending_clr_START  (0)
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ch_pending_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_CTRL_UNION
 结构说明  : CMDLIST_CH_CTRL 寄存器结构定义。地址偏移量:0x0004+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_enable      : 1;  /* bit[0]   : 1：CMDLIST使能, 0: CMDLIST禁止. CMDLIST禁止后, 等所有已发出AXI命令都返回后,通道处于IDLE状态。 */
        unsigned int  ch_auto_single : 1;  /* bit[1]   : 0：Single Frame Update模式
                                                         1： Auto Refresh 模式 */
        unsigned int  ch_start_sel   : 1;  /* bit[2]   : 在Auto Refresh模式下有效
                                                         0：选择看ldi0给出的sync信号作为start信号
                                                         1：选择看ldi1给出的sync信号作为start信号 */
        unsigned int  ch_pause       : 1;  /* bit[3]   : 1：当前命令节点完成后，暂停执行，软件清除该位后，继续执行下面的命令 */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_enable_START       (0)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_enable_END         (0)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_auto_single_START  (1)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_auto_single_END    (1)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_start_sel_START    (2)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_start_sel_END      (2)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_pause_START        (3)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_pause_END          (3)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_STATUS_UNION
 结构说明  : CMDLIST_CH_STATUS 寄存器结构定义。地址偏移量:0x0008+0x40*(i)，初值:0x00000C00，宽度:32
 寄存器说明: CMDLIST通道状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_ctl_fsm     : 4;  /* bit[0-3]  : 内部状态机，需要关注以下三个状态：
                                                          0x0:idle状态；
                                                          0x5:等待event_list的状态；
                                                          0x7:pending状态； */
        unsigned int  ch_items_fsm   : 4;  /* bit[4-7]  : 内部状态机,调试使用 */
        unsigned int  ch_dma_fsm     : 2;  /* bit[8-9]  : 内部状态机,调试使用 */
        unsigned int  ch_idle        : 1;  /* bit[10]   : CMDLIST通道的dma模块axi_idle */
        unsigned int  oa_idle        : 1;  /* bit[11]   : CMD通道完全idle */
        unsigned int  ch_cmd_done_id : 10; /* bit[12-21]: 当前完成的命令节点ID */
        unsigned int  ch_cmd_id      : 10; /* bit[22-31]: 当前命令节点的ID */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_ctl_fsm_START      (0)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_ctl_fsm_END        (3)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_items_fsm_START    (4)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_items_fsm_END      (7)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_dma_fsm_START      (8)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_dma_fsm_END        (9)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_idle_START         (10)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_idle_END           (10)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_oa_idle_START         (11)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_oa_idle_END           (11)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_done_id_START  (12)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_done_id_END    (21)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_id_START       (22)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_id_END         (31)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_STAAD_UNION
 结构说明  : CMDLIST_CH_STAAD 寄存器结构定义。地址偏移量:0x000C+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 4;  /* bit[0-3] : 保留 */
        unsigned int  ch_start_addr : 28; /* bit[4-31]: CMDLIST命令的起始始地址,128bit对齐 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_STAAD_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ch_start_addr_START  (4)
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ch_start_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_CURAD_UNION
 结构说明  : CMDLIST_CH_CURAD 寄存器结构定义。地址偏移量:0x0010+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道当前命令节点地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 4;  /* bit[0-3] : 保留 */
        unsigned int  ch_curr_addr : 28; /* bit[4-31]: CMDLIST当前执行命令的地址,128bit对齐，DEBUG用 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_CURAD_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ch_curr_addr_START  (4)
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ch_curr_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_INTE_UNION
 结构说明  : CMDLIST_CH_INTE 寄存器结构定义。地址偏移量:0x0014+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道中断使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_onedone_inte  : 1;  /* bit[0]   : 1: 一个命令节点中断完成中断使能, 0: 中断禁止 */
        unsigned int  ch_alldone_inte  : 1;  /* bit[1]   : 1: 所有命令节点中断完成中断使能, 0: 中断禁止 */
        unsigned int  ch_axi_err_inte  : 1;  /* bit[2]   : 1: AXI总线返回错误中断使能, 0: 中断禁止 */
        unsigned int  ch_pending_inte  : 1;  /* bit[3]   : 1: 进入Pending状态中断使能, 0: 中断禁止 */
        unsigned int  ch_start_inte    : 1;  /* bit[4]   : 1:当cmdlist开始执行一组命令时,中断使能, 0: 中断禁止 */
        unsigned int  ch_badcmd_inte   : 1;  /* bit[5]   : 1:错误命令格式中断使能 0: 中断禁止 */
        unsigned int  ch_timeout_inte  : 1;  /* bit[6]   : 1:timeout超时中断使能 0: 中断禁止 */
        unsigned int  ch_taskdone_inte : 1;  /* bit[7]   : 1:单个任务完成中断使能 0: 中断禁止 */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTE_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_onedone_inte_START   (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_onedone_inte_END     (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_alldone_inte_START   (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_alldone_inte_END     (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_axi_err_inte_START   (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_axi_err_inte_END     (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_pending_inte_START   (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_pending_inte_END     (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_start_inte_START     (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_start_inte_END       (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_badcmd_inte_START    (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_badcmd_inte_END      (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_timeout_inte_START   (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_timeout_inte_END     (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_taskdone_inte_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_taskdone_inte_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_INTC_UNION
 结构说明  : CMDLIST_CH_INTC 寄存器结构定义。地址偏移量:0x0018+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_onedone_intc  : 1;  /* bit[0]   : 1:中断清除 */
        unsigned int  ch_alldone_intc  : 1;  /* bit[1]   : 1:中断清除 */
        unsigned int  ch_axi_err_intc  : 1;  /* bit[2]   : 1:中断清除 */
        unsigned int  ch_pending_intc  : 1;  /* bit[3]   : 1:中断清除 */
        unsigned int  ch_start_intc    : 1;  /* bit[4]   : 1:中断清除 */
        unsigned int  ch_badcmd_intc   : 1;  /* bit[5]   : 1:中断清除 */
        unsigned int  ch_timeout_intc  : 1;  /* bit[6]   : 1:中断清除 */
        unsigned int  ch_taskdone_intc : 1;  /* bit[7]   : 1:中断清除 */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTC_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_onedone_intc_START   (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_onedone_intc_END     (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_alldone_intc_START   (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_alldone_intc_END     (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_axi_err_intc_START   (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_axi_err_intc_END     (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_pending_intc_START   (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_pending_intc_END     (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_start_intc_START     (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_start_intc_END       (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_badcmd_intc_START    (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_badcmd_intc_END      (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_timeout_intc_START   (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_timeout_intc_END     (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_taskdone_intc_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_taskdone_intc_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_INTS_UNION
 结构说明  : CMDLIST_CH_INTS 寄存器结构定义。地址偏移量:0x001C+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_onedone_ints  : 1;  /* bit[0]   : 1:产生中断, 0:没有中断 */
        unsigned int  ch_alldone_ints  : 1;  /* bit[1]   : 1:产生中断, 0:没有中断 */
        unsigned int  ch_axi_err_ints  : 1;  /* bit[2]   : 1:产生中断, 0:没有中断 */
        unsigned int  ch_pending_ints  : 1;  /* bit[3]   : 1:产生中断, 0:没有中断 */
        unsigned int  ch_start_ints    : 1;  /* bit[4]   : 1:产生中断, 0:没有中断 */
        unsigned int  ch_badcmd_ints   : 1;  /* bit[5]   : 1:产生中断, 0:没有中断 */
        unsigned int  ch_timeout_ints  : 1;  /* bit[6]   : 1:产生中断, 0:没有中断 */
        unsigned int  ch_taskdone_ints : 1;  /* bit[7]   : 1:产生中断, 0:没有中断 */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_onedone_ints_START   (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_onedone_ints_END     (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_alldone_ints_START   (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_alldone_ints_END     (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_axi_err_ints_START   (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_axi_err_ints_END     (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_pending_ints_START   (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_pending_ints_END     (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_start_ints_START     (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_start_ints_END       (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_badcmd_ints_START    (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_badcmd_ints_END      (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_timeout_ints_START   (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_timeout_ints_END     (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_taskdone_ints_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_taskdone_ints_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_PERF_UNION
 结构说明  : CMDLIST_CH_PERF 寄存器结构定义。地址偏移量:0x0024+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道debug计数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_perf_cnt : 32; /* bit[0-31]: 调试用 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_PERF_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ch_perf_cnt_START  (0)
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ch_perf_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CH_DBG_UNION
 结构说明  : CMDLIST_CH_DBG 寄存器结构定义。地址偏移量:0x0028+0x40*(i)，初值:0x00000000，宽度:32
 寄存器说明: DBG寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_dbg0 : 1;  /* bit[0]    : 保留 */
        unsigned int  cmd_dbg1 : 1;  /* bit[1]    : 保留 */
        unsigned int  cmd_dbg2 : 1;  /* bit[2]    : 保留 */
        unsigned int  cmd_dbg3 : 1;  /* bit[3]    : 保留 */
        unsigned int  cmd_dbg4 : 1;  /* bit[4]    : 保留 */
        unsigned int  cmd_dbg5 : 1;  /* bit[5]    : 保留 */
        unsigned int  cmd_dbg6 : 1;  /* bit[6]    : 保留 */
        unsigned int  cmd_dbg7 : 1;  /* bit[7]    : 保留 */
        unsigned int  cmd_dbg8 : 1;  /* bit[8]    : 保留 */
        unsigned int  cmd_dbg9 : 1;  /* bit[9]    : 保留 */
        unsigned int  reserved : 22; /* bit[10-31]: 保留； */
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_DBG_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg0_START  (0)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg0_END    (0)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg1_START  (1)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg1_END    (1)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg2_START  (2)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg2_END    (2)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg3_START  (3)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg3_END    (3)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg4_START  (4)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg4_END    (4)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg5_START  (5)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg5_END    (5)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg6_START  (6)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg6_END    (6)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg7_START  (7)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg7_END    (7)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg8_START  (8)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg8_END    (8)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg9_START  (9)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg9_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_BUF_DBG_EN_UNION
 结构说明  : BUF_DBG_EN 寄存器结构定义。地址偏移量:0x03F0，初值:0x00000000，宽度:32
 寄存器说明: BUF DBG使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_dbg_en : 1;  /* bit[0]   : 调试用寄存器，CMDLIST buf dbg使能信号，使能时CPU可读出BUF数据。
                                                     0: 不使能
                                                     1: 使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_CMD_BUF_DBG_EN_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_EN_buf_dbg_en_START  (0)
#define SOC_DSS_CMD_BUF_DBG_EN_buf_dbg_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_BUF_DBG_CNT_CLR_UNION
 结构说明  : BUF_DBG_CNT_CLR 寄存器结构定义。地址偏移量:0x03F4，初值:0x00000000，宽度:32
 寄存器说明: BUF DBG计数清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_dbg_cnt_clr : 1;  /* bit[0]   : 调试用寄存器，对应tpram200x128
                                                          [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                          [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                          [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                          [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_CMD_BUF_DBG_CNT_CLR_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_buf_dbg_cnt_clr_START  (0)
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_buf_dbg_cnt_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_BUF_DBG_CNT_UNION
 结构说明  : BUF_DBG_CNT 寄存器结构定义。地址偏移量:0x03F8，初值:0x000000C8，宽度:32
 寄存器说明: BUF DBG计数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_dbg_cnt_th : 8;  /* bit[0-7] : 调试用寄存器，buf计数寄存器，默认值设置为MEM深度。 */
        unsigned int  reserved       : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_CMD_BUF_DBG_CNT_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_CNT_buf_dbg_cnt_th_START  (0)
#define SOC_DSS_CMD_BUF_DBG_CNT_buf_dbg_cnt_th_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_UNION
 结构说明  : CMDLIST_TIMEOUT_TH 寄存器结构定义。地址偏移量:0x03FC，初值:0xFFFFFFFF，宽度:32
 寄存器说明: CMDLIST超时阈值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeout_th : 32; /* bit[0-31]: CMDLIST通道超时计数寄存器，当计数达到该配置值时timeout中断有效 */
    } reg;
} SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_timeout_th_START  (0)
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_timeout_th_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_START_UNION
 结构说明  : CMDLIST_START 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道启动寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start    : 14; /* bit[0-13] : single模式下有效
                                                    bit0：ch0启动任务脉冲信号；
                                                    bit1：ch1启动任务脉冲信号；
                                                    bit2：ch2启动任务脉冲信号；
                                                    bit3：ch3启动任务脉冲信号；
                                                    bit4：ch4启动任务脉冲信号；
                                                    bit5：ch5启动任务脉冲信号；
                                                    bit6：ch6启动任务脉冲信号；
                                                    bit7：ch7启动任务脉冲信号；
                                                    bit8：ch8启动任务脉冲信号；
                                                    bit9：ch9启动任务脉冲信号；
                                                    bit10：ch10启动任务脉冲信号；
                                                    bit11：ch11启动任务脉冲信号；
                                                    bit12：ch12启动任务脉冲信号；
                                                    bit13：ch13启动任务脉冲信号； */
        unsigned int  reserved : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_START_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_START_start_START     (0)
#define SOC_DSS_CMD_CMDLIST_START_start_END       (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_UNION
 结构说明  : CMDLIST_ADDR_MASK_STATUS 寄存器结构定义。地址偏移量:0x03E8，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道起始地址屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mask_status : 14; /* bit[0-13] : 1:表示软件正在改写start_addr，硬件禁止使用start_addr寄存器；
                                                            0:表示软件已经改写好start_addr，硬件可以使用start_addr；
                                                            bit1：ch1起始地址屏蔽；
                                                            bit2：ch2起始地址屏蔽；
                                                            bit3：ch3起始地址屏蔽；
                                                            bit4：ch4起始地址屏蔽；
                                                            bit5：ch5起始地址屏蔽；
                                                            bit6：ch6起始地址屏蔽；
                                                            bit7：ch7起始地址屏蔽；
                                                            bit8：ch8起始地址屏蔽；
                                                            bit9：ch9起始地址屏蔽；
                                                            bit10：ch10起始地址屏蔽；
                                                            bit11：ch11起始地址屏蔽；
                                                            bit12：ch12起始地址屏蔽；
                                                            bit13：ch13起始地址屏蔽； */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_addr_mask_status_START  (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_addr_mask_status_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_UNION
 结构说明  : CMDLIST_ADDR_MASK_DIS 寄存器结构定义。地址偏移量:0x03EC，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道起始地址屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mask_dis : 14; /* bit[0-13] : 软件配置该寄存器时，不需要先回读，直接配置对应bit即可；
                                                         1:表示软件已经改写完start_addr，硬件可以使用start_addr寄存器；
                                                         0:表示该bit无效，不起任何作用；
                                                         bit0：ch0起始地址不屏蔽；
                                                         bit1：ch1起始地址不屏蔽；
                                                         bit2：ch2起始地址不屏蔽；
                                                         bit3：ch3起始地址不屏蔽；
                                                         bit4：ch4起始地址不屏蔽；
                                                         bit5：ch5起始地址不屏蔽；
                                                         bit6：ch6起始地址不屏蔽；
                                                         bit7：ch7起始地址不屏蔽；
                                                         bit8：ch8起始地址不屏蔽；
                                                         bit9：ch9起始地址不屏蔽；
                                                         bit10：ch10起始地址不屏蔽；
                                                         bit11：ch11起始地址不屏蔽；
                                                         bit12：ch12起始地址不屏蔽；
                                                         bit13：ch13起始地址不屏蔽； */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_addr_mask_dis_START  (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_addr_mask_dis_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_UNION
 结构说明  : CMDLIST_ADDR_MASK_EN 寄存器结构定义。地址偏移量:0x0404，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道起始地址屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mask_en : 14; /* bit[0-13] : 软件配置该寄存器时，不需要先回读，直接配置对应bit即可；
                                                        1:表示软件正在改写start_addr，硬件禁止使用start_addr寄存器；
                                                        0:表示该bit无效，不起任何作用；
                                                        bit0：ch0起始地址屏蔽；
                                                        bit1：ch1起始地址屏蔽；
                                                        bit2：ch2起始地址屏蔽；
                                                        bit3：ch3起始地址屏蔽；
                                                        bit4：ch4起始地址屏蔽；
                                                        bit5：ch5起始地址屏蔽；
                                                        bit6：ch6起始地址屏蔽；
                                                        bit7：ch7起始地址屏蔽；
                                                        bit8：ch8起始地址屏蔽；
                                                        bit9：ch9起始地址屏蔽；
                                                        bit10：ch10起始地址屏蔽；
                                                        bit11：ch11起始地址屏蔽；
                                                        bit12：ch12起始地址屏蔽；
                                                        bit13：ch13起始地址屏蔽； */
        unsigned int  reserved     : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_addr_mask_en_START  (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_addr_mask_en_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_UNION
 结构说明  : CMDLIST_TASK_CONTINUE 寄存器结构定义。地址偏移量:0x0408，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道继续任务寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  task_continue : 14; /* bit[0-13] : 软件配置该寄存器时，不需要先回读，直接配置对应bit即可；
                                                         1:表示软件准备好新任务，可以继续跑新任务，cmdlist不需要重新开始跑链表；
                                                         0:表示该bit无效，不起任何作用；
                                                         bit0：ch0更新任务标志位；
                                                         bit1：ch1更新任务标志位；
                                                         bit2：ch2更新任务标志位；
                                                         bit3：ch3更新任务标志位；
                                                         bit4：ch4更新任务标志位；
                                                         bit5：ch5更新任务标志位；
                                                         bit6：ch6更新任务标志位；
                                                         bit7：ch7更新任务标志位；
                                                         bit8：ch8更新任务标志位；
                                                         bit9：ch9更新任务标志位；
                                                         bit10：ch10更新任务标志位；
                                                         bit11：ch11更新任务标志位；
                                                         bit12：ch12更新任务标志位；
                                                         bit13：ch13更新任务标志位； */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_task_continue_START  (0)
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_task_continue_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_TASK_STATUS_UNION
 结构说明  : CMDLIST_TASK_STATUS 寄存器结构定义。地址偏移量:0x040C，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST通道任务状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  task_status : 14; /* bit[0-13] : 1:当前有新任务还没有被CMD通道接收;
                                                       0:当前没有新任务需要CMD通道接收;
                                                       bit0：ch0任务状态标志位；
                                                       bit1：ch1任务状态标志位；
                                                       bit2：ch2任务状态标志位；
                                                       bit3：ch3任务状态标志位；
                                                       bit4：ch4任务状态标志位；
                                                       bit5：ch5任务状态标志位；
                                                       bit6：ch6任务状态标志位；
                                                       bit7：ch7任务状态标志位；
                                                       bit8：ch8任务状态标志位；
                                                       bit9：ch9任务状态标志位；
                                                       bit10：ch10任务状态标志位；
                                                       bit11：ch11任务状态标志位；
                                                       bit12：ch12任务状态标志位；
                                                       bit13：ch13任务状态标志位； */
        unsigned int  reserved    : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_TASK_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_task_status_START  (0)
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_task_status_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_CTRL_UNION
 结构说明  : CMDLIST_CTRL 寄存器结构定义。地址偏移量:0x0410，初值:0x00000400，宽度:32
 寄存器说明: CMDLIST控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_mid          : 4;  /* bit[0-3]  : side band signal for priority arbitration */
        unsigned int  axi_qos          : 2;  /* bit[4-5]  : forced qos value, axi_qos[1] = ctl_online, axi_qos[0]=ctl_qos.1表示优先极高,0:表示优先级低 */
        unsigned int  axi_mainpress    : 2;  /* bit[6-7]  : forced mainpress value, axi_mainpress[1]=ctl_online, axi_mainpress[0]=prirority. 1表示优先极高,0:表示优先级低 */
        unsigned int  axi_outstd_depth : 4;  /* bit[8-11] : outstanding深度，可配范围为1~8，默认配置为4 */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mid_START           (0)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mid_END             (3)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_qos_START           (4)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_qos_END             (5)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mainpress_START     (6)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mainpress_END       (7)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_outstd_depth_START  (8)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_outstd_depth_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_SECU_UNION
 结构说明  : CMDLIST_SECU 寄存器结构定义。地址偏移量:0x0414，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST安全属性寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_secu  : 14; /* bit[0-13] : CMDLIST通道起始地址寄存器的起始地址寄存器安全属性。1: 安全, 0: 非安全
                                                    bit0：ch0起始地址寄存器安全属性；
                                                    bit1：ch1起始地址寄存器安全属性；
                                                    bit2：ch2起始地址寄存器安全属性；
                                                    bit3：ch3起始地址寄存器安全属性；
                                                    bit4：ch4起始地址寄存器安全属性；
                                                    bit5：ch5起始地址寄存器安全属性；
                                                    bit6：ch6起始地址寄存器安全属性；
                                                    bit7：ch7起始地址寄存器安全属性；
                                                    bit8：ch8起始地址寄存器安全属性；
                                                    bit9：ch9起始地址寄存器安全属性；
                                                    bit10：ch10起始地址寄存器安全属性；
                                                    bit11：ch11起始地址寄存器安全属性；
                                                    bit12：ch12起始地址寄存器安全属性；
                                                    bit13：ch13起始地址寄存器安全属性； */
        unsigned int  reserved : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_SECU_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_SECU_ch_secu_START   (0)
#define SOC_DSS_CMD_CMDLIST_SECU_ch_secu_END     (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_INTS_UNION
 结构说明  : CMDLIST_INTS 寄存器结构定义。地址偏移量:0x0418，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_ints  : 14; /* bit[0-13] : CMDLIST通道中断状态。1:中断有效, 0: 中断无效
                                                    bit0：ch0中断状态；
                                                    bit1：ch1中断状态；
                                                    bit2：ch2中断状态；
                                                    bit3：ch3中断状态；
                                                    bit4：ch4中断状态；
                                                    bit5：ch5中断状态；
                                                    bit6：ch6中断状态；
                                                    bit7：ch7中断状态；
                                                    bit8：ch8中断状态；
                                                    bit9：ch9中断状态；
                                                    bit10：ch10中断状态；
                                                    bit11：ch11中断状态；
                                                    bit12：ch12中断状态；
                                                    bit13：ch13中断状态； */
        unsigned int  reserved : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_INTS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_INTS_ch_ints_START   (0)
#define SOC_DSS_CMD_CMDLIST_INTS_ch_ints_END     (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMDLIST_SWRST_UNION
 结构说明  : CMDLIST_SWRST 寄存器结构定义。地址偏移量:0x041C，初值:0x00000000，宽度:32
 寄存器说明: CMDLIST软件复位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_swreset : 14; /* bit[0-13] : CMDLIST通道软件复位。软件复位后.所有已发出AXI命令的数据返回后,通道处于IDLE状态；
                                                      bit0：ch0软件复位；
                                                      bit1：ch1软件复位；
                                                      bit2：ch2软件复位；
                                                      bit3：ch3软件复位；
                                                      bit4：ch4软件复位；
                                                      bit5：ch5软件复位；
                                                      bit6：ch6软件复位；
                                                      bit7：ch7软件复位；
                                                      bit8：ch8软件复位；
                                                      bit9：ch9软件复位；
                                                      bit10：ch10软件复位；
                                                      bit11：ch11软件复位；
                                                      bit12：ch12软件复位；
                                                      bit13：ch13软件复位； */
        unsigned int  reserved   : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMDLIST_SWRST_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_SWRST_ch_swreset_START  (0)
#define SOC_DSS_CMD_CMDLIST_SWRST_ch_swreset_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMD_MEM_CTRL_UNION
 结构说明  : CMD_MEM_CTRL 寄存器结构定义。地址偏移量:0x0420，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器（TP）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器，对应tpram200x128
                                                       [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_CMD_CMD_MEM_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMD_MEM_CTRL_cmd_mem_ctrl_START  (0)
#define SOC_DSS_CMD_CMD_MEM_CTRL_cmd_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMD_CLK_SEL_UNION
 结构说明  : CMD_CLK_SEL 寄存器结构定义。地址偏移量:0x0428，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                      1：表示强制打开时钟。
                                                      0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                      bit0：用于apb；
                                                      bit1：用于cmd逻辑；
                                                      bit2：reserved；
                                                      bit3：用于reg；
                                                      bit4：用于ch0；
                                                      bit5：用于ch1；
                                                      bit6：用于ch2；
                                                      bit7：用于ch3；
                                                      bit8：用于ch4；
                                                      bit9：用于ch5；
                                                      bit10：用于ch6；
                                                      bit11：用于ch7；
                                                      bit12：用于ch8；
                                                      bit13：用于ch9；
                                                      bit14：用于ch10；
                                                      bit15：用于ch11；
                                                      bit16：用于ch12；
                                                      bit17：用于ch13； */
    } reg;
} SOC_DSS_CMD_CMD_CLK_SEL_UNION;
#endif
#define SOC_DSS_CMD_CMD_CLK_SEL_cmd_clk_sel_START  (0)
#define SOC_DSS_CMD_CMD_CLK_SEL_cmd_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_CMD_CMD_CLK_EN_UNION
 结构说明  : CMD_CLK_EN 寄存器结构定义。地址偏移量:0x042C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                     1：表示软件时钟使能有效，允许硬件开钟
                                                     0：表示软件时钟使能无效，禁止硬件开钟
                                                     bit0：reserved；
                                                     bit1：用于cmd逻辑；
                                                     bit2：reserved；
                                                     bit3：用于reg；
                                                     bit4：用于ch0；
                                                     bit5：用于ch1；
                                                     bit6：用于ch2；
                                                     bit7：用于ch3；
                                                     bit8：用于ch4；
                                                     bit9：用于ch5；
                                                     bit10：用于ch6；
                                                     bit11：用于ch7；
                                                     bit12：用于ch8；
                                                     bit13：用于ch9；
                                                     bit14：用于ch10；
                                                     bit15：用于ch11；
                                                     bit16：用于ch12；
                                                     bit17：用于ch13； */
    } reg;
} SOC_DSS_CMD_CMD_CLK_EN_UNION;
#endif
#define SOC_DSS_CMD_CMD_CLK_EN_cmd_clk_en_START  (0)
#define SOC_DSS_CMD_CMD_CLK_EN_cmd_clk_en_END    (31)






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

#endif /* end of soc_dss_cmd_interface.h */
